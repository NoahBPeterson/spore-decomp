// Slice s0116c170: rw::audio::core::HELPER_CMpegLayer3Base (MPEG-1/2 Layer III helper).
// Object file: the RW4 audio core (0x0116c170 .. 0x0116c750).
//
// 0x0116c170  interface initialiser (unlisted in the index; builds a reader interface)
// 0x0116c1a0  HELPER_CMpegLayer3Base::SToPowerOf4over3  x^(4/3) table interpolation
// 0x0116c330  HELPER_CMpegLayer3Base::HELPER_CMpegLayer3Base
// 0x0116c390  HELPER_CMpegLayer3Base::~HELPER_CMpegLayer3Base
// 0x0116c3c0  HELPER_CMpegLayer3Base::Dequantize         scalefactor dequantisation
// 0x0116c600  III_ms_stereo                               mid/side stereo (custom-register helper)
//
// Layout confirmed against the 0x0116c330 ctor and 0x0116c3c0 accesses.
// The object was built by VC .NET 2003 (cl 13.10) with /GL + /LTCG, so it is equivalence-only:
// the byte-exact rows below use the VC9 toolchain (closest codegen), while 0x0116c1a0 is
// checked with /vc71 (VC .NET 2003), the toolchain this code was actually built with.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#if _MSC_VER >= 1400
#include <intrin.h>
#endif
#include <xmmintrin.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long  ulong;

// ------------------------------------------------------------------ externals
// MPEG Layer III scale-factor band boundaries (one 60-byte entry per sampling frequency).
struct SFBandIndex {
    short l[23];      // +0x00
    u8    s[14];      // +0x2e
};
extern "C" SFBandIndex sfBandIndexLSF_14da570[3];   // 0x014da570
extern "C" char        pretabTable_14da040[];       // 0x014da040  pre-flag offsets (signed bytes)

// 8-byte entries; only the first float of each is read here.
extern "C" float       scaleValueTable_15c4620[];   // 0x015c4620 (through the pointer below)
extern "C" float*      g_pScaleValueTable_15c4620;  // 0x015c4620 holds the table pointer

extern "C" float       g_float_1485720;             // 0x01485720 = 1.0f
extern "C" float       g_float_13ef584;             // 0x013ef584 = 0.70710677f

// x^(4/3) piecewise-polynomial coefficient quads (4 floats each, stride 0x10).
extern "C" float g_coef0_14da460[4];
extern "C" float g_coef1_14da470[4];
extern "C" float g_coef2_14da480[4];
extern "C" float g_coef3_14da490[4];
extern "C" float g_coef4_14da4a0[4];
extern "C" float g_coef5_14da4b0[4];
extern "C" float g_coef6_14da4c0[4];
extern "C" float g_coef7_14da4d0[4];
extern "C" float g_coef8_14da4e0[4];

// ------------------------------------------------------------------ System
// rw::audio::core::System owns the allocator the Layer III helper frees through.
class CSystem_s0116c170 {
public:
    __declspec(nothrow) void Free(void* p, int flag);   // 0x0112c850
};
extern CSystem_s0116c170* g_pSystem_16e61a8;    // 0x016e61a8

// 0x01148da0  rw::audio::core::ScaleSamples(float* dst, float scale, int count)
extern "C" void ScaleSamples_1148da0(float* dst, float scale, int count);

// ------------------------------------------------------------------ reader interface
// 0x0116c0f0 / 0x0116bda0 are the two entry points the initialiser installs; both are
// unlisted leaves, so they are only referenced by address here.
extern "C" int  readerRead_116c0f0(int* self, int size, void* dst);   // 0x0116c0f0
extern "C" int  readerPos_116bda0(int* self);                        // 0x0116bda0

// ------------------------------------------------------------------ granule / scalefac
// III_gr_info: 0x18 bytes, the per-granule side information this code reads.
struct III_gr_info_s0116c170 {
    u8  pad00[0x07];            // +0x00
    u8  windowSwitchingFlag;    // +0x07
    u8  blockType;              // +0x08
    u8  mixedBlockFlag;         // +0x09
    u8  pad0a[6];               // +0x0a
    u8  subBlockGain[3];        // +0x10
    u8  preFlag;                // +0x13
    u32 scaleFacScale;          // +0x14
};

// III_scalefac: 0x7c bytes, the long and short scale factors of one granule.
struct III_scalefac_s0116c170 {
    short l[23];                // +0x00
    short s[3][13];             // +0x2e
};

// ------------------------------------------------------------------ the base class
// HELPER_CMpegBase is opaque here: only its size (0x48) matters, because the derived
// class stores its own members from +0x48 on.  It is polymorphic (its ctor at
// 0x01170210 stores a vftable), so the derived class keeps the single base vptr.
class HELPER_CMpegBase_s0116c170 {
public:
    HELPER_CMpegBase_s0116c170();       // 0x01170210
    ~HELPER_CMpegBase_s0116c170();      // 0x01170540
    virtual void BaseSlot();
protected:
    u8 mBaseHead[0x2c];                 // +0x04 .. +0x2f
    u8 samplingFrequency;               // +0x30   MPEG sampling-frequency index
    u8 mBaseTail[0x17];                 // +0x31 .. +0x47  (opaque base state)
};

class HELPER_CMpegLayer3Base_s0116c170 : public HELPER_CMpegBase_s0116c170 {
public:
    HELPER_CMpegLayer3Base_s0116c170();
    __declspec(nothrow) ~HELPER_CMpegLayer3Base_s0116c170();

    void SToPowerOf4over3(u32 count, short* in, float* out);    // 0x0116c1a0
    void Dequantize(int gr, int ch, float* out);                // 0x0116c3c0

    float* sToPowerOf4over3Coefficients[9];     // +0x48
    u8     pad6c[4];                            // +0x6c .. +0x6f
    III_gr_info_s0116c170 gr_info[4];           // +0x70   indexed [ch + 2 * gr]
    III_scalefac_s0116c170 scalefac[2];         // +0xd0   indexed [gr]
    float* mpPrevBlockX4;                       // +0x1c8
};

// ------------------------------------------------------------------ 0x0116c3c0
// Requantises one granule: the long blocks walk the Layer III long scale-factor bands,
// the short blocks (block_type 2, optionally mixed) walk the three short bands, and
// each band whose requantisation factor is not exactly 1.0 is scaled in place.
// @ 0x0116c3c0
void HELPER_CMpegLayer3Base_s0116c170::Dequantize(int gr, int ch, float* out)
{
    III_scalefac_s0116c170* scf = &scalefac[gr];
    III_gr_info_s0116c170*  gi  = &gr_info[ch + 2 * gr];
    short* sfbTable = (short*)&sfBandIndexLSF_14da570[samplingFrequency];

    int n;
    if (!gi->windowSwitchingFlag || gi->blockType != 2)
        n = 0x16;
    else if (!gi->mixedBlockFlag)
        n = 0;
    else
        n = (samplingFrequency < 3) ? 6 : 8;

    int i;
    for (i = 0; i < n; i++) {
        int width = sfbTable[i + 1] - sfbTable[i];
        int gain = scf->l[i];
        if (gi->preFlag)
            gain += pretabTable_14da040[i];
        float value = g_pScaleValueTable_15c4620[(gain << gi->scaleFacScale) * 2];
        if (value != g_float_1485720)
            ScaleSamples_1148da0(out + sfbTable[i], value, width);
    }

    int sfb = (n == 0x16) ? 0xd : (n != 0 ? 3 : 0);
    for (; sfb < 0xd; sfb++) {
        const u8* sb = (const u8*)sfbTable + 0x2e + sfb;
        int start = sb[0];
        int width = sb[1] - start;

        int gain0 = (scf->s[0][sfb] << gi->scaleFacScale) + gi->subBlockGain[0] * 4;
        float v0 = g_pScaleValueTable_15c4620[gain0 * 2];
        if (v0 != g_float_1485720)
            ScaleSamples_1148da0(out + start * 3, v0, width);

        int gain1 = (scf->s[1][sfb] << gi->scaleFacScale) + gi->subBlockGain[1] * 4;
        float v1 = g_pScaleValueTable_15c4620[gain1 * 2];
        if (v1 != g_float_1485720)
            ScaleSamples_1148da0(out + start * 3 + width, v1, width);

        int gain2 = (scf->s[2][sfb] << gi->scaleFacScale) + gi->subBlockGain[2] * 4;
        float v2 = g_pScaleValueTable_15c4620[gain2 * 2];
        if (v2 != g_float_1485720)
            ScaleSamples_1148da0(out + start * 3 + 2 * width, v2, width);
    }
}

// ------------------------------------------------------------------ 0x0116c170
// @ 0x0116c170
// Builds a reader interface in `out` from a source descriptor `src`: the interface
// gets the two entry points (read, tell) and inherits the source's stream fields.
void InitReaderInterface_s0116c170(int* out, int* src)
{
    out[0] = (int)&readerRead_116c0f0;
    out[7] = src[0];
    out[8] = 0;
    out[9] = src[3];
    src[9] = (int)&readerPos_116bda0;
    out[1] = 0;
}

// ------------------------------------------------------------------ 0x0116c330
// @ 0x0116c330
HELPER_CMpegLayer3Base_s0116c170::HELPER_CMpegLayer3Base_s0116c170()
{
    mpPrevBlockX4 = 0;
    sToPowerOf4over3Coefficients[0] = g_coef0_14da460;
    sToPowerOf4over3Coefficients[1] = g_coef1_14da470;
    sToPowerOf4over3Coefficients[2] = g_coef2_14da480;
    sToPowerOf4over3Coefficients[3] = g_coef3_14da490;
    sToPowerOf4over3Coefficients[4] = g_coef4_14da4a0;
    sToPowerOf4over3Coefficients[5] = g_coef5_14da4b0;
    sToPowerOf4over3Coefficients[6] = g_coef6_14da4c0;
    sToPowerOf4over3Coefficients[7] = g_coef7_14da4d0;
    sToPowerOf4over3Coefficients[8] = g_coef8_14da4e0;
}

// ------------------------------------------------------------------ 0x0116c390
// @ 0x0116c390
__declspec(nothrow) HELPER_CMpegLayer3Base_s0116c170::~HELPER_CMpegLayer3Base_s0116c170()
{
    if (mpPrevBlockX4)
        g_pSystem_16e61a8->Free(mpPrevBlockX4, 0);
}

// ------------------------------------------------------------------ 0x0116c1a0
// Table index for one sample: the original computes `13 - bsr(v)` and clamps it to 8
// (bsr's result is undefined for v == 0, where the original leaves the destination as the
// value itself, i.e. 0, so the index becomes 13 and is clamped to 8 as well).
static int STableIndex_s0116c170(int v)
{
    unsigned long lz = 0;
#if _MSC_VER >= 1400
    if (v != 0)
        _BitScanReverse(&lz, (unsigned long)v);
#else
    if (v != 0) {
        __asm {
            bsr eax, v
            mov lz, eax
        }
    }
#endif
    int idx = 0xd - (int)lz;
    return idx > 8 ? 8 : idx;
}

// Approximates x^(4/3) for an MPEG Layer III requantisation: each input sample is
// looked up in a piecewise polynomial table keyed by the log2 of its magnitude and the
// resulting degree-3 quad is evaluated for it.  The body is four-way vectorised (the
// original is 16-byte frame aligned and computes the first multiple of four samples with
// packed SSE, the remainder scalar), so the packed and scalar forms are spelled out
// separately to keep the arithmetic bit-identical to the original.
// @ 0x0116c1a0
void HELPER_CMpegLayer3Base_s0116c170::SToPowerOf4over3(u32 count, short* in, float* out)
{
    // The original keeps `count & ~3` in a register and tests it SIGNED (jle): a count whose
    // top bits are set skips the vector loop entirely instead of running billions of quads.
    int quadCount = (int)(count & ~3u);
    u32 rem = count - (u32)quadCount;          // 0..3 leftover samples (the tail loop's count)

    float* const* tbl = sToPowerOf4over3Coefficients;

    for (int i = 0; i < quadCount; i += 4) {
        float xs[4], cs[4], bs[4], ds[4], es[4];

        for (int j = 0; j < 4; j++) {
            int v = in[j];
            float* coef = tbl[STableIndex_s0116c170(v)];
            cs[j] = coef[0];
            xs[j] = (float)v;
            bs[j] = coef[1];
            ds[j] = coef[2];
            es[j] = coef[3];
        }

        __m128 x  = _mm_load_ps(xs);
        __m128 x2 = _mm_mul_ps(x, x);
        __m128 y  = _mm_add_ps(_mm_mul_ps(x, _mm_load_ps(bs)), _mm_load_ps(cs));
        __m128 z  = _mm_add_ps(_mm_mul_ps(_mm_mul_ps(x2, x), _mm_load_ps(es)),
                               _mm_mul_ps(x2, _mm_load_ps(ds)));
        _mm_store_ps(out, _mm_add_ps(y, z));

        in += 4;
        out += 4;
    }

    for (u32 k = 0; k < rem; k++) {
        int v = *in;
        const float* coef = tbl[STableIndex_s0116c170(v)];

        __m128 x  = _mm_set_ss((float)v);
        __m128 x2 = _mm_mul_ss(x, x);
        __m128 x3 = _mm_mul_ss(x2, x);
        __m128 r  = _mm_add_ss(_mm_load_ss(coef + 0),
                               _mm_mul_ss(x3, _mm_load_ss(coef + 3)));
        r = _mm_add_ss(r, _mm_mul_ss(x2, _mm_load_ss(coef + 2)));
        r = _mm_add_ss(r, _mm_mul_ss(x, _mm_load_ss(coef + 1)));
        _mm_store_ss(out, r);

        in++;
        out++;
    }
}

// ------------------------------------------------------------------ 0x0116c600
// Mid/side stereo: the granule holds both channels back to back, so every pair
// (xr[i], xr[i + 0x240]) is replaced by the normalised sum and difference.
// The original receives `xr` in EAX (a whole-program-optimised custom ABI) and selects an
// SSE path from the pointer's 16-byte alignment; both paths compute the same value.
// @ 0x0116c600
void III_ms_stereo_s0116c170(float* xr)
{
    for (int i = 0; i < 0x240; i++) {
        float l = xr[i];
        float r = xr[i + 0x240];
        xr[i] = (l + r) * g_float_13ef584;
        xr[i + 0x240] = (l - r) * g_float_13ef584;
    }
}
