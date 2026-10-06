// Slice s007ea440.
#include "../s007e5220/s007e5220.h"
#include <intrin.h>

extern "C" void operator_delete__(void* p);

struct DateTime { int a; int b; void Set(int kind); };

// @ 0x007EAEF0
struct ObjAE {
    char pad[0x30];
    int  f30;   // +0x30
    int  f34;   // +0x34
    void FUN_007eaef0();
};
void ObjAE::FUN_007eaef0() {
    DateTime dt;
    dt.Set(2);
    f30 = dt.a;
    f34 = dt.b;
}

// @ 0x007EAF30
struct ObjAF {
    void* Cast(int id);
};
void* ObjAF::Cast(int id) {
    if (id == 0x45a9b42)
        return (char*)this - 8;
    return 0;
}

// @ 0x007EB060  (copy ints [first,last) to dst)
void FUN_007eb060(int first, int last, int* dst) {
    if (first != last) {
        int off = first - (int)dst;
        do {
            if (dst)
                *dst = *(int*)(off + (int)dst);
            ++dst;
        } while (off + (int)dst != last);
    }
}

// @ 0x007EB090  (rbtree node count)
int FUN_007eb090(int self) {
    int* bucket = *(int**)(self + 0x10);
    int node = *bucket;
    int count = 0;
    if (node == 0) {
        ++bucket;
        node = *bucket;
        while (node == 0) {
            ++bucket;
            node = *bucket;
        }
    }
    int end = *(int*)(*(int*)(self + 0x10) + *(int*)(self + 0x14) * 4);
    while (node != end) {
        int n = 0;
        for (int* p = *(int**)(node + 4); p != (int*)(node + 4); p = (int*)*p)
            ++n;
        count += n;
        node = *(int*)(node + 0x10);
        while (node == 0) {
            ++bucket;
            node = *bucket;
        }
    }
    return count;
}

// @ 0x007EB100  (hashtable find)
struct HashTable {
    char pad0[4];
    int* mpBucketArray;   // +4
    int  mnBucketCount;   // +8
    void find(void* out, void* key);
};
struct ObjB1 {
    char pad[0xc];
    HashTable ht;         // +0xc
    int FUN_007eb100(int key);
};
int ObjB1::FUN_007eb100(int key) {
    int local;
    ht.find(&local, (void*)key);
    if (local != ht.mpBucketArray[ht.mnBucketCount])
        return local + 4;
    return 0;
}

// @ 0x007EB360  (vector assign from another)
struct VecB { int* begin; int* end; int* cap; };
struct ObjB3 {
    int* begin; int* end; int* cap;
    void FUN_007eb000(int n, void* tag);
    ObjB3* FUN_007eb360(VecB* src);
};
ObjB3* ObjB3::FUN_007eb360(VecB* src) {
    FUN_007eb000((src->end - src->begin) >> 2, src + 1);
    int* s = src->begin;
    int* d = begin;
    while (s != src->end) {
        if (d)
            *d = *s;
        ++s; ++d;
    }
    end = d;
    return this;
}

// @ 0x007EB3B0  (copy [src,..) backwards)
struct ObjB3b { int* begin; int* end; void copyDown(int* dst, int* src); };
void ObjB3b::copyDown(int* dst, int* src) {
    int* d = dst;
    for (int* s = src; s != end; ++s) {
        *d = *s;
        ++d;
    }
    end += ((int)src - (int)dst >> 2) * -4;
}

// @ 0x007EB3F0  (free list nodes)
struct ObjB3f { int* first; void freeNodes(); };
void ObjB3f::freeNodes() {
    int* node = *(int**)this;
    while (node != (int*)this) {
        int p = node[5];
        int* next = (int*)*node;
        if (p && *(int*)(p - 4))
            operator_delete__((void*)p);
        operator_delete__(node);
        node = next;
    }
}

// @ 0x007EA440  (large serialization routine)
void FUN_007ea440(void* self) { (void)self; }

// @ 0x007EAA10  (cAppSystem::InitGraphics)
int cAppSystemInitGraphics(void* self) { (void)self; return 0; }

// @ 0x007EB140  (large serialization routine)
void FUN_007eb140(void* self, void* writer) { (void)self; (void)writer; }
