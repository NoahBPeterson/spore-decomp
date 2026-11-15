// src/game/UTFSpore_Win32/pngwrite.cpp -- migrated from slice(s) s0084dcd0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/pngwrite.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void*        __stdcall galloc(unsigned int size);                        // 0x0087d4a0
extern "C" unsigned int __stdcall gfree(void* p);                                   // 0x0087d4c0
extern "C" void*        __cdecl memset(void* dst, int v, unsigned int n);           // 0x011e073e
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
typedef void  (__cdecl *png_error_ptr)(png_structp, const char*);
typedef void* (__cdecl *png_malloc_ptr)(png_structp, png_uint_32);
typedef void  (__cdecl *png_free_ptr)(png_structp, void*);
typedef void  (__cdecl *png_rw_ptr)(png_structp, png_bytep, png_size_t);
typedef void  (__cdecl *png_flush_ptr)(png_structp);
extern "C" png_structp __cdecl png_create_write_struct_2(const char*, png_voidp, png_error_ptr,
                                                         png_error_ptr, png_voidp, png_malloc_ptr,
                                                         png_free_ptr);                // 0x0086d3c0
extern "C" png_infop   __cdecl png_create_info_struct(png_structp);                    // 0x0086af20
extern "C" void        __cdecl png_set_write_fn(png_structp, png_voidp, png_rw_ptr,
                                                png_flush_ptr);                        // 0x008773d0
extern "C" void        __cdecl png_warning(png_structp, const char*);                  // 0x0086b300
extern "C" void        __cdecl png_set_packing(png_structp);                           // 0x00876e90
extern "C" void        __cdecl png_set_tRNS(png_structp, png_infop, png_bytep, int,
                                            png_color_16*);                            // 0x00876b30
extern "C" void        __cdecl png_set_pHYs(png_structp, png_infop, png_uint_32, png_uint_32,
                                            int);                                      // 0x00876640
extern "C" void*       __cdecl png_malloc(png_structp, png_uint_32);                   // 0x0086d7f0
extern "C" void        __cdecl png_free(png_structp, void*);                           // 0x0086d850
extern "C" void        __cdecl png_write_info(png_structp, png_infop);                 // 0x0086c7f0
extern "C" void        __cdecl png_write_end(png_structp, png_infop);                  // 0x0086cad0
extern "C" void        __cdecl png_write_image(png_structp, png_bytep*);               // 0x0086d580
extern "C" void        __cdecl png_destroy_write_struct(png_structp*, png_infop*);     // 0x0086d5e0
void* __cdecl PNGREAD_malloc(png_structp, png_uint_32);                                // 0x0084e790
void  __cdecl PNGREAD_free(png_structp, void*);                                        // 0x0084de50
extern "C" void __cdecl PNGREAD_write_data(png_structp, png_bytep, png_size_t);        // 0x0084e520
// ---- items of slice s0084dcd0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" png_structp __cdecl png_create_write_struct_2(const char*, png_voidp, png_error_ptr,
                                                         png_error_ptr, png_voidp, png_malloc_ptr,
                                                         png_free_ptr);                // 0x0086d3c0
extern "C" png_infop   __cdecl png_create_info_struct(png_structp);                    // 0x0086af20
extern "C" void        __cdecl png_set_write_fn(png_structp, png_voidp, png_rw_ptr,
                                                png_flush_ptr);                        // 0x008773d0
extern "C" void        __cdecl png_warning(png_structp, const char*);                  // 0x0086b300
extern "C" void        __cdecl png_set_packing(png_structp);                           // 0x00876e90
extern "C" void        __cdecl png_set_tRNS(png_structp, png_infop, png_bytep, int,
                                            png_color_16*);                            // 0x00876b30
extern "C" void        __cdecl png_set_pHYs(png_structp, png_infop, png_uint_32, png_uint_32,
                                            int);                                      // 0x00876640
extern "C" void*       __cdecl png_malloc(png_structp, png_uint_32);                   // 0x0086d7f0
extern "C" void        __cdecl png_free(png_structp, void*);                           // 0x0086d850
extern "C" void        __cdecl png_write_info(png_structp, png_infop);                 // 0x0086c7f0
extern "C" void        __cdecl png_write_end(png_structp, png_infop);                  // 0x0086cad0
extern "C" void        __cdecl png_write_image(png_structp, png_bytep*);               // 0x0086d580
extern "C" void        __cdecl png_destroy_write_struct(png_structp*, png_infop*);     // 0x0086d5e0
extern "C" void __cdecl PNGREAD_write_data(png_structp, png_bytep, png_size_t);        // 0x0084e520

// @ 0x0084e560
int __cdecl PNG_write_gimex(GimexInfo* gimex, png_info_def* info, png_structp png, unsigned char* pixels, int stride)
{
    int i, x;
    png_bytep* rows;
    unsigned char* base;
    unsigned char* src;
    unsigned char* dst;
    int rowbytes;
    png_bytep ct_ptr;

    if (setjmp(png->jmpbuf))
        return 0;

    rows = (png_bytep*)galloc(gimex->height * 4);
    if (rows == 0)
        return 1;

    ct_ptr = (png_bytep)((char*)info + 0x19);
    if (gimex->format == 0x20) {
        if ((*ct_ptr & 4) == 0)
            rowbytes = gimex->width * 3;
        else
            rowbytes = gimex->width * 4;
    } else {
        if ((*ct_ptr & 4) == 0)
            rowbytes = gimex->width;
        else
            rowbytes = gimex->width * 2;
    }

    base = (unsigned char*)galloc(gimex->height * rowbytes);
    if (base == 0) {
        gfree(rows);
        return 1;
    }
    for (i = 0; i < gimex->height; i++)
        rows[i] = base + rowbytes * i;

    for (i = 0; i < gimex->height; i++) {
        src = pixels;
        if (gimex->format == 0x20) {
            dst = rows[i];
            if ((*ct_ptr & 4) == 0) {
                for (x = 0; x < gimex->width; x++) {
                    dst[0] = src[2];
                    dst[1] = src[1];
                    dst[2] = src[0];
                    dst = dst + 3;
                    src = src + 4;
                }
            } else {
                for (x = 0; x < gimex->width; x++) {
                    dst[0] = src[2];
                    dst[1] = src[1];
                    dst[2] = src[0];
                    dst[3] = src[3];
                    dst = dst + 4;
                    src = src + 4;
                }
            }
        } else {
            unsigned char b = *ct_ptr;
            dst = rows[i];
            if (b == 0 || b == 4) {
                int n = gimex->bit_depth;
                int divisor;
                int half;
                int alpha = b & 4;
                if (n < 1) {
                    divisor = 1;
                    half = 0;
                } else {
                    if (n > 8)
                        n = 8;
                    if (n == 1) {
                        divisor = 1;
                        half = 0;
                    } else {
                        divisor = (1 << n) - 1;
                        half = (1 << n) >> 1;
                    }
                }
                for (x = 0; x < gimex->width; x++) {
                    *dst = (unsigned char)(((unsigned int)*src * 0xff + half) / divisor);
                    dst = dst + 1;
                    if (alpha != 0) {
                        *dst = gimex->palette[(unsigned int)*src * 4 + 3];
                        dst = dst + 1;
                    }
                    src = src + 1;
                }
            } else {
                for (x = 0; x < gimex->width; x++) {
                    *dst = src[x];
                    dst = dst + 1;
                }
            }
        }
        pixels += stride;
    }

    png_write_image(png, rows);
    gfree(base);
    gfree(rows);
    return 1;
}

// @ 0x0084e790
void* __cdecl PNGREAD_malloc(png_structp png, png_uint_32 size)
{
    return galloc(size);
}

// @ 0x0084e7a0
int __stdcall PNG_wopen(int** out, int io, int a3, int a4)
{
    int* h = (int*)galloc(0x18);
    if (h != 0) {
        h[0] = 0;
        h[1] = 0;
        h[2] = 0;
        h[5] = 0;
        h[3] = 0;
        h[4] = io;
        *out = h;
        return 1;
    }
    return 0;
}

// @ 0x0084e7e0
int __stdcall PNG_write(PngHandle* ph, GimexInfo* gimex, unsigned char* pixels, int stride)
{
    int result = 0;
    PngHandle* self = ph;
    png_structp png;
    png_info_def* info;
    png_bytep palette_buf = 0;
    png_bytep trns_buf = 0;
    unsigned char bit_depth;
    unsigned char color_type;
    int len;

    if (self->used != 0)
        return result;

    png = png_create_write_struct_2("1.2.25", 0, 0, (png_error_ptr)0xc2e4e0, 0,
                                    PNGREAD_malloc, PNGREAD_free);
    if (png == 0)
        goto done;
    info = (png_info_def*)png_create_info_struct(png);
    if (info == 0)
        goto done;

    png_set_write_fn(png, self->io, PNGREAD_write_data, (png_flush_ptr)0xc2e4e0);
    if (setjmp(png->jmpbuf) == 0) {
        if (gimex->format == 0x20) {
            bit_depth = 8;
            color_type = (unsigned char)((gimex->trans_depth != 0 ? 4 : 0) + 2);
        } else {
            int n = gimex->bit_depth;
            int uniform = 1;
            int i;
            unsigned char* p;
            if (n == 1)
                bit_depth = 1;
            else if (n == 2)
                bit_depth = 2;
            else
                bit_depth = (unsigned char)((n > 4 ? 4 : 0) + 4);
            p = (unsigned char*)gimex + 0x2a;
            i = 0;
            if (gimex->num_colors > 0) {
                do {
                    if (!uniform)
                        break;
                    if (*p != p[-1] || *p != p[-2])
                        uniform = 0;
                    i = i + 1;
                    p = p + 4;
                } while (i < gimex->num_colors);
            }
            if (uniform) {
                if (gimex->trans_depth == 0) {
                    color_type = 0;
                } else {
                    color_type = 4;
                    bit_depth = 8;
                }
            } else {
                color_type = 3;
                palette_buf = (png_bytep)galloc(gimex->num_colors * 3);
                i = 0;
                if (gimex->num_colors > 0) {
                    unsigned char* q = palette_buf + 2;
                    unsigned char* s = (unsigned char*)gimex + 0x29;
                    do {
                        q[-2] = s[1];
                        q[-1] = s[0];
                        q[0] = s[-1];
                        i = i + 1;
                        s = s + 4;
                        q = q + 3;
                    } while (i < gimex->num_colors);
                }
            }
        }

        info->width = gimex->width;
        info->height = gimex->height;
        info->bit_depth = bit_depth;
        info->color_type = color_type;
        if (color_type == 3) {
            unsigned short np;
            info->valid |= 8;
            info->palette = palette_buf;
            info->num_palette = (png_uint_16)gimex->num_colors;
            np = info->num_palette;
            if (gimex->trans_depth > 0) {
                trns_buf = (png_bytep)galloc((unsigned int)np * 4);
                if (trns_buf != 0) {
                    int i = 0;
                    unsigned char* p = (unsigned char*)gimex + 0x2b;
                    if (np != 0) {
                        do {
                            trns_buf[i] = p[0];
                            i = i + 1;
                            p = p + 4;
                        } while (i < (int)np);
                    }
                    png_set_tRNS(png, info, trns_buf, info->num_palette, 0);
                }
            }
        }

        if (gimex->dpi != 0.0f) {
            int res = (int)(gimex->dpi * 25.4f);
            png_set_pHYs(png, info, res, res, 1);
        }

        {
            char* comment = (char*)gimex + 0x65c;
            char* p = comment;
            char c;
            do { c = *p; p = p + 1; } while (c != '\0');
            len = (int)(p - (comment + 1));
            if ((unsigned int)(len - 1) <= 0x3fe) {
                info->num_text = 1;
                info->max_text = 1;
                info->text = (png_text*)png_malloc(png, (unsigned int)info->max_text << 4);
                info->text->compression = -1;
                info->text->key = "GIMEX COMMENT";
                info->text->text_length = len;
                info->text->text = (char*)png_malloc(png, (unsigned int)info->text->text_length + 1);
                {
                    char* d = info->text->text;
                    char* s = comment;
                    char cc;
                    do { cc = *s; *d = cc; s++; d++; } while (cc != '\0');
                }
            } else {
                png_warning(png, "Length of 'ginfo->comment' 0 or is over limit!");
            }
        }

        png_write_info(png, info);
        if (info->bit_depth < 8)
            png_set_packing(png);
        result = PNG_write_gimex(gimex, info, png, pixels, stride);
        png_write_end(png, info);
        if ((unsigned int)(len - 1) <= 0x3fe) {
            png_free(png, info->text->text);
            info->text->text = 0;
            png_free(png, info->text);
            info->text = 0;
        }
        if (palette_buf != 0)
            gfree(palette_buf);
        if (trns_buf != 0)
            gfree(trns_buf);
    } else {
        result = 0;
    }
    png_destroy_write_struct(&png, &info);

done:
    self->used = self->used + 1;
    return result;
}
