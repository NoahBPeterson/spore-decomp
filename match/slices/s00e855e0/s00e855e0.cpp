// Slice s00e855e0: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00e853c0();
extern "C" void FUN_00e855e0();
extern "C" void FUN_011e073e();

// @ 0x00e855e0  (1144 bytes)
__declspec(naked) void FUN_00e855e0()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x48
        // sub esp, 0x48
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x4C
        // mov ecx, dword ptr [esp + 0x4c]
        _emit 0x8D
        _emit 0x41
        _emit 0xFF
        // lea eax, [ecx - 1]
        _emit 0x55
        // push ebp
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // mov dword ptr [esp + 0x44], eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x7D
        _emit 0x0E
        // jge 0xe85603
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x44
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x44], 0
        _emit 0x8B
        _emit 0xE8
        // mov ebp, eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // mov eax, dword ptr [esp + 0x44]
        _emit 0x3B
        _emit 0xE8
        // cmp ebp, eax
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x04
        // mov dword ptr [esp + 4], ebp
        _emit 0x0F
        _emit 0x8F
        _emit 0x44
        _emit 0x04
        _emit 0x00
        _emit 0x00
        // jg 0xe85a53
        _emit 0x53
        // push ebx
        _emit 0xD9
        _emit 0x05
        _emit 0xB8
        _emit 0xC4
        _emit 0x3E
        _emit 0x01
        // fld dword ptr [0x13ec4b8]
        _emit 0x56
        // push esi
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x0D
        _emit 0xB0
        _emit 0xB8
        _emit 0x3E
        _emit 0x01
        // movss xmm1, dword ptr [0x13eb8b0]
        _emit 0x0F
        _emit 0x57
        _emit 0xD2
        // xorps xmm2, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x1D
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // movss xmm3, dword ptr [0x1485720]
        _emit 0x8D
        _emit 0x34
        _emit 0x8D
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esi, [ecx*4]
        _emit 0x8D
        _emit 0x56
        _emit 0x04
        // lea edx, [esi + 4]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x50
        // mov dword ptr [esp + 0x50], edx
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x5C
        // mov edx, dword ptr [esp + 0x5c]
        _emit 0x8D
        _emit 0x1C
        _emit 0xAA
        // lea ebx, [edx + ebp*4]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x50
        // mov ebx, dword ptr [esp + 0x50]
        _emit 0x0F
        _emit 0xAF
        _emit 0xDD
        // imul ebx, ebp
        _emit 0x8B
        _emit 0xC5
        // mov eax, ebp
        _emit 0x0F
        _emit 0xAF
        _emit 0xC1
        // imul eax, ecx
        _emit 0x03
        _emit 0xDA
        // add ebx, edx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x44
        // mov dword ptr [esp + 0x44], ebx
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x1C
        _emit 0x29
        // lea ebx, [ecx + ebp]
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x5C
        // mov dword ptr [esp + 0x5c], eax
        _emit 0x8D
        _emit 0x1C
        _emit 0x9A
        // lea ebx, [edx + ebx*4]
        _emit 0x8D
        _emit 0x04
        _emit 0x82
        // lea eax, [edx + eax*4]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ebx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x4C
        // mov dword ptr [esp + 0x4c], eax
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x48
        // mov ebx, dword ptr [esp + 0x48]
        _emit 0xD9
        _emit 0x03
        // fld dword ptr [ebx]
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x44
        // fst dword ptr [esp + 0x44]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xDB
        _emit 0xF1
        // fcomi st(1)
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0x76
        _emit 0x2D
        // jbe 0xe856ae
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x0F
        _emit 0x8E
        _emit 0x90
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // jle 0xe85a19
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x4C
        // mov eax, dword ptr [esp + 0x4c]
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov ebx, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x13
        // movss dword ptr [ebx], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x10
        // movss dword ptr [eax], xmm2
        _emit 0x83
        _emit 0xC0
        _emit 0x04
        // add eax, 4
        _emit 0x03
        _emit 0xDE
        // add ebx, esi
        _emit 0x83
        _emit 0xEF
        _emit 0x01
        // sub edi, 1
        _emit 0x75
        _emit 0xEE
        // jne 0xe85693
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x5C
        // mov edi, dword ptr [esp + 0x5c]
        _emit 0xE9
        _emit 0x6B
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // jmp 0xe85a19
        _emit 0x0F
        _emit 0x28
        _emit 0xC3
        // movaps xmm0, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x5E
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // divss xmm0, dword ptr [esp + 0x44]
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x83
        _emit 0xF9
        _emit 0x04
        // cmp ecx, 4
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x03
        // movss dword ptr [ebx], xmm0
        _emit 0x7C
        _emit 0x76
        // jl 0xe85738
        _emit 0x3B
        _emit 0xC5
        // cmp eax, ebp
        _emit 0x74
        _emit 0x16
        // je 0xe856dc
        _emit 0x8D
        _emit 0x34
        _emit 0x07
        // lea esi, [edi + eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x24
        _emit 0xB2
        // movss xmm4, dword ptr [edx + esi*4]
        _emit 0x8D
        _emit 0x34
        _emit 0xB2
        // lea esi, [edx + esi*4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE0
        // mulss xmm4, xmm0
        _emit 0x0F
        _emit 0x57
        _emit 0xE1
        // xorps xmm4, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x26
        // movss dword ptr [esi], xmm4
        _emit 0x8D
        _emit 0x58
        _emit 0x02
        // lea ebx, [eax + 2]
        _emit 0x8D
        _emit 0x73
        _emit 0xFF
        // lea esi, [ebx - 1]
        _emit 0x3B
        _emit 0xF5
        // cmp esi, ebp
        _emit 0x74
        _emit 0x15
        // je 0xe856fb
        _emit 0x8D
        _emit 0x34
        _emit 0x07
        // lea esi, [edi + eax]
        _emit 0x8D
        _emit 0x74
        _emit 0xB2
        _emit 0x04
        // lea esi, [edx + esi*4 + 4]
        _emit 0x0F
        _emit 0x28
        _emit 0xE0
        // movaps xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x26
        // mulss xmm4, dword ptr [esi]
        _emit 0x0F
        _emit 0x57
        _emit 0xE1
        // xorps xmm4, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x26
        // movss dword ptr [esi], xmm4
        _emit 0x3B
        _emit 0xDD
        // cmp ebx, ebp
        _emit 0x74
        _emit 0x15
        // je 0xe85714
        _emit 0x8D
        _emit 0x34
        _emit 0x07
        // lea esi, [edi + eax]
        _emit 0x8D
        _emit 0x74
        _emit 0xB2
        _emit 0x08
        // lea esi, [edx + esi*4 + 8]
        _emit 0x0F
        _emit 0x28
        _emit 0xE0
        // movaps xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x26
        // mulss xmm4, dword ptr [esi]
        _emit 0x0F
        _emit 0x57
        _emit 0xE1
        // xorps xmm4, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x26
        // movss dword ptr [esi], xmm4
        _emit 0x43
        // inc ebx
        _emit 0x3B
        _emit 0xDD
        // cmp ebx, ebp
        _emit 0x74
        _emit 0x15
        // je 0xe8572e
        _emit 0x8D
        _emit 0x34
        _emit 0x07
        // lea esi, [edi + eax]
        _emit 0x8D
        _emit 0x74
        _emit 0xB2
        _emit 0x0C
        // lea esi, [edx + esi*4 + 0xc]
        _emit 0x0F
        _emit 0x28
        _emit 0xE0
        // movaps xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x26
        // mulss xmm4, dword ptr [esi]
        _emit 0x0F
        _emit 0x57
        _emit 0xE1
        // xorps xmm4, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x26
        // movss dword ptr [esi], xmm4
        _emit 0x83
        _emit 0xC0
        _emit 0x04
        // add eax, 4
        _emit 0x8D
        _emit 0x71
        _emit 0xFD
        // lea esi, [ecx - 3]
        _emit 0x3B
        _emit 0xC6
        // cmp eax, esi
        _emit 0x7C
        _emit 0x8A
        // jl 0xe856c2
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x7D
        _emit 0x1F
        // jge 0xe8575b
        _emit 0x3B
        _emit 0xC5
        // cmp eax, ebp
        _emit 0x74
        _emit 0x16
        // je 0xe85756
        _emit 0x8D
        _emit 0x34
        _emit 0x07
        // lea esi, [edi + eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x24
        _emit 0xB2
        // movss xmm4, dword ptr [edx + esi*4]
        _emit 0x8D
        _emit 0x34
        _emit 0xB2
        // lea esi, [edx + esi*4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE0
        // mulss xmm4, xmm0
        _emit 0x0F
        _emit 0x57
        _emit 0xE1
        // xorps xmm4, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x26
        // movss dword ptr [esi], xmm4
        _emit 0x40
        // inc eax
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x7C
        _emit 0xE1
        // jl 0xe8573c
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0x83
        _emit 0xF9
        _emit 0x04
        // cmp ecx, 4
        _emit 0x0F
        _emit 0x8C
        _emit 0xA7
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jl 0xe8580d
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov ebx, dword ptr [esp + 0x18]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ebx
        _emit 0x8B
        _emit 0xC1
        // mov eax, ecx
        _emit 0x8D
        _emit 0x5C
        _emit 0x4D
        _emit 0x00
        // lea ebx, [ebp + ecx*2]
        _emit 0xC1
        _emit 0xE0
        _emit 0x04
        // shl eax, 4
        _emit 0x03
        _emit 0xD9
        // add ebx, ecx
        _emit 0x8D
        _emit 0x1C
        _emit 0x9A
        // lea ebx, [edx + ebx*4]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], ebx
        _emit 0x8D
        _emit 0x5C
        _emit 0x4D
        _emit 0x00
        // lea ebx, [ebp + ecx*2]
        _emit 0x8D
        _emit 0x1C
        _emit 0x9A
        // lea ebx, [edx + ebx*4]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov ebx, dword ptr [esp + 0x1c]
        _emit 0x8D
        _emit 0x7E
        _emit 0x02
        // lea edi, [esi + 2]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], ebx
        _emit 0x3B
        _emit 0xF5
        // cmp esi, ebp
        _emit 0x74
        _emit 0x10
        // je 0xe857aa
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // mov ebx, dword ptr [esp + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x23
        // movss xmm4, dword ptr [ebx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE0
        // mulss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x23
        // movss dword ptr [ebx], xmm4
        _emit 0x8D
        _emit 0x5F
        _emit 0xFF
        // lea ebx, [edi - 1]
        _emit 0x3B
        _emit 0xDD
        // cmp ebx, ebp
        _emit 0x74
        _emit 0x10
        // je 0xe857c1
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // mov ebx, dword ptr [esp + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x23
        // movss xmm4, dword ptr [ebx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE0
        // mulss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x23
        // movss dword ptr [ebx], xmm4
        _emit 0x3B
        _emit 0xFD
        // cmp edi, ebp
        _emit 0x74
        _emit 0x10
        // je 0xe857d5
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // mov ebx, dword ptr [esp + 0x24]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x23
        // movss xmm4, dword ptr [ebx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE0
        // mulss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x23
        // movss dword ptr [ebx], xmm4
        _emit 0x8D
        _emit 0x5F
        _emit 0x01
        // lea ebx, [edi + 1]
        _emit 0x3B
        _emit 0xDD
        // cmp ebx, ebp
        _emit 0x74
        _emit 0x10
        // je 0xe857ec
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x28
        // mov ebx, dword ptr [esp + 0x28]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x23
        // movss xmm4, dword ptr [ebx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE0
        // mulss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x23
        // movss dword ptr [ebx], xmm4
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // add dword ptr [esp + 0x14], eax
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // add dword ptr [esp + 0x20], eax
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // add dword ptr [esp + 0x24], eax
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // add dword ptr [esp + 0x28], eax
        _emit 0x83
        _emit 0xC6
        _emit 0x04
        // add esi, 4
        _emit 0x8D
        _emit 0x59
        _emit 0xFD
        // lea ebx, [ecx - 3]
        _emit 0x83
        _emit 0xC7
        _emit 0x04
        // add edi, 4
        _emit 0x3B
        _emit 0xF3
        // cmp esi, ebx
        _emit 0x7C
        _emit 0x8D
        // jl 0xe85796
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x5C
        // mov edi, dword ptr [esp + 0x5c]
        _emit 0x3B
        _emit 0xF1
        // cmp esi, ecx
        _emit 0x7D
        _emit 0x27
        // jge 0xe85838
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x0F
        _emit 0xAF
        _emit 0xC1
        // imul eax, ecx
        _emit 0x03
        _emit 0xC5
        // add eax, ebp
        _emit 0x8D
        _emit 0x1C
        _emit 0x82
        // lea ebx, [edx + eax*4]
        _emit 0x3B
        _emit 0xF5
        // cmp esi, ebp
        _emit 0x74
        _emit 0x0B
        // je 0xe8582a
        _emit 0x0F
        _emit 0x28
        _emit 0xE0
        // movaps xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x23
        // mulss xmm4, dword ptr [ebx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x23
        // movss dword ptr [ebx], xmm4
        _emit 0x8D
        _emit 0x04
        _emit 0x8D
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea eax, [ecx*4]
        _emit 0x46
        // inc esi
        _emit 0x03
        _emit 0xD8
        // add ebx, eax
        _emit 0x3B
        _emit 0xF1
        // cmp esi, ecx
        _emit 0x7C
        _emit 0xE3
        // jl 0xe8581b
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x0F
        _emit 0x8E
        _emit 0xD7
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jle 0xe85a19
        _emit 0x8D
        _emit 0x04
        _emit 0x8A
        // lea eax, [edx + ecx*4]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x40
        // mov dword ptr [esp + 0x40], edx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // mov dword ptr [esp + 0x44], eax
        _emit 0x3B
        _emit 0xF5
        // cmp esi, ebp
        _emit 0x0F
        _emit 0x84
        _emit 0xAE
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xe85a03
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x83
        _emit 0xF9
        _emit 0x04
        // cmp ecx, 4
        _emit 0x0F
        _emit 0x8C
        _emit 0x55
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jl 0xe859b5
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x40
        // mov edi, dword ptr [esp + 0x40]
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x18
        // mov edi, dword ptr [esp + 0x18]
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], edi
        _emit 0x8D
        _emit 0x3C
        _emit 0x49
        // lea edi, [ecx + ecx*2]
        _emit 0x8D
        _emit 0x2C
        _emit 0x37
        // lea ebp, [edi + esi]
        _emit 0x8D
        _emit 0x2C
        _emit 0xAA
        // lea ebp, [edx + ebp*4]
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x3C
        // mov dword ptr [esp + 0x3c], ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x10
        // mov ebp, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0xC1
        // mov eax, ecx
        _emit 0xC1
        _emit 0xE0
        _emit 0x04
        // shl eax, 4
        _emit 0x03
        _emit 0xFD
        // add edi, ebp
        _emit 0x8D
        _emit 0x3C
        _emit 0xBA
        // lea edi, [edx + edi*4]
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x38
        // mov dword ptr [esp + 0x38], edi
        _emit 0x8D
        _emit 0x3C
        _emit 0x4E
        // lea edi, [esi + ecx*2]
        _emit 0x8D
        _emit 0x3C
        _emit 0xBA
        // lea edi, [edx + edi*4]
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x34
        // mov dword ptr [esp + 0x34], edi
        _emit 0x8D
        _emit 0x7C
        _emit 0x4D
        _emit 0x00
        // lea edi, [ebp + ecx*2]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x24
        // mov ebp, dword ptr [esp + 0x24]
        _emit 0x8D
        _emit 0x3C
        _emit 0xBA
        // lea edi, [edx + edi*4]
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x30
        // mov dword ptr [esp + 0x30], edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x44
        // mov edi, dword ptr [esp + 0x44]
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x1C
        // mov edi, dword ptr [esp + 0x1c]
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x14], 2
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        // mov edi, dword ptr [esp + 0x10]
        _emit 0x3B
        _emit 0xDF
        // cmp ebx, edi
        _emit 0x74
        _emit 0x25
        // je 0xe858ed
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x5C
        // mov edi, dword ptr [esp + 0x5c]
        _emit 0x03
        _emit 0xFE
        // add edi, esi
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x24
        _emit 0xBA
        // movss xmm4, dword ptr [edx + edi*4]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x28
        // mov edi, dword ptr [esp + 0x28]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5E
        _emit 0xE0
        // divss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x27
        // mulss xmm4, dword ptr [edi]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x65
        _emit 0x00
        // addss xmm4, dword ptr [ebp]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        // mov edi, dword ptr [esp + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x65
        _emit 0x00
        // movss dword ptr [ebp], xmm4
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x14
        // mov ebp, dword ptr [esp + 0x14]
        _emit 0x4D
        // dec ebp
        _emit 0x3B
        _emit 0xEF
        // cmp ebp, edi
        _emit 0x74
        _emit 0x26
        // je 0xe8591c
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x5C
        // mov ebp, dword ptr [esp + 0x5c]
        _emit 0x03
        _emit 0xEE
        // add ebp, esi
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x24
        _emit 0xAA
        // movss xmm4, dword ptr [edx + ebp*4]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x20
        // mov ebp, dword ptr [esp + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5E
        _emit 0xE0
        // divss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x65
        _emit 0x00
        // mulss xmm4, dword ptr [ebp]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x2C
        // mov ebp, dword ptr [esp + 0x2c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x65
        _emit 0x00
        // addss xmm4, dword ptr [ebp]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x65
        _emit 0x00
        // movss dword ptr [ebp], xmm4
        _emit 0x39
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // cmp dword ptr [esp + 0x14], edi
        _emit 0x74
        _emit 0x26
        // je 0xe85948
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x5C
        // mov ebp, dword ptr [esp + 0x5c]
        _emit 0x03
        _emit 0xEE
        // add ebp, esi
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x24
        _emit 0xAA
        // movss xmm4, dword ptr [edx + ebp*4]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x30
        // mov ebp, dword ptr [esp + 0x30]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5E
        _emit 0xE0
        // divss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x65
        _emit 0x00
        // mulss xmm4, dword ptr [ebp]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x34
        // mov ebp, dword ptr [esp + 0x34]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x65
        _emit 0x00
        // addss xmm4, dword ptr [ebp]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x65
        _emit 0x00
        // movss dword ptr [ebp], xmm4
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x14
        // mov ebp, dword ptr [esp + 0x14]
        _emit 0x45
        // inc ebp
        _emit 0x3B
        _emit 0xEF
        // cmp ebp, edi
        _emit 0x74
        _emit 0x23
        // je 0xe85974
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x5C
        // mov edi, dword ptr [esp + 0x5c]
        _emit 0x03
        _emit 0xFE
        // add edi, esi
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x24
        _emit 0xBA
        // movss xmm4, dword ptr [edx + edi*4]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x38
        // mov edi, dword ptr [esp + 0x38]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5E
        _emit 0xE0
        // divss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x27
        // mulss xmm4, dword ptr [edi]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x3C
        // mov edi, dword ptr [esp + 0x3c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x27
        // addss xmm4, dword ptr [edi]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x27
        // movss dword ptr [edi], xmm4
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x24
        // mov ebp, dword ptr [esp + 0x24]
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // add dword ptr [esp + 0x28], eax
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // add dword ptr [esp + 0x20], eax
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // add dword ptr [esp + 0x2c], eax
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // add dword ptr [esp + 0x30], eax
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // add dword ptr [esp + 0x34], eax
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // add dword ptr [esp + 0x38], eax
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        // add dword ptr [esp + 0x3c], eax
        _emit 0x83
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x04
        // add dword ptr [esp + 0x14], 4
        _emit 0x83
        _emit 0xC3
        _emit 0x04
        // add ebx, 4
        _emit 0x03
        _emit 0xE8
        // add ebp, eax
        _emit 0x8D
        _emit 0x79
        _emit 0xFD
        // lea edi, [ecx - 3]
        _emit 0x3B
        _emit 0xDF
        // cmp ebx, edi
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], ebp
        _emit 0x0F
        _emit 0x8C
        _emit 0x13
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jl 0xe858c0
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x5C
        // mov edi, dword ptr [esp + 0x5c]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x10
        // mov ebp, dword ptr [esp + 0x10]
        _emit 0x3B
        _emit 0xD9
        // cmp ebx, ecx
        _emit 0x7D
        _emit 0x4A
        // jge 0xe85a03
        _emit 0x8B
        _emit 0xC3
        // mov eax, ebx
        _emit 0x0F
        _emit 0xAF
        _emit 0xC1
        // imul eax, ecx
        _emit 0x8D
        _emit 0x3C
        _emit 0x30
        // lea edi, [eax + esi]
        _emit 0x03
        _emit 0xC5
        // add eax, ebp
        _emit 0x8D
        _emit 0x3C
        _emit 0xBA
        // lea edi, [edx + edi*4]
        _emit 0x8D
        _emit 0x2C
        _emit 0x82
        // lea ebp, [edx + eax*4]
        _emit 0x3B
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // cmp ebx, dword ptr [esp + 0x10]
        _emit 0x74
        _emit 0x1C
        // je 0xe859eb
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x5C
        // mov eax, dword ptr [esp + 0x5c]
        _emit 0x03
        _emit 0xC6
        // add eax, esi
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x24
        _emit 0x82
        // movss xmm4, dword ptr [edx + eax*4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5E
        _emit 0xE0
        // divss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x65
        _emit 0x00
        // mulss xmm4, dword ptr [ebp]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x27
        // addss xmm4, dword ptr [edi]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x27
        // movss dword ptr [edi], xmm4
        _emit 0x8D
        _emit 0x04
        _emit 0x8D
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea eax, [ecx*4]
        _emit 0x43
        // inc ebx
        _emit 0x03
        _emit 0xE8
        // add ebp, eax
        _emit 0x03
        _emit 0xF8
        // add edi, eax
        _emit 0x3B
        _emit 0xD9
        // cmp ebx, ecx
        _emit 0x7C
        _emit 0xCE
        // jl 0xe859c9
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x5C
        // mov edi, dword ptr [esp + 0x5c]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x10
        // mov ebp, dword ptr [esp + 0x10]
        _emit 0xB8
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 4
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // add dword ptr [esp + 0x40], eax
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // add dword ptr [esp + 0x44], eax
        _emit 0x46
        // inc esi
        _emit 0x3B
        _emit 0xF1
        // cmp esi, ecx
        _emit 0x0F
        _emit 0x8C
        _emit 0x34
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jl 0xe8584d
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x54
        // mov eax, dword ptr [esp + 0x54]
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // add dword ptr [esp + 0x48], eax
        _emit 0xB8
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 4
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // add dword ptr [esp + 0x18], eax
        _emit 0x01
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // add dword ptr [esp + 0x1c], eax
        _emit 0x45
        // inc ebp
        _emit 0x8D
        _emit 0x34
        _emit 0x8D
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esi, [ecx*4]
        _emit 0x01
        _emit 0x74
        _emit 0x24
        _emit 0x4C
        // add dword ptr [esp + 0x4c], esi
        _emit 0x03
        _emit 0xF9
        // add edi, ecx
        _emit 0x3B
        _emit 0x6C
        _emit 0x24
        _emit 0x50
        // cmp ebp, dword ptr [esp + 0x50]
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ebp
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x5C
        // mov dword ptr [esp + 0x5c], edi
        _emit 0x0F
        _emit 0x8E
        _emit 0x1F
        _emit 0xFC
        _emit 0xFF
        _emit 0xFF
        // jle 0xe8566d
        _emit 0x5F
        // pop edi
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x5D
        // pop ebp
        _emit 0x83
        _emit 0xC4
        _emit 0x48
        // add esp, 0x48
        _emit 0xC3
        // ret 
    }
}

// @ 0x00e85a60  (860 bytes)
__declspec(naked) void FUN_00e85a60()
{
    __asm {
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov eax, dword ptr [esp + 0xc]
        _emit 0x81
        _emit 0xEC
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // sub esp, 0x88
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0xAC
        _emit 0x24
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebp, dword ptr [esp + 0x94]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xB4
        _emit 0x24
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov esi, dword ptr [esp + 0xa8]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xBC
        _emit 0x24
        _emit 0xA0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edi, dword ptr [esp + 0xa0]
        _emit 0x56
        // push esi
        _emit 0x50
        // push eax
        _emit 0x57
        // push edi
        _emit 0x55
        // push ebp
        call FUN_00e853c0
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x83
        _emit 0xFD
        _emit 0x04
        // cmp ebp, 4
        _emit 0x0F
        _emit 0x8C
        _emit 0xEE
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jl 0xe85b88
        _emit 0x8B
        _emit 0x94
        _emit 0x24
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esp + 0xa8]
        _emit 0x8D
        _emit 0x4A
        _emit 0x1C
        // lea ecx, [edx + 0x1c]
        _emit 0x2B
        _emit 0xD7
        // sub edx, edi
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], edx
        _emit 0x8D
        _emit 0x55
        _emit 0xFC
        // lea edx, [ebp - 4]
        _emit 0xC1
        _emit 0xEA
        _emit 0x02
        // shr edx, 2
        _emit 0x42
        // inc edx
        _emit 0x8D
        _emit 0x47
        _emit 0x14
        // lea eax, [edi + 0x14]
        _emit 0x8D
        _emit 0x1C
        _emit 0x95
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebx, [edx*4]
        _emit 0xEB
        _emit 0x03
        // jmp 0xe85ac0
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0xEC
        // movss xmm0, dword ptr [eax - 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x06
        // subss xmm0, dword ptr [esi]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0xF0
        // movss xmm1, dword ptr [eax - 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x4E
        _emit 0x04
        // subss xmm1, dword ptr [esi + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x50
        _emit 0xF4
        // movss xmm2, dword ptr [eax - 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x56
        _emit 0x08
        // subss xmm2, dword ptr [esi + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x41
        _emit 0xE4
        // movss dword ptr [ecx - 0x1c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x49
        _emit 0xE8
        // movss dword ptr [ecx - 0x18], xmm1
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        // mov edi, dword ptr [esp + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x51
        _emit 0xEC
        // movss dword ptr [ecx - 0x14], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0xF8
        // movss xmm0, dword ptr [eax - 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x06
        // subss xmm0, dword ptr [esi]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0xFC
        // movss xmm1, dword ptr [eax - 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x4E
        _emit 0x04
        // subss xmm1, dword ptr [esi + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x10
        // movss xmm2, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x56
        _emit 0x08
        // subss xmm2, dword ptr [esi + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x41
        _emit 0xF0
        // movss dword ptr [ecx - 0x10], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x49
        _emit 0xF4
        // movss dword ptr [ecx - 0xc], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x14
        _emit 0x07
        // movss dword ptr [edi + eax], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x04
        // movss xmm0, dword ptr [eax + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0x08
        // movss xmm1, dword ptr [eax + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x50
        _emit 0x0C
        // movss xmm2, dword ptr [eax + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x06
        // subss xmm0, dword ptr [esi]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x4E
        _emit 0x04
        // subss xmm1, dword ptr [esi + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x56
        _emit 0x08
        // subss xmm2, dword ptr [esi + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x41
        _emit 0xFC
        // movss dword ptr [ecx - 4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x09
        // movss dword ptr [ecx], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x51
        _emit 0x04
        // movss dword ptr [ecx + 4], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x10
        // movss xmm0, dword ptr [eax + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0x14
        // movss xmm1, dword ptr [eax + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x50
        _emit 0x18
        // movss xmm2, dword ptr [eax + 0x18]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x06
        // subss xmm0, dword ptr [esi]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x4E
        _emit 0x04
        // subss xmm1, dword ptr [esi + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x56
        _emit 0x08
        // subss xmm2, dword ptr [esi + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x41
        _emit 0x08
        // movss dword ptr [ecx + 8], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x49
        _emit 0x0C
        // movss dword ptr [ecx + 0xc], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x51
        _emit 0x10
        // movss dword ptr [ecx + 0x10], xmm2
        _emit 0x83
        _emit 0xC0
        _emit 0x30
        // add eax, 0x30
        _emit 0x83
        _emit 0xC1
        _emit 0x30
        // add ecx, 0x30
        _emit 0x83
        _emit 0xEA
        _emit 0x01
        // sub edx, 1
        _emit 0x0F
        _emit 0x85
        _emit 0x3F
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jne 0xe85ac0
        _emit 0x8B
        _emit 0xBC
        _emit 0x24
        _emit 0xA0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edi, dword ptr [esp + 0xa0]
        _emit 0x3B
        _emit 0xDD
        // cmp ebx, ebp
        _emit 0x7D
        _emit 0x5D
        // jge 0xe85be9
        _emit 0x8B
        _emit 0x94
        _emit 0x24
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esp + 0xa8]
        _emit 0x8D
        _emit 0x04
        _emit 0x5B
        // lea eax, [ebx + ebx*2]
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x8D
        _emit 0x0C
        _emit 0x10
        // lea ecx, [eax + edx]
        _emit 0x2B
        _emit 0xD7
        // sub edx, edi
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], edx
        _emit 0x8B
        _emit 0xD5
        // mov edx, ebp
        _emit 0x8D
        _emit 0x44
        _emit 0x38
        _emit 0x08
        // lea eax, [eax + edi + 8]
        _emit 0x2B
        _emit 0xD3
        // sub edx, ebx
        _emit 0xEB
        _emit 0x03
        // jmp 0xe85bb0
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0xF8
        // movss xmm0, dword ptr [eax - 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0xFC
        // movss xmm1, dword ptr [eax - 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x10
        // movss xmm2, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x06
        // subss xmm0, dword ptr [esi]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x4E
        _emit 0x04
        // subss xmm1, dword ptr [esi + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x56
        _emit 0x08
        // subss xmm2, dword ptr [esi + 8]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        // mov edi, dword ptr [esp + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x01
        // movss dword ptr [ecx], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x49
        _emit 0x04
        // movss dword ptr [ecx + 4], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x14
        _emit 0x38
        // movss dword ptr [eax + edi], xmm2
        _emit 0x83
        _emit 0xC0
        _emit 0x0C
        // add eax, 0xc
        _emit 0x83
        _emit 0xC1
        _emit 0x0C
        // add ecx, 0xc
        _emit 0x83
        _emit 0xEA
        _emit 0x01
        // sub edx, 1
        _emit 0x75
        _emit 0xC7
        // jne 0xe85bb0
        _emit 0x8B
        _emit 0x9C
        _emit 0x24
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, dword ptr [esp + 0xb0]
        _emit 0x68
        _emit 0x44
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // push 0x144
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x53
        // push ebx
        call FUN_011e073e
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x85
        _emit 0xED
        // test ebp, ebp
        _emit 0x0F
        _emit 0x8E
        _emit 0x9C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jle 0xe85da6
        _emit 0x8B
        _emit 0x84
        _emit 0x24
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esp + 0xa8]
        _emit 0x83
        _emit 0xC0
        _emit 0x08
        // add eax, 8
        _emit 0xEB
        _emit 0x0A
        // jmp 0xe85c20
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0xF8
        // movss xmm0, dword ptr [eax - 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0xFC
        // movss xmm1, dword ptr [eax - 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x20
        // movss xmm4, dword ptr [eax]
        _emit 0x8B
        _emit 0x8C
        _emit 0x24
        _emit 0xA4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esp + 0xa4]
        _emit 0x0F
        _emit 0x28
        _emit 0xD8
        // movaps xmm3, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD9
        // mulss xmm3, xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0xD0
        // movaps xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD0
        // mulss xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC4
        // mulss xmm0, xmm4
        _emit 0x0F
        _emit 0x28
        _emit 0xF0
        // movaps xmm6, xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0xEB
        // movaps xmm5, xmm3
        _emit 0x0F
        _emit 0x28
        _emit 0xFB
        // movaps xmm7, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x84
        _emit 0x24
        _emit 0x8C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esp + 0x8c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x04
        _emit 0x91
        // movss xmm0, dword ptr [ecx + edx*4]
        _emit 0x0F
        _emit 0x28
        _emit 0xD9
        // movaps xmm3, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD9
        // mulss xmm3, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD8
        // mulss xmm3, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCC
        // mulss xmm1, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD0
        // mulss xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x13
        // addss xmm2, dword ptr [ebx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x8C
        _emit 0x24
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esp + 0x88], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x8C
        _emit 0x24
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esp + 0x90], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xF8
        // mulss xmm7, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE8
        // mulss xmm5, xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0xCC
        // movaps xmm1, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCC
        // mulss xmm1, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0x0F
        _emit 0x28
        _emit 0xE6
        // movaps xmm4, xmm6
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE0
        // mulss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xF0
        // mulss xmm6, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x5C
        _emit 0x24
        _emit 0x6C
        // movss dword ptr [esp + 0x6c], xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x9C
        _emit 0x24
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm3, dword ptr [esp + 0x88]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD8
        // mulss xmm3, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x5B
        _emit 0x14
        // addss xmm3, dword ptr [ebx + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x64
        _emit 0x24
        _emit 0x5C
        // movss dword ptr [esp + 0x5c], xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA4
        _emit 0x24
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [esp + 0x90]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE0
        // mulss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x5C
        // movss xmm0, dword ptr [esp + 0x5c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x43
        _emit 0x18
        // addss xmm0, dword ptr [ebx + 0x18]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x43
        _emit 0x1C
        // movss xmm0, dword ptr [ebx + 0x1c]
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
        _emit 0x18
        // movss dword ptr [esp + 0x18], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x43
        _emit 0x0C
        // movss xmm0, dword ptr [ebx + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x4B
        _emit 0x20
        // addss xmm1, dword ptr [ebx + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC7
        // addss xmm0, xmm7
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // movss dword ptr [esp + 0x2c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x43
        _emit 0x10
        // movss xmm0, dword ptr [ebx + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x44
        _emit 0x24
        _emit 0x6C
        // addss xmm0, dword ptr [esp + 0x6c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // movss dword ptr [esp + 0x30], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x43
        _emit 0x04
        // movss xmm0, dword ptr [ebx + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // movss dword ptr [esp + 0x20], xmm2
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x38
        // mov dword ptr [esp + 0x38], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC5
        // addss xmm0, xmm5
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // movss dword ptr [esp + 0x24], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x43
        _emit 0x08
        // movss xmm0, dword ptr [ebx + 8]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // mov ecx, dword ptr [esp + 0x24]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x3C
        // mov dword ptr [esp + 0x3c], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC6
        // addss xmm0, xmm6
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // movss dword ptr [esp + 0x28], xmm0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // mov ecx, dword ptr [esp + 0x28]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // mov dword ptr [esp + 0x40], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov ecx, dword ptr [esp + 0x2c]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x44
        // mov dword ptr [esp + 0x44], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x30
        // mov ecx, dword ptr [esp + 0x30]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // mov dword ptr [esp + 0x48], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x5C
        _emit 0x24
        _emit 0x34
        // movss dword ptr [esp + 0x34], xmm3
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // mov ecx, dword ptr [esp + 0x34]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x4C
        // mov dword ptr [esp + 0x4c], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x50
        // mov dword ptr [esp + 0x50], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x54
        // mov dword ptr [esp + 0x54], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // movss dword ptr [esp + 0x1c], xmm1
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov ecx, dword ptr [esp + 0x1c]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x58
        // mov dword ptr [esp + 0x58], ecx
        _emit 0xB9
        _emit 0x09
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, 9
        _emit 0x8D
        _emit 0x74
        _emit 0x24
        _emit 0x38
        // lea esi, [esp + 0x38]
        _emit 0x8B
        _emit 0xFB
        // mov edi, ebx
        _emit 0xF3
        _emit 0xA5
        // rep movsd dword ptr es:[edi], dword ptr [esi]
        _emit 0x42
        // inc edx
        _emit 0x83
        _emit 0xC0
        _emit 0x0C
        // add eax, 0xc
        _emit 0x3B
        _emit 0xD5
        // cmp edx, ebp
        _emit 0x0F
        _emit 0x8C
        _emit 0x7A
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jl 0xe85c20
        _emit 0x53
        // push ebx
        _emit 0x6A
        _emit 0x03
        // push 3
        call FUN_00e855e0
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0x81
        _emit 0xC4
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add esp, 0x88
        _emit 0xC3
        // ret 
    }
}
