// Slice s0110ad70: Spore/RenderWare engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_010d93e0();
extern "C" void FUN_010ec500();
extern "C" void FUN_01108750();
extern "C" void FUN_011088b0();
extern "C" void FUN_01108a10();
extern "C" void FUN_01108b80();
extern "C" void FUN_01108c30();
extern "C" void FUN_01109460();
extern "C" void FUN_0110a0d0();
extern "C" void FUN_0110a2b0();
extern "C" void FUN_0110a4b0();
extern "C" void FUN_0110a600();
extern "C" void FUN_0110ad70();

// @ 0x0110ad70  (1251 bytes)
__declspec(naked) void FUN_0110ad70()
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
        _emit 0x34
        // sub esp, 0x34
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x08
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x18], 8
        _emit 0xEB
        _emit 0x08
        // jmp 0x110ad90
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea esp, [esp]
        _emit 0x90
        // nop 
        _emit 0xD9
        _emit 0x87
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [edi + 0xe0]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0xD8
        _emit 0x97
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcom dword ptr [edi + 0xe0]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x08
        // jp 0x110adad
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xD9
        _emit 0x87
        _emit 0xE0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [edi + 0xe0]
        _emit 0xD8
        _emit 0x97
        _emit 0xE4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcom dword ptr [edi + 0xe4]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x0D
        // jp 0x110adc7
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xBB
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 1
        _emit 0xD9
        _emit 0x87
        _emit 0xE4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [edi + 0xe4]
        _emit 0xD8
        _emit 0x97
        _emit 0xE8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcom dword ptr [edi + 0xe8]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x0D
        // jp 0x110ade1
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xBB
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 2
        _emit 0xD9
        _emit 0x87
        _emit 0xE8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [edi + 0xe8]
        _emit 0xD8
        _emit 0x97
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcom dword ptr [edi + 0xf0]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x0D
        // jp 0x110adfb
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xBB
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 4
        _emit 0xD9
        _emit 0x87
        _emit 0xF0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [edi + 0xf0]
        _emit 0xD8
        _emit 0x97
        _emit 0xF4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcom dword ptr [edi + 0xf4]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x0D
        // jp 0x110ae15
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xBB
        _emit 0x05
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 5
        _emit 0xD9
        _emit 0x87
        _emit 0xF4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [edi + 0xf4]
        _emit 0xD8
        _emit 0x97
        _emit 0xF8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcom dword ptr [edi + 0xf8]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x0D
        // jp 0x110ae2f
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xBB
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 6
        _emit 0xD9
        _emit 0x87
        _emit 0xF8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fld dword ptr [edi + 0xf8]
        _emit 0xD8
        _emit 0x97
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fcom dword ptr [edi + 0x100]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x0D
        // jp 0x110ae49
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xBB
        _emit 0x08
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 8
        _emit 0xD9
        _emit 0x87
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fld dword ptr [edi + 0x100]
        _emit 0xD8
        _emit 0x97
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fcom dword ptr [edi + 0x104]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x0D
        // jp 0x110ae63
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xBB
        _emit 0x09
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 9
        _emit 0xD9
        _emit 0x87
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fld dword ptr [edi + 0x104]
        _emit 0xD8
        _emit 0x97
        _emit 0x08
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fcom dword ptr [edi + 0x108]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x0D
        // jp 0x110ae7d
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xBB
        _emit 0x0A
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 0xa
        _emit 0xD9
        _emit 0x87
        _emit 0x08
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fld dword ptr [edi + 0x108]
        _emit 0xD8
        _emit 0x97
        _emit 0x10
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fcom dword ptr [edi + 0x110]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x0D
        // jp 0x110ae97
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xBB
        _emit 0x0C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 0xc
        _emit 0xD9
        _emit 0x87
        _emit 0x10
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fld dword ptr [edi + 0x110]
        _emit 0xD8
        _emit 0x97
        _emit 0x14
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fcom dword ptr [edi + 0x114]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x0D
        // jp 0x110aeb1
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xBB
        _emit 0x0D
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 0xd
        _emit 0xD9
        _emit 0x87
        _emit 0x14
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fld dword ptr [edi + 0x114]
        _emit 0xD8
        _emit 0x97
        _emit 0x18
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fcom dword ptr [edi + 0x118]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x0D
        // jp 0x110aecb
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xBB
        _emit 0x0E
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 0xe
        _emit 0xD9
        _emit 0x87
        _emit 0x18
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fld dword ptr [edi + 0x118]
        _emit 0xD8
        _emit 0x97
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fcom dword ptr [edi + 0x120]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x0D
        // jp 0x110aee5
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xBB
        _emit 0x10
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 0x10
        _emit 0xD9
        _emit 0x87
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fld dword ptr [edi + 0x120]
        _emit 0xD8
        _emit 0x97
        _emit 0x24
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fcom dword ptr [edi + 0x124]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x0D
        // jp 0x110aeff
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0xBB
        _emit 0x11
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 0x11
        _emit 0xD9
        _emit 0x87
        _emit 0x24
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fld dword ptr [edi + 0x124]
        _emit 0xD8
        _emit 0x9F
        _emit 0x28
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // fcomp dword ptr [edi + 0x128]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x0F
        _emit 0x8A
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jp 0x110afd4
        _emit 0xBB
        _emit 0x12
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ebx, 0x12
        _emit 0x8B
        _emit 0x75
        _emit 0x10
        // mov esi, dword ptr [ebp + 0x10]
        _emit 0x8D
        _emit 0x43
        _emit 0xF8
        // lea eax, [ebx - 8]
        _emit 0x8B
        _emit 0xD0
        // mov edx, eax
        _emit 0xC1
        _emit 0xEA
        _emit 0x02
        // shr edx, 2
        _emit 0x83
        _emit 0xE0
        _emit 0x03
        // and eax, 3
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0x89
        _emit 0x56
        _emit 0x38
        // mov dword ptr [esi + 0x38], edx
        _emit 0x89
        _emit 0x46
        _emit 0x3C
        // mov dword ptr [esi + 0x3c], eax
        call FUN_0110a4b0
        _emit 0x8B
        _emit 0x46
        _emit 0x3C
        // mov eax, dword ptr [esi + 0x3c]
        _emit 0x8B
        _emit 0x4E
        _emit 0x38
        // mov ecx, dword ptr [esi + 0x38]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4D
        _emit 0x10
        // mov ecx, dword ptr [ebp + 0x10]
        _emit 0x8D
        _emit 0x46
        _emit 0x10
        // lea eax, [esi + 0x10]
        _emit 0x8B
        _emit 0x75
        _emit 0x0C
        // mov esi, dword ptr [ebp + 0xc]
        call FUN_01108750
        _emit 0x0F
        _emit 0xB6
        _emit 0x16
        // movzx edx, byte ptr [esi]
        _emit 0x8B
        _emit 0x4D
        _emit 0x10
        // mov ecx, dword ptr [ebp + 0x10]
        _emit 0x89
        _emit 0x51
        _emit 0x38
        // mov dword ptr [ecx + 0x38], edx
        _emit 0x0F
        _emit 0xB6
        _emit 0x46
        _emit 0x01
        // movzx eax, byte ptr [esi + 1]
        _emit 0x8B
        _emit 0x55
        _emit 0x08
        // mov edx, dword ptr [ebp + 8]
        _emit 0x89
        _emit 0x41
        _emit 0x3C
        // mov dword ptr [ecx + 0x3c], eax
        _emit 0x0F
        _emit 0xB6
        _emit 0x42
        _emit 0x21
        // movzx eax, byte ptr [edx + 0x21]
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x48
        // dec eax
        _emit 0x78
        _emit 0x28
        // js 0x110af8c
        _emit 0x8A
        _emit 0x0E
        // mov cl, byte ptr [esi]
        _emit 0x88
        _emit 0x4C
        _emit 0x24
        _emit 0x17
        // mov byte ptr [esp + 0x17], cl
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebx, [ebx]
        _emit 0x8A
        _emit 0x4C
        _emit 0x24
        _emit 0x17
        // mov cl, byte ptr [esp + 0x17]
        _emit 0x38
        _emit 0x0C
        _emit 0x82
        // cmp byte ptr [edx + eax*4], cl
        _emit 0x75
        _emit 0x0D
        // jne 0x110af86
        _emit 0x8A
        _emit 0x4C
        _emit 0x82
        _emit 0x01
        // mov cl, byte ptr [edx + eax*4 + 1]
        _emit 0x3A
        _emit 0x4E
        _emit 0x01
        // cmp cl, byte ptr [esi + 1]
        _emit 0x0F
        _emit 0x84
        _emit 0xBF
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // je 0x110b245
        _emit 0x48
        // dec eax
        _emit 0x79
        _emit 0xE7
        // jns 0x110af70
        _emit 0x8B
        _emit 0x4D
        _emit 0x10
        // mov ecx, dword ptr [ebp + 0x10]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // lea edx, [esp + 0x20]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        call FUN_0110a600
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
        _emit 0x57
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jne 0x110b0fc
        _emit 0x8B
        _emit 0xC3
        // mov eax, ebx
        _emit 0xC1
        _emit 0xE8
        _emit 0x02
        // shr eax, 2
        _emit 0x83
        _emit 0xE3
        _emit 0x03
        // and ebx, 3
        _emit 0x8D
        _emit 0x4C
        _emit 0x83
        _emit 0x38
        // lea ecx, [ebx + eax*4 + 0x38]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov eax, dword ptr [esp + 0x18]
        _emit 0x48
        // dec eax
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0xC7
        _emit 0x04
        _emit 0x8F
        _emit 0xEE
        _emit 0xFF
        _emit 0x7F
        _emit 0xFF
        // mov dword ptr [edi + ecx*4], 0xff7fffee
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], eax
        _emit 0x0F
        _emit 0x8F
        _emit 0xC7
        _emit 0xFD
        _emit 0xFF
        _emit 0xFF
        // jg 0x110ad90
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
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
        _emit 0x83
        _emit 0xFB
        _emit 0x02
        // cmp ebx, 2
        _emit 0x0F
        _emit 0x87
        _emit 0x2D
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // ja 0x110b10a
        _emit 0x8B
        _emit 0x45
        _emit 0x0C
        // mov eax, dword ptr [ebp + 0xc]
        _emit 0x8B
        _emit 0x75
        _emit 0x10
        // mov esi, dword ptr [ebp + 0x10]
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0x88
        _emit 0x18
        // mov byte ptr [eax], bl
        call FUN_0110a0d0
        _emit 0x8B
        _emit 0x4E
        _emit 0x30
        // mov ecx, dword ptr [esi + 0x30]
        _emit 0x51
        // push ecx
        _emit 0x83
        _emit 0xC6
        _emit 0x10
        // add esi, 0x10
        call FUN_011088b0
        _emit 0x8B
        _emit 0x55
        _emit 0x0C
        // mov edx, dword ptr [ebp + 0xc]
        _emit 0x8B
        _emit 0x75
        _emit 0x08
        // mov esi, dword ptr [ebp + 8]
        _emit 0x88
        _emit 0x42
        _emit 0x01
        // mov byte ptr [edx + 1], al
        _emit 0x0F
        _emit 0xB6
        _emit 0x4E
        _emit 0x21
        // movzx ecx, byte ptr [esi + 0x21]
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x49
        // dec ecx
        _emit 0x78
        _emit 0x15
        // js 0x110b022
        _emit 0x8A
        _emit 0x12
        // mov dl, byte ptr [edx]
        _emit 0x90
        // nop 
        _emit 0x38
        _emit 0x14
        _emit 0x8E
        // cmp byte ptr [esi + ecx*4], dl
        _emit 0x75
        _emit 0x0A
        // jne 0x110b01f
        _emit 0x38
        _emit 0x44
        _emit 0x8E
        _emit 0x01
        // cmp byte ptr [esi + ecx*4 + 1], al
        _emit 0x0F
        _emit 0x84
        _emit 0x26
        _emit 0x02
        _emit 0x00
        _emit 0x00
        // je 0x110b245
        _emit 0x49
        // dec ecx
        _emit 0x79
        _emit 0xEE
        // jns 0x110b010
        _emit 0x8B
        _emit 0x75
        _emit 0x10
        // mov esi, dword ptr [ebp + 0x10]
        _emit 0x8B
        _emit 0xD6
        // mov edx, esi
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x8B
        _emit 0x4A
        _emit 0x04
        // mov ecx, dword ptr [edx + 4]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // mov dword ptr [esp + 0x20], eax
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // fld dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0x42
        _emit 0x08
        // mov eax, dword ptr [edx + 8]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // mov dword ptr [esp + 0x24], ecx
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0x8B
        _emit 0x4A
        _emit 0x0C
        // mov ecx, dword ptr [edx + 0xc]
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
        _emit 0x9F
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcomp dword ptr [edi + 0x90]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x04
        // jp 0x110b077
        _emit 0xB2
        _emit 0x01
        // mov dl, 1
        _emit 0xEB
        _emit 0x02
        // jmp 0x110b079
        _emit 0x32
        _emit 0xD2
        // xor dl, dl
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x16
        _emit 0x01
        // mov byte ptr [esp + 0x16], 1
        _emit 0xD8
        _emit 0x9F
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcomp dword ptr [edi + 0x94]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7B
        _emit 0x05
        // jnp 0x110b094
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x16
        _emit 0x00
        // mov byte ptr [esp + 0x16], 0
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // fld dword ptr [esp + 0x28]
        _emit 0xD8
        _emit 0x9F
        _emit 0x98
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcomp dword ptr [edi + 0x98]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x04
        // jp 0x110b0a9
        _emit 0xB1
        _emit 0x01
        // mov cl, 1
        _emit 0xEB
        _emit 0x02
        // jmp 0x110b0ab
        _emit 0x32
        _emit 0xC9
        // xor cl, cl
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // fld dword ptr [esp + 0x2c]
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x17
        _emit 0x01
        // mov byte ptr [esp + 0x17], 1
        _emit 0xD8
        _emit 0x9F
        _emit 0x9C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcomp dword ptr [edi + 0x9c]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7B
        _emit 0x05
        // jnp 0x110b0c6
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x17
        _emit 0x00
        // mov byte ptr [esp + 0x17], 0
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x8A
        _emit 0x44
        _emit 0x24
        _emit 0x16
        // mov al, byte ptr [esp + 0x16]
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
        _emit 0x17
        // mov eax, dword ptr [esp + 0x17]
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
        _emit 0xB9
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // jne 0x110afa5
        _emit 0x8B
        _emit 0x46
        _emit 0x38
        // mov eax, dword ptr [esi + 0x38]
        _emit 0xD9
        _emit 0x04
        _emit 0x86
        // fld dword ptr [esi + eax*4]
        _emit 0xD8
        _emit 0x4E
        _emit 0x30
        // fmul dword ptr [esi + 0x30]
        _emit 0xD8
        _emit 0x64
        _emit 0x87
        _emit 0x60
        // fsub dword ptr [edi + eax*4 + 0x60]
        _emit 0xD9
        _emit 0x5E
        _emit 0x34
        // fstp dword ptr [esi + 0x34]
        _emit 0xB8
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 2
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
        _emit 0x0C
        _emit 0x00
        // ret 0xc
        _emit 0x83
        _emit 0xFB
        _emit 0x06
        // cmp ebx, 6
        _emit 0x0F
        _emit 0x87
        _emit 0x02
        _emit 0xFE
        _emit 0xFF
        _emit 0xFF
        // ja 0x110af15
        _emit 0x8B
        _emit 0x55
        _emit 0x0C
        // mov edx, dword ptr [ebp + 0xc]
        _emit 0x8B
        _emit 0x75
        _emit 0x10
        // mov esi, dword ptr [ebp + 0x10]
        _emit 0x8D
        _emit 0x43
        _emit 0xFC
        // lea eax, [ebx - 4]
        _emit 0x50
        // push eax
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0x88
        _emit 0x1A
        // mov byte ptr [edx], bl
        call FUN_0110a2b0
        _emit 0x8B
        _emit 0x4E
        _emit 0x30
        // mov ecx, dword ptr [esi + 0x30]
        _emit 0x51
        // push ecx
        call FUN_011088b0
        _emit 0x8B
        _emit 0x55
        _emit 0x0C
        // mov edx, dword ptr [ebp + 0xc]
        _emit 0x8B
        _emit 0x75
        _emit 0x08
        // mov esi, dword ptr [ebp + 8]
        _emit 0x88
        _emit 0x42
        _emit 0x01
        // mov byte ptr [edx + 1], al
        _emit 0x0F
        _emit 0xB6
        _emit 0x4E
        _emit 0x21
        // movzx ecx, byte ptr [esi + 0x21]
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x49
        // dec ecx
        _emit 0x78
        _emit 0x14
        // js 0x110b157
        _emit 0x8A
        _emit 0x12
        // mov dl, byte ptr [edx]
        _emit 0x38
        _emit 0x14
        _emit 0x8E
        // cmp byte ptr [esi + ecx*4], dl
        _emit 0x75
        _emit 0x0A
        // jne 0x110b154
        _emit 0x38
        _emit 0x44
        _emit 0x8E
        _emit 0x01
        // cmp byte ptr [esi + ecx*4 + 1], al
        _emit 0x0F
        _emit 0x84
        _emit 0xF1
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0x110b245
        _emit 0x49
        // dec ecx
        _emit 0x79
        _emit 0xEE
        // jns 0x110b145
        _emit 0x8B
        _emit 0x75
        _emit 0x10
        // mov esi, dword ptr [ebp + 0x10]
        _emit 0x8D
        _emit 0x56
        _emit 0x10
        // lea edx, [esi + 0x10]
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x8B
        _emit 0x4A
        _emit 0x04
        // mov ecx, dword ptr [edx + 4]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // mov dword ptr [esp + 0x30], eax
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // fld dword ptr [esp + 0x30]
        _emit 0x8B
        _emit 0x42
        _emit 0x08
        // mov eax, dword ptr [edx + 8]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // mov dword ptr [esp + 0x34], ecx
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // fld dword ptr [esp + 0x34]
        _emit 0x8B
        _emit 0x4A
        _emit 0x0C
        // mov ecx, dword ptr [edx + 0xc]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // mov dword ptr [esp + 0x38], eax
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
        _emit 0x89
        _emit 0x4C
        _emit 0x24
        _emit 0x3C
        // mov dword ptr [esp + 0x3c], ecx
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x38
        // fstp dword ptr [esp + 0x38]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        // fld dword ptr [esp + 0x3c]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x3C
        // fstp dword ptr [esp + 0x3c]
        _emit 0xD8
        _emit 0x9F
        _emit 0xA0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcomp dword ptr [edi + 0xa0]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x04
        // jp 0x110b1ad
        _emit 0xB2
        _emit 0x01
        // mov dl, 1
        _emit 0xEB
        _emit 0x02
        // jmp 0x110b1af
        _emit 0x32
        _emit 0xD2
        // xor dl, dl
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // fld dword ptr [esp + 0x34]
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x17
        _emit 0x01
        // mov byte ptr [esp + 0x17], 1
        _emit 0xD8
        _emit 0x9F
        _emit 0xA4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcomp dword ptr [edi + 0xa4]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7B
        _emit 0x05
        // jnp 0x110b1ca
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x17
        _emit 0x00
        // mov byte ptr [esp + 0x17], 0
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // fld dword ptr [esp + 0x38]
        _emit 0xD8
        _emit 0x9F
        _emit 0xA8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcomp dword ptr [edi + 0xa8]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7A
        _emit 0x04
        // jp 0x110b1df
        _emit 0xB1
        _emit 0x01
        // mov cl, 1
        _emit 0xEB
        _emit 0x02
        // jmp 0x110b1e1
        _emit 0x32
        _emit 0xC9
        // xor cl, cl
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        // fld dword ptr [esp + 0x3c]
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x16
        _emit 0x01
        // mov byte ptr [esp + 0x16], 1
        _emit 0xD8
        _emit 0x9F
        _emit 0xAC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // fcomp dword ptr [edi + 0xac]
        _emit 0xDF
        _emit 0xE0
        // fnstsw ax
        _emit 0xF6
        _emit 0xC4
        _emit 0x05
        // test ah, 5
        _emit 0x7B
        _emit 0x05
        // jnp 0x110b1fc
        _emit 0xC6
        _emit 0x44
        _emit 0x24
        _emit 0x16
        _emit 0x00
        // mov byte ptr [esp + 0x16], 0
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x8A
        _emit 0x44
        _emit 0x24
        _emit 0x17
        // mov al, byte ptr [esp + 0x17]
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
        _emit 0x16
        // mov eax, dword ptr [esp + 0x16]
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
        _emit 0x83
        _emit 0xFD
        _emit 0xFF
        _emit 0xFF
        // jne 0x110afa5
        _emit 0x8B
        _emit 0x46
        _emit 0x38
        // mov eax, dword ptr [esi + 0x38]
        _emit 0xD9
        _emit 0x04
        _emit 0x86
        // fld dword ptr [esi + eax*4]
        _emit 0x83
        _emit 0xE8
        _emit 0x04
        // sub eax, 4
        _emit 0xD8
        _emit 0x4E
        _emit 0x30
        // fmul dword ptr [esi + 0x30]
        _emit 0xD9
        _emit 0xE0
        // fchs 
        _emit 0xD8
        _emit 0x64
        _emit 0x87
        _emit 0x70
        // fsub dword ptr [edi + eax*4 + 0x70]
        _emit 0xB8
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 2
        _emit 0xD9
        _emit 0x5E
        _emit 0x34
        // fstp dword ptr [esi + 0x34]
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
        _emit 0x0C
        _emit 0x00
        // ret 0xc
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0xB8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 1
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

// @ 0x0110b260  (313 bytes)
__declspec(naked) void FUN_0110b260()
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
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // sub esp, 0xc8
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x8D
        _emit 0x8C
        _emit 0x24
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [esp + 0x80]
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        call FUN_010ec500
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x66
        _emit 0x89
        _emit 0x5C
        _emit 0x24
        _emit 0x0E
        // mov word ptr [esp + 0xe], bx
        call FUN_010d93e0
        _emit 0x8D
        _emit 0x86
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea eax, [esi + 0x80]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_01109460
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x0F
        _emit 0x85
        _emit 0xDD
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0x110b37d
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
        _emit 0x10
        // lea edx, [esp + 0x10]
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x84
        _emit 0x24
        _emit 0x88
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea eax, [esp + 0x88]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_0110ad70
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x0F
        _emit 0x85
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0x110b38a
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x78
        // mov eax, dword ptr [esp + 0x78]
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
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
        _emit 0x10
        // lea edx, [esp + 0x10]
        _emit 0xB3
        _emit 0x01
        // mov bl, 1
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x52
        // push edx
        _emit 0x7F
        _emit 0x0C
        // jg 0x110b2e5
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // lea eax, [esp + 0x18]
        _emit 0x50
        // push eax
        call FUN_01108a10
        _emit 0xEB
        _emit 0x16
        // jmp 0x110b2fb
        _emit 0x83
        _emit 0xF8
        _emit 0x06
        // cmp eax, 6
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // lea eax, [esp + 0x18]
        _emit 0x50
        // push eax
        _emit 0x7F
        _emit 0x07
        // jg 0x110b2f6
        call FUN_01108b80
        _emit 0xEB
        _emit 0x05
        // jmp 0x110b2fb
        call FUN_01108c30
        _emit 0x80
        _emit 0x7C
        _emit 0x24
        _emit 0x0C
        _emit 0x02
        // cmp byte ptr [esp + 0xc], 2
        _emit 0x76
        _emit 0x3A
        // jbe 0x110b33c
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x2C
        // fld dword ptr [esp + 0x2c]
        _emit 0xD9
        _emit 0xE0
        // fchs 
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
        _emit 0x10
        // fadd dword ptr [esp + 0x10]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x10
        // fstp dword ptr [esp + 0x10]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // fld dword ptr [esp + 0x24]
        _emit 0xD8
        _emit 0xC9
        // fmul st(1)
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fadd dword ptr [esp + 0x14]
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
        _emit 0xC9
        // fmul st(1)
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fadd dword ptr [esp + 0x18]
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x18
        // fstp dword ptr [esp + 0x18]
        _emit 0xD8
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // fmul dword ptr [esp + 0x2c]
        _emit 0xD8
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fadd dword ptr [esp + 0x1c]
        _emit 0xEB
        _emit 0x04
        // jmp 0x110b340
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // fld dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x45
        _emit 0x0C
        // mov eax, dword ptr [ebp + 0xc]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // mov edx, dword ptr [esp + 0x24]
        _emit 0x89
        _emit 0x48
        _emit 0x10
        // mov dword ptr [eax + 0x10], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // mov ecx, dword ptr [esp + 0x28]
        _emit 0x89
        _emit 0x50
        _emit 0x14
        // mov dword ptr [eax + 0x14], edx
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x2C
        // mov edx, dword ptr [esp + 0x2c]
        _emit 0x89
        _emit 0x48
        _emit 0x18
        // mov dword ptr [eax + 0x18], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x89
        _emit 0x50
        _emit 0x1C
        // mov dword ptr [eax + 0x1c], edx
        _emit 0xD9
        _emit 0x58
        _emit 0x0C
        // fstp dword ptr [eax + 0xc]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x14
        // mov edx, dword ptr [esp + 0x14]
        _emit 0x89
        _emit 0x08
        // mov dword ptr [eax], ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x89
        _emit 0x50
        _emit 0x04
        // mov dword ptr [eax + 4], edx
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x2C
        // mov edx, dword ptr [esp + 0x2c]
        _emit 0x89
        _emit 0x48
        _emit 0x08
        // mov dword ptr [eax + 8], ecx
        _emit 0x89
        _emit 0x50
        _emit 0x1C
        // mov dword ptr [eax + 0x1c], edx
        _emit 0x8B
        _emit 0x45
        _emit 0x08
        // mov eax, dword ptr [ebp + 8]
        _emit 0x88
        _emit 0x18
        // mov byte ptr [eax], bl
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
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x8B
        _emit 0x45
        _emit 0x08
        // mov eax, dword ptr [ebp + 8]
        _emit 0x32
        _emit 0xC9
        // xor cl, cl
        _emit 0x5E
        // pop esi
        _emit 0x88
        _emit 0x08
        // mov byte ptr [eax], cl
        _emit 0x5B
        // pop ebx
        _emit 0x8B
        _emit 0xE5
        // mov esp, ebp
        _emit 0x5D
        // pop ebp
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}
