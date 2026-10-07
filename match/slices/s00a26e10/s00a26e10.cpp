// Slice s00a26e10: EASTL container instances and resource/voice factory helpers (Audio / UTFWin region).
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"
#include <new>
#include <string.h>
#include <stdarg.h>
#include <intrin.h>

#define EASTL_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

void* eaNew(size_t size, const char* name, int flags, unsigned dbgFlags, const char* file, int line);   // 0x00f473a0
void* operator new(size_t size, const char* name, int a, int b, int c, int d);                           // 0x00f473a0 (new-expression form)
void  operator delete(void*);                                                                           // 0x00f47380

template <class T> static inline T& fld(void* p, int off) { return *(T*)((char*)p + off); }

// ---------------------------------------------------------------------------
// Reference-counted objects: slot 0 = AddRef / deleting dtor, slot 1 = Release (by usage).
struct RefObj {
    virtual void AddRef();
    virtual void Release();
};

// Intrusive counted resource: vtable slot 0 is the deleting destructor, count at +4.
struct CountedRes {
    virtual void Destroy(int flag);
    volatile int mnRefCount;
};
static inline void ReleaseCounted(CountedRes* r)
{
    if (r) {
        int n = (r->mnRefCount += -1);
        if (n == 0) {
            r->mnRefCount = 1;
            r->Destroy(1);
        }
    }
}

// ---------------------------------------------------------------------------
// hashtable<Key4,...>::DoInsertKey (unique insert) for a 16-byte key hashed on words 0 and 2.
struct Key4 { uint32_t a, b, c, d; };
struct KNode { Key4 key; KNode* next; };
struct RehashRes { bool bNeed; uint32_t nNew; };
struct RehashPolicy { void GetRehashRequired(RehashRes* out, uint32_t nBuckets, uint32_t nElems, uint32_t nExtra); };  // 0x00921440
struct InsertRes { KNode* node; KNode** bucket; bool inserted; };

struct KTable {
    void* pad0;
    KNode** mpBuckets;      // +4
    uint32_t mnBuckets;     // +8
    uint32_t mnElements;    // +0xc
    RehashPolicy mPolicy;   // +0x10
    void DoRehash(uint32_t n);                                   // 0x00998870
    void Insert(InsertRes* out, const Key4* k, int tag);         // 0x00a26e10
};

// @ 0x00a26e10
void KTable::Insert(InsertRes* out, const Key4* k, int)
{
    uint32_t h = k->a ^ k->c;
    uint32_t idx = h % mnBuckets;
    KNode** bucket = &mpBuckets[idx];
    for (KNode* n = mpBuckets[idx]; n; n = n->next) {
        if (k->a == n->key.a && k->b == n->key.b && k->c == n->key.c) {
            out->node = n;
            out->inserted = false;
            out->bucket = bucket;
            return;
        }
    }
    RehashRes r;
    mPolicy.GetRehashRequired(&r, mnBuckets, mnElements, 1);
    KNode* nn = (KNode*)eaNew(0x14, "EASTL", 0, 0, EASTL_FILE, 0xd1);
    if (nn) {
        nn->key = *k;
    }
    nn->next = 0;
    if (r.bNeed) {
        idx = h % r.nNew;
        DoRehash(r.nNew);
    }
    nn->next = mpBuckets[idx];
    mpBuckets[idx] = nn;
    mnElements++;
    out->node = nn;
    out->inserted = true;
    out->bucket = &mpBuckets[idx];
}

// ---------------------------------------------------------------------------
// hashtable<Key, pair<Key const, AutoRefCount<Resource>>>::DoFreeNodes
struct ResNode { uint32_t key; CountedRes* value; ResNode* next; };
struct ResTable {
    void DoFreeNodes(ResNode** buckets, uint32_t n);
};
// @ 0x00a26f30
void ResTable::DoFreeNodes(ResNode** buckets, uint32_t n)
{
    for (uint32_t i = 0; i < n; i++) {
        ResNode* node = buckets[i];
        while (node) {
            ResNode* cur = node;
            node = node->next;
            ReleaseCounted(cur->value);
            operator delete(cur);
        }
        buckets[i] = 0;
    }
}

// ---------------------------------------------------------------------------
// Node allocation from a free list (node holds a 16-byte header then a {a,b,c,RefObj*} payload).
struct Payload { uint32_t a, b, c; RefObj* obj; };
struct NodePool {
    char pad[0x18];
    void** mpFree;          // +0x18
    char pad1c[0xc];
    size_t mnNodeSize;      // +0x28
    void* Alloc(const Payload* src);
};
// @ 0x00a27010
void* NodePool::Alloc(const Payload* src)
{
    void** node = mpFree;
    if (node) {
        mpFree = (void**)*node;
    } else {
        node = (void**)eaNew(mnNodeSize, "EASTL", 0, 0, EASTL_FILE, 0xd1);
    }
    Payload* dst = (Payload*)(node + 4);
    if (dst) {
        dst->a = src->a;
        dst->b = src->b;
        dst->c = src->c;
        dst->obj = src->obj;
        if (src->obj) src->obj->AddRef();
    }
    return node;
}

// ---------------------------------------------------------------------------
// Property-list style resource with two fixed-capacity vectors (size 0x47c).
struct EdRes {
    virtual void AddRef();                                  // vtable 0x013eb938 (base)
    virtual void Release();
    virtual ~EdRes() {}
};
struct PropBase : EdRes {                                   // vtable 0x013ebcdc
    long mnRefCount;        // +4
    uint32_t a, b, c;       // +8..+0x10
    PropBase()
    {
        _InterlockedExchange(&mnRefCount, 0);
        a = 0; b = 0; c = 0;
    }
};
struct FixedVec {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    int   pad;
    char* mpLocal;
    ~FixedVec() { if (mpBegin && mpBegin != mpLocal) operator delete(mpBegin); }
};
struct PropList : PropBase {
    FixedVec v1;            // +0x14
    int pad28;
    char buf1[0x168];       // +0x2c
    FixedVec v2;            // +0x194
    int pad1a8;
    char buf2[0x2d0];       // +0x1ac
    PropList();
    virtual void AddRef();                                  // vtable 0x01452b98
    virtual void Release();
    virtual ~PropList();
};
// @ 0x00a270b0
PropList::PropList()
{
    v1.mpLocal = buf1;
    v1.mpEnd = buf1;
    v1.mpBegin = buf1;
    v1.mpCap = buf1 + 0x168;
    v2.mpLocal = buf2;
    v2.mpEnd = buf2;
    v2.mpBegin = buf2;
    v2.mpCap = buf2 + 0x2d0;
}
void PropList::AddRef() {}
void PropList::Release() {}

// @ 0x00a27110   scalar deleting destructor of the property list
PropList::~PropList()
{
    // the two fixed vectors free their heap buffers in their own destructors (v2, then v1)
}

// ---------------------------------------------------------------------------
// EA::Audio::FactoryVoiceTemplate::CreateResource
struct FactoryVoiceTemplate {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool InitResource(int key, PropList* res, int a, int b);     // slot 9 (+0x24)
    bool CreateResource(int key, PropList** out, int a, int b);
};
// @ 0x00a27170
bool FactoryVoiceTemplate::CreateResource(int key, PropList** out, int a, int b)
{
    bool ok = false;
    if (out != 0 && key != 0) {
        PropList* res = new ("audio", 0, 0, 0, 0) PropList();
        if (res) res->AddRef();
        if (InitResource(key, res, a, b)) {
            res->AddRef();
            *out = res;
            ok = true;
        }
        if (res) res->Release();
    }
    return ok;
}

// ---------------------------------------------------------------------------
// Scalar deleting destructor of a class owning one fixed-capacity vector.
struct OwnerBase { virtual ~OwnerBase() {} };               // vtable 0x013ef094
struct OwnedVec {
    char* mpBegin; char pad[0xc]; char* mpLocal;
    ~OwnedVec() { if (mpBegin && mpBegin != mpLocal) operator delete(mpBegin); }
};
struct AbilityList : OwnerBase {
    char pad4[4];
    OwnedVec v;             // +8
    AbilityList();
};
// @ 0x00a27290
AbilityList::AbilityList() {}

// ---------------------------------------------------------------------------
// Hashtable iteration/erase against the style table of a manager object.
struct HIter { void* node; void** bucket; };
struct StyleTable {
    char pad0[4];
    void** mpBuckets;       // +4
    uint32_t mnBuckets;     // +8
    void find(HIter* out, const uint32_t* key) const;       // 0x00645ed0
    HIter erase(HIter it);                                  // 0x00d2c9f0
};
struct StyleNode { uint32_t key; RefObj* value; };
struct StyleMgr {
    virtual void v0();
    char pad[0x119bb4];
    StyleTable mStyles;     // +0x119bb8
};
typedef void (__thiscall* VFn1)(void*, void*);
typedef bool (__thiscall* VFnB)(void*);
#define VSLOT(obj, off) ((*(void***)(obj))[(off) / 4])

// @ 0x00a27340
bool StyleMgr_Remove(StyleMgr* self, uint32_t key)
{
    HIter it;
    self->mStyles.find(&it, &key);
    HIter end; end.node = self->mStyles.mpBuckets[self->mStyles.mnBuckets];
    if (it.node != end.node) {
        void* obj = ((StyleNode*)it.node)->value;
        ((VFn1)VSLOT(self, 0x170))(self, obj);
        bool r = ((VFnB)VSLOT(obj, 0x24))(obj);
        self->mStyles.erase(it);
        return r;
    }
    return false;
}

// @ 0x00a273d0
void StyleMgr_RemoveAll(StyleMgr* self)
{
    void** bucket = self->mStyles.mpBuckets;
    void* node = *bucket;
    if (!node) {
        bucket++;
        node = *bucket;
        while (!node) { bucket++; node = *bucket; }
        node = *bucket;
    }
    void* end = self->mStyles.mpBuckets[self->mStyles.mnBuckets];
    while (node != end) {
        void* obj = ((StyleNode*)node)->value;
        ((VFn1)VSLOT(self, 0x170))(self, obj);
        ((VFnB)VSLOT(obj, 0x24))(obj);
        HIter it; it.node = node; it.bucket = bucket;
        HIter nx = self->mStyles.erase(it);
        bucket = nx.bucket;
        node = nx.node;
    }
}

// ---------------------------------------------------------------------------
// Texture instance lookup: hashtable<Key, pair<Key const, cTextureInstanceInternal*>>
struct TexNode { uint32_t key[3]; void* value; };
struct TexTable {
    char pad0[4];
    void** mpBuckets;       // +4
    uint32_t mnBuckets;     // +8
    void find(HIter* out, const void* key) const;           // 0x00833840
};
struct TexMgr { char pad[0x80424]; TexTable mTex; };
// @ 0x00a27460
void* TexMgr_Find(TexMgr* self, const void* key)
{
    HIter it;
    it.node = 0;
    self->mTex.find(&it, key);
    if (it.node != self->mTex.mpBuckets[self->mTex.mnBuckets]) {
        return ((TexNode*)it.node)->value;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Find-or-insert in hashtable<uint, pair<uint, AutoRefCount<X>>>; returns the mapped value slot.
struct MapNode { uint32_t key; CountedRes* value; };
struct RefMap {
    char pad0[4];
    void** mpBuckets;       // +4
    uint32_t mnBuckets;     // +8
    void find(HIter* out, const uint32_t* key) const;       // 0x00645ed0
    void Insert(HIter* out, const MapNode* v, int tag);     // 0x00a23830
    CountedRes** FindOrInsert(const uint32_t* key);
};
// @ 0x00a27530
CountedRes** RefMap::FindOrInsert(const uint32_t* key)
{
    HIter it;
    find(&it, key);
    if (it.node != mpBuckets[mnBuckets]) {
        return &((MapNode*)it.node)->value;
    }
    MapNode v;
    v.key = *key;
    v.value = 0;
    int tag = 0;
    HIter res;
    Insert(&res, &v, tag);
    CountedRes** slot = &((MapNode*)res.node)->value;
    ReleaseCounted(v.value);
    return slot;
}

// ---------------------------------------------------------------------------
// hashtable::erase(iterator) for nodes {..., value at +0xc, next at +0x10}.
struct ENode { uint32_t pad[3]; RefObj* value; ENode* next; };
struct ETable {
    char pad0[4];
    void** mpBuckets;       // +4
    uint32_t mnBuckets;     // +8
    uint32_t mnElements;    // +0xc
    HIter* erase(HIter* out, ENode* node, ENode** bucket);
};
// @ 0x00a27660
HIter* ETable::erase(HIter* out, ENode* node, ENode** bucket)
{
    out->bucket = (void**)bucket;
    out->node = node->next;
    while (out->node == 0) {
        out->bucket = (void**)((char*)out->bucket + 4);
        out->node = *(void**)out->bucket;
    }
    ENode* cur = *bucket;
    if (cur == node) {
        *bucket = cur->next;
    } else {
        ENode* nx = cur->next;
        while (nx != node) {
            cur = nx;
            nx = nx->next;
        }
        cur->next = nx->next;
    }
    if (node->value) node->value->Release();
    operator delete(node);
    mnElements--;
    return out;
}

// ---------------------------------------------------------------------------
// fixed hashtable<uint, pair<uint, Subscription>>::DoFreeNodes
struct SubNode { void* link; uint32_t key; void* pad; char* sub; SubNode* next; };
struct SubTable {
    char pad[0x1c];
    SubNode* mpFreeList;    // +0x1c
    char pad20[4];
    char* mpPoolBegin;      // +0x24
    char* mpPoolEnd;        // +0x28
    char pad2c[4];
    SubNode* mpInline;      // +0x30
    void DoFreeNodes(SubNode** buckets, uint32_t n);
};
// @ 0x00a276e0
void SubTable::DoFreeNodes(SubNode** buckets, uint32_t n)
{
    for (uint32_t i = 0; i < n; i++) {
        SubNode* node = buckets[i];
        while (node) {
            SubNode* cur = node;
            node = node->next;
            if (cur->sub) {
                RefObj* r = (RefObj*)(cur->sub + 4);
                r->Release();
            }
            if (cur != mpInline) {
                if ((char*)cur < mpPoolBegin || (char*)cur >= mpPoolEnd) {
                    operator delete(cur);
                } else {
                    *(SubNode**)cur = mpFreeList;
                    mpFreeList = cur;
                }
            }
        }
        buckets[i] = 0;
    }
}

// ---------------------------------------------------------------------------
// eastl::vector<AutoRefCount<T>, fixed_vector_allocator>::DoInsertValue
struct RcPtr {                                              // AutoRefCount<T>
    RefObj* p;
    RcPtr() : p(0) {}
    RcPtr(const RcPtr& o) : p(o.p) { if (p) p->AddRef(); }
    ~RcPtr() { if (p) p->Release(); }
    RcPtr& operator=(const RcPtr& o)
    {
        if (p != o.p) {
            RefObj* old = p;
            p = o.p;
            if (p) p->AddRef();
            if (old) old->Release();
        }
        return *this;
    }
};
RcPtr* CopyBackwardRc(RcPtr* first, RcPtr* last, RcPtr* destEnd);     // 0x00ac97a0 (cdecl)
void* memcpy_11e0744(void* dst, const void* src, size_t n);           // 0x011e0744 (memcpy)

struct RcVector {
    RcPtr* mpBegin;
    RcPtr* mpEnd;
    RcPtr* mpCap;
    void DoInsertValue(RcPtr* pos, const RcPtr* value);
};
// @ 0x00a27760
void RcVector::DoInsertValue(RcPtr* pos, const RcPtr* value)
{
    if (mpEnd != mpCap) {
        const RcPtr* pv = value;
        if (pv >= pos && pv < mpEnd) ++pv;
        ::new (mpEnd) RcPtr(*(mpEnd - 1));
        CopyBackwardRc(pos, mpEnd - 1, mpEnd);
        *pos = *pv;
        ++mpEnd;
    } else {
        size_t nPrev = mpEnd - mpBegin;
        size_t nNew = nPrev ? nPrev * 2 : 1;
        RcPtr* pNew = nNew ? (RcPtr*)eaNew(nNew * sizeof(RcPtr), "EASTL", 0, 0, EASTL_FILE, 0xd1) : 0;
        size_t nBefore = (char*)pos - (char*)mpBegin;
        RcPtr* pNewPos = (RcPtr*)memcpy_11e0744(pNew, mpBegin, nBefore) + nBefore / sizeof(RcPtr);
        ::new (pNewPos) RcPtr(*value);
        size_t nAfter = (char*)mpEnd - (char*)pos;
        RcPtr* pNewEnd = (RcPtr*)memcpy_11e0744(pNewPos + 1, pos, nAfter) + nAfter / sizeof(RcPtr);
        if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
        mpEnd = pNewEnd;
        mpBegin = pNew;
        mpCap = pNew + nNew;
    }
}

// ---------------------------------------------------------------------------
// eastl::vector<12-byte POD, fixed allocator>::DoInsertValue
struct Rec12 { uint32_t a, b, c; };
Rec12* RelocateRec12(Rec12* first, Rec12* last, Rec12* dest);         // 0x00a11310 (cdecl)
struct Rec12Vector {
    Rec12* mpBegin;
    Rec12* mpEnd;
    Rec12* mpCap;
    char pad[4];
    Rec12* mpFixed;         // +0x10
    void DoInsertValue(Rec12* pos, const Rec12* value);
};
// @ 0x00a27910
void Rec12Vector::DoInsertValue(Rec12* pos, const Rec12* value)
{
    if (mpEnd != mpCap) {
        const Rec12* pv = value;
        if (pv >= pos && pv < mpEnd) ++pv;
        if (mpEnd) *mpEnd = mpEnd[-1];
        Rec12* last = mpEnd - 1;
        Rec12* dst = mpEnd;
        while (last != pos) {
            --last;
            --dst;
            *dst = *last;
        }
        *pos = *pv;
        ++mpEnd;
    } else {
        size_t nPrev = mpEnd - mpBegin;
        size_t nNew = nPrev ? nPrev * 2 : 1;
        Rec12* pNew = nNew ? (Rec12*)eaNew(nNew * sizeof(Rec12), "EASTL", 0, 0, EASTL_FILE, 0xd1) : 0;
        Rec12* pNewEnd = RelocateRec12(mpBegin, pos, pNew);
        if (pNewEnd) *pNewEnd = *value;
        pNewEnd = RelocateRec12(pos, mpEnd, pNewEnd + 1);
        if (mpBegin && mpBegin != mpFixed) operator delete(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCap = pNew + nNew;
    }
}

// ---------------------------------------------------------------------------
// eastl::vector<24-byte POD, fixed allocator>::DoInsertValue
struct Rec24 { uint32_t d[6]; };
Rec24* CopyBackwardRec24(Rec24* first, Rec24* last, Rec24* destEnd);   // 0x00cc8b50 (cdecl)
Rec24* RelocateRec24(Rec24* first, Rec24* last, Rec24* dest);          // 0x00720200 (cdecl)
struct Rec24Vector {
    Rec24* mpBegin;
    Rec24* mpEnd;
    Rec24* mpCap;
    char pad[4];
    Rec24* mpFixed;         // +0x10
    void DoInsertValue(Rec24* pos, const Rec24* value);
};
// @ 0x00a27a40
void Rec24Vector::DoInsertValue(Rec24* pos, const Rec24* value)
{
    if (mpEnd != mpCap) {
        const Rec24* pv = value;
        if (pv >= pos && pv < mpEnd) ++pv;
        if (mpEnd) *mpEnd = mpEnd[-1];
        CopyBackwardRec24(pos, mpEnd - 1, mpEnd);
        *pos = *pv;
        ++mpEnd;
    } else {
        size_t nPrev = mpEnd - mpBegin;
        size_t nNew = nPrev ? nPrev * 2 : 1;
        Rec24* pNew = nNew ? (Rec24*)eaNew(nNew * sizeof(Rec24), "EASTL", 0, 0, EASTL_FILE, 0xd1) : 0;
        Rec24* pNewEnd = RelocateRec24(mpBegin, pos, pNew);
        if (pNewEnd) *pNewEnd = *value;
        pNewEnd = RelocateRec24(pos, mpEnd, pNewEnd + 1);
        if (mpBegin && mpBegin != mpFixed) operator delete(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCap = pNew + nNew;
    }
}

// ---------------------------------------------------------------------------
// eastl::vector<tInstrumentZone (44 bytes), sp_vector_allocator>::DoInsertValue
struct Zone { uint32_t d[11]; };
Zone* RelocateZone(Zone* first, Zone* last, Zone* dest);               // 0x00b3d890 (cdecl)
struct ZoneVector {
    Zone* mpBegin;
    Zone* mpEnd;
    Zone* mpCap;
    void DoInsertValue(Zone* pos, const Zone* value);
};
// @ 0x00a27b90
void ZoneVector::DoInsertValue(Zone* pos, const Zone* value)
{
    if (mpEnd != mpCap) {
        const Zone* pv = value;
        if (pv >= pos && pv < mpEnd) ++pv;
        if (mpEnd) *mpEnd = mpEnd[-1];
        Zone* last = mpEnd - 1;
        Zone* dst = mpEnd;
        while (last != pos) {
            --last;
            --dst;
            *dst = *last;
        }
        *pos = *pv;
        ++mpEnd;
    } else {
        size_t nPrev = mpEnd - mpBegin;
        size_t nNew = nPrev ? nPrev * 2 : 1;
        Zone* pNew = nNew ? (Zone*)eaNew(nNew * sizeof(Zone), "EASTL", 0, 0, EASTL_FILE, 0xd1) : 0;
        Zone* pNewEnd = RelocateZone(mpBegin, pos, pNew);
        if (pNewEnd) *pNewEnd = *value;
        pNewEnd = RelocateZone(pos, mpEnd, pNewEnd + 1);
        if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
        mpEnd = pNewEnd;
        mpBegin = pNew;
        mpCap = pNew + nNew;
    }
}

// ---------------------------------------------------------------------------
// map<uint, pair<uint, int>>: bump a per-key counter, inserting {key, 1} when absent.
struct CountNode { char pad[0x14]; int count; };   // rbtree node: value.second at +0x14
struct CountPair { uint32_t key; int count; CountPair(uint32_t k, int c) : key(k), count(c) {} };
struct CountTrueType {};  // eastl::true_type: empty tag passed by value
struct CountTree {
    void find(HIter* out, const uint32_t* key);                            // 0x00e5c780
    HIter findv(const uint32_t& key) { HIter r; find(&r, &key); return r; }
    HIter Insert(const CountPair& v, CountTrueType tag);                   // 0x00a246c0
    HIter insert(const CountPair& v) { return Insert(v, CountTrueType()); }
};
struct CountMap {
    char pad0[4];
    CountTree mTree;        // +4
    char pad_anchor[4];     // +8 is the tree anchor node address
    bool AddRef(uint32_t key);
};
// @ 0x00a27e60
bool CountMap::AddRef(uint32_t key)
{
    CountNode* n = (CountNode*)mTree.findv(key).node;
    if ((char*)this + 8 == (char*)n) {
        mTree.insert(CountPair(key, 1));
        return true;
    }
    n->count++;
    return true;
}

// ---------------------------------------------------------------------------
// EA::Audio::Submix::ConnectToSubmix
extern char g_EmptyStrRep[];            // 0x01667bac
struct EStr {
    char* mpBegin; char* mpEnd; char* mpCap;
    struct Alloc {} mAllocator;         // eastl::allocator (empty)
    const char* c_str() const { return mpBegin; }
    EStr() : mpBegin(g_EmptyStrRep), mpEnd(g_EmptyStrRep), mpCap(g_EmptyStrRep + 1) {}
    ~EStr() { if (mpCap - mpBegin > 1 && mpBegin) operator delete(mpBegin); }
    void sprintf(const char* fmt, ...);                                    // 0x00472fe0 (cdecl, this pushed)
};
struct LockObj { void Lock(); void Unlock(); };                            // 0x0112c600 / 0x0112c620
extern LockObj* g_pAudioLock;           // 0x016e61a8
struct AudioLockGuard {
    AudioLockGuard() { if (g_pAudioLock) g_pAudioLock->Lock(); }
    ~AudioLockGuard() { if (g_pAudioLock) g_pAudioLock->Unlock(); }
};
struct VoiceContainer {
    void* FindPlugin(uint32_t id);                                         // 0x00a34230
    bool ConnectToSubmix(void* submixVoice, int flag);                     // 0x00a34b50
};
struct Plugin { void SetName(int a, const char* const& name); };                 // 0x0112ccc0
struct Submix {
    char pad0[0x10];
    VoiceContainer mVoiceContainer;     // +0x10
    char pad_988[0x977];
    const char* mpName;                 // +0x988
    bool ConnectToSubmix(Submix* other);
};
// @ 0x00a27ed0
bool Submix::ConnectToSubmix(Submix* other)
{
    if (!other) return false;
    AudioLockGuard lock;
    Plugin* plugin = (Plugin*)mVoiceContainer.FindPlugin(0x41695730);
    if (plugin) {
        EStr s;
        s.sprintf("%s.aiff", mpName);
        plugin->SetName(0, s.c_str());
    }
    return mVoiceContainer.ConnectToSubmix(fld<void*>(other, 0x970), 0);
}

// ---------------------------------------------------------------------------
// Register an event once: look it up in the hashtable, otherwise ask the owner to create it.
struct EvTable {
    char pad0[4];
    void** mpBuckets;       // +4
    uint32_t mnBuckets;     // +8
    void find(HIter* out, const uint32_t* key);                            // 0x00a23ef0
    void Insert(HIter* out, const uint32_t* v, int tag);                   // 0x00a26be0
};
struct EvOwner {
    virtual void v0();
    char pad[0x13795c - 4];
    EvTable mEvents;        // +0x13795c
    bool Register(uint32_t a1, uint32_t a2, void* a3, double a4);
};
// This type's virtual slots 0x94 / 0x98 are called below.
typedef bool (__thiscall* VCreate)(void*, uint32_t, uint32_t, void*, int, RefObj**);
typedef void (__thiscall* VNotify)(void*, uint32_t, int);
typedef bool (__thiscall* VFire)(void*, double);
// @ 0x00a27ff0
bool EvOwner_Register(EvOwner* self, uint32_t a1, uint32_t a2, void* a3, double a4)
{
    HIter it;
    EvTable& t = self->mEvents;
    void* end = t.mpBuckets[t.mnBuckets];
    t.find(&it, &a1);
    if (it.node != end) return false;
    RefObj* created = 0;
    bool ok = ((VCreate)VSLOT(self, 0x94))(self, a1, a2, a3, 0, &created);
    if (!ok) {
        HIter res;
        t.Insert(&res, &a1, 0);
        ((VNotify)VSLOT(self, 0x98))(self, a2, 1);
        if (created) created->Release();
        return false;
    }
    bool fired = ((VFire)VSLOT(created, 0x14))(created, a4);
    if (fired) {
        if (created) created->Release();
        return true;
    }
    if (created) created->Release();
    return false;
}
