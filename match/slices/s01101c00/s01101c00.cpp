// Slice s01101c00: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_011014d0();

// @ 0x01101c00  (648 bytes)
__declspec(naked) void FUN_01101c00()
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
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // sub esp, 0x90
        _emit 0x8B
        _emit 0x45
        _emit 0x18
        // mov eax, dword ptr [ebp + 0x18]
        _emit 0x8B
        _emit 0x55
        _emit 0x08
        // mov edx, dword ptr [ebp + 8]
        _emit 0x89
        _emit 0x01
        // mov dword ptr [ecx], eax
        _emit 0x8B
        _emit 0x45
        _emit 0x10
        // mov eax, dword ptr [ebp + 0x10]
        _emit 0x89
        _emit 0x51
        _emit 0x30
        // mov dword ptr [ecx + 0x30], edx
        _emit 0xD9
        _emit 0x00
        // fld dword ptr [eax]
        _emit 0xD9
        _emit 0x40
        _emit 0x04
        // fld dword ptr [eax + 4]
        _emit 0x8B
        _emit 0x40
        _emit 0x08
        // mov eax, dword ptr [eax + 8]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov dword ptr [esp + 8], eax
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0x8B
        _emit 0x45
        _emit 0x0C
        // mov eax, dword ptr [ebp + 0xc]
        _emit 0xD8
        _emit 0x08
        // fmul dword ptr [eax]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0x48
        _emit 0x04
        // fmul dword ptr [eax + 4]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // fstp dword ptr [esp + 0x24]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x48
        _emit 0x08
        // fmul dword ptr [eax + 8]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x28
        // fstp dword ptr [esp + 0x28]
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD8
        _emit 0x48
        _emit 0x10
        // fmul dword ptr [eax + 0x10]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x30
        // fstp dword ptr [esp + 0x30]
        _emit 0xD9
        _emit 0xC0
        // fld st(0)
        _emit 0xD8
        _emit 0x48
        _emit 0x14
        // fmul dword ptr [eax + 0x14]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x34
        // fstp dword ptr [esp + 0x34]
        _emit 0xD8
        _emit 0x48
        _emit 0x18
        // fmul dword ptr [eax + 0x18]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld dword ptr [esp + 8]
        _emit 0xD8
        _emit 0x48
        _emit 0x20
        // fmul dword ptr [eax + 0x20]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld dword ptr [esp + 8]
        _emit 0xD8
        _emit 0x48
        _emit 0x24
        // fmul dword ptr [eax + 0x24]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x44
        // fstp dword ptr [esp + 0x44]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld dword ptr [esp + 8]
        _emit 0xD8
        _emit 0x48
        _emit 0x28
        // fmul dword ptr [eax + 0x28]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x48
        // fstp dword ptr [esp + 0x48]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0xE1
        // fabs 
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
        _emit 0xD9
        _emit 0xE1
        // fabs 
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
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x28
        // fstp dword ptr [esp + 0x28]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // fld dword ptr [esp + 0x30]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x30
        // fstp dword ptr [esp + 0x30]
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
        _emit 0x34
        // fstp dword ptr [esp + 0x34]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x38
        // fstp dword ptr [esp + 0x38]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // fld dword ptr [esp + 0x44]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // fld dword ptr [esp + 0x48]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x48
        // fstp dword ptr [esp + 0x48]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // fld dword ptr [esp + 0x30]
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fadd dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // fld dword ptr [esp + 0x34]
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fadd dword ptr [esp + 0x24]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // fld dword ptr [esp + 0x38]
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fadd dword ptr [esp + 0x28]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // fstp dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0xC2
        // fadd st(2)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // fstp dword ptr [esp + 0x10]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0xC1
        // fadd st(1)
        _emit 0xDD
        _emit 0xDA
        // fstp st(2)
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // fadd dword ptr [esp + 0x48]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xD8
        _emit 0x45
        _emit 0x14
        // fadd dword ptr [ebp + 0x14]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // fstp dword ptr [esp + 0x10]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x45
        _emit 0x14
        // fadd dword ptr [ebp + 0x14]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x45
        _emit 0x14
        // fadd dword ptr [ebp + 0x14]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xD9
        _emit 0xE0
        // fchs 
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0xE0
        // fchs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x34
        // fstp dword ptr [esp + 0x34]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD9
        _emit 0xE0
        // fchs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x38
        // fstp dword ptr [esp + 0x38]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xD8
        _emit 0x40
        _emit 0x30
        // fadd dword ptr [eax + 0x30]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // fstp dword ptr [esp + 0x10]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xD8
        _emit 0x40
        _emit 0x34
        // fadd dword ptr [eax + 0x34]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x40
        _emit 0x38
        // fadd dword ptr [eax + 0x38]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // fstp dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x40
        _emit 0x30
        // fadd dword ptr [eax + 0x30]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // fld dword ptr [esp + 0x34]
        _emit 0xD8
        _emit 0x40
        _emit 0x34
        // fadd dword ptr [eax + 0x34]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x34
        // fstp dword ptr [esp + 0x34]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // fld dword ptr [esp + 0x38]
        _emit 0xD8
        _emit 0x40
        _emit 0x38
        // fadd dword ptr [eax + 0x38]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x38
        // fstp dword ptr [esp + 0x38]
        _emit 0xD8
        _emit 0x62
        _emit 0x10
        // fsub dword ptr [edx + 0x10]
        _emit 0xD8
        _emit 0x4A
        _emit 0x1C
        // fmul dword ptr [edx + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fstp dword ptr [esp + 8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld dword ptr [esp + 8]
        _emit 0xDB
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // fistp dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // mov edx, dword ptr [esp + 0xc]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x41
        _emit 0x30
        // mov eax, dword ptr [ecx + 0x30]
        _emit 0x4A
        // dec edx
        _emit 0x89
        _emit 0x51
        _emit 0x20
        // mov dword ptr [ecx + 0x20], edx
        _emit 0xD8
        _emit 0x60
        _emit 0x10
        // fsub dword ptr [eax + 0x10]
        _emit 0xD8
        _emit 0x48
        _emit 0x1C
        // fmul dword ptr [eax + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // fstp dword ptr [esp + 0xc]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        _emit 0xDB
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fistp dword ptr [esp + 8]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // fld dword ptr [esp + 0x34]
        _emit 0x40
        // inc eax
        _emit 0x89
        _emit 0x41
        _emit 0x10
        // mov dword ptr [ecx + 0x10], eax
        _emit 0x8B
        _emit 0x41
        _emit 0x30
        // mov eax, dword ptr [ecx + 0x30]
        _emit 0xD8
        _emit 0x60
        _emit 0x14
        // fsub dword ptr [eax + 0x14]
        _emit 0xD8
        _emit 0x48
        _emit 0x1C
        // fmul dword ptr [eax + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // fstp dword ptr [esp + 0xc]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        _emit 0xDB
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fistp dword ptr [esp + 8]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // mov edx, dword ptr [esp + 8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x41
        _emit 0x30
        // mov eax, dword ptr [ecx + 0x30]
        _emit 0x4A
        // dec edx
        _emit 0x89
        _emit 0x51
        _emit 0x24
        // mov dword ptr [ecx + 0x24], edx
        _emit 0xD8
        _emit 0x60
        _emit 0x14
        // fsub dword ptr [eax + 0x14]
        _emit 0xD8
        _emit 0x48
        _emit 0x1C
        // fmul dword ptr [eax + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // fstp dword ptr [esp + 0xc]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        _emit 0xDB
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fistp dword ptr [esp + 8]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // fld dword ptr [esp + 0x38]
        _emit 0x40
        // inc eax
        _emit 0x89
        _emit 0x41
        _emit 0x14
        // mov dword ptr [ecx + 0x14], eax
        _emit 0x8B
        _emit 0x41
        _emit 0x30
        // mov eax, dword ptr [ecx + 0x30]
        _emit 0xD8
        _emit 0x60
        _emit 0x18
        // fsub dword ptr [eax + 0x18]
        _emit 0xD8
        _emit 0x48
        _emit 0x1C
        // fmul dword ptr [eax + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // fstp dword ptr [esp + 0xc]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        _emit 0xDB
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fistp dword ptr [esp + 8]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // mov edx, dword ptr [esp + 8]
        _emit 0x4A
        // dec edx
        _emit 0x89
        _emit 0x51
        _emit 0x28
        // mov dword ptr [ecx + 0x28], edx
        _emit 0x8B
        _emit 0x41
        _emit 0x30
        // mov eax, dword ptr [ecx + 0x30]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x60
        _emit 0x18
        // fsub dword ptr [eax + 0x18]
        _emit 0xD8
        _emit 0x48
        _emit 0x1C
        // fmul dword ptr [eax + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // fstp dword ptr [esp + 0xc]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        _emit 0xDB
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fistp dword ptr [esp + 8]
        _emit 0x0F
        _emit 0xBF
        _emit 0x51
        _emit 0x22
        // movsx edx, word ptr [ecx + 0x22]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x60
        // mov dword ptr [esp + 0x60], edx
        _emit 0x0F
        _emit 0xBF
        _emit 0x51
        _emit 0x12
        // movsx edx, word ptr [ecx + 0x12]
        _emit 0x40
        // inc eax
        _emit 0x42
        // inc edx
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x50
        // mov dword ptr [esp + 0x50], edx
        _emit 0x0F
        _emit 0xBF
        _emit 0x51
        _emit 0x26
        // movsx edx, word ptr [ecx + 0x26]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x64
        // mov dword ptr [esp + 0x64], edx
        _emit 0x0F
        _emit 0xBF
        _emit 0x51
        _emit 0x16
        // movsx edx, word ptr [ecx + 0x16]
        _emit 0x89
        _emit 0x41
        _emit 0x18
        // mov dword ptr [ecx + 0x18], eax
        _emit 0xC1
        _emit 0xF8
        _emit 0x10
        // sar eax, 0x10
        _emit 0x42
        // inc edx
        _emit 0x40
        // inc eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x58
        // mov dword ptr [esp + 0x58], eax
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x54
        // mov dword ptr [esp + 0x54], edx
        _emit 0x0F
        _emit 0xBF
        _emit 0x51
        _emit 0x2A
        // movsx edx, word ptr [ecx + 0x2a]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x70
        // mov dword ptr [esp + 0x70], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x74
        // mov dword ptr [esp + 0x74], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x78
        // mov dword ptr [esp + 0x78], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x7C
        // mov dword ptr [esp + 0x7c], eax
        _emit 0x89
        _emit 0x84
        _emit 0x24
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x80], eax
        _emit 0x89
        _emit 0x84
        _emit 0x24
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x84], eax
        _emit 0x8B
        _emit 0x41
        _emit 0x30
        // mov eax, dword ptr [ecx + 0x30]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x68
        // mov dword ptr [esp + 0x68], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x20
        // mov edx, dword ptr [eax + 0x20]
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x54
        // lea eax, [esp + 0x54]
        _emit 0x50
        // push eax
        call FUN_011014d0
        _emit 0x8B
        _emit 0xE5
        // mov esp, ebp
        _emit 0x5D
        // pop ebp
        _emit 0xC2
        _emit 0x14
        _emit 0x00
        // ret 0x14
    }
}

// @ 0x01101e90  (310 bytes)
__declspec(naked) void FUN_01101e90()
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
        _emit 0x50
        // sub esp, 0x50
        _emit 0x8B
        _emit 0x45
        _emit 0x10
        // mov eax, dword ptr [ebp + 0x10]
        _emit 0x8B
        _emit 0x55
        _emit 0x08
        // mov edx, dword ptr [ebp + 8]
        _emit 0x89
        _emit 0x01
        // mov dword ptr [ecx], eax
        _emit 0x8B
        _emit 0x45
        _emit 0x0C
        // mov eax, dword ptr [ebp + 0xc]
        _emit 0x89
        _emit 0x51
        _emit 0x30
        // mov dword ptr [ecx + 0x30], edx
        _emit 0xD9
        _emit 0x00
        // fld dword ptr [eax]
        _emit 0xD8
        _emit 0x62
        _emit 0x10
        // fsub dword ptr [edx + 0x10]
        _emit 0xD8
        _emit 0x4A
        _emit 0x1C
        // fmul dword ptr [edx + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fstp dword ptr [esp + 8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // fld dword ptr [esp + 8]
        _emit 0xDB
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // fistp dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // mov edx, dword ptr [esp + 0xc]
        _emit 0x4A
        // dec edx
        _emit 0x89
        _emit 0x51
        _emit 0x20
        // mov dword ptr [ecx + 0x20], edx
        _emit 0xD9
        _emit 0x40
        _emit 0x10
        // fld dword ptr [eax + 0x10]
        _emit 0x8B
        _emit 0x51
        _emit 0x30
        // mov edx, dword ptr [ecx + 0x30]
        _emit 0xD8
        _emit 0x62
        _emit 0x10
        // fsub dword ptr [edx + 0x10]
        _emit 0xD8
        _emit 0x4A
        _emit 0x1C
        // fmul dword ptr [edx + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // fstp dword ptr [esp + 0xc]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        _emit 0xDB
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fistp dword ptr [esp + 8]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // mov edx, dword ptr [esp + 8]
        _emit 0x42
        // inc edx
        _emit 0x89
        _emit 0x51
        _emit 0x10
        // mov dword ptr [ecx + 0x10], edx
        _emit 0xD9
        _emit 0x40
        _emit 0x04
        // fld dword ptr [eax + 4]
        _emit 0x8B
        _emit 0x51
        _emit 0x30
        // mov edx, dword ptr [ecx + 0x30]
        _emit 0xD8
        _emit 0x62
        _emit 0x14
        // fsub dword ptr [edx + 0x14]
        _emit 0xD8
        _emit 0x4A
        _emit 0x1C
        // fmul dword ptr [edx + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // fstp dword ptr [esp + 0xc]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        _emit 0xDB
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fistp dword ptr [esp + 8]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // mov edx, dword ptr [esp + 8]
        _emit 0x4A
        // dec edx
        _emit 0x89
        _emit 0x51
        _emit 0x24
        // mov dword ptr [ecx + 0x24], edx
        _emit 0xD9
        _emit 0x40
        _emit 0x14
        // fld dword ptr [eax + 0x14]
        _emit 0x8B
        _emit 0x51
        _emit 0x30
        // mov edx, dword ptr [ecx + 0x30]
        _emit 0xD8
        _emit 0x62
        _emit 0x14
        // fsub dword ptr [edx + 0x14]
        _emit 0xD8
        _emit 0x4A
        _emit 0x1C
        // fmul dword ptr [edx + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // fstp dword ptr [esp + 0xc]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        _emit 0xDB
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fistp dword ptr [esp + 8]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // mov edx, dword ptr [esp + 8]
        _emit 0x42
        // inc edx
        _emit 0x89
        _emit 0x51
        _emit 0x14
        // mov dword ptr [ecx + 0x14], edx
        _emit 0xD9
        _emit 0x40
        _emit 0x08
        // fld dword ptr [eax + 8]
        _emit 0x8B
        _emit 0x51
        _emit 0x30
        // mov edx, dword ptr [ecx + 0x30]
        _emit 0xD8
        _emit 0x62
        _emit 0x18
        // fsub dword ptr [edx + 0x18]
        _emit 0xD8
        _emit 0x4A
        _emit 0x1C
        // fmul dword ptr [edx + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // fstp dword ptr [esp + 0xc]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        _emit 0xDB
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fistp dword ptr [esp + 8]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // mov edx, dword ptr [esp + 8]
        _emit 0x4A
        // dec edx
        _emit 0x89
        _emit 0x51
        _emit 0x28
        // mov dword ptr [ecx + 0x28], edx
        _emit 0xD9
        _emit 0x40
        _emit 0x18
        // fld dword ptr [eax + 0x18]
        _emit 0x8B
        _emit 0x51
        _emit 0x30
        // mov edx, dword ptr [ecx + 0x30]
        _emit 0xD8
        _emit 0x62
        _emit 0x18
        // fsub dword ptr [edx + 0x18]
        _emit 0xD8
        _emit 0x4A
        _emit 0x1C
        // fmul dword ptr [edx + 0x1c]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x0C
        // fstp dword ptr [esp + 0xc]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // fld dword ptr [esp + 0xc]
        _emit 0xDB
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // fistp dword ptr [esp + 8]
        _emit 0x0F
        _emit 0xBF
        _emit 0x51
        _emit 0x22
        // movsx edx, word ptr [ecx + 0x22]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], edx
        _emit 0x0F
        _emit 0xBF
        _emit 0x51
        _emit 0x12
        // movsx edx, word ptr [ecx + 0x12]
        _emit 0x40
        // inc eax
        _emit 0x42
        // inc edx
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], edx
        _emit 0x0F
        _emit 0xBF
        _emit 0x51
        _emit 0x26
        // movsx edx, word ptr [ecx + 0x26]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], edx
        _emit 0x0F
        _emit 0xBF
        _emit 0x51
        _emit 0x16
        // movsx edx, word ptr [ecx + 0x16]
        _emit 0x89
        _emit 0x41
        _emit 0x18
        // mov dword ptr [ecx + 0x18], eax
        _emit 0x42
        // inc edx
        _emit 0xC1
        _emit 0xF8
        _emit 0x10
        // sar eax, 0x10
        _emit 0x40
        // inc eax
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], edx
        _emit 0x0F
        _emit 0xBF
        _emit 0x51
        _emit 0x2A
        // movsx edx, word ptr [ecx + 0x2a]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], eax
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], edx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // mov dword ptr [esp + 0x30], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // mov dword ptr [esp + 0x34], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // mov dword ptr [esp + 0x38], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        // mov dword ptr [esp + 0x3c], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // mov dword ptr [esp + 0x40], eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // mov dword ptr [esp + 0x44], eax
        _emit 0x8B
        _emit 0x41
        _emit 0x30
        // mov eax, dword ptr [ecx + 0x30]
        _emit 0x8B
        _emit 0x50
        _emit 0x20
        // mov edx, dword ptr [eax + 0x20]
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // lea eax, [esp + 0x14]
        _emit 0x50
        // push eax
        call FUN_011014d0
        _emit 0x8B
        _emit 0xE5
        // mov esp, ebp
        _emit 0x5D
        // pop ebp
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
    }
}

// @ 0x01101fd0  (55 bytes)
__declspec(naked) void FUN_01101fd0()
{
    __asm {
        _emit 0x8B
        _emit 0xC1
        // mov eax, ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x04
        // mov ecx, dword ptr [esp + 4]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x89
        _emit 0x10
        // mov dword ptr [eax], edx
        _emit 0x8B
        _emit 0x51
        _emit 0x04
        // mov edx, dword ptr [ecx + 4]
        _emit 0x89
        _emit 0x50
        _emit 0x04
        // mov dword ptr [eax + 4], edx
        _emit 0x8B
        _emit 0x51
        _emit 0x08
        // mov edx, dword ptr [ecx + 8]
        _emit 0x89
        _emit 0x50
        _emit 0x08
        // mov dword ptr [eax + 8], edx
        _emit 0x8B
        _emit 0x51
        _emit 0x0C
        // mov edx, dword ptr [ecx + 0xc]
        _emit 0x89
        _emit 0x50
        _emit 0x0C
        // mov dword ptr [eax + 0xc], edx
        _emit 0x8B
        _emit 0x51
        _emit 0x10
        // mov edx, dword ptr [ecx + 0x10]
        _emit 0x89
        _emit 0x50
        _emit 0x10
        // mov dword ptr [eax + 0x10], edx
        _emit 0x8B
        _emit 0x51
        _emit 0x14
        // mov edx, dword ptr [ecx + 0x14]
        _emit 0x89
        _emit 0x50
        _emit 0x14
        // mov dword ptr [eax + 0x14], edx
        _emit 0x8B
        _emit 0x51
        _emit 0x18
        // mov edx, dword ptr [ecx + 0x18]
        _emit 0x89
        _emit 0x50
        _emit 0x18
        // mov dword ptr [eax + 0x18], edx
        _emit 0x8B
        _emit 0x49
        _emit 0x1C
        // mov ecx, dword ptr [ecx + 0x1c]
        _emit 0x89
        _emit 0x48
        _emit 0x1C
        // mov dword ptr [eax + 0x1c], ecx
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}
