// Spore decompilation - batch bfs4, slice s008e1d50 (0x008E1D50..0x008E2E0F).
// EA::ResourceMan::Manager and EA::XHTML DOM/Resource helpers (EA framework, UTFSpore).
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>
#include <intrin.h>
#include "types.h"

typedef unsigned short wchar16;
struct IObj;

// ---------------------------------------------------------------------------
// external helpers (declared only; relocation-masked)
// ---------------------------------------------------------------------------
void __cdecl FUN_008e1690(void* a, void* b, void* c = 0);
void __cdecl FUN_008e12c0(void* a, void* b);
void __cdecl FUN_008e55d0(void* a, void* b, int c);
void __cdecl FUN_008e4380(void* self, void* v);
void* __cdecl FUN_008e4480(void* self, const wchar_t* name, int flag);
struct XElem { const wchar_t* GetAttrValue(int id); };   // 0x008e45b0 EA::XHTML::DOM::Element::GetAttrValue (thiscall)
void __cdecl FUN_008e4940(void* self, void* a, void* b);
void __cdecl FUN_008e52b0(void* self, void* a, int b);
void __cdecl FUN_008e52e0(void* self);
void __cdecl FUN_008e5370(void* self, void* a, int b, void* c);
void __cdecl FUN_008f3790(void* out, const void* first, const void* last, const void* key);   // eastl::equal_range over a static definition table
char __cdecl FUN_008e42c0(void);
void __cdecl FUN_008e42e0(void*);
void __cdecl operator_delete(void* p);
void __cdecl operator_delete__(void* p);
void __cdecl FUN_00928ba0(void* alloc, unsigned n);
void __cdecl FUN_00928dc0(void* alloc);
void __cdecl FUN_00620230(void* p);
void __cdecl FUN_011e0744(void* d, const void* s, unsigned n);
void __cdecl FUN_008e1200(void* a, void* b);
void __cdecl FUN_008de4f0(void* a);
void __cdecl FUN_00889380(void* a, void* b);
void __cdecl FUN_00925f30(void* a, unsigned b, unsigned c);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);

struct IKV { int m0; int m4; char m8; char pad9[7]; int m10; };

// ---------------------------------------------------------------------------
// refcounted object with a secondary virtual interface at +0x0c
// ---------------------------------------------------------------------------
struct Obj6 {
    virtual void v0(int);
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9(void* ctx, int flag);
    virtual void v10();
    virtual void v11();
};

struct Ref {
    char pad0[0xc];
    Obj6* mp0c;             // +0x0c
    char pad10[0x1c - 0x10];
    uint8_t mb1c;           // +0x1c
    uint8_t mb1d;           // +0x1d
    char pad1e[2];
    int mnRef;              // +0x20
    bool Test();
    bool Release();
};

// @ 0x008e22e0
bool Ref::Test()
{
    if (_InterlockedExchangeAdd((volatile long*)&mnRef, 0) != 0) {
        _InterlockedExchangeAdd((volatile long*)&mnRef, 1);
        return true;
    }
    return false;
}

// @ 0x008e2300
bool Ref::Release()
{
    if (_InterlockedExchangeAdd((volatile long*)&mnRef, 0) == 0)
        return false;
    if (_InterlockedDecrement((volatile long*)&mnRef) == 0) {
        if (mb1c != 0 && mp0c != 0) {
            mp0c->v6();
            if (mb1d != 0) {
                Obj6* p = mp0c;
                if (p != 0)
                    p->v0(1);
            }
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// a small refcounted value class (ctor / non-deleting & deleting dtors)
// ---------------------------------------------------------------------------
struct BaseV {
    virtual void bv0();
    int mRef4;      // +0x04
    int m8;         // +0x08
    int m12;        // +0x0c
    BaseV(int a, int b) { _InterlockedExchange((volatile long*)&mRef4, 0); m8 = a; m12 = b; }
    void ForceRelease();
};

struct DerV : BaseV {
    virtual void bv0();
    int v10, v14, v18;      // +0x10,14,18
    uint8_t b1c, b1d;       // +0x1c,0x1d
    char pad1e[2];
    int mRef20;             // +0x20
    DerV(int a, int b, const int* c, uint8_t d, uint8_t e);
    ~DerV();
};

// @ 0x008e2380
DerV::DerV(int a, int b, const int* c, uint8_t d, uint8_t e) : BaseV(a, b)
{
    v10 = c[0];
    v14 = c[1];
    v18 = c[2];
    b1c = d;
    b1d = e;
    _InterlockedExchange((volatile long*)&mRef20, 1);
}

// @ 0x008e2350
DerV::~DerV()
{
    if (_InterlockedExchangeAdd((volatile long*)&mRef20, 0) != 0) {
        _InterlockedExchange((volatile long*)&mRef20, 1);
        ForceRelease();
    }
}

// ---------------------------------------------------------------------------
// XHTML DOM Document-like object
// ---------------------------------------------------------------------------
struct DocX {
    char pad0[0x2c];
    uint8_t mFlag;          // +0x2c
    char pad1[0xb];
    void* mpOther;          // +0x38
    char pad2[4];
    int   mVal40;           // +0x40
    void SetChild(int v);
    void CallA();
    void CallB();
    void* FindBody();
    void SetAt(unsigned idx, IObj* o);
    void RemoveAllChildren();
    bool CheckFlag(bool flag);
    int LookupStyle();
    void RemoveAttr(IKV* kv);
};

// @ 0x008e2800
void DocX::SetChild(int v)
{
    mFlag = 1;
    mVal40 = v;
}

// @ 0x008e2870
void DocX::CallA()
{
    if (mpOther != 0 && mVal40 != 0)
        ((Obj6*)mVal40)->v10();
}

// @ 0x008e2890
void DocX::CallB()
{
    if (mpOther != 0 && mVal40 != 0)
        ((Obj6*)mVal40)->v11();
}

// ---------------------------------------------------------------------------
// stack allocator helpers
// ---------------------------------------------------------------------------
struct SA {
    char pad0[8];
    void* m8;       // end
    void* mc;       // cur
    void* m10;
    bool AllocateNewBlock(unsigned n);
};

inline void* RawAlloc(SA* a, unsigned n)
{
    if ((int)((char*)a->m8 - (char*)a->mc) - (int)n < 0) {
        if (!a->AllocateNewBlock(n))
            return 0;
    }
    char* p = (char*)a->mc;
    a->mc = p + n;
    a->m10 = p + n;
    return p;
}

// @ 0x008e2540
void* __cdecl AllocBlock(unsigned size, SA* a)
{
    unsigned n = (size + 7) & ~7u;
    return RawAlloc(a, n);
}

extern "C" unsigned __cdecl wcslen(const wchar_t* s);

struct Der43;
struct Der4f;
struct Holder {
    char pad[8];
    SA sa;          // +0x08
    wchar_t* AppendWStr(const wchar_t* s, int len);
    Der43* CreateDer43(const wchar_t* a, const wchar_t* b, bool convert);
    Der4f* CreateDer4f(const wchar_t* s, int len, bool convert);
    void* CreateNodeA(const wchar_t* s, int len, bool convert);
    void* CreateElement(const wchar_t* name, const struct AttrSrc* attrs, unsigned nAttrs, bool convert);
};

// @ 0x008e25d0
wchar_t* Holder::AppendWStr(const wchar_t* s, int len)
{
    if (len == -1)
        len = (int)wcslen(s);
    unsigned nbytes = (unsigned)len * 2;
    char* p = (char*)RawAlloc(&sa, (nbytes + 9) & ~7u);
    FUN_011e0744(p, s, nbytes);
    *(wchar16*)(nbytes + (char*)p) = 0;
    return (wchar_t*)p;
}

// ---------------------------------------------------------------------------
// XHTML element nodes constructed into the stack allocator
// ---------------------------------------------------------------------------
struct Base24 {
    virtual void bv();
    char pad[0x14];
    Base24(void*, int);
};

struct Der43 : Base24 {
    void* m18;
    void* m1c;
    __declspec(noinline) Der43(void* a, void* b, void* c);
};
// @ 0x008e2430
Der43::Der43(void* a, void* b, void* c) : Base24(a, 3) { m18 = b; m1c = c; }

struct Der4f : Base24 {
    void* m18;
    void* m1c;
    __declspec(noinline) Der4f(void* a, void* b, void* c);
};
// @ 0x008e24f0
Der4f::Der4f(void* a, void* b, void* c) : Base24(a, 4) { m18 = b; m1c = c; }

// @ 0x008e2650
Der43* Holder::CreateDer43(const wchar_t* a, const wchar_t* b, bool convert)
{
    void* y;
    void* x;
    if (convert) {
        x = AppendWStr(a, -1);
        y = AppendWStr(b, -1);
    } else {
        x = (void*)a;
        y = (void*)b;
    }
    if (!x || !y)
        return 0;
    Der43* p = (Der43*)RawAlloc(&sa, 0x20);
    if (!p)
        return 0;
    return new (p) Der43((void*)this, x, y);
}

struct DNodeA { __declspec(noinline) DNodeA(void*, void*, void*); };

// @ 0x008e26e0
void* Holder::CreateNodeA(const wchar_t* s, int len, bool convert)
{
    if (len == -1)
        len = (int)wcslen(s);
    void* x = (void*)s;
    if (convert)
        x = AppendWStr(s, len);
    if (!x)
        return 0;
    DNodeA* p = (DNodeA*)RawAlloc(&sa, 0x20);
    if (!p)
        return 0;
    return new (p) DNodeA((void*)this, x, (void*)len);
}

// @ 0x008e2770
Der4f* Holder::CreateDer4f(const wchar_t* s, int len, bool convert)
{
    if (len == -1)
        len = (int)wcslen(s);
    void* x = (void*)s;
    if (convert)
        x = AppendWStr(s, len);
    if (!x)
        return 0;
    Der4f* p = (Der4f*)RawAlloc(&sa, 0x20);
    if (!p)
        return 0;
    return new (p) Der4f((void*)this, x, (void*)len);
}

// ---------------------------------------------------------------------------
// DOM helpers
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);

struct Child40 { void* FindChild(const wchar_t* name, int flag); };

// @ 0x008e2810
void* DocX::FindBody()
{
    void* c = *(void**)((char*)this + 0x40);
    if (!c)
        return c;
    if (wcscmp(*(const wchar_t**)((char*)c + 0x34), L"html") == 0)
        return ((Child40*)c)->FindChild(L"body", 0);
    return c;
}

struct IObj {
    virtual void AddRef();
    virtual void Release();
};

// @ 0x008e28b0
void DocX::SetAt(unsigned idx, IObj* o)
{
    IObj** begin = *(IObj***)((char*)this + 0x108);
    IObj** end = *(IObj***)((char*)this + 0x10c);
    if (idx >= (unsigned)(end - begin))
        return;
    IObj* old = begin[idx];
    if (o == old)
        return;
    if (o)
        o->AddRef();
    begin[idx] = o;
    if (old)
        old->Release();
}

struct InList { InList* mpNext; InList* mpPrev; };
struct VI { virtual void v0(); virtual void v1(); virtual void v2(void*); };

// @ 0x008e2930
void DocX::RemoveAllChildren()
{
    InList* head = (InList*)((char*)this + 0x100);
    while (*(void**)((char*)this + 0x104) != (void*)head) {
        VI* p = *(VI**)((char*)this + 0x34);
        void* n = *(void**)((char*)this + 0x104);
        p->v2(*(void**)((char*)n + 0x14));
    }
}

// @ 0x008e29e0
bool DocX::CheckFlag(bool flag)
{
    InList* head = (InList*)((char*)this + 0x100);
    void* p = *(void**)head;
    while (p != (void*)head) {
        if (!flag)
            return true;
        if (*((uint8_t*)p + 0xc) != 0)
            return true;
        p = *(void**)p;
    }
    return false;
}

// ---------------------------------------------------------------------------
// generic constructors (base ctor out-of-line)
// ---------------------------------------------------------------------------
struct B29 {
    virtual void v();
    char pad[0x40];
    B29(void*, void*);
};
struct D29a : B29 {
    void* m44;
    __declspec(noinline) D29a(void* a, void* b);
};
// @ 0x008e2960
D29a::D29a(void* a, void* b) : B29(a, b) { m44 = 0; }

struct D29b : B29 {
    void* m44;
    __declspec(noinline) D29b(void* a, void* b);
};
// @ 0x008e2990
D29b::D29b(void* a, void* b) : B29(a, b) { m44 = 0; }

// ---------------------------------------------------------------------------
// intrusive pointer release / vector free / base ctor
// ---------------------------------------------------------------------------
struct C2b0 {
    virtual void v0();
    virtual void v1();
    virtual void v2(int);
};

// @ 0x008e2af0
int __fastcall Release2(C2b0* p)
{
    volatile long* c = (volatile long*)((char*)p + 4);
    int n = _InterlockedDecrement(c);
    if (n != 0)
        return n;
    _InterlockedExchange(c, 1);
    if (p)
        p->v2(1);
    return 0;
}

struct Vec2b {
    IObj** mpBegin;     // +0
    IObj** mpEnd;       // +4
    char pad[8];
    IObj** mpInline;    // +0x10
    void Free();
};

// @ 0x008e2b20
void Vec2b::Free()
{
    IObj** end = mpEnd;
    for (IObj** it = mpBegin; it < end; ++it) {
        if (*it)
            (*it)->Release();
    }
    if (mpBegin != 0 && mpBegin != mpInline)
        operator_delete__(mpBegin);
}

struct B2b6 {
    virtual void v();
    B2b6(void*, int, void*);
};
struct D2b6 : B2b6 {
    __declspec(noinline) D2b6(void* a, void* b);
};
// @ 0x008e2b60
D2b6::D2b6(void* a, void* b) : B2b6(a, 10, b) {}

// ---------------------------------------------------------------------------
// DOM node with two callback registrations
// ---------------------------------------------------------------------------
struct M10 { void Remove(void*); };
struct Base46 {
    virtual void v();
    virtual ~Base46();
};
struct Node46 : Base46 {
    char pad[0xc];
    void* m10;      // +0x10
    char pad14[4];
    void* m18;      // +0x18
    void* m1c;      // +0x1c
    ~Node46();
};
// @ 0x008e2460
Node46::~Node46()
{
    ((M10*)m10)->Remove(m18);
    ((M10*)m10)->Remove(m1c);
}

// ---------------------------------------------------------------------------
// EA::ResourceMan::Manager (retail layout; large EASTL bodies)
// ---------------------------------------------------------------------------
// EA::ResourceMan::Manager (retail layout, 0x178 bytes)
struct CAlloc {
    virtual void a0();
    virtual void a1();
    virtual void* Alloc(unsigned size, const char* name, unsigned flags);   // +8
    virtual void Free(void* p, unsigned size);                              // +0xc
};
CAlloc* __cdecl GetDefaultAllocator();   // 0x925cb0

// intrusive refcounted factory (refcount at +4; vtable: deleting dtor, OnAdded, OnRemoved)
struct IFactory {
    virtual void* Del(unsigned flags);
    virtual void OnAdded();
    virtual void OnRemoved();
    volatile long mRef;     // +4
};

inline void AddRefF(IFactory* p)
{
    if (p)
        _InterlockedExchangeAdd(&p->mRef, 1);
}

inline void ReleaseF(IFactory* p)
{
    if (p) {
        if (_InterlockedExchangeAdd(&p->mRef, -1) - 1 == 0) {
            _InterlockedExchange(&p->mRef, 1);
            p->Del(1);
        }
    }
}

struct FEntry {
    IFactory* mp;
    int mPriority;
};

struct FactoryVec {
    FEntry* mpBegin;    // +0
    FEntry* mpEnd;      // +4
    FEntry* mpCap;      // +8
    CAlloc* mpAlloc;    // +0xc
    int mFlags;         // +0x10
    FactoryVec(CAlloc* a) : mpBegin(0), mpEnd(0), mpCap(0), mpAlloc(a), mFlags(0) {}
    void insert(FEntry* where, const FEntry& v);        // 0x8e1690
    void DoInsertValue(FEntry* where, const FEntry& v); // 0x8e12c0
    void DestroyRange(FEntry* first, FEntry* last);     // 0x8dede0
    ~FactoryVec()
    {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin)
            mpAlloc->Free(mpBegin, (unsigned)(((char*)mpCap - (char*)mpBegin) >> 3) * 8);
    }
};
void __cdecl MoveDown(FEntry* first, FEntry* last, FEntry* dest);   // 0x8defe0

extern char vtbl_Manager[];     // 0x1436ae8
extern char vtbl_ZBase[];       // 0x13effb8
extern void* gEmptyBuckets[];   // 0x154df28

struct ZBase {
    void* vt;
    ~ZBase() { vt = vtbl_ZBase; }
};

struct RBAnchor {
    void* right;
    void* left;
    void* parent;
    int color;
    RBAnchor() : left(0), parent(0), color(0) {}
};

struct RBSet {
    uint8_t mCompare;       // +0 (padded to 4)
    RBAnchor mAnchor;       // +4
    int mnSize;             // +0x14
    CAlloc* mpAlloc;        // +0x18
    int mnFlags;            // +0x1c
    void DoNuke(void* root);    // 0x8de4f0
    RBSet(CAlloc* a) : mCompare(0), mpAlloc(a), mnFlags(0)
    {
        mAnchor.right = &mAnchor;
        mAnchor.left = &mAnchor;
        mAnchor.parent = 0;
        *(char*)&mAnchor.color = 0;
        mnSize = 0;
    }
    ~RBSet() { DoNuke(mAnchor.parent); }
};

struct HTBase {
    uint32_t pad0;
    void** mpBuckets;       // +4
    unsigned mnBuckets;     // +8
    unsigned mnElems;       // +0xc
    float mfMaxLoad;        // +0x10
    float mfGrowth;         // +0x14
    unsigned mnNextResize;  // +0x18
    CAlloc* mpAlloc;        // +0x1c
    int mFlags;             // +0x20
    HTBase(CAlloc* a) : mnBuckets(1), mnElems(0), mfMaxLoad(1.0f), mfGrowth(2.0f), mnNextResize(0), mpAlloc(a), mFlags(0)
    {
        mpBuckets = gEmptyBuckets;
    }
};

// eastl::hashtable instantiations; N selects the (out-of-line) DoFreeNodes of that table type
template <int N>
struct HT : HTBase {
    HT(CAlloc* a) : HTBase(a) {}
    void DoFreeNodes(void** buckets, unsigned n);
    ~HT()
    {
        DoFreeNodes(mpBuckets, mnBuckets);
        mnElems = 0;
        if (mnBuckets > 1)
            mpAlloc->Free(mpBuckets, mnBuckets * 4 + 4);
    }
};

struct IDBList {
    char d[0x78];
    IDBList(CAlloc* a);     // 0x8de8e0
    ~IDBList();             // 0x8e1420
};

struct StackAllocator {
    char d[0x20];
    StackAllocator(CAlloc* a, unsigned size, unsigned align);   // 0x925f30
    ~StackAllocator();                                          // 0x925e60
};

struct Mutex2 {
    char d[0x30];
    Mutex2(void*, bool);    // 0x9222a0
    ~Mutex2();              // 0x922130
};

struct ZBase1 : ZBase {
    ZBase1() { vt = vtbl_Manager; }
};

struct ManagerX : ZBase1 {
    bool mbInitialized;             // +4
    CAlloc* mpAllocator;            // +8
    RBSet mFunctionInfoSet;         // +0xc
    IDBList* mpDatabaseList;        // +0x2c
    HT<1> mTypeToFactoryMap;        // +0x30
    HT<2> mResourceToRecordMap;     // +0x54
    HT<3> mTable78;                 // +0x78
    FactoryVec mFactories;          // +0x9c (pair<AutoRefCount<Factory>,int> vector)
    HT<4> mTableB0;                 // +0xb0
    StackAllocator mStack;          // +0xd4
    HT<5> mNameMap;                 // +0xf4
    Mutex2 mNameMutex;              // +0x118
    Mutex2 mMutex;                  // +0x148

    ManagerX(CAlloc* alloc);
    ~ManagerX();
    bool RegisterFactory(bool bAdd, IFactory* f, int prio);
    void ResetAll();
};

typedef char chk_mgr_size[(sizeof(ManagerX) == 0x178) ? 1 : -1];

// @ 0x008e1d50
bool ManagerX::RegisterFactory(bool bAdd, IFactory* f, int prio)
{
    if (!bAdd) {
        FEntry* it = mFactories.mpBegin;
        FEntry* end = mFactories.mpEnd;
        if (it == end)
            return false;
        for (; it != end; ++it) {
            if (it->mp == f)
                goto found;
        }
        return false;
    found:
        if (_InterlockedExchangeAdd(&it->mp->mRef, 0) == 1)
            it->mp->OnRemoved();
        if (it + 1 < mFactories.mpEnd)
            MoveDown(it + 1, mFactories.mpEnd, it);
        --mFactories.mpEnd;
        ReleaseF(mFactories.mpEnd->mp);
        return true;
    }
    AddRefF(f);
    FEntry local;
    local.mp = f;
    AddRefF(f);
    local.mPriority = prio;
    ReleaseF(f);
    bool r = true;
    for (FEntry* it = mFactories.mpBegin; it != mFactories.mpEnd; ++it) {
        if (it->mp == f) {
            r = false;
            goto done;
        }
        if (it->mPriority < prio) {
            mFactories.insert(it, local);
            goto added;
        }
    }
    {
        FEntry* e = mFactories.mpEnd;
        if (e < mFactories.mpCap) {
            mFactories.mpEnd = e + 1;
            if (e) {
                e->mp = f;
                AddRefF(f);
                e->mPriority = prio;
            }
        } else {
            mFactories.DoInsertValue(e, local);
        }
    }
added:
    f->OnAdded();
done:
    ReleaseF(local.mp);
    return r;
}

// @ 0x008e1f10
ManagerX::~ManagerX()
{
    vt = vtbl_Manager;
    mpDatabaseList->~IDBList();
    mpAllocator->Free(mpDatabaseList, 0);
}

// @ 0x008e20c0
ManagerX::ManagerX(CAlloc* alloc)
    : mbInitialized(false),
      mpAllocator(alloc ? alloc : GetDefaultAllocator()),
      mFunctionInfoSet(mpAllocator),
      mpDatabaseList(new (mpAllocator->Alloc(0x78, "Resource/Mgr/DBList", 0)) IDBList(mpAllocator)),
      mTypeToFactoryMap(mpAllocator),
      mResourceToRecordMap(mpAllocator),
      mTable78(mpAllocator),
      mFactories(mpAllocator),
      mTableB0(mpAllocator),
      mStack(mpAllocator, 0x400, 0x20),
      mNameMap((CAlloc*)&mStack),
      mNameMutex(0, true),
      mMutex(0, true)
{
    vt = vtbl_Manager;
}

// ---------------------------------------------------------------------------
// small lookups / helpers
// ---------------------------------------------------------------------------
// @ 0x008e24a0
extern const void* gListStyleDefs[];      // 0x154c490 static definition table (begin)
extern const void* gListStyleDefsEnd[];   // 0x154c5d8 (end)
int DocX::LookupStyle()
{
    struct Key { int name; int value; } key;
    key.value = 0;
    key.name = *(int*)((char*)this + 0x18);
    struct Range { char* first; char* last; } r;
    FUN_008f3790(&r, gListStyleDefs, gListStyleDefsEnd, &key);
    const int* p = (r.first + 8 == r.last) ? (const int*)(r.first + 4) : &key.value;
    return *p;
}

// @ 0x008e2580
bool EqAttr(void* elem, int id, const wchar_t* s)
{
    const wchar_t* v = ((XElem*)elem)->GetAttrValue(id);
    if (v == s)
        return true;
    if (v != 0 && s != 0)
        return _wcsicmp(v, s) == 0;
    return false;
}

// @ 0x008e2a10
void DocX::RemoveAttr(IKV* kv)
{
    void** head = (void**)((char*)this + 0x100);
    void** node = (void**)*head;
    if (node == head)
        return;
    do {
        if (*(int*)((char*)node + 0x14) == kv->m4)
            goto found;
        node = (void**)*node;
    } while (node != head);
    return;
found:
    unsigned idx = *(unsigned*)((char*)node + 0x10);
    IObj** begin = *(IObj***)((char*)this + 0x108);
    IObj** slot = begin + idx;
    IObj* ov = *slot;
    IObj* nv = (IObj*)kv->m10;
    if (nv != ov) {
        if (nv)
            nv->AddRef();
        *slot = nv;
        if (ov)
            ov->Release();
    }
    void** prev = (void**)node[1];
    void** next = (void**)node[0];
    *prev = next;
    next[1] = prev;
    node[0] = 0;
    node[1] = 0;
    if (kv->m0 != 4) {
        *(uint8_t*)((char*)this + 0x2c) = 1;
        if (kv->m8 == 0) {
            struct { Obj6* p; int k; } ctx;
            Obj6* p = *(Obj6**)((char*)this + 0x40);
            ctx.k = 6;
            ctx.p = p;
            p->v9(&ctx, 1);
        }
    }
}

// @ 0x008e2b90
void ManagerX::ResetAll()
{
    // frees three intrusive sub-lists (+0x108, +0xa8, +0x50), destroys the
    // list anchor (+0x100) and resets the stack allocator at +8
    Vec2b* v1 = (Vec2b*)((char*)this + 0x108);
    Vec2b* v2 = (Vec2b*)((char*)this + 0xa8);
    Vec2b* v3 = (Vec2b*)((char*)this + 0x50);
    v1->Free();
    FUN_00620230((char*)this + 0x100);
    v2->Free();
    v3->Free();
    FUN_00928dc0((char*)this + 8);
}

// ---------------------------------------------------------------------------
// XHTML Document::CreateElement (name -> element subclass), allocates in the stack allocator
// ---------------------------------------------------------------------------
extern const wchar_t* gTagSysGui;       // 0x154c5f8
extern const wchar_t* gTagObject;       // 0x154c5f4
extern const wchar_t* gTagForm;         // 0x154c5f0
extern const wchar_t* gTagInput;        // 0x154c5ec
extern const wchar_t* gTagButton;       // 0x154c5e8
extern const wchar_t* gTagSelect;       // 0x154c5e4
extern const wchar_t* gTagTextArea;     // 0x154c5e0
extern char vtbl_ElemSysGui[];          // 0x1436da8

struct ElemSysGui {
    void* vt;
    char pad[0x44];
    __declspec(noinline) ElemSysGui(void* doc, int kind, const wchar_t* name);   // 0x8e5370
};

struct ElemDefault {
    char pad[0x44];
    __declspec(noinline) ElemDefault(void* doc, const wchar_t* name);   // 0x8e4940
};

struct ElemAny {
    void AppendAttr(void* attr);   // 0x8e4380
};

struct AttrSrc {
    const wchar_t* name;
    const wchar_t* value;
};

// @ 0x008e2c10
void* Holder::CreateElement(const wchar_t* name, const AttrSrc* attrs, unsigned nAttrs, bool convert)
{
    if (convert)
        name = AppendWStr(name, -1);
    if (!name)
        return 0;
    void* e;
    if (_wcsicmp(name, gTagSysGui) == 0) {
        e = RawAlloc(&sa, 0x48);
        if (!e)
            return 0;
        new (e) ElemSysGui(this, 9, name);
        *(void**)e = vtbl_ElemSysGui;
    } else if (_wcsicmp(name, gTagObject) == 0) {
        e = AllocBlock(0x44, &sa);
        if (!e)
            return 0;
        e = new (e) D2b6(this, (void*)name);
    } else if (_wcsicmp(name, gTagForm) == 0) {
        e = AllocBlock(0x48, &sa);
        if (!e)
            return 0;
        e = new (e) D29b(this, (void*)name);
    } else if (_wcsicmp(name, gTagInput) == 0 || _wcsicmp(name, gTagButton) == 0 ||
               _wcsicmp(name, gTagSelect) == 0 || _wcsicmp(name, gTagTextArea) == 0) {
        e = AllocBlock(0x50, &sa);
        if (!e)
            return 0;
        e = new (e) D29a(this, (void*)name);
    } else {
        e = AllocBlock(0x44, &sa);
        if (!e)
            return 0;
        e = new (e) ElemDefault(this, name);
    }
    if (e && nAttrs > 0) {
        do {
            ((ElemAny*)e)->AppendAttr(CreateDer43(attrs->name, attrs->value, convert));
            ++attrs;
        } while (--nAttrs);
    }
    return e;
}
