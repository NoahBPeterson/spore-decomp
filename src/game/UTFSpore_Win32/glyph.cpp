// src/game/UTFSpore_Win32/glyph.cpp -- migrated from slice(s) s008b0560, s008af670 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/glyph.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s008af670 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int32_t int32;
struct tsiMemObject;
typedef int (*PF_READ_TO_RAM)(void* id, uint8* dst, uint32 pos, uint32 n);
struct InputStream {
    uint8* privateBase;            // +0x000
    PF_READ_TO_RAM ReadToRamFunc;  // +0x004
    void* nonRamID;                // +0x008
    uint8 tmp_ch[0x208];           // +0x00c
    uint32 cacheCount;             // +0x214
    uint32 posZero;                // +0x218
    uint32 pos;                    // +0x21c
    uint32 pad220[3];              // +0x220
    tsiMemObject* mem;             // +0x22c
};
extern "C" void tsi_Error(tsiMemObject* mem, int32 errCode);   // 0x008d10c0
extern "C" void PrimeT2KInputStream(InputStream* in);          // 0x008cc0b0
extern "C" void* tsi_AllocMem(tsiMemObject* mem, int32 size);  // 0x008d1260
extern "C" void tsi_DeAllocMem(tsiMemObject* mem, void* p);    // 0x008d1440
extern "C" void* tsi_FastAllocN(tsiMemObject* mem, int32 size, int32 zero); // 0x008d14d0
#define T2K_ERR_TRANS_FAIL 10024
static __forceinline int ReadUnsignedByteSlow(InputStream* in)
{
    int error = in->ReadToRamFunc(in->nonRamID, in->tmp_ch, in->pos++, 1);
    if (error < 0) {
        tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
        return 0;
    }
    return in->tmp_ch[0];
}
#define ReadUnsignedByteMacro2(stream) \
    ((int)(((stream)->pos - (stream)->posZero + 1 > (stream)->cacheCount ? PrimeT2KInputStream(stream) : (void)0), \
             (stream)->privateBase[(stream)->pos++ - (stream)->posZero]))
#define ReadUnsignedByteMacro(stream) \
    ((uint8)((stream)->privateBase != 0 \
                 ? ((stream)->ReadToRamFunc != 0 ? ReadUnsignedByteMacro2(stream) \
                                                 : (stream)->privateBase[(stream)->pos++]) \
                 : ReadUnsignedByteSlow(stream)))
struct GlyphClass;
struct tsiMemObject {
    uint8  pad00[0x50];        // +0x00
    GlyphClass* defGlyph;      // +0x50
    int32* defX;               // +0x54
    uint8  pad58[4];           // +0x58
    void*  defY;               // +0x5c
    uint8  pad60[0x28];        // +0x60
    int32  ownGlyph;           // +0x88
    int32  ownX;               // +0x8c
    uint8  pad90[4];           // +0x90
    int32  ownY;               // +0x94
};
struct GlyphClass {
    tsiMemObject* mem;         // +0x00
    uint16 contourCapacity;    // +0x04
    uint16 pad06;              // +0x06
    int32  pointCapacity;      // +0x08
    int32  field0c;            // +0x0c
    int32  field10;            // +0x10
    uint8  inlineContours[0x20]; // +0x14
    uint16 field34;            // +0x34
    uint16 contourCount;       // +0x36
    uint16 pointCount;         // +0x38
    uint16 pad3a;              // +0x3a
    uint16* contourStarts;     // +0x3c
    uint16* contourEnds;       // +0x40
    int16* xs;                 // +0x44
    int16* ys;                 // +0x48
    uint8* flags;              // +0x4c
    int32* x32;                // +0x50
    int32* y32;                // +0x54
    void*  field58;            // +0x58
    void*  field5c;            // +0x5c
    int32  field60;            // +0x60
    void*  field64;            // +0x64
    int32  field68;            // +0x68
    uint16 field6c;            // +0x6c
    uint16 field6e;            // +0x6e
    uint16 field70;            // +0x70
    uint16 field72;            // +0x72
};
// ---- items of slice s008af670 end

// The T2K slice s008b0560 spells the same retail InputStream struct with other member names (readToRam, tmp_ch,
// bytesLeft, maxPos, posZero2, ctorType); its stub is renamed InputStream_s008b_0560, so its verbatim body reaches the
// TU's InputStream through this alias (same layout, 0x000..0x22c).
typedef InputStream InputStreamGlyph;

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void tsi_Error(tsiMemObject* mem, int32 errCode);   // 0x008d10c0
extern "C" void PrimeT2KInputStream(InputStream* in);          // 0x008cc0b0
extern "C" void* tsi_AllocMem(tsiMemObject* mem, int32 size);  // 0x008d1260
extern "C" void tsi_DeAllocMem(tsiMemObject* mem, void* p);    // 0x008d1440
extern "C" void* tsi_FastAllocN(tsiMemObject* mem, int32 size, int32 zero); // 0x008d14d0

// ---- items of slice s008b0560 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct InputStream_s008b_0560;
extern "C" void*  tsi_ReAllocMem(tsiMemObject* mem, void* p, int32 size);     // 0x008d1330
extern "C" int16  ReadInt16(InputStream_s008b_0560* in);                                 // 0x008cc190
struct InputStream_s008b_0560 {
    uint8*         privateBase;   // 0x000
    PF_READ_TO_RAM readToRam;     // 0x004
    void*          nonRamID;      // 0x008
    uint8          tmp_ch;        // 0x00c  one-byte staging area for readToRam
    uint8          pad00d[0x210 - 0x00d];
    uint32         bytesLeft;     // 0x210
    uint32         cacheCount;    // 0x214
    uint32         posZero;       // 0x218
    uint32         pos;           // 0x21c
    uint32         maxPos;        // 0x220
    uint32         posZero2;      // 0x224
    int            ctorType;      // 0x228
    tsiMemObject*  mem;           // 0x22c
};
struct GlyphClass_s008b_0560 {
    tsiMemObject* mem;            // 0x00
    uint16        w04;            // 0x04  T2K: point count
    uint16        pad06;
    uint32        w08;            // 0x08  T2K: number of contours (state: "has coords")
    uint32        d0c;            // 0x0c  composite record pointer (small glyphs)
    uint32        d10;            // 0x10  composite record end   (small glyphs)
    char          pad14[0x34 - 0x14];
    uint16        tag34;          // 0x34  glyph kind (3 for T2K glyphs)
    uint16        compFlag;       // 0x36  < 0 => composite
    uint16        contour;        // 0x38  current contour index
    uint16        pad3a;
    uint32        d3c;            // 0x3c  contour-offset table / composite record pointer
    uint32        d40;            // 0x40  contour-end table
    uint32        d44;            // 0x44  x array pointer
    uint32        d48;            // 0x48  y array pointer
    uint32        d4c;            // 0x4c  per-point tag array
    uint32        d50;            // 0x50  packed component blob
    uint32        d54;            // 0x54  end of the packed component blob
    uint32        d58;            // 0x58  decoded components
    uint32        d5c;            // 0x5c
    uint32        d60;            // 0x60  component capacity
    char          pad64[0x68 - 0x64];
    uint32        d68;            // 0x68  component count
    int16         cnt6c;          // 0x6c
    int16         cnt6e;          // 0x6e
    uint16        w70;            // 0x70  min x of the point set
    uint16        w72;            // 0x72  max y of the point set
    uint8         b74;            // 0x74
};
// ---- items of slice s008b0560 end

// @ 0x008af670
uint32 ReadDeltaXYValue(InputStream* in, int16* dx, int16* dy)
{
    uint32 value = ReadUnsignedByteMacro(in) << 8;
    value |= ReadUnsignedByteMacro(in);
    int code = (int)(value >> 14);
    value &= 0x3fff;
    uint32 x, y;
    if (value < 0x898) {
        if (value == 0 && code <= 1) {
            uint16 a = (uint16)(ReadUnsignedByteMacro(in) << 8);
            a |= ReadUnsignedByteMacro(in);
            uint16 b = (uint16)(ReadUnsignedByteMacro(in) << 8);
            b |= ReadUnsignedByteMacro(in);
            *dx = (int16)a;
            *dy = (int16)b;
            return code == 0;
        }
        x = value;
        y = 0;
    }
    else if (value < 0x313c) {
        value -= 0x898;
        x = (int16)value / 0x66 + 1;
        y = (int16)value % 0x66 + 1;
    }
    else if (value < 0x393c) {
        uint32 v = (value - 0x313c) << 8;
        v |= ReadUnsignedByteMacro(in);
        x = v / 0x2d4 + 1;
        y = v % 0x2d4 + 1;
    }
    else {
        uint32 v = (value - 0x393c) << 8;
        v |= ReadUnsignedByteMacro(in);
        v <<= 8;
        v |= ReadUnsignedByteMacro(in);
        x = v / 0x299a;
        y = v % 0x299a;
    }
    int32 ry = 0;
    int32 rx = 0;
    switch (code) {
    case 0: rx = x; ry = y; break;
    case 1: rx = -(int32)y; ry = x; break;
    case 2: rx = -(int32)x; ry = -(int32)y; break;
    case 3: rx = y; ry = -(int32)x; break;
    }
    *dx = (int16)(rx >> 1);
    *dy = (int16)ry;
    return 1 - (rx & 1);
}

// @ 0x008afd50
void glyph_AllocContours(GlyphClass* g, int16 n)
{
    if ((int16)g->contourCapacity >= n) return;
    g->contourCapacity = (uint16)n;
    uint16* starts = (uint16*)tsi_AllocMem(g->mem, n * 4);
    uint16* ends = starts + n;
    for (int16 i = 0; i < (int16)g->contourCount; i++) {
        starts[i] = g->contourStarts[i];
        ends[i] = g->contourEnds[i];
    }
    if (g->contourStarts != (uint16*)((uint8*)g + 0x14))
        tsi_DeAllocMem(g->mem, g->contourStarts);
    g->contourStarts = starts;
    g->contourEnds = ends;
}

// @ 0x008afde0
void glyph_CloseContour(GlyphClass* g)
{
    if (g->pointCount == 0) return;
    int16 pc = (int16)g->pointCount;
    if ((int16)g->contourCount <= 0 || (int16)g->contourEnds[(int16)g->contourCount - 1] != pc - 1) {
    glyph_AllocContours(g, (int16)((int16)g->contourCount + 2));
    if ((int16)g->pointCount <= 0)
        g->contourEnds[(int16)g->contourCount] = 0;
    else
        g->contourEnds[(int16)g->contourCount] = g->pointCount - 1;
    g->contourCount = g->contourCount + 1;

    int16 acc = 0;
    for (int16 i = 0; i < (int16)g->contourCount; i++) {
        g->contourStarts[i] = acc;
        acc = g->contourEnds[i] + 1;
    }

    if ((int16)g->pointCount > 0) {
        int16 lastStart = (int16)g->contourStarts[(int16)g->contourCount - 1];
        uint16* lastEnd = &g->contourEnds[(int16)g->contourCount - 1];
        int16 e = (int16)*lastEnd;
        if (e > lastStart) {
            if (g->xs[lastStart] == g->xs[e] &&
                g->ys[lastStart] == g->ys[e] &&
                g->flags[lastStart] == g->flags[e]) {
                g->pointCount = g->pointCount - 1;
                *lastEnd = (uint16)(g->pointCount - 1);
            }
        }
    }

    }
}

// @ 0x008afee0
void Add_GlyphClass(GlyphClass** dstp, GlyphClass* src, uint32 flags, int32 px, int32 py)
{
    GlyphClass* d = *dstp;
    if (d == 0) {
        if (flags & 2) {
            if (flags & 4) {
                px = (px + 0x20) & ~0x3f;
                py = (py + 0x20) & ~0x3f;
            }
            if (px != 0 || py != 0) {
                int32 n = (int16)src->pointCount;
                for (int32 i = 0; i < n; i++) {
                    src->x32[i] = src->x32[i] + px;
                    src->y32[i] = src->y32[i] + py;
                }
            }
        }
        *dstp = src;
        return;
    }

    int32 oldPoints = (int16)d->pointCount;
    int32 oldContours = (int16)d->contourCount;
    int32 totalPoints = (int16)src->pointCount + oldPoints;
    int32 totalContours = (int16)src->contourCount + oldContours;
    int32 n = totalPoints + 4;

    uint8* base = (uint8*)tsi_AllocMem(d->mem, n * 0xd);
    int32* nx = (int32*)base;
    int32* ny = (int32*)(base + n * 4);
    int16* nxs = (int16*)(base + n * 8);
    int16* nys = (int16*)(base + n * 10);
    uint8* nfl = (uint8*)(base + n * 12);

    uint16* nc = (uint16*)tsi_AllocMem(d->mem, totalContours * 4);
    uint16* nce = nc + totalContours;

    d->pointCapacity = (int32)(int16)totalPoints;
    d->contourCapacity = (uint16)totalContours;

    for (int32 i = 0; i < (int16)d->pointCount; i++) {
        nx[i] = d->x32[i];
        ny[i] = d->y32[i];
        nfl[i] = d->flags[i];
    }
    if ((flags & 0x200) == 0) {
        nx[totalPoints] = d->x32[oldPoints];
        ny[totalPoints] = d->y32[oldPoints];
        nx[totalPoints + 1] = d->x32[oldPoints + 1];
        ny[totalPoints + 1] = d->y32[oldPoints + 1];
    }

    int32 ox, oy;
    if ((flags & 2) == 0) {
        ox = d->x32[px] - src->x32[py];
        oy = d->y32[px] - src->y32[py];
    }
    else {
        ox = px;
        oy = py;
        if (flags & 4) {
            ox = (px + 0x20) & ~0x3f;
            oy = (py + 0x20) & ~0x3f;
        }
    }

    int32 si = 0;
    for (int32 i = (int16)d->pointCount; i < totalPoints; i++) {
        nx[i] = src->x32[si] + ox;
        ny[i] = src->y32[si] + oy;
        nfl[i] = src->flags[si];
        si++;
    }

    for (int32 i = 0; i < (int16)d->contourCount; i++) {
        nc[i] = d->contourStarts[i];
        nce[i] = d->contourEnds[i];
    }
    int32 extra = totalContours - (int16)d->contourCount;
    int32 ci = 0;
    for (; extra != 0; extra--) {
        nc[(int16)d->contourCount + ci] = src->contourStarts[ci] + oldPoints;
        nce[(int16)d->contourCount + ci] = src->contourEnds[ci] + oldPoints;
        ci++;
    }

    if (d->x32 == d->mem->defX)
        d->mem->ownX = 1;
    else
        tsi_DeAllocMem(d->mem, d->x32);
    if (d->contourStarts != (uint16*)((uint8*)d + 0x14))
        tsi_DeAllocMem(d->mem, d->contourStarts);

    d->x32 = nx;
    d->y32 = ny;
    d->xs = nxs;
    d->ys = nys;
    d->flags = nfl;
    d->contourStarts = nc;
    d->contourEnds = nce;
    d->field34 = src->field34;
    d->pointCount = (uint16)totalPoints;
    d->contourCount = (uint16)totalContours;
}

// @ 0x008b0230
void AllocGlyphPointMemory(GlyphClass* g, int32 cap)
{
    int32 n = cap + 4;
    int32* p = (int32*)tsi_FastAllocN(g->mem, n * 0xd, 1);
    g->x32 = p;
    p += n;
    g->y32 = p;
    p += n;
    int16* q = (int16*)p;
    g->xs = q;
    q += n;
    g->pointCapacity = cap;
    g->ys = q;
    g->flags = (uint8*)(q + n);
}

// @ 0x008b0280
void Delete_GlyphClass(GlyphClass* g)
{
    if (g == 0) return;
    if (g->x32 == g->mem->defX)
        g->mem->ownX = 1;
    else
        tsi_DeAllocMem(g->mem, g->x32);
    if (g->contourStarts != (uint16*)((uint8*)g + 0x14))
        tsi_DeAllocMem(g->mem, g->contourStarts);
    if (g->field64 == g->mem->defY)
        g->mem->ownY = 1;
    else
        tsi_DeAllocMem(g->mem, g->field64);
    tsi_DeAllocMem(g->mem, g->field58);
    if (g == g->mem->defGlyph) {
        g->mem->ownGlyph = 1;
        return;
    }
    tsi_DeAllocMem(g->mem, g);
}

// @ 0x008b0320
void glyph_AddPoint(GlyphClass* g, int32 x, int32 y, uint8 flag)
{
    if ((int16)g->pointCount >= g->pointCapacity) {
        int32 oldCap = g->pointCapacity;
        int32* oldX = g->x32;
        int16* oldXs = g->xs;
        int16* oldYs = g->ys;
        uint8* oldF = g->flags;
        int32 newCap = oldCap + oldCap / 2 + 0x20;
        int32 n = newCap + 4;
        int32* p = (int32*)tsi_FastAllocN(g->mem, n * 0xd, 1);
        g->x32 = p;
        p += n;
        g->y32 = p;
        p += n;
        int16* nxs = (int16*)p;
        g->xs = nxs;
        nxs += n;
        int16* nys = nxs;
        g->ys = nys;
        uint8* nfl = (uint8*)(nys + n);
        g->flags = nfl;
        g->pointCapacity = newCap;

        int32 cnt = (int16)g->pointCount + 4;
        for (int32 i = 0; i < cnt; i++) {
            nxs[i] = oldXs[i];
            nys[i] = oldYs[i];
            nfl[i] = oldF[i];
        }
        if (oldX == g->mem->defX)
            g->mem->ownX = 1;
        else
            tsi_DeAllocMem(g->mem, oldX);
    }
    int32 i = (int16)g->pointCount;
    g->xs[i] = (int16)x;
    g->ys[i] = (int16)y;
    g->flags[i] = flag;
    g->pointCount = (uint16)(i + 1);
}

// @ 0x008b0440
void glyph_StartLine(GlyphClass* g, int32 x, int32 y)
{
    int32 i = (int16)g->pointCount - 1;
    if (i < 0 || g->xs[i] != x || g->ys[i] != y)
        glyph_AddPoint(g, x, y, 1);
}

// @ 0x008b0480
GlyphClass* New_EmptyGlyph(tsiMemObject* mem, int32 unused, int16 a, int16 b, int16 c)
{
    GlyphClass* g = (GlyphClass*)tsi_FastAllocN(mem, 0x78, 0);
    g->field34 = 2;
    g->mem = mem;
    g->contourEnds = 0;
    g->contourStarts = 0;
    g->field58 = 0;
    g->y32 = 0;
    g->x32 = 0;
    g->field0c = 0;
    g->field10 = 0;
    g->contourCapacity = 0;
    g->pointCapacity = 0;
    g->field60 = 0;
    g->contourCount = 0;
    g->field6c = 0;
    g->field6e = 0;
    g->field70 = 0;
    g->field72 = 0;
    g->field5c = 0;
    g->field68 = 0;
    g->field64 = 0;

    uint8* p = (uint8*)tsi_FastAllocN(mem, 0x34, 1);
    g->x32 = (int32*)p;
    p += 0x10;
    g->y32 = (int32*)p;
    p += 0x10;
    int16* pxs = (int16*)p;
    int16* pys = (int16*)(p + 8);
    g->xs = pxs;
    g->ys = pys;
    g->pointCapacity = 0;
    g->flags = (uint8*)(pys + 4);

    pys[0] = 0;
    pxs[0] = 0;
    pys[1] = 0;
    pxs[1] = pxs[0] + a;
    pys[2] = g->field72 + b;
    pxs[2] = 0;
    pys[3] = pys[2] - c;
    pxs[3] = 0;
    g->pointCount = 0;
    return g;
}

// @ 0x008b0560
extern "C" GlyphClass_s008b_0560* New_GlyphClassT2K(tsiMemObject* mem, InputStream_s008b_0560* in, uint32 a3, int16 lsb, int16 adv, int16 tsb, int16 adv2)
{
    GlyphClass_s008b_0560* g = (GlyphClass_s008b_0560*)tsi_FastAllocN(mem, 0x78, 0);
    g->mem = mem;
    g->d68 = 0;
    g->d3c = 0;
    g->d58 = 0;
    g->d54 = 0;
    g->d50 = 0;
    g->d0c = 0;
    g->d10 = 0;
    g->tag34 = 3;
    g->w04 = 0;
    g->w08 = 0;

    int16 contourDelta = ReadInt16(in);
    g->compFlag = contourDelta;
    g->cnt6c = 0;
    g->cnt6e = 0;
    g->w70 = 0;
    g->w72 = 0;
    g->d5c = 0;
    g->d68 = 0;
    g->d60 = 0;

    uint32 nAll = 0;        // points already in the arrays (also the phantom index)
    uint32 limit;           // packed-blob capacity (composite) or nPts (simple)

    if (contourDelta < 0) {
        // ---- composite glyph: the point deltas are packed back to front ----
        g->d60 = 0x400;
        int16* buf = (int16*)tsi_AllocMem(mem, 0x800);
        uint16 f;
        do {
            if ((int)g->d60 <= (int)nAll + 10) {
                g->d60 = g->d60 / 2 + g->d60;
                buf = (int16*)tsi_ReAllocMem(mem, buf, g->d60 * 2);
            }
            f = (uint16)ReadInt16(in);
            buf[nAll] = (int16)f;
            nAll++;
            buf[nAll] = ReadInt16(in);
            nAll++;
            if (f & 1)
                buf[nAll++] = ReadInt16(in);
            buf[nAll++] = ReadInt16(in);
            if (f & 8) {
                buf[nAll++] = ReadInt16(in);
            } else if (f & 0x40) {
                buf[nAll++] = ReadInt16(in);
            } else if (f & 0x80) {
                buf[nAll++] = ReadInt16(in);
                buf[nAll++] = ReadInt16(in);
                buf[nAll++] = ReadInt16(in);
            }
            if (f & 0x20)
                continue;
            break;
        } while (true);

        limit = 0;
        g->d68 = 0;
        uint32 m = (uint32)tsi_FastAllocN(mem, 0x34, 1);
        g->d50 = m;
        g->d54 = m + 0x10;
        g->d3c = m + 0x10;
        g->d44 = m + 0x20;
        g->d48 = m + 0x28;
        g->d4c = m + 0x30;
        g->d58 = (uint32)buf;
        g->d5c = nAll;
    } else if (contourDelta > 0) {
        // ---- simple glyph: cumulative contour ends ----
        int total = 0;
        int16* tbl;
        if (contourDelta <= 8) {
            g->d3c = (uint32)((char*)g + 0x44);
            tbl = (int16*)((char*)g + 0x50);
        } else {
            tbl = (int16*)tsi_AllocMem(mem, contourDelta * 4);
            g->d3c = (uint32)tbl;
            tbl = (int16*)((char*)tbl + contourDelta * 2);
        }
        int16* pEnd = tbl;
        for (int i = 0; i < contourDelta; i++) {
            *(int16*)((char*)g->d3c + i * 2) = (int16)total;
            total = (int16)(pEnd[i] + total);
            pEnd[i] = (int16)(total + 1);
            total++;
        }
        int nPts = total;
        int stride = nPts + 4;
        limit = (uint32)nPts;
        g->d68 = 0;
        char* m = (char*)tsi_FastAllocN(mem, stride * 0xd, 1);
        g->d50 = (uint32)m;
        g->d54 = (uint32)(m + stride * 4);
        g->d3c = (uint32)(m + stride * 4);
        g->d44 = (uint32)(m + stride * 8);
        g->d48 = (uint32)(m + stride * 0xa);
        g->d4c = (uint32)(m + stride * 0xc);
        g->w04 = g->compFlag;
        g->w08 = g->compFlag;
        int16 minX = 0x7fff;
        int16 maxY = (int16)0x8001;
        int16* pX = (int16*)g->d44;
        int16* pY = (int16*)g->d48;
        int16* pT = (int16*)g->d4c;
        int xAcc = 0;
        int yAcc = 0;
        for (int i = 0; i < nPts; i++) {
            int16 dx, dy;
            uint8 t = (uint8)ReadDeltaXYValue((InputStreamGlyph*)in, &dx, &dy);
            xAcc += dx;
            yAcc += dy;
            pT[i] = t;
            if ((int16)xAcc < minX)
                minX = (int16)xAcc;
            if ((int16)yAcc > maxY)
                maxY = (int16)yAcc;
            pX[i] = (int16)xAcc;
            pY[i] = (int16)yAcc;
        }
        g->w70 = (uint16)minX;
        g->w72 = (uint16)maxY;
    } else {
        // ---- empty glyph ----
        limit = 0;
        g->d3c = 0;
        g->w08 = 0;
    }

    if (contourDelta <= 0) {
        // composite / empty: the four phantom points live in the packed blob
        uint32 m = g->d50;
        uint32 e = g->d54;
        int16* pp = (int16*)(m + 4);
        pp[0] = (int16)(g->w70 - lsb);
        pp[1] = (int16)(pp[0] + adv);
        int mid = ((int)pp[0] + (int)pp[1]) >> 1;
        *(int16*)(m + 2) = 0;
        *(int16*)(m + 4 + 4) = (int16)(g->w72 + tsb);
        *(int16*)(e) = (int16)(g->w72 + tsb - adv2);
        *(int16*)(e + 2) = (int16)mid;
        *(int16*)(e + 4) = (int16)mid;
        g->contour = (uint16)nAll;
        return g;
    }

    // simple glyph: the four phantom points follow the real points
    int16* pX = (int16*)(g->d44 + nAll * 2);
    int16* pY = (int16*)(g->d48 + nAll * 2);
    char*  pT = (char*)g->d4c + nAll * 2;
    *(int16*)(g->d58 + nAll * 2) = 0;
    pX[1] = (int16)(g->w70 - lsb);
    pT[2] = 0;
    int16 v = pX[1];
    pX[2] = (int16)(v + adv);
    pT[4] = (int16)(g->w72 + tsb);
    int mid = ((int)v + (int)pX[2]) >> 1;
    pT[6] = (int16)(pT[4] - adv2);
    pT[8] = (int16)mid;
    pT[10] = (int16)mid;
    g->contour = (uint16)limit;
    g->d54 = g->d58;
    return g;
}
