// Slice s00760ea0 : SP render helpers (rw::graphics Raster creation, global-state reset,
// small Raster/refcounted thunks and the 0xc-stride vector insert).
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast region.
#include "types.h"
#include <new>
#include <stdlib.h>

// ---------------------------------------------------------------- descriptor types
struct E8 { int a, b; E8() {} E8(int x, int y) : a(x), b(y) {} ~E8(); };
struct D1 { E8 v[4]; };
struct D2 { E8 v[4]; };
struct D3 { E8 v[4]; };
struct D4 { E8 v[4]; };

E8::~E8() {}

extern "C" {
void* __cdecl operator_new(unsigned int size, const char* name, int a, int b, int c, int d);
void  __cdecl operator_delete_(void* p);
void  __cdecl opnew3(void* p, int a, unsigned int n);           // @ 0x11e073e
void  __cdecl FUN_00777ae0(int a, void* p, int b);             // @ 0x777ae0
void  __cdecl FUN_007823b0(void* a, void* b);                  // @ 0x7823b0
void  __cdecl FUN_00781b10();                                  // @ 0x781b10
void* __cdecl FUN_00928a30(void* a, void* b, int c, int d, int e, int f, int g, int h); // @ 0x928a30
void* __cdecl FUN_011f3c40(void* p);                           // @ 0x11f3c40
void* __cdecl FUN_011f34a0(void* p, int a, int b);             // @ 0x11f34a0
void* __cdecl FUN_011f9a90(void* p, int a);                    // @ 0x11f9a90
void* __cdecl FUN_011f9eb0(void* p, int a, int b);             // @ 0x11f9eb0
void* __cdecl FUN_011eef30(void* p, int a, int b);             // @ 0x11eef30
void* __cdecl Raster_Initialize(void* p, int a, int b, int c, int d, int e); // @ 0x11efeb0
void* __cdecl GetD3DCAPS9();                                   // @ 0x11f8af0
void* __cdecl FUN_011f1340(int a);                             // @ 0x11f1340
}
D1 __cdecl FUN_011f0220(int a, int b, int c, int d, int e);    // @ 0x11f0220 (returns descriptor by value)
D1 __cdecl FUN_011f9e50(int a, int b);                         // @ 0x11f9e50
D1 __cdecl FUN_011eec00(int a, int b);                         // @ 0x11eec00
struct Raster {
    void D3D9GetStreamedMipLevelSize(void* p, int b);          // @ 0x11f0270
};

// ---------------------------------------------------------------- shared types
struct RefCountedAt8 {
    virtual void r0();
    int r1;
    int mRefCount;                     // +0x8
    void AddRef();
    void Release();
};
struct Elem3 {                         // 0xc, intrusive refcounted pointer + 2 words
    RefCountedAt8* p;                  // +0x0
    void* a;                           // +0x4
    void* b;                           // +0x8
    Elem3() {}
    Elem3(const Elem3& o) : p(o.p), a(o.a), b(o.b) { if (p) p->AddRef(); }
    ~Elem3() { if (p) p->Release(); }
};
struct Vec3 {
    Elem3* mpBegin;                    // +0x0
    Elem3* mpEnd;                      // +0x4
    Elem3* mpCapacity;                 // +0x8
    Elem3* insert(Elem3* position, const Elem3& value);        // @ 0x760ea0
    void   DoInsertValue(Elem3* position, const Elem3& value); // @ 0x760ca0
    void   setByKey(RefCountedAt8* layer, unsigned int key, void* flags); // @ 0x760fd0
};

// @ 0x760ea0
Elem3* Vec3::insert(Elem3* position, const Elem3& value)
{
    int idx = (int)((char*)position - (char*)mpBegin) / 0xc;
    if (position == mpEnd && mpEnd != mpCapacity) {
        mpEnd = (Elem3*)((char*)mpEnd + 0xc);
        if (position)
            new (position) Elem3(value);
    } else {
        DoInsertValue(position, value);
    }
    return (Elem3*)((char*)mpBegin + idx);
}

// ------------------------------------------------------------------- 0x760f50 (dtor)
extern void* g_vt140ddf4, *g_vt140ddf0, *g_vt13ef094, *g_vt13eb938;
struct D_760f50 {
    void* p0; void* p1;
    char pad8[4];
    void* vfirst; void* vlast;   // +0xc / +0x10
    ~D_760f50();
};
D_760f50::~D_760f50()
{
    p0 = g_vt140ddf4;
    p1 = g_vt140ddf0;
    if (vfirst != vlast)
        FUN_007823b0(vfirst, vlast);
    FUN_00781b10();
    p0 = g_vt13eb938;
    p1 = g_vt13ef094;
}

// ------------------------------------------------ 0x760fd0 (set by layer number)
// @ 0x760fd0
void Vec3::setByKey(RefCountedAt8* layer, unsigned int key, void* flags)
{
    Elem3* first = mpBegin;
    Elem3* last = mpEnd;
    Elem3* it = first;
    if (it != last) {
        while (key > *(unsigned int*)((char*)it + 4)) {
            it = (Elem3*)((char*)it + 0xc);
            if (it == last) break;
        }
    }
    if (it != last && key == *(unsigned int*)((char*)it + 4)) {
        RefCountedAt8* old = *(RefCountedAt8**)it;
        if (layer != old) {
            if (layer) layer->AddRef();
            *(RefCountedAt8**)it = layer;
            if (old) old->Release();
        }
        *(unsigned int*)((char*)it + 4) = key;
        *(void**)((char*)it + 8) = flags;
        return;
    }
    Elem3 val;
    val.p = layer;
    if (layer) layer->AddRef();
    val.a = (void*)key;
    val.b = flags;
    insert(it, val);
    if (val.p) val.p->Release();
}

// ------------------------------------------------------------- 0x7610f0..0x761170 thunks
struct Alloc16c8b44 {
    void  Free(void* p);                                           // @ 0x9276c0
    void* allocate(int a, int b, int c, int d, int e, int f, int g, int h); // @ 0x928a30
};
extern Alloc16c8b44* g_alloc;          // 0x16c8b44

struct D0 { void call(); };

// @ 0x7610f0
void __cdecl FUN_007610f0(D0* p) { p->call(); g_alloc->Free(p); }
// @ 0x761110
void __cdecl FUN_00761110(D0* p) { if (p) { p->call(); g_alloc->Free(p); } }
// @ 0x761130
void __cdecl FUN_00761130(D0* p) { p->call(); g_alloc->Free(p); }
// @ 0x761150
void __cdecl FUN_00761150(D0* p) { p->call(); g_alloc->Free(p); }
// @ 0x761170
void __cdecl FUN_00761170(D0* p) { p->call(); g_alloc->Free(p); }

// --------------------------------------------------------------- 0x7611a0 (scan)
struct Elem11a0 { int a; unsigned char b; char pad[3]; int c; };   // 0xc
struct S11a0 {
    char pad0[0xc];
    unsigned short mCount;     // +0xc
    char pad_e[2];
    unsigned char mFlags;      // +0x10
    char pad11[7];
};
extern unsigned char g_flag1539034;    // 0x1539034
// @ 0x7611a0
void __cdecl FUN_007611a0(S11a0* s)
{
    if (s->mFlags & 4) {
        unsigned int n = s->mCount;
        unsigned int i = 0;
        if (n > 0) {
            Elem11a0* e = (Elem11a0*)((char*)s + 0x18);
            do {
                if (e->c == 2) {
                    if (e->b == 5 && g_flag1539034)
                        FUN_00777ae0(0x22c, &g_flag1539034, 0);
                    return;
                }
                i++;
                e = (Elem11a0*)((char*)e + 0xc);
            } while (i < n);
        }
    }
}

// ------------------------------------------------------------- 0x761240 (vcall)
struct Arg1240 { char pad[4]; unsigned int a; char pad2[4]; unsigned int b; };
struct Local1240 { unsigned int a, b, c, d; };
struct V1240 { virtual void v0(); virtual void v1(); virtual void v2(Local1240*); void set(Arg1240*); };
// @ 0x761240
void V1240::set(Arg1240* p)
{
    Local1240 l;
    l.b = p->a;
    l.d = p->b;
    p->a = 0;
    p->b = 0;
    l.a = 0;
    l.c = 0;
    v2(&l);
}

// ------------------------------------------------- 0x761280/2c0/300/340 (descriptors)
// @ 0x761280
D1 __cdecl FUN_00761280(int n)
{
    D1 d;
    d.v[0] = E8((n * 3 + 6) * 4, 4);
    return d;
}
// @ 0x7612c0
D2 __cdecl FUN_007612c0(int n)
{
    D2 d;
    d.v[0] = E8(n * 4 + 0x24, 4);
    return d;
}
// @ 0x761300
D3 __cdecl FUN_00761300()
{
    D3 d;
    d.v[0] = E8(0x40, 0x10);
    return d;
}
// @ 0x761340
D4 __cdecl FUN_00761340()
{
    D4 d;
    d.v[0] = E8(0xa0, 0x10);
    return d;
}

// ------------------------------------------------------------------- 0x761380
// @ 0x761380
unsigned int __cdecl FUN_00761380()
{
    D4 d = FUN_00761340();
    int local[4];
    local[0] = (int)FUN_00928a30((void*)d.v[0].a, (void*)d.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    return (unsigned int)FUN_011f3c40(local);
}

// ------------------------------------------------------------------- 0x761420
// @ 0x761420  SP::CreateRaster
void* __cdecl SP_CreateRaster(int w, int h, int levels, int fmt, int flags)
{
    void* caps = GetD3DCAPS9();
    if (!(*(unsigned int*)((char*)caps + 0xc) & 0x40000000))
        flags &= 0xfffffdff;
    D1 d = FUN_011f0220(w, h, levels, fmt, flags);
    int local[4];
    local[0] = (int)FUN_00928a30((void*)d.v[0].a, (void*)d.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    return Raster_Initialize(local, w, h, levels, fmt, flags);
}

// ------------------------------------------------------------------- 0x761650
// @ 0x761650
void* __cdecl FUN_00761650(int n)
{
    D1 d = FUN_00761280(n);
    int local[4];
    local[0] = (int)FUN_00928a30((void*)d.v[0].a, (void*)d.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    return FUN_011f34a0(local, n, 0);
}

// ------------------------------------------------------------------- 0x7616f0
// @ 0x7616f0
void* __cdecl FUN_007616f0(int a, int b)
{
    D1 d = FUN_011f9e50(a, b);
    int local[4];
    local[0] = (int)FUN_00928a30((void*)d.v[0].a, (void*)d.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    return FUN_011f9eb0(local, a, b);
}

// ------------------------------------------------------------------- 0x7617a0
// @ 0x7617a0
void* __cdecl FUN_007617a0(int a)
{
    D1 d = FUN_011eec00(a, a);
    int local[4];
    local[0] = (int)FUN_00928a30((void*)d.v[0].a, (void*)d.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    return FUN_011eef30(local, a, a);
}

// ------------------------------------------------------------------- 0x761840
// @ 0x761840
void* __cdecl FUN_00761840(int a)
{
    D2 d = FUN_007612c0(a);
    int local[4];
    local[0] = (int)FUN_00928a30((void*)d.v[0].a, (void*)d.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    return FUN_011f9a90(local, a);
}

// ------------------------------------------------------------------- 0x761500
void* __cdecl FUN_012055f0(void* out, int a, int b, int c, int d, void* e, int f); // @ 0x12055f0
void* __cdecl FUN_012046f0(void* p, int a, int b, int c, int d, void* e, int f);    // @ 0x12046f0
// @ 0x761500  SP::CreateTriangleKDTreeProcedural
void* __cdecl FUN_00761500(int a, int b, int c, int d, void** out)
{
    char desc[0x50];
    FUN_012055f0(desc, a, b, c, d, (void*)0x15d0a7c, 0x50);
    int local[4];
    local[0] = (int)FUN_00928a30(*(void**)desc, *(void**)(desc + 4), 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    void* r = FUN_012046f0(local, a, b, c, d, (void*)0x15d0a7c, 0x50);
    if (out) {
        out[0] = r;
        char* src = desc;
        char* dst = (char*)out + 0x20;
        for (int i = 0; i < 8; i++)
            ((int*)dst)[i] = ((int*)src)[i];
    }
    return r;
}

// ------------------------------------------------------------------- 0x7618e0
extern unsigned int g_16fa38c, g_16f9218, g_16f923c, g_16f9530, g_16f9534;
extern unsigned int g_16f9538, g_16f953c, g_16f9540, g_16f9544, g_16f9528;
extern unsigned int g_16f922c, g_16f9230, g_16f921c, g_16f9244, g_16f9240;
extern unsigned int g_16f9650, g_16fa3a8, g_16f9fdc, g_16f9fe0, g_16f9fe4;
extern unsigned int g_16f9654, g_16fa014, g_16fa018, g_16fa01c, g_16f9658;
extern unsigned int g_16fa04c, g_16fa050, g_16fa054, g_16f965c, g_16fa084;
extern unsigned int g_16fa088, g_16fa08c, g_16f9660, g_16fa0bc, g_16fa0c0;
extern unsigned int g_16fa0c4, g_16f9664, g_16fa0f4, g_16fa0f8, g_16fa0fc;
extern unsigned int g_16f96a0, g_16f96a8, g_16f96ac, g_16f96b0, g_16f96b4;
extern unsigned int g_16fa380;
// @ 0x7618e0  SP::ResetGlobalState
void __cdecl FUN_007618e0()
{
    g_16fa38c |= 0x10080;
    g_16f9218 = 1;
    g_16f923c = 2;
    FUN_011f1340(0x10002);
    g_16f9530 |= 0x70;
    g_16f9534 |= 0x70;
    g_16f9538 |= 0x70;
    g_16fa3a8 |= 0x3f;
    g_16f953c |= 0x70;
    g_16f9540 |= 0x70;
    g_16f9544 |= 0x70;
    g_16f9528 |= 0x11;
    g_16f922c = 5;
    g_16f9230 = 6;
    g_16f921c = 0;
    g_16f9244 = 8;
    g_16f9240 = 0;
    g_16f9650 = 0; g_16f9fe0 = 2; g_16f9fdc = 2; g_16f9fe4 = 2;
    g_16f9654 = 0; g_16fa018 = 2; g_16fa014 = 2; g_16fa01c = 2;
    g_16f9658 = 0; g_16fa050 = 2; g_16fa04c = 2; g_16fa054 = 2;
    g_16f965c = 0; g_16fa088 = 2; g_16fa084 = 2; g_16fa08c = 2;
    g_16f9660 = 0; g_16fa0c0 = 2; g_16fa0bc = 2; g_16fa0c4 = 2;
    g_16f9664 = 0; g_16fa0f8 = 2; g_16fa0f4 = 2; g_16fa0fc = 2;
    g_16f96a0 = 4;
    g_16fa380 = 0x16fa4f0;
    g_16f96ac = 0x3f800000; g_16f96b0 = 0x3f800000; g_16f96b4 = 0x3f800000;
}

// ------------------------------------------------------------------- 0x761b40
// @ 0x761b40
void* __cdecl FUN_00761b40()
{
    void* r = SP_CreateRaster(0x100, 0x100, 1, 8, 0x15);
    if (!r)
        return 0;
    unsigned int* buf = (unsigned int*)operator_new(0x40000, "Graphics", 0, 0, 0, 0);
    unsigned int* row = buf;
    int y = 0;
    do {
        int x = 0;
        int d = -y;
        do {
            if (abs(d) < 8 || abs(x + y - 0x100) < 8)
                row[x] = 0xffff0000;
            else
                row[x] = 0xffffffff;
            x++;
            d++;
        } while (x < 0x100);
        y++;
        row += 0x100;
    } while (y < 0x100);
    ((Raster*)r)->D3D9GetStreamedMipLevelSize(buf, 0);
    operator_delete_(buf);
    return r;
}

// ------------------------------------------------------------------- 0x761c00
// @ 0x761c00
void* __cdecl FUN_00761c00()
{
    void* r = SP_CreateRaster(8, 8, 1, 8, 0x15);
    char buf[0x100];
    opnew3(buf, 0, 0x100);
    ((Raster*)r)->D3D9GetStreamedMipLevelSize(buf, 0);
    return r;
}

// ------------------------------------------------------------------- 0x761c50
struct Pair2 { unsigned int x; unsigned int y; };
// @ 0x761c50
unsigned int* __stdcall FUN_00761c50(unsigned int* out, Pair2* arr, int unused)
{
    out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
    out[0] = 0;
    unsigned int i = 0;
    Pair2* p = arr;
    do {
        if (p->x != 0)
            out[i] = (unsigned int)g_alloc->allocate((int)p->x, (int)p->y, 0, 0, 0, 0, 0, 0);
        i++;
        p++;
    } while (i < 4);
    return out;
}

// ------------------------------------------------------------------- 0x761cc0
// @ 0x761cc0
void __stdcall FUN_00761cc0(void** arr)
{
    unsigned int i = 0;
    do {
        void* p = arr[i];
        if (p)
            g_alloc->Free(p);
        i++;
    } while (i < 4);
}

// ------------------------------------------------------------------- 0x761cf0
extern float g_16f8bec, g_16f8be8, g_16f8bfc, g_16f8bf8;
extern float g_16f8c0c, g_16f8c08, g_16f8c1c, g_16f8c18;
extern float g_16f8c90, g_16f8c94, g_16f8c98, g_16f8c9c;
extern float g_140dea0;
// @ 0x761cf0
void __cdecl FUN_00761cf0(int n)
{
    float f = (float)(-n) * g_140dea0;
    g_16f8be8 = g_16f8bec * f + g_16f8be8;
    g_16f8bf8 = g_16f8bfc * f + g_16f8bf8;
    g_16f8c08 = g_16f8c0c * f + g_16f8c08;
    g_16f8c18 = g_16f8c1c * f + g_16f8c18;
    g_16f8c90 = g_16f8bec * f + g_16f8c90;
    g_16f8c94 = g_16f8bfc * f + g_16f8c94;
    g_16f8c98 = g_16f8c0c * f + g_16f8c98;
    g_16f8c9c = g_16f8c1c * f + g_16f8c9c;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
