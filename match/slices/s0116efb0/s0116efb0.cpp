// Slice s0116efb0 -- rw::audio::core::HELPER_Imdct36X4Implementation (0x0116efb0, 2478 bytes):
// EA RenderWare Audio, MPEG layer-3 36-point IMDCT with windowing for four interleaved subbands at once.
//
// Each float4 is one group of four subband lanes (float index 4*v is vector v). The aligned path
// (all of in/out/win on 16 bytes) runs the SIMD butterflies in place on `in`, two passes over the
// vectors (loop index i = 0,1 selects the second 4-vector block), then writes the 36 windowed output
// vectors. The unaligned path calls the scalar HELPER_Imdct36X1 once per lane (0x0116e4f0).
//
// Float constants are the 0x014daac0 table (bit-exact): 0.34729636, 1.5320889, 1.8793852, 0.70710677,
// 1.7320508, 0.6840403, 1.2855753, 1.9696155, 0.5019099, 0.5176381, 0.55168897, 0.61038727,
// 0.8717234, 1.1831008, 1.9318516, 5.7368565.
//
// Calling convention: cdecl (plain ret, 3 stack args). The scalar fallback calls
// HELPER_Imdct36X1 with win in ECX, out in EDX and `in` pushed; the caller pops (add esp,4).
// Declared __fastcall here, so the callee pops instead (ret 4): the same register/stack assignment
// with a different cleanup site, as in the s0116e4f0 slice.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <xmmintrin.h>

namespace rw { namespace audio { namespace core {
// 0x0116e4f0 (slice s0116e4f0): win in ECX, out in EDX, in on the stack.
void __fastcall HELPER_Imdct36X1(const float* win, float* out, float* in);
}}}

namespace {

// One group of four lanes (SSE register).
typedef __m128 F4;
__forceinline F4 operator+(const F4& a, const F4& b) { return _mm_add_ps(a, b); }
__forceinline F4 operator-(const F4& a, const F4& b) { return _mm_sub_ps(a, b); }
__forceinline F4 operator*(const F4& a, float c) { return _mm_mul_ps(a, _mm_set1_ps(c)); }

}  // namespace

namespace rw { namespace audio { namespace core {

// @ 0x0116efb0
void HELPER_Imdct36X4Implementation(float* param_1, float* param_2, float* param_3)
{
    if ((((unsigned int)param_1 | (unsigned int)param_2 | (unsigned int)param_3) & 0xf) == 0) {
        F4* P = (F4*)param_1;
#define V(f) P[(f) >> 2]

        // Stage 1: butterflies in place on the input vectors.
        F4 f50 = V(0x3c) + V(0x38);
        F4 f54 = V(0x34) + V(0x30);
        F4 f66 = V(0x2c) + V(0x28);
        V(0x44) = (V(0x44) + V(0x40)) + f50;
        V(0x40) = V(0x40) + V(0x3c);
        V(0x3c) = f50 + f54;
        V(0x38) = V(0x38) + V(0x34);
        V(0x34) = f54 + f66;
        V(0x30) = V(0x30) + V(0x2c);

        F4 g50 = V(0x24) + V(0x20);
        F4 g54 = V(0x1c) + V(0x18);
        F4 g55 = V(0x14) + V(0x10);
        V(0x2c) = f66 + g50;
        V(0x28) = V(0x28) + V(0x24);
        V(0x24) = g50 + g54;
        V(0x20) = V(0x20) + V(0x1c);
        V(0x1c) = g54 + g55;
        V(0x18) = V(0x18) + V(0x14);

        F4 h54 = V(0xc) + V(0x8);
        F4 h50 = V(0x4) + V(0x0);
        V(0x14) = g55 + h54;
        V(0x10) = V(0x10) + V(0xc);
        V(0xc) = h54 + h50;
        V(0x8) = V(0x8) + V(0x4);
        V(0x4) = h50;

        // Stage 2: two passes (i = 0, 1) over the block at vector i; results go to two-vector arrays.
        F4 A120[2], A100[2], A140[2], Ae0[2], Aa0[2], Ac0[2], A80[2], A60[2], A40[2];
        for (int i = 0; i < 2; ++i) {
            F4* b = P + i;
            F4 t0 = b[0] + b[0];
            F4 a56 = b[12] + t0;
            A120[i] = ((b[4] * 1.8793852f + a56) + b[8] * 1.5320889f) + b[16] * 0.34729636f;
            A40[i] = (((b[4] + t0) - b[8]) - (b[12] + b[12])) - b[16];
            A100[i] = ((b[16] * 1.5320889f + a56) - b[4] * 0.34729636f) - b[8] * 1.8793852f;
            A140[i] = ((b[8] * 0.34729636f + a56) - b[4] * 1.5320889f) - b[16] * 1.8793852f;
            F4 t5 = ((b[0] - b[4]) - b[12]) + (b[8] + b[16]);
            if (i != 0) t5 = t5 * 0.70710677f;
            Ae0[i] = t5;
            F4 t6 = b[6] * 1.7320508f;
            Aa0[i] = (b[2] * 1.9696155f + t6) + (b[10] * 1.2855753f + b[14] * 0.6840403f);
            A60[i] = ((b[2] - b[10]) - b[14]) * 1.7320508f;
            Ac0[i] = (b[2] * 1.2855753f + b[14] * 1.9696155f) - (b[10] * 0.6840403f + t6);
            A80[i] = (b[2] * 0.6840403f + b[10] * 1.9696155f) - (b[14] * 1.2855753f + t6);
        }

        // Stage 3: combine the two passes (sum/difference groups, each scaled by its cosine constant).
        F4 t18 = (A120[1] + Aa0[1]) * 0.5019099f;
        F4 s18 = A120[0] + Aa0[0];
        F4 f54b = s18 + t18;
        F4 d18 = s18 - t18;
        F4 t19 = (A40[1] + A60[1]) * 0.5176381f;
        F4 s19 = A40[0] + A60[0];
        F4 f57 = s19 + t19;
        F4 d19 = s19 - t19;
        F4 t20 = (A100[1] + Ac0[1]) * 0.55168897f;
        F4 s20 = A100[0] + Ac0[0];
        F4 f60 = s20 + t20;
        F4 d20 = s20 - t20;
        F4 t21 = (A140[1] + A80[1]) * 0.61038727f;
        F4 s21 = A140[0] + A80[0];
        F4 f63 = s21 + t21;
        F4 d21 = s21 - t21;
        F4 t22 = (A140[1] - A80[1]) * 0.8717234f;
        F4 s22 = A140[0] - A80[0];
        F4 f55 = s22 + t22;
        F4 d22 = s22 - t22;
        F4 t23 = (A100[1] - Ac0[1]) * 1.1831008f;
        F4 s23 = A100[0] - Ac0[0];
        F4 f58 = s23 + t23;
        F4 d23 = s23 - t23;
        F4 t24 = (A40[1] - A60[1]) * 1.9318516f;
        F4 s24 = A40[0] - A60[0];
        F4 f61 = s24 + t24;
        F4 d24 = s24 - t24;
        F4 t25 = (A120[1] - Aa0[1]) * 5.7368565f;
        F4 s25 = A120[0] - Aa0[0];
        F4 f64 = s25 + t25;
        F4 d25 = s25 - t25;
        F4 e4 = Ae0[0] - Ae0[1];
        F4 e8 = Ae0[0] + Ae0[1];

        // Stage 4: window each output vector by its scalar window value (broadcast).
        F4* O = (F4*)param_2;
        O[0] = d25 * param_3[0];
        O[1] = d24 * param_3[1];
        O[2] = d23 * param_3[2];
        O[3] = d22 * param_3[3];
        O[4] = e4 * param_3[4];
        O[5] = d21 * param_3[5];
        O[6] = d20 * param_3[6];
        O[7] = d19 * param_3[7];
        O[8] = d18 * param_3[8];
        O[9] = d18 * param_3[9];
        O[10] = d19 * param_3[10];
        O[11] = d20 * param_3[11];
        O[12] = d21 * param_3[12];
        O[13] = e4 * param_3[13];
        O[14] = d22 * param_3[14];
        O[15] = d23 * param_3[15];
        O[16] = d24 * param_3[16];
        O[17] = d25 * param_3[17];
        O[18] = f64 * param_3[18];
        O[19] = f61 * param_3[19];
        O[20] = f58 * param_3[20];
        O[21] = f55 * param_3[21];
        O[22] = e8 * param_3[22];
        O[23] = f63 * param_3[23];
        O[24] = f60 * param_3[24];
        O[25] = f57 * param_3[25];
        O[26] = f54b * param_3[26];
        O[27] = f54b * param_3[27];
        O[28] = f57 * param_3[28];
        O[29] = f60 * param_3[29];
        O[30] = f63 * param_3[30];
        O[31] = e8 * param_3[31];
        O[32] = f55 * param_3[32];
        O[33] = f58 * param_3[33];
        O[34] = f61 * param_3[34];
        O[35] = f64 * param_3[35];
#undef V
        return;
    }

    // Unaligned: one scalar 36-point IMDCT per lane.
    for (int k = 0; k < 4; ++k)
        HELPER_Imdct36X1(param_3, param_2 + k, param_1 + k);
}

}}}  // namespace rw::audio::core

// ---------------------------------------------------------------------------------------------
// 0x0116f960 / 0x0116fc20 / 0x0116fdc0 -- the layer-3 hybrid stage around the IMDCT helpers.
// All three are LTCG-register-ABI code from the same TU as the IMDCT helpers: the calls into
// HELPER_Imdct36X1 (win=ECX, out=EDX, in=stack) and HELPER_Imdct12X1 (out=EAX, in=stack) use
// per-function register conventions, so the 12-point helper is transcribed locally instead of
// being declared (see the s01145d10 slice, same algorithm on the other decoder class).
// ---------------------------------------------------------------------------------------------
#include <mmintrin.h>
#include <malloc.h>     // _alloca

// 0x014da860: 36-point window table used by this decoder object (block type selects +0x90 each).
extern "C" const float g_imdct36WinHybrid[];      // 0x014da860 IMDCT36 windows (hybrid stage)

namespace rw { namespace audio { namespace core {

class System {
public:
    void* Alloc(int size, const char* name, int align, int flags);  // 0x0112c820
};

extern System* g_audioSystem;                    // 0x016e61a8
void* AudioMemset(void* dst, int c, unsigned n); // 0x011e073e memset
void HELPER_Imdct12X4(float* in, float* out);    // 0x011464a0
void HELPER_Imdct36X4Implementation(float* in, float* out, const float* tbl); // 0x0116efb0

// HELPER_Imdct36X1 is caller-cleanup in the original (plain ret), but the __fastcall declaration
// that reproduces its ECX/EDX register assignment makes our compiler assume a callee-pop of the
// pushed third argument. Route the call through a dynamic-frame wrapper: its epilogue restores ESP
// from EBP, so the two leaked stack words cannot shift the aligned scratch frame over the saved
// registers in Hybrid.
static void CallImdct36X1(const float* win, float* out, float* in)
{
    _alloca(4);
    HELPER_Imdct36X1(win, out, in);
}

// !!! 0x0116f960: overlap-add of four interleaved lanes.
// out[i] = tmp[i] + hist[i] and hist[i] = tmp[72 + i] for the 72 samples of the block.
// The aligned path copies 8 floats per iteration with SSE, the fallback walks the four lanes
// vertically (one float every four), which is why the element stride below is 4.
// @ 0x0116f960
void HELPER_OverlapAddX4(float* out, float* tmp, float* hist)
{
    if ((((unsigned int)out | (unsigned int)tmp | (unsigned int)hist) & 0xf) == 0) {
        F4* o = (F4*)out;
        F4* s = (F4*)tmp;
        F4* h = (F4*)hist;
        for (int i = 0; i < 9; ++i) {
            F4 h0 = h[0];
            F4 h1 = h[1];
            F4 s0 = s[0];
            F4 s1 = s[1];
            o[0] = h0 + s0;
            o[1] = h1 + s1;
            h += 2;
            s += 2;
            o += 2;
        }
        h = (F4*)hist;
        for (int i = 0; i < 9; ++i) {
            F4 s0 = s[0];
            F4 s1 = s[1];
            h[0] = s0;
            h[1] = s1;
            h += 2;
            s += 2;
        }
        return;
    }
    for (int k = 0; k < 4; ++k) {
        for (int n = 0; n < 18; ++n)
            out[n * 4 + k] = hist[n * 4 + k] + tmp[n * 4 + k];
        for (int n = 0; n < 18; ++n)
            hist[n * 4 + k] = tmp[72 + n * 4 + k];
    }
}

// Local bit-faithful transcription of HELPER_Imdct12X1 (0x011661b0): `out` arrives in EAX, which
// has no C spelling. Zero this lane's 36 slots (stride 4) then run the three short-block
// butterflies, accumulating into the same slots.
void Imdct12X1Local(float* in, float* out)
{
    for (int k = 0; k < 36; k++)
        out[4 * k] = 0.0f;
    for (int w = 0; w < 3; w++) {
        float* p = in + 4 * w;
        float A = p[0x00];
        float B = p[0x0c];
        float C = p[0x18];
        float D = p[0x24];
        float E = p[0x30];
        float F = p[0x3c];
        p[0x0c] = A + B;
        p[0x18] = C + B;
        p[0x3c] = E + F;
        p[0x30] = E + D;
        p[0x24] = (A + B) + (C + D);
        float u5 = (C + D) + (E + F);
        p[0x3c] = u5;

        float v26 = (E + D) * 0.5f + A;
        float v14 = (C + B) * 0.8660254f;
        float t33 = v26 - v14;
        float t34 = v26 + v14;
        float W   = u5 * 0.5f + (A + B);
        float vX  = ((A + B) - u5) * 0.70710677f;
        float t44 = ((A + B) + (C + D)) * 0.8660254f;
        float t46 = W - t44;
        float t47 = W + t44;
        float t48 = t46 * 1.9318516f;
        float t49 = t47 * 0.5176381f;
        float t53 = t34 - t49;
        float t58 = (t49 + t34) * 0.50431448f;
        float t56 = t53 * 3.8306489f;
        float t61 = (vX + (A - (E + D))) * 0.54119611f;
        float t64 = ((A - (E + D)) - vX) * 1.306563f;
        float t68 = (t48 + t33) * 0.63023621f;
        float t81 = (t33 - t48) * 0.82133979f;
        float* o = out + 0x18 + 0x18 * w;
        o[0x00] += t81 * 0.13052619f;
        o[0x04] += t64 * 0.38268343f;
        o[0x08] += t56 * 0.60876143f;
        o[0x0c] += t56 * -0.79335332f;
        o[0x10] += t64 * -0.92387950f;
        o[0x14] += t81 * -0.99144489f;
        o[0x18] += t68 * -0.99144489f;
        o[0x1c] += t61 * -0.92387950f;
        o[0x20] += t58 * -0.79335332f;
        o[0x24] += t58 * -0.60876143f;
        o[0x28] += t61 * -0.38268343f;
        o[0x2c] += t68 * -0.13052619f;
    }
}

// Granule side-info record, PDB GranuleInfo layout (0x18 bytes) as recovered in s01145d10.
struct GranuleInfo {                            // size 0x18
    uint16_t part2And3Length;                   // +0x00
    uint16_t bigValues;                         // +0x02
    uint16_t scaleFacCompress;                  // +0x04
    uint8_t  globalGain;                        // +0x06
    uint8_t  windowSwitchingFlag;               // +0x07
    uint8_t  blockType;                         // +0x08
    uint8_t  mixedBlockFlag;                    // +0x09
    uint8_t  region0Count;                      // +0x0a
    uint8_t  region1Count;                      // +0x0b
    uint8_t  tableSelect[3];                    // +0x0c
    uint8_t  count1TableSelect;                 // +0x0f
    uint8_t  subBlockGain[3];                   // +0x10
    uint8_t  preFlag;                           // +0x13
    uint32_t scaleFacScale;                     // +0x14
};

// Reconstructed layout of this caller's decoder object (no PDB class name survived; only the
// members the hybrid stage touches are named). Distinct from CMpegLayer3Base: granules at +0x70
// and the hybrid history at +0x1c8 instead of +0x154/+0x2c0.
struct cMpegHybridDecoder {
    uint8_t     pad00[0x3c];                    // +0x000
    uint8_t     mChannels;                      // +0x03c  hybrid planes allocated
    uint8_t     pad3d[0x70 - 0x3d];             // +0x03d
    GranuleInfo mGranules[4];                   // +0x070  [2*granule + channel]
    uint8_t     padD0[0x1c8 - 0xd0];            // +0x0d0
    float*      mpHybridHistory;                // +0x1c8  one 0x900-byte plane per granule

    void Hybrid(int gr, int ch, float* buf);    // 0x0116fc20
};

// !!! 0x0116fc20: hybrid synthesis for one granule/channel.
// Lazily allocates the per-granule history planes, runs the mixed-block IMDCT quartet when the
// granule has both window switching and a mixed block, then fills the remaining eight short
// blocks (block type 2) or long blocks and overlap-adds each into the history plane.
// @ 0x0116fc20
void cMpegHybridDecoder::Hybrid(int gr, int ch, float* buf)
{
    __declspec(align(16)) float tmp[0x240 / 4];

    if (mpHybridHistory == 0) {
        mpHybridHistory = (float*)g_audioSystem->Alloc(mChannels * 0x900, "MP3HybridHistory", 0x10, 0);
        if (mpHybridHistory == 0) {
            // The original stores a zero dword here (the Alloc result was already 0 in EAX);
            // an integer store keeps the same bytes without touching XMM.
            *(unsigned int*)buf = 0;
            return;
        }
        AudioMemset(mpHybridHistory, 0, mChannels * 0x900);
    }
    GranuleInfo* gi = &mGranules[gr * 2 + ch];
    float* hist = (float*)((uint8_t*)mpHybridHistory + gr * 0x900);
    int flag = 0;
    if (gi->windowSwitchingFlag && gi->mixedBlockFlag) {
        uint8_t* t = (uint8_t*)tmp;
        uint8_t* in = (uint8_t*)buf;
        CallImdct36X1(g_imdct36WinHybrid, (float*)(t + 0), (float*)(in + 0));
        CallImdct36X1(g_imdct36WinHybrid, (float*)(t + 4), (float*)(in + 4));
        Imdct12X1Local((float*)(in + 8), (float*)(t + 8));
        Imdct12X1Local((float*)(in + 0xc), (float*)(t + 0xc));
        HELPER_OverlapAddX4(buf, tmp, hist);
        flag = 1;
    }
    if (gi->blockType == 2) {
        for (; flag < 8; flag++) {
            float* p = buf + flag * 0x48;       // 0x120 bytes of four interleaved lanes
            HELPER_Imdct12X4(p, tmp);
            HELPER_OverlapAddX4(p, tmp, hist + flag * 0x48);
        }
    } else {
        const float* tbl = (const float*)((const uint8_t*)g_imdct36WinHybrid + gi->blockType * 0x90);
        for (; flag < 8; flag++) {
            float* p = buf + flag * 0x48;
            HELPER_Imdct36X4Implementation(p, tmp, tbl);
            HELPER_OverlapAddX4(p, tmp, hist + flag * 0x48);
        }
    }
}

// !!! 0x0116fdc0: requantise the 8 interleaved hybrid planes into 16-bit samples.
// 18 blocks of four samples per plane; each plane is 0x120 bytes apart, the destination advances
// one 32-word group per block. Values are scaled by 16384 and saturated by packssdw; the stores
// are streaming (movntq) and the MMX state is cleared at the end.
// @ 0x0116fdc0
void FUN_0116fdc0(const float* src, int16_t* dst)
{
    const __m128 scale = _mm_set1_ps(16384.0f);
    const float* s = src;
    int16_t* d = dst;
    for (int i = 0; i < 18; i++) {
        // The original unrolls the eight planes in four two-plane blocks (the pair shares the
        // multiply/conversion pipeline before the two streaming stores).
#define HYBRID_PAIR(g)                                                          \
        {                                                                       \
            const float* q = s + (g) * 0x48;                                    \
            __m128 x0 = _mm_loadl_pi(_mm_setzero_ps(), (const __m64*)(q + 0));  \
            __m128 x1 = _mm_loadl_pi(_mm_setzero_ps(), (const __m64*)(q + 2));  \
            __m128 y0 = _mm_loadl_pi(_mm_setzero_ps(), (const __m64*)(q + 0x48)); \
            __m128 y1 = _mm_loadl_pi(_mm_setzero_ps(), (const __m64*)(q + 0x4a)); \
            __m64 m0 = _mm_packs_pi32(_mm_cvtps_pi32(_mm_mul_ps(x0, scale)),    \
                                      _mm_cvtps_pi32(_mm_mul_ps(x1, scale)));   \
            __m64 m1 = _mm_packs_pi32(_mm_cvtps_pi32(_mm_mul_ps(y0, scale)),    \
                                      _mm_cvtps_pi32(_mm_mul_ps(y1, scale)));   \
            _mm_stream_pi((__m64*)(d + (g) * 4), m0);                           \
            _mm_stream_pi((__m64*)(d + (g) * 4 + 4), m1);                       \
        }
        HYBRID_PAIR(0);
        HYBRID_PAIR(2);
        HYBRID_PAIR(4);
        HYBRID_PAIR(6);
#undef HYBRID_PAIR
        s += 4;
        d += 32;
    }
    _mm_empty();
    // The original's loop counter is the *destination* end pointer and it is still in EAX at the
    // epilogue; a volatile keep-read reproduces that hidden void return value.
    int16_t* volatile done = d;
    (void)done;
}

}}}  // namespace rw::audio::core
