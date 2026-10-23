// Slice s00de81b0: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00401030();
extern "C" void FUN_0042f530();
extern "C" void FUN_0067c3b0();
extern "C" void FUN_0067cac0();
extern "C" void FUN_0067cad0();
extern "C" void FUN_0067cb10();
extern "C" void FUN_0067dcc0();
extern "C" void FUN_0067dd10();
extern "C" void FUN_0067dd50();
extern "C" void FUN_0067ddd0();
extern "C" void FUN_007c4010();
extern "C" void FUN_00804ed0();
extern "C" void FUN_00809db0();
extern "C" void FUN_0080dc50();
extern "C" void FUN_008105b0();
extern "C" void FUN_00811ad0();
extern "C" void FUN_008d3200();
extern "C" void FUN_00921580();
extern "C" void FUN_00b3d2a0();
extern "C" void FUN_00b3d340();
extern "C" void FUN_00b96600();
extern "C" void FUN_00bb7620();
extern "C" void FUN_00dd9190();
extern "C" void FUN_00dda3b0();
extern "C" void FUN_00ddc6d0();
extern "C" void FUN_00ddc8d0();
extern "C" void FUN_00dde5c0();
extern "C" void FUN_00de44f0();
extern "C" void FUN_00de4910();
extern "C" void FUN_00de5470();
extern "C" void FUN_00de6650();
extern "C" void FUN_00de7630();
extern "C" void FUN_00df5f40();
extern "C" void FUN_00df6db0();
extern "C" void FUN_00df9510();
extern "C" void FUN_00e012b0();

// @ 0x00de81b0  (1312 bytes)
__declspec(naked) void FUN_00de81b0()
{
    __asm {
        _emit 0x51
        // push ecx
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0x53
        // push ebx
        _emit 0x68
        _emit 0x5E
        _emit 0x81
        _emit 0x25
        _emit 0x2E
        // push 0x2e25815e
        _emit 0xC6
        _emit 0x87
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov byte ptr [edi + 0xc8], 0
        call FUN_0067cac0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_0067c3b0
        _emit 0x8B
        _emit 0xB7
        _emit 0x2C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov esi, dword ptr [edi + 0x12c]
        _emit 0x8D
        _emit 0xAF
        _emit 0x28
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea ebp, [edi + 0x128]
        _emit 0x3B
        _emit 0xF5
        // cmp esi, ebp
        _emit 0x74
        _emit 0x19
        // je 0xde81fb
        _emit 0x8B
        _emit 0x4E
        _emit 0x14
        // mov ecx, dword ptr [esi + 0x14]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x3C
        // mov edx, dword ptr [eax + 0x3c]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x56
        // push esi
        call FUN_00921580
        _emit 0x8B
        _emit 0xF0
        // mov esi, eax
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x3B
        _emit 0xF5
        // cmp esi, ebp
        _emit 0x75
        _emit 0xE7
        // jne 0xde81e2
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x8D
        _emit 0xB7
        _emit 0x44
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea esi, [edi + 0x144]
        _emit 0x68
        _emit 0xFF
        _emit 0xA5
        _emit 0x15
        _emit 0x06
        // push 0x615a5ff
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_008105b0
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x74
        _emit 0x0C
        // je 0xde821f
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x7C
        // mov eax, dword ptr [edx + 0x7c]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00811ad0
        _emit 0x83
        _emit 0xBF
        _emit 0x08
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x03
        // cmp dword ptr [edi + 0x108], 3
        _emit 0x75
        _emit 0x11
        // jne 0xde8242
        _emit 0xB8
        _emit 0x05
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 5
        _emit 0x89
        _emit 0x87
        _emit 0x08
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x108], eax
        _emit 0x89
        _emit 0x87
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x10c], eax
        _emit 0x8B
        _emit 0x8F
        _emit 0x84
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x184]
        _emit 0x88
        _emit 0x9F
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov byte ptr [edi + 0x100], bl
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x0C
        // mov eax, dword ptr [edx + 0xc]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x8F
        _emit 0x84
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x184]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x08
        // je 0xde8267
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x02
        // mov eax, dword ptr [edx]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x8F
        _emit 0xB0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x1b0]
        _emit 0xC6
        _emit 0x87
        _emit 0x03
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x01
        // mov byte ptr [edi + 0x103], 1
        _emit 0x89
        _emit 0x9F
        _emit 0x84
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x184], ebx
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x1F
        // je 0xde829d
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x0C
        // mov eax, dword ptr [edx + 0xc]
        _emit 0x53
        // push ebx
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x8F
        _emit 0xB0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x1b0]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x0D
        // je 0xde829d
        _emit 0x89
        _emit 0x9F
        _emit 0xB0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x1b0], ebx
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00df5f40
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x5C
        // mov eax, dword ptr [edx + 0x5c]
        _emit 0x53
        // push ebx
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067dd50
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x50
        // mov eax, dword ptr [edx + 0x50]
        _emit 0x6A
        _emit 0x0D
        // push 0xd
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067ddd0
        _emit 0x8B
        _emit 0xAF
        _emit 0x5C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ebp, dword ptr [edi + 0x15c]
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0x75
        _emit 0x00
        // mov esi, dword ptr [ebp]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x1C
        // mov eax, dword ptr [edx + 0x1c]
        _emit 0x83
        _emit 0xC6
        _emit 0x1C
        // add esi, 0x1c
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x16
        // mov edx, dword ptr [esi]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x8F
        _emit 0x60
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x160]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x0D
        // je 0xde82f4
        _emit 0x89
        _emit 0x9F
        _emit 0x60
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x160], ebx
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x8F
        _emit 0xA0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x1a0]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x0D
        // je 0xde830b
        _emit 0x89
        _emit 0x9F
        _emit 0xA0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x1a0], ebx
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x8F
        _emit 0x64
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x164]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x0D
        // je 0xde8322
        _emit 0x89
        _emit 0x9F
        _emit 0x64
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x164], ebx
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x8F
        _emit 0x68
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x168]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x0D
        // je 0xde8339
        _emit 0x89
        _emit 0x9F
        _emit 0x68
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x168], ebx
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x8F
        _emit 0x6C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x16c]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x0D
        // je 0xde8350
        _emit 0x89
        _emit 0x9F
        _emit 0x6C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x16c], ebx
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x8F
        _emit 0x70
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x170]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x0D
        // je 0xde8367
        _emit 0x89
        _emit 0x9F
        _emit 0x70
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x170], ebx
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x8F
        _emit 0xA4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x1a4]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x1A
        // je 0xde838b
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x10
        // mov edx, dword ptr [eax + 0x10]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x0F
        // je 0xde838b
        _emit 0x8B
        _emit 0x8F
        _emit 0xA4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x1a4]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x8F
        _emit 0xA4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x1a4]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x0D
        // je 0xde83a2
        _emit 0x89
        _emit 0x9F
        _emit 0xA4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x1a4], ebx
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x8F
        _emit 0xA8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x1a8]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x1A
        // je 0xde83c6
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x10
        // mov edx, dword ptr [eax + 0x10]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x0F
        // je 0xde83c6
        _emit 0x8B
        _emit 0x8F
        _emit 0xA8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x1a8]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x8F
        _emit 0xA8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x1a8]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x0D
        // je 0xde83dd
        _emit 0x89
        _emit 0x9F
        _emit 0xA8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x1a8], ebx
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x8F
        _emit 0x9C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x19c]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x1A
        // je 0xde8401
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x10
        // mov edx, dword ptr [eax + 0x10]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x0F
        // je 0xde8401
        _emit 0x8B
        _emit 0x8F
        _emit 0x9C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x19c]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8B
        _emit 0x8F
        _emit 0x9C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x19c]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x0D
        // je 0xde8418
        _emit 0x89
        _emit 0x9F
        _emit 0x9C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x19c], ebx
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x83
        _emit 0xBF
        _emit 0x08
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x04
        // cmp dword ptr [edi + 0x108], 4
        _emit 0x0F
        _emit 0x84
        _emit 0x95
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xde84ba
        _emit 0x8B
        _emit 0x87
        _emit 0xFC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edi + 0xfc]
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x74
        _emit 0x13
        // je 0xde8442
        _emit 0x8B
        _emit 0x80
        _emit 0xB8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [eax + 0xb8]
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x74
        _emit 0x09
        // je 0xde8442
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00df6db0
        _emit 0x8B
        _emit 0xB7
        _emit 0xD8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov esi, dword ptr [edi + 0x1d8]
        _emit 0x3B
        _emit 0xB7
        _emit 0xDC
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // cmp esi, dword ptr [edi + 0x1dc]
        _emit 0x74
        _emit 0x16
        // je 0xde8466
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x83
        _emit 0xC6
        _emit 0x04
        // add esi, 4
        _emit 0x3B
        _emit 0xB7
        _emit 0xDC
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // cmp esi, dword ptr [edi + 0x1dc]
        _emit 0x75
        _emit 0xEA
        // jne 0xde8450
        _emit 0x8B
        _emit 0x87
        _emit 0xD8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edi + 0x1d8]
        _emit 0x8B
        _emit 0xB7
        _emit 0xDC
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov esi, dword ptr [edi + 0x1dc]
        _emit 0x50
        // push eax
        _emit 0x56
        // push esi
        _emit 0x56
        // push esi
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov dword ptr [esp + 0x1c], eax
        call FUN_0042f530
        _emit 0x8B
        _emit 0x9F
        _emit 0xDC
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ebx, dword ptr [edi + 0x1dc]
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x8B
        _emit 0xE8
        // mov ebp, eax
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x73
        _emit 0x18
        // jae 0xde84a5
        _emit 0x8D
        _emit 0x49
        _emit 0x00
        // lea ecx, [ecx]
        _emit 0x8B
        _emit 0x4D
        _emit 0x00
        // mov ecx, dword ptr [ebp]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x07
        // je 0xde849e
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x04
        // mov edx, dword ptr [eax + 4]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x83
        _emit 0xC5
        _emit 0x04
        // add ebp, 4
        _emit 0x3B
        _emit 0xEB
        // cmp ebp, ebx
        _emit 0x72
        _emit 0xEB
        // jb 0xde8490
        _emit 0x2B
        _emit 0x74
        _emit 0x24
        _emit 0x10
        // sub esi, dword ptr [esp + 0x10]
        _emit 0xC1
        _emit 0xFE
        _emit 0x02
        // sar esi, 2
        _emit 0xF7
        _emit 0xDE
        // neg esi
        _emit 0x03
        _emit 0xF6
        // add esi, esi
        _emit 0x03
        _emit 0xF6
        // add esi, esi
        _emit 0x01
        _emit 0xB7
        _emit 0xDC
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // add dword ptr [edi + 0x1dc], esi
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0xA1
        _emit 0x44
        _emit 0x13
        _emit 0x6A
        _emit 0x01
        // mov eax, dword ptr [0x16a1344]
        _emit 0x80
        _emit 0xB8
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [eax + 0x104], 0
        _emit 0x75
        _emit 0x09
        // jne 0xde84d1
        _emit 0x83
        _emit 0xB8
        _emit 0x08
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x04
        // cmp dword ptr [eax + 0x108], 4
        _emit 0x74
        _emit 0x2B
        // je 0xde84fc
        call FUN_00df5f40
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x60
        // mov eax, dword ptr [edx + 0x60]
        _emit 0x53
        // push ebx
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00df5f40
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x5C
        // mov eax, dword ptr [edx + 0x5c]
        _emit 0x53
        // push ebx
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00df5f40
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00df9510
        _emit 0xC6
        _emit 0x87
        _emit 0x40
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov byte ptr [edi + 0x140], 0
        _emit 0x8D
        _emit 0x77
        _emit 0x08
        // lea esi, [edi + 8]
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0xF1
        _emit 0xD8
        _emit 0xFF
        _emit 0xFF
        // push 0xffffd8f1
        _emit 0x68
        _emit 0x14
        _emit 0x0E
        _emit 0x36
        _emit 0x04
        // push 0x4360e14
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0xF1
        _emit 0xD8
        _emit 0xFF
        _emit 0xFF
        // push 0xffffd8f1
        _emit 0x68
        _emit 0x7F
        _emit 0xBD
        _emit 0x6B
        _emit 0x05
        // push 0x56bbd7f
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0xF1
        _emit 0xD8
        _emit 0xFF
        _emit 0xFF
        // push 0xffffd8f1
        _emit 0x68
        _emit 0x2E
        _emit 0xB1
        _emit 0x4D
        _emit 0x04
        // push 0x44db12e
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0xF1
        _emit 0xD8
        _emit 0xFF
        _emit 0xFF
        // push 0xffffd8f1
        _emit 0x68
        _emit 0x78
        _emit 0x63
        _emit 0xBD
        _emit 0x05
        // push 0x5bd6378
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0xF1
        _emit 0xD8
        _emit 0xFF
        _emit 0xFF
        // push 0xffffd8f1
        _emit 0x68
        _emit 0xC7
        _emit 0x52
        _emit 0xDD
        _emit 0x05
        // push 0x5dd52c7
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0xF1
        _emit 0xD8
        _emit 0xFF
        _emit 0xFF
        // push 0xffffd8f1
        _emit 0x68
        _emit 0xDC
        _emit 0x3F
        _emit 0x20
        _emit 0x06
        // push 0x6203fdc
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0xF1
        _emit 0xD8
        _emit 0xFF
        _emit 0xFF
        // push 0xffffd8f1
        _emit 0x68
        _emit 0x5F
        _emit 0x9B
        _emit 0x51
        _emit 0x04
        // push 0x4519b5f
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0xF1
        _emit 0xD8
        _emit 0xFF
        _emit 0xFF
        // push 0xffffd8f1
        _emit 0x68
        _emit 0x7D
        _emit 0xD2
        _emit 0x25
        _emit 0x06
        // push 0x625d27d
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0xF1
        _emit 0xD8
        _emit 0xFF
        _emit 0xFF
        // push 0xffffd8f1
        _emit 0x68
        _emit 0xD6
        _emit 0x5B
        _emit 0xC7
        _emit 0x67
        // push 0x67c75bd6
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0xF1
        _emit 0xD8
        _emit 0xFF
        _emit 0xFF
        // push 0xffffd8f1
        _emit 0x68
        _emit 0xAD
        _emit 0x97
        _emit 0x42
        _emit 0x63
        // push 0x634297ad
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0xF1
        _emit 0xD8
        _emit 0xFF
        _emit 0xFF
        // push 0xffffd8f1
        _emit 0x68
        _emit 0x8C
        _emit 0x9C
        _emit 0x5A
        _emit 0x27
        // push 0x275a9c8c
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0xF1
        _emit 0xD8
        _emit 0xFF
        _emit 0xFF
        // push 0xffffd8f1
        _emit 0x68
        _emit 0xDE
        _emit 0x17
        _emit 0xA1
        _emit 0xED
        // push 0xeda117de
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067dcc0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x68
        _emit 0xF1
        _emit 0xD8
        _emit 0xFF
        _emit 0xFF
        // push 0xffffd8f1
        _emit 0x68
        _emit 0x4C
        _emit 0x5C
        _emit 0x08
        _emit 0x08
        // push 0x8085c4c
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x2C
        // mov eax, dword ptr [edx + 0x2c]
        _emit 0x56
        // push esi
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067ddd0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x82
        _emit 0x98
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edx + 0x98]
        _emit 0x6A
        _emit 0x0A
        // push 0xa
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x8F
        _emit 0x5C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x15c]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x34
        // mov eax, dword ptr [edx + 0x34]
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_0067ddd0
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x50
        // mov eax, dword ptr [edx + 0x50]
        _emit 0x68
        _emit 0x76
        _emit 0xA9
        _emit 0xDD
        _emit 0x02
        // push 0x2dda976
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x8F
        _emit 0x5C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0x15c]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x0D
        // je 0xde8696
        _emit 0x89
        _emit 0x9F
        _emit 0x5C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x15c], ebx
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x04
        // mov eax, dword ptr [edx + 4]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0xC6
        _emit 0x87
        _emit 0xC9
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov byte ptr [edi + 0xc9], 0
        call FUN_0067cb10
        _emit 0x3B
        _emit 0xC3
        // cmp eax, ebx
        _emit 0x74
        _emit 0x0B
        // je 0xde86b1
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x40
        // mov eax, dword ptr [edx + 0x40]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x8F
        _emit 0xCC
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [edi + 0xcc]
        _emit 0x51
        // push ecx
        call FUN_0067cad0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_0080dc50
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
        _emit 0x04
        // add esp, 4
        jmp FUN_00ddc8d0
    }
}

// @ 0x00de86d0  (132 bytes)
__declspec(naked) void FUN_00de86d0()
{
    __asm {
        _emit 0x80
        _emit 0x7C
        _emit 0x24
        _emit 0x08
        _emit 0x00
        // cmp byte ptr [esp + 8], 0
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x74
        _emit 0x6C
        // je 0xde8746
        _emit 0x8B
        _emit 0x86
        _emit 0x08
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x108]
        _emit 0x8D
        _emit 0x96
        _emit 0x08
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea edx, [esi + 0x108]
        _emit 0x83
        _emit 0xF8
        _emit 0x01
        // cmp eax, 1
        _emit 0x74
        _emit 0x0E
        // je 0xde86f9
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x0A
        // je 0xde86f9
        _emit 0x83
        _emit 0xF8
        _emit 0x08
        // cmp eax, 8
        _emit 0x74
        _emit 0x05
        // je 0xde86f9
        _emit 0x83
        _emit 0xF8
        _emit 0x09
        // cmp eax, 9
        _emit 0x75
        _emit 0x06
        // jne 0xde86ff
        _emit 0xC7
        _emit 0x02
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edx], 2
        _emit 0x8B
        _emit 0x86
        _emit 0x14
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x114]
        _emit 0x3B
        _emit 0x86
        _emit 0x18
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // cmp eax, dword ptr [esi + 0x118]
        _emit 0x8D
        _emit 0x8E
        _emit 0x10
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea ecx, [esi + 0x110]
        _emit 0x73
        _emit 0x1E
        // jae 0xde8731
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x78
        _emit 0x04
        // lea edi, [eax + 4]
        _emit 0x89
        _emit 0x79
        _emit 0x04
        // mov dword ptr [ecx + 4], edi
        _emit 0x5F
        // pop edi
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x04
        // je 0xde8723
        _emit 0x8B
        _emit 0x0A
        // mov ecx, dword ptr [edx]
        _emit 0x89
        _emit 0x08
        // mov dword ptr [eax], ecx
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // mov edx, dword ptr [esp + 8]
        _emit 0x89
        _emit 0x96
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x10c], edx
        _emit 0x5E
        // pop esi
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x52
        // push edx
        _emit 0x50
        // push eax
        call FUN_00b96600
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0x89
        _emit 0x86
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x10c], eax
        _emit 0x5E
        // pop esi
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x08
        // mov ecx, dword ptr [esp + 8]
        _emit 0x89
        _emit 0x8E
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x10c], ecx
        _emit 0x5E
        // pop esi
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}

// @ 0x00de8760  (879 bytes)
__declspec(naked) void FUN_00de8760()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x20
        // sub esp, 0x20
        _emit 0x53
        // push ebx
        _emit 0x56
        // push esi
        _emit 0x33
        _emit 0xDB
        // xor ebx, ebx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x38
        _emit 0x1D
        _emit 0x48
        _emit 0x13
        _emit 0x6A
        _emit 0x01
        // cmp byte ptr [0x16a1348], bl
        _emit 0x74
        _emit 0x21
        // je 0xde8793
        _emit 0x53
        // push ebx
        call FUN_00dd9190
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00dda3b0
        _emit 0x6A
        _emit 0x01
        // push 1
        call FUN_00dd9190
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00dda3b0
        _emit 0x88
        _emit 0x1D
        _emit 0x48
        _emit 0x13
        _emit 0x6A
        _emit 0x01
        // mov byte ptr [0x16a1348], bl
        _emit 0x0F
        _emit 0xB6
        _emit 0x05
        _emit 0xA8
        _emit 0x0F
        _emit 0x6A
        _emit 0x01
        // movzx eax, byte ptr [0x16a0fa8]
        _emit 0x50
        // push eax
        call FUN_00dd9190
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00dda3b0
        _emit 0x38
        _emit 0x9E
        _emit 0xF6
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [esi + 0x1f6], bl
        _emit 0x74
        _emit 0x12
        // je 0xde87c1
        call FUN_00b3d2a0
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00bb7620
        _emit 0x88
        _emit 0x9E
        _emit 0xF6
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esi + 0x1f6], bl
        _emit 0x8B
        _emit 0x4E
        _emit 0x38
        // mov ecx, dword ptr [esi + 0x38]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x0F
        // je 0xde87d7
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x30
        // fld dword ptr [esp + 0x30]
        _emit 0x8B
        _emit 0x42
        _emit 0x14
        // mov eax, dword ptr [edx + 0x14]
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // fld dword ptr [esp + 0x34]
        _emit 0xD8
        _emit 0x0D
        _emit 0xB4
        _emit 0xC5
        _emit 0x3E
        _emit 0x01
        // fmul dword ptr [0x13ec5b4]
        _emit 0xD9
        _emit 0x7C
        _emit 0x24
        _emit 0x0C
        // fnstcw word ptr [esp + 0xc]
        _emit 0x0F
        _emit 0xB7
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // movzx eax, word ptr [esp + 0xc]
        _emit 0x0D
        _emit 0x00
        _emit 0x0C
        _emit 0x00
        _emit 0x00
        // or eax, 0xc00
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // mov dword ptr [esp + 0x10], eax
        _emit 0xD9
        _emit 0x6C
        _emit 0x24
        _emit 0x10
        // fldcw word ptr [esp + 0x10]
        _emit 0xDF
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        // fistp qword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x51
        // push ecx
        _emit 0xD9
        _emit 0x6C
        _emit 0x24
        _emit 0x10
        // fldcw word ptr [esp + 0x10]
        call FUN_00dd9190
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00ddc6d0
        _emit 0x38
        _emit 0x9E
        _emit 0x03
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // cmp byte ptr [esi + 0x103], bl
        _emit 0x0F
        _emit 0x84
        _emit 0xC3
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xde88df
        _emit 0x88
        _emit 0x9E
        _emit 0x03
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov byte ptr [esi + 0x103], bl
        call FUN_0067dd10
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x1C
        // lea edx, [esp + 0x1c]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0x10
        // mov edx, dword ptr [eax]
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        _emit 0x8B
        _emit 0x42
        _emit 0x58
        // mov eax, dword ptr [edx + 0x58]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_007c4010
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x24
        // mov eax, dword ptr [esp + 0x24]
        _emit 0x2B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // sub eax, dword ptr [esp + 0x1c]
        _emit 0x8B
        _emit 0x8E
        _emit 0x84
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x184]
        _emit 0x99
        // cdq 
        _emit 0x2B
        _emit 0xC2
        // sub eax, edx
        _emit 0xD1
        _emit 0xF8
        // sar eax, 1
        _emit 0xF3
        _emit 0x0F
        _emit 0x2A
        _emit 0xC0
        // cvtsi2ss xmm0, eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x28
        // mov eax, dword ptr [esp + 0x28]
        _emit 0x2B
        _emit 0x44
        _emit 0x24
        _emit 0x20
        // sub eax, dword ptr [esp + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // movss dword ptr [esp + 0xc], xmm0
        _emit 0x99
        // cdq 
        _emit 0x2B
        _emit 0xC2
        // sub eax, edx
        _emit 0xD1
        _emit 0xF8
        // sar eax, 1
        _emit 0xF3
        _emit 0x0F
        _emit 0x2A
        _emit 0xC0
        // cvtsi2ss xmm0, eax
        _emit 0x68
        _emit 0x38
        _emit 0x50
        _emit 0x68
        _emit 0x03
        // push 0x3685038
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm0
        call FUN_00e012b0
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x74
        _emit 0x5F
        // je 0xde88df
        _emit 0x8B
        _emit 0x17
        // mov edx, dword ptr [edi]
        _emit 0x8B
        _emit 0x42
        _emit 0x38
        // mov eax, dword ptr [edx + 0x38]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x50
        _emit 0x04
        // movss xmm2, dword ptr [eax + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0x0C
        // movss xmm1, dword ptr [eax + 0xc]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x25
        _emit 0x64
        _emit 0x10
        _emit 0x47
        _emit 0x01
        // movss xmm4, dword ptr [0x1471064]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x18
        // movss xmm3, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x08
        // movss xmm0, dword ptr [eax + 8]
        _emit 0x8B
        _emit 0x17
        // mov edx, dword ptr [edi]
        _emit 0x8B
        _emit 0x42
        _emit 0x64
        // mov eax, dword ptr [edx + 0x64]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xCA
        // subss xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // movss xmm2, dword ptr [esp + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCC
        // mulss xmm1, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xD1
        // subss xmm2, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // movss xmm1, dword ptr [esp + 0xc]
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xC3
        // subss xmm0, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC4
        // mulss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x54
        _emit 0x24
        _emit 0x04
        // movss dword ptr [esp + 4], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xC8
        // subss xmm1, xmm0
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x0C
        _emit 0x24
        // movss dword ptr [esp], xmm1
        _emit 0xFF
        _emit 0xD0
        // call eax
        call FUN_00401030
        _emit 0x8B
        _emit 0x8E
        _emit 0x5C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x15c]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x38
        _emit 0x58
        _emit 0x1C
        // cmp byte ptr [eax + 0x1c], bl
        _emit 0x8B
        _emit 0x42
        _emit 0x0C
        // mov eax, dword ptr [edx + 0xc]
        _emit 0x74
        _emit 0x04
        // je 0xde88f8
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0xEB
        _emit 0x01
        // jmp 0xde88f9
        _emit 0x53
        // push ebx
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // fld dword ptr [esp + 0x34]
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x04
        // fstp dword ptr [esp + 4]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x38
        // fld dword ptr [esp + 0x38]
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        call FUN_00de6650
        _emit 0x8B
        _emit 0x8E
        _emit 0x98
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x198]
        call FUN_00dde5c0
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x34
        // fstp dword ptr [esp + 0x34]
        _emit 0x68
        _emit 0xFF
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // push 0x3ff
        _emit 0x6A
        _emit 0x11
        // push 0x11
        call FUN_008d3200
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x44
        // je 0xde897a
        _emit 0x68
        _emit 0xFF
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // push 0x3ff
        _emit 0x6A
        _emit 0x10
        // push 0x10
        call FUN_008d3200
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x74
        _emit 0x31
        // je 0xde897a
        _emit 0x8B
        _emit 0x8E
        _emit 0x70
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x170]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x5E
        // je 0xde89b1
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // fld dword ptr [esp + 0x34]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x05
        _emit 0x68
        _emit 0x0F
        _emit 0x6A
        _emit 0x01
        // fld dword ptr [0x16a0f68]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xDF
        _emit 0xF1
        // fcompi st(1)
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x76
        _emit 0x4A
        // jbe 0xde89b1
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x10
        // mov eax, dword ptr [edx + 0x10]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x75
        _emit 0x3F
        // jne 0xde89b1
        _emit 0x8B
        _emit 0x8E
        _emit 0x70
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x170]
        _emit 0xEB
        _emit 0x2F
        // jmp 0xde89a9
        _emit 0x8B
        _emit 0x8E
        _emit 0x6C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x16c]
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x2D
        // je 0xde89b1
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // fld dword ptr [esp + 0x34]
        _emit 0xD9
        _emit 0xE1
        // fabs 
        _emit 0xD9
        _emit 0x05
        _emit 0x68
        _emit 0x0F
        _emit 0x6A
        _emit 0x01
        // fld dword ptr [0x16a0f68]
        _emit 0xD9
        _emit 0xC9
        // fxch st(1)
        _emit 0xDF
        _emit 0xF1
        // fcompi st(1)
        _emit 0xDD
        _emit 0xD8
        // fstp st(0)
        _emit 0x76
        _emit 0x19
        // jbe 0xde89b1
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x10
        // mov eax, dword ptr [edx + 0x10]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x84
        _emit 0xC0
        // test al, al
        _emit 0x75
        _emit 0x0E
        // jne 0xde89b1
        _emit 0x8B
        _emit 0x8E
        _emit 0x6C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x16c]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x42
        _emit 0x08
        // mov eax, dword ptr [edx + 8]
        _emit 0x53
        // push ebx
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x8B
        _emit 0x8E
        _emit 0x08
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x108]
        _emit 0x8B
        _emit 0x86
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x10c]
        _emit 0x8D
        _emit 0xBE
        _emit 0x08
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea edi, [esi + 0x108]
        _emit 0x3B
        _emit 0xC8
        // cmp ecx, eax
        _emit 0x74
        _emit 0x76
        // je 0xde8a3d
        _emit 0x2B
        _emit 0xCB
        // sub ecx, ebx
        _emit 0x74
        _emit 0x09
        // je 0xde89d4
        _emit 0x83
        _emit 0xE9
        _emit 0x01
        // sub ecx, 1
        _emit 0x74
        _emit 0x27
        // je 0xde89f7
        _emit 0x89
        _emit 0x07
        // mov dword ptr [edi], eax
        _emit 0xEB
        _emit 0x69
        // jmp 0xde8a3d
        _emit 0x83
        _emit 0xBE
        _emit 0xEC
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x06
        // cmp dword ptr [esi + 0x1ec], 6
        _emit 0x75
        _emit 0x60
        // jne 0xde8a3d
        call FUN_00b3d340
        _emit 0x38
        _emit 0x58
        _emit 0x47
        // cmp byte ptr [eax + 0x47], bl
        _emit 0x75
        _emit 0x1D
        // jne 0xde8a04
        _emit 0x38
        _emit 0x1D
        _emit 0x78
        _emit 0x0E
        _emit 0x6A
        _emit 0x01
        // cmp byte ptr [0x16a0e78], bl
        _emit 0x75
        _emit 0x15
        // jne 0xde8a04
        _emit 0x8B
        _emit 0x86
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x10c]
        _emit 0x89
        _emit 0x07
        // mov dword ptr [edi], eax
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x89
        _emit 0x07
        // mov dword ptr [edi], eax
        call FUN_00de5470
        _emit 0xEB
        _emit 0x39
        // jmp 0xde8a3d
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // lea ecx, [esp + 0x10]
        _emit 0x8D
        _emit 0x46
        _emit 0x0C
        // lea eax, [esi + 0xc]
        _emit 0x51
        // push ecx
        _emit 0x50
        // push eax
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x84
        _emit 0xE5
        _emit 0xA5
        _emit 0x7F
        // mov dword ptr [esp + 0x18], 0x7fa5e584
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        _emit 0x04
        _emit 0xB1
        _emit 0xB1
        _emit 0x00
        // mov dword ptr [esp + 0x1c], 0xb1b104
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x20
        _emit 0xE8
        _emit 0xFD
        _emit 0xF6
        _emit 0xF5
        // mov dword ptr [esp + 0x20], 0xf5f6fde8
        call FUN_00809db0
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x89
        _emit 0x9E
        _emit 0x0C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x10c], ebx
        _emit 0x89
        _emit 0x1F
        // mov dword ptr [edi], ebx
        call FUN_00b3d340
        _emit 0x88
        _emit 0x58
        _emit 0x47
        // mov byte ptr [eax + 0x47], bl
        _emit 0x55
        // push ebp
        _emit 0x8D
        _emit 0xAE
        _emit 0x24
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea ebp, [esi + 0x124]
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        call FUN_00de7630
        _emit 0x8B
        _emit 0x38
        // mov edi, dword ptr [eax]
        _emit 0x8B
        _emit 0x86
        _emit 0xEC
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x1ec]
        _emit 0x48
        // dec eax
        _emit 0x83
        _emit 0xF8
        _emit 0x04
        // cmp eax, 4
        _emit 0x77
        _emit 0x16
        // ja 0xde8a70
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x38
        // lea edx, [esp + 0x38]
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCD
        // mov ecx, ebp
        _emit 0xC7
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esp + 0x3c], 1
        call FUN_00de7630
        _emit 0x8B
        _emit 0x38
        // mov edi, dword ptr [eax]
        _emit 0x8B
        _emit 0x4E
        _emit 0x38
        // mov ecx, dword ptr [esi + 0x38]
        _emit 0x5D
        // pop ebp
        _emit 0x3B
        _emit 0xF9
        // cmp edi, ecx
        _emit 0x74
        _emit 0x4E
        // je 0xde8ac6
        _emit 0x3B
        _emit 0xCB
        // cmp ecx, ebx
        _emit 0x74
        _emit 0x07
        // je 0xde8a83
        _emit 0x8B
        _emit 0x01
        // mov eax, dword ptr [ecx]
        _emit 0x8B
        _emit 0x50
        _emit 0x10
        // mov edx, dword ptr [eax + 0x10]
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x89
        _emit 0x7E
        _emit 0x38
        // mov dword ptr [esi + 0x38], edi
        _emit 0x3B
        _emit 0xFB
        // cmp edi, ebx
        _emit 0x74
        _emit 0x09
        // je 0xde8a93
        _emit 0x8B
        _emit 0x07
        // mov eax, dword ptr [edi]
        _emit 0x8B
        _emit 0x50
        _emit 0x0C
        // mov edx, dword ptr [eax + 0xc]
        _emit 0x8B
        _emit 0xCF
        // mov ecx, edi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x34
        // lea eax, [esp + 0x34]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x34
        // lea ecx, [esp + 0x34]
        _emit 0x51
        // push ecx
        call FUN_00804ed0
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        // fld dword ptr [esp + 0x3c]
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x53
        // push ebx
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x04
        // fstp dword ptr [esp + 4]
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x3C
        // fld dword ptr [esp + 0x3c]
        _emit 0xD9
        _emit 0x1C
        _emit 0x24
        // fstp dword ptr [esp]
        call FUN_00de44f0
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00de4910
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x20
        // add esp, 0x20
        _emit 0xC2
        _emit 0x08
        _emit 0x00
        // ret 8
    }
}
