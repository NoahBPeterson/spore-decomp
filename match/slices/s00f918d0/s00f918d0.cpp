// Slice s00f918d0: cube-map edge smoothing (blurs the border texels of each cube face using
// samples that wrap across neighbouring faces).
// Flags: /O2 /MD /Gy /EHsc /TP.
#include "types.h"

void operator delete[](void* p) throw();                                  // 0x00f47380
void* __cdecl MemCopy(void* dst, const void* src, unsigned n);            // 0x011e0744 (memmove thunk)
namespace SP { int __cdecl WrapCubeFace(int size, int* face, int* x, int* y, int a, int b); }   // 0x00684ca0

static inline void FreeBlock(void* p) {
    if (p && ((int*)p)[-1] != 0) operator delete[](p);
}

// eastl::vector<uint8_t> with the byte-vector DoInsertValues out of line.
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
    uint8_t* mpData;  // +0x10 six faces of mSize*mSize bytes
    void SmoothEdges();   // 0x00f918d0
};

// Texel at (x, y) of `face`, wrapping across cube edges when outside [0, size).
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
