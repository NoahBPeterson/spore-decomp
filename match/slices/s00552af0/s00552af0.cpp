// Slice s00552af0: EASTL hashtable instantiations (find/erase/insert for uint64/key3/uint
// keys) and the string16-vector helpers. Module flags:
// /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

void operator_delete(void* p);
void FUN_00921440(void* out, int buckets, int count, int force);
int  FUN_00554250(uint32_t* key);
void FUN_005542d0(int buckets);
int  FUN_00554480(int buckets);
int  FUN_00554560(uint32_t* key);
void FUN_005545c0(int buckets);
void FUN_00429410(void* self);
void FUN_00554b10();
void FUN_005550a0(void* first, int n, void* out);
void FUN_00554760(void* first, void* last);
extern char DAT_01667bac[];

struct HT {
    char pad[0x100];
    int  Erase64(uint32_t* key);
    int* EraseIter(int* out, int node, int* bucket);
    int* Insert64(int* out, uint32_t* key);
    int* FindKey3(int* out, uint32_t* key);
    int* FindKey3b(int* out, uint32_t* key);
    int  EraseKey3(uint32_t* key);
    int* InsertKey3(int* out, uint32_t* key);
    int* Find64(int* out, uint32_t* key);
    int  ErasePair(uint32_t* key);
    int* InsertPair(int* out, uint32_t* key);
    int* FindU32(int* out, uint32_t* key);
};
struct El { void Dtor(); };
struct Vec16 { void FUN_00553b90(); void FUN_00553be0(unsigned n); };

// @ 0x00552af0
int HT::Erase64(uint32_t* key)
{
    char* s = (char*)this;
    int n0 = *(int*)(s + 0xc);
    int* p = (int*)(*(int*)(s + 4) + (*key % *(uint32_t*)(s + 8)) * 4);
    for (;;) {
        if (*p == 0) break;
        if (*key == *(uint32_t*)*p && key[1] == ((uint32_t*)*p)[1]) break;
        p = (int*)(*p + 0x18);
    }
    for (;;) {
        if (*p == 0) return n0 - *(int*)(s + 0xc);
        if (!(*key == *(uint32_t*)*p && key[1] == ((uint32_t*)*p)[1])) return n0 - *(int*)(s + 0xc);
        int node = *p;
        *p = *(int*)(node + 0x18);
        operator_delete((void*)node);
        *(int*)(s + 0xc) = *(int*)(s + 0xc) - 1;
    }
}

// @ 0x00552c20
int* HT::EraseIter(int* out, int node, int* bucket)
{
    char* s = (char*)this;
    int local_10 = *(int*)(node + 0x18);
    while (local_10 == 0) {
        bucket = bucket + 1;
        local_10 = *bucket;
    }
    int local_8 = *bucket;
    if (local_8 == node) {
        *bucket = *(int*)(local_8 + 0x18);
    } else {
        int local_18 = *(int*)(local_8 + 0x18);
        for (; local_18 != node; local_18 = *(int*)(local_18 + 0x18)) {
            local_8 = local_18;
        }
        *(int*)(local_8 + 0x18) = *(int*)(local_18 + 0x18);
    }
    operator_delete((void*)node);
    *(int*)(s + 0xc) = *(int*)(s + 0xc) - 1;
    out[0] = local_10;
    out[1] = (int)bucket;
    return out;
}

// @ 0x00552d00
int* HT::Insert64(int* out, uint32_t* key)
{
    char* s = (char*)this;
    uint32_t h = *key % *(uint32_t*)(s + 8);
    uint32_t* p = *(uint32_t**)(*(int*)(s + 4) + h * 4);
    uint32_t* found;
    for (;;) {
        if (p == 0) { found = 0; break; }
        if (*key == *p && key[1] == p[1]) { found = p; break; }
        p = (uint32_t*)p[6];
    }
    if (found == 0) {
        char rehash[4];
        uint32_t newBuckets = 0;
        FUN_00921440(rehash, *(int*)(s + 8), *(int*)(s + 0xc), 1);
        int node = FUN_00554250(key);
        if (rehash[0] != 0) {
            h = *key % newBuckets;
            FUN_005542d0((int)newBuckets);
        }
        *(int*)(node + 0x18) = *(int*)(*(int*)(s + 4) + h * 4);
        *(int*)(*(int*)(s + 4) + h * 4) = node;
        *(int*)(s + 0xc) = *(int*)(s + 0xc) + 1;
        out[0] = node;
        out[1] = *(int*)(s + 4) + h * 4;
        *(char*)(out + 2) = 1;
    } else {
        out[0] = (int)found;
        out[1] = *(int*)(s + 4) + h * 4;
        *(char*)(out + 2) = 0;
    }
    return out;
}

// @ 0x00552f80
int* HT::FindKey3(int* out, uint32_t* key)
{
    char* s = (char*)this;
    uint32_t* p = *(uint32_t**)(*(int*)(s + 4) + ((key[0] ^ key[2]) % *(uint32_t*)(s + 8)) * 4);
    uint32_t* found;
    for (;;) {
        if (p == 0) { found = 0; break; }
        if (key[0] == p[0] && key[1] == p[1] && key[2] == p[2]) { found = p; break; }
        p = (uint32_t*)p[6];
    }
    int local_24[2] = { 0, 0 };
    int local_1c[2];
    if (found == 0) { out[0] = local_24[0]; out[1] = local_24[1]; }
    else { local_1c[0] = (int)found; local_1c[1] = 0; out[0] = local_1c[0]; out[1] = local_1c[1]; }
    return out;
}

// @ 0x00553090
int* HT::FindKey3b(int* out, uint32_t* key)
{
    char* s = (char*)this;
    uint32_t* p = *(uint32_t**)(*(int*)(s + 4) + ((key[0] ^ key[2]) % *(uint32_t*)(s + 8)) * 4);
    uint32_t* found;
    for (;;) {
        if (p == 0) { found = 0; break; }
        if (key[0] == p[0] && key[1] == p[1] && key[2] == p[2]) { found = p; break; }
        p = (uint32_t*)p[6];
    }
    int local_24[2] = { 0, 0 };
    int local_1c[2];
    if (found == 0) { out[0] = local_24[0]; out[1] = local_24[1]; }
    else { local_1c[0] = (int)found; local_1c[1] = 0; out[0] = local_1c[0]; out[1] = local_1c[1]; }
    return out;
}

// @ 0x005531b0
int HT::EraseKey3(uint32_t* key)
{
    char* s = (char*)this;
    int n0 = *(int*)(s + 0xc);
    int* p = (int*)(*(int*)(s + 4) + ((key[0] ^ key[2]) % *(uint32_t*)(s + 8)) * 4);
    for (;;) {
        if (*p == 0) break;
        uint32_t* q = (uint32_t*)*p;
        if (key[0] == q[0] && key[1] == q[1] && key[2] == q[2]) break;
        p = (int*)(*p + 0x18);
    }
    for (;;) {
        if (*p == 0) return n0 - *(int*)(s + 0xc);
        uint32_t* q = (uint32_t*)*p;
        if (!(key[0] == q[0] && key[1] == q[1] && key[2] == q[2])) return n0 - *(int*)(s + 0xc);
        int node = *p;
        *p = *(int*)(node + 0x18);
        operator_delete((void*)node);
        *(int*)(s + 0xc) = *(int*)(s + 0xc) - 1;
    }
}

// @ 0x005532f0
int* HT::InsertKey3(int* out, uint32_t* key)
{
    char* s = (char*)this;
    uint32_t h = (key[0] ^ key[2]) % *(uint32_t*)(s + 8);
    uint32_t* p = *(uint32_t**)(*(int*)(s + 4) + h * 4);
    uint32_t* found;
    for (;;) {
        if (p == 0) { found = 0; break; }
        if (key[0] == p[0] && key[1] == p[1] && key[2] == p[2]) { found = p; break; }
        p = (uint32_t*)p[6];
    }
    if (found == 0) {
        char rehash[4];
        uint32_t newBuckets = 0;
        FUN_00921440(rehash, *(int*)(s + 8), *(int*)(s + 0xc), 1);
        int node = FUN_00554250(key);
        if (rehash[0] != 0) {
            FUN_00554480((int)newBuckets);
        }
        *(int*)(node + 0x18) = *(int*)(*(int*)(s + 4) + h * 4);
        *(int*)(*(int*)(s + 4) + h * 4) = node;
        *(int*)(s + 0xc) = *(int*)(s + 0xc) + 1;
        out[0] = node;
        out[1] = *(int*)(s + 4) + h * 4;
        *(char*)(out + 2) = 1;
    } else {
        out[0] = (int)found;
        out[1] = *(int*)(s + 4) + h * 4;
        *(char*)(out + 2) = 0;
    }
    return out;
}

// @ 0x00553510
int* HT::Find64(int* out, uint32_t* key)
{
    char* s = (char*)this;
    uint32_t* p = *(uint32_t**)(*(int*)(s + 4) + (*key % *(uint32_t*)(s + 8)) * 4);
    uint32_t* found;
    for (;;) {
        if (p == 0) { found = 0; break; }
        if (*key == p[0] && key[1] == p[1]) { found = p; break; }
        p = (uint32_t*)p[2];
    }
    int local_24[2] = { 0, 0 };
    int local_1c[2];
    if (found == 0) { out[0] = local_24[0]; out[1] = local_24[1]; }
    else { local_1c[0] = (int)found; local_1c[1] = 0; out[0] = local_1c[0]; out[1] = local_1c[1]; }
    return out;
}

// @ 0x00553620
int HT::ErasePair(uint32_t* key)
{
    char* s = (char*)this;
    int n0 = *(int*)(s + 0xc);
    int* p = (int*)(*(int*)(s + 4) + (*key % *(uint32_t*)(s + 8)) * 4);
    for (;;) {
        if (*p == 0) break;
        if (*key == *(uint32_t*)*p && key[1] == ((uint32_t*)*p)[1]) break;
        p = (int*)(*p + 8);
    }
    for (;;) {
        if (*p == 0) return n0 - *(int*)(s + 0xc);
        if (!(*key == *(uint32_t*)*p && key[1] == ((uint32_t*)*p)[1])) return n0 - *(int*)(s + 0xc);
        int node = *p;
        *p = *(int*)(node + 8);
        operator_delete((void*)node);
        *(int*)(s + 0xc) = *(int*)(s + 0xc) - 1;
    }
}

// @ 0x00553750
int* HT::InsertPair(int* out, uint32_t* key)
{
    char* s = (char*)this;
    uint32_t h = *key % *(uint32_t*)(s + 8);
    uint32_t* p = *(uint32_t**)(*(int*)(s + 4) + h * 4);
    uint32_t* found;
    for (;;) {
        if (p == 0) { found = 0; break; }
        if (*key == p[0] && key[1] == p[1]) { found = p; break; }
        p = (uint32_t*)p[2];
    }
    if (found == 0) {
        char rehash[4];
        uint32_t newBuckets = 0;
        FUN_00921440(rehash, *(int*)(s + 8), *(int*)(s + 0xc), 1);
        int node = FUN_00554560(key);
        if (rehash[0] != 0) {
            FUN_005545c0((int)newBuckets);
        }
        *(int*)(node + 8) = *(int*)(*(int*)(s + 4) + h * 4);
        *(int*)(*(int*)(s + 4) + h * 4) = node;
        *(int*)(s + 0xc) = *(int*)(s + 0xc) + 1;
        out[0] = node;
        out[1] = *(int*)(s + 4) + h * 4;
        *(char*)(out + 2) = 1;
    } else {
        out[0] = (int)found;
        out[1] = *(int*)(s + 4) + h * 4;
        *(char*)(out + 2) = 0;
    }
    return out;
}

// @ 0x005538f0
int* HT::FindU32(int* out, uint32_t* key)
{
    char* s = (char*)this;
    uint32_t* p = *(uint32_t**)(*(int*)(s + 4) + (*key % *(uint32_t*)(s + 8)) * 4);
    uint32_t* found;
    for (;;) {
        if (p == 0) { found = 0; break; }
        if (*key == p[0]) { found = p; break; }
        p = (uint32_t*)p[4];
    }
    int local_24[2] = { 0, 0 };
    int local_1c[2];
    if (found == 0) { out[0] = local_24[0]; out[1] = local_24[1]; }
    else { local_1c[0] = (int)found; local_1c[1] = 0; out[0] = local_1c[0]; out[1] = local_1c[1]; }
    return out;
}

// @ 0x00553b90
void Vec16::FUN_00553b90()
{
    char* s = (char*)this;
    uint32_t end = *(uint32_t*)(s + 4);
    for (uint32_t p = *(uint32_t*)s; p < end; p = p + 0x10) {
        ((El*)p)->Dtor();
    }
    FUN_00554b10();
}

// @ 0x00553be0
void Vec16::FUN_00553be0(unsigned n)
{
    char* s = (char*)this;
    if ((unsigned)((*(int*)(s + 4) - *(int*)s) >> 4) < n) {
        char* local_14 = DAT_01667bac;
        char* local_10 = DAT_01667bac;
        int local_c = 0x1667bad;
        FUN_005550a0(*(void**)(s + 4), n - ((*(int*)(s + 4) - *(int*)s) >> 4), &local_14);
        if (1 < local_c - (int)local_14 && local_14 != 0) {
            operator_delete(local_14);
        }
    } else {
        FUN_00554760((void*)(n * 0x10 + *(int*)s), *(void**)(s + 4));
    }
}
