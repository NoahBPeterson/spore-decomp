// src/game/SPTerrain/_at_00f90000.cpp -- migrated from slice(s) s00f927c0, s00f918d0 by tools/migrate/rewrite.py
// Object file: SPTerrain/_at_00f90000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cTerrainMapBase.h"
#include "SP/cTerrainMapSet.h"
#include "SP/cTerrainStateMgr.h"
#include <new>
#include <math.h>

// ---- items of slice s00f918d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void operator delete[](void* p) throw();                                  // 0x00f47380
void* __cdecl MemCopy(void* dst, const void* src, unsigned n);            // 0x011e0744 (memmove thunk)
namespace SP {
 int __cdecl WrapCubeFace(int size, int* face, int* x, int* y, int a, int b);   // 0x00684ca0
}
static inline void FreeBlock(void* p) {
    if (p && ((int*)p)[-1] != 0) operator delete[](p);
}
struct ByteVec {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    ByteVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    void DoInsertValues(char* pos, unsigned n, const char& v);            // 0x004c10e0
    void Fit(unsigned sz) {
        if ((unsigned)(mpEnd - mpBegin) < sz) {
            char zero = 0;
            DoInsertValues(mpEnd, sz - (unsigned)(mpEnd - mpBegin), zero);
        } else {
            MemCopy(mpBegin + sz, mpEnd, 0);
            mpEnd = mpBegin + sz;
        }
    }
};
struct CubeMapBuffer {
    char pad0[8];
    int mSize;        // +0x08 texels per face edge
    char pad1[4];
    uint8_t* mpData;     // +0x10 six faces of mSize*mSize bytes
    uint8_t* mpDataEnd;  // +0x14 byte-vector end
    uint8_t* mpDataCap;  // +0x18 byte-vector capacity
    void SmoothEdges();                // 0x00f918d0
    void SetSize(int size, int fill); // 0x00f921d0
};
static inline uint8_t Sample(CubeMapBuffer* self, int face, int x, int y)
{
    int n = self->mSize;
    int f = face, a = x, b = y;
    if (((a | b) & ~(n - 1)) != 0)
        SP::WrapCubeFace(n, &f, &a, &b, 0, 0);
    return self->mpData[(n * f + b) * n + a];
}
static inline uint8_t Blend(CubeMapBuffer* self, int face, int x1, int y1, int x2, int y2)
{
    uint8_t a = Sample(self, face, x1, y1);
    uint8_t b = Sample(self, face, x2, y2);
    return (uint8_t)((a * 2 + b) / 3);
}
struct PairSink {
    char pad0[0x50];
    uint32_t mValue0;    // +0x50
    uint32_t mValue1;    // +0x54
    void Set(const uint32_t* p);   // 0x00f92520
};
// ---- items of slice s00f918d0 end

// @ 0x00f918d0
void CubeMapBuffer::SmoothEdges()
{
    int n = mSize;
    int nn = n * n;
    ByteVec tmp;
    tmp.Fit(nn * 6);
    char* const begin = tmp.mpBegin;
    char* const p38 = begin + (n - 1) * n;
    char* p3c = begin + n;
    char* const p1c = begin + nn - 1;
    char* const p20 = p3c;
    int o44 = 0;
    for (int face = 0; face < 6; ++face) {
        char* q = p3c;
        for (int y = 1; y < n - 1; ++y) {
            q[0] = Blend(this, face, 1, y, -2, y);
            q[n - 1] = Blend(this, face, n - 2, y, n + 1, y);
            q += n;
        }
        char* top = begin + o44;
        char* bot = p38 + o44;
        for (int x = 1; x < n - 1; ++x) {
            top[x] = Blend(this, face, x, 1, x, -2);
            bot[x] = Blend(this, face, x, n - 2, x, n + 1);
        }
        begin[o44] = Blend(this, face, 1, 1, -2, -2);
        p20[o44 - 1] = Blend(this, face, n - 2, 1, n + 1, -2);
        p38[o44] = Blend(this, face, 1, n - 2, -2, n + 1);
        p1c[o44] = Blend(this, face, n - 2, n - 2, n + 1, n + 1);
        p3c += nn;
        o44 += nn;
    }
    for (int face = 0; face < 6; ++face) {
        int off = face * nn;
        for (int i = 0; i < n; ++i) {
            mpData[off + i * n] = tmp.mpBegin[off + i * n];
            mpData[off + i * n + n - 1] = tmp.mpBegin[off + i * n + n - 1];
        }
        for (int x = 1; x < n - 1; ++x) {
            mpData[off + x] = tmp.mpBegin[off + x];
            mpData[off + (n - 1) * n + x] = tmp.mpBegin[off + (n - 1) * n + x];
        }
    }
    MemCopy(tmp.mpBegin, tmp.mpEnd, 0);
    FreeBlock(tmp.mpBegin);
}

// @ 0x00f92520
void PairSink::Set(const uint32_t* p)
{
    mValue0 = p[0];
    mValue1 = p[1];
}

// @ 0x00f93190
bool __stdcall TerrainMapSetCheck(void* p)
{
    if (*(int*)((char*)p + 4) != 0xb1b104)
        return false;
    unsigned int v = *(unsigned int*)((char*)p + 8);
    return (v & 0xff0000) == 0x840000
        && (v & 0x1f000000) == 0
        && (unsigned char)v == 0
        && ((v >> 8) & 0xff) >= 0xa1
        && ((v >> 8) & 0xff) <= 0xb3;
}
