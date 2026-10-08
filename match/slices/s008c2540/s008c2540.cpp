// Slice s008c2540 -- T2K (Type 2000 font scaler) "TV effects" bitmap post-processing (0x008c2540,
// 1852 bytes): expands the glyph's 1-bit or 8-bit coverage bitmap into a 32-bit ARGB buffer and
// optionally adds an outline / drop shadow / glow around it (modes 1..5).
//
// Modes (effect->mode): 0 plain fill, 1/2/3 outline grown by (dx,dy) on every side,
// 4/5 shadow offset by (dx,dy) (4 = bottom-right, 5 = top-left shifted). Names are Claude-coined; the
// function name comes from the PDB candidate file name T2K_TV_Effects. The T2K struct is accessed
// by raw offsets (layout not recovered, same approach as slice s008c0760).
//
// T2K_CastRaysOfLightAndDarkness (0x008c21c0) is a same-TU static in the original (effect struct
// passed in EAX); its body is not part of this slice, so a stand-in is defined here only so that
// the call site gets cl's register convention.
// Module flags: /O2 /MD /Gy /TP.
#include "types.h"

typedef uint8_t u8;
typedef uint32_t u32;

#define I32(p, o) (*(int*)((char*)(p) + (o)))
#define U32(p, o) (*(unsigned*)((char*)(p) + (o)))
#define PTR(p, o) (*(char**)((char*)(p) + (o)))

struct tsiMemObject;

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

extern "C" {
void* tsi_AllocMem(void* mem, unsigned size);   // 0x008d1260
void tsi_DeAllocMem(void* mem, void* p);        // 0x008d1440
}

// Bit x of a 1-bit-per-pixel row (MSB first): `on` when set, else 0.
static inline u32 BitVal(const u8* row, int x, u32 on)
{
    return ((0x80 >> (x & 7)) & row[x >> 3]) ? on : 0;
}

typedef void* (*AllocCallback)(void* user, int size);

static __declspec(noinline) void T2K_CastRaysOfLightAndDarkness(TVEffect* fx, u32* buf, int w, int h,
                                                                int rowW, int total)
{
    // real body at 0x008c21c0 (not part of this slice)
    if (fx->mode == 1) buf[0] = (u32)w + h + rowW + total;
}

void T2K_TV_Effects(char* t, TVEffect* fx)
{
    char mode = fx->mode;
    int dx = fx->dx;
    int b = fx->b;
    int dy = fx->dy;
    int g = fx->g;
    int g2 = fx->g2;
    int r2 = fx->r2;
    int r = fx->r;
    int b2 = fx->b2;
    int total;
    u32* out;
    char* src = PTR(t, 0x118);
    int srcRow = I32(t, 0x114);
    u32* p = 0;
    int isGrey = fx->isGrey != 0;
    int height = I32(t, 0x110);
    int dy2 = dy + dy;
    int dx2 = dx + dx;
    int width = I32(t, 0x10c);
    int outW = width;
    int outH = height;

    if (mode != 0) {
        if (mode == 4 || mode == 5) {
            outW = dx + width;
            outH = dy + height;
        } else {
            I32(t, 0xe0) += dy * 0x40;
            I32(t, 0xfc) += dy * 0x40;
            outW = dx2 + width;
            outH = dy2 + height;
        }
    }
    if (height == 0)
        outH = 0;
    I32(t, 0x114) = outW;
    I32(t, 0x110) = outH;
    I32(t, 0x10c) = outW;
    if (src == 0)
        total = 0;
    else
        total = outW * outH;
    I32(t, 0x34) = 0;
    if (!PTR(t, 0x24) || (out = (u32*)((AllocCallback)PTR(t, 0x24))(PTR(t, 0x20), total * 4)) == 0) {
        out = (u32*)tsi_AllocMem(PTR(t, 4), total * 4);
        I32(t, 0x34) = 1;
    }
    PTR(t, 0x11c) = (char*)out;
    if (total == 0)
        goto done;
    {
        u32* z = out;
        int n;
        if (total > 0) {
            for (n = total; n != 0; n--)
                *z++ = 0;
        }
    }
    if (mode == 0) {
        u32 color = (((u32)r << 8 | (u32)g) << 8) | (u32)b;
        if (isGrey) {
            if (total > 0) {
                int i = 0;
                do {
                    u32 v = ((u8*)src)[i];
                    out[i] = ((v * 0x40 + (v & 0xffffffe0u)) * 0x80000u) | color;
                    i++;
                } while (i < total);
            }
        } else {
            int o = 0;
            if (height > 0) {
                int bit = 0;
                int rows = height;
                do {
                    int x = 0;
                    int pos = bit;
                    if (width > 0) {
                        do {
                            out[o] = (BitVal((u8*)src, pos, 0xff) << 24) | color;
                            x++;
                            o++;
                            pos++;
                        } while (x < width);
                    }
                    bit += srcRow * 8;
                    rows--;
                } while (rows != 0);
            }
        }
        goto done;
    }
    {
        int rows = height;
        if (mode == 4 || mode == 5) {
            p = out + outW * dy;
            if (mode == 5)
                p += dx;
            if (height > 0) {
                do {
                    int x = 0;
                    if (width > 0) {
                        do {
                            u32 v;
                            if (isGrey)
                                v = ((u8*)src)[x];
                            else
                                v = BitVal((u8*)src, x, 0x7e);
                            *p = v;
                            x++;
                            p++;
                        } while (x < width);
                    }
                    src += srcRow;
                    p += outW - width;
                    rows--;
                } while (rows != 0);
            }
          after_shadow:
            if (mode != 3) goto not3;
          fill_shadow:
            {
                u32 color = ((((u32)r2 << 8) | (u32)g2) << 8) | (u32)b2;
                int i = 0;
                if (total > 0) {
                    do {
                        u32 v = out[i];
                        if (v != 0)
                            out[i] = ((v * 0x40 + (v & 0xffffffe0u)) * 0x80000u) | color;
                        i++;
                    } while (i < total);
                }
            }
        } else {
            if (mode == 1 || mode == 2 || mode == 3) {
                p = out + outW * dy * 2;
                if (height > 0) {
                    do {
                        int x = 0;
                        if (width > 0) {
                            do {
                                u32 v;
                                if (isGrey)
                                    v = ((u8*)src)[x];
                                else
                                    v = BitVal((u8*)src, x, 0x7e);
                                if (v != 0) {
                                    int k;
                                    for (k = dy * 2; 0 < k; k--) {
                                        if (v > *p) *p = v;
                                        p -= outW;
                                    }
                                    for (k = dx * 2; 0 < k; k--) {
                                        if (v > *p) *p = v;
                                        p++;
                                    }
                                    for (k = dy * 2; 0 < k; k--) {
                                        if (v > *p) *p = v;
                                        p += outW;
                                    }
                                    for (k = dx * 2; 0 < k; k--) {
                                        if (v > *p) *p = v;
                                        p--;
                                    }
                                }
                                x++;
                                p++;
                            } while (x < width);
                        }
                        src += srcRow;
                        p += outW - width;
                        rows--;
                    } while (rows != 0);
                }
                if (mode == 1 || mode == 2) {
                    p = out + outW * dy + dx;
                    src = PTR(t, 0x118);
                    if (height > 0) {
                        rows = height;
                        do {
                            int x = 0;
                            if (width > 0) {
                                do {
                                    u8 v;
                                    if (isGrey)
                                        v = ((u8*)src)[x];
                                    else
                                        v = BitVal((u8*)src, x, 0x7e);
                                    if (v == 0x7e)
                                        *p = 0x7f;
                                    x++;
                                    p++;
                                } while (x < width);
                            }
                            src += srcRow;
                            p += outW - width;
                            rows--;
                        } while (rows != 0);
                    }
                }
                goto after_shadow;
            }
          not3:
            if (mode == 4 || mode == 5) goto fill_shadow;
            if (mode == 1 || mode == 2)
                T2K_CastRaysOfLightAndDarkness(fx, out, outW, outH, outW, total);
        }
    }
    if (mode == 1 || mode == 2 || mode == 3 || mode == 4 || mode == 5) {
        char* s = PTR(t, 0x118);
        if (mode == 1 || mode == 2 || mode == 3)
            p = out + outW * dy + dx;
        else if (mode == 4)
            p = out + dx;
        else if (mode == 5)
            p = out;
        if (height > 0) {
            int rows = height;
            do {
                int x = 0;
                if (width > 0) {
                    do {
                        u32 v;
                        if (isGrey)
                            v = ((u8*)s)[x];
                        else
                            v = BitVal((u8*)s, x, 0x7e);
                        if (v != 0) {
                            u32 px = *p;
                            u32 pb = px & 0xff;
                            u32 pg = (px >> 8) & 0xff;
                            u32 pr = (px >> 16) & 0xff;
                            u32 pa = px >> 24;
                            int k = (int)(v >> 5) + 1 + (int)v * 2;
                            pa = pa + (pa >> 7);
                            *p = (((((r - pr) * k) & 0xffffff00u) + pr * 0x100) * 0x100) |
                                 ((((g - pg) * k) & 0xffffff00u) + pg * 0x100) |
                                 (((((0x100 - pa) * k) >> 8) - 1 + pa) * 0x1000000) |
                                 ((((b - pb) * k) >> 8) + pb);
                        }
                        x++;
                        p++;
                    } while (x < width);
                }
                s += srcRow;
                p += outW - width;
                rows--;
            } while (rows != 0);
        }
    }
done:
    {
        char* base = PTR(t, 0x118);
        if (base != 0 && I32(t, 0x30) != 0) {
            char* mem = PTR(t, 4);
            if (base == PTR(mem, 0x64))
                I32(mem, 0x9c) = 1;
            else
                tsi_DeAllocMem(mem, base);
            PTR(t, 0x118) = 0;
            I32(t, 0x30) = 0;
        }
        if (PTR(t, 0x11c) != 0)
            I32(t, 0x114) = I32(t, 0x10c) * 4;
    }
}
