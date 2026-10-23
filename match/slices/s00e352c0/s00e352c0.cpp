// Slice s00e352c0: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00828100();
extern "C" void FUN_00b25c30();
extern "C" void FUN_00b3d300();
extern "C" void FUN_00bdc4a0();
extern "C" void FUN_00cf0e10();
extern "C" void FUN_00cf74c0();
extern "C" void FUN_00cf74f0();
extern "C" void FUN_00e2a6c0();
extern "C" void FUN_00e352c0();

// @ 0x00e352c0  (99 bytes)
__declspec(naked) void FUN_00e352c0()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8B
        _emit 0x4E
        _emit 0x10
        // mov ecx, dword ptr [esi + 0x10]
        _emit 0x80
        _emit 0x79
        _emit 0x44
        _emit 0x00
        // cmp byte ptr [ecx + 0x44], 0
        _emit 0x74
        _emit 0x55
        // je 0xe35321
        call FUN_00828100
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x6A
        _emit 0x00
        // push 0
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
        _emit 0x8B
        _emit 0x4E
        _emit 0x10
        // mov ecx, dword ptr [esi + 0x10]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x24
        // mov eax, dword ptr [edx + 0x24]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x80
        _emit 0x7E
        _emit 0x20
        _emit 0x00
        // cmp byte ptr [esi + 0x20], 0
        _emit 0x74
        _emit 0x33
        // je 0xe35321
        call FUN_00cf74c0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00cf74f0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00cf0e10
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x75
        _emit 0x1C
        // jne 0xe35321
        _emit 0x88
        _emit 0x46
        _emit 0x20
        // mov byte ptr [esi + 0x20], al
        call FUN_00b3d300
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b25c30
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x09
        // je 0xe35321
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bdc4a0
        _emit 0x5E
        // pop esi
        _emit 0xC3
        // ret 
    }
}

// @ 0x00e35350  (17 bytes)
__declspec(naked) void FUN_00e35350()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        call FUN_00e352c0
        _emit 0x8B
        _emit 0x4E
        _emit 0x18
        // mov ecx, dword ptr [esi + 0x18]
        _emit 0x5E
        // pop esi
        jmp FUN_00e2a6c0
    }
}
