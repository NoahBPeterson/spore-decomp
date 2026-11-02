// src/game/SPEngine/SPGraphicsRenderWareUtils.cpp -- migrated from slice(s) s00761dc0, s00760ea0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsRenderWareUtils.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/core/arena/ArenaExportedObject.h"
#include "rw/graphics/Raster.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl operator_new(unsigned int size, const char* name, int a, int b, int c, int d);
extern "C" void  __cdecl operator_delete_(void* p);
extern "C" void  __cdecl opnew3(void* p, int a, unsigned int n);           // @ 0x11e073e
extern "C" void* __cdecl FUN_011f34a0(void* p, int a, int b);             // @ 0x11f34a0
extern "C" void* __cdecl FUN_011f9a90(void* p, int a);                    // @ 0x11f9a90
extern "C" void* __cdecl FUN_011f9eb0(void* p, int a, int b);             // @ 0x11f9eb0
extern "C" void* __cdecl FUN_011eef30(void* p, int a, int b);             // @ 0x11eef30
extern "C" void* __cdecl Raster_Initialize(void* p, int a, int b, int c, int d, int e); // @ 0x11efeb0
extern "C" void* __cdecl GetD3DCAPS9();                                   // @ 0x11f8af0
#include <new>
#include <stdlib.h>
#include <xmmintrin.h>

// ---- items of slice s00760ea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct E8 { int a, b; E8() {} E8(int x, int y) : a(x), b(y) {} ~E8(); };
struct D1 { E8 v[4]; };
struct D2 { E8 v[4]; };
E8::~E8() {}   // 0xc2e4e0
extern "C" void* __cdecl operator_new(unsigned int size, const char* name, int a, int b, int c, int d);
extern "C" void  __cdecl operator_delete_(void* p);
extern "C" void  __cdecl opnew3(void* p, int a, unsigned int n);           // @ 0x11e073e
struct SPMemPoolStub {
void* LockedAligned(unsigned int size, unsigned int align, int a, int b, int c, int d, int e, int f); // @ 0x928a30
};
extern "C" extern SPMemPoolStub* g_pSPMemPool;                            // 0x016c8b44
extern "C" void* __cdecl FUN_011f34a0(void* p, int a, int b);             // @ 0x11f34a0
extern "C" void* __cdecl FUN_011f9a90(void* p, int a);                    // @ 0x11f9a90
extern "C" void* __cdecl FUN_011f9eb0(void* p, int a, int b);             // @ 0x11f9eb0
extern "C" void* __cdecl FUN_011eef30(void* p, int a, int b);             // @ 0x11eef30
extern "C" void* __cdecl Raster_Initialize(void* p, int a, int b, int c, int d, int e); // @ 0x11efeb0
extern "C" void* __cdecl GetD3DCAPS9();                                   // @ 0x11f8af0
D1 __cdecl FUN_011f0220(int a, int b, int c, int d, int e);    // @ 0x11f0220 (returns descriptor by value)
D1 __cdecl FUN_011f9e50(int a, int b);                         // @ 0x11f9e50
D1 __cdecl FUN_011eec00(int a, int b);                         // @ 0x11eec00
struct Raster {
    void D3D9GetStreamedMipLevelSize(void* p, int b);          // @ 0x11f0270
};
void* __cdecl FUN_012055f0(void* out, int a, int b, int c, int d, void* e, int f); // @ 0x12055f0
void* __cdecl FUN_012046f0(void* p, int a, int b, int c, int d, void* e, int f);    // @ 0x12046f0
struct KDElem { int a, b; ~KDElem(); };
struct KDDesc {
    KDElem elems[4];   // +0x00  the two dwords LockedAligned consumes are elems[0].a, elems[0].b
    char   rest[0x30]; // +0x20  remaining payload FUN_012055f0 wrote
};
struct KDTreeDesc {
    unsigned int tag;        // +0x00  0x80003
    void*        obj;        // +0x04  Initialize result
    unsigned int a;          // +0x08  == local[0]
    unsigned int b;          // +0x0c  == local[1]
    unsigned int c;          // +0x10  == local[2]
    unsigned int d;          // +0x14  == local[3]
    KDElem       tail[4];    // +0x18  copy of the descriptor's elems[0..3]
};
// ---- items of slice s00760ea0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" extern SPMemPoolStub* g_pSPMemPool;                            // 0x016c8b44
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
extern float g_16fa4f0[16];      // the 4x4 affine matrix local copy (0x40 bytes)
extern float g_1485720;          // _HK_REAL_ONE == 1.0f

// ---- items of slice s00761dc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_011f3220(void* p);
extern "C" void* __cdecl VectorDescr(int n);   // @ 0x761650
// ---- items of slice s00761dc0 end

// @ 0x00761280
D1 __cdecl FUN_00761280(int n)
{
    D1 d;
    d.v[0] = E8((n * 3 + 6) * 4, 4);
    return d;
}

// @ 0x007612c0
D2 __cdecl FUN_007612c0(int n)
{
    D2 d;
    d.v[0] = E8(n * 4 + 0x24, 4);
    return d;
}

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
void* __cdecl FUN_00761500(int a, int b, int c, int d, KDTreeDesc* out)
{
    KDTreeDesc tmp;
    KDDesc desc;
    unsigned int local[4];
    FUN_012055f0(&desc, a, b, c, d, (void*)0x15d0a7c, 0x50);
    local[0] = (unsigned int)g_pSPMemPool->LockedAligned(desc.elems[0].a, desc.elems[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0;
    local[2] = 0;
    local[3] = 0;
    void* r = FUN_012046f0(local, a, b, c, d, (void*)0x15d0a7c, 0x50);
    if (out) {
        tmp.tag = 0x80003;
        tmp.obj = r;
        tmp.a = local[0];
        tmp.b = local[1];
        tmp.c = local[2];
        tmp.d = local[3];
        for (int i = 0; i < 4; i++)
            tmp.tail[i] = desc.elems[i];
        *out = tmp;
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
    const int two = 2;
    g_16fa38c |= 0x10080;
    g_16f9218 = 1;
    g_16f923c = two;
    FUN_011f1340(0x10002);
    unsigned int v;
    v = g_16f9530; v |= 0x20; v |= 0x10; v |= 0x40; g_16f9530 = v;
    v = g_16f9534; v |= 0x20; v |= 0x10; v |= 0x40; g_16f9534 = v;
    v = g_16f9538; v |= 0x20;
    g_16fa38c |= 0x63100;
    v |= 0x10; v |= 0x40; g_16f9538 = v;
    v = g_16fa3a8; v |= 1; v |= two; v |= 4; v |= 8; v |= 0x10; v |= 0x20; g_16fa3a8 = v;
    v = g_16f953c; v |= 0x20; v |= 0x10; v |= 0x40; g_16f953c = v;
    v = g_16f9540; v |= 0x20; v |= 0x10; v |= 0x40; g_16f9540 = v;
    v = g_16f9544; v |= 0x20; v |= 0x10; v |= 0x40; g_16f9544 = v;
    g_16f922c = 5;
    g_16f9230 = 6;
    g_16f921c = 0;
    g_16f9244 = 8;
    g_16f9240 = 0;
    g_16f9650 = 0; g_16f9fe0 = two; g_16f9fdc = two; g_16f9fe4 = two;
    g_16f9654 = 0; g_16fa018 = two; g_16fa014 = two; g_16fa01c = two;
    g_16f9658 = 0; g_16fa050 = two; g_16fa04c = two; g_16fa054 = two;
    g_16f965c = 0; g_16fa088 = two; g_16fa084 = two; g_16fa08c = two;
    g_16f9660 = 0; g_16fa0c0 = two; g_16fa0bc = two; g_16fa0c4 = two;
    g_16f9664 = 0; g_16fa0f8 = two; g_16fa0f4 = two; g_16fa0fc = two;
    // SSE-built 4x4 affine matrix: diag(1,1,1) in rows 0..2 (1.0 from _HK_REAL_ONE), row 3 zero.
    const float one = g_1485720;
    g_16f9528 |= 0x11;
    float m[16];
    m[0] = one; m[1] = 0; m[2] = 0; m[3] = 0;
    m[4] = 0; m[5] = one; m[6] = 0; m[7] = 0;
    m[8] = 0; m[9] = 0; m[10] = one; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 0;
    g_16f96a0 = 4;
    g_16fa380 = 0x16fa4f0;
    for (int i = 0; i < 16; i++)
        g_16fa4f0[i] = m[i];
    g_16f96a8 = g_16f96ac = g_16f96b0 = g_16f96b4 = 0x3f800000;
}
}  // namespace SP

// @ 0x00761b40
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

// @ 0x00761c00
void* __cdecl FUN_00761c00()
{
    void* r = SP_CreateRaster(8, 8, 1, 8, 0x15);
    char buf[0x100];
    opnew3(buf, 0, 0x100);
    ((Raster*)r)->D3D9GetStreamedMipLevelSize(buf, 0);
    return r;
}

// @ 0x007625d0
void* __cdecl FUN_007625d0(const char* s)
{
    struct Ent { short semantic; char type; char pad5; char pad6; char pad7; int value; };
    Ent ents[32];

    const char* p = s;
    do { } while (*p++);
    int n = (int)(p - (s + 1)) / 3;      // number of 3-char groups
    int count = 0;
    int idxTag = n;                      // +0 field tag: starts at n, ++ per STR triple
    int tIndex = 0;                      // T/t value counter
    int cRun = 0;                        // C/c run counter
    if (n > 0) {
        p = s + 1;
        Ent* e = ents;
        do {
            char c = p[-1];
            if (c == 'S' && p[0] == 'T' && p[1] == 'R') {
                ++idxTag;
            } else {
                bool bT = false, bC = false, bV = false, bW = false;
                if (c == 'T' || c == 't') {
                    bT = true;
                    if (p[0] == '0') {
                        ++tIndex;
                        goto next;
                    }
                }
                ++count;
                e->semantic = (short)idxTag;
                e->type = 0;
                e->value = 0;
                switch (c) {
                case 'B': case 'b': e->value = 0x14; break;
                case 'C': case 'c': bC = true; e->value = (cRun != 0 ? 1 : 0) * 2 + 3; ++cRun; break;
                case 'G': case 'g': e->value = 0x13; break;
                case 'I': case 'i': e->value = 0xe;  break;
                case 'N': case 'n': e->value = 2;    break;
                case 'P': case 'p': e->value = 0x10; break;
                case 'T': case 't': e->value = tIndex; ++tIndex; break;
                case 'V': case 'v': e->value = 0;    bV = true; break;
                case 'W': case 'w': e->value = 0xf;  bW = true; break;
                default: break;
                }
                switch (p[1]) {
                case 'B': case 'b':
                    if (bW)          e->type = 8;
                    else if (bC || bT || bV) e->type = 4;
                    else             e->type = 5;
                    break;
                case 'F': case 'f': e->type = (char)(p[0] - 0x31); break;
                case 'S': case 's': e->type = (char)((p[0] != '2') + 6); break;
                default: break;
                }
            }
next:
            p += 3;
            ++e;
        } while (--n != 0);
    }

    void* desc = VectorDescr(count);
    if (desc) {
        *(unsigned char*)((char*)desc + 0xe) |= 2;
        char* dst = (char*)desc + 0x18;
        for (int i = 0; i < count; i++) {
            *(short*)(dst + 0) = ents[i].semantic;
            dst[4] = ents[i].type;
            *(int*)(dst + 8) = ents[i].value;
            dst += 0xc;
        }
        FUN_011f3220(desc);
    }
    return desc;
}
