// Slice s00908bb0: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_009036b0();
extern "C" void FUN_00907fb0();

// @ 0x00908bb0  (80 bytes)
__declspec(naked) void FUN_00908bb0()
{
    __asm {
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov edx, dword ptr [esp + 0x10]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x08
        // mov esi, dword ptr [esp + 8]
        _emit 0x80
        _emit 0xBE
        _emit 0xE4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [esi + 0x1e4], 0
        _emit 0x57
        // push edi
        _emit 0x0F
        _emit 0x94
        _emit 0xC0
        // sete al
        _emit 0x0F
        _emit 0xB6
        _emit 0xC8
        // movzx ecx, al
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0x96
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x90]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x56
        // push esi
        call FUN_00907fb0
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x83
        _emit 0xC4
        _emit 0x1C
        // add esp, 0x1c
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x75
        _emit 0x10
        // jne 0x908bfb
        _emit 0x56
        // push esi
        call FUN_009036b0
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x8D
        _emit 0x47
        _emit 0x01
        // lea eax, [edi + 1]
        _emit 0x74
        _emit 0x02
        // je 0x908bfd
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
