// src/game/UTFSpore_Win32/pngrtran.cpp -- migrated from slice(s) s00871d50, s0086d090 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/pngrtran.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>

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
#define PNG_COLOR_MASK_COLOR 2
#define PNG_BACKGROUND 0x0080
#define PNG_16_TO_8 0x0400
#define PNG_RGB_TO_GRAY 0x600000L
#define PNG_MAX_GAMMA_8 11
extern "C" png_voidp png_malloc(png_structp png_ptr, png_uint_32 size);   // 0x0086d7f0
static const int png_gamma_shift[] = { 0x10, 0x21, 0x42, 0x84, 0x110, 0x248, 0x550, 0xff0, 0x00 };   // 0x014223bc
// ---- items of slice s0086d090 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" png_voidp png_malloc(png_structp png_ptr, png_uint_32 size);   // 0x0086d7f0

// ---- items of slice s00871d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
#ifndef NULL
#define NULL 0
#endif
typedef unsigned int png_uint_32_s0087_1d50;
typedef int png_fixed_point;
typedef char* png_charp;
typedef const char* png_const_charp;
typedef unsigned char* png_bytep_s0087_1d50;
struct z_stream_s_s0087_1d50 {
    png_bytep_s0087_1d50 next_in;       png_uint_32_s0087_1d50 avail_in;  unsigned long total_in;
    png_bytep_s0087_1d50 next_out;      png_uint_32_s0087_1d50 avail_out; unsigned long total_out;
    png_charp msg;           void* state;           void* zalloc;
    void* zfree;             void* opaque;
    int data_type;           unsigned long adler;   unsigned long reserved;
};
struct png_color_def { png_byte red, green, blue; };
typedef png_color_def png_color_s0087_1d50;
typedef png_color_s0087_1d50* png_colorp_s0087_1d50;
struct png_color_16_def { png_byte index; png_uint_16 red, green, blue, gray; };
typedef png_color_16_def png_color_16_s0087_1d50;
typedef png_color_16_s0087_1d50* png_color_16p;
struct png_color_8_def { png_byte red, green, blue, gray, alpha; };
typedef png_color_8_def png_color_8_s0087_1d50;
typedef png_color_8_s0087_1d50* png_color_8p;
struct png_row_info_def {
    png_uint_32_s0087_1d50 width;
    png_uint_32_s0087_1d50 rowbytes;
    png_byte color_type;
    png_byte bit_depth;
    png_byte channels;
    png_byte pixel_depth;
};
typedef png_row_info_def png_row_info_s0087_1d50;
typedef png_row_info_s0087_1d50* png_row_infop;
struct png_struct_def_s0087_1d50;
typedef png_struct_def_s0087_1d50* png_structp_s0087_1d50;
typedef void (*png_user_transform_ptr)(png_structp_s0087_1d50, png_row_infop, png_bytep_s0087_1d50);
struct png_struct_def_s0087_1d50 {
    int jmpbuf[16];                                  // +0x00
    png_fnptr error_fn;                              // +0x40
    png_fnptr warning_fn;                            // +0x44
    png_voidp error_ptr;                             // +0x48
    png_fnptr write_data_fn;                         // +0x4c
    png_fnptr read_data_fn;                          // +0x50
    png_voidp io_ptr;                                // +0x54
    png_user_transform_ptr read_user_transform_fn;   // +0x58
    png_fnptr write_user_transform_fn;               // +0x5c
    png_voidp user_transform_ptr;                    // +0x60
    png_byte user_transform_depth;                   // +0x64
    png_byte user_transform_channels;                // +0x65
    png_uint_32_s0087_1d50 mode;                                // +0x68
    png_uint_32_s0087_1d50 flags;                               // +0x6c
    png_uint_32_s0087_1d50 transformations;                     // +0x70
    z_stream_s_s0087_1d50 zstream;                              // +0x74
    png_bytep_s0087_1d50 zbuf;                                  // +0xac
    png_size_t zbuf_size;                            // +0xb0
    int zlib_level;                                  // +0xb4
    int zlib_method;                                 // +0xb8
    int zlib_window_bits;                            // +0xbc
    int zlib_mem_level;                              // +0xc0
    int zlib_strategy;                               // +0xc4
    png_uint_32_s0087_1d50 width;                               // +0xc8
    png_uint_32_s0087_1d50 height;                              // +0xcc
    png_uint_32_s0087_1d50 num_rows;                            // +0xd0
    png_uint_32_s0087_1d50 usr_width;                           // +0xd4
    png_uint_32_s0087_1d50 rowbytes;                            // +0xd8
    png_uint_32_s0087_1d50 irowbytes;                           // +0xdc
    png_uint_32_s0087_1d50 iwidth;                              // +0xe0
    png_uint_32_s0087_1d50 row_number;                          // +0xe4
    png_bytep_s0087_1d50 prev_row;                              // +0xe8
    png_bytep_s0087_1d50 row_buf;                               // +0xec
    png_bytep_s0087_1d50 sub_row;                               // +0xf0
    png_bytep_s0087_1d50 up_row;                                // +0xf4
    png_bytep_s0087_1d50 avg_row;                               // +0xf8
    png_bytep_s0087_1d50 paeth_row;                             // +0xfc
    png_row_info_s0087_1d50 row_info;                           // +0x100
    png_uint_32_s0087_1d50 idat_size;                           // +0x10c
    png_uint_32_s0087_1d50 crc;                                 // +0x110
    png_colorp_s0087_1d50 palette;                              // +0x114
    png_uint_16 num_palette;                         // +0x118
    png_uint_16 num_trans;                           // +0x11a
    png_byte chunk_name[5];                          // +0x11c
    png_byte compression;                            // +0x121
    png_byte filter;                                 // +0x122
    png_byte interlaced;                             // +0x123
    png_byte pass;                                   // +0x124
    png_byte do_filter;                              // +0x125
    png_byte color_type;                             // +0x126
    png_byte bit_depth;                              // +0x127
    png_byte usr_bit_depth;                          // +0x128
    png_byte pixel_depth;                            // +0x129
    png_byte channels;                               // +0x12a
    png_byte usr_channels;                           // +0x12b
    png_byte sig_bytes;                              // +0x12c
    png_uint_16 filler;                              // +0x12e
    png_byte background_gamma_type;                  // +0x130
    float background_gamma;                          // +0x134
    png_color_16_s0087_1d50 background;                         // +0x138
    png_color_16_s0087_1d50 background_1;                       // +0x142
    png_fnptr output_flush_fn;                       // +0x14c
    png_uint_32_s0087_1d50 flush_dist;                          // +0x150
    png_uint_32_s0087_1d50 flush_rows;                          // +0x154
    int gamma_shift;                                 // +0x158
    float gamma;                                     // +0x15c
    float screen_gamma;                              // +0x160
    png_bytep_s0087_1d50 gamma_table;                           // +0x164
    png_bytep_s0087_1d50 gamma_from_1;                          // +0x168
    png_bytep_s0087_1d50 gamma_to_1;                            // +0x16c
    png_uint_16** gamma_16_table;                    // +0x170
    png_uint_16** gamma_16_from_1;                   // +0x174
    png_uint_16** gamma_16_to_1;                     // +0x178
    png_color_8_s0087_1d50 sig_bit;                             // +0x17c
    png_color_8_s0087_1d50 shift;                               // +0x181
    png_bytep_s0087_1d50 trans;                                 // +0x188
    png_color_16_s0087_1d50 trans_values;                       // +0x18c
    png_fnptr read_row_fn;                           // +0x198
    png_fnptr write_row_fn;                          // +0x19c
    png_fnptr info_fn;                               // +0x1a0
    png_fnptr row_fn;                                // +0x1a4
    png_fnptr end_fn;                                // +0x1a8
    png_bytep_s0087_1d50 save_buffer_ptr;                       // +0x1ac
    png_bytep_s0087_1d50 save_buffer;                           // +0x1b0
    png_bytep_s0087_1d50 current_buffer_ptr;                    // +0x1b4
    png_bytep_s0087_1d50 current_buffer;                        // +0x1b8
    png_uint_32_s0087_1d50 push_length;                         // +0x1bc
    png_uint_32_s0087_1d50 skip_length;                         // +0x1c0
    png_size_t save_buffer_size;                     // +0x1c4
    png_size_t save_buffer_max;                      // +0x1c8
    png_size_t buffer_size;                          // +0x1cc
    png_size_t current_buffer_size;                  // +0x1d0
    int process_mode;                                // +0x1d4
    int cur_palette;                                 // +0x1d8
    png_size_t current_text_size;                    // +0x1dc
    png_size_t current_text_left;                    // +0x1e0
    png_charp current_text;                          // +0x1e4
    png_charp current_text_ptr;                      // +0x1e8
    png_bytep_s0087_1d50 palette_lookup;                        // +0x1ec
    png_bytep_s0087_1d50 dither_index;                          // +0x1f0
    png_uint_16* hist;                               // +0x1f4
    png_byte heuristic_method;                       // +0x1f8
    png_byte num_prev_filters;                       // +0x1f9
    png_bytep_s0087_1d50 prev_filters;                          // +0x1fc
    png_uint_16* filter_weights;                     // +0x200
    png_uint_16* inv_filter_weights;                 // +0x204
    png_uint_16* filter_costs;                       // +0x208
    png_uint_16* inv_filter_costs;                   // +0x20c
    png_charp time_buffer;                           // +0x210
    png_uint_32_s0087_1d50 free_me;                             // +0x214
    png_voidp user_chunk_ptr;                        // +0x218
    png_fnptr read_user_chunk_fn;                    // +0x21c
    int num_chunk_list;                              // +0x220
    png_bytep_s0087_1d50 chunk_list;                            // +0x224
    png_byte rgb_to_gray_status;                     // +0x228
    png_uint_16 rgb_to_gray_red_coeff;               // +0x229
    png_uint_16 rgb_to_gray_green_coeff;             // +0x22b
    png_uint_16 rgb_to_gray_blue_coeff;              // +0x22d
    png_uint_32_s0087_1d50 mng_features_permitted;              // +0x230
    png_fixed_point int_gamma;                       // +0x234
    png_byte filter_type;                            // +0x238
    png_byte mmx_bitdepth_threshold;                 // +0x239
    png_uint_32_s0087_1d50 mmx_rowbytes_threshold;              // +0x23c
    png_uint_32_s0087_1d50 asm_flags;                           // +0x240
    png_voidp mem_ptr;                               // +0x244
    png_fnptr malloc_fn;                             // +0x248
    png_fnptr free_fn;                               // +0x24c
    png_bytep_s0087_1d50 big_row_buf;                           // +0x250
    png_bytep_s0087_1d50 dither_sort;                           // +0x254
    png_bytep_s0087_1d50 index_to_palette;                      // +0x258
    png_bytep_s0087_1d50 palette_to_index;                      // +0x25c
    png_byte compression_type;                       // +0x260
    png_uint_32_s0087_1d50 user_width_max;                      // +0x264
    png_uint_32_s0087_1d50 user_height_max;                     // +0x268
};
#define png_snprintf _snprintf
#define PNG_FLAG_ROW_INIT     0x0040
#define PNG_FLAG_FILLER_AFTER 0x0080
#define PNG_FLAG_STRIP_ALPHA  0x400000L
#define PNG_COLOR_MASK_PALETTE 1
#define PNG_COLOR_MASK_ALPHA   4
#define PNG_COLOR_TYPE_PALETTE   (PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_PALETTE)
#define PNG_BGR                0x0001
#define PNG_PACK               0x0004
#define PNG_SHIFT              0x0008
#define PNG_SWAP_BYTES         0x0010
#define PNG_INVERT_MONO        0x0020
#define PNG_DITHER             0x0040
#define PNG_EXPAND             0x1000
#define PNG_GAMMA              0x2000
#define PNG_GRAY_TO_RGB        0x4000
#define PNG_FILLER             0x8000L
#define PNG_PACKSWAP           0x10000L
#define PNG_SWAP_ALPHA         0x20000L
#define PNG_INVERT_ALPHA       0x80000L
#define PNG_USER_TRANSFORM     0x100000L
#define PNG_RGB_TO_GRAY_ERR    0x200000L
#define PNG_RGB_TO_GRAY_WARN   0x400000L
#define PNG_EXPAND_tRNS        0x2000000L
#define PNG_BACKGROUND_IS_GRAY 0x800
#define PNG_ROWBYTES(pixel_bits, width) \
    ((pixel_bits) >= 8 ? \
    ((width) * (((png_uint_32_s0087_1d50)(pixel_bits)) >> 3)) : \
    (( ((width) * ((png_uint_32_s0087_1d50)(pixel_bits))) + 7) >> 3) )
extern "C" void png_error(png_structp_s0087_1d50 png_ptr, png_const_charp error_message);
extern "C" void png_warning(png_structp_s0087_1d50 png_ptr, png_const_charp warning_message);
extern "C" void png_do_expand_palette(png_row_infop row_info, png_bytep_s0087_1d50 row, png_colorp_s0087_1d50 palette,
png_bytep_s0087_1d50 trans, png_uint_16 num_trans);
extern "C" void png_do_expand(png_row_infop row_info, png_bytep_s0087_1d50 row, png_color_16p trans_value);
extern "C" void png_do_strip_filler(png_row_infop row_info, png_bytep_s0087_1d50 row, png_uint_32_s0087_1d50 flags);
extern "C" int png_do_rgb_to_gray(png_structp_s0087_1d50 png_ptr, png_row_infop row_info, png_bytep_s0087_1d50 row);
extern "C" void png_do_gray_to_rgb(png_row_infop row_info, png_bytep_s0087_1d50 row);
extern "C" void png_do_background(png_row_infop row_info, png_bytep_s0087_1d50 row, png_color_16p trans_values,
png_color_16p background, png_color_16p background_1, png_bytep_s0087_1d50 gamma_table,
png_bytep_s0087_1d50 gamma_from_1, png_bytep_s0087_1d50 gamma_to_1, png_uint_16pp gamma_16_table,
png_uint_16pp gamma_16_from_1, png_uint_16pp gamma_16_to_1, int gamma_shift);
extern "C" void png_do_gamma(png_row_infop row_info, png_bytep_s0087_1d50 row, png_bytep_s0087_1d50 gamma_table,
png_uint_16pp gamma_16_table, int gamma_shift);
extern "C" void png_do_chop(png_row_infop row_info, png_bytep_s0087_1d50 row);
extern "C" void png_do_dither(png_row_infop row_info, png_bytep_s0087_1d50 row, png_bytep_s0087_1d50 palette_lookup,
png_bytep_s0087_1d50 dither_lookup);
extern "C" void png_do_invert(png_row_infop row_info, png_bytep_s0087_1d50 row);
extern "C" void png_do_unshift(png_row_infop row_info, png_bytep_s0087_1d50 row, png_color_8p sig_bits);
extern "C" void png_do_unpack(png_row_infop row_info, png_bytep_s0087_1d50 row);
extern "C" void png_do_bgr(png_row_infop row_info, png_bytep_s0087_1d50 row);
extern "C" void png_do_packswap(png_row_infop row_info, png_bytep_s0087_1d50 row);
extern "C" void png_do_read_filler(png_row_infop row_info, png_bytep_s0087_1d50 row, png_uint_32_s0087_1d50 filler,
png_uint_32_s0087_1d50 flags);
extern "C" void png_do_read_invert_alpha(png_row_infop row_info, png_bytep_s0087_1d50 row);
extern "C" void png_do_read_swap_alpha(png_row_infop row_info, png_bytep_s0087_1d50 row);
extern "C" void png_do_swap(png_row_infop row_info, png_bytep_s0087_1d50 row);
extern "C" void png_do_read_transformations(png_structp_s0087_1d50 png_ptr);
// ---- items of slice s00871d50 end

// @ 0x00870860
void png_build_gamma_table(png_structp png_ptr)
{
    if (png_ptr->bit_depth <= 8) {
        int i;
        double g;

        if (png_ptr->screen_gamma > .000001)
            g = 1.0 / (png_ptr->gamma * png_ptr->screen_gamma);
        else
            g = 1.0;

        png_ptr->gamma_table = (png_bytep)png_malloc(png_ptr, (png_uint_32)256);

        for (i = 0; i < 256; i++) {
            png_ptr->gamma_table[i] = (png_byte)(pow((double)i / 255.0, g) * 255.0 + .5);
        }

        if (png_ptr->transformations & (PNG_BACKGROUND | PNG_RGB_TO_GRAY)) {
            g = 1.0 / (png_ptr->gamma);

            png_ptr->gamma_to_1 = (png_bytep)png_malloc(png_ptr, (png_uint_32)256);

            for (i = 0; i < 256; i++) {
                png_ptr->gamma_to_1[i] = (png_byte)(pow((double)i / 255.0, g) * 255.0 + .5);
            }

            png_ptr->gamma_from_1 = (png_bytep)png_malloc(png_ptr, (png_uint_32)256);

            if (png_ptr->screen_gamma > 0.000001)
                g = 1.0 / png_ptr->screen_gamma;
            else
                g = png_ptr->gamma;

            for (i = 0; i < 256; i++) {
                png_ptr->gamma_from_1[i] = (png_byte)(pow((double)i / 255.0, g) * 255.0 + .5);
            }
        }
    } else {
        double g;
        int i, j, shift, num;
        int sig_bit;
        png_uint_32 ig;

        if (png_ptr->color_type & PNG_COLOR_MASK_COLOR) {
            sig_bit = (int)png_ptr->sig_bit.red;
            if ((int)png_ptr->sig_bit.green > sig_bit)
                sig_bit = png_ptr->sig_bit.green;
            if ((int)png_ptr->sig_bit.blue > sig_bit)
                sig_bit = png_ptr->sig_bit.blue;
        } else {
            sig_bit = (int)png_ptr->sig_bit.gray;
        }

        if (sig_bit > 0)
            shift = 16 - sig_bit;
        else
            shift = 0;

        if (png_ptr->transformations & PNG_16_TO_8) {
            if (shift < (16 - PNG_MAX_GAMMA_8))
                shift = (16 - PNG_MAX_GAMMA_8);
        }

        if (shift > 8)
            shift = 8;
        if (shift < 0)
            shift = 0;

        png_ptr->gamma_shift = (png_byte)shift;

        num = (1 << (8 - shift));

        if (png_ptr->screen_gamma > .000001)
            g = 1.0 / (png_ptr->gamma * png_ptr->screen_gamma);
        else
            g = 1.0;

        png_ptr->gamma_16_table = (png_uint_16pp)png_malloc(png_ptr, (png_uint_32)(num * sizeof(png_uint_16p)));

        if (png_ptr->transformations & (PNG_16_TO_8 | PNG_BACKGROUND)) {
            double fin, fout;
            png_uint_32 last, max;

            for (i = 0; i < num; i++) {
                png_ptr->gamma_16_table[i] = (png_uint_16p)png_malloc(png_ptr, (png_uint_32)(256 * sizeof(png_uint_16)));
            }

            g = 1.0 / g;
            last = 0;
            for (i = 0; i < 256; i++) {
                fout = ((double)i + 0.5) / 256.0;
                fin = pow(fout, g);
                max = (png_uint_32)(fin * (double)((png_uint_32)num << 8));
                while (last <= max) {
                    png_ptr->gamma_16_table[(int)(last & (0xff >> shift))][(int)(last >> (8 - shift))] =
                        (png_uint_16)((png_uint_16)i | ((png_uint_16)i << 8));
                    last++;
                }
            }
            while (last < ((png_uint_32)num << 8)) {
                png_ptr->gamma_16_table[(int)(last & (0xff >> shift))][(int)(last >> (8 - shift))] =
                    (png_uint_16)65535L;
                last++;
            }
        } else {
            for (i = 0; i < num; i++) {
                png_ptr->gamma_16_table[i] = (png_uint_16p)png_malloc(png_ptr, (png_uint_32)(256 * sizeof(png_uint_16)));

                ig = (((png_uint_32)i * (png_uint_32)png_gamma_shift[shift]) >> 4);
                for (j = 0; j < 256; j++) {
                    png_ptr->gamma_16_table[i][j] = (png_uint_16)(pow((double)ig / 65535.0, g) * 65535.0 + .5);
                    ig += 256;
                }
            }
        }

        if (png_ptr->transformations & (PNG_BACKGROUND | PNG_RGB_TO_GRAY)) {
            g = 1.0 / (png_ptr->gamma);

            png_ptr->gamma_16_to_1 = (png_uint_16pp)png_malloc(png_ptr, (png_uint_32)(num * sizeof(png_uint_16p)));

            for (i = 0; i < num; i++) {
                png_ptr->gamma_16_to_1[i] = (png_uint_16p)png_malloc(png_ptr, (png_uint_32)(256 * sizeof(png_uint_16)));

                ig = (((png_uint_32)i * (png_uint_32)png_gamma_shift[shift]) >> 4);
                for (j = 0; j < 256; j++) {
                    png_ptr->gamma_16_to_1[i][j] = (png_uint_16)(pow((double)ig / 65535.0, g) * 65535.0 + .5);
                    ig += 256;
                }
            }

            if (png_ptr->screen_gamma > 0.000001)
                g = 1.0 / png_ptr->screen_gamma;
            else
                g = png_ptr->gamma;

            png_ptr->gamma_16_from_1 = (png_uint_16pp)png_malloc(png_ptr, (png_uint_32)(num * sizeof(png_uint_16p)));

            for (i = 0; i < num; i++) {
                png_ptr->gamma_16_from_1[i] = (png_uint_16p)png_malloc(png_ptr, (png_uint_32)(256 * sizeof(png_uint_16)));

                ig = (((png_uint_32)i * (png_uint_32)png_gamma_shift[shift]) >> 4);
                for (j = 0; j < 256; j++) {
                    png_ptr->gamma_16_from_1[i][j] = (png_uint_16)(pow((double)ig / 65535.0, g) * 65535.0 + .5);
                    ig += 256;
                }
            }
        }
    }
}

// @ 0x00871d50
void /* PRIVATE */ png_do_read_transformations(png_structp_s0087_1d50 png_ptr)
{
   if (png_ptr->row_buf == NULL)
   {
      char msg[50];

      png_snprintf(msg, 50,
         "NULL row buffer for row %ld, pass %d", png_ptr->row_number,
         png_ptr->pass);
      png_error(png_ptr, msg);
   }
   if (!(png_ptr->flags & PNG_FLAG_ROW_INIT))
      /* Application has failed to call either png_read_start_image()
       * or png_read_update_info() after setting transforms that expand
       * pixels.  This check added to libpng-1.2.19 */
      png_error(png_ptr, "Uninitialized row");

   if (png_ptr->transformations & PNG_EXPAND)
   {
      if (png_ptr->row_info.color_type == PNG_COLOR_TYPE_PALETTE)
      {
         png_do_expand_palette(&(png_ptr->row_info), png_ptr->row_buf + 1,
            png_ptr->palette, png_ptr->trans, png_ptr->num_trans);
      }
      else
      {
         if (png_ptr->num_trans &&
             (png_ptr->transformations & PNG_EXPAND_tRNS))
            png_do_expand(&(png_ptr->row_info), png_ptr->row_buf + 1,
               &(png_ptr->trans_values));
         else
            png_do_expand(&(png_ptr->row_info), png_ptr->row_buf + 1,
               NULL);
      }
   }

   if (png_ptr->flags & PNG_FLAG_STRIP_ALPHA)
      png_do_strip_filler(&(png_ptr->row_info), png_ptr->row_buf + 1,
         PNG_FLAG_FILLER_AFTER | (png_ptr->flags & PNG_FLAG_STRIP_ALPHA));

   if (png_ptr->transformations & PNG_RGB_TO_GRAY)
   {
      int rgb_error =
         png_do_rgb_to_gray(png_ptr, &(png_ptr->row_info), png_ptr->row_buf + 1);
      if(rgb_error)
      {
         png_ptr->rgb_to_gray_status=1;
         if((png_ptr->transformations & PNG_RGB_TO_GRAY) ==
             PNG_RGB_TO_GRAY_WARN)
            png_warning(png_ptr, "png_do_rgb_to_gray found nongray pixel");
         if((png_ptr->transformations & PNG_RGB_TO_GRAY) ==
             PNG_RGB_TO_GRAY_ERR)
            png_error(png_ptr, "png_do_rgb_to_gray found nongray pixel");
      }
   }

   /* if gray -> RGB, do so now only if background is non-gray; else do later
    * for performance reasons */
   if ((png_ptr->transformations & PNG_GRAY_TO_RGB) &&
       !(png_ptr->mode & PNG_BACKGROUND_IS_GRAY))
      png_do_gray_to_rgb(&(png_ptr->row_info), png_ptr->row_buf + 1);

   if ((png_ptr->transformations & PNG_BACKGROUND) &&
      ((png_ptr->num_trans != 0 ) ||
      (png_ptr->color_type & PNG_COLOR_MASK_ALPHA)))
      png_do_background(&(png_ptr->row_info), png_ptr->row_buf + 1,
         &(png_ptr->trans_values), &(png_ptr->background),
         &(png_ptr->background_1),
         png_ptr->gamma_table, png_ptr->gamma_from_1,
         png_ptr->gamma_to_1, png_ptr->gamma_16_table,
         png_ptr->gamma_16_from_1, png_ptr->gamma_16_to_1,
         png_ptr->gamma_shift
);

   if ((png_ptr->transformations & PNG_GAMMA) &&
      !((png_ptr->transformations & PNG_BACKGROUND) &&
      ((png_ptr->num_trans != 0) ||
      (png_ptr->color_type & PNG_COLOR_MASK_ALPHA))) &&
      (png_ptr->color_type != PNG_COLOR_TYPE_PALETTE))
      png_do_gamma(&(png_ptr->row_info), png_ptr->row_buf + 1,
         png_ptr->gamma_table, png_ptr->gamma_16_table,
         png_ptr->gamma_shift);

   if (png_ptr->transformations & PNG_16_TO_8)
      png_do_chop(&(png_ptr->row_info), png_ptr->row_buf + 1);

   if (png_ptr->transformations & PNG_DITHER)
   {
      png_do_dither((png_row_infop)&(png_ptr->row_info), png_ptr->row_buf + 1,
         png_ptr->palette_lookup, png_ptr->dither_index);
      if(png_ptr->row_info.rowbytes == (png_uint_32_s0087_1d50)0)
         png_error(png_ptr, "png_do_dither returned rowbytes=0");
   }

   if (png_ptr->transformations & PNG_INVERT_MONO)
      png_do_invert(&(png_ptr->row_info), png_ptr->row_buf + 1);

   if (png_ptr->transformations & PNG_SHIFT)
      png_do_unshift(&(png_ptr->row_info), png_ptr->row_buf + 1,
         &(png_ptr->shift));

   if (png_ptr->transformations & PNG_PACK)
      png_do_unpack(&(png_ptr->row_info), png_ptr->row_buf + 1);

   if (png_ptr->transformations & PNG_BGR)
      png_do_bgr(&(png_ptr->row_info), png_ptr->row_buf + 1);

   if (png_ptr->transformations & PNG_PACKSWAP)
      png_do_packswap(&(png_ptr->row_info), png_ptr->row_buf + 1);

   /* if gray -> RGB, do so now only if we did not do so above */
   if ((png_ptr->transformations & PNG_GRAY_TO_RGB) &&
       (png_ptr->mode & PNG_BACKGROUND_IS_GRAY))
      png_do_gray_to_rgb(&(png_ptr->row_info), png_ptr->row_buf + 1);

   if (png_ptr->transformations & PNG_FILLER)
      png_do_read_filler(&(png_ptr->row_info), png_ptr->row_buf + 1,
         (png_uint_32_s0087_1d50)png_ptr->filler, png_ptr->flags);

   if (png_ptr->transformations & PNG_INVERT_ALPHA)
      png_do_read_invert_alpha(&(png_ptr->row_info), png_ptr->row_buf + 1);

   if (png_ptr->transformations & PNG_SWAP_ALPHA)
      png_do_read_swap_alpha(&(png_ptr->row_info), png_ptr->row_buf + 1);

   if (png_ptr->transformations & PNG_SWAP_BYTES)
      png_do_swap(&(png_ptr->row_info), png_ptr->row_buf + 1);

   if (png_ptr->transformations & PNG_USER_TRANSFORM)
    {
      if(png_ptr->read_user_transform_fn != NULL)
        (*(png_ptr->read_user_transform_fn)) /* user read transform function */
          (png_ptr,                    /* png_ptr */
           &(png_ptr->row_info),       /* row_info:     */
           png_ptr->row_buf + 1);      /* start of pixel data for row */
      if(png_ptr->user_transform_depth)
         png_ptr->row_info.bit_depth = png_ptr->user_transform_depth;
      if(png_ptr->user_transform_channels)
         png_ptr->row_info.channels = png_ptr->user_transform_channels;
      png_ptr->row_info.pixel_depth = (png_byte)(png_ptr->row_info.bit_depth *
         png_ptr->row_info.channels);
      png_ptr->row_info.rowbytes = PNG_ROWBYTES(png_ptr->row_info.pixel_depth,
         png_ptr->row_info.width);
    }

}
