// Slice s00567a90: EASTL rbtree/hashtable instantiations and range helpers emitted for the
// OTDB module. Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "../s0055ce80/s0055ce80.h"

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* FUN_0042dee0(void* a, int size, int align, int flags);
void FUN_00511f70(void* first, void* last, void* dst);
void* FUN_00569980();
void* FUN_005699f0(void* src, void* dst);
void* FUN_00569b80(void* key);
void* FUN_00569b10(void* key);
void FUN_00566c50(void* node);
void FUN_00566900(void* node);
void FUN_00566900_();
void FUN_00565920(void* p);
void FUN_004e1780(void* p);
void FUN_00564470(void* p);
void FUN_00553fb0(void* p);
void FUN_005156b0(void* p);
void RBTreeInsert(void* node, void* where, void* anchor, char flag);   // 0x009216a0 (equiv t2)
void RBTreeErase(void* node, void* anchor);

// @ 0x00567a90  (large vector DoInsertValue helper)
void* FUN_00567a90(void* this_, void* pos, int n, void* value) {
    (void)this_; (void)pos; (void)n; (void)value;
    return pos;
}

// @ 0x00567e70  (large vector insert helper)
void* FUN_00567e70(void* this_, void* pos, int n, void* value) {
    (void)this_; (void)pos; (void)n; (void)value;
    return pos;
}

// @ 0x005680a0
int FUN_005680a0(int first, int last, int out) {
    int result = out;
    for (int it = first; it != last; it += 0x50) {
        FUN_00553fb0((char*)it + 0x2c);
        FUN_00564470((char*)it + 0x10);
        result += 0x50;
    }
    return result;
}

// @ 0x00568110
int FUN_00568110(void* this_, void* src) {
    *(int*)((char*)this_ + 4) = 0;
    *(int*)((char*)this_ + 8) = 0;
    *(int*)((char*)this_ + 0xc) = 0;
    *(int*)((char*)this_ + 0x10) = 0;
    *(int*)((char*)this_ + 0x14) = 0;
    *(int*)((char*)this_ + 4) = (int)((char*)this_ + 4);
    *(int*)((char*)this_ + 8) = (int)((char*)this_ + 4);
    *(int*)((char*)this_ + 0xc) = 0;
    *(char*)((char*)this_ + 0x10) = 0;
    *(int*)((char*)this_ + 0x14) = 0;
    if (*(int*)((char*)src + 0xc) != 0) {
        void* u = FUN_005699f0(*(void**)((char*)src + 0xc), (char*)this_ + 4);
        *(void**)((char*)this_ + 0xc) = u;
        int* local_8;
        for (local_8 = *(int**)((char*)this_ + 0xc); *local_8 != 0; local_8 = (int*)*local_8) {
        }
        *(int**)((char*)this_ + 4) = local_8;
        int local_c;
        for (local_c = *(int*)((char*)this_ + 0xc); *(int*)(local_c + 4) != 0; local_c = *(int*)(local_c + 4)) {
        }
        *(int*)((char*)this_ + 8) = local_c;
        *(int*)((char*)this_ + 0x14) = *(int*)((char*)src + 0x14);
    }
    return (int)this_;
}

// @ 0x005681f0
int FUN_005681f0(void* this_, int retval, void* pos, int* key, char flag) {
    int local;
    if (flag == 0 && pos != (char*)this_ + 4 && *(int*)((char*)pos + 0x10) <= *key)
        local = 1;
    else
        local = 0;
    void* node = FUN_00569980();
    (void)node;
    RBTreeInsert(0, pos, (char*)this_ + 4, (char)local);
    *(int*)((char*)this_ + 0x14) += 1;
    return retval;
}

// @ 0x00568320
int FUN_00568320(void* this_, void* src) {
    *(int*)((char*)this_ + 4) = 0;
    *(int*)((char*)this_ + 8) = 0;
    *(int*)((char*)this_ + 0xc) = 0;
    *(int*)((char*)this_ + 0x10) = 0;
    *(int*)((char*)this_ + 0x14) = 0;
    *(int*)((char*)this_ + 4) = (int)((char*)this_ + 4);
    *(int*)((char*)this_ + 8) = (int)((char*)this_ + 4);
    *(int*)((char*)this_ + 0xc) = 0;
    *(char*)((char*)this_ + 0x10) = 0;
    *(int*)((char*)this_ + 0x14) = 0;
    if (*(int*)((char*)src + 0xc) != 0) {
        void* u = FUN_005699f0(*(void**)((char*)src + 0xc), (char*)this_ + 4);
        *(void**)((char*)this_ + 0xc) = u;
        int* local_8;
        for (local_8 = *(int**)((char*)this_ + 0xc); *local_8 != 0; local_8 = (int*)*local_8) {
        }
        *(int**)((char*)this_ + 4) = local_8;
        int local_c;
        for (local_c = *(int*)((char*)this_ + 0xc); *(int*)(local_c + 4) != 0; local_c = *(int*)(local_c + 4)) {
        }
        *(int*)((char*)this_ + 8) = local_c;
        *(int*)((char*)this_ + 0x14) = *(int*)((char*)src + 0x14);
    }
    return (int)this_;
}

// @ 0x00568400
int FUN_00568400(void* this_, int retval, void* pos, float* key, char flag) {
    int local;
    if (flag == 0 && pos != (char*)this_ + 4 && *key < *(float*)((char*)pos + 0x10))
        local = 1;
    else
        local = 0;
    void* node = FUN_00569b10(key);
    RBTreeInsert(node, pos, (char*)this_ + 4, (char)local);
    *(int*)((char*)this_ + 0x14) += 1;
    FUN_00566c50(node);
    return retval;
}

// @ 0x005684b0
void FUN_005684b0(void* p) {
    FUN_00566900(*(void**)((char*)p + 0x20));
    EASTL_allocator_deallocate(p);
}

// @ 0x00568590
void FUN_00568590(void* p) {
    if (*(void**)((char*)p + 0x14) != 0) {
        void* q = *(void**)((char*)p + 0x14);
        (*(void(__thiscall**)(void*))((*(void***)q)[2]))(q);
    }
    EASTL_allocator_deallocate(p);
}

// @ 0x00568680
int FUN_00568680(int first, int last, int out) {
    int local_20 = out;
    for (int it = first; it != last; it += 0x28) {
        if (local_20 != 0)
            FUN_00565920((void*)it);
        local_20 += 0x28;
    }
    for (int it = first; it != last; it += 0x28)
        FUN_004e1780((char*)it + 0x14);
    return local_20;
}

// @ 0x00568740
void FUN_00568740(int* dst, int* first, int* last, int flag) {
    (void)flag;
    int n = (int)(last - first) >> 2;
    int* mem;
    if (n == 0)
        mem = 0;
    else
        mem = (int*)FUN_0042dee0((char*)dst + 0xc, n << 2, 4, 0);
    dst[0] = (int)mem;
    dst[2] = (int)mem + n * 4;
    dst[1] = dst[2];
    FUN_00511f70(first, last, (void*)dst[0]);
}

// @ 0x005687d0
void FUN_005687d0(void* this_, void** pArr, unsigned n) {
    (void)this_;
    for (unsigned i = 0; i < n; ++i) {
        void* node = pArr[i];
        while (node) {
            void* next = *(void**)node;
            EASTL_allocator_deallocate(node);
            node = next;
        }
    }
}

// @ 0x00568840
void FUN_00568840(void* this_) {
    (void)this_;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
