// Slice s01202ca0: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_012016f0();
extern "C" void FUN_01202020();
extern "C" void FUN_01202160();

// @ 0x01202ca0  (810 bytes)
__declspec(naked) void FUN_01202ca0()
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
        _emit 0x14
        // sub esp, 0x14
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x75
        _emit 0x08
        // mov esi, dword ptr [ebp + 8]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0x8B
        _emit 0x4D
        _emit 0x0C
        // mov ecx, dword ptr [ebp + 0xc]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x5E
        _emit 0x20
        // lea ebx, [esi + 0x20]
        _emit 0x53
        // push ebx
        _emit 0x8D
        _emit 0x46
        _emit 0x30
        // lea eax, [esi + 0x30]
        _emit 0x50
        // push eax
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_01202160
        _emit 0x8B
        _emit 0x55
        _emit 0x0C
        // mov edx, dword ptr [ebp + 0xc]
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x46
        _emit 0x10
        // lea eax, [esi + 0x10]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_01202020
        _emit 0x0F
        _emit 0x28
        _emit 0x06
        // movaps xmm0, xmmword ptr [esi]
        _emit 0x0F
        _emit 0x28
        _emit 0x0B
        // movaps xmm1, xmmword ptr [ebx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x2D
        _emit 0x64
        _emit 0x10
        _emit 0x47
        _emit 0x01
        // movss xmm5, dword ptr [0x1471064]
        _emit 0x0F
        _emit 0x5C
        _emit 0xC8
        // subps xmm1, xmm0
        _emit 0xB8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 1
        _emit 0x89
        _emit 0x86
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x88], eax
        _emit 0xC7
        _emit 0x86
        _emit 0x8C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x8c], 3
        _emit 0x89
        _emit 0xBE
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x80], edi
        _emit 0x0F
        _emit 0x29
        _emit 0x4E
        _emit 0x40
        // movaps xmmword ptr [esi + 0x40], xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0x46
        _emit 0x40
        // movaps xmm0, xmmword ptr [esi + 0x40]
        _emit 0x0F
        _emit 0x59
        _emit 0xC0
        // mulps xmm0, xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xC8
        _emit 0x02
        // shufps xmm1, xmm0, 2
        _emit 0x0F
        _emit 0x28
        _emit 0xD0
        // movaps xmm2, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xD0
        _emit 0x01
        // shufps xmm2, xmm0, 1
        _emit 0x0F
        _emit 0x58
        _emit 0xD1
        // addps xmm2, xmm1
        _emit 0x0F
        _emit 0x58
        _emit 0xC2
        // addps xmm0, xmm2
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xC8
        _emit 0x00
        // shufps xmm1, xmm0, 0
        _emit 0x0F
        _emit 0x29
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // movaps xmmword ptr [esp + 0x10], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // movss xmm0, dword ptr [esp + 0x10]
        _emit 0x0F
        _emit 0x2F
        _emit 0x05
        _emit 0x84
        _emit 0x89
        _emit 0x4F
        _emit 0x01
        // comiss xmm0, dword ptr [0x14f8984]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x70
        // movss dword ptr [esi + 0x70], xmm0
        _emit 0x0F
        _emit 0x86
        _emit 0x92
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jbe 0x1202dd5
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
        _emit 0x10
        _emit 0xC0
        // movss xmm0, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xC0
        _emit 0x00
        // shufps xmm0, xmm0, 0
        _emit 0x0F
        _emit 0x52
        _emit 0xC8
        // rsqrtps xmm1, xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0xF1
        // movaps xmm6, xmm1
        _emit 0x0F
        _emit 0x59
        _emit 0xF1
        // mulps xmm6, xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0xD1
        // movaps xmm2, xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0xF8
        // movaps xmm7, xmm0
        _emit 0x0F
        _emit 0x59
        _emit 0xFE
        // mulps xmm7, xmm6
        _emit 0x0F
        _emit 0xC6
        _emit 0xDB
        _emit 0x00
        // shufps xmm3, xmm3, 0
        _emit 0x0F
        _emit 0x28
        _emit 0xF3
        // movaps xmm6, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xE5
        // movss xmm4, xmm5
        _emit 0x0F
        _emit 0xC6
        _emit 0xE4
        _emit 0x00
        // shufps xmm4, xmm4, 0
        _emit 0x0F
        _emit 0x59
        _emit 0xD4
        // mulps xmm2, xmm4
        _emit 0x0F
        _emit 0x5C
        _emit 0xF7
        // subps xmm6, xmm7
        _emit 0x0F
        _emit 0x59
        _emit 0xF2
        // mulps xmm6, xmm2
        _emit 0x0F
        _emit 0x58
        _emit 0xCE
        // addps xmm1, xmm6
        _emit 0x0F
        _emit 0x28
        _emit 0xD1
        // movaps xmm2, xmm1
        _emit 0x0F
        _emit 0x59
        _emit 0xD4
        // mulps xmm2, xmm4
        _emit 0x0F
        _emit 0x28
        _emit 0xE1
        // movaps xmm4, xmm1
        _emit 0x0F
        _emit 0x59
        _emit 0xE1
        // mulps xmm4, xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0xF0
        // movaps xmm6, xmm0
        _emit 0x0F
        _emit 0x59
        _emit 0xF4
        // mulps xmm6, xmm4
        _emit 0x0F
        _emit 0x5C
        _emit 0xDE
        // subps xmm3, xmm6
        _emit 0x0F
        _emit 0x59
        _emit 0xDA
        // mulps xmm3, xmm2
        _emit 0x0F
        _emit 0x58
        _emit 0xCB
        // addps xmm1, xmm3
        _emit 0x0F
        _emit 0x28
        _emit 0xD0
        // movaps xmm2, xmm0
        _emit 0x0F
        _emit 0x59
        _emit 0xD1
        // mulps xmm2, xmm1
        _emit 0x0F
        _emit 0x57
        _emit 0xC9
        // xorps xmm1, xmm1
        _emit 0x0F
        _emit 0xC2
        _emit 0xC8
        _emit 0x00
        // cmpeqps xmm1, xmm0
        _emit 0x0F
        _emit 0x55
        _emit 0xCA
        // andnps xmm1, xmm2
        _emit 0x0F
        _emit 0x29
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // movaps xmmword ptr [esp + 0x10], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // movss xmm0, dword ptr [esp + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x70
        // movss dword ptr [esi + 0x70], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xC0
        // movss xmm0, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xC0
        _emit 0x00
        // shufps xmm0, xmm0, 0
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xC8
        _emit 0x00
        // shufps xmm1, xmm0, 0
        _emit 0x0F
        _emit 0x28
        _emit 0x46
        _emit 0x40
        // movaps xmm0, xmmword ptr [esi + 0x40]
        _emit 0x0F
        _emit 0x5E
        _emit 0xC1
        // divps xmm0, xmm1
        _emit 0x0F
        _emit 0x29
        _emit 0x46
        _emit 0x40
        // movaps xmmword ptr [esi + 0x40], xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0x03
        // movaps xmm0, xmmword ptr [ebx]
        _emit 0x0F
        _emit 0x28
        _emit 0x4E
        _emit 0x30
        // movaps xmm1, xmmword ptr [esi + 0x30]
        _emit 0x0F
        _emit 0x5C
        _emit 0xC8
        // subps xmm1, xmm0
        _emit 0x0F
        _emit 0x29
        _emit 0x4E
        _emit 0x50
        // movaps xmmword ptr [esi + 0x50], xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0x46
        _emit 0x50
        // movaps xmm0, xmmword ptr [esi + 0x50]
        _emit 0x0F
        _emit 0x59
        _emit 0xC0
        // mulps xmm0, xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xC8
        _emit 0x02
        // shufps xmm1, xmm0, 2
        _emit 0x0F
        _emit 0x28
        _emit 0xD0
        // movaps xmm2, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xD0
        _emit 0x01
        // shufps xmm2, xmm0, 1
        _emit 0x0F
        _emit 0x58
        _emit 0xD1
        // addps xmm2, xmm1
        _emit 0x0F
        _emit 0x58
        _emit 0xC2
        // addps xmm0, xmm2
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xC8
        _emit 0x00
        // shufps xmm1, xmm0, 0
        _emit 0x0F
        _emit 0x29
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // movaps xmmword ptr [esp + 0x10], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // movss xmm0, dword ptr [esp + 0x10]
        _emit 0x0F
        _emit 0x2F
        _emit 0x05
        _emit 0x84
        _emit 0x89
        _emit 0x4F
        _emit 0x01
        // comiss xmm0, dword ptr [0x14f8984]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x74
        // movss dword ptr [esi + 0x74], xmm0
        _emit 0x0F
        _emit 0x86
        _emit 0x92
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jbe 0x1202eb4
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
        _emit 0x10
        _emit 0xC0
        // movss xmm0, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xC0
        _emit 0x00
        // shufps xmm0, xmm0, 0
        _emit 0x0F
        _emit 0x52
        _emit 0xC8
        // rsqrtps xmm1, xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0xF1
        // movaps xmm6, xmm1
        _emit 0x0F
        _emit 0x59
        _emit 0xF1
        // mulps xmm6, xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0xD1
        // movaps xmm2, xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0xF8
        // movaps xmm7, xmm0
        _emit 0x0F
        _emit 0x59
        _emit 0xFE
        // mulps xmm7, xmm6
        _emit 0x0F
        _emit 0xC6
        _emit 0xDB
        _emit 0x00
        // shufps xmm3, xmm3, 0
        _emit 0x0F
        _emit 0x28
        _emit 0xF3
        // movaps xmm6, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xE5
        // movss xmm4, xmm5
        _emit 0x0F
        _emit 0xC6
        _emit 0xE4
        _emit 0x00
        // shufps xmm4, xmm4, 0
        _emit 0x0F
        _emit 0x59
        _emit 0xD4
        // mulps xmm2, xmm4
        _emit 0x0F
        _emit 0x5C
        _emit 0xF7
        // subps xmm6, xmm7
        _emit 0x0F
        _emit 0x59
        _emit 0xF2
        // mulps xmm6, xmm2
        _emit 0x0F
        _emit 0x58
        _emit 0xCE
        // addps xmm1, xmm6
        _emit 0x0F
        _emit 0x28
        _emit 0xD1
        // movaps xmm2, xmm1
        _emit 0x0F
        _emit 0x59
        _emit 0xD4
        // mulps xmm2, xmm4
        _emit 0x0F
        _emit 0x28
        _emit 0xE1
        // movaps xmm4, xmm1
        _emit 0x0F
        _emit 0x59
        _emit 0xE1
        // mulps xmm4, xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0xF0
        // movaps xmm6, xmm0
        _emit 0x0F
        _emit 0x59
        _emit 0xF4
        // mulps xmm6, xmm4
        _emit 0x0F
        _emit 0x5C
        _emit 0xDE
        // subps xmm3, xmm6
        _emit 0x0F
        _emit 0x59
        _emit 0xDA
        // mulps xmm3, xmm2
        _emit 0x0F
        _emit 0x58
        _emit 0xCB
        // addps xmm1, xmm3
        _emit 0x0F
        _emit 0x28
        _emit 0xD0
        // movaps xmm2, xmm0
        _emit 0x0F
        _emit 0x59
        _emit 0xD1
        // mulps xmm2, xmm1
        _emit 0x0F
        _emit 0x57
        _emit 0xC9
        // xorps xmm1, xmm1
        _emit 0x0F
        _emit 0xC2
        _emit 0xC8
        _emit 0x00
        // cmpeqps xmm1, xmm0
        _emit 0x0F
        _emit 0x55
        _emit 0xCA
        // andnps xmm1, xmm2
        _emit 0x0F
        _emit 0x29
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // movaps xmmword ptr [esp + 0x10], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // movss xmm0, dword ptr [esp + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x74
        // movss dword ptr [esi + 0x74], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xC0
        // movss xmm0, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xC0
        _emit 0x00
        // shufps xmm0, xmm0, 0
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xC8
        _emit 0x00
        // shufps xmm1, xmm0, 0
        _emit 0x0F
        _emit 0x28
        _emit 0x46
        _emit 0x50
        // movaps xmm0, xmmword ptr [esi + 0x50]
        _emit 0x0F
        _emit 0x5E
        _emit 0xC1
        // divps xmm0, xmm1
        _emit 0x0F
        _emit 0x29
        _emit 0x46
        _emit 0x50
        // movaps xmmword ptr [esi + 0x50], xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0x46
        _emit 0x30
        // movaps xmm0, xmmword ptr [esi + 0x30]
        _emit 0x0F
        _emit 0x28
        _emit 0x0E
        // movaps xmm1, xmmword ptr [esi]
        _emit 0x0F
        _emit 0x5C
        _emit 0xC8
        // subps xmm1, xmm0
        _emit 0x0F
        _emit 0x29
        _emit 0x4E
        _emit 0x60
        // movaps xmmword ptr [esi + 0x60], xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0x46
        _emit 0x60
        // movaps xmm0, xmmword ptr [esi + 0x60]
        _emit 0x0F
        _emit 0x59
        _emit 0xC0
        // mulps xmm0, xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xC8
        _emit 0x02
        // shufps xmm1, xmm0, 2
        _emit 0x0F
        _emit 0x28
        _emit 0xD0
        // movaps xmm2, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xD0
        _emit 0x01
        // shufps xmm2, xmm0, 1
        _emit 0x0F
        _emit 0x58
        _emit 0xD1
        // addps xmm2, xmm1
        _emit 0x0F
        _emit 0x58
        _emit 0xC2
        // addps xmm0, xmm2
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xC8
        _emit 0x00
        // shufps xmm1, xmm0, 0
        _emit 0x0F
        _emit 0x29
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // movaps xmmword ptr [esp + 0x10], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // movss xmm0, dword ptr [esp + 0x10]
        _emit 0x0F
        _emit 0x2F
        _emit 0x05
        _emit 0x84
        _emit 0x89
        _emit 0x4F
        _emit 0x01
        // comiss xmm0, dword ptr [0x14f8984]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x78
        // movss dword ptr [esi + 0x78], xmm0
        _emit 0x0F
        _emit 0x86
        _emit 0x92
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jbe 0x1202f93
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x15
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // movss xmm2, dword ptr [0x1485720]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xC0
        // movss xmm0, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xC0
        _emit 0x00
        // shufps xmm0, xmm0, 0
        _emit 0x0F
        _emit 0x52
        _emit 0xC8
        // rsqrtps xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xDD
        // movss xmm3, xmm5
        _emit 0x0F
        _emit 0x28
        _emit 0xE9
        // movaps xmm5, xmm1
        _emit 0x0F
        _emit 0x59
        _emit 0xE9
        // mulps xmm5, xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0xE1
        // movaps xmm4, xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0xF0
        // movaps xmm6, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xD2
        _emit 0x00
        // shufps xmm2, xmm2, 0
        _emit 0x0F
        _emit 0x59
        _emit 0xF5
        // mulps xmm6, xmm5
        _emit 0x0F
        _emit 0x28
        _emit 0xEA
        // movaps xmm5, xmm2
        _emit 0x0F
        _emit 0xC6
        _emit 0xDB
        _emit 0x00
        // shufps xmm3, xmm3, 0
        _emit 0x0F
        _emit 0x59
        _emit 0xE3
        // mulps xmm4, xmm3
        _emit 0x0F
        _emit 0x5C
        _emit 0xEE
        // subps xmm5, xmm6
        _emit 0x0F
        _emit 0x59
        _emit 0xEC
        // mulps xmm5, xmm4
        _emit 0x0F
        _emit 0x58
        _emit 0xCD
        // addps xmm1, xmm5
        _emit 0x0F
        _emit 0x28
        _emit 0xE1
        // movaps xmm4, xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0xE8
        // movaps xmm5, xmm0
        _emit 0x0F
        _emit 0x59
        _emit 0xE3
        // mulps xmm4, xmm3
        _emit 0x0F
        _emit 0x28
        _emit 0xD9
        // movaps xmm3, xmm1
        _emit 0x0F
        _emit 0x59
        _emit 0xD9
        // mulps xmm3, xmm1
        _emit 0x0F
        _emit 0x59
        _emit 0xEB
        // mulps xmm5, xmm3
        _emit 0x0F
        _emit 0x5C
        _emit 0xD5
        // subps xmm2, xmm5
        _emit 0x0F
        _emit 0x59
        _emit 0xD4
        // mulps xmm2, xmm4
        _emit 0x0F
        _emit 0x58
        _emit 0xCA
        // addps xmm1, xmm2
        _emit 0x0F
        _emit 0x28
        _emit 0xD0
        // movaps xmm2, xmm0
        _emit 0x0F
        _emit 0x59
        _emit 0xD1
        // mulps xmm2, xmm1
        _emit 0x0F
        _emit 0x57
        _emit 0xC9
        // xorps xmm1, xmm1
        _emit 0x0F
        _emit 0xC2
        _emit 0xC8
        _emit 0x00
        // cmpeqps xmm1, xmm0
        _emit 0x0F
        _emit 0x55
        _emit 0xCA
        // andnps xmm1, xmm2
        _emit 0x0F
        _emit 0x29
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // movaps xmmword ptr [esp + 0x10], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // movss xmm0, dword ptr [esp + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x78
        // movss dword ptr [esi + 0x78], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xC0
        // movss xmm0, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xC0
        _emit 0x00
        // shufps xmm0, xmm0, 0
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0x0F
        _emit 0xC6
        _emit 0xC8
        _emit 0x00
        // shufps xmm1, xmm0, 0
        _emit 0x0F
        _emit 0x28
        _emit 0x46
        _emit 0x60
        // movaps xmm0, xmmword ptr [esi + 0x60]
        _emit 0x0F
        _emit 0x5E
        _emit 0xC1
        // divps xmm0, xmm1
        _emit 0x0F
        _emit 0x29
        _emit 0x46
        _emit 0x60
        // movaps xmmword ptr [esi + 0x60], xmm0
        _emit 0x8B
        _emit 0x4F
        _emit 0x50
        // mov ecx, dword ptr [edi + 0x50]
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x4E
        _emit 0x7C
        // mov dword ptr [esi + 0x7c], ecx
        _emit 0xC7
        _emit 0x86
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xF0
        _emit 0x23
        _emit 0x20
        _emit 0x01
        // mov dword ptr [esi + 0x90], 0x12023f0
        _emit 0xC7
        _emit 0x86
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x60
        _emit 0x29
        _emit 0x20
        _emit 0x01
        // mov dword ptr [esi + 0x94], 0x1202960
        _emit 0xC7
        _emit 0x86
        _emit 0x98
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xF0
        _emit 0x2A
        _emit 0x20
        _emit 0x01
        // mov dword ptr [esi + 0x98], 0x1202af0
        _emit 0xC7
        _emit 0x86
        _emit 0x9C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x20
        _emit 0xB2
        _emit 0x1F
        _emit 0x01
        // mov dword ptr [esi + 0x9c], 0x11fb220
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x8B
        _emit 0xE5
        // mov esp, ebp
        _emit 0x5D
        // pop ebp
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x01202fd0  (229 bytes)
__declspec(naked) void FUN_01202fd0()
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
        _emit 0x81
        _emit 0xEC
        _emit 0xFC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // sub esp, 0xfc
        _emit 0x0F
        _emit 0x28
        _emit 0x01
        // movaps xmm0, xmmword ptr [ecx]
        _emit 0x0F
        _emit 0x29
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // movaps xmmword ptr [esp + 0xc], xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0x41
        _emit 0x10
        // movaps xmm0, xmmword ptr [ecx + 0x10]
        _emit 0x56
        // push esi
        _emit 0x0F
        _emit 0x29
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // movaps xmmword ptr [esp + 0x20], xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0x41
        _emit 0x20
        // movaps xmm0, xmmword ptr [ecx + 0x20]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // lea eax, [esp + 0x20]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // lea ecx, [esp + 0x14]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // lea ecx, [esp + 0x48]
        _emit 0x0F
        _emit 0x29
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // movaps xmmword ptr [esp + 0x38], xmm0
        call FUN_012016f0
        _emit 0x0F
        _emit 0x28
        _emit 0x00
        // movaps xmm0, xmmword ptr [eax]
        _emit 0x8B
        _emit 0x75
        _emit 0x10
        // mov esi, dword ptr [ebp + 0x10]
        _emit 0x0F
        _emit 0x29
        _emit 0x46
        _emit 0x10
        // movaps xmmword ptr [esi + 0x10], xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0x40
        _emit 0x10
        // movaps xmm0, xmmword ptr [eax + 0x10]
        _emit 0x0F
        _emit 0x29
        _emit 0x46
        _emit 0x20
        // movaps xmmword ptr [esi + 0x20], xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0x40
        _emit 0x20
        // movaps xmm0, xmmword ptr [eax + 0x20]
        _emit 0x0F
        _emit 0x29
        _emit 0x46
        _emit 0x30
        // movaps xmmword ptr [esi + 0x30], xmm0
        _emit 0x8B
        _emit 0x50
        _emit 0x30
        // mov edx, dword ptr [eax + 0x30]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // lea eax, [esp + 0x30]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // lea ecx, [esp + 0x24]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x8C
        _emit 0x24
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [esp + 0x88]
        _emit 0x89
        _emit 0x56
        _emit 0x40
        // mov dword ptr [esi + 0x40], edx
        call FUN_012016f0
        _emit 0x0F
        _emit 0x28
        _emit 0x00
        // movaps xmm0, xmmword ptr [eax]
        _emit 0x0F
        _emit 0x29
        _emit 0x46
        _emit 0x50
        // movaps xmmword ptr [esi + 0x50], xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0x40
        _emit 0x10
        // movaps xmm0, xmmword ptr [eax + 0x10]
        _emit 0x0F
        _emit 0x29
        _emit 0x46
        _emit 0x60
        // movaps xmmword ptr [esi + 0x60], xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0x40
        _emit 0x20
        // movaps xmm0, xmmword ptr [eax + 0x20]
        _emit 0x0F
        _emit 0x29
        _emit 0x46
        _emit 0x70
        // movaps xmmword ptr [esi + 0x70], xmm0
        _emit 0x8B
        _emit 0x50
        _emit 0x30
        // mov edx, dword ptr [eax + 0x30]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // lea eax, [esp + 0x10]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // lea ecx, [esp + 0x34]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x8C
        _emit 0x24
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [esp + 0xc8]
        _emit 0x89
        _emit 0x96
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x80], edx
        call FUN_012016f0
        _emit 0x0F
        _emit 0x28
        _emit 0x00
        // movaps xmm0, xmmword ptr [eax]
        _emit 0x0F
        _emit 0x29
        _emit 0x86
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movaps xmmword ptr [esi + 0x90], xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0x40
        _emit 0x10
        // movaps xmm0, xmmword ptr [eax + 0x10]
        _emit 0x0F
        _emit 0x29
        _emit 0x86
        _emit 0xA0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movaps xmmword ptr [esi + 0xa0], xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0x40
        _emit 0x20
        // movaps xmm0, xmmword ptr [eax + 0x20]
        _emit 0x0F
        _emit 0x29
        _emit 0x86
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movaps xmmword ptr [esi + 0xb0], xmm0
        _emit 0x8B
        _emit 0x50
        _emit 0x30
        // mov edx, dword ptr [eax + 0x30]
        _emit 0x89
        _emit 0x96
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xc0], edx
        _emit 0xC7
        _emit 0x86
        _emit 0x30
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x130], 3
        _emit 0xB8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 1
        _emit 0x5E
        // pop esi
        _emit 0x8B
        _emit 0xE5
        // mov esp, ebp
        _emit 0x5D
        // pop ebp
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
    }
}

// @ 0x012030c0  (66 bytes)
__declspec(naked) void FUN_012030c0()
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
        _emit 0x30
        // sub esp, 0x30
        _emit 0x0F
        _emit 0x28
        _emit 0x08
        // movaps xmm1, xmmword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0xBC
        _emit 0xB1
        _emit 0x3E
        _emit 0x01
        // movss xmm0, dword ptr [0x13eb1bc]
        _emit 0x0F
        _emit 0xC6
        _emit 0xC0
        _emit 0x00
        // shufps xmm0, xmm0, 0
        _emit 0x0F
        _emit 0x59
        _emit 0xC1
        // mulps xmm0, xmm1
        _emit 0x0F
        _emit 0x5F
        _emit 0xC1
        // maxps xmm0, xmm1
        _emit 0x0F
        _emit 0x29
        _emit 0x04
        _emit 0x24
        // movaps xmmword ptr [esp], xmm0
        _emit 0x0F
        _emit 0x29
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // movaps xmmword ptr [esp + 0x20], xmm0
        _emit 0x0F
        _emit 0x29
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // movaps xmmword ptr [esp + 0x10], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // movss xmm0, dword ptr [esp + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // addss xmm0, dword ptr [esp + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // addss xmm0, dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0xE5
        // mov esp, ebp
        _emit 0x5D
        // pop ebp
        _emit 0xC3
        // ret 
    }
}
