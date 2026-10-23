// Slice s011090b0: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_010ec4a0();
extern "C" void FUN_010ec540();
extern "C" void FUN_01108a10();
extern "C" void FUN_01108ac0();
extern "C" void FUN_01108b80();
extern "C" void FUN_01108c30();

// @ 0x011090b0  (943 bytes)
__declspec(naked) void FUN_011090b0()
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
        _emit 0xB8
        _emit 0x70
        _emit 0x5F
        _emit 0x4A
        _emit 0x01
        // mov eax, 0x14a5f70
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7D
        _emit 0x08
        // mov edi, dword ptr [ebp + 8]
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], eax
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebx, [ebx]
        _emit 0x0F
        _emit 0xB7
        _emit 0x00
        // movzx eax, word ptr [eax]
        _emit 0x8B
        _emit 0x5D
        _emit 0x10
        // mov ebx, dword ptr [ebp + 0x10]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x23
        _emit 0xCB
        // and ecx, ebx
        _emit 0x66
        _emit 0x85
        _emit 0xC9
        // test cx, cx
        _emit 0x0F
        _emit 0x85
        _emit 0x5D
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // jne 0x1109440
        _emit 0x8B
        _emit 0x4D
        _emit 0x0C
        // mov ecx, dword ptr [ebp + 0xc]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], ecx
        _emit 0x32
        _emit 0xC5
        // xor al, ch
        _emit 0x8A
        _emit 0xCD
        // mov cl, ch
        _emit 0x80
        _emit 0xE1
        _emit 0x0F
        // and cl, 0xf
        _emit 0x0A
        _emit 0xC1
        // or al, cl
        _emit 0x8A
        _emit 0xC8
        // mov cl, al
        _emit 0x0F
        _emit 0xB6
        _emit 0x47
        _emit 0x21
        // movzx eax, byte ptr [edi + 0x21]
        _emit 0x48
        // dec eax
        _emit 0x88
        _emit 0x4C
        _emit 0x24
        _emit 0x15
        // mov byte ptr [esp + 0x15], cl
        _emit 0x78
        _emit 0x16
        // js 0x1109116
        _emit 0x8A
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov dl, byte ptr [esp + 0x14]
        _emit 0x38
        _emit 0x14
        _emit 0x87
        // cmp byte ptr [edi + eax*4], dl
        _emit 0x75
        _emit 0x0A
        // jne 0x1109113
        _emit 0x38
        _emit 0x4C
        _emit 0x87
        _emit 0x01
        // cmp byte ptr [edi + eax*4 + 1], cl
        _emit 0x0F
        _emit 0x84
        _emit 0x2D
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // je 0x1109440
        _emit 0x48
        // dec eax
        _emit 0x79
        _emit 0xEE
        // jns 0x1109104
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // lea edx, [esp + 0x14]
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // lea eax, [esp + 0x44]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_01108ac0
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x50
        // mov ecx, dword ptr [esp + 0x50]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x54
        // mov edx, dword ptr [esp + 0x54]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x58
        // mov eax, dword ptr [esp + 0x58]
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], ecx
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x5C
        // mov ecx, dword ptr [esp + 0x5c]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], edx
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // mov dword ptr [esp + 0x28], eax
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
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov dword ptr [esp + 0x2c], ecx
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
        _emit 0x2C
        // fld dword ptr [esp + 0x2c]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x2C
        // fstp dword ptr [esp + 0x2c]
        _emit 0xD8
        _emit 0x9E
        _emit 0xA0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcomp dword ptr [esi + 0xa0]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x04
        // jp 0x110917c
        _emit 0xB2
        _emit 0x01
        // mov dl, 1
        _emit 0xEB
        _emit 0x02
        // jmp 0x110917e
        _emit 0x32
        _emit 0xD2
        // xor dl, dl
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0x9E
        _emit 0xA4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcomp dword ptr [esi + 0xa4]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x04
        // jp 0x1109193
        _emit 0xB3
        _emit 0x01
        // mov bl, 1
        _emit 0xEB
        _emit 0x02
        // jmp 0x1109195
        _emit 0x32
        _emit 0xDB
        // xor bl, bl
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0xD8
        _emit 0x9E
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcomp dword ptr [esi + 0xa8]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x04
        // jp 0x11091aa
        _emit 0xB1
        _emit 0x01
        // mov cl, 1
        _emit 0xEB
        _emit 0x02
        // jmp 0x11091ac
        _emit 0x32
        _emit 0xC9
        // xor cl, cl
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // fld dword ptr [esp + 0x2c]
        _emit 0xD8
        _emit 0x9E
        _emit 0xAC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcomp dword ptr [esi + 0xac]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x04
        // jp 0x11091c1
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0xEB
        _emit 0x02
        // jmp 0x11091c3
        _emit 0x32
        _emit 0xC0
        // xor al, al
        _emit 0xD1
        _emit 0xE1
        // shl ecx, 1
        _emit 0xC1
        _emit 0xE3
        _emit 0x02
        // shl ebx, 2
        _emit 0x0B
        _emit 0xCB
        // or ecx, ebx
        _emit 0xF7
        _emit 0xDA
        // neg edx
        _emit 0xC1
        _emit 0xE2
        _emit 0x03
        // shl edx, 3
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
        _emit 0x61
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // jne 0x1109440
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x78
        // mov eax, dword ptr [esp + 0x78]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x70
        // fld dword ptr [esp + 0x70]
        _emit 0xD8
        _emit 0x4C
        _emit 0x84
        _emit 0x40
        // fmul dword ptr [esp + eax*4 + 0x40]
        _emit 0xD9
        _emit 0xE0
        // fchs 
        _emit 0xD8
        _emit 0x64
        _emit 0x86
        _emit 0x60
        // fsub dword ptr [esi + eax*4 + 0x60]
        _emit 0xD9
        _emit 0x54
        _emit 0x24
        _emit 0x74
        // fst dword ptr [esp + 0x74]
        _emit 0xD9
        _emit 0x45
        _emit 0x14
        // fld dword ptr [ebp + 0x14]
        _emit 0xD8
        _emit 0x25
        _emit 0x80
        _emit 0x5F
        _emit 0x4A
        _emit 0x01
        // fsub dword ptr [0x14a5f80]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xDE
        _emit 0xD9
        // fcompp 
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x01
        // test ah, 1
        _emit 0x0F
        _emit 0x85
        _emit 0x33
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // jne 0x1109440
        _emit 0x8A
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov al, byte ptr [esp + 0x14]
        _emit 0x3C
        _emit 0x06
        // cmp al, 6
        _emit 0x0F
        _emit 0x87
        _emit 0x1D
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // ja 0x1109336
        _emit 0x3C
        _emit 0x02
        // cmp al, 2
        _emit 0x77
        _emit 0x50
        // ja 0x110926d
        _emit 0x8B
        _emit 0x46
        _emit 0x18
        // mov eax, dword ptr [esi + 0x18]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x58
        // fld dword ptr [esp + 0x58]
        _emit 0xD8
        _emit 0x48
        _emit 0x20
        // fmul dword ptr [eax + 0x20]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x54
        // fld dword ptr [esp + 0x54]
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
        _emit 0x50
        // fld dword ptr [esp + 0x50]
        _emit 0xD8
        _emit 0x08
        // fmul dword ptr [eax]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x40
        _emit 0x30
        // fadd dword ptr [eax + 0x30]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x58
        // fld dword ptr [esp + 0x58]
        _emit 0xD8
        _emit 0x48
        _emit 0x24
        // fmul dword ptr [eax + 0x24]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x54
        // fld dword ptr [esp + 0x54]
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
        _emit 0x50
        // fld dword ptr [esp + 0x50]
        _emit 0xD8
        _emit 0x48
        _emit 0x04
        // fmul dword ptr [eax + 4]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x40
        _emit 0x34
        // fadd dword ptr [eax + 0x34]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x58
        // fld dword ptr [esp + 0x58]
        _emit 0xD8
        _emit 0x48
        _emit 0x28
        // fmul dword ptr [eax + 0x28]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x54
        // fld dword ptr [esp + 0x54]
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
        _emit 0x50
        // fld dword ptr [esp + 0x50]
        _emit 0xEB
        _emit 0x4E
        // jmp 0x11092bb
        _emit 0x8B
        _emit 0x46
        _emit 0x14
        // mov eax, dword ptr [esi + 0x14]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // fld dword ptr [esp + 0x48]
        _emit 0xD8
        _emit 0x48
        _emit 0x20
        // fmul dword ptr [eax + 0x20]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // fld dword ptr [esp + 0x44]
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
        _emit 0x40
        // fld dword ptr [esp + 0x40]
        _emit 0xD8
        _emit 0x08
        // fmul dword ptr [eax]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x40
        _emit 0x30
        // fadd dword ptr [eax + 0x30]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // fld dword ptr [esp + 0x48]
        _emit 0xD8
        _emit 0x48
        _emit 0x24
        // fmul dword ptr [eax + 0x24]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // fld dword ptr [esp + 0x44]
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
        _emit 0x40
        // fld dword ptr [esp + 0x40]
        _emit 0xD8
        _emit 0x48
        _emit 0x04
        // fmul dword ptr [eax + 4]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x40
        _emit 0x34
        // fadd dword ptr [eax + 0x34]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x48
        // fld dword ptr [esp + 0x48]
        _emit 0xD8
        _emit 0x48
        _emit 0x28
        // fmul dword ptr [eax + 0x28]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x44
        // fld dword ptr [esp + 0x44]
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
        _emit 0x40
        // fld dword ptr [esp + 0x40]
        _emit 0xD8
        _emit 0x48
        _emit 0x08
        // fmul dword ptr [eax + 8]
        _emit 0x33
        _emit 0xC9
        // xor ecx, ecx
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD8
        _emit 0x40
        _emit 0x38
        // fadd dword ptr [eax + 0x38]
        _emit 0x8A
        _emit 0x47
        _emit 0x21
        // mov al, byte ptr [edi + 0x21]
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x38
        // fstp dword ptr [esp + 0x38]
        _emit 0x76
        _emit 0x62
        // jbe 0x1109332
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x80
        _emit 0x3C
        _emit 0x8F
        _emit 0x06
        // cmp byte ptr [edi + ecx*4], 6
        _emit 0x77
        _emit 0x4E
        // ja 0x1109326
        _emit 0x8B
        _emit 0x46
        _emit 0x10
        // mov eax, dword ptr [esi + 0x10]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0x64
        _emit 0x10
        _emit 0x30
        // fsub dword ptr [eax + edx + 0x30]
        _emit 0x8D
        _emit 0x44
        _emit 0x10
        _emit 0x30
        // lea eax, [eax + edx + 0x30]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0x60
        _emit 0x04
        // fsub dword ptr [eax + 4]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // fld dword ptr [esp + 0x38]
        _emit 0xD8
        _emit 0x60
        _emit 0x08
        // fsub dword ptr [eax + 8]
        _emit 0xD9
        _emit 0x86
        _emit 0xB0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [esi + 0xb0]
        _emit 0xD9
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xD9
        _emit 0xC3
        // fld st(3)
        _emit 0xD8
        _emit 0xCC
        // fmul st(4)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
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
        _emit 0xC1
        // fld st(1)
        _emit 0xD8
        _emit 0xCA
        // fmul st(2)
        _emit 0xD8
        _emit 0x05
        _emit 0x80
        _emit 0x5F
        _emit 0x4A
        _emit 0x01
        // fadd dword ptr [0x14a5f80]
        _emit 0xDE
        _emit 0xD9
        // fcompp 
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
        _emit 0x01
        // test ah, 1
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x0F
        _emit 0x84
        _emit 0x16
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // je 0x110943c
        _emit 0x0F
        _emit 0xB6
        _emit 0x47
        _emit 0x21
        // movzx eax, byte ptr [edi + 0x21]
        _emit 0x41
        // inc ecx
        _emit 0x83
        _emit 0xC2
        _emit 0x30
        // add edx, 0x30
        _emit 0x3B
        _emit 0xC8
        // cmp ecx, eax
        _emit 0x7C
        _emit 0xA0
        // jl 0x11092d2
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x80
        _emit 0x7F
        _emit 0x21
        _emit 0x08
        // cmp byte ptr [edi + 0x21], 8
        _emit 0x0F
        _emit 0x83
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jae 0x1109440
        _emit 0x8B
        _emit 0x56
        _emit 0x04
        // mov edx, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // lea ecx, [esp + 0x14]
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_010ec540
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], eax
        _emit 0x0F
        _emit 0x8C
        _emit 0xE1
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jl 0x1109440
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x78
        // mov eax, dword ptr [esp + 0x78]
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x8B
        _emit 0x4E
        _emit 0x10
        // mov ecx, dword ptr [esi + 0x10]
        _emit 0x8B
        _emit 0x19
        // mov ebx, dword ptr [ecx]
        _emit 0x7F
        _emit 0x14
        // jg 0x1109381
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x40
        // lea edx, [esp + 0x40]
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // lea eax, [esp + 0x18]
        _emit 0x50
        // push eax
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_01108a10
        _emit 0xEB
        _emit 0x2B
        // jmp 0x11093ac
        _emit 0x83
        _emit 0xF8
        _emit 0x06
        // cmp eax, 6
        _emit 0x7F
        _emit 0x14
        // jg 0x110939a
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x40
        // lea ecx, [esp + 0x40]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x18
        // lea edx, [esp + 0x18]
        _emit 0x52
        // push edx
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_01108b80
        _emit 0xEB
        _emit 0x12
        // jmp 0x11093ac
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x40
        // lea eax, [esp + 0x40]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        _emit 0x51
        // push ecx
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_01108c30
        _emit 0x80
        _emit 0x7F
        _emit 0x21
        _emit 0x01
        // cmp byte ptr [edi + 0x21], 1
        _emit 0x76
        _emit 0x38
        // jbe 0x11093ea
        _emit 0x8B
        _emit 0x56
        _emit 0x10
        // mov edx, dword ptr [esi + 0x10]
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0xD9
        _emit 0x40
        _emit 0xE8
        // fld dword ptr [eax - 0x18]
        _emit 0x83
        _emit 0xE8
        _emit 0x20
        // sub eax, 0x20
        _emit 0xD8
        _emit 0x4B
        _emit 0x18
        // fmul dword ptr [ebx + 0x18]
        _emit 0xD9
        _emit 0x40
        _emit 0x04
        // fld dword ptr [eax + 4]
        _emit 0xD8
        _emit 0x4B
        _emit 0x14
        // fmul dword ptr [ebx + 0x14]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x00
        // fld dword ptr [eax]
        _emit 0xD8
        _emit 0x4B
        _emit 0x10
        // fmul dword ptr [ebx + 0x10]
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
        _emit 0x7A
        _emit 0x0E
        // jp 0x11093ea
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov eax, dword ptr [esp + 0x18]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_010ec4a0
        _emit 0xEB
        _emit 0x56
        // jmp 0x1109440
        _emit 0x8B
        _emit 0x46
        _emit 0x08
        // mov eax, dword ptr [esi + 8]
        _emit 0x8B
        _emit 0x4E
        _emit 0x0C
        // mov ecx, dword ptr [esi + 0xc]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x53
        // push ebx
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x50
        // push eax
        _emit 0xFF
        _emit 0x52
        _emit 0x08
        // call dword ptr [edx + 8]
        _emit 0x66
        _emit 0x3D
        _emit 0xFF
        _emit 0xFF
        // cmp ax, 0xffff
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x66
        _emit 0x89
        _emit 0x44
        _emit 0x8F
        _emit 0x02
        // mov word ptr [edi + ecx*4 + 2], ax
        _emit 0x75
        _emit 0x0A
        // jne 0x1109417
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_010ec4a0
        _emit 0xEB
        _emit 0x29
        // jmp 0x1109440
        _emit 0x8B
        _emit 0x46
        _emit 0x10
        // mov eax, dword ptr [esi + 0x10]
        _emit 0x83
        _emit 0x00
        _emit 0x30
        // add dword ptr [eax], 0x30
        _emit 0x66
        _emit 0x8B
        _emit 0x54
        _emit 0x8F
        _emit 0x02
        // mov dx, word ptr [edi + ecx*4 + 2]
        _emit 0x66
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x16
        // mov word ptr [esp + 0x16], dx
        _emit 0x66
        _emit 0x8B
        _emit 0x44
        _emit 0x8F
        _emit 0x02
        // mov ax, word ptr [edi + ecx*4 + 2]
        _emit 0x66
        _emit 0x89
        _emit 0x43
        _emit 0x20
        // mov word ptr [ebx + 0x20], ax
        _emit 0x80
        _emit 0x7C
        _emit 0x24
        _emit 0x14
        _emit 0x06
        // cmp byte ptr [esp + 0x14], 6
        _emit 0x77
        _emit 0x09
        // ja 0x1109440
        _emit 0xFE
        _emit 0x47
        _emit 0x20
        // inc byte ptr [edi + 0x20]
        _emit 0xEB
        _emit 0x04
        // jmp 0x1109440
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov eax, dword ptr [esp + 0x1c]
        _emit 0x83
        _emit 0xC0
        _emit 0x02
        // add eax, 2
        _emit 0x3D
        _emit 0x7E
        _emit 0x5F
        _emit 0x4A
        _emit 0x01
        // cmp eax, 0x14a5f7e
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], eax
        _emit 0x0F
        _emit 0x8C
        _emit 0x7A
        _emit 0xFC
        _emit 0xFF
        _emit 0xFF
        // jl 0x11090d0
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
    }
}
