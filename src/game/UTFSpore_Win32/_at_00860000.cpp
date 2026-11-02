// src/game/UTFSpore_Win32/_at_00860000.cpp -- migrated from slice(s) s0086d090, s00866220, s00865150, s00864330 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_00860000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);
extern "C" int  FUN_00864930(int* param_1, int* param_2);
# pragma function(memset)

// ---- items of slice s00864330 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            boolean;
#define FALSE 0
#define TRUE  1
#define JCS_RGB 2
#define RGB_RED   0
#define RGB_GREEN 1
#define RGB_BLUE  2
struct jpeg_error_mgr {
    void (*error_exit)(void*);                 // 0x00
    void (*emit_message)(void*, int);          // 0x04
    void (*output_message)(void*);             // 0x08
    void (*format_message)(void*, char*);      // 0x0c
    void (*reset_error_mgr)(void*);            // 0x10
    int   msg_code;                            // 0x14
    union { int i[8]; char s[80]; } msg_parm;  // 0x18
};
struct jpeg_memory_mgr {
    void*   (*alloc_small)(void*, int, unsigned);              // 0x00
    void*   (*alloc_large)(void*, int, unsigned);              // 0x04
    void**  (*alloc_sarray)(void*, int, unsigned, unsigned);   // 0x08
    void**  (*alloc_barray)(void*, int, unsigned, unsigned);   // 0x0c
};
struct jpeg_decompress_struct {
    struct jpeg_error_mgr*  err;       // 0x00
    struct jpeg_memory_mgr* mem;       // 0x04
    int pad_08[8];                     // 0x08..0x27
    int out_color_space;               // 0x28
    int pad_2c[0x0b];                  // 0x2c..0x57
    int dither_mode;                   // 0x58
    int pad_5c[1];                     // 0x5c
    int desired_number_of_colors;      // 0x60
    int pad_64[3];                     // 0x64..0x6f
    int output_width;                  // 0x70
    int pad_74[1];                     // 0x74
    int out_color_components;          // 0x78
    int pad_7c[340];                   // 0x7c..0x5cb
    void* cquantize;                   // 0x5cc
};
struct cquantize_s {
    int    pad_00[4];                  // 0x00..0x0f
    void** sv_colormap;                // 0x10
    int    sv_actual;                  // 0x14
    unsigned char** colorindex;        // 0x18
    int    is_padded;                  // 0x1c
    int    Ncolors[4];                 // 0x20
};
#define MAXJSAMPLE 255
#define JPOOL_IMAGE 1
extern "C" int  FUN_00864930(int* param_1, int* param_2);
static const int RGB_order[3] = { RGB_GREEN, RGB_RED, RGB_BLUE };
static int output_value(struct jpeg_decompress_struct* cinfo, int ci, int j, int maxj)
{
    return (int)(((int)j * MAXJSAMPLE + maxj / 2) / maxj);
}
static int largest_input_value(struct jpeg_decompress_struct* cinfo, int ci, int j, int maxj)
{
    return (int)(((int)(2 * j + 1) * MAXJSAMPLE + maxj) / (2 * maxj));
}
// ---- items of slice s00864330 end

// ---- items of slice s00865150 begin (TODO(rewrite): local stubs, replace by canonical classes)
#ifndef NULL
#define NULL 0
#endif
extern "C" void FUN_008668f0(void* p, int n);           // jzero_far
struct jpeg_decompress_struct_s0086_5150 {
    struct jpeg_error_mgr*  err;       // 0x00
    struct jpeg_memory_mgr* mem;       // 0x04
    int pad_08[0x14];                  // 0x08..0x57
    int dither_mode;                   // 0x58
    int pad_5c[1];                     // 0x5c
    int desired_number_of_colors;      // 0x60
    int pad_64[3];                     // 0x64..0x6f
    int output_width;                  // 0x70
    int pad_74[1];                     // 0x74
    int out_color_components;          // 0x78
    int pad_7c[2];                     // 0x7c..0x83
    int actual_number_of_colors;       // 0x84
    u8** colormap;                     // 0x88
    int pad_8c[0x12e];                 // 0x8c..0x543
    u8* sample_range_limit;            // 0x544
    int pad_548[0x21];                 // 0x548..0x5cb
    void* cquantize;                   // 0x5cc
};
struct cquantize_s_s0086_5150 {
    void (*start_pass)(void*);                      // 0x00
    void (*color_quantize)(void*, u8**, u8**, int);  // 0x04
    void (*finish_pass)(void*);                     // 0x08
    void (*new_color_map)(void*);                   // 0x0c
    u8** sv_colormap;                               // 0x10
    int  sv_actual;                                 // 0x14
    u8** colorindex;                                // 0x18
    int  is_padded;                                 // 0x1c
    int  Ncolors[4];                                // 0x20
    int  row_index;                                 // 0x30
    int  odither[4];                                // 0x34
    short* fserrors[3];                             // 0x44
    int  pad_50[1];                                 // 0x50
    int  direction;                                 // 0x54
};
struct jpeg_decompress_struct_s0086_5150;
extern "C" void FUN_00864a20_s0086_5150(struct jpeg_decompress_struct_s0086_5150* cinfo);  // create_colormap
extern "C" void FUN_00864b90_s0086_5150(struct jpeg_decompress_struct_s0086_5150* cinfo);  // create_colorindex
extern "C" int  FUN_00865950(struct jpeg_decompress_struct_s0086_5150*, int*, int, int); // median_cut
void FUN_00865150(struct jpeg_decompress_struct_s0086_5150*, u8**, u8**, int);
void FUN_00865300(struct jpeg_decompress_struct_s0086_5150*);
void FUN_00865340(struct jpeg_decompress_struct_s0086_5150*);
void FUN_00865450(struct jpeg_decompress_struct_s0086_5150*);
void FUN_008654f0(struct jpeg_decompress_struct_s0086_5150*, u8**, u8**, int);
void FUN_00865570(struct jpeg_decompress_struct_s0086_5150*, int*);
void FUN_00865ad0(int*, struct jpeg_decompress_struct_s0086_5150*, int);
void FUN_00865c50(struct jpeg_decompress_struct_s0086_5150*, int);
int  FUN_00865ce0(struct jpeg_decompress_struct_s0086_5150*, int, int, int, u8*);
void FUN_00865ec0(struct jpeg_decompress_struct_s0086_5150*, int, int, int, int, u8*, u8*);
void FUN_00866040(int, struct jpeg_decompress_struct_s0086_5150*, int, int);
void FUN_00866160(struct jpeg_decompress_struct_s0086_5150*, u8**, u8**, int);
// ---- items of slice s00865150 end

// ---- items of slice s00866220 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00866040(void* self, int a, int b);
extern "C" void FUN_00865c50(int x);
extern "C" const uint32_t g_0141e9c0[256];
extern "C" const uint32_t g_0141edc0[256];
extern "C" const uint32_t g_0141f1c0[256];
extern "C" const uint32_t g_0141f5c0[256];
struct Ctx;
typedef void* (__cdecl *AFn)(void*, int, int);
typedef void* (__cdecl *AFn3)(void*, int, int, int);
struct Ctx {
    void*     f00;   // +0x00  (fn ptr: the per-scan mode entry)
    void*     f04;   // +0x04  (fn ptr)
    void*     f08;   // +0x08  (fn ptr)
    void*     f0c;   // +0x0c  (fn ptr)
    int       f10;   // +0x10
    int       f14;   // +0x14
    uint32_t* f18;   // +0x18  (array of 0x20 row buffers)
    int       f1c;   // +0x1c
    int*      f20;   // +0x20  (sample buffer)
    int       f24;   // +0x24
    int*      f28;   // +0x28  (range-limit table)
};
struct Obj {
    void**   m00;    // +0x00  (points at an error-reporting object: vtbl[0] and
                     //         two int fields at +0x14 / +0x18)
    void**   alloc;  // +0x04  (allocator interface)
    uint8_t  pad08[0x50];
    int      f58;    // +0x58
    uint8_t  pad5c[4];
    int      f60;    // +0x60
    uint8_t  pad64[8];
    int      f6c;    // +0x6c
    int      f70;    // +0x70
    uint8_t  pad74[4];
    int      f78;    // +0x78
    uint8_t  pad7c[8];
    int      f84;    // +0x84
    int*     f88;    // +0x88  (int[3])
    uint8_t  pad8c[0x544 - 0x8c];
    int      f544;   // +0x544
    uint8_t  pad548[0x5cc - 0x548];
    Ctx*     ctx;    // +0x5cc
};
void FUN_00866220(Obj* self, int param_2, int* param_3, int param_4);
void FUN_008664e0(Obj* self);
void FUN_00866580(Obj* self);
void FUN_008665b0(Obj* self, int param_2);
void FUN_008666e0(Obj* self);
void FUN_00866700(Obj* self);
// ---- items of slice s00866220 end

// ---- items of slice s0086d090 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned long png_uint_32;
typedef unsigned short png_uint_16;
typedef unsigned char png_byte;
typedef png_byte* png_bytep;
typedef png_uint_16* png_uint_16p;
typedef png_uint_16** png_uint_16pp;
typedef void* png_voidp;
typedef unsigned int png_size_t;
struct png_color { png_byte red, green, blue; };
typedef png_color* png_colorp;
struct png_color_16 { png_byte index; png_uint_16 red, green, blue, gray; };
struct png_color_8 { png_byte red, green, blue, gray, alpha; };
struct png_row_info { png_uint_32 width, rowbytes; png_byte color_type, bit_depth, channels, pixel_depth; };
struct z_stream_s {
    png_bytep next_in; unsigned avail_in; png_uint_32 total_in;
    png_bytep next_out; unsigned avail_out; png_uint_32 total_out;
    char* msg; void* state; void* zalloc; void* zfree; void* opaque;
    int data_type; png_uint_32 adler; png_uint_32 reserved;
};
struct png_struct_def;
typedef png_struct_def* png_structp;
typedef void (*png_fnptr)(void);
struct png_struct_def {
    int jmpbuf[16];
    png_fnptr error_fn, warning_fn;
    png_voidp error_ptr;
    png_fnptr write_data_fn, read_data_fn;
    png_voidp io_ptr;
    png_fnptr read_user_transform_fn, write_user_transform_fn;
    png_voidp user_transform_ptr;
    png_byte user_transform_depth, user_transform_channels;
    png_uint_32 mode;              // +0x68
    png_uint_32 flags;
    png_uint_32 transformations;   // +0x70
    z_stream_s zstream;
    png_bytep zbuf;
    png_size_t zbuf_size;
    int zlib_level, zlib_method, zlib_window_bits, zlib_mem_level, zlib_strategy;
    png_uint_32 width, height, num_rows, usr_width, rowbytes, irowbytes, iwidth, row_number;
    png_bytep prev_row, row_buf, sub_row, up_row, avg_row, paeth_row;
    png_row_info row_info;
    png_uint_32 idat_size, crc;
    png_colorp palette;            // +0x114
    png_uint_16 num_palette;       // +0x118
    png_uint_16 num_trans;         // +0x11a
    png_byte chunk_name[5];
    png_byte compression, filter, interlaced, pass, do_filter;
    png_byte color_type;           // +0x126
    png_byte bit_depth;            // +0x127
    png_byte usr_bit_depth, pixel_depth, channels, usr_channels, sig_bytes;
    png_uint_16 filler;
    png_byte background_gamma_type;  // +0x130
    float background_gamma;          // +0x134
    png_color_16 background;         // +0x138
    png_color_16 background_1;       // +0x142
    png_fnptr output_flush_fn;
    png_uint_32 flush_dist, flush_rows;
    int gamma_shift;
    float gamma;                     // +0x15c
    float screen_gamma;              // +0x160
    png_bytep gamma_table;           // +0x164
    png_bytep gamma_from_1;          // +0x168
    png_bytep gamma_to_1;            // +0x16c
    png_uint_16pp gamma_16_table, gamma_16_from_1, gamma_16_to_1;
    png_color_8 sig_bit;             // +0x17c
    png_color_8 shift;
    png_bytep trans;                 // +0x188
    png_color_16 trans_values;       // +0x18c
    // libpng 1.2.25 fields enabled in Spore's build, from trans_values to the end of png_struct
    // (offsets are the retail ones, from png_set_filter_heuristics and png_create_write_struct_2).
    png_fnptr read_row_fn;           // +0x198
    png_fnptr write_row_fn;          // +0x19c
    png_fnptr info_fn;               // +0x1a0
    png_fnptr row_fn;                // +0x1a4
    png_fnptr end_fn;                // +0x1a8
    png_bytep save_buffer_ptr;       // +0x1ac
    png_bytep save_buffer;           // +0x1b0
    png_bytep current_buffer_ptr;    // +0x1b4
    png_bytep current_buffer;        // +0x1b8
    png_uint_32 push_length;         // +0x1bc
    png_uint_32 skip_length;         // +0x1c0
    png_size_t save_buffer_size;     // +0x1c4
    png_size_t save_buffer_max;      // +0x1c8
    png_size_t buffer_size;          // +0x1cc
    png_size_t current_buffer_size;  // +0x1d0
    int process_mode;                // +0x1d4
    int cur_palette;                 // +0x1d8
    png_size_t current_text_size;    // +0x1dc
    png_size_t current_text_left;    // +0x1e0
    char* current_text;              // +0x1e4
    char* current_text_ptr;          // +0x1e8
    png_bytep palette_lookup;        // +0x1ec
    png_bytep dither_index;          // +0x1f0
    png_uint_16p hist;               // +0x1f4
    png_byte heuristic_method;       // +0x1f8
    png_byte num_prev_filters;       // +0x1f9
    png_byte pad_1fa[2];             // +0x1fa
    png_bytep prev_filters;          // +0x1fc
    png_uint_16p filter_weights;     // +0x200
    png_uint_16p inv_filter_weights; // +0x204
    png_uint_16p filter_costs;       // +0x208
    png_uint_16p inv_filter_costs;   // +0x20c
    char* time_buffer;               // +0x210
    png_uint_32 free_me;             // +0x214
    png_voidp user_chunk_ptr;        // +0x218
    png_fnptr read_user_chunk_fn;    // +0x21c
    int num_chunk_list;              // +0x220
    png_bytep chunk_list;            // +0x224
    png_byte rgb_to_gray_status;     // +0x228
    png_byte pad_229;                // +0x229
    png_uint_16 rgb_to_gray_red_coeff;   // +0x22a
    png_uint_16 rgb_to_gray_green_coeff; // +0x22c
    png_uint_16 rgb_to_gray_blue_coeff;  // +0x22e
    png_uint_32 mng_features_permitted;  // +0x230
    int int_gamma;                   // +0x234
    png_byte filter_type;            // +0x238
    png_byte mmx_bitdepth_threshold; // +0x239
    png_byte pad_23a[2];             // +0x23a
    png_uint_32 mmx_rowbytes_threshold;  // +0x23c
    png_uint_32 asm_flags;           // +0x240
    png_voidp mem_ptr;               // +0x244
    png_fnptr malloc_fn;             // +0x248
    png_fnptr free_fn;               // +0x24c
    png_bytep big_row_buf;           // +0x250
    png_bytep dither_sort;           // +0x254
    png_bytep index_to_palette;      // +0x258
    png_bytep palette_to_index;      // +0x25c
    png_byte compression_type;       // +0x260
    png_byte pad_261[3];             // +0x261
    png_uint_32 user_width_max;      // +0x264
    png_uint_32 user_height_max;     // +0x268
    png_byte unknown_chunk[0x14];    // +0x26c..+0x27f (png_unknown_chunk)
};
typedef void (*png_free_ptr)(png_structp, png_voidp);
void png_destroy_struct_2(png_voidp struct_ptr, png_free_ptr free_fn, png_voidp mem_ptr);
// ---- items of slice s0086d090 end

// @ 0x00864930
extern "C" int FUN_00864930(int* pcinfo, int* Ncolors)
{
    struct jpeg_decompress_struct* cinfo = (struct jpeg_decompress_struct*)pcinfo;
    int  nc = cinfo->out_color_components;
    int  max_colors = cinfo->desired_number_of_colors;
    int  total_colors, iroot, i, j;
    boolean changed;
    long temp;

    iroot = 1;
    do {
        iroot++;
        temp = iroot;
        for (i = 1; i < nc; i++)
            temp *= iroot;
    } while (temp <= (long)max_colors);
    iroot--;

    if (iroot < 2) {
        cinfo->err->msg_code = 0x37;                 // JERR_QUANT_FEW_COLORS
        cinfo->err->msg_parm.i[0] = (int)temp;
        (*(void(__cdecl*)(struct jpeg_decompress_struct*))cinfo->err->error_exit)(cinfo);
    }

    total_colors = 1;
    for (i = 0; i < nc; i++) {
        Ncolors[i] = iroot;
        total_colors *= iroot;
    }
    do {
        changed = FALSE;
        for (i = 0; i < nc; i++) {
            j = (cinfo->out_color_space == JCS_RGB ? RGB_order[i] : i);
            temp = total_colors / Ncolors[j];
            temp *= Ncolors[j] + 1;
            if (temp > (long)max_colors)
                break;
            Ncolors[j]++;
            total_colors = (int)temp;
            changed = TRUE;
        }
    } while (changed);

    return total_colors;
}

// @ 0x00864a20
extern "C" void FUN_00864a20(struct jpeg_decompress_struct* cinfo)
{
    struct cquantize_s* cquantize = (struct cquantize_s*)cinfo->cquantize;
    int total_colors;
    unsigned char** colormap;
    int i, j, k, nci, blksize, blkdist, ptr, val;

    /* Select number of colors for each component */
    total_colors = FUN_00864930((int*)cinfo, cquantize->Ncolors);

    /* Report selected color counts */
    void* report_this;
    if (cinfo->out_color_components == 3) {
        cinfo->err->msg_parm.i[0] = total_colors;
        cinfo->err->msg_parm.i[1] = cquantize->Ncolors[0];
        cinfo->err->msg_parm.i[2] = cquantize->Ncolors[1];
        cinfo->err->msg_parm.i[3] = cquantize->Ncolors[2];
        cinfo->err->msg_code = 0x5d;
        report_this = (void*)cinfo->err->emit_message;
    } else {
        cinfo->err->msg_code = 0x5e;
        cinfo->err->msg_parm.i[0] = total_colors;
        report_this = (void*)cinfo->err;
    }
    ((void (__fastcall*)(void*, void*))cinfo->err->emit_message)
        (report_this, (void*)cinfo);

    /* Allocate and fill in the colormap. */
    colormap = (unsigned char**)((void* (__thiscall*)(void*, void*, int, unsigned, unsigned))
        cinfo->mem->alloc_sarray)
        ((void*)(size_t)cinfo->out_color_components, (void*)cinfo, JPOOL_IMAGE,
         (unsigned)total_colors, (unsigned)cinfo->out_color_components);

    blkdist = total_colors;

    for (i = 0; i < cinfo->out_color_components; i++) {
        nci = cquantize->Ncolors[i];
        blksize = blkdist / nci;
        for (j = 0; j < nci; j++) {
            val = output_value(cinfo, i, j, nci - 1);
            for (ptr = j * blksize; ptr < total_colors; ptr += blkdist) {
                for (k = 0; k < blksize; k++)
                    colormap[i][ptr + k] = (u8)val;
            }
        }
        blkdist = blksize;
    }

    cquantize->sv_colormap = (void**)colormap;
    cquantize->sv_actual = total_colors;
}

// @ 0x00864b90
extern "C" void FUN_00864b90(struct jpeg_decompress_struct* cinfo)
{
    struct cquantize_s* cquantize = (struct cquantize_s*)cinfo->cquantize;
    unsigned char* indexptr;
    int i, j, k, nci, blksize, val, pad;

    if (cinfo->dither_mode == 1 /* JDITHER_ORDERED */) {
        pad = MAXJSAMPLE * 2;
        cquantize->is_padded = TRUE;
    } else {
        pad = 0;
        cquantize->is_padded = FALSE;
    }

    cquantize->colorindex = (unsigned char**)(*cinfo->mem->alloc_sarray)
        ((void*)cinfo, JPOOL_IMAGE,
         (unsigned)(MAXJSAMPLE + 1 + pad),
         (unsigned)cinfo->out_color_components);

    blksize = cquantize->sv_actual;

    for (i = 0; i < cinfo->out_color_components; i++) {
        nci = cquantize->Ncolors[i];
        blksize = blksize / nci;
        if (pad)
            cquantize->colorindex[i] += MAXJSAMPLE;
        indexptr = cquantize->colorindex[i];
        val = 0;
        k = largest_input_value(cinfo, i, 0, nci - 1);
        for (j = 0; j <= MAXJSAMPLE; j++) {
            while (j > k)
                k = largest_input_value(cinfo, i, ++val, nci - 1);
            indexptr[j] = (u8)(val * blksize);
        }
        if (pad)
            for (j = 1; j <= MAXJSAMPLE; j++) {
                indexptr[-j] = indexptr[0];
                indexptr[MAXJSAMPLE + j] = indexptr[MAXJSAMPLE];
            }
    }
}

// @ 0x00864ce0
void* FUN_00864ce0(void* cinfo, int scale)
{
    void* p = (*(void*(**)(void*, int, int))(*(int*)((int*)cinfo + 1)))(cinfo, 1, 0x400);
    int* q = (int*)p;
    u8*  tbl = (u8*)0x0141e770;
    int  div = scale * 0x200 - 0x200;
    do {
        int i = 0;
        do {
            q[i] = (int)(((u32)tbl[i] * 0xfffffe02u + 0xfe01) / (u32)div);
            i++;
        } while (i < 0x10);
        q += 0x10;
        tbl += 0x10;
    } while ((int)tbl < 0x0141e870);
    return p;
}

// @ 0x00864d60
void FUN_00864d60(int* cinfo)
{
    int  iVar1 = *(int*)((char*)cinfo + 0x5cc);
    int  iVar4 = 0;
    int* piVar5;
    if (0 < *(int*)((char*)cinfo + 0x78)) {
        piVar5 = (int*)(iVar1 + 0x34);
        do {
            int iVar2 = 0;
            if (0 < iVar4) {
                int* piVar3 = (int*)(iVar1 + 0x20);
                do {
                    if (piVar5[-5] == *piVar3) {
                        iVar2 = *(int*)(iVar1 + 0x34 + iVar2 * 4);
                        if (iVar2 != 0) goto store;
                        break;
                    }
                    iVar2++;
                    piVar3++;
                } while (iVar2 < iVar4);
            }
            iVar2 = (int)FUN_00864ce0(cinfo, *(int*)((char*)cinfo + 0x70));
        store:
            *piVar5 = iVar2;
            iVar4++;
            piVar5++;
        } while (iVar4 < *(int*)((char*)cinfo + 0x78));
    }
    return;
}

// @ 0x00864db0
extern "C" void FUN_00864db0(struct jpeg_decompress_struct* cinfo, u8** input_buf, u8** output_buf, int num_rows)
{
    struct cquantize_s* cquantize = (struct cquantize_s*)cinfo->cquantize;
    u8** colorindex = cquantize->colorindex;
    int  pixcode, ci;
    u8*  ptrin;
    u8*  ptrout;
    int  row;
    unsigned int col;
    unsigned int width = cinfo->output_width;
    int  nc = cinfo->out_color_components;

    for (row = 0; row < num_rows; row++) {
        ptrin = input_buf[row];
        ptrout = output_buf[row];
        for (col = width; col > 0; col--) {
            pixcode = 0;
            for (ci = 0; ci < nc; ci++) {
                pixcode += colorindex[ci][*ptrin++];
            }
            *ptrout++ = (u8)pixcode;
        }
    }
}

// @ 0x00864e60
extern "C" void FUN_00864e60(struct jpeg_decompress_struct* cinfo, u8** input_buf, u8** output_buf, int num_rows)
{
    struct cquantize_s* cquantize = (struct cquantize_s*)cinfo->cquantize;
    int  pixcode;
    u8*  ptrin;
    u8*  ptrout;
    u8*  colorindex0 = cquantize->colorindex[0];
    u8*  colorindex1 = cquantize->colorindex[1];
    u8*  colorindex2 = cquantize->colorindex[2];
    int  row;
    unsigned int col;
    unsigned int width = cinfo->output_width;

    for (row = 0; row < num_rows; row++) {
        ptrin = input_buf[row];
        ptrout = output_buf[row];
        for (col = width; col > 0; col--) {
            pixcode  = colorindex0[*ptrin++];
            pixcode += colorindex1[*ptrin++];
            pixcode += colorindex2[*ptrin++];
            *ptrout++ = (u8)pixcode;
        }
    }
}

// @ 0x00865150
void FUN_00865150(struct jpeg_decompress_struct_s0086_5150* cinfo, u8** input_buf, u8** output_buf, int num_rows)
{
    struct cquantize_s_s0086_5150* cq = (struct cquantize_s_s0086_5150*)cinfo->cquantize;
    short** fserrors = (short**)((char*)cq + 0x44);
    int width = cinfo->output_width;
    u8* range_limit = cinfo->sample_range_limit;
    int comps = cinfo->out_color_components;

    if (num_rows <= 0)
        return;

    do {
        int ci;

        FUN_008668f0(*output_buf, width);
        ci = 0;
        if (comps > 0) {
            short** errp = fserrors;
            do {
                u8*   outptr = *output_buf;
                u8*   inptr  = *input_buf + ci;
                short* err   = *errp;
                u8*   cmap   = cq->sv_colormap[ci];
                u8*   cidx   = cq->colorindex[ci];
                int   dir, step;
                int   prev, next, carry;
                int   col;

                if (cq->direction == 0) {
                    dir = 1;
                    step = comps;
                } else {
                    outptr += width - 1;
                    inptr  += (width - 1) * comps;
                    dir = -1;
                    err += width + 1;
                    step = -comps;
                }

                prev = 0;
                next = 0;
                carry = 0;
                for (col = width; col != 0; col--) {
                    int cur = range_limit[inptr[0] + ((err[dir] + prev + 8) >> 4)];
                    int pixcode, diff;

                    inptr += step;
                    pixcode = cidx[cur];
                    *outptr += (u8)pixcode;
                    diff = cur - cmap[pixcode];

                    next += diff * 3;
                    err[0] = (short)next;
                    next = carry + diff * 5;
                    carry = diff;
                    prev = diff * 7;

                    outptr += dir;
                    err += dir;
                }
                err[0] = (short)next;
                errp++;
                ci++;
            } while (ci < comps);
        }
        output_buf++;
        input_buf++;
        cq->direction = (cq->direction == 0);
        num_rows--;
    } while (num_rows != 0);
}

// @ 0x00865300
void FUN_00865300(struct jpeg_decompress_struct_s0086_5150* cinfo)
{
    struct cquantize_s_s0086_5150* cq = (struct cquantize_s_s0086_5150*)cinfo->cquantize;
    int size = cinfo->output_width * 2 + 4;
    short** p = (short**)((char*)cq + 0x44);
    int i = 0;

    if (cinfo->out_color_components > 0) {
        do {
            *p = (short*)(*cinfo->mem->alloc_large)(cinfo, 1, size);
            i++;
            p++;
        } while (i < cinfo->out_color_components);
    }
}

// @ 0x00865450
void FUN_00865450(struct jpeg_decompress_struct_s0086_5150* cinfo)
{
    struct cquantize_s_s0086_5150* cq =
        (struct cquantize_s_s0086_5150*)(*cinfo->mem->alloc_small)(cinfo, 1, 0x58);

    cinfo->cquantize = cq;
    cq->start_pass = (void (*)(void*))FUN_00865340;
    cq->finish_pass = (void (*)(void*))0x00c2e4e0;
    cq->new_color_map = (void (*)(void*))0x00865430;
    cq->fserrors[0] = NULL;
    cq->odither[0] = 0;

    if (cinfo->out_color_components > 4) {
        cinfo->err->msg_code = 0x36;
        cinfo->err->msg_parm.i[0] = 4;
        (*cinfo->err->error_exit)(cinfo);
    }
    if (cinfo->desired_number_of_colors > 0x100) {
        cinfo->err->msg_code = 0x38;
        cinfo->err->msg_parm.i[0] = 0x100;
        (*cinfo->err->error_exit)(cinfo);
    }

    FUN_00864a20_s0086_5150(cinfo);
    FUN_00864b90_s0086_5150(cinfo);

    if (cinfo->dither_mode == 2)
        FUN_00865300(cinfo);
}

// @ 0x008654f0
void FUN_008654f0(struct jpeg_decompress_struct_s0086_5150* cinfo, u8** input_buf, u8** output_buf, int num_rows)
{
    struct cquantize_s_s0086_5150* cq = (struct cquantize_s_s0086_5150*)cinfo->cquantize;
    short** hist = (short**)((char*)cq + 0x18);
    int width = cinfo->output_width;
    int row = 0;

    if (num_rows <= 0)
        return;

    do {
        u8* ptr = input_buf[row];
        int col = width;
        if (width != 0) {
            do {
                int idx = (ptr[1] >> 2) * 0x20 + (ptr[2] >> 3);
                short* cell = (short*)((char*)hist[ptr[0] >> 3] + idx * 2);
                (*cell)++;
                if (*cell == 0)
                    *cell = -1;
                ptr += 3;
                col--;
            } while (col != 0);
        }
        row++;
    } while (row < num_rows);
}

// @ 0x00865570
void FUN_00865570(struct jpeg_decompress_struct_s0086_5150* cinfo, int* box)
{
    struct cquantize_s_s0086_5150* cq = (struct cquantize_s_s0086_5150*)cinfo->cquantize;
    short** hist = (short**)((char*)cq + 0x18);
    int c0min = box[0], c0max = box[1];
    int c1min = box[2], c1max = box[3];
    int c2min = box[4], c2max = box[5];
    int i, j, k, found, count;

    /* minimum c0 */
    found = 0;
    for (i = c0min; i <= c0max && !found; i++) {
        short* row = hist[i];
        for (j = c1min; j <= c1max && !found; j++) {
            short* p = (short*)((char*)row + (j * 0x20 + c2min) * 2);
            for (k = c2min; k <= c2max; k++) {
                if (*p++ != 0) {
                    box[0] = i;
                    c0min = i;
                    found = 1;
                    break;
                }
            }
        }
    }
    /* maximum c0 */
    found = 0;
    for (i = c0max; i >= c0min && !found; i--) {
        short* row = hist[i];
        for (j = c1min; j <= c1max && !found; j++) {
            short* p = (short*)((char*)row + (j * 0x20 + c2min) * 2);
            for (k = c2min; k <= c2max; k++) {
                if (*p++ != 0) {
                    box[1] = i;
                    c0max = i;
                    found = 1;
                    break;
                }
            }
        }
    }
    /* minimum c1 */
    if (c1min < c1max) {
        found = 0;
        for (j = c1min; j <= c1max && !found; j++) {
            for (i = c0min; i <= c0max && !found; i++) {
                short* p = (short*)((char*)hist[i] + (j * 0x20 + c2min) * 2);
                for (k = c2min; k <= c2max; k++) {
                    if (*p++ != 0) {
                        box[2] = j;
                        c1min = j;
                        found = 1;
                        break;
                    }
                }
            }
        }
        /* maximum c1 */
        found = 0;
        for (j = c1max; j >= c1min && !found; j--) {
            for (i = c0min; i <= c0max && !found; i++) {
                short* p = (short*)((char*)hist[i] + (j * 0x20 + c2min) * 2);
                for (k = c2min; k <= c2max; k++) {
                    if (*p++ != 0) {
                        box[3] = j;
                        c1max = j;
                        found = 1;
                        break;
                    }
                }
            }
        }
    }
    /* minimum c2 */
    if (c2min < c2max) {
        found = 0;
        for (k = c2min; k <= c2max && !found; k++) {
            for (i = c0min; i <= c0max && !found; i++) {
                short* p = (short*)((char*)hist[i] + (c1min * 0x20 + k) * 2);
                for (j = c1min; j <= c1max; j++) {
                    if (*p != 0) {
                        box[4] = k;
                        c2min = k;
                        found = 1;
                        break;
                    }
                    p += 0x20;
                }
            }
        }
        /* maximum c2 */
        found = 0;
        for (k = c2max; k >= c2min && !found; k--) {
            for (i = c0min; i <= c0max && !found; i++) {
                short* p = (short*)((char*)hist[i] + (c1min * 0x20 + k) * 2);
                for (j = c1min; j <= c1max; j++) {
                    if (*p != 0) {
                        box[5] = k;
                        c2max = k;
                        found = 1;
                        break;
                    }
                    p += 0x20;
                }
            }
        }
    }

    box[6] = (c2max - c2min) * 8 * ((c2max - c2min) * 8)
           + (c1max - c1min) * 0xc * ((c1max - c1min) * 0xc)
           + (c0max - c0min) * 0x10 * ((c0max - c0min) * 0x10);

    count = 0;
    for (i = c0min; i <= c0max; i++) {
        for (j = c1min; j <= c1max; j++) {
            short* p = (short*)((char*)hist[i] + (j * 0x20 + c2min) * 2);
            for (k = c2min; k <= c2max; k++) {
                if (*p++ != 0)
                    count++;
            }
        }
    }
    box[7] = count;
}

// @ 0x00865ad0
void FUN_00865ad0(int* box, struct jpeg_decompress_struct_s0086_5150* cinfo, int idx)
{
    struct cquantize_s_s0086_5150* cq = (struct cquantize_s_s0086_5150*)cinfo->cquantize;
    short** hist = (short**)((char*)cq + 0x18);
    u8** colormap = cinfo->colormap;
    int c0min = box[0], c0max = box[1];
    int c1min = box[2], c1max = box[3];
    int c2min = box[4], c2max = box[5];
    int count = 0, sum0 = 0, sum1 = 0, sum2 = 0;
    int i, j, k;

    for (i = c0min; i <= c0max; i++) {
        int w0 = i * 8 + 4;
        for (j = c1min; j <= c1max; j++) {
            short* p = (short*)((char*)hist[i] + (j * 0x20 + c2min) * 2);
            int w1 = j * 4 + 2;
            for (k = c2min; k <= c2max; k++) {
                int v = *p++;
                int w2 = k * 8 + 4;
                if (v != 0) {
                    sum0 += w0 * v;
                    sum1 += w1 * v;
                    count += v;
                    sum2 += w2 * v;
                }
            }
        }
    }

    if (count != 0) {
        int half = count >> 1;
        colormap[0][idx] = (u8)((sum0 + half) / count);
        colormap[1][idx] = (u8)((sum1 + half) / count);
        colormap[2][idx] = (u8)((sum2 + half) / count);
    }
}

// @ 0x00865c50
void FUN_00865c50(struct jpeg_decompress_struct_s0086_5150* cinfo, int desired)
{
    int* box = (int*)(*cinfo->mem->alloc_small)(cinfo, 1, desired * 0x20);
    int n, i;

    box[0] = 0;
    box[1] = 0x1f;
    box[2] = 0;
    box[3] = 0x3f;
    box[4] = 0;
    box[5] = 0x1f;

    FUN_00865570(cinfo, box);
    n = FUN_00865950(cinfo, box, 1, desired);

    i = 0;
    if (n > 0) {
        do {
            FUN_00865ad0(box, cinfo, i);
            i++;
            box += 8;
        } while (i < n);
    }

    cinfo->actual_number_of_colors = n;
    cinfo->err->msg_code = 0x5f;
    cinfo->err->msg_parm.i[0] = n;
    (*cinfo->err->emit_message)(cinfo, 1);
}

// @ 0x00865ce0
int FUN_00865ce0(struct jpeg_decompress_struct_s0086_5150* cinfo, int green, int red, int blue, u8* out)
{
    int n = cinfo->actual_number_of_colors;
    u8* cm0 = cinfo->colormap[0];
    u8* cm1 = cinfo->colormap[1];
    u8* cm2 = cinfo->colormap[2];
    int ghi = green + 0x1c;
    int gmid = (green + ghi) >> 1;
    int rmid = (red * 2 + 0x18) >> 1;
    int bmid = (blue * 2 + 0x18) >> 1;
    int errs[256];
    int idx, minv, nout;

    minv = 0x7fffffff;
    idx = 0;
    if (n > 0) {
        do {
            int v0 = cm0[idx];
            int d0, gres, redres, bres, dist;
            int rlo;

            if (v0 < red) {
                int t = (v0 - red) * 2;
                d0 = t * t;
                rlo = red + 0x18;
            } else {
                int hi = red + 0x18;
                if (hi < v0) {
                    int t = (v0 - hi) * 2;
                    d0 = t * t;
                    rlo = red;
                } else {
                    d0 = 0;
                    if (rmid < v0)
                        rlo = red;
                    else
                        rlo = red + 0x18;
                }
            }
            redres = (v0 - rlo) * 2;

            {
                int v1 = cm1[idx];
                if (v1 < green) {
                    int t = (v1 - green) * 3;
                    d0 += t * t;
                    gres = v1 - ghi;
                } else {
                    if (ghi < v1) {
                        int t = (v1 - ghi) * 3;
                        d0 += t * t;
                        gres = v1 - green;
                    } else if (v1 <= gmid) {
                        gres = v1 - ghi;
                    } else {
                        gres = v1 - green;
                    }
                }
            }
            {
                int v2 = cm2[idx];
                int vhi = blue + 0x18;
                if (v2 < blue) {
                    d0 += (v2 - blue) * (v2 - blue);
                    bres = v2 - vhi;
                } else if (vhi < v2) {
                    d0 += (v2 - vhi) * (v2 - vhi);
                    bres = v2 - blue;
                } else if (v2 <= bmid) {
                    bres = v2 - vhi;
                } else {
                    bres = v2 - blue;
                }
            }
            dist = redres * redres + gres * 3 * gres * 3 + bres * bres;
            errs[idx] = d0;
            if (dist < minv)
                minv = dist;
            idx++;
        } while (idx < n);
    }

    nout = 0;
    for (idx = 0; idx < n; idx++) {
        if (errs[idx] <= minv) {
            out[nout] = (u8)idx;
            nout++;
        }
    }
    return nout;
}

// @ 0x00865ec0
void FUN_00865ec0(struct jpeg_decompress_struct_s0086_5150* cinfo, int c0, int c1, int c2, int ncolors, u8* list, u8* out)
{
    int colorlist[128];
    int i;

    for (i = 0; i < 128; i++)
        colorlist[i] = 0x7fffffff;

    if (ncolors > 0) {
        int idx = 0;
        do {
            u8 color = list[idx];
            u8** cmap = cinfo->colormap;
            int gdiff = c1 - cmap[1][color];
            int bdiff = c2 - cmap[2][color];
            int rdiff = (c0 - cmap[0][color]) * 2;
            int dist = bdiff * bdiff + (gdiff * 3) * (gdiff * 3) + rdiff * rdiff;
            int stepB = (bdiff + 4) * 0x10;
            int stepR = (rdiff + 8) * 0x20;
            int* p = colorlist;
            u8*  o = out;
            int  outer = 3;
            int  d = dist;

            do {
                int inner = 7;
                int v = d;
                int sg = (gdiff * 9 + 0x12) * 8;
                do {
                    int v1, v2, v3;
                    if (v < p[0]) { p[0] = v; o[0] = color; }
                    v1 = v + stepB;
                    if (v1 < p[1]) { p[1] = v1; o[1] = color; }
                    v2 = v1 + stepB + 0x80;
                    if (v2 < p[2]) { p[2] = v2; o[2] = color; }
                    v3 = v2 + stepB + 0x100;
                    if (v3 < p[3]) { p[3] = v3; o[3] = color; }
                    v += sg;
                    sg += 0x120;
                    p += 4;
                    o += 4;
                    inner--;
                } while (inner >= 0);
                d += stepR;
                stepR += 0x200;
                outer--;
            } while (outer >= 0);
            idx++;
        } while (idx < ncolors);
    }
}

// @ 0x00866040
void FUN_00866040(int green, struct jpeg_decompress_struct_s0086_5150* cinfo, int red, int blue)
{
    struct cquantize_s_s0086_5150* cq = (struct cquantize_s_s0086_5150*)cinfo->cquantize;
    short** hist = (short**)((char*)cq + 0x18);
    int r2 = (red >> 2) * 0x20 + 4;
    int b2 = (blue >> 2) * 0x20 + 4;
    int g2 = ((green >> 3) * 0x20) + 2;
    u8 list[256];
    u8 best[128];
    int n;
    short** prow;
    int roff;
    u8* pb;
    int outer;

    n = FUN_00865ce0(cinfo, g2, r2, b2, list);
    FUN_00865ec0(cinfo, r2, g2, b2, n, list, best);

    prow = hist + (red >> 2);
    roff = ((green >> 3) * 0x100 + (blue >> 2) * 4);
    pb = best;
    outer = 4;
    do {
        short* p = (short*)((char*)prow[0] + roff * 2);
        int inner = 8;
        do {
            p[0] = (short)(pb[0] + 1);
            p[1] = (short)(pb[1] + 1);
            p[2] = (short)(pb[2] + 1);
            p[3] = (short)(pb[3] + 1);
            pb += 4;
            p = (short*)((char*)p + 0x40);
            inner--;
        } while (inner != 0);
        prow++;
        outer--;
    } while (outer != 0);
}

// @ 0x00866160
void FUN_00866160(struct jpeg_decompress_struct_s0086_5150* cinfo, u8** input_buf, u8** output_buf, int num_rows)
{
    struct cquantize_s_s0086_5150* cq = (struct cquantize_s_s0086_5150*)cinfo->cquantize;
    short** hist = (short**)((char*)cq + 0x18);
    int width = cinfo->output_width;
    int row = 0;

    if (num_rows <= 0)
        return;

    do {
        u8* inptr  = input_buf[row];
        u8* outptr = output_buf[row];
        int col = width;
        if (width != 0) {
            do {
                int r = inptr[0];
                int g = inptr[1];
                int b = inptr[2];
                short* cell;
                inptr += 3;
                cell = (short*)((char*)hist[r >> 3]
                                + ((g >> 2) * 0x20 + (b >> 3)) * 2);
                if (*cell == 0)
                    FUN_00866040(g >> 2, cinfo, r >> 3, b >> 3);
                *outptr++ = (u8)(*cell - 1);
                col--;
            } while (col != 0);
        }
        row++;
    } while (row < num_rows);
}

// @ 0x00866220
void FUN_00866220(Obj* self, int param_2, int* param_3, int param_4)
{
    int iVar1, iVar2, iVar4, iVar5, iVar7, iVar8, iVar9, iVar10;
    int iVar12, iVar13, iVar14, iVar17, iVar19, iVar21;
    uint32_t uVar15, uVar18, uVar20;
    int* piVar6;
    uint8_t* pbVar11;
    int16_t* psVar16;
    uint8_t* puStack_5c;
    int iStack_54, iStack_50, iStack_4c, iStack_44, iStack_40, iStack_3c, iStack_38, iStack_24;
    int stride;
    int* piStack_48;
    Ctx* c;

    iVar2 = self->f70;
    c = self->ctx;
    iVar4 = (int)c->f18;
    iVar5 = self->f544;
    piVar6 = self->f88;
    iVar7 = piVar6[0];
    iVar8 = piVar6[1];
    iVar9 = piVar6[2];
    iVar10 = (int)c->f28;
    if (0 < param_4) {
        piStack_48 = param_3;
        iStack_24 = param_4;
        do {
            iVar12 = 0;
            pbVar11 = *(uint8_t**)((int)piStack_48 + (param_2 - (int)param_3));
            puStack_5c = (uint8_t*)*piStack_48;
            if (c->f24 == 0) {
                psVar16 = (int16_t*)c->f20;
                iStack_38 = 1;
                stride = 3;
                c->f24 = 1;
            } else {
                pbVar11 = pbVar11 + iVar2 * 3 - 3;
                puStack_5c = puStack_5c + iVar2 - 1;
                psVar16 = (int16_t*)((char*)c->f20 + (iVar2 * 3 + 3) * 2);
                iStack_38 = -1;
                stride = -3;
                c->f24 = 0;
            }
            iVar17 = 0;
            iVar14 = 0;
            iStack_3c = 0;
            iStack_40 = 0;
            iStack_44 = 0;
            iStack_4c = 0;
            iStack_50 = 0;
            iStack_54 = 0;
            for (iVar1 = iVar2; iVar1 != 0; iVar1 = iVar1 - 1) {
                uVar18 = *(uint8_t*)(*(int*)(iVar10 + ((psVar16[stride] + 8 + iVar17) >> 4) * 4) + (uint32_t)*pbVar11 + iVar5);
                uVar20 = *(uint8_t*)(*(int*)(iVar10 + ((psVar16[stride + 1] + 8 + iVar12) >> 4) * 4) + (uint32_t)pbVar11[1] + iVar5);
                uVar15 = *(uint8_t*)(*(int*)(iVar10 + ((psVar16[stride + 2] + 8 + iVar14) >> 4) * 4) + (uint32_t)pbVar11[2] + iVar5);
                iVar13 = (int)uVar15 >> 3;
                iVar14 = ((int)uVar20 >> 2) * 0x20 + iVar13;
                iVar17 = (int)uVar18 >> 3;
                iVar12 = *(int*)(iVar4 + iVar17 * 4);
                if (*(int16_t*)(iVar12 + iVar14 * 2) == 0) {
                    FUN_00866040(self, iVar17, iVar13);
                }
                iVar12 = (int)(*(uint16_t*)(iVar12 + iVar14 * 2) - 1);
                *puStack_5c = (char)iVar12;
                iVar19 = (int)uVar18 - *(uint8_t*)(iVar12 + iVar7);
                iVar21 = (int)uVar20 - *(uint8_t*)(iVar12 + iVar8);
                iVar13 = (int)uVar15 - *(uint8_t*)(iVar12 + iVar9);
                psVar16[0] = (int16_t)(iStack_54 + iVar19 * 3);
                iStack_54 = iStack_44 + iVar19 * 5;
                iVar17 = iVar19 * 7;
                psVar16[1] = (int16_t)(iStack_50 + iVar21 * 3);
                iStack_50 = iStack_40 + iVar21 * 5;
                iVar12 = iVar21 * 7;
                psVar16[2] = (int16_t)(iStack_4c + iVar13 * 3);
                iStack_4c = iStack_3c + iVar13 * 5;
                puStack_5c = puStack_5c + iStack_38;
                iVar14 = iVar13 * 7;
                pbVar11 = pbVar11 + stride;
                psVar16 = psVar16 + stride;
                iStack_3c = iVar13;
                iStack_40 = iVar21;
                iStack_44 = iVar19;
            }
            piStack_48 = piStack_48 + 1;
            *psVar16 = (int16_t)iStack_54;
            psVar16[1] = (int16_t)iStack_50;
            iStack_24 = iStack_24 - 1;
            psVar16[2] = (int16_t)iStack_4c;
        } while (iStack_24 != 0);
    }
    return;
}

// @ 0x008664e0
void FUN_008664e0(Obj* self)
{
    Ctx* c;
    int* piVar2;
    int* piVar5;
    int iVar1;
    int iVar4;
    uint32_t uVar3;

    c = self->ctx;
    piVar2 = (int*)((char*)((AFn)self->alloc[0])(self, 1, 0x7fc) + 0x3fc);
    c->f28 = piVar2;
    iVar4 = 0;
    uVar3 = 0;
    iVar1 = 0;
    piVar5 = piVar2;
    do {
        piVar2[uVar3] = iVar4;
        *piVar5 = iVar1;
        uVar3 = uVar3 + 1;
        piVar5 = piVar5 + -1;
        iVar4 = iVar4 + 1;
        iVar1 = iVar1 + -1;
    } while ((int)uVar3 < 0x10);
    if ((int)uVar3 < 0x30) {
        piVar5 = piVar2 + -uVar3;
        do {
            piVar2[uVar3] = iVar4;
            *piVar5 = -iVar4;
            uVar3 = uVar3 + 1;
            piVar5 = piVar5 + -1;
            iVar4 = iVar4 + (~uVar3 & 1);
        } while ((int)uVar3 < 0x30);
    }
    if ((int)uVar3 <= 0xff) {
        piVar5 = piVar2 + -uVar3;
        do {
            piVar2[uVar3] = iVar4;
            *piVar5 = -iVar4;
            uVar3 = uVar3 + 1;
            piVar5 = piVar5 + -1;
        } while ((int)uVar3 <= 0xff);
    }
    return;
}

// @ 0x00866580
void FUN_00866580(Obj* self)
{
    Ctx* c = self->ctx;

    self->f88 = (int*)c->f10;
    FUN_00865c50(c->f14);
    c->f1c = 1;
    return;
}

// @ 0x008666e0
void FUN_008666e0(Obj* self)
{
    self->ctx->f1c = 1;
    return;
}

// @ 0x00866700
void FUN_00866700(Obj* self)
{
    Ctx* c;
    int iVar3;

    c = (Ctx*)((AFn)self->alloc[0])(self, 1, 0x2c);
    self->ctx = c;
    c->f00 = (void*)&FUN_008665b0;
    c->f0c = (void*)&FUN_008666e0;
    c->f20 = 0;
    c->f28 = 0;
    if (self->f78 != 3) {
        *(int*)((char*)self->m00 + 0x14) = 0x2e;
        ((void(__cdecl*)(void*))self->m00[0])(self);
    }
    c->f18 = (uint32_t*)((AFn)self->alloc[0])(self, 1, 0x80);
    iVar3 = 0;
    do {
        *(void**)((char*)c->f18 + iVar3) = (void*)((AFn)self->alloc[1])(self, 1, 0x1000);
        iVar3 = iVar3 + 4;
    } while (iVar3 < 0x80);
    c->f1c = 1;
    if (self->f6c == 0) {
        c->f10 = 0;
    } else {
        iVar3 = self->f60;
        if (iVar3 < 8) {
            *(int*)((char*)self->m00 + 0x14) = 0x37;
            *(int*)((char*)self->m00 + 0x18) = 8;
            ((void(__cdecl*)(void*))self->m00[0])(self);
        }
        if (0x100 < iVar3) {
            *(int*)((char*)self->m00 + 0x14) = 0x38;
            *(int*)((char*)self->m00 + 0x18) = 0x100;
            ((void(__cdecl*)(void*))self->m00[0])(self);
        }
        c->f10 = (int)((AFn3)self->alloc[2])(self, 1, iVar3, 3);
        c->f14 = iVar3;
    }
    if (self->f58 != 0) {
        self->f58 = 2;
    }
    if (self->f58 == 2) {
        c->f20 = (int*)((AFn)self->alloc[1])(self, 1, (self->f70 + 2) * 6);
        FUN_008664e0(self);
        return;
    }
    return;
}

// @ 0x00866b80
uint32_t crc32_little(uint32_t crc, const uint8_t* buf, uint32_t len)
{
    uint32_t c = ~crc;

    while (len != 0 && (((uintptr_t)buf & 3) != 0)) {
        c = (c >> 8) ^ g_0141e9c0[(*buf ^ c) & 0xff];
        buf++;
        len--;
    }
    while (len >= 0x20) {
        uint32_t n = len >> 5;
        do {
            c = c ^ *(const uint32_t*)buf;
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff] ^ *(const uint32_t*)buf);
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff] ^ *(const uint32_t*)buf);
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff] ^ *(const uint32_t*)buf);
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff] ^ *(const uint32_t*)buf);
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff] ^ *(const uint32_t*)buf);
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff] ^ *(const uint32_t*)buf);
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff] ^ *(const uint32_t*)buf);
            buf += 4;
            len -= 0x20;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff]);
            n--;
        } while (n != 0);
    }
    while (len >= 4) {
        uint32_t n = len >> 2;
        do {
            c = c ^ *(const uint32_t*)buf;
            buf += 4;
            c = (g_0141edc0[(c >> 16) & 0xff] ^ g_0141f1c0[(c >> 8) & 0xff] ^
                 g_0141e9c0[c >> 24] ^ g_0141f5c0[c & 0xff]);
            len -= 4;
            n--;
        } while (n != 0);
    }
    while (len != 0) {
        c = (c >> 8) ^ g_0141e9c0[(*buf ^ c) & 0xff];
        buf++;
        len--;
    }
    return ~c;
}

// @ 0x0086d710
void png_destroy_struct_2(png_voidp struct_ptr, png_free_ptr free_fn, png_voidp mem_ptr)
{
   if (struct_ptr != 0)
   {
      if (free_fn != 0)
      {
         png_struct_def dummy_struct;
         png_structp png_ptr = &dummy_struct;
         png_ptr->mem_ptr = mem_ptr;
         (*free_fn)(png_ptr, struct_ptr);
         return;
      }
      free(struct_ptr);
   }
}
