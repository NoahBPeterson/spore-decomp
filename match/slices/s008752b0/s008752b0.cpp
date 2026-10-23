// Slice s008752b0 -- Spore's bundled libpng 1.2.x: chunk handlers, cHRM/gamma
// setters, row finishing and the write-side compression helper.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The two structs below model every png_struct / png_info offset this slice
// touches; padding keeps the offsets exact.
#include "types.h"

typedef unsigned char  png_byte;
typedef unsigned short png_uint_16;
typedef unsigned int   png_uint_32;
typedef int            png_fixed_point;
typedef unsigned int   png_size_t;

// ---------------------------------------------------------------------------------------------
// png_struct
// ---------------------------------------------------------------------------------------------
struct PngStruct {
    char pad000[0x68];
    unsigned int   mode;                 // +0x68
    unsigned int   flags;                // +0x6c
    unsigned char  transformations;      // +0x70
    char pad071[0x74 - 0x71];
    png_byte*      znext_in;             // +0x74  zstream.next_in
    unsigned int   z_avail_in;           // +0x78  zstream.avail_in
    char pad07c[0x80 - 0x7c];
    png_byte*      znext_out;            // +0x80  zstream.next_out
    unsigned int   z_avail_out;          // +0x84  zstream.avail_out
    char pad088[0x8c - 0x88];
    char*          zmsg;                 // +0x8c  zstream.msg
    char pad090[0xac - 0x90];
    png_byte*      zbuf;                 // +0xac
    png_size_t     zbuf_size;            // +0xb0
    char pad0b4[0xc8 - 0xb4];
    png_uint_32    width;                // +0xc8
    png_uint_32    height;               // +0xcc
    png_uint_32    num_rows;             // +0xd0
    char pad0d4[0xd8 - 0xd4];
    png_size_t     rowbytes;             // +0xd8
    unsigned int   irowbytes;            // +0xdc
    unsigned int   iwidth;               // +0xe0
    unsigned int   row_number;           // +0xe4
    png_byte*      prev_row;             // +0xe8
    char pad0ec[0x10c - 0xec];
    png_uint_32    idat_size;            // +0x10c
    char pad110[0x11c - 0x110];
    png_byte       chunk_name[5];        // +0x11c
    char pad121[0x123 - 0x121];
    unsigned char  interlaced;           // +0x123
    unsigned char  pass;                 // +0x124
    char pad125[0x129 - 0x125];
    unsigned char  pixel_depth;          // +0x129
    char pad12a[0x12c - 0x12a];
    png_byte       sig_bytes;            // +0x12c
    char pad12d[0x21c - 0x12d];
    int (*read_user_chunk_fn)(PngStruct*, void*);   // +0x21c
    char pad220[0x26c - 0x220];
    png_byte       unk_name[5];          // +0x26c
    char pad271[0x274 - 0x271];
    png_byte*      unk_data;             // +0x274
    png_size_t     unk_size;             // +0x278
};

// ---------------------------------------------------------------------------------------------
// png_info
// ---------------------------------------------------------------------------------------------
struct PngInfo {
    char pad000[0x08];
    unsigned int   valid;                // +0x08
    char pad00c[0x28 - 0x0c];
    float          gamma;                // +0x28
    char pad02c[0x80 - 0x2c];
    float          x_white;              // +0x80
    float          y_white;              // +0x84
    float          x_red;                // +0x88
    float          y_red;                // +0x8c
    float          x_green;              // +0x90
    float          y_green;              // +0x94
    float          x_blue;               // +0x98
    float          y_blue;               // +0x9c
    char pad0a0[0xfc - 0xa0];
    png_fixed_point int_gamma;           // +0xfc
    png_fixed_point int_x_white;         // +0x100
    png_fixed_point int_y_white;         // +0x104
    png_fixed_point int_x_red;           // +0x108
    png_fixed_point int_y_red;           // +0x10c
    png_fixed_point int_x_green;         // +0x110
    png_fixed_point int_y_green;         // +0x114
    png_fixed_point int_x_blue;          // +0x118
    png_fixed_point int_y_blue;          // +0x11c
};

typedef struct { png_uint_16 year; png_byte month, day, hour, minute, second; } png_time;

// ---------------------------------------------------------------------------------------------
// constants
// ---------------------------------------------------------------------------------------------
#define PNG_HAVE_IHDR               0x0001
#define PNG_HAVE_IDAT               0x0004
#define PNG_AFTER_IDAT              0x0008
#define PNG_HAVE_PNG_SIGNATURE      0x1000

#define PNG_INFO_gAMA               0x0001
#define PNG_INFO_cHRM               0x0004
#define PNG_INFO_tIME               0x0200

#define PNG_FLAG_ZLIB_FINISHED      0x0020
#define PNG_FLAG_KEEP_UNKNOWN_CHUNKS 0x8000

#define PNG_INTERLACE               0x02
#define PNG_HANDLE_CHUNK_ALWAYS     3

// ---------------------------------------------------------------------------------------------
// helpers defined in the same libpng module (call targets are relocations)
// ---------------------------------------------------------------------------------------------
void  png_error(PngStruct* png_ptr, const char* msg);
void  png_chunk_error(PngStruct* png_ptr, const char* msg);
void  png_warning(PngStruct* png_ptr, const char* msg);
void  png_read_data(PngStruct* png_ptr, png_byte* data, png_size_t length);
void  png_calculate_crc(PngStruct* png_ptr, png_byte* ptr, png_size_t length);
int   png_crc_finish(PngStruct* png_ptr, png_size_t skip);
void  png_reset_crc(PngStruct* png_ptr);
void  png_check_chunk_name(PngStruct* png_ptr, png_byte* chunk_name);
int   png_handle_as_unknown(PngStruct* png_ptr, png_byte* chunk_name);
void* png_malloc(PngStruct* png_ptr, png_size_t size);
void  png_free(PngStruct* png_ptr, void* ptr);
void  png_set_unknown_chunks(PngStruct* png_ptr, PngInfo* info_ptr, void* unknown_chunks, int num);
void  png_set_tIME(PngStruct* png_ptr, PngInfo* info_ptr, png_time* mod_time);
void  png_write_data(PngStruct* png_ptr, png_byte* data, png_size_t length);
void  png_memset_check(PngStruct* png_ptr, void* dest, int value, png_size_t size);
int   inflate(void* strm, int flush);
int   inflateReset(void* strm);
int   deflate(void* strm, int flush);
void  mem_copy(void* dst, const void* src, png_size_t size);
int   _snprintf(char* buffer, png_size_t count, const char* format, ...);

// ===================================================================================================
// 0x008752b0  png_handle_tIME: read + store a tIME chunk.
// ===================================================================================================
// @ 0x008752b0
__declspec(noinline) void png_handle_tIME(PngStruct* png_ptr, PngInfo* info_ptr, png_uint_32 length)
{
    png_byte buf[7];
    png_time mod_time;

    if (!(png_ptr->mode & PNG_HAVE_IHDR))
        png_error(png_ptr, "Out of place tIME chunk");
    else if (info_ptr != 0 && (info_ptr->valid & PNG_INFO_tIME))
    {
        png_warning(png_ptr, "Duplicate tIME chunk");
        png_crc_finish(png_ptr, length);
        return;
    }

    if (png_ptr->mode & PNG_HAVE_IDAT)
        png_ptr->mode |= PNG_AFTER_IDAT;

    if (length != 7)
    {
        png_warning(png_ptr, "Incorrect tIME chunk length");
        png_crc_finish(png_ptr, length);
        return;
    }

    png_read_data(png_ptr, buf, 7);
    png_calculate_crc(png_ptr, buf, 7);

    if (png_crc_finish(png_ptr, 0) != 0)
        return;

    mod_time.second = buf[6];
    mod_time.minute = buf[5];
    mod_time.hour   = buf[4];
    mod_time.day    = buf[3];
    mod_time.month  = buf[2];
    mod_time.year   = (png_uint_16)((png_uint_16)buf[0] * 256 + (png_uint_16)buf[1]);

    png_set_tIME(png_ptr, info_ptr, &mod_time);
}

// ===================================================================================================
// 0x00875640  png_handle_unknown: keep or skip an unknown chunk.
// ===================================================================================================
// @ 0x00875640
__declspec(noinline) void png_handle_unknown(PngStruct* png_ptr, PngInfo* info_ptr, png_uint_32 length)
{
    png_uint_32 skip = 0;

    if (png_ptr->mode & PNG_HAVE_IDAT)
    {
        const png_byte png_IDAT[5] = { 73, 68, 65, 84, 0 };
        if (*(png_uint_32*)png_ptr->chunk_name != *(const png_uint_32*)png_IDAT)
            png_ptr->mode |= PNG_AFTER_IDAT;
    }

    png_check_chunk_name(png_ptr, png_ptr->chunk_name);

    if (!(png_ptr->chunk_name[0] & 0x20))
    {
        if (png_handle_as_unknown(png_ptr, png_ptr->chunk_name) != PNG_HANDLE_CHUNK_ALWAYS
            && png_ptr->read_user_chunk_fn == 0)
            png_chunk_error(png_ptr, "unknown critical chunk");
    }

    if (!(png_ptr->flags & PNG_FLAG_KEEP_UNKNOWN_CHUNKS) && png_ptr->read_user_chunk_fn == 0)
    {
        png_crc_finish(png_ptr, length);
        return;
    }

    *(png_uint_32*)png_ptr->unk_name = *(png_uint_32*)png_ptr->chunk_name;
    png_ptr->unk_name[4] = 0;
    png_ptr->unk_data = (png_byte*)png_malloc(png_ptr, length);
    png_ptr->unk_size = (png_size_t)length;
    png_read_data(png_ptr, png_ptr->unk_data, length);
    png_calculate_crc(png_ptr, png_ptr->unk_data, length);

    if (png_ptr->read_user_chunk_fn != 0)
    {
        int r = png_ptr->read_user_chunk_fn(png_ptr, (void*)((char*)png_ptr + 0x26c));
        if (r < 0)
            png_chunk_error(png_ptr, "error in user chunk");
        if (r != 0)
            goto done;
        if (!(png_ptr->chunk_name[0] & 0x20)
            && png_handle_as_unknown(png_ptr, png_ptr->chunk_name) != PNG_HANDLE_CHUNK_ALWAYS)
            png_chunk_error(png_ptr, "unknown critical chunk");
    }

    png_set_unknown_chunks(png_ptr, info_ptr, (void*)((char*)png_ptr + 0x26c), 1);

done:
    png_free(png_ptr, png_ptr->unk_data);
    png_ptr->unk_data = 0;
    png_crc_finish(png_ptr, skip);
}

// ===================================================================================================
// 0x008757c0  png_read_finish_row: advance the row/pass cursor and drain the IDAT stream.
// ===================================================================================================
// @ 0x008757c0
__declspec(noinline) void png_read_finish_row(PngStruct* png_ptr)
{
    const int png_pass_inc[7]    = { 8, 8, 4, 4, 2, 2, 1 };
    const int png_pass_start[7]  = { 0, 4, 0, 2, 0, 1, 0 };
    const int png_pass_yinc[7]   = { 8, 8, 8, 4, 4, 2, 2 };
    const int png_pass_ystart[7] = { 0, 0, 4, 0, 2, 0, 1 };

    png_ptr->row_number++;
    if (png_ptr->row_number < png_ptr->num_rows)
        return;

    if (png_ptr->interlaced)
    {
        unsigned char pass;
        unsigned iwidth;

        png_ptr->row_number = 0;
        png_memset_check(png_ptr, png_ptr->prev_row, 0, png_ptr->rowbytes + 1);
        do
        {
            png_ptr->pass++;
            pass = png_ptr->pass;
            if (pass >= 7)
                break;
            iwidth = (png_ptr->width - png_pass_start[pass] - 1 + png_pass_inc[pass])
                     / png_pass_inc[pass];
            png_ptr->iwidth = iwidth;
            if (png_ptr->pixel_depth < 8)
                png_ptr->irowbytes = ((png_ptr->pixel_depth * iwidth + 7) >> 3) + 1;
            else
                png_ptr->irowbytes = ((png_ptr->pixel_depth >> 3) * iwidth) + 1;
            if (png_ptr->transformations & PNG_INTERLACE)
                break;
            png_ptr->num_rows = (png_ptr->height - png_pass_ystart[pass] - 1 + png_pass_yinc[pass])
                                / png_pass_yinc[pass];
        } while (iwidth == 0);
        if (pass < 7)
            return;
    }

    if (!(png_ptr->flags & PNG_FLAG_ZLIB_FINISHED))
    {
        png_byte idat[4];
        char extra;
        unsigned ret;

        idat[0] = 'I'; idat[1] = 'D'; idat[2] = 'A'; idat[3] = 'T';
        png_ptr->znext_out = (png_byte*)&extra;
        png_ptr->z_avail_out = 1;
        do
        {
            if (png_ptr->z_avail_in == 0)
            {
                if (png_ptr->idat_size == 0)
                {
                    do
                    {
                        png_crc_finish(png_ptr, 0);
                        png_read_data(png_ptr, idat, 4);
                        unsigned n = ((unsigned)idat[0] << 24) | ((unsigned)idat[1] << 16) |
                                     ((unsigned)idat[2] << 8) | (unsigned)idat[3];
                        if (n > 0x7fffffffU)
                            png_error(png_ptr, "PNG unsigned integer out of range.");
                        png_ptr->idat_size = n;
                        png_reset_crc(png_ptr);
                        png_read_data(png_ptr, png_ptr->chunk_name, 4);
                        png_calculate_crc(png_ptr, png_ptr->chunk_name, 4);
                        if (*(png_uint_32*)png_ptr->chunk_name != 0x54414449U)
                            png_error(png_ptr, "Not enough image data");
                    } while (png_ptr->idat_size == 0);
                }
                png_ptr->znext_in = png_ptr->zbuf;
                png_ptr->z_avail_in = png_ptr->zbuf_size;
                if (png_ptr->idat_size < png_ptr->zbuf_size)
                    png_ptr->z_avail_in = png_ptr->idat_size;
                png_read_data(png_ptr, png_ptr->zbuf, png_ptr->z_avail_in);
                png_calculate_crc(png_ptr, png_ptr->zbuf, png_ptr->z_avail_in);
                png_ptr->idat_size -= png_ptr->z_avail_in;
            }

            ret = (unsigned)inflate((char*)png_ptr + 0x74, 1);
            if (ret == 1)
            {
                if (png_ptr->z_avail_out != 0 && png_ptr->z_avail_in == 0
                    && png_ptr->idat_size == 0)
                    goto finished;
                png_warning(png_ptr, "Extra compressed data");
                goto finished;
            }
            if (ret != 0)
            {
                char* m = png_ptr->zmsg;
                if (m == 0)
                    m = "Decompression Error";
                png_error(png_ptr, m);
            }
        } while (png_ptr->z_avail_out != 0);
        png_warning(png_ptr, "Extra compressed data.");

finished:
        png_ptr->mode |= PNG_AFTER_IDAT;
        png_ptr->flags |= PNG_FLAG_ZLIB_FINISHED;
        png_ptr->z_avail_out = 0;
    }

    if (png_ptr->idat_size != 0 || png_ptr->z_avail_in != 0)
        png_warning(png_ptr, "Extra compression data");

    inflateReset((char*)png_ptr + 0x74);
    png_ptr->mode |= PNG_AFTER_IDAT;
}

// ===================================================================================================
// 0x00875b40  png_set_cHRM (double form).
// ===================================================================================================
// @ 0x00875b40
__declspec(noinline) void png_set_cHRM(PngStruct* png_ptr, PngInfo* info_ptr,
    double white_x, double white_y, double red_x, double red_y,
    double green_x, double green_y, double blue_x, double blue_y)
{
    if (png_ptr == 0)
        return;
    if (info_ptr == 0)
        return;

    if (white_x == 0.0 && white_y == 0.0 && red_x == 0.0 && red_y == 0.0 &&
        green_x == 0.0 && green_y == 0.0 && blue_x == 0.0 && blue_y == 0.0)
    {
        png_warning(png_ptr, "Ignoring attempt to set all-zero chromaticity values");
        return;
    }

    if (white_x < 0.0 || white_y < 0.0 || red_x < 0.0 || red_y < 0.0 ||
        green_x < 0.0 || green_y < 0.0 || blue_x < 0.0 || blue_y < 0.0)
    {
        png_warning(png_ptr, "Ignoring attempt to set negative chromaticity value");
        return;
    }

    if (white_x > 21474.83 || white_y > 21474.83 || red_x > 21474.83 || red_y > 21474.83 ||
        green_x > 21474.83 || green_y > 21474.83 || blue_x > 21474.83 || blue_y > 21474.83)
    {
        png_warning(png_ptr, "Ignoring attempt to set chromaticity value exceeding 21474.83");
        return;
    }

    info_ptr->x_white = (float)white_x;
    info_ptr->y_white = (float)white_y;
    info_ptr->x_red   = (float)red_x;
    info_ptr->y_red   = (float)red_y;
    info_ptr->x_green = (float)green_x;
    info_ptr->y_green = (float)green_y;
    info_ptr->x_blue  = (float)blue_x;
    info_ptr->y_blue  = (float)blue_y;

    info_ptr->int_x_white = (png_fixed_point)(white_x * 100000. + 0.5);
    info_ptr->int_y_white = (png_fixed_point)(white_y * 100000. + 0.5);
    info_ptr->int_x_red   = (png_fixed_point)(red_x   * 100000. + 0.5);
    info_ptr->int_y_red   = (png_fixed_point)(red_y   * 100000. + 0.5);
    info_ptr->int_x_green = (png_fixed_point)(green_x * 100000. + 0.5);
    info_ptr->int_y_green = (png_fixed_point)(green_y * 100000. + 0.5);
    info_ptr->int_x_blue  = (png_fixed_point)(blue_x  * 100000. + 0.5);
    info_ptr->int_y_blue  = (png_fixed_point)(blue_y  * 100000. + 0.5);

    info_ptr->valid |= PNG_INFO_cHRM;
}

// ===================================================================================================
// 0x00875e50  png_set_cHRM_fixed (fixed-point form).
// ===================================================================================================
// @ 0x00875e50
__declspec(noinline) void png_set_cHRM_fixed(PngStruct* png_ptr, PngInfo* info_ptr,
    png_fixed_point white_x, png_fixed_point white_y,
    png_fixed_point red_x, png_fixed_point red_y,
    png_fixed_point green_x, png_fixed_point green_y,
    png_fixed_point blue_x, png_fixed_point blue_y)
{
    if (png_ptr == 0)
        return;
    if (info_ptr == 0)
        return;

    if (white_x == 0 && white_y == 0 && red_x == 0 && red_y == 0 &&
        green_x == 0 && green_y == 0 && blue_x == 0 && blue_y == 0)
    {
        png_warning(png_ptr, "Ignoring attempt to set all-zero chromaticity values");
        return;
    }

    if (white_x < 0 || white_y < 0 || red_x < 0 || red_y < 0 ||
        green_x < 0 || green_y < 0 || blue_x < 0 || blue_y < 0)
    {
        png_warning(png_ptr, "Ignoring attempt to set negative chromaticity value");
        return;
    }

    if (white_x > 0x7fffffff || white_y > 0x7fffffff || red_x > 0x7fffffff || red_y > 0x7fffffff ||
        green_x > 0x7fffffff || green_y > 0x7fffffff || blue_x > 0x7fffffff || blue_y > 0x7fffffff)
    {
        png_warning(png_ptr, "Ignoring attempt to set chromaticity value exceeding 21474.83");
        return;
    }

    info_ptr->valid |= PNG_INFO_cHRM;

    info_ptr->int_x_white = white_x;
    info_ptr->int_y_white = white_y;
    info_ptr->int_x_red   = red_x;
    info_ptr->int_y_red   = red_y;
    info_ptr->int_x_green = green_x;
    info_ptr->int_y_green = green_y;
    info_ptr->int_x_blue  = blue_x;
    info_ptr->int_y_blue  = blue_y;

    info_ptr->x_white = (float)(white_x * 1e-05);
    info_ptr->y_white = (float)(white_y * 1e-05);
    info_ptr->x_red   = (float)(red_x   * 1e-05);
    info_ptr->y_red   = (float)(red_y   * 1e-05);
    info_ptr->x_green = (float)(green_x * 1e-05);
    info_ptr->y_green = (float)(green_y * 1e-05);
    info_ptr->x_blue  = (float)(blue_x  * 1e-05);
    info_ptr->y_blue  = (float)(blue_y  * 1e-05);
}

// ===================================================================================================
// 0x00876040  png_set_gamma (double form).
// ===================================================================================================
// @ 0x00876040
__declspec(noinline) void png_set_gamma(PngStruct* png_ptr, PngInfo* info_ptr, double scrn_gamma)
{
    if (png_ptr == 0)
        return;
    if (info_ptr == 0)
        return;

    if (scrn_gamma > 21474.83)
    {
        png_warning(png_ptr, "Limiting gamma to 21474.83");
        scrn_gamma = 21474.83;
    }

    info_ptr->gamma = (float)scrn_gamma;
    info_ptr->int_gamma = (png_fixed_point)(scrn_gamma * 100000. + 0.5);
    info_ptr->valid |= PNG_INFO_gAMA;

    if (scrn_gamma == 0.0)
        png_warning(png_ptr, "Setting gamma=0");
}

// ===================================================================================================
// 0x008760c0  png_set_gamma_fixed (fixed-point form).
// ===================================================================================================
// @ 0x008760c0
__declspec(noinline) void png_set_gamma_fixed(PngStruct* png_ptr, PngInfo* info_ptr,
    png_fixed_point scrn_gamma)
{
    if (png_ptr == 0)
        return;
    if (info_ptr == 0)
        return;

    if (scrn_gamma > 0x7fffffff)
    {
        png_warning(png_ptr, "Limiting gamma to 21474.83");
        scrn_gamma = 0x7fffffff;
    }
    else if (scrn_gamma < 0)
    {
        png_warning(png_ptr, "Setting negative gamma to zero");
        scrn_gamma = 0;
    }

    info_ptr->valid |= PNG_INFO_gAMA;
    info_ptr->int_gamma = scrn_gamma;
    info_ptr->gamma = (float)(scrn_gamma * 1e-05);

    if (scrn_gamma == 0)
        png_warning(png_ptr, "Setting gamma=0");
}

// ===================================================================================================
// 0x00877d30  png_write_sig: emit the 8-byte PNG signature.
// ===================================================================================================
// @ 0x00877d30
__declspec(noinline) void png_write_sig(PngStruct* png_ptr)
{
    png_byte png_signature[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };

    png_write_data(png_ptr, &png_signature[png_ptr->sig_bytes],
        (png_size_t)(8 - png_ptr->sig_bytes));
    if (png_ptr->sig_bytes < 3)
        png_ptr->mode |= PNG_HAVE_PNG_SIGNATURE;
}

// ===================================================================================================
// 0x00877da0  png_write_compressed: write-side deflate helper.  The original is a private static
// helper that MSVC gave a custom register convention (type=EAX, png_ptr=EDX, len=ECX, data=[esp+4],
// vec=EDI), so the standalone cdecl form below cannot reproduce the entry sequence byte-for-byte;
// the body is otherwise a faithful transcription.
// ===================================================================================================
// @ 0x00877da0
__declspec(noinline) int png_write_compressed(int type, PngStruct* png_ptr, unsigned len,
                                              png_byte* data, int* vec)
{
    vec[0] = 0;
    vec[1] = 0;
    vec[2] = 0;
    vec[3] = 0;
    vec[4] = 0;

    if (type == -1)
    {
        vec[0] = (int)data;
        vec[1] = (int)len;
        return (int)len;
    }

    if (type > 2)
    {
        char buf[50];
        _snprintf(buf, 50, "Unknown compression type %d", type);
        png_warning(png_ptr, buf);
    }

    png_ptr->z_avail_in = len;
    png_ptr->znext_in = data;
    png_ptr->z_avail_out = png_ptr->zbuf_size;
    png_ptr->znext_out = png_ptr->zbuf;

    do
    {
        if (deflate((char*)png_ptr + 0x74, 0) != 0)
        {
            char* m = png_ptr->zmsg;
            png_error(png_ptr, m != 0 ? m : "zlib error");
        }
        if (png_ptr->z_avail_out == 0)
        {
            int cap = vec[3];
            if (cap <= vec[2])
            {
                void* old = (void*)vec[4];
                int ncap = vec[2] + 4;
                vec[3] = ncap;
                if (old == 0)
                {
                    vec[4] = (int)png_malloc(png_ptr, ncap * 4);
                }
                else
                {
                    void* nw = png_malloc(png_ptr, ncap * 4);
                    vec[4] = (int)nw;
                    mem_copy(nw, old, cap * 4);
                    png_free(png_ptr, old);
                }
            }
            png_byte* p = (png_byte*)png_malloc(png_ptr, png_ptr->zbuf_size);
            *(png_byte**)(vec[4] + vec[2] * 4) = p;
            mem_copy(p, png_ptr->zbuf, png_ptr->zbuf_size);
            vec[2] = vec[2] + 1;
            png_ptr->z_avail_out = png_ptr->zbuf_size;
            png_ptr->znext_out = png_ptr->zbuf;
        }
    } while (png_ptr->z_avail_in != 0);

    for (;;)
    {
        int ret = deflate((char*)png_ptr + 0x74, 4);
        if (ret != 0)
        {
            if (ret == 1)
                break;
            {
                char* m = png_ptr->zmsg;
                png_error(png_ptr, m != 0 ? m : "zlib error");
            }
        }
        if (png_ptr->z_avail_out == 0)
        {
            int cap = vec[3];
            if (cap <= vec[2])
            {
                void* old = (void*)vec[4];
                int ncap = vec[2] + 4;
                vec[3] = ncap;
                if (old == 0)
                {
                    vec[4] = (int)png_malloc(png_ptr, ncap * 4);
                }
                else
                {
                    void* nw = png_malloc(png_ptr, ncap * 4);
                    vec[4] = (int)nw;
                    mem_copy(nw, old, cap * 4);
                    png_free(png_ptr, old);
                }
            }
            png_byte* p = (png_byte*)png_malloc(png_ptr, png_ptr->zbuf_size);
            *(png_byte**)(vec[4] + vec[2] * 4) = p;
            mem_copy(p, png_ptr->zbuf, png_ptr->zbuf_size);
            vec[2] = vec[2] + 1;
            png_ptr->z_avail_out = png_ptr->zbuf_size;
            png_ptr->znext_out = png_ptr->zbuf;
        }
    }

    unsigned zsize = png_ptr->zbuf_size;
    int total = vec[2] * zsize;
    if (png_ptr->z_avail_out < zsize)
        total += zsize - png_ptr->z_avail_out;
    return total;
}
