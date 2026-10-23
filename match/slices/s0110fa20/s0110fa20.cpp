// Slice s0110fa20: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_0110cd00();
extern "C" void FUN_0110e510();
extern "C" void FUN_0110fc50();

// @ 0x0110fa20  (555 bytes)
__declspec(naked) void FUN_0110fa20()
{
    __asm {
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0xEC
        // mov ebp, esp
        _emit 0x83
        _emit 0xE4
        _emit 0xF0
        // and esp, 0xfffffff0
        _emit 0x81
        _emit 0xEC
        _emit 0x94
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // sub esp, 0x194
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x75
        _emit 0x08
        // mov esi, dword ptr [ebp + 8]
        _emit 0x8B
        _emit 0x4E
        _emit 0x08
        // mov ecx, dword ptr [esi + 8]
        _emit 0x8B
        _emit 0x5E
        _emit 0x0C
        // mov ebx, dword ptr [esi + 0xc]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7D
        _emit 0x0C
        // mov edi, dword ptr [ebp + 0xc]
        _emit 0x0F
        _emit 0xBE
        _emit 0x57
        _emit 0x09
        // movsx edx, byte ptr [edi + 9]
        _emit 0x0F
        _emit 0xBE
        _emit 0x47
        _emit 0x08
        // movsx eax, byte ptr [edi + 8]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], edx
        _emit 0x0F
        _emit 0xBE
        _emit 0x57
        _emit 0x0B
        // movsx edx, byte ptr [edi + 0xb]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], edx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], eax
        _emit 0x0F
        _emit 0xBE
        _emit 0x47
        _emit 0x0A
        // movsx eax, byte ptr [edi + 0xa]
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x40
        // lea edx, [esp + 0x40]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // mov edx, dword ptr [esp + 0x24]
        _emit 0x52
        // push edx
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x38
        _emit 0x00
        // mov byte ptr [esp + 0x38], 0
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // mov dword ptr [esp + 0x30], eax
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x3c], 0
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x57
        // push edi
        _emit 0xFF
        _emit 0x50
        _emit 0x28
        // call dword ptr [eax + 0x28]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // mov edx, dword ptr [esp + 0x24]
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x8D
        _emit 0x8C
        _emit 0x24
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea ecx, [esp + 0x100]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // mov ecx, dword ptr [esp + 0x24]
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x14
        _emit 0x4F
        // lea edx, [edi + ecx*2]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0x50
        _emit 0x28
        // call dword ptr [eax + 0x28]
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0x56
        _emit 0x0C
        // mov edx, dword ptr [esi + 0xc]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // lea eax, [esp + 0x10]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x46
        _emit 0x08
        // mov eax, dword ptr [esi + 8]
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x30
        // lea ecx, [esp + 0x30]
        call FUN_0110e510
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // mov eax, dword ptr [esp + 0x34]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x74
        _emit 0x0A
        // je 0x110fac1
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // lea ecx, [esp + 0x24]
        call FUN_0110cd00
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x4E
        _emit 0x08
        // mov ecx, dword ptr [esi + 8]
        _emit 0xD8
        _emit 0x61
        _emit 0x0C
        // fsub dword ptr [ecx + 0xc]
        _emit 0x8B
        _emit 0x56
        _emit 0x0C
        // mov edx, dword ptr [esi + 0xc]
        _emit 0x8B
        _emit 0x4D
        _emit 0x10
        // mov ecx, dword ptr [ebp + 0x10]
        _emit 0xD8
        _emit 0x62
        _emit 0x0C
        // fsub dword ptr [edx + 0xc]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x48
        _emit 0x20
        // fmul dword ptr [eax + 0x20]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x48
        _emit 0x10
        // fmul dword ptr [eax + 0x10]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xD8
        _emit 0x08
        // fmul dword ptr [eax]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x19
        // fstp dword ptr [ecx]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x48
        _emit 0x24
        // fmul dword ptr [eax + 0x24]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x48
        _emit 0x14
        // fmul dword ptr [eax + 0x14]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xD8
        _emit 0x48
        _emit 0x04
        // fmul dword ptr [eax + 4]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x59
        _emit 0x04
        // fstp dword ptr [ecx + 4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x48
        _emit 0x28
        // fmul dword ptr [eax + 0x28]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x48
        _emit 0x18
        // fmul dword ptr [eax + 0x18]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xD8
        _emit 0x48
        _emit 0x08
        // fmul dword ptr [eax + 8]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x59
        _emit 0x08
        // fstp dword ptr [ecx + 8]
        _emit 0x89
        _emit 0x59
        _emit 0x0C
        // mov dword ptr [ecx + 0xc], ebx
        _emit 0xD9
        _emit 0x51
        _emit 0x0C
        // fst dword ptr [ecx + 0xc]
        _emit 0xD8
        _emit 0x5E
        _emit 0x10
        // fcomp dword ptr [esi + 0x10]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0xB8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 1
        _emit 0x0F
        _emit 0x8A
        _emit 0x02
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jp 0x110fc44
        _emit 0x39
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // cmp dword ptr [esp + 0x20], eax
        _emit 0x75
        _emit 0x34
        // jne 0x110fb7c
        _emit 0x8B
        _emit 0x46
        _emit 0x0C
        // mov eax, dword ptr [esi + 0xc]
        _emit 0xD9
        _emit 0x40
        _emit 0x0C
        // fld dword ptr [eax + 0xc]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x1C
        // fsub dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // fstp dword ptr [esp + 0xc]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // fadd dword ptr [esp + 0x40]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // fadd dword ptr [esp + 0x44]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // fadd dword ptr [esp + 0x48]
        _emit 0xEB
        _emit 0x76
        // jmp 0x110fbf2
        _emit 0x39
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // cmp dword ptr [esp + 0x24], eax
        _emit 0x75
        _emit 0x39
        // jne 0x110fbbb
        _emit 0x8B
        _emit 0x4E
        _emit 0x0C
        // mov ecx, dword ptr [esi + 0xc]
        _emit 0x8B
        _emit 0x51
        _emit 0x0C
        // mov edx, dword ptr [ecx + 0xc]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], edx
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // fmul dword ptr [esp + 0x10]
        _emit 0xD8
        _emit 0x84
        _emit 0x24
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fadd dword ptr [esp + 0xc0]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0xD8
        _emit 0x84
        _emit 0x24
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fadd dword ptr [esp + 0xc4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0xD8
        _emit 0x84
        _emit 0x24
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fadd dword ptr [esp + 0xc8]
        _emit 0xEB
        _emit 0x37
        // jmp 0x110fbf2
        _emit 0x8B
        _emit 0x46
        _emit 0x0C
        // mov eax, dword ptr [esi + 0xc]
        _emit 0xD9
        _emit 0x40
        _emit 0x0C
        // fld dword ptr [eax + 0xc]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x1C
        // fsub dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // fst dword ptr [esp + 0xc]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // fmul dword ptr [esp + 0x10]
        _emit 0xD8
        _emit 0x84
        _emit 0x24
        _emit 0x50
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fadd dword ptr [esp + 0x150]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0xD8
        _emit 0x84
        _emit 0x24
        _emit 0x54
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fadd dword ptr [esp + 0x154]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0xD8
        _emit 0x84
        _emit 0x24
        _emit 0x58
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fadd dword ptr [esp + 0x158]
        _emit 0x8B
        _emit 0x76
        _emit 0x04
        // mov esi, dword ptr [esi + 4]
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD8
        _emit 0x4E
        _emit 0x20
        // fmul dword ptr [esi + 0x20]
        _emit 0x8B
        _emit 0x45
        _emit 0x14
        // mov eax, dword ptr [ebp + 0x14]
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0xD8
        _emit 0x4E
        _emit 0x10
        // fmul dword ptr [esi + 0x10]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC3
        // fld st(3)
        _emit 0xD8
        _emit 0x0E
        // fmul dword ptr [esi]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x46
        _emit 0x30
        // fadd dword ptr [esi + 0x30]
        _emit 0xD9
        _emit 0x18
        // fstp dword ptr [eax]
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD8
        _emit 0x4E
        _emit 0x24
        // fmul dword ptr [esi + 0x24]
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0xD8
        _emit 0x4E
        _emit 0x14
        // fmul dword ptr [esi + 0x14]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC3
        // fld st(3)
        _emit 0xD8
        _emit 0x4E
        _emit 0x04
        // fmul dword ptr [esi + 4]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x46
        _emit 0x34
        // fadd dword ptr [esi + 0x34]
        _emit 0xD9
        _emit 0x58
        _emit 0x04
        // fstp dword ptr [eax + 4]
        _emit 0xD8
        _emit 0x4E
        _emit 0x28
        // fmul dword ptr [esi + 0x28]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4E
        _emit 0x18
        // fmul dword ptr [esi + 0x18]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4E
        _emit 0x08
        // fmul dword ptr [esi + 8]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x46
        _emit 0x38
        // fadd dword ptr [esi + 0x38]
        _emit 0xD9
        _emit 0x58
        _emit 0x08
        // fstp dword ptr [eax + 8]
        _emit 0x89
        _emit 0x58
        _emit 0x0C
        // mov dword ptr [eax + 0xc], ebx
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x8B
        _emit 0xE5
        // mov esp, ebp
        _emit 0x5D
        // pop ebp
        _emit 0xC3
        // ret 
    }
}

// @ 0x0110fc50  (282 bytes)
__declspec(naked) void FUN_0110fc50()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x50
        // sub esp, 0x50
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x0F
        _emit 0xB6
        _emit 0x71
        _emit 0x02
        // movzx esi, byte ptr [ecx + 2]
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x3B
        _emit 0xF0
        // cmp esi, eax
        _emit 0x57
        // push edi
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], eax
        _emit 0x7E
        _emit 0x54
        // jle 0x110fcc5
        _emit 0x0F
        _emit 0xB6
        _emit 0x79
        _emit 0x02
        // movzx edi, byte ptr [ecx + 2]
        _emit 0x8D
        _emit 0x41
        _emit 0x08
        // lea eax, [ecx + 8]
        _emit 0xB3
        _emit 0x01
        // mov bl, 1
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebx, [ebx]
        _emit 0x0F
        _emit 0xB6
        _emit 0x68
        _emit 0xFD
        // movzx ebp, byte ptr [eax - 3]
        _emit 0x0F
        _emit 0xB6
        _emit 0x50
        _emit 0xFC
        // movzx edx, byte ptr [eax - 4]
        _emit 0x03
        _emit 0xD5
        // add edx, ebp
        _emit 0x0F
        _emit 0xB6
        _emit 0x28
        // movzx ebp, byte ptr [eax]
        _emit 0xC1
        _emit 0xED
        _emit 0x04
        // shr ebp, 4
        _emit 0x88
        _emit 0x5C
        _emit 0x2C
        _emit 0x10
        // mov byte ptr [esp + ebp + 0x10], bl
        _emit 0x0F
        _emit 0xB6
        _emit 0x68
        _emit 0x01
        // movzx ebp, byte ptr [eax + 1]
        _emit 0xC1
        _emit 0xED
        _emit 0x04
        // shr ebp, 4
        _emit 0x83
        _emit 0xFA
        _emit 0x03
        // cmp edx, 3
        _emit 0x88
        _emit 0x5C
        _emit 0x2C
        _emit 0x10
        // mov byte ptr [esp + ebp + 0x10], bl
        _emit 0x7C
        _emit 0x0B
        // jl 0x110fcaf
        _emit 0x0F
        _emit 0xB6
        _emit 0x68
        _emit 0x02
        // movzx ebp, byte ptr [eax + 2]
        _emit 0xC1
        _emit 0xED
        _emit 0x04
        // shr ebp, 4
        _emit 0x88
        _emit 0x5C
        _emit 0x2C
        _emit 0x10
        // mov byte ptr [esp + ebp + 0x10], bl
        _emit 0x83
        _emit 0xFA
        _emit 0x04
        // cmp edx, 4
        _emit 0x75
        _emit 0x0B
        // jne 0x110fcbf
        _emit 0x0F
        _emit 0xB6
        _emit 0x50
        _emit 0x03
        // movzx edx, byte ptr [eax + 3]
        _emit 0xC1
        _emit 0xEA
        _emit 0x04
        // shr edx, 4
        _emit 0x88
        _emit 0x5C
        _emit 0x14
        _emit 0x10
        // mov byte ptr [esp + edx + 0x10], bl
        _emit 0x83
        _emit 0xC0
        _emit 0x08
        // add eax, 8
        _emit 0x4F
        // dec edi
        _emit 0x75
        _emit 0xBB
        // jne 0x110fc80
        _emit 0x0F
        _emit 0xB6
        _emit 0x01
        // movzx eax, byte ptr [ecx]
        _emit 0x8D
        _emit 0x7C
        _emit 0xF1
        _emit 0x04
        // lea edi, [ecx + esi*8 + 4]
        _emit 0x0F
        _emit 0xB6
        _emit 0x71
        _emit 0x01
        // movzx esi, byte ptr [ecx + 1]
        _emit 0x03
        _emit 0xF0
        // add esi, eax
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x7E
        _emit 0x21
        // jle 0x110fcfd
        _emit 0x8D
        _emit 0x64
        _emit 0x24
        _emit 0x00
        // lea esp, [esp]
        _emit 0x8A
        _emit 0x5C
        _emit 0x04
        _emit 0x10
        // mov bl, byte ptr [esp + eax + 0x10]
        _emit 0x84
        _emit 0xDB
        // test bl, bl
        _emit 0x89
        _emit 0x6C
        _emit 0x84
        _emit 0x20
        // mov dword ptr [esp + eax*4 + 0x20], ebp
        _emit 0x74
        _emit 0x0C
        // je 0x110fcf8
        _emit 0x66
        _emit 0x8B
        _emit 0x1C
        _emit 0x47
        // mov bx, word ptr [edi + eax*2]
        _emit 0x66
        _emit 0x89
        _emit 0x1C
        _emit 0x57
        // mov word ptr [edi + edx*2], bx
        _emit 0x42
        // inc edx
        _emit 0x83
        _emit 0xC5
        _emit 0x10
        // add ebp, 0x10
        _emit 0x40
        // inc eax
        _emit 0x3B
        _emit 0xC6
        // cmp eax, esi
        _emit 0x7C
        _emit 0xE3
        // jl 0x110fce0
        _emit 0x0F
        _emit 0xB6
        _emit 0x01
        // movzx eax, byte ptr [ecx]
        _emit 0x8B
        _emit 0x44
        _emit 0x84
        _emit 0x20
        // mov eax, dword ptr [esp + eax*4 + 0x20]
        _emit 0xC1
        _emit 0xE8
        _emit 0x04
        // shr eax, 4
        _emit 0x2A
        _emit 0xD0
        // sub dl, al
        _emit 0x88
        _emit 0x01
        // mov byte ptr [ecx], al
        _emit 0x8A
        _emit 0x41
        _emit 0x02
        // mov al, byte ptr [ecx + 2]
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x88
        _emit 0x51
        _emit 0x01
        // mov byte ptr [ecx + 1], dl
        _emit 0x76
        _emit 0x4B
        // jbe 0x110fd62
        _emit 0x8D
        _emit 0x41
        _emit 0x09
        // lea eax, [ecx + 9]
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebx, [ebx]
        _emit 0x0F
        _emit 0xB6
        _emit 0x50
        _emit 0xFF
        // movzx edx, byte ptr [eax - 1]
        _emit 0xC1
        _emit 0xEA
        _emit 0x04
        // shr edx, 4
        _emit 0x8A
        _emit 0x54
        _emit 0x94
        _emit 0x20
        // mov dl, byte ptr [esp + edx*4 + 0x20]
        _emit 0x88
        _emit 0x50
        _emit 0xFF
        // mov byte ptr [eax - 1], dl
        _emit 0x0F
        _emit 0xB6
        _emit 0x10
        // movzx edx, byte ptr [eax]
        _emit 0xC1
        _emit 0xEA
        _emit 0x04
        // shr edx, 4
        _emit 0x8A
        _emit 0x54
        _emit 0x94
        _emit 0x20
        // mov dl, byte ptr [esp + edx*4 + 0x20]
        _emit 0x88
        _emit 0x10
        // mov byte ptr [eax], dl
        _emit 0x0F
        _emit 0xB6
        _emit 0x50
        _emit 0x01
        // movzx edx, byte ptr [eax + 1]
        _emit 0xC1
        _emit 0xEA
        _emit 0x04
        // shr edx, 4
        _emit 0x8A
        _emit 0x54
        _emit 0x94
        _emit 0x20
        // mov dl, byte ptr [esp + edx*4 + 0x20]
        _emit 0x88
        _emit 0x50
        _emit 0x01
        // mov byte ptr [eax + 1], dl
        _emit 0x0F
        _emit 0xB6
        _emit 0x50
        _emit 0x02
        // movzx edx, byte ptr [eax + 2]
        _emit 0xC1
        _emit 0xEA
        _emit 0x04
        // shr edx, 4
        _emit 0x8A
        _emit 0x54
        _emit 0x94
        _emit 0x20
        // mov dl, byte ptr [esp + edx*4 + 0x20]
        _emit 0x88
        _emit 0x50
        _emit 0x02
        // mov byte ptr [eax + 2], dl
        _emit 0x0F
        _emit 0xB6
        _emit 0x51
        _emit 0x02
        // movzx edx, byte ptr [ecx + 2]
        _emit 0x46
        // inc esi
        _emit 0x83
        _emit 0xC0
        _emit 0x08
        // add eax, 8
        _emit 0x3B
        _emit 0xF2
        // cmp esi, edx
        _emit 0x7C
        _emit 0xBE
        // jl 0x110fd20
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
        _emit 0x50
        // add esp, 0x50
        _emit 0xC3
        // ret 
    }
}

// @ 0x0110fd70  (88 bytes)
__declspec(naked) void FUN_0110fd70()
{
    __asm {
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x04
        // mov ecx, dword ptr [esp + 4]
        _emit 0x8A
        _emit 0x41
        _emit 0x02
        // mov al, byte ptr [ecx + 2]
        _emit 0xFE
        _emit 0xC8
        // dec al
        _emit 0x88
        _emit 0x41
        _emit 0x02
        // mov byte ptr [ecx + 2], al
        _emit 0x0F
        _emit 0xB6
        _emit 0xD0
        // movzx edx, al
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0xD1
        _emit 0x04
        // mov esi, dword ptr [ecx + edx*8 + 4]
        _emit 0x89
        _emit 0x74
        _emit 0xC1
        _emit 0x04
        // mov dword ptr [ecx + eax*8 + 4], esi
        _emit 0x8B
        _emit 0x54
        _emit 0xD1
        _emit 0x08
        // mov edx, dword ptr [ecx + edx*8 + 8]
        _emit 0x89
        _emit 0x54
        _emit 0xC1
        _emit 0x08
        // mov dword ptr [ecx + eax*8 + 8], edx
        _emit 0x0F
        _emit 0xB6
        _emit 0x41
        _emit 0x02
        // movzx eax, byte ptr [ecx + 2]
        _emit 0x8D
        _emit 0x04
        _emit 0xC1
        // lea eax, [ecx + eax*8]
        _emit 0x8D
        _emit 0x50
        _emit 0x04
        // lea edx, [eax + 4]
        _emit 0x8D
        _emit 0x70
        _emit 0x0C
        // lea esi, [eax + 0xc]
        _emit 0x0F
        _emit 0xB6
        _emit 0x41
        _emit 0x01
        // movzx eax, byte ptr [ecx + 1]
        _emit 0x57
        // push edi
        _emit 0x0F
        _emit 0xB6
        _emit 0x39
        // movzx edi, byte ptr [ecx]
        _emit 0x8D
        _emit 0x44
        _emit 0x38
        _emit 0xFF
        // lea eax, [eax + edi - 1]
        _emit 0xD1
        _emit 0xF8
        // sar eax, 1
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x7C
        _emit 0x0E
        // jl 0x110fdc1
        _emit 0x40
        // inc eax
        _emit 0x8B
        _emit 0x3E
        // mov edi, dword ptr [esi]
        _emit 0x89
        _emit 0x3A
        // mov dword ptr [edx], edi
        _emit 0x83
        _emit 0xC2
        _emit 0x04
        // add edx, 4
        _emit 0x83
        _emit 0xC6
        _emit 0x04
        // add esi, 4
        _emit 0x48
        // dec eax
        _emit 0x75
        _emit 0xF3
        // jne 0x110fdb4
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        jmp FUN_0110fc50
    }
}

// @ 0x0110fdd0  (79 bytes)
__declspec(naked) void FUN_0110fdd0()
{
    __asm {
        _emit 0x55
        // push ebp
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x0C
        // mov edi, dword ptr [esp + 0xc]
        _emit 0x8A
        _emit 0x47
        _emit 0x02
        // mov al, byte ptr [edi + 2]
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x76
        _emit 0x32
        // jbe 0x110fe11
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // mov ebx, dword ptr [esp + 0x14]
        _emit 0x56
        // push esi
        _emit 0x8D
        _emit 0x77
        _emit 0x06
        // lea esi, [edi + 6]
        _emit 0xEB
        _emit 0x06
        // jmp 0x110fdf0
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebx, [ebx]
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x66
        _emit 0x8B
        _emit 0x06
        // mov ax, word ptr [esi]
        _emit 0x66
        _emit 0x3D
        _emit 0xFF
        _emit 0xFF
        // cmp ax, 0xffff
        _emit 0x74
        _emit 0x08
        // je 0x110fe03
        _emit 0x8B
        _emit 0x13
        // mov edx, dword ptr [ebx]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0x52
        _emit 0x10
        // call dword ptr [edx + 0x10]
        _emit 0x0F
        _emit 0xB6
        _emit 0x47
        _emit 0x02
        // movzx eax, byte ptr [edi + 2]
        _emit 0x45
        // inc ebp
        _emit 0x83
        _emit 0xC6
        _emit 0x08
        // add esi, 8
        _emit 0x3B
        _emit 0xE8
        // cmp ebp, eax
        _emit 0x7C
        _emit 0xE1
        // jl 0x110fdf0
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0xC6
        _emit 0x47
        _emit 0x02
        _emit 0x00
        // mov byte ptr [edi + 2], 0
        _emit 0xC6
        _emit 0x07
        _emit 0x00
        // mov byte ptr [edi], 0
        _emit 0xC6
        _emit 0x47
        _emit 0x01
        _emit 0x00
        // mov byte ptr [edi + 1], 0
        _emit 0x5F
        // pop edi
        _emit 0x5D
        // pop ebp
        _emit 0xC3
        // ret 
    }
}
