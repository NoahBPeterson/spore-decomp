// slice s0079f8d0
// Per-instruction reconstruction (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
// Control flow is decoded recursively; call targets are symbolic so COFF
// relocation bytes are masked by the verifier. Unreachable bytes are data.

extern "C" void EXT_424cf0();
extern "C" void EXT_537dc0();
extern "C" void EXT_7993a0();
extern "C" void EXT_799450();
extern "C" void EXT_799dc0();
extern "C" void EXT_79a4a0();
extern "C" void EXT_79a6c0();
extern "C" void EXT_79a710();
extern "C" void EXT_79a800();
extern "C" void EXT_79a8f0();
extern "C" void EXT_79aaa0();
extern "C" void EXT_79ab40();
extern "C" void EXT_79ae00();
extern "C" void EXT_79b0d0();
extern "C" void EXT_79b150();
extern "C" void EXT_79b190();
extern "C" void EXT_79b1c0();
extern "C" void EXT_79b2a0();
extern "C" void EXT_79b470();
extern "C" void EXT_79b6b0();
extern "C" void EXT_79f4e0();
extern "C" void EXT_79f640();
extern "C" void EXT_79f730();
extern "C" void EXT_79f770();
extern "C" void EXT_79f7b0();
extern "C" void EXT_79f8d0();
extern "C" void EXT_79fa20();
extern "C" void EXT_79fa70();
extern "C" void EXT_79fcc0();
extern "C" void EXT_79fef0();
extern "C" void EXT_7a0010();
extern "C" void EXT_f47380();
extern "C" void EXT_f473a0();
extern "C" void EXT_11e0744();

// @ 0x0079f8d0
__declspec(naked) void FUN_0079f8d0() {
  __asm {
    push ecx
    push ebx
    push esi
    mov esi, ecx
    mov eax, dword ptr [esi + 4]
    push edi
    cmp eax, dword ptr [esi + 8]
    _emit 0x74
    _emit 0x66  ; je 0x79f944
    mov ebx, dword ptr [esp + 18h]
    mov edi, dword ptr [esp + 14h]
    cmp ebx, edi
    _emit 0x72
    _emit 0x07  ; jb 0x79f8f1
    cmp ebx, eax
    _emit 0x73
    _emit 0x03  ; jae 0x79f8f1
    add ebx, 78h
    test eax, eax
    _emit 0x74
    _emit 0x11  ; je 0x79f906
    mov ecx, dword ptr [eax - 78h]
    lea edx, [eax - 74h]
    mov dword ptr [eax], ecx
    push edx
    lea ecx, [eax + 4]
    call EXT_799450
    mov eax, dword ptr [esi + 4]
    push eax
    add eax, -78h
    push eax
    push edi
    call EXT_79aaa0
    mov eax, dword ptr [ebx]
    mov dword ptr [edi], eax
    mov cl, byte ptr [ebx + 4]
    add esp, 0ch
    lea edx, [ebx + 8]
    mov byte ptr [edi + 4], cl
    push edx
    lea ecx, [edi + 8]
    call EXT_537dc0
    add ebx, 40h
    push ebx
    lea ecx, [edi + 40h]
    call EXT_537dc0
    add dword ptr [esi + 4], 78h
    pop edi
    pop esi
    pop ebx
    pop ecx
    ret 8
    sub eax, dword ptr [esi]
    mov ecx, eax
    mov eax, 88888889h
    imul ecx
    add edx, ecx
    sar edx, 6
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    _emit 0x74
    _emit 0x37  ; je 0x79f994
    add eax, eax
    mov dword ptr [esp + 0ch], eax
    test eax, eax
    _emit 0x74
    _emit 0x3b  ; je 0x79f9a2
    push 0d1h
    mov ecx, eax
    shl ecx, 4
    push 13ebb38h
    sub ecx, eax
    push 0
    add ecx, ecx
    push 0
    add ecx, ecx
    add ecx, ecx
    push 13eb8a4h
    push ecx
    call EXT_f473a0
    add esp, 18h
    mov ebx, eax
    _emit 0xeb
    _emit 0x10  ; jmp 0x79f9a4
    mov dword ptr [esp + 0ch], 1
    mov eax, dword ptr [esp + 0ch]
    _emit 0xeb
    _emit 0xc5  ; jmp 0x79f967
    xor ebx, ebx
    mov eax, dword ptr [esi]
    push ebp
    mov ebp, dword ptr [esp + 18h]
    push ebx
    push ebp
    push eax
    call EXT_799dc0
    mov edi, eax
    add esp, 0ch
    test edi, edi
    _emit 0x74
    _emit 0x14  ; je 0x79f9d0
    mov eax, dword ptr [esp + 1ch]
    mov edx, dword ptr [eax]
    add eax, 4
    push eax
    lea ecx, [edi + 4]
    mov dword ptr [edi], edx
    call EXT_799450
    mov eax, dword ptr [esi + 4]
    add edi, 78h
    push edi
    push eax
    push ebp
    call EXT_799dc0
    mov edi, eax
    mov eax, dword ptr [esi]
    add esp, 0ch
    pop ebp
    test eax, eax
    _emit 0x74
    _emit 0x0f  ; je 0x79f9f9
    cmp dword ptr [eax - 4], 0
    _emit 0x74
    _emit 0x09  ; je 0x79f9f9
    push eax
    call EXT_f47380
    add esp, 4
    mov eax, dword ptr [esp + 0ch]
    mov ecx, eax
    shl ecx, 4
    sub ecx, eax
    mov dword ptr [esi + 4], edi
    lea edx, [ebx + ecx*8]
    pop edi
    mov dword ptr [esi], ebx
    mov dword ptr [esi + 8], edx
    pop esi
    pop ebx
    pop ecx
    ret 8
  }
}

// @ 0x0079fa70
__declspec(naked) void FUN_0079fa70() {
  __asm {
    push -1
    _emit 0x64
    _emit 0xa1
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov eax, dword ptr fs:[0]
    push 120c068h
    push eax
    _emit 0x64
    _emit 0x89
    _emit 0x25
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], esp
    sub esp, 18h
    push ebx
    push ebp
    push esi
    mov esi, ecx
    mov ecx, dword ptr [esi + 4]
    mov edx, dword ptr [esi + 8]
    sub edx, ecx
    mov eax, 66666667h
    imul edx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    push edi
    mov edi, dword ptr [esp + 3ch]
    add eax, edx
    cmp edi, eax
    _emit 0x0f
    _emit 0x87
    _emit 0xfa
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; ja 0x79fbad
    test edi, edi
    _emit 0x0f
    _emit 0x86
    _emit 0xea
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jbe 0x79fca5
    mov ecx, dword ptr [esp + 40h]
    push ecx
    lea ecx, [esp + 18h]
    call EXT_79a6c0
    mov ecx, dword ptr [esi + 4]
    sub ecx, dword ptr [esp + 38h]
    mov ebp, dword ptr [esi + 4]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov ebx, edx
    shr ebx, 1fh
    add ebx, edx
    mov edx, dword ptr [esp + 38h]
    mov dword ptr [esp + 30h], 0
    push edx
    cmp edi, ebx
    _emit 0x73
    _emit 0x3a  ; jae 0x79fb2f
    lea edi, [edi + edi*4]
    add edi, edi
    push ebp
    add edi, edi
    mov ebx, ebp
    push ebp
    sub ebx, edi
    lea eax, [esp + 4ch]
    push ebx
    push eax
    call EXT_79a800
    add dword ptr [esi + 4], edi
    mov esi, dword ptr [esp + 4ch]
    push ebp
    push ebx
    push esi
    call EXT_79ab40
    lea ecx, [esp + 34h]
    push ecx
    add edi, esi
    push edi
    push esi
    call EXT_79b190
    add esp, 2ch
    _emit 0xeb
    _emit 0x4a  ; jmp 0x79fb79
    lea eax, [esp + 18h]
    push eax
    sub edi, ebx
    push edi
    push ebp
    call EXT_79a8f0
    mov edx, dword ptr [esp + 48h]
    lea ecx, [edi + edi*4]
    mov edi, dword ptr [esp + 48h]
    add ecx, ecx
    add ecx, ecx
    add dword ptr [esi + 4], ecx
    mov eax, dword ptr [esi + 4]
    push edx
    push eax
    push ebp
    lea eax, [esp + 54h]
    push edi
    push eax
    call EXT_79a800
    lea edx, [esp + 38h]
    push edx
    lea ecx, [ebx + ebx*4]
    add ecx, ecx
    add ecx, ecx
    add dword ptr [esi + 4], ecx
    push ebp
    push edi
    call EXT_79b190
    add esp, 30h
    mov eax, dword ptr [esp + 14h]
    test eax, eax
    _emit 0x0f
    _emit 0x84
    _emit 0x20
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x79fca5
    cmp dword ptr [eax - 4], 0
    _emit 0x0f
    _emit 0x84
    _emit 0x16
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x79fca5
    push eax
    call EXT_f47380
    add esp, 4
    pop edi
    pop esi
    pop ebp
    pop ebx
    mov ecx, dword ptr [esp + 18h]
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 24h
    ret 0ch
    sub ecx, dword ptr [esi]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    lea ecx, [eax + eax]
    _emit 0x75
    _emit 0x05  ; jne 0x79fbca
    mov ecx, 1
    add eax, edi
    cmp ecx, eax
    _emit 0x76
    _emit 0x02  ; jbe 0x79fbd2
    mov eax, ecx
    mov dword ptr [esp + 10h], eax
    test eax, eax
    _emit 0x74
    _emit 0x29  ; je 0x79fc03
    push 0d1h
    push 13ebb38h
    push 0
    lea eax, [eax + eax*4]
    push 0
    add eax, eax
    add eax, eax
    push 13eb8a4h
    push eax
    call EXT_f473a0
    add esp, 18h
    mov dword ptr [esp + 3ch], eax
    _emit 0xeb
    _emit 0x08  ; jmp 0x79fc0b
    mov dword ptr [esp + 3ch], 0
    mov eax, dword ptr [esi]
    mov ebp, dword ptr [esp + 38h]
    mov ecx, dword ptr [esp + 3ch]
    mov ebx, ebp
    sub ebx, eax
    push ebx
    push eax
    push ecx
    call EXT_11e0744
    mov ecx, eax
    mov eax, 66666667h
    imul ebx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    lea edx, [eax + eax*4]
    mov eax, dword ptr [esp + 44h]
    lea ebx, [ecx + edx*4]
    mov ecx, dword ptr [esp + 4ch]
    push eax
    push ecx
    push edi
    push ebx
    call EXT_79a8f0
    lea edx, [edi + edi*4]
    mov edi, dword ptr [esi + 4]
    sub edi, ebp
    push edi
    lea eax, [ebx + edx*4]
    push ebp
    push eax
    call EXT_11e0744
    mov ecx, eax
    mov eax, 66666667h
    imul edi
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    lea edx, [eax + eax*4]
    mov eax, dword ptr [esi]
    add esp, 28h
    lea edi, [ecx + edx*4]
    test eax, eax
    _emit 0x74
    _emit 0x0f  ; je 0x79fc8f
    cmp dword ptr [eax - 4], 0
    _emit 0x74
    _emit 0x09  ; je 0x79fc8f
    push eax
    call EXT_f47380
    add esp, 4
    mov ecx, dword ptr [esp + 10h]
    mov eax, dword ptr [esp + 3ch]
    lea ecx, [ecx + ecx*4]
    lea edx, [eax + ecx*4]
    mov dword ptr [esi], eax
    mov dword ptr [esi + 4], edi
    mov dword ptr [esi + 8], edx
    mov ecx, dword ptr [esp + 28h]
    pop edi
    pop esi
    pop ebp
    pop ebx
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 24h
    ret 0ch
  }
}

// @ 0x0079fd20
__declspec(naked) void FUN_0079fd20() {
  __asm {
    push -1
    push 1213bd1h
    _emit 0x64
    _emit 0xa1
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov eax, dword ptr fs:[0]
    push eax
    _emit 0x64
    _emit 0x89
    _emit 0x25
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], esp
    sub esp, 10h
    push ebx
    xor ebx, ebx
    push ebp
    mov dword ptr [esp + 8], ebx
    push esi
    mov esi, dword ptr [esp + 2ch]
    push edi
    mov dword ptr [esi], ebx
    mov dword ptr [esi + 4], ebx
    mov dword ptr [esi + 8], ebx
    mov eax, dword ptr [esp + 34h]
    mov ebp, dword ptr [eax + 4]
    sub ebp, dword ptr [eax]
    xor edi, edi
    sar ebp, 2
    mov dword ptr [esp + 28h], ebx
    mov dword ptr [esp + 10h], 1
    cmp ebp, ebx
    _emit 0x0f
    _emit 0x86
    _emit 0x9b
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; jbe 0x79fe0b
    _emit 0xeb
    _emit 0x06  ; jmp 0x79fd78
    mov eax, dword ptr [esp + 34h]
    xor ebx, ebx
    mov eax, dword ptr [eax]
    mov ecx, dword ptr [eax + edi*4]
    lea eax, [eax + edi*4]
    mov dword ptr [esp + 18h], ecx
    cmp ecx, ebx
    _emit 0x74
    _emit 0x0c  ; je 0x79fd94
    lea edx, [ecx + 4]
    mov eax, 1
    lock xadd dword ptr [edx], eax
    mov dword ptr [esp + 1ch], edi
    mov eax, dword ptr [esi + 4]
    mov dword ptr [esp + 28h], 1
    cmp eax, dword ptr [esi + 8]
    _emit 0x73
    _emit 0x23  ; jae 0x79fdcb
    lea edx, [eax + 8]
    mov dword ptr [esi + 4], edx
    cmp eax, ebx
    _emit 0x74
    _emit 0x2a  ; je 0x79fddc
    mov dword ptr [eax], ecx
    cmp ecx, ebx
    _emit 0x74
    _emit 0x0c  ; je 0x79fdc4
    lea edx, [ecx + 4]
    mov ebx, 1
    lock xadd dword ptr [edx], ebx
    mov dword ptr [eax + 4], edi
    xor ebx, ebx
    _emit 0xeb
    _emit 0x11  ; jmp 0x79fddc
    lea ecx, [esp + 18h]
    push ecx
    push eax
    mov ecx, esi
    call EXT_79f4e0
    mov ecx, dword ptr [esp + 18h]
    mov byte ptr [esp + 28h], bl
    cmp ecx, ebx
    _emit 0x74
    _emit 0x1e  ; je 0x79fe02
    lea eax, [ecx + 4]
    mov edx, eax
    or ebx, 0ffffffffh
    lock xadd dword ptr [edx], ebx
    dec ebx
    _emit 0x75
    _emit 0x0f  ; jne 0x79fe02
    mov edx, 1
    xchg dword ptr [eax], edx
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax]
    push 1
    call edx
    inc edi
    cmp edi, ebp
    _emit 0x0f
    _emit 0x82
    _emit 0x67
    _emit 0xff
    _emit 0xff
    _emit 0xff  ; jb 0x79fd72
    mov ecx, dword ptr [esp + 20h]
    pop edi
    mov eax, esi
    pop esi
    pop ebp
    pop ebx
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 1ch
    ret
  }
}

// @ 0x0079fe20
__declspec(naked) void FUN_0079fe20() {
  __asm {
    _emit 0x64
    _emit 0xa1
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov eax, dword ptr fs:[0]
    push -1
    push 1213bf9h
    push eax
    _emit 0x64
    _emit 0x89
    _emit 0x25
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], esp
    mov eax, dword ptr [ecx + 4]
    sub esp, 28h
    push esi
    cmp eax, dword ptr [ecx + 8]
    _emit 0x73
    _emit 0x44  ; jae 0x79fe85
    lea edx, [eax + 20h]
    mov dword ptr [ecx + 4], edx
    xor esi, esi
    cmp eax, esi
    _emit 0x0f
    _emit 0x84
    _emit 0x8c
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x79fedd
    mov dword ptr [eax], esi
    mov dword ptr [eax + 4], esi
    mov dword ptr [eax + 8], esi
    mov dword ptr [eax + 0ch], 0eh
    xor ecx, ecx
    xor edx, edx
    mov dword ptr [eax + 10h], esi
    mov dword ptr [eax + 14h], esi
    mov word ptr [eax + 18h], cx
    mov word ptr [eax + 1ah], dx
    mov dword ptr [eax + 1ch], esi
    pop esi
    mov ecx, dword ptr [esp + 28h]
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 34h
    ret
    xor esi, esi
    xor edx, edx
    mov dword ptr [esp + 0ch], esi
    mov dword ptr [esp + 10h], esi
    mov dword ptr [esp + 14h], esi
    mov dword ptr [esp + 18h], 0eh
    mov dword ptr [esp + 1ch], esi
    mov dword ptr [esp + 20h], esi
    mov word ptr [esp + 24h], dx
    mov word ptr [esp + 26h], dx
    mov dword ptr [esp + 28h], esi
    lea edx, [esp + 0ch]
    push edx
    push eax
    mov dword ptr [esp + 3ch], 1
    call EXT_424cf0
    mov ecx, dword ptr [esp + 28h]
    mov dword ptr [esp + 34h], 0ffffffffh
    cmp ecx, esi
    _emit 0x74
    _emit 0x07  ; je 0x79fedd
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax + 4]
    call edx
    mov ecx, dword ptr [esp + 2ch]
    pop esi
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 34h
    ret
  }
}

// @ 0x0079fef0
__declspec(naked) void FUN_0079fef0() {
  __asm {
    sub esp, 78h
    push esi
    mov esi, ecx
    mov eax, dword ptr [esi + 4]
    cmp eax, dword ptr [esi + 8]
    _emit 0x73
    _emit 0x1c  ; jae 0x79ff1a
    lea ecx, [eax + 78h]
    mov dword ptr [esi + 4], ecx
    test eax, eax
    _emit 0x74
    _emit 0x33  ; je 0x79ff3b
    mov dword ptr [eax], 0fffffffeh
    lea ecx, [eax + 4]
    pop esi
    add esp, 78h
    jmp EXT_7993a0
    lea ecx, [esp + 8]
    mov dword ptr [esp + 4], 0fffffffeh
    call EXT_7993a0
    mov eax, dword ptr [esi + 4]
    lea edx, [esp + 4]
    push edx
    push eax
    mov ecx, esi
    call EXT_79f8d0
    pop esi
    add esp, 78h
    ret
  }
}

// @ 0x0079ff40
__declspec(naked) void FUN_0079ff40() {
  __asm {
    sub esp, 0ech
    push ebx
    mov ebx, ecx
    push esi
    mov esi, dword ptr [ebx]
    push edi
    lea edi, [ebx + 4]
    test esi, esi
    _emit 0x7e
    _emit 0x1d  ; jle 0x79ff71
    mov ecx, dword ptr [edi]
    mov eax, esi
    shl eax, 4
    sub eax, esi
    add eax, eax
    add eax, eax
    add eax, eax
    mov edx, dword ptr [ecx + eax]
    mov dword ptr [ebx], edx
    mov dword ptr [ecx + eax], 0fffffffeh
    _emit 0xeb
    _emit 0x1f  ; jmp 0x79ff90
    mov ecx, dword ptr [edi + 4]
    sub ecx, dword ptr [edi]
    mov eax, 88888889h
    imul ecx
    add edx, ecx
    sar edx, 6
    mov esi, edx
    shr esi, 1fh
    mov ecx, edi
    add esi, edx
    call EXT_79fef0
    mov eax, dword ptr [esp + 0fch]
    push eax
    lea ecx, [esp + 88h]
    call EXT_799450
    lea ecx, [esp + 84h]
    push ecx
    lea ecx, [esp + 14h]
    mov dword ptr [esp + 10h], 0fffffffeh
    call EXT_799450
    mov eax, dword ptr [edi]
    mov ecx, dword ptr [esp + 0ch]
    mov edx, esi
    shl edx, 4
    sub edx, esi
    lea edi, [eax + edx*8]
    mov dl, byte ptr [esp + 10h]
    mov dword ptr [edi], ecx
    lea eax, [esp + 14h]
    push eax
    lea ecx, [edi + 8]
    mov byte ptr [edi + 4], dl
    call EXT_537dc0
    lea ecx, [esp + 4ch]
    push ecx
    lea ecx, [edi + 40h]
    call EXT_537dc0
    inc dword ptr [ebx + 18h]
    pop edi
    mov eax, esi
    pop esi
    pop ebx
    add esp, 0ech
    ret 4
  }
}

// @ 0x007a0010
__declspec(naked) void FUN_007a0010() {
  __asm {
    _emit 0x64
    _emit 0xa1
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov eax, dword ptr fs:[0]
    push -1
    push 120c068h
    push eax
    _emit 0x64
    _emit 0x89
    _emit 0x25
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], esp
    sub esp, 14h
    push ebx
    mov ebx, dword ptr [ecx + 4]
    push esi
    mov esi, dword ptr [esp + 2ch]
    push edi
    mov edi, dword ptr [ecx]
    mov edx, ebx
    sub edx, edi
    mov eax, 66666667h
    imul edx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    cmp esi, eax
    _emit 0x76
    _emit 0x49  ; jbe 0x7a0096
    xor eax, eax
    mov dword ptr [esp + 0ch], eax
    mov dword ptr [esp + 10h], eax
    mov dword ptr [esp + 14h], eax
    mov dword ptr [esp + 28h], eax
    lea edx, [esp + 0ch]
    push edx
    mov edx, ebx
    sub edx, edi
    mov eax, 66666667h
    imul edx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    sub esi, eax
    push esi
    push ebx
    call EXT_79fa70
    pop edi
    pop esi
    pop ebx
    mov ecx, dword ptr [esp + 14h]
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 20h
    ret 4
    lea edx, [esi + esi*4]
    push ebx
    lea eax, [edi + edx*4]
    push eax
    call EXT_79fa20
    mov ecx, dword ptr [esp + 20h]
    pop edi
    pop esi
    pop ebx
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 20h
    ret 4
  }
}

// @ 0x007a0110
__declspec(naked) void FUN_007a0110() {
  __asm {
    push -1
    _emit 0x64
    _emit 0xa1
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov eax, dword ptr fs:[0]
    push 120c068h
    push eax
    _emit 0x64
    _emit 0x89
    _emit 0x25
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], esp
    sub esp, 18h
    push ebx
    push ebp
    push esi
    mov esi, ecx
    mov ecx, dword ptr [esi + 4]
    mov edx, dword ptr [esi + 8]
    sub edx, ecx
    mov eax, 66666667h
    imul edx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    push edi
    mov edi, dword ptr [esp + 3ch]
    add eax, edx
    cmp edi, eax
    _emit 0x0f
    _emit 0x87
    _emit 0xfa
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; ja 0x7a024d
    test edi, edi
    _emit 0x0f
    _emit 0x86
    _emit 0xea
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jbe 0x7a0345
    mov ecx, dword ptr [esp + 40h]
    push ecx
    lea ecx, [esp + 18h]
    call EXT_79b150
    mov ecx, dword ptr [esi + 4]
    sub ecx, dword ptr [esp + 38h]
    mov ebp, dword ptr [esi + 4]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov ebx, edx
    shr ebx, 1fh
    add ebx, edx
    mov edx, dword ptr [esp + 38h]
    mov dword ptr [esp + 30h], 0
    push edx
    cmp edi, ebx
    _emit 0x73
    _emit 0x3a  ; jae 0x7a01cf
    lea edi, [edi + edi*4]
    add edi, edi
    push ebp
    add edi, edi
    mov ebx, ebp
    push ebp
    sub ebx, edi
    lea eax, [esp + 4ch]
    push ebx
    push eax
    call EXT_79b1c0
    add dword ptr [esi + 4], edi
    mov esi, dword ptr [esp + 4ch]
    push ebp
    push ebx
    push esi
    call EXT_79b470
    lea ecx, [esp + 34h]
    push ecx
    add edi, esi
    push edi
    push esi
    call EXT_79fcc0
    add esp, 2ch
    _emit 0xeb
    _emit 0x4a  ; jmp 0x7a0219
    lea eax, [esp + 18h]
    push eax
    sub edi, ebx
    push edi
    push ebp
    call EXT_79b2a0
    mov edx, dword ptr [esp + 48h]
    lea ecx, [edi + edi*4]
    mov edi, dword ptr [esp + 48h]
    add ecx, ecx
    add ecx, ecx
    add dword ptr [esi + 4], ecx
    mov eax, dword ptr [esi + 4]
    push edx
    push eax
    push ebp
    lea eax, [esp + 54h]
    push edi
    push eax
    call EXT_79b1c0
    lea edx, [esp + 38h]
    push edx
    lea ecx, [ebx + ebx*4]
    add ecx, ecx
    add ecx, ecx
    add dword ptr [esi + 4], ecx
    push ebp
    push edi
    call EXT_79fcc0
    add esp, 30h
    mov eax, dword ptr [esp + 14h]
    test eax, eax
    _emit 0x0f
    _emit 0x84
    _emit 0x20
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x7a0345
    cmp dword ptr [eax - 4], 0
    _emit 0x0f
    _emit 0x84
    _emit 0x16
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x7a0345
    push eax
    call EXT_f47380
    add esp, 4
    pop edi
    pop esi
    pop ebp
    pop ebx
    mov ecx, dword ptr [esp + 18h]
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 24h
    ret 0ch
    sub ecx, dword ptr [esi]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    lea ecx, [eax + eax]
    _emit 0x75
    _emit 0x05  ; jne 0x7a026a
    mov ecx, 1
    add eax, edi
    cmp ecx, eax
    _emit 0x76
    _emit 0x02  ; jbe 0x7a0272
    mov eax, ecx
    mov dword ptr [esp + 10h], eax
    test eax, eax
    _emit 0x74
    _emit 0x29  ; je 0x7a02a3
    push 0d1h
    push 13ebb38h
    push 0
    lea eax, [eax + eax*4]
    push 0
    add eax, eax
    add eax, eax
    push 13eb8a4h
    push eax
    call EXT_f473a0
    add esp, 18h
    mov dword ptr [esp + 3ch], eax
    _emit 0xeb
    _emit 0x08  ; jmp 0x7a02ab
    mov dword ptr [esp + 3ch], 0
    mov eax, dword ptr [esi]
    mov ebp, dword ptr [esp + 38h]
    mov ecx, dword ptr [esp + 3ch]
    mov ebx, ebp
    sub ebx, eax
    push ebx
    push eax
    push ecx
    call EXT_11e0744
    mov ecx, eax
    mov eax, 66666667h
    imul ebx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    lea edx, [eax + eax*4]
    mov eax, dword ptr [esp + 44h]
    lea ebx, [ecx + edx*4]
    mov ecx, dword ptr [esp + 4ch]
    push eax
    push ecx
    push edi
    push ebx
    call EXT_79b2a0
    lea edx, [edi + edi*4]
    mov edi, dword ptr [esi + 4]
    sub edi, ebp
    push edi
    lea eax, [ebx + edx*4]
    push ebp
    push eax
    call EXT_11e0744
    mov ecx, eax
    mov eax, 66666667h
    imul edi
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    lea edx, [eax + eax*4]
    mov eax, dword ptr [esi]
    add esp, 28h
    lea edi, [ecx + edx*4]
    test eax, eax
    _emit 0x74
    _emit 0x0f  ; je 0x7a032f
    cmp dword ptr [eax - 4], 0
    _emit 0x74
    _emit 0x09  ; je 0x7a032f
    push eax
    call EXT_f47380
    add esp, 4
    mov ecx, dword ptr [esp + 10h]
    mov eax, dword ptr [esp + 3ch]
    lea ecx, [ecx + ecx*4]
    lea edx, [eax + ecx*4]
    mov dword ptr [esi], eax
    mov dword ptr [esi + 4], edi
    mov dword ptr [esi + 8], edx
    mov ecx, dword ptr [esp + 28h]
    pop edi
    pop esi
    pop ebp
    pop ebx
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 24h
    ret 0ch
  }
}

// @ 0x007a0360
__declspec(naked) void FUN_007a0360() {
  __asm {
    sub esp, 8
    push esi
    mov esi, dword ptr [esp + 10h]
    mov ecx, dword ptr [esi + 4]
    sub ecx, dword ptr [esi]
    mov eax, 66666667h
    imul ecx
    mov ecx, dword ptr [esp + 14h]
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    push eax
    call EXT_7a0010
    mov ecx, dword ptr [esi + 4]
    sub ecx, dword ptr [esi]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    test eax, eax
    _emit 0x7e
    _emit 0x61  ; jle 0x7a0403
    push ebx
    push ebp
    xor ecx, ecx
    push edi
    mov dword ptr [esp + 10h], ecx
    mov dword ptr [esp + 14h], eax
    _emit 0xeb
    _emit 0x08  ; jmp 0x7a03b9
    mov esi, dword ptr [esp + 1ch]
    mov ecx, dword ptr [esp + 10h]
    mov edx, dword ptr [esp + 20h]
    mov ebx, dword ptr [edx]
    mov edi, dword ptr [esi]
    add ebx, ecx
    push ebx
    add edi, ecx
    call EXT_79f7b0
    mov esi, dword ptr [edi + 4]
    sub esi, dword ptr [edi]
    add esp, 4
    sar esi, 3
    xor ebp, ebp
    test esi, esi
    _emit 0x7e
    _emit 0x18  ; jle 0x7a03f4
    _emit 0x8d
    _emit 0x64
    _emit 0x24
    _emit 0x00  ; lea esp, [esp]
    mov eax, dword ptr [edi]
    lea ecx, [eax + ebp*8]
    push ecx
    push ebx
    call EXT_79b6b0
    inc ebp
    add esp, 8
    cmp ebp, esi
    _emit 0x7c
    _emit 0xec  ; jl 0x7a03e0
    add dword ptr [esp + 10h], 14h
    sub dword ptr [esp + 14h], 1
    _emit 0x75
    _emit 0xb1  ; jne 0x7a03b1
    pop edi
    pop ebp
    pop ebx
    pop esi
    add esp, 8
    ret
  }
}

// @ 0x007a0410
__declspec(naked) void FUN_007a0410() {
  __asm {
    push edi
    mov edi, dword ptr [esp + 8]
    mov ecx, dword ptr [edi + 4]
    sub ecx, dword ptr [edi]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    test eax, eax
    _emit 0x7e
    _emit 0x1d  ; jle 0x7a044c
    push ebx
    push esi
    xor esi, esi
    mov ebx, eax
    mov eax, dword ptr [edi]
    add eax, esi
    push eax
    call EXT_79f7b0
    add esp, 4
    add esi, 14h
    sub ebx, 1
    _emit 0x75
    _emit 0xeb  ; jne 0x7a0435
    pop esi
    pop ebx
    push 0
    mov ecx, edi
    call EXT_7a0010
    pop edi
    ret
  }
}

// @ 0x007a0460
__declspec(naked) void FUN_007a0460() {
  __asm {
    push ebp
    mov ebp, dword ptr [esp + 8]
    push esi
    mov esi, ecx
    cmp ebp, esi
    _emit 0x0f
    _emit 0x84
    _emit 0x2b
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x7a059b
    mov edx, dword ptr [ebp + 4]
    mov ecx, dword ptr [ebp]
    sub edx, ecx
    mov eax, 66666667h
    imul edx
    sar edx, 3
    push ebx
    mov ebx, dword ptr [esi]
    push edi
    mov edi, edx
    shr edi, 1fh
    add edi, edx
    mov edx, dword ptr [esi + 8]
    sub edx, ebx
    mov eax, 66666667h
    imul edx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    cmp edi, eax
    _emit 0x76
    _emit 0x51  ; jbe 0x7a04f8
    mov edx, dword ptr [ebp + 4]
    push edx
    push ecx
    push edi
    mov ecx, esi
    call EXT_79ae00
    mov ecx, dword ptr [esi]
    mov ebx, eax
    mov eax, dword ptr [esi + 4]
    push eax
    push ecx
    mov ecx, esi
    call EXT_79b0d0
    mov eax, dword ptr [esi]
    test eax, eax
    _emit 0x74
    _emit 0x0f  ; je 0x7a04d9
    cmp dword ptr [eax - 4], 0
    _emit 0x74
    _emit 0x09  ; je 0x7a04d9
    push eax
    call EXT_f47380
    add esp, 4
    lea edx, [edi + edi*4]
    lea eax, [ebx + edx*4]
    mov dword ptr [esi + 8], eax
    mov eax, ebx
    lea edx, [edi + edi*4]
    pop edi
    mov dword ptr [esi], ebx
    lea ecx, [eax + edx*4]
    pop ebx
    mov dword ptr [esi + 4], ecx
    mov eax, esi
    pop esi
    pop ebp
    ret 4
    mov edx, dword ptr [esi + 4]
    sub edx, ebx
    mov eax, 66666667h
    imul edx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    push ebx
    cmp edi, eax
    _emit 0x76
    _emit 0x62  ; jbe 0x7a0575
    lea edx, [eax + eax*4]
    lea eax, [ecx + edx*4]
    push eax
    push ecx
    call EXT_79f730
    mov ecx, dword ptr [ebp + 4]
    mov ebx, dword ptr [esi + 4]
    mov dword ptr [esp + 20h], ecx
    mov ecx, ebx
    sub ecx, dword ptr [esi]
    mov eax, 66666667h
    imul ecx
    mov ecx, dword ptr [esp + 20h]
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    lea edx, [eax + eax*4]
    mov eax, dword ptr [ebp]
    push ecx
    lea eax, [eax + edx*4]
    mov edx, dword ptr [esp + 24h]
    push ebx
    push edx
    push eax
    lea eax, [esp + 30h]
    push eax
    call EXT_79a710
    mov eax, dword ptr [esi]
    add esp, 20h
    lea edx, [edi + edi*4]
    pop edi
    lea ecx, [eax + edx*4]
    pop ebx
    mov dword ptr [esi + 4], ecx
    mov eax, esi
    pop esi
    pop ebp
    ret 4
    mov edx, dword ptr [ebp + 4]
    push edx
    push ecx
    call EXT_79f730
    mov ecx, dword ptr [esi + 4]
    add esp, 0ch
    push ecx
    push eax
    mov ecx, esi
    call EXT_79b0d0
    mov eax, dword ptr [esi]
    lea edx, [edi + edi*4]
    lea ecx, [eax + edx*4]
    pop edi
    mov dword ptr [esi + 4], ecx
    pop ebx
    mov eax, esi
    pop esi
    pop ebp
    ret 4
  }
}

// @ 0x007a0600
__declspec(naked) void FUN_007a0600() {
  __asm {
    push -1
    push 1219c95h
    _emit 0x64
    _emit 0xa1
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov eax, dword ptr fs:[0]
    push eax
    _emit 0x64
    _emit 0x89
    _emit 0x25
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], esp
    sub esp, 0ch
    push ebx
    push esi
    mov esi, ecx
    mov eax, dword ptr [esi + 4]
    push edi
    mov dword ptr [esp + 10h], esi
    cmp eax, dword ptr [esi + 8]
    _emit 0x74
    _emit 0x69  ; je 0x7a0692
    mov ecx, dword ptr [esp + 2ch]
    mov edi, dword ptr [esp + 28h]
    mov ebx, ecx
    cmp ecx, edi
    _emit 0x72
    _emit 0x07  ; jb 0x7a063e
    cmp ecx, eax
    _emit 0x73
    _emit 0x03  ; jae 0x7a063e
    lea ebx, [ecx + 14h]
    mov dword ptr [esp + 28h], eax
    mov dword ptr [esp + 20h], 0
    test eax, eax
    _emit 0x74
    _emit 0x0b  ; je 0x7a0659
    lea ecx, [eax - 14h]
    push ecx
    mov ecx, eax
    call EXT_79a4a0
    mov eax, dword ptr [esi + 4]
    push eax
    add eax, -14h
    push eax
    push edi
    mov dword ptr [esp + 2ch], 0ffffffffh
    call EXT_79f770
    add esp, 0ch
    push ebx
    mov ecx, edi
    call EXT_79f640
    add dword ptr [esi + 4], 14h
    pop edi
    pop esi
    pop ebx
    mov ecx, dword ptr [esp + 0ch]
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 18h
    ret 8
    sub eax, dword ptr [esi]
    mov ebx, 1
    mov ecx, eax
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    _emit 0x74
    _emit 0x33  ; je 0x7a06e1
    add eax, eax
    mov dword ptr [esp + 10h], eax
    test eax, eax
    _emit 0x74
    _emit 0x31  ; je 0x7a06e9
    push 0d1h
    push 13ebb38h
    lea eax, [eax + eax*4]
    push 0
    add eax, eax
    push 0
    add eax, eax
    push 13eb8a4h
    push eax
    call EXT_f473a0
    add esp, 18h
    mov dword ptr [esp + 0ch], eax
    _emit 0xeb
    _emit 0x10  ; jmp 0x7a06f1
    mov dword ptr [esp + 10h], ebx
    mov eax, ebx
    _emit 0xeb
    _emit 0xcf  ; jmp 0x7a06b8
    mov dword ptr [esp + 0ch], 0
    mov eax, dword ptr [esi]
    mov edx, dword ptr [esp + 0ch]
    push ebp
    mov ebp, dword ptr [esp + 2ch]
    mov edi, ebp
    sub edi, eax
    push edi
    push eax
    push edx
    call EXT_11e0744
    mov ecx, eax
    mov eax, 66666667h
    imul edi
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    lea edx, [eax + eax*4]
    lea edi, [ecx + edx*4]
    add esp, 0ch
    mov dword ptr [esp + 2ch], edi
    mov dword ptr [esp + 18h], edi
    mov dword ptr [esp + 24h], ebx
    test edi, edi
    _emit 0x74
    _emit 0x0c  ; je 0x7a0740
    mov eax, dword ptr [esp + 30h]
    push eax
    mov ecx, edi
    call EXT_79a4a0
    mov ebx, dword ptr [esi + 4]
    sub ebx, ebp
    push ebx
    add edi, 14h
    push ebp
    push edi
    call EXT_11e0744
    mov ecx, eax
    mov eax, 66666667h
    imul ebx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    lea edx, [eax + eax*4]
    mov eax, dword ptr [esi]
    add esp, 0ch
    lea edi, [ecx + edx*4]
    pop ebp
    test eax, eax
    _emit 0x74
    _emit 0x0f  ; je 0x7a0782
    cmp dword ptr [eax - 4], 0
    _emit 0x74
    _emit 0x09  ; je 0x7a0782
    push eax
    call EXT_f47380
    add esp, 4
    mov ecx, dword ptr [esp + 10h]
    mov eax, dword ptr [esp + 0ch]
    lea ecx, [ecx + ecx*4]
    mov dword ptr [esi + 4], edi
    lea edx, [eax + ecx*4]
    mov ecx, dword ptr [esp + 18h]
    pop edi
    mov dword ptr [esi], eax
    mov dword ptr [esi + 8], edx
    pop esi
    pop ebx
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 18h
    ret 8
  }
}


