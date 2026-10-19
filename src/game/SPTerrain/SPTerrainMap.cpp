// src/game/SPTerrain/SPTerrainMap.cpp -- migrated from slice(s) s00f8fe60, s00f8e6c0, s00f8b2b0, s00f7d9d0 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainMap.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <xmmintrin.h>
#include <math.h>
#include <float.h>

// ---- items of slice s00f7d9d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define NM_ALIGN16 __declspec(align(16))
NM_ALIGN16 static const uint32_t kLow16Mask[4]   = { 0xffff, 0xffff, 0xffff, 0xffff };                  // 0x01490640
NM_ALIGN16 static const uint32_t kHigh16Mask[4]  = { 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000 };  // 0x0148ff60
NM_ALIGN16 static const uint32_t kByte0Mask[4]   = { 0xff, 0xff, 0xff, 0xff };                          // 0x0148ffe0
NM_ALIGN16 static const uint32_t kByte1Mask[4]   = { 0xff00, 0xff00, 0xff00, 0xff00 };                  // 0x0148ff80
NM_ALIGN16 static const float kOne[4]        = { 1.0f, 1.0f, 1.0f, 1.0f };                              // 0x0148fff0
NM_ALIGN16 static const float kHalf[4]       = { 0.5f, 0.5f, 0.5f, 0.5f };                              // 0x0148ffa0
NM_ALIGN16 static const float kTwoPow23[4]   = { 8388608.0f, 8388608.0f, 8388608.0f, 8388608.0f };      // 0x0148ff50
NM_ALIGN16 static const float kEpsilon[4]    = { 0.001f, 0.001f, 0.001f, 0.001f };                      // 0x0148ff90
NM_ALIGN16 static const float kByte0Scale[4] = { 255.0f / 8388608.0f, 255.0f / 8388608.0f,
                                                 255.0f / 8388608.0f, 255.0f / 8388608.0f };            // 0x01490000
NM_ALIGN16 static const float kByte1Scale[4] = { 255.0f / 32768.0f, 255.0f / 32768.0f,
                                                 255.0f / 32768.0f, 255.0f / 32768.0f };                // 0x0148ff70
NM_ALIGN16 static const float kOneTexel[4]   = { 1.0f / 256, 1.0f / 256, 1.0f / 256, 1.0f / 256 };      // 0x0148ffc0
NM_ALIGN16 static const float kTwoTexels[4]  = { 1.0f / 128, 1.0f / 128, 1.0f / 128, 1.0f / 128 };      // 0x0148ffb0
NM_ALIGN16 static const float kFourTexels[4] = { 1.0f / 64, 1.0f / 64, 1.0f / 64, 1.0f / 64 };          // 0x0148ffd0
NM_ALIGN16 static const float kTexelRamp[4]  = { 0.0f, 1.0f / 256, 2.0f / 256, 3.0f / 256 };            // 0x01490010
static const float kHeightUnit = 3.0518044e-05f;   // 0x01435840 (0x38000080, ~1/32767.5)
static const int kRowPitch = 512;   // texels (and heights) per row
static __forceinline __m128 Load(const float* p) { return _mm_load_ps(p); }
static __forceinline __m128 Load(const uint32_t* p) { return _mm_load_ps((const float*)p); }
static __forceinline __m128 HeightsToFloat(__m128 raw)
{
    __m128 one = Load(kOne);
    return _mm_mul_ps(_mm_sub_ps(_mm_or_ps(_mm_and_ps(raw, Load(kLow16Mask)), one), one),
                      Load(kTwoPow23));
}
struct HeightRow8
{
    __m128 lo;
    __m128 hi;
};
static __forceinline void LoadHeights8(const uint16_t* p, HeightRow8& out)
{
    __m128 evens = HeightsToFloat(_mm_load_ps((const float*)p));        // columns 0, 2, 4, 6
    __m128 odds  = HeightsToFloat(_mm_loadu_ps((const float*)(p + 1))); // columns 1, 3, 5, 7
    __m128 t = _mm_shuffle_ps(evens, odds, 0x44);
    out.lo = _mm_shuffle_ps(t, t, 0xd8);
    t = _mm_shuffle_ps(evens, odds, 0xee);
    out.hi = _mm_shuffle_ps(t, t, 0xd8);
}
struct HeightBlock
{
    HeightRow8 row[4];
};
static __forceinline void LoadBlock(const uint16_t* p, HeightBlock& b)
{
    LoadHeights8(p, b.row[0]);
    LoadHeights8(p + kRowPitch, b.row[1]);
    LoadHeights8(p + 2 * kRowPitch, b.row[2]);
    LoadHeights8(p + 3 * kRowPitch, b.row[3]);
}
static __forceinline __m128 ShiftInLeft(__m128 prev, __m128 cur)
{
    __m128 t = _mm_shuffle_ps(prev, cur, _MM_SHUFFLE(0, 0, 3, 3));
    return _mm_shuffle_ps(t, cur, _MM_SHUFFLE(2, 1, 2, 0));
}
static __forceinline __m128 ShiftInRight(__m128 cur, __m128 next)
{
    __m128 t = _mm_shuffle_ps(cur, next, _MM_SHUFFLE(0, 0, 3, 3));
    return _mm_shuffle_ps(cur, t, _MM_SHUFFLE(2, 0, 2, 1));
}
struct NormalMapConsts
{
    __m128 heightScale;    // height units -> world: (heightRange / 2) * kHeightUnit
    __m128 heightBase;     // radius - heightRange / 2
    __m128 gradientScale;  // heightScale * 256 (one texel = 1/256 of the face half-width)
    __m128 slopeScale;     // 2 / ((heightRange / 2) * slopeRange)
    __m128 scaleB;         // channelB * 0.5 (bits 0-7)
    __m128 scaleG;         // channelG * 0.5 (bits 8-15)
    __m128 scaleR;         // channelR * 0.5 (bits 16-23)
    __m128 zero;
};
static __forceinline void InitConsts(NormalMapConsts& c, float radius, float heightRange,
                                     float slopeRange, float channelB, float channelG, float channelR)
{
    float halfRange = heightRange * 0.5f;
    float base = radius - halfRange;
    float slopeScale = 2.0f / (halfRange * slopeRange);
    float heightScale = halfRange * kHeightUnit;
    float gradientScale = heightScale * 256.0f;
    __m128 half = Load(kHalf);
    c.scaleB = _mm_mul_ps(_mm_set1_ps(channelB), half);
    c.scaleG = _mm_mul_ps(_mm_set1_ps(channelG), half);
    c.scaleR = _mm_mul_ps(_mm_set1_ps(channelR), half);
    c.heightScale = _mm_set1_ps(heightScale);
    c.heightBase = _mm_set1_ps(base);
    c.gradientScale = _mm_set1_ps(gradientScale);
    c.slopeScale = _mm_set1_ps(slopeScale);
    c.zero = _mm_setzero_ps();
}
static __forceinline float FaceCoord(int n)
{
    return ((float)n + 0.5f) * (1.0f / 256) - 1.0f;
}
static __forceinline __m128 PackChannel(const __m128& inv, const __m128& n, const __m128& scale,
                                         const float* byteScale)
{
    return _mm_add_ps(_mm_mul_ps(_mm_add_ps(_mm_mul_ps(_mm_mul_ps(inv, n), scale), Load(kHalf)),
                                 Load(byteScale)), Load(kOne));
}
template <int kAxis>
static __forceinline void ShadeQuad(uint32_t* out, const __m128& h, const __m128& left,
                                    const __m128& right, const __m128& up, const __m128& down,
                                    const __m128& u, const __m128& v, const NormalMapConsts& c)
{
    __m128 gradU = _mm_sub_ps(left, right);
    __m128 gradV = _mm_sub_ps(up, down);

    // Point on the unit sphere: (u, v, 1) / |(u, v, 1)|, at radius base + h * scale.
    __m128 invLen = _mm_rsqrt_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(v, v), _mm_mul_ps(u, u)), Load(kOne)));
    __m128 invRadius = _mm_rcp_ps(_mm_mul_ps(invLen,
                                             _mm_add_ps(_mm_mul_ps(h, c.heightScale), c.heightBase)));
    __m128 dU = _mm_mul_ps(invRadius, gradU);
    __m128 dV = _mm_mul_ps(invRadius, gradV);

    __m128 nV = _mm_add_ps(_mm_mul_ps(invLen, v), dV);
    __m128 nU = _mm_add_ps(_mm_mul_ps(invLen, u), dU);
    __m128 nW = _mm_sub_ps(invLen, _mm_add_ps(_mm_mul_ps(dU, u), _mm_mul_ps(dV, v)));
    __m128 inv = _mm_rsqrt_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(nV, nV), _mm_mul_ps(nU, nU)),
                                         _mm_add_ps(_mm_mul_ps(nW, nW), Load(kEpsilon))));

    // Rotate (nV, nU, nW) into (R, G, B) for this cube axis.
    __m128 nR, nG, nB;
    if (kAxis == 0)
    {
        nR = nW; nG = nV; nB = nU;
    }
    else if (kAxis == 1)
    {
        nR = nU; nG = nW; nB = nV;
    }
    else
    {
        nR = nV; nG = nU; nB = nW;
    }

    __m128 one = Load(kOne);
    __m128 slope = _mm_mul_ps(_mm_sqrt_ps(_mm_add_ps(_mm_mul_ps(gradU, gradU), _mm_mul_ps(gradV, gradV))),
                              c.slopeScale);
    slope = _mm_max_ps(c.zero, _mm_min_ps(one, slope));
    slope = _mm_add_ps(_mm_mul_ps(slope, Load(kByte1Scale)), one);

    // High half (A, R), stored first, then moved up by re-reading it 2 bytes early.
    __m128 high = _mm_or_ps(_mm_and_ps(slope, Load(kByte1Mask)),
                            _mm_and_ps(PackChannel(inv, nR, c.scaleR, kByte0Scale), Load(kByte0Mask)));
    __m128 low = _mm_or_ps(_mm_and_ps(PackChannel(inv, nG, c.scaleG, kByte1Scale), Load(kByte1Mask)),
                           _mm_and_ps(PackChannel(inv, nB, c.scaleB, kByte0Scale), Load(kByte0Mask)));
    _mm_store_ps((float*)out, high);
    __m128 shifted = _mm_loadu_ps((const float*)((const char*)out - 2));
    _mm_store_ps((float*)out, _mm_or_ps(_mm_and_ps(shifted, Load(kHigh16Mask)), low));
}
template <int kAxis>
static __forceinline void ShadeQuadPair(uint32_t* out, const __m128& h1, const __m128& left1,
                                        const __m128& right1, const __m128& h2, const __m128& left2,
                                        const __m128& right2, const __m128& up0, const __m128& mid1,
                                        const __m128& mid2, const __m128& down3,
                                        __m128& u, __m128& v, const NormalMapConsts& c)
{
    ShadeQuad<kAxis>(out, h1, left1, right1, up0, mid2, u, v, c);
    v = _mm_add_ps(Load(kOneTexel), v);
    ShadeQuad<kAxis>(out + kRowPitch, h2, left2, right2, mid1, down3, u, v, c);
    v = _mm_sub_ps(v, Load(kOneTexel));
    u = _mm_add_ps(Load(kFourTexels), u);
}
static __forceinline __m128 Scaled(__m128 h, const NormalMapConsts& c)
{
    return _mm_mul_ps(h, c.gradientScale);
}
template <int kAxis>
static __forceinline void NormalMapLeft(uint32_t* dst, const uint16_t* src, int x0, int x1, int y0,
                                        int y1, float radius, float heightRange, float slopeRange,
                                        float channelB, float channelG, float channelR)
{
    NormalMapConsts c;
    InitConsts(c, radius, heightRange, slopeRange, channelB, channelG, channelR);
    int firstBlock = x0 / 8;
    int endBlock = (x1 + 7) / 8;
    float u0 = FaceCoord(firstBlock * 8);
    __m128 v = _mm_set1_ps(FaceCoord(y0 - 1));
    const uint16_t* srcRows = src + (y0 - 1) * kRowPitch;
    uint32_t* dstRows = dst + y0 * kRowPitch;

    for (int pair = (y0 - 1) / 2; pair <= (y1 - 1) / 2; ++pair)
    {
        HeightBlock cur;
        LoadBlock(srcRows + firstBlock * 8, cur);
        __m128 u = _mm_add_ps(_mm_set1_ps(u0), Load(kTexelRamp));
        __m128 prev1 = c.zero;  // lane 3: scaled height of the column left of the block
        __m128 prev2 = c.zero;
        for (int block = firstBlock; block < endBlock; ++block)
        {
            HeightBlock next;
            LoadBlock(srcRows + (block + 1) * 8, next);
            uint32_t* out = dstRows + block * 8;

            __m128 s0lo = Scaled(cur.row[0].lo, c), s0hi = Scaled(cur.row[0].hi, c);
            __m128 s1lo = Scaled(cur.row[1].lo, c), s1hi = Scaled(cur.row[1].hi, c);
            __m128 s2lo = Scaled(cur.row[2].lo, c), s2hi = Scaled(cur.row[2].hi, c);
            __m128 s3lo = Scaled(cur.row[3].lo, c), s3hi = Scaled(cur.row[3].hi, c);
            __m128 n1lo = Scaled(next.row[1].lo, c), n2lo = Scaled(next.row[2].lo, c);

            ShadeQuadPair<kAxis>(out, cur.row[1].lo, ShiftInLeft(prev1, s1lo), ShiftInRight(s1lo, s1hi),
                                 cur.row[2].lo, ShiftInLeft(prev2, s2lo), ShiftInRight(s2lo, s2hi),
                                 s0lo, s1lo, s2lo, s3lo, u, v, c);
            ShadeQuadPair<kAxis>(out + 4, cur.row[1].hi, ShiftInLeft(s1lo, s1hi), ShiftInRight(s1hi, n1lo),
                                 cur.row[2].hi, ShiftInLeft(s2lo, s2hi), ShiftInRight(s2hi, n2lo),
                                 s0hi, s1hi, s2hi, s3hi, u, v, c);
            prev1 = s1hi;
            prev2 = s2hi;
            cur = next;
        }
        v = _mm_add_ps(Load(kTwoTexels), v);
        srcRows += 2 * kRowPitch;
        dstRows += 2 * kRowPitch;
    }
}
template <int kAxis>
static __forceinline void ShadeOffsetBlock(uint32_t* out, const HeightBlock& cur, const HeightBlock& next,
                                           __m128& u, __m128& v, const NormalMapConsts& c)
{
    __m128 s0hi = Scaled(cur.row[0].hi, c);
    __m128 s1lo = Scaled(cur.row[1].lo, c), s1hi = Scaled(cur.row[1].hi, c);
    __m128 s2lo = Scaled(cur.row[2].lo, c), s2hi = Scaled(cur.row[2].hi, c);
    __m128 s3hi = Scaled(cur.row[3].hi, c);
    __m128 n0lo = Scaled(next.row[0].lo, c);
    __m128 n1lo = Scaled(next.row[1].lo, c), n1hi = Scaled(next.row[1].hi, c);
    __m128 n2lo = Scaled(next.row[2].lo, c), n2hi = Scaled(next.row[2].hi, c);
    __m128 n3lo = Scaled(next.row[3].lo, c);

    ShadeQuadPair<kAxis>(out, cur.row[1].hi, ShiftInLeft(s1lo, s1hi), ShiftInRight(s1hi, n1lo),
                         cur.row[2].hi, ShiftInLeft(s2lo, s2hi), ShiftInRight(s2hi, n2lo),
                         s0hi, s1hi, s2hi, s3hi, u, v, c);
    ShadeQuadPair<kAxis>(out + 4, next.row[1].lo, ShiftInLeft(s1hi, n1lo), ShiftInRight(n1lo, n1hi),
                         next.row[2].lo, ShiftInLeft(s2hi, n2lo), ShiftInRight(n2lo, n2hi),
                         n0lo, n1lo, n2lo, n3lo, u, v, c);
}
template <int kAxis>
static __forceinline void NormalMapInterior(uint32_t* dst, const uint16_t* src, int x0, int x1, int y0,
                                            int y1, float radius, float heightRange, float slopeRange,
                                            float channelB, float channelG, float channelR)
{
    NormalMapConsts c;
    InitConsts(c, radius, heightRange, slopeRange, channelB, channelG, channelR);
    int firstBlock = (x0 - 4) / 8;
    int endBlock = (x1 + 7) / 8;
    float u0 = FaceCoord(firstBlock * 8 + 4);
    __m128 v = _mm_set1_ps(FaceCoord(y0 - 1));
    const uint16_t* srcRows = src + (y0 - 1) * kRowPitch;
    uint32_t* dstRows = dst + y0 * kRowPitch + 4;

    for (int pair = (y0 - 1) / 2; pair < (y1 - 1) / 2; ++pair)
    {
        HeightBlock cur;
        LoadBlock(srcRows + firstBlock * 8, cur);
        __m128 u = _mm_add_ps(_mm_set1_ps(u0), Load(kTexelRamp));
        for (int block = firstBlock; block < endBlock; ++block)
        {
            HeightBlock next;
            LoadBlock(srcRows + (block + 1) * 8, next);
            ShadeOffsetBlock<kAxis>(dstRows + block * 8, cur, next, u, v, c);
            cur = next;
        }
        v = _mm_add_ps(Load(kTwoTexels), v);
        srcRows += 2 * kRowPitch;
        dstRows += 2 * kRowPitch;
    }
}
template <int kAxis>
static __forceinline void NormalMapRight(uint32_t* dst, const uint16_t* src, int x0, int x1, int y0,
                                         int y1, float radius, float heightRange, float slopeRange,
                                         float channelB, float channelG, float channelR)
{
    NormalMapConsts c;
    InitConsts(c, radius, heightRange, slopeRange, channelB, channelG, channelR);
    int firstBlock = (x0 - 4) / 8;
    int lastBlock = (x1 + 7) / 8 - 1;
    float u0 = FaceCoord(firstBlock * 8 + 4);
    __m128 v = _mm_set1_ps(FaceCoord(y0 - 1));
    const uint16_t* srcRows = src + (y0 - 1) * kRowPitch;
    uint32_t* dstRows = dst + y0 * kRowPitch + 4;

    for (int pair = (y0 - 1) / 2; pair < (y1 - 1) / 2; ++pair)
    {
        HeightBlock cur;
        LoadBlock(srcRows + firstBlock * 8, cur);
        __m128 u = _mm_add_ps(_mm_set1_ps(u0), Load(kTexelRamp));
        for (int block = firstBlock; block < lastBlock; ++block)
        {
            HeightBlock next;
            LoadBlock(srcRows + (block + 1) * 8, next);
            ShadeOffsetBlock<kAxis>(dstRows + block * 8, cur, next, u, v, c);
            cur = next;
        }

        HeightRow8 edge1, edge2;
        LoadHeights8(srcRows + kRowPitch + lastBlock * 8 + 8, edge1);
        LoadHeights8(srcRows + 2 * kRowPitch + lastBlock * 8 + 8, edge2);
        __m128 s0hi = Scaled(cur.row[0].hi, c);
        __m128 s1lo = Scaled(cur.row[1].lo, c), s1hi = Scaled(cur.row[1].hi, c);
        __m128 s2lo = Scaled(cur.row[2].lo, c), s2hi = Scaled(cur.row[2].hi, c);
        __m128 s3hi = Scaled(cur.row[3].hi, c);
        ShadeQuadPair<kAxis>(dstRows + lastBlock * 8, cur.row[1].hi, ShiftInLeft(s1lo, s1hi),
                             ShiftInRight(s1hi, Scaled(edge1.lo, c)),
                             cur.row[2].hi, ShiftInLeft(s2lo, s2hi), ShiftInRight(s2hi, Scaled(edge2.lo, c)),
                             s0hi, s1hi, s2hi, s3hi, u, v, c);

        v = _mm_add_ps(Load(kTwoTexels), v);
        srcRows += 2 * kRowPitch;
        dstRows += 2 * kRowPitch;
    }
}
// ---- items of slice s00f7d9d0 end

// ---- items of slice s00f8b2b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void FUN_00f7d9d0(int, int, int, int, int, int, int,
                         float, float, float, float, float, float, int, int, int); // 0xf7d9d0
extern void WrapCubeFace(int width, void* a, void* b, void* c, void* d, void* e);   // 0x684ca0
extern int  SP_cPropertyList_GetDescription(void* list, unsigned int id);           // 0x???? placeholder
extern int  DAT_016c9bc4;
extern const unsigned char DAT_0148ff28[];
static int  RND(float x) { return (int)x; }   // cvttss2si (trunc), then floor-correct below
static unsigned PackRGBA(const float* n, float alpha, const int* idx, const float* cs)
{
    float r = n[idx[0]] * (cs[0] * 0.5f) + 0.5f;
    float g = n[idx[1]] * (cs[1] * 0.5f) + 0.5f;
    float b = n[idx[2]] * (cs[2] * 0.5f) + 0.5f;
    unsigned a = (unsigned)RND(alpha * 255.0f) & 0xffU;
    unsigned bb = (unsigned)RND(b * 255.0f) & 0xffU;
    unsigned gg = (unsigned)RND(g * 255.0f) & 0xffU;
    unsigned rr = (unsigned)RND(r * 255.0f) & 0xffU;
    return (((a << 8 | bb) << 8 | gg) << 8 | rr);
}
// ---- items of slice s00f8b2b0 end

// ---- items of slice s00f8e6c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct FaceUV { float u, v; int face; };
struct Vec3 { float x, y, z; Vec3() {} Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; } };
namespace SP {
struct cTerrainMapU16 {
    float GetFloat(FaceUV* uv);   // 0x00f8d620 SP::cTerrainMap<unsigned short>::GetFloat
};
}
bool __cdecl RaySphere(Vec3* p, Vec3* d, float r, float* t0, float* t1);   // 0x00f884a0
static __forceinline const float& Max(const float& a, const float& b) { return (a < b) ? b : a; }
static __forceinline const float& Min(const float& a, const float& b) { return (b < a) ? b : a; }
static __forceinline void DirToCubeInto(FaceUV& r, const Vec3& v)
{
    float x = v.x;
    float y = v.y;
    float z = v.z;
    float ax = fabsf(x);
    float ay = fabsf(y);
    float az = fabsf(z);
    if (az >= ax && az >= ay) {
        r.u = (x / z + 1.0f) * 0.5f;
        r.v = (y / az + 1.0f) * 0.5f;
        if (z >= 0.0f) r.face = 0; else r.face = 1;
    } else if (ay >= ax) {
        r.u = (z / y + 1.0f) * 0.5f;
        r.v = (x / ay + 1.0f) * 0.5f;
        if (y >= 0.0f) r.face = 4; else r.face = 5;
    } else {
        r.u = (y / x + 1.0f) * 0.5f;
        r.v = (z / ax + 1.0f) * 0.5f;
        r.face = 2;
        if (!(x >= 0.0f)) r.face = 3;
    }
}
static __forceinline FaceUV DirToCube(const Vec3& v)
{
    FaceUV r;
    DirToCubeInto(r, v);
    return r;
}
// ---- items of slice s00f8e6c0 end

// ---- items of slice s00f8fe60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned int n);   // 0x011e0744 thunk
void EASTLFree(void* p);                                                         // 0x00f47380
struct Vector4 {
    float x, y, z, w;
    Vector4() {}
    Vector4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
};
extern Vector4 kVector4One;   // 0x015b0f90 = {1,1,1,1}
namespace eastl {
struct allocator_s00f8_fe60 {};
}
namespace eastl {
template <class T, class Allocator = allocator_s00f8_fe60> struct vector_s00f8_fe60 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;

    vector_s00f8_fe60() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector_s00f8_fe60() { DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin)); }

    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T& operator[](uint32_t n) { return mpBegin[n]; }

    void resize(uint32_t n);                       // 0x004cd3c0 (folded with vector<void*>::resize)
    T* erase(T* first, T* last)
    {
        T* const position = (T*)memmove(first, last, (uint32_t)((char*)mpEnd - (char*)last)) + (mpEnd - last);
        mpEnd -= (last - first);
        (void)position;
        return first;
    }
    void DoFree(T* p, uint32_t) { if (p && *((uint32_t*)p - 1)) EASTLFree(p); }
};
}
namespace SP {
void WrapCubeFace(int size, int* face, int* x, int* y, int* rot, int* flip);   // 0x00684ca0
}
namespace SP {
uint32_t Direction4fToDirection4c(const Vector4& v);                            // 0x00f87c10
}
namespace SP {
__forceinline void Direction4cToDirection4f(uint32_t c, Vector4& v)
{
    v.x = (float)(c & 0xff);
    v.y = (float)((c >> 8) & 0xff);
    v.z = (float)((c >> 16) & 0xff);
    v.w = (float)(c >> 24) * (1.0f / 255.0f);
    v.x = v.x * (1.0f / 255.0f) * 2.0f - kVector4One.x;
    v.y = v.y * (1.0f / 255.0f) * 2.0f - kVector4One.y;
    v.z = v.z * (1.0f / 255.0f) * 2.0f - kVector4One.z;
}
}
namespace SP {
__forceinline uint32_t BlendEdge(const Vector4& a, const Vector4& b)
{
    Vector4 r;
    r.x = (a.x * 2.0f + b.x) * (1.0f / 3.0f);
    r.y = (a.y * 2.0f + b.y) * (1.0f / 3.0f);
    r.z = (a.z * 2.0f + b.z) * (1.0f / 3.0f);
    r.w = (a.w * 2.0f + b.w) * (1.0f / 3.0f);
    return Direction4fToDirection4c(r);
}
}
namespace SP {
class cTerrainMapBase_s00f8_fe60 {
public:
    virtual ~cTerrainMapBase_s00f8_fe60();
    int mnRefCount;          // +0x04
    unsigned int mFaceSize;  // +0x08
    unsigned int mModCount;  // +0x0c
    struct allocator_128 : eastl::allocator_s00f8_fe60 {};
};
}
namespace SP {
template <class T> class cTerrainMap : public cTerrainMapBase_s00f8_fe60 {
public:
    typedef eastl::vector_s00f8_fe60<T, allocator_128> MapData;

    // Texel (x, y) of `face`; coordinates outside the face wrap onto its neighbours.
    // The range test assumes a power-of-two face size.
    __forceinline T GetCubeValue(int face, int x, int y)
    {
        int size = mFaceSize;
        if ((x | y) & ~(size - 1))
            WrapCubeFace(size, &face, &x, &y, 0, 0);
        return mMapData[(size * face + y) * size + x];
    }

    // Border texel `dst` of the scratch copy = blend of texel (ix, iy) and texel (ox, oy).
    __forceinline uint32_t BlendTexels(int face, int ix, int iy, int ox, int oy)
    {
        Vector4 inner, across;
        Direction4cToDirection4f(GetCubeValue(face, ix, iy), inner);
        Direction4cToDirection4f(GetCubeValue(face, ox, oy), across);
        return BlendEdge(inner, across);
    }

    void BlendMapEdges();

    MapData mMapData;        // +0x10
};
}
// ---- items of slice s00f8fe60 end

// @ 0x00f7d9d0
void UpdateNormalMapRegion(uint32_t* dst, const uint16_t* src, int x0, int x1, int y0, int y1, float radius, float heightRange, float slopeRange, float channelB, float channelG, float channelR, int axis, int, int)
{
    if (x0 < 4)
    {
        switch (axis)
        {
        case 0: NormalMapLeft<0>(dst, src, x0, x1, y0, y1, radius, heightRange, slopeRange, channelB, channelG, channelR); return;
        case 1: NormalMapLeft<1>(dst, src, x0, x1, y0, y1, radius, heightRange, slopeRange, channelB, channelG, channelR); return;
        case 2: NormalMapLeft<2>(dst, src, x0, x1, y0, y1, radius, heightRange, slopeRange, channelB, channelG, channelR); return;
        }
    }
    else if (x1 >= 510)
    {
        switch (axis)
        {
        case 0: NormalMapRight<0>(dst, src, x0, x1, y0, y1, radius, heightRange, slopeRange, channelB, channelG, channelR); return;
        case 1: NormalMapRight<1>(dst, src, x0, x1, y0, y1, radius, heightRange, slopeRange, channelB, channelG, channelR); return;
        case 2: NormalMapRight<2>(dst, src, x0, x1, y0, y1, radius, heightRange, slopeRange, channelB, channelG, channelR); return;
        }
    }
    else
    {
        switch (axis)
        {
        case 0: NormalMapInterior<0>(dst, src, x0, x1, y0, y1, radius, heightRange, slopeRange, channelB, channelG, channelR); return;
        case 1: NormalMapInterior<1>(dst, src, x0, x1, y0, y1, radius, heightRange, slopeRange, channelB, channelG, channelR); return;
        case 2: NormalMapInterior<2>(dst, src, x0, x1, y0, y1, radius, heightRange, slopeRange, channelB, channelG, channelR); return;
        }
    }
}

// @ 0x00f8b2b0
int FUN_00f8b2b0(int param_1, int param_2, int param_3, float param_4, float param_5, float param_6, float param_7, float param_8, float param_9, float param_10)
{
    int width = *(int*)(param_1 + 8);
    float wf = (float)width;

    // ---- clamped integer sub-rectangle (t0=x0, t2=x1, t1=y0, t3=y1) -------
    int t0 = RND(param_7 * wf);
    if (param_7 * wf < (float)t0) t0 = t0 - 1;
    int t2 = RND(param_9 * wf);
    if (param_9 * wf < (float)t2) t2 = t2 - 1;
    int t1r = RND(param_8 * wf);
    if (param_8 * wf < (float)t1r) t1r = t1r - 1;
    float t3f = param_10 * wf;
    int t3 = RND(t3f);
    if (t3f < (float)t3) t3 = t3 - 1;

    int flag0, flag1, flag2, flag3;
    if (t0 < 1) { flag0 = 1; t0 = 1; } else flag0 = 0;
    int fv1 = width - 1;
    if (fv1 <= t2) { flag1 = 1; t2 = width - 2; } else flag1 = 0;
    if (t1r < 1) { flag2 = 1; t1r = 1; } else flag2 = 0;
    if (fv1 <= t3) { flag3 = 1; t3 = width - 2; } else flag3 = 0;

    // ---- format tables and the normal->colour axis {s, 1, s} --------------
    int iVar6 = (param_3 >> 1) * 4;
    float s = ((param_3 & 1) == 0) ? 1.0f : -1.0f;
    int idx[3];
    idx[0] = DAT_0148ff28[iVar6 + 0];
    idx[1] = DAT_0148ff28[iVar6 + 1];
    idx[2] = DAT_0148ff28[iVar6 + 2];
    float axis[3] = { s, 1.0f, s };
    float cscale[3] = { axis[idx[0]], axis[idx[1]], axis[idx[2]] };

    if (DAT_016c9bc4 == 0) {
        FUN_00f7d9d0(*(int*)(param_2 + 0x10) +
                         *(int*)(param_2 + 8) * *(int*)(param_2 + 8) * param_3 * 4,
                     *(int*)(param_1 + 0x10) +
                         *(int*)(param_1 + 8) * *(int*)(param_1 + 8) * param_3 * 2,
                     t0, t2, t1r, t3, (int)param_4, param_4, param_5, param_6,
                     axis[idx[0]], axis[idx[1]], axis[idx[2]],
                     idx[0], idx[1], idx[2]);
    }
    (void)SP_cPropertyList_GetDescription(0, 0xbb60eb9c);

    if ((flag0 | flag1 | flag2 | flag3) == 0)
        return 0;

    // ---- loop constants ---------------------------------------------------
    param_5 = param_5 * 0.5f;
    float local_60 = param_4 - param_5;
    float local_5c = param_5 * 3.0518044e-05f;
    float local_50 = cscale[0] * 0.5f;
    float local_3c = cscale[1] * 0.5f;
    float local_a0 = (wf * 0.5f) * (param_5 * 3.0518044e-05f);
    float local_54 = 2.0f / (param_5 * param_6);
    float local_98 = 2.0f / wf;
    float local_38 = cscale[2] * 0.5f;
    int w2 = width * width;
    unsigned char* heightBase = (unsigned char*)(*(int*)(param_1 + 0x10));
    unsigned char* dstBase = (unsigned char*)(*(int*)(param_2 + 0x10));
    int dstW = *(int*)(param_2 + 8);

    // ======================================================================
    // face flag2 (local_9c._2_1_): rows t0..t2
    // ======================================================================
    if (flag2) {
        float lf0 = (float)t0;
        float lf8 = (float)param_3;
        int   lf4 = -1;
        int   le4 = 1;
        float lfc = 0.0f;
        WrapCubeFace(width, &lf8, &lf0, &lf4, &le4, &lfc);
        int i6 = *(int*)(param_1 + 8) * *(int*)(param_1 + 8);
        unsigned short* local_d0 = (unsigned short*)
            (*(int*)(param_1 + 0x10) + i6 * param_3 * 2);
        int local_ac = *(int*)(param_2 + 0x10) +
                       *(int*)(param_2 + 8) * *(int*)(param_2 + 8) * param_3 * 4;
        unsigned short* local_8c = (unsigned short*)
            (*(int*)(param_1 + 0x10) +
             ((int)lf4 * width + i6 * (int)lf8 + (int)lf0) * 2);
        float cc = local_98 * 0.5f - 1.0f;
        float b0 = ((float)t0 + 0.5f) * local_98 - 1.0f;
        if (t0 <= t2) {
            float ec = (float)((int)lfc * width * 2);
            unsigned* c8 = (unsigned*)(local_d0 + t0 + width);
            local_d0 = local_d0 + t0 + 1;
            int f8i = t0;
            do {
                float hyp = sqrtf((b0 * b0 + cc * cc) + 1.0f);
                float du = (float)((int)*local_8c - (int)(unsigned short)*c8) * local_a0;
                float dv = (float)((int)local_d0[-2] - (int)*local_d0) * local_a0;
                float inv = 1.0f / hyp;
                float h = hyp / ((float)local_d0[-1] * local_5c + local_60);
                float nx = h * du;
                float ny = h * dv;
                float nrm[3];
                nrm[1] = inv * b0 + ny;
                nrm[2] = inv * cc + nx;
                nrm[0] = inv - (ny * b0 + nx * cc);
                float len = ((nrm[1] * nrm[1] + nrm[0] * nrm[0]) + nrm[2] * nrm[2]) + 1e-08f;
                float sc = 1.0f / sqrtf(len);
                nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
                float alpha = sqrtf(dv * dv + du * du) * local_54;
                if (alpha < 0.0f) alpha = 0.0f;
                if (alpha > 1.0f) alpha = 1.0f;
                *(unsigned*)(local_ac + f8i * 4) = PackRGBA(nrm, alpha, idx, cscale);
                local_8c = (unsigned short*)((char*)local_8c + (int)ec);
                f8i = f8i + 1;
                local_d0 = local_d0 + 1;
                b0 = b0 + local_98;
            } while (f8i <= t2);
        }
    }

    // ======================================================================
    // face flag3 (local_9c._3_1_): rows t0..t2 (transposed)
    // ======================================================================
    if (flag3) {
        float lf0 = (float)param_3;
        int   le4 = 1;
        float lfc = 0.0f;
        float lf4 = (float)t0;
        float lf8 = (float)width;
        WrapCubeFace(width, &lf4, &lfc, &lf8, &le4, &lf0);
        int i6 = *(int*)(param_1 + 8) * *(int*)(param_1 + 8);
        unsigned short* local_d0 = (unsigned short*)
            (*(int*)(param_1 + 0x10) +
             (i6 * (int)lf4 + (int)lf8 * width + (int)lfc) * 2);
        float ec = (float)((int)lf0 * width);
        int local_ac = *(int*)(param_1 + 0x10) +
                       (i6 * param_3 + (width - 1) * width) * 2;
        int local_24 = *(int*)(param_2 + 0x10) +
                       (*(int*)(param_2 + 8) * *(int*)(param_2 + 8) * param_3 +
                        (width - 1) * width) * 4;
        float cc = ((float)(width - 1) + 0.5f) * local_98 - 1.0f;
        float b0 = ((float)t0 + 0.5f) * local_98 - 1.0f;
        if (t0 <= t2) {
            unsigned* c8 = (unsigned*)(local_ac + (t0 - width) * 2);
            unsigned short* local_8c = (unsigned short*)(local_ac + 2 + t0 * 2);
            int f8i = t0;
            do {
                float hyp = sqrtf((b0 * b0 + cc * cc) + 1.0f);
                float du = (float)((int)local_8c[-2] - (int)*local_8c) * local_a0;
                float dv = (float)((int)(unsigned short)*c8 - (int)*local_d0) * local_a0;
                float inv = 1.0f / hyp;
                float h = hyp / ((float)local_8c[-1] * local_5c + local_60);
                float du2 = du * h;
                float dv2 = dv * h;
                float nrm[3];
                nrm[0] = b0 * inv + du2;
                nrm[1] = cc * inv + dv2;
                nrm[2] = inv - (cc * dv2 + b0 * du2);
                float len = ((nrm[2] * nrm[2] + nrm[1] * nrm[1]) + nrm[0] * nrm[0]) + 1e-08f;
                float sc = 1.0f / sqrtf(len);
                nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
                float alpha = sqrtf(du * du + dv * dv) * local_54;
                if (alpha < 0.0f) alpha = 0.0f;
                if (alpha > 1.0f) alpha = 1.0f;
                *(unsigned*)(local_24 + f8i * 4) = PackRGBA(nrm, alpha, idx, cscale);
                local_d0 = (unsigned short*)((char*)local_d0 + (int)ec);
                f8i = f8i + 1;
                local_8c = local_8c + 1;
                b0 = b0 + local_98;
            } while (f8i <= t2);
        }
    }

    // ======================================================================
    // face flag0 ((char)local_9c): columns t1r..t3
    // ======================================================================
    if (flag0) {
        float lf4 = (float)t1r;
        float lf0 = (float)param_3;
        int   lf8 = -1;
        float lfc = 0.0f;
        int   le4 = 1;
        WrapCubeFace(width, &lf0, &lf8, &lf4, &lfc, &le4);
        float lb0 = (float)(*(int*)(param_1 + 0x10));
        int i6 = *(int*)(param_1 + 8) * *(int*)(param_1 + 8);
        unsigned short* local_d0 = (unsigned short*)
            ((int)lb0 + (i6 * (int)lf0 + (int)lf4 * width + (int)lf8) * 2);
        unsigned short* puVar9 = (unsigned short*)
            ((int)lb0 + (i6 * param_3 + t1r * width) * 2);
        float b0 = ((float)t1r + 0.5f) * local_98 - 1.0f;
        unsigned* c8 = (unsigned*)(*(int*)(param_2 + 0x10) +
            (*(int*)(param_2 + 8) * *(int*)(param_2 + 8) * param_3 + t1r * width) * 4);
        float cc = local_98 * 0.5f - 1.0f;
        if (t1r <= t3) {
            int cnt = (t3 - t1r) + 1;
            do {
                float hyp = sqrtf((b0 * b0 + cc * cc) + 1.0f);
                float du = (float)((int)*local_d0 - (int)puVar9[1]) * local_a0;
                float dv = (float)((int)puVar9[-width] - (int)puVar9[width]) * local_a0;
                float inv = 1.0f / hyp;
                float h = hyp / ((float)*puVar9 * local_5c + local_60);
                float nx = du * h;
                float ny = dv * h;
                float nrm[3];
                nrm[0] = cc * inv + nx;
                nrm[1] = b0 * inv + ny;
                nrm[2] = inv - (b0 * ny + cc * nx);
                float len = ((nrm[2] * nrm[2] + nrm[1] * nrm[1]) + nrm[0] * nrm[0]) + 1e-08f;
                float sc = 1.0f / sqrtf(len);
                nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
                float alpha = sqrtf(du * du + dv * dv) * local_54;
                if (alpha < 0.0f) alpha = 0.0f;
                if (alpha > 1.0f) alpha = 1.0f;
                *c8 = PackRGBA(nrm, alpha, idx, cscale);
                c8 += width;
                local_d0 = (unsigned short*)((char*)local_d0 + (int)lfc);
                puVar9 += width;
                b0 = b0 + local_98;
            } while (--cnt != 0);
        }
    }

    // ======================================================================
    // face flag1 (local_9c._1_1_): columns t1r..t3 (transposed)
    // ======================================================================
    if (flag1) {
        float lf4 = (float)t1r;
        float lf0 = (float)param_3;
        float lfc = 0.0f;
        int   le4 = 1;
        float lf8 = (float)width;
        WrapCubeFace(width, &lf0, &lf8, &lf4, &lfc, &le4);
        float lb0 = (float)(*(int*)(param_1 + 0x10));
        int i6 = *(int*)(param_1 + 8) * *(int*)(param_1 + 8);
        unsigned short* local_d0 = (unsigned short*)
            ((int)lb0 + (i6 * (int)lf0 + (int)lf4 * width + (int)lf8) * 2);
        unsigned short* puVar9 = (unsigned short*)
            ((int)lb0 + (i6 * param_3 + t1r * width + (width - 1)) * 2);
        float b0 = ((float)t1r + 0.5f) * local_98 - 1.0f;
        unsigned* c8 = (unsigned*)(*(int*)(param_2 + 0x10) +
            (*(int*)(param_2 + 8) * *(int*)(param_2 + 8) * param_3 +
             t1r * width + (width - 1)) * 4);
        float cc = ((float)(width - 1) + 0.5f) * local_98 - 1.0f;
        if (t1r <= t3) {
            int cnt = (t3 - t1r) + 1;
            do {
                float hyp = sqrtf((b0 * b0 + cc * cc) + 1.0f);
                float du = (float)((int)puVar9[-1] - (int)*local_d0) * local_a0;
                float dv = (float)((int)puVar9[-width] - (int)puVar9[width]) * local_a0;
                float inv = 1.0f / hyp;
                float h = hyp / ((float)*puVar9 * local_5c + local_60);
                float nx = du * h;
                float ny = dv * h;
                float nrm[3];
                nrm[0] = cc * inv + nx;
                nrm[1] = b0 * inv + ny;
                nrm[2] = inv - (b0 * ny + cc * nx);
                float len = ((nrm[0] * nrm[0] + nrm[2] * nrm[2]) + nrm[1] * nrm[1]) + 1e-08f;
                float sc = 1.0f / sqrtf(len);
                nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
                float alpha = sqrtf(du * du + dv * dv) * local_54;
                if (alpha < 0.0f) alpha = 0.0f;
                if (alpha > 1.0f) alpha = 1.0f;
                *c8 = PackRGBA(nrm, alpha, idx, cscale);
                c8 += width;
                local_d0 = (unsigned short*)((char*)local_d0 + (int)lfc);
                puVar9 += width;
                b0 = b0 + local_98;
            } while (--cnt != 0);
        }
    }

    // ======================================================================
    // corner texels (single pixel each)
    // ======================================================================
    if (flag2) {
        if (flag0) {
            int fa[3] = { -1, 0, param_3 };
            int fbc = (int)~(unsigned)(width - 1);
            float fc0 = 0.0f;
            int fb8 = param_3;
            if (fbc != 0)
                WrapCubeFace(width, &fa[2], fa, &fa[1], 0, 0);
            if (((unsigned)fbc & ((unsigned)fbc | (unsigned)(int)fc0)) != 0)
                WrapCubeFace(width, &fb8, &fc0, &fbc, 0, 0);
            int i6 = width;
            int c4 = i6 * param_3;
            int c8 = c4 * i6;
            float cc = local_98 * 0.5f - 1.0f;
            unsigned char* hb = heightBase;
            float len = sqrtf((cc * cc + cc * cc) + 1.0f);
            float duN = (float)(int)(*(unsigned short*)(hb +
                             ((fa[2] * i6 + fa[1]) * i6 + fa[0]) * 2) -
                         *(unsigned short*)(hb + 2 + c8 * 2)) * local_a0;
            float dvN = (float)(int)(*(unsigned short*)(hb +
                             ((fb8 * i6 + fbc) * i6 + (int)fc0) * 2) -
                         *(unsigned short*)(hb + (c4 + 1) * i6 * 2)) * local_a0;
            float inv = 1.0f / len;
            float h = len / ((float)*(unsigned short*)(hb + c8 * 2) * local_5c + local_60);
            float nx = duN * h;
            float ny = dvN * h;
            float nrm[3];
            nrm[0] = cc * inv + nx;
            nrm[1] = cc * inv + ny;
            nrm[2] = inv - (cc * nx + cc * ny);
            float l2 = ((nrm[2] * nrm[2] + nrm[1] * nrm[1]) + nrm[0] * nrm[0]) + 1e-08f;
            float sc = 1.0f / sqrtf(l2);
            nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
            float alpha = sqrtf(duN * duN + dvN * dvN) * local_54;
            if (alpha < 0.0f) alpha = 0.0f;
            if (alpha > 1.0f) alpha = 1.0f;
            *(unsigned*)(*(int*)(param_2 + 0x10) +
                         *(int*)(param_2 + 8) * *(int*)(param_2 + 8) * param_3 * 4) =
                PackRGBA(nrm, alpha, idx, cscale);
        }
        if (flag1) {
            int fa[3] = { width, 0, param_3 };
            int c4 = (int)~(unsigned)(width - 1);
            int fb8 = (int)(width - 2) + width;
            int i6 = width;
            float cc = local_98 * 0.5f - 1.0f;
            float b0 = ((float)(width - 1) + 0.5f) * local_98 - 1.0f;
            float hyp = sqrtf((b0 * b0 + cc * cc) + 1.0f);
            unsigned char* hb = heightBase;
            float v84 = (float)(int)(*(unsigned short*)(hb +
                             ((c4 * i6 + width - 1)) * 2) -
                         *(unsigned short*)(hb +
                             ((fa[2] * i6 + fa[1]) * i6 + fa[0]) * 2)) * local_a0;
            float v88 = (float)(int)(*(unsigned short*)(hb +
                             ((fb8 * i6 + c4)) * 2) -
                         *(unsigned short*)(hb +
                             (((c4 + 1) * i6 + width - 1)) * 2)) * local_a0;
            float inv = 1.0f / hyp;
            float h = hyp / ((float)*(unsigned short*)(hb + ((c4 * i6 + (int)(width - 1)) * 2)) * local_5c + local_60);
            float nx = v84 * h;
            float ny = v88 * h;
            float nrm[3];
            nrm[2] = inv - (b0 * nx + cc * ny);
            nrm[0] = b0 * inv + nx;
            nrm[1] = cc * inv + ny;
            float l2 = ((nrm[2] * nrm[2] + nrm[1] * nrm[1]) + nrm[0] * nrm[0]) + 1e-08f;
            float sc = 1.0f / sqrtf(l2);
            nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
            float alpha = sqrtf(v84 * v84 + v88 * v88) * local_54;
            if (alpha < 0.0f) alpha = 0.0f;
            if (alpha > 1.0f) alpha = 1.0f;
            *(unsigned*)(*(int*)(param_2 + 0x10) +
                         (*(int*)(param_2 + 8) * *(int*)(param_2 + 8) * param_3 + width - 1) * 4) =
                PackRGBA(nrm, alpha, idx, cscale);
        }
    }

    if (flag3) {
        if (flag0) {
            int fa[3] = { -1, width - 1, param_3 };
            int c4 = (int)~(unsigned)(width - 1);
            float fc0 = 0.0f;
            int fb8 = param_3;
            if (c4 != 0)
                WrapCubeFace(width, &fa[2], fa, &fa[1], 0, 0);
            if (((unsigned)c4 & ((unsigned)c4 | (unsigned)(int)fc0)) != 0)
                WrapCubeFace(width, &fb8, &fc0, &c4, 0, 0);
            int i6 = width;
            int c4i = i6 * param_3;
            int idx10 = (c4i + width - 1) * i6;
            float cc = ((float)(width - 1) + 0.5f) * local_98 - 1.0f;
            float b0 = local_98 * 0.5f - 1.0f;
            unsigned char* hb = heightBase;
            float hyp = sqrtf((b0 * b0 + cc * cc) + 1.0f);
            float v84 = (float)(int)(*(unsigned short*)(hb +
                             ((fa[2] * i6 + fa[1]) * i6 + fa[0]) * 2) -
                         *(unsigned short*)(hb + 2 + idx10 * 2)) * local_a0;
            float v88 = (float)(int)(*(unsigned short*)(hb +
                             (((width - 2) + c4i) * i6 + width - 1) * 2) -
                         *(unsigned short*)(hb +
                             ((fb8 * i6 + c4) * i6 + (int)fc0) * 2)) * local_a0;
            float inv = 1.0f / hyp;
            float h = hyp / ((float)*(unsigned short*)(hb + (idx10 + width - 1) * 2) * local_5c + local_60);
            float nx = v84 * h;
            float ny = v88 * h;
            float nrm[3];
            nrm[2] = inv - (b0 * nx + cc * ny);
            nrm[0] = b0 * inv + nx;
            nrm[1] = cc * inv + ny;
            float l2 = ((nrm[2] * nrm[2] + nrm[1] * nrm[1]) + nrm[0] * nrm[0]) + 1e-08f;
            float sc = 1.0f / sqrtf(l2);
            nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
            float alpha = sqrtf(v84 * v84 + v88 * v88) * local_54;
            if (alpha < 0.0f) alpha = 0.0f;
            if (alpha > 1.0f) alpha = 1.0f;
            *(unsigned*)(*(int*)(param_2 + 0x10) +
                         (*(int*)(param_2 + 8) * param_3 + width - 1) *
                             *(int*)(param_2 + 8) * 4) =
                PackRGBA(nrm, alpha, idx, cscale);
        }
        if (flag1) {
            int c4 = (int)~(unsigned)(width - 1);
            int fa[3] = { width, width - 1, param_3 };
            float fc0 = 0.0f;
            int fb8 = param_3;
            if (((unsigned)c4 & ((unsigned)width | (unsigned)(width - 1))) != 0)
                WrapCubeFace(width, &fa[2], fa, &fa[1], 0, 0);
            if (((unsigned)c4 & ((unsigned)c4 | (unsigned)(int)fc0)) != 0)
                WrapCubeFace(width, &fb8, &fc0, &c4, 0, 0);
            int i6 = width;
            int c4i = i6 * param_3;
            int idx10 = (width - 1 + c4i) * i6;
            float cc = ((float)(width - 1) + 0.5f) * local_98 - 1.0f;
            float b0 = ((float)(width - 1) + 0.5f) * local_98 - 1.0f;
            unsigned char* hb = heightBase;
            float hyp = sqrtf((b0 * b0 + cc * cc) + 1.0f);
            float v94 = (float)(int)(*(unsigned short*)(hb + (idx10 + width - 2) * 2) -
                         *(unsigned short*)(hb +
                             ((fa[2] * i6 + fa[1]) * i6 + fa[0]) * 2)) * local_a0;
            float v84 = (float)(int)(*(unsigned short*)(hb +
                             (((width - 2) + c4i) * i6 + width - 1) * 2) -
                         *(unsigned short*)(hb +
                             ((fb8 * i6 + c4) * i6 + (int)fc0) * 2)) * local_a0;
            float inv = 1.0f / hyp;
            float h = hyp / ((float)*(unsigned short*)(hb + (idx10 + width - 1) * 2) * local_5c + local_60);
            float nx = v94 * h;
            float ny = v84 * h;
            float nrm[3];
            nrm[0] = b0 * inv + nx;
            nrm[1] = cc * inv + ny;
            nrm[2] = inv - (nx * b0 + ny * cc);
            float l2 = ((nrm[2] * nrm[2] + nrm[1] * nrm[1]) + nrm[0] * nrm[0]) + 1e-08f;
            float sc = 1.0f / sqrtf(l2);
            nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
            float alpha = sqrtf(v94 * v94 + v84 * v84) * local_54;
            if (alpha < 0.0f) alpha = 0.0f;
            if (alpha > 1.0f) alpha = 1.0f;
            *(unsigned*)(*(int*)(param_2 + 0x10) +
                         ((*(int*)(param_2 + 8) * param_3 + width - 1) *
                              *(int*)(param_2 + 8) + (width - 1)) * 4) =
                PackRGBA(nrm, alpha, idx, cscale);
        }
    }
    return 0;
}

// @ 0x00f8e6c0
bool __cdecl TerrainRayCast(SP::cTerrainMapU16* map, float base, float scale, Vec3* origin, Vec3* dir, Vec3* out)
{
    float hi = scale * 1.001f + base;
    float lo = base - scale * 1.001f;
    Vec3 o = *origin;
    Vec3 d = *dir;
    float len2 = (o.y * o.y + o.x * o.x) + o.z * o.z;
    if (lo * lo > len2)
        return false;

    FaceUV uv;
    DirToCubeInto(uv, o);
    float r = map->GetFloat(&uv) * scale + base;
    if (r * r > len2)
        return false;

    float tmin = 0.0f;
    float tmax = FLT_MAX;
    float t0, t1;
    if (!RaySphere(&o, &d, hi, &t0, &t1))
        return false;
    if (1e-6f > fabsf(t0 - t1))
        return false;
    tmin = Max(tmin, t0);
    tmax = Min(tmax, t1);
    if (RaySphere(&o, &d, lo, &t0, &t1) && tmin < t0)
        tmax = Min(tmax, t0);

    float len = sqrtf((d.x * d.x + d.y * d.y) + d.z * d.z);
    float inv = 1.0f / len;
    float nx = d.x * inv;
    float ny = d.y * inv;
    float nz = d.z * inv;
    float t = len * tmin;
    float tEnd = len * tmax + 2.0f;
    float prev = t;
    if (!(tEnd > t))
        return false;

    Vec3 p;
    for (;;) {
        p.x = nx * t + o.x;
        p.y = ny * t + o.y;
        p.z = nz * t + o.z;
        uv = DirToCube(p);
        float rr = map->GetFloat(&uv) * scale + base;
        rr = rr * rr;
        float pl = (p.x * p.x + p.z * p.z) + p.y * p.y;
        if (rr >= pl)
            break;
        prev = t;
        t = t + 2.0f;
        if (!(tEnd > t))
            return false;
    }

    float a = prev;
    float b = t;
    for (int i = 0; i < 20; i++) {
        float mid = (b + a) * 0.5f;
        p.x = nx * mid + o.x;
        p.y = ny * mid + o.y;
        p.z = nz * mid + o.z;
        uv = DirToCube(p);
        float rr = map->GetFloat(&uv) * scale + base;
        rr = rr * rr;
        float pl = (p.x * p.x + p.z * p.z) + p.y * p.y;
        if (fabsf(rr - pl) < 0.01f)
            break;
        if (!(rr >= pl))
            a = mid;
        else
            b = mid;
    }
    out->x = p.x;
    out->y = p.y;
    out->z = p.z;
    return true;
}

// @ 0x00f8fe60
namespace SP {
template <> void cTerrainMap<unsigned int>::BlendMapEdges()
{
    const int size = mFaceSize;
    const int faceArea = size * size;
    MapData blended;
    blended.resize(faceArea * 6);
    const int lastRow = (size - 1) * size;

    int faceBase = 0;
    for (int face = 0; face < 6; ++face) {
        // left and right columns
        for (int y = 1; y < size - 1; ++y) {
            blended[faceBase + y * size] =
                BlendTexels(face, 1, y, -2, y);
            blended[faceBase + y * size + size - 1] =
                BlendTexels(face, size - 2, y, size + 1, y);
        }
        // top and bottom rows
        for (int x = 1; x < size - 1; ++x) {
            blended[faceBase + x] =
                BlendTexels(face, x, 1, x, -2);
            blended[faceBase + lastRow + x] =
                BlendTexels(face, x, size - 2, x, size + 1);
        }
        // corners (diagonal neighbours)
        blended[faceBase] =
            BlendTexels(face, 1, 1, -2, -2);
        blended[faceBase + size - 1] =
            BlendTexels(face, size - 2, 1, size + 1, -2);
        blended[faceBase + lastRow] =
            BlendTexels(face, 1, size - 2, -2, size + 1);
        blended[faceBase + faceArea - 1] =
            BlendTexels(face, size - 2, size - 2, size + 1, size + 1);
        faceBase += faceArea;
    }

    // Copy only the border texels back.
    faceBase = 0;
    for (int face = 0; face < 6; ++face) {
        for (int y = 0; y < size; ++y) {
            mMapData[faceBase + y * size] = blended[faceBase + y * size];
            mMapData[faceBase + y * size + size - 1] = blended[faceBase + y * size + size - 1];
        }
        for (int x = 1; x < size - 1; ++x) {
            mMapData[faceBase + x] = blended[faceBase + x];
            mMapData[faceBase + lastRow + x] = blended[faceBase + lastRow + x];
        }
        faceBase += faceArea;
    }

    blended.erase(blended.begin(), blended.end());
}
}  // namespace SP
