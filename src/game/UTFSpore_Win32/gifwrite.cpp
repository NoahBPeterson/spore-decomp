// src/game/UTFSpore_Win32/gifwrite.cpp -- migrated from slice(s) s0084cd70 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/gifwrite.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void*         __stdcall galloc(size_t n);              // 0x0087d4a0
extern "C" unsigned char __stdcall gfree(void* p);                 // 0x0087d4c0
extern "C" int           __stdcall gwrite(void* f, const void* buf, unsigned n); // 0x0087d510
extern "C" int           __stdcall gseek(void* f, long off, int whence);    // 0x0087d540
extern "C" int           __stdcall gtell(void* f);                 // 0x0087d570
extern "C" void*         __cdecl   memset(void* dst, int v, size_t n);
extern "C" void*         __cdecl   memcpy(void* dst, const void* src, size_t n);

// ---- items of slice s0084cd70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*         __stdcall galloc(size_t n);              // 0x0087d4a0
extern "C" unsigned char __stdcall gfree(void* p);                 // 0x0087d4c0
extern "C" int           __stdcall gwrite(void* f, const void* buf, unsigned n); // 0x0087d510
extern "C" int           __stdcall gseek(void* f, long off, int whence);    // 0x0087d540
extern "C" int           __stdcall gtell(void* f);                 // 0x0087d570
extern "C" void*         __cdecl   memset(void* dst, int v, size_t n);
extern "C" void*         __cdecl   memcpy(void* dst, const void* src, size_t n);
struct GifFileType {
    int  SWidth;                 // 0x00
    int  SHeight;                // 0x04
    int  SColorResolution;       // 0x08
    int  SBackGroundColor;       // 0x0c
    int  AspectByte;             // 0x10
    int  ImageLeft;              // 0x14
    int  ImageTop;               // 0x18
    int  ImageWidth;             // 0x1c
    int  ImageHeight;            // 0x20
    int  ImageInterlace;         // 0x24
    int  ImageColorRes;          // 0x28
    int  ImageTransparent;       // 0x2c
    int  ImageReserved30;        // 0x30
    int  ImageReserved34;        // 0x34
    int  Reserved38;             // 0x38
    void* ImageColorMap;         // 0x3c
    void* SavedImageColorMap;    // 0x40
    int  ImageCount;             // 0x44
    void* Private;               // 0x48
};
struct EGifPrivate {
    int  FileState;              // 0x00
    int  FileHandle;             // 0x04
    int  BitsPerPixel;           // 0x08
    int  ClearCode;              // 0x0c
    int  EOFCode;                // 0x10
    int  RunningCode;            // 0x14
    int  RunningBits;            // 0x18
    int  MaxCode1;               // 0x1c
    int  CrntCode;               // 0x20
    int  CrntShiftState;         // 0x24
    int  CrntShiftDWord;         // 0x28
    int  Reserved2c;             // 0x2c
    void* fd;                    // 0x30
    unsigned char Buf[256];      // 0x34
    void* HashTable;             // 0x134
    unsigned char Masks[9];      // 0x138
};
struct GIFWriteInfo {            // 0x18
    int  f00, f04, f08, f0c, f10;   // 0x00..0x13
    void* file;                     // 0x14
};
struct GIFWriteFile {           // 0x10
    int  pos;                   // 0x00
    int  f04;                   // 0x04
    int  f08;                   // 0x08
    void* egif;                 // 0x0c
};
int  __cdecl EGifCloseFile(void* g);                       // 0x0084ceb0
void* __cdecl EGifOpenFileHandle(void* f);                 // 0x0084d060
void* __cdecl _InitHashTable(void);                        // 0x0084cfd0
int  __cdecl EGifSetupCompress(void* g);                   // 0x0084d4c0
static int gif_bufout(EGifPrivate* p, int c)
{
    if (c == 0x100) {
        if (p->Buf[0] == 0) {
            if (gwrite(p->fd, p->Buf, 1) == 0)
                return 0;
        } else {
            if (gwrite(p->fd, p->Buf, p->Buf[0] + 1) == 0)
                return 0;
            p->Buf[0] = 0;
            if (gwrite(p->fd, p->Buf, 1) == 0)
                return 0;
        }
    } else {
        if (p->Buf[0] == 0xff) {
            if (gwrite(p->fd, p->Buf, 0x100) == 0)
                return 0;
            p->Buf[0] = 0;
        }
        p->Buf[0]++;
        p->Buf[p->Buf[0]] = (unsigned char)c;
    }
    return 1;
}
// ---- items of slice s0084cd70 end

// @ 0x0084cde0
int __cdecl GifPutNetscapeBlock(void* f)
{
    unsigned char buf[8];
    buf[0] = 0x21;
    buf[1] = 0xff;
    buf[2] = 0x0b;
    gwrite(f, buf, 3);
    gwrite(f, "NETSCAPE2.0", 11);
    buf[0] = 3;
    buf[1] = 1;
    *(unsigned short*)(buf + 2) = 0;
    buf[4] = 0;
    return gwrite(f, buf, 5) != 0;
}

// @ 0x0084ce40
int __cdecl EGifPutExtension(GifFileType* g, unsigned char code, int len, void* data)
{
    EGifPrivate* p = (EGifPrivate*)g->Private;
    if ((p->FileState & 1) == 0)
        return 0;
    unsigned char hdr[4];
    hdr[0] = 0x21;
    hdr[1] = code;
    hdr[2] = (unsigned char)len;
    gwrite(p->fd, hdr, 3);
    gwrite(p->fd, data, len);
    hdr[0] = 0;
    gwrite(p->fd, hdr, 1);
    return 1;
}

// @ 0x0084ceb0
int __cdecl EGifCloseFile(void* g_)
{
    GifFileType* g = (GifFileType*)g_;
    if (!g)
        return 0;
    EGifPrivate* p = (EGifPrivate*)g->Private;
    if ((p->FileState & 1) == 0)
        return 0;
    unsigned char term = 0x3b;
    gwrite(p->fd, &term, 1);
    if (g->SavedImageColorMap)
        gfree(g->SavedImageColorMap);
    if (g->ImageColorMap)
        gfree(g->ImageColorMap);
    if (p->HashTable)
        gfree(p->HashTable);
    gfree(p);
    gfree(g);
    return 1;
}

// @ 0x0084cf20
int EGifUpdateLSD(void* fd, int pos, int height, int newPos)
{
    unsigned short buf;
    gseek(fd, pos, pos >> 31);
    buf = (unsigned short)height;
    if (gwrite(fd, &buf, 2) == 0)
        return 0;
    if (gwrite(fd, &buf, 2) == 0)
        return 0;
    gseek(fd, newPos, newPos >> 31);
    return 1;
}

// @ 0x0084cf90
int __stdcall GIF_wclose(GIFWriteInfo* info)
{
    int r = 0;
    if (info) {
        if (info->file) {
            EGifCloseFile(((GIFWriteFile*)info->file)->egif);
            gfree(info->file);
        }
        r = gfree(info);
    }
    return r;
}

// @ 0x0084cfd0
void* __cdecl _InitHashTable(void)
{
    void* p = galloc(0x8000);
    if (!p)
        return 0;
    memset(p, 0xff, 0x8000);
    return p;
}

// @ 0x0084d000
namespace  {
void _InsertHashTable(unsigned int * table, unsigned int key, int value)
{
    unsigned int i = (key >> 12 ^ key) & 0x1fff;
    while ((table[i] & 0xfffff000) != 0xfffff000)
        i = (i + 1) & 0x1fff;
    table[i] = (value & 0xfff) | (key << 12);
}
}  // namespace 

// @ 0x0084d060
void* __cdecl EGifOpenFileHandle(void* f)
{
    char* g = (char*)galloc(0x4c);
    if (!g)
        return 0;
    *(int*)(g + 0x28) = 0;
    *(int*)(g + 0x24) = 0;
    *(int*)(g + 0x20) = 0;
    *(int*)(g + 0x1c) = 0;
    *(int*)(g + 0x18) = 0;
    *(int*)(g + 0x14) = 0;
    *(int*)(g + 0x10) = 0;
    *(int*)(g + 0x0c) = 0;
    *(int*)(g + 0x08) = 0;
    *(int*)(g + 0x04) = 0;
    *(int*)(g + 0x00) = 0;
    *(int*)(g + 0x40) = 0;
    *(int*)(g + 0x3c) = 0;
    if (gwrite(f, "GIF87a", 6) == 0) {
        gfree(g);
        return 0;
    }
    char* p = (char*)galloc(0x144);
    if (!p)
        return 0;
    *(void**)(g + 0x48) = p;
    *(int*)(p + 0x04) = 0;
    *(void**)(p + 0x30) = f;
    *(int*)(p + 0x00) = 1;
    *(unsigned char*)(p + 0x138) = 0;
    *(unsigned char*)(p + 0x139) = 1;
    *(unsigned char*)(p + 0x13a) = 3;
    *(unsigned char*)(p + 0x13b) = 7;
    *(unsigned char*)(p + 0x13c) = 0xf;
    *(unsigned char*)(p + 0x13d) = 0x1f;
    *(unsigned char*)(p + 0x13e) = 0x3f;
    *(unsigned char*)(p + 0x13f) = 0x7f;
    *(unsigned char*)(p + 0x140) = 0xff;
    *(void**)(p + 0x134) = _InitHashTable();
    return *(void**)(p + 0x134) ? g : 0;
}

// @ 0x0084d140
int __cdecl EGifPutScreenDesc(GifFileType* g, int width, int height, int colorRes, int aspect, int bpp, void* cmap)
{
    EGifPrivate* p = (EGifPrivate*)g->Private;
    if ((p->FileState & 2) != 0 || (p->FileState & 1) == 0)
        return 0;
    g->SHeight = height;
    g->SWidth = width;
    g->SColorResolution = colorRes;
    g->SBackGroundColor = bpp;
    g->AspectByte = aspect;
    if (cmap) {
        int n = (1 << (bpp & 0x1f)) * 3;
        void* dst = galloc(n);
        g->ImageColorMap = dst;
        memcpy(dst, cmap, n);
    }
    unsigned char buf[4];
    buf[0] = (unsigned char)width;
    buf[1] = (unsigned char)(width >> 8);
    gwrite(p->fd, buf, 2);
    buf[0] = (unsigned char)height;
    buf[1] = (unsigned char)(height >> 8);
    gwrite(p->fd, buf, 2);
    buf[0] = (unsigned char)(((colorRes - 1) << 4) | (cmap ? 0x80 : 0) | (bpp - 1));
    buf[1] = (unsigned char)aspect;
    buf[2] = 0;
    gwrite(p->fd, buf, 3);
    if (cmap) {
        int n = 1 << (bpp & 0x1f);
        unsigned char* src = (unsigned char*)cmap;
        for (int i = 0; i < n; i++) {
            unsigned char c[3];
            c[0] = src[0];
            c[1] = src[1];
            c[2] = src[2];
            if (gwrite(p->fd, c, 3) == 0)
                return 0;
            src += 3;
        }
    }
    if (GifPutNetscapeBlock(p->fd) == 0)
        return 0;
    p->FileState |= 2;
    return 1;
}

// @ 0x0084d2a0
int EGifCompressOutput(EGifPrivate* p, int code)
{
    int retval = 1;
    if (code != 0x1000) {
        p->CrntShiftDWord |= code << (p->CrntShiftState & 0x1f);
        p->CrntShiftState += p->RunningBits;
        while (p->CrntShiftState > 7) {
            if (gif_bufout(p, p->CrntShiftDWord & 0xff) == 0)
                retval = 0;
            p->CrntShiftDWord >>= 8;
            p->CrntShiftState -= 8;
        }
    } else {
        while (p->CrntShiftState > 0) {
            if (gif_bufout(p, p->CrntShiftDWord & 0xff) == 0)
                retval = 0;
            p->CrntShiftDWord >>= 8;
            p->CrntShiftState -= 8;
        }
        p->CrntShiftState = 0;
        if (gif_bufout(p, 0x100) == 0)
            retval = 0;
    }
    if (p->RunningCode >= p->MaxCode1 && code <= 0xfff) {
        p->RunningBits++;
        p->MaxCode1 = 1 << p->RunningBits;
    }
    return retval;
}

// @ 0x0084d430
int __stdcall GIF_wopen(void** ppInfo, void* f, int p3, int p4)
{
    (void)p3;
    (void)p4;
    GIFWriteInfo* info = (GIFWriteInfo*)galloc(0x18);
    int ok = 0;
    if (info) {
        info->f00 = 0;
        info->f04 = 0;
        info->f08 = 0;
        info->file = 0;
        info->f10 = (int)f;
        info->f0c = -1;
        *ppInfo = info;
        info->file = (void*)galloc(0x10);
        ((GIFWriteFile*)info->file)->egif = EGifOpenFileHandle((void*)info->f10);
        *(int*)((char*)((GIFWriteFile*)info->file)->egif + 0x38) = gtell((void*)info->f10);
        ((GIFWriteFile*)info->file)->pos = gtell((void*)info->f10);
        ((GIFWriteFile*)info->file)->f04 = 0;
        ((GIFWriteFile*)info->file)->f08 = 0;
        ok = 1;
    }
    return ok;
}

// @ 0x0084d4c0
bool EGifSetupCompress(GifFileType* g)
{
    EGifPrivate* p = (EGifPrivate*)g->Private;
    int bpp;
    if (g->SavedImageColorMap == 0) {
        if (g->ImageColorMap == 0)
            return false;
        bpp = g->SBackGroundColor;
    } else {
        bpp = g->ImageColorRes;
    }
    if (bpp < 2)
        bpp = 2;
    unsigned char c = (unsigned char)bpp;
    gwrite(p->fd, &c, 1);
    p->ClearCode = 1 << bpp;
    p->EOFCode = p->ClearCode + 1;
    p->RunningCode = p->ClearCode + 2;
    memset(p->HashTable, 0xff, 0x8000);
    p->Buf[0] = 0;
    p->BitsPerPixel = bpp;
    p->RunningBits = bpp + 1;
    p->MaxCode1 = 1 << (bpp + 1);
    p->CrntCode = 0x1001;
    p->CrntShiftState = 0;
    p->CrntShiftDWord = 0;
    return EGifCompressOutput(p, p->ClearCode) != 0;
}

// @ 0x0084d570
int EGifCompressLine(GifFileType* g, unsigned char* line, int len)
{
    EGifPrivate* p = (EGifPrivate*)g->Private;
    unsigned int* table = (unsigned int*)p->HashTable;
    unsigned int crnt = p->CrntCode;
    int i = 0;
    if (crnt == 0x1001) {
        crnt = line[0];
        i = 1;
    }
    for (;;) {
        if (i >= len) {
            p->CrntCode = crnt;
            if (p->Reserved2c != 0)
                return 1;
            if (EGifCompressOutput(p, crnt) == 0)
                return 0;
            if (EGifCompressOutput(p, p->EOFCode) == 0)
                return 0;
            if (EGifCompressOutput(p, 0x1000) == 0)
                return 0;
            return 1;
        }
        unsigned int pixel = line[i++];
        unsigned int key = (crnt << 8) + pixel;
        unsigned int h = ((key >> 12) ^ key) & 0x1fff;
        unsigned int e = table[h];
        while ((e >> 12) != 0xfffff) {
            if (key == (e >> 12)) {
                crnt = table[h] & 0xfff;
                break;
            }
            h = (h + 1) & 0x1fff;
            e = table[h];
        }
        if ((e >> 12) == key)
            continue;
        if (EGifCompressOutput(p, crnt) == 0)
            return 0;
        unsigned int rc = p->RunningCode;
        crnt = pixel;
        if (rc < 0xfff) {
            p->RunningCode = rc + 1;
            _InsertHashTable(table, key, rc);
        } else {
            if (EGifCompressOutput(p, p->ClearCode) == 0)
                return 0;
            unsigned int rb = p->BitsPerPixel + 1;
            p->RunningCode = p->EOFCode + 1;
            p->RunningBits = rb;
            p->MaxCode1 = 1 << rb;
            memset(table, 0xff, 0x8000);
        }
    }
}
