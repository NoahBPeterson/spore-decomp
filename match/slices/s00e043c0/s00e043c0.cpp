// Slice s00e043c0 - SporeApp 0x00e043c0..0x00e05120
// SP::cSPUIGlobalUICiv / cSPUINewProgressBar UI helpers.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
//
// NOTE: the remaining slice VAs were not reconstructed in this pass and are
// recorded as unreconstructed in partial.txt.
#include "types.h"

typedef unsigned char u8;

// ---------------------------------------------------------------------------------------------
// Support types
// ---------------------------------------------------------------------------------------------
struct cSPUINewProgressBar {
    void Update(float value, int mode);   // 0x00e29da0
};

void __cdecl SPUIHelpers_SetWindowSPMaterial(void* window, int material, int flags);  // 0x00808ad0

// vtable slot dispatch helpers
static inline int  VT_0C_1(void* p, int a)
{
    return ((int (__thiscall*)(void*, int))(*(void***)p)[3])(p, a);
}
static inline void* VT_4C_0(void* p)
{
    return ((void* (__thiscall*)(void*))(*(void***)p)[0x13])(p);
}

// ---------------------------------------------------------------------------------------------
// UI classes
// ---------------------------------------------------------------------------------------------
struct cSPUIGlobalUICiv {
    u8                    mPad0000[0xc0];
    cSPUINewProgressBar*  mpProgressBarC0;   // 0xc0

    void SetProgress(float value, int mode);        // 0x00e04540
};

// @ 0x00e04540
// Forwards a progress value and its display mode to the progress bar.
void cSPUIGlobalUICiv::SetProgress(float value, int mode)
{
    mpProgressBarC0->Update(value, mode);
}

// @ 0x00e04a50
// Re-applies the blinking material to a comm button unless the button already
// carries the expected material.
void __stdcall FlashCivCommButton(int unused1, void* window, int unused3)
{
    if (window != 0)
        VT_0C_1(window, 0x8ed27e7a);
    void* child = VT_4C_0(window);
    if (child == 0)
        SPUIHelpers_SetWindowSPMaterial(window, 0x0147f2c8, 0);
    else if (VT_0C_1(child, 0x5234b49) == 0)
        SPUIHelpers_SetWindowSPMaterial(window, 0x0147f2c8, 0);
}
