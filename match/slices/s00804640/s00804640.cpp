// Slice s00804640 -- UTFWin::cSPUIFrameSequencer secondary object (Sec).
// 0x00804640  int Sec::Get0x1c()  -- returns the truncated frame duration.
//
// The original round-trips the float through a 4-byte scratch slot and converts
// it from memory (cvttss2si eax, [esp]); a plain (int)mDuration keeps the value
// in xmm0 and converts from the register.  A volatile copy forces the store.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

struct Sec {
    void** vtable;    // +0x00
    float  mTime;     // +0x04
    float  mFrameTime; // +0x08
    float  mDuration; // +0x0c

    int Get0x1c();
};

#pragma warning(disable:4035)
static __forceinline int TruncToInt(float f)
{
    __asm { cvttss2si eax, f }
}

// @ 0x00804640
int Sec::Get0x1c() { return TruncToInt(mDuration); }
