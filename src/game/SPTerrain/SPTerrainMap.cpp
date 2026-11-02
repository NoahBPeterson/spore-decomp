// src/game/SPTerrain/SPTerrainMap.cpp -- migrated from slice(s) s00f918d0, s00f8f4d0, s00f8afd0, s00f87b30, s00f73260, s00f708d0, s00f6fc50, s00f6df40, s00f8fe60, s00f8e6c0, s00f8b2b0, s00f7d9d0 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainMap.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <xmmintrin.h>
#include <math.h>
#include <float.h>
#include "SP/cTerrainSphere.h"
#include "SP/cCubeMapIndex.h"
#include "cSPVector3.h"
#include <string.h>

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

// ---- items of slice s00f6df40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
#pragma intrinsic(memcpy, memset)
#pragma intrinsic(fabs)
struct cSPVector3_s00f6_df40 {
    float x, y, z;
    cSPVector3_s00f6_df40() {}
    cSPVector3_s00f6_df40(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3_s00f6_df40(const cSPVector3_s00f6_df40& o) : x(o.x), y(o.y), z(o.z) {}
};
struct cTerrainUV {
    float mU;      // +0x00
    float mV;      // +0x04
    int   mFace;   // +0x08
};
struct cTerrainMap_s00f6_df40 {
    float GetFloat(const cTerrainUV* uv);    // 0x00f8d620
};
struct cTerrainRef {
    void*         mPad00;   // +0x00
    void*         mPad04;   // +0x04
    cTerrainMap_s00f6_df40*  mpMap;    // +0x08
};
struct cFaceMapper {
    void*        mPad00;        // +0x00
    void*        mPad04;        // +0x04
    void*        mPad08;        // +0x08
    cTerrainRef* mpTerrain;     // +0x0c

    float GetFaceValue(const cSPVector3_s00f6_df40* pDir);
};
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
extern "C" void* __cdecl memset(void*, int, size_t);
// ---- items of slice s00f6df40 end

// ---- items of slice s00f6fc50 begin (TODO(rewrite): local stubs, replace by canonical classes)
#ifndef NULL
#define NULL 0
#endif
extern void* EffectsManager();   // 0x0067ddd0
struct cTerrainMapU32
{
	float GetFloat(const float* uv);
};
struct cTerrainMapU16_s00f6_fc50
{
	float GetFloat(const float* uv);
};
struct cCubeImage
{
	float SampleBilinear(const float* uv);
};
struct AtlasSampler
{
	double Sample(float v);
};
struct IEffect
{
	virtual void  vt00();
	virtual void  vt04();
	virtual void  vt08();
	virtual void  vt0c();
	virtual int   vt10();
	virtual void  vt14();
	virtual void  vt18();
	virtual void  vt1c();
	virtual float vt20(void* p);
};
typedef IEffect* (__thiscall *PFN_MgrLookup)(void* self, int key, int b);
struct CubeInner
{
	char   _pad00[8];
	void*  mp08;                     // +0x08  cTerrainMap<unsigned short>*
	void*  mp0c;                     // +0x0c  cTerrainMap<unsigned int>*
	void*  mp10;                     // +0x10  cCubeImage*
	void*  mp14;                     // +0x14  other sub-object
	char   _pad18[0x38 - 0x18];
	float  m38;                      // +0x38
	float  m3c;                      // +0x3c
	float  m40;                      // +0x40
	float  m44;                      // +0x44
	float  m48;                      // +0x48
};
struct CubeOwner
{
	char        _pad00[0xc];
	CubeInner*  mpInner;             // +0x0c
	void*       mp10;                // +0x10

	float Sample32(const float* p);          // 0x00F6FC50
	float Test32(const float* p);            // 0x00F6FE50
	float Slope16(const float* p);           // 0x00F70080
	float Test16(const float* p);            // 0x00F70250
	int   CountSubs();                       // 0x00F70440
	float SampleImage(const float* p);       // 0x00F70470
	float TestEffect(const float* p);        // 0x00F70660
	int   CountSubsEffect();                 // 0x00F70870
};
struct CubeUV { float u; float v; int face; };
static __forceinline void ProjectToFace(const float* p, CubeUV* out)
{
	float vx = p[0];
	float vy = p[1];
	float vz = p[2];
	float ax = (float)fabs(vx);
	float ay = (float)fabs(vy);
	float az = (float)fabs(vz);

	if (az < ax || az < ay)
	{
		if (ay < ax)
		{
			out->u = (vy / vx + 1.0f) * 0.5f;
			out->v = (vz / ax + 1.0f) * 0.5f;
			out->face = 2;
			if (vx < 0.0f)
				out->face = 3;
		}
		else
		{
			out->u = (vz / vy + 1.0f) * 0.5f;
			out->v = (vx / ay + 1.0f) * 0.5f;
			out->face = 4;
			if (vy < 0.0f)
				out->face = 5;
		}
	}
	else
	{
		out->u = (vx / vz + 1.0f) * 0.5f;
		out->v = (vy / az + 1.0f) * 0.5f;
		out->face = 0;
		if (vz < 0.0f)
			out->face = 1;
	}
}
// ---- items of slice s00f6fc50 end

// ---- items of slice s00f708d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_013ec478;    // 0.05f
typedef unsigned int uint;
struct V4 {
    float x, y, z, w;
};
float SampleBilinear(void* cubeImage, V4* uv);            // 0x00f8de70 SP::cCubeImage::SampleBilinear
float FbPtr9e70(void* p, float t);                        // 0x00fb9e70
float TerrainFloatU16(void* map, V4* uv);                 // 0x00f88650
float TerrainFloatU32(void* map, V4* uv);                 // 0x00f8d620
V4*   TerrainGetVector4(V4* out, V4* uv);                 // 0x00f89e50
struct IEff {
    void** mpVtbl;
};
inline void*  EffGet(void* mgr, unsigned int key, void* p) { return ((void*(*)(void*,unsigned int,void*))(((void**)mgr)[0x8c/4]))(mgr, key, p); }
inline void   EffAddRef(IEff* e)                           { ((void(*)(IEff*))(e->mpVtbl[0]))(e); }
inline void   EffRelease(IEff* e)                          { ((void(*)(IEff*))(e->mpVtbl[1]))(e); }
inline float  EffCall20(IEff* e, const V4* dir)            { return ((float(*)(IEff*,const V4*))(e->mpVtbl[0x20/4]))(e, dir); }
inline float AbsF(float f) { return f < 0.0f ? -f : f; }
struct CCubeQuery {
    char pad0[0x0c];
    struct Ctx* mpCtx;        // +0x0c
    struct Terrain* mpTerrain; // +0x10
    struct Viewer* mpViewer;   // +0x14
    void* mpSlot;              // +0x18
    // member functions
    float QueryA(const V4* dir);       // 0x00f708d0
    float QueryB(const V4* dir);       // 0x00f70c30
    float QueryC(const V4* dir);       // 0x00f70fa0
    float QueryD(const V4* dir);       // 0x00f71220
    V4*   GetCubeUV(V4* out);          // 0x00f713c0
    V4*   DirToTerrainColor(V4* out, const V4* dir);  // 0x00f713e0
    V4*   GetColorA(V4* out);          // 0x00f715d0
    V4*   GetColorB(V4* out);          // 0x00f71610
    V4*   GetScaledColor(V4* out, const V4* unused);  // 0x00f716b0
};
struct Ctx {
    char pad0[8];
    void* mpMapA;             // +0x08
    void* mpMapB;             // +0x0c
    void* mpCube;             // +0x10
    void* mpUV;               // +0x14
    char pad1[0x38 - 0x18];
    float f38;                // +0x38
    float f3c;                // +0x3c
    float f40;                // +0x40
    float f44;                // +0x44
    float f48;                // +0x48
};
struct Terrain {
    char pad0[0x2f4];
    char body[0x2f4];         // +0x2f4 base
};
struct Viewer {
    char pad0[0x14];
    void* mpCubeImage;        // +0x14
};
static void CubeUV_s00f7_08d0(const V4* dir, float* uv, uint* face)
{
    float cx = dir->x, cy = dir->y, cz = dir->z;
    float ax = AbsF(cx), ay = AbsF(cy), az = AbsF(cz);
    if (az >= ax && az >= ay) {
        uv[0] = (cx / cz + 1.0f) * 0.5f;
        uv[1] = (cy / az + 1.0f) * 0.5f;
        *face = cz < 0.0f ? 1 : 0;
    } else if (ay >= ax) {
        uv[0] = (cz / cy + 1.0f) * 0.5f;
        uv[1] = (cx / ay + 1.0f) * 0.5f;
        *face = cy < 0.0f ? 5 : 4;
    } else {
        uv[0] = (cy / cx + 1.0f) * 0.5f;
        uv[1] = (cz / ax + 1.0f) * 0.5f;
        *face = cx < 0.0f ? 3 : 2;
    }
}
// ---- items of slice s00f708d0 end

// ---- items of slice s00f73260 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3_s00f7_3260 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct Mat33 { float m[9]; };
struct FaceUV_s00f7_3260 { float u; float v; int face; };
struct Xform {
    uint32_t flags;                       // +0x00  (bit 1: rotated, bit 2: biased)
    Vec3_s00f7_3260     t;                           // +0x04
    float    scale;                       // +0x10
    float    m[9];                        // +0x14
    float    pad38;                       // +0x38
    void InverseTransformPoint(Vec3_s00f7_3260* v) const;  // 0x007CDA70
};
namespace SP {
struct cTerrainMapU16_s00f7_3260 {
    float GetFloat(const FaceUV_s00f7_3260* uv);               // 0x00f8d620
    void  GetVector4(float* out, const FaceUV_s00f7_3260* uv); // 0x00f89e50
};
}
void  FUN_00a81b80(const Vec3_s00f7_3260* n, Mat33* out);                       // 0x00a81b80
Quat& QuaternionFromMatrix33(Quat* out, const Mat33* m, float eps);  // 0x00472b80
static const float kEps  = 1e-06f;
static __forceinline void DirToCubeInto_s00f7_3260(FaceUV_s00f7_3260& r, const Vec3_s00f7_3260& v)
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
static __forceinline Vec3_s00f7_3260 ForwardPoint(const Xform* xf, float dx, float dy, float dz)
{
    if (xf->flags & 2) {
        // The three rotated components are each staged through memory before the scale pass
        // (the original keeps them in a Vec3 local that the scale pass then reads back).
        float rx = (xf->m[6] * dz + xf->m[3] * dy) + xf->m[0] * dx;
        float ry = (xf->m[7] * dz + xf->m[4] * dy) + xf->m[1] * dx;
        float rz = (xf->m[8] * dz + xf->m[5] * dy) + xf->m[2] * dx;
        dx = rx; dy = ry; dz = rz;
    }
    float s = xf->scale;
    Vec3_s00f7_3260 p;
    p.x = xf->t.x + s * dx;
    p.y = xf->t.y + s * dy;
    p.z = (xf->t.z + s * dz) + kEps;
    return p;
}
static __forceinline Vec3_s00f7_3260 RotateBy(const Xform* xf, const Vec3_s00f7_3260& v)
{
    float z = v.z;
    float y = v.y;
    float x = v.x;
    Vec3_s00f7_3260 r;
    r.x = (xf->m[2] * z + xf->m[1] * y) + xf->m[0] * x;
    r.y = (xf->m[5] * z + xf->m[4] * y) + xf->m[3] * x;
    r.z = (xf->m[8] * z + xf->m[7] * y) + xf->m[6] * x;
    return r;
}
struct cTerrainSphere_s00f7_3260 {
    uint8_t pad00[0x0c];
    float base;                       // +0x0c
    float scale;                      // +0x10
    float minv;                       // +0x14
    SP::cTerrainMapU16_s00f7_3260* heightMap;    // +0x18
    SP::cTerrainMapU16_s00f7_3260* normalMap;    // +0x1c

    bool SampleHeight(const Vec3_s00f7_3260* dir, Vec3_s00f7_3260* outPos, Vec3_s00f7_3260* outN, Quat* outQ, const Xform* xf, int);    // 0x00f73260
    bool SampleOffset(float extra, int, Vec3_s00f7_3260* pos, Vec3_s00f7_3260* outN, const Xform* xf, int);                  // 0x00f73760
    bool SampleNormal(const Vec3_s00f7_3260* dir, Vec3_s00f7_3260* outPos, Vec3_s00f7_3260* outN, Quat* outQ, const Xform* xf, int);    // 0x00f73c10
};
// ---- items of slice s00f73260 end

// ---- items of slice s00f87b30 begin (TODO(rewrite): local stubs, replace by canonical classes)
int __cdecl SP_WrapCubeFace(int n, int* face, int* x, int* y, int* u, int* v);  // 0x00684ca0
namespace SP {
struct cCubeMapIndex_s00f8_7b30 { int mCol; int mRow; int mFace; };
}
namespace SP {
struct cSPVector3_s00f8_7b30 { float x, y, z; };
}
namespace SP {
class cTerrainMapBase_s00f8_7b30 { public:
    void* mVftable;        // +0x00
    int mnRefCount;        // +0x04
    unsigned mFaceSize;    // +0x08
    unsigned mModCount;    // +0x0c
};
}
namespace SP {
template <class T> class cTerrainMap_s00f8_7b30 : public cTerrainMapBase_s00f8_7b30 { public:
    T* mBegin;             // +0x10 (eastl::vector<T>::mpBegin)
    T* mEnd;
    T* mCap;

    void SetCell(const cCubeMapIndex_s00f8_7b30& c, T v);
    int  GetRelativeIndex(int face, int x, int y, int dx, int dy);
    void Convolve(int face, int x, int y, float* dst, const float* k, int unused);
    void DownSampleMap(const cTerrainMap_s00f8_7b30& src);
    void CopyMap(const cTerrainMap_s00f8_7b30& src);
};
}
using SP::cCubeMapIndex_s00f8_7b30;
using SP::cSPVector3_s00f8_7b30;
using SP::cTerrainMap_s00f8_7b30;
namespace SP {
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
}
namespace SP {
static __declspec(noinline) unsigned char SatA(float x)
{
    __m128 v = _mm_set_ss(x);
    v = _mm_max_ss(_mm_setzero_ps(), v);
    v = _mm_mul_ss(v, _mm_set_ss(255.0f));
    v = _mm_min_ss(v, _mm_set_ss(255.0f));
    return (unsigned char)_mm_cvtss_si32(v);
}
}
// ---- items of slice s00f87b30 end

// ---- items of slice s00f8afd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct MapU32 {
    void*          mVftable;   // +0x00
    int            mnRefCount; // +0x04
    int            mFaceSize;  // +0x08
    int            mModCount;  // +0x0c
    unsigned int*  mBegin;     // +0x10
};
struct MapU16 {
    void*           mVftable;   // +0x00
    int             mnRefCount; // +0x04
    int             mFaceSize;  // +0x08
    int             mModCount;  // +0x0c
    unsigned short* mBegin;     // +0x10
};
#define HEIGHT_SCALE 3.0518509447574615e-05f   // 1/32767
#define VALUE_SCALE  0.3921568989753723f       // 100/255
// ---- items of slice s00f8afd0 end

// ---- items of slice s00f8f4d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* operator_new(int size, int align, int a3, const char* a4,
                              int a5, int a6, const char* file, int line); // 0xf473d0
extern "C" void  operator_delete__(void* p);                                  // 0xf47380
extern "C" void  operator_new__(void* dst, const void* src, int len);         // 0x11e073e
extern "C" void* eastl_fill(void* dst, const void* src, int nbytes);          // 0x11e0744
extern "C" void  DoFill(void* first, void* last, const void* value);          // 0xa177f0
extern "C" void  FUN_00f8f130();                                              // 0xf8f130
extern "C" void  FUN_00f8f330();                                              // 0xf8f330
struct VecGrower {
    void* Grow(int n, const void* srcBegin, const void* srcEnd);   // 0x00f8eef0
};
#define ALLOC_FILE \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
struct VecF {
    float* mpBegin;   // +0x00
    float* mpEnd;     // +0x04
    float* mpCap;     // +0x08

    void Insert(float* pos, unsigned int n, const float* pvalue);
};
struct VecAI {
    char* mpBegin;   // +0x00
    char* mpEnd;     // +0x04
    char* mpCap;     // +0x08

    void Insert(char* pos, unsigned int n, const char* pvalue);
};
struct VecFAssign {
    float* mpBegin;   // +0x00
    float* mpEnd;     // +0x04
    float* mpCap;     // +0x08

    VecFAssign* Assign(VecFAssign* other);
};
struct GmeListF {
    void* m_vtbl;    // +0x00
    char  m_pad04[0x0c];
    void* mpBegin;   // +0x10
    void* mpEnd;     // +0x14

    void DtorF();
};
struct GmeListS {
    void* m_vtbl;    // +0x00
    char  m_pad04[0x0c];
    void* mpBegin;   // +0x10
    void* mpEnd;     // +0x14

    void DtorH();
};
struct SimVec12 {
    void* m_vtbl;    // +0x00
    int   m_pad04;   // +0x04
    int   mCount;    // +0x08
    char  m_pad0c[0x04];
    void* mpBegin;   // +0x10
    void* mpEnd;     // +0x14
    void* mpCap;     // +0x18

    SimVec12* Ctor(int n, const void* init);
    void DtorB();
    void* DtorD(int freeFlag);
};
struct GmeListFB {
    void* m_vtbl;    // +0x00
    char  m_pad04[0x0c];
    void* mpBegin;   // +0x10
    void* mpEnd;     // +0x14

    void* DtorI(int freeFlag);
};
struct GmeListSB {
    void* m_vtbl;    // +0x00
    char  m_pad04[0x0c];
    void* mpBegin;   // +0x10
    void* mpEnd;     // +0x14

    void* DtorC(int freeFlag);
};
struct Vec0C {
    char* mpBegin;   // +0x00
    char* mpEnd;     // +0x04

    char* erase(char* a, char* b);
};
struct GmeListV3 {
    void* m_vtbl;    // +0x00
    char  m_pad04[0x0c];
    Vec0C mVec;      // +0x10

    void DtorE();
    void* DtorJ(int freeFlag);
};
struct EastlVec {
    char* mpBegin;   // +0x00
    char* mpEnd;     // +0x04

    void Resize16(unsigned int n);
    void Resize08(unsigned int n);
    void Resize4F(unsigned int n);
};
// ---- items of slice s00f8f4d0 end

// ---- items of slice s00f918d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl MemCopy(void* dst, const void* src, unsigned n);            // 0x011e0744 (memmove thunk)
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
// ---- items of slice s00f918d0 end

// @ 0x00f6ebe0
float cFaceMapper::GetFaceValue(const cSPVector3_s00f6_df40* pDir)
{
    cTerrainMap_s00f6_df40* pMap = mpTerrain->mpMap;
    if (pMap != 0) {
        cSPVector3_s00f6_df40 d = *pDir;
        float fx = (float)fabs(d.x);
        float fy = (float)fabs(d.y);
        float fz = (float)fabs(d.z);
        cTerrainUV uv;
        if (fx <= fz && fy <= fz) {
            uv.mU = (d.x / d.z + 1.0f) * 0.5f;
            uv.mV = (d.y / fz + 1.0f) * 0.5f;
            if (d.z >= 0.0f) {
                uv.mFace = 0;
                return pMap->GetFloat(&uv);
            }
            uv.mFace = 1;
            return pMap->GetFloat(&uv);
        }
        if (fy >= fx) {
            uv.mU = (d.z / d.y + 1.0f) * 0.5f;
            uv.mV = (d.x / fy + 1.0f) * 0.5f;
            if (d.y >= 0.0f) {
                uv.mFace = 4;
                return pMap->GetFloat(&uv);
            }
            uv.mFace = 5;
            return pMap->GetFloat(&uv);
        }
        uv.mU = (d.y / d.x + 1.0f) * 0.5f;
        uv.mV = (d.z / fx + 1.0f) * 0.5f;
        uv.mFace = 2;
        if (d.x < 0.0f)
            uv.mFace = 3;
        return pMap->GetFloat(&uv);
    }
    return 0.0f;
}

// @ 0x00f6fc50
float CubeOwner::Sample32(const float* p)
{
	CubeInner* in = mpInner;
	if (in->mp08 == NULL || in->mp0c == NULL)
		return 0.0f;

	float f1 = in->m38;
	float f2 = in->m3c;
	float f3 = in->m38;
	float f4 = in->m48;

	CubeUV uv;
	ProjectToFace(p, &uv);

	float r1 = ((cTerrainMapU32*)in->mp0c)->GetFloat(&uv.u);
	if (f4 <= r1 * f1)
	{
		float r2 = ((cTerrainMapU16_s00f6_fc50*)in->mp08)->GetFloat(&uv.u);
		if (f2 * f3 < r2 * f1)
			return r1;
	}
	return 0.0f;
}

// @ 0x00f6fe50
float CubeOwner::Test32(const float* p)
{
	CubeInner* in = mpInner;
	if (in->mp08 == NULL || in->mp0c == NULL)
		return 0.0f;

	float f1 = in->m38;
	float f2 = in->m3c;
	float f3 = in->m38;
	float f4 = in->m48;

	CubeUV uv;
	ProjectToFace(p, &uv);

	float r1 = ((cTerrainMapU32*)in->mp0c)->GetFloat(&uv.u);
	if (f4 <= r1 * f1)
	{
		float r2 = ((cTerrainMapU16_s00f6_fc50*)in->mp08)->GetFloat(&uv.u);
		if (f2 * f3 < r2 * f1)
			return 1.0f;
		return 0.0f;
	}
	return 0.0f;
}

// @ 0x00f70080
float CubeOwner::Slope16(const float* p)
{
	CubeInner* in = mpInner;
	if (in->mp08 == NULL)
		return 0.0f;

	float f1 = in->m38;
	float f2 = in->m3c;
	float f3 = in->m38;

	CubeUV uv;
	ProjectToFace(p, &uv);

	float r = ((cTerrainMapU16_s00f6_fc50*)in->mp08)->GetFloat(&uv.u);
	float hi = f2 * f3;
	if (hi <= r * f1)
		return 0.0f;
	return (hi - r * f1) / (hi + f1);
}

// @ 0x00f70250
float CubeOwner::Test16(const float* p)
{
	CubeInner* in = mpInner;
	if (in->mp08 == NULL)
		return 0.0f;

	float f1 = in->m38;
	float f2 = in->m3c;
	float f3 = in->m38;

	CubeUV uv;
	ProjectToFace(p, &uv);

	float r = ((cTerrainMapU16_s00f6_fc50*)in->mp08)->GetFloat(&uv.u);
	if (f2 * f3 > r * f1)
		return 1.0f;
	return 0.0f;
}

// @ 0x00f70470
float CubeOwner::SampleImage(const float* p)
{
	CubeInner* in = mpInner;
	if (in->mp10 == NULL)
		return 0.0f;

	CubeUV uv;
	ProjectToFace(p, &uv);

	float r = ((cCubeImage*)in->mp10)->SampleBilinear(&uv.u);
	double v = ((AtlasSampler*)mp10)->Sample(r);
	if (v < 0.05)
		return 0.0f;
	return 1.0f;
}

// @ 0x00f70660
float CubeOwner::TestEffect(const float* p)
{
	CubeUV uv;
	ProjectToFace(p, &uv);

	CubeInner* in = mpInner;
	if (in->mp08 != NULL)
	{
		float thr = (in->m44 + in->m3c) * in->m38;
		float r = ((cTerrainMapU16_s00f6_fc50*)in->mp08)->GetFloat(&uv.u);
		if (r * in->m38 <= thr)
			return 0.0f;
	}

	void* mgr = EffectsManager();
	IEffect* obj = ((PFN_MgrLookup)(*(void***)mgr)[0x8c / 4])(mgr, 0x107ae878, 0);
	if (obj != NULL)
	{
		obj->vt00();
		if (obj->vt20((void*)p) != 0.0f)
		{
			obj->vt04();
			return 1.0f;
		}
		obj->vt04();
	}
	return 0.0f;
}

// @ 0x00f708d0
float CCubeQuery::QueryA(const V4* dir)
{
    float uv[2];
    uint face;
    V4  uv4;
    CubeUV_s00f7_08d0(dir, uv, &face);

    Ctx* ctx = mpCtx;
    if (ctx->mpCube) {
        CubeUV_s00f7_08d0(dir, &uv4.x, (uint*)&uv4.z);   // recomputed for the bilinear tap
        uv4.w = uv4.z;
        float s = SampleBilinear(&uv4, &uv4);
        (void)s;
        float t = FbPtr9e70(mpTerrain, s);
        if (t > DAT_013ec478)
            goto Lfail;
    }
    if (ctx->mpMapA) {
        float f = ctx->f38;
        V4 tap;
        tap.x = (ctx->f44 + ctx->f3c) * f;
        tap.y = ctx->f48;
        float terrain = TerrainFloatU32(ctx->mpMapA, &tap);
        if (terrain * f >= tap.x)
            goto Lfail;
    }
    {
        IEff* eff = (IEff*)EffGet(EffectsManager(), 0x107ae878, 0);
        if (eff) {
            EffAddRef(eff);
            float r = EffCall20(eff, dir);
            EffRelease(eff);
            if (r != 0.0f)
                return 1.0f;
        }
    }
Lfail:
    return 0.0f;
}

// @ 0x00f70c30
float CCubeQuery::QueryB(const V4* dir)
{
    float uv[2];
    uint face;
    V4  uv4;
    CubeUV_s00f7_08d0(dir, uv, &face);

    Ctx* ctx = mpCtx;
    if (ctx->mpCube) {
        CubeUV_s00f7_08d0(dir, &uv4.x, (uint*)&uv4.z);
        uv4.w = uv4.z;
        float s = SampleBilinear(&uv4, &uv4);
        float t = FbPtr9e70(mpTerrain, s);
        if (t >= DAT_013ec478)
            goto Lfail;
    }
    if (ctx->mpMapA) {
        float f = ctx->f38;
        V4 tap;
        tap.x = (ctx->f44 + ctx->f3c) * f;
        tap.y = ctx->f48;
        float terrain = TerrainFloatU16(ctx->mpMapA, &tap);
        if (terrain * f <= tap.x)
            goto Lfail;
    }
    {
        IEff* eff = (IEff*)EffGet(EffectsManager(), 0x107ae878, 0);
        if (eff) {
            EffAddRef(eff);
            float r = EffCall20(eff, dir);
            EffRelease(eff);
            if (r != 0.0f)
                return 1.0f;
        }
    }
Lfail:
    return 0.0f;
}

// @ 0x00f70fa0
float CCubeQuery::QueryC(const V4* dir)
{
    float uv[2];
    uint face;
    CubeUV_s00f7_08d0(dir, uv, &face);

    Ctx* ctx = mpCtx;
    if (ctx->mpCube) {
        float s = SampleBilinear(&uv[0], (V4*)&uv[0]);
        float t = FbPtr9e70(mpTerrain, s);
        if (t < 0.95f)
            return 0.0f;
    }
    if (ctx->mpMapA && ctx->mpMapB) {
        float f = ctx->f38;
        float hi = ctx->f48;
        float lo = (ctx->f44 + ctx->f3c) * f;
        float a = TerrainFloatU32(ctx->mpMapA, (V4*)&uv[0]);
        if (!(hi <= a * f))
            goto Lcheck2;
        return 0.0f;
    Lcheck2:
        {
            float b = TerrainFloatU16(ctx->mpMapB, (V4*)&uv[0]);
            if (!(b * f <= lo))
                goto Lcheck3;
            return 0.0f;
        }
    }
Lcheck3:
    {
        IEff* eff = (IEff*)EffGet(EffectsManager(), 0x107ae878, 0);
        if (eff) {
            EffAddRef(eff);
            float r = EffCall20(eff, dir);
            EffRelease(eff);
            if (r != 0.0f)
                return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00f713e0
V4* CCubeQuery::DirToTerrainColor(V4* out, const V4* dir)
{
    if (!mpCtx->mpUV) {
        out->x = 1.0f; out->y = 1.0f; out->z = 1.0f; out->w = 1.0f;
        return out;
    }
    float uv2[2];
    uint face;
    CubeUV_s00f7_08d0(dir, uv2, &face);
    {
        V4 key;
        key.x = uv2[0];
        key.y = uv2[1];
        key.z = (float)face;
        V4* r = TerrainGetVector4(&key, &key);
        out->x = r->x; out->y = r->y; out->z = r->z;
    }
    out->w = 1.0f;
    return out;
}

// @ 0x00f73260
bool cTerrainSphere_s00f7_3260::SampleHeight(const Vec3_s00f7_3260* dir, Vec3_s00f7_3260* outPos, Vec3_s00f7_3260* outN, Quat* outQ, const Xform* xf, int)
{
    Vec3_s00f7_3260 p = ForwardPoint(xf, dir->x, dir->y, dir->z);
    float len = sqrtf((p.z * p.z + p.y * p.y) + p.x * p.x);

    FaceUV_s00f7_3260 uv;
    DirToCubeInto_s00f7_3260(uv, p);
    float h = scale * heightMap->GetFloat(&uv);
    float radius = (xf->pad38 + base) + (h < minv ? minv : h);
    // comiss + jb: unordered (NaN) counts as "below", i.e. the guard fires
    if (!(len >= kEps))
        return false;

    float inv = 1.0f / len;
    Vec3_s00f7_3260 n;
    n.x = inv * p.x;
    n.y = inv * p.y;
    n.z = p.z * inv;
    Vec3_s00f7_3260 nn = n;

    Vec3_s00f7_3260 out;
    out.x = n.x * radius;
    out.y = n.y * radius;
    out.z = n.z * radius;
    xf->InverseTransformPoint(&out);
    *outPos = out;

    if (outN) {
        if (xf->flags & 2)
            nn = RotateBy(xf, n);
        *outN = nn;
    }
    if (outQ) {
        Mat33 m;
        FUN_00a81b80(&nn, &m);
        Quat q;   // the helper's out-param is a stack temporary; the result is copied to *outQ
        *outQ = QuaternionFromMatrix33(&q, &m, 0.0f);
    }
    return true;
}

// @ 0x00f73760
bool cTerrainSphere_s00f7_3260::SampleOffset(float extra, int, Vec3_s00f7_3260* pos, Vec3_s00f7_3260* outN, const Xform* xf, int)
{
    Vec3_s00f7_3260 p = ForwardPoint(xf, pos->x, pos->y, pos->z);
    float len = sqrtf((p.z * p.z + p.y * p.y) + p.x * p.x);

    FaceUV_s00f7_3260 uv;
    DirToCubeInto_s00f7_3260(uv, p);
    float h = scale * heightMap->GetFloat(&uv);
    float radius = ((xf->pad38 + base) + (h < minv ? minv : h)) + extra;
    // comiss + jbe: unordered (NaN) counts as "below or equal", i.e. the guard fires
    if (!(radius > len))
        return false;

    float inv = 1.0f / len;
    Vec3_s00f7_3260 out;
    out.x = (inv * p.x) * radius;
    out.y = (inv * p.y) * radius;
    out.z = (p.z * inv) * radius;

    float v4[4];
    normalMap->GetVector4(v4, &uv);
    Vec3_s00f7_3260 n;
    n.x = v4[0] * 2.0f - 1.0f;
    n.y = v4[1] * 2.0f - 1.0f;
    n.z = v4[2] * 2.0f - 1.0f;

    if (xf->scale != 1.0f || (xf->flags & 6)) {
        xf->InverseTransformPoint(&out);
        if (xf->flags & 2)
            n = RotateBy(xf, n);
    }

    *pos = out;
    *outN = n;
    return true;
}

// @ 0x00f73c10
bool cTerrainSphere_s00f7_3260::SampleNormal(const Vec3_s00f7_3260* dir, Vec3_s00f7_3260* outPos, Vec3_s00f7_3260* outN, Quat* outQ, const Xform* xf, int)
{
    Vec3_s00f7_3260 p = ForwardPoint(xf, dir->x, dir->y, dir->z);
    float len = sqrtf((p.z * p.z + p.y * p.y) + p.x * p.x);
    // comiss + jb: unordered (NaN) counts as "below", i.e. the guard fires
    if (!(len >= kEps))
        return false;

    float inv = 1.0f / len;
    Vec3_s00f7_3260 n;
    n.x = inv * p.x;
    n.y = p.y * inv;
    n.z = p.z * inv;

    FaceUV_s00f7_3260 uv;
    DirToCubeInto_s00f7_3260(uv, p);
    float h = scale * heightMap->GetFloat(&uv);
    float radius = (xf->pad38 + base) + (h < minv ? minv : h);

    Vec3_s00f7_3260 out;
    out.x = n.x * radius;
    out.y = n.y * radius;
    out.z = n.z * radius;

    float v4[4];
    normalMap->GetVector4(v4, &uv);
    Vec3_s00f7_3260 nn;
    nn.x = v4[0] * 2.0f - 1.0f;
    nn.y = v4[1] * 2.0f - 1.0f;
    nn.z = v4[2] * 2.0f - 1.0f;

    xf->InverseTransformPoint(&out);
    *outPos = out;

    if (outN) {
        if (xf->flags & 2)
            nn = RotateBy(xf, nn);
        *outN = nn;
    }
    if (outQ) {
        Mat33 m;
        FUN_00a81b80(&nn, &m);
        Quat q;   // the helper's out-param is a stack temporary; the result is copied to *outQ
        *outQ = QuaternionFromMatrix33(&q, &m, 0.0f);
    }
    return true;
}

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

// @ 0x00f87b30
template <> void cTerrainMap_s00f8_7b30<float>::SetCell(const cCubeMapIndex_s00f8_7b30& c, float v)
{
    mBegin[(c.mFace * (int)mFaceSize + c.mRow) * (int)mFaceSize + c.mCol] = v;
}

// @ 0x00f87b60
template <> int cTerrainMap_s00f8_7b30<float>::GetRelativeIndex(int face, int x, int y, int dx, int dy)
{
    int size = (int)mFaceSize;
    y += dy;
    x += dx;
    if ((~(size - 1)) & (x | y))
        SP_WrapCubeFace(size, &face, &x, &y, 0, 0);
    return (size * face + y) * size + x;
}

// @ 0x00f87bd0
template <> void cTerrainMap_s00f8_7b30<cSPVector3_s00f8_7b30>::SetCell(const cCubeMapIndex_s00f8_7b30& c, cSPVector3_s00f8_7b30 v)
{
    mBegin[(c.mFace * (int)mFaceSize + c.mRow) * (int)mFaceSize + c.mCol] = v;
}

// @ 0x00f87c10
namespace SP {
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
template <> void cTerrainMap_s00f8_7b30<float>::Convolve(int face, int x, int y, float* dst, const float* k, int)
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
template <> void cTerrainMap_s00f8_7b30<float>::DownSampleMap(const cTerrainMap_s00f8_7b30<float>& src)
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
template <> void cTerrainMap_s00f8_7b30<float>::CopyMap(const cTerrainMap_s00f8_7b30<float>& src)
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
template <> void cTerrainMap_s00f8_7b30<cSPVector3_s00f8_7b30>::CopyMap(const cTerrainMap_s00f8_7b30<cSPVector3_s00f8_7b30>& src)
{
    if (src.mFaceSize != mFaceSize)
        return;
    __m128* d = (__m128*)mBegin;
    const __m128* s = (const __m128*)src.mBegin;
    unsigned n = (mFaceSize * mFaceSize * 6 * sizeof(cSPVector3_s00f8_7b30)) >> 4;
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

// @ 0x00f8afd0
void __cdecl ComputeThresholdFraction(const MapU32& src, const MapU16& dst, float threshold, float* outA, float* outB, float* outC, float* outD)
{
    int total = src.mFaceSize * src.mFaceSize * 6;
    const unsigned char*  values  = (const unsigned char*)src.mBegin;
    const unsigned short* heights = dst.mBegin;
    unsigned int above = 0;
    unsigned int lt3 = 0;
    unsigned int mid = 0;
    unsigned int gt32 = 0;
    bool want = outA != 0 || outB != 0 || outC != 0;

#define CELL(n)                                                        \
    do {                                                               \
        int h = (int)heights[(n)] - 0x8000;                            \
        if ((float)h * HEIGHT_SCALE > threshold) {                     \
            ++above;                                                   \
            if (want) {                                                \
                float v = (float)values[(n) * 4 + 3] * VALUE_SCALE;    \
                if (v < 3.0f)      ++lt3;                              \
                else if (v > 32.0f) ++gt32;                            \
                else               ++mid;                              \
            }                                                          \
        }                                                              \
    } while (0)

    for (int i = 0; i < total; ++i)
        CELL(i);

#undef CELL

    *outD = 1.0f - (float)above / (float)total;
    if (above == 0)
        above = 1;
    if (outA != 0)
        *outA = (float)lt3 / (float)above;
    if (outB != 0)
        *outB = (float)mid / (float)above;
    if (outC != 0)
        *outC = (float)gt32 / (float)above;
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

// @ 0x00f8f4d0
void VecF::Insert(float* pos, unsigned int n, const float* pvalue)
{
    if (n > (unsigned int)((mpCap - mpEnd) >> 2)) {
        int size = (int)((mpEnd - mpBegin) >> 2);
        unsigned int newCap = (unsigned int)(size * 2);
        if (size == 0)
            newCap = 1;
        unsigned int need = (unsigned int)size + n;
        if (newCap <= need)
            newCap = need;
        float* pNew;
        if (newCap == 0)
            pNew = 0;
        else
            pNew = (float*)operator_new((int)(newCap * 4), 0x80, 0, "Simulator", 0, 0,
                                        ALLOC_FILE, 0xe5);
        unsigned int off = (unsigned int)((char*)pos - (char*)mpBegin);
        char* base = (char*)eastl_fill(pNew, mpBegin, (int)off);
        float* dst = (float*)(base + off);
        float v = *pvalue;
        for (unsigned int i = 0; i < n; ++i)
            dst[i] = v;
        unsigned int tail = (unsigned int)((char*)mpEnd - (char*)pos);
        char* newEnd = (char*)eastl_fill(dst + n, pos, (int)tail);
        if (mpBegin != 0)
            operator_delete__(mpBegin);
        mpBegin = pNew;
        mpEnd = (float*)(newEnd + ((tail >> 2) << 2));
        mpCap = (float*)((char*)pNew + (int)(newCap * 4));
    } else if (n != 0) {
        float v = *pvalue;
        unsigned int tailCount = (unsigned int)((mpEnd - pos) >> 2);
        if (n < tailCount) {
            float* src = mpEnd - n;
            eastl_fill(mpEnd, src, (int)(n * 4));
            mpEnd = (float*)((char*)mpEnd + n * 4);
            memmove(pos + n, pos, (int)((char*)src - (char*)pos));
            for (float* q = pos; q != pos + n; ++q)
                *q = v;
        } else {
            float* oldEnd = mpEnd;
            unsigned int fill = n - tailCount;
            for (unsigned int i = 0; i < fill; ++i)
                mpEnd[i] = v;
            mpEnd = (float*)((char*)mpEnd + fill * 4);
            eastl_fill(mpEnd, pos, (int)((char*)oldEnd - (char*)pos));
            mpEnd = (float*)((char*)mpEnd + tailCount * 4);
            for (float* q = pos; q != oldEnd; ++q)
                *q = v;
        }
    }
}

// @ 0x00f8f6d0
void VecAI::Insert(char* pos, unsigned int n, const char* pvalue)
{
    if (n > (unsigned int)((mpCap - mpEnd) / 0xc)) {
        int size = (int)((mpEnd - mpBegin) / 0xc);
        unsigned int newCap = (unsigned int)(size * 2);
        if (size == 0)
            newCap = 1;
        unsigned int need = (unsigned int)size + n;
        if (newCap <= need)
            newCap = need;
        char* pNew;
        if (newCap == 0)
            pNew = 0;
        else
            pNew = (char*)operator_new((int)(newCap * 0xc), 0x80, 0, "Simulator", 0, 0,
                                       ALLOC_FILE, 0xe5);
        unsigned int off = (unsigned int)(pos - mpBegin);
        char* base = (char*)eastl_fill(pNew, mpBegin, (int)off);
        char* dst = base + off;
        char tmp[0xc];
        *(int*)(tmp + 0) = *(int*)(pvalue + 0);
        *(int*)(tmp + 4) = *(int*)(pvalue + 4);
        *(int*)(tmp + 8) = *(int*)(pvalue + 8);
        for (unsigned int i = 0; i < n; ++i) {
            *(int*)(dst + 0) = *(int*)(tmp + 0);
            *(int*)(dst + 4) = *(int*)(tmp + 4);
            *(int*)(dst + 8) = *(int*)(tmp + 8);
            dst += 0xc;
        }
        unsigned int tail = (unsigned int)(mpEnd - pos);
        char* newEnd = (char*)eastl_fill(dst, pos, (int)tail);
        if (mpBegin != 0)
            operator_delete__(mpBegin);
        mpBegin = pNew;
        mpEnd = newEnd + ((tail / 0xc) * 0xc);
        mpCap = pNew + (int)(newCap * 0xc);
    } else if (n != 0) {
        char tmp[0xc];
        *(int*)(tmp + 0) = *(int*)(pvalue + 0);
        *(int*)(tmp + 4) = *(int*)(pvalue + 4);
        *(int*)(tmp + 8) = *(int*)(pvalue + 8);
        unsigned int tailCount = (unsigned int)((mpEnd - pos) / 0xc);
        if (n < tailCount) {
            char* src = mpEnd - (int)(n * 0xc);
            eastl_fill(mpEnd, src, (int)(n * 0xc));
            mpEnd = mpEnd + n * 0xc;
            memmove(pos + n * 0xc, pos, (int)(src - pos));
            for (char* q = pos; q != pos + n * 0xc; q += 0xc)
                DoFill(q, q + 0xc, tmp);
        } else {
            char* oldEnd = mpEnd;
            unsigned int fill = n - tailCount;
            char* q = mpEnd;
            for (unsigned int i = 0; i < fill; ++i) {
                DoFill(q, q + 0xc, tmp);
                q += 0xc;
            }
            mpEnd = mpEnd + fill * 0xc;
            eastl_fill(mpEnd, pos, (int)(oldEnd - pos));
            mpEnd = mpEnd + tailCount * 0xc;
            for (q = pos; q != oldEnd; q += 0xc)
                DoFill(q, q + 0xc, tmp);
        }
    }
}

// @ 0x00f8f8a0
VecFAssign* VecFAssign::Assign(VecFAssign* other)
{
    if (other == this)
        return this;
    float* srcBeg = other->mpBegin;
    float* dstBeg = mpBegin;
    float* srcEnd = other->mpEnd;
    unsigned int n = (unsigned int)((srcEnd - srcBeg) >> 2);
    if ((unsigned int)((mpCap - dstBeg) >> 2) < n) {
        float* p = (float*)((VecGrower*)this)->Grow((int)n, srcBeg, srcEnd);
        if (mpBegin != 0)
            operator_delete__(mpBegin);
        mpBegin = p;
        mpCap = p + n;
        mpEnd = p + n;
        return this;
    }
    unsigned int used = (unsigned int)((mpEnd - dstBeg) >> 2);
    if (used < n) {
        eastl_fill(dstBeg, srcBeg, (int)(used * 4));
        char* extra = (char*)other->mpBegin + ((char*)mpEnd - (char*)mpBegin);
        eastl_fill(mpEnd, extra, (int)((char*)other->mpEnd - extra));
        mpEnd = mpBegin + n;
        return this;
    }
    eastl_fill(dstBeg, srcBeg, (int)((char*)srcEnd - (char*)srcBeg));
    mpEnd = mpBegin + n;
    return this;
}

// @ 0x00f8f970
void GmeListF::DtorF()
{
    *(int*)this = 0x1490020;
    int endp = (int)mpEnd;
    int begp = (int)mpBegin;
    eastl_fill((void*)begp, (void*)endp, 0);
    int cnt = (endp - begp) >> 2;
    *(int*)((char*)this + 0x14) += -cnt * 4;
    if (*(int*)((char*)this + 0x10) != 0)
        operator_delete__(*(void**)((char*)this + 0x10));
    *(int*)this = 0x13ef094;
}

// @ 0x00f8f9c0
void GmeListS::DtorH()
{
    *(int*)this = 0x1490028;
    int endp = (int)mpEnd;
    int begp = (int)mpBegin;
    eastl_fill((void*)begp, (void*)endp, 0);
    int cnt = (endp - begp) >> 1;
    *(int*)((char*)this + 0x14) += -cnt * 2;
    if (*(int*)((char*)this + 0x10) != 0)
        operator_delete__(*(void**)((char*)this + 0x10));
    *(int*)this = 0x13ef094;
}

// @ 0x00f8fa10
SimVec12* SimVec12::Ctor(int n, const void* init)
{
    mCount = n;
    int size = n * n * 6;
    m_pad04 = 0;
    *(int*)this = 0x1490030;
    char* p;
    if (size == 0)
        p = 0;
    else
        p = (char*)operator_new(size, 0x80, 0, "Simulator", 0, 0, ALLOC_FILE, 0xe5);
    mpBegin = p;
    mpEnd   = p;
    mpCap   = p + size;
    if (size != 0)
        operator_new__(p, init, size);
    mpEnd = (char*)mpBegin + size;
    return this;
}

// @ 0x00f8fa90
void SimVec12::DtorB()
{
    *(int*)this = 0x1490030;
    int endp = (int)mpEnd;
    int begp = (int)mpBegin;
    eastl_fill((void*)begp, (void*)endp, 0);
    *(int*)((char*)this + 0x14) += begp - endp;
    if (*(int*)((char*)this + 0x10) != 0)
        operator_delete__(*(void**)((char*)this + 0x10));
    *(int*)this = 0x13ef094;
}

// @ 0x00f8fad0
void GmeListV3::DtorE()
{
    *(int*)this = 0x1490038;
    mVec.erase(mVec.mpBegin, mVec.mpEnd);
    if (mVec.mpBegin != 0)
        operator_delete__(mVec.mpBegin);
    *(int*)this = 0x13ef094;
}

// @ 0x00f8fb10
void* GmeListFB::DtorI(int freeFlag)
{
    *(int*)this = 0x1490020;
    int endp = (int)mpEnd;
    int begp = (int)mpBegin;
    eastl_fill((void*)begp, (void*)endp, 0);
    int cnt = (endp - begp) >> 2;
    *(int*)((char*)this + 0x14) += -cnt * 4;
    if (*(int*)((char*)this + 0x10) != 0)
        operator_delete__(*(void**)((char*)this + 0x10));
    *(int*)this = 0x13ef094;
    if (freeFlag & 1)
        operator_delete__(this);
    return this;
}

// @ 0x00f8fb70
void* GmeListSB::DtorC(int freeFlag)
{
    *(int*)this = 0x1490028;
    int endp = (int)mpEnd;
    int begp = (int)mpBegin;
    eastl_fill((void*)begp, (void*)endp, 0);
    int cnt = (endp - begp) >> 1;
    *(int*)((char*)this + 0x14) += -cnt * 2;
    if (*(int*)((char*)this + 0x10) != 0)
        operator_delete__(*(void**)((char*)this + 0x10));
    *(int*)this = 0x13ef094;
    if (freeFlag & 1)
        operator_delete__(this);
    return this;
}

// @ 0x00f8fbd0
void* SimVec12::DtorD(int freeFlag)
{
    *(int*)this = 0x1490030;
    int endp = (int)mpEnd;
    int begp = (int)mpBegin;
    eastl_fill((void*)begp, (void*)endp, 0);
    *(int*)((char*)this + 0x14) += begp - endp;
    if (*(int*)((char*)this + 0x10) != 0)
        operator_delete__(*(void**)((char*)this + 0x10));
    *(int*)this = 0x13ef094;
    if (freeFlag & 1)
        operator_delete__(this);
    return this;
}

// @ 0x00f8fc30
void* GmeListV3::DtorJ(int freeFlag)
{
    *(int*)this = 0x1490038;
    mVec.erase(mVec.mpBegin, mVec.mpEnd);
    if (mVec.mpBegin != 0)
        operator_delete__(mVec.mpBegin);
    *(int*)this = 0x13ef094;
    if (freeFlag & 1)
        operator_delete__(this);
    return this;
}

// @ 0x00f8fce0
void EastlVec::Resize16(unsigned int n)
{
    char* endp = mpEnd;
    char* begp = mpBegin;
    unsigned int used = (unsigned int)((endp - begp) >> 1);
    if (used < n) {
        unsigned int add = n - used;
        short zero = 0;
        ((void (__thiscall*)(EastlVec*, char*, unsigned int, short*))(void*)FUN_00f8f130)
            (this, endp, add, &zero);
        return;
    }
    char* dst = begp + n * 2;
    eastl_fill(dst, endp, 0);
    int cnt = (int)((endp - dst) >> 1);
    *(int*)((char*)this + 0x04) += -cnt * 2;
}

// @ 0x00f8fd40
void EastlVec::Resize08(unsigned int n)
{
    char* endp = mpEnd;
    char* begp = mpBegin;
    if ((unsigned int)(endp - begp) < n) {
        unsigned int add = n - (unsigned int)(endp - begp);
        char zero = 0;
        ((void (__thiscall*)(EastlVec*, char*, unsigned int, char*))(void*)FUN_00f8f330)
            (this, endp, add, &zero);
        return;
    }
    char* dst = begp + n;
    eastl_fill(dst, endp, 0);
    *(int*)((char*)this + 0x04) += dst - endp;
}

// @ 0x00f8fd90
void EastlVec::Resize4F(unsigned int n)
{
    char* endp = mpEnd;
    char* begp = mpBegin;
    unsigned int used = (unsigned int)((endp - begp) >> 2);
    if (used < n) {
        unsigned int add = n - used;
        float zero = 0.0f;
        ((void (__thiscall*)(EastlVec*, char*, unsigned int, float*))(void*)FUN_00f8f130)
            (this, endp, add, &zero);
        return;
    }
    char* dst = begp + n * 4;
    eastl_fill(dst, endp, 0);
    int cnt = (int)((endp - dst) >> 2);
    *(int*)((char*)this + 0x04) += -cnt * 4;
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

// @ 0x00f921d0
void CubeMapBuffer::SetSize(int size, int fill)
{
    mSize = size;
    CubeMapVec* v = (CubeMapVec*)&mpData;
    v->Fit(0, 0);
    v->Fit((unsigned)(size * size * 6), (const char*)&fill);
}
