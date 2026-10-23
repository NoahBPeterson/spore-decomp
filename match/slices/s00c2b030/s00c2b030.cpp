// Slice s00c2b030: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00406540();
extern "C" void FUN_00c296b0();
extern "C" void FUN_00c2b030();
extern "C" void FUN_00c2b080();
extern "C" void FUN_00cadb00();
extern "C" void FUN_00cadb50();
extern "C" void FUN_00cb00d0();
extern "C" void FUN_00cb1110();
extern "C" void FUN_011e0700();

// @ 0x00c2b030  (75 bytes)
__declspec(naked) void FUN_00c2b030()
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
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // mov ebx, dword ptr [esp + 0xc]
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x68
        _emit 0xB0
        _emit 0x9A
        _emit 0xC2
        _emit 0x00
        // push 0xc29ab0
        _emit 0x6A
        _emit 0x08
        // push 8
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x68
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // push 0x100
        _emit 0x53
        // push ebx
        _emit 0x8D
        _emit 0x7E
        _emit 0x04
        // lea edi, [esi + 4]
        _emit 0x57
        // push edi
        _emit 0x89
        _emit 0x0E
        // mov dword ptr [esi], ecx
        call FUN_00406540
        _emit 0x68
        _emit 0x80
        _emit 0x89
        _emit 0xAC
        _emit 0x00
        // push 0xac8980
        _emit 0x6A
        _emit 0x08
        // push 8
        _emit 0x6A
        _emit 0x04
        // push 4
        _emit 0x81
        _emit 0xC3
        _emit 0x00
        _emit 0x08
        _emit 0x00
        _emit 0x00
        // add ebx, 0x800
        _emit 0x53
        // push ebx
        _emit 0x81
        _emit 0xC7
        _emit 0x00
        _emit 0x08
        _emit 0x00
        _emit 0x00
        // add edi, 0x800
        _emit 0x57
        // push edi
        call FUN_00406540
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
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00c2b080  (132 bytes)
__declspec(naked) void FUN_00c2b080()
{
    __asm {
        _emit 0xB8
        _emit 0x50
        _emit 0x10
        _emit 0x00
        _emit 0x00
        // mov eax, 0x1050
        call FUN_011e0700
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xBC
        _emit 0x24
        _emit 0x5C
        _emit 0x10
        _emit 0x00
        _emit 0x00
        // mov edi, dword ptr [esp + 0x105c]
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // lea eax, [esp + 0xc]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        call FUN_00cb00d0
        _emit 0x8B
        _emit 0x4E
        _emit 0x08
        // mov ecx, dword ptr [esi + 8]
        _emit 0x8B
        _emit 0x56
        _emit 0x04
        // mov edx, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0x3B
        _emit 0x04
        _emit 0x8A
        // cmp eax, dword ptr [edx + ecx*4]
        _emit 0x75
        _emit 0x47
        // jne 0xc2b0f6
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // lea ecx, [esp + 0x14]
        call FUN_00c296b0
        _emit 0x50
        // push eax
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x8C
        _emit 0x24
        _emit 0x3C
        _emit 0x08
        _emit 0x00
        _emit 0x00
        // lea ecx, [esp + 0x83c]
        call FUN_00c2b030
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x08
        _emit 0x00
        // mov byte ptr [esp + 8], 0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // mov ecx, dword ptr [esp + 8]
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // lea edx, [esp + 0x10]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00cb1110
        _emit 0x8D
        _emit 0x8C
        _emit 0x24
        _emit 0x38
        _emit 0x08
        _emit 0x00
        _emit 0x00
        // lea ecx, [esp + 0x838]
        call FUN_00cadb00
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // lea ecx, [esp + 0x14]
        call FUN_00cadb00
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0x5F
        // pop edi
        _emit 0x83
        _emit 0xC0
        _emit 0x04
        // add eax, 4
        _emit 0x5E
        // pop esi
        _emit 0x81
        _emit 0xC4
        _emit 0x50
        _emit 0x10
        _emit 0x00
        _emit 0x00
        // add esp, 0x1050
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00c2b110  (84 bytes)
__declspec(naked) void FUN_00c2b110()
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
        _emit 0x60
        _emit 0x24
        _emit 0x57
        _emit 0x01
        // mov ecx, 0x1572460
        call FUN_00cb00d0
        _emit 0x8B
        _emit 0x04
        _emit 0x24
        // mov eax, dword ptr [esp]
        _emit 0x8B
        _emit 0x15
        _emit 0x68
        _emit 0x24
        _emit 0x57
        _emit 0x01
        // mov edx, dword ptr [0x1572468]
        _emit 0x8B
        _emit 0x0D
        _emit 0x64
        _emit 0x24
        _emit 0x57
        _emit 0x01
        // mov ecx, dword ptr [0x1572464]
        _emit 0x3B
        _emit 0x04
        _emit 0x91
        // cmp eax, dword ptr [ecx + edx*4]
        _emit 0x75
        _emit 0x22
        // jne 0xc2b15d
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
        _emit 0x60
        _emit 0x24
        _emit 0x57
        _emit 0x01
        // mov ecx, 0x1572460
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
