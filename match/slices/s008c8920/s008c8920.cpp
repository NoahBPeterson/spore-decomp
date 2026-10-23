// Slice s008c8920: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_008c77d0();
extern "C" void FUN_008c7be0();
extern "C" void FUN_008c7c40();
extern "C" void FUN_008c8220();
extern "C" void FUN_008c8720();
extern "C" void FUN_008c8920();
extern "C" void FUN_008c8eb0();
extern "C" void FUN_008d1260();
extern "C" void FUN_008d14d0();

// @ 0x008c8920  (772 bytes)
__declspec(naked) void FUN_008c8920()
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
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x38
        // mov esi, dword ptr [esp + 0x38]
        _emit 0x8B
        _emit 0x86
        _emit 0x28
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x2228]
        _emit 0x8B
        _emit 0x8E
        _emit 0x2C
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x222c]
        _emit 0x8B
        _emit 0x96
        _emit 0x30
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x2230]
        _emit 0x57
        // push edi
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], eax
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ecx
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], edx
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x18], 0
        _emit 0x0F
        _emit 0xBF
        _emit 0x8E
        _emit 0x24
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // movsx ecx, word ptr [esi + 0x2224]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov eax, dword ptr [esp + 0x18]
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x0F
        _emit 0x8D
        _emit 0xB8
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // jge 0x8c8c1c
        _emit 0x8B
        _emit 0x96
        _emit 0x1C
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esi + 0x221c]
        _emit 0x0F
        _emit 0xBF
        _emit 0x2C
        _emit 0x42
        // movsx ebp, word ptr [edx + eax*2]
        _emit 0x8B
        _emit 0x8E
        _emit 0x20
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x2220]
        _emit 0x0F
        _emit 0xBF
        _emit 0x1C
        _emit 0x41
        // movsx ebx, word ptr [ecx + eax*2]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x1C
        // mov edi, dword ptr [esp + 0x1c]
        _emit 0x80
        _emit 0x3C
        _emit 0x2F
        _emit 0x00
        // cmp byte ptr [edi + ebp], 0
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], ebp
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], ebp
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x30
        // mov dword ptr [esp + 0x30], ebx
        _emit 0x0F
        _emit 0x84
        _emit 0xCC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0x8c8a5e
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov edx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x04
        _emit 0xAA
        // mov eax, dword ptr [edx + ebp*4]
        _emit 0x8B
        _emit 0x14
        _emit 0xA9
        // mov edx, dword ptr [ecx + ebp*4]
        _emit 0x33
        _emit 0xC9
        // xor ecx, ecx
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], ecx
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], ecx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x80
        _emit 0xE1
        _emit 0x3F
        // and cl, 0x3f
        _emit 0x83
        _emit 0xCF
        _emit 0xFF
        // or edi, 0xffffffff
        _emit 0x80
        _emit 0xF9
        _emit 0x20
        // cmp cl, 0x20
        _emit 0x75
        _emit 0x3E
        // jne 0x8c89f5
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x0C
        _emit 0x99
        // mov ecx, dword ptr [ecx + ebx*4]
        _emit 0x89
        _emit 0x0E
        // mov dword ptr [esi], ecx
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // mov dword ptr [esp + 0x34], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov ecx, dword ptr [esp + 0x1c]
        _emit 0x80
        _emit 0x3C
        _emit 0x0B
        _emit 0x00
        // cmp byte ptr [ebx + ecx], 0
        _emit 0x74
        _emit 0x1F
        // je 0x8c89ed
        _emit 0x39
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // cmp dword ptr [esp + 0x34], eax
        _emit 0x75
        _emit 0x21
        // jne 0x8c89f5
        _emit 0x3B
        _emit 0xDD
        // cmp ebx, ebp
        _emit 0x74
        _emit 0x11
        // je 0x8c89e9
        _emit 0x80
        _emit 0x7C
        _emit 0x0B
        _emit 0xFF
        _emit 0x00
        // cmp byte ptr [ebx + ecx - 1], 0
        _emit 0x74
        _emit 0x0A
        // je 0x8c89e9
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x4C
        _emit 0x99
        _emit 0xFC
        // mov ecx, dword ptr [ecx + ebx*4 - 4]
        _emit 0x89
        _emit 0x0E
        // mov dword ptr [esi], ecx
        _emit 0x39
        _emit 0x06
        // cmp dword ptr [esi], eax
        _emit 0x75
        _emit 0x08
        // jne 0x8c89f5
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x48
        // dec eax
        _emit 0x89
        _emit 0x04
        _emit 0xA9
        // mov dword ptr [ecx + ebp*4], eax
        _emit 0x8B
        _emit 0xCA
        // mov ecx, edx
        _emit 0x80
        _emit 0xE1
        _emit 0x3F
        // and cl, 0x3f
        _emit 0x80
        _emit 0xF9
        _emit 0x20
        // cmp cl, 0x20
        _emit 0x0F
        _emit 0x85
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0x8c8ae3
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x0C
        _emit 0x99
        // mov ecx, dword ptr [ecx + ebx*4]
        _emit 0x89
        _emit 0x4E
        _emit 0x04
        // mov dword ptr [esi + 4], ecx
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // mov dword ptr [esp + 0x34], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov ecx, dword ptr [esp + 0x1c]
        _emit 0x80
        _emit 0x3C
        _emit 0x0B
        _emit 0x00
        // cmp byte ptr [ebx + ecx], 0
        _emit 0x75
        _emit 0x0D
        // jne 0x8c8a28
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x4A
        // dec edx
        _emit 0x89
        _emit 0x14
        _emit 0xA9
        // mov dword ptr [ecx + ebp*4], edx
        _emit 0xE9
        _emit 0xBB
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jmp 0x8c8ae3
        _emit 0x39
        _emit 0x54
        _emit 0x24
        _emit 0x34
        // cmp dword ptr [esp + 0x34], edx
        _emit 0x0F
        _emit 0x85
        _emit 0xB1
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0x8c8ae3
        _emit 0x3B
        _emit 0xDD
        // cmp ebx, ebp
        _emit 0x74
        _emit 0x12
        // je 0x8c8a48
        _emit 0x80
        _emit 0x7C
        _emit 0x0B
        _emit 0xFF
        _emit 0x00
        // cmp byte ptr [ebx + ecx - 1], 0
        _emit 0x74
        _emit 0x0B
        // je 0x8c8a48
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x4C
        _emit 0x99
        _emit 0xFC
        // mov ecx, dword ptr [ecx + ebx*4 - 4]
        _emit 0x89
        _emit 0x4E
        _emit 0x04
        // mov dword ptr [esi + 4], ecx
        _emit 0x39
        _emit 0x56
        _emit 0x04
        // cmp dword ptr [esi + 4], edx
        _emit 0x0F
        _emit 0x85
        _emit 0x92
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0x8c8ae3
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x4A
        // dec edx
        _emit 0x89
        _emit 0x14
        _emit 0xA9
        // mov dword ptr [ecx + ebp*4], edx
        _emit 0xE9
        _emit 0x85
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jmp 0x8c8ae3
        _emit 0x80
        _emit 0x3C
        _emit 0x3B
        _emit 0x00
        // cmp byte ptr [ebx + edi], 0
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
        _emit 0x8B
        _emit 0x34
        _emit 0xA8
        // mov esi, dword ptr [eax + ebp*4]
        _emit 0x8B
        _emit 0x0C
        _emit 0xAA
        // mov ecx, dword ptr [edx + ebp*4]
        _emit 0x8B
        _emit 0x04
        _emit 0x98
        // mov eax, dword ptr [eax + ebx*4]
        _emit 0x8B
        _emit 0x14
        _emit 0x9A
        // mov edx, dword ptr [edx + ebx*4]
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], esi
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], ecx
        _emit 0x75
        _emit 0x39
        // jne 0x8c8ab9
        _emit 0x8D
        _emit 0x44
        _emit 0x06
        _emit 0x01
        // lea eax, [esi + eax + 1]
        _emit 0xD1
        _emit 0xF8
        // sar eax, 1
        _emit 0x8D
        _emit 0x54
        _emit 0x11
        _emit 0x01
        // lea edx, [ecx + edx + 1]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x80
        _emit 0xE1
        _emit 0x3F
        // and cl, 0x3f
        _emit 0xD1
        _emit 0xFA
        // sar edx, 1
        _emit 0x80
        _emit 0xF9
        _emit 0x20
        // cmp cl, 0x20
        _emit 0x75
        _emit 0x0C
        // jne 0x8c8aa2
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x4E
        // dec esi
        _emit 0x48
        // dec eax
        _emit 0x89
        _emit 0x34
        _emit 0xA9
        // mov dword ptr [ecx + ebp*4], esi
        _emit 0xFF
        _emit 0x0C
        _emit 0x99
        // dec dword ptr [ecx + ebx*4]
        _emit 0x8B
        _emit 0xCA
        // mov ecx, edx
        _emit 0x80
        _emit 0xE1
        _emit 0x3F
        // and cl, 0x3f
        _emit 0x80
        _emit 0xF9
        _emit 0x20
        // cmp cl, 0x20
        _emit 0x75
        _emit 0x31
        // jne 0x8c8add
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0xFF
        _emit 0x0C
        _emit 0xA9
        // dec dword ptr [ecx + ebp*4]
        _emit 0x4A
        // dec edx
        _emit 0xFF
        _emit 0x0C
        _emit 0x99
        // dec dword ptr [ecx + ebx*4]
        _emit 0xEB
        _emit 0x24
        // jmp 0x8c8add
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x80
        _emit 0xE1
        _emit 0x3F
        // and cl, 0x3f
        _emit 0x80
        _emit 0xF9
        _emit 0x20
        // cmp cl, 0x20
        _emit 0x75
        _emit 0x08
        // jne 0x8c8acb
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x48
        // dec eax
        _emit 0x89
        _emit 0x04
        _emit 0x99
        // mov dword ptr [ecx + ebx*4], eax
        _emit 0x8B
        _emit 0xCA
        // mov ecx, edx
        _emit 0x80
        _emit 0xE1
        _emit 0x3F
        // and cl, 0x3f
        _emit 0x80
        _emit 0xF9
        _emit 0x20
        // cmp cl, 0x20
        _emit 0x75
        _emit 0x08
        // jne 0x8c8add
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x4A
        // dec edx
        _emit 0x89
        _emit 0x14
        _emit 0x99
        // mov dword ptr [ecx + ebx*4], edx
        _emit 0x8B
        _emit 0xFD
        // mov edi, ebp
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], ebx
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x0F
        _emit 0x8C
        _emit 0xC7
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jl 0x8c8bb2
        _emit 0xEB
        _emit 0x03
        // jmp 0x8c8af0
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x8D
        _emit 0x77
        _emit 0x01
        // lea esi, [edi + 1]
        _emit 0x3B
        _emit 0xF3
        // cmp esi, ebx
        _emit 0x0F
        _emit 0x4F
        _emit 0xF5
        // cmovg esi, ebp
        _emit 0x8B
        _emit 0x1C
        _emit 0xB1
        // mov ebx, dword ptr [ecx + esi*4]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x2C
        _emit 0xB1
        // mov ebp, dword ptr [ecx + esi*4]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov ecx, dword ptr [esp + 0x1c]
        _emit 0x80
        _emit 0x3C
        _emit 0x0E
        _emit 0x00
        // cmp byte ptr [esi + ecx], 0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x34
        // mov dword ptr [esp + 0x34], ebx
        _emit 0x89
        _emit 0x6C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], ebp
        _emit 0x75
        _emit 0x64
        // jne 0x8c8b80
        _emit 0x8D
        _emit 0x5C
        _emit 0x0B
        _emit 0x01
        // lea ebx, [ebx + ecx + 1]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // mov ecx, dword ptr [esp + 0x24]
        _emit 0x8D
        _emit 0x6C
        _emit 0x29
        _emit 0x01
        // lea ebp, [ecx + ebp + 1]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // mov ecx, dword ptr [esp + 0x28]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x44
        // mov edx, dword ptr [esp + 0x44]
        _emit 0x50
        // push eax
        _emit 0xD1
        _emit 0xFB
        // sar ebx, 1
        _emit 0xD1
        _emit 0xFD
        // sar ebp, 1
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xD5
        // mov edx, ebp
        _emit 0x8B
        _emit 0xC3
        // mov eax, ebx
        call FUN_008c8220
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        _emit 0x3B
        _emit 0x74
        _emit 0x24
        _emit 0x28
        // cmp esi, dword ptr [esp + 0x28]
        _emit 0x0F
        _emit 0x84
        _emit 0xBD
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0x8c8c0f
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // mov ecx, dword ptr [esp + 0x34]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov ecx, dword ptr [esp + 0x2c]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], ecx
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0x8B
        _emit 0xC3
        // mov eax, ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x30
        // mov ebx, dword ptr [esp + 0x30]
        _emit 0x8B
        _emit 0xD5
        // mov edx, ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x28
        // mov ebp, dword ptr [esp + 0x28]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], ecx
        _emit 0x8B
        _emit 0xFE
        // mov edi, esi
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x0F
        _emit 0x8D
        _emit 0x72
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jge 0x8c8af0
        _emit 0xEB
        _emit 0x36
        // jmp 0x8c8bb6
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // mov ecx, dword ptr [esp + 0x28]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x44
        // mov edx, dword ptr [esp + 0x44]
        _emit 0x50
        // push eax
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xD5
        // mov edx, ebp
        _emit 0x8B
        _emit 0xC3
        // mov eax, ebx
        call FUN_008c8220
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        _emit 0x3B
        _emit 0x74
        _emit 0x24
        _emit 0x28
        // cmp esi, dword ptr [esp + 0x28]
        _emit 0x74
        _emit 0x71
        // je 0x8c8c0f
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x8B
        _emit 0xC3
        // mov eax, ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x30
        // mov ebx, dword ptr [esp + 0x30]
        _emit 0x8B
        _emit 0xD5
        // mov edx, ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x28
        // mov ebp, dword ptr [esp + 0x28]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], ecx
        _emit 0xEB
        _emit 0x04
        // jmp 0x8c8bb6
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov ecx, dword ptr [esp + 0x2c]
        _emit 0x8D
        _emit 0x79
        _emit 0x01
        // lea edi, [ecx + 1]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x0F
        _emit 0x4F
        _emit 0xFD
        // cmovg edi, ebp
        _emit 0x8B
        _emit 0x34
        _emit 0xB9
        // mov esi, dword ptr [ecx + edi*4]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x1C
        _emit 0xB9
        // mov ebx, dword ptr [ecx + edi*4]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov ecx, dword ptr [esp + 0x1c]
        _emit 0x80
        _emit 0x3C
        _emit 0x0F
        _emit 0x00
        // cmp byte ptr [edi + ecx], 0
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], esi
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], ebx
        _emit 0x74
        _emit 0x24
        // je 0x8c8c02
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x48
        // mov edx, dword ptr [esp + 0x48]
        _emit 0x50
        // push eax
        call FUN_008c7c40
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        _emit 0x3B
        _emit 0xFD
        // cmp edi, ebp
        _emit 0x74
        _emit 0x1D
        // je 0x8c8c0f
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0x8B
        _emit 0xD3
        // mov edx, ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x30
        // mov ebx, dword ptr [esp + 0x30]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], ecx
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0xEB
        _emit 0xB4
        // jmp 0x8c8bb6
        _emit 0x3B
        _emit 0xFD
        // cmp edi, ebp
        _emit 0x74
        _emit 0x09
        // je 0x8c8c0f
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x30
        // mov ebx, dword ptr [esp + 0x30]
        _emit 0xE9
        _emit 0xD4
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jmp 0x8c8ae3
        _emit 0xFF
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // inc dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x3C
        // mov esi, dword ptr [esp + 0x3c]
        _emit 0xE9
        _emit 0x35
        _emit 0xFD
        _emit 0xFF
        _emit 0xFF
        // jmp 0x8c8951
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

// @ 0x008c8c30  (630 bytes)
__declspec(naked) void FUN_008c8c30()
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
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov edi, dword ptr [esp + 0x14]
        _emit 0x6A
        _emit 0x04
        // push 4
        _emit 0x68
        _emit 0x38
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // push 0x2238
        _emit 0x57
        // push edi
        call FUN_008d14d0
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x39
        _emit 0x5C
        _emit 0x24
        _emit 0x40
        // cmp dword ptr [esp + 0x40], ebx
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x0F
        _emit 0x95
        _emit 0xC0
        // setne al
        _emit 0x39
        _emit 0x5C
        _emit 0x24
        _emit 0x44
        // cmp dword ptr [esp + 0x44], ebx
        _emit 0x88
        _emit 0x86
        _emit 0x10
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esi + 0x2210], al
        _emit 0x0F
        _emit 0x95
        _emit 0xC0
        // setne al
        _emit 0x89
        _emit 0xBE
        _emit 0x34
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x2234], edi
        _emit 0x88
        _emit 0x86
        _emit 0x0F
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esi + 0x220f], al
        _emit 0x3A
        _emit 0xC3
        // cmp al, bl
        _emit 0x75
        _emit 0x16
        // jne 0x8c8c86
        _emit 0x38
        _emit 0x5C
        _emit 0x24
        _emit 0x38
        // cmp byte ptr [esp + 0x38], bl
        _emit 0x75
        _emit 0x08
        // jne 0x8c8c7e
        _emit 0x8A
        _emit 0x4C
        _emit 0x24
        _emit 0x3C
        // mov cl, byte ptr [esp + 0x3c]
        _emit 0x3A
        _emit 0xCB
        // cmp cl, bl
        _emit 0x74
        _emit 0x0C
        // je 0x8c8c8a
        _emit 0xB1
        _emit 0x01
        // mov cl, 1
        _emit 0x88
        _emit 0x4C
        _emit 0x24
        _emit 0x38
        // mov byte ptr [esp + 0x38], cl
        _emit 0xEB
        _emit 0x04
        // jmp 0x8c8c8a
        _emit 0x8A
        _emit 0x4C
        _emit 0x24
        _emit 0x3C
        // mov cl, byte ptr [esp + 0x3c]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x4C
        // mov edi, dword ptr [esp + 0x4c]
        _emit 0x8A
        _emit 0x54
        _emit 0x24
        _emit 0x30
        // mov dl, byte ptr [esp + 0x30]
        _emit 0x88
        _emit 0x96
        _emit 0x0C
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esi + 0x220c], dl
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x74
        _emit 0x0C
        // je 0x8c8ca8
        _emit 0xC7
        _emit 0x86
        _emit 0x08
        _emit 0x22
        _emit 0x00
        _emit 0x00
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x2208], 2
        _emit 0xEB
        _emit 0x12
        // jmp 0x8c8cba
        _emit 0x32
        _emit 0xC0
        // xor al, al
        _emit 0x3A
        _emit 0xC2
        // cmp al, dl
        _emit 0x1B
        _emit 0xC0
        // sbb eax, eax
        _emit 0x83
        _emit 0xE0
        _emit 0x02
        // and eax, 2
        _emit 0x83
        _emit 0xC0
        _emit 0x02
        // add eax, 2
        _emit 0x89
        _emit 0x86
        _emit 0x08
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x2208], eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // mov eax, dword ptr [esp + 0x48]
        _emit 0x3B
        _emit 0x86
        _emit 0x08
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // cmp eax, dword ptr [esi + 0x2208]
        _emit 0x7E
        _emit 0x06
        // jle 0x8c8ccc
        _emit 0x89
        _emit 0x86
        _emit 0x08
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x2208], eax
        _emit 0xB8
        _emit 0x10
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 0x10
        _emit 0x39
        _emit 0x86
        _emit 0x08
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // cmp dword ptr [esi + 0x2208], eax
        _emit 0x7E
        _emit 0x06
        // jle 0x8c8cdf
        _emit 0x89
        _emit 0x86
        _emit 0x08
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x2208], eax
        _emit 0x8A
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // mov al, byte ptr [esp + 0x38]
        _emit 0x88
        _emit 0x86
        _emit 0x0D
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esi + 0x220d], al
        _emit 0x88
        _emit 0x8E
        _emit 0x0E
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esi + 0x220e], cl
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x74
        _emit 0x09
        // je 0x8c8cfc
        _emit 0xC6
        _emit 0x86
        _emit 0x11
        _emit 0x22
        _emit 0x00
        _emit 0x00
        _emit 0x01
        // mov byte ptr [esi + 0x2211], 1
        _emit 0xEB
        _emit 0x14
        // jmp 0x8c8d10
        _emit 0x3A
        _emit 0xCB
        // cmp cl, bl
        _emit 0x75
        _emit 0x08
        // jne 0x8c8d08
        _emit 0x3A
        _emit 0xD3
        // cmp dl, bl
        _emit 0x77
        _emit 0x04
        // ja 0x8c8d08
        _emit 0x32
        _emit 0xC0
        // xor al, al
        _emit 0xEB
        _emit 0x02
        // jmp 0x8c8d0a
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x88
        _emit 0x86
        _emit 0x11
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esi + 0x2211], al
        _emit 0x66
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov cx, word ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // mov edx, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // mov eax, dword ptr [esp + 0x24]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x28
        // mov edi, dword ptr [esp + 0x28]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x2C
        // mov ebp, dword ptr [esp + 0x2c]
        _emit 0x66
        _emit 0x89
        _emit 0x8E
        _emit 0x24
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov word ptr [esi + 0x2224], cx
        _emit 0x89
        _emit 0x96
        _emit 0x1C
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x221c], edx
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov edx, dword ptr [esp + 0x20]
        _emit 0x0F
        _emit 0xBF
        _emit 0xC9
        // movsx ecx, cx
        _emit 0x89
        _emit 0x9E
        _emit 0x14
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x2214], ebx
        _emit 0x89
        _emit 0x9E
        _emit 0x18
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x2218], ebx
        _emit 0x89
        _emit 0x5E
        _emit 0x2C
        // mov dword ptr [esi + 0x2c], ebx
        _emit 0x89
        _emit 0x96
        _emit 0x20
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x2220], edx
        _emit 0x89
        _emit 0x86
        _emit 0x28
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x2228], eax
        _emit 0x89
        _emit 0xBE
        _emit 0x2C
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x222c], edi
        _emit 0x89
        _emit 0xAE
        _emit 0x30
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x2230], ebp
        _emit 0x0F
        _emit 0xBF
        _emit 0x54
        _emit 0x4A
        _emit 0xFE
        // movsx edx, word ptr [edx + ecx*2 - 2]
        _emit 0x52
        // push edx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xDE
        // mov ebx, esi
        call FUN_008c7be0
        _emit 0x8B
        _emit 0x6E
        _emit 0x44
        // mov ebp, dword ptr [esi + 0x44]
        _emit 0x8B
        _emit 0x5E
        _emit 0x40
        // mov ebx, dword ptr [esi + 0x40]
        _emit 0x8B
        _emit 0xC5
        // mov eax, ebp
        _emit 0x2B
        _emit 0xC3
        // sub eax, ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x3D
        _emit 0x04
        _emit 0xB5
        _emit 0x00
        _emit 0x00
        // cmp eax, 0xb504
        _emit 0xC7
        _emit 0x46
        _emit 0x50
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x50], 0
        _emit 0x7D
        _emit 0x0E
        // jge 0x8c8d97
        _emit 0x8B
        _emit 0x4E
        _emit 0x4C
        // mov ecx, dword ptr [esi + 0x4c]
        _emit 0x2B
        _emit 0x4E
        _emit 0x48
        // sub ecx, dword ptr [esi + 0x48]
        _emit 0x81
        _emit 0xF9
        _emit 0x04
        _emit 0xB5
        _emit 0x00
        _emit 0x00
        // cmp ecx, 0xb504
        _emit 0x7C
        _emit 0x07
        // jl 0x8c8d9e
        _emit 0xC7
        _emit 0x46
        _emit 0x50
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x50], 1
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // mov dword ptr [esp + 0x38], eax
        _emit 0x83
        _emit 0xC5
        _emit 0x40
        // add ebp, 0x40
        _emit 0xC1
        _emit 0xFD
        _emit 0x06
        // sar ebp, 6
        _emit 0x83
        _emit 0xC3
        _emit 0xC0
        // add ebx, -0x40
        _emit 0xC1
        _emit 0xFB
        _emit 0x06
        // sar ebx, 6
        _emit 0x8B
        _emit 0xFD
        // mov edi, ebp
        _emit 0x2B
        _emit 0xFB
        // sub edi, ebx
        _emit 0x47
        // inc edi
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x75
        _emit 0x0C
        // jne 0x8c8dc5
        _emit 0x38
        _emit 0x86
        _emit 0x11
        _emit 0x22
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [esi + 0x2211], al
        _emit 0x75
        _emit 0x04
        // jne 0x8c8dc5
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0xEB
        _emit 0x45
        // jmp 0x8c8e0a
        _emit 0x83
        _emit 0xFF
        _emit 0x20
        // cmp edi, 0x20
        _emit 0x7F
        _emit 0x11
        // jg 0x8c8ddb
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x75
        _emit 0x08
        // jne 0x8c8dd6
        _emit 0x8D
        _emit 0x96
        _emit 0xE4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea edx, [esi + 0xe4]
        _emit 0xEB
        _emit 0x20
        // jmp 0x8c8df6
        _emit 0x8D
        _emit 0x56
        _emit 0x54
        // lea edx, [esi + 0x54]
        _emit 0xEB
        _emit 0x1B
        // jmp 0x8c8df6
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x8D
        _emit 0x14
        _emit 0xBD
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea edx, [edi*4]
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        call FUN_008d1260
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // mov eax, dword ptr [esp + 0x40]
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x7E
        _emit 0x0C
        // jle 0x8c8e06
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x8B
        _emit 0xFA
        // mov edi, edx
        _emit 0xF3
        _emit 0xAB
        // rep stosd dword ptr es:[edi], eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // mov eax, dword ptr [esp + 0x38]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x75
        _emit 0x31
        // jne 0x8c8e3b
        _emit 0x89
        _emit 0x96
        _emit 0x68
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x168], edx
        _emit 0x85
        _emit 0xD2
        // test edx, edx
        _emit 0x74
        _emit 0x0B
        // je 0x8c8e1f
        _emit 0x8D
        _emit 0x0C
        _emit 0x9D
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [ebx*4]
        _emit 0x2B
        _emit 0xD1
        // sub edx, ecx
        _emit 0xEB
        _emit 0x02
        // jmp 0x8c8e21
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x89
        _emit 0x9E
        _emit 0x6C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x16c], ebx
        _emit 0x8B
        _emit 0x5E
        _emit 0x48
        // mov ebx, dword ptr [esi + 0x48]
        _emit 0x89
        _emit 0xAE
        _emit 0x70
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x170], ebp
        _emit 0x8B
        _emit 0x6E
        _emit 0x4C
        // mov ebp, dword ptr [esi + 0x4c]
        _emit 0x89
        _emit 0x96
        _emit 0x64
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x164], edx
        _emit 0xEB
        _emit 0x21
        // jmp 0x8c8e5c
        _emit 0x8D
        _emit 0x0C
        _emit 0x9D
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [ebx*4]
        _emit 0x89
        _emit 0x96
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xd8], edx
        _emit 0x2B
        _emit 0xD1
        // sub edx, ecx
        _emit 0x89
        _emit 0x96
        _emit 0xD4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xd4], edx
        _emit 0x89
        _emit 0x9E
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xdc], ebx
        _emit 0x89
        _emit 0xAE
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xe0], ebp
        _emit 0x40
        // inc eax
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // mov dword ptr [esp + 0x38], eax
        _emit 0x0F
        _emit 0x8C
        _emit 0x3A
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jl 0x8c8da4
        _emit 0xC7
        _emit 0x86
        _emit 0x00
        _emit 0x22
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x2200], 0
        call FUN_008c77d0
        _emit 0x80
        _emit 0x7C
        _emit 0x24
        _emit 0x34
        _emit 0x03
        // cmp byte ptr [esp + 0x34], 3
        _emit 0xC7
        _emit 0x46
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x24], 0
        _emit 0x56
        // push esi
        _emit 0x75
        _emit 0x0F
        // jne 0x8c8e97
        call FUN_008c8720
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
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
        _emit 0xC3
        // ret 
        call FUN_008c8920
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
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
        _emit 0xC3
        // ret 
    }
}

// @ 0x008c8eb0  (76 bytes)
__declspec(naked) void FUN_008c8eb0()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // mov ebx, dword ptr [esp + 8]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xFA
        // mov edi, edx
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x3D
        // je 0x8c8ef9
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x71
        _emit 0x04
        // mov esi, dword ptr [ecx + 4]
        _emit 0x83
        _emit 0xEB
        _emit 0x04
        // sub ebx, 4
        _emit 0x83
        _emit 0xC7
        _emit 0x04
        // add edi, 4
        _emit 0x8B
        _emit 0x09
        // mov ecx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0xD1
        _emit 0xF9
        // sar ecx, 1
        _emit 0xD1
        _emit 0xFA
        // sar edx, 1
        _emit 0x3B
        _emit 0xCF
        // cmp ecx, edi
        _emit 0x7F
        _emit 0x26
        // jg 0x8c8ef8
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x7C
        _emit 0x06
        // jl 0x8c8edc
        _emit 0x40
        // inc eax
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x7D
        _emit 0x1C
        // jge 0x8c8ef8
        _emit 0x3B
        _emit 0xD7
        // cmp edx, edi
        _emit 0x7F
        _emit 0x18
        // jg 0x8c8ef8
        _emit 0x3B
        _emit 0xD3
        // cmp edx, ebx
        _emit 0x7C
        _emit 0x06
        // jl 0x8c8eea
        _emit 0x40
        // inc eax
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x7D
        _emit 0x0E
        // jge 0x8c8ef8
        _emit 0x8B
        _emit 0x4E
        _emit 0x04
        // mov ecx, dword ptr [esi + 4]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x07
        // je 0x8c8ef8
        _emit 0x8B
        _emit 0x71
        _emit 0x04
        // mov esi, dword ptr [ecx + 4]
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x75
        _emit 0xCE
        // jne 0x8c8ec6
        _emit 0x5E
        // pop esi
        _emit 0x5F
        // pop edi
        _emit 0x5B
        // pop ebx
        _emit 0xC3
        // ret 
    }
}

// @ 0x008c8f00  (254 bytes)
__declspec(naked) void FUN_008c8f00()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x14
        // mov ebp, dword ptr [esp + 0x14]
        _emit 0x56
        // push esi
        _emit 0x8D
        _emit 0x70
        _emit 0x01
        // lea esi, [eax + 1]
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x78
        _emit 0xFF
        // lea edi, [eax - 1]
        _emit 0xC1
        _emit 0xE0
        _emit 0x06
        // shl eax, 6
        _emit 0x83
        _emit 0xC0
        _emit 0x20
        // add eax, 0x20
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x3B
        _emit 0xF1
        // cmp esi, ecx
        _emit 0x0F
        _emit 0x9D
        _emit 0xC0
        // setge al
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x7C
        _emit 0x04
        // jl 0x8c8f25
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0xEB
        _emit 0x29
        // jmp 0x8c8f4e
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov edx, dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0xC1
        _emit 0xE1
        _emit 0x06
        // shl ecx, 6
        _emit 0x83
        _emit 0xC1
        _emit 0x20
        // add ecx, 0x20
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x0C
        _emit 0xB1
        // mov ecx, dword ptr [ecx + esi*4]
        _emit 0xC1
        _emit 0xE2
        _emit 0x06
        // shl edx, 6
        _emit 0x83
        _emit 0xC2
        _emit 0x20
        // add edx, 0x20
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        call FUN_008c8eb0
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x7D
        _emit 0x42
        // jge 0x8c8f90
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x0C
        _emit 0xA9
        // mov ecx, dword ptr [ecx + ebp*4]
        _emit 0xC1
        _emit 0xE6
        _emit 0x06
        // shl esi, 6
        _emit 0x83
        _emit 0xC6
        _emit 0x20
        // add esi, 0x20
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xD6
        // mov edx, esi
        call FUN_008c8eb0
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x7D
        _emit 0x25
        // jge 0x8c8f90
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0xD6
        // mov edx, esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x18
        // mov esi, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x0C
        _emit 0x8E
        // mov ecx, dword ptr [esi + ecx*4]
        _emit 0x53
        // push ebx
        call FUN_008c8eb0
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x7D
        _emit 0x0A
        // jge 0x8c8f90
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0xB8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 1
        _emit 0x5B
        // pop ebx
        _emit 0xC3
        // ret 
        _emit 0x3B
        _emit 0x7C
        _emit 0x24
        _emit 0x24
        // cmp edi, dword ptr [esp + 0x24]
        _emit 0x7D
        _emit 0x04
        // jge 0x8c8f9a
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0xEB
        _emit 0x29
        // jmp 0x8c8fc3
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov edx, dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x0C
        _emit 0xB9
        // mov ecx, dword ptr [ecx + edi*4]
        _emit 0x8B
        _emit 0xC5
        // mov eax, ebp
        _emit 0xC1
        _emit 0xE0
        _emit 0x06
        // shl eax, 6
        _emit 0x83
        _emit 0xC0
        _emit 0x20
        // add eax, 0x20
        _emit 0xC1
        _emit 0xE2
        _emit 0x06
        // shl edx, 6
        _emit 0x50
        // push eax
        _emit 0x83
        _emit 0xC2
        _emit 0x20
        // add edx, 0x20
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        call FUN_008c8eb0
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x7D
        _emit 0x34
        // jge 0x8c8ff7
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x18
        // mov esi, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x0C
        _emit 0xAE
        // mov ecx, dword ptr [esi + ebp*4]
        _emit 0xC1
        _emit 0xE7
        _emit 0x06
        // shl edi, 6
        _emit 0x83
        _emit 0xC7
        _emit 0x20
        // add edi, 0x20
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xD3
        // mov edx, ebx
        call FUN_008c8eb0
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x7D
        _emit 0x17
        // jge 0x8c8ff7
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0x0C
        _emit 0x8E
        // mov ecx, dword ptr [esi + ecx*4]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xD3
        // mov edx, ebx
        call FUN_008c8eb0
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x7C
        _emit 0x8F
        // jl 0x8c8f86
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x5B
        // pop ebx
        _emit 0xC3
        // ret 
    }
}
