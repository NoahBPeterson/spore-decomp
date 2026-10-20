// Slice s00f87b30 -- SP::cTerrainMap<T> helpers (SPTerrain/SPTerrainMap.obj).
// Cube-map: 6 faces of mFaceSize x mFaceSize packed elements, stored in the eastl::vector
// mMapData (mpBegin at +0x10).  mFaceSize at +8.  A cube coordinate is (col, row, face).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

int __cdecl SP_WrapCubeFace(int n, int* face, int* x, int* y, int* u, int* v);  // 0x00684ca0
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);    // 0x011e0744 thunk

namespace SP {

struct cCubeMapIndex { int mCol; int mRow; int mFace; };
struct cSPVector3 { float x, y, z; };

struct cTerrainMapBase {
    void* mVftable;        // +0x00
    int mnRefCount;        // +0x04
    unsigned mFaceSize;    // +0x08
    unsigned mModCount;    // +0x0c
};

template <class T> struct cTerrainMap : cTerrainMapBase {
    T* mBegin;             // +0x10 (eastl::vector<T>::mpBegin)
    T* mEnd;
    T* mCap;

    void SetCell(const cCubeMapIndex& c, T v);
    int  GetRelativeIndex(int face, int x, int y, int dx, int dy);
    void Convolve(int face, int x, int y, float* dst, const float* k, int unused);
    void DownSampleMap(const cTerrainMap& src);
    void CopyMap(const cTerrainMap& src);
};

}  // namespace SP

using SP::cCubeMapIndex;
using SP::cSPVector3;
using SP::cTerrainMap;

// @ 0x00f87b30
template <> void cTerrainMap<float>::SetCell(const cCubeMapIndex& c, float v)
{
    mBegin[(c.mFace * (int)mFaceSize + c.mRow) * (int)mFaceSize + c.mCol] = v;
}

// @ 0x00f87b60
template <> int cTerrainMap<float>::GetRelativeIndex(int face, int x, int y, int dx, int dy)
{
    int size = (int)mFaceSize;
    y += dy;
    x += dx;
    if ((~(size - 1)) & (x | y))
        SP_WrapCubeFace(size, &face, &x, &y, 0, 0);
    return (size * face + y) * size + x;
}

// @ 0x00f87bd0
template <> void cTerrainMap<cSPVector3>::SetCell(const cCubeMapIndex& c, cSPVector3 v)
{
    mBegin[(c.mFace * (int)mFaceSize + c.mRow) * (int)mFaceSize + c.mCol] = v;
}

namespace SP {

// Saturation helpers.  Kept out-of-line so the caller touches only xmm0 for each argument
// (the original writes only xmm0..xmm3; an LTCG caller may keep a live value in xmm4..xmm7).
static __declspec(noinline) unsigned char SatRgb(float x)
{
    __m128 v = _mm_set_ss(x);
    v = _mm_add_ss(v, _mm_set_ss(1.0f));
    v = _mm_mul_ss(v, _mm_set_ss(0.5f));
    v = _mm_max_ss(_mm_setzero_ps(), v);
    v = _mm_mul_ss(v, _mm_set_ss(255.0f));
    v = _mm_min_ss(v, _mm_set_ss(255.0f));
    return (unsigned char)_mm_cvtss_si32(v);
}

static __declspec(noinline) unsigned char SatA(float x)
{
    __m128 v = _mm_set_ss(x);
    v = _mm_max_ss(_mm_setzero_ps(), v);
    v = _mm_mul_ss(v, _mm_set_ss(255.0f));
    v = _mm_min_ss(v, _mm_set_ss(255.0f));
    return (unsigned char)_mm_cvtss_si32(v);
}

// @ 0x00f87c10
uint32_t __cdecl Direction4fToDirection4c(const float* v)
{
    unsigned char r = SatRgb(v[0]);
    unsigned char g = SatRgb(v[1]);
    unsigned char b = SatRgb(v[2]);
    unsigned char a = SatA(v[3]);
    return ((((unsigned)a << 8) | b) << 8 | g) << 8 | r;
}

}  // namespace SP

// @ 0x00f87d20
template <> void cTerrainMap<float>::Convolve(int face, int x, int y, float* dst, const float* k, int)
{
    int size = (int)mFaceSize;
    int centre = (size * face + y) * size + x;

    int i2 = GetRelativeIndex(face, x, y, -1, -1);
    int i3 = GetRelativeIndex(face, x, y, 0, -1);
    int i4 = GetRelativeIndex(face, x, y, 1, -1);
    int i5 = GetRelativeIndex(face, x, y, -1, 0);
    int i6 = GetRelativeIndex(face, x, y, 1, 0);
    int i7 = GetRelativeIndex(face, x, y, -1, 1);
    int i8 = GetRelativeIndex(face, x, y, 0, 1);
    int i9 = GetRelativeIndex(face, x, y, 1, 1);

    float sum = mBegin[i3] * k[1] + mBegin[i2] * k[0];
    sum += mBegin[i4] * k[2];
    sum += mBegin[i5] * k[3];
    sum += mBegin[centre] * k[4];
    sum += mBegin[i6] * k[5];
    sum += mBegin[i7] * k[6];
    sum += mBegin[i8] * k[7];
    sum += mBegin[i9] * k[8];
    dst[centre] = sum;
}

// @ 0x00f87ea0
template <> void cTerrainMap<float>::DownSampleMap(const cTerrainMap<float>& src)
{
    int dstSize = (int)mFaceSize;
    int srcSize = (int)src.mFaceSize;
    int ratio = srcSize / dstSize;
    if (ratio <= 1 || srcSize % dstSize != 0)
        return;
    for (int face = 0; face < 6; ++face)
    {
        const float* sp = src.mBegin + srcSize * srcSize * face;
        float* dp = mBegin + dstSize * dstSize * face;
        float inv = 1.0f / (float)(ratio * ratio);
        for (int y = 0; y < dstSize; ++y)
        {
            for (int x = 0; x < dstSize; ++x)
            {
                float total = 0.0f;
                for (int j = 0; j < ratio; ++j)
                {
                    const float* row = sp + (y * ratio + j) * srcSize + x * ratio;
                    float evens = 0.0f, odds = 0.0f;
                    int i = 0;
                    for (; i + 1 < ratio; i += 2)
                    {
                        evens += row[i];
                        odds += row[i + 1];
                    }
                    if (i < ratio)
                        total += row[i];
                    total = (evens + odds) + total;
                }
                *dp++ = inv * total;
            }
        }
    }
}

// @ 0x00f88090
void __cdecl FaceTangentBasis(float* out, int face, float t, float b, float u, float v)
{
    volatile float xyz[3];
    switch (face)
    {
    case 0: xyz[0] = -u; xyz[1] = -v; xyz[2] =  1.0f; break;
    case 1: xyz[0] = -u; xyz[1] =  v; xyz[2] = -1.0f; break;
    case 2: xyz[0] =  1.0f; xyz[1] = -u; xyz[2] = -v; break;
    case 3: xyz[0] = -1.0f; xyz[1] =  u; xyz[2] = -v; break;
    case 4: xyz[0] =  u; xyz[1] =  1.0f; xyz[2] = -v; break;
    case 5: xyz[0] = -u; xyz[1] = -1.0f; xyz[2] = -v; break;
    }
    float x = xyz[0], y = xyz[1], z = xyz[2];
    float inv = (float)(1.0 / sqrt((double)z * z + (double)y * y + (double)x * x + 1.0e-8));
    float nx = inv * x;
    float ny = inv * y;
    float nz = inv * z;
    float f6 = ny * 0.0f - -x * nz;
    float f2 = -x * nx - ny * y;
    float f7 = nz * y - nx * 0.0f;
    float f1 = (float)(1.0 / sqrt((double)f6 * f6 + ((double)f7 * f7 + (double)f2 * f2) + 1.0e-8));
    f6 = f1 * f6;
    f7 = f7 * f1;
    f2 = f2 * f1;
    out[0] = f7 * nz - f2 * ny;
    out[1] = f2 * nx - f6 * nz;
    out[2] = f6 * ny - f7 * nx;
    out[0] = out[0] * t + f6 * b;
    out[1] = out[1] * t + f7 * b;
    out[2] = out[2] * t + f2 * b;
}

// @ 0x00f88360
template <> void cTerrainMap<float>::CopyMap(const cTerrainMap<float>& src)
{
    if (src.mFaceSize != mFaceSize)
        return;
    __m128* d = (__m128*)mBegin;
    const __m128* s = (const __m128*)src.mBegin;
    unsigned n = (mFaceSize * mFaceSize * 6 * sizeof(float)) >> 4;   // 16-byte units
    for (unsigned i = 0; i < n; i += 8)
    {
        d[i + 0] = s[i + 0];
        d[i + 1] = s[i + 1];
        d[i + 2] = s[i + 2];
        d[i + 3] = s[i + 3];
        d[i + 4] = s[i + 4];
        d[i + 5] = s[i + 5];
        d[i + 6] = s[i + 6];
        d[i + 7] = s[i + 7];
    }
}

// @ 0x00f88400
template <> void cTerrainMap<cSPVector3>::CopyMap(const cTerrainMap<cSPVector3>& src)
{
    if (src.mFaceSize != mFaceSize)
        return;
    __m128* d = (__m128*)mBegin;
    const __m128* s = (const __m128*)src.mBegin;
    unsigned n = (mFaceSize * mFaceSize * 6 * sizeof(cSPVector3)) >> 4;
    for (unsigned i = 0; i < n; i += 8)
    {
        d[i + 0] = s[i + 0];
        d[i + 1] = s[i + 1];
        d[i + 2] = s[i + 2];
        d[i + 3] = s[i + 3];
        d[i + 4] = s[i + 4];
        d[i + 5] = s[i + 5];
        d[i + 6] = s[i + 6];
        d[i + 7] = s[i + 7];
    }
}

// @ 0x00f884a0
bool __cdecl IntersectRaySphere(const float* orig, const float* dir, float radius, float* t0, float* t1)
{
    float a = dir[0] * dir[0] + dir[2] * dir[2] + dir[1] * dir[1];
    float c = orig[0] * orig[0] + orig[2] * orig[2] + orig[1] * orig[1];
    float b = dir[0] * orig[0] + dir[2] * orig[2] + dir[1] * orig[1];
    float disc = b * b - a * (c - radius * radius);
    if (disc < 0.0f)
        return false;
    if (disc > 0.0f)
    {
        float s = (float)sqrt((double)disc);
        float inv = 1.0f / a;
        *t0 = (-b - s) * inv;
        *t1 = (s - b) * inv;
        return true;
    }
    *t0 = -(b / a);
    *t1 = -(b / a);
    return true;
}

// @ 0x00f885b0
void ToVector3(float* out, unsigned c)
{
    out[0] = (float)(c & 0xff);
    out[1] = (float)((c >> 8) & 0xff);
    out[2] = (float)((c >> 16) & 0xff);
}

// @ 0x00f885f0
void ToVector4(float* out, unsigned c)
{
    out[0] = (float)(c & 0xff);
    out[1] = (float)((c >> 8) & 0xff);
    out[2] = (float)((c >> 16) & 0xff);
    out[3] = (float)(c >> 24);
}
