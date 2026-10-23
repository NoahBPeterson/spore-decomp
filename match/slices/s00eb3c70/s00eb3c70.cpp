// Slice s00eb3c70: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00472b80();
extern "C" void FUN_00572600();
extern "C" void FUN_0069d090();
extern "C" void FUN_0069d100();
extern "C" void FUN_0069d150();
extern "C" void FUN_00eb2eb0();
extern "C" void FUN_00eb4130();

// @ 0x00eb3c70  (972 bytes)
__declspec(naked) void FUN_00eb3c70()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x30
        // sub esp, 0x30
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x38
        // mov ebx, dword ptr [esp + 0x38]
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x83
        _emit 0xFB
        _emit 0x04
        // cmp ebx, 4
        _emit 0x0F
        _emit 0x87
        _emit 0x97
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // ja 0xeb401c
        _emit 0xFF
        _emit 0x24
        _emit 0x9D
        _emit 0x28
        _emit 0x40
        _emit 0xEB
        _emit 0x00
        // jmp dword ptr [ebx*4 + 0xeb4028]
        _emit 0x8B
        _emit 0x46
        _emit 0x14
        // mov eax, dword ptr [esi + 0x14]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x75
        _emit 0x43
        // jne 0xeb3cd6
        _emit 0x8B
        _emit 0x86
        _emit 0x78
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x178]
        _emit 0x8B
        _emit 0x8E
        _emit 0x7C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x17c]
        _emit 0x8B
        _emit 0x96
        _emit 0x80
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x180]
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0x89
        _emit 0x46
        _emit 0x54
        // mov dword ptr [esi + 0x54], eax
        _emit 0x89
        _emit 0x46
        _emit 0x6C
        // mov dword ptr [esi + 0x6c], eax
        _emit 0x89
        _emit 0x4E
        _emit 0x58
        // mov dword ptr [esi + 0x58], ecx
        _emit 0x89
        _emit 0x4E
        _emit 0x70
        // mov dword ptr [esi + 0x70], ecx
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x5E
        _emit 0x14
        // mov dword ptr [esi + 0x14], ebx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xf0], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xEC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xec], xmm0
        _emit 0x89
        _emit 0x56
        _emit 0x5C
        // mov dword ptr [esi + 0x5c], edx
        _emit 0x89
        _emit 0x56
        _emit 0x74
        // mov dword ptr [esi + 0x74], edx
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x30
        // add esp, 0x30
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x75
        _emit 0x1F
        // jne 0xeb3cfa
        _emit 0x8B
        _emit 0x8E
        _emit 0x7C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x17c]
        _emit 0x8B
        _emit 0x86
        _emit 0x78
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x178]
        _emit 0x89
        _emit 0x46
        _emit 0x54
        // mov dword ptr [esi + 0x54], eax
        _emit 0x89
        _emit 0x46
        _emit 0x6C
        // mov dword ptr [esi + 0x6c], eax
        _emit 0x89
        _emit 0x4E
        _emit 0x58
        // mov dword ptr [esi + 0x58], ecx
        _emit 0x89
        _emit 0x4E
        _emit 0x70
        // mov dword ptr [esi + 0x70], ecx
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // lea ecx, [esp + 0x10]
        _emit 0xEB
        _emit 0x26
        // jmp 0xeb3d20
        _emit 0x83
        _emit 0xF8
        _emit 0x03
        // cmp eax, 3
        _emit 0x0F
        _emit 0x85
        _emit 0x19
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // jne 0xeb401c
        _emit 0x8B
        _emit 0x8E
        _emit 0x7C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x17c]
        _emit 0x8B
        _emit 0x86
        _emit 0x78
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x178]
        _emit 0x89
        _emit 0x46
        _emit 0x54
        // mov dword ptr [esi + 0x54], eax
        _emit 0x89
        _emit 0x46
        _emit 0x6C
        // mov dword ptr [esi + 0x6c], eax
        _emit 0x89
        _emit 0x4E
        _emit 0x58
        // mov dword ptr [esi + 0x58], ecx
        _emit 0x89
        _emit 0x4E
        _emit 0x70
        // mov dword ptr [esi + 0x70], ecx
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // lea ecx, [esp + 0x20]
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0xD9
        _emit 0xEE
        // fldz 
        _emit 0x8B
        _emit 0x96
        _emit 0x80
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x180]
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        _emit 0x8D
        _emit 0x86
        _emit 0x88
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea eax, [esi + 0x188]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xEC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xec], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xf0], xmm0
        _emit 0x89
        _emit 0x56
        _emit 0x5C
        // mov dword ptr [esi + 0x5c], edx
        _emit 0x8D
        _emit 0xBE
        _emit 0x40
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea edi, [esi + 0x140]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x4C
        // movss dword ptr [esi + 0x4c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x40
        // movss dword ptr [esi + 0x40], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x48
        // movss dword ptr [esi + 0x48], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x44
        // movss dword ptr [esi + 0x44], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x24
        // movss dword ptr [esi + 0x24], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x18
        // movss dword ptr [esi + 0x18], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x20
        // movss dword ptr [esi + 0x20], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x1C
        // movss dword ptr [esi + 0x1c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x38
        // movss dword ptr [esi + 0x38], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x2C
        // movss dword ptr [esi + 0x2c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x34
        // movss dword ptr [esi + 0x34], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x30
        // movss dword ptr [esi + 0x30], xmm0
        _emit 0x89
        _emit 0x56
        _emit 0x74
        // mov dword ptr [esi + 0x74], edx
        call FUN_00472b80
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_00572600
        _emit 0x8B
        _emit 0x17
        // mov edx, dword ptr [edi]
        _emit 0x8B
        _emit 0x47
        _emit 0x04
        // mov eax, dword ptr [edi + 4]
        _emit 0x8B
        _emit 0x4F
        _emit 0x08
        // mov ecx, dword ptr [edi + 8]
        _emit 0x89
        _emit 0x96
        _emit 0x30
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x130], edx
        _emit 0x8B
        _emit 0x57
        _emit 0x0C
        // mov edx, dword ptr [edi + 0xc]
        _emit 0x89
        _emit 0x86
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x134], eax
        _emit 0x89
        _emit 0x8E
        _emit 0x38
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x138], ecx
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x5E
        _emit 0x14
        // mov dword ptr [esi + 0x14], ebx
        _emit 0x89
        _emit 0x96
        _emit 0x3C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x13c], edx
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x30
        // add esp, 0x30
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0x83
        _emit 0x7E
        _emit 0x14
        _emit 0x00
        // cmp dword ptr [esi + 0x14], 0
        _emit 0x74
        _emit 0x0B
        // je 0xeb3dde
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xf0], xmm0
        _emit 0xD9
        _emit 0x86
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [esi + 0xf0]
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x9E
        _emit 0xEC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [esi + 0xec]
        _emit 0x8D
        _emit 0x86
        _emit 0x88
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea eax, [esi + 0x188]
        _emit 0xD9
        _emit 0xEE
        // fldz 
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x30
        // lea ecx, [esp + 0x30]
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        call FUN_00472b80
        _emit 0xD9
        _emit 0x00
        // fld dword ptr [eax]
        _emit 0xD9
        _emit 0x9E
        _emit 0x40
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [esi + 0x140]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xD9
        _emit 0x40
        _emit 0x04
        // fld dword ptr [eax + 4]
        _emit 0x5F
        // pop edi
        _emit 0xD9
        _emit 0x9E
        _emit 0x44
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [esi + 0x144]
        _emit 0xD9
        _emit 0x40
        _emit 0x08
        // fld dword ptr [eax + 8]
        _emit 0xD9
        _emit 0x9E
        _emit 0x48
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [esi + 0x148]
        _emit 0xD9
        _emit 0x40
        _emit 0x0C
        // fld dword ptr [eax + 0xc]
        _emit 0xD9
        _emit 0x9E
        _emit 0x4C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [esi + 0x14c]
        _emit 0x8B
        _emit 0x96
        _emit 0x40
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x140]
        _emit 0x8B
        _emit 0x86
        _emit 0x44
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x144]
        _emit 0x8B
        _emit 0x8E
        _emit 0x48
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x148]
        _emit 0x89
        _emit 0x96
        _emit 0x30
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x130], edx
        _emit 0x8B
        _emit 0x96
        _emit 0x4C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x14c]
        _emit 0x89
        _emit 0x86
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x134], eax
        _emit 0x89
        _emit 0x8E
        _emit 0x38
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x138], ecx
        _emit 0x89
        _emit 0x5E
        _emit 0x14
        // mov dword ptr [esi + 0x14], ebx
        _emit 0x89
        _emit 0x96
        _emit 0x3C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x13c], edx
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x30
        // add esp, 0x30
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0x8B
        _emit 0x46
        _emit 0x54
        // mov eax, dword ptr [esi + 0x54]
        _emit 0xD9
        _emit 0x86
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [esi + 0xf0]
        _emit 0x8B
        _emit 0x4E
        _emit 0x58
        // mov ecx, dword ptr [esi + 0x58]
        _emit 0xD9
        _emit 0x9E
        _emit 0xEC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [esi + 0xec]
        _emit 0x8B
        _emit 0x56
        _emit 0x5C
        // mov edx, dword ptr [esi + 0x5c]
        _emit 0xD9
        _emit 0x46
        _emit 0x30
        // fld dword ptr [esi + 0x30]
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0xD9
        _emit 0x5E
        _emit 0x2C
        // fstp dword ptr [esi + 0x2c]
        _emit 0xD9
        _emit 0x46
        _emit 0x1C
        // fld dword ptr [esi + 0x1c]
        _emit 0x89
        _emit 0x46
        _emit 0x6C
        // mov dword ptr [esi + 0x6c], eax
        _emit 0x8B
        _emit 0x86
        _emit 0x40
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x140]
        _emit 0xD9
        _emit 0x5E
        _emit 0x18
        // fstp dword ptr [esi + 0x18]
        _emit 0x89
        _emit 0x4E
        _emit 0x70
        // mov dword ptr [esi + 0x70], ecx
        _emit 0x8B
        _emit 0x8E
        _emit 0x44
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x144]
        _emit 0x89
        _emit 0x86
        _emit 0x30
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x130], eax
        _emit 0x8B
        _emit 0x86
        _emit 0x4C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x14c]
        _emit 0x89
        _emit 0x56
        _emit 0x74
        // mov dword ptr [esi + 0x74], edx
        _emit 0x8B
        _emit 0x96
        _emit 0x48
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x148]
        _emit 0x89
        _emit 0x8E
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x134], ecx
        _emit 0x8B
        _emit 0x8E
        _emit 0x8C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x8c]
        _emit 0x89
        _emit 0x96
        _emit 0x38
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x138], edx
        _emit 0x8B
        _emit 0x96
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x90]
        _emit 0x89
        _emit 0x86
        _emit 0x3C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x13c], eax
        _emit 0x8B
        _emit 0x86
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x94]
        _emit 0x89
        _emit 0x8E
        _emit 0xA4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xa4], ecx
        _emit 0x89
        _emit 0x96
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xa8], edx
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x5E
        _emit 0x14
        // mov dword ptr [esi + 0x14], ebx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xF8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xf8], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x38
        // movss dword ptr [esi + 0x38], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x24
        // movss dword ptr [esi + 0x24], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0x60
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0x160], xmm0
        _emit 0x89
        _emit 0x86
        _emit 0xAC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xac], eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xB4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xb4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xD0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xd0], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x7C
        // movss dword ptr [esi + 0x7c], xmm0
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x30
        // add esp, 0x30
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0x8B
        _emit 0x8E
        _emit 0x78
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x178]
        _emit 0x8B
        _emit 0x96
        _emit 0x7C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x17c]
        _emit 0x8B
        _emit 0x86
        _emit 0x80
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x180]
        _emit 0x89
        _emit 0x4E
        _emit 0x54
        // mov dword ptr [esi + 0x54], ecx
        _emit 0x89
        _emit 0x4E
        _emit 0x6C
        // mov dword ptr [esi + 0x6c], ecx
        _emit 0x89
        _emit 0x56
        _emit 0x58
        // mov dword ptr [esi + 0x58], edx
        _emit 0x89
        _emit 0x56
        _emit 0x70
        // mov dword ptr [esi + 0x70], edx
        _emit 0x89
        _emit 0x46
        _emit 0x5C
        // mov dword ptr [esi + 0x5c], eax
        _emit 0x89
        _emit 0x46
        _emit 0x74
        // mov dword ptr [esi + 0x74], eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xf0], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xEC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xec], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xF8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xf8], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x30
        // movss dword ptr [esi + 0x30], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x34
        // movss dword ptr [esi + 0x34], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x2C
        // movss dword ptr [esi + 0x2c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x38
        // movss dword ptr [esi + 0x38], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x1C
        // movss dword ptr [esi + 0x1c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x20
        // movss dword ptr [esi + 0x20], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x18
        // movss dword ptr [esi + 0x18], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x24
        // movss dword ptr [esi + 0x24], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x44
        // movss dword ptr [esi + 0x44], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x48
        // movss dword ptr [esi + 0x48], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x40
        // movss dword ptr [esi + 0x40], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x4C
        // movss dword ptr [esi + 0x4c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x7C
        // movss dword ptr [esi + 0x7c], xmm0
        _emit 0xD9
        _emit 0x46
        _emit 0x5C
        // fld dword ptr [esi + 0x5c]
        _emit 0xD9
        _emit 0x46
        _emit 0x58
        // fld dword ptr [esi + 0x58]
        _emit 0x8B
        _emit 0x8E
        _emit 0x40
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x140]
        _emit 0xD9
        _emit 0x46
        _emit 0x54
        // fld dword ptr [esi + 0x54]
        _emit 0x8B
        _emit 0x96
        _emit 0x44
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x144]
        _emit 0xDC
        _emit 0xC8
        // fmul st(0), st(0)
        _emit 0x8B
        _emit 0x86
        _emit 0x48
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x148]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0x89
        _emit 0x8E
        _emit 0x30
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x130], ecx
        _emit 0xDE
        _emit 0xCA
        // fmulp st(2)
        _emit 0x8B
        _emit 0x8E
        _emit 0x4C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x14c]
        _emit 0x89
        _emit 0x96
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x134], edx
        _emit 0x89
        _emit 0x86
        _emit 0x38
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x138], eax
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x5E
        _emit 0x14
        // mov dword ptr [esi + 0x14], ebx
        _emit 0x89
        _emit 0x8E
        _emit 0x3C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x13c], ecx
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0x60
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0x160], xmm0
        _emit 0xDE
        _emit 0xCA
        // fmulp st(2)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xFA
        // fsqrt 
        _emit 0xD9
        _emit 0x9E
        _emit 0xAC
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [esi + 0x1ac]
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x30
        // add esp, 0x30
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0x8B
        _emit 0x56
        _emit 0x54
        // mov edx, dword ptr [esi + 0x54]
        _emit 0x8B
        _emit 0x46
        _emit 0x58
        // mov eax, dword ptr [esi + 0x58]
        _emit 0x8B
        _emit 0x4E
        _emit 0x5C
        // mov ecx, dword ptr [esi + 0x5c]
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0x89
        _emit 0x56
        _emit 0x6C
        // mov dword ptr [esi + 0x6c], edx
        _emit 0x89
        _emit 0x46
        _emit 0x70
        // mov dword ptr [esi + 0x70], eax
        _emit 0x89
        _emit 0x4E
        _emit 0x74
        // mov dword ptr [esi + 0x74], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x7C
        // movss dword ptr [esi + 0x7c], xmm0
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x5E
        _emit 0x14
        // mov dword ptr [esi + 0x14], ebx
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x30
        // add esp, 0x30
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0xCD
        _emit 0x3D
        // int 0x3d
        _emit 0xEB
        _emit 0x00
        // jmp 0xeb402c
        _emit 0x63
        _emit 0x3E
        // arpl word ptr [esi], di
        _emit 0xEB
        _emit 0x00
        // jmp 0xeb4030
        _emit 0x1F
        // pop ds
        _emit 0x3F
        // aas 
        _emit 0xEB
        _emit 0x00
        // jmp 0xeb4034
        _emit 0x02
        _emit 0x40
        _emit 0xEB
        // add al, byte ptr [eax - 0x15]
        // trailing data bytes 00eb4037..00eb403c
        _emit 0x00
        _emit 0x8C
        _emit 0x3C
        _emit 0xEB
        _emit 0x00
    }
}

// @ 0x00eb4040  (228 bytes)
__declspec(naked) void FUN_00eb4040()
{
    __asm {
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x41
        _emit 0x30
        // fld dword ptr [ecx + 0x30]
        _emit 0x53
        // push ebx
        _emit 0xD8
        _emit 0x61
        _emit 0x34
        // fsub dword ptr [ecx + 0x34]
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x06
        _emit 0x01
        // mov byte ptr [esp + 6], 1
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x05
        _emit 0x6C
        _emit 0x86
        _emit 0x48
        _emit 0x01
        // fld dword ptr [0x148866c]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xDF
        _emit 0xF1
        // fcompi st(1)
        _emit 0x77
        _emit 0x05
        // ja 0xeb4060
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x06
        _emit 0x00
        // mov byte ptr [esp + 6], 0
        _emit 0xD9
        _emit 0x41
        _emit 0x1C
        // fld dword ptr [ecx + 0x1c]
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x07
        _emit 0x01
        // mov byte ptr [esp + 7], 1
        _emit 0xD8
        _emit 0x61
        _emit 0x20
        // fsub dword ptr [ecx + 0x20]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xDF
        _emit 0xF1
        // fcompi st(1)
        _emit 0x77
        _emit 0x05
        // ja 0xeb4076
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x07
        _emit 0x00
        // mov byte ptr [esp + 7], 0
        _emit 0xD9
        _emit 0x41
        _emit 0x44
        // fld dword ptr [ecx + 0x44]
        _emit 0xD8
        _emit 0x61
        _emit 0x48
        // fsub dword ptr [ecx + 0x48]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xDF
        _emit 0xF1
        // fcompi st(1)
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x76
        _emit 0x04
        // jbe 0xeb4088
        _emit 0xB3
        _emit 0x01
        // mov bl, 1
        _emit 0xEB
        _emit 0x02
        // jmp 0xeb408a
        _emit 0x32
        _emit 0xDB
        // xor bl, bl
        _emit 0xD9
        _emit 0x81
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [ecx + 0xf0]
        _emit 0xD8
        _emit 0xA1
        _emit 0xF4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fsub dword ptr [ecx + 0xf4]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x05
        _emit 0x70
        _emit 0x86
        _emit 0x48
        _emit 0x01
        // fld dword ptr [0x1488670]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xDF
        _emit 0xF1
        // fcompi st(1)
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x76
        _emit 0x04
        // jbe 0xeb40aa
        _emit 0xB2
        _emit 0x01
        // mov dl, 1
        _emit 0xEB
        _emit 0x02
        // jmp 0xeb40ac
        _emit 0x32
        _emit 0xD2
        // xor dl, dl
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x59
        _emit 0x60
        // movss xmm3, dword ptr [ecx + 0x60]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x69
        _emit 0x68
        // movss xmm5, dword ptr [ecx + 0x68]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x41
        _emit 0x54
        // movss xmm0, dword ptr [ecx + 0x54]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x51
        _emit 0x5C
        // movss xmm2, dword ptr [ecx + 0x5c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x61
        _emit 0x64
        // movss xmm4, dword ptr [ecx + 0x64]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x49
        _emit 0x58
        // movss xmm1, dword ptr [ecx + 0x58]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xC3
        // subss xmm0, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xD5
        // subss xmm2, xmm5
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xCC
        // subss xmm1, xmm4
        _emit 0x0F
        _emit 0x28
        _emit 0xDA
        // movaps xmm3, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xDA
        // mulss xmm3, xmm2
        _emit 0x0F
        _emit 0x28
        _emit 0xD1
        // movaps xmm2, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD1
        // mulss xmm2, xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xDA
        // addss xmm3, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xD9
        // addss xmm3, xmm1
        _emit 0x0F
        _emit 0x2F
        _emit 0x1D
        _emit 0x70
        _emit 0x86
        _emit 0x48
        _emit 0x01
        // comiss xmm3, dword ptr [0x1488670]
        _emit 0x76
        _emit 0x04
        // jbe 0xeb4100
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0xEB
        _emit 0x02
        // jmp 0xeb4102
        _emit 0x32
        _emit 0xC0
        // xor al, al
        _emit 0x80
        _emit 0x7C
        _emit 0x24
        _emit 0x06
        _emit 0x00
        // cmp byte ptr [esp + 6], 0
        _emit 0x75
        _emit 0x16
        // jne 0xeb411f
        _emit 0x80
        _emit 0x7C
        _emit 0x24
        _emit 0x07
        _emit 0x00
        // cmp byte ptr [esp + 7], 0
        _emit 0x75
        _emit 0x0F
        // jne 0xeb411f
        _emit 0x84
        _emit 0xDB
        // test bl, bl
        _emit 0x75
        _emit 0x0B
        // jne 0xeb411f
        _emit 0x84
        _emit 0xD2
        // test dl, dl
        _emit 0x75
        _emit 0x07
        // jne 0xeb411f
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x75
        _emit 0x03
        // jne 0xeb411f
        _emit 0x5B
        // pop ebx
        _emit 0x59
        // pop ecx
        _emit 0xC3
        // ret 
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x5B
        // pop ebx
        _emit 0x59
        // pop ecx
        _emit 0xC3
        // ret 
    }
}

// @ 0x00eb4130  (178 bytes)
__declspec(naked) void FUN_00eb4130()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x10
        // sub esp, 0x10
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x0D
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // movss xmm1, dword ptr [0x1485720]
        _emit 0x53
        // push ebx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // movss dword ptr [esp + 4], xmm0
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
        _emit 0x56
        // push esi
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // movss dword ptr [esp + 0xc], xmm0
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // mov edx, dword ptr [esp + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // movss dword ptr [esp + 8], xmm0
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // mov ebx, dword ptr [esp + 8]
        _emit 0x89
        _emit 0x59
        _emit 0x20
        // mov dword ptr [ecx + 0x20], ebx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // movss dword ptr [esp + 0x10], xmm0
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x10
        // mov esi, dword ptr [esp + 0x10]
        _emit 0x89
        _emit 0x41
        _emit 0x10
        // mov dword ptr [ecx + 0x10], eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // movss dword ptr [esp + 0xc], xmm0
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // mov ebx, dword ptr [esp + 0xc]
        _emit 0x89
        _emit 0x59
        _emit 0x24
        // mov dword ptr [ecx + 0x24], ebx
        _emit 0x89
        _emit 0x01
        // mov dword ptr [ecx], eax
        _emit 0x57
        // push edi
        _emit 0x89
        _emit 0x51
        _emit 0x14
        // mov dword ptr [ecx + 0x14], edx
        _emit 0x89
        _emit 0x51
        _emit 0x04
        // mov dword ptr [ecx + 4], edx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // movss dword ptr [esp + 0x18], xmm1
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x18
        // mov edi, dword ptr [esp + 0x18]
        _emit 0x89
        _emit 0x71
        _emit 0x18
        // mov dword ptr [ecx + 0x18], esi
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm0
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // mov ebx, dword ptr [esp + 0x14]
        _emit 0x89
        _emit 0x59
        _emit 0x28
        // mov dword ptr [ecx + 0x28], ebx
        _emit 0x89
        _emit 0x71
        _emit 0x08
        // mov dword ptr [ecx + 8], esi
        _emit 0x89
        _emit 0x79
        _emit 0x1C
        // mov dword ptr [ecx + 0x1c], edi
        _emit 0x89
        _emit 0x79
        _emit 0x0C
        // mov dword ptr [ecx + 0xc], edi
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // movss dword ptr [esp + 0x18], xmm1
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov ebx, dword ptr [esp + 0x18]
        _emit 0x89
        _emit 0x59
        _emit 0x2C
        // mov dword ptr [ecx + 0x2c], ebx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x41
        _emit 0x30
        // movss dword ptr [ecx + 0x30], xmm0
        _emit 0xA1
        _emit 0x90
        _emit 0x72
        _emit 0x6C
        _emit 0x01
        // mov eax, dword ptr [0x16c7290]
        _emit 0x89
        _emit 0x41
        _emit 0x34
        // mov dword ptr [ecx + 0x34], eax
        _emit 0x8B
        _emit 0x15
        _emit 0x94
        _emit 0x72
        _emit 0x6C
        _emit 0x01
        // mov edx, dword ptr [0x16c7294]
        _emit 0x89
        _emit 0x51
        _emit 0x38
        // mov dword ptr [ecx + 0x38], edx
        _emit 0xA1
        _emit 0x98
        _emit 0x72
        _emit 0x6C
        _emit 0x01
        // mov eax, dword ptr [0x16c7298]
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x41
        _emit 0x3C
        // mov dword ptr [ecx + 0x3c], eax
        _emit 0x8B
        _emit 0x15
        _emit 0x9C
        _emit 0x72
        _emit 0x6C
        _emit 0x01
        // mov edx, dword ptr [0x16c729c]
        _emit 0x5E
        // pop esi
        _emit 0x89
        _emit 0x51
        _emit 0x40
        // mov dword ptr [ecx + 0x40], edx
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        _emit 0xC3
        // ret 
    }
}

// @ 0x00eb41f0  (518 bytes)
__declspec(naked) void FUN_00eb41f0()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x0C
        // sub esp, 0xc
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x0D
        _emit 0xBC
        _emit 0xB1
        _emit 0x3E
        _emit 0x01
        // movss xmm1, dword ptr [0x13eb1bc]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x8E
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0x104], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x8E
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0x100], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0x10c], xmm0
        _emit 0xC6
        _emit 0x86
        _emit 0x0A
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esi + 0x10a], 0
        _emit 0xC6
        _emit 0x86
        _emit 0x08
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esi + 0x108], 0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x1C
        // movss dword ptr [esi + 0x1c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x20
        // movss dword ptr [esi + 0x20], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x18
        // movss dword ptr [esi + 0x18], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x24
        // movss dword ptr [esi + 0x24], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x28
        // movss dword ptr [esi + 0x28], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x30
        // movss dword ptr [esi + 0x30], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x34
        // movss dword ptr [esi + 0x34], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x2C
        // movss dword ptr [esi + 0x2c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x38
        // movss dword ptr [esi + 0x38], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x3C
        // movss dword ptr [esi + 0x3c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x44
        // movss dword ptr [esi + 0x44], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x48
        // movss dword ptr [esi + 0x48], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x40
        // movss dword ptr [esi + 0x40], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x4C
        // movss dword ptr [esi + 0x4c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x46
        _emit 0x50
        // movss dword ptr [esi + 0x50], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xE4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xe4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xE8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xe8], xmm0
        _emit 0x8D
        _emit 0x4E
        _emit 0x54
        // lea ecx, [esi + 0x54]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x8E
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xe0], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x8E
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xdc], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x8E
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xd8], xmm1
        call FUN_00eb2eb0
        _emit 0x8D
        _emit 0x8E
        _emit 0x8C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [esi + 0x8c]
        call FUN_00eb2eb0
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xc8], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xCC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xcc], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xc4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xD0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xd0], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xD4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xd4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xF8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xf8], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xFC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xfc], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0x70
        _emit 0x3C
        _emit 0x47
        _emit 0x01
        // movss xmm0, dword ptr [0x1473c70]
        _emit 0x8D
        _emit 0x8E
        _emit 0x30
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea ecx, [esi + 0x130]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xf0], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xF4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xf4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x86
        _emit 0xEC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esi + 0xec], xmm0
        call FUN_00eb4130
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0xC7
        _emit 0x86
        _emit 0x14
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x114], 0
        _emit 0xC7
        _emit 0x86
        _emit 0x10
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xE8
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x110], 0x3e8
        _emit 0xA1
        _emit 0x0C
        _emit 0x94
        _emit 0x5A
        _emit 0x01
        // mov eax, dword ptr [0x15a940c]
        _emit 0x89
        _emit 0x86
        _emit 0x18
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x118], eax
        _emit 0x8B
        _emit 0x0D
        _emit 0x10
        _emit 0x94
        _emit 0x5A
        _emit 0x01
        // mov ecx, dword ptr [0x15a9410]
        _emit 0x89
        _emit 0x8E
        _emit 0x1C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x11c], ecx
        _emit 0x8B
        _emit 0x15
        _emit 0x14
        _emit 0x94
        _emit 0x5A
        _emit 0x01
        // mov edx, dword ptr [0x15a9414]
        _emit 0x89
        _emit 0x96
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x120], edx
        _emit 0xA1
        _emit 0x24
        _emit 0x94
        _emit 0x5A
        _emit 0x01
        // mov eax, dword ptr [0x15a9424]
        _emit 0x89
        _emit 0x86
        _emit 0x24
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x124], eax
        _emit 0x8B
        _emit 0x0D
        _emit 0x28
        _emit 0x94
        _emit 0x5A
        _emit 0x01
        // mov ecx, dword ptr [0x15a9428]
        _emit 0x89
        _emit 0x8E
        _emit 0x28
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x128], ecx
        _emit 0x8B
        _emit 0x15
        _emit 0x2C
        _emit 0x94
        _emit 0x5A
        _emit 0x01
        // mov edx, dword ptr [0x15a942c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // movss dword ptr [esp + 4], xmm0
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // movss dword ptr [esp + 8], xmm0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // mov ecx, dword ptr [esp + 8]
        _emit 0x89
        _emit 0x86
        _emit 0xDC
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x2dc], eax
        _emit 0x89
        _emit 0x96
        _emit 0x2C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x12c], edx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // movss dword ptr [esp + 0xc], xmm0
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // mov edx, dword ptr [esp + 0xc]
        _emit 0x89
        _emit 0x8E
        _emit 0xE0
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x2e0], ecx
        _emit 0x8D
        _emit 0x8E
        _emit 0xA0
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // lea ecx, [esi + 0x2a0]
        _emit 0x89
        _emit 0x96
        _emit 0xE4
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x2e4], edx
        call FUN_0069d100
        _emit 0x8D
        _emit 0x8E
        _emit 0xB0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea ecx, [esi + 0x1b0]
        _emit 0xC7
        _emit 0x46
        _emit 0x14
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x14], 4
        call FUN_0069d090
        _emit 0x8D
        _emit 0x8E
        _emit 0x28
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // lea ecx, [esi + 0x228]
        call FUN_0069d100
        _emit 0x8D
        _emit 0x8E
        _emit 0xEC
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea ecx, [esi + 0x1ec]
        call FUN_0069d090
        _emit 0x8D
        _emit 0x8E
        _emit 0x64
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // lea ecx, [esi + 0x264]
        call FUN_0069d150
        _emit 0x83
        _emit 0x7E
        _emit 0x10
        _emit 0x00
        // cmp dword ptr [esi + 0x10], 0
        _emit 0x74
        _emit 0x0D
        // je 0xeb43f1
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x50
        _emit 0x50
        // mov edx, dword ptr [eax + 0x50]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xFF
        _emit 0xE2
        // jmp edx
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xC3
        // ret 
    }
}
