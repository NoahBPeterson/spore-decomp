// src/game/UTFSpore_Win32/pngset.cpp -- migrated from slice(s) s008752b0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/pngset.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s008752b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  png_byte;
typedef unsigned int   png_uint_32;
typedef int            png_fixed_point;
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
#define PNG_INFO_gAMA               0x0001
#define PNG_INFO_cHRM               0x0004
void  png_warning(PngStruct* png_ptr, const char* msg);
// ---- items of slice s008752b0 end

// @ 0x00875b40
__declspec(noinline) void png_set_cHRM(PngStruct* png_ptr, PngInfo* info_ptr, double white_x, double white_y, double red_x, double red_y, double green_x, double green_y, double blue_x, double blue_y)
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

// @ 0x00875e50
__declspec(noinline) void png_set_cHRM_fixed(PngStruct* png_ptr, PngInfo* info_ptr, png_fixed_point white_x, png_fixed_point white_y, png_fixed_point red_x, png_fixed_point red_y, png_fixed_point green_x, png_fixed_point green_y, png_fixed_point blue_x, png_fixed_point blue_y)
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

// @ 0x008760c0
__declspec(noinline) void png_set_gamma_fixed(PngStruct* png_ptr, PngInfo* info_ptr, png_fixed_point scrn_gamma)
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
