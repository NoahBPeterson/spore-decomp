// src/game/SPMovie/Wmt_CpuID.cpp -- migrated from slice(s) s00fd1c60, s00fd0d20, s00fcfe60 by tools/migrate/rewrite.py
// Object file: SPMovie/Wmt_CpuID.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* g_vp6ExpandFn;              // 0x016d9414
#include <emmintrin.h>
#include <string.h>
#include <crtdefs.h>
#include <mmintrin.h>
#include <xmmintrin.h>
#include <stdlib.h>
#include <intrin.h>

// ---- items of slice s00fcfe60 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef short          s16;
void vp6_expand_row_16(u8* dst, u8* src, int n);   // 0x00fd1e10
void FUN_00fd1ba0(int* a, void* b, int* c);        // 0x00fd1ba0
void FUN_00fd1ab0();                               // 0x00fd1ab0
void FUN_00fd1ae0();                               // 0x00fd1ae0
void FUN_00fd60b0();                               // 0x00fd60b0
extern "C" void* g_vp6ExpandFn;              // 0x016d9414
// ---- items of slice s00fcfe60 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_00fd0410(const u8* src, u8* dst, int srcStride, int unused, int rows, int dstStride, const s16* k);  // 0x00fd0410 (stays in the slice: not this object's)
void FUN_00fd04f0(const u8* src, u8* dst, int srcStride, int unused, int rows, int dstStride, const s16* k);  // 0x00fd04f0 (stays in the slice: not this object's)
void FUN_00fd05c0(const u8* src, u8* dst, int srcStride, int unused, int rows, int dstStride, const s16* k);  // 0x00fd05c0 (stays in the slice: not this object's)
void FUN_00fd0650(const u8* src, u8* dst, int srcStride, int unused, int rows, int dstStride, const s16* k);  // 0x00fd0650 (stays in the slice: not this object's)
void FUN_00fd06d0(const u8* src, u8* dst, int srcStride, int unused, int rows, int dstStride, const s16* k);  // 0x00fd06d0 (stays in the slice: not this object's)
void FUN_00fd07d0(int a1, int a2, int a3, int a4, int a5, int a6, int a7);  // 0x00fd07d0 (stays in the slice: not this object's)

// ---- items of slice s00fd0d20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memset(void*, int, unsigned int);
#undef _CRT_ALIGN
#pragma function(memset)
int WillametteNewInstructionHWSupport(void);
// ---- items of slice s00fd0d20 end

// @ 0x00fd03c0
void FUN_00fd03c0()
{
    int local_c;
    int local_8;
    char local_4[4];
    FUN_00fd1ba0(&local_8, local_4, &local_c);
    if (local_c != 0) { g_vp6ExpandFn = (void*)&FUN_00fd1ae0; return; }
    g_vp6ExpandFn = (void*)&FUN_00fd1ab0;
    if (local_8 == 0) g_vp6ExpandFn = (void*)&FUN_00fd60b0;
}

// @ 0x00fd0830
void FUN_00fd0830(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    uint32_t tmp[64];
    int d = a2 - a1;
    if (d < 0) { d = -d; int t = a1; a1 = a2; a2 = t; }
    if (d == 0) return;

    if (d == 1) {
        if (a6)
            FUN_00fd0410((const u8*)a1, (u8*)tmp, 1, 8, 8, a4, (const s16*)(a4 * 64 + 0x15b3150));
        else
            FUN_00fd05c0((const u8*)a1, (u8*)tmp, 1, 8, 8, a5, (const s16*)(a4 * 32 + 0x15b3050));
    } else if (d == a3) {
        if (a6)
            FUN_00fd04f0((const u8*)a1, (u8*)tmp, a3, 8, 8, a5, (const s16*)(a5 * 64 + 0x15b3150));
        else
            FUN_00fd0650((const u8*)a1, (u8*)tmp, a3, 8, 8, a5, (const s16*)(a5 * 32 + 0x15b3050));
    } else if (d == a3 - 1) {
        if (a6)
            FUN_00fd07d0(a1 - 1, (int)tmp, a3, a4 * 64 + 0x15b3150, a4 * 64 + 0x15b3150, 0, 0);
        else
            FUN_00fd06d0((const u8*)(a1 - 1), (u8*)tmp, a3, 8, 8, a5, (const s16*)(a4 * 32 + 0x15b3050));
    } else if (d == a3 + 1) {
        if (a6)
            FUN_00fd07d0(a1, (int)tmp, a3, a4 * 64 + 0x15b3150, a4 * 64 + 0x15b3150, 0, 0);
        else
            FUN_00fd06d0((const u8*)a1, (u8*)tmp, a3, 8, 8, a5, (const s16*)(a4 * 32 + 0x15b3050));
    } else {
        return;
    }
    vp6_expand_row_16((u8*)a7, (u8*)tmp, 8);
}

// @ 0x00fd1ba0
void __cdecl FUN_00fd1ba0(int* a, int* b, int* c)
{
    int level = 1;
    if (WillametteNewInstructionHWSupport())
        level = 12;
    // Retail dispatches directly through a table covering levels 0 through 12.
    __assume(level >= 0 && level <= 12);
    switch (level) {
    case 0:
    case 2:
    case 4:
    case 5:
    case 8:
    case 9:
    case 10:
        *a = 0;
        *b = 0;
        *c = 0;
        break;
    case 1:
    case 3:
    case 6:
    case 7:
        *a = 1;
        *b = 0;
        *c = 0;
        break;
    case 11:
        *a = 1;
        *b = 1;
        *c = 0;
        break;
    case 12:
        *a = 1;
        *b = 1;
        *c = 1;
        break;
    }
}

typedef void (*Vp6Kernel)();

struct Vp6DispatchTable {
    Vp6Kernel filterRow;
    Vp6Kernel addRows;
    Vp6Kernel inverseTransforms[65];
    Vp6Kernel addResidual;
    Vp6Kernel fillRow;
};

struct Vp6ExpansionTable {
    Vp6Kernel endMmx;
    Vp6Kernel expandRow;
};

extern "C" Vp6DispatchTable g_16d9580;
extern "C" Vp6ExpansionTable g_16d9418;
void vp6_emms();
void vp6_add_rows_16(u8* a, u8* b, u8* dst, int stride);
extern "C" void FUN_00c2e4e0();
extern "C" void FUN_00fd0d20();
extern "C" void FUN_00fd0eb0();
extern "C" void FUN_00fd0f10();
extern "C" void FUN_00fd1610();
extern "C" void FUN_00fd1a20();
extern "C" void FUN_00fd1a60();
extern "C" void FUN_00fd1f70();
extern "C" void FUN_00fd2470();
extern "C" void FUN_00fd2870();
extern "C" void FUN_00fd28e0();
extern "C" void FUN_00fd2920();
extern "C" void FUN_00fd52c0();
extern "C" void FUN_00fd5770();
extern "C" void FUN_00fd5d50();
extern "C" void FUN_00fd64b0();
extern "C" void FUN_00fd6550();
extern "C" void FUN_00fd6740();
extern "C" void FUN_00fd6c60();
extern "C" void FUN_00fd6ed0();

// @ 0x00fd1c60
void vp6_setup_tables(void)
{
    int hasSSE2;
    int hasMMX;
    int has3DNow;
    FUN_00fd1ba0(&hasMMX, &has3DNow, &hasSSE2);

    if (hasSSE2 != 0) {
        for (unsigned i = 0; i <= 0x40; ++i) {
            if (i <= 1)
                g_16d9580.inverseTransforms[i] = &FUN_00fd2870;
            else if (i <= 0xa)
                g_16d9580.inverseTransforms[i] = &FUN_00fd2470;
            else
                g_16d9580.inverseTransforms[i] = &FUN_00fd1f70;
        }
        g_16d9580.fillRow = &FUN_00fd28e0;
        g_16d9580.addRows = &FUN_00fd2920;
        g_16d9418.endMmx = &vp6_emms;
        g_16d9418.expandRow = reinterpret_cast<Vp6Kernel>(&vp6_expand_row_16);
        g_16d9580.addResidual = reinterpret_cast<Vp6Kernel>(&vp6_add_rows_16);
        g_16d9580.filterRow = &FUN_00fd0d20;
        return;
    }
    if (hasMMX != 0) {
        for (unsigned i = 0; i <= 0x40; ++i) {
            if (i <= 1)
                g_16d9580.inverseTransforms[i] = &FUN_00fd0eb0;
            else if (i <= 0xa)
                g_16d9580.inverseTransforms[i] = &FUN_00fd1610;
            else
                g_16d9580.inverseTransforms[i] = &FUN_00fd0f10;
        }
        g_16d9580.fillRow = &FUN_00fd1a20;
        g_16d9580.addRows = &FUN_00fd1a60;
        g_16d9418.endMmx = &vp6_emms;
        g_16d9418.expandRow = reinterpret_cast<Vp6Kernel>(&vp6_expand_row_16);
        g_16d9580.addResidual = reinterpret_cast<Vp6Kernel>(&vp6_add_rows_16);
        g_16d9580.filterRow = reinterpret_cast<Vp6Kernel>(&FUN_00fd0830);
        return;
    }
    for (int i = 0; i <= 0x40; ++i) {
        if (i <= 1)
            g_16d9580.inverseTransforms[i] = &FUN_00fd5d50;
        else if (i <= 0xa)
            g_16d9580.inverseTransforms[i] = &FUN_00fd5770;
        else
            g_16d9580.inverseTransforms[i] = &FUN_00fd52c0;
    }
    g_16d9418.endMmx = &FUN_00c2e4e0;
    g_16d9580.fillRow = &FUN_00fd64b0;
    g_16d9580.addRows = &FUN_00fd6550;
    g_16d9418.expandRow = &FUN_00fd6c60;
    g_16d9580.addResidual = &FUN_00fd6740;
    g_16d9580.filterRow = &FUN_00fd6ed0;
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

// @ 0x00fd1ea0
#pragma intrinsic(__cpuid)
namespace  {
int WillametteNewInstructionHWSupport()
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
}  // namespace 
