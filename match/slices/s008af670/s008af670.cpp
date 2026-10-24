// Slice s008af670: T2K (Type 2000) glyph decoder -- ReadDeltaXYValue (0x008af670).
// Decodes one compressed delta pair (dx, dy) from the stream; returns the on-curve flag.
// Module flags: /O2 /MD /Gy /TP.
#include "types.h"

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

extern "C" {
void tsi_Error(tsiMemObject* mem, int32 errCode);   // 0x008d10c0
void PrimeT2KInputStream(InputStream* in);          // 0x008cc0b0
void* tsi_AllocMem(tsiMemObject* mem, int32 size);  // 0x008d1260
void tsi_DeAllocMem(tsiMemObject* mem, void* p);    // 0x008d1440
void* tsi_FastAllocN(tsiMemObject* mem, int32 size, int32 zero); // 0x008d14d0
}

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

// ---------------------------------------------------------------------------
// T2K glyph class storage (0x008afd50 .. 0x008b0555)
// ---------------------------------------------------------------------------

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
    int16 cc = (int16)g->contourCount;
    if (cc <= 0 || (int16)g->contourEnds[cc - 1] != pc - 1) {

    glyph_AllocContours(g, (int16)(cc + 2));
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
GlyphClass* New_EmptyGlyph(tsiMemObject* mem, int32 unused, int16 a, int16 b)
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
    pys[3] = pys[2] - b;
    pxs[3] = 0;
    g->pointCount = 0;
    return g;
}
