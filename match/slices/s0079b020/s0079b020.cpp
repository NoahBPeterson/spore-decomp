// slice s0079b020
// Per-instruction reconstruction (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
// Control flow is decoded recursively; call targets are symbolic so COFF
// relocation bytes are masked by the verifier. Unreachable bytes are data.

extern "C" void EXT_428900();
extern "C" void EXT_6ec390();
extern "C" void EXT_6f5bc0();
extern "C" void EXT_71ddc0();
extern "C" void EXT_72b630();
extern "C" void EXT_7658f0();
extern "C" void EXT_799840();
extern "C" void EXT_7998a0();
extern "C" void EXT_79a710();
extern "C" void EXT_79ace0();
extern "C" void EXT_79ae60();
extern "C" void EXT_79b4b0();
extern "C" void EXT_79b520();
extern "C" void EXT_79b5d0();
extern "C" void EXT_8dede0();
extern "C" void EXT_f47380();
extern "C" void EXT_f473a0();
extern "C" void EXT_11e0744();

// @ 0x0079b020
__declspec(naked) void FUN_0079b020() {
  __asm {
    push -1
    push 1213b58h
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
    push ebx
    mov ebx, dword ptr [esp + 18h]
    push esi
    push edi
    mov edi, ecx
    mov ecx, dword ptr [ebx + 4]
    sub ecx, dword ptr [ebx]
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov esi, edx
    shr esi, 1fh
    add esi, edx
    mov dword ptr [esp + 0ch], edi
    _emit 0x74
    _emit 0x25  ; je 0x79b080
    push 0d1h
    push 13ebb38h
    push 0
    lea eax, [esi + esi*4]
    add eax, eax
    push 0
    add eax, eax
    push 13eb8a4h
    push eax
    call EXT_f473a0
    add esp, 18h
    _emit 0xeb
    _emit 0x02  ; jmp 0x79b082
    xor eax, eax
    lea ecx, [esi + esi*4]
    lea edx, [eax + ecx*4]
    mov dword ptr [edi], eax
    mov dword ptr [edi + 4], eax
    mov dword ptr [edi + 8], edx
    mov edx, dword ptr [esp + 20h]
    mov ecx, dword ptr [ebx + 4]
    mov ebx, dword ptr [ebx]
    push edx
    push eax
    push ecx
    lea eax, [esp + 2ch]
    push ebx
    push eax
    mov dword ptr [esp + 2ch], 0
    call EXT_79a710
    mov ecx, dword ptr [esp + 34h]
    add esp, 14h
    mov dword ptr [edi + 4], ecx
    mov ecx, dword ptr [esp + 10h]
    mov eax, edi
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
    add esp, 10h
    ret 4
  }
}

// @ 0x0079b0d0
__declspec(naked) void FUN_0079b0d0() {
  __asm {
    _emit 0x64
    _emit 0xa1
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov eax, dword ptr fs:[0]
    push -1
    push 1213b78h
    push eax
    _emit 0x64
    _emit 0x89
    _emit 0x25
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], esp
    push ebx
    mov ebx, dword ptr [esp + 18h]
    push esi
    mov esi, dword ptr [esp + 18h]
    cmp esi, ebx
    _emit 0x73
    _emit 0x3e  ; jae 0x79b131
    mov eax, dword ptr [esi + 4]
    mov ecx, dword ptr [esi]
    push eax
    push ecx
    mov ecx, esi
    mov dword ptr [esp + 18h], 0
    call EXT_8dede0
    mov eax, dword ptr [esi]
    mov dword ptr [esp + 10h], 0ffffffffh
    test eax, eax
    _emit 0x74
    _emit 0x0f  ; je 0x79b126
    cmp dword ptr [eax - 4], 0
    _emit 0x74
    _emit 0x09  ; je 0x79b126
    push eax
    call EXT_f47380
    add esp, 4
    add esi, 14h
    mov dword ptr [esp + 18h], esi
    cmp esi, ebx
    _emit 0x72
    _emit 0xc2  ; jb 0x79b0f3
    mov ecx, dword ptr [esp + 8]
    pop esi
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    pop ebx
    add esp, 0ch
    ret 8
  }
}

// @ 0x0079b150
__declspec(naked) void FUN_0079b150() {
  __asm {
    push ebx
    mov ebx, dword ptr [esp + 8]
    push esi
    push edi
    mov edi, ecx
    mov ecx, dword ptr [ebx + 4]
    sub ecx, dword ptr [ebx]
    lea eax, [ebx + 0ch]
    sar ecx, 1
    push eax
    push ecx
    mov ecx, edi
    call EXT_799840
    mov esi, dword ptr [ebx + 4]
    mov ebx, dword ptr [ebx]
    mov eax, dword ptr [edi]
    sub esi, ebx
    push esi
    push ebx
    push eax
    call EXT_11e0744
    sar esi, 1
    lea eax, [eax + esi*2]
    add esp, 0ch
    mov dword ptr [edi + 4], eax
    mov eax, edi
    pop edi
    pop esi
    pop ebx
    ret 4
  }
}

// @ 0x0079b1c0
__declspec(naked) void FUN_0079b1c0() {
  __asm {
    _emit 0x64
    _emit 0xa1
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov eax, dword ptr fs:[0]
    mov ecx, dword ptr [esp + 4]
    push -1
    push 120f721h
    push eax
    _emit 0x64
    _emit 0x89
    _emit 0x25
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], esp
    mov eax, dword ptr [esp + 1ch]
    mov dword ptr [ecx], eax
    mov eax, dword ptr [esp + 14h]
    sub esp, 8
    cmp eax, dword ptr [esp + 20h]
    _emit 0x0f
    _emit 0x84
    _emit 0x98
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x79b288
    push ebx
    push ebp
    push esi
    push edi
    mov edi, dword ptr [ecx]
    mov dword ptr [esp + 10h], edi
    mov dword ptr [esp + 14h], edi
    mov dword ptr [esp + 20h], 0
    test edi, edi
    _emit 0x74
    _emit 0x5e  ; je 0x79b268
    mov esi, dword ptr [eax + 4]
    sub esi, dword ptr [eax]
    lea ebx, [eax + 4]
    sar esi, 1
    mov ebp, eax
    _emit 0x74
    _emit 0x21  ; je 0x79b239
    push 0d1h
    push 13ebb38h
    push 0
    push 0
    lea eax, [esi + esi]
    push 13eb8a4h
    push eax
    call EXT_f473a0
    add esp, 18h
    _emit 0xeb
    _emit 0x02  ; jmp 0x79b23b
    xor eax, eax
    lea ecx, [eax + esi*2]
    mov dword ptr [edi], eax
    mov dword ptr [edi + 4], eax
    mov dword ptr [edi + 8], ecx
    mov ecx, dword ptr [ebp]
    mov esi, dword ptr [ebx]
    sub esi, ecx
    push esi
    push ecx
    push eax
    call EXT_11e0744
    mov ecx, dword ptr [esp + 34h]
    add esp, 0ch
    sar esi, 1
    lea edx, [eax + esi*2]
    mov dword ptr [edi + 4], edx
    mov eax, dword ptr [esp + 2ch]
    add dword ptr [ecx], 14h
    add eax, 14h
    mov dword ptr [esp + 20h], 0ffffffffh
    mov dword ptr [esp + 2ch], eax
    cmp eax, dword ptr [esp + 30h]
    _emit 0x0f
    _emit 0x85
    _emit 0x70
    _emit 0xff
    _emit 0xff
    _emit 0xff  ; jne 0x79b1f4
    pop edi
    pop esi
    pop ebp
    pop ebx
    mov eax, ecx
    mov ecx, dword ptr [esp + 8]
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 14h
    ret
  }
}

// @ 0x0079b2a0
__declspec(naked) void FUN_0079b2a0() {
  __asm {
    push -1
    push 1210971h
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
    push ebp
    mov ebp, dword ptr [esp + 1ch]
    push edi
    mov edi, dword ptr [esp + 1ch]
    test ebp, ebp
    _emit 0x0f
    _emit 0x86
    _emit 0x7f
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; jbe 0x79b347
    push ebx
    mov ebx, dword ptr [esp + 28h]
    push esi
    mov edi, edi
    mov dword ptr [esp + 28h], edi
    mov dword ptr [esp + 10h], edi
    mov dword ptr [esp + 1ch], 0
    test edi, edi
    _emit 0x74
    _emit 0x51  ; je 0x79b335
    mov esi, dword ptr [ebx + 4]
    sub esi, dword ptr [ebx]
    sar esi, 1
    _emit 0x74
    _emit 0x21  ; je 0x79b30e
    push 0d1h
    push 13ebb38h
    push 0
    push 0
    lea eax, [esi + esi]
    push 13eb8a4h
    push eax
    call EXT_f473a0
    add esp, 18h
    _emit 0xeb
    _emit 0x02  ; jmp 0x79b310
    xor eax, eax
    lea ecx, [eax + esi*2]
    mov dword ptr [edi], eax
    mov dword ptr [edi + 4], eax
    mov dword ptr [edi + 8], ecx
    mov ecx, dword ptr [ebx]
    mov esi, dword ptr [ebx + 4]
    sub esi, ecx
    push esi
    push ecx
    push eax
    call EXT_11e0744
    add esp, 0ch
    sar esi, 1
    lea edx, [eax + esi*2]
    mov dword ptr [edi + 4], edx
    dec ebp
    add edi, 14h
    mov dword ptr [esp + 1ch], 0ffffffffh
    test ebp, ebp
    _emit 0x77
    _emit 0x8b  ; ja 0x79b2d0
    pop esi
    pop ebx
    mov ecx, dword ptr [esp + 0ch]
    pop edi
    pop ebp
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

// @ 0x0079b360
__declspec(naked) void FUN_0079b360() {
  __asm {
    push ebp
    mov ebp, dword ptr [esp + 8]
    push esi
    mov esi, ecx
    cmp ebp, esi
    _emit 0x0f
    _emit 0x84
    _emit 0xb1
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x79b421
    mov edx, dword ptr [ebp + 4]
    mov eax, dword ptr [ebp]
    mov ecx, dword ptr [esi + 8]
    push ebx
    mov ebx, dword ptr [esi]
    push edi
    mov edi, edx
    sub edi, eax
    sub ecx, ebx
    sar edi, 1
    sar ecx, 1
    cmp edi, ecx
    _emit 0x76
    _emit 0x3a  ; jbe 0x79b3c5
    push edx
    push eax
    push edi
    mov ecx, esi
    call EXT_79ae60
    mov ebx, eax
    mov eax, dword ptr [esi]
    test eax, eax
    _emit 0x74
    _emit 0x0f  ; je 0x79b3ac
    cmp dword ptr [eax - 4], 0
    _emit 0x74
    _emit 0x09  ; je 0x79b3ac
    push eax
    call EXT_f47380
    add esp, 4
    mov eax, ebx
    lea edx, [ebx + edi*2]
    lea ecx, [eax + edi*2]
    pop edi
    mov dword ptr [esi], ebx
    pop ebx
    mov dword ptr [esi + 8], edx
    mov dword ptr [esi + 4], ecx
    mov eax, esi
    pop esi
    pop ebp
    ret 4
    mov ecx, dword ptr [esi + 4]
    sub ecx, ebx
    sar ecx, 1
    cmp edi, ecx
    _emit 0x76
    _emit 0x3a  ; jbe 0x79b40a
    add ecx, ecx
    push ecx
    push eax
    push ebx
    call EXT_11e0744
    mov eax, dword ptr [esi + 4]
    mov ecx, dword ptr [ebp]
    mov edx, eax
    sub edx, dword ptr [esi]
    sar edx, 1
    lea ecx, [ecx + edx*2]
    mov edx, dword ptr [ebp + 4]
    sub edx, ecx
    push edx
    push ecx
    push eax
    call EXT_11e0744
    mov eax, dword ptr [esi]
    add esp, 18h
    lea ecx, [eax + edi*2]
    pop edi
    pop ebx
    mov dword ptr [esi + 4], ecx
    mov eax, esi
    pop esi
    pop ebp
    ret 4
    sub edx, eax
    push edx
    push eax
    push ebx
    call EXT_11e0744
    mov eax, dword ptr [esi]
    add esp, 0ch
    lea ecx, [eax + edi*2]
    pop edi
    mov dword ptr [esi + 4], ecx
    pop ebx
    mov eax, esi
    pop esi
    pop ebp
    ret 4
  }
}

// @ 0x0079b4b0
__declspec(naked) void FUN_0079b4b0() {
  __asm {
    sub esp, 10h
    mov eax, dword ptr [ecx + 8]
    mov edx, dword ptr [esp + 14h]
    xorps xmm0, xmm0
    push esi
    mov esi, dword ptr [esp + 1ch]
    add ecx, 4
    push edi
    xor edi, edi
    mov dword ptr [esp + 8], edx
    mov dword ptr [esp + 0ch], esi
    mov dword ptr [esp + 10h], edi
    movss dword ptr [esp + 14h], xmm0
    cmp eax, dword ptr [ecx + 8]
    _emit 0x73
    _emit 0x23  ; jae 0x79b502
    push ebx
    lea ebx, [eax + 10h]
    mov dword ptr [ecx + 4], ebx
    pop ebx
    test eax, eax
    _emit 0x74
    _emit 0x22  ; je 0x79b50d
    mov ecx, dword ptr [esp + 14h]
    mov dword ptr [eax], edx
    mov dword ptr [eax + 4], esi
    mov dword ptr [eax + 8], edi
    pop edi
    mov dword ptr [eax + 0ch], ecx
    pop esi
    add esp, 10h
    ret 8
    lea edx, [esp + 8]
    push edx
    push eax
    call EXT_79ace0
    pop edi
    pop esi
    add esp, 10h
    ret 8
  }
}

// @ 0x0079b520
__declspec(naked) void FUN_0079b520() {
  __asm {
    sub esp, 10h
    mov eax, dword ptr [ecx + 8]
    mov edx, dword ptr [esp + 14h]
    movss xmm0, dword ptr [esp + 20h]
    push esi
    mov esi, dword ptr [esp + 1ch]
    add ecx, 4
    push edi
    mov edi, dword ptr [esp + 24h]
    mov dword ptr [esp + 8], edx
    mov dword ptr [esp + 0ch], esi
    mov dword ptr [esp + 10h], edi
    movss dword ptr [esp + 14h], xmm0
    cmp eax, dword ptr [ecx + 8]
    _emit 0x73
    _emit 0x23  ; jae 0x79b577
    push ebx
    lea ebx, [eax + 10h]
    mov dword ptr [ecx + 4], ebx
    pop ebx
    test eax, eax
    _emit 0x74
    _emit 0x22  ; je 0x79b582
    mov ecx, dword ptr [esp + 14h]
    mov dword ptr [eax], edx
    mov dword ptr [eax + 4], esi
    mov dword ptr [eax + 8], edi
    pop edi
    mov dword ptr [eax + 0ch], ecx
    pop esi
    add esp, 10h
    ret 10h
    lea edx, [esp + 8]
    push edx
    push eax
    call EXT_79ace0
    pop edi
    pop esi
    add esp, 10h
    ret 10h
  }
}

// @ 0x0079b590
__declspec(naked) void FUN_0079b590() {
  __asm {
    mov eax, dword ptr [ecx + 30h]
    mov ecx, dword ptr [ecx + 18h]
    lea eax, [eax + eax*4]
    lea ecx, [ecx + eax*4]
    mov eax, dword ptr [ecx + 4]
    cmp eax, dword ptr [ecx + 8]
    _emit 0x73
    _emit 0x15  ; jae 0x79b5b9
    lea edx, [eax + 2]
    mov dword ptr [ecx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x16  ; je 0x79b5c4
    mov cx, word ptr [esp + 4]
    mov word ptr [eax], cx
    ret 4
    lea edx, [esp + 4]
    push edx
    push eax
    call EXT_6f5bc0
    ret 4
  }
}

// @ 0x0079b5d0
__declspec(naked) void FUN_0079b5d0() {
  __asm {
    mov eax, dword ptr [ecx + 30h]
    mov edx, dword ptr [ecx + 18h]
    lea eax, [eax + eax*4]
    lea edx, [edx + eax*4]
    mov eax, dword ptr [edx + 4]
    sub eax, dword ptr [edx]
    sar eax, 1
    cmp dword ptr [ecx + 34h], eax
    mov dword ptr [ecx + 38h], eax
    _emit 0x7d
    _emit 0x40  ; jge 0x79b62b
    lea edx, [ecx + 2ch]
    mov ecx, dword ptr [ecx]
    mov eax, dword ptr [ecx + 34h]
    add ecx, 30h
    cmp eax, dword ptr [ecx + 8]
    _emit 0x73
    _emit 0x29  ; jae 0x79b624
    push esi
    lea esi, [eax + 14h]
    mov dword ptr [ecx + 4], esi
    pop esi
    test eax, eax
    _emit 0x74
    _emit 0x24  ; je 0x79b62b
    mov ecx, dword ptr [edx]
    mov dword ptr [eax], ecx
    mov ecx, dword ptr [edx + 4]
    mov dword ptr [eax + 4], ecx
    mov ecx, dword ptr [edx + 8]
    mov dword ptr [eax + 8], ecx
    mov ecx, dword ptr [edx + 0ch]
    mov dword ptr [eax + 0ch], ecx
    mov edx, dword ptr [edx + 10h]
    mov dword ptr [eax + 10h], edx
    ret
    push edx
    push eax
    call EXT_428900
    ret
  }
}

// @ 0x0079b630
__declspec(naked) void FUN_0079b630() {
  __asm {
    push esi
    mov esi, ecx
    lea ecx, [esi + 8]
    call EXT_79b5d0
    mov ecx, dword ptr [esp + 0ch]
    mov edx, dword ptr [esi + 48h]
    lea eax, [ecx + ecx*4]
    lea edx, [edx + eax*4]
    mov eax, dword ptr [edx + 4]
    sub eax, dword ptr [edx]
    sar eax, 1
    cmp dword ptr [esi + 64h], eax
    mov dword ptr [esi + 68h], eax
    _emit 0x7d
    _emit 0x51  ; jge 0x79b6a8
    mov eax, dword ptr [esp + 8]
    mov dword ptr [esi + 60h], ecx
    mov ecx, dword ptr [esp + 18h]
    mov dword ptr [esi + 6ch], ecx
    mov ecx, dword ptr [esi]
    lea edx, [esi + 5ch]
    add ecx, 30h
    mov dword ptr [edx], eax
    mov eax, dword ptr [ecx + 4]
    cmp eax, dword ptr [ecx + 8]
    _emit 0x73
    _emit 0x2a  ; jae 0x79b6a1
    lea esi, [eax + 14h]
    mov dword ptr [ecx + 4], esi
    test eax, eax
    _emit 0x74
    _emit 0x27  ; je 0x79b6a8
    mov ecx, dword ptr [edx]
    mov dword ptr [eax], ecx
    mov ecx, dword ptr [edx + 4]
    mov dword ptr [eax + 4], ecx
    mov ecx, dword ptr [edx + 8]
    mov dword ptr [eax + 8], ecx
    mov ecx, dword ptr [edx + 0ch]
    mov dword ptr [eax + 0ch], ecx
    mov edx, dword ptr [edx + 10h]
    mov dword ptr [eax + 10h], edx
    pop esi
    ret 14h
    push edx
    push eax
    call EXT_428900
    pop esi
    ret 14h
  }
}

// @ 0x0079b6b0
__declspec(naked) void FUN_0079b6b0() {
  __asm {
    push -1
    push 120c068h
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
    sub esp, 1ch
    push ebx
    push ebp
    xor ebp, ebp
    push esi
    push edi
    mov dword ptr [esp + 18h], ebp
    mov dword ptr [esp + 1ch], ebp
    mov dword ptr [esp + 20h], ebp
    mov esi, dword ptr [esp + 40h]
    mov eax, dword ptr [esi]
    mov ecx, dword ptr [eax + 34h]
    sub ecx, dword ptr [eax + 30h]
    add eax, 30h
    mov eax, 66666667h
    imul ecx
    sar edx, 3
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    push eax
    lea ecx, [esp + 1ch]
    mov dword ptr [esp + 38h], ebp
    call EXT_7658f0
    mov edx, dword ptr [esi]
    push -1
    push ebp
    push ebp
    push ebp
    push ebp
    push ebp
    lea ecx, [esp + 30h]
    push ecx
    push ebp
    push edx
    call EXT_72b630
    mov edi, dword ptr [esp + 40h]
    mov ecx, dword ptr [esp + 3ch]
    sub edi, ecx
    sar edi, 2
    add esp, 24h
    xor ebx, ebx
    cmp edi, ebp
    _emit 0x7e
    _emit 0x54  ; jle 0x79b787
    mov esi, dword ptr [esp + 3ch]
    _emit 0xeb
    _emit 0x07  ; jmp 0x79b740
    _emit 0x8d
    _emit 0xa4
    _emit 0x24
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; data
    mov eax, dword ptr [esp + 40h]
    mov eax, dword ptr [eax + 4]
    mov edx, dword ptr [ecx + ebx*4]
    mov dword ptr [esp + 14h], eax
    mov eax, dword ptr [esi + 4]
    mov dword ptr [esp + 10h], edx
    cmp eax, dword ptr [esi + 8]
    _emit 0x73
    _emit 0x17  ; jae 0x79b771
    lea ebp, [eax + 8]
    mov dword ptr [esi + 4], ebp
    xor ebp, ebp
    cmp eax, ebp
    _emit 0x74
    _emit 0x1c  ; je 0x79b782
    mov ecx, dword ptr [esp + 14h]
    mov dword ptr [eax], edx
    mov dword ptr [eax + 4], ecx
    _emit 0xeb
    _emit 0x0d  ; jmp 0x79b77e
    lea edx, [esp + 10h]
    push edx
    push eax
    mov ecx, esi
    call EXT_6ec390
    mov ecx, dword ptr [esp + 18h]
    inc ebx
    cmp ebx, edi
    _emit 0x7c
    _emit 0xb9  ; jl 0x79b740
    cmp ecx, ebp
    _emit 0x74
    _emit 0x0e  ; je 0x79b799
    cmp dword ptr [ecx - 4], ebp
    _emit 0x74
    _emit 0x09  ; je 0x79b799
    push ecx
    call EXT_f47380
    add esp, 4
    mov ecx, dword ptr [esp + 2ch]
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
    add esp, 28h
    ret
  }
}

// @ 0x0079b7b0
__declspec(naked) void FUN_0079b7b0() {
  __asm {
    sub esp, 20h
    push esi
    push edi
    mov edi, dword ptr [esp + 2ch]
    push 0eh
    push 3
    push 0
    push 1
    push edi
    mov dword ptr [esp + 1ch], ecx
    call EXT_71ddc0
    mov edx, dword ptr [edi + 8]
    mov ecx, eax
    shl ecx, 5
    lea ecx, [ecx + edx + 10h]
    mov edx, dword ptr [esp + 44h]
    mov esi, dword ptr [edx + 4]
    imul esi, esi, 8ch
    add esi, dword ptr [edi + 1ch]
    mov dword ptr [esp + 30h], ecx
    mov ecx, dword ptr [edx + 8]
    add esp, 14h
    cmp ecx, dword ptr [edx + 0ch]
    mov dword ptr [esp + 18h], eax
    mov dword ptr [esp + 2ch], ecx
    _emit 0x0f
    _emit 0x8d
    _emit 0x8a
    _emit 0x07
    _emit 0x00
    _emit 0x00  ; jge 0x79bf8c
    push ebx
    push ebp
    mov ebp, dword ptr [esp + 40h]
    _emit 0xeb
    _emit 0x0e  ; jmp 0x79b818
    _emit 0x8d
    _emit 0x9b
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; data
    mov ecx, dword ptr [esp + 34h]
    mov eax, dword ptr [esp + 20h]
    mov edi, dword ptr [esi + 4]
    lea edx, [ecx + 1]
    mov dword ptr [esp + 18h], edx
    lea edx, [ecx + 2]
    mov dword ptr [esp + 14h], edx
    mov edx, dword ptr [esi + 44h]
    cmp edx, dword ptr [esi + 48h]
    _emit 0x0f
    _emit 0x84
    _emit 0xa9
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x79b8de
    mov edx, dword ptr [esi + 14h]
    movsx eax, word ptr [edx + eax*4 + 2]
    mov edx, dword ptr [esi + 44h]
    movzx ebx, word ptr [esi + 8]
    mov ebx, dword ptr [ebx*4 + 140f544h]
    mov dword ptr [esp + 40h], ebx
    shl eax, 4
    add eax, edx
    movzx edx, word ptr [esi + 0ah]
    mov ebx, edx
    imul ebx, ecx
    mov ecx, dword ptr [ebx + edi]
    movzx edi, word ptr [eax + 0ah]
    and ecx, dword ptr [esp + 40h]
    movzx ebx, word ptr [eax + 8]
    imul ecx, edi
    mov edi, dword ptr [eax + 4]
    mov ecx, dword ptr [ecx + edi]
    mov edi, edx
    imul edi, dword ptr [esp + 18h]
    and ecx, dword ptr [ebx*4 + 140f544h]
    movzx ebx, word ptr [eax + 8]
    mov dword ptr [esp + 1ch], edx
    mov edx, dword ptr [esi + 4]
    mov edx, dword ptr [edi + edx]
    movzx edi, word ptr [eax + 0ah]
    and edx, dword ptr [esp + 40h]
    imul edx, edi
    mov edi, dword ptr [eax + 4]
    mov edx, dword ptr [edx + edi]
    mov edi, dword ptr [esp + 1ch]
    imul edi, dword ptr [esp + 14h]
    and edx, dword ptr [ebx*4 + 140f544h]
    mov ebx, dword ptr [esi + 4]
    mov edi, dword ptr [edi + ebx]
    movzx ebx, word ptr [eax + 0ah]
    and edi, dword ptr [esp + 40h]
    imul edi, ebx
    mov ebx, dword ptr [eax + 4]
    movzx eax, word ptr [eax + 8]
    mov dword ptr [esp + 40h], eax
    mov eax, dword ptr [edi + ebx]
    mov edi, dword ptr [esp + 40h]
    and eax, dword ptr [edi*4 + 140f544h]
    _emit 0xeb
    _emit 0x37  ; jmp 0x79b915
    movzx eax, word ptr [esi + 0ah]
    movzx edx, word ptr [esi + 8]
    mov edx, dword ptr [edx*4 + 140f544h]
    mov ebx, eax
    imul ebx, ecx
    mov ecx, dword ptr [ebx + edi]
    mov dword ptr [esp + 40h], edx
    and ecx, edx
    mov edx, eax
    imul eax, dword ptr [esp + 14h]
    imul edx, dword ptr [esp + 18h]
    mov edx, dword ptr [edx + edi]
    mov eax, dword ptr [eax + edi]
    and edx, dword ptr [esp + 40h]
    and eax, dword ptr [esp + 40h]
    mov edi, dword ptr [esp + 24h]
    movzx ebx, word ptr [edi + 0ah]
    mov edi, dword ptr [edi + 4]
    mov dword ptr [esp + 40h], edi
    mov edi, ebx
    imul edi, ecx
    add edi, dword ptr [esp + 40h]
    mov dword ptr [esp + 1ch], ebx
    imul ebx, edx
    mov ecx, dword ptr [esp + 1ch]
    mov edx, dword ptr [esp + 40h]
    imul ecx, eax
    mov eax, dword ptr [esp + 10h]
    movss xmm0, dword ptr [eax + 14h]
    mulss xmm0, dword ptr [edi + 8]
    movss xmm1, dword ptr [eax + 10h]
    mulss xmm1, dword ptr [edi + 4]
    add eax, 0ch
    addss xmm0, xmm1
    movss xmm1, dword ptr [eax]
    mulss xmm1, dword ptr [edi]
    add ecx, edx
    add ebx, edx
    addss xmm0, xmm1
    comiss xmm0, dword ptr [eax + 0ch]
    mov dword ptr [esp + 40h], ecx
    _emit 0x76
    _emit 0x07  ; jbe 0x79b97f
    mov ecx, 1
    _emit 0xeb
    _emit 0x02  ; jmp 0x79b981
    xor ecx, ecx
    mov eax, dword ptr [esp + 10h]
    mov eax, dword ptr [eax + 1ch]
    xor edx, edx
    cmp ecx, eax
    mov ecx, dword ptr [esp + 10h]
    movss xmm0, dword ptr [ecx + 14h]
    mulss xmm0, dword ptr [ebx + 8]
    movss xmm1, dword ptr [ecx + 10h]
    mulss xmm1, dword ptr [ebx + 4]
    sete dl
    add ecx, 0ch
    addss xmm0, xmm1
    movss xmm1, dword ptr [ecx]
    mulss xmm1, dword ptr [ebx]
    addss xmm0, xmm1
    comiss xmm0, dword ptr [ecx + 0ch]
    mov dword ptr [esp + 14h], edx
    _emit 0x76
    _emit 0x07  ; jbe 0x79b9cb
    mov ecx, 1
    _emit 0xeb
    _emit 0x02  ; jmp 0x79b9cd
    xor ecx, ecx
    xor edx, edx
    cmp ecx, eax
    mov ecx, dword ptr [esp + 10h]
    movss xmm0, dword ptr [ecx + 14h]
    movss xmm1, dword ptr [ecx + 10h]
    sete dl
    add ecx, 0ch
    mov dword ptr [esp + 18h], edx
    mov edx, dword ptr [esp + 40h]
    mulss xmm1, dword ptr [edx + 4]
    mulss xmm0, dword ptr [edx + 8]
    addss xmm0, xmm1
    movss xmm1, dword ptr [edx]
    mulss xmm1, dword ptr [ecx]
    addss xmm0, xmm1
    comiss xmm0, dword ptr [ecx + 0ch]
    _emit 0x76
    _emit 0x07  ; jbe 0x79ba14
    mov ecx, 1
    _emit 0xeb
    _emit 0x02  ; jmp 0x79ba16
    xor ecx, ecx
    xor edx, edx
    cmp ecx, eax
    mov ecx, dword ptr [esp + 18h]
    sete dl
    mov eax, edx
    add ecx, eax
    add ecx, dword ptr [esp + 14h]
    mov dword ptr [esp + 1ch], eax
    mov eax, 55555556h
    imul ecx
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    lea edx, [eax + eax*2]
    mov eax, ecx
    sub eax, edx
    mov dword ptr [esp + 2ch], ecx
    _emit 0x75
    _emit 0x30  ; jne 0x79ba78
    cmp dword ptr [esp + 14h], eax
    _emit 0x0f
    _emit 0x84
    _emit 0x20
    _emit 0x05
    _emit 0x00
    _emit 0x00  ; je 0x79bf72
    movzx ecx, word ptr [esi + 0ah]
    mov ebx, dword ptr [esp + 34h]
    mov edx, dword ptr [esi + 4]
    imul ecx, ebx
    movzx eax, word ptr [esi + 8]
    mov cx, word ptr [ecx + edx]
    and cx, word ptr [eax*4 + 140f544h]
    movzx ecx, cx
    _emit 0xe9
    _emit 0x3e
    _emit 0x04
    _emit 0x00
    _emit 0x00  ; jmp 0x79beb6
    mov eax, dword ptr [esp + 10h]
    mov edx, dword ptr [eax + 8]
    sub edx, 0
    _emit 0x0f
    _emit 0x84
    _emit 0x0d
    _emit 0x04
    _emit 0x00
    _emit 0x00  ; je 0x79be95
    sub edx, 2
    _emit 0x0f
    _emit 0x84
    _emit 0xd8
    _emit 0x03
    _emit 0x00
    _emit 0x00  ; je 0x79be69
    sub edx, 1
    _emit 0x0f
    _emit 0x85
    _emit 0xd8
    _emit 0x04
    _emit 0x00
    _emit 0x00  ; jne 0x79bf72
    mov edx, dword ptr [ebp + 8]
    sub edx, dword ptr [ebp + 4]
    sar edx, 4
    cmp dword ptr [esp + 14h], 0
    movzx ecx, dx
    mov dword ptr [esp + 28h], ecx
    _emit 0x0f
    _emit 0x84
    _emit 0x2a
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x79bbdf
    mov edx, dword ptr [esp + 34h]
    mov eax, dword ptr [esp + 38h]
    mov ecx, dword ptr [eax + 4]
    push edx
    push ecx
    mov ecx, ebp
    call EXT_79b4b0
    cmp dword ptr [esp + 18h], 0
    _emit 0x74
    _emit 0x75  ; je 0x79bb45
    mov eax, dword ptr [esp + 34h]
    mov edx, dword ptr [esp + 38h]
    inc eax
    push eax
    mov eax, dword ptr [edx + 4]
    push eax
    mov ecx, ebp
    call EXT_79b4b0
    mov ecx, dword ptr [esp + 40h]
    push ecx
    mov ecx, dword ptr [esp + 14h]
    add ecx, 0ch
    push ebx
    mov dword ptr [esp + 20h], ecx
    call EXT_7998a0
    mov eax, dword ptr [esp + 34h]
    mov edx, dword ptr [esp + 38h]
    push ecx
    lea ebx, [eax + 2]
    fstp dword ptr [esp]
    push ebx
    inc eax
    push eax
    mov eax, dword ptr [edx + 4]
    push eax
    mov ecx, ebp
    call EXT_79b520
    mov ecx, dword ptr [esp + 40h]
    push ecx
    mov ecx, dword ptr [esp + 1ch]
    push edi
    call EXT_7998a0
    mov edx, dword ptr [esp + 34h]
    mov eax, dword ptr [esp + 38h]
    push ecx
    mov ecx, dword ptr [eax + 4]
    fstp dword ptr [esp]
    push ebx
    push edx
    push ecx
    mov ecx, ebp
    call EXT_79b520
    _emit 0xe9
    _emit 0xbf
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jmp 0x79bd04
    mov ecx, dword ptr [esp + 10h]
    push ebx
    push edi
    add ecx, 0ch
    call EXT_7998a0
    mov eax, dword ptr [esp + 34h]
    mov edx, dword ptr [esp + 34h]
    push ecx
    fstp dword ptr [esp]
    inc eax
    push eax
    mov eax, dword ptr [esp + 40h]
    mov ecx, dword ptr [eax + 4]
    push edx
    push ecx
    mov ecx, ebp
    call EXT_79b520
    mov ecx, dword ptr [esp + 10h]
    mov edx, dword ptr [esp + 40h]
    add ecx, 0ch
    cmp dword ptr [esp + 1ch], 0
    _emit 0x74
    _emit 0x30  ; je 0x79bbb3
    push ebx
    push edx
    call EXT_7998a0
    mov eax, dword ptr [esp + 34h]
    mov ebx, dword ptr [esp + 38h]
    push ecx
    lea ecx, [eax + 1]
    fstp dword ptr [esp]
    push ecx
    lea edi, [eax + 2]
    mov eax, dword ptr [ebx + 4]
    push edi
    push eax
    mov ecx, ebp
    call EXT_79b520
    mov ecx, dword ptr [ebx + 4]
    push edi
    push ecx
    _emit 0xe9
    _emit 0x4a
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jmp 0x79bcfd
    push edx
    push edi
    call EXT_7998a0
    mov eax, dword ptr [esp + 34h]
    push ecx
    mov ecx, dword ptr [esp + 3ch]
    fstp dword ptr [esp]
    mov edx, dword ptr [ecx + 4]
    add eax, 2
    push eax
    mov eax, dword ptr [esp + 3ch]
    push eax
    push edx
    mov ecx, ebp
    call EXT_79b520
    _emit 0xe9
    _emit 0x25
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jmp 0x79bd04
    cmp dword ptr [esp + 18h], 0
    push edi
    _emit 0x0f
    _emit 0x84
    _emit 0xb7
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x79bca2
    push ebx
    lea ecx, [eax + 0ch]
    call EXT_7998a0
    mov eax, dword ptr [esp + 34h]
    push ecx
    fstp dword ptr [esp]
    push eax
    inc eax
    push eax
    mov eax, dword ptr [esp + 44h]
    mov ecx, dword ptr [eax + 4]
    push ecx
    mov ecx, ebp
    call EXT_79b520
    mov eax, dword ptr [esp + 34h]
    mov edx, dword ptr [esp + 38h]
    inc eax
    push eax
    mov eax, dword ptr [edx + 4]
    push eax
    mov ecx, ebp
    call EXT_79b4b0
    cmp dword ptr [esp + 1ch], 0
    _emit 0x74
    _emit 0x47  ; je 0x79bc71
    mov ebx, dword ptr [esp + 34h]
    mov ecx, dword ptr [esp + 38h]
    mov edx, dword ptr [ecx + 4]
    add ebx, 2
    push ebx
    push edx
    mov ecx, ebp
    call EXT_79b4b0
    mov eax, dword ptr [esp + 40h]
    mov ecx, dword ptr [esp + 10h]
    push edi
    push eax
    add ecx, 0ch
    call EXT_7998a0
    mov edx, dword ptr [esp + 38h]
    mov eax, dword ptr [edx + 4]
    push ecx
    mov ecx, dword ptr [esp + 38h]
    fstp dword ptr [esp]
    push ecx
    push ebx
    push eax
    mov ecx, ebp
    call EXT_79b520
    _emit 0xe9
    _emit 0x93
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; jmp 0x79bd04
    mov ecx, dword ptr [esp + 40h]
    push ecx
    mov ecx, dword ptr [esp + 14h]
    push ebx
    add ecx, 0ch
    call EXT_7998a0
    mov eax, dword ptr [esp + 34h]
    mov edx, dword ptr [esp + 38h]
    push ecx
    lea ecx, [eax + 2]
    fstp dword ptr [esp]
    push ecx
    inc eax
    push eax
    mov eax, dword ptr [edx + 4]
    push eax
    mov ecx, ebp
    call EXT_79b520
    _emit 0xeb
    _emit 0x62  ; jmp 0x79bd04
    mov ecx, dword ptr [esp + 44h]
    push ecx
    lea ecx, [eax + 0ch]
    mov dword ptr [esp + 20h], ecx
    call EXT_7998a0
    mov edi, dword ptr [esp + 34h]
    mov edx, dword ptr [esp + 38h]
    mov eax, dword ptr [edx + 4]
    push ecx
    fstp dword ptr [esp]
    push edi
    add edi, 2
    push edi
    push eax
    mov ecx, ebp
    call EXT_79b520
    mov ecx, dword ptr [esp + 40h]
    push ebx
    push ecx
    mov ecx, dword ptr [esp + 20h]
    call EXT_7998a0
    mov eax, dword ptr [esp + 34h]
    mov ebx, dword ptr [esp + 38h]
    mov edx, dword ptr [ebx + 4]
    push ecx
    fstp dword ptr [esp]
    inc eax
    push eax
    push edi
    push edx
    mov ecx, ebp
    call EXT_79b520
    mov eax, dword ptr [ebx + 4]
    push edi
    push eax
    mov ecx, ebp
    call EXT_79b4b0
    mov edi, dword ptr [esp + 28h]
    mov eax, dword ptr [ebp + 30h]
    movzx ecx, di
    lea edx, [eax + eax*4]
    mov eax, dword ptr [ebp + 18h]
    mov dword ptr [esp + 40h], ecx
    lea ecx, [eax + edx*4]
    mov eax, dword ptr [ecx + 4]
    cmp eax, dword ptr [ecx + 8]
    _emit 0x73
    _emit 0x0f  ; jae 0x79bd32
    lea edx, [eax + 2]
    mov dword ptr [ecx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x10  ; je 0x79bd3d
    mov word ptr [eax], di
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79bd3d
    lea edx, [esp + 40h]
    push edx
    push eax
    call EXT_6f5bc0
    lea eax, [edi + 1]
    movzx edx, ax
    mov eax, dword ptr [ebp + 30h]
    lea ecx, [eax + eax*4]
    mov eax, dword ptr [ebp + 18h]
    lea ecx, [eax + ecx*4]
    mov eax, dword ptr [ecx + 4]
    mov dword ptr [esp + 40h], edx
    cmp eax, dword ptr [ecx + 8]
    _emit 0x73
    _emit 0x0f  ; jae 0x79bd6a
    lea ebx, [eax + 2]
    mov dword ptr [ecx + 4], ebx
    test eax, eax
    _emit 0x74
    _emit 0x10  ; je 0x79bd75
    mov word ptr [eax], dx
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79bd75
    lea edx, [esp + 40h]
    push edx
    push eax
    call EXT_6f5bc0
    mov edx, dword ptr [ebp + 18h]
    lea ebx, [edi + 2]
    movzx eax, bx
    mov dword ptr [esp + 40h], eax
    mov eax, dword ptr [ebp + 30h]
    lea ecx, [eax + eax*4]
    mov eax, dword ptr [edx + ecx*4 + 4]
    cmp eax, dword ptr [edx + ecx*4 + 8]
    lea ecx, [edx + ecx*4]
    _emit 0x73
    _emit 0x14  ; jae 0x79bda9
    lea edx, [eax + 2]
    mov dword ptr [ecx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x15  ; je 0x79bdb4
    mov cx, word ptr [esp + 40h]
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79bdb4
    lea edx, [esp + 40h]
    push edx
    push eax
    call EXT_6f5bc0
    cmp dword ptr [esp + 2ch], 1
    _emit 0x0f
    _emit 0x8e
    _emit 0xb3
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jle 0x79bf72
    mov edx, dword ptr [ebp + 18h]
    movzx eax, di
    mov dword ptr [esp + 40h], eax
    mov eax, dword ptr [ebp + 30h]
    lea ecx, [eax + eax*4]
    mov eax, dword ptr [edx + ecx*4 + 4]
    cmp eax, dword ptr [edx + ecx*4 + 8]
    lea ecx, [edx + ecx*4]
    _emit 0x73
    _emit 0x0f  ; jae 0x79bdeb
    lea edx, [eax + 2]
    mov dword ptr [ecx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x10  ; je 0x79bdf6
    mov word ptr [eax], di
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79bdf6
    lea edx, [esp + 40h]
    push edx
    push eax
    call EXT_6f5bc0
    mov eax, dword ptr [ebp + 30h]
    mov ecx, dword ptr [ebp + 18h]
    lea eax, [eax + eax*4]
    lea ecx, [ecx + eax*4]
    mov eax, dword ptr [ecx + 4]
    movzx edx, bx
    mov dword ptr [esp + 40h], edx
    cmp eax, dword ptr [ecx + 8]
    _emit 0x73
    _emit 0x0f  ; jae 0x79be20
    lea ebx, [eax + 2]
    mov dword ptr [ecx + 4], ebx
    test eax, eax
    _emit 0x74
    _emit 0x10  ; je 0x79be2b
    mov word ptr [eax], dx
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79be2b
    lea edx, [esp + 40h]
    push edx
    push eax
    call EXT_6f5bc0
    mov eax, dword ptr [ebp + 30h]
    mov ecx, dword ptr [ebp + 18h]
    lea eax, [eax + eax*4]
    add edi, 3
    lea ecx, [ecx + eax*4]
    mov eax, dword ptr [ecx + 4]
    movzx edx, di
    mov dword ptr [esp + 40h], edx
    cmp eax, dword ptr [ecx + 8]
    _emit 0x73
    _emit 0x16  ; jae 0x79be5f
    lea edi, [eax + 2]
    mov dword ptr [ecx + 4], edi
    test eax, eax
    _emit 0x0f
    _emit 0x84
    _emit 0x1b
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x79bf72
    mov word ptr [eax], dx
    _emit 0xe9
    _emit 0x13
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jmp 0x79bf72
    lea edx, [esp + 40h]
    push edx
    _emit 0xe9
    _emit 0x03
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jmp 0x79bf6c
    cmp ecx, 1
    _emit 0x0f
    _emit 0x8e
    _emit 0x00
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jle 0x79bf72
    movzx eax, word ptr [esi + 0ah]
    mov ebx, dword ptr [esp + 34h]
    mov ecx, dword ptr [esi + 4]
    imul eax, ebx
    movzx edx, word ptr [esi + 8]
    mov ax, word ptr [eax + ecx]
    and ax, word ptr [edx*4 + 140f544h]
    movzx ecx, ax
    _emit 0xeb
    _emit 0x21  ; jmp 0x79beb6
    movzx edx, word ptr [esi + 0ah]
    mov ebx, dword ptr [esp + 34h]
    movzx ecx, word ptr [esi + 8]
    imul edx, ebx
    mov eax, dword ptr [esi + 4]
    mov dx, word ptr [edx + eax]
    and dx, word ptr [ecx*4 + 140f544h]
    movzx ecx, dx
    mov edi, dword ptr [esp + 3ch]
    mov eax, dword ptr [edi + 4]
    mov dword ptr [esp + 40h], ecx
    cmp eax, dword ptr [edi + 8]
    _emit 0x73
    _emit 0x0f  ; jae 0x79bed5
    lea edx, [eax + 2]
    mov dword ptr [edi + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x12  ; je 0x79bee2
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0d  ; jmp 0x79bee2
    lea ecx, [esp + 40h]
    push ecx
    push eax
    mov ecx, edi
    call EXT_6f5bc0
    movzx edx, word ptr [esi + 0ah]
    movzx ecx, word ptr [esi + 8]
    lea eax, [ebx + 1]
    imul edx, eax
    mov eax, dword ptr [esi + 4]
    mov dx, word ptr [edx + eax]
    and dx, word ptr [ecx*4 + 140f544h]
    mov eax, dword ptr [edi + 4]
    movzx ecx, dx
    mov dword ptr [esp + 40h], ecx
    cmp eax, dword ptr [edi + 8]
    _emit 0x73
    _emit 0x0f  ; jae 0x79bf1d
    lea edx, [eax + 2]
    mov dword ptr [edi + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x12  ; je 0x79bf2a
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0d  ; jmp 0x79bf2a
    lea ecx, [esp + 40h]
    push ecx
    push eax
    mov ecx, edi
    call EXT_6f5bc0
    movzx edx, word ptr [esi + 0ah]
    movzx ecx, word ptr [esi + 8]
    lea eax, [ebx + 2]
    imul edx, eax
    mov eax, dword ptr [esi + 4]
    mov dx, word ptr [edx + eax]
    and dx, word ptr [ecx*4 + 140f544h]
    mov eax, dword ptr [edi + 4]
    movzx ecx, dx
    mov dword ptr [esp + 40h], ecx
    cmp eax, dword ptr [edi + 8]
    _emit 0x73
    _emit 0x0f  ; jae 0x79bf65
    lea edx, [eax + 2]
    mov dword ptr [edi + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x12  ; je 0x79bf72
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0d  ; jmp 0x79bf72
    lea ecx, [esp + 40h]
    push ecx
    mov ecx, edi
    push eax
    call EXT_6f5bc0
    mov eax, dword ptr [esp + 34h]
    mov edx, dword ptr [esp + 38h]
    add eax, 3
    cmp eax, dword ptr [edx + 0ch]
    mov dword ptr [esp + 34h], eax
    _emit 0x0f
    _emit 0x8c
    _emit 0x86
    _emit 0xf8
    _emit 0xff
    _emit 0xff  ; jl 0x79b810
    pop ebp
    pop ebx
    pop edi
    pop esi
    add esp, 20h
    ret 10h
  }
}


