// Slice s0086d090: png_build_gamma_table (libpng 1.2.25, pngrtran.c), 1734 bytes.
// Self-contained: png_struct is declared below with the layout of Spore's libpng configuration
// (copied from slice s00871010: transformations +0x70, color_type +0x126, bit_depth +0x127,
// gamma_shift +0x158, gamma +0x15c, screen_gamma +0x160, gamma_table +0x164, gamma_from_1 +0x168,
// gamma_to_1 +0x16c, gamma_16_* +0x170..0x178, sig_bit +0x17c).
// Flags: /O2 /MD /Gy /GS- /EHsc /TP /arch:SSE /fp:fast
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>

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

// zlib 1.2.3 z_stream (56 bytes)
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

// @ 0x00870860 (libpng 1.2.25 pngrtran.c)
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

// ---------------------------------------------------------------------------
// libpng 1.2.25 pngwrite.c / pngmem.c functions in this slice.
// ---------------------------------------------------------------------------

typedef void (*png_error_ptr)(png_structp, const char*);
typedef void (*png_rw_ptr)(png_structp, png_bytep, png_size_t);
typedef void (*png_flush_ptr)(png_structp);
typedef png_voidp (*png_malloc_ptr)(png_structp, png_size_t);
typedef void (*png_free_ptr)(png_structp, png_voidp);

extern "C" void png_warning(png_structp, const char*);       // 0x0086b300
extern "C" void png_error(png_structp, const char*);         // 0x0086b250
extern "C" void png_free(png_structp, png_voidp);            // 0x0086d850
extern "C" void png_set_mem_fn(png_structp, png_voidp, png_malloc_ptr, png_free_ptr);      // 0x0086d7a0
extern "C" void png_set_error_fn(png_structp, png_voidp, png_error_ptr, png_error_ptr);    // 0x0086b230
extern "C" void png_set_write_fn(png_structp, png_voidp, png_rw_ptr, png_flush_ptr);       // 0x008773d0
extern "C" const char* png_get_libpng_ver(png_voidp);        // 0x0086aec0

__declspec(noinline) png_voidp png_create_struct_2(int type, png_malloc_ptr malloc_fn, png_voidp mem_ptr);
void png_destroy_struct_2(png_voidp struct_ptr, png_free_ptr free_fn, png_voidp mem_ptr);
__declspec(noinline) void png_destroy_struct(png_voidp struct_ptr);

// @ 0x0086d090 (libpng 1.2.25 pngwrite.c)
void png_set_filter_heuristics(png_structp png_ptr, int heuristic_method,
   int num_weights, double* filter_weights, double* filter_costs)
{
   int i;

   if (png_ptr == 0)
      return;
   if (heuristic_method >= 3)
   {
      png_warning(png_ptr, "Unknown filter heuristic method");
      return;
   }

   if (heuristic_method == 0)
      heuristic_method = 1;

   if (num_weights < 0 || filter_weights == 0 ||
      heuristic_method == 1)
      num_weights = 0;

   png_ptr->num_prev_filters = (png_byte)num_weights;
   png_ptr->heuristic_method = (png_byte)heuristic_method;

   if (num_weights > 0)
   {
      if (png_ptr->prev_filters == 0)
      {
         png_ptr->prev_filters = (png_bytep)png_malloc(png_ptr,
            (png_uint_32)(sizeof(png_byte) * num_weights));

         /* To make sure that the weighting starts out fairly */
         for (i = 0; i < num_weights; i++)
         {
            png_ptr->prev_filters[i] = 255;
         }
      }

      if (png_ptr->filter_weights == 0)
      {
         png_ptr->filter_weights = (png_uint_16p)png_malloc(png_ptr,
            (png_uint_32)(sizeof(png_uint_16) * num_weights));

         png_ptr->inv_filter_weights = (png_uint_16p)png_malloc(png_ptr,
            (png_uint_32)(sizeof(png_uint_16) * num_weights));
         for (i = 0; i < num_weights; i++)
         {
            png_ptr->inv_filter_weights[i] =
            png_ptr->filter_weights[i] = 256;
         }
      }

      for (i = 0; i < num_weights; i++)
      {
         if (filter_weights[i] < 0.0)
         {
            png_ptr->inv_filter_weights[i] =
            png_ptr->filter_weights[i] = 256;
         }
         else
         {
            png_ptr->inv_filter_weights[i] =
               (png_uint_16)((double)256 * filter_weights[i] + 0.5);
            png_ptr->filter_weights[i] =
               (png_uint_16)((double)256 / filter_weights[i] + 0.5);
         }
      }
   }

   /* If, in the future, there are other filter methods, this would
    * need to be based on png_ptr->filter.
    */
   if (png_ptr->filter_costs == 0)
   {
      png_ptr->filter_costs = (png_uint_16p)png_malloc(png_ptr,
         (png_uint_32)(sizeof(png_uint_16) * 5));

      png_ptr->inv_filter_costs = (png_uint_16p)png_malloc(png_ptr,
         (png_uint_32)(sizeof(png_uint_16) * 5));

      for (i = 0; i < 5; i++)
      {
         png_ptr->inv_filter_costs[i] =
         png_ptr->filter_costs[i] = 8;
      }
   }

   for (i = 0; i < 5; i++)
   {
      if (filter_costs == 0 || filter_costs[i] < 0.0)
      {
         png_ptr->inv_filter_costs[i] =
         png_ptr->filter_costs[i] = 8;
      }
      else if (filter_costs[i] >= 1.0)
      {
         png_ptr->inv_filter_costs[i] =
            (png_uint_16)((double)8 / filter_costs[i] + 0.5);
         png_ptr->filter_costs[i] =
            (png_uint_16)((double)8 * filter_costs[i] + 0.5);
      }
   }
}

// @ 0x0086d3c0 (libpng 1.2.25 pngwrite.c)
png_structp png_create_write_struct_2(const char* user_png_ver, png_voidp error_ptr,
   png_error_ptr error_fn, png_error_ptr warn_fn, png_voidp mem_ptr,
   png_malloc_ptr malloc_fn, png_free_ptr free_fn)
{
   png_structp png_ptr;
   int i;

   png_ptr = (png_structp)png_create_struct_2(1, malloc_fn, mem_ptr);
   if (png_ptr == 0)
      return 0;

   png_ptr->user_width_max = 1000000;
   png_ptr->user_height_max = 1000000;

   if (setjmp(png_ptr->jmpbuf))
   {
      png_free(png_ptr, png_ptr->zbuf);
      png_ptr->zbuf = 0;
      png_destroy_struct(png_ptr);
      return 0;
   }

   png_set_mem_fn(png_ptr, mem_ptr, malloc_fn, free_fn);
   png_set_error_fn(png_ptr, error_ptr, error_fn, warn_fn);

   if (user_png_ver)
   {
      i = 0;
      do
      {
         if (user_png_ver[i] != png_get_libpng_ver(0)[i])
            png_ptr->flags |= 0x20000;
      } while (png_get_libpng_ver(0)[i++]);
   }

   if (png_ptr->flags & 0x20000)
   {
      if (user_png_ver == 0 || user_png_ver[0] != png_get_libpng_ver(0)[0] ||
          (user_png_ver[0] == '1' && user_png_ver[2] != png_get_libpng_ver(0)[2]) ||
          (user_png_ver[0] == '0' && user_png_ver[2] < '9'))
      {
         char msg[80];
         if (user_png_ver)
         {
            _snprintf(msg, 80,
               "Application was compiled with png.h from libpng-%.20s",
               user_png_ver);
            png_warning(png_ptr, msg);
         }
         _snprintf(msg, 80,
            "Application  is  running with png.c from libpng-%.20s",
            png_get_libpng_ver(0));
         png_warning(png_ptr, msg);
         png_ptr->flags = 0;
         png_error(png_ptr,
            "Incompatible libpng version in application and library");
      }
   }

   /* initialize zbuf - compression buffer */
   png_ptr->zbuf_size = 0x2000;
   png_ptr->zbuf = (png_bytep)png_malloc(png_ptr,
      (png_uint_32)png_ptr->zbuf_size);

   png_set_write_fn(png_ptr, 0, 0, 0);

   png_set_filter_heuristics(png_ptr, 0, 1, 0, 0);

   if (setjmp(png_ptr->jmpbuf))
      abort();

   return png_ptr;
}

// @ 0x0086d690 (libpng 1.2.25 pngmem.c)
png_voidp png_create_struct_2(int type, png_malloc_ptr malloc_fn, png_voidp mem_ptr)
{
   png_size_t size;
   png_voidp struct_ptr;

   if (type == 2)
      size = 0x120;
   else if (type == 1)
      size = 0x280;
   else
      return 0;

   if (malloc_fn != 0)
   {
      png_struct_def dummy_struct;
      png_structp png_ptr = &dummy_struct;
      png_ptr->mem_ptr = mem_ptr;
      struct_ptr = (png_voidp)(*malloc_fn)(png_ptr, size);
      if (struct_ptr != 0)
         memset(struct_ptr, 0, size);
      return struct_ptr;
   }

   struct_ptr = (png_voidp)malloc(size);
   if (struct_ptr != 0)
      memset(struct_ptr, 0, size);

   return struct_ptr;
}

// @ 0x0086d710 (libpng 1.2.25 pngmem.c)
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

// @ 0x0086d7d0 (libpng 1.2.25 pngmem.c)
void png_destroy_struct(png_voidp struct_ptr)
{
   if (struct_ptr != 0)
      free(struct_ptr);
}
