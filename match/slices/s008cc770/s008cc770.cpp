// Slice s008cc770: FreeType-derived TrueType scaling ("T2KTTClass"), CMap and kern-table
// helpers. These operate on the 'tt_face' / 'T2KTTClass' structures whose fields the original
// reaches through raw offsets; the class below reproduces those offsets. The allocation and
// stream helpers (tsi_AllocMem, ReadInt16, ...) are real extern functions in the module.
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;
typedef signed short   s16;
typedef int            i32;

// Stream/serialiser object handed to ReadInt16/ReadInt32/PeekInt16/Seek_InputStream.
struct Stream;

// --- imported helpers (real addresses given in comments) --------------------------------
void* tsi_AllocMem(void* mem, u32 size);         // 0x8d1260
void  tsi_DeAllocMem(void* mem, void* ptr);      // 0x8d1440
s16   ReadInt16(Stream* s);                      // 0x8cc190
i32   ReadInt32(Stream* s);                      // 0x8cc0f0
void  PeekInt16(Stream* s, void* dst, u32 n);    // 0x8cc220
void  Seek_InputStream(Stream* s, u32 off);      // 0x8cc580
void  Delete_InputStream(Stream* s, int flags);  // 0x8cc5d0
Stream* New_InputStream2(void* mem, int* file, u32 off, u32 size, int a, int b); // 0x8cc330
i32   util_FixDiv(i32 a, i32 b);                 // 0x8d16d0
i32   util_FixMul(i32 a, i32 b);                 // 0x8d1590
u16   GetUPEM(void* face);                       // 0x8ceb70
void* GetTableDirEntry_sfntClass(void* face, u32 tag); // 0x8cebe0
void  FUN_008af5e0(void* p);                     // 0x8af5e0
void  fnt_Execute(void* a, i32 b, i32 c, void* d, i32 e); // 0x8ac600
i32   fnt_RoundToGrid(void);                     // 0x8ac040
void  setT2KScaleFactors(i32 a, i32 b, u8* out); // 0x8cd1b0

// --- the scaled font object -------------------------------------------------------------
// Offsets match the retail structure. Only the fields the slice touches are named; the rest
// are reached through explicit byte offsets on a flat buffer.
struct T2K {
    void*  mMem;                 // 0x00
    i32    mXScale;              // 0x04
    i32    mYScale;              // 0x08
    u32    pad0c;                // 0x0c
    u32    pad10;                // 0x10
    void*  mAlloc;               // 0x14
    u8     pad18[0x158 - 0x18];  // 0x18 .. 0x158
};

// Face object supplied by the caller; only offsets we read are described.
struct TTFace {
    u8     pad00[0x158];
};

extern "C" {
}

// @ 0x008cc770
void* New_T2KTTClass(void* mem, int* file, void* face)
{
    u8* p = (u8*)tsi_AllocMem(mem, 0x158);
    int* f = (int*)face;
    u32 tbl = *(u32*)((u8*)face + 0x54);

    *(u32*)(p + 0x00) = (u32)mem;
    *(u32*)(p + 0xd0) = tbl;
    *(u32*)(p + 0x04) = 0xffffffff;
    *(u32*)(p + 0x08) = 0x7fffa55a;
    u16 upem = GetUPEM(face);
    *(u16*)(p + 0xec) = upem;
    FUN_008af5e0(p + 0x18);

    u32 n1 = *(u16*)(tbl + 0x1c);
    *(u32*)(p + 0x18) = (u32)tsi_AllocMem(mem, n1 * 4);
    u32 n2 = *(u16*)(tbl + 0x16);
    *(u32*)(p + 0x1c) = (u32)tsi_AllocMem(mem, n2 * 4);
    for (i32 i = 0; i < (i32)n2; ++i)
        ((u32*)*(u32*)(p + 0x1c))[i] = 0;

    u32 nmax = *(u16*)(tbl + 0x0e);
    if (*(u16*)(tbl + 0x0a) > nmax) nmax = *(u16*)(tbl + 0x0a);
    *(u32*)(p + 0x14) = (u32)tsi_AllocMem(mem, nmax * 9 + 0x24);
    *(u32*)(p + 0x20) = 0;
    *(u32*)(p + 0x0c) = 0;
    *(u32*)(p + 0x10) = 0;

    u8* te = (u8*)GetTableDirEntry_sfntClass(face, 0x63767420); // 'cvt '
    if (te) {
        Stream* s = New_InputStream2(mem, file, *(u32*)(te + 8), *(u32*)(te + 0xc), 0, 0);
        u32 cnt = *(u32*)(te + 0xc) >> 1;
        *(u32*)(p + 0xe4) = cnt;
        *(u32*)(p + 0x20) = (u32)tsi_AllocMem(mem, cnt * 4);
        s16* dst = (s16*)tsi_AllocMem(mem, cnt * 2);
        *(u32*)(p + 0x0c) = (u32)dst;
        *(u32*)(p + 0x10) = cnt;
        while (cnt > 0) { *dst++ = ReadInt16(s); --cnt; }
        Delete_InputStream(s, 0);
    }

    *(u32*)(p + 0xa8) = (u32)tsi_AllocMem(mem, *(u16*)(tbl + 0x18) * 8);
    *(u32*)(p + 0xac) = (u32)tsi_AllocMem(mem, *(u16*)(tbl + 0x1a) * 8);

    u32* sizeSlot = (u32*)(p + 0xf0);
    u32* dataSlot = (u32*)(p + 0xb4);
    for (i32 i = 0; i < 2; ++i) {
        *dataSlot = 0;
        u32 tag = (i != 0) ? 0x70726570u : 0x6d6f7270u; // "prep"/"morx" family tag
        u8* te2 = (u8*)GetTableDirEntry_sfntClass(face, tag);
        if (te2) {
            if (((u8*)file)[0x228] == 5 || file[2] != 0) {
                Seek_InputStream((Stream*)file, *(u32*)(te2 + 8));
                u32 n = *(u32*)(te2 + 0xc);
                *sizeSlot = n;
                i32 buf = (i32)tsi_AllocMem(mem, n);
                *dataSlot = (u32)buf;
                PeekInt16((Stream*)file, (void*)buf, n);
                p[0xf8] = 1;
            } else {
                *sizeSlot = *(u32*)(te2 + 0xc);
                *dataSlot = (u32)(*(i32*)(te2 + 8) + *(i32*)file);
                p[0xf8] = 0;
            }
        }
        sizeSlot++;
        dataSlot++;
    }

    u8* q = p + 0x18;
    *(u16*)(q + 0x30) = 0;
    *(u16*)(q + 0x2a) = 9;
    *(u16*)(q + 0x2c) = 3;
    *(u32*)(q + 0x04) = 0;
    *(u32*)(q + 0x10) = 0;
    *(u16*)(q + 0x2e) = 0x80;
    *(u32*)(q + 0x18) = (u32)&fnt_RoundToGrid;
    *(u32*)(q + 0x14) = 0x40;
    *(u32*)(q + 0x00) = 0x44;
    *(u8*)(q + 0x32) = 1;
    *(u32*)(q + 0x0c) = 0x307c0;

    u32 nglyph = (u32)(s16)*(u16*)((u8*)face + 0x14);
    *(u16*)(p + 0xee) = *(u16*)((u8*)face + 0x14);
    u32 base = (u32)tsi_AllocMem(mem, nglyph * 0x16);
    u32 stride4 = nglyph * 4;
    *(u32*)(p + 0x100) = base;
    u32 cur = base + stride4;
    *(u32*)(p + 0x104) = cur;
    cur += stride4;
    *(u32*)(p + 0x108) = cur;
    cur += stride4;
    *(u32*)(p + 0x10c) = cur;
    cur += stride4;
    *(u32*)(p + 0x110) = cur;
    cur += nglyph * 2;
    *(u32*)(p + 0x114) = cur;
    cur += nglyph * 2;
    *(u32*)(p + 0x118) = cur;
    cur += nglyph;
    *(u32*)(p + 0x128) = cur;

    *(u16*)(p + 0xfa) = 0;
    *(u16*)(p + 0xfc) = 0;
    *(u16*)(p + 0x11c) = 1;
    *(u16*)(p + 0x11e) = 0;
    *(u32*)(p + 0x124) = (u32)(p + 0xfc);
    *(u32*)(p + 0x120) = (u32)(p + 0xfa);

    // copy 13 dwords from q+0x24 to q+0x58
    i32  pad = *(i32*)(q + 0xa0);
    u32* dst = (u32*)(q + 0x58);
    u32* src = (u32*)(q + 0x24);
    for (i32 i = 0; i < 13; ++i) dst[i] = src[i];

    if (pad != 0) {
        q[0xc9] = 1;
        q[0xc8] = 1;
        fnt_Execute(p + 0x100, *(i32*)(q + 0xa0), *(i32*)(p + 0xf4) + *(i32*)(q + 0xa0),
                    p + 0x18, 0);
    }
    return p;
}

// @ 0x008ccb20
i32 FUN_008ccb20(u8* o, i32 x)
{
    u8 sh = *(u8*)(o + 0xb4);
    return (*(i32*)(o + 0xa8) * x + *(i32*)(o + 0xb0)) >> sh;
}

// @ 0x008ccb40
i32 FUN_008ccb40(u8* o, i32 x)
{
    if (x > -1)
        return (*(i32*)(o + 0xa8) * x + *(i32*)(o + 0xb0)) / *(i32*)(o + 0xac);
    return -((*(i32*)(o + 0xb0) - *(i32*)(o + 0xa8) * x) / *(i32*)(o + 0xac));
}

// @ 0x008ccb90
void fnt_FixRound(u8* o, i32 v)
{
    util_FixMul(v, *(i32*)(o + 0xa4));
}

// @ 0x008ccbb0
void FUN_008ccbb0(u8* o, i32 xScale, i32 yScale)
{
    if (o == 0) return;
    if (*(i32*)(o + 4) == xScale && *(i32*)(o + 8) == yScale) return;

    u8* e = o + 0x18;
    *(i32*)(o + 4) = xScale;
    *(i32*)(o + 8) = yScale;
    *(i32*)(e + 0xb8) = 0x10000;
    *(i32*)(e + 0xbc) = 0x10000;
    if (xScale == yScale) {
        *(u8*)(e + 0xb6) = 1;
        *(u16*)(e + 0x0c) = (u16)xScale;
    } else {
        *(u8*)(e + 0xb6) = 0;
        if (xScale > yScale) {
            *(u16*)(e + 0x0c) = (u16)xScale;
            *(i32*)(e + 0xbc) = util_FixDiv(yScale, xScale);
        } else {
            *(u16*)(e + 0x0c) = (u16)yScale;
            *(i32*)(e + 0xb8) = util_FixDiv(xScale, yScale);
        }
    }
    u16 s = *(u16*)(e + 0x0c);
    *(u16*)(e + 0x0e) = s;
    *(u32*)(e + 0x10) = (u32)s << 16;
    *(u32*)(e + 0x14) = 0;
    *(u32*)(e + 0x18) = 0;
    *(u32*)(e + 0x1c) = 0;
    *(u32*)(e + 0x20) = 0;

    u8 loc[0x1c];
    setT2KScaleFactors(s, *(u16*)(o + 0xec), loc);

    i32 n = *(i32*)(o + 0x10);
    i32 mode = *(s16*)(loc + 0x18);
    i32 c   = *(i32*)(loc + 0x14);
    i32 d   = *(i32*)(loc + 0x10);
    s16 a   = *(s16*)(loc + 0x00);
    s16 b   = *(s16*)(loc + 0x02);
    u8  sh  = *(u8*)(loc + 0x04);

    if (mode == 0) {
        *(u32*)(e + 0x98) = (u32)&FUN_008ccb20;
        for (i32 i = 0; i < n; ++i) {
            i32 v = *(s16*)((u8*)*(u32*)(o + 0x0c) + i * 2);
            ((i32*)*(u32*)(e + 0x08))[i] = (v * a + c) >> sh;
        }
    } else if (mode == 1) {
        *(u32*)(e + 0x98) = (u32)&FUN_008ccb40;
        for (i32 i = 0; i < n; ++i) {
            i32 v = *(s16*)((u8*)*(u32*)(o + 0x0c) + i * 2);
            i32 r;
            if (v > -1) r = (a * v + c) / d;
            else        r = -((c - a * v) / d);
            ((i32*)*(u32*)(e + 0x08))[i] = r;
        }
    } else if (mode == 2) {
        *(u32*)(e + 0x98) = (u32)&fnt_FixRound;
        for (i32 i = 0; i < n; ++i) {
            i32 v = *(s16*)((u8*)*(u32*)(o + 0x0c) + i * 2);
            ((i32*)*(u32*)(e + 0x08))[i] = util_FixMul(v, b);
        }
    }

    *(i32*)(o + 0xc0) = a;
    *(u16*)(o + 0xcc) = *(u16*)(loc + 0x02);
    *(i32*)(o + 0xc4) = d;
    *(i32*)(o + 0xbc) = b;
    *(i32*)(o + 0xc8) = c;

    i32 ng = *(s16*)(o + 0xee);
    for (i32 i = 0; i < ng; ++i) {
        ((u32*)*(u32*)(o + 0x100))[i] = 0;
        ((u32*)*(u32*)(o + 0x104))[i] = 0;
        ((u32*)*(u32*)(o + 0x108))[i] = 0;
        ((u32*)*(u32*)(o + 0x10c))[i] = 0;
        ((u16*)*(u32*)(o + 0x110))[i] = 0;
        ((u16*)*(u32*)(o + 0x114))[i] = 0;
        ((u8*)*(u32*)(o + 0x118))[i] = 0;
        ((u8*)*(u32*)(o + 0x128))[i] = 0;
    }

    if (*(i32*)(o + 0xb4) != 0) {
        u32* s1 = (u32*)(o + 0x3c);
        u32* d1 = (u32*)(o + 0x70);
        for (i32 i = 0; i < 13; ++i) d1[i] = s1[i];
        *(u16*)(o + 0xca) = 0;
        *(u8*)(o + 0xc9) = 0;
        *(u8*)(o + 0xc8) = 1;
        fnt_Execute(o + 0x100, *(i32*)(o + 0xb4), *(i32*)(o + 0xf0) + *(i32*)(o + 0xb4),
                    o + 0x18, 0);
        u32* s2 = (u32*)(o + 0x70);
        u32* d2 = (u32*)(o + 0x3c);
        for (i32 i = 0; i < 13; ++i) d2[i] = s2[i];
    }
}

// @ 0x008cceb0
void FUN_008cceb0(u8* o, u8* src)
{
    if (o == 0) return;
    if (*(i32*)(src + 0x64) == 0) return;
    if (*(i32*)(src + 0x68) <= 0) return;

    i32 n = (i32)*(s16*)(src + 0x38) + 4;

    *(u32*)(o + 0x12c) = *(u32*)(src + 0x50);
    *(u32*)(o + 0x130) = *(u32*)(src + 0x54);
    *(u32*)(o + 0x134) = *(u32*)(o + 0x14);
    i32 base = *(i32*)(o + 0x14);
    *(u32*)(o + 0x138) = base + n * 4;
    *(u32*)(o + 0x13c) = *(u32*)(src + 0x44);
    *(u32*)(o + 0x140) = *(u32*)(src + 0x48);
    *(u32*)(o + 0x144) = *(u32*)(src + 0x4c);
    *(u16*)(o + 0x148) = *(u16*)(src + 0x36);
    *(u16*)(o + 0x14a) = 0;
    *(u32*)(o + 0x14c) = *(u32*)(src + 0x3c);
    *(u32*)(o + 0x150) = *(u32*)(src + 0x40);
    i32 dst2 = *(i32*)(o + 0x138) + n * 4;
    *(u32*)(o + 0x154) = dst2;

    {
        i32 off = *(i32*)(src + 0x50) - base;
        i32* p = (i32*)base;
        for (i32 i = 0; i < n; ++i) {
            p[i] = *(i32*)(off + (i32)&p[i]);
            *(u8*)(dst2 + i) = 0;
        }
    }
    {
        i32* p = (i32*)*(u32*)(o + 0x138);
        i32 off = *(i32*)(src + 0x54) - (i32)p;
        for (i32 i = 0; i < n; ++i) p[i] = *(i32*)((i32)&p[i] + off);
    }

    i32 sc = *(i32*)(o + 0xd4);
    if (sc != 0x10000) {
        i32 addr = *(i32*)(o + 0x140);
        s16* p = (s16*)addr;
        for (i32 i = 0; i < n; ++i) p[i] = (s16)util_FixMul(p[i], sc);
    }
    sc = *(i32*)(o + 0xd0);
    if (sc != 0x10000) {
        i32 addr = *(i32*)(o + 0x13c);
        s16* p = (s16*)addr;
        for (i32 i = 0; i < n; ++i) p[i] = (s16)util_FixMul(p[i], sc);
    }

    {
        i32 arr = *(i32*)(src + 0x50);
        i32 idx = (s16)*(u16*)(src + 0x38);
        i32 lo = *(i32*)(arr + idx * 4);
        i32 hi = *(i32*)(arr + idx * 4 + 4);
        *(i32*)(arr + idx * 4) = lo + 0x20;
        *(i32*)(arr + idx * 4) &= ~0x3f;
        i32 cur = *(i32*)(arr + idx * 4);
        *(i32*)(arr + idx * 4 + 4) = cur + (((hi - lo) + 0x20) & ~0x3f);
    }
    {
        i32 arr = *(i32*)(src + 0x54);
        i32 idx = (s16)*(u16*)(src + 0x38);
        i32 lo = *(i32*)(arr + idx * 4 + 8);
        i32 hi = *(i32*)(arr + idx * 4 + 0xc);
        *(i32*)(arr + idx * 4 + 8) = lo + 0x20;
        *(i32*)(arr + idx * 4 + 8) &= ~0x3f;
        i32 cur = *(i32*)(arr + idx * 4 + 8);
        *(i32*)(arr + idx * 4 + 0xc) = cur + (((hi - lo) + 0x20) & ~0x3f);
    }

    o[0xe1] = 0;
    o[0xe0] = 0;
    {
        u32* s1 = (u32*)(o + 0x3c);
        u32* d1 = (u32*)(o + 0x70);
        for (i32 i = 0; i < 13; ++i) d1[i] = s1[i];
    }
    fnt_Execute(o + 0x100, *(i32*)(src + 0x64), *(i32*)(src + 0x68) + *(i32*)(src + 0x64),
                o + 0x18, 0);
}

// @ 0x008cd0f0
void FUN_008cd0f0(u8* p)
{
    if (p == 0) return;
    tsi_DeAllocMem(*(void**)p, *(void**)(p + 0x18));
    tsi_DeAllocMem(*(void**)p, *(void**)(p + 0x1c));
    tsi_DeAllocMem(*(void**)p, *(void**)(p + 0x20));
    tsi_DeAllocMem(*(void**)p, *(void**)(p + 0xa8));
    tsi_DeAllocMem(*(void**)p, *(void**)(p + 0xac));
    if (*(u8*)(p + 0xf8) != 0) {
        void** q = (void**)(p + 0xb4);
        i32 n = 2;
        do {
            tsi_DeAllocMem(*(void**)p, *q);
            q++;
        } while (--n != 0);
    }
    tsi_DeAllocMem(*(void**)p, *(void**)(p + 0x14));
    tsi_DeAllocMem(*(void**)p, *(void**)(p + 0x0c));
    tsi_DeAllocMem(*(void**)p, *(void**)(p + 0x100));
    tsi_DeAllocMem(*(void**)p, p);
}

// @ 0x008cd1b0
void setT2KScaleFactors(i32 a, i32 b, u8* out)
{
    i32 esi = a << 6;
    i32 ebx = b;
    while (((esi | ebx) & 1) == 0) { esi >>= 1; ebx >>= 1; }

    i32 ebp = ebx >> 1;
    *(u16*)(out + 0x10) = 2;
    *(i32*)(out + 0x0c) = util_FixDiv(esi, ebx);

    if ((u32)(esi + 0x7fff) <= 0xfffe) {
        *(u16*)(out + 0x00) = (u16)esi;
        i32 sh = 0;
        while ((ebx & 1) == 0) { ++sh; ebx >>= 1; }
        if (ebx == 1) {
            *(i32*)(out + 4) = ebx;
            *(i32*)(out + 8) = ebp;
            *(u16*)(out + 0x10) = 0;
            *(u16*)(out + 2) = (u16)sh;
        } else {
            *(u16*)(out + 0x10) = 1;
            *(u16*)(out + 2) = (u16)sh;
            *(i32*)(out + 4) = ebx;
            *(i32*)(out + 8) = ebp;
        }
    }
}

// @ 0x008cd260
i32 FUN_008cd260(u8* ctx, u32 code)
{
    i32 base = *(i32*)(*(i32*)(*(i32*)(ctx + 0xc) + (s16)*(u16*)(ctx + 0x18) * 4) + 4) + 6
               + *(i32*)(ctx + 0x10);
    u32 hi = (code >> 8) & 0xff;
    u8* pb = (u8*)(base + 0x200 + (i32)(hi * 0x100) / 8);
    u32 lo = (code & 0xff) >> 3;
    i32 sum = 0;
    if (pb[lo] & (u8)(1 << (code & 7))) {
        i32 k = (i32)lo;
        while (k != 0) {
            u8 v = *pb++;
            sum += (v & 1) + ((v >> 4) & 1) + ((0xe994 >> (v & 0xe)) & 3)
                 + ((0xe994 >> ((v >> 4) & 0xe)) & 3);
            --k;
        }
        u8 v = *pb;
        i32 cnt = (i32)(code & 7) + 1;
        do { sum += (v & 1); v >>= 1; } while (--cnt);
        u32 pair = ((u32)*(u8*)(base + hi * 2) << 8) | *(u8*)(base + hi * 2 + 1);
        return sum + (i32)(pair & 0xffff);
    }
    return 0;
}

// @ 0x008cd350
i32 FUN_008cd350(u8* ctx, u32 want)
{
    u8* pb = (u8*)(*(i32*)(*(i32*)(*(i32*)(ctx + 0xc) + (s16)*(u16*)(ctx + 0x18) * 4) + 4) + 6
                   + *(i32*)(ctx + 0x10));
    u32 hdr = ((u32)pb[0] << 8) | pb[1];
    u8* p = pb + 8;
    if (hdr > 0xe) {
        u32 lo = 0;
        u32 hi = (hdr - 2) & 0xffff;
        do {
            u32 mid = ((i32)(hi + lo) >> 1) & 0xfffe;
            u32 v = ((u32)p[mid] << 8) | p[mid + 1];
            if ((u16)want > (u16)v) lo = (mid + 2) & 0xffff;
            else                   hi = mid;
        } while ((i32)(hi - lo) > 0xc);
        p += lo;
    }
    u8* seg;
    do {
        seg = p;
        p += 2;
    } while ((u16)want > (u16)(((u32)seg[0] << 8) | seg[1]));

    u32 off = hdr & 0xffff;
    u32 v1 = ((u32)p[off] << 8) | p[off + 1];
    p += off;
    if ((u16)want < (u16)v1) return 0;
    u32 v2 = ((u32)p[off] << 8) | p[off + 1];
    p += off;
    i32 res = 0;
    if ((u16)want <= (u16)v2) {
        u32 dt = ((u32)p[0] << 8) | p[1];
        if (dt == 0) {
            res = (i32)((u16)v1 + (u16)want);
        } else {
            u32 idx = ((u16)want - (u16)v1) * 2 + dt + (u32)p;
            if (idx >= (u32)(*(i32*)(ctx + 0x14) + *(i32*)(ctx + 0x10))) return 0;
            u8* q = (u8*)idx;
            res = (i32)((u16)(((u32)q[0] << 8) | q[1]) + (u16)v1);
        }
    }
    if (*(i32*)(ctx + 8) <= res) return 0;
    return res;
}

// @ 0x008cd4b0
u16 FUN_008cd4b0(u8* ctx, u16 want)
{
    u8* pb = (u8*)(*(i32*)(*(i32*)(*(i32*)(ctx + 0xc) + (s16)*(u16*)(ctx + 0x18) * 4) + 4) + 6
                   + *(i32*)(ctx + 0x10));
    u16 base = ((u16)pb[0] << 8) | pb[1];
    u16 n = ((u16)pb[2] << 8) | pb[3];
    u16 d = (u16)(want - base);
    u16 r = 0;
    if (d < n) {
        u8* e = pb + 4 + (u32)d * 2;
        r = ((u16)e[0] << 8) | e[1];
    }
    return r;
}

// @ 0x008cd520
void Delete_cmapClass(u8* p)
{
    if (p == 0) return;
    for (i32 i = 0; i < (i32)*(s16*)(p + 6); ++i)
        tsi_DeAllocMem(*(void**)p, *(void**)(*(u32*)(p + 0xc) + i * 4));
    tsi_DeAllocMem(*(void**)p, *(void**)(p + 0xc));
    tsi_DeAllocMem(*(void**)p, *(void**)(p + 0x10));
    tsi_DeAllocMem(*(void**)p, p);
}

// @ 0x008cd580
u8* New_kernSubTable0Data(void* mem)
{
    u8* p = (u8*)tsi_AllocMem(mem, 0x10);
    *(u32*)p = (u32)mem;
    Stream* s = *(Stream**)0; // stream is passed in ebx (custom register convention)
    (void)s;
    *(u16*)(p + 4) = (u16)ReadInt16((Stream*)mem);
    *(u16*)(p + 6) = (u16)ReadInt16((Stream*)mem);
    *(u16*)(p + 8) = (u16)ReadInt16((Stream*)mem);
    *(u16*)(p + 0xa) = (u16)ReadInt16((Stream*)mem);
    *(u32*)(p + 0xc) = (u32)tsi_AllocMem(mem, *(u16*)(p + 4) * 8);
    for (i32 i = 0; i < (i32)*(u16*)(p + 4); ++i) {
        *(u32*)(*(u32*)(p + 0xc) + i * 8) = (u32)ReadInt32((Stream*)mem);
        *(u16*)(*(u32*)(p + 0xc) + i * 8 + 4) = (u16)ReadInt16((Stream*)mem);
    }
    return p;
}

// @ 0x008cd610
u16 GetKernSubTable0Value(u8* p, u16 keyhi)
{
    u16 keylo = keyhi; // low half is supplied in dx by the caller (freeType convention)
    u32 want = ((u32)keyhi << 0x10) | (u32)keylo;
    i32 lo = 0;
    i32 hi = (i32)*(u16*)(p + 4) - 1;
    for (;;) {
        i32 mid = (hi + lo) >> 1;
        u32 v = *(u32*)(*(u32*)(p + 0xc) + mid * 8);
        if (want > v)      lo = mid + 1;
        else if (want < v) hi = mid - 1;
        else               return *(u16*)(*(u32*)(p + 0xc) + mid * 8 + 4);
        if (lo > hi) return 0;
    }
}

// @ 0x008cd660
u8* New_kernSubTable(void* mem, i32 flag)
{
    u8* p = (u8*)tsi_AllocMem(mem, 0x14);
    *(u32*)p = (u32)mem;
    *(u32*)(p + 0x10) = 0;
    if (flag != 0) {
        *(u32*)(p + 8) = (u32)ReadInt32((Stream*)mem);
        *(u16*)(p + 0xc) = (u16)ReadInt16((Stream*)mem);
        *(u16*)(p + 4) = *(u16*)(p + 0xc) & 0xff;
        ReadInt16((Stream*)mem);
    } else {
        *(u16*)(p + 4) = (u16)ReadInt16((Stream*)mem);
        *(u32*)(p + 8) = (u32)(u16)ReadInt16((Stream*)mem);
        *(u16*)(p + 0xc) = (u16)ReadInt16((Stream*)mem);
    }
    if (*(u16*)(p + 4) == 0 && *(i32*)(p + 8) > 0)
        *(u32*)(p + 0x10) = (u32)New_kernSubTable0Data(mem);
    return p;
}
