// src/game/UTFSpore_Win32/jpgread.cpp
// The game's JPEG (Gimex) importer: format descriptor, signature test, and the
// open/info/read entry points over the bundled libjpeg.

#include "game/types.h"
#ifndef NULL
#define NULL 0
#endif

// Allocation/stream helpers shared with the Gimex glue (address in the comment).
extern "C" void*        __stdcall galloc(unsigned int size);                       // 0x0087d4a0
extern "C" unsigned int __stdcall gread(void* h, void* buf, unsigned int n);       // 0x0087d4e0
extern "C" int          __stdcall gseek(void* h, long off, int whence);            // 0x0087d540
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);
extern "C" char* __cdecl strcpy(char* dst, const char* src);
extern "C" char* __cdecl strncpy(char* dst, const char* src, unsigned int n);
extern "C" int   __cdecl setjmp3(void* jb, int arg);                               // 0x011e0cac
#pragma function(memset)

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// Glue to the bundled libjpeg, called through its public entry points.
namespace lib_jpeg {
    void* jpeg_std_error(void* errmgr);
    void  jpeg_destroy(void* cinfo);
    void  jpeg_stdio_src(void* cinfo, void* io);
    int   jpeg_read_header(void* cinfo, int require_image);              // 0x00857bf0
    void  jpeg_start_decompress(void* cinfo);                           // 0x00857e10
    int   jpeg_read_scanlines(void* cinfo, void** rows, int count);     // 0x00857d70
    void  jpeg_finish_decompress(void* cinfo);                         // 0x00857b20
}

// Remaining libjpeg internals used by the decoder setup, plus the scanline
// helper and the error handler.  gfree_i frees a Gimex allocation (0x0087d4c0).
extern "C" void FUN_00857730(void* cinfo, int a, int size);
extern "C" void FUN_00857820(void* cinfo, int marker, void* reader);
extern "C" void FUN_00857bf0(void* cinfo, int a);
extern "C" void FUN_00857e10(void* cinfo);
extern "C" void FUN_00857d70(void* cinfo, void* buf, int n);
extern "C" void FUN_00857b20(void* cinfo);
extern "C" int FUN_00863c50(void* cinfo);
extern "C" int FUN_00863d50(void* cinfo);
extern "C" void FUN_00863e40(void* cinfo);
extern "C" int __stdcall FUN_00864000(void** out, void* io, int a3, int a4);
extern "C" unsigned int __stdcall gfree_i(void* p);                    // 0x0087d4c0 (same fn)
extern "C" unsigned int __stdcall FUN_00864910(void* p);
extern "C" void FUN_00863b70(u8* dst, u8* src, int width, int pixfmt, int flag);

// Layout of the 0x100-byte format descriptor Gimex asks each importer for.
// The strings (extension list, author, version) sit at fixed offsets past it.
enum JpgAboutField
{
    kAboutSize        = 0x100,     // descriptor size in bytes
    kAboutTag         = 0x00,      // "JPEG"
    kAboutTagValue    = 0x4a504547,
    kAboutSizeField   = 0x04,      // descriptor size, repeated in the header
    kAboutVersion     = 0x08,
    kAboutVersionVal  = 0x159,
    kAboutFlags       = 0x0c,
    kAboutFlagsMask   = 0xffffb3d7,
    kAboutFlagsSet    = 0xb3d7,
    kAboutKind        = 0x14,
    kAboutMaxExt      = 0x18,      // maximum extension length
    kAboutMaxExtVal   = 0x50,
    kAboutFamily      = 0x1c,      // family tag, same value as kAboutTag
    kAboutExtensions  = 0x3c,      // ".jpg", ".jpeg", ".jfif" (10 bytes each)
    kAboutExtension2  = 0x44,
    kAboutExtension3  = 0x4c,
    kAboutAuthor      = 0x7c,
    kAboutVersionStr  = 0x9c,
    kAboutShortName   = 0xa4,      // "JP"...
    kAboutShortNameVal = 0x47504a,
    kAboutDisplayName  = 0xac,
    kAboutSaveName     = 0xbc,
};

// ---- items of slice s00864330 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned char __stdcall gfree(void* p);                           // 0x0087d4c0
extern "C" unsigned int __cdecl strlen(const char* s);
# pragma function(memset)
namespace lib_jpeg {
    void  jpeg_stdio_dest(void* cinfo, void* io);              // 0x00857fb0
}
namespace lib_jpeg {
    void  jpeg_create_compress(void* cinfo);                   // 0x008502a0
}
namespace lib_jpeg {
    void  jpeg_set_defaults(void* cinfo);                      // 0x00855a30
}
namespace lib_jpeg {
    void  jpeg_set_quality(void* cinfo, int q, int force);     // 0x008550e0
}
namespace lib_jpeg {
    void  jpeg_start_compress(void* cinfo, int write_all);     // 0x00850570
}
namespace lib_jpeg {
    void  jpeg_write_marker(void* cinfo, int marker, const void* data, unsigned len); // 0x00850510
}
namespace lib_jpeg {
    int   jpeg_write_scanlines(void* cinfo, void** rows, int count);   // 0x008505f0
}
namespace lib_jpeg {
    void  jpeg_finish_compress(void* cinfo);                   // 0x008503f0
}
extern "C" u8* FUN_008644f0(u8* src, u8* dst, int count, int mode, int fmt);
// ---- items of slice s00864330 end

// @ 0x00863e60
u8* JPG_about(void)
{
    u8* d = (u8*)galloc(kAboutSize);
    if (d != NULL) {
        memset(d, 0, kAboutSize);
        *(u32*)(d + kAboutTag) = kAboutTagValue;
        *(u32*)(d + kAboutSizeField) = kAboutSize;
        *(u32*)(d + kAboutVersion) = kAboutVersionVal;
        *(u32*)(d + kAboutKind) = 0;
        *(u32*)(d + kAboutMaxExt) = kAboutMaxExtVal;
        *(u32*)(d + kAboutFamily) = kAboutTagValue;
        *(u32*)(d + kAboutFlags) =
            (*(u32*)(d + kAboutFlags) & kAboutFlagsMask) | kAboutFlagsSet;
        strcpy((char*)(d + kAboutExtensions), ".jpg");
        strcpy((char*)(d + kAboutExtension2), ".jpeg");
        strcpy((char*)(d + kAboutExtension3), ".jfif");
        strcpy((char*)(d + kAboutAuthor), "FrANK G. Barchard");
        strcpy((char*)(d + kAboutVersionStr), "1.12");
        *(u32*)(d + kAboutShortName) = kAboutShortNameVal;
        strcpy((char*)(d + kAboutDisplayName), "JPeg");
        strcpy((char*)(d + kAboutSaveName), "JPeg");
    }
    return d;
}

// Signatures JPG_is accepts: SOI+APP0 (JFIF), SOI+APP1 (EXIF), SOI+APP13 (IPTC).
enum JpegSignature
{
    kJfif = 0xffd8ffe0,
    kExif = 0xffd8ffe1,
    kIptc = 0xffd8ffed,
    kJpegType = 0x63,   // importer type code reported back to Gimex
};

// @ 0x00863f90
int __stdcall JPG_is(void* io)
{
    u8  buf[4];
    u32 sig;
    int type = 0;
    gseek(io, 0, 0);
    if (gread(io, buf, 4) != 0) {
        sig = ((u32)buf[0] << 24) | ((u32)buf[1] << 16) | ((u32)buf[2] << 8) | buf[3];
        if (sig == kJfif || sig == kExif || sig == kIptc)
            type = kJpegType;
    }
    return type;
}

// @ 0x00864000
int __stdcall FUN_00864000(void** out, void* io, int a3, int a4)
{
    int  ok = 0;
    int* h = (int*)galloc(0x18);
    if (h != 0) {
        h[3] = 0;
        h[5] = 0;
        h[2] = 1;
        h[0] = 0x4a504547;
        h[1] = 0x18;
        h[4] = (int)io;
        *out = h;
        ok = 1;
    }
    return ok;
}

// @ 0x00864050
void* __stdcall FUN_00864050(void* handle, int a2)
{
    u8   dec[0x5d8];
    u8   jmpbuf[64];
    u8   errmgr[0x40];
    u8   comment[1024];
    void* local_10 = 0;
    int  local_1c = 1;
    int  i;
    int  local_18, local_14, local_20, local_c, local_8;
    unsigned local_c8 = 0;
    int  local_588, local_57c;
    unsigned local_584, local_56c;
    char local_4dc;
    u16  local_4da;
    void* local_5f4;
    u32* d;
    int  rc;

    *(void**)(dec + 8) = lib_jpeg::jpeg_std_error(errmgr);
    *(void**)(dec + 0) = (void*)&FUN_00863e40;
    local_5f4 = *(void**)(dec + 4);

    rc = setjmp3(jmpbuf, 0);
    if (rc != 0) {
        lib_jpeg::jpeg_destroy(dec);
        return NULL;
    }
    FUN_00857730(dec + 4, 0x3d, 0x5d8);
    FUN_00857820(dec + 4, 0xed, (void*)&FUN_00863c50);
    FUN_00857820(dec + 4, 0xfe, (void*)&FUN_00863d50);
    gseek(*(void**)((u8*)handle + 0x10), 0, 0);
    lib_jpeg::jpeg_stdio_src(dec + 4, *(void**)((u8*)handle + 0x10));
    *(int*)0x01650394 = 0;
    FUN_00857bf0(dec + 4, 1);
    local_18 = *(int*)0x01650394;
    FUN_00857e10(dec + 4);
    local_14 = *(int*)(dec + 0x70);
    local_20 = *(unsigned*)(dec + 0x74);
    local_588 = *(int*)(dec + 0x70);
    local_584 = *(unsigned*)(dec + 0x74);
    local_57c = *(int*)(dec + 0x7c);
    local_56c = *(unsigned*)(dec + 0x8c);
    local_4dc = *(char*)(dec + 0x11c);
    local_4da = *(u16*)(dec + 0x11e);
    local_c = 0;
    if (local_4dc != 0)
        local_c = local_4da;
    {
        int  eax = local_57c * local_588;
        void* p;
        p = (*(void*(**)(void*, int, int, int))((char*)local_5f4 + 8))(dec + 4, 1, eax, 1);
        while (local_56c < local_584)
            FUN_00857d70(dec + 4, p, 1);
    }
    FUN_00857b20(dec + 4);
    lib_jpeg::jpeg_destroy(dec + 4);
    if (local_1c != 0) {
        local_8 = 0x18;
        if (local_57c == 1)
            local_8 = 8;
        d = (u32*)galloc(0x2a70);
        local_10 = NULL;
        if (d != NULL) {
            local_10 = d;
            memset(d, 0, 0x2a70);
            d[0] = 0x4a504547;
            d[1] = 0x2a70;
            d[2] = 0x159;
            d[3] = 0;
            d[4] = local_14;
            d[5] = local_20;
            d[0x10a] = (local_18 != 0);
            d[0x10b] = 1;
            d[0x10c] = 0x46;
            d[0x10e] = 0;
            d[0x10f] = 8;
            d[0x110] = 8;
            d[0x111] = 8;
            d[0x112] = 0;
            d[0x113] = 0;
            d[0x114] = 0;
            d[0x115] = 0;
            d[0x116] = 0;
            *(float*)((u8*)d + 0x2a5c) = (float)(int)local_c;
            *(u8*)((u8*)d + 0x45c) = 0;
            if (local_8 < 0xf) {
                d[6] = 8;
                d[7] = 8;
                d[9] = 0x100;
                {
                    u8* p = (u8*)d + 0x2a;
                    for (i = 0; i < 0x100; i++) {
                        p[1] = 0xff; p[0] = (u8)i; p[-1] = (u8)i; p[-2] = (u8)i; p += 4;
                    }
                }
            }
            else {
                d[6] = 0x20;
                d[7] = local_8;
                d[9] = 0;
            }
            strncpy((char*)d + 0x65c, (char*)comment, local_c8);
            return d;
        }
    }
    return local_10;
}

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

// @ 0x00864910
extern "C" unsigned int __stdcall FUN_00864910(void* p)
{
    unsigned int r = 0;
    if (p != NULL)
        r = gfree_i(p);
    return r;
}
