// slice s007a1740
// Per-instruction reconstruction (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
// Control flow is decoded recursively; call targets are symbolic so COFF
// relocation bytes are masked by the verifier. Unreachable bytes are data.

extern "C" void EXT_42d020();
extern "C" void EXT_4772a0();
extern "C" void EXT_719170();
extern "C" void EXT_71f7e0();
extern "C" void EXT_7201d0();
extern "C" void EXT_735dd0();
extern "C" void EXT_79aeb0();
extern "C" void EXT_79af80();
extern "C" void EXT_79b0d0();
extern "C" void EXT_79b630();
extern "C" void EXT_79b7b0();
extern "C" void EXT_79bfa0();
extern "C" void EXT_79c960();
extern "C" void EXT_79d190();
extern "C" void EXT_79dce0();
extern "C" void EXT_79e950();
extern "C" void EXT_79f4e0();
extern "C" void EXT_7a0b90();
extern "C" void EXT_7a0de0();
extern "C" void EXT_7a1100();
extern "C" void EXT_7a1400();
extern "C" void EXT_7a1740();
extern "C" void EXT_7a1940();
extern "C" void EXT_f47380();

// @ 0x007a1740
__declspec(naked) void FUN_007a1740() {
  __asm {
    push -1
    push 120ee28h
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
    sub esp, 20h
    push ebx
    mov ebx, ecx
    mov ecx, dword ptr [ebx]
    mov edx, dword ptr [ecx + 34h]
    sub edx, dword ptr [ecx + 30h]
    mov eax, 66666667h
    imul edx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    push esi
    push edi
    mov dword ptr [esp + 18h], ebx
    test eax, eax
    _emit 0x0f
    _emit 0x8e
    _emit 0x39
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jle 0x7a18bb
    mov edi, dword ptr [esp + 3ch]
    lea edx, [edi + 8]
    push edx
    add ecx, 8
    call EXT_735dd0
    mov ecx, dword ptr [edi + 20h]
    sub ecx, dword ptr [edi + 1ch]
    mov esi, dword ptr [ebx]
    mov eax, 0ea0ea0ebh
    imul ecx
    add edx, ecx
    sar edx, 7
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    push eax
    lea ecx, [esi + 1ch]
    call EXT_71f7e0
    mov ecx, dword ptr [edi + 20h]
    sub ecx, dword ptr [edi + 1ch]
    mov eax, 0ea0ea0ebh
    imul ecx
    add edx, ecx
    sar edx, 7
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    xor ecx, ecx
    cmp eax, ecx
    _emit 0x0f
    _emit 0x8e
    _emit 0x0e
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jle 0x7a18e7
    push ebp
    mov dword ptr [esp + 14h], ecx
    mov dword ptr [esp + 10h], ecx
    mov dword ptr [esp + 18h], eax
    _emit 0xeb
    _emit 0x0c  ; jmp 0x7a17f4
    _emit 0xeb
    _emit 0x06
    _emit 0x8d
    _emit 0x9b
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; data
    mov ecx, dword ptr [esp + 10h]
    mov eax, dword ptr [ebx]
    mov edi, dword ptr [edi + 1ch]
    mov esi, dword ptr [eax + 1ch]
    mov ebx, dword ptr [ebx + 48h]
    add ebx, dword ptr [esp + 14h]
    add edi, ecx
    add esi, ecx
    mov ecx, dword ptr [edi + 10h]
    lea edx, [edi + 14h]
    mov dword ptr [esi + 10h], ecx
    push edx
    lea ecx, [esi + 14h]
    call EXT_719170
    lea ebp, [edi + 44h]
    lea edi, [esi + 44h]
    cmp edi, ebp
    _emit 0x74
    _emit 0x22  ; je 0x7a1845
    mov eax, dword ptr [edi + 4]
    mov ecx, dword ptr [edi]
    push eax
    push ecx
    mov ecx, edi
    call EXT_4772a0
    mov edx, dword ptr [esp + 40h]
    mov eax, dword ptr [ebp + 4]
    mov ebp, dword ptr [ebp]
    push edx
    push eax
    push ebp
    mov ecx, edi
    call EXT_42d020
    mov eax, dword ptr [ebx]
    mov ebx, dword ptr [ebx + 4]
    sub ebx, eax
    sar ebx, 1
    _emit 0x74
    _emit 0x48  ; je 0x7a1898
    mov dword ptr [esp + 24h], eax
    mov eax, 2
    mov ecx, eax
    xor edi, edi
    mov dword ptr [esp + 20h], ebx
    mov word ptr [esp + 28h], ax
    mov word ptr [esp + 2ah], cx
    mov dword ptr [esp + 2ch], edi
    lea edx, [esp + 20h]
    push esi
    push edx
    mov dword ptr [esp + 40h], edi
    call EXT_7201d0
    mov ecx, dword ptr [esp + 34h]
    add esp, 8
    mov dword ptr [esp + 38h], 0ffffffffh
    cmp ecx, edi
    _emit 0x74
    _emit 0x07  ; je 0x7a1898
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax + 4]
    call edx
    add dword ptr [esp + 10h], 8ch
    add dword ptr [esp + 14h], 14h
    sub dword ptr [esp + 18h], 1
    mov ebx, dword ptr [esp + 1ch]
    mov edi, dword ptr [esp + 40h]
    _emit 0x0f
    _emit 0x85
    _emit 0x38
    _emit 0xff
    _emit 0xff
    _emit 0xff  ; jne 0x7a17f0
    pop ebp
    _emit 0xeb
    _emit 0x2c  ; jmp 0x7a18e7
    test ecx, ecx
    _emit 0x74
    _emit 0x24  ; je 0x7a18e3
    lea eax, [ecx + 4]
    mov dword ptr [ebx], 0
    mov edx, eax
    or esi, 0ffffffffh
    lock xadd dword ptr [edx], esi
    dec esi
    _emit 0x75
    _emit 0x0f  ; jne 0x7a18e3
    mov edx, 1
    xchg dword ptr [eax], edx
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax]
    push 1
    call edx
    mov edi, dword ptr [esp + 3ch]
    push edi
    lea ecx, [ebx + 8]
    call EXT_7a1400
    mov ecx, dword ptr [ebx + 4]
    cmp eax, ecx
    _emit 0x74
    _emit 0x35  ; je 0x7a192c
    test eax, eax
    _emit 0x74
    _emit 0x0c  ; je 0x7a1907
    lea edx, [eax + 4]
    mov esi, 1
    lock xadd dword ptr [edx], esi
    mov dword ptr [ebx + 4], eax
    test ecx, ecx
    _emit 0x74
    _emit 0x1e  ; je 0x7a192c
    lea eax, [ecx + 4]
    mov edx, eax
    or esi, 0ffffffffh
    lock xadd dword ptr [edx], esi
    dec esi
    _emit 0x75
    _emit 0x0f  ; jne 0x7a192c
    mov edx, 1
    xchg dword ptr [eax], edx
    mov eax, dword ptr [ecx]
    mov edx, dword ptr [eax]
    push 1
    call edx
    mov ecx, dword ptr [esp + 2ch]
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
    add esp, 2ch
    ret 4
  }
}

// @ 0x007a1940
__declspec(naked) void FUN_007a1940() {
  __asm {
    sub esp, 1ch
    push ebx
    mov dword ptr [esp + 8], ecx
    push ebp
    mov ebp, dword ptr [esp + 28h]
    mov ecx, dword ptr [ebp + 20h]
    sub ecx, dword ptr [ebp + 1ch]
    mov eax, 0ea0ea0ebh
    imul ecx
    add edx, ecx
    mov ecx, dword ptr [ebp + 34h]
    sub ecx, dword ptr [ebp + 30h]
    sar edx, 7
    mov ebx, dword ptr [esp + 2ch]
    mov eax, edx
    push esi
    shr eax, 1fh
    add eax, edx
    push edi
    push eax
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov ecx, edx
    shr ecx, 1fh
    add ecx, edx
    push ecx
    mov ecx, ebx
    call EXT_7a0de0
    mov ecx, dword ptr [ebp + 34h]
    sub ecx, dword ptr [ebp + 30h]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    _emit 0x0f
    _emit 0x84
    _emit 0xc1
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x7a1a6a
    lea edi, [ebx + 8]
    mov dword ptr [esp + 34h], 0
    mov dword ptr [esp + 10h], eax
    mov esi, dword ptr [ebp + 30h]
    add esi, dword ptr [esp + 34h]
    push edi
    mov eax, dword ptr [esi + 8]
    mov edx, dword ptr [esi]
    mov ecx, dword ptr [esi + 0ch]
    mov dword ptr [esp + 24h], eax
    mov eax, dword ptr [esi + 10h]
    mov dword ptr [esp + 2ch], eax
    mov dword ptr [esp + 1ch], edx
    mov edx, dword ptr [esi + 4]
    mov dword ptr [esp + 28h], ecx
    mov ecx, dword ptr [ebx + 48h]
    lea eax, [edx + edx*4]
    add eax, eax
    add eax, eax
    mov ebp, dword ptr [ecx + eax + 4]
    sub ebp, dword ptr [ecx + eax]
    add ecx, eax
    mov ecx, dword ptr [esp + 1ch]
    sar ebp, 1
    mov dword ptr [ebx + 64h], ebp
    mov ebp, dword ptr [esp + 34h]
    mov dword ptr [edi + 2ch], ecx
    mov ecx, dword ptr [edi + 18h]
    mov dword ptr [edi + 30h], edx
    mov edx, dword ptr [esp + 2ch]
    add ecx, eax
    mov dword ptr [edi + 3ch], edx
    mov eax, dword ptr [ecx + 4]
    sub eax, dword ptr [ecx]
    sar eax, 1
    mov dword ptr [edi + 34h], eax
    mov eax, dword ptr [esi + 4]
    mov edx, dword ptr [ebx + 48h]
    lea ecx, [eax + eax*4]
    lea eax, [edx + ecx*4]
    mov ecx, dword ptr [esp + 18h]
    push eax
    push esi
    push ebp
    call EXT_79b7b0
    mov ecx, dword ptr [esi]
    mov edx, dword ptr [esi + 4]
    sub esp, 14h
    mov eax, esp
    mov dword ptr [eax], ecx
    mov ecx, dword ptr [esi + 8]
    mov dword ptr [eax + 4], edx
    mov edx, dword ptr [esi + 0ch]
    mov dword ptr [eax + 8], ecx
    mov ecx, dword ptr [esi + 10h]
    mov dword ptr [eax + 0ch], edx
    mov dword ptr [eax + 10h], ecx
    mov ecx, ebx
    call EXT_79b630
    add dword ptr [esp + 34h], 14h
    sub dword ptr [esp + 10h], 1
    _emit 0x0f
    _emit 0x85
    _emit 0x4e
    _emit 0xff
    _emit 0xff
    _emit 0xff  ; jne 0x7a19b8
    push ebp
    mov ecx, ebx
    call EXT_7a1740
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 1ch
    ret 8
  }
}

// @ 0x007a1a80
__declspec(naked) void FUN_007a1a80() {
  __asm {
    sub esp, 1ch
    push ebx
    mov dword ptr [esp + 8], ecx
    push ebp
    mov ebp, dword ptr [esp + 28h]
    mov ecx, dword ptr [ebp + 20h]
    sub ecx, dword ptr [ebp + 1ch]
    mov eax, 0ea0ea0ebh
    imul ecx
    add edx, ecx
    mov ecx, dword ptr [ebp + 34h]
    sub ecx, dword ptr [ebp + 30h]
    sar edx, 7
    mov ebx, dword ptr [esp + 2ch]
    mov eax, edx
    push esi
    shr eax, 1fh
    add eax, edx
    push edi
    push eax
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov ecx, edx
    shr ecx, 1fh
    add ecx, edx
    push ecx
    mov ecx, ebx
    call EXT_7a0de0
    mov ecx, dword ptr [ebp + 34h]
    sub ecx, dword ptr [ebp + 30h]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    _emit 0x0f
    _emit 0x84
    _emit 0xc1
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x7a1baa
    lea edi, [ebx + 8]
    mov dword ptr [esp + 34h], 0
    mov dword ptr [esp + 10h], eax
    mov esi, dword ptr [ebp + 30h]
    add esi, dword ptr [esp + 34h]
    push edi
    mov eax, dword ptr [esi + 8]
    mov edx, dword ptr [esi]
    mov ecx, dword ptr [esi + 0ch]
    mov dword ptr [esp + 24h], eax
    mov eax, dword ptr [esi + 10h]
    mov dword ptr [esp + 2ch], eax
    mov dword ptr [esp + 1ch], edx
    mov edx, dword ptr [esi + 4]
    mov dword ptr [esp + 28h], ecx
    mov ecx, dword ptr [ebx + 48h]
    lea eax, [edx + edx*4]
    add eax, eax
    add eax, eax
    mov ebp, dword ptr [ecx + eax + 4]
    sub ebp, dword ptr [ecx + eax]
    add ecx, eax
    mov ecx, dword ptr [esp + 1ch]
    sar ebp, 1
    mov dword ptr [ebx + 64h], ebp
    mov ebp, dword ptr [esp + 34h]
    mov dword ptr [edi + 2ch], ecx
    mov ecx, dword ptr [edi + 18h]
    mov dword ptr [edi + 30h], edx
    mov edx, dword ptr [esp + 2ch]
    add ecx, eax
    mov dword ptr [edi + 3ch], edx
    mov eax, dword ptr [ecx + 4]
    sub eax, dword ptr [ecx]
    sar eax, 1
    mov dword ptr [edi + 34h], eax
    mov eax, dword ptr [esi + 4]
    mov edx, dword ptr [ebx + 48h]
    lea ecx, [eax + eax*4]
    lea eax, [edx + ecx*4]
    mov ecx, dword ptr [esp + 18h]
    push eax
    push esi
    push ebp
    call EXT_79bfa0
    mov ecx, dword ptr [esi]
    mov edx, dword ptr [esi + 4]
    sub esp, 14h
    mov eax, esp
    mov dword ptr [eax], ecx
    mov ecx, dword ptr [esi + 8]
    mov dword ptr [eax + 4], edx
    mov edx, dword ptr [esi + 0ch]
    mov dword ptr [eax + 8], ecx
    mov ecx, dword ptr [esi + 10h]
    mov dword ptr [eax + 0ch], edx
    mov dword ptr [eax + 10h], ecx
    mov ecx, ebx
    call EXT_79b630
    add dword ptr [esp + 34h], 14h
    sub dword ptr [esp + 10h], 1
    _emit 0x0f
    _emit 0x85
    _emit 0x4e
    _emit 0xff
    _emit 0xff
    _emit 0xff  ; jne 0x7a1af8
    push ebp
    mov ecx, ebx
    call EXT_7a1740
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 1ch
    ret 8
  }
}

// @ 0x007a1bc0
__declspec(naked) void FUN_007a1bc0() {
  __asm {
    sub esp, 1ch
    push ebx
    mov dword ptr [esp + 8], ecx
    push ebp
    mov ebp, dword ptr [esp + 28h]
    mov ecx, dword ptr [ebp + 20h]
    sub ecx, dword ptr [ebp + 1ch]
    mov eax, 0ea0ea0ebh
    imul ecx
    add edx, ecx
    mov ecx, dword ptr [ebp + 34h]
    sub ecx, dword ptr [ebp + 30h]
    sar edx, 7
    mov ebx, dword ptr [esp + 2ch]
    mov eax, edx
    push esi
    shr eax, 1fh
    add eax, edx
    push edi
    push eax
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov ecx, edx
    shr ecx, 1fh
    add ecx, edx
    push ecx
    mov ecx, ebx
    call EXT_7a0de0
    mov ecx, dword ptr [ebp + 34h]
    sub ecx, dword ptr [ebp + 30h]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    _emit 0x0f
    _emit 0x84
    _emit 0xc1
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x7a1cea
    lea edi, [ebx + 8]
    mov dword ptr [esp + 34h], 0
    mov dword ptr [esp + 10h], eax
    mov esi, dword ptr [ebp + 30h]
    add esi, dword ptr [esp + 34h]
    push edi
    mov eax, dword ptr [esi + 8]
    mov edx, dword ptr [esi]
    mov ecx, dword ptr [esi + 0ch]
    mov dword ptr [esp + 24h], eax
    mov eax, dword ptr [esi + 10h]
    mov dword ptr [esp + 2ch], eax
    mov dword ptr [esp + 1ch], edx
    mov edx, dword ptr [esi + 4]
    mov dword ptr [esp + 28h], ecx
    mov ecx, dword ptr [ebx + 48h]
    lea eax, [edx + edx*4]
    add eax, eax
    add eax, eax
    mov ebp, dword ptr [ecx + eax + 4]
    sub ebp, dword ptr [ecx + eax]
    add ecx, eax
    mov ecx, dword ptr [esp + 1ch]
    sar ebp, 1
    mov dword ptr [ebx + 64h], ebp
    mov ebp, dword ptr [esp + 34h]
    mov dword ptr [edi + 2ch], ecx
    mov ecx, dword ptr [edi + 18h]
    mov dword ptr [edi + 30h], edx
    mov edx, dword ptr [esp + 2ch]
    add ecx, eax
    mov dword ptr [edi + 3ch], edx
    mov eax, dword ptr [ecx + 4]
    sub eax, dword ptr [ecx]
    sar eax, 1
    mov dword ptr [edi + 34h], eax
    mov eax, dword ptr [esi + 4]
    mov edx, dword ptr [ebx + 48h]
    lea ecx, [eax + eax*4]
    lea eax, [edx + ecx*4]
    mov ecx, dword ptr [esp + 18h]
    push eax
    push esi
    push ebp
    call EXT_79c960
    mov ecx, dword ptr [esi]
    mov edx, dword ptr [esi + 4]
    sub esp, 14h
    mov eax, esp
    mov dword ptr [eax], ecx
    mov ecx, dword ptr [esi + 8]
    mov dword ptr [eax + 4], edx
    mov edx, dword ptr [esi + 0ch]
    mov dword ptr [eax + 8], ecx
    mov ecx, dword ptr [esi + 10h]
    mov dword ptr [eax + 0ch], edx
    mov dword ptr [eax + 10h], ecx
    mov ecx, ebx
    call EXT_79b630
    add dword ptr [esp + 34h], 14h
    sub dword ptr [esp + 10h], 1
    _emit 0x0f
    _emit 0x85
    _emit 0x4e
    _emit 0xff
    _emit 0xff
    _emit 0xff  ; jne 0x7a1c38
    push ebp
    mov ecx, ebx
    call EXT_7a1740
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 1ch
    ret 8
  }
}

// @ 0x007a1d00
__declspec(naked) void FUN_007a1d00() {
  __asm {
    sub esp, 34h
    push ebx
    mov dword ptr [esp + 0ch], ecx
    push ebp
    mov ebp, dword ptr [esp + 40h]
    mov ecx, dword ptr [ebp + 20h]
    sub ecx, dword ptr [ebp + 1ch]
    mov eax, 0ea0ea0ebh
    imul ecx
    add edx, ecx
    mov ecx, dword ptr [ebp + 34h]
    sub ecx, dword ptr [ebp + 30h]
    sar edx, 7
    mov ebx, dword ptr [esp + 44h]
    mov eax, edx
    push esi
    shr eax, 1fh
    add eax, edx
    push edi
    push eax
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov ecx, edx
    shr ecx, 1fh
    add ecx, edx
    push ecx
    mov ecx, ebx
    call EXT_7a0de0
    mov ecx, dword ptr [ebp + 20h]
    sub ecx, dword ptr [ebp + 1ch]
    mov eax, 0ea0ea0ebh
    imul ecx
    add edx, ecx
    mov ecx, dword ptr [ebp + 34h]
    sub ecx, dword ptr [ebp + 30h]
    sar edx, 7
    mov edi, dword ptr [esp + 50h]
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    push eax
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov ecx, edx
    shr ecx, 1fh
    add ecx, edx
    push ecx
    mov ecx, edi
    call EXT_7a0de0
    mov ecx, dword ptr [ebp + 34h]
    sub ecx, dword ptr [ebp + 30h]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    _emit 0x0f
    _emit 0x84
    _emit 0x78
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x7a1f1e
    add edi, 8
    add ebx, 8
    mov dword ptr [esp + 48h], 0
    mov dword ptr [esp + 10h], eax
    mov esi, dword ptr [ebp + 30h]
    add esi, dword ptr [esp + 48h]
    push edi
    mov edx, dword ptr [esi]
    mov eax, dword ptr [esi + 4]
    mov ecx, dword ptr [esi + 8]
    mov dword ptr [esp + 28h], ecx
    mov ecx, dword ptr [esi + 10h]
    mov dword ptr [esp + 24h], eax
    mov dword ptr [esp + 30h], ecx
    mov dword ptr [esp + 20h], edx
    mov edx, dword ptr [esi + 0ch]
    lea eax, [eax + eax*4]
    add eax, eax
    add eax, eax
    mov dword ptr [esp + 2ch], edx
    mov edx, dword ptr [esp + 50h]
    mov ecx, dword ptr [edx + 48h]
    mov edx, dword ptr [ecx + eax + 4]
    sub edx, dword ptr [ecx + eax]
    add ecx, eax
    mov ecx, dword ptr [esp + 50h]
    sar edx, 1
    mov dword ptr [ecx + 64h], edx
    mov ecx, dword ptr [esp + 20h]
    mov edx, dword ptr [esp + 24h]
    mov dword ptr [ebx + 2ch], ecx
    mov ecx, dword ptr [ebx + 18h]
    add ecx, eax
    mov dword ptr [ebx + 30h], edx
    mov edx, dword ptr [esp + 30h]
    mov dword ptr [ebx + 3ch], edx
    mov eax, dword ptr [ecx + 4]
    sub eax, dword ptr [ecx]
    push ebx
    sar eax, 1
    mov dword ptr [ebx + 34h], eax
    mov ecx, dword ptr [esi]
    mov eax, dword ptr [esi + 4]
    mov edx, dword ptr [esi + 8]
    mov dword ptr [esp + 38h], ecx
    mov ecx, dword ptr [esi + 0ch]
    mov dword ptr [esp + 3ch], eax
    mov dword ptr [esp + 44h], ecx
    mov ecx, dword ptr [esp + 58h]
    mov ecx, dword ptr [ecx + 48h]
    lea eax, [eax + eax*4]
    add eax, eax
    add eax, eax
    add ecx, eax
    mov dword ptr [esp + 40h], edx
    mov edx, dword ptr [esi + 10h]
    mov dword ptr [esp + 48h], edx
    mov edx, dword ptr [ecx + 4]
    sub edx, dword ptr [ecx]
    sar edx, 1
    mov ecx, edx
    mov edx, dword ptr [esp + 58h]
    mov dword ptr [edx + 64h], ecx
    mov ecx, dword ptr [esp + 3ch]
    mov dword ptr [edi + 30h], ecx
    mov ecx, dword ptr [esp + 38h]
    mov dword ptr [edi + 2ch], ecx
    mov ecx, dword ptr [esp + 48h]
    mov dword ptr [edi + 3ch], ecx
    mov ecx, dword ptr [edi + 18h]
    add ecx, eax
    mov eax, dword ptr [ecx + 4]
    sub eax, dword ptr [ecx]
    sar eax, 1
    mov dword ptr [edi + 34h], eax
    mov eax, dword ptr [esi + 4]
    mov ecx, dword ptr [edx + 48h]
    mov edx, dword ptr [esp + 54h]
    lea eax, [eax + eax*4]
    add eax, eax
    add eax, eax
    add ecx, eax
    push ecx
    mov ecx, dword ptr [edx + 48h]
    add ecx, eax
    push ecx
    mov ecx, dword ptr [esp + 28h]
    push esi
    push ebp
    call EXT_79d190
    mov edx, dword ptr [esi]
    mov ecx, dword ptr [esi + 4]
    sub esp, 14h
    mov eax, esp
    mov dword ptr [eax], edx
    mov edx, dword ptr [esi + 8]
    mov dword ptr [eax + 4], ecx
    mov ecx, dword ptr [esi + 0ch]
    mov dword ptr [eax + 8], edx
    mov edx, dword ptr [esi + 10h]
    mov dword ptr [eax + 0ch], ecx
    mov ecx, dword ptr [esp + 60h]
    mov dword ptr [eax + 10h], edx
    call EXT_79b630
    mov ecx, dword ptr [esi]
    mov edx, dword ptr [esi + 4]
    sub esp, 14h
    mov eax, esp
    mov dword ptr [eax], ecx
    mov ecx, dword ptr [esi + 8]
    mov dword ptr [eax + 4], edx
    mov edx, dword ptr [esi + 0ch]
    mov dword ptr [eax + 8], ecx
    mov ecx, dword ptr [esi + 10h]
    mov dword ptr [eax + 0ch], edx
    mov dword ptr [eax + 10h], ecx
    mov ecx, dword ptr [esp + 64h]
    call EXT_79b630
    add dword ptr [esp + 48h], 14h
    sub dword ptr [esp + 10h], 1
    _emit 0x0f
    _emit 0x85
    _emit 0xa2
    _emit 0xfe
    _emit 0xff
    _emit 0xff  ; jne 0x7a1db8
    mov ebx, dword ptr [esp + 4ch]
    mov edi, dword ptr [esp + 50h]
    push ebp
    mov ecx, ebx
    call EXT_7a1740
    push ebp
    mov ecx, edi
    call EXT_7a1740
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 34h
    ret 0ch
  }
}

// @ 0x007a1f40
__declspec(naked) void FUN_007a1f40() {
  __asm {
    sub esp, 34h
    push ebx
    mov dword ptr [esp + 0ch], ecx
    push ebp
    mov ebp, dword ptr [esp + 40h]
    mov ecx, dword ptr [ebp + 20h]
    sub ecx, dword ptr [ebp + 1ch]
    mov eax, 0ea0ea0ebh
    imul ecx
    add edx, ecx
    mov ecx, dword ptr [ebp + 34h]
    sub ecx, dword ptr [ebp + 30h]
    sar edx, 7
    mov ebx, dword ptr [esp + 44h]
    mov eax, edx
    push esi
    shr eax, 1fh
    add eax, edx
    push edi
    push eax
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov ecx, edx
    shr ecx, 1fh
    add ecx, edx
    push ecx
    mov ecx, ebx
    call EXT_7a0de0
    mov ecx, dword ptr [ebp + 20h]
    sub ecx, dword ptr [ebp + 1ch]
    mov eax, 0ea0ea0ebh
    imul ecx
    add edx, ecx
    mov ecx, dword ptr [ebp + 34h]
    sub ecx, dword ptr [ebp + 30h]
    sar edx, 7
    mov edi, dword ptr [esp + 50h]
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    push eax
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov ecx, edx
    shr ecx, 1fh
    add ecx, edx
    push ecx
    mov ecx, edi
    call EXT_7a0de0
    mov ecx, dword ptr [ebp + 34h]
    sub ecx, dword ptr [ebp + 30h]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    _emit 0x0f
    _emit 0x84
    _emit 0x78
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x7a215e
    add edi, 8
    add ebx, 8
    mov dword ptr [esp + 48h], 0
    mov dword ptr [esp + 10h], eax
    mov esi, dword ptr [ebp + 30h]
    add esi, dword ptr [esp + 48h]
    push edi
    mov edx, dword ptr [esi]
    mov eax, dword ptr [esi + 4]
    mov ecx, dword ptr [esi + 8]
    mov dword ptr [esp + 28h], ecx
    mov ecx, dword ptr [esi + 10h]
    mov dword ptr [esp + 24h], eax
    mov dword ptr [esp + 30h], ecx
    mov dword ptr [esp + 20h], edx
    mov edx, dword ptr [esi + 0ch]
    lea eax, [eax + eax*4]
    add eax, eax
    add eax, eax
    mov dword ptr [esp + 2ch], edx
    mov edx, dword ptr [esp + 50h]
    mov ecx, dword ptr [edx + 48h]
    mov edx, dword ptr [ecx + eax + 4]
    sub edx, dword ptr [ecx + eax]
    add ecx, eax
    mov ecx, dword ptr [esp + 50h]
    sar edx, 1
    mov dword ptr [ecx + 64h], edx
    mov ecx, dword ptr [esp + 20h]
    mov edx, dword ptr [esp + 24h]
    mov dword ptr [ebx + 2ch], ecx
    mov ecx, dword ptr [ebx + 18h]
    add ecx, eax
    mov dword ptr [ebx + 30h], edx
    mov edx, dword ptr [esp + 30h]
    mov dword ptr [ebx + 3ch], edx
    mov eax, dword ptr [ecx + 4]
    sub eax, dword ptr [ecx]
    push ebx
    sar eax, 1
    mov dword ptr [ebx + 34h], eax
    mov ecx, dword ptr [esi]
    mov eax, dword ptr [esi + 4]
    mov edx, dword ptr [esi + 8]
    mov dword ptr [esp + 38h], ecx
    mov ecx, dword ptr [esi + 0ch]
    mov dword ptr [esp + 3ch], eax
    mov dword ptr [esp + 44h], ecx
    mov ecx, dword ptr [esp + 58h]
    mov ecx, dword ptr [ecx + 48h]
    lea eax, [eax + eax*4]
    add eax, eax
    add eax, eax
    add ecx, eax
    mov dword ptr [esp + 40h], edx
    mov edx, dword ptr [esi + 10h]
    mov dword ptr [esp + 48h], edx
    mov edx, dword ptr [ecx + 4]
    sub edx, dword ptr [ecx]
    sar edx, 1
    mov ecx, edx
    mov edx, dword ptr [esp + 58h]
    mov dword ptr [edx + 64h], ecx
    mov ecx, dword ptr [esp + 3ch]
    mov dword ptr [edi + 30h], ecx
    mov ecx, dword ptr [esp + 38h]
    mov dword ptr [edi + 2ch], ecx
    mov ecx, dword ptr [esp + 48h]
    mov dword ptr [edi + 3ch], ecx
    mov ecx, dword ptr [edi + 18h]
    add ecx, eax
    mov eax, dword ptr [ecx + 4]
    sub eax, dword ptr [ecx]
    sar eax, 1
    mov dword ptr [edi + 34h], eax
    mov eax, dword ptr [esi + 4]
    mov ecx, dword ptr [edx + 48h]
    mov edx, dword ptr [esp + 54h]
    lea eax, [eax + eax*4]
    add eax, eax
    add eax, eax
    add ecx, eax
    push ecx
    mov ecx, dword ptr [edx + 48h]
    add ecx, eax
    push ecx
    mov ecx, dword ptr [esp + 28h]
    push esi
    push ebp
    call EXT_79dce0
    mov edx, dword ptr [esi]
    mov ecx, dword ptr [esi + 4]
    sub esp, 14h
    mov eax, esp
    mov dword ptr [eax], edx
    mov edx, dword ptr [esi + 8]
    mov dword ptr [eax + 4], ecx
    mov ecx, dword ptr [esi + 0ch]
    mov dword ptr [eax + 8], edx
    mov edx, dword ptr [esi + 10h]
    mov dword ptr [eax + 0ch], ecx
    mov ecx, dword ptr [esp + 60h]
    mov dword ptr [eax + 10h], edx
    call EXT_79b630
    mov ecx, dword ptr [esi]
    mov edx, dword ptr [esi + 4]
    sub esp, 14h
    mov eax, esp
    mov dword ptr [eax], ecx
    mov ecx, dword ptr [esi + 8]
    mov dword ptr [eax + 4], edx
    mov edx, dword ptr [esi + 0ch]
    mov dword ptr [eax + 8], ecx
    mov ecx, dword ptr [esi + 10h]
    mov dword ptr [eax + 0ch], edx
    mov dword ptr [eax + 10h], ecx
    mov ecx, dword ptr [esp + 64h]
    call EXT_79b630
    add dword ptr [esp + 48h], 14h
    sub dword ptr [esp + 10h], 1
    _emit 0x0f
    _emit 0x85
    _emit 0xa2
    _emit 0xfe
    _emit 0xff
    _emit 0xff  ; jne 0x7a1ff8
    mov ebx, dword ptr [esp + 4ch]
    mov edi, dword ptr [esp + 50h]
    push ebp
    mov ecx, ebx
    call EXT_7a1740
    push ebp
    mov ecx, edi
    call EXT_7a1740
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 34h
    ret 0ch
  }
}

// @ 0x007a2180
__declspec(naked) void FUN_007a2180() {
  __asm {
    sub esp, 34h
    push ebx
    mov dword ptr [esp + 0ch], ecx
    push ebp
    mov ebp, dword ptr [esp + 40h]
    mov ecx, dword ptr [ebp + 20h]
    sub ecx, dword ptr [ebp + 1ch]
    mov eax, 0ea0ea0ebh
    imul ecx
    add edx, ecx
    mov ecx, dword ptr [ebp + 34h]
    sub ecx, dword ptr [ebp + 30h]
    sar edx, 7
    mov ebx, dword ptr [esp + 44h]
    mov eax, edx
    push esi
    shr eax, 1fh
    add eax, edx
    push edi
    push eax
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov ecx, edx
    shr ecx, 1fh
    add ecx, edx
    push ecx
    mov ecx, ebx
    call EXT_7a0de0
    mov ecx, dword ptr [ebp + 20h]
    sub ecx, dword ptr [ebp + 1ch]
    mov eax, 0ea0ea0ebh
    imul ecx
    add edx, ecx
    mov ecx, dword ptr [ebp + 34h]
    sub ecx, dword ptr [ebp + 30h]
    sar edx, 7
    mov edi, dword ptr [esp + 50h]
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    push eax
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov ecx, edx
    shr ecx, 1fh
    add ecx, edx
    push ecx
    mov ecx, edi
    call EXT_7a0de0
    mov ecx, dword ptr [ebp + 34h]
    sub ecx, dword ptr [ebp + 30h]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    _emit 0x0f
    _emit 0x84
    _emit 0x78
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x7a239e
    add edi, 8
    add ebx, 8
    mov dword ptr [esp + 48h], 0
    mov dword ptr [esp + 10h], eax
    mov esi, dword ptr [ebp + 30h]
    add esi, dword ptr [esp + 48h]
    push edi
    mov edx, dword ptr [esi]
    mov eax, dword ptr [esi + 4]
    mov ecx, dword ptr [esi + 8]
    mov dword ptr [esp + 28h], ecx
    mov ecx, dword ptr [esi + 10h]
    mov dword ptr [esp + 24h], eax
    mov dword ptr [esp + 30h], ecx
    mov dword ptr [esp + 20h], edx
    mov edx, dword ptr [esi + 0ch]
    lea eax, [eax + eax*4]
    add eax, eax
    add eax, eax
    mov dword ptr [esp + 2ch], edx
    mov edx, dword ptr [esp + 50h]
    mov ecx, dword ptr [edx + 48h]
    mov edx, dword ptr [ecx + eax + 4]
    sub edx, dword ptr [ecx + eax]
    add ecx, eax
    mov ecx, dword ptr [esp + 50h]
    sar edx, 1
    mov dword ptr [ecx + 64h], edx
    mov ecx, dword ptr [esp + 20h]
    mov edx, dword ptr [esp + 24h]
    mov dword ptr [ebx + 2ch], ecx
    mov ecx, dword ptr [ebx + 18h]
    add ecx, eax
    mov dword ptr [ebx + 30h], edx
    mov edx, dword ptr [esp + 30h]
    mov dword ptr [ebx + 3ch], edx
    mov eax, dword ptr [ecx + 4]
    sub eax, dword ptr [ecx]
    push ebx
    sar eax, 1
    mov dword ptr [ebx + 34h], eax
    mov ecx, dword ptr [esi]
    mov eax, dword ptr [esi + 4]
    mov edx, dword ptr [esi + 8]
    mov dword ptr [esp + 38h], ecx
    mov ecx, dword ptr [esi + 0ch]
    mov dword ptr [esp + 3ch], eax
    mov dword ptr [esp + 44h], ecx
    mov ecx, dword ptr [esp + 58h]
    mov ecx, dword ptr [ecx + 48h]
    lea eax, [eax + eax*4]
    add eax, eax
    add eax, eax
    add ecx, eax
    mov dword ptr [esp + 40h], edx
    mov edx, dword ptr [esi + 10h]
    mov dword ptr [esp + 48h], edx
    mov edx, dword ptr [ecx + 4]
    sub edx, dword ptr [ecx]
    sar edx, 1
    mov ecx, edx
    mov edx, dword ptr [esp + 58h]
    mov dword ptr [edx + 64h], ecx
    mov ecx, dword ptr [esp + 3ch]
    mov dword ptr [edi + 30h], ecx
    mov ecx, dword ptr [esp + 38h]
    mov dword ptr [edi + 2ch], ecx
    mov ecx, dword ptr [esp + 48h]
    mov dword ptr [edi + 3ch], ecx
    mov ecx, dword ptr [edi + 18h]
    add ecx, eax
    mov eax, dword ptr [ecx + 4]
    sub eax, dword ptr [ecx]
    sar eax, 1
    mov dword ptr [edi + 34h], eax
    mov eax, dword ptr [esi + 4]
    mov ecx, dword ptr [edx + 48h]
    mov edx, dword ptr [esp + 54h]
    lea eax, [eax + eax*4]
    add eax, eax
    add eax, eax
    add ecx, eax
    push ecx
    mov ecx, dword ptr [edx + 48h]
    add ecx, eax
    push ecx
    mov ecx, dword ptr [esp + 28h]
    push esi
    push ebp
    call EXT_79e950
    mov edx, dword ptr [esi]
    mov ecx, dword ptr [esi + 4]
    sub esp, 14h
    mov eax, esp
    mov dword ptr [eax], edx
    mov edx, dword ptr [esi + 8]
    mov dword ptr [eax + 4], ecx
    mov ecx, dword ptr [esi + 0ch]
    mov dword ptr [eax + 8], edx
    mov edx, dword ptr [esi + 10h]
    mov dword ptr [eax + 0ch], ecx
    mov ecx, dword ptr [esp + 60h]
    mov dword ptr [eax + 10h], edx
    call EXT_79b630
    mov ecx, dword ptr [esi]
    mov edx, dword ptr [esi + 4]
    sub esp, 14h
    mov eax, esp
    mov dword ptr [eax], ecx
    mov ecx, dword ptr [esi + 8]
    mov dword ptr [eax + 4], edx
    mov edx, dword ptr [esi + 0ch]
    mov dword ptr [eax + 8], ecx
    mov ecx, dword ptr [esi + 10h]
    mov dword ptr [eax + 0ch], edx
    mov dword ptr [eax + 10h], ecx
    mov ecx, dword ptr [esp + 64h]
    call EXT_79b630
    add dword ptr [esp + 48h], 14h
    sub dword ptr [esp + 10h], 1
    _emit 0x0f
    _emit 0x85
    _emit 0xa2
    _emit 0xfe
    _emit 0xff
    _emit 0xff  ; jne 0x7a2238
    mov ebx, dword ptr [esp + 4ch]
    mov edi, dword ptr [esp + 50h]
    push ebp
    mov ecx, ebx
    call EXT_7a1740
    push ebp
    mov ecx, edi
    call EXT_7a1740
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 34h
    ret 0ch
  }
}

// @ 0x007a23c0
__declspec(naked) void FUN_007a23c0() {
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
    _emit 0x00  ; jbe 0x7a267a
    mov dword ptr [esp + 10h], edi
    mov dword ptr [esp + 18h], ebp
    mov dword ptr [esp + 20h], esi
    _emit 0xeb
    _emit 0x09  ; jmp 0x7a24d7
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
    _emit 0x00  ; jbe 0x7a265f
    _emit 0xeb
    _emit 0x07  ; jmp 0x7a2510
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
    call EXT_7a1940
    mov eax, dword ptr [esp + 50h]
    cmp eax, edi
    _emit 0x0f
    _emit 0x84
    _emit 0x86
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x7a25be
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
    _emit 0x1a  ; jae 0x7a257d
    lea ebx, [eax + 8]
    mov dword ptr [esi + 4], ebx
    test eax, eax
    _emit 0x74
    _emit 0x21  ; je 0x7a258e
    mov dword ptr [eax], ecx
    mov ebx, 1
    lock xadd dword ptr [edi], ebx
    mov dword ptr [eax + 4], edx
    _emit 0xeb
    _emit 0x11  ; jmp 0x7a258e
    lea ecx, [esp + 34h]
    push ecx
    push eax
    mov ecx, esi
    call EXT_79f4e0
    mov ecx, dword ptr [esp + 34h]
    mov byte ptr [esp + 0c8h], 1
    test ecx, ecx
    _emit 0x74
    _emit 0x1e  ; je 0x7a25b8
    lea eax, [ecx + 4]
    mov edx, eax
    or edi, 0ffffffffh
    lock xadd dword ptr [edx], edi
    dec edi
    _emit 0x75
    _emit 0x0f  ; jne 0x7a25b8
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
    _emit 0x00  ; je 0x7a264a
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
    _emit 0x1a  ; jae 0x7a260d
    lea ebp, [eax + 8]
    mov dword ptr [esi + 4], ebp
    test eax, eax
    _emit 0x74
    _emit 0x21  ; je 0x7a261e
    mov dword ptr [eax], ecx
    mov ebp, 1
    lock xadd dword ptr [edi], ebp
    mov dword ptr [eax + 4], edx
    _emit 0xeb
    _emit 0x11  ; jmp 0x7a261e
    lea ecx, [esp + 28h]
    push ecx
    push eax
    mov ecx, esi
    call EXT_79f4e0
    mov ecx, dword ptr [esp + 28h]
    mov byte ptr [esp + 0c8h], 1
    test ecx, ecx
    _emit 0x74
    _emit 0x1e  ; je 0x7a2648
    lea eax, [ecx + 4]
    mov edx, eax
    or edi, 0ffffffffh
    lock xadd dword ptr [edx], edi
    dec edi
    _emit 0x75
    _emit 0x0f  ; jne 0x7a2648
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
    _emit 0xff  ; jb 0x7a2510
    add dword ptr [esp + 10h], 14h
    add ebp, 14h
    sub dword ptr [esp + 20h], 1
    mov dword ptr [esp + 18h], ebp
    _emit 0x0f
    _emit 0x85
    _emit 0x5a
    _emit 0xfe
    _emit 0xff
    _emit 0xff  ; jne 0x7a24d0
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
    _emit 0x0e  ; je 0x7a26b7
    cmp dword ptr [ebp - 4], edi
    _emit 0x74
    _emit 0x09  ; je 0x7a26b7
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


