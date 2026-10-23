// Slice s0085d930 -- 0x85xxxx region (allocator/streaming helpers).
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1, flags /O2 /MD /Gy /TP
// /arch:SSE /fp:fast (default /GS on).

typedef unsigned int  uint;
typedef unsigned char byte;

typedef void* (__cdecl *ALLOC_FN)(int, int, int);
#define ALLOCATOR(p) (*(ALLOC_FN*)(*(int*)((char*)(p) + 4)))

void FUN_0085e2d0();

// @ 0x0085e5c0 -- FUN_0085e5c0
// Allocates the 0x40-byte vtable-ish object (installing FUN_0085e2d0 as its
// first entry) plus a (count << 8) table of 0xffffffff words.
void __cdecl FUN_0085e5c0(int param_1) {
    int* puVar1 = (int*)ALLOCATOR(param_1)(param_1, 1, 0x40);
    *(int*)(param_1 + 0x5bc) = (int)puVar1;
    puVar1[0] = (int)FUN_0085e2d0;
    puVar1[0xb] = 0;
    puVar1[0xc] = 0;
    puVar1[0xd] = 0;
    puVar1[0xe] = 0;
    int iVar3 = 0;
    int iVar6 = (int)ALLOCATOR(param_1)(param_1, 1, *(int*)(param_1 + 0x20) << 8);
    *(int*)(param_1 + 0xa0) = iVar6;
    int* puVar2 = (int*)iVar6;
    if (0 < *(int*)(param_1 + 0x20)) {
        do {
            iVar3 = iVar3 + 1;
            int* puVar4 = puVar2;
            for (int iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1) {
                *puVar4 = 0xffffffff;
                puVar4 = puVar4 + 1;
            }
            puVar2 = puVar2 + 0x40;
        } while (iVar3 < *(int*)(param_1 + 0x20));
    }
}

// @ 0x0085e630 -- FUN_0085e630
// Clamps the request to the buffer capacity, decodes up to that many elements
// through the codec at +0x5c4 and copies the result through the sink at +0x5cc.
void __cdecl FUN_0085e630(int param_1, int param_2, int param_3, int param_4, int param_5,
                          int* param_6, int param_7) {
    int* piVar4 = param_6;
    int iVar3 = param_1;
    int iVar2 = *(int*)(param_1 + 0x5b0);
    uint uVar5 = param_7 - *param_6;
    if (uVar5 > *(uint*)(iVar2 + 0x10)) {
        uVar5 = *(uint*)(iVar2 + 0x10);
    }
    int local = 0;
    (*(void(__cdecl**)(int, int, int, int, int, int*, uint))(*(int*)(param_1 + 0x5c4) + 4))(
        iVar3, param_2, param_3, param_4, *(int*)(iVar2 + 0xc), &local, uVar5);
    (*(void(__cdecl**)(int, int, int, int))(*(int*)(iVar3 + 0x5cc) + 4))(
        iVar3, *(int*)(iVar2 + 0xc), param_5 + *piVar4 * 4, local);
    *piVar4 = *piVar4 + local;
}

// @ 0x0085e6b0 -- FUN_0085e6b0
// Decodes into the sink buffer, zero-fills the gap the decoder left behind and
// recycles the buffer once it is full.
void __cdecl FUN_0085e6b0(int param_1, int param_2, int param_3, int param_4, int param_5,
                          int* param_6) {
    int iVar2 = *(int*)(param_1 + 0x5b0);
    uint* puVar1 = (uint*)(iVar2 + 0x18);
    if (*(int*)(iVar2 + 0x18) == 0) {
        int uVar4 = (*(int(__cdecl**)(int, int, int, int, int))(*(int*)(param_1 + 4) + 0x1c))(
            param_1, *(int*)(iVar2 + 8), *(int*)(iVar2 + 0x14), *(int*)(iVar2 + 0x10), 1);
        *(int*)(iVar2 + 0xc) = uVar4;
    }
    uint uVar3 = *puVar1;
    (*(void(__cdecl**)(int, int, int, int, int, uint*, int))(*(int*)(param_1 + 0x5c4) + 4))(
        param_1, param_2, param_3, param_4, *(int*)(iVar2 + 0xc), puVar1, *(int*)(iVar2 + 0x10));
    if (*puVar1 > uVar3) {
        int iVar5 = *puVar1 - uVar3;
        (*(void(__cdecl**)(int, int, int, int))(*(int*)(param_1 + 0x5cc) + 4))(
            param_1, *(int*)(iVar2 + 0xc) + uVar3 * 4, 0, iVar5);
        *param_6 = *param_6 + iVar5;
    }
    if (*puVar1 >= *(uint*)(iVar2 + 0x10)) {
        *(int*)(iVar2 + 0x14) = *(int*)(iVar2 + 0x14) + *(uint*)(iVar2 + 0x10);
        *puVar1 = 0;
    }
}

// @ 0x0085e760 -- FUN_0085e760
// Copies as many buffered elements as both the ring and the caller's remaining
// count allow through the sink at +0x5cc, then advances and recycles the ring.
void __cdecl FUN_0085e760(int param_1, int param_2, int param_3, int param_4, int param_5,
                          int* param_6, int param_7) {
    int iVar1 = *(int*)(param_1 + 0x5b0);
    if (*(int*)(iVar1 + 0x18) == 0) {
        int uVar2 = (*(int(__cdecl**)(int, int, int, int, int))(*(int*)(param_1 + 4) + 0x1c))(
            param_1, *(int*)(iVar1 + 8), *(int*)(iVar1 + 0x14), *(int*)(iVar1 + 0x10), 0);
        *(int*)(iVar1 + 0xc) = uVar2;
    }
    uint uVar4 = *(int*)(iVar1 + 0x10) - *(int*)(iVar1 + 0x18);
    uint uVar3 = param_7 - *param_6;
    if (uVar4 > uVar3) {
        uVar4 = uVar3;
    }
    uVar3 = *(int*)(param_1 + 0x74) - *(int*)(iVar1 + 0x14);
    if (uVar4 > uVar3) {
        uVar4 = uVar3;
    }
    (*(void(__cdecl**)(int, int, int, uint))(*(int*)(param_1 + 0x5cc) + 4))(
        param_1, *(int*)(iVar1 + 0xc) + *(int*)(iVar1 + 0x18) * 4, param_5 + *param_6 * 4, uVar4);
    *param_6 = *param_6 + uVar4;
    *(int*)(iVar1 + 0x18) = *(int*)(iVar1 + 0x18) + uVar4;
    if (*(uint*)(iVar1 + 0x18) >= *(uint*)(iVar1 + 0x10)) {
        *(int*)(iVar1 + 0x14) = *(int*)(iVar1 + 0x14) + *(uint*)(iVar1 + 0x10);
        *(int*)(iVar1 + 0x18) = 0;
    }
}
