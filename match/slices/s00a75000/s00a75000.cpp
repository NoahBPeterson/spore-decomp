// Slice s00a75000 — EA::Swarm "MapInfo" component.
// Reconstructed from the original disassembly (retail vftable 0x014575d4).
#include "s00a75000.h"
#include <math.h>

namespace EA { namespace Swarm {

// ---------------------------------------------------------------------------
// @ 0x00a75000  one_float  (constant 1.0f accessor)
// ---------------------------------------------------------------------------
float __stdcall cMapInfo_One(void*)
{
    return 1.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00a75010  cMapInfo::Get1c
// ---------------------------------------------------------------------------
float cMapInfo::Get1c()
{
    return (float)mbWrap1c;
}

// ---------------------------------------------------------------------------
// @ 0x00a75020  cMapInfo::MapToCell
// ---------------------------------------------------------------------------
void cMapInfo::MapToCell(float rx, float ry, int* px, int* py, float* fx, float* fy)
{
    float u = (rx - mMinX) * mScaleX;
    float v = (ry - mMinY) * mScaleY;

    int cx = (int)u;
    if (u < (float)cx)
        cx -= 1;
    *px = cx;

    int cy = (int)v;
    if (v < (float)cy)
        cy -= 1;
    *py = cy;

    *fx = u - (float)cx;
    *fy = v - (float)cy;

    if (mbWrap3c) {
        int m = m20 - 1;
        *px = cx % m;
        if (*px < 0)
            *px += m;
        int n = m24 - 1;
        *py = cy % n;
        if (*py < 0)
            *py += n;
    } else {
        int m = m20 - 1;
        *px = cx - (cx >= m);
        int n = m24 - 1;
        *py = cy - (cy >= n);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a751a0  cMapInfo::RefreshScale
// ---------------------------------------------------------------------------
void cMapInfo::NormalizeNoWrap()
{
    if (mpPixels40)
        return;
    mpOwner38->RequestGrid(mpGrid, (int*)&m20, (int*)&m24, (int*)&mpPixels40);
    mScaleX = (float)((int)m20 - 1) / (mMaxX - mMinX);
    mScaleY = (float)((int)m24 - 1) / (mMaxY - mMinY);
}

// ---------------------------------------------------------------------------
// @ 0x00a75120  cMapInfo::Normalize
// ---------------------------------------------------------------------------
void cMapInfo::Normalize()
{
    if (mpPixels40)
        return;
    mpOwner38->RequestGrid(mpGrid, (int*)&m20, (int*)&m24, (int*)&mpPixels40);
    mpPixels40 = (uint32_t*)((char*)mpPixels40 + m4c);
    int cols = (int)m20;
    m44 = (1 << m48) * cols;
    mScaleX = (float)(cols - 1) / (mMaxX - mMinX);
    mScaleY = (float)((int)m24 - 1) / (mMaxY - mMinY);
}

// ---------------------------------------------------------------------------
// @ 0x00a75200  cMapInfo::NormalizeFloor
// ---------------------------------------------------------------------------
void cMapInfo::NormalizeFloor()
{
    if (mpPixels40)
        return;
    mpOwner38->RequestGrid(mpGrid, (int*)&m20, (int*)&m24, (int*)&mpPixels40);
    m44 = ((int)m20 + 7) >> 3;
    mScaleX = (float)((int)m20 - 1) / (mMaxX - mMinX);
    mScaleY = (float)((int)m24 - 1) / (mMaxY - mMinY);
}

// ---------------------------------------------------------------------------
// @ 0x00a75270  cMapInfo::NormalizeRound
// ---------------------------------------------------------------------------
void cMapInfo::NormalizeRound()
{
    if (mpPixels40)
        return;
    mpOwner38->RequestGrid(mpGrid, (int*)&m20, (int*)&m24, (int*)&mpPixels40);
    m44 = ((int)m20 + 7) >> 3;
    mScaleX = (float)((int)m20 - 1) / (mMaxX - mMinX);
    mScaleY = (float)((int)m20 - 1) / (mMaxY - mMinY);
}

// ---------------------------------------------------------------------------
// @ 0x00a752d0  cMapInfo::SetColor
// ---------------------------------------------------------------------------
void cMapInfo::SetColor(int idx, const Vec4* c)
{
    uint32_t* dst;
    if (idx == 0) {
        dst = (uint32_t*)((char*)this + 0x40);
        dst[0] = *(const uint32_t*)((const char*)c + 0);
        dst[1] = *(const uint32_t*)((const char*)c + 4);
        dst[2] = *(const uint32_t*)((const char*)c + 8);
        dst[3] = *(const uint32_t*)((const char*)c + 0xc);
        return;
    }
    if (idx == 1) {
        dst = (uint32_t*)((char*)this + 0x50);
        dst[0] = *(const uint32_t*)((const char*)c + 0);
        dst[1] = *(const uint32_t*)((const char*)c + 4);
        dst[2] = *(const uint32_t*)((const char*)c + 8);
        dst[3] = *(const uint32_t*)((const char*)c + 0xc);
        return;
    }
    if (idx == 2) {
        dst = (uint32_t*)((char*)this + 0x60);
        dst[0] = *(const uint32_t*)((const char*)c + 0);
        dst[1] = *(const uint32_t*)((const char*)c + 4);
        dst[2] = *(const uint32_t*)((const char*)c + 8);
        dst[3] = *(const uint32_t*)((const char*)c + 0xc);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a75340  cMapInfo::SetPoint
// ---------------------------------------------------------------------------
void cMapInfo::SetPoint(int idx, uint32_t a, uint32_t b)
{
    if (idx == 0) {
        *(uint32_t*)((char*)this + 0x28) = a;
        *(uint32_t*)((char*)this + 0x2c) = b;
        return;
    }
    if (idx == 1) {
        *(uint32_t*)((char*)this + 0x30) = a;
        *(uint32_t*)((char*)this + 0x34) = b;
        return;
    }
    if (idx == 2) {
        *(uint32_t*)((char*)this + 0x38) = a;
        *(uint32_t*)((char*)this + 0x3c) = b;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a75390  cMapInfo::ResetGrid
// ---------------------------------------------------------------------------
void __cdecl cMapInfo_ResetGrid(void* a, uint32_t* b)
{
    void* p = *(void**)((char*)a + 8);
    int n = *(int*)((char*)a + 0xc);
    ((void (__thiscall*)(uint32_t*, void*, int, int))(*(void***)b)[0x88 / 4])(b, p, n, 0);
}

// ---------------------------------------------------------------------------
// @ 0x00a753b0  vec3_min
// ---------------------------------------------------------------------------
void cMapInfo_SortRect2(float* out, const float* b, const float* a)
{
    const float* p2 = (a[2] <= b[2]) ? a + 2 : b + 2;
    const float* p1 = (a[1] <= b[1]) ? a + 1 : b + 1;
    const float* p0 = (a[0] <= b[0]) ? a : b;
    out[0] = *p0;
    out[1] = *p1;
    out[2] = *p2;
}

// ---------------------------------------------------------------------------
// @ 0x00a75410  vec4_min
// ---------------------------------------------------------------------------
void cMapInfo_SortRect3(float* out, const float* b, const float* a)
{
    const float* p3 = (a[3] <= b[3]) ? a + 3 : b + 3;
    const float* p2 = (a[2] <= b[2]) ? a + 2 : b + 2;
    const float* p1 = (a[1] <= b[1]) ? a + 1 : b + 1;
    const float* p0 = (a[0] <= b[0]) ? a : b;
    out[0] = *p0;
    out[1] = *p1;
    out[2] = *p2;
    out[3] = *p3;
}

// ---------------------------------------------------------------------------
// @ 0x00a75480  vec4_min (reversed operands)
// ---------------------------------------------------------------------------
void cMapInfo_SortRect3R(float* out, const float* b, const float* a)
{
    const float* p3 = (b[3] > a[3]) ? b + 3 : a + 3;
    const float* p2 = (b[2] > a[2]) ? b + 2 : a + 2;
    const float* p1 = (b[1] > a[1]) ? b + 1 : a + 1;
    const float* p0 = (b[0] > a[0]) ? b : a;
    out[0] = *p0;
    out[1] = *p1;
    out[2] = *p2;
    out[3] = *p3;
}

// ---------------------------------------------------------------------------
// @ 0x00a754f0  cMapInfo::UnpackColor
// ---------------------------------------------------------------------------
void cMapInfo::UnpackColor(float* out, int packed, uint32_t a)
{
    uint32_t v = mpPixels40[m20 * a + packed];
    out[0] = (float)((v >> 16) & 0xff);
    out[1] = (float)((v >> 8) & 0xff);
    out[2] = (float)(v & 0xff);
    out[3] = (float)(uint32_t)(v >> 24);
}

// ---------------------------------------------------------------------------
// @ 0x00a75560  cMapInfo::ClassifyOrientation
// ---------------------------------------------------------------------------
int cMapInfo::ClassifyOrientation(const float* n, int* out)
{
    float ax = n[0], ay = n[1], az = n[2];
    float aax = ax < 0 ? -ax : ax;
    float aay = ay < 0 ? -ay : ay;
    float aaz = az < 0 ? -az : az;
    float u, v;
    int cls;
    if (aaz >= aay && aaz >= aax) {
        u = -ax / az;
        v = ay / aaz;
        if (az < 0.0f) {
            *out = 2;
        } else {
            *out = 0;
        }
    } else if (aay >= aax) {
        u = -ax / aay;
        v = az / ay;
        cls = (ay < 0.0f) ? 1 : 3;
        *out = cls;
    } else {
        u = -az / ax;
        v = ay / aax;
        cls = (ax < 0.0f) ? 5 : 4;
        *out = cls;
        if (cls == 4) {
            u = -u;
            v = -v;
        }
    }
    return cls;
}

// ---------------------------------------------------------------------------
// @ 0x00a756a0  cMapInfo::SetVec3
// ---------------------------------------------------------------------------
void cMapInfo::SetVec3(float* out, uint32_t a)
{
    out[0] = 3.402823466e38f;
    out[1] = 3.402823466e38f;
    out[2] = 3.402823466e38f;
}

// ---------------------------------------------------------------------------
// @ 0x00a756d0  cMapInfo::MulScale
// ---------------------------------------------------------------------------
float* cMapInfo::MulScale(float* out, float* s)
{
    float f = (float)((double (__thiscall*)(cMapInfo*, float*))(*(void***)this)[0x20 / 4])(this, s);
    float v[3];
    float* r = ((float* (__thiscall*)(cMapInfo*, float*, float*))(*(void***)this)[0x24 / 4])(this, v, s);
    out[0] = f * r[0];
    out[1] = f * r[1];
    out[2] = f * r[2];
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00a75720  cMapInfo::Fill
// ---------------------------------------------------------------------------
void cMapInfo::Fill(float* out, uint32_t a)
{
    double w = ((double (__thiscall*)(cMapInfo*, uint32_t))(*(void***)this)[0x20 / 4])(this, a);
    out[0] = 1.0f;
    out[1] = 1.0f;
    out[2] = 1.0f;
    out[3] = w;
}

// ---------------------------------------------------------------------------
// @ 0x00a75750  cMapInfo::GetBounds
// ---------------------------------------------------------------------------
void cMapInfo::GetBounds(float* out)
{
    float t[6];
    t[0] = mMinX;
    t[1] = mMaxX;
    t[2] = mMinY;
    t[3] = mMaxY;
    t[4] = 0.0f;
    t[5] = 0.0f;
    out[0] = t[0];
    out[1] = t[1];
    out[2] = t[2];
    out[3] = t[3];
    out[4] = t[4];
    out[5] = t[5];
}

// ---------------------------------------------------------------------------
// @ 0x00a757c0  cMapInfo::Contains
// ---------------------------------------------------------------------------
bool cMapInfo::Contains(const float* p)
{
    if (mbWrap3c)
        return true;
    if (p[0] < mMinX)
        return false;
    if (mMaxX <= p[0])
        return false;
    if (p[1] < mMinY)
        return false;
    if (mMaxY <= p[1])
        return false;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00a75810  cMapInfo::InitA
// ---------------------------------------------------------------------------
void cMapInfo::InitA(const float* rect, uint8_t a, void* b, int c, uint8_t d)
{
    mbWrap3c = d;
    mMinX = rect[0];
    mMinY = rect[1];
    mMaxX = rect[2];
    mMaxY = rect[3];
    mbWrap1c = a;
    mpOwner38 = (IcOwner*)b;
    mbValid34 = ((bool (__thiscall*)(void*, int, void*, int))(*(void***)b)[0x14 / 4])(b, 10, 0, 0);
    if (!mbValid34) {
        m20 = 2;
        m24 = 2;
        mpPixels40 = (uint32_t*)0x014575d4;
        mScaleX = 1.0f / (mMaxX - mMinX);
        mScaleY = 1.0f / (mMaxY - mMinY);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a758b0  cMapInfo::InitB
// ---------------------------------------------------------------------------
void cMapInfo::InitB(const float* rect, uint8_t a, void* b, int c, uint8_t d, int e)
{
    mbWrap3c = d;
    mMinX = rect[0];
    mMinY = rect[1];
    mMaxX = rect[2];
    mMaxY = rect[3];
    mbWrap1c = a;
    mpOwner38 = (IcOwner*)b;
    mbValid34 = ((bool (__thiscall*)(void*, int, void*, int))(*(void***)b)[0x14 / 4])(b, 11, 0, 0);
    if (mbValid34) {
        m48 = 2;
        m4c = e;
        return;
    }
    m20 = 2;
    m24 = 2;
    mpPixels40 = (uint32_t*)0x014575d4;
    mScaleX = 1.0f / (mMaxX - mMinX);
    mScaleY = 1.0f / (mMaxY - mMinY);
}

// ---------------------------------------------------------------------------
// @ 0x00a75960  cMapInfo::SampleBilinear
// ---------------------------------------------------------------------------
float cMapInfo::SampleBilinear(const float* p)
{
    int cx, cy;
    float fx, fy;
    MapToCell(p[0], p[1], &cx, &cy, &fx, &fy);

    int stride = m44;
    int sh = m48;
    uint8_t* px = (uint8_t*)mpPixels40;

    float v00 = (float)px[stride * cy + (int)cx];
    float v10 = (float)px[stride * (cy + 1) + (int)cx];
    float top = v00 + (v10 - v00) * fy;
    int c1 = cx + 1;
    float v01 = (float)px[stride * cy + c1];
    float v11 = (float)px[stride * (cy + 1) + c1];
    float bot = v01 + (v11 - v01) * fy;
    return (top + (bot - top) * fy) * (1.0f / 255.0f);
}

// ---------------------------------------------------------------------------
// @ 0x00a75d00  cMapInfo::NormalizeVec
// ---------------------------------------------------------------------------
void cMapInfo::NormalizeVec(float* out, uint32_t a)
{
    float v[4];
    ((void (__thiscall*)(cMapInfo*, float*, uint32_t))(*(void***)this)[0x2c / 4])(this, v, a);
    float x = v[0] * 2.0f - 1.0f;
    float y = v[1] * 2.0f - 1.0f;
    float z = v[2] * 2.0f - 1.0f;
    float len = 1.0f / sqrtf(x * x + y * y + z * z + 1e-9f);
    out[0] = v[3] * x * len;
    out[1] = v[3] * y * len;
    out[2] = v[3] * z * len;
}

// ---------------------------------------------------------------------------
// @ 0x00a75a30  cMapInfo::SampleBicubic
// ---------------------------------------------------------------------------
void cMapInfo::SampleBicubic(float* out, const float* p)
{
    int cx, cy;
    float fx, fy;
    MapToCell(p[0], p[1], &cx, &cy, &fx, &fy);

    int stride = m44;
    uint8_t* px = (uint8_t*)mpPixels40;
    int sh = m48;

    int c0 = cx - 1; if (c0 <= 0) c0 = 0;
    int c1 = cx + 1; if (c1 >= (int)m20 - 1) c1 = (int)m20 - 1;
    int c2 = cx + 2; if (c2 >= (int)m20 - 1) c2 = (int)m20 - 1;
    int r0 = cy - 1; if (r0 <= 0) r0 = 0;
    int r1 = cy + 1; if (r1 >= (int)m24 - 1) r1 = (int)m24 - 1;
    int r2 = cy + 2; if (r2 >= (int)m24 - 1) r2 = (int)m24 - 1;

    // 4x4 neighbourhood (row-major, rows r0..r2 and cy, cols c0..c2 and cx).
    float s[4][4];
    int rows[4] = { r0, cy, r1, r2 };
    int cols[4] = { c0, cx, c1, c2 };
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            s[r][c] = (float)px[(uint32_t)rows[r] * stride + ((uint32_t)cols[c] << sh)];
    (void)fy; (void)fx;
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
}

}}
