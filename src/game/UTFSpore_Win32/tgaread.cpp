// src/game/UTFSpore_Win32/tgaread.cpp -- migrated from slice(s) s0084ebe0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/tgaread.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void*        __stdcall galloc(unsigned int size);                       // 0x0087d4a0
extern "C" unsigned char __stdcall gfree(void* p);                                 // 0x0087d4c0
extern "C" unsigned int __stdcall gread(void* h, void* buf, unsigned int n);       // 0x0087d4e0
extern "C" int          __stdcall gseek(void* h, long off, int whence);            // 0x0087d540
extern "C" unsigned long long __stdcall glen(void* h);                             // 0x0087d560
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);
#pragma function(memset)

// ---- items of slice s0084ebe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;
extern "C" void*        __stdcall galloc(unsigned int size);                       // 0x0087d4a0
extern "C" unsigned char __stdcall gfree(void* p);                                 // 0x0087d4c0
extern "C" unsigned int __stdcall gread(void* h, void* buf, unsigned int n);       // 0x0087d4e0
extern "C" int          __stdcall gseek(void* h, long off, int whence);            // 0x0087d540
extern "C" unsigned long long __stdcall glen(void* h);                             // 0x0087d560
struct TgaHeader {
    u8  id_length;      // +0x00
    u8  cmap_type;      // +0x01
    u8  image_type;     // +0x02
    u16 cmap_first;     // +0x03
    u16 cmap_length;    // +0x05
    u8  cmap_depth;     // +0x07
    u16 x_origin;       // +0x08
    u16 y_origin;       // +0x0a
    u16 width;          // +0x0c
    u16 height;         // +0x0e
    u8  pixel_depth;    // +0x10
    u8  image_desc;     // +0x11
};
// ---- items of slice s0084ebe0 end

// @ 0x0084ebe0
u32 TGAreadline(void* gimex, u8* dest, void* io, u8* buf)
{
    u32* g = (u32*)gimex;
    int trans_depth = (int)g[0x438 / 4];
    int width       = (int)g[0x10 / 4];
    int pixel_depth = (int)g[0x1c / 4];
    int done = 0;
    u8* pbVar4 = buf;
    u8* pbVar8 = buf;
    u32 uVar5 = 0;

    if (g[0x42c / 4] == 0) {
        uVar5 = gread(io, buf, (unsigned)(((pixel_depth + 7U & 0xfffffff8U) * width) >> 3));
        switch (pixel_depth) {
        case 8:
            if (width > 0) {
                int n = width;
                while (n-- != 0) { *dest = *buf; dest++; buf++; }
            }
            break;
        case 0xf:
        case 0x10:
            if (width > 0) {
                int n = width;
                buf++;
                do {
                    dest[3] = (trans_depth == 0) ? 0xff : (u8)((s8)buf[0] >> 7);
                    dest[2] = (u8)(((buf[0] >> 2 & 0x1f) * 0xff) / 0x1f);
                    dest[1] = (u8)((((buf[0] & 3) * 8 | (u32)(buf[-1] >> 5)) * 0xff) / 0x1f);
                    dest[0] = (u8)(((buf[-1] & 0x1f) * 0xff) / 0x1f);
                    dest += 4; buf += 2;
                } while (--n != 0);
            }
            break;
        case 0x18:
            if (width > 0) {
                int n = width;
                buf++;
                do {
                    dest[3] = 0xff;
                    dest[2] = buf[1];
                    dest[1] = buf[0];
                    dest[0] = buf[-1];
                    dest += 4; buf += 3;
                } while (--n != 0);
            }
            break;
        case 0x20:
            if (width > 0) {
                int n = width;
                buf += 2;
                do {
                    dest[3] = buf[1];
                    dest[2] = buf[0];
                    dest[1] = buf[-1];
                    dest[0] = buf[-2];
                    dest += 4; buf += 4;
                } while (--n != 0);
            }
            break;
        }
        return uVar5;
    }

    do {
        uVar5 = gread(io, pbVar8, 1);
        u8 bVar1 = *pbVar8;
        pbVar8 = pbVar4;
        if ((s8)bVar1 < 0) {
            int n = (bVar1 & 0x7f) + 1;
            done += n;
            switch (pixel_depth) {
            case 8:
                gread(io, pbVar4, 1);
                while (n-- != 0) { *dest = *pbVar4; dest++; }
                break;
            case 0xf:
            case 0x10:
                gread(io, pbVar4, 2);
                while (n-- != 0) {
                    dest[3] = (trans_depth == 0) ? 0xff : (u8)((s8)pbVar4[1] >> 7);
                    dest[2] = (u8)(((pbVar4[1] >> 2 & 0x1f) * 0xff) / 0x1f);
                    dest[1] = (u8)((((pbVar4[1] & 3) * 8 | (u32)(*pbVar4 >> 5)) * 0xff) / 0x1f);
                    dest[0] = (u8)(((*pbVar4 & 0x1f) * 0xff) / 0x1f);
                    dest += 4;
                }
                break;
            case 0x18:
                gread(io, pbVar4, 3);
                while (n-- != 0) {
                    dest[3] = 0xff; dest[2] = pbVar4[2]; dest[1] = pbVar4[1]; dest[0] = pbVar4[0];
                    dest += 4;
                }
                break;
            case 0x20:
                gread(io, pbVar4, 4);
                while (n-- != 0) {
                    dest[3] = pbVar4[3]; dest[2] = pbVar4[2]; dest[1] = pbVar4[1]; dest[0] = pbVar4[0];
                    dest += 4;
                }
                break;
            }
        }
        else {
            int n = (bVar1 & 0x7f) + 1;
            done += n;
            gread(io, pbVar4, (unsigned)(((pixel_depth + 7U & 0xfffffff8U) * n) >> 3));
            switch (pixel_depth) {
            case 8:
                while (n-- != 0) { *dest = *pbVar8; dest++; pbVar8++; }
                break;
            case 0xf:
            case 0x10:
                while (n-- != 0) {
                    dest[3] = (trans_depth == 0) ? 0xff : (u8)((s8)pbVar8[1] >> 7);
                    dest[2] = (u8)(((pbVar8[1] >> 2 & 0x1f) * 0xff) / 0x1f);
                    dest[1] = (u8)((((pbVar8[1] & 3) * 8 | (u32)(*pbVar8 >> 5)) * 0xff) / 0x1f);
                    dest[0] = (u8)(((*pbVar8 & 0x1f) * 0xff) / 0x1f);
                    dest += 4; pbVar8 += 2;
                }
                break;
            case 0x18:
                while (n-- != 0) {
                    dest[3] = 0xff; dest[2] = pbVar8[2]; dest[1] = pbVar8[1]; dest[0] = pbVar8[0];
                    dest += 4; pbVar8 += 3;
                }
                break;
            case 0x20:
                while (n-- != 0) {
                    dest[3] = pbVar8[3]; dest[2] = pbVar8[2]; dest[1] = pbVar8[1]; dest[0] = pbVar8[0];
                    dest += 4; pbVar8 += 4;
                }
                break;
            }
        }
    } while (done < width);
    return uVar5;
}

// @ 0x0084f170
void TGAflipline(u8* ptr, int bpp, int count)
{
    int i;
    i = count >> 1;
    if (bpp == 0x20) {
        u32* a = (u32*)ptr;
        u32* b = (u32*)(ptr + count * 4 - 4);
        if (i > 0) {
            do {
                u32 t = *a;
                *a = *b;
                *b = t;
                a++; b--; i--;
            } while (i != 0);
        }
    }
    else {
        u8* a = ptr;
        u8* b = ptr + count - 1;
        if (i > 0) {
            do {
                u8 t = *a;
                *a = *b;
                *b = t;
                a++; b--; i--;
            } while (i != 0);
        }
    }
}

// @ 0x0084f300
int __stdcall TGA_is(void* io)
{
    TgaHeader h;
    u32 r;

    gseek(io, 0, 0);
    glen(io);
    r = 0;
    if (gread(io, &h, 0x12) != 0) {
        if (h.cmap_type <= 1) {
            if ((h.image_type >= 1 && h.image_type <= 3) ||
                (u32)(h.image_type - 9) <= 2) {
                if (h.pixel_depth == 8 || h.pixel_depth == 0xf || h.pixel_depth == 0x10 ||
                    h.pixel_depth == 0x18 || h.pixel_depth == 0x20) {
                    r = 0x3c;
                    if ((u32)(h.width - 1) <= 0xfff) {
                        if ((u32)(h.height - 1) <= 0x7ff) {
                            if (h.cmap_first <= 0xff) {
                                if (h.cmap_length <= 0x100) {
                                    if (h.cmap_depth <= 0x20) {
                                        if ((u32)(h.x_origin + 0x800) <= 0x1800) {
                                            if ((u32)(h.y_origin + 0x400) <= 0xc00) {
                                                r = 100;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return (int)r;
}

// @ 0x0084f3f0
int __stdcall TGA_open(void** out, void* io, int a3, int a4)
{
    int* h = (int*)galloc(0x18);
    if (h != 0) {
        h[3] = 0;
        h[5] = 0;
        h[2] = 1;
        h[0] = 0x2e544741;
        h[1] = 0x18;
        h[4] = (int)io;
        *out = h;
        return 1;
    }
    return 0;
}

// @ 0x0084f900
u32 __stdcall TGA_read(void* handle, void* gimex, u8* pixels, int stride)
{
    TgaHeader h;
    u32* g = (u32*)gimex;
    unsigned char* row;
    u32 res;
    int i;
    int width, height, bit_depth;
    int rowstep;

    gseek(*(void**)((u8*)handle + 0x10), 0, 0);
    if (gread(*(void**)((u8*)handle + 0x10), &h, 0x12) == 0)
        return 0;

    width = (int)g[0x10 / 4];
    height = (int)g[0x14 / 4];
    bit_depth = (int)g[0x1c / 4];

    res = (u32)gseek(*(void**)((u8*)handle + 0x10),
                     h.id_length + 0x12 +
                     (h.cmap_type != 0 ? (int)((h.cmap_depth + 7) >> 3) * (int)h.cmap_length : 0),
                     0) & 0xff;

    if ((h.image_desc & 0x20) != 0) {
        rowstep = stride;
    }
    else {
        rowstep = (height - 1) * stride;
        stride = -stride;
    }

    row = (u8*)galloc((u32)((((bit_depth + 7) & 0xfffffff8) * width) >> 3));
    if (row != 0) {
        for (i = 0; i < height; i++) {
            if (res == 0)
                break;
            res = TGAreadline(gimex, pixels + rowstep, *(void**)((u8*)handle + 0x10), row);
            if ((h.image_desc & 0x10) != 0)
                TGAflipline(pixels + rowstep, (int)g[0x18 / 4], width);
            rowstep += stride;
        }
        gfree(row);
    }
    return res;
}
