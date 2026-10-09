// Editor/Graphics resource helpers around 0x0042F9D0: a wide string append,
// multiple-inheritance adjustor thunks, and the BakeSprites-style resource builder.
// Built without optimization: /Od /Ob1 /arch:SSE (frame pointer, locals in memory).
#include "types.h"

extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
#pragma intrinsic(_InterlockedExchange)

// ---------------------------------------------------------------- externals
void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int align,
                                       const char* file, int line);
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
void* __cdecl memcpy(void* dst, const void* src, unsigned int n);

// ---------------------------------------------------------------- wide string buffer
struct WideFixedBuf {
    wchar_t* mBegin;
    wchar_t* mEnd;
    wchar_t* mCapacity;
    void ReleaseHeap();                                   // @ 0x004292A0
    WideFixedBuf& append(const wchar_t* pBegin, const wchar_t* pEnd);
};

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }

inline uint32_t MaxU(const uint32_t& a, const uint32_t& b) { return (a < b) ? b : a; }
inline const uint32_t& MaxRef(const uint32_t& a, const uint32_t& b) { return (a < b) ? b : a; }

// Copies [first,last) to dest and returns the end of the copied range.
inline wchar_t* CopyWide(const wchar_t* first, const wchar_t* last, wchar_t* dest)
{
    memcpy(dest, first, (last - first) * 2);
    return dest + (last - first);
}

inline wchar_t* DoAllocate(uint32_t n)
{
    void* p = EASTL_allocator_allocate(
        n * 2, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    return (wchar_t*)p;
}

// @ 0x0042F9D0
WideFixedBuf& WideFixedBuf::append(const wchar_t* pBegin, const wchar_t* pEnd)
{
    if (pBegin != pEnd) {
        const uint32_t nOldSize = mEnd - mBegin;
        const uint32_t n = pEnd - pBegin;
        const uint32_t nCapacity = (mCapacity - mBegin) - 1;
        if (nOldSize + n > nCapacity) {
            const uint32_t nLength = MaxRef(nCapacity > 8 ? nCapacity * 2 : 8, nOldSize + n) + 1;
            wchar_t* pNewBegin = DoAllocate(nLength);
            wchar_t* pNewEnd = pNewBegin;
            pNewEnd = CopyWide(mBegin, mEnd, pNewBegin);
            ScratchSlots<3>();
            pNewEnd = CopyWide(pBegin, pEnd, pNewEnd);
            *pNewEnd = 0;
            ReleaseHeap();
            mBegin = pNewBegin;
            mEnd = pNewEnd;
            mCapacity = pNewBegin + nLength;
        } else {
            const wchar_t* pTempBegin = pBegin;
            ++pTempBegin;
            CopyWide(pTempBegin, pEnd, mEnd + 1);
            mEnd[n] = 0;
            *mEnd = *pBegin;
            mEnd = mEnd + n;
        }
    }
    return *this;
}

// ---------------------------------------------------------------- adjustor thunks
// Each thunk is the this-adjusting stub in the vtable of a secondary base (sub ecx,N ; jmp D::f).
// @ 0x0042FBB0  (adjustor thunk: sub ecx,4 ; jmp ThunkD_4036a0::f)
struct ThunkB0_4036a0 { virtual void f(); };
struct ThunkB1_4036a0 { virtual void f(); };
struct ThunkD_4036a0 : ThunkB0_4036a0, ThunkB1_4036a0 { void f(); ThunkD_4036a0(); };
ThunkD_4036a0::ThunkD_4036a0() {}

// @ 0x0042FBC0  (adjustor thunk: sub ecx,4 ; jmp ThunkD_410d40::f)
struct ThunkB0_410d40 { virtual void f(); };
struct ThunkB1_410d40 { virtual void f(); };
struct ThunkD_410d40 : ThunkB0_410d40, ThunkB1_410d40 { void f(); ThunkD_410d40(); };
ThunkD_410d40::ThunkD_410d40() {}

// @ 0x0042FBD0  (adjustor thunk: sub ecx,4 ; jmp ThunkD_41a9f0::f)
struct ThunkB0_41a9f0 { virtual void f(); };
struct ThunkB1_41a9f0 { virtual void f(); };
struct ThunkD_41a9f0 : ThunkB0_41a9f0, ThunkB1_41a9f0 { void f(); ThunkD_41a9f0(); };
ThunkD_41a9f0::ThunkD_41a9f0() {}

// Class with three polymorphic bases and a custom operator delete (allocator based).
// @ 0x0042FBE0  (deleting-destructor thunk, this -= 4 -> DelObj scalar deleting dtor)
// @ 0x0042FBF0  (DelObj scalar deleting destructor)
// @ 0x0042FC30  (deleting-destructor thunk, this -= 8 -> DelObj scalar deleting dtor)
struct DelB0 { virtual ~DelB0(); };
struct DelB1 { virtual ~DelB1(); };
struct DelB2 { virtual ~DelB2(); };
struct DelObj : DelB0, DelB1, DelB2 {
    virtual ~DelObj();                                    // @ 0x004037B0
    void operator delete(void* p) { EASTL_allocator_deallocate(p); }
    DelObj();
};
DelObj::DelObj() {}

// @ 0x0042FC20  (deleting-destructor thunk, this -= 4 -> EditorResource scalar deleting dtor)
struct EdB0 { virtual ~EdB0(); };
struct EdB1 { virtual ~EdB1(); };
struct EditorResourceD : EdB0, EdB1 { virtual ~EditorResourceD(); EditorResourceD(); };
EditorResourceD::EditorResourceD() {}

// ---------------------------------------------------------------- engine interfaces (vtable stubs)
struct Property {
    char pad[0x12];
    uint16_t type;                                        // +0x12, 9 = int, 0xd = float
    int*   GetInt();                                      // @ 0x0041E990
    float* GetFloat();                                    // @ 0x0041EA70
};

struct IPropHost {
    virtual void _v0();
    virtual void Release();                               // +0x04
    virtual void _v2(); virtual void _v3(); virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7(); virtual void _v8();
    virtual bool GetProp(uint32_t key, Property** out);   // +0x24
};

struct IResourceMgr {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7(); virtual void _v8(); virtual void _v9(); virtual void _v10();
    virtual bool Find(uint32_t a, uint32_t b, IPropHost** out);   // +0x2c
};

struct ISettings {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7(); virtual void _v8(); virtual void _v9(); virtual void _v10(); virtual void _v11(); virtual void _v12(); virtual void _v13(); virtual void _v14(); virtual void _v15(); virtual void _v16(); virtual void _v17(); virtual void _v18(); virtual void _v19(); virtual void _v20(); virtual void _v21(); virtual void _v22(); virtual void _v23(); virtual void _v24(); virtual void _v25(); virtual void _v26(); virtual void _v27(); virtual void _v28(); virtual void _v29(); virtual void _v30(); virtual void _v31(); virtual void _v32(); virtual void _v33(); virtual void _v34(); virtual void _v35(); virtual void _v36(); virtual void _v37(); virtual void _v38(); virtual void _v39(); virtual void _v40(); virtual void _v41(); virtual void _v42();
    virtual void Get_ac(void* out);                       // +0xac
    virtual void _v44();
    virtual void Get_b4(void* out);                       // +0xb4
    virtual void Get_b8(void* out);                       // +0xb8
    virtual void _v47(); virtual void _v48(); virtual void _v49(); virtual void _v50(); virtual void _v51(); virtual void _v52(); virtual void _v53(); virtual void _v54(); virtual void _v55(); virtual void _v56(); virtual void _v57(); virtual void _v58(); virtual void _v59();
    virtual void Set_f0(uint16_t v);                      // +0xf0
};

struct IBuilder {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7(); virtual void _v8(); virtual void _v9(); virtual void _v10(); virtual void _v11(); virtual void _v12(); virtual void _v13();
    virtual void Build(uint32_t flags, void* a, void* b, void* c, void* d, void* e, void* tbl,
                       uint32_t f, int mode, void* g, void* h, void* i);   // +0x38
};

struct IScene {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual bool Query(void* p);                          // +0x10
    virtual void _v5(); virtual void _v6(); virtual void _v7();
    virtual void Begin();                                 // +0x20
    virtual void End();                                   // +0x24
};

// Begin/End bracket around the scene work; End runs when the guard goes out of scope.
struct SceneGuard {
    IScene* p;
    void Begin() { p->Begin(); }
    ~SceneGuard() { p->End(); }
};

extern IPropHost* g_pApp;                                 // 0x015FD918
extern int g_Table2458018;                                // 0x02458018
void  __cdecl Unk777ae0(int a, int b, int c);             // @ 0x00777AE0
void* __cdecl GetUnk67dd60();                             // @ 0x0067DD60
ISettings*    __cdecl GetSettings();                      // @ 0x0067DD40
IBuilder*     __cdecl GetBuilder();                       // @ 0x0067DDB0
IResourceMgr* __cdecl GetResourceMgr();                   // @ 0x0067DE30
IScene*       __cdecl GetScene();                         // @ 0x0068F4D0

inline void TryGetFloat(IPropHost* host, uint32_t key, float& out)
{
    Property* prop;
    if (host && host->GetProp(key, &prop) && prop->type == 0xd)
        out = *prop->GetFloat();
}

// Owning reference to a property host. Taking its address releases the current object first.
struct PropHostRef {
    IPropHost* p;
    PropHostRef() { p = 0; }
    ~PropHostRef() { if (p) p->Release(); }
    operator IPropHost*() { return p; }
    IPropHost** operator&()
    {
        if (p) {
            IPropHost* old = p;
            p = 0;
            old->Release();
        }
        return &p;
    }
};

// Reads an int property (type 9) from a property host.
inline bool TryGetInt(IPropHost* h, uint32_t key, int& out)
{
    Property* pEntry;
    int temp;
    if (h && h->GetProp(key, &pEntry) && pEntry->type == 9) {
        out = *pEntry->GetInt();
        return true;
    }
    return false;
}

inline bool TryGetUInt(IPropHost* propHost, uint32_t key, uint32_t& outValue)
{
    Property* pValue;
    int typeId;
    if (propHost && propHost->GetProp(key, &pValue) && pValue->type == 9) {
        outValue = *(uint32_t*)pValue->GetInt();
        return true;
    }
    return false;
}

// @ 0x0042FC40
bool __cdecl BakeSpritesLoadAndBuild(void* p1, uint32_t resA, uint32_t resB, uint32_t p4,
                                     void* p5, void* p6, void* p7, void* p8)
{
    IPropHost* application = g_pApp;
    Unk777ae0(0x219, 0, 0);
    void* display = GetUnk67dd60();
    ISettings* settingsMgr = GetSettings();
    uint32_t resourceKey[2] = { 0xffffffff, 0xffffffff };
    uint32_t secondKey[2] = { 0xffffffff, 0xffffffff };
    uint32_t keyZ[2] = { 0xffffffff, 0xffffffff };
    IBuilder* creator = GetBuilder();
    int spriteMode = 0;
    uint32_t bakeFlags = 0x100;
    PropHostRef host;
    bool isSet;
    if (GetResourceMgr()->Find(resA, resB, &host)) {
        isSet = TryGetInt(host, 0x4c6ba3c, spriteMode);
        isSet = TryGetUInt(host, 0x4c6ba29, bakeFlags);
    }
    GetSettings()->Set_f0((uint16_t)bakeFlags);
    settingsMgr->Get_ac(resourceKey);
    if (spriteMode == 0) {
        creator->Build(bakeFlags, resourceKey, p1, p5, p6, p7, &g_Table2458018, p4, spriteMode, secondKey, keyZ, p8);
    } else if (spriteMode == 1) {
        settingsMgr->Get_b8(secondKey);
        creator->Build(bakeFlags, resourceKey, p1, p5, p6, p7, &g_Table2458018, p4, spriteMode, secondKey, keyZ, p8);
    } else if (spriteMode == 2) {
        settingsMgr->Get_b8(secondKey);
        settingsMgr->Get_b4(keyZ);
        creator->Build(bakeFlags, resourceKey, p1, p5, p6, p7, &g_Table2458018, p4, spriteMode, secondKey, keyZ, p8);
    }
    return true;
}

// ---------------------------------------------------------------- BakeSprites resource object
struct cEditorResource { cEditorResource() {} virtual void _e0(); };
struct BakeSprites : cEditorResource { BakeSprites() {} virtual void _b0(); };
struct AtomicInt {
    long mValue;
    AtomicInt() { Set(0); }
    void Set(long x) { _InterlockedExchange(&mValue, x); }
};
struct cCreatureAbility {
    AtomicInt mRefCount;
    cCreatureAbility() {}
    virtual void _c0();
};

struct RefVector {
    void* mBegin; void* mEnd; void* mCap;
    RefVector() { mBegin = 0; mEnd = 0; mCap = 0; }
    ~RefVector();                                         // @ 0x0041EB80
    RefVector& operator=(const RefVector& o);             // @ 0x0041EBE0
};
struct AllocTag { AllocTag() {} };
struct Vector8Base {
    uint32_t mData[5];
    Vector8Base(const AllocTag&);                         // @ 0x00540470
    ~Vector8Base();                                       // @ 0x00564580
    Vector8Base& operator=(const Vector8Base& o);         // @ 0x004269B0
};
struct Vector8 : Vector8Base {
    bool mFlag;                                           // +0x14
    Vector8() : Vector8Base(AllocTag()) {}
    Vector8& operator=(const Vector8& o)
    {
        Vector8Base::operator=(o);
        bool f = o.mFlag;
        mFlag = f;
        return *this;
    }
};
struct Elem24Vec {
    void* mBegin; void* mEnd; void* mCap;
    Elem24Vec() { mBegin = 0; mEnd = 0; mCap = 0; }
    ~Elem24Vec();                                         // @ 0x00421230
    Elem24Vec& operator=(const Elem24Vec& o);             // @ 0x00421290
};
struct Transform56 { uint32_t data[14]; };
struct TransformVec {
    Transform56* mBegin; Transform56* mEnd; Transform56* mCap;
    TransformVec() { mBegin = 0; mEnd = 0; mCap = 0; }
    Transform56* begin() { return mBegin; }
    ~TransformVec() { for (Transform56* p = mBegin; p < mEnd; ++p) {} FreeStorage(); }
    void FreeStorage();                                   // @ 0x00427440
    TransformVec& operator=(const TransformVec& o);       // @ 0x0041E0D0
};

struct IMgr {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4();
    virtual void Notify(uint32_t id, int a, int b);       // +0x14
    virtual void Notify4(uint32_t id, int a, int b, int c);   // +0x18
};
IMgr* __cdecl GetMgr();                                   // @ 0x0067DCC0

// Scalar deleting destructor of this class is the compiler-generated function at 0x004302F0.
struct BakeSpritesResource : BakeSprites, cCreatureAbility {
    RefVector    mVecA;       // +0x0c
    uint32_t     mField18;    // +0x18
    uint32_t     mField1c;    // +0x1c
    uint32_t     mField20;    // +0x20
    uint32_t     mField24;    // +0x24
    uint32_t     mField28;    // +0x28
    RefVector    mVecB;       // +0x2c
    uint32_t     mField38;    // +0x38
    uint32_t     mField3c;    // +0x3c
    Vector8      mVec8;       // +0x40
    Elem24Vec    mElems;      // +0x58
    uint32_t     mField64;    // +0x64
    uint32_t     mField68;    // +0x68
    TransformVec mTransforms; // +0x6c
    uint32_t     mField78;    // +0x78
    uint32_t     mField7c;    // +0x7c
    bool         mFlag80;     // +0x80

    BakeSpritesResource();                                // @ 0x004301E0
    void Run(int unused);                                 // @ 0x0042FF30
    void* operator new(unsigned size)
    {
        ScratchSlots<3>();
        return EASTL_allocator_allocate(size, "Graphics", 0, 0, 0, 0);
    }
    virtual ~BakeSpritesResource()                        // @ 0x00430320
    {
        if (!mFlag80) {
            GetMgr()->Notify4(0x355dad8, 0, 0, 0);
        }
        // Frame filler: the original reserves unused slots here (they also size the
        // compiler-generated scalar deleting destructor at 0x004302F0).
        ScratchSlots<13>();
    }
    void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};

// @ 0x004301E0
BakeSpritesResource::BakeSpritesResource()
{
    int unusedSlot;
    mFlag80 = false;
}


// @ 0x0042FF30
void BakeSpritesResource::Run(int)
{
    GetMgr()->Notify(0x355dad8, 0, 0);
    mFlag80 = true;
    BakeSpritesLoadAndBuild(&mVecA, mField24, mField28, mField20, &mVecB, &mVec8, &mElems, &mTransforms);
}

// ---------------------------------------------------------------- scene objects
struct SceneObj {
    uint32_t pad[6];
    uint32_t mState;                                      // +0x18
    void Fn68f9b0(BakeSpritesResource* r);                // @ 0x0068F9B0
    void Fn432dc0(BakeSpritesResource* r);                // @ 0x00432DC0
    void Fn691380(SceneObj* o);                           // @ 0x00691380
    void Fn6909b0();                                      // @ 0x006909B0
    void Fn690120();                                      // @ 0x00690120
};
struct ObjRef {
    SceneObj* p;
    void* GetRaw();                                       // @ 0x0041D940
    void* Get() { return GetRaw(); }
    SceneObj* get() { SceneObj* t = p; return t; }
    SceneObj* operator->() { SceneObj* t = p; return t; }
    ~ObjRef() { if (p) p->Fn690120(); }
};

void __cdecl Unk729300(void* vec, float f, void* a, uint32_t b, uint32_t c, int d, void* e);

inline IScene* GetSceneRef() { IScene* s = GetScene(); return s; }

// @ 0x0042FFB0
bool __cdecl BakeSpritesCreate(RefVector* vecA, uint32_t f24, uint32_t f28, uint32_t f20,
                               RefVector* vecB, Vector8* v8, Elem24Vec* elems, TransformVec* xf)
{
    BakeSpritesResource* newRes = new BakeSpritesResource;
    newRes->mVecA = *vecA;
    newRes->mField24 = f24;
    newRes->mField28 = f28;
    newRes->mField20 = f20;
    newRes->mVecB = *vecB;
    newRes->mVec8 = *v8;
    newRes->mElems = *elems;
    newRes->mTransforms = *xf;

    SceneGuard sceneGuard;
    sceneGuard.p = GetSceneRef();
    sceneGuard.Begin();
    IScene* sceneRef = GetScene();
    ObjRef primary;
    primary.p = 0;
    float mult = 1.0f;
    TryGetFloat(g_pApp, 0x444d5b0, mult);
    Unk729300(&newRes->mVecA, mult, primary.Get(), f24, f28, 0, xf->begin());
    ObjRef secondary;
    secondary.p = 0;
    if (sceneRef->Query(secondary.Get())) {
        secondary.p->Fn68f9b0(newRes);
        secondary.p->Fn432dc0(newRes);
        if (primary.p)
            secondary.p->Fn691380(primary.get());
        secondary->mState = 1;
    }
    if (primary.p)
        primary.p->Fn6909b0();
    secondary.p->Fn6909b0();
    return true;
}

// @ 0x0042FF00
void __cdecl BakeSpritesCreateThunk(RefVector* vecA, uint32_t f24, uint32_t f28, uint32_t f20,
                                    RefVector* vecB, Vector8* v8, Elem24Vec* elems, TransformVec* xf)
{
    BakeSpritesCreate(vecA, f24, f28, f20, vecB, v8, elems, xf);
}
