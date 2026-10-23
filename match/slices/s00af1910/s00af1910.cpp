// Slice s00af1910: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00537dc0();

// @ 0x00af1910  (374 bytes)
__declspec(naked) void FUN_00af1910()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xD9
        // mov ebx, ecx
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
        _emit 0xB9
        _emit 0x08
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, 8
        _emit 0x8B
        _emit 0xF5
        // mov esi, ebp
        _emit 0x8B
        _emit 0xFB
        // mov edi, ebx
        _emit 0xF3
        _emit 0xA5
        // rep movsd dword ptr es:[edi], dword ptr [esi]
        _emit 0x8B
        _emit 0x45
        _emit 0x20
        // mov eax, dword ptr [ebp + 0x20]
        _emit 0x89
        _emit 0x43
        _emit 0x20
        // mov dword ptr [ebx + 0x20], eax
        _emit 0x8B
        _emit 0x4D
        _emit 0x24
        // mov ecx, dword ptr [ebp + 0x24]
        _emit 0x89
        _emit 0x4B
        _emit 0x24
        // mov dword ptr [ebx + 0x24], ecx
        _emit 0x8B
        _emit 0x55
        _emit 0x28
        // mov edx, dword ptr [ebp + 0x28]
        _emit 0x89
        _emit 0x53
        _emit 0x28
        // mov dword ptr [ebx + 0x28], edx
        _emit 0x8B
        _emit 0x45
        _emit 0x2C
        // mov eax, dword ptr [ebp + 0x2c]
        _emit 0x89
        _emit 0x43
        _emit 0x2C
        // mov dword ptr [ebx + 0x2c], eax
        _emit 0x8B
        _emit 0x4D
        _emit 0x30
        // mov ecx, dword ptr [ebp + 0x30]
        _emit 0x89
        _emit 0x4B
        _emit 0x30
        // mov dword ptr [ebx + 0x30], ecx
        _emit 0x8B
        _emit 0x55
        _emit 0x34
        // mov edx, dword ptr [ebp + 0x34]
        _emit 0x89
        _emit 0x53
        _emit 0x34
        // mov dword ptr [ebx + 0x34], edx
        _emit 0x8B
        _emit 0x45
        _emit 0x38
        // mov eax, dword ptr [ebp + 0x38]
        _emit 0x89
        _emit 0x43
        _emit 0x38
        // mov dword ptr [ebx + 0x38], eax
        _emit 0x8B
        _emit 0x4D
        _emit 0x3C
        // mov ecx, dword ptr [ebp + 0x3c]
        _emit 0x89
        _emit 0x4B
        _emit 0x3C
        // mov dword ptr [ebx + 0x3c], ecx
        _emit 0x8A
        _emit 0x55
        _emit 0x40
        // mov dl, byte ptr [ebp + 0x40]
        _emit 0x88
        _emit 0x53
        _emit 0x40
        // mov byte ptr [ebx + 0x40], dl
        _emit 0xD9
        _emit 0x45
        _emit 0x44
        // fld dword ptr [ebp + 0x44]
        _emit 0xD9
        _emit 0x5B
        _emit 0x44
        // fstp dword ptr [ebx + 0x44]
        _emit 0x8B
        _emit 0x45
        _emit 0x48
        // mov eax, dword ptr [ebp + 0x48]
        _emit 0x89
        _emit 0x43
        _emit 0x48
        // mov dword ptr [ebx + 0x48], eax
        _emit 0x8B
        _emit 0x4D
        _emit 0x4C
        // mov ecx, dword ptr [ebp + 0x4c]
        _emit 0x89
        _emit 0x4B
        _emit 0x4C
        // mov dword ptr [ebx + 0x4c], ecx
        _emit 0x8B
        _emit 0x55
        _emit 0x50
        // mov edx, dword ptr [ebp + 0x50]
        _emit 0x89
        _emit 0x53
        _emit 0x50
        // mov dword ptr [ebx + 0x50], edx
        _emit 0xD9
        _emit 0x45
        _emit 0x54
        // fld dword ptr [ebp + 0x54]
        _emit 0xD9
        _emit 0x5B
        _emit 0x54
        // fstp dword ptr [ebx + 0x54]
        _emit 0x8B
        _emit 0x45
        _emit 0x64
        // mov eax, dword ptr [ebp + 0x64]
        _emit 0x89
        _emit 0x43
        _emit 0x64
        // mov dword ptr [ebx + 0x64], eax
        _emit 0x8B
        _emit 0x4D
        _emit 0x68
        // mov ecx, dword ptr [ebp + 0x68]
        _emit 0x89
        _emit 0x4B
        _emit 0x68
        // mov dword ptr [ebx + 0x68], ecx
        _emit 0x8B
        _emit 0x55
        _emit 0x6C
        // mov edx, dword ptr [ebp + 0x6c]
        _emit 0x89
        _emit 0x53
        _emit 0x6C
        // mov dword ptr [ebx + 0x6c], edx
        _emit 0x8B
        _emit 0x45
        _emit 0x58
        // mov eax, dword ptr [ebp + 0x58]
        _emit 0x89
        _emit 0x43
        _emit 0x58
        // mov dword ptr [ebx + 0x58], eax
        _emit 0x8B
        _emit 0x4D
        _emit 0x5C
        // mov ecx, dword ptr [ebp + 0x5c]
        _emit 0x89
        _emit 0x4B
        _emit 0x5C
        // mov dword ptr [ebx + 0x5c], ecx
        _emit 0x8B
        _emit 0x55
        _emit 0x60
        // mov edx, dword ptr [ebp + 0x60]
        _emit 0x8D
        _emit 0x45
        _emit 0x70
        // lea eax, [ebp + 0x70]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4B
        _emit 0x70
        // lea ecx, [ebx + 0x70]
        _emit 0x89
        _emit 0x53
        _emit 0x60
        // mov dword ptr [ebx + 0x60], edx
        call FUN_00537dc0
        _emit 0x8B
        _emit 0x8D
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [ebp + 0xa8]
        _emit 0x89
        _emit 0x8B
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xa8], ecx
        _emit 0x8B
        _emit 0x95
        _emit 0xAC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [ebp + 0xac]
        _emit 0x89
        _emit 0x93
        _emit 0xAC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xac], edx
        _emit 0x8B
        _emit 0x85
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [ebp + 0xb0]
        _emit 0x89
        _emit 0x83
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xb0], eax
        _emit 0x8B
        _emit 0x8D
        _emit 0xB4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [ebp + 0xb4]
        _emit 0x89
        _emit 0x8B
        _emit 0xB4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xb4], ecx
        _emit 0x8B
        _emit 0x95
        _emit 0xB8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [ebp + 0xb8]
        _emit 0x89
        _emit 0x93
        _emit 0xB8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xb8], edx
        _emit 0x8B
        _emit 0x85
        _emit 0xBC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [ebp + 0xbc]
        _emit 0x89
        _emit 0x83
        _emit 0xBC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xbc], eax
        _emit 0x8B
        _emit 0x8D
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [ebp + 0xc0]
        _emit 0x89
        _emit 0x8B
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xc0], ecx
        _emit 0x8B
        _emit 0x95
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [ebp + 0xc4]
        _emit 0x89
        _emit 0x93
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xc4], edx
        _emit 0xD9
        _emit 0x85
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [ebp + 0xc8]
        _emit 0xD9
        _emit 0x9B
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [ebx + 0xc8]
        _emit 0x8B
        _emit 0x85
        _emit 0xCC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [ebp + 0xcc]
        _emit 0x89
        _emit 0x83
        _emit 0xCC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xcc], eax
        _emit 0x8B
        _emit 0x8D
        _emit 0xD0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [ebp + 0xd0]
        _emit 0x89
        _emit 0x8B
        _emit 0xD0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xd0], ecx
        _emit 0x8B
        _emit 0x95
        _emit 0xD4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [ebp + 0xd4]
        _emit 0x89
        _emit 0x93
        _emit 0xD4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xd4], edx
        _emit 0x8B
        _emit 0x85
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [ebp + 0xd8]
        _emit 0x89
        _emit 0x83
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xd8], eax
        _emit 0x8B
        _emit 0x8D
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [ebp + 0xdc]
        _emit 0x89
        _emit 0x8B
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xdc], ecx
        _emit 0x8B
        _emit 0x95
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [ebp + 0xe0]
        _emit 0x8D
        _emit 0x85
        _emit 0xE4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea eax, [ebp + 0xe4]
        _emit 0x89
        _emit 0x93
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xe0], edx
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x89
        _emit 0x8B
        _emit 0xE4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xe4], ecx
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x93
        _emit 0xE8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xe8], edx
        _emit 0x8B
        _emit 0x40
        _emit 0x08
        // mov eax, dword ptr [eax + 8]
        _emit 0x5E
        // pop esi
        _emit 0x89
        _emit 0x83
        _emit 0xEC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0xec], eax
        _emit 0x5D
        // pop ebp
        _emit 0x8B
        _emit 0xC3
        // mov eax, ebx
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}
