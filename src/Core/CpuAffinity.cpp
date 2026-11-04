#include "Core/CpuAffinity.hpp"
#include "Core/Paths.hpp"
#include <windows.h>
#include <tlhelp32.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern void Log(const char* fmt, ...);

namespace cvr::cpu {
namespace {
// The raw value of xr_cpu_affinity ("0", "1", "0xFFFF"); empty when missing.
bool ReadSetting(char* out, size_t size) {
    // The plugin's config folder (0.2.x layout), as the rest of the port reads vrport.ini.
    const std::string path = cvr::paths::FileA(cvr::paths::Folder::Config, "vrport.ini");
    FILE* f = nullptr;
    if (fopen_s(&f, path.c_str(), "r") != 0 || !f) return false;
    char line[256];
    bool found = false;
    while (!found && fgets(line, sizeof(line), f)) {
        char* p = line;
        while (*p == ' ' || *p == '\t') ++p;
        if (strncmp(p, "xr_cpu_affinity", 15) != 0) continue;
        p += 15;
        while (*p == ' ' || *p == '\t') ++p;
        if (*p != '=') continue;
        ++p;
        while (*p == ' ' || *p == '\t') ++p;
        size_t n = 0;
        while (p[n] && p[n] != '\r' && p[n] != '\n' && p[n] != ' ' && p[n] != ';' && n + 1 < size) { out[n] = p[n]; ++n; }
        out[n] = '\0';
        found = n > 0;
    }
    fclose(f);
    return found;
}

// The CPUs (processor group 0) of the largest L3, with every L3 logged; 0 when no L3 is larger than another: one L3, or
// equal ones (a 7950X), have no better CPUs to pick.
DWORD_PTR LargestL3Mask() {
    DWORD length = 0;
    GetLogicalProcessorInformationEx(RelationCache, nullptr, &length);
    std::vector<uint8_t> buffer(length);
    auto* info = reinterpret_cast<SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*>(buffer.data());
    if (!length || !GetLogicalProcessorInformationEx(RelationCache, info, &length)) return 0;
    DWORD_PTR best = 0;
    DWORD bestSize = 0, smallest = 0;
    for (DWORD offset = 0; offset < length;) {
        auto* entry = reinterpret_cast<SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*>(buffer.data() + offset);
        if (entry->Relationship == RelationCache && entry->Cache.Level == 3 && entry->Cache.GroupMask.Group == 0) {
            Log("[cpu] L3 %lu MB on CPUs 0x%llX\n", entry->Cache.CacheSize / (1024 * 1024),
                static_cast<unsigned long long>(entry->Cache.GroupMask.Mask));
            if (!smallest || entry->Cache.CacheSize < smallest) smallest = entry->Cache.CacheSize;
            if (entry->Cache.CacheSize > bestSize) { bestSize = entry->Cache.CacheSize; best = entry->Cache.GroupMask.Mask; }
        }
        offset += entry->Size;
    }
    return bestSize > smallest ? best : 0;
}

int ThreadCount() {
    const HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (snap == INVALID_HANDLE_VALUE) return -1;
    THREADENTRY32 t{sizeof(t)};
    int n = 0;
    const DWORD self = GetCurrentProcessId();
    for (BOOL ok = Thread32First(snap, &t); ok; ok = Thread32Next(snap, &t)) n += t.th32OwnerProcessID == self;
    CloseHandle(snap);
    return n;
}
}

void ApplyAffinity() {
    char value[32]{};
    if (!ReadSetting(value, sizeof(value)) || strcmp(value, "0") == 0) return;
    DWORD_PTR process = 0, system = 0;
    GetProcessAffinityMask(GetCurrentProcess(), &process, &system);
    const bool automatic = strcmp(value, "1") == 0;
    const DWORD_PTR wanted = automatic ? LargestL3Mask() : static_cast<DWORD_PTR>(strtoull(value, nullptr, 0));
    if (automatic && !wanted) { Log("[cpu] xr_cpu_affinity=1: no L3 is larger than another, left as it is\n"); return; }
    const DWORD_PTR mask = wanted & system;
    if (!mask) { Log("[cpu] xr_cpu_affinity=%s: no usable CPUs (system 0x%llX), left as it is\n", value, (unsigned long long)system); return; }
    const BOOL ok = SetProcessAffinityMask(GetCurrentProcess(), mask);
    Log("[cpu] xr_cpu_affinity=%s: process affinity 0x%llX -> 0x%llX %s (%d threads at plugin load)\n", value,
        (unsigned long long)process, (unsigned long long)mask, ok ? "set" : "FAILED", ThreadCount());
}
}
