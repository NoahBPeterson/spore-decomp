// src/game/SPEngine/SPGraphicsRenderWareUtils.cpp -- migrated from slice(s) s00760ea0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsRenderWareUtils.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/graphics/Raster.h"

// SP::cSPMemPool global allocator (0x016c8b44); LockedAligned is __thiscall (this = the pool).
struct SPMemPoolStub {
    void* LockedAligned(unsigned int size, unsigned int align, int a, int b, int c, int d, int e, int f); // @ 0x928a30
};
extern SPMemPoolStub* g_pSPMemPool;                            // 0x016c8b44
extern "C" void* __cdecl FUN_011f34a0(void* p, int a, int b);             // @ 0x11f34a0
extern "C" void* __cdecl FUN_011f9a90(void* p, int a);                    // @ 0x11f9a90
extern "C" void* __cdecl FUN_011f9eb0(void* p, int a, int b);             // @ 0x11f9eb0
extern "C" void* __cdecl FUN_011eef30(void* p, int a, int b);             // @ 0x11eef30
extern "C" void* __cdecl Raster_Initialize(void* p, int a, int b, int c, int d, int e); // @ 0x11efeb0
extern "C" void* __cdecl GetD3DCAPS9();                                   // @ 0x11f8af0
#include <new>
#include <stdlib.h>

// ---- items of slice s00760ea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct E8 { int a, b; E8() {} E8(int x, int y) : a(x), b(y) {} ~E8(); };
struct D1 { E8 v[4]; };
struct D2 { E8 v[4]; };
E8::~E8() {}   // 0xc2e4e0
extern "C" void* __cdecl FUN_011f34a0(void* p, int a, int b);             // @ 0x11f34a0
extern "C" void* __cdecl FUN_011f9a90(void* p, int a);                    // @ 0x11f9a90
extern "C" void* __cdecl FUN_011f9eb0(void* p, int a, int b);             // @ 0x11f9eb0
extern "C" void* __cdecl FUN_011eef30(void* p, int a, int b);             // @ 0x11eef30
extern "C" void* __cdecl Raster_Initialize(void* p, int a, int b, int c, int d, int e); // @ 0x11efeb0
extern "C" void* __cdecl GetD3DCAPS9();                                   // @ 0x11f8af0
D1 __cdecl FUN_011f0220(int a, int b, int c, int d, int e);    // @ 0x11f0220 (returns descriptor by value)
D1 __cdecl FUN_011f9e50(int a, int b);                         // @ 0x11f9e50
D1 __cdecl FUN_011eec00(int a, int b);                         // @ 0x11eec00
void* __cdecl FUN_012055f0(void* out, int a, int b, int c, int d, void* e, int f); // @ 0x12055f0
void* __cdecl FUN_012046f0(void* p, int a, int b, int c, int d, void* e, int f);    // @ 0x12046f0
// ---- items of slice s00760ea0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* __cdecl FUN_011f1340(int a);                             // @ 0x11f1340
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

// callees this slice defines outside this object (rewrite.py held_callee_protos)
D1 __cdecl FUN_00761280(int n);  // 0x00761280 (stays in the slice: not this object's)
D2 __cdecl FUN_007612c0(int n);  // 0x007612c0 (stays in the slice: not this object's)

// @ 0x00761420
void* __cdecl SP_CreateRaster(int w, int h, int levels, int fmt, int flags)
{
    void* caps = GetD3DCAPS9();
    if (!(*(unsigned int*)((char*)caps + 0xc) & 0x40000000))
        fmt &= 0xfffffdff;
    D1 d = FUN_011f0220(w, h, levels, fmt, flags);
    int local[4];
    local[0] = (int)g_pSPMemPool->LockedAligned(d.v[0].a, d.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    return Raster_Initialize(local, w, h, levels, fmt, flags);
}

// @ 0x00761500
void* __cdecl FUN_00761500(int a, int b, int c, int d, void** out)
{
    char desc[0x50];
    FUN_012055f0(desc, a, b, c, d, (void*)0x15d0a7c, 0x50);
    int local[4];
    local[0] = (int)g_pSPMemPool->LockedAligned(*(unsigned int*)desc, *(unsigned int*)(desc + 4), 0, 0, 0, 0, 0, 0);
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

// @ 0x00761650
void* __cdecl FUN_00761650(int n)
{
    D1 d = FUN_00761280(n);
    int local[4];
    local[0] = (int)g_pSPMemPool->LockedAligned(d.v[0].a, d.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    return FUN_011f34a0(local, n, 0);
}

// @ 0x007616f0
void* __cdecl FUN_007616f0(int a, int b)
{
    D1 d = FUN_011f9e50(a, b);
    int local[4];
    local[0] = (int)g_pSPMemPool->LockedAligned(d.v[0].a, d.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    return FUN_011f9eb0(local, a, b);
}

// @ 0x007617a0
void* __cdecl FUN_007617a0(int a)
{
    D1 d = FUN_011eec00(a, a);
    int local[4];
    local[0] = (int)g_pSPMemPool->LockedAligned(d.v[0].a, d.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    return FUN_011eef30(local, a, a);
}

// @ 0x00761840
void* __cdecl FUN_00761840(int a)
{
    D2 d = FUN_007612c0(a);
    int local[4];
    local[0] = (int)g_pSPMemPool->LockedAligned(d.v[0].a, d.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    return FUN_011f9a90(local, a);
}

// @ 0x007618e0
namespace SP {
void ResetGlobalState()
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
}  // namespace SP
