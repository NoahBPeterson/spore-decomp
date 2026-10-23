// Slice s00a94b90: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_007cdbe0();
extern "C" void FUN_009360d0();

// @ 0x00a94b90  (1046 bytes)
__declspec(naked) void FUN_00a94b90()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x14
        // sub esp, 0x14
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
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
        _emit 0xF9
        // mov edi, ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x08
        // movss dword ptr [esi + 8], xmm0
        _emit 0x8B
        _emit 0x47
        _emit 0x20
        // mov eax, dword ptr [edi + 0x20]
        _emit 0xD9
        _emit 0x40
        _emit 0x0C
        // fld dword ptr [eax + 0xc]
        _emit 0x83
        _emit 0xC0
        _emit 0x0C
        // add eax, 0xc
        _emit 0xDD
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // fstp qword ptr [esp + 0x10]
        _emit 0xB9
        _emit 0xDC
        _emit 0x78
        _emit 0x67
        _emit 0x01
        // mov ecx, 0x16778dc
        _emit 0xD9
        _emit 0x40
        _emit 0x04
        // fld dword ptr [eax + 4]
        _emit 0xDD
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fstp qword ptr [esp + 8]
        call FUN_009360d0
        _emit 0xDD
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld qword ptr [esp + 8]
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xDD
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld qword ptr [esp + 0x10]
        _emit 0xDC
        _emit 0xE9
        // fsub st(1), st(0)
        _emit 0xD9
        _emit 0xCB
        // fxch st(3)
        _emit 0xDE
        _emit 0xC9
        // fmulp st(1)
        _emit 0xD8
        _emit 0xC2
        // fadd st(2)
        _emit 0xDB
        _emit 0xF1
        // fcomi st(1)
        _emit 0x72
        _emit 0x06
        // jb 0xa94bdd
        _emit 0xDD
        _emit 0xDA
        // fstp st(2)
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0xEB
        _emit 0x0E
        // jmp 0xa94beb
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xDB
        _emit 0xF1
        // fcomi st(1)
        _emit 0x76
        _emit 0x04
        // jbe 0xa94be9
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0xEB
        _emit 0x02
        // jmp 0xa94beb
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xD8
        _emit 0x8F
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fmul dword ptr [edi + 0x134]
        _emit 0x8D
        _emit 0x87
        _emit 0x64
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea eax, [edi + 0x164]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // lea ecx, [esp + 0x14]
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x5E
        _emit 0x0C
        // fstp dword ptr [esi + 0xc]
        call FUN_007cdbe0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x89
        _emit 0x56
        _emit 0x10
        // mov dword ptr [esi + 0x10], edx
        _emit 0x8B
        _emit 0x48
        _emit 0x04
        // mov ecx, dword ptr [eax + 4]
        _emit 0x89
        _emit 0x4E
        _emit 0x14
        // mov dword ptr [esi + 0x14], ecx
        _emit 0x8B
        _emit 0x50
        _emit 0x08
        // mov edx, dword ptr [eax + 8]
        _emit 0x89
        _emit 0x56
        _emit 0x18
        // mov dword ptr [esi + 0x18], edx
        _emit 0x8B
        _emit 0x47
        _emit 0x20
        // mov eax, dword ptr [edi + 0x20]
        _emit 0x83
        _emit 0xC0
        _emit 0x28
        // add eax, 0x28
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // lea ecx, [esp + 0x1c]
        _emit 0x51
        // push ecx
        call FUN_007cdbe0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x89
        _emit 0x56
        _emit 0x1C
        // mov dword ptr [esi + 0x1c], edx
        _emit 0x8B
        _emit 0x48
        _emit 0x04
        // mov ecx, dword ptr [eax + 4]
        _emit 0x89
        _emit 0x4E
        _emit 0x20
        // mov dword ptr [esi + 0x20], ecx
        _emit 0x8B
        _emit 0x50
        _emit 0x08
        // mov edx, dword ptr [eax + 8]
        _emit 0x89
        _emit 0x56
        _emit 0x24
        // mov dword ptr [esi + 0x24], edx
        _emit 0x8B
        _emit 0x47
        _emit 0x20
        // mov eax, dword ptr [edi + 0x20]
        _emit 0xD9
        _emit 0x40
        _emit 0x40
        // fld dword ptr [eax + 0x40]
        _emit 0x83
        _emit 0xC0
        _emit 0x40
        // add eax, 0x40
        _emit 0xDD
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // fstp qword ptr [esp + 0x18]
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        _emit 0xD9
        _emit 0x40
        _emit 0x04
        // fld dword ptr [eax + 4]
        _emit 0xB9
        _emit 0xDC
        _emit 0x78
        _emit 0x67
        _emit 0x01
        // mov ecx, 0x16778dc
        _emit 0xDD
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // fstp qword ptr [esp + 0x10]
        call FUN_009360d0
        _emit 0xDD
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld qword ptr [esp + 0x10]
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xDD
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld qword ptr [esp + 8]
        _emit 0xDC
        _emit 0xE9
        // fsub st(1), st(0)
        _emit 0xD9
        _emit 0xCB
        // fxch st(3)
        _emit 0xDE
        _emit 0xC9
        // fmulp st(1)
        _emit 0xD8
        _emit 0xC2
        // fadd st(2)
        _emit 0xDB
        _emit 0xF1
        // fcomi st(1)
        _emit 0x72
        _emit 0x06
        // jb 0xa94c75
        _emit 0xDD
        _emit 0xDA
        // fstp st(2)
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0xEB
        _emit 0x0E
        // jmp 0xa94c83
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xDB
        _emit 0xF1
        // fcomi st(1)
        _emit 0x76
        _emit 0x04
        // jbe 0xa94c81
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0xEB
        _emit 0x02
        // jmp 0xa94c83
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x56
        _emit 0x20
        // movss xmm2, dword ptr [esi + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4E
        _emit 0x24
        // movss xmm1, dword ptr [esi + 0x24]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x46
        _emit 0x1C
        // movss xmm0, dword ptr [esi + 0x1c]
        _emit 0x0F
        _emit 0x57
        _emit 0xE4
        // xorps xmm4, xmm4
        _emit 0x0F
        _emit 0x28
        _emit 0xDA
        // movaps xmm3, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xDA
        // mulss xmm3, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC0
        // mulss xmm0, xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0xD1
        // movaps xmm2, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC3
        // addss xmm0, xmm3
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
        _emit 0x0F
        _emit 0x2F
        _emit 0xC4
        // comiss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // movss dword ptr [esp + 0x20], xmm0
        _emit 0x76
        _emit 0x26
        // jbe 0xa94ce0
        _emit 0xD8
        _emit 0x8F
        _emit 0x2C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fmul dword ptr [edi + 0x12c]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0xFA
        // fsqrt 
        _emit 0xDE
        _emit 0xF9
        // fdivp st(1)
        _emit 0xD9
        _emit 0x46
        _emit 0x1C
        // fld dword ptr [esi + 0x1c]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD9
        _emit 0x5E
        _emit 0x1C
        // fstp dword ptr [esi + 0x1c]
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD8
        _emit 0x4E
        _emit 0x20
        // fmul dword ptr [esi + 0x20]
        _emit 0xD9
        _emit 0x5E
        _emit 0x20
        // fstp dword ptr [esi + 0x20]
        _emit 0xD8
        _emit 0x4E
        _emit 0x24
        // fmul dword ptr [esi + 0x24]
        _emit 0xD9
        _emit 0x5E
        _emit 0x24
        // fstp dword ptr [esi + 0x24]
        _emit 0xEB
        _emit 0x02
        // jmp 0xa94ce2
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x8B
        _emit 0x4F
        _emit 0x20
        // mov ecx, dword ptr [edi + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x81
        _emit 0xF8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [ecx + 0xf8]
        _emit 0x0F
        _emit 0x2E
        _emit 0xC4
        // ucomiss xmm0, xmm4
        _emit 0x9F
        // lahf 
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // movss dword ptr [esp + 8], xmm0
        _emit 0xF6
        _emit 0xC4
        _emit 0x44
        // test ah, 0x44
        _emit 0x0F
        _emit 0x8B
        _emit 0x99
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jnp 0xa94d99
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4E
        _emit 0x14
        // movss xmm1, dword ptr [esi + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x89
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // subss xmm1, dword ptr [ecx + 0x100]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x56
        _emit 0x18
        // movss xmm2, dword ptr [esi + 0x18]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x91
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // subss xmm2, dword ptr [ecx + 0x104]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x46
        _emit 0x10
        // movss xmm0, dword ptr [esi + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x81
        _emit 0xFC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // subss xmm0, dword ptr [ecx + 0xfc]
        _emit 0x0F
        _emit 0x28
        _emit 0xDA
        // movaps xmm3, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xDA
        // mulss xmm3, xmm2
        _emit 0x0F
        _emit 0x28
        _emit 0xE9
        // movaps xmm5, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE9
        // mulss xmm5, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xDD
        // addss xmm3, xmm5
        _emit 0x0F
        _emit 0x28
        _emit 0xE8
        // movaps xmm5, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE8
        // mulss xmm5, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xDD
        // addss xmm3, xmm5
        _emit 0x0F
        _emit 0x2F
        _emit 0xDC
        // comiss xmm3, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // movss dword ptr [esp + 0x20], xmm3
        _emit 0x76
        _emit 0x4A
        // jbe 0xa94d99
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0xFA
        // fsqrt 
        _emit 0xD8
        _emit 0x7C
        _emit 0x24
        _emit 0x08
        // fdivr dword ptr [esp + 8]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // movss xmm3, dword ptr [esp + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC3
        // mulss xmm0, xmm3
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
        _emit 0x10
        _emit 0x5E
        _emit 0x1C
        // movss xmm3, dword ptr [esi + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xD8
        // addss xmm3, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x46
        _emit 0x20
        // movss xmm0, dword ptr [esi + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC1
        // addss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x20
        // movss dword ptr [esi + 0x20], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x46
        _emit 0x24
        // movss xmm0, dword ptr [esi + 0x24]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC2
        // addss xmm0, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x5E
        _emit 0x1C
        // movss dword ptr [esi + 0x1c], xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x24
        // movss dword ptr [esi + 0x24], xmm0
        _emit 0xB0
        _emit 0x02
        // mov al, 2
        _emit 0x84
        _emit 0x87
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // test byte ptr [edi + 0x94], al
        _emit 0x0F
        _emit 0x84
        _emit 0xB9
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xa94e60
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4E
        _emit 0x14
        // movss xmm1, dword ptr [esi + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x46
        _emit 0x18
        // movss xmm0, dword ptr [esi + 0x18]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x56
        _emit 0x10
        // movss xmm2, dword ptr [esi + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x9F
        _emit 0xB4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm3, dword ptr [edi + 0xb4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA7
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [edi + 0xc0]
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
        _emit 0x0F
        _emit 0x28
        _emit 0xE2
        // movaps xmm4, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xA7
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mulss xmm4, dword ptr [edi + 0xa8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xDC
        // addss xmm3, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA7
        _emit 0xB8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [edi + 0xb8]
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
        _emit 0x9F
        _emit 0xAC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm3, dword ptr [edi + 0xac]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
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
        _emit 0xA7
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [edi + 0xc4]
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
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x9F
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm3, dword ptr [edi + 0xb0]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov edx, dword ptr [esp + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xDA
        // mulss xmm3, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x97
        _emit 0xBC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm2, dword ptr [edi + 0xbc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD1
        // mulss xmm2, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8F
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [edi + 0xc8]
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
        _emit 0x89
        _emit 0x4E
        _emit 0x10
        // mov dword ptr [esi + 0x10], ecx
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
        _emit 0x18
        // movss dword ptr [esp + 0x18], xmm3
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x89
        _emit 0x56
        _emit 0x14
        // mov dword ptr [esi + 0x14], edx
        _emit 0x89
        _emit 0x4E
        _emit 0x18
        // mov dword ptr [esi + 0x18], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x87
        _emit 0xA4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [edi + 0xa4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4E
        _emit 0x14
        // movss xmm1, dword ptr [esi + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0xD0
        // movaps xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x56
        _emit 0x18
        // mulss xmm2, dword ptr [esi + 0x18]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x46
        _emit 0x10
        // mulss xmm0, dword ptr [esi + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x10
        // movss dword ptr [esi + 0x10], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4E
        _emit 0x14
        // movss dword ptr [esi + 0x14], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x56
        _emit 0x18
        // movss dword ptr [esi + 0x18], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x87
        _emit 0x9C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [edi + 0x9c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC1
        // addss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8F
        _emit 0xA0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [edi + 0xa0]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xCA
        // addss xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x56
        _emit 0x10
        // movss xmm2, dword ptr [esi + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x97
        _emit 0x98
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // addss xmm2, dword ptr [edi + 0x98]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x56
        _emit 0x10
        // movss dword ptr [esi + 0x10], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x14
        // movss dword ptr [esi + 0x14], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4E
        _emit 0x18
        // movss dword ptr [esi + 0x18], xmm1
        _emit 0x84
        _emit 0x87
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // test byte ptr [edi + 0x94], al
        _emit 0x0F
        _emit 0x84
        _emit 0xB9
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xa94f86
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4E
        _emit 0x20
        // movss xmm1, dword ptr [esi + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x46
        _emit 0x24
        // movss xmm0, dword ptr [esi + 0x24]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x56
        _emit 0x1C
        // movss xmm2, dword ptr [esi + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x9F
        _emit 0xB4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm3, dword ptr [edi + 0xb4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA7
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [edi + 0xc0]
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
        _emit 0x0F
        _emit 0x28
        _emit 0xE2
        // movaps xmm4, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xA7
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mulss xmm4, dword ptr [edi + 0xa8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xDC
        // addss xmm3, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA7
        _emit 0xB8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [edi + 0xb8]
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
        _emit 0x9F
        _emit 0xAC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm3, dword ptr [edi + 0xac]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov edx, dword ptr [esp + 0x10]
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
        _emit 0xA7
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [edi + 0xc4]
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
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x9F
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm3, dword ptr [edi + 0xb0]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xDA
        // mulss xmm3, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x97
        _emit 0xBC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm2, dword ptr [edi + 0xbc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD1
        // mulss xmm2, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8F
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [edi + 0xc8]
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
        _emit 0x18
        // movss dword ptr [esp + 0x18], xmm3
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x89
        _emit 0x56
        _emit 0x1C
        // mov dword ptr [esi + 0x1c], edx
        _emit 0x89
        _emit 0x46
        _emit 0x20
        // mov dword ptr [esi + 0x20], eax
        _emit 0x89
        _emit 0x4E
        _emit 0x24
        // mov dword ptr [esi + 0x24], ecx
        _emit 0x66
        _emit 0x8B
        _emit 0x97
        _emit 0x7C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dx, word ptr [edi + 0x17c]
        _emit 0x66
        _emit 0x89
        _emit 0x56
        _emit 0x28
        // mov word ptr [esi + 0x28], dx
        _emit 0x66
        _emit 0xFF
        _emit 0x87
        _emit 0x7C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // inc word ptr [edi + 0x17c]
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x5F
        // pop edi
        _emit 0x66
        _emit 0x89
        _emit 0x46
        _emit 0x2A
        // mov word ptr [esi + 0x2a], ax
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x14
        // add esp, 0x14
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00a94fb0  (1268 bytes)
__declspec(naked) void FUN_00a94fb0()
{
    __asm {
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0xEC
        // mov ebp, esp
        _emit 0x83
        _emit 0xE4
        _emit 0xF0
        // and esp, 0xfffffff0
        _emit 0x83
        _emit 0xEC
        _emit 0x54
        // sub esp, 0x54
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x75
        _emit 0x08
        // mov esi, dword ptr [ebp + 8]
        _emit 0x8B
        _emit 0x46
        _emit 0x14
        // mov eax, dword ptr [esi + 0x14]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], eax
        _emit 0x8B
        _emit 0x4E
        _emit 0x1C
        // mov ecx, dword ptr [esi + 0x1c]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7E
        _emit 0x20
        // mov edi, dword ptr [esi + 0x20]
        _emit 0x8B
        _emit 0x97
        _emit 0x98
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [edi + 0x98]
        _emit 0x2B
        _emit 0x97
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // sub edx, dword ptr [edi + 0x94]
        _emit 0x8B
        _emit 0x9F
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, dword ptr [edi + 0x84]
        _emit 0x2B
        _emit 0x9F
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // sub ebx, dword ptr [edi + 0x80]
        _emit 0xB8
        _emit 0xAB
        _emit 0xAA
        _emit 0xAA
        _emit 0x2A
        // mov eax, 0x2aaaaaab
        _emit 0xF7
        _emit 0xEA
        // imul edx
        _emit 0xD1
        _emit 0xFA
        // sar edx, 1
        _emit 0x8B
        _emit 0xC2
        // mov eax, edx
        _emit 0xC1
        _emit 0xE8
        _emit 0x1F
        // shr eax, 0x1f
        _emit 0x8D
        _emit 0x54
        _emit 0x02
        _emit 0xFF
        // lea edx, [edx + eax - 1]
        _emit 0x8B
        _emit 0x87
        _emit 0xAC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edi + 0xac]
        _emit 0x2B
        _emit 0x87
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // sub eax, dword ptr [edi + 0xa8]
        _emit 0xC1
        _emit 0xFB
        _emit 0x02
        // sar ebx, 2
        _emit 0xC1
        _emit 0xF8
        _emit 0x02
        // sar eax, 2
        _emit 0x48
        // dec eax
        _emit 0x4B
        // dec ebx
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ecx
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], edx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // mov dword ptr [esp + 0x30], eax
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], ebx
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x0F
        _emit 0x8E
        _emit 0x7B
        _emit 0x04
        _emit 0x00
        _emit 0x00
        // jle 0xa9549d
        _emit 0xEB
        _emit 0x04
        // jmp 0xa95028
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x45
        _emit 0x0C
        // mov eax, dword ptr [ebp + 0xc]
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0x12
        // mov edx, dword ptr [edx]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // lea eax, [esp + 0x10]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // lea eax, [esp + 0x10]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4D
        _emit 0x0C
        // mov ecx, dword ptr [ebp + 0xc]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x0F
        _emit 0x84
        _emit 0x56
        _emit 0x04
        _emit 0x00
        _emit 0x00
        // je 0xa9549d
        _emit 0x29
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // sub dword ptr [esp + 0x14], eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x0F
        _emit 0x8E
        _emit 0x35
        _emit 0x04
        _emit 0x00
        _emit 0x00
        // jle 0xa95488
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], eax
        _emit 0xEB
        _emit 0x07
        // jmp 0xa95060
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x41
        _emit 0x08
        // movss xmm0, dword ptr [ecx + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5E
        _emit 0x41
        _emit 0x0C
        // divss xmm0, dword ptr [ecx + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // movss dword ptr [esp + 0x28], xmm0
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x75
        _emit 0x0C
        // jne 0xa95088
        _emit 0x8B
        _emit 0x87
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edi + 0x80]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x00
        // movss xmm0, dword ptr [eax]
        _emit 0xEB
        _emit 0x5C
        // jmp 0xa950e4
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ebx
        _emit 0xDB
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fild dword ptr [esp + 0x1c]
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x7D
        _emit 0x06
        // jge 0xa9509a
        _emit 0xD8
        _emit 0x05
        _emit 0xD0
        _emit 0x4F
        _emit 0x3F
        _emit 0x01
        // fadd dword ptr [0x13f4fd0]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x2C
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // cvttss2si eax, dword ptr [esp + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // movss xmm1, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x97
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [edi + 0x80]
        _emit 0xF3
        _emit 0x0F
        _emit 0x2A
        _emit 0xC0
        // cvtsi2ss xmm0, eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xC8
        // subss xmm1, xmm0
        _emit 0x0F
        _emit 0x2F
        _emit 0x0D
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // comiss xmm1, dword ptr [0x1485378]
        _emit 0x76
        _emit 0x1C
        // jbe 0xa950df
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x14
        _emit 0x82
        // movss xmm2, dword ptr [edx + eax*4]
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
        _emit 0xC2
        // subss xmm0, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC1
        // mulss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC2
        // addss xmm0, xmm2
        _emit 0xEB
        _emit 0x05
        // jmp 0xa950e4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x04
        _emit 0x82
        // movss xmm0, dword ptr [edx + eax*4]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // mov eax, dword ptr [esp + 0x2c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0x50
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0x150]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x44
        // movss dword ptr [esp + 0x44], xmm1
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x75
        _emit 0x54
        // jne 0xa95152
        _emit 0x8B
        _emit 0x87
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edi + 0x94]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x08
        // movss xmm0, dword ptr [eax + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x58
        _emit 0x04
        // movss xmm3, dword ptr [eax + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x20
        // movss xmm4, dword ptr [eax]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // mov eax, dword ptr [esp + 0x30]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xAE
        _emit 0x58
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm5, dword ptr [esi + 0x158]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xB6
        _emit 0x5C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm6, dword ptr [esi + 0x15c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x86
        _emit 0x60
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mulss xmm0, dword ptr [esi + 0x160]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xEC
        // mulss xmm5, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xF3
        // mulss xmm6, xmm3
        _emit 0x0F
        _emit 0x28
        _emit 0xF8
        // movaps xmm7, xmm0
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x0F
        _emit 0x85
        _emit 0x9D
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0xa951de
        _emit 0x8B
        _emit 0x87
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edi + 0xa8]
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x00
        // movss xmm0, dword ptr [eax]
        _emit 0xE9
        _emit 0xE8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jmp 0xa9523a
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], eax
        _emit 0xDB
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fild dword ptr [esp + 0x1c]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x7D
        _emit 0x06
        // jge 0xa95164
        _emit 0xD8
        _emit 0x05
        _emit 0xD0
        _emit 0x4F
        _emit 0x3F
        _emit 0x01
        // fadd dword ptr [0x13f4fd0]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x2C
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // cvttss2si eax, dword ptr [esp + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // movss xmm3, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x97
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [edi + 0x94]
        _emit 0xF3
        _emit 0x0F
        _emit 0x2A
        _emit 0xC0
        // cvtsi2ss xmm0, eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xD8
        // subss xmm3, xmm0
        _emit 0x0F
        _emit 0x2F
        _emit 0x1D
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // comiss xmm3, dword ptr [0x1485378]
        _emit 0x8D
        _emit 0x04
        _emit 0x40
        // lea eax, [eax + eax*2]
        _emit 0x8D
        _emit 0x04
        _emit 0x82
        // lea eax, [edx + eax*4]
        _emit 0x0F
        _emit 0x86
        _emit 0x6D
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jbe 0xa95104
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x0C
        // movss xmm0, dword ptr [eax + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x00
        // subss xmm0, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0x10
        // movss xmm1, dword ptr [eax + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x50
        _emit 0x14
        // movss xmm2, dword ptr [eax + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x48
        _emit 0x04
        // subss xmm1, dword ptr [eax + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x50
        _emit 0x08
        // subss xmm2, dword ptr [eax + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC3
        // mulss xmm0, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x00
        // addss xmm0, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD3
        // mulss xmm2, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCB
        // mulss xmm1, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x58
        _emit 0x04
        // movss xmm3, dword ptr [eax + 4]
        _emit 0x0F
        _emit 0x28
        _emit 0xE0
        // movaps xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x08
        // movss xmm0, dword ptr [eax + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xD9
        // addss xmm3, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC2
        // addss xmm0, xmm2
        _emit 0xE9
        _emit 0x34
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jmp 0xa95112
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], eax
        _emit 0xDB
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fild dword ptr [esp + 0x1c]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x7D
        _emit 0x06
        // jge 0xa951f0
        _emit 0xD8
        _emit 0x05
        _emit 0xD0
        _emit 0x4F
        _emit 0x3F
        _emit 0x01
        // fadd dword ptr [0x13f4fd0]
        _emit 0xDE
        _emit 0xC9
        // fmulp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x2C
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // cvttss2si eax, dword ptr [esp + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // movss xmm1, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x97
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [edi + 0xa8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x2A
        _emit 0xC0
        // cvtsi2ss xmm0, eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xC8
        // subss xmm1, xmm0
        _emit 0x0F
        _emit 0x2F
        _emit 0x0D
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // comiss xmm1, dword ptr [0x1485378]
        _emit 0x76
        _emit 0x1C
        // jbe 0xa95235
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x14
        _emit 0x82
        // movss xmm2, dword ptr [edx + eax*4]
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
        _emit 0xC2
        // subss xmm0, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC1
        // mulss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC2
        // addss xmm0, xmm2
        _emit 0xEB
        _emit 0x05
        // jmp 0xa9523a
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x04
        _emit 0x82
        // movss xmm0, dword ptr [edx + eax*4]
        _emit 0xF6
        _emit 0x86
        _emit 0xCC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x02
        // test byte ptr [esi + 0xcc], 2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0x54
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0x154]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x51
        _emit 0x10
        // movss xmm2, dword ptr [ecx + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x61
        _emit 0x14
        // movss xmm4, dword ptr [ecx + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x59
        _emit 0x18
        // movss xmm3, dword ptr [ecx + 0x18]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // movss dword ptr [esp + 0x40], xmm1
        _emit 0x0F
        _emit 0x84
        _emit 0xBF
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xa95327
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0xF8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0xf8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0xEC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0xec]
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
        _emit 0x0F
        _emit 0x28
        _emit 0xCA
        // movaps xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x8E
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mulss xmm1, dword ptr [esi + 0xe0]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC1
        // addss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0xf0]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x54
        // movss dword ptr [esp + 0x54], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0xFC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0xfc]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x54
        // mov eax, dword ptr [esp + 0x54]
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
        _emit 0xE4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0xe4]
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
        _emit 0xF4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0xf4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x58
        // movss dword ptr [esp + 0x58], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0x100]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x58
        // mov ecx, dword ptr [esp + 0x58]
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
        _emit 0xE8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0xe8]
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
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x5C
        // movss dword ptr [esp + 0x5c], xmm0
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x5C
        // mov edx, dword ptr [esp + 0x5c]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // mov dword ptr [esp + 0x48], eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x54
        _emit 0x24
        _emit 0x48
        // movss xmm2, dword ptr [esp + 0x48]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x4C
        // mov dword ptr [esp + 0x4c], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x64
        _emit 0x24
        _emit 0x4C
        // movss xmm4, dword ptr [esp + 0x4c]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x50
        // mov dword ptr [esp + 0x50], edx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5C
        _emit 0x24
        _emit 0x50
        // movss xmm3, dword ptr [esp + 0x50]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0xdc]
        _emit 0x8B
        _emit 0x45
        _emit 0x10
        // mov eax, dword ptr [ebp + 0x10]
        _emit 0x0F
        _emit 0xB6
        _emit 0x00
        // movzx eax, byte ptr [eax]
        _emit 0x03
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // add eax, dword ptr [esp + 0xc]
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCA
        // mulss xmm1, xmm2
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
        _emit 0xD0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm3, dword ptr [esi + 0xd0]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xD9
        // addss xmm3, xmm1
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
        _emit 0x59
        _emit 0xD4
        // mulss xmm2, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xCA
        // addss xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x4C
        // movss dword ptr [esp + 0x4c], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0xd8]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x4C
        // mov edx, dword ptr [esp + 0x4c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC8
        // addss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x5C
        _emit 0x24
        _emit 0x48
        // movss dword ptr [esp + 0x48], xmm3
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // mov ecx, dword ptr [esp + 0x48]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x50
        // movss dword ptr [esp + 0x50], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0xdc]
        _emit 0x89
        _emit 0x08
        // mov dword ptr [eax], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x50
        // mov ecx, dword ptr [esp + 0x50]
        _emit 0x89
        _emit 0x50
        _emit 0x04
        // mov dword ptr [eax + 4], edx
        _emit 0x89
        _emit 0x48
        _emit 0x08
        // mov dword ptr [eax + 8], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x6C
        _emit 0x24
        _emit 0x34
        // movss dword ptr [esp + 0x34], xmm5
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x5F
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // maxss xmm0, dword ptr [esp + 0x34]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x05
        _emit 0x9C
        _emit 0x86
        _emit 0x45
        _emit 0x01
        // mulss xmm0, dword ptr [0x145869c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5D
        _emit 0x05
        _emit 0x9C
        _emit 0x86
        _emit 0x45
        _emit 0x01
        // minss xmm0, dword ptr [0x145869c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x2D
        _emit 0xC0
        // cvtss2si eax, xmm0
        _emit 0x8A
        _emit 0xC8
        // mov cl, al
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x74
        _emit 0x24
        _emit 0x38
        // movss dword ptr [esp + 0x38], xmm6
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x5F
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // maxss xmm0, dword ptr [esp + 0x38]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x05
        _emit 0x9C
        _emit 0x86
        _emit 0x45
        _emit 0x01
        // mulss xmm0, dword ptr [0x145869c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5D
        _emit 0x05
        _emit 0x9C
        _emit 0x86
        _emit 0x45
        _emit 0x01
        // minss xmm0, dword ptr [0x145869c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x2D
        _emit 0xC0
        // cvtss2si eax, xmm0
        _emit 0x8A
        _emit 0xD0
        // mov dl, al
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x7C
        _emit 0x24
        _emit 0x3C
        // movss dword ptr [esp + 0x3c], xmm7
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x5F
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        // maxss xmm0, dword ptr [esp + 0x3c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x05
        _emit 0x9C
        _emit 0x86
        _emit 0x45
        _emit 0x01
        // mulss xmm0, dword ptr [0x145869c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5D
        _emit 0x05
        _emit 0x9C
        _emit 0x86
        _emit 0x45
        _emit 0x01
        // minss xmm0, dword ptr [0x145869c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x2D
        _emit 0xC0
        // cvtss2si eax, xmm0
        _emit 0x8A
        _emit 0xD8
        // mov bl, al
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x5F
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // maxss xmm0, dword ptr [esp + 0x40]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x05
        _emit 0x9C
        _emit 0x86
        _emit 0x45
        _emit 0x01
        // mulss xmm0, dword ptr [0x145869c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5D
        _emit 0x05
        _emit 0x9C
        _emit 0x86
        _emit 0x45
        _emit 0x01
        // minss xmm0, dword ptr [0x145869c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x2D
        _emit 0xC0
        // cvtss2si eax, xmm0
        _emit 0x0F
        _emit 0xB6
        _emit 0xC0
        // movzx eax, al
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x4C
        _emit 0x24
        _emit 0x44
        // mulss xmm1, dword ptr [esp + 0x44]
        _emit 0xC1
        _emit 0xE0
        _emit 0x08
        // shl eax, 8
        _emit 0x0F
        _emit 0xB6
        _emit 0xC9
        // movzx ecx, cl
        _emit 0x0B
        _emit 0xC1
        // or eax, ecx
        _emit 0xC1
        _emit 0xE0
        _emit 0x08
        // shl eax, 8
        _emit 0x0F
        _emit 0xB6
        _emit 0xD2
        // movzx edx, dl
        _emit 0x0B
        _emit 0xC2
        // or eax, edx
        _emit 0x0F
        _emit 0xB6
        _emit 0xCB
        // movzx ecx, bl
        _emit 0xC1
        _emit 0xE0
        _emit 0x08
        // shl eax, 8
        _emit 0x0B
        _emit 0xC1
        // or eax, ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // mov ecx, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        _emit 0x8B
        _emit 0x45
        _emit 0x10
        // mov eax, dword ptr [ebp + 0x10]
        _emit 0x0F
        _emit 0xB6
        _emit 0x50
        _emit 0x01
        // movzx edx, byte ptr [eax + 1]
        _emit 0x89
        _emit 0x1C
        _emit 0x0A
        // mov dword ptr [edx + ecx], ebx
        _emit 0x0F
        _emit 0xB6
        _emit 0x50
        _emit 0x02
        // movzx edx, byte ptr [eax + 2]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov eax, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // mov ebx, dword ptr [esp + 0x24]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x0C
        _emit 0x02
        // movss dword ptr [edx + eax], xmm1
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x18
        // mov edx, dword ptr [esp + 0x18]
        _emit 0x01
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // add dword ptr [esp + 0xc], ecx
        _emit 0x83
        _emit 0x6C
        _emit 0x24
        _emit 0x20
        _emit 0x01
        // sub dword ptr [esp + 0x20], 1
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], eax
        _emit 0x0F
        _emit 0x85
        _emit 0xD8
        _emit 0xFB
        _emit 0xFF
        _emit 0xFF
        // jne 0xa95060
        _emit 0x8B
        _emit 0x4D
        _emit 0x0C
        // mov ecx, dword ptr [ebp + 0xc]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x08
        // mov eax, dword ptr [edx + 8]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x83
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        _emit 0x00
        // cmp dword ptr [esp + 0x14], 0
        _emit 0x0F
        _emit 0x8F
        _emit 0x87
        _emit 0xFB
        _emit 0xFF
        _emit 0xFF
        // jg 0xa95024
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x8B
        _emit 0xE5
        // mov esp, ebp
        _emit 0x5D
        // pop ebp
        _emit 0xC3
        // ret 
    }
}
