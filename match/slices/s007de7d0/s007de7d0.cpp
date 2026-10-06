// Slice s007de7d0 (w2g5 slice 24).  Region: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast.
// SP::cSmoothCameraController reset/pitch/zoom setters.
#include "types.h"

struct FVec { void* b; void* e; void* c; void* a; FVec& operator=(const FVec&); };

struct Cam24 {
    char pad0[0x30];        // +0x00
    FVec mZoomLevels;       // +0x30
    char pad1[4];           // +0x40
    FVec mNearClip;         // +0x44
    char pad2[4];           // +0x54
    FVec mFarClip;          // +0x58
    char pad3[0x138 - 0x68];// +0x68
    FVec mOrientations;     // +0x138

    void SetZoomLevels(const FVec& a, const FVec& b);   // 007df6a0
    void SetClipPlanes(const FVec& a, const FVec& b);   // 007df6d0
    void Reset();                                       // 007de7d0 (partial)
    void SetPitchAngles(const FVec& a, const FVec& b);  // 007df230 (partial)
};

void Cam24::SetPitchAngles(const FVec&, const FVec&)
{
    // 0x007df230: pitch-angle vector rebuild, skeleton only.
}

void FUN_007df330()
{
    // 0x007df330: quadratic ramp helper, skeleton only.
}

void FUN_007df450()
{
    // 0x007df450: cSmoothCameraController constructor body, skeleton only.
}

void* SP_CreateSmoothCameraController(void*)
{
    // 0x007df710: operator_new(0x3a4) + ctor, SEH wrapper not reproduced.
    return 0;
}

void Cam24::SetZoomLevels(const FVec& a, const FVec& b)
{
    mZoomLevels = a;
    mOrientations = b;
}

void Cam24::SetClipPlanes(const FVec& a, const FVec& b)
{
    mNearClip = a;
    mFarClip = b;
}

void Cam24::Reset()
{
    // 0x007de7d0: 2643-byte reset, skeleton only.
}
