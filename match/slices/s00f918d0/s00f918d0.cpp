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
    uint8_t* mpData;     // +0x10 six faces of mSize*mSize bytes
    uint8_t* mpDataEnd;  // +0x14 byte-vector end
    uint8_t* mpDataCap;  // +0x18 byte-vector capacity
    void SmoothEdges();                // 0x00f918d0
    void SetSize(int size, int fill); // 0x00f921d0
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

// ---------------------------------------------------------------------------
// Cube-map face construction from an RGBA texture, plus the byte-vector resize
// and the height-range pyramid that share this slice.

struct F1 { float f; };
extern F1 g145c3ec;      // 0x0145c3ec  0.007843138f
extern F1 g1470f1c;      // 0x01470f1c  2.0f
extern F1 g1485720;      // 0x01485720  1.0f

void* __cdecl operator new[](unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void __cdecl FaceTangentBasis(float* out, int face, float r, float g, float b, float a); // 0x00f88090

struct FaceBasis { int mValues[6]; };
extern FaceBasis g015b0ef0[6];      // 0x015b0ef0  per-face coefficient table
extern const uint8_t g01491464[16]; // 0x01491464  nibble-expansion table

// Byte vector at CubeMapBuffer+0x10 (element size 1).
struct CubeMapVec {
    uint8_t* mpBegin;    // +0x10
    uint8_t* mpEnd;      // +0x14
    uint8_t* mpCap;      // +0x18
    void DoInsertValues(uint8_t* pos, unsigned n, const char* v);  // 0x00f8f330
    void Fit(unsigned sz, const char* fill) {
        if ((unsigned)(mpEnd - mpBegin) < sz) {
            DoInsertValues(mpEnd, sz - (unsigned)(mpEnd - mpBegin), fill);
        } else {
            MemCopy(mpBegin + sz, mpEnd, 0);
            mpEnd = mpBegin + sz;
        }
    }
};

// @ 0x00f921d0
void CubeMapBuffer::SetSize(int size, int fill)
{
    mSize = size;
    CubeMapVec* v = (CubeMapVec*)&mpData;
    v->Fit(0, 0);
    v->Fit((unsigned)(size * size * 6), (const char*)&fill);
}

// 12-byte element vector at CubeMapBuildTarget+0x10 (element size 0xc).
struct Vec3Array {
    uint8_t* mpBegin;    // +0x10
    uint8_t* mpEnd;      // +0x14
    uint8_t* mpCap;      // +0x18
    void Fit(unsigned count);   // 0x00f8fdf0
};

struct CubeMapBuildTarget {
    char pad0[8];
    int mSize;           // +0x08
    char pad1[4];
    Vec3Array mData;     // +0x10
};

// @ 0x00f922b0
bool __cdecl CubeMapBuild(CubeMapBuildTarget* pBuf, const uint8_t* pTexels, int stride)
{
    int n = stride / 4;
    if (pBuf->mSize != n) {
        pBuf->mSize = n;
        pBuf->mData.Fit((unsigned)(n * n * 6));
    }
    n = pBuf->mSize;
    const float one = g1485720.f;
    const float scale = g145c3ec.f;
    int faceOff = 0;
    const FaceBasis* entry = g015b0ef0;
    for (int face = 0; face < 6; ++face, ++entry) {
        uint8_t* pFace = pBuf->mData.mpBegin + faceOff;
        if (n > 0) {
            float f = g1470f1c.f / (float)(n - 1);
            for (int y = 1; y <= n; ++y) {
                for (int x = 1; x <= n; ++x) {
                    int a = entry->mValues[2] * x + entry->mValues[3] * y;
                    int b = entry->mValues[4] * x + entry->mValues[5] * y;
                    if (a < 0) a += n + 1;
                    if (b < 0) b += n + 1;
                    int row = entry->mValues[1] * n + y - 1;
                    int col = entry->mValues[0] * n + x - 1;
                    const uint8_t* texel = pTexels + (row * stride + col) * 4;
                    float* out = (float*)(pFace + ((b - 1) * n + a - 1) * 12);
                    float fc = (float)(col % n) * f - one;
                    float fr = (float)(row % n) * f - one;
                    FaceTangentBasis(out, face,
                                     (float)texel[2] * scale - one,
                                     (float)texel[1] * scale - one,
                                     fc, fr);
                    float alpha = (float)texel[3] * scale;
                    out[0] *= alpha;
                    out[1] *= alpha;
                    out[2] *= alpha;
                }
            }
        }
        faceOff += n * n * 12;
    }
    return true;
}

// Height-range cell pyramid: six cumulative level counts then the cell array.
struct HRCell { uint16_t mLo; uint16_t mHi; };
struct HRSource { uint16_t mWords[8]; };

struct HeightRanges {
    int mCounts[6];      // +0x00
    HRCell* mpData;      // +0x18
    HeightRanges* Init();                                             // 0x00f92540
    int Merge(int level, int index, int x0, int y0, int x1, int y1);  // 0x00f925b0
};

// @ 0x00f92540
HeightRanges* HeightRanges::Init()
{
    mCounts[0] = 0x555;
    mpData = 0;
    int n = 0x1ffe;
    mpData = new ("Terrain/HeightRanges/cCell", 0, 0, 0, 0) HRCell[n];
    mCounts[1] = 1;
    mCounts[2] = 5;
    mCounts[3] = 0x15;
    mCounts[4] = 0x55;
    mCounts[5] = 0x155;
    return this;
}

// @ 0x00f925b0
int HeightRanges::Merge(int level, int index, int x0, int y0, int x1, int y1)
{
    const int y1Raw = y1;
    x0 /= 2;
    x1 /= 2;
    y0 /= 2;
    y1 /= 2;
    if (x0 == x1)
        return y1Raw + (y1Raw < 0 ? 1 : 0);
    int* p = mCounts + level + 2;
    int ret = level;
    do {
        if (y0 == y1)
            return ret;
        HRCell* pA = mpData + (p[-1] + mCounts[0] * index);
        HRSource* pB = (HRSource*)(mpData + (p[0] + mCounts[0] * index));
        int changed = 0;
        if (y0 >= y1)
            return y0;
        for (int y = y0; y < y1; ++y) {
            if (x0 < x1) {
                const uint8_t* pYHi = &g01491464[y >> 4];
                const uint8_t* pYLo = &g01491464[y & 0xf];
                for (int x = x0; x < x1; ++x) {
                    unsigned xHi = g01491464[x >> 4];
                    unsigned xLo = g01491464[x & 0xf];
                    unsigned idx = ((xHi | (*pYHi << 1)) << 7 | *pYLo) * 2 | xLo;
                    HRSource* src = pB + idx;
                    HRCell* dst = pA + idx;
                    uint16_t lo = src->mWords[0];
                    uint16_t hi = src->mWords[1];
                    if (lo > src->mWords[2]) lo = src->mWords[2];
                    if (hi < src->mWords[3]) hi = src->mWords[3];
                    if (lo > src->mWords[4]) lo = src->mWords[4];
                    if (hi < src->mWords[5]) hi = src->mWords[5];
                    if (lo > src->mWords[6]) lo = src->mWords[6];
                    if (hi < src->mWords[7]) hi = src->mWords[7];
                    if (dst->mLo != lo || dst->mHi != hi) {
                        ++changed;
                        dst->mLo = lo;
                        dst->mHi = hi;
                    }
                }
            }
        }
        if (changed == 0)
            return y1;
        if (level <= 0)
            return y1;
        x0 /= 2;
        --level;
        --p;
        y0 /= 2;
        x1 /= 2;
        y1 /= 2;
        ret = y1;
    } while (x0 != x1);
    return y1;
}

// Two-dword setter on a larger object (values live at +0x50/+0x54).
struct PairSink {
    char pad0[0x50];
    uint32_t mValue0;    // +0x50
    uint32_t mValue1;    // +0x54
    void Set(const uint32_t* p);   // 0x00f92520
};

// @ 0x00f92520
void PairSink::Set(const uint32_t* p)
{
    mValue0 = p[0];
    mValue1 = p[1];
}
