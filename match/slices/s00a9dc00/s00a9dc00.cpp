// Slice s00a9dc00: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00a79f60();
extern "C" void FUN_00a9b120();
extern "C" void FUN_00a9b780();
extern "C" void FUN_00a9d640();

// @ 0x00a9dc00  (463 bytes)
__declspec(naked) void FUN_00a9dc00()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x24
        // sub esp, 0x24
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8B
        _emit 0x4E
        _emit 0x0C
        // mov ecx, dword ptr [esi + 0xc]
        _emit 0x8B
        _emit 0x41
        _emit 0x08
        // mov eax, dword ptr [ecx + 8]
        _emit 0xC1
        _emit 0xE8
        _emit 0x1A
        // shr eax, 0x1a
        _emit 0xA8
        _emit 0x01
        // test al, 1
        _emit 0x0F
        _emit 0x84
        _emit 0x55
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xa9dd6c
        _emit 0x8B
        _emit 0x96
        _emit 0x18
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x218]
        _emit 0x3B
        _emit 0x96
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // cmp edx, dword ptr [esi + 0x21c]
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x30
        // mov ebx, dword ptr [esp + 0x30]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x43
        _emit 0x1C
        // movss xmm0, dword ptr [ebx + 0x1c]
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x7B
        _emit 0x1C
        // lea edi, [ebx + 0x1c]
        _emit 0x8D
        _emit 0x86
        _emit 0x18
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // lea eax, [esi + 0x218]
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
        _emit 0x47
        _emit 0x04
        // movss xmm0, dword ptr [edi + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // movss dword ptr [esp + 0x28], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x47
        _emit 0x08
        // movss xmm0, dword ptr [edi + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // movss dword ptr [esp + 0x2c], xmm0
        _emit 0x8D
        _emit 0x91
        _emit 0xA8
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // lea edx, [ecx + 0x2a8]
        _emit 0x74
        _emit 0x02
        // je 0xa9dc5d
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x74
        _emit 0x05
        // je 0xa9dc66
        _emit 0x8D
        _emit 0x4B
        _emit 0x08
        // lea ecx, [ebx + 8]
        _emit 0xEB
        _emit 0x02
        // jmp 0xa9dc68
        _emit 0x33
        _emit 0xC9
        // xor ecx, ecx
        _emit 0x8B
        _emit 0x46
        _emit 0x0C
        // mov eax, dword ptr [esi + 0xc]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // fld dword ptr [esp + 0x38]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x60
        _emit 0x44
        // movss xmm4, dword ptr [eax + 0x44]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0x3C
        // movss xmm1, dword ptr [eax + 0x3c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x48
        _emit 0x30
        // addss xmm1, dword ptr [eax + 0x30]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x2C
        // movss xmm0, dword ptr [eax + 0x2c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x40
        _emit 0x38
        // addss xmm0, dword ptr [eax + 0x38]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x50
        _emit 0x40
        // movss xmm2, dword ptr [eax + 0x40]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x50
        _emit 0x34
        // addss xmm2, dword ptr [eax + 0x34]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x1D
        _emit 0x64
        _emit 0x10
        _emit 0x47
        _emit 0x01
        // movss xmm3, dword ptr [0x1471064]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCB
        // mulss xmm1, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC3
        // mulss xmm0, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD3
        // mulss xmm2, xmm3
        _emit 0x0F
        _emit 0x28
        _emit 0xEC
        // movaps xmm5, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE9
        // mulss xmm5, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x6C
        _emit 0x24
        _emit 0x10
        // movss dword ptr [esp + 0x10], xmm5
        _emit 0x0F
        _emit 0x28
        _emit 0xCC
        // movaps xmm1, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCA
        // mulss xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE0
        // mulss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x64
        _emit 0x24
        _emit 0x0C
        // movss dword ptr [esp + 0xc], xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x58
        // movss xmm0, dword ptr [eax + 0x58]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0x5C
        // movss xmm1, dword ptr [eax + 0x5c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x50
        _emit 0x60
        // movss xmm2, dword ptr [eax + 0x60]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x40
        _emit 0x4C
        // addss xmm0, dword ptr [eax + 0x4c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x48
        _emit 0x50
        // addss xmm1, dword ptr [eax + 0x50]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x50
        _emit 0x54
        // addss xmm2, dword ptr [eax + 0x54]
        _emit 0x8D
        _emit 0x46
        _emit 0x30
        // lea eax, [esi + 0x30]
        _emit 0x50
        // push eax
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
        _emit 0x20
        // lea eax, [esp + 0x20]
        _emit 0x50
        // push eax
        _emit 0x52
        // push edx
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
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
        _emit 0x51
        // push ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // movss dword ptr [esp + 0x30], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // movss dword ptr [esp + 0x34], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x54
        _emit 0x24
        _emit 0x38
        // movss dword ptr [esp + 0x38], xmm2
        call FUN_00a79f60
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x3B
        // je 0xa9dd61
        _emit 0x8B
        _emit 0x76
        _emit 0x0C
        // mov esi, dword ptr [esi + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0x78
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0x278]
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
        _emit 0xF6
        _emit 0xC4
        _emit 0x44
        // test ah, 0x44
        _emit 0x7B
        _emit 0x18
        // jnp 0xa9dd56
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // fld dword ptr [esp + 0x38]
        _emit 0x53
        // push ebx
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x30
        // lea ecx, [esp + 0x30]
        _emit 0x51
        // push ecx
        _emit 0x56
        // push esi
        call FUN_00a9b120
        _emit 0x83
        _emit 0xC4
        _emit 0x14
        // add esp, 0x14
        _emit 0x5F
        // pop edi
        _emit 0x5B
        // pop ebx
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x24
        // add esp, 0x24
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x5F
        // pop edi
        _emit 0x5B
        // pop ebx
        _emit 0x32
        _emit 0xC0
        // xor al, al
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x24
        // add esp, 0x24
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x8B
        _emit 0x51
        _emit 0x08
        // mov edx, dword ptr [ecx + 8]
        _emit 0x8B
        _emit 0x41
        _emit 0x0C
        // mov eax, dword ptr [ecx + 0xc]
        _emit 0x23
        _emit 0x15
        _emit 0x34
        _emit 0x90
        _emit 0x67
        _emit 0x01
        // and edx, dword ptr [0x1679034]
        _emit 0x23
        _emit 0x05
        _emit 0x38
        _emit 0x90
        _emit 0x67
        _emit 0x01
        // and eax, dword ptr [0x1679038]
        _emit 0x0B
        _emit 0xC2
        // or eax, edx
        _emit 0x75
        _emit 0x32
        // jne 0xa9ddb4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x81
        _emit 0x68
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [ecx + 0x168]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // mulss xmm0, dword ptr [esp + 0x30]
        _emit 0x0F
        _emit 0x2F
        _emit 0x05
        _emit 0x78
        _emit 0xC4
        _emit 0x3E
        _emit 0x01
        // comiss xmm0, dword ptr [0x13ec478]
        _emit 0x77
        _emit 0x1B
        // ja 0xa9ddb4
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // fld dword ptr [esp + 0x30]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x2C
        // mov edx, dword ptr [esp + 0x2c]
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00a9b780
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x24
        // add esp, 0x24
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // fld dword ptr [esp + 0x30]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // mov eax, dword ptr [esp + 0x2c]
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00a9d640
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x24
        // add esp, 0x24
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}
