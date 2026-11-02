// src/game/UTFSpore_Win32/pngwutil.cpp -- migrated from slice(s) s008752b0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/pngwutil.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s008752b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  png_byte;
typedef unsigned int   png_uint_32;
typedef unsigned int   png_size_t;
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
#define PNG_HAVE_PNG_SIGNATURE      0x1000
void  png_error(PngStruct* png_ptr, const char* msg);
void  png_warning(PngStruct* png_ptr, const char* msg);
void* png_malloc(PngStruct* png_ptr, png_size_t size);
void  png_free(PngStruct* png_ptr, void* ptr);
void  png_write_data(PngStruct* png_ptr, png_byte* data, png_size_t length);
int   deflate(void* strm, int flush);
void  mem_copy(void* dst, const void* src, png_size_t size);
int   _snprintf(char* buffer, png_size_t count, const char* format, ...);
// ---- items of slice s008752b0 end

// @ 0x00877d30
__declspec(noinline) void png_write_sig(PngStruct* png_ptr)
{
    png_byte png_signature[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };

    png_write_data(png_ptr, &png_signature[png_ptr->sig_bytes],
        (png_size_t)(8 - png_ptr->sig_bytes));
    if (png_ptr->sig_bytes < 3)
        png_ptr->mode |= PNG_HAVE_PNG_SIGNATURE;
}

// @ 0x00877da0
__declspec(noinline) int png_write_compressed(int type, PngStruct* png_ptr, unsigned len, png_byte* data, int* vec)
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
