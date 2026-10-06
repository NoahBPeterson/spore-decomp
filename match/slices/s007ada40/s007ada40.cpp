// Slice s007ada40 — DXT block mapping, endpoint refinement and small surface
// descriptor helpers (0x7ada40..0x7ae9f0).
// Optimized region: /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <intrin.h>
#include <xmmintrin.h>

// ---------------------------------------------------------------------------
// @ 0x007ae920
// Initialise a scanline descriptor from a starting point and two extents.
class Span {
public:
    void Init(int x, int y, int dx, int dy, int extra);
    int mX;         // +0x00
    int mY;         // +0x04
    int mXEnd;      // +0x08
    int mYEnd;      // +0x0c
    int mExtra;     // +0x10
    int mM1;        // +0x14
    int mM2;        // +0x18
    uint8_t mFlag;  // +0x1c
};

void Span::Init(int x, int y, int dx, int dy, int extra)
{
    int* p = (int*)this;
    p[0] = x;
    p[2] = x + dx;
    p[1] = y;
    p[3] = y + dy;
    p[4] = extra;
    p[5] = -1;
    p[6] = -1;
    ((uint8_t*)this)[0x1c] = 0;
}

// ---------------------------------------------------------------------------
// @ 0x007ae960
class InnerData {
public:
    char    mPad00[0x1c];
    uint8_t mFlag;      // +0x1c
};
class FlagHolder {
public:
    uint8_t IsSet();
    InnerData* mpData;  // +0x00
};

uint8_t FlagHolder::IsSet()
{
    return mpData->mFlag;
}

// ---------------------------------------------------------------------------
// @ 0x007ae9f0 / 0x007ae980
class DxtBase1 { public: virtual void v1(); virtual ~DxtBase1() {} };
class DxtBase2 { public: virtual void v2(); virtual ~DxtBase2() {} };
class DxtRefCount {
public:
    long mCount;
    DxtRefCount() { _InterlockedExchange((volatile long*)&mCount, 0); }
};
struct IRel1 { virtual void v0(); virtual void Release(); };            // Release at slot 1 (+4)
struct IRel2 { virtual void v0(); virtual void v1(); virtual void Release(); };  // Release at slot 2 (+8)
template<class T> struct RelPtr {
    T* mp;
    RelPtr() {}
    RelPtr(int) : mp(0) {}
    ~RelPtr() { if (mp) mp->Release(); }
};
class DxtSurface : public DxtBase1, public DxtBase2, public DxtRefCount {
public:
    RelPtr<IRel1> mC;   // +0x0c
    int m10;            // +0x10
    RelPtr<IRel2> m14;  // +0x14
    int m18;            // +0x18
    int m1c;            // +0x1c
    int m20;            // +0x20
    int m24;            // +0x24
    DxtSurface();
};

DxtSurface::DxtSurface() : mC(0), m10(0), m24(0)
{
}

// @ 0x007ae980 SP::cDXTBlock::~cDXTBlock (compiler-generated: two member releases, base vptr resets)
#pragma auto_inline(off)
void DestroyDxtSurface(DxtSurface* p)
{
    p->~DxtSurface();
}
#pragma auto_inline(on)

// ---------------------------------------------------------------------------
// Shared helpers.
// 565 -> 0xFFrrggbb expansion with bit replication.
static inline uint32_t Expand565(uint32_t c)
{
    uint32_t r = ((c >> 11) << 3) & 0xff;
    r |= (c >> 13) & 7;
    uint32_t g = ((c >> 5) << 2) & 0xff;
    uint32_t g2 = (c >> 9) & 3;
    uint32_t b = (c << 3) & 0xff;
    uint32_t b2 = (c >> 2) & 7;
    uint32_t v = (0xffffff00u | r) << 8;
    v |= g2;
    v |= g;
    v <<= 8;
    v |= b2;
    v |= b;
    return v;
}

// Build the four-entry palette used by the block mappers. c0, c1 are the expanded endpoints.
static inline void BuildPalette(uint32_t* pal, uint32_t c0, uint32_t c1, uint32_t raw0, uint32_t raw1)
{
    pal[0] = c0;
    pal[1] = c1;
    if (raw0 > raw1) {
        uint32_t r0 = (c0 >> 16) & 0xff, g0 = (c0 >> 8) & 0xff, b0 = c0 & 0xff;
        uint32_t r1 = (c1 >> 16) & 0xff, g1 = (c1 >> 8) & 0xff, b1 = c1 & 0xff;
        uint32_t t = (0xffffff00u | ((r1 + r0 * 2) / 3)) << 8;
        t |= ((g1 + g0 * 2) / 3) & 0xff;
        t <<= 8;
        t |= ((b1 + b0 * 2) / 3) & 0xff;
        pal[2] = t;
        uint32_t u = (0xffffff00u | ((r0 + r1 * 2) / 3)) << 8;
        u |= ((g0 + g1 * 2) / 3) & 0xff;
        u <<= 8;
        u |= ((b0 + b1 * 2) / 3) & 0xff;
        pal[3] = u;
    } else {
        pal[2] = ((((c1 & 0xfefefe) + (c0 & 0xfefefe)) >> 1) + (c1 & c0 & 0x10101)) | 0xff000000u;
        pal[3] = 0;
    }
}

// Pixel mappers (callees outside this slice).
void mappixeltransparent(uint32_t pix, int* idx, const uint32_t* pal);   // @ 0x007ad400
void __fastcall mappixel(uint32_t pix, const uint32_t* pal, int* idx);    // @ 0x007ad2e0 (pal in eax in the original)
uint32_t rbmappixel(uint32_t pix, const uint32_t* pal);                  // @ 0x007ad760 (pal in esi, pix in edx)
uint32_t trymapblockfast(const uint32_t* px, uint32_t c0, uint32_t c1, uint32_t limit);  // @ 0x007ad950

// ---------------------------------------------------------------------------
// @ 0x007ada40
// Map a 4x4 source block to a DXT1 block: writes the two 565 endpoints and 4 index bytes.
void mapblock(const uint32_t* src, uint8_t* dst, uint32_t c0, uint32_t c1, int mode)
{
    uint32_t pal[4];
    pal[0] = Expand565(c0);
    pal[1] = Expand565(c1);
    dst[0] = (uint8_t)c0;
    dst[2] = (uint8_t)c1;
    dst[1] = (uint8_t)(c0 >> 8);
    dst[3] = (uint8_t)(c1 >> 8);
    if (mode == 0) {
        BuildPalette(pal, pal[0], pal[1], c0, c1);
        for (int row = 0; row < 4; row++) {
            int bits = 0;
            for (int k = 0; k < 8; k += 2) {
                int idx = 0;
                mappixeltransparent(*src, &idx, pal);
                bits |= idx << k;
                src++;
            }
            dst[4 + row] = (uint8_t)bits;
        }
    } else {
        for (int row = 0; row < 4; row++) {
            int bits = 0;
            for (int k = 0; k < 8; k += 2) {
                int idx = 0;
                mappixel(*src, pal, &idx);
                bits |= idx << k;
                src++;
            }
            dst[4 + row] = (uint8_t)bits;
        }
    }
}

// @ 0x007adcf0
// MMX nearest-endpoint mapper: endpoints given as 888, writes two 565 words and a 32-bit index word.
static const unsigned __int64 kMaskRGB = 0x0000000000ffffffULL;    // 0x140fbd0
static const unsigned __int64 kThird = 0x5555555555555555ULL;      // 0x140fbc8
void FUN_007adcf0(const uint32_t* src, uint8_t* dst, uint32_t cB, uint32_t cA)
{
    uint32_t a565 = ((cA >> 8) & 0xf800) | ((cA >> 5) & 0x7e0) | ((cA >> 3) & 0x1f);
    uint32_t b565 = ((cB >> 8) & 0xf800) | ((cB >> 5) & 0x7e0) | ((cB >> 3) & 0x1f);
    *(uint16_t*)(dst + 0) = (uint16_t)a565;
    *(uint16_t*)(dst + 2) = (uint16_t)b565;
    if ((uint16_t)a565 <= (uint16_t)b565) {
        *(uint32_t*)(dst + 4) = 0;
        return;
    }
    __m64 mask = *(const __m64*)&kMaskRGB;
    __m64 m0 = _mm_and_si64(_mm_cvtsi32_si64((int)cA), mask);
    __m64 m1 = _mm_and_si64(_mm_cvtsi32_si64((int)cB), mask);
    __m64 zero = _mm_setzero_si64();
    m0 = _mm_unpacklo_pi8(m0, zero);
    m1 = _mm_unpacklo_pi8(m1, zero);
    __m64 m2 = _mm_shuffle_pi16(m0, 0xe4);
    __m64 m3 = _mm_shuffle_pi16(m1, 0xe4);
    m2 = _mm_add_pi16(m2, m0);
    m3 = _mm_add_pi16(m3, m0);
    m2 = _mm_add_pi16(m2, m1);
    m3 = _mm_add_pi16(m3, m1);
    __m64 third = *(const __m64*)&kThird;
    m2 = _mm_mulhi_pi16(m2, third);
    m3 = _mm_mulhi_pi16(m3, third);
    uint32_t result = 0;
    for (int off = 0x3c; off >= 0; off -= 4) {
        __m64 p = _mm_unpacklo_pi8(_mm_and_si64(_mm_cvtsi32_si64(*(const int*)((const uint8_t*)src + off)), mask), zero);
        __m64 d0 = _mm_madd_pi16(_mm_sub_pi16(p, m0), _mm_sub_pi16(p, m0));
        __m64 d1 = _mm_madd_pi16(_mm_sub_pi16(p, m1), _mm_sub_pi16(p, m1));
        uint32_t best = (((uint32_t)_mm_cvtsi64_si32(d0) + (uint32_t)_mm_cvtsi64_si32(_mm_unpackhi_pi32(d0, d0))) * 4);
        uint32_t e1 = (((uint32_t)_mm_cvtsi64_si32(d1) + (uint32_t)_mm_cvtsi64_si32(_mm_unpackhi_pi32(d1, d1))) * 4) | 1;
        if (e1 < best) best = e1;
        __m64 d2 = _mm_madd_pi16(_mm_sub_pi16(p, m2), _mm_sub_pi16(p, m2));
        uint32_t e2 = (((uint32_t)_mm_cvtsi64_si32(d2) + (uint32_t)_mm_cvtsi64_si32(_mm_unpackhi_pi32(d2, d2))) * 4) | 2;
        if (e2 < best) best = e2;
        __m64 d3 = _mm_madd_pi16(_mm_sub_pi16(p, m3), _mm_sub_pi16(p, m3));
        uint32_t e3 = (((uint32_t)_mm_cvtsi64_si32(d3) + (uint32_t)_mm_cvtsi64_si32(_mm_unpackhi_pi32(d3, d3))) * 4) | 3;
        if (e3 < best) best = e3;
        result = (result << 2) | (best & 3);
    }
    *(uint32_t*)(dst + 4) = result;
}

// @ 0x007ade70
// Error of mapping a block's 16 byte-channel samples (byte +2 of each pixel) to the DXT1 palette.
uint32_t rtrymapblock(const uint32_t* src, uint32_t raw0, uint32_t raw1)
{
    uint32_t pal[4];
    pal[0] = Expand565(raw0);
    pal[1] = Expand565(raw1);
    BuildPalette(pal, pal[0], pal[1], raw0, raw1);
    uint32_t p0 = pal[0] & 0xff, p1 = pal[1] & 0xff, p2 = pal[2] & 0xff, p3 = pal[3] & 0xff;
    uint32_t total = 0;
    const uint8_t* p = (const uint8_t*)src + 2;
    for (int i = 0; i < 16; i++) {
        int v = p[0];
        uint32_t best = 0x7fffffff;
        uint32_t e;
        e = (uint32_t)((v - (int)p0) * (v - (int)p0)); if (e < best) best = e;
        e = (uint32_t)((v - (int)p1) * (v - (int)p1)); if (e < best) best = e;
        e = (uint32_t)((v - (int)p2) * (v - (int)p2)); if (e < best) best = e;
        e = (uint32_t)((v - (int)p3) * (v - (int)p3)); if (e < best) best = e;
        total += best;
        p += 4;
    }
    return total;
}

// @ 0x007ae0b0
// Same palette as rtrymapblock, error summed through the per-pixel mapper.
uint32_t rbtrymapblock(const uint32_t* src, uint32_t raw0, uint32_t raw1)
{
    uint32_t pal[4];
    pal[0] = Expand565(raw0);
    pal[1] = Expand565(raw1);
    BuildPalette(pal, pal[0], pal[1], raw0, raw1);
    uint32_t total = 0;
    for (int i = 0; i < 16; i++)
        total += rbmappixel(src[i], pal);
    return total;
}

// @ 0x007ae2a0
// Refine the endpoints in out[0..1] by trying quantised candidate colours from five sample pixels.
uint32_t RefineMinMaxColors(const uint32_t* px, uint32_t* out)
{
    uint32_t q[5];
    static const int kSample[5] = { 0, 2, 5, 11, 13 };
    for (int i = 0; i < 5; i++) {
        uint32_t v = px[kSample[i]];
        uint32_t c565 = ((((v >> 3) & 0x1f0000) | (v & 0xfc00)) >> 2 | (v & 0xf8)) >> 3;
        uint32_t base = ((((c565 >> 11) << 3) & 0xff) << 8 | (((c565 >> 5) << 2) & 0xff)) << 8 | ((c565 << 3) & 0xff);
        base &= 0xffffff;
        uint32_t rep = (((((c565 >> 13) & 7) << 8) | ((c565 >> 9) & 3)) << 8) | ((c565 >> 2) & 7);
        q[i] = base | rep;
    }
    uint32_t best = trymapblockfast(px, out[0] & 0xffffff, out[1] & 0xffffff, 0x7fffffff);
    if (best > 8) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                uint32_t c0 = q[i], c1 = q[j];
                if (c0 < c1) {
                    uint32_t e = trymapblockfast(px, c0, c1, best);
                    if (e < best) {
                        best = e;
                        out[0] = c0;
                        out[1] = c1;
                        if (best <= 8) return best;
                    }
                }
            }
        }
    }
    return best;
}

// @ 0x007ae5b0
// Interleave two nibbles of four alpha rows into an 8-byte DXT3 block (src row stride in bytes).
void FUN_007ae5b0(const uint8_t* src, uint8_t* dst, int stride)
{
    const uint8_t* p = src;
    for (int i = 0; i < 4; i++) {
        dst[i * 2] = (p[7] & 0xf0) | (p[3] >> 4);
        dst[i * 2 + 1] = (p[0xf] & 0xf0) | (p[0xb] >> 4);
        p += stride;
    }
}

// @ 0x007ae660
// DXT5 interpolated alpha block: endpoints hi/lo, 16 3-bit indices from the alpha byte of each pixel.
extern const uint32_t g_alphaIndexTable[8];   // 0x153bcec
void InterpolatedAlphaBlock(int hi, int lo, const uint8_t* src, uint8_t* dst)
{
    dst[0] = (uint8_t)hi;
    dst[1] = (uint8_t)lo;
    if (hi - lo == 0) {
        *(uint32_t*)(dst + 2) = 0;
        *(uint16_t*)(dst + 6) = 0;
        return;
    }
    uint32_t scale = 0x7ffffffu / (uint32_t)(hi - lo);
    uint32_t rows[4];
    for (int r = 0; r < 4; r++) {
        uint32_t v = 0;
        for (int c = 3; c >= 0; c--) {
            uint32_t a = src[r * 16 + c * 4 + 3];
            uint32_t t = g_alphaIndexTable[((a - (uint32_t)lo) * scale) >> 24];
            v = (v << 3) | t;
        }
        rows[r] = v;
    }
    uint32_t lo24 = rows[0] | (rows[1] << 12);
    dst[2] = (uint8_t)lo24;
    dst[3] = (uint8_t)(lo24 >> 8);
    dst[4] = (uint8_t)(lo24 >> 16);
    uint32_t hi24 = rows[2] | (rows[3] << 12);
    dst[5] = (uint8_t)hi24;
    dst[6] = (uint8_t)(hi24 >> 8);
    dst[7] = (uint8_t)(hi24 >> 16);
}

// @ 0x007ae840
// Copy a 4x4 byte block (stride in bytes, 16 bytes per row copied) to a 64-byte buffer and
// reduce it to per-channel min and max, written as two dwords.
void FUN_007ae840(const uint8_t* src, int stride, __m64* copy, uint32_t* out)
{
    const uint8_t* p = src;
    __m64 r0 = *(const __m64*)p;
    __m64 r1 = *(const __m64*)(p + 8);
    p += stride;
    __m64 r2 = *(const __m64*)p;
    __m64 r3 = *(const __m64*)(p + 8);
    p += stride;
    __m64 r4 = *(const __m64*)p;
    __m64 r5 = *(const __m64*)(p + 8);
    __m64 r6 = *(const __m64*)(p + stride);
    __m64 r7 = *(const __m64*)(p + stride + 8);
    copy[0] = r0; copy[1] = r1; copy[2] = r2; copy[3] = r3;
    copy[4] = r4; copy[5] = r5; copy[6] = r6; copy[7] = r7;
    __m64 mn = _mm_min_pu8(r0, r1);
    __m64 mx = _mm_max_pu8(r1, copy[0]);
    mn = _mm_min_pu8(mn, r2); mx = _mm_max_pu8(mx, r2);
    mn = _mm_min_pu8(mn, r3); mx = _mm_max_pu8(mx, r3);
    mn = _mm_min_pu8(mn, r4); mx = _mm_max_pu8(mx, r4);
    mn = _mm_min_pu8(mn, r5); mx = _mm_max_pu8(mx, r5);
    mn = _mm_min_pu8(mn, r6); mx = _mm_max_pu8(mx, r6);
    mn = _mm_min_pu8(mn, r7); mx = _mm_max_pu8(mx, r7);
    __m64 mn2 = _mm_srli_si64(mn, 32);
    __m64 mx2 = _mm_srli_si64(mx, 32);
    mn = _mm_min_pu8(mn, mn2);
    mx = _mm_max_pu8(mx, mx2);
    out[0] = (uint32_t)_mm_cvtsi64_si32(mn);
    out[1] = (uint32_t)_mm_cvtsi64_si32(mx);
}
