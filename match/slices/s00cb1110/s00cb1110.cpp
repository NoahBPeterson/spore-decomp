// Slice s00cb1110: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00921440();
extern "C" void FUN_00c29710();
extern "C" void FUN_00c2b080();
extern "C" void FUN_00cadb50();
extern "C" void FUN_00cb00d0();
extern "C" void FUN_00cb02a0();
extern "C" void FUN_00f473a0();

// @ 0x00cb1110  (242 bytes)
__declspec(naked) void FUN_00cb1110()
{
    __asm {
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x18
        // mov ebx, dword ptr [eax]
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7E
        _emit 0x08
        // mov edi, dword ptr [esi + 8]
        _emit 0x8B
        _emit 0xC3
        // mov eax, ebx
        _emit 0xF7
        _emit 0xF7
        // div edi
        _emit 0x8B
        _emit 0x4E
        _emit 0x04
        // mov ecx, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0xEA
        // mov ebp, edx
        _emit 0x8D
        _emit 0x14
        _emit 0xA9
        // lea edx, [ecx + ebp*4]
        _emit 0x8B
        _emit 0x0A
        // mov ecx, dword ptr [edx]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x12
        // je 0xcb1148
        _emit 0x3B
        _emit 0x19
        // cmp ebx, dword ptr [ecx]
        _emit 0x0F
        _emit 0x84
        _emit 0xAD
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xcb11eb
        _emit 0x8B
        _emit 0x89
        _emit 0x24
        _emit 0x08
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [ecx + 0x824]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x75
        _emit 0xEE
        // jne 0xcb1136
        _emit 0x8B
        _emit 0x56
        _emit 0x0C
        // mov edx, dword ptr [esi + 0xc]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x52
        // push edx
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // lea eax, [esp + 0x1c]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4E
        _emit 0x10
        // lea ecx, [esi + 0x10]
        call FUN_00921440
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
        _emit 0x68
        _emit 0xB4
        _emit 0x09
        _emit 0x3F
        _emit 0x01
        // push 0x13f09b4
        _emit 0x68
        _emit 0x28
        _emit 0x08
        _emit 0x00
        _emit 0x00
        // push 0x828
        call FUN_00f473a0
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x74
        _emit 0x0C
        // je 0xcb118e
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_00cb02a0
        _emit 0xC7
        _emit 0x87
        _emit 0x24
        _emit 0x08
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x824], 0
        _emit 0x80
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        _emit 0x00
        // cmp byte ptr [esp + 0x10], 0
        _emit 0x74
        _emit 0x14
        // je 0xcb11b3
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x8B
        _emit 0xC3
        // mov eax, ebx
        _emit 0xF7
        _emit 0xF1
        // div ecx
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x8B
        _emit 0xEA
        // mov ebp, edx
        call FUN_00c29710
        _emit 0x8B
        _emit 0x56
        _emit 0x04
        // mov edx, dword ptr [esi + 4]
        _emit 0x8D
        _emit 0x0C
        _emit 0xAD
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [ebp*4]
        _emit 0x8B
        _emit 0x04
        _emit 0x11
        // mov eax, dword ptr [ecx + edx]
        _emit 0x89
        _emit 0x87
        _emit 0x24
        _emit 0x08
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x824], eax
        _emit 0x8B
        _emit 0x56
        _emit 0x04
        // mov edx, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov eax, dword ptr [esp + 0x1c]
        _emit 0x89
        _emit 0x3C
        _emit 0x11
        // mov dword ptr [ecx + edx], edi
        _emit 0xFF
        _emit 0x46
        _emit 0x0C
        // inc dword ptr [esi + 0xc]
        _emit 0x8B
        _emit 0x56
        _emit 0x04
        // mov edx, dword ptr [esi + 4]
        _emit 0x89
        _emit 0x38
        // mov dword ptr [eax], edi
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x03
        _emit 0xD1
        // add edx, ecx
        _emit 0x5D
        // pop ebp
        _emit 0xC6
        _emit 0x40
        _emit 0x08
        _emit 0x01
        // mov byte ptr [eax + 8], 1
        _emit 0x89
        _emit 0x50
        _emit 0x04
        // mov dword ptr [eax + 4], edx
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
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov eax, dword ptr [esp + 0x1c]
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x89
        _emit 0x08
        // mov dword ptr [eax], ecx
        _emit 0xC6
        _emit 0x40
        _emit 0x08
        _emit 0x00
        // mov byte ptr [eax + 8], 0
        _emit 0x89
        _emit 0x50
        _emit 0x04
        // mov dword ptr [eax + 4], edx
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

// @ 0x00cb1210  (84 bytes)
__declspec(naked) void FUN_00cb1210()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // lea eax, [esp + 0xc]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x04
        // lea ecx, [esp + 4]
        _emit 0x51
        // push ecx
        _emit 0xB9
        _emit 0x0C
        _emit 0xD3
        _emit 0x57
        _emit 0x01
        // mov ecx, 0x157d30c
        call FUN_00cb00d0
        _emit 0x8B
        _emit 0x04
        _emit 0x24
        // mov eax, dword ptr [esp]
        _emit 0x8B
        _emit 0x15
        _emit 0x14
        _emit 0xD3
        _emit 0x57
        _emit 0x01
        // mov edx, dword ptr [0x157d314]
        _emit 0x8B
        _emit 0x0D
        _emit 0x10
        _emit 0xD3
        _emit 0x57
        _emit 0x01
        // mov ecx, dword ptr [0x157d310]
        _emit 0x3B
        _emit 0x04
        _emit 0x91
        // cmp eax, dword ptr [ecx + edx*4]
        _emit 0x75
        _emit 0x22
        // jne 0xcb125d
        _emit 0x56
        // push esi
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // lea edx, [esp + 0x10]
        _emit 0x52
        // push edx
        _emit 0xB9
        _emit 0x0C
        _emit 0xD3
        _emit 0x57
        _emit 0x01
        // mov ecx, 0x157d30c
        call FUN_00c2b080
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x56
        // push esi
        call FUN_00cadb50
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC3
        // ret 
        _emit 0x83
        _emit 0xC0
        _emit 0x04
        // add eax, 4
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC3
        // ret 
    }
}
