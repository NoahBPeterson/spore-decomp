// Slice s0088a490 -- 0x0088a490: glyph-cache texture upload helpers.  CopyPixels reformats
// source glyph bitmaps into the cached texture (DXT-compressed, palettised or 32-bpp),
// FillBlocks clears a freshly allocated texture surface, and Remove unlinks a glyph info
// record from the cache hashtable and resets its texture bookkeeping.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include "types.h"
#include <string.h>

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(_p, __COUNTER__)();
#define VP4 VP VP VP VP

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void*);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void*);

// squish::Compress(const uint8_t* src, void* dst, uint32_t pitch, uint32_t size)
void Compress(const uint8_t* src, void* dst, uint32_t pitch, uint32_t size);  // 0x0088a76e0

// ---- cache records -------------------------------------------------------------------------

// One cached glyph.  The offsets at +0x50 are the per-glyph texture rects; +0x15e is the number
// of rects and +0x15f the per-rect bitmap index bytes.
struct GlyphInfo {
    char pad0[0x4c];
    int  mRefs;              // +0x4c
    uint32_t mOffsets[0x40]; // +0x50
    int  mTotal;             // +0x150
    int  mA;                 // +0x154
    int  mB;                 // +0x158
    char pad15c[2];
    uint8_t mCount;          // +0x15e
    uint8_t mValues[1];      // +0x15f
};

// Hashtable iterator {node, bucket slot}; the erase helper returns it by value.
struct HashIter {
    void* mpNode;
    void* mpSlot;
};

struct HashTable {
    char pad0[4];            // +0x00 (within the sub-object at GlyphCache+0xc)
    void** mpBuckets;        // +0x04 -> GlyphCache+0x10
    int    mnBuckets;        // +0x08 -> GlyphCache+0x14
    HashIter erase(HashIter it);  // 0x0088aa50
};

struct GlyphCache {
    VP4 VP4 VP4 VP4 VP4 VP VP VP
    virtual void OnRemove(GlyphInfo* info);   // vtable +0x5c
    char pad04[8];
    HashTable mTable;        // +0x0c
    char pad18[0x168 - 0x18];
    uint32_t mCS[6];         // +0x168 (CRITICAL_SECTION, 0x18 bytes)

    void CopyPixels(uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, int format,
                    uint8_t* a7, uint32_t a8, uint32_t a9, uint32_t a10, int a11);  // 0x0088a490
    void FillBlocks(uint8_t* dst, uint32_t size, uint32_t stride, int format);       // 0x0088a950
    bool Remove(GlyphInfo* info);                                                    // 0x0088ab80
};

// ---- CopyPixels -----------------------------------------------------------------------------

// @ 0x0088a490
void GlyphCache::CopyPixels(uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, int format,
                            uint8_t* a7, uint32_t a8, uint32_t a9, uint32_t a10, int a11)
{
    void* cs = mCS;
    EnterCriticalSection(cs);

    if (format == 3) {
        if (a11 == 0x20) {
            // DXT-ish 4x4 block compression: pack the source nibbles into 2-byte texel pairs,
            // then hand each 4x4 block to the squish compressor.
            uint8_t* dst = (uint8_t*)(a2 + (a4 >> 2) * a5 + a3 * 4);
            for (uint32_t y = 0; y < a9; y += 4) {
                uint8_t* rowDst = dst;
                uint32_t remain = a9 - y;
                int n = (remain > 4) ? 4 : (int)remain;
                if (a8 != 0) {
                    uint32_t size = a9 * a10;
                    uint32_t rowStep = a10 >> 2;
                    uint32_t blocks = ((a8 - 1) >> 2) + 1;
                    uint8_t* s = a7 + rowStep * y * 4;
                    do {
                        if (n != 0) {
                            uint8_t* p = s + 0xc;
                            uint8_t* o = rowDst;
                            int k = n;
                            do {
                                o[0] = (uint8_t)((p[-5] & 0xf0) |
                                                 (*(uint32_t*)(p - 0xc) >> 0x1c));
                                o[1] = (uint8_t)((*(uint32_t*)(p - 4) >> 0x1c) |
                                                 (p[3] & 0xf0));
                                p += rowStep * 4;
                                o += 2;
                            } while (--k != 0);
                        }
                        Compress(s, rowDst, a10, size);
                        rowDst += 0x10;
                        s += 0x10;
                    } while (--blocks != 0);
                }
                dst += a5;
            }
            LeaveCriticalSection(cs);
            return;
        }

        // Uncompressed: expand each source group of four texels into one 16-bit palette index.
        uint32_t end = a4 + a9;
        uint8_t* dst = (uint8_t*)(a2 + (a4 >> 2) * a5 + a3 * 4);
        uint32_t sub = a4 & 3;
        if ((int)a4 < (int)end) {
            do {
                uint16_t* ps = (uint16_t*)(dst + sub * 2);
                uint32_t mask = 0x80;
                uint32_t groups = a8 >> 2;
                uint8_t* p = a7;
                if (a11 == 1) {
                    for (uint32_t k = groups; k != 0; --k) {
                        uint8_t byte = *p;
                        int v = 0;
                        if (mask & byte)
                            v = 0xf;
                        mask >>= 1;
                        if (mask & byte)
                            v += 0xf0;
                        mask >>= 1;
                        if (mask & byte)
                            v += 0xf00;
                        mask >>= 1;
                        if (mask & byte)
                            v += 0xf000;
                        mask >>= 1;
                        if (mask == 0) {
                            ++p;
                            mask = 0x80;
                        }
                        *ps = (uint16_t)v;
                        ps += 8;
                    }
                } else {
                    for (uint32_t k = groups; k != 0; --k) {
                        *ps = (uint16_t)(((((p[3] & 0xf0) << 4) + (p[2] & 0xf0)) << 4) +
                                         (p[1] & 0xf0) + (p[0] >> 4));
                        ps += 8;
                        p += 4;
                    }
                }
                uint32_t n = a8 & 3;
                if (n != 0) {
                    int v = 0;
                    if (a11 == 1) {
                        int step = 0xf;
                        uint8_t byte = *p;
                        uint32_t k = n;
                        do {
                            if (mask & byte)
                                v += step;
                            step <<= 4;
                            mask >>= 1;
                        } while (--k != 0);
                    } else {
                        int i = (int)n - 1;
                        while (i >= 0) {
                            v = (v << 4) + (p[i] >> 4);
                            --i;
                        }
                    }
                    *ps = (uint16_t)v;
                }
                ++a4;
                sub = a4 & 3;
                if (sub == 0)
                    dst += a5;
                a7 += a10;
            } while ((int)a4 < (int)end);
        }
        LeaveCriticalSection(cs);
        return;
    }

    if (format == 0x20) {
        if (a11 == 8) {
            // 8-bpp luminance -> 32-bpp
            uint8_t* dst = (uint8_t*)(a2 + (((a4 * a5) >> 2) + a3) * 4);
            uint8_t* end = a7 + a9 * a10;
            for (uint8_t* s = a7; s < end; s += a10) {
                uint8_t* rowEnd = s + a8;
                uint8_t* q = dst;
                for (uint8_t* p = s; p < rowEnd; ++p) {
                    *(uint32_t*)q = (uint32_t)(*p) * 0x1000000 + 0xffffff;
                    q += 4;
                }
                dst += a5;
            }
            LeaveCriticalSection(cs);
            return;
        }
        if (a11 == 1) {
            // 1-bpp -> 32-bpp
            uint8_t* end = a7 + a9 * a10;
            uint8_t* dst = (uint8_t*)(a2 + (((a4 * a5) >> 2) + a3) * 4);
            uint8_t* dstRowEnd = dst + a8 * 4;
            uint8_t* s = a7;
            if (s < end) {
                do {
                    uint32_t mask = 0x80;
                    uint8_t* p = s;
                    for (uint8_t* q = dst; q < dstRowEnd; q += 4) {
                        uint8_t bit = (uint8_t)mask;
                        mask >>= 1;
                        *(uint32_t*)q = ((*p & bit) ? 0xff000000u : 0u) + 0xffffff;
                        if (mask == 0) {
                            ++p;
                            mask = 0x80;
                        }
                    }
                    s += a10;
                    dst += a5;
                    dstRowEnd += a5;
                } while (s < end);
            }
            LeaveCriticalSection(cs);
            return;
        }
        if (a11 == 0x20) {
            // 32-bpp straight copy
            uint8_t* end = a7 + ((a9 * a10) & ~3u);
            uint8_t* dst = (uint8_t*)(a2 + (((a4 * a5) >> 2) + a3) * 4);
            if (a7 < end) {
                uint32_t rowBytes = a8 * 4;
                uint32_t srcStep = a10 & ~3u;
                uint32_t dstStep = a5 & ~3u;
                do {
                    memcpy(dst, a7, rowBytes);
                    a7 += srcStep;
                    dst += dstStep;
                } while (a7 < end);
            }
        }
    }

    LeaveCriticalSection(cs);
}

// ---- FillBlocks -----------------------------------------------------------------------------

// @ 0x0088a950
void GlyphCache::FillBlocks(uint8_t* dst, uint32_t size, uint32_t stride, int format)
{
    EnterCriticalSection(mCS);
    uint8_t* p = dst;

    if (format == 3) {
        uint32_t n = (size + 3) >> 2;
        if ((int)n > 0) {
            uint32_t rows = n;
            do {
                if ((int)n > 0) {
                    uint32_t* q = (uint32_t*)(p + 8);
                    uint32_t k = n;
                    do {
                        q[-2] = 0;
                        q[-1] = 0;
                        q[0] = 0xffffffff;
                        q[1] = 0;
                        q += 4;
                    } while (--k != 0);
                }
                p += stride;
            } while (--rows != 0);
            LeaveCriticalSection(mCS);
            return;
        }
    } else if (format == 8) {
        if (size != 0) {
            uint32_t rows = size;
            do {
                memset(p, 0, size);
                p += stride;
            } while (--rows != 0);
            LeaveCriticalSection(mCS);
            return;
        }
    } else if (format == 0x20 && size != 0) {
        uint32_t k = size;
        uint32_t bytes = size * 4;
        do {
            memset(p, 0, bytes);
            p += stride;
        } while (--k != 0);
    }

    LeaveCriticalSection(mCS);
}

// ---- Remove ---------------------------------------------------------------------------------

// @ 0x0088ab80
bool GlyphCache::Remove(GlyphInfo* info)
{
    void* cs = mCS;
    EnterCriticalSection(cs);
    OnRemove(info);

    void** slot = mTable.mpBuckets;
    int* node = (int*)*slot;
    if (node == 0) {
        do {
            ++slot;
            node = (int*)*slot;
        } while (node == 0);
    }
    int* end = (int*)mTable.mpBuckets[mTable.mnBuckets];
    while (node != end) {
        if (node[2] == (int)info) {
            int* cur = node;
            node = (int*)node[7];
            void** curSlot = slot;
            if (node == 0) {
                do {
                    ++slot;
                    node = (int*)*slot;
                } while (node == 0);
            }
            HashIter it;
            it.mpNode = cur;
            it.mpSlot = curSlot;
            mTable.erase(it);
        } else {
            node = (int*)node[7];
            if (node == 0) {
                do {
                    ++slot;
                    node = (int*)*slot;
                } while (node == 0);
            }
        }
        end = (int*)mTable.mpBuckets[mTable.mnBuckets];
    }

    info->mTotal = 0;
    info->mA = 0;
    info->mB = 0;
    if (info->mCount != 0) {
        uint32_t* q = info->mOffsets;
        uint32_t i = 0;
        uint8_t n = info->mCount;
        do {
            info->mTotal += info->mValues[i];
            *q = 0;
            n = info->mCount;
            ++i;
            ++q;
        } while (i < n);
    }
    ++info->mRefs;

    LeaveCriticalSection(cs);
    return true;
}
