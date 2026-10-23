// Slice s00871d50: libpng 1.2.25 read path, verbatim upstream source.
//   pngrtran.c : png_do_read_transformations
//   pngrutil.c : png_decompress_chunk, png_do_read_interlace, png_handle_IHDR, png_handle_gAMA
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE   (third-party libpng build: /O2 /arch:SSE /MD /Gy /TC)
//
// Self-contained: png_struct_def below is Spore's libpng configuration, offsets checked against
// the disassembly (transformations +0x70, row_buf +0xec, row_info +0x100, palette +0x114,
// trans +0x188, palette_lookup +0x1ec, rgb_to_gray_status +0x228, filter_type +0x238,
// compression_type +0x260, zstream +0x74, zbuf +0xac).
#include <stdio.h>
#include <string.h>

typedef unsigned char png_byte;
typedef unsigned short png_uint_16;
typedef unsigned int png_uint_32;
typedef int png_int_32;
typedef unsigned int png_size_t;
typedef int png_fixed_point;
typedef char* png_charp;
typedef const char* png_const_charp;
typedef unsigned char* png_bytep;
typedef void* png_voidp;

struct z_stream_s {
    png_bytep next_in;       png_uint_32 avail_in;  unsigned long total_in;
    png_bytep next_out;      png_uint_32 avail_out; unsigned long total_out;
    png_charp msg;           void* state;           void* zalloc;
    void* zfree;             void* opaque;
    int data_type;           unsigned long adler;   unsigned long reserved;
};
typedef z_stream_s* z_streamp;

struct png_color_def { png_byte red, green, blue; };
typedef png_color_def png_color;
typedef png_color* png_colorp;
struct png_color_16_def { png_byte index; png_uint_16 red, green, blue, gray; };
typedef png_color_16_def png_color_16;
typedef png_color_16* png_color_16p;
struct png_color_8_def { png_byte red, green, blue, gray, alpha; };
typedef png_color_8_def png_color_8;
typedef png_color_8* png_color_8p;
typedef png_uint_16** png_uint_16pp;
struct png_row_info_def {
    png_uint_32 width;
    png_uint_32 rowbytes;
    png_byte color_type;
    png_byte bit_depth;
    png_byte channels;
    png_byte pixel_depth;
};
typedef png_row_info_def png_row_info;
typedef png_row_info* png_row_infop;

struct png_struct_def;
typedef png_struct_def* png_structp;
typedef void (*png_fnptr)(void);
typedef void (*png_user_transform_ptr)(png_structp, png_row_infop, png_bytep);

struct png_struct_def {
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
    png_uint_32 mode;                                // +0x68
    png_uint_32 flags;                               // +0x6c
    png_uint_32 transformations;                     // +0x70
    z_stream_s zstream;                              // +0x74
    png_bytep zbuf;                                  // +0xac
    png_size_t zbuf_size;                            // +0xb0
    int zlib_level;                                  // +0xb4
    int zlib_method;                                 // +0xb8
    int zlib_window_bits;                            // +0xbc
    int zlib_mem_level;                              // +0xc0
    int zlib_strategy;                               // +0xc4
    png_uint_32 width;                               // +0xc8
    png_uint_32 height;                              // +0xcc
    png_uint_32 num_rows;                            // +0xd0
    png_uint_32 usr_width;                           // +0xd4
    png_uint_32 rowbytes;                            // +0xd8
    png_uint_32 irowbytes;                           // +0xdc
    png_uint_32 iwidth;                              // +0xe0
    png_uint_32 row_number;                          // +0xe4
    png_bytep prev_row;                              // +0xe8
    png_bytep row_buf;                               // +0xec
    png_bytep sub_row;                               // +0xf0
    png_bytep up_row;                                // +0xf4
    png_bytep avg_row;                               // +0xf8
    png_bytep paeth_row;                             // +0xfc
    png_row_info row_info;                           // +0x100
    png_uint_32 idat_size;                           // +0x10c
    png_uint_32 crc;                                 // +0x110
    png_colorp palette;                              // +0x114
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
    png_color_16 background;                         // +0x138
    png_color_16 background_1;                       // +0x142
    png_fnptr output_flush_fn;                       // +0x14c
    png_uint_32 flush_dist;                          // +0x150
    png_uint_32 flush_rows;                          // +0x154
    int gamma_shift;                                 // +0x158
    float gamma;                                     // +0x15c
    float screen_gamma;                              // +0x160
    png_bytep gamma_table;                           // +0x164
    png_bytep gamma_from_1;                          // +0x168
    png_bytep gamma_to_1;                            // +0x16c
    png_uint_16** gamma_16_table;                    // +0x170
    png_uint_16** gamma_16_from_1;                   // +0x174
    png_uint_16** gamma_16_to_1;                     // +0x178
    png_color_8 sig_bit;                             // +0x17c
    png_color_8 shift;                               // +0x181
    png_bytep trans;                                 // +0x188
    png_color_16 trans_values;                       // +0x18c
    png_fnptr read_row_fn;                           // +0x198
    png_fnptr write_row_fn;                          // +0x19c
    png_fnptr info_fn;                               // +0x1a0
    png_fnptr row_fn;                                // +0x1a4
    png_fnptr end_fn;                                // +0x1a8
    png_bytep save_buffer_ptr;                       // +0x1ac
    png_bytep save_buffer;                           // +0x1b0
    png_bytep current_buffer_ptr;                    // +0x1b4
    png_bytep current_buffer;                        // +0x1b8
    png_uint_32 push_length;                         // +0x1bc
    png_uint_32 skip_length;                         // +0x1c0
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
    png_bytep palette_lookup;                        // +0x1ec
    png_bytep dither_index;                          // +0x1f0
    png_uint_16* hist;                               // +0x1f4
    png_byte heuristic_method;                       // +0x1f8
    png_byte num_prev_filters;                       // +0x1f9
    png_bytep prev_filters;                          // +0x1fc
    png_uint_16* filter_weights;                     // +0x200
    png_uint_16* inv_filter_weights;                 // +0x204
    png_uint_16* filter_costs;                       // +0x208
    png_uint_16* inv_filter_costs;                   // +0x20c
    png_charp time_buffer;                           // +0x210
    png_uint_32 free_me;                             // +0x214
    png_voidp user_chunk_ptr;                        // +0x218
    png_fnptr read_user_chunk_fn;                    // +0x21c
    int num_chunk_list;                              // +0x220
    png_bytep chunk_list;                            // +0x224
    png_byte rgb_to_gray_status;                     // +0x228
    png_uint_16 rgb_to_gray_red_coeff;               // +0x229
    png_uint_16 rgb_to_gray_green_coeff;             // +0x22b
    png_uint_16 rgb_to_gray_blue_coeff;              // +0x22d
    png_uint_32 mng_features_permitted;              // +0x230
    png_fixed_point int_gamma;                       // +0x234
    png_byte filter_type;                            // +0x238
    png_byte mmx_bitdepth_threshold;                 // +0x239
    png_uint_32 mmx_rowbytes_threshold;              // +0x23c
    png_uint_32 asm_flags;                           // +0x240
    png_voidp mem_ptr;                               // +0x244
    png_fnptr malloc_fn;                             // +0x248
    png_fnptr free_fn;                               // +0x24c
    png_bytep big_row_buf;                           // +0x250
    png_bytep dither_sort;                           // +0x254
    png_bytep index_to_palette;                      // +0x258
    png_bytep palette_to_index;                      // +0x25c
    png_byte compression_type;                       // +0x260
    png_uint_32 user_width_max;                      // +0x264
    png_uint_32 user_height_max;                     // +0x268
};

struct png_info_def {
    png_uint_32 width;                               // +0x00
    png_uint_32 height;                              // +0x04
    png_uint_32 valid;                               // +0x08
};
typedef png_info_def* png_infop;

#define png_memcpy memcpy
#define png_sizeof sizeof
#define png_snprintf _snprintf
#define PNGAPI __cdecl

#define PNG_HAVE_IHDR  0x01
#define PNG_HAVE_PLTE  0x02
#define PNG_HAVE_IDAT  0x04

#define PNG_FLAG_ROW_INIT     0x0040
#define PNG_FLAG_FILLER_AFTER 0x0080
#define PNG_FLAG_STRIP_ALPHA  0x400000L

#define PNG_COLOR_MASK_PALETTE 1
#define PNG_COLOR_MASK_COLOR   2
#define PNG_COLOR_MASK_ALPHA   4
#define PNG_COLOR_TYPE_GRAY      0
#define PNG_COLOR_TYPE_PALETTE   (PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_PALETTE)
#define PNG_COLOR_TYPE_RGB       (PNG_COLOR_MASK_COLOR)
#define PNG_COLOR_TYPE_RGB_ALPHA (PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_ALPHA)
#define PNG_COLOR_TYPE_GRAY_ALPHA (PNG_COLOR_MASK_ALPHA)

#define PNG_BGR                0x0001
#define PNG_PACK               0x0004
#define PNG_SHIFT              0x0008
#define PNG_SWAP_BYTES         0x0010
#define PNG_INVERT_MONO        0x0020
#define PNG_DITHER             0x0040
#define PNG_BACKGROUND         0x0080
#define PNG_BACKGROUND_EXPAND  0x0100
#define PNG_16_TO_8            0x0400
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
#define PNG_RGB_TO_GRAY        0x600000L
#define PNG_EXPAND_tRNS        0x2000000L

#define PNG_BACKGROUND_IS_GRAY 0x800

#define PNG_INFO_gAMA 0x0001
#define PNG_INFO_sRGB 0x0800

#define PNG_UINT_31_MAX ((png_uint_32)0x7fffffffL)
#define PNG_COMPRESSION_TYPE_BASE 0

#define PNG_OUT_OF_RANGE(value, ideal, delta) \
   ( (value) < (ideal)-(delta) || (value) > (ideal)+(delta) )

#define PNG_ROWBYTES(pixel_bits, width) \
    ((pixel_bits) >= 8 ? \
    ((width) * (((png_uint_32)(pixel_bits)) >> 3)) : \
    (( ((width) * ((png_uint_32)(pixel_bits))) + 7) >> 3) )

#define PNG_COLOR_TYPE_IS_INVERTED 0

extern "C" {

void png_error(png_structp png_ptr, png_const_charp error_message);
void png_warning(png_structp png_ptr, png_const_charp warning_message);
png_voidp png_malloc_warn(png_structp png_ptr, png_size_t size);
void png_free(png_structp png_ptr, png_voidp ptr);
void png_read_data(png_structp png_ptr, png_bytep data, png_size_t length);
void png_calculate_crc(png_structp png_ptr, png_bytep ptr, png_size_t length);
int png_crc_finish(png_structp png_ptr, png_uint_32 skip);
void png_set_IHDR(png_structp png_ptr, png_infop info_ptr, png_uint_32 width,
    png_uint_32 height, int bit_depth, int color_type, int interlace_type,
    int compression_type, int filter_type);
void png_set_gAMA(png_structp png_ptr, png_infop info_ptr, double file_gamma);
void png_set_gAMA_fixed(png_structp png_ptr, png_infop info_ptr, png_fixed_point int_gamma);

int inflate(z_streamp strm, int flush);
int inflateReset(z_streamp strm);

void png_do_expand_palette(png_row_infop row_info, png_bytep row, png_colorp palette,
    png_bytep trans, png_uint_16 num_trans);
void png_do_expand(png_row_infop row_info, png_bytep row, png_color_16p trans_value);
void png_do_strip_filler(png_row_infop row_info, png_bytep row, png_uint_32 flags);
int png_do_rgb_to_gray(png_structp png_ptr, png_row_infop row_info, png_bytep row);
void png_do_gray_to_rgb(png_row_infop row_info, png_bytep row);
void png_do_background(png_row_infop row_info, png_bytep row, png_color_16p trans_values,
    png_color_16p background, png_color_16p background_1, png_bytep gamma_table,
    png_bytep gamma_from_1, png_bytep gamma_to_1, png_uint_16pp gamma_16_table,
    png_uint_16pp gamma_16_from_1, png_uint_16pp gamma_16_to_1, int gamma_shift);
void png_do_gamma(png_row_infop row_info, png_bytep row, png_bytep gamma_table,
    png_uint_16pp gamma_16_table, int gamma_shift);
void png_do_chop(png_row_infop row_info, png_bytep row);
void png_do_dither(png_row_infop row_info, png_bytep row, png_bytep palette_lookup,
    png_bytep dither_lookup);
void png_do_invert(png_row_infop row_info, png_bytep row);
void png_do_unshift(png_row_infop row_info, png_bytep row, png_color_8p sig_bits);
void png_do_unpack(png_row_infop row_info, png_bytep row);
void png_do_bgr(png_row_infop row_info, png_bytep row);
void png_do_packswap(png_row_infop row_info, png_bytep row);
void png_do_read_filler(png_row_infop row_info, png_bytep row, png_uint_32 filler,
    png_uint_32 flags);
void png_do_read_invert_alpha(png_row_infop row_info, png_bytep row);
void png_do_read_swap_alpha(png_row_infop row_info, png_bytep row);
void png_do_swap(png_row_infop row_info, png_bytep row);

void png_do_read_transformations(png_structp png_ptr);
png_charp png_decompress_chunk(png_structp png_ptr, int comp_type,
    png_charp chunkdata, png_size_t chunklength, png_size_t prefix_size,
    png_size_t *newlength);
void png_do_read_interlace(png_structp png_ptr);
void png_handle_IHDR(png_structp png_ptr, png_infop info_ptr, png_uint_32 length);
void png_handle_gAMA(png_structp png_ptr, png_infop info_ptr, png_uint_32 length);

}

/* Read data, and (optionally) run it through the CRC. */
static void /* PRIVATE */
png_crc_read(png_structp png_ptr, png_bytep buf, png_size_t length)
{
   if(png_ptr == NULL) return;
   png_read_data(png_ptr, buf, length);
   png_calculate_crc(png_ptr, buf, length);
}

/* Grab an unsigned 32-bit integer from a buffer in big-endian format. */
static png_uint_32 PNGAPI
png_get_uint_32(png_bytep buf)
{
   png_uint_32 i = ((png_uint_32)(*buf) << 24) +
      ((png_uint_32)(*(buf + 1)) << 16) +
      ((png_uint_32)(*(buf + 2)) << 8) +
      (png_uint_32)(*(buf + 3));

   return (i);
}

static png_uint_32 PNGAPI
png_get_uint_31(png_structp png_ptr, png_bytep buf)
{
   png_uint_32 i = png_get_uint_32(buf);
   if (i > PNG_UINT_31_MAX)
     png_error(png_ptr, "PNG unsigned integer out of range.");
   return (i);
}

// @ 0x00871d50
void /* PRIVATE */
png_do_read_transformations(png_structp png_ptr)
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
      if(png_ptr->row_info.rowbytes == (png_uint_32)0)
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
         (png_uint_32)png_ptr->filler, png_ptr->flags);

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

// @ 0x008722c0
png_charp /* PRIVATE */
png_decompress_chunk(png_structp png_ptr, int comp_type,
                              png_charp chunkdata, png_size_t chunklength,
                              png_size_t prefix_size, png_size_t *newlength)
{
   static const char msg[] = "Error decoding compressed text";
   png_charp text;
   png_size_t text_size;

   if (comp_type == PNG_COMPRESSION_TYPE_BASE)
   {
      int ret = 0; /* Z_OK */
      png_ptr->zstream.next_in = (png_bytep)(chunkdata + prefix_size);
      png_ptr->zstream.avail_in = (png_uint_32)(chunklength - prefix_size);
      png_ptr->zstream.next_out = png_ptr->zbuf;
      png_ptr->zstream.avail_out = (png_uint_32)png_ptr->zbuf_size;

      text_size = 0;
      text = NULL;

      while (png_ptr->zstream.avail_in)
      {
         ret = inflate(&png_ptr->zstream, 1 /* Z_PARTIAL_FLUSH */);
         if (ret != 0 /* Z_OK */ && ret != 1 /* Z_STREAM_END */)
         {
            if (png_ptr->zstream.msg != NULL)
               png_warning(png_ptr, png_ptr->zstream.msg);
            else
               png_warning(png_ptr, msg);
            inflateReset(&png_ptr->zstream);
            png_ptr->zstream.avail_in = 0;

            if (text ==  NULL)
            {
               text_size = prefix_size + png_sizeof(msg) + 1;
               text = (png_charp)png_malloc_warn(png_ptr, text_size);
               if (text ==  NULL)
                 {
                    png_free(png_ptr,chunkdata);
                    png_error(png_ptr,"Not enough memory to decompress chunk");
                 }
               png_memcpy(text, chunkdata, prefix_size);
            }

            text[text_size - 1] = 0x00;

            /* Copy what we can of the error message into the text chunk */
            text_size = (png_size_t)(chunklength - (text - chunkdata) - 1);
            text_size = png_sizeof(msg) > text_size ? text_size :
               png_sizeof(msg);
            png_memcpy(text + prefix_size, msg, text_size);
            break;
         }
         if (!png_ptr->zstream.avail_out || ret == 1 /* Z_STREAM_END */)
         {
            if (text == NULL)
            {
               text_size = prefix_size +
                   png_ptr->zbuf_size - png_ptr->zstream.avail_out;
               text = (png_charp)png_malloc_warn(png_ptr, text_size + 1);
               if (text ==  NULL)
                 {
                    png_free(png_ptr,chunkdata);
                    png_error(png_ptr,"Not enough memory to decompress chunk.");
                 }
               png_memcpy(text + prefix_size, png_ptr->zbuf,
                    text_size - prefix_size);
               png_memcpy(text, chunkdata, prefix_size);
               *(text + text_size) = 0x00;
            }
            else
            {
               png_charp tmp;

               tmp = text;
               text = (png_charp)png_malloc_warn(png_ptr,
                  (png_uint_32)(text_size +
                  png_ptr->zbuf_size - png_ptr->zstream.avail_out + 1));
               if (text == NULL)
               {
                  png_free(png_ptr, tmp);
                  png_free(png_ptr, chunkdata);
                  png_error(png_ptr,"Not enough memory to decompress chunk..");
               }
               png_memcpy(text, tmp, text_size);
               png_free(png_ptr, tmp);
               png_memcpy(text + text_size, png_ptr->zbuf,
                  (png_ptr->zbuf_size - png_ptr->zstream.avail_out));
               text_size += png_ptr->zbuf_size - png_ptr->zstream.avail_out;
               *(text + text_size) = 0x00;
            }
            if (ret == 1 /* Z_STREAM_END */)
               break;
            else
            {
               png_ptr->zstream.next_out = png_ptr->zbuf;
               png_ptr->zstream.avail_out = (png_uint_32)png_ptr->zbuf_size;
            }
         }
      }
      if (ret != 1 /* Z_STREAM_END */)
      {
         char umsg[52];

         if (ret == -5 /* Z_BUF_ERROR */)
            png_snprintf(umsg, 52,
                "Buffer error in compressed datastream in %s chunk",
                png_ptr->chunk_name);
         else if (ret == -3 /* Z_DATA_ERROR */)
            png_snprintf(umsg, 52,
                "Data error in compressed datastream in %s chunk",
                png_ptr->chunk_name);
         else
            png_snprintf(umsg, 52,
                "Incomplete compressed datastream in %s chunk",
                png_ptr->chunk_name);
         png_warning(png_ptr, umsg);
         text_size=prefix_size;
         if (text ==  NULL)
         {
            text = (png_charp)png_malloc_warn(png_ptr, text_size+1);
            if (text == NULL)
              {
                png_free(png_ptr, chunkdata);
                png_error(png_ptr,"Not enough memory for text.");
              }
            png_memcpy(text, chunkdata, prefix_size);
         }
         *(text + text_size) = 0x00;
      }

      inflateReset(&png_ptr->zstream);
      png_ptr->zstream.avail_in = 0;

      png_free(png_ptr, chunkdata);
      chunkdata = text;
      *newlength=text_size;
   }
   else /* if (comp_type != PNG_COMPRESSION_TYPE_BASE) */
   {
      char umsg[50];

      png_snprintf(umsg, 50,
         "Unknown zTXt compression type %d", comp_type);
      png_warning(png_ptr, umsg);

      *(chunkdata + prefix_size) = 0x00;
      *newlength=prefix_size;
   }

   return chunkdata;
}

// @ 0x00872970
void /* PRIVATE */
png_do_read_interlace(png_structp png_ptr)
{
   png_row_infop row_info = &(png_ptr->row_info);
   png_bytep row = png_ptr->row_buf + 1;
   int pass = png_ptr->pass;
   png_uint_32 transformations = png_ptr->transformations;
   /* arrays to facilitate easy interlacing - use pass (0 - 6) as index */
   /* offset to next interlace block */
   const int png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};

   if (row != NULL && row_info != NULL)
   {
      png_uint_32 final_width;

      final_width = row_info->width * png_pass_inc[pass];

      switch (row_info->pixel_depth)
      {
         case 1:
         {
            png_bytep sp = row + (png_size_t)((row_info->width - 1) >> 3);
            png_bytep dp = row + (png_size_t)((final_width - 1) >> 3);
            int sshift, dshift;
            int s_start, s_end, s_inc;
            int jstop = png_pass_inc[pass];
            png_byte v;
            png_uint_32 i;
            int j;

            if (transformations & PNG_PACKSWAP)
            {
                sshift = (int)((row_info->width + 7) & 0x07);
                dshift = (int)((final_width + 7) & 0x07);
                s_start = 7;
                s_end = 0;
                s_inc = -1;
            }
            else
            {
                sshift = 7 - (int)((row_info->width + 7) & 0x07);
                dshift = 7 - (int)((final_width + 7) & 0x07);
                s_start = 0;
                s_end = 7;
                s_inc = 1;
            }

            for (i = 0; i < row_info->width; i++)
            {
               v = (png_byte)((*sp >> sshift) & 0x01);
               for (j = 0; j < jstop; j++)
               {
                  *dp &= (png_byte)((0x7f7f >> (7 - dshift)) & 0xff);
                  *dp |= (png_byte)(v << dshift);
                  if (dshift == s_end)
                  {
                     dshift = s_start;
                     dp--;
                  }
                  else
                     dshift += s_inc;
               }
               if (sshift == s_end)
               {
                  sshift = s_start;
                  sp--;
               }
               else
                  sshift += s_inc;
            }
            break;
         }
         case 2:
         {
            png_bytep sp = row + (png_uint_32)((row_info->width - 1) >> 2);
            png_bytep dp = row + (png_uint_32)((final_width - 1) >> 2);
            int sshift, dshift;
            int s_start, s_end, s_inc;
            int jstop = png_pass_inc[pass];
            png_uint_32 i;

            if (transformations & PNG_PACKSWAP)
            {
               sshift = (int)(((row_info->width + 3) & 0x03) << 1);
               dshift = (int)(((final_width + 3) & 0x03) << 1);
               s_start = 6;
               s_end = 0;
               s_inc = -2;
            }
            else
            {
               sshift = (int)((3 - ((row_info->width + 3) & 0x03)) << 1);
               dshift = (int)((3 - ((final_width + 3) & 0x03)) << 1);
               s_start = 0;
               s_end = 6;
               s_inc = 2;
            }

            for (i = 0; i < row_info->width; i++)
            {
               png_byte v;
               int j;

               v = (png_byte)((*sp >> sshift) & 0x03);
               for (j = 0; j < jstop; j++)
               {
                  *dp &= (png_byte)((0x3f3f >> (6 - dshift)) & 0xff);
                  *dp |= (png_byte)(v << dshift);
                  if (dshift == s_end)
                  {
                     dshift = s_start;
                     dp--;
                  }
                  else
                     dshift += s_inc;
               }
               if (sshift == s_end)
               {
                  sshift = s_start;
                  sp--;
               }
               else
                  sshift += s_inc;
            }
            break;
         }
         case 4:
         {
            png_bytep sp = row + (png_size_t)((row_info->width - 1) >> 1);
            png_bytep dp = row + (png_size_t)((final_width - 1) >> 1);
            int sshift, dshift;
            int s_start, s_end, s_inc;
            png_uint_32 i;
            int jstop = png_pass_inc[pass];

            if (transformations & PNG_PACKSWAP)
            {
               sshift = (int)(((row_info->width + 1) & 0x01) << 2);
               dshift = (int)(((final_width + 1) & 0x01) << 2);
               s_start = 4;
               s_end = 0;
               s_inc = -4;
            }
            else
            {
               sshift = (int)((1 - ((row_info->width + 1) & 0x01)) << 2);
               dshift = (int)((1 - ((final_width + 1) & 0x01)) << 2);
               s_start = 0;
               s_end = 4;
               s_inc = 4;
            }

            for (i = 0; i < row_info->width; i++)
            {
               png_byte v = (png_byte)((*sp >> sshift) & 0xf);
               int j;

               for (j = 0; j < jstop; j++)
               {
                  *dp &= (png_byte)((0xf0f >> (4 - dshift)) & 0xff);
                  *dp |= (png_byte)(v << dshift);
                  if (dshift == s_end)
                  {
                     dshift = s_start;
                     dp--;
                  }
                  else
                     dshift += s_inc;
               }
               if (sshift == s_end)
               {
                  sshift = s_start;
                  sp--;
               }
               else
                  sshift += s_inc;
            }
            break;
         }
         default:
         {
            png_size_t pixel_bytes = (row_info->pixel_depth >> 3);
            png_bytep sp = row + (png_size_t)(row_info->width - 1) * pixel_bytes;
            png_bytep dp = row + (png_size_t)(final_width - 1) * pixel_bytes;

            int jstop = png_pass_inc[pass];
            png_uint_32 i;

            for (i = 0; i < row_info->width; i++)
            {
               png_byte v[8];
               int j;

               png_memcpy(v, sp, pixel_bytes);
               for (j = 0; j < jstop; j++)
               {
                  png_memcpy(dp, v, pixel_bytes);
                  dp -= pixel_bytes;
               }
               sp -= pixel_bytes;
            }
            break;
         }
      }
      row_info->width = final_width;
      row_info->rowbytes = PNG_ROWBYTES(row_info->pixel_depth,final_width);
   }
}

// @ 0x008733a0
void /* PRIVATE */
png_handle_IHDR(png_structp png_ptr, png_infop info_ptr, png_uint_32 length)
{
   png_byte buf[13];
   png_uint_32 width, height;
   int bit_depth, color_type, compression_type, filter_type;
   int interlace_type;

   if (png_ptr->mode & PNG_HAVE_IHDR)
      png_error(png_ptr, "Out of place IHDR");

   /* check the length */
   if (length != 13)
      png_error(png_ptr, "Invalid IHDR chunk");

   png_ptr->mode |= PNG_HAVE_IHDR;

   png_crc_read(png_ptr, buf, 13);
   png_crc_finish(png_ptr, 0);

   width = png_get_uint_31(png_ptr, buf);
   height = png_get_uint_31(png_ptr, buf + 4);
   bit_depth = buf[8];
   color_type = buf[9];
   compression_type = buf[10];
   filter_type = buf[11];
   interlace_type = buf[12];

   /* set internal variables */
   png_ptr->width = width;
   png_ptr->height = height;
   png_ptr->bit_depth = (png_byte)bit_depth;
   png_ptr->interlaced = (png_byte)interlace_type;
   png_ptr->color_type = (png_byte)color_type;
   png_ptr->filter_type = (png_byte)filter_type;
   png_ptr->compression_type = (png_byte)compression_type;

   /* find number of channels */
   switch (png_ptr->color_type)
   {
      case PNG_COLOR_TYPE_GRAY:
      case PNG_COLOR_TYPE_PALETTE:
         png_ptr->channels = 1;
         break;
      case PNG_COLOR_TYPE_RGB:
         png_ptr->channels = 3;
         break;
      case PNG_COLOR_TYPE_GRAY_ALPHA:
         png_ptr->channels = 2;
         break;
      case PNG_COLOR_TYPE_RGB_ALPHA:
         png_ptr->channels = 4;
         break;
   }

   /* set up other useful info */
   png_ptr->pixel_depth = (png_byte)(png_ptr->bit_depth *
   png_ptr->channels);
   png_ptr->rowbytes = PNG_ROWBYTES(png_ptr->pixel_depth,png_ptr->width);
   png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth,
      color_type, interlace_type, compression_type, filter_type);
}

// @ 0x00873750
void /* PRIVATE */
png_handle_gAMA(png_structp png_ptr, png_infop info_ptr, png_uint_32 length)
{
   png_fixed_point igamma;
   float file_gamma;
   png_byte buf[4];

   if (!(png_ptr->mode & PNG_HAVE_IHDR))
      png_error(png_ptr, "Missing IHDR before gAMA");
   else if (png_ptr->mode & PNG_HAVE_IDAT)
   {
      png_warning(png_ptr, "Invalid gAMA after IDAT");
      png_crc_finish(png_ptr, length);
      return;
   }
   else if (png_ptr->mode & PNG_HAVE_PLTE)
      /* Should be an error, but we can cope with it */
      png_warning(png_ptr, "Out of place gAMA chunk");

   if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_gAMA)
      && !(info_ptr->valid & PNG_INFO_sRGB)
      )
   {
      png_warning(png_ptr, "Duplicate gAMA chunk");
      png_crc_finish(png_ptr, length);
      return;
   }

   if (length != 4)
   {
      png_warning(png_ptr, "Incorrect gAMA chunk length");
      png_crc_finish(png_ptr, length);
      return;
   }

   png_crc_read(png_ptr, buf, 4);
   if (png_crc_finish(png_ptr, 0))
      return;

   igamma = (png_fixed_point)png_get_uint_32(buf);
   /* check for zero gamma */
   if (igamma == 0)
      {
         png_warning(png_ptr,
           "Ignoring gAMA chunk with gamma=0");
         return;
      }

   if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_sRGB))
      if (PNG_OUT_OF_RANGE(igamma, 45500L, 500))
      {
         png_warning(png_ptr,
           "Ignoring incorrect gAMA value when sRGB is also present");
         fprintf(stderr, "gamma = (%d/100000)\n", (int)igamma);
         return;
      }

   file_gamma = (float)igamma / (float)100000.0;
   png_ptr->gamma = file_gamma;
   png_set_gAMA(png_ptr, info_ptr, file_gamma);
   png_set_gAMA_fixed(png_ptr, info_ptr, igamma);
}
