// Slice s00b60110: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00405050();
extern "C" void FUN_00454cb0();
extern "C" void FUN_0067caa0();
extern "C" void FUN_0067dd10();
extern "C" void FUN_0067dd50();
extern "C" void FUN_0067ddb0();
extern "C" void FUN_0067ddd0();
extern "C" void FUN_0067de40();
extern "C" void FUN_006962a0();
extern "C" void FUN_00760c00();
extern "C" void FUN_00760fd0();
extern "C" void FUN_007eb820();
extern "C" void FUN_00812d80();
extern "C" void FUN_00812d90();
extern "C" void FUN_0083a9f0();
extern "C" void FUN_0083b9d0();
extern "C" void FUN_0083bcd0();
extern "C" void FUN_0083c750();
extern "C" void FUN_0083c800();
extern "C" void FUN_00841000();
extern "C" void FUN_0093c570();
extern "C" void FUN_0093c5a0();
extern "C" void FUN_00a16f40();
extern "C" void FUN_00b25fb0();
extern "C" void FUN_00b3d300();
extern "C" void FUN_00b3d350();
extern "C" void FUN_00b5b800();
extern "C" void FUN_00b7e4d0();
extern "C" void FUN_00befd80();
extern "C" void FUN_00c31a00();
extern "C" void FUN_00c707e0();
extern "C" void FUN_00cd0950();
extern "C" void FUN_00cd40b0();
extern "C" void FUN_00cf2330();
extern "C" void FUN_00cf74c0();
extern "C" void FUN_00cf74f0();
extern "C" void FUN_00d272e0();
extern "C" void FUN_00f33b50();
extern "C" void FUN_00f47380();
extern "C" void FUN_00f473a0();
extern "C" void FUN_01002bd0();
extern "C" void FUN_01005180();
extern "C" void FUN_01021080();
extern "C" void FUN_01021260();
extern "C" void FUN_01021300();
extern "C" void FUN_0102f810();
extern "C" void FUN_0102fe20();

// @ 0x00b60110  (486 bytes)
__declspec(naked) void FUN_00b60110()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x10
        // sub esp, 0x10
        call FUN_01021080
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x0F
        _emit 0x85
        _emit 0xD0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jne 0xb602f0
        call FUN_00b5b800
        _emit 0x3D
        _emit 0x00
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp eax, 0x1654c00
        _emit 0x0F
        _emit 0x84
        _emit 0xC0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xb602f0
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0x56
        // push esi
        _emit 0x56
        // push esi
        _emit 0x56
        // push esi
        _emit 0x56
        // push esi
        _emit 0x68
        _emit 0xB4
        _emit 0x09
        _emit 0x3F
        _emit 0x01
        // push 0x13f09b4
        _emit 0x6A
        _emit 0x2C
        // push 0x2c
        call FUN_00f473a0
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x3B
        _emit 0xC6
        // cmp eax, esi
        _emit 0x0F
        _emit 0x84
        _emit 0x39
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xb60289
        _emit 0x89
        _emit 0x70
        _emit 0x04
        // mov dword ptr [eax + 4], esi
        _emit 0xC7
        _emit 0x00
        _emit 0x70
        _emit 0x2D
        _emit 0x46
        _emit 0x01
        // mov dword ptr [eax], 0x1462d70
        _emit 0x89
        _emit 0x70
        _emit 0x10
        // mov dword ptr [eax + 0x10], esi
        _emit 0x89
        _emit 0x70
        _emit 0x14
        // mov dword ptr [eax + 0x14], esi
        _emit 0xB9
        _emit 0xAC
        _emit 0x7B
        _emit 0x66
        _emit 0x01
        // mov ecx, 0x1667bac
        _emit 0x89
        _emit 0x48
        _emit 0x18
        // mov dword ptr [eax + 0x18], ecx
        _emit 0x89
        _emit 0x48
        _emit 0x1C
        // mov dword ptr [eax + 0x1c], ecx
        _emit 0xC7
        _emit 0x40
        _emit 0x20
        _emit 0xAD
        _emit 0x7B
        _emit 0x66
        _emit 0x01
        // mov dword ptr [eax + 0x20], 0x1667bad
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x56
        // push esi
        _emit 0x56
        // push esi
        _emit 0x56
        // push esi
        _emit 0x56
        // push esi
        _emit 0x68
        _emit 0xB4
        _emit 0x09
        _emit 0x3F
        _emit 0x01
        // push 0x13f09b4
        _emit 0x6A
        _emit 0x20
        // push 0x20
        call FUN_00f473a0
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x3B
        _emit 0xC6
        // cmp eax, esi
        _emit 0x0F
        _emit 0x84
        _emit 0xF9
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xb60290
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00760c00
        _emit 0x8B
        _emit 0xE8
        // mov ebp, eax
        _emit 0x3B
        _emit 0xEE
        // cmp ebp, esi
        _emit 0x74
        _emit 0x09
        // je 0xb601ad
        _emit 0x8B
        _emit 0x55
        _emit 0x00
        // mov edx, dword ptr [ebp]
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x53
        // push ebx
        call FUN_0067dd50
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x68
        // mov eax, dword ptr [edx + 0x68]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x7E
        _emit 0x35
        // jle 0xb601f7
        call FUN_0067dd50
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x70
        // mov eax, dword ptr [edx + 0x70]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x48
        _emit 0x04
        // mov ecx, dword ptr [eax + 4]
        _emit 0x83
        _emit 0xF9
        _emit 0x07
        // cmp ecx, 7
        _emit 0x74
        _emit 0x0A
        // je 0xb601e3
        _emit 0x83
        _emit 0xF9
        _emit 0x08
        // cmp ecx, 8
        _emit 0x74
        _emit 0x05
        // je 0xb601e3
        _emit 0x83
        _emit 0xF9
        _emit 0x0A
        // cmp ecx, 0xa
        _emit 0x75
        _emit 0x0F
        // jne 0xb601f2
        _emit 0x8B
        _emit 0x50
        _emit 0x08
        // mov edx, dword ptr [eax + 8]
        _emit 0x8B
        _emit 0x00
        // mov eax, dword ptr [eax]
        _emit 0x52
        // push edx
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        call FUN_00760fd0
        _emit 0x46
        // inc esi
        _emit 0x3B
        _emit 0xF3
        // cmp esi, ebx
        _emit 0x7C
        _emit 0xCB
        // jl 0xb601c2
        call FUN_01021260
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00c707e0
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // lea ecx, [esp + 0x14]
        _emit 0x51
        // push ecx
        call FUN_0093c570
        _emit 0x8D
        _emit 0x4F
        _emit 0x18
        // lea ecx, [edi + 0x18]
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x74
        _emit 0x0C
        // je 0xb60224
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x8B
        _emit 0x00
        // mov eax, dword ptr [eax]
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        call FUN_00454cb0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0x2B
        _emit 0xC8
        // sub ecx, eax
        _emit 0x83
        _emit 0xF9
        _emit 0x01
        // cmp ecx, 1
        _emit 0x7E
        _emit 0x0D
        // jle 0xb60240
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x09
        // je 0xb60240
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        call FUN_00b3d350
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b7e4d0
        _emit 0xD9
        _emit 0x5F
        _emit 0x08
        // fstp dword ptr [edi + 8]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0xC7
        _emit 0x47
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0xc], 1
        _emit 0x89
        _emit 0x5F
        _emit 0x28
        // mov dword ptr [edi + 0x28], ebx
        _emit 0x8B
        _emit 0x47
        _emit 0x14
        // mov eax, dword ptr [edi + 0x14]
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x74
        _emit 0x3B
        // je 0xb6029d
        _emit 0x83
        _emit 0xC0
        _emit 0x08
        // add eax, 8
        _emit 0x89
        _emit 0x5F
        _emit 0x14
        // mov dword ptr [edi + 0x14], ebx
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0x83
        _emit 0xC9
        _emit 0xFF
        // or ecx, 0xffffffff
        _emit 0xF0
        _emit 0x0F
        _emit 0xC1
        _emit 0x0A
        // lock xadd dword ptr [edx], ecx
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xF0
        _emit 0x0F
        _emit 0xC1
        _emit 0x11
        // lock xadd dword ptr [ecx], edx
        _emit 0x83
        _emit 0xFA
        _emit 0x01
        // cmp edx, 1
        _emit 0x7D
        _emit 0x19
        // jge 0xb60297
        _emit 0xBA
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, 1
        _emit 0xF0
        _emit 0x0F
        _emit 0xC1
        _emit 0x10
        // lock xadd dword ptr [eax], edx
        _emit 0xEB
        _emit 0x14
        // jmp 0xb6029d
        _emit 0x33
        _emit 0xFF
        // xor edi, edi
        _emit 0xE9
        _emit 0xEC
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jmp 0xb6017c
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0xE9
        _emit 0x16
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jmp 0xb601ad
        _emit 0x33
        _emit 0xC9
        // xor ecx, ecx
        _emit 0xF0
        _emit 0x0F
        _emit 0xC1
        _emit 0x08
        // lock xadd dword ptr [eax], ecx
        _emit 0x8B
        _emit 0x77
        _emit 0x10
        // mov esi, dword ptr [edi + 0x10]
        _emit 0x3B
        _emit 0xEE
        // cmp ebp, esi
        _emit 0x74
        _emit 0x1D
        // je 0xb602c1
        _emit 0x3B
        _emit 0xEB
        // cmp ebp, ebx
        _emit 0x74
        _emit 0x09
        // je 0xb602b1
        _emit 0x8B
        _emit 0x55
        _emit 0x00
        // mov edx, dword ptr [ebp]
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x89
        _emit 0x6F
        _emit 0x10
        // mov dword ptr [edi + 0x10], ebp
        _emit 0x3B
        _emit 0xF3
        // cmp esi, ebx
        _emit 0x74
        _emit 0x09
        // je 0xb602c1
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
        call FUN_0067ddb0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // push 0x80
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x34
        // mov eax, dword ptr [edx + 0x34]
        _emit 0x57
        // push edi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x3B
        _emit 0xEB
        // cmp ebp, ebx
        _emit 0x5B
        // pop ebx
        _emit 0x74
        _emit 0x0A
        // je 0xb602e4
        _emit 0x8B
        _emit 0x55
        _emit 0x00
        // mov edx, dword ptr [ebp]
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x17
        // mov edx, dword ptr [edi]
        _emit 0x8B
        _emit 0x42
        _emit 0x08
        // mov eax, dword ptr [edx + 8]
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
        _emit 0x5D
        // pop ebp
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00b60350  (84 bytes)
__declspec(naked) void FUN_00b60350()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        call FUN_0083c800
        _emit 0x8D
        _emit 0x7E
        _emit 0x10
        // lea edi, [esi + 0x10]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xC7
        _emit 0x06
        _emit 0x24
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // mov dword ptr [esi], 0x1462e24
        call FUN_0083a9f0
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0xFC
        _emit 0x2D
        _emit 0x46
        _emit 0x01
        // push 0x1462dfc
        _emit 0x6A
        _emit 0x02
        // push 2
        _emit 0x68
        _emit 0xF0
        _emit 0x2D
        _emit 0x46
        _emit 0x01
        // push 0x1462df0
        _emit 0x68
        _emit 0xD8
        _emit 0x2D
        _emit 0x46
        _emit 0x01
        // push 0x1462dd8
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x68
        _emit 0xD0
        _emit 0x2D
        _emit 0x46
        _emit 0x01
        // push 0x1462dd0
        _emit 0x68
        _emit 0xB8
        _emit 0x2D
        _emit 0x46
        _emit 0x01
        // push 0x1462db8
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0xB0
        _emit 0x2D
        _emit 0x46
        _emit 0x01
        // push 0x1462db0
        _emit 0x68
        _emit 0x7C
        _emit 0x2D
        _emit 0x46
        _emit 0x01
        // push 0x1462d7c
        _emit 0x57
        // push edi
        call FUN_0083bcd0
        _emit 0x83
        _emit 0xC4
        _emit 0x30
        // add esp, 0x30
        _emit 0x5F
        // pop edi
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x5E
        // pop esi
        _emit 0xC3
        // ret 
    }
}

// @ 0x00b603b0  (152 bytes)
__declspec(naked) void FUN_00b603b0()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // mov ecx, dword ptr [esp + 8]
        _emit 0x57
        // push edi
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x4E
        _emit 0x10
        // lea ecx, [esi + 0x10]
        call FUN_0083b9d0
        call FUN_0067caa0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x05
        // je 0xb603dc
        _emit 0x8D
        _emit 0x78
        _emit 0xFC
        // lea edi, [eax - 4]
        _emit 0xEB
        _emit 0x02
        // jmp 0xb603de
        _emit 0x33
        _emit 0xFF
        // xor edi, edi
        _emit 0xF6
        _emit 0x86
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x01
        // test byte ptr [esi + 0x80], 1
        _emit 0x74
        _emit 0x04
        // je 0xb603eb
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0xEB
        _emit 0x2A
        // jmp 0xb60415
        _emit 0x8B
        _emit 0x86
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x80]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xD1
        _emit 0xE9
        // shr ecx, 1
        _emit 0xF6
        _emit 0xC1
        _emit 0x01
        // test cl, 1
        _emit 0x74
        _emit 0x04
        // je 0xb603fe
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xEB
        _emit 0x17
        // jmp 0xb60415
        _emit 0xC1
        _emit 0xE8
        _emit 0x02
        // shr eax, 2
        _emit 0xA8
        _emit 0x01
        // test al, 1
        _emit 0x74
        _emit 0x17
        // je 0xb6041c
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_00812d90
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x0F
        _emit 0x94
        _emit 0xC2
        // sete dl
        _emit 0x0F
        _emit 0xB6
        _emit 0xC2
        // movzx eax, dl
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_00812d80
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_00812d90
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0xB8
        _emit 0x98
        _emit 0xD4
        _emit 0x43
        _emit 0x01
        // mov eax, 0x143d498
        _emit 0x75
        _emit 0x05
        // jne 0xb60431
        _emit 0xB8
        _emit 0x9C
        _emit 0xD4
        _emit 0x43
        _emit 0x01
        // mov eax, 0x143d49c
        _emit 0x8B
        _emit 0x4E
        _emit 0x04
        // mov ecx, dword ptr [esi + 4]
        _emit 0x50
        // push eax
        _emit 0x68
        _emit 0x3C
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // push 0x1462e3c
        _emit 0x51
        // push ecx
        call FUN_00841000
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
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

// @ 0x00b604a0  (130 bytes)
__declspec(naked) void FUN_00b604a0()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        call FUN_0083c800
        _emit 0x8D
        _emit 0x7E
        _emit 0x10
        // lea edi, [esi + 0x10]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xC7
        _emit 0x06
        _emit 0x2C
        _emit 0x2F
        _emit 0x46
        _emit 0x01
        // mov dword ptr [esi], 0x1462f2c
        call FUN_0083a9f0
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x20
        _emit 0x2F
        _emit 0x46
        _emit 0x01
        // push 0x1462f20
        _emit 0x6A
        _emit 0x05
        // push 5
        _emit 0x68
        _emit 0x18
        _emit 0x2F
        _emit 0x46
        _emit 0x01
        // push 0x1462f18
        _emit 0x68
        _emit 0x04
        _emit 0x2F
        _emit 0x46
        _emit 0x01
        // push 0x1462f04
        _emit 0x6A
        _emit 0x04
        // push 4
        _emit 0x68
        _emit 0xF4
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // push 0x1462ef4
        _emit 0x68
        _emit 0xE4
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // push 0x1462ee4
        _emit 0x6A
        _emit 0x03
        // push 3
        _emit 0x68
        _emit 0xD8
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // push 0x1462ed8
        _emit 0x68
        _emit 0xC0
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // push 0x1462ec0
        _emit 0x6A
        _emit 0x02
        // push 2
        _emit 0x68
        _emit 0xB0
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // push 0x1462eb0
        _emit 0x68
        _emit 0xA0
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // push 0x1462ea0
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x68
        _emit 0x94
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // push 0x1462e94
        _emit 0x68
        _emit 0x84
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // push 0x1462e84
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x78
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // push 0x1462e78
        _emit 0x68
        _emit 0x54
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // push 0x1462e54
        _emit 0x57
        // push edi
        _emit 0xC7
        _emit 0x86
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xd8], 0
        call FUN_0083bcd0
        _emit 0x83
        _emit 0xC4
        _emit 0x54
        // add esp, 0x54
        _emit 0x5F
        // pop edi
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x5E
        // pop esi
        _emit 0xC3
        // ret 
    }
}

// @ 0x00b60550  (731 bytes)
__declspec(naked) void FUN_00b60550()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // mov ecx, dword ptr [esp + 8]
        _emit 0x57
        // push edi
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x4E
        _emit 0x10
        // lea ecx, [esi + 0x10]
        call FUN_0083b9d0
        _emit 0x8B
        _emit 0x96
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x80]
        _emit 0xC1
        _emit 0xEA
        _emit 0x04
        // shr edx, 4
        _emit 0xF6
        _emit 0xC2
        _emit 0x01
        // test dl, 1
        _emit 0x74
        _emit 0x77
        // je 0xb605ea
        _emit 0x8B
        _emit 0x8E
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0xd8]
        _emit 0x81
        _emit 0xC6
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add esi, 0xd8
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x29
        // je 0xb605ac
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x10
        // mov edx, dword ptr [eax + 0x10]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x1E
        // je 0xb605ac
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x0D
        // je 0xb605ac
        _emit 0xC7
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi], 0
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
        call FUN_0067ddd0
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x0D
        // je 0xb605c6
        _emit 0xC7
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi], 0
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
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x8B
        _emit 0x50
        _emit 0x2C
        // mov edx, dword ptr [eax + 0x2c]
        _emit 0x56
        // push esi
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x21
        _emit 0x48
        _emit 0xF2
        _emit 0x6E
        // push 0x6ef24821
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 4], 0
        _emit 0x8B
        _emit 0x50
        _emit 0x08
        // mov edx, dword ptr [eax + 8]
        _emit 0xFF
        _emit 0xE2
        // jmp edx
        call FUN_00b5b800
        _emit 0x3D
        _emit 0x00
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp eax, 0x1654c00
        _emit 0x0F
        _emit 0x84
        _emit 0x2C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // je 0xb60826
        _emit 0x8B
        _emit 0x86
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x80]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xC1
        _emit 0xE9
        _emit 0x05
        // shr ecx, 5
        _emit 0xF6
        _emit 0xC1
        _emit 0x01
        // test cl, 1
        _emit 0x74
        _emit 0x3B
        // je 0xb60645
        _emit 0x8B
        _emit 0x8E
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0xd8]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x0F
        _emit 0x84
        _emit 0x0E
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // je 0xb60826
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x0C
        // mov eax, dword ptr [edx + 0xc]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x8E
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0xd8]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x0F
        _emit 0x84
        _emit 0xF7
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xb60826
        _emit 0xC7
        _emit 0x86
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xd8], 0
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0xA8
        _emit 0x01
        // test al, 1
        _emit 0x74
        _emit 0x77
        // je 0xb606c0
        _emit 0x8B
        _emit 0x8E
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0xd8]
        _emit 0x81
        _emit 0xC6
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add esi, 0xd8
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x29
        // je 0xb60682
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x10
        // mov eax, dword ptr [edx + 0x10]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x1E
        // je 0xb60682
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x0C
        // mov eax, dword ptr [edx + 0xc]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x0D
        // je 0xb60682
        _emit 0xC7
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi], 0
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067ddd0
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x0D
        // je 0xb6069c
        _emit 0xC7
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi], 0
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x17
        // mov edx, dword ptr [edi]
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x56
        // push esi
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0xF3
        _emit 0x1F
        _emit 0xE4
        _emit 0x91
        // push 0x91e41ff3
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 4], 0
        _emit 0x8B
        _emit 0x42
        _emit 0x08
        // mov eax, dword ptr [edx + 8]
        _emit 0xFF
        _emit 0xE0
        // jmp eax
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xD1
        _emit 0xE9
        // shr ecx, 1
        _emit 0x53
        // push ebx
        _emit 0xF6
        _emit 0xC1
        _emit 0x01
        // test cl, 1
        _emit 0x74
        _emit 0x6E
        // je 0xb60738
        _emit 0x8B
        _emit 0x8E
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0xd8]
        _emit 0x81
        _emit 0xC6
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add esi, 0xd8
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x29
        // je 0xb60703
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x10
        // mov eax, dword ptr [edx + 0x10]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x1E
        // je 0xb60703
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x0C
        // mov eax, dword ptr [edx + 0xc]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x0D
        // je 0xb60703
        _emit 0xC7
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi], 0
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067ddd0
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        _emit 0x8B
        _emit 0x3B
        // mov edi, dword ptr [ebx]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x83
        _emit 0xC7
        _emit 0x2C
        // add edi, 0x2c
        call FUN_00a16f40
        _emit 0x8B
        _emit 0x17
        // mov edx, dword ptr [edi]
        _emit 0x50
        // push eax
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x29
        _emit 0x56
        _emit 0xA7
        _emit 0x74
        // push 0x74a75629
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x5B
        // pop ebx
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 4], 0
        _emit 0x8B
        _emit 0x50
        _emit 0x08
        // mov edx, dword ptr [eax + 8]
        _emit 0xFF
        _emit 0xE2
        // jmp edx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xC1
        _emit 0xE9
        _emit 0x02
        // shr ecx, 2
        _emit 0xF6
        _emit 0xC1
        _emit 0x01
        // test cl, 1
        _emit 0x74
        _emit 0x6E
        // je 0xb607b0
        _emit 0x8B
        _emit 0x8E
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0xd8]
        _emit 0x81
        _emit 0xC6
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add esi, 0xd8
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x29
        // je 0xb6077b
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x10
        // mov eax, dword ptr [edx + 0x10]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x1E
        // je 0xb6077b
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x0C
        // mov eax, dword ptr [edx + 0xc]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x0D
        // je 0xb6077b
        _emit 0xC7
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi], 0
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067ddd0
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        _emit 0x8B
        _emit 0x3B
        // mov edi, dword ptr [ebx]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x83
        _emit 0xC7
        _emit 0x2C
        // add edi, 0x2c
        call FUN_00a16f40
        _emit 0x8B
        _emit 0x17
        // mov edx, dword ptr [edi]
        _emit 0x50
        // push eax
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x8D
        _emit 0xE8
        _emit 0x57
        _emit 0x3E
        // push 0x3e57e88d
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x5B
        // pop ebx
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 4], 0
        _emit 0x8B
        _emit 0x50
        _emit 0x08
        // mov edx, dword ptr [eax + 8]
        _emit 0xFF
        _emit 0xE2
        // jmp edx
        _emit 0xC1
        _emit 0xE8
        _emit 0x03
        // shr eax, 3
        _emit 0xA8
        _emit 0x01
        // test al, 1
        _emit 0x74
        _emit 0x6E
        // je 0xb60825
        _emit 0x8B
        _emit 0x8E
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0xd8]
        _emit 0x81
        _emit 0xC6
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add esi, 0xd8
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x29
        // je 0xb607f0
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x10
        // mov edx, dword ptr [eax + 0x10]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x1E
        // je 0xb607f0
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x0D
        // je 0xb607f0
        _emit 0xC7
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi], 0
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
        call FUN_0067ddd0
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        _emit 0x8B
        _emit 0x3B
        // mov edi, dword ptr [ebx]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x83
        _emit 0xC7
        _emit 0x2C
        // add edi, 0x2c
        call FUN_00a16f40
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x00
        _emit 0xED
        _emit 0xCA
        _emit 0x92
        // push 0x92caed00
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x5B
        // pop ebx
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 4], 0
        _emit 0x8B
        _emit 0x42
        _emit 0x08
        // mov eax, dword ptr [edx + 8]
        _emit 0xFF
        _emit 0xE0
        // jmp eax
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

// @ 0x00b60830  (63 bytes)
__declspec(naked) void FUN_00b60830()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0xC7
        _emit 0x06
        _emit 0x2C
        _emit 0x2F
        _emit 0x46
        _emit 0x01
        // mov dword ptr [esi], 0x1462f2c
        _emit 0x8B
        _emit 0x8E
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0xd8]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x07
        // je 0xb6084a
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
        _emit 0x8D
        _emit 0x4E
        _emit 0x10
        // lea ecx, [esi + 0x10]
        call FUN_00405050
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_0083c750
        _emit 0xF6
        _emit 0x44
        _emit 0x24
        _emit 0x08
        _emit 0x01
        // test byte ptr [esp + 8], 1
        _emit 0x74
        _emit 0x09
        // je 0xb60869
        _emit 0x56
        // push esi
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x5E
        // pop esi
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00b60870  (132 bytes)
__declspec(naked) void FUN_00b60870()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        call FUN_0083c800
        _emit 0x8D
        _emit 0x7E
        _emit 0x10
        // lea edi, [esi + 0x10]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xC7
        _emit 0x06
        _emit 0x20
        _emit 0x32
        _emit 0x46
        _emit 0x01
        // mov dword ptr [esi], 0x1463220
        call FUN_0083a9f0
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x20
        _emit 0x2F
        _emit 0x46
        _emit 0x01
        // push 0x1462f20
        _emit 0x6A
        _emit 0x06
        // push 6
        _emit 0x68
        _emit 0x18
        _emit 0x2F
        _emit 0x46
        _emit 0x01
        // push 0x1462f18
        _emit 0x68
        _emit 0x0C
        _emit 0x32
        _emit 0x46
        _emit 0x01
        // push 0x146320c
        _emit 0x6A
        _emit 0x05
        // push 5
        _emit 0x68
        _emit 0x00
        _emit 0x32
        _emit 0x46
        _emit 0x01
        // push 0x1463200
        _emit 0x68
        _emit 0xC0
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // push 0x1462ec0
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x68
        _emit 0xB0
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // push 0x1462eb0
        _emit 0x68
        _emit 0xDC
        _emit 0x31
        _emit 0x46
        _emit 0x01
        // push 0x14631dc
        _emit 0x6A
        _emit 0x04
        // push 4
        _emit 0x68
        _emit 0xCC
        _emit 0x31
        _emit 0x46
        _emit 0x01
        // push 0x14631cc
        _emit 0x68
        _emit 0xBC
        _emit 0x31
        _emit 0x46
        _emit 0x01
        // push 0x14631bc
        _emit 0x6A
        _emit 0x03
        // push 3
        _emit 0x68
        _emit 0xAC
        _emit 0x31
        _emit 0x46
        _emit 0x01
        // push 0x14631ac
        _emit 0x68
        _emit 0x9C
        _emit 0x31
        _emit 0x46
        _emit 0x01
        // push 0x146319c
        _emit 0x6A
        _emit 0x02
        // push 2
        _emit 0x68
        _emit 0x90
        _emit 0x31
        _emit 0x46
        _emit 0x01
        // push 0x1463190
        _emit 0x68
        _emit 0x84
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // push 0x1462e84
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x78
        _emit 0x2E
        _emit 0x46
        _emit 0x01
        // push 0x1462e78
        _emit 0x68
        _emit 0xF8
        _emit 0x30
        _emit 0x46
        _emit 0x01
        // push 0x14630f8
        _emit 0x57
        // push edi
        call FUN_0083bcd0
        _emit 0x83
        _emit 0xC4
        _emit 0x60
        // add esp, 0x60
        _emit 0x5F
        // pop edi
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x5E
        // pop esi
        _emit 0xC3
        // ret 
    }
}

// @ 0x00b60920  (219 bytes)
__declspec(naked) void FUN_00b60920()
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
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x57
        // push edi
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x4E
        _emit 0x10
        // lea ecx, [esi + 0x10]
        call FUN_0083b9d0
        _emit 0x8B
        _emit 0x15
        _emit 0xA4
        _emit 0x7A
        _emit 0x6C
        _emit 0x01
        // mov edx, dword ptr [0x16c7aa4]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ebx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ebx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], ebx
        _emit 0x8B
        _emit 0x7A
        _emit 0x18
        // mov edi, dword ptr [edx + 0x18]
        call FUN_00b5b800
        _emit 0x3D
        _emit 0x10
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp eax, 0x1654c10
        _emit 0x0F
        _emit 0x85
        _emit 0x92
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0xb609f2
        _emit 0x8B
        _emit 0x86
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x80]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xC1
        _emit 0xE9
        _emit 0x06
        // shr ecx, 6
        _emit 0xF6
        _emit 0xC1
        _emit 0x01
        // test cl, 1
        _emit 0x74
        _emit 0x06
        // je 0xb60976
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], ebx
        _emit 0xEB
        _emit 0x6C
        // jmp 0xb609e2
        _emit 0xA8
        _emit 0x01
        // test al, 1
        _emit 0x74
        _emit 0x0A
        // je 0xb60984
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        _emit 0x05
        _emit 0xFB
        _emit 0x7A
        _emit 0x29
        // mov dword ptr [esp + 0xc], 0x297afb05
        _emit 0xEB
        _emit 0x5E
        // jmp 0xb609e2
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0xD1
        _emit 0xEA
        // shr edx, 1
        _emit 0xF6
        _emit 0xC2
        _emit 0x01
        // test dl, 1
        _emit 0x74
        _emit 0x0A
        // je 0xb60997
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        _emit 0xD2
        _emit 0xE2
        _emit 0x99
        _emit 0x37
        // mov dword ptr [esp + 0xc], 0x3799e2d2
        _emit 0xEB
        _emit 0x4B
        // jmp 0xb609e2
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xC1
        _emit 0xE9
        _emit 0x02
        // shr ecx, 2
        _emit 0xF6
        _emit 0xC1
        _emit 0x01
        // test cl, 1
        _emit 0x74
        _emit 0x0A
        // je 0xb609ab
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        _emit 0x12
        _emit 0x7B
        _emit 0xDA
        _emit 0xEA
        // mov dword ptr [esp + 0xc], 0xeada7b12
        _emit 0xEB
        _emit 0x37
        // jmp 0xb609e2
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0xC1
        _emit 0xEA
        _emit 0x03
        // shr edx, 3
        _emit 0xF6
        _emit 0xC2
        _emit 0x01
        // test dl, 1
        _emit 0x74
        _emit 0x0A
        // je 0xb609bf
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        _emit 0x5F
        _emit 0xB4
        _emit 0xCE
        _emit 0xD5
        // mov dword ptr [esp + 0xc], 0xd5ceb45f
        _emit 0xEB
        _emit 0x23
        // jmp 0xb609e2
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xC1
        _emit 0xE9
        _emit 0x04
        // shr ecx, 4
        _emit 0xF6
        _emit 0xC1
        _emit 0x01
        // test cl, 1
        _emit 0x74
        _emit 0x0A
        // je 0xb609d3
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        _emit 0x51
        _emit 0xC7
        _emit 0x26
        _emit 0xB8
        // mov dword ptr [esp + 0xc], 0xb826c751
        _emit 0xEB
        _emit 0x0F
        // jmp 0xb609e2
        _emit 0xC1
        _emit 0xE8
        _emit 0x05
        // shr eax, 5
        _emit 0xA8
        _emit 0x01
        // test al, 1
        _emit 0x74
        _emit 0x08
        // je 0xb609e2
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        _emit 0x87
        _emit 0x4C
        _emit 0xCF
        _emit 0x1F
        // mov dword ptr [esp + 0xc], 0x1fcf4c87
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x74
        _emit 0x0C
        // je 0xb609f2
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // lea edx, [esp + 0xc]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_00f33b50
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
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00b60a70  (236 bytes)
__declspec(naked) void FUN_00b60a70()
{
    __asm {
        _emit 0x8B
        _emit 0x41
        _emit 0x04
        // mov eax, dword ptr [ecx + 4]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x04
        // mov edx, dword ptr [esp + 4]
        _emit 0x50
        // push eax
        _emit 0x52
        // push edx
        _emit 0x83
        _emit 0xC1
        _emit 0x10
        // add ecx, 0x10
        call FUN_0083b9d0
        call FUN_00b5b800
        _emit 0x05
        _emit 0xFF
        _emit 0xB3
        _emit 0x9A
        _emit 0xFE
        // add eax, 0xfe9ab3ff
        _emit 0x83
        _emit 0xF8
        _emit 0x0F
        // cmp eax, 0xf
        _emit 0x0F
        _emit 0x87
        _emit 0xA4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // ja 0xb60b38
        _emit 0x0F
        _emit 0xB6
        _emit 0x80
        _emit 0x4C
        _emit 0x0B
        _emit 0xB6
        _emit 0x00
        // movzx eax, byte ptr [eax + 0xb60b4c]
        _emit 0xFF
        _emit 0x24
        _emit 0x85
        _emit 0x3C
        _emit 0x0B
        _emit 0xB6
        _emit 0x00
        // jmp dword ptr [eax*4 + 0xb60b3c]
        call FUN_0067dd10
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x50
        // mov eax, dword ptr [edx + 0x50]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x38
        // mov eax, dword ptr [edx + 0x38]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x7B
        // je 0xb60b38
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x0C
        // mov eax, dword ptr [edx + 0xc]
        _emit 0x68
        _emit 0xD2
        _emit 0xEC
        _emit 0xA7
        _emit 0x02
        // push 0x2a7ecd2
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x69
        // je 0xb60b38
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00d272e0
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        call FUN_00cd40b0
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x56
        // je 0xb60b38
        call FUN_00cd40b0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x70
        // mov eax, dword ptr [edx + 0x70]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x44
        // je 0xb60b38
        call FUN_00cd40b0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x70
        // mov eax, dword ptr [edx + 0x70]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00cd0950
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        call FUN_00cf74c0
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x23
        // je 0xb60b38
        call FUN_00cf74c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00cf74f0
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x13
        // je 0xb60b38
        call FUN_00cf74c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00cf74f0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00cf2330
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0x90
        // nop 
        _emit 0xA2
        _emit 0x0A
        _emit 0xB6
        _emit 0x00
        _emit 0xD9
        // mov byte ptr [0xd900b60a], al
        _emit 0x0A
        _emit 0xB6
        _emit 0x00
        _emit 0x0C
        _emit 0x0B
        _emit 0xB6
        // or dh, byte ptr [esi - 0x49f4f400]
        _emit 0x00
        _emit 0x38
        // add byte ptr [eax], bh
        _emit 0x0B
        _emit 0xB6
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x03
        // or esi, dword ptr [esi + 0x3010000]
        _emit 0x02
        _emit 0x03
        // add al, byte ptr [ebx]
        _emit 0x03
        _emit 0x03
        // add eax, dword ptr [ebx]
        _emit 0x03
        _emit 0x03
        // add eax, dword ptr [ebx]
        _emit 0x03
        _emit 0x03
        // add eax, dword ptr [ebx]
        _emit 0x03
        _emit 0x03
        // add eax, dword ptr [ebx]
        _emit 0x03
        _emit 0x03
        // add eax, dword ptr [ebx]
        // trailing data bytes 00b60b5b..00b60b5c
        _emit 0x00
    }
}

// @ 0x00b60bb0  (133 bytes)
__declspec(naked) void FUN_00b60bb0()
{
    __asm {
        call FUN_00b5b800
        _emit 0x3D
        _emit 0x04
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp eax, 0x1654c04
        _emit 0x75
        _emit 0x26
        // jne 0xb60be2
        call FUN_00b3d300
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b25fb0
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x66
        // je 0xb60c32
        _emit 0xD9
        _emit 0x05
        _emit 0x2C
        _emit 0xC1
        _emit 0x45
        _emit 0x01
        // fld dword ptr [0x145c12c]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        call FUN_00befd80
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        call FUN_00b5b800
        _emit 0x3D
        _emit 0x05
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp eax, 0x1654c05
        _emit 0x75
        _emit 0x44
        // jne 0xb60c32
        _emit 0x57
        // push edi
        call FUN_01021300
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x74
        _emit 0x37
        // je 0xb60c31
        _emit 0x56
        // push esi
        call FUN_0102f810
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_0102fe20
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_00c31a00
        _emit 0x6A
        _emit 0x0B
        // push 0xb
        call FUN_01002bd0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_01005180
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x6A
        _emit 0x08
        // push 8
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_007eb820
        _emit 0x8B
        _emit 0x47
        _emit 0x0C
        // mov eax, dword ptr [edi + 0xc]
        _emit 0x89
        _emit 0x70
        _emit 0x1C
        // mov dword ptr [eax + 0x1c], esi
        _emit 0x5E
        // pop esi
        _emit 0x5F
        // pop edi
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00b60c70  (223 bytes)
__declspec(naked) void FUN_00b60c70()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x44
        // sub esp, 0x44
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x4C
        // mov ecx, dword ptr [esp + 0x4c]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x4E
        _emit 0x10
        // lea ecx, [esi + 0x10]
        call FUN_0083b9d0
        _emit 0x80
        _emit 0xBE
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [esi + 0xd8], 0
        _emit 0x8B
        _emit 0x96
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0xdc]
        _emit 0x6A
        _emit 0xFF
        // push -1
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        _emit 0x74
        _emit 0x36
        // je 0xb60cd2
        _emit 0x8B
        _emit 0x04
        _emit 0xD5
        _emit 0x50
        _emit 0x9D
        _emit 0x56
        _emit 0x01
        // mov eax, dword ptr [edx*8 + 0x1569d50]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        call FUN_0093c5a0
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        call FUN_0067de40
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0x52
        _emit 0x18
        // mov edx, dword ptr [edx + 0x18]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x04
        // lea ecx, [esp + 4]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // mov ecx, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
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
        _emit 0xEB
        _emit 0x67
        // jmp 0xb60d39
        _emit 0x8B
        _emit 0x04
        _emit 0xD5
        _emit 0x18
        _emit 0x9E
        _emit 0x56
        _emit 0x01
        // mov eax, dword ptr [edx*8 + 0x1569e18]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        call FUN_0093c5a0
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov edx, dword ptr [esp + 0x10]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        call FUN_006962a0
        call FUN_0067de40
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0x52
        _emit 0x10
        // mov edx, dword ptr [edx + 0x10]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // lea ecx, [esp + 0x14]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov ecx, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
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
        _emit 0x13
        // jle 0xb60d29
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xb60d29
        _emit 0x3B
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // cmp eax, dword ptr [esp + 0x24]
        _emit 0x74
        _emit 0x09
        // je 0xb60d29
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
        _emit 0x0C
        // mov edx, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
        _emit 0x2B
        _emit 0xD0
        // sub edx, eax
        _emit 0x83
        _emit 0xE2
        _emit 0xFE
        // and edx, 0xfffffffe
        _emit 0x83
        _emit 0xFA
        _emit 0x02
        // cmp edx, 2
        _emit 0x7E
        _emit 0x0D
        // jle 0xb60d48
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x09
        // je 0xb60d48
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x44
        // add esp, 0x44
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}
