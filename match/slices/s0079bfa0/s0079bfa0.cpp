// slice s0079bfa0
// Per-instruction reconstruction (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
// Control flow is decoded recursively; call targets are symbolic so COFF
// relocation bytes are masked by the verifier. Unreachable bytes are data.

extern "C" void EXT_6f5bc0();
extern "C" void EXT_71ddc0();
extern "C" void EXT_7999a0();
extern "C" void EXT_79b4b0();
extern "C" void EXT_79b520();

// @ 0x0079bfa0
__declspec(naked) void FUN_0079bfa0() {
  __asm {
    sub esp, 24h
    push ebx
    mov ebx, dword ptr [esp + 2ch]
    push esi
    push edi
    push 0eh
    push 3
    push 0
    mov esi, ecx
    push 1
    push ebx
    mov dword ptr [esp + 2ch], esi
    call EXT_71ddc0
    mov edx, dword ptr [ebx + 8]
    mov ecx, eax
    shl ecx, 5
    lea ecx, [ecx + edx + 10h]
    mov edx, dword ptr [esp + 4ch]
    mov edi, dword ptr [edx + 4]
    imul edi, edi, 8ch
    add edi, dword ptr [ebx + 1ch]
    mov dword ptr [esp + 38h], ecx
    mov ecx, dword ptr [edx + 8]
    add esp, 14h
    cmp ecx, dword ptr [edx + 0ch]
    mov dword ptr [esp + 20h], eax
    mov dword ptr [esp + 34h], ecx
    _emit 0x0f
    _emit 0x8d
    _emit 0x59
    _emit 0x09
    _emit 0x00
    _emit 0x00  ; jge 0x79c94e
    push ebp
    add esi, 0ch
    _emit 0xeb
    _emit 0x0d  ; jmp 0x79c008
    _emit 0xeb
    _emit 0x03
    _emit 0x8d
    _emit 0x49
    _emit 0x00  ; data
    mov ecx, dword ptr [esp + 38h]
    mov eax, dword ptr [esp + 24h]
    mov ebx, dword ptr [edi + 4]
    lea edx, [ecx + 1]
    mov dword ptr [esp + 18h], edx
    lea edx, [ecx + 2]
    mov dword ptr [esp + 14h], edx
    mov edx, dword ptr [edi + 44h]
    cmp edx, dword ptr [edi + 48h]
    _emit 0x0f
    _emit 0x84
    _emit 0xa9
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x79c0ce
    mov edx, dword ptr [edi + 14h]
    movsx eax, word ptr [edx + eax*4 + 2]
    mov edx, dword ptr [edi + 44h]
    movzx ebp, word ptr [edi + 8]
    mov ebp, dword ptr [ebp*4 + 140f544h]
    shl eax, 4
    add eax, edx
    movzx edx, word ptr [edi + 0ah]
    mov dword ptr [esp + 10h], ebp
    mov ebp, edx
    imul ebp, ecx
    mov ecx, dword ptr [ebx + ebp]
    movzx ebx, word ptr [eax + 0ah]
    and ecx, dword ptr [esp + 10h]
    movzx ebp, word ptr [eax + 8]
    imul ecx, ebx
    mov ebx, dword ptr [eax + 4]
    mov ecx, dword ptr [ecx + ebx]
    mov ebx, edx
    imul ebx, dword ptr [esp + 18h]
    and ecx, dword ptr [ebp*4 + 140f544h]
    movzx ebp, word ptr [eax + 8]
    mov dword ptr [esp + 20h], edx
    mov edx, dword ptr [edi + 4]
    mov edx, dword ptr [ebx + edx]
    movzx ebx, word ptr [eax + 0ah]
    and edx, dword ptr [esp + 10h]
    imul edx, ebx
    mov ebx, dword ptr [eax + 4]
    mov edx, dword ptr [edx + ebx]
    mov ebx, dword ptr [esp + 20h]
    imul ebx, dword ptr [esp + 14h]
    and edx, dword ptr [ebp*4 + 140f544h]
    mov ebp, dword ptr [edi + 4]
    mov ebx, dword ptr [ebx + ebp]
    movzx ebp, word ptr [eax + 0ah]
    and ebx, dword ptr [esp + 10h]
    imul ebx, ebp
    mov ebp, dword ptr [eax + 4]
    movzx eax, word ptr [eax + 8]
    mov dword ptr [esp + 20h], eax
    mov eax, dword ptr [ebx + ebp]
    mov ebx, dword ptr [esp + 20h]
    and eax, dword ptr [ebx*4 + 140f544h]
    _emit 0xeb
    _emit 0x37  ; jmp 0x79c105
    movzx eax, word ptr [edi + 0ah]
    movzx edx, word ptr [edi + 8]
    mov edx, dword ptr [edx*4 + 140f544h]
    mov ebp, eax
    imul ebp, ecx
    mov ecx, dword ptr [ebx + ebp]
    mov dword ptr [esp + 10h], edx
    and ecx, edx
    mov edx, eax
    imul eax, dword ptr [esp + 14h]
    imul edx, dword ptr [esp + 18h]
    mov edx, dword ptr [edx + ebx]
    mov eax, dword ptr [eax + ebx]
    and edx, dword ptr [esp + 10h]
    and eax, dword ptr [esp + 10h]
    mov ebx, dword ptr [esp + 28h]
    movzx ebp, word ptr [ebx + 0ah]
    mov ebx, dword ptr [ebx + 4]
    movss xmm0, dword ptr [esi + 14h]
    movss xmm1, dword ptr [esi + 10h]
    movss xmm3, dword ptr [esi + 14h]
    movss xmm2, dword ptr [esi + 10h]
    mov dword ptr [esp + 18h], ebx
    mov ebx, ebp
    imul ebx, ecx
    add ebx, dword ptr [esp + 18h]
    mov dword ptr [esp + 20h], ebp
    imul ebp, edx
    movss xmm5, dword ptr [ebx + 4]
    subss xmm5, dword ptr [esi + 4]
    movss xmm6, dword ptr [ebx + 8]
    subss xmm6, dword ptr [esi + 8]
    mov ecx, dword ptr [esp + 20h]
    movss xmm4, dword ptr [ebx]
    imul ecx, eax
    subss xmm4, dword ptr [esi]
    mov edx, dword ptr [esp + 18h]
    mulss xmm0, xmm6
    mulss xmm1, xmm5
    addss xmm0, xmm1
    movss xmm1, dword ptr [esi + 0ch]
    mulss xmm1, xmm4
    addss xmm0, xmm1
    movss xmm1, dword ptr [esi + 0ch]
    mulss xmm3, xmm0
    mulss xmm2, xmm0
    mulss xmm1, xmm0
    subss xmm3, xmm6
    subss xmm2, xmm5
    movaps xmm0, xmm3
    mulss xmm0, xmm3
    movaps xmm3, xmm2
    mulss xmm3, xmm2
    subss xmm1, xmm4
    movaps xmm2, xmm1
    add ecx, edx
    addss xmm0, xmm3
    mulss xmm2, xmm1
    add ebp, edx
    addss xmm0, xmm2
    comiss xmm0, dword ptr [esi + 18h]
    mov dword ptr [esp + 10h], ecx
    _emit 0x76
    _emit 0x07  ; jbe 0x79c1c7
    mov ecx, 1
    _emit 0xeb
    _emit 0x02  ; jmp 0x79c1c9
    xor ecx, ecx
    movss xmm5, dword ptr [ebp + 4]
    subss xmm5, dword ptr [esi + 4]
    movss xmm6, dword ptr [ebp + 8]
    subss xmm6, dword ptr [esi + 8]
    movss xmm0, dword ptr [esi + 14h]
    movss xmm1, dword ptr [esi + 10h]
    movss xmm4, dword ptr [ebp]
    subss xmm4, dword ptr [esi]
    mov eax, dword ptr [esp + 1ch]
    mov eax, dword ptr [eax + 28h]
    movss xmm2, dword ptr [esi + 10h]
    movss xmm3, dword ptr [esi + 14h]
    mulss xmm1, xmm5
    mulss xmm0, xmm6
    addss xmm0, xmm1
    movaps xmm1, xmm4
    mulss xmm1, dword ptr [esi + 0ch]
    addss xmm0, xmm1
    movaps xmm1, xmm0
    mulss xmm1, dword ptr [esi + 0ch]
    subss xmm1, xmm4
    xor edx, edx
    mulss xmm2, xmm0
    mulss xmm3, xmm0
    movaps xmm0, xmm1
    mulss xmm0, xmm1
    cmp ecx, eax
    sete dl
    subss xmm3, xmm6
    movaps xmm1, xmm3
    mulss xmm1, xmm3
    addss xmm0, xmm1
    subss xmm2, xmm5
    movaps xmm1, xmm2
    mulss xmm1, xmm2
    addss xmm0, xmm1
    comiss xmm0, dword ptr [esi + 18h]
    mov dword ptr [esp + 14h], edx
    _emit 0x76
    _emit 0x07  ; jbe 0x79c26a
    mov ecx, 1
    _emit 0xeb
    _emit 0x02  ; jmp 0x79c26c
    xor ecx, ecx
    movss xmm0, dword ptr [esi + 14h]
    movss xmm1, dword ptr [esi + 10h]
    movss xmm2, dword ptr [esi + 10h]
    movss xmm3, dword ptr [esi + 14h]
    xor edx, edx
    cmp ecx, eax
    mov ecx, dword ptr [esp + 10h]
    movss xmm5, dword ptr [ecx + 4]
    subss xmm5, dword ptr [esi + 4]
    movss xmm6, dword ptr [ecx + 8]
    subss xmm6, dword ptr [esi + 8]
    movss xmm4, dword ptr [ecx]
    subss xmm4, dword ptr [esi]
    mulss xmm1, xmm5
    mulss xmm0, xmm6
    addss xmm0, xmm1
    movaps xmm1, xmm4
    mulss xmm1, dword ptr [esi + 0ch]
    addss xmm0, xmm1
    movaps xmm1, xmm0
    mulss xmm1, dword ptr [esi + 0ch]
    subss xmm1, xmm4
    mulss xmm2, xmm0
    mulss xmm3, xmm0
    movaps xmm0, xmm1
    mulss xmm0, xmm1
    sete dl
    subss xmm3, xmm6
    movaps xmm1, xmm3
    mulss xmm1, xmm3
    addss xmm0, xmm1
    subss xmm2, xmm5
    movaps xmm1, xmm2
    mulss xmm1, xmm2
    addss xmm0, xmm1
    comiss xmm0, dword ptr [esi + 18h]
    mov dword ptr [esp + 18h], edx
    _emit 0x76
    _emit 0x07  ; jbe 0x79c309
    mov ecx, 1
    _emit 0xeb
    _emit 0x02  ; jmp 0x79c30b
    xor ecx, ecx
    xor edx, edx
    cmp ecx, eax
    mov ecx, dword ptr [esp + 18h]
    sete dl
    mov eax, edx
    add ecx, eax
    add ecx, dword ptr [esp + 14h]
    mov dword ptr [esp + 20h], eax
    mov eax, 55555556h
    imul ecx
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    lea edx, [eax + eax*2]
    mov eax, ecx
    sub eax, edx
    mov dword ptr [esp + 30h], ecx
    _emit 0x0f
    _emit 0x85
    _emit 0xea
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; jne 0x79c42b
    cmp dword ptr [esp + 14h], eax
    _emit 0x0f
    _emit 0x84
    _emit 0xea
    _emit 0x05
    _emit 0x00
    _emit 0x00  ; je 0x79c935
    movzx ecx, word ptr [edi + 0ah]
    mov ebp, dword ptr [esp + 38h]
    movzx eax, word ptr [edi + 8]
    imul ecx, ebp
    mov edx, dword ptr [edi + 4]
    mov cx, word ptr [ecx + edx]
    and cx, word ptr [eax*4 + 140f544h]
    mov ebx, dword ptr [esp + 40h]
    mov eax, dword ptr [ebx + 4]
    movzx ecx, cx
    mov dword ptr [esp + 20h], ecx
    cmp eax, dword ptr [ebx + 8]
    _emit 0x73
    _emit 0x0f  ; jae 0x79c38b
    lea edx, [eax + 2]
    mov dword ptr [ebx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x12  ; je 0x79c398
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0d  ; jmp 0x79c398
    lea ecx, [esp + 20h]
    push ecx
    push eax
    mov ecx, ebx
    call EXT_6f5bc0
    movzx edx, word ptr [edi + 0ah]
    movzx ecx, word ptr [edi + 8]
    lea eax, [ebp + 1]
    imul edx, eax
    mov eax, dword ptr [edi + 4]
    mov dx, word ptr [edx + eax]
    and dx, word ptr [ecx*4 + 140f544h]
    mov eax, dword ptr [ebx + 4]
    movzx ecx, dx
    mov dword ptr [esp + 20h], ecx
    cmp eax, dword ptr [ebx + 8]
    _emit 0x73
    _emit 0x0f  ; jae 0x79c3d3
    lea edx, [eax + 2]
    mov dword ptr [ebx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x12  ; je 0x79c3e0
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0d  ; jmp 0x79c3e0
    lea ecx, [esp + 20h]
    push ecx
    push eax
    mov ecx, ebx
    call EXT_6f5bc0
    movzx edx, word ptr [edi + 0ah]
    movzx ecx, word ptr [edi + 8]
    lea eax, [ebp + 2]
    imul edx, eax
    mov eax, dword ptr [edi + 4]
    mov dx, word ptr [edx + eax]
    and dx, word ptr [ecx*4 + 140f544h]
    mov eax, dword ptr [ebx + 4]
    movzx ecx, dx
    mov dword ptr [esp + 20h], ecx
    cmp eax, dword ptr [ebx + 8]
    _emit 0x73
    _emit 0x16  ; jae 0x79c422
    lea edx, [eax + 2]
    mov dword ptr [ebx + 4], edx
    test eax, eax
    _emit 0x0f
    _emit 0x84
    _emit 0x1b
    _emit 0x05
    _emit 0x00
    _emit 0x00  ; je 0x79c935
    mov word ptr [eax], cx
    _emit 0xe9
    _emit 0x13
    _emit 0x05
    _emit 0x00
    _emit 0x00  ; jmp 0x79c935
    lea ecx, [esp + 20h]
    _emit 0xe9
    _emit 0x01
    _emit 0x05
    _emit 0x00
    _emit 0x00  ; jmp 0x79c92c
    mov edx, dword ptr [esp + 1ch]
    mov eax, dword ptr [edx + 8]
    sub eax, 0
    _emit 0x0f
    _emit 0x84
    _emit 0x1d
    _emit 0x04
    _emit 0x00
    _emit 0x00  ; je 0x79c858
    sub eax, 2
    _emit 0x0f
    _emit 0x84
    _emit 0xe8
    _emit 0x03
    _emit 0x00
    _emit 0x00  ; je 0x79c82c
    sub eax, 1
    _emit 0x0f
    _emit 0x85
    _emit 0xe8
    _emit 0x04
    _emit 0x00
    _emit 0x00  ; jne 0x79c935
    mov ecx, dword ptr [esp + 44h]
    mov eax, dword ptr [ecx + 8]
    sub eax, dword ptr [ecx + 4]
    sar eax, 4
    cmp dword ptr [esp + 14h], 0
    movzx edx, ax
    mov dword ptr [esp + 2ch], edx
    _emit 0x0f
    _emit 0x84
    _emit 0x37
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x79c5a3
    mov eax, dword ptr [esp + 38h]
    mov edx, dword ptr [esp + 3ch]
    push eax
    mov eax, dword ptr [edx + 4]
    push eax
    call EXT_79b4b0
    cmp dword ptr [esp + 18h], 0
    _emit 0x74
    _emit 0x78  ; je 0x79c4fd
    mov eax, dword ptr [esp + 38h]
    mov ecx, dword ptr [esp + 3ch]
    mov edx, dword ptr [ecx + 4]
    mov ecx, dword ptr [esp + 44h]
    inc eax
    push eax
    push edx
    call EXT_79b4b0
    mov eax, dword ptr [esp + 10h]
    push eax
    push ebp
    mov ecx, esi
    call EXT_7999a0
    mov eax, dword ptr [esp + 38h]
    mov ebp, dword ptr [esp + 44h]
    push ecx
    lea ecx, [eax + 2]
    fstp dword ptr [esp]
    push ecx
    mov dword ptr [esp + 1ch], ecx
    mov ecx, dword ptr [esp + 44h]
    mov edx, dword ptr [ecx + 4]
    inc eax
    push eax
    push edx
    mov ecx, ebp
    call EXT_79b520
    mov eax, dword ptr [esp + 10h]
    push eax
    push ebx
    mov ecx, esi
    call EXT_7999a0
    mov edx, dword ptr [esp + 38h]
    mov eax, dword ptr [esp + 3ch]
    push ecx
    mov ecx, dword ptr [esp + 18h]
    fstp dword ptr [esp]
    push ecx
    mov ecx, dword ptr [eax + 4]
    push edx
    push ecx
    mov ecx, ebp
    call EXT_79b520
    _emit 0xe9
    _emit 0xbb
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jmp 0x79c6b8
    push ebp
    push ebx
    mov ecx, esi
    call EXT_7999a0
    mov eax, dword ptr [esp + 38h]
    mov edx, dword ptr [esp + 38h]
    push ecx
    fstp dword ptr [esp]
    inc eax
    push eax
    mov eax, dword ptr [esp + 44h]
    mov ecx, dword ptr [eax + 4]
    push edx
    push ecx
    mov ecx, dword ptr [esp + 54h]
    call EXT_79b520
    cmp dword ptr [esp + 20h], 0
    _emit 0x74
    _emit 0x3e  ; je 0x79c56b
    mov edx, dword ptr [esp + 10h]
    push ebp
    push edx
    mov ecx, esi
    call EXT_7999a0
    mov eax, dword ptr [esp + 38h]
    mov ebp, dword ptr [esp + 44h]
    push ecx
    lea ecx, [eax + 1]
    fstp dword ptr [esp]
    push ecx
    lea ebx, [eax + 2]
    mov eax, dword ptr [esp + 44h]
    mov ecx, dword ptr [eax + 4]
    push ebx
    push ecx
    mov ecx, ebp
    call EXT_79b520
    mov edx, dword ptr [esp + 3ch]
    mov eax, dword ptr [edx + 4]
    push ebx
    push eax
    _emit 0xe9
    _emit 0x46
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jmp 0x79c6b1
    mov ecx, dword ptr [esp + 10h]
    push ecx
    push ebx
    mov ecx, esi
    call EXT_7999a0
    mov eax, dword ptr [esp + 38h]
    mov edx, dword ptr [esp + 38h]
    push ecx
    fstp dword ptr [esp]
    add eax, 2
    push eax
    mov eax, dword ptr [esp + 44h]
    mov ecx, dword ptr [eax + 4]
    push edx
    push ecx
    mov ecx, dword ptr [esp + 54h]
    call EXT_79b520
    mov ebp, dword ptr [esp + 44h]
    _emit 0xe9
    _emit 0x15
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jmp 0x79c6b8
    cmp dword ptr [esp + 18h], 0
    push ebx
    mov ecx, esi
    _emit 0x0f
    _emit 0x84
    _emit 0xa4
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x79c655
    push ebp
    call EXT_7999a0
    mov eax, dword ptr [esp + 38h]
    mov edx, dword ptr [esp + 3ch]
    push ecx
    mov ecx, dword ptr [esp + 48h]
    fstp dword ptr [esp]
    push eax
    inc eax
    push eax
    mov eax, dword ptr [edx + 4]
    push eax
    call EXT_79b520
    mov eax, dword ptr [esp + 38h]
    mov ecx, dword ptr [esp + 3ch]
    mov edx, dword ptr [ecx + 4]
    mov ecx, dword ptr [esp + 44h]
    inc eax
    push eax
    push edx
    call EXT_79b4b0
    cmp dword ptr [esp + 20h], 0
    _emit 0x74
    _emit 0x32  ; je 0x79c623
    mov ebp, dword ptr [esp + 38h]
    mov eax, dword ptr [esp + 3ch]
    mov ecx, dword ptr [eax + 4]
    add ebp, 2
    push ebp
    push ecx
    mov ecx, dword ptr [esp + 4ch]
    call EXT_79b4b0
    mov edx, dword ptr [esp + 10h]
    push ebx
    push edx
    mov ecx, esi
    call EXT_7999a0
    mov eax, dword ptr [esp + 38h]
    push ecx
    fstp dword ptr [esp]
    push eax
    push ebp
    _emit 0xeb
    _emit 0x1b  ; jmp 0x79c63e
    mov eax, dword ptr [esp + 10h]
    push eax
    push ebp
    mov ecx, esi
    call EXT_7999a0
    mov eax, dword ptr [esp + 38h]
    push ecx
    lea ecx, [eax + 2]
    fstp dword ptr [esp]
    push ecx
    inc eax
    push eax
    mov ecx, dword ptr [esp + 48h]
    mov edx, dword ptr [ecx + 4]
    mov ecx, dword ptr [esp + 50h]
    push edx
    call EXT_79b520
    mov ebp, dword ptr [esp + 44h]
    _emit 0xeb
    _emit 0x63  ; jmp 0x79c6b8
    mov eax, dword ptr [esp + 14h]
    push eax
    call EXT_7999a0
    mov ebx, dword ptr [esp + 38h]
    push ecx
    mov ecx, dword ptr [esp + 40h]
    fstp dword ptr [esp]
    mov edx, dword ptr [ecx + 4]
    mov ecx, dword ptr [esp + 48h]
    push ebx
    add ebx, 2
    push ebx
    push edx
    call EXT_79b520
    mov eax, dword ptr [esp + 10h]
    push ebp
    push eax
    mov ecx, esi
    call EXT_7999a0
    mov eax, dword ptr [esp + 38h]
    mov ebp, dword ptr [esp + 44h]
    push ecx
    mov ecx, dword ptr [esp + 40h]
    fstp dword ptr [esp]
    mov edx, dword ptr [ecx + 4]
    inc eax
    push eax
    push ebx
    push edx
    mov ecx, ebp
    call EXT_79b520
    mov eax, dword ptr [esp + 3ch]
    mov ecx, dword ptr [eax + 4]
    push ebx
    push ecx
    mov ecx, ebp
    call EXT_79b4b0
    mov eax, dword ptr [ebp + 30h]
    mov ebx, dword ptr [esp + 2ch]
    mov ecx, dword ptr [ebp + 18h]
    lea eax, [eax + eax*4]
    lea ecx, [ecx + eax*4]
    mov eax, dword ptr [ecx + 4]
    movzx edx, bx
    mov dword ptr [esp + 2ch], edx
    cmp eax, dword ptr [ecx + 8]
    _emit 0x73
    _emit 0x0f  ; jae 0x79c6e6
    lea edx, [eax + 2]
    mov dword ptr [ecx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x10  ; je 0x79c6f1
    mov word ptr [eax], bx
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79c6f1
    lea edx, [esp + 2ch]
    push edx
    push eax
    call EXT_6f5bc0
    lea eax, [ebx + 1]
    movzx ecx, ax
    mov eax, dword ptr [ebp + 30h]
    lea edx, [eax + eax*4]
    mov eax, dword ptr [ebp + 18h]
    mov dword ptr [esp + 20h], ecx
    lea ecx, [eax + edx*4]
    mov eax, dword ptr [ecx + 4]
    cmp eax, dword ptr [ecx + 8]
    _emit 0x73
    _emit 0x14  ; jae 0x79c723
    lea edx, [eax + 2]
    mov dword ptr [ecx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x15  ; je 0x79c72e
    mov cx, word ptr [esp + 20h]
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79c72e
    lea edx, [esp + 20h]
    push edx
    push eax
    call EXT_6f5bc0
    mov edx, dword ptr [ebp + 18h]
    lea eax, [ebx + 2]
    movzx eax, ax
    mov dword ptr [esp + 20h], eax
    mov eax, dword ptr [ebp + 30h]
    lea ecx, [eax + eax*4]
    mov eax, dword ptr [edx + ecx*4 + 4]
    cmp eax, dword ptr [edx + ecx*4 + 8]
    lea ecx, [edx + ecx*4]
    _emit 0x73
    _emit 0x14  ; jae 0x79c762
    lea edx, [eax + 2]
    mov dword ptr [ecx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x15  ; je 0x79c76d
    mov cx, word ptr [esp + 20h]
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79c76d
    lea edx, [esp + 20h]
    push edx
    push eax
    call EXT_6f5bc0
    cmp dword ptr [esp + 30h], 1
    _emit 0x0f
    _emit 0x8e
    _emit 0xbd
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jle 0x79c935
    mov edx, dword ptr [ebp + 18h]
    movzx eax, bx
    mov dword ptr [esp + 30h], eax
    mov eax, dword ptr [ebp + 30h]
    lea ecx, [eax + eax*4]
    mov eax, dword ptr [edx + ecx*4 + 4]
    cmp eax, dword ptr [edx + ecx*4 + 8]
    lea ecx, [edx + ecx*4]
    _emit 0x73
    _emit 0x0f  ; jae 0x79c7a4
    lea edx, [eax + 2]
    mov dword ptr [ecx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x10  ; je 0x79c7af
    mov word ptr [eax], bx
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79c7af
    lea edx, [esp + 30h]
    push edx
    push eax
    call EXT_6f5bc0
    mov edx, dword ptr [ebp + 18h]
    lea eax, [ebx + 2]
    movzx eax, ax
    mov dword ptr [esp + 20h], eax
    mov eax, dword ptr [ebp + 30h]
    lea ecx, [eax + eax*4]
    mov eax, dword ptr [edx + ecx*4 + 4]
    cmp eax, dword ptr [edx + ecx*4 + 8]
    lea ecx, [edx + ecx*4]
    _emit 0x73
    _emit 0x14  ; jae 0x79c7e3
    lea edx, [eax + 2]
    mov dword ptr [ecx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x15  ; je 0x79c7ee
    mov cx, word ptr [esp + 20h]
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79c7ee
    lea edx, [esp + 20h]
    push edx
    push eax
    call EXT_6f5bc0
    mov eax, dword ptr [ebp + 30h]
    mov ecx, dword ptr [ebp + 18h]
    lea eax, [eax + eax*4]
    add ebx, 3
    lea ecx, [ecx + eax*4]
    mov eax, dword ptr [ecx + 4]
    movzx edx, bx
    mov dword ptr [esp + 30h], edx
    cmp eax, dword ptr [ecx + 8]
    _emit 0x73
    _emit 0x16  ; jae 0x79c822
    lea ebx, [eax + 2]
    mov dword ptr [ecx + 4], ebx
    test eax, eax
    _emit 0x0f
    _emit 0x84
    _emit 0x1b
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; je 0x79c935
    mov word ptr [eax], dx
    _emit 0xe9
    _emit 0x13
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jmp 0x79c935
    lea edx, [esp + 30h]
    push edx
    _emit 0xe9
    _emit 0x03
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jmp 0x79c92f
    cmp ecx, 1
    _emit 0x0f
    _emit 0x8e
    _emit 0x00
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jle 0x79c935
    movzx eax, word ptr [edi + 0ah]
    mov ebp, dword ptr [esp + 38h]
    mov ecx, dword ptr [edi + 4]
    imul eax, ebp
    movzx edx, word ptr [edi + 8]
    mov ax, word ptr [eax + ecx]
    and ax, word ptr [edx*4 + 140f544h]
    movzx ecx, ax
    _emit 0xeb
    _emit 0x21  ; jmp 0x79c879
    movzx edx, word ptr [edi + 0ah]
    mov ebp, dword ptr [esp + 38h]
    movzx ecx, word ptr [edi + 8]
    imul edx, ebp
    mov eax, dword ptr [edi + 4]
    mov dx, word ptr [edx + eax]
    and dx, word ptr [ecx*4 + 140f544h]
    movzx ecx, dx
    mov ebx, dword ptr [esp + 40h]
    mov eax, dword ptr [ebx + 4]
    mov dword ptr [esp + 30h], ecx
    cmp eax, dword ptr [ebx + 8]
    _emit 0x73
    _emit 0x0f  ; jae 0x79c898
    lea edx, [eax + 2]
    mov dword ptr [ebx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x12  ; je 0x79c8a5
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0d  ; jmp 0x79c8a5
    lea ecx, [esp + 30h]
    push ecx
    push eax
    mov ecx, ebx
    call EXT_6f5bc0
    movzx edx, word ptr [edi + 0ah]
    movzx ecx, word ptr [edi + 8]
    lea eax, [ebp + 1]
    imul edx, eax
    mov eax, dword ptr [edi + 4]
    mov dx, word ptr [edx + eax]
    and dx, word ptr [ecx*4 + 140f544h]
    mov eax, dword ptr [ebx + 4]
    movzx ecx, dx
    mov dword ptr [esp + 30h], ecx
    cmp eax, dword ptr [ebx + 8]
    _emit 0x73
    _emit 0x0f  ; jae 0x79c8e0
    lea edx, [eax + 2]
    mov dword ptr [ebx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x12  ; je 0x79c8ed
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0d  ; jmp 0x79c8ed
    lea ecx, [esp + 30h]
    push ecx
    push eax
    mov ecx, ebx
    call EXT_6f5bc0
    movzx edx, word ptr [edi + 0ah]
    movzx ecx, word ptr [edi + 8]
    lea eax, [ebp + 2]
    imul edx, eax
    mov eax, dword ptr [edi + 4]
    mov dx, word ptr [edx + eax]
    and dx, word ptr [ecx*4 + 140f544h]
    mov eax, dword ptr [ebx + 4]
    movzx ecx, dx
    mov dword ptr [esp + 30h], ecx
    cmp eax, dword ptr [ebx + 8]
    _emit 0x73
    _emit 0x0f  ; jae 0x79c928
    lea edx, [eax + 2]
    mov dword ptr [ebx + 4], edx
    test eax, eax
    _emit 0x74
    _emit 0x12  ; je 0x79c935
    mov word ptr [eax], cx
    _emit 0xeb
    _emit 0x0d  ; jmp 0x79c935
    lea ecx, [esp + 30h]
    push ecx
    mov ecx, ebx
    push eax
    call EXT_6f5bc0
    mov eax, dword ptr [esp + 38h]
    mov edx, dword ptr [esp + 3ch]
    add eax, 3
    cmp eax, dword ptr [edx + 0ch]
    mov dword ptr [esp + 38h], eax
    _emit 0x0f
    _emit 0x8c
    _emit 0xb3
    _emit 0xf6
    _emit 0xff
    _emit 0xff  ; jl 0x79c000
    pop ebp
    pop edi
    pop esi
    pop ebx
    add esp, 24h
    ret 10h
  }
}


