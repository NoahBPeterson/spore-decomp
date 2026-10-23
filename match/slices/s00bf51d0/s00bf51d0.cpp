// Slice s00bf51d0: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_006a46a0();
extern "C" void FUN_009a9600();
extern "C" void FUN_00a110b0();
extern "C" void FUN_00ae9390();
extern "C" void FUN_00aea5d0();
extern "C" void FUN_00b20c60();
extern "C" void FUN_00b21340();
extern "C" void FUN_00b25ca0();
extern "C" void FUN_00b3d260();
extern "C" void FUN_00b3d300();
extern "C" void FUN_00b3d350();
extern "C" void FUN_00b3d4a0();
extern "C" void FUN_00b638b0();
extern "C" void FUN_00b81470();
extern "C" void FUN_00b88590();
extern "C" void FUN_00bab900();
extern "C" void FUN_00bd8210();
extern "C" void FUN_00bd9bf0();
extern "C" void FUN_00be5be0();
extern "C" void FUN_00befb80();
extern "C" void FUN_00bf0f90();
extern "C" void FUN_00bf2840();
extern "C" void FUN_00bf28b0();
extern "C" void FUN_00bf28f0();
extern "C" void FUN_00bf2960();
extern "C" void FUN_00bf29c0();
extern "C" void FUN_00bf2a10();
extern "C" void FUN_00bf49e0();
extern "C" void FUN_00bf4a90();
extern "C" void FUN_00bf5050();
extern "C" void FUN_00bf5630();
extern "C" void FUN_00c71040();
extern "C" void FUN_00c9eae0();
extern "C" void FUN_00ca6630();
extern "C" void FUN_00f47380();
extern "C" void FUN_00f473a0();
extern "C" void FUN_00ff0db0();
extern "C" void FUN_00ff2d20();
extern "C" void FUN_01021260();

// @ 0x00bf51d0  (78 bytes)
__declspec(naked) void FUN_00bf51d0()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x10
        // mov ebp, dword ptr [esp + 0x10]
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x47
        _emit 0x04
        // mov eax, dword ptr [edi + 4]
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        _emit 0x55
        // push ebp
        call FUN_00bf29c0
        _emit 0x8B
        _emit 0x5F
        _emit 0x04
        // mov ebx, dword ptr [edi + 4]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x73
        _emit 0x11
        // jae 0xbf5206
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x83
        _emit 0xC6
        _emit 0x20
        // add esi, 0x20
        _emit 0x3B
        _emit 0xF3
        // cmp esi, ebx
        _emit 0x72
        _emit 0xEF
        // jb 0xbf51f5
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x2B
        _emit 0xE8
        // sub ebp, eax
        _emit 0xC1
        _emit 0xFD
        _emit 0x05
        // sar ebp, 5
        _emit 0xF7
        _emit 0xDD
        // neg ebp
        _emit 0xC1
        _emit 0xE5
        _emit 0x05
        // shl ebp, 5
        _emit 0x01
        _emit 0x6F
        _emit 0x04
        // add dword ptr [edi + 4], ebp
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

// @ 0x00bf5220  (506 bytes)
__declspec(naked) void FUN_00bf5220()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x24
        // sub esp, 0x24
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
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0x4E
        _emit 0x08
        // mov ecx, dword ptr [esi + 8]
        _emit 0x2B
        _emit 0xC8
        // sub ecx, eax
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x3C
        // mov edi, dword ptr [esp + 0x3c]
        _emit 0xC1
        _emit 0xF9
        _emit 0x05
        // sar ecx, 5
        _emit 0x3B
        _emit 0xF9
        // cmp edi, ecx
        _emit 0x0F
        _emit 0x87
        _emit 0xF7
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // ja 0xbf5337
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x0F
        _emit 0x86
        _emit 0xC8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jbe 0xbf5410
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // mov ecx, dword ptr [esp + 0x40]
        _emit 0x8B
        _emit 0x51
        _emit 0x08
        // mov edx, dword ptr [ecx + 8]
        _emit 0x2B
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // sub eax, dword ptr [esp + 0x38]
        _emit 0x8B
        _emit 0x5E
        _emit 0x04
        // mov ebx, dword ptr [esi + 4]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], edx
        _emit 0x8B
        _emit 0x51
        _emit 0x0C
        // mov edx, dword ptr [ecx + 0xc]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], edx
        _emit 0x8B
        _emit 0x51
        _emit 0x10
        // mov edx, dword ptr [ecx + 0x10]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], edx
        _emit 0x8B
        _emit 0x51
        _emit 0x14
        // mov edx, dword ptr [ecx + 0x14]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], edx
        _emit 0x8A
        _emit 0x51
        _emit 0x18
        // mov dl, byte ptr [ecx + 0x18]
        _emit 0x8B
        _emit 0x49
        _emit 0x1C
        // mov ecx, dword ptr [ecx + 0x1c]
        _emit 0xC1
        _emit 0xF8
        _emit 0x05
        // sar eax, 5
        _emit 0x88
        _emit 0x54
        _emit 0x24
        _emit 0x2C
        // mov byte ptr [esp + 0x2c], dl
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x38
        // mov edx, dword ptr [esp + 0x38]
        _emit 0x8B
        _emit 0xE8
        // mov ebp, eax
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x18], 0
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x30
        // mov dword ptr [esp + 0x30], ecx
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x50
        _emit 0x44
        _emit 0x46
        _emit 0x01
        // mov dword ptr [esp + 0x14], 0x1464450
        _emit 0x52
        // push edx
        _emit 0x3B
        _emit 0xFD
        // cmp edi, ebp
        _emit 0x73
        _emit 0x47
        // jae 0xbf52e2
        _emit 0x53
        // push ebx
        _emit 0xC1
        _emit 0xE7
        _emit 0x05
        // shl edi, 5
        _emit 0x8B
        _emit 0xEB
        // mov ebp, ebx
        _emit 0x53
        // push ebx
        _emit 0x2B
        _emit 0xEF
        // sub ebp, edi
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x4C
        // lea eax, [esp + 0x4c]
        _emit 0x55
        // push ebp
        _emit 0x50
        // push eax
        call FUN_00bf2840
        _emit 0x01
        _emit 0x7E
        _emit 0x04
        // add dword ptr [esi + 4], edi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x4C
        // mov esi, dword ptr [esp + 0x4c]
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        call FUN_00bf2a10
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // lea ecx, [esp + 0x34]
        _emit 0x51
        // push ecx
        _emit 0x03
        _emit 0xFE
        // add edi, esi
        _emit 0x57
        // push edi
        _emit 0x56
        // push esi
        call FUN_00bf28b0
        _emit 0x83
        _emit 0xC4
        _emit 0x2C
        // add esp, 0x2c
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // lea ecx, [esp + 0x14]
        call FUN_00b638b0
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
        _emit 0x24
        // add esp, 0x24
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // lea eax, [esp + 0x18]
        _emit 0x50
        // push eax
        _emit 0x2B
        _emit 0xFD
        // sub edi, ebp
        _emit 0x57
        // push edi
        _emit 0x53
        // push ebx
        call FUN_00bf28f0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // mov ecx, dword ptr [esp + 0x48]
        _emit 0xC1
        _emit 0xE7
        _emit 0x05
        // shl edi, 5
        _emit 0x01
        _emit 0x7E
        _emit 0x04
        // add dword ptr [esi + 4], edi
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x48
        // mov edi, dword ptr [esp + 0x48]
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        _emit 0x53
        // push ebx
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x54
        // lea edx, [esp + 0x54]
        _emit 0x57
        // push edi
        _emit 0x52
        // push edx
        call FUN_00bf2840
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // lea eax, [esp + 0x38]
        _emit 0x50
        // push eax
        _emit 0x53
        // push ebx
        _emit 0xC1
        _emit 0xE5
        _emit 0x05
        // shl ebp, 5
        _emit 0x01
        _emit 0x6E
        _emit 0x04
        // add dword ptr [esi + 4], ebp
        _emit 0x57
        // push edi
        call FUN_00bf28b0
        _emit 0x83
        _emit 0xC4
        _emit 0x30
        // add esp, 0x30
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // lea ecx, [esp + 0x14]
        call FUN_00b638b0
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
        _emit 0x24
        // add esp, 0x24
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
        _emit 0x2B
        _emit 0x06
        // sub eax, dword ptr [esi]
        _emit 0xC1
        _emit 0xF8
        _emit 0x05
        // sar eax, 5
        _emit 0x8D
        _emit 0x0C
        _emit 0x00
        // lea ecx, [eax + eax]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x77
        _emit 0x05
        // ja 0xbf5348
        _emit 0xB9
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, 1
        _emit 0x03
        _emit 0xC7
        // add eax, edi
        _emit 0x3B
        _emit 0xC8
        // cmp ecx, eax
        _emit 0x76
        _emit 0x06
        // jbe 0xbf5354
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x3C
        // mov dword ptr [esp + 0x3c], ecx
        _emit 0xEB
        _emit 0x06
        // jmp 0xbf535a
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        // mov dword ptr [esp + 0x3c], eax
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x23
        // je 0xbf5381
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
        _emit 0xC1
        _emit 0xE1
        _emit 0x05
        // shl ecx, 5
        _emit 0x68
        _emit 0xB4
        _emit 0x09
        _emit 0x3F
        _emit 0x01
        // push 0x13f09b4
        _emit 0x51
        // push ecx
        call FUN_00f473a0
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x8B
        _emit 0xE8
        // mov ebp, eax
        _emit 0xEB
        _emit 0x02
        // jmp 0xbf5383
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x38
        // mov ebx, dword ptr [esp + 0x38]
        _emit 0x55
        // push ebp
        _emit 0x53
        // push ebx
        _emit 0x50
        // push eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], eax
        call FUN_00bf2960
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov ecx, dword ptr [esp + 0x1c]
        _emit 0x55
        // push ebp
        _emit 0x53
        // push ebx
        _emit 0x51
        // push ecx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x50
        // mov dword ptr [esp + 0x50], eax
        call FUN_00befb80
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x50
        // mov edx, dword ptr [esp + 0x50]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x58
        // mov eax, dword ptr [esp + 0x58]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x50
        // mov ecx, dword ptr [esp + 0x50]
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        _emit 0x57
        // push edi
        _emit 0x51
        // push ecx
        call FUN_00bf28f0
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0xC1
        _emit 0xE7
        _emit 0x05
        // shl edi, 5
        _emit 0x03
        _emit 0x7C
        _emit 0x24
        _emit 0x60
        // add edi, dword ptr [esp + 0x60]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x60
        // mov dword ptr [esp + 0x60], eax
        _emit 0x57
        // push edi
        _emit 0x50
        // push eax
        _emit 0x53
        // push ebx
        call FUN_00bf2960
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x6C
        // mov edx, dword ptr [esp + 0x6c]
        _emit 0x57
        // push edi
        _emit 0x52
        // push edx
        _emit 0x53
        // push ebx
        _emit 0x89
        _emit 0x84
        _emit 0x24
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x80], eax
        call FUN_00befb80
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x83
        _emit 0xC4
        _emit 0x40
        // add esp, 0x40
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xbf53fb
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xbf53fb
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // mov eax, dword ptr [esp + 0x40]
        _emit 0x89
        _emit 0x46
        _emit 0x04
        // mov dword ptr [esi + 4], eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        // mov eax, dword ptr [esp + 0x3c]
        _emit 0xC1
        _emit 0xE0
        _emit 0x05
        // shl eax, 5
        _emit 0x03
        _emit 0xC5
        // add eax, ebp
        _emit 0x89
        _emit 0x2E
        // mov dword ptr [esi], ebp
        _emit 0x89
        _emit 0x46
        _emit 0x08
        // mov dword ptr [esi + 8], eax
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
        _emit 0x24
        // add esp, 0x24
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
    }
}

// @ 0x00bf5420  (426 bytes)
__declspec(naked) void FUN_00bf5420()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0x8B
        _emit 0x47
        _emit 0x04
        // mov eax, dword ptr [edi + 4]
        _emit 0x3B
        _emit 0x47
        _emit 0x08
        // cmp eax, dword ptr [edi + 8]
        _emit 0x0F
        _emit 0x84
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xbf54c4
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov ebx, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x18
        // mov esi, dword ptr [esp + 0x18]
        _emit 0x3B
        _emit 0xDE
        // cmp ebx, esi
        _emit 0x72
        _emit 0x07
        // jb 0xbf5447
        _emit 0x3B
        _emit 0xD8
        // cmp ebx, eax
        _emit 0x73
        _emit 0x03
        // jae 0xbf5447
        _emit 0x83
        _emit 0xC3
        _emit 0x20
        // add ebx, 0x20
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x37
        // je 0xbf5482
        _emit 0xC7
        _emit 0x00
        _emit 0x54
        _emit 0x5D
        _emit 0x46
        _emit 0x01
        // mov dword ptr [eax], 0x1465d54
        _emit 0xC7
        _emit 0x40
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [eax + 4], 0
        _emit 0x8B
        _emit 0x48
        _emit 0xE8
        // mov ecx, dword ptr [eax - 0x18]
        _emit 0x89
        _emit 0x48
        _emit 0x08
        // mov dword ptr [eax + 8], ecx
        _emit 0x8B
        _emit 0x50
        _emit 0xEC
        // mov edx, dword ptr [eax - 0x14]
        _emit 0x89
        _emit 0x50
        _emit 0x0C
        // mov dword ptr [eax + 0xc], edx
        _emit 0x8B
        _emit 0x48
        _emit 0xF0
        // mov ecx, dword ptr [eax - 0x10]
        _emit 0x89
        _emit 0x48
        _emit 0x10
        // mov dword ptr [eax + 0x10], ecx
        _emit 0x8B
        _emit 0x50
        _emit 0xF4
        // mov edx, dword ptr [eax - 0xc]
        _emit 0x89
        _emit 0x50
        _emit 0x14
        // mov dword ptr [eax + 0x14], edx
        _emit 0x8A
        _emit 0x48
        _emit 0xF8
        // mov cl, byte ptr [eax - 8]
        _emit 0x88
        _emit 0x48
        _emit 0x18
        // mov byte ptr [eax + 0x18], cl
        _emit 0x8B
        _emit 0x50
        _emit 0xFC
        // mov edx, dword ptr [eax - 4]
        _emit 0x89
        _emit 0x50
        _emit 0x1C
        // mov dword ptr [eax + 0x1c], edx
        _emit 0xC7
        _emit 0x00
        _emit 0x50
        _emit 0x44
        _emit 0x46
        _emit 0x01
        // mov dword ptr [eax], 0x1464450
        _emit 0x8B
        _emit 0x47
        _emit 0x04
        // mov eax, dword ptr [edi + 4]
        _emit 0x50
        // push eax
        _emit 0x83
        _emit 0xC0
        _emit 0xE0
        // add eax, -0x20
        _emit 0x50
        // push eax
        _emit 0x56
        // push esi
        call FUN_00bf2a10
        _emit 0x8B
        _emit 0x43
        _emit 0x08
        // mov eax, dword ptr [ebx + 8]
        _emit 0x89
        _emit 0x46
        _emit 0x08
        // mov dword ptr [esi + 8], eax
        _emit 0x8B
        _emit 0x4B
        _emit 0x0C
        // mov ecx, dword ptr [ebx + 0xc]
        _emit 0x89
        _emit 0x4E
        _emit 0x0C
        // mov dword ptr [esi + 0xc], ecx
        _emit 0x8B
        _emit 0x53
        _emit 0x10
        // mov edx, dword ptr [ebx + 0x10]
        _emit 0x89
        _emit 0x56
        _emit 0x10
        // mov dword ptr [esi + 0x10], edx
        _emit 0x8B
        _emit 0x43
        _emit 0x14
        // mov eax, dword ptr [ebx + 0x14]
        _emit 0x89
        _emit 0x46
        _emit 0x14
        // mov dword ptr [esi + 0x14], eax
        _emit 0x8A
        _emit 0x4B
        _emit 0x18
        // mov cl, byte ptr [ebx + 0x18]
        _emit 0x88
        _emit 0x4E
        _emit 0x18
        // mov byte ptr [esi + 0x18], cl
        _emit 0x8B
        _emit 0x53
        _emit 0x1C
        // mov edx, dword ptr [ebx + 0x1c]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x89
        _emit 0x56
        _emit 0x1C
        // mov dword ptr [esi + 0x1c], edx
        _emit 0x83
        _emit 0x47
        _emit 0x04
        _emit 0x20
        // add dword ptr [edi + 4], 0x20
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x2B
        _emit 0x07
        // sub eax, dword ptr [edi]
        _emit 0xC1
        _emit 0xF8
        _emit 0x05
        // sar eax, 5
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x76
        _emit 0x2F
        // jbe 0xbf54fc
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x33
        // je 0xbf550a
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
        _emit 0xC1
        _emit 0xE0
        _emit 0x05
        // shl eax, 5
        _emit 0x68
        _emit 0xB4
        _emit 0x09
        _emit 0x3F
        _emit 0x01
        // push 0x13f09b4
        _emit 0x50
        // push eax
        call FUN_00f473a0
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], eax
        _emit 0xEB
        _emit 0x16
        // jmp 0xbf5512
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x10], 1
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0xEB
        _emit 0xCD
        // jmp 0xbf54d7
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0xc], 0
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov eax, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov ebx, dword ptr [esp + 0x18]
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x2F
        // mov ebp, dword ptr [edi]
        _emit 0x50
        // push eax
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        call FUN_00bf2960
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov ecx, dword ptr [esp + 0x1c]
        _emit 0x51
        // push ecx
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        call FUN_00befb80
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x3B
        // je 0xbf5575
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov eax, dword ptr [esp + 0x20]
        _emit 0xC7
        _emit 0x06
        _emit 0x54
        _emit 0x5D
        _emit 0x46
        _emit 0x01
        // mov dword ptr [esi], 0x1465d54
        _emit 0xC7
        _emit 0x46
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 4], 0
        _emit 0x8B
        _emit 0x50
        _emit 0x08
        // mov edx, dword ptr [eax + 8]
        _emit 0x89
        _emit 0x56
        _emit 0x08
        // mov dword ptr [esi + 8], edx
        _emit 0x8B
        _emit 0x48
        _emit 0x0C
        // mov ecx, dword ptr [eax + 0xc]
        _emit 0x89
        _emit 0x4E
        _emit 0x0C
        // mov dword ptr [esi + 0xc], ecx
        _emit 0x8B
        _emit 0x50
        _emit 0x10
        // mov edx, dword ptr [eax + 0x10]
        _emit 0x89
        _emit 0x56
        _emit 0x10
        // mov dword ptr [esi + 0x10], edx
        _emit 0x8B
        _emit 0x48
        _emit 0x14
        // mov ecx, dword ptr [eax + 0x14]
        _emit 0x89
        _emit 0x4E
        _emit 0x14
        // mov dword ptr [esi + 0x14], ecx
        _emit 0x8A
        _emit 0x50
        _emit 0x18
        // mov dl, byte ptr [eax + 0x18]
        _emit 0x88
        _emit 0x56
        _emit 0x18
        // mov byte ptr [esi + 0x18], dl
        _emit 0x8B
        _emit 0x40
        _emit 0x1C
        // mov eax, dword ptr [eax + 0x1c]
        _emit 0x89
        _emit 0x46
        _emit 0x1C
        // mov dword ptr [esi + 0x1c], eax
        _emit 0xC7
        _emit 0x06
        _emit 0x50
        _emit 0x44
        _emit 0x46
        _emit 0x01
        // mov dword ptr [esi], 0x1464450
        _emit 0x8B
        _emit 0x6F
        _emit 0x04
        // mov ebp, dword ptr [edi + 4]
        _emit 0x83
        _emit 0xC6
        _emit 0x20
        // add esi, 0x20
        _emit 0x56
        // push esi
        _emit 0x55
        // push ebp
        _emit 0x53
        // push ebx
        call FUN_00bf2960
        _emit 0x56
        // push esi
        _emit 0x55
        // push ebp
        _emit 0x53
        // push ebx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // mov dword ptr [esp + 0x34], eax
        call FUN_00befb80
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x5D
        // pop ebp
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xbf55a8
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xbf55a8
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // mov ecx, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x18
        // mov edx, dword ptr [esp + 0x18]
        _emit 0xC1
        _emit 0xE0
        _emit 0x05
        // shl eax, 5
        _emit 0x03
        _emit 0xC1
        // add eax, ecx
        _emit 0x89
        _emit 0x0F
        // mov dword ptr [edi], ecx
        _emit 0x89
        _emit 0x57
        _emit 0x04
        // mov dword ptr [edi + 4], edx
        _emit 0x89
        _emit 0x47
        _emit 0x08
        // mov dword ptr [edi + 8], eax
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00bf55d0  (93 bytes)
__declspec(naked) void FUN_00bf55d0()
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
        _emit 0xB9
        _emit 0xF0
        _emit 0xCA
        _emit 0x68
        _emit 0x01
        // mov ecx, 0x168caf0
        call FUN_00bf4a90
        _emit 0xBE
        _emit 0x0C
        _emit 0xCB
        _emit 0x68
        _emit 0x01
        // mov esi, 0x168cb0c
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x8B
        _emit 0x7E
        _emit 0x0C
        // mov edi, dword ptr [esi + 0xc]
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x74
        _emit 0x20
        // je 0xbf560c
        _emit 0x8D
        _emit 0x64
        _emit 0x24
        _emit 0x00
        // lea esp, [esp]
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_009a9600
        _emit 0x8B
        _emit 0x6F
        _emit 0x04
        // mov ebp, dword ptr [edi + 4]
        _emit 0x57
        // push edi
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0xFD
        // mov edi, ebp
        _emit 0x3B
        _emit 0xEB
        // cmp ebp, ebx
        _emit 0x75
        _emit 0xE4
        // jne 0xbf55f0
        _emit 0x8D
        _emit 0x46
        _emit 0x04
        // lea eax, [esi + 4]
        _emit 0x89
        _emit 0x46
        _emit 0x08
        // mov dword ptr [esi + 8], eax
        _emit 0x89
        _emit 0x5E
        _emit 0x0C
        // mov dword ptr [esi + 0xc], ebx
        _emit 0x88
        _emit 0x5E
        _emit 0x10
        // mov byte ptr [esi + 0x10], bl
        _emit 0x89
        _emit 0x5E
        _emit 0x14
        // mov dword ptr [esi + 0x14], ebx
        _emit 0x83
        _emit 0xC6
        _emit 0x1C
        // add esi, 0x1c
        _emit 0x81
        _emit 0xFE
        _emit 0x44
        _emit 0xCB
        _emit 0x68
        _emit 0x01
        // cmp esi, 0x168cb44
        _emit 0x89
        _emit 0x00
        // mov dword ptr [eax], eax
        _emit 0x7C
        _emit 0xBD
        // jl 0xbf55e5
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0xC3
        // ret 
    }
}

// @ 0x00bf5630  (239 bytes)
__declspec(naked) void FUN_00bf5630()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x0C
        // mov esi, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0xDE
        // mov ebx, esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ebx
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x08
        // je 0xbf564b
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x87
        _emit 0xB4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edi + 0xb4]
        _emit 0x3B
        _emit 0x87
        _emit 0xB8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp eax, dword ptr [edi + 0xb8]
        _emit 0x8D
        _emit 0x8F
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [edi + 0xb0]
        _emit 0x73
        _emit 0x1A
        // jae 0xbf5679
        _emit 0x8D
        _emit 0x50
        _emit 0x04
        // lea edx, [eax + 4]
        _emit 0x89
        _emit 0x51
        _emit 0x04
        // mov dword ptr [ecx + 4], edx
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x1F
        // je 0xbf5688
        _emit 0x89
        _emit 0x30
        // mov dword ptr [eax], esi
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x26
        // je 0xbf5695
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0xEB
        _emit 0x0F
        // jmp 0xbf5688
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // lea edx, [esp + 0x10]
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        call FUN_00aea5d0
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // mov ebx, dword ptr [esp + 0x10]
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x74
        _emit 0x09
        // je 0xbf5695
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x8B
        _emit 0x50
        _emit 0x4C
        // mov edx, dword ptr [eax + 0x4c]
        _emit 0x8B
        _emit 0x1E
        // mov ebx, dword ptr [esi]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x43
        _emit 0x48
        // mov eax, dword ptr [ebx + 0x48]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x42
        _emit 0x0C
        // mov eax, dword ptr [edx + 0xc]
        _emit 0x68
        _emit 0x77
        _emit 0x65
        _emit 0x18
        _emit 0x01
        // push 0x1186577
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x5D
        // je 0xbf5719
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x82
        _emit 0xBC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edx + 0xbc]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x87
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edi + 0xd8]
        _emit 0x3B
        _emit 0x87
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp eax, dword ptr [edi + 0xdc]
        _emit 0x8D
        _emit 0x8F
        _emit 0xD4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [edi + 0xd4]
        _emit 0x73
        _emit 0x1A
        // jae 0xbf56fa
        _emit 0x8D
        _emit 0x50
        _emit 0x04
        // lea edx, [eax + 4]
        _emit 0x89
        _emit 0x51
        _emit 0x04
        // mov dword ptr [ecx + 4], edx
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x1F
        // je 0xbf5709
        _emit 0x89
        _emit 0x30
        // mov dword ptr [eax], esi
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x90
        _emit 0xBC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [eax + 0xbc]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0xEB
        _emit 0x0F
        // jmp 0xbf5709
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // lea edx, [esp + 0x10]
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        call FUN_00bab900
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x10
        // mov esi, dword ptr [esp + 0x10]
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x0C
        // je 0xbf5719
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x90
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [eax + 0xc0]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00bf5720  (143 bytes)
__declspec(naked) void FUN_00bf5720()
{
    __asm {
        _emit 0x51
        // push ecx
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ecx
        call FUN_00b3d300
        _emit 0x68
        _emit 0xE8
        _emit 0x43
        _emit 0x8C
        _emit 0x01
        // push 0x18c43e8
        _emit 0x68
        _emit 0x00
        _emit 0xE5
        _emit 0xB1
        _emit 0x00
        // push 0xb1e500
        _emit 0x68
        _emit 0xF0
        _emit 0xDF
        _emit 0xAC
        _emit 0x00
        // push 0xacdff0
        _emit 0x68
        _emit 0x20
        _emit 0xD4
        _emit 0xD3
        _emit 0x00
        // push 0xd3d420
        _emit 0x68
        _emit 0x10
        _emit 0x7D
        _emit 0xCD
        _emit 0x00
        // push 0xcd7d10
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b21340
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x8B
        _emit 0x77
        _emit 0x08
        // mov esi, dword ptr [edi + 8]
        _emit 0x2B
        _emit 0x77
        _emit 0x04
        // sub esi, dword ptr [edi + 4]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov eax, dword ptr [esp + 0x18]
        _emit 0x83
        _emit 0xC7
        _emit 0x04
        // add edi, 4
        _emit 0x50
        // push eax
        _emit 0xC1
        _emit 0xFE
        _emit 0x02
        // sar esi, 2
        call FUN_00b3d350
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b88590
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], eax
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x7E
        _emit 0x24
        // jle 0xbf579b
        _emit 0x8B
        _emit 0x0F
        // mov ecx, dword ptr [edi]
        _emit 0x8B
        _emit 0x2C
        _emit 0x99
        // mov ebp, dword ptr [ecx + ebx*4]
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        call FUN_00bd9bf0
        _emit 0x3B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // cmp eax, dword ptr [esp + 0x10]
        _emit 0x74
        _emit 0x0D
        // je 0xbf5796
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        call FUN_00bd8210
        _emit 0x3B
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // cmp eax, dword ptr [esp + 0x18]
        _emit 0x74
        _emit 0x0F
        // je 0xbf57a5
        _emit 0x43
        // inc ebx
        _emit 0x3B
        _emit 0xDE
        // cmp ebx, esi
        _emit 0x7C
        _emit 0xDC
        // jl 0xbf5777
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
        _emit 0x59
        // pop ecx
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
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
        _emit 0x59
        // pop ecx
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00bf57b0  (531 bytes)
__declspec(naked) void FUN_00bf57b0()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x74
        // sub esp, 0x74
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xE9
        // mov ebp, ecx
        call FUN_00b3d300
        _emit 0x68
        _emit 0xE8
        _emit 0x6D
        _emit 0x8C
        _emit 0x01
        // push 0x18c6de8
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b20c60
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x0F
        _emit 0x84
        _emit 0xE8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xbf59bc
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x0C
        // mov eax, dword ptr [edx + 0xc]
        _emit 0x68
        _emit 0xE0
        _emit 0xE8
        _emit 0x37
        _emit 0x01
        // push 0x137e8e0
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x3B
        _emit 0xF3
        // cmp esi, ebx
        _emit 0x74
        _emit 0x08
        // je 0xbf57f0
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        call FUN_00bf5630
        _emit 0x8B
        _emit 0x8C
        _emit 0x24
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esp + 0x90]
        _emit 0x8B
        _emit 0x94
        _emit 0x24
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esp + 0x94]
        _emit 0x83
        _emit 0xEC
        _emit 0x0C
        // sub esp, 0xc
        _emit 0x8B
        _emit 0xC4
        // mov eax, esp
        _emit 0x89
        _emit 0x08
        // mov dword ptr [eax], ecx
        _emit 0x8B
        _emit 0x8C
        _emit 0x24
        _emit 0xA4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esp + 0xa4]
        _emit 0x89
        _emit 0x50
        _emit 0x04
        // mov dword ptr [eax + 4], edx
        _emit 0x8B
        _emit 0x94
        _emit 0x24
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esp + 0x94]
        _emit 0x89
        _emit 0x48
        _emit 0x08
        // mov dword ptr [eax + 8], ecx
        _emit 0x8B
        _emit 0x84
        _emit 0x24
        _emit 0x98
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esp + 0x98]
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00ca6630
        _emit 0x8B
        _emit 0x56
        _emit 0x34
        // mov edx, dword ptr [esi + 0x34]
        _emit 0x8B
        _emit 0x84
        _emit 0x24
        _emit 0x9C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esp + 0x9c]
        _emit 0x8B
        _emit 0x52
        _emit 0x38
        // mov edx, dword ptr [edx + 0x38]
        _emit 0x8D
        _emit 0x7E
        _emit 0x34
        // lea edi, [esi + 0x34]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0x14
        _emit 0xC5
        _emit 0x68
        _emit 0x01
        // movss xmm0, dword ptr [0x168c514]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x0D
        _emit 0x1C
        _emit 0x0F
        _emit 0x47
        _emit 0x01
        // movss xmm1, dword ptr [0x1470f1c]
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x8B
        _emit 0x90
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [eax + 0xdc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // movss dword ptr [esp + 0x24], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0x18
        _emit 0xC5
        _emit 0x68
        _emit 0x01
        // movss xmm0, dword ptr [0x168c518]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // movss dword ptr [esp + 0x28], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0x1C
        _emit 0xC5
        _emit 0x68
        _emit 0x01
        // movss xmm0, dword ptr [0x168c51c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // movss dword ptr [esp + 0x2c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // movss xmm0, dword ptr [0x1485720]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x70
        // movss dword ptr [esp + 0x70], xmm1
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
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // lea ecx, [esp + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // movss dword ptr [esp + 0x30], xmm0
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
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
        _emit 0x3C
        _emit 0x93
        _emit 0x46
        _emit 0x01
        // movss xmm1, dword ptr [0x146933c]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
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
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x38
        // mov dword ptr [esp + 0x38], ebx
        _emit 0x88
        _emit 0x5C
        _emit 0x24
        _emit 0x60
        // mov byte ptr [esp + 0x60], bl
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x64
        // movss dword ptr [esp + 0x64], xmm0
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
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x70
        // mov dword ptr [esp + 0x70], ebx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x7C
        // movss dword ptr [esp + 0x7c], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x84
        _emit 0x24
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esp + 0x80], xmm0
        _emit 0x89
        _emit 0x9C
        _emit 0x24
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x84], ebx
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
        _emit 0x74
        _emit 0x0E
        // je 0xbf590c
        _emit 0x39
        _emit 0x58
        _emit 0xFC
        // cmp dword ptr [eax - 4], ebx
        _emit 0x74
        _emit 0x09
        // je 0xbf590c
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0xD9
        _emit 0xEE
        // fldz 
        _emit 0x8B
        _emit 0x90
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [eax + 0xc4]
        _emit 0x53
        // push ebx
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8D
        _emit 0xBE
        _emit 0xD0
        _emit 0x05
        _emit 0x00
        _emit 0x00
        // lea edi, [esi + 0x5d0]
        call FUN_00b3d260
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x38
        // mov eax, dword ptr [edx + 0x38]
        _emit 0x57
        // push edi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x42
        _emit 0x0C
        // mov eax, dword ptr [edx + 0xc]
        _emit 0x68
        _emit 0x77
        _emit 0x65
        _emit 0x18
        _emit 0x01
        // push 0x1186577
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x38
        _emit 0x9C
        _emit 0x24
        _emit 0xA0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [esp + 0xa0], bl
        _emit 0x74
        _emit 0x5C
        // je 0xbf59a7
        call FUN_01021260
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x74
        _emit 0x51
        // je 0xbf59a7
        _emit 0x8B
        _emit 0x55
        _emit 0x00
        // mov edx, dword ptr [ebp]
        _emit 0x8B
        _emit 0x42
        _emit 0x4C
        // mov eax, dword ptr [edx + 0x4c]
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_00c71040
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x74
        _emit 0x39
        // je 0xbf59a7
        _emit 0x53
        // push ebx
        _emit 0x53
        // push ebx
        _emit 0x53
        // push ebx
        _emit 0x53
        // push ebx
        _emit 0x68
        _emit 0x34
        _emit 0x5B
        _emit 0x46
        _emit 0x01
        // push 0x1465b34
        _emit 0x6A
        _emit 0x14
        // push 0x14
        call FUN_00f473a0
        _emit 0x83
        _emit 0xC4
        _emit 0x18
        // add esp, 0x18
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x74
        _emit 0x0A
        // je 0xbf598f
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ff0db0
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_00ff2d20
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00c9eae0
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00a110b0
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x5F
        // pop edi
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x74
        // add esp, 0x74
        _emit 0xC2
        _emit 0x1C
        _emit 0x00
        // ret 0x1c
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0xE9
        _emit 0x2D
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jmp 0xbf57f0
    }
}

// @ 0x00bf59d0  (447 bytes)
__declspec(naked) void FUN_00bf59d0()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x44
        // sub esp, 0x44
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xE9
        // mov ebp, ecx
        _emit 0x57
        // push edi
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], ebp
        call FUN_00b3d350
        _emit 0x8B
        _emit 0x9D
        _emit 0xA0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, dword ptr [ebp + 0xa0]
        _emit 0x2B
        _emit 0x9D
        _emit 0x9C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // sub ebx, dword ptr [ebp + 0x9c]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], eax
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x13
        // lea eax, [esp + 0x13]
        _emit 0x50
        // push eax
        _emit 0xC1
        _emit 0xFB
        _emit 0x02
        // sar ebx, 2
        _emit 0x53
        // push ebx
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // lea ecx, [esp + 0x48]
        call FUN_006a46a0
        _emit 0x33
        _emit 0xFF
        // xor edi, edi
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x7E
        _emit 0x38
        // jle 0xbf5a42
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x40
        // mov esi, dword ptr [esp + 0x40]
        _emit 0x8B
        _emit 0xFF
        // mov edi, edi
        _emit 0x8B
        _emit 0x8D
        _emit 0x9C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [ebp + 0x9c]
        _emit 0x8B
        _emit 0x0C
        _emit 0xB9
        // mov ecx, dword ptr [ecx + edi*4]
        _emit 0x8B
        _emit 0x91
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [ecx + 0x120]
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x81
        _emit 0xC1
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // add ecx, 0x120
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x89
        _emit 0x0E
        // mov dword ptr [esi], ecx
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x89
        _emit 0x56
        _emit 0x04
        // mov dword ptr [esi + 4], edx
        _emit 0x8B
        _emit 0x40
        _emit 0x08
        // mov eax, dword ptr [eax + 8]
        _emit 0x89
        _emit 0x46
        _emit 0x08
        // mov dword ptr [esi + 8], eax
        _emit 0x47
        // inc edi
        _emit 0x83
        _emit 0xC6
        _emit 0x0C
        // add esi, 0xc
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x7C
        _emit 0xCE
        // jl 0xbf5a10
        call FUN_00b3d300
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00b25ca0
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], ecx
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x30
        // mov dword ptr [esp + 0x30], edx
        _emit 0x3B
        _emit 0xCA
        // cmp ecx, edx
        _emit 0x0F
        _emit 0x84
        _emit 0x0D
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0xbf5b70
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x3B
        _emit 0xC5
        // cmp eax, ebp
        _emit 0x0F
        _emit 0x84
        _emit 0xF4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xbf5b61
        _emit 0x8B
        _emit 0xB8
        _emit 0xA0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edi, dword ptr [eax + 0xa0]
        _emit 0x8B
        _emit 0xA8
        _emit 0x9C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebp, dword ptr [eax + 0x9c]
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], edi
        _emit 0x3B
        _emit 0xEF
        // cmp ebp, edi
        _emit 0x0F
        _emit 0x84
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xbf5b5d
        _emit 0xEB
        _emit 0x09
        // jmp 0xbf5a90
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0x8B
        _emit 0xFF
        // mov edi, edi
        _emit 0x8B
        _emit 0x75
        _emit 0x00
        // mov esi, dword ptr [ebp]
        _emit 0x8B
        _emit 0x96
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x120]
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x8D
        _emit 0x8E
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea ecx, [esi + 0x120]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x00
        // movss xmm0, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // movss dword ptr [esp + 0x34], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x04
        // movss xmm0, dword ptr [eax + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // movss dword ptr [esp + 0x38], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x08
        // movss xmm0, dword ptr [eax + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        // movss dword ptr [esp + 0x3c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0x3C
        _emit 0x93
        _emit 0x46
        _emit 0x01
        // movss xmm0, dword ptr [0x146933c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm0
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x7E
        _emit 0x41
        // jle 0xbf5b17
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x40
        // mov edi, dword ptr [esp + 0x40]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ebx
        _emit 0x8B
        _emit 0xFF
        // mov edi, edi
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x38
        // lea ecx, [esp + 0x38]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov ecx, dword ptr [esp + 0x2c]
        call FUN_00b81470
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x28
        // fst dword ptr [esp + 0x28]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xDF
        _emit 0xF1
        // fcompi st(1)
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x76
        _emit 0x0C
        // jbe 0xbf5b09
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // movss xmm0, dword ptr [esp + 0x28]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm0
        _emit 0x83
        _emit 0xC7
        _emit 0x0C
        // add edi, 0xc
        _emit 0x83
        _emit 0x6C
        _emit 0x24
        _emit 0x1C
        _emit 0x01
        // sub dword ptr [esp + 0x1c], 1
        _emit 0x75
        _emit 0xCD
        // jne 0xbf5ae0
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x2C
        // mov edi, dword ptr [esp + 0x2c]
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // lea ecx, [esp + 0x28]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov ecx, dword ptr [esp + 0x1c]
        _emit 0x81
        _emit 0xC1
        _emit 0x10
        _emit 0x04
        _emit 0x00
        _emit 0x00
        // add ecx, 0x410
        call FUN_00bf5050
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // movss xmm0, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x00
        // movss dword ptr [eax], xmm0
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x83
        _emit 0xC5
        _emit 0x04
        // add ebp, 4
        _emit 0x3B
        _emit 0xEF
        // cmp ebp, edi
        _emit 0x0F
        _emit 0x85
        _emit 0x3B
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jne 0xbf5a90
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x30
        // mov edx, dword ptr [esp + 0x30]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x18
        // mov ebp, dword ptr [esp + 0x18]
        _emit 0x83
        _emit 0xC1
        _emit 0x04
        // add ecx, 4
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], ecx
        _emit 0x3B
        _emit 0xCA
        // cmp ecx, edx
        _emit 0x0F
        _emit 0x85
        _emit 0xF3
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jne 0xbf5a63
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // mov eax, dword ptr [esp + 0x40]
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xbf5b8b
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xbf5b8b
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x83
        _emit 0xC4
        _emit 0x44
        // add esp, 0x44
        _emit 0xC3
        // ret 
    }
}

// @ 0x00bf5b90  (72 bytes)
__declspec(naked) void FUN_00bf5b90()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x08
        // mov esi, dword ptr [esp + 8]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], esi
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x08
        // je 0xbf5ba8
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // lea eax, [esp + 0xc]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x8F
        _emit 0x10
        _emit 0x04
        _emit 0x00
        _emit 0x00
        // lea ecx, [edi + 0x410]
        call FUN_00bf5050
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x00
        // movss xmm0, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // movss dword ptr [esp + 0xc], xmm0
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x09
        // je 0xbf5bcf
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00bf5be0  (197 bytes)
__declspec(naked) void FUN_00bf5be0()
{
    __asm {
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x3D
        _emit 0x9E
        _emit 0x21
        _emit 0xA0
        _emit 0x01
        // cmp eax, 0x1a0219e
        _emit 0x0F
        _emit 0x84
        _emit 0x93
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xbf5c85
        _emit 0x3D
        _emit 0x9C
        _emit 0x08
        _emit 0x0C
        _emit 0x02
        // cmp eax, 0x20c089c
        _emit 0x74
        _emit 0x6E
        // je 0xbf5c67
        _emit 0x3D
        _emit 0x8F
        _emit 0x4F
        _emit 0x52
        _emit 0x06
        // cmp eax, 0x6524f8f
        _emit 0x0F
        _emit 0x85
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0xbf5c9f
        _emit 0x8B
        _emit 0x8E
        _emit 0x6C
        _emit 0x04
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x46c]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x2E
        // je 0xbf5c3c
        call FUN_00bd9bf0
        _emit 0x8D
        _emit 0x4E
        _emit 0xC8
        // lea ecx, [esi - 0x38]
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x75
        _emit 0x22
        // jne 0xbf5c3c
        _emit 0x80
        _emit 0x7E
        _emit 0x51
        _emit 0x00
        // cmp byte ptr [esi + 0x51], 0
        _emit 0x74
        _emit 0x1C
        // je 0xbf5c3c
        _emit 0x8B
        _emit 0x86
        _emit 0x70
        _emit 0x04
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x470]
        _emit 0x83
        _emit 0xF8
        _emit 0xFF
        // cmp eax, -1
        _emit 0x74
        _emit 0x11
        // je 0xbf5c3c
        _emit 0x8B
        _emit 0x8E
        _emit 0x6C
        _emit 0x04
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x46c]
        _emit 0x68
        _emit 0x14
        _emit 0xC5
        _emit 0x68
        _emit 0x01
        // push 0x168c514
        _emit 0x50
        // push eax
        call FUN_00be5be0
        _emit 0x8B
        _emit 0x8E
        _emit 0x6C
        _emit 0x04
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x46c]
        _emit 0xC7
        _emit 0x86
        _emit 0x6C
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x46c], 0
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x07
        // je 0xbf5c57
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
        _emit 0xC7
        _emit 0x86
        _emit 0x70
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // mov dword ptr [esi + 0x470], 0xffffffff
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x5E
        // pop esi
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        call FUN_00b3d4a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ae9390
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x75
        _emit 0x28
        // jne 0xbf5c9f
        _emit 0x8D
        _emit 0x4E
        _emit 0xC8
        // lea ecx, [esi - 0x38]
        call FUN_00bf0f90
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x5E
        // pop esi
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // mov ecx, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x41
        _emit 0x10
        // mov eax, dword ptr [ecx + 0x10]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xbf5c9f
        _emit 0x83
        _emit 0x79
        _emit 0x08
        _emit 0x04
        // cmp dword ptr [ecx + 8], 4
        _emit 0x75
        _emit 0x09
        // jne 0xbf5c9f
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4E
        _emit 0xC8
        // lea ecx, [esi - 0x38]
        call FUN_00bf49e0
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x5E
        // pop esi
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}
