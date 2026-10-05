// slice s007a07b0
// Per-instruction reconstruction (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
// Control flow is decoded recursively; call targets are symbolic so COFF
// relocation bytes are masked by the verifier. Unreachable bytes are data.

extern "C" void EXT_41eb80();
extern "C" void EXT_424f70();
extern "C" void EXT_432de0();
extern "C" void EXT_432e80();
extern "C" void EXT_475320();
extern "C" void EXT_705250();
extern "C" void EXT_719170();
extern "C" void EXT_71f7e0();
extern "C" void EXT_720190();
extern "C" void EXT_7201d0();
extern "C" void EXT_73eb90();
extern "C" void EXT_73eca0();
extern "C" void EXT_73ede0();
extern "C" void EXT_799e70();
extern "C" void EXT_79a3f0();
extern "C" void EXT_79a4a0();
extern "C" void EXT_79a4f0();
extern "C" void EXT_79a710();
extern "C" void EXT_79a9d0();
extern "C" void EXT_79b020();
extern "C" void EXT_79b0d0();
extern "C" void EXT_79f730();
extern "C" void EXT_79f770();
extern "C" void EXT_79fcf0();
extern "C" void EXT_79fd20();
extern "C" void EXT_79fe20();
extern "C" void EXT_7a00c0();
extern "C" void EXT_7a0110();
extern "C" void EXT_7a0360();
extern "C" void EXT_7a0410();
extern "C" void EXT_7a0460();
extern "C" void EXT_7a05b0();
extern "C" void EXT_7a07b0();
extern "C" void EXT_7a0ae0();
extern "C" void EXT_7a0b90();
extern "C" void EXT_7a0c50();
extern "C" void EXT_7a0cd0();
extern "C" void EXT_7a0ee0();
extern "C" void EXT_7a0f90();
extern "C" void EXT_f47380();
extern "C" void EXT_f473a0();
extern "C" void EXT_1023030();
extern "C" void EXT_11e0744();

// @ 0x007a07b0
__declspec(naked) void FUN_007a07b0() {
  __asm {
    push -1
    _emit 0x64
    _emit 0xa1
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov eax, dword ptr fs:[0]
    push 1213c58h
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
    _emit 0xec
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; ja 0x7a08df
    test edi, edi
    _emit 0x0f
    _emit 0x86
    _emit 0xdc
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jbe 0x7a09d7
    mov ecx, dword ptr [esp + 40h]
    push ecx
    lea ecx, [esp + 18h]
    call EXT_79a4a0
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
    _emit 0x3a  ; jae 0x7a086f
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
    call EXT_79a710
    add dword ptr [esi + 4], edi
    mov esi, dword ptr [esp + 4ch]
    push ebp
    push ebx
    push esi
    call EXT_79f770
    lea ecx, [esp + 34h]
    push ecx
    add edi, esi
    push edi
    push esi
    call EXT_79fcf0
    add esp, 2ch
    _emit 0xeb
    _emit 0x4a  ; jmp 0x7a08b9
    lea eax, [esp + 18h]
    push eax
    sub edi, ebx
    push edi
    push ebp
    call EXT_79a9d0
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
    call EXT_79a710
    lea edx, [esp + 38h]
    push edx
    lea ecx, [ebx + ebx*4]
    add ecx, ecx
    add ecx, ecx
    add dword ptr [esi + 4], ecx
    push ebp
    push edi
    call EXT_79fcf0
    add esp, 30h
    lea ecx, [esp + 14h]
    mov dword ptr [esp + 30h], 0ffffffffh
    call EXT_432e80
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
    _emit 0x05  ; jne 0x7a08fc
    mov ecx, 1
    add eax, edi
    cmp ecx, eax
    _emit 0x76
    _emit 0x02  ; jbe 0x7a0904
    mov eax, ecx
    mov dword ptr [esp + 10h], eax
    test eax, eax
    _emit 0x74
    _emit 0x29  ; je 0x7a0935
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
    _emit 0x08  ; jmp 0x7a093d
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
    call EXT_79a9d0
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
    _emit 0x0f  ; je 0x7a09c1
    cmp dword ptr [eax - 4], 0
    _emit 0x74
    _emit 0x09  ; je 0x7a09c1
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

// @ 0x007a09f0
__declspec(naked) void FUN_007a09f0() {
  __asm {
    push -1
    push 1213c39h
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
    push ecx
    push esi
    mov esi, ecx
    push edi
    mov dword ptr [esp + 8], esi
    mov dword ptr [esi], 140f58ch
    mov dword ptr [esi + 4], 140f588h
    lea edi, [esi + 10h]
    push edi
    mov dword ptr [esp + 18h], 3
    call EXT_7a0410
    mov ecx, dword ptr [esi + 24h]
    add esp, 4
    mov byte ptr [esp + 14h], 2
    test ecx, ecx
    _emit 0x74
    _emit 0x1a  ; je 0x7a0a55
    mov eax, dword ptr [ecx + 4]
    add eax, -1
    mov dword ptr [ecx + 4], eax
    _emit 0x75
    _emit 0x0f  ; jne 0x7a0a55
    mov dword ptr [ecx + 4], 1
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax]
    push 1
    call edx
    mov eax, dword ptr [edi + 4]
    mov ecx, dword ptr [edi]
    push eax
    push ecx
    mov ecx, edi
    call EXT_1023030
    mov edi, dword ptr [edi]
    test edi, edi
    _emit 0x74
    _emit 0x0f  ; je 0x7a0a78
    cmp dword ptr [edi - 4], 0
    _emit 0x74
    _emit 0x09  ; je 0x7a0a78
    push edi
    call EXT_f47380
    add esp, 4
    mov ecx, dword ptr [esi + 0ch]
    mov byte ptr [esp + 14h], 0
    test ecx, ecx
    _emit 0x74
    _emit 0x1a  ; je 0x7a0a9e
    mov eax, dword ptr [ecx + 4]
    add eax, -1
    mov dword ptr [ecx + 4], eax
    _emit 0x75
    _emit 0x0f  ; jne 0x7a0a9e
    mov dword ptr [ecx + 4], 1
    mov edx, dword ptr [ecx]
    mov eax, dword ptr [edx]
    push 1
    call eax
    mov ecx, dword ptr [esp + 0ch]
    mov dword ptr [esi + 4], 13ef094h
    pop edi
    pop esi
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 10h
    ret
  }
}

// @ 0x007a0ae0
__declspec(naked) void FUN_007a0ae0() {
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
    _emit 0x49  ; jbe 0x7a0b66
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
    call EXT_7a0110
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
    call EXT_7a00c0
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

// @ 0x007a0b90
__declspec(naked) void FUN_007a0b90() {
  __asm {
    _emit 0x64
    _emit 0xa1
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov eax, dword ptr fs:[0]
    push -1
    push 1213c78h
    push eax
    _emit 0x64
    _emit 0x89
    _emit 0x25
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], esp
    sub esp, 14h
    push esi
    mov esi, ecx
    mov ecx, dword ptr [esi]
    push edi
    mov edi, dword ptr [esp + 2ch]
    test ecx, ecx
    _emit 0x74
    _emit 0x06  ; je 0x7a0bbc
    cmp dword ptr [ecx - 4], 0
    _emit 0x74
    _emit 0x0c  ; je 0x7a0bc8
    mov eax, dword ptr [edi]
    test eax, eax
    _emit 0x74
    _emit 0x50  ; je 0x7a0c12
    cmp dword ptr [eax - 4], 0
    _emit 0x75
    _emit 0x4a  ; jne 0x7a0c12
    push esi
    lea ecx, [esp + 0ch]
    call EXT_79b020
    push edi
    mov ecx, esi
    mov dword ptr [esp + 28h], 0
    call EXT_7a0460
    lea eax, [esp + 8]
    push eax
    mov ecx, edi
    call EXT_7a0460
    lea ecx, [esp + 8]
    mov dword ptr [esp + 24h], 0ffffffffh
    call EXT_432de0
    pop edi
    pop esi
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
    mov dword ptr [esi], eax
    mov dword ptr [edi], ecx
    mov ecx, dword ptr [edi + 4]
    mov eax, dword ptr [esi + 4]
    mov dword ptr [esi + 4], ecx
    mov ecx, dword ptr [esp + 1ch]
    mov dword ptr [edi + 4], eax
    mov edx, dword ptr [edi + 8]
    mov eax, dword ptr [esi + 8]
    mov dword ptr [esi + 8], edx
    mov dword ptr [edi + 8], eax
    pop edi
    pop esi
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

// @ 0x007a0cd0
__declspec(naked) void FUN_007a0cd0() {
  __asm {
    push ecx
    push ebx
    push esi
    push edi
    xor esi, esi
    push esi
    push esi
    push esi
    push esi
    push 13eb8a4h
    push 58h
    mov ebx, ecx
    call EXT_f473a0
    add esp, 18h
    cmp eax, esi
    _emit 0x74
    _emit 0x39  ; je 0x7a0d28
    mov dword ptr [eax], 13ef094h
    xor ecx, ecx
    lea edx, [eax + 4]
    xchg dword ptr [edx], ecx
    mov dword ptr [eax], 13eb8d0h
    mov dword ptr [eax + 8], esi
    mov dword ptr [eax + 0ch], esi
    mov dword ptr [eax + 10h], esi
    mov dword ptr [eax + 1ch], esi
    mov dword ptr [eax + 20h], esi
    mov dword ptr [eax + 24h], esi
    mov dword ptr [eax + 30h], esi
    mov dword ptr [eax + 34h], esi
    mov dword ptr [eax + 38h], esi
    mov dword ptr [eax + 44h], esi
    mov dword ptr [eax + 48h], esi
    mov dword ptr [eax + 4ch], esi
    _emit 0xeb
    _emit 0x02  ; jmp 0x7a0d2a
    xor eax, eax
    mov ecx, dword ptr [ebx]
    cmp eax, ecx
    _emit 0x74
    _emit 0x34  ; je 0x7a0d64
    cmp eax, esi
    _emit 0x74
    _emit 0x0c  ; je 0x7a0d40
    lea edx, [eax + 4]
    mov edi, 1
    lock xadd dword ptr [edx], edi
    mov dword ptr [ebx], eax
    cmp ecx, esi
    _emit 0x74
    _emit 0x1e  ; je 0x7a0d64
    lea eax, [ecx + 4]
    mov edx, eax
    or esi, 0ffffffffh
    lock xadd dword ptr [edx], esi
    dec esi
    _emit 0x75
    _emit 0x0f  ; jne 0x7a0d64
    mov edx, 1
    xchg dword ptr [eax], edx
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax]
    push 1
    call edx
    mov eax, dword ptr [esp + 14h]
    mov ecx, dword ptr [ebx]
    push eax
    add ecx, 30h
    call EXT_79a3f0
    mov edi, dword ptr [ebx + 4]
    mov esi, dword ptr [ebx + 8]
    push edi
    push esi
    push esi
    call EXT_705250
    mov ecx, dword ptr [esp + 24h]
    sub esi, edi
    sar esi, 4
    neg esi
    shl esi, 4
    add dword ptr [ebx + 8], esi
    add esp, 0ch
    lea esi, [ebx + 18h]
    push ecx
    mov ecx, esi
    call EXT_7a0ae0
    mov edi, dword ptr [esi]
    cmp edi, dword ptr [ebx + 1ch]
    _emit 0x74
    _emit 0x29  ; je 0x7a0dd0
    push ebp
    mov esi, dword ptr [edi + 4]
    mov ebp, dword ptr [edi]
    mov edx, esi
    sub edx, esi
    push edx
    push esi
    push ebp
    call EXT_11e0744
    sub esi, ebp
    sar esi, 1
    neg esi
    add esi, esi
    add dword ptr [edi + 4], esi
    add edi, 14h
    add esp, 0ch
    cmp edi, dword ptr [ebx + 1ch]
    _emit 0x75
    _emit 0xd9  ; jne 0x7a0da8
    pop ebp
    pop edi
    pop esi
    pop ebx
    pop ecx
    ret 8
  }
}

// @ 0x007a0de0
__declspec(naked) void FUN_007a0de0() {
  __asm {
    push ecx
    push ebp
    push esi
    push edi
    xor esi, esi
    push esi
    push esi
    push esi
    push esi
    push 13eb8a4h
    push 58h
    mov ebp, ecx
    call EXT_f473a0
    add esp, 18h
    cmp eax, esi
    _emit 0x74
    _emit 0x39  ; je 0x7a0e38
    mov dword ptr [eax], 13ef094h
    xor ecx, ecx
    lea edx, [eax + 4]
    xchg dword ptr [edx], ecx
    mov dword ptr [eax], 13eb8d0h
    mov dword ptr [eax + 8], esi
    mov dword ptr [eax + 0ch], esi
    mov dword ptr [eax + 10h], esi
    mov dword ptr [eax + 1ch], esi
    mov dword ptr [eax + 20h], esi
    mov dword ptr [eax + 24h], esi
    mov dword ptr [eax + 30h], esi
    mov dword ptr [eax + 34h], esi
    mov dword ptr [eax + 38h], esi
    mov dword ptr [eax + 44h], esi
    mov dword ptr [eax + 48h], esi
    mov dword ptr [eax + 4ch], esi
    _emit 0xeb
    _emit 0x02  ; jmp 0x7a0e3a
    xor eax, eax
    mov ecx, dword ptr [ebp]
    cmp eax, ecx
    _emit 0x74
    _emit 0x35  ; je 0x7a0e76
    cmp eax, esi
    _emit 0x74
    _emit 0x0c  ; je 0x7a0e51
    lea edx, [eax + 4]
    mov edi, 1
    lock xadd dword ptr [edx], edi
    mov dword ptr [ebp], eax
    cmp ecx, esi
    _emit 0x74
    _emit 0x1e  ; je 0x7a0e76
    lea eax, [ecx + 4]
    mov edx, eax
    or esi, 0ffffffffh
    lock xadd dword ptr [edx], esi
    dec esi
    _emit 0x75
    _emit 0x0f  ; jne 0x7a0e76
    mov edx, 1
    xchg dword ptr [eax], edx
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax]
    push 1
    call edx
    mov edi, dword ptr [esp + 18h]
    mov eax, dword ptr [esp + 14h]
    push edi
    push eax
    lea ecx, [ebp + 8]
    call EXT_7a0cd0
    lea esi, [ebp + 48h]
    push edi
    mov ecx, esi
    call EXT_7a0ae0
    mov edi, dword ptr [esi]
    cmp edi, dword ptr [ebp + 4ch]
    _emit 0x74
    _emit 0x2e  ; je 0x7a0ec8
    push ebx
    _emit 0xeb
    _emit 0x03  ; jmp 0x7a0ea0
    _emit 0x8d
    _emit 0x49
    _emit 0x00  ; data
    mov esi, dword ptr [edi + 4]
    mov ebx, dword ptr [edi]
    mov ecx, esi
    sub ecx, esi
    push ecx
    push esi
    push ebx
    call EXT_11e0744
    sub esi, ebx
    sar esi, 1
    neg esi
    add esi, esi
    add dword ptr [edi + 4], esi
    add edi, 14h
    add esp, 0ch
    cmp edi, dword ptr [ebp + 4ch]
    _emit 0x75
    _emit 0xd9  ; jne 0x7a0ea0
    pop ebx
    mov edx, dword ptr [esp + 14h]
    mov ecx, dword ptr [ebp]
    push edx
    add ecx, 30h
    call EXT_79a3f0
    pop edi
    pop esi
    pop ebp
    pop ecx
    ret 8
  }
}

// @ 0x007a0ee0
__declspec(naked) void FUN_007a0ee0() {
  __asm {
    push -1
    push 1213c58h
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
    sub esp, 14h
    push ebx
    push ebp
    push esi
    mov esi, dword ptr [esp + 34h]
    mov ebp, dword ptr [esi]
    push edi
    mov edi, dword ptr [esi + 4]
    push ebp
    push edi
    push edi
    mov ebx, ecx
    call EXT_79f730
    mov ecx, dword ptr [esi + 4]
    add esp, 0ch
    push ecx
    push eax
    mov ecx, esi
    call EXT_79b0d0
    sub edi, ebp
    mov eax, 99999999h
    imul edi
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    lea edx, [eax + eax*4]
    mov eax, dword ptr [esp + 34h]
    add edx, edx
    push eax
    lea ecx, [esp + 14h]
    add edx, edx
    add dword ptr [esi + 4], edx
    push ecx
    call EXT_79fd20
    add esp, 8
    push eax
    mov ecx, esi
    mov dword ptr [esp + 30h], 0
    call EXT_7a0c50
    lea ecx, [esp + 10h]
    mov dword ptr [esp + 2ch], 0ffffffffh
    call EXT_432e80
    mov edx, dword ptr [ebx]
    mov eax, dword ptr [edx + 4]
    push esi
    mov ecx, ebx
    call eax
    mov ecx, dword ptr [esp + 24h]
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
    add esp, 20h
    ret 8
  }
}

// @ 0x007a0f90
__declspec(naked) void FUN_007a0f90() {
  __asm {
    push -1
    push 1213c78h
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
    sub esp, 14h
    xor eax, eax
    mov dword ptr [esp], eax
    mov dword ptr [esp + 4], eax
    mov dword ptr [esp + 8], eax
    mov edx, dword ptr [esp + 24h]
    mov dword ptr [esp + 1ch], eax
    lea eax, [esp]
    push eax
    push edx
    call EXT_7a0ee0
    mov eax, dword ptr [esp + 28h]
    push eax
    lea ecx, [esp + 4]
    push ecx
    call EXT_7a0360
    add esp, 8
    lea ecx, [esp]
    mov dword ptr [esp + 1ch], 0ffffffffh
    call EXT_432de0
    mov ecx, dword ptr [esp + 14h]
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 20h
    ret 8
  }
}

// @ 0x007a1000
__declspec(naked) void FUN_007a1000() {
  __asm {
    push -1
    push 1213ca0h
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
    sub esp, 18h
    push ebx
    push ebp
    push esi
    push edi
    xor edi, edi
    mov ebx, ecx
    mov dword ptr [esp + 14h], edi
    mov dword ptr [esp + 18h], edi
    mov dword ptr [esp + 1ch], edi
    mov eax, dword ptr [ebx + 20h]
    push eax
    lea ecx, [esp + 18h]
    mov dword ptr [esp + 34h], edi
    call EXT_79a4f0
    mov eax, dword ptr [esp + 38h]
    push eax
    lea ecx, [esp + 18h]
    call EXT_7a0b90
    mov ecx, dword ptr [esp + 18h]
    mov ebp, dword ptr [esp + 14h]
    sub ecx, ebp
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov esi, edx
    shr esi, 1fh
    add esi, edx
    _emit 0x74
    _emit 0x5a  ; je 0x7a10c2
    mov ecx, dword ptr [esp + 14h]
    lea ebp, [ebx + 10h]
    mov dword ptr [esp + 10h], ecx
    mov eax, dword ptr [ebx + 18h]
    mov ecx, ebp
    test eax, eax
    _emit 0x74
    _emit 0x1f  ; je 0x7a109b
    _emit 0x8d
    _emit 0x64
    _emit 0x24
    _emit 0x00  ; lea esp, [esp]
    cmp dword ptr [eax + 10h], edi
    _emit 0x7c
    _emit 0x07  ; jl 0x7a108c
    mov ecx, eax
    mov eax, dword ptr [eax + 4]
    _emit 0xeb
    _emit 0x02  ; jmp 0x7a108e
    mov eax, dword ptr [eax]
    test eax, eax
    _emit 0x75
    _emit 0xee  ; jne 0x7a1080
    cmp ecx, ebp
    _emit 0x74
    _emit 0x05  ; je 0x7a109b
    cmp edi, dword ptr [ecx + 10h]
    _emit 0x7d
    _emit 0x02  ; jge 0x7a109d
    mov ecx, ebp
    lea eax, [ebx + 10h]
    cmp ecx, eax
    _emit 0x74
    _emit 0x0e  ; je 0x7a10b2
    mov edx, dword ptr [esp + 10h]
    mov ecx, dword ptr [esp + 38h]
    push edx
    call EXT_7a0c50
    add dword ptr [esp + 10h], 14h
    inc edi
    cmp edi, esi
    _emit 0x72
    _emit 0xb7  ; jb 0x7a1073
    mov ebp, dword ptr [esp + 14h]
    xor edi, edi
    mov eax, dword ptr [esp + 18h]
    push eax
    push ebp
    lea ecx, [esp + 1ch]
    mov dword ptr [esp + 38h], 1
    call EXT_79b0d0
    cmp ebp, edi
    _emit 0x74
    _emit 0x0e  ; je 0x7a10eb
    cmp dword ptr [ebp - 4], edi
    _emit 0x74
    _emit 0x09  ; je 0x7a10eb
    push ebp
    call EXT_f47380
    add esp, 4
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
    ret 4
  }
}

// @ 0x007a1100
__declspec(naked) void FUN_007a1100() {
  __asm {
    _emit 0x64
    _emit 0xa1
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov eax, dword ptr fs:[0]
    push -1
    push 1213c58h
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
    mov ebx, dword ptr [ecx]
    push esi
    mov esi, dword ptr [esp + 2ch]
    push edi
    mov edi, dword ptr [ecx + 4]
    mov edx, edi
    sub edx, ebx
    mov eax, 66666667h
    imul edx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    cmp esi, eax
    _emit 0x76
    _emit 0x5a  ; jbe 0x7a1197
    xor eax, eax
    mov dword ptr [esp + 0ch], eax
    mov dword ptr [esp + 10h], eax
    mov dword ptr [esp + 14h], eax
    mov dword ptr [esp + 28h], eax
    mov edx, edi
    sub edx, ebx
    mov eax, 66666667h
    imul edx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    lea edx, [esp + 0ch]
    push edx
    sub esi, eax
    push esi
    push edi
    call EXT_7a07b0
    lea ecx, [esp + 0ch]
    mov dword ptr [esp + 28h], 0ffffffffh
    call EXT_432e80
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
    lea eax, [esi + esi*4]
    push edi
    lea edx, [ebx + eax*4]
    push edx
    call EXT_7a05b0
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

// @ 0x007a11c0
__declspec(naked) void FUN_007a11c0() {
  __asm {
    push -1
    push 1213cb8h
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
    sub esp, 38h
    push ebx
    push ebp
    push esi
    push edi
    mov edi, ecx
    mov eax, dword ptr [edi + 10h]
    lea esi, [edi + 10h]
    xor ebx, ebx
    mov dword ptr [esp + 20h], edi
    mov dword ptr [esp + 1ch], esi
    cmp eax, dword ptr [esi + 4]
    _emit 0x75
    _emit 0x3d  ; jne 0x7a1230
    mov dword ptr [esp + 34h], ebx
    mov dword ptr [esp + 38h], ebx
    mov dword ptr [esp + 3ch], ebx
    lea ecx, [esp + 34h]
    push ecx
    mov ecx, dword ptr [esp + 5ch]
    mov dword ptr [esp + 54h], ebx
    call EXT_73eb90
    mov ecx, dword ptr [edi + 0ch]
    push esi
    lea edx, [esp + 38h]
    push edx
    call EXT_7a0f90
    lea ecx, [esp + 34h]
    mov dword ptr [esp + 50h], 0ffffffffh
    call EXT_41eb80
    _emit 0x81
    _emit 0x0d
    _emit 0x8c
    _emit 0xa3
    _emit 0x6f
    _emit 0x01
    _emit 0x00
    _emit 0x80
    _emit 0x00
    _emit 0x00  ; or dword ptr [0x16fa38c], 0x8000
    _emit 0xc7
    _emit 0x05
    _emit 0x38
    _emit 0x92
    _emit 0x6f
    _emit 0x01
    _emit 0x01
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr [0x16f9238], 1
    mov eax, dword ptr [edi + 24h]
    cmp eax, ebx
    _emit 0x0f
    _emit 0x84
    _emit 0x17
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x7a1366
    mov ecx, dword ptr [eax + 44h]
    sub ecx, dword ptr [eax + 40h]
    mov eax, 92492493h
    imul ecx
    add edx, ecx
    sar edx, 4
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    _emit 0x0f
    _emit 0x84
    _emit 0x70
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x7a13de
    mov dword ptr [esp + 14h], ebx
    mov dword ptr [esp + 10h], ebx
    mov dword ptr [esp + 18h], eax
    _emit 0x8d
    _emit 0x9b
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; lea ebx, [ebx]
    mov eax, dword ptr [edi + 24h]
    mov eax, dword ptr [eax + 40h]
    add eax, dword ptr [esp + 14h]
    mov ebp, dword ptr [esi]
    mov ecx, dword ptr [eax + 8]
    mov ebx, dword ptr [eax + 4]
    add ebp, dword ptr [esp + 10h]
    mov dword ptr [esp + 30h], ecx
    cmp ebx, ecx
    _emit 0x74
    _emit 0x0e  ; je 0x7a12ac
    mov edi, edi
    cmp dword ptr [ebx], -2
    _emit 0x74
    _emit 0x07  ; je 0x7a12ac
    add ebx, 78h
    cmp ebx, ecx
    _emit 0x75
    _emit 0xf4  ; jne 0x7a12a0
    mov eax, ecx
    mov dword ptr [esp + 24h], ecx
    cmp ecx, eax
    _emit 0x74
    _emit 0x10  ; je 0x7a12c6
    cmp dword ptr [ecx], -2
    _emit 0x74
    _emit 0x07  ; je 0x7a12c2
    add ecx, 78h
    cmp ecx, eax
    _emit 0x75
    _emit 0xf4  ; jne 0x7a12b6
    mov dword ptr [esp + 24h], ecx
    cmp ebx, ecx
    _emit 0x74
    _emit 0x72  ; je 0x7a133c
    _emit 0x8d
    _emit 0x9b
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; lea ebx, [ebx]
    mov ecx, dword ptr [esp + 5ch]
    push ecx
    mov ecx, dword ptr [esp + 5ch]
    lea edx, [ebx + 40h]
    push edx
    call EXT_73eca0
    mov esi, dword ptr [ebp + 4]
    sub esi, dword ptr [ebp]
    xor edi, edi
    sar esi, 3
    test esi, esi
    _emit 0x76
    _emit 0x26  ; jbe 0x7a1317
    mov eax, dword ptr [ebp]
    mov ecx, dword ptr [esp + 5ch]
    mov edx, dword ptr [esp + 60h]
    push ecx
    mov ecx, dword ptr [eax + edi*8 + 4]
    lea eax, [eax + edi*8]
    push edx
    mov edx, dword ptr [eax]
    push ecx
    mov ecx, dword ptr [esp + 64h]
    push edx
    call EXT_73ede0
    inc edi
    cmp edi, esi
    _emit 0x72
    _emit 0xda  ; jb 0x7a12f1
    mov eax, dword ptr [esp + 30h]
    add ebx, 78h
    cmp ebx, eax
    _emit 0x74
    _emit 0x0c  ; je 0x7a132e
    cmp dword ptr [ebx], -2
    _emit 0x74
    _emit 0x07  ; je 0x7a132e
    add ebx, 78h
    cmp ebx, eax
    _emit 0x75
    _emit 0xf4  ; jne 0x7a1322
    cmp ebx, dword ptr [esp + 24h]
    _emit 0x75
    _emit 0x9c  ; jne 0x7a12d0
    mov edi, dword ptr [esp + 20h]
    mov esi, dword ptr [esp + 1ch]
    add dword ptr [esp + 10h], 14h
    add dword ptr [esp + 14h], 1ch
    sub dword ptr [esp + 18h], 1
    _emit 0x0f
    _emit 0x85
    _emit 0x2f
    _emit 0xff
    _emit 0xff
    _emit 0xff  ; jne 0x7a1280
    pop edi
    pop esi
    pop ebp
    pop ebx
    mov ecx, dword ptr [esp + 38h]
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 44h
    ret 0ch
    mov ecx, dword ptr [esi + 4]
    sub ecx, dword ptr [esi]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    _emit 0x74
    _emit 0x60  ; je 0x7a13de
    mov edi, dword ptr [esp + 60h]
    mov dword ptr [esp + 14h], ebx
    mov dword ptr [esp + 18h], eax
    _emit 0xeb
    _emit 0x0a  ; jmp 0x7a1396
    _emit 0x8d
    _emit 0x64
    _emit 0x24
    _emit 0x00  ; data
    mov esi, dword ptr [esp + 1ch]
    xor ebx, ebx
    mov ebp, dword ptr [esi]
    add ebp, dword ptr [esp + 14h]
    xor esi, esi
    mov ebx, dword ptr [ebp + 4]
    sub ebx, dword ptr [ebp]
    sar ebx, 3
    test ebx, ebx
    _emit 0x76
    _emit 0x27  ; jbe 0x7a13d2
    _emit 0xeb
    _emit 0x03  ; jmp 0x7a13b0
    _emit 0x8d
    _emit 0x49
    _emit 0x00  ; data
    mov eax, dword ptr [ebp]
    mov ecx, dword ptr [esp + 5ch]
    mov edx, dword ptr [eax + esi*8 + 4]
    push ecx
    mov ecx, dword ptr [esp + 5ch]
    lea eax, [eax + esi*8]
    mov eax, dword ptr [eax]
    push edi
    push edx
    push eax
    call EXT_73ede0
    inc esi
    cmp esi, ebx
    _emit 0x72
    _emit 0xde  ; jb 0x7a13b0
    add dword ptr [esp + 14h], 14h
    sub dword ptr [esp + 18h], 1
    _emit 0x75
    _emit 0xb2  ; jne 0x7a1390
    mov ecx, dword ptr [esp + 48h]
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
    add esp, 44h
    ret 0ch
  }
}

// @ 0x007a1400
__declspec(naked) void FUN_007a1400() {
  __asm {
    _emit 0x64
    _emit 0xa1
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov eax, dword ptr fs:[0]
    push -1
    push 120ee28h
    push eax
    _emit 0x64
    _emit 0x89
    _emit 0x25
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], esp
    sub esp, 34h
    push edi
    mov edi, ecx
    mov eax, dword ptr [edi + 4]
    cmp eax, dword ptr [edi + 8]
    _emit 0x75
    _emit 0x14  ; jne 0x7a1437
    xor eax, eax
    pop edi
    mov ecx, dword ptr [esp + 34h]
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 40h
    ret 4
    push ebx
    mov ebx, dword ptr [edi]
    push ebp
    push esi
    mov esi, dword ptr [esp + 54h]
    mov ecx, dword ptr [esi + 20h]
    sub ecx, dword ptr [esi + 1ch]
    mov eax, 0ea0ea0ebh
    imul ecx
    add edx, ecx
    sar edx, 7
    mov ecx, edx
    shr ecx, 1fh
    add ecx, edx
    push ecx
    lea ecx, [ebx + 1ch]
    call EXT_71f7e0
    mov ecx, dword ptr [edi + 1ch]
    sub ecx, dword ptr [edi + 18h]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    xor ebp, ebp
    cmp eax, ebp
    _emit 0x0f
    _emit 0x8e
    _emit 0xa3
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; jle 0x7a1526
    mov dword ptr [esp + 10h], ebp
    mov dword ptr [esp + 18h], eax
    _emit 0xeb
    _emit 0x03  ; jmp 0x7a1490
    _emit 0x8d
    _emit 0x49
    _emit 0x00  ; data
    mov eax, dword ptr [esi + 1ch]
    mov ecx, dword ptr [edi]
    mov edx, dword ptr [edi + 8]
    mov esi, dword ptr [ecx + 1ch]
    sub edx, dword ptr [edi + 4]
    mov ebx, dword ptr [edi + 18h]
    add ebx, dword ptr [esp + 10h]
    add eax, ebp
    add esi, ebp
    add eax, 14h
    sar edx, 4
    push eax
    lea ecx, [esi + 14h]
    mov dword ptr [esi + 10h], edx
    call EXT_719170
    mov eax, dword ptr [ebx]
    mov ecx, dword ptr [ebx + 4]
    sub ecx, eax
    mov edx, 2
    mov dword ptr [esp + 38h], eax
    sar ecx, 1
    mov eax, edx
    xor ebx, ebx
    mov dword ptr [esp + 34h], ecx
    mov word ptr [esp + 3ch], dx
    mov word ptr [esp + 3eh], ax
    mov dword ptr [esp + 40h], ebx
    lea ecx, [esp + 34h]
    push esi
    push ecx
    mov dword ptr [esp + 54h], ebx
    call EXT_7201d0
    mov ecx, dword ptr [esp + 48h]
    add esp, 8
    mov dword ptr [esp + 4ch], 0ffffffffh
    cmp ecx, ebx
    _emit 0x74
    _emit 0x07  ; je 0x7a150c
    mov edx, dword ptr [ecx]
    mov eax, dword ptr [edx + 4]
    call eax
    add dword ptr [esp + 10h], 14h
    mov esi, dword ptr [esp + 54h]
    add ebp, 8ch
    sub dword ptr [esp + 18h], 1
    _emit 0x0f
    _emit 0x85
    _emit 0x6a
    _emit 0xff
    _emit 0xff
    _emit 0xff  ; jne 0x7a1490
    mov ecx, dword ptr [esi + 0ch]
    sub ecx, dword ptr [esi + 8]
    sar ecx, 5
    push ecx
    mov ecx, dword ptr [edi]
    add ecx, 8
    call EXT_475320
    mov eax, dword ptr [esi + 0ch]
    sub eax, dword ptr [esi + 8]
    sar eax, 5
    test eax, eax
    _emit 0x0f
    _emit 0x86
    _emit 0xdd
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jbe 0x7a1728
    mov dword ptr [esp + 18h], 0
    mov dword ptr [esp + 28h], eax
    _emit 0xeb
    _emit 0x0b  ; jmp 0x7a1564
    _emit 0x8d
    _emit 0xa4
    _emit 0x24
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; data
    mov esi, dword ptr [esp + 54h]
    mov esi, dword ptr [esi + 8]
    add esi, dword ptr [esp + 18h]
    mov edx, dword ptr [esi]
    cmp dword ptr [edx*4 + 153b208h], 0
    _emit 0x0f
    _emit 0x84
    _emit 0x9d
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x7a1718
    mov ecx, dword ptr [edi]
    add ecx, 8
    call EXT_79fe20
    mov eax, dword ptr [edi]
    mov ebx, dword ptr [eax + 0ch]
    mov ecx, dword ptr [esi + 0ch]
    sub ebx, 20h
    mov dword ptr [ebx + 0ch], ecx
    mov edx, dword ptr [esi + 4]
    mov dword ptr [ebx + 4], edx
    mov eax, dword ptr [esi]
    mov dword ptr [ebx], eax
    mov ecx, dword ptr [esi + 8]
    mov dword ptr [ebx + 8], ecx
    mov eax, dword ptr [esi + 0ch]
    test eax, eax
    _emit 0x0f
    _emit 0x8c
    _emit 0x6a
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jl 0x7a1718
    cmp eax, 2
    _emit 0x7e
    _emit 0x1a  ; jle 0x7a15cd
    cmp eax, 8
    _emit 0x0f
    _emit 0x85
    _emit 0x5c
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jne 0x7a1718
    add esi, 10h
    push esi
    lea ecx, [ebx + 10h]
    call EXT_424f70
    _emit 0xe9
    _emit 0x4b
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jmp 0x7a1718
    mov eax, dword ptr [edi + 8]
    movzx edx, word ptr [esi + 18h]
    sub eax, dword ptr [edi + 4]
    lea ebp, [ebx + 10h]
    push ebp
    push edx
    sar eax, 4
    push eax
    call EXT_720190
    mov eax, dword ptr [edi + 8]
    sub eax, dword ptr [edi + 4]
    add esp, 0ch
    sar eax, 4
    mov dword ptr [esp + 10h], 0
    mov dword ptr [esp + 30h], eax
    test eax, eax
    _emit 0x0f
    _emit 0x86
    _emit 0x13
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jbe 0x7a1718
    mov dword ptr [esp + 14h], 0
    _emit 0x8d
    _emit 0x49
    _emit 0x00  ; lea ecx, [ecx]
    mov edx, dword ptr [edi + 4]
    add edx, dword ptr [esp + 14h]
    mov eax, dword ptr [esp + 54h]
    mov ecx, dword ptr [edx]
    movss xmm0, dword ptr [edx + 0ch]
    imul ecx, ecx, 8ch
    add ecx, dword ptr [eax + 1ch]
    _emit 0x0f
    _emit 0x2e
    _emit 0x05
    _emit 0x78
    _emit 0x53
    _emit 0x48
    _emit 0x01  ; ucomiss xmm0, dword ptr [0x1485378]
    lahf
    movss dword ptr [esp + 2ch], xmm0
    test ah, 44h
    _emit 0x0f
    _emit 0x8b
    _emit 0x80
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; jnp 0x7a16c2
    movzx eax, word ptr [ecx + 0ah]
    fld dword ptr [esp + 2ch]
    mov dword ptr [esp + 1ch], eax
    mov eax, dword ptr [ecx + 4]
    movzx ecx, word ptr [ecx + 8]
    mov dword ptr [esp + 20h], eax
    mov eax, dword ptr [ecx*4 + 140f544h]
    movzx ecx, word ptr [ebp + 0ah]
    imul ecx, dword ptr [esp + 10h]
    add ecx, dword ptr [ebp + 4]
    mov dword ptr [esp + 24h], eax
    mov eax, dword ptr [edx + 8]
    imul eax, dword ptr [esp + 1ch]
    mov edx, dword ptr [edx + 4]
    imul edx, dword ptr [esp + 1ch]
    push ecx
    mov ecx, dword ptr [esp + 24h]
    mov eax, dword ptr [eax + ecx]
    and eax, dword ptr [esp + 28h]
    movzx ecx, word ptr [esi + 1ah]
    imul eax, ecx
    add eax, dword ptr [esi + 14h]
    push eax
    mov eax, dword ptr [esp + 28h]
    mov ecx, dword ptr [edx + eax]
    and ecx, dword ptr [esp + 2ch]
    movzx edx, word ptr [esi + 1ah]
    mov eax, dword ptr [ebx + 8]
    imul ecx, edx
    add ecx, dword ptr [esi + 14h]
    push ecx
    push ecx
    mov ecx, dword ptr [ebx]
    fstp dword ptr [esp]
    push eax
    push ecx
    call EXT_799e70
    add esp, 18h
    _emit 0xeb
    _emit 0x3e  ; jmp 0x7a1700
    movzx eax, word ptr [esi + 18h]
    push eax
    movzx eax, word ptr [ecx + 0ah]
    imul eax, dword ptr [edx + 4]
    mov edx, dword ptr [ecx + 4]
    movzx ecx, word ptr [ecx + 8]
    mov edx, dword ptr [eax + edx]
    and edx, dword ptr [ecx*4 + 140f544h]
    movzx eax, word ptr [esi + 1ah]
    movzx ecx, word ptr [ebp + 0ah]
    imul edx, eax
    imul ecx, dword ptr [esp + 14h]
    add edx, dword ptr [esi + 14h]
    add ecx, dword ptr [ebp + 4]
    push edx
    push ecx
    call EXT_11e0744
    add esp, 0ch
    mov eax, dword ptr [esp + 10h]
    add dword ptr [esp + 14h], 10h
    inc eax
    mov dword ptr [esp + 10h], eax
    cmp eax, dword ptr [esp + 30h]
    _emit 0x0f
    _emit 0x82
    _emit 0xf8
    _emit 0xfe
    _emit 0xff
    _emit 0xff  ; jb 0x7a1610
    add dword ptr [esp + 18h], 20h
    sub dword ptr [esp + 28h], 1
    _emit 0x0f
    _emit 0x85
    _emit 0x38
    _emit 0xfe
    _emit 0xff
    _emit 0xff  ; jne 0x7a1560
    mov eax, dword ptr [edi]
    mov ecx, dword ptr [esp + 44h]
    pop esi
    pop ebp
    pop ebx
    pop edi
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 40h
    ret 4
  }
}


