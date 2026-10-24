// Slice s0086b250: libpng error/warning helpers, png_create_read_struct_2, png_read_info and
// png_read_row (libpng 1.2.x with MNG user limits).  MSVC 2008 SP1, /O2.
#include "game/types.h"

#include <setjmp.h>

#ifndef NULL
#define NULL 0
#endif

typedef unsigned char png_byte;
typedef unsigned int png_uint_32;
typedef unsigned int png_size_t;
typedef unsigned char* png_bytep;
typedef void* png_voidp;
typedef const char* png_const_charp;

struct png_struct_def;
typedef png_struct_def* png_structp;
struct png_info_def;
typedef png_info_def* png_infop;

typedef void (__cdecl* png_error_ptr)(png_structp, png_const_charp);
typedef void* (__cdecl* png_malloc_ptr)(png_structp, png_uint_32);
typedef void (__cdecl* png_free_ptr)(png_structp, png_voidp);
typedef void (__cdecl* png_rw_ptr)(png_structp, png_bytep, png_size_t);
typedef void (__cdecl* png_read_status_ptr)(png_structp, png_uint_32, int);
typedef void* (__cdecl* png_zalloc_ptr)(png_voidp, unsigned int, unsigned int);
typedef void (__cdecl* png_zfree_ptr)(png_voidp, png_voidp);

// png.h mode bits
enum
{
    PNG_HAVE_IHDR = 0x0001,
    PNG_HAVE_PLTE = 0x0002,
    PNG_HAVE_IDAT = 0x0004,
    PNG_AFTER_IDAT = 0x0008,
    PNG_HAVE_PNG_SIGNATURE = 0x1000,
    PNG_MULTIPLE_IDAT = 0x2000
};

// png.h flag bits
enum
{
    PNG_FLAG_ZSTREAM_ENDED = 0x0020,
    PNG_FLAG_ROW_INIT = 0x0040,
    PNG_FLAG_LIBRARY_MISMATCH = 0x020000,
    PNG_FLAG_STRIP_ERROR_NUMBERS = 0x040000,
    PNG_FLAG_STRIP_ERROR_TEXT = 0x080000,
    PNG_FLAG_READ_TRANSFORM = 0x400000
};

enum
{
    PNG_INTERLACE = 0x0002,
    PNG_FLAG_MNG_FILTER_64 = 0x04,
    PNG_INTRAPIXEL_DIFFERENCING = 0x40,
    PNG_COLOR_TYPE_PALETTE = 3,
    PNG_ZBUF_SIZE = 0x2000
};

struct z_stream_s
{
    png_bytep next_in;          // +0x00
    unsigned int avail_in;      // +0x04
    unsigned long total_in;     // +0x08
    png_bytep next_out;         // +0x0c
    unsigned int avail_out;     // +0x10
    unsigned long total_out;    // +0x14
    char* msg;                  // +0x18
    void* state;                // +0x1c
    void* zalloc;               // +0x20
    void* zfree;                // +0x24
    void* opaque;               // +0x28
    int data_type;              // +0x2c
    unsigned long adler;        // +0x30
    unsigned long reserved;     // +0x34
};

struct png_row_info_struct
{
    png_uint_32 width;          // +0x00
    png_uint_32 rowbytes;       // +0x04
    png_byte color_type;        // +0x08
    png_byte bit_depth;         // +0x09
    png_byte channels;          // +0x0a
    png_byte pixel_depth;       // +0x0b
};

struct png_struct_def
{
    jmp_buf jmpbuf;                             // +0x000
    void* error_fn;                             // +0x040
    void* warning_fn;                           // +0x044
    void* error_ptr;                            // +0x048
    void* write_data_fn;                        // +0x04c
    void* read_data_fn;                         // +0x050
    void* io_ptr;                               // +0x054
    void* read_user_transform_fn;               // +0x058
    void* write_user_transform_fn;              // +0x05c
    void* user_transform_ptr;                   // +0x060
    png_byte user_transform_depth;              // +0x064
    png_byte user_transform_channels;           // +0x065
    png_byte pad_066[0x068 - 0x066];
    png_uint_32 mode;                           // +0x068
    png_uint_32 flags;                          // +0x06c
    png_uint_32 transformations;                // +0x070
    z_stream_s zstream;                         // +0x074
    png_bytep zbuf;                             // +0x0ac
    png_uint_32 zbuf_size;                      // +0x0b0
    int zlib_level;                             // +0x0b4
    int zlib_method;                            // +0x0b8
    int zlib_window_bits;                       // +0x0bc
    int zlib_mem_level;                         // +0x0c0
    int zlib_strategy;                          // +0x0c4
    png_uint_32 width;                          // +0x0c8
    png_uint_32 height;                         // +0x0cc
    png_uint_32 num_rows;                       // +0x0d0
    png_uint_32 usr_width;                      // +0x0d4
    png_uint_32 rowbytes;                       // +0x0d8
    png_uint_32 irowbytes;                      // +0x0dc
    png_uint_32 iwidth;                         // +0x0e0
    png_uint_32 row_number;                     // +0x0e4
    png_bytep prev_row;                         // +0x0e8
    png_bytep row_buf;                          // +0x0ec
    png_bytep sub_row;                          // +0x0f0
    png_bytep up_row;                           // +0x0f4
    png_bytep avg_row;                          // +0x0f8
    png_bytep paeth_row;                        // +0x0fc
    png_row_info_struct row_info;               // +0x100
    png_uint_32 idat_size;                      // +0x10c
    png_uint_32 crc;                            // +0x110
    void* palette;                              // +0x114
    unsigned short num_palette;                 // +0x118
    unsigned short num_trans;                   // +0x11a
    png_byte chunk_name[5];                     // +0x11c
    png_byte compression;                       // +0x121
    png_byte filter;                            // +0x122
    png_byte interlaced;                        // +0x123
    png_byte pass;                              // +0x124
    png_byte do_filter;                         // +0x125
    png_byte color_type;                        // +0x126
    png_byte bit_depth;                         // +0x127
    png_byte usr_bit_depth;                     // +0x128
    png_byte pixel_depth;                       // +0x129
    png_byte channels;                          // +0x12a
    png_byte usr_channels;                      // +0x12b
    png_byte sig_bytes;                         // +0x12c
    png_byte pad_12d[0x198 - 0x12d];
    void* read_row_fn;                          // +0x198
    png_byte pad_19c[0x230 - 0x19c];
    png_byte mng_features_permitted;            // +0x230
    png_byte pad_231[0x238 - 0x231];
    png_byte filter_type;                       // +0x238
    png_byte pad_239[0x264 - 0x239];
    png_uint_32 user_width_max;                 // +0x264
    png_uint_32 user_height_max;                // +0x268
    png_byte pad_26c[0x280 - 0x26c];
};

struct png_info_def
{
    png_uint_32 width;             // +0x00
    png_uint_32 height;            // +0x04
    png_uint_32 valid;             // +0x08
    png_uint_32 rowbytes;          // +0x0c
    png_byte* palette;             // +0x10
    unsigned short num_palette;    // +0x14
    unsigned short num_trans;      // +0x16
    png_byte bit_depth;            // +0x18
    png_byte color_type;           // +0x19
    png_byte compression_type;     // +0x1a
    png_byte filter_type;          // +0x1b
    png_byte interlace_type;       // +0x1c
    png_byte channels;             // +0x1d
    png_byte pixel_depth;          // +0x1e
    png_byte spare_byte;           // +0x1f
    png_byte signature[8];         // +0x20
};

// ---- callees (retail addresses in the comments) ----
extern "C" void __cdecl png_default_error(png_structp, png_const_charp);                    // 0x0086aff0
extern "C" void __cdecl png_default_warning(png_structp, png_const_charp);                  // 0x0086b110
extern "C" void __cdecl png_format_buffer(png_structp, char*, png_const_charp);             // 0x0086af60
extern "C" void __cdecl png_read_data(png_structp, png_bytep, png_size_t);                  // 0x0086d8b0
extern "C" png_uint_32 __cdecl png_get_uint_31(png_structp, png_bytep);                     // 0x00873280
extern "C" void __cdecl png_reset_crc(png_structp);                                         // 0x0086aa30
extern "C" void __cdecl png_crc_read(png_structp, png_bytep, png_size_t);                   // 0x00872210
extern "C" void __cdecl png_crc_finish(png_structp, png_uint_32);                           // 0x008732d0
extern "C" int __cdecl png_sig_cmp(png_bytep, png_uint_32, png_size_t);                     // 0x0086a8c0
extern "C" int __cdecl png_handle_as_unknown(png_structp, png_bytep);                       // 0x0086aed0
extern "C" void __cdecl png_handle_IHDR(png_structp, png_infop, png_uint_32);               // 0x008733a0
extern "C" void __cdecl png_handle_PLTE(png_structp, png_infop, png_uint_32);               // 0x00873560
extern "C" void __cdecl png_handle_IEND(png_structp, png_infop, png_uint_32);               // 0x00873700
extern "C" void __cdecl png_handle_bKGD(png_structp, png_infop);                            // 0x00874860
extern "C" void __cdecl png_handle_cHRM(png_structp, png_infop);                            // 0x00873a60
extern "C" void __cdecl png_handle_gAMA(png_structp, png_infop);                            // 0x00873750
extern "C" void __cdecl png_handle_hIST(png_structp, png_infop);                            // 0x00874a80
extern "C" void __cdecl png_handle_oFFs(png_structp, png_infop);                            // 0x00874d20
extern "C" void __cdecl png_handle_pCAL(png_structp, png_infop);                            // 0x00874e40
extern "C" void __cdecl png_handle_sCAL(png_structp, png_infop);                            // 0x00875100
extern "C" void __cdecl png_handle_pHYs(png_structp, png_infop);                            // 0x00874c00
extern "C" void __cdecl png_handle_sBIT(png_structp, png_infop);                            // 0x008738e0
extern "C" void __cdecl png_handle_sRGB(png_structp, png_infop);                            // 0x00873f70
extern "C" void __cdecl png_handle_iCCP(png_structp, png_infop);                            // 0x00874180
extern "C" void __cdecl png_handle_sPLT(png_structp, png_infop);                            // 0x00874340
extern "C" void __cdecl png_handle_tEXt(png_structp, png_infop);                            // 0x008753c0
extern "C" void __cdecl png_handle_tIME(png_structp, png_infop);                            // 0x008752b0
extern "C" void __cdecl png_handle_tRNS(png_structp, png_infop);                            // 0x008745a0
extern "C" void __cdecl png_handle_zTXt(png_structp, png_infop);                            // 0x008754e0
extern "C" void __cdecl png_handle_unknown(png_structp, png_infop, png_uint_32);            // 0x00875640
extern "C" png_structp __cdecl png_create_png_struct(int, png_malloc_ptr, png_voidp);       // 0x0086d690
extern "C" void __cdecl png_destroy_png_struct(png_structp, png_free_ptr, png_voidp);       // 0x0086d710
extern "C" void __cdecl png_set_mem_fn(png_structp, png_voidp, png_malloc_ptr,
                                        png_free_ptr);                                      // 0x0086d7a0
extern "C" void __cdecl png_set_error_fn(png_structp, png_voidp, png_error_ptr,
                                         png_error_ptr);                                    // 0x0086b230
extern "C" png_voidp __cdecl png_malloc(png_structp, png_uint_32);                          // 0x0086d7f0
extern "C" void __cdecl png_free(png_structp, png_voidp);                                   // 0x0086d850
extern "C" png_voidp __cdecl png_zalloc(png_voidp, unsigned int, unsigned int);             // 0x0086a9d0
extern "C" void __cdecl png_zfree(png_voidp, png_voidp);                                    // 0x0086aa20
extern "C" const char* __cdecl png_get_libpng_ver(png_structp);                             // 0x0086aec0
extern "C" void __cdecl png_set_read_fn(png_structp, png_voidp, png_rw_ptr);                // 0x0086d910
extern "C" int __cdecl inflateInit_(z_stream_s*, const char*, int);                         // 0x00868d90
extern "C" int __cdecl inflate(z_stream_s*, int);                                           // 0x00868e90
extern "C" void __cdecl png_read_start_row(png_structp);                                    // 0x00872f90
extern "C" void __cdecl png_combine_row(png_structp, png_bytep, int);                       // 0x00872680
extern "C" void __cdecl png_read_finish_row(png_structp);                                   // 0x008757c0
extern "C" void __cdecl png_read_filter_row(png_structp, png_row_info_struct*, png_bytep,
                                            png_bytep, int);                                // 0x00872dc0
extern "C" void __cdecl png_memcpy_check(png_structp, png_voidp, png_voidp, png_uint_32);  // 0x0086d760
extern "C" void __cdecl png_do_read_intrapixel(png_row_info_struct*, png_bytep);            // 0x00870f30
extern "C" void __cdecl png_do_read_transformations(png_structp);                           // 0x00871d50
extern "C" void __cdecl png_do_read_interlace(png_structp);                                 // 0x00872970
extern "C" __declspec(dllimport) int __cdecl _snprintf(char*, png_size_t, const char*, ...);
extern "C" __declspec(dllimport) void __cdecl abort(void);

// libpng zlib error codes
enum { Z_OK = 0, Z_STREAM_ERROR = -2, Z_MEM_ERROR = -4, Z_VERSION_ERROR = -6 };
enum { Z_SYNC_FLUSH = 2 };

// 4-byte chunk name comparison (inlined png_memcmp)
#define PNG_CHUNK_IS(name, lit) (*(const png_uint_32*)(name) == *(const png_uint_32*)(lit))
#define PNG_ROWBYTES(pixel_bits, width) \
    ((pixel_bits) >= 8 ? (((pixel_bits) >> 3) * (width)) : (((width) * (pixel_bits) + 7) >> 3))

// @ 0x0086b250
void __cdecl png_error(png_structp png_ptr, png_const_charp error_message)
{
    char msg[16];
    int offset;

    if (png_ptr != NULL)
    {
        if ((png_ptr->flags & (PNG_FLAG_STRIP_ERROR_NUMBERS | PNG_FLAG_STRIP_ERROR_TEXT)) != 0)
        {
            if (*error_message == '#')
            {
                for (offset = 1; offset < 15; offset += 2)
                {
                    if (error_message[offset] == ' ')
                        break;
                    if (error_message[offset + 1] == ' ')
                    {
                        offset++;
                        break;
                    }
                }
                if ((png_ptr->flags & PNG_FLAG_STRIP_ERROR_TEXT) == 0)
                    error_message += offset;
                else
                {
                    int i;

                    for (i = 0; i < offset - 1; i++)
                        msg[i] = error_message[i + 1];
                    msg[i] = '\0';
                    error_message = msg;
                }
            }
            else if ((png_ptr->flags & PNG_FLAG_STRIP_ERROR_TEXT) != 0)
            {
                msg[0] = '0';
                msg[1] = '\0';
                error_message = msg;
            }
        }
        if (png_ptr->error_fn != NULL)
            ((png_error_ptr)png_ptr->error_fn)(png_ptr, error_message);
    }
    png_default_error(png_ptr, error_message);
}

// @ 0x0086b300
void __cdecl png_warning(png_structp png_ptr, png_const_charp warning_message)
{
    int offset = 0;

    if (png_ptr != NULL)
    {
        if ((png_ptr->flags & (PNG_FLAG_STRIP_ERROR_NUMBERS | PNG_FLAG_STRIP_ERROR_TEXT)) != 0 &&
            *warning_message == '#')
        {
            for (offset = 1; offset < 15; offset += 2)
            {
                if (warning_message[offset] == ' ')
                    break;
                if (warning_message[offset + 1] == ' ')
                {
                    offset++;
                    break;
                }
            }
        }
        if (png_ptr->warning_fn != NULL)
            ((png_error_ptr)png_ptr->warning_fn)(png_ptr, warning_message + offset);
        return;
    }
    png_default_warning(png_ptr, warning_message);
}

// @ 0x0086b360
void __cdecl png_chunk_error(png_structp png_ptr, png_const_charp error_message)
{
    char msg[0x54];

    if (png_ptr == NULL)
    {
        png_error(png_ptr, error_message);
        return;
    }
    png_format_buffer(png_ptr, msg, error_message);
    png_error(png_ptr, msg);
}

// @ 0x0086b3b0
void __cdecl png_chunk_warning(png_structp png_ptr, png_const_charp warning_message)
{
    char msg[0x54];

    if (png_ptr == NULL)
    {
        png_warning(png_ptr, warning_message);
        return;
    }
    png_format_buffer(png_ptr, msg, warning_message);
    png_warning(png_ptr, msg);
}

// @ 0x0086b500
png_structp __cdecl png_create_read_struct_2(const char* user_png_ver, png_voidp error_ptr,
                                             png_error_ptr error_fn, png_error_ptr warn_fn,
                                             png_voidp mem_ptr, png_malloc_ptr malloc_fn,
                                             png_free_ptr free_fn)
{
    png_structp png_ptr;
    char msg[0x50];
    int i;

    png_ptr = png_create_png_struct(1, malloc_fn, mem_ptr);
    if (png_ptr == NULL)
        return NULL;

    png_ptr->user_width_max = 1000000;
    png_ptr->user_height_max = 1000000;

    if (setjmp(png_ptr->jmpbuf) != 0)
    {
        png_free(png_ptr, png_ptr->zbuf);
        png_ptr->zbuf = NULL;
        png_destroy_png_struct(png_ptr, free_fn, mem_ptr);
        return NULL;
    }

    png_set_mem_fn(png_ptr, mem_ptr, malloc_fn, free_fn);
    png_set_error_fn(png_ptr, error_ptr, error_fn, warn_fn);

    if (user_png_ver != NULL)
    {
        i = 0;
        do
        {
            if (user_png_ver[i] != png_get_libpng_ver(NULL)[i])
                png_ptr->flags |= PNG_FLAG_LIBRARY_MISMATCH;
        } while (png_get_libpng_ver(NULL)[i++] != '\0');
    }
    else
        png_ptr->flags |= PNG_FLAG_LIBRARY_MISMATCH;

    if ((png_ptr->flags & PNG_FLAG_LIBRARY_MISMATCH) != 0)
    {
        if (user_png_ver == NULL ||
            user_png_ver[0] != png_get_libpng_ver(NULL)[0] ||
            (user_png_ver[0] == '1' && user_png_ver[2] != png_get_libpng_ver(NULL)[2]) ||
            (user_png_ver[0] == '0' && user_png_ver[2] < '9'))
        {
            if (user_png_ver != NULL)
            {
                _snprintf(msg, 0x50, "Application was compiled with png.h from libpng-%.20s",
                          user_png_ver);
                png_warning(png_ptr, msg);
            }
            _snprintf(msg, 0x50, "Application  is  running with png.c from libpng-%.20s",
                      png_get_libpng_ver(NULL));
            png_warning(png_ptr, msg);
            png_ptr->flags = 0;
            png_error(png_ptr, "Incompatible libpng version in application and library");
        }
    }

    png_ptr->zbuf_size = PNG_ZBUF_SIZE;
    png_ptr->zbuf = (png_bytep)png_malloc(png_ptr, png_ptr->zbuf_size);
    png_ptr->zstream.zalloc = (void*)png_zalloc;
    png_ptr->zstream.zfree = (void*)png_zfree;
    png_ptr->zstream.opaque = png_ptr;

    switch (inflateInit_(&png_ptr->zstream, "1.2.3", sizeof(z_stream_s)))
    {
    case Z_OK:
        break;
    case Z_MEM_ERROR:
    case Z_STREAM_ERROR:
        png_error(png_ptr, "zlib memory error");
        break;
    case Z_VERSION_ERROR:
        png_error(png_ptr, "zlib version error");
        break;
    default:
        png_error(png_ptr, "Unknown zlib error");
        break;
    }

    png_ptr->zstream.next_out = png_ptr->zbuf;
    png_ptr->zstream.avail_out = png_ptr->zbuf_size;
    png_set_read_fn(png_ptr, NULL, NULL);

    if (setjmp(png_ptr->jmpbuf) != 0)
        abort();

    return png_ptr;
}

// @ 0x0086b750
void __cdecl png_read_info(png_structp png_ptr, png_infop info_ptr)
{
    png_byte chunk_length[4];
    png_uint_32 length;

    if (png_ptr == NULL || info_ptr == NULL)
        return;

    if (png_ptr->sig_bytes < 8)
    {
        png_uint_32 sig_bytes = png_ptr->sig_bytes;
        png_size_t num_to_read = 8 - sig_bytes;
        png_bytep buffer = info_ptr->signature + sig_bytes;

        png_read_data(png_ptr, buffer, num_to_read);
        png_ptr->sig_bytes = 8;

        if (png_sig_cmp(info_ptr->signature, sig_bytes, num_to_read) != 0)
        {
            if (sig_bytes < 4 &&
                png_sig_cmp(info_ptr->signature, sig_bytes, num_to_read - 4) != 0)
                png_error(png_ptr, "Not a PNG file");
            else
                png_error(png_ptr, "PNG file corrupted by ASCII conversion");
        }
        if (sig_bytes < 3)
            png_ptr->mode |= PNG_HAVE_PNG_SIGNATURE;
    }

    do
    {
        png_byte png_IHDR[8] = {'I', 'H', 'D', 'R'};
        png_byte png_IDAT[8] = {'I', 'D', 'A', 'T'};
        png_byte png_IEND[8] = {'I', 'E', 'N', 'D'};
        png_byte png_PLTE[8] = {'P', 'L', 'T', 'E'};
        png_byte png_bKGD[8] = {'b', 'K', 'G', 'D'};
        png_byte png_cHRM[8] = {'c', 'H', 'R', 'M'};
        png_byte png_gAMA[8] = {'g', 'A', 'M', 'A'};
        png_byte png_hIST[8] = {'h', 'I', 'S', 'T'};
        png_byte png_iCCP[8] = {'i', 'C', 'C', 'P'};
        png_byte png_oFFs[8] = {'o', 'F', 'F', 's'};
        png_byte png_pCAL[8] = {'p', 'C', 'A', 'L'};
        png_byte png_pHYs[8] = {'p', 'H', 'Y', 's'};
        png_byte png_sBIT[8] = {'s', 'B', 'I', 'T'};
        png_byte png_sCAL[8] = {'s', 'C', 'A', 'L'};
        png_byte png_sPLT[8] = {'s', 'P', 'L', 'T'};
        png_byte png_sRGB[8] = {'s', 'R', 'G', 'B'};
        png_byte png_tEXt[8] = {'t', 'E', 'X', 't'};
        png_byte png_tIME[8] = {'t', 'I', 'M', 'E'};
        png_byte png_tRNS[8] = {'t', 'R', 'N', 'S'};
        png_byte png_zTXt[8] = {'z', 'T', 'X', 't'};

        png_read_data(png_ptr, chunk_length, 4);
        length = png_get_uint_31(png_ptr, chunk_length);
        png_reset_crc(png_ptr);
        png_crc_read(png_ptr, png_ptr->chunk_name, 4);

        if (PNG_CHUNK_IS(png_ptr->chunk_name, png_IDAT) &&
            (png_ptr->mode & PNG_AFTER_IDAT) != 0)
            png_ptr->mode |= PNG_MULTIPLE_IDAT;

        if (PNG_CHUNK_IS(png_ptr->chunk_name, png_IHDR))
        {
            png_handle_IHDR(png_ptr, info_ptr, length);
            continue;
        }
        if (PNG_CHUNK_IS(png_ptr->chunk_name, png_IEND))
        {
            png_handle_IEND(png_ptr, info_ptr, length);
            continue;
        }

        if (png_handle_as_unknown(png_ptr, png_ptr->chunk_name) != 0)
        {
            if (PNG_CHUNK_IS(png_ptr->chunk_name, png_IDAT))
                png_ptr->mode |= PNG_HAVE_IDAT;
            png_handle_unknown(png_ptr, info_ptr, length);
            if (PNG_CHUNK_IS(png_ptr->chunk_name, png_PLTE))
            {
                png_ptr->mode |= PNG_HAVE_PLTE;
                continue;
            }
            if (!PNG_CHUNK_IS(png_ptr->chunk_name, png_IDAT))
                continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_PLTE))
        {
            png_handle_PLTE(png_ptr, info_ptr, length);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_bKGD))
        {
            png_handle_bKGD(png_ptr, info_ptr);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_cHRM))
        {
            png_handle_cHRM(png_ptr, info_ptr);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_gAMA))
        {
            png_handle_gAMA(png_ptr, info_ptr);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_hIST))
        {
            png_handle_hIST(png_ptr, info_ptr);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_oFFs))
        {
            png_handle_oFFs(png_ptr, info_ptr);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_pCAL))
        {
            png_handle_pCAL(png_ptr, info_ptr);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_sCAL))
        {
            png_handle_sCAL(png_ptr, info_ptr);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_pHYs))
        {
            png_handle_pHYs(png_ptr, info_ptr);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_sBIT))
        {
            png_handle_sBIT(png_ptr, info_ptr);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_sRGB))
        {
            png_handle_sRGB(png_ptr, info_ptr);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_iCCP))
        {
            png_handle_iCCP(png_ptr, info_ptr);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_sPLT))
        {
            png_handle_sPLT(png_ptr, info_ptr);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_tEXt))
        {
            png_handle_tEXt(png_ptr, info_ptr);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_tIME))
        {
            png_handle_tIME(png_ptr, info_ptr);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_tRNS))
        {
            png_handle_tRNS(png_ptr, info_ptr);
            continue;
        }
        else if (PNG_CHUNK_IS(png_ptr->chunk_name, png_zTXt))
        {
            png_handle_zTXt(png_ptr, info_ptr);
            continue;
        }
        else
        {
            png_handle_unknown(png_ptr, info_ptr, length);
            continue;
        }

        /* IDAT */
        if ((png_ptr->mode & PNG_HAVE_IHDR) == 0)
            png_error(png_ptr, "Missing IHDR before IDAT");
        else if (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE &&
                 (png_ptr->mode & PNG_HAVE_PLTE) == 0)
            png_error(png_ptr, "Missing PLTE before IDAT");
        png_ptr->mode |= PNG_HAVE_IDAT;
        png_ptr->idat_size = length;
        return;
    } while (1);
}

// @ 0x0086bd90
void __cdecl png_read_row(png_structp png_ptr, png_bytep row, png_bytep dsp_row)
{
    png_byte png_IDAT[8] = {'I', 'D', 'A', 'T'};
    png_uint_32 mask[14] = {0xff, 0x0f, 0xff, 0x33, 0xff, 0x55, 0xff,
                            0x80, 0x08, 0x88, 0x22, 0xaa, 0x55, 0xff};
    png_byte chunk_length[4];
    int ret;

    if (png_ptr == NULL)
        return;

    if ((png_ptr->flags & PNG_FLAG_ROW_INIT) == 0)
        png_read_start_row(png_ptr);

    if (png_ptr->interlaced && (png_ptr->transformations & PNG_INTERLACE))
    {
        switch (png_ptr->pass)
        {
        case 0:
            if ((png_ptr->row_number & 0x07) != 0)
            {
                if (dsp_row != NULL)
                    png_combine_row(png_ptr, dsp_row, 0xff);
                png_read_finish_row(png_ptr);
                return;
            }
            break;
        case 1:
            if ((png_ptr->row_number & 0x07) != 0 || png_ptr->width < 5)
            {
                if (dsp_row != NULL)
                    png_combine_row(png_ptr, dsp_row, 0x0f);
                png_read_finish_row(png_ptr);
                return;
            }
            break;
        case 2:
            if ((png_ptr->row_number & 0x07) != 4)
            {
                if (dsp_row != NULL && (png_ptr->row_number & 0x04) != 0)
                    png_combine_row(png_ptr, dsp_row, 0xff);
                png_read_finish_row(png_ptr);
                return;
            }
            break;
        case 3:
            if ((png_ptr->row_number & 0x03) != 0 || png_ptr->width < 3)
            {
                if (dsp_row != NULL)
                    png_combine_row(png_ptr, dsp_row, 0x33);
                png_read_finish_row(png_ptr);
                return;
            }
            break;
        case 4:
            if ((png_ptr->row_number & 0x03) != 2)
            {
                if (dsp_row != NULL && (png_ptr->row_number & 0x02) != 0)
                    png_combine_row(png_ptr, dsp_row, 0xff);
                png_read_finish_row(png_ptr);
                return;
            }
            break;
        case 5:
            if ((png_ptr->row_number & 0x01) != 0 || png_ptr->width < 2)
            {
                if (dsp_row != NULL)
                    png_combine_row(png_ptr, dsp_row, 0x55);
                png_read_finish_row(png_ptr);
                return;
            }
            break;
        case 6:
            if ((png_ptr->row_number & 0x01) == 0)
            {
                png_read_finish_row(png_ptr);
                return;
            }
            break;
        }
    }

    if ((png_ptr->mode & PNG_HAVE_IDAT) == 0)
        png_error(png_ptr, "Invalid attempt to read row data");

    png_ptr->zstream.next_out = png_ptr->row_buf;
    png_ptr->zstream.avail_out = png_ptr->irowbytes;
    do
    {
        if (png_ptr->zstream.avail_in == 0)
        {
            while (png_ptr->idat_size == 0)
            {
                png_crc_finish(png_ptr, 0);
                png_read_data(png_ptr, chunk_length, 4);
                png_ptr->idat_size = png_get_uint_31(png_ptr, chunk_length);
                png_reset_crc(png_ptr);
                png_crc_read(png_ptr, png_ptr->chunk_name, 4);
                if (!PNG_CHUNK_IS(png_ptr->chunk_name, png_IDAT))
                    png_error(png_ptr, "Not enough image data");
            }
            png_ptr->zstream.avail_in = png_ptr->zbuf_size;
            png_ptr->zstream.next_in = png_ptr->zbuf;
            if (png_ptr->zstream.avail_in > png_ptr->idat_size)
                png_ptr->zstream.avail_in = png_ptr->idat_size;
            png_crc_read(png_ptr, png_ptr->zbuf, png_ptr->zstream.avail_in);
            png_ptr->idat_size -= png_ptr->zstream.avail_in;
        }
        ret = inflate(&png_ptr->zstream, 1); /* Z_SYNC_FLUSH in this build */
        if (ret == 1)
        {
            if (png_ptr->zstream.avail_out != 0 || png_ptr->zstream.avail_in != 0 ||
                png_ptr->idat_size != 0)
                png_error(png_ptr, "Extra compressed data");
            png_ptr->mode |= PNG_AFTER_IDAT;
            png_ptr->flags |= PNG_FLAG_ZSTREAM_ENDED;
            break;
        }
        if (ret != Z_OK)
        {
            const char* msg = png_ptr->zstream.msg;

            if (msg == NULL)
                msg = "Decompression error";
            png_error(png_ptr, msg);
        }
    } while (png_ptr->zstream.avail_out != 0);

    png_ptr->row_info.color_type = png_ptr->color_type;
    png_ptr->row_info.width = png_ptr->iwidth;
    png_ptr->row_info.channels = png_ptr->channels;
    png_ptr->row_info.bit_depth = png_ptr->bit_depth;
    png_ptr->row_info.pixel_depth = png_ptr->pixel_depth;
    png_ptr->row_info.rowbytes = PNG_ROWBYTES(png_ptr->row_info.pixel_depth,
                                             png_ptr->row_info.width);

    if (png_ptr->row_buf[0] != 0)
        png_read_filter_row(png_ptr, &png_ptr->row_info, png_ptr->row_buf + 1,
                            png_ptr->prev_row + 1, png_ptr->row_buf[0]);

    png_memcpy_check(png_ptr, png_ptr->prev_row, png_ptr->row_buf, png_ptr->rowbytes + 1);

    if ((png_ptr->mng_features_permitted & PNG_FLAG_MNG_FILTER_64) != 0 &&
        png_ptr->filter_type == PNG_INTRAPIXEL_DIFFERENCING)
        png_do_read_intrapixel(&png_ptr->row_info, png_ptr->row_buf + 1);

    if (png_ptr->transformations != 0 || (png_ptr->flags & PNG_FLAG_READ_TRANSFORM) != 0)
        png_do_read_transformations(png_ptr);

    if (png_ptr->interlaced && (png_ptr->transformations & PNG_INTERLACE))
    {
        if (png_ptr->pass < 6)
            png_do_read_interlace(png_ptr);
        if (dsp_row != NULL)
            png_combine_row(png_ptr, dsp_row, mask[png_ptr->pass]);
        if (row != NULL)
            png_combine_row(png_ptr, row, mask[png_ptr->pass + 7]);
    }
    else
    {
        if (row != NULL)
            png_combine_row(png_ptr, row, 0xff);
        if (dsp_row != NULL)
            png_combine_row(png_ptr, dsp_row, 0xff);
    }

    png_read_finish_row(png_ptr);

    if (png_ptr->read_row_fn != NULL)
        ((png_read_status_ptr)png_ptr->read_row_fn)(png_ptr, png_ptr->row_number, png_ptr->pass);
}
