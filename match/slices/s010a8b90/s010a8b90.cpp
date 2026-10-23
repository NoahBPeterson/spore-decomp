// Slice s010a8b90: Spore collision/window math routines.  Names are Claude-coined
// from usage.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef unsigned int uint;

// Shared float constants referenced by the x87 kernels below.  Named so the
// operand encodes as a ds-relative displacement with a COFF relocation,
// exactly like the original.
extern float kP1;       // 0x01485378
extern float kP2;       // 0x014a2394
extern float kP3;       // 0x01485720
extern float kP4;       // 0x013f9428
extern float kP5;       // 0x01471064

// =============================================================================
// @ 0x010a8cb0  Plane-side test.  Incoming: ecx = point, eax = plane (origin at
// +0x10..+0x18, normal at +0..+8), edx = out bool.  Returns edx; *out = 1 when
// dot(point - origin, normal) < -0.001.  Emitted byte-by-byte because MSVC's
// inline assembler rejects the x87 operand forms the original uses.
__declspec(naked) void FUN_010a8cb0()
{
    __asm {
        _emit 0xD9
        _emit 0x01                    // fld    dword ptr [ecx]
        _emit 0xD8
        _emit 0x60
        _emit 0x10                    // fsub   dword ptr [eax + 0x10]
        _emit 0xD9
        _emit 0x41
        _emit 0x04                    // fld    dword ptr [ecx + 4]
        _emit 0xD8
        _emit 0x60
        _emit 0x14                    // fsub   dword ptr [eax + 0x14]
        _emit 0xD9
        _emit 0x41
        _emit 0x08                    // fld    dword ptr [ecx + 8]
        _emit 0xD8
        _emit 0x60
        _emit 0x18                    // fsub   dword ptr [eax + 0x18]
        _emit 0xD8
        _emit 0x48
        _emit 0x08                    // fmul   dword ptr [eax + 8]
        _emit 0xD9
        _emit 0xC9                    // fxch   st(1)
        _emit 0xD8
        _emit 0x48
        _emit 0x04                    // fmul   dword ptr [eax + 4]
        _emit 0xDE
        _emit 0xC1                    // faddp  st(1)
        _emit 0xD9
        _emit 0xC9                    // fxch   st(1)
        _emit 0xD8
        _emit 0x08                    // fmul   dword ptr [eax]
        _emit 0xDE
        _emit 0xC1                    // faddp  st(1)
        _emit 0xD8
        _emit 0x1D                    // fcomp  dword ptr [0x13ef56c]
        _emit 0x6C
        _emit 0xF5
        _emit 0x3E
        _emit 0x01
        _emit 0xDF
        _emit 0xE0                    // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x01                    // test   ah, 1
        _emit 0x8B
        _emit 0xC2                    // mov    eax, edx
        _emit 0x75
        _emit 0x04                    // jne    +4
        _emit 0xC6
        _emit 0x02
        _emit 0x00                    // mov    byte ptr [edx], 0
        _emit 0xC3                    // ret
        _emit 0xC6
        _emit 0x02
        _emit 0x01                    // mov    byte ptr [edx], 1
        _emit 0xC3                    // ret
    }
}
// @ 0x010a8b90  insertion-sort pass over 0xc-stride records
__declspec(naked) void FUN_010a8b90()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x1C
        // sub esp, 0x1c
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x24
        // mov ebp, dword ptr [esp + 0x24]
        _emit 0x8B
        _emit 0x45
        _emit 0x30
        // mov eax, dword ptr [ebp + 0x30]
        _emit 0x8D
        _emit 0x48
        _emit 0xFF
        // lea ecx, [eax - 1]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x0F
        _emit 0x8E
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jle 0x10a8ca6
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0xB9
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, 1
        _emit 0x8D
        _emit 0x5D
        _emit 0x04
        // lea ebx, [ebp + 4]
        _emit 0x57
        // push edi
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], ecx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ebx
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0x3B
        _emit 0xC8
        // cmp ecx, eax
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ecx
        _emit 0x0F
        _emit 0x8D
        _emit 0xBA
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jge 0x10a8c86
        _emit 0x8D
        _emit 0x53
        _emit 0x0C
        // lea edx, [ebx + 0xc]
        _emit 0x90
        // nop 
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x8B
        _emit 0x0B
        // mov ecx, dword ptr [ebx]
        _emit 0x8B
        _emit 0x71
        _emit 0x30
        // mov esi, dword ptr [ecx + 0x30]
        _emit 0x8B
        _emit 0x78
        _emit 0x30
        // mov edi, dword ptr [eax + 0x30]
        _emit 0x3B
        _emit 0xF7
        // cmp esi, edi
        _emit 0x0F
        _emit 0x8C
        _emit 0x89
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jl 0x10a8c6b
        _emit 0x75
        _emit 0x4D
        // jne 0x10a8c31
        _emit 0xD9
        _emit 0x41
        _emit 0x18
        // fld dword ptr [ecx + 0x18]
        _emit 0xD9
        _emit 0x41
        _emit 0x14
        // fld dword ptr [ecx + 0x14]
        _emit 0xD9
        _emit 0x41
        _emit 0x10
        // fld dword ptr [ecx + 0x10]
        _emit 0xD9
        _emit 0x40
        _emit 0x18
        // fld dword ptr [eax + 0x18]
        _emit 0xD9
        _emit 0x40
        _emit 0x14
        // fld dword ptr [eax + 0x14]
        _emit 0x8B
        _emit 0x40
        _emit 0x10
        // mov eax, dword ptr [eax + 0x10]
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], eax
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
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
        _emit 0xC5
        // fld st(5)
        _emit 0xD8
        _emit 0xCE
        // fmul st(6)
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
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
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
        _emit 0xDE
        _emit 0xD9
        // fcompp 
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
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
        _emit 0x74
        _emit 0x3A
        // je 0x10a8c6b
        _emit 0x8D
        _emit 0x7B
        _emit 0xFC
        // lea edi, [ebx - 4]
        _emit 0x8B
        _emit 0xC7
        // mov eax, edi
        _emit 0x8B
        _emit 0x08
        // mov ecx, dword ptr [eax]
        _emit 0x8B
        _emit 0x70
        _emit 0x04
        // mov esi, dword ptr [eax + 4]
        _emit 0x8B
        _emit 0x40
        _emit 0x08
        // mov eax, dword ptr [eax + 8]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], eax
        _emit 0x8D
        _emit 0x42
        _emit 0xFC
        // lea eax, [edx - 4]
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        _emit 0x8B
        _emit 0x2B
        // mov ebp, dword ptr [ebx]
        _emit 0x89
        _emit 0x2F
        // mov dword ptr [edi], ebp
        _emit 0x8B
        _emit 0x6B
        _emit 0x04
        // mov ebp, dword ptr [ebx + 4]
        _emit 0x89
        _emit 0x6F
        _emit 0x04
        // mov dword ptr [edi + 4], ebp
        _emit 0x8B
        _emit 0x5B
        _emit 0x08
        // mov ebx, dword ptr [ebx + 8]
        _emit 0x8B
        _emit 0x6C
        _emit 0x24
        _emit 0x30
        // mov ebp, dword ptr [esp + 0x30]
        _emit 0x89
        _emit 0x5F
        _emit 0x08
        // mov dword ptr [edi + 8], ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov ebx, dword ptr [esp + 0x1c]
        _emit 0x89
        _emit 0x08
        // mov dword ptr [eax], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // mov ecx, dword ptr [esp + 0x28]
        _emit 0x89
        _emit 0x70
        _emit 0x04
        // mov dword ptr [eax + 4], esi
        _emit 0x89
        _emit 0x48
        _emit 0x08
        // mov dword ptr [eax + 8], ecx
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x4D
        _emit 0x30
        // mov ecx, dword ptr [ebp + 0x30]
        _emit 0x40
        // inc eax
        _emit 0x83
        _emit 0xC2
        _emit 0x0C
        // add edx, 0xc
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], eax
        _emit 0x0F
        _emit 0x8C
        _emit 0x4E
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jl 0x10a8bd0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x45
        _emit 0x30
        // mov eax, dword ptr [ebp + 0x30]
        _emit 0x41
        // inc ecx
        _emit 0x83
        _emit 0xC3
        _emit 0x0C
        // add ebx, 0xc
        _emit 0x8D
        _emit 0x51
        _emit 0xFF
        // lea edx, [ecx - 1]
        _emit 0x8D
        _emit 0x70
        _emit 0xFF
        // lea esi, [eax - 1]
        _emit 0x3B
        _emit 0xD6
        // cmp edx, esi
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], ecx
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], ebx
        _emit 0x0F
        _emit 0x8C
        _emit 0x1D
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jl 0x10a8bc0
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x5D
        // pop ebp
        _emit 0x83
        _emit 0xC4
        _emit 0x1C
        // add esp, 0x1c
        _emit 0xC3
        // ret 
    }
}
// @ 0x010a8cf0  x87 contact/closest-point kernel
__declspec(naked) void FUN_010a8cf0()
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
        _emit 0x30
        // sub esp, 0x30
        _emit 0xD9
        _emit 0x00
        // fld dword ptr [eax]
        _emit 0x8B
        _emit 0x51
        _emit 0x20
        // mov edx, dword ptr [ecx + 0x20]
        _emit 0xD8
        _emit 0x61
        _emit 0x10
        // fsub dword ptr [ecx + 0x10]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x04
        // mov dword ptr [esp + 4], edx
        _emit 0xD9
        _emit 0x40
        _emit 0x04
        // fld dword ptr [eax + 4]
        _emit 0x8B
        _emit 0x51
        _emit 0x2C
        // mov edx, dword ptr [ecx + 0x2c]
        _emit 0xD8
        _emit 0x61
        _emit 0x14
        // fsub dword ptr [ecx + 0x14]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], edx
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
        _emit 0x61
        _emit 0x18
        // fsub dword ptr [ecx + 0x18]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // fstp dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0x40
        _emit 0x0C
        // fld dword ptr [eax + 0xc]
        _emit 0x8B
        _emit 0x45
        _emit 0x08
        // mov eax, dword ptr [ebp + 8]
        _emit 0xD8
        _emit 0x61
        _emit 0x1C
        // fsub dword ptr [ecx + 0x1c]
        _emit 0x8B
        _emit 0x50
        _emit 0x38
        // mov edx, dword ptr [eax + 0x38]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x49
        _emit 0x04
        // fmul dword ptr [ecx + 4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x49
        _emit 0x08
        // fmul dword ptr [ecx + 8]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0x09
        // fmul dword ptr [ecx]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // fmul dword ptr [esp + 0x18]
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
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fstp dword ptr [esp + 8]
        _emit 0xD9
        _emit 0x04
        _emit 0x24
        // fld dword ptr [esp]
        _emit 0xD8
        _emit 0x09
        // fmul dword ptr [ecx]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x04
        _emit 0x24
        // fld dword ptr [esp]
        _emit 0xD8
        _emit 0x49
        _emit 0x04
        // fmul dword ptr [ecx + 4]
        _emit 0xD8
        _emit 0x6C
        _emit 0x24
        _emit 0x14
        // fsubr dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x04
        _emit 0x24
        // fld dword ptr [esp]
        _emit 0xD8
        _emit 0x49
        _emit 0x08
        // fmul dword ptr [ecx + 8]
        _emit 0xD8
        _emit 0x6C
        _emit 0x24
        _emit 0x18
        // fsubr dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // fstp dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0x04
        _emit 0x24
        // fld dword ptr [esp]
        _emit 0xD8
        _emit 0x49
        _emit 0x0C
        // fmul dword ptr [ecx + 0xc]
        _emit 0xD8
        _emit 0x6C
        _emit 0x24
        _emit 0x1C
        // fsubr dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x04
        _emit 0x24
        // fld dword ptr [esp]
        _emit 0xD8
        _emit 0x0C
        _emit 0x24
        // fmul dword ptr [esp]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x4A
        _emit 0x38
        // fmul dword ptr [edx + 0x38]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x4A
        _emit 0x34
        // fmul dword ptr [edx + 0x34]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0xD8
        _emit 0x4A
        _emit 0x30
        // fmul dword ptr [edx + 0x30]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        fcomp dword ptr [kP1]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x75
        _emit 0x05
        // jne 0x10a8dc5
        _emit 0xD9
        _emit 0x41
        _emit 0x24
        // fld dword ptr [ecx + 0x24]
        _emit 0xEB
        _emit 0x03
        // jmp 0x10a8dc8
        _emit 0xD9
        _emit 0x41
        _emit 0x28
        // fld dword ptr [ecx + 0x28]
        fcom dword ptr [kP1]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x0F
        _emit 0x85
        _emit 0x8B
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // jne 0x10a9064
        _emit 0xD9
        _emit 0x42
        _emit 0x34
        // fld dword ptr [edx + 0x34]
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x2c], 0
        _emit 0xD8
        _emit 0x49
        _emit 0x08
        // fmul dword ptr [ecx + 8]
        _emit 0xC7
        _emit 0x04
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp], 0
        _emit 0xD9
        _emit 0x42
        _emit 0x38
        // fld dword ptr [edx + 0x38]
        _emit 0xD8
        _emit 0x49
        _emit 0x04
        // fmul dword ptr [ecx + 4]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0x42
        _emit 0x38
        // fld dword ptr [edx + 0x38]
        _emit 0xD8
        _emit 0x09
        // fmul dword ptr [ecx]
        _emit 0xD9
        _emit 0x42
        _emit 0x30
        // fld dword ptr [edx + 0x30]
        _emit 0xD8
        _emit 0x49
        _emit 0x08
        // fmul dword ptr [ecx + 8]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // fstp dword ptr [esp + 0x24]
        _emit 0xD9
        _emit 0x42
        _emit 0x30
        // fld dword ptr [edx + 0x30]
        _emit 0xD8
        _emit 0x49
        _emit 0x04
        // fmul dword ptr [ecx + 4]
        _emit 0xD9
        _emit 0x01
        // fld dword ptr [ecx]
        _emit 0xD8
        _emit 0x4A
        _emit 0x34
        // fmul dword ptr [edx + 0x34]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x28
        // fstp dword ptr [esp + 0x28]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // fmul dword ptr [esp + 0x28]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // fmul dword ptr [esp + 0x24]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // fmul dword ptr [esp + 0x20]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        fcom dword ptr [kP2]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x0F
        _emit 0x85
        _emit 0xA5
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0x10a8eee
        _emit 0xD9
        _emit 0xFA
        // fsqrt 
        fdivr dword ptr [kP3]
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
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // fstp dword ptr [esp + 0x24]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x28
        // fstp dword ptr [esp + 0x28]
        fmul dword ptr [kP1]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x2C
        // fstp dword ptr [esp + 0x2c]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // fmul dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
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
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0xCC
        // fmul st(4)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
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
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xD9
        _emit 0x04
        _emit 0x24
        // fld dword ptr [esp]
        _emit 0xD8
        _emit 0x0C
        _emit 0x24
        // fmul dword ptr [esp]
        _emit 0xDE
        _emit 0xD9
        // fcompp 
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x7A
        _emit 0x41
        // jp 0x10a8ef0
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0x0C
        _emit 0x24
        // fmul dword ptr [esp]
        _emit 0xDE
        _emit 0xEB
        // fsubp st(3)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0x0C
        _emit 0x24
        // fmul dword ptr [esp]
        _emit 0xD8
        _emit 0x6C
        _emit 0x24
        _emit 0x14
        // fsubr dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0xD8
        _emit 0x0C
        _emit 0x24
        // fmul dword ptr [esp]
        _emit 0xD8
        _emit 0x6C
        _emit 0x24
        _emit 0x18
        // fsubr dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // fstp dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // fld dword ptr [esp + 0x2c]
        _emit 0xD8
        _emit 0x0C
        _emit 0x24
        // fmul dword ptr [esp]
        _emit 0xC7
        _emit 0x04
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp], 0
        _emit 0xD8
        _emit 0x6C
        _emit 0x24
        _emit 0x1C
        // fsubr dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xEB
        _emit 0x02
        // jmp 0x10a8ef0
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // fadd dword ptr [esp + 4]
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xD9
        _emit 0x04
        _emit 0x24
        // fld dword ptr [esp]
        _emit 0xD8
        _emit 0x0C
        _emit 0x24
        // fmul dword ptr [esp]
        _emit 0xD8
        _emit 0x6C
        _emit 0x24
        _emit 0x08
        // fsubr dword ptr [esp + 8]
        _emit 0xD8
        _emit 0xE3
        // fsub st(3)
        _emit 0xDE
        _emit 0xD9
        // fcompp 
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
        _emit 0x7A
        _emit 0x40
        // jp 0x10a8f53
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        fld dword ptr [kP1]
        _emit 0xD9
        _emit 0x04
        _emit 0x24
        // fld dword ptr [esp]
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
        _emit 0x5E
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jnp 0x10a9089
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0x0C
        _emit 0x24
        // fmul dword ptr [esp]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0x0C
        _emit 0x24
        // fmul dword ptr [esp]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0xD8
        _emit 0x0C
        _emit 0x24
        // fmul dword ptr [esp]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // fstp dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // fld dword ptr [esp + 0x2c]
        _emit 0xD8
        _emit 0x0C
        _emit 0x24
        // fmul dword ptr [esp]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        fcomp dword ptr [kP3]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x0F
        _emit 0x8A
        _emit 0xD5
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jp 0x10a903d
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // fmul dword ptr [esp + 0x18]
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
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x04
        // fst dword ptr [esp + 4]
        fcomp dword ptr [kP2]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x01
        // test ah, 1
        _emit 0x0F
        _emit 0x85
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0x10a903d
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld dword ptr [esp + 8]
        fmul dword ptr [kP4]
        _emit 0xD8
        _emit 0x5C
        _emit 0x24
        _emit 0x04
        // fcomp dword ptr [esp + 4]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x0F
        _emit 0x8A
        _emit 0x8F
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jp 0x10a903d
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld dword ptr [esp + 8]
        _emit 0xD8
        _emit 0x74
        _emit 0x24
        _emit 0x04
        // fdiv dword ptr [esp + 4]
        _emit 0xD9
        _emit 0xFA
        // fsqrt 
        fld dword ptr [kP3]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x0C
        // fsub dword ptr [esp + 0xc]
        _emit 0xDE
        _emit 0xC9
        // fmulp st(1)
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fadd dword ptr [esp + 0xc]
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // fst dword ptr [esp + 8]
        _emit 0xDE
        _emit 0xC9
        // fmulp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // fmul dword ptr [esp + 8]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // fmul dword ptr [esp + 8]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // fstp dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // fmul dword ptr [esp + 8]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x49
        _emit 0x04
        // fmul dword ptr [ecx + 4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x49
        _emit 0x08
        // fmul dword ptr [ecx + 8]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0x09
        // fmul dword ptr [ecx]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // fst dword ptr [esp + 8]
        _emit 0xD8
        _emit 0x09
        // fmul dword ptr [ecx]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld dword ptr [esp + 8]
        _emit 0xD8
        _emit 0x49
        _emit 0x04
        // fmul dword ptr [ecx + 4]
        _emit 0xD8
        _emit 0x6C
        _emit 0x24
        _emit 0x14
        // fsubr dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld dword ptr [esp + 8]
        _emit 0xD8
        _emit 0x49
        _emit 0x08
        // fmul dword ptr [ecx + 8]
        _emit 0xD8
        _emit 0x6C
        _emit 0x24
        _emit 0x18
        // fsubr dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // fstp dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld dword ptr [esp + 8]
        _emit 0xD8
        _emit 0x49
        _emit 0x0C
        // fmul dword ptr [ecx + 0xc]
        _emit 0xD8
        _emit 0x6C
        _emit 0x24
        _emit 0x1C
        // fsubr dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0x41
        _emit 0x10
        // fadd dword ptr [ecx + 0x10]
        _emit 0xD9
        _emit 0x1E
        // fstp dword ptr [esi]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x41
        _emit 0x14
        // fadd dword ptr [ecx + 0x14]
        _emit 0xD9
        _emit 0x5E
        _emit 0x04
        // fstp dword ptr [esi + 4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x41
        _emit 0x18
        // fadd dword ptr [ecx + 0x18]
        _emit 0xD9
        _emit 0x5E
        _emit 0x08
        // fstp dword ptr [esi + 8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0x41
        _emit 0x1C
        // fadd dword ptr [ecx + 0x1c]
        _emit 0xD9
        _emit 0x5E
        _emit 0x0C
        // fstp dword ptr [esi + 0xc]
        _emit 0x8B
        _emit 0xE5
        // mov esp, ebp
        _emit 0x5D
        // pop ebp
        _emit 0xC3
        // ret 
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
        fadd dword ptr [kP3]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD8
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fcomp dword ptr [esp + 8]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xF6
        _emit 0xC4
        _emit 0x01
        // test ah, 1
        _emit 0x0F
        _emit 0x85
        _emit 0xCC
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jne 0x10a8f53
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x8B
        _emit 0x51
        _emit 0x10
        // mov edx, dword ptr [ecx + 0x10]
        _emit 0x89
        _emit 0x16
        // mov dword ptr [esi], edx
        _emit 0x8B
        _emit 0x41
        _emit 0x14
        // mov eax, dword ptr [ecx + 0x14]
        _emit 0x89
        _emit 0x46
        _emit 0x04
        // mov dword ptr [esi + 4], eax
        _emit 0x8B
        _emit 0x51
        _emit 0x18
        // mov edx, dword ptr [ecx + 0x18]
        _emit 0x89
        _emit 0x56
        _emit 0x08
        // mov dword ptr [esi + 8], edx
        _emit 0x8B
        _emit 0x41
        _emit 0x1C
        // mov eax, dword ptr [ecx + 0x1c]
        _emit 0x89
        _emit 0x46
        _emit 0x0C
        // mov dword ptr [esi + 0xc], eax
        _emit 0x8B
        _emit 0xE5
        // mov esp, ebp
        _emit 0x5D
        // pop ebp
        _emit 0xC3
        // ret 
    }
}
// @ 0x010a90b0  x87 contact kernel B
__declspec(naked) void FUN_010a90b0()
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
        _emit 0x78
        // sub esp, 0x78
        _emit 0xD9
        _emit 0x47
        _emit 0x08
        // fld dword ptr [edi + 8]
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5D
        _emit 0x0C
        // mov ebx, dword ptr [ebp + 0xc]
        _emit 0xD8
        _emit 0x4B
        _emit 0x04
        // fmul dword ptr [ebx + 4]
        _emit 0x56
        // push esi
        _emit 0xD9
        _emit 0x43
        _emit 0x08
        // fld dword ptr [ebx + 8]
        _emit 0xD8
        _emit 0x4F
        _emit 0x04
        // fmul dword ptr [edi + 4]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x43
        _emit 0x08
        // fld dword ptr [ebx + 8]
        _emit 0xD8
        _emit 0x0F
        // fmul dword ptr [edi]
        _emit 0xD9
        _emit 0x47
        _emit 0x08
        // fld dword ptr [edi + 8]
        _emit 0xD8
        _emit 0x0B
        // fmul dword ptr [ebx]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // fstp dword ptr [esp + 0x24]
        _emit 0xD9
        _emit 0x47
        _emit 0x04
        // fld dword ptr [edi + 4]
        _emit 0xD8
        _emit 0x0B
        // fmul dword ptr [ebx]
        _emit 0xD9
        _emit 0x07
        // fld dword ptr [edi]
        _emit 0xD8
        _emit 0x4B
        _emit 0x04
        // fmul dword ptr [ebx + 4]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x28
        // fstp dword ptr [esp + 0x28]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // fmul dword ptr [esp + 0x24]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // fmul dword ptr [esp + 0x28]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        fcom dword ptr [kP2]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x0F
        _emit 0x8B
        _emit 0xE2
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // jnp 0x10a93f7
        _emit 0xD9
        _emit 0xFA
        // fsqrt 
        fdivr dword ptr [kP3]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // fmul dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // fmul dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // fstp dword ptr [esp + 0x24]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // fmul dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x28
        // fstp dword ptr [esp + 0x28]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        fmul dword ptr [kP1]
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x2C
        // fst dword ptr [esp + 0x2c]
        _emit 0xD9
        _emit 0x47
        _emit 0x08
        // fld dword ptr [edi + 8]
        _emit 0xD8
        _emit 0x4B
        _emit 0x04
        // fmul dword ptr [ebx + 4]
        _emit 0xD9
        _emit 0x43
        _emit 0x08
        // fld dword ptr [ebx + 8]
        _emit 0xD8
        _emit 0x4F
        _emit 0x04
        // fmul dword ptr [edi + 4]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x43
        _emit 0x08
        // fld dword ptr [ebx + 8]
        _emit 0xD8
        _emit 0x0F
        // fmul dword ptr [edi]
        _emit 0xD9
        _emit 0x47
        _emit 0x08
        // fld dword ptr [edi + 8]
        _emit 0xD8
        _emit 0x0B
        // fmul dword ptr [ebx]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x47
        _emit 0x04
        // fld dword ptr [edi + 4]
        _emit 0xD8
        _emit 0x0B
        // fmul dword ptr [ebx]
        _emit 0xD9
        _emit 0x07
        // fld dword ptr [edi]
        _emit 0xD8
        _emit 0x4B
        _emit 0x04
        // fmul dword ptr [ebx + 4]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x58
        // fstp dword ptr [esp + 0x58]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0xD8
        _emit 0x4F
        _emit 0x04
        // fmul dword ptr [edi + 4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0x4F
        _emit 0x08
        // fmul dword ptr [edi + 8]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0x4F
        _emit 0x08
        // fmul dword ptr [edi + 8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0xD8
        _emit 0x0F
        // fmul dword ptr [edi]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x64
        // fstp dword ptr [esp + 0x64]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0x0F
        // fmul dword ptr [edi]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0x4F
        _emit 0x04
        // fmul dword ptr [edi + 4]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x68
        // fstp dword ptr [esp + 0x68]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0x4B
        _emit 0x08
        // fmul dword ptr [ebx + 8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0xD8
        _emit 0x4B
        _emit 0x04
        // fmul dword ptr [ebx + 4]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0xD8
        _emit 0x0B
        // fmul dword ptr [ebx]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0x4B
        _emit 0x08
        // fmul dword ptr [ebx + 8]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x74
        // fstp dword ptr [esp + 0x74]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0x4B
        _emit 0x04
        // fmul dword ptr [ebx + 4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0x0B
        // fmul dword ptr [ebx]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x78
        // fstp dword ptr [esp + 0x78]
        _emit 0xD9
        _emit 0x43
        _emit 0x10
        // fld dword ptr [ebx + 0x10]
        _emit 0xD8
        _emit 0x47
        _emit 0x10
        // fadd dword ptr [edi + 0x10]
        _emit 0xD9
        _emit 0x47
        _emit 0x14
        // fld dword ptr [edi + 0x14]
        _emit 0xD8
        _emit 0x43
        _emit 0x14
        // fadd dword ptr [ebx + 0x14]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x44
        // fstp dword ptr [esp + 0x44]
        _emit 0xD9
        _emit 0x47
        _emit 0x18
        // fld dword ptr [edi + 0x18]
        _emit 0xD8
        _emit 0x43
        _emit 0x18
        // fadd dword ptr [ebx + 0x18]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x48
        // fstp dword ptr [esp + 0x48]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // fld dword ptr [esp + 0x44]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // fmul dword ptr [esp + 0x24]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // fld dword ptr [esp + 0x48]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // fmul dword ptr [esp + 0x28]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // fmul dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0x75
        _emit 0x08
        // mov esi, dword ptr [ebp + 8]
        _emit 0x8B
        _emit 0x4E
        _emit 0x38
        // mov ecx, dword ptr [esi + 0x38]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        fmul dword ptr [kP5]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x40
        // fstp dword ptr [esp + 0x40]
        _emit 0xD9
        _emit 0x43
        _emit 0x18
        // fld dword ptr [ebx + 0x18]
        _emit 0xD8
        _emit 0x4B
        _emit 0x08
        // fmul dword ptr [ebx + 8]
        _emit 0xD9
        _emit 0x43
        _emit 0x14
        // fld dword ptr [ebx + 0x14]
        _emit 0xD8
        _emit 0x4B
        _emit 0x04
        // fmul dword ptr [ebx + 4]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x43
        _emit 0x10
        // fld dword ptr [ebx + 0x10]
        _emit 0xD8
        _emit 0x0B
        // fmul dword ptr [ebx]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x44
        // fstp dword ptr [esp + 0x44]
        _emit 0xD9
        _emit 0x47
        _emit 0x18
        // fld dword ptr [edi + 0x18]
        _emit 0xD8
        _emit 0x4F
        _emit 0x08
        // fmul dword ptr [edi + 8]
        _emit 0xD9
        _emit 0x47
        _emit 0x14
        // fld dword ptr [edi + 0x14]
        _emit 0xD8
        _emit 0x4F
        _emit 0x04
        // fmul dword ptr [edi + 4]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x07
        // fld dword ptr [edi]
        _emit 0xD8
        _emit 0x4F
        _emit 0x10
        // fmul dword ptr [edi + 0x10]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x48
        // fstp dword ptr [esp + 0x48]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // fmul dword ptr [esp + 0x48]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x44
        // fmul dword ptr [esp + 0x44]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xCA
        // fxch st(2)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // fmul dword ptr [esp + 0x40]
        _emit 0xDE
        _emit 0xC2
        // faddp st(2)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x30
        // fstp dword ptr [esp + 0x30]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x74
        // fld dword ptr [esp + 0x74]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // fmul dword ptr [esp + 0x48]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x64
        // fld dword ptr [esp + 0x64]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x44
        // fmul dword ptr [esp + 0x44]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // fmul dword ptr [esp + 0x40]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x68
        // fld dword ptr [esp + 0x68]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x44
        // fmul dword ptr [esp + 0x44]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x58
        // fld dword ptr [esp + 0x58]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // fmul dword ptr [esp + 0x40]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x78
        // fld dword ptr [esp + 0x78]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x48
        // fmul dword ptr [esp + 0x48]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // fld dword ptr [esp + 0x30]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // fmul dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x30
        // fstp dword ptr [esp + 0x30]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // fmul dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x34
        // fstp dword ptr [esp + 0x34]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // fmul dword ptr [esp + 0x14]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ecx
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x38
        // fstp dword ptr [esp + 0x38]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // fld dword ptr [esp + 0x30]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // fld dword ptr [esp + 0x34]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x44
        // fstp dword ptr [esp + 0x44]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // fld dword ptr [esp + 0x38]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x48
        // fstp dword ptr [esp + 0x48]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x4C
        // fstp dword ptr [esp + 0x4c]
        _emit 0xD8
        _emit 0x59
        _emit 0x20
        // fcomp dword ptr [ecx + 0x20]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x04
        // jp 0x10a92fd
        _emit 0xB2
        _emit 0x01
        // mov dl, 1
        _emit 0xEB
        _emit 0x02
        // jmp 0x10a92ff
        _emit 0x32
        _emit 0xD2
        // xor dl, dl
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // fld dword ptr [esp + 0x44]
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x12
        _emit 0x01
        // mov byte ptr [esp + 0x12], 1
        _emit 0xD8
        _emit 0x59
        _emit 0x24
        // fcomp dword ptr [ecx + 0x24]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7B
        _emit 0x05
        // jnp 0x10a9317
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x12
        _emit 0x00
        // mov byte ptr [esp + 0x12], 0
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // fld dword ptr [esp + 0x48]
        _emit 0xD8
        _emit 0x59
        _emit 0x28
        // fcomp dword ptr [ecx + 0x28]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x04
        // jp 0x10a9329
        _emit 0xB1
        _emit 0x01
        // mov cl, 1
        _emit 0xEB
        _emit 0x02
        // jmp 0x10a932b
        _emit 0x32
        _emit 0xC9
        // xor cl, cl
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x4C
        // fld dword ptr [esp + 0x4c]
        _emit 0xD8
        _emit 0x58
        _emit 0x2C
        // fcomp dword ptr [eax + 0x2c]
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x13
        _emit 0x01
        // mov byte ptr [esp + 0x13], 1
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7B
        _emit 0x05
        // jnp 0x10a9347
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x13
        _emit 0x00
        // mov byte ptr [esp + 0x13], 0
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x8A
        _emit 0x44
        _emit 0x24
        _emit 0x12
        // mov al, byte ptr [esp + 0x12]
        _emit 0xD1
        _emit 0xE1
        // shl ecx, 1
        _emit 0xF7
        _emit 0xDA
        // neg edx
        _emit 0xC1
        _emit 0xE2
        _emit 0x03
        // shl edx, 3
        _emit 0xC1
        _emit 0xE0
        _emit 0x02
        // shl eax, 2
        _emit 0x0B
        _emit 0xC8
        // or ecx, eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x13
        // mov eax, dword ptr [esp + 0x13]
        _emit 0x0B
        _emit 0xCA
        // or ecx, edx
        _emit 0x0B
        _emit 0xC8
        // or ecx, eax
        _emit 0x83
        _emit 0xE1
        _emit 0x0E
        // and ecx, 0xe
        _emit 0x80
        _emit 0xF9
        _emit 0x0E
        // cmp cl, 0xe
        _emit 0x0F
        _emit 0x85
        _emit 0x8F
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0x10a93fc
        _emit 0x8B
        _emit 0x45
        _emit 0x10
        // mov eax, dword ptr [ebp + 0x10]
        _emit 0xD9
        _emit 0x00
        // fld dword ptr [eax]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x30
        // fsub dword ptr [esp + 0x30]
        _emit 0xD9
        _emit 0x40
        _emit 0x04
        // fld dword ptr [eax + 4]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x34
        // fsub dword ptr [esp + 0x34]
        _emit 0xD9
        _emit 0x40
        _emit 0x08
        // fld dword ptr [eax + 8]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x38
        // fsub dword ptr [esp + 0x38]
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // fstp dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0x48
        _emit 0x34
        // fmul dword ptr [eax + 0x34]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0xD8
        _emit 0x48
        _emit 0x38
        // fmul dword ptr [eax + 0x38]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0x48
        _emit 0x30
        // fmul dword ptr [eax + 0x30]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // fmul dword ptr [esp + 0x24]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // fmul dword ptr [esp + 0x28]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // fmul dword ptr [esp + 0x20]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x43
        _emit 0x20
        // fld dword ptr [ebx + 0x20]
        _emit 0xD8
        _emit 0x47
        _emit 0x20
        // fadd dword ptr [edi + 0x20]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // fmul dword ptr [esp + 0x14]
        fcomp dword ptr [kP1]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x41
        // test ah, 0x41
        _emit 0x0F
        _emit 0x85
        _emit 0x97
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0x10a9483
        _emit 0xD9
        _emit 0x43
        _emit 0x24
        // fld dword ptr [ebx + 0x24]
        _emit 0xD8
        _emit 0x47
        _emit 0x24
        // fadd dword ptr [edi + 0x24]
        _emit 0xE9
        _emit 0x92
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jmp 0x10a9489
        _emit 0x8B
        _emit 0x75
        _emit 0x08
        // mov esi, dword ptr [ebp + 8]
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x8B
        _emit 0x4E
        _emit 0x38
        // mov ecx, dword ptr [esi + 0x38]
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x8B
        _emit 0x41
        _emit 0x48
        // mov eax, dword ptr [ecx + 0x48]
        _emit 0x8B
        _emit 0xD3
        // mov edx, ebx
        _emit 0x2B
        _emit 0xD0
        // sub edx, eax
        _emit 0x8B
        _emit 0x46
        _emit 0x3C
        // mov eax, dword ptr [esi + 0x3c]
        _emit 0x8B
        _emit 0x48
        _emit 0x24
        // mov ecx, dword ptr [eax + 0x24]
        _emit 0xC1
        _emit 0xFA
        _emit 0x06
        // sar edx, 6
        _emit 0xC1
        _emit 0xE2
        _emit 0x04
        // shl edx, 4
        _emit 0xB8
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 2
        _emit 0x89
        _emit 0x44
        _emit 0x0A
        _emit 0x0C
        // mov dword ptr [edx + ecx + 0xc], eax
        _emit 0x8B
        _emit 0x56
        _emit 0x38
        // mov edx, dword ptr [esi + 0x38]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0x2B
        _emit 0x4A
        _emit 0x48
        // sub ecx, dword ptr [edx + 0x48]
        _emit 0x8B
        _emit 0x56
        _emit 0x3C
        // mov edx, dword ptr [esi + 0x3c]
        _emit 0x8B
        _emit 0x52
        _emit 0x24
        // mov edx, dword ptr [edx + 0x24]
        _emit 0xC1
        _emit 0xF9
        _emit 0x06
        // sar ecx, 6
        _emit 0xC1
        _emit 0xE1
        _emit 0x04
        // shl ecx, 4
        _emit 0x89
        _emit 0x44
        _emit 0x11
        _emit 0x0C
        // mov dword ptr [ecx + edx + 0xc], eax
        _emit 0x8B
        _emit 0x43
        _emit 0x30
        // mov eax, dword ptr [ebx + 0x30]
        _emit 0x8B
        _emit 0x4F
        _emit 0x30
        // mov ecx, dword ptr [edi + 0x30]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x75
        _emit 0x14
        // mov esi, dword ptr [ebp + 0x14]
        _emit 0x3B
        _emit 0xC1
        // cmp eax, ecx
        _emit 0x8B
        _emit 0x45
        _emit 0x10
        // mov eax, dword ptr [ebp + 0x10]
        _emit 0x7E
        _emit 0x1D
        // jle 0x10a9463
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_010a8cf0
        _emit 0x8B
        _emit 0x4D
        _emit 0x08
        // mov ecx, dword ptr [ebp + 8]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        call FUN_010a8cf0
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
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
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        call FUN_010a8cf0
        _emit 0x8B
        _emit 0x55
        _emit 0x08
        // mov edx, dword ptr [ebp + 8]
        _emit 0x8B
        _emit 0x45
        _emit 0x14
        // mov eax, dword ptr [ebp + 0x14]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_010a8cf0
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
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
        _emit 0xD9
        _emit 0x43
        _emit 0x28
        // fld dword ptr [ebx + 0x28]
        _emit 0xD8
        _emit 0x47
        _emit 0x28
        // fadd dword ptr [edi + 0x28]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // fmul dword ptr [esp + 0x14]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        fmul dword ptr [kP5]
        _emit 0xD9
        _emit 0x43
        _emit 0x2C
        // fld dword ptr [ebx + 0x2c]
        _emit 0xD8
        _emit 0x47
        _emit 0x2C
        // fadd dword ptr [edi + 0x2c]
        fmul dword ptr [kP5]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // fst dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0xE1
        // fsub st(1)
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
        _emit 0xDE
        _emit 0xC9
        // fmulp st(1)
        _emit 0xD8
        _emit 0xD9
        // fcomp st(1)
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xF6
        _emit 0xC4
        _emit 0x01
        // test ah, 1
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x75
        _emit 0x22
        // jne 0x10a94e8
        _emit 0x8B
        _emit 0x45
        _emit 0x14
        // mov eax, dword ptr [ebp + 0x14]
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x30
        // mov ecx, dword ptr [esp + 0x30]
        _emit 0xD9
        _emit 0x58
        _emit 0x0C
        // fstp dword ptr [eax + 0xc]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x34
        // mov edx, dword ptr [esp + 0x34]
        _emit 0x89
        _emit 0x08
        // mov dword ptr [eax], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x38
        // mov ecx, dword ptr [esp + 0x38]
        _emit 0x89
        _emit 0x50
        _emit 0x04
        // mov dword ptr [eax + 4], edx
        _emit 0x89
        _emit 0x48
        _emit 0x08
        // mov dword ptr [eax + 8], ecx
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
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        fcomp dword ptr [kP3]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x3D
        // jp 0x10a9536
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        fmul dword ptr [kP4]
        _emit 0xD8
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fcomp dword ptr [esp + 0x1c]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x28
        // jp 0x10a9536
        fld dword ptr [kP3]
        _emit 0xD8
        _emit 0xF1
        // fdiv st(1)
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0xFA
        // fsqrt 
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xDE
        _emit 0xC9
        // fmulp st(1)
        fld dword ptr [kP3]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x14
        // fsub dword ptr [esp + 0x14]
        _emit 0xDE
        _emit 0xC9
        // fmulp st(1)
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fadd dword ptr [esp + 0x14]
        _emit 0xDE
        _emit 0xC9
        // fmulp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0x45
        _emit 0x14
        // mov eax, dword ptr [ebp + 0x14]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fadd dword ptr [esp + 0x28]
        _emit 0xD9
        _emit 0x18
        // fstp dword ptr [eax]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // fadd dword ptr [esp + 0x2c]
        _emit 0xD9
        _emit 0x58
        _emit 0x04
        // fstp dword ptr [eax + 4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // fadd dword ptr [esp + 0x30]
        _emit 0xD9
        _emit 0x58
        _emit 0x08
        // fstp dword ptr [eax + 8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD8
        _emit 0xC2
        // fadd st(2)
        _emit 0xD9
        _emit 0x58
        _emit 0x0C
        // fstp dword ptr [eax + 0xc]
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
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
// @ 0x010a9580  ray/SAT kernel calling 010a8b90 and 010a90b0
__declspec(naked) void FUN_010a9580()
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
        _emit 0x64
        // sub esp, 0x64
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xD8
        // mov ebx, eax
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7D
        _emit 0x0C
        // mov edi, dword ptr [ebp + 0xc]
        _emit 0xD9
        _emit 0x47
        _emit 0x08
        // fld dword ptr [edi + 8]
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0xD8
        _emit 0x4B
        _emit 0x04
        // fmul dword ptr [ebx + 4]
        _emit 0xD9
        _emit 0x43
        _emit 0x08
        // fld dword ptr [ebx + 8]
        _emit 0xD8
        _emit 0x4F
        _emit 0x04
        // fmul dword ptr [edi + 4]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x43
        _emit 0x08
        // fld dword ptr [ebx + 8]
        _emit 0xD8
        _emit 0x0F
        // fmul dword ptr [edi]
        _emit 0xD9
        _emit 0x47
        _emit 0x08
        // fld dword ptr [edi + 8]
        _emit 0xD8
        _emit 0x0B
        // fmul dword ptr [ebx]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x44
        // fstp dword ptr [esp + 0x44]
        _emit 0xD9
        _emit 0x03
        // fld dword ptr [ebx]
        _emit 0xD8
        _emit 0x4F
        _emit 0x04
        // fmul dword ptr [edi + 4]
        _emit 0xD9
        _emit 0x07
        // fld dword ptr [edi]
        _emit 0xD8
        _emit 0x4B
        _emit 0x04
        // fmul dword ptr [ebx + 4]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x47
        _emit 0x04
        // fld dword ptr [edi + 4]
        _emit 0xD8
        _emit 0x4E
        _emit 0x08
        // fmul dword ptr [esi + 8]
        _emit 0xD9
        _emit 0x47
        _emit 0x08
        // fld dword ptr [edi + 8]
        _emit 0xD8
        _emit 0x4E
        _emit 0x04
        // fmul dword ptr [esi + 4]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x50
        // fstp dword ptr [esp + 0x50]
        _emit 0xD9
        _emit 0x47
        _emit 0x08
        // fld dword ptr [edi + 8]
        _emit 0xD8
        _emit 0x0E
        // fmul dword ptr [esi]
        _emit 0xD9
        _emit 0x07
        // fld dword ptr [edi]
        _emit 0xD8
        _emit 0x4E
        _emit 0x08
        // fmul dword ptr [esi + 8]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x54
        // fstp dword ptr [esp + 0x54]
        _emit 0xD9
        _emit 0x46
        _emit 0x04
        // fld dword ptr [esi + 4]
        _emit 0xD8
        _emit 0x0F
        // fmul dword ptr [edi]
        _emit 0xD9
        _emit 0x06
        // fld dword ptr [esi]
        _emit 0xD8
        _emit 0x4F
        _emit 0x04
        // fmul dword ptr [edi + 4]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x43
        _emit 0x08
        // fld dword ptr [ebx + 8]
        _emit 0xD8
        _emit 0x4E
        _emit 0x04
        // fmul dword ptr [esi + 4]
        _emit 0xD9
        _emit 0x46
        _emit 0x08
        // fld dword ptr [esi + 8]
        _emit 0xD8
        _emit 0x4B
        _emit 0x04
        // fmul dword ptr [ebx + 4]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x60
        // fstp dword ptr [esp + 0x60]
        _emit 0xD9
        _emit 0x03
        // fld dword ptr [ebx]
        _emit 0xD8
        _emit 0x4E
        _emit 0x08
        // fmul dword ptr [esi + 8]
        _emit 0xD9
        _emit 0x43
        _emit 0x08
        // fld dword ptr [ebx + 8]
        _emit 0xD8
        _emit 0x0E
        // fmul dword ptr [esi]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x64
        // fstp dword ptr [esp + 0x64]
        _emit 0xD9
        _emit 0x06
        // fld dword ptr [esi]
        _emit 0xD8
        _emit 0x4B
        _emit 0x04
        // fmul dword ptr [ebx + 4]
        _emit 0xD9
        _emit 0x03
        // fld dword ptr [ebx]
        _emit 0xD8
        _emit 0x4E
        _emit 0x04
        // fmul dword ptr [esi + 4]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x68
        // fstp dword ptr [esp + 0x68]
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0xD8
        _emit 0x0E
        // fmul dword ptr [esi]
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0xD8
        _emit 0x4E
        _emit 0x08
        // fmul dword ptr [esi + 8]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // fld dword ptr [esp + 0x44]
        _emit 0xD8
        _emit 0x4E
        _emit 0x04
        // fmul dword ptr [esi + 4]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // fst dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        fcomp dword ptr [kP2]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x0F
        _emit 0x8B
        _emit 0x8C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jnp 0x10a97d4
        _emit 0xD9
        _emit 0x46
        _emit 0x18
        // fld dword ptr [esi + 0x18]
        _emit 0xD8
        _emit 0x4E
        _emit 0x08
        // fmul dword ptr [esi + 8]
        _emit 0xD9
        _emit 0x46
        _emit 0x14
        // fld dword ptr [esi + 0x14]
        _emit 0xD8
        _emit 0x4E
        _emit 0x04
        // fmul dword ptr [esi + 4]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x06
        // fld dword ptr [esi]
        _emit 0xD8
        _emit 0x4E
        _emit 0x10
        // fmul dword ptr [esi + 0x10]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x43
        _emit 0x18
        // fld dword ptr [ebx + 0x18]
        _emit 0xD8
        _emit 0x4B
        _emit 0x08
        // fmul dword ptr [ebx + 8]
        _emit 0xD9
        _emit 0x43
        _emit 0x14
        // fld dword ptr [ebx + 0x14]
        _emit 0xD8
        _emit 0x4B
        _emit 0x04
        // fmul dword ptr [ebx + 4]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x43
        _emit 0x10
        // fld dword ptr [ebx + 0x10]
        _emit 0xD8
        _emit 0x0B
        // fmul dword ptr [ebx]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x47
        _emit 0x18
        // fld dword ptr [edi + 0x18]
        _emit 0xD8
        _emit 0x4F
        _emit 0x08
        // fmul dword ptr [edi + 8]
        _emit 0xD9
        _emit 0x47
        _emit 0x14
        // fld dword ptr [edi + 0x14]
        _emit 0xD8
        _emit 0x4F
        _emit 0x04
        // fmul dword ptr [edi + 4]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x07
        // fld dword ptr [edi]
        _emit 0xD8
        _emit 0x4F
        _emit 0x10
        // fmul dword ptr [edi + 0x10]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x60
        // fld dword ptr [esp + 0x60]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x50
        // fld dword ptr [esp + 0x50]
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xCE
        // fxch st(6)
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
        _emit 0xDE
        _emit 0xC6
        // faddp st(6)
        _emit 0xD9
        _emit 0xCD
        // fxch st(5)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x64
        // fld dword ptr [esp + 0x64]
        _emit 0xD8
        _emit 0xCD
        // fmul st(5)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x54
        // fld dword ptr [esp + 0x54]
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // fld dword ptr [esp + 0x44]
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // fstp dword ptr [esp + 0x24]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x68
        // fld dword ptr [esp + 0x68]
        _emit 0xD8
        _emit 0xCD
        // fmul st(5)
        _emit 0xD9
        _emit 0xCB
        // fxch st(3)
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xDE
        _emit 0xC3
        // faddp st(3)
        _emit 0xD9
        _emit 0xCB
        // fxch st(3)
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xDE
        _emit 0xC2
        // faddp st(2)
        _emit 0xDD
        _emit 0xDB
        // fstp st(3)
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        fld dword ptr [kP3]
        _emit 0xD8
        _emit 0x74
        _emit 0x24
        _emit 0x1C
        // fdiv dword ptr [esp + 0x1c]
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
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // fstp dword ptr [esp + 0x24]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x28
        // fstp dword ptr [esp + 0x28]
        fmul dword ptr [kP1]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0x8B
        _emit 0x4D
        _emit 0x08
        // mov ecx, dword ptr [ebp + 8]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x34
        // fstp dword ptr [esp + 0x34]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0x8B
        _emit 0x51
        _emit 0x38
        // mov edx, dword ptr [ecx + 0x38]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0x83
        _emit 0xC2
        _emit 0x20
        // add edx, 0x20
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x38
        // fstp dword ptr [esp + 0x38]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x1A
        _emit 0x01
        // mov byte ptr [esp + 0x1a], 1
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x3C
        // fstp dword ptr [esp + 0x3c]
        _emit 0xD8
        _emit 0x1A
        // fcomp dword ptr [edx]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7B
        _emit 0x05
        // jnp 0x10a973d
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x1A
        _emit 0x00
        // mov byte ptr [esp + 0x1a], 0
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // fld dword ptr [esp + 0x34]
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x19
        _emit 0x01
        // mov byte ptr [esp + 0x19], 1
        _emit 0xD8
        _emit 0x5A
        _emit 0x04
        // fcomp dword ptr [edx + 4]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7B
        _emit 0x05
        // jnp 0x10a9755
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x19
        _emit 0x00
        // mov byte ptr [esp + 0x19], 0
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // fld dword ptr [esp + 0x38]
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x01
        // mov byte ptr [esp + 0x18], 1
        _emit 0xD8
        _emit 0x5A
        _emit 0x08
        // fcomp dword ptr [edx + 8]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7B
        _emit 0x05
        // jnp 0x10a976d
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x00
        // mov byte ptr [esp + 0x18], 0
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        // fld dword ptr [esp + 0x3c]
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x1B
        _emit 0x01
        // mov byte ptr [esp + 0x1b], 1
        _emit 0xD8
        _emit 0x5A
        _emit 0x0C
        // fcomp dword ptr [edx + 0xc]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7B
        _emit 0x05
        // jnp 0x10a9785
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x1B
        _emit 0x00
        // mov byte ptr [esp + 0x1b], 0
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x8A
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov al, byte ptr [esp + 0x18]
        _emit 0xD1
        _emit 0xE0
        // shl eax, 1
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x8A
        _emit 0x44
        _emit 0x24
        _emit 0x19
        // mov al, byte ptr [esp + 0x19]
        _emit 0xC1
        _emit 0xE0
        _emit 0x02
        // shl eax, 2
        _emit 0x0B
        _emit 0xD0
        // or edx, eax
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x8A
        _emit 0x44
        _emit 0x24
        _emit 0x1A
        // mov al, byte ptr [esp + 0x1a]
        _emit 0xF7
        _emit 0xD8
        // neg eax
        _emit 0xC1
        _emit 0xE0
        _emit 0x03
        // shl eax, 3
        _emit 0x0B
        _emit 0xD0
        // or edx, eax
        _emit 0x0B
        _emit 0x54
        _emit 0x24
        _emit 0x1B
        // or edx, dword ptr [esp + 0x1b]
        _emit 0x83
        _emit 0xE2
        _emit 0x0E
        // and edx, 0xe
        _emit 0x80
        _emit 0xFA
        _emit 0x0E
        // cmp dl, 0xe
        _emit 0x75
        _emit 0x28
        // jne 0x10a97db
        _emit 0x8B
        _emit 0x45
        _emit 0x18
        // mov eax, dword ptr [ebp + 0x18]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0x58
        _emit 0x0C
        // fstp dword ptr [eax + 0xc]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // mov edx, dword ptr [esp + 0x24]
        _emit 0x89
        _emit 0x08
        // mov dword ptr [eax], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // mov ecx, dword ptr [esp + 0x28]
        _emit 0x89
        _emit 0x50
        _emit 0x04
        // mov dword ptr [eax + 4], edx
        _emit 0x89
        _emit 0x48
        _emit 0x08
        // mov dword ptr [eax + 8], ecx
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
        _emit 0x8B
        _emit 0x4D
        _emit 0x08
        // mov ecx, dword ptr [ebp + 8]
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x8B
        _emit 0x45
        _emit 0x10
        // mov eax, dword ptr [ebp + 0x10]
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x1D
        // je 0x10a9801
        _emit 0x51
        // push ecx
        call FUN_010a8b90
        _emit 0x8B
        _emit 0x45
        _emit 0x08
        // mov eax, dword ptr [ebp + 8]
        _emit 0x8B
        _emit 0x70
        _emit 0x04
        // mov esi, dword ptr [eax + 4]
        _emit 0x8B
        _emit 0x58
        _emit 0x10
        // mov ebx, dword ptr [eax + 0x10]
        _emit 0x8B
        _emit 0x40
        _emit 0x1C
        // mov eax, dword ptr [eax + 0x1c]
        _emit 0x8B
        _emit 0x4D
        _emit 0x08
        // mov ecx, dword ptr [ebp + 8]
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x89
        _emit 0x45
        _emit 0x0C
        // mov dword ptr [ebp + 0xc], eax
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x8B
        _emit 0x51
        _emit 0x38
        // mov edx, dword ptr [ecx + 0x38]
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0x2B
        _emit 0x42
        _emit 0x48
        // sub eax, dword ptr [edx + 0x48]
        _emit 0x8B
        _emit 0x51
        _emit 0x3C
        // mov edx, dword ptr [ecx + 0x3c]
        _emit 0x8B
        _emit 0x52
        _emit 0x24
        // mov edx, dword ptr [edx + 0x24]
        _emit 0xC1
        _emit 0xF8
        _emit 0x06
        // sar eax, 6
        _emit 0xC1
        _emit 0xE0
        _emit 0x04
        // shl eax, 4
        _emit 0xC7
        _emit 0x44
        _emit 0x10
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [eax + edx + 0xc], 1
        _emit 0x8B
        _emit 0x41
        _emit 0x38
        // mov eax, dword ptr [ecx + 0x38]
        _emit 0x8B
        _emit 0xD3
        // mov edx, ebx
        _emit 0x2B
        _emit 0x50
        _emit 0x48
        // sub edx, dword ptr [eax + 0x48]
        _emit 0x8B
        _emit 0x41
        _emit 0x3C
        // mov eax, dword ptr [ecx + 0x3c]
        _emit 0x8B
        _emit 0x40
        _emit 0x24
        // mov eax, dword ptr [eax + 0x24]
        _emit 0xC1
        _emit 0xFA
        _emit 0x06
        // sar edx, 6
        _emit 0xC1
        _emit 0xE2
        _emit 0x04
        // shl edx, 4
        _emit 0xC7
        _emit 0x44
        _emit 0x02
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edx + eax + 0xc], 1
        _emit 0x8B
        _emit 0x51
        _emit 0x38
        // mov edx, dword ptr [ecx + 0x38]
        _emit 0x2B
        _emit 0x7A
        _emit 0x48
        // sub edi, dword ptr [edx + 0x48]
        _emit 0x8B
        _emit 0x41
        _emit 0x3C
        // mov eax, dword ptr [ecx + 0x3c]
        _emit 0x8B
        _emit 0x50
        _emit 0x24
        // mov edx, dword ptr [eax + 0x24]
        _emit 0xC1
        _emit 0xFF
        _emit 0x06
        // sar edi, 6
        _emit 0xC1
        _emit 0xE7
        _emit 0x04
        // shl edi, 4
        _emit 0xC7
        _emit 0x44
        _emit 0x17
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + edx + 0xc], 1
        _emit 0x8B
        _emit 0x41
        _emit 0x30
        // mov eax, dword ptr [ecx + 0x30]
        _emit 0x8B
        _emit 0x55
        _emit 0x18
        // mov edx, dword ptr [ebp + 0x18]
        _emit 0x52
        // push edx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], eax
        _emit 0x8B
        _emit 0x45
        _emit 0x14
        // mov eax, dword ptr [ebp + 0x14]
        _emit 0x50
        // push eax
        _emit 0x56
        // push esi
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xFB
        // mov edi, ebx
        call FUN_010a90b0
        _emit 0x8B
        _emit 0x45
        _emit 0x08
        // mov eax, dword ptr [ebp + 8]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov ecx, dword ptr [esp + 0x2c]
        _emit 0x8B
        _emit 0x50
        _emit 0x30
        // mov edx, dword ptr [eax + 0x30]
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        _emit 0x3B
        _emit 0xCA
        // cmp ecx, edx
        _emit 0x75
        _emit 0x15
        // jne 0x10a9891
        _emit 0x8B
        _emit 0x4D
        _emit 0x18
        // mov ecx, dword ptr [ebp + 0x18]
        _emit 0x8B
        _emit 0x7D
        _emit 0x0C
        // mov edi, dword ptr [ebp + 0xc]
        _emit 0x51
        // push ecx
        _emit 0x51
        // push ecx
        _emit 0x56
        // push esi
        _emit 0x50
        // push eax
        call FUN_010a90b0
        _emit 0x8B
        _emit 0x45
        _emit 0x08
        // mov eax, dword ptr [ebp + 8]
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // mov edx, dword ptr [esp + 0x1c]
        _emit 0x3B
        _emit 0x50
        _emit 0x30
        // cmp edx, dword ptr [eax + 0x30]
        _emit 0x0F
        _emit 0x85
        _emit 0x2F
        _emit 0xFF
        _emit 0xFF
        _emit 0xFF
        // jne 0x10a97cd
        _emit 0x8B
        _emit 0x4D
        _emit 0x18
        // mov ecx, dword ptr [ebp + 0x18]
        _emit 0x8B
        _emit 0x7D
        _emit 0x0C
        // mov edi, dword ptr [ebp + 0xc]
        _emit 0x51
        // push ecx
        _emit 0x51
        // push ecx
        _emit 0x53
        // push ebx
        _emit 0x50
        // push eax
        call FUN_010a90b0
        _emit 0x83
        _emit 0xC4
        _emit 0x10
        // add esp, 0x10
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
