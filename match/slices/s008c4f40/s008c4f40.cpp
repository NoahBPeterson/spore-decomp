// Slice s008c4f40: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_008c4dc0();

// @ 0x008c4f40  (986 bytes)
__declspec(naked) void FUN_008c4f40()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x38
        // sub esp, 0x38
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // mov ecx, dword ptr [esp + 0x40]
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x4C
        // mov ebx, dword ptr [esp + 0x4c]
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x4C
        // mov ebp, dword ptr [esp + 0x4c]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x48
        // mov esi, dword ptr [esp + 0x48]
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // lea eax, [esp + 0x14]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xC3
        // mov eax, ebx
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        call FUN_008c4dc0
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x89
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], edi
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x0F
        _emit 0x84
        _emit 0x87
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // je 0x8c52fe
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x5C
        // mov esi, dword ptr [esp + 0x5c]
        _emit 0x66
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov cx, word ptr [esp + 0x20]
        _emit 0xC7
        _emit 0x06
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi], 1
        _emit 0x66
        _emit 0x0F
        _emit 0xBE
        _emit 0x57
        _emit 0x14
        // movsx dx, byte ptr [edi + 0x14]
        _emit 0x0F
        _emit 0xB7
        _emit 0xC2
        // movzx eax, dx
        _emit 0x98
        // cwde 
        _emit 0x66
        _emit 0x3B
        _emit 0xCB
        // cmp cx, bx
        _emit 0x74
        _emit 0x17
        // je 0x8c4fab
        _emit 0x0F
        _emit 0xB7
        _emit 0xD3
        // movzx edx, bx
        _emit 0x0F
        _emit 0xAF
        _emit 0xC2
        // imul eax, edx
        _emit 0x0F
        _emit 0xB7
        _emit 0xC9
        // movzx ecx, cx
        _emit 0x8B
        _emit 0xD1
        // mov edx, ecx
        _emit 0xD1
        _emit 0xEA
        // shr edx, 1
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xF9
        // idiv ecx
        _emit 0x66
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov cx, word ptr [esp + 0x20]
        _emit 0x66
        _emit 0x89
        _emit 0x46
        _emit 0x04
        // mov word ptr [esi + 4], ax
        _emit 0x66
        _emit 0x0F
        _emit 0xBE
        _emit 0x47
        _emit 0x15
        // movsx ax, byte ptr [edi + 0x15]
        _emit 0x0F
        _emit 0xB7
        _emit 0xC0
        // movzx eax, ax
        _emit 0x98
        // cwde 
        _emit 0x66
        _emit 0x3B
        _emit 0xCB
        // cmp cx, bx
        _emit 0x74
        _emit 0x12
        // je 0x8c4fcf
        _emit 0x0F
        _emit 0xB7
        _emit 0xD3
        // movzx edx, bx
        _emit 0x0F
        _emit 0xAF
        _emit 0xC2
        // imul eax, edx
        _emit 0x0F
        _emit 0xB7
        _emit 0xC9
        // movzx ecx, cx
        _emit 0x8B
        _emit 0xD1
        // mov edx, ecx
        _emit 0xD1
        _emit 0xEA
        // shr edx, 1
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xF9
        // idiv ecx
        _emit 0x66
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x1E
        // mov bx, word ptr [esp + 0x1e]
        _emit 0x66
        _emit 0x89
        _emit 0x46
        _emit 0x06
        // mov word ptr [esi + 6], ax
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x66
        _emit 0x89
        _emit 0x46
        _emit 0x08
        // mov word ptr [esi + 8], ax
        _emit 0x66
        _emit 0x0F
        _emit 0xB6
        _emit 0x4F
        _emit 0x16
        // movzx cx, byte ptr [edi + 0x16]
        _emit 0x0F
        _emit 0xB7
        _emit 0xC1
        // movzx eax, cx
        _emit 0x98
        // cwde 
        _emit 0x66
        _emit 0x3B
        _emit 0xDD
        // cmp bx, bp
        _emit 0x74
        _emit 0x12
        // je 0x8c4ffe
        _emit 0x0F
        _emit 0xB7
        _emit 0xD5
        // movzx edx, bp
        _emit 0x0F
        _emit 0xAF
        _emit 0xC2
        // imul eax, edx
        _emit 0x0F
        _emit 0xB7
        _emit 0xCB
        // movzx ecx, bx
        _emit 0x8B
        _emit 0xD1
        // mov edx, ecx
        _emit 0xD1
        _emit 0xEA
        // shr edx, 1
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xF9
        // idiv ecx
        _emit 0x66
        _emit 0x89
        _emit 0x46
        _emit 0x0A
        // mov word ptr [esi + 0xa], ax
        _emit 0x66
        _emit 0x0F
        _emit 0xBE
        _emit 0x47
        _emit 0x17
        // movsx ax, byte ptr [edi + 0x17]
        _emit 0x0F
        _emit 0xB7
        _emit 0xC0
        // movzx eax, ax
        _emit 0x98
        // cwde 
        _emit 0x66
        _emit 0x3B
        _emit 0xDD
        // cmp bx, bp
        _emit 0x74
        _emit 0x12
        // je 0x8c5022
        _emit 0x0F
        _emit 0xB7
        _emit 0xD5
        // movzx edx, bp
        _emit 0x0F
        _emit 0xAF
        _emit 0xC2
        // imul eax, edx
        _emit 0x0F
        _emit 0xB7
        _emit 0xCB
        // movzx ecx, bx
        _emit 0x8B
        _emit 0xD1
        // mov edx, ecx
        _emit 0xD1
        _emit 0xEA
        // shr edx, 1
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xF9
        // idiv ecx
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x58
        // mov edx, dword ptr [esp + 0x58]
        _emit 0x98
        // cwde 
        _emit 0x89
        _emit 0x46
        _emit 0x10
        // mov dword ptr [esi + 0x10], eax
        _emit 0x0F
        _emit 0xBE
        _emit 0x4F
        _emit 0x18
        // movsx ecx, byte ptr [edi + 0x18]
        _emit 0x0F
        _emit 0xB7
        _emit 0xC1
        // movzx eax, cx
        _emit 0x66
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov cx, word ptr [esp + 0x20]
        _emit 0x98
        // cwde 
        _emit 0x66
        _emit 0x3B
        _emit 0xCA
        // cmp cx, dx
        _emit 0x74
        _emit 0x12
        // je 0x8c504e
        _emit 0x0F
        _emit 0xB7
        _emit 0xD2
        // movzx edx, dx
        _emit 0x0F
        _emit 0xAF
        _emit 0xC2
        // imul eax, edx
        _emit 0x0F
        _emit 0xB7
        _emit 0xC9
        // movzx ecx, cx
        _emit 0x8B
        _emit 0xD1
        // mov edx, ecx
        _emit 0xD1
        _emit 0xEA
        // shr edx, 1
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xF9
        // idiv ecx
        _emit 0x98
        // cwde 
        _emit 0x89
        _emit 0x46
        _emit 0x0C
        // mov dword ptr [esi + 0xc], eax
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0xEB
        _emit 0x0A
        // jmp 0x8c5060
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0x8B
        _emit 0x46
        _emit 0x0C
        // mov eax, dword ptr [esi + 0xc]
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp eax, 0x10000
        _emit 0x0F
        _emit 0x8D
        _emit 0xB4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jge 0x8c5122
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp eax, 0xffff0000
        _emit 0x0F
        _emit 0x8E
        _emit 0xA9
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jle 0x8c5122
        _emit 0x8B
        _emit 0x4E
        _emit 0x10
        // mov ecx, dword ptr [esi + 0x10]
        _emit 0x81
        _emit 0xF9
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp ecx, 0x10000
        _emit 0x0F
        _emit 0x8D
        _emit 0x9A
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jge 0x8c5122
        _emit 0x81
        _emit 0xF9
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp ecx, 0xffff0000
        _emit 0x0F
        _emit 0x8E
        _emit 0x8E
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jle 0x8c5122
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xC9
        // add ecx, ecx
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp eax, 0x10000
        _emit 0x89
        _emit 0x46
        _emit 0x0C
        // mov dword ptr [esi + 0xc], eax
        _emit 0x89
        _emit 0x4E
        _emit 0x10
        // mov dword ptr [esi + 0x10], ecx
        _emit 0x7D
        _emit 0x7D
        // jge 0x8c5122
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp eax, 0xffff0000
        _emit 0x7E
        _emit 0x76
        // jle 0x8c5122
        _emit 0x81
        _emit 0xF9
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp ecx, 0x10000
        _emit 0x7D
        _emit 0x6E
        // jge 0x8c5122
        _emit 0x81
        _emit 0xF9
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp ecx, 0xffff0000
        _emit 0x7E
        _emit 0x66
        // jle 0x8c5122
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xC9
        // add ecx, ecx
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp eax, 0x10000
        _emit 0x89
        _emit 0x46
        _emit 0x0C
        // mov dword ptr [esi + 0xc], eax
        _emit 0x89
        _emit 0x4E
        _emit 0x10
        // mov dword ptr [esi + 0x10], ecx
        _emit 0x7D
        _emit 0x55
        // jge 0x8c5122
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp eax, 0xffff0000
        _emit 0x7E
        _emit 0x4E
        // jle 0x8c5122
        _emit 0x81
        _emit 0xF9
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp ecx, 0x10000
        _emit 0x7D
        _emit 0x46
        // jge 0x8c5122
        _emit 0x81
        _emit 0xF9
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp ecx, 0xffff0000
        _emit 0x7E
        _emit 0x3E
        // jle 0x8c5122
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xC9
        // add ecx, ecx
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp eax, 0x10000
        _emit 0x89
        _emit 0x46
        _emit 0x0C
        // mov dword ptr [esi + 0xc], eax
        _emit 0x89
        _emit 0x4E
        _emit 0x10
        // mov dword ptr [esi + 0x10], ecx
        _emit 0x7D
        _emit 0x2D
        // jge 0x8c5122
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp eax, 0xffff0000
        _emit 0x7E
        _emit 0x26
        // jle 0x8c5122
        _emit 0x81
        _emit 0xF9
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp ecx, 0x10000
        _emit 0x7D
        _emit 0x1E
        // jge 0x8c5122
        _emit 0x81
        _emit 0xF9
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp ecx, 0xffff0000
        _emit 0x7E
        _emit 0x16
        // jle 0x8c5122
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xC9
        // add ecx, ecx
        _emit 0x83
        _emit 0xC2
        _emit 0x04
        // add edx, 4
        _emit 0x83
        _emit 0xFA
        _emit 0x10
        // cmp edx, 0x10
        _emit 0x89
        _emit 0x46
        _emit 0x0C
        // mov dword ptr [esi + 0xc], eax
        _emit 0x89
        _emit 0x4E
        _emit 0x10
        // mov dword ptr [esi + 0x10], ecx
        _emit 0x0F
        _emit 0x8C
        _emit 0x3E
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jl 0x8c5060
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x60
        // mov ecx, dword ptr [esp + 0x60]
        _emit 0xC7
        _emit 0x01
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ecx], 1
        _emit 0x66
        _emit 0x0F
        _emit 0xBE
        _emit 0x57
        _emit 0x20
        // movsx dx, byte ptr [edi + 0x20]
        _emit 0x0F
        _emit 0xB7
        _emit 0xC2
        // movzx eax, dx
        _emit 0x98
        // cwde 
        _emit 0x66
        _emit 0x3B
        _emit 0xDD
        // cmp bx, bp
        _emit 0x74
        _emit 0x16
        // je 0x8c5150
        _emit 0x0F
        _emit 0xB7
        _emit 0xD5
        // movzx edx, bp
        _emit 0x0F
        _emit 0xAF
        _emit 0xC2
        // imul eax, edx
        _emit 0x0F
        _emit 0xB7
        _emit 0xFB
        // movzx edi, bx
        _emit 0x8B
        _emit 0xD7
        // mov edx, edi
        _emit 0xD1
        _emit 0xEA
        // shr edx, 1
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xFF
        // idiv edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        // mov edi, dword ptr [esp + 0x10]
        _emit 0x66
        _emit 0x89
        _emit 0x41
        _emit 0x04
        // mov word ptr [ecx + 4], ax
        _emit 0x66
        _emit 0x0F
        _emit 0xBE
        _emit 0x47
        _emit 0x21
        // movsx ax, byte ptr [edi + 0x21]
        _emit 0x0F
        _emit 0xB7
        _emit 0xC0
        // movzx eax, ax
        _emit 0x98
        // cwde 
        _emit 0x66
        _emit 0x3B
        _emit 0xDD
        // cmp bx, bp
        _emit 0x74
        _emit 0x16
        // je 0x8c5178
        _emit 0x0F
        _emit 0xB7
        _emit 0xD5
        // movzx edx, bp
        _emit 0x0F
        _emit 0xAF
        _emit 0xC2
        // imul eax, edx
        _emit 0x0F
        _emit 0xB7
        _emit 0xFB
        // movzx edi, bx
        _emit 0x8B
        _emit 0xD7
        // mov edx, edi
        _emit 0xD1
        _emit 0xEA
        // shr edx, 1
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xFF
        // idiv edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        // mov edi, dword ptr [esp + 0x10]
        _emit 0x66
        _emit 0x89
        _emit 0x41
        _emit 0x06
        // mov word ptr [ecx + 6], ax
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x66
        _emit 0x89
        _emit 0x41
        _emit 0x08
        // mov word ptr [ecx + 8], ax
        _emit 0x0F
        _emit 0xB6
        _emit 0x57
        _emit 0x22
        // movzx edx, byte ptr [edi + 0x22]
        _emit 0x0F
        _emit 0xB7
        _emit 0xC2
        // movzx eax, dx
        _emit 0x66
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov dx, word ptr [esp + 0x20]
        _emit 0x98
        // cwde 
        _emit 0x66
        _emit 0x3B
        _emit 0x54
        _emit 0x24
        _emit 0x58
        // cmp dx, word ptr [esp + 0x58]
        _emit 0x74
        _emit 0x19
        // je 0x8c51af
        _emit 0x0F
        _emit 0xB7
        _emit 0xFA
        // movzx edi, dx
        _emit 0x0F
        _emit 0xB7
        _emit 0x54
        _emit 0x24
        _emit 0x58
        // movzx edx, word ptr [esp + 0x58]
        _emit 0x0F
        _emit 0xAF
        _emit 0xC2
        // imul eax, edx
        _emit 0x8B
        _emit 0xD7
        // mov edx, edi
        _emit 0xD1
        _emit 0xEA
        // shr edx, 1
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xFF
        // idiv edi
        _emit 0x66
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov dx, word ptr [esp + 0x20]
        _emit 0x66
        _emit 0x89
        _emit 0x41
        _emit 0x0A
        // mov word ptr [ecx + 0xa], ax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0x66
        _emit 0x0F
        _emit 0xBE
        _emit 0x40
        _emit 0x24
        // movsx ax, byte ptr [eax + 0x24]
        _emit 0x0F
        _emit 0xB7
        _emit 0xC0
        // movzx eax, ax
        _emit 0x98
        // cwde 
        _emit 0x66
        _emit 0x3B
        _emit 0xDD
        // cmp bx, bp
        _emit 0x74
        _emit 0x17
        // je 0x8c51dc
        _emit 0x0F
        _emit 0xB7
        _emit 0xD5
        // movzx edx, bp
        _emit 0x0F
        _emit 0xAF
        _emit 0xC2
        // imul eax, edx
        _emit 0x0F
        _emit 0xB7
        _emit 0xFB
        // movzx edi, bx
        _emit 0x8B
        _emit 0xD7
        // mov edx, edi
        _emit 0xD1
        _emit 0xEA
        // shr edx, 1
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xFF
        // idiv edi
        _emit 0x66
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov dx, word ptr [esp + 0x20]
        _emit 0x98
        // cwde 
        _emit 0x89
        _emit 0x41
        _emit 0x0C
        // mov dword ptr [ecx + 0xc], eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov eax, dword ptr [esp + 0x10]
        _emit 0x66
        _emit 0x0F
        _emit 0xBE
        _emit 0x40
        _emit 0x23
        // movsx ax, byte ptr [eax + 0x23]
        _emit 0x0F
        _emit 0xB7
        _emit 0xC0
        // movzx eax, ax
        _emit 0x98
        // cwde 
        _emit 0x66
        _emit 0x3B
        _emit 0x54
        _emit 0x24
        _emit 0x58
        // cmp dx, word ptr [esp + 0x58]
        _emit 0x74
        _emit 0x14
        // je 0x8c5208
        _emit 0x0F
        _emit 0xB7
        _emit 0xFA
        // movzx edi, dx
        _emit 0x0F
        _emit 0xB7
        _emit 0x54
        _emit 0x24
        _emit 0x58
        // movzx edx, word ptr [esp + 0x58]
        _emit 0x0F
        _emit 0xAF
        _emit 0xC2
        // imul eax, edx
        _emit 0x8B
        _emit 0xD7
        // mov edx, edi
        _emit 0xD1
        _emit 0xEA
        // shr edx, 1
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x99
        // cdq 
        _emit 0xF7
        _emit 0xFF
        // idiv edi
        _emit 0x98
        // cwde 
        _emit 0x89
        _emit 0x41
        _emit 0x10
        // mov dword ptr [ecx + 0x10], eax
        _emit 0x33
        _emit 0xFF
        // xor edi, edi
        _emit 0x8B
        _emit 0xFF
        // mov edi, edi
        _emit 0x8B
        _emit 0x41
        _emit 0x0C
        // mov eax, dword ptr [ecx + 0xc]
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp eax, 0x10000
        _emit 0x0F
        _emit 0x8D
        _emit 0xB4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jge 0x8c52d2
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp eax, 0xffff0000
        _emit 0x0F
        _emit 0x8E
        _emit 0xA9
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jle 0x8c52d2
        _emit 0x8B
        _emit 0x51
        _emit 0x10
        // mov edx, dword ptr [ecx + 0x10]
        _emit 0x81
        _emit 0xFA
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp edx, 0x10000
        _emit 0x0F
        _emit 0x8D
        _emit 0x9A
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jge 0x8c52d2
        _emit 0x81
        _emit 0xFA
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp edx, 0xffff0000
        _emit 0x0F
        _emit 0x8E
        _emit 0x8E
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jle 0x8c52d2
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xD2
        // add edx, edx
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp eax, 0x10000
        _emit 0x89
        _emit 0x41
        _emit 0x0C
        // mov dword ptr [ecx + 0xc], eax
        _emit 0x89
        _emit 0x51
        _emit 0x10
        // mov dword ptr [ecx + 0x10], edx
        _emit 0x7D
        _emit 0x7D
        // jge 0x8c52d2
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp eax, 0xffff0000
        _emit 0x7E
        _emit 0x76
        // jle 0x8c52d2
        _emit 0x81
        _emit 0xFA
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp edx, 0x10000
        _emit 0x7D
        _emit 0x6E
        // jge 0x8c52d2
        _emit 0x81
        _emit 0xFA
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp edx, 0xffff0000
        _emit 0x7E
        _emit 0x66
        // jle 0x8c52d2
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xD2
        // add edx, edx
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp eax, 0x10000
        _emit 0x89
        _emit 0x41
        _emit 0x0C
        // mov dword ptr [ecx + 0xc], eax
        _emit 0x89
        _emit 0x51
        _emit 0x10
        // mov dword ptr [ecx + 0x10], edx
        _emit 0x7D
        _emit 0x55
        // jge 0x8c52d2
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp eax, 0xffff0000
        _emit 0x7E
        _emit 0x4E
        // jle 0x8c52d2
        _emit 0x81
        _emit 0xFA
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp edx, 0x10000
        _emit 0x7D
        _emit 0x46
        // jge 0x8c52d2
        _emit 0x81
        _emit 0xFA
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp edx, 0xffff0000
        _emit 0x7E
        _emit 0x3E
        // jle 0x8c52d2
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xD2
        // add edx, edx
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp eax, 0x10000
        _emit 0x89
        _emit 0x41
        _emit 0x0C
        // mov dword ptr [ecx + 0xc], eax
        _emit 0x89
        _emit 0x51
        _emit 0x10
        // mov dword ptr [ecx + 0x10], edx
        _emit 0x7D
        _emit 0x2D
        // jge 0x8c52d2
        _emit 0x3D
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp eax, 0xffff0000
        _emit 0x7E
        _emit 0x26
        // jle 0x8c52d2
        _emit 0x81
        _emit 0xFA
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        // cmp edx, 0x10000
        _emit 0x7D
        _emit 0x1E
        // jge 0x8c52d2
        _emit 0x81
        _emit 0xFA
        _emit 0x00
        _emit 0x00
        _emit 0xFF
        _emit 0xFF
        // cmp edx, 0xffff0000
        _emit 0x7E
        _emit 0x16
        // jle 0x8c52d2
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xD2
        // add edx, edx
        _emit 0x83
        _emit 0xC7
        _emit 0x04
        // add edi, 4
        _emit 0x83
        _emit 0xFF
        _emit 0x10
        // cmp edi, 0x10
        _emit 0x89
        _emit 0x41
        _emit 0x0C
        // mov dword ptr [ecx + 0xc], eax
        _emit 0x89
        _emit 0x51
        _emit 0x10
        // mov dword ptr [ecx + 0x10], edx
        _emit 0x0F
        _emit 0x8C
        _emit 0x3E
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jl 0x8c5210
        _emit 0x0F
        _emit 0xB7
        _emit 0x46
        _emit 0x06
        // movzx eax, word ptr [esi + 6]
        _emit 0x66
        _emit 0x85
        _emit 0xC0
        // test ax, ax
        _emit 0x7E
        _emit 0x37
        // jle 0x8c5312
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov edx, dword ptr [esp + 0x10]
        _emit 0x80
        _emit 0x7A
        _emit 0x1D
        _emit 0x00
        // cmp byte ptr [edx + 0x1d], 0
        _emit 0x7D
        _emit 0x2D
        // jge 0x8c5312
        _emit 0xF7
        _emit 0xD8
        // neg eax
        _emit 0x66
        _emit 0x89
        _emit 0x46
        _emit 0x06
        // mov word ptr [esi + 6], ax
        _emit 0x66
        _emit 0x8B
        _emit 0x41
        _emit 0x06
        // mov ax, word ptr [ecx + 6]
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x66
        _emit 0xF7
        _emit 0xD8
        // neg ax
        _emit 0x5D
        // pop ebp
        _emit 0x66
        _emit 0x89
        _emit 0x41
        _emit 0x06
        // mov word ptr [ecx + 6], ax
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x38
        // add esp, 0x38
        _emit 0xC3
        // ret 
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x5C
        // mov ecx, dword ptr [esp + 0x5c]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x60
        // mov edx, dword ptr [esp + 0x60]
        _emit 0xC7
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ecx], 0
        _emit 0xC7
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edx], 0
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
        _emit 0x38
        // add esp, 0x38
        _emit 0xC3
        // ret 
    }
}

// @ 0x008c5320  (424 bytes)
__declspec(naked) void FUN_008c5320()
{
    __asm {
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov eax, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x24
        // mov ebp, dword ptr [esp + 0x24]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x10
        // mov esi, dword ptr [esp + 0x10]
        _emit 0x55
        // push ebp
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // mov eax, dword ptr [esp + 0x2c]
        call FUN_008c4dc0
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x33
        _emit 0xC9
        // xor ecx, ecx
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x08
        // mov dword ptr [esp + 8], esi
        _emit 0x3B
        _emit 0xC6
        // cmp eax, esi
        _emit 0x0F
        _emit 0x84
        _emit 0x43
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0x8c5494
        _emit 0x66
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // mov dx, word ptr [esp + 0x1c]
        _emit 0x66
        _emit 0x3B
        _emit 0x50
        _emit 0x2C
        // cmp dx, word ptr [eax + 0x2c]
        _emit 0x0F
        _emit 0x82
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jb 0x8c5494
        _emit 0x66
        _emit 0x3B
        _emit 0x50
        _emit 0x2E
        // cmp dx, word ptr [eax + 0x2e]
        _emit 0x0F
        _emit 0x87
        _emit 0x2A
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // ja 0x8c5494
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x58
        _emit 0x0C
        // mov ebx, dword ptr [eax + 0xc]
        _emit 0x3B
        _emit 0xDE
        // cmp ebx, esi
        _emit 0x0F
        _emit 0x8E
        _emit 0x1D
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jle 0x8c5493
        _emit 0x8B
        _emit 0x50
        _emit 0x34
        // mov edx, dword ptr [eax + 0x34]
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebx, [ebx]
        _emit 0x0F
        _emit 0xB7
        _emit 0x3A
        // movzx edi, word ptr [edx]
        _emit 0x66
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x24
        // mov bp, word ptr [esp + 0x24]
        _emit 0x66
        _emit 0x3B
        _emit 0xEF
        // cmp bp, di
        _emit 0x72
        _emit 0x06
        // jb 0x8c5393
        _emit 0x66
        _emit 0x3B
        _emit 0x6A
        _emit 0x02
        // cmp bp, word ptr [edx + 2]
        _emit 0x76
        _emit 0x11
        // jbe 0x8c53a4
        _emit 0x46
        // inc esi
        _emit 0x83
        _emit 0xC2
        _emit 0x08
        // add edx, 8
        _emit 0x3B
        _emit 0xF3
        // cmp esi, ebx
        _emit 0x7C
        _emit 0xE5
        // jl 0x8c5380
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x30
        // mov ebp, dword ptr [esp + 0x30]
        _emit 0xE9
        _emit 0xEE
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jmp 0x8c5492
        _emit 0x0F
        _emit 0xB6
        _emit 0x50
        _emit 0x32
        // movzx edx, byte ptr [eax + 0x32]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x30
        // mov ebp, dword ptr [esp + 0x30]
        _emit 0x88
        _emit 0x55
        _emit 0x0F
        // mov byte ptr [ebp + 0xf], dl
        _emit 0x0F
        _emit 0xB6
        _emit 0x50
        _emit 0x32
        // movzx edx, byte ptr [eax + 0x32]
        _emit 0x88
        _emit 0x55
        _emit 0x0E
        // mov byte ptr [ebp + 0xe], dl
        _emit 0x0F
        _emit 0xB6
        _emit 0x50
        _emit 0x33
        // movzx edx, byte ptr [eax + 0x33]
        _emit 0x88
        _emit 0x55
        _emit 0x10
        // mov byte ptr [ebp + 0x10], dl
        _emit 0x8B
        _emit 0x50
        _emit 0x34
        // mov edx, dword ptr [eax + 0x34]
        _emit 0x8B
        _emit 0x54
        _emit 0xF2
        _emit 0x04
        // mov edx, dword ptr [edx + esi*8 + 4]
        _emit 0x0F
        _emit 0xB7
        _emit 0x5A
        _emit 0x02
        // movzx ebx, word ptr [edx + 2]
        _emit 0x0F
        _emit 0xB7
        _emit 0x12
        // movzx edx, word ptr [edx]
        _emit 0x4A
        // dec edx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ebx
        _emit 0x83
        _emit 0xFA
        _emit 0x04
        // cmp edx, 4
        _emit 0x0F
        _emit 0x87
        _emit 0xB9
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // ja 0x8c5492
        _emit 0xFF
        _emit 0x24
        _emit 0x95
        _emit 0xB4
        _emit 0x54
        _emit 0x8C
        _emit 0x00
        // jmp dword ptr [edx*4 + 0x8c54b4]
        _emit 0x0F
        _emit 0xB7
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // movzx edx, word ptr [esp + 0x24]
        _emit 0x8B
        _emit 0x40
        _emit 0x34
        // mov eax, dword ptr [eax + 0x34]
        _emit 0x0F
        _emit 0xB7
        _emit 0xCF
        // movzx ecx, di
        _emit 0x2B
        _emit 0xD1
        // sub edx, ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0xF0
        _emit 0x04
        // mov ecx, dword ptr [eax + esi*8 + 4]
        _emit 0x8B
        _emit 0x41
        _emit 0x08
        // mov eax, dword ptr [ecx + 8]
        _emit 0x8B
        _emit 0x0C
        _emit 0x90
        // mov ecx, dword ptr [eax + edx*4]
        _emit 0xE9
        _emit 0x96
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jmp 0x8c5492
        _emit 0x8B
        _emit 0x48
        _emit 0x34
        // mov ecx, dword ptr [eax + 0x34]
        _emit 0x8B
        _emit 0x74
        _emit 0xF1
        _emit 0x04
        // mov esi, dword ptr [ecx + esi*8 + 4]
        _emit 0x0F
        _emit 0xB7
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // movzx ecx, word ptr [esp + 0x24]
        _emit 0x0F
        _emit 0xB7
        _emit 0xD7
        // movzx edx, di
        _emit 0x2B
        _emit 0xCA
        // sub ecx, edx
        _emit 0x0F
        _emit 0xAF
        _emit 0x4E
        _emit 0x08
        // imul ecx, dword ptr [esi + 8]
        _emit 0x8B
        _emit 0x56
        _emit 0x0C
        // mov edx, dword ptr [esi + 0xc]
        _emit 0x03
        _emit 0x4E
        _emit 0x04
        // add ecx, dword ptr [esi + 4]
        _emit 0x8D
        _emit 0x46
        _emit 0x0C
        // lea eax, [esi + 0xc]
        _emit 0x89
        _emit 0x55
        _emit 0x14
        // mov dword ptr [ebp + 0x14], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0x89
        _emit 0x55
        _emit 0x18
        // mov dword ptr [ebp + 0x18], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x08
        // mov edx, dword ptr [eax + 8]
        _emit 0x89
        _emit 0x55
        _emit 0x1C
        // mov dword ptr [ebp + 0x1c], edx
        _emit 0x8B
        _emit 0x40
        _emit 0x0C
        // mov eax, dword ptr [eax + 0xc]
        _emit 0x89
        _emit 0x45
        _emit 0x20
        // mov dword ptr [ebp + 0x20], eax
        _emit 0xEB
        _emit 0x61
        // jmp 0x8c5492
        _emit 0x8B
        _emit 0x50
        _emit 0x34
        // mov edx, dword ptr [eax + 0x34]
        _emit 0x8B
        _emit 0x74
        _emit 0xF2
        _emit 0x04
        // mov esi, dword ptr [edx + esi*8 + 4]
        _emit 0x8B
        _emit 0x56
        _emit 0x08
        // mov edx, dword ptr [esi + 8]
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x85
        _emit 0xD2
        // test edx, edx
        _emit 0x76
        _emit 0x51
        // jbe 0x8c5492
        _emit 0x8B
        _emit 0x7E
        _emit 0x0C
        // mov edi, dword ptr [esi + 0xc]
        _emit 0x66
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // mov bx, word ptr [esp + 0x24]
        _emit 0x66
        _emit 0x3B
        _emit 0x1F
        // cmp bx, word ptr [edi]
        _emit 0x74
        _emit 0x0A
        // je 0x8c5458
        _emit 0x40
        // inc eax
        _emit 0x83
        _emit 0xC7
        _emit 0x04
        // add edi, 4
        _emit 0x3B
        _emit 0xC2
        // cmp eax, edx
        _emit 0x72
        _emit 0xEE
        // jb 0x8c5444
        _emit 0xEB
        _emit 0x3A
        // jmp 0x8c5492
        _emit 0x8B
        _emit 0x4E
        _emit 0x0C
        // mov ecx, dword ptr [esi + 0xc]
        _emit 0x0F
        _emit 0xB7
        _emit 0x4C
        _emit 0x81
        _emit 0x02
        // movzx ecx, word ptr [ecx + eax*4 + 2]
        _emit 0xEB
        _emit 0x2D
        // jmp 0x8c548f
        _emit 0x8B
        _emit 0x40
        _emit 0x34
        // mov eax, dword ptr [eax + 0x34]
        _emit 0x8B
        _emit 0x74
        _emit 0xF0
        _emit 0x04
        // mov esi, dword ptr [eax + esi*8 + 4]
        _emit 0x8B
        _emit 0x56
        _emit 0x1C
        // mov edx, dword ptr [esi + 0x1c]
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x85
        _emit 0xD2
        // test edx, edx
        _emit 0x76
        _emit 0x20
        // jbe 0x8c5492
        _emit 0x8B
        _emit 0x7E
        _emit 0x20
        // mov edi, dword ptr [esi + 0x20]
        _emit 0x66
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // mov bx, word ptr [esp + 0x24]
        _emit 0x66
        _emit 0x39
        _emit 0x1F
        // cmp word ptr [edi], bx
        _emit 0x74
        _emit 0x0A
        // je 0x8c5489
        _emit 0x40
        // inc eax
        _emit 0x83
        _emit 0xC7
        _emit 0x02
        // add edi, 2
        _emit 0x3B
        _emit 0xC2
        // cmp eax, edx
        _emit 0x72
        _emit 0xEE
        // jb 0x8c5475
        _emit 0xEB
        _emit 0x09
        // jmp 0x8c5492
        _emit 0x8B
        _emit 0x4E
        _emit 0x08
        // mov ecx, dword ptr [esi + 8]
        _emit 0x0F
        _emit 0xAF
        _emit 0xC8
        // imul ecx, eax
        _emit 0x03
        _emit 0x4E
        _emit 0x04
        // add ecx, dword ptr [esi + 4]
        _emit 0x5F
        // pop edi
        _emit 0x5B
        // pop ebx
        _emit 0x66
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov ax, word ptr [esp + 0x1c]
        _emit 0x66
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // mov dx, word ptr [esp + 8]
        _emit 0x66
        _emit 0x89
        _emit 0x45
        _emit 0x04
        // mov word ptr [ebp + 4], ax
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x5E
        // pop esi
        _emit 0x89
        _emit 0x4D
        _emit 0x00
        // mov dword ptr [ebp], ecx
        _emit 0x66
        _emit 0x89
        _emit 0x55
        _emit 0x12
        // mov word ptr [ebp + 0x12], dx
        _emit 0x0F
        _emit 0x95
        _emit 0xC0
        // setne al
        _emit 0x5D
        // pop ebp
        _emit 0x59
        // pop ecx
        _emit 0xC3
        // ret 
        _emit 0xE0
        _emit 0x53
        // loopne 0x8c5509
        _emit 0x8C
        _emit 0x00
        // mov word ptr [eax], es
        _emit 0xFC
        // cld 
        _emit 0x53
        // push ebx
        _emit 0x8C
        _emit 0x00
        // mov word ptr [eax], es
        _emit 0xE0
        _emit 0x53
        // loopne 0x8c5511
        _emit 0x8C
        _emit 0x00
        // mov word ptr [eax], es
        _emit 0x31
        _emit 0x54
        _emit 0x8C
        _emit 0x00
        // xor dword ptr [esp + ecx*4], edx
        _emit 0x62
        _emit 0x54
        _emit 0x8C
        _emit 0x00
        // bound edx, qword ptr [esp + ecx*4]
    }
}
