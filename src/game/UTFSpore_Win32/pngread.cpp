// src/game/UTFSpore_Win32/pngread.cpp -- migrated from slice(s) s0084dcd0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/pngread.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void*        __stdcall galloc(unsigned int size);                        // 0x0087d4a0
extern "C" unsigned int __stdcall gfree(void* p);                                   // 0x0087d4c0
extern "C" unsigned int __stdcall gread(void* h, void* buf, unsigned int n);        // 0x0087d4e0
extern "C" int          __stdcall gseek(void* h, long off, int whence);             // 0x0087d540
extern "C" void*        __cdecl memset(void* dst, int v, unsigned int n);           // 0x011e073e
extern "C" char*        __cdecl strcpy(char* dst, const char* src);                 // 0x011e0744
#include <setjmp.h>
#pragma function(memset)

// ---- items of slice s0084dcd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char png_byte;
typedef unsigned short png_uint_16;
typedef unsigned int png_uint_32;
typedef unsigned int png_size_t;
typedef unsigned char* png_bytep;
typedef void* png_voidp;
struct png_struct_def;
typedef png_struct_def* png_structp;
struct png_info_def;
typedef png_info_def* png_infop;
struct png_text_struct;
typedef png_text_struct png_text;
struct png_struct_def { jmp_buf jmpbuf; };
struct png_text_struct {
    int          compression;   // +0x00
    char*        key;           // +0x04
    char*        text;          // +0x08
    png_size_t   text_length;   // +0x0c
};
struct png_info_def {
    png_uint_32 width;             // +0x00
    png_uint_32 height;            // +0x04
    png_uint_32 valid;             // +0x08
    png_uint_32 rowbytes;          // +0x0c
    png_byte*   palette;           // +0x10
    png_uint_16 num_palette;       // +0x14
    png_uint_16 num_trans;         // +0x16
    png_byte    bit_depth;         // +0x18
    png_byte    color_type;        // +0x19
    png_byte    compression_type;  // +0x1a
    png_byte    filter_type;       // +0x1b
    png_byte    interlace_type;    // +0x1c
    png_byte    channels;          // +0x1d
    png_byte    pixel_depth;       // +0x1e
    png_byte    spare_byte;        // +0x1f
    png_byte    signature[8];      // +0x20
    png_byte    pad_28[0x30 - 0x28];
    int         num_text;          // +0x30
    int         max_text;          // +0x34
    png_text*   text;              // +0x38
};
struct png_color_16 { png_byte index; png_uint_16 red, green, blue, gray; };
struct GimexInfo {
    int           magic;          // +0x0000  'GNP' = 0x00504e47
    int           size_;          // +0x0004  0x2a70
    int           type_;          // +0x0008  0x159
    int           field_c;        // +0x000c
    int           width;          // +0x0010
    int           height;         // +0x0014
    int           format;         // +0x0018
    int           bit_depth;      // +0x001c
    int           field_20;       // +0x0020
    int           num_colors;     // +0x0024
    unsigned char palette[0x400]; // +0x0028 .. 0x0427  (BGRA)
    int           field_428;      // +0x0428
    int           field_42c;      // +0x042c
    int           field_430;      // +0x0430
    int           field_434;      // +0x0434
    int           trans_depth;    // +0x0438
    int           field_43c;      // +0x043c
    int           field_440;      // +0x0440
    int           field_444;      // +0x0444
    int           field_448;      // +0x0448
    int           field_44c;      // +0x044c
    int           field_450;      // +0x0450
    int           field_454;      // +0x0454
    int           field_458;      // +0x0458
    unsigned char field_45c;      // +0x045c
    unsigned char pad_45d[0x65c - 0x45d];
    char          comment[0x400]; // +0x065c
    unsigned char pad_a5c[0x2a5c - 0xa5c];
    float         dpi;            // +0x2a5c
};
struct PngAboutDesc {
    int           magic;          // +0x0000 0x504e47
    int           size_;          // +0x0004 0x100
    int           type_;          // +0x0008 0x159
    int           flags;          // +0x000c
    int           field_10;       // +0x0010
    int           field_14;       // +0x0014 0
    int           field_18;       // +0x0018 0x64
    int           field_1c;       // +0x001c 0x504e47
    unsigned char pad_20[0x3c - 0x20];
    char          ext[5];         // +0x003c ".png"
    unsigned char pad_41[0x7c - 0x41];
    char          author[10];     // +0x007c "Kaz Okuda"
    unsigned char pad_86[0x9c - 0x86];
    char          version[5];     // +0x009c "1.10"
    unsigned char pad_a1[0xa4 - 0xa1];
    int           field_a4;       // +0x00a4 0x474e50
    int           field_a8;       // +0x00a8
    int           field_ac;       // +0x00ac 0x474e50
    unsigned char pad_b0[0xbc - 0xb0];
    char          desc[26];       // +0x00bc "Portable Network Graphics"
};
struct PngPair {
    png_structp png;   // +0
    png_infop   info;  // +4
};
struct PngHandle {
    int           magic;          // +0x00
    int           size_;          // +0x04
    int           ok;             // +0x08
    int           used;           // +0x0c
    png_voidp     io;             // +0x10
    PngPair*      pair;           // +0x14
};
extern "C" void*        __stdcall galloc(unsigned int size);                        // 0x0087d4a0
extern "C" unsigned int __stdcall gfree(void* p);                                   // 0x0087d4c0
extern "C" unsigned int __stdcall gread(void* h, void* buf, unsigned int n);        // 0x0087d4e0
extern "C" int          __stdcall gseek(void* h, long off, int whence);             // 0x0087d540
extern "C" void*        __cdecl memset(void* dst, int v, unsigned int n);           // 0x011e073e
extern "C" char*        __cdecl strcpy(char* dst, const char* src);                 // 0x011e0744
typedef void  (__cdecl *png_error_ptr)(png_structp, const char*);
typedef void* (__cdecl *png_malloc_ptr)(png_structp, png_uint_32);
typedef void  (__cdecl *png_free_ptr)(png_structp, void*);
typedef void  (__cdecl *png_rw_ptr)(png_structp, png_bytep, png_size_t);
extern "C" png_structp __cdecl png_create_read_struct_2(const char*, png_voidp, png_error_ptr,
                                                        png_error_ptr, png_voidp, png_malloc_ptr,
                                                        png_free_ptr);                 // 0x0086b500
extern "C" png_infop   __cdecl png_create_info_struct(png_structp);                    // 0x0086af20
extern "C" void        __cdecl png_set_read_fn(png_structp, png_voidp, png_rw_ptr);    // 0x0086d910
extern "C" void        __cdecl png_read_info(png_structp, png_infop);                  // 0x0086b750
extern "C" void        __cdecl png_read_image(png_structp, png_bytep*);                // 0x0086c240
extern "C" void        __cdecl png_read_update_info(png_structp, png_infop);           // 0x0086bd40
extern "C" void        __cdecl png_destroy_read_struct(png_structp*, png_infop*, png_infop*);// 0x0086c540
extern "C" void        __cdecl png_set_strip_16(png_structp);                          // 0x0086d970
extern "C" void        __cdecl png_set_gray_to_rgb(png_structp);                       // 0x0086d980
extern "C" int         __cdecl png_check_sig(png_bytep, int);                          // 0x0086a9b0
extern "C" void        __cdecl png_set_packing(png_structp);                           // 0x00876e90
extern "C" int         __cdecl png_get_text(png_structp, png_infop, png_text**, int*); // 0x0086b430
extern "C" int         __cdecl png_get_tRNS(png_structp, png_infop, png_bytep*, int*,
                                            png_color_16*);                            // 0x0086b480
extern "C" png_uint_32 __cdecl png_get_x_pixels_per_meter(png_structp, png_infop);     // 0x0086b400
extern "C" void __cdecl PNGREAD_read_data(png_structp, png_bytep, png_size_t);         // 0x0084dc90
void* __cdecl PNGREAD_malloc(png_structp, png_uint_32);                                // 0x0084e790
void  __cdecl PNGREAD_free(png_structp, void*);                                        // 0x0084de50
// ---- items of slice s0084dcd0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" png_structp __cdecl png_create_read_struct_2(const char*, png_voidp, png_error_ptr,
                                                        png_error_ptr, png_voidp, png_malloc_ptr,
                                                        png_free_ptr);                 // 0x0086b500
extern "C" png_infop   __cdecl png_create_info_struct(png_structp);                    // 0x0086af20
extern "C" void        __cdecl png_set_read_fn(png_structp, png_voidp, png_rw_ptr);    // 0x0086d910
extern "C" void        __cdecl png_read_info(png_structp, png_infop);                  // 0x0086b750
extern "C" void        __cdecl png_read_image(png_structp, png_bytep*);                // 0x0086c240
extern "C" void        __cdecl png_read_update_info(png_structp, png_infop);           // 0x0086bd40
extern "C" void        __cdecl png_destroy_read_struct(png_structp*, png_infop*, png_infop*);// 0x0086c540
extern "C" void        __cdecl png_set_strip_16(png_structp);                          // 0x0086d970
extern "C" void        __cdecl png_set_gray_to_rgb(png_structp);                       // 0x0086d980
extern "C" int         __cdecl png_check_sig(png_bytep, int);                          // 0x0086a9b0
extern "C" void        __cdecl png_set_packing(png_structp);                           // 0x00876e90
extern "C" int         __cdecl png_get_text(png_structp, png_infop, png_text**, int*); // 0x0086b430
extern "C" int         __cdecl png_get_tRNS(png_structp, png_infop, png_bytep*, int*,
                                            png_color_16*);                            // 0x0086b480
extern "C" png_uint_32 __cdecl png_get_x_pixels_per_meter(png_structp, png_infop);     // 0x0086b400
extern "C" void __cdecl PNGREAD_read_data(png_structp, png_bytep, png_size_t);         // 0x0084dc90

// @ 0x0084dcd0
int __cdecl PNG_read_gimex(GimexInfo* gimex, png_info_def* info, png_structp png, unsigned char* pixels, int stride)
{
    int i;
    png_bytep* rows;
    unsigned char* base;
    unsigned char* src;
    unsigned char* dst;

    if (setjmp(png->jmpbuf))
        return 0;

    rows = (png_bytep*)galloc(gimex->height * 4);
    if (rows != 0) {
        if (gimex->format == 0x20) {
            base = (unsigned char*)galloc(info->rowbytes * gimex->height);
            if (base != 0) {
                for (i = 0; i < gimex->height; i++)
                    rows[i] = base + info->rowbytes * i;

                png_read_image(png, rows);

                for (i = 0; i < gimex->height; i++) {
                    src = rows[i];
                    if (info->color_type == 2) {
                        int x;
                        dst = pixels;
                        for (x = 0; x < gimex->width; x++) {
                            dst[2] = src[0];
                            dst[1] = src[1];
                            dst[0] = src[2];
                            dst[3] = 0xff;
                            src += 3;
                            dst += 4;
                        }
                    } else if (info->color_type == 6) {
                        int x;
                        dst = pixels;
                        for (x = 0; x < gimex->width; x++) {
                            dst[2] = src[0];
                            dst[1] = src[1];
                            dst[0] = src[2];
                            dst[3] = src[3];
                            src += 4;
                            dst += 4;
                        }
                    }
                    pixels += stride;
                }
                gfree(base);
                gfree(rows);
                return 1;
            }
        } else {
            for (i = 0; i < gimex->height; i++) {
                rows[i] = pixels;
                pixels += stride;
            }
            png_read_image(png, rows);
        }
        gfree(rows);
    }
    return 1;
}

// @ 0x0084de50
void __cdecl PNGREAD_free(png_structp png, void* p)
{
    gfree(p);
}

// @ 0x0084de60
void* PNG_about(void)
{
    PngAboutDesc* d = (PngAboutDesc*)galloc(0x100);
    if (d != 0) {
        memset(d, 0, 0x100);
        d->magic = 0x504e47;
        d->size_ = 0x100;
        d->type_ = 0x159;
        d->flags = d->flags & 0xffffa3d7 | 0xa3d7;
        d->field_14 = 0;
        d->field_18 = 0x64;
        d->field_1c = 0x504e47;
        strcpy(d->ext, ".png");
        strcpy(d->author, "Kaz Okuda");
        strcpy(d->version, "1.10");
        d->field_a4 = 0x474e50;
        d->field_ac = 0x474e50;
        strcpy(d->desc, "Portable Network Graphics");
    }
    return d;
}

// @ 0x0084df40
int __stdcall PNG_check_sig(void* h)
{
    unsigned char buf[8];
    int r;

    gseek(h, 0, 0);
    gread(h, buf, 8);
    r = png_check_sig(buf, 8);
    if (r == 0) {
        if (png_check_sig(buf, 4) != 0)
            return 0x32;
    } else {
        return 100;
    }
    return 0;
}

// @ 0x0084dfa0
int __stdcall PNG_ropen(int** out, int io, int a3, int a4)
{
    int* h;
    int* pair;
    int iVar3;

    h = (int*)galloc(0x18);
    if (h != 0) {
        h[0] = 0;
        h[1] = 0;
        h[2] = 0;
        h[3] = 0;
        h[4] = 0;
        h[5] = 0;
        pair = (int*)galloc(8);
        h[5] = (int)pair;
        if (pair != 0) {
            iVar3 = (int)png_create_read_struct_2("1.2.25", 0, 0, (png_error_ptr)0xc2e4e0, 0,
                                                  (png_malloc_ptr)0x84e790, (png_free_ptr)0x84de50);
            pair[0] = iVar3;
            if (iVar3 != 0) {
                iVar3 = (int)png_create_info_struct((png_structp)pair[0]);
                pair[1] = iVar3;
                if (iVar3 != 0) {
                    png_set_read_fn((png_structp)pair[0], (void*)io, (png_rw_ptr)0x84dc90);
                    if (setjmp(((png_struct_def*)pair[0])->jmpbuf) == 0) {
                        gseek((void*)io, 0, 0);
                        png_read_info((png_structp)pair[0], (png_infop)pair[1]);
                        h[2] = 1;
                        h[3] = 0;
                        h[0] = 0x504e47;
                        h[1] = 0x18;
                        h[4] = io;
                        *out = h;
                        return h[2];
                    }
                    png_destroy_read_struct((png_structp*)&pair[0], (png_infop*)&pair[1], 0);
                    return 0;
                }
                png_destroy_read_struct((png_structp*)&pair[0], 0, 0);
            }
        }
    }
    return 0;
}

// @ 0x0084e0d0
GimexInfo* __stdcall PNG_read(int handle, int unused)
{
    PngPair* pair = *(PngPair**)(handle + 0x14);
    png_info_def* info;
    GimexInfo* d;
    unsigned int uVar12 = 0x20;
    unsigned int uVar7;
    int fmt;
    int iVar13;
    unsigned char bVar1;

    d = (GimexInfo*)galloc(0x2a70);
    if (d == 0)
        return d;
    memset(d, 0, 0x2a70);

    info = pair->info;
    iVar13 = (int)info;
    bVar1 = info->color_type;
    switch (bVar1) {
    case 0:
    case 3:
        if (info->bit_depth < 8)
            uVar12 = info->bit_depth;
        else
            uVar12 = 8;
        break;
    case 2:
        uVar12 = 0x18;
        break;
    }
    if (info->pixel_depth == 0x30)
        uVar12 = 0x30;

    uVar7 = 8;
    if (uVar12 < 9)
        fmt = 8;
    else {
        fmt = uVar12;
        if (uVar12 < 0x21)
            fmt = 0x20;
    }
    if (bVar1 != 3)
        uVar7 = info->bit_depth;

    d->field_c = 0;
    d->magic = 0x504e47;
    d->size_ = 0x2a70;
    d->type_ = 0x159;
    d->width = info->width;
    d->field_43c = uVar7;
    d->field_440 = uVar7;
    d->field_444 = uVar7;
    d->height = info->height;
    d->field_434 = 0;
    d->field_428 = 0;
    d->field_42c = 0;
    d->field_448 = 0;
    d->field_44c = 0;
    d->field_450 = 0;
    d->field_454 = 0;
    d->field_458 = 0;
    d->field_45c = 0;
    d->field_430 = 100;
    d->trans_depth = (bVar1 & 4) ? (int)uVar7 : 0;
    d->format = fmt;
    d->bit_depth = info->pixel_depth;
    d->num_colors = 0;

    {
        png_text* open_text = 0;
        int num_text = 0;
        png_get_text(pair->png, info, &open_text, &num_text);
        if (num_text > 0) {
            char* s = open_text->text;
            char* p = d->comment;
            char c;
            do { c = *s; *p = c; s++; p++; } while (c != '\0');
        }
    }

    {
        int ppm = (int)png_get_x_pixels_per_meter(pair->png, info);
        float f = (float)ppm;
        if (ppm < 0)
            f = f + 4294967296.0f;
        d->dpi = f * 0.03937007874015748f;
    }

    if (uVar12 < 9) {
        if (info->color_type == 0) {
            int n = 1 << uVar12;
            int i = 0;
            int j = 0;
            d->num_colors = n;
            if (n > 0) {
                unsigned char* p = (unsigned char*)d + 0x29;
                do {
                    int t = j / (d->num_colors - 1);
                    p[2] = 0xff;
                    i = i + 1;
                    j = j + 0xff;
                    p[1] = (unsigned char)t;
                    p[0] = (unsigned char)t;
                    p[-1] = (unsigned char)t;
                    p = p + 4;
                } while (i < d->num_colors);
            }
        } else {
            int i = 0;
            d->num_colors = info->num_palette;
            if (info->num_palette == 0) {
                gfree(d);
                return 0;
            }
            {
                png_bytep trans = 0;
                int num_trans = 0;
                png_color_16 trans_values;
                trans_values.index = 0;
                trans_values.red = 0;
                trans_values.green = 0;
                trans_values.blue = 0;
                trans_values.gray = 0;
                if (png_get_tRNS(pair->png, info, &trans, &num_trans, &trans_values) == 0)
                    trans = 0;
                else
                    d->trans_depth = 8;

                if (d->num_colors > 0) {
                    unsigned char* p = (unsigned char*)d + 0x29;
                    int k = 0;
                    do {
                        unsigned char* pal = info->palette;
                        p[1] = pal[k + 0];
                        p[0] = pal[k + 1];
                        p[-1] = pal[k + 2];
                        if (trans == 0 || num_trans <= i)
                            p[2] = 0xff;
                        else
                            p[2] = trans[i];
                        i = i + 1;
                        k = k + 3;
                        p = p + 4;
                    } while (i < d->num_colors);
                    return d;
                }
            }
        }
    }
    return d;
}

// @ 0x0084e3c0
int __stdcall PNG_read_rgba(PngHandle* ph, GimexInfo* gimex, unsigned char* pixels, int stride)
{
    png_structp png;
    png_info_def* info;
    int r = 0;

    png = png_create_read_struct_2("1.2.25", 0, 0, (png_error_ptr)0xc2e4e0, 0,
                                   PNGREAD_malloc, PNGREAD_free);
    if (png != 0) {
        info = (png_info_def*)png_create_info_struct(png);
        if (info != 0) {
            png_set_read_fn(png, ph->io, PNGREAD_read_data);
            if (setjmp(png->jmpbuf) == 0) {
                gseek(ph->io, 0, 0);
                png_read_info(png, info);
                if (info->bit_depth == 0x10 && info->pixel_depth != 0x30)
                    png_set_strip_16(png);
                png_set_packing(png);
                if (info->color_type == 4)
                    png_set_gray_to_rgb(png);
                png_read_update_info(png, info);
                r = PNG_read_gimex(gimex, info, png, pixels, stride);
            } else {
                r = 0;
            }
            png_destroy_read_struct(&png, &info, 0);
        }
    }
    return r;
}

// @ 0x0084e4e0
int __stdcall PNG_rclose(int handle)
{
    int r = 0;
    if (handle != 0) {
        PngPair* pair = *(PngPair**)(handle + 0x14);
        if (pair != 0) {
            png_destroy_read_struct(&pair->png, &pair->info, 0);
            gfree(*(void**)(handle + 0x14));
        }
        r = (int)gfree((void*)handle);
    }
    return r;
}
