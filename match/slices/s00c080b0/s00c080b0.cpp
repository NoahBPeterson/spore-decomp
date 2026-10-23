// Slice s00c080b0: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00acca00();
extern "C" void FUN_00b1fd50();
extern "C" void FUN_00b1fdb0();
extern "C" void FUN_00b3d260();
extern "C" void FUN_00b3d300();
extern "C" void FUN_00b3d310();
extern "C" void FUN_00b45410();
extern "C" void FUN_00bc9de0();
extern "C" void FUN_00c0cff0();
extern "C" void FUN_00c0d240();
extern "C" void FUN_00c0d3a0();
extern "C" void FUN_00c17350();
extern "C" void FUN_00c1c8e0();
extern "C" void FUN_00c41d60();
extern "C" void FUN_00d53490();
extern "C" void FUN_00d539d0();
extern "C" void FUN_00f47380();
extern "C" void FUN_011e0744();

// @ 0x00c080b0  (438 bytes)
__declspec(naked) void FUN_00c080b0()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x78
        // sub esp, 0x78
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8B
        _emit 0x46
        _emit 0x58
        // mov eax, dword ptr [esi + 0x58]
        _emit 0x8B
        _emit 0x50
        _emit 0x34
        // mov edx, dword ptr [eax + 0x34]
        _emit 0x8D
        _emit 0x4E
        _emit 0x58
        // lea ecx, [esi + 0x58]
        _emit 0x57
        // push edi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x90
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [eax + 0x84]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x53
        // push ebx
        _emit 0x53
        // push ebx
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0x8B
        _emit 0x86
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0xc0]
        _emit 0x8B
        _emit 0x90
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [eax + 0xdc]
        _emit 0x88
        _emit 0x9E
        _emit 0x28
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esi + 0x328], bl
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xE0
        _emit 0x05
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0x5e0], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x0D
        _emit 0x44
        _emit 0xD8
        _emit 0x68
        _emit 0x01
        // movss xmm1, dword ptr [0x168d844]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // movss dword ptr [esp + 0x28], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x0D
        _emit 0x48
        _emit 0xD8
        _emit 0x68
        _emit 0x01
        // movss xmm1, dword ptr [0x168d848]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // movss dword ptr [esp + 0x2c], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x0D
        _emit 0x4C
        _emit 0xD8
        _emit 0x68
        _emit 0x01
        // movss xmm1, dword ptr [0x168d84c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x30
        // movss dword ptr [esp + 0x30], xmm1
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
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // movss dword ptr [esp + 0x34], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x0D
        _emit 0x1C
        _emit 0x0F
        _emit 0x47
        _emit 0x01
        // movss xmm1, dword ptr [0x1470f1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x74
        // movss dword ptr [esp + 0x74], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x0D
        _emit 0xB4
        _emit 0xC4
        _emit 0x3E
        _emit 0x01
        // movss xmm1, dword ptr [0x13ec4b4]
        _emit 0x8D
        _emit 0xAE
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebp, [esi + 0xc0]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // lea ecx, [esp + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x78
        // movss dword ptr [esp + 0x78], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x0D
        _emit 0x30
        _emit 0x9E
        _emit 0x46
        _emit 0x01
        // movss xmm1, dword ptr [0x1469e30]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], ebx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ebx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], ebx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x3C
        // mov dword ptr [esp + 0x3c], ebx
        _emit 0x88
        _emit 0x5C
        _emit 0x24
        _emit 0x64
        // mov byte ptr [esp + 0x64], bl
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x68
        // movss dword ptr [esp + 0x68], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x6C
        // movss dword ptr [esp + 0x6c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x70
        // movss dword ptr [esp + 0x70], xmm0
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x74
        // mov dword ptr [esp + 0x74], ebx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x8C
        _emit 0x24
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esp + 0x80], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x84
        _emit 0x24
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esp + 0x84], xmm0
        _emit 0x89
        _emit 0x9C
        _emit 0x24
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x88], ebx
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x74
        _emit 0x0E
        // je 0xc081b6
        _emit 0x39
        _emit 0x58
        _emit 0xFC
        // cmp dword ptr [eax - 4], ebx
        _emit 0x74
        _emit 0x09
        // je 0xc081b6
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00c0cff0
        _emit 0x68
        _emit 0x44
        _emit 0xD8
        _emit 0x68
        _emit 0x01
        // push 0x168d844
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        call FUN_00c41d60
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0x83
        _emit 0xC8
        _emit 0xFF
        // or eax, 0xffffffff
        _emit 0x89
        _emit 0x86
        _emit 0x8C
        _emit 0x0E
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xe8c], eax
        _emit 0x89
        _emit 0x86
        _emit 0x90
        _emit 0x0E
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xe90], eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0x94
        _emit 0x0E
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xe94], xmm0
        _emit 0x8B
        _emit 0xBE
        _emit 0x9C
        _emit 0x0E
        _emit 0x00
        _emit 0x00
        // mov edi, dword ptr [esi + 0xe9c]
        _emit 0x8B
        _emit 0x86
        _emit 0x98
        _emit 0x0E
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0xe98]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0x2B
        _emit 0xCF
        // sub ecx, edi
        _emit 0x51
        // push ecx
        _emit 0x57
        // push edi
        _emit 0x50
        // push eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], eax
        call FUN_011e0744
        _emit 0x2B
        _emit 0x7C
        _emit 0x24
        _emit 0x1C
        // sub edi, dword ptr [esp + 0x1c]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
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
        _emit 0xBE
        _emit 0x9C
        _emit 0x0E
        _emit 0x00
        _emit 0x00
        // add dword ptr [esi + 0xe9c], edi
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xC7
        _emit 0x86
        _emit 0x3C
        _emit 0x0E
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // mov dword ptr [esi + 0xe3c], 0xffffffff
        call FUN_00c0d240
        _emit 0x8B
        _emit 0x8E
        _emit 0x24
        _emit 0x16
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x1624]
        _emit 0x6A
        _emit 0xFF
        // push -1
        _emit 0xC6
        _emit 0x86
        _emit 0x5E
        _emit 0x0B
        _emit 0x00
        _emit 0x00
        _emit 0x01
        // mov byte ptr [esi + 0xb5e], 1
        call FUN_00bc9de0
        _emit 0x53
        // push ebx
        _emit 0x68
        _emit 0x1C
        _emit 0xBF
        _emit 0xC4
        _emit 0x02
        // push 0x2c4bf1c
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00c17350
        call FUN_00b3d310
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0D
        // je 0xc0825e
        _emit 0x55
        // push ebp
        call FUN_00b3d310
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b45410
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
        _emit 0x78
        // add esp, 0x78
        _emit 0xC3
        // ret 
    }
}

// @ 0x00c08270  (220 bytes)
__declspec(naked) void FUN_00c08270()
{
    __asm {
        _emit 0x51
        // push ecx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x56
        // push esi
        call FUN_00c0d3a0
        _emit 0x8B
        _emit 0x8E
        _emit 0x24
        _emit 0x16
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x1624]
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x6A
        _emit 0xFF
        // push -1
        call FUN_00bc9de0
        call FUN_00b3d300
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b1fdb0
        _emit 0x3B
        _emit 0xF0
        // cmp esi, eax
        _emit 0x75
        _emit 0x0E
        // jne 0xc082a8
        _emit 0x6A
        _emit 0x00
        // push 0
        call FUN_00b3d300
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b1fd50
        _emit 0x8B
        _emit 0x86
        _emit 0x58
        _emit 0x0B
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0xb58]
        _emit 0xC1
        _emit 0xE8
        _emit 0x08
        // shr eax, 8
        _emit 0xA8
        _emit 0x01
        // test al, 1
        _emit 0x74
        _emit 0x11
        // je 0xc082c6
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x56
        // push esi
        call FUN_00d539d0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00d53490
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x7E
        _emit 0x58
        // lea edi, [esi + 0x58]
        call FUN_00b3d260
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x3C
        // mov eax, dword ptr [edx + 0x3c]
        _emit 0x57
        // push edi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x82
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edx + 0x84]
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
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x86
        _emit 0x74
        _emit 0x16
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x1674]
        _emit 0x5F
        // pop edi
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x15
        // je 0xc0830b
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x04
        // lea ecx, [esp + 4]
        _emit 0x51
        // push ecx
        _emit 0x83
        _emit 0xC0
        _emit 0x40
        // add eax, 0x40
        _emit 0x50
        // push eax
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], esi
        call FUN_00acca00
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x8B
        _emit 0x8E
        _emit 0x74
        _emit 0x16
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x1674]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x11
        // je 0xc08326
        _emit 0xC7
        _emit 0x86
        _emit 0x74
        _emit 0x16
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x1674], 0
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
        _emit 0x8E
        _emit 0x98
        _emit 0x16
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x1698]
        _emit 0xC7
        _emit 0x86
        _emit 0x98
        _emit 0x16
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x1698], 0
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x07
        // je 0xc08341
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x64
        // mov eax, dword ptr [edx + 0x64]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        jmp FUN_00c1c8e0
    }
}
