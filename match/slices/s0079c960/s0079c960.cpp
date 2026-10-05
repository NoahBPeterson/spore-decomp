// slice s0079c960
// Per-instruction reconstruction (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
// Control flow is decoded recursively; call targets are symbolic so COFF
// relocation bytes are masked by the verifier. Unreachable bytes are data.

extern "C" void EXT_6f5bc0();
extern "C" void EXT_71ddc0();
extern "C" void EXT_799b50();
extern "C" void EXT_79b4b0();
extern "C" void EXT_79b520();

// @ 0x0079c960
__declspec(naked) void FUN_0079c960() {
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
    _emit 0xcb
    _emit 0x07
    _emit 0x00
    _emit 0x00  ; jge 0x79d17d
    push ebx
    push ebp
    mov ebp, dword ptr [esp + 40h]
    _emit 0xeb
    _emit 0x0e  ; jmp 0x79c9c8
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
    _emit 0x00  ; je 0x79ca8e
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
    _emit 0x37  ; jmp 0x79cac5
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
    movss xmm2, dword ptr [edi + 8]
    imul ecx, eax
    mov eax, dword ptr [esp + 10h]
    subss xmm2, dword ptr [eax + 14h]
    movss xmm1, dword ptr [edi + 4]
    subss xmm1, dword ptr [eax + 10h]
    mov edx, dword ptr [esp + 40h]
    movss xmm0, dword ptr [edi]
    subss xmm0, dword ptr [eax + 0ch]
    add eax, 0ch
    movaps xmm3, xmm2
    mulss xmm3, xmm2
    movaps xmm2, xmm1
    mulss xmm2, xmm1
    movaps xmm1, xmm0
    add ecx, edx
    addss xmm3, xmm2
    mulss xmm1, xmm0
    add ebx, edx
    addss xmm3, xmm1
    comiss xmm3, dword ptr [eax + 0ch]
    mov dword ptr [esp + 40h], ecx
    _emit 0x76
    _emit 0x07  ; jbe 0x79cb45
    mov ecx, 1
    _emit 0xeb
    _emit 0x02  ; jmp 0x79cb47
    xor ecx, ecx
    mov eax, dword ptr [esp + 10h]
    mov eax, dword ptr [eax + 1ch]
    movss xmm2, dword ptr [ebx + 8]
    movss xmm1, dword ptr [ebx + 4]
    movss xmm0, dword ptr [ebx]
    xor edx, edx
    cmp ecx, eax
    mov ecx, dword ptr [esp + 10h]
    subss xmm2, dword ptr [ecx + 14h]
    subss xmm1, dword ptr [ecx + 10h]
    subss xmm0, dword ptr [ecx + 0ch]
    sete dl
    add ecx, 0ch
    movaps xmm3, xmm2
    mulss xmm3, xmm2
    movaps xmm2, xmm1
    mulss xmm2, xmm1
    movaps xmm1, xmm0
    addss xmm3, xmm2
    mulss xmm1, xmm0
    addss xmm3, xmm1
    comiss xmm3, dword ptr [ecx + 0ch]
    mov dword ptr [esp + 14h], edx
    _emit 0x76
    _emit 0x07  ; jbe 0x79cba7
    mov ecx, 1
    _emit 0xeb
    _emit 0x02  ; jmp 0x79cba9
    xor ecx, ecx
    xor edx, edx
    cmp ecx, eax
    mov ecx, dword ptr [esp + 10h]
    sete dl
    add ecx, 0ch
    mov dword ptr [esp + 18h], edx
    mov edx, dword ptr [esp + 40h]
    movss xmm2, dword ptr [edx + 8]
    subss xmm2, dword ptr [ecx + 8]
    movss xmm1, dword ptr [edx + 4]
    subss xmm1, dword ptr [ecx + 4]
    movss xmm0, dword ptr [edx]
    subss xmm0, dword ptr [ecx]
    movaps xmm3, xmm2
    mulss xmm3, xmm2
    movaps xmm2, xmm1
    mulss xmm2, xmm1
    movaps xmm1, xmm0
    addss xmm3, xmm2
    mulss xmm1, xmm0
    addss xmm3, xmm1
    comiss xmm3, dword ptr [ecx + 0ch]
    _emit 0x76
    _emit 0x07  ; jbe 0x79cc05
    mov ecx, 1
    _emit 0xeb
    _emit 0x02  ; jmp 0x79cc07
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
    _emit 0x30  ; jne 0x79cc69
    cmp dword ptr [esp + 14h], eax
    _emit 0x0f
    _emit 0x84
    _emit 0x20
    _emit 0x05
    _emit 0x00
    _emit 0x00  ; je 0x79d163
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
    _emit 0x00  ; jmp 0x79d0a7
    mov eax, dword ptr [esp + 10h]
    mov edx, dword ptr [eax + 8]
    sub edx, 0
    _emit 0x0f
    _emit 0x84
    _emit 0x0d
    _emit 0x04
    _emit 0x00
    _emit 0x00  ; je 0x79d086
    sub edx, 2
    _emit 0x0f
    _emit 0x84
    _emit 0xd8
    _emit 0x03
    _emit 0x00
    _emit 0x00  ; je 0x79d05a
    sub edx, 1
    _emit 0x0f
    _emit 0x85
    _emit 0xd8
    _emit 0x04
    _emit 0x00
    _emit 0x00  ; jne 0x79d163
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
    _emit 0x00  ; je 0x79cdd0
    mov edx, dword ptr [esp + 34h]
    mov eax, dword ptr [esp + 38h]
    mov ecx, dword ptr [eax + 4]
    push edx
    push ecx
    mov ecx, ebp
    call EXT_79b4b0
    cmp dword ptr [esp + 18h], 0
    _emit 0x74
    _emit 0x75  ; je 0x79cd36
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
    call EXT_799b50
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
    call EXT_799b50
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
    _emit 0x00  ; jmp 0x79cef5
    mov ecx, dword ptr [esp + 10h]
    push ebx
    push edi
    add ecx, 0ch
    call EXT_799b50
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
    _emit 0x30  ; je 0x79cda4
    push ebx
    push edx
    call EXT_799b50
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
    _emit 0x00  ; jmp 0x79ceee
    push edx
    push edi
    call EXT_799b50
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
    _emit 0x00  ; jmp 0x79cef5
    cmp dword ptr [esp + 18h], 0
    push edi
    _emit 0x0f
    _emit 0x84
    _emit 0xb7
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x79ce93
    push ebx
    lea ecx, [eax + 0ch]
    call EXT_799b50
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
    _emit 0x47  ; je 0x79ce62
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
    call EXT_799b50
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
    _emit 0x00  ; jmp 0x79cef5
    mov ecx, dword ptr [esp + 40h]
    push ecx
    mov ecx, dword ptr [esp + 14h]
    push ebx
    add ecx, 0ch
    call EXT_799b50
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
    _emit 0x62  ; jmp 0x79cef5
    mov ecx, dword ptr [esp + 44h]
    push ecx
    lea ecx, [eax + 0ch]
    mov dword ptr [esp + 20h], ecx
    call EXT_799b50
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
    call EXT_799b50
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
    _emit 0x0f  ; jae 0x79cf23
    lea edx, [eax + 2]
    mov dword ptr [ecx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x10  ; je 0x79cf2e
    mov word ptr [eax], di
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79cf2e
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
    _emit 0x0f  ; jae 0x79cf5b
    lea ebx, [eax + 2]
    mov dword ptr [ecx + 4], ebx
    test eax, eax
    _emit 0x74
    _emit 0x10  ; je 0x79cf66
    mov word ptr [eax], dx
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79cf66
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
    _emit 0x14  ; jae 0x79cf9a
    lea edx, [eax + 2]
    mov dword ptr [ecx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x15  ; je 0x79cfa5
    mov cx, word ptr [esp + 40h]
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79cfa5
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
    _emit 0x00  ; jle 0x79d163
    mov edx, dword ptr [ebp + 18h]
    movzx eax, di
    mov dword ptr [esp + 40h], eax
    mov eax, dword ptr [ebp + 30h]
    lea ecx, [eax + eax*4]
    mov eax, dword ptr [edx + ecx*4 + 4]
    cmp eax, dword ptr [edx + ecx*4 + 8]
    lea ecx, [edx + ecx*4]
    _emit 0x73
    _emit 0x0f  ; jae 0x79cfdc
    lea edx, [eax + 2]
    mov dword ptr [ecx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x10  ; je 0x79cfe7
    mov word ptr [eax], di
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79cfe7
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
    _emit 0x0f  ; jae 0x79d011
    lea ebx, [eax + 2]
    mov dword ptr [ecx + 4], ebx
    test eax, eax
    _emit 0x74
    _emit 0x10  ; je 0x79d01c
    mov word ptr [eax], dx
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79d01c
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
    _emit 0x16  ; jae 0x79d050
    lea edi, [eax + 2]
    mov dword ptr [ecx + 4], edi
    test eax, eax
    _emit 0x0f
    _emit 0x84
    _emit 0x1b
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x79d163
    mov word ptr [eax], dx
    _emit 0xe9
    _emit 0x13
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jmp 0x79d163
    lea edx, [esp + 40h]
    push edx
    _emit 0xe9
    _emit 0x03
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jmp 0x79d15d
    cmp ecx, 1
    _emit 0x0f
    _emit 0x8e
    _emit 0x00
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jle 0x79d163
    movzx eax, word ptr [esi + 0ah]
    mov ebx, dword ptr [esp + 34h]
    mov ecx, dword ptr [esi + 4]
    imul eax, ebx
    movzx edx, word ptr [esi + 8]
    mov ax, word ptr [eax + ecx]
    and ax, word ptr [edx*4 + 140f544h]
    movzx ecx, ax
    _emit 0xeb
    _emit 0x21  ; jmp 0x79d0a7
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
    _emit 0x0f  ; jae 0x79d0c6
    lea edx, [eax + 2]
    mov dword ptr [edi + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x12  ; je 0x79d0d3
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0d  ; jmp 0x79d0d3
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
    _emit 0x0f  ; jae 0x79d10e
    lea edx, [eax + 2]
    mov dword ptr [edi + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x12  ; je 0x79d11b
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0d  ; jmp 0x79d11b
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
    _emit 0x0f  ; jae 0x79d156
    lea edx, [eax + 2]
    mov dword ptr [edi + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x12  ; je 0x79d163
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0d  ; jmp 0x79d163
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
    _emit 0x45
    _emit 0xf8
    _emit 0xff
    _emit 0xff  ; jl 0x79c9c0
    pop ebp
    pop ebx
    pop edi
    pop esi
    add esp, 20h
    ret 10h
  }
}


