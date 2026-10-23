// Slice s0115de20: Spore/RenderWare engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_0112c820();
extern "C" void FUN_0112c850();
extern "C" void FUN_0115dc10();
extern "C" void FUN_0115ddd0();
extern "C" void FUN_0115f190();
extern "C" void FUN_0115ffe0();
extern "C" void FUN_011e073e();
extern "C" void FUN_011e0744();

// @ 0x0115de20  (1290 bytes)
__declspec(naked) void FUN_0115de20()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x0C
        // sub esp, 0xc
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x80
        _emit 0xBE
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [esi + 0x90], 0
        _emit 0x57
        // push edi
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ebp
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ebp
        _emit 0x75
        _emit 0x62
        // jne 0x115de9e
        _emit 0x8B
        _emit 0x46
        _emit 0x74
        // mov eax, dword ptr [esi + 0x74]
        _emit 0x0F
        _emit 0xAF
        _emit 0x46
        _emit 0x48
        // imul eax, dword ptr [esi + 0x48]
        _emit 0x8B
        _emit 0x4E
        _emit 0x08
        // mov ecx, dword ptr [esi + 8]
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x50
        // push eax
        _emit 0x55
        // push ebp
        _emit 0x51
        // push ecx
        call FUN_011e073e
        _emit 0x8B
        _emit 0x56
        _emit 0x24
        // mov edx, dword ptr [esi + 0x24]
        _emit 0x0F
        _emit 0xAF
        _emit 0x56
        _emit 0x78
        // imul edx, dword ptr [esi + 0x78]
        _emit 0x8B
        _emit 0x46
        _emit 0x14
        // mov eax, dword ptr [esi + 0x14]
        _emit 0x03
        _emit 0xD2
        // add edx, edx
        _emit 0x03
        _emit 0xD2
        // add edx, edx
        _emit 0x52
        // push edx
        _emit 0x55
        // push ebp
        _emit 0x50
        // push eax
        call FUN_011e073e
        _emit 0x8B
        _emit 0x4E
        _emit 0x78
        // mov ecx, dword ptr [esi + 0x78]
        _emit 0x0F
        _emit 0xAF
        _emit 0x4E
        _emit 0x50
        // imul ecx, dword ptr [esi + 0x50]
        _emit 0x8B
        _emit 0x56
        _emit 0x18
        // mov edx, dword ptr [esi + 0x18]
        _emit 0x03
        _emit 0xC9
        // add ecx, ecx
        _emit 0x03
        _emit 0xC9
        // add ecx, ecx
        _emit 0x51
        // push ecx
        _emit 0x55
        // push ebp
        _emit 0x52
        // push edx
        call FUN_011e073e
        _emit 0x8B
        _emit 0x46
        _emit 0x78
        // mov eax, dword ptr [esi + 0x78]
        _emit 0x0F
        _emit 0xAF
        _emit 0x46
        _emit 0x50
        // imul eax, dword ptr [esi + 0x50]
        _emit 0x8B
        _emit 0x4E
        _emit 0x1C
        // mov ecx, dword ptr [esi + 0x1c]
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x50
        // push eax
        _emit 0x55
        // push ebp
        _emit 0x51
        // push ecx
        call FUN_011e073e
        _emit 0x83
        _emit 0xC4
        _emit 0x30
        // add esp, 0x30
        _emit 0xC6
        _emit 0x86
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x01
        // mov byte ptr [esi + 0x90], 1
        _emit 0x33
        _emit 0xFF
        // xor edi, edi
        _emit 0x39
        _emit 0x6E
        _emit 0x74
        // cmp dword ptr [esi + 0x74], ebp
        _emit 0x76
        _emit 0x4B
        // jbe 0x115def0
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // mov ebx, dword ptr [esp + 0x20]
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0x0F
        _emit 0xB7
        _emit 0x4B
        _emit 0x0E
        // movzx ecx, word ptr [ebx + 0xe]
        _emit 0x8B
        _emit 0x46
        _emit 0x38
        // mov eax, dword ptr [esi + 0x38]
        _emit 0x0F
        _emit 0xAF
        _emit 0xCF
        // imul ecx, edi
        _emit 0x8D
        _emit 0x14
        _emit 0x85
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea edx, [eax*4]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0x53
        _emit 0x04
        // mov edx, dword ptr [ebx + 4]
        _emit 0x8D
        _emit 0x0C
        _emit 0x8A
        // lea ecx, [edx + ecx*4]
        _emit 0x8B
        _emit 0x56
        _emit 0x5C
        // mov edx, dword ptr [esi + 0x5c]
        _emit 0x0F
        _emit 0xAF
        _emit 0xD0
        // imul edx, eax
        _emit 0x8B
        _emit 0x46
        _emit 0x48
        // mov eax, dword ptr [esi + 0x48]
        _emit 0x0F
        _emit 0xAF
        _emit 0xC7
        // imul eax, edi
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4E
        _emit 0x68
        // mov ecx, dword ptr [esi + 0x68]
        _emit 0x03
        _emit 0xD0
        // add edx, eax
        _emit 0x8B
        _emit 0x44
        _emit 0x8E
        _emit 0x04
        // mov eax, dword ptr [esi + ecx*4 + 4]
        _emit 0x8D
        _emit 0x0C
        _emit 0x90
        // lea ecx, [eax + edx*4]
        _emit 0x51
        // push ecx
        call FUN_011e0744
        _emit 0x47
        // inc edi
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x3B
        _emit 0x7E
        _emit 0x74
        // cmp edi, dword ptr [esi + 0x74]
        _emit 0x72
        _emit 0xC0
        // jb 0x115deb0
        _emit 0x8B
        _emit 0x46
        _emit 0x5C
        // mov eax, dword ptr [esi + 0x5c]
        _emit 0x8B
        _emit 0x56
        _emit 0x7C
        // mov edx, dword ptr [esi + 0x7c]
        _emit 0x8D
        _emit 0x04
        _emit 0x40
        // lea eax, [eax + eax*2]
        _emit 0x8B
        _emit 0x44
        _emit 0x82
        _emit 0x04
        // mov eax, dword ptr [edx + eax*4 + 4]
        _emit 0x3B
        _emit 0xC5
        // cmp eax, ebp
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], edx
        _emit 0x0F
        _emit 0x8E
        _emit 0x75
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jle 0x115e07e
        _emit 0x8B
        _emit 0xBE
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edi, dword ptr [esi + 0x80]
        _emit 0x8B
        _emit 0x5E
        _emit 0x6C
        // mov ebx, dword ptr [esi + 0x6c]
        _emit 0x33
        _emit 0xC9
        // xor ecx, ecx
        _emit 0x39
        _emit 0x6E
        _emit 0x68
        // cmp dword ptr [esi + 0x68], ebp
        _emit 0x8D
        _emit 0x14
        _emit 0x07
        // lea edx, [edi + eax]
        _emit 0x0F
        _emit 0x94
        _emit 0xC1
        // sete cl
        _emit 0x3B
        _emit 0xFA
        // cmp edi, edx
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], ecx
        _emit 0x7D
        _emit 0x71
        // jge 0x115df96
        _emit 0x8B
        _emit 0x46
        _emit 0x48
        // mov eax, dword ptr [esi + 0x48]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x0F
        _emit 0xAF
        _emit 0xC7
        // imul eax, edi
        _emit 0x8B
        _emit 0x54
        _emit 0x8E
        _emit 0x04
        // mov edx, dword ptr [esi + ecx*4 + 4]
        _emit 0x8B
        _emit 0x4E
        _emit 0x40
        // mov ecx, dword ptr [esi + 0x40]
        _emit 0x8D
        _emit 0x2C
        _emit 0x82
        // lea ebp, [edx + eax*4]
        _emit 0x8B
        _emit 0x46
        _emit 0x3C
        // mov eax, dword ptr [esi + 0x3c]
        _emit 0x2B
        _emit 0xC8
        // sub ecx, eax
        _emit 0x03
        _emit 0xC9
        // add ecx, ecx
        _emit 0x03
        _emit 0xC9
        // add ecx, ecx
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x54
        _emit 0x85
        _emit 0x00
        // lea edx, [ebp + eax*4]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x52
        // push edx
        call FUN_011e073e
        _emit 0x55
        // push ebp
        _emit 0x53
        // push ebx
        call FUN_0115f190
        _emit 0x8B
        _emit 0x4E
        _emit 0x74
        // mov ecx, dword ptr [esi + 0x74]
        _emit 0x0F
        _emit 0xAF
        _emit 0x4E
        _emit 0x30
        // imul ecx, dword ptr [esi + 0x30]
        _emit 0x8B
        _emit 0x46
        _emit 0x44
        // mov eax, dword ptr [esi + 0x44]
        _emit 0x8B
        _emit 0x56
        _emit 0x0C
        // mov edx, dword ptr [esi + 0xc]
        _emit 0x03
        _emit 0xCF
        // add ecx, edi
        _emit 0x0F
        _emit 0xAF
        _emit 0x4E
        _emit 0x4C
        // imul ecx, dword ptr [esi + 0x4c]
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x04
        _emit 0x8A
        // lea eax, [edx + ecx*4]
        _emit 0x55
        // push ebp
        _emit 0x50
        // push eax
        call FUN_011e0744
        _emit 0x8B
        _emit 0x46
        _emit 0x5C
        // mov eax, dword ptr [esi + 0x5c]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x40
        // mov edx, dword ptr [esp + 0x40]
        _emit 0x8D
        _emit 0x0C
        _emit 0x40
        // lea ecx, [eax + eax*2]
        _emit 0x8B
        _emit 0x44
        _emit 0x8A
        _emit 0x04
        // mov eax, dword ptr [edx + ecx*4 + 4]
        _emit 0x03
        _emit 0x86
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add eax, dword ptr [esi + 0x80]
        _emit 0x47
        // inc edi
        _emit 0x83
        _emit 0xC4
        _emit 0x20
        // add esp, 0x20
        _emit 0x3B
        _emit 0xF8
        // cmp edi, eax
        _emit 0x7C
        _emit 0x91
        // jl 0x115df25
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0x8B
        _emit 0x46
        _emit 0x5C
        // mov eax, dword ptr [esi + 0x5c]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov edx, dword ptr [esp + 0x20]
        _emit 0x8D
        _emit 0x0C
        _emit 0x40
        // lea ecx, [eax + eax*2]
        _emit 0x8B
        _emit 0x44
        _emit 0x8A
        _emit 0x04
        // mov eax, dword ptr [edx + ecx*4 + 4]
        _emit 0x01
        _emit 0x86
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add dword ptr [esi + 0x80], eax
        _emit 0x8B
        _emit 0x86
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x80]
        _emit 0x39
        _emit 0x46
        _emit 0x74
        // cmp dword ptr [esi + 0x74], eax
        _emit 0x0F
        _emit 0x85
        _emit 0xC5
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0x115e07e
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x2C
        // mov ebp, dword ptr [esp + 0x2c]
        _emit 0x8B
        _emit 0x45
        _emit 0x00
        // mov eax, dword ptr [ebp]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x0F
        _emit 0x84
        _emit 0xAA
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0x115e072
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xC1
        _emit 0xF9
        _emit 0x18
        // sar ecx, 0x18
        _emit 0x88
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov byte ptr [esp + 0x2c], cl
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xC1
        _emit 0xFA
        _emit 0x10
        // sar edx, 0x10
        _emit 0xC1
        _emit 0xF9
        _emit 0x08
        // sar ecx, 8
        _emit 0x88
        _emit 0x54
        _emit 0x24
        _emit 0x2D
        // mov byte ptr [esp + 0x2d], dl
        _emit 0x88
        _emit 0x4C
        _emit 0x24
        _emit 0x2E
        // mov byte ptr [esp + 0x2e], cl
        _emit 0x88
        _emit 0x44
        _emit 0x24
        _emit 0x2F
        // mov byte ptr [esp + 0x2f], al
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x2C
        // mov edi, dword ptr [esp + 0x2c]
        _emit 0xF7
        _emit 0xDF
        // neg edi
        _emit 0x3B
        _emit 0x7E
        _emit 0x2C
        // cmp edi, dword ptr [esi + 0x2c]
        _emit 0x7D
        _emit 0x08
        // jge 0x115dffa
        _emit 0x3B
        _emit 0xBE
        _emit 0x8C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp edi, dword ptr [esi + 0x8c]
        _emit 0x74
        _emit 0x05
        // je 0x115dfff
        _emit 0x83
        _emit 0xFF
        _emit 0xFF
        // cmp edi, -1
        _emit 0x75
        _emit 0x39
        // jne 0x115e038
        _emit 0x8B
        _emit 0x4E
        _emit 0x28
        // mov ecx, dword ptr [esi + 0x28]
        _emit 0x8B
        _emit 0x46
        _emit 0x58
        // mov eax, dword ptr [esi + 0x58]
        _emit 0x8B
        _emit 0xD1
        // mov edx, ecx
        _emit 0x0F
        _emit 0xAF
        _emit 0xD0
        // imul edx, eax
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0x96
        _emit 0x8C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x8c]
        _emit 0x0F
        _emit 0xAF
        _emit 0xD1
        // imul edx, ecx
        _emit 0x0F
        _emit 0xAF
        _emit 0xD0
        // imul edx, eax
        _emit 0x8B
        _emit 0x46
        _emit 0x10
        // mov eax, dword ptr [esi + 0x10]
        _emit 0x8D
        _emit 0x0C
        _emit 0x50
        // lea ecx, [eax + edx*2]
        _emit 0x51
        // push ecx
        call FUN_0115ddd0
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x83
        _emit 0xFF
        _emit 0xFF
        // cmp edi, -1
        _emit 0x75
        _emit 0x0D
        // jne 0x115e038
        _emit 0xB0
        _emit 0xFF
        // mov al, 0xff
        _emit 0x88
        _emit 0x45
        _emit 0x00
        // mov byte ptr [ebp], al
        _emit 0x88
        _emit 0x45
        _emit 0x01
        // mov byte ptr [ebp + 1], al
        _emit 0x88
        _emit 0x45
        _emit 0x02
        // mov byte ptr [ebp + 2], al
        _emit 0xEB
        _emit 0x37
        // jmp 0x115e06f
        _emit 0x8B
        _emit 0x56
        _emit 0x2C
        // mov edx, dword ptr [esi + 0x2c]
        _emit 0x4A
        // dec edx
        _emit 0x3B
        _emit 0xFA
        // cmp edi, edx
        _emit 0x75
        _emit 0x12
        // jne 0x115e052
        _emit 0xC6
        _emit 0x45
        _emit 0x00
        _emit 0x00
        // mov byte ptr [ebp], 0
        _emit 0xC6
        _emit 0x45
        _emit 0x01
        _emit 0x00
        // mov byte ptr [ebp + 1], 0
        _emit 0xC6
        _emit 0x45
        _emit 0x02
        _emit 0x00
        // mov byte ptr [ebp + 2], 0
        _emit 0xC6
        _emit 0x45
        _emit 0x03
        _emit 0x00
        // mov byte ptr [ebp + 3], 0
        _emit 0xEB
        _emit 0x20
        // jmp 0x115e072
        _emit 0x47
        // inc edi
        _emit 0xF7
        _emit 0xDF
        // neg edi
        _emit 0x8B
        _emit 0xC7
        // mov eax, edi
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xC1
        _emit 0xF9
        _emit 0x18
        // sar ecx, 0x18
        _emit 0x88
        _emit 0x4D
        _emit 0x00
        // mov byte ptr [ebp], cl
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0xC1
        _emit 0xFA
        _emit 0x10
        // sar edx, 0x10
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xC1
        _emit 0xF9
        _emit 0x08
        // sar ecx, 8
        _emit 0x88
        _emit 0x55
        _emit 0x01
        // mov byte ptr [ebp + 1], dl
        _emit 0x88
        _emit 0x4D
        _emit 0x02
        // mov byte ptr [ebp + 2], cl
        _emit 0x88
        _emit 0x45
        _emit 0x03
        // mov byte ptr [ebp + 3], al
        _emit 0xFF
        _emit 0x86
        _emit 0x8C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // inc dword ptr [esi + 0x8c]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov edx, dword ptr [esp + 0x20]
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0x8B
        _emit 0x46
        _emit 0x5C
        // mov eax, dword ptr [esi + 0x5c]
        _emit 0x8D
        _emit 0x0C
        _emit 0x40
        // lea ecx, [eax + eax*2]
        _emit 0x39
        _emit 0x2C
        _emit 0x8A
        // cmp dword ptr [edx + ecx*4], ebp
        _emit 0x8D
        _emit 0x0C
        _emit 0x8A
        // lea ecx, [edx + ecx*4]
        _emit 0x0F
        _emit 0x8E
        _emit 0x02
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jle 0x115e192
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x39
        _emit 0x6E
        _emit 0x78
        // cmp dword ptr [esi + 0x78], ebp
        _emit 0x0F
        _emit 0x8E
        _emit 0xE6
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jle 0x115e181
        _emit 0xEB
        _emit 0x03
        // jmp 0x115e0a0
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0x8B
        _emit 0x46
        _emit 0x24
        // mov eax, dword ptr [esi + 0x24]
        _emit 0x8B
        _emit 0x4E
        _emit 0x14
        // mov ecx, dword ptr [esi + 0x14]
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0x0F
        _emit 0xAF
        _emit 0xD3
        // imul edx, ebx
        _emit 0x8D
        _emit 0x0C
        _emit 0x91
        // lea ecx, [ecx + edx*4]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], ecx
        _emit 0x39
        _emit 0xAE
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp dword ptr [esi + 0x84], ebp
        _emit 0x75
        _emit 0x12
        // jne 0x115e0cc
        _emit 0x8D
        _emit 0x14
        _emit 0x85
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea edx, [eax*4]
        _emit 0x52
        // push edx
        _emit 0x55
        // push ebp
        _emit 0x51
        // push ecx
        call FUN_011e073e
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x8B
        _emit 0x46
        _emit 0x5C
        // mov eax, dword ptr [esi + 0x5c]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0xBE
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edi, dword ptr [esi + 0x84]
        _emit 0x8D
        _emit 0x04
        _emit 0x40
        // lea eax, [eax + eax*2]
        _emit 0x8B
        _emit 0x14
        _emit 0x81
        // mov edx, dword ptr [ecx + eax*4]
        _emit 0x8B
        _emit 0x8E
        _emit 0x8C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x8c]
        _emit 0x8D
        _emit 0x04
        _emit 0x3A
        // lea eax, [edx + edi]
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x8B
        _emit 0xE8
        // mov ebp, eax
        _emit 0x7C
        _emit 0x02
        // jl 0x115e0f0
        _emit 0x8B
        _emit 0xE9
        // mov ebp, ecx
        _emit 0x3B
        _emit 0xFD
        // cmp edi, ebp
        _emit 0x7D
        _emit 0x7D
        // jge 0x115e171
        _emit 0x8B
        _emit 0x4E
        _emit 0x30
        // mov ecx, dword ptr [esi + 0x30]
        _emit 0x2B
        _emit 0xCF
        // sub ecx, edi
        _emit 0x79
        _emit 0x03
        // jns 0x115e0fe
        _emit 0x03
        _emit 0x4E
        _emit 0x2C
        // add ecx, dword ptr [esi + 0x2c]
        _emit 0x8B
        _emit 0x46
        _emit 0x28
        // mov eax, dword ptr [esi + 0x28]
        _emit 0x83
        _emit 0xF8
        _emit 0x01
        // cmp eax, 1
        _emit 0x75
        _emit 0x0C
        // jne 0x115e112
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x75
        _emit 0x1B
        // jne 0x115e125
        _emit 0x8B
        _emit 0x46
        _emit 0x58
        // mov eax, dword ptr [esi + 0x58]
        _emit 0x0F
        _emit 0xAF
        _emit 0xC7
        // imul eax, edi
        _emit 0xEB
        _emit 0x09
        // jmp 0x115e11b
        _emit 0x0F
        _emit 0xAF
        _emit 0xC7
        // imul eax, edi
        _emit 0x03
        _emit 0xC3
        // add eax, ebx
        _emit 0x0F
        _emit 0xAF
        _emit 0x46
        _emit 0x58
        // imul eax, dword ptr [esi + 0x58]
        _emit 0x8B
        _emit 0x56
        _emit 0x10
        // mov edx, dword ptr [esi + 0x10]
        _emit 0x8D
        _emit 0x04
        _emit 0x42
        // lea eax, [edx + eax*2]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], eax
        _emit 0x8B
        _emit 0x46
        _emit 0x74
        // mov eax, dword ptr [esi + 0x74]
        _emit 0x83
        _emit 0xF8
        _emit 0x01
        // cmp eax, 1
        _emit 0x75
        _emit 0x16
        // jne 0x115e143
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x75
        _emit 0x25
        // jne 0x115e156
        _emit 0x8B
        _emit 0x56
        _emit 0x4C
        // mov edx, dword ptr [esi + 0x4c]
        _emit 0x8B
        _emit 0x46
        _emit 0x0C
        // mov eax, dword ptr [esi + 0xc]
        _emit 0x0F
        _emit 0xAF
        _emit 0xD1
        // imul edx, ecx
        _emit 0x8D
        _emit 0x0C
        _emit 0x90
        // lea ecx, [eax + edx*4]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ecx
        _emit 0xEB
        _emit 0x13
        // jmp 0x115e156
        _emit 0x8B
        _emit 0x56
        _emit 0x0C
        // mov edx, dword ptr [esi + 0xc]
        _emit 0x0F
        _emit 0xAF
        _emit 0xC1
        // imul eax, ecx
        _emit 0x03
        _emit 0xC3
        // add eax, ebx
        _emit 0x0F
        _emit 0xAF
        _emit 0x46
        _emit 0x4C
        // imul eax, dword ptr [esi + 0x4c]
        _emit 0x8D
        _emit 0x04
        _emit 0x82
        // lea eax, [edx + eax*4]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], eax
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov ecx, dword ptr [esp + 0x2c]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov edx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_0115dc10
        _emit 0x47
        // inc edi
        _emit 0x3B
        _emit 0xFD
        // cmp edi, ebp
        _emit 0x7C
        _emit 0x83
        // jl 0x115e0f4
        _emit 0x43
        // inc ebx
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0x3B
        _emit 0x5E
        _emit 0x78
        // cmp ebx, dword ptr [esi + 0x78]
        _emit 0x0F
        _emit 0x8C
        _emit 0x23
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jl 0x115e0a0
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov edx, dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0x46
        _emit 0x5C
        // mov eax, dword ptr [esi + 0x5c]
        _emit 0x8D
        _emit 0x0C
        _emit 0x40
        // lea ecx, [eax + eax*2]
        _emit 0x8D
        _emit 0x0C
        _emit 0x8A
        // lea ecx, [edx + ecx*4]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x01
        _emit 0x96
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add dword ptr [esi + 0x84], edx
        _emit 0x8B
        _emit 0x49
        _emit 0x08
        // mov ecx, dword ptr [ecx + 8]
        _emit 0x3B
        _emit 0xCD
        // cmp ecx, ebp
        _emit 0x7E
        _emit 0x5A
        // jle 0x115e1f3
        _emit 0x8B
        _emit 0xBE
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edi, dword ptr [esi + 0x88]
        _emit 0x8B
        _emit 0x5E
        _emit 0x6C
        // mov ebx, dword ptr [esi + 0x6c]
        _emit 0x8D
        _emit 0x04
        _emit 0x0F
        // lea eax, [edi + ecx]
        _emit 0x3B
        _emit 0xF8
        // cmp edi, eax
        _emit 0x7D
        _emit 0x36
        // jge 0x115e1df
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0x8B
        _emit 0x4E
        _emit 0x24
        // mov ecx, dword ptr [esi + 0x24]
        _emit 0x8B
        _emit 0x56
        _emit 0x14
        // mov edx, dword ptr [esi + 0x14]
        _emit 0x0F
        _emit 0xAF
        _emit 0xCF
        // imul ecx, edi
        _emit 0x8D
        _emit 0x04
        _emit 0x8A
        // lea eax, [edx + ecx*4]
        _emit 0x50
        // push eax
        _emit 0x53
        // push ebx
        call FUN_0115ffe0
        _emit 0x8B
        _emit 0x46
        _emit 0x5C
        // mov eax, dword ptr [esi + 0x5c]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x28
        // mov edx, dword ptr [esp + 0x28]
        _emit 0x8D
        _emit 0x0C
        _emit 0x40
        // lea ecx, [eax + eax*2]
        _emit 0x8B
        _emit 0x44
        _emit 0x8A
        _emit 0x08
        // mov eax, dword ptr [edx + ecx*4 + 8]
        _emit 0x03
        _emit 0x86
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add eax, dword ptr [esi + 0x88]
        _emit 0x47
        // inc edi
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x3B
        _emit 0xF8
        // cmp edi, eax
        _emit 0x7C
        _emit 0xD1
        // jl 0x115e1b0
        _emit 0x8B
        _emit 0x46
        _emit 0x5C
        // mov eax, dword ptr [esi + 0x5c]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov edx, dword ptr [esp + 0x20]
        _emit 0x8D
        _emit 0x0C
        _emit 0x40
        // lea ecx, [eax + eax*2]
        _emit 0x8B
        _emit 0x4C
        _emit 0x8A
        _emit 0x08
        // mov ecx, dword ptr [edx + ecx*4 + 8]
        _emit 0x01
        _emit 0x8E
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add dword ptr [esi + 0x88], ecx
        _emit 0x8B
        _emit 0x56
        _emit 0x54
        // mov edx, dword ptr [esi + 0x54]
        _emit 0x4A
        // dec edx
        _emit 0x3B
        _emit 0xC2
        // cmp eax, edx
        _emit 0x0F
        _emit 0x8C
        _emit 0xCF
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jl 0x115e2ce
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x39
        _emit 0x6E
        _emit 0x64
        // cmp dword ptr [esi + 0x64], ebp
        _emit 0x0F
        _emit 0x94
        _emit 0xC0
        // sete al
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x39
        _emit 0x6E
        _emit 0x78
        // cmp dword ptr [esi + 0x78], ebp
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], ebx
        _emit 0x7E
        _emit 0x7F
        // jle 0x115e291
        _emit 0x8B
        _emit 0x44
        _emit 0x86
        _emit 0x18
        // mov eax, dword ptr [esi + eax*4 + 0x18]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], eax
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebx, [ebx]
        _emit 0x8B
        _emit 0x6E
        _emit 0x3C
        // mov ebp, dword ptr [esi + 0x3c]
        _emit 0x8B
        _emit 0x4E
        _emit 0x64
        // mov ecx, dword ptr [esi + 0x64]
        _emit 0x8B
        _emit 0x54
        _emit 0x8E
        _emit 0x18
        // mov edx, dword ptr [esi + ecx*4 + 0x18]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x7E
        _emit 0x14
        // mov edi, dword ptr [esi + 0x14]
        _emit 0x8B
        _emit 0xC5
        // mov eax, ebp
        _emit 0x0F
        _emit 0xAF
        _emit 0xC3
        // imul eax, ebx
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xD0
        // add edx, eax
        _emit 0x03
        _emit 0xC1
        // add eax, ecx
        _emit 0x8B
        _emit 0x4E
        _emit 0x24
        // mov ecx, dword ptr [esi + 0x24]
        _emit 0x0F
        _emit 0xAF
        _emit 0xCB
        // imul ecx, ebx
        _emit 0x8D
        _emit 0x3C
        _emit 0x8F
        // lea edi, [edi + ecx*4]
        _emit 0x33
        _emit 0xC9
        // xor ecx, ecx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], eax
        _emit 0x85
        _emit 0xED
        // test ebp, ebp
        _emit 0x7E
        _emit 0x34
        // jle 0x115e285
        _emit 0x8B
        _emit 0xEF
        // mov ebp, edi
        _emit 0x2B
        _emit 0xE8
        // sub ebp, eax
        _emit 0x2B
        _emit 0xD0
        // sub edx, eax
        _emit 0xEB
        _emit 0x07
        // jmp 0x115e260
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x04
        _emit 0x28
        // movss xmm0, dword ptr [eax + ebp]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x00
        // addss xmm0, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x00
        // movss dword ptr [eax], xmm0
        _emit 0x8B
        _emit 0x5E
        _emit 0x3C
        // mov ebx, dword ptr [esi + 0x3c]
        _emit 0x03
        _emit 0xD9
        // add ebx, ecx
        _emit 0xD9
        _emit 0x04
        _emit 0x9F
        // fld dword ptr [edi + ebx*4]
        _emit 0x41
        // inc ecx
        _emit 0xD9
        _emit 0x1C
        _emit 0x02
        // fstp dword ptr [edx + eax]
        _emit 0x83
        _emit 0xC0
        _emit 0x04
        // add eax, 4
        _emit 0x3B
        _emit 0x4E
        _emit 0x3C
        // cmp ecx, dword ptr [esi + 0x3c]
        _emit 0x7C
        _emit 0xDF
        // jl 0x115e260
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x2C
        // mov ebx, dword ptr [esp + 0x2c]
        _emit 0x43
        // inc ebx
        _emit 0x3B
        _emit 0x5E
        _emit 0x78
        // cmp ebx, dword ptr [esi + 0x78]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], ebx
        _emit 0x7C
        _emit 0x91
        // jl 0x115e220
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0xB9
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, 1
        _emit 0x01
        _emit 0x4E
        _emit 0x30
        // add dword ptr [esi + 0x30], ecx
        _emit 0x8B
        _emit 0x46
        _emit 0x30
        // mov eax, dword ptr [esi + 0x30]
        _emit 0x3B
        _emit 0x46
        _emit 0x2C
        // cmp eax, dword ptr [esi + 0x2c]
        _emit 0x7C
        _emit 0x03
        // jl 0x115e2a4
        _emit 0x89
        _emit 0x6E
        _emit 0x30
        // mov dword ptr [esi + 0x30], ebp
        _emit 0x39
        _emit 0x6E
        _emit 0x64
        // cmp dword ptr [esi + 0x64], ebp
        _emit 0x75
        _emit 0x08
        // jne 0x115e2b1
        _emit 0x89
        _emit 0x4E
        _emit 0x64
        // mov dword ptr [esi + 0x64], ecx
        _emit 0x89
        _emit 0x4E
        _emit 0x68
        // mov dword ptr [esi + 0x68], ecx
        _emit 0xEB
        _emit 0x06
        // jmp 0x115e2b7
        _emit 0x89
        _emit 0x6E
        _emit 0x64
        // mov dword ptr [esi + 0x64], ebp
        _emit 0x89
        _emit 0x6E
        _emit 0x68
        // mov dword ptr [esi + 0x68], ebp
        _emit 0x89
        _emit 0x6E
        _emit 0x5C
        // mov dword ptr [esi + 0x5c], ebp
        _emit 0x89
        _emit 0xAE
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x80], ebp
        _emit 0x89
        _emit 0xAE
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x84], ebp
        _emit 0x89
        _emit 0xAE
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x88], ebp
        _emit 0xEB
        _emit 0x04
        // jmp 0x115e2d2
        _emit 0x40
        // inc eax
        _emit 0x89
        _emit 0x46
        _emit 0x5C
        // mov dword ptr [esi + 0x5c], eax
        _emit 0x33
        _emit 0xFF
        // xor edi, edi
        _emit 0x39
        _emit 0x6E
        _emit 0x78
        // cmp dword ptr [esi + 0x78], ebp
        _emit 0x76
        _emit 0x47
        // jbe 0x115e320
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // mov ebx, dword ptr [esp + 0x24]
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0x8B
        _emit 0x46
        _emit 0x38
        // mov eax, dword ptr [esi + 0x38]
        _emit 0x8B
        _emit 0x4E
        _emit 0x5C
        // mov ecx, dword ptr [esi + 0x5c]
        _emit 0x8D
        _emit 0x14
        _emit 0x85
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea edx, [eax*4]
        _emit 0x0F
        _emit 0xAF
        _emit 0xC8
        // imul ecx, eax
        _emit 0x8B
        _emit 0x46
        _emit 0x64
        // mov eax, dword ptr [esi + 0x64]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0x56
        _emit 0x3C
        // mov edx, dword ptr [esi + 0x3c]
        _emit 0x0F
        _emit 0xAF
        _emit 0xD7
        // imul edx, edi
        _emit 0x03
        _emit 0xCA
        // add ecx, edx
        _emit 0x8B
        _emit 0x54
        _emit 0x86
        _emit 0x18
        // mov edx, dword ptr [esi + eax*4 + 0x18]
        _emit 0x8D
        _emit 0x04
        _emit 0x8A
        // lea eax, [edx + ecx*4]
        _emit 0x0F
        _emit 0xB7
        _emit 0x4B
        _emit 0x0E
        // movzx ecx, word ptr [ebx + 0xe]
        _emit 0x8B
        _emit 0x53
        _emit 0x04
        // mov edx, dword ptr [ebx + 4]
        _emit 0x0F
        _emit 0xAF
        _emit 0xCF
        // imul ecx, edi
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x04
        _emit 0x8A
        // lea eax, [edx + ecx*4]
        _emit 0x50
        // push eax
        call FUN_011e0744
        _emit 0x47
        // inc edi
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x3B
        _emit 0x7E
        _emit 0x78
        // cmp edi, dword ptr [esi + 0x78]
        _emit 0x72
        _emit 0xC0
        // jb 0x115e2e0
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
        _emit 0x0C
        // add esp, 0xc
        _emit 0xC2
        _emit 0x10
        _emit 0x00
        // ret 0x10
    }
}

// @ 0x0115e330  (138 bytes)
__declspec(naked) void FUN_0115e330()
{
    __asm {
        _emit 0x80
        _emit 0x7C
        _emit 0x24
        _emit 0x08
        _emit 0x00
        // cmp byte ptr [esp + 8], 0
        _emit 0x53
        // push ebx
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
        _emit 0x75
        _emit 0x01
        // jne 0x115e340
        _emit 0x4D
        // dec ebp
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0xBF
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edi, 1
        _emit 0xD3
        _emit 0xE7
        // shl edi, cl
        _emit 0x8B
        _emit 0x0D
        _emit 0xA8
        _emit 0x61
        _emit 0x6E
        _emit 0x01
        // mov ecx, dword ptr [0x16e61a8]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x68
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // push 0x80
        _emit 0x8B
        _emit 0xF7
        // mov esi, edi
        _emit 0xD1
        _emit 0xEE
        // shr esi, 1
        _emit 0x46
        // inc esi
        _emit 0x8D
        _emit 0x5C
        _emit 0x77
        _emit 0x08
        // lea ebx, [edi + esi*2 + 8]
        _emit 0x03
        _emit 0xDB
        // add ebx, ebx
        _emit 0x68
        _emit 0x00
        _emit 0xE9
        _emit 0x4C
        _emit 0x01
        // push 0x14ce900
        _emit 0x03
        _emit 0xDB
        // add ebx, ebx
        _emit 0x53
        // push ebx
        call FUN_0112c820
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x75
        _emit 0x19
        // jne 0x115e38b
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov eax, dword ptr [esp + 0x1c]
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0xC7
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [eax], 0
        _emit 0xC7
        _emit 0x40
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [eax + 4], 0
        _emit 0x83
        _emit 0xC8
        _emit 0xFF
        // or eax, 0xffffffff
        _emit 0x5B
        // pop ebx
        _emit 0xC3
        // ret 
        _emit 0x8D
        _emit 0x0C
        _emit 0xB5
        _emit 0x18
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [esi*4 + 0x18]
        _emit 0x89
        _emit 0x48
        _emit 0x10
        // mov dword ptr [eax + 0x10], ecx
        _emit 0x89
        _emit 0x78
        _emit 0x08
        // mov dword ptr [eax + 8], edi
        _emit 0x89
        _emit 0x70
        _emit 0x04
        // mov dword ptr [eax + 4], esi
        _emit 0x8D
        _emit 0x0C
        _emit 0xB1
        // lea ecx, [ecx + esi*4]
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x48
        _emit 0x14
        // mov dword ptr [eax + 0x14], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x89
        _emit 0x28
        // mov dword ptr [eax], ebp
        _emit 0x5E
        // pop esi
        _emit 0xC7
        _emit 0x40
        _emit 0x0C
        _emit 0x18
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [eax + 0xc], 0x18
        _emit 0x5D
        // pop ebp
        _emit 0x89
        _emit 0x01
        // mov dword ptr [ecx], eax
        _emit 0x89
        _emit 0x59
        _emit 0x04
        // mov dword ptr [ecx + 4], ebx
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x5B
        // pop ebx
        _emit 0xC3
        // ret 
    }
}

// @ 0x0115e3c0  (38 bytes)
__declspec(naked) void FUN_0115e3c0()
{
    __asm {
        _emit 0x8B
        _emit 0x0D
        _emit 0xA8
        _emit 0x61
        _emit 0x6E
        _emit 0x01
        // mov ecx, dword ptr [0x16e61a8]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x08
        // mov esi, dword ptr [esp + 8]
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x50
        // push eax
        call FUN_0112c850
        _emit 0xC7
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi], 0
        _emit 0xC7
        _emit 0x46
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 4], 0
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x5E
        // pop esi
        _emit 0xC3
        // ret 
    }
}

// @ 0x0115e3f0  (197 bytes)
__declspec(naked) void FUN_0115e3f0()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x1C
        // sub esp, 0x1c
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov eax, dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x58
        _emit 0x08
        // mov ebx, dword ptr [eax + 8]
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x68
        _emit 0x14
        // mov ebp, dword ptr [eax + 0x14]
        _emit 0x56
        // push esi
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ecx
        _emit 0x8B
        _emit 0x48
        _emit 0x10
        // mov ecx, dword ptr [eax + 0x10]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x78
        _emit 0x04
        // mov edi, dword ptr [eax + 4]
        _emit 0x03
        _emit 0xE8
        // add ebp, eax
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0x03
        _emit 0xD0
        // add edx, eax
        _emit 0x03
        _emit 0xC8
        // add ecx, eax
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], ebp
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x30
        // mov dword ptr [esp + 0x30], esi
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x7E
        _emit 0x3D
        // jle 0x115e461
        _emit 0xD9
        _emit 0x05
        _emit 0x24
        _emit 0xE9
        _emit 0x4C
        _emit 0x01
        // fld dword ptr [0x14ce924]
        _emit 0xF3
        _emit 0x0F
        _emit 0x2A
        _emit 0xC3
        // cvtsi2ss xmm0, ebx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // movss dword ptr [esp + 0x10], xmm0
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0xC1
        // mov eax, ecx
        _emit 0x2B
        _emit 0xD1
        // sub edx, ecx
        _emit 0xDB
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // fild dword ptr [esp + 0x30]
        _emit 0x46
        // inc esi
        _emit 0x83
        _emit 0xC0
        _emit 0x04
        // add eax, 4
        _emit 0x3B
        _emit 0xF7
        // cmp esi, edi
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x30
        // mov dword ptr [esp + 0x30], esi
        _emit 0xD8
        _emit 0xF1
        // fdiv st(1)
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD9
        _emit 0xFF
        // fcos 
        _emit 0xD9
        _emit 0x5C
        _emit 0x02
        _emit 0xFC
        // fstp dword ptr [edx + eax - 4]
        _emit 0xD9
        _emit 0xFE
        // fsin 
        _emit 0xD9
        _emit 0x58
        _emit 0xFC
        // fstp dword ptr [eax - 4]
        _emit 0x7C
        _emit 0xDF
        // jl 0x115e43c
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0x85
        _emit 0xDB
        // test ebx, ebx
        _emit 0x7E
        _emit 0x39
        // jle 0x115e4a0
        _emit 0x8B
        _emit 0xFD
        // mov edi, ebp
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
        _emit 0x14
        // mov edx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xC7
        _emit 0x07
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi], 0
        _emit 0x85
        _emit 0xD2
        // test edx, edx
        _emit 0x7E
        _emit 0x18
        // jle 0x115e498
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x8B
        _emit 0xE9
        // mov ebp, ecx
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x83
        _emit 0xE5
        _emit 0x01
        // and ebp, 1
        _emit 0x0B
        _emit 0xC5
        // or eax, ebp
        _emit 0xD1
        _emit 0xE9
        // shr ecx, 1
        _emit 0x83
        _emit 0xEA
        _emit 0x01
        // sub edx, 1
        _emit 0x75
        _emit 0xF0
        // jne 0x115e482
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x28
        // mov ebp, dword ptr [esp + 0x28]
        _emit 0x89
        _emit 0x07
        // mov dword ptr [edi], eax
        _emit 0x46
        // inc esi
        _emit 0x83
        _emit 0xC7
        _emit 0x04
        // add edi, 4
        _emit 0x3B
        _emit 0xF3
        // cmp esi, ebx
        _emit 0x7C
        _emit 0xD0
        // jl 0x115e470
        _emit 0x5F
        // pop edi
        _emit 0x8D
        _emit 0x53
        _emit 0x01
        // lea edx, [ebx + 1]
        _emit 0x5E
        // pop esi
        _emit 0x89
        _emit 0x5C
        _emit 0x9D
        _emit 0x00
        // mov dword ptr [ebp + ebx*4], ebx
        _emit 0x89
        _emit 0x54
        _emit 0x9D
        _emit 0x04
        // mov dword ptr [ebp + ebx*4 + 4], edx
        _emit 0x5D
        // pop ebp
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x1C
        // add esp, 0x1c
        _emit 0xC3
        // ret 
    }
}
