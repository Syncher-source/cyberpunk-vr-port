#pragma once

// CPU AFFINITY (xr_cpu_affinity in vrport.ini), applied once when the plugin loads, before the engine starts its job
// threads. 0 = untouched (default); 1 = auto: the CPUs sharing the largest L3 (the V-cache CCD of an X3D Ryzen, e.g.
// 0x0000FFFF on a 9950X3D), only when the L3s differ in size, so SteamVR and the rest can be kept on the other CCD by the player's own tools; or an
// explicit hex mask (0xFFFF). The engine's job pool (one worker per physical core, minus one) is left as it is.
namespace cvr::cpu {
void ApplyAffinity();
}
