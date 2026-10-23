#include "types.h"

extern "C" void FUN_0067caa0();
extern "C" void FUN_0067dcc0();
extern "C" void FUN_0067dd60();
extern "C" void FUN_006a17e0();
extern "C" void FUN_006a25a0();
extern "C" void FUN_00ac1500();
extern "C" void FUN_00ac4f50();
extern "C" void FUN_00ac7080();
extern "C" void FUN_00ac79d0();
extern "C" void FUN_00ac7a40();
extern "C" void FUN_00acd210();
extern "C" void FUN_00ad0bd0();
extern "C" void FUN_00ad2560();
extern "C" void FUN_00ae7de0();
extern "C" void FUN_00ae7df0();
extern "C" void FUN_00aeb680();
extern "C" void FUN_00aeb700();
extern "C" void FUN_00af0f30();
extern "C" void FUN_00af1020();
extern "C" void FUN_00af13b0();
extern "C" void FUN_00b0c190();
extern "C" void FUN_00b0c520();
extern "C" void FUN_00b26320();
extern "C" void FUN_00b26600();
extern "C" void FUN_00b267c0();
extern "C" void FUN_00b2f680();
extern "C" void FUN_00b2f710();
extern "C" void FUN_00b33d00();
extern "C" void FUN_00b33d40();
extern "C" void FUN_00b33dd0();
extern "C" void FUN_00b3d240();
extern "C" void FUN_00b3d260();
extern "C" void FUN_00b3d290();
extern "C" void FUN_00b3d2a0();
extern "C" void FUN_00b3d2b0();
extern "C" void FUN_00b3d300();
extern "C" void FUN_00b3d310();
extern "C" void FUN_00b3d340();
extern "C" void FUN_00b3d350();
extern "C" void FUN_00b3d360();
extern "C" void FUN_00b3d370();
extern "C" void FUN_00b3d3b0();
extern "C" void FUN_00b3d3c0();
extern "C" void FUN_00b3d3e0();
extern "C" void FUN_00b3d400();
extern "C" void FUN_00b3d410();
extern "C" void FUN_00b3d420();
extern "C" void FUN_00b3d430();
extern "C" void FUN_00b3d440();
extern "C" void FUN_00b3d480();
extern "C" void FUN_00b3d490();
extern "C" void FUN_00b3d4a0();
extern "C" void FUN_00b3d4c0();
extern "C" void FUN_00b3d7a0();
extern "C" void FUN_00b4b7b0();
extern "C" void FUN_00b79a50();
extern "C" void FUN_00b79aa0();
extern "C" void FUN_00b7dec0();
extern "C" void FUN_00b7f390();
extern "C" void FUN_00b8d2f0();
extern "C" void FUN_00b8ff60();
extern "C" void FUN_00b90480();
extern "C" void FUN_00ba3310();
extern "C" void FUN_00ba51f0();
extern "C" void FUN_00ba70b0();
extern "C" void FUN_00ba8160();
extern "C" void FUN_00bad810();
extern "C" void FUN_00bb7620();
extern "C" void FUN_00bb8b20();
extern "C" void FUN_00bbfe80();
extern "C" void FUN_00bc20e0();
extern "C" void FUN_00bc8000();
extern "C" void FUN_00bc8040();
extern "C" void FUN_00bc8200();
extern "C" void FUN_00bc83f0();
extern "C" void FUN_00bcb6c0();
extern "C" void FUN_00bcb700();
extern "C" void FUN_00c2e4e0();
extern "C" void FUN_00cd3440();
extern "C" void FUN_00cd40b0();
extern "C" void FUN_00cd56e0();
extern "C" void FUN_00cf74c0();
extern "C" void FUN_00cf8fd0();
extern "C" void FUN_00d004b0();
extern "C" void FUN_00d37cb0();
extern "C" void FUN_00d38840();
extern "C" void FUN_00d392f0();
extern "C" void FUN_00dd6d70();
extern "C" void FUN_00dd8da0();
extern "C" void FUN_00e15a10();
extern "C" void FUN_00e180d0();
extern "C" void FUN_00e18340();
extern "C" void FUN_00e3c760();
extern "C" void FUN_00e4bc70();
extern "C" void FUN_00fd9c60();
extern "C" void FUN_00fdbee0();
extern "C" void FUN_00fdc710();
extern "C" void FUN_00fe0160();
extern "C" void FUN_00fe0570();
extern "C" void FUN_00fe19a0();
extern "C" void FUN_01021080();
extern "C" void FUN_01021960();
extern "C" void FUN_010219b0();
extern "C" void FUN_01022460();
extern "C" void FUN_01022580();

// @ 0x00b328e0  (132 bytes)
__declspec(naked) void FUN_00b328e0()
{
    __asm {
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x0D
        _emit 0x18
        _emit 0xD9
        _emit 0x5F
        _emit 0x01
        // mov ecx, dword ptr [0x15fd918]
        _emit 0x56
        // push esi
        _emit 0x68
        _emit 0xF9
        _emit 0x9B
        _emit 0x43
        _emit 0x66
        // push 0x66439bf9
        call FUN_006a25a0
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x0C
        // mov esi, dword ptr [esp + 0xc]
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x33
        // je 0xb3292d
        _emit 0x8D
        _emit 0x86
        _emit 0x00
        _emit 0xB4
        _emit 0x9A
        _emit 0xFE
        // lea eax, [esi - 0x1654c00]
        _emit 0x83
        _emit 0xF8
        _emit 0x05
        // cmp eax, 5
        _emit 0x77
        _emit 0x0E
        // ja 0xb32913
        _emit 0xFF
        _emit 0x24
        _emit 0x85
        _emit 0x4C
        _emit 0x29
        _emit 0xB3
        _emit 0x00
        // jmp dword ptr [eax*4 + 0xb3294c]
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x04
        _emit 0x01
        // mov byte ptr [esp + 4], 1
        _emit 0xEB
        _emit 0x05
        // jmp 0xb32918
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x04
        _emit 0x00
        // mov byte ptr [esp + 4], 0
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
        _emit 0x8B
        _emit 0x0D
        _emit 0x18
        _emit 0xD9
        _emit 0x5F
        _emit 0x01
        // mov ecx, dword ptr [0x15fd918]
        _emit 0x50
        // push eax
        _emit 0x68
        _emit 0x50
        _emit 0xE2
        _emit 0xF9
        _emit 0xC3
        // push 0xc3f9e250
        call FUN_006a17e0
        _emit 0x56
        // push esi
        call FUN_00b3d490
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ae7df0
        _emit 0x6A
        _emit 0x00
        // push 0
        call FUN_00b3d3e0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00dd8da0
        _emit 0x5E
        // pop esi
        _emit 0x59
        // pop ecx
        _emit 0xC3
        // ret 
        _emit 0x90
        // nop 
        _emit 0x0C
        _emit 0x29
        // or al, 0x29
        _emit 0xB3
        _emit 0x00
        // mov bl, 0
        _emit 0x0C
        _emit 0x29
        // or al, 0x29
        _emit 0xB3
        _emit 0x00
        // mov bl, 0
        _emit 0x0C
        _emit 0x29
        // or al, 0x29
        _emit 0xB3
        _emit 0x00
        // mov bl, 0
        _emit 0x13
        _emit 0x29
        // adc ebp, dword ptr [ecx]
        _emit 0xB3
        _emit 0x00
        // mov bl, 0
        _emit 0x13
        _emit 0x29
        // adc ebp, dword ptr [ecx]
        _emit 0xB3
        _emit 0x00
        // mov bl, 0
        _emit 0x13
        _emit 0x29
        // adc ebp, dword ptr [ecx]
        _emit 0xB3
        _emit 0x00
        // mov bl, 0
    }
}

// @ 0x00b32970  (152 bytes)
__declspec(naked) void FUN_00b32970()
{
    __asm {
        call FUN_0067dd60
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x18
        // mov eax, dword ptr [edx + 0x18]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00b3d3e0
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x24
        // je 0xb329ab
        _emit 0x6A
        _emit 0x01
        // push 1
        call FUN_00b3d3e0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00dd8da0
        _emit 0x81
        _emit 0x7C
        _emit 0x24
        _emit 0x04
        _emit 0xA1
        _emit 0xDB
        _emit 0xDB
        _emit 0x00
        // cmp dword ptr [esp + 4], 0xdbdba1
        _emit 0x74
        _emit 0x0C
        // je 0xb329ab
        call FUN_00b3d3e0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00dd6d70
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0x05
        _emit 0xFF
        _emit 0xB3
        _emit 0x9A
        _emit 0xFE
        // add eax, 0xfe9ab3ff
        _emit 0x83
        _emit 0xF8
        _emit 0x04
        // cmp eax, 4
        _emit 0x77
        _emit 0x39
        // ja 0xb329f2
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0x24
        _emit 0x85
        _emit 0xF4
        _emit 0x29
        _emit 0xB3
        _emit 0x00
        // jmp dword ptr [eax*4 + 0xb329f4]
        _emit 0xBE
        _emit 0x64
        _emit 0x56
        _emit 0xB0
        _emit 0x26
        // mov esi, 0x26b05664
        _emit 0xEB
        _emit 0x13
        // jmp 0xb329db
        _emit 0xBE
        _emit 0x07
        _emit 0x7C
        _emit 0x94
        _emit 0x24
        // mov esi, 0x24947c07
        _emit 0xEB
        _emit 0x0C
        // jmp 0xb329db
        _emit 0xBE
        _emit 0x28
        _emit 0x5C
        _emit 0xB0
        _emit 0x2A
        // mov esi, 0x2ab05c28
        _emit 0xEB
        _emit 0x05
        // jmp 0xb329db
        _emit 0xBE
        _emit 0xDE
        _emit 0xB6
        _emit 0x87
        _emit 0x28
        // mov esi, 0x2887b6de
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x14
        // mov eax, dword ptr [edx + 0x14]
        _emit 0x68
        _emit 0x12
        _emit 0x97
        _emit 0x57
        _emit 0x06
        // push 0x6579712
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x5E
        // pop esi
        _emit 0xC3
        // ret 
        _emit 0x90
        // nop 
        _emit 0xC1
        _emit 0x29
        _emit 0xB3
        // shr dword ptr [ecx], 0xb3
        _emit 0x00
        _emit 0xC8
        // add al, cl
        _emit 0x29
        _emit 0xB3
        _emit 0x00
        _emit 0xF1
        _emit 0x29
        _emit 0xB3
        // sub dword ptr [ebx - 0x4cd60f00], esi
        _emit 0x00
        _emit 0xCF
        // add bh, cl
        _emit 0x29
        _emit 0xB3
        _emit 0x00
        _emit 0xD6
        _emit 0x29
        _emit 0xB3
        // sub dword ptr [ebx - 0x4cd62a00], esi
        // trailing data bytes 00b32a07..00b32a08
        _emit 0x00
    }
}

// @ 0x00b32a10  (137 bytes)
__declspec(naked) void FUN_00b32a10()
{
    __asm {
        _emit 0x8B
        _emit 0x0D
        _emit 0x18
        _emit 0xD9
        _emit 0x5F
        _emit 0x01
        // mov ecx, dword ptr [0x15fd918]
        _emit 0x68
        _emit 0xF9
        _emit 0x9B
        _emit 0x43
        _emit 0x66
        // push 0x66439bf9
        call FUN_006a25a0
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x12
        // je 0xb32a36
        _emit 0x8B
        _emit 0x0D
        _emit 0x18
        _emit 0xD9
        _emit 0x5F
        _emit 0x01
        // mov ecx, dword ptr [0x15fd918]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x50
        _emit 0xE2
        _emit 0xF9
        _emit 0xC3
        // push 0xc3f9e250
        call FUN_006a17e0
        call FUN_00b3d360
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b7dec0
        call FUN_00b3d370
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ac7080
        call FUN_00bc8000
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bc83f0
        call FUN_00b3d490
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ae7de0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x04
        // mov ecx, dword ptr [esp + 4]
        _emit 0x81
        _emit 0xF9
        _emit 0xA1
        _emit 0xDB
        _emit 0xDB
        _emit 0x00
        // cmp ecx, 0xdbdba1
        _emit 0x74
        _emit 0x26
        // je 0xb32a98
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0x3D
        _emit 0xA1
        _emit 0xDB
        _emit 0xDB
        _emit 0x00
        // cmp eax, 0xdbdba1
        _emit 0x74
        _emit 0x1B
        // je 0xb32a98
        _emit 0x81
        _emit 0xF9
        _emit 0x10
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp ecx, 0x1654c10
        _emit 0x74
        _emit 0x13
        // je 0xb32a98
        _emit 0x3D
        _emit 0x10
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp eax, 0x1654c10
        _emit 0x74
        _emit 0x0C
        // je 0xb32a98
        call FUN_00b3d4a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        jmp FUN_00aeb700
        _emit 0xC3
        // ret 
    }
}

// @ 0x00b32aa0  (120 bytes)
__declspec(naked) void FUN_00b32aa0()
{
    __asm {
        call FUN_00b3d360
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b7dec0
        call FUN_00b3d290
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ac4f50
        call FUN_00b3d290
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ac1500
        call FUN_00b3d260
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x30
        // mov eax, dword ptr [edx + 0x30]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00b3d4a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00aeb700
        call FUN_00b3d3b0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b2f710
        call FUN_00b3d3c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b79a50
        call FUN_00b3d400
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00e18340
        call FUN_00b3d3e0
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0C
        // je 0xb32b17
        call FUN_00b3d3e0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        jmp FUN_00dd6d70
        _emit 0xC3
        // ret 
    }
}

// @ 0x00b32b20  (308 bytes)
__declspec(naked) void FUN_00b32b20()
{
    __asm {
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
        // je 0xb32b37
        _emit 0x83
        _emit 0xC0
        _emit 0xFC
        // add eax, -4
        _emit 0xEB
        _emit 0x02
        // jmp 0xb32b39
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0xC6
        _emit 0x80
        _emit 0x8D
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov byte ptr [eax + 0x28d], 0
        call FUN_00ba51f0
        call FUN_00e3c760
        call FUN_00b3d430
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bbfe80
        call FUN_00b3d480
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00acd210
        call FUN_00b3d480
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ad0bd0
        call FUN_00b3d2b0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x64
        // mov eax, dword ptr [edx + 0x64]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00b3d420
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b8ff60
        call FUN_00b3d240
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b33dd0
        call FUN_00b3d3e0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00dd6d70
        call FUN_00b3d300
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b26600
        call FUN_00b3d310
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x10
        // mov eax, dword ptr [edx + 0x10]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00b3d4c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ba3310
        _emit 0x6A
        _emit 0x01
        // push 1
        call FUN_00b3d440
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b0c190
        call FUN_00b3d350
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b8d2f0
        call FUN_01022460
        _emit 0x6A
        _emit 0xFF
        // push -1
        call FUN_01021960
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x6A
        _emit 0x00
        // push 0
        call FUN_010219b0
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        call FUN_00b3d2a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ba70b0
        call FUN_00bc8000
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bc8040
        call FUN_00af13b0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00af0f30
        call FUN_00b3d2a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bad810
        call FUN_00b3d2a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bb8b20
        call FUN_00b3d2a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bb7620
        call FUN_00bcb700
        _emit 0x6A
        _emit 0x00
        // push 0
        call FUN_00b3d340
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b267c0
        _emit 0xC3
        // ret 
    }
}

// @ 0x00b32c60  (113 bytes)
__declspec(naked) void FUN_00b32c60()
{
    __asm {
        _emit 0x81
        _emit 0x7C
        _emit 0x24
        _emit 0x04
        _emit 0x10
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp dword ptr [esp + 4], 0x1654c10
        _emit 0x75
        _emit 0x05
        // jne 0xb32c6f
        call FUN_00e4bc70
        call FUN_00b3d360
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b7dec0
        call FUN_00b3d290
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ac4f50
        call FUN_00b3d290
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ac1500
        call FUN_00b3d260
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x30
        // mov eax, dword ptr [edx + 0x30]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00b3d4a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00aeb700
        call FUN_00b3d3b0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b2f710
        call FUN_00b3d3c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b79a50
        call FUN_00b3d400
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        jmp FUN_00e18340
    }
}

// @ 0x00b32ce0  (225 bytes)
__declspec(naked) void FUN_00b32ce0()
{
    __asm {
        call FUN_00ba51f0
        call FUN_00e3c760
        call FUN_00b3d430
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bbfe80
        call FUN_00b3d480
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00acd210
        call FUN_00b3d480
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ad0bd0
        call FUN_00b3d2b0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x64
        // mov eax, dword ptr [edx + 0x64]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00b3d420
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b8ff60
        call FUN_00b3d240
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b33dd0
        call FUN_00b3d3e0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00dd6d70
        call FUN_00b3d300
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b26600
        call FUN_00b3d310
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x10
        // mov eax, dword ptr [edx + 0x10]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00b3d4c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ba3310
        _emit 0x6A
        _emit 0x01
        // push 1
        call FUN_00b3d440
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b0c190
        call FUN_00b3d350
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b8d2f0
        call FUN_01022460
        _emit 0x6A
        _emit 0xFF
        // push -1
        call FUN_01021960
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x6A
        _emit 0x00
        // push 0
        call FUN_010219b0
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        call FUN_00b3d2a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ba70b0
        call FUN_00bc8000
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bc8040
        call FUN_00af13b0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00af0f30
        jmp FUN_00bcb700
    }
}

// @ 0x00b32dd0  (161 bytes)
__declspec(naked) void FUN_00b32dd0()
{
    __asm {
        _emit 0x56
        // push esi
        call FUN_00bcb6c0
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x08
        // mov esi, dword ptr [esp + 8]
        _emit 0x56
        // push esi
        call FUN_00b3d2a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ba8160
        call FUN_01022580
        _emit 0x56
        // push esi
        call FUN_00b3d4a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00aeb680
        _emit 0x81
        _emit 0xFE
        _emit 0x10
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp esi, 0x1654c10
        _emit 0x74
        _emit 0x0D
        // je 0xb32e0e
        _emit 0x56
        // push esi
        call FUN_00b3d480
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ad2560
        _emit 0x56
        // push esi
        call FUN_00b3d400
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00e15a10
        _emit 0x81
        _emit 0xFE
        _emit 0x00
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp esi, 0x1654c00
        _emit 0x74
        _emit 0x0D
        // je 0xb32e30
        _emit 0x56
        // push esi
        call FUN_00b3d240
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b33d40
        call FUN_00b3d310
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x14
        // mov eax, dword ptr [edx + 0x14]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00b3d420
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b90480
        _emit 0x8B
        _emit 0x0D
        _emit 0xF0
        _emit 0x4E
        _emit 0x5E
        _emit 0x01
        // mov ecx, dword ptr [0x15e4ef0]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x50
        // mov eax, dword ptr [edx + 0x50]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00bc8000
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bc8200
        call FUN_00af13b0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x5E
        // pop esi
        jmp FUN_00af1020
    }
}

// @ 0x00b32e80  (224 bytes)
__declspec(naked) void FUN_00b32e80()
{
    __asm {
        _emit 0x56
        // push esi
        call FUN_00b3d360
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b7dec0
        call FUN_00b3d2b0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x60
        // mov eax, dword ptr [edx + 0x60]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00b3d290
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ac1500
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x08
        // mov esi, dword ptr [esp + 8]
        _emit 0x81
        _emit 0xFE
        _emit 0x00
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp esi, 0x1654c00
        _emit 0x74
        _emit 0x0D
        // je 0xb32ec0
        _emit 0x56
        // push esi
        call FUN_00b3d240
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b33d40
        _emit 0x56
        // push esi
        call FUN_00b3d350
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b7f390
        _emit 0x56
        // push esi
        call FUN_00b3d430
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bc20e0
        _emit 0x56
        // push esi
        call FUN_00b3d3b0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b2f680
        _emit 0x56
        // push esi
        call FUN_00b3d440
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b0c520
        _emit 0x6A
        _emit 0x00
        // push 0
        call FUN_00b3d340
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b267c0
        _emit 0x8D
        _emit 0x86
        _emit 0x00
        _emit 0xB4
        _emit 0x9A
        _emit 0xFE
        // lea eax, [esi - 0x1654c00]
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xF8
        _emit 0x05
        // cmp eax, 5
        _emit 0x77
        _emit 0x37
        // ja 0xb32f45
        _emit 0xFF
        _emit 0x24
        _emit 0x85
        _emit 0x48
        _emit 0x2F
        _emit 0xB3
        _emit 0x00
        // jmp dword ptr [eax*4 + 0xb32f48]
        call FUN_00b3d3c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        jmp FUN_00b79aa0
        call FUN_00fd9c60
        _emit 0xC6
        _emit 0x80
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov byte ptr [eax + 0x88], 0
        call FUN_00fd9c60
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00fe0570
        call FUN_00b3d3c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        jmp FUN_00b79aa0
        _emit 0xC3
        // ret 
        _emit 0x8B
        _emit 0xFF
        // mov edi, edi
        _emit 0x45
        // inc ebp
        _emit 0x2F
        // das 
        _emit 0xB3
        _emit 0x00
        // mov bl, 0
        _emit 0x15
        _emit 0x2F
        _emit 0xB3
        _emit 0x00
        _emit 0x15
        // adc eax, 0x1500b32f
        _emit 0x2F
        // das 
        _emit 0xB3
        _emit 0x00
        // mov bl, 0
        _emit 0x45
        // inc ebp
        _emit 0x2F
        // das 
        _emit 0xB3
        _emit 0x00
        // mov bl, 0
        _emit 0x15
        _emit 0x2F
        _emit 0xB3
        _emit 0x00
        _emit 0x21
        // adc eax, 0x2100b32f
        _emit 0x2F
        // das 
        _emit 0xB3
        _emit 0x00
        // mov bl, 0
    }
}

// @ 0x00b32f60  (196 bytes)
__declspec(naked) void FUN_00b32f60()
{
    __asm {
        _emit 0x56
        // push esi
        call FUN_01022580
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0x05
        _emit 0x00
        _emit 0xB4
        _emit 0x9A
        _emit 0xFE
        // add eax, 0xfe9ab400
        _emit 0x83
        _emit 0xF8
        _emit 0x04
        // cmp eax, 4
        _emit 0x77
        _emit 0x23
        // ja 0xb32f97
        _emit 0xFF
        _emit 0x24
        _emit 0x85
        _emit 0x10
        _emit 0x30
        _emit 0xB3
        _emit 0x00
        // jmp dword ptr [eax*4 + 0xb33010]
        _emit 0xBE
        _emit 0x01
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // mov esi, 0x1654c01
        _emit 0xEB
        _emit 0x18
        // jmp 0xb32f9a
        _emit 0xBE
        _emit 0x02
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // mov esi, 0x1654c02
        _emit 0xEB
        _emit 0x11
        // jmp 0xb32f9a
        _emit 0xBE
        _emit 0x04
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // mov esi, 0x1654c04
        _emit 0xEB
        _emit 0x0A
        // jmp 0xb32f9a
        _emit 0xBE
        _emit 0x05
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // mov esi, 0x1654c05
        _emit 0xEB
        _emit 0x03
        // jmp 0xb32f9a
        _emit 0x83
        _emit 0xCE
        _emit 0xFF
        // or esi, 0xffffffff
        _emit 0x56
        // push esi
        call FUN_00b3d4a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00aeb680
        _emit 0x56
        // push esi
        call FUN_00b3d480
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ad2560
        _emit 0x56
        // push esi
        call FUN_00b3d240
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b33d40
        call FUN_00b3d420
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b90480
        call FUN_00b3d310
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x14
        // mov eax, dword ptr [edx + 0x14]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x56
        // push esi
        call FUN_00b3d2a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ba8160
        call FUN_00b3d400
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00e180d0
        call FUN_00b3d2b0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ac79d0
        _emit 0x50
        // push eax
        call FUN_00b3d2b0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ac7a40
        _emit 0x5E
        // pop esi
        _emit 0xC3
        // ret 
        _emit 0x7B
        _emit 0x2F
        // jnp 0xb33041
        _emit 0xB3
        _emit 0x00
        // mov bl, 0
        _emit 0x82
        _emit 0x2F
        _emit 0xB3
        // sub byte ptr [edi], 0xb3
        _emit 0x00
        _emit 0x89
        _emit 0x2F
        _emit 0xB3
        _emit 0x00
        _emit 0x97
        // add byte ptr [ecx - 0x68ff4cd1], cl
        _emit 0x2F
        // das 
        _emit 0xB3
        _emit 0x00
        // mov bl, 0
        _emit 0x90
        // nop 
        _emit 0x2F
        // das 
        _emit 0xB3
        _emit 0x00
        // mov bl, 0
    }
}

// @ 0x00b33030  (168 bytes)
__declspec(naked) void FUN_00b33030()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x08
        // mov esi, dword ptr [esp + 8]
        _emit 0x56
        // push esi
        call FUN_00b3d350
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b7f390
        _emit 0x56
        // push esi
        call FUN_00b3d430
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bc20e0
        _emit 0x56
        // push esi
        call FUN_00b3d3b0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b2f680
        _emit 0x56
        // push esi
        call FUN_00b3d440
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b0c520
        _emit 0x81
        _emit 0xFE
        _emit 0x01
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp esi, 0x1654c01
        _emit 0x7E
        _emit 0x0E
        // jle 0xb3307f
        call FUN_00b3d2b0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x60
        // mov eax, dword ptr [edx + 0x60]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8D
        _emit 0x86
        _emit 0xFF
        _emit 0xB3
        _emit 0x9A
        _emit 0xFE
        // lea eax, [esi - 0x1654c01]
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xF8
        _emit 0x04
        // cmp eax, 4
        _emit 0x77
        _emit 0x37
        // ja 0xb330c2
        _emit 0xFF
        _emit 0x24
        _emit 0x85
        _emit 0xC4
        _emit 0x30
        _emit 0xB3
        _emit 0x00
        // jmp dword ptr [eax*4 + 0xb330c4]
        call FUN_00b3d3c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        jmp FUN_00b79aa0
        call FUN_00b3d3c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b79aa0
        call FUN_00fd9c60
        _emit 0xC6
        _emit 0x80
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x01
        // mov byte ptr [eax + 0x88], 1
        call FUN_00fd9c60
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        jmp FUN_00fe0160
        _emit 0xC3
        // ret 
        _emit 0x90
        // nop 
        _emit 0x92
        // xchg edx, eax
        _emit 0x30
        _emit 0xB3
        _emit 0x00
        _emit 0x92
        _emit 0x30
        _emit 0xB3
        // xor byte ptr [ebx - 0x4ccf6e00], dh
        _emit 0x00
        _emit 0xC2
        // add dl, al
        _emit 0x30
        _emit 0xB3
        _emit 0x00
        _emit 0x92
        _emit 0x30
        _emit 0xB3
        // xor byte ptr [ebx - 0x4ccf6e00], dh
        // trailing data bytes 00b330d3..00b330d8
        _emit 0x00
        _emit 0x9E
        _emit 0x30
        _emit 0xB3
        _emit 0x00
    }
}

// @ 0x00b330e0  (78 bytes)
__declspec(naked) void FUN_00b330e0()
{
    __asm {
        _emit 0x56
        // push esi
        call FUN_00bcb6c0
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x08
        // mov esi, dword ptr [esp + 8]
        _emit 0x56
        // push esi
        call FUN_00b3d4a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00aeb680
        _emit 0x56
        // push esi
        call FUN_00b3d240
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b33d40
        call FUN_00b3d420
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b90480
        call FUN_00b3d310
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x14
        // mov eax, dword ptr [edx + 0x14]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x56
        // push esi
        call FUN_00b3d400
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00e15a10
        _emit 0x5E
        // pop esi
        _emit 0xC3
        // ret 
    }
}

// @ 0x00b33130  (536 bytes)
__declspec(naked) void FUN_00b33130()
{
    __asm {
        _emit 0x56
        // push esi
        call FUN_00b3d3e0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00dd6d70
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x08
        // mov esi, dword ptr [esp + 8]
        _emit 0x81
        _emit 0xFE
        _emit 0x05
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp esi, 0x1654c05
        _emit 0x74
        _emit 0x05
        // je 0xb3314e
        call FUN_01022580
        call FUN_00b3d290
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ac1500
        _emit 0x56
        // push esi
        call FUN_00b3d440
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b0c520
        _emit 0x56
        // push esi
        call FUN_00b3d430
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bc20e0
        _emit 0x56
        // push esi
        call FUN_00b3d3b0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b2f680
        _emit 0x56
        // push esi
        call FUN_00b3d350
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b7f390
        _emit 0x8D
        _emit 0x86
        _emit 0xFF
        _emit 0xB3
        _emit 0x9A
        _emit 0xFE
        // lea eax, [esi - 0x1654c01]
        _emit 0x83
        _emit 0xF8
        _emit 0x0F
        // cmp eax, 0xf
        _emit 0x0F
        _emit 0x87
        _emit 0x65
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // ja 0xb33302
        _emit 0x0F
        _emit 0xB6
        _emit 0x80
        _emit 0x38
        _emit 0x33
        _emit 0xB3
        _emit 0x00
        // movzx eax, byte ptr [eax + 0xb33338]
        _emit 0xFF
        _emit 0x24
        _emit 0x85
        _emit 0x20
        _emit 0x33
        _emit 0xB3
        _emit 0x00
        // jmp dword ptr [eax*4 + 0xb33320]
        _emit 0x56
        // push esi
        call FUN_00b3d480
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ad2560
        call FUN_00b3d310
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b3d7a0
        call FUN_00b3d3c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b79aa0
        call FUN_00d37cb0
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        call FUN_00d38840
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x0F
        _emit 0x85
        _emit 0x1E
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jne 0xb33302
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x0F
        _emit 0x84
        _emit 0x16
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xb33302
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00d392f0
        _emit 0xE9
        _emit 0x0A
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jmp 0xb33302
        _emit 0x56
        // push esi
        call FUN_00b3d480
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ad2560
        call FUN_00b3d310
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b3d7a0
        call FUN_00b3d3c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b79aa0
        call FUN_00cd3440
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        call FUN_00cd40b0
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x0F
        _emit 0x85
        _emit 0xD1
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0xb33302
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x0F
        _emit 0x84
        _emit 0xC9
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xb33302
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00cd56e0
        _emit 0xE9
        _emit 0xBD
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jmp 0xb33302
        call FUN_00b3d480
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00acd210
        _emit 0x56
        // push esi
        call FUN_00b3d480
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ad2560
        call FUN_00b3d310
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b3d7a0
        call FUN_00b3d3c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b79aa0
        call FUN_00d004b0
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        call FUN_00cf74c0
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x75
        _emit 0x7C
        // jne 0xb33302
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x78
        // je 0xb33302
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00cf8fd0
        _emit 0xEB
        _emit 0x6F
        // jmp 0xb33302
        call FUN_00b3d480
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00acd210
        _emit 0x56
        // push esi
        call FUN_00b3d480
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ad2560
        call FUN_01021080
        _emit 0x83
        _emit 0xE8
        _emit 0x00
        // sub eax, 0
        _emit 0x74
        _emit 0x26
        // je 0xb332dc
        _emit 0x83
        _emit 0xE8
        _emit 0x01
        // sub eax, 1
        _emit 0x74
        _emit 0x13
        // je 0xb332ce
        _emit 0x83
        _emit 0xE8
        _emit 0x01
        // sub eax, 1
        _emit 0x75
        _emit 0x42
        // jne 0xb33302
        call FUN_00fd9c60
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00fdbee0
        _emit 0xEB
        _emit 0x34
        // jmp 0xb33302
        call FUN_00fd9c60
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00fe19a0
        _emit 0xEB
        _emit 0x26
        // jmp 0xb33302
        call FUN_00fd9c60
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00fdc710
        _emit 0xEB
        _emit 0x18
        // jmp 0xb33302
        call FUN_00b3d310
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b3d7a0
        call FUN_00b3d3c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b79aa0
        call FUN_00b3d2b0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x60
        // mov eax, dword ptr [edx + 0x60]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x6A
        _emit 0x00
        // push 0
        call FUN_00b3d340
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b267c0
        _emit 0x5E
        // pop esi
        _emit 0xC3
        // ret 
        _emit 0xAB
        // stosd dword ptr es:[edi], eax
        _emit 0x31
        _emit 0xB3
        _emit 0x00
        _emit 0xF8
        _emit 0x31
        _emit 0xB3
        // xor dword ptr [ebx - 0x4cce0800], esi
        _emit 0x00
        _emit 0x45
        _emit 0x32
        // add byte ptr [ebp + 0x32], al
        _emit 0xB3
        _emit 0x00
        // mov bl, 0
        _emit 0x93
        // xchg ebx, eax
        _emit 0x32
        _emit 0xB3
        _emit 0x00
        _emit 0xEA
        _emit 0x32
        _emit 0xB3
        // xor dh, byte ptr [ebx - 0x4ccd1600]
        _emit 0x00
        _emit 0x02
        // add byte ptr [edx], al
        _emit 0x33
        _emit 0xB3
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x05
        // xor esi, dword ptr [ebx + 0x5010000]
        _emit 0x02
        _emit 0x03
        // add al, byte ptr [ebx]
        _emit 0x05
        _emit 0x05
        _emit 0x05
        _emit 0x05
        _emit 0x05
        // add eax, 0x5050505
        _emit 0x05
        _emit 0x05
        _emit 0x05
        _emit 0x05
        _emit 0x05
        // add eax, 0x5050505
        // trailing data bytes 00b33347..00b33348
        _emit 0x04
    }
}

// @ 0x00b33350  (385 bytes)
__declspec(naked) void FUN_00b33350()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        call FUN_00ba51f0
        call FUN_00e3c760
        call FUN_00b3d290
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ac4f50
        call FUN_00b3d2b0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x5C
        // mov eax, dword ptr [edx + 0x5c]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00b3d4a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00aeb700
        call FUN_00b3d240
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b33d00
        call FUN_00b3d3e0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00dd6d70
        call FUN_00b3d310
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b4b7b0
        call FUN_00b3d410
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00c2e4e0
        call FUN_00b3d400
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00e18340
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x0C
        // mov edi, dword ptr [esp + 0xc]
        _emit 0x8D
        _emit 0xB7
        _emit 0x00
        _emit 0xB4
        _emit 0x9A
        _emit 0xFE
        // lea esi, [edi - 0x1654c00]
        _emit 0x83
        _emit 0xFE
        _emit 0x10
        // cmp esi, 0x10
        _emit 0x77
        _emit 0x4A
        // ja 0xb33417
        _emit 0x0F
        _emit 0xB6
        _emit 0x8E
        _emit 0xA4
        _emit 0x34
        _emit 0xB3
        _emit 0x00
        // movzx ecx, byte ptr [esi + 0xb334a4]
        _emit 0xFF
        _emit 0x24
        _emit 0x8D
        _emit 0x9C
        _emit 0x34
        _emit 0xB3
        _emit 0x00
        // jmp dword ptr [ecx*4 + 0xb3349c]
        call FUN_00b3d420
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b8ff60
        call FUN_00b3d3b0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b2f710
        call FUN_00b3d3c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b79a50
        call FUN_00b3d430
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bbfe80
        call FUN_00b3d350
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b8d2f0
        call FUN_00b3d300
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b26320
        _emit 0x83
        _emit 0xFE
        _emit 0x10
        // cmp esi, 0x10
        _emit 0x77
        _emit 0x1C
        // ja 0xb33444
        _emit 0x0F
        _emit 0xB6
        _emit 0x96
        _emit 0xC0
        _emit 0x34
        _emit 0xB3
        _emit 0x00
        // movzx edx, byte ptr [esi + 0xb334c0]
        _emit 0xFF
        _emit 0x24
        _emit 0x95
        _emit 0xB8
        _emit 0x34
        _emit 0xB3
        _emit 0x00
        // jmp dword ptr [edx*4 + 0xb334b8]
        _emit 0x6A
        _emit 0x01
        // push 1
        call FUN_00b3d440
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b0c190
        call FUN_01022460
        _emit 0x81
        _emit 0xFF
        _emit 0x01
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp edi, 0x1654c01
        _emit 0x7C
        _emit 0x23
        // jl 0xb33474
        _emit 0x81
        _emit 0xFF
        _emit 0x02
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp edi, 0x1654c02
        _emit 0x7E
        _emit 0x08
        // jle 0xb33461
        _emit 0x81
        _emit 0xFF
        _emit 0x04
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // cmp edi, 0x1654c04
        _emit 0x75
        _emit 0x13
        // jne 0xb33474
        _emit 0x6A
        _emit 0xFF
        // push -1
        call FUN_01021960
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x6A
        _emit 0x00
        // push 0
        call FUN_010219b0
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        call FUN_00b3d2a0
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
        call FUN_00bc8000
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bc8200
        call FUN_00af13b0
        _emit 0x5F
        // pop edi
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x5E
        // pop esi
        jmp FUN_00af1020
        // trailing data bytes 00b3349c..00b334d1
        _emit 0xDB
        _emit 0x33
        _emit 0xB3
        _emit 0x00
        _emit 0x17
        _emit 0x34
        _emit 0xB3
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x00
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        _emit 0x36
        _emit 0x34
        _emit 0xB3
        _emit 0x00
        _emit 0x44
        _emit 0x34
        _emit 0xB3
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x00
    }
}

// @ 0x00b334e0  (90 bytes)
__declspec(naked) void FUN_00b334e0()
{
    __asm {
        call FUN_00bcb6c0
        _emit 0x68
        _emit 0x10
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // push 0x1654c10
        call FUN_00b3d240
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b33d40
        call FUN_00b3d310
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x14
        // mov eax, dword ptr [edx + 0x14]
        _emit 0x68
        _emit 0x10
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // push 0x1654c10
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00b3d420
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b90480
        _emit 0x8B
        _emit 0x0D
        _emit 0xF0
        _emit 0x4E
        _emit 0x5E
        _emit 0x01
        // mov ecx, dword ptr [0x15e4ef0]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x50
        // mov eax, dword ptr [edx + 0x50]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00bc8000
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bc8200
        call FUN_00af13b0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        jmp FUN_00af1020
    }
}

// @ 0x00b33540  (138 bytes)
__declspec(naked) void FUN_00b33540()
{
    __asm {
        call FUN_00b3d360
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b7dec0
        call FUN_00b3d2b0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x60
        // mov eax, dword ptr [edx + 0x60]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00b3d290
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ac1500
        _emit 0x68
        _emit 0x10
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // push 0x1654c10
        call FUN_00b3d240
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b33d40
        _emit 0x68
        _emit 0x10
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // push 0x1654c10
        call FUN_00b3d350
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b7f390
        _emit 0x68
        _emit 0x10
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // push 0x1654c10
        call FUN_00b3d430
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bc20e0
        _emit 0x68
        _emit 0x10
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // push 0x1654c10
        call FUN_00b3d3b0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b2f680
        _emit 0x68
        _emit 0x10
        _emit 0x4C
        _emit 0x65
        _emit 0x01
        // push 0x1654c10
        call FUN_00b3d440
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b0c520
        _emit 0x6A
        _emit 0x00
        // push 0
        call FUN_00b3d340
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b267c0
        _emit 0xC3
        // ret 
    }
}
