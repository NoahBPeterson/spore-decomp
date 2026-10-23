// Slice s00f145a0: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_004aa350();
extern "C" void FUN_0050d4e0();
extern "C" void FUN_005c2170();
extern "C" void FUN_0062ffd0();
extern "C" void FUN_0067de40();
extern "C" void FUN_006b5240();
extern "C" void FUN_006b55c0();
extern "C" void FUN_006b5770();
extern "C" void FUN_008105b0();
extern "C" void FUN_008345c0();
extern "C" void FUN_00834e30();
extern "C" void FUN_00834fa0();
extern "C" void FUN_00881ae0();
extern "C" void FUN_00ae6710();
extern "C" void FUN_00b93c60();
extern "C" void FUN_00e09c80();
extern "C" void FUN_00e09c90();
extern "C" void FUN_00e0a640();
extern "C" void FUN_00e0a800();
extern "C" void FUN_00f137b0();
extern "C" void FUN_00f14270();
extern "C" void FUN_00f145a0();
extern "C" void FUN_00f14980();
extern "C" void FUN_00f149d0();
extern "C" void FUN_00f14b30();
extern "C" void FUN_00f47380();
extern "C" void FUN_00f473a0();
extern "C" void FUN_01022c60();
extern "C" void FUN_011e0744();

// @ 0x00f145a0  (234 bytes)
__declspec(naked) void FUN_00f145a0()
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
        _emit 0xD3
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xf14683
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0x56
        _emit 0x08
        // mov edx, dword ptr [esi + 8]
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6B
        _emit 0x04
        // mov ebp, dword ptr [ebx + 4]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xFD
        // mov edi, ebp
        _emit 0x2B
        _emit 0xF8
        // sub edi, eax
        _emit 0x2B
        _emit 0xD1
        // sub edx, ecx
        _emit 0xC1
        _emit 0xFF
        _emit 0x02
        // sar edi, 2
        _emit 0xC1
        _emit 0xFA
        _emit 0x02
        // sar edx, 2
        _emit 0x3B
        _emit 0xFA
        // cmp edi, edx
        _emit 0x76
        _emit 0x48
        // jbe 0xf14614
        _emit 0x55
        // push ebp
        _emit 0x50
        // push eax
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f137b0
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00ae6710
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xf145fb
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xf145fb
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8D
        _emit 0x14
        _emit 0xBB
        // lea edx, [ebx + edi*4]
        _emit 0x89
        _emit 0x56
        _emit 0x08
        // mov dword ptr [esi + 8], edx
        _emit 0x8B
        _emit 0xD3
        // mov edx, ebx
        _emit 0x8D
        _emit 0x04
        _emit 0xBA
        // lea eax, [edx + edi*4]
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x46
        _emit 0x04
        // mov dword ptr [esi + 4], eax
        _emit 0x5D
        // pop ebp
        _emit 0x89
        _emit 0x1E
        // mov dword ptr [esi], ebx
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
        _emit 0xD1
        // sub edx, ecx
        _emit 0xC1
        _emit 0xFA
        _emit 0x02
        // sar edx, 2
        _emit 0x51
        // push ecx
        _emit 0x3B
        _emit 0xFA
        // cmp edi, edx
        _emit 0x76
        _emit 0x42
        // jbe 0xf14663
        _emit 0x8D
        _emit 0x0C
        _emit 0x90
        // lea ecx, [eax + edx*4]
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        call FUN_0062ffd0
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0x4B
        _emit 0x04
        // mov ecx, dword ptr [ebx + 4]
        _emit 0x8B
        _emit 0x1B
        // mov ebx, dword ptr [ebx]
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0x2B
        _emit 0x16
        // sub edx, dword ptr [esi]
        _emit 0xC1
        _emit 0xFA
        _emit 0x02
        // sar edx, 2
        _emit 0x8D
        _emit 0x14
        _emit 0x93
        // lea edx, [ebx + edx*4]
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // mov ebx, dword ptr [esp + 0x20]
        _emit 0x53
        // push ebx
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // lea eax, [esp + 0x30]
        _emit 0x50
        // push eax
        call FUN_01022c60
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x83
        _emit 0xC4
        _emit 0x20
        // add esp, 0x20
        _emit 0x8D
        _emit 0x04
        _emit 0xBA
        // lea eax, [edx + edi*4]
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x46
        _emit 0x04
        // mov dword ptr [esi + 4], eax
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
        _emit 0x55
        // push ebp
        _emit 0x50
        // push eax
        call FUN_0062ffd0
        _emit 0x8B
        _emit 0x4E
        _emit 0x04
        // mov ecx, dword ptr [esi + 4]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00ae6710
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8D
        _emit 0x04
        _emit 0xBA
        // lea eax, [edx + edi*4]
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x46
        _emit 0x04
        // mov dword ptr [esi + 4], eax
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

// @ 0x00f14690  (264 bytes)
__declspec(naked) void FUN_00f14690()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x10
        // mov esi, dword ptr [esp + 0x10]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0xC7
        _emit 0x07
        _emit 0x04
        _emit 0xF6
        _emit 0x47
        _emit 0x01
        // mov dword ptr [edi], 0x147f604
        _emit 0x8B
        _emit 0x4E
        _emit 0x04
        // mov ecx, dword ptr [esi + 4]
        _emit 0x89
        _emit 0x4F
        _emit 0x04
        // mov dword ptr [edi + 4], ecx
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x06
        // je 0xf146b0
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x4E
        _emit 0x08
        // mov ecx, dword ptr [esi + 8]
        _emit 0x89
        _emit 0x4F
        _emit 0x08
        // mov dword ptr [edi + 8], ecx
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x06
        // je 0xf146c0
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x46
        _emit 0x0C
        // mov eax, dword ptr [esi + 0xc]
        _emit 0x89
        _emit 0x47
        _emit 0x0C
        // mov dword ptr [edi + 0xc], eax
        _emit 0x8B
        _emit 0x4E
        _emit 0x10
        // mov ecx, dword ptr [esi + 0x10]
        _emit 0x89
        _emit 0x4F
        _emit 0x10
        // mov dword ptr [edi + 0x10], ecx
        _emit 0x8B
        _emit 0x56
        _emit 0x14
        // mov edx, dword ptr [esi + 0x14]
        _emit 0x89
        _emit 0x57
        _emit 0x14
        // mov dword ptr [edi + 0x14], edx
        _emit 0x8B
        _emit 0x4E
        _emit 0x1C
        // mov ecx, dword ptr [esi + 0x1c]
        _emit 0x2B
        _emit 0x4E
        _emit 0x18
        // sub ecx, dword ptr [esi + 0x18]
        _emit 0x8D
        _emit 0x46
        _emit 0x24
        // lea eax, [esi + 0x24]
        _emit 0xC1
        _emit 0xF9
        _emit 0x02
        // sar ecx, 2
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x5F
        _emit 0x18
        // lea ebx, [edi + 0x18]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        call FUN_00b93c60
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x14
        // mov ebp, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x8B
        _emit 0x4E
        _emit 0x1C
        // mov ecx, dword ptr [esi + 0x1c]
        _emit 0x8B
        _emit 0x56
        _emit 0x18
        // mov edx, dword ptr [esi + 0x18]
        _emit 0x55
        // push ebp
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // lea edx, [esp + 0x24]
        _emit 0x52
        // push edx
        call FUN_01022c60
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // mov eax, dword ptr [esp + 0x28]
        _emit 0x89
        _emit 0x43
        _emit 0x04
        // mov dword ptr [ebx + 4], eax
        _emit 0x8B
        _emit 0x4E
        _emit 0x2C
        // mov ecx, dword ptr [esi + 0x2c]
        _emit 0x89
        _emit 0x4F
        _emit 0x2C
        // mov dword ptr [edi + 0x2c], ecx
        _emit 0x8B
        _emit 0x46
        _emit 0x34
        // mov eax, dword ptr [esi + 0x34]
        _emit 0x2B
        _emit 0x46
        _emit 0x30
        // sub eax, dword ptr [esi + 0x30]
        _emit 0x83
        _emit 0xC4
        _emit 0x14
        // add esp, 0x14
        _emit 0x8D
        _emit 0x56
        _emit 0x3C
        // lea edx, [esi + 0x3c]
        _emit 0x52
        // push edx
        _emit 0xC1
        _emit 0xF8
        _emit 0x02
        // sar eax, 2
        _emit 0x8D
        _emit 0x6F
        _emit 0x30
        // lea ebp, [edi + 0x30]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        call FUN_004aa350
        _emit 0x8B
        _emit 0x46
        _emit 0x30
        // mov eax, dword ptr [esi + 0x30]
        _emit 0x8B
        _emit 0x5E
        _emit 0x34
        // mov ebx, dword ptr [esi + 0x34]
        _emit 0x8B
        _emit 0x4D
        _emit 0x00
        // mov ecx, dword ptr [ebp]
        _emit 0x2B
        _emit 0xD8
        // sub ebx, eax
        _emit 0x53
        // push ebx
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        call FUN_011e0744
        _emit 0xC1
        _emit 0xFB
        _emit 0x02
        // sar ebx, 2
        _emit 0x8D
        _emit 0x04
        _emit 0x98
        // lea eax, [eax + ebx*4]
        _emit 0x89
        _emit 0x45
        _emit 0x04
        // mov dword ptr [ebp + 4], eax
        _emit 0xD9
        _emit 0x46
        _emit 0x44
        // fld dword ptr [esi + 0x44]
        _emit 0xD9
        _emit 0x5F
        _emit 0x44
        // fstp dword ptr [edi + 0x44]
        _emit 0x8D
        _emit 0x46
        _emit 0x5C
        // lea eax, [esi + 0x5c]
        _emit 0xD9
        _emit 0x46
        _emit 0x48
        // fld dword ptr [esi + 0x48]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xD9
        _emit 0x5F
        _emit 0x48
        // fstp dword ptr [edi + 0x48]
        _emit 0xD9
        _emit 0x46
        _emit 0x4C
        // fld dword ptr [esi + 0x4c]
        _emit 0xD9
        _emit 0x5F
        _emit 0x4C
        // fstp dword ptr [edi + 0x4c]
        _emit 0xD9
        _emit 0x46
        _emit 0x50
        // fld dword ptr [esi + 0x50]
        _emit 0xD9
        _emit 0x5F
        _emit 0x50
        // fstp dword ptr [edi + 0x50]
        _emit 0xD9
        _emit 0x46
        _emit 0x54
        // fld dword ptr [esi + 0x54]
        _emit 0xD9
        _emit 0x5F
        _emit 0x54
        // fstp dword ptr [edi + 0x54]
        _emit 0xD9
        _emit 0x46
        _emit 0x58
        // fld dword ptr [esi + 0x58]
        _emit 0xD9
        _emit 0x5F
        _emit 0x58
        // fstp dword ptr [edi + 0x58]
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x89
        _emit 0x4F
        _emit 0x5C
        // mov dword ptr [edi + 0x5c], ecx
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x89
        _emit 0x57
        _emit 0x60
        // mov dword ptr [edi + 0x60], edx
        _emit 0x8B
        _emit 0x48
        _emit 0x08
        // mov ecx, dword ptr [eax + 8]
        _emit 0x89
        _emit 0x4F
        _emit 0x64
        // mov dword ptr [edi + 0x64], ecx
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x89
        _emit 0x57
        _emit 0x68
        // mov dword ptr [edi + 0x68], edx
        _emit 0x8B
        _emit 0x40
        _emit 0x10
        // mov eax, dword ptr [eax + 0x10]
        _emit 0x89
        _emit 0x47
        _emit 0x6C
        // mov dword ptr [edi + 0x6c], eax
        _emit 0x8B
        _emit 0xC7
        // mov eax, edi
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

// @ 0x00f147e0  (213 bytes)
__declspec(naked) void FUN_00f147e0()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov edi, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x5F
        _emit 0x04
        // mov ebx, dword ptr [edi + 4]
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8B
        _emit 0x6E
        _emit 0x04
        // mov ebp, dword ptr [esi + 4]
        _emit 0x3B
        _emit 0xDD
        // cmp ebx, ebp
        _emit 0x74
        _emit 0x1D
        // je 0xf14811
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x74
        _emit 0x08
        // je 0xf14800
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x89
        _emit 0x5E
        _emit 0x04
        // mov dword ptr [esi + 4], ebx
        _emit 0x85
        _emit 0xED
        // test ebp, ebp
        _emit 0x74
        _emit 0x0A
        // je 0xf14811
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
        _emit 0x5F
        _emit 0x08
        // mov ebx, dword ptr [edi + 8]
        _emit 0x8B
        _emit 0x6E
        _emit 0x08
        // mov ebp, dword ptr [esi + 8]
        _emit 0x3B
        _emit 0xDD
        // cmp ebx, ebp
        _emit 0x74
        _emit 0x1D
        // je 0xf14838
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x74
        _emit 0x08
        // je 0xf14827
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x89
        _emit 0x5E
        _emit 0x08
        // mov dword ptr [esi + 8], ebx
        _emit 0x85
        _emit 0xED
        // test ebp, ebp
        _emit 0x74
        _emit 0x0A
        // je 0xf14838
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
        _emit 0x47
        _emit 0x0C
        // mov eax, dword ptr [edi + 0xc]
        _emit 0x89
        _emit 0x46
        _emit 0x0C
        // mov dword ptr [esi + 0xc], eax
        _emit 0x8B
        _emit 0x4F
        _emit 0x10
        // mov ecx, dword ptr [edi + 0x10]
        _emit 0x89
        _emit 0x4E
        _emit 0x10
        // mov dword ptr [esi + 0x10], ecx
        _emit 0x8B
        _emit 0x57
        _emit 0x14
        // mov edx, dword ptr [edi + 0x14]
        _emit 0x8D
        _emit 0x47
        _emit 0x18
        // lea eax, [edi + 0x18]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4E
        _emit 0x18
        // lea ecx, [esi + 0x18]
        _emit 0x89
        _emit 0x56
        _emit 0x14
        // mov dword ptr [esi + 0x14], edx
        call FUN_00f145a0
        _emit 0x8B
        _emit 0x4F
        _emit 0x2C
        // mov ecx, dword ptr [edi + 0x2c]
        _emit 0x8D
        _emit 0x57
        _emit 0x30
        // lea edx, [edi + 0x30]
        _emit 0x89
        _emit 0x4E
        _emit 0x2C
        // mov dword ptr [esi + 0x2c], ecx
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x4E
        _emit 0x30
        // lea ecx, [esi + 0x30]
        call FUN_0050d4e0
        _emit 0xD9
        _emit 0x47
        _emit 0x44
        // fld dword ptr [edi + 0x44]
        _emit 0xD9
        _emit 0x5E
        _emit 0x44
        // fstp dword ptr [esi + 0x44]
        _emit 0x8D
        _emit 0x47
        _emit 0x5C
        // lea eax, [edi + 0x5c]
        _emit 0xD9
        _emit 0x47
        _emit 0x48
        // fld dword ptr [edi + 0x48]
        _emit 0xD9
        _emit 0x5E
        _emit 0x48
        // fstp dword ptr [esi + 0x48]
        _emit 0xD9
        _emit 0x47
        _emit 0x4C
        // fld dword ptr [edi + 0x4c]
        _emit 0xD9
        _emit 0x5E
        _emit 0x4C
        // fstp dword ptr [esi + 0x4c]
        _emit 0xD9
        _emit 0x47
        _emit 0x50
        // fld dword ptr [edi + 0x50]
        _emit 0xD9
        _emit 0x5E
        _emit 0x50
        // fstp dword ptr [esi + 0x50]
        _emit 0xD9
        _emit 0x47
        _emit 0x54
        // fld dword ptr [edi + 0x54]
        _emit 0xD9
        _emit 0x5E
        _emit 0x54
        // fstp dword ptr [esi + 0x54]
        _emit 0xD9
        _emit 0x47
        _emit 0x58
        // fld dword ptr [edi + 0x58]
        _emit 0x5F
        // pop edi
        _emit 0xD9
        _emit 0x5E
        _emit 0x58
        // fstp dword ptr [esi + 0x58]
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x89
        _emit 0x4E
        _emit 0x5C
        // mov dword ptr [esi + 0x5c], ecx
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x89
        _emit 0x56
        _emit 0x60
        // mov dword ptr [esi + 0x60], edx
        _emit 0x8B
        _emit 0x48
        _emit 0x08
        // mov ecx, dword ptr [eax + 8]
        _emit 0x89
        _emit 0x4E
        _emit 0x64
        // mov dword ptr [esi + 0x64], ecx
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x89
        _emit 0x56
        _emit 0x68
        // mov dword ptr [esi + 0x68], edx
        _emit 0x8B
        _emit 0x40
        _emit 0x10
        // mov eax, dword ptr [eax + 0x10]
        _emit 0x89
        _emit 0x46
        _emit 0x6C
        // mov dword ptr [esi + 0x6c], eax
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

// @ 0x00f14980  (65 bytes)
__declspec(naked) void FUN_00f14980()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x4E
        _emit 0x08
        // lea ecx, [esi + 8]
        call FUN_00e0a640
        _emit 0x8D
        _emit 0x5E
        _emit 0x78
        // lea ebx, [esi + 0x78]
        _emit 0x8B
        _emit 0x73
        _emit 0x04
        // mov esi, dword ptr [ebx + 4]
        _emit 0x2B
        _emit 0x33
        // sub esi, dword ptr [ebx]
        _emit 0x33
        _emit 0xFF
        // xor edi, edi
        _emit 0xC1
        _emit 0xFE
        _emit 0x02
        // sar esi, 2
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x7E
        _emit 0x11
        // jle 0xf149af
        _emit 0x8B
        _emit 0xFF
        // mov edi, edi
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x8B
        _emit 0x0C
        _emit 0xB8
        // mov ecx, dword ptr [eax + edi*4]
        call FUN_00834e30
        _emit 0x47
        // inc edi
        _emit 0x3B
        _emit 0xFE
        // cmp edi, esi
        _emit 0x7C
        _emit 0xF1
        // jl 0xf149a0
        _emit 0x8B
        _emit 0x4B
        _emit 0x04
        // mov ecx, dword ptr [ebx + 4]
        _emit 0x8B
        _emit 0x13
        // mov edx, dword ptr [ebx]
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        call FUN_005c2170
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0xC3
        // ret 
    }
}

// @ 0x00f149d0  (350 bytes)
__declspec(naked) void FUN_00f149d0()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xD9
        // mov ebx, ecx
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x73
        _emit 0x08
        // lea esi, [ebx + 8]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00e0a800
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x0F
        _emit 0x84
        _emit 0x37
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xf14b24
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00e09c80
        _emit 0x48
        // dec eax
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00e09c90
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
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x68
        _emit 0xB4
        _emit 0x09
        _emit 0x3F
        _emit 0x01
        // push 0x13f09b4
        _emit 0x6A
        _emit 0x78
        // push 0x78
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], edi
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
        // je 0xf14a29
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_008345c0
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0xEB
        _emit 0x02
        // jmp 0xf14a2b
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], esi
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x09
        // je 0xf14a3c
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x43
        _emit 0x7C
        // mov eax, dword ptr [ebx + 0x7c]
        _emit 0x3B
        _emit 0x83
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp eax, dword ptr [ebx + 0x80]
        _emit 0x8D
        _emit 0x4B
        _emit 0x78
        // lea ecx, [ebx + 0x78]
        _emit 0x73
        _emit 0x1B
        // jae 0xf14a65
        _emit 0x8D
        _emit 0x50
        _emit 0x04
        // lea edx, [eax + 4]
        _emit 0x89
        _emit 0x51
        _emit 0x04
        // mov dword ptr [ecx + 4], edx
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x20
        // je 0xf14a74
        _emit 0x89
        _emit 0x30
        // mov dword ptr [eax], esi
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x27
        // je 0xf14a81
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0xEB
        _emit 0x0F
        // jmp 0xf14a74
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // lea edx, [esp + 0x10]
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        call FUN_00f14270
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
        // je 0xf14a81
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x50
        _emit 0x08
        // mov edx, dword ptr [eax + 8]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x43
        _emit 0x7C
        // mov eax, dword ptr [ebx + 0x7c]
        _emit 0x8B
        _emit 0x58
        _emit 0xFC
        // mov ebx, dword ptr [eax - 4]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x68
        _emit 0xC0
        _emit 0x67
        _emit 0xFB
        _emit 0x07
        // push 0x7fb67c0
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_008105b0
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x68
        _emit 0xE0
        _emit 0xE1
        _emit 0xC7
        _emit 0x07
        // push 0x7c7e1e0
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        call FUN_008105b0
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x74
        _emit 0x10
        // je 0xf14abd
        _emit 0x8B
        _emit 0x17
        // mov edx, dword ptr [edi]
        _emit 0x8B
        _emit 0x42
        _emit 0x0C
        // mov eax, dword ptr [edx + 0xc]
        _emit 0x68
        _emit 0xBD
        _emit 0xF4
        _emit 0x15
        _emit 0x0F
        // push 0xf15f4bd
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0xEB
        _emit 0x02
        // jmp 0xf14abf
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x83
        _emit 0xEC
        _emit 0x0C
        // sub esp, 0xc
        _emit 0x8B
        _emit 0xCC
        // mov ecx, esp
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x89
        _emit 0x29
        // mov dword ptr [ecx], ebp
        _emit 0x56
        // push esi
        _emit 0x89
        _emit 0x51
        _emit 0x04
        // mov dword ptr [ecx + 4], edx
        _emit 0x52
        // push edx
        _emit 0x89
        _emit 0x51
        _emit 0x08
        // mov dword ptr [ecx + 8], edx
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        call FUN_00834fa0
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x10
        // je 0xf14aee
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov eax, dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x52
        _emit 0x7C
        // mov edx, dword ptr [edx + 0x7c]
        _emit 0x50
        // push eax
        _emit 0x6A
        _emit 0x02
        // push 2
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x74
        _emit 0x11
        // je 0xf14b03
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov ecx, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x8B
        _emit 0x90
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [eax + 0x80]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
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
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x50
        // push eax
        call FUN_008105b0
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0D
        // je 0xf14b24
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x7C
        // mov eax, dword ptr [edx + 0x7c]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
    }
}

// @ 0x00f14b30  (100 bytes)
__declspec(naked) void FUN_00f14b30()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x40
        // sub esp, 0x40
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x4C
        // mov edi, dword ptr [esp + 0x4c]
        _emit 0x6A
        _emit 0x20
        // push 0x20
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // lea eax, [esp + 0xc]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xC7
        // mov eax, edi
        _emit 0x99
        // cdq 
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        call FUN_00881ae0
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        call FUN_0067de40
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x20
        // mov eax, dword ptr [edx + 0x20]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0x52
        _emit 0x34
        // mov edx, dword ptr [edx + 0x34]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // lea ecx, [esp + 0xc]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x54
        // mov eax, dword ptr [esp + 0x54]
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x0F
        _emit 0x95
        _emit 0xC1
        // setne cl
        _emit 0x0F
        _emit 0xB6
        _emit 0xD1
        // movzx edx, cl
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x50
        // mov ecx, dword ptr [esp + 0x50]
        _emit 0x50
        // push eax
        _emit 0x52
        // push edx
        call FUN_006b55c0
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f149d0
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x40
        // add esp, 0x40
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
    }
}

// @ 0x00f14ba0  (493 bytes)
__declspec(naked) void FUN_00f14ba0()
{
    __asm {
        _emit 0x81
        _emit 0xEC
        _emit 0x1C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // sub esp, 0x11c
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x9C
        _emit 0x24
        _emit 0x24
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ebx, dword ptr [esp + 0x124]
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x0F
        _emit 0x95
        _emit 0xC0
        // setne al
        _emit 0x88
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov byte ptr [esp + 8], al
        _emit 0xB8
        _emit 0x89
        _emit 0x88
        _emit 0x88
        _emit 0x88
        // mov eax, 0x88888889
        _emit 0xF7
        _emit 0xEB
        // imul ebx
        _emit 0x03
        _emit 0xD3
        // add edx, ebx
        _emit 0xC1
        _emit 0xFA
        _emit 0x05
        // sar edx, 5
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x04
        // mov dword ptr [esp + 4], ecx
        _emit 0x8B
        _emit 0xCA
        // mov ecx, edx
        _emit 0xC1
        _emit 0xE9
        _emit 0x1F
        // shr ecx, 0x1f
        _emit 0x03
        _emit 0xCA
        // add ecx, edx
        _emit 0xB8
        _emit 0x89
        _emit 0x88
        _emit 0x88
        _emit 0x88
        // mov eax, 0x88888889
        _emit 0xF7
        _emit 0xE9
        // imul ecx
        _emit 0x03
        _emit 0xD1
        // add edx, ecx
        _emit 0xC1
        _emit 0xFA
        _emit 0x05
        // sar edx, 5
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF2
        // mov esi, edx
        _emit 0xC1
        _emit 0xEE
        _emit 0x1F
        // shr esi, 0x1f
        _emit 0x03
        _emit 0xF2
        // add esi, edx
        _emit 0x8B
        _emit 0xD6
        // mov edx, esi
        _emit 0xC1
        _emit 0xE2
        _emit 0x04
        // shl edx, 4
        _emit 0x2B
        _emit 0xD6
        // sub edx, esi
        _emit 0xF7
        _emit 0xDA
        // neg edx
        _emit 0x8D
        _emit 0x2C
        _emit 0x91
        // lea ebp, [ecx + edx*4]
        _emit 0xB8
        _emit 0xAB
        _emit 0xAA
        _emit 0xAA
        _emit 0x2A
        // mov eax, 0x2aaaaaab
        _emit 0xF7
        _emit 0xEE
        // imul esi
        _emit 0x57
        // push edi
        _emit 0xC1
        _emit 0xFA
        _emit 0x02
        // sar edx, 2
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
        _emit 0xC7
        // mov eax, edi
        _emit 0x6B
        _emit 0xC0
        _emit 0xE8
        // imul eax, eax, -0x18
        _emit 0x03
        _emit 0xF0
        // add esi, eax
        _emit 0x8B
        _emit 0xC1
        // mov eax, ecx
        _emit 0xC1
        _emit 0xE0
        _emit 0x04
        // shl eax, 4
        _emit 0x2B
        _emit 0xC1
        // sub eax, ecx
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x6A
        _emit 0x20
        // push 0x20
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x30
        // lea edx, [esp + 0x30]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xC3
        // mov eax, ebx
        _emit 0x2B
        _emit 0xC1
        // sub eax, ecx
        _emit 0x99
        // cdq 
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        call FUN_00881ae0
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        call FUN_0067de40
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x20
        // mov eax, dword ptr [edx + 0x20]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0x52
        _emit 0x34
        // mov edx, dword ptr [edx + 0x34]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x30
        // lea ecx, [esp + 0x30]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x6A
        _emit 0x20
        // push 0x20
        _emit 0x8D
        _emit 0x84
        _emit 0x24
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea eax, [esp + 0xb0]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xC5
        // mov eax, ebp
        _emit 0x99
        // cdq 
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        call FUN_00881ae0
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        call FUN_0067de40
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x20
        // mov eax, dword ptr [edx + 0x20]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x8B
        _emit 0x52
        _emit 0x34
        // mov edx, dword ptr [edx + 0x34]
        _emit 0x8D
        _emit 0x8C
        _emit 0x24
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [esp + 0xb0]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x6A
        _emit 0x20
        // push 0x20
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x70
        // lea eax, [esp + 0x70]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x99
        // cdq 
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        call FUN_00881ae0
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        call FUN_0067de40
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x20
        // mov eax, dword ptr [edx + 0x20]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0x52
        _emit 0x34
        // mov edx, dword ptr [edx + 0x34]
        _emit 0x6A
        _emit 0x02
        // push 2
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x70
        // lea ecx, [esp + 0x70]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x6A
        _emit 0x20
        // push 0x20
        _emit 0x8D
        _emit 0x84
        _emit 0x24
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea eax, [esp + 0xf0]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xC7
        // mov eax, edi
        _emit 0x99
        // cdq 
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        call FUN_00881ae0
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        call FUN_0067de40
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x20
        // mov eax, dword ptr [edx + 0x20]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0x52
        _emit 0x34
        // mov edx, dword ptr [edx + 0x34]
        _emit 0x6A
        _emit 0x03
        // push 3
        _emit 0x8D
        _emit 0x8C
        _emit 0x24
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [esp + 0xf0]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x7E
        _emit 0x07
        // jle 0xf14cf8
        _emit 0x68
        _emit 0x2D
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x773632d
        _emit 0xEB
        _emit 0x51
        // jmp 0xf14d49
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x7E
        _emit 0x22
        // jle 0xf14d1e
        _emit 0x68
        _emit 0x2C
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x773632c
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // lea ecx, [esp + 0x24]
        call FUN_006b5770
        _emit 0x8B
        _emit 0x94
        _emit 0x24
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esp + 0x134]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        _emit 0xEB
        _emit 0x46
        // jmp 0xf14d64
        _emit 0x85
        _emit 0xED
        // test ebp, ebp
        _emit 0x7E
        _emit 0x22
        // jle 0xf14d44
        _emit 0x68
        _emit 0x2B
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x773632b
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // lea ecx, [esp + 0x24]
        call FUN_006b5770
        _emit 0x8B
        _emit 0x8C
        _emit 0x24
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esp + 0x134]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov edx, dword ptr [esp + 0x14]
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        _emit 0xEB
        _emit 0x20
        // jmp 0xf14d64
        _emit 0x68
        _emit 0x2A
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x773632a
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // lea ecx, [esp + 0x24]
        call FUN_006b5770
        _emit 0x8B
        _emit 0x84
        _emit 0x24
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esp + 0x134]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // lea ecx, [esp + 0x20]
        call FUN_006b55c0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x50
        // push eax
        call FUN_00f149d0
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5240
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
        _emit 0x1C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // add esp, 0x11c
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00f14d90  (828 bytes)
__declspec(naked) void FUN_00f14d90()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x14
        // sub esp, 0x14
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        call FUN_00f14980
        _emit 0x68
        _emit 0x50
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b50
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x16
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x7736316
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x24
        // mov edi, dword ptr [esp + 0x24]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x47
        _emit 0x1C
        // mov eax, dword ptr [edi + 0x1c]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x66
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b66
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x1C
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x773631c
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0x8B
        _emit 0x4F
        _emit 0x20
        // mov ecx, dword ptr [edi + 0x20]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x61
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b61
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x1D
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x773631d
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0x8B
        _emit 0x57
        _emit 0x24
        // mov edx, dword ptr [edi + 0x24]
        _emit 0x50
        // push eax
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x63
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b63
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x1E
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x773631e
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x47
        _emit 0x28
        // mov eax, dword ptr [edi + 0x28]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x62
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b62
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x23
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x7736323
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0xF3
        _emit 0x0F
        _emit 0x2C
        _emit 0x4F
        _emit 0x44
        // cvttss2si ecx, dword ptr [edi + 0x44]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x64
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b64
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x1F
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x773631f
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0xF3
        _emit 0x0F
        _emit 0x2C
        _emit 0x57
        _emit 0x40
        // cvttss2si edx, dword ptr [edi + 0x40]
        _emit 0x50
        // push eax
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x65
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b65
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x22
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x7736322
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0x50
        // push eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x2C
        _emit 0x47
        _emit 0x3C
        // cvttss2si eax, dword ptr [edi + 0x3c]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x51
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b51
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x17
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x7736317
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0x8B
        _emit 0x0F
        // mov ecx, dword ptr [edi]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x51
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b51
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x19
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x7736319
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0x8B
        _emit 0x57
        _emit 0x08
        // mov edx, dword ptr [edi + 8]
        _emit 0x50
        // push eax
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x51
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b51
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x18
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x7736318
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x47
        _emit 0x04
        // mov eax, dword ptr [edi + 4]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x51
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b51
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x24
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x7736324
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0x8B
        _emit 0x4F
        _emit 0x34
        // mov ecx, dword ptr [edi + 0x34]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x54
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b54
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x25
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x7736325
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0x8B
        _emit 0x57
        _emit 0x38
        // mov edx, dword ptr [edi + 0x38]
        _emit 0x50
        // push eax
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x52
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b52
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x1A
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x773631a
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x47
        _emit 0x10
        // mov eax, dword ptr [edi + 0x10]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x55
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b55
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x26
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x7736326
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0x8B
        _emit 0x4F
        _emit 0x0C
        // mov ecx, dword ptr [edi + 0xc]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x53
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b53
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x1B
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x773631b
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0x8B
        _emit 0x57
        _emit 0x14
        // mov edx, dword ptr [edi + 0x14]
        _emit 0x50
        // push eax
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x68
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b68
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x20
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x7736320
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x47
        _emit 0x2C
        // mov eax, dword ptr [edi + 0x2c]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x68
        _emit 0x67
        _emit 0x2B
        _emit 0xCA
        _emit 0x07
        // push 0x7ca2b67
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x21
        _emit 0x63
        _emit 0x73
        _emit 0x07
        // push 0x7736321
        _emit 0x68
        _emit 0x47
        _emit 0xB5
        _emit 0x25
        _emit 0xEA
        // push 0xea25b547
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006b5770
        _emit 0x8B
        _emit 0x4F
        _emit 0x30
        // mov ecx, dword ptr [edi + 0x30]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00f14b30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        call FUN_006b5240
        _emit 0x5F
        // pop edi
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
