// Slice s0084cd70, 0x0084cd70-0x0084dc90.  giflib encoder (egif_lib.c) + Spore GIF_*/PNG_*
// wrappers.  Optimized module (/O2, /GS-).
#include "types.h"

// ---------------------------------------------------------------- giflib I/O (all __stdcall)
extern "C" void*         __stdcall galloc(size_t n);              // 0x0087d4a0
extern "C" unsigned char __stdcall gfree(void* p);                 // 0x0087d4c0
extern "C" int           __stdcall gread(void* f, void* buf, unsigned n);   // 0x0087d4e0
extern "C" int           __stdcall gwrite(void* f, const void* buf, unsigned n); // 0x0087d510
extern "C" int           __stdcall gseek(void* f, long off, int whence);    // 0x0087d540
extern "C" int           __stdcall gtell(void* f);                 // 0x0087d570
extern "C" void*         __cdecl   memset(void* dst, int v, size_t n);
extern "C" void*         __cdecl   memcpy(void* dst, const void* src, size_t n);
extern "C" void*         __cdecl   png_get_io_ptr(void* png);      // 0x0086aeb0
extern "C" void          __cdecl   png_error(void* png, const char* msg); // 0x0086b250
void* __cdecl GIFgetinfo(void* name, int want, void* out, int stride);    // 0x0084c7d0

// ---------------------------------------------------------------- structures
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

// ---------------------------------------------------------------- forward decls (this slice)
int  __cdecl EGifCloseFile(void* g);                       // 0x0084ceb0
void* __cdecl EGifOpenFileHandle(void* f);                 // 0x0084d060
void* __cdecl _InitHashTable(void);                        // 0x0084cfd0
int  __cdecl EGifSetupCompress(void* g);                   // 0x0084d4c0

// @ 0x0084cd70
int __stdcall GIF_read(void* info, void* desc, int p3, int p4)
{
    int r = 0;
    GifFileType* g = (GifFileType*)GIFgetinfo(*(void**)((char*)info + 0x10),
                                              *(int*)((char*)desc + 0xc), (void*)p3, p4);
    if (g) {
        void* p = g->Private;
        if (g->SavedImageColorMap)
            gfree(g->SavedImageColorMap);
        if (g->ImageColorMap)
            gfree(g->ImageColorMap);
        if (p)
            gfree(p);
        gfree(g);
        r = 1;
    }
    return r;
}

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
void __cdecl _InsertHashTable(unsigned int* table, unsigned int key, unsigned int value)
{
    unsigned int i = (key >> 12 ^ key) & 0x1fff;
    while ((table[i] & 0xfffff000) != 0xfffff000)
        i = (i + 1) & 0x1fff;
    table[i] = (value & 0xfff) | (key << 12);
}

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
int __cdecl EGifPutScreenDesc(GifFileType* g, int width, int height, int colorRes,
                              int aspect, int bpp, void* cmap)
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

// @ 0x0084dc90
void __cdecl PNG_read_data(void* png, void* buf, int len)
{
    void* io = png_get_io_ptr(png);
    if (gread(io, buf, len) != len)
        png_error(png, "Read Error");
}

// ------------------------------------------------------------------------------
// The following functions were built with LTCG's custom register conventions
// (GifFile/private pointer passed in ESI/EAX instead of on the stack), which the
// source level cannot reproduce under this toolchain; they are reconstructed
// semantically from the original (giflib egif_lib.c).
// ------------------------------------------------------------------------------

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

// @ 0x0084d6e0
int __cdecl EGifPutImageDesc(GifFileType* g, int left, int top, int width, int height,
                             int interlace, int colorRes, void* cmap)
{
    EGifPrivate* p = (EGifPrivate*)g->Private;
    if (((p->FileState & 4) != 0 && p->Reserved2c > 0) || (p->FileState & 1) == 0)
        return 0;
    g->ImageWidth = width;
    g->ImageLeft = left < 0 ? 0 : left;
    g->ImageInterlace = interlace;
    g->ImageTop = top < 0 ? 0 : top;
    g->ImageHeight = height;
    g->ImageColorRes = colorRes;
    if (cmap) {
        int n = (1 << (colorRes & 0x1f)) * 3;
        if (g->SavedImageColorMap)
            gfree(g->SavedImageColorMap);
        void* dst = galloc(n);
        g->SavedImageColorMap = dst;
        memcpy(dst, cmap, n);
    }
    unsigned char b = 0x2c;
    gwrite(p->fd, &b, 1);
    unsigned short w;
    w = (unsigned short)left;
    gwrite(p->fd, &w, 2);
    w = (unsigned short)top;
    gwrite(p->fd, &w, 2);
    w = (unsigned short)width;
    gwrite(p->fd, &w, 2);
    w = (unsigned short)height;
    gwrite(p->fd, &w, 2);
    b = (unsigned char)((cmap ? 0x80 : 0) | (interlace ? 0x40 : 0) | (colorRes - 1));
    gwrite(p->fd, &b, 1);
    if (cmap) {
        int n = 1 << (colorRes & 0x1f);
        unsigned char* src = (unsigned char*)cmap;
        for (int k = 0; k < n; k++) {
            unsigned char c[3];
            c[0] = src[0];
            c[1] = src[1];
            c[2] = src[2];
            if (gwrite(p->fd, c, 3) == 0)
                return 0;
            src += 3;
        }
    }
    if (g->ImageColorMap == 0 && g->SavedImageColorMap == 0)
        return 0;
    p->FileState |= 4;
    p->Reserved2c = width * height;
    EGifSetupCompress(g);
    return 1;
}

// @ 0x0084d8d0
bool __stdcall GIF_write(void* info_, void* desc_, int param_3, int param_4)
{
    char* info = (char*)info_;
    char* desc = (char*)desc_;
    char* wf = *(char**)(info + 0x14);
    char* g = *(char**)(wf + 0xc);
    char* priv;
    unsigned char* pixels = (unsigned char*)param_3;
    bool ok = false;

    if (*(int*)(desc + 0x18) > 8)
        return false;
    if (g == 0)
        return false;
    unsigned char* line = (unsigned char*)galloc(*(unsigned int*)(desc + 0x10));
    if (line == 0)
        return false;
    ok = true;
    priv = *(char**)(g + 0x48);

    if (*(int*)(info + 0xc) == -1) {
        *(int*)(priv + 0x2c) = -1;
        gseek(*(void**)(info + 0x10), *(int*)(priv + 0x38), 0);
        unsigned char pal[0x300];
        memset(pal, 0, 0x300);
        int n = *(int*)(desc + 0x24);
        char* pu = desc + 0x29;
        unsigned char* pv = pal;
        for (int k = 0; k < n; k++) {
            int flag = *(int*)(desc + 0x438);
            pv[0] = pu[1];
            pv[1] = pu[0];
            pv[2] = pu[-1];
            if (flag != 0 && (unsigned char)pu[2] < 0x40 && *(int*)(priv + 0x2c) < 0)
                *(int*)(priv + 0x2c) = k;
            pv += 3;
            pu += 4;
        }
        if (EGifPutScreenDesc((GifFileType*)g, *(int*)(desc + 0x10), *(int*)(desc + 0x14),
                              *(int*)(desc + 0x1c),
                              ((*(int*)(priv + 0x2c) < 0) ? 0 : *(int*)(priv + 0x2c)),
                              *(int*)(desc + 0x1c), pal) == 0)
            ok = false;
        *(int*)(wf + 8) = *(int*)(desc + 0x14);
        *(int*)(wf + 4) = *(int*)(desc + 0x10);
        *(int*)(priv + 0x38) = gtell(*(void**)(info + 0x10));
    }

    gseek(*(void**)(info + 0x10), *(int*)(priv + 0x38), 0);
    int transparent = *(int*)(priv + 0x2c);
    float fdelay = *(float*)(desc + 0x2a60);
    int delay = 10;
    if (fdelay != 0.0f) {
        delay = (int)(100.0f / fdelay + 0.5f);
        if (delay >= 0x1771)
            delay = 6000;
        else if (delay < 0)
            delay = 0;
    }
    if (transparent >= 0 || fdelay != 0.0f) {
        unsigned char ext[4];
        *(unsigned short*)ext = (unsigned short)delay;
        ext[2] = (unsigned char)transparent;
        ext[3] = (unsigned char)((transparent >= 0) | 8);
        if (EGifPutExtension((GifFileType*)g, 0xf9, 4, ext) == 0)
            ok = false;
    }
    if (*(int*)(wf + 4) < *(int*)(desc + 0x10) || *(int*)(wf + 8) < *(int*)(desc + 0x14)) {
        int pos = gtell(*(void**)(info + 0x10));
        if (EGifUpdateLSD(*(void**)(info + 0x10), pos, *(int*)(desc + 0x14), pos) == 0)
            ok = false;
        *(int*)(wf + 4) = *(int*)(desc + 0x10);
        *(int*)(wf + 8) = *(int*)(desc + 0x14);
    }
    if (EGifPutImageDesc((GifFileType*)g, *(int*)(desc + 0x450), *(int*)(desc + 0x454),
                         *(int*)(desc + 0x10), *(int*)(desc + 0x14), 0,
                         *(int*)(desc + 0x1c), 0) == 0)
        ok = false;

    int rows = 0;
    while (rows < *(int*)(desc + 0x14)) {
        if (!ok)
            break;
        int x = 0;
        unsigned char* dst = line;
        while (x < *(int*)(desc + 0x10)) {
            unsigned char b = pixels[x];
            if (*(unsigned char*)(desc + 0x2b + (unsigned)b * 4) < 0x40 && transparent >= 0)
                b = (unsigned char)transparent;
            dst[x] = b;
            x++;
        }
        if ((*(unsigned char*)(g + 0x48) & 1) == 0) {
            ok = false;
        } else {
            int len = *(int*)(desc + 0x10);
            if (len == 0)
                len = *(int*)(g + 0x1c);
            *(int*)(priv + 0x2c) -= len;
            if (*(int*)(priv + 0x2c) < 0) {
                ok = false;
            } else {
                unsigned char mask = (unsigned char)priv[*(int*)(priv + 8) + 0x138];
                for (int m = 0; m < len; m++)
                    line[m] &= mask;
                if (EGifCompressLine((GifFileType*)g, line, len) == 0)
                    ok = false;
            }
        }
        pixels += param_4;
        rows++;
    }
    gfree(line);
    *(int*)(priv + 0x38) = gtell(*(void**)(info + 0x10));
    *(int*)(info + 0xc) = *(int*)(info + 0xc) + 1;
    return ok;
}

