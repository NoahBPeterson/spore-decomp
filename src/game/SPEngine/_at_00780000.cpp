// src/game/SPEngine/_at_00780000.cpp -- migrated from slice(s) s00782860, s007819d0, s0077ff30 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_00780000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern int g_Unk153a2e8;
extern int   g_16fa3a8;
extern int   g_16f954c, g_16f9550, g_16f9558, g_16f955c;
extern int   g_16f966c, g_16f9670, g_16f9678, g_16f967c, g_16f9680;
extern int   g_16fa168, g_16fa16c, g_16fa164;
extern int   g_16fa1a0, g_16fa19c, g_16fa1a4;
extern int   g_16fa248, g_16fa244, g_16fa24c;
extern int   g_16fa210, g_16fa20c, g_16fa214;
extern float g_140e8f8;
#include <intrin.h>
#include <stddef.h>
#include <math.h>
#pragma intrinsic(_InterlockedExchangeAdd)

// ---- items of slice s0077ff30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cPropertyList {
    bool GetDescription(uint32_t key);
};
struct Raster {
    int mField0;                    // +0x0 (raster handle / vtable word)
};
struct RectID { int a; int b; };
struct cShadowWorld;
Raster* CreateRaster(int w, int h, int a, int b, int c);
void    GetImageResource(void* r);
int*    Property_GetInt(void* prop);
void*   FUN_0077f040(cShadowWorld* owner, int a, bool b, int c);
void*   EastlAllocate(unsigned int size, const char* name, int a, int b, int c, int d);
struct cShadowWorld {
    void** vftable;                 // +0x000
    int    mRefCount;               // +0x004
    char   pad_008[5];              // +0x008
    bool   mUnkD;                   // +0x00d
    char   pad_00e[2];
    void*  mLightingWorld;          // +0x010
    bool   mUnk14;                  // +0x014
    bool   mUnk15;                  // +0x015
    char   pad_016[0x044 - 0x016];
    int    mUnk44;                  // +0x044
    char   pad_048[0x0e8 - 0x048];
    Raster* mShadowDB;              // +0x0e8
    char   pad_0ec[0x0f4 - 0x0ec];
    Raster* mShadowMaps[2];         // +0x0f4
    RectID  mShadowMapRectIDs[2];   // +0x0fc
    Raster* mShadowBasisMaps[2][4]; // +0x10c
    RectID  mShadowBasisMapRectIDs[2][4]; // +0x12c
    char   pad_16c[0x1ac - 0x16c];
    float  mUnk1ac;                 // +0x1ac
    char   pad_1b0[0x1bc - 0x1b0];
    void*  mRenderShadow;           // +0x1bc
    int    mUnk1c0;                 // +0x1c0
    bool   mUnk1c4;                 // +0x1c4
    char   pad_1c5[0x220 - 0x1c5];
    int    mUnk220;                 // +0x220

    void Init(int n);
    void Update();
    void Cleanup();
    void Apply();
    void SetLightingWorld();
    void NotifyLighting();
};
struct IRefCounted {
    virtual void AddRef();
    virtual void Release();
};
struct AutoRef {
    void* mpObject;
    AutoRef(void* p) : mpObject(p) {
        if (mpObject)
            _InterlockedExchangeAdd((volatile long*)((char*)mpObject + 8), 1);
    }
    ~AutoRef() {
        if (mpObject) {
            volatile long* rc = (volatile long*)((char*)mpObject + 8);
            _InterlockedExchangeAdd(rc, -1);
            if (_InterlockedExchangeAdd(rc, 0) < 1)
                _InterlockedExchangeAdd(rc, 1);
            else
                _InterlockedExchangeAdd(rc, 0);
        }
    }
};
struct Elem12 {
    IRefCounted* mObj;              // +0
    int mField4;                    // +4
    int mField8;                    // +8
};
extern cPropertyList* g_AppProperties;
extern int g_Unk153a2e8;
void* Graphics_67dd60();
void* Graphics_67dda0();
void* Graphics_67dd50();
void  FUN_00777ae0(int a, int b, int c);
void  FUN_00761110(void* p);
extern int   g_16fa3a8;
extern int   g_16f954c, g_16f9550, g_16f9558, g_16f955c;
extern int   g_16f966c, g_16f9670, g_16f9678, g_16f967c, g_16f9680;
extern int   g_16fa168, g_16fa16c, g_16fa164;
extern int   g_16fa1a0, g_16fa19c, g_16fa1a4;
extern int   g_16fa248, g_16fa244, g_16fa24c;
extern int   g_16fa210, g_16fa20c, g_16fa214;
extern float g_140e8f8;
void cShadowWorld::Apply()
{
    if (mUnk14 != 0 && mUnk1ac >= g_140e8f8)
        mUnk44 = 3;
    else
        mUnk44 = 2;

    int t0 = mShadowBasisMaps[0][0]->mField0;
    g_16fa3a8 |= 0x80;
    g_16f954c |= 0x70;
    g_16f966c = t0;
    g_16fa168 = 2;
    g_16fa164 = 2;
    g_16fa16c = 2;
    if (mUnk14 != 0) {
        int t1 = mShadowBasisMaps[0][1]->mField0;
        g_16fa3a8 |= 0x100;
        g_16f9550 |= 0x70;
        g_16f9670 = t1;
        g_16fa1a0 = 2;
        g_16fa19c = 2;
        g_16fa1a4 = 2;
        int t2 = mShadowBasisMaps[1][0]->mField0;
        g_16fa3a8 |= 0x800;
        g_16f955c |= 0x70;
        g_16f967c = t2;
        g_16fa248 = 2;
        g_16fa244 = 2;
        g_16fa24c = 2;
    }

    void* g = Graphics_67dd60();
    AutoRef ar((void*)((void*(__thiscall*)(void*, uint32_t, int, int))((void**)(*(void**)g))[8])(g, 0x7543c109, g_Unk153a2e8, 0));
    void* p = ar.mpObject;
    if (p) {
        if ((*(uint8_t*)((char*)p + 4) & 1) == 0) {
            void* g2 = Graphics_67dd60();
            ((void(__thiscall*)(void*, void*))((void**)(*(void**)g2))[13])(g2, p);
        }
        g_16fa3a8 |= 0x400;
        g_16f9558 |= 0x70;
        g_16f9678 = *(int*)p;
        g_16fa210 = 2;
        g_16fa20c = 2;
        g_16fa214 = 0;
    }
}
void AssignRef(void** slot, void* p);  // 0x00780270 (defined below; used by a stub's inline body)
void cShadowWorld::Init(int)
{
    int width = 0x200;
    int height = 0x200;
    if (g_AppProperties) {
        void* local = 0;
        if (((bool(__thiscall*)(cPropertyList*, uint32_t, void**))((void**)g_AppProperties)[9])(g_AppProperties, 0x276ac00, &local)
            && *(uint16_t*)((char*)local + 0x12) == 9) {
            width = *Property_GetInt(local);
            height = width;
        }
    }
    int height2 = 0x200;
    if (g_AppProperties) {
        void* local = 0;
        if (((bool(__thiscall*)(cPropertyList*, uint32_t, void**))((void**)g_AppProperties)[9])(g_AppProperties, 0x33cb1dad, &local)
            && *(uint16_t*)((char*)local + 0x12) == 9) {
            height2 = *Property_GetInt(local);
        }
    }

    mShadowDB = CreateRaster(width, width, 1, 2, 0x50);

    void* g = Graphics_67dda0();
    int rid[2];
    ((void(__thiscall*)(void*, int*, int, int, int, int, uint32_t, int))((void**)(*(void**)g))[4])(g, rid, width, width, 0x15, 0, 0xd24f7, 0);
    mShadowMapRectIDs[1].a = rid[0];
    mShadowMapRectIDs[1].b = rid[1];
    ((void(__thiscall*)(void*, int, int, const char*))((void**)(*(void**)g))[0x12])(g, rid[0], rid[1], "ShadowMap");
    void* res = (void*)((void*(__thiscall*)(void*, int, int))((void**)(*(void**)g))[7])(g, mShadowMapRectIDs[1].a, mShadowMapRectIDs[1].b);
    GetImageResource(res);

    bool blur = g_AppProperties->GetDescription(0x5879277);
    int format = mUnk15 ? 0x72 : 0x15;

    int numMaps = height2;
    for (int i = 0; i < numMaps; ++i) {
        int cnt = 2;
        if (i == numMaps - 1)
            cnt = 1;
        for (int j = 0; j < cnt; ++j) {
            int rr[2];
            ((void(__thiscall*)(void*, int*, int, int, int, int, uint32_t, int))((void**)(*(void**)g))[4])(g, rr, width, width, format, 0, 0x140e928, 0);
            if (rr[0] != -1) {
                ((void(__thiscall*)(void*, int, int, const char*))((void**)(*(void**)g))[0x12])(g, rr[0], rr[1], "WorldShadowBasisMap");
                void* obj = (void*)((void*(__thiscall*)(void*, int, int))((void**)(*(void**)g))[7])(g, rr[0], rr[1]);
                int k = i * 4 + j;
                AssignRef((void**)&mShadowBasisMaps[0][k], obj);
                mShadowBasisMapRectIDs[0][k].a = rr[0];
                mShadowBasisMapRectIDs[0][k].b = rr[1];
            }
        }
        if (blur) {
            for (int j = 2; j < 4; ++j) {
                int rr[2];
                ((void(__thiscall*)(void*, int*, int, int, int, int, uint32_t, int))((void**)(*(void**)g))[4])(g, rr, width, width, format, 0, 0x140e928, 0);
                if (rr[0] != -1) {
                    ((void(__thiscall*)(void*, int, int, const char*))((void**)(*(void**)g))[0x12])(g, rr[0], rr[1], "WorldShadowBasisMapBlur");
                    void* obj = (void*)((void*(__thiscall*)(void*, int, int))((void**)(*(void**)g))[7])(g, rr[0], rr[1]);
                    int k = i * 4 + j;
                    AssignRef((void**)&mShadowBasisMaps[0][k], obj);
                    mShadowBasisMapRectIDs[0][k].a = rr[0];
                    mShadowBasisMapRectIDs[0][k].b = rr[1];
                }
            }
        }
    }

    void* s = EastlAllocate(0x47c, "Graphics", 0, 0, 0, 0);
    if (s)
        s = FUN_0077f040(this, 0, blur, 0);
    if (s != mRenderShadow) {
        void* old = mRenderShadow;
        if (s)
            _InterlockedExchangeAdd((volatile long*)((char*)s + 8), 1);
        mRenderShadow = s;
        if (old) {
            volatile long* rc = (volatile long*)((char*)old + 8);
            _InterlockedExchangeAdd(rc, -1);
            if (_InterlockedExchangeAdd(rc, 0) < 1)
                _InterlockedExchangeAdd(rc, 1);
            else
                _InterlockedExchangeAdd(rc, 0);
        }
    }
}
// ---- items of slice s0077ff30 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cPropertyList* g_AppProperties;

// ---- items of slice s007819d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_153a130, g_153a134, g_153a138;
extern float g_1633bd0, g_1633bd4, g_1633bd8;
extern float g_1470f1c, g_1485720, g_1486110;
extern float g_13ef61c, g_13ec4d0, g_13eb1bc, g_1488874;
struct IRefObj {
    virtual void AddRef();
    virtual void Release();
};
inline void* operator new(size_t, void* p) { return p; }
struct E12 {
    IRefObj* p;
    int      a;
    int      b;

    E12() {}
    E12(const E12& o) { p = o.p; if (p) p->AddRef(); a = o.a; b = o.b; }
    E12(IRefObj* pp, int aa, int bb) { p = pp; if (p) p->AddRef(); a = aa; b = bb; }
    ~E12() { if (p) p->Release(); }
};
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
void  EastlFree(void* p);
void  FUN_00743b50(void* p);
void  FUN_00576620(void* p);
struct Sub14 { void FreeRange(void* a, void* b); };
struct ShadowBase { void Notify(); };
void  FUN_Memset(void* dst, int val, unsigned size);        // 0x11e073e
__declspec(noinline) void __fastcall FUN_00781CF0(void* v);  // E36 vector destroy
void __stdcall EhVecCtorIterator(void* p, unsigned elemSize, int count,
                                 void (*ctor)(void*), void (*dtor)(void*));
void __stdcall EhVecDtorIterator(void* p, unsigned elemSize, int count,
                                 void (*dtor)(void*));
static void DecRefOrRestore(void* obj)
{
    long* rc = (long*)((char*)obj + 8);
    _InterlockedExchangeAdd(rc, -1);
    if (_InterlockedExchangeAdd(rc, 0) < 1)
        _InterlockedExchangeAdd(rc, 1);
}
struct cShadowWorld_s0078_19d0 {
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
// ---- items of slice s007819d0 end

// ---- items of slice s00782860 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int   g_153a2fc[16];
extern int   g_153a32c;
extern float g_13f4fd0;
extern float g_14853e0;
extern float g_153ae10;
extern float g_1633e44, g_1633e50, g_1633e58, g_1633e60;
extern int   g_1633e48, g_1633e68;
void  FUN_00782800(int a, int b);
void  FUN_007806a0(void* self);
float FUN_00782bb0(int n);
float FUN_00782db0(float t, int m, float x);
float FUN_00782d40(int a, int b);
// ---- items of slice s00782860 end

// @ 0x007806a0
void cShadowWorld::Cleanup()
{
    if (mUnkD) {
        FUN_00777ae0(0x223, 0, 0);
        if (mRenderShadow) {
            void* g = Graphics_67dd50();
            ((void(__thiscall*)(void*, int))((void**)(*(void**)g))[20])(g, mUnk220);
        }
    }
    if (mRenderShadow) {
        void* p = mRenderShadow;
        mRenderShadow = 0;
        ((void(__thiscall*)(void*))((void**)(*(void**)p))[1])(p);
    }
    void* g2 = Graphics_67dda0();
    if (mShadowDB) {
        FUN_00761110(mShadowDB);
        mShadowDB = 0;
    }
    Raster** sm = mShadowMaps;
    RectID*  sr = mShadowMapRectIDs;
    Raster** bm = mShadowBasisMaps[0];
    RectID*  br = mShadowBasisMapRectIDs[0];
    for (int i = 0; i < 2; ++i) {
        if (*sm) {
            if (*sm) {
                Raster* p = *sm;
                *sm = 0;
                volatile long* rc = (volatile long*)((char*)p + 8);
                _InterlockedExchangeAdd(rc, -1);
                if (_InterlockedExchangeAdd(rc, 0) < 1)
                    _InterlockedExchangeAdd(rc, 1);
                else
                    _InterlockedExchangeAdd(rc, 0);
            }
            ((void(__thiscall*)(void*, int, int))((void**)(*(void**)g2))[5])(g2, sr->a, sr->b);
        }
        for (int j = 4; j != 0; --j) {
            if (*bm) {
                if (*bm) {
                    Raster* p = *bm;
                    *bm = 0;
                    volatile long* rc = (volatile long*)((char*)p + 8);
                    _InterlockedExchangeAdd(rc, -1);
                    if (_InterlockedExchangeAdd(rc, 0) < 1)
                        _InterlockedExchangeAdd(rc, 1);
                    else
                        _InterlockedExchangeAdd(rc, 0);
                }
                ((void(__thiscall*)(void*, int, int))((void**)(*(void**)g2))[5])(g2, br->a, br->b);
            }
            ++bm;
            ++br;
        }
        ++sm;
        ++sr;
    }
}

// @ 0x00780a50
Elem12* MoveBackward12(Elem12* first, Elem12* last, Elem12* dLast)
{
    while (last != first) {
        --last;
        --dLast;
        IRefCounted* src = last->mObj;
        IRefCounted* dst = dLast->mObj;
        if (src != dst) {
            if (src)
                src->AddRef();
            dLast->mObj = src;
            if (dst)
                dst->Release();
        }
        dLast->mField4 = last->mField4;
        dLast->mField8 = last->mField8;
    }
    return dLast;
}

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

// @ 0x00781cf0
void __fastcall FUN_00781CF0(void* v)
{
    char* begin = *(char**)v;
    char* end = *(char**)((char*)v + 4);
    for (; begin < end; begin += 0x24)
        ((Vec12*)(begin + 4))->Destroy();
    begin = *(char**)v;
    if (begin && *(int*)(begin - 4) != 0)
        EastlFree(begin);
}

// @ 0x00781d60
cShadowWorld_s0078_19d0* cShadowWorld_ctor(cShadowWorld_s0078_19d0* p)
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

// @ 0x007821b0
void cShadowWorld_dtor(cShadowWorld_s0078_19d0* p)
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

// @ 0x007825d0
void cSWsub::FUN_007825d0(void* obj, unsigned flag)
{
    unsigned f = flag | 0x11d00;
    IRefObj* p = (IRefObj*)((void*(__thiscall*)(void*))((void**)(*(void**)obj))[0x13c / 4])(obj);
    E12 tmp(p, (int)f, (int)f);
    mVec.push_back(tmp);
}

// @ 0x00782660
void cSWsub::FUN_00782660(void* obj, unsigned flag)
{
    Obj10* p = new Obj10(((int(__thiscall*)(void*))((void**)(*(void**)obj))[0xa0 / 4])(obj));
    E12 tmp((IRefObj*)p, (int)flag, (int)(flag | 0x40000));
    mVec.push_back(tmp);
}

// @ 0x00782740
void cSWsub::FUN_00782740(void* obj, unsigned flag)
{
    E12 tmp((IRefObj*)obj, (int)flag, (int)flag);
    mVec.push_back(tmp);
}

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

// @ 0x00782b00
void __fastcall FUN_00782B00(int p)
{
    FUN_007806a0((char*)p - 8);
    FUN_00782800(*(int*)(p + 0x30), *(int*)(p + 0x34));
    (*(void(__thiscall**)(int))(*(int*)(p + 8) + 0x24))(p + 8);
}

// @ 0x00782bb0
float FUN_00782bb0(int n)
{
    float f;
    if (n < 0xd) {
        int v = g_153a2fc[n];
        double d = (double)v;                 // x87 fild keeps the extended result the original returns
        if (v < 0)
            d += (double)g_13f4fd0;
        return (float)d;
    }
    f = (float)g_153a32c;
    if (g_153a32c < 0)
        f = f + g_13f4fd0;
    if (7 < n - 0xc) {
        int i = n - 2;
        do {
            int a = i + 1, b = i, c = i - 1, d = i - 2, e = i - 3, gg = i - 4, h = i - 5;
            f = (float)n * f;
            n -= 8;
            i -= 8;
            f = f * (float)a; f = f * (float)b; f = f * (float)c; f = f * (float)d;
            f = f * (float)e; f = f * (float)gg; f = f * (float)h;
        } while (0x13 < n);
    }
    while (0xc < n) {
        f = (float)n * f;
        n -= 1;
    }
    return f;
}

// @ 0x00782c90
void FUN_00782c90(float* out, const float* m, const float* v)
{
    float vy = v[1];
    float vx = v[0];
    float vz = v[2];
    out[0] = (vy * m[4] + vx * m[0]) + vz * m[8];
    out[1] = (vy * m[5] + vx * m[1]) + vz * m[9];
    out[2] = (vy * m[6] + vx * m[2]) + vz * m[10];
    out[3] = (vy * m[7] + vx * m[3]) + vz * m[11];
}

// @ 0x00782ce0
void FUN_00782ce0(float* out, int n, const float* m, const float* w)
{
    n = n - 1;
    float w0 = w[0];
    float r0 = w0 * m[0], r1 = w0 * m[1], r2 = w0 * m[2], r3 = w0 * m[3];
    out[0] = r0; out[1] = r1; out[2] = r2; out[3] = r3;
    if (0 < n) {
        do {
            float wi = w[1];
            const float* c = m + 4;
            m = m + 4;
            w = w + 1;
            n = n - 1;
            r0 = wi * c[0] + r0;
            r1 = wi * c[1] + r1;
            r2 = wi * c[2] + r2;
            r3 = wi * c[3] + r3;
        } while (0 < n);
        out[0] = r0; out[1] = r1; out[2] = r2; out[3] = r3;
    }
}

// @ 0x00782d40
float FUN_00782d40(int l, int m)
{
    if (m == 0)
        return (float)sqrt((double)((float)(l * 2 + 1) / (g_153ae10 * g_14853e0)));
    float a = FUN_00782bb0(l - m);
    float b = FUN_00782bb0(l + m);
    return (float)sqrt((double)((a * (float)(l * 2 + 1)) / ((g_153ae10 * g_14853e0) * b)));
}

// @ 0x00782db0
float FUN_00782db0(float lf, int m, float x)
{
    union { float f; int i; } lb;
    lb.f = lf;
    int l = lb.i;

    float f13 = 1.0f;
    volatile float f16 = 1.0f;
    volatile float acc;
    float local = 1.0f;
    if (0 < m) {
        int i = 1;
        float f12 = (float)sqrt((double)((1.0f - x) * (x + 1.0f)));
        if (7 < m) {
            unsigned n = (unsigned)m >> 3;
            i = (int)(n * 8 + 1);
            do {
                n = n - 1;
                float cf = f13;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                acc = -cf; acc = acc * f12; acc = acc * f16; f16 = acc;
                cf = cf + 2.0f;
                f13 = cf;
            } while (n != 0);
        }
        if (i <= m) {
            int k = (m - i) + 1;
            do {
                k = k - 1;
                acc = -f13; acc = acc * f12; acc = acc * f16; f16 = acc;
                f13 = f13 + 2.0f;
            } while (k != 0);
        }
        local = f16;
    }
    if (l == m)
        return local;
    float A0 = (float)(m * 2 + 1);
    acc = A0 * local; acc = acc * x;
    float prev1 = acc;
    if (l == m + 1)
        return prev1;
    float result = 0.0f;
    int i = m + 2;
    if (i <= l) {
        float prev2 = local;
        while (i <= l) {
            float A = (float)(i * 2 - 1);
            acc = A * prev1; acc = acc * x;
            float B = (float)(i + m - 1);
            float bp = B * prev2;
            acc = acc - bp;
            acc = acc / (float)(i - m);
            prev2 = prev1;
            prev1 = acc;
            result = acc;
            i = i + 1;
        }
    }
    return result;
}

// @ 0x00783130
float FUN_00783130(float theta, unsigned m, float phi, float extra)
{
    if ((g_1633e48 & 1) == 0) {
        g_1633e48 |= 1;
        g_1633e44 = 1.4142135f;
    }
    float c = (float)cos((double)phi);
    int mm = (int)((m ^ ((int)m >> 31)) - ((int)m >> 31));
    float a = (float)FUN_00782db0(theta, mm, c);
    union { float f; int i; } tb;
    tb.f = theta;
    float b = FUN_00782d40(tb.i, mm);   // the original passes the float's bit pattern as the int l
    b = b * a;
    if (m != 0) {
        float ge = g_153ae10 + extra;       // SSE addss rounds g+extra to float, as the original does
        double t = (double)mm * (double)ge; // x87 fild/fmul keeps the extended product
        if (0 < (int)m)
            return cos(t) * g_1633e44 * b;
        return sin(t) * g_1633e44 * b;
    }
    return b;
}
