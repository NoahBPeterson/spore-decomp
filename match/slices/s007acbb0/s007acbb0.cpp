// Slice s007acbb0 — DXT block downsampling / matching helpers used by the
// texture manager (0x7acbb0..0x7ad950).
// Optimized region: /O2 /MD /Gy /EHsc /TP.
#include "types.h"

// ---------------------------------------------------------------------------
// @ 0x007ace40
// 2x2 box filter of byte pixels, averaging two rows of `width` pixels.
void FUN_007ace40(uint8_t* dest, int destStride, uint8_t* src, int srcStride, int width, int height)
{
    uint8_t* d = dest;
    uint8_t* s2 = src + srcStride;
    int step = (srcStride - width) * 2;
    int pad = destStride - width;
    do {
        int n = width;
        do {
            *d = (uint8_t)((src[1] + s2[1] + s2[0] + src[0] + 2) >> 2);
            d++;
            src += 2;
            s2 += 2;
        } while (--n);
        d += pad;
        src += step;
        s2 += step;
    } while (--height);
}

// ---------------------------------------------------------------------------
// @ 0x007aceb0
// Vertical 2-tap average of a single byte column.
void FUN_007aceb0(uint8_t* dest, int destStride, uint8_t* src, int srcStride, int rows)
{
    uint8_t* d = dest;
    uint8_t* s2 = src + srcStride;
    int step = srcStride * 2;
    do {
        *d = (uint8_t)((src[0] + s2[0] + 1) >> 1);
        d += destStride;
        src += step;
        s2 += step;
    } while (--rows);
}

// ---------------------------------------------------------------------------
// @ 0x007acef0
// 2x2 box filter of 32-bit RGBA pixels (SWAR byte average), two rows.
void FUN_007acef0(uint32_t* dest, int destStride, uint32_t* src, int srcStride, int width, int height)
{
    uint32_t* d = dest;
    uint32_t* s2 = (uint32_t*)((char*)src + srcStride);
    int step = (srcStride - width * 4) * 2;
    int pad = destStride - width * 4;
    do {
        int n = width;
        do {
            uint32_t a = (src[1] | src[0]) - (((src[1] ^ src[0]) >> 1) & 0x7f7f7f7f);
            uint32_t b = (s2[1] | s2[0]) - (((s2[1] ^ s2[0]) >> 1) & 0x7f7f7f7f);
            *d = (a | b) - (((a ^ b) >> 1) & 0x7f7f7f7f);
            d++;
            src += 2;
            s2 += 2;
        } while (--n);
        d = (uint32_t*)((char*)d + pad);
        src = (uint32_t*)((char*)src + step);
        s2 = (uint32_t*)((char*)s2 + step);
    } while (--height);
}

// ---------------------------------------------------------------------------
// @ 0x007acfa0
// Vertical 2-tap average of a single 32-bit RGBA column (SWAR).
void FUN_007acfa0(uint32_t* dest, int destStride, uint32_t* src, int srcStride, int rows)
{
    uint32_t* d = dest;
    uint32_t* s2 = (uint32_t*)((char*)src + srcStride);
    int step = srcStride * 2;
    do {
        *d = (*s2 | *src) - (((*s2 ^ *src) >> 1) & 0x7f7f7f7f);
        d = (uint32_t*)((char*)d + destStride);
        src = (uint32_t*)((char*)src + step);
        s2 = (uint32_t*)((char*)s2 + step);
    } while (--rows);
}

// ---------------------------------------------------------------------------
// @ 0x007acfe0
// Dispatch a downsampling of one DXT surface into another.
// fields: +0x1c width/height-scaled, +0x20, +0x24 format, +0x28 data pointer.
struct DXTDesc {
    char     mPad00[0x1c];
    int      mField1c;   // +0x1c
    int      mField20;   // +0x20
    int      mFormat;    // +0x24
    void*    mpData;     // +0x28
};

bool FUN_007acfe0(DXTDesc* dst, DXTDesc* src)
{
    int s1c = src->mField1c;
    int d1c = dst->mField1c;
    if ((d1c == s1c * 2) || ((d1c == 1) && (s1c == 1))) {
        int s20 = src->mField20;
        if (((dst->mField20 == s20 * 2) || ((dst->mField20 == 1) && (s20 == 1))) &&
            (dst->mFormat == src->mFormat)) {
            int n1c = d1c;
            int n1c2 = s1c;
            if (dst->mFormat == 2) {
                n1c = d1c * 4;
                n1c2 = s1c * 4;
            }
            if (dst->mField20 == 1)
                n1c = 0;
            if (dst->mFormat == 1) {
                if (d1c > 1) {
                    FUN_007ace40((uint8_t*)src->mpData, n1c2, (uint8_t*)dst->mpData, n1c, s1c, s20);
                    return true;
                }
                FUN_007aceb0((uint8_t*)src->mpData, n1c2, (uint8_t*)dst->mpData, n1c, s20);
                return true;
            }
            if (dst->mFormat == 2) {
                if (d1c > 1) {
                    FUN_007acef0((uint32_t*)src->mpData, n1c2, (uint32_t*)dst->mpData, n1c, s1c, s20);
                    return true;
                }
                FUN_007acfa0((uint32_t*)src->mpData, n1c2, (uint32_t*)dst->mpData, n1c, s20);
                return true;
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x007acbb0
extern "C" void FUN_007acbb0(void)
{
    // PARTIAL: cTextureManager::GetTexture (EH, map find + sync/async load).
}

// @ 0x007acd90
extern "C" void FUN_007acd90(void)
{
    // PARTIAL: cTextureManager::StallUntilLoaded (EH).
}

// @ 0x007ad0c0
extern "C" uint32_t FUN_007ad0c0(void)
{
    // PARTIAL: DXT3 alpha-block expansion into RGBA4444.
    return 0;
}

// @ 0x007ad2e0
extern "C" uint32_t mappixel(void)
{
    // PARTIAL: map a pixel against four DXT candidates (EAX/ECX register convention).
    return 0;
}

// @ 0x007ad400
extern "C" uint32_t mappixeltransparent(void)
{
    // PARTIAL: like mappixel but including alpha in the error metric.
    return 0;
}

// @ 0x007ad610
extern "C" uint32_t trymappixel(void)
{
    // PARTIAL: minimum squared error against four candidates.
    return 0;
}

// @ 0x007ad760
extern "C" uint32_t rbmappixel(void)
{
    // PARTIAL: reciprocal min-error variant.
    return 0;
}

// @ 0x007ad810
extern "C" uint32_t trymapblock(void)
{
    // PARTIAL: test a candidate 4x4 block against a 256-entry cache.
    return 0;
}

// @ 0x007ad950
extern "C" uint32_t trymapblockfast(void)
{
    // PARTIAL: MMX fast path for trymapblock.
    return 0;
}
