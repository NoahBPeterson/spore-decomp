// slice s006b47a0: SP::cString and its async-save helpers.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef unsigned short wchar16;

volatile int g_opaqueGlobal;

// ---------------------------------------------------------------------------
// External helpers (call targets are masked relocations).
// ---------------------------------------------------------------------------
__declspec(dllimport) void* __cdecl SteamApps();
void __cdecl EA_Free(void* p);
void* __cdecl FUN_0067de50();   // returns cStringManager* (global 0x15fd8fc)
void* __cdecl FUN_0067de40();   // returns resource manager (global 0x15fd8f8)

// ---------------------------------------------------------------------------
// Generic polymorphic stubs.
// ---------------------------------------------------------------------------
struct IRefCountedStub {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
};

struct ISteamApps {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual bool v6(const char* p);
};

// @ 0x006b4f40
bool __cdecl FUN_006b4f40(const char* p)
{
    ISteamApps* pApps = (ISteamApps*)SteamApps();
    if (pApps != 0)
        return pApps->v6(p);
    return 0;
}

// ---------------------------------------------------------------------------
// cString sink helper (retail layout matches cString's payload).
// ---------------------------------------------------------------------------
struct CSink {
    uint32_t mField0;        // +0x0
    uint32_t mField4;        // +0x4
    uint32_t mField8;        // +0x8
    uint32_t mFieldC;        // +0xc
    bool     mField10;       // +0x10
    char     mPad11;         // +0x11

    CSink(uint32_t a, uint32_t b);
    void FUN_006b4f90(bool b);
    void FUN_006b4fa0(const void* arg);
    void FUN_006b4fd0(const void* arg);
    void FUN_006b5000();
};

// @ 0x006b4f60
CSink::CSink(uint32_t a, uint32_t b)
{
    mField0 = 0;
    mField4 = 0;
    mField8 = a;
    mFieldC = b;
    mField10 = true;
}

// @ 0x006b4f90
void CSink::FUN_006b4f90(bool b)
{
    mField10 = mField10 & b;
}

// @ 0x006b4fa0
void CSink::FUN_006b4fa0(const void* arg)
{
    if (mField10) {
        bool __cdecl FUN_00693390(uint32_t src, const void* arg, uint32_t placeholder);
        mField10 = mField10 & FUN_00693390(mField8, arg, mFieldC);
    }
}

// @ 0x006b4fd0
void CSink::FUN_006b4fd0(const void* arg)
{
    if (mField10) {
        bool __cdecl FUN_00694440(uint32_t src, const void* arg, uint32_t placeholder);
        mField10 = mField10 & FUN_00694440(mField8, arg, mFieldC);
    }
}

// @ 0x006b5000
void CSink::FUN_006b5000()
{
    if (mField4 != 0) {
        ((IRefCountedStub*)mField4)->v9();
        ((IRefCountedStub*)mField4)->v2();
        mField4 = 0;
        mField8 = 0;
    }
}

extern bool g_ColorLocalized;

// @ 0x006b5030
void __cdecl SP_cString_SetColorLocalized(bool b)
{
    g_ColorLocalized = b;
}

// @ 0x006b5040
void __cdecl FUN_006b5040(uint32_t a, uint32_t b, uint32_t c, uint32_t* out)
{
    out[0] = a;
    out[1] = b;
}

// ---------------------------------------------------------------------------
// SP::cString
// ---------------------------------------------------------------------------
namespace SP {

class cString;
class cStringDetokenizer;
class cStringManager;
struct IRefCounted;

struct string16 {
    wchar16* mpBegin;      // +0
    wchar16* mpEnd;        // +4
    wchar16* mpCapacity;   // +8
    int      mAllocator;   // +0xc
};

// EA::AutoRefCount: plain pointer + user destructor (this is what makes the
// /EHsc frame appear in the cString constructor).
struct IRefCounted {
    virtual void AddRef();
    virtual void Release();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
};

struct AutoRefCount {
    IRefCounted* mpObject;   // +0
    explicit AutoRefCount(IRefCounted* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    void Release() { IRefCounted* p = mpObject; if (p) { mpObject = 0; p->Release(); } }
};

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

class cStringDetokenizer { public:
    virtual void v0();                                          // +0x00
    virtual void v1();                                          // +0x04
    virtual void v2();                                          // +0x08
    virtual void v3();                                          // +0x0c
    virtual bool TranslateToken(const wchar16*, string16&);     // +0x10
    virtual void func14h(int);                                  // +0x14
    virtual void func18h();                                     // +0x18
    virtual void AddTranslator(void*);                          // +0x1c
    virtual void RemoveTranslator(void*);                       // +0x20
    virtual bool HasTokens(const wchar16*);                     // +0x24
    virtual bool func28h(int, void*);                           // +0x28
    virtual bool ProcessString(const wchar16*, string16&);      // +0x2c
    virtual bool func30h(void*, void*, void*);                  // +0x30
    virtual void func34h(const wchar16*, int);                  // +0x34
    virtual bool ProcessStringEx(const wchar16*, string16&);    // +0x38
    virtual bool FindTokenTranslation(const wchar16*, string16&);// +0x3c
};

class cStringManager { public:
    virtual ~cStringManager();                                  // +0x00
    virtual void AddString(cString*);                           // +0x04
    virtual void RemoveString(cString*);                        // +0x08
    virtual void v3();                                          // +0x0c
    virtual cStringDetokenizer* GetStringDetokenizer();         // +0x10
};

extern wchar16 sDefaultCStr[];
extern char g_placeholderMap[];   // eastl hash_map<uint32_t, string16> @ 0x15308a8

struct HashMap {
    void erase_key(uint32_t* key);
};

class cString { public:
    AutoRefCount mpTableResource; // +0x0
    string16* mpLocalString;      // +0x4
    const wchar16* mpSourceCStr;  // +0x8
    uint32_t mPlaceholderId;      // +0xc
    bool mbHasTokens;             // +0x10
    bool mField11;                // +0x11
    cString* Self() { return this; }

    cString();
    cString(const cString& other);
    ~cString();
    bool Load(uint32_t tableID, uint32_t instanceID, int group);
    cString& operator=(const cString& other);
    void set_source_string(const wchar16* src, bool alloc);
    const wchar16* GetText();
};

// @ 0x006b5060
cString::cString()
    : mpTableResource(0), mpLocalString(0), mpSourceCStr(sDefaultCStr),
      mPlaceholderId(0), mbHasTokens(false), mField11(false)
{
    if (FUN_0067de50() != 0)
        ((cStringManager*)FUN_0067de50())->AddString(this);
}

// @ 0x006b5240
cString::~cString()
{
    if (FUN_0067de50() != 0)
        ((cStringManager*)FUN_0067de50())->RemoveString(this);
    if (mpLocalString != 0) {
        string16* s = mpLocalString;
        wchar16* p = s->mpBegin;
        int n = ((int)(size_t)s->mpCapacity - (int)(size_t)p) & 0xfffffffe;
        if (n > 2 && p != 0)
            EA_Free(p);
        EA_Free(s);
        mpLocalString = 0;
    }
    if (mPlaceholderId != 0) {
        uint32_t id = mPlaceholderId;
        ((HashMap*)g_placeholderMap)->erase_key(&id);
        mPlaceholderId = 0;
    }
    mpTableResource.Release();
}

// @ 0x006b5310
void cString::set_source_string(const wchar16* src, bool alloc)
{
    if (mPlaceholderId != 0) {
        uint32_t id = mPlaceholderId;
        ((HashMap*)g_placeholderMap)->erase_key(&id);
        mPlaceholderId = 0;
    }
    if (src != 0 && src[0] != 0 && src != sDefaultCStr) {
        if (!alloc) {
            mpSourceCStr = src;
        } else {
            uint32_t __cdecl FUN_006b51a0(const wchar16*);
            uint32_t* __cdecl FUN_006b50d0(uint32_t);
            uint32_t id = FUN_006b51a0(src);
            mPlaceholderId = id;
            mpSourceCStr = (const wchar16*)*FUN_006b50d0(id);
        }
        mbHasTokens = ((cStringManager*)FUN_0067de50())->GetStringDetokenizer()->HasTokens(mpSourceCStr);
        return;
    }
    mbHasTokens = false;
    mpSourceCStr = sDefaultCStr;
}

// @ 0x006b5430
cString& cString::operator=(const cString& other)
{
    if (this != &other) {
        IRefCounted* old = mpTableResource.mpObject;
        IRefCounted* nw = other.mpTableResource.mpObject;
        if (nw != old) {
            if (nw != 0)
                nw->AddRef();
            mpTableResource.mpObject = nw;
            if (old != 0)
                old->Release();
        }
        mpSourceCStr = other.mpSourceCStr;
        mbHasTokens = other.mbHasTokens;
        mField11 = false;
        if (other.mPlaceholderId != 0) {
            uint32_t* __cdecl FUN_006b50d0(uint32_t);
            uint32_t* p = FUN_006b50d0(other.mPlaceholderId);
            if (p != 0) {
                set_source_string((const wchar16*)*p, true);
                return *this;
            }
            set_source_string(sDefaultCStr, false);
        }
    }
    return *this;
}

// Resource-manager stub (enough slots for the vtable calls in Load).
struct IResourceMgr {
    virtual void r0();
    virtual void r1();
    virtual void r2();
    virtual void r3();
    virtual void r4();
    virtual void r5();
    virtual void r6();
    virtual void r7();
    virtual void r8();
    virtual void r9(ResourceKey*, cString*);   // +0x24
};

// Resource stub for slot 0x14.
struct IResource {
    virtual void q0();
    virtual void q1();
    virtual void q2();
    virtual void q3();
    virtual void q4();
    virtual const wchar16* q5(int group);      // +0x14
};

// @ 0x006b54b0
bool cString::Load(uint32_t tableID, uint32_t instanceID, int group)
{
    mField11 = false;
    if (mpLocalString != 0) {
        wchar16* p = mpLocalString->mpBegin;
        int n = ((int)(size_t)mpLocalString->mpCapacity - (int)(size_t)p) & 0xfffffffe;
        if (n > 2 && p != 0)
            EA_Free(p);
        EA_Free(mpLocalString);
    }
    IRefCounted* t = mpTableResource.mpObject;
    mpLocalString = 0;
    if (t == 0) {
        if (tableID == 0xffffffff || instanceID == 0xffffffff)
            goto after_load;
    } else if (*(uint32_t*)((char*)t + 8) == tableID) {
        goto after_load;
    }
    {
        IResourceMgr* mgr = (IResourceMgr*)FUN_0067de40();
        if (mpTableResource.mpObject != 0) {
            IRefCounted* r = mpTableResource.mpObject;
            mpTableResource.mpObject = 0;
            r->Release();
        }
        ResourceKey key;
        key.instanceID = tableID;
        key.typeID = 0x2fac0b6;
        key.groupID = 0x2fabf01;
        mgr->r9(&key, this);
    }
after_load:
    if (mPlaceholderId != 0) {
        uint32_t id = mPlaceholderId;
        ((HashMap*)g_placeholderMap)->erase_key(&id);
        mPlaceholderId = 0;
    }
    IRefCounted* res = mpTableResource.mpObject;
    mbHasTokens = false;
    mpSourceCStr = sDefaultCStr;
    if (res != 0) {
        const wchar16* s = ((IResource*)res)->q5(group);
        if (s == 0 || s[0] == 0)
            s = 0;
        else
            set_source_string(s, false);
        if (mpTableResource.mpObject != 0 && s != 0)
            return true;
    }
    return false;
}

// @ 0x006b55c0
const wchar16* cString::GetText()
{
    if (mField11) {
        string16* s0 = mpLocalString;
        if (s0 == 0)
            return 0;
        return s0->mpBegin;
    }
    if (!mbHasTokens && !g_ColorLocalized)
        return mpLocalString->mpBegin;
    cStringDetokenizer* d = ((cStringManager*)FUN_0067de50())->GetStringDetokenizer();
    d->ProcessString(mpSourceCStr, *mpLocalString);
    return mpLocalString->mpBegin;
}

} // namespace SP

// ---------------------------------------------------------------------------
// Async-save cluster: SP save-queue job holder + App/AsyncSave job.
// ---------------------------------------------------------------------------
namespace EA { namespace Thread {
class Mutex {
public:
    char mData[0x30];
    int Lock(unsigned* pTimeout);   // 0x009221b0
    int Unlock();                   // 0x00922270
};
}} // namespace EA::Thread

extern EA::Thread::Mutex g_saveMutex;      // 0x01604b50
extern unsigned          g_lockTimeout;    // 0x014099b8
extern int               g_saveJobReady;   // 0x01604b80

struct cJob {
    void*    mpCallback;        // +0x00
    void*    mpCallbackData;    // +0x04
    void*    mpExtraObject;     // +0x08
    void*    mpDebugName;       // +0x0c
    int      mPriority;         // +0x10
    int      mStatus;           // +0x14
    uint32_t mThreadAffinity;   // +0x18
    int      mSlot;             // +0x1c
    void*    mpReturnValue;     // +0x20
    void*    mpCleanupValue;    // +0x24

    int  AddRef();                          // 0x0068f950
    int  Release();                         // 0x00690120
    void Wait();                            // 0x006926b0
    void AddWeakDependency(cJob* pOther);   // 0x006913c0
    void AddDependency(cJob* pOther);       // 0x00691380
    int  GetStatus();                       // 0x006909b0
    void SetResult(void* pValue);           // 0x0068f9b0
};

extern cJob* g_saveJob;   // 0x01604b48

struct MutexScopedLock {
    EA::Thread::Mutex* mpMutex;
    MutexScopedLock(EA::Thread::Mutex* m) : mpMutex(m) { m->Lock(&g_lockTimeout); }
    ~MutexScopedLock() { mpMutex->Unlock(); }
};

inline void* operator new(uint32_t, void* p) { return p; }

void* __cdecl FUN_0067dcd0();      // 0x0067dcd0 EA::ResourceMan::GetManager
void* __cdecl FUN_0068f4d0();      // 0x0068f4d0 cJobManager getter
void* __cdecl ZoneObject_new(uint32_t nSize, const char* pName, int, int, int, int);  // 0x00926020
int   __cdecl FUN_00695cf0(void* p);   // 0x00695cf0
int   __cdecl FUN_006b4390(void** p);  // 0x006b4390
void  __cdecl FUN_006b4710();      // 0x006b4710
void  __cdecl FUN_006b4720();      // 0x006b4720
void  __cdecl FUN_006b4b50();      // 0x006b4b50

struct IRefC {                 // refcounted interface (slot 0 = AddRef, slot 1 = Release)
    virtual void v0();         // +0x00
    virtual void v1();         // +0x04
    virtual void v2();         // +0x08
    virtual void v3();         // +0x0c
    virtual void v4();         // +0x10
    virtual void v5();         // +0x14
    virtual void v6();         // +0x18
    virtual void v7();         // +0x1c
};

struct ResMgr {                // EA::ResourceMan manager (0x0067dcd0)
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17();
    virtual void* FindResource(uint32_t a, uint32_t b);      // slot 0x12 / +0x48
    virtual void m19(); virtual void m20(); virtual void m21();
    virtual void* GetByKey(void* key);                       // slot 0x16 / +0x58
};

struct JobMgr {                // SP::cJobManager (0x0068f4d0)
    virtual void j0(); virtual void j1(); virtual void j2(); virtual void j3();
    virtual bool BeginJob(cJob** pOut);      // slot 4  / +0x10
    virtual void j5(); virtual void j6(); virtual void j7();
    virtual void Lock();                     // slot 8  / +0x20
    virtual void Unlock();                   // slot 9  / +0x24
};

struct Key3 { uint32_t inst, type, group; };

struct ILocal2 {               // object returned by ILocal::Get
    virtual void n0(); virtual void n1(); virtual void n2(); virtual void n3();
    virtual void n4(); virtual void n5(); virtual void n6(); virtual void n7();
    virtual void n8(); virtual void n9(); virtual void nA(); virtual void nB();
    virtual void nC(); virtual void nD();
    virtual bool Write(void* pData, int nSize);   // slot 0xe / +0x38
};

struct ILocal {                // object produced by the resource provider
    virtual void l0();         // +0x00
    virtual void l1();         // +0x04
    virtual void Release();    // +0x08 (slot 2)
    virtual void l3();         // +0x0c
    virtual void l4();         // +0x10
    virtual void l5();         // +0x14
    virtual ILocal2* Get();    // +0x18 (slot 6)
    virtual void l7();         // +0x1c
    virtual void l8();         // +0x20
    virtual bool Check();      // +0x24 (slot 9)
};

struct IProv {                 // provider object at +0x1c
    virtual void p0(); virtual void p1(); virtual void p2();
    virtual uint32_t GetKind();                       // slot 3 / +0x0c
    virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
    virtual void p8(); virtual void p9(); virtual void pA(); virtual void pB();
    virtual void pC();
    virtual bool Make(void* pKey, void** ppOut);      // slot 0xd / +0x34
};

struct IResProv {              // param_3 in FUN_006b4b60
    virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3();
    virtual void q4(); virtual void q5(); virtual void q6(); virtual void q7();
    virtual void q8(); virtual void q9();
    virtual bool Run(void* pA, void* pB, int c, uint32_t d);   // slot 0xa / +0x28
};

struct GfarStream {            // EA::IO::GraphicsFactoryAsyncRequest at +0x20 (size 0x24)
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5();
    virtual void Flush();      // slot 6 / +0x18
    virtual int  Size();       // slot 7 / +0x1c
    GfarStream(void* pData, void* pUnused, const char* pName);  // 0x0093c270
    void* GetData();                                            // 0x0093ba70
    void  SetProperty(int index, float value);                  // 0x0093bb40
    char mData[0x20];
};

struct JobBaseA {              // primary base (cILayer)
    virtual void AddRef();     // slot 0
    virtual void Release();    // slot 1
    virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5();
};
struct AsyncSave;

struct JobBaseB {              // secondary base at +4 (BG6)
    virtual void b0(); virtual void b1(); virtual void b2();
    virtual void b3(); virtual void b4(); virtual void b5();
    virtual void b6(); virtual void b7(); virtual void b8();
    virtual bool Complete();       // slot 9 / +0x24; `this` is the +4 subobject
};

struct AsyncSave : JobBaseA, JobBaseB {
    uint32_t   m8;         // +0x08
    IRefC*     m0c;        // +0x0c
    Key3       m10;        // +0x10
    IProv*     m1c;        // +0x1c (provider, secondary interface at +4)
    GfarStream mStrm;      // +0x20
    uint32_t   m44;        // +0x44 (refcount)
    uint32_t   m48;        // +0x48
    uint32_t   m4c;        // +0x4c
    uint32_t   m50;        // +0x50
    uint16_t   m54;        // +0x54
    AsyncSave(IRefC* pTarget, void* pProvider, Key3* pKey);
    bool     Finish(cJob* c);
};

// @ 0x006b47a0
void __cdecl FUN_006b47a0(cJob* p)
{
    if (g_saveJobReady == 1) {
        MutexScopedLock lock(&g_saveMutex);
        p->AddWeakDependency(g_saveJob);
        if (p != g_saveJob) {
            cJob* old = g_saveJob;
            if (p)
                p->AddRef();
            g_saveJob = p;
            if (old)
                old->Release();
        }
    }
}

struct AutoRef {
    cJob* mpObject;
    AutoRef(cJob* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRef() { if (mpObject) mpObject->Release(); }
};

// @ 0x006b4840
void __cdecl FUN_006b4840()
{
    if (g_saveJobReady == 1) {
        g_saveMutex.Lock(&g_lockTimeout);
        AutoRef ref(g_saveJob);
        g_saveMutex.Unlock();
        if (ref.mpObject)
            ref.mpObject->Wait();
    }
}

// @ 0x006b48d0
AsyncSave::AsyncSave(IRefC* pTarget, void* pProvider, Key3* pKey)
    : mStrm(0, 0, "UTF/MemoryStream")
{
    m8 = 0;
    m0c = pTarget;
    if (pTarget != 0)
        pTarget->v0();
    m10 = *pKey;
    m1c = (IProv*)pProvider;
    if (pProvider != 0)
        ((IRefC*)((char*)pProvider + 4))->v0();
    m54 = 0;
    m44 = 1;
    m48 = 0;
    m4c = 0;
    m50 = 0;
    mStrm.s1();
    mStrm.SetProperty(1, 1.0f);
    mStrm.SetProperty(2, 2.0f);
    mStrm.SetProperty(3, 15000.0f);
}

// @ 0x006b4a10
bool AsyncSave::Finish(cJob* c)
{
    void* data = mStrm.GetData();
    int   size = mStrm.Size();
    ILocal* obj = 0;
    if (!m1c->Make(&m10, (void**)&obj)) {
        if (obj)
            obj->Release();
        return false;
    }
    ILocal2* p = obj->Get();
    bool w = p->Write(data, size);
    bool chk = obj->Check();
    bool res = (chk && w);
    mStrm.Flush();
    if (obj) {
        obj->Release();
        obj = 0;
    }
    if (m0c) {
        IRefC* t = m0c;
        m0c = 0;
        t->v1();
    }
    if (m1c) {
        IRefC* t = (IRefC*)((char*)m1c + 4);
        m1c = 0;
        t->v1();
    }
    c->SetResult(0);
    return res;
}

// @ 0x006b4b60
char __cdecl FUN_006b4b60(void* pArg0, void* pArg1, IResProv* pArg2, Key3* pArg3)
{
    char result = 0;
    ResMgr* mgr = (ResMgr*)FUN_0067dcd0();
    if (pArg0 != 0) {
        Key3 key;
        if (pArg3 == 0) {
            key.inst  = *(uint32_t*)((char*)pArg0 + 8);
            key.type  = *(uint32_t*)((char*)pArg0 + 0xc);
            key.group = *(uint32_t*)((char*)pArg0 + 0x10);
        } else {
            key = *pArg3;
        }
        if (pArg1 == 0) {
            pArg1 = mgr->GetByKey(&key);
            if (pArg1 == 0)
                return 0;
        }
        if (pArg2 == 0) {
            pArg2 = (IResProv*)mgr->FindResource(key.type, *(uint32_t*)((char*)pArg0 + 0xc));
            if (pArg2 == 0)
                return 0;
        }
        AsyncSave* mem = (AsyncSave*)ZoneObject_new(0x58, "App/AsyncSave", 0, 0, 0, 0);
        AsyncSave* job = 0;
        if (mem != 0)
            job = new (mem) AsyncSave((IRefC*)pArg0, pArg1, &key);
        if (job != 0)
            job->AddRef();
        void* jsec = (job == 0) ? 0 : (void*)((char*)job + 4);
        result = pArg2->Run(pArg0, jsec, 0, key.type);
        if (result == 0)
            job->m44 = 0;
        else if (job != 0)
            job->Complete();
        job->Release();
    }
    return result;
}

// @ 0x006b4ce0
bool JobBaseB::Complete()
{
    AsyncSave* self = (AsyncSave*)((char*)this - 4);
    if (self->m44 == 0)
        return false;
    if (--self->m44 != 0)
        return true;
    JobMgr* mgr = (JobMgr*)FUN_0068f4d0();
    mgr->Lock();
    cJob* job1 = 0;
    if (!mgr->BeginJob(&job1)) {
        if (job1)
            job1->Release();
        mgr->Unlock();
        return false;
    }
    uint32_t kind = self->m1c->GetKind();
    bool pair;
    if (kind == 0x2a43bd44 || kind == 0x6492c68)
        pair = true;
    else if (kind == 0x498d9c1)
        pair = (FUN_00695cf0(&self->m1c) != 0 || FUN_006b4390((void**)&self->m1c) != 0);
    else
        pair = false;
    if (pair) {
        cJob* job2 = 0;
        if (!mgr->BeginJob(&job2)) {
            if (job2)
                job2->Release();
            if (job1)
                job1->Release();
            mgr->Unlock();
            return false;
        }
        job2->mThreadAffinity = 0x80000000;
        job2->mpCallback = (void*)&FUN_006b4710;
        job2->mpCallbackData = self;
        job2->SetResult(self);
        job1->AddDependency(job2);
        job1->mThreadAffinity = 4;
        job1->mpCallback = (void*)&FUN_006b4720;
        job1->mpCallbackData = self;
        job1->SetResult(self);
        job1->GetStatus();
        if (job2)
            job2->Release();
    } else {
        job1->mThreadAffinity = 4;
        job1->mpCallback = (void*)&FUN_006b4b50;
        job1->mpCallbackData = self;
        job1->SetResult(self);
    }
    FUN_006b47a0(job1);
    job1->GetStatus();
    if (job1)
        job1->Release();
    mgr->Unlock();
    return true;
}

// @ 0x006b56d0
void __cdecl FUN_006b56d0(SP::ResourceKey* key, SP::cString* out)
{
    out->Load(key->instanceID, key->typeID, 0);
}

// @ 0x006b56f0
SP::cString::cString(const cString& other)
    : mpTableResource(other.mpTableResource.mpObject), mpLocalString(0),
      mpSourceCStr(other.mpSourceCStr), mPlaceholderId(0),
      mbHasTokens(false), mField11(false)
{
    if (FUN_0067de50() != 0)
        ((cStringManager*)FUN_0067de50())->AddString(this);
    *this = other;
}
