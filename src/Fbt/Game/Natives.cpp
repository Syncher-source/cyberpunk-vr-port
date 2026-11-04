#include "Fbt/Game/Natives.hpp"
#include "Fbt/Game/Body.hpp"
#include "Fbt/Game/Calibration.hpp"
#include <RED4ext/Scripting/Functions.hpp>

extern "C" float CyberpunkVR_PlayerEntityPos[3];

namespace {
// VRFbtCalibrating() -> Int32: 1 while full-body tracking calibrates (Fbt/Game/Calibration.hpp). The VR menu closes
// itself when it turns on, so the player sees the "look down" arrow and the tracker helpers.
static void VRFbtCalibrating(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, int32_t* aOut, int64_t) {
    aFrame->code++;
    if (aOut) *aOut = cvr::fbt::game::Calibrating() ? 1 : 0;
}

// VRFbtCalibrationStep() -> Int32: the calibration's step, 0 off, 1 head, 2 body, 3 arms.
static void VRFbtCalibrationStep(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, int32_t* aOut, int64_t) {
    aFrame->code++;
    if (aOut) *aOut = cvr::fbt::game::CalibrationStep();
}
// VRFbtSetCalibrationText(step: Int32, text: String): the instruction drawn in the view for that step, translated.
static void VRFbtSetCalibrationText(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t) {
    int32_t step = 0;
    RED4ext::CString text;
    RED4ext::GetParameter(aFrame, &step);
    RED4ext::GetParameter(aFrame, &text);
    aFrame->code++;
    cvr::fbt::game::SetStepText(step, text.c_str());
    if (aOut) *aOut = true;
}

// VRFbtViewWorldZ() -> Vector4: Z = the height the view is drawn at while the camera stands at V's eyes, W = 1 then and
// 0 otherwise. VRViewWorldPos stays the head the hands are built from, which does not take this height.
static void VRFbtViewWorldZ(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, RED4ext::Vector4* aOut, int64_t) {
    aFrame->code++;
    if (!aOut) return;
    float eyeZ = 0.0f;
    const bool on = cvr::fbt::game::CameraEyeHeight(&eyeZ);
    aOut->X = 0.0f; aOut->Y = 0.0f;
    aOut->Z = on ? CyberpunkVR_PlayerEntityPos[2] + eyeZ : 0.0f;
    aOut->W = on ? 1.0f : 0.0f;
}
}  // namespace

using namespace wrpuppets::fbt;   // the IK library (externals/wrpuppets-fbt-ik)

namespace cvr::fbt::game {

void RegisterNatives(RED4ext::CRTTISystem* rtti) {
    RED4ext::CBaseFunction::Flags flags = {.isNative = true, .isStatic = true};
    auto fbtCalibrating = RED4ext::CGlobalFunction::Create("VRFbtCalibrating", "VRFbtCalibrating", &VRFbtCalibrating);
    fbtCalibrating->flags = flags; fbtCalibrating->SetReturnType("Int32"); rtti->RegisterFunction(fbtCalibrating);
    auto fbtStep = RED4ext::CGlobalFunction::Create("VRFbtCalibrationStep", "VRFbtCalibrationStep", &VRFbtCalibrationStep);
    fbtStep->flags = flags; fbtStep->SetReturnType("Int32"); rtti->RegisterFunction(fbtStep);
    auto fbtText = RED4ext::CGlobalFunction::Create("VRFbtSetCalibrationText", "VRFbtSetCalibrationText", &VRFbtSetCalibrationText);
    fbtText->flags = flags; fbtText->AddParam("Int32", "step"); fbtText->AddParam("String", "text"); fbtText->SetReturnType("Bool");
    rtti->RegisterFunction(fbtText);
    auto fbtViewZ = RED4ext::CGlobalFunction::Create("VRFbtViewWorldZ", "VRFbtViewWorldZ", &VRFbtViewWorldZ);
    fbtViewZ->flags = flags; fbtViewZ->SetReturnType("Vector4"); rtti->RegisterFunction(fbtViewZ);
}

}  // namespace cvr::fbt::game
