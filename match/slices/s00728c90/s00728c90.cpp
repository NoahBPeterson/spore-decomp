// Slice s00728c90 — UV generation: SP::CreateUVsAndCharts and its small enum/index helpers.
// Small switch tables and index lookups are reconstructed; the large chart builders are partial.
#include "types.h"

// ---------------------------------------------------------------------------
// small helpers
// ---------------------------------------------------------------------------

// @ 0x00729430 — enum -> canonical id (A)
int FUN_00729430(int a)
{
    switch (a) {
    case 2:
    case 0x12: return 2;
    case 3:
    case 5:  return 5;
    case 4:  return 6;
    case 6:
    case 7:
    case 8:
    case 9:
    case 0xa:
    case 0xb:
    case 0xc:
    case 0xd: return 8;
    case 0xe: return 9;
    case 0xf: return 10;
    case 0x13: return 3;
    case 0x14: return 4;
    case 0:  return 1;
    case 1:  return 1;
    case 0x10: return 1;
    case 0x11: return 1;
    case 0x15: return 1;
    default:  return 1;
    }
}

// @ 0x007294d0 — enum -> canonical id (B)
int FUN_007294d0(int a)
{
    switch (a) {
    case 0:  return 1;
    case 1:  return 2;
    case 2:  return 3;
    case 3:  return 4;
    case 4:  return 5;
    case 5:  return 7;
    case 8:  return 0xa;
    case 6:  return 8;
    case 7:  return 9;
    case 9:  return 0xb;
    case 10: return 0xc;
    default: return 0;
    }
}

// @ 0x00729560 — enum -> canonical id (C)
int FUN_00729560(int a)
{
    switch (a) {
    case 1:  return 0;
    case 2:  return 1;
    case 3:  return 2;
    case 4:  return 3;
    case 5:  return 4;
    default: return -1;
    case 7:  return 5;
    case 10: return 8;
    case 8:  return 6;
    case 9:  return 7;
    case 0xb: return 9;
    case 0xc: return 10;
    }
}

// @ 0x007295f0 — (enum, sub) -> canonical id
int FUN_007295f0(int a, int b)
{
    switch (a) {
    case 1:
        if (b == 0) return 0;
        break;
    case 2:
        if (b == 0) return 2;
        break;
    case 8:
        if (b < 8) return b + 6;
        break;
    case 3:
        if (b == 0) return 0x13;
        break;
    case 5:
    case 7:
        if (b == 0) return 3;
        if (b == 1) return 5;
        break;
    case 6:
        if (b == 0) return 4;
        break;
    case 9:
        if (b == 0) return 0xe;
        break;
    case 10:
        if (b == 0) return 0xf;
        break;
    case 0xb:
        return 0x16;
    case 0xc:
        if (b == 0) return 0x11;
        break;
    case 0xd:
        if (b == 0) return 0x12;
    }
    return -1;
}

// @ 0x00729820 — initialise a descriptor (13 dwords). PMeshType ctor.
struct C29820 {
    int   f0;
    int   f1;
    float f2, f3, f4, f5, f6, f7;
    int   f8, f9, f10, f11, f12;
    C29820* Init(int a, float* b, int c, int d);
};

C29820* C29820::Init(int a, float* b, int c, int d)
{
    f0 = a;
    f1 = 0;
    f2 = b[0];
    f3 = b[1];
    f4 = b[2];
    f5 = b[3];
    f6 = b[4];
    f7 = b[5];
    f8 = c;
    f9 = d;
    f10 = 0;
    f11 = 0;
    f12 = 0;
    return this;
}

// @ 0x00729ad0 — find the element (stride 0xc) whose [lo,hi) contains x.
struct C29ad0 {
    char* mpBegin;   // +0
    char* mpEnd;     // +4
    int   Find(int x);
};

int C29ad0::Find(int x)
{
    int* p = (int*)mpBegin;
    int  n = (int)(mpEnd - mpBegin) / 0xc;
    int  i = 0;
    if (0 < n) {
        do {
            if (p[1] <= x && x < p[2])
                return p[0];
            i++;
            p += 3;
        } while (i < n);
    }
    return -1;
}

// @ 0x00729870 — recursively unlink two child lists onto a global free list.
extern "C" void* g_162b1f0;
struct C29a70 {
    char   pad[0x2c];
    C29a70* mp2c;   // +0x2c
    C29a70* mp30;   // +0x30
    void Free();
};

void C29a70::Free()
{
    if (mp2c) {
        mp2c->Free();
        C29a70* n = mp2c;
        *(void**)n = g_162b1f0;
        g_162b1f0 = n;
    }
    if (mp30) {
        mp30->Free();
        C29a70* n = mp30;
        *(void**)n = g_162b1f0;
        g_162b1f0 = n;
    }
}

// @ 0x007296e0 — copy `rows` rows of dword data from src to dst with independent strides.
void FUN_007296e0(int* dst, int* src, int rows)
{
    int      srcBase   = src[1];
    int*     d         = (int*)dst[0];
    unsigned dstStride = (unsigned)dst[1];
    unsigned srcStride = *(unsigned short*)((char*)src + 10);
    unsigned count     = *(unsigned short*)((char*)src + 8) >> 2;
    for (; rows > 0; --rows) {
        int* s = (int*)srcBase;
        for (unsigned i = 0; i < count; ++i)
            d[i] = s[i];
        srcBase += (int)(srcStride >> 2) * 4;
        d = (int*)((char*)d + (dstStride & 0xfffffffc));
    }
}

// @ 0x00729760 — like FUN_007296e0 but the source row is selected through a mask table.
extern const unsigned int DAT_0140d15c[];
void FUN_00729760(int* dst, int* src, int* sel, int rows)
{
    if (sel[1] == 0) {
        FUN_007296e0(dst, src, rows);
        return;
    }
    int      srcBase   = src[1];
    int*     d         = (int*)dst[0];
    unsigned dstStride = (unsigned)dst[1];
    unsigned srcStride = *(unsigned short*)((char*)src + 10);
    unsigned count     = *(unsigned short*)((char*)src + 8) >> 2;
    unsigned mask      = DAT_0140d15c[*(unsigned short*)((char*)sel + 8)];
    for (int row = 0; row < rows; ++row) {
        unsigned idx = *(unsigned int*)((char*)sel[1] + *(unsigned short*)((char*)sel + 10) * row);
        int* s = (int*)(srcBase + (int)((mask & idx) * (srcStride >> 2) * 4));
        for (unsigned i = 0; i < count; ++i)
            d[i] = s[i];
        d = (int*)((char*)d + (dstStride & 0xfffffffc));
    }
}

// ---------------------------------------------------------------------------
// large functions (partial)
// ---------------------------------------------------------------------------

// @ 0x00728c90  SP::CreateUVsAndCharts  (PARTIAL)
void FUN_00728c90(void* self, int a, int b, int c, int d)
{
    (void)self; (void)a; (void)b; (void)c; (void)d;
}

// @ 0x00729290  (PARTIAL)
int FUN_00729290(void* self)
{
    (void)self;
    return 1;
}

// @ 0x00729300  (PARTIAL)
int FUN_00729300(int a, int b, int* c, int d, int e, int f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    return 0;
}

// @ 0x007298b0  (PARTIAL: x87 area/size helper)
double FUN_007298b0(float* a, int b)
{
    (void)a; (void)b;
    return 0.0;
}

// @ 0x00729990  (PARTIAL)
int FUN_00729990(void* a, void* b)
{
    (void)a; (void)b;
    return 0;
}

// @ 0x00729b20  (PARTIAL: VertexBuffer lock/copy)
int* FUN_00729b20(void* vb, int* a, int* b)
{
    (void)vb; (void)a; (void)b;
    return 0;
}
