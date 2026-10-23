// Slice s00aecf90: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_004558a0();
extern "C" void FUN_0050d4e0();
extern "C" void FUN_0067dcc0();
extern "C" void FUN_0067de30();
extern "C" void FUN_006a0ae0();
extern "C" void FUN_00926060();
extern "C" void FUN_009fdab0();
extern "C" void FUN_00ae9040();
extern "C" void FUN_00ae93f0();
extern "C" void FUN_00ae9490();
extern "C" void FUN_00ae9500();
extern "C" void FUN_00ae9930();
extern "C" void FUN_00aea1b0();
extern "C" void FUN_00aeb160();
extern "C" void FUN_00aeb720();
extern "C" void FUN_00aeb960();
extern "C" void FUN_00aebe90();
extern "C" void FUN_00aed050();
extern "C" void FUN_00b3d2a0();
extern "C" void FUN_00b3d300();
extern "C" void FUN_00b3d3e0();
extern "C" void FUN_00b3d4a0();
extern "C" void FUN_00ba5bc0();
extern "C" void FUN_00ba6d80();
extern "C" void FUN_00ba6dc0();
extern "C" void FUN_00ba9370();
extern "C" void FUN_00bfc5f0();
extern "C" void FUN_00c77bf0();
extern "C" void FUN_00dd6d10();
extern "C" void FUN_00f47380();
extern "C" void FUN_00f473a0();
extern "C" void FUN_00f67d90();
extern "C" void FUN_00fe4180();
extern "C" void FUN_00feb9f0();
extern "C" void FUN_00fee930();
extern "C" void FUN_01002bd0();
extern "C" void FUN_01021090();
extern "C" void FUN_01045a60();
extern "C" void FUN_01046fc0();

// @ 0x00aecf90  (184 bytes)
__declspec(naked) void FUN_00aecf90()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x68
        _emit 0x86
        _emit 0x6A
        _emit 0x7F
        _emit 0x05
        // push 0x57f6a86
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        call FUN_00b3d300
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00f67d90
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00c77bf0
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov ebx, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x14
        // mov ebp, dword ptr [esp + 0x14]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        call FUN_00b3d4a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ae9500
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x75
        // je 0xaed041
        _emit 0x55
        // push ebp
        call FUN_00b3d2a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ba9370
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x64
        // je 0xaed041
        _emit 0x8B
        _emit 0x0D
        _emit 0x08
        _emit 0x0D
        _emit 0x6E
        _emit 0x01
        // mov ecx, dword ptr [0x16e0d08]
        _emit 0x53
        // push ebx
        _emit 0x89
        _emit 0x41
        _emit 0x1C
        // mov dword ptr [ecx + 0x1c], eax
        call FUN_00b3d2a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ba6d80
        _emit 0x8B
        _emit 0x15
        _emit 0x08
        _emit 0x0D
        _emit 0x6E
        _emit 0x01
        // mov edx, dword ptr [0x16e0d08]
        _emit 0x89
        _emit 0x42
        _emit 0x10
        // mov dword ptr [edx + 0x10], eax
        _emit 0x8B
        _emit 0x46
        _emit 0x34
        // mov eax, dword ptr [esi + 0x34]
        _emit 0x50
        // push eax
        call FUN_00b3d2a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ba6dc0
        _emit 0x8B
        _emit 0x0D
        _emit 0x08
        _emit 0x0D
        _emit 0x6E
        _emit 0x01
        // mov ecx, dword ptr [0x16e0d08]
        _emit 0x89
        _emit 0x41
        _emit 0x0C
        // mov dword ptr [ecx + 0xc], eax
        _emit 0x8B
        _emit 0x56
        _emit 0x10
        // mov edx, dword ptr [esi + 0x10]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x52
        // push edx
        call FUN_01046fc0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_01045a60
        _emit 0x8B
        _emit 0x46
        _emit 0x14
        // mov eax, dword ptr [esi + 0x14]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x50
        // push eax
        call FUN_00b3d3e0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00dd6d10
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_00aebe90
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00aed050  (140 bytes)
__declspec(naked) void FUN_00aed050()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x2C
        // sub esp, 0x2c
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x38
        // mov edi, dword ptr [esp + 0x38]
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
        call FUN_00aea1b0
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
        _emit 0x74
        _emit 0x0B
        // je 0xaed080
        _emit 0x5F
        // pop edi
        _emit 0x83
        _emit 0xC0
        _emit 0x04
        // add eax, 4
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x2C
        // add esp, 0x2c
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0x53
        // push ebx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // lea eax, [esp + 0xc]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x50
        // push eax
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // lea ecx, [esp + 0x28]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ebx
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
        call FUN_009fdab0
        _emit 0x88
        _emit 0x5C
        _emit 0x24
        _emit 0x3C
        // mov byte ptr [esp + 0x3c], bl
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x3C
        // mov ecx, dword ptr [esp + 0x3c]
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // lea edx, [esp + 0x14]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00aeb960
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x0C
        // mov esi, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // mov eax, dword ptr [esp + 0x24]
        _emit 0x83
        _emit 0xC6
        _emit 0x04
        // add esi, 4
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x74
        _emit 0x0E
        // je 0xaed0d1
        _emit 0x39
        _emit 0x58
        _emit 0xFC
        // cmp dword ptr [eax - 4], ebx
        _emit 0x74
        _emit 0x09
        // je 0xaed0d1
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x5B
        // pop ebx
        _emit 0x5F
        // pop edi
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x5E
        // pop esi
        _emit 0x83
        _emit 0xC4
        _emit 0x2C
        // add esp, 0x2c
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00aed0e0  (473 bytes)
__declspec(naked) void FUN_00aed0e0()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x3C
        // sub esp, 0x3c
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], edi
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x74
        _emit 0x05
        // je 0xaed0f7
        _emit 0x8D
        _emit 0x77
        _emit 0x1C
        // lea esi, [edi + 0x1c]
        _emit 0xEB
        _emit 0x02
        // jmp 0xaed0f9
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0x38
        _emit 0xD0
        _emit 0x80
        _emit 0x05
        // push 0x580d038
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x24
        // mov eax, dword ptr [edx + 0x24]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x74
        _emit 0x05
        // je 0xaed116
        _emit 0x8D
        _emit 0x77
        _emit 0x1C
        // lea esi, [edi + 0x1c]
        _emit 0xEB
        _emit 0x02
        // jmp 0xaed118
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0x26
        _emit 0xC3
        _emit 0x53
        _emit 0x01
        // push 0x153c326
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x24
        // mov eax, dword ptr [edx + 0x24]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x74
        _emit 0x05
        // je 0xaed135
        _emit 0x8D
        _emit 0x77
        _emit 0x1C
        // lea esi, [edi + 0x1c]
        _emit 0xEB
        _emit 0x02
        // jmp 0xaed137
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0x55
        // push ebp
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0xD9
        _emit 0xF3
        _emit 0x09
        _emit 0x06
        // push 0x609f3d9
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x24
        // mov eax, dword ptr [edx + 0x24]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x38
        // mov dword ptr [esp + 0x38], ebx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x3C
        // mov dword ptr [esp + 0x3c], ebx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x40
        // mov dword ptr [esp + 0x40], ebx
        call FUN_0067de30
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0x52
        _emit 0x48
        // mov edx, dword ptr [edx + 0x48]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x38
        // lea ecx, [esp + 0x38]
        _emit 0x51
        // push ecx
        _emit 0x68
        _emit 0x29
        _emit 0xC2
        _emit 0x09
        _emit 0x06
        // push 0x609c229
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x3C
        // mov edi, dword ptr [esp + 0x3c]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // mov eax, dword ptr [esp + 0x38]
        _emit 0x2B
        _emit 0xF8
        // sub edi, eax
        _emit 0xC1
        _emit 0xFF
        _emit 0x02
        // sar edi, 2
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], edi
        _emit 0x0F
        _emit 0x8E
        _emit 0x14
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jle 0xaed29f
        _emit 0xEB
        _emit 0x03
        // jmp 0xaed190
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ebx
        call FUN_0067de30
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x0B
        // je 0xaed1ae
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ebx
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
        _emit 0x54
        _emit 0x24
        _emit 0x38
        // mov edx, dword ptr [esp + 0x38]
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // lea ecx, [esp + 0x10]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x0C
        _emit 0xAA
        // mov ecx, dword ptr [edx + ebp*4]
        _emit 0x8B
        _emit 0x50
        _emit 0x2C
        // mov edx, dword ptr [eax + 0x2c]
        _emit 0x68
        _emit 0x29
        _emit 0xC2
        _emit 0x09
        _emit 0x06
        // push 0x609c229
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x0F
        _emit 0x84
        _emit 0xBD
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xaed292
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x18
        // lea edx, [esp + 0x18]
        _emit 0x52
        // push edx
        _emit 0x68
        _emit 0xA3
        _emit 0xD0
        _emit 0x09
        _emit 0x06
        // push 0x609d0a3
        _emit 0x50
        // push eax
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], ebx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], ebx
        call FUN_006a0ae0
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        _emit 0x33
        _emit 0xFF
        // xor edi, edi
        _emit 0x39
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // cmp dword ptr [esp + 0x14], ebx
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], esi
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], eax
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], ebx
        _emit 0x7E
        _emit 0x40
        // jle 0xaed24d
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x8D
        _emit 0x14
        _emit 0x0E
        // lea edx, [esi + ecx]
        _emit 0x3B
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // cmp eax, dword ptr [esp + 0x2c]
        _emit 0x73
        _emit 0x13
        // jae 0xaed230
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x83
        _emit 0xC0
        _emit 0x04
        // add eax, 4
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], eax
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x15
        // je 0xaed23f
        _emit 0x8B
        _emit 0x12
        // mov edx, dword ptr [edx]
        _emit 0x89
        _emit 0x11
        // mov dword ptr [ecx], edx
        _emit 0xEB
        _emit 0x0F
        // jmp 0xaed23f
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // lea ecx, [esp + 0x2c]
        call FUN_004558a0
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // mov eax, dword ptr [esp + 0x28]
        _emit 0x47
        // inc edi
        _emit 0x83
        _emit 0xC6
        _emit 0x0C
        // add esi, 0xc
        _emit 0x3B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // cmp edi, dword ptr [esp + 0x14]
        _emit 0x7C
        _emit 0xC7
        // jl 0xaed210
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x24
        // mov esi, dword ptr [esp + 0x24]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // mov eax, dword ptr [esp + 0x38]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // lea ecx, [esp + 0x24]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // mov ecx, dword ptr [esp + 0x24]
        _emit 0x8D
        _emit 0x04
        _emit 0xA8
        // lea eax, [eax + ebp*4]
        _emit 0x50
        // push eax
        _emit 0x83
        _emit 0xC1
        _emit 0x40
        // add ecx, 0x40
        call FUN_00aed050
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_0050d4e0
        _emit 0x3B
        _emit 0xF3
        // cmp esi, ebx
        _emit 0x74
        _emit 0x0E
        // je 0xaed27f
        _emit 0x39
        _emit 0x5E
        _emit 0xFC
        // cmp dword ptr [esi - 4], ebx
        _emit 0x74
        _emit 0x09
        // je 0xaed27f
        _emit 0x56
        // push esi
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x07
        // je 0xaed28e
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
        _emit 0x7C
        _emit 0x24
        _emit 0x1C
        // mov edi, dword ptr [esp + 0x1c]
        _emit 0x45
        // inc ebp
        _emit 0x3B
        _emit 0xEF
        // cmp ebp, edi
        _emit 0x0F
        _emit 0x8C
        _emit 0xF5
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jl 0xaed190
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // mov eax, dword ptr [esp + 0x38]
        _emit 0x5D
        // pop ebp
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x74
        _emit 0x0E
        // je 0xaed2b2
        _emit 0x39
        _emit 0x58
        _emit 0xFC
        // cmp dword ptr [eax - 4], ebx
        _emit 0x74
        _emit 0x09
        // je 0xaed2b2
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x3C
        // add esp, 0x3c
        _emit 0xC3
        // ret 
    }
}

// @ 0x00aed2c0  (272 bytes)
__declspec(naked) void FUN_00aed2c0()
{
    __asm {
        _emit 0x51
        // push ecx
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        // mov edi, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x83
        _emit 0xFF
        _emit 0xFF
        // cmp edi, -1
        _emit 0x0F
        _emit 0x84
        _emit 0xF8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xaed3ca
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov ebx, dword ptr [esp + 0x18]
        _emit 0x55
        // push ebp
        _emit 0x6A
        _emit 0x02
        // push 2
        _emit 0x53
        // push ebx
        _emit 0x57
        // push edi
        call FUN_00ae9490
        _emit 0x8B
        _emit 0xE8
        // mov ebp, eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x85
        _emit 0xED
        // test ebp, ebp
        _emit 0x75
        _emit 0x52
        // jne 0xaed33b
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x18
        // lea edx, [esp + 0x18]
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // lea eax, [esp + 0x20]
        _emit 0x50
        // push eax
        _emit 0x53
        // push ebx
        _emit 0x57
        // push edi
        call FUN_00ae9040
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x26
        // je 0xaed324
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // mov edx, dword ptr [esp + 0x1c]
        _emit 0x55
        // push ebp
        _emit 0x55
        // push ebp
        _emit 0x55
        // push ebp
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        _emit 0x53
        // push ebx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00aeb160
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00aebe90
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x59
        // pop ecx
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x6A
        _emit 0xFF
        // push -1
        _emit 0x6A
        _emit 0xFF
        // push -1
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x53
        // push ebx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00ae93f0
        _emit 0x8B
        _emit 0xE8
        // mov ebp, eax
        _emit 0x85
        _emit 0xED
        // test ebp, ebp
        _emit 0x74
        _emit 0x34
        // je 0xaed36d
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x55
        // push ebp
        call FUN_00aebe90
        _emit 0x8B
        _emit 0x45
        _emit 0x14
        // mov eax, dword ptr [ebp + 0x14]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x50
        // push eax
        call FUN_00b3d3e0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00dd6d10
        _emit 0x8B
        _emit 0x4D
        _emit 0x10
        // mov ecx, dword ptr [ebp + 0x10]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x51
        // push ecx
        call FUN_01046fc0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_01045a60
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x59
        // pop ecx
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // lea edx, [esp + 0x10]
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // lea eax, [esp + 0x1c]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // lea ecx, [esp + 0x24]
        _emit 0x51
        // push ecx
        _emit 0x53
        // push ebx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x24], 0
        call FUN_00ae9930
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov edx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov eax, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov ecx, dword ptr [esp + 0x1c]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x53
        // push ebx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00aeb720
        call FUN_01021090
        _emit 0x3B
        _emit 0xF8
        // cmp edi, eax
        _emit 0x74
        _emit 0x18
        // je 0xaed3c8
        _emit 0x57
        // push edi
        call FUN_00b3d2a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ba9370
        _emit 0x6A
        _emit 0x05
        // push 5
        _emit 0x50
        // push eax
        call FUN_00ba5bc0
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x59
        // pop ecx
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00aed3d0  (30 bytes)
__declspec(naked) void FUN_00aed3d0()
{
    __asm {
        _emit 0x8B
        _emit 0x0D
        _emit 0xF4
        _emit 0xAC
        _emit 0x67
        _emit 0x01
        // mov ecx, dword ptr [0x167acf4]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x13
        // je 0xaed3ed
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x2C
        // mov edx, dword ptr [eax + 0x2c]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0xC7
        _emit 0x05
        _emit 0xF4
        _emit 0xAC
        _emit 0x67
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [0x167acf4], 0
        _emit 0xC3
        // ret 
    }
}

// @ 0x00aed4d0  (52 bytes)
__declspec(naked) void FUN_00aed4d0()
{
    __asm {
        _emit 0xA1
        _emit 0xF4
        _emit 0xAC
        _emit 0x67
        _emit 0x01
        // mov eax, dword ptr [0x167acf4]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x75
        _emit 0x2A
        // jne 0xaed503
        _emit 0x50
        // push eax
        _emit 0x50
        // push eax
        _emit 0x50
        // push eax
        _emit 0x50
        // push eax
        _emit 0x68
        _emit 0xB4
        _emit 0x09
        _emit 0x3F
        _emit 0x01
        // push 0x13f09b4
        _emit 0x6A
        _emit 0x04
        // push 4
        call FUN_00f473a0
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0C
        // je 0xaed4fc
        _emit 0xC7
        _emit 0x00
        _emit 0xB4
        _emit 0xC0
        _emit 0x45
        _emit 0x01
        // mov dword ptr [eax], 0x145c0b4
        _emit 0xA3
        _emit 0xF4
        _emit 0xAC
        _emit 0x67
        _emit 0x01
        // mov dword ptr [0x167acf4], eax
        _emit 0xC3
        // ret 
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0xA3
        _emit 0xF4
        _emit 0xAC
        _emit 0x67
        _emit 0x01
        // mov dword ptr [0x167acf4], eax
        _emit 0xC3
        // ret 
    }
}

// @ 0x00aed550  (45 bytes)
__declspec(naked) void FUN_00aed550()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8B
        _emit 0x4E
        _emit 0x08
        // mov ecx, dword ptr [esi + 8]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x07
        // je 0xaed561
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
        _emit 0xF6
        _emit 0x44
        _emit 0x24
        _emit 0x08
        _emit 0x01
        // test byte ptr [esp + 8], 1
        _emit 0xC7
        _emit 0x06
        _emit 0xB8
        _emit 0xFF
        _emit 0x3E
        _emit 0x01
        // mov dword ptr [esi], 0x13effb8
        _emit 0x74
        _emit 0x09
        // je 0xaed577
        _emit 0x56
        // push esi
        call FUN_00926060
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

// @ 0x00aed580  (379 bytes)
__declspec(naked) void FUN_00aed580()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x28
        // sub esp, 0x28
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // mov eax, dword ptr [esp + 0x30]
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x58
        _emit 0x0C
        // mov ebx, dword ptr [eax + 0xc]
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x68
        _emit 0x10
        // mov ebp, dword ptr [eax + 0x10]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x38
        // mov esi, dword ptr [esp + 0x38]
        _emit 0x23
        _emit 0x4E
        _emit 0x14
        // and ecx, dword ptr [esi + 0x14]
        _emit 0x23
        _emit 0x56
        _emit 0x18
        // and edx, dword ptr [esi + 0x18]
        _emit 0x23
        _emit 0x5E
        _emit 0x20
        // and ebx, dword ptr [esi + 0x20]
        _emit 0x23
        _emit 0x6E
        _emit 0x24
        // and ebp, dword ptr [esi + 0x24]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x78
        _emit 0x08
        // mov edi, dword ptr [eax + 8]
        _emit 0x23
        _emit 0x7E
        _emit 0x1C
        // and edi, dword ptr [esi + 0x1c]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ecx
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], edx
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], edi
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ebx
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], ebp
        _emit 0x33
        _emit 0xC9
        // xor ecx, ecx
        _emit 0x83
        _emit 0x7C
        _emit 0x8C
        _emit 0x10
        _emit 0x00
        // cmp dword ptr [esp + ecx*4 + 0x10], 0
        _emit 0x0F
        _emit 0x85
        _emit 0x22
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jne 0xaed6ef
        _emit 0x41
        // inc ecx
        _emit 0x83
        _emit 0xF9
        _emit 0x05
        // cmp ecx, 5
        _emit 0x72
        _emit 0xEF
        // jb 0xaed5c2
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0x78
        _emit 0x04
        // mov edi, dword ptr [eax + 4]
        _emit 0x8B
        _emit 0x58
        _emit 0x08
        // mov ebx, dword ptr [eax + 8]
        _emit 0x8B
        _emit 0x68
        _emit 0x0C
        // mov ebp, dword ptr [eax + 0xc]
        _emit 0x23
        _emit 0x6E
        _emit 0x0C
        // and ebp, dword ptr [esi + 0xc]
        _emit 0x8B
        _emit 0x40
        _emit 0x10
        // mov eax, dword ptr [eax + 0x10]
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x23
        _emit 0x7E
        _emit 0x04
        // and edi, dword ptr [esi + 4]
        _emit 0x23
        _emit 0x5E
        _emit 0x08
        // and ebx, dword ptr [esi + 8]
        _emit 0x33
        _emit 0x7E
        _emit 0x04
        // xor edi, dword ptr [esi + 4]
        _emit 0x33
        _emit 0x5E
        _emit 0x08
        // xor ebx, dword ptr [esi + 8]
        _emit 0x23
        _emit 0xD1
        // and edx, ecx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], eax
        _emit 0x8B
        _emit 0x46
        _emit 0x10
        // mov eax, dword ptr [esi + 0x10]
        _emit 0x21
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // and dword ptr [esp + 0x20], eax
        _emit 0x33
        _emit 0xCA
        // xor ecx, edx
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x30
        // mov dword ptr [esp + 0x30], ebp
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x20
        // mov ebp, dword ptr [esp + 0x20]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], edx
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x30
        // mov edx, dword ptr [esp + 0x30]
        _emit 0x33
        _emit 0x56
        _emit 0x0C
        // xor edx, dword ptr [esi + 0xc]
        _emit 0x33
        _emit 0xE8
        // xor ebp, eax
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ecx
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], edi
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], ebx
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], edx
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], ebp
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x83
        _emit 0x7C
        _emit 0x84
        _emit 0x10
        _emit 0x00
        // cmp dword ptr [esp + eax*4 + 0x10], 0
        _emit 0x0F
        _emit 0x85
        _emit 0xB4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0xaed6ef
        _emit 0x40
        // inc eax
        _emit 0x83
        _emit 0xF8
        _emit 0x05
        // cmp eax, 5
        _emit 0x72
        _emit 0xEF
        // jb 0xaed630
        _emit 0x8B
        _emit 0x7E
        _emit 0x78
        // mov edi, dword ptr [esi + 0x78]
        _emit 0x2B
        _emit 0x7E
        _emit 0x74
        // sub edi, dword ptr [esi + 0x74]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0xC1
        _emit 0xFF
        _emit 0x02
        // sar edi, 2
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x7E
        _emit 0x27
        // jle 0xaed677
        _emit 0x8B
        _emit 0x4E
        _emit 0x74
        // mov ecx, dword ptr [esi + 0x74]
        _emit 0x8B
        _emit 0x04
        _emit 0x99
        // mov eax, dword ptr [ecx + ebx*4]
        _emit 0x50
        // push eax
        call FUN_01002bd0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bfc5f0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00fe4180
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x0F
        _emit 0x84
        _emit 0x7D
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xaed6ef
        _emit 0x43
        // inc ebx
        _emit 0x3B
        _emit 0xDF
        // cmp ebx, edi
        _emit 0x7C
        _emit 0xD9
        // jl 0xaed650
        _emit 0x8B
        _emit 0xBE
        _emit 0xA0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edi, dword ptr [esi + 0xa0]
        _emit 0x2B
        _emit 0xBE
        _emit 0x9C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // sub edi, dword ptr [esi + 0x9c]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0xC1
        _emit 0xFF
        _emit 0x02
        // sar edi, 2
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x7E
        _emit 0x23
        // jle 0xaed6af
        _emit 0x8D
        _emit 0x64
        _emit 0x24
        _emit 0x00
        // lea esp, [esp]
        _emit 0x8B
        _emit 0x96
        _emit 0x9C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x9c]
        _emit 0x8B
        _emit 0x04
        _emit 0x9A
        // mov eax, dword ptr [edx + ebx*4]
        _emit 0x50
        // push eax
        call FUN_00feb9f0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00fee930
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x45
        // je 0xaed6ef
        _emit 0x43
        // inc ebx
        _emit 0x3B
        _emit 0xDF
        // cmp ebx, edi
        _emit 0x7C
        _emit 0xE1
        // jl 0xaed690
        _emit 0x8B
        _emit 0xBE
        _emit 0xB4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edi, dword ptr [esi + 0xb4]
        _emit 0x2B
        _emit 0xBE
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // sub edi, dword ptr [esi + 0xb0]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0xC1
        _emit 0xFF
        _emit 0x02
        // sar edi, 2
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x7E
        _emit 0x1F
        // jle 0xaed6e3
        _emit 0x8B
        _emit 0x86
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0xb0]
        _emit 0x8B
        _emit 0x04
        _emit 0x98
        // mov eax, dword ptr [eax + ebx*4]
        _emit 0x50
        // push eax
        call FUN_00feb9f0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00fee930
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x75
        _emit 0x11
        // jne 0xaed6ef
        _emit 0x43
        // inc ebx
        _emit 0x3B
        _emit 0xDF
        // cmp ebx, edi
        _emit 0x7C
        _emit 0xE1
        // jl 0xaed6c4
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x28
        // add esp, 0x28
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x32
        _emit 0xC0
        // xor al, al
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x28
        // add esp, 0x28
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}
