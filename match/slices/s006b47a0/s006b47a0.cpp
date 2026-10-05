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

struct cString;
struct cStringDetokenizer;
struct cStringManager;
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

struct cStringDetokenizer {
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

struct cStringManager {
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

struct cString {
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
// Async-save cluster (behavioural reconstruction; see nonmatching.txt).
// ---------------------------------------------------------------------------
struct cJob {
    char pad0[0x40];
    int  mRefCount;          // +0x40
    void FUN_006913c0(cJob* other);
    void FUN_0068f950();
    void FUN_006909b0();
    void GetStatus();
    void FUN_006926b0();
    static cJob* Get();
};

// @ 0x006b47a0
void __cdecl FUN_006b47a0(cJob* p)
{
    // complete structure requires the EA::Thread scoped mutex; stubbed body.
    (void)p;
}

// @ 0x006b4840
void __cdecl FUN_006b4840()
{
}

struct AsyncSave : cJob {
    void* FUN_006b48d0(cJob* p, int a, void* key);
    bool  FUN_006b4a10(int arg);
    bool  FUN_006b4ce0();
    void* Init(cJob* p, int a, void* key) { return FUN_006b48d0(p, a, key); }
};

// @ 0x006b48d0
void* AsyncSave::FUN_006b48d0(cJob* p, int a, void* key)
{
    (void)p; (void)a; (void)key;
    return this;
}

// @ 0x006b4a10
bool AsyncSave::FUN_006b4a10(int arg)
{
    (void)arg;
    return false;
}

// @ 0x006b4b60
char __cdecl FUN_006b4b60(int a, int b, int c, void* d)
{
    (void)a; (void)b; (void)c; (void)d;
    return 0;
}

// @ 0x006b4ce0
bool AsyncSave::FUN_006b4ce0()
{
    return false;
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
