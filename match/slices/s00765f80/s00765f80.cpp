// Slice s00765f80: UTFKernel "RenderAsset" graphics-resource family
// (cEditorResource / cPropertyList-derived resource objects, their ctors/dtors,
//  the resource factory create-by-type helper, and two small vector helpers).
//
// Module: /O2 /MD /Gy /EHsc /TP (no SSE). All callees/globals are masked
// relocations, so only call shapes, offsets and stack frames matter.
#include "types.h"
#include <intrin.h>
#include <string.h>
#include <malloc.h>
#include <new>

// ---------------------------------------------------------------------------
// out-of-slice callees (relocation targets)
// ---------------------------------------------------------------------------
extern "C" {
extern char g_allocFile[];
void __cdecl sub_87cf40(void* p);
void __cdecl sub_87cf60(void* p, int v);
bool __cdecl sub_87d2a0(void* p, int a, int b);
bool __cdecl sub_87d030(void* p, void* a, int n);
void __cdecl sub_87cff0(void* p);
void __cdecl sub_87d260(void* p);
void* __cdecl Ctor765f10(void* p);
void* __cdecl Ctor763100(void* p);
void* __cdecl Ctor7004d0(void* p);
void __cdecl sub_4e0880(void* vec, uint32_t n);
// 0x0f473a0 : EASTL allocator (size, name, a, b, file, line)
void* __cdecl sub_f473a0(uint32_t size, const char* name, int a, int b, const char* file, int line);
// 0x0f473d0 : aligned allocator (8 args)
void* __cdecl EA_Alloc8(uint32_t size, int align, int a, const char* name, int b, int c, const char* file, int line);
// 0x0f47380 : EASTL deallocate
void  __cdecl EA_Dealloc(void* p);
// 0x11e0744 : memcpy thunk
void* __cdecl memcpy_t(void* dst, const void* src, uint32_t n);
// 0x11e40a0 : rw::core::arena::Arena::Release (thiscall, ecx=obj)
// 0x006c20b0 / 0x006c2060 / 0x006c20e0 : inline-container helpers
void  __cdecl sub_6c20b0(void* p);
void  __cdecl sub_6c2060(void* p, int a, int b);
void  __cdecl sub_6c20e0(void* p);
// 0x006c1570 : vector growth helper (thiscall, ecx=vector)
// 0x00b5f950 : AutoRefCount::operator=
void* __cdecl AssignRef6b5f950(void* dst, void* p);
// 0x006ac040 : sub_6ac040
void  __cdecl sub_6ac040(int a, void* b);
// 0x0067dcc0 / 0x0067dcd0 : managers
void* __cdecl MessageServer();
void* __cdecl Manager67dcd0();
// 0x0093a780 : EA::IO::ReadInt32
bool  __cdecl ReadInt32(void* stream, void* dst, int count, int flags);
// 0x004b54b0 / 0x006ac0a0 : ref-vector push / sub_6ac040-like
void  __cdecl sub_4b54b0(void* p);
void  __cdecl sub_6ac0a0(int a, void* b);
// 0x011eff60 : arena/refcount release helper
void  __cdecl sub_11eff60(void* p);
// 0x09276c0 : cLocalLightInfo destructor (allocator, obj)
void  __cdecl cLocalLightInfo_dtor(void* alloc, void* obj);
// 0x006abe20 : SP::cResourceBase::AsInterface
void* __cdecl cResourceBase_AsInterface(void* self, int type);
// 0x00fc7e50 : EA::XHTML::DOM::Node::Type (thiscall)
} // extern "C"

// helper vtable invoke
static inline void* VP(void* p) { return *(void**)p; }

// ---------------------------------------------------------------------------
// common interfaces
// ---------------------------------------------------------------------------
struct IRef {
    virtual void AddRef();   // +0
    virtual void Release();  // +4
    virtual void m2();       // +8
    virtual void m3();       // +0xc
    virtual void m4();       // +0x10
    virtual void m5();       // +0x14
    virtual void m6();       // +0x18
    virtual void m7();       // +0x1c
};

struct Arena {
    void Release();          // 0x11e40a0
};

struct IElem { virtual void m0(); };

// ===========================================================================
// @ 0x00765f80  scalar deleting destructor of a refcounted resource
// ===========================================================================
struct IResEd {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3();
    virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7();
    virtual void e8(); virtual void e9(); virtual void eA(); virtual void eB();
    virtual ~IResEd();
    int mRef;                 // +0x4
    int m08, m0c, m10, m14;   // +0x8..+0x14
    int m18;                  // +0x18
    IRef* m1c;                // +0x1c
};
IResEd::~IResEd() { if (m1c) m1c->Release(); }
void DeleteResEd(IResEd* p) { delete p; }

// ===========================================================================
// @ 0x00765fe0  ctor of the type-0x2f4e681b resource (MI: cPropertyList-like base + secondary)
// ===========================================================================
struct BaseP {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
    virtual void p8(); virtual void p9(); virtual void pA(); virtual void pB();
    virtual void pC(); virtual void pD(); virtual void pE(); virtual void pF();
    int mRef;                 // +0x4
    int k8, kc, k10, k14;     // +0x8..+0x14
    int x18;                  // +0x18
    BaseP() { (void)_InterlockedExchange((volatile long*)&mRef, 0); k8 = 0; kc = 0; k10 = 0; k14 = 0; x18 = 0; }
};
struct SecP {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    SecP() {}
};
struct ResB : BaseP, SecP {
    int a20, a24, a28, a2c;   // +0x20..+0x2c
    ResB();
    void* AsInterface(int type);      // 0x766030
    void MoveOut(void* out);          // 0x766100
    void Method66070(int a, int b);   // (secondary slot, 0x766070)
    void Method660b0();               // (secondary slot, 0x7660b0)
};
ResB::ResB() : a20(0), a24(0), a28(0), a2c(0) {}
void* InitResB(void* p) { return new (p) ResB(); }

// ===========================================================================
// @ 0x00766030
// ===========================================================================
struct RawRes {
    void* AsInterface(int type);
};
void* __fastcall AsInterfaceFC(void* self, int, int type) {
    if (type == 0x34c84e9) {
        if (self)
            return (char*)self + 0x1c;
        return 0;
    }
    if (type == 0x2f4e681b)
        return self;
    return ((RawRes*)self)->AsInterface(type);
}

// ===========================================================================
// @ 0x00766070
// ===========================================================================
void ResB::Method66070(int a, int b) {
    Arena* arena = *(Arena**)((char*)this - 4);
    if (arena)
        arena->Release();
    *(void**)((char*)this - 4) = 0;
    void* p = (char*)this + 4;
    sub_6c20b0(p);
    sub_6c2060(p, a, b);
}

// ===========================================================================
// @ 0x007660b0
// ===========================================================================
void ResB::Method660b0() {
    sub_6c20e0((char*)this + 4);
}

// ===========================================================================
// @ 0x00766100  move +0x4..+0x10 out and clear
// ===========================================================================
void ResB::MoveOut(void* out) {
    int* o = (int*)out;
    char* self = (char*)this;
    o[0] = *(int*)(self + 4);
    o[1] = *(int*)(self + 8);
    o[2] = *(int*)(self + 0xc);
    o[3] = *(int*)(self + 0x10);
    *(int*)(self + 4) = 0;
    *(int*)(self + 8) = 0;
    *(int*)(self + 0xc) = 0;
    *(int*)(self + 0x10) = 0;
}

// ===========================================================================
// @ 0x00766140  ctor with an EH-initialised temporary array + refcounted member
// ===========================================================================
struct AllocDesc {
    uint32_t size;            // +0
    uint32_t type;            // +4
    AllocDesc();              // 0x6c0fa0
    ~AllocDesc();             // 0xc2e4e0
};
void __cdecl FreePtrs4(void* p);                                  // 0x6c20b0
void __cdecl AllocFromDesc(void* dst, const void* desc, int n);   // 0x6c2060
struct ResD {
    char pad0[0x18];
    void* mArena;             // +0x18
    void* m20;                // +0x20
    void* m24;                // +0x24
    void* m28;                // +0x28
    void* m2c;                // +0x2c
    ResD();
};
ResD::ResD() {
    *(void**)this = (void*)0x140e118;
    *(void**)((char*)this + 0x1c) = (void*)0x140e0f8;
    AllocDesc desc[4];
    desc[0].size = 0;
    desc[0].type = 1;
    if (mArena)
        ((Arena*)mArena)->Release();
    mArena = 0;
    FreePtrs4((char*)this + 0x20);
    AllocFromDesc((char*)this + 0x20, desc, 0);
    *(void**)((char*)this + 0x1c) = (void*)0x13eb938;
    *(void**)this = (void*)0x13eb938;
}

// ===========================================================================
// @ 0x00766220  ctor of the small (0x1c) cPropertyList-derived resource
// ===========================================================================
struct BaseE {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3();
    virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7();
    virtual void e8(); virtual void e9(); virtual void eA(); virtual void eB();
    int mRef;                 // +0x4
    int k8, kc, k10, k14;     // +0x8..+0x14
    BaseE() { (void)_InterlockedExchange((volatile long*)&mRef, 0); k8 = 0; kc = 0; k10 = 0; k14 = 0; }
};
struct ResE : BaseE {
    int a18;                  // +0x18
    ResE();
    ~ResE();
};
ResE::ResE() : a18(0) {}
void* InitResE(void* p) { return new (p) ResE(); }
ResE::~ResE() {
    if (a18) {
        sub_11eff60((void*)a18);
        cLocalLightInfo_dtor(*(void**)0x016c8b44, (void*)a18);
    }
}

// ===========================================================================
// @ 0x007662d0  vector<stride 0xa0>::insert(position, n, value)
// ===========================================================================
struct VBig {
    char* mpBegin;            // +0
    char* mpEnd;              // +4
    char* mpCap;              // +8
    void _insert(char* position, uint32_t n, char* value);
};
extern "C" {
// container helpers used by VBig::insert (relocation-masked)
char* __cdecl BigMoveBack(char* dst, char* first, char* last, char* src);   // 0x764720
char* __cdecl BigCopyBack(char* dst, char* first, char* last);              // 0x763f90
char* __cdecl BigMove(char* dst, char* first, char* last);                  // 0x763f10
char* __cdecl BigUninitFill(char* dst, uint32_t n, char* value);            // 0x765200
char* __cdecl BigUninitCopy(char* dst, char* first, char* last);            // 0x7651d0
void  __cdecl BigDestroyRange(void* p, int n);                              // 0x763e50
}

void VBig::_insert(char* position, uint32_t n, char* value) {
    uint32_t size = (uint32_t)((mpEnd - mpBegin) / 0xa0);
    if (size < n) {
        uint32_t cap = size * 2;
        if (size == 0)
            cap = 1;
        uint32_t need = size + n;
        if (need < cap)
            need = cap;
        char* nb = need ? (char*)EA_Alloc8(need * 0xa0, 0x10, 0, "Graphics", 0, 0, g_allocFile, 0xe5) : 0;
        char* p = BigMove(nb, mpBegin, position);
        BigUninitFill(p, n, value);
        char* ne = BigMove(position, mpEnd, p + n * 0xa0);
        if (mpBegin && mpBegin != *(char**)((char*)this + 0x10))
            EA_Dealloc(mpBegin);
        mpBegin = nb;
        mpEnd = ne;
        mpCap = nb + need * 0xa0;
    } else if (n) {
        char* end = mpEnd;
        uint32_t right = (uint32_t)((end - position) / 0xa0);
        if (n < right) {
            char* edge = end - n * 0xa0;
            BigMoveBack(edge, end, position, end);
            mpEnd = end + n * 0xa0;
            BigMoveBack(position + n * 0xa0, edge, end, position);
            BigUninitFill(position, n, value);
        } else {
            BigUninitFill(end, n - right, value);
            mpEnd = end + (n - right) * 0xa0;
            BigMove(position, end, mpEnd);
            mpEnd += right * 0xa0;
            BigUninitFill(position, right, value);
        }
    }
}

// ===========================================================================
// @ 0x007664e0  SP::cGraphicsResourceFactory::PNGWriteCallback
// ===========================================================================
struct PngInner {
    char pad0[0x1c];
    int      c1c;      // +0x1c
    void*    c20;      // +0x20
    void*    c24;      // +0x24
    void*    c28;      // +0x28
    uint32_t c2c;      // +0x2c
    uint32_t c30;      // +0x30
    char     c34;      // +0x34
};
struct PngObj10 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual int  v6();      // +0x18
    virtual void v7(); virtual void v8();
    virtual void v9();      // +0x24
};
struct PngArg2 {
    char pad0[0xc];
    PngInner* inner;        // +0xc
    PngObj10* obj10;        // +0x10
    void*     p14;          // +0x14
    unsigned char flag18;   // +0x18
};
struct PngArg {
    char pad[0x8];
    PngArg2* p08;           // +0x8
};
struct PngCtx {
    char pad[0x10];
    void ctor87cf40();                          // 0x87cf40 (thiscall)
    void m87cf60(int v);                        // 0x87cf60
    bool m87d2a0(int a, int b);                 // 0x87d2a0
    bool m87d030(void* dst, void* src, int n);  // 0x87d030
    void m87cff0();                             // 0x87cff0
    void m87d260();                             // 0x87d260
};
struct MsgSrv {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5();
    virtual int  s6(void* a, int, int, int);    // +0x18
};
void __cdecl EA_Free(void* p);                                    // 0xf47380
struct PngStr {
    const char* mpBegin;    // +0
    const char* mpEnd;      // +4
    const char* mpCap;      // +8
    ~PngStr() {
        if ((int)(mpCap - mpBegin) > 1 && mpBegin != 0)
            EA_Free((void*)mpBegin);
    }
};
void __cdecl EAString_sprintf(PngStr* s, const char* fmt, ...);   // 0x472fe0
void __cdecl MsvcrSprintf(char* dst, const char* fmt, ...);       // 0x13cc4a0

bool __stdcall PNGWriteCallback(PngArg* arg) {
    unsigned char buf[0x2a70];
    memset(buf, 0, 0x2a70);
    PngArg2* a = arg->p08;
    PngInner* inner = a->inner;
    int c1c = inner->c1c;
    void* c20 = inner->c20;
    *(int*)(buf + 0x10) = c1c;
    *(void**)(buf + 0x14) = c20;
    *(int*)(buf + 0x18) = 0x20;
    *(int*)(buf + 0x438) = (a->flag18 != 0) ? 8 : 0;
    if (inner->c34 != 0) {
        PngStr s;
        s.mpBegin = (const char*)0x1667bac;
        s.mpEnd   = (const char*)0x1667bac;
        s.mpCap   = (const char*)0x1667bad;
        EAString_sprintf(&s, "0x%08x:0x%08x", inner->c2c, inner->c30);
        MsvcrSprintf((char*)buf + 0x65c, s.mpBegin);
    }
    PngCtx ctx;
    ctx.ctor87cf40();
    int v = a->obj10->v6();
    ctx.m87cf60(v);
    bool ok = ctx.m87d2a0(4, 1);
    if (!ok) {
        ctx.m87d260();
        return false;
    }
    bool wrote = ctx.m87d030(buf, inner->c28, c1c * 4);
    ctx.m87cff0();
    a->obj10->v9();
    MsgSrv* srv = (MsgSrv*)MessageServer();
    if (srv && a->p14)
        srv->s6(a->p14, 0, 0, 0);
    ctx.m87d260();
    return wrote;
}
extern "C" {
void __cdecl sub_87cf40(void* p);
void __cdecl sub_87cf60(void* p, int v);
bool __cdecl sub_87d2a0(void* p, int a, int b);
bool __cdecl sub_87d030(void* p, void* a, int n);
void __cdecl sub_87cff0(void* p);
void __cdecl sub_87d260(void* p);
}

// ===========================================================================
// @ 0x007666a0  factory create-by-type helper
// ===========================================================================
extern "C" {
void* __cdecl NewList7639(void* p);  // (unused)
}
// placement-ctor target types (call shapes only; symbols are relocation-masked)
struct CEditorRes { CEditorRes(); };       // 0x763100 (thiscall, no args)
struct D7004d0    { D7004d0(); };          // 0x7004d0
struct D765f10    { D765f10(void*); };     // 0x765f10 (thiscall, one arg)
struct AutoRef {
    void* p;                               // +0
    AutoRef& operator=(void* q);           // 0xb5f950 (thiscall, one arg)
};

bool __stdcall CreateByType(void** out, uint32_t type, int sub) {
    AutoRef ref;
    ref.p = 0;
    if (type < 0x2cb4f30) {
        if (type == 0x2cb4f2f) {
            void* p = sub_f473a0(0x3fe4, "RenderAsset", 0, 0, 0, 0);
            if (p) {
                *(void**)p = (void*)0x13ebcdc;
                _InterlockedExchange((volatile long*)((char*)p + 4), 0);
                *(int*)((char*)p + 8) = 0;
                *(int*)((char*)p + 0xc) = 0;
                *(int*)((char*)p + 0x10) = 0;
                *(int*)((char*)p + 0x14) = 0;
                *(void**)p = (void*)0x140e0d0;
                ref.p = p;
                ((IRef*)p)->AddRef();
            }
        } else if (type == 0xe6bce5) {
            void* p = sub_f473a0(0x140, "RenderAsset", 0, 0, 0, 0);
            ref = p ? (void*)new (p) D7004d0() : 0;
            sub_6ac040(4, ref.p);
        } else if (type == 0x1c135da) {
            void* p = sub_f473a0(0x2c, "RenderAsset", 0, 0, 0, 0);
            ref = p ? (void*)new (p) CEditorRes() : 0;
            sub_6ac040(4, ref.p);
        } else {
            return false;
        }
    } else if (type == 0x2f4e681b) {
        void* p = sub_f473a0(0x30, "RenderAsset", 0, 0, 0, 0);
        if (!p)
            return false;
        void* q = (void*)new (p) ResB();
        if (!q)
            return false;
        ref.p = q;
        ((IRef*)q)->AddRef();
    } else if (type == 0x2f4e681c) {
        if (sub == 0x2f4e681b) {
            void* p = sub_f473a0(0x20, "RenderAsset", 0, 0, 0, 0);
            ref = p ? (void*)new (p) D765f10(0) : 0;
        } else {
            void* p = sub_f473a0(0x1c, "RenderAsset", 0, 0, 0, 0);
            ref = p ? (void*)new (p) ResE() : 0;
        }
    } else {
        return false;
    }
    if (ref.p) {
        *out = ref.p;
        ((IRef*)ref.p)->AddRef();
        ((IRef*)ref.p)->Release();
        return true;
    }
    return false;
}

// ===========================================================================
// @ 0x007668c0  cUnionType::Destroy
// ===========================================================================
struct CUnionTarget { void m(); };
void __cdecl UnionDestroy(void* p, int type) {
    if (type == 4) {
        ((CUnionTarget*)p)->m();
        return;
    }
    if (type == 3)
        return;
    if (type == 2) {
        ((CUnionTarget*)p)->m();
        return;
    }
    if (type == 1) {
        void* v = *(void**)((char*)p + 0x18);
        if (v)
            EA_Dealloc(v);
        *(void**)((char*)p + 0x18) = 0;
    }
}

// ===========================================================================
// @ 0x00766910  vector<uint32_t>::push_back
// ===========================================================================
struct VPtr {
    uint32_t* mpBegin;   // +0
    uint32_t* mpEnd;     // +4
    uint32_t* mpCap;     // +8
    void push_back(const uint32_t& v);
    void DoInsertValue(uint32_t* pos, const uint32_t& v);  // 0x6c1570
};
void VPtr::push_back(const uint32_t& v) {
    uint32_t* e = mpEnd;
    if (e < mpCap) {
        mpEnd = e + 1;
        if (e)
            *e = v;
        return;
    }
    DoInsertValue(e, v);
}

// ===========================================================================
// @ 0x00766950  vector<uint32_t>::insert(position, n, value)
// ===========================================================================
struct V4 {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    uint32_t* mpAlloc;   // +0x10
    void insert(uint32_t* position, uint32_t n, const uint32_t& value);
};
void V4::insert(uint32_t* position, uint32_t n, const uint32_t& value) {
    if ((uint32_t)(mpCap - mpEnd) < n) {
        uint32_t size = (uint32_t)(mpEnd - mpBegin);
        uint32_t cap = size * 2;
        if (size == 0)
            cap = 1;
        uint32_t need = size + n;
        if (need < cap)
            need = cap;
        uint32_t* nb = need ? (uint32_t*)sub_f473a0(need * 4, "Graphics", 0, 0, g_allocFile, 0xd1) : 0;
        uint32_t* p = (uint32_t*)memcpy_t(nb, mpBegin, (uint32_t)((char*)position - (char*)mpBegin));
        p = (uint32_t*)((char*)p + ((char*)position - (char*)mpBegin));
        for (uint32_t i = 0; i < n; i++)
            p[i] = value;
        uint32_t* r = (uint32_t*)memcpy_t(p + n, position, (uint32_t)((char*)mpEnd - (char*)position));
        uint32_t* ne = (uint32_t*)((char*)r + ((char*)mpEnd - (char*)position));
        if (mpBegin && mpBegin != mpAlloc)
            EA_Dealloc(mpBegin);
        mpBegin = nb;
        mpEnd = ne;
        mpCap = nb + need;
    } else if (n) {
        uint32_t v = value;
        uint32_t* end = mpEnd;
        uint32_t right = (uint32_t)(end - position);
        if (n < right) {
            uint32_t* edge = end - n;
            memcpy_t(end, edge, n * 4);
            mpEnd = end + n;
            memmove(end - (edge - position), position, (uint32_t)((char*)edge - (char*)position));
            for (uint32_t* p = position; p != position + n; ++p)
                *p = v;
        } else {
            for (uint32_t* p = end; p != end + (n - right); ++p)
                *p = v;
            mpEnd = end + (n - right);
            memcpy_t(mpEnd, position, (uint32_t)((char*)end - (char*)position));
            mpEnd += right;
            for (uint32_t* p = position; p != end; ++p)
                *p = v;
        }
    }
}

// ===========================================================================
// @ 0x00766b30  SP::cTerrainSphere::RequestPaintDecalsFromModels
// ===========================================================================
struct RefObj {
    virtual void AddRef();                    // +0x00
    virtual void Release();                   // +0x04
    virtual void r2();                        // +0x08
    virtual RefObj* GetCached(int key);       // +0x0c
    virtual void r4();                        // +0x10
    virtual void GetOut(RefObj** out);        // +0x14
};
struct AutoRefCount {
    RefObj* p;
    AutoRefCount() : p(0) {}
    ~AutoRefCount() { if (p) p->Release(); }
    AutoRefCount& operator=(RefObj* q) {
        RefObj* old = p;
        p = q;
        if (old) old->Release();
        return *this;
    }
};
struct RefVec {
    void* mpBegin;             // +0
    void* mpEnd;               // +4
    void* mpCap;               // +8
    void reserve(uint32_t n);              // 0x4e0880 (thiscall)
    void push_back(const AutoRefCount& v);      // 0x4b54b0 (thiscall)
};
struct IResMgr {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual bool m4(void* key, AutoRefCount* hA, AutoRefCount* hB, int, int, int, int, int);
};
struct NodeFC { int Type(); };                     // 0xfc7e50 (thiscall)
struct JobC {
    void AddWeakDependency(int t);                 // 0x6913c0 (thiscall)
    bool Continuation(void* fn, void* ctx);        // 0x68f9f0 (thiscall)
};
struct TerrainSphere {
    char pad0[0x100];
    RefObj* handle;            // +0x100
    RefVec vec;                // +0x104
    char pad1[0x19c - 0x110];
    bool RequestPaintDecalsFromModels(void* job);
};

bool TerrainSphere::RequestPaintDecalsFromModels(void* job) {
    char* s = (char*)this;
    vec.reserve((uint32_t)((*(int*)(s + 0x1a0) - *(int*)(s + 0x19c)) / 0xc));
    uint32_t have = (uint32_t)(((char*)vec.mpEnd - (char*)vec.mpBegin) >> 2);
    while (have < (uint32_t)((*(int*)(s + 0x1a0) - *(int*)(s + 0x19c)) / 0xc)) {
        if (handle != 0) {
            AutoRefCount local;
            handle->GetOut(&local.p);
            RefObj* old = handle;
            if (old) { handle = 0; old->Release(); }
            vec.push_back(local);
            if (local.p) sub_6ac0a0(2, local.p);
        } else {
            AutoRefCount hA;
            AutoRefCount hB;
            IResMgr* mgr = (IResMgr*)Manager67dcd0();
            bool ok = mgr->m4(s + 0x19c + have * 0xc, &hA, &hB, 0, 0, 0, 0, 0);
            if (!ok) {
                hA = (RefObj*)0;
                hB = (RefObj*)0;
            }
            RefObj* got = hA.p ? hA.p->GetCached(0x3a212ac) : 0;
            RefObj* old = handle;
            if (got != old) {
                if (got) got->AddRef();
                handle = got;
                if (old) old->Release();
            }
            if (hB.p == 0 && handle != 0) {
                int t = ((NodeFC*)handle)->Type();
                ((JobC*)job)->AddWeakDependency(t);
                return ((JobC*)job)->Continuation((void*)0x767340, this);
            }
            vec.push_back(hB);
            if (hB.p) sub_6ac0a0(2, hB.p);
        }
        have = (uint32_t)(((char*)vec.mpEnd - (char*)vec.mpBegin) >> 2);
    }
    return true;
}

// ===========================================================================
// @ 0x00766e10  read a paint-decal block
// ===========================================================================
struct IStream {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void sA(); virtual void sB();
    virtual int  sC(void* dst, int n);          // slot 0xc
};
struct Vec3Vec {
    void reserve(uint32_t n);          // 0x41e4d0 (thiscall)
    void push_back(const int* v);      // 0x4e19a0 (thiscall)
};
struct Reader {
    char pad0[0x28];
    IStream* mStream;         // +0x28
    int mField2c;             // +0x2c
    char pad1[0x19c - 0x30];
    Vec3Vec vec;              // +0x19c
    bool ReadDecalBlock(int unused);
};
extern "C" {
bool __cdecl ReadTriplet763340(IStream* s, int* p, int io);   // 0x763340
}
bool Reader::ReadDecalBlock(int /*unused*/) {
    if (mStream->sC(&mField2c, 4) != 4)
        return false;
    uint32_t count = (uint32_t)mField2c;
    if (count < 8)
        return false;
    if (count > 9)
        return false;
    uint32_t num;
    IStream* stream = mStream;
    if (!ReadInt32(stream, &num, 1, 0))
        return false;
    vec.reserve(num);
    for (uint32_t i = 0; i < num; i++) {
        int v[3] = {0, 0, 0};
        IStream* s2 = mStream;
        if (!ReadTriplet763340(s2, v, 0))
            return false;
        vec.push_back(v);
    }
    return true;
}

// ===========================================================================
// @ 0x00766ed0  SP::cGraphicsResourceFactory::CreateResource
// ===========================================================================
struct IFactorySrc {
    virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
    virtual void* f4();   // +0x10
};
struct Factory {
    char pad[0x8];
    virtual void g0(); virtual void g1(); virtual void g2(); virtual void g3();
    virtual void g4(); virtual void g5();
    virtual void g6(); virtual void g7(); virtual void g8(); virtual void g9();
    virtual bool g9call(int* src, void* res, int a, int b);   // +0x24
    bool CreateResource(int* src, void** out, int a, int b);
};
bool Factory::CreateResource(int* src, void** out, int a, int b) {
    void* local = 0;
    int* tmp = (int*)((IFactorySrc*)src)->f4();
    CreateByType(&local, (uint32_t)b, *(int*)((char*)tmp + 4));
    if (local) {
        if (this->g9call(src, local, a, b)) {
            *out = local;
            ((void(__thiscall**)(void*))VP(local))[0](local);
            ((void(__thiscall**)(void*))VP(local))[1](local);
            return true;
        }
    }
    if (local)
        ((void(__thiscall**)(void*))VP(local))[1](local);
    return false;
}
