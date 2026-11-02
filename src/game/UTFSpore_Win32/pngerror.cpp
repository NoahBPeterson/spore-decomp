// src/game/UTFSpore_Win32/pngerror.cpp -- migrated from slice(s) s008680d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/pngerror.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) __declspec(noreturn) void __cdecl longjmp(void* env, int val);

// ---- items of slice s008680d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef const char* png_const_charp;
typedef struct { char _raw[0x20]; } FILE;
extern "C" __declspec(dllimport) FILE* __cdecl __iob_func(void);
extern "C" __declspec(dllimport) int   __cdecl fprintf(FILE* stream, const char* fmt, ...);
extern "C" __declspec(dllimport) __declspec(noreturn) void __cdecl longjmp(void* env, int val);
/* ===========================================================================
 * inflate.c -- updatewindow
 */
/* ===========================================================================
 * inftrees.c -- inflate_table
 */

/* ===========================================================================
 * png.c -- png_sig_cmp
 */

/* ===========================================================================
 * pngerror.c -- png_default_error / png_default_warning
 */
typedef struct png_struct_def {
    unsigned int flags;
} png_struct_def;
typedef png_struct_def* png_structp;
// ---- items of slice s008680d0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) FILE* __cdecl __iob_func(void);
extern "C" __declspec(dllimport) int   __cdecl fprintf(FILE* stream, const char* fmt, ...);

// @ 0x0086aff0
static void png_default_error(png_structp png_ptr, png_const_charp error_message)
{
    if (*error_message == '#') {
        int offset;
        char error_number[16];
        for (offset = 0; offset < 15; offset++) {
            error_number[offset] = *(error_message + offset + 1);
            if (*(error_message + offset) == ' ')
                break;
        }
        if ((offset > 1) && (offset < 15)) {
            error_number[offset - 1] = '\0';
            fprintf(__iob_func() + 2, "libpng error no. %s: %s\n",
                    error_number, error_message + offset);
        } else {
            fprintf(__iob_func() + 2, "libpng error: %s, offset=%d\n",
                    error_message, offset);
        }
    } else {
        fprintf(__iob_func() + 2, "libpng error: %s\n", error_message);
    }

    if (png_ptr) {
        longjmp(png_ptr, 1);
    }
}

// @ 0x0086b110
static void png_default_warning(png_structp png_ptr, png_const_charp warning_message)
{
    if (*warning_message == '#') {
        int offset;
        char warning_number[16];
        for (offset = 0; offset < 15; offset++) {
            warning_number[offset] = *(warning_message + offset + 1);
            if (*(warning_message + offset) == ' ')
                break;
        }
        if ((offset > 1) && (offset < 15)) {
            warning_number[offset - 1] = '\0';
            fprintf(__iob_func() + 2, "libpng warning no. %s: %s\n",
                    warning_number, warning_message + offset);
        } else {
            fprintf(__iob_func() + 2, "libpng warning: %s\n", warning_message);
        }
    } else {
        fprintf(__iob_func() + 2, "libpng warning: %s\n", warning_message);
    }
    png_ptr = png_ptr;
}
