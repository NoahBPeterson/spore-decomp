// Slice s00a75dd0 — EA::Swarm::cMapInfo (MapInfo component), second batch.
// Sample* / Init* helpers reached through the component and owner vtables.
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "s00a75dd0.h"
#include <math.h>
#include <xmmintrin.h>

// The retail build inlined sqrt() (x87 fsqrt) and the EA math clamp helpers
// (SSE maxss/minss, which map NaN to the bound) instead of emitting calls.
#pragma intrinsic(sqrt)

namespace EA { namespace Swarm {

// Inline [0,1] clamp as the original does it: maxss/minss, so a NaN input
// yields 0 (the second operand) rather than propagating.
static __forceinline float Clamp01(float v)
{
    __m128 x = _mm_set_ss(v);
    x = _mm_max_ss(x, _mm_setzero_ps());
    x = _mm_min_ss(x, _mm_set_ss(1.0f));
    return _mm_cvtss_f32(x);
}

// ---------------------------------------------------------------------------
// @ 0x00a75dd0  cMapInfo::SampleColorClamp
// Bilinear colour fetch; the result is scaled by 1/254 and RGB clamped to [0,1].
// ---------------------------------------------------------------------------
void cMapInfo::SampleColorClamp(float* out, const float* p)
{
    int cx, cy;
    float fx, fy;
    MapToCell(p[0], p[1], &cx, &cy, &fx, &fy);

    float a[4], b[4], c[4], d[4];
    UnpackColor(a, cx, cy);
    UnpackColor(b, cx, cy + 1);
    for (int i = 0; i < 4; ++i)
        b[i] = (b[i] - a[i]) * fx + a[i];

    UnpackColor(c, cx + 1, cy);
    UnpackColor(d, cx + 1, cy + 1);
    for (int i = 0; i < 4; ++i)
        out[i] = ((((d[i] - c[i]) * fx + c[i]) - b[i]) * fy + b[i]) * (1.0f / 254.0f);

    for (int i = 0; i < 3; ++i)
        out[i] = Clamp01(out[i]);
}

// ---------------------------------------------------------------------------
// @ 0x00a76070  cMapInfo::Init11 (palette id 0xb, fallback table 0x014575d8)
// ---------------------------------------------------------------------------
void cMapInfo::Init11(const float* rect, int a2, int a3, uint8_t a4, IcOwner* owner, uint8_t a6)
{
    mbWrap3c = a6;
    mMinX = rect[0];
    mMinY = rect[1];
    mMaxX = rect[2];
    mMaxY = rect[3];
    mbWrap1c = a4;
    mpOwner38 = owner;
    bool ok = owner->v14(0xb, a2, a3, &mpGrid);
    mbValid34 = ok;
    if (!ok) {
        m20 = 2;
        m24 = 2;
        mpPixels40 = (uint32_t*)0x014575d8;
        mScaleX = 1.0f / (mMaxX - mMinX);
        mScaleY = 1.0f / (mMaxY - mMinY);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a76110  cMapInfo::SampleAlpha
// Bilinear fetch of the alpha byte (pixel +3) with the m20 stride.
// ---------------------------------------------------------------------------
float cMapInfo::SampleAlpha(const float* p)
{
    int cx, cy;
    float fx, fy;
    MapToCell(p[0], p[1], &cx, &cy, &fx, &fy);

    const uint8_t* q = (const uint8_t*)mpPixels40;
    int stride = (int)m20;
    int i0 = stride * cy + cx;
    int i1 = stride * (cy + 1) + cx;

    float A = (float)q[i0 * 4 + 3];
    float B = (float)q[i0 * 4 + 7];
    float C = (float)q[i1 * 4 + 3];
    float D = (float)q[i1 * 4 + 7];

    float R = (C - A) * fx + A;
    float S = (D - B) * fx + B;
    return (R + (S - R) * fy) * (1.0f / 255.0f);
}

// ---------------------------------------------------------------------------
// @ 0x00a761d0  cMapInfo::SampleDir
// Calls vtable slot 0x2c for a unit-direction vector and remaps it to [-1,1].
// ---------------------------------------------------------------------------
void cMapInfo::SampleDir(float* out, uint32_t a)
{
    float v[4];
    ((void (__thiscall*)(cMapInfo*, float*, uint32_t))(*(void***)this)[0x2c / 4])(this, v, a);
    out[0] = v[0] * 2.0f - 1.0f;
    out[1] = v[1] * 2.0f - 1.0f;
    out[2] = v[2] * 2.0f - 1.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00a76240  cMapInfo::SampleColor
// Bilinear colour fetch scaled by 1/255 (no clamping).
// ---------------------------------------------------------------------------
void cMapInfo::SampleColor(float* out, const float* p)
{
    int cx, cy;
    float fx, fy;
    MapToCell(p[0], p[1], &cx, &cy, &fx, &fy);

    float a[4], b[4], c[4], d[4];
    UnpackColor(a, cx, cy);
    UnpackColor(b, cx, cy + 1);
    for (int i = 0; i < 4; ++i)
        b[i] = (b[i] - a[i]) * fx + a[i];

    UnpackColor(c, cx + 1, cy);
    UnpackColor(d, cx + 1, cy + 1);
    for (int i = 0; i < 4; ++i)
        out[i] = ((((d[i] - c[i]) * fx + c[i]) - b[i]) * fy + b[i]) * (1.0f / 255.0f);
}

// ---------------------------------------------------------------------------
// @ 0x00a76420  cMapInfo::Init9 (palette id 9, fallback table 0x014575d4)
// ---------------------------------------------------------------------------
void cMapInfo::Init9(const float* rect, int a2, int a3, uint8_t a4, IcOwner* owner, uint8_t a6)
{
    mbWrap3c = a6;
    mMinX = rect[0];
    mMinY = rect[1];
    mMaxX = rect[2];
    mMaxY = rect[3];
    mbWrap1c = a4;
    mpOwner38 = owner;
    bool ok = owner->v14(9, a2, a3, &mpGrid);
    mbValid34 = ok;
    if (!ok) {
        m20 = 2;
        m24 = 2;
        mpPixels40 = (uint32_t*)0x014575d4;
        mScaleX = 1.0f / (mMaxX - mMinX);
        mScaleY = 1.0f / (mMaxY - mMinY);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a764c0  cMapInfo::SampleBit
// Bilinear fetch of one bit of the packed grid; thresholded at 0.5.
// ---------------------------------------------------------------------------
float cMapInfo::SampleBit(const float* p)
{
    int cx, cy;
    float fx, fy;
    MapToCell(p[0], p[1], &cx, &cy, &fx, &fy);

    const uint8_t* q = (const uint8_t*)mpPixels40;
    int stride = m44;
    int row0 = stride * cy;
    int row1 = stride * (cy + 1);

    float A = (float)((q[row0 + (cx >> 3)] >> (cx & 7)) & 1);
    float B = (float)((q[row1 + (cx >> 3)] >> (cx & 7)) & 1);
    int c1 = cx + 1;
    float C = (float)((q[row0 + (c1 >> 3)] >> (c1 & 7)) & 1);
    float D = (float)((q[row1 + (c1 >> 3)] >> (c1 & 7)) & 1);

    float R = (B - A) * fx + A;
    float S = (D - C) * fx + C;
    return ((S - R) * fy + R) > 0.5f ? 1.0f : 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00a765f0  cMapInfo::SampleNormal
// Gradient of the packed bit grid -> normalized 3-vector.
// ---------------------------------------------------------------------------
void cMapInfo::SampleNormal(float* out, const float* p)
{
    int cx, cy;
    float fx, fy;
    MapToCell(p[0], p[1], &cx, &cy, &fx, &fy);

    const uint8_t* q = (const uint8_t*)mpPixels40;
    int stride = m44;

    int cols = (int)m20;
    int rows = (int)m24;
    int c0 = cx - 1; if (c0 < 0) c0 = 0;
    int c1 = cx + 1; if (c1 >= cols - 1) c1 = cols - 1;
    int c2 = cx + 2; if (c2 >= cols - 1) c2 = cols - 1;
    int r0 = cy - 1; if (r0 < 0) r0 = 0;
    int r1 = cy + 1; if (r1 >= rows - 1) r1 = rows - 1;
    int r2 = cy + 2; if (r2 >= rows - 1) r2 = rows - 1;

#define BIT(col, row) ((float)((q[(row) * stride + ((col) >> 3)] >> ((col) & 7)) & 1))

    float A  = BIT(cx, cy);
    float B  = BIT(cx, r1);
    float C  = BIT(cx, r0);
    float L  = BIT(cx, r2);
    float D  = BIT(c1, cy);
    float E  = BIT(c1, r1);
    float F  = BIT(c1, r0);
    float J2 = BIT(c1, r2);
    float G  = BIT(c0, cy);
    float H  = BIT(c0, r1);
    float I  = BIT(c2, cy);
    float P  = BIT(c2, r1);

    float t1 = B - C;
    float t2 = ((L - A) - t1) * fy + t1;
    float t3 = E - F;
    float t4 = ((I - A) - (D - G)) * fx + (D - G);
    float t5 = E - H;

    float nx = (((((P - B) - t5) * fx + t5) - t4) * fy + t4) * mScaleX * -0.5f;
    float ny = (((((J2 - D) - t3) * fy + t3) - t2) * fx + t2) * mScaleY * -0.5f;

    out[0] = nx;
    out[1] = ny;
    out[2] = 1.0f;

    float len = 1.0f / sqrtf(out[0] * out[0] + out[1] * out[1] + out[2] * out[2]);
    out[2] = len;
    out[0] = nx * len;
    out[1] = ny * len;
#undef BIT
}

// ---------------------------------------------------------------------------
// @ 0x00a76970  cMapInfo::SampleTangent
// ---------------------------------------------------------------------------
float* cMapInfo::SampleTangent(float* out, uint32_t a)
{
    ((void (__thiscall*)(cMapInfo*, float*, uint32_t))(*(void***)this)[0x24 / 4])(this, out, a);
    out[2] = 0.0f;
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00a76990  cMapInfo::SampleScalar4
// ---------------------------------------------------------------------------
void cMapInfo::SampleScalar4(float* out, uint32_t a)
{
    float v = ((float (__thiscall*)(cMapInfo*, uint32_t))(*(void***)this)[0x20 / 4])(this, a);
    out[0] = v;
    out[1] = v;
    out[2] = v;
    out[3] = v;
}

// ---------------------------------------------------------------------------
// @ 0x00a769b0  cMapInfo::Init12 (palette id 0xc, fallback table 0x014575d4)
// ---------------------------------------------------------------------------
void cMapInfo::Init12(const float* rect, int a2, int a3, uint8_t a4, IcOwner* owner)
{
    float* dst = &mMinX;
    for (int i = 0; i < 4; ++i)
        dst[i] = rect[i];
    mbWrap1c = a4;
    mpOwner38 = owner;
    bool ok = owner->v14(0xc, a2, a3, &mpGrid);
    mbValid34 = ok;
    if (!ok) {
        m20 = 2;
        m24 = 2;
        mpPixels40 = (uint32_t*)0x014575d4;
        mScaleX = 1.0f / (mMaxX - mMinX);
        mScaleY = 1.0f / (mMaxY - mMinY);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a76a50  cMapInfo::SampleBitOriented
// ---------------------------------------------------------------------------
float cMapInfo::SampleBitOriented(const float* p)
{
    int cls;
    float u, v;
    ClassifyOrientation(p, &cls, &u, &v);

    int stride = (int)m20;
    float xf = (float)stride * u;
    int ix = (int)xf;
    if (xf < (float)ix)
        ix -= 1;
    float yf = (float)stride * v;
    int iy = (int)yf;
    if (yf < (float)iy)
        iy -= 1;

    const uint8_t* q = (const uint8_t*)mpPixels40;
    int idx = (stride * cls + iy) * m44 + (ix >> 3);
    return ((q[idx] >> (ix & 7)) & 1) > 0.5f ? 1.0f : 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00a76b30  cMapInfo::NormalizeVec3
// ---------------------------------------------------------------------------
void cMapInfo::NormalizeVec3(float* out, const float* v)
{
    float len = 1.0f / sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + 1e-9f);
    out[0] = v[0] * len;
    out[1] = v[1] * len;
    out[2] = v[2] * len;
}

// ---------------------------------------------------------------------------
// @ 0x00a76b80  cMapInfo::Init13 (palette id 0xd, fallback table 0x014575d4)
// ---------------------------------------------------------------------------
void cMapInfo::Init13(const float* rect, int a2, int a3, uint8_t a4, IcOwner* owner)
{
    float* dst = &mMinX;
    for (int i = 0; i < 4; ++i)
        dst[i] = rect[i];
    mbWrap1c = a4;
    mpOwner38 = owner;
    bool ok = owner->v14(0xd, a2, a3, &mpGrid);
    mbValid34 = ok;
    if (!ok) {
        m20 = 2;
        m24 = 2;
        mpPixels40 = (uint32_t*)0x014575d4;
        mScaleX = 1.0f / (mMaxX - mMinX);
        mScaleY = 1.0f / (mMaxY - mMinY);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a76c20  cMapInfo::SampleByteOriented
// ---------------------------------------------------------------------------
float cMapInfo::SampleByteOriented(const float* p)
{
    int cls;
    float u, v;
    ClassifyOrientation(p, &cls, &u, &v);

    int stride = (int)m20;
    float xf = (float)stride * u;
    int ix = (int)xf;
    if (xf < (float)ix)
        ix -= 1;
    float yf = (float)stride * v;
    int iy = (int)yf;
    if (yf < (float)iy)
        iy -= 1;

    const uint8_t* q = (const uint8_t*)mpPixels40;
    int idx = (stride * cls + iy) * stride + ix;
    return (float)q[idx] * (1.0f / 255.0f);
}

// ---------------------------------------------------------------------------
// @ 0x00a76cd0  cMapInfo::SampleVec3
// ---------------------------------------------------------------------------
float* cMapInfo::SampleVec3(float* out, uint32_t a)
{
    ((void (__thiscall*)(cMapInfo*, float*, uint32_t))(*(void***)this)[0x24 / 4])(this, out, a);
    return out;
}

}}
