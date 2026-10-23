// Slice s00f4fe50: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00f47380();
extern "C" void FUN_00f48aa0();
extern "C" void FUN_00f98800();

// @ 0x00f4fe50  (175 bytes)
__declspec(naked) void FUN_00f4fe50()
{
    __asm {
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // mov edx, dword ptr [esp + 8]
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4C
        _emit 0x24
        _emit 0x04
        // movss xmm1, dword ptr [esp + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // movss xmm2, dword ptr [esp + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // movss xmm3, dword ptr [esp + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x64
        _emit 0x24
        _emit 0x10
        // movss xmm4, dword ptr [esp + 0x10]
        _emit 0x89
        _emit 0x41
        _emit 0x3C
        // mov dword ptr [ecx + 0x3c], eax
        _emit 0x89
        _emit 0x41
        _emit 0x2C
        // mov dword ptr [ecx + 0x2c], eax
        _emit 0x89
        _emit 0x41
        _emit 0x1C
        // mov dword ptr [ecx + 0x1c], eax
        _emit 0x89
        _emit 0x41
        _emit 0x0C
        // mov dword ptr [ecx + 0xc], eax
        _emit 0x89
        _emit 0x51
        _emit 0x40
        // mov dword ptr [ecx + 0x40], edx
        _emit 0x89
        _emit 0x51
        _emit 0x30
        // mov dword ptr [ecx + 0x30], edx
        _emit 0x89
        _emit 0x51
        _emit 0x20
        // mov dword ptr [ecx + 0x20], edx
        _emit 0x89
        _emit 0x51
        _emit 0x10
        // mov dword ptr [ecx + 0x10], edx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x10
        // mov esi, dword ptr [esp + 0x10]
        _emit 0x89
        _emit 0x71
        _emit 0x44
        // mov dword ptr [ecx + 0x44], esi
        _emit 0x89
        _emit 0x71
        _emit 0x34
        // mov dword ptr [ecx + 0x34], esi
        _emit 0x89
        _emit 0x71
        _emit 0x24
        // mov dword ptr [ecx + 0x24], esi
        _emit 0x89
        _emit 0x71
        _emit 0x14
        // mov dword ptr [ecx + 0x14], esi
        _emit 0xC6
        _emit 0x01
        _emit 0x00
        // mov byte ptr [ecx], 0
        _emit 0xC6
        _emit 0x41
        _emit 0x01
        _emit 0x00
        // mov byte ptr [ecx + 1], 0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x41
        _emit 0x08
        // movss dword ptr [ecx + 8], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x41
        _emit 0x04
        // movss dword ptr [ecx + 4], xmm0
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x18
        // mov edi, dword ptr [esp + 0x18]
        _emit 0x89
        _emit 0x79
        _emit 0x48
        // mov dword ptr [ecx + 0x48], edi
        _emit 0x89
        _emit 0x79
        _emit 0x38
        // mov dword ptr [ecx + 0x38], edi
        _emit 0x89
        _emit 0x79
        _emit 0x28
        // mov dword ptr [ecx + 0x28], edi
        _emit 0x89
        _emit 0x79
        _emit 0x18
        // mov dword ptr [ecx + 0x18], edi
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x49
        _emit 0x4C
        // movss dword ptr [ecx + 0x4c], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD0
        // mulss xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x51
        _emit 0x50
        // movss dword ptr [ecx + 0x50], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD8
        // mulss xmm3, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x59
        _emit 0x54
        // movss dword ptr [ecx + 0x54], xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE0
        // mulss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x61
        _emit 0x58
        // movss dword ptr [ecx + 0x58], xmm4
        _emit 0x8B
        _emit 0x41
        _emit 0x4C
        // mov eax, dword ptr [ecx + 0x4c]
        _emit 0x89
        _emit 0x41
        _emit 0x5C
        // mov dword ptr [ecx + 0x5c], eax
        _emit 0x8B
        _emit 0x51
        _emit 0x50
        // mov edx, dword ptr [ecx + 0x50]
        _emit 0x89
        _emit 0x51
        _emit 0x60
        // mov dword ptr [ecx + 0x60], edx
        _emit 0x8B
        _emit 0x41
        _emit 0x54
        // mov eax, dword ptr [ecx + 0x54]
        _emit 0x89
        _emit 0x41
        _emit 0x64
        // mov dword ptr [ecx + 0x64], eax
        _emit 0x8B
        _emit 0x51
        _emit 0x58
        // mov edx, dword ptr [ecx + 0x58]
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x51
        _emit 0x68
        // mov dword ptr [ecx + 0x68], edx
        _emit 0x5E
        // pop esi
        _emit 0xC2
        _emit 0x10
        _emit 0x00
        // ret 0x10
    }
}

// @ 0x00f4ff00  (315 bytes)
__declspec(naked) void FUN_00f4ff00()
{
    __asm {
        _emit 0x80
        _emit 0x7C
        _emit 0x24
        _emit 0x08
        _emit 0x00
        // cmp byte ptr [esp + 8], 0
        _emit 0x0F
        _emit 0x84
        _emit 0xBC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xf4ffc7
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x89
        _emit 0x51
        _emit 0x3C
        // mov dword ptr [ecx + 0x3c], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x89
        _emit 0x51
        _emit 0x40
        // mov dword ptr [ecx + 0x40], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x08
        // mov edx, dword ptr [eax + 8]
        _emit 0x89
        _emit 0x51
        _emit 0x44
        // mov dword ptr [ecx + 0x44], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x89
        _emit 0x51
        _emit 0x48
        // mov dword ptr [ecx + 0x48], edx
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x89
        _emit 0x51
        _emit 0x2C
        // mov dword ptr [ecx + 0x2c], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x89
        _emit 0x51
        _emit 0x30
        // mov dword ptr [ecx + 0x30], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x08
        // mov edx, dword ptr [eax + 8]
        _emit 0x89
        _emit 0x51
        _emit 0x34
        // mov dword ptr [ecx + 0x34], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x89
        _emit 0x51
        _emit 0x38
        // mov dword ptr [ecx + 0x38], edx
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x89
        _emit 0x51
        _emit 0x1C
        // mov dword ptr [ecx + 0x1c], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x89
        _emit 0x51
        _emit 0x20
        // mov dword ptr [ecx + 0x20], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x08
        // mov edx, dword ptr [eax + 8]
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0x89
        _emit 0x51
        _emit 0x24
        // mov dword ptr [ecx + 0x24], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x89
        _emit 0x51
        _emit 0x28
        // mov dword ptr [ecx + 0x28], edx
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x89
        _emit 0x51
        _emit 0x0C
        // mov dword ptr [ecx + 0xc], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x89
        _emit 0x51
        _emit 0x10
        // mov dword ptr [ecx + 0x10], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x08
        // mov edx, dword ptr [eax + 8]
        _emit 0x89
        _emit 0x51
        _emit 0x14
        // mov dword ptr [ecx + 0x14], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x89
        _emit 0x51
        _emit 0x18
        // mov dword ptr [ecx + 0x18], edx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x08
        // movss xmm1, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x50
        _emit 0x04
        // movss xmm2, dword ptr [eax + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x58
        _emit 0x08
        // movss xmm3, dword ptr [eax + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x60
        _emit 0x0C
        // movss xmm4, dword ptr [eax + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x49
        _emit 0x4C
        // movss dword ptr [ecx + 0x4c], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD0
        // mulss xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x51
        _emit 0x50
        // movss dword ptr [ecx + 0x50], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD8
        // mulss xmm3, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x59
        _emit 0x54
        // movss dword ptr [ecx + 0x54], xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE0
        // mulss xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x61
        _emit 0x58
        // movss dword ptr [ecx + 0x58], xmm4
        _emit 0x8B
        _emit 0x41
        _emit 0x4C
        // mov eax, dword ptr [ecx + 0x4c]
        _emit 0x89
        _emit 0x41
        _emit 0x5C
        // mov dword ptr [ecx + 0x5c], eax
        _emit 0x8B
        _emit 0x51
        _emit 0x50
        // mov edx, dword ptr [ecx + 0x50]
        _emit 0x89
        _emit 0x51
        _emit 0x60
        // mov dword ptr [ecx + 0x60], edx
        _emit 0x8B
        _emit 0x41
        _emit 0x54
        // mov eax, dword ptr [ecx + 0x54]
        _emit 0x89
        _emit 0x41
        _emit 0x64
        // mov dword ptr [ecx + 0x64], eax
        _emit 0x8B
        _emit 0x51
        _emit 0x58
        // mov edx, dword ptr [ecx + 0x58]
        _emit 0x89
        _emit 0x51
        _emit 0x68
        // mov dword ptr [ecx + 0x68], edx
        _emit 0xC6
        _emit 0x01
        _emit 0x00
        // mov byte ptr [ecx], 0
        _emit 0xC6
        _emit 0x41
        _emit 0x01
        _emit 0x00
        // mov byte ptr [ecx + 1], 0
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x04
        // mov edx, dword ptr [esp + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x02
        // movss xmm0, dword ptr [edx]
        _emit 0x0F
        _emit 0x2E
        _emit 0x41
        _emit 0x3C
        // ucomiss xmm0, dword ptr [ecx + 0x3c]
        _emit 0x9F
        // lahf 
        _emit 0xF6
        _emit 0xC4
        _emit 0x44
        // test ah, 0x44
        _emit 0x7A
        _emit 0x2D
        // jp 0xf50006
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x42
        _emit 0x04
        // movss xmm0, dword ptr [edx + 4]
        _emit 0x0F
        _emit 0x2E
        _emit 0x41
        _emit 0x40
        // ucomiss xmm0, dword ptr [ecx + 0x40]
        _emit 0x9F
        // lahf 
        _emit 0xF6
        _emit 0xC4
        _emit 0x44
        // test ah, 0x44
        _emit 0x7A
        _emit 0x1E
        // jp 0xf50006
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x42
        _emit 0x08
        // movss xmm0, dword ptr [edx + 8]
        _emit 0x0F
        _emit 0x2E
        _emit 0x41
        _emit 0x44
        // ucomiss xmm0, dword ptr [ecx + 0x44]
        _emit 0x9F
        // lahf 
        _emit 0xF6
        _emit 0xC4
        _emit 0x44
        // test ah, 0x44
        _emit 0x7A
        _emit 0x0F
        // jp 0xf50006
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x42
        _emit 0x0C
        // movss xmm0, dword ptr [edx + 0xc]
        _emit 0x0F
        _emit 0x2E
        _emit 0x41
        _emit 0x48
        // ucomiss xmm0, dword ptr [ecx + 0x48]
        _emit 0x9F
        // lahf 
        _emit 0xF6
        _emit 0xC4
        _emit 0x44
        // test ah, 0x44
        _emit 0x7B
        _emit 0x32
        // jnp 0xf50038
        _emit 0x8B
        _emit 0x41
        _emit 0x1C
        // mov eax, dword ptr [ecx + 0x1c]
        _emit 0x89
        _emit 0x41
        _emit 0x0C
        // mov dword ptr [ecx + 0xc], eax
        _emit 0x8B
        _emit 0x41
        _emit 0x20
        // mov eax, dword ptr [ecx + 0x20]
        _emit 0x89
        _emit 0x41
        _emit 0x10
        // mov dword ptr [ecx + 0x10], eax
        _emit 0x8B
        _emit 0x41
        _emit 0x24
        // mov eax, dword ptr [ecx + 0x24]
        _emit 0x89
        _emit 0x41
        _emit 0x14
        // mov dword ptr [ecx + 0x14], eax
        _emit 0x8B
        _emit 0x41
        _emit 0x28
        // mov eax, dword ptr [ecx + 0x28]
        _emit 0x89
        _emit 0x41
        _emit 0x18
        // mov dword ptr [ecx + 0x18], eax
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x89
        _emit 0x41
        _emit 0x3C
        // mov dword ptr [ecx + 0x3c], eax
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0x89
        _emit 0x41
        _emit 0x40
        // mov dword ptr [ecx + 0x40], eax
        _emit 0x8B
        _emit 0x42
        _emit 0x08
        // mov eax, dword ptr [edx + 8]
        _emit 0x89
        _emit 0x41
        _emit 0x44
        // mov dword ptr [ecx + 0x44], eax
        _emit 0x8B
        _emit 0x52
        _emit 0x0C
        // mov edx, dword ptr [edx + 0xc]
        _emit 0x89
        _emit 0x51
        _emit 0x48
        // mov dword ptr [ecx + 0x48], edx
        _emit 0xC6
        _emit 0x01
        _emit 0x01
        // mov byte ptr [ecx], 1
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00f50040  (362 bytes)
__declspec(naked) void FUN_00f50040()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0xC7
        _emit 0x06
        _emit 0x10
        _emit 0xE8
        _emit 0x48
        _emit 0x01
        // mov dword ptr [esi], 0x148e810
        _emit 0xC7
        _emit 0x46
        _emit 0x04
        _emit 0xFC
        _emit 0xE7
        _emit 0x48
        _emit 0x01
        // mov dword ptr [esi + 4], 0x148e7fc
        _emit 0xC7
        _emit 0x46
        _emit 0x08
        _emit 0xF8
        _emit 0xE7
        _emit 0x48
        _emit 0x01
        // mov dword ptr [esi + 8], 0x148e7f8
        _emit 0x8B
        _emit 0x8E
        _emit 0x0C
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x30c]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x07
        // je 0xf50068
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
        _emit 0x86
        _emit 0x48
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x248]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xf50081
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xf50081
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x86
        _emit 0x34
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x234]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xf5009a
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xf5009a
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x86
        _emit 0x20
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x220]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xf500b3
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xf500b3
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x86
        _emit 0x0C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x20c]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xf500cc
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xf500cc
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x86
        _emit 0xF8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x1f8]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xf500e5
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xf500e5
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x86
        _emit 0xE4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x1e4]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xf500fe
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xf500fe
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x86
        _emit 0xD0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x1d0]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xf50117
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xf50117
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x86
        _emit 0xBC
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x1bc]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xf50130
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xf50130
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x86
        _emit 0xA8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x1a8]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xf50149
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xf50149
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x86
        _emit 0x94
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x194]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xf50162
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xf50162
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x86
        _emit 0x80
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x180]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xf5017b
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xf5017b
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x86
        _emit 0x6C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x16c]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xf50194
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xf50194
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0xC7
        _emit 0x46
        _emit 0x08
        _emit 0x94
        _emit 0xF0
        _emit 0x3E
        _emit 0x01
        // mov dword ptr [esi + 8], 0x13ef094
        _emit 0xC7
        _emit 0x46
        _emit 0x04
        _emit 0x94
        _emit 0xB3
        _emit 0x3E
        _emit 0x01
        // mov dword ptr [esi + 4], 0x13eb394
        _emit 0xC7
        _emit 0x06
        _emit 0x38
        _emit 0xB9
        _emit 0x3E
        _emit 0x01
        // mov dword ptr [esi], 0x13eb938
        _emit 0x5E
        // pop esi
        _emit 0xC3
        // ret 
    }
}

// @ 0x00f501d0  (217 bytes)
__declspec(naked) void FUN_00f501d0()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        call FUN_00f48aa0
        _emit 0xB9
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, 1
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x5D
        // je 0xf5023e
        _emit 0x84
        _emit 0x0D
        _emit 0xC0
        _emit 0x91
        _emit 0x6C
        _emit 0x01
        // test byte ptr [0x16c91c0], cl
        _emit 0x75
        _emit 0x06
        // jne 0xf501ef
        _emit 0x09
        _emit 0x0D
        _emit 0xC0
        _emit 0x91
        _emit 0x6C
        _emit 0x01
        // or dword ptr [0x16c91c0], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x46
        _emit 0x28
        // movss xmm0, dword ptr [esi + 0x28]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4E
        _emit 0x54
        // movss xmm1, dword ptr [esi + 0x54]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x56
        _emit 0x58
        // movss xmm2, dword ptr [esi + 0x58]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5E
        _emit 0x5C
        // movss xmm3, dword ptr [esi + 0x5c]
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x08
        // mov esi, dword ptr [esp + 8]
        _emit 0x68
        _emit 0xB4
        _emit 0x91
        _emit 0x6C
        _emit 0x01
        // push 0x16c91b4
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD0
        // mulss xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD8
        // mulss xmm3, xmm0
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x0D
        _emit 0xB4
        _emit 0x91
        _emit 0x6C
        _emit 0x01
        // movss dword ptr [0x16c91b4], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x15
        _emit 0xB8
        _emit 0x91
        _emit 0x6C
        _emit 0x01
        // movss dword ptr [0x16c91b8], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x1D
        _emit 0xBC
        _emit 0x91
        _emit 0x6C
        _emit 0x01
        // movss dword ptr [0x16c91bc], xmm3
        call FUN_00f98800
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x5E
        // pop esi
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0x84
        _emit 0x0D
        _emit 0xC0
        _emit 0x91
        _emit 0x6C
        _emit 0x01
        // test byte ptr [0x16c91c0], cl
        _emit 0x75
        _emit 0x06
        // jne 0xf5024c
        _emit 0x09
        _emit 0x0D
        _emit 0xC0
        _emit 0x91
        _emit 0x6C
        _emit 0x01
        // or dword ptr [0x16c91c0], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4E
        _emit 0x28
        // movss xmm1, dword ptr [esi + 0x28]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x56
        _emit 0x58
        // movss xmm2, dword ptr [esi + 0x58]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5E
        _emit 0x5C
        // movss xmm3, dword ptr [esi + 0x5c]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0x0F
        _emit 0x28
        _emit 0xC1
        // movaps xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x46
        _emit 0x54
        // mulss xmm0, dword ptr [esi + 0x54]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x05
        _emit 0xB4
        _emit 0x91
        _emit 0x6C
        _emit 0x01
        // movss dword ptr [0x16c91b4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD1
        // mulss xmm2, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x15
        _emit 0xB8
        _emit 0x91
        _emit 0x6C
        _emit 0x01
        // movss dword ptr [0x16c91b8], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD9
        // mulss xmm3, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x1D
        _emit 0xBC
        _emit 0x91
        _emit 0x6C
        _emit 0x01
        // movss dword ptr [0x16c91bc], xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x00
        // movss dword ptr [eax], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0xB8
        _emit 0x91
        _emit 0x6C
        _emit 0x01
        // movss xmm0, dword ptr [0x16c91b8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x40
        _emit 0x04
        // movss dword ptr [eax + 4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0xBC
        _emit 0x91
        _emit 0x6C
        _emit 0x01
        // movss xmm0, dword ptr [0x16c91bc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x40
        _emit 0x08
        // movss dword ptr [eax + 8], xmm0
        _emit 0x5E
        // pop esi
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}
