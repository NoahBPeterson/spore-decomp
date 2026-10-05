// Slice s007c1c10 — DXT/bump-map helpers in the texture subsystem.
// /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"

// ---------------------------------------------------------------------------
// @ 0x007c2730  anonymous-namespace::expand_2_32
// Expand a packed 2-bit-per-channel value into 4 ARGB dwords per iteration.
// ---------------------------------------------------------------------------
void expand_2_32(uint32_t* dst, int stride, uint32_t src, uint32_t* table)
{
    for (int i = 4; i != 0; --i) {
        dst[0] = table[src & 3];
        dst[1] = *(uint32_t*)((char*)table + (src & 0xc));
        src >>= 4;
        dst[2] = table[src & 3];
        dst[3] = *(uint32_t*)((char*)table + (src & 0xc));
        src >>= 4;
        dst = (uint32_t*)((char*)dst + stride);
    }
}

// ---------------------------------------------------------------------------
// @ 0x007c24a0  SP::cBumpMapTable::cBumpMapTable(this, float)
// ---------------------------------------------------------------------------
struct F2I { float f; int i; };

struct cBumpMapTable {
    float fastnorm[0x4001];
    cBumpMapTable(float param);
};

cBumpMapTable::cBumpMapTable(float param)
{
    float k = 1020.0f / param;
    fastnorm[0] = k;
    float kk = k * k;
    for (int i = 0; i < 0x4000; ++i) {
        float v = (float)i * 64.0f + kk;
        F2I u;
        u.f = v;
        u.i = 0x5f400000 - (u.i >> 1);
        float w = u.f;
        fastnorm[i + 1] = ((1.5f - (w * w) * (v * 0.5f)) * w) * 127.5f;
    }
}

// ---------------------------------------------------------------------------
// remaining routines (skeletons)
// ---------------------------------------------------------------------------
void FUN_007c1c10(void* a) { (void)a; }
void FUN_007c2540(void* a) { (void)a; }
void ColorReduce(void* a) { (void)a; }
void ConvertDXT1ToARGB8888(void* a) { (void)a; }
