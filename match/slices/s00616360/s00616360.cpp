// Slice s00616360: Pollen transaction/job helper classes (constructors, destructors and
// result handlers of the upload/download transactions), the index sort helpers used to order
// asset records by timestamp, two eastl basic_string<char> members and a few small
// Pollinator helpers.
// Built /O2 /MD /Gy /TP (no /EHsc).
#include "types.h"
#include <intrin.h>
#pragma intrinsic(_ReadWriteBarrier)
#pragma intrinsic(_InterlockedExchangeAdd)
typedef unsigned int size_type;
typedef unsigned __int64 u64;

inline void* operator new(unsigned int, void* p) { return p; }
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0 (EASTL allocate)
void* EASTL_alloc(unsigned size, const char* name, int flags, int a, const char* file, int line);
void EASTL_free(void* p);
extern "C" void* __cdecl memset(void*, int, size_t);

struct ResourceKey { uint32_t instanceID, typeID, groupID; };

// ---------------------------------------------------------------------------------------------
// shared pointee types (only the vtable slots and fields the code touches)
// ---------------------------------------------------------------------------------------------
struct IAddRef {                      // refcounted: AddRef at +0, Release at +4
    virtual int AddRef();
    virtual int Release();
};
struct IAddRef1 {                     // AddRef at slot 1 (+4)
    virtual int s0();
    virtual int AddRef1();
};
struct IRel2 {                        // Release at slot 2 (+8)
    virtual int slot0();
    virtual int slot1();
    virtual int ReleaseSlot2();
};
struct IRel1 {                        // Release at slot 1 (+4)
    virtual int slot0();
    virtual int ReleaseSlot1();
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

extern void* kBaseVtbl[];             // 0x013ec458 (cITransaction base vtable)

struct cHttpResult {
    char pad[0xf3c];
    IRel2* mpResponse;                // +0xf3c
};

// ---------------------------------------------------------------------------------------------
// 0x00616360 / 0x00616300 : a transaction holding a refcounted object and two interface refs
// ---------------------------------------------------------------------------------------------
extern void* kVtbl13fc52c[]; extern void* kVtbl13fc550[]; extern void* kVtbl13fc574[];
extern void* kVtbl13fc598[]; extern void* kVtbl13fc5bc[]; extern void* kVtbl13fc484[]; extern void* kVtbl13fc4a8[];
struct cTxC {
    void** vtbl; int mnRef;
    RCObj* mpObj;                     // +8
    int m0c; int m10, m14, m18;
    IRel2* m1c;
    IRel1* m20;
    void Dtor();                      // 0x00616360
};

// @ 0x00616360
void cTxC::Dtor()
{
    vtbl = kVtbl13fc52c;
    _ReadWriteBarrier();
    {
        RCObj* p = mpObj;
        if (p) {
            mpObj = 0;
            RCRelease(p);
        }
    }
    if (m20) m20->ReleaseSlot1();
    if (m1c) m1c->ReleaseSlot2();
    {
        RCObj* p = mpObj;
        if (p) RCRelease(p);
    }
    vtbl = kBaseVtbl;
}

// ---------------------------------------------------------------------------------------------
// 0x006163e0 / 0x00616460 : transaction with a key, a database ref and a counted object
// ---------------------------------------------------------------------------------------------
struct cTxD {
    void** vtbl; int mnRef;
    bool mb8; bool mb9;
    RCObj* mpCounted;                 // +0xc
    unsigned mnCount;                 // +0x10
    ResourceKey mKey;                 // +0x14
    IAddRef* mpRef;                   // +0x20
    IRel2* mpRel;                     // +0x24
    cTxD* Init(ResourceKey key, IAddRef* ref, RCObj* counted, unsigned n, bool b);   // 0x006163e0
    void Dtor();                      // 0x00616460
};

// @ 0x006163e0
cTxD* cTxD::Init(ResourceKey key, IAddRef* ref, RCObj* counted, unsigned n, bool b)
{
    mb8 = b;
    mnRef = 0;
    vtbl = kVtbl13fc550;
    mb9 = true;
    mpCounted = counted;
    if (counted) ++counted->mnRef;
    mnCount = n;
    mKey = key;
    mpRef = ref;
    if (ref) ref->AddRef();
    _ReadWriteBarrier();
    mpRel = 0;
    return this;
}

// @ 0x00616460
void cTxD::Dtor()
{
    vtbl = kVtbl13fc550;
    _ReadWriteBarrier();
    {
        RCObj* p = mpCounted;
        if (p) {
            mpCounted = 0;
            RCRelease(p);
        }
    }
    {
        IRel2* p = mpRel;
        if (p) {
            mpRel = 0;
            p->ReleaseSlot2();
        }
    }
    if (mpRel) mpRel->ReleaseSlot2();
    if (mpRef) ((IRel1*)mpRef)->ReleaseSlot1();
    {
        RCObj* p = mpCounted;
        if (p) RCRelease(p);
    }
    vtbl = kBaseVtbl;
}

// ---------------------------------------------------------------------------------------------
// 0x00616500 : destructor of a transaction with a counted object and one interface ref
// ---------------------------------------------------------------------------------------------
struct cTxE {
    void** vtbl; int mnRef;
    RCObj* mpObj;                     // +8
    int pad[5];
    IRel2* mpRel;                     // +0x20
    void Dtor();                      // 0x00616500
};

// @ 0x00616500
void cTxE::Dtor()
{
    vtbl = kVtbl13fc574;
    _ReadWriteBarrier();
    {
        RCObj* p = mpObj;
        if (p) {
            mpObj = 0;
            RCRelease(p);
        }
    }
    {
        IRel2* p = mpRel;
        if (p) {
            mpRel = 0;
            p->ReleaseSlot2();
        }
    }
    if (mpRel) mpRel->ReleaseSlot2();
    {
        RCObj* p = mpObj;
        if (p) RCRelease(p);
    }
    vtbl = kBaseVtbl;
}

// ---------------------------------------------------------------------------------------------
// manager / message server interfaces
// ---------------------------------------------------------------------------------------------
struct IResourceManager {
    virtual ~IResourceManager();
    virtual bool Initialize();
    virtual bool Dispose();
    virtual bool GetResource(const ResourceKey* key, void* dst, void* a, void* b, void* c, void* d);   // 0x0c
};
IResourceManager* GetManager2();   // 0x008de1a0

struct IMessageServer {
    virtual int slot00(); virtual int slot04(); virtual int slot08(); virtual int slot0c();
    virtual int slot10();
    virtual bool PostMessage(uint32_t id, void* data, int flag);   // 0x14
};
IMessageServer* GetMessageServer();      // 0x0067dcc0 (SP::MessageServer)
IMessageServer* GetMessageServer2();     // 0x00883860 (EA::Messaging::GetServer)

// the worker held by transaction 0x00616580
struct IWorkerObj { virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5(); virtual int s6(); virtual int s7(); virtual int s8(); virtual int s9(); virtual int s10(); virtual int s11(); virtual int s12(); virtual int s13(); virtual int s14(); virtual int s15(); virtual void Fn40(int v); };
struct IWorker {
    virtual int s0(); virtual int s1();
    virtual int ReleaseWorker();          // +8
    virtual int s3();
    virtual int Fn10();                   // +0x10
    virtual int s5(); virtual int s6();
    virtual IWorkerObj* Fn1c();           // +0x1c
    virtual int s8();
    virtual void Fn24();                  // +0x24
};

// @ 0x00616580
struct cTxF {
    void** vtbl; int mnRef; int pad[3];
    ResourceKey mKey;                     // +0x14
    IWorker* mpWorker;                    // +0x20
    bool HandleResult(int err, void* a, void* b);
};
bool cTxF::HandleResult(int err, void* a, void* b)
{
    bool ok = false;
    if (err == 0) {
        if (GetManager2()->GetResource(&mKey, 0, 0, 0, 0, 0))
            ok = true;
    }
    if (mpWorker) mpWorker->Fn24();
    if (!ok) {
        IWorkerObj* o = mpWorker->Fn1c();
        if (o)
            o->Fn40(mpWorker->Fn10());
    }
    if (mpWorker) {
        IWorker* w = mpWorker;
        mpWorker = 0;
        w->ReleaseWorker();
    }
    return ok;
}

// @ 0x00616610
struct cPollinatorLite { virtual int s0(); virtual int Notify(uint32_t id, void* data); };
cPollinatorLite* GetPollinatorLite();    // 0x0067cb30
struct IResp { virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5(); virtual int Close(); };
struct cTxG {
    void** vtbl; int mnRef; void* mp8; int mpC;
    bool HandleResult(int err, cHttpResult* r, void* unused);   // 0x00616610
};
bool cTxG::HandleResult(int err, cHttpResult* r, void* unused)
{
    if (r) {
        IResp* p = (IResp*)r->mpResponse;
        if (p) p->Close();
    }
    bool b = (err == 0);
    if (b)
        GetPollinatorLite()->Notify(0x3cf0359, mp8);
    return b;
}

// @ 0x00616660
struct cTxH {
    void** vtbl; int mnRef; IAddRef1* mp8; int pad; int m10; int m14;
    cTxH* Init(IAddRef1* p, int a, int b);
};
cTxH* cTxH::Init(IAddRef1* p, int a, int b)
{
    mnRef = 0;
    vtbl = kVtbl13fc598;
    mp8 = p;
    if (p) p->AddRef1();
    m10 = a;
    m14 = b;
    return this;
}

// @ 0x006166b0
struct cTxI {
    bool HandleResult(int err, cHttpResult* r, void* unused);
};
bool cTxI::HandleResult(int err, cHttpResult* r, void* unused)
{
    if (r) {
        IRel2* p = r->mpResponse;
        if (p) {
            r->mpResponse = 0;
            p->ReleaseSlot2();
        }
    }
    return false;
}

// @ 0x006166e0
struct cTxJ {
    void** vtbl; int mnRef; IAddRef1* mp8; IAddRef1* mpC;
    cTxJ* Init(IAddRef1* a, IAddRef1* b);
};
cTxJ* cTxJ::Init(IAddRef1* a, IAddRef1* b)
{
    mnRef = 0;
    vtbl = kVtbl13fc5bc;
    mp8 = a;
    if (a) a->AddRef1();
    mpC = b;
    if (b) b->AddRef1();
    return this;
}

// @ 0x00616730
struct IFnObj { virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5(); virtual void Fn18(); };
struct cHttpResult2 {
    char pad[0x43c];
    int mnStatus;                         // +0x43c
    char pad2[0xf3c - 0x440];
    IRel2* mpResponse;                    // +0xf3c
};
struct cTxK {
    void** vtbl; int mnRef; IFnObj* mp8; uint32_t mpC;
    bool HandleResult(int err, cHttpResult2* r, void* unused);
};
bool cTxK::HandleResult(int err, cHttpResult2* r, void* unused)
{
    mp8->Fn18();
    uint32_t v = 0;
    if (err == 0)
        v = mpC;
    else if (r && r->mnStatus == 0x23f)
        v = mpC;
    GetMessageServer()->PostMessage(0x60ba744, (void*)v, 0);
    if (r) {
        IRel2* p = r->mpResponse;
        if (p) {
            r->mpResponse = 0;
            p->ReleaseSlot2();
        }
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// index sorting by record timestamp (records are 0x118 bytes, 64-bit time at +0x30)
// ---------------------------------------------------------------------------------------------
struct sTimedRec { char pad[0x30]; __int64 mTime; char pad2[0x118 - 0x38]; };
struct sTimedOwner { char pad[0x60]; sTimedRec* mpTable; };
struct cTimeGreater {
    sTimedOwner* mpOwner;
    bool operator()(unsigned a, unsigned b) const;   // 0x00616220 (out of line)
};
// @ 0x00616220 (defined in slice s00614f20): out-of-line comparison, declared here only
// The inlined copies below expand the same comparison.
struct cTimeGreaterInl {
    sTimedOwner* mpOwner;
    bool operator()(unsigned a, unsigned b) const {
        return mpOwner->mpTable[a].mTime > mpOwner->mpTable[b].mTime;
    }
};

// @ 0x006167a0   eastl::insertion_sort<unsigned*, cTimeGreater>
void insertion_sort(unsigned* first, unsigned* last, cTimeGreaterInl compare)
{
    if (first != last) {
        unsigned *iCurrent, *iNext, *iSorted = first;
        for (++iSorted; iSorted != last; ++iSorted) {
            const unsigned temp(*iSorted);
            iNext = iCurrent = iSorted;
            for (--iCurrent; (iNext != first) && compare(temp, *iCurrent); --iNext, --iCurrent)
                *iNext = *iCurrent;
            *iNext = temp;
        }
    }
}

// @ 0x00616820   unguarded insertion sort over [first, last)
void insertion_sort_unguarded(unsigned* first, unsigned* last, cTimeGreaterInl compare)
{
    for (unsigned* i = first; i != last; ++i) {
        const unsigned value(*i);
        unsigned *end(i), *prev(i);
        for (--prev; compare(value, *prev); --end, --prev)
            *end = *prev;
        *end = value;
    }
}

// @ 0x006168a0   eastl::median<unsigned, cTimeGreater>
inline const unsigned& median(const unsigned& a, const unsigned& b, const unsigned& c, cTimeGreaterInl compare)
{
    if (compare(a, b)) {
        if (compare(b, c))
            return b;
        else if (compare(a, c))
            return c;
        else
            return a;
    } else if (compare(a, c))
        return a;
    else if (compare(b, c))
        return c;
    return b;
}
const unsigned& median_unsigned(const unsigned& a, const unsigned& b, const unsigned& c, cTimeGreaterInl compare)
{
    return median(a, b, c, compare);
}

// @ 0x00616a00   eastl::promote_heap<unsigned*, int, unsigned, cTimeGreater>
void promote_heap(unsigned* first, int topPosition, int position, const unsigned value, cTimeGreaterInl compare)
{
    for (int parentPosition = (position - 1) >> 1;
         (position > topPosition) && compare(*(first + parentPosition), value);
         parentPosition = (position - 1) >> 1) {
        *(first + position) = *(first + parentPosition);
        position = parentPosition;
    }
    *(first + position) = value;
}

// ---------------------------------------------------------------------------------------------
// eastl::basic_string<char>
// ---------------------------------------------------------------------------------------------
extern char gEmptyString8[];            // 0x01667bac
template <typename T> inline const T& emax(const T& a, const T& b) { return (a < b) ? b : a; }
struct string8 {
    char* mpBegin; char* mpEnd; char* mpCapacity; int mAllocator;
    void SetCapacity(size_type n);              // 0x0061c280
    string8& append(size_type n, char c);       // 0x00616960
    void AllocateSelf(size_type n);             // 0x00616aa0
    static size_type GetNewCapacity(size_type nCurrentCapacity) { return (nCurrentCapacity > 8) ? (2 * nCurrentCapacity) : 8; }
    void reserve(size_type n) {
        n = emax(n, (size_type)(mpEnd - mpBegin));
        if ((n + 1) > (size_type)(mpCapacity - mpBegin))
            SetCapacity(n + 1);
    }
};

// @ 0x00616960
string8& string8::append(size_type n, char c)
{
    const size_type nLength = (size_type)(mpEnd - mpBegin);
    const size_type nCapacity = (size_type)((mpCapacity - mpBegin) - 1);
    if ((nLength + n) > nCapacity)
        reserve(emax(GetNewCapacity(nCapacity), (size_type)(nLength + n)));
    if (n > 0) {
        memset(mpEnd + 1, (unsigned char)c, n - 1);
        *mpEnd = c;
        mpEnd += n;
        *mpEnd = 0;
    }
    return *this;
}

// @ 0x00616aa0
void string8::AllocateSelf(size_type n)
{
    if (n > 1) {
        mpBegin = (char*)EASTL_alloc(n, "Editor", 0, 0, "UTFKernel\\EASTL\\string.h", 0xd1);
        mpEnd = mpBegin;
        mpCapacity = mpBegin + n;
    } else {
        mpBegin = gEmptyString8;
        mpEnd = gEmptyString8;
        mpCapacity = gEmptyString8 + 1;
    }
}

// ---------------------------------------------------------------------------------------------
// pooled transaction objects: scalar deleting destructors that return the object to a free list
// ---------------------------------------------------------------------------------------------
extern void* gFreeListA;   // 0x015f52e4
extern void* gFreeListB;   // 0x015f5194
extern void* gFreeListC;   // 0x015f51d8 (cAssetUploadTransaction pool)
extern void* gFreeListD;   // 0x015f5590 (cModelUploadTransaction pool)

struct cPoolTxA {
    void** vtbl;
    void* Destroy(unsigned flags);        // 0x00616b00
};
// @ 0x00616b00
void* cPoolTxA::Destroy(unsigned flags)
{
    vtbl = kBaseVtbl;
    if (flags & 1) {
        *(void**)this = gFreeListA;
        gFreeListA = this;
    }
    return this;
}

struct cPoolTxB {
    void** vtbl;
    void* Destroy(unsigned flags);        // 0x00616b20
};
// @ 0x00616b20
void* cPoolTxB::Destroy(unsigned flags)
{
    vtbl = kBaseVtbl;
    if (flags & 1) {
        *(void**)this = gFreeListB;
        gFreeListB = this;
    }
    return this;
}

struct cTxUp1 {                           // class "cAssetUploadTransaction"
    void** vtbl; int mnRef; IAddRef* pad8[3];
    IAddRef* mpAssetMetadata;             // +0x14
    void* Destroy(unsigned flags);        // 0x00616b40
};
// @ 0x00616b40
void* cTxUp1::Destroy(unsigned flags)
{
    IAddRef* m = mpAssetMetadata;
    vtbl = kVtbl13fc484;
    if (m) m->Release();
    vtbl = kBaseVtbl;
    if (flags & 1) {
        *(void**)this = gFreeListC;
        gFreeListC = this;
    }
    return this;
}

struct cTxUp2 {                           // class "cModelUploadTransaction"
    void** vtbl; int mnRef; IAddRef* pad8[3];
    IAddRef* mpAssetMetadata;             // +0x14
    void* Destroy(unsigned flags);        // 0x00616d20
};
// @ 0x00616d20
void* cTxUp2::Destroy(unsigned flags)
{
    IAddRef* m = mpAssetMetadata;
    vtbl = kVtbl13fc4a8;
    if (m) m->Release();
    vtbl = kBaseVtbl;
    if (flags & 1) {
        *(void**)this = gFreeListD;
        gFreeListD = this;
    }
    return this;
}

// ---------------------------------------------------------------------------------------------
// transaction results
// ---------------------------------------------------------------------------------------------
struct cServerResponseLite {              // SP::Pollen::cServerResponse (only what is used here)
    void* vtbl; int mnRef; void* vtblStream; int mnReturnCode;
    const wchar_t* GetField(const wchar_t* name);   // 0x00614e50
};
struct IStreamLite {
    virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4();
    virtual int GetState();               // +0x14
    virtual bool Close();                 // +0x18
};
struct cAssetMetadata {
    virtual int AddRef();
    virtual int Release();
    virtual int slot8();
    virtual void* Cast(uint32_t typeID);
    uint32_t* GetServerID();              // 0x005507a0
};
struct cAssetDirectory {
    void AddMapping(uint32_t lo, uint32_t hi, ResourceKey* key);   // 0x0054e250
    bool GetServerId(const ResourceKey* key, uint32_t* out, bool b);   // 0x0054e530
    void Fn54ed50(uint32_t lo, uint32_t hi, int a);                // 0x0054ed50
    void Fn54e7b0(uint32_t lo, uint32_t hi, int a);                // 0x0054e7b0
};
u64 StrtoU64(const wchar_t* s, wchar_t** end, int base);           // 0x0092d710
struct cTransactionBase { int mnRefCount; };
struct cTransactionQueue { void Enqueue(void* t, bool b); };        // 0x0060eaf0
void* AllocTransaction(unsigned size);                              // 0x00615840
struct cModelUploadTransactionLite {                                 // ctor 0x00615e50
    void* operator new(size_t n) { return AllocTransaction((unsigned)n); }
    cModelUploadTransactionLite(cAssetMetadata* m, cAssetDirectory* dir, bool a, bool b, unsigned n);
    char pad[0x38];
};
struct sUploadMsg { bool ok; ResourceKey key; };

struct cTxUpload {                                                  // cAssetUploadTransaction (retail 0x30 bytes)
    void** vtbl; int mnRef;
    ResourceKey mKey;                     // +8
    cAssetMetadata* mpAssetMetadata;      // +0x14
    cAssetDirectory* mpAssetDir;          // +0x18
    int pad1c;
    union { u64 mnNextAssetID; struct { uint32_t mnNextLo, mnNextHi; }; };   // +0x20
    bool mbA; bool mbB;                   // +0x28, +0x29
    unsigned mnRetries;                   // +0x2c
    bool HandleResult(int err, cHttpResult* r, cTransactionQueue* q);       // 0x00616b80
};

// @ 0x00616b80
bool cTxUpload::HandleResult(int err, cHttpResult* r, cTransactionQueue* q)
{
    bool result = false;
    IRel2** pRef;
    if (err != 0) {
        if (!r) goto retry;
        pRef = &r->mpResponse;
        if (*pRef) ((IResp*)*pRef)->Close();
    } else {
        pRef = &r->mpResponse;
        cServerResponseLite* o = *pRef ? (cServerResponseLite*)((char*)*pRef - 8) : 0;
        IStreamLite* s = (IStreamLite*)((char*)o + 8);
        int state = s->GetState();
        s->Close();
        if (state == 0 && o->mnReturnCode == 0) {
            uint32_t* sid = mpAssetMetadata->GetServerID();
            uint32_t lo = sid[0];
            uint32_t hi = sid[1];
            mpAssetDir->AddMapping(lo, hi, &mKey);
            const wchar_t* idText = o->GetField(L"next-id");
            if (idText)
                mnNextAssetID = StrtoU64(idText, 0, 10);
            result = true;
        }
    }
    {
        IRel2* ref = *pRef;
        if (ref) {
            *pRef = 0;
            ref->ReleaseSlot2();
        }
    }
    if (!result) {
retry:
        if (err != 8) {
            mnNextLo = 0xffffffffu;
            mnNextHi = 0xffffffffu;
            cModelUploadTransactionLite* t = new cModelUploadTransactionLite(mpAssetMetadata, mpAssetDir, mbA, mbB, mnRetries);
            ((cTransactionQueue*)q)->Enqueue(t, true);
        }
        return result;
    }
    sUploadMsg m;
    m.ok = true;
    m.key = mKey;
    GetMessageServer2()->PostMessage(0x68cd252, &m, 0);
    return result;
}

// ---------------------------------------------------------------------------------------------
// download job creation (0x00616d60) and the related transaction handlers
// ---------------------------------------------------------------------------------------------
struct cTripleObj {                       // three-base object, see slice s00614f20 (0x00616160)
    void** v0; void** v4; void** v8;
    volatile long mnRef;
    IAddRef* m10;                         // refcounted: AddRef +0, Release +4
    struct SubOwner* m14;                 // object with refcounted subobject at +4
    ResourceKey m18;                      // +0x18
    cTripleObj();                         // 0x00616160
};
struct SubIface { virtual int AddRefSub(); virtual int ReleaseSub(); };
struct SubOwner { void* vtbl; SubIface sub; };
struct cOwnerWithKey { char pad[8]; ResourceKey mKey; };   // db object: key at +8

struct cJob {                             // SP::cJob
    void* mpFn; void* mp4; char pad[0x10]; int mnStatus;   // +0x18
    void Attach(cTripleObj* o);           // 0x0068f9b0
    void Start();                         // 0x006909b0
    void Release();                       // 0x00690120 (smart pointer release)
};
struct cJobManager {
    virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3();
    virtual bool CreateJob(cJob** out);   // +0x10
};
cJobManager* GetJobManager();             // 0x0068f4d0
extern void JobFn68f5a0();                // 0x0068f5a0

struct IIObj { virtual int AddRef(); virtual int Release(); };
struct IAddRefOwner { virtual int AddRef(); virtual int Release(); };

// @ 0x00616d60
void CreateDownloadJob(IAddRef* pDb, SubOwner* pOwner, const ResourceKey* pKey)
{
    cJob* job = 0;
    cJobManager* mgr = GetJobManager();
    {
        cJob* old = job;
        if (old) {
            job = 0;
            old->Release();
        }
    }
    if (!mgr->CreateJob(&job)) {
        if (job) job->Release();
        return;
    }
    cTripleObj* o = new ("Pollinator", 0, 0, 0, 0) cTripleObj();
    if (o) ((IAddRef*)o)->AddRef();
    job->mnStatus = 4;
    void* p4 = o ? &o->v4 : 0;
    job->mpFn = (void*)JobFn68f5a0;
    job->mp4 = p4;
    job->Attach(o);
    IAddRef* oldDb = o->m10;
    if (pDb != oldDb) {
        if (pDb) pDb->AddRef();
        o->m10 = pDb;
        if (oldDb) oldDb->Release();
    }
    SubOwner* oldOwner = o->m14;
    if (pOwner != oldOwner) {
        if (pOwner) pOwner->sub.AddRefSub();
        o->m14 = pOwner;
        if (oldOwner) oldOwner->sub.ReleaseSub();
    }
    const ResourceKey* k = pKey ? pKey : (const ResourceKey*)((char*)pDb + 8);
    o->m18 = *k;
    job->Start();
    ((IAddRef*)o)->Release();
    if (job) job->Release();
}

// @ 0x00616ed0
struct cAssetMetadataLite : IAddRef {
    virtual int slot2();
    virtual void* Cast(uint32_t typeID);  // +0x0c
};
struct cPollinatorDir { char pad[0x58]; cAssetDirectory* mpAssetDirectory; };
cPollinatorDir* GetPollinatorDir();       // 0x0067cb30
void __cdecl SetCachingType(int type, void* a);   // 0x006ac040
void* __cdecl Fn6ad010(void* a);                  // 0x006ad010
void* __cdecl GetSaveArea(uint32_t id);           // 0x006b1f90

struct cResponseObj {                     // cServerResponse: IStream subobject at +8
    char pad[8];
    IStreamLite stream;
};
struct cResponseRef {
    virtual int s0(); virtual int s1();
    virtual int ReleaseSlot2();
};
struct cTxDownload {
    void** vtbl; int mnRef; char pad8[8];
    ResourceKey mKey;                     // +0x10
    cResponseObj* mpResp;                 // +0x1c
    cAssetMetadataLite* mpMetadata;       // +0x20
    bool HandleResult(int err, void* a, void* b);   // 0x00616ed0
};
bool cTxDownload::HandleResult(int err, void* a, void* b)
{
    ResourceKey scratch;
    bool closed;
    if (!mpResp)
        closed = false;
    else
        closed = mpResp->stream.Close();
    {
        cResponseRef* p = (cResponseRef*)mpResp;
        if (p) {
            mpResp = 0;
            p->ReleaseSlot2();
        }
    }
    if (closed && err == 0) {
        SetCachingType(10, mpMetadata);
        void* x = mpMetadata ? mpMetadata->Cast(0x2269ed1) : 0;
        Fn6ad010(x);
        scratch.instanceID = mKey.instanceID;
        scratch.typeID = 0x1a99b06b;
        scratch.groupID = mKey.groupID;
        CreateDownloadJob(mpMetadata, (SubOwner*)GetSaveArea(0x11ac19d), &scratch);
        return true;
    }
    cAssetDirectory* dir = GetPollinatorDir()->mpAssetDirectory;
    uint32_t* id = (uint32_t*)&scratch;
    if (dir->GetServerId(&mKey, id, false)) {
        if (err != 0xb)
            dir->Fn54ed50(id[0], id[1], 0);
        dir->Fn54e7b0(id[0], id[1], 0);
    }
    return false;
}

// @ 0x00617010   cGetFeedEntryThumbnailTransaction::ConstructRequest
struct cFeedDoc {                         // SP::Feed::AtomDocument: entries of 0x118 bytes at +0x60..+0x64
    char pad[0x60];
    char* mpEntriesBegin;
    char* mpEntriesEnd;
};
struct IRecordLite {
    virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5();
    virtual void* GetStream();            // +0x18
};
struct IDatabase {
    virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3(); virtual int s4(); virtual int s5(); virtual int s6(); virtual int s7(); virtual int s8(); virtual int s9(); virtual int s10(); virtual int s11(); virtual int s12();
    virtual bool OpenRecord(const ResourceKey* key, IRel2** pOut, int access, int createMode, int a, int b);   // +0x34
};
struct cHttpRequestRef {                  // EA::AutoRefCount<HTTPRequest> wrapper (out-of-line helpers)
    char* mp;
    void** GetAddressOf();                // 0x0060d240
    void Release();                       // 0x0060d210
};
bool __cdecl CreateHTTPGetRequest(const char* url, void* stream, void** ppOut);   // 0x00944450

struct cTxThumbnail {
    void** vtbl; int mnRef; char pad8[4];
    cFeedDoc* mpFeed;                     // +0xc
    unsigned mnEntryIndex;                // +0x10
    ResourceKey mAssetKey;                // +0x14 (instance, ?, group)
    int pad20;
    IRel2* mpRecord;                      // +0x24
    bool ConstructRequest(char** ppOut);   // 0x00617010
};
bool cTxThumbnail::ConstructRequest(char** ppOut)
{
    cFeedDoc* feed = mpFeed;
    if (feed) {
        int count = (int)(feed->mpEntriesEnd - feed->mpEntriesBegin) / 0x118;
        if (mnEntryIndex <= (unsigned)count) {
            char* entry = feed->mpEntriesBegin + mnEntryIndex * 0x118;
            ResourceKey key = mAssetKey;
            key.typeID = 0x2f7d0004;
            IDatabase* db = (IDatabase*)GetSaveArea(0x11ac19d);
            if (db) {
                IRel2** pRecord = &mpRecord;
                if (*pRecord) {
                    IRel2* old = *pRecord;
                    *pRecord = 0;
                    old->ReleaseSlot2();
                }
                if (db->OpenRecord(&key, pRecord, 2, 2, 0, 0)) {
                    IRecordLite* rec = (IRecordLite*)*pRecord;
                    const char* url = *(const char**)(entry + 0xa8);
                    cHttpRequestRef req;
                    req.mp = 0;
                    if (CreateHTTPGetRequest(url, rec->GetStream(), req.GetAddressOf())) {
                        *(int*)(req.mp + 0xd94) = 0x15206f0;
                        _InterlockedExchangeAdd((volatile long*)(req.mp + 4), 1);
                        *ppOut = req.mp;
                    }
                    req.Release();
                    return true;
                }
            }
        }
    }
    return false;
}
