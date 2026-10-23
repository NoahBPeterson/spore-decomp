// Slice s00f75c10: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_004df2d0();
extern "C" void FUN_007cda70();
extern "C" void FUN_00926650();
extern "C" void FUN_009360d0();

// @ 0x00f75c10  (931 bytes)
__declspec(naked) void FUN_00f75c10()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x18
        // sub esp, 0x18
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x24
        // mov edi, dword ptr [esp + 0x24]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x57
        _emit 0x10
        // movss xmm2, dword ptr [edi + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x67
        _emit 0x14
        // movss xmm4, dword ptr [edi + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5F
        _emit 0x18
        // movss xmm3, dword ptr [edi + 0x18]
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x80
        _emit 0xBE
        _emit 0xA1
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [esi + 0x1a1], 0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x64
        _emit 0x24
        _emit 0x18
        // movss dword ptr [esp + 0x18], xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // movss dword ptr [esp + 0x1c], xmm3
        _emit 0x0F
        _emit 0x84
        _emit 0x24
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // je 0xf75e6d
        _emit 0xB0
        _emit 0x02
        // mov al, 2
        _emit 0x84
        _emit 0x86
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // test byte ptr [esi + 0xb0], al
        _emit 0x0F
        _emit 0x84
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xf75d17
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0xdc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0xD0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0xd0]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCC
        // mulss xmm1, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC3
        // mulss xmm0, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC1
        // addss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0xc4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCA
        // mulss xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC1
        // addss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0xD4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0xd4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // movss dword ptr [esp + 8], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0xe0]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // mov ecx, dword ptr [esp + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCC
        // mulss xmm1, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC3
        // mulss xmm0, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC1
        // addss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0xc8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCA
        // mulss xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC1
        // addss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0xd8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // movss dword ptr [esp + 0xc], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0xE4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0xe4]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // mov edx, dword ptr [esp + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCC
        // mulss xmm1, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC3
        // mulss xmm0, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC1
        // addss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0xCC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0xcc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCA
        // mulss xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC1
        // addss xmm0, xmm1
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // movss xmm2, dword ptr [esp + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // movss dword ptr [esp + 0x10], xmm0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], edx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x64
        _emit 0x24
        _emit 0x18
        // movss xmm4, dword ptr [esp + 0x18]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // movss xmm3, dword ptr [esp + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0xc0]
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCA
        // mulss xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x8E
        _emit 0xB4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // addss xmm1, dword ptr [esi + 0xb4]
        _emit 0x0F
        _emit 0x28
        _emit 0xD0
        // movaps xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC3
        // mulss xmm0, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x9E
        _emit 0xB8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm3, dword ptr [esi + 0xb8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD4
        // mulss xmm2, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xDA
        // addss xmm3, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x96
        _emit 0xBC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm2, dword ptr [esi + 0xbc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xD0
        // addss xmm2, xmm0
        _emit 0x84
        _emit 0x86
        _emit 0xE8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // test byte ptr [esi + 0xe8], al
        _emit 0x0F
        _emit 0x84
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xf75e1d
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0x14
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0x114]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA6
        _emit 0x08
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [esi + 0x108]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC2
        // mulss xmm0, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE3
        // mulss xmm4, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC4
        // addss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA6
        _emit 0xFC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [esi + 0xfc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE1
        // mulss xmm4, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC4
        // addss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA6
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [esi + 0x10c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // movss dword ptr [esp + 8], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0x18
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0x118]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // mov edx, dword ptr [esp + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC2
        // mulss xmm0, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE3
        // mulss xmm4, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC4
        // addss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA6
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [esi + 0x100]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE1
        // mulss xmm4, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC4
        // addss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // movss dword ptr [esp + 0xc], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0x1C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0x11c]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov eax, dword ptr [esp + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC2
        // mulss xmm0, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x96
        _emit 0x10
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm2, dword ptr [esi + 0x110]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD3
        // mulss xmm2, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC2
        // addss xmm0, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x96
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm2, dword ptr [esi + 0x104]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD1
        // mulss xmm2, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC2
        // addss xmm0, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // movss dword ptr [esp + 0x10], xmm0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], edx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // movss xmm1, dword ptr [esp + 0x14]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // movss xmm3, dword ptr [esp + 0x18]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // movss xmm2, dword ptr [esp + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0xF8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0xf8]
        _emit 0x0F
        _emit 0x28
        _emit 0xE0
        // movaps xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE1
        // mulss xmm4, xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC2
        // mulss xmm0, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x96
        _emit 0xEC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm2, dword ptr [esi + 0xec]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xD4
        // addss xmm2, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCB
        // mulss xmm1, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x96
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm2, dword ptr [esi + 0xf0]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xD1
        // addss xmm2, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0xF4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0xf4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC8
        // addss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x54
        _emit 0x24
        _emit 0x18
        // movss dword ptr [esp + 0x18], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // movss dword ptr [esp + 0x1c], xmm1
        _emit 0x8B
        _emit 0x8E
        _emit 0x98
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x198]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x0F
        _emit 0x84
        _emit 0xBA
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xf75f35
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x52
        _emit 0x18
        // mov edx, dword ptr [edx + 0x18]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // lea eax, [esp + 0x14]
        _emit 0x50
        // push eax
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x0F
        _emit 0x84
        _emit 0xA6
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xf75f35
        _emit 0x8B
        _emit 0x8E
        _emit 0x98
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x198]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x40
        _emit 0x20
        // mov eax, dword ptr [eax + 0x20]
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // lea edx, [esp + 0x14]
        _emit 0x52
        // push edx
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // fst dword ptr [esp + 0x24]
        _emit 0x8B
        _emit 0x4E
        _emit 0x24
        // mov ecx, dword ptr [esi + 0x24]
        _emit 0x8B
        _emit 0x41
        _emit 0x08
        // mov eax, dword ptr [ecx + 8]
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0xC1
        _emit 0xEA
        _emit 0x06
        // shr edx, 6
        _emit 0xF6
        _emit 0xC2
        _emit 0x01
        // test dl, 1
        _emit 0x74
        _emit 0x61
        // je 0xf75f16
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0x6C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0x16c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // movss xmm0, dword ptr [esp + 0x24]
        _emit 0x0F
        _emit 0x2F
        _emit 0xC8
        // comiss xmm1, xmm0
        _emit 0x77
        _emit 0x6B
        // ja 0xf75f33
        _emit 0x0F
        _emit 0x2F
        _emit 0x86
        _emit 0x70
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // comiss xmm0, dword ptr [esi + 0x170]
        _emit 0x77
        _emit 0x62
        // ja 0xf75f33
        _emit 0x8B
        _emit 0x46
        _emit 0x24
        // mov eax, dword ptr [esi + 0x24]
        _emit 0x8B
        _emit 0x48
        _emit 0x08
        // mov ecx, dword ptr [eax + 8]
        _emit 0xC1
        _emit 0xE9
        _emit 0x05
        // shr ecx, 5
        _emit 0xF6
        _emit 0xC1
        _emit 0x01
        // test cl, 1
        _emit 0x74
        _emit 0x60
        // je 0xf75f3f
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0xB4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0x1b4]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0xC0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0x1c0]
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // lea edx, [esp + 8]
        _emit 0x52
        // push edx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // movss dword ptr [esp + 0xc], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // movss dword ptr [esp + 0x10], xmm1
        call FUN_004df2d0
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fadd dword ptr [esp + 0x20]
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xEB
        _emit 0x2B
        // jmp 0xf75f41
        _emit 0xC1
        _emit 0xE8
        _emit 0x07
        // shr eax, 7
        _emit 0xA8
        _emit 0x01
        // test al, 1
        _emit 0x74
        _emit 0xB4
        // je 0xf75ed1
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xB9
        _emit 0xDC
        _emit 0x78
        _emit 0x67
        _emit 0x01
        // mov ecx, 0x16778dc
        call FUN_009360d0
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xDB
        _emit 0xF1
        // fcomi st(1)
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0x77
        _emit 0x9E
        // ja 0xf75ed1
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x5F
        // pop edi
        _emit 0x32
        _emit 0xC0
        // xor al, al
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // movss dword ptr [esp + 8], xmm0
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // movss dword ptr [esp + 0xc], xmm0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // mov ecx, dword ptr [esp + 0xc]
        _emit 0x89
        _emit 0x47
        _emit 0x48
        // mov dword ptr [edi + 0x48], eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // movss dword ptr [esp + 0x10], xmm0
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov edx, dword ptr [esp + 0x10]
        _emit 0x89
        _emit 0x4F
        _emit 0x4C
        // mov dword ptr [edi + 0x4c], ecx
        _emit 0x89
        _emit 0x57
        _emit 0x50
        // mov dword ptr [edi + 0x50], edx
        _emit 0x80
        _emit 0xBE
        _emit 0xA1
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [esi + 0x1a1], 0
        _emit 0x74
        _emit 0x20
        // je 0xf75f94
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // lea eax, [esp + 0x14]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x8E
        _emit 0xE8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [esi + 0xe8]
        call FUN_007cda70
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // lea ecx, [esp + 0x14]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x8E
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [esi + 0xb0]
        call FUN_007cda70
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov edx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov eax, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov ecx, dword ptr [esp + 0x1c]
        _emit 0x89
        _emit 0x57
        _emit 0x10
        // mov dword ptr [edi + 0x10], edx
        _emit 0x89
        _emit 0x47
        _emit 0x14
        // mov dword ptr [edi + 0x14], eax
        _emit 0x89
        _emit 0x4F
        _emit 0x18
        // mov dword ptr [edi + 0x18], ecx
        _emit 0x5F
        // pop edi
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00f75fc0  (50 bytes)
__declspec(naked) void FUN_00f75fc0()
{
    __asm {
        _emit 0xA1
        _emit 0x68
        _emit 0x9B
        _emit 0x6C
        _emit 0x01
        // mov eax, dword ptr [0x16c9b68]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x75
        _emit 0x13
        // jne 0xf75fdc
        _emit 0x50
        // push eax
        _emit 0x50
        // push eax
        _emit 0xB9
        _emit 0x58
        _emit 0x9B
        _emit 0x6C
        _emit 0x01
        // mov ecx, 0x16c9b58
        call FUN_00926650
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x75
        _emit 0xE7
        // jne 0xf75fc0
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0xC3
        // ret 
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x89
        _emit 0x0D
        _emit 0x68
        _emit 0x9B
        _emit 0x6C
        _emit 0x01
        // mov dword ptr [0x16c9b68], ecx
        _emit 0xC7
        _emit 0x40
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [eax + 4], 0
        _emit 0xC7
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [eax], 0
        _emit 0xC3
        // ret 
    }
}
