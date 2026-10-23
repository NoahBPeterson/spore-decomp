// Slice s00d59b00: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_004554f0();
extern "C" void FUN_0059aed0();
extern "C" void FUN_005b2500();
extern "C" void FUN_00951740();
extern "C" void FUN_00ac0730();
extern "C" void FUN_00b2af00();
extern "C" void FUN_00b3d550();
extern "C" void FUN_00b84c80();
extern "C" void FUN_00d577b0();
extern "C" void FUN_00d58510();
extern "C" void FUN_00d592e0();
extern "C" void FUN_00d59410();
extern "C" void FUN_00d597b0();
extern "C" void FUN_00d59820();
extern "C" void FUN_00edba80();
extern "C" void FUN_00f47380();
extern "C" void FUN_00f473a0();
extern "C" void FUN_011e08c8();

// @ 0x00d59b00  (504 bytes)
__declspec(naked) void FUN_00d59b00()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x40
        // sub esp, 0x40
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // mov eax, dword ptr [esp + 0x48]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x48
        // mov esi, dword ptr [esp + 0x48]
        _emit 0x50
        // push eax
        _emit 0x56
        // push esi
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x2C
        // lea edx, [esp + 0x2c]
        _emit 0x52
        // push edx
        call FUN_00d58510
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x50
        _emit 0x5C
        // mov edx, dword ptr [eax + 0x5c]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // lea eax, [esp + 0x24]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        _emit 0x68
        _emit 0x80
        _emit 0xEC
        _emit 0x69
        _emit 0x01
        // push 0x169ec80
        _emit 0x51
        // push ecx
        call FUN_0059aed0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x58
        _emit 0x08
        // movss xmm3, dword ptr [eax + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x50
        _emit 0x04
        // movss xmm2, dword ptr [eax + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // movss xmm0, dword ptr [esp + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x08
        // movss xmm1, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC3
        // mulss xmm0, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // movss xmm3, dword ptr [esp + 0x18]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xDA
        // mulss xmm3, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // movss xmm2, dword ptr [esp + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD1
        // mulss xmm2, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x0D
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // movss xmm1, dword ptr [0x1485720]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC3
        // addss xmm0, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC2
        // addss xmm0, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x15
        _emit 0xBC
        _emit 0xB1
        _emit 0x3E
        _emit 0x01
        // movss xmm2, dword ptr [0x13eb1bc]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x0F
        _emit 0x2F
        _emit 0xC8
        // comiss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x4C
        // movss dword ptr [esp + 0x4c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // movss dword ptr [esp + 0x48], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x54
        _emit 0x24
        _emit 0x04
        // movss dword ptr [esp + 4], xmm2
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x4C
        // lea eax, [esp + 0x4c]
        _emit 0x77
        _emit 0x04
        // ja 0xd59ba0
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // lea eax, [esp + 0x48]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x00
        // movss xmm0, dword ptr [eax]
        _emit 0x0F
        _emit 0x2F
        _emit 0xC2
        // comiss xmm0, xmm2
        _emit 0x77
        _emit 0x04
        // ja 0xd59bad
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // lea eax, [esp + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x00
        // movss xmm0, dword ptr [eax]
        _emit 0x0F
        _emit 0x57
        _emit 0xC9
        // xorps xmm1, xmm1
        _emit 0x0F
        _emit 0x2F
        _emit 0xC1
        // comiss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // movss dword ptr [esp + 0x48], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x4C
        // movss dword ptr [esp + 0x4c], xmm1
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // lea eax, [esp + 0x48]
        _emit 0x77
        _emit 0x04
        // ja 0xd59bcd
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x4C
        // lea eax, [esp + 0x4c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x00
        // movss xmm0, dword ptr [eax]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // fld dword ptr [esp + 0x48]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x44
        _emit 0x24
        _emit 0x54
        // mulss xmm0, dword ptr [esp + 0x54]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x4C
        // movss dword ptr [esp + 0x4c], xmm0
        call FUN_011e08c8
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x54
        // fst dword ptr [esp + 0x54]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x48
        // fstp dword ptr [esp + 0x48]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // mov eax, dword ptr [esp + 0x48]
        _emit 0xA9
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        _emit 0x7F
        // test eax, 0x7fffffff
        _emit 0x74
        _emit 0x15
        // je 0xd59c0e
        _emit 0x05
        _emit 0x00
        _emit 0x00
        _emit 0x80
        _emit 0xFF
        // add eax, 0xff800000
        _emit 0x25
        _emit 0x00
        _emit 0x00
        _emit 0x80
        _emit 0x7F
        // and eax, 0x7f800000
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x7F
        // cmp eax, 0x7f000000
        _emit 0x0F
        _emit 0x83
        _emit 0xDF
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jae 0xd59ced
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4C
        _emit 0x24
        _emit 0x54
        // movss xmm1, dword ptr [esp + 0x54]
        _emit 0x0F
        _emit 0x2F
        _emit 0x0D
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // comiss xmm1, dword ptr [0x1485378]
        _emit 0x76
        _emit 0x37
        // jbe 0xd59c54
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x50
        // movss xmm0, dword ptr [esp + 0x50]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x44
        _emit 0x24
        _emit 0x58
        // mulss xmm0, dword ptr [esp + 0x58]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5E
        _emit 0xC1
        // divss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x0D
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // movss xmm1, dword ptr [0x1485720]
        _emit 0x0F
        _emit 0x2F
        _emit 0xC8
        // comiss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // movss dword ptr [esp + 0x48], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x54
        // movss dword ptr [esp + 0x54], xmm1
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // lea eax, [esp + 0x48]
        _emit 0x77
        _emit 0x04
        // ja 0xd59c4e
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x54
        // lea eax, [esp + 0x54]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x00
        // movss xmm0, dword ptr [eax]
        _emit 0xEB
        _emit 0x08
        // jmp 0xd59c5c
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // movss xmm0, dword ptr [0x1485720]
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x42
        _emit 0x30
        // mov eax, dword ptr [edx + 0x30]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
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
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // fld dword ptr [esp + 0x48]
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // lea ecx, [esp + 0x28]
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x40
        // lea edx, [esp + 0x40]
        _emit 0x52
        // push edx
        call FUN_005b2500
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x00
        // movss xmm0, dword ptr [eax]
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
        _emit 0x40
        _emit 0x04
        // movss xmm0, dword ptr [eax + 4]
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
        _emit 0x40
        _emit 0x08
        // movss xmm0, dword ptr [eax + 8]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // mov ecx, dword ptr [esp + 0x28]
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
        _emit 0x40
        _emit 0x0C
        // movss xmm0, dword ptr [eax + 0xc]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // mov eax, dword ptr [esp + 0x24]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x2C
        // mov edx, dword ptr [esp + 0x2c]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x38
        // mov dword ptr [esp + 0x38], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // movss dword ptr [esp + 0x30], xmm0
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // mov dword ptr [esp + 0x34], eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // mov eax, dword ptr [esp + 0x30]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // lea ecx, [esp + 0x34]
        _emit 0x51
        // push ecx
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
        call FUN_00b3d550
        _emit 0x83
        _emit 0xC4
        _emit 0x14
        // add esp, 0x14
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x0E
        // je 0xd59ced
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x52
        _emit 0x3C
        // mov edx, dword ptr [edx + 0x3c]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // lea eax, [esp + 0x24]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x4C
        // fld dword ptr [esp + 0x4c]
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x40
        // add esp, 0x40
        _emit 0xC2
        _emit 0x14
        _emit 0x00
        // ret 0x14
    }
}

// @ 0x00d59d00  (160 bytes)
__declspec(naked) void FUN_00d59d00()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x0C
        // mov esi, dword ptr [esp + 0xc]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x0C
        // mov edi, dword ptr [esp + 0xc]
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebx, [ebx]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x08
        // je 0xd59d20
        _emit 0x8D
        _emit 0x88
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [eax + 0xc0]
        _emit 0xEB
        _emit 0x02
        // jmp 0xd59d22
        _emit 0x33
        _emit 0xC9
        // xor ecx, ecx
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x07
        // je 0xd59d2f
        _emit 0x05
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add eax, 0xc0
        _emit 0xEB
        _emit 0x02
        // jmp 0xd59d31
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // lea ecx, [esp + 0x20]
        call FUN_00ac0730
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x05
        // je 0xd59d45
        _emit 0x83
        _emit 0xC7
        _emit 0x04
        // add edi, 4
        _emit 0xEB
        _emit 0xCB
        // jmp 0xd59d10
        _emit 0x8B
        _emit 0x46
        _emit 0xFC
        // mov eax, dword ptr [esi - 4]
        _emit 0x83
        _emit 0xEE
        _emit 0x04
        // sub esi, 4
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x08
        // je 0xd59d57
        _emit 0x8D
        _emit 0x88
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [eax + 0xc0]
        _emit 0xEB
        _emit 0x02
        // jmp 0xd59d59
        _emit 0x33
        _emit 0xC9
        // xor ecx, ecx
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x07
        // je 0xd59d68
        _emit 0x05
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add eax, 0xc0
        _emit 0xEB
        _emit 0x02
        // jmp 0xd59d6a
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // lea ecx, [esp + 0x20]
        call FUN_00ac0730
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x75
        _emit 0xCC
        // jne 0xd59d45
        _emit 0x3B
        _emit 0xFE
        // cmp edi, esi
        _emit 0x73
        _emit 0x0F
        // jae 0xd59d8c
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        call FUN_00b2af00
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x83
        _emit 0xC7
        _emit 0x04
        // add edi, 4
        _emit 0xEB
        _emit 0x84
        // jmp 0xd59d10
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x07
        // je 0xd59d9b
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
        _emit 0xC7
        // mov eax, edi
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0xC3
        // ret 
    }
}

// @ 0x00d59da0  (339 bytes)
__declspec(naked) void FUN_00d59da0()
{
    __asm {
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // movss xmm0, dword ptr [esp + 0x10]
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x10
        // mov ebp, dword ptr [esp + 0x10]
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov edi, dword ptr [esp + 0x14]
        _emit 0x83
        _emit 0xEC
        _emit 0x0C
        // sub esp, 0xc
        _emit 0x8B
        _emit 0xC4
        // mov eax, esp
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x00
        // movss dword ptr [eax], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // movss xmm0, dword ptr [esp + 0x30]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x40
        _emit 0x04
        // movss dword ptr [eax + 4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // movss xmm0, dword ptr [esp + 0x34]
        _emit 0x55
        // push ebp
        _emit 0x57
        // push edi
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x40
        _emit 0x08
        // movss dword ptr [eax + 8], xmm0
        call FUN_00d597b0
        _emit 0x83
        _emit 0xC4
        _emit 0x14
        // add esp, 0x14
        _emit 0x3B
        _emit 0x6C
        _emit 0x24
        _emit 0x1C
        // cmp ebp, dword ptr [esp + 0x1c]
        _emit 0x0F
        _emit 0x83
        _emit 0xDA
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jae 0xd59ebf
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x08
        // je 0xd59df3
        _emit 0x8D
        _emit 0x88
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [eax + 0xc0]
        _emit 0xEB
        _emit 0x02
        // jmp 0xd59df5
        _emit 0x33
        _emit 0xC9
        // xor ecx, ecx
        _emit 0x8B
        _emit 0x45
        _emit 0x00
        // mov eax, dword ptr [ebp]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x07
        // je 0xd59e03
        _emit 0x05
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add eax, 0xc0
        _emit 0xEB
        _emit 0x02
        // jmp 0xd59e05
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // lea ecx, [esp + 0x28]
        call FUN_00ac0730
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x0F
        _emit 0x84
        _emit 0x96
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xd59eae
        _emit 0x8B
        _emit 0x75
        _emit 0x00
        // mov esi, dword ptr [ebp]
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x08
        // je 0xd59e27
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x3F
        // mov edi, dword ptr [edi]
        _emit 0x8B
        _emit 0x5D
        _emit 0x00
        // mov ebx, dword ptr [ebp]
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x74
        _emit 0x1C
        // je 0xd59e4c
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x74
        _emit 0x08
        // je 0xd59e3c
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
        _emit 0x89
        _emit 0x7D
        _emit 0x00
        // mov dword ptr [ebp], edi
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x74
        _emit 0x09
        // je 0xd59e4c
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // movss xmm0, dword ptr [esp + 0x20]
        _emit 0x83
        _emit 0xEC
        _emit 0x0C
        // sub esp, 0xc
        _emit 0x8B
        _emit 0xC4
        // mov eax, esp
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x00
        // movss dword ptr [eax], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // movss xmm0, dword ptr [esp + 0x30]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x40
        _emit 0x04
        // movss dword ptr [eax + 4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // movss xmm0, dword ptr [esp + 0x34]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x40
        _emit 0x08
        // movss dword ptr [eax + 8], xmm0
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xC4
        // mov eax, esp
        _emit 0x89
        _emit 0x30
        // mov dword ptr [eax], esi
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x08
        // je 0xd59e82
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // mov eax, dword ptr [esp + 0x24]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // mov ecx, dword ptr [esp + 0x28]
        _emit 0x2B
        _emit 0xC8
        // sub ecx, eax
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0xC1
        _emit 0xF9
        _emit 0x02
        // sar ecx, 2
        _emit 0x51
        // push ecx
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x50
        // push eax
        call FUN_00d592e0
        _emit 0x83
        _emit 0xC4
        _emit 0x20
        // add esp, 0x20
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x09
        // je 0xd59eaa
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
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov edi, dword ptr [esp + 0x14]
        _emit 0x83
        _emit 0xC5
        _emit 0x04
        // add ebp, 4
        _emit 0x3B
        _emit 0x6C
        _emit 0x24
        _emit 0x1C
        // cmp ebp, dword ptr [esp + 0x1c]
        _emit 0x0F
        _emit 0x82
        _emit 0x2A
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jb 0xd59de5
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x18
        // mov ebp, dword ptr [esp + 0x18]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // movss xmm0, dword ptr [esp + 0x20]
        _emit 0x83
        _emit 0xEC
        _emit 0x0C
        // sub esp, 0xc
        _emit 0x8B
        _emit 0xC4
        // mov eax, esp
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x00
        // movss dword ptr [eax], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // movss xmm0, dword ptr [esp + 0x30]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x40
        _emit 0x04
        // movss dword ptr [eax + 4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // movss xmm0, dword ptr [esp + 0x34]
        _emit 0x55
        // push ebp
        _emit 0x57
        // push edi
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x40
        _emit 0x08
        // movss dword ptr [eax + 8], xmm0
        call FUN_00d59820
        _emit 0x83
        _emit 0xC4
        _emit 0x14
        // add esp, 0x14
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0xC3
        // ret 
    }
}

// @ 0x00d59f00  (262 bytes)
__declspec(naked) void FUN_00d59f00()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x57
        // push edi
        _emit 0x3B
        _emit 0x46
        _emit 0x08
        // cmp eax, dword ptr [esi + 8]
        _emit 0x74
        _emit 0x5C
        // je 0xd59f69
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov edx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0x3B
        _emit 0xCA
        // cmp ecx, edx
        _emit 0x72
        _emit 0x07
        // jb 0xd59f22
        _emit 0x3B
        _emit 0xC8
        // cmp ecx, eax
        _emit 0x73
        _emit 0x03
        // jae 0xd59f22
        _emit 0x8D
        _emit 0x79
        _emit 0x08
        // lea edi, [ecx + 8]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0B
        // je 0xd59f31
        _emit 0x8B
        _emit 0x48
        _emit 0xF8
        // mov ecx, dword ptr [eax - 8]
        _emit 0x89
        _emit 0x08
        // mov dword ptr [eax], ecx
        _emit 0x8B
        _emit 0x48
        _emit 0xFC
        // mov ecx, dword ptr [eax - 4]
        _emit 0x89
        _emit 0x48
        _emit 0x04
        // mov dword ptr [eax + 4], ecx
        _emit 0x8B
        _emit 0x4E
        _emit 0x04
        // mov ecx, dword ptr [esi + 4]
        _emit 0x8D
        _emit 0x41
        _emit 0xF8
        // lea eax, [ecx - 8]
        _emit 0x3B
        _emit 0xC2
        // cmp eax, edx
        _emit 0x74
        _emit 0x1A
        // je 0xd59f55
        _emit 0xEB
        _emit 0x03
        // jmp 0xd59f40
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0x8B
        _emit 0x58
        _emit 0xF8
        // mov ebx, dword ptr [eax - 8]
        _emit 0x83
        _emit 0xE8
        _emit 0x08
        // sub eax, 8
        _emit 0x83
        _emit 0xE9
        _emit 0x08
        // sub ecx, 8
        _emit 0x89
        _emit 0x19
        // mov dword ptr [ecx], ebx
        _emit 0x8B
        _emit 0x58
        _emit 0x04
        // mov ebx, dword ptr [eax + 4]
        _emit 0x89
        _emit 0x59
        _emit 0x04
        // mov dword ptr [ecx + 4], ebx
        _emit 0x3B
        _emit 0xC2
        // cmp eax, edx
        _emit 0x75
        _emit 0xEB
        // jne 0xd59f40
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x89
        _emit 0x02
        // mov dword ptr [edx], eax
        _emit 0x8B
        _emit 0x4F
        _emit 0x04
        // mov ecx, dword ptr [edi + 4]
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x4A
        _emit 0x04
        // mov dword ptr [edx + 4], ecx
        _emit 0x83
        _emit 0x46
        _emit 0x04
        _emit 0x08
        // add dword ptr [esi + 4], 8
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x2B
        _emit 0x06
        // sub eax, dword ptr [esi]
        _emit 0x55
        // push ebp
        _emit 0xC1
        _emit 0xF8
        _emit 0x03
        // sar eax, 3
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x76
        _emit 0x2E
        // jbe 0xd59fa1
        _emit 0x8D
        _emit 0x2C
        _emit 0x00
        // lea ebp, [eax + eax]
        _emit 0x85
        _emit 0xED
        // test ebp, ebp
        _emit 0x74
        _emit 0x2E
        // je 0xd59fa8
        _emit 0x68
        _emit 0xD1
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // push 0xd1
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
        _emit 0x8D
        _emit 0x14
        _emit 0xED
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea edx, [ebp*8]
        _emit 0x68
        _emit 0xB4
        _emit 0x09
        _emit 0x3F
        _emit 0x01
        // push 0x13f09b4
        _emit 0x52
        // push edx
        call FUN_00f473a0
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0xEB
        _emit 0x09
        // jmp 0xd59faa
        _emit 0xBD
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebp, 1
        _emit 0xEB
        _emit 0xD2
        // jmp 0xd59f7a
        _emit 0x33
        _emit 0xFF
        // xor edi, edi
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // mov ebx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x57
        // push edi
        _emit 0x53
        // push ebx
        _emit 0x50
        // push eax
        call FUN_004554f0
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0E
        // je 0xd59fcd
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x89
        _emit 0x10
        // mov dword ptr [eax], edx
        _emit 0x8B
        _emit 0x49
        _emit 0x04
        // mov ecx, dword ptr [ecx + 4]
        _emit 0x89
        _emit 0x48
        _emit 0x04
        // mov dword ptr [eax + 4], ecx
        _emit 0x8B
        _emit 0x56
        _emit 0x04
        // mov edx, dword ptr [esi + 4]
        _emit 0x83
        _emit 0xC0
        _emit 0x08
        // add eax, 8
        _emit 0x50
        // push eax
        _emit 0x52
        // push edx
        _emit 0x53
        // push ebx
        call FUN_004554f0
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0E
        // je 0xd59ff4
        _emit 0x3B
        _emit 0x46
        _emit 0x10
        // cmp eax, dword ptr [esi + 0x10]
        _emit 0x74
        _emit 0x09
        // je 0xd59ff4
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8D
        _emit 0x04
        _emit 0xEF
        // lea eax, [edi + ebp*8]
        _emit 0x5D
        // pop ebp
        _emit 0x89
        _emit 0x3E
        // mov dword ptr [esi], edi
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x5E
        _emit 0x04
        // mov dword ptr [esi + 4], ebx
        _emit 0x89
        _emit 0x46
        _emit 0x08
        // mov dword ptr [esi + 8], eax
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00d5a010  (289 bytes)
__declspec(naked) void FUN_00d5a010()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // mov ebx, dword ptr [esp + 8]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x3B
        _emit 0xDE
        // cmp ebx, esi
        _emit 0x0F
        _emit 0x84
        _emit 0x0A
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xd5a12a
        _emit 0x8B
        _emit 0x53
        _emit 0x04
        // mov edx, dword ptr [ebx + 4]
        _emit 0x8B
        _emit 0x0B
        // mov ecx, dword ptr [ebx]
        _emit 0x2B
        _emit 0xD1
        // sub edx, ecx
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
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x2E
        // mov ebp, dword ptr [esi]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xFA
        // mov edi, edx
        _emit 0xC1
        _emit 0xEF
        _emit 0x1F
        // shr edi, 0x1f
        _emit 0x03
        _emit 0xFA
        // add edi, edx
        _emit 0x8B
        _emit 0x56
        _emit 0x08
        // mov edx, dword ptr [esi + 8]
        _emit 0x2B
        _emit 0xD5
        // sub edx, ebp
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
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x3B
        _emit 0xF8
        // cmp edi, eax
        _emit 0x76
        _emit 0x42
        // jbe 0xd5a096
        _emit 0x8B
        _emit 0x53
        _emit 0x04
        // mov edx, dword ptr [ebx + 4]
        _emit 0x52
        // push edx
        _emit 0x51
        // push ecx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00d59410
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0E
        // je 0xd5a077
        _emit 0x3B
        _emit 0x46
        _emit 0x10
        // cmp eax, dword ptr [esi + 0x10]
        _emit 0x74
        _emit 0x09
        // je 0xd5a077
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8D
        _emit 0x04
        _emit 0x7F
        // lea eax, [edi + edi*2]
        _emit 0x8D
        _emit 0x0C
        _emit 0x83
        // lea ecx, [ebx + eax*4]
        _emit 0x89
        _emit 0x4E
        _emit 0x08
        // mov dword ptr [esi + 8], ecx
        _emit 0x8D
        _emit 0x04
        _emit 0x7F
        // lea eax, [edi + edi*2]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0x5F
        // pop edi
        _emit 0x8D
        _emit 0x14
        _emit 0x81
        // lea edx, [ecx + eax*4]
        _emit 0x5D
        // pop ebp
        _emit 0x89
        _emit 0x1E
        // mov dword ptr [esi], ebx
        _emit 0x89
        _emit 0x56
        _emit 0x04
        // mov dword ptr [esi + 4], edx
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0x8B
        _emit 0x56
        _emit 0x04
        // mov edx, dword ptr [esi + 4]
        _emit 0x2B
        _emit 0xD5
        // sub edx, ebp
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
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x55
        // push ebp
        _emit 0x3B
        _emit 0xF8
        // cmp edi, eax
        _emit 0x76
        _emit 0x60
        // jbe 0xd5a110
        _emit 0x8D
        _emit 0x14
        _emit 0x40
        // lea edx, [eax + eax*2]
        _emit 0x8D
        _emit 0x04
        _emit 0x91
        // lea eax, [ecx + edx*4]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        call FUN_00b84c80
        _emit 0x8B
        _emit 0x4B
        _emit 0x04
        // mov ecx, dword ptr [ebx + 4]
        _emit 0x8B
        _emit 0x6E
        _emit 0x04
        // mov ebp, dword ptr [esi + 4]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], ecx
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0x2B
        _emit 0x0E
        // sub ecx, dword ptr [esi]
        _emit 0xB8
        _emit 0xAB
        _emit 0xAA
        _emit 0xAA
        _emit 0x2A
        // mov eax, 0x2aaaaaab
        _emit 0xF7
        _emit 0xE9
        // imul ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
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
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x8D
        _emit 0x14
        _emit 0x40
        // lea edx, [eax + eax*2]
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x04
        _emit 0x90
        // lea eax, [eax + edx*4]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // mov edx, dword ptr [esp + 0x24]
        _emit 0x55
        // push ebp
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // lea eax, [esp + 0x30]
        _emit 0x50
        // push eax
        call FUN_00951740
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x83
        _emit 0xC4
        _emit 0x20
        // add esp, 0x20
        _emit 0x8D
        _emit 0x04
        _emit 0x7F
        // lea eax, [edi + edi*2]
        _emit 0x5F
        // pop edi
        _emit 0x8D
        _emit 0x14
        _emit 0x81
        // lea edx, [ecx + eax*4]
        _emit 0x5D
        // pop ebp
        _emit 0x89
        _emit 0x56
        _emit 0x04
        // mov dword ptr [esi + 4], edx
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0x8B
        _emit 0x53
        _emit 0x04
        // mov edx, dword ptr [ebx + 4]
        _emit 0x52
        // push edx
        _emit 0x51
        // push ecx
        call FUN_00b84c80
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x8D
        _emit 0x04
        _emit 0x7F
        // lea eax, [edi + edi*2]
        _emit 0x8D
        _emit 0x14
        _emit 0x81
        // lea edx, [ecx + eax*4]
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x56
        _emit 0x04
        // mov dword ptr [esi + 4], edx
        _emit 0x5D
        // pop ebp
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
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

// @ 0x00d5a140  (277 bytes)
__declspec(naked) void FUN_00d5a140()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x57
        // push edi
        _emit 0x3B
        _emit 0x46
        _emit 0x08
        // cmp eax, dword ptr [esi + 8]
        _emit 0x74
        _emit 0x5F
        // je 0xd5a1ac
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // mov ebx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        // mov edi, dword ptr [esp + 0x10]
        _emit 0x3B
        _emit 0xDF
        // cmp ebx, edi
        _emit 0x72
        _emit 0x07
        // jb 0xd5a160
        _emit 0x3B
        _emit 0xD8
        // cmp ebx, eax
        _emit 0x73
        _emit 0x03
        // jae 0xd5a160
        _emit 0x83
        _emit 0xC3
        _emit 0x10
        // add ebx, 0x10
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x17
        // je 0xd5a17b
        _emit 0x8B
        _emit 0x48
        _emit 0xF0
        // mov ecx, dword ptr [eax - 0x10]
        _emit 0x89
        _emit 0x08
        // mov dword ptr [eax], ecx
        _emit 0xD9
        _emit 0x40
        _emit 0xF4
        // fld dword ptr [eax - 0xc]
        _emit 0xD9
        _emit 0x58
        _emit 0x04
        // fstp dword ptr [eax + 4]
        _emit 0xD9
        _emit 0x40
        _emit 0xF8
        // fld dword ptr [eax - 8]
        _emit 0xD9
        _emit 0x58
        _emit 0x08
        // fstp dword ptr [eax + 8]
        _emit 0xD9
        _emit 0x40
        _emit 0xFC
        // fld dword ptr [eax - 4]
        _emit 0xD9
        _emit 0x58
        _emit 0x0C
        // fstp dword ptr [eax + 0xc]
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x50
        // push eax
        _emit 0x83
        _emit 0xC0
        _emit 0xF0
        // add eax, -0x10
        _emit 0x50
        // push eax
        _emit 0x57
        // push edi
        call FUN_00edba80
        _emit 0x8B
        _emit 0x13
        // mov edx, dword ptr [ebx]
        _emit 0x89
        _emit 0x17
        // mov dword ptr [edi], edx
        _emit 0x8B
        _emit 0x43
        _emit 0x04
        // mov eax, dword ptr [ebx + 4]
        _emit 0x89
        _emit 0x47
        _emit 0x04
        // mov dword ptr [edi + 4], eax
        _emit 0x8B
        _emit 0x4B
        _emit 0x08
        // mov ecx, dword ptr [ebx + 8]
        _emit 0x89
        _emit 0x4F
        _emit 0x08
        // mov dword ptr [edi + 8], ecx
        _emit 0x8B
        _emit 0x53
        _emit 0x0C
        // mov edx, dword ptr [ebx + 0xc]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x89
        _emit 0x57
        _emit 0x0C
        // mov dword ptr [edi + 0xc], edx
        _emit 0x83
        _emit 0x46
        _emit 0x04
        _emit 0x10
        // add dword ptr [esi + 4], 0x10
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x2B
        _emit 0x06
        // sub eax, dword ptr [esi]
        _emit 0xC1
        _emit 0xF8
        _emit 0x04
        // sar eax, 4
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x76
        _emit 0x2C
        // jbe 0xd5a1e1
        _emit 0x8D
        _emit 0x3C
        _emit 0x00
        // lea edi, [eax + eax]
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x74
        _emit 0x2C
        // je 0xd5a1e8
        _emit 0x68
        _emit 0xD1
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // push 0xd1
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
        _emit 0x8B
        _emit 0xC7
        // mov eax, edi
        _emit 0xC1
        _emit 0xE0
        _emit 0x04
        // shl eax, 4
        _emit 0x68
        _emit 0xB4
        _emit 0x09
        _emit 0x3F
        _emit 0x01
        // push 0x13f09b4
        _emit 0x50
        // push eax
        call FUN_00f473a0
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        _emit 0xEB
        _emit 0x09
        // jmp 0xd5a1ea
        _emit 0xBF
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edi, 1
        _emit 0xEB
        _emit 0xD4
        // jmp 0xd5a1bc
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x14
        // mov ebp, dword ptr [esp + 0x14]
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x50
        // push eax
        call FUN_00d577b0
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x1A
        // je 0xd5a21a
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x89
        _emit 0x10
        // mov dword ptr [eax], edx
        _emit 0xD9
        _emit 0x41
        _emit 0x04
        // fld dword ptr [ecx + 4]
        _emit 0xD9
        _emit 0x58
        _emit 0x04
        // fstp dword ptr [eax + 4]
        _emit 0xD9
        _emit 0x41
        _emit 0x08
        // fld dword ptr [ecx + 8]
        _emit 0xD9
        _emit 0x58
        _emit 0x08
        // fstp dword ptr [eax + 8]
        _emit 0xD9
        _emit 0x41
        _emit 0x0C
        // fld dword ptr [ecx + 0xc]
        _emit 0xD9
        _emit 0x58
        _emit 0x0C
        // fstp dword ptr [eax + 0xc]
        _emit 0x8B
        _emit 0x4E
        _emit 0x04
        // mov ecx, dword ptr [esi + 4]
        _emit 0x83
        _emit 0xC0
        _emit 0x10
        // add eax, 0x10
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x55
        // push ebp
        call FUN_00d577b0
        _emit 0x8B
        _emit 0xE8
        // mov ebp, eax
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0E
        // je 0xd5a241
        _emit 0x3B
        _emit 0x46
        _emit 0x10
        // cmp eax, dword ptr [esi + 0x10]
        _emit 0x74
        _emit 0x09
        // je 0xd5a241
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0xC1
        _emit 0xE7
        _emit 0x04
        // shl edi, 4
        _emit 0x03
        _emit 0xFB
        // add edi, ebx
        _emit 0x89
        _emit 0x6E
        _emit 0x04
        // mov dword ptr [esi + 4], ebp
        _emit 0x5D
        // pop ebp
        _emit 0x89
        _emit 0x7E
        _emit 0x08
        // mov dword ptr [esi + 8], edi
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x1E
        // mov dword ptr [esi], ebx
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}
