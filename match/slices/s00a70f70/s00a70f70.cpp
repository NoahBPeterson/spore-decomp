// Slice s00a70f70: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_0042b9e0();
extern "C" void FUN_00454cb0();
extern "C" void FUN_00472fe0();
extern "C" void FUN_0050d4e0();
extern "C" void FUN_00537dc0();
extern "C" void FUN_0093d5d0();
extern "C" void FUN_00950ea0();
extern "C" void FUN_00a69b20();
extern "C" void FUN_00a6b150();
extern "C" void FUN_00a6d7b0();
extern "C" void FUN_00a70730();
extern "C" void FUN_00a70980();
extern "C" void FUN_00a70bb0();
extern "C" void FUN_00a70cc0();
extern "C" void FUN_00a70d60();
extern "C" void FUN_00a70df0();
extern "C" void FUN_00a70f70();
extern "C" void FUN_00a711c0();
extern "C" void FUN_00a71260();
extern "C" void FUN_00a712e0();
extern "C" void FUN_00a71410();
extern "C" void FUN_00a71910();
extern "C" void FUN_00a82370();
extern "C" void FUN_00f47380();
extern "C" void FUN_00f473a0();
extern "C" void FUN_011e0744();

// @ 0x00a70f70  (94 bytes)
__declspec(naked) void FUN_00a70f70()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x0C
        // mov ebp, dword ptr [esp + 0xc]
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        call FUN_00537dc0
        _emit 0x8B
        _emit 0x7D
        _emit 0x38
        // mov edi, dword ptr [ebp + 0x38]
        _emit 0x8B
        _emit 0x5E
        _emit 0x38
        // mov ebx, dword ptr [esi + 0x38]
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x74
        _emit 0x1D
        // je 0xa70fa7
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x74
        _emit 0x09
        // je 0xa70f97
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x8B
        _emit 0x50
        _emit 0x34
        // mov edx, dword ptr [eax + 0x34]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x89
        _emit 0x7E
        _emit 0x38
        // mov dword ptr [esi + 0x38], edi
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x74
        _emit 0x09
        // je 0xa70fa7
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x8B
        _emit 0x50
        _emit 0x38
        // mov edx, dword ptr [eax + 0x38]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x45
        _emit 0x3C
        // mov eax, dword ptr [ebp + 0x3c]
        _emit 0x89
        _emit 0x46
        _emit 0x3C
        // mov dword ptr [esi + 0x3c], eax
        _emit 0xD9
        _emit 0x45
        _emit 0x40
        // fld dword ptr [ebp + 0x40]
        _emit 0xD9
        _emit 0x5E
        _emit 0x40
        // fstp dword ptr [esi + 0x40]
        _emit 0x8B
        _emit 0x4D
        _emit 0x44
        // mov ecx, dword ptr [ebp + 0x44]
        _emit 0x89
        _emit 0x4E
        _emit 0x44
        // mov dword ptr [esi + 0x44], ecx
        _emit 0x83
        _emit 0xC5
        _emit 0x48
        // add ebp, 0x48
        _emit 0x55
        // push ebp
        _emit 0x8D
        _emit 0x4E
        _emit 0x48
        // lea ecx, [esi + 0x48]
        call FUN_0050d4e0
        _emit 0x5F
        // pop edi
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
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

// @ 0x00a70fd0  (490 bytes)
__declspec(naked) void FUN_00a70fd0()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x0C
        // mov ebp, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x45
        _emit 0x00
        // mov eax, dword ptr [ebp]
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x0F
        _emit 0x85
        _emit 0xDE
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0xa710c3
        call FUN_00a70bb0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0x56
        _emit 0x14
        // mov edx, dword ptr [esi + 0x14]
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x8B
        _emit 0x47
        _emit 0x04
        // mov eax, dword ptr [edi + 4]
        _emit 0x8B
        _emit 0x00
        // mov eax, dword ptr [eax]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x5F
        _emit 0x04
        // lea ebx, [edi + 4]
        _emit 0x52
        // push edx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x85
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [ebp + 0x80]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x7C
        _emit 0x72
        // jl 0xa7107e
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x81
        _emit 0xE1
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        // and ecx, 0xff000000
        _emit 0x81
        _emit 0xF9
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x7F
        // cmp ecx, 0x7f000000
        _emit 0x75
        _emit 0x2F
        // jne 0xa7104b
        _emit 0x8B
        _emit 0x4E
        _emit 0x14
        // mov ecx, dword ptr [esi + 0x14]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // mov edx, dword ptr [esp + 0x24]
        _emit 0x8B
        _emit 0x69
        _emit 0x2C
        // mov ebp, dword ptr [ecx + 0x2c]
        _emit 0xC1
        _emit 0xFA
        _emit 0x18
        // sar edx, 0x18
        _emit 0x8B
        _emit 0x54
        _emit 0x95
        _emit 0x00
        // mov edx, dword ptr [ebp + edx*4]
        _emit 0x8B
        _emit 0x92
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [edx + 0x88]
        _emit 0x25
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        _emit 0x00
        // and eax, 0xffffff
        _emit 0x8B
        _emit 0x2C
        _emit 0xC2
        // mov ebp, dword ptr [edx + eax*8]
        _emit 0x8B
        _emit 0x44
        _emit 0xC2
        _emit 0x04
        // mov eax, dword ptr [edx + eax*8 + 4]
        _emit 0x50
        // push eax
        _emit 0x55
        // push ebp
        call FUN_00a6d7b0
        _emit 0x89
        _emit 0x47
        _emit 0x20
        // mov dword ptr [edi + 0x20], eax
        _emit 0xEB
        _emit 0x0F
        // jmp 0xa7105a
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // mov ecx, dword ptr [esp + 0x24]
        _emit 0x81
        _emit 0xE1
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        // and ecx, 0xff000000
        _emit 0x0B
        _emit 0xC8
        // or ecx, eax
        _emit 0x89
        _emit 0x4F
        _emit 0x20
        // mov dword ptr [edi + 0x20], ecx
        _emit 0x8B
        _emit 0x47
        _emit 0x20
        // mov eax, dword ptr [edi + 0x20]
        _emit 0x8B
        _emit 0x4E
        _emit 0x14
        // mov ecx, dword ptr [esi + 0x14]
        _emit 0x8B
        _emit 0x49
        _emit 0x2C
        // mov ecx, dword ptr [ecx + 0x2c]
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0x25
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        _emit 0x00
        // and eax, 0xffffff
        _emit 0x6B
        _emit 0xC0
        _emit 0x58
        // imul eax, eax, 0x58
        _emit 0xC1
        _emit 0xFA
        _emit 0x18
        // sar edx, 0x18
        _emit 0x8B
        _emit 0x14
        _emit 0x91
        // mov edx, dword ptr [ecx + edx*4]
        _emit 0x03
        _emit 0x42
        _emit 0x34
        // add eax, dword ptr [edx + 0x34]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0x50
        // push eax
        call FUN_00a82370
        _emit 0x83
        _emit 0x4F
        _emit 0x2C
        _emit 0x20
        // or dword ptr [edi + 0x2c], 0x20
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x18
        // mov ebp, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x75
        _emit 0x38
        // mov esi, dword ptr [ebp + 0x38]
        _emit 0x3B
        _emit 0xDE
        // cmp ebx, esi
        _emit 0x0F
        _emit 0x84
        _emit 0x18
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xa711a9
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x74
        _emit 0x09
        // je 0xa7109e
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x8B
        _emit 0x50
        _emit 0x34
        // mov edx, dword ptr [eax + 0x34]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x89
        _emit 0x5D
        _emit 0x38
        // mov dword ptr [ebp + 0x38], ebx
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x0F
        _emit 0x84
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xa711a9
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x50
        _emit 0x38
        // mov edx, dword ptr [eax + 0x38]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x48
        _emit 0x04
        // mov ecx, dword ptr [eax + 4]
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x89
        _emit 0x4D
        _emit 0x44
        // mov dword ptr [ebp + 0x44], ecx
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x14
        _emit 0x00
        // ret 0x14
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x24
        // mov edi, dword ptr [esp + 0x24]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x18
        // mov ebp, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xC1
        _emit 0xE1
        _emit 0x05
        // shl ecx, 5
        _emit 0xC1
        _emit 0xFF
        _emit 0x18
        // sar edi, 0x18
        _emit 0x83
        _emit 0xB9
        _emit 0xB8
        _emit 0x5E
        _emit 0x67
        _emit 0x01
        _emit 0x00
        // cmp dword ptr [ecx + 0x1675eb8], 0
        _emit 0x74
        _emit 0x53
        // je 0xa7112f
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // mov ebx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x9B
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, dword ptr [ebx + 0x80]
        _emit 0x8B
        _emit 0x4E
        _emit 0x14
        // mov ecx, dword ptr [esi + 0x14]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x57
        // push edi
        _emit 0x53
        // push ebx
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x42
        _emit 0x70
        // mov eax, dword ptr [edx + 0x70]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0xC1
        _emit 0xE2
        _emit 0x05
        // shl edx, 5
        _emit 0x57
        // push edi
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x82
        _emit 0xB8
        _emit 0x5E
        _emit 0x67
        _emit 0x01
        // mov eax, dword ptr [edx + 0x1675eb8]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x5D
        _emit 0x38
        // mov ebx, dword ptr [ebp + 0x38]
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x74
        _emit 0x1D
        // je 0xa7112f
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x74
        _emit 0x09
        // je 0xa7111f
        _emit 0x8B
        _emit 0x17
        // mov edx, dword ptr [edi]
        _emit 0x8B
        _emit 0x42
        _emit 0x34
        // mov eax, dword ptr [edx + 0x34]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x89
        _emit 0x7D
        _emit 0x38
        // mov dword ptr [ebp + 0x38], edi
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x74
        _emit 0x09
        // je 0xa7112f
        _emit 0x8B
        _emit 0x13
        // mov edx, dword ptr [ebx]
        _emit 0x8B
        _emit 0x42
        _emit 0x38
        // mov eax, dword ptr [edx + 0x38]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x4D
        _emit 0x38
        // mov ecx, dword ptr [ebp + 0x38]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x73
        // je 0xa711a9
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov eax, dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x12
        // mov edx, dword ptr [edx]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x46
        _emit 0x14
        // mov eax, dword ptr [esi + 0x14]
        _emit 0x50
        // push eax
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov edi, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x47
        _emit 0x04
        // mov eax, dword ptr [edi + 4]
        _emit 0xD1
        _emit 0xE8
        // shr eax, 1
        _emit 0xA8
        _emit 0x01
        // test al, 1
        _emit 0x74
        _emit 0x4C
        // je 0xa7119f
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x1C
        // mov esi, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x0B
        // je 0xa71168
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x45
        _emit 0x38
        // mov eax, dword ptr [ebp + 0x38]
        _emit 0x8B
        _emit 0x52
        _emit 0x2C
        // mov edx, dword ptr [edx + 0x2c]
        _emit 0x50
        // push eax
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x47
        _emit 0x04
        // mov eax, dword ptr [edi + 4]
        _emit 0xC1
        _emit 0xE8
        _emit 0x02
        // shr eax, 2
        _emit 0xA8
        _emit 0x01
        // test al, 1
        _emit 0x74
        _emit 0x17
        // je 0xa71189
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0xC7
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi], 0
        _emit 0x8B
        _emit 0x48
        _emit 0x04
        // mov ecx, dword ptr [eax + 4]
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x89
        _emit 0x4D
        _emit 0x44
        // mov dword ptr [ebp + 0x44], ecx
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x14
        _emit 0x00
        // ret 0x14
        _emit 0x8B
        _emit 0x4D
        _emit 0x38
        // mov ecx, dword ptr [ebp + 0x38]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x89
        _emit 0x0E
        // mov dword ptr [esi], ecx
        _emit 0x8B
        _emit 0x48
        _emit 0x04
        // mov ecx, dword ptr [eax + 4]
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x89
        _emit 0x4D
        _emit 0x44
        // mov dword ptr [ebp + 0x44], ecx
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x14
        _emit 0x00
        // ret 0x14
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // mov edx, dword ptr [esp + 0x1c]
        _emit 0xC7
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edx], 0
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x48
        _emit 0x04
        // mov ecx, dword ptr [eax + 4]
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x89
        _emit 0x4D
        _emit 0x44
        // mov dword ptr [ebp + 0x44], ecx
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x14
        _emit 0x00
        // ret 0x14
    }
}

// @ 0x00a711c0  (158 bytes)
__declspec(naked) void FUN_00a711c0()
{
    __asm {
        _emit 0x51
        // push ecx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x80
        _emit 0x7E
        _emit 0x24
        _emit 0x00
        // cmp byte ptr [esi + 0x24], 0
        _emit 0x0F
        _emit 0x85
        _emit 0x8B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0xa71259
        _emit 0x8B
        _emit 0x4E
        _emit 0x44
        // mov ecx, dword ptr [esi + 0x44]
        _emit 0x53
        // push ebx
        _emit 0x57
        // push edi
        _emit 0xB8
        _emit 0x0A
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 0xa
        _emit 0x3B
        _emit 0x4E
        _emit 0x48
        // cmp ecx, dword ptr [esi + 0x48]
        _emit 0x74
        _emit 0x57
        // je 0xa71234
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x10
        // mov ebp, dword ptr [esp + 0x10]
        _emit 0xEB
        _emit 0x04
        // jmp 0xa711e8
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0x48
        // dec eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], eax
        _emit 0x85
        _emit 0xD2
        // test edx, edx
        _emit 0x7E
        _emit 0x40
        // jle 0xa71233
        _emit 0x8B
        _emit 0x46
        _emit 0x48
        // mov eax, dword ptr [esi + 0x48]
        _emit 0x8B
        _emit 0x4E
        _emit 0x44
        // mov ecx, dword ptr [esi + 0x44]
        _emit 0x8B
        _emit 0x56
        _emit 0x5C
        // mov edx, dword ptr [esi + 0x5c]
        _emit 0x55
        // push ebp
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x4E
        _emit 0x58
        // lea ecx, [esi + 0x58]
        call FUN_0042b9e0
        _emit 0x8B
        _emit 0x7E
        _emit 0x48
        // mov edi, dword ptr [esi + 0x48]
        _emit 0x8B
        _emit 0x5E
        _emit 0x44
        // mov ebx, dword ptr [esi + 0x44]
        _emit 0x8B
        _emit 0xC7
        // mov eax, edi
        _emit 0x2B
        _emit 0xC7
        // sub eax, edi
        _emit 0x50
        // push eax
        _emit 0x57
        // push edi
        _emit 0x53
        // push ebx
        call FUN_011e0744
        _emit 0x2B
        _emit 0xFB
        // sub edi, ebx
        _emit 0xC1
        _emit 0xFF
        _emit 0x02
        // sar edi, 2
        _emit 0xF7
        _emit 0xDF
        // neg edi
        _emit 0x03
        _emit 0xFF
        // add edi, edi
        _emit 0x03
        _emit 0xFF
        // add edi, edi
        _emit 0x01
        _emit 0x7E
        _emit 0x48
        // add dword ptr [esi + 0x48], edi
        _emit 0x8B
        _emit 0x4E
        _emit 0x44
        // mov ecx, dword ptr [esi + 0x44]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x3B
        _emit 0x4E
        _emit 0x48
        // cmp ecx, dword ptr [esi + 0x48]
        _emit 0x75
        _emit 0xB1
        // jne 0xa711e4
        _emit 0x5D
        // pop ebp
        _emit 0x8B
        _emit 0x7E
        _emit 0x48
        // mov edi, dword ptr [esi + 0x48]
        _emit 0x8B
        _emit 0x5E
        _emit 0x44
        // mov ebx, dword ptr [esi + 0x44]
        _emit 0x8B
        _emit 0xD7
        // mov edx, edi
        _emit 0x2B
        _emit 0xD7
        // sub edx, edi
        _emit 0x52
        // push edx
        _emit 0x57
        // push edi
        _emit 0x53
        // push ebx
        call FUN_011e0744
        _emit 0x2B
        _emit 0xFB
        // sub edi, ebx
        _emit 0xC1
        _emit 0xFF
        _emit 0x02
        // sar edi, 2
        _emit 0xF7
        _emit 0xDF
        // neg edi
        _emit 0x03
        _emit 0xFF
        // add edi, edi
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x03
        _emit 0xFF
        // add edi, edi
        _emit 0x01
        _emit 0x7E
        _emit 0x48
        // add dword ptr [esi + 0x48], edi
        _emit 0x5F
        // pop edi
        _emit 0x5B
        // pop ebx
        _emit 0x5E
        // pop esi
        _emit 0x59
        // pop ecx
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00a71260  (121 bytes)
__declspec(naked) void FUN_00a71260()
{
    __asm {
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x08
        // mov edi, dword ptr [esp + 8]
        _emit 0x3B
        _emit 0x7C
        _emit 0x24
        _emit 0x0C
        // cmp edi, dword ptr [esp + 0xc]
        _emit 0x74
        _emit 0x68
        // je 0xa712d3
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
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
        _emit 0xCE
        // mov ecx, esi
        call FUN_00537dc0
        _emit 0x8B
        _emit 0x5F
        _emit 0x38
        // mov ebx, dword ptr [edi + 0x38]
        _emit 0x8B
        _emit 0x6E
        _emit 0x38
        // mov ebp, dword ptr [esi + 0x38]
        _emit 0x3B
        _emit 0xDD
        // cmp ebx, ebp
        _emit 0x74
        _emit 0x1E
        // je 0xa712a2
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x74
        _emit 0x09
        // je 0xa71291
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x8B
        _emit 0x50
        _emit 0x34
        // mov edx, dword ptr [eax + 0x34]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x89
        _emit 0x5E
        _emit 0x38
        // mov dword ptr [esi + 0x38], ebx
        _emit 0x85
        _emit 0xED
        // test ebp, ebp
        _emit 0x74
        _emit 0x0A
        // je 0xa712a2
        _emit 0x8B
        _emit 0x45
        _emit 0x00
        // mov eax, dword ptr [ebp]
        _emit 0x8B
        _emit 0x50
        _emit 0x38
        // mov edx, dword ptr [eax + 0x38]
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x47
        _emit 0x3C
        // mov eax, dword ptr [edi + 0x3c]
        _emit 0x89
        _emit 0x46
        _emit 0x3C
        // mov dword ptr [esi + 0x3c], eax
        _emit 0xD9
        _emit 0x47
        _emit 0x40
        // fld dword ptr [edi + 0x40]
        _emit 0xD9
        _emit 0x5E
        _emit 0x40
        // fstp dword ptr [esi + 0x40]
        _emit 0x8B
        _emit 0x4F
        _emit 0x44
        // mov ecx, dword ptr [edi + 0x44]
        _emit 0x8D
        _emit 0x57
        _emit 0x48
        // lea edx, [edi + 0x48]
        _emit 0x89
        _emit 0x4E
        _emit 0x44
        // mov dword ptr [esi + 0x44], ecx
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x4E
        _emit 0x48
        // lea ecx, [esi + 0x48]
        call FUN_0050d4e0
        _emit 0x83
        _emit 0xC7
        _emit 0x5C
        // add edi, 0x5c
        _emit 0x83
        _emit 0xC6
        _emit 0x5C
        // add esi, 0x5c
        _emit 0x3B
        _emit 0x7C
        _emit 0x24
        _emit 0x18
        // cmp edi, dword ptr [esp + 0x18]
        _emit 0x75
        _emit 0xA6
        // jne 0xa71272
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0x5F
        // pop edi
        _emit 0xC3
        // ret 
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0x5F
        // pop edi
        _emit 0xC3
        // ret 
    }
}

// @ 0x00a712e0  (121 bytes)
__declspec(naked) void FUN_00a712e0()
{
    __asm {
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x0C
        // mov edi, dword ptr [esp + 0xc]
        _emit 0x3B
        _emit 0x7C
        _emit 0x24
        _emit 0x08
        // cmp edi, dword ptr [esp + 8]
        _emit 0x74
        _emit 0x68
        // je 0xa71353
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x1C
        // mov esi, dword ptr [esp + 0x1c]
        _emit 0x83
        _emit 0xEF
        _emit 0x5C
        // sub edi, 0x5c
        _emit 0x83
        _emit 0xEE
        _emit 0x5C
        // sub esi, 0x5c
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00537dc0
        _emit 0x8B
        _emit 0x5F
        _emit 0x38
        // mov ebx, dword ptr [edi + 0x38]
        _emit 0x8B
        _emit 0x6E
        _emit 0x38
        // mov ebp, dword ptr [esi + 0x38]
        _emit 0x3B
        _emit 0xDD
        // cmp ebx, ebp
        _emit 0x74
        _emit 0x1E
        // je 0xa71328
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x74
        _emit 0x09
        // je 0xa71317
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x8B
        _emit 0x50
        _emit 0x34
        // mov edx, dword ptr [eax + 0x34]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x89
        _emit 0x5E
        _emit 0x38
        // mov dword ptr [esi + 0x38], ebx
        _emit 0x85
        _emit 0xED
        // test ebp, ebp
        _emit 0x74
        _emit 0x0A
        // je 0xa71328
        _emit 0x8B
        _emit 0x45
        _emit 0x00
        // mov eax, dword ptr [ebp]
        _emit 0x8B
        _emit 0x50
        _emit 0x38
        // mov edx, dword ptr [eax + 0x38]
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x47
        _emit 0x3C
        // mov eax, dword ptr [edi + 0x3c]
        _emit 0x89
        _emit 0x46
        _emit 0x3C
        // mov dword ptr [esi + 0x3c], eax
        _emit 0xD9
        _emit 0x47
        _emit 0x40
        // fld dword ptr [edi + 0x40]
        _emit 0xD9
        _emit 0x5E
        _emit 0x40
        // fstp dword ptr [esi + 0x40]
        _emit 0x8B
        _emit 0x4F
        _emit 0x44
        // mov ecx, dword ptr [edi + 0x44]
        _emit 0x8D
        _emit 0x57
        _emit 0x48
        // lea edx, [edi + 0x48]
        _emit 0x89
        _emit 0x4E
        _emit 0x44
        // mov dword ptr [esi + 0x44], ecx
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x4E
        _emit 0x48
        // lea ecx, [esi + 0x48]
        call FUN_0050d4e0
        _emit 0x3B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // cmp edi, dword ptr [esp + 0x14]
        _emit 0x75
        _emit 0xA6
        // jne 0xa712f2
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0x5F
        // pop edi
        _emit 0xC3
        // ret 
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0x5F
        // pop edi
        _emit 0xC3
        // ret 
    }
}

// @ 0x00a71360  (170 bytes)
__declspec(naked) void FUN_00a71360()
{
    __asm {
        _emit 0x83
        _emit 0x7C
        _emit 0x24
        _emit 0x0C
        _emit 0x00
        // cmp dword ptr [esp + 0xc], 0
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xD9
        // mov ebx, ecx
        _emit 0x0F
        _emit 0x84
        _emit 0x96
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xa71404
        _emit 0x83
        _emit 0x7B
        _emit 0x20
        _emit 0x05
        // cmp dword ptr [ebx + 0x20], 5
        _emit 0x0F
        _emit 0x84
        _emit 0x8C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xa71404
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0x8B
        _emit 0x4B
        _emit 0x14
        // mov ecx, dword ptr [ebx + 0x14]
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x10
        // mov ebp, dword ptr [esp + 0x10]
        _emit 0x56
        // push esi
        _emit 0x55
        // push ebp
        _emit 0x50
        // push eax
        call FUN_00a6d7b0
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x7D
        _emit 0x08
        // jge 0xa7139a
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x32
        _emit 0xC0
        // xor al, al
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        call FUN_00a70bb0
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x8B
        _emit 0x43
        _emit 0x14
        // mov eax, dword ptr [ebx + 0x14]
        _emit 0x8B
        _emit 0x57
        _emit 0x04
        // mov edx, dword ptr [edi + 4]
        _emit 0x8B
        _emit 0x12
        // mov edx, dword ptr [edx]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x8D
        _emit 0x4F
        _emit 0x04
        // lea ecx, [edi + 4]
        _emit 0x50
        // push eax
        _emit 0x53
        // push ebx
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x89
        _emit 0x77
        _emit 0x20
        // mov dword ptr [edi + 0x20], esi
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x81
        _emit 0xE6
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        _emit 0x00
        // and esi, 0xffffff
        _emit 0x89
        _emit 0x47
        _emit 0x18
        // mov dword ptr [edi + 0x18], eax
        _emit 0x6B
        _emit 0xF6
        _emit 0x58
        // imul esi, esi, 0x58
        _emit 0x89
        _emit 0x6F
        _emit 0x1C
        // mov dword ptr [edi + 0x1c], ebp
        _emit 0x8B
        _emit 0x53
        _emit 0x14
        // mov edx, dword ptr [ebx + 0x14]
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0xC1
        _emit 0xF9
        _emit 0x18
        // sar ecx, 0x18
        _emit 0x8B
        _emit 0x0C
        _emit 0x88
        // mov ecx, dword ptr [eax + ecx*4]
        _emit 0x03
        _emit 0x71
        _emit 0x34
        // add esi, dword ptr [ecx + 0x34]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0x56
        // push esi
        call FUN_00a82370
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        call FUN_00a711c0
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // mov edx, dword ptr [esp + 0x1c]
        _emit 0x89
        _emit 0x3A
        // mov dword ptr [edx], edi
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
        _emit 0x32
        _emit 0xC0
        // xor al, al
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
    }
}

// @ 0x00a71410  (217 bytes)
__declspec(naked) void FUN_00a71410()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x0C
        // mov esi, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x25
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        // and eax, 0xff000000
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x7F
        // cmp eax, 0x7f000000
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0xD9
        // mov ebx, ecx
        _emit 0x75
        _emit 0x30
        // jne 0xa7145a
        _emit 0x8B
        _emit 0x4B
        _emit 0x14
        // mov ecx, dword ptr [ebx + 0x14]
        _emit 0x8B
        _emit 0x51
        _emit 0x2C
        // mov edx, dword ptr [ecx + 0x2c]
        _emit 0x8B
        _emit 0x14
        _emit 0x82
        // mov edx, dword ptr [edx + eax*4]
        _emit 0x8B
        _emit 0x82
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edx + 0x88]
        _emit 0x81
        _emit 0xE6
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        _emit 0x00
        // and esi, 0xffffff
        _emit 0x8B
        _emit 0x14
        _emit 0xF0
        // mov edx, dword ptr [eax + esi*8]
        _emit 0x8B
        _emit 0x44
        _emit 0xF0
        _emit 0x04
        // mov eax, dword ptr [eax + esi*8 + 4]
        _emit 0x50
        // push eax
        _emit 0x52
        // push edx
        call FUN_00a6d7b0
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x7D
        _emit 0x0C
        // jge 0xa7145f
        _emit 0x5E
        // pop esi
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
        _emit 0xC1
        _emit 0xE0
        _emit 0x18
        // shl eax, 0x18
        _emit 0x0B
        _emit 0xF0
        // or esi, eax
        _emit 0x55
        // push ebp
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        call FUN_00a70bb0
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x8B
        _emit 0x43
        _emit 0x14
        // mov eax, dword ptr [ebx + 0x14]
        _emit 0x8B
        _emit 0x57
        _emit 0x04
        // mov edx, dword ptr [edi + 4]
        _emit 0x8B
        _emit 0x12
        // mov edx, dword ptr [edx]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x8D
        _emit 0x4F
        _emit 0x04
        // lea ecx, [edi + 4]
        _emit 0x50
        // push eax
        _emit 0x53
        // push ebx
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x1C
        // mov ebp, dword ptr [esp + 0x1c]
        _emit 0x83
        _emit 0x4F
        _emit 0x2C
        _emit 0x40
        // or dword ptr [edi + 0x2c], 0x40
        _emit 0x85
        _emit 0xED
        // test ebp, ebp
        _emit 0x74
        _emit 0x30
        // je 0xa714b7
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
        _emit 0x24
        _emit 0x60
        _emit 0x45
        _emit 0x01
        // push 0x1456024
        _emit 0x68
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // push 0xd8
        call FUN_00f473a0
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0A
        // je 0xa714af
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00a70df0
        _emit 0xEB
        _emit 0x02
        // jmp 0xa714b1
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x89
        _emit 0x87
        _emit 0x7C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x17c], eax
        _emit 0x89
        _emit 0x77
        _emit 0x20
        // mov dword ptr [edi + 0x20], esi
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x7C
        _emit 0x22
        // jl 0xa714e0
        _emit 0x8B
        _emit 0x4B
        _emit 0x14
        // mov ecx, dword ptr [ebx + 0x14]
        _emit 0x8B
        _emit 0x51
        _emit 0x2C
        // mov edx, dword ptr [ecx + 0x2c]
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x81
        _emit 0xE6
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        _emit 0x00
        // and esi, 0xffffff
        _emit 0x6B
        _emit 0xF6
        _emit 0x58
        // imul esi, esi, 0x58
        _emit 0xC1
        _emit 0xF8
        _emit 0x18
        // sar eax, 0x18
        _emit 0x8B
        _emit 0x04
        _emit 0x82
        // mov eax, dword ptr [edx + eax*4]
        _emit 0x03
        _emit 0x70
        _emit 0x34
        // add esi, dword ptr [eax + 0x34]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0x56
        // push esi
        call FUN_00a82370
        _emit 0x8B
        _emit 0xC7
        // mov eax, edi
        _emit 0x5F
        // pop edi
        _emit 0x5D
        // pop ebp
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
    }
}

// @ 0x00a714f0  (137 bytes)
__declspec(naked) void FUN_00a714f0()
{
    __asm {
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xD9
        // mov ebx, ecx
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x75
        _emit 0x27
        // jne 0xa71522
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // mov edx, dword ptr [esp + 0xc]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        call FUN_00a71410
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x07
        // je 0xa7151c
        _emit 0x83
        _emit 0xC0
        _emit 0x04
        // add eax, 4
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x10
        _emit 0x00
        // ret 0x10
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x10
        _emit 0x00
        // ret 0x10
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xC1
        _emit 0xE1
        _emit 0x05
        // shl ecx, 5
        _emit 0x57
        // push edi
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0x39
        _emit 0xB1
        _emit 0xB8
        _emit 0x5E
        _emit 0x67
        _emit 0x01
        // cmp dword ptr [ecx + 0x1675eb8], esi
        _emit 0x8D
        _emit 0xB9
        _emit 0xB8
        _emit 0x5E
        _emit 0x67
        _emit 0x01
        // lea edi, [ecx + 0x1675eb8]
        _emit 0x74
        _emit 0x38
        // je 0xa71571
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x18
        // mov esi, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x4B
        _emit 0x14
        // mov ecx, dword ptr [ebx + 0x14]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x18
        // mov ebp, dword ptr [esp + 0x18]
        _emit 0x56
        // push esi
        _emit 0x55
        // push ebp
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x42
        _emit 0x70
        // mov eax, dword ptr [edx + 0x70]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x0F
        // mov ecx, dword ptr [edi]
        _emit 0x56
        // push esi
        _emit 0x50
        // push eax
        _emit 0xFF
        _emit 0xD1
        // call ecx
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x5D
        // pop ebp
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x12
        // je 0xa71571
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov eax, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x4B
        _emit 0x14
        // mov ecx, dword ptr [ebx + 0x14]
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x12
        // mov edx, dword ptr [edx]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x5F
        // pop edi
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x10
        _emit 0x00
        // ret 0x10
    }
}

// @ 0x00a71580  (582 bytes)
__declspec(naked) void FUN_00a71580()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x3C
        // sub esp, 0x3c
        _emit 0x53
        // push ebx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0x8B
        _emit 0x5F
        _emit 0x5C
        // mov ebx, dword ptr [edi + 0x5c]
        _emit 0x2B
        _emit 0x5F
        _emit 0x58
        // sub ebx, dword ptr [edi + 0x58]
        _emit 0xB9
        _emit 0xAC
        _emit 0x7B
        _emit 0x66
        _emit 0x01
        // mov ecx, 0x1667bac
        _emit 0xC1
        _emit 0xFB
        _emit 0x02
        // sar ebx, 2
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0xB8
        _emit 0xAD
        _emit 0x7B
        _emit 0x66
        _emit 0x01
        // mov eax, 0x1667bad
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ecx
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ecx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], eax
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], edx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // mov dword ptr [esp + 8], ebx
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x0F
        _emit 0x86
        _emit 0xF2
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jbe 0xa717aa
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebx, [ebx]
        _emit 0x8B
        _emit 0x47
        _emit 0x58
        // mov eax, dword ptr [edi + 0x58]
        _emit 0x8B
        _emit 0x34
        _emit 0x90
        // mov esi, dword ptr [eax + edx*4]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x58
        // mov eax, dword ptr [esp + 0x58]
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x7D
        _emit 0x15
        // jge 0xa715e4
        _emit 0x8B
        _emit 0x57
        _emit 0x30
        // mov edx, dword ptr [edi + 0x30]
        _emit 0x8B
        _emit 0x14
        _emit 0xB2
        // mov edx, dword ptr [edx + esi*4]
        _emit 0x8B
        _emit 0x52
        _emit 0x2C
        // mov edx, dword ptr [edx + 0x2c]
        _emit 0xC1
        _emit 0xEA
        _emit 0x05
        // shr edx, 5
        _emit 0xF6
        _emit 0xC2
        _emit 0x01
        // test dl, 1
        _emit 0x0F
        _emit 0x85
        _emit 0xAF
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jne 0xa71793
        _emit 0x83
        _emit 0xF8
        _emit 0x01
        // cmp eax, 1
        _emit 0x7D
        _emit 0x15
        // jge 0xa715fe
        _emit 0x8B
        _emit 0x57
        _emit 0x30
        // mov edx, dword ptr [edi + 0x30]
        _emit 0x8B
        _emit 0x14
        _emit 0xB2
        // mov edx, dword ptr [edx + esi*4]
        _emit 0x8B
        _emit 0x52
        _emit 0x2C
        // mov edx, dword ptr [edx + 0x2c]
        _emit 0xC1
        _emit 0xEA
        _emit 0x06
        // shr edx, 6
        _emit 0xF6
        _emit 0xC2
        _emit 0x01
        // test dl, 1
        _emit 0x0F
        _emit 0x85
        _emit 0x95
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jne 0xa71793
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x7D
        _emit 0x14
        // jge 0xa71617
        _emit 0x8B
        _emit 0x47
        _emit 0x30
        // mov eax, dword ptr [edi + 0x30]
        _emit 0x8B
        _emit 0x14
        _emit 0xB0
        // mov edx, dword ptr [eax + esi*4]
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0xC1
        _emit 0xE8
        _emit 0x09
        // shr eax, 9
        _emit 0xA8
        _emit 0x01
        // test al, 1
        _emit 0x0F
        _emit 0x84
        _emit 0x7C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xa71793
        _emit 0x8B
        _emit 0x57
        _emit 0x30
        // mov edx, dword ptr [edi + 0x30]
        _emit 0x8B
        _emit 0x04
        _emit 0xB2
        // mov eax, dword ptr [edx + esi*4]
        _emit 0x83
        _emit 0x78
        _emit 0x20
        _emit 0x00
        // cmp dword ptr [eax + 0x20], 0
        _emit 0x0F
        _emit 0x8C
        _emit 0x6C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jl 0xa71793
        _emit 0x3B
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // cmp ecx, dword ptr [esp + 0x1c]
        _emit 0x74
        _emit 0x0B
        // je 0xa71638
        _emit 0xC6
        _emit 0x01
        _emit 0x00
        // mov byte ptr [ecx], 0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ecx
        _emit 0x8B
        _emit 0x57
        _emit 0x30
        // mov edx, dword ptr [edi + 0x30]
        _emit 0x8B
        _emit 0x04
        _emit 0xB2
        // mov eax, dword ptr [edx + esi*4]
        _emit 0x8B
        _emit 0x40
        _emit 0x20
        // mov eax, dword ptr [eax + 0x20]
        _emit 0x8B
        _emit 0x4F
        _emit 0x14
        // mov ecx, dword ptr [edi + 0x14]
        _emit 0x8B
        _emit 0x49
        _emit 0x2C
        // mov ecx, dword ptr [ecx + 0x2c]
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0xC1
        _emit 0xF8
        _emit 0x18
        // sar eax, 0x18
        _emit 0x8B
        _emit 0x04
        _emit 0x81
        // mov eax, dword ptr [ecx + eax*4]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        _emit 0x51
        // push ecx
        _emit 0x81
        _emit 0xE2
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        _emit 0x00
        // and edx, 0xffffff
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00950ea0
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x75
        _emit 0x20
        // jne 0xa71686
        _emit 0x8B
        _emit 0x57
        _emit 0x30
        // mov edx, dword ptr [edi + 0x30]
        _emit 0x8B
        _emit 0x04
        _emit 0xB2
        // mov eax, dword ptr [edx + esi*4]
        _emit 0x8B
        _emit 0x48
        _emit 0x1C
        // mov ecx, dword ptr [eax + 0x1c]
        _emit 0x8B
        _emit 0x50
        _emit 0x18
        // mov edx, dword ptr [eax + 0x18]
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // lea eax, [esp + 0x20]
        _emit 0x68
        _emit 0x98
        _emit 0xC7
        _emit 0x3F
        _emit 0x01
        // push 0x13fc798
        _emit 0x50
        // push eax
        call FUN_00472fe0
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x54
        // mov eax, dword ptr [esp + 0x54]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x18
        // je 0xa716a6
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        call FUN_0093d5d0
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x0F
        _emit 0x84
        _emit 0xE9
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xa7178f
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // mov edx, dword ptr [esp + 0x1c]
        _emit 0xB8
        _emit 0xAC
        _emit 0x7B
        _emit 0x66
        _emit 0x01
        // mov eax, 0x1667bac
        _emit 0xB9
        _emit 0xAD
        _emit 0x7B
        _emit 0x66
        _emit 0x01
        // mov ecx, 0x1667bad
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // mov dword ptr [esp + 0x38], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        // mov dword ptr [esp + 0x3c], eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov eax, dword ptr [esp + 0x18]
        _emit 0x52
        // push edx
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // mov dword ptr [esp + 0x34], ecx
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x44
        // mov dword ptr [esp + 0x44], ecx
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x30
        // lea ecx, [esp + 0x30]
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x50
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x50], 0
        call FUN_00454cb0
        _emit 0x8B
        _emit 0x4F
        _emit 0x30
        // mov ecx, dword ptr [edi + 0x30]
        _emit 0x8B
        _emit 0x34
        _emit 0xB1
        // mov esi, dword ptr [ecx + esi*4]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x48
        // mov ebp, dword ptr [esp + 0x48]
        _emit 0x3B
        _emit 0xF5
        // cmp esi, ebp
        _emit 0x74
        _emit 0x25
        // je 0xa71716
        _emit 0x8B
        _emit 0xDD
        // mov ebx, ebp
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x08
        // je 0xa716ff
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
        _emit 0x8B
        _emit 0xEE
        // mov ebp, esi
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x48
        // mov dword ptr [esp + 0x48], ebp
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x74
        _emit 0x09
        // je 0xa71712
        _emit 0x8B
        _emit 0x13
        // mov edx, dword ptr [ebx]
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // mov ebx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x50
        // mov eax, dword ptr [esp + 0x50]
        _emit 0x8B
        _emit 0x48
        _emit 0x04
        // mov ecx, dword ptr [eax + 4]
        _emit 0x3B
        _emit 0x48
        _emit 0x08
        // cmp ecx, dword ptr [eax + 8]
        _emit 0x73
        _emit 0x16
        // jae 0xa71738
        _emit 0x8D
        _emit 0x51
        _emit 0x24
        // lea edx, [ecx + 0x24]
        _emit 0x89
        _emit 0x50
        _emit 0x04
        // mov dword ptr [eax + 4], edx
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x1D
        // je 0xa71749
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // lea eax, [esp + 0x28]
        _emit 0x50
        // push eax
        call FUN_00a69b20
        _emit 0xEB
        _emit 0x0D
        // jmp 0xa71745
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x28
        // lea edx, [esp + 0x28]
        _emit 0x52
        // push edx
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00a6b150
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x48
        // mov ebp, dword ptr [esp + 0x48]
        _emit 0x85
        _emit 0xED
        // test ebp, ebp
        _emit 0x74
        _emit 0x0A
        // je 0xa71757
        _emit 0x8B
        _emit 0x45
        _emit 0x00
        // mov eax, dword ptr [ebp]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // mov ecx, dword ptr [esp + 0x40]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // mov eax, dword ptr [esp + 0x38]
        _emit 0x2B
        _emit 0xC8
        // sub ecx, eax
        _emit 0x83
        _emit 0xF9
        _emit 0x01
        // cmp ecx, 1
        _emit 0x7E
        _emit 0x0D
        // jle 0xa71773
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x09
        // je 0xa71773
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x30
        // mov edx, dword ptr [esp + 0x30]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // mov eax, dword ptr [esp + 0x28]
        _emit 0x2B
        _emit 0xD0
        // sub edx, eax
        _emit 0x83
        _emit 0xFA
        _emit 0x01
        // cmp edx, 1
        _emit 0x7E
        _emit 0x0D
        // jle 0xa7178f
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x09
        // je 0xa7178f
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov edx, dword ptr [esp + 0x14]
        _emit 0x42
        // inc edx
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], edx
        _emit 0x3B
        _emit 0xD3
        // cmp edx, ebx
        _emit 0x0F
        _emit 0x82
        _emit 0x1C
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jb 0xa715c0
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov eax, dword ptr [esp + 0x20]
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x2B
        _emit 0xC1
        // sub eax, ecx
        _emit 0x83
        _emit 0xF8
        _emit 0x01
        // cmp eax, 1
        _emit 0x5F
        // pop edi
        _emit 0x5B
        // pop ebx
        _emit 0x7E
        _emit 0x0D
        // jle 0xa717c0
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x09
        // je 0xa717c0
        _emit 0x51
        // push ecx
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x83
        _emit 0xC4
        _emit 0x3C
        // add esp, 0x3c
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
    }
}

// @ 0x00a717d0  (317 bytes)
__declspec(naked) void FUN_00a717d0()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8B
        _emit 0x4E
        _emit 0x04
        // mov ecx, dword ptr [esi + 4]
        _emit 0x57
        // push edi
        _emit 0x3B
        _emit 0x4E
        _emit 0x08
        // cmp ecx, dword ptr [esi + 8]
        _emit 0x74
        _emit 0x48
        // je 0xa71828
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov eax, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x18
        // mov edi, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        _emit 0x3B
        _emit 0xC7
        // cmp eax, edi
        _emit 0x72
        _emit 0x07
        // jb 0xa717f5
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x73
        _emit 0x03
        // jae 0xa717f5
        _emit 0x8D
        _emit 0x58
        _emit 0x5C
        // lea ebx, [eax + 0x5c]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x09
        // je 0xa71802
        _emit 0x8D
        _emit 0x41
        _emit 0xA4
        // lea eax, [ecx - 0x5c]
        _emit 0x50
        // push eax
        call FUN_00a70cc0
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x50
        // push eax
        _emit 0x83
        _emit 0xC0
        _emit 0xA4
        // add eax, -0x5c
        _emit 0x50
        // push eax
        _emit 0x57
        // push edi
        call FUN_00a712e0
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_00a70f70
        _emit 0x83
        _emit 0x46
        _emit 0x04
        _emit 0x5C
        // add dword ptr [esi + 4], 0x5c
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x2B
        _emit 0x0E
        // sub ecx, dword ptr [esi]
        _emit 0xB8
        _emit 0xC9
        _emit 0x42
        _emit 0x16
        _emit 0xB2
        // mov eax, 0xb21642c9
        _emit 0xF7
        _emit 0xE9
        // imul ecx
        _emit 0x03
        _emit 0xD1
        // add edx, ecx
        _emit 0xC1
        _emit 0xFA
        _emit 0x06
        // sar edx, 6
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
        _emit 0x74
        _emit 0x2F
        // je 0xa7186e
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x33
        // je 0xa7187c
        _emit 0x68
        _emit 0xD1
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // push 0xd1
        _emit 0x6B
        _emit 0xC0
        _emit 0x5C
        // imul eax, eax, 0x5c
        _emit 0x68
        _emit 0x38
        _emit 0xBB
        _emit 0x3E
        _emit 0x01
        // push 0x13ebb38
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x50
        _emit 0x21
        _emit 0x3F
        _emit 0x01
        // push 0x13f2150
        _emit 0x50
        // push eax
        call FUN_00f473a0
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], eax
        _emit 0xEB
        _emit 0x16
        // jmp 0xa71884
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x10], 1
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0xEB
        _emit 0xCD
        // jmp 0xa71849
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0xc], 0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // mov ecx, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x18
        // mov edi, dword ptr [esp + 0x18]
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x2E
        // mov ebp, dword ptr [esi]
        _emit 0x51
        // push ecx
        _emit 0x57
        // push edi
        _emit 0x55
        // push ebp
        call FUN_00a70d60
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // mov edx, dword ptr [esp + 0x1c]
        _emit 0x52
        // push edx
        _emit 0x57
        // push edi
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        call FUN_00a70730
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x74
        _emit 0x0C
        // je 0xa718b8
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov eax, dword ptr [esp + 0x20]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        call FUN_00a70cc0
        _emit 0x8B
        _emit 0x6E
        _emit 0x04
        // mov ebp, dword ptr [esi + 4]
        _emit 0x83
        _emit 0xC3
        _emit 0x5C
        // add ebx, 0x5c
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x57
        // push edi
        call FUN_00a70d60
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x57
        // push edi
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // mov dword ptr [esp + 0x34], eax
        call FUN_00a70730
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x5D
        // pop ebp
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xa718eb
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xa718eb
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // mov ecx, dword ptr [esp + 0xc]
        _emit 0x6B
        _emit 0xC0
        _emit 0x5C
        // imul eax, eax, 0x5c
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x18
        // mov edx, dword ptr [esp + 0x18]
        _emit 0x03
        _emit 0xC1
        // add eax, ecx
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x0E
        // mov dword ptr [esi], ecx
        _emit 0x89
        _emit 0x56
        _emit 0x04
        // mov dword ptr [esi + 4], edx
        _emit 0x89
        _emit 0x46
        _emit 0x08
        // mov dword ptr [esi + 8], eax
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00a71910  (169 bytes)
__declspec(naked) void FUN_00a71910()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        // mov edi, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x8F
        _emit 0x48
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x148]
        _emit 0x2B
        _emit 0x8F
        _emit 0x44
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // sub ecx, dword ptr [edi + 0x144]
        _emit 0x81
        _emit 0xC7
        _emit 0x44
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // add edi, 0x144
        _emit 0xB8
        _emit 0xC9
        _emit 0x42
        _emit 0x16
        _emit 0xB2
        // mov eax, 0xb21642c9
        _emit 0xF7
        _emit 0xE9
        // imul ecx
        _emit 0x03
        _emit 0xD1
        // add edx, ecx
        _emit 0xC1
        _emit 0xFA
        _emit 0x06
        // sar edx, 6
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
        _emit 0x74
        _emit 0x3E
        // je 0xa7197c
        _emit 0x55
        // push ebp
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x8B
        _emit 0xE8
        // mov ebp, eax
        _emit 0x8B
        _emit 0x37
        // mov esi, dword ptr [edi]
        _emit 0x8B
        _emit 0x4C
        _emit 0x1E
        _emit 0x38
        // mov ecx, dword ptr [esi + ebx + 0x38]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x03
        _emit 0xF3
        // add esi, ebx
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x4E
        _emit 0x38
        // mov ecx, dword ptr [esi + 0x38]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x4E
        _emit 0x38
        // mov ecx, dword ptr [esi + 0x38]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x0E
        // je 0xa71973
        _emit 0xC7
        _emit 0x46
        _emit 0x38
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x38], 0
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x38
        // mov edx, dword ptr [eax + 0x38]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x83
        _emit 0xC3
        _emit 0x5C
        // add ebx, 0x5c
        _emit 0x83
        _emit 0xED
        _emit 0x01
        // sub ebp, 1
        _emit 0x75
        _emit 0xC8
        // jne 0xa71943
        _emit 0x5D
        // pop ebp
        _emit 0x8B
        _emit 0x1F
        // mov ebx, dword ptr [edi]
        _emit 0x8B
        _emit 0x77
        _emit 0x04
        // mov esi, dword ptr [edi + 4]
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x56
        // push esi
        call FUN_00a71260
        _emit 0x8B
        _emit 0x4F
        _emit 0x04
        // mov ecx, dword ptr [edi + 4]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_00a70980
        _emit 0x2B
        _emit 0xF3
        // sub esi, ebx
        _emit 0xB8
        _emit 0x37
        _emit 0xBD
        _emit 0xE9
        _emit 0x4D
        // mov eax, 0x4de9bd37
        _emit 0xF7
        _emit 0xEE
        // imul esi
        _emit 0x2B
        _emit 0xD6
        // sub edx, esi
        _emit 0xC1
        _emit 0xFA
        _emit 0x06
        // sar edx, 6
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
        _emit 0x6B
        _emit 0xC0
        _emit 0x5C
        // imul eax, eax, 0x5c
        _emit 0x01
        _emit 0x47
        _emit 0x04
        // add dword ptr [edi + 4], eax
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00a719c0  (59 bytes)
__declspec(naked) void FUN_00a719c0()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7E
        _emit 0x58
        // mov edi, dword ptr [esi + 0x58]
        _emit 0x3B
        _emit 0x7E
        _emit 0x5C
        // cmp edi, dword ptr [esi + 0x5c]
        _emit 0x74
        _emit 0x2A
        // je 0xa719f6
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // mov ebx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x8B
        _emit 0x4E
        _emit 0x30
        // mov ecx, dword ptr [esi + 0x30]
        _emit 0x8B
        _emit 0x04
        _emit 0x81
        // mov eax, dword ptr [ecx + eax*4]
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x7C
        _emit 0x08
        // jl 0xa719e5
        _emit 0x0F
        _emit 0xBE
        _emit 0x50
        _emit 0x23
        // movsx edx, byte ptr [eax + 0x23]
        _emit 0x3B
        _emit 0xDA
        // cmp ebx, edx
        _emit 0x75
        _emit 0x08
        // jne 0xa719ed
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00a71910
        _emit 0x83
        _emit 0xC7
        _emit 0x04
        // add edi, 4
        _emit 0x3B
        _emit 0x7E
        _emit 0x5C
        // cmp edi, dword ptr [esi + 0x5c]
        _emit 0x75
        _emit 0xDC
        // jne 0xa719d1
        _emit 0x5B
        // pop ebx
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}
