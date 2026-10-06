// Planet terrain normal-map builder (SSE), @ 0x00f7d9d0 (41,301 bytes).
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE
//
// Only caller: SP::UpdateNormalMap (call at 0x00f8b53b, cdecl, 15 dword args, the last two unused).
// It turns a 512x512 face of 16-bit heights into packed A8R8G8B8 texels:
//   A = clamp(|height gradient| * slopeScale, 0, 1)   (slope)
//   R/G/B = the per-texel sphere normal (cube face point (u, v, 1) displaced by the height
//           gradient), with the three components rotated by the cube axis (0, 1 or 2) and
//           scaled by three per-channel factors (the caller passes +/-1 signs).
// The source buffer has one border row above the region: dst row y uses src rows y-1..y+1.
// Work is done in blocks of 8 columns x 2 rows, as two 4-texel groups ("quads"), with the next
// block's heights loaded one iteration ahead (hand-pipelined, which decides what an empty loop
// leaves for the right-edge tail below).
//
// Three loop shapes, each inlined for the three cube axes (9 bodies in the binary):
//   x0 < 4      : left edge. Blocks start at column 0; the left neighbour of column 0 is 0.
//   x1 >= 510   : right edge. Blocks start at column 4; the last 4 columns are a separate quad.
//   otherwise   : interior. Blocks start at column 4.
// The left-edge loop runs row pairs (y0-1)/2 .. (y1-1)/2 inclusive, the other two exclusive.
//
// The u/v coordinates are advanced by repeated float adds/subtracts (v += 1/256 for the second
// row, then -= 1/256), so the rounding drift of the original is part of the result; keep it.
//
// Behaviourally equivalent reconstruction (verified with a unicorn differential test against the
// original, work/match/scratch_s00f7d9d0_diff.py); NOT byte-exact (see nonmatching.txt).

#include "../../include/types.h"
#include <xmmintrin.h>

#define NM_ALIGN16 __declspec(align(16))

// 16-byte constants (the original's are .rdata globals at the noted addresses).
NM_ALIGN16 static const uint32_t kLow16Mask[4]   = { 0xffff, 0xffff, 0xffff, 0xffff };                  // 0x01490640
NM_ALIGN16 static const uint32_t kHigh16Mask[4]  = { 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000 };  // 0x0148ff60
NM_ALIGN16 static const uint32_t kByte0Mask[4]   = { 0xff, 0xff, 0xff, 0xff };                          // 0x0148ffe0
NM_ALIGN16 static const uint32_t kByte1Mask[4]   = { 0xff00, 0xff00, 0xff00, 0xff00 };                  // 0x0148ff80
NM_ALIGN16 static const float kOne[4]        = { 1.0f, 1.0f, 1.0f, 1.0f };                              // 0x0148fff0
NM_ALIGN16 static const float kHalf[4]       = { 0.5f, 0.5f, 0.5f, 0.5f };                              // 0x0148ffa0
NM_ALIGN16 static const float kTwoPow23[4]   = { 8388608.0f, 8388608.0f, 8388608.0f, 8388608.0f };      // 0x0148ff50
NM_ALIGN16 static const float kEpsilon[4]    = { 0.001f, 0.001f, 0.001f, 0.001f };                      // 0x0148ff90
// x * kByte0Scale + 1.0f leaves round(x * 255) in mantissa bits 0-7, kByte1Scale in bits 8-15.
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

// Low 16 bits of each lane (one packed uint16 height) as a float, via the 1.0f-or trick.
static __forceinline __m128 HeightsToFloat(__m128 raw)
{
    __m128 one = Load(kOne);
    return _mm_mul_ps(_mm_sub_ps(_mm_or_ps(_mm_and_ps(raw, Load(kLow16Mask)), one), one),
                      Load(kTwoPow23));
}

// Eight consecutive heights of one source row: columns 0-3 and 4-7.
struct HeightRow8
{
    __m128 lo;
    __m128 hi;
};

// p must be 16-byte aligned. Reads p[0..8].
static __forceinline void LoadHeights8(const uint16_t* p, HeightRow8& out)
{
    __m128 evens = HeightsToFloat(_mm_load_ps((const float*)p));        // columns 0, 2, 4, 6
    __m128 odds  = HeightsToFloat(_mm_loadu_ps((const float*)(p + 1))); // columns 1, 3, 5, 7
    __m128 t = _mm_shuffle_ps(evens, odds, 0x44);
    out.lo = _mm_shuffle_ps(t, t, 0xd8);
    t = _mm_shuffle_ps(evens, odds, 0xee);
    out.hi = _mm_shuffle_ps(t, t, 0xd8);
}

// Source rows y-1 .. y+2 of one 8-column block.
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

// (prev[3], cur[0], cur[1], cur[2])
static __forceinline __m128 ShiftInLeft(__m128 prev, __m128 cur)
{
    __m128 t = _mm_shuffle_ps(prev, cur, _MM_SHUFFLE(0, 0, 3, 3));
    return _mm_shuffle_ps(t, cur, _MM_SHUFFLE(2, 1, 2, 0));
}

// (cur[1], cur[2], cur[3], next[0])
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

// Face coordinate of a texel column/row: (n + 0.5) / 256 - 1.
static __forceinline float FaceCoord(int n)
{
    return ((float)n + 0.5f) * (1.0f / 256) - 1.0f;
}

// ((inv * n) * scale + 0.5) * byteScale + 1.0 : the channel byte in the mantissa.
static __forceinline __m128 PackChannel(const __m128& inv, const __m128& n, const __m128& scale,
                                         const float* byteScale)
{
    return _mm_add_ps(_mm_mul_ps(_mm_add_ps(_mm_mul_ps(_mm_mul_ps(inv, n), scale), Load(kHalf)),
                                 Load(byteScale)), Load(kOne));
}

// Shades 4 texels of one row and stores them as A8R8G8B8.
//   h            heights of the 4 texels (height units)
//   left, right  scaled heights (h * gradientScale) of the left/right neighbours
//   up, down     scaled heights of the texels in the rows above/below
//   u, v         face coordinates of the 4 texels
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

// One quad on both output rows (src rows 1 and 2 of the block). Advances u and v (with drift).
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

// Left edge (x0 < 4): blocks of columns 8i .. 8i+7 from column 8 * (x0 / 8).
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

// Columns 8i+4 .. 8i+11 of block i (cur = columns 8i..8i+7, next = 8i+8..8i+15).
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

// Interior (4 <= x0, x1 < 510): blocks of columns 8i+4 .. 8i+11 from i = (x0 - 4) / 8.
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

// Right edge (4 <= x0, x1 >= 510): interior blocks up to the last one, then the last 4 columns
// (8e+4 .. 8e+7, e = (x1 + 7) / 8 - 1) as a single quad whose right neighbour is read from
// column 8e+8. The quad uses the block left over from the loop (the prologue's if it ran 0 times).
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

// @ 0x00f7d9d0
// dst: 512x512 A8R8G8B8 texels; src: 16-bit heights, 512 per row, with a border row above.
// Shades columns [x0, x1) (rounded out to the block grid) of the row pairs starting at y0.
void UpdateNormalMapRegion(uint32_t* dst, const uint16_t* src, int x0, int x1, int y0, int y1,
                           float radius, float heightRange, float slopeRange,
                           float channelB, float channelG, float channelR, int axis, int, int)
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
