// Slice s00864330 - libjpeg 6a encode/decode colour + upsample internals (SporeApp.exe)
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
//
// These are libjpeg 6a internals (jdmerge / jdsample / jdcolor / jdmaster / jcmaster)
// plus the Spore JPG glue, built with whole-program optimisation: several routines take
// arguments in fixed registers (EAX/ECX/ESI/EBX).  They are rewritten here with explicit
// arguments: complete source, faithful, but not byte-exact where a register ABI is fixed.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef int            boolean;

#define NULL 0
#define FALSE 0
#define TRUE  1

// --------------------------------------------------------------- libjpeg types
// Minimal mirrors of the libjpeg-6a structs, with the field offsets this build used.
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

#define TRACEMS1(cinfo,lvl,code,p1) \
    ((cinfo)->err->msg_code = (code), \
     (cinfo)->err->msg_parm.i[0] = (p1), \
     (*(cinfo)->err->emit_message)((void*)(cinfo), (lvl)))

#define TRACEMS4(cinfo,lvl,code,p1,p2,p3,p4) \
    ((cinfo)->err->msg_parm.i[0] = (p1), \
     (cinfo)->err->msg_parm.i[1] = (p2), \
     (cinfo)->err->msg_parm.i[2] = (p3), \
     (cinfo)->err->msg_parm.i[3] = (p4), \
     (cinfo)->err->msg_code = (code), \
     (*(cinfo)->err->emit_message)((void*)(cinfo), (lvl)))

// ------------------------------------------------------------------ runtime
extern "C" void*        __stdcall galloc(unsigned int size);                 // 0x0087d4a0
extern "C" unsigned char __stdcall gfree(void* p);                           // 0x0087d4c0
extern "C" unsigned int  __stdcall gfree_i(void* p);                         // 0x0087d4c0 (same fn)
extern "C" void*         __stdcall gfree_p(void* p);                         // 0x0087d4c0 (same fn)
extern "C" unsigned int __stdcall gread(void* h, void* buf, unsigned int n); // 0x0087d4e0
extern "C" int          __stdcall gseek(void* h, long off, int whence);      // 0x0087d540
# pragma function(memset)
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);
extern "C" unsigned int __cdecl strlen(const char* s);
extern "C" int   __cdecl setjmp3(void* jb, int arg);                         // 0x011e0cac
extern "C" __declspec(dllimport,noreturn) void __cdecl longjmp(void* jb, int val);

// ------------------------------------------------------------------ libjpeg
namespace lib_jpeg {
    void* jpeg_std_error(void* errmgr);                        // 0x0085f190
    void  jpeg_destroy(void* cinfo);                           // 0x00850370
    void  jpeg_stdio_src(void* cinfo, void* io);               // 0x008580c0
    void  jpeg_stdio_dest(void* cinfo, void* io);              // 0x00857fb0
    void  jpeg_create_compress(void* cinfo);                   // 0x008502a0
    void  jpeg_set_defaults(void* cinfo);                      // 0x00855a30
    void  jpeg_set_quality(void* cinfo, int q, int force);     // 0x008550e0
    void  jpeg_start_compress(void* cinfo, int write_all);     // 0x00850570
    void  jpeg_write_marker(void* cinfo, int marker, const void* data, unsigned len); // 0x00850510
    int   jpeg_write_scanlines(void* cinfo, void** rows, int count);   // 0x008505f0
    void  jpeg_finish_compress(void* cinfo);                   // 0x008503f0
    void  jpeg_create_decompress(void* cinfo);                 // 0x00857730
    void  jpeg_save_markers(void* cinfo, int marker, unsigned len);    // 0x00857820
    int   jpeg_read_header(void* cinfo, int require_image);    // 0x00857bf0
    void  jpeg_start_decompress(void* cinfo);                  // 0x00857e10
    int   jpeg_read_scanlines(void* cinfo, void** rows, int count);    // 0x00857d70
    void  jpeg_finish_decompress(void* cinfo);                 // 0x00857b20
}
extern "C" void FUN_00857730(void* cinfo, int a, int size);      // create_decompress
extern "C" void FUN_00857820(void* cinfo, int marker, void* reader);

extern "C" void FUN_008668f0(void* p, int n);                   // jzero_far

// slice-26 helpers referenced from here
extern "C" int  FUN_00863c50(void* cinfo);
extern "C" int  FUN_00863d50(void* cinfo);
extern "C" void FUN_00863e40(void* cinfo);
extern "C" void FUN_00863b70(u8* dst, u8* src, int width, int pixfmt, int flag);

// slice-27 helpers
extern "C" unsigned int __stdcall FUN_00864910(void* p);
extern "C" int  FUN_00864930(int* param_1, int* param_2);
extern "C" u8* FUN_008644f0(u8* src, u8* dst, int count, int mode, int fmt);

// ================================================================ 0x00864330
// JPG_read: decode a JPEG stream into dst, one output row per line.
// @ 0x00864330
int __stdcall FUN_00864330(int handle, int desc, u8* dst, int stride)
{
    u8    cinfo[0x5d8];
    u8    errmgr[0x40];
    u8    jmpbuf[0x40];
    void* row;
    int   pixfmt = 0;
    int   flag;
    int   w, h, rows, y;
    int   ok = 1;

    *(void**)cinfo = lib_jpeg::jpeg_std_error(errmgr);
    *(void**)errmgr = (void*)&FUN_00863e40;

    if (setjmp3(jmpbuf, 0) != 0) {
        lib_jpeg::jpeg_destroy(cinfo);
        return 0;
    }
    FUN_00857730(cinfo, 0x3d, 0x5d8);
    FUN_00857820(cinfo, 0xed, (void*)&FUN_00863c50);
    FUN_00857820(cinfo, 0xfe, (void*)&FUN_00863d50);
    gseek(*(void**)((char*)handle + 0x10), 0, 0);
    lib_jpeg::jpeg_stdio_src(cinfo, *(void**)((char*)handle + 0x10));
    *(int*)0x01650394 = 0;
    lib_jpeg::jpeg_read_header(cinfo, 1);
    flag = *(int*)0x01650394;
    if (*(int*)(cinfo + 0x24) == 3) pixfmt = 2;
    else if (*(int*)(cinfo + 0x24) == 5) pixfmt = 4;
    lib_jpeg::jpeg_start_decompress(cinfo);
    w = *(int*)(cinfo + 0x70);
    h = *(int*)(cinfo + 0x7c);
    rows = *(int*)(cinfo + 0x74);
    row = (*(void*(**)(void*, int, int, int))(*(int*)(cinfo + 4) + 8))(cinfo, 1, w * h, 1);
    for (y = 0; y < rows; y++) {
        lib_jpeg::jpeg_read_scanlines(cinfo, &row, 1);
        if (y < *(int*)(desc + 0x14))
            FUN_00863b70(dst, *(u8**)row, w, pixfmt, flag);
        dst += stride;
    }
    lib_jpeg::jpeg_finish_decompress(cinfo);
    lib_jpeg::jpeg_destroy(cinfo);
    return ok;
    (void)h;
}

// ================================================================ 0x008644f0
// Convert one scanline from the GIMEX pixel layout to the layout libjpeg expects
// (or vice versa).  mode 0/1/2 selects the byte order; fmt+0x18 == 0x20 means 32-bit.
// @ 0x008644f0
u8* FUN_008644f0(u8* param_1, u8* param_2, int param_3, int param_4, int param_5)
{
    int iVar1;
    u8* pbVar2;
    u8* pbVar3;

    if (param_4 == 0) {
        if (*(int*)(param_5 + 0x18) == 0x20) {
            if (0 < param_3) {
                pbVar3 = param_2 + 3;
                pbVar2 = param_1 + 2;
                do {
                    pbVar3[-3] = pbVar2[1];
                    pbVar3[-2] = *pbVar2;
                    pbVar2[(int)param_2 - (int)param_1] = pbVar2[-1];
                    *pbVar3 = pbVar2[-2];
                    pbVar2 = pbVar2 + 4;
                    pbVar3 = pbVar3 + 4;
                    param_3 = param_3 + -1;
                } while (param_3 != 0);
                return param_1;
            }
        }
        else if (0 < param_3) {
            param_2 = param_2 + 2;
            do {
                param_2[-2] = *(u8*)(param_5 + 0x2b + (u32)*param_1 * 4);
                param_2[-1] = *(u8*)(param_5 + 0x2a + (u32)*param_1 * 4);
                *param_2 = *(u8*)(param_5 + 0x29 + (u32)*param_1 * 4);
                param_2[1] = *(u8*)(param_5 + 0x28 + (u32)*param_1 * 4);
                param_2 = param_2 + 4;
                param_1 = param_1 + 1;
                param_3 = param_3 + -1;
            } while (param_3 != 0);
        }
    }
    else if (param_4 == 1) {
        if (*(int*)(param_5 + 0x18) == 0x20) {
            if (0 < param_3) {
                param_1 = param_1 + 1;
                do {
                    *param_2 = *param_1;
                    param_2 = param_2 + 1;
                    param_1 = param_1 + 4;
                    param_3 = param_3 + -1;
                } while (param_3 != 0);
                return param_1;
            }
        }
        else {
            iVar1 = 0;
            if (0 < param_3) {
                do {
                    param_2[iVar1] = *(u8*)(param_5 + 0x29 + (u32)param_1[iVar1] * 4);
                    iVar1 = iVar1 + 1;
                } while (iVar1 < param_3);
                return param_1;
            }
        }
    }
    else if (param_4 == 2) {
        if (*(int*)(param_5 + 0x18) == 0x20) {
            if (0 < param_3) {
                param_2 = param_2 + 2;
                param_1 = param_1 + 1;
                do {
                    param_2[-2] = param_1[1];
                    param_2[-1] = *param_1;
                    *param_2 = param_1[-1];
                    param_2 = param_2 + 3;
                    param_1 = param_1 + 4;
                    param_3 = param_3 + -1;
                } while (param_3 != 0);
                return param_1;
            }
        }
        else if (0 < param_3) {
            param_2 = param_2 + 2;
            do {
                param_2[-2] = *(u8*)(param_5 + 0x2a + (u32)*param_1 * 4);
                param_2[-1] = *(u8*)(param_5 + 0x29 + (u32)*param_1 * 4);
                *param_2   = *(u8*)(param_5 + 0x28 + (u32)*param_1 * 4);
                param_2 = param_2 + 3;
                param_1 = param_1 + 1;
                param_3 = param_3 + -1;
            } while (param_3 != 0);
            return param_1;
        }
    }
    return param_1;
}

// ================================================================ 0x00864680
// JPG_write: encode src (GIMEX layout) into a JPEG stream on handle->io.
// The original places its nested error_exit thunk immediately before the body; this is
// the body (encoder driver).
// @ 0x00864680
int __stdcall FUN_00864680(int handle, int* desc, u8* src, int stride)
{
    u8    cinfo[0x170];
    u8    errmgr[0xc4];
    u8    jmpbuf[0x40];
    int   quality;
    int   width, height;
    int   in_color, jpeg_color;
    int   ok = 0;
    u8*   buf = NULL;
    int   y;

    if (desc[0x10b] != 0) quality = desc[0x10c];
    else                  quality = 100;
    width  = desc[4];
    height = desc[5];
    in_color = 3; jpeg_color = 2;
    if (desc[0x10a] & 1) {
        in_color = 4; jpeg_color = 0;
    }
    else if (desc[6] == 8) {
        int n = desc[9];
        int i;
        u8* p = (u8*)desc + 0x2a;
        for (i = 0; i < n; i++) {
            if (p[0] != p[-1] || p[0] != p[-2]) break;
            p += 4;
        }
        if (i >= n) { in_color = 1; jpeg_color = 1; }
    }

    *(void**)errmgr = (void*)&FUN_00864680;
    *(void**)cinfo  = lib_jpeg::jpeg_std_error(errmgr);
    if (setjmp3(jmpbuf, 0) == 0) {
        lib_jpeg::jpeg_create_compress(cinfo);
        lib_jpeg::jpeg_stdio_dest(cinfo, *(void**)((char*)handle + 0x10));
        *(int*)(cinfo + 0x18) = width;
        *(int*)(cinfo + 0x1c) = height;
        *(int*)(cinfo + 0x20) = in_color;
        *(int*)(cinfo + 0x24) = jpeg_color;
        lib_jpeg::jpeg_set_defaults(cinfo);
        lib_jpeg::jpeg_set_quality(cinfo, quality, 1);
        {
            float q = *(float*)((char*)desc + 0x2a5c);
            if (q != 0.0f) {
                *(u8*)(cinfo + 0xcc) = 1;
                *(u16*)(cinfo + 0xce) = (u16)(int)q;
                *(u16*)(cinfo + 0xd0) = (u16)(int)q;
            }
            else {
                *(u8*)(cinfo + 0xcc) = 0;
                *(u16*)(cinfo + 0xce) = 1;
                *(u16*)(cinfo + 0xd0) = 1;
            }
        }
        lib_jpeg::jpeg_start_compress(cinfo, 1);
        if (desc[0x10a] & 1)
            lib_jpeg::jpeg_write_marker(cinfo, 0xed, "GIMEXARGB", 9);
        {
            char* c = (char*)desc + 0x65c;
            unsigned n = (unsigned)strlen(c);
            if (n != 0)
                lib_jpeg::jpeg_write_marker(cinfo, 0xfe, c, n);
        }
        buf = (u8*)galloc((u32)(in_color * width));
        if (buf != NULL) {
            for (y = 0; y < height; y++) {
                u8* rowp = buf;
                FUN_008644f0(src, rowp, width, jpeg_color, (int)desc);
                lib_jpeg::jpeg_write_scanlines(cinfo, (void**)&rowp, 1);
                src += stride;
            }
            lib_jpeg::jpeg_finish_compress(cinfo);
            ok = 1;
        }
    }
    if (buf != NULL) gfree(buf);
    lib_jpeg::jpeg_destroy(cinfo);
    return ok;
}

// ================================================================ 0x00864910
// free a buffer, returning 0 for a null pointer.
// @ 0x00864910
extern "C" unsigned int __stdcall FUN_00864910(void* p)
{
    unsigned int r = 0;
    if (p != NULL)
        r = gfree_i(p);
    return r;
}

// ================================================================ 0x00864930
// libjpeg jquant1.c select_ncolors: divvy the desired colours among the
// components.  Returns the total number of colours; Ncolors[] is filled in.
// @ 0x00864930
static const int RGB_order[3] = { RGB_GREEN, RGB_RED, RGB_BLUE };

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

// libjpeg jquant1.c helper: value that output level j represents.
static int output_value(struct jpeg_decompress_struct* cinfo, int ci, int j, int maxj)
{
    return (int)(((int)j * MAXJSAMPLE + maxj / 2) / maxj);
}

// ================================================================ 0x00864a20
// libjpeg jquant1.c create_colormap: allocate and fill the output colormap.
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

// ================================================================ 0x00864b90
// libjpeg jquant1.c create_colorindex: build the (optionally padded) colorindex.
// @ 0x00864b90
static int largest_input_value(struct jpeg_decompress_struct* cinfo, int ci, int j, int maxj)
{
    return (int)(((int)(2 * j + 1) * MAXJSAMPLE + maxj) / (2 * maxj));
}

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

// ================================================================ 0x00864ce0
// libjpeg jdmerge::make_odither_array - build one ordered-dither table.
// cinfo arrives in EAX and the quality scale in ECX (whole-program convention).
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

// ================================================================ 0x00864d60
// libjpeg jdmerge: allocate the ordered-dither arrays per component (reuse identical ones).
// The original takes cinfo in EBX (whole-program convention).
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

// ================================================================ 0x00864db0
// libjpeg jquant1.c color_quantize: general (N-component) colormap mapping.
// @ 0x00864db0
extern "C" void FUN_00864db0(struct jpeg_decompress_struct* cinfo, u8** input_buf,
                             u8** output_buf, int num_rows)
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

// ================================================================ 0x00864e60
// libjpeg jquant1.c color_quantize3: fast path for out_color_components == 3.
// @ 0x00864e60
extern "C" void FUN_00864e60(struct jpeg_decompress_struct* cinfo, u8** input_buf,
                             u8** output_buf, int num_rows)
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
