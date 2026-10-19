// Slice s007819d0: EASTL vector<12-byte> and vector<36-byte> machinery for the
// cShadowWorld editor/simulator object (0x7819d0..0x78285b), plus two member helpers.
// /O2 /MD /Gy /EHsc /TP module.  Element sizes: 0xc and 0x24.
#include "types.h"
#include <intrin.h>
#include <stddef.h>

// ---------------------------------------------------------------------------
// Reference-counted interface.  AddRef is vtable slot 0, Release slot 1.
// ---------------------------------------------------------------------------
struct IRefObj {
    virtual void AddRef();
    virtual void Release();
};

// placement new / delete (vector element construction in place)
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

// ---------------------------------------------------------------------------
// 12-byte vector element: refcounted pointer + two ints.
// ---------------------------------------------------------------------------
struct E12 {
    IRefObj* p;
    int      a;
    int      b;

    E12() {}
    E12(const E12& o) { p = o.p; if (p) p->AddRef(); a = o.a; b = o.b; }
    E12(IRefObj* pp, int aa, int bb) { p = pp; if (p) p->AddRef(); a = aa; b = bb; }
    ~E12() { if (p) p->Release(); }
};

// ---------------------------------------------------------------------------
// EASTL vector of E12.
// ---------------------------------------------------------------------------
struct Vec12 {
    E12* begin;                     // +0x0
    E12* end;                       // +0x4
    E12* cap;                       // +0x8

    __declspec(noinline) Vec12* Assign(const Vec12& src);           // 0x00782270
    __declspec(noinline) void   Destroy();                          // 0x00781b10
    __declspec(noinline) Vec12* ConstructRange(const Vec12& src);   // 0x00781a60
    __declspec(noinline) void   push_back(const E12& value);        // 0x00782540

    E12*  Allocate(unsigned n, E12* first, E12* last);              // 0x007809f0
    void  DestroyRange(E12* first, E12* last);                      // 0x007809c0
    void  InsertAux(E12* pos, const E12& value);                    // 0x00760ca0
};

// ---------------------------------------------------------------------------
// 36-byte vector element: refcounted ptr + Vec12 + int/bool/int.
// ---------------------------------------------------------------------------
// By-value block used by the E36 two-argument constructor (0x781c30); its first
// 0xc bytes are a Vec12 and it is non-trivially destructible (destroys that Vec12).
struct E36Part {
    Vec12 v;                        // +0x00
    char  pad_0c[8];                // +0x0c
    int   a;                        // +0x14
    bool  b;                        // +0x18
    int   c;                        // +0x1c
    ~E36Part() { v.Destroy(); }
};

struct E36 {
    void* p0;                       // +0x00
    Vec12 v;                        // +0x04
    char  pad_10[8];                // +0x10
    int   a;                        // +0x18
    bool  b;                        // +0x1c
    int   c;                        // +0x20
    E36*  Construct(void* p0a, E36Part src);   // 0x00781c30 (thiscall)
};

// ---------------------------------------------------------------------------
// Sub-object that owns the two vectors (lives at cShadowWorld + 8).
// ---------------------------------------------------------------------------
struct cSWsub {
    void* vtbl;                     // +0x00
    char  pad04[0x10];              // +0x04
    Vec12 mVec;                     // +0x14
    char  pad20[8];                 // +0x20
    E36*  mE36b;                    // +0x28
    E36*  mE36e;                    // +0x2c
    E36*  mE36c;                    // +0x30
    char  pad34[0x1c4 - 0x34];      // +0x34
    bool  mFlag1c4;                 // +0x1c4
    char  pad1c5[0x21c - 0x1c5];    // +0x1c5
    int   mInt21c;                  // +0x21c
    int   mInt220;                  // +0x220
    int   mInt224;                  // +0x224

    void FUN_007824e0();                            // pop_back-like
    void FUN_007825d0(void* obj, unsigned flag);    // emplace via virtual fetch
    void FUN_00782660(void* obj, unsigned flag);    // emplace a fresh 16-byte object
    void FUN_00782740(void* obj, unsigned flag);    // emplace from a refcounted object
};

// 16-byte helper object allocated by 0x782660.  It is a multiply-derived
// polymorphic type: an empty primary base (vptr at +0), a refcounted secondary
// base at +4 (vptr at +4, n8 at +8) and its own int at +0xc.  It carries a class
// specific operator new that forwards to the EASTL allocator.
void* EastlAllocate(unsigned int size, const char* name, int a, int b, const char* file, int line);
struct Obj10Primary {
    virtual void p0();
    virtual void p1();
};
struct Obj10RefCounted {
    virtual void r0();
    virtual void r1();
    int n8;
    Obj10RefCounted() : n8(0) {}
    virtual ~Obj10RefCounted();
};
struct Obj10 : Obj10Primary, Obj10RefCounted {
    virtual void d0();
    virtual void d1();
    int nc;
    Obj10(int v) { nc = v; }
    virtual ~Obj10();
    static void* operator new(size_t s) { return EastlAllocate(s, "Graphics", 0, 0, 0, 0); }
};

// ---------------------------------------------------------------------------
// externals
// ---------------------------------------------------------------------------
void* EastlAllocate(unsigned int size, const char* name, int a, int b, const char* file, int line);
void  EastlFree(void* p);
void  FUN_0077fa70(void* out, void* first, void* last, void* dst, void* extra);
void* FUN_00760ba0(void* first, void* last, void* dst);
void  FUN_00743b50(void* p);
void  FUN_00576620(void* p);
void __fastcall FUN_0077f6a0(void* self);
void  FUN_00777ae0(int a, int b, int c);
void  FUN_00780810(void* self);
void  FUN_0077f980(void* self);
void  FUN_007806a0(void* self);
void  FUN_00780ab0(void* self);

struct Sub14 { void FreeRange(void* a, void* b); };
struct ShadowBase { void Notify(); };
void  FUN_Memset(void* dst, int val, unsigned size);        // 0x11e073e
__declspec(noinline) void __fastcall FUN_00781CF0(void* v);  // E36 vector destroy

// CRT array constructor/destructor iterators (??_L / ??_M), __stdcall.
void __stdcall EhVecCtorIterator(void* p, unsigned elemSize, int count,
                                 void (*ctor)(void*), void (*dtor)(void*));
void __stdcall EhVecDtorIterator(void* p, unsigned elemSize, int count,
                                 void (*dtor)(void*));

extern float g_153a130, g_153a134, g_153a138;
extern float g_1633bd0, g_1633bd4, g_1633bd8;
extern float g_1470f1c, g_1485720, g_1486110;
extern float g_13ef61c, g_13ec4d0, g_13eb1bc, g_1488874;

// ============================================================================
// 0x007819D0 : conditional apply/notify on the shadow sub-object
// ============================================================================
struct ShadowSub {
    char pad0[4];
    char mUnk4;
    char mUnk5;
    char mUnk6;
    char pad7[1];
    int  mUnk8;
    char pad_c[4];
    int  mUnk10;
    char pad_14[0x1bc - 0x14];
    bool mUnk1bc;
    void TryApply(int other);
};

// @ 0x007819d0
void ShadowSub::TryApply(int other)
{
    ShadowSub* self = this;
    if (self->mUnk8 != 0)
        return;
    if (self->mUnk10 != 0 && other == self->mUnk10 && self->mUnk5 && self->mUnk4 && self->mUnk6) {
        FUN_00777ae0(0x20a, 0, 0);
        FUN_00777ae0(0x20b, 0, 0);
        FUN_00777ae0(0x223, (int)self + 0x3c, 1);
        if (self->mUnk1bc) {
            FUN_00780810((char*)self - 8);
            return;
        }
        FUN_0077f980((char*)self - 8);
        return;
    }
    FUN_00777ae0(0x223, 0, 0);
}

// ============================================================================
// 0x00781A60 : Vec12 copy-range construction
// ============================================================================
// @ 0x00781a60
Vec12* Vec12::ConstructRange(const Vec12& src)
{
    int count = (int)(src.end - src.begin) / 0xc;
    E12* buf;
    if (count == 0)
        buf = 0;
    else
        buf = (E12*)EastlAllocate(count * 0xc, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    begin = buf;
    end = buf;
    cap = (E12*)((char*)buf + count * 0xc);
    void* tmp = 0;
    FUN_0077fa70(&tmp, src.begin, src.end, buf, (void*)&src);
    end = (E12*)tmp;
    return this;
}

// ============================================================================
// 0x00781B10 : Vec12 destroy (release every element, then free the block)
// ============================================================================
// @ 0x00781b10
void Vec12::Destroy()
{
    E12* p = begin;
    E12* e = end;
    for (; p < e; p = (E12*)((char*)p + 0xc)) {
        if (p->p)
            p->p->Release();
    }
    if (begin && *(int*)((char*)begin - 4) != 0)
        EastlFree(begin);
}

// ============================================================================
// 0x00781B80 : copy-construct an E36 range into uninitialised storage
// ============================================================================
// @ 0x00781b80
E36* Func_00781B80(E36* first, E36* last, E36* dst)
{
    while (first != last) {
        if (dst) {
            dst->p0 = first->p0;
            dst->v.ConstructRange(first->v);
            dst->a = first->a;
            dst->b = first->b;
            dst->c = first->c;
        }
        first = (E36*)((char*)first + 0x24);
        dst = (E36*)((char*)dst + 0x24);
    }
    return dst;
}

// ============================================================================
// 0x00781C30 : E36 two-argument constructor (p0 + by-value block)
// ============================================================================
// @ 0x00781c30
E36* E36::Construct(void* p0a, E36Part src)
{
    p0 = p0a;
    v.ConstructRange(src.v);
    a = src.a;
    b = src.b;
    c = src.c;
    return this;
}

// ============================================================================
// 0x00781CB0 : destroy an E36 range
// ============================================================================
// @ 0x00781cb0
E36* Func_00781CB0(E36* first, E36* last, E36* dst)
{
    while (first != last) {
        first->v.Destroy();
        first = (E36*)((char*)first + 0x24);
        dst = (E36*)((char*)dst + 0x24);
    }
    return dst;
}

// ============================================================================
// 0x00781CF0 : destroy an E36 vector (elements + block)
// ============================================================================
// @ 0x00781cf0
__declspec(noinline) void __fastcall FUN_00781CF0(void* v)
{
    char* begin = *(char**)v;
    char* end = *(char**)((char*)v + 4);
    for (; begin < end; begin += 0x24)
        ((Vec12*)(begin + 4))->Destroy();
    begin = *(char**)v;
    if (begin && *(int*)(begin - 4) != 0)
        EastlFree(begin);
}

// ---------------------------------------------------------------------------
// Refcounted slot at +8: decrement, and if it would drop below one, restore it.
// (Reproduces the inlined lock xadd sequence of the original.)
// ---------------------------------------------------------------------------
static void DecRefOrRestore(void* obj)
{
    long* rc = (long*)((char*)obj + 8);
    _InterlockedExchangeAdd(rc, -1);
    if (_InterlockedExchangeAdd(rc, 0) < 1)
        _InterlockedExchangeAdd(rc, 1);
}

// ============================================================================
// 0x00781D60 : cShadowWorld constructor
// ============================================================================
struct cShadowWorld {
    void*   vtbl;                   // +0x000
    int     refcount;               // +0x004
    void*   vtbl2;                  // +0x008
    unsigned char b0c, b0d, b0e, b0f;   // +0x00c
    void*   p10;                    // +0x010
    int     u14;                    // +0x014
    IRefObj* p18;                   // +0x018
    Vec12   vec1c;                  // +0x01c
    int     u28;                    // +0x028
    int     u2c;                    // +0x02c
    E36*    e36b;                   // +0x030
    E36*    e36e;                   // +0x034
    E36*    e36c;                   // +0x038
    int     u3c;                    // +0x03c
    int     u40;                    // +0x040
    char    arr44[0xa4];            // +0x044
    int     ue8;                    // +0x0e8
    int     uec;                    // +0x0ec
    int     uf0;                    // +0x0f0
    void*   rastA[2];               // +0x0f4
    int     iafc[4];                // +0x0fc
    void*   rastB[8];               // +0x10c
    int     ib12c[16];              // +0x12c
    float   f16c, f170, f174, f178, f17c, f180, f184, f188, f18c;
    float   f190, f194, f198, f19c, f1a0, f1a4, f1a8, f1ac, f1b0, f1b4, f1b8;
    int     i1bc;                   // +0x1bc
    int     i1c0;                   // +0x1c0
    bool    b1c4;                   // +0x1c4
    char    pad1c5[3];
    float   f1c8, f1cc, f1d0, f1d4, f1d8;
    int     i1dc;                   // +0x1dc
    void*   p1e0;                   // +0x1e0
    int     i1e4;                   // +0x1e4
    void*   p1e8;                   // +0x1e8
    int     i1ec;                   // +0x1ec
    void*   p1f0;                   // +0x1f0
    int     i1f4;                   // +0x1f4
    void*   p1f8;                   // +0x1f8
    int     i1fc;                   // +0x1fc
    void*   p200;                   // +0x200
    float   f204, f208, f20c, f210, f214, f218, f21c;
    int     i220;                   // +0x220
    int     i224;                   // +0x224
};

// @ 0x00781d60
cShadowWorld* cShadowWorld_ctor(cShadowWorld* p)
{
    p->refcount = 0;
    p->vtbl2 = (void*)0x1444e90;
    p->vtbl = (void*)0x140e9fc;
    p->vtbl2 = (void*)0x140e9a8;
    p->b0c = 0;
    p->b0d = 0;
    p->b0e = 0;
    p->p10 = 0;
    p->p18 = 0;
    p->vec1c.begin = 0;
    p->vec1c.end = 0;
    p->vec1c.cap = 0;
    p->e36b = 0;
    p->e36e = 0;
    p->e36c = 0;

    FUN_Memset(p->arr44, 0, 0xa4);
    p->ue8 = 0;
    p->uec = -1;
    p->uf0 = -1;
    EhVecCtorIterator(p->rastA, 4, 2, &FUN_00743b50, &FUN_00576620);
    p->iafc[0] = -1;
    p->iafc[1] = -1;
    p->iafc[2] = -1;
    p->iafc[3] = -1;
    EhVecCtorIterator(p->rastB, 4, 8, &FUN_00743b50, &FUN_00576620);
    for (int i = 0; i < 16; ++i)
        p->ib12c[i] = -1;

    p->f16c = g_153a130;  p->f170 = g_153a134;  p->f174 = g_153a138;
    p->f178 = g_153a130;  p->f17c = g_153a134;  p->f180 = g_153a138;
    p->f184 = g_1633bd0;  p->f188 = g_1633bd4;  p->f18c = g_1633bd8;
    p->f190 = g_153a130;  p->f194 = g_153a134;  p->f198 = g_153a138;
    p->f19c = g_1633bd0;  p->f1a0 = g_1633bd4;  p->f1a4 = g_1633bd8;
    p->f1a8 = g_1470f1c;  p->f1ac = g_1485720;
    p->f1b0 = g_1633bd0;  p->f1b4 = g_1633bd4;  p->f1b8 = g_1633bd8;
    p->i1bc = 0;
    p->i1c0 = 0;
    p->b1c4 = false;
    p->f1c8 = g_1486110;  p->f1cc = g_13ec4d0;
    p->f1d0 = 0.0f;       p->f1d4 = 0.0f;
    p->f1d8 = 0.0f;
    p->i1dc = 2;
    p->p1e0 = (void*)0x140e8fc;
    p->i1e4 = 2;
    p->p1e8 = (void*)0x140e904;
    p->i1ec = 1;
    p->p1f0 = (void*)0x140e90c;
    p->i1f4 = 1;
    p->p1f8 = (void*)0x140e910;
    p->i1fc = 1;
    p->p200 = (void*)0x140e914;
    p->f204 = g_13ef61c;
    p->f208 = g_1485720;
    p->f20c = g_13eb1bc;
    p->f210 = g_1485720;
    p->f214 = g_1488874;
    p->f218 = g_1485720;
    p->f21c = 0.0f;
    p->i220 = 1;
    p->i224 = 0;

    for (int i = 0; i < 2; ++i) {
        if (p->rastA[i])
            DecRefOrRestore(p->rastA[i]);
        for (int j = 0; j < 2; ++j) {
            int idx = i * 4 + j;
            if (p->rastB[idx])
                DecRefOrRestore(p->rastB[idx]);
        }
    }
    return p;
}

// ============================================================================
// 0x007821B0 : cShadowWorld destructor
// ============================================================================
// @ 0x007821b0
void cShadowWorld_dtor(cShadowWorld* p)
{
    IRefObj* r1bc = *(IRefObj**)&p->i1bc;
    if (r1bc)
        r1bc->Release();

    EhVecDtorIterator(p->rastB, 4, 8, &FUN_00576620);
    EhVecDtorIterator(p->rastA, 4, 2, &FUN_00576620);
    FUN_00781CF0(&p->e36b);
    p->vec1c.Destroy();
    if (p->p18)
        p->p18->Release();

    p->vtbl = (void*)0x13ef094;
    p->vtbl2 = (void*)0x13eb938;
}

// ============================================================================
// 0x00782270 : Vec12 assignment
// ============================================================================
// @ 0x00782270
Vec12* Vec12::Assign(const Vec12& src)
{
    if (&src == this)
        return this;

    unsigned newCount = (unsigned)(src.end - src.begin) / 0xc;
    E12* oldBegin = begin;

    if ((unsigned)(cap - begin) / 0xc < newCount) {
        E12* fresh = Allocate(newCount, src.begin, src.end);
        DestroyRange(begin, end);
        if (begin && *(int*)((char*)begin - 4) != 0)
            EastlFree(begin);
        cap = (E12*)((char*)fresh + newCount * 0xc);
        begin = fresh;
        end = (E12*)((char*)fresh + newCount * 0xc);
        return this;
    }

    unsigned oldCount = (unsigned)(end - oldBegin) / 0xc;
    if (oldCount < newCount) {
        FUN_00760ba0(src.begin, (E12*)((char*)src.begin + oldCount * 0xc), oldBegin);
        void* srcEnd = src.end;
        void* tmp = 0;
        FUN_0077fa70(&tmp, (E12*)((char*)src.begin + ((char*)end - (char*)begin)),
                     srcEnd, end, srcEnd);
        end = (E12*)((char*)begin + newCount * 0xc);
        return this;
    }

    void* fresh = FUN_00760ba0(src.begin, src.end, oldBegin);
    DestroyRange((E12*)fresh, end);
    end = (E12*)((char*)begin + newCount * 0xc);
    return this;
}

// ============================================================================
// 0x00782420 : copy-assign an E36 range into initialised storage
// ============================================================================
// @ 0x00782420
E36* Func_00782420(E36* first, E36* last, E36* dst)
{
    while (first != last) {
        dst->p0 = first->p0;
        dst->v.Assign(first->v);
        dst->a = first->a;
        dst->b = first->b;
        dst->c = first->c;
        first = (E36*)((char*)first + 0x24);
        dst = (E36*)((char*)dst + 0x24);
    }
    return dst;
}

// ============================================================================
// 0x00782470 : move-assign an E36 range backwards
// ============================================================================
// @ 0x00782470
E36* Func_00782470(E36* first, E36* last, E36* dst)
{
    while (last != first) {
        last = (E36*)((char*)last - 0x24);
        dst = (E36*)((char*)dst - 0x24);
        dst->p0 = last->p0;
        dst->v.Assign(last->v);
        dst->a = last->a;
        dst->b = last->b;
        dst->c = last->c;
    }
    return dst;
}

// ============================================================================
// 0x007824E0 : pop_back-like member helper
// ============================================================================
// @ 0x007824e0
void cSWsub::FUN_007824e0()
{
    E36* last = (E36*)((char*)mE36e - 0x24);
    ((void(__thiscall*)(void*, void*))((void**)(*(void**)this))[0x10 / 4])(this, last->p0);
    mVec.Assign(last->v);
    mInt21c = last->a;
    ((void(__thiscall*)(void*, int))((void**)(*(void**)this))[0x14 / 4])(this, last->c);
    ((void(__thiscall*)(void*, int))((void**)(*(void**)this))[0x28 / 4])(this, last->b);
    FUN_0077f6a0((char*)this - 8);
    mE36e = (E36*)((char*)mE36e - 0x24);
    mE36e->v.Destroy();
}

// ============================================================================
// 0x00782540 : Vec12::push_back(const E12&)
// ============================================================================
// @ 0x00782540
void Vec12::push_back(const E12& value)
{
    if (end < cap) {
        new (end++) E12(value);
    } else {
        InsertAux(end, value);
    }
}

// ============================================================================
// 0x007825D0 : emplace at end from a virtual fetch
// ============================================================================
// @ 0x007825d0
void cSWsub::FUN_007825d0(void* obj, unsigned flag)
{
    unsigned f = flag | 0x11d00;
    IRefObj* p = (IRefObj*)((void*(__thiscall*)(void*))((void**)(*(void**)obj))[0x13c / 4])(obj);
    E12 tmp(p, (int)f, (int)f);
    mVec.push_back(tmp);
}

// ============================================================================
// 0x00782660 : emplace a freshly allocated 16-byte object
// ============================================================================
// @ 0x00782660
void cSWsub::FUN_00782660(void* obj, unsigned flag)
{
    Obj10* p = new Obj10(((int(__thiscall*)(void*))((void**)(*(void**)obj))[0xa0 / 4])(obj));
    E12 tmp((IRefObj*)p, (int)flag, (int)(flag | 0x40000));
    mVec.push_back(tmp);
}

// ============================================================================
// 0x00782740 : emplace from an existing refcounted object
// ============================================================================
// @ 0x00782740
void cSWsub::FUN_00782740(void* obj, unsigned flag)
{
    E12 tmp((IRefObj*)obj, (int)flag, (int)flag);
    mVec.push_back(tmp);
}

// ============================================================================
// 0x007827C0 : clear + notify
// ============================================================================
// @ 0x007827c0
void __fastcall Func_007827C0(int param_1)
{
    int* p = *(int**)(param_1 + 0x10);
    if (p) {
        *(int*)(param_1 + 0x10) = 0;
        ((IRefObj*)p)->Release();
    }
    ((Sub14*)(param_1 + 0x14))->FreeRange(*(void**)(param_1 + 0x14), *(void**)(param_1 + 0x18));
    ((ShadowBase*)(param_1 - 8))->Notify();
}

// ============================================================================
// 0x00782800 : insert a range of E36 into the vector
// ============================================================================
// @ 0x00782800
char* Func_00782800(char* self, char* first, char* last)
{
    char* dst = (char*)Func_00782420((E36*)last, *(E36**)(self + 4), (E36*)first);
    char* end = *(char**)(self + 4);
    for (; dst < end; dst += 0x24)
        ((Vec12*)(dst + 4))->Destroy();
    int n = (int)((last - first) * -0x38e38e39LL >> 32);
    *(int*)(self + 4) += ((n >> 3) - (n >> 0x1f)) * 0x24;
    return first;
}
