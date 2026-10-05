#include "types.h"

// Slice s005e16c0: SP::cSPEditorVerbIcon and friends.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (the float compares need /fp:fast).

// ---------------------------------------------------------------------------------------------
namespace SP {
struct cVerbIconInterpolationValue {
    float mTarget;      // +0x00
    float mCurrent;     // +0x04
    float mElapsed;     // +0x08
    float mInitial;     // +0x0c
    float mDuration;    // +0x10
    float mOverShoot;   // +0x14
    float mDampen;      // +0x18
    void Init(float a, float b, float c, float d, float e);
    int IsAtTarget();
};
}
using SP::cVerbIconInterpolationValue;

// @ 0x005e1c80
void cVerbIconInterpolationValue::Init(float a, float b, float c, float d, float e)
{
    mInitial = a;
    mCurrent = a;
    mTarget = b;
    mDuration = c;
    mOverShoot = e;
    mDampen = d;
    mElapsed = 0.0f;
}

// @ 0x005e1cd0
int cVerbIconInterpolationValue::IsAtTarget()
{
    if (mCurrent == mTarget && mElapsed >= mDuration)
        return 1;
    return 0;
}

// ---------------------------------------------------------------------------------------------
namespace SP {
struct cSPEditorVerbIcon {
    char pad[0x6a];
    char m6a;   // +0x6a
    char m6b;   // +0x6b
    void SetFlag(char b);
};
}
// @ 0x005e1fa0
void SP::cSPEditorVerbIcon::SetFlag(char b)
{
    m6b = 1;
    m6a = b;
}

// ---------------------------------------------------------------------------------------------
// Not reconstructed.  See partial.txt.

// @ 0x005e16c0
void FUN_005e16c0(void* self) { (void)self; }

// @ 0x005e1b70
void FUN_005e1b70(void* self) { (void)self; }

// @ 0x005e1d00
void FUN_005e1d00(void* self) { (void)self; }

// @ 0x005e1e90
void FUN_005e1e90(void* self) { (void)self; }

// @ 0x005e2000
void FUN_005e2000(void* self) { (void)self; }

// @ 0x005e2280
void FUN_005e2280(void* self) { (void)self; }

// @ 0x005e23b0
void FUN_005e23b0(void* self) { (void)self; }
