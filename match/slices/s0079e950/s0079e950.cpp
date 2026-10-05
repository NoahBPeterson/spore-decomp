// slice s0079e950
// Per-instruction reconstruction (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
// Control flow is decoded recursively; call targets are symbolic so COFF
// relocation bytes are masked by the verifier. Unreachable bytes are data.

extern "C" void EXT_6c1570();
extern "C" void EXT_6f5bc0();
extern "C" void EXT_71ddc0();
extern "C" void EXT_762d70();
extern "C" void EXT_799290();
extern "C" void EXT_7992e0();
extern "C" void EXT_799d60();
extern "C" void EXT_799e00();
extern "C" void EXT_8dede0();
extern "C" void EXT_8dee30();
extern "C" void EXT_8def80();
extern "C" void EXT_8defe0();
extern "C" void EXT_f47380();
extern "C" void EXT_f473a0();

// @ 0x0079e950
__declspec(naked) void FUN_0079e950() {
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
    _emit 0x25
    _emit 0x0b
    _emit 0x00
    _emit 0x00  ; jge 0x79f4c6
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
    _emit 0x00  ; je 0x79ea90
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
    _emit 0x3f  ; jmp 0x79eacf
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
    movss xmm1, dword ptr [eax + 4]
    mov dword ptr [esp + 20h], ecx
    mov ecx, dword ptr [esp + 44h]
    movss xmm0, dword ptr [eax]
    imul ecx, edx
    add ecx, dword ptr [esp + 20h]
    mov edx, dword ptr [esp + 10h]
    subss xmm1, dword ptr [edx + 10h]
    subss xmm0, dword ptr [edx + 0ch]
    movss xmm2, dword ptr [eax + 8]
    subss xmm2, dword ptr [edx + 14h]
    mov dword ptr [esp + 14h], ecx
    mov ecx, dword ptr [esp + 44h]
    imul ecx, dword ptr [esp + 28h]
    add ecx, dword ptr [esp + 20h]
    add edx, 0ch
    movaps xmm3, xmm1
    mulss xmm3, xmm1
    movaps xmm1, xmm0
    mulss xmm1, xmm0
    movaps xmm0, xmm2
    addss xmm3, xmm1
    mulss xmm0, xmm2
    addss xmm3, xmm0
    comiss xmm3, dword ptr [edx + 0ch]
    mov dword ptr [esp + 18h], eax
    mov dword ptr [esp + 44h], ecx
    mov dword ptr [esp + 2ch], edx
    mov dword ptr [esp + 20h], 1
    _emit 0x77
    _emit 0x08  ; ja 0x79eb6c
    mov dword ptr [esp + 20h], 0
    mov eax, dword ptr [esp + 14h]
    movss xmm0, dword ptr [eax]
    subss xmm0, dword ptr [edx]
    movss xmm2, dword ptr [eax + 8]
    subss xmm2, dword ptr [edx + 8]
    movss xmm1, dword ptr [eax + 4]
    subss xmm1, dword ptr [edx + 4]
    movaps xmm3, xmm0
    mulss xmm3, xmm0
    movaps xmm0, xmm2
    mulss xmm0, xmm2
    addss xmm3, xmm0
    movaps xmm0, xmm1
    mulss xmm0, xmm1
    addss xmm3, xmm0
    comiss xmm3, dword ptr [edx + 0ch]
    _emit 0x76
    _emit 0x07  ; jbe 0x79ebb6
    mov edx, 1
    _emit 0xeb
    _emit 0x02  ; jmp 0x79ebb8
    xor edx, edx
    mov eax, dword ptr [esp + 2ch]
    movss xmm2, dword ptr [ecx + 8]
    subss xmm2, dword ptr [eax + 8]
    movss xmm1, dword ptr [ecx + 4]
    subss xmm1, dword ptr [eax + 4]
    movss xmm0, dword ptr [ecx]
    subss xmm0, dword ptr [eax]
    movaps xmm3, xmm2
    mulss xmm3, xmm2
    movaps xmm2, xmm1
    mulss xmm2, xmm1
    movaps xmm1, xmm0
    addss xmm3, xmm2
    mulss xmm1, xmm0
    addss xmm3, xmm1
    comiss xmm3, dword ptr [eax + 0ch]
    mov dword ptr [esp + 24h], edx
    _emit 0x76
    _emit 0x07  ; jbe 0x79ec06
    mov eax, 1
    _emit 0xeb
    _emit 0x02  ; jmp 0x79ec08
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
    _emit 0x00  ; jne 0x79edfc
    cmp dword ptr [esp + 20h], ecx
    _emit 0x0f
    _emit 0x85
    _emit 0xe2
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; jne 0x79ed1c
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
    _emit 0x14  ; jae 0x79ec7d
    lea edx, [ecx + 2]
    mov dword ptr [eax + 4], edx
    test ecx, ecx
    _emit 0x74
    _emit 0x1d  ; je 0x79ec90
    mov dx, word ptr [esp + 44h]
    mov word ptr [ecx], dx
    _emit 0xeb
    _emit 0x13  ; jmp 0x79ec90
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
    _emit 0x0f  ; jae 0x79ecc8
    lea ebx, [ecx + 2]
    mov dword ptr [eax + 4], ebx
    test ecx, ecx
    _emit 0x74
    _emit 0x18  ; je 0x79ecdb
    mov word ptr [ecx], dx
    _emit 0xeb
    _emit 0x13  ; jmp 0x79ecdb
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
    _emit 0x00  ; jb 0x79ede6
    lea edx, [esp + 44h]
    push edx
    push ecx
    mov ecx, dword ptr [esp + 54h]
    call EXT_6f5bc0
    _emit 0xe9
    _emit 0x95
    _emit 0x07
    _emit 0x00
    _emit 0x00  ; jmp 0x79f4b1
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
    _emit 0x14  ; jae 0x79ed5f
    lea edx, [ecx + 2]
    mov dword ptr [eax + 4], edx
    test ecx, ecx
    _emit 0x74
    _emit 0x1d  ; je 0x79ed72
    mov dx, word ptr [esp + 44h]
    mov word ptr [ecx], dx
    _emit 0xeb
    _emit 0x13  ; jmp 0x79ed72
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
    _emit 0x0f  ; jae 0x79edaa
    lea ebx, [ecx + 2]
    mov dword ptr [eax + 4], ebx
    test ecx, ecx
    _emit 0x74
    _emit 0x18  ; je 0x79edbd
    mov word ptr [ecx], dx
    _emit 0xeb
    _emit 0x13  ; jmp 0x79edbd
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
    _emit 0x55  ; jae 0x79ee3b
    lea edi, [ecx + 2]
    mov dword ptr [eax + 4], edi
    test ecx, ecx
    _emit 0x0f
    _emit 0x84
    _emit 0xbd
    _emit 0x06
    _emit 0x00
    _emit 0x00  ; je 0x79f4b1
    mov word ptr [ecx], dx
    _emit 0xe9
    _emit 0xb5
    _emit 0x06
    _emit 0x00
    _emit 0x00  ; jmp 0x79f4b1
    mov eax, dword ptr [esp + 10h]
    mov eax, dword ptr [eax + 8]
    cmp eax, 3
    _emit 0x0f
    _emit 0x87
    _emit 0xa5
    _emit 0x06
    _emit 0x00
    _emit 0x00  ; ja 0x79f4b1
    jmp dword ptr [eax*4 + 79f4d0h]
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
    _emit 0x00  ; jmp 0x79f4b1
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
    _emit 0x77
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
    _emit 0x77
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
    _emit 0x77
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
    _emit 0x77
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
    _emit 0xc5
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
    _emit 0xc8
    _emit 0xab
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
    _emit 0xae
    _emit 0xab
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
    _emit 0xc4
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
    _emit 0xc5
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
    _emit 0xc5
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
    _emit 0xc5
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
    _emit 0xc5
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
    _emit 0xc4
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
    _emit 0x12
    _emit 0xab
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
    _emit 0xc4
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
    _emit 0xc4
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
    _emit 0xc4
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
    _emit 0xaf
    _emit 0xaa
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
    _emit 0xc4
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
    _emit 0xc3
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
    _emit 0xc4
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
    _emit 0x52
    _emit 0xaa
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
    _emit 0xc4
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
    _emit 0xc3
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
    _emit 0xc3
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
    _emit 0xe4
    _emit 0xa9
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
    _emit 0xc3
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
    _emit 0xc3
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
    _emit 0xc3
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
    _emit 0x81
    _emit 0xa9
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
    _emit 0xc2
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
    _emit 0xc3
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
    _emit 0x39
    _emit 0xa9
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
    _emit 0xc2
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
    _emit 0xc2
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
    _emit 0xc2
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
    _emit 0xe0
    _emit 0xa8
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
    _emit 0xc6
    _emit 0xa8
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
    _emit 0xc2
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
    _emit 0xc2
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
    _emit 0xc1
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
    _emit 0xc1
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
    _emit 0xc2
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
    _emit 0xc2
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
    _emit 0x68
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
    _emit 0x68
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
    _emit 0x67
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
    _emit 0x67
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
    _emit 0x67
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
    _emit 0x67
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
    _emit 0xc0
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
    _emit 0xc0
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
    _emit 0xc0
    _emit 0xff
    _emit 0xff  ; data
    mov eax, dword ptr [esp + 40h]
    add eax, 3
    cmp eax, dword ptr [ebp + 0ch]
    mov dword ptr [esp + 40h], eax
    _emit 0x0f
    _emit 0x8c
    _emit 0xdd
    _emit 0xf4
    _emit 0xff
    _emit 0xff  ; jl 0x79e9a2
    pop ebx
    pop edi
    pop esi
    pop ebp
    add esp, 2ch
    ret 18h
    _emit 0x90
    _emit 0x13
    _emit 0xee
    _emit 0x79
    _emit 0x00
    _emit 0x4f
    _emit 0xee
    _emit 0x79
    _emit 0x00
    _emit 0x77
    _emit 0xee
    _emit 0x79
    _emit 0x00
    _emit 0x28
    _emit 0xef
    _emit 0x79
    _emit 0x00  ; data
  }
}

// @ 0x0079f4e0
__declspec(naked) void FUN_0079f4e0() {
  __asm {
    sub esp, 8
    push ebx
    push esi
    mov esi, ecx
    mov eax, dword ptr [esi + 4]
    push edi
    cmp eax, dword ptr [esi + 8]
    _emit 0x74
    _emit 0x5a  ; je 0x79f54a
    mov ecx, dword ptr [esp + 1ch]
    mov edi, dword ptr [esp + 18h]
    mov ebx, ecx
    cmp ecx, edi
    _emit 0x72
    _emit 0x07  ; jb 0x79f505
    cmp ecx, eax
    _emit 0x73
    _emit 0x03  ; jae 0x79f505
    lea ebx, [ecx + 8]
    test eax, eax
    _emit 0x74
    _emit 0x1b  ; je 0x79f524
    mov ecx, dword ptr [eax - 8]
    mov dword ptr [eax], ecx
    test ecx, ecx
    _emit 0x74
    _emit 0x0c  ; je 0x79f51e
    add ecx, 4
    mov edx, 1
    lock xadd dword ptr [ecx], edx
    mov ecx, dword ptr [eax - 4]
    mov dword ptr [eax + 4], ecx
    mov eax, dword ptr [esi + 4]
    push eax
    add eax, -8
    push eax
    push edi
    call EXT_799e00
    add esp, 0ch
    push ebx
    mov ecx, edi
    call EXT_8dee30
    add dword ptr [esi + 4], 8
    pop edi
    pop esi
    pop ebx
    add esp, 8
    ret 8
    sub eax, dword ptr [esi]
    sar eax, 3
    test eax, eax
    _emit 0x76
    _emit 0x33  ; jbe 0x79f586
    add eax, eax
    mov dword ptr [esp + 10h], eax
    test eax, eax
    _emit 0x74
    _emit 0x37  ; je 0x79f594
    push 0d1h
    push 13ebb38h
    push 0
    push 0
    lea edx, [eax*8]
    push 13eb8a4h
    push edx
    call EXT_f473a0
    add esp, 18h
    mov dword ptr [esp + 0ch], eax
    _emit 0xeb
    _emit 0x16  ; jmp 0x79f59c
    mov dword ptr [esp + 10h], 1
    mov eax, dword ptr [esp + 10h]
    _emit 0xeb
    _emit 0xc9  ; jmp 0x79f55d
    mov dword ptr [esp + 0ch], 0
    mov eax, dword ptr [esp + 0ch]
    mov ebx, dword ptr [esi]
    push ebp
    mov ebp, dword ptr [esp + 1ch]
    push eax
    push ebp
    push ebx
    call EXT_7992e0
    mov ecx, dword ptr [esp + 1ch]
    push ecx
    push ebp
    push ebx
    mov edi, eax
    call EXT_8def80
    add esp, 18h
    test edi, edi
    _emit 0x74
    _emit 0x1e  ; je 0x79f5e2
    mov ecx, dword ptr [esp + 20h]
    mov eax, dword ptr [ecx]
    mov dword ptr [edi], eax
    test eax, eax
    _emit 0x74
    _emit 0x0c  ; je 0x79f5dc
    add eax, 4
    mov edx, 1
    lock xadd dword ptr [eax], edx
    mov eax, dword ptr [ecx + 4]
    mov dword ptr [edi + 4], eax
    mov ebx, dword ptr [esi + 4]
    add edi, 8
    push edi
    push ebx
    push ebp
    call EXT_7992e0
    push edi
    push ebx
    push ebp
    mov dword ptr [esp + 34h], eax
    call EXT_8def80
    mov eax, dword ptr [esi]
    add esp, 18h
    pop ebp
    test eax, eax
    _emit 0x74
    _emit 0x0f  ; je 0x79f615
    cmp dword ptr [eax - 4], 0
    _emit 0x74
    _emit 0x09  ; je 0x79f615
    push eax
    call EXT_f47380
    add esp, 4
    mov eax, dword ptr [esp + 0ch]
    mov edx, dword ptr [esp + 10h]
    mov ecx, dword ptr [esp + 18h]
    mov dword ptr [esi], eax
    lea eax, [eax + edx*8]
    pop edi
    mov dword ptr [esi + 4], ecx
    mov dword ptr [esi + 8], eax
    pop esi
    pop ebx
    add esp, 8
    ret 8
  }
}

// @ 0x0079f640
__declspec(naked) void FUN_0079f640() {
  __asm {
    push ebx
    mov ebx, dword ptr [esp + 8]
    push esi
    mov esi, ecx
    cmp ebx, esi
    _emit 0x0f
    _emit 0x84
    _emit 0xd3
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; je 0x79f723
    mov eax, dword ptr [ebx]
    mov ecx, dword ptr [esi]
    mov edx, dword ptr [esi + 8]
    push ebp
    mov ebp, dword ptr [ebx + 4]
    push edi
    mov edi, ebp
    sub edi, eax
    sub edx, ecx
    sar edi, 3
    sar edx, 3
    cmp edi, edx
    _emit 0x76
    _emit 0x48  ; jbe 0x79f6b4
    push ebp
    push eax
    push edi
    mov ecx, esi
    call EXT_799d60
    mov ecx, dword ptr [esi]
    mov ebx, eax
    mov eax, dword ptr [esi + 4]
    push eax
    push ecx
    mov ecx, esi
    call EXT_8dede0
    mov eax, dword ptr [esi]
    test eax, eax
    _emit 0x74
    _emit 0x0f  ; je 0x79f69b
    cmp dword ptr [eax - 4], 0
    _emit 0x74
    _emit 0x09  ; je 0x79f69b
    push eax
    call EXT_f47380
    add esp, 4
    lea edx, [ebx + edi*8]
    mov dword ptr [esi + 8], edx
    mov edx, ebx
    lea eax, [edx + edi*8]
    pop edi
    mov dword ptr [esi + 4], eax
    pop ebp
    mov dword ptr [esi], ebx
    mov eax, esi
    pop esi
    pop ebx
    ret 4
    mov edx, dword ptr [esi + 4]
    sub edx, ecx
    sar edx, 3
    push ecx
    cmp edi, edx
    _emit 0x76
    _emit 0x42  ; jbe 0x79f703
    lea ecx, [eax + edx*8]
    push ecx
    push eax
    call EXT_8defe0
    mov eax, dword ptr [esi + 4]
    mov ecx, dword ptr [ebx + 4]
    mov ebx, dword ptr [ebx]
    mov edx, eax
    sub edx, dword ptr [esi]
    sar edx, 3
    lea edx, [ebx + edx*8]
    mov ebx, dword ptr [esp + 20h]
    push ebx
    push eax
    push ecx
    push edx
    lea eax, [esp + 30h]
    push eax
    call EXT_799290
    mov edx, dword ptr [esi]
    add esp, 20h
    lea eax, [edx + edi*8]
    pop edi
    mov dword ptr [esi + 4], eax
    pop ebp
    mov eax, esi
    pop esi
    pop ebx
    ret 4
    push ebp
    push eax
    call EXT_8defe0
    mov ecx, dword ptr [esi + 4]
    add esp, 0ch
    push ecx
    push eax
    mov ecx, esi
    call EXT_8dede0
    mov edx, dword ptr [esi]
    lea eax, [edx + edi*8]
    pop edi
    mov dword ptr [esi + 4], eax
    pop ebp
    mov eax, esi
    pop esi
    pop ebx
    ret 4
  }
}

// @ 0x0079f7b0
__declspec(naked) void FUN_0079f7b0() {
  __asm {
    push -1
    push 1213b9bh
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
    sub esp, 118h
    lea eax, [esp + 18h]
    push ebx
    push esi
    mov ecx, eax
    lea edx, [esp + 120h]
    push edi
    mov dword ptr [esp + 1ch], eax
    mov dword ptr [esp + 10h], eax
    mov dword ptr [esp + 0ch], ecx
    mov dword ptr [esp + 14h], edx
    mov esi, dword ptr [esp + 134h]
    mov edi, dword ptr [esi + 4]
    sub edi, dword ptr [esi]
    xor ebx, ebx
    sar edi, 3
    mov dword ptr [esp + 12ch], 0
    test edi, edi
    _emit 0x7e
    _emit 0x4a  ; jle 0x79f855
    _emit 0xeb
    _emit 0x03  ; jmp 0x79f810
    _emit 0x8d
    _emit 0x49
    _emit 0x00  ; data
    mov ecx, dword ptr [esi]
    cmp dword ptr [ecx + ebx*8], 0
    lea edx, [ecx + ebx*8]
    _emit 0x74
    _emit 0x31  ; je 0x79f84c
    cmp eax, dword ptr [esp + 14h]
    _emit 0x73
    _emit 0x13  ; jae 0x79f834
    mov ecx, eax
    add eax, 4
    mov dword ptr [esp + 10h], eax
    test ecx, ecx
    _emit 0x74
    _emit 0x11  ; je 0x79f83f
    mov edx, dword ptr [edx]
    mov dword ptr [ecx], edx
    _emit 0xeb
    _emit 0x0b  ; jmp 0x79f83f
    push edx
    push eax
    lea ecx, [esp + 14h]
    call EXT_6c1570
    mov eax, dword ptr [esi]
    mov dword ptr [eax + ebx*8], 0
    mov eax, dword ptr [esp + 10h]
    inc ebx
    cmp ebx, edi
    _emit 0x7c
    _emit 0xbf  ; jl 0x79f810
    mov ecx, dword ptr [esp + 0ch]
    sub eax, ecx
    push ecx
    sar eax, 2
    push eax
    call EXT_762d70
    mov eax, dword ptr [esi + 4]
    mov edi, dword ptr [esi]
    add esp, 8
    mov edx, edi
    mov ecx, eax
    cmp eax, eax
    _emit 0x74
    _emit 0x14  ; je 0x79f885
    mov ebx, dword ptr [ecx]
    mov dword ptr [edx], ebx
    mov ebx, dword ptr [ecx + 4]
    mov dword ptr [edx + 4], ebx
    add ecx, 8
    add edx, 8
    cmp ecx, eax
    _emit 0x75
    _emit 0xec  ; jne 0x79f871
    sub eax, edi
    sar eax, 3
    neg eax
    add eax, eax
    add eax, eax
    add eax, eax
    add dword ptr [esi + 4], eax
    mov eax, dword ptr [esp + 0ch]
    pop edi
    pop esi
    pop ebx
    test eax, eax
    _emit 0x74
    _emit 0x0f  ; je 0x79f8af
    cmp eax, dword ptr [esp + 10h]
    _emit 0x74
    _emit 0x09  ; je 0x79f8af
    push eax
    call EXT_f47380
    add esp, 4
    mov ecx, dword ptr [esp + 118h]
    _emit 0x64
    _emit 0x89
    _emit 0x0d
    _emit 0x00
    _emit 0x00
    _emit 0x00
    _emit 0x00  ; mov dword ptr fs:[0], ecx
    add esp, 124h
    ret
  }
}


