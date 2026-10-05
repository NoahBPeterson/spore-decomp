// slice s0079d190
// Per-instruction reconstruction (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
// Control flow is decoded recursively; call targets are symbolic so COFF
// relocation bytes are masked by the verifier. Unreachable bytes are data.

extern "C" void EXT_6f5bc0();
extern "C" void EXT_71ddc0();

// @ 0x0079d190
__declspec(naked) void FUN_0079d190() {
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
    _emit 0xe5
    _emit 0x0a
    _emit 0x00
    _emit 0x00  ; jge 0x79dcc6
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
    _emit 0x00  ; je 0x79d2d0
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
    _emit 0x3f  ; jmp 0x79d30f
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
    add eax, ecx
    mov dword ptr [esp + 20h], ecx
    mov ecx, dword ptr [esp + 44h]
    imul ecx, edx
    add ecx, dword ptr [esp + 20h]
    mov edx, dword ptr [esp + 10h]
    movss xmm0, dword ptr [edx + 14h]
    mulss xmm0, dword ptr [eax + 8]
    movss xmm1, dword ptr [edx + 10h]
    mulss xmm1, dword ptr [eax + 4]
    mov dword ptr [esp + 14h], ecx
    mov ecx, dword ptr [esp + 44h]
    imul ecx, dword ptr [esp + 28h]
    add ecx, dword ptr [esp + 20h]
    add edx, 0ch
    addss xmm0, xmm1
    movss xmm1, dword ptr [edx]
    mulss xmm1, dword ptr [eax]
    addss xmm0, xmm1
    comiss xmm0, dword ptr [edx + 0ch]
    mov dword ptr [esp + 18h], eax
    mov dword ptr [esp + 44h], ecx
    mov dword ptr [esp + 2ch], edx
    mov dword ptr [esp + 20h], 1
    _emit 0x77
    _emit 0x08  ; ja 0x79d396
    mov dword ptr [esp + 20h], 0
    mov eax, dword ptr [esp + 14h]
    movss xmm0, dword ptr [edx + 8]
    mulss xmm0, dword ptr [eax + 8]
    movss xmm1, dword ptr [edx + 4]
    mulss xmm1, dword ptr [eax + 4]
    addss xmm0, xmm1
    movss xmm1, dword ptr [edx]
    mulss xmm1, dword ptr [eax]
    addss xmm0, xmm1
    comiss xmm0, dword ptr [edx + 0ch]
    _emit 0x76
    _emit 0x07  ; jbe 0x79d3cb
    mov edx, 1
    _emit 0xeb
    _emit 0x02  ; jmp 0x79d3cd
    xor edx, edx
    mov eax, dword ptr [esp + 2ch]
    movss xmm0, dword ptr [eax + 8]
    mulss xmm0, dword ptr [ecx + 8]
    movss xmm1, dword ptr [eax + 4]
    mulss xmm1, dword ptr [ecx + 4]
    addss xmm0, xmm1
    movss xmm1, dword ptr [ecx]
    mulss xmm1, dword ptr [eax]
    addss xmm0, xmm1
    comiss xmm0, dword ptr [eax + 0ch]
    mov dword ptr [esp + 24h], edx
    _emit 0x76
    _emit 0x07  ; jbe 0x79d406
    mov eax, 1
    _emit 0xeb
    _emit 0x02  ; jmp 0x79d408
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
    _emit 0x00  ; jne 0x79d5fc
    cmp dword ptr [esp + 20h], ecx
    _emit 0x0f
    _emit 0x85
    _emit 0xe2
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; jne 0x79d51c
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
    _emit 0x14  ; jae 0x79d47d
    lea edx, [ecx + 2]
    mov dword ptr [eax + 4], edx
    test ecx, ecx
    _emit 0x74
    _emit 0x1d  ; je 0x79d490
    mov dx, word ptr [esp + 44h]
    mov word ptr [ecx], dx
    _emit 0xeb
    _emit 0x13  ; jmp 0x79d490
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
    _emit 0x0f  ; jae 0x79d4c8
    lea ebx, [ecx + 2]
    mov dword ptr [eax + 4], ebx
    test ecx, ecx
    _emit 0x74
    _emit 0x18  ; je 0x79d4db
    mov word ptr [ecx], dx
    _emit 0xeb
    _emit 0x13  ; jmp 0x79d4db
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
    _emit 0x00  ; jb 0x79d5e6
    lea edx, [esp + 44h]
    push edx
    push ecx
    mov ecx, dword ptr [esp + 54h]
    call EXT_6f5bc0
    _emit 0xe9
    _emit 0x95
    _emit 0x07
    _emit 0x00
    _emit 0x00  ; jmp 0x79dcb1
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
    _emit 0x14  ; jae 0x79d55f
    lea edx, [ecx + 2]
    mov dword ptr [eax + 4], edx
    test ecx, ecx
    _emit 0x74
    _emit 0x1d  ; je 0x79d572
    mov dx, word ptr [esp + 44h]
    mov word ptr [ecx], dx
    _emit 0xeb
    _emit 0x13  ; jmp 0x79d572
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
    _emit 0x0f  ; jae 0x79d5aa
    lea ebx, [ecx + 2]
    mov dword ptr [eax + 4], ebx
    test ecx, ecx
    _emit 0x74
    _emit 0x18  ; je 0x79d5bd
    mov word ptr [ecx], dx
    _emit 0xeb
    _emit 0x13  ; jmp 0x79d5bd
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
    _emit 0x55  ; jae 0x79d63b
    lea edi, [ecx + 2]
    mov dword ptr [eax + 4], edi
    test ecx, ecx
    _emit 0x0f
    _emit 0x84
    _emit 0xbd
    _emit 0x06
    _emit 0x00
    _emit 0x00  ; je 0x79dcb1
    mov word ptr [ecx], dx
    _emit 0xe9
    _emit 0xb5
    _emit 0x06
    _emit 0x00
    _emit 0x00  ; jmp 0x79dcb1
    mov eax, dword ptr [esp + 10h]
    mov eax, dword ptr [eax + 8]
    cmp eax, 3
    _emit 0x0f
    _emit 0x87
    _emit 0xa5
    _emit 0x06
    _emit 0x00
    _emit 0x00  ; ja 0x79dcb1
    jmp dword ptr [eax*4 + 79dcd0h]
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
    _emit 0x00  ; jmp 0x79dcb1
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
    _emit 0xf1
    _emit 0x8f
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
    _emit 0xdb
    _emit 0x8f
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
    _emit 0xaa
    _emit 0x8f
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
    _emit 0x7d
    _emit 0x8f
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
    _emit 0x49
    _emit 0xdd
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
    _emit 0x18
    _emit 0xc1
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
    _emit 0xfe
    _emit 0xc0
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
    _emit 0xfc
    _emit 0xdc
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
    _emit 0x55
    _emit 0xdd
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
    _emit 0x3a
    _emit 0xdd
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
    _emit 0x1d
    _emit 0xdd
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
    _emit 0x02
    _emit 0xdd
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
    _emit 0x86
    _emit 0xdc
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
    _emit 0x62
    _emit 0xc0
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
    _emit 0xc7
    _emit 0xdc
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
    _emit 0xaa
    _emit 0xdc
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
    _emit 0x2c
    _emit 0xdc
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
    _emit 0xff
    _emit 0xbf
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
    _emit 0x68
    _emit 0xdc
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
    _emit 0xea
    _emit 0xdb
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
    _emit 0x41
    _emit 0xdc
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
    _emit 0xa2
    _emit 0xbf
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
    _emit 0x07
    _emit 0xdc
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
    _emit 0x87
    _emit 0xdb
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
    _emit 0x65
    _emit 0xdb
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
    _emit 0x34
    _emit 0xbf
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
    _emit 0x99
    _emit 0xdb
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
    _emit 0x1b
    _emit 0xdb
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
    _emit 0x6e
    _emit 0xdb
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
    _emit 0xd1
    _emit 0xbe
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
    _emit 0xcf
    _emit 0xda
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
    _emit 0x24
    _emit 0xdb
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
    _emit 0x89
    _emit 0xbe
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
    _emit 0xf2
    _emit 0xda
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
    _emit 0xd7
    _emit 0xda
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
    _emit 0x5b
    _emit 0xda
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
    _emit 0x30
    _emit 0xbe
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
    _emit 0x16
    _emit 0xbe
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
    _emit 0x77
    _emit 0xda
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
    _emit 0x60
    _emit 0xda
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
    _emit 0xe2
    _emit 0xd9
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
    _emit 0xd4
    _emit 0xd9
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
    _emit 0x29
    _emit 0xda
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
    _emit 0x0e
    _emit 0xda
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
    _emit 0x6e
    _emit 0x80
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
    _emit 0x2f
    _emit 0x80
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
    _emit 0xf3
    _emit 0x7f
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
    _emit 0xb8
    _emit 0x7f
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
    _emit 0x7b
    _emit 0x7f
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
    _emit 0x3c
    _emit 0x7f
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
    _emit 0xf5
    _emit 0xd8
    _emit 0xff
    _emit 0xff
    _emit 0x8d
    _emit 0x47
    _emit 0x02
    _emit 0x50
    _emit 0x8b
    _emit 0xcb
    _emit 0xe8
    _emit 0xea
    _emit 0xd8
    _emit 0xff
    _emit 0xff
    _emit 0x83
    _emit 0xc7
    _emit 0x03
    _emit 0x57
    _emit 0x8b
    _emit 0xcb
    _emit 0xe8
    _emit 0xdf
    _emit 0xd8
    _emit 0xff
    _emit 0xff  ; data
    mov eax, dword ptr [esp + 40h]
    add eax, 3
    cmp eax, dword ptr [ebp + 0ch]
    mov dword ptr [esp + 40h], eax
    _emit 0x0f
    _emit 0x8c
    _emit 0x1d
    _emit 0xf5
    _emit 0xff
    _emit 0xff  ; jl 0x79d1e2
    pop ebx
    pop edi
    pop esi
    pop ebp
    add esp, 2ch
    ret 18h
    _emit 0x90
    _emit 0x13
    _emit 0xd6
    _emit 0x79
    _emit 0x00
    _emit 0x4f
    _emit 0xd6
    _emit 0x79
    _emit 0x00
    _emit 0x77
    _emit 0xd6
    _emit 0x79
    _emit 0x00
    _emit 0x28
    _emit 0xd7
    _emit 0x79
    _emit 0x00  ; data
  }
}


