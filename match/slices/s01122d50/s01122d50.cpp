// Slice s01122d50: EASTL/Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_0107db10();
extern "C" void FUN_01122b20();
extern "C" void FUN_01122b70();
extern "C" void FUN_01122c00();
extern "C" void FUN_01122cd0();
extern "C" void FUN_01122d50();
extern "C" void FUN_01122f70();

// @ 0x01122d50  (532 bytes)
__declspec(naked) void FUN_01122d50()
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
        _emit 0x83
        _emit 0xEC
        _emit 0x24
        // sub esp, 0x24
        _emit 0x8B
        _emit 0x55
        _emit 0x08
        // mov edx, dword ptr [ebp + 8]
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x72
        _emit 0x04
        // mov esi, dword ptr [edx + 4]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x3B
        _emit 0xF3
        // cmp esi, ebx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7D
        _emit 0x10
        // mov edi, dword ptr [ebp + 0x10]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ecx
        _emit 0x0F
        _emit 0x8E
        _emit 0x88
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jle 0x1122efd
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x0F
        _emit 0x84
        _emit 0xD9
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0x1122f56
        _emit 0x8B
        _emit 0x0A
        // mov ecx, dword ptr [edx]
        _emit 0x8B
        _emit 0x14
        _emit 0x81
        // mov edx, dword ptr [ecx + eax*4]
        _emit 0x8D
        _emit 0x58
        _emit 0x01
        // lea ebx, [eax + 1]
        _emit 0x3B
        _emit 0xDE
        // cmp ebx, esi
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], ebx
        _emit 0x7D
        _emit 0x0A
        // jge 0x1122d97
        _emit 0x8B
        _emit 0x44
        _emit 0x81
        _emit 0x04
        // mov eax, dword ptr [ecx + eax*4 + 4]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], eax
        _emit 0xEB
        _emit 0x06
        // jmp 0x1122d9d
        _emit 0x8B
        _emit 0x09
        // mov ecx, dword ptr [ecx]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ecx
        _emit 0x89
        _emit 0x52
        _emit 0x20
        // mov dword ptr [edx + 0x20], edx
        _emit 0x89
        _emit 0x52
        _emit 0x30
        // mov dword ptr [edx + 0x30], edx
        _emit 0x89
        _emit 0x52
        _emit 0x40
        // mov dword ptr [edx + 0x40], edx
        _emit 0x8D
        _emit 0x5A
        _emit 0x34
        // lea ebx, [edx + 0x34]
        _emit 0x89
        _emit 0x5A
        _emit 0x28
        // mov dword ptr [edx + 0x28], ebx
        _emit 0x8D
        _emit 0x42
        _emit 0x14
        // lea eax, [edx + 0x14]
        _emit 0x89
        _emit 0x42
        _emit 0x38
        // mov dword ptr [edx + 0x38], eax
        _emit 0x8D
        _emit 0x4A
        _emit 0x24
        // lea ecx, [edx + 0x24]
        _emit 0x89
        _emit 0x4A
        _emit 0x18
        // mov dword ptr [edx + 0x18], ecx
        _emit 0x8B
        _emit 0x77
        _emit 0x04
        // mov esi, dword ptr [edi + 4]
        _emit 0x8B
        _emit 0x36
        // mov esi, dword ptr [esi]
        _emit 0x89
        _emit 0x30
        // mov dword ptr [eax], esi
        _emit 0x8B
        _emit 0x37
        // mov esi, dword ptr [edi]
        _emit 0x89
        _emit 0x31
        // mov dword ptr [ecx], esi
        _emit 0x8B
        _emit 0x75
        _emit 0x14
        // mov esi, dword ptr [ebp + 0x14]
        _emit 0x8B
        _emit 0x36
        // mov esi, dword ptr [esi]
        _emit 0x89
        _emit 0x33
        // mov dword ptr [ebx], esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x14
        // mov esi, dword ptr [esp + 0x14]
        _emit 0x89
        _emit 0x47
        _emit 0x08
        // mov dword ptr [edi + 8], eax
        _emit 0x89
        _emit 0x7A
        _emit 0x1C
        // mov dword ptr [edx + 0x1c], edi
        _emit 0x89
        _emit 0x5E
        _emit 0x2C
        // mov dword ptr [esi + 0x2c], ebx
        _emit 0x8B
        _emit 0x1B
        // mov ebx, dword ptr [ebx]
        _emit 0x83
        _emit 0xC6
        _emit 0x24
        // add esi, 0x24
        _emit 0x89
        _emit 0x72
        _emit 0x3C
        // mov dword ptr [edx + 0x3c], esi
        _emit 0x8B
        _emit 0x30
        // mov esi, dword ptr [eax]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0xD9
        _emit 0x06
        // fld dword ptr [esi]
        _emit 0xD8
        _emit 0x20
        // fsub dword ptr [eax]
        _emit 0xD9
        _emit 0x46
        _emit 0x04
        // fld dword ptr [esi + 4]
        _emit 0xD8
        _emit 0x60
        _emit 0x04
        // fsub dword ptr [eax + 4]
        _emit 0xD9
        _emit 0x46
        _emit 0x08
        // fld dword ptr [esi + 8]
        _emit 0xD8
        _emit 0x60
        _emit 0x08
        // fsub dword ptr [eax + 8]
        _emit 0xD9
        _emit 0x00
        // fld dword ptr [eax]
        _emit 0xD8
        _emit 0x23
        // fsub dword ptr [ebx]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0x40
        _emit 0x04
        // fld dword ptr [eax + 4]
        _emit 0xD8
        _emit 0x63
        _emit 0x04
        // fsub dword ptr [ebx + 4]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // fstp dword ptr [esp + 0x24]
        _emit 0xD9
        _emit 0x40
        _emit 0x08
        // fld dword ptr [eax + 8]
        _emit 0xD8
        _emit 0x63
        _emit 0x08
        // fsub dword ptr [ebx + 8]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x89
        _emit 0x5A
        _emit 0x0C
        // mov dword ptr [edx + 0xc], ebx
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // fst dword ptr [esp + 0x10]
        _emit 0xD9
        _emit 0x1A
        // fstp dword ptr [edx]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // fmul dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // fst dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x5A
        _emit 0x04
        // fstp dword ptr [edx + 4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // fmul dword ptr [esp + 0x20]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // fstp dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov eax, dword ptr [esp + 0xc]
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x89
        _emit 0x42
        _emit 0x08
        // mov dword ptr [edx + 8], eax
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // fmul dword ptr [esp + 0x14]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // fmul dword ptr [esp + 0x10]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x05
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // fld dword ptr [0x1485378]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xDA
        _emit 0xE9
        // fucompp 
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x44
        // test ah, 0x44
        _emit 0x0F
        _emit 0x8B
        _emit 0xD3
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jnp 0x1122f54
        _emit 0xD9
        _emit 0x05
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // fld dword ptr [0x1485378]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xDA
        _emit 0xE9
        // fucompp 
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x44
        // test ah, 0x44
        _emit 0x7B
        _emit 0x0A
        // jnp 0x1122e9c
        _emit 0xD9
        _emit 0xFA
        // fsqrt 
        _emit 0xD8
        _emit 0x3D
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // fdivr dword ptr [0x1485720]
        _emit 0xEB
        _emit 0x08
        // jmp 0x1122ea4
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xD9
        _emit 0x05
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // fld dword ptr [0x1485378]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD9
        _emit 0x12
        // fst dword ptr [edx]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xD9
        _emit 0x52
        _emit 0x04
        // fst dword ptr [edx + 4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
        _emit 0xD9
        _emit 0x52
        _emit 0x08
        // fst dword ptr [edx + 8]
        _emit 0xD9
        _emit 0xCB
        // fxch st(3)
        _emit 0xD8
        _emit 0x0D
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // fmul dword ptr [0x1485378]
        _emit 0xD9
        _emit 0x5A
        _emit 0x0C
        // fstp dword ptr [edx + 0xc]
        _emit 0xD9
        _emit 0xCA
        // fxch st(2)
        _emit 0xD8
        _emit 0x4E
        _emit 0x08
        // fmul dword ptr [esi + 8]
        _emit 0xD9
        _emit 0xCA
        // fxch st(2)
        _emit 0xD8
        _emit 0x4E
        _emit 0x04
        // fmul dword ptr [esi + 4]
        _emit 0xDE
        _emit 0xC2
        // faddp st(2)
        _emit 0xD8
        _emit 0x0E
        // fmul dword ptr [esi]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x5A
        _emit 0x10
        // fstp dword ptr [edx + 0x10]
        _emit 0x8B
        _emit 0x4F
        _emit 0x04
        // mov ecx, dword ptr [edi + 4]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x78
        _emit 0x30
        // mov edi, dword ptr [eax + 0x30]
        _emit 0x8B
        _emit 0x55
        _emit 0x08
        // mov edx, dword ptr [ebp + 8]
        _emit 0x89
        _emit 0x58
        _emit 0x30
        // mov dword ptr [eax + 0x30], ebx
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov eax, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x72
        _emit 0x04
        // mov esi, dword ptr [edx + 4]
        _emit 0x3B
        _emit 0xC6
        // cmp eax, esi
        _emit 0x0F
        _emit 0x8C
        _emit 0x7C
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jl 0x1122d75
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x1C
        // mov ecx, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x51
        _emit 0x10
        // mov edx, dword ptr [ecx + 0x10]
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x3B
        _emit 0xD3
        // cmp edx, ebx
        _emit 0x7E
        _emit 0x17
        // jle 0x1122f1d
        _emit 0x8D
        _emit 0x91
        _emit 0xB4
        _emit 0x0F
        _emit 0x00
        _emit 0x00
        // lea edx, [ecx + 0xfb4]
        _emit 0x8D
        _emit 0x64
        _emit 0x24
        _emit 0x00
        // lea esp, [esp]
        _emit 0x89
        _emit 0x1A
        // mov dword ptr [edx], ebx
        _emit 0x8B
        _emit 0x71
        _emit 0x10
        // mov esi, dword ptr [ecx + 0x10]
        _emit 0x40
        // inc eax
        _emit 0x83
        _emit 0xC2
        _emit 0x50
        // add edx, 0x50
        _emit 0x3B
        _emit 0xC6
        // cmp eax, esi
        _emit 0x7C
        _emit 0xF3
        // jl 0x1122f10
        _emit 0x8B
        _emit 0x51
        _emit 0x08
        // mov edx, dword ptr [ecx + 8]
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x3B
        _emit 0xD3
        // cmp edx, ebx
        _emit 0x7E
        _emit 0x17
        // jle 0x1122f3d
        _emit 0x8D
        _emit 0x51
        _emit 0x50
        // lea edx, [ecx + 0x50]
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0x89
        _emit 0x1A
        // mov dword ptr [edx], ebx
        _emit 0x8B
        _emit 0x71
        _emit 0x08
        // mov esi, dword ptr [ecx + 8]
        _emit 0x40
        // inc eax
        _emit 0x83
        _emit 0xC2
        _emit 0x40
        // add edx, 0x40
        _emit 0x3B
        _emit 0xC6
        // cmp eax, esi
        _emit 0x7C
        _emit 0xF3
        // jl 0x1122f30
        _emit 0x8B
        _emit 0x75
        _emit 0x10
        // mov esi, dword ptr [ebp + 0x10]
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x3B
        _emit 0xF7
        // cmp esi, edi
        _emit 0x0F
        _emit 0x94
        _emit 0xC0
        // sete al
        _emit 0x48
        // dec eax
        _emit 0x83
        _emit 0xE0
        _emit 0x02
        // and eax, 2
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
        _emit 0xC2
        _emit 0x10
        _emit 0x00
        // ret 0x10
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0xB8
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 2
        _emit 0x5B
        // pop ebx
        _emit 0x8B
        _emit 0xE5
        // mov esp, ebp
        _emit 0x5D
        // pop ebp
        _emit 0xC2
        _emit 0x10
        _emit 0x00
        // ret 0x10
    }
}

// @ 0x01122f70  (255 bytes)
__declspec(naked) void FUN_01122f70()
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
        _emit 0x83
        _emit 0xEC
        _emit 0x1C
        // sub esp, 0x1c
        _emit 0x8B
        _emit 0x41
        _emit 0x24
        // mov eax, dword ptr [ecx + 0x24]
        _emit 0x8B
        _emit 0x51
        _emit 0x14
        // mov edx, dword ptr [ecx + 0x14]
        _emit 0xD9
        _emit 0x02
        // fld dword ptr [edx]
        _emit 0x56
        // push esi
        _emit 0xD8
        _emit 0x20
        // fsub dword ptr [eax]
        _emit 0x8B
        _emit 0x71
        _emit 0x34
        // mov esi, dword ptr [ecx + 0x34]
        _emit 0xD9
        _emit 0x42
        _emit 0x04
        // fld dword ptr [edx + 4]
        _emit 0xD8
        _emit 0x60
        _emit 0x04
        // fsub dword ptr [eax + 4]
        _emit 0xD9
        _emit 0x42
        _emit 0x08
        // fld dword ptr [edx + 8]
        _emit 0xD8
        _emit 0x60
        _emit 0x08
        // fsub dword ptr [eax + 8]
        _emit 0xD9
        _emit 0x00
        // fld dword ptr [eax]
        _emit 0xD8
        _emit 0x26
        // fsub dword ptr [esi]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // fstp dword ptr [esp + 0x10]
        _emit 0xD9
        _emit 0x40
        _emit 0x04
        // fld dword ptr [eax + 4]
        _emit 0xD8
        _emit 0x66
        _emit 0x04
        // fsub dword ptr [esi + 4]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x40
        _emit 0x08
        // fld dword ptr [eax + 8]
        _emit 0xD8
        _emit 0x66
        _emit 0x08
        // fsub dword ptr [esi + 8]
        _emit 0xC7
        _emit 0x41
        _emit 0x0C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ecx + 0xc], 0
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // fst dword ptr [esp + 8]
        _emit 0xD9
        _emit 0x19
        // fstp dword ptr [ecx]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // fmul dword ptr [esp + 0x10]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // fst dword ptr [esp + 0xc]
        _emit 0xD9
        _emit 0x59
        _emit 0x04
        // fstp dword ptr [ecx + 4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x04
        // fstp dword ptr [esp + 4]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x89
        _emit 0x41
        _emit 0x08
        // mov dword ptr [ecx + 8], eax
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // fld dword ptr [esp + 4]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x04
        // fmul dword ptr [esp + 4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld dword ptr [esp + 8]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // fmul dword ptr [esp + 8]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x05
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // fld dword ptr [0x1485378]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xDA
        _emit 0xE9
        // fucompp 
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x44
        // test ah, 0x44
        _emit 0x7B
        _emit 0x0A
        // jnp 0x112302b
        _emit 0xD9
        _emit 0xFA
        // fsqrt 
        _emit 0xD8
        _emit 0x3D
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // fdivr dword ptr [0x1485720]
        _emit 0xEB
        _emit 0x08
        // jmp 0x1123033
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xD9
        _emit 0x05
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // fld dword ptr [0x1485378]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld dword ptr [esp + 8]
        _emit 0x5E
        // pop esi
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD9
        _emit 0x11
        // fst dword ptr [ecx]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld dword ptr [esp + 8]
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xD9
        _emit 0x51
        _emit 0x04
        // fst dword ptr [ecx + 4]
        _emit 0xD9
        _emit 0x04
        _emit 0x24
        // fld dword ptr [esp]
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
        _emit 0xD9
        _emit 0x51
        _emit 0x08
        // fst dword ptr [ecx + 8]
        _emit 0xD9
        _emit 0xCB
        // fxch st(3)
        _emit 0xD8
        _emit 0x0D
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // fmul dword ptr [0x1485378]
        _emit 0xD9
        _emit 0x59
        _emit 0x0C
        // fstp dword ptr [ecx + 0xc]
        _emit 0xD9
        _emit 0xCA
        // fxch st(2)
        _emit 0xD8
        _emit 0x4A
        _emit 0x08
        // fmul dword ptr [edx + 8]
        _emit 0xD9
        _emit 0xCA
        // fxch st(2)
        _emit 0xD8
        _emit 0x4A
        _emit 0x04
        // fmul dword ptr [edx + 4]
        _emit 0xDE
        _emit 0xC2
        // faddp st(2)
        _emit 0xD8
        _emit 0x0A
        // fmul dword ptr [edx]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x59
        _emit 0x10
        // fstp dword ptr [ecx + 0x10]
        _emit 0x8B
        _emit 0xE5
        // mov esp, ebp
        _emit 0x5D
        // pop ebp
        _emit 0xC3
        // ret 
    }
}

// @ 0x01123070  (290 bytes)
__declspec(naked) void FUN_01123070()
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
        _emit 0x83
        _emit 0xEC
        _emit 0x14
        // sub esp, 0x14
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        call FUN_01122b20
        _emit 0x8B
        _emit 0x4D
        _emit 0x08
        // mov ecx, dword ptr [ebp + 8]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x88
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov byte ptr [esp + 0x1c], bl
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebx, [ebx]
        _emit 0x8A
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov al, byte ptr [esp + 0x1c]
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x0F
        _emit 0x85
        _emit 0xEB
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0x1123187
        _emit 0xC7
        _emit 0x41
        _emit 0x44
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ecx + 0x44], 3
        _emit 0x33
        _emit 0xFF
        // xor edi, edi
        _emit 0x8D
        _emit 0x51
        _emit 0x14
        // lea edx, [ecx + 0x14]
        _emit 0x3B
        _emit 0xD3
        // cmp edx, ebx
        _emit 0x0F
        _emit 0x84
        _emit 0xA9
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0x1123159
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x8B
        _emit 0x72
        _emit 0x04
        // mov esi, dword ptr [edx + 4]
        _emit 0x8B
        _emit 0x36
        // mov esi, dword ptr [esi]
        _emit 0xD9
        _emit 0x06
        // fld dword ptr [esi]
        _emit 0xD8
        _emit 0x20
        // fsub dword ptr [eax]
        _emit 0xD9
        _emit 0x46
        _emit 0x04
        // fld dword ptr [esi + 4]
        _emit 0xD8
        _emit 0x60
        _emit 0x04
        // fsub dword ptr [eax + 4]
        _emit 0xD9
        _emit 0x46
        _emit 0x08
        // fld dword ptr [esi + 8]
        _emit 0xD8
        _emit 0x60
        _emit 0x08
        // fsub dword ptr [eax + 8]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0x49
        _emit 0x08
        // fmul dword ptr [ecx + 8]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0x49
        _emit 0x04
        // fmul dword ptr [ecx + 4]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0x09
        // fmul dword ptr [ecx]
        _emit 0xD9
        _emit 0xC4
        // fld st(4)
        _emit 0xD8
        _emit 0x49
        _emit 0x08
        // fmul dword ptr [ecx + 8]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0xC4
        // fld st(4)
        _emit 0xD8
        _emit 0x49
        _emit 0x04
        // fmul dword ptr [ecx + 4]
        _emit 0xD9
        _emit 0xC4
        // fld st(4)
        _emit 0xD8
        _emit 0x09
        // fmul dword ptr [ecx]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x48
        _emit 0x04
        // fmul dword ptr [eax + 4]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x48
        _emit 0x08
        // fmul dword ptr [eax + 8]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x08
        // fmul dword ptr [eax]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x18
        // fst dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // fmul dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xD9
        _emit 0xC4
        // fld st(4)
        _emit 0xD8
        _emit 0xCD
        // fmul st(5)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC3
        // fld st(3)
        _emit 0xD8
        _emit 0xCC
        // fmul st(4)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x0D
        _emit 0x80
        _emit 0x61
        _emit 0x4A
        _emit 0x01
        // fmul dword ptr [0x14a6180]
        _emit 0xDE
        _emit 0xD9
        // fcompp 
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x75
        _emit 0x2F
        // jne 0x1123159
        _emit 0x8B
        _emit 0x42
        _emit 0x08
        // mov eax, dword ptr [edx + 8]
        _emit 0x8B
        _emit 0x70
        _emit 0x0C
        // mov esi, dword ptr [eax + 0xc]
        _emit 0x8B
        _emit 0x45
        _emit 0x08
        // mov eax, dword ptr [ebp + 8]
        _emit 0xD9
        _emit 0x40
        _emit 0x10
        // fld dword ptr [eax + 0x10]
        _emit 0xD8
        _emit 0x1D
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // fcomp dword ptr [0x1485378]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x75
        _emit 0x25
        // jne 0x1123168
        _emit 0x8B
        _emit 0x45
        _emit 0x08
        // mov eax, dword ptr [ebp + 8]
        _emit 0xD9
        _emit 0x40
        _emit 0x10
        // fld dword ptr [eax + 0x10]
        _emit 0xD8
        _emit 0x0D
        _emit 0xB4
        _emit 0xC4
        _emit 0x3E
        _emit 0x01
        // fmul dword ptr [0x13ec4b4]
        _emit 0xD8
        _emit 0x5E
        _emit 0x10
        // fcomp dword ptr [esi + 0x10]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x75
        _emit 0x0F
        // jne 0x1123168
        _emit 0x47
        // inc edi
        _emit 0x83
        _emit 0xC2
        _emit 0x10
        // add edx, 0x10
        _emit 0x83
        _emit 0xFF
        _emit 0x03
        // cmp edi, 3
        _emit 0x0F
        _emit 0x8C
        _emit 0x42
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jl 0x11230a8
        _emit 0xEB
        _emit 0x16
        // jmp 0x112317e
        _emit 0x8B
        _emit 0x46
        _emit 0x44
        // mov eax, dword ptr [esi + 0x44]
        _emit 0x8B
        _emit 0xD7
        // mov edx, edi
        _emit 0xC1
        _emit 0xE2
        _emit 0x04
        // shl edx, 4
        _emit 0x8B
        _emit 0x5C
        _emit 0x0A
        _emit 0x1C
        // mov ebx, dword ptr [edx + ecx + 0x1c]
        _emit 0x83
        _emit 0xF8
        _emit 0x03
        // cmp eax, 3
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x0F
        _emit 0x94
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // sete byte ptr [esp + 0x1c]
        _emit 0x83
        _emit 0xFF
        _emit 0x03
        // cmp edi, 3
        _emit 0x0F
        _emit 0x85
        _emit 0x09
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jne 0x1123090
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x8B
        _emit 0xC1
        // mov eax, ecx
        _emit 0x5B
        // pop ebx
        _emit 0x8B
        _emit 0xE5
        // mov esp, ebp
        _emit 0x5D
        // pop ebp
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x011231a0  (866 bytes)
__declspec(naked) void FUN_011231a0()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x20
        // sub esp, 0x20
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // mov ecx, dword ptr [esp + 0x24]
        _emit 0x8B
        _emit 0x41
        _emit 0x10
        // mov eax, dword ptr [ecx + 0x10]
        _emit 0x48
        // dec eax
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x38
        // mov ebp, dword ptr [esp + 0x38]
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        _emit 0xEE
        _emit 0xFF
        _emit 0x7F
        _emit 0x7F
        // mov dword ptr [esp + 0xc], 0x7f7fffee
        _emit 0x0F
        _emit 0x88
        _emit 0x57
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // js 0x1123415
        _emit 0x53
        // push ebx
        _emit 0x8D
        _emit 0x14
        _emit 0x80
        // lea edx, [eax + eax*4]
        _emit 0xC1
        _emit 0xE2
        _emit 0x04
        // shl edx, 4
        _emit 0x56
        // push esi
        _emit 0x40
        // inc eax
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x9C
        _emit 0x0A
        _emit 0x80
        _emit 0x0F
        _emit 0x00
        _emit 0x00
        // lea ebx, [edx + ecx + 0xf80]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], eax
        _emit 0xD9
        _emit 0x03
        // fld dword ptr [ebx]
        _emit 0x8D
        _emit 0x53
        _emit 0xF0
        // lea edx, [ebx - 0x10]
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD8
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // fcomp dword ptr [esp + 0x18]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x0F
        _emit 0x84
        _emit 0x13
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // je 0x1123400
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x38
        // mov ecx, dword ptr [esp + 0x38]
        _emit 0x8B
        _emit 0x41
        _emit 0x10
        // mov eax, dword ptr [ecx + 0x10]
        _emit 0x48
        // dec eax
        _emit 0x83
        _emit 0xF8
        _emit 0x01
        // cmp eax, 1
        _emit 0x0F
        _emit 0x8C
        _emit 0x02
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // jl 0x1123400
        _emit 0x8D
        _emit 0x34
        _emit 0x80
        // lea esi, [eax + eax*4]
        _emit 0xC1
        _emit 0xE6
        _emit 0x04
        // shl esi, 4
        _emit 0x8D
        _emit 0x8C
        _emit 0x0E
        _emit 0x80
        _emit 0x0F
        _emit 0x00
        _emit 0x00
        // lea ecx, [esi + ecx + 0xf80]
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0xD9
        _emit 0x01
        // fld dword ptr [ecx]
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD8
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // fcomp dword ptr [esp + 0x18]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x0F
        _emit 0x84
        _emit 0xCF
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0x11233f6
        _emit 0xD9
        _emit 0x41
        _emit 0xF8
        // fld dword ptr [ecx - 8]
        _emit 0x8D
        _emit 0x71
        _emit 0xF0
        // lea esi, [ecx - 0x10]
        _emit 0xD8
        _emit 0x4A
        _emit 0x08
        // fmul dword ptr [edx + 8]
        _emit 0xD9
        _emit 0x42
        _emit 0x04
        // fld dword ptr [edx + 4]
        _emit 0xD8
        _emit 0x49
        _emit 0xF4
        // fmul dword ptr [ecx - 0xc]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x06
        // fld dword ptr [esi]
        _emit 0xD8
        _emit 0x0A
        // fmul dword ptr [edx]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x34
        // fst dword ptr [esp + 0x34]
        _emit 0xD8
        _emit 0x1D
        _emit 0x88
        _emit 0xC4
        _emit 0x3E
        _emit 0x01
        // fcomp dword ptr [0x13ec488]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x0F
        _emit 0x8B
        _emit 0xA3
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jnp 0x11233f6
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], eax
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], eax
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // fmul dword ptr [esp + 0x34]
        _emit 0xD8
        _emit 0x6C
        _emit 0x24
        _emit 0x10
        // fsubr dword ptr [esp + 0x10]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // fmul dword ptr [esp + 0x34]
        _emit 0xD8
        _emit 0x6C
        _emit 0x24
        _emit 0x14
        // fsubr dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0x1D
        _emit 0x78
        _emit 0x61
        _emit 0x4A
        _emit 0x01
        // fcomp dword ptr [0x14a6178]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x0F
        _emit 0x85
        _emit 0xF1
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0x1123385
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0x1D
        _emit 0x78
        _emit 0x61
        _emit 0x4A
        _emit 0x01
        // fcomp dword ptr [0x14a6178]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x0F
        _emit 0x85
        _emit 0xB3
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0x112335c
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fcomp dword ptr [esp + 0x20]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x75
        _emit 0x40
        // jne 0x11232f8
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0x74
        _emit 0x24
        _emit 0x1C
        // fdiv dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // fst dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // fmul dword ptr [esp + 0x34]
        _emit 0xD8
        _emit 0x05
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // fadd dword ptr [0x1485720]
        _emit 0xD8
        _emit 0x3D
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // fdivr dword ptr [0x1485720]
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // fst dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x44
        // fstp dword ptr [esp + 0x44]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // fmul dword ptr [esp + 0x10]
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // fst dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // fmul dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0xEB
        _emit 0x3A
        // jmp 0x1123332
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0x74
        _emit 0x24
        _emit 0x20
        // fdiv dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // fst dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // fmul dword ptr [esp + 0x34]
        _emit 0xD8
        _emit 0x05
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // fadd dword ptr [0x1485720]
        _emit 0xD8
        _emit 0x3D
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // fdivr dword ptr [0x1485720]
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // fst dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x44
        // fstp dword ptr [esp + 0x44]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x44
        // fmul dword ptr [esp + 0x44]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // fmul dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // fmul dword ptr [esp + 0x34]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // fld dword ptr [esp + 0x34]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // fmul dword ptr [esp + 0x34]
        _emit 0xD8
        _emit 0x2D
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // fsubr dword ptr [0x1485720]
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xDE
        _emit 0xCA
        // fmulp st(2)
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xDE
        _emit 0xC2
        // faddp st(2)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x34
        // fst dword ptr [esp + 0x34]
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0xEB
        _emit 0x6E
        // jmp 0x11233ca
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x1D
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // fcomp dword ptr [0x1485378]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x75
        _emit 0x41
        // jne 0x11233ae
        _emit 0xD9
        _emit 0x05
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // fld dword ptr [0x1485720]
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x44
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x44], 0
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // fmul dword ptr [esp + 0x10]
        _emit 0xEB
        _emit 0x41
        // jmp 0x11233c6
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xD8
        _emit 0x1D
        _emit 0x78
        _emit 0x61
        _emit 0x4A
        _emit 0x01
        // fcomp dword ptr [0x14a6178]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x75
        _emit 0x18
        // jne 0x11233ae
        _emit 0xD9
        _emit 0x05
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // fld dword ptr [0x1485378]
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x44
        _emit 0x00
        _emit 0x00
        _emit 0x80
        _emit 0x3F
        // mov dword ptr [esp + 0x44], 0x3f800000
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // fmul dword ptr [esp + 0x14]
        _emit 0xEB
        _emit 0x18
        // jmp 0x11233c6
        _emit 0xD9
        _emit 0x05
        _emit 0x64
        _emit 0x10
        _emit 0x47
        _emit 0x01
        // fld dword ptr [0x1471064]
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x44
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x3F
        // mov dword ptr [esp + 0x44], 0x3f000000
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // fld dword ptr [esp + 0x34]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // fmul dword ptr [esp + 0x34]
        _emit 0xD9
        _emit 0xE0
        // fchs 
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x34
        // fst dword ptr [esp + 0x34]
        _emit 0xD8
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // fcomp dword ptr [esp + 0x18]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x1F
        // jp 0x11233f4
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // mov eax, dword ptr [esp + 0x44]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x28
        // fstp dword ptr [esp + 0x28]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // mov eax, dword ptr [esp + 0x40]
        _emit 0x89
        _emit 0x10
        // mov dword ptr [eax], edx
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // mov eax, dword ptr [esp + 0x34]
        _emit 0x89
        _emit 0x75
        _emit 0x00
        // mov dword ptr [ebp], esi
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], eax
        _emit 0xEB
        _emit 0x02
        // jmp 0x11233f6
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x83
        _emit 0xE9
        _emit 0x50
        // sub ecx, 0x50
        _emit 0x4F
        // dec edi
        _emit 0x0F
        _emit 0x85
        _emit 0x10
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jne 0x1123210
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // mov eax, dword ptr [esp + 0x24]
        _emit 0x83
        _emit 0xEB
        _emit 0x50
        // sub ebx, 0x50
        _emit 0x48
        // dec eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], eax
        _emit 0x0F
        _emit 0x85
        _emit 0xC1
        _emit 0xFD
        _emit 0xFF
        _emit 0xFF
        // jne 0x11231d3
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // mov ecx, dword ptr [esp + 0x34]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0xD8
        _emit 0x08
        // fmul dword ptr [eax]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x30
        // mov ecx, dword ptr [esp + 0x30]
        _emit 0xD9
        _emit 0x19
        // fstp dword ptr [ecx]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0x48
        _emit 0x04
        // fmul dword ptr [eax + 4]
        _emit 0xD9
        _emit 0x59
        _emit 0x04
        // fstp dword ptr [ecx + 4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0x48
        _emit 0x08
        // fmul dword ptr [eax + 8]
        _emit 0xD9
        _emit 0x59
        _emit 0x08
        // fstp dword ptr [ecx + 8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0x48
        _emit 0x0C
        // fmul dword ptr [eax + 0xc]
        _emit 0xD9
        _emit 0x59
        _emit 0x0C
        // fstp dword ptr [ecx + 0xc]
        _emit 0x8B
        _emit 0x45
        _emit 0x00
        // mov eax, dword ptr [ebp]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0x5D
        // pop ebp
        _emit 0xD8
        _emit 0x08
        // fmul dword ptr [eax]
        _emit 0xD8
        _emit 0x01
        // fadd dword ptr [ecx]
        _emit 0xD9
        _emit 0x19
        // fstp dword ptr [ecx]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0x48
        _emit 0x04
        // fmul dword ptr [eax + 4]
        _emit 0xD8
        _emit 0x41
        _emit 0x04
        // fadd dword ptr [ecx + 4]
        _emit 0xD9
        _emit 0x59
        _emit 0x04
        // fstp dword ptr [ecx + 4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0x48
        _emit 0x08
        // fmul dword ptr [eax + 8]
        _emit 0xD8
        _emit 0x41
        _emit 0x08
        // fadd dword ptr [ecx + 8]
        _emit 0xD9
        _emit 0x59
        _emit 0x08
        // fstp dword ptr [ecx + 8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0x48
        _emit 0x0C
        // fmul dword ptr [eax + 0xc]
        _emit 0xD8
        _emit 0x41
        _emit 0x0C
        // fadd dword ptr [ecx + 0xc]
        _emit 0xD9
        _emit 0x59
        _emit 0x0C
        // fstp dword ptr [ecx + 0xc]
        _emit 0xD9
        _emit 0x41
        _emit 0x08
        // fld dword ptr [ecx + 8]
        _emit 0xD9
        _emit 0x41
        _emit 0x04
        // fld dword ptr [ecx + 4]
        _emit 0xD9
        _emit 0x01
        // fld dword ptr [ecx]
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0xDE
        _emit 0xCB
        // fmulp st(3)
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xDE
        _emit 0xC3
        // faddp st(3)
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xDE
        _emit 0xC3
        // faddp st(3)
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xD9
        _emit 0x05
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // fld dword ptr [0x1485378]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xDA
        _emit 0xE9
        // fucompp 
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x44
        // test ah, 0x44
        _emit 0x7B
        _emit 0x0A
        // jnp 0x11234b1
        _emit 0xD9
        _emit 0xFA
        // fsqrt 
        _emit 0xD8
        _emit 0x3D
        _emit 0x20
        _emit 0x57
        _emit 0x48
        _emit 0x01
        // fdivr dword ptr [0x1485720]
        _emit 0xEB
        _emit 0x08
        // jmp 0x11234b9
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xD9
        _emit 0x05
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // fld dword ptr [0x1485378]
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD8
        _emit 0x09
        // fmul dword ptr [ecx]
        _emit 0xD9
        _emit 0x19
        // fstp dword ptr [ecx]
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD8
        _emit 0x49
        _emit 0x04
        // fmul dword ptr [ecx + 4]
        _emit 0xD9
        _emit 0x59
        _emit 0x04
        // fstp dword ptr [ecx + 4]
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD8
        _emit 0x49
        _emit 0x08
        // fmul dword ptr [ecx + 8]
        _emit 0xD9
        _emit 0x59
        _emit 0x08
        // fstp dword ptr [ecx + 8]
        _emit 0xD8
        _emit 0x49
        _emit 0x0C
        // fmul dword ptr [ecx + 0xc]
        _emit 0xD9
        _emit 0x59
        _emit 0x0C
        // fstp dword ptr [ecx + 0xc]
        _emit 0xD9
        _emit 0x05
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // fld dword ptr [0x1485378]
        _emit 0xD8
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fcomp dword ptr [esp + 8]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x75
        _emit 0x0F
        // jne 0x11234f5
        _emit 0xD9
        _emit 0x05
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // fld dword ptr [0x1485378]
        _emit 0xD9
        _emit 0xFA
        // fsqrt 
        _emit 0xD9
        _emit 0x59
        _emit 0x0C
        // fstp dword ptr [ecx + 0xc]
        _emit 0x83
        _emit 0xC4
        _emit 0x20
        // add esp, 0x20
        _emit 0xC3
        // ret 
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld dword ptr [esp + 8]
        _emit 0xD9
        _emit 0xFA
        // fsqrt 
        _emit 0xD9
        _emit 0x59
        _emit 0x0C
        // fstp dword ptr [ecx + 0xc]
        _emit 0x83
        _emit 0xC4
        _emit 0x20
        // add esp, 0x20
        _emit 0xC3
        // ret 
    }
}

// @ 0x01123510  (102 bytes)
__declspec(naked) void FUN_01123510()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // mov ebx, dword ptr [esp + 0x14]
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x14
        // mov ebp, dword ptr [esp + 0x14]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        // mov edi, dword ptr [esp + 0x14]
        _emit 0xC7
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebx], 0
        _emit 0x8D
        _emit 0x46
        _emit 0x04
        // lea eax, [esi + 4]
        _emit 0x50
        // push eax
        _emit 0xC7
        _emit 0x45
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [ebp], 0
        _emit 0xC7
        _emit 0x00
        _emit 0xEE
        _emit 0xFF
        _emit 0x7F
        _emit 0x7F
        // mov dword ptr [eax], 0x7f7fffee
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov eax, dword ptr [esp + 0x1c]
        _emit 0x56
        // push esi
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xC7
        _emit 0x06
        _emit 0x95
        _emit 0xBF
        _emit 0xD6
        _emit 0x33
        // mov dword ptr [esi], 0x33d6bf95
        call FUN_01122b70
        _emit 0x83
        _emit 0xF8
        _emit 0x01
        // cmp eax, 1
        _emit 0x89
        _emit 0x47
        _emit 0x44
        // mov dword ptr [edi + 0x44], eax
        _emit 0x75
        _emit 0x16
        // jne 0x112356a
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x51
        // push ecx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_01122c00
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x10
        _emit 0x00
        // ret 0x10
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0xB8
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 2
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x10
        _emit 0x00
        // ret 0x10
    }
}

// @ 0x01123580  (250 bytes)
__declspec(naked) void FUN_01123580()
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
        _emit 0x51
        // push ecx
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8D
        _emit 0x9E
        _emit 0x70
        _emit 0x0F
        _emit 0x00
        _emit 0x00
        // lea ebx, [esi + 0xf70]
        _emit 0x8D
        _emit 0x86
        _emit 0xB0
        _emit 0x10
        _emit 0x00
        _emit 0x00
        // lea eax, [esi + 0x10b0]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0x3B
        _emit 0xC8
        // cmp ecx, eax
        _emit 0x57
        // push edi
        _emit 0xC7
        _emit 0x46
        _emit 0x10
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x10], 4
        _emit 0xBA
        _emit 0x88
        _emit 0x61
        _emit 0x4A
        _emit 0x01
        // mov edx, 0x14a6188
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], ebx
        _emit 0x74
        _emit 0x58
        // je 0x1123606
        _emit 0x8B
        _emit 0xFF
        // mov edi, edi
        _emit 0x8D
        _emit 0x41
        _emit 0x24
        // lea eax, [ecx + 0x24]
        _emit 0x89
        _emit 0x41
        _emit 0x18
        // mov dword ptr [ecx + 0x18], eax
        _emit 0x8D
        _emit 0x41
        _emit 0x34
        // lea eax, [ecx + 0x34]
        _emit 0x8D
        _emit 0x79
        _emit 0x44
        // lea edi, [ecx + 0x44]
        _emit 0x89
        _emit 0x41
        _emit 0x28
        // mov dword ptr [ecx + 0x28], eax
        _emit 0x8D
        _emit 0x41
        _emit 0x14
        // lea eax, [ecx + 0x14]
        _emit 0x3B
        _emit 0xC7
        // cmp eax, edi
        _emit 0xC7
        _emit 0x07
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi], 0
        _emit 0x89
        _emit 0x41
        _emit 0x38
        // mov dword ptr [ecx + 0x38], eax
        _emit 0x73
        _emit 0x26
        // jae 0x11235f5
        _emit 0x90
        // nop 
        _emit 0x89
        _emit 0x48
        _emit 0x0C
        // mov dword ptr [eax + 0xc], ecx
        _emit 0x8B
        _emit 0x1A
        // mov ebx, dword ptr [edx]
        _emit 0x8D
        _emit 0x5C
        _emit 0x33
        _emit 0x20
        // lea ebx, [ebx + esi + 0x20]
        _emit 0x89
        _emit 0x18
        // mov dword ptr [eax], ebx
        _emit 0x8B
        _emit 0x5A
        _emit 0x08
        // mov ebx, dword ptr [edx + 8]
        _emit 0x03
        _emit 0x5A
        _emit 0x04
        // add ebx, dword ptr [edx + 4]
        _emit 0x83
        _emit 0xC0
        _emit 0x10
        // add eax, 0x10
        _emit 0x8D
        _emit 0x9C
        _emit 0x33
        _emit 0x84
        _emit 0x0F
        _emit 0x00
        _emit 0x00
        // lea ebx, [ebx + esi + 0xf84]
        _emit 0x89
        _emit 0x58
        _emit 0xF8
        // mov dword ptr [eax - 8], ebx
        _emit 0x83
        _emit 0xC2
        _emit 0x0C
        // add edx, 0xc
        _emit 0x3B
        _emit 0xC7
        // cmp eax, edi
        _emit 0x72
        _emit 0xDB
        // jb 0x11235d0
        _emit 0x83
        _emit 0xC1
        _emit 0x50
        // add ecx, 0x50
        _emit 0x8D
        _emit 0x86
        _emit 0xB0
        _emit 0x10
        _emit 0x00
        _emit 0x00
        // lea eax, [esi + 0x10b0]
        _emit 0x3B
        _emit 0xC8
        // cmp ecx, eax
        _emit 0x75
        _emit 0xAE
        // jne 0x11235b0
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // mov ebx, dword ptr [esp + 0xc]
        _emit 0x8D
        _emit 0x8E
        _emit 0x60
        _emit 0x10
        _emit 0x00
        _emit 0x00
        // lea ecx, [esi + 0x1060]
        call FUN_01122f70
        _emit 0xD9
        _emit 0x46
        _emit 0x20
        // fld dword ptr [esi + 0x20]
        _emit 0xD8
        _emit 0x66
        _emit 0x60
        // fsub dword ptr [esi + 0x60]
        _emit 0x8D
        _emit 0x7E
        _emit 0x20
        // lea edi, [esi + 0x20]
        _emit 0xD9
        _emit 0x47
        _emit 0x04
        // fld dword ptr [edi + 4]
        _emit 0x8D
        _emit 0x56
        _emit 0x60
        // lea edx, [esi + 0x60]
        _emit 0xD8
        _emit 0x62
        _emit 0x04
        // fsub dword ptr [edx + 4]
        _emit 0xD9
        _emit 0x47
        _emit 0x08
        // fld dword ptr [edi + 8]
        _emit 0xD8
        _emit 0x62
        _emit 0x08
        // fsub dword ptr [edx + 8]
        _emit 0xD8
        _emit 0x49
        _emit 0x08
        // fmul dword ptr [ecx + 8]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x49
        _emit 0x04
        // fmul dword ptr [ecx + 4]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x09
        // fmul dword ptr [ecx]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x1D
        _emit 0x78
        _emit 0x53
        _emit 0x48
        _emit 0x01
        // fcomp dword ptr [0x1485378]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x75
        _emit 0x1B
        // jne 0x1123661
        _emit 0x89
        _emit 0x96
        _emit 0x24
        _emit 0x10
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x1024], edx
        _emit 0x89
        _emit 0x96
        _emit 0xD4
        _emit 0x0F
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xfd4], edx
        _emit 0x89
        _emit 0x53
        _emit 0x14
        // mov dword ptr [ebx + 0x14], edx
        _emit 0x89
        _emit 0x79
        _emit 0x14
        // mov dword ptr [ecx + 0x14], edi
        _emit 0x89
        _emit 0xBE
        _emit 0xE4
        _emit 0x0F
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xfe4], edi
        _emit 0x89
        _emit 0x7B
        _emit 0x34
        // mov dword ptr [ebx + 0x34], edi
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xBE
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov esi, 4
        call FUN_01122f70
        _emit 0x83
        _emit 0xC1
        _emit 0x50
        // add ecx, 0x50
        _emit 0x4E
        // dec esi
        _emit 0x75
        _emit 0xF5
        // jne 0x1123668
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

// @ 0x01123680  (139 bytes)
__declspec(naked) void FUN_01123680()
{
    __asm {
        _emit 0x81
        _emit 0xEC
        _emit 0x9C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // sub esp, 0x19c
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xB4
        _emit 0x24
        _emit 0xA4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov esi, dword ptr [esp + 0x1a4]
        _emit 0x56
        // push esi
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // lea edx, [esp + 8]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // lea eax, [esp + 0x14]
        _emit 0x52
        // push edx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], eax
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x10], 0
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x64
        _emit 0x00
        _emit 0x00
        _emit 0x80
        // mov dword ptr [esp + 0x14], 0x80000064
        call FUN_01122cd0
        _emit 0x8B
        _emit 0x94
        _emit 0x24
        _emit 0xA8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [esp + 0x1a8]
        _emit 0x8D
        _emit 0x84
        _emit 0x24
        _emit 0xAC
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea eax, [esp + 0x1ac]
        _emit 0x50
        // push eax
        _emit 0x52
        // push edx
        _emit 0x56
        // push esi
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // lea eax, [esp + 0x10]
        _emit 0x50
        // push eax
        call FUN_01122d50
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov eax, dword ptr [esp + 0xc]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x78
        _emit 0x29
        // js 0x11236ff
        _emit 0x8B
        _emit 0x0D
        _emit 0x74
        _emit 0x41
        _emit 0x6E
        _emit 0x01
        // mov ecx, dword ptr [0x16e4174]
        _emit 0x51
        // push ecx
        _emit 0xFF
        _emit 0x15
        _emit 0xBC
        _emit 0xC2
        _emit 0x3C
        _emit 0x01
        // call dword ptr [0x13cc2bc]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // mov edx, dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x04
        // mov ecx, dword ptr [esp + 4]
        _emit 0x81
        _emit 0xE2
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        _emit 0x3F
        // and edx, 0x3fffffff
        _emit 0x6A
        _emit 0x14
        // push 0x14
        _emit 0xC1
        _emit 0xE2
        _emit 0x02
        // shl edx, 2
        _emit 0x52
        // push edx
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_0107db10
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x5E
        // pop esi
        _emit 0x81
        _emit 0xC4
        _emit 0x9C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // add esp, 0x19c
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
    }
}

// @ 0x01123710  (307 bytes)
__declspec(naked) void FUN_01123710()
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
        _emit 0x83
        _emit 0xEC
        _emit 0x2C
        // sub esp, 0x2c
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5D
        _emit 0x0C
        // mov ebx, dword ptr [ebp + 0xc]
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x89
        _emit 0x47
        _emit 0x20
        // mov dword ptr [edi + 0x20], eax
        _emit 0x8B
        _emit 0x53
        _emit 0x04
        // mov edx, dword ptr [ebx + 4]
        _emit 0x89
        _emit 0x57
        _emit 0x24
        // mov dword ptr [edi + 0x24], edx
        _emit 0x8B
        _emit 0x43
        _emit 0x08
        // mov eax, dword ptr [ebx + 8]
        _emit 0x89
        _emit 0x47
        _emit 0x28
        // mov dword ptr [edi + 0x28], eax
        _emit 0x8B
        _emit 0x53
        _emit 0x0C
        // mov edx, dword ptr [ebx + 0xc]
        _emit 0x89
        _emit 0x57
        _emit 0x2C
        // mov dword ptr [edi + 0x2c], edx
        _emit 0xD9
        _emit 0x03
        // fld dword ptr [ebx]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0xD9
        _emit 0xE0
        // fchs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // fstp dword ptr [esp + 0x10]
        _emit 0x57
        // push edi
        _emit 0xD9
        _emit 0x43
        _emit 0x04
        // fld dword ptr [ebx + 4]
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // lea edx, [esp + 0x14]
        _emit 0xD9
        _emit 0xE0
        // fchs 
        _emit 0x52
        // push edx
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x43
        _emit 0x08
        // fld dword ptr [ebx + 8]
        _emit 0xD9
        _emit 0xE0
        // fchs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0x43
        _emit 0x0C
        // fld dword ptr [ebx + 0xc]
        _emit 0xD9
        _emit 0xE0
        // fchs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // fstp dword ptr [esp + 0x24]
        _emit 0xFF
        _emit 0x50
        _emit 0x24
        // call dword ptr [eax + 0x24]
        _emit 0xD9
        _emit 0x03
        // fld dword ptr [ebx]
        _emit 0x8B
        _emit 0x4D
        _emit 0x08
        // mov ecx, dword ptr [ebp + 8]
        _emit 0xD9
        _emit 0x43
        _emit 0x04
        // fld dword ptr [ebx + 4]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0xD9
        _emit 0x43
        _emit 0x08
        // fld dword ptr [ebx + 8]
        _emit 0x8D
        _emit 0x5F
        _emit 0x10
        // lea ebx, [edi + 0x10]
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0x53
        // push ebx
        _emit 0xD8
        _emit 0x0E
        // fmul dword ptr [esi]
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // lea edx, [esp + 0x24]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0x52
        // push edx
        _emit 0xD8
        _emit 0x4E
        _emit 0x08
        // fmul dword ptr [esi + 8]
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x34
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x34], 0
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0xD8
        _emit 0x4E
        _emit 0x04
        // fmul dword ptr [esi + 4]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x28
        // fstp dword ptr [esp + 0x28]
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0xD8
        _emit 0x4E
        _emit 0x10
        // fmul dword ptr [esi + 0x10]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0x4E
        _emit 0x18
        // fmul dword ptr [esi + 0x18]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
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
        _emit 0x5C
        _emit 0x24
        _emit 0x2C
        // fstp dword ptr [esp + 0x2c]
        _emit 0xD9
        _emit 0xCA
        // fxch st(2)
        _emit 0xD8
        _emit 0x4E
        _emit 0x20
        // fmul dword ptr [esi + 0x20]
        _emit 0xD9
        _emit 0xCA
        // fxch st(2)
        _emit 0xD8
        _emit 0x4E
        _emit 0x28
        // fmul dword ptr [esi + 0x28]
        _emit 0xDE
        _emit 0xC2
        // faddp st(2)
        _emit 0xD8
        _emit 0x4E
        _emit 0x24
        // fmul dword ptr [esi + 0x24]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x30
        // fstp dword ptr [esp + 0x30]
        _emit 0xFF
        _emit 0x50
        _emit 0x24
        // call dword ptr [eax + 0x24]
        _emit 0xD9
        _emit 0x03
        // fld dword ptr [ebx]
        _emit 0xD9
        _emit 0x43
        _emit 0x04
        // fld dword ptr [ebx + 4]
        _emit 0xD9
        _emit 0x43
        _emit 0x08
        // fld dword ptr [ebx + 8]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0x4E
        _emit 0x10
        // fmul dword ptr [esi + 0x10]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0x4E
        _emit 0x20
        // fmul dword ptr [esi + 0x20]
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
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0x4E
        _emit 0x14
        // fmul dword ptr [esi + 0x14]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0x4E
        _emit 0x24
        // fmul dword ptr [esi + 0x24]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0x5B
        // pop ebx
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
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4E
        _emit 0x18
        // fmul dword ptr [esi + 0x18]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4E
        _emit 0x28
        // fmul dword ptr [esi + 0x28]
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
        _emit 0x07
        // fld dword ptr [edi]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x1C
        // fsub dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x47
        _emit 0x04
        // fld dword ptr [edi + 4]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x20
        // fsub dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0x47
        _emit 0x08
        // fld dword ptr [edi + 8]
        _emit 0xD8
        _emit 0xE3
        // fsub st(3)
        _emit 0xD8
        _emit 0x4F
        _emit 0x28
        // fmul dword ptr [edi + 0x28]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4F
        _emit 0x24
        // fmul dword ptr [edi + 0x24]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4F
        _emit 0x20
        // fmul dword ptr [edi + 0x20]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x5F
        _emit 0x2C
        // fstp dword ptr [edi + 0x2c]
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x8B
        _emit 0xE5
        // mov esp, ebp
        _emit 0x5D
        // pop ebp
        _emit 0xC3
        // ret 
    }
}
