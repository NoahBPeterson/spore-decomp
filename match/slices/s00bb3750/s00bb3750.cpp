// Slice s00bb3750: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_0041e990();
extern "C" void FUN_005c65e0();
extern "C" void FUN_006782c0();
extern "C" void FUN_009360d0();
extern "C" void FUN_00b1fdb0();
extern "C" void FUN_00ba7320();
extern "C" void FUN_00bac7d0();
extern "C" void FUN_00badea0();
extern "C" void FUN_00bb1080();
extern "C" void FUN_00bb1340();
extern "C" void FUN_00bb9ae0();
extern "C" void FUN_00c33da0();
extern "C" void FUN_00c341a0();
extern "C" void FUN_00c8b6d0();
extern "C" void FUN_00e25bd0();
extern "C" void FUN_00e5c780();
extern "C" void FUN_00f47380();
extern "C" void FUN_011e07ef();

// @ 0x00bb3750  (176 bytes)
__declspec(naked) void FUN_00bb3750()
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
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov edi, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0xD9
        // mov ebx, ecx
        _emit 0xC7
        _emit 0x07
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi], 0
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x0F
        _emit 0x84
        _emit 0x8F
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xbb37fa
        _emit 0x8B
        _emit 0x46
        _emit 0x70
        // mov eax, dword ptr [esi + 0x70]
        _emit 0x55
        // push ebp
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
        _emit 0x8D
        _emit 0x6B
        _emit 0x20
        // lea ebp, [ebx + 0x20]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], eax
        call FUN_00e5c780
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x8D
        _emit 0x4B
        _emit 0x24
        // lea ecx, [ebx + 0x24]
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x74
        _emit 0x12
        // je 0xbb37a4
        _emit 0x8B
        _emit 0x48
        _emit 0x14
        // mov ecx, dword ptr [eax + 0x14]
        _emit 0x89
        _emit 0x0F
        // mov dword ptr [edi], ecx
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x5D
        // pop ebp
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        call FUN_00bac7d0
        _emit 0x89
        _emit 0x07
        // mov dword ptr [edi], eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x48
        // je 0xbb37f9
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x0F
        // mov ecx, dword ptr [edi]
        _emit 0x56
        // push esi
        call FUN_00c8b6d0
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        call FUN_00badea0
        _emit 0x8B
        _emit 0x17
        // mov edx, dword ptr [edi]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x89
        _emit 0x10
        // mov dword ptr [eax], edx
        call FUN_00bb9ae0
        _emit 0x83
        _emit 0xF8
        _emit 0x05
        // cmp eax, 5
        _emit 0x75
        _emit 0x1C
        // jne 0xbb37f9
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00b1fdb0
        _emit 0x83
        _emit 0xF8
        _emit 0xFF
        // cmp eax, -1
        _emit 0x74
        _emit 0x10
        // je 0xbb37f9
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        call FUN_00bb1340
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00c341a0
        _emit 0x5D
        // pop ebp
        _emit 0x5F
        // pop edi
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

// @ 0x00bb3800  (566 bytes)
__declspec(naked) void FUN_00bb3800()
{
    __asm {
        _emit 0x51
        // push ecx
        _emit 0x53
        // push ebx
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0xF6
        _emit 0x05
        _emit 0x98
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        _emit 0x01
        // test byte ptr [0x1689e98], 1
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0x75
        _emit 0x43
        // jne 0xbb3853
        _emit 0x83
        _emit 0x0D
        _emit 0x98
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        _emit 0x01
        // or dword ptr [0x1689e98], 1
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // lea ecx, [esp + 8]
        _emit 0x51
        // push ecx
        _emit 0xB8
        _emit 0x80
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov eax, 0x1689e80
        _emit 0x6A
        _emit 0x06
        // push 6
        _emit 0x50
        // push eax
        _emit 0xB9
        _emit 0x6C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov ecx, 0x1689e6c
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ebx
        _emit 0xA3
        _emit 0x70
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov dword ptr [0x1689e70], eax
        _emit 0xA3
        _emit 0x6C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov dword ptr [0x1689e6c], eax
        _emit 0xC7
        _emit 0x05
        _emit 0x74
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        _emit 0x98
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov dword ptr [0x1689e74], 0x1689e98
        call FUN_00c33da0
        _emit 0x68
        _emit 0x60
        _emit 0x30
        _emit 0x3C
        _emit 0x01
        // push 0x13c3060
        call FUN_011e07ef
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0xB8
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 2
        _emit 0x84
        _emit 0x05
        _emit 0x98
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // test byte ptr [0x1689e98], al
        _emit 0x75
        _emit 0x42
        // jne 0xbb38a2
        _emit 0x09
        _emit 0x05
        _emit 0x98
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // or dword ptr [0x1689e98], eax
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // lea edx, [esp + 8]
        _emit 0x52
        // push edx
        _emit 0xB8
        _emit 0x54
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov eax, 0x1689e54
        _emit 0x6A
        _emit 0x06
        // push 6
        _emit 0x50
        // push eax
        _emit 0xB9
        _emit 0x40
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov ecx, 0x1689e40
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ebx
        _emit 0xA3
        _emit 0x44
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov dword ptr [0x1689e44], eax
        _emit 0xA3
        _emit 0x40
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov dword ptr [0x1689e40], eax
        _emit 0xC7
        _emit 0x05
        _emit 0x48
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        _emit 0x6C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov dword ptr [0x1689e48], 0x1689e6c
        call FUN_00c33da0
        _emit 0x68
        _emit 0x50
        _emit 0x30
        _emit 0x3C
        _emit 0x01
        // push 0x13c3050
        call FUN_011e07ef
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x38
        _emit 0x1D
        _emit 0x3C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // cmp byte ptr [0x1689e3c], bl
        _emit 0x0F
        _emit 0x85
        _emit 0x5F
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jne 0xbb3a0d
        _emit 0x8B
        _emit 0x8F
        _emit 0xA0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x1a0]
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x35
        _emit 0x6C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov esi, dword ptr [0x1689e6c]
        _emit 0x83
        _emit 0xC6
        _emit 0x04
        // add esi, 4
        _emit 0xBD
        _emit 0x09
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebp, 9
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x28
        // je 0xbb38f0
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x40
        _emit 0x24
        // mov eax, dword ptr [eax + 0x24]
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // lea edx, [esp + 0x10]
        _emit 0x52
        // push edx
        _emit 0x68
        _emit 0x9A
        _emit 0x29
        _emit 0xF8
        _emit 0x02
        // push 0x2f8299a
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x13
        // je 0xbb38f0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x66
        _emit 0x39
        _emit 0x69
        _emit 0x12
        // cmp word ptr [ecx + 0x12], bp
        _emit 0x75
        _emit 0x09
        // jne 0xbb38f0
        call FUN_0041e990
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x89
        _emit 0x0E
        // mov dword ptr [esi], ecx
        _emit 0x8B
        _emit 0x35
        _emit 0x6C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov esi, dword ptr [0x1689e6c]
        _emit 0x8B
        _emit 0x8F
        _emit 0xA0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x1a0]
        _emit 0x83
        _emit 0xC6
        _emit 0x08
        // add esi, 8
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x28
        // je 0xbb392b
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x52
        _emit 0x24
        // mov edx, dword ptr [edx + 0x24]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // lea eax, [esp + 0x10]
        _emit 0x50
        // push eax
        _emit 0x68
        _emit 0x3B
        _emit 0x35
        _emit 0xF8
        _emit 0x02
        // push 0x2f8353b
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x13
        // je 0xbb392b
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x66
        _emit 0x39
        _emit 0x69
        _emit 0x12
        // cmp word ptr [ecx + 0x12], bp
        _emit 0x75
        _emit 0x09
        // jne 0xbb392b
        call FUN_0041e990
        _emit 0x8B
        _emit 0x00
        // mov eax, dword ptr [eax]
        _emit 0x89
        _emit 0x06
        // mov dword ptr [esi], eax
        _emit 0x8B
        _emit 0x0D
        _emit 0x6C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov ecx, dword ptr [0x1689e6c]
        _emit 0x89
        _emit 0x59
        _emit 0x0C
        // mov dword ptr [ecx + 0xc], ebx
        _emit 0x8B
        _emit 0x35
        _emit 0x6C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov esi, dword ptr [0x1689e6c]
        _emit 0x8B
        _emit 0x8F
        _emit 0xA0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x1a0]
        _emit 0x83
        _emit 0xC6
        _emit 0x10
        // add esi, 0x10
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x28
        // je 0xbb396f
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x52
        _emit 0x24
        // mov edx, dword ptr [edx + 0x24]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // lea eax, [esp + 0x10]
        _emit 0x50
        // push eax
        _emit 0x68
        _emit 0xCE
        _emit 0x27
        _emit 0xF8
        _emit 0x02
        // push 0x2f827ce
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x13
        // je 0xbb396f
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x66
        _emit 0x39
        _emit 0x69
        _emit 0x12
        // cmp word ptr [ecx + 0x12], bp
        _emit 0x75
        _emit 0x09
        // jne 0xbb396f
        call FUN_0041e990
        _emit 0x8B
        _emit 0x00
        // mov eax, dword ptr [eax]
        _emit 0x89
        _emit 0x06
        // mov dword ptr [esi], eax
        _emit 0x8B
        _emit 0x35
        _emit 0x6C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov esi, dword ptr [0x1689e6c]
        _emit 0x8B
        _emit 0x8F
        _emit 0xA0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x1a0]
        _emit 0x83
        _emit 0xC6
        _emit 0x14
        // add esi, 0x14
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x28
        // je 0xbb39aa
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x52
        _emit 0x24
        // mov edx, dword ptr [edx + 0x24]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // lea eax, [esp + 0x10]
        _emit 0x50
        // push eax
        _emit 0x68
        _emit 0xD5
        _emit 0x27
        _emit 0xF8
        _emit 0x02
        // push 0x2f827d5
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x13
        // je 0xbb39aa
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x66
        _emit 0x39
        _emit 0x69
        _emit 0x12
        // cmp word ptr [ecx + 0x12], bp
        _emit 0x75
        _emit 0x09
        // jne 0xbb39aa
        call FUN_0041e990
        _emit 0x8B
        _emit 0x00
        // mov eax, dword ptr [eax]
        _emit 0x89
        _emit 0x06
        // mov dword ptr [esi], eax
        _emit 0x8B
        _emit 0x0D
        _emit 0x6C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov ecx, dword ptr [0x1689e6c]
        _emit 0x8B
        _emit 0x51
        _emit 0x04
        // mov edx, dword ptr [ecx + 4]
        _emit 0xA1
        _emit 0x40
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov eax, dword ptr [0x1689e40]
        _emit 0x89
        _emit 0x50
        _emit 0x04
        // mov dword ptr [eax + 4], edx
        _emit 0x8B
        _emit 0x0D
        _emit 0x6C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov ecx, dword ptr [0x1689e6c]
        _emit 0x8B
        _emit 0x51
        _emit 0x08
        // mov edx, dword ptr [ecx + 8]
        _emit 0xA1
        _emit 0x40
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov eax, dword ptr [0x1689e40]
        _emit 0x89
        _emit 0x50
        _emit 0x08
        // mov dword ptr [eax + 8], edx
        _emit 0x8B
        _emit 0x0D
        _emit 0x40
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov ecx, dword ptr [0x1689e40]
        _emit 0x89
        _emit 0x59
        _emit 0x0C
        // mov dword ptr [ecx + 0xc], ebx
        _emit 0x8B
        _emit 0x15
        _emit 0x6C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov edx, dword ptr [0x1689e6c]
        _emit 0x8B
        _emit 0x42
        _emit 0x10
        // mov eax, dword ptr [edx + 0x10]
        _emit 0x8B
        _emit 0x0D
        _emit 0x40
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov ecx, dword ptr [0x1689e40]
        _emit 0x89
        _emit 0x41
        _emit 0x10
        // mov dword ptr [ecx + 0x10], eax
        _emit 0x8B
        _emit 0x15
        _emit 0x40
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov edx, dword ptr [0x1689e40]
        _emit 0x89
        _emit 0x5A
        _emit 0x14
        // mov dword ptr [edx + 0x14], ebx
        _emit 0xA1
        _emit 0x6C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov eax, dword ptr [0x1689e6c]
        _emit 0x8B
        _emit 0x48
        _emit 0x14
        // mov ecx, dword ptr [eax + 0x14]
        _emit 0x01
        _emit 0x48
        _emit 0x04
        // add dword ptr [eax + 4], ecx
        _emit 0x8B
        _emit 0x15
        _emit 0x6C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov edx, dword ptr [0x1689e6c]
        _emit 0x5E
        // pop esi
        _emit 0x89
        _emit 0x5A
        _emit 0x14
        // mov dword ptr [edx + 0x14], ebx
        _emit 0xC6
        _emit 0x05
        _emit 0x3C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        _emit 0x01
        // mov byte ptr [0x1689e3c], 1
        _emit 0x5D
        // pop ebp
        _emit 0x38
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // cmp byte ptr [esp + 0x10], bl
        _emit 0x5F
        // pop edi
        _emit 0x5B
        // pop ebx
        _emit 0xB8
        _emit 0x6C
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov eax, 0x1689e6c
        _emit 0x75
        _emit 0x05
        // jne 0xbb3a1f
        _emit 0xB8
        _emit 0x40
        _emit 0x9E
        _emit 0x68
        _emit 0x01
        // mov eax, 0x1689e40
        _emit 0x50
        // push eax
        call FUN_00ba7320
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x83
        _emit 0xF8
        _emit 0x06
        // cmp eax, 6
        _emit 0x75
        _emit 0x05
        // jne 0xbb3a32
        _emit 0xB8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 1
        _emit 0x59
        // pop ecx
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00bb3a40  (558 bytes)
__declspec(naked) void FUN_00bb3a40()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x34
        // sub esp, 0x34
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // lea eax, [esp + 0x24]
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x57
        // push edi
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], eax
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // lea eax, [esp + 0x10]
        _emit 0x50
        // push eax
        _emit 0x6A
        _emit 0x07
        // push 7
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ecx
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x4C
        // lea edx, [esp + 0x4c]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // lea ecx, [esp + 0x20]
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x1c], 0
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], edx
        call FUN_00c33da0
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x48
        // mov ebx, dword ptr [esp + 0x48]
        _emit 0x8B
        _emit 0x13
        // mov edx, dword ptr [ebx]
        _emit 0xC1
        _emit 0xEA
        _emit 0x02
        // shr edx, 2
        _emit 0xBD
        _emit 0x09
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebp, 9
        _emit 0xF6
        _emit 0xC2
        _emit 0x01
        // test dl, 1
        _emit 0x74
        _emit 0x39
        // je 0xbb3ac4
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov edi, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x8E
        _emit 0xA0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x1a0]
        _emit 0x83
        _emit 0xC7
        _emit 0x08
        // add edi, 8
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x28
        // je 0xbb3ac4
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x40
        _emit 0x24
        // mov eax, dword ptr [eax + 0x24]
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x48
        // lea edx, [esp + 0x48]
        _emit 0x52
        // push edx
        _emit 0x68
        _emit 0x88
        _emit 0xB1
        _emit 0x06
        _emit 0x03
        // push 0x306b188
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x13
        // je 0xbb3ac4
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // mov ecx, dword ptr [esp + 0x48]
        _emit 0x66
        _emit 0x39
        _emit 0x69
        _emit 0x12
        // cmp word ptr [ecx + 0x12], bp
        _emit 0x75
        _emit 0x09
        // jne 0xbb3ac4
        call FUN_0041e990
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x89
        _emit 0x0F
        // mov dword ptr [edi], ecx
        _emit 0x8B
        _emit 0x13
        // mov edx, dword ptr [ebx]
        _emit 0xC1
        _emit 0xEA
        _emit 0x03
        // shr edx, 3
        _emit 0xF6
        _emit 0xC2
        _emit 0x01
        // test dl, 1
        _emit 0x74
        _emit 0x39
        // je 0xbb3b07
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov edi, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x8E
        _emit 0xA0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x1a0]
        _emit 0x83
        _emit 0xC7
        _emit 0x0C
        // add edi, 0xc
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x28
        // je 0xbb3b07
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x40
        _emit 0x24
        // mov eax, dword ptr [eax + 0x24]
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x48
        // lea edx, [esp + 0x48]
        _emit 0x52
        // push edx
        _emit 0x68
        _emit 0xC2
        _emit 0x78
        _emit 0xC3
        _emit 0x02
        // push 0x2c378c2
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x13
        // je 0xbb3b07
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // mov ecx, dword ptr [esp + 0x48]
        _emit 0x66
        _emit 0x39
        _emit 0x69
        _emit 0x12
        // cmp word ptr [ecx + 0x12], bp
        _emit 0x75
        _emit 0x09
        // jne 0xbb3b07
        call FUN_0041e990
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x89
        _emit 0x0F
        // mov dword ptr [edi], ecx
        _emit 0x8B
        _emit 0x13
        // mov edx, dword ptr [ebx]
        _emit 0xC1
        _emit 0xEA
        _emit 0x04
        // shr edx, 4
        _emit 0xF6
        _emit 0xC2
        _emit 0x01
        // test dl, 1
        _emit 0x74
        _emit 0x39
        // je 0xbb3b4a
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov edi, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x8E
        _emit 0xA0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x1a0]
        _emit 0x83
        _emit 0xC7
        _emit 0x10
        // add edi, 0x10
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x28
        // je 0xbb3b4a
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x40
        _emit 0x24
        // mov eax, dword ptr [eax + 0x24]
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x48
        // lea edx, [esp + 0x48]
        _emit 0x52
        // push edx
        _emit 0x68
        _emit 0x31
        _emit 0xB1
        _emit 0x06
        _emit 0x03
        // push 0x306b131
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x13
        // je 0xbb3b4a
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // mov ecx, dword ptr [esp + 0x48]
        _emit 0x66
        _emit 0x39
        _emit 0x69
        _emit 0x12
        // cmp word ptr [ecx + 0x12], bp
        _emit 0x75
        _emit 0x09
        // jne 0xbb3b4a
        call FUN_0041e990
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x89
        _emit 0x0F
        // mov dword ptr [edi], ecx
        _emit 0x8B
        _emit 0x13
        // mov edx, dword ptr [ebx]
        _emit 0xC1
        _emit 0xEA
        _emit 0x05
        // shr edx, 5
        _emit 0xF6
        _emit 0xC2
        _emit 0x01
        // test dl, 1
        _emit 0x74
        _emit 0x39
        // je 0xbb3b8d
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov edi, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x8E
        _emit 0xA0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x1a0]
        _emit 0x83
        _emit 0xC7
        _emit 0x14
        // add edi, 0x14
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x28
        // je 0xbb3b8d
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x40
        _emit 0x24
        // mov eax, dword ptr [eax + 0x24]
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x48
        // lea edx, [esp + 0x48]
        _emit 0x52
        // push edx
        _emit 0x68
        _emit 0x33
        _emit 0xB1
        _emit 0x06
        _emit 0x03
        // push 0x306b133
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x13
        // je 0xbb3b8d
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // mov ecx, dword ptr [esp + 0x48]
        _emit 0x66
        _emit 0x39
        _emit 0x69
        _emit 0x12
        // cmp word ptr [ecx + 0x12], bp
        _emit 0x75
        _emit 0x09
        // jne 0xbb3b8d
        call FUN_0041e990
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x89
        _emit 0x0F
        // mov dword ptr [edi], ecx
        _emit 0x8B
        _emit 0x13
        // mov edx, dword ptr [ebx]
        _emit 0xD1
        _emit 0xEA
        // shr edx, 1
        _emit 0xF6
        _emit 0xC2
        _emit 0x01
        // test dl, 1
        _emit 0x74
        _emit 0x39
        // je 0xbb3bcf
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov edi, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x8E
        _emit 0xA0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x1a0]
        _emit 0x83
        _emit 0xC7
        _emit 0x04
        // add edi, 4
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x28
        // je 0xbb3bcf
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x40
        _emit 0x24
        // mov eax, dword ptr [eax + 0x24]
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x48
        // lea edx, [esp + 0x48]
        _emit 0x52
        // push edx
        _emit 0x68
        _emit 0xFC
        _emit 0x78
        _emit 0xC3
        _emit 0x02
        // push 0x2c378fc
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x13
        // je 0xbb3bcf
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // mov ecx, dword ptr [esp + 0x48]
        _emit 0x66
        _emit 0x39
        _emit 0x69
        _emit 0x12
        // cmp word ptr [ecx + 0x12], bp
        _emit 0x75
        _emit 0x09
        // jne 0xbb3bcf
        call FUN_0041e990
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x89
        _emit 0x0F
        // mov dword ptr [edi], ecx
        _emit 0xF6
        _emit 0x03
        _emit 0x01
        // test byte ptr [ebx], 1
        _emit 0x74
        _emit 0x36
        // je 0xbb3c0a
        _emit 0x8B
        _emit 0x8E
        _emit 0xA0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x1a0]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov edi, dword ptr [esp + 0x14]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x28
        // je 0xbb3c0a
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x52
        _emit 0x24
        // mov edx, dword ptr [edx + 0x24]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // lea eax, [esp + 0x48]
        _emit 0x50
        // push eax
        _emit 0x68
        _emit 0x07
        _emit 0x79
        _emit 0xC3
        _emit 0x02
        // push 0x2c37907
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x13
        // je 0xbb3c0a
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // mov ecx, dword ptr [esp + 0x48]
        _emit 0x66
        _emit 0x39
        _emit 0x69
        _emit 0x12
        // cmp word ptr [ecx + 0x12], bp
        _emit 0x75
        _emit 0x09
        // jne 0xbb3c0a
        call FUN_0041e990
        _emit 0x8B
        _emit 0x00
        // mov eax, dword ptr [eax]
        _emit 0x89
        _emit 0x07
        // mov dword ptr [edi], eax
        _emit 0x8B
        _emit 0x0B
        // mov ecx, dword ptr [ebx]
        _emit 0xC1
        _emit 0xE9
        _emit 0x06
        // shr ecx, 6
        _emit 0xF6
        _emit 0xC1
        _emit 0x01
        // test cl, 1
        _emit 0x74
        _emit 0x39
        // je 0xbb3c4d
        _emit 0x8B
        _emit 0x8E
        _emit 0xA0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x1a0]
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x14
        // mov esi, dword ptr [esp + 0x14]
        _emit 0x83
        _emit 0xC6
        _emit 0x18
        // add esi, 0x18
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x28
        // je 0xbb3c4d
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x52
        _emit 0x24
        // mov edx, dword ptr [edx + 0x24]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // lea eax, [esp + 0x48]
        _emit 0x50
        // push eax
        _emit 0x68
        _emit 0x67
        _emit 0x22
        _emit 0x2A
        _emit 0x04
        // push 0x42a2267
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x13
        // je 0xbb3c4d
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // mov ecx, dword ptr [esp + 0x48]
        _emit 0x66
        _emit 0x39
        _emit 0x69
        _emit 0x12
        // cmp word ptr [ecx + 0x12], bp
        _emit 0x75
        _emit 0x09
        // jne 0xbb3c4d
        call FUN_0041e990
        _emit 0x8B
        _emit 0x00
        // mov eax, dword ptr [eax]
        _emit 0x89
        _emit 0x06
        // mov dword ptr [esi], eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // lea ecx, [esp + 0x14]
        _emit 0x51
        // push ecx
        call FUN_00ba7320
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xF8
        _emit 0x07
        // cmp eax, 7
        _emit 0x75
        _emit 0x05
        // jne 0xbb3c68
        _emit 0xB8
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 2
        _emit 0x83
        _emit 0xC4
        _emit 0x34
        // add esp, 0x34
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00bb3c70  (1166 bytes)
__declspec(naked) void FUN_00bb3c70()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x74
        // sub esp, 0x74
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0x0C
        _emit 0xC5
        _emit 0x56
        _emit 0x01
        // movss xmm0, dword ptr [0x156c50c]
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xD9
        // mov ebx, ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC0
        // mulss xmm0, xmm0
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // lea ecx, [esp + 0x48]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // movss dword ptr [esp + 0x30], xmm0
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // mov dword ptr [esp + 0x48], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x4C
        // mov dword ptr [esp + 0x4c], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x50
        // mov dword ptr [esp + 0x50], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], eax
        call FUN_00e25bd0
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // mov eax, dword ptr [esp + 0x44]
        _emit 0x2B
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // sub eax, dword ptr [esp + 0x40]
        _emit 0xC1
        _emit 0xF8
        _emit 0x02
        // sar eax, 2
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], eax
        _emit 0xEB
        _emit 0x03
        // jmp 0xbb3cc0
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0xB9
        _emit 0x60
        _emit 0x17
        _emit 0x60
        _emit 0x01
        // mov ecx, 0x1601760
        call FUN_009360d0
        _emit 0xDC
        _emit 0x0D
        _emit 0xC8
        _emit 0x61
        _emit 0x46
        _emit 0x01
        // fmul qword ptr [0x14661c8]
        _emit 0xDD
        _emit 0x05
        _emit 0xC0
        _emit 0x61
        _emit 0x46
        _emit 0x01
        // fld qword ptr [0x14661c0]
        _emit 0xDC
        _emit 0xE9
        // fsub st(1), st(0)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xDB
        _emit 0xF1
        // fcomi st(1)
        _emit 0x73
        _emit 0x10
        // jae 0xbb3cee
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0xDD
        _emit 0x05
        _emit 0xB8
        _emit 0x61
        _emit 0x46
        _emit 0x01
        // fld qword ptr [0x14661b8]
        _emit 0xDB
        _emit 0xF1
        // fcomi st(1)
        _emit 0x76
        _emit 0x04
        // jbe 0xbb3cee
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0xEB
        _emit 0x02
        // jmp 0xbb3cf0
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xB9
        _emit 0x60
        _emit 0x17
        _emit 0x60
        _emit 0x01
        // mov ecx, 0x1601760
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        call FUN_009360d0
        _emit 0xDC
        _emit 0x0D
        _emit 0xC8
        _emit 0x61
        _emit 0x46
        _emit 0x01
        // fmul qword ptr [0x14661c8]
        _emit 0xDD
        _emit 0x05
        _emit 0xC0
        _emit 0x61
        _emit 0x46
        _emit 0x01
        // fld qword ptr [0x14661c0]
        _emit 0xDC
        _emit 0xE9
        // fsub st(1), st(0)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xDB
        _emit 0xF1
        // fcomi st(1)
        _emit 0x73
        _emit 0x10
        // jae 0xbb3d22
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0xDD
        _emit 0x05
        _emit 0xB8
        _emit 0x61
        _emit 0x46
        _emit 0x01
        // fld qword ptr [0x14661b8]
        _emit 0xDB
        _emit 0xF1
        // fcomi st(1)
        _emit 0x76
        _emit 0x04
        // jbe 0xbb3d22
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0xEB
        _emit 0x02
        // jmp 0xbb3d24
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // movss xmm1, dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // movss xmm0, dword ptr [esp + 0x20]
        _emit 0x0F
        _emit 0x28
        _emit 0xD1
        // movaps xmm2, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD1
        // mulss xmm2, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // movss xmm1, dword ptr [esp + 0x28]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC0
        // mulss xmm0, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC2
        // addss xmm0, xmm2
        _emit 0x0F
        _emit 0x2F
        _emit 0xC8
        // comiss xmm1, xmm0
        _emit 0x0F
        _emit 0x87
        _emit 0x6E
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // ja 0xbb3cc0
        _emit 0x0F
        _emit 0x2F
        _emit 0x05
        _emit 0xB0
        _emit 0x61
        _emit 0x46
        _emit 0x01
        // comiss xmm0, dword ptr [0x14661b0]
        _emit 0x0F
        _emit 0x87
        _emit 0x61
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // ja 0xbb3cc0
        _emit 0x8B
        _emit 0xB3
        _emit 0xF4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov esi, dword ptr [ebx + 0xf4]
        _emit 0x2B
        _emit 0xB3
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // sub esi, dword ptr [ebx + 0xf0]
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0xC1
        _emit 0xFE
        _emit 0x02
        // sar esi, 2
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x13
        _emit 0x01
        // mov byte ptr [esp + 0x13], 1
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x76
        _emit 0x68
        // jbe 0xbb3de1
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0x8B
        _emit 0x83
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [ebx + 0xf0]
        _emit 0x8B
        _emit 0x3C
        _emit 0xA8
        // mov edi, dword ptr [eax + ebp*4]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_005c65e0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x00
        // movss xmm0, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // subss xmm0, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // movss dword ptr [esp + 0x2c], xmm0
        call FUN_005c65e0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x04
        // movss xmm0, dword ptr [eax + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // subss xmm0, dword ptr [esp + 0x20]
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // movss xmm0, dword ptr [esp + 0x2c]
        _emit 0x0F
        _emit 0x28
        _emit 0xD0
        // movaps xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD0
        // mulss xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0xD0
        _emit 0xC4
        _emit 0x3E
        _emit 0x01
        // movss xmm0, dword ptr [0x13ec4d0]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xCA
        // addss xmm1, xmm2
        _emit 0x0F
        _emit 0x2F
        _emit 0xC1
        // comiss xmm0, xmm1
        _emit 0x76
        _emit 0x05
        // jbe 0xbb3ddc
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x13
        _emit 0x00
        // mov byte ptr [esp + 0x13], 0
        _emit 0x45
        // inc ebp
        _emit 0x3B
        _emit 0xEE
        // cmp ebp, esi
        _emit 0x72
        _emit 0x9F
        // jb 0xbb3d80
        _emit 0x8B
        _emit 0xAB
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebp, dword ptr [ebx + 0xe0]
        _emit 0x2B
        _emit 0xAB
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // sub ebp, dword ptr [ebx + 0xdc]
        _emit 0x33
        _emit 0xFF
        // xor edi, edi
        _emit 0xC1
        _emit 0xFD
        _emit 0x02
        // sar ebp, 2
        _emit 0x85
        _emit 0xED
        // test ebp, ebp
        _emit 0x76
        _emit 0x6B
        // jbe 0xbb3e61
        _emit 0xEB
        _emit 0x08
        // jmp 0xbb3e00
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0x90
        // nop 
        _emit 0x8B
        _emit 0x8B
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [ebx + 0xdc]
        _emit 0x8B
        _emit 0x34
        _emit 0xB9
        // mov esi, dword ptr [ecx + edi*4]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_005c65e0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x00
        // movss xmm0, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // subss xmm0, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // movss dword ptr [esp + 0x30], xmm0
        call FUN_005c65e0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x04
        // movss xmm0, dword ptr [eax + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // subss xmm0, dword ptr [esp + 0x20]
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // movss xmm0, dword ptr [esp + 0x30]
        _emit 0x0F
        _emit 0x28
        _emit 0xD0
        // movaps xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD0
        // mulss xmm2, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0xD0
        _emit 0xC4
        _emit 0x3E
        _emit 0x01
        // movss xmm0, dword ptr [0x13ec4d0]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xCA
        // addss xmm1, xmm2
        _emit 0x0F
        _emit 0x2F
        _emit 0xC1
        // comiss xmm0, xmm1
        _emit 0x76
        _emit 0x05
        // jbe 0xbb3e5c
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x13
        _emit 0x00
        // mov byte ptr [esp + 0x13], 0
        _emit 0x47
        // inc edi
        _emit 0x3B
        _emit 0xFD
        // cmp edi, ebp
        _emit 0x72
        _emit 0x9F
        // jb 0xbb3e00
        _emit 0x80
        _emit 0x7C
        _emit 0x24
        _emit 0x13
        _emit 0x00
        // cmp byte ptr [esp + 0x13], 0
        _emit 0x75
        _emit 0x17
        // jne 0xbb3e7f
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0x40
        // inc eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], eax
        _emit 0x81
        _emit 0xFA
        _emit 0xE8
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // cmp edx, 0x3e8
        _emit 0x0F
        _emit 0x82
        _emit 0x41
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jb 0xbb3cc0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0xBC
        _emit 0xB1
        _emit 0x3E
        _emit 0x01
        // movss xmm0, dword ptr [0x13eb1bc]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x44
        // mov edi, dword ptr [esp + 0x44]
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x70
        // mov dword ptr [esp + 0x70], eax
        _emit 0x89
        _emit 0x84
        _emit 0x24
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x80], eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // mov eax, dword ptr [esp + 0x40]
        _emit 0x50
        // push eax
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
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0x70
        _emit 0x3C
        _emit 0x47
        _emit 0x01
        // movss xmm0, dword ptr [0x1473c70]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x7C
        // movss dword ptr [esp + 0x7c], xmm0
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0x57
        // push edi
        _emit 0x57
        // push edi
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x78
        _emit 0x3F
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x78], 0x3f
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x74
        _emit 0x10
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x74], 0x10
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
        call FUN_006782c0
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x3B
        _emit 0xF7
        // cmp esi, edi
        _emit 0x73
        _emit 0x14
        // jae 0xbb3ef4
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x07
        // je 0xbb3eed
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
        _emit 0x83
        _emit 0xC6
        _emit 0x04
        // add esi, 4
        _emit 0x3B
        _emit 0xF7
        // cmp esi, edi
        _emit 0x72
        _emit 0xEC
        // jb 0xbb3ee0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // mov ecx, dword ptr [esp + 0x24]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // movss xmm0, dword ptr [esp + 0x1c]
        _emit 0xF7
        _emit 0xD9
        // neg ecx
        _emit 0x8D
        _emit 0x14
        _emit 0x8F
        // lea edx, [edi + ecx*4]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // lea eax, [esp + 0x40]
        _emit 0x50
        // push eax
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
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // movss xmm0, dword ptr [esp + 0x24]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x6C
        // lea ecx, [esp + 0x6c]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x48
        // mov dword ptr [esp + 0x48], edx
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x3C
        // lea edx, [esp + 0x3c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // movss dword ptr [esp + 0x40], xmm0
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // movss dword ptr [esp + 0x48], xmm0
        call FUN_00bb1080
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // mov eax, dword ptr [esp + 0x44]
        _emit 0x2B
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // sub eax, dword ptr [esp + 0x40]
        _emit 0xC1
        _emit 0xF8
        _emit 0x02
        // sar eax, 2
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x75
        _emit 0x17
        // jne 0xbb3f62
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x40
        // inc eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], eax
        _emit 0x81
        _emit 0xF9
        _emit 0xE8
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // cmp ecx, 0x3e8
        _emit 0x0F
        _emit 0x82
        _emit 0x5E
        _emit 0xFD
        _emit 0xFF
        _emit 0xFF
        // jb 0xbb3cc0
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // mov eax, dword ptr [esp + 0x44]
        _emit 0x2B
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // sub eax, dword ptr [esp + 0x40]
        _emit 0x33
        _emit 0xC9
        // xor ecx, ecx
        _emit 0xC1
        _emit 0xF8
        _emit 0x02
        // sar eax, 2
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x54
        // mov dword ptr [esp + 0x54], ebp
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x5C
        // mov dword ptr [esp + 0x5c], ecx
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], ecx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], eax
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x0F
        _emit 0x86
        _emit 0xE5
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jbe 0xbb4070
        _emit 0xEB
        _emit 0x03
        // jmp 0xbb3f90
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x40
        // mov edx, dword ptr [esp + 0x40]
        _emit 0x8B
        _emit 0x14
        _emit 0x8A
        // mov edx, dword ptr [edx + ecx*4]
        _emit 0x80
        _emit 0xBA
        _emit 0xAC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [edx + 0xac], 0
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], edx
        _emit 0x0F
        _emit 0x85
        _emit 0xB5
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0xbb405d
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x74
        // movss dword ptr [esp + 0x74], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0x90
        _emit 0x5E
        _emit 0x46
        _emit 0x01
        // movss xmm0, dword ptr [0x1465e90]
        _emit 0x55
        // push ebp
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x7C
        // movss dword ptr [esp + 0x7c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x05
        _emit 0xA8
        _emit 0x5E
        _emit 0x46
        _emit 0x01
        // movss xmm0, dword ptr [0x1465ea8]
        _emit 0x56
        // push esi
        _emit 0x56
        // push esi
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x74
        _emit 0xFF
        _emit 0x1F
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x74], 0x1fff
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x78
        _emit 0x3F
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x78], 0x3f
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x7C
        // mov dword ptr [esp + 0x7c], eax
        _emit 0x89
        _emit 0x84
        _emit 0x24
        _emit 0x8C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x8c], eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x84
        _emit 0x24
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esp + 0x88], xmm0
        call FUN_006782c0
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x3B
        _emit 0xFE
        // cmp edi, esi
        _emit 0x73
        _emit 0x16
        // jae 0xbb4014
        _emit 0x8B
        _emit 0xFF
        // mov edi, edi
        _emit 0x8B
        _emit 0x0F
        // mov ecx, dword ptr [edi]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x07
        // je 0xbb400d
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
        _emit 0x83
        _emit 0xC7
        _emit 0x04
        // add edi, 4
        _emit 0x3B
        _emit 0xFE
        // cmp edi, esi
        _emit 0x72
        _emit 0xEC
        // jb 0xbb4000
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x1C
        // mov edi, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x2B
        _emit 0xC5
        // sub eax, ebp
        _emit 0xC1
        _emit 0xF8
        _emit 0x02
        // sar eax, 2
        _emit 0xF7
        _emit 0xD8
        // neg eax
        _emit 0x8D
        _emit 0x0C
        _emit 0x86
        // lea ecx, [esi + eax*4]
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x54
        // lea edx, [esp + 0x54]
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x6C
        // lea eax, [esp + 0x6c]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x5C
        // mov dword ptr [esp + 0x5c], ecx
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_005c65e0
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        call FUN_00bb1080
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x58
        // mov esi, dword ptr [esp + 0x58]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x54
        // mov ebp, dword ptr [esp + 0x54]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x2B
        _emit 0xCD
        // sub ecx, ebp
        _emit 0xC1
        _emit 0xF9
        _emit 0x02
        // sar ecx, 2
        _emit 0x83
        _emit 0xF9
        _emit 0x14
        // cmp ecx, 0x14
        _emit 0x73
        _emit 0x17
        // jae 0xbb406c
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // mov eax, dword ptr [esp + 0x24]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0x41
        // inc ecx
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], ecx
        _emit 0x3B
        _emit 0xC8
        // cmp ecx, eax
        _emit 0x0F
        _emit 0x82
        _emit 0x26
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jb 0xbb3f90
        _emit 0xEB
        _emit 0x04
        // jmp 0xbb4070
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], edi
        _emit 0x8B
        _emit 0xFD
        // mov edi, ebp
        _emit 0x3B
        _emit 0xEE
        // cmp ebp, esi
        _emit 0x73
        _emit 0x14
        // jae 0xbb408a
        _emit 0x8B
        _emit 0x0F
        // mov ecx, dword ptr [edi]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x07
        // je 0xbb4083
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
        _emit 0x83
        _emit 0xC7
        _emit 0x04
        // add edi, 4
        _emit 0x3B
        _emit 0xFE
        // cmp edi, esi
        _emit 0x72
        _emit 0xEC
        // jb 0xbb4076
        _emit 0x85
        _emit 0xED
        // test ebp, ebp
        _emit 0x74
        _emit 0x0F
        // je 0xbb409d
        _emit 0x83
        _emit 0x7D
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [ebp - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xbb409d
        _emit 0x55
        // push ebp
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x83
        _emit 0x7C
        _emit 0x24
        _emit 0x18
        _emit 0x00
        // cmp dword ptr [esp + 0x18], 0
        _emit 0x75
        _emit 0x17
        // jne 0xbb40bb
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x40
        // inc eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], eax
        _emit 0x81
        _emit 0xF9
        _emit 0xE8
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // cmp ecx, 0x3e8
        _emit 0x0F
        _emit 0x82
        _emit 0x05
        _emit 0xFC
        _emit 0xFF
        _emit 0xFF
        // jb 0xbb3cc0
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x40
        // mov esi, dword ptr [esp + 0x40]
        _emit 0x3B
        _emit 0x74
        _emit 0x24
        _emit 0x44
        // cmp esi, dword ptr [esp + 0x44]
        _emit 0x73
        _emit 0x1A
        // jae 0xbb40df
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x07
        // je 0xbb40d2
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
        _emit 0x83
        _emit 0xC6
        _emit 0x04
        // add esi, 4
        _emit 0x3B
        _emit 0x74
        _emit 0x24
        _emit 0x44
        // cmp esi, dword ptr [esp + 0x44]
        _emit 0x72
        _emit 0xEA
        // jb 0xbb40c5
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x40
        // mov esi, dword ptr [esp + 0x40]
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x0F
        // je 0xbb40f2
        _emit 0x83
        _emit 0x7E
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [esi - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xbb40f2
        _emit 0x56
        // push esi
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov eax, dword ptr [esp + 0x18]
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
        _emit 0x74
        // add esp, 0x74
        _emit 0xC3
        // ret 
    }
}
