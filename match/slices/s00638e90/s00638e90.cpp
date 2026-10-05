// slice s00638e90: cSPPlayModeSubModeAction (play-mode action sub-mode).
// PARTIAL skeletons only (all functions here are large UI/animation logic).
#include "../s00636320/s00636320.h"

struct cSPPlayModeSubModeAction {
    char pad[0x200];
    bool HasRequiredPart();
    float SetIdleAnimation(void* a, uint32_t b, int c, int d);
    void StartBoredAnimation(float t);
    void FUN_00639350();
    void MarkKeyInputKeyDown(int idx);
    void CaptureGIF();
    void FUN_00639b70();
};

// @ 0x00638E90
bool cSPPlayModeSubModeAction::HasRequiredPart() { return false; }
// @ 0x00638FD0
float cSPPlayModeSubModeAction::SetIdleAnimation(void* a, uint32_t b, int c, int d) { (void)a; (void)b; (void)c; (void)d; return 0.0f; }
// @ 0x006392E0
void cSPPlayModeSubModeAction::StartBoredAnimation(float t) { (void)t; }
// @ 0x00639350
void cSPPlayModeSubModeAction::FUN_00639350() {}
// @ 0x006398F0
void cSPPlayModeSubModeAction::MarkKeyInputKeyDown(int idx) { (void)idx; }
// @ 0x00639A10
void cSPPlayModeSubModeAction::CaptureGIF() {}
// @ 0x00639B70
void cSPPlayModeSubModeAction::FUN_00639b70() {}
