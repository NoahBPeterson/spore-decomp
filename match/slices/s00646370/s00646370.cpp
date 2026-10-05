// Slice s00646370 -- swatch/community editor helpers.
// Module flags: /O2 /MD /Gy /TP /EHsc (scalar integer + EASTL, no SSE).
#include "types.h"

// ---------------------------------------------------------------------------
// Runtime helpers (relocations are masked, declarations only need the right
// calling convention / argument layout).
// ---------------------------------------------------------------------------
extern "C" void  __cdecl eastl_dealloc(void* p);                    // 0x00f47380
extern "C" void* __cdecl eastl_alloc(uint32_t n, const char* name, int a, int b,
                                     const char* file, int line);    // 0x00f473a0

// Spore's custom EASTL allocator keeps a header word in front of each block;
// a block is only released when that word is non-zero.
inline void FreeChecked(void* p) {
    if (p && ((uint32_t*)p)[-1])
        eastl_dealloc(p);
}

struct Key8 { uint32_t first; uint32_t second; };
struct InsertResult { void* node; void* bucket; bool inserted; };

// ---------------------------------------------------------------------------
// @ 0x00646d70  eastl::vector<T,sp_vector_allocator>::DoDestroyValues
// ---------------------------------------------------------------------------
// @ 0x00646d70
void __stdcall sub_646d70(uint8_t* first, uint8_t* last) {
    for (; first < last; first += 0x34) {
        FreeChecked(*(void**)(first + 0x20));
        FreeChecked(*(void**)(first + 8));
    }
}

// ---------------------------------------------------------------------------
// @ 0x00646fc0  eastl::vector<T (0x14 bytes)>::reserve
// ---------------------------------------------------------------------------
extern "C" void* __cdecl uninit_copy14(void* first, void* last, void* dest);    // 0x00645450
extern "C" void* __cdecl uninit_destroy14(void* first, void* last, void* dest); // 0x006454c0

class Vec14 {
public:
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCapacity;
    void reserve(uint32_t n);
};

// @ 0x00646fc0
void Vec14::reserve(uint32_t n) {
    if (n > (uint32_t)((mpCapacity - mpBegin) / 0x14)) {
        uint8_t* pNewData;
        if (n)
            pNewData = (uint8_t*)eastl_alloc(n * 0x14, "Editor", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        else
            pNewData = 0;
        uint8_t* const pOldEnd = mpEnd;
        uint8_t* const pOldBegin = mpBegin;
        uninit_copy14(pOldBegin, pOldEnd, pNewData);
        uninit_destroy14(pOldBegin, pOldEnd, pNewData);
        if (mpBegin)
            eastl_dealloc(mpBegin);
        const uint32_t nPrevSize = (uint32_t)((mpEnd - mpBegin) / 0x14);
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize * 0x14;
        mpCapacity = pNewData + n * 0x14;
    }
}

// ---------------------------------------------------------------------------
// Hashtable container stubs (0x20 / 0x24 bytes so the owner's member offsets
// line up with the disassembly: +0xf8, +0x118, +0x138, +0x15c).
// ---------------------------------------------------------------------------
struct IRef {
    virtual void AddRef();
    virtual void Release();
};
struct AutoRef {
    IRef* p;
    AutoRef() : p(0) {}
    AutoRef(IRef* x) : p(x) { if (p) p->AddRef(); }
    AutoRef& operator=(IRef* x) { if (x) x->AddRef(); p = x; return *this; }
    ~AutoRef() { if (p) p->Release(); }
};
struct RefPair {
    uint32_t first;
    IRef* second;
    RefPair() {}
};
struct EmptyTag {};

struct Container0F8 {
    uint8_t mData[0x20];
    InsertResult find_insert(const Key8& key, EmptyTag tag);
};
struct Container118 {
    uint8_t mData[0x20];
    InsertResult find_insert(const Key8& key, EmptyTag tag);
};
struct Container138 {
    uint8_t mData[0x24];
    InsertResult insert(const RefPair& key, EmptyTag tag);
};
struct Container15C {
    uint8_t mData[0x24];
    InsertResult insert(const RefPair& key, EmptyTag tag);
};

struct Owner {
    uint8_t pad0[0xf8];
    Container0F8 m0F8;      // +0xf8
    Container118 m118;      // +0x118
    Container138 m138;      // +0x138
    Container15C m15C;      // +0x15c

    bool Insert0F8(uint32_t a, uint32_t b);
    bool Insert118(uint32_t a, uint32_t b);
    bool Insert138(uint32_t a, IRef* b);
    bool Insert15C(uint32_t a, IRef* b);
};

// @ 0x00646dc0
bool Owner::Insert118(uint32_t a, uint32_t b) {
    Key8 key; key.first = a; key.second = b;
    InsertResult r = m118.find_insert(key, EmptyTag());
    return r.inserted;
}

// @ 0x00646e00
bool Owner::Insert0F8(uint32_t a, uint32_t b) {
    Key8 key; key.first = a; key.second = b;
    InsertResult r = m0F8.find_insert(key, EmptyTag());
    return r.inserted;
}

// @ 0x00646e40
bool Owner::Insert138(uint32_t a, IRef* b) {
    if (b) b->AddRef();
    RefPair key; key.first = a; key.second = b;
    if (b) b->AddRef();
    InsertResult r = m138.insert(key, EmptyTag());
    if (key.second) key.second->Release();
    if (b) b->Release();
    return r.inserted;
}

// @ 0x00646ec0
bool Owner::Insert15C(uint32_t a, IRef* b) {
    if (b) b->AddRef();
    RefPair key; key.first = a; key.second = b;
    if (b) b->AddRef();
    InsertResult r = m15C.insert(key, EmptyTag());
    if (key.second) key.second->Release();
    if (b) b->Release();
    return r.inserted;
}

// ---------------------------------------------------------------------------
// @ 0x00646d10  map find (template instantiation)
// ---------------------------------------------------------------------------
struct Elem20 {
    uint32_t f00, f04, f08, f0c, f10, f14, f18, f1c;
};
struct OutPair { void* first; void* second; };
struct MapFindSelf {
    Elem20* mBegin;     // +0
    Elem20* mEnd;       // +4
    uint32_t mField8;   // +8
    uint32_t mFieldC;   // +0xc
    uint32_t mField10;  // +0x10
    uint8_t  mFlag14;   // +0x14

    void Find(OutPair* out, const OutPair* key);
};
extern "C" Elem20* __cdecl lower_bound20(Elem20* first, Elem20* last, const OutPair* key, uint8_t flag); // 0x00646030

// @ 0x00646d10
void MapFindSelf::Find(OutPair* out, const OutPair* key) {
    Elem20* const last = mEnd;
    Elem20* p = lower_bound20(mBegin, last, key, mFlag14);
    if (p != last) {
        const uint32_t* k = (const uint32_t*)key;
        bool less = k[0] < p->f00;
        if ((k[0] == p->f00) && (less = k[2] < p->f08, k[2] == p->f08))
            less = k[1] < p->f04;
        if (!less) {
            out->first = p;
            out->second = p + 1;
            return;
        }
    }
    out->first = p;
    out->second = p;
}

// ---------------------------------------------------------------------------
// @ 0x00646f40  find-or-insert returning a pointer just past the key
// ---------------------------------------------------------------------------
struct MapFindInsert {
    uint32_t mField0;       // +0
    void* mpBuckets;        // +4
    uint32_t mBucketCount;  // +8
    uint32_t mCountC;       // +0xc
    uint32_t mField10;      // +0x10

    void find(InsertResult* out, const uint32_t* key);
    void insert(InsertResult* out, const uint32_t* key, EmptyTag tag);
    uint32_t* FindOrInsert(uint32_t* key);
};

// @ 0x00646f40
uint32_t* MapFindInsert::FindOrInsert(uint32_t* key) {
    InsertResult r;
    find(&r, key);
    if ((uint32_t*)r.node != ((uint32_t**)mpBuckets)[mBucketCount])
        return (uint32_t*)r.node + 1;
    uint32_t keyCopy = *key;
    insert(&r, &keyCopy, EmptyTag());
    return (uint32_t*)r.node + 1;
}

// ---------------------------------------------------------------------------
// Large swatch/community-editor methods; reconstructed only in outline and
// therefore listed in partial.txt.
// ---------------------------------------------------------------------------
// @ 0x00646370
bool __cdecl sub_646370(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t) {
    return false;
}

// @ 0x00646ae0
void __fastcall sub_646ae0(void*) {
}
