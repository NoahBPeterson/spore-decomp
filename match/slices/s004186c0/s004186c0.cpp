// Editor resource object (size 0x2D4) and its construction / load setup.
//
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no EH frames needed).
#include "types.h"
extern "C" long _InterlockedExchangeAdd(long volatile*, long);
extern "C" long _InterlockedExchange(long volatile*, long);
extern "C" long _InterlockedIncrement(long volatile*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedIncrement)

struct Object {
    virtual int AddRef();
    virtual int Release();
};

// Thread-safe ref-counted object released out of line (Resource::ThreadedObject)
struct DefaultRefCounted {
    uint32_t pad0;
    int mRefCount;
    void Release();  // 0x00453540
    void AddRef() { int r = mRefCount + 1; mRefCount = mRefCount + 1; }
};
struct ItemA : DefaultRefCounted {  // 0x1D0 bytes
    ItemA();  // 0x00507380
    uint32_t pad[(0x1d0 - 8) / 4];
};
struct ItemB : DefaultRefCounted {  // 0xF8 bytes
    ItemB(float f);  // 0x004F85B0
    uint32_t pad[(0xf8 - 8) / 4];
};

template <class T>
struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr() {
        if (mpObject)
            mpObject->Release();
    }
    T* get() const { return mpObject; }
    intrusive_ptr& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

struct EditorOwner;
struct EditorSource;
struct ThreadedObject {  // 0xBC bytes
    uint32_t pad0;
    int mRefCount;  // +4, bumped with lock xadd
    uint32_t pad08[(0x34 - 8) / 4];
    intrusive_ptr<DefaultRefCounted> mpItemA;  // +0x34
    intrusive_ptr<DefaultRefCounted> mpItemB;  // +0x38
    uint32_t pad3C[(0xbc - 0x3c) / 4];
    ThreadedObject(EditorSource* pOwner);  // 0x004C6DF0
    void Method1();  // 0x004CA6E0
    void Method2();  // 0x004CB340
    void Method3();  // 0x004CB820
    void Release();  // 0x00404F90
};
template <>
struct intrusive_ptr<ThreadedObject> {
    ThreadedObject* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr() {
        if (mpObject)
            mpObject->Release();
    }
    ThreadedObject* get() const { return mpObject; }
    intrusive_ptr& operator=(ThreadedObject* pObject) {
        if (pObject != mpObject) {
            ThreadedObject* const pTemp = mpObject;
            if (pObject)
                _InterlockedIncrement((long*)&pObject->mRefCount);
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

struct PropertyListValue {
    uint32_t pad00[4];
    uint16_t pad10;
    uint16_t type;  // +0x12
    float* GetFloat();  // 0x0041EA70
};

struct PropertyList : Object {
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20();
    virtual bool GetProperty(uint32_t id, PropertyListValue** dst);  // +0x24
};
struct PropertyListPtr {
    PropertyList* mpObject;
    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr() {
        if (mpObject)
            mpObject->Release();
    }
    PropertyList* get() const { return mpObject; }
    PropertyList** OutImpl();  // 0x0041D870
    PropertyList** Out() { return OutImpl(); }
};

struct PropManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** dst);  // +0x2C
    static PropManager* GetImpl();  // 0x0067DE30
    static PropManager* Get() { return GetImpl(); }
};
extern uint32_t g_PropListGroup;  // 0x015D13E8


// Load handle (non-virtual refcount)
struct LoadHandle {
    uint32_t pad00[6];
    uint32_t mState;  // +0x18
    void Release();  // 0x00690120
    void SetState(uint32_t s) { mState = s; }
    void Attach(void* p);  // 0x00422990 (editor resource)
    void SetTarget(void* p);  // 0x0068F9B0
    void Finish();  // 0x006909B0
    void Add(LoadHandle* h);  // 0x00691380
    bool Process(void* res);  // 0x004229F0
    void OnBegin(void* p);  // 0x004229B0
    void OnEnd(void* p);  // 0x004229D0
};
struct LoadHandle2;  // placeholder
struct HandlePtr {
    LoadHandle* mpObject;
    HandlePtr() : mpObject(0) {}
    ~HandlePtr() {
        if (mpObject)
            mpObject->Release();
    }
    LoadHandle* get() const { return mpObject; }
    LoadHandle* operator->() const { return mpObject; }
    LoadHandle** OutImpl();  // 0x0041D940
    LoadHandle** AsPointer() {
        if (mpObject) {
            LoadHandle* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    LoadHandle** Out() { return OutImpl(); }
    LoadHandle* Detach() {
        LoadHandle* p = mpObject;
        mpObject = 0;
        return p;
    }
};
struct LoadManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual bool OpenHandle(LoadHandle** dst);  // +0x10
    virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void Lock();  // +0x20
    virtual void Unlock();  // +0x24
};
LoadManager* GetLoadManager();  // 0x0068F4D0

struct ConfigRoot {
    void Begin(ThreadedObject* pThreaded, float scale, LoadHandle** pOut);  // 0x00414470
};
ConfigRoot* GetConfigRoot();  // 0x00401010
extern const float kDefaultScale;  // 0x013EBA80
extern const float kDefaultItemScale;  // 0x013EB2B0
int LookupIndex(uint32_t key);  // 0x00432F10

// ---- members of the resource object ----
struct SubBase {
    ~SubBase();  // 0x0041EB80
    uint32_t pad[5];
};
struct MemberA { ~MemberA(); uint32_t pad[5]; };  // 0x004B5440 (0x14)
struct MemberB { ~MemberB(); uint32_t pad[5]; };  // 0x00432D60 (0x14)

struct Elem38 { uint32_t pad[14]; };
struct Elem10 { uint32_t pad[4]; };

struct Vec38 {
    Elem38* mpBegin;
    Elem38* mpEnd;
    uint32_t pad[3];
    void FreeData();  // 0x00427440
    ~Vec38() {
        Elem38* p = mpBegin;
        uint32_t dead[3];
        for (; p < mpEnd; ++p) {}
        FreeData();
    }
};
struct Vec10 {
    Elem10* mpBegin;
    Elem10* mpEnd;
    uint32_t pad[3];
    void FreeData();  // 0x00554B10
    ~Vec10() {
        Elem10* p = mpBegin;
        uint32_t dead[3];
        for (; p < mpEnd; ++p) {}
        FreeData();
    }
};

struct DeadTail {
    ~DeadTail() { uint32_t post[8]; }
};
struct SubObject : SubBase, DeadTail {  // size 0x8C
    Vec10 mVec14;
    Vec38 mVec28;
    Vec38 mVec3C;
    SubBase mBase50;
    MemberA mMember64;
    MemberB mMember78;
    SubObject();  // 0x00460F80
    ~SubObject();
};
struct TailObject {  // at +0xBC
    TailObject();  // 0x0041D360
    void Reserve(int n);  // 0x004E0880
    ~TailObject();  // 0x0041E640
    uint32_t pad[1];
};

struct IntrusiveAtomic {
    int mValue;
    IntrusiveAtomic() { _InterlockedExchange((long*)&mValue, 0); }
};

struct Gap28 {
    uint32_t a, b;
    Gap28() { uint32_t unused; }
};
struct DeadHead {
    ~DeadHead() { uint32_t pre[7]; }
};
struct EditorBaseP {
    virtual int AddRef();
    virtual int Release();
    virtual ~EditorBaseP() {}
};
struct EditorBaseQ : EditorBaseP {
    EditorBaseQ() {}
};
struct EditorBaseR {
    virtual void rf0();
    IntrusiveAtomic mCount;
    EditorBaseR() {}
    ~EditorBaseR() {}
};

struct Vec3Zero {
    uint32_t a, b, c;
    Vec3Zero() : a(0), b(0), c(0) {}
};
struct KeyPair {
    uint32_t id;
    uint16_t a, b;
    KeyPair() : id(0x2ea8fb98), a(0), b(4) {}
};

int ConvertValue(uint32_t v);  // 0x004BB860
struct Elem8C { uint32_t pad[35]; };
struct Vec8C {
    Elem8C* mpBegin;
    Elem8C* mpEnd;
    uint32_t pad[3];
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct EditorSource : Object {  // owner object / creation source
    uint32_t f04, f08, f0C, f10, f14;
    uint32_t f18;
    uint32_t pad1C[(0x98 - 0x1C) / 4];
    Vec8C mItems;  // +0x98
};

struct EditorResource : EditorBaseQ, EditorBaseR {
    intrusive_ptr<EditorSource> mpOwner;  // +0x0C
    Vec3Zero mVec;                        // +0x10
    KeyPair mKey;                         // +0x1C
    intrusive_ptr<ThreadedObject> mpThreaded;  // +0x24
    Gap28 mGap;                           // +0x28
    SubObject mSub;                       // +0x30
    TailObject mTail;                     // +0xBC
    uint32_t pad[(0x2d4 - 0xc0) / 4 - 1];
    DeadHead mDeadHead;

    EditorResource();  // 0x00418870
    bool Setup(LoadHandle* pParent);  // 0x00418AE0
    void NotifyA(LoadHandle* pParent);  // 0x00418F90
    bool NotifyB(LoadHandle* pParent);  // 0x00418FD0
    static void operator delete(void* p);  // 0x00F47380
};
void* operator new(size_t, const char*, int, int, int, int);  // 0x00F473A0

inline void DeadPad5() { uint32_t dead[6]; }
struct ResPtr {
    EditorResource* mpObject;
    ResPtr(EditorResource* p) : mpObject(p) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~ResPtr() {
        if (mpObject)
            mpObject->Release();
    }
    EditorResource* get() const { return mpObject; }
    EditorResource* operator->() const { return mpObject; }
    operator EditorResource*() const { return mpObject; }
};

// @ 0x004186C0
EditorResource* CreateEditorResource(EditorSource* pSource, uint32_t* pKey, LoadHandle** pOutHandle) {
    HandlePtr hLoad;
    if (!GetLoadManager()->OpenHandle(hLoad.Out()))
        return 0;
    DeadPad5();
    ResPtr pRes(new ("Editor", 0, 0, 0, 0) EditorResource);
    pRes->mpOwner = pSource;
    pRes->mVec = *(Vec3Zero*)&pSource->f08;
    pRes->mVec.b = ConvertValue(pSource->f18);
    pRes->mKey = *(KeyPair*)pKey;
    hLoad->SetState(1);
    hLoad->Attach(pRes.get());
    hLoad->SetTarget(pRes.get());
    *pOutHandle = hLoad.Detach();
    return pRes;
}

// @ 0x00418870
EditorResource::EditorResource() {}

// @ 0x00418960
// EditorResource scalar deleting destructor (compiler-generated from the virtual dtor).

// @ 0x00418990


// @ 0x00418990
// EditorResource::~EditorResource is implicit (members: Tail, Sub, mpThreaded, mpOwner released in reverse order).

// @ 0x00418A10
SubObject::~SubObject() { uint32_t pre[6]; }

// @ 0x00418AE0
bool EditorResource::Setup(LoadHandle* pParent) {
    mpThreaded = new ("Editor", 0, 0, 0, 0) ThreadedObject(mpOwner.get());
    mpThreaded.get()->mpItemA = new ("Editor", 0, 0, 0, 0) ItemA;
    mpThreaded.get()->mpItemB = new ("Editor", 0, 0, 0, 0) ItemB(kDefaultItemScale);
    mTail.Reserve(mpOwner.get()->mItems.size());
    float scale = kDefaultScale;
    int idx = LookupIndex(mpOwner.get()->f18);
    if (idx != -1) {
        const uint32_t kPropId = 0x711306ce;
        PropertyListPtr pList;
        if (PropManager::Get()->GetPropertyList(idx, g_PropListGroup, pList.Out())) {
            PropertyList* pl = pList.get();
            PropertyListValue* pProp;
            if (pl && pl->GetProperty(0x711306ce, &pProp) && pProp->type == 0xd)
                scale = *pProp->GetFloat();
        }
    }
    ConfigRoot* pCfg = GetConfigRoot();
    LoadManager* pMgr = GetLoadManager();
    pMgr->Lock();
    HandlePtr h1;
    pCfg->Begin(mpThreaded.get(), scale, h1.Out());
    HandlePtr h2;
    GetLoadManager()->OpenHandle(h2.Out());
    h2->SetState(0x80000000);
    h2->OnBegin(this);
    h2->Add(h1.get());
    HandlePtr h3;
    GetLoadManager()->OpenHandle(h3.AsPointer());
    h3->SetState(1);
    h3->OnEnd(this);
    pParent->Add(h2.mpObject);
    pParent->Add(h3.mpObject);
    h1->Finish();
    h2->Finish();
    h3->Finish();
    pMgr->Unlock();
    return pParent->Process(this);
}

// @ 0x00418F90
void EditorResource::NotifyA(LoadHandle* pParent) {
    mpThreaded.get()->Method1();
    mpThreaded.get()->Method2();
    pParent->Process(this);
}

// @ 0x00418FD0
bool EditorResource::NotifyB(LoadHandle* pParent) {
    mpThreaded.get()->Method3();
    return true;
}
