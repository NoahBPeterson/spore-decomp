// Slices of lib_b5rw / On2 VP6 decoder setup, SporeApp.exe
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include <string.h>
#include <stdlib.h>
#include <crtdefs.h>
#undef _CRT_ALIGN
#define _CRT_ALIGN(x)
#include <intrin.h>
#include <mmintrin.h>
#include <xmmintrin.h>

// ---------------------------------------------------------------------------
// Table selection entry.
//
// 0x16d9584  vp6_filter_row
// 0x16d9588  vp6_filter[0x41]      (per-MV-row selection table)
// 0x16d9418  vp6_idct_...
// 0x16d941c  vp6_...
// 0x16d968c  vp6_...
// 0x16d9690  vp6_...
// 0x16d9580  vp6_...
// ---------------------------------------------------------------------------
extern "C" {
void* p_vp6_filter_row_;
void* p_vp6_filter_[0x41];
void* p_vp6_a_;
void* p_vp6_b_;
void* p_vp6_c_;
void* p_vp6_d_;
void* p_vp6_e_;
}

typedef void* (*vp6_fn)(void);

void FUN_00fd1ba0(int* a, void* b, int* c);

// @ 0x00fd1c60
void vp6_setup_tables(void)
{
    int hasSSE2 = 0;
    int hasMMX = 0;
    int has3DNow = 0;
    FUN_00fd1ba0(&hasMMX, &has3DNow, &hasSSE2);

    int i;
    if (hasSSE2 != 0) {
        for (i = 0; i < 0x41; i++) {
            if (i < 2)
                p_vp6_filter_[i] = (void*)0x00fd2870;
            else if (i < 0xb)
                p_vp6_filter_[i] = (void*)0x00fd2470;
            else
                p_vp6_filter_[i] = (void*)0x00fd1f70;
        }
        p_vp6_e_   = (void*)0x00fd28e0;
        p_vp6_a_   = (void*)0x00fd2920;
        p_vp6_b_   = (void*)0x00fd1e00;
        p_vp6_c_   = (void*)0x00fd1e10;
        p_vp6_d_   = (void*)0x00fd1e50;
        p_vp6_filter_row_ = (void*)0x00fd0d20;
        return;
    }
    if (hasMMX != 0) {
        for (i = 0; i < 0x41; i++) {
            if (i < 2)
                p_vp6_filter_[i] = (void*)0x00fd0eb0;
            else if (i < 0xb)
                p_vp6_filter_[i] = (void*)0x00fd1610;
            else
                p_vp6_filter_[i] = (void*)0x00fd0f10;
        }
        p_vp6_e_   = (void*)0x00fd1a20;
        p_vp6_a_   = (void*)0x00fd1a60;
        p_vp6_b_   = (void*)0x00fd1e00;
        p_vp6_c_   = (void*)0x00fd1e10;
        p_vp6_d_   = (void*)0x00fd1e50;
        p_vp6_filter_row_ = (void*)0x00fd0830;
        return;
    }
    for (i = 0; i < 0x41; i++) {
        if (i < 2)
            p_vp6_filter_[i] = (void*)0x00fd5d50;
        else if (i < 0xb)
            p_vp6_filter_[i] = (void*)0x00fd5770;
        else
            p_vp6_filter_[i] = (void*)0x00fd52c0;
    }
    p_vp6_b_   = (void*)0x00c2e4e0;
    p_vp6_e_   = (void*)0x00fd64b0;
    p_vp6_a_   = (void*)0x00fd6550;
    p_vp6_c_   = (void*)0x00fd6c60;
    p_vp6_d_   = (void*)0x00fd6740;
    p_vp6_filter_row_ = (void*)0x00fd6ed0;
}

// @ 0x00fd1e00
void vp6_emms(void)
{
    _mm_empty();
}

// @ 0x00fd1e10
void vp6_expand_row_16(unsigned char* src, unsigned char* dst, int stride)
{
    __m64 zero = _mm_setzero_si64();
    int n = 8;
    do {
        __m64 v = *(__m64*)src;
        *(__m64*)dst       = _mm_unpacklo_pi8(v, zero);
        *(__m64*)(dst + 8) = _mm_unpackhi_pi8(v, zero);
        src += stride;
        dst += 16;
    } while (--n);
}

// @ 0x00fd1e50
void vp6_add_rows_16(unsigned char* a, unsigned char* b, unsigned char* dst, int stride)
{
    int n = 8;
    do {
        __m64 p = _mm_add_pi16(*(__m64*)a, *(__m64*)b);
        __m64 q = _mm_add_pi16(*(__m64*)(a + 8), *(__m64*)(b + 8));
        *(__m64*)dst = _mm_packs_pu16(p, q);
        a += 16;
        b += 16;
        dst += stride;
    } while (--n);
}

// ---------------------------------------------------------------------------
// CPU feature detection (CPUID probe).
// ---------------------------------------------------------------------------
extern "C" int __cdecl __cpuid_basic(int* out, int leaf);
#pragma intrinsic(__cpuid)

// @ 0x00fd1ea0
int WillametteNewInstructionHWSupport(void)
{
    char vendor[16];
    int  regs[4];
    int  result = 0;

    __try {
        __cpuid(regs, 0);
        *(int*)(vendor + 0) = regs[1];
        *(int*)(vendor + 4) = regs[2];
        *(int*)(vendor + 8) = regs[3];

        if (strncmp(vendor, "GenuineIntel", 12) == 0 ||
            strncmp(vendor, "AuthenticAMD", 12) == 0) {
            __cpuid(regs, 1);
            if ((regs[2] & 0x4000000) != 0)
                result = 1;
        }
    } __except (1) {
        result = 0;
    }
    return result;
}

// ---------------------------------------------------------------------------
// SSE2 8x8 inverse DCT (0x00fd1f70 full, 0x00fd2470 sparse 4x4).
//
// Layout:  r[0..7] are the eight 16-byte rows of the block (8 int16 samples each).
// Pass 1 transforms the columns (each r[i] is one row, so the eight rows are the
// eight 1-D inputs); the block is then transposed 8x8 and pass 2 transforms the
// other direction, adding 8 and shifting right by 4 for the final rounding.
//
// The fixed-point coefficients are the runtime IDCT vectors (cosines scaled by
// 2^16, stored as the negative complement where |c| > 0.5 so pmulhw can be folded
// with paddw).  ROWSEL is the sparse 4-tap path: the odd inputs are zero.
// ---------------------------------------------------------------------------
static __forceinline void vp6_idct_transpose8(__m128i* r)
{
    __m128i b0 = _mm_unpacklo_epi16(r[0], r[1]);
    __m128i b1 = _mm_unpackhi_epi16(r[0], r[1]);
    __m128i b2 = _mm_unpacklo_epi16(r[2], r[3]);
    __m128i b3 = _mm_unpackhi_epi16(r[2], r[3]);
    __m128i b4 = _mm_unpacklo_epi16(r[4], r[5]);
    __m128i b5 = _mm_unpackhi_epi16(r[4], r[5]);
    __m128i b6 = _mm_unpacklo_epi16(r[6], r[7]);
    __m128i b7 = _mm_unpackhi_epi16(r[6], r[7]);

    __m128i c0 = _mm_unpacklo_epi32(b0, b2);
    __m128i c1 = _mm_unpackhi_epi32(b0, b2);
    __m128i c2 = _mm_unpacklo_epi32(b1, b3);
    __m128i c3 = _mm_unpackhi_epi32(b1, b3);
    __m128i c4 = _mm_unpacklo_epi32(b4, b6);
    __m128i c5 = _mm_unpackhi_epi32(b4, b6);
    __m128i c6 = _mm_unpacklo_epi32(b5, b7);
    __m128i c7 = _mm_unpackhi_epi32(b5, b7);

    r[0] = _mm_unpacklo_epi64(c0, c4);
    r[1] = _mm_unpackhi_epi64(c0, c4);
    r[2] = _mm_unpacklo_epi64(c1, c5);
    r[3] = _mm_unpackhi_epi64(c1, c5);
    r[4] = _mm_unpacklo_epi64(c2, c6);
    r[5] = _mm_unpackhi_epi64(c2, c6);
    r[6] = _mm_unpacklo_epi64(c3, c7);
    r[7] = _mm_unpackhi_epi64(c3, c7);
}

static __forceinline __m128i vp6_mh(__m128i a, __m128i b) { return _mm_mulhi_epi16(a, b); }
static __forceinline __m128i vp6_aw(__m128i a, __m128i b) { return _mm_add_epi16(a, b); }
static __forceinline __m128i vp6_as(__m128i a, __m128i b) { return _mm_adds_epi16(a, b); }
static __forceinline __m128i vp6_ss(__m128i a, __m128i b) { return _mm_subs_epi16(a, b); }

// Full 8-point 1-D pass.  kFinal selects the row pass (rounding + arithmetic shift).
template <bool kFinal>
static __forceinline void vp6_idct_full(__m128i* r)
{
    const __m128i k0  = *(__m128i*)0x015b3ac0;   // cos(1*pi/16)
    const __m128i k1  = *(__m128i*)0x015b3ad0;   // cos(2*pi/16)
    const __m128i k2  = *(__m128i*)0x015b3ae0;   // cos(3*pi/16)
    const __m128i k3  = *(__m128i*)0x015b3af0;   // cos(4*pi/16)
    const __m128i k4  = *(__m128i*)0x015b3b00;   // cos(5*pi/16)
    const __m128i k5  = *(__m128i*)0x015b3b10;   // cos(6*pi/16)
    const __m128i k6  = *(__m128i*)0x015b3b20;   // cos(7*pi/16)
    const __m128i rnd = *(__m128i*)0x015b3aa0;   // rounding (8)

    __m128i x0, x1, x2, x3, x4, x5, x6, x7, even1, even2;

    x2 = r[3];
    x6 = k2;
    x4 = x2;
    x7 = r[5];
    x4 = vp6_mh(x4, x6);
    x1 = k4;
    x6 = vp6_mh(x6, x7);
    x5 = x1;
    x1 = vp6_mh(x1, x2);
    x3 = r[1];
    x5 = vp6_mh(x5, x7);
    x0 = k0;
    x4 = vp6_aw(x4, x2);
    x6 = vp6_aw(x6, x7);
    x2 = vp6_aw(x2, x1);
    x1 = r[7];
    x7 = vp6_aw(x7, x5);
    x5 = x0;
    x0 = vp6_mh(x0, x3);
    x4 = vp6_as(x4, x7);
    x5 = vp6_mh(x5, x1);
    x7 = k6;
    x6 = vp6_ss(x6, x2);
    x0 = vp6_aw(x0, x3);
    x3 = vp6_mh(x3, x7);
    x2 = r[2];
    x7 = vp6_mh(x7, x1);
    x5 = vp6_aw(x5, x1);
    x1 = x2;
    x2 = vp6_mh(x2, k1);
    x3 = vp6_ss(x3, x5);
    x5 = r[6];
    x0 = vp6_as(x0, x7);
    x7 = x5;
    x0 = vp6_ss(x0, x4);
    x5 = vp6_mh(x5, k1);
    x2 = vp6_aw(x2, x1);
    x1 = vp6_mh(x1, k5);
    x4 = vp6_as(x4, x4);
    x4 = vp6_as(x4, x0);
    x3 = vp6_ss(x3, x6);
    x5 = vp6_aw(x5, x7);
    x6 = vp6_as(x6, x6);
    x7 = vp6_mh(x7, k5);
    x6 = vp6_as(x6, x3);
    even1 = x4;
    x1 = vp6_ss(x1, x5);
    x4 = k3;
    x5 = x3;
    x3 = vp6_mh(x3, x4);
    x7 = vp6_as(x7, x2);
    even2 = x6;
    x2 = x0;
    x6 = r[0];
    x0 = vp6_mh(x0, x4);
    x5 = vp6_aw(x5, x3);
    x3 = r[4];
    x5 = vp6_ss(x5, x1);
    x2 = vp6_aw(x2, x0);
    x6 = vp6_ss(x6, x3);
    x0 = x6;
    x6 = vp6_mh(x6, x4);
    x3 = vp6_as(x3, x3);
    x1 = vp6_as(x1, x1);
    x3 = vp6_as(x3, x0);
    x1 = vp6_as(x1, x5);
    x4 = vp6_mh(x4, x3);
    x6 = vp6_aw(x6, x0);
    x6 = vp6_ss(x6, x2);
    x2 = vp6_as(x2, x2);
    x0 = even1;
    x2 = vp6_as(x2, x6);
    x4 = vp6_aw(x4, x3);
    x2 = vp6_ss(x2, x1);
    if (kFinal)
        x2 = vp6_as(x2, rnd);
    x1 = vp6_as(x1, x1);
    x1 = vp6_as(x1, x2);
    if (kFinal)
        x2 = _mm_srai_epi16(x2, 4);
    x4 = vp6_ss(x4, x7);
    if (kFinal)
        x1 = _mm_srai_epi16(x1, 4);
    x3 = even2;
    x7 = vp6_as(x7, x7);
    x7 = vp6_as(x7, x4);
    x4 = vp6_ss(x4, x3);
    if (kFinal)
        x4 = vp6_as(x4, rnd);
    x3 = vp6_as(x3, x3);
    x3 = vp6_as(x3, x4);
    if (kFinal)
        x4 = _mm_srai_epi16(x4, 4);
    x6 = vp6_ss(x6, x5);
    if (kFinal)
        x3 = _mm_srai_epi16(x3, 4);
    if (kFinal)
        x6 = vp6_as(x6, rnd);
    x5 = vp6_as(x5, x5);
    x5 = vp6_as(x5, x6);
    if (kFinal)
        x6 = _mm_srai_epi16(x6, 4);
    if (kFinal)
        x5 = _mm_srai_epi16(x5, 4);
    x7 = vp6_ss(x7, x0);
    if (kFinal)
        x7 = vp6_as(x7, rnd);
    x0 = vp6_as(x0, x0);
    x0 = vp6_as(x0, x7);
    if (kFinal)
        x7 = _mm_srai_epi16(x7, 4);
    if (kFinal)
        x0 = _mm_srai_epi16(x0, 4);

    r[0] = x0;
    r[1] = x1;
    r[2] = x2;
    r[3] = x3;
    r[4] = x4;
    r[5] = x5;
    r[6] = x6;
    r[7] = x7;
}

// Sparse 4-tap 1-D pass: the odd inputs are zero (only the top-left 4x4 of the
// coefficient block is coded, so the decoder selects this 4x4 inverse DCT).
template <bool kFinal>
static __forceinline void vp6_idct_sparse(__m128i* r)
{
    const __m128i k0  = *(__m128i*)0x015b3ac0;
    const __m128i k1  = *(__m128i*)0x015b3ad0;
    const __m128i k2  = *(__m128i*)0x015b3ae0;
    const __m128i k3  = *(__m128i*)0x015b3af0;
    const __m128i k4  = *(__m128i*)0x015b3b00;
    const __m128i k5  = *(__m128i*)0x015b3b10;
    const __m128i k6  = *(__m128i*)0x015b3b20;
    const __m128i rnd = *(__m128i*)0x015b3aa0;

    __m128i x0, x1, x2, x3, x4, x5, x6, x7, even1, even2;

    x2 = r[3];
    x6 = k2;
    x4 = x2;
    x4 = vp6_mh(x4, x6);
    x1 = k4;
    x5 = x1;
    x1 = vp6_mh(x1, x2);
    x3 = r[1];
    x0 = k0;
    x4 = vp6_aw(x4, x2);
    x7 = k6;
    x2 = vp6_aw(x2, x1);
    x5 = x0;
    x0 = vp6_mh(x0, x3);
    x6 = _mm_setzero_si128();
    x6 = vp6_ss(x6, x2);
    x0 = vp6_aw(x0, x3);
    x3 = vp6_mh(x3, x7);
    x2 = r[2];
    x1 = x2;
    x2 = vp6_mh(x2, k1);
    x0 = vp6_ss(x0, x4);
    x2 = vp6_aw(x2, x1);
    x1 = vp6_mh(x1, k5);
    x4 = vp6_as(x4, x4);
    x4 = vp6_as(x4, x0);
    x3 = vp6_ss(x3, x6);
    x6 = vp6_as(x6, x6);
    x6 = vp6_as(x6, x3);
    even1 = x4;
    x4 = k3;
    x5 = x3;
    x3 = vp6_mh(x3, x4);
    x7 = x2;
    even2 = x6;
    x2 = x0;
    x6 = r[0];
    x0 = vp6_mh(x0, x4);
    x5 = vp6_aw(x5, x3);
    x5 = vp6_ss(x5, x1);
    x2 = vp6_aw(x2, x0);
    x0 = x6;
    x6 = vp6_mh(x6, x4);
    x1 = vp6_as(x1, x1);
    x1 = vp6_as(x1, x5);
    x6 = vp6_aw(x6, x0);
    x4 = x6;
    x6 = vp6_ss(x6, x2);
    x2 = vp6_as(x2, x2);
    x0 = even1;
    x2 = vp6_as(x2, x6);
    x2 = vp6_ss(x2, x1);
    if (kFinal)
        x2 = vp6_as(x2, rnd);
    x1 = vp6_as(x1, x1);
    x1 = vp6_as(x1, x2);
    if (kFinal)
        x2 = _mm_srai_epi16(x2, 4);
    x4 = vp6_ss(x4, x7);
    if (kFinal)
        x1 = _mm_srai_epi16(x1, 4);
    x3 = even2;
    x7 = vp6_as(x7, x7);
    x7 = vp6_as(x7, x4);
    x4 = vp6_ss(x4, x3);
    if (kFinal)
        x4 = vp6_as(x4, rnd);
    x3 = vp6_as(x3, x3);
    x3 = vp6_as(x3, x4);
    if (kFinal)
        x4 = _mm_srai_epi16(x4, 4);
    x6 = vp6_ss(x6, x5);
    if (kFinal)
        x3 = _mm_srai_epi16(x3, 4);
    if (kFinal)
        x6 = vp6_as(x6, rnd);
    x5 = vp6_as(x5, x5);
    x5 = vp6_as(x5, x6);
    if (kFinal)
        x6 = _mm_srai_epi16(x6, 4);
    if (kFinal)
        x5 = _mm_srai_epi16(x5, 4);
    x7 = vp6_ss(x7, x0);
    if (kFinal)
        x7 = vp6_as(x7, rnd);
    x0 = vp6_as(x0, x0);
    x0 = vp6_as(x0, x7);
    if (kFinal)
        x7 = _mm_srai_epi16(x7, 4);
    if (kFinal)
        x0 = _mm_srai_epi16(x0, 4);

    r[0] = x0;
    r[1] = x1;
    r[2] = x2;
    r[3] = x3;
    r[4] = x4;
    r[5] = x5;
    r[6] = x6;
    r[7] = x7;
}

// @ 0x00fd1f70
short* vp6_filter_row_sse2_a(short* m, short* h, short* out)
{
    __m128i r[8];
    const __m128i* pm = (const __m128i*)m;
    const __m128i* ph = (const __m128i*)h;
    for (int i = 0; i < 8; i++)
        r[i] = _mm_mullo_epi16(pm[i], ph[i]);

    vp6_idct_full<false>(r);
    vp6_idct_transpose8(r);
    vp6_idct_full<true>(r);

    __m128i* po = (__m128i*)out;
    for (int i = 0; i < 8; i++)
        po[i] = r[i];
    return m;
}

// @ 0x00fd2470
short* vp6_filter_row_sse2_b(short* m, short* h, short* out)
{
    __m128i r[8];
    const __m128i* pm = (const __m128i*)m;
    const __m128i* ph = (const __m128i*)h;
    for (int i = 0; i < 4; i++)
        r[i] = _mm_mullo_epi16(pm[i], ph[i]);

    vp6_idct_sparse<false>(r);
    vp6_idct_transpose8(r);
    vp6_idct_sparse<true>(r);

    __m128i* po = (__m128i*)out;
    for (int i = 0; i < 8; i++)
        po[i] = r[i];
    return m;
}

// @ 0x00fd28e0
void vp6_store_row_dc(unsigned char* dst, int stride, __m128i* src)
{
    unsigned __int64 mask;
    memcpy(&mask, (void*)0x015b3bb0, 8);
    int n = 8;
    do {
        __m64 lo = _mm_movepi64_pi64(_mm_packs_epi16(*src, _mm_setzero_si128()));
        *(__m64*)dst = _mm_xor_si64(lo, *(__m64*)&mask);
        src++;
        dst += stride;
    } while (--n);
}

// @ 0x00fd2920
void vp6_add_rows_8(unsigned char* a, unsigned char* dst, short* add, int stride)
{
    __m128i zero = _mm_setzero_si128();
    short*  end  = add + 0x40;
    do {
        __m128i s = _mm_unpacklo_epi8(_mm_loadl_epi64((__m128i*)a), zero);
        s = _mm_adds_epi16(s, *(__m128i*)add);
        *(__m64*)dst = _mm_movepi64_pi64(_mm_packus_epi16(s, zero));
        a   += stride;
        dst += stride;
        add += 8;
    } while (add < end);
}

// ---------------------------------------------------------------------------
// b5rw (On2 VP6) allocator hooks: forward to the registered allocator vtable,
// otherwise fall back to malloc/free.
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) void* __cdecl malloc(size_t);
extern "C" __declspec(dllimport) void  __cdecl free(void*);

void* g_vp6Allocator;

struct vp6_alloc_vtbl {
    void* (__stdcall *fn2)(unsigned int, const char*, int);
    void  (__stdcall *fn3)(void*, int);
};

// @ 0x00fd2980
void* vp6_alloc(unsigned int size)
{
    vp6_alloc_vtbl* a = (vp6_alloc_vtbl*)g_vp6Allocator;
    if (a != 0)
        return a->fn2(size, "VP6", 1);
    return malloc(size);
}

// @ 0x00fd29b0
void vp6_free(void* p)
{
    vp6_alloc_vtbl* a = (vp6_alloc_vtbl*)g_vp6Allocator;
    if (a != 0) {
        a->fn3(p, 0);
        return;
    }
    free(p);
}

// @ 0x00fd29d0
void vp6_bitreader_init(int* br, unsigned char* p)
{
    br[4] = 0;
    br[0] = 0;
    br[1] = 0xff;
    br[3] = 8;
    br[5] = (int)p;
    int v = p[0];
    v = (v << 8) + p[1];
    v = (v << 8) + p[2];
    v = (v << 8) + p[3];
    br[2] = v;
    br[4] = 4;
}
