// src/game/UTFSpore_Win32/Document.cpp -- migrated from slice(s) s008e2dd0, s008e1d50 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Document.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/XHTML/DOM/Document.h"
#include "EA/Thread/Mutex.h"
#include "EA/Allocator/ICoreAllocator.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);
extern char vtbl_Manager[];     // 0x1436ae8
extern char vtbl_ZBase[];       // 0x13effb8
extern void* gEmptyBuckets[];   // 0x154df28
extern const wchar_t* gTagSysGui;       // 0x154c5f8
extern const wchar_t* gTagObject;       // 0x154c5f4
extern const wchar_t* gTagForm;         // 0x154c5f0
extern const wchar_t* gTagInput;        // 0x154c5ec
extern const wchar_t* gTagButton;       // 0x154c5e8
extern const wchar_t* gTagSelect;       // 0x154c5e4
extern const wchar_t* gTagTextArea;     // 0x154c5e0
extern char vtbl_ElemSysGui[];          // 0x1436da8
#include <new>
#include <intrin.h>
#include <stddef.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

// ---- items of slice s008e1d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IObj;
void __cdecl operator_delete(void* p);
void __cdecl operator_delete__(void* p);
void __cdecl FUN_00928dc0(void* alloc);
void __cdecl FUN_00620230(void* p);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);
struct IKV { int m0; int m4; char m8; char pad9[7]; int m10; };
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
struct SA {
    char pad0[8];
    void* m8;       // end
    void* mc;       // cur
    void* m10;
    bool AllocateNewBlock(unsigned n);     // 0x00928ba0 EA::Allocator::StackAllocator::AllocateNewBlock
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
struct Der4f : Base24 {
    void* m18;
    void* m1c;
    __declspec(noinline) Der4f(void* a, void* b, void* c);
};
struct IObj {
    virtual void AddRef();
    virtual void Release();
};
struct InList { InList* mpNext; InList* mpPrev; };
struct VI { virtual void v0(); virtual void v1(); virtual void v2(void*); };
struct B29 {
    virtual void v();
    char pad[0x40];
    B29(void*, void*);
};
struct D29a : B29 {
    void* m44;
    __declspec(noinline) D29a(void* a, void* b);
};
struct D29b : B29 {
    void* m44;
    __declspec(noinline) D29b(void* a, void* b);
};
struct C2b0 {
    virtual void v0();
    virtual void v1();
    virtual void v2(int);
};
struct Vec2b {
    IObj** mpBegin;     // +0
    IObj** mpEnd;       // +4
    char pad[8];
    IObj** mpInline;    // +0x10
    void Free();
};
struct B2b6 {
    virtual void v();
    B2b6(void*, int, void*);
};
struct D2b6 : B2b6 {
    __declspec(noinline) D2b6(void* a, void* b);
};
struct CAlloc {
    virtual void a0();
    virtual void a1();
    virtual void* Alloc(unsigned size, const char* name, unsigned flags);   // +8
    virtual void Free(void* p, unsigned size);                              // +0xc
};
struct IFactory {
    virtual void* Del(unsigned flags);
    virtual void OnAdded();
    virtual void OnRemoved();
    volatile long mRef;     // +4
};
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
// ---- items of slice s008e1d50 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void* __cdecl AllocBlock(unsigned size, SA* a);  // 0x008e2540 (stays in the slice: not this object's)

// ---- items of slice s008e2dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void Fn829110(void*, void*, void*, void*, void*);   // 0x00829110
extern "C" void Fnac97a0(void*, void*, void*);                 // 0x00ac97a0
typedef unsigned int   uint32;
static void FreeWCStr(char* begin, char* capacity)
{
    if (((capacity - begin) & ~1) > 2 && begin) {
        operator_delete__(begin);
    }
}
struct Doc {
    void Fn8e3380(void* elem, void* arg);   // @ 0x008e3380
    void Fn8e3600(void* arg);               // @ 0x008e3600
};
// ---- items of slice s008e2dd0 end

// @ 0x008e2890
void EA::XHTML::DOM::Document::DestroyFormControls()
{
    if (mpFormControlMgr != 0 && mpDocumentElement != 0)
        ((Obj6*)mpDocumentElement)->v11();
}

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

// @ 0x008e2960
D29a::D29a(void* a, void* b)
: B29(a, b) { m44 = 0; }

// @ 0x008e2990
D29b::D29b(void* a, void* b)
: B29(a, b) { m44 = 0; }

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

// @ 0x008e2b60
D2b6::D2b6(void* a, void* b)
: B2b6(a, 10, b) {}

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

// @ 0x008e2dd0
void* __fastcall Fn8e2dd0(int* pThis, int param_2) // placeholder; see Fn8e2dd0_impl
{
    return pThis;
}

// @ 0x008e2ed0
void __fastcall Fn8e2ed0(void* pThis)
{
    char* c = (char*)pThis;
    FreeWCStr(*(char**)(c + 0x50), *(char**)(c + 0x58));
    FreeWCStr(*(char**)(c + 0x38), *(char**)(c + 0x40));
    FreeWCStr(*(char**)(c + 0x14), *(char**)(c + 0x1c));
}

// @ 0x008e2f30
void Fn8e2f30(int* pThis, char* first, char* last, char* pos)
{
    if (pos == last) return;
    int* begin = (int*)pThis[0];
    int* end   = (int*)pThis[1];
    uint32 n = (uint32)((last - pos) >> 2);
    if (n <= (uint32)((char*)end - (char*)begin >> 2)) {
        uint32 off = (uint32)(((char*)end - first) >> 2);
        if (off <= n) {
            char* mid = pos + off * 4;
            Fn829110(0, mid, last, 0, 0);
            pThis[1] = pThis[1] + (int)((n - off) * 4);
            Fn829110(0, first, 0, 0, 0);
            pThis[1] = pThis[1] + (int)(off * 4);
            Fnac97a0(pos, mid, first + off * 4);
            return;
        }
    }
}

// @ 0x008e3100
void __fastcall Fn8e3100(void* pThis, int param_2, void* p3, void* p4, char p5, int param_6)
{
    (void)pThis; (void)param_2; (void)p3; (void)p4; (void)p5; (void)param_6;
}

// @ 0x008e3380
__declspec(noinline) void Doc::Fn8e3380(void* elem, void* arg)
{
    (void)elem; (void)arg;
    *(volatile int*)((char*)this + 0x40) = 0;
}

// @ 0x008e3600
void Doc::Fn8e3600(void* arg)
{
    void* q = *(void**)((char*)this + 0x40);
    if (q) Fn8e3380(q, arg);
}

// @ 0x008e3660
void __fastcall Fn8e3660(void* pThis, void* elem)
{
    (void)pThis; (void)elem;
}
