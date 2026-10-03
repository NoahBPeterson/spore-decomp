// Editor palette: mark a resource (and its "base" variant) as used, then register / refresh
// the editor listener for a ResourceKey.
// Built /Od /Ob1 /MD /Gy /TP (no /EHsc): frame pointer, every local in memory.
#include "types.h"

typedef unsigned short uint16_t;

// ---------------------------------------------------------------------------
// Reference counting
// ---------------------------------------------------------------------------
struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
};

template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    T* get() const { return mpObject; }
    T* Ptr() const { T* p = mpObject; return p; }
    void Reset() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    intrusive_ptr& operator=(T* pObject) {
        T* const pTemp = mpObject;
        if (pObject) pObject->AddRef();
        mpObject = pObject;
        if (pTemp) pTemp->Release();
        return *this;
    }
    T** GetAddress();   // 0x0041d870 (releases, returns out-param slot)
    T** AsOutParam() { return GetAddress(); }
};

// ---------------------------------------------------------------------------
// Resource keys
// ---------------------------------------------------------------------------
struct ResourceKey {
    uint32_t instance, type, group;
    uint32_t GetGroup() const { return group; }
};

struct GroupBits { uint32_t lo : 16; uint32_t tag : 8; uint32_t flags : 5; uint32_t hi : 3; };
inline uint32_t KeyGroupTag(uint32_t v) { uint32_t r = v; return (r >> 16) & 0xff; }
inline uint32_t KeyFlags(uint32_t v) { uint32_t r = v; return (r >> 24) & 0x1f; }
inline uint32_t KeyWithFlags(uint32_t v, uint32_t n) { ((GroupBits*)&v)->flags = n; return v; }

// 16-byte tagged value (flags bit 2 = owns heap storage)
struct Variant {
    uint32_t data[4];
    uint16_t flags;
    uint16_t type;
    Variant(const bool& b) : flags(0), type(0) {
        type = 1;
        flags = 2;
        Store((bool*)&b);
    }
    void Store(bool* p);        // 0x00422e20
    void Free(int a);           // 0x0093db80
    ~Variant() { if (flags & 4) Free(0); }
};

struct IResource : IRefCounted {
    virtual void v2(); virtual void v3(); virtual void v4();
    virtual void SetProperty(uint32_t id, const Variant& v);      // +0x14
};
void MarkUsed(IResource* r, int flag);                       // 0x006b2090

struct IResourceManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool Load(uint32_t instance, uint32_t group, IResource** out);   // +0x2c
};
IResourceManager* GetResourceManager();                      // 0x0067de30

template <> IResource** intrusive_ptr<IResource>::GetAddress();

// ---------------------------------------------------------------------------
// Strings (EASTL basic_string<wchar_t>: begin / end / capacity)
// ---------------------------------------------------------------------------
extern wchar_t gEmptyWString[];                              // 0x01667bac
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    WString() : mpBegin(0), mpEnd(0), mpCapacity(0)
    {
        mpBegin = gEmptyWString;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    int rfind(const wchar_t* s, int pos, int n) const;       // 0x00423700
    int rfind(wchar_t c, int pos) const;                     // 0x0041dfc0
    void erase(int pos, int n);                              // 0x004228e0
    ~WString();                                              // 0x004237d0
};

// ---------------------------------------------------------------------------
// Manager objects
// ---------------------------------------------------------------------------
struct IWindow {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual bool Contains(ResourceKey* key, int a, int b, int c, int d, int e);   // +0x34
};
void SyncState();                                            // 0x006b4840
void* LookupName(uint32_t nameAddr);                         // 0x006b1f90
IWindow* FindWindow(void* name);                             // 0x00422950

struct HitEntry { uint32_t a, b, c; };
template <class T> struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    void Free();                                             // 0x005156b0
};

struct QueryBase {
    uint32_t instance, group, a, b;
    __forceinline QueryBase() : instance(-1), group(-1), a(-1), b(-1) {}
    __forceinline virtual ~QueryBase() {}
};

struct Query : QueryBase {
    vector<HitEntry> list;
    __forceinline Query() { list.mpBegin = 0; list.mpEnd = 0; list.mpCapacity = 0; }
    __forceinline virtual ~Query() {
        for (HitEntry* p = list.mpBegin; p < list.mpEnd; ++p) {}
        list.Free();
    }
};

struct IEditorServices {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool Lookup(ResourceKey* key, IRefCounted** out, int, int, int, int);                 // +0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void Register(IRefCounted* listener, int, IWindow* win, int, ResourceKey* key);       // +0x20
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void Collect(vector<HitEntry>* out, Query* q, int a);             // +0x38
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30();
    virtual void GetPath(ResourceKey* key, WString* out);                                         // +0x7c
    virtual void SetExt(ResourceKey* key, const wchar_t* ext);                                    // +0x80
};
IEditorServices* GetServices();                              // 0x0067dcd0
void BuildKey(ResourceKey* key, WString* ext, const wchar_t* path);   // 0x0068d0d0
struct Panel {
    void Apply(ResourceKey* key, bool flag, void* extra);
};
void Process(vector<HitEntry>* list, void* extra, const wchar_t* name, IWindow* a, IWindow* b, bool flag);   // 0x00417210


// @ 0x00417600
void Panel::Apply(ResourceKey* key, bool flag, void* extra)
{
    const wchar_t* name = 0;
    switch (KeyGroupTag(key->GetGroup())) {
    case 0x61: name = L"Cell"; break;
    case 0x62: name = L"Creature"; break;
    case 0x63: name = L"Building"; break;
    case 0x64: name = L"Vehicle"; break;
    case 0x65: name = L"UFO"; break;
    case 0x66: name = L"Flora"; break;
    case 0x6b: name = L"Palette"; break;
    }
    if (!name) return;

    intrusive_ptr<IResource> res;
    if (GetResourceManager()->Load(key->instance, key->group, res.AsOutParam())) {
        res->SetProperty(0x66fadbd, Variant(true));
        MarkUsed(res.get(), 1);
        if (KeyGroupTag(key->GetGroup()) == 0x62 && KeyFlags(key->GetGroup()) == 0) {
            IResourceManager* mgr = GetResourceManager();
            res.Reset();
            if (mgr->Load(key->instance, KeyWithFlags(key->group, 1), (IResource**)&res)) {
                res->SetProperty(0x66fadbd, Variant(true));
                MarkUsed(res.get(), 1);
            }
        }
        if (res.get()) res = 0;
    }

    SyncState();
    IWindow* winA = FindWindow(LookupName(0x11ac1ac));
    IWindow* winB = FindWindow(LookupName(0x11ac19c));
    ResourceKey key2 = *key;
    key2.type = 0x1a99b06b;
    IEditorServices* services = GetServices();
    intrusive_ptr<IRefCounted> listener;
    listener.Reset();
    if (services->Lookup(key, &listener.mpObject, 0, 0, 0, 0)) {
        WString path;
        int idx;
        WString ext;
        services->GetPath(key, &path);
        const wchar_t* e1 = L"_@";
        while (*e1) ++e1;
        idx = path.rfind(L"_@", -1, (int)(e1 - L"_@"));
        if (idx == -1) {
            const wchar_t* e2 = L"_0x";
            while (*e2) ++e2;
            idx = path.rfind(L"_0x", -1, (int)(e2 - L"_0x"));
        }
        if (idx == -1) idx = path.rfind(L'.', -1);
        path.erase(idx, -1);
        BuildKey(&key2, &ext, path.mpBegin);
        services->SetExt(&key2, ext.mpBegin);
        services->Register(listener.Ptr(), 0, winB, 0, &key2);
    }
    if ((winA && winA->Contains(&key2, 0, 1, 6, 1, 0)) || (winB && winB->Contains(&key2, 0, 1, 6, 1, 0))) {
        Query q;
        q.instance = key->instance;
        q.group = key->group;
        q.b = 0xc0ff0000;
        services->Collect(&q.list, &q, 0);
        Process(&q.list, extra, name, winA, winB, flag);
    }
}

// ---------------------------------------------------------------------------
// Editor block data (0x1248 bytes, allocated from the "Editor" EASTL pool)
// ---------------------------------------------------------------------------
struct EditorBlockData {
    EditorBlockData() throw();      // 0x00403240
    char* GetSlotArea();
    uint32_t pad[0x1100 / 4];
    char slotArea[0x148];
};

// @ 0x00417cf0
char* EditorBlockData::GetSlotArea()
{
    return (char*)this + 0x1100;
}

void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int a, int b, int c, int d) throw();   // 0x00f473a0

inline void* operator new(size_t sz, const char* name, int a, int b, int c, int d) throw()
{
    return EASTL_allocator_allocate(sz, name, a, b, c, d);
}
inline void operator delete(void*, const char*, int, int, int, int) throw() {}

// @ 0x00417d10
EditorBlockData* CreateEditorBlockData()
{
    return new("Editor", 0, 0, 0, 0) EditorBlockData();
}
