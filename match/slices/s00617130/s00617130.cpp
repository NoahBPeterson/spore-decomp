// SP::Pollen transaction classes: telemetry/snapshot upload transactions, get-asset-feed and the
// heap-based feed helpers (0x00617130-0x00617f10). Complete behavioral ports of every function.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE (no /EHsc).
#include "types.h"
#include <intrin.h>
#include <string.h>
#pragma intrinsic(_ReadWriteBarrier)
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedDecrement)
#pragma intrinsic(_InterlockedExchange)

typedef unsigned int size_type;
typedef unsigned __int64 u64;

void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void operator delete[](void* p);                                                    // 0x00f47380

struct ResourceKey { uint32_t instanceID, typeID, groupID; };

extern char gEmptyString8[];            // 0x01667bac (shared empty string storage)

// ---------------------------------------------------------------------------------------------
// shared vtable tags / free lists
// ---------------------------------------------------------------------------------------------
extern void* kBaseVtbl[];               // 0x013ec458 (cITransaction base vtable)
extern void* kVtbl13fc598[];
extern void* kVtbl13fc5bc[];
extern void* kVtbl13fc5e0[];
extern void* kVtbl13fc698[];
extern void* gFreeList15f52c4;
extern void* gFreeList15f5304;

struct IRel2 {                          // Release at slot 2 (+8)
    virtual int s0(); virtual int s1();
    virtual int ReleaseSlot2();
};
struct IRel1 {                          // AddRef at +0, Release at +4
    virtual int AddRef();
    virtual int ReleaseSlot1();
    virtual int ReleaseSlot2();
};

// reference counted object with the count at +4 and a deleting destructor at slot 0
struct RCObj {
    virtual void* Destroy(unsigned flags);
    int mnRef;
};
inline void RCRelease(RCObj* p)
{
    int n = (*(volatile int*)&p->mnRef += -1);
    if (n == 0) {
        p->mnRef = 1;
        _ReadWriteBarrier();
        p->Destroy(1);
    }
}

// ---------------------------------------------------------------------------------------------
// eastl::basic_string<char> (16 bytes)
// ---------------------------------------------------------------------------------------------
template <typename T> inline const T& emax(const T& a, const T& b) { return (a < b) ? b : a; }
struct string8 {
    char* mpBegin; char* mpEnd; char* mpCapacity; int mAllocator;
    string8& append(size_type n, char c);               // 0x00616960
    void erase(char* first, char* last)
    {
        if (first != last) {
            memmove(first, last, (size_t)((mpEnd - last) + 1));
            mpEnd -= (last - first);
        }
    }
    void resize(size_type n, char c)
    {
        const size_type nLength = (size_type)(mpEnd - mpBegin);
        if (n < nLength)
            erase(mpBegin + n, mpEnd);
        else if (n > nLength)
            append(n - nLength, c);
    }
    void Resize0(size_type n);                         // 0x006174e0
    ~string8()
    {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin) operator delete[](mpBegin);
        }
    }
};
// the empty string state (what eastl's default constructor stores)
struct string8Empty {
    char* mpBegin; char* mpEnd; char* mpCapacity; int mAllocator;
};
void __cdecl MapLookup(uint32_t hash, string8* out);       // 0x00621460 (SP::Pollen::MapLookup)

// a pointer to a variable-size array whose allocation header (count) sits at [-4]
inline void FreeCountedArray(void* p)
{
    if (p && ((int*)p)[-1] != 0) operator delete[](p);
}

// ---------------------------------------------------------------------------------------------
// 0x00617450 / 0x00617490: scalar deleting destructors of pooled transactions
// ---------------------------------------------------------------------------------------------
struct cTelemetryUploadTransaction {
    void** vtbl; int mnRef;
    IRel2* mpTelemetryStream;               // +8
    void* Destroy(unsigned flags);          // 0x00617450
};
// @ 0x00617450
void* cTelemetryUploadTransaction::Destroy(unsigned flags)
{
    vtbl = kVtbl13fc598;
    _ReadWriteBarrier();
    if (mpTelemetryStream) mpTelemetryStream->ReleaseSlot2();
    vtbl = kBaseVtbl;
    if (flags & 1) {
        *(void**)this = gFreeList15f52c4;
        gFreeList15f52c4 = this;
    }
    return this;
}

struct cPollenTxTwoRefs {
    void** vtbl; int mnRef;
    IRel2* mp8;
    IRel2* mpC;
    void* Destroy(unsigned flags);          // 0x00617490
};
// @ 0x00617490
void* cPollenTxTwoRefs::Destroy(unsigned flags)
{
    vtbl = kVtbl13fc5bc;
    _ReadWriteBarrier();
    if (mpC) mpC->ReleaseSlot2();
    if (mp8) mp8->ReleaseSlot2();
    vtbl = kBaseVtbl;
    if (flags & 1) {
        *(void**)this = gFreeList15f5304;
        gFreeList15f5304 = this;
    }
    return this;
}

// @ 0x006174e0   eastl::basic_string<char>::resize(n)
void string8::Resize0(size_type n)
{
    resize(n, 0);
}

// ---------------------------------------------------------------------------------------------
// 0x00617530   eastl::adjust_heap<unsigned*, int, unsigned, cTimeGreater>
// ---------------------------------------------------------------------------------------------
struct sTimedRec { char pad[0x30]; __int64 mTime; char pad2[0x118 - 0x38]; };
struct sTimedOwner { char pad[0x60]; sTimedRec* mpTable; };
struct cTimeGreaterInl {
    sTimedOwner* mpOwner;
    bool operator()(unsigned a, unsigned b) const {
        return mpOwner->mpTable[a].mTime > mpOwner->mpTable[b].mTime;
    }
};
void promote_heap(unsigned* first, int topPosition, int position, const unsigned value, cTimeGreaterInl compare);   // 0x00616a00

// @ 0x00617530
void adjust_heap(unsigned* first, int topPosition, int heapSize, int position, unsigned value, cTimeGreaterInl compare)
{
    int childPosition = (2 * position) + 2;
    while (childPosition < heapSize) {
        if (compare(*(first + childPosition), *(first + (childPosition - 1))))
            --childPosition;
        *(first + position) = *(first + childPosition);
        position = childPosition;
        childPosition = (2 * position) + 2;
    }
    if (childPosition == heapSize) {
        *(first + position) = *(first + (childPosition - 1));
        position = childPosition - 1;
    }
    promote_heap(first, topPosition, position, value, compare);
}

// ---------------------------------------------------------------------------------------------
// resource manager / database / directory interfaces (only the slots used here)
// ---------------------------------------------------------------------------------------------
struct IObj {                           // refcounted resource: AddRef +4, Release +8 (slot 1 / slot 2)
    virtual int s0();
    virtual int AddRef();
    virtual int Release();
    virtual void* Cast(uint32_t typeID);    // +0x0c
};
struct IObj4 {                          // refcounted: Release at +4 (slot 1)
    virtual int s0();
    virtual int Release4();
    virtual int s2();
    virtual void* Cast(uint32_t typeID);    // +0x0c
};
struct IDb {
    virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5(); virtual int s6();
    virtual bool Fn1c(void* obj, void** pOut, int a, uint32_t b);                  // +0x1c
    virtual int s8(); virtual int s9(); virtual int s10(); virtual int s11(); virtual int s12();
    virtual bool OpenRecord(const ResourceKey* key, void** pOut, int a, int b, int c, int d);   // +0x34
};
struct IResMgr {
    virtual int s0(); virtual int s1(); virtual int s2();
    virtual bool GetResource(const ResourceKey* key, void** pOut, int a, int b, int c, int d);   // +0x0c
    virtual int s4(); virtual int s5(); virtual int s6(); virtual int s7();
    virtual void Fn20(void* obj, int a, void* area, int b, int c);                  // +0x20
    virtual int s9(); virtual int s10(); virtual int s11(); virtual int s12(); virtual int s13(); virtual int s14();
    virtual int s15(); virtual int s16(); virtual int s17();
    virtual IDb* FindDatabase(uint32_t id, int flags);                              // +0x48
    virtual int s19(); virtual int s20(); virtual int s21();
    virtual IDb* FindDatabaseByKey(const ResourceKey* key);                        // +0x58
};
IResMgr* GetManager();                  // 0x0067dcd0
struct IMgr2 {                          // 0x008de1a0
    virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4();
    virtual bool Fn14(const ResourceKey* key, int a);                              // +0x14
};
IMgr2* GetManager2();

struct IMessageServer {
    virtual int slot00(); virtual int slot04(); virtual int slot08(); virtual int slot0c();
    virtual int slot10();
    virtual bool PostMessage(uint32_t id, void* data, int flag);   // 0x14
};
IMessageServer* GetMessageServer();     // 0x0067dcc0 (SP::MessageServer)
IMessageServer* GetMessageServer2();    // 0x00883860 (EA::Messaging::GetServer)

struct cAssetDirectory {
    bool GetServerId(const ResourceKey* key, uint32_t* out, bool b);   // 0x0054e530
    bool GetLocalKey(uint32_t lo, uint32_t hi, ResourceKey* out);      // 0x0054e460
    void Fn54e7b0(uint32_t lo, uint32_t hi, int a);                    // 0x0054e7b0
    void Fn54e8c0(uint32_t a, uint32_t lo, uint32_t hi);               // 0x0054e8c0
    u64 Fn54e8f0(uint32_t a);                                          // 0x0054e8f0
    void Fn54eb10(const ResourceKey* key, int a);                      // 0x0054eb10
};
struct cPollinatorDir { char pad[0x58]; cAssetDirectory* mpAssetDirectory; };
cPollinatorDir* GetPollinatorDir();     // 0x0067cb30
struct cPollinatorNotify { virtual int s0(); virtual int Notify(uint32_t id, void* data); };
cPollinatorNotify* GetPollinatorNotify();   // 0x0067cb30 (same object)

struct cMeta {                          // SP::Pollen::cAssetMetadata (only RemoveFeedURI used)
    bool RemoveFeedURI(const string8* uri);     // 0x00551ff0
};
struct cIDGen { bool CreateKey(); };            // 0x005fbb00
cIDGen* __stdcall GetIDGen(void* t);            // 0x005f7930
void __cdecl SetCachingType(int type, void* obj);   // 0x006ac0a0
void __cdecl Fn6ad010(void* obj);                    // 0x006ad010
void* __cdecl GetSaveArea(uint32_t id);              // 0x006b1f90
void __cdecl Fn6b4b60(void* a, void* b, int c, int d);   // 0x006b4b60 (async-save)
void CreateDownloadJob(IObj* pDb, void* pOwner, const ResourceKey* pKey);   // 0x00616d60 (defined in s00614f20/s00616360)
void* ZoneNew(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00926020 (EA::Allocator::ZoneObject::operator new)
struct cResourceReader {                     // ctor 0x008e2380
    cResourceReader* Ctor(int a, void* b, const ResourceKey* key, int c, int d);
};
uint32_t __cdecl FNV1_String8(const char* s, uint32_t seed, int a);     // 0x00932e80

// the object passed around by the feed transactions: slot +0x18 yields a stream, +0x24 closes it
struct IStreamObj {
    virtual int s0(); virtual int s1();
    virtual int ReleaseSlot2();
    virtual int s3(); virtual int s4(); virtual int s5();
    virtual void* Fn18(int a, void** pOut);   // +0x18
    virtual int s7(); virtual int s8();
    virtual void Close24();                   // +0x24
};
struct cFeedDocRef {                          // feed owner: id at +0x18, entries of 0x118 at +0x60
    char pad[0x18]; uint32_t mId; char pad2[0x60 - 0x1c]; sTimedRec* mpTable;
};
struct cHttpResult {
    char pad[0xf3c];
    IRel2* mpResponse;                    // +0xf3c
};
struct IResp { virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5(); virtual int Close(); };

// a smart pointer used as an out-parameter: GetAddressOf releases the old value first
struct ObjPtr {
    IObj4* mp;
    ObjPtr() : mp(0) {}
    IObj4** GetAddressOf()
    {
        IObj4* t = mp;
        if (t) {
            mp = 0;
            t->Release4();
        }
        return &mp;
    }
};

struct sFeedMsg {
    uint32_t hash;
    uint32_t minusOne;
    ResourceKey key;
};

// ---------------------------------------------------------------------------------------------
// 0x00617130: handle the result of a feed asset download transaction
// ---------------------------------------------------------------------------------------------
struct cFeedAssetTx {
    void** vtbl; int mnRef;
    bool mb8; bool mb9;
    cFeedDocRef* mpFeed;                  // +0xc
    unsigned mnIndex;                     // +0x10
    ResourceKey mKey;                     // +0x14
    IObj* mp20;                           // +0x20
    IStreamObj* mp24;                     // +0x24
    bool HandleResult(int err, void* a, void* b);   // 0x00617130
};

// @ 0x00617130
bool cFeedAssetTx::HandleResult(int err, void* a, void* b)
{
    bool ok = false;
    bool failed = false;
    cAssetDirectory* dir = GetPollinatorDir()->mpAssetDirectory;
    uint32_t id[2];
    id[0] = 0xffffffffu;
    id[1] = 0xffffffffu;
    if (dir->GetServerId(&mKey, id, false))
        dir->Fn54e7b0(id[0], id[1], 0);
    if (err == 0) {
        if (mb8 && mp24) {
            void* rec = 0;
            void* t = mp24->Fn18(0, &rec);
            if (GetIDGen(t)->CreateKey()) {
                IResMgr* mgr = GetManager();
                IDb* db = mgr->FindDatabase(mKey.typeID, -1);
                void* mem = ZoneNew(0x24, "Pollinator", 0, 0, 0, 0);
                IObj* pObj;
                if (mem)
                    pObj = (IObj*)((cResourceReader*)mem)->Ctor(0, rec, &mKey, 0, 0);
                else
                    pObj = 0;
                if (pObj) pObj->AddRef();
                IObj4* res = 0;
                if (db->Fn1c(pObj, (void**)&res, 0, mKey.typeID)) {
                    ResourceKey* rk = (ResourceKey*)((char*)res + 8);
                    *rk = mKey;
                    SetCachingType(10, res);
                    Fn6ad010(res);
                    IResMgr* m2 = GetManager();
                    m2->Fn20(res, 0, GetSaveArea(0x11ac19d), 0, 0);
                }
                if (res) res->Release4();
                if (pObj) pObj->Release();
            }
            if (rec) ((IObj*)rec)->Release();
        }
        if (GetManager2()->Fn14(&mKey, 0)) {
            void* x = mp20 ? mp20->Cast(0x2269ed1) : 0;
            void* area = GetSaveArea(0x11ac19d);
            SetCachingType(10, x);
            Fn6ad010(x);
            Fn6b4b60(x, area, 0, 0);
            if (mp24) {
                mp24->Close24();
                if (mp24) {
                    IStreamObj* p = mp24;
                    mp24 = 0;
                    p->ReleaseSlot2();
                }
            }
            GetMessageServer2()->PostMessage(0x1a7f758, &mKey, 0);
            if (mb9) {
                sTimedRec* r = &mpFeed->mpTable[mnIndex];
                u64 t64 = (u64)r->mTime;
                uint32_t lo = (uint32_t)t64;
                uint32_t hi = (uint32_t)(t64 >> 32);
                if (dir->Fn54e8f0(mpFeed->mId) < t64)
                    dir->Fn54e8c0(mpFeed->mId, lo, hi);
            }
            ok = true;
        } else {
            failed = true;
        }
    }
    if (mp24) {
        mp24->Close24();
        if (mp24) {
            IStreamObj* p = mp24;
            mp24 = 0;
            p->ReleaseSlot2();
        }
    }
    if (!ok && !failed)
        dir->Fn54eb10(&mKey, 1);
    return ok;
}

// ---------------------------------------------------------------------------------------------
// 0x006175c0 / 0x006177b0: drop the feed URI from every matching asset's metadata
// ---------------------------------------------------------------------------------------------
// the shared per-asset step of both loops
static __forceinline void UnsubscribeAsset(const ResourceKey& src, const string8* uri, sFeedMsg* msg, const ResourceKey& orig)
{
    ResourceKey k = src;
    k.typeID = 0x30bdee3;
    ObjPtr p;
    IResMgr* m = GetManager();
    if (m->GetResource(&k, (void**)p.GetAddressOf(), 0, 0, 0, 0)) {
        cMeta* meta = p.mp ? (cMeta*)p.mp->Cast(0x30bdee3) : 0;
        if (meta->RemoveFeedURI(uri)) {
            *(ResourceKey*)((char*)p.mp + 8) = k;
            void* area = GetSaveArea(0x11ac19d);
            SetCachingType(10, p.mp);
            Fn6ad010(p.mp);
            CreateDownloadJob((IObj*)p.mp, area, 0);
            msg->key = orig;
            GetMessageServer2()->PostMessage(0x64e331c, msg, 0);
        }
    }
    if (p.mp) p.mp->Release4();
}

struct hnode { uint32_t lo, hi; hnode* next; };
struct cPendingAssetSet {
    int pad4;
    hnode** mpBucketArray;                // +4
    unsigned mnBucketCount;               // +8
};

// @ 0x006175c0
void __cdecl RemoveFeedFromAll(cPendingAssetSet* self, const string8* uri)
{
    cAssetDirectory* dir = GetPollinatorDir()->mpAssetDirectory;
    if (dir) {
        sFeedMsg msg;
        msg.key.instanceID = 0;
        msg.key.typeID = 0;
        msg.key.groupID = 0;
        msg.hash = FNV1_String8(uri->mpBegin, 0x811c9dc5, 0);
        msg.minusOne = 0xffffffffu;
        hnode** bucket = self->mpBucketArray;
        hnode* node = *bucket;
        if (!node) {
            ++bucket;
            while (*bucket == 0) ++bucket;
            node = *bucket;
        }
        hnode* end = self->mpBucketArray[self->mnBucketCount];
        while (node != end) {
            ResourceKey local;
            local.instanceID = 0;
            local.typeID = 0;
            local.groupID = 0;
            if (dir->GetLocalKey(node->lo, node->hi, &local))
                UnsubscribeAsset(local, uri, &msg, local);
            node = node->next;
            while (node == 0) {
                ++bucket;
                node = *bucket;
            }
        }
    }
}

namespace FunctionalMatch {
struct Constraint {
    Constraint(uint32_t dummy);                                    // 0x00558830
    Constraint(uint32_t property, uint32_t op, uint32_t value);   // 0x00558960
    char data[0x10];
    struct SubVec {
        Constraint* mpBegin; Constraint* mpEnd; Constraint* mpCapacity; int mAlloc;
    } mSubConstraints;
    uint32_t mFlags;
    ~Constraint()                                                  // 0x006066f0
    {
        for (Constraint* p = mSubConstraints.mpBegin; p < mSubConstraints.mpEnd; ++p)
            p->~Constraint();
        FreeCountedArray(mSubConstraints.mpBegin);
    }
};
}
struct KeyVec { ResourceKey* mpBegin; ResourceKey* mpEnd; ResourceKey* mpCapacity; };
struct IObjectTemplateDB {
    virtual int s00(); virtual int s01(); virtual int s02(); virtual int s03(); virtual int s04(); virtual int s05();
    virtual int s06(); virtual int s07(); virtual int s08(); virtual int s09(); virtual int s0a(); virtual int s0b();
    virtual int s0c();
};
struct sTemplateDB {
    void** vtbl;
};
sTemplateDB* ObjectTemplateDB();                  // 0x0067cb40
typedef void (__cdecl *QueryFn)(sTemplateDB*, KeyVec*, FunctionalMatch::Constraint, FunctionalMatch::Constraint);

// @ 0x006177b0
void RemoveFeedByName(const string8* name)
{
    KeyVec results;
    results.mpBegin = 0;
    results.mpEnd = 0;
    results.mpCapacity = 0;
    sTemplateDB* db = ObjectTemplateDB();
    QueryFn* pQuery = (QueryFn*)((char*)db->vtbl + 0x34);
    const char* nm = name->mpBegin;
    (*pQuery)(db, &results, FunctionalMatch::Constraint(0x3cc89b1, 0, FNV1_String8(nm, 0x811c9dc5, 0)),
              FunctionalMatch::Constraint(0));
    sFeedMsg msg;
    msg.key.instanceID = 0;
    msg.key.typeID = 0;
    msg.key.groupID = 0;
    msg.hash = FNV1_String8(name->mpBegin, 0x811c9dc5, 0);
    msg.minusOne = 0xffffffffu;
    ResourceKey* end = results.mpEnd;
    for (ResourceKey* it = results.mpBegin; it != end; ++it) {
        ResourceKey cur = *it;
        UnsubscribeAsset(cur, name, &msg, cur);
    }
    FreeCountedArray(results.mpBegin);
}

// ---------------------------------------------------------------------------------------------
// 0x00617a40: cGetAssetFeedTransaction destructor
// ---------------------------------------------------------------------------------------------
struct cGetAssetFeedTransaction {
    void** vtbl; int mnRef;
    RCObj* mpFeed;                        // +8
    int pad[4];
    string8 mUrl;                         // +0x1c
    int pad2[1];
    char* mpEntries;                      // +0x30
    void Dtor();                          // 0x00617a40
};
// @ 0x00617a40
void cGetAssetFeedTransaction::Dtor()
{
    vtbl = kVtbl13fc5e0;
    _ReadWriteBarrier();
    {
        RCObj* p = mpFeed;
        if (p) {
            mpFeed = 0;
            RCRelease(p);
        }
    }
    FreeCountedArray(mpEntries);
    mUrl.~string8();
    {
        RCObj* p = mpFeed;
        if (p) RCRelease(p);
    }
    vtbl = kBaseVtbl;
}

// ---------------------------------------------------------------------------------------------
// 0x00617b10 / 0x00617c90: build an HTTP GET request carrying the "uri" header
// ---------------------------------------------------------------------------------------------
struct HTTPRequest {                    // EA::Internet::HTTPRequest (refcount at +4)
    virtual ~HTTPRequest();
    volatile long mnRef;
    char pad[0xd94 - 8];
    void** mpHandlerVtbl;               // +0xd94
    bool AddHeader(const char* name, const char* value);     // 0x00944660
    void Release()
    {
        long rc = _InterlockedDecrement(&mnRef);
        if (rc == 0) {
            _InterlockedExchange(&mnRef, 1);
            delete this;
        }
    }
};
struct StreamObj { StreamObj* Ctor(); };                       // 0x0093c430 (thiscall ctor)
bool __cdecl CreateHTTPGetRequest(const char* url, void* stream, HTTPRequest** ppOut);   // 0x00944450
extern void* kVtbl15206f0[];

struct HttpReqRef {
    HTTPRequest* mp;
    void Dtor();                                  // 0x0060d210 (out of line release)
    HTTPRequest** GetAddressOutOfLine();          // 0x0060d240
    HTTPRequest** GetAddressOf()
    {
        HTTPRequest* p = mp;
        if (p) {
            mp = 0;
            p->Release();
        }
        return &mp;
    }
};

struct cFeedGetTx {
    void** vtbl; int mnRef;
    string8 mUri;                         // +8
    bool ConstructRequestA(HTTPRequest** ppOut);   // 0x00617b10
    bool ConstructRequestB(HTTPRequest** ppOut);   // 0x00617c90
};

static __forceinline bool BuildGetRequest(cFeedGetTx* self, uint32_t mapId, HTTPRequest** ppOut)
{
    if (self->mUri.mpBegin != self->mUri.mpEnd) {
        string8 url;
        url.mpBegin = gEmptyString8;
        url.mpEnd = gEmptyString8;
        url.mpCapacity = gEmptyString8 + 1;
        MapLookup(mapId, &url);
        HttpReqRef req;
        req.mp = 0;
        void* mem = operator new(8, "Pollinator", 0, 0, 0, 0);
        void* stream = mem ? ((StreamObj*)mem)->Ctor() : 0;
        if (CreateHTTPGetRequest(url.mpBegin, stream, req.GetAddressOf()) &&
            req.mp->AddHeader("uri", self->mUri.mpBegin)) {
            req.mp->mpHandlerVtbl = kVtbl15206f0;
            _InterlockedExchangeAdd(&req.mp->mnRef, 1);
            *ppOut = req.mp;
            req.Dtor();
            return true;
        }
        if (req.mp) req.mp->Release();
    }
    return false;
}

// @ 0x00617b10
bool cFeedGetTx::ConstructRequestA(HTTPRequest** ppOut) { return BuildGetRequest(this, 0x539f69d, ppOut); }
// @ 0x00617c90
bool cFeedGetTx::ConstructRequestB(HTTPRequest** ppOut) { return BuildGetRequest(this, 0x539f705, ppOut); }

// ---------------------------------------------------------------------------------------------
// 0x00617e00: result handler of the feed-unsubscribe transaction
// ---------------------------------------------------------------------------------------------
struct cFeedUnsubscribeTransaction {
    void** vtbl; int mnRef;
    string8 mUri;                         // +8
    bool HandleResult(int err, cHttpResult* r, void* unused);   // 0x00617e00
};
// @ 0x00617e00
bool cFeedUnsubscribeTransaction::HandleResult(int err, cHttpResult* r, void* unused)
{
    if (r) {
        IResp* p = (IResp*)r->mpResponse;
        if (p) p->Close();
    }
    bool ok = (err == 0);
    char* v;
    if (ok) {
        RemoveFeedByName(&mUri);
        v = mUri.mpBegin;
    } else {
        v = 0;
    }
    GetPollinatorNotify()->Notify(0x3ffd8c9, v);
    if (ok)
        v = mUri.mpBegin;
    else
        v = 0;
    GetMessageServer()->PostMessage(0x3ffd8c9, v, 0);
    return ok;
}

// ---------------------------------------------------------------------------------------------
// 0x00617e80 / 0x00617f10: cSnapshotUploadTransaction
// ---------------------------------------------------------------------------------------------
struct cSnapshotUploadTransaction {
    void** vtbl; int mnRef;
    ResourceKey mKey;                     // +8
    string8 mMyEmailAddress;              // +0x14
    string8 mDestinationEmailAddress;     // +0x24
    string8 mMessageText;                 // +0x34
    string8 mLocale;                      // +0x44
    void Dtor();                          // 0x00617e80
    bool ConstructRequest(HTTPRequest** ppOut);   // 0x00617f10
};
// @ 0x00617e80
void cSnapshotUploadTransaction::Dtor()
{
    vtbl = kVtbl13fc698;
    mLocale.~string8();
    mMessageText.~string8();
    mDestinationEmailAddress.~string8();
    mMyEmailAddress.~string8();
    vtbl = kBaseVtbl;
}

class HTTPMultipartFormDataPostBodyStream {
public:
    HTTPMultipartFormDataPostBodyStream* Ctor();   // 0x00946dc0
    virtual int s0();
    virtual int AddRef();
    virtual int Release();
    virtual int s3(); virtual int s4(); virtual int s5(); virtual int s6(); virtual int s7(); virtual int s8();
    virtual int s9(); virtual int s10(); virtual int s11(); virtual int s12(); virtual int s13(); virtual int s14();
    virtual int s15(); virtual int s16(); virtual int s17(); virtual int s18(); virtual int s19();
    virtual bool AddFile(const char* field, void* data, const char* contentType, const char* fileName, int flags);   // +0x50
    virtual bool AddField(const char* field, const char* value);                                                    // +0x54
};
struct cImageRequest {                      // Graphics::GraphicsFactoryAsyncRequest
    cImageRequest* Ctor(int a, int b, const char* name);       // 0x0093c270
    void SetProperty(int id, float v);                         // 0x0093bb40
};
struct IDbStream { virtual int s0(); virtual int s1(); virtual int ReleaseSlot2(); virtual int s3(); virtual int s4(); virtual int s5(); virtual void* GetStream(); };
struct IRefHolder {
    IDbStream* mp;
    IRefHolder* Reset()                                         // 0x00c463d0
    {
        IDbStream* o = mp;
        if (o) {
            mp = 0;
            o->ReleaseSlot2();
        }
        return this;
    }
};
bool __cdecl CreateHTTPPostRequest(const char* url, void* body, void* image, HTTPRequest** ppOut);   // 0x00945b20

// @ 0x00617f10
bool cSnapshotUploadTransaction::ConstructRequest(HTTPRequest** ppOut)
{
    void* mem = operator new(0x48, "Pollinator", 0, 0, 0, 0);
    if (mem) {
        HTTPMultipartFormDataPostBodyStream* body = ((HTTPMultipartFormDataPostBodyStream*)mem)->Ctor();
        if (body) {
            body->AddRef();
            void* mem2 = operator new(0x24, "Pollinator", 0, 0, 0, 0);
            cImageRequest* img = mem2 ? ((cImageRequest*)mem2)->Ctor(0, 0, "UTF/MemoryStream") : 0;
            img->SetProperty(1, 1.0f);
            if (body->AddField("locale", mLocale.mpBegin)) {
                if (body->AddField("myEmail", mMyEmailAddress.mpBegin)) {
                    if (body->AddField("destEmail", mDestinationEmailAddress.mpBegin)) {
                        if (body->AddField("msgTxt", mMessageText.mpBegin)) {
                            IDb* db = GetManager()->FindDatabaseByKey(&mKey);
                            IRefHolder held;
                            held.mp = 0;
                            if (db) {
                                if (db->OpenRecord(&mKey, (void**)held.Reset(), 1, 6, 1, 0)) {
                                    if (body->AddFile("imagedata", held.mp->GetStream(), "image/jpeg", "postcard.tmp", 0)) {
                                        string8 url;
                                        url.mpBegin = gEmptyString8;
                                        url.mpEnd = gEmptyString8;
                                        url.mpCapacity = gEmptyString8 + 1;
                                        MapLookup(0x53c3e41, &url);
                                        HttpReqRef req;
                                        req.mp = 0;
                                        if (CreateHTTPPostRequest(url.mpBegin, body, img, req.GetAddressOutOfLine())) {
                                            _InterlockedExchangeAdd(&req.mp->mnRef, 1);
                                            req.mp->mpHandlerVtbl = kVtbl15206f0;
                                            *ppOut = req.mp;
                                            req.Dtor();
                                            url.~string8();
                                            if (held.mp) held.mp->ReleaseSlot2();
                                            body->Release();
                                            return true;
                                        }
                                        req.Dtor();
                                        url.~string8();
                                    }
                                }
                                if (held.mp) held.mp->ReleaseSlot2();
                            }
                        }
                    }
                }
            }
            body->Release();
        }
    }
    return false;
}
