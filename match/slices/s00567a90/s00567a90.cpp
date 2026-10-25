// Slice s00567a90: EASTL rbtree/hashtable instantiations and range helpers emitted for the
// OTDB module. Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "../s0055ce80/s0055ce80.h"

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* FUN_0042dee0(void* a, int size, int align, int flags);
void FUN_00511f70(void* first, void* last, void* dst);
void FUN_0050eb40(void* first, void* last, void* dst);
void* FUN_0050f8b0(void* first, void* last, void* dst);
void FUN_00457450(void* dst, int bytes, void* value, void* unused);
void FUN_00512050(void* a, void* b, void* c, void* unused);
void* FUN_004554f0(void* first, void* last, void* dst);
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

struct RBTreeIntStub { int CopyCtor(void* src); };
struct RBTreeFloatStub { int CopyCtor(void* src); int InsertFloat(int retval, void* pos, float* key, char flag); };
struct HashFreeStub { void DoFreeNodes(void** pArr, unsigned n); };
struct VecRangeStub { void RangeCtor(int* first, int* last, int flag); };

// Callees that are thiscall members: the original loads ecx before each call.
struct RBTreeOps {
    void* FUN_005699f0(void* src, void* dst);   // 0x5699f0
    void* FUN_00569b10(void* key);              // 0x569b10
};
struct NodeSlot {
    void FUN_00566c50(void* node);              // 0x566c50
};

// Vector helpers whose host is passed in ecx (the migrated markers omitted the hidden this).
struct Vec12Stub {
    void DoInsertValue(void* pos, int n, void* value);    // 0x567a90
};
struct Vec8Stub {
    void InsertOne(void* pos, void* value);               // 0x567e70
};

// @ 0x00567a90  (large vector DoInsertValue helper, 12-byte elements)
void Vec12Stub::DoInsertValue(void* pos, int n, void* value) {
    struct Vec12 { char pad[0xc]; };
    char* self = (char*)this;
    int size = (*(int*)(self + 8) - *(int*)(self + 4)) / 0xc;
    if ((unsigned)n > (unsigned)size) {
        // --- grow ---
        int oldCount = (*(int*)(self + 4) - *(int*)(self)) / 0xc;
        int newCount;
        if (oldCount == 0)
            newCount = 1;
        else
            newCount = oldCount * 2;
        int grow;
        if (newCount < oldCount + n)
            grow = oldCount + n;
        else
            grow = newCount;
        char* mem;
        if (grow == 0)
            mem = 0;
        else
            mem = (char*)FUN_0042dee0(self + 0xc, grow * 0xc, 4, 0);
        char* mid = (char*)FUN_0050f8b0(*(void**)(self + 0), *(void**)(self + 4), mem);
        FUN_00457450(mid, n * 0xc, pos, value);
        char* end2 = (char*)FUN_0050f8b0(mid + n * 0xc, *(void**)(self + 4), *(void**)(self + 4));
        if (*(void**)(self + 0) != 0)
            FUN_004e1780(*(void**)(self));
        *(void**)(self + 0) = mem;
        *(void**)(self + 4) = end2;
        *(void**)(self + 8) = mem + grow * 0xc;
        (void)end2;
        (void)mid;
    } else if (n != 0) {
        // --- insert in place ---
        Vec12 tmp = *(Vec12*)value;
        int after = (*(int*)(self + 4) - (int)pos) / 0xc;
        char* oldEnd = (char*)(*(int*)(self + 4));
        if (n < after) {
            FUN_00512050(*(void**)(self + 4), (void*)(*(int*)(self + 4) + n * -0xc), *(void**)(self + 4), 0);
            *(int*)(self + 4) = n * 0xc + *(int*)(self + 4);
            char* dst = oldEnd;
            char* src = oldEnd + n * -0xc;
            while (src != (char*)pos) {
                *(int*)(dst - 0xc) = *(int*)(src - 0xc);
                *(int*)(dst - 8) = *(int*)(src - 8);
                *(int*)(dst - 4) = *(int*)(src - 4);
                dst -= 0xc;
                src -= 0xc;
            }
            char* it = (char*)pos;
            char* stop = (char*)pos + n * 0xc;
            while (it != stop) {
                *(int*)(it + 0) = *(int*)&tmp;
                *(int*)(it + 4) = *(int*)((char*)&tmp + 4);
                *(int*)(it + 8) = *(int*)((char*)&tmp + 8);
                it += 0xc;
            }
        } else {
            FUN_00457450(*(void**)(self + 4), (n - after) * 0xc, value, 0);
            *(int*)(self + 4) = (n - after) * 0xc + *(int*)(self + 4);
            FUN_0050eb40(pos, oldEnd, *(void**)(self + 4));
            *(int*)(self + 4) = after * 0xc + *(int*)(self + 4);
            char* it = (char*)pos;
            while (it != oldEnd) {
                *(int*)(it + 0) = *(int*)&tmp;
                *(int*)(it + 4) = *(int*)((char*)&tmp + 4);
                *(int*)(it + 8) = *(int*)((char*)&tmp + 8);
                it += 0xc;
            }
        }
    }
    (void)pos;
}

// @ 0x00567e70  (large vector insert helper, 8-byte elements)
void Vec8Stub::InsertOne(void* pos, void* value) {
    char* self = (char*)this;
    if (*(int*)(self + 4) == *(int*)(self + 8)) {
        // --- grow ---
        int oldCount = (*(int*)(self + 4) - *(int*)(self)) >> 3;
        int grow;
        if (oldCount == 0)
            grow = 1;
        else
            grow = oldCount << 1;
        char* mem;
        if (grow == 0)
            mem = 0;
        else
            mem = (char*)FUN_0042dee0(self + 0xc, grow << 3, 4, 0);
        char* p = (char*)FUN_004554f0(*(void**)(self), pos, mem);
        char* q;
        if (p == 0) {
            q = 0;
        } else {
            *(int*)p = *(int*)value;
            *(int*)(p + 4) = *(int*)((char*)value + 4);
            q = p;
        }
        char* end2 = (char*)FUN_004554f0(pos, *(void**)(self + 4), (char*)p + 8);
        if (*(void**)(self) != 0)
            FUN_004e1780(*(void**)(self));
        *(void**)(self) = mem;
        *(void**)(self + 4) = end2;
        *(void**)(self + 8) = mem + (grow << 3);
        (void)p;
    } else {
        // --- insert in place ---
        char* src = (char*)value;
        if ((unsigned)pos <= (unsigned)value && value < *(void**)(self + 4))
            src = (char*)value + 8;
        char* end = *(char**)(self + 4);
        if (end != 0) {
            *(int*)end = *(int*)(end - 8);
            *(int*)(end + 4) = *(int*)(end - 4);
        }
        char* dst = end;
        char* cur = end - 8;
        while (cur != (char*)pos) {
            *(int*)(dst - 8) = *(int*)(cur - 8);
            *(int*)(dst - 4) = *(int*)(cur - 4);
            dst -= 8;
            cur -= 8;
        }
        *(int*)pos = *(int*)src;
        *(int*)((char*)pos + 4) = *(int*)(src + 4);
        *(int*)(self + 4) = *(int*)(self + 4) + 8;
    }
    (void)pos;
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
int RBTreeIntStub::CopyCtor(void* src) {
    void* this_ = this;
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
        void* u = ((RBTreeOps*)this_)->FUN_005699f0(*(void**)((char*)src + 0xc), (char*)this_ + 4);
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
int RBTreeFloatStub::CopyCtor(void* src) {
    void* this_ = this;
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
int RBTreeFloatStub::InsertFloat(int retval, void* pos, float* key, char flag) {
    void* this_ = this;
    int local;
    if (flag == 0 && pos != (char*)this_ + 4 && *(float*)((char*)pos + 0x10) <= *key)
        local = 1;
    else
        local = 0;
    void* node = ((RBTreeOps*)this_)->FUN_00569b10(key);
    RBTreeInsert(node, pos, (char*)this_ + 4, (char)local);
    *(int*)((char*)this_ + 0x14) += 1;
    ((NodeSlot*)retval)->FUN_00566c50(node);
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
void VecRangeStub::RangeCtor(int* first, int* last, int flag) {
    int* dst = (int*)this;
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
void HashFreeStub::DoFreeNodes(void** pArr, unsigned n) {
    for (unsigned i = 0; i < n; ++i) {
        void* node = pArr[i];
        while (node) {
            void* next = *(void**)((char*)node + 8);
            EASTL_allocator_deallocate(node);
            node = next;
        }
        pArr[i] = 0;
    }
}

// @ 0x00568840  (lower_bound over 0x10-stride elements: primary key at +4, secondary at +0)
unsigned* FUN_00568840(unsigned* first, int last, unsigned* value) {
    int len = (last - (int)first) >> 4;
    while (len > 0) {
        int half = len >> 1;
        unsigned* mid = first + half * 4;
        int moveRight;
        if ((int)value[1] < (int)mid[1] ||
            ((int)value[1] <= (int)mid[1] && *value <= *mid))
            moveRight = 0;
        else
            moveRight = 1;
        if (moveRight) {
            first = mid + 4;
            len = len - (half + 1);
        } else {
            len = half;
        }
    }
    return first;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
