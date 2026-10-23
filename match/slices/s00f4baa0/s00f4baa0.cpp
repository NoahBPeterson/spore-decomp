// Slice s00f4baa0: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00406540();
extern "C" void FUN_00576650();
extern "C" void FUN_007d45d0();
extern "C" void FUN_00d73090();
extern "C" void FUN_00f47380();
extern "C" void FUN_00f473a0();
extern "C" void FUN_00f48a70();
extern "C" void FUN_00f4b190();
extern "C" void FUN_00f4b1d0();
extern "C" void FUN_00f4b4c0();
extern "C" void FUN_00f4bf30();
extern "C" void FUN_00f678d0();
extern "C" void FUN_00f6df40();
extern "C" void FUN_00f6e120();

// @ 0x00f4baa0  (515 bytes)
__declspec(naked) void FUN_00f4baa0()
{
    __asm {
        _emit 0x81
        _emit 0xEC
        _emit 0xF8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // sub esp, 0xf8
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0xE9
        // mov ebp, ecx
        _emit 0x8B
        _emit 0x45
        _emit 0x0C
        // mov eax, dword ptr [ebp + 0xc]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // movss dword ptr [esp + 8], xmm0
        _emit 0x38
        _emit 0x58
        _emit 0x54
        // cmp byte ptr [eax + 0x54], bl
        _emit 0x74
        _emit 0x18
        // je 0xf4bad5
        call FUN_00f48a70
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00f678d0
        _emit 0xDC
        _emit 0xC0
        // fadd st(0), st(0)
        _emit 0xD8
        _emit 0x25
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // fsub dword ptr [0x1485720]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fstp dword ptr [esp + 8]
        _emit 0x8B
        _emit 0x8D
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [ebp + 0xc0]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // lea ecx, [esp + 0x10]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], ebx
        call FUN_00576650
        _emit 0x39
        _emit 0x9D
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp dword ptr [ebp + 0xc0], ebx
        _emit 0x74
        _emit 0x0C
        // je 0xf4bafd
        _emit 0x8B
        _emit 0x55
        _emit 0x0C
        // mov edx, dword ptr [ebp + 0xc]
        _emit 0x38
        _emit 0x5A
        _emit 0x21
        // cmp byte ptr [edx + 0x21], bl
        _emit 0x88
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // mov byte ptr [esp + 0x10], bl
        _emit 0x74
        _emit 0x05
        // je 0xf4bb02
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x01
        // mov byte ptr [esp + 0x10], 1
        _emit 0x8B
        _emit 0x45
        _emit 0x0C
        // mov eax, dword ptr [ebp + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x24
        // movss xmm0, dword ptr [eax + 0x24]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // movss xmm2, dword ptr [esp + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x84
        _emit 0x24
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esp + 0x104]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // movss dword ptr [esp + 0x28], xmm0
        _emit 0x8A
        _emit 0x88
        _emit 0x81
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov cl, byte ptr [eax + 0x81]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x85
        _emit 0xBC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [ebp + 0xbc]
        _emit 0x88
        _emit 0x4C
        _emit 0x24
        _emit 0x11
        // mov byte ptr [esp + 0x11], cl
        _emit 0x8A
        _emit 0x90
        _emit 0xD0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dl, byte ptr [eax + 0xd0]
        _emit 0x88
        _emit 0x54
        _emit 0x24
        _emit 0x12
        // mov byte ptr [esp + 0x12], dl
        _emit 0x0F
        _emit 0xB6
        _emit 0x48
        _emit 0x20
        // movzx ecx, byte ptr [eax + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC2
        // addss xmm0, xmm2
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // movss dword ptr [esp + 0x1c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x74
        // movss xmm0, dword ptr [eax + 0x74]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // movss dword ptr [esp + 0x20], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0x78
        // movss xmm1, dword ptr [eax + 0x78]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // movss dword ptr [esp + 0x24], xmm1
        _emit 0x83
        _emit 0xF9
        _emit 0x05
        // cmp ecx, 5
        _emit 0x74
        _emit 0x19
        // je 0xf4bb87
        _emit 0x83
        _emit 0xF9
        _emit 0x06
        // cmp ecx, 6
        _emit 0x74
        _emit 0x14
        // je 0xf4bb87
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC2
        // addss xmm0, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xCA
        // addss xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // movss dword ptr [esp + 0x20], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // movss dword ptr [esp + 0x24], xmm1
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x48
        // mov dword ptr [esp + 0x48], ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xB4
        _emit 0x24
        _emit 0x14
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov esi, dword ptr [esp + 0x114]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0x8A
        _emit 0x82
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov al, byte ptr [edx + 0x80]
        _emit 0x88
        _emit 0x84
        _emit 0x24
        _emit 0x8C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esp + 0x8c], al
        _emit 0x8B
        _emit 0xC2
        // mov eax, edx
        _emit 0xB9
        _emit 0x11
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, 0x11
        _emit 0x8D
        _emit 0xBC
        _emit 0x24
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea edi, [esp + 0x90]
        _emit 0xF3
        _emit 0xA5
        // rep movsd dword ptr es:[edi], dword ptr [esi]
        _emit 0x88
        _emit 0x9C
        _emit 0x24
        _emit 0x8D
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esp + 0x8d], bl
        _emit 0x0F
        _emit 0xB6
        _emit 0x88
        _emit 0xB8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movzx ecx, byte ptr [eax + 0xb8]
        _emit 0x89
        _emit 0x8C
        _emit 0x24
        _emit 0xD4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0xd4], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x80
        _emit 0xBC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [eax + 0xbc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x84
        _emit 0x24
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esp + 0xd8], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x80
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [eax + 0xc0]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x84
        _emit 0x24
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esp + 0xdc], xmm0
        _emit 0x0F
        _emit 0xB6
        _emit 0x88
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movzx ecx, byte ptr [eax + 0xc4]
        _emit 0x89
        _emit 0x8C
        _emit 0x24
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0xe0], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x80
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [eax + 0xc8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x84
        _emit 0x24
        _emit 0xE4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esp + 0xe4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x80
        _emit 0xCC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [eax + 0xcc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x84
        _emit 0x24
        _emit 0xE8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esp + 0xe8], xmm0
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x38
        _emit 0x98
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [eax + 0x80], bl
        _emit 0x74
        _emit 0x11
        // je 0xf4bc35
        _emit 0x80
        _emit 0xBA
        _emit 0x82
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x12
        // cmp byte ptr [edx + 0x82], 0x12
        _emit 0x75
        _emit 0x08
        // jne 0xf4bc35
        _emit 0xC6
        _emit 0x84
        _emit 0x24
        _emit 0x85
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x01
        // mov byte ptr [esp + 0x85], 1
        _emit 0x8B
        _emit 0x94
        _emit 0x24
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esp + 0x10c]
        _emit 0x8B
        _emit 0x84
        _emit 0x24
        _emit 0x08
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esp + 0x108]
        _emit 0x53
        // push ebx
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x8C
        _emit 0x24
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [esp + 0x90]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // lea edx, [esp + 0x1c]
        _emit 0x52
        // push edx
        call FUN_00f48a70
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00f6e120
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov eax, dword ptr [esp + 0xc]
        _emit 0x5D
        // pop ebp
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x5B
        // pop ebx
        _emit 0x74
        _emit 0x31
        // je 0xf4bc9a
        _emit 0x83
        _emit 0xC0
        _emit 0x08
        // add eax, 8
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x83
        _emit 0xCA
        _emit 0xFF
        // or edx, 0xffffffff
        _emit 0xF0
        _emit 0x0F
        _emit 0xC1
        _emit 0x11
        // lock xadd dword ptr [ecx], edx
        _emit 0x33
        _emit 0xC9
        // xor ecx, ecx
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0xF0
        _emit 0x0F
        _emit 0xC1
        _emit 0x0A
        // lock xadd dword ptr [edx], ecx
        _emit 0x83
        _emit 0xF9
        _emit 0x01
        // cmp ecx, 1
        _emit 0x7D
        _emit 0x12
        // jge 0xf4bc94
        _emit 0xB9
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, 1
        _emit 0xF0
        _emit 0x0F
        _emit 0xC1
        _emit 0x08
        // lock xadd dword ptr [eax], ecx
        _emit 0x81
        _emit 0xC4
        _emit 0xF8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add esp, 0xf8
        _emit 0xC2
        _emit 0x10
        _emit 0x00
        // ret 0x10
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0xF0
        _emit 0x0F
        _emit 0xC1
        _emit 0x10
        // lock xadd dword ptr [eax], edx
        _emit 0x81
        _emit 0xC4
        _emit 0xF8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add esp, 0xf8
        _emit 0xC2
        _emit 0x10
        _emit 0x00
        // ret 0x10
    }
}

// @ 0x00f4bcb0  (633 bytes)
__declspec(naked) void FUN_00f4bcb0()
{
    __asm {
        _emit 0x81
        _emit 0xEC
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // sub esp, 0x104
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0xE9
        // mov ebp, ecx
        _emit 0x8B
        _emit 0x45
        _emit 0x0C
        // mov eax, dword ptr [ebp + 0xc]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // movss dword ptr [esp + 8], xmm0
        _emit 0x38
        _emit 0x58
        _emit 0x54
        // cmp byte ptr [eax + 0x54], bl
        _emit 0x74
        _emit 0x18
        // je 0xf4bce5
        call FUN_00f48a70
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00f678d0
        _emit 0xDC
        _emit 0xC0
        // fadd st(0), st(0)
        _emit 0xD8
        _emit 0x25
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // fsub dword ptr [0x1485720]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fstp dword ptr [esp + 8]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], ebx
        _emit 0x39
        _emit 0x9D
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp dword ptr [ebp + 0xc0], ebx
        _emit 0x74
        _emit 0x0C
        // je 0xf4bcfd
        _emit 0x8B
        _emit 0x4D
        _emit 0x0C
        // mov ecx, dword ptr [ebp + 0xc]
        _emit 0x38
        _emit 0x59
        _emit 0x21
        // cmp byte ptr [ecx + 0x21], bl
        _emit 0x88
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov byte ptr [esp + 0x1c], bl
        _emit 0x74
        _emit 0x05
        // je 0xf4bd02
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        _emit 0x01
        // mov byte ptr [esp + 0x1c], 1
        _emit 0x8B
        _emit 0x55
        _emit 0x0C
        // mov edx, dword ptr [ebp + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x42
        _emit 0x24
        // movss xmm0, dword ptr [edx + 0x24]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // movss dword ptr [esp + 0x20], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x84
        _emit 0x24
        _emit 0x10
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esp + 0x110]
        _emit 0x8B
        _emit 0xC2
        // mov eax, edx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // movss dword ptr [esp + 0x34], xmm0
        _emit 0x8A
        _emit 0x88
        _emit 0x81
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov cl, byte ptr [eax + 0x81]
        _emit 0x88
        _emit 0x4C
        _emit 0x24
        _emit 0x1D
        // mov byte ptr [esp + 0x1d], cl
        _emit 0x8A
        _emit 0x90
        _emit 0xD0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dl, byte ptr [eax + 0xd0]
        _emit 0x88
        _emit 0x54
        _emit 0x24
        _emit 0x1E
        // mov byte ptr [esp + 0x1e], dl
        _emit 0xD9
        _emit 0x80
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [eax + 0xe0]
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x04
        // fstp dword ptr [esp + 4]
        _emit 0xD9
        _emit 0x80
        _emit 0xD4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [eax + 0xd4]
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        call FUN_007d45d0
        _emit 0x8B
        _emit 0x45
        _emit 0x0C
        // mov eax, dword ptr [ebp + 0xc]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x80
        _emit 0xE4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [eax + 0xe4]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x04
        // fstp dword ptr [esp + 4]
        _emit 0xD9
        _emit 0x80
        _emit 0xD8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [eax + 0xd8]
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        call FUN_007d45d0
        _emit 0x8B
        _emit 0x45
        _emit 0x0C
        // mov eax, dword ptr [ebp + 0xc]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // fstp dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0x80
        _emit 0xE8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [eax + 0xe8]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x04
        // fstp dword ptr [esp + 4]
        _emit 0xD9
        _emit 0x80
        _emit 0xDC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [eax + 0xdc]
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        call FUN_007d45d0
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
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
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x85
        _emit 0xBC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [ebp + 0xbc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // movss xmm2, dword ptr [esp + 0x10]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // mov dword ptr [esp + 0x40], eax
        _emit 0x8B
        _emit 0x45
        _emit 0x0C
        // mov eax, dword ptr [ebp + 0xc]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x44
        // mov dword ptr [esp + 0x44], ecx
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x48
        // mov dword ptr [esp + 0x48], edx
        _emit 0x0F
        _emit 0xB6
        _emit 0x48
        _emit 0x20
        // movzx ecx, byte ptr [eax + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC2
        // addss xmm0, xmm2
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // movss dword ptr [esp + 0x30], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x74
        // movss xmm0, dword ptr [eax + 0x74]
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
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
        _emit 0x48
        _emit 0x78
        // movss xmm1, dword ptr [eax + 0x78]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x30
        // movss dword ptr [esp + 0x30], xmm1
        _emit 0x83
        _emit 0xF9
        _emit 0x05
        // cmp ecx, 5
        _emit 0x74
        _emit 0x19
        // je 0xf4be04
        _emit 0x83
        _emit 0xF9
        _emit 0x06
        // cmp ecx, 6
        _emit 0x74
        _emit 0x14
        // je 0xf4be04
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC2
        // addss xmm0, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xCA
        // addss xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // movss dword ptr [esp + 0x2c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x30
        // movss dword ptr [esp + 0x30], xmm1
        _emit 0x8B
        _emit 0x85
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [ebp + 0xc0]
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // lea ecx, [esp + 0x24]
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x60
        // mov dword ptr [esp + 0x60], ebx
        call FUN_00576650
        _emit 0x8B
        _emit 0x45
        _emit 0x0C
        // mov eax, dword ptr [ebp + 0xc]
        _emit 0x8A
        _emit 0x88
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov cl, byte ptr [eax + 0x80]
        _emit 0x8B
        _emit 0xB4
        _emit 0x24
        _emit 0x1C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov esi, dword ptr [esp + 0x11c]
        _emit 0x88
        _emit 0x8C
        _emit 0x24
        _emit 0x98
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esp + 0x98], cl
        _emit 0x8B
        _emit 0xE8
        // mov ebp, eax
        _emit 0xB9
        _emit 0x11
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, 0x11
        _emit 0x8D
        _emit 0xBC
        _emit 0x24
        _emit 0x9C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea edi, [esp + 0x9c]
        _emit 0xF3
        _emit 0xA5
        // rep movsd dword ptr es:[edi], dword ptr [esi]
        _emit 0x88
        _emit 0x9C
        _emit 0x24
        _emit 0x99
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esp + 0x99], bl
        _emit 0x0F
        _emit 0xB6
        _emit 0x95
        _emit 0xB8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movzx edx, byte ptr [ebp + 0xb8]
        _emit 0x89
        _emit 0x94
        _emit 0x24
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0xe0], edx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x85
        _emit 0xBC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [ebp + 0xbc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x84
        _emit 0x24
        _emit 0xE4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esp + 0xe4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x85
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [ebp + 0xc0]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x84
        _emit 0x24
        _emit 0xE8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esp + 0xe8], xmm0
        _emit 0x0F
        _emit 0xB6
        _emit 0x8D
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movzx ecx, byte ptr [ebp + 0xc4]
        _emit 0x89
        _emit 0x8C
        _emit 0x24
        _emit 0xEC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0xec], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x85
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [ebp + 0xc8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x84
        _emit 0x24
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esp + 0xf0], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x85
        _emit 0xCC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [ebp + 0xcc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x84
        _emit 0x24
        _emit 0xF4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [esp + 0xf4], xmm0
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x38
        _emit 0x9D
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [ebp + 0x80], bl
        _emit 0x74
        _emit 0x11
        // je 0xf4bec3
        _emit 0x80
        _emit 0xB8
        _emit 0x82
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x12
        // cmp byte ptr [eax + 0x82], 0x12
        _emit 0x75
        _emit 0x08
        // jne 0xf4bec3
        _emit 0xC6
        _emit 0x84
        _emit 0x24
        _emit 0x91
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x01
        // mov byte ptr [esp + 0x91], 1
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld dword ptr [esp + 8]
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        _emit 0x53
        // push ebx
        _emit 0x8D
        _emit 0x94
        _emit 0x24
        _emit 0x98
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea edx, [esp + 0x98]
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // lea eax, [esp + 0x24]
        _emit 0x50
        // push eax
        call FUN_00f48a70
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00f6df40
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov eax, dword ptr [esp + 0x18]
        _emit 0x5D
        // pop ebp
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x5B
        // pop ebx
        _emit 0x74
        _emit 0x31
        // je 0xf4bf20
        _emit 0x83
        _emit 0xC0
        _emit 0x08
        // add eax, 8
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x83
        _emit 0xCA
        _emit 0xFF
        // or edx, 0xffffffff
        _emit 0xF0
        _emit 0x0F
        _emit 0xC1
        _emit 0x11
        // lock xadd dword ptr [ecx], edx
        _emit 0x33
        _emit 0xC9
        // xor ecx, ecx
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0xF0
        _emit 0x0F
        _emit 0xC1
        _emit 0x0A
        // lock xadd dword ptr [edx], ecx
        _emit 0x83
        _emit 0xF9
        _emit 0x01
        // cmp ecx, 1
        _emit 0x7D
        _emit 0x12
        // jge 0xf4bf1a
        _emit 0xB9
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, 1
        _emit 0xF0
        _emit 0x0F
        _emit 0xC1
        _emit 0x08
        // lock xadd dword ptr [eax], ecx
        _emit 0x81
        _emit 0xC4
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // add esp, 0x104
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0xF0
        _emit 0x0F
        _emit 0xC1
        _emit 0x10
        // lock xadd dword ptr [eax], edx
        _emit 0x81
        _emit 0xC4
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // add esp, 0x104
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00f4bf30  (359 bytes)
__declspec(naked) void FUN_00f4bf30()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xD9
        // mov ebx, ecx
        _emit 0x8B
        _emit 0x43
        _emit 0x04
        // mov eax, dword ptr [ebx + 4]
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x3B
        _emit 0x43
        _emit 0x08
        // cmp eax, dword ptr [ebx + 8]
        _emit 0x74
        _emit 0x7F
        // je 0xf4bfbd
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x14
        // mov ebp, dword ptr [esp + 0x14]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], ecx
        _emit 0x3B
        _emit 0xCD
        // cmp ecx, ebp
        _emit 0x72
        _emit 0x0B
        // jb 0xf4bf59
        _emit 0x3B
        _emit 0xC8
        // cmp ecx, eax
        _emit 0x73
        _emit 0x07
        // jae 0xf4bf59
        _emit 0x83
        _emit 0xC1
        _emit 0x1C
        // add ecx, 0x1c
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], ecx
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x29
        // je 0xf4bf86
        _emit 0xD9
        _emit 0x40
        _emit 0xE4
        // fld dword ptr [eax - 0x1c]
        _emit 0xD9
        _emit 0x18
        // fstp dword ptr [eax]
        _emit 0xD9
        _emit 0x40
        _emit 0xE8
        // fld dword ptr [eax - 0x18]
        _emit 0xD9
        _emit 0x58
        _emit 0x04
        // fstp dword ptr [eax + 4]
        _emit 0xD9
        _emit 0x40
        _emit 0xEC
        // fld dword ptr [eax - 0x14]
        _emit 0xD9
        _emit 0x58
        _emit 0x08
        // fstp dword ptr [eax + 8]
        _emit 0xD9
        _emit 0x40
        _emit 0xF0
        // fld dword ptr [eax - 0x10]
        _emit 0xD9
        _emit 0x58
        _emit 0x0C
        // fstp dword ptr [eax + 0xc]
        _emit 0xD9
        _emit 0x40
        _emit 0xF4
        // fld dword ptr [eax - 0xc]
        _emit 0xD9
        _emit 0x58
        _emit 0x10
        // fstp dword ptr [eax + 0x10]
        _emit 0xD9
        _emit 0x40
        _emit 0xF8
        // fld dword ptr [eax - 8]
        _emit 0xD9
        _emit 0x58
        _emit 0x14
        // fstp dword ptr [eax + 0x14]
        _emit 0xD9
        _emit 0x40
        _emit 0xFC
        // fld dword ptr [eax - 4]
        _emit 0xD9
        _emit 0x58
        _emit 0x18
        // fstp dword ptr [eax + 0x18]
        _emit 0x8B
        _emit 0x53
        _emit 0x04
        // mov edx, dword ptr [ebx + 4]
        _emit 0x8D
        _emit 0x42
        _emit 0xE4
        // lea eax, [edx - 0x1c]
        _emit 0x3B
        _emit 0xC5
        // cmp eax, ebp
        _emit 0x74
        _emit 0x15
        // je 0xf4bfa5
        _emit 0x83
        _emit 0xE8
        _emit 0x1C
        // sub eax, 0x1c
        _emit 0x83
        _emit 0xEA
        _emit 0x1C
        // sub edx, 0x1c
        _emit 0xB9
        _emit 0x07
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, 7
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x8B
        _emit 0xFA
        // mov edi, edx
        _emit 0xF3
        _emit 0xA5
        // rep movsd dword ptr es:[edi], dword ptr [esi]
        _emit 0x3B
        _emit 0xC5
        // cmp eax, ebp
        _emit 0x75
        _emit 0xEB
        // jne 0xf4bf90
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x18
        // mov esi, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0xFD
        // mov edi, ebp
        _emit 0xB9
        _emit 0x07
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, 7
        _emit 0xF3
        _emit 0xA5
        // rep movsd dword ptr es:[edi], dword ptr [esi]
        _emit 0x83
        _emit 0x43
        _emit 0x04
        _emit 0x1C
        // add dword ptr [ebx + 4], 0x1c
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
        _emit 0x2B
        _emit 0x03
        // sub eax, dword ptr [ebx]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xB8
        _emit 0x93
        _emit 0x24
        _emit 0x49
        _emit 0x92
        // mov eax, 0x92492493
        _emit 0xF7
        _emit 0xE9
        // imul ecx
        _emit 0x03
        _emit 0xD1
        // add edx, ecx
        _emit 0xC1
        _emit 0xFA
        _emit 0x04
        // sar edx, 4
        _emit 0x8B
        _emit 0xC2
        // mov eax, edx
        _emit 0xC1
        _emit 0xE8
        _emit 0x1F
        // shr eax, 0x1f
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x74
        _emit 0x34
        // je 0xf4c00a
        _emit 0x8D
        _emit 0x2C
        _emit 0x00
        // lea ebp, [eax + eax]
        _emit 0x85
        _emit 0xED
        // test ebp, ebp
        _emit 0x74
        _emit 0x34
        // je 0xf4c011
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
        _emit 0x8D
        _emit 0x04
        _emit 0xED
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea eax, [ebp*8]
        _emit 0x2B
        _emit 0xC5
        // sub eax, ebp
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x03
        _emit 0xC0
        // add eax, eax
        _emit 0x03
        _emit 0xC0
        // add eax, eax
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
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0xEB
        _emit 0x09
        // jmp 0xf4c013
        _emit 0xBD
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebp, 1
        _emit 0xEB
        _emit 0xCC
        // jmp 0xf4bfdd
        _emit 0x33
        _emit 0xF6
        // xor esi, esi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov edi, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x50
        // push eax
        call FUN_00f4b1d0
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x2C
        // je 0xf4c054
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0x01
        // fld dword ptr [ecx]
        _emit 0xD9
        _emit 0x18
        // fstp dword ptr [eax]
        _emit 0xD9
        _emit 0x41
        _emit 0x04
        // fld dword ptr [ecx + 4]
        _emit 0xD9
        _emit 0x58
        _emit 0x04
        // fstp dword ptr [eax + 4]
        _emit 0xD9
        _emit 0x41
        _emit 0x08
        // fld dword ptr [ecx + 8]
        _emit 0xD9
        _emit 0x58
        _emit 0x08
        // fstp dword ptr [eax + 8]
        _emit 0xD9
        _emit 0x41
        _emit 0x0C
        // fld dword ptr [ecx + 0xc]
        _emit 0xD9
        _emit 0x58
        _emit 0x0C
        // fstp dword ptr [eax + 0xc]
        _emit 0xD9
        _emit 0x41
        _emit 0x10
        // fld dword ptr [ecx + 0x10]
        _emit 0xD9
        _emit 0x58
        _emit 0x10
        // fstp dword ptr [eax + 0x10]
        _emit 0xD9
        _emit 0x41
        _emit 0x14
        // fld dword ptr [ecx + 0x14]
        _emit 0xD9
        _emit 0x58
        _emit 0x14
        // fstp dword ptr [eax + 0x14]
        _emit 0xD9
        _emit 0x41
        _emit 0x18
        // fld dword ptr [ecx + 0x18]
        _emit 0xD9
        _emit 0x58
        _emit 0x18
        // fstp dword ptr [eax + 0x18]
        _emit 0x8B
        _emit 0x4B
        _emit 0x04
        // mov ecx, dword ptr [ebx + 4]
        _emit 0x83
        _emit 0xC0
        _emit 0x1C
        // add eax, 0x1c
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x57
        // push edi
        call FUN_00f4b1d0
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xf4c07c
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xf4c07c
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8D
        _emit 0x0C
        _emit 0xED
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [ebp*8]
        _emit 0x89
        _emit 0x7B
        _emit 0x04
        // mov dword ptr [ebx + 4], edi
        _emit 0x2B
        _emit 0xCD
        // sub ecx, ebp
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x33
        // mov dword ptr [ebx], esi
        _emit 0x8D
        _emit 0x14
        _emit 0x8E
        // lea edx, [esi + ecx*4]
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x89
        _emit 0x53
        _emit 0x08
        // mov dword ptr [ebx + 8], edx
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00f4c150  (35 bytes)
__declspec(naked) void FUN_00f4c150()
{
    __asm {
        _emit 0x8B
        _emit 0x41
        _emit 0x04
        // mov eax, dword ptr [ecx + 4]
        _emit 0x83
        _emit 0xEC
        _emit 0x1C
        // sub esp, 0x1c
        _emit 0x3B
        _emit 0x41
        _emit 0x08
        // cmp eax, dword ptr [ecx + 8]
        _emit 0x73
        _emit 0x0A
        // jae 0xf4c165
        _emit 0x83
        _emit 0xC0
        _emit 0x1C
        // add eax, 0x1c
        _emit 0x89
        _emit 0x41
        _emit 0x04
        // mov dword ptr [ecx + 4], eax
        _emit 0x83
        _emit 0xC4
        _emit 0x1C
        // add esp, 0x1c
        _emit 0xC3
        // ret 
        _emit 0x8D
        _emit 0x14
        _emit 0x24
        // lea edx, [esp]
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        call FUN_00f4bf30
        _emit 0x83
        _emit 0xC4
        _emit 0x1C
        // add esp, 0x1c
        _emit 0xC3
        // ret 
    }
}

// @ 0x00f4c180  (316 bytes)
__declspec(naked) void FUN_00f4c180()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xD9
        // mov ebx, ecx
        _emit 0x8B
        _emit 0x43
        _emit 0x04
        // mov eax, dword ptr [ebx + 4]
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x3B
        _emit 0x43
        _emit 0x08
        // cmp eax, dword ptr [ebx + 8]
        _emit 0x74
        _emit 0x64
        // je 0xf4c1f1
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        // mov edi, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x3B
        _emit 0xCF
        // cmp ecx, edi
        _emit 0x72
        _emit 0x0A
        // jb 0xf4c1a5
        _emit 0x3B
        _emit 0xC8
        // cmp ecx, eax
        _emit 0x73
        _emit 0x06
        // jae 0xf4c1a5
        _emit 0x8D
        _emit 0xB1
        _emit 0xC4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea esi, [ecx + 0x1c4]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x21
        // je 0xf4c1ca
        _emit 0x8B
        _emit 0x88
        _emit 0x3C
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // mov ecx, dword ptr [eax - 0x1c4]
        _emit 0x68
        _emit 0x00
        _emit 0x5C
        _emit 0x70
        _emit 0x00
        // push 0x705c00
        _emit 0x6A
        _emit 0x10
        // push 0x10
        _emit 0x6A
        _emit 0x1C
        // push 0x1c
        _emit 0x8D
        _emit 0x90
        _emit 0x40
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // lea edx, [eax - 0x1c0]
        _emit 0x89
        _emit 0x08
        // mov dword ptr [eax], ecx
        _emit 0x52
        // push edx
        _emit 0x83
        _emit 0xC0
        _emit 0x04
        // add eax, 4
        _emit 0x50
        // push eax
        call FUN_00406540
        _emit 0x8B
        _emit 0x43
        _emit 0x04
        // mov eax, dword ptr [ebx + 4]
        _emit 0x50
        // push eax
        _emit 0x05
        _emit 0x3C
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // add eax, 0xfffffe3c
        _emit 0x50
        // push eax
        _emit 0x57
        // push edi
        call FUN_00f4b190
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xB9
        _emit 0x71
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, 0x71
        _emit 0xF3
        _emit 0xA5
        // rep movsd dword ptr es:[edi], dword ptr [esi]
        _emit 0x81
        _emit 0x43
        _emit 0x04
        _emit 0xC4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // add dword ptr [ebx + 4], 0x1c4
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
        _emit 0x2B
        _emit 0x03
        // sub eax, dword ptr [ebx]
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0xB8
        _emit 0x05
        _emit 0xDE
        _emit 0x7E
        _emit 0x48
        // mov eax, 0x487ede05
        _emit 0xF7
        _emit 0xE9
        // imul ecx
        _emit 0xC1
        _emit 0xFA
        _emit 0x07
        // sar edx, 7
        _emit 0x8B
        _emit 0xC2
        // mov eax, edx
        _emit 0xC1
        _emit 0xE8
        _emit 0x1F
        // shr eax, 0x1f
        _emit 0x03
        _emit 0xC2
        // add eax, edx
        _emit 0x74
        _emit 0x2F
        // je 0xf4c238
        _emit 0x8D
        _emit 0x3C
        _emit 0x00
        // lea edi, [eax + eax]
        _emit 0x85
        _emit 0xFF
        // test edi, edi
        _emit 0x74
        _emit 0x2F
        // je 0xf4c23f
        _emit 0x68
        _emit 0xD1
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // push 0xd1
        _emit 0x8B
        _emit 0xC7
        // mov eax, edi
        _emit 0x69
        _emit 0xC0
        _emit 0xC4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // imul eax, eax, 0x1c4
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
        _emit 0x8B
        _emit 0xE8
        // mov ebp, eax
        _emit 0xEB
        _emit 0x09
        // jmp 0xf4c241
        _emit 0xBF
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edi, 1
        _emit 0xEB
        _emit 0xD1
        // jmp 0xf4c210
        _emit 0x33
        _emit 0xED
        // xor ebp, ebp
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x55
        // push ebp
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        call FUN_00f4b4c0
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x1E
        // je 0xf4c276
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov eax, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0x00
        _emit 0x5C
        _emit 0x70
        _emit 0x00
        // push 0x705c00
        _emit 0x6A
        _emit 0x10
        // push 0x10
        _emit 0x6A
        _emit 0x1C
        // push 0x1c
        _emit 0x83
        _emit 0xC0
        _emit 0x04
        // add eax, 4
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x46
        _emit 0x04
        // lea eax, [esi + 4]
        _emit 0x50
        // push eax
        _emit 0x89
        _emit 0x16
        // mov dword ptr [esi], edx
        call FUN_00406540
        _emit 0x8B
        _emit 0x43
        _emit 0x04
        // mov eax, dword ptr [ebx + 4]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x81
        _emit 0xC6
        _emit 0xC4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // add esi, 0x1c4
        _emit 0x56
        // push esi
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        call FUN_00f4b4c0
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0F
        // je 0xf4c2a5
        _emit 0x83
        _emit 0x78
        _emit 0xFC
        _emit 0x00
        // cmp dword ptr [eax - 4], 0
        _emit 0x74
        _emit 0x09
        // je 0xf4c2a5
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x69
        _emit 0xFF
        _emit 0xC4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // imul edi, edi, 0x1c4
        _emit 0x03
        _emit 0xFD
        // add edi, ebp
        _emit 0x89
        _emit 0x2B
        // mov dword ptr [ebx], ebp
        _emit 0x5D
        // pop ebp
        _emit 0x89
        _emit 0x7B
        _emit 0x08
        // mov dword ptr [ebx + 8], edi
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x73
        _emit 0x04
        // mov dword ptr [ebx + 4], esi
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

// @ 0x00f4c2c0  (61 bytes)
__declspec(naked) void FUN_00f4c2c0()
{
    __asm {
        _emit 0x80
        _emit 0x79
        _emit 0x10
        _emit 0x00
        // cmp byte ptr [ecx + 0x10], 0
        _emit 0x75
        _emit 0x34
        // jne 0xf4c2fa
        _emit 0x0F
        _emit 0x57
        _emit 0xC0
        // xorps xmm0, xmm0
        _emit 0x8B
        _emit 0x41
        _emit 0x0C
        // mov eax, dword ptr [ecx + 0xc]
        _emit 0xC6
        _emit 0x41
        _emit 0x10
        _emit 0x01
        // mov byte ptr [ecx + 0x10], 1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x81
        _emit 0x9C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [ecx + 0x9c], xmm0
        _emit 0x80
        _emit 0xB8
        _emit 0xEC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [eax + 0xec], 0
        _emit 0x74
        _emit 0x19
        // je 0xf4c2fa
        _emit 0x8B
        _emit 0x91
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [ecx + 0xc8]
        _emit 0x8B
        _emit 0x81
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [ecx + 0xc4]
        _emit 0x81
        _emit 0xC1
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // add ecx, 0xc4
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        call FUN_00d73090
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}
