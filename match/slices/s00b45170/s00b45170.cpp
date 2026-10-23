// Slice s00b45170: Spore engine routines (naked transcription).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00645ed0();
extern "C" void FUN_0067dcc0();
extern "C" void FUN_00693230();
extern "C" void FUN_007611f0();
extern "C" void FUN_00921440();
extern "C" void FUN_00b3dec0();
extern "C" void FUN_00b3e860();
extern "C" void FUN_00b3e980();
extern "C" void FUN_00b3f260();
extern "C" void FUN_00b41900();
extern "C" void FUN_00b41dc0();
extern "C" void FUN_00b42760();
extern "C" void FUN_00b4d720();
extern "C" void FUN_00b54340();
extern "C" void FUN_00b544c0();
extern "C" void FUN_00b544f0();
extern "C" void FUN_00b54520();
extern "C" void FUN_00b5a390();
extern "C" void FUN_00c2e4e0();
extern "C" void FUN_00c446d0();
extern "C" void FUN_00ef7c00();
extern "C" void FUN_00f47380();
extern "C" void FUN_00f473a0();

// @ 0x00b45170  (116 bytes)
__declspec(naked) void FUN_00b45170()
{
    __asm {
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0x8B
        _emit 0x87
        _emit 0x90
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edi + 0x90]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x09
        // je 0xb45186
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x47
        _emit 0x78
        // mov eax, dword ptr [edi + 0x78]
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x09
        // je 0xb45196
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8B
        _emit 0x47
        _emit 0x60
        // mov eax, dword ptr [edi + 0x60]
        _emit 0x8B
        _emit 0x4F
        _emit 0x5C
        // mov ecx, dword ptr [edi + 0x5c]
        _emit 0x56
        // push esi
        _emit 0x8D
        _emit 0x77
        _emit 0x58
        // lea esi, [edi + 0x58]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00693230
        _emit 0x83
        _emit 0x7E
        _emit 0x08
        _emit 0x01
        // cmp dword ptr [esi + 8], 1
        _emit 0xC7
        _emit 0x46
        _emit 0x0C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xc], 0
        _emit 0x76
        _emit 0x0C
        // jbe 0xb451c2
        _emit 0x8B
        _emit 0x56
        _emit 0x04
        // mov edx, dword ptr [esi + 4]
        _emit 0x52
        // push edx
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8D
        _emit 0x4F
        _emit 0x3C
        // lea ecx, [edi + 0x3c]
        call FUN_00c2e4e0
        _emit 0x8B
        _emit 0x47
        _emit 0x24
        // mov eax, dword ptr [edi + 0x24]
        _emit 0x5E
        // pop esi
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x09
        // je 0xb451db
        _emit 0x50
        // push eax
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x8D
        _emit 0x4F
        _emit 0x08
        // lea ecx, [edi + 8]
        _emit 0x5F
        // pop edi
        jmp FUN_00c2e4e0
    }
}

// @ 0x00b451f0  (178 bytes)
__declspec(naked) void FUN_00b451f0()
{
    __asm {
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        call FUN_0067dcc0
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x0F
        _emit 0x84
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xb45281
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
        _emit 0x82
        _emit 0xC5
        _emit 0x82
        _emit 0x01
        // push 0x182c582
        _emit 0x8D
        _emit 0x77
        _emit 0xFC
        // lea esi, [edi - 4]
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
        _emit 0x9E
        _emit 0x21
        _emit 0xA0
        _emit 0x01
        // push 0x1a0219e
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
        _emit 0xB7
        _emit 0x30
        _emit 0x56
        _emit 0x02
        // push 0x25630b7
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
        _emit 0xB9
        _emit 0x18
        _emit 0x10
        _emit 0x03
        // push 0x31018b9
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
        _emit 0xEF
        _emit 0x2D
        _emit 0xF6
        _emit 0x00
        // push 0xf62def
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
        call FUN_00b4d720
        _emit 0x8B
        _emit 0x4F
        _emit 0x44
        // mov ecx, dword ptr [edi + 0x44]
        _emit 0x8B
        _emit 0x57
        _emit 0x40
        // mov edx, dword ptr [edi + 0x40]
        _emit 0x8D
        _emit 0x77
        _emit 0x3C
        // lea esi, [edi + 0x3c]
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_007611f0
        _emit 0x5F
        // pop edi
        _emit 0xC7
        _emit 0x46
        _emit 0x0C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xc], 0
        _emit 0x5E
        // pop esi
        _emit 0xC3
        // ret 
    }
}

// @ 0x00b452b0  (51 bytes)
__declspec(naked) void FUN_00b452b0()
{
    __asm {
        _emit 0x80
        _emit 0x3D
        _emit 0x75
        _emit 0xEB
        _emit 0x67
        _emit 0x01
        _emit 0x00
        // cmp byte ptr [0x167eb75], 0
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x74
        _emit 0x07
        // je 0xb452c3
        _emit 0xC6
        _emit 0x05
        _emit 0x75
        _emit 0xEB
        _emit 0x67
        _emit 0x01
        _emit 0x00
        // mov byte ptr [0x167eb75], 0
        call FUN_00b5a390
        _emit 0x8B
        _emit 0x46
        _emit 0x48
        // mov eax, dword ptr [esi + 0x48]
        _emit 0x8B
        _emit 0x4E
        _emit 0x44
        // mov ecx, dword ptr [esi + 0x44]
        _emit 0x83
        _emit 0xC6
        _emit 0x40
        // add esi, 0x40
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_007611f0
        _emit 0xC7
        _emit 0x46
        _emit 0x0C
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0xc], 0
        _emit 0x5E
        // pop esi
        _emit 0xC3
        // ret 
    }
}

// @ 0x00b452f0  (172 bytes)
__declspec(naked) void FUN_00b452f0()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0x83
        _emit 0x7F
        _emit 0x20
        _emit 0x00
        // cmp dword ptr [edi + 0x20], 0
        _emit 0x75
        _emit 0x1E
        // jne 0xb4531a
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov eax, dword ptr [esp + 0x18]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov edx, dword ptr [esp + 0x10]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x52
        // push edx
        call FUN_00b54340
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0x5F
        // pop edi
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x74
        _emit 0x24
        _emit 0x14
        // mov esi, dword ptr [esp + 0x14]
        _emit 0x85
        _emit 0xF6
        // test esi, esi
        _emit 0x74
        _emit 0x2B
        // je 0xb4534e
        _emit 0x8B
        _emit 0x06
        // mov eax, dword ptr [esi]
        _emit 0x8B
        _emit 0x90
        _emit 0xB8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, dword ptr [eax + 0xb8]
        _emit 0x68
        _emit 0x1B
        _emit 0xDD
        _emit 0x16
        _emit 0x01
        // push 0x116dd1b
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xFF
        _emit 0xD2
        // call edx
        _emit 0x85
        _emit 0xC0
        // test eax, eax
        _emit 0x74
        _emit 0x16
        // je 0xb4534e
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // mov ecx, dword ptr [esp + 0x18]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xC8
        // mov ecx, eax
        call FUN_00c446d0
        _emit 0x5E
        // pop esi
        _emit 0x5F
        // pop edi
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
        _emit 0x83
        _emit 0x7F
        _emit 0x20
        _emit 0x01
        // cmp dword ptr [edi + 0x20], 1
        _emit 0x75
        _emit 0x40
        // jne 0xb45394
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x14
        // mov dword ptr [esp + 0x14], esi
        _emit 0x8B
        _emit 0x35
        _emit 0x70
        _emit 0xEB
        _emit 0x67
        _emit 0x01
        // mov esi, dword ptr [0x167eb70]
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
        _emit 0x0C
        // lea eax, [esp + 0xc]
        _emit 0x83
        _emit 0xC6
        _emit 0x58
        // add esi, 0x58
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00645ed0
        _emit 0x8B
        _emit 0x4E
        _emit 0x08
        // mov ecx, dword ptr [esi + 8]
        _emit 0x8B
        _emit 0x56
        _emit 0x04
        // mov edx, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0x3B
        _emit 0x04
        _emit 0x8A
        // cmp eax, dword ptr [edx + ecx*4]
        _emit 0x74
        _emit 0x13
        // je 0xb45394
        _emit 0x8B
        _emit 0x70
        _emit 0x04
        // mov esi, dword ptr [eax + 4]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov eax, dword ptr [esp + 0x18]
        _emit 0x50
        // push eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00b3dec0
        _emit 0xC6
        _emit 0x46
        _emit 0x34
        _emit 0x00
        // mov byte ptr [esi + 0x34], 0
        _emit 0x5E
        // pop esi
        _emit 0x5F
        // pop edi
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
    }
}

// @ 0x00b453a0  (103 bytes)
__declspec(naked) void FUN_00b453a0()
{
    __asm {
        _emit 0x8B
        _emit 0x41
        _emit 0x20
        // mov eax, dword ptr [ecx + 0x20]
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0x83
        _emit 0xE8
        _emit 0x00
        // sub eax, 0
        _emit 0x74
        _emit 0x47
        // je 0xb453f2
        _emit 0x83
        _emit 0xE8
        _emit 0x01
        // sub eax, 1
        _emit 0x75
        _emit 0x51
        // jne 0xb45401
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov eax, dword ptr [esp + 0xc]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x35
        _emit 0x70
        _emit 0xEB
        _emit 0x67
        _emit 0x01
        // mov esi, dword ptr [0x167eb70]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // lea ecx, [esp + 0x10]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // lea edx, [esp + 8]
        _emit 0x83
        _emit 0xC6
        _emit 0x58
        // add esi, 0x58
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], eax
        call FUN_00645ed0
        _emit 0x8B
        _emit 0x4E
        _emit 0x08
        // mov ecx, dword ptr [esi + 8]
        _emit 0x8B
        _emit 0x56
        _emit 0x04
        // mov edx, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
        _emit 0x5E
        // pop esi
        _emit 0x3B
        _emit 0x04
        _emit 0x8A
        // cmp eax, dword ptr [edx + ecx*4]
        _emit 0x74
        _emit 0x1E
        // je 0xb45401
        _emit 0x8B
        _emit 0x40
        _emit 0x04
        // mov eax, dword ptr [eax + 4]
        _emit 0x8B
        _emit 0x48
        _emit 0x3C
        // mov ecx, dword ptr [eax + 0x3c]
        _emit 0x89
        _emit 0x48
        _emit 0x38
        // mov dword ptr [eax + 0x38], ecx
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x0C
        // mov edx, dword ptr [esp + 0xc]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x52
        // push edx
        call FUN_00b544c0
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00b45410  (104 bytes)
__declspec(naked) void FUN_00b45410()
{
    __asm {
        _emit 0x8B
        _emit 0x41
        _emit 0x20
        // mov eax, dword ptr [ecx + 0x20]
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0x83
        _emit 0xE8
        _emit 0x00
        // sub eax, 0
        _emit 0x74
        _emit 0x48
        // je 0xb45463
        _emit 0x83
        _emit 0xE8
        _emit 0x01
        // sub eax, 1
        _emit 0x75
        _emit 0x52
        // jne 0xb45472
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov eax, dword ptr [esp + 0xc]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x35
        _emit 0x70
        _emit 0xEB
        _emit 0x67
        _emit 0x01
        // mov esi, dword ptr [0x167eb70]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // lea ecx, [esp + 0x10]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // lea edx, [esp + 8]
        _emit 0x83
        _emit 0xC6
        _emit 0x58
        // add esi, 0x58
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], eax
        call FUN_00645ed0
        _emit 0x8B
        _emit 0x4E
        _emit 0x08
        // mov ecx, dword ptr [esi + 8]
        _emit 0x8B
        _emit 0x56
        _emit 0x04
        // mov edx, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
        _emit 0x5E
        // pop esi
        _emit 0x3B
        _emit 0x04
        _emit 0x8A
        // cmp eax, dword ptr [edx + ecx*4]
        _emit 0x74
        _emit 0x1F
        // je 0xb45472
        _emit 0x8B
        _emit 0x40
        _emit 0x04
        // mov eax, dword ptr [eax + 4]
        _emit 0xC7
        _emit 0x40
        _emit 0x38
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [eax + 0x38], 0
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x0C
        // mov ecx, dword ptr [esp + 0xc]
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x51
        // push ecx
        call FUN_00b544f0
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00b45480  (180 bytes)
__declspec(naked) void FUN_00b45480()
{
    __asm {
        _emit 0x8B
        _emit 0x41
        _emit 0x20
        // mov eax, dword ptr [ecx + 0x20]
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0x83
        _emit 0xE8
        _emit 0x00
        // sub eax, 0
        _emit 0x0F
        _emit 0x84
        _emit 0x92
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // je 0xb45521
        _emit 0x83
        _emit 0xE8
        _emit 0x01
        // sub eax, 1
        _emit 0x0F
        _emit 0x85
        _emit 0x81
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // jne 0xb45519
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov eax, dword ptr [esp + 0xc]
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0x35
        _emit 0x70
        _emit 0xEB
        _emit 0x67
        _emit 0x01
        // mov esi, dword ptr [0x167eb70]
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // lea ecx, [esp + 0x10]
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x54
        _emit 0x24
        _emit 0x08
        // lea edx, [esp + 8]
        _emit 0x83
        _emit 0xC6
        _emit 0x58
        // add esi, 0x58
        _emit 0x52
        // push edx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // mov dword ptr [esp + 0x18], eax
        call FUN_00645ed0
        _emit 0x8B
        _emit 0x4E
        _emit 0x08
        // mov ecx, dword ptr [esi + 8]
        _emit 0x8B
        _emit 0x56
        _emit 0x04
        // mov edx, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x04
        // mov eax, dword ptr [esp + 4]
        _emit 0x5E
        // pop esi
        _emit 0x3B
        _emit 0x04
        _emit 0x8A
        // cmp eax, dword ptr [edx + ecx*4]
        _emit 0x74
        _emit 0x4E
        // je 0xb45519
        _emit 0x8B
        _emit 0x40
        _emit 0x04
        // mov eax, dword ptr [eax + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x50
        _emit 0x1C
        // movss xmm2, dword ptr [eax + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0x20
        // movss xmm1, dword ptr [eax + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x40
        _emit 0x24
        // movss xmm0, dword ptr [eax + 0x24]
        _emit 0x83
        _emit 0xC0
        _emit 0x1C
        // add eax, 0x1c
        _emit 0x0F
        _emit 0x28
        _emit 0xDA
        // movaps xmm3, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xDA
        // mulss xmm3, xmm2
        _emit 0x0F
        _emit 0x28
        _emit 0xD1
        // movaps xmm2, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD1
        // mulss xmm2, xmm1
        _emit 0x0F
        _emit 0x28
        _emit 0xC8
        // movaps xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xDA
        // addss xmm3, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xD9
        // addss xmm3, xmm1
        _emit 0x0F
        _emit 0x2F
        _emit 0x1D
        _emit 0x54
        _emit 0x11
        _emit 0x46
        _emit 0x01
        // comiss xmm3, dword ptr [0x1461154]
        _emit 0x76
        _emit 0x0B
        // jbe 0xb45511
        _emit 0xB8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, 1
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0x32
        _emit 0xC0
        // xor al, al
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x0C
        // mov eax, dword ptr [esp + 0xc]
        _emit 0x50
        // push eax
        call FUN_00b54520
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00b45540  (1391 bytes)
__declspec(naked) void FUN_00b45540()
{
    __asm {
        _emit 0x83
        _emit 0xEC
        _emit 0x0C
        // sub esp, 0xc
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // mov eax, dword ptr [esp + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x1D
        _emit 0xB0
        _emit 0xB8
        _emit 0x3E
        _emit 0x01
        // movss xmm3, dword ptr [0x13eb8b0]
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7C
        _emit 0x24
        _emit 0x30
        // mov edi, dword ptr [esp + 0x30]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x87
        _emit 0x84
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [edi + 0x184]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8F
        _emit 0x88
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [edi + 0x188]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x97
        _emit 0x8C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm2, dword ptr [edi + 0x18c]
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x6E
        _emit 0x04
        // lea ebp, [esi + 4]
        _emit 0x55
        // push ebp
        _emit 0x8D
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // lea ecx, [esp + 0x18]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov ecx, dword ptr [esp + 0x2c]
        _emit 0x0F
        _emit 0x57
        _emit 0xC3
        // xorps xmm0, xmm3
        _emit 0x0F
        _emit 0x57
        _emit 0xCB
        // xorps xmm1, xmm3
        _emit 0x0F
        _emit 0x57
        _emit 0xD3
        // xorps xmm2, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // movss dword ptr [esp + 0x1c], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // movss dword ptr [esp + 0x20], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x54
        _emit 0x24
        _emit 0x24
        // movss dword ptr [esp + 0x24], xmm2
        call FUN_00b42760
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x20
        // mov edx, dword ptr [esp + 0x20]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // mov ecx, dword ptr [esp + 0x24]
        _emit 0x52
        // push edx
        _emit 0x89
        _emit 0x86
        _emit 0x04
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x304], eax
        _emit 0x8D
        _emit 0x9E
        _emit 0x84
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea ebx, [esi + 0x184]
        _emit 0x53
        // push ebx
        _emit 0x8D
        _emit 0x87
        _emit 0x84
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea eax, [edi + 0x184]
        _emit 0x50
        // push eax
        call FUN_00b42760
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x39
        _emit 0x96
        _emit 0x04
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // cmp dword ptr [esi + 0x304], edx
        _emit 0x89
        _emit 0x86
        _emit 0x08
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // mov dword ptr [esi + 0x308], eax
        _emit 0x7E
        _emit 0x61
        // jle 0xb45632
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x28
        // mov ecx, dword ptr [esp + 0x28]
        _emit 0x8D
        _emit 0x46
        _emit 0x0C
        // lea eax, [esi + 0xc]
        _emit 0xEB
        _emit 0x06
        // jmp 0xb455e0
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebx, [ebx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8F
        _emit 0x90
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [edi + 0x190]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x11
        // movss xmm2, dword ptr [ecx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x59
        _emit 0x04
        // movss xmm3, dword ptr [ecx + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x41
        _emit 0x08
        // movss xmm0, dword ptr [ecx + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC1
        // mulss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x00
        // addss xmm0, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD1
        // mulss xmm2, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD9
        // mulss xmm3, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0xF8
        // movss xmm1, dword ptr [eax - 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xCA
        // addss xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x48
        _emit 0xF8
        // movss dword ptr [eax - 8], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x48
        _emit 0xFC
        // movss xmm1, dword ptr [eax - 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xCB
        // addss xmm1, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x48
        _emit 0xFC
        // movss dword ptr [eax - 4], xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x00
        // movss dword ptr [eax], xmm0
        _emit 0x42
        // inc edx
        _emit 0x83
        _emit 0xC0
        _emit 0x0C
        // add eax, 0xc
        _emit 0x3B
        _emit 0x96
        _emit 0x04
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // cmp edx, dword ptr [esi + 0x304]
        _emit 0x7C
        _emit 0xAE
        // jl 0xb455e0
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x39
        _emit 0x96
        _emit 0x08
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // cmp dword ptr [esi + 0x308], edx
        _emit 0x7E
        _emit 0x62
        // jle 0xb4569e
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x2C
        // mov ecx, dword ptr [esp + 0x2c]
        _emit 0x8D
        _emit 0x86
        _emit 0x8C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea eax, [esi + 0x18c]
        _emit 0xEB
        _emit 0x08
        // jmp 0xb45650
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
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x97
        _emit 0x90
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm2, dword ptr [edi + 0x190]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x19
        // movss xmm3, dword ptr [ecx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x41
        _emit 0x04
        // movss xmm0, dword ptr [ecx + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x49
        _emit 0x08
        // movss xmm1, dword ptr [ecx + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC2
        // mulss xmm0, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x40
        _emit 0xFC
        // addss xmm0, dword ptr [eax - 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCA
        // mulss xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0x08
        // addss xmm1, dword ptr [eax]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xDA
        // mulss xmm3, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x50
        _emit 0xF8
        // movss xmm2, dword ptr [eax - 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xD3
        // addss xmm2, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x50
        _emit 0xF8
        // movss dword ptr [eax - 8], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x40
        _emit 0xFC
        // movss dword ptr [eax - 4], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x08
        // movss dword ptr [eax], xmm1
        _emit 0x42
        // inc edx
        _emit 0x83
        _emit 0xC0
        _emit 0x0C
        // add eax, 0xc
        _emit 0x3B
        _emit 0x96
        _emit 0x08
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // cmp edx, dword ptr [esi + 0x308]
        _emit 0x7C
        _emit 0xB2
        // jl 0xb45650
        _emit 0x8B
        _emit 0x86
        _emit 0x04
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x304]
        _emit 0xBA
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov edx, 1
        _emit 0x3B
        _emit 0xC2
        // cmp eax, edx
        _emit 0x0F
        _emit 0x85
        _emit 0xF0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jne 0xb458a1
        _emit 0x8B
        _emit 0x86
        _emit 0x08
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x308]
        _emit 0x3B
        _emit 0xC2
        // cmp eax, edx
        _emit 0x75
        _emit 0x3D
        // jne 0xb456f8
        _emit 0x8B
        _emit 0x45
        _emit 0x00
        // mov eax, dword ptr [ebp]
        _emit 0x89
        _emit 0x07
        // mov dword ptr [edi], eax
        _emit 0x8B
        _emit 0x4D
        _emit 0x04
        // mov ecx, dword ptr [ebp + 4]
        _emit 0x89
        _emit 0x4F
        _emit 0x04
        // mov dword ptr [edi + 4], ecx
        _emit 0x8B
        _emit 0x45
        _emit 0x08
        // mov eax, dword ptr [ebp + 8]
        _emit 0x89
        _emit 0x47
        _emit 0x08
        // mov dword ptr [edi + 8], eax
        _emit 0x8B
        _emit 0x0B
        // mov ecx, dword ptr [ebx]
        _emit 0x89
        _emit 0x8F
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0xc0], ecx
        _emit 0x8B
        _emit 0x43
        _emit 0x04
        // mov eax, dword ptr [ebx + 4]
        _emit 0x89
        _emit 0x87
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0xc4], eax
        _emit 0x8B
        _emit 0x4B
        _emit 0x08
        // mov ecx, dword ptr [ebx + 8]
        _emit 0x89
        _emit 0x8F
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0xc8], ecx
        _emit 0x89
        _emit 0x97
        _emit 0x80
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x180], edx
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x8A
        _emit 0xC2
        // mov al, dl
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xC2
        _emit 0x14
        _emit 0x00
        // ret 0x14
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x75
        _emit 0x2A
        // jne 0xb45727
        _emit 0x8D
        _emit 0x97
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea edx, [edi + 0xc0]
        _emit 0x52
        // push edx
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x86
        _emit 0x90
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea eax, [esi + 0x190]
        _emit 0x50
        // push eax
        _emit 0x53
        // push ebx
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00b3e860
        _emit 0x89
        _emit 0x87
        _emit 0x80
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x180], eax
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xC2
        _emit 0x14
        _emit 0x00
        // ret 0x14
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xB6
        _emit 0x90
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm6, dword ptr [esi + 0x190]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA6
        _emit 0x9C
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [esi + 0x19c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xBE
        _emit 0x94
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm7, dword ptr [esi + 0x194]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x8E
        _emit 0xA0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm1, dword ptr [esi + 0x1a0]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x9E
        _emit 0xA4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm3, dword ptr [esi + 0x1a4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x86
        _emit 0x98
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm0, dword ptr [esi + 0x198]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x43
        _emit 0x08
        // subss xmm0, dword ptr [ebx + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xE6
        // subss xmm4, xmm6
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xCF
        // subss xmm1, xmm7
        _emit 0x0F
        _emit 0x28
        _emit 0xEE
        // movaps xmm5, xmm6
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x2B
        // subss xmm5, dword ptr [ebx]
        _emit 0x0F
        _emit 0x28
        _emit 0xF4
        // movaps xmm6, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0xA6
        _emit 0x98
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // movss xmm4, dword ptr [esi + 0x198]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xDC
        // subss xmm3, xmm4
        _emit 0x0F
        _emit 0x28
        _emit 0xE3
        // movaps xmm4, xmm3
        _emit 0x0F
        _emit 0x28
        _emit 0xD7
        // movaps xmm2, xmm7
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x53
        _emit 0x04
        // subss xmm2, dword ptr [ebx + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE2
        // mulss xmm4, xmm2
        _emit 0x0F
        _emit 0x28
        _emit 0xF9
        // movaps xmm7, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xF8
        // mulss xmm7, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xE7
        // subss xmm4, xmm7
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x64
        _emit 0x24
        _emit 0x10
        // movss dword ptr [esp + 0x10], xmm4
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCD
        // mulss xmm1, xmm5
        _emit 0xDC
        _emit 0xC8
        // fmul st(0), st(0)
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD6
        // mulss xmm2, xmm6
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xCA
        // subss xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xDD
        // mulss xmm3, xmm5
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC6
        // mulss xmm0, xmm6
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xC3
        // subss xmm0, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // movss dword ptr [esp + 0x18], xmm1
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xDC
        _emit 0xC8
        // fmul st(0), st(0)
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm0
        _emit 0x8B
        _emit 0x4D
        _emit 0x00
        // mov ecx, dword ptr [ebp]
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0xDC
        _emit 0xC8
        // fmul st(0), st(0)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xFA
        // fsqrt 
        _emit 0xD9
        _emit 0xE8
        // fld1 
        _emit 0xDE
        _emit 0xF1
        // fdivrp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x6C
        _emit 0x24
        _emit 0x20
        // movss xmm5, dword ptr [esp + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC5
        // mulss xmm0, xmm5
        _emit 0x0F
        _emit 0x28
        _emit 0xD8
        // movaps xmm3, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x45
        _emit 0x00
        // movss xmm0, dword ptr [ebp]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCD
        // mulss xmm1, xmm5
        _emit 0x0F
        _emit 0x28
        _emit 0xD5
        // movaps xmm2, xmm5
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x6B
        _emit 0x04
        // movss xmm5, dword ptr [ebx + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD4
        // mulss xmm2, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC2
        // mulss xmm0, xmm2
        _emit 0x0F
        _emit 0x28
        _emit 0xE1
        // movaps xmm4, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x65
        _emit 0x08
        // mulss xmm4, dword ptr [ebp + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC4
        // addss xmm0, xmm4
        _emit 0x0F
        _emit 0x28
        _emit 0xE3
        // movaps xmm4, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x65
        _emit 0x04
        // mulss xmm4, dword ptr [ebp + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC4
        // addss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x63
        _emit 0x08
        // movss xmm4, dword ptr [ebx + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xEB
        // mulss xmm5, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE1
        // mulss xmm4, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xE5
        // addss xmm4, xmm5
        _emit 0x0F
        _emit 0x28
        _emit 0xEA
        // movaps xmm5, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x2B
        // mulss xmm5, dword ptr [ebx]
        _emit 0x89
        _emit 0x0F
        // mov dword ptr [edi], ecx
        _emit 0x8B
        _emit 0x45
        _emit 0x04
        // mov eax, dword ptr [ebp + 4]
        _emit 0x89
        _emit 0x47
        _emit 0x04
        // mov dword ptr [edi + 4], eax
        _emit 0x8B
        _emit 0x4D
        _emit 0x08
        // mov ecx, dword ptr [ebp + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xE5
        // addss xmm4, xmm5
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xC4
        // subss xmm0, xmm4
        _emit 0x0F
        _emit 0x28
        _emit 0xE0
        // movaps xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD8
        // mulss xmm3, xmm0
        _emit 0x89
        _emit 0x4F
        _emit 0x08
        // mov dword ptr [edi + 8], ecx
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE2
        // mulss xmm4, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x55
        _emit 0x04
        // movss xmm2, dword ptr [ebp + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x45
        _emit 0x00
        // movss xmm0, dword ptr [ebp]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xD3
        // subss xmm2, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5D
        _emit 0x08
        // movss xmm3, dword ptr [ebp + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xC4
        // subss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xD9
        // subss xmm3, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x87
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [edi + 0xc0], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x97
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [edi + 0xc4], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x9F
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // movss dword ptr [edi + 0xc8], xmm3
        _emit 0x89
        _emit 0x97
        _emit 0x80
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x180], edx
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x8A
        _emit 0xC2
        // mov al, dl
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xC2
        _emit 0x14
        _emit 0x00
        // ret 0x14
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x75
        _emit 0x70
        // jne 0xb45916
        _emit 0x8B
        _emit 0x86
        _emit 0x08
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [esi + 0x308]
        _emit 0x3B
        _emit 0xC2
        // cmp eax, edx
        _emit 0x75
        _emit 0x27
        // jne 0xb458d7
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x97
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea edx, [edi + 0xc0]
        _emit 0x52
        // push edx
        _emit 0x8D
        _emit 0x46
        _emit 0x10
        // lea eax, [esi + 0x10]
        _emit 0x50
        // push eax
        _emit 0x55
        // push ebp
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00b3e860
        _emit 0x89
        _emit 0x87
        _emit 0x80
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x180], eax
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xC2
        _emit 0x14
        _emit 0x00
        // ret 0x14
        _emit 0x8D
        _emit 0x8F
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ecx, [edi + 0xc0]
        _emit 0x83
        _emit 0xF8
        _emit 0x02
        // cmp eax, 2
        _emit 0x75
        _emit 0x28
        // jne 0xb4590a
        _emit 0x51
        // push ecx
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x96
        _emit 0x90
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // lea edx, [esi + 0x190]
        _emit 0x52
        // push edx
        _emit 0x53
        // push ebx
        _emit 0x8D
        _emit 0x46
        _emit 0x10
        // lea eax, [esi + 0x10]
        _emit 0x50
        // push eax
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00b3e980
        _emit 0x89
        _emit 0x87
        _emit 0x80
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x180], eax
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xC2
        _emit 0x14
        _emit 0x00
        // ret 0x14
        _emit 0x57
        // push edi
        _emit 0x51
        // push ecx
        _emit 0x6A
        _emit 0x02
        // push 2
        _emit 0x55
        // push ebp
        _emit 0x50
        // push eax
        _emit 0x53
        // push ebx
        _emit 0xE9
        _emit 0x80
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jmp 0xb45a96
        _emit 0x8B
        _emit 0x8E
        _emit 0x08
        _emit 0x03
        _emit 0x00
        _emit 0x00
        // mov ecx, dword ptr [esi + 0x308]
        _emit 0x3B
        _emit 0xCA
        // cmp ecx, edx
        _emit 0x0F
        _emit 0x85
        _emit 0x66
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // jne 0xb45a8a
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x76
        _emit 0x10
        // movss xmm6, dword ptr [esi + 0x10]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x66
        _emit 0x1C
        // movss xmm4, dword ptr [esi + 0x1c]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x7E
        _emit 0x14
        // movss xmm7, dword ptr [esi + 0x14]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5E
        _emit 0x24
        // movss xmm3, dword ptr [esi + 0x24]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x4E
        _emit 0x20
        // movss xmm1, dword ptr [esi + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x46
        _emit 0x18
        // movss xmm0, dword ptr [esi + 0x18]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x45
        _emit 0x08
        // subss xmm0, dword ptr [ebp + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xE6
        // subss xmm4, xmm6
        _emit 0x0F
        _emit 0x28
        _emit 0xEE
        // movaps xmm5, xmm6
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x6D
        _emit 0x00
        // subss xmm5, dword ptr [ebp]
        _emit 0x0F
        _emit 0x28
        _emit 0xF4
        // movaps xmm6, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x66
        _emit 0x18
        // movss xmm4, dword ptr [esi + 0x18]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xDC
        // subss xmm3, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xCF
        // subss xmm1, xmm7
        _emit 0x0F
        _emit 0x28
        _emit 0xE3
        // movaps xmm4, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xDD
        // mulss xmm3, xmm5
        _emit 0x0F
        _emit 0x28
        _emit 0xD7
        // movaps xmm2, xmm7
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0x55
        _emit 0x04
        // subss xmm2, dword ptr [ebp + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE2
        // mulss xmm4, xmm2
        _emit 0x0F
        _emit 0x28
        _emit 0xF9
        // movaps xmm7, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xF8
        // mulss xmm7, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCD
        // mulss xmm1, xmm5
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC6
        // mulss xmm0, xmm6
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xC3
        // subss xmm0, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD6
        // mulss xmm2, xmm6
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xCA
        // subss xmm1, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // movss dword ptr [esp + 0x14], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xE7
        // subss xmm4, xmm7
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x4C
        _emit 0x24
        _emit 0x18
        // movss dword ptr [esp + 0x18], xmm1
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x18
        // fld dword ptr [esp + 0x18]
        _emit 0xDC
        _emit 0xC8
        // fmul st(0), st(0)
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x64
        _emit 0x24
        _emit 0x10
        // movss dword ptr [esp + 0x10], xmm4
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x14
        // fld dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0xDC
        _emit 0xC8
        // fmul st(0), st(0)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0x44
        _emit 0x24
        _emit 0x10
        // fld dword ptr [esp + 0x10]
        _emit 0xDC
        _emit 0xC8
        // fmul st(0), st(0)
        _emit 0xDE
        _emit 0xC1
        // faddp st(1)
        _emit 0xD9
        _emit 0xFA
        // fsqrt 
        _emit 0xD9
        _emit 0xE8
        // fld1 
        _emit 0xDE
        _emit 0xF1
        // fdivrp st(1)
        _emit 0xD9
        _emit 0x5C
        _emit 0x24
        _emit 0x20
        // fstp dword ptr [esp + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x6C
        _emit 0x24
        _emit 0x20
        // movss xmm5, dword ptr [esp + 0x20]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC5
        // mulss xmm0, xmm5
        _emit 0x0F
        _emit 0x28
        _emit 0xD8
        // movaps xmm3, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x43
        _emit 0x08
        // movss xmm0, dword ptr [ebx + 8]
        _emit 0x0F
        _emit 0x28
        _emit 0xD5
        // movaps xmm2, xmm5
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD4
        // mulss xmm2, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x63
        _emit 0x04
        // movss xmm4, dword ptr [ebx + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE3
        // mulss xmm4, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xCD
        // mulss xmm1, xmm5
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x6D
        _emit 0x04
        // movss xmm5, dword ptr [ebp + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC1
        // mulss xmm0, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC4
        // addss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x23
        // movss xmm4, dword ptr [ebx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE2
        // mulss xmm4, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xC4
        // addss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x65
        _emit 0x08
        // movss xmm4, dword ptr [ebp + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xEB
        // mulss xmm5, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE1
        // mulss xmm4, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xE5
        // addss xmm4, xmm5
        _emit 0x0F
        _emit 0x28
        _emit 0xEA
        // movaps xmm5, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0x6D
        _emit 0x00
        // mulss xmm5, dword ptr [ebp]
        _emit 0x89
        _emit 0x87
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0xc0], eax
        _emit 0x8B
        _emit 0x4B
        _emit 0x04
        // mov ecx, dword ptr [ebx + 4]
        _emit 0x89
        _emit 0x8F
        _emit 0xC4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0xc4], ecx
        _emit 0x8B
        _emit 0x43
        _emit 0x08
        // mov eax, dword ptr [ebx + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x58
        _emit 0xE5
        // addss xmm4, xmm5
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xC4
        // subss xmm0, xmm4
        _emit 0x0F
        _emit 0x28
        _emit 0xE0
        // movaps xmm4, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xD8
        // mulss xmm3, xmm0
        _emit 0x89
        _emit 0x87
        _emit 0xC8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0xc8], eax
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xE2
        // mulss xmm4, xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x53
        _emit 0x04
        // movss xmm2, dword ptr [ebx + 4]
        _emit 0xF3
        _emit 0x0F
        _emit 0x59
        _emit 0xC8
        // mulss xmm1, xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x03
        // movss xmm0, dword ptr [ebx]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xD3
        // subss xmm2, xmm3
        _emit 0xF3
        _emit 0x0F
        _emit 0x10
        _emit 0x5B
        _emit 0x08
        // movss xmm3, dword ptr [ebx + 8]
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xC4
        // subss xmm0, xmm4
        _emit 0xF3
        _emit 0x0F
        _emit 0x5C
        _emit 0xD9
        // subss xmm3, xmm1
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x07
        // movss dword ptr [edi], xmm0
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x57
        _emit 0x04
        // movss dword ptr [edi + 4], xmm2
        _emit 0xF3
        _emit 0x0F
        _emit 0x11
        _emit 0x5F
        _emit 0x08
        // movss dword ptr [edi + 8], xmm3
        _emit 0x89
        _emit 0x97
        _emit 0x80
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x180], edx
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x8A
        _emit 0xC2
        // mov al, dl
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xC2
        _emit 0x14
        _emit 0x00
        // ret 0x14
        _emit 0x8D
        _emit 0x97
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea edx, [edi + 0xc0]
        _emit 0x52
        // push edx
        _emit 0x57
        // push edi
        _emit 0x51
        // push ecx
        _emit 0x53
        // push ebx
        _emit 0x50
        // push eax
        _emit 0x55
        // push ebp
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00b41900
        _emit 0x89
        _emit 0x87
        _emit 0x80
        _emit 0x01
        _emit 0x00
        _emit 0x00
        // mov dword ptr [edi + 0x180], eax
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0xB0
        _emit 0x01
        // mov al, 1
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x0C
        // add esp, 0xc
        _emit 0xC2
        _emit 0x14
        _emit 0x00
        // ret 0x14
    }
}

// @ 0x00b45ab0  (153 bytes)
__declspec(naked) void FUN_00b45ab0()
{
    __asm {
        _emit 0x51
        // push ecx
        _emit 0x53
        // push ebx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0x8B
        _emit 0x47
        _emit 0x0C
        // mov eax, dword ptr [edi + 0xc]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x10
        // mov ecx, dword ptr [esp + 0x10]
        _emit 0x8B
        _emit 0x09
        // mov ecx, dword ptr [ecx]
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov dword ptr [esp + 8], eax
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x8B
        _emit 0xC1
        // mov eax, ecx
        _emit 0xF7
        _emit 0x77
        _emit 0x08
        // div dword ptr [edi + 8]
        _emit 0x8B
        _emit 0x47
        _emit 0x04
        // mov eax, dword ptr [edi + 4]
        _emit 0x83
        _emit 0x3C
        _emit 0x90
        _emit 0x00
        // cmp dword ptr [eax + edx*4], 0
        _emit 0x8D
        _emit 0x1C
        _emit 0x90
        // lea ebx, [eax + edx*4]
        _emit 0x74
        _emit 0x67
        // je 0xb45b3c
        _emit 0x8B
        _emit 0x03
        // mov eax, dword ptr [ebx]
        _emit 0x3B
        _emit 0x08
        // cmp ecx, dword ptr [eax]
        _emit 0x74
        _emit 0x09
        // je 0xb45ae4
        _emit 0x83
        _emit 0x78
        _emit 0x04
        _emit 0x00
        // cmp dword ptr [eax + 4], 0
        _emit 0x8D
        _emit 0x58
        _emit 0x04
        // lea ebx, [eax + 4]
        _emit 0x75
        _emit 0xF1
        // jne 0xb45ad5
        _emit 0x83
        _emit 0x3B
        _emit 0x00
        // cmp dword ptr [ebx], 0
        _emit 0x74
        _emit 0x53
        // je 0xb45b3c
        _emit 0x56
        // push esi
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea ebx, [ebx]
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x8B
        _emit 0x33
        // mov esi, dword ptr [ebx]
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x3B
        _emit 0x16
        // cmp edx, dword ptr [esi]
        _emit 0x75
        _emit 0x3F
        // jne 0xb45b3b
        _emit 0x8B
        _emit 0x46
        _emit 0x04
        // mov eax, dword ptr [esi + 4]
        _emit 0x89
        _emit 0x03
        // mov dword ptr [ebx], eax
        _emit 0x8B
        _emit 0x0E
        // mov ecx, dword ptr [esi]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x0A
        // je 0xb45b11
        _emit 0x8B
        _emit 0x11
        // mov edx, dword ptr [ecx]
        _emit 0x8B
        _emit 0x82
        _emit 0xC0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // mov eax, dword ptr [edx + 0xc0]
        _emit 0xFF
        _emit 0xD0
        // call eax
        _emit 0x3B
        _emit 0x77
        _emit 0x30
        // cmp esi, dword ptr [edi + 0x30]
        _emit 0x74
        _emit 0x1D
        // je 0xb45b33
        _emit 0x3B
        _emit 0x77
        _emit 0x24
        // cmp esi, dword ptr [edi + 0x24]
        _emit 0x72
        _emit 0x0F
        // jb 0xb45b2a
        _emit 0x3B
        _emit 0x77
        _emit 0x28
        // cmp esi, dword ptr [edi + 0x28]
        _emit 0x73
        _emit 0x0A
        // jae 0xb45b2a
        _emit 0x8B
        _emit 0x4F
        _emit 0x1C
        // mov ecx, dword ptr [edi + 0x1c]
        _emit 0x89
        _emit 0x0E
        // mov dword ptr [esi], ecx
        _emit 0x89
        _emit 0x77
        _emit 0x1C
        // mov dword ptr [edi + 0x1c], esi
        _emit 0xEB
        _emit 0x09
        // jmp 0xb45b33
        _emit 0x56
        // push esi
        call FUN_00f47380
        _emit 0x83
        _emit 0xC4
        _emit 0x04
        // add esp, 4
        _emit 0xFF
        _emit 0x4F
        _emit 0x0C
        // dec dword ptr [edi + 0xc]
        _emit 0x83
        _emit 0x3B
        _emit 0x00
        // cmp dword ptr [ebx], 0
        _emit 0x75
        _emit 0xB5
        // jne 0xb45af0
        _emit 0x5E
        // pop esi
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0x2B
        _emit 0x47
        _emit 0x0C
        // sub eax, dword ptr [edi + 0xc]
        _emit 0x5F
        // pop edi
        _emit 0x5B
        // pop ebx
        _emit 0x59
        // pop ecx
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}

// @ 0x00b45b50  (186 bytes)
__declspec(naked) void FUN_00b45b50()
{
    __asm {
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x08
        // mov eax, dword ptr [esp + 8]
        _emit 0x83
        _emit 0xEC
        _emit 0x08
        // sub esp, 8
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x18
        // mov ebx, dword ptr [eax]
        _emit 0x55
        // push ebp
        _emit 0x56
        // push esi
        _emit 0x8B
        _emit 0xF1
        // mov esi, ecx
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0x7E
        _emit 0x08
        // mov edi, dword ptr [esi + 8]
        _emit 0x8B
        _emit 0xC3
        // mov eax, ebx
        _emit 0xF7
        _emit 0xF7
        // div edi
        _emit 0x8B
        _emit 0x4E
        _emit 0x04
        // mov ecx, dword ptr [esi + 4]
        _emit 0x8B
        _emit 0xEA
        // mov ebp, edx
        _emit 0x8D
        _emit 0x14
        _emit 0xA9
        // lea edx, [ecx + ebp*4]
        _emit 0x8B
        _emit 0x0A
        // mov ecx, dword ptr [edx]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x74
        _emit 0x0B
        // je 0xb45b81
        _emit 0x3B
        _emit 0x19
        // cmp ebx, dword ptr [ecx]
        _emit 0x74
        _emit 0x79
        // je 0xb45bf3
        _emit 0x8B
        _emit 0x49
        _emit 0x04
        // mov ecx, dword ptr [ecx + 4]
        _emit 0x85
        _emit 0xC9
        // test ecx, ecx
        _emit 0x75
        _emit 0xF5
        // jne 0xb45b76
        _emit 0x8B
        _emit 0x56
        _emit 0x0C
        // mov edx, dword ptr [esi + 0xc]
        _emit 0x6A
        _emit 0x01
        // push 1
        _emit 0x52
        // push edx
        _emit 0x57
        // push edi
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // lea eax, [esp + 0x1c]
        _emit 0x50
        // push eax
        _emit 0x8D
        _emit 0x4E
        _emit 0x10
        // lea ecx, [esi + 0x10]
        call FUN_00921440
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x20
        // mov ecx, dword ptr [esp + 0x20]
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        call FUN_00b41dc0
        _emit 0x80
        _emit 0x7C
        _emit 0x24
        _emit 0x10
        _emit 0x00
        // cmp byte ptr [esp + 0x10], 0
        _emit 0x8B
        _emit 0xF8
        // mov edi, eax
        _emit 0x74
        _emit 0x14
        // je 0xb45bbe
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x14
        // mov ecx, dword ptr [esp + 0x14]
        _emit 0x33
        _emit 0xD2
        // xor edx, edx
        _emit 0x8B
        _emit 0xC3
        // mov eax, ebx
        _emit 0xF7
        _emit 0xF1
        // div ecx
        _emit 0x51
        // push ecx
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0x8B
        _emit 0xEA
        // mov ebp, edx
        call FUN_00ef7c00
        _emit 0x8B
        _emit 0x56
        _emit 0x04
        // mov edx, dword ptr [esi + 4]
        _emit 0x8D
        _emit 0x04
        _emit 0xAD
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        // lea eax, [ebp*4]
        _emit 0x8B
        _emit 0x0C
        _emit 0x10
        // mov ecx, dword ptr [eax + edx]
        _emit 0x89
        _emit 0x4F
        _emit 0x04
        // mov dword ptr [edi + 4], ecx
        _emit 0x8B
        _emit 0x56
        _emit 0x04
        // mov edx, dword ptr [esi + 4]
        _emit 0x89
        _emit 0x3C
        _emit 0x10
        // mov dword ptr [eax + edx], edi
        _emit 0xFF
        _emit 0x46
        _emit 0x0C
        // inc dword ptr [esi + 0xc]
        _emit 0x8B
        _emit 0x76
        _emit 0x04
        // mov esi, dword ptr [esi + 4]
        _emit 0x03
        _emit 0xF0
        // add esi, eax
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov eax, dword ptr [esp + 0x1c]
        _emit 0x89
        _emit 0x38
        // mov dword ptr [eax], edi
        _emit 0x5F
        // pop edi
        _emit 0x89
        _emit 0x70
        _emit 0x04
        // mov dword ptr [eax + 4], esi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0xC6
        _emit 0x40
        _emit 0x08
        _emit 0x01
        // mov byte ptr [eax + 8], 1
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
        _emit 0x8B
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // mov eax, dword ptr [esp + 0x1c]
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5D
        // pop ebp
        _emit 0x89
        _emit 0x08
        // mov dword ptr [eax], ecx
        _emit 0x89
        _emit 0x50
        _emit 0x04
        // mov dword ptr [eax + 4], edx
        _emit 0xC6
        _emit 0x40
        _emit 0x08
        _emit 0x00
        // mov byte ptr [eax + 8], 0
        _emit 0x5B
        // pop ebx
        _emit 0x83
        _emit 0xC4
        _emit 0x08
        // add esp, 8
        _emit 0xC2
        _emit 0x0C
        _emit 0x00
        // ret 0xc
    }
}

// @ 0x00b45c10  (137 bytes)
__declspec(naked) void FUN_00b45c10()
{
    __asm {
        _emit 0x53
        // push ebx
        _emit 0x8B
        _emit 0x5C
        _emit 0x24
        _emit 0x08
        // mov ebx, dword ptr [esp + 8]
        _emit 0x56
        // push esi
        _emit 0x57
        // push edi
        _emit 0x8B
        _emit 0xF9
        // mov edi, ecx
        _emit 0x8B
        _emit 0x4B
        _emit 0x04
        // mov ecx, dword ptr [ebx + 4]
        _emit 0x2B
        _emit 0x0B
        // sub ecx, dword ptr [ebx]
        _emit 0xB8
        _emit 0x89
        _emit 0x88
        _emit 0x88
        _emit 0x88
        // mov eax, 0x88888889
        _emit 0xF7
        _emit 0xE9
        // imul ecx
        _emit 0x03
        _emit 0xD1
        // add edx, ecx
        _emit 0xC1
        _emit 0xFA
        _emit 0x05
        // sar edx, 5
        _emit 0x8B
        _emit 0xF2
        // mov esi, edx
        _emit 0xC1
        _emit 0xEE
        _emit 0x1F
        // shr esi, 0x1f
        _emit 0x03
        _emit 0xF2
        // add esi, edx
        _emit 0x74
        _emit 0x29
        // je 0xb45c5c
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
        _emit 0x8B
        _emit 0xC6
        // mov eax, esi
        _emit 0xC1
        _emit 0xE0
        _emit 0x04
        // shl eax, 4
        _emit 0x6A
        _emit 0x00
        // push 0
        _emit 0x2B
        _emit 0xC6
        // sub eax, esi
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
        _emit 0xEB
        _emit 0x02
        // jmp 0xb45c5e
        _emit 0x33
        _emit 0xC0
        // xor eax, eax
        _emit 0x8B
        _emit 0xCE
        // mov ecx, esi
        _emit 0xC1
        _emit 0xE1
        _emit 0x04
        // shl ecx, 4
        _emit 0x2B
        _emit 0xCE
        // sub ecx, esi
        _emit 0x8D
        _emit 0x14
        _emit 0x88
        // lea edx, [eax + ecx*4]
        _emit 0x89
        _emit 0x57
        _emit 0x08
        // mov dword ptr [edi + 8], edx
        _emit 0x8B
        _emit 0x54
        _emit 0x24
        _emit 0x10
        // mov edx, dword ptr [esp + 0x10]
        _emit 0x52
        // push edx
        _emit 0x89
        _emit 0x07
        // mov dword ptr [edi], eax
        _emit 0x89
        _emit 0x47
        _emit 0x04
        // mov dword ptr [edi + 4], eax
        _emit 0x8B
        _emit 0x4B
        _emit 0x04
        // mov ecx, dword ptr [ebx + 4]
        _emit 0x8B
        _emit 0x1B
        // mov ebx, dword ptr [ebx]
        _emit 0x50
        // push eax
        _emit 0x51
        // push ecx
        _emit 0x8D
        _emit 0x44
        _emit 0x24
        _emit 0x1C
        // lea eax, [esp + 0x1c]
        _emit 0x53
        // push ebx
        _emit 0x50
        // push eax
        call FUN_00b3f260
        _emit 0x8B
        _emit 0x4C
        _emit 0x24
        _emit 0x24
        // mov ecx, dword ptr [esp + 0x24]
        _emit 0x83
        _emit 0xC4
        _emit 0x14
        // add esp, 0x14
        _emit 0x89
        _emit 0x4F
        _emit 0x04
        // mov dword ptr [edi + 4], ecx
        _emit 0x8B
        _emit 0xC7
        // mov eax, edi
        _emit 0x5F
        // pop edi
        _emit 0x5E
        // pop esi
        _emit 0x5B
        // pop ebx
        _emit 0xC2
        _emit 0x04
        _emit 0x00
        // ret 4
    }
}
