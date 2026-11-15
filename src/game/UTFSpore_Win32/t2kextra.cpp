// src/game/UTFSpore_Win32/t2kextra.cpp -- migrated from slice(s) s008c3120, s008c2540 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/t2kextra.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* tsi_AllocMem(void* mem, unsigned size);   // 0x008d1260
extern "C" void tsi_DeAllocMem(void* mem, void* p);        // 0x008d1440
extern "C" int util_EuclidianDistance(int x, int y);   // 0x008d17d0
extern "C" int util_FixDiv(int a, int b);              // 0x008d16d0
extern "C" int util_FixMul(int a, int b);              // 0x008d1590

// ---- items of slice s008c2540 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint8_t u8;
typedef uint32_t u32;
struct TVEffect {
    u8 isGrey;     // +0: 0 = source is a 1-bit bitmap
    u8 mode;       // +1
    u8 pad2[2];
    int dx;        // +4
    int dy;        // +8
    int r;         // +0xc
    int g;         // +0x10
    int b;         // +0x14
    int r2;        // +0x18
    int g2;        // +0x1c
    int b2;        // +0x20
};
extern "C" void* tsi_AllocMem(void* mem, unsigned size);   // 0x008d1260
extern "C" void tsi_DeAllocMem(void* mem, void* p);        // 0x008d1440
static inline u32 BitVal(const u8* row, int x, u32 on)
{
    return ((0x80 >> (x & 7)) & row[x >> 3]) ? on : 0;
}
typedef void* (*AllocCallback)(void* user, int size);
struct T2KMem {
    char pad0[0x64];
    void* m_cache;      // +0x64
    char pad68[0x34];
    int m_flag9c;       // +0x9c
};
struct T2KObj {
    char pad00[4];
    T2KMem* m_mem;      // +0x04
    char pad08[0x14];
    int m_flag1c;       // +0x1c
    void* m_allocUser;  // +0x20
    void* m_allocFn;    // +0x24
    char pad28[0x8];
    int m_owned;        // +0x30
    int m_allocated;    // +0x34
    char pad38[0x98];
    int m_fix0;         // +0xd0
    int m_fix1;         // +0xd4
    int m_fix2;         // +0xd8
    int m_fix3;         // +0xdc
    int m_light0;       // +0xe0
    char padE4[0x18];
    int m_light1;       // +0xfc
    char pad100[0xc];
    int m_width;        // +0x10c
    int m_height;       // +0x110
    int m_rowBytes;     // +0x114
    u8* m_src;          // +0x118
    u32* m_out;         // +0x11c
};
extern "C" int util_EuclidianDistance(int x, int y);   // 0x008d17d0
extern "C" int util_FixDiv(int a, int b);              // 0x008d16d0
extern "C" int util_FixMul(int a, int b);              // 0x008d1590
// ---- items of slice s008c2540 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_008c3120(int self);  // 0x008c3120 (stays in the slice: not this object's)

// @ 0x008c2c80
void T2K_CreateBorderedCharacter(T2KObj* t, TVEffect* fx)
{
    int g = fx->g;
    int r = fx->r;
    int r2 = fx->r2;
    u32 b2 = (u32)fx->b2;
    u8 isGrey = fx->isGrey;
    int b = fx->b;
    int width = t->m_width;
    int dy = fx->dy;
    u32 g2 = (u32)fx->g2;
    int dx = fx->dx;
    int rowBytes = t->m_rowBytes;
    u8* src = t->m_src;
    int dx2 = dx * 2;
    int height = t->m_height;
    int dy2 = dy * 2;
    int outW = width + dx2;
    int outH = dy2 + height;
    if (height == 0)
        outH = 0;

    if (t->m_fix0 != 0) {
        if (t->m_flag1c == 0) {
            int span = dx2 > dy2 ? dx2 : dy2;
            int dist = util_EuclidianDistance(t->m_fix2, t->m_fix3);
            int scale = util_FixDiv(span * 0x10000 + dist, dist);
            t->m_fix0 = util_FixMul(scale, t->m_fix0);
            t->m_fix1 = util_FixMul(scale, t->m_fix1);
            t->m_fix2 = util_FixMul(scale, t->m_fix2);
            t->m_fix3 = util_FixMul(scale, t->m_fix3);
        } else {
            t->m_fix2 += dx * 0x20000;
            t->m_fix0 += dx * 0x20000;
        }
    }

    t->m_light0 += dy * 0x40;
    t->m_light1 += dy * 0x40;
    t->m_rowBytes = outW * 4;
    t->m_height = outH;
    t->m_width = outW;

    int total = src == 0 ? 0 : outW * outH;
    t->m_allocated = 0;
    u32* out;
    if (t->m_allocFn == 0 ||
        (out = (u32*)((AllocCallback)t->m_allocFn)(t->m_allocUser, total * 4)) == 0) {
        out = (u32*)tsi_AllocMem(t->m_mem, total * 4);
        t->m_allocated = 1;
    }
    t->m_out = out;

    if (total != 0) {
        for (int i = 0; i < total; i++)
            out[i] = 0;

        u32* scan = out + outW * dy * 2;
        if (height > 0) {
            int rows = height;
            do {
                int x = 0;
                if (width > 0) {
                    do {
                        u32 v = isGrey ? src[x] : BitVal(src, x, 0x7e);
                        if (v != 0) {
                            u32 s = (v >> 5) + v * 2;
                            for (int i = dy2; i > 0; i--) {
                                if (*scan < s) *scan = s;
                                scan -= outW;
                            }
                            for (int i = dx2; i > 0; i--) {
                                if (*scan < s) *scan = s;
                                scan++;
                            }
                            for (int i = dy2; i > 0; i--) {
                                if (*scan < s) *scan = s;
                                scan += outW;
                            }
                            for (int i = dx2; i > 0; i--) {
                                if (*scan < s) *scan = s;
                                scan--;
                            }
                        }
                        x++;
                        scan++;
                    } while (x < width);
                }
                src += rowBytes;
                scan += outW - width;
                rows--;
            } while (rows != 0);
        }

        for (int i = 0; i < total; i++)
            out[i] = (out[i] << 24) | ((((u32)r2 << 8) | g2) << 8) | b2;

        u32* dest = out + outW * dy + dx;
        if (height > 0) {
            int rows = height;
            do {
                int x = 0;
                if (width > 0) {
                    do {
                        u32 v = isGrey ? src[x] : BitVal(src, x, 0x7e);
                        if (v != 0) {
                            int k = (v >> 5) + 1 + (int)v * 2;
                            u32 px = *dest;
                            unsigned a = (px >> 24) & 0xff;
                            a = a + (a >> 7);
                            *dest = ((((u32)(r - r2) * k) & 0xffffff00u) + (u32)r2 * 0x100) * 0x100 |
                                    ((((u32)(g - (int)g2) * k) & 0xffffff00u) + g2 * 0x100) |
                                    (((((0x100 - a) * (u32)k) >> 8) - 1 + a) * 0x1000000) |
                                    ((((u32)(b - (int)b2) * k) >> 8) + b2);
                        }
                        x++;
                        dest++;
                    } while (x < width);
                }
                src += rowBytes;
                dest += outW - width;
                rows--;
            } while (rows != 0);
        }
    }

    if (t->m_out != 0 && t->m_owned != 0) {
        T2KMem* mem = t->m_mem;
        if (t->m_out == (u32*)mem->m_cache)
            mem->m_flag9c = 1;
        else
            tsi_DeAllocMem(mem, t->m_out);
        t->m_out = 0;
    }
}

// @ 0x008c3570
void FUN_008c3570(int self)
{
	FUN_008c3120(self);
}
