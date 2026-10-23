// Slice s008c63a0: Spore image/codec routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_008c44d0();
extern "C" void FUN_008c4a00();
extern "C" void FUN_008c5320();
extern "C" void FUN_008c54d0();
extern "C" void FUN_008c63a0();
extern "C" void FUN_008c6500();
extern "C" void FUN_008c65d0();
extern "C" void FUN_008c6720();
extern "C" void FUN_008cc0b0();
extern "C" void FUN_008cc190();
extern "C" void FUN_008cc580();
extern "C" void FUN_008d10c0();
extern "C" void FUN_008d1260();
extern "C" void FUN_008d1440();
extern "C" void FUN_011e073e();

// @ 0x008c63a0  (345 bytes)
__declspec(naked) void FUN_008c63a0()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x20
        // sub esp, 0x20
        _emit 0x53
        // push ebx
        _emit 0x0F
        _emit 0xB7
        _emit 0x58
        _emit 0x16
        // movzx ebx, word ptr [eax + 0x16]
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x68
        _emit 0x28
        // mov ebp, dword ptr [eax + 0x28]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x71
        _emit 0x2C
        // mov esi, dword ptr [ecx + 0x2c]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], ebx
        _emit 0x0F
        _emit 0xB7
        _emit 0x59
        _emit 0x16
        // movzx ebx, word ptr [ecx + 0x16]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x78
        _emit 0x2C
        // mov edi, dword ptr [eax + 0x2c]
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ebp
        _emit 0x8B
        _emit 0x69
        _emit 0x28
        // mov ebp, dword ptr [ecx + 0x28]
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], esi
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], ebx
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], ebp
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x0F
        _emit 0x84
        _emit 0x1A
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0x8c64f1
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x0F
        _emit 0x84
        _emit 0x12
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0x8c64f1
        _emit 0x0F
        _emit 0xB7
        _emit 0x40
        _emit 0x14
        // movzx eax, word ptr [eax + 0x14]
        _emit 0x0F
        _emit 0xAF
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // imul eax, dword ptr [esp + 0x14]
        _emit 0x03
        _emit 0xC7
        // add eax, edi
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], eax
        _emit 0x0F
        _emit 0xB6
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // movzx eax, byte ptr [esp + 0x34]
        _emit 0x0F
        _emit 0xAF
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // imul eax, dword ptr [esp + 0x14]
        _emit 0x03
        _emit 0xF8
        // add edi, eax
        _emit 0x80
        _emit 0x7C
        _emit 0x24
        _emit 0x38
        _emit 0x00
        // cmp byte ptr [esp + 0x38], 0
        _emit 0x76
        _emit 0x69
        // jbe 0x8c646a
        _emit 0x0F
        _emit 0xB7
        _emit 0x49
        _emit 0x14
        // movzx ecx, word ptr [ecx + 0x14]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ecx
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x0F
        _emit 0x8E
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jle 0x8c64f1
        _emit 0x0F
        _emit 0xB6
        _emit 0xEA
        // movzx ebp, dl
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x8B
        _emit 0xC5
        // mov eax, ebp
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x7E
        _emit 0x27
        // jle 0x8c6443
        _emit 0x2B
        _emit 0xF5
        // sub esi, ebp
        _emit 0x8B
        _emit 0xFF
        // mov edi, edi
        _emit 0x3B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // cmp eax, dword ptr [esp + 0x1c]
        _emit 0x7D
        _emit 0x15
        // jge 0x8c643b
        _emit 0x8A
        _emit 0x0C
        _emit 0x06
        // mov cl, byte ptr [esi + eax]
        _emit 0x84
        _emit 0xC9
        // test cl, cl
        _emit 0x74
        _emit 0x08
        // je 0x8c6435
        _emit 0x3A
        _emit 0x0C
        _emit 0x38
        // cmp cl, byte ptr [eax + edi]
        _emit 0x76
        _emit 0x03
        // jbe 0x8c6435
        _emit 0x88
        _emit 0x0C
        _emit 0x38
        // mov byte ptr [eax + edi], cl
        _emit 0x42
        // inc edx
        _emit 0x40
        // inc eax
        _emit 0x3B
        _emit 0xD3
        // cmp edx, ebx
        _emit 0x7C
        _emit 0xE5
        // jl 0x8c6420
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x18
        // mov esi, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x03
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // add edi, dword ptr [esp + 0x14]
        _emit 0x03
        _emit 0x74
        _emit 0x24
        _emit 0x20
        // add esi, dword ptr [esp + 0x20]
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], esi
        _emit 0x3B
        _emit 0x7C
        _emit 0x24
        _emit 0x24
        // cmp edi, dword ptr [esp + 0x24]
        _emit 0x0F
        _emit 0x83
        _emit 0x98
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jae 0x8c64f1
        _emit 0x49
        // dec ecx
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ecx
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x7F
        _emit 0xB2
        // jg 0x8c6414
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
        _emit 0x20
        // add esp, 0x20
        _emit 0xC3
        // ret 
        _emit 0x0F
        _emit 0xB7
        _emit 0x41
        _emit 0x14
        // movzx eax, word ptr [ecx + 0x14]
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x7E
        _emit 0x79
        // jle 0x8c64f1
        _emit 0x0F
        _emit 0xB6
        _emit 0xCA
        // movzx ecx, dl
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], ecx
        _emit 0x90
        // nop 
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // mov eax, dword ptr [esp + 0x28]
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x7E
        _emit 0x48
        // jle 0x8c64d2
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebx, [ebx]
        _emit 0x3B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // cmp eax, dword ptr [esp + 0x1c]
        _emit 0x7D
        _emit 0x3C
        // jge 0x8c64d2
        _emit 0xF6
        _emit 0xC2
        _emit 0x07
        // test dl, 7
        _emit 0x75
        _emit 0x09
        // jne 0x8c64a4
        _emit 0x8B
        _emit 0xCA
        // mov ecx, edx
        _emit 0xC1
        _emit 0xF9
        _emit 0x03
        // sar ecx, 3
        _emit 0x0F
        _emit 0xB6
        _emit 0x2C
        _emit 0x31
        // movzx ebp, byte ptr [ecx + esi]
        _emit 0x03
        _emit 0xED
        // add ebp, ebp
        _emit 0xF7
        _emit 0xC5
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // test ebp, 0x100
        _emit 0x74
        _emit 0x1E
        // je 0x8c64cc
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xC1
        _emit 0xF9
        _emit 0x03
        // sar ecx, 3
        _emit 0x8D
        _emit 0x34
        _emit 0x39
        // lea esi, [ecx + edi]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x83
        _emit 0xE1
        _emit 0x07
        // and ecx, 7
        _emit 0xBB
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 0x80
        _emit 0xD3
        _emit 0xFB
        // sar ebx, cl
        _emit 0x08
        _emit 0x1E
        // or byte ptr [esi], bl
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x2C
        // mov ebx, dword ptr [esp + 0x2c]
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x18
        // mov esi, dword ptr [esp + 0x18]
        _emit 0x42
        // inc edx
        _emit 0x40
        // inc eax
        _emit 0x3B
        _emit 0xD3
        // cmp edx, ebx
        _emit 0x7C
        _emit 0xBE
        // jl 0x8c6490
        _emit 0x03
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // add edi, dword ptr [esp + 0x14]
        _emit 0x03
        _emit 0x74
        _emit 0x24
        _emit 0x20
        // add esi, dword ptr [esp + 0x20]
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], esi
        _emit 0x3B
        _emit 0x7C
        _emit 0x24
        _emit 0x24
        // cmp edi, dword ptr [esp + 0x24]
        _emit 0x73
        _emit 0x0D
        // jae 0x8c64f1
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0x48
        // dec eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x7F
        _emit 0x8F
        // jg 0x8c6480
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
        _emit 0x20
        // add esp, 0x20
        _emit 0xC3
        // ret 
    }
}

// @ 0x008c6500  (202 bytes)
__declspec(naked) void FUN_008c6500()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov edx, dword ptr [esp + 0x14]
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // mov ebx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0x0F
        _emit 0xAF
        _emit 0xCA
        // imul ecx, edx
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x14
        // mov ebp, dword ptr [esp + 0x14]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x8B
        _emit 0xC3
        // mov eax, ebx
        _emit 0xD1
        _emit 0xF8
        // sar eax, 1
        _emit 0x3B
        _emit 0xD3
        // cmp edx, ebx
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], edi
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ecx
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], edx
        _emit 0x7E
        _emit 0x4B
        // jle 0x8c6578
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x0F
        _emit 0x8D
        _emit 0x8E
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jge 0x8c65c3
        _emit 0x3B
        _emit 0xD0
        // cmp edx, eax
        _emit 0x7D
        _emit 0x0A
        // jge 0x8c6543
        _emit 0x03
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // add edx, dword ptr [esp + 0x20]
        _emit 0x03
        _emit 0xFE
        // add edi, esi
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], edi
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x7E
        _emit 0x22
        // jle 0x8c6569
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0x2B
        _emit 0xFD
        // sub edi, ebp
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], esi
        _emit 0x90
        // nop 
        _emit 0x8A
        _emit 0x1C
        _emit 0x0F
        // mov bl, byte ptr [edi + ecx]
        _emit 0x88
        _emit 0x19
        // mov byte ptr [ecx], bl
        _emit 0x41
        // inc ecx
        _emit 0x83
        _emit 0x6C
        _emit 0x24
        _emit 0x18
        _emit 0x01
        // sub dword ptr [esp + 0x18], 1
        _emit 0x75
        _emit 0xF3
        // jne 0x8c6550
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x0C
        // mov edi, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov ebx, dword ptr [esp + 0x1c]
        _emit 0x03
        _emit 0xC3
        // add eax, ebx
        _emit 0x03
        _emit 0xEE
        // add ebp, esi
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x7C
        _emit 0xC4
        // jl 0x8c6535
        _emit 0x5F
        // pop edi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC3
        // ret 
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x7D
        _emit 0x47
        // jge 0x8c65c3
        _emit 0x8B
        _emit 0xDA
        // mov ebx, edx
        _emit 0xEB
        _emit 0x04
        // jmp 0x8c6584
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // mov ebx, dword ptr [esp + 0x20]
        _emit 0x3B
        _emit 0xD0
        // cmp edx, eax
        _emit 0x7D
        _emit 0x10
        // jge 0x8c6598
        _emit 0x03
        _emit 0xD3
        // add edx, ebx
        _emit 0x03
        _emit 0xFE
        // add edi, esi
        _emit 0x3B
        _emit 0xD0
        // cmp edx, eax
        _emit 0x7C
        _emit 0xF8
        // jl 0x8c6588
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], edi
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], edx
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x7E
        _emit 0x1D
        // jle 0x8c65b9
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0x2B
        _emit 0xFD
        // sub edi, ebp
        _emit 0x8B
        _emit 0xD6
        // mov edx, esi
        _emit 0x8A
        _emit 0x1C
        _emit 0x39
        // mov bl, byte ptr [ecx + edi]
        _emit 0x88
        _emit 0x19
        // mov byte ptr [ecx], bl
        _emit 0x41
        // inc ecx
        _emit 0x83
        _emit 0xEA
        _emit 0x01
        // sub edx, 1
        _emit 0x75
        _emit 0xF5
        // jne 0x8c65a2
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x0C
        // mov edi, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x18
        // mov edx, dword ptr [esp + 0x18]
        _emit 0x03
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // add eax, dword ptr [esp + 0x1c]
        _emit 0x03
        _emit 0xEE
        // add ebp, esi
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x7C
        _emit 0xBD
        // jl 0x8c6580
        _emit 0x5F
        // pop edi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC3
        // ret 
    }
}

// @ 0x008c65d0  (329 bytes)
__declspec(naked) void FUN_008c65d0()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x20
        // sub esp, 0x20
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x28
        // mov edi, dword ptr [esp + 0x28]
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], edi
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // mov dword ptr [esp + 8], edx
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x0F
        _emit 0x8E
        _emit 0x2C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jle 0x8c6714
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x34
        // mov ebp, dword ptr [esp + 0x34]
        _emit 0xD1
        _emit 0xFD
        // sar ebp, 1
        _emit 0x56
        // push esi
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], ebp
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], ecx
        _emit 0xEB
        _emit 0x09
        // jmp 0x8c6604
        _emit 0xEB
        _emit 0x03
        // jmp 0x8c6600
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x28
        // mov ebp, dword ptr [esp + 0x28]
        _emit 0x33
        _emit 0xC9
        // xor ecx, ecx
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], ebp
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x38
        _emit 0x4C
        _emit 0x24
        _emit 0x44
        // cmp byte ptr [esp + 0x44], cl
        _emit 0x76
        _emit 0x31
        // jbe 0x8c6643
        _emit 0x33
        _emit 0xFF
        // xor edi, edi
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x0F
        _emit 0x8E
        _emit 0xD6
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jle 0x8c66f2
        _emit 0x8D
        _emit 0x64
        _emit 0x24
        _emit 0x00
        // lea esp, [esp]
        _emit 0x3B
        _emit 0xF5
        // cmp esi, ebp
        _emit 0x7D
        _emit 0x07
        // jge 0x8c662b
        _emit 0x03
        _emit 0xF0
        // add esi, eax
        _emit 0x47
        // inc edi
        _emit 0x3B
        _emit 0xF5
        // cmp esi, ebp
        _emit 0x7C
        _emit 0xF9
        // jl 0x8c6624
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov ebx, dword ptr [esp + 0x18]
        _emit 0x8A
        _emit 0x1C
        _emit 0x1F
        // mov bl, byte ptr [edi + ebx]
        _emit 0x03
        _emit 0x6C
        _emit 0x24
        _emit 0x38
        // add ebp, dword ptr [esp + 0x38]
        _emit 0x88
        _emit 0x1C
        _emit 0x11
        // mov byte ptr [ecx + edx], bl
        _emit 0x41
        // inc ecx
        _emit 0x3B
        _emit 0xC8
        // cmp ecx, eax
        _emit 0x7C
        _emit 0xE2
        // jl 0x8c6620
        _emit 0xE9
        _emit 0xAF
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jmp 0x8c66f2
        _emit 0x8A
        _emit 0x17
        // mov dl, byte ptr [edi]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x88
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // mov byte ptr [esp + 0x34], cl
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ecx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ebx
        _emit 0x0F
        _emit 0x8E
        _emit 0x83
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jle 0x8c66de
        _emit 0xEB
        _emit 0x03
        // jmp 0x8c6660
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0x3B
        _emit 0xF5
        // cmp esi, ebp
        _emit 0x7D
        _emit 0x1E
        // jge 0x8c6682
        _emit 0x43
        // inc ebx
        _emit 0x03
        _emit 0xF0
        // add esi, eax
        _emit 0x02
        _emit 0xD2
        // add dl, dl
        _emit 0xF6
        _emit 0xC3
        _emit 0x07
        // test bl, 7
        _emit 0x75
        _emit 0x0C
        // jne 0x8c667a
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x18
        // mov edi, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0xD3
        // mov edx, ebx
        _emit 0xC1
        _emit 0xFA
        _emit 0x03
        // sar edx, 3
        _emit 0x8A
        _emit 0x14
        _emit 0x3A
        // mov dl, byte ptr [edx + edi]
        _emit 0x3B
        _emit 0xF5
        // cmp esi, ebp
        _emit 0x7C
        _emit 0xE6
        // jl 0x8c6664
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ebx
        _emit 0x84
        _emit 0xD2
        // test dl, dl
        _emit 0x79
        _emit 0x16
        // jns 0x8c669c
        _emit 0x83
        _emit 0xE1
        _emit 0x07
        // and ecx, 7
        _emit 0xBB
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 0x80
        _emit 0xD3
        _emit 0xFB
        // sar ebx, cl
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x08
        _emit 0x5C
        _emit 0x24
        _emit 0x34
        // or byte ptr [esp + 0x34], bl
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov ebx, dword ptr [esp + 0x1c]
        _emit 0x83
        _emit 0xE1
        _emit 0x07
        // and ecx, 7
        _emit 0x80
        _emit 0xF9
        _emit 0x07
        // cmp cl, 7
        _emit 0x75
        _emit 0x23
        // jne 0x8c66c7
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov edi, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x20
        // mov ebp, dword ptr [esp + 0x20]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], eax
        _emit 0x8A
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // mov al, byte ptr [esp + 0x34]
        _emit 0xC1
        _emit 0xF9
        _emit 0x03
        // sar ecx, 3
        _emit 0x88
        _emit 0x04
        _emit 0x39
        // mov byte ptr [ecx + edi], al
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // mov eax, dword ptr [esp + 0x2c]
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x34
        _emit 0x00
        // mov byte ptr [esp + 0x34], 0
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        // mov edi, dword ptr [esp + 0x10]
        _emit 0x03
        _emit 0x6C
        _emit 0x24
        _emit 0x38
        // add ebp, dword ptr [esp + 0x38]
        _emit 0x47
        // inc edi
        _emit 0x3B
        _emit 0xF8
        // cmp edi, eax
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], edi
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], ebp
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0x7C
        _emit 0x82
        // jl 0x8c6660
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov edx, dword ptr [esp + 0x14]
        _emit 0xF6
        _emit 0xC1
        _emit 0x07
        // test cl, 7
        _emit 0x74
        _emit 0x0B
        // je 0x8c66f2
        _emit 0x8A
        _emit 0x5C
        _emit 0x24
        _emit 0x34
        // mov bl, byte ptr [esp + 0x34]
        _emit 0x49
        // dec ecx
        _emit 0xC1
        _emit 0xF9
        _emit 0x03
        // sar ecx, 3
        _emit 0x88
        _emit 0x1C
        _emit 0x11
        // mov byte ptr [ecx + edx], bl
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x18
        // mov edi, dword ptr [esp + 0x18]
        _emit 0x03
        _emit 0x7C
        _emit 0x24
        _emit 0x3C
        // add edi, dword ptr [esp + 0x3c]
        _emit 0x03
        _emit 0x54
        _emit 0x24
        _emit 0x40
        // add edx, dword ptr [esp + 0x40]
        _emit 0x83
        _emit 0x6C
        _emit 0x24
        _emit 0x24
        _emit 0x01
        // sub dword ptr [esp + 0x24], 1
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], edi
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], edx
        _emit 0x0F
        _emit 0x85
        _emit 0xEF
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jne 0x8c6600
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0x5F
        // pop edi
        _emit 0x83
        _emit 0xC4
        _emit 0x20
        // add esp, 0x20
        _emit 0xC3
        // ret 
    }
}

// @ 0x008c6720  (620 bytes)
__declspec(naked) void FUN_008c6720()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x28
        // sub esp, 0x28
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x40
        // mov edi, dword ptr [esp + 0x40]
        _emit 0x0F
        _emit 0xB7
        _emit 0x47
        _emit 0x06
        // movzx eax, word ptr [edi + 6]
        _emit 0x0F
        _emit 0xB7
        _emit 0x77
        _emit 0x16
        // movzx esi, word ptr [edi + 0x16]
        _emit 0x0F
        _emit 0xB7
        _emit 0x57
        _emit 0x0A
        // movzx edx, word ptr [edi + 0xa]
        _emit 0x0F
        _emit 0xB7
        _emit 0xC0
        // movzx eax, ax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // mov dword ptr [esp + 0x30], eax
        _emit 0x0F
        _emit 0xB7
        _emit 0xDA
        // movzx ebx, dx
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], esi
        _emit 0x0F
        _emit 0xAF
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // imul eax, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0xD3
        // mov edx, ebx
        _emit 0xD1
        _emit 0xEA
        // shr edx, 1
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x34
        // mov dword ptr [esp + 0x34], edx
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xFB
        // idiv ebx
        _emit 0x0F
        _emit 0xB7
        _emit 0x4F
        _emit 0x08
        // movzx ecx, word ptr [edi + 8]
        _emit 0x0F
        _emit 0xB7
        _emit 0x77
        _emit 0x14
        // movzx esi, word ptr [edi + 0x14]
        _emit 0x0F
        _emit 0xB7
        _emit 0x6F
        _emit 0x0C
        // movzx ebp, word ptr [edi + 0xc]
        _emit 0x0F
        _emit 0xB7
        _emit 0xED
        // movzx ebp, bp
        _emit 0x8B
        _emit 0xD5
        // mov edx, ebp
        _emit 0xD1
        _emit 0xEA
        // shr edx, 1
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], edx
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], ebp
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], esi
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // mov dword ptr [esp + 0x40], eax
        _emit 0x0F
        _emit 0xB7
        _emit 0xC1
        // movzx eax, cx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], eax
        _emit 0x0F
        _emit 0xAF
        _emit 0xC6
        // imul eax, esi
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xFD
        // idiv ebp
        _emit 0x8B
        _emit 0xE8
        // mov ebp, eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // mov eax, dword ptr [esp + 0x48]
        _emit 0xA9
        _emit 0x00
        _emit 0x30
        _emit 0x00
        _emit 0x00
        // test eax, 0x3000
        _emit 0x75
        _emit 0x25
        // jne 0x8c67bb
        _emit 0xA9
        _emit 0x00
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        // test eax, 0xc000
        _emit 0x74
        _emit 0x41
        // je 0x8c67de
        _emit 0x66
        _emit 0x8B
        _emit 0x47
        _emit 0x1A
        // mov ax, word ptr [edi + 0x1a]
        _emit 0x66
        _emit 0x8B
        _emit 0x4F
        _emit 0x20
        // mov cx, word ptr [edi + 0x20]
        _emit 0x66
        _emit 0x6B
        _emit 0xC0
        _emit 0x03
        // imul ax, ax, 3
        _emit 0x66
        _emit 0x6B
        _emit 0xC9
        _emit 0x03
        // imul cx, cx, 3
        _emit 0x8D
        _emit 0x6C
        _emit 0x6D
        _emit 0x00
        // lea ebp, [ebp + ebp*2]
        _emit 0x66
        _emit 0x89
        _emit 0x47
        _emit 0x1A
        // mov word ptr [edi + 0x1a], ax
        _emit 0x66
        _emit 0x89
        _emit 0x4F
        _emit 0x20
        // mov word ptr [edi + 0x20], cx
        _emit 0xEB
        _emit 0x23
        // jmp 0x8c67de
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // mov eax, dword ptr [esp + 0x40]
        _emit 0x66
        _emit 0x8B
        _emit 0x4F
        _emit 0x1E
        // mov cx, word ptr [edi + 0x1e]
        _emit 0x8D
        _emit 0x14
        _emit 0x40
        // lea edx, [eax + eax*2]
        _emit 0x66
        _emit 0x8B
        _emit 0x47
        _emit 0x18
        // mov ax, word ptr [edi + 0x18]
        _emit 0x66
        _emit 0x6B
        _emit 0xC0
        _emit 0x03
        // imul ax, ax, 3
        _emit 0x66
        _emit 0x6B
        _emit 0xC9
        _emit 0x03
        // imul cx, cx, 3
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x40
        // mov dword ptr [esp + 0x40], edx
        _emit 0x66
        _emit 0x89
        _emit 0x47
        _emit 0x18
        // mov word ptr [edi + 0x18], ax
        _emit 0x66
        _emit 0x89
        _emit 0x4F
        _emit 0x1E
        // mov word ptr [edi + 0x1e], cx
        _emit 0x83
        _emit 0xCA
        _emit 0xFF
        // or edx, 0xffffffff
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x3B
        _emit 0xEE
        // cmp ebp, esi
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x48
        // mov dword ptr [esp + 0x48], edx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], eax
        _emit 0x7E
        _emit 0x0A
        // jle 0x8c67f9
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x48
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x48], 1
        _emit 0xEB
        _emit 0x0E
        // jmp 0x8c6807
        _emit 0x7D
        _emit 0x0C
        // jge 0x8c6807
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // mov dword ptr [esp + 0x48], eax
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x14], 1
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // mov ecx, dword ptr [esp + 0x40]
        _emit 0x39
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // cmp dword ptr [esp + 0x18], ecx
        _emit 0x75
        _emit 0x04
        // jne 0x8c6815
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], edx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], eax
        _emit 0xEB
        _emit 0x09
        // jmp 0x8c6824
        _emit 0xEB
        _emit 0x03
        // jmp 0x8c6820
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // mov ecx, dword ptr [esp + 0x40]
        _emit 0x39
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // cmp dword ptr [esp + 0x48], eax
        _emit 0x0F
        _emit 0x85
        _emit 0x82
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0x8c68b0
        _emit 0x8B
        _emit 0x57
        _emit 0x28
        // mov edx, dword ptr [edi + 0x28]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        // mov eax, dword ptr [esp + 0x3c]
        _emit 0x0F
        _emit 0xAF
        _emit 0xD5
        // imul edx, ebp
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        call FUN_008d1260
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x77
        _emit 0x28
        // mov esi, dword ptr [edi + 0x28]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], eax
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x47
        _emit 0x2C
        // mov eax, dword ptr [edi + 0x2c]
        call FUN_008c6500
        _emit 0x8B
        _emit 0x4F
        _emit 0x2C
        // mov ecx, dword ptr [edi + 0x2c]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x50
        // mov edx, dword ptr [esp + 0x50]
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        call FUN_008d1440
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // mov eax, dword ptr [esp + 0x38]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x44
        // mov ecx, dword ptr [esp + 0x44]
        _emit 0x89
        _emit 0x47
        _emit 0x2C
        // mov dword ptr [edi + 0x2c], eax
        _emit 0x0F
        _emit 0xBF
        _emit 0x47
        _emit 0x1A
        // movsx eax, word ptr [edi + 0x1a]
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x48
        // mov esi, dword ptr [esp + 0x48]
        _emit 0x0F
        _emit 0xAF
        _emit 0xC1
        // imul eax, ecx
        _emit 0x03
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // add eax, dword ptr [esp + 0x2c]
        _emit 0x83
        _emit 0xC4
        _emit 0x1C
        // add esp, 0x1c
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xFE
        // idiv esi
        _emit 0x66
        _emit 0x89
        _emit 0x6F
        _emit 0x14
        // mov word ptr [edi + 0x14], bp
        _emit 0x66
        _emit 0x89
        _emit 0x47
        _emit 0x1A
        // mov word ptr [edi + 0x1a], ax
        _emit 0x0F
        _emit 0xBF
        _emit 0x47
        _emit 0x20
        // movsx eax, word ptr [edi + 0x20]
        _emit 0x0F
        _emit 0xAF
        _emit 0xC1
        // imul eax, ecx
        _emit 0x03
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // add eax, dword ptr [esp + 0x10]
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xFE
        // idiv esi
        _emit 0x66
        _emit 0x89
        _emit 0x47
        _emit 0x20
        // mov word ptr [edi + 0x20], ax
        _emit 0x0F
        _emit 0xB7
        _emit 0x47
        _emit 0x22
        // movzx eax, word ptr [edi + 0x22]
        _emit 0x0F
        _emit 0xAF
        _emit 0xC1
        // imul eax, ecx
        _emit 0x03
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // add eax, dword ptr [esp + 0x10]
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xFE
        // idiv esi
        _emit 0x66
        _emit 0x89
        _emit 0x47
        _emit 0x22
        // mov word ptr [edi + 0x22], ax
        _emit 0xE9
        _emit 0xB3
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jmp 0x8c6963
        _emit 0x39
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // cmp dword ptr [esp + 0x14], eax
        _emit 0x0F
        _emit 0x85
        _emit 0xB1
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0x8c696b
        _emit 0x80
        _emit 0x7C
        _emit 0x24
        _emit 0x44
        _emit 0x00
        // cmp byte ptr [esp + 0x44], 0
        _emit 0x75
        _emit 0x10
        // jne 0x8c68d1
        _emit 0x8D
        _emit 0x41
        _emit 0x07
        // lea eax, [ecx + 7]
        _emit 0x99
        // cdq 
        _emit 0x83
        _emit 0xE2
        _emit 0x07
        // and edx, 7
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0xC1
        _emit 0xFE
        _emit 0x03
        // sar esi, 3
        _emit 0xEB
        _emit 0x02
        // jmp 0x8c68d3
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x3C
        // mov edx, dword ptr [esp + 0x3c]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x0F
        _emit 0xAF
        _emit 0xCD
        // imul ecx, ebp
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        call FUN_008d1260
        _emit 0x8B
        _emit 0x4F
        _emit 0x28
        // mov ecx, dword ptr [edi + 0x28]
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x4C
        // mov eax, dword ptr [esp + 0x4c]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // mov eax, dword ptr [esp + 0x24]
        _emit 0x56
        // push esi
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4F
        _emit 0x2C
        // mov ecx, dword ptr [edi + 0x2c]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x58
        // mov eax, dword ptr [esp + 0x58]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x38
        // mov dword ptr [esp + 0x38], edx
        call FUN_008c65d0
        _emit 0x8B
        _emit 0x57
        _emit 0x2C
        // mov edx, dword ptr [edi + 0x2c]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x58
        // mov eax, dword ptr [esp + 0x58]
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        call FUN_008d1440
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // mov ecx, dword ptr [esp + 0x40]
        _emit 0x0F
        _emit 0xBF
        _emit 0x47
        _emit 0x18
        // movsx eax, word ptr [edi + 0x18]
        _emit 0x66
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x64
        // mov dx, word ptr [esp + 0x64]
        _emit 0x89
        _emit 0x4F
        _emit 0x2C
        // mov dword ptr [edi + 0x2c], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x54
        // mov ecx, dword ptr [esp + 0x54]
        _emit 0x0F
        _emit 0xAF
        _emit 0xC1
        // imul eax, ecx
        _emit 0x66
        _emit 0x89
        _emit 0x57
        _emit 0x16
        // mov word ptr [edi + 0x16], dx
        _emit 0x89
        _emit 0x77
        _emit 0x28
        // mov dword ptr [edi + 0x28], esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x58
        // mov esi, dword ptr [esp + 0x58]
        _emit 0x03
        _emit 0xC6
        // add eax, esi
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xFB
        // idiv ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x24
        // add esp, 0x24
        _emit 0x66
        _emit 0x89
        _emit 0x47
        _emit 0x18
        // mov word ptr [edi + 0x18], ax
        _emit 0x0F
        _emit 0xBF
        _emit 0x47
        _emit 0x1E
        // movsx eax, word ptr [edi + 0x1e]
        _emit 0x0F
        _emit 0xAF
        _emit 0xC1
        // imul eax, ecx
        _emit 0x03
        _emit 0xC6
        // add eax, esi
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xFB
        // idiv ebx
        _emit 0x66
        _emit 0x89
        _emit 0x47
        _emit 0x1E
        // mov word ptr [edi + 0x1e], ax
        _emit 0x0F
        _emit 0xB7
        _emit 0x47
        _emit 0x1C
        // movzx eax, word ptr [edi + 0x1c]
        _emit 0x0F
        _emit 0xAF
        _emit 0xC1
        // imul eax, ecx
        _emit 0x03
        _emit 0xC6
        // add eax, esi
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xFB
        // idiv ebx
        _emit 0x66
        _emit 0x89
        _emit 0x47
        _emit 0x1C
        // mov word ptr [edi + 0x1c], ax
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x24
        // mov esi, dword ptr [esp + 0x24]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov eax, dword ptr [esp + 0x20]
        _emit 0x40
        // inc eax
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], eax
        _emit 0x0F
        _emit 0x8C
        _emit 0xA7
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jl 0x8c6820
        _emit 0x0F
        _emit 0xB7
        _emit 0x47
        _emit 0x14
        // movzx eax, word ptr [edi + 0x14]
        _emit 0x0F
        _emit 0xAF
        _emit 0x47
        _emit 0x28
        // imul eax, dword ptr [edi + 0x28]
        _emit 0x89
        _emit 0x47
        _emit 0x30
        // mov dword ptr [edi + 0x30], eax
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
        _emit 0x28
        // add esp, 0x28
        _emit 0xC3
        // ret 
    }
}

// @ 0x008c6990  (1264 bytes)
__declspec(naked) void FUN_008c6990()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x14
        // sub esp, 0x14
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x30
        // mov esi, dword ptr [esp + 0x30]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x30
        // mov edi, dword ptr [esp + 0x30]
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x03
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // add eax, dword ptr [esp + 0x38]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x50
        // push eax
        _emit 0x56
        // push esi
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ebx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], ebx
        call FUN_008cc580
        _emit 0x0F
        _emit 0xB7
        _emit 0x47
        _emit 0x12
        // movzx eax, word ptr [edi + 0x12]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x30
        // mov ebp, dword ptr [esp + 0x30]
        _emit 0x48
        // dec eax
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x89
        _emit 0x5F
        _emit 0x24
        // mov dword ptr [edi + 0x24], ebx
        _emit 0x83
        _emit 0xF8
        _emit 0x08
        // cmp eax, 8
        _emit 0x0F
        _emit 0x87
        _emit 0x40
        _emit 0x04
        _emit 0x00
        _emit 0x00
        // ja 0x8c6e0e
        _emit 0xFF
        _emit 0x24
        _emit 0x85
        _emit 0x5C
        _emit 0x6E
        _emit 0x8C
        _emit 0x00
        // jmp dword ptr [eax*4 + 0x8c6e5c]
        _emit 0x8D
        _emit 0x5F
        _emit 0x14
        // lea ebx, [edi + 0x14]
        call FUN_008c4a00
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // mov eax, dword ptr [esp + 0x44]
        _emit 0xC7
        _emit 0x47
        _emit 0x24
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x24], 1
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x0F
        _emit 0x84
        _emit 0x1E
        _emit 0x04
        _emit 0x00
        _emit 0x00
        // je 0x8c6e0e
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x3C
        // mov edx, dword ptr [esp + 0x3c]
        _emit 0x50
        // push eax
        _emit 0x0F
        _emit 0xB6
        _emit 0x47
        _emit 0x0F
        // movzx eax, byte ptr [edi + 0xf]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // lea ecx, [esp + 0x14]
        _emit 0x51
        // push ecx
        _emit 0x0F
        _emit 0xB7
        _emit 0x4F
        _emit 0x16
        // movzx ecx, word ptr [edi + 0x16]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        _emit 0x0F
        _emit 0xB7
        _emit 0x03
        // movzx eax, word ptr [ebx]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4D
        _emit 0x00
        // mov ecx, dword ptr [ebp]
        _emit 0x57
        // push edi
        call FUN_008c54d0
        _emit 0x83
        _emit 0xC4
        _emit 0x1C
        // add esp, 0x1c
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], eax
        _emit 0xE9
        _emit 0xEF
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // jmp 0x8c6e0e
        _emit 0x8D
        _emit 0x5F
        _emit 0x14
        // lea ebx, [edi + 0x14]
        call FUN_008c4a00
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // mov eax, dword ptr [esp + 0x44]
        _emit 0xC7
        _emit 0x47
        _emit 0x24
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x24], 1
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x0F
        _emit 0x84
        _emit 0xD4
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // je 0x8c6e0e
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // lea edx, [esp + 0x14]
        _emit 0x52
        // push edx
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // mov eax, dword ptr [esp + 0x48]
        _emit 0x0F
        _emit 0xB6
        _emit 0x4F
        _emit 0x0F
        // movzx ecx, byte ptr [edi + 0xf]
        _emit 0x0F
        _emit 0xB7
        _emit 0x57
        _emit 0x16
        // movzx edx, word ptr [edi + 0x16]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        _emit 0x0F
        _emit 0xB7
        _emit 0x03
        // movzx eax, word ptr [ebx]
        _emit 0x8B
        _emit 0x4D
        _emit 0x00
        // mov ecx, dword ptr [ebp]
        _emit 0x57
        // push edi
        call FUN_008c54d0
        _emit 0x83
        _emit 0xC4
        _emit 0x1C
        // add esp, 0x1c
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], eax
        _emit 0xE9
        _emit 0xA5
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // jmp 0x8c6e0e
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // mov eax, dword ptr [esp + 0x44]
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x0F
        _emit 0x84
        _emit 0x99
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // je 0x8c6e0e
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x3C
        // mov ecx, dword ptr [esp + 0x3c]
        _emit 0x0F
        _emit 0xB6
        _emit 0x57
        _emit 0x0F
        // movzx edx, byte ptr [edi + 0xf]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // lea eax, [esp + 0x14]
        _emit 0x50
        // push eax
        _emit 0x0F
        _emit 0xB7
        _emit 0x47
        _emit 0x14
        // movzx eax, word ptr [edi + 0x14]
        _emit 0x53
        // push ebx
        _emit 0x51
        // push ecx
        _emit 0x0F
        _emit 0xB7
        _emit 0x4F
        _emit 0x16
        // movzx ecx, word ptr [edi + 0x16]
        _emit 0x52
        // push edx
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4D
        _emit 0x00
        // mov ecx, dword ptr [ebp]
        _emit 0x57
        // push edi
        call FUN_008c54d0
        _emit 0x83
        _emit 0xC4
        _emit 0x1C
        // add esp, 0x1c
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], eax
        _emit 0xE9
        _emit 0x6A
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // jmp 0x8c6e0e
        _emit 0x8D
        _emit 0x5F
        _emit 0x14
        // lea ebx, [edi + 0x14]
        call FUN_008c44d0
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // mov eax, dword ptr [esp + 0x44]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x0F
        _emit 0x84
        _emit 0x56
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // je 0x8c6e0e
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // lea edx, [esp + 0x14]
        _emit 0x52
        // push edx
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xEB
        _emit 0x80
        // jmp 0x8c6a42
        _emit 0x8D
        _emit 0x5F
        _emit 0x14
        // lea ebx, [edi + 0x14]
        call FUN_008c44d0
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // mov eax, dword ptr [esp + 0x44]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x0F
        _emit 0x84
        _emit 0x38
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // je 0x8c6e0e
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x3C
        // mov ecx, dword ptr [esp + 0x3c]
        _emit 0x0F
        _emit 0xB6
        _emit 0x57
        _emit 0x0F
        // movzx edx, byte ptr [edi + 0xf]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // lea eax, [esp + 0x14]
        _emit 0x50
        // push eax
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x51
        // push ecx
        _emit 0x0F
        _emit 0xB7
        _emit 0x4F
        _emit 0x16
        // movzx ecx, word ptr [edi + 0x16]
        _emit 0x52
        // push edx
        _emit 0x51
        // push ecx
        _emit 0xE9
        _emit 0x5F
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jmp 0x8c6a51
        _emit 0x8D
        _emit 0x5F
        _emit 0x14
        // lea ebx, [edi + 0x14]
        call FUN_008c4a00
        _emit 0xC7
        _emit 0x47
        _emit 0x24
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x24], 1
        _emit 0x8B
        _emit 0x96
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x21c]
        _emit 0x42
        // inc edx
        _emit 0x52
        // push edx
        _emit 0x56
        // push esi
        call FUN_008cc580
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xEB
        _emit 0x08
        // jmp 0x8c6b1c
        _emit 0x8D
        _emit 0x5F
        _emit 0x14
        // lea ebx, [edi + 0x14]
        call FUN_008c44d0
        _emit 0x56
        // push esi
        call FUN_008cc190
        _emit 0x8B
        _emit 0x4D
        _emit 0x00
        // mov ecx, dword ptr [ebp]
        _emit 0x0F
        _emit 0xB7
        _emit 0xD8
        // movzx ebx, ax
        _emit 0x8D
        _emit 0x04
        _emit 0xDD
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea eax, [ebx*8]
        _emit 0x2B
        _emit 0xC3
        // sub eax, ebx
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x3C
        // mov dword ptr [esp + 0x3c], ebx
        call FUN_008d1260
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], eax
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x0F
        _emit 0x8E
        _emit 0xBA
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jle 0x8c6d0b
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x30
        // mov edx, dword ptr [esp + 0x30]
        _emit 0x8D
        _emit 0x58
        _emit 0x03
        // lea ebx, [eax + 3]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], ebx
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], edx
        _emit 0x56
        // push esi
        call FUN_008cc190
        _emit 0x66
        _emit 0x89
        _emit 0x43
        _emit 0xFD
        // mov word ptr [ebx - 3], ax
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x53
        // je 0x8c6bc6
        _emit 0x83
        _emit 0x7E
        _emit 0x04
        _emit 0x00
        // cmp dword ptr [esi + 4], 0
        _emit 0x74
        _emit 0x3A
        // je 0x8c6bb3
        _emit 0x8B
        _emit 0x86
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x21c]
        _emit 0x2B
        _emit 0x86
        _emit 0x18
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // sub eax, dword ptr [esi + 0x218]
        _emit 0x40
        // inc eax
        _emit 0x3B
        _emit 0x86
        _emit 0x14
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // cmp eax, dword ptr [esi + 0x214]
        _emit 0x76
        _emit 0x09
        // jbe 0x8c6b97
        _emit 0x56
        // push esi
        call FUN_008cc0b0
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x8E
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x21c]
        _emit 0x2B
        _emit 0x96
        _emit 0x18
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // sub edx, dword ptr [esi + 0x218]
        _emit 0x41
        // inc ecx
        _emit 0x0F
        _emit 0xB6
        _emit 0x44
        _emit 0x0A
        _emit 0xFF
        // movzx eax, byte ptr [edx + ecx - 1]
        _emit 0x89
        _emit 0x8E
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x21c], ecx
        _emit 0xEB
        _emit 0x54
        // jmp 0x8c6c07
        _emit 0x8B
        _emit 0x8E
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x21c]
        _emit 0x0F
        _emit 0xB6
        _emit 0x04
        _emit 0x08
        // movzx eax, byte ptr [eax + ecx]
        _emit 0x41
        // inc ecx
        _emit 0x89
        _emit 0x8E
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x21c], ecx
        _emit 0xEB
        _emit 0x41
        // jmp 0x8c6c07
        _emit 0x8B
        _emit 0x86
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x21c]
        _emit 0x8B
        _emit 0x56
        _emit 0x08
        // mov edx, dword ptr [esi + 8]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x5E
        _emit 0x0C
        // lea ebx, [esi + 0xc]
        _emit 0x8D
        _emit 0x48
        _emit 0x01
        // lea ecx, [eax + 1]
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x53
        // push ebx
        _emit 0x52
        // push edx
        _emit 0x89
        _emit 0x8E
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x21c], ecx
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x7D
        _emit 0x18
        // jge 0x8c6c04
        _emit 0x8B
        _emit 0x8E
        _emit 0x2C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x22c]
        _emit 0x68
        _emit 0x28
        _emit 0x27
        _emit 0x00
        _emit 0x00
        // push 0x2728
        _emit 0x51
        // push ecx
        call FUN_008d10c0
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0xEB
        _emit 0x03
        // jmp 0x8c6c07
        _emit 0x0F
        _emit 0xB6
        _emit 0x03
        // movzx eax, byte ptr [ebx]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x18
        // mov edx, dword ptr [esp + 0x18]
        _emit 0x88
        _emit 0x42
        _emit 0xFF
        // mov byte ptr [edx - 1], al
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x53
        // je 0x8c6c67
        _emit 0x83
        _emit 0x7E
        _emit 0x04
        _emit 0x00
        // cmp dword ptr [esi + 4], 0
        _emit 0x74
        _emit 0x3A
        // je 0x8c6c54
        _emit 0x8B
        _emit 0x86
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x21c]
        _emit 0x2B
        _emit 0x86
        _emit 0x18
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // sub eax, dword ptr [esi + 0x218]
        _emit 0x40
        // inc eax
        _emit 0x3B
        _emit 0x86
        _emit 0x14
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // cmp eax, dword ptr [esi + 0x214]
        _emit 0x76
        _emit 0x09
        // jbe 0x8c6c38
        _emit 0x56
        // push esi
        call FUN_008cc0b0
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x8B
        _emit 0x8E
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x21c]
        _emit 0x2B
        _emit 0x96
        _emit 0x18
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // sub edx, dword ptr [esi + 0x218]
        _emit 0x41
        // inc ecx
        _emit 0x0F
        _emit 0xB6
        _emit 0x44
        _emit 0x0A
        _emit 0xFF
        // movzx eax, byte ptr [edx + ecx - 1]
        _emit 0x89
        _emit 0x8E
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x21c], ecx
        _emit 0xEB
        _emit 0x54
        // jmp 0x8c6ca8
        _emit 0x8B
        _emit 0x8E
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x21c]
        _emit 0x0F
        _emit 0xB6
        _emit 0x04
        _emit 0x08
        // movzx eax, byte ptr [eax + ecx]
        _emit 0x41
        // inc ecx
        _emit 0x89
        _emit 0x8E
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x21c], ecx
        _emit 0xEB
        _emit 0x41
        // jmp 0x8c6ca8
        _emit 0x8B
        _emit 0x86
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x21c]
        _emit 0x8B
        _emit 0x56
        _emit 0x08
        // mov edx, dword ptr [esi + 8]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x5E
        _emit 0x0C
        // lea ebx, [esi + 0xc]
        _emit 0x8D
        _emit 0x48
        _emit 0x01
        // lea ecx, [eax + 1]
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x53
        // push ebx
        _emit 0x52
        // push edx
        _emit 0x89
        _emit 0x8E
        _emit 0x1C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x21c], ecx
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x7D
        _emit 0x18
        // jge 0x8c6ca5
        _emit 0x8B
        _emit 0x8E
        _emit 0x2C
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x22c]
        _emit 0x68
        _emit 0x28
        _emit 0x27
        _emit 0x00
        _emit 0x00
        // push 0x2728
        _emit 0x51
        // push ecx
        call FUN_008d10c0
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0xEB
        _emit 0x03
        // jmp 0x8c6ca8
        _emit 0x0F
        _emit 0xB6
        _emit 0x03
        // movzx eax, byte ptr [ebx]
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov ebx, dword ptr [esp + 0x18]
        _emit 0x88
        _emit 0x03
        // mov byte ptr [ebx], al
        _emit 0x83
        _emit 0xC3
        _emit 0x38
        // add ebx, 0x38
        _emit 0x83
        _emit 0x6C
        _emit 0x24
        _emit 0x20
        _emit 0x01
        // sub dword ptr [esp + 0x20], 1
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], ebx
        _emit 0x0F
        _emit 0x85
        _emit 0xA0
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jne 0x8c6b60
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x30
        // mov ebx, dword ptr [esp + 0x30]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov eax, dword ptr [esp + 0x1c]
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x7E
        _emit 0x3F
        // jle 0x8c6d0b
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x30
        // mov edx, dword ptr [esp + 0x30]
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], edx
        _emit 0xEB
        _emit 0x08
        // jmp 0x8c6ce0
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
        _emit 0x0F
        _emit 0xB7
        _emit 0x4F
        _emit 0x0C
        // movzx ecx, word ptr [edi + 0xc]
        _emit 0x0F
        _emit 0xB7
        _emit 0x57
        _emit 0x0A
        // movzx edx, word ptr [edi + 0xa]
        _emit 0x8D
        _emit 0x43
        _emit 0x04
        // lea eax, [ebx + 4]
        _emit 0x50
        // push eax
        _emit 0x0F
        _emit 0xB7
        _emit 0x03
        // movzx eax, word ptr [ebx]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // mov ecx, dword ptr [esp + 0x34]
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        _emit 0x56
        // push esi
        _emit 0x51
        // push ecx
        _emit 0x55
        // push ebp
        call FUN_008c5320
        _emit 0x83
        _emit 0xC4
        _emit 0x1C
        // add esp, 0x1c
        _emit 0x83
        _emit 0xC3
        _emit 0x38
        // add ebx, 0x38
        _emit 0x83
        _emit 0x6C
        _emit 0x24
        _emit 0x20
        _emit 0x01
        // sub dword ptr [esp + 0x20], 1
        _emit 0x75
        _emit 0xD5
        // jne 0x8c6ce0
        _emit 0x83
        _emit 0x7C
        _emit 0x24
        _emit 0x44
        _emit 0x00
        // cmp dword ptr [esp + 0x44], 0
        _emit 0x0F
        _emit 0x84
        _emit 0xF8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0x8c6e0e
        _emit 0x80
        _emit 0x7C
        _emit 0x24
        _emit 0x3C
        _emit 0x00
        // cmp byte ptr [esp + 0x3c], 0
        _emit 0x75
        _emit 0x16
        // jne 0x8c6d33
        _emit 0x0F
        _emit 0xB7
        _emit 0x47
        _emit 0x16
        // movzx eax, word ptr [edi + 0x16]
        _emit 0x83
        _emit 0xC0
        _emit 0x07
        // add eax, 7
        _emit 0x99
        // cdq 
        _emit 0x83
        _emit 0xE2
        _emit 0x07
        // and edx, 7
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0xC1
        _emit 0xF8
        _emit 0x03
        // sar eax, 3
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], eax
        _emit 0xEB
        _emit 0x0A
        // jmp 0x8c6d3d
        _emit 0x0F
        _emit 0xB7
        _emit 0x57
        _emit 0x16
        // movzx edx, word ptr [edi + 0x16]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], edx
        _emit 0x8B
        _emit 0xC2
        // mov eax, edx
        _emit 0x0F
        _emit 0xB7
        _emit 0x5F
        _emit 0x14
        // movzx ebx, word ptr [edi + 0x14]
        _emit 0x0F
        _emit 0xAF
        _emit 0xD8
        // imul ebx, eax
        _emit 0x8B
        _emit 0x45
        _emit 0x00
        // mov eax, dword ptr [ebp]
        _emit 0x53
        // push ebx
        _emit 0x50
        // push eax
        call FUN_008d1260
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], eax
        _emit 0x89
        _emit 0x5F
        _emit 0x30
        // mov dword ptr [edi + 0x30], ebx
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x7E
        _emit 0x10
        // jle 0x8c6d6c
        _emit 0x53
        // push ebx
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x50
        // push eax
        call FUN_011e073e
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov eax, dword ptr [esp + 0x20]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x89
        _emit 0x47
        _emit 0x2C
        // mov dword ptr [edi + 0x2c], eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // mov eax, dword ptr [esp + 0x40]
        _emit 0x40
        // inc eax
        _emit 0x83
        _emit 0xF8
        _emit 0x10
        // cmp eax, 0x10
        _emit 0x89
        _emit 0x4F
        _emit 0x28
        // mov dword ptr [edi + 0x28], ecx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // mov dword ptr [esp + 0x40], eax
        _emit 0x7F
        _emit 0x79
        // jg 0x8c6dfd
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // mov eax, dword ptr [esp + 0x30]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x7E
        _emit 0x71
        // jle 0x8c6dfd
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov ebx, dword ptr [esp + 0x1c]
        _emit 0x83
        _emit 0xC3
        _emit 0x04
        // add ebx, 4
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // mov dword ptr [esp + 0x30], eax
        _emit 0xEB
        _emit 0x07
        // jmp 0x8c6da0
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x48
        // mov edx, dword ptr [esp + 0x48]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // mov eax, dword ptr [esp + 0x44]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // mov ecx, dword ptr [esp + 0x40]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x40
        // mov edx, dword ptr [esp + 0x40]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // mov eax, dword ptr [esp + 0x40]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x38
        // mov ecx, dword ptr [esp + 0x38]
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        _emit 0x56
        // push esi
        _emit 0x53
        // push ebx
        _emit 0x51
        // push ecx
        _emit 0x55
        // push ebp
        _emit 0xE8
        _emit 0xCA
        _emit 0xFB
        _emit 0xFF
        _emit 0xFF
        // call 0x8c6990
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x60
        // mov edx, dword ptr [esp + 0x60]
        _emit 0x0F
        _emit 0xB6
        _emit 0x43
        _emit 0xFF
        // movzx eax, byte ptr [ebx - 1]
        _emit 0x52
        // push edx
        _emit 0x8A
        _emit 0x53
        _emit 0xFE
        // mov dl, byte ptr [ebx - 2]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0x8B
        _emit 0xC7
        // mov eax, edi
        call FUN_008c63a0
        _emit 0x8B
        _emit 0x4B
        _emit 0x2C
        // mov ecx, dword ptr [ebx + 0x2c]
        _emit 0x8B
        _emit 0x55
        _emit 0x00
        // mov edx, dword ptr [ebp]
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        call FUN_008d1440
        _emit 0xC7
        _emit 0x43
        _emit 0x2C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx + 0x2c], 0
        _emit 0x83
        _emit 0xC4
        _emit 0x34
        // add esp, 0x34
        _emit 0x83
        _emit 0xC3
        _emit 0x38
        // add ebx, 0x38
        _emit 0x83
        _emit 0x6C
        _emit 0x24
        _emit 0x30
        _emit 0x01
        // sub dword ptr [esp + 0x30], 1
        _emit 0x75
        _emit 0xA3
        // jne 0x8c6da0
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov eax, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x4D
        _emit 0x00
        // mov ecx, dword ptr [ebp]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        call FUN_008d1440
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov edx, dword ptr [esp + 0x14]
        _emit 0x89
        _emit 0x47
        _emit 0x28
        // mov dword ptr [edi + 0x28], eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        // mov eax, dword ptr [esp + 0x3c]
        _emit 0x89
        _emit 0x57
        _emit 0x2C
        // mov dword ptr [edi + 0x2c], edx
        _emit 0x3C
        _emit 0xFF
        // cmp al, 0xff
        _emit 0x74
        _emit 0x2F
        // je 0x8c6e53
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // mov ecx, dword ptr [esp + 0x48]
        _emit 0xF7
        _emit 0xC1
        _emit 0x00
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        // test ecx, 0xf000
        _emit 0x75
        _emit 0x14
        // jne 0x8c6e44
        _emit 0x66
        _emit 0x8B
        _emit 0x57
        _emit 0x0A
        // mov dx, word ptr [edi + 0xa]
        _emit 0x66
        _emit 0x3B
        _emit 0x57
        _emit 0x06
        // cmp dx, word ptr [edi + 6]
        _emit 0x75
        _emit 0x0A
        // jne 0x8c6e44
        _emit 0x66
        _emit 0x8B
        _emit 0x57
        _emit 0x0C
        // mov dx, word ptr [edi + 0xc]
        _emit 0x66
        _emit 0x3B
        _emit 0x57
        _emit 0x08
        // cmp dx, word ptr [edi + 8]
        _emit 0x74
        _emit 0x0F
        // je 0x8c6e53
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x45
        _emit 0x00
        // mov eax, dword ptr [ebp]
        _emit 0x57
        // push edi
        _emit 0x50
        // push eax
        call FUN_008c6720
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
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
        _emit 0x14
        // add esp, 0x14
        _emit 0xC3
        // ret 
        _emit 0x90
        // nop 
        _emit 0xD5
        _emit 0x69
        // aad 0x69
        _emit 0x8C
        _emit 0x00
        // mov word ptr [eax], es
        _emit 0x1F
        // pop ds
        _emit 0x6A
        _emit 0x8C
        // push -0x74
        _emit 0x00
        _emit 0x0E
        // add byte ptr [esi], cl
        _emit 0x6E
        // outsb dx, byte ptr [esi]
        _emit 0x8C
        _emit 0x00
        // mov word ptr [eax], es
        _emit 0x0E
        // push cs
        _emit 0x6E
        // outsb dx, byte ptr [esi]
        _emit 0x8C
        _emit 0x00
        // mov word ptr [eax], es
        _emit 0x69
        _emit 0x6A
        _emit 0x8C
        _emit 0x00
        _emit 0xA4
        _emit 0x6A
        _emit 0x8C
        // imul ebp, dword ptr [edx - 0x74], 0x8c6aa400
        _emit 0x00
        _emit 0xC2
        // add dl, al
        _emit 0x6A
        _emit 0x8C
        // push -0x74
        _emit 0x00
        _emit 0xF2
        // add dl, dh
        _emit 0x6A
        _emit 0x8C
        // push -0x74
        _emit 0x00
        _emit 0x14
        _emit 0x6B
        // add byte ptr [ebx + ebp*2], dl
        _emit 0x8C
        _emit 0x00
        // mov word ptr [eax], es
    }
}
