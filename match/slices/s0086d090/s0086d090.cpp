// Slice s0086d090: png_build_gamma_table (libpng 1.2.25, pngrtran.c), 1734 bytes.
// Self-contained: png_struct is declared below with the layout of Spore's libpng configuration
// (copied from slice s00871010: transformations +0x70, color_type +0x126, bit_depth +0x127,
// gamma_shift +0x158, gamma +0x15c, screen_gamma +0x160, gamma_table +0x164, gamma_from_1 +0x168,
// gamma_to_1 +0x16c, gamma_16_* +0x170..0x178, sig_bit +0x17c).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include <math.h>

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
