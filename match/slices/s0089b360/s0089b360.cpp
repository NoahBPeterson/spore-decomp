// Slice s0089b360 -- UTFSpore_Win32 EA framework (FrameDrawable / XML helpers).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---- stand-in classes -------------------------------------------------------
struct FrameDrawable_0089b360 {
    char    pad_000[0x3bc];                    // +0x000 .. +0x3bb
    void*   mp3bc;                             // +0x3bc

    void* F_0089b140(void* arg);               // 0x0089b140
    void Set3bc(void* arg);                    // 0x0089b360
};

// @ 0x0089b360
void FrameDrawable_0089b360::Set3bc(void* arg)
{
    mp3bc = this->F_0089b140(arg);
}
