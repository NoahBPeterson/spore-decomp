// Slice s00a9b480: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00537dc0();
extern "C" void FUN_00a7f8d0();
extern "C" void FUN_00a81a20();
extern "C" void FUN_00a9b120();

// @ 0x00a9b480  (762 bytes)
__declspec(naked) void FUN_00a9b480()
{
    __asm {
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x18
        // movss xmm3, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x50
        _emit 0x04
        // movss xmm2, dword ptr [eax + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0x08
        // movss xmm1, dword ptr [eax + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x3D
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // movss xmm7, dword ptr [0x1485720]
        _emit 0x83
        _emit 0xEC
        _emit 0x40
        // sub esp, 0x40
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0xE9
        // mov ebp, ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x65
        _emit 0x78
        // movss xmm4, dword ptr [ebp + 0x78]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x5D
        _emit 0x6C
        // subss xmm3, dword ptr [ebp + 0x6c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x55
        _emit 0x70
        // subss xmm2, dword ptr [ebp + 0x70]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x4D
        _emit 0x74
        // subss xmm1, dword ptr [ebp + 0x74]
        _emit 0x0F
        _emit 0x2E
        _emit 0xE7
        // ucomiss xmm4, xmm7
        _emit 0x9F
        // lahf 
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0xF6
        _emit 0xC4
        _emit 0x44
        // test ah, 0x44
        _emit 0x7B
        _emit 0x19
        // jnp 0xa9b4d8
        _emit 0x0F
        _emit 0x28
        _emit 0xC7
        // movaps xmm0, xmm7
        _emit 0xF3
        _emit 0x0F
        _emit 0x5E
        _emit 0xC4
        // divss xmm0, xmm4
        _emit 0x0F
        _emit 0x28
        _emit 0xE0
        // movaps xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE3
        // mulss xmm4, xmm3
        _emit 0x0F
        _emit 0x28
        _emit 0xDC
        // movaps xmm3, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD0
        // mulss xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0xF6
        _emit 0x45
        _emit 0x68
        _emit 0x02
        // test byte ptr [ebp + 0x68], 2
        _emit 0x0F
        _emit 0x84
        _emit 0xBD
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xa9b59f
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x85
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [ebp + 0x84]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA5
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [ebp + 0x80]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC1
        // mulss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE2
        // mulss xmm4, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC4
        // addss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x65
        _emit 0x7C
        // movss xmm4, dword ptr [ebp + 0x7c]
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
        _emit 0xA5
        _emit 0x8C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [ebp + 0x8c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // movss dword ptr [esp + 0x1c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x85
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [ebp + 0x90]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov eax, dword ptr [esp + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC1
        // mulss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE2
        // mulss xmm4, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC4
        // addss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA5
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [ebp + 0x88]
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
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // movss dword ptr [esp + 0x20], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x85
        _emit 0x9C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [ebp + 0x9c]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC1
        // mulss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8D
        _emit 0x98
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [ebp + 0x98]
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
        _emit 0x8D
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [ebp + 0x94]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCB
        // mulss xmm1, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC1
        // addss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // movss dword ptr [esp + 0x24], xmm0
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // mov edx, dword ptr [esp + 0x24]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // movss xmm3, dword ptr [esp + 0x10]
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
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], edx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // movss xmm1, dword ptr [esp + 0x18]
        _emit 0xF6
        _emit 0x45
        _emit 0x30
        _emit 0x02
        // test byte ptr [ebp + 0x30], 2
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x5D
        _emit 0x34
        // subss xmm3, dword ptr [ebp + 0x34]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x55
        _emit 0x38
        // subss xmm2, dword ptr [ebp + 0x38]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x4D
        _emit 0x3C
        // subss xmm1, dword ptr [ebp + 0x3c]
        _emit 0x0F
        _emit 0x84
        _emit 0xA5
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xa9b65d
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x45
        _emit 0x4C
        // movss xmm0, dword ptr [ebp + 0x4c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x65
        _emit 0x48
        // movss xmm4, dword ptr [ebp + 0x48]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC1
        // mulss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE2
        // mulss xmm4, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC4
        // addss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x65
        _emit 0x44
        // movss xmm4, dword ptr [ebp + 0x44]
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
        _emit 0x65
        _emit 0x54
        // movss xmm4, dword ptr [ebp + 0x54]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // movss dword ptr [esp + 0x1c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x45
        _emit 0x58
        // movss xmm0, dword ptr [ebp + 0x58]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov eax, dword ptr [esp + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC1
        // mulss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE2
        // mulss xmm4, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC4
        // addss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x65
        _emit 0x50
        // movss xmm4, dword ptr [ebp + 0x50]
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
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // movss dword ptr [esp + 0x20], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x45
        _emit 0x64
        // movss xmm0, dword ptr [ebp + 0x64]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC1
        // mulss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4D
        _emit 0x60
        // movss xmm1, dword ptr [ebp + 0x60]
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
        _emit 0x4D
        _emit 0x5C
        // movss xmm1, dword ptr [ebp + 0x5c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCB
        // mulss xmm1, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC1
        // addss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // movss dword ptr [esp + 0x24], xmm0
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // mov edx, dword ptr [esp + 0x24]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // movss xmm3, dword ptr [esp + 0x10]
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
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], edx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // movss xmm1, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x45
        _emit 0x0C
        // mov eax, dword ptr [ebp + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x14
        // movss xmm0, dword ptr [eax + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x40
        _emit 0x10
        // addss xmm0, dword ptr [eax + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x25
        _emit 0x64
        _emit 0x10
        _emit 0x47
        _emit 0x01
        // movss xmm4, dword ptr [0x1471064]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xB5
        _emit 0xD4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm6, dword ptr [ebp + 0xd4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xAD
        _emit 0xD0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm5, dword ptr [ebp + 0xd0]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC4
        // mulss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // movss dword ptr [esp + 0xc], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC0
        // mulss xmm0, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC4
        // mulss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA5
        _emit 0xCC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [ebp + 0xcc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xF0
        // mulss xmm6, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xCE
        // subss xmm1, xmm6
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // movss dword ptr [esp + 0x18], xmm1
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xDC
        _emit 0xC8
        // fmul st(0), st(0)
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE8
        // mulss xmm5, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xD5
        // subss xmm2, xmm5
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm2
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xDC
        _emit 0xC8
        // fmul st(0), st(0)
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE0
        // mulss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xDC
        // subss xmm3, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // movss dword ptr [esp + 0x10], xmm3
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xDC
        _emit 0xC8
        // fmul st(0), st(0)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xFA
        // fsqrt 
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x50
        // fst dword ptr [esp + 0x50]
        _emit 0xD9
        _emit 0xEE
        // fldz 
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xDF
        _emit 0xF1
        // fcompi st(1)
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x76
        _emit 0x27
        // jbe 0xa9b713
        _emit 0x0F
        _emit 0x28
        _emit 0xC7
        // movaps xmm0, xmm7
        _emit 0xF3
        _emit 0x0F
        _emit 0x5E
        _emit 0x44
        _emit 0x24
        _emit 0x50
        // divss xmm0, dword ptr [esp + 0x50]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD8
        // mulss xmm3, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD0
        // mulss xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // movss dword ptr [esp + 0x10], xmm3
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
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // movss dword ptr [esp + 0x18], xmm1
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // lea eax, [esp + 0x28]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // lea ecx, [esp + 0x14]
        _emit 0x51
        // push ecx
        call FUN_00a81a20
        _emit 0x66
        _emit 0x83
        _emit 0x4D
        _emit 0x30
        _emit 0x02
        // or word ptr [ebp + 0x30], 2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // movss xmm0, dword ptr [0x1485720]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5E
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // divss xmm0, dword ptr [esp + 0x14]
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x66
        _emit 0xFF
        _emit 0x45
        _emit 0x32
        // inc word ptr [ebp + 0x32]
        _emit 0x8D
        _emit 0x7D
        _emit 0x44
        // lea edi, [ebp + 0x44]
        _emit 0xB9
        _emit 0x09
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, 9
        _emit 0x8D
        _emit 0x74
        _emit 0x24
        _emit 0x28
        // lea esi, [esp + 0x28]
        _emit 0xF3
        _emit 0xA5
        // rep movsd dword ptr es:[edi], dword ptr [esi]
        _emit 0x8B
        _emit 0x45
        _emit 0x0C
        // mov eax, dword ptr [ebp + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0x48
        // movss xmm1, dword ptr [eax + 0x48]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x48
        _emit 0x44
        // addss xmm1, dword ptr [eax + 0x44]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x0D
        _emit 0x64
        _emit 0x10
        _emit 0x47
        _emit 0x01
        // mulss xmm1, dword ptr [0x1471064]
        _emit 0x5F
        // pop edi
        _emit 0xF3
        _emit 0x0F
        _emit 0x5E
        _emit 0xC1
        // divss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x44
        _emit 0x24
        _emit 0x4C
        // mulss xmm0, dword ptr [esp + 0x4c]
        _emit 0x5E
        // pop esi
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x85
        _emit 0x3C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss dword ptr [ebp + 0x13c], xmm0
        _emit 0x5D
        // pop ebp
        _emit 0x83
        _emit 0xC4
        _emit 0x40
        // add esp, 0x40
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00a9b780  (329 bytes)
__declspec(naked) void FUN_00a9b780()
{
    __asm {
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // movss xmm0, dword ptr [esp + 8]
        _emit 0x83
        _emit 0xEC
        _emit 0x0C
        // sub esp, 0xc
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x14
        // mov esi, dword ptr [esp + 0x14]
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x4E
        _emit 0x08
        // addss xmm1, dword ptr [esi + 8]
        _emit 0x0F
        _emit 0x2F
        _emit 0x4E
        _emit 0x0C
        // comiss xmm1, dword ptr [esi + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4E
        _emit 0x08
        // movss dword ptr [esi + 8], xmm1
        _emit 0x72
        _emit 0x09
        // jb 0xa9b7aa
        _emit 0x32
        _emit 0xC0
        // xor al, al
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x91
        _emit 0xD0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm2, dword ptr [ecx + 0xd0]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x7E
        _emit 0x20
        // movss xmm7, dword ptr [esi + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x99
        _emit 0xCC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm3, dword ptr [ecx + 0xcc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA9
        _emit 0xD4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm5, dword ptr [ecx + 0xd4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x76
        _emit 0x1C
        // movss xmm6, dword ptr [esi + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4E
        _emit 0x24
        // movss xmm1, dword ptr [esi + 0x24]
        _emit 0x8B
        _emit 0x41
        _emit 0x0C
        // mov eax, dword ptr [ecx + 0xc]
        _emit 0x8D
        _emit 0x56
        _emit 0x1C
        // lea edx, [esi + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD0
        // mulss xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xD7
        // addss xmm2, xmm7
        _emit 0x0F
        _emit 0x28
        _emit 0xE2
        // movaps xmm4, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x52
        _emit 0x08
        // movss xmm2, dword ptr [edx + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x62
        _emit 0x04
        // movss dword ptr [edx + 4], xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // movss dword ptr [esp + 0xc], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD8
        // mulss xmm3, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE8
        // mulss xmm5, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xD5
        // addss xmm2, xmm5
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x52
        _emit 0x08
        // movss dword ptr [edx + 8], xmm2
        _emit 0x0F
        _emit 0x28
        _emit 0xCE
        // movaps xmm1, xmm6
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xCB
        // addss xmm1, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x1D
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // movss xmm3, dword ptr [0x1485720]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x0A
        // movss dword ptr [edx], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA8
        _emit 0x68
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm5, dword ptr [eax + 0x168]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE8
        // mulss xmm5, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x05
        _emit 0x64
        _emit 0x10
        _emit 0x47
        _emit 0x01
        // mulss xmm0, dword ptr [0x1471064]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xDD
        // subss xmm3, xmm5
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE3
        // mulss xmm4, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x62
        _emit 0x04
        // movss dword ptr [edx + 4], xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD3
        // mulss xmm2, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x52
        _emit 0x08
        // movss dword ptr [edx + 8], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // addss xmm2, dword ptr [esp + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCB
        // mulss xmm1, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x0A
        // movss dword ptr [edx], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD0
        // mulss xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x56
        _emit 0x18
        // addss xmm2, dword ptr [esi + 0x18]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xE7
        // addss xmm4, xmm7
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE0
        // mulss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x66
        _emit 0x14
        // addss xmm4, dword ptr [esi + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xCE
        // addss xmm1, xmm6
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x46
        _emit 0x10
        // movss xmm0, dword ptr [esi + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC1
        // addss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x10
        // movss dword ptr [esi + 0x10], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x66
        _emit 0x14
        // movss dword ptr [esi + 0x14], xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x56
        _emit 0x18
        // movss dword ptr [esi + 0x18], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x80
        _emit 0x78
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [eax + 0x278]
        _emit 0x0F
        _emit 0x2E
        _emit 0x05
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // ucomiss xmm0, dword ptr [0x1485378]
        _emit 0x9F
        // lahf 
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x74
        _emit 0x24
        _emit 0x04
        // movss dword ptr [esp + 4], xmm6
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x7C
        _emit 0x24
        _emit 0x08
        // movss dword ptr [esp + 8], xmm7
        _emit 0xF6
        _emit 0xC4
        _emit 0x44
        // test ah, 0x44
        _emit 0x7B
        _emit 0x1B
        // jnp 0xa9b8c0
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0x56
        // push esi
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x49
        _emit 0x0C
        // mov ecx, dword ptr [ecx + 0xc]
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // lea eax, [esp + 0x10]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        call FUN_00a9b120
        _emit 0x83
        _emit 0xC4
        _emit 0x14
        // add esp, 0x14
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00a9b8d0  (329 bytes)
__declspec(naked) void FUN_00a9b8d0()
{
    __asm {
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x51
        _emit 0x0C
        // mov edx, dword ptr [ecx + 0xc]
        _emit 0x8B
        _emit 0x82
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edx + 0x84]
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x10
        // mov esi, dword ptr [esp + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5E
        _emit 0x28
        // movss xmm3, dword ptr [esi + 0x28]
        _emit 0x57
        // push edi
        _emit 0x3B
        _emit 0x82
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp eax, dword ptr [edx + 0x88]
        _emit 0x0F
        _emit 0x84
        _emit 0x8D
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xa9b97f
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x46
        _emit 0x08
        // movss xmm0, dword ptr [esi + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5E
        _emit 0x46
        _emit 0x0C
        // divss xmm0, dword ptr [esi + 0xc]
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x8B
        _emit 0x82
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edx + 0x88]
        _emit 0x2B
        _emit 0xC7
        // sub eax, edi
        _emit 0xC1
        _emit 0xF8
        _emit 0x02
        // sar eax, 2
        _emit 0x83
        _emit 0xE8
        _emit 0x01
        // sub eax, 1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm0
        _emit 0x75
        _emit 0x06
        // jne 0xa9b91a
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x07
        // movss xmm0, dword ptr [edi]
        _emit 0xEB
        _emit 0x5E
        // jmp 0xa9b978
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], eax
        _emit 0xDB
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fild dword ptr [esp + 0xc]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x7D
        _emit 0x06
        // jge 0xa9b92c
        _emit 0xD8
        _emit 0x05
        _emit 0xD0
        _emit 0x4F
        _emit 0x3F
        _emit 0x01
        // fadd dword ptr [0x13f4fd0]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // fmul dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x2C
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // cvttss2si eax, dword ptr [esp + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // movss xmm2, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x92
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [edx + 0x84]
        _emit 0xF3
        _emit 0x0F
        _emit 0x2A
        _emit 0xC0
        // cvtsi2ss xmm0, eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xD0
        // subss xmm2, xmm0
        _emit 0x0F
        _emit 0x2F
        _emit 0x15
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // comiss xmm2, dword ptr [0x1485378]
        _emit 0x76
        _emit 0x1C
        // jbe 0xa9b973
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x0C
        _emit 0x82
        // movss xmm1, dword ptr [edx + eax*4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x82
        _emit 0x04
        // movss xmm0, dword ptr [edx + eax*4 + 4]
        _emit 0x8D
        _emit 0x04
        _emit 0x82
        // lea eax, [edx + eax*4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xC1
        // subss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC2
        // mulss xmm0, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC1
        // addss xmm0, xmm1
        _emit 0xEB
        _emit 0x05
        // jmp 0xa9b978
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x04
        _emit 0x82
        // movss xmm0, dword ptr [edx + eax*4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC3
        // mulss xmm0, xmm3
        _emit 0x0F
        _emit 0x28
        _emit 0xD8
        // movaps xmm3, xmm0
        _emit 0x8B
        _emit 0x41
        _emit 0x0C
        // mov eax, dword ptr [ecx + 0xc]
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x41
        _emit 0x78
        // movss xmm0, dword ptr [ecx + 0x78]
        _emit 0xC1
        _emit 0xEA
        _emit 0x02
        // shr edx, 2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC3
        // mulss xmm0, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm0
        _emit 0xF6
        _emit 0xC2
        _emit 0x01
        // test dl, 1
        _emit 0x74
        _emit 0x08
        // je 0xa9b9a4
        _emit 0x8D
        _emit 0xAE
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebp, [esi + 0x80]
        _emit 0xEB
        _emit 0x02
        // jmp 0xa9b9a6
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0x8B
        _emit 0x91
        _emit 0xFC
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [ecx + 0x1fc]
        _emit 0x85
        _emit 0xD2
        // test edx, edx
        _emit 0x74
        _emit 0x11
        // je 0xa9b9c1
        _emit 0x8B
        _emit 0x86
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x90]
        _emit 0x0F
        _emit 0xAF
        _emit 0xC2
        // imul eax, edx
        _emit 0x03
        _emit 0x81
        _emit 0xE8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // add eax, dword ptr [ecx + 0x1e8]
        _emit 0xEB
        _emit 0x02
        // jmp 0xa9b9c3
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x8B
        _emit 0x51
        _emit 0x1C
        // mov edx, dword ptr [ecx + 0x1c]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0x80
        _emit 0x79
        _emit 0x22
        _emit 0x00
        // cmp byte ptr [ecx + 0x22], 0
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xB9
        _emit 0xD4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edi, dword ptr [ecx + 0x1d4]
        _emit 0x8D
        _emit 0x51
        _emit 0x68
        // lea edx, [ecx + 0x68]
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x91
        _emit 0x50
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // lea edx, [ecx + 0x250]
        _emit 0x52
        // push edx
        _emit 0x0F
        _emit 0x94
        _emit 0xC2
        // sete dl
        _emit 0x0F
        _emit 0xB6
        _emit 0xD2
        // movzx edx, dl
        _emit 0x52
        // push edx
        _emit 0x55
        // push ebp
        _emit 0x8D
        _emit 0x56
        _emit 0x1C
        // lea edx, [esi + 0x1c]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x30
        // mov edx, dword ptr [esp + 0x30]
        _emit 0x83
        _emit 0xC6
        _emit 0x10
        // add esi, 0x10
        _emit 0x56
        // push esi
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0x51
        _emit 0x14
        // mov edx, dword ptr [ecx + 0x14]
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        _emit 0x50
        // push eax
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x81
        _emit 0xBC
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea eax, [ecx + 0x1bc]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x41
        _emit 0x10
        // mov eax, dword ptr [ecx + 0x10]
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        call FUN_00a7f8d0
        _emit 0x83
        _emit 0xC4
        _emit 0x38
        // add esp, 0x38
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x59
        // pop ecx
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00a9ba20  (349 bytes)
__declspec(naked) void FUN_00a9ba20()
{
    __asm {
        _emit 0x51
        // push ecx
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // mov ebx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x8B
        _emit 0x28
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [ebx + 0x128]
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x10
        // mov ebp, dword ptr [esp + 0x10]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x1C
        // mov esi, dword ptr [esp + 0x1c]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x24
        // mov edi, dword ptr [esp + 0x24]
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x10], 0
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x7C
        _emit 0x28
        // jl 0xa9ba6f
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x39
        _emit 0x83
        _emit 0x2C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // cmp dword ptr [ebx + 0x12c], eax
        _emit 0x75
        _emit 0x0D
        // jne 0xa9ba5e
        _emit 0x8B
        _emit 0x45
        _emit 0x00
        // mov eax, dword ptr [ebp]
        _emit 0x8B
        _emit 0x50
        _emit 0x2C
        // mov edx, dword ptr [eax + 0x2c]
        _emit 0x57
        // push edi
        _emit 0x56
        // push esi
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], eax
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x09
        // je 0xa9ba6f
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xC1
        _emit 0xE1
        _emit 0x04
        // shl ecx, 4
        _emit 0x03
        _emit 0xF1
        // add esi, ecx
        _emit 0x2B
        _emit 0xF8
        // sub edi, eax
        _emit 0x8B
        _emit 0x83
        _emit 0x30
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [ebx + 0x130]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x7C
        _emit 0x1E
        // jl 0xa9ba97
        _emit 0x8B
        _emit 0x55
        _emit 0x00
        // mov edx, dword ptr [ebp]
        _emit 0x57
        // push edi
        _emit 0x56
        // push esi
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // add dword ptr [esp + 0x10], eax
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x09
        // je 0xa9ba97
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xC1
        _emit 0xE1
        _emit 0x04
        // shl ecx, 4
        _emit 0x03
        _emit 0xF1
        // add esi, ecx
        _emit 0x2B
        _emit 0xF8
        // sub edi, eax
        _emit 0x8B
        _emit 0x8B
        _emit 0xB4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [ebx + 0x1b4]
        _emit 0x2B
        _emit 0x8B
        _emit 0xB0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // sub ecx, dword ptr [ebx + 0x1b0]
        _emit 0xB8
        _emit 0xE9
        _emit 0xA2
        _emit 0x8B
        _emit 0x2E
        // mov eax, 0x2e8ba2e9
        _emit 0xF7
        _emit 0xE9
        // imul ecx
        _emit 0xC1
        _emit 0xFA
        _emit 0x04
        // sar edx, 4
        _emit 0x8B
        _emit 0xC2
        // mov eax, edx
        _emit 0xC1
        _emit 0xE8
        _emit 0x1F
        // shr eax, 0x1f
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x7E
        _emit 0x41
        // jle 0xa9baf9
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], eax
        _emit 0x8B
        _emit 0xFF
        // mov edi, edi
        _emit 0x8B
        _emit 0x8B
        _emit 0xB0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [ebx + 0x1b0]
        _emit 0x8B
        _emit 0x54
        _emit 0x29
        _emit 0x08
        // mov edx, dword ptr [ecx + ebp + 8]
        _emit 0x8B
        _emit 0x4C
        _emit 0x29
        _emit 0x0C
        // mov ecx, dword ptr [ecx + ebp + 0xc]
        _emit 0x8B
        _emit 0xC2
        // mov eax, edx
        _emit 0x23
        _emit 0xC1
        // and eax, ecx
        _emit 0x83
        _emit 0xF8
        _emit 0xFF
        // cmp eax, -1
        _emit 0x74
        _emit 0x18
        // je 0xa9baef
        _emit 0xFF
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // inc dword ptr [esp + 0x10]
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x7E
        _emit 0x10
        // jle 0xa9baef
        _emit 0x89
        _emit 0x16
        // mov dword ptr [esi], edx
        _emit 0x89
        _emit 0x4E
        _emit 0x04
        // mov dword ptr [esi + 4], ecx
        _emit 0xC7
        _emit 0x46
        _emit 0x08
        _emit 0x07
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 8], 7
        _emit 0x83
        _emit 0xC6
        _emit 0x10
        // add esi, 0x10
        _emit 0x4F
        // dec edi
        _emit 0x83
        _emit 0xC5
        _emit 0x58
        // add ebp, 0x58
        _emit 0x83
        _emit 0x6C
        _emit 0x24
        _emit 0x1C
        _emit 0x01
        // sub dword ptr [esp + 0x1c], 1
        _emit 0x75
        _emit 0xC7
        // jne 0xa9bac0
        _emit 0x8B
        _emit 0x8B
        _emit 0xE8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [ebx + 0x1e8]
        _emit 0x8B
        _emit 0x93
        _emit 0xEC
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [ebx + 0x1ec]
        _emit 0x8B
        _emit 0xC1
        // mov eax, ecx
        _emit 0x23
        _emit 0xC2
        // and eax, edx
        _emit 0x83
        _emit 0xF8
        _emit 0xFF
        // cmp eax, -1
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0x74
        _emit 0x15
        // je 0xa9bb27
        _emit 0x40
        // inc eax
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x7E
        _emit 0x10
        // jle 0xa9bb27
        _emit 0x89
        _emit 0x0E
        // mov dword ptr [esi], ecx
        _emit 0x89
        _emit 0x56
        _emit 0x04
        // mov dword ptr [esi + 4], edx
        _emit 0xC7
        _emit 0x46
        _emit 0x08
        _emit 0x05
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 8], 5
        _emit 0x83
        _emit 0xC6
        _emit 0x10
        // add esi, 0x10
        _emit 0x4F
        // dec edi
        _emit 0x8B
        _emit 0x8B
        _emit 0xF0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [ebx + 0x1f0]
        _emit 0x8B
        _emit 0x93
        _emit 0xF4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [ebx + 0x1f4]
        _emit 0x8B
        _emit 0xE9
        // mov ebp, ecx
        _emit 0x23
        _emit 0xEA
        // and ebp, edx
        _emit 0x83
        _emit 0xFD
        _emit 0xFF
        // cmp ebp, -1
        _emit 0x74
        _emit 0x15
        // je 0xa9bb51
        _emit 0x40
        // inc eax
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x7E
        _emit 0x10
        // jle 0xa9bb51
        _emit 0x89
        _emit 0x0E
        // mov dword ptr [esi], ecx
        _emit 0x89
        _emit 0x56
        _emit 0x04
        // mov dword ptr [esi + 4], edx
        _emit 0xC7
        _emit 0x46
        _emit 0x08
        _emit 0x05
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 8], 5
        _emit 0x83
        _emit 0xC6
        _emit 0x10
        // add esi, 0x10
        _emit 0x4F
        // dec edi
        _emit 0x8B
        _emit 0x8B
        _emit 0xF8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [ebx + 0x1f8]
        _emit 0x8B
        _emit 0x9B
        _emit 0xFC
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ebx, dword ptr [ebx + 0x1fc]
        _emit 0x8B
        _emit 0xD1
        // mov edx, ecx
        _emit 0x23
        _emit 0xD3
        // and edx, ebx
        _emit 0x83
        _emit 0xFA
        _emit 0xFF
        // cmp edx, -1
        _emit 0x74
        _emit 0x11
        // je 0xa9bb77
        _emit 0x40
        // inc eax
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x7E
        _emit 0x0C
        // jle 0xa9bb77
        _emit 0x89
        _emit 0x0E
        // mov dword ptr [esi], ecx
        _emit 0x89
        _emit 0x5E
        _emit 0x04
        // mov dword ptr [esi + 4], ebx
        _emit 0xC7
        _emit 0x46
        _emit 0x08
        _emit 0x05
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 8], 5
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0x59
        // pop ecx
        _emit 0xC3
        // ret 
    }
}

// @ 0x00a9bb80  (494 bytes)
__declspec(naked) void FUN_00a9bb80()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x0C
        // sub esp, 0xc
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x46
        _emit 0x78
        // movss xmm0, dword ptr [esi + 0x78]
        _emit 0x0F
        _emit 0x2E
        _emit 0x05
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // ucomiss xmm0, dword ptr [0x1485720]
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x7E
        _emit 0x68
        // lea edi, [esi + 0x68]
        _emit 0x9F
        // lahf 
        _emit 0xF6
        _emit 0xC4
        _emit 0x44
        // test ah, 0x44
        _emit 0x7A
        _emit 0x09
        // jp 0xa9bba6
        _emit 0xF6
        _emit 0x07
        _emit 0x06
        // test byte ptr [edi], 6
        _emit 0x75
        _emit 0x04
        // jne 0xa9bba6
        _emit 0xB3
        _emit 0x01
        // mov bl, 1
        _emit 0xEB
        _emit 0x02
        // jmp 0xa9bba8
        _emit 0x32
        _emit 0xDB
        // xor bl, bl
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov eax, dword ptr [esp + 0x1c]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4E
        _emit 0x30
        // lea ecx, [esi + 0x30]
        call FUN_00537dc0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_00537dc0
        _emit 0x8B
        _emit 0x56
        _emit 0x34
        // mov edx, dword ptr [esi + 0x34]
        _emit 0x8B
        _emit 0x46
        _emit 0x38
        // mov eax, dword ptr [esi + 0x38]
        _emit 0x8B
        _emit 0x4E
        _emit 0x3C
        // mov ecx, dword ptr [esi + 0x3c]
        _emit 0x89
        _emit 0x96
        _emit 0x30
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x130], edx
        _emit 0x89
        _emit 0x86
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x134], eax
        _emit 0xC6
        _emit 0x86
        _emit 0xD0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esi + 0x1d0], 0
        _emit 0x89
        _emit 0x8E
        _emit 0x38
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x138], ecx
        _emit 0xF6
        _emit 0x07
        _emit 0x02
        // test byte ptr [edi], 2
        _emit 0x0F
        _emit 0x84
        _emit 0xB1
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xa9bc9d
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0x134]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0x38
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0x138]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x96
        _emit 0x30
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm2, dword ptr [esi + 0x130]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5F
        _emit 0x20
        // movss xmm3, dword ptr [edi + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x67
        _emit 0x2C
        // movss xmm4, dword ptr [edi + 0x2c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD9
        // mulss xmm3, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE0
        // mulss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xDC
        // addss xmm3, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x67
        _emit 0x14
        // movss xmm4, dword ptr [edi + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE2
        // mulss xmm4, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xDC
        // addss xmm3, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x67
        _emit 0x24
        // movss xmm4, dword ptr [edi + 0x24]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // movss dword ptr [esp + 0xc], xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5F
        _emit 0x18
        // movss xmm3, dword ptr [edi + 0x18]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // mov edx, dword ptr [esp + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xDA
        // mulss xmm3, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE1
        // mulss xmm4, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xDC
        // addss xmm3, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x67
        _emit 0x30
        // movss xmm4, dword ptr [edi + 0x30]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE0
        // mulss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xDC
        // addss xmm3, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // movss dword ptr [esp + 0x10], xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5F
        _emit 0x1C
        // movss xmm3, dword ptr [edi + 0x1c]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xDA
        // mulss xmm3, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x57
        _emit 0x28
        // movss xmm2, dword ptr [edi + 0x28]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD1
        // mulss xmm2, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4F
        _emit 0x34
        // movss xmm1, dword ptr [edi + 0x34]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xDA
        // addss xmm3, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xD9
        // addss xmm3, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm3
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x89
        _emit 0x96
        _emit 0x30
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x130], edx
        _emit 0x89
        _emit 0x86
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x134], eax
        _emit 0x89
        _emit 0x8E
        _emit 0x38
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x138], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x47
        _emit 0x10
        // movss xmm0, dword ptr [edi + 0x10]
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x8E
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mulss xmm1, dword ptr [esi + 0x134]
        _emit 0x0F
        _emit 0x28
        _emit 0xD0
        // movaps xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x96
        _emit 0x38
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mulss xmm2, dword ptr [esi + 0x138]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x86
        _emit 0x30
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mulss xmm0, dword ptr [esi + 0x130]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0x30
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0x130], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x8E
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0x134], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x96
        _emit 0x38
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0x138], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x47
        _emit 0x08
        // movss xmm0, dword ptr [edi + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC1
        // addss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4F
        _emit 0x0C
        // movss xmm1, dword ptr [edi + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xCA
        // addss xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x57
        _emit 0x04
        // movss xmm2, dword ptr [edi + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x96
        _emit 0x30
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // addss xmm2, dword ptr [esi + 0x130]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x96
        _emit 0x30
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0x130], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0x134], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x8E
        _emit 0x38
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0x138], xmm1
        _emit 0x84
        _emit 0xDB
        // test bl, bl
        _emit 0x74
        _emit 0x17
        // je 0xa9bd2a
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x47
        _emit 0x10
        // movss xmm0, dword ptr [edi + 0x10]
        _emit 0x0F
        _emit 0x2E
        _emit 0x05
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // ucomiss xmm0, dword ptr [0x1485720]
        _emit 0x9F
        // lahf 
        _emit 0xF6
        _emit 0xC4
        _emit 0x44
        // test ah, 0x44
        _emit 0x7A
        _emit 0x05
        // jp 0xa9bd2a
        _emit 0xF6
        _emit 0x07
        _emit 0x06
        // test byte ptr [edi], 6
        _emit 0x74
        _emit 0x3B
        // je 0xa9bd65
        _emit 0x8B
        _emit 0x96
        _emit 0x54
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x254]
        _emit 0x2B
        _emit 0x96
        _emit 0x50
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // sub edx, dword ptr [esi + 0x250]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0xC1
        _emit 0xFA
        _emit 0x02
        // sar edx, 2
        _emit 0x85
        _emit 0xD2
        // test edx, edx
        _emit 0x76
        _emit 0x26
        // jbe 0xa9bd65
        _emit 0x90
        // nop 
        _emit 0x8B
        _emit 0x86
        _emit 0x50
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x250]
        _emit 0x8B
        _emit 0x0C
        _emit 0x98
        // mov ecx, dword ptr [eax + ebx*4]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x14
        // mov eax, dword ptr [edx + 0x14]
        _emit 0x57
        // push edi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x8E
        _emit 0x54
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x254]
        _emit 0x2B
        _emit 0x8E
        _emit 0x50
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // sub ecx, dword ptr [esi + 0x250]
        _emit 0x43
        // inc ebx
        _emit 0xC1
        _emit 0xF9
        _emit 0x02
        // sar ecx, 2
        _emit 0x3B
        _emit 0xD9
        // cmp ebx, ecx
        _emit 0x72
        _emit 0xDB
        // jb 0xa9bd40
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00a9bd70  (146 bytes)
__declspec(naked) void FUN_00a9bd70()
{
    __asm {
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
        _emit 0x53
        // push ebx
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x32
        _emit 0xDB
        // xor bl, bl
        _emit 0x2B
        _emit 0xC2
        // sub eax, edx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        // mov edi, dword ptr [esp + 0x10]
        _emit 0x74
        _emit 0x2B
        // je 0xa9bdad
        _emit 0x83
        _emit 0xE8
        _emit 0x01
        // sub eax, 1
        _emit 0x74
        _emit 0x16
        // je 0xa9bd9d
        _emit 0x83
        _emit 0xE8
        _emit 0x01
        // sub eax, 1
        _emit 0x75
        _emit 0x31
        // jne 0xa9bdbd
        _emit 0x8B
        _emit 0xC7
        // mov eax, edi
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x91
        _emit 0x34
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ecx + 0x234], edx
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x89
        _emit 0x81
        _emit 0x40
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ecx + 0x240], eax
        _emit 0x89
        _emit 0x91
        _emit 0x44
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ecx + 0x244], edx
        _emit 0xEB
        _emit 0x0E
        // jmp 0xa9bdbb
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x89
        _emit 0x81
        _emit 0x38
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ecx + 0x238], eax
        _emit 0x89
        _emit 0x91
        _emit 0x3C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ecx + 0x23c], edx
        _emit 0xB3
        _emit 0x01
        // mov bl, 1
        _emit 0x55
        // push ebp
        _emit 0x8D
        _emit 0x69
        _emit 0x24
        // lea ebp, [ecx + 0x24]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x75
        _emit 0x00
        // mov esi, dword ptr [ebp]
        _emit 0x3B
        _emit 0xF5
        // cmp esi, ebp
        _emit 0x74
        _emit 0x30
        // je 0xa9bdf9
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0x8B
        _emit 0x4E
        _emit 0x7C
        // mov ecx, dword ptr [esi + 0x7c]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x1C
        // je 0xa9bdf3
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov eax, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x52
        _emit 0x20
        // mov edx, dword ptr [edx + 0x20]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov eax, dword ptr [esp + 0x18]
        _emit 0x57
        // push edi
        _emit 0x50
        // push eax
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x75
        _emit 0x04
        // jne 0xa9bdf1
        _emit 0x84
        _emit 0xDB
        // test bl, bl
        _emit 0x74
        _emit 0x02
        // je 0xa9bdf3
        _emit 0xB3
        _emit 0x01
        // mov bl, 1
        _emit 0x8B
        _emit 0x36
        // mov esi, dword ptr [esi]
        _emit 0x3B
        _emit 0xF5
        // cmp esi, ebp
        _emit 0x75
        _emit 0xD7
        // jne 0xa9bdd0
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x5F
        // pop edi
        _emit 0x8A
        _emit 0xC3
        // mov al, bl
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
    }
}

// @ 0x00a9be10  (137 bytes)
__declspec(naked) void FUN_00a9be10()
{
    __asm {
        _emit 0x83
        _emit 0x7C
        _emit 0x24
        _emit 0x04
        _emit 0x00
        // cmp dword ptr [esp + 4], 0
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x74
        _emit 0x41
        // je 0xa9be5d
        _emit 0x8D
        _emit 0x7E
        _emit 0x24
        // lea edi, [esi + 0x24]
        _emit 0x8B
        _emit 0x37
        // mov esi, dword ptr [edi]
        _emit 0x32
        _emit 0xDB
        // xor bl, bl
        _emit 0x3B
        _emit 0xF7
        // cmp esi, edi
        _emit 0x74
        _emit 0x2E
        // je 0xa9be55
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x18
        // mov ebp, dword ptr [esp + 0x18]
        _emit 0x8D
        _emit 0x64
        _emit 0x24
        _emit 0x00
        // lea esp, [esp]
        _emit 0x8B
        _emit 0x4E
        _emit 0x7C
        // mov ecx, dword ptr [esi + 0x7c]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x17
        // je 0xa9be4e
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov edx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x40
        _emit 0x24
        // mov eax, dword ptr [eax + 0x24]
        _emit 0x55
        // push ebp
        _emit 0x52
        // push edx
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x75
        _emit 0x04
        // jne 0xa9be4c
        _emit 0x84
        _emit 0xDB
        // test bl, bl
        _emit 0x74
        _emit 0x02
        // je 0xa9be4e
        _emit 0xB3
        _emit 0x01
        // mov bl, 1
        _emit 0x8B
        _emit 0x36
        // mov esi, dword ptr [esi]
        _emit 0x3B
        _emit 0xF7
        // cmp esi, edi
        _emit 0x75
        _emit 0xDC
        // jne 0xa9be30
        _emit 0x5D
        // pop ebp
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x8A
        _emit 0xC3
        // mov al, bl
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // mov ebx, dword ptr [esp + 0x14]
        _emit 0xC6
        _emit 0x86
        _emit 0x2C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x01
        // mov byte ptr [esi + 0x22c], 1
        _emit 0x8B
        _emit 0xBE
        _emit 0x30
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov edi, dword ptr [esi + 0x230]
        _emit 0x3B
        _emit 0xDF
        // cmp ebx, edi
        _emit 0x74
        _emit 0x1F
        // je 0xa9be91
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x74
        _emit 0x08
        // je 0xa9be7e
        _emit 0x8B
        _emit 0x13
        // mov edx, dword ptr [ebx]
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x89
        _emit 0x9E
        _emit 0x30
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x230], ebx
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x74
        _emit 0x09
        // je 0xa9be91
        _emit 0x8B
        _emit 0x17
        // mov edx, dword ptr [edi]
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00a9bea0  (124 bytes)
__declspec(naked) void FUN_00a9bea0()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // mov ebx, dword ptr [esp + 8]
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8D
        _emit 0x6E
        _emit 0x24
        // lea ebp, [esi + 0x24]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7D
        _emit 0x00
        // mov edi, dword ptr [ebp]
        _emit 0x88
        _emit 0x5E
        _emit 0x22
        // mov byte ptr [esi + 0x22], bl
        _emit 0x3B
        _emit 0xFD
        // cmp edi, ebp
        _emit 0x74
        _emit 0x15
        // je 0xa9becc
        _emit 0x8B
        _emit 0x4F
        _emit 0x7C
        // mov ecx, dword ptr [edi + 0x7c]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x08
        // je 0xa9bec6
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x28
        // mov edx, dword ptr [eax + 0x28]
        _emit 0x53
        // push ebx
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x3F
        // mov edi, dword ptr [edi]
        _emit 0x3B
        _emit 0xFD
        // cmp edi, ebp
        _emit 0x75
        _emit 0xEB
        // jne 0xa9beb7
        _emit 0x8B
        _emit 0x86
        _emit 0x54
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x254]
        _emit 0x2B
        _emit 0x86
        _emit 0x50
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // sub eax, dword ptr [esi + 0x250]
        _emit 0x33
        _emit 0xFF
        // xor edi, edi
        _emit 0xC1
        _emit 0xF8
        _emit 0x02
        // sar eax, 2
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x76
        _emit 0x34
        // jbe 0xa9bf15
        _emit 0x84
        _emit 0xDB
        // test bl, bl
        _emit 0x0F
        _emit 0x94
        _emit 0xC3
        // sete bl
        _emit 0xEB
        _emit 0x08
        // jmp 0xa9bef0
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0x90
        // nop 
        _emit 0x8B
        _emit 0x8E
        _emit 0x50
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x250]
        _emit 0x8B
        _emit 0x0C
        _emit 0xB9
        // mov ecx, dword ptr [ecx + edi*4]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x30
        // mov eax, dword ptr [edx + 0x30]
        _emit 0x53
        // push ebx
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x8E
        _emit 0x54
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x254]
        _emit 0x2B
        _emit 0x8E
        _emit 0x50
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // sub ecx, dword ptr [esi + 0x250]
        _emit 0x47
        // inc edi
        _emit 0xC1
        _emit 0xF9
        _emit 0x02
        // sar ecx, 2
        _emit 0x3B
        _emit 0xF9
        // cmp edi, ecx
        _emit 0x72
        _emit 0xDB
        // jb 0xa9bef0
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}
