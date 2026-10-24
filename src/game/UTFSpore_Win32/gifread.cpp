// src/game/UTFSpore_Win32/gifread.cpp -- migrated from slice(s) s0084be00 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/gifread.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __stdcall galloc(size_t size);                       // 0x0087d4a0
extern "C" void  __stdcall gfree(void* p);                            // 0x0087d4c0
extern "C" int   __stdcall gread(void* f, void* buf, unsigned n);     // 0x0087d4e0
extern "C" int   __stdcall gseek(void* f, long off, int whence);      // 0x0087d540
extern "C" void* __cdecl   memset(void* dst, int val, size_t n);
extern "C" char* __cdecl   strcpy(char* dst, const char* src);
extern "C" int   __cdecl   strncmp(const char* a, const char* b, size_t n);

// ---- items of slice s0084be00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __stdcall galloc(size_t size);                       // 0x0087d4a0
extern "C" void  __stdcall gfree(void* p);                            // 0x0087d4c0
extern "C" int   __stdcall gread(void* f, void* buf, unsigned n);     // 0x0087d4e0
extern "C" int   __stdcall gseek(void* f, long off, int whence);      // 0x0087d540
extern "C" void* __cdecl   memset(void* dst, int val, size_t n);
extern "C" char* __cdecl   strcpy(char* dst, const char* src);
extern "C" int   __cdecl   strncmp(const char* a, const char* b, size_t n);
struct GifFilePrivate;
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
    GifFilePrivate* Private;     // 0x48
};
struct GifFilePrivate {
    int FileState, FileHandle, BitsPerPixel, ClearCode, EOFCode;   // 0x00..0x13
    int RunningCode, RunningBits, MaxCode1, LastCode, CrntCode;    // 0x14..0x27
    int StackPtr, CrntShiftState, CrntShiftDWord, PixelCount;      // 0x28..0x37
    void* fd;                                                       // 0x38
    int masks[13];                                                  // 0x3c..0x6f
    unsigned char Buf[256];                                         // 0x70..0x16f
    unsigned char Suffix[0x1000];                                   // 0x170..0x116f
    unsigned char Stack[0x1000];                                    // 0x1170..0x216f
    int Prefix[0x1000];                                             // 0x2170..0x616f
};
int  DGifSetupDecompress(GifFileType* f);                     // 0x0084bd20
int  DGifGetPrefixChar(GifFileType* f);                       // 0x0084bd90
GifFileType* DGifOpenFileHandle(void* fh);                    // 0x0084c2b0
int  DGifDecompressInput(GifFileType* f, unsigned int* out);  // 0x0084c1f0
// LTCG view of 0x0084c1f0: the callee takes the private object in ESI (0x84c475 `mov esi,ebp`)
// and only the out-pointer on the stack (0x84c470 `lea edx,[esp+0x18]; push edx`).
int  DGifDecompressInputPriv(unsigned int* out);             // 0x0084c1f0
int  DGifDecompressLine(GifFileType* f, int line, int len);   // 0x0084c400
int  DGifGetLine(GifFileType* f, unsigned char* line, int len); // 0x0084c680
int  LoadImage(GifFileType* f, int dest, int stride);         // 0x0084c710
// ---- items of slice s0084be00 end

// @ 0x0084be00
void* __cdecl GIF_about(void)
{
    char* f = (char*)galloc(0x100);
    if (f) {
        memset(f, 0, 0x100);
        *(int*)(f + 0x00) = 0x2e474946;
        *(int*)(f + 0x04) = 0x100;
        *(int*)(f + 0x08) = 0x159;
        *(int*)(f + 0x14) = 0;
        *(int*)(f + 0x18) = 0x64;
        *(int*)(f + 0x1c) = 0x47494666;
        *(int*)(f + 0x0c) = (*(int*)(f + 0x0c) & 0xffffb4d7) | 0x201b4d7;
        strcpy(f + 0x3c, ".gif");
        strcpy(f + 0x7c, "FrANK G. Barchard");
        strcpy(f + 0x9c, "1.20");
        *(int*)(f + 0xa4) = 0x464947;
        *(int*)(f + 0xac) = 0x464947;
        strcpy(f + 0xbc, "Compuserve GIF");
        *(unsigned char*)(f + 0xdc) = 1;
        *(unsigned char*)(f + 0xdd) = 8;
        *(unsigned char*)(f + 0xde) = 8;
        *(unsigned char*)(f + 0xdf) = 8;
    }
    return f;
}

// @ 0x0084bf30
int __stdcall GIF_is(void* f)
{
    char buf[8];
    int off = 0;
    gseek(f, off, off);
    if (gread(f, buf, 6) != 0 &&
        (strncmp(buf, "GIF87a", 6) == 0 || strncmp(buf, "GIF89a", 6) == 0))
        return 100;
    return off;
}

// @ 0x0084bfa0
int DGifGetScreenDesc(GifFileType* f)
{
    GifFilePrivate* p = f->Private;
    short w[2];
    unsigned char rgb[4];
    if (gread(p->fd, w, 2) == 0)
        return 0;
    f->SWidth = w[0];
    if (gread(p->fd, w, 2) == 0)
        return 0;
    f->SHeight = w[0];
    if (gread(p->fd, rgb, 3) == 0)
        return 0;
    f->SColorResolution = (rgb[0] >> 4 & 7) + 1;
    int n = (rgb[0] & 7) + 1;
    f->SBackGroundColor = n;
    f->AspectByte = rgb[1];
    if ((char)rgb[0] < 0) {
        int cnt = 1 << n;
        unsigned char* cmap = (unsigned char*)galloc(cnt * 3);
        f->ImageColorMap = cmap;
        for (int i = 0; i < cnt; i++) {
            if (gread(p->fd, rgb, 3) == 0)
                return 0;
            cmap[i * 3 + 0] = rgb[0];
            cmap[i * 3 + 1] = rgb[1];
            cmap[i * 3 + 2] = rgb[2];
        }
    }
    return 1;
}

// @ 0x0084c0a0
int DGifGetImageDesc(GifFileType* f)
{
    GifFilePrivate* p = f->Private;
    short w[2];
    unsigned char rgb[4];
    if (gread(p->fd, w, 2) == 0)
        return 0;
    f->ImageLeft = w[0];
    if (gread(p->fd, w, 2) == 0)
        return 0;
    f->ImageTop = w[0];
    if (gread(p->fd, w, 2) == 0)
        return 0;
    f->ImageWidth = w[0];
    if (gread(p->fd, w, 2) == 0)
        return 0;
    f->ImageHeight = w[0];
    if (gread(p->fd, rgb, 1) == 0)
        return 0;
    int n = (rgb[0] & 7) + 1;
    f->ImageColorRes = n;
    f->ImageInterlace = rgb[0] & 0x40;
    if ((char)rgb[0] < 0) {
        int cnt = 1 << n;
        if (f->SavedImageColorMap)
            gfree(f->SavedImageColorMap);
        unsigned char* cmap = (unsigned char*)galloc(cnt * 3);
        f->SavedImageColorMap = cmap;
        for (int i = 0; i < cnt; i++) {
            if (gread(p->fd, rgb, 3) == 0)
                return 0;
            cmap[i * 3 + 0] = rgb[0];
            cmap[i * 3 + 1] = rgb[1];
            cmap[i * 3 + 2] = rgb[2];
        }
    }
    p->PixelCount = f->ImageHeight * f->ImageWidth;
    DGifSetupDecompress(f);
    return 1;
}

// @ 0x0084c1f0
int DGifDecompressInput(GifFileType* f, unsigned int* out)
{
    GifFilePrivate* p = f->Private;
    if (p->CrntShiftState < p->RunningBits) {
        unsigned char* buf = p->Buf;
        do {
            void* fh = p->fd;
            unsigned char b;
            if (buf[0] == 0) {
                if (gread(fh, buf, 1) == 0)
                    return 0;
                if (gread(fh, p->Buf + 1, buf[0]) == 0)
                    return 0;
                b = p->Buf[1];
                buf[0] -= 1;
                p->Buf[1] = 2;
            } else {
                b = buf[p->Buf[1]];
                p->Buf[1] += 1;
                buf[0] -= 1;
            }
            int idx = p->CrntShiftState;
            p->CrntShiftState = idx + 8;
            p->CrntShiftDWord |= (unsigned)b << (idx & 0x1f);
        } while (p->CrntShiftState < p->RunningBits);
    }
    *out = (unsigned)p->masks[p->RunningBits] & (unsigned)p->CrntShiftDWord;
    int nb = p->RunningBits;
    p->RunningCode += 1;
    p->CrntShiftDWord = (int)((unsigned)p->CrntShiftDWord >> (nb & 0x1f));
    p->CrntShiftState -= nb;
    if (p->MaxCode1 < p->RunningCode && nb < 0xc) {
        p->MaxCode1 *= 2;
        p->RunningBits = nb + 1;
    }
    return 1;
}

// @ 0x0084c2b0
GifFileType* DGifOpenFileHandle(void* fh)
{
    GifFileType* g = (GifFileType*)galloc(0x4c);
    if (!g)
        return 0;
    GifFilePrivate* p = (GifFilePrivate*)galloc(0x6170);
    if (!p) {
        gfree(g);
        return 0;
    }
    g->Private = p;
    g->SavedImageColorMap = 0;
    g->ImageColorMap = 0;
    unsigned char magic[6];
    if (gread(fh, magic, 6) == 0)
        goto fail;
    magic[6] = 0;
    if (strncmp((char*)magic, "GIF87a", 6) != 0 &&
        strncmp((char*)magic, "GIF89a", 6) != 0)
        goto fail;
    if (DGifGetScreenDesc(g) == 0)
        goto fail;
    p->FileHandle = 0;
    p->fd = fh;
    p->FileState = 0;
    p->masks[0] = 0;
    p->masks[1] = 1;
    p->masks[2] = 3;
    p->masks[3] = 7;
    p->masks[4] = 0xf;
    p->masks[5] = 0x1f;
    p->masks[6] = 0x3f;
    p->masks[7] = 0x7f;
    p->masks[8] = 0xff;
    p->masks[9] = 0x1ff;
    p->masks[10] = 0x3ff;
    p->masks[11] = 0x7ff;
    p->masks[12] = 0xfff;
    return g;
fail:
    gfree(p);
    gfree(g);
    return 0;
}

// 0x0084bd90 DGifGetPrefixChar(Prefix, Code, ClearCode): LTCG passes Prefix in ESI, Code in
// EAX and ClearCode in EDX, so the call cannot be spelled in C++.  The walk is pure (it only
// reads Prefix), so reproduce it locally; callers get the same value.
static int DGifGetPrefixCharLocal(const int* prefix, int code, int clear)
{
    int i = 0;
    while (code > clear) {
        if (i > 0xfff)
            break;
        code = prefix[code];
        i++;
    }
    return code;
}

// @ 0x0084c400
int DGifDecompressLine(GifFileType* f, int line, int len)
{
    GifFilePrivate* p = f->Private;
    unsigned char* suffix = p->Suffix;
    unsigned char* stack = p->Stack;
    int local_4 = p->EOFCode;
    int local_14 = p->StackPtr;
    int iVar5 = p->LastCode;
    int local_18 = 0;
    int local_c = p->ClearCode;
    int iVar4 = iVar5;

    while (local_14 != 0) {
        if (len <= local_18)
            goto done;
        unsigned char b = suffix[local_14 - 1];
        local_14--;
        if ((unsigned)b != (unsigned)f->ImageTransparent)
            ((unsigned char*)line)[local_18] = b;
        local_18++;
    }
    while (local_18 < len) {
        unsigned int local_10;
        unsigned int uVar3;
        int iVar6 = 0;
        int iVar8;
        iVar4 = iVar5;
        if (DGifDecompressInputPriv(&local_10) == 0)
            return 0;
        if ((int)local_10 == local_4) {
            if ((local_18 != len - 1) || (p->PixelCount != 0))
                local_18 = len - 1;
            local_18++;
            iVar4 = iVar5;
        } else if ((int)local_10 == local_c) {
            for (iVar8 = 0; iVar8 < 0xfff; iVar8++)
                p->Prefix[iVar8] = 0x1002;
            p->RunningCode = p->EOFCode + 1;
            iVar8 = p->BitsPerPixel + 1;
            p->RunningBits = iVar8;
            p->LastCode = 0x1002;
            iVar5 = 0x1002;
            iVar4 = 0x1002;
            p->MaxCode1 = 1 << (iVar8 & 0x1f);
        } else {
            if ((int)local_10 < local_c) {
                if ((int)local_10 != f->ImageTransparent)
                    ((char*)line)[local_18] = (char)local_10;
                local_18++;
                iVar6 = iVar5;
            } else {
                iVar6 = iVar5;
                iVar4 = (int)local_10;
                if (p->Prefix[local_10] == 0x1002) {
                    if ((int)local_10 != p->RunningCode - 2)
                        return 0;
                    uVar3 = (unsigned)DGifGetPrefixCharLocal(p->Prefix, iVar5, local_c);
                    suffix[local_14] = (unsigned char)uVar3;
                    stack[p->RunningCode - 3] = (unsigned char)uVar3;
                    local_14++;
                    iVar4 = iVar5;
                }
                iVar8 = 0;
                do {
                    iVar8++;
                    if ((iVar4 <= local_c) || (0xfff < iVar4))
                        goto lab_c59c;
                    suffix[local_14] = stack[iVar4 - 1];
                    iVar4 = p->Prefix[iVar4];
                    local_14++;
                } while (iVar8 < 0x1000);
                iVar8++;
            lab_c59c:
                if (0xffe < iVar8)
                    return 0;
                if (0xfff < iVar4)
                    return 0;
                suffix[local_14] = (unsigned char)iVar4;
                local_14++;
                while (local_14 != 0 && local_18 < len) {
                    unsigned char b = suffix[local_14 - 1];
                    local_14--;
                    if ((unsigned)b != (unsigned)f->ImageTransparent)
                        ((unsigned char*)line)[local_18] = b;
                    local_18++;
                }
            }
            iVar5 = (int)local_10;
            iVar4 = (int)local_10;
            if (iVar6 != 0x1002) {
                p->Prefix[p->RunningCode - 2] = iVar6;
                iVar5 = p->RunningCode;
                uVar3 = (unsigned)DGifGetPrefixCharLocal(p->Prefix,
                    (int)local_10 == p->RunningCode - 2 ? iVar6 : (int)local_10, local_c);
                stack[iVar5 - 3] = (unsigned char)uVar3;
                iVar5 = (int)local_10;
                iVar4 = (int)local_10;
            }
        }
    }
done:
    p->LastCode = iVar5;
    p->StackPtr = local_14;
    return 1;
}

// @ 0x0084c680
int DGifGetLine(GifFileType* f, unsigned char* line, int len)
{
    GifFilePrivate* p = f->Private;
    if (len == 0)
        len = f->ImageWidth;
    p->PixelCount -= len;
    if (DGifDecompressLine(f, (int)line, len) != 1)
        return 0;
    if (p->PixelCount != 0)
        return 1;
    for (;;) {
        p = f->Private;
        unsigned char b;
        if (gread(p->fd, &b, 1) == 0)
            return 0;
        if (b == 0) {
            p->Buf[0] = 0;
            p->PixelCount = 0;
            return 1;
        }
        p->Buf[0] = b;
        if (gread(p->fd, p->Buf + 1, b) == 0)
            return 0;
    }
}

// @ 0x0084c710
int LoadImage(GifFileType* f, int dest, int stride)
{
    int ebx = f->ImageLeft;
    int esi = f->ImageTop;
    int local_8;
    if (ebx < 0)
        ebx = 0;
    if (esi < 0)
        esi = 0;
    int edx = f->ImageHeight;
    if (f->SHeight < edx + esi)
        esi = f->SHeight - edx;
    int ecx = f->ImageWidth;
    if (f->SWidth < ecx + ebx)
        ebx = f->SWidth - ecx;
    if (esi < 0 || ebx < 0)
        return 0;
    local_8 = 0;
    if (edx > 0) {
        int ebp = 8;
        do {
            int off = f->ImageWidth;
            off = esi * stride + ebx + dest;
            if (DGifGetLine(f, (unsigned char*)off, f->ImageWidth) == 0)
                return 0;
            if (f->ImageInterlace == 0) {
                esi++;
            } else {
                esi += ebp;
                if (esi >= f->ImageHeight) {
                    if ((esi & (ebp - 1)) != 0)
                        ebp >>= 1;
                    esi = ebp >> 1;
                }
            }
            local_8++;
        } while (local_8 < f->ImageHeight);
    }
    return 1;
}
