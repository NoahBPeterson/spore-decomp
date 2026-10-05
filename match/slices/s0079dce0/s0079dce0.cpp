// slice s0079dce0
// Per-instruction reconstruction (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
// Control flow is decoded recursively; call targets are symbolic so COFF
// relocation bytes are masked by the verifier. Unreachable bytes are data.

extern "C" void EXT_6f5bc0();
extern "C" void EXT_71ddc0();

// @ 0x0079dce0
__declspec(naked) void FUN_0079dce0() {
  __asm {
    sub esp, 2ch
    push ebp
    push esi
    push edi
    mov edi, dword ptr [esp + 3ch]
    push 0eh
    push 3
    push 0
    push 1
    push edi
    mov dword ptr [esp + 20h], ecx
    call EXT_71ddc0
    mov ebp, dword ptr [esp + 54h]
    mov esi, dword ptr [ebp + 4]
    mov ecx, dword ptr [edi + 8]
    imul esi, esi, 8ch
    add esi, dword ptr [edi + 1ch]
    mov dword ptr [esp + 40h], eax
    shl eax, 5
    lea edx, [eax + ecx + 10h]
    mov eax, dword ptr [ebp + 8]
    add esp, 14h
    cmp eax, dword ptr [ebp + 0ch]
    mov dword ptr [esp + 30h], edx
    mov dword ptr [esp + 3ch], eax
    _emit 0x0f
    _emit 0x8d
    _emit 0x02
    _emit 0x0c
    _emit 0x00
    _emit 0x00  ; jge 0x79e933
    push ebx
    mov ecx, dword ptr [esp + 40h]
    mov eax, dword ptr [esi + 44h]
    lea ebx, [ecx + 1]
    lea edi, [ecx + 2]
    cmp eax, dword ptr [esi + 48h]
    _emit 0x0f
    _emit 0x84
    _emit 0xd8
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x79de20
    mov eax, dword ptr [esp + 30h]
    mov edx, dword ptr [esi + 14h]
    movsx edx, word ptr [edx + eax*4 + 2]
    mov eax, dword ptr [esi + 44h]
    shl edx, 4
    add eax, edx
    movzx edx, word ptr [esi + 0ah]
    mov dword ptr [esp + 44h], edx
    movzx edx, word ptr [esi + 8]
    mov edx, dword ptr [edx*4 + 140f544h]
    mov dword ptr [esp + 20h], edx
    mov edx, dword ptr [esp + 44h]
    imul edx, ecx
    mov ecx, dword ptr [esi + 4]
    mov ecx, dword ptr [edx + ecx]
    movzx edx, word ptr [eax + 0ah]
    and ecx, dword ptr [esp + 20h]
    mov dword ptr [esp + 28h], eax
    imul ecx, edx
    mov edx, dword ptr [eax + 4]
    movzx eax, word ptr [eax + 8]
    mov dword ptr [esp + 2ch], eax
    mov eax, dword ptr [ecx + edx]
    mov edx, dword ptr [esp + 44h]
    mov ecx, dword ptr [esp + 2ch]
    imul edx, ebx
    and eax, dword ptr [ecx*4 + 140f544h]
    mov dword ptr [esp + 24h], eax
    mov eax, dword ptr [esi + 4]
    mov ecx, dword ptr [edx + eax]
    and ecx, dword ptr [esp + 20h]
    mov eax, dword ptr [esp + 28h]
    movzx edx, word ptr [eax + 0ah]
    imul ecx, edx
    mov edx, dword ptr [eax + 4]
    movzx eax, word ptr [eax + 8]
    mov dword ptr [esp + 2ch], eax
    mov eax, dword ptr [ecx + edx]
    mov ecx, dword ptr [esp + 2ch]
    and eax, dword ptr [ecx*4 + 140f544h]
    mov ecx, dword ptr [esi + 4]
    mov dword ptr [esp + 2ch], eax
    mov eax, dword ptr [esp + 44h]
    imul eax, edi
    mov edx, dword ptr [eax + ecx]
    mov eax, dword ptr [esp + 28h]
    movzx ecx, word ptr [eax + 0ah]
    and edx, dword ptr [esp + 20h]
    imul edx, ecx
    mov ecx, dword ptr [eax + 4]
    movzx eax, word ptr [eax + 8]
    mov dword ptr [esp + 44h], eax
    mov eax, dword ptr [edx + ecx]
    mov edx, dword ptr [esp + 44h]
    and eax, dword ptr [edx*4 + 140f544h]
    mov edx, dword ptr [esp + 2ch]
    _emit 0xeb
    _emit 0x3f  ; jmp 0x79de5f
    movzx edx, word ptr [esi + 8]
    mov edx, dword ptr [edx*4 + 140f544h]
    movzx eax, word ptr [esi + 0ah]
    mov dword ptr [esp + 44h], edx
    mov edx, eax
    imul edx, ecx
    mov ecx, dword ptr [esi + 4]
    mov ecx, dword ptr [edx + ecx]
    and ecx, dword ptr [esp + 44h]
    mov edx, eax
    imul eax, edi
    imul edx, ebx
    mov dword ptr [esp + 24h], ecx
    mov ecx, dword ptr [esi + 4]
    mov edx, dword ptr [edx + ecx]
    mov eax, dword ptr [eax + ecx]
    and edx, dword ptr [esp + 44h]
    and eax, dword ptr [esp + 44h]
    mov ecx, dword ptr [esp + 34h]
    mov dword ptr [esp + 28h], eax
    movzx eax, word ptr [ecx + 0ah]
    mov ecx, dword ptr [ecx + 4]
    mov dword ptr [esp + 44h], eax
    imul eax, dword ptr [esp + 24h]
    movss xmm5, dword ptr [eax + ecx + 4]
    movss xmm6, dword ptr [eax + ecx + 8]
    movss xmm4, dword ptr [eax + ecx]
    add eax, ecx
    mov dword ptr [esp + 20h], ecx
    mov ecx, dword ptr [esp + 44h]
    imul ecx, edx
    add ecx, dword ptr [esp + 20h]
    mov edx, dword ptr [esp + 10h]
    subss xmm5, dword ptr [edx + 10h]
    subss xmm6, dword ptr [edx + 14h]
    movss xmm0, dword ptr [edx + 20h]
    movss xmm1, dword ptr [edx + 1ch]
    subss xmm4, dword ptr [edx + 0ch]
    movss xmm3, dword ptr [edx + 20h]
    movss xmm2, dword ptr [edx + 1ch]
    add edx, 0ch
    mulss xmm0, xmm6
    mulss xmm1, xmm5
    addss xmm0, xmm1
    movss xmm1, dword ptr [edx + 0ch]
    mov dword ptr [esp + 14h], ecx
    mov ecx, dword ptr [esp + 44h]
    imul ecx, dword ptr [esp + 28h]
    add ecx, dword ptr [esp + 20h]
    mulss xmm1, xmm4
    addss xmm0, xmm1
    movss xmm1, dword ptr [edx + 0ch]
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
    addss xmm0, xmm3
    mulss xmm2, xmm1
    addss xmm0, xmm2
    comiss xmm0, dword ptr [edx + 18h]
    mov dword ptr [esp + 18h], eax
    mov dword ptr [esp + 44h], ecx
    mov dword ptr [esp + 2ch], edx
    mov dword ptr [esp + 20h], 1
    _emit 0x77
    _emit 0x08  ; ja 0x79df49
    mov dword ptr [esp + 20h], 0
    mov eax, dword ptr [esp + 14h]
    movss xmm5, dword ptr [eax + 4]
    subss xmm5, dword ptr [edx + 4]
    movss xmm6, dword ptr [eax + 8]
    subss xmm6, dword ptr [edx + 8]
    movss xmm0, dword ptr [edx + 14h]
    movss xmm1, dword ptr [edx + 10h]
    movss xmm4, dword ptr [eax]
    subss xmm4, dword ptr [edx]
    movss xmm2, dword ptr [edx + 10h]
    movss xmm3, dword ptr [edx + 14h]
    mulss xmm1, xmm5
    mulss xmm0, xmm6
    addss xmm0, xmm1
    movaps xmm1, xmm4
    mulss xmm1, dword ptr [edx + 0ch]
    addss xmm0, xmm1
    movaps xmm1, xmm0
    mulss xmm1, dword ptr [edx + 0ch]
    subss xmm1, xmm4
    mulss xmm2, xmm0
    mulss xmm3, xmm0
    movaps xmm0, xmm1
    mulss xmm0, xmm1
    subss xmm3, xmm6
    movaps xmm1, xmm3
    mulss xmm1, xmm3
    addss xmm0, xmm1
    subss xmm2, xmm5
    movaps xmm1, xmm2
    mulss xmm1, xmm2
    addss xmm0, xmm1
    comiss xmm0, dword ptr [edx + 18h]
    _emit 0x76
    _emit 0x07  ; jbe 0x79dfdb
    mov edx, 1
    _emit 0xeb
    _emit 0x02  ; jmp 0x79dfdd
    xor edx, edx
    mov eax, dword ptr [esp + 2ch]
    movss xmm5, dword ptr [ecx + 4]
    subss xmm5, dword ptr [eax + 4]
    movss xmm6, dword ptr [ecx + 8]
    subss xmm6, dword ptr [eax + 8]
    movss xmm0, dword ptr [eax + 14h]
    movss xmm1, dword ptr [eax + 10h]
    movss xmm4, dword ptr [ecx]
    subss xmm4, dword ptr [eax]
    movss xmm3, dword ptr [eax + 14h]
    movss xmm2, dword ptr [eax + 10h]
    mulss xmm0, xmm6
    mulss xmm1, xmm5
    addss xmm0, xmm1
    movaps xmm1, xmm4
    mulss xmm1, dword ptr [eax + 0ch]
    addss xmm0, xmm1
    mulss xmm3, xmm0
    mulss xmm2, xmm0
    movaps xmm1, xmm0
    mulss xmm1, dword ptr [eax + 0ch]
    subss xmm3, xmm6
    subss xmm2, xmm5
    movaps xmm0, xmm3
    mulss xmm0, xmm3
    movaps xmm3, xmm2
    mulss xmm3, xmm2
    subss xmm1, xmm4
    movaps xmm2, xmm1
    addss xmm0, xmm3
    mulss xmm2, xmm1
    addss xmm0, xmm2
    comiss xmm0, dword ptr [eax + 18h]
    mov dword ptr [esp + 24h], edx
    _emit 0x76
    _emit 0x07  ; jbe 0x79e073
    mov eax, 1
    _emit 0xeb
    _emit 0x02  ; jmp 0x79e075
    xor eax, eax
    lea ecx, [eax + edx]
    add ecx, dword ptr [esp + 20h]
    mov dword ptr [esp + 28h], eax
    mov eax, 55555556h
    imul ecx
    mov eax, edx
    shr eax, 1fh
    add eax, edx
    lea eax, [eax + eax*2]
    mov dword ptr [esp + 2ch], ecx
    sub ecx, eax
    _emit 0x0f
    _emit 0x85
    _emit 0xcc
    _emit 0x01
    _emit 0x00
    _emit 0x00  ; jne 0x79e269
    cmp dword ptr [esp + 20h], ecx
    _emit 0x0f
    _emit 0x85
    _emit 0xe2
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; jne 0x79e189
    movzx ecx, word ptr [esi + 0ah]
    imul ecx, dword ptr [esp + 40h]
    mov edx, dword ptr [esi + 4]
    movzx eax, word ptr [esi + 8]
    mov cx, word ptr [ecx + edx]
    and cx, word ptr [eax*4 + 140f544h]
    movzx edx, cx
    mov dword ptr [esp + 44h], edx
    mov eax, dword ptr [esp + 4ch]
    mov ecx, dword ptr [eax + 4]
    cmp ecx, dword ptr [eax + 8]
    _emit 0x73
    _emit 0x14  ; jae 0x79e0ea
    lea edx, [ecx + 2]
    mov dword ptr [eax + 4], edx
    test ecx, ecx
    _emit 0x74
    _emit 0x1d  ; je 0x79e0fd
    mov dx, word ptr [esp + 44h]
    mov word ptr [ecx], dx
    _emit 0xeb
    _emit 0x13  ; jmp 0x79e0fd
    lea eax, [esp + 44h]
    push eax
    push ecx
    mov ecx, dword ptr [esp + 54h]
    call EXT_6f5bc0
    mov eax, dword ptr [esp + 4ch]
    movzx ecx, word ptr [esi + 0ah]
    mov edx, dword ptr [esi + 4]
    imul ecx, ebx
    movzx ebx, word ptr [esi + 8]
    mov cx, word ptr [ecx + edx]
    and cx, word ptr [ebx*4 + 140f544h]
    movzx edx, cx
    mov ecx, dword ptr [eax + 4]
    mov dword ptr [esp + 44h], edx
    cmp ecx, dword ptr [eax + 8]
    _emit 0x73
    _emit 0x0f  ; jae 0x79e135
    lea ebx, [ecx + 2]
    mov dword ptr [eax + 4], ebx
    test ecx, ecx
    _emit 0x74
    _emit 0x18  ; je 0x79e148
    mov word ptr [ecx], dx
    _emit 0xeb
    _emit 0x13  ; jmp 0x79e148
    lea edx, [esp + 44h]
    push edx
    push ecx
    mov ecx, dword ptr [esp + 54h]
    call EXT_6f5bc0
    mov eax, dword ptr [esp + 4ch]
    movzx ecx, word ptr [esi + 0ah]
    mov edx, dword ptr [esi + 4]
    imul ecx, edi
    movzx edi, word ptr [esi + 8]
    mov cx, word ptr [ecx + edx]
    and cx, word ptr [edi*4 + 140f544h]
    movzx edx, cx
    mov ecx, dword ptr [eax + 4]
    mov dword ptr [esp + 44h], edx
    cmp ecx, dword ptr [eax + 8]
    _emit 0x0f
    _emit 0x82
    _emit 0xde
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; jb 0x79e253
    lea edx, [esp + 44h]
    push edx
    push ecx
    mov ecx, dword ptr [esp + 54h]
    call EXT_6f5bc0
    _emit 0xe9
    _emit 0x95
    _emit 0x07
    _emit 0x00
    _emit 0x00  ; jmp 0x79e91e
    movzx eax, word ptr [esi + 0ah]
    imul eax, dword ptr [esp + 40h]
    mov ecx, dword ptr [esi + 4]
    movzx edx, word ptr [esi + 8]
    mov ax, word ptr [eax + ecx]
    and ax, word ptr [edx*4 + 140f544h]
    movzx ecx, ax
    mov dword ptr [esp + 44h], ecx
    mov eax, dword ptr [esp + 48h]
    mov ecx, dword ptr [eax + 4]
    cmp ecx, dword ptr [eax + 8]
    _emit 0x73
    _emit 0x14  ; jae 0x79e1cc
    lea edx, [ecx + 2]
    mov dword ptr [eax + 4], edx
    test ecx, ecx
    _emit 0x74
    _emit 0x1d  ; je 0x79e1df
    mov dx, word ptr [esp + 44h]
    mov word ptr [ecx], dx
    _emit 0xeb
    _emit 0x13  ; jmp 0x79e1df
    lea eax, [esp + 44h]
    push eax
    push ecx
    mov ecx, dword ptr [esp + 50h]
    call EXT_6f5bc0
    mov eax, dword ptr [esp + 48h]
    movzx ecx, word ptr [esi + 0ah]
    mov edx, dword ptr [esi + 4]
    imul ecx, ebx
    movzx ebx, word ptr [esi + 8]
    mov cx, word ptr [ecx + edx]
    and cx, word ptr [ebx*4 + 140f544h]
    movzx edx, cx
    mov ecx, dword ptr [eax + 4]
    mov dword ptr [esp + 44h], edx
    cmp ecx, dword ptr [eax + 8]
    _emit 0x73
    _emit 0x0f  ; jae 0x79e217
    lea ebx, [ecx + 2]
    mov dword ptr [eax + 4], ebx
    test ecx, ecx
    _emit 0x74
    _emit 0x18  ; je 0x79e22a
    mov word ptr [ecx], dx
    _emit 0xeb
    _emit 0x13  ; jmp 0x79e22a
    lea edx, [esp + 44h]
    push edx
    push ecx
    mov ecx, dword ptr [esp + 50h]
    call EXT_6f5bc0
    mov eax, dword ptr [esp + 48h]
    movzx ecx, word ptr [esi + 0ah]
    mov edx, dword ptr [esi + 4]
    imul ecx, edi
    movzx edi, word ptr [esi + 8]
    mov cx, word ptr [ecx + edx]
    and cx, word ptr [edi*4 + 140f544h]
    movzx edx, cx
    mov ecx, dword ptr [eax + 4]
    mov dword ptr [esp + 44h], edx
    cmp ecx, dword ptr [eax + 8]
    _emit 0x73
    _emit 0x55  ; jae 0x79e2a8
    lea edi, [ecx + 2]
    mov dword ptr [eax + 4], edi
    test ecx, ecx
    _emit 0x0f
    _emit 0x84
    _emit 0xbd
    _emit 0x06
    _emit 0x00
    _emit 0x00  ; je 0x79e91e
    mov word ptr [ecx], dx
    _emit 0xe9
    _emit 0xb5
    _emit 0x06
    _emit 0x00
    _emit 0x00  ; jmp 0x79e91e
    mov eax, dword ptr [esp + 10h]
    mov eax, dword ptr [eax + 8]
    cmp eax, 3
    _emit 0x0f
    _emit 0x87
    _emit 0xa5
    _emit 0x06
    _emit 0x00
    _emit 0x00  ; ja 0x79e91e
    jmp dword ptr [eax*4 + 79e93ch]
    _emit 0x0f
    _emit 0xb7
    _emit 0x4e
    _emit 0x0a
    _emit 0x0f
    _emit 0xaf
    _emit 0x4c
    _emit 0x24
    _emit 0x40
    _emit 0x8b
    _emit 0x56
    _emit 0x04
    _emit 0x0f
    _emit 0xb7
    _emit 0x46
    _emit 0x08
    _emit 0x66
    _emit 0x8b
    _emit 0x0c
    _emit 0x11
    _emit 0x66
    _emit 0x23
    _emit 0x0c
    _emit 0x85
    _emit 0x44
    _emit 0xf5
    _emit 0x40
    _emit 0x01
    _emit 0x0f
    _emit 0xb7
    _emit 0xd1
    _emit 0x89
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0xe9
    _emit 0x04
    _emit 0xff
    _emit 0xff
    _emit 0xff  ; data
    lea edx, [esp + 44h]
    push edx
    push ecx
    mov ecx, dword ptr [esp + 50h]
    call EXT_6f5bc0
    _emit 0xe9
    _emit 0x62
    _emit 0x06
    _emit 0x00
    _emit 0x00  ; jmp 0x79e91e
    _emit 0x0f
    _emit 0xb7
    _emit 0x46
    _emit 0x0a
    _emit 0x0f
    _emit 0xaf
    _emit 0x44
    _emit 0x24
    _emit 0x40
    _emit 0x8b
    _emit 0x4e
    _emit 0x04
    _emit 0x0f
    _emit 0xb7
    _emit 0x56
    _emit 0x08
    _emit 0x66
    _emit 0x8b
    _emit 0x04
    _emit 0x08
    _emit 0x66
    _emit 0x23
    _emit 0x04
    _emit 0x95
    _emit 0x44
    _emit 0xf5
    _emit 0x40
    _emit 0x01
    _emit 0x0f
    _emit 0xb7
    _emit 0xc8
    _emit 0x89
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0xe9
    _emit 0xe6
    _emit 0xfd
    _emit 0xff
    _emit 0xff
    _emit 0x0f
    _emit 0xb7
    _emit 0x46
    _emit 0x0a
    _emit 0x0f
    _emit 0xaf
    _emit 0x44
    _emit 0x24
    _emit 0x40
    _emit 0x8b
    _emit 0x4e
    _emit 0x04
    _emit 0x0f
    _emit 0xb7
    _emit 0x56
    _emit 0x08
    _emit 0x0f
    _emit 0xb7
    _emit 0x04
    _emit 0x08
    _emit 0x66
    _emit 0x23
    _emit 0x04
    _emit 0x95
    _emit 0x44
    _emit 0xf5
    _emit 0x40
    _emit 0x01
    _emit 0x83
    _emit 0x7c
    _emit 0x24
    _emit 0x2c
    _emit 0x01
    _emit 0x0f
    _emit 0xb7
    _emit 0xc8
    _emit 0x8d
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x89
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0x52
    _emit 0x7e
    _emit 0x16
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x4c
    _emit 0xe8
    _emit 0x84
    _emit 0x83
    _emit 0xf5
    _emit 0xff
    _emit 0x0f
    _emit 0xb7
    _emit 0x46
    _emit 0x0a
    _emit 0x0f
    _emit 0xaf
    _emit 0xc3
    _emit 0x8b
    _emit 0x5c
    _emit 0x24
    _emit 0x48
    _emit 0xeb
    _emit 0x14
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x50
    _emit 0xe8
    _emit 0x6e
    _emit 0x83
    _emit 0xf5
    _emit 0xff
    _emit 0x0f
    _emit 0xb7
    _emit 0x46
    _emit 0x0a
    _emit 0x0f
    _emit 0xaf
    _emit 0xc3
    _emit 0x8b
    _emit 0x5c
    _emit 0x24
    _emit 0x4c
    _emit 0x8b
    _emit 0x4e
    _emit 0x04
    _emit 0x0f
    _emit 0xb7
    _emit 0x04
    _emit 0x08
    _emit 0x0f
    _emit 0xb7
    _emit 0x56
    _emit 0x08
    _emit 0x66
    _emit 0x23
    _emit 0x04
    _emit 0x95
    _emit 0x44
    _emit 0xf5
    _emit 0x40
    _emit 0x01
    _emit 0x8d
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x0f
    _emit 0xb7
    _emit 0xc8
    _emit 0x89
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0x52
    _emit 0x8b
    _emit 0xcb
    _emit 0xe8
    _emit 0x3d
    _emit 0x83
    _emit 0xf5
    _emit 0xff
    _emit 0x0f
    _emit 0xb7
    _emit 0x46
    _emit 0x0a
    _emit 0x8b
    _emit 0x4e
    _emit 0x04
    _emit 0x0f
    _emit 0xaf
    _emit 0xc7
    _emit 0x0f
    _emit 0xb7
    _emit 0x04
    _emit 0x08
    _emit 0x0f
    _emit 0xb7
    _emit 0x56
    _emit 0x08
    _emit 0x66
    _emit 0x23
    _emit 0x04
    _emit 0x95
    _emit 0x44
    _emit 0xf5
    _emit 0x40
    _emit 0x01
    _emit 0x8d
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x0f
    _emit 0xb7
    _emit 0xc8
    _emit 0x89
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0x52
    _emit 0x8b
    _emit 0xcb
    _emit 0xe8
    _emit 0x10
    _emit 0x83
    _emit 0xf5
    _emit 0xff
    _emit 0xe9
    _emit 0x89
    _emit 0x05
    _emit 0x00
    _emit 0x00
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x50
    _emit 0x8b
    _emit 0x41
    _emit 0x08
    _emit 0x2b
    _emit 0x41
    _emit 0x04
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x54
    _emit 0xc1
    _emit 0xf8
    _emit 0x04
    _emit 0x89
    _emit 0x44
    _emit 0x24
    _emit 0x1c
    _emit 0x8b
    _emit 0x41
    _emit 0x08
    _emit 0x2b
    _emit 0x41
    _emit 0x04
    _emit 0x8b
    _emit 0x4d
    _emit 0x04
    _emit 0xc1
    _emit 0xf8
    _emit 0x04
    _emit 0x83
    _emit 0x7c
    _emit 0x24
    _emit 0x20
    _emit 0x00
    _emit 0x89
    _emit 0x44
    _emit 0x24
    _emit 0x38
    _emit 0x8b
    _emit 0x44
    _emit 0x24
    _emit 0x40
    _emit 0x50
    _emit 0x51
    _emit 0x0f
    _emit 0x84
    _emit 0xe4
    _emit 0x01
    _emit 0x00
    _emit 0x00
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x58
    _emit 0xe8
    _emit 0xdc
    _emit 0xd0
    _emit 0xff
    _emit 0xff
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x10
    _emit 0x83
    _emit 0xc1
    _emit 0x0c
    _emit 0x83
    _emit 0x7c
    _emit 0x24
    _emit 0x24
    _emit 0x00
    _emit 0x0f
    _emit 0x84
    _emit 0xb6
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x8b
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x8b
    _emit 0x44
    _emit 0x24
    _emit 0x14
    _emit 0x52
    _emit 0x50
    _emit 0xe8
    _emit 0xab
    _emit 0xb5
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0x5c
    _emit 0x24
    _emit 0x28
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0x8b
    _emit 0x54
    _emit 0x24
    _emit 0x18
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x14
    _emit 0x52
    _emit 0x83
    _emit 0xc1
    _emit 0x0c
    _emit 0xe8
    _emit 0x91
    _emit 0xb5
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0x5c
    _emit 0x24
    _emit 0x44
    _emit 0x8b
    _emit 0x45
    _emit 0x04
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x50
    _emit 0x53
    _emit 0x50
    _emit 0xe8
    _emit 0x8f
    _emit 0xd0
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0x44
    _emit 0x24
    _emit 0x28
    _emit 0x51
    _emit 0x8b
    _emit 0x4d
    _emit 0x04
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x57
    _emit 0x53
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x60
    _emit 0xe8
    _emit 0xe8
    _emit 0xd0
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0x44
    _emit 0x24
    _emit 0x44
    _emit 0x8b
    _emit 0x54
    _emit 0x24
    _emit 0x40
    _emit 0x8b
    _emit 0x45
    _emit 0x04
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x54
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x57
    _emit 0x52
    _emit 0x50
    _emit 0xe8
    _emit 0xcd
    _emit 0xd0
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0xe8
    _emit 0xd8
    _emit 0x64
    _emit 0x24
    _emit 0x44
    _emit 0x8b
    _emit 0x55
    _emit 0x04
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x5c
    _emit 0x57
    _emit 0x52
    _emit 0xe8
    _emit 0xb0
    _emit 0xd0
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0xe8
    _emit 0xd8
    _emit 0x64
    _emit 0x24
    _emit 0x28
    _emit 0x8b
    _emit 0x45
    _emit 0x04
    _emit 0x51
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x53
    _emit 0x8b
    _emit 0x5c
    _emit 0x24
    _emit 0x5c
    _emit 0x57
    _emit 0x50
    _emit 0x8b
    _emit 0xcb
    _emit 0xe8
    _emit 0x95
    _emit 0xd0
    _emit 0xff
    _emit 0xff
    _emit 0x8b
    _emit 0x4d
    _emit 0x04
    _emit 0x57
    _emit 0x51
    _emit 0x8b
    _emit 0xcb
    _emit 0xe8
    _emit 0x19
    _emit 0xd0
    _emit 0xff
    _emit 0xff
    _emit 0xe9
    _emit 0xe3
    _emit 0x02
    _emit 0x00
    _emit 0x00
    _emit 0x8b
    _emit 0x54
    _emit 0x24
    _emit 0x14
    _emit 0x8b
    _emit 0x44
    _emit 0x24
    _emit 0x18
    _emit 0x52
    _emit 0x50
    _emit 0xe8
    _emit 0xf5
    _emit 0xb4
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0x54
    _emit 0x24
    _emit 0x24
    _emit 0x8b
    _emit 0x55
    _emit 0x04
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x53
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x5c
    _emit 0x52
    _emit 0xe8
    _emit 0x5a
    _emit 0xd0
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0xe8
    _emit 0xd8
    _emit 0x64
    _emit 0x24
    _emit 0x24
    _emit 0x8b
    _emit 0x44
    _emit 0x24
    _emit 0x40
    _emit 0x51
    _emit 0x8b
    _emit 0x4d
    _emit 0x04
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x50
    _emit 0x53
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x64
    _emit 0xe8
    _emit 0x3d
    _emit 0xd0
    _emit 0xff
    _emit 0xff
    _emit 0x8b
    _emit 0x55
    _emit 0x04
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x54
    _emit 0x53
    _emit 0x52
    _emit 0xe8
    _emit 0xbf
    _emit 0xcf
    _emit 0xff
    _emit 0xff
    _emit 0x83
    _emit 0x7c
    _emit 0x24
    _emit 0x28
    _emit 0x00
    _emit 0x74
    _emit 0x5d
    _emit 0x8b
    _emit 0x44
    _emit 0x24
    _emit 0x14
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0x50
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x18
    _emit 0x83
    _emit 0xc1
    _emit 0x0c
    _emit 0xe8
    _emit 0x92
    _emit 0xb4
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x8b
    _emit 0x55
    _emit 0x04
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x54
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x53
    _emit 0x57
    _emit 0x52
    _emit 0xe8
    _emit 0xfb
    _emit 0xcf
    _emit 0xff
    _emit 0xff
    _emit 0x8b
    _emit 0x45
    _emit 0x04
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x50
    _emit 0x57
    _emit 0x50
    _emit 0xe8
    _emit 0x7d
    _emit 0xcf
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0xe8
    _emit 0x51
    _emit 0xd8
    _emit 0x64
    _emit 0x24
    _emit 0x48
    _emit 0x8b
    _emit 0x4d
    _emit 0x04
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x57
    _emit 0x53
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x64
    _emit 0xe8
    _emit 0xd4
    _emit 0xcf
    _emit 0xff
    _emit 0xff
    _emit 0x8b
    _emit 0x5c
    _emit 0x24
    _emit 0x54
    _emit 0xe9
    _emit 0x2a
    _emit 0x02
    _emit 0x00
    _emit 0x00
    _emit 0x8b
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x8b
    _emit 0x44
    _emit 0x24
    _emit 0x18
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x10
    _emit 0x52
    _emit 0x50
    _emit 0x83
    _emit 0xc1
    _emit 0x0c
    _emit 0xe8
    _emit 0x35
    _emit 0xb4
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x8b
    _emit 0x55
    _emit 0x04
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x57
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x5c
    _emit 0x52
    _emit 0xe8
    _emit 0x9a
    _emit 0xcf
    _emit 0xff
    _emit 0xff
    _emit 0x8b
    _emit 0x45
    _emit 0x04
    _emit 0x8b
    _emit 0x5c
    _emit 0x24
    _emit 0x54
    _emit 0x57
    _emit 0x50
    _emit 0x8b
    _emit 0xcb
    _emit 0xe8
    _emit 0x1a
    _emit 0xcf
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0xe8
    _emit 0xd8
    _emit 0x64
    _emit 0x24
    _emit 0x44
    _emit 0x8b
    _emit 0x55
    _emit 0x04
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x51
    _emit 0x57
    _emit 0x52
    _emit 0xe9
    _emit 0xc9
    _emit 0x01
    _emit 0x00
    _emit 0x00
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x5c
    _emit 0xe8
    _emit 0xf8
    _emit 0xce
    _emit 0xff
    _emit 0xff
    _emit 0x83
    _emit 0x7c
    _emit 0x24
    _emit 0x24
    _emit 0x00
    _emit 0x0f
    _emit 0x84
    _emit 0x04
    _emit 0x01
    _emit 0x00
    _emit 0x00
    _emit 0x8b
    _emit 0x54
    _emit 0x24
    _emit 0x18
    _emit 0x8b
    _emit 0x44
    _emit 0x24
    _emit 0x14
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x10
    _emit 0x52
    _emit 0x50
    _emit 0x83
    _emit 0xc1
    _emit 0x0c
    _emit 0xe8
    _emit 0xc7
    _emit 0xb3
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0x54
    _emit 0x24
    _emit 0x24
    _emit 0x8b
    _emit 0x55
    _emit 0x04
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x58
    _emit 0x53
    _emit 0x52
    _emit 0xe8
    _emit 0x2c
    _emit 0xcf
    _emit 0xff
    _emit 0xff
    _emit 0x8b
    _emit 0x45
    _emit 0x04
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x50
    _emit 0x53
    _emit 0x50
    _emit 0xe8
    _emit 0xae
    _emit 0xce
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0xe8
    _emit 0xd8
    _emit 0x64
    _emit 0x24
    _emit 0x24
    _emit 0x8b
    _emit 0x55
    _emit 0x04
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x53
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x60
    _emit 0x52
    _emit 0xe8
    _emit 0x01
    _emit 0xcf
    _emit 0xff
    _emit 0xff
    _emit 0x83
    _emit 0x7c
    _emit 0x24
    _emit 0x28
    _emit 0x00
    _emit 0x74
    _emit 0x48
    _emit 0x8b
    _emit 0x44
    _emit 0x24
    _emit 0x18
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0x50
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x18
    _emit 0x83
    _emit 0xc1
    _emit 0x0c
    _emit 0xe8
    _emit 0x64
    _emit 0xb3
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0x5c
    _emit 0x24
    _emit 0x44
    _emit 0x8b
    _emit 0x55
    _emit 0x04
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x50
    _emit 0x57
    _emit 0x52
    _emit 0xe8
    _emit 0x62
    _emit 0xce
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0x44
    _emit 0x24
    _emit 0x44
    _emit 0x8b
    _emit 0x5c
    _emit 0x24
    _emit 0x40
    _emit 0x8b
    _emit 0x45
    _emit 0x04
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x54
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x53
    _emit 0x57
    _emit 0x50
    _emit 0xe8
    _emit 0xb7
    _emit 0xce
    _emit 0xff
    _emit 0xff
    _emit 0xe9
    _emit 0xc5
    _emit 0xfe
    _emit 0xff
    _emit 0xff
    _emit 0x8b
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x8b
    _emit 0x44
    _emit 0x24
    _emit 0x14
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x10
    _emit 0x52
    _emit 0x50
    _emit 0x83
    _emit 0xc1
    _emit 0x0c
    _emit 0xe8
    _emit 0x1c
    _emit 0xb3
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x51
    _emit 0x8b
    _emit 0x4d
    _emit 0x04
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x57
    _emit 0x53
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x60
    _emit 0xe8
    _emit 0x85
    _emit 0xce
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0xe8
    _emit 0xd8
    _emit 0x64
    _emit 0x24
    _emit 0x44
    _emit 0x8b
    _emit 0x55
    _emit 0x04
    _emit 0x51
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x53
    _emit 0x8b
    _emit 0x5c
    _emit 0x24
    _emit 0x5c
    _emit 0x57
    _emit 0x52
    _emit 0x8b
    _emit 0xcb
    _emit 0xe8
    _emit 0x6a
    _emit 0xce
    _emit 0xff
    _emit 0xff
    _emit 0x8b
    _emit 0x45
    _emit 0x04
    _emit 0x57
    _emit 0x50
    _emit 0x8b
    _emit 0xcb
    _emit 0xe8
    _emit 0xee
    _emit 0xcd
    _emit 0xff
    _emit 0xff
    _emit 0xe9
    _emit 0xb8
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x18
    _emit 0x8b
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x14
    _emit 0x52
    _emit 0x83
    _emit 0xc1
    _emit 0x0c
    _emit 0xe8
    _emit 0xc3
    _emit 0xb2
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0x5c
    _emit 0x24
    _emit 0x28
    _emit 0x8b
    _emit 0x44
    _emit 0x24
    _emit 0x14
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0x50
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x18
    _emit 0x83
    _emit 0xc1
    _emit 0x0c
    _emit 0xe8
    _emit 0xa9
    _emit 0xb2
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0x5c
    _emit 0x24
    _emit 0x44
    _emit 0xd9
    _emit 0x44
    _emit 0x24
    _emit 0x28
    _emit 0x8b
    _emit 0x54
    _emit 0x24
    _emit 0x40
    _emit 0x8b
    _emit 0x45
    _emit 0x04
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x54
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x52
    _emit 0x57
    _emit 0x50
    _emit 0xe8
    _emit 0x0a
    _emit 0xce
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0x44
    _emit 0x24
    _emit 0x44
    _emit 0x51
    _emit 0x8b
    _emit 0x4d
    _emit 0x04
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x53
    _emit 0x57
    _emit 0x51
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x60
    _emit 0xe8
    _emit 0xf3
    _emit 0xcd
    _emit 0xff
    _emit 0xff
    _emit 0x8b
    _emit 0x55
    _emit 0x04
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x50
    _emit 0x57
    _emit 0x52
    _emit 0xe8
    _emit 0x75
    _emit 0xcd
    _emit 0xff
    _emit 0xff
    _emit 0x8b
    _emit 0x45
    _emit 0x04
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x54
    _emit 0x53
    _emit 0x50
    _emit 0xe8
    _emit 0x67
    _emit 0xcd
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0xe8
    _emit 0xd8
    _emit 0x64
    _emit 0x24
    _emit 0x44
    _emit 0x51
    _emit 0x8b
    _emit 0x4d
    _emit 0x04
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x57
    _emit 0x53
    _emit 0x8b
    _emit 0x5c
    _emit 0x24
    _emit 0x60
    _emit 0x51
    _emit 0x8b
    _emit 0xcb
    _emit 0xe8
    _emit 0xbc
    _emit 0xcd
    _emit 0xff
    _emit 0xff
    _emit 0xd9
    _emit 0xe8
    _emit 0xd8
    _emit 0x64
    _emit 0x24
    _emit 0x28
    _emit 0x8b
    _emit 0x54
    _emit 0x24
    _emit 0x40
    _emit 0x8b
    _emit 0x45
    _emit 0x04
    _emit 0x51
    _emit 0xd9
    _emit 0x1c
    _emit 0x24
    _emit 0x57
    _emit 0x52
    _emit 0x50
    _emit 0x8b
    _emit 0xcb
    _emit 0xe8
    _emit 0xa1
    _emit 0xcd
    _emit 0xff
    _emit 0xff
    _emit 0x8b
    _emit 0x7c
    _emit 0x24
    _emit 0x50
    _emit 0x0f
    _emit 0xb7
    _emit 0x4c
    _emit 0x24
    _emit 0x1c
    _emit 0x8b
    _emit 0x47
    _emit 0x30
    _emit 0x8d
    _emit 0x14
    _emit 0x80
    _emit 0x8b
    _emit 0x47
    _emit 0x18
    _emit 0x89
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0x8d
    _emit 0x0c
    _emit 0x90
    _emit 0x8b
    _emit 0x41
    _emit 0x04
    _emit 0x3b
    _emit 0x41
    _emit 0x08
    _emit 0x73
    _emit 0x14
    _emit 0x8d
    _emit 0x50
    _emit 0x02
    _emit 0x89
    _emit 0x51
    _emit 0x04
    _emit 0x85
    _emit 0xc0
    _emit 0x74
    _emit 0x15
    _emit 0x66
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x1c
    _emit 0x66
    _emit 0x89
    _emit 0x08
    _emit 0xeb
    _emit 0x0b
    _emit 0x8d
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x52
    _emit 0x50
    _emit 0xe8
    _emit 0x01
    _emit 0x74
    _emit 0xf5
    _emit 0xff
    _emit 0x8b
    _emit 0x44
    _emit 0x24
    _emit 0x1c
    _emit 0x40
    _emit 0x0f
    _emit 0xb7
    _emit 0xc8
    _emit 0x8b
    _emit 0x47
    _emit 0x30
    _emit 0x8d
    _emit 0x14
    _emit 0x80
    _emit 0x8b
    _emit 0x47
    _emit 0x18
    _emit 0x89
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0x8d
    _emit 0x0c
    _emit 0x90
    _emit 0x8b
    _emit 0x41
    _emit 0x04
    _emit 0x3b
    _emit 0x41
    _emit 0x08
    _emit 0x73
    _emit 0x14
    _emit 0x8d
    _emit 0x50
    _emit 0x02
    _emit 0x89
    _emit 0x51
    _emit 0x04
    _emit 0x85
    _emit 0xc0
    _emit 0x74
    _emit 0x15
    _emit 0x66
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0x66
    _emit 0x89
    _emit 0x08
    _emit 0xeb
    _emit 0x0b
    _emit 0x8d
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x52
    _emit 0x50
    _emit 0xe8
    _emit 0xc2
    _emit 0x73
    _emit 0xf5
    _emit 0xff
    _emit 0x8b
    _emit 0x44
    _emit 0x24
    _emit 0x1c
    _emit 0x8b
    _emit 0x4f
    _emit 0x18
    _emit 0x83
    _emit 0xc0
    _emit 0x02
    _emit 0x0f
    _emit 0xb7
    _emit 0xd0
    _emit 0x8b
    _emit 0x47
    _emit 0x30
    _emit 0x8d
    _emit 0x04
    _emit 0x80
    _emit 0x8d
    _emit 0x0c
    _emit 0x81
    _emit 0x8b
    _emit 0x41
    _emit 0x04
    _emit 0x89
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x3b
    _emit 0x41
    _emit 0x08
    _emit 0x73
    _emit 0x0f
    _emit 0x8d
    _emit 0x78
    _emit 0x02
    _emit 0x89
    _emit 0x79
    _emit 0x04
    _emit 0x85
    _emit 0xc0
    _emit 0x74
    _emit 0x10
    _emit 0x66
    _emit 0x89
    _emit 0x10
    _emit 0xeb
    _emit 0x0b
    _emit 0x8d
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x52
    _emit 0x50
    _emit 0xe8
    _emit 0x86
    _emit 0x73
    _emit 0xf5
    _emit 0xff
    _emit 0x8b
    _emit 0x7c
    _emit 0x24
    _emit 0x38
    _emit 0x8b
    _emit 0x53
    _emit 0x18
    _emit 0x0f
    _emit 0xb7
    _emit 0xc7
    _emit 0x89
    _emit 0x44
    _emit 0x24
    _emit 0x44
    _emit 0x8b
    _emit 0x43
    _emit 0x30
    _emit 0x8d
    _emit 0x0c
    _emit 0x80
    _emit 0x8b
    _emit 0x44
    _emit 0x8a
    _emit 0x04
    _emit 0x3b
    _emit 0x44
    _emit 0x8a
    _emit 0x08
    _emit 0x8d
    _emit 0x0c
    _emit 0x8a
    _emit 0x73
    _emit 0x0f
    _emit 0x8d
    _emit 0x50
    _emit 0x02
    _emit 0x89
    _emit 0x51
    _emit 0x04
    _emit 0x85
    _emit 0xc0
    _emit 0x74
    _emit 0x10
    _emit 0x66
    _emit 0x89
    _emit 0x38
    _emit 0xeb
    _emit 0x0b
    _emit 0x8d
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x52
    _emit 0x50
    _emit 0xe8
    _emit 0x4b
    _emit 0x73
    _emit 0xf5
    _emit 0xff
    _emit 0x8d
    _emit 0x47
    _emit 0x01
    _emit 0x0f
    _emit 0xb7
    _emit 0xc8
    _emit 0x8b
    _emit 0x43
    _emit 0x30
    _emit 0x8d
    _emit 0x14
    _emit 0x80
    _emit 0x8b
    _emit 0x43
    _emit 0x18
    _emit 0x89
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0x8d
    _emit 0x0c
    _emit 0x90
    _emit 0x8b
    _emit 0x41
    _emit 0x04
    _emit 0x3b
    _emit 0x41
    _emit 0x08
    _emit 0x73
    _emit 0x14
    _emit 0x8d
    _emit 0x50
    _emit 0x02
    _emit 0x89
    _emit 0x51
    _emit 0x04
    _emit 0x85
    _emit 0xc0
    _emit 0x74
    _emit 0x15
    _emit 0x66
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0x66
    _emit 0x89
    _emit 0x08
    _emit 0xeb
    _emit 0x0b
    _emit 0x8d
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x52
    _emit 0x50
    _emit 0xe8
    _emit 0x0e
    _emit 0x73
    _emit 0xf5
    _emit 0xff
    _emit 0x8b
    _emit 0x53
    _emit 0x18
    _emit 0x8d
    _emit 0x47
    _emit 0x02
    _emit 0x0f
    _emit 0xb7
    _emit 0xc0
    _emit 0x89
    _emit 0x44
    _emit 0x24
    _emit 0x44
    _emit 0x8b
    _emit 0x43
    _emit 0x30
    _emit 0x8d
    _emit 0x0c
    _emit 0x80
    _emit 0x8b
    _emit 0x44
    _emit 0x8a
    _emit 0x04
    _emit 0x3b
    _emit 0x44
    _emit 0x8a
    _emit 0x08
    _emit 0x8d
    _emit 0x0c
    _emit 0x8a
    _emit 0x73
    _emit 0x14
    _emit 0x8d
    _emit 0x50
    _emit 0x02
    _emit 0x89
    _emit 0x51
    _emit 0x04
    _emit 0x85
    _emit 0xc0
    _emit 0x74
    _emit 0x15
    _emit 0x66
    _emit 0x8b
    _emit 0x4c
    _emit 0x24
    _emit 0x44
    _emit 0x66
    _emit 0x89
    _emit 0x08
    _emit 0xeb
    _emit 0x0b
    _emit 0x8d
    _emit 0x54
    _emit 0x24
    _emit 0x44
    _emit 0x52
    _emit 0x50
    _emit 0xe8
    _emit 0xcf
    _emit 0x72
    _emit 0xf5
    _emit 0xff
    _emit 0x83
    _emit 0x7c
    _emit 0x24
    _emit 0x2c
    _emit 0x01
    _emit 0x7e
    _emit 0x08
    _emit 0x8b
    _emit 0x7c
    _emit 0x24
    _emit 0x1c
    _emit 0x8b
    _emit 0x5c
    _emit 0x24
    _emit 0x50
    _emit 0x57
    _emit 0x8b
    _emit 0xcb
    _emit 0xe8
    _emit 0x88
    _emit 0xcc
    _emit 0xff
    _emit 0xff
    _emit 0x8d
    _emit 0x47
    _emit 0x02
    _emit 0x50
    _emit 0x8b
    _emit 0xcb
    _emit 0xe8
    _emit 0x7d
    _emit 0xcc
    _emit 0xff
    _emit 0xff
    _emit 0x83
    _emit 0xc7
    _emit 0x03
    _emit 0x57
    _emit 0x8b
    _emit 0xcb
    _emit 0xe8
    _emit 0x72
    _emit 0xcc
    _emit 0xff
    _emit 0xff  ; data
    mov eax, dword ptr [esp + 40h]
    add eax, 3
    cmp eax, dword ptr [ebp + 0ch]
    mov dword ptr [esp + 40h], eax
    _emit 0x0f
    _emit 0x8c
    _emit 0x00
    _emit 0xf4
    _emit 0xff
    _emit 0xff  ; jl 0x79dd32
    pop ebx
    pop edi
    pop esi
    pop ebp
    add esp, 2ch
    ret 18h
    _emit 0x80
    _emit 0xe2
    _emit 0x79
    _emit 0x00
    _emit 0xbc
    _emit 0xe2
    _emit 0x79
    _emit 0x00
    _emit 0xe4
    _emit 0xe2
    _emit 0x79
    _emit 0x00
    _emit 0x95
    _emit 0xe3
    _emit 0x79
    _emit 0x00  ; data
  }
}


