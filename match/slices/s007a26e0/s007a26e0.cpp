// slice s007a26e0
// Per-instruction reconstruction (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
// Control flow is decoded recursively; call targets are symbolic so COFF
// relocation bytes are masked by the verifier. Unreachable bytes are data.

extern "C" void EXT_79aeb0();
extern "C" void EXT_79af80();
extern "C" void EXT_79b0d0();
extern "C" void EXT_79f4e0();
extern "C" void EXT_7a0b90();
extern "C" void EXT_7a1100();
extern "C" void EXT_7a1a80();
extern "C" void EXT_7a1bc0();
extern "C" void EXT_7a1d00();
extern "C" void EXT_f47380();

// @ 0x007a26e0
__declspec(naked) void FUN_007a26e0() {
  __asm {
    push -1
    push 1213d04h
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
    sub esp, 0b0h
    push ebx
    push ebp
    push esi
    push edi
    xor edi, edi
    mov dword ptr [esp + 24h], ecx
    mov dword ptr [esp + 3ch], edi
    mov dword ptr [esp + 40h], edi
    mov dword ptr [esp + 44h], edi
    mov ebx, dword ptr [esp + 0d0h]
    push ebx
    lea ecx, [esp + 40h]
    mov dword ptr [esp + 0cch], edi
    call EXT_7a0b90
    mov ecx, dword ptr [esp + 40h]
    mov ebp, dword ptr [esp + 3ch]
    sub ecx, ebp
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov esi, edx
    shr esi, 1fh
    add esi, edx
    push esi
    mov ecx, ebx
    call EXT_7a1100
    mov eax, 4
    mov dword ptr [esp + 50h], edi
    mov dword ptr [esp + 54h], edi
    mov dword ptr [esp + 58h], edi
    mov dword ptr [esp + 5ch], edi
    mov dword ptr [esp + 60h], edi
    mov dword ptr [esp + 64h], edi
    mov dword ptr [esp + 70h], edi
    mov dword ptr [esp + 74h], edi
    mov dword ptr [esp + 78h], edi
    mov dword ptr [esp + 84h], eax
    mov dword ptr [esp + 88h], edi
    mov dword ptr [esp + 8ch], edi
    mov dword ptr [esp + 90h], edi
    mov dword ptr [esp + 94h], edi
    mov dword ptr [esp + 98h], edi
    mov dword ptr [esp + 9ch], edi
    mov dword ptr [esp + 0a0h], edi
    mov dword ptr [esp + 0ach], eax
    mov dword ptr [esp + 0b0h], edi
    mov dword ptr [esp + 0b4h], edi
    mov dword ptr [esp + 0b8h], edi
    mov dword ptr [esp + 0bch], edi
    mov byte ptr [esp + 0c8h], 1
    cmp esi, edi
    _emit 0x0f
    _emit 0x86
    _emit 0xba
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jbe 0x7a299a
    mov dword ptr [esp + 10h], edi
    mov dword ptr [esp + 18h], ebp
    mov dword ptr [esp + 20h], esi
    _emit 0xeb
    _emit 0x09  ; jmp 0x7a27f7
    _emit 0x8b
    _emit 0xff  ; data
    mov ebx, dword ptr [esp + 0d0h]
    mov eax, dword ptr [ebp + 4]
    mov esi, dword ptr [ebx]
    sub eax, dword ptr [ebp]
    add esi, dword ptr [esp + 10h]
    sar eax, 3
    push eax
    mov ecx, esi
    call EXT_79af80
    mov ebx, dword ptr [ebp + 4]
    sub ebx, dword ptr [ebp]
    mov dword ptr [esp + 1ch], edi
    sar ebx, 3
    mov dword ptr [esp + 14h], ebx
    cmp ebx, edi
    _emit 0x0f
    _emit 0x86
    _emit 0x58
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jbe 0x7a297f
    _emit 0xeb
    _emit 0x07  ; jmp 0x7a2830
    _emit 0x8d
    _emit 0xa4
    _emit 0x24
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; data
    mov ecx, dword ptr [ebp]
    mov edx, dword ptr [esp + 1ch]
    mov eax, dword ptr [ecx + edx*8]
    lea ebp, [ecx + edx*8]
    lea ecx, [esp + 50h]
    push ecx
    mov ecx, dword ptr [esp + 28h]
    push eax
    call EXT_7a1a80
    mov eax, dword ptr [esp + 50h]
    cmp eax, edi
    _emit 0x0f
    _emit 0x84
    _emit 0x86
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x7a28de
    mov edx, dword ptr [ebp + 4]
    mov ecx, eax
    lea edi, [eax + 4]
    mov dword ptr [esp + 34h], ecx
    mov eax, edi
    mov ebx, 1
    lock xadd dword ptr [eax], ebx
    mov dword ptr [esp + 38h], edx
    mov eax, dword ptr [esi + 4]
    mov byte ptr [esp + 0c8h], 2
    cmp eax, dword ptr [esi + 8]
    _emit 0x73
    _emit 0x1a  ; jae 0x7a289d
    lea ebx, [eax + 8]
    mov dword ptr [esi + 4], ebx
    test eax, eax
    _emit 0x74
    _emit 0x21  ; je 0x7a28ae
    mov dword ptr [eax], ecx
    mov ebx, 1
    lock xadd dword ptr [edi], ebx
    mov dword ptr [eax + 4], edx
    _emit 0xeb
    _emit 0x11  ; jmp 0x7a28ae
    lea ecx, [esp + 34h]
    push ecx
    push eax
    mov ecx, esi
    call EXT_79f4e0
    mov ecx, dword ptr [esp + 34h]
    mov byte ptr [esp + 0c8h], 1
    test ecx, ecx
    _emit 0x74
    _emit 0x1e  ; je 0x7a28d8
    lea eax, [ecx + 4]
    mov edx, eax
    or edi, 0ffffffffh
    lock xadd dword ptr [edx], edi
    dec edi
    _emit 0x75
    _emit 0x0f  ; jne 0x7a28d8
    mov edx, 1
    xchg dword ptr [eax], edx
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax]
    push 1
    call edx
    mov ebx, dword ptr [esp + 14h]
    xor edi, edi
    mov ecx, dword ptr [esp + 54h]
    cmp ecx, edi
    _emit 0x0f
    _emit 0x84
    _emit 0x80
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x7a296a
    mov edx, dword ptr [ebp + 4]
    lea edi, [ecx + 4]
    mov dword ptr [esp + 28h], ecx
    mov eax, edi
    mov ebp, 1
    lock xadd dword ptr [eax], ebp
    mov dword ptr [esp + 2ch], edx
    mov eax, dword ptr [esi + 4]
    mov byte ptr [esp + 0c8h], 3
    cmp eax, dword ptr [esi + 8]
    _emit 0x73
    _emit 0x1a  ; jae 0x7a292d
    lea ebp, [eax + 8]
    mov dword ptr [esi + 4], ebp
    test eax, eax
    _emit 0x74
    _emit 0x21  ; je 0x7a293e
    mov dword ptr [eax], ecx
    mov ebp, 1
    lock xadd dword ptr [edi], ebp
    mov dword ptr [eax + 4], edx
    _emit 0xeb
    _emit 0x11  ; jmp 0x7a293e
    lea ecx, [esp + 28h]
    push ecx
    push eax
    mov ecx, esi
    call EXT_79f4e0
    mov ecx, dword ptr [esp + 28h]
    mov byte ptr [esp + 0c8h], 1
    test ecx, ecx
    _emit 0x74
    _emit 0x1e  ; je 0x7a2968
    lea eax, [ecx + 4]
    mov edx, eax
    or edi, 0ffffffffh
    lock xadd dword ptr [edx], edi
    dec edi
    _emit 0x75
    _emit 0x0f  ; jne 0x7a2968
    mov edx, 1
    xchg dword ptr [eax], edx
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax]
    push 1
    call edx
    xor edi, edi
    mov eax, dword ptr [esp + 1ch]
    mov ebp, dword ptr [esp + 18h]
    inc eax
    mov dword ptr [esp + 1ch], eax
    cmp eax, ebx
    _emit 0x0f
    _emit 0x82
    _emit 0xb1
    _emit 0xfe
    _emit 0xff
    _emit 0xff  ; jb 0x7a2830
    add dword ptr [esp + 10h], 14h
    add ebp, 14h
    sub dword ptr [esp + 20h], 1
    mov dword ptr [esp + 18h], ebp
    _emit 0x0f
    _emit 0x85
    _emit 0x5a
    _emit 0xfe
    _emit 0xff
    _emit 0xff  ; jne 0x7a27f0
    mov ebp, dword ptr [esp + 3ch]
    lea ecx, [esp + 50h]
    mov byte ptr [esp + 0c8h], 0
    call EXT_79aeb0
    mov eax, dword ptr [esp + 40h]
    push eax
    push ebp
    lea ecx, [esp + 44h]
    mov dword ptr [esp + 0d0h], 4
    call EXT_79b0d0
    cmp ebp, edi
    _emit 0x74
    _emit 0x0e  ; je 0x7a29d7
    cmp dword ptr [ebp - 4], edi
    _emit 0x74
    _emit 0x09  ; je 0x7a29d7
    push ebp
    call EXT_f47380
    add esp, 4
    mov ecx, dword ptr [esp + 0c0h]
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
    add esp, 0bch
    ret 4
  }
}

// @ 0x007a2a00
__declspec(naked) void FUN_007a2a00() {
  __asm {
    push -1
    push 1213d04h
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
    sub esp, 0b0h
    push ebx
    push ebp
    push esi
    push edi
    xor edi, edi
    mov dword ptr [esp + 24h], ecx
    mov dword ptr [esp + 3ch], edi
    mov dword ptr [esp + 40h], edi
    mov dword ptr [esp + 44h], edi
    mov ebx, dword ptr [esp + 0d0h]
    push ebx
    lea ecx, [esp + 40h]
    mov dword ptr [esp + 0cch], edi
    call EXT_7a0b90
    mov ecx, dword ptr [esp + 40h]
    mov ebp, dword ptr [esp + 3ch]
    sub ecx, ebp
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov esi, edx
    shr esi, 1fh
    add esi, edx
    push esi
    mov ecx, ebx
    call EXT_7a1100
    mov eax, 4
    mov dword ptr [esp + 50h], edi
    mov dword ptr [esp + 54h], edi
    mov dword ptr [esp + 58h], edi
    mov dword ptr [esp + 5ch], edi
    mov dword ptr [esp + 60h], edi
    mov dword ptr [esp + 64h], edi
    mov dword ptr [esp + 70h], edi
    mov dword ptr [esp + 74h], edi
    mov dword ptr [esp + 78h], edi
    mov dword ptr [esp + 84h], eax
    mov dword ptr [esp + 88h], edi
    mov dword ptr [esp + 8ch], edi
    mov dword ptr [esp + 90h], edi
    mov dword ptr [esp + 94h], edi
    mov dword ptr [esp + 98h], edi
    mov dword ptr [esp + 9ch], edi
    mov dword ptr [esp + 0a0h], edi
    mov dword ptr [esp + 0ach], eax
    mov dword ptr [esp + 0b0h], edi
    mov dword ptr [esp + 0b4h], edi
    mov dword ptr [esp + 0b8h], edi
    mov dword ptr [esp + 0bch], edi
    mov byte ptr [esp + 0c8h], 1
    cmp esi, edi
    _emit 0x0f
    _emit 0x86
    _emit 0xba
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jbe 0x7a2cba
    mov dword ptr [esp + 10h], edi
    mov dword ptr [esp + 18h], ebp
    mov dword ptr [esp + 20h], esi
    _emit 0xeb
    _emit 0x09  ; jmp 0x7a2b17
    _emit 0x8b
    _emit 0xff  ; data
    mov ebx, dword ptr [esp + 0d0h]
    mov eax, dword ptr [ebp + 4]
    mov esi, dword ptr [ebx]
    sub eax, dword ptr [ebp]
    add esi, dword ptr [esp + 10h]
    sar eax, 3
    push eax
    mov ecx, esi
    call EXT_79af80
    mov ebx, dword ptr [ebp + 4]
    sub ebx, dword ptr [ebp]
    mov dword ptr [esp + 1ch], edi
    sar ebx, 3
    mov dword ptr [esp + 14h], ebx
    cmp ebx, edi
    _emit 0x0f
    _emit 0x86
    _emit 0x58
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jbe 0x7a2c9f
    _emit 0xeb
    _emit 0x07  ; jmp 0x7a2b50
    _emit 0x8d
    _emit 0xa4
    _emit 0x24
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; data
    mov ecx, dword ptr [ebp]
    mov edx, dword ptr [esp + 1ch]
    mov eax, dword ptr [ecx + edx*8]
    lea ebp, [ecx + edx*8]
    lea ecx, [esp + 50h]
    push ecx
    mov ecx, dword ptr [esp + 28h]
    push eax
    call EXT_7a1bc0
    mov eax, dword ptr [esp + 50h]
    cmp eax, edi
    _emit 0x0f
    _emit 0x84
    _emit 0x86
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x7a2bfe
    mov edx, dword ptr [ebp + 4]
    mov ecx, eax
    lea edi, [eax + 4]
    mov dword ptr [esp + 34h], ecx
    mov eax, edi
    mov ebx, 1
    lock xadd dword ptr [eax], ebx
    mov dword ptr [esp + 38h], edx
    mov eax, dword ptr [esi + 4]
    mov byte ptr [esp + 0c8h], 2
    cmp eax, dword ptr [esi + 8]
    _emit 0x73
    _emit 0x1a  ; jae 0x7a2bbd
    lea ebx, [eax + 8]
    mov dword ptr [esi + 4], ebx
    test eax, eax
    _emit 0x74
    _emit 0x21  ; je 0x7a2bce
    mov dword ptr [eax], ecx
    mov ebx, 1
    lock xadd dword ptr [edi], ebx
    mov dword ptr [eax + 4], edx
    _emit 0xeb
    _emit 0x11  ; jmp 0x7a2bce
    lea ecx, [esp + 34h]
    push ecx
    push eax
    mov ecx, esi
    call EXT_79f4e0
    mov ecx, dword ptr [esp + 34h]
    mov byte ptr [esp + 0c8h], 1
    test ecx, ecx
    _emit 0x74
    _emit 0x1e  ; je 0x7a2bf8
    lea eax, [ecx + 4]
    mov edx, eax
    or edi, 0ffffffffh
    lock xadd dword ptr [edx], edi
    dec edi
    _emit 0x75
    _emit 0x0f  ; jne 0x7a2bf8
    mov edx, 1
    xchg dword ptr [eax], edx
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax]
    push 1
    call edx
    mov ebx, dword ptr [esp + 14h]
    xor edi, edi
    mov ecx, dword ptr [esp + 54h]
    cmp ecx, edi
    _emit 0x0f
    _emit 0x84
    _emit 0x80
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x7a2c8a
    mov edx, dword ptr [ebp + 4]
    lea edi, [ecx + 4]
    mov dword ptr [esp + 28h], ecx
    mov eax, edi
    mov ebp, 1
    lock xadd dword ptr [eax], ebp
    mov dword ptr [esp + 2ch], edx
    mov eax, dword ptr [esi + 4]
    mov byte ptr [esp + 0c8h], 3
    cmp eax, dword ptr [esi + 8]
    _emit 0x73
    _emit 0x1a  ; jae 0x7a2c4d
    lea ebp, [eax + 8]
    mov dword ptr [esi + 4], ebp
    test eax, eax
    _emit 0x74
    _emit 0x21  ; je 0x7a2c5e
    mov dword ptr [eax], ecx
    mov ebp, 1
    lock xadd dword ptr [edi], ebp
    mov dword ptr [eax + 4], edx
    _emit 0xeb
    _emit 0x11  ; jmp 0x7a2c5e
    lea ecx, [esp + 28h]
    push ecx
    push eax
    mov ecx, esi
    call EXT_79f4e0
    mov ecx, dword ptr [esp + 28h]
    mov byte ptr [esp + 0c8h], 1
    test ecx, ecx
    _emit 0x74
    _emit 0x1e  ; je 0x7a2c88
    lea eax, [ecx + 4]
    mov edx, eax
    or edi, 0ffffffffh
    lock xadd dword ptr [edx], edi
    dec edi
    _emit 0x75
    _emit 0x0f  ; jne 0x7a2c88
    mov edx, 1
    xchg dword ptr [eax], edx
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax]
    push 1
    call edx
    xor edi, edi
    mov eax, dword ptr [esp + 1ch]
    mov ebp, dword ptr [esp + 18h]
    inc eax
    mov dword ptr [esp + 1ch], eax
    cmp eax, ebx
    _emit 0x0f
    _emit 0x82
    _emit 0xb1
    _emit 0xfe
    _emit 0xff
    _emit 0xff  ; jb 0x7a2b50
    add dword ptr [esp + 10h], 14h
    add ebp, 14h
    sub dword ptr [esp + 20h], 1
    mov dword ptr [esp + 18h], ebp
    _emit 0x0f
    _emit 0x85
    _emit 0x5a
    _emit 0xfe
    _emit 0xff
    _emit 0xff  ; jne 0x7a2b10
    mov ebp, dword ptr [esp + 3ch]
    lea ecx, [esp + 50h]
    mov byte ptr [esp + 0c8h], 0
    call EXT_79aeb0
    mov eax, dword ptr [esp + 40h]
    push eax
    push ebp
    lea ecx, [esp + 44h]
    mov dword ptr [esp + 0d0h], 4
    call EXT_79b0d0
    cmp ebp, edi
    _emit 0x74
    _emit 0x0e  ; je 0x7a2cf7
    cmp dword ptr [ebp - 4], edi
    _emit 0x74
    _emit 0x09  ; je 0x7a2cf7
    push ebp
    call EXT_f47380
    add esp, 4
    mov ecx, dword ptr [esp + 0c0h]
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
    add esp, 0bch
    ret 4
  }
}

// @ 0x007a2d20
__declspec(naked) void FUN_007a2d20() {
  __asm {
    push ebp
    mov ebp, esp
    and esp, 0fffffff8h
    push -1
    push 1213d65h
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
    sub esp, 140h
    push ebx
    push esi
    push edi
    xor edi, edi
    mov dword ptr [esp + 5ch], ecx
    mov dword ptr [esp + 48h], edi
    mov dword ptr [esp + 4ch], edi
    mov dword ptr [esp + 50h], edi
    mov ebx, dword ptr [ebp + 8]
    push ebx
    lea ecx, [esp + 4ch]
    mov dword ptr [esp + 158h], edi
    call EXT_7a0b90
    mov eax, 4
    mov dword ptr [esp + 0d8h], edi
    mov dword ptr [esp + 0dch], edi
    mov dword ptr [esp + 0e0h], edi
    mov dword ptr [esp + 0e4h], edi
    mov dword ptr [esp + 0e8h], edi
    mov dword ptr [esp + 0ech], edi
    mov dword ptr [esp + 0f8h], edi
    mov dword ptr [esp + 0fch], edi
    mov dword ptr [esp + 100h], edi
    mov dword ptr [esp + 10ch], eax
    mov dword ptr [esp + 110h], edi
    mov dword ptr [esp + 114h], edi
    mov dword ptr [esp + 118h], edi
    mov dword ptr [esp + 11ch], edi
    mov dword ptr [esp + 120h], edi
    mov dword ptr [esp + 124h], edi
    mov dword ptr [esp + 128h], edi
    mov dword ptr [esp + 134h], eax
    mov dword ptr [esp + 138h], edi
    mov dword ptr [esp + 13ch], edi
    mov dword ptr [esp + 140h], edi
    mov dword ptr [esp + 144h], edi
    mov dword ptr [esp + 68h], edi
    mov dword ptr [esp + 6ch], edi
    mov dword ptr [esp + 70h], edi
    mov dword ptr [esp + 74h], edi
    mov dword ptr [esp + 78h], edi
    mov dword ptr [esp + 7ch], edi
    mov dword ptr [esp + 88h], edi
    mov dword ptr [esp + 8ch], edi
    mov dword ptr [esp + 90h], edi
    mov dword ptr [esp + 9ch], eax
    mov dword ptr [esp + 0a0h], edi
    mov dword ptr [esp + 0a4h], edi
    mov dword ptr [esp + 0a8h], edi
    mov dword ptr [esp + 0ach], edi
    mov dword ptr [esp + 0b0h], edi
    mov dword ptr [esp + 0b4h], edi
    mov dword ptr [esp + 0b8h], edi
    mov dword ptr [esp + 0c4h], eax
    mov dword ptr [esp + 0c8h], edi
    mov dword ptr [esp + 0cch], edi
    mov dword ptr [esp + 0d0h], edi
    mov dword ptr [esp + 0d4h], edi
    mov ecx, dword ptr [esp + 4ch]
    sub ecx, dword ptr [esp + 48h]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov esi, edx
    shr esi, 1fh
    add esi, edx
    lea eax, [esi + esi]
    push eax
    mov ecx, ebx
    mov byte ptr [esp + 158h], 2
    call EXT_7a1100
    cmp esi, edi
    _emit 0x0f
    _emit 0x86
    _emit 0xe9
    _emit 0x02
    _emit 0x00
    _emit 0x00  ; jbe 0x7a31ae
    mov eax, dword ptr [esp + 48h]
    mov dword ptr [esp + 24h], edi
    mov dword ptr [esp + 14h], eax
    mov dword ptr [esp + 28h], esi
    _emit 0xeb
    _emit 0x07  ; jmp 0x7a2ede
    mov ebx, dword ptr [ebp + 8]
    mov eax, dword ptr [esp + 14h]
    mov ecx, dword ptr [ebx]
    mov edx, dword ptr [esp + 24h]
    lea ebx, [edx + ecx]
    mov edx, dword ptr [eax + 4]
    sub edx, dword ptr [eax]
    lea ecx, [ebx + 14h]
    sar edx, 3
    mov dword ptr [esp + 20h], ecx
    push edx
    mov ecx, ebx
    mov dword ptr [esp + 10h], ebx
    call EXT_79af80
    mov esi, dword ptr [esp + 14h]
    mov eax, dword ptr [esi + 4]
    sub eax, dword ptr [esi]
    mov ecx, dword ptr [esp + 20h]
    sar eax, 3
    push eax
    call EXT_79af80
    mov eax, dword ptr [esi + 4]
    sub eax, dword ptr [esi]
    mov dword ptr [esp + 1ch], edi
    sar eax, 3
    mov dword ptr [esp + 2ch], eax
    cmp eax, edi
    _emit 0x0f
    _emit 0x86
    _emit 0x67
    _emit 0x02
    _emit 0x00
    _emit 0x00  ; jbe 0x7a3197
    mov ecx, dword ptr [esi]
    mov edx, dword ptr [esp + 1ch]
    mov eax, dword ptr [ecx + edx*8]
    lea edi, [ecx + edx*8]
    lea ecx, [esp + 68h]
    push ecx
    mov ecx, dword ptr [esp + 60h]
    lea edx, [esp + 0dch]
    push edx
    push eax
    mov dword ptr [esp + 24h], edi
    call EXT_7a1d00
    mov eax, dword ptr [esp + 0d8h]
    test eax, eax
    _emit 0x0f
    _emit 0x84
    _emit 0x8a
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x7a2ff0
    mov edx, dword ptr [edi + 4]
    mov ecx, eax
    add eax, 4
    mov dword ptr [esp + 40h], ecx
    mov dword ptr [esp + 10h], eax
    mov esi, 1
    lock xadd dword ptr [eax], esi
    mov dword ptr [esp + 44h], edx
    mov eax, dword ptr [ebx + 4]
    mov byte ptr [esp + 154h], 3
    cmp eax, dword ptr [ebx + 8]
    _emit 0x73
    _emit 0x22  ; jae 0x7a2fb5
    lea esi, [eax + 8]
    mov dword ptr [ebx + 4], esi
    test eax, eax
    _emit 0x74
    _emit 0x29  ; je 0x7a2fc6
    mov esi, dword ptr [esp + 10h]
    mov dword ptr [eax], ecx
    mov ebx, 1
    lock xadd dword ptr [esi], ebx
    mov ebx, dword ptr [esp + 0ch]
    mov dword ptr [eax + 4], edx
    _emit 0xeb
    _emit 0x11  ; jmp 0x7a2fc6
    lea ecx, [esp + 40h]
    push ecx
    push eax
    mov ecx, ebx
    call EXT_79f4e0
    mov ecx, dword ptr [esp + 40h]
    mov byte ptr [esp + 154h], 2
    test ecx, ecx
    _emit 0x74
    _emit 0x1e  ; je 0x7a2ff0
    lea eax, [ecx + 4]
    mov edx, eax
    or esi, 0ffffffffh
    lock xadd dword ptr [edx], esi
    dec esi
    _emit 0x75
    _emit 0x0f  ; jne 0x7a2ff0
    mov edx, 1
    xchg dword ptr [eax], edx
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax]
    push 1
    call edx
    mov esi, dword ptr [esp + 0dch]
    test esi, esi
    _emit 0x74
    _emit 0x79  ; je 0x7a3074
    mov edx, dword ptr [edi + 4]
    mov ecx, esi
    add esi, 4
    mov dword ptr [esp + 60h], ecx
    mov eax, esi
    mov ebx, 1
    lock xadd dword ptr [eax], ebx
    mov dword ptr [esp + 64h], edx
    mov ebx, dword ptr [esp + 0ch]
    mov eax, dword ptr [ebx + 4]
    mov byte ptr [esp + 154h], 4
    cmp eax, dword ptr [ebx + 8]
    _emit 0x0f
    _emit 0x83
    _emit 0xec
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jae 0x7a321a
    lea edi, [eax + 8]
    mov dword ptr [ebx + 4], edi
    test eax, eax
    _emit 0x74
    _emit 0x0e  ; je 0x7a3046
    mov dword ptr [eax], ecx
    mov edi, 1
    lock xadd dword ptr [esi], edi
    mov dword ptr [eax + 4], edx
    mov edi, dword ptr [esp + 18h]
    mov byte ptr [esp + 154h], 2
    test ecx, ecx
    _emit 0x74
    _emit 0x1e  ; je 0x7a3074
    lea eax, [ecx + 4]
    mov edx, eax
    or esi, 0ffffffffh
    lock xadd dword ptr [edx], esi
    dec esi
    _emit 0x75
    _emit 0x0f  ; jne 0x7a3074
    mov edx, 1
    xchg dword ptr [eax], edx
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax]
    push 1
    call edx
    mov esi, dword ptr [esp + 68h]
    test esi, esi
    _emit 0x0f
    _emit 0x84
    _emit 0x7d
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x7a30fd
    mov edx, dword ptr [edi + 4]
    mov ecx, esi
    add esi, 4
    mov dword ptr [esp + 30h], ecx
    mov eax, esi
    mov ebx, 1
    lock xadd dword ptr [eax], ebx
    mov dword ptr [esp + 34h], edx
    mov ebx, dword ptr [esp + 20h]
    mov eax, dword ptr [ebx + 4]
    mov byte ptr [esp + 154h], 5
    cmp eax, dword ptr [ebx + 8]
    _emit 0x0f
    _emit 0x83
    _emit 0x7d
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jae 0x7a3230
    lea edi, [eax + 8]
    mov dword ptr [ebx + 4], edi
    test eax, eax
    _emit 0x74
    _emit 0x0e  ; je 0x7a30cb
    mov dword ptr [eax], ecx
    mov edi, 1
    lock xadd dword ptr [esi], edi
    mov dword ptr [eax + 4], edx
    mov edi, dword ptr [esp + 18h]
    mov ebx, dword ptr [esp + 0ch]
    mov byte ptr [esp + 154h], 2
    test ecx, ecx
    _emit 0x74
    _emit 0x1e  ; je 0x7a30fd
    lea eax, [ecx + 4]
    mov edx, eax
    or esi, 0ffffffffh
    lock xadd dword ptr [edx], esi
    dec esi
    _emit 0x75
    _emit 0x0f  ; jne 0x7a30fd
    mov edx, 1
    xchg dword ptr [eax], edx
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax]
    push 1
    call edx
    mov esi, dword ptr [esp + 6ch]
    test esi, esi
    _emit 0x74
    _emit 0x79  ; je 0x7a317e
    mov edx, dword ptr [edi + 4]
    mov ecx, esi
    add esi, 4
    mov dword ptr [esp + 38h], ecx
    mov eax, esi
    mov edi, 1
    lock xadd dword ptr [eax], edi
    mov dword ptr [esp + 3ch], edx
    mov edi, dword ptr [esp + 20h]
    mov eax, dword ptr [edi + 4]
    mov byte ptr [esp + 154h], 6
    cmp eax, dword ptr [edi + 8]
    _emit 0x0f
    _emit 0x83
    _emit 0x0e
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jae 0x7a3246
    lea ebx, [eax + 8]
    mov dword ptr [edi + 4], ebx
    test eax, eax
    _emit 0x74
    _emit 0x0e  ; je 0x7a3150
    mov dword ptr [eax], ecx
    mov edi, 1
    lock xadd dword ptr [esi], edi
    mov dword ptr [eax + 4], edx
    mov ebx, dword ptr [esp + 0ch]
    mov byte ptr [esp + 154h], 2
    test ecx, ecx
    _emit 0x74
    _emit 0x1e  ; je 0x7a317e
    lea eax, [ecx + 4]
    mov edx, eax
    or esi, 0ffffffffh
    lock xadd dword ptr [edx], esi
    dec esi
    _emit 0x75
    _emit 0x0f  ; jne 0x7a317e
    mov edx, 1
    xchg dword ptr [eax], edx
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax]
    push 1
    call edx
    mov eax, dword ptr [esp + 1ch]
    mov esi, dword ptr [esp + 14h]
    inc eax
    mov dword ptr [esp + 1ch], eax
    cmp eax, dword ptr [esp + 2ch]
    _emit 0x0f
    _emit 0x82
    _emit 0x9b
    _emit 0xfd
    _emit 0xff
    _emit 0xff  ; jb 0x7a2f30
    xor edi, edi
    add dword ptr [esp + 24h], 28h
    add esi, 14h
    sub dword ptr [esp + 28h], 1
    mov dword ptr [esp + 14h], esi
    _emit 0x0f
    _emit 0x85
    _emit 0x29
    _emit 0xfd
    _emit 0xff
    _emit 0xff  ; jne 0x7a2ed7
    lea ecx, [esp + 68h]
    mov byte ptr [esp + 154h], 1
    call EXT_79aeb0
    lea ecx, [esp + 0d8h]
    mov byte ptr [esp + 154h], 0
    call EXT_79aeb0
    mov eax, dword ptr [esp + 4ch]
    mov esi, dword ptr [esp + 48h]
    push eax
    push esi
    lea ecx, [esp + 50h]
    mov dword ptr [esp + 15ch], 7
    call EXT_79b0d0
    cmp esi, edi
    _emit 0x74
    _emit 0x0e  ; je 0x7a3203
    cmp dword ptr [esi - 4], edi
    _emit 0x74
    _emit 0x09  ; je 0x7a3203
    push esi
    call EXT_f47380
    add esp, 4
    mov ecx, dword ptr [esp + 14ch]
    pop edi
    pop esi
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    pop ebx
    mov esp, ebp
    pop ebp
    ret 4
    lea ecx, [esp + 60h]
    push ecx
    push eax
    mov ecx, ebx
    call EXT_79f4e0
    mov ecx, dword ptr [esp + 60h]
    _emit 0xe9
    _emit 0x1a
    _emit 0xfe
    _emit 0xff
    _emit 0xff  ; jmp 0x7a304a
    lea ecx, [esp + 30h]
    push ecx
    push eax
    mov ecx, ebx
    call EXT_79f4e0
    mov ecx, dword ptr [esp + 30h]
    _emit 0xe9
    _emit 0x89
    _emit 0xfe
    _emit 0xff
    _emit 0xff  ; jmp 0x7a30cf
    lea ecx, [esp + 38h]
    push ecx
    push eax
    mov ecx, edi
    call EXT_79f4e0
    mov ecx, dword ptr [esp + 38h]
    _emit 0xe9
    _emit 0xf8
    _emit 0xfe
    _emit 0xff
    _emit 0xff  ; jmp 0x7a3154
  }
}


