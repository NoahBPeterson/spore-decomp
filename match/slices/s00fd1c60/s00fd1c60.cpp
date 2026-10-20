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

// @ 0x00fd1f70
void vp6_filter_row_sse2_a(short* m, short* h, short* out)
{
    __m128i x0 = *(__m128i*)(m + 0);
    __m128i x1 = *(__m128i*)(m + 8);
    __m128i x2 = *(__m128i*)(m + 16);
    __m128i x3 = *(__m128i*)(m + 24);
    *(__m128i*)(out + 0)  = _mm_mullo_epi16(x0, *(__m128i*)(h + 0));
    *(__m128i*)(out + 8)  = _mm_mullo_epi16(x1, *(__m128i*)(h + 8));
    *(__m128i*)(out + 16) = _mm_mullo_epi16(x2, *(__m128i*)(h + 16));
    *(__m128i*)(out + 24) = _mm_mullo_epi16(x3, *(__m128i*)(h + 24));
}

// @ 0x00fd2470
void vp6_filter_row_sse2_b(short* m, short* h, short* out)
{
    __m128i x0 = *(__m128i*)(m + 0);
    __m128i x1 = *(__m128i*)(m + 8);
    __m128i x2 = *(__m128i*)(m + 16);
    __m128i x3 = *(__m128i*)(m + 24);
    *(__m128i*)(out + 0)  = _mm_mullo_epi16(x0, *(__m128i*)(h + 0));
    *(__m128i*)(out + 8)  = _mm_mullo_epi16(x1, *(__m128i*)(h + 8));
    *(__m128i*)(out + 16) = _mm_mullo_epi16(x2, *(__m128i*)(h + 16));
    *(__m128i*)(out + 24) = _mm_mullo_epi16(x3, *(__m128i*)(h + 24));
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
