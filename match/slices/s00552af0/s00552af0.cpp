// Slice s00552af0: EASTL hashtable instantiations (find/erase/insert for uint64/key3/uint
// keys) and the string16-vector helpers. Module flags:
// /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

void operator_delete(void* p);
void FUN_00429410(void* self);
void FUN_00554b10();
void FUN_005550a0(void* first, int n, void* out);
void FUN_00554760(void* first, void* last);
extern char DAT_01667bac[];

// ---- key types ---------------------------------------------------------------------------
typedef unsigned long long Key64;
struct Key3  { uint32_t a, b, c; };
typedef unsigned long long Key2;

inline bool Eq64(const Key64& x, const Key64& y) { return x == y; }
inline bool Eq2 (const Key2&  x, const Key2&  y) { return x == y; }
inline bool Eq3 (const Key3&  x, const Key3&  y) { return x.a  == y.a  && x.b  == y.b  && x.c == y.c; }
inline bool Eq32(const uint32_t& x, const uint32_t& y) { return x == y; }
inline uint32_t HashU32(uint32_t v) { uint32_t r = v; return r; }

// ---- EASTL iterator / insert-result / rehash policy --------------------------------------
struct IterBase {
    void*  mpNode;
    void** mpBucket;
    IterBase(void* n, void** b) : mpNode(n), mpBucket(b) {}
};
struct Iter : IterBase {
    Iter(void* n, void** b) : IterBase(n, b) {}
    Iter(void** b) : IterBase(*b, b) {}
};
struct InsertResult {
    Iter first;
    bool second;
    InsertResult(const Iter& it, const bool& b) : first(it), second(b) {}
};
struct IterV : IterBase {
    IterV(void* n, void** b) : IterBase(n, b) {}
    IterV(void** b) : IterBase(*b, b) {}
    IterV(const IterV& x) : IterBase(x.mpNode, x.mpBucket) {}
};
struct InsertResultV {
    IterV first;
    bool second;
    InsertResultV(const IterV& it, const bool& b) : first(it), second(b) {}
};
// iterator whose non-trivial copy ctor adds the extra return-value copy layer
struct IterR : IterBase {
    IterR(void* n, void** b) : IterBase(n, b) {}
    IterR(void** b) : IterBase(*b, b) {}
    IterR(const IterR& x) : IterBase(x.mpNode, x.mpBucket) {}
};
struct TrueType {};
struct RehashResult { bool first; uint32_t second; };
struct RehashPolicy {
    uint32_t pad[4];
    RehashResult GetRehashRequired(uint32_t bucketCount, uint32_t elementCount, uint32_t add);
};

// ---- legacy table used by the erase() / vector helpers (booked non-matching) --------------
struct HT {
    char pad[0x100];
    int  Erase64(uint32_t* key);
    int* EraseIter(int* out, int node, int* bucket);
    int  EraseKey3(uint32_t* key);
    int  ErasePair(uint32_t* key);
};
struct El { void Dtor(); };
struct Vec16 {
    void FUN_00553b90();
    void FUN_00553be0(unsigned n);
    void DestroyStorage();                        // 0x00554B10
    void ReserveRaw(void* pos, int n, void* out); // 0x005550A0
};

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

// @ 0x00553b90
void Vec16::FUN_00553b90()
{
    char* s = (char*)this;
    uint32_t end = *(uint32_t*)(s + 4);
    for (uint32_t p = *(uint32_t*)s; p < end; p = p + 0x10) {
        ((El*)p)->Dtor();
    }
    DestroyStorage();
}

// @ 0x00553be0
void Vec16::FUN_00553be0(unsigned n)
{
    char* s = (char*)this;
    if ((unsigned)((*(int*)(s + 4) - *(int*)s) >> 4) < n) {
        char* local_14 = DAT_01667bac;
        char* local_10 = DAT_01667bac;
        int local_c = 0x1667bad;
        ReserveRaw(*(void**)(s + 4), n - ((*(int*)(s + 4) - *(int*)s) >> 4), &local_14);
        if (1 < local_c - (int)local_14 && local_14 != 0) {
            operator_delete(local_14);
        }
    } else {
        FUN_00554760((void*)(n * 0x10 + *(int*)s), *(void**)(s + 4));
    }
}

// ---- find() instantiations ---------------------------------------------------------------
// uint64 keys, node next at +0x08
struct Node64F { Key64 key; Node64F* next; };
struct Tbl64F {
    uint32_t pad0;
    Node64F** mpBucketArray;  // +4
    uint32_t  mnBucketCount;  // +8
    uint32_t  mnElementCount; // +0xc
    RehashPolicy mPolicy;     // +0x10

    __forceinline Node64F* DoFindNode(Node64F* pNode, const Key64& k) const
    {
        for (; pNode; pNode = pNode->next)
            if (Eq64(k, pNode->key))
                return pNode;
        return 0;
    }
    Iter Find(const Key64& k);   // 0x00553510
};

// key3 keys, node next at +0x18; by-reference equality predicate
struct Node3F { Key3 key; uint32_t pad[3]; Node3F* next; };
struct Tbl3F {
    uint32_t pad0;
    Node3F** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    RehashPolicy mPolicy;

    __forceinline Node3F* DoFindNode(Node3F* pNode, const Key3& k) const
    {
        for (; pNode; pNode = pNode->next)
            if (Eq3(k, pNode->key))
                return pNode;
        return 0;
    }
    Iter Find(const Key3& k);    // 0x00552f80
};

// key3 keys, node next at +0x18; direct member-wise comparison
struct Node3Fb { Key3 key; uint32_t pad[3]; Node3Fb* next; };
struct Tbl3Fb {
    uint32_t pad0;
    Node3Fb** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    RehashPolicy mPolicy;

    __forceinline Node3Fb* DoFindNode(Node3Fb* pNode, const Key3& k) const
    {
        for (; pNode; pNode = pNode->next)
            if (Eq3(k, pNode->key))
                return pNode;
        return 0;
    }
    IterR Find(const Key3& k);   // 0x00553090
};

// uint32 keys, node next at +0x10
struct Node32F { uint32_t key; uint32_t pad[3]; Node32F* next; };
struct Tbl32F {
    uint32_t pad0;
    Node32F** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    RehashPolicy mPolicy;

    __forceinline Node32F* DoFindNode(Node32F* pNode, const uint32_t& k) const
    {
        for (; pNode; pNode = pNode->next)
            if (Eq32(k, pNode->key))
                return pNode;
        return 0;
    }
    IterR Find(const uint32_t& k); // 0x005538f0
};

// ---- DoInsertValue instantiations --------------------------------------------------------
// uint64 keys, node next at +0x18
struct Node64I { Key64 key; uint32_t pad[4]; Node64I* next; };
struct Tbl64I {
    uint32_t pad0;
    Node64I** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    RehashPolicy mPolicy;

    Node64I* DoAllocateNode(const Key64& v);
    void     DoRehash(uint32_t n);
    __forceinline Node64I* DoFindNode(Node64I* pNode, const Key64& k) const
    {
        for (; pNode; pNode = pNode->next)
            if (Eq64(k, pNode->key))
                return pNode;
        return 0;
    }
    InsertResultV DoInsertValue(const Key64& value, TrueType);  // 0x00552d00
};

// key3 keys, node next at +0x18; direct member-wise comparison
struct Node3I { Key3 key; uint32_t pad[3]; Node3I* next; };
struct Tbl3I {
    uint32_t pad0;
    Node3I** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    RehashPolicy mPolicy;

    Node3I* DoAllocateNode(const Key3& v);
    void    DoRehash(uint32_t n);
    __forceinline Node3I* DoFindNode(Node3I* pNode, const Key3& k) const
    {
        for (; pNode; pNode = pNode->next)
            if (Eq3(k, pNode->key))
                return pNode;
        return 0;
    }
    InsertResultV DoInsertValue(const Key3& value, TrueType);   // 0x005532f0
};

// pair keys, node next at +0x08
struct Node2I { Key2 key; Node2I* next; };
struct Tbl2I {
    uint32_t pad0;
    Node2I** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    RehashPolicy mPolicy;

    Node2I* DoAllocateNode(const Key2& v);
    void    DoRehash(uint32_t n);
    __forceinline Node2I* DoFindNode(Node2I* pNode, const Key2& k) const
    {
        for (; pNode; pNode = pNode->next)
            if (Eq2(k, pNode->key))
                return pNode;
        return 0;
    }
    InsertResult DoInsertValue(const Key2& value, TrueType);   // 0x00553750
};

// @ 0x00552d00
InsertResultV Tbl64I::DoInsertValue(const Key64& value, TrueType)
{
    const Key64& k = value;
    uint32_t c = (uint32_t)k;
    uint32_t n = (uint32_t)c % mnBucketCount;
    Node64I* pNode = DoFindNode(mpBucketArray[n], k);

    if (pNode == 0) {
        RehashResult bRehash = mPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
        Node64I* pNodeNew = DoAllocateNode(value);
        if (bRehash.first) {
            n = (uint32_t)c % bRehash.second;
            DoRehash(bRehash.second);
        }
        pNodeNew->next = mpBucketArray[n];
        mpBucketArray[n] = pNodeNew;
        ++mnElementCount;
        return InsertResultV(IterV(pNodeNew, (void**)(mpBucketArray + n)), true);
    }
    return InsertResultV(IterV(pNode, (void**)(mpBucketArray + n)), false);
}

// @ 0x005532f0
InsertResultV Tbl3I::DoInsertValue(const Key3& value, TrueType)
{
    const Key3& k = value;
    uint32_t c = k.a ^ k.c;
    uint32_t n = (uint32_t)c % mnBucketCount;
    Node3I* pNode = DoFindNode(mpBucketArray[n], k);

    if (pNode == 0) {
        RehashResult bRehash = mPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
        Node3I* pNodeNew = DoAllocateNode(value);
        if (bRehash.first) {
            n = (uint32_t)c % bRehash.second;
            DoRehash(bRehash.second);
        }
        pNodeNew->next = mpBucketArray[n];
        mpBucketArray[n] = pNodeNew;
        ++mnElementCount;
        return InsertResultV(IterV(pNodeNew, (void**)(mpBucketArray + n)), true);
    }
    return InsertResultV(IterV(pNode, (void**)(mpBucketArray + n)), false);
}

// @ 0x00553750
InsertResult Tbl2I::DoInsertValue(const Key2& value, TrueType)
{
    const Key2& k = value;
    uint32_t c = (uint32_t)k;
    uint32_t n = (uint32_t)c % mnBucketCount;
    Node2I* pNode = DoFindNode(mpBucketArray[n], k);

    if (pNode == 0) {
        RehashResult bRehash = mPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
        Node2I* pNodeNew = DoAllocateNode(value);
        if (bRehash.first) {
            n = (uint32_t)c % bRehash.second;
            DoRehash(bRehash.second);
        }
        pNodeNew->next = mpBucketArray[n];
        mpBucketArray[n] = pNodeNew;
        ++mnElementCount;
        return InsertResult(Iter(pNodeNew, (void**)(mpBucketArray + n)), true);
    }
    return InsertResult(Iter(pNode, (void**)(mpBucketArray + n)), false);
}

// @ 0x00553510
Iter Tbl64F::Find(const Key64& k)
{
    uint32_t c = (uint32_t)k;
    uint32_t n = (uint32_t)c % mnBucketCount;
    Node64F* pNode = DoFindNode(mpBucketArray[n], k);
    return pNode ? Iter(pNode, (void**)(mpBucketArray + n))
                 : Iter((void**)(mpBucketArray + mnBucketCount));
}

// @ 0x00552f80
Iter Tbl3F::Find(const Key3& k)
{
    uint32_t c = k.a ^ k.c;
    uint32_t n = (uint32_t)c % mnBucketCount;
    Node3F* pNode = DoFindNode(mpBucketArray[n], k);
    return pNode ? Iter(pNode, (void**)(mpBucketArray + n))
                 : Iter((void**)(mpBucketArray + mnBucketCount));
}

// @ 0x00553090
IterR Tbl3Fb::Find(const Key3& k)
{
    uint32_t c = k.a ^ k.c;
    uint32_t n = (uint32_t)c % mnBucketCount;
    Node3Fb* pNode = DoFindNode(mpBucketArray[n], k);
    return pNode ? IterR(pNode, (void**)(mpBucketArray + n))
                 : IterR((void**)(mpBucketArray + mnBucketCount));
}

// @ 0x005538f0
IterR Tbl32F::Find(const uint32_t& k)
{
    uint32_t c = HashU32(k);
    uint32_t n = (uint32_t)c % mnBucketCount;
    Node32F* pNode = DoFindNode(mpBucketArray[n], k);
    return pNode ? IterR(pNode, (void**)(mpBucketArray + n))
                 : IterR((void**)(mpBucketArray + mnBucketCount));
}
