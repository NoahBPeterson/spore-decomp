// Slice s00e47520: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00579a90();
extern "C" void FUN_005a74a0();
extern "C" void FUN_006b5060();
extern "C" void FUN_006b5240();
extern "C" void FUN_006b55c0();
extern "C" void FUN_00806e40();
extern "C" void FUN_00808b20();
extern "C" void FUN_00828020();
extern "C" void FUN_00828740();
extern "C" void FUN_00828c30();
extern "C" void FUN_0093db80();
extern "C" void FUN_00aea5d0();
extern "C" void FUN_00b3d410();
extern "C" void FUN_00b8ef40();
extern "C" void FUN_00e37d70();
extern "C" void FUN_00e3cf60();
extern "C" void FUN_00e460d0();
extern "C" void FUN_00e46140();
extern "C" void FUN_00e46180();
extern "C" void FUN_00e46600();
extern "C" void FUN_00e471e0();
extern "C" void FUN_00f47380();
extern "C" void FUN_00f473a0();

// @ 0x00e47520  (465 bytes)
__declspec(naked) void FUN_00e47520()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x38
        // sub esp, 0x38
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x83
        _emit 0x7E
        _emit 0x78
        _emit 0x00
        // cmp dword ptr [esi + 0x78], 0
        _emit 0x0F
        _emit 0x84
        _emit 0xBA
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xe476ea
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x44
        // mov ebx, dword ptr [esp + 0x44]
        _emit 0x53
        // push ebx
        call FUN_00828020
        _emit 0x8B
        _emit 0x4E
        _emit 0x7C
        // mov ecx, dword ptr [esi + 0x7c]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x0A
        // je 0xe4754c
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x7C
        // mov edx, dword ptr [eax + 0x7c]
        _emit 0x53
        // push ebx
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x84
        _emit 0xDB
        // test bl, bl
        _emit 0x0F
        _emit 0x84
        _emit 0x95
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xe476e9
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x4C
        // mov edi, dword ptr [esp + 0x4c]
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x0F
        _emit 0x84
        _emit 0x87
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xe476e8
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // lea ecx, [esp + 0x1c]
        call FUN_006b5060
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // lea eax, [esp + 0x1c]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_00e46140
        _emit 0x83
        _emit 0xBF
        _emit 0xD4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x01
        // cmp dword ptr [edi + 0xd4], 1
        _emit 0x8A
        _emit 0xD8
        // mov bl, al
        _emit 0x7E
        _emit 0x10
        // jle 0xe47591
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // lea ecx, [esp + 0x1c]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_00e46180
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x75
        _emit 0x08
        // jne 0xe47599
        _emit 0x84
        _emit 0xDB
        // test bl, bl
        _emit 0x0F
        _emit 0x84
        _emit 0x2B
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xe476c4
        _emit 0x57
        // push edi
        call FUN_00b3d410
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00e3cf60
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // lea ecx, [esp + 0x1c]
        call FUN_006b55c0
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // lea ecx, [esp + 0x10]
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x10], 0
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x14], 0
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x18], 0
        call FUN_00579a90
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // lea edx, [esp + 0xc]
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // lea ecx, [esp + 0x34]
        call FUN_005a74a0
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // lea eax, [esp + 0x38]
        _emit 0x50
        // push eax
        _emit 0x68
        _emit 0xB8
        _emit 0x6E
        _emit 0x0C
        _emit 0x06
        // push 0x60c6eb8
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00828c30
        _emit 0xF6
        _emit 0x44
        _emit 0x24
        _emit 0x40
        _emit 0x04
        // test byte ptr [esp + 0x40], 4
        _emit 0x74
        _emit 0x0B
        // je 0xe47606
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // lea ecx, [esp + 0x34]
        call FUN_0093db80
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov eax, dword ptr [esp + 0xc]
        _emit 0x2B
        _emit 0xC8
        // sub ecx, eax
        _emit 0x83
        _emit 0xE1
        _emit 0xFE
        // and ecx, 0xfffffffe
        _emit 0x83
        _emit 0xF9
        _emit 0x02
        // cmp ecx, 2
        _emit 0x7E
        _emit 0x0D
        // jle 0xe47625
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x09
        // je 0xe47625
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00828740
        _emit 0x8B
        _emit 0x8E
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x80]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x0F
        _emit 0x84
        _emit 0x93
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xe476cd
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x38
        // mov eax, dword ptr [edx + 0x38]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x8E
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x80]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x0C
        // movss xmm0, dword ptr [eax + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x40
        _emit 0x04
        // subss xmm0, dword ptr [eax + 4]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x51
        // push ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x54
        // movss dword ptr [esp + 0x54], xmm0
        call FUN_00806e40
        _emit 0x8B
        _emit 0x8E
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x80]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x38
        // mov eax, dword ptr [edx + 0x38]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x4E
        _emit 0x78
        // mov ecx, dword ptr [esi + 0x78]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x0C
        // movss xmm0, dword ptr [eax + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x40
        _emit 0x04
        // subss xmm0, dword ptr [eax + 4]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // subss xmm0, dword ptr [esp + 0x48]
        _emit 0x8B
        _emit 0x42
        _emit 0x38
        // mov eax, dword ptr [edx + 0x38]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // movss dword ptr [esp + 0x48], xmm0
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x0C
        // movss xmm0, dword ptr [eax + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x40
        _emit 0x04
        // subss xmm0, dword ptr [eax + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // addss xmm0, dword ptr [esp + 0x48]
        _emit 0x8B
        _emit 0x4E
        _emit 0x78
        // mov ecx, dword ptr [esi + 0x78]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // movss dword ptr [esp + 4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x08
        // movss xmm0, dword ptr [eax + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x00
        // subss xmm0, dword ptr [eax]
        _emit 0x8B
        _emit 0x42
        _emit 0x74
        // mov eax, dword ptr [edx + 0x74]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x04
        _emit 0x24
        // movss dword ptr [esp], xmm0
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0xEB
        _emit 0x09
        // jmp 0xe476cd
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00828020
        _emit 0x8B
        _emit 0x4E
        _emit 0x78
        // mov ecx, dword ptr [esi + 0x78]
        _emit 0x8B
        _emit 0x57
        _emit 0x20
        // mov edx, dword ptr [edi + 0x20]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        call FUN_00808b20
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // lea ecx, [esp + 0x1c]
        call FUN_006b5240
        _emit 0x5F
        // pop edi
        _emit 0x5B
        // pop ebx
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x38
        // add esp, 0x38
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00e47700  (549 bytes)
__declspec(naked) void FUN_00e47700()
{
    __asm {
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0x8D
        _emit 0x8F
        _emit 0xAC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [edi + 0xac]
        _emit 0x50
        // push eax
        call FUN_00b8ef40
        _emit 0x80
        _emit 0xBF
        _emit 0xED
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [edi + 0xed], 0
        _emit 0x0F
        _emit 0x84
        _emit 0xFB
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xe4791e
        _emit 0x56
        // push esi
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x3C
        _emit 0x6B
        _emit 0x3F
        _emit 0x01
        // push 0x13f6b3c
        _emit 0x68
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // push 0x10c
        call FUN_00f473a0
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0B
        // je 0xe4774d
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00e471e0
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0xEB
        _emit 0x02
        // jmp 0xe4774f
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0x8B
        _emit 0x87
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edi + 0xa8]
        _emit 0x8B
        _emit 0x4F
        _emit 0x1C
        // mov ecx, dword ptr [edi + 0x1c]
        _emit 0x89
        _emit 0x86
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xa8], eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x15
        // je 0xe47777
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x89
        _emit 0x46
        _emit 0x68
        // mov dword ptr [esi + 0x68], eax
        call FUN_00e46600
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xC6
        _emit 0x86
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x01
        // mov byte ptr [esi + 0xe0], 1
        call FUN_00e460d0
        _emit 0xD9
        _emit 0x9E
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [esi + 0xdc]
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x87
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edi + 0xc4]
        _emit 0x3B
        _emit 0x87
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp eax, dword ptr [edi + 0xc8]
        _emit 0x8D
        _emit 0xAF
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebp, [edi + 0xc0]
        _emit 0x73
        _emit 0x16
        // jae 0xe477c2
        _emit 0x8D
        _emit 0x48
        _emit 0x04
        // lea ecx, [eax + 4]
        _emit 0x89
        _emit 0x4D
        _emit 0x04
        // mov dword ptr [ebp + 4], ecx
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x1D
        // je 0xe477d3
        _emit 0x89
        _emit 0x30
        // mov dword ptr [eax], esi
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0xEB
        _emit 0x11
        // jmp 0xe477d3
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        call FUN_00aea5d0
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x18
        // mov esi, dword ptr [esp + 0x18]
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x09
        // je 0xe477e0
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x87
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edi + 0xb0]
        _emit 0x2B
        _emit 0x87
        _emit 0xAC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // sub eax, dword ptr [edi + 0xac]
        _emit 0x53
        // push ebx
        _emit 0xC1
        _emit 0xF8
        _emit 0x02
        // sar eax, 2
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x0F
        _emit 0x8E
        _emit 0x1D
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jle 0xe4791b
        _emit 0x8B
        _emit 0xFF
        // mov edi, edi
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x3C
        _emit 0x6B
        _emit 0x3F
        _emit 0x01
        // push 0x13f6b3c
        _emit 0x68
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // push 0x10c
        call FUN_00f473a0
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0B
        // je 0xe47829
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00e471e0
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0xEB
        _emit 0x02
        // jmp 0xe4782b
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0x8B
        _emit 0x97
        _emit 0xAC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [edi + 0xac]
        _emit 0x8B
        _emit 0x04
        _emit 0x9A
        // mov eax, dword ptr [edx + ebx*4]
        _emit 0x8B
        _emit 0x4F
        _emit 0x1C
        // mov ecx, dword ptr [edi + 0x1c]
        _emit 0x89
        _emit 0x86
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xa8], eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x15
        // je 0xe47856
        _emit 0x8B
        _emit 0x40
        _emit 0x0C
        // mov eax, dword ptr [eax + 0xc]
        _emit 0x8B
        _emit 0x00
        // mov eax, dword ptr [eax]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x89
        _emit 0x46
        _emit 0x68
        // mov dword ptr [esi + 0x68], eax
        call FUN_00e46600
        _emit 0xC6
        _emit 0x86
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x01
        // mov byte ptr [esi + 0xe0], 1
        _emit 0x80
        _emit 0xBF
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [edi + 0xe0], 0
        _emit 0x74
        _emit 0x0A
        // je 0xe47870
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x87
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [edi + 0xdc]
        _emit 0xEB
        _emit 0x50
        // jmp 0xe478c0
        _emit 0x8B
        _emit 0x87
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edi + 0xa8]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0A
        // je 0xe47884
        _emit 0x8B
        _emit 0x48
        _emit 0x0C
        // mov ecx, dword ptr [eax + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x41
        _emit 0x04
        // movss xmm0, dword ptr [ecx + 4]
        _emit 0xEB
        _emit 0x03
        // jmp 0xe47887
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // movss dword ptr [esp + 0x1c], xmm0
        call FUN_00b3d410
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x24
        // je 0xe478ba
        _emit 0x81
        _emit 0xBF
        _emit 0xE4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xCB
        _emit 0x28
        _emit 0xB5
        _emit 0xBE
        // cmp dword ptr [edi + 0xe4], 0xbeb528cb
        _emit 0x74
        _emit 0x18
        // je 0xe478ba
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        call FUN_00b3d410
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00e37d70
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // movss xmm0, dword ptr [esp + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xdc], xmm0
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x45
        _emit 0x04
        // mov eax, dword ptr [ebp + 4]
        _emit 0x3B
        _emit 0x45
        _emit 0x08
        // cmp eax, dword ptr [ebp + 8]
        _emit 0x73
        _emit 0x16
        // jae 0xe478f2
        _emit 0x8D
        _emit 0x48
        _emit 0x04
        // lea ecx, [eax + 4]
        _emit 0x89
        _emit 0x4D
        _emit 0x04
        // mov dword ptr [ebp + 4], ecx
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x1D
        // je 0xe47903
        _emit 0x89
        _emit 0x30
        // mov dword ptr [eax], esi
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0xEB
        _emit 0x11
        // jmp 0xe47903
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // lea ecx, [esp + 0x10]
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        call FUN_00aea5d0
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x10
        // mov esi, dword ptr [esp + 0x10]
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x09
        // je 0xe47910
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x43
        // inc ebx
        _emit 0x3B
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // cmp ebx, dword ptr [esp + 0x14]
        _emit 0x0F
        _emit 0x8C
        _emit 0xE5
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jl 0xe47800
        _emit 0x5B
        // pop ebx
        _emit 0x5D
        // pop ebp
        _emit 0x5E
        // pop esi
        _emit 0x5F
        // pop edi
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}
