// src/game/UTFSpore_Win32/jpgread.cpp -- migrated from slice(s) s00864330, s00863260 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/jpgread.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#ifndef NULL
#define NULL 0
#endif

// unnamed retail callees and globals (address in the comment)
extern "C" void*        __stdcall galloc(unsigned int size);                       // 0x0087d4a0
extern "C" unsigned int __stdcall gread(void* h, void* buf, unsigned int n);       // 0x0087d4e0
extern "C" int          __stdcall gseek(void* h, long off, int whence);            // 0x0087d540
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);
extern "C" char* __cdecl strcpy(char* dst, const char* src);
extern "C" char* __cdecl strncpy(char* dst, const char* src, unsigned int n);
extern "C" int   __cdecl setjmp3(void* jb, int arg);                               // 0x011e0cac
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
#pragma function(memset)

// ---- items of slice s00863260 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
extern "C" void*        __stdcall galloc(unsigned int size);                       // 0x0087d4a0
extern "C" unsigned int __stdcall gread(void* h, void* buf, unsigned int n);       // 0x0087d4e0
extern "C" int          __stdcall gseek(void* h, long off, int whence);            // 0x0087d540
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);
extern "C" char* __cdecl strcpy(char* dst, const char* src);
extern "C" char* __cdecl strncpy(char* dst, const char* src, unsigned int n);
extern "C" int   __cdecl setjmp3(void* jb, int arg);                               // 0x011e0cac
namespace lib_jpeg {
    void* jpeg_std_error(void* errmgr);
}
namespace lib_jpeg {
    void  jpeg_destroy(void* cinfo);
}
namespace lib_jpeg {
    void  jpeg_stdio_src(void* cinfo, void* io);
}
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
// ---- items of slice s00863260 end

// ---- items of slice s00864330 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned int  __stdcall gfree_i(void* p);                         // 0x0087d4c0 (same fn)
extern "C" unsigned int __stdcall FUN_00864910(void* p);
# pragma function(memset)
namespace lib_jpeg {
    int   jpeg_read_header(void* cinfo, int require_image);    // 0x00857bf0
}
namespace lib_jpeg {
    void  jpeg_start_decompress(void* cinfo);                  // 0x00857e10
}
namespace lib_jpeg {
    int   jpeg_read_scanlines(void* cinfo, void** rows, int count);    // 0x00857d70
}
namespace lib_jpeg {
    void  jpeg_finish_decompress(void* cinfo);                 // 0x00857b20
}
extern "C" void FUN_00863b70(u8* dst, u8* src, int width, int pixfmt, int flag);
// ---- items of slice s00864330 end

// @ 0x00863e60
u8* JPG_about(void)
{
    u8* d = (u8*)galloc(0x100);
    if (d != NULL) {
        memset(d, 0, 0x100);
        *(u32*)(d + 0x00) = 0x4a504547;                 // "JPEG"
        *(u32*)(d + 0x04) = 0x100;
        *(u32*)(d + 0x08) = 0x159;
        *(u32*)(d + 0x14) = 0;
        *(u32*)(d + 0x18) = 0x50;
        *(u32*)(d + 0x1c) = 0x4a504547;
        *(u32*)(d + 0x0c) = (*(u32*)(d + 0x0c) & 0xffffb3d7) | 0xb3d7;
        strcpy((char*)(d + 0x3c), ".jpg");
        strcpy((char*)(d + 0x44), ".jpeg");
        strcpy((char*)(d + 0x4c), ".jfif");
        strcpy((char*)(d + 0x7c), "FrANK G. Barchard");
        strcpy((char*)(d + 0x9c), "1.12");
        *(u32*)(d + 0xa4) = 0x47504a;
        strcpy((char*)(d + 0xac), "JPeg");
        strcpy((char*)(d + 0xbc), "JPeg");
    }
    return d;
}

// @ 0x00863f90
int __stdcall JPG_is(void* io)
{
    u8  buf[4];
    u32 v;
    int r = 0;
    gseek(io, 0, 0);
    if (gread(io, buf, 4) != 0) {
        v = ((u32)buf[0] << 24) | ((u32)buf[1] << 16) | ((u32)buf[2] << 8) | buf[3];
        if (v == 0xffd8ffe0 || v == 0xffd8ffe1 || v == 0xffd8ffed)
            r = 0x63;
    }
    return r;
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

// @ 0x00864910
extern "C" unsigned int __stdcall FUN_00864910(void* p)
{
    unsigned int r = 0;
    if (p != NULL)
        r = gfree_i(p);
    return r;
}
