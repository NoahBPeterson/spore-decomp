// Slice s01113e90: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_01081360();
extern "C" void FUN_01081440();

// @ 0x01113e90  (317 bytes)
__declspec(naked) void FUN_01113e90()
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
        _emit 0x74
        // sub esp, 0x74
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7D
        _emit 0x08
        // mov edi, dword ptr [ebp + 8]
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x50
        // lea ecx, [esp + 0x50]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xFF
        _emit 0x50
        _emit 0x2C
        // call dword ptr [eax + 0x2c]
        _emit 0x8B
        _emit 0x5D
        _emit 0x0C
        // mov ebx, dword ptr [ebp + 0xc]
        _emit 0x8B
        _emit 0x13
        // mov edx, dword ptr [ebx]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x60
        // lea eax, [esp + 0x60]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0x52
        _emit 0x2C
        // call dword ptr [edx + 0x2c]
        _emit 0x8B
        _emit 0x55
        _emit 0x10
        // mov edx, dword ptr [ebp + 0x10]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x60
        // lea ecx, [esp + 0x60]
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x38
        // lea ecx, [esp + 0x38]
        call FUN_01081360
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // fld dword ptr [esp + 0x30]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x50
        // fsub dword ptr [esp + 0x50]
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // lea ecx, [esp + 0x40]
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // lea edx, [esp + 0x14]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // fld dword ptr [esp + 0x38]
        _emit 0x52
        // push edx
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x5C
        // fsub dword ptr [esp + 0x5c]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // fld dword ptr [esp + 0x40]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x60
        // fsub dword ptr [esp + 0x60]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // fld dword ptr [esp + 0x44]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x64
        // fsub dword ptr [esp + 0x64]
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
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // fld dword ptr [esp + 0x30]
        _emit 0x8B
        _emit 0x55
        _emit 0x10
        // mov edx, dword ptr [ebp + 0x10]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x40
        // fsub dword ptr [esp + 0x40]
        _emit 0x66
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x4C
        // mov ax, word ptr [esp + 0x4c]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // lea ecx, [esp + 0x10]
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0x52
        // push edx
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        // fld dword ptr [esp + 0x3c]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // lea ecx, [esp + 0x28]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x4C
        // fsub dword ptr [esp + 0x4c]
        _emit 0x66
        _emit 0x89
        _emit 0x06
        // mov word ptr [esi], ax
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // fld dword ptr [esp + 0x40]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x50
        // fsub dword ptr [esp + 0x50]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // fld dword ptr [esp + 0x44]
        _emit 0xD8
        _emit 0x64
        _emit 0x24
        _emit 0x54
        // fsub dword ptr [esp + 0x54]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x24
        // fstp dword ptr [esp + 0x24]
        call FUN_01081440
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0xD9
        _emit 0xE0
        // fchs 
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x70
        // lea ecx, [esp + 0x70]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // lea edx, [esp + 0x24]
        _emit 0xD9
        _emit 0xE0
        // fchs 
        _emit 0x52
        // push edx
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x2C
        // fstp dword ptr [esp + 0x2c]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // fld dword ptr [esp + 0x30]
        _emit 0xD9
        _emit 0xE0
        // fchs 
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
        _emit 0xE0
        // fchs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x34
        // fstp dword ptr [esp + 0x34]
        _emit 0xFF
        _emit 0x50
        _emit 0x24
        // call dword ptr [eax + 0x24]
        _emit 0x66
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x7C
        // mov ax, word ptr [esp + 0x7c]
        _emit 0x66
        _emit 0x89
        _emit 0x46
        _emit 0x02
        // mov word ptr [esi + 2], ax
        _emit 0xB8
        _emit 0xFF
        _emit 0xFF
        _emit 0x00
        _emit 0x00
        // mov eax, 0xffff
        _emit 0x66
        _emit 0x89
        _emit 0x46
        _emit 0x04
        // mov word ptr [esi + 4], ax
        _emit 0x66
        _emit 0x89
        _emit 0x46
        _emit 0x06
        // mov word ptr [esi + 6], ax
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x88
        _emit 0x46
        _emit 0x08
        // mov byte ptr [esi + 8], al
        _emit 0x88
        _emit 0x46
        _emit 0x09
        // mov byte ptr [esi + 9], al
        _emit 0x8B
        _emit 0x17
        // mov edx, dword ptr [edi]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xFF
        _emit 0x52
        _emit 0x30
        // call dword ptr [edx + 0x30]
        _emit 0x88
        _emit 0x46
        _emit 0x0A
        // mov byte ptr [esi + 0xa], al
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x8B
        _emit 0xCB
        // mov ecx, ebx
        _emit 0xFF
        _emit 0x50
        _emit 0x30
        // call dword ptr [eax + 0x30]
        _emit 0x5F
        // pop edi
        _emit 0x88
        _emit 0x46
        _emit 0x0B
        // mov byte ptr [esi + 0xb], al
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
        _emit 0x0C
        _emit 0x00
        // ret 0xc
    }
}

// @ 0x01113fd0  (829 bytes)
__declspec(naked) void FUN_01113fd0()
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
        _emit 0xB8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // sub esp, 0xb8
        _emit 0x8B
        _emit 0x45
        _emit 0x10
        // mov eax, dword ptr [ebp + 0x10]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x66
        _emit 0xC7
        _emit 0x46
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // mov word ptr [esi + 2], 0
        _emit 0x66
        _emit 0xC7
        _emit 0x46
        _emit 0x04
        _emit 0x10
        _emit 0x00
        // mov word ptr [esi + 4], 0x10
        _emit 0x66
        _emit 0xC7
        _emit 0x46
        _emit 0x06
        _emit 0x20
        _emit 0x00
        // mov word ptr [esi + 6], 0x20
        _emit 0xD9
        _emit 0x00
        // fld dword ptr [eax]
        _emit 0x8B
        _emit 0x48
        _emit 0x08
        // mov ecx, dword ptr [eax + 8]
        _emit 0xD9
        _emit 0x40
        _emit 0x04
        // fld dword ptr [eax + 4]
        _emit 0x8B
        _emit 0x50
        _emit 0x14
        // mov edx, dword ptr [eax + 0x14]
        _emit 0xD9
        _emit 0x40
        _emit 0x10
        // fld dword ptr [eax + 0x10]
        _emit 0xD9
        _emit 0x40
        _emit 0x20
        // fld dword ptr [eax + 0x20]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x60
        // mov dword ptr [esp + 0x60], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x24
        // mov edx, dword ptr [eax + 0x24]
        _emit 0xD9
        _emit 0x40
        _emit 0x30
        // fld dword ptr [eax + 0x30]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x54
        // mov dword ptr [esp + 0x54], ecx
        _emit 0x8B
        _emit 0x48
        _emit 0x18
        // mov ecx, dword ptr [eax + 0x18]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x70
        // mov dword ptr [esp + 0x70], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x34
        // mov edx, dword ptr [eax + 0x34]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x64
        // mov dword ptr [esp + 0x64], ecx
        _emit 0x8B
        _emit 0x48
        _emit 0x28
        // mov ecx, dword ptr [eax + 0x28]
        _emit 0x8B
        _emit 0x40
        _emit 0x38
        // mov eax, dword ptr [eax + 0x38]
        _emit 0x89
        _emit 0x84
        _emit 0x24
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x84], eax
        _emit 0x8B
        _emit 0x45
        _emit 0x0C
        // mov eax, dword ptr [ebp + 0xc]
        _emit 0xD9
        _emit 0x40
        _emit 0x10
        // fld dword ptr [eax + 0x10]
        _emit 0x89
        _emit 0x94
        _emit 0x24
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x80], edx
        _emit 0x8B
        _emit 0x50
        _emit 0x18
        // mov edx, dword ptr [eax + 0x18]
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x04
        // mov dword ptr [esp + 4], edx
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x04
        // fmul dword ptr [esp + 4]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x74
        // mov dword ptr [esp + 0x74], ecx
        _emit 0x8B
        _emit 0x48
        _emit 0x14
        // mov ecx, dword ptr [eax + 0x14]
        _emit 0xD9
        _emit 0xC4
        // fld st(4)
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // mov dword ptr [esp + 8], ecx
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // fmul dword ptr [esp + 8]
        _emit 0x8B
        _emit 0x50
        _emit 0x28
        // mov edx, dword ptr [eax + 0x28]
        _emit 0x8B
        _emit 0x48
        _emit 0x24
        // mov ecx, dword ptr [eax + 0x24]
        _emit 0x57
        // push edi
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC6
        // fld st(6)
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0xC2
        // fadd st(2)
        _emit 0xD9
        _emit 0x9C
        _emit 0x24
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [esp + 0x90]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x74
        // fld dword ptr [esp + 0x74]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // fmul dword ptr [esp + 8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x64
        // fld dword ptr [esp + 0x64]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC5
        // fld st(5)
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x84
        _emit 0x24
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fadd dword ptr [esp + 0x84]
        _emit 0xD9
        _emit 0x9C
        _emit 0x24
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [esp + 0x94]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x78
        // fld dword ptr [esp + 0x78]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // fmul dword ptr [esp + 8]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // mov dword ptr [esp + 8], edx
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x68
        // fld dword ptr [esp + 0x68]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], ecx
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x58
        // fld dword ptr [esp + 0x58]
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x84
        _emit 0x24
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fadd dword ptr [esp + 0x88]
        _emit 0xD9
        _emit 0x9C
        _emit 0x24
        _emit 0x98
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [esp + 0x98]
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xD9
        _emit 0x40
        _emit 0x20
        // fld dword ptr [eax + 0x20]
        _emit 0xD9
        _emit 0xC2
        // fld st(2)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // fmul dword ptr [esp + 8]
        _emit 0xD9
        _emit 0xC4
        // fld st(4)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC6
        // fld st(6)
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0xC2
        // fadd st(2)
        _emit 0xD9
        _emit 0x9C
        _emit 0x24
        _emit 0xA0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [esp + 0xa0]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x74
        // fld dword ptr [esp + 0x74]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // fmul dword ptr [esp + 8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x64
        // fld dword ptr [esp + 0x64]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0x8B
        _emit 0x48
        _emit 0x30
        // mov ecx, dword ptr [eax + 0x30]
        _emit 0x8B
        _emit 0x50
        _emit 0x34
        // mov edx, dword ptr [eax + 0x34]
        _emit 0x8B
        _emit 0x40
        _emit 0x38
        // mov eax, dword ptr [eax + 0x38]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], ecx
        _emit 0xD9
        _emit 0xC5
        // fld st(5)
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x84
        _emit 0x24
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fadd dword ptr [esp + 0x84]
        _emit 0xD9
        _emit 0x9C
        _emit 0x24
        _emit 0xA4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [esp + 0xa4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x78
        // fld dword ptr [esp + 0x78]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // fmul dword ptr [esp + 8]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov dword ptr [esp + 8], eax
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x68
        // fld dword ptr [esp + 0x68]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // mov dword ptr [esp + 0xc], edx
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x58
        // fld dword ptr [esp + 0x58]
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x84
        _emit 0x24
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fadd dword ptr [esp + 0x88]
        _emit 0xD9
        _emit 0x9C
        _emit 0x24
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [esp + 0xa8]
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // fmul dword ptr [esp + 8]
        _emit 0xD9
        _emit 0xCA
        // fxch st(2)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0xDE
        _emit 0xC2
        // faddp st(2)
        _emit 0xD9
        _emit 0xCB
        // fxch st(3)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // fmul dword ptr [esp + 0x2c]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0xC2
        // fadd st(2)
        _emit 0xD9
        _emit 0x9C
        _emit 0x24
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fstp dword ptr [esp + 0xb0]
        _emit 0xDD
        _emit 0xD9
        // fstp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x74
        // fld dword ptr [esp + 0x74]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // fmul dword ptr [esp + 8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x64
        // fld dword ptr [esp + 0x64]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // fmul dword ptr [esp + 0xc]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // fmul dword ptr [esp + 0x2c]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x84
        _emit 0x24
        _emit 0x84
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fadd dword ptr [esp + 0x84]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x78
        // fld dword ptr [esp + 0x78]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // fmul dword ptr [esp + 8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x68
        // fld dword ptr [esp + 0x68]
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
        _emit 0x58
        // fld dword ptr [esp + 0x58]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // fmul dword ptr [esp + 0x2c]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x84
        _emit 0x24
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fadd dword ptr [esp + 0x88]
        _emit 0xD9
        _emit 0x84
        _emit 0x24
        _emit 0xA0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [esp + 0xa0]
        _emit 0xD8
        _emit 0xA4
        _emit 0x24
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fsub dword ptr [esp + 0x90]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x30
        // fstp dword ptr [esp + 0x30]
        _emit 0xD9
        _emit 0x84
        _emit 0x24
        _emit 0xA4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [esp + 0xa4]
        _emit 0xD8
        _emit 0xA4
        _emit 0x24
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fsub dword ptr [esp + 0x94]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x34
        // fstp dword ptr [esp + 0x34]
        _emit 0xD9
        _emit 0x84
        _emit 0x24
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [esp + 0xa8]
        _emit 0xD8
        _emit 0xA4
        _emit 0x24
        _emit 0x98
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fsub dword ptr [esp + 0x98]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x38
        // fstp dword ptr [esp + 0x38]
        _emit 0xD9
        _emit 0x84
        _emit 0x24
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [esp + 0xb0]
        _emit 0xD8
        _emit 0xA4
        _emit 0x24
        _emit 0xA0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fsub dword ptr [esp + 0xa0]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x40
        // fstp dword ptr [esp + 0x40]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0xA4
        _emit 0x24
        _emit 0xA4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fsub dword ptr [esp + 0xa4]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x44
        // fstp dword ptr [esp + 0x44]
        _emit 0xD8
        _emit 0xA4
        _emit 0x24
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fsub dword ptr [esp + 0xa8]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // fld dword ptr [esp + 0x34]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // fld dword ptr [esp + 0x44]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x38
        // fmul dword ptr [esp + 0x38]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // fstp dword ptr [esp + 0x10]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // fld dword ptr [esp + 0x38]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // fmul dword ptr [esp + 0x40]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x30
        // fmul dword ptr [esp + 0x30]
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x14
        // fstp dword ptr [esp + 0x14]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // fld dword ptr [esp + 0x44]
        _emit 0x8B
        _emit 0x7D
        _emit 0x08
        // mov edi, dword ptr [ebp + 8]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x30
        // fmul dword ptr [esp + 0x30]
        _emit 0x8B
        _emit 0x17
        // mov edx, dword ptr [edi]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // fld dword ptr [esp + 0x34]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // lea eax, [esp + 0x40]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // fmul dword ptr [esp + 0x40]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x20
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x20], 0
        _emit 0xDE
        _emit 0xE9
        // fsubp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0xFF
        _emit 0x52
        _emit 0x2C
        // call dword ptr [edx + 0x2c]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // fld dword ptr [esp + 0x40]
        _emit 0xD8
        _emit 0xA4
        _emit 0x24
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fsub dword ptr [esp + 0x90]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // fld dword ptr [esp + 0x44]
        _emit 0xD8
        _emit 0xA4
        _emit 0x24
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fsub dword ptr [esp + 0x94]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // fld dword ptr [esp + 0x48]
        _emit 0xD8
        _emit 0xA4
        _emit 0x24
        _emit 0x98
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fsub dword ptr [esp + 0x98]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD9
        _emit 0xCA
        // fxch st(2)
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // fmul dword ptr [esp + 0x14]
        _emit 0xDE
        _emit 0xC2
        // faddp st(2)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xD8
        _emit 0xCB
        // fmul st(3)
        _emit 0xDE
        _emit 0xC2
        // faddp st(2)
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
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
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x7A
        _emit 0x28
        // jp 0x11142d6
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xD9
        _emit 0xE0
        // fchs 
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
        _emit 0xD9
        _emit 0xE0
        // fchs 
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
        _emit 0xD9
        _emit 0xE0
        // fchs 
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
        _emit 0xD9
        _emit 0xE0
        // fchs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x1C
        // fstp dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x17
        // mov edx, dword ptr [edi]
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // lea eax, [esp + 0x30]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // lea ecx, [esp + 0x14]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xFF
        _emit 0x52
        _emit 0x24
        // call dword ptr [edx + 0x24]
        _emit 0x66
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x3C
        // mov dx, word ptr [esp + 0x3c]
        _emit 0x66
        _emit 0x89
        _emit 0x16
        // mov word ptr [esi], dx
        _emit 0xC6
        _emit 0x46
        _emit 0x08
        _emit 0x01
        // mov byte ptr [esi + 8], 1
        _emit 0xC6
        _emit 0x46
        _emit 0x09
        _emit 0x03
        // mov byte ptr [esi + 9], 3
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xFF
        _emit 0x50
        _emit 0x30
        // call dword ptr [eax + 0x30]
        _emit 0x5F
        // pop edi
        _emit 0x88
        _emit 0x46
        _emit 0x0A
        // mov byte ptr [esi + 0xa], al
        _emit 0xC6
        _emit 0x46
        _emit 0x0B
        _emit 0x03
        // mov byte ptr [esi + 0xb], 3
        _emit 0x5E
        // pop esi
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

// @ 0x01114310  (85 bytes)
__declspec(naked) void FUN_01114310()
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
        _emit 0x51
        _emit 0x1C
        // mov edx, dword ptr [ecx + 0x1c]
        _emit 0x89
        _emit 0x50
        _emit 0x1C
        // mov dword ptr [eax + 0x1c], edx
        _emit 0x8B
        _emit 0x51
        _emit 0x20
        // mov edx, dword ptr [ecx + 0x20]
        _emit 0x89
        _emit 0x50
        _emit 0x20
        // mov dword ptr [eax + 0x20], edx
        _emit 0x8B
        _emit 0x51
        _emit 0x24
        // mov edx, dword ptr [ecx + 0x24]
        _emit 0x89
        _emit 0x50
        _emit 0x24
        // mov dword ptr [eax + 0x24], edx
        _emit 0x8B
        _emit 0x51
        _emit 0x28
        // mov edx, dword ptr [ecx + 0x28]
        _emit 0x89
        _emit 0x50
        _emit 0x28
        // mov dword ptr [eax + 0x28], edx
        _emit 0x8B
        _emit 0x51
        _emit 0x2C
        // mov edx, dword ptr [ecx + 0x2c]
        _emit 0x89
        _emit 0x50
        _emit 0x2C
        // mov dword ptr [eax + 0x2c], edx
        _emit 0x8B
        _emit 0x49
        _emit 0x30
        // mov ecx, dword ptr [ecx + 0x30]
        _emit 0x89
        _emit 0x48
        _emit 0x30
        // mov dword ptr [eax + 0x30], ecx
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}
