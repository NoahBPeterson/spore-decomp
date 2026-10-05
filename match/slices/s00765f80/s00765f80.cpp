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
void* __cdecl EA_Alloc6(uint32_t size, const char* name, int a, int b, const char* file, int line);
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
// 0x006ac040 : SetCachingType
void  __cdecl SetCachingType(int a, void* b);
// 0x0067dcc0 / 0x0067dcd0 : managers
void* __cdecl MessageServer();
void* __cdecl Manager67dcd0();
// 0x0093a780 : EA::IO::ReadInt32
bool  __cdecl ReadInt32(void* stream, void* dst, int count, int flags);
// 0x004b54b0 / 0x006ac0a0 : ref-vector push / SetCachingType-like
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
struct Elem8 {
    void* p;
    int   x;
    Elem8() : p(0), x(0) {}
    ~Elem8() {}
};
struct ResD {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
    virtual ~ResD();
    int mRef;                 // +0x4
    int m08, m0c, m10, m14;   // +0x8..+0x14
    void* mArena;             // +0x18
    Elem8* mpBegin;           // +0x20
    Elem8* mpEnd;             // +0x24
    Elem8* mpCap;             // +0x28
    ResD();
};
ResD::ResD() : mRef(0), m08(0), m0c(0), m10(0), m14(0), mArena(0),
               mpBegin(0), mpEnd(0), mpCap(0) {
    Elem8 tmp[4];
    (void)tmp;
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
struct IPngArg {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    char pad[0x18];
    void* mMgr;               // +0x1c (approx)
};
struct PngArg {
    char pad[0x8];
    IPngArg* p08;             // +0x8
};
bool __stdcall PNGWriteCallback(PngArg* arg) {
    unsigned char* buf = (unsigned char*)_alloca(0x2a70);
    (void)buf;
    IPngArg* a = arg->p08;
    void* inner = *(void**)((char*)a + 0xc);
    int c1c = *(int*)((char*)inner + 0x1c);
    void* c20 = *(void**)((char*)inner + 0x20);
    void* ctx = 0;
    (void)c1c; (void)c20;
    if (*(char*)((char*)a + 0x18)) {
        // formatted debug string path (stubbed)
    }
    sub_87cf40(&ctx);
    void* m = *(void**)((char*)a + 0x10);
    int v = ((int(__thiscall**)(void*))VP(m))[0x18 / 4](m);
    sub_87cf60(&ctx, v);
    bool ok = sub_87d2a0(&ctx, 1, 4);
    if (ok) {
        ok = sub_87d030(&ctx, *(void**)((char*)inner + 0x28), *(int*)((char*)arg + 0x44) * 4) != 0;
        sub_87cff0(&ctx);
        m = *(void**)((char*)a + 0x10);
        ((void(__thiscall**)(void*))VP(m))[0x24 / 4](m);
        void* srv = MessageServer();
        if (srv && *(void**)((char*)a + 0x14))
            ((void(__thiscall**)(void*, void*, int, int, int))VP(srv))[0x18 / 4](
                srv, *(void**)((char*)a + 0x14), 0, 0, 0);
    }
    sub_87d260(&ctx);
    return ok;
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
void* __cdecl Ctor765f10(void* p);   // 0x765f10
void* __cdecl Ctor763100(void* p);   // 0x763100
void* __cdecl Ctor7004d0(void* p);   // 0x7004d0
void* __cdecl NewList7639(void* p);  // (unused)
}
// local ctors (defined in this slice)
void* InitResB(void* p);
void* InitResE(void* p);

bool __stdcall CreateByType(void** out, uint32_t type, int sub) {
    void* obj = 0;
    if (type < 0x2cb4f30) {
        if (type == 0x2f4e681b) {
            void* p = EA_Alloc6(0x3fe4, "RenderAsset", 0, 0, 0, 0);
            if (p) {
                // cPropertyList base ctor + derived vtable
                *(void**)p = (void*)0x13ebcdc;
                _InterlockedExchange((volatile long*)((char*)p + 4), 0);
                *(int*)((char*)p + 8) = 0;
                *(int*)((char*)p + 0xc) = 0;
                *(int*)((char*)p + 0x10) = 0;
                *(int*)((char*)p + 0x14) = 0;
                // (large body stubbed)
                obj = p;
            }
        } else if (type == 0x2cb4f2f) {
            void* p = EA_Alloc6(0x140, "RenderAsset", 0, 0, 0, 0);
            if (p) obj = Ctor7004d0(p);
        } else if (type == 0x1c135da) {
            void* p = EA_Alloc6(0x2c, "RenderAsset", 0, 0, 0, 0);
            if (p) obj = Ctor763100(p);
        }
    } else if (type == 0x2f4e681b) {
        // unreachable by ordering
    } else if (type == 0x2f4e681c) {
        if (sub == 0x2f4e681b) {
            void* p = EA_Alloc6(0x20, "RenderAsset", 0, 0, 0, 0);
            if (p) obj = Ctor765f10(p);
        } else {
            void* p = EA_Alloc6(0x1c, "RenderAsset", 0, 0, 0, 0);
            if (p) obj = InitResE(p);
        }
    }
    if (obj) {
        *out = obj;
        ((void(__thiscall**)(void*))VP(obj))[0](obj);   // AddRef
        ((void(__thiscall**)(void*))VP(obj))[1](obj);   // Release
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
        uint32_t* nb = need ? (uint32_t*)EA_Alloc6(need * 4, "Graphics", 0, 0, g_allocFile, 0xd1) : 0;
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
struct IResMgr {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual bool m4(void* key, void** outA, void** outB, int, int, int, int, int);
};
struct ResHandle { virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3(); };

bool RequestPaintDecalsFromModels(void* self, void* job) {
    char* s = (char*)self;
    // reserve
    sub_4e0880(s + 0x104, (uint32_t)((*(int*)(s + 0x1a0) - *(int*)(s + 0x19c)) / 0xc));
    uint32_t have = (uint32_t)((*(int*)(s + 0x108) - *(int*)(s + 0x104)) >> 2);
    uint32_t want = (uint32_t)((*(int*)(s + 0x1a0) - *(int*)(s + 0x19c)) / 0xc);
    while (have < want) {
        if (*(void**)(s + 0x100) == 0) {
            IResMgr* mgr = (IResMgr*)Manager67dcd0();
            ResHandle* hA = 0;
            ResHandle* hB = 0;
            bool ok = ((IResMgr*)mgr)->m4(s + 0x19c + have * 0xc, (void**)&hA, (void**)&hB, 0, 0, 0, 0, 0);
            if (!ok) {
                if (hA) { hA->h1(); hA = 0; }
                if (hB) { hB->h1(); hB = 0; }
            }
            ResHandle* got = hA ? (ResHandle*)((int(__thiscall**)(ResHandle*, int))VP(hA))[0xc / 4](hA, 0x3a212ac) : 0;
            ResHandle* old = *(ResHandle**)(s + 0x100);
            if (got != old) {
                if (got) got->h0();
                *(ResHandle**)(s + 0x100) = got;
                if (old) old->h1();
            }
            if (hB == 0 && *(void**)(s + 0x100) != 0) {
                // continuation
                sub_4b54b0(&hB);
                if (hB) sub_6ac0a0(2, hB);
                if (hB) hB->h1();
                if (hA) hA->h1();
                return true;
            }
            sub_4b54b0(&hB);
            if (hB) sub_6ac0a0(2, hB);
            if (hA) hA->h1();
        } else {
            ResHandle* local = 0;
            ((void(__thiscall**)(ResHandle*, ResHandle**))VP(*(void**)(s + 0x100)))[0x14 / 4](
                *(ResHandle**)(s + 0x100), &local);
            ResHandle* old = *(ResHandle**)(s + 0x100);
            if (old) { *(void**)(s + 0x100) = 0; old->h1(); }
            sub_4b54b0(&local);
            if (local) sub_6ac0a0(2, local);
            if (local) local->h1();
        }
        have = (uint32_t)((*(int*)(s + 0x108) - *(int*)(s + 0x104)) >> 2);
    }
    return true;
}
extern "C" void __cdecl sub_4e0880(void* vec, uint32_t n);

// ===========================================================================
// @ 0x00766e10  read a paint-decal block
// ===========================================================================
struct IStream {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void sA(); virtual void sB();
    virtual int  sC(void* dst, int n);          // slot 0xc
};
struct Reader { IStream* mStream; int mField2c; };
extern "C" {
bool __cdecl ReadTriplet763340(IStream* s, int* p, int io);   // 0x763340
void __cdecl VecReserve41e4d0(void* vec, int n);               // 0x41e4d0
void __cdecl PushDeclareParam(void* vec, int* v);              // 0x4e19a0
}
bool __fastcall ReadDecalBlock(Reader* r) {
    int n = r->mStream->sC(&r->mField2c, 4);
    if (n != 4)
        return false;
    int count = r->mField2c;
    if (count < 8 || count > 9)
        return false;
    int num = 0;
    if (!ReadInt32(r->mStream, &num, 1, 0))
        return false;
    VecReserve41e4d0((char*)r + 0x19c, num);
    for (int i = 0; i < num; i++) {
        int v[3] = {0, 0, 0};
        if (!ReadTriplet763340(r->mStream, v, 0))
            return false;
        PushDeclareParam((char*)r + 0x19c, v);
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
