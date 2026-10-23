// Slice s01164140: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"


// @ 0x01164140  (183 bytes)
__declspec(naked) void FUN_01164140()
{
    __asm {
        _emit 0x8D
        _emit 0x88
        _emit 0x00
        _emit 0x09
        _emit 0x00
        _emit 0x00
        // lea ecx, [eax + 0x900]
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x0F
        _emit 0x84
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0x11641f6
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x1D
        _emit 0x84
        _emit 0xF5
        _emit 0x3E
        _emit 0x01
        // movss xmm3, dword ptr [0x13ef584]
        _emit 0x83
        _emit 0xC0
        _emit 0x04
        // add eax, 4
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0xFC
        // movss xmm0, dword ptr [eax - 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xB8
        _emit 0xFC
        _emit 0x08
        _emit 0x00
        _emit 0x00
        // movss xmm7, dword ptr [eax + 0x8fc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x88
        _emit 0x00
        _emit 0x09
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [eax + 0x900]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x28
        // movss xmm5, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x90
        _emit 0x04
        _emit 0x09
        _emit 0x00
        _emit 0x00
        // movss xmm2, dword ptr [eax + 0x904]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x70
        _emit 0x04
        // movss xmm6, dword ptr [eax + 4]
        _emit 0x0F
        _emit 0x28
        _emit 0xE0
        // movaps xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC7
        // addss xmm0, xmm7
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC3
        // mulss xmm0, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x40
        _emit 0xFC
        // movss dword ptr [eax - 4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x00
        // movss xmm0, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xE9
        // subss xmm5, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xF2
        // subss xmm6, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC8
        // addss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x04
        // movss xmm0, dword ptr [eax + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xE7
        // subss xmm4, xmm7
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xD0
        // addss xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE3
        // mulss xmm4, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xEB
        // mulss xmm5, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xF3
        // mulss xmm6, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCB
        // mulss xmm1, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD3
        // mulss xmm2, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0xA0
        _emit 0xFC
        _emit 0x08
        _emit 0x00
        _emit 0x00
        // movss dword ptr [eax + 0x8fc], xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x08
        // movss dword ptr [eax], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0xA8
        _emit 0x00
        _emit 0x09
        _emit 0x00
        _emit 0x00
        // movss dword ptr [eax + 0x900], xmm5
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x50
        _emit 0x04
        // movss dword ptr [eax + 4], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0xB0
        _emit 0x04
        _emit 0x09
        _emit 0x00
        _emit 0x00
        // movss dword ptr [eax + 0x904], xmm6
        _emit 0x83
        _emit 0xC0
        _emit 0x0C
        // add eax, 0xc
        _emit 0x8D
        _emit 0x50
        _emit 0xFC
        // lea edx, [eax - 4]
        _emit 0x3B
        _emit 0xD1
        // cmp edx, ecx
        _emit 0x0F
        _emit 0x85
        _emit 0x6A
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jne 0x1164160
        _emit 0xC3
        // ret 
    }
}
