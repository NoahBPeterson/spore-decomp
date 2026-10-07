// Spore decompilation - batch bfs4, slice s008fe610 (0x008FE610..0x008FF60F).
// EA::XHTML::Resource ResourceCache / ProtocolHandler map + EASTL hashtable internals.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE2
#include <intrin.h>
#include <string.h>
#include "types.h"

void __cdecl operator_delete__(void* p);  // 0x00f47380
void* __cdecl operator_new(unsigned n, const char* name, int a, int b, const char* file, int line);
// ---------------------------------------------------------------------------
// intrusive doubly-linked list (header node == this)
// ---------------------------------------------------------------------------
struct ListHdr {
    void* mpNext;   // +0
    void* mpPrev;   // +4
    ListHdr()
    {
        mpPrev = this;
        mpNext = this;
    }
    __declspec(noinline) void Find(void** out, void* limit);
};

struct LNode {
    LNode* mpNext;
    LNode* mpPrev;
};

static __forceinline void FindInl(void* head, void** out, void* lim)
{
    LNode* h = (LNode*)head;
    LNode* p = h->mpNext;
    if (p != h) {
        do {
            if (p == lim) {
                *out = p;
                return;
            }
            p = p->mpNext;
        } while (p != h);
    }
    *out = head;
}

static __forceinline void SpliceInl(void* pos_, void* node_)
{
    LNode* pos = (LNode*)pos_;
    LNode* node = (LNode*)node_;
    if (pos == node)
        return;
    LNode* n0 = node->mpNext;
    LNode* n1 = node->mpPrev;
    n0->mpPrev = n1;
    n1->mpNext = n0;
    LNode* p1 = pos->mpPrev;
    p1->mpNext = node;
    pos->mpPrev = node;
    node->mpPrev = p1;
    node->mpNext = pos;
}

// @ 0x008fe6a0
void ListHdr::Find(void** out, void* limit)
{
    FindInl(this, out, limit);
}

__declspec(noinline) void __stdcall Splice(void* pos, void* x, void* node);

// @ 0x008fe6d0
void __stdcall Splice(void* pos, void* x, void* node)
{
    (void)x;
    SpliceInl(pos, node);
}

// ---------------------------------------------------------------------------
// non-atomic refcount template + global holder
// ---------------------------------------------------------------------------
struct RCObjN {
    virtual void v0(int);
    virtual void v1();
    virtual void v2();
    int mRef;       // +4
};

extern "C" void* gResourceProvider;

// @ 0x008fe930
RCObjN* SetGlobalProvider(RCObjN* p)
{
    RCObjN** slot = (RCObjN**)((char*)gResourceProvider + 0x10);
    RCObjN* old = *slot;
    if (p != old) {
        if (p)
            p->mRef++;
        *slot = p;
        if (old) {
            if (--old->mRef == 0) {
                old->mRef = 1;
                old->v0(1);
            }
        }
    }
    return old;
}

// ---------------------------------------------------------------------------
// hashtable node allocation / bucket freeing
// ---------------------------------------------------------------------------
struct SrcNode {
    void* p0;
    RCObjN* p4;
};
struct HNode {
    void* p0;       // +0
    RCObjN* p4;     // +4
    void* p8;       // +8
};

// @ 0x008fea30
HNode* __stdcall AllocHNode(SrcNode* s)
{
    HNode* n = (HNode*)operator_new(0xc, "EASTL", 0, 0, "eastl/allocator.h", 0xd1);
    if (n) {
        n->p0 = s->p0;
        n->p4 = s->p4;
        if (n->p4)
            n->p4->v1();
    }
    n->p8 = 0;
    return n;
}

struct BucketNode {
    char pad0[8];
    void* p8;       // +8
    char pad1[0x1c - 0xc];
    BucketNode* p1c;  // +0x1c
};

// @ 0x008ff110
void __stdcall FreeBuckets(BucketNode** buckets, unsigned n)
{
    for (unsigned i = 0; i < n; i++) {
        BucketNode* p = buckets[i];
        if (p) {
            do {
                BucketNode* cur = p;
                _ReadWriteBarrier();
                void* buf = cur->p8;
                _ReadWriteBarrier();
                p = p->p1c;
                if (buf != 0 && *((int*)buf - 1) != 0)
                    operator_delete__(buf);
                operator_delete__(cur);
            } while (p);
        }
        buckets[i] = 0;
    }
}

// ---------------------------------------------------------------------------
// shared stubs
// ---------------------------------------------------------------------------
struct TagT {};  // empty tag struct passed by value (eastl true_type)

struct IAlloc {
    virtual void v0();
    virtual void* Alloc(unsigned sz, const char* name, unsigned flags, unsigned align, unsigned off);
    virtual void v2();
    virtual void Free(void* p, unsigned sz);
};
struct IUnk {
    virtual void v0();
    virtual void Release();
};
struct IRC {  // refcounted interface (dtor, AddRef, Release)
    virtual void v0(int);
    virtual void AddRef();
    virtual void Release();
};
struct ARC {  // EA::AutoRefCount<IUnknown32>
    IUnk* mp;
    void Assign(IUnk* p);  // 0x00b5f950
};

static inline uint32_t HashStr(const uint16_t* s)
{
    uint32_t h = 0x811c9dc5;
    uint32_t c = *s;
    while (c != 0) {
        h = h * 0x1000193 ^ c;
        s++;
        c = *s;
    }
    return h;
}

// ---------------------------------------------------------------------------
// ResourceCache (intrusive hash map + LRU list)
// ---------------------------------------------------------------------------
struct LRUEntry;
struct CacheEntry {
    CacheEntry* next;       // +0
    const uint16_t* mKey;   // +4
    unsigned mDataSize;     // +8
    ARC mpData;             // +0xc
    LRUEntry* mpListEntry;  // +0x10
};
struct LRUEntry {
    LRUEntry* mpNext;       // +0
    LRUEntry* mpPrev;       // +4
    CacheEntry* mpCacheEntry; // +8
};
struct IterC {  // iterator
    CacheEntry* node;
    CacheEntry** slot;
};
struct IterR {  // iterator + inserted flag
    CacheEntry* node;
    CacheEntry** slot;
    uint8_t inserted;
};
struct IHTable {
    CacheEntry* mBucketArray[65];
    unsigned mnElementCount;
    IHTable()
    {
        mnElementCount = 0;
        memset(this, 0, 0x100);
        mBucketArray[64] = (CacheEntry*)-1;
    }
    CacheEntry* DoFindNode(CacheEntry* head, const uint16_t* const* key);  // 0x008fe430
    IterR* DoInsertValue(IterR* out, CacheEntry* node, TagT);
    void erase(const uint16_t* const* key);                                 // 0x008fe510
    void find(IterC* out, const uint16_t* const* key);                      // 0x008fe490
    void insert(IterC* out, CacheEntry* e);                                 // 0x008fe970
};

static inline const uint16_t* const& ExtractKey(CacheEntry& e) { return e.mKey; }

// @ 0x008fe610
IterR* IHTable::DoInsertValue(IterR* out, CacheEntry* node, TagT)
{
    const uint16_t* const& k = ExtractKey(*node);
    const uint16_t* const* pk = &k;
    const uint16_t* s = k;
    uint32_t h = 0x811c9dc5;
    uint32_t c = *s;
    while (c != 0) {
        s++;
        h = h * 0x1000193 ^ c;
        c = *s;
    }
    CacheEntry** slot = &mBucketArray[h & 0x3f];
    CacheEntry* head = *slot;
    CacheEntry* found = DoFindNode(head, pk);
    if (found == 0) {
        node->next = head;
        *slot = node;
        mnElementCount += 1;
        out->slot = slot;
        out->node = node;
        out->inserted = 1;
        return out;
    }
    out->slot = slot;
    out->node = found;
    out->inserted = 0;
    return out;
}

struct ResourceCache {
    IAlloc* mpAllocator;       // +0
    unsigned mSize;            // +4
    unsigned mMaxSize;         // +8
    unsigned mMaxEntrySize;    // +0xc
    uint16_t mMaxEntryFraction;// +0x10
    IHTable mMap;              // +0x14
    char pad[0x120 - 0x14 - sizeof(IHTable)];
    ListHdr mLRUList;          // +0x120

    ResourceCache(IAlloc* a, unsigned maxSize, uint16_t frac);
    void Remove(CacheEntry* e);
    void Clear();
    IUnk* Find(const uint16_t* key);
    bool Insert(const uint16_t* key, IUnk* data, unsigned size);
};

// @ 0x008fe830
ResourceCache::ResourceCache(IAlloc* a, unsigned maxSize, uint16_t frac)
    : mpAllocator(a), mSize(0), mMaxSize(maxSize), mMaxEntryFraction(frac)
{
    if (mMaxEntryFraction == 0)
        mMaxEntrySize = 0;
    else
        mMaxEntrySize = mMaxSize / mMaxEntryFraction;
}

// @ 0x008fe8b0
void ResourceCache::Remove(CacheEntry* e)
{
    mMap.erase(&e->mKey);
    LRUEntry* le = e->mpListEntry;
    LRUEntry* prev = le->mpPrev;
    LRUEntry* next = le->mpNext;
    prev->mpNext = next;
    next->mpPrev = prev;
    le->mpNext = 0;
    le->mpPrev = 0;
    mpAllocator->Free((void*)e->mKey, 0);
    IUnk* d = e->mpData.mp;
    if (d) {
        e->mpData.mp = 0;
        d->Release();
    }
    mSize -= e->mDataSize;
    if (e->mpData.mp)
        e->mpData.mp->Release();
    operator_delete__(e);
}

// @ 0x008feae0
void ResourceCache::Clear()
{
    memset(&mMap, 0, 0x100);
    mMap.mnElementCount = 0;
    while (*(void**)((char*)&mLRUList + 4) != &mLRUList) {
        LRUEntry* le = (LRUEntry*)mLRUList.mpNext;
        mpAllocator->Free((void*)le->mpCacheEntry->mKey, 0);
        CacheEntry* ce = le->mpCacheEntry;
        IUnk* d = ce->mpData.mp;
        if (d) {
            ce->mpData.mp = 0;
            d->Release();
        }
        ce = le->mpCacheEntry;
        if (ce) {
            if (ce->mpData.mp)
                ce->mpData.mp->Release();
            operator_delete__(ce);
        }
        LRUEntry* first = (LRUEntry*)mLRUList.mpNext;
        ((LRUEntry*)first->mpNext)->mpPrev = (LRUEntry*)&mLRUList;
        mLRUList.mpNext = first->mpNext;
        if (first != (LRUEntry*)&mLRUList) {
            first->mpPrev = 0;
            first->mpNext = 0;
        }
        operator_delete__(le);
    }
    mSize = 0;
}

// @ 0x008feba0
IUnk* ResourceCache::Find(const uint16_t* key)
{
    IterC it;
    mMap.find(&it, &key);
    if (it.node == mMap.mBucketArray[64])
        return 0;
    void* pos;
    FindInl(&mLRUList, &pos, it.node->mpListEntry);
    SpliceInl(mLRUList.mpNext, pos);
    return it.node->mpData.mp;
}

// @ 0x008fec20
bool ResourceCache::Insert(const uint16_t* key, IUnk* data, unsigned size)
{
    if (size == 0 || key == 0)
        return false;
    bool inserted = false;
    IterC it;
    mMap.find(&it, &key);
    if (size > mMaxEntrySize) {
        if (it.node != mMap.mBucketArray[64])
            Remove(it.node);
        return inserted;
    }
    if (it.node == mMap.mBucketArray[64]) {
        CacheEntry* e = (CacheEntry*)mpAllocator->Alloc(0x14, "ResourceProvider/ResourceCacheEntry", 0, 4, 0);
        CacheEntry* ce = 0;
        if (e) {
            e->mpData.mp = 0;
            ce = e;
        }
        LRUEntry* l = (LRUEntry*)mpAllocator->Alloc(0xc, "ResourceProvider/LRUListEntry", 0, 4, 0);
        LRUEntry* le = 0;
        if (l) {
            l->mpPrev = 0;
            l->mpNext = 0;
            le = l;
        }
        le->mpCacheEntry = ce;
        ce->mpListEntry = le;
        ce->mKey = key;
        ce->mpData.Assign(data);
        ce->mDataSize = size;
        mMap.insert(&it, ce);
        le->mpNext = (LRUEntry*)mLRUList.mpNext;
        le->mpPrev = (LRUEntry*)&mLRUList;
        mLRUList.mpNext = le;
        le->mpNext->mpPrev = le;
        mSize += ce->mDataSize;
        inserted = true;
    } else {
        CacheEntry* e = it.node;
        mSize += size - e->mDataSize;
        e->mDataSize = size;
        e->mpData.Assign(data);
        void* found;
        mLRUList.Find(&found, e->mpListEntry);
        Splice(mLRUList.mpNext, &mLRUList, found);
    }
    while (mSize > mMaxSize)
        Remove(((LRUEntry*)mLRUList.mpPrev)->mpCacheEntry);
    return inserted;
}

// ---------------------------------------------------------------------------
// string-keyed hash map (node: key@0, value-array@8, next@0x1c)
// ---------------------------------------------------------------------------
struct SNode {
    const uint16_t* key;   // +0
    char pad4[4];
    void* arr;             // +8
    char pad[0x1c - 0xc];
    SNode* next;           // +0x1c
};
struct SIter {
    SNode* node;
    SNode** slot;
};
struct SMap {
    int unk0;
    SNode** mBuckets;      // +4
    unsigned mBucketCount; // +8
    unsigned mCount;       // +0xc
    SNode* DoFindNode(SNode* head, const uint16_t* const* key, uint32_t hash);  // 0x008fe7e0
    void find(SIter* out, const uint16_t* const* key);
    SIter* erase(SIter* out, SNode* n, SNode** slot);
};

// @ 0x008fe7e0
SNode* SMap::DoFindNode(SNode* node, const uint16_t* const* key, uint32_t hash)
{
    (void)hash;
    while (node) {
        const uint16_t* b = node->key;
        const uint16_t* a = *key;
        while (*a != 0 && *a == *b) {
            a++;
            b++;
        }
        if (*a == *b)
            return node;
        node = node->next;
    }
    return 0;
}

// @ 0x008fe9a0
void SMap::find(SIter* out, const uint16_t* const* key)
{
    uint32_t h = HashStr(*key);
    unsigned n = mBucketCount;
    unsigned idx = h % n;
    SNode** b = mBuckets;
    SIter it;
    SNode* f = DoFindNode(b[idx], key, h);
    if (f) {
        it.node = f;
        it.slot = &b[idx];
    } else {
        it.node = b[n];
        it.slot = &b[n];
    }
    *out = it;
}

// @ 0x008ff3c0
SIter* SMap::erase(SIter* out, SNode* n, SNode** slot)
{
    SNode* nx = n->next;
    out->slot = slot;
    out->node = nx;
    while (nx == 0) {
        out->slot = out->slot + 1;
        nx = *out->slot;
        out->node = nx;
    }
    SNode* cur = *slot;
    if (cur == n) {
        *slot = cur->next;
    } else {
        SNode* p = cur->next;
        while (p != n) {
            cur = p;
            p = p->next;
        }
        cur->next = p->next;
    }
    void* arr = n->arr;
    if (arr && ((int*)arr)[-1] != 0)
        operator_delete__(arr);
    operator_delete__(n);
    mCount -= 1;
    return out;
}

// ---------------------------------------------------------------------------
// protocol-handler map (wchar_t const* -> wchar_t const*/handler), node: pair + next@8
// ---------------------------------------------------------------------------
struct PIter {
    HNode* node;
    HNode** slot;
    uint8_t inserted;
};
struct RehashR {
    uint8_t rehash;
    unsigned newCount;
};
struct RehashPolicy {
    void GetRehashRequired(RehashR* r, unsigned buckets, unsigned elems, unsigned add);  // 0x00921440
};
struct PMap {
    int unk0;
    HNode** mBuckets;      // +4
    unsigned mBucketCount; // +8
    unsigned mCount;       // +0xc
    RehashPolicy mPolicy;  // +0x10
    HNode* DoFindNode(HNode* head, SrcNode* key, uint32_t hash);  // 0x005d6a90
    HNode* AllocNode(SrcNode* s);                                  // 0x008fea30
    void DoRehash(unsigned n);                                     // 0x008fbac0
    void find(PIter* out, const uint16_t* const* key);             // 0x008fbbf0
    PIter* DoInsertValue(PIter* out, SrcNode* key, TagT);
    unsigned erase(const uint16_t* const* key);
};

// @ 0x008fedb0
PIter* PMap::DoInsertValue(PIter* out, SrcNode* kv, TagT)
{
    uint32_t h = HashStr(*(const uint16_t* const*)kv);
    unsigned n = mBucketCount;
    unsigned idx = h % n;
    HNode** slot = &mBuckets[idx];
    HNode* found = DoFindNode(*slot, kv, h);
    if (found == 0) {
        RehashR r;
        mPolicy.GetRehashRequired(&r, n, mCount, 1);
        HNode* node = AllocNode(kv);
        if (r.rehash) {
            idx = h % r.newCount;
            DoRehash(r.newCount);
        }
        int off = idx * 4;
        node->p8 = *(HNode**)((char*)mBuckets + off);
        *(HNode**)((char*)mBuckets + off) = node;
        mCount++;
        HNode** bk = mBuckets;
        out->node = node;
        out->slot = (HNode**)((char*)bk + off);
        out->inserted = 1;
        return out;
    }
    out->node = found;
    out->slot = slot;
    out->inserted = 0;
    return out;
}

static __forceinline bool StrEqW(const uint16_t* a, const uint16_t* b)
{
    uint16_t c = *a;
    while (c != 0 && c == *b) {
        const uint16_t* n = a + 1;
        a++;
        b++;
        c = *n;
    }
    return *a == *b;
}

// @ 0x008fefb0
unsigned PMap::erase(const uint16_t* const* key)
{
    const uint16_t* k = *key;
    uint32_t h = HashStr(k);
    unsigned idx = h % mBucketCount;
    unsigned n0 = mCount;
    HNode** slot = &mBuckets[idx];
    if (*slot != 0) {
        for (;;) {
            HNode* node = *slot;
            if (StrEqW(k, (const uint16_t*)node->p0))
                break;
            slot = (HNode**)&node->p8;
            if (node->p8 == 0)
                break;
        }
        while (*slot != 0) {
            HNode* node = *slot;
            if (!StrEqW(*key, (const uint16_t*)node->p0))
                break;
            *slot = (HNode*)node->p8;
            if (node->p4)
                node->p4->v2();
            operator_delete__(node);
            mCount += -1;
        }
    }
    return n0 - mCount;
}

// ---------------------------------------------------------------------------
// handler-list interface used by 008ff270
// ---------------------------------------------------------------------------
struct IHandlerList {
    virtual void v0();
    virtual void AddRef();       // +4
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual unsigned GetCount();             // +0x18
    virtual const uint16_t* GetAt(unsigned); // +0x1c
    virtual void Done(void* ctx);            // +0x20
};
struct KV {
    const uint16_t* key;
    IHandlerList* val;
};
struct KV2 {  // pair whose value is refcounted via vt+8
    const uint16_t* key;
    RCObjN* val;
};

struct HolderMap {
    char pad[0x264];
    PMap map;   // +0x264
    void* Resolve(const uint16_t* s);  // 0x008feef0
    void Register(IHandlerList* l, bool add);  // 0x008ff270
};

struct Alloc4 { int x; };
struct WStr2 {  // eastl::basic_string<wchar_t> with fixed buffer
    uint16_t* b;
    uint16_t* e;
    uint16_t* c;
    int alloc;
    WStr2(const uint16_t* f, const uint16_t* l, const Alloc4&);  // 0x00630750
};
const uint16_t* __cdecl CharTypeFindFirstOf(const uint16_t* f, const uint16_t* l, const uint16_t* a, const uint16_t* b);
extern const uint16_t gSep1[];  // 0x01430254
extern const uint16_t gSep2[];  // 0x01430258

// @ 0x008feef0
void* HolderMap::Resolve(const uint16_t* s)
{
    const uint16_t* end = s + 0x40;
    const uint16_t* p = CharTypeFindFirstOf(s, end, gSep1, gSep2);
    if (p != end && *p == ':') {
        Alloc4 t;
        WStr2 str(s, p, t);
        const uint16_t* key = str.b;
        PIter it;
        map.find((PIter*)&it, &key);
        if (it.node == map.mBuckets[map.mBucketCount]) {
            if (((int)((char*)str.c - (char*)str.b) & ~1) > 2 && str.b)
                operator_delete__(str.b);
            return 0;
        }
        void* r = it.node->p4;
        if (((int)((char*)str.c - (char*)str.b) & ~1) > 2 && str.b)
            operator_delete__(str.b);
        return r;
    }
    return 0;
}

// @ 0x008ff270
void HolderMap::Register(IHandlerList* l, bool add)
{
    if (l) {
        unsigned n = l->GetCount();
        for (unsigned i = 0; i < n; i++) {
            const uint16_t* k = l->GetAt(i);
            if (add) {
                KV2 kv;
                kv.key = k;
                kv.val = (RCObjN*)l;
                ((IHandlerList*)kv.val)->AddRef();
                PIter r;
                map.DoInsertValue(&r, (SrcNode*)&kv, TagT());
                if (kv.val)
                    kv.val->v2();
            } else {
                map.erase(&k);
            }
        }
        l->Done(this);
    }
}

// ---------------------------------------------------------------------------
// vector / provider helpers
// ---------------------------------------------------------------------------
struct VBase {
    void* mpBegin;
    void* mpEnd;
    void* mpCap;
    void AllocInit(unsigned n, void* alloc);   // 0x008fea80
};
struct VObj {
    void* x;        // +0
    VBase v;        // +4
    char alloc[4];  // +0x10
    VObj* CopyCtor(VObj* src);
};
void __cdecl EastlCopy(void** out, void* first, void* last, void* dst, void* tag);  // 0x0076ffd0

// @ 0x008ff0b0
VObj* VObj::CopyCtor(VObj* src)
{
    x = src->x;
    v.AllocInit(((char*)src->v.mpEnd - (char*)src->v.mpBegin) >> 3, &src->alloc);
    EastlCopy((void**)&src, src->v.mpBegin, src->v.mpEnd, v.mpBegin, src);
    v.mpEnd = src;
    return this;
}

struct VOut {
    void* a;
    void* b;
    VBase v;   // +8
    void* end; // +0xc is v.mpEnd
};

// @ 0x008ff450
VOut* __cdecl BuildVec(VOut* out, void* a2, void* a3, char* begin, char* end, int a6, int alloc7)
{
    VOut* o = out;
    out->a = a2;
    out->b = a3;
    o->v.AllocInit((end - begin) >> 3, &alloc7);
    EastlCopy((void**)&out, begin, end, o->v.mpBegin, out);
    o->v.mpEnd = out;
    if (begin && ((int*)begin)[-1] != 0)
        operator_delete__(begin);
    return o;
}

// ---------------------------------------------------------------------------
// ResourceProvider
// ---------------------------------------------------------------------------
struct CreateCtx;
struct IFactory {
    virtual void v0();
    virtual int Create(unsigned a, unsigned b, CreateCtx* c);
};
struct ILogger {
    virtual void v0();
    virtual void Report(unsigned code, unsigned id, int a, int b, const uint16_t* msg);
};
struct CreateCtx {
    char pad[8];
    ILogger* log;       // +8
    unsigned id;        // +0xc
    const char* mime;   // +0x10
    const char* mimeEnd;// +0x14
};
struct WS {
    uint16_t* b;
    uint16_t* e;
    uint16_t* c;
    int alloc;
    void Assign(const uint16_t* f, const uint16_t* l);  // 0x00423650
};
void __cdecl WStr_Format(WS* s, const wchar_t* fmt, const char* arg);  // 0x0041e050
extern uint16_t gEmptyStr[2];          // 0x01667bac
extern const uint16_t gDefaultMsg[];   // 0x01439fe4

struct ResourceProvider {
    char pad[0xc];
    IFactory** mBegin;  // +0xc
    IFactory** mEnd;    // +0x10
    int CreateResource(unsigned a, unsigned b, CreateCtx* c);
};

// @ 0x008ff170
int ResourceProvider::CreateResource(unsigned a, unsigned b, CreateCtx* c)
{
    for (IFactory** p = mBegin; p != mEnd; ++p) {
        int r = (*p)->Create(a, b, c);
        if (r != 3)
            return r;
    }
    if (c->log) {
        WS s;
        s.b = gEmptyStr;
        s.e = gEmptyStr;
        s.c = gEmptyStr + 1;
        if (c->mime != c->mimeEnd) {
            WStr_Format(&s, L"MIME Type: %hs\n", c->mime);
        } else {
            const uint16_t* q = gDefaultMsg;
            do {
                q++;
            } while (*q);
            int n = ((char*)q - (char*)gDefaultMsg) >> 1;
            s.Assign(gDefaultMsg, (const uint16_t*)((char*)gDefaultMsg + n * 2));
        }
        c->log->Report(0x23f0000, c->id, -1, -1, s.b);
        if (((int)((char*)s.c - (char*)s.b) & ~1) > 2 && s.b)
            operator_delete__(s.b);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// sorted vector map<unsigned, WinXHTML*>
// ---------------------------------------------------------------------------
struct UPair {
    unsigned first;
    void* second;
};
UPair* __cdecl LowerBound(UPair* b, UPair* e, unsigned* key, uint8_t flag);  // 0x00d01260
struct UMap {
    char pad[0x124];
    UPair* mpBegin;  // +0x124
    UPair* mpEnd;    // +0x128
    char pad2[0xc];
    uint8_t mFlag;   // +0x138
    void* Find(unsigned key);
};

// @ 0x008ff320
void* UMap::Find(unsigned key)
{
    UPair* e = mpEnd;
    UPair* it = LowerBound(mpBegin, e, &key, mFlag);
    if (it == e || key < it->first)
        it = e;
    else if (it == it + 1)
        it = e;
    if (it != e)
        return it->second;
    return 0;
}

// ---------------------------------------------------------------------------
// vector<AutoRefCount<RCObjN>>
// ---------------------------------------------------------------------------
void __cdecl MoveElems(RCObjN** first, RCObjN** last, RCObjN** dst);       // 0x00d3b3c0
void __cdecl MoveBackward(RCObjN** first, RCObjN** last, RCObjN** dstEnd); // 0x00a690d0
void* __cdecl operator_new_eastl(unsigned n, const char* name, int a, int b, const char* file, int line);

static __forceinline void RelRC(RCObjN* o)
{
    int n = (*(volatile int*)&o->mRef += -1);
    if (n == 0) {
        o->mRef = 1;
        _ReadWriteBarrier();
        o->v0(1);
    }
}

struct RCVec {
    RCObjN** mpBegin;  // +0
    RCObjN** mpEnd;    // +4
    RCObjN** mpCap;    // +8
    char pad[4];
    RCObjN** mpFixed;  // +0x10
    RCObjN** erase(RCObjN** pos);
    void InsertValue(RCObjN** pos, RCObjN** val);
};

// @ 0x008ff370
RCObjN** RCVec::erase(RCObjN** pos)
{
    if (pos + 1 < mpEnd)
        MoveElems(pos + 1, mpEnd, pos);
    mpEnd -= 1;
    RCObjN* o = *mpEnd;
    if (o)
        RelRC(o);
    return pos;
}

// @ 0x008ff4c0
void RCVec::InsertValue(RCObjN** pos, RCObjN** val)
{
    if (mpEnd != mpCap) {
        RCObjN** v = val;
        if (val >= pos && val < mpEnd)
            v = val + 1;
        if (mpEnd) {
            RCObjN* t = mpEnd[-1];
            *mpEnd = t;
            if (t)
                t->mRef += 1;
        }
        MoveBackward(pos, mpEnd - 1, mpEnd);
        RCObjN* nv = *v;
        RCObjN* old = *pos;
        if (nv != old) {
            if (nv)
                nv->mRef += 1;
            *pos = nv;
            if (old)
                RelRC(old);
        }
        mpEnd += 1;
        return;
    }
    unsigned cnt = (unsigned)(mpEnd - mpBegin);
    unsigned newCap;
    if (cnt > 0) {
        newCap = cnt * 2;
    } else {
        newCap = 1;
    }
    RCObjN** nb;
    if (newCap)
        nb = (RCObjN**)operator_new_eastl(newCap * 4, "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    else
        nb = 0;
    int bytes = (char*)pos - (char*)mpBegin;
    RCObjN** p = (RCObjN**)memcpy(nb, mpBegin, bytes);
    p = p + (bytes >> 2);
    if (p) {
        RCObjN* t = *val;
        *p = t;
        if (t)
            t->mRef += 1;
    }
    int bytes2 = (char*)mpEnd - (char*)pos;
    RCObjN** q = (RCObjN**)memcpy(p + 1, pos, bytes2);
    RCObjN** ne = q + (bytes2 >> 2);
    if (mpBegin && mpBegin != mpFixed)
        operator_delete__(mpBegin);
    mpBegin = nb;
    mpEnd = ne;
    mpCap = nb + newCap;
}
