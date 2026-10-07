// Spore decompilation - batch bfs4, slice s008ff610 (0x008FF610..0x00900400).
// EA::XHTML::Resource::ResourceProvider request management + ResourceRequest.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE2
#include <string.h>
#include <new>
#include <intrin.h>
#include "types.h"

void __cdecl operator_delete__(void* p);
void* __cdecl operator_new(unsigned n, const char* name, int a, int b, const char* file, int line);
struct IAlloc {
    virtual void v0();
    virtual void* Alloc(unsigned sz, const char* name, unsigned flags, unsigned align, unsigned off);
    virtual void* AllocSimple(unsigned sz, const char* name, unsigned flags);
    virtual void Free(void* p, unsigned sz);
};
IAlloc* GetDefaultAllocator();   // EA::Allocator::ICoreAllocator::GetDefaultAllocator
struct TagT {};

struct IUnk {
    virtual void AddRef();
    virtual void Release();
};
struct ARC {
    IUnk* mp;
    void Assign(IUnk* p);   // 0x00b5f950
};
struct IRC {  // refcounted interface (dtor, AddRef, Release)
    virtual void v0(int);
    virtual void AddRef();
    virtual void Release();
};
struct RCObjN {  // vptr + refcount
    virtual void v0(int);
    int mRef;
};

struct ResourceRequest;
typedef void (__cdecl *ReqCb)(void* evt, void* ctx);

struct Evt {
    int type;               // +0
    unsigned id;            // +4
    uint8_t flag;           // +8
    const uint16_t* url;    // +0xc
    IUnk* obj;              // +0x10
};

struct EvtA {
    int type;
    unsigned id;
    uint8_t flag;
    const uint16_t* url;
    ARC obj;
};

// ---------------------------------------------------------------------------
// callback vector / string-keyed wait map
// ---------------------------------------------------------------------------
struct CbPair {
    ReqCb fn;
    void* arg;
};
struct CbVec {
    void* x;            // +0 (node +4)
    CbPair* mpBegin;    // +4 (node +8)
    CbPair* mpEnd;      // +8 (node +0xc)
    CbPair* mpCap;      // +0xc (node +0x10)
    char alloc[4];
    char pad[4];
    CbVec* CopyCtor(CbVec* src);   // 0x008ff0b0
};
struct CbVecRaw {
    CbPair* mpBegin;
    CbPair* mpEnd;
    CbPair* mpCap;
    void InsertAux(CbPair* pos, CbPair* val);  // 0x009a0c50
};
struct WNode {
    const uint16_t* key;    // +0
    ResourceRequest* req;   // +4 (CbVec::x)
    CbPair* mpBegin;        // +8
    CbPair* mpEnd;          // +0xc
    CbPair* mpCap;          // +0x10
    char pad[0x1c - 0x14];
    WNode* next;            // +0x1c
};
struct WIter {
    WNode* node;
    WNode** slot;
};
struct WIns {
    WNode* node;
    WNode** slot;
    uint8_t inserted;
};
struct WKV {
    const uint16_t* key;
    CbVec val;
};
struct RehashR {
    uint8_t rehash;
    unsigned newCount;
};
struct RehashPolicy {
    float maxLoad;
    float growth;
    unsigned nextResize;
    void GetRehashRequired(RehashR* r, unsigned buckets, unsigned elems, unsigned add);  // 0x00921440
};
extern void* gEmptyBuckets[1];   // 0x0154df28
struct WMap {
    int unk0;
    WNode** mBuckets;       // +4
    unsigned mBucketCount;  // +8
    unsigned mCount;        // +0xc
    RehashPolicy mPolicy;   // +0x10
    WMap()
    {
        mPolicy.maxLoad = 1.0f;
        mPolicy.growth = 2.0f;
        mCount = 0;
        mPolicy.nextResize = 0;
        mBuckets = (WNode**)gEmptyBuckets;
        mBucketCount = 1;
    }
    WNode* DoFindNode(WNode* head, const uint16_t* const* key, uint32_t hash);  // 0x008fe7e0
    void DoRehash(unsigned n);                                                  // 0x008fe710
    void find(WIter* out, const uint16_t* const* key);                          // 0x008fe9a0
    WIter* erase(WIter* out, WIter it);                                         // 0x008ff3c0
    WIns* DoInsertValue(WIns* out, WKV* kv, TagT);
    void FreeNodes(WNode** b, unsigned n);                                      // 0x008ff110
    void Destroy()
    {
        FreeNodes(mBuckets, mBucketCount);
        mCount = 0;
        if (mBucketCount > 1)
            operator_delete__(mBuckets);
    }
    __forceinline void Notify(Evt* evt)
    {
        WIter wi;
        find(&wi, &evt->url);
        if (wi.node != mBuckets[mBucketCount]) {
            CbPair* ce = wi.node->mpEnd;
            for (CbPair* p = wi.node->mpBegin; p != ce; p++)
                p->fn(evt, p->arg);
            erase(&wi, wi);
        }
    }
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

// @ 0x008ffa20
WIns* WMap::DoInsertValue(WIns* out, WKV* kv, TagT)
{
    uint32_t h = HashStr(kv->key);
    unsigned n = mBucketCount;
    unsigned idx = h % n;
    WNode** slot = &mBuckets[idx];
    WNode* found = DoFindNode(*slot, &kv->key, h);
    if (found == 0) {
        RehashR r;
        mPolicy.GetRehashRequired(&r, n, mCount, 1);
        WNode* node = (WNode*)operator_new(0x20, "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        if (node) {
            node->key = kv->key;
            ((CbVec*)&node->req)->CopyCtor(&kv->val);
        }
        node->next = 0;
        if (r.rehash) {
            idx = h % r.newCount;
            DoRehash(r.newCount);
        }
        node->next = mBuckets[idx];
        mBuckets[idx] = node;
        mCount++;
        out->node = node;
        out->slot = &mBuckets[idx];
        out->inserted = 1;
        return out;
    }
    out->node = found;
    out->slot = slot;
    out->inserted = 0;
    return out;
}

// ---------------------------------------------------------------------------
// ResourceRequest
// ---------------------------------------------------------------------------
struct IStream {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void SetPosition(int a, int b);   // +0x28
    virtual void v11();
    virtual int Read(void* buf, unsigned n);  // +0x30
};
struct ILogListener;
extern uint16_t gEmptyStrBuf[1];   // 0x01667bac
extern unsigned gNextRequestId;    // 0x0154db08

struct ResourceRequest {
    ResourceRequest* mpNext;        // +0
    ResourceRequest* mpPrev;        // +4
    ILogListener* mpErrorListener;  // +8
    const uint16_t* mpURL;          // +0xc
    char* mTypeBegin;               // +0x10
    char* mTypeEnd;                 // +0x14
    char* mTypeCap;                 // +0x18
    int mTypePad;                   // +0x1c
    IUnk* mpResource;               // +0x20
    int mEncoding;                  // +0x24
    int mEncodingSource;            // +0x28
    bool mCacheable;                // +0x2c
    ReqCb mpCallback;               // +0x30
    void* mpContext;                // +0x34
    unsigned mRequestId;            // +0x38
    IRC* mpStream;                  // +0x3c

    ResourceRequest(const uint16_t* url, ILogListener* el);
    bool SetEncoding(int enc, int src);
};

// @ 0x00900310
ResourceRequest::ResourceRequest(const uint16_t* url, ILogListener* el)
{
    mpErrorListener = el;
    _ReadWriteBarrier();
    mpURL = url;
    _ReadWriteBarrier();
    mpPrev = 0;
    mpNext = 0;
    _ReadWriteBarrier();
    mTypeCap = (char*)gEmptyStrBuf + 1;
    _ReadWriteBarrier();
    mTypeBegin = (char*)gEmptyStrBuf;
    mTypeEnd = (char*)gEmptyStrBuf;
    mpResource = 0;
    _ReadWriteBarrier();
    mEncoding = 8;
    mEncodingSource = 4;
    mCacheable = true;
    mpCallback = 0;
    mpContext = 0;
    _ReadWriteBarrier();
    mRequestId = gNextRequestId;
    gNextRequestId += 1;
    mpStream = 0;
}

// @ 0x009002f0
bool ResourceRequest::SetEncoding(int enc, int src)
{
    if (src <= mEncodingSource) {
        mEncodingSource = src;
        mEncoding = enc;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// stream encoding sniffer: owns a char buffer at +8
// ---------------------------------------------------------------------------
struct CharVec {
    char* mpBegin;
    char* mpEnd;
    void DoInsertValues(char* pos, unsigned n, const char& v);   // 0x004c10e0
};
struct EncodingSniffer {
    char pad[8];
    CharVec buf;    // +8
    int Detect(IStream* s);
};
int __cdecl DetectEncoding(const char* p, unsigned n, int a, int b);   // 0x0093c730

// @ 0x00900370
int EncodingSniffer::Detect(IStream* s)
{
    unsigned sz = buf.mpEnd - buf.mpBegin;
    if (sz < 0x40) {
        char fill = 0;
        buf.DoInsertValues(buf.mpEnd, 0x40 - sz, fill);
    } else {
        char* nf = buf.mpBegin + 0x40;
        char* last = buf.mpEnd;
        memcpy(nf, last, last - last);
        buf.mpEnd += nf - last;
    }
    s->SetPosition(0, 0);
    if (s->Read(buf.mpBegin, 0x40) != 0) {
        s->SetPosition(0, 0);
        return DetectEncoding(buf.mpBegin, 0x40, 0, 0);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// sorted vector map<unsigned, ResourceRequest*>
// ---------------------------------------------------------------------------
struct UPair {
    unsigned first;
    ResourceRequest* second;
};
UPair* __cdecl LowerBound(UPair* b, UPair* e, unsigned* key, uint8_t flag);  // 0x00d01260
struct UMap {
    UPair* mpBegin;     // +0
    UPair* mpEnd;       // +4
    UPair* mpCap;       // +8
    char pad[8];
    uint8_t mFlag;      // +0x14
    UMap()
    {
        mpBegin = 0;
        mpEnd = 0;
        mpCap = 0;
    }
    unsigned erase(unsigned* key);
    ResourceRequest** operator[](unsigned* key);
    void insert(UPair* pos, UPair* val);   // 0x009970e0
};

// @ 0x008ff9b0
unsigned UMap::erase(unsigned* key)
{
    UPair* e = mpEnd;
    UPair* it = LowerBound(mpBegin, e, key, mFlag);
    if (it == e || *key < it->first)
        it = e;
    else if (it == it + 1)
        it = e;
    if (it == e)
        return 0;
    UPair* s = it + 1;
    if (s < e) {
        UPair* d = it;
        do {
            *d = *s;
            s++;
            d++;
        } while (s != e);
    }
    mpEnd -= 1;
    return 1;
}

// @ 0x008ffdf0
ResourceRequest** UMap::operator[](unsigned* key)
{
    UPair* b = mpBegin;
    UPair* e = mpEnd;
    UPair* it = LowerBound(b, e, key, mFlag);
    if (it == e || *key < it->first) {
        unsigned k = *key;
        UPair val;
        val.first = k;
        val.second = 0;
        if (it == e || k >= it->first)
            it = LowerBound(it, e, &val.first, mFlag);
        else
            it = LowerBound(b, it, &val.first, mFlag);
        if (it == e || k < it->first)
            insert(it, &val);
    }
    return &it->second;
}

// ---------------------------------------------------------------------------
// ResourceProvider
// ---------------------------------------------------------------------------
struct ListBase {  // eastl::intrusive_list_base
    void* mpNext;
    void* mpPrev;
    ~ListBase();   // 0x00620230
};

struct ResourceCache {
    char data[0x128];
    ResourceCache(IAlloc* a, unsigned maxSize, uint16_t frac);   // 0x008fe830
    void Clear();                                                // 0x008feae0
    IUnk* Find(const uint16_t* key);                             // 0x008feba0
    bool Insert(const uint16_t* key, IUnk* data, unsigned size); // 0x008fec20
    void Destroy()
    {
        Clear();
        ((ListBase*)(data + 0x120))->~ListBase();
    }
};

struct RCVec {
    RCObjN** mpBegin;
    RCObjN** mpEnd;
    RCObjN** mpCap;
    char pad[4];
    RCObjN** mpFixed;
    RCVec(RCObjN** b)
    {
        mpFixed = b;
        mpEnd = b;
        mpBegin = b;
        mpCap = b + 64;
    }
    void Destroy()
    {
        DestroyRange(mpBegin, mpEnd);
        RCObjN** b = mpBegin;
        if (b && b != mpFixed)
            operator_delete__(b);
    }
    RCObjN** erase(RCObjN** pos);                   // 0x008ff370
    void InsertValue(RCObjN** pos, RCObjN** val);   // 0x008ff4c0
    void DestroyRange(RCObjN** f, RCObjN** l);      // 0x00a693f0
    RCObjN** find(RCObjN* f)
    {
        RCObjN** p = mpBegin;
        RCObjN** e = mpEnd;
        for (; p != e && *p != f; ++p) {
        }
        return p;
    }
    void push_back(RCObjN* const& v)
    {
        if (mpEnd < mpCap) {
            RCObjN** slot = mpEnd++;
            if (slot) {
                *slot = v;
                if (v)
                    v->mRef += 1;
            }
        } else {
            InsertValue(mpEnd, (RCObjN**)&v);
        }
    }
};

struct PMapNode;
struct PMap {
    int unk0;
    PMapNode** mBuckets;
    unsigned mBucketCount;
    unsigned mCount;
    RehashPolicy mPolicy;
    PMap()
    {
        mPolicy.maxLoad = 1.0f;
        mPolicy.growth = 2.0f;
        mCount = 0;
        mPolicy.nextResize = 0;
        mBuckets = (PMapNode**)gEmptyBuckets;
        mBucketCount = 1;
    }
    void FreeNodes(PMapNode** b, unsigned n);   // 0x008feea0
    void Destroy()
    {
        FreeNodes(mBuckets, mBucketCount);
        mCount = 0;
        if (mBucketCount > 1)
            operator_delete__(mBuckets);
    }
};

struct IProtocolHandler {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual bool Start(ResourceRequest* r, bool noCache);   // +0x10
    virtual bool IsCacheValid(const uint16_t* url);         // +0x14
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void Cancel(ResourceRequest* r);                // +0x24
};

struct IFactory {
    virtual void v0();
    virtual int Create(void** out, unsigned* size, ResourceRequest* r);
};

struct VecVal {  // by-value vector argument to BuildVec
    int u0;
    int z0, z1, z2;
    int u4, u5;
    VecVal() { z0 = 0; z1 = 0; z2 = 0; }
};
struct VOut {
    const uint16_t* key;
    CbVec val;
};
VOut* __cdecl BuildVec(VOut* out, const uint16_t* key, VecVal v);   // 0x008ff450

struct IResourceProvider {
    IResourceProvider() : mRefCount(0) {}
    virtual ~IResourceProvider() {}
    int mRefCount;
};

struct ResourceProvider : IResourceProvider {
    IAlloc* mpAllocator;       // +8
    RCVec mFactories;          // +0xc
    char fpad[0x24 - 0xc - sizeof(RCVec)];
    char fbuf[0x100];
    UMap mRequests;            // +0x124
    ResourceCache mCache;      // +0x13c
    PMap mProtocolTable;       // +0x264
    char ppad[0x284 - 0x264 - sizeof(PMap)];
    unsigned mCurrentId;       // +0x284
    WMap mWaiting;             // +0x288

    ResourceProvider(IAlloc* a);
    virtual ~ResourceProvider();
    IProtocolHandler* GetProtocolHandler(const uint16_t* url);   // 0x008feef0
    int CreateResource(void** out, unsigned* size, ResourceRequest* r);  // 0x008ff170
    bool CancelRequest(unsigned id);
    bool CancelAll();
    void SetFactory(RCObjN* f, bool add);
    void FinishRequest(ResourceRequest* r, int stage);
    bool Request(unsigned* outId, const uint16_t* url, ReqCb cb, void* ctx, ILogListener* el, bool noCache);
};

static __forceinline void ReleaseRC(RCObjN* o)
{
    if (o) {
        int n = (*(volatile int*)&o->mRef += -1);
        if (n == 0) {
            o->mRef = 1;
            _ReadWriteBarrier();
            o->v0(1);
        }
    }
}

// @ 0x008ff610
bool ResourceProvider::CancelRequest(unsigned id)
{
    UPair* e = mRequests.mpEnd;
    UPair* it = LowerBound(mRequests.mpBegin, e, &id, mRequests.mFlag);
    if (it == e || id < it->first)
        it = e;
    else if (it == it + 1)
        it = e;
    if (it == e)
        return false;
    ResourceRequest* r = it->second;
    IProtocolHandler* h = GetProtocolHandler(r->mpURL);
    if (h)
        h->Cancel(r);
    Evt evt;
    evt.obj = 0;
    evt.id = r->mRequestId;
    evt.flag = 0;
    evt.type = 4;
    evt.url = r->mpURL;
    r->mpCallback(&evt, r->mpContext);
    mWaiting.Notify(&evt);
    if (r->mpURL)
        mpAllocator->Free((void*)r->mpURL, 0);
    r->mpURL = 0;
    IAlloc* a = mpAllocator;
    if (r->mpStream)
        r->mpStream->Release();
    if (r->mpResource)
        r->mpResource->Release();
    if (r->mTypeCap - r->mTypeBegin > 1 && r->mTypeBegin)
        operator_delete__(r->mTypeBegin);
    a->Free(r, 0);
    UPair* s = it + 1;
    UPair* e2 = mRequests.mpEnd;
    if (s < e2) {
        UPair* d = it;
        do {
            *d = *s;
            s++;
            d++;
        } while (s != e2);
    }
    mRequests.mpEnd -= 1;
    if (evt.obj)
        evt.obj->Release();
    return true;
}

// @ 0x008ff7f0
bool ResourceProvider::CancelAll()
{
    UPair* p = mRequests.mpBegin;
    Evt evt;
    evt.obj = 0;
    evt.flag = 0;
    evt.type = 4;
    bool any = false;
    if (p != mRequests.mpEnd) {
        any = true;
        do {
            ResourceRequest* r = p->second;
            IProtocolHandler* h = GetProtocolHandler(r->mpURL);
            if (h)
                h->Cancel(r);
            evt.id = r->mRequestId;
            evt.url = r->mpURL;
            r->mpCallback(&evt, r->mpContext);
            mWaiting.Notify(&evt);
            if (r->mpURL)
                mpAllocator->Free((void*)r->mpURL, 0);
            r->mpURL = 0;
            IAlloc* a = mpAllocator;
            if (r->mpStream)
                r->mpStream->Release();
            if (r->mpResource)
                r->mpResource->Release();
            if (r->mTypeCap - r->mTypeBegin > 1 && r->mTypeBegin)
                operator_delete__(r->mTypeBegin);
            a->Free(r, 0);
            p++;
        } while (p != mRequests.mpEnd);
    }
    UPair* last = mRequests.mpEnd;
    UPair* first = mRequests.mpBegin;
    UPair* d = first;
    UPair* s = last;
    if (last != mRequests.mpEnd) {
        do {
            *d = *s;
            s++;
            d++;
        } while (s != mRequests.mpEnd);
    }
    mRequests.mpEnd -= (last - first);
    if (evt.obj)
        evt.obj->Release();
    return any;
}

// @ 0x008ffb40
void ResourceProvider::FinishRequest(ResourceRequest* r, int stage)
{
    Evt evt;
    evt.url = r->mpURL;
    evt.obj = 0;
    evt.type = stage;
    evt.id = r->mRequestId;
    if (mCurrentId != 0) {
        evt.flag = 1;
        if (mCurrentId == evt.id)
            goto flagdone;
    }
    evt.flag = 0;
flagdone:
    if (stage == 2) {
        // the original keeps the created resource in the dead `stage` argument slot
        IUnk*& res = *(IUnk**)&stage;
        res = 0;
        unsigned size = 0;
        int rc = CreateResource((void**)&res, &size, r);
        if (rc == 0) {
            if (r->mCacheable) {
                if (mCache.Insert(r->mpURL, res, size))
                    r->mpURL = 0;
            }
            IUnk* nv = res;
            IUnk* old = evt.obj;
            if (nv != old) {
                if (nv)
                    nv->AddRef();
                evt.obj = nv;
                if (old)
                    old->Release();
            }
            res->Release();
        } else {
            if (rc == 2) {
                if (evt.obj)
                    evt.obj->Release();
                return;
            }
            evt.type = 3;
        }
    }
    r->mpCallback(&evt, r->mpContext);
    mWaiting.Notify(&evt);
    if (r->mpURL)
        mpAllocator->Free((void*)r->mpURL, 0);
    // the original keeps the request id in the dead `stage` argument slot
    *(unsigned*)&stage = r->mRequestId;
    r->mpURL = 0;
    mRequests.erase((unsigned*)&stage);
    IAlloc* a = mpAllocator;
    if (r->mpStream)
        r->mpStream->Release();
    if (r->mpResource)
        r->mpResource->Release();
    if (r->mTypeCap - r->mTypeBegin > 1 && r->mTypeBegin)
        operator_delete__(r->mTypeBegin);
    a->Free(r, 0);
    if (evt.obj)
        evt.obj->Release();
}

// @ 0x008ffd50
void ResourceProvider::SetFactory(RCObjN* f, bool add)
{
    RCObjN** end = mFactories.mpEnd;
    RCObjN** p = mFactories.mpBegin;
    for (; p != end && *p != f; ++p) {
    }
    if (add) {
        if (p == end) {
            RCObjN* tmp = f;
            if (tmp)
                tmp->mRef += 1;
            RCObjN** slot = mFactories.mpEnd;
            if (slot < mFactories.mpCap) {
                mFactories.mpEnd = slot + 1;
                if (slot) {
                    *slot = f;
                    if (f)
                        f->mRef += 1;
                }
            } else {
                mFactories.InsertValue(slot, &tmp);
            }
            ReleaseRC(tmp);
        }
    } else if (p != end) {
        mFactories.erase(p);
    }
}

// @ 0x008ffe80
ResourceProvider::ResourceProvider(IAlloc* a)
    : mpAllocator(a ? a : GetDefaultAllocator()),
      mFactories((RCObjN**)fbuf),
      mCache(a ? a : GetDefaultAllocator(), 0x500000, 10),
      mCurrentId(0)
{
}

// @ 0x008fff80
ResourceProvider::~ResourceProvider()
{
    mWaiting.Destroy();
    mProtocolTable.Destroy();
    mCache.Destroy();
    if (mRequests.mpBegin)
        operator_delete__(mRequests.mpBegin);
    mFactories.Destroy();
}

// @ 0x00900070
bool ResourceProvider::Request(unsigned* outId, const uint16_t* url, ReqCb cb, void* ctx, ILogListener* el, bool noCache)
{
    const uint16_t* u = url;
    IProtocolHandler* h = GetProtocolHandler(u);
    if (!h)
        return false;
    if (!noCache) {
        IUnk* res = mCache.Find(u);
        if (res) {
            if (h->IsCacheValid(u)) {
                EvtA evt;
                evt.obj.mp = 0;
                evt.type = 2;
                evt.id = 0;
                evt.flag = 1;
                evt.url = u;
                evt.obj.Assign(res);
                *outId = 0;
                cb(&evt, ctx);
                if (evt.obj.mp)
                    evt.obj.mp->Release();
                return true;
            }
        }
    }
    WIter wi;
    mWaiting.find(&wi, &url);
    if (wi.node != mWaiting.mBuckets[mWaiting.mBucketCount]) {
        WNode* n = wi.node;
        CbPair cp;
        cp.fn = cb;
        cp.arg = ctx;
        if (n->mpEnd < n->mpCap) {
            CbPair* slot = n->mpEnd;
            n->mpEnd = slot + 1;
            if (slot) {
                slot->fn = cb;
                slot->arg = ctx;
            }
        } else {
            ((CbVecRaw*)&n->mpBegin)->InsertAux(n->mpEnd, &cp);
        }
        *outId = n->req->mRequestId;
        return true;
    }
    ResourceRequest* rq = (ResourceRequest*)mpAllocator->Alloc(0x40, "ResourceProvider/ResourceRequest", 0, 4, 0);
    ResourceRequest* r;
    if (rq) {
        new (rq) ResourceRequest(0, el);
        r = rq;
    } else {
        r = 0;
    }
    const uint16_t* q = u;
    while (*q)
        q++;
    unsigned len = (unsigned)(q - u);
    uint16_t* dup = (uint16_t*)mpAllocator->AllocSimple(len * 2 + 2, "ResourceProvider/StrDup", 0);
    memcpy(dup, u, len * 2);
    dup[len] = 0;
    r->mpURL = dup;
    r->mpCallback = cb;
    r->mpContext = ctx;
    *outId = r->mRequestId;
    *mRequests[outId] = r;
    VOut bv;
    BuildVec(&bv, r->mpURL, VecVal());
    WKV kv;
    kv.key = bv.key;
    kv.val.CopyCtor(&bv.val);
    WIns ins;
    mWaiting.DoInsertValue(&ins, &kv, TagT());
    if (kv.val.mpBegin && ((int*)kv.val.mpBegin)[-1] != 0)
        operator_delete__(kv.val.mpBegin);
    if (bv.val.mpBegin && ((int*)bv.val.mpBegin)[-1] != 0)
        operator_delete__(bv.val.mpBegin);
    ins.node->req = r;
    mCurrentId = *outId;
    bool ok = h->Start(r, noCache);
    mCurrentId = 0;
    return ok;
}
