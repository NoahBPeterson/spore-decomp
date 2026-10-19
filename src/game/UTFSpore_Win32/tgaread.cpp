// src/game/UTFSpore_Win32/tgaread.cpp -- migrated from slice(s) s0084ebe0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/tgaread.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#ifndef NULL
#define NULL 0
#endif

// unnamed retail callees and globals (address in the comment)
extern "C" void*        __stdcall galloc(unsigned int size);                       // 0x0087d4a0
extern "C" unsigned char __stdcall gfree(void* p);                                 // 0x0087d4c0
extern "C" unsigned int __stdcall gread(void* h, void* buf, unsigned int n);       // 0x0087d4e0
extern "C" int          __stdcall gseek(void* h, long off, int whence);            // 0x0087d540
extern "C" unsigned long long __stdcall glen(void* h);                             // 0x0087d560
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);
extern "C" char* __cdecl strcpy(char* dst, const char* src);                        // 0x011e0744
#pragma function(memset)

// ---- items of slice s0084ebe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;
typedef signed short   s16;
extern "C" void*        __stdcall galloc(unsigned int size);                       // 0x0087d4a0
extern "C" unsigned char __stdcall gfree(void* p);                                 // 0x0087d4c0
extern "C" unsigned int __stdcall gread(void* h, void* buf, unsigned int n);       // 0x0087d4e0
extern "C" int          __stdcall gseek(void* h, long off, int whence);            // 0x0087d540
extern "C" unsigned long long __stdcall glen(void* h);                             // 0x0087d560
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);
extern "C" char* __cdecl strcpy(char* dst, const char* src);                        // 0x011e0744
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

// @ 0x0084f1c0
u8* TGA_about(void)
{
    u8* d = (u8*)galloc(0x100);
    if (d != NULL) {
        memset(d, 0, 0x100);
        *(u32*)(d + 0x00) = 0x2e544741;                 // "TGA."
        *(u32*)(d + 0x04) = 0x100;
        *(u32*)(d + 0x08) = 0x159;
        *(u32*)(d + 0x14) = 0;
        *(u32*)(d + 0x18) = 100;
        *(u32*)(d + 0x1c) = 0x54504943;                 // "CIPT"
        *(u32*)(d + 0x0c) = (*(u32*)(d + 0x0c) & 0xffff93d7) | 0x93d7;
        strcpy((char*)(d + 0x3c), ".tga");
        strcpy((char*)(d + 0x44), ".vda");
        strcpy((char*)(d + 0x4c), ".icb");
        strcpy((char*)(d + 0x54), ".vst");
        strcpy((char*)(d + 0x7c), "FrANK G. Barchard");
        strcpy((char*)(d + 0x9c), "1.38");
        *(u32*)(d + 0xa4) = 0x414754;
        strcpy((char*)(d + 0xac), "Targa");
        strcpy((char*)(d + 0xbc), "Targa");
    }
    return d;
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

// @ 0x0084f440
void* __stdcall TGA_info(void* handle, int a2)
{
    u8  palbuf[0x400];
    TgaHeader h;
    u32* d;
    unsigned long long len;
    u32 alpha_depth;
    u32 seekres;
    u32 cmap_count;
    int x_org, y_org;
    int i;

    gseek(*(void**)((u8*)handle + 0x10), 0, 0);              // handle->io
    len = glen(*(void**)((u8*)handle + 0x10));
    if (gread(*(void**)((u8*)handle + 0x10), &h, 0x12) == 0)
        return NULL;

    x_org = (int)h.x_origin;
    y_org = (int)h.y_origin;
    if ((h.image_desc & 0x20) == 0)
        y_org = -y_org;
    if ((h.image_desc & 0x10) != 0)
        x_org = -x_org;

    alpha_depth = (u32)h.pixel_depth - 0x18;
    if (h.pixel_depth == 0xf || h.pixel_depth == 0x10 ||
        (h.pixel_depth == 8 && h.cmap_type != 0 &&
         (h.cmap_depth == 0xf || h.cmap_depth == 0x10))) {
        alpha_depth = ((h.image_desc & 0xf) == 1);
    }
    if ((int)alpha_depth < 1)
        alpha_depth = 0;
    else if ((int)alpha_depth > 8)
        alpha_depth = 8;

    seekres = (u32)gseek(*(void**)((u8*)handle + 0x10), h.id_length + 0x12, 0) & 0xff;

    cmap_count = h.cmap_length;
    if ((h.image_type & 7) != 1) {
        cmap_count = 0;
        if ((h.image_type & 7) == 3)
            cmap_count = 0x100;
    }

    d = (u32*)galloc(0x2a70);
    if (d != NULL) {
        memset(d, 0, 0x2a70);
        d[5] = h.height;
        d[4] = h.width;
        d[0x10e] = alpha_depth;
        d[0x10d] = (u32)len;
        d[0x114] = (u32)x_org;
        d[0] = 0x2e544741;
        d[1] = 0x2a70;
        d[2] = 0x159;
        d[3] = 0;
        d[0x10a] = 0;
        d[0x10b] = (h.image_type >> 3) & 1;
        d[0x10c] = 100;
        d[0x10f] = 8;
        d[0x110] = 8;
        d[0x111] = 8;
        d[0x112] = 0;
        d[0x113] = 0;
        d[0x115] = (u32)y_org;
        d[0x116] = 0;
        *(u8*)((u8*)d + 0x45c) = 0;

        if (h.pixel_depth < 0xf) {
            int pd = h.pixel_depth;
            if (pd == 0)
                pd = 8;
            if (cmap_count == 0)
                cmap_count = 1u << (pd & 0x1f);
            if ((int)cmap_count > 0x100)
                cmap_count = 0x100;
            d[6] = 8;
            d[7] = pd;
            d[9] = cmap_count;
            d[8] = h.cmap_first;
            if (h.cmap_type == 0) {
                u8* p = (u8*)d + 0x2a;
                for (i = 0; i < 0x100; i++) {
                    p[0] = (u8)i; p[-1] = (u8)i; p[-2] = (u8)i; p[1] = 0xff; p += 4;
                }
            }
            else {
                switch (h.cmap_depth) {
                case 0xf:
                case 0x10: {
                    u8* t;
                    d[0x111] = 5; d[0x110] = 5; d[0x10f] = 5; d[0x10e] = 0;
                    seekres = gread(*(void**)((u8*)handle + 0x10), palbuf, cmap_count * 2);
                    t = (u8*)d + h.cmap_first * 4 + 0x28;
                    for (i = 0; i < (int)h.cmap_length; i++) {
                        u16 v = ((u16*)palbuf)[i];
                        u32 g, r, b, t1, t2, t3;
                        if (alpha_depth == 0) t[3] = 0xff;
                        else t[3] = (u8)((s16)v >> 15);
                        g = (v >> 10 & 0x1f) * 0xff;
                        t1 = g / 0x1f;
                        r = (v >> 5 & 0x1f) * 0xff;
                        t[2] = (u8)((((g - t1) >> 1) + t1) >> 4);
                        t2 = r / 0x1f;
                        b = (v & 0x1f) * 0xff;
                        t[1] = (u8)((((r - t2) >> 1) + t2) >> 4);
                        t3 = b / 0x1f;
                        t[0] = (u8)((((b - t3) >> 1) + t3) >> 4);
                        t += 4;
                    }
                    break;
                }
                case 0x18: {
                    u8* s = palbuf;
                    u8* t;
                    d[0x10e] = 0;
                    seekres = gread(*(void**)((u8*)handle + 0x10), palbuf, cmap_count * 3);
                    t = (u8*)d + h.cmap_first * 4 + 0x28;
                    for (i = 0; i < (int)h.cmap_length; i++) {
                        t[0] = s[0]; t[1] = s[1]; t[2] = s[2]; t[3] = 0xff;
                        s += 3; t += 4;
                    }
                    break;
                }
                case 0x20: {
                    u8* s = palbuf;
                    u8* t;
                    d[0x10e] = 8;
                    seekres = gread(*(void**)((u8*)handle + 0x10), palbuf, cmap_count * 4);
                    t = (u8*)d + h.cmap_first * 4 + 0x28;
                    for (i = 0; i < (int)h.cmap_length; i++) {
                        t[0] = s[0]; t[1] = s[1]; t[2] = s[2]; t[3] = s[3];
                        s += 4; t += 4;
                    }
                    break;
                }
                }
            }
        }
        else {
            int pd = h.pixel_depth;
            if (pd == 0x10)
                pd = 0xf;
            d[6] = 0x20;
            d[7] = pd;
            d[9] = 0;
            if (pd < 0x11) { d[0x111] = 5; d[0x110] = 5; d[0x10f] = 5; }
            if (pd < 0x20) { d[0x10e] = 0; }
        }

        if (seekres != 0)
            return d;
        gfree(d);
    }
    return NULL;
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
