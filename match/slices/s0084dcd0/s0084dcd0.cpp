// Slice s0084dcd0: Spore's PNG glue (custom wrappers around libpng 1.2.25).
// Self-contained: png_struct / png_info layouts, the GIMEX image descriptor and the little
// file handle are declared below with the offsets observed in the disassembly.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include <setjmp.h>

#pragma function(memset)

typedef unsigned char png_byte;
typedef unsigned short png_uint_16;
typedef unsigned int png_uint_32;
typedef unsigned int png_size_t;
typedef char* png_charp;
typedef unsigned char* png_bytep;
typedef void* png_voidp;

struct png_struct_def;
typedef png_struct_def* png_structp;
struct png_info_def;
typedef png_info_def* png_infop;
struct png_text_struct;
typedef png_text_struct png_text;
typedef png_text_struct* png_textp;

// png_struct: we only ever touch the leading jmp_buf (libpng's png_jmpbuf is field 0).
struct png_struct_def { jmp_buf jmpbuf; };

struct png_text_struct {
    int          compression;   // +0x00
    char*        key;           // +0x04
    char*        text;          // +0x08
    png_size_t   text_length;   // +0x0c
};

// png_info (libpng 1.2.25 configuration), fields used by the wrappers.
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

// ---- the GIMEX image descriptor (0x2a70 bytes) ----------------------------------------------
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

// ---- the PNG "about"/format descriptor (0x100 bytes) ----------------------------------------
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

// ---- { png_struct*, png_info* } pair stored at handle + 0x14 --------------------------------
struct PngPair {
    png_structp png;   // +0
    png_infop   info;  // +4
};

// ---- file handle returned by the open helpers (0x18 bytes) ----------------------------------
struct PngHandle {
    int           magic;          // +0x00
    int           size_;          // +0x04
    int           ok;             // +0x08
    int           used;           // +0x0c
    png_voidp     io;             // +0x10
    PngPair*      pair;           // +0x14
};

// ---- custom allocators / io (Spore's g*) ----------------------------------------------------
extern "C" void*        __stdcall galloc(unsigned int size);                        // 0x0087d4a0
extern "C" unsigned int __stdcall gfree(void* p);                                   // 0x0087d4c0
extern "C" unsigned int __stdcall gread(void* h, void* buf, unsigned int n);        // 0x0087d4e0
extern "C" unsigned int __stdcall gwrite(void* h, const void* buf, unsigned int n); // 0x0087d510
extern "C" int          __stdcall gseek(void* h, long off, int whence);             // 0x0087d540
extern "C" void*        __cdecl memset(void* dst, int v, unsigned int n);           // 0x011e073e
extern "C" char*        __cdecl strcpy(char* dst, const char* src);                 // 0x011e0744

// ---- libpng entry points --------------------------------------------------------------------
typedef void  (__cdecl *png_error_ptr)(png_structp, const char*);
typedef void* (__cdecl *png_malloc_ptr)(png_structp, png_uint_32);
typedef void  (__cdecl *png_free_ptr)(png_structp, void*);
typedef void  (__cdecl *png_rw_ptr)(png_structp, png_bytep, png_size_t);
typedef void  (__cdecl *png_flush_ptr)(png_structp);

extern "C" png_structp __cdecl png_create_read_struct_2(const char*, png_voidp, png_error_ptr,
                                                        png_error_ptr, png_voidp, png_malloc_ptr,
                                                        png_free_ptr);                 // 0x0086b500
extern "C" png_structp __cdecl png_create_write_struct_2(const char*, png_voidp, png_error_ptr,
                                                         png_error_ptr, png_voidp, png_malloc_ptr,
                                                         png_free_ptr);                // 0x0086d3c0
extern "C" png_infop   __cdecl png_create_info_struct(png_structp);                    // 0x0086af20
extern "C" void        __cdecl png_set_read_fn(png_structp, png_voidp, png_rw_ptr);    // 0x0086d910
extern "C" void        __cdecl png_set_write_fn(png_structp, png_voidp, png_rw_ptr,
                                                png_flush_ptr);                        // 0x008773d0
extern "C" void        __cdecl png_read_info(png_structp, png_infop);                  // 0x0086b750
extern "C" void        __cdecl png_read_image(png_structp, png_bytep*);                // 0x0086c240
extern "C" void        __cdecl png_read_update_info(png_structp, png_infop);           // 0x0086bd40
extern "C" void        __cdecl png_destroy_read_struct(png_structp*, png_infop*, png_infop*);// 0x0086c540
extern "C" void        __cdecl png_set_strip_16(png_structp);                          // 0x0086d970
extern "C" void        __cdecl png_set_gray_to_rgb(png_structp);                       // 0x0086d980
extern "C" int         __cdecl png_check_sig(png_bytep, int);                          // 0x0086a9b0
extern "C" void        __cdecl png_error(png_structp, const char*);                    // 0x0086b250
extern "C" void        __cdecl png_warning(png_structp, const char*);                  // 0x0086b300
extern "C" png_voidp   __cdecl png_get_io_ptr(png_structp);                            // 0x0086aeb0
extern "C" void        __cdecl png_set_packing(png_structp);                           // 0x00876e90
extern "C" int         __cdecl png_get_text(png_structp, png_infop, png_text**, int*); // 0x0086b430
extern "C" int         __cdecl png_get_tRNS(png_structp, png_infop, png_bytep*, int*,
                                            png_color_16*);                            // 0x0086b480
extern "C" png_uint_32 __cdecl png_get_x_pixels_per_meter(png_structp, png_infop);     // 0x0086b400
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

// the read callback that lives just before this slice
extern "C" void __cdecl PNGREAD_read_data(png_structp, png_bytep, png_size_t);         // 0x0084dc90
// local helpers referenced as function pointers by the create calls
void* __cdecl PNGREAD_malloc(png_structp, png_uint_32);                                // 0x0084e790
void  __cdecl PNGREAD_free(png_structp, void*);                                        // 0x0084de50
extern "C" void __cdecl PNGREAD_write_data(png_structp, png_bytep, png_size_t);        // 0x0084e520

// @ 0x0084dcd0
int __cdecl PNG_read_gimex(GimexInfo* gimex, png_info_def* info, png_structp png,
                           unsigned char* pixels, int stride)
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

// @ 0x0084e520
void __cdecl PNGREAD_write_data(png_structp png, png_bytep data, png_size_t size)
{
    void* io = png_get_io_ptr(png);
    if (gwrite(io, data, size) != size)
        png_error(png, "Write Error");
}

// @ 0x0084e560
int __cdecl PNG_write_gimex(GimexInfo* gimex, png_info_def* info, png_structp png,
                            unsigned char* pixels, int stride)
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