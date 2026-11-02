// src/game/UTFSpore_Win32/pfrread.cpp -- migrated from slice(s) s008b4cc0, s008b3040, s008b0560, s008b3ae0, s008b2250 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/pfrread.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s008b2250 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cNibbleReader {
public:
    const uint8_t* mpCursor;   // +0x00
    uint16_t mHalf;            // +0x04

    uint16_t ReadPacked();     // 0x008b2b30 (thiscall, no args)
};
// ---- items of slice s008b2250 end

// ---- items of slice s008b3ae0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int   util_FixMul(int a, int b);                                    // 0x008d1590
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef uint32_t uint32;
struct tsiMemObject;
struct InputStream;
struct PFRClass;
extern "C" void* tsi_AllocMem(tsiMemObject* mem, uint32 size);                 // 0x008d1260
extern "C" void  tsi_DeAllocMem(tsiMemObject* mem, void* p);                   // 0x008d1440
extern "C" void* tsi_ReAllocMem(tsiMemObject* mem, void* p, uint32 size);      // 0x008d1330
extern "C" void  Seek_InputStream(InputStream* in, int pos);                   // 0x008cc580
extern "C" void  PeekInt16(InputStream* in, void* dst, int n);                 // 0x008cc220
struct GlyphBuilder { char pad[0x38]; int16 contour; };
extern "C" void glyph_AddPoint(GlyphBuilder* g, int x, int y, int onCurve);    // 0x008b0320
extern "C" void glyph_CloseContour(GlyphBuilder* g);                           // 0x008afde0
struct PFROutline {
    tsiMemObject* mem;           // 0x000
    char   pad4[0x2c0 - 4];
    int16* xAll;                 // 0x2c0  per-point tags for x set (indexed cntXPts + cntXSet)
    int16  capXAll, pad2c6;      // 0x2c4
    int16* yAll;                 // 0x2c8
    int16  capYAll, pad2ce;      // 0x2cc
    int16* xSetArr;              // 0x2d0
    int16  capXSet, cntXSet;     // 0x2d4, 0x2d6
    int16* ySetArr;              // 0x2d8
    int16  capYSet, cntYSet;     // 0x2dc, 0x2de
    int16* xPts;                 // 0x2e0
    int16  capXPts, cntXPts;     // 0x2e4, 0x2e6
    int16* yPts;                 // 0x2e8
    int16  capYPts, cntYPts;     // 0x2ec, 0x2ee
    char   pad2f0[0x34c - 0x2f0];
    int16  numChars;             // 0x34c
};
struct PFRClass {
    tsiMemObject* mem;           // 0x00
    InputStream*  stream;        // 0x04
    uint8  ver;                  // 0x08
    char   pad09[0x28 - 9];
    int    f28;                  // 0x28
    int    dataBase;             // 0x2c
    char   pad30[4];
    uint8  inContour;            // 0x34
    char   pad35[0xb4 - 0x35];
    int    fb4;                  // 0xb4
    char   padb8[0xe0 - 0xb8];
    int    m[6];                 // 0xe0 transform: m0 m1 m2 m3 tx ty
    char   pade8[0xfc - 0xf8];
    GlyphBuilder* glyph;         // 0xfc
};
struct PFRPts {
    int16 nx;  int16 xs[64];     // 0x000
    int16 ny;  int16 ys[64];     // 0x082
    int16 curX, curY;            // 0x104
    int16 w4, w2;                // 0x108
};
struct PFRState { uint8* cur; int16 flag; };   // command stream cursor for FUN_008b3680
struct PFRRec { int v[4]; int offset; uint32 size; };   // component record / saved matrix
extern "C" void FUN_008b2630(PFRClass* pfr, uint8** cursor, PFRRec* out, int* scratch);          // 0x008b2630
extern "C" void FUN_008b0920(PFRClass* pfr, uint8 flags, uint8** cursor, PFRPts* pts);          // 0x008b0920
extern "C" void FUN_008b0f10(uint8** cursor, uint32 flags, PFRPts* pts, uint32* a, uint32* b);   // 0x008b0f10
extern "C" void FUN_008b3390(PFROutline* o, PFRClass* pfr, uint8** extra);                       // 0x008b3390 (eax = o)
extern "C" void FUN_008b3680(PFRPts* pts, PFRState* st, int16* out, int* type);                  // 0x008b3680 (ecx/eax/edi)
extern "C" void SetupTrans(PFRClass* pfr, int sx, int sy, int tx, int ty);                       // 0x008b1db0 (ecx=tx eax=ty)
extern "C" void TransformPoint(PFRClass* pfr, int x, int y, int* ox, int* oy);                   // 0x008b1e60 (eax = x)
static inline void Xf(PFRClass* c, int x, int y, int* ox, int* oy)
{
    int a = util_FixMul(y << 16, c->m[2]);
    a += util_FixMul(x << 16, c->m[0]);
    int b = util_FixMul(x << 16, c->m[1]);
    int d = util_FixMul(y << 16, c->m[3]);
    *ox = a + c->m[4];
    *oy = c->m[5] + b + d;
}
static inline uint8* SkipItems(uint8* cur, uint32 n)
{
    for (; n != 0; --n) cur += *cur + 2;
    return cur;
}
// ---- items of slice s008b3ae0 end

// ---- items of slice s008b0560 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int8_t   int8;
typedef int32_t  int32;
struct T2KPointSet {
    uint16  nx;                   // 0x00
    int16   xs[0x40];             // 0x02
    uint16  ny;                   // 0x82
    int16   ys[0x40];             // 0x84
    int16   curX;                 // 0x104
    int16   curY;                 // 0x106
    uint16  out1;                 // 0x108  written as ushort, read as the u16 at 0x82
    uint16  out0;                 // 0x10a  written as ushort, read as the u16 at 0x84
    uint8*  outCursor;            // 0x10c
};
struct NibSrcTC {
    uint8* cur;                    // 0x00
    uint16 half;                   // 0x04
    uint8 ReadHi();                // 0x008b1040
};
struct PFRKernSubTable {
    tsiMemObject* mem;            // 0x00
    uint16        count;          // 0x04
    uint16        f06;            // 0x06
    uint16        f08;            // 0x08
    uint16        f0a;            // 0x0a
    uint32*       entries;        // 0x0c  count * 8 bytes of packed entries
};
// ---- items of slice s008b0560 end

// ---- items of slice s008b3040 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char uint8_s008b_3040;
typedef unsigned short uint16_s008b_3040;
typedef short int16_s008b_3040;
typedef unsigned int uint;
typedef unsigned int uint32_s008b_3040;
struct GlyphBuilder_s008b_3040 { char pad[0x38]; int16_s008b_3040 contour; };
struct PFROutline_s008b_3040 {
    tsiMemObject* mem;           // 0x000
    char   pad4[0xfc - 4];
    GlyphBuilder_s008b_3040* glyph;         // 0x0fc
    char   pad100[0x34e - 0x100];
    int16_s008b_3040  cntEdges;             // 0x34e
    int16_s008b_3040  capY;                 // 0x350
    int16_s008b_3040  capX;                 // 0x352
    int16_s008b_3040  cntXSet;              // 0x354
    char   pad356[2];
    int16_s008b_3040* xAll;                 // 0x358
    int16_s008b_3040* xPts;                 // 0x35c
    int16_s008b_3040* xSetArr;              // 0x360
    int16_s008b_3040* xExtra;               // 0x364
    int16_s008b_3040* yAll;                 // 0x368
    int16_s008b_3040* yPts;                 // 0x36c
    int16_s008b_3040* ySetArr;              // 0x370
    int16_s008b_3040* yExtra;               // 0x374
};
struct PFRClass_s008b_3040 {
    tsiMemObject* mem;           // 0x00
    InputStream*  stream;        // 0x04
    uint8_s008b_3040  ver;                  // 0x08
    char   pad09[0x28 - 9];
    int    f28;                  // 0x28
    int    dataBase;             // 0x2c
    char   pad30[4];
    uint8_s008b_3040  inContour;            // 0x34
    char   pad35[0xb4 - 0x35];
    int    fb4;                  // 0xb4
    char   padb8[0xe0 - 0xb8];
    int    m[6];                 // 0xe0 transform: m0 m1 m2 m3 tx ty
    char   pade8[0xfc - 0xf8];
    GlyphBuilder_s008b_3040* glyph;         // 0xfc
};
struct PFRRec_s008b_3040 {
    char   pad00[0x40];
    int16_s008b_3040  x;                    // 0x40
    int16_s008b_3040  y;                    // 0x44
    int16_s008b_3040  z;                    // 0x46
    int    f48;                  // 0x48
    int    f4c;                  // 0x4c
    int    f50;                  // 0x50
    int    f54;                  // 0x54
    int    f58;                  // 0x58
    int    f5c;                  // 0x5c
    int    f60;                  // 0x60
    int    f64;                  // 0x64
    int    f68;                  // 0x68
    char   pad6c[4];
    void*  buf70;                // 0x70
    uint16_s008b_3040 size74;               // 0x74
    char   pad76[2];
    int    off78;                // 0x78
    void*  buf7c;                // 0x7c
};
extern "C" void ProcessExtraStrokes(PFROutline_s008b_3040* o, uint8_s008b_3040* data);               // 0x008b2da0 (eax = o)
extern "C" void ProcessExtraEdgesHints(PFROutline_s008b_3040* o, uint8_s008b_3040* data);            // 0x008b3040 (eax = o)
extern "C" void ProcessExtraHints(void* self, PFROutline_s008b_3040* o, uint8_s008b_3040** cursor);  // 0x008b3390 (eax = self)
extern "C" int   TransformPoint_s008b_3040(int x, int* ox, int* oy);                      // 0x008b1e60 (x in eax)
extern "C" int   FindCharIndex(PFRClass_s008b_3040* pfr, int16_s008b_3040 key, int16_s008b_3040* out);          // 0x008b1c70 (obj in eax, key in edi)
extern "C" int16_s008b_3040 AddPointRange(PFRClass_s008b_3040* pfr, int16_s008b_3040 a, int16_s008b_3040 b, int16_s008b_3040 e, int16_s008b_3040 f); // 0x008b20b0 (ecx = this)
extern "C" void  FUN_008b2250(PFRClass_s008b_3040* pfr, int a, int b, int c);             // 0x008b2250
// ---- items of slice s008b3040 end

// ---- items of slice s008b4cc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char uint8_s008b_4cc0;
typedef unsigned short uint16_s008b_4cc0;
typedef short int16_s008b_4cc0;
typedef unsigned int uint32_s008b_4cc0;
typedef int int32_s008b_4cc0;
struct PFRGlyph {
    char      pad00[0x34];
    int16_s008b_4cc0     w34;                 // 0x34  command/contour tag
    int16_s008b_4cc0     w36;                 // 0x36  open-contour flag
    int16_s008b_4cc0     cnt;                 // 0x38  point count
    char      pad3a[0x44 - 0x3a];
    int16_s008b_4cc0*    px;                  // 0x44  x coordinate array
    int16_s008b_4cc0*    py;                  // 0x48  y coordinate array
};
struct HRec {
    int FUN_008b19e0(void* h24, int id, int16_s008b_4cc0* a, int16_s008b_4cc0* b, int16_s008b_4cc0* c); // 0x008b19e0
};
extern "C" void     Delete_GlyphClass(PFRGlyph* g);                               // 0x008b0280
struct PFRClass_s008b_4cc0;
extern "C" void     FUN_008b1c70(PFRClass_s008b_4cc0* o, int key, int16_s008b_4cc0* out);               // 0x008b1c70
static int16_s008b_4cc0 g_foundKey = 0;
static uint  FoundIdx() { return (uint)(uint16_s008b_4cc0)g_foundKey; }
static uint16_s008b_4cc0 KeyIdx()  { return (uint16_s008b_4cc0)g_foundKey; }
struct PFRClass_s008b_4cc0 {
    tsiMemObject* mem;             // 0x00
    InputStream*  stream;          // 0x04
    char          pad08[0x0c - 0x08];
    char*         charTable;       // 0x0c  entries of 8 bytes: [+2] size, [+4] offset
    char          pad10[0x1c - 0x10];
    uint8_s008b_4cc0         b1c;             // 0x1c  char-code signedness / vertical flag
    char          pad1d[0x2c - 0x1d];
    uint32_s008b_4cc0        baseOff;         // 0x2c  added to each char offset
    char          pad30[0x34 - 0x30];
    uint8_s008b_4cc0         inContour;       // 0x34  a contour is currently open
    char          pad35[0x90 - 0x35];
    uint32_s008b_4cc0        metX;            // 0x90
    uint32_s008b_4cc0        metY;            // 0x94
    char          pad98[0xa6 - 0x98];
    int16_s008b_4cc0         haveChar;        // 0xa6
    char          pada8[0xac - 0xa8];
    uint8_s008b_4cc0         fAc;             // 0xac
    uint8_s008b_4cc0         fAd;             // 0xad
    char          padae[0xfc - 0xae];
    PFRGlyph*     glyph;           // 0xfc  current glyph (FUN_008b0480 result)
    char          pad100[0x104 - 0x100];
    char*         metricsTable;    // 0x104  [+0x10] -> uint16 per char index
    int16_s008b_4cc0         numChars;        // 0x108
    char          pad10a[0x10c - 0x10a];
    uint16_s008b_4cc0        width;           // 0x10c
    // BuildPFRMetricsEtc (0x008b4f00) reads 0x108/0x10c as 32-bit ints.
    uint32_s008b_4cc0        f110;            // 0x110
    int32_s008b_4cc0         f114;            // 0x114
    int32_s008b_4cc0         f118;            // 0x118
    int32_s008b_4cc0         f11c;            // 0x11c
    int32_s008b_4cc0         f120;            // 0x120
    uint32_s008b_4cc0        f124;            // 0x124
    char          pad128[0x1ec - 0x128];
    uint32_s008b_4cc0        f1ec;            // 0x1ec
};
extern "C" PFRGlyph* FUN_008b0480(tsiMemObject* mem, int, int, int, int);
// ---- items of slice s008b4cc0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
extern "C" int FUN_008b4cc0(PFRClass_s008b_4cc0* o, uint16_s008b_4cc0 idx, int16_s008b_4cc0* outW, uint16_s008b_4cc0* outH, int reserved);  // 0x008b4cc0 (stays in the slice: not this object's)

// @ 0x008b0f10
extern "C" void tsi_ReadGlyphCoord(uint8** cursor, uint8 sel, T2KPointSet* pts, int16* outA, int16* outB)
{
    uint8* cur = *cursor;
    switch (sel & 3) {
    case 0:
        *outA = pts->xs[*cur];
        cur++;
        break;
    case 1:
        *outA = (int16)(*cur * 0x100 + cur[1]);
        cur += 2;
        break;
    case 2:
        *outA = (int16)((int16)(int8)*cur + pts->curX);
        cur++;
        break;
    case 3:
        *outA = pts->curX;
        break;
    }
    pts->curX = *outA;

    switch ((sel >> 2) & 3) {
    case 0:
        *outB = pts->ys[*cur];
        pts->curY = *outB;
        cur++;
        break;
    case 1:
        *outB = (int16)(*cur * 0x100 + cur[1]);
        pts->curY = *outB;
        cur += 2;
        break;
    case 2:
        *outB = (int16)((int16)(int8)*cur + pts->curY);
        pts->curY = *outB;
        cur++;
        break;
    case 3:
        *outB = pts->curY;
        pts->curY = *outB;
        break;
    }
    *cursor = cur;
}

// @ 0x008b1040
uint8 NibSrcTC::ReadHi()
{
    if (half == 0) {
        half = 1;
        return *cur >> 4;
    }
    half = 0;
    uint8 v = (uint8)(*cur & 0xf);
    cur = cur + 1;
    return v;
}

// @ 0x008b10a0
static int FindCoordIndex(T2KPointSet* pts, int dirHint, int16 useY)
{
    int16* arr;
    int    count;
    int    ref;
    int    acc;
    if (useY == 0) {
        arr   = pts->xs;
        count = (uint16)pts->nx;
        ref   = (uint16)pts->out1;
        acc   = (uint16)pts->curX;
    } else {
        arr   = pts->ys;
        count = (uint16)pts->ny;
        ref   = (uint16)pts->out0;
        acc   = (uint16)pts->curY;
    }

    int dir = (int16)dirHint;
    if (dir == 0) {
        if ((int16)acc > (int16)ref)
            dir = 1;
        else if ((int16)acc < (int16)ref)
            dir = -1;
        else
            return acc;
    }

    if (dir > 0) {
        for (int i = 0; i < (int16)count; i++) {
            if (arr[i] > (int16)acc) {
                int idx = i + dir - 1;
                if (idx >= (int16)count)
                    idx = count - 1;
                return arr[idx];
            }
        }
        return acc;
    }

    for (int i = (int16)count - 1; i >= 0; i--) {
        if (arr[i] < (int16)acc) {
            int idx = i + dir + 1;
            if (idx < 0)
                idx = 0;
            return arr[idx];
        }
    }
    return acc;
}

// @ 0x008b12e0
extern "C" PFRKernSubTable* New_pfrkernSubTable0Data(uint8* data, tsiMemObject* mem, uint16 firstChar)
{
    PFRKernSubTable* kt = (PFRKernSubTable*)tsi_AllocMem(mem, 0x10);
    uint8* p;
    uint16 count = 0;
    uint16 entryIdx = 0;
    uint16 next;

    p = data;
    do {
        p += (int16)firstChar;
        count = (uint16)(count + *p);
        next = *(uint16*)(p + 1);
        p += 3;
        firstChar = next;
    } while (next == 4);

    kt->mem = mem;
    kt->count = count;
    kt->entries = (uint32*)tsi_AllocMem(mem, count * 8);

    do {
        uint8 nb = p[0];
        uint16 groupStart = entryIdx;
        uint16 groupEnd = (uint16)(groupStart + nb);
        uint8 pack = p[3];
        kt->f06 = 0;
        kt->f08 = 0;
        kt->f0a = 0;
        p += 4;
        for (; groupStart < groupEnd; entryIdx++, groupStart++) {
            uint16 v1, v2;
            if ((pack & 1) == 0) {
                v1 = (uint16)(p[0] * 0x100 + p[1]);
                p += 2;
                v2 = (uint16)(p[0] * 0x100 + p[1]);
                p += 2;
            } else {
                v1 = (uint16)(p[0] * 0x100 + p[1]);
                v2 = (uint16)(p[2] * 0x100 + p[3]);
                p += 4;
            }
            kt->entries[entryIdx] = ((uint32)v1 << 16) | v2;
        }
        next = *(uint16*)(p + 1);
        p += 2;
    } while (next == 4);
    return kt;
}

// @ 0x008b2b30
uint16_t cNibbleReader::ReadPacked()
{
    uint16_t half = mHalf;
    const uint8_t* p;
    uint8_t b;
    if (half == 0) {
        p = mpCursor;
        b = *p;
        p = p + 1;
        mpCursor = p;
    } else {
        p = mpCursor;
        uint8_t a = *p;
        p = p + 1;
        mpCursor = p;
        b = (uint8_t)((a << 4) + (p[0] >> 4));
    }
    int32_t hi = (int8_t)b;
    uint16_t v;
    if (half == 0) {
        mHalf = 1;
        v = (uint16_t)(hi << 4);
        v = (uint16_t)(v + (p[0] >> 4));
    } else {
        mHalf = 0;
        v = (uint16_t)(hi << 4);
        v = (uint16_t)(v + (p[0] & 0xf));
        p = p + 1;
        mpCursor = p;
    }
    uint16_t result = v;
    if ((uint16_t)(v + 0x80) <= 0xff) {
        if (mHalf == 0) {
            int16_t lo = (int8_t)*mpCursor;
            mpCursor = mpCursor + 1;
            result = (uint16_t)((v << 8) + lo);
        } else {
            uint8_t a = mpCursor[0];
            mpCursor = mpCursor + 1;
            int16_t lo = (int8_t)((a << 4) + (mpCursor[0] >> 4));
            result = (uint16_t)((v << 8) + lo);
        }
    }
    return result;
}

// @ 0x008b3040
extern "C" void ProcessExtraEdgesHints(PFROutline_s008b_3040* o, uint8_s008b_3040* data)
{
    int16_s008b_3040* xAll = o->xAll;       // pass 0 "all"
    int16_s008b_3040* xSet = o->xSetArr;    // pass 0 "current"
    int16_s008b_3040* yAll = o->yAll;       // pass 0 secondary
    int16_s008b_3040* ySet = o->ySetArr;    // pass 0 contour
    int16_s008b_3040* xPts = o->xPts;       // pass 1 "current" (after realloc)
    int16_s008b_3040* xExt = o->xExtra;
    int16_s008b_3040* yPts = o->yPts;
    int16_s008b_3040* yExt = o->yExtra;

    int   second = 0;
    int   count  = 0;
    uint8_s008b_3040* cur   = data;

    int   base = o->cntEdges;    // word index of the first point this call writes

    // The "current point" array is xSetArr (pass 0) / xExtra (pass 1); the other
    // three arrays are reached through signed word deltas from it.
    int16_s008b_3040* pt;
    int    dAll;                 // xAll (p0) / xPts (p1)
    int    dY;                   // yAll (p0) / yPts (p1)
    int    dYSet;                // ySetArr (p0) / yExtra (p1)

    if (!second) {
        pt    = xSet + base;
        dAll  = (int)(xAll - xSet);
        dY    = (int)(yAll - xSet);
        dYSet = (int)(ySet - xSet);
    } else {
        pt    = xExt + base;
        dAll  = (int)(xPts - xExt);
        dY    = (int)(yPts - xExt);
        dYSet = (int)(yExt - xExt);
    }

    int last = 0;

    for (;;) {
        count = *cur++;
        int tag = 0;

        if (second) {
            if (o->capX <= o->cntEdges + count) {
                int16_s008b_3040 cap = (int16_s008b_3040)(o->capX + 0x14);
                o->capX = cap;
                xPts = (int16_s008b_3040*)tsi_ReAllocMem(o->mem, xPts, cap * 2);
                xExt = (int16_s008b_3040*)tsi_ReAllocMem(o->mem, xExt, cap * 2);
                yPts = (int16_s008b_3040*)tsi_ReAllocMem(o->mem, yPts, cap * 2);
                yExt = (int16_s008b_3040*)tsi_ReAllocMem(o->mem, yExt, cap * 2);
                pt    = xExt + base;
                dAll  = (int)(xPts - xExt);
                dY    = (int)(yPts - xExt);
                dYSet = (int)(yExt - xExt);
            }
        } else {
            if (o->capY <= o->cntEdges + count) {
                int16_s008b_3040 cap = (int16_s008b_3040)(o->capY + 0x14);
                o->capY = cap;
                xAll = (int16_s008b_3040*)tsi_ReAllocMem(o->mem, xAll, cap * 2);
                yAll = (int16_s008b_3040*)tsi_ReAllocMem(o->mem, yAll, cap * 2);
                xSet = (int16_s008b_3040*)tsi_ReAllocMem(o->mem, xSet, cap * 2);
                ySet = (int16_s008b_3040*)tsi_ReAllocMem(o->mem, ySet, cap * 2);
                pt    = xSet + base;
                dAll  = (int)(xAll - xSet);
                dY    = (int)(yAll - xSet);
                dYSet = (int)(ySet - xSet);
            }
        }

        if (count > 0) {
            int16_s008b_3040* p = pt;
            int n = count;
            do {
                uint8_s008b_3040 b = *cur++;
                if ((int8_t)b < 0) {
                    tag = (b & 0x3f) - 1;
                    if (tag < 0) tag = *cur++;
                    if (b & 0x40)
                        *(int16_s008b_3040*)((char*)p + dAll * 2) = 0x10;
                    else
                        *(int16_s008b_3040*)((char*)p + dAll * 2) = *cur++;
                    int16_s008b_3040 c = (int16_s008b_3040)(int8_t)*cur++;
                    *p = c;
                    if (c == 0) {
                        c = (int16_s008b_3040)((uint16_s008b_3040)*cur * 0x100 + (uint16_s008b_3040)cur[1]);
                        cur += 2;
                        *p = c;
                    }
                } else {
                    tag += b >> 4;
                    *(int16_s008b_3040*)((char*)p + dAll * 2) = 0x10;
                    *p = (int16_s008b_3040)((int8_t)(b << 4) >> 4);
                }

                int ox, oy;
                if (second) {
                    TransformPoint_s008b_3040((int)*p << 16, &ox, &oy);
                    *p = (int16_s008b_3040)(oy >> 16);
                } else {
                    TransformPoint_s008b_3040(1, &ox, &oy);
                    *p = (int16_s008b_3040)(ox >> 16);
                }
                last = tag;
                *(int16_s008b_3040*)((char*)p + dY * 2) = (int16_s008b_3040)tag;
                *(int16_s008b_3040*)((char*)p + dYSet * 2) = o->glyph->contour;
                ++p;
            } while (--n != 0);
        }

        if (second) break;
        o->cntEdges = (int16_s008b_3040)(o->cntEdges + (int16_s008b_3040)count);
        base = o->cntEdges;
        second = 1;
        pt    = xExt + base;
        dAll  = (int)(xPts - xExt);
        dY    = (int)(yPts - xExt);
        dYSet = (int)(yExt - xExt);
    }
    (void)last;
    o->cntEdges = (int16_s008b_3040)(o->cntEdges + (int16_s008b_3040)count);
}

// @ 0x008b3390
extern "C" void ProcessExtraHints(void* self, PFROutline_s008b_3040* o, uint8_s008b_3040** cursor)
{
    (void)self;
    uint8_s008b_3040* p = *cursor + 1;
    uint16_s008b_3040 n = *(uint8_s008b_3040*)*cursor;
    if (n != 0) {
        uint32_s008b_3040 c = n;
        do {
            uint8_s008b_3040 b = *p;
            uint8_s008b_3040* q = p + 2;
            if (p[1] == 1)
                ProcessExtraStrokes(o, q);
            else if (p[1] == 2)
                ProcessExtraEdgesHints(o, q);
            p = q + (int16_s008b_3040)(uint16_s008b_3040)b;
        } while (--c != 0);
        *cursor = p;
        return;
    }
    *cursor = p;
}

// @ 0x008b3400
extern "C" uint FUN_008b3400(PFRClass_s008b_3040* obj, int16_s008b_3040 key)
{
    int16_s008b_3040 local4 = 0;
    uint  r = (uint)FindCharIndex(obj, key, &local4);
    *(uint*)((char*)obj + 0x1ec) = (uint)(r & 0xff);
    return (uint)(uint16_s008b_3040)local4;
}

// @ 0x008b3440
extern "C" uint FUN_008b3440(PFRClass_s008b_3040* obj, uint key, char noLoad, uint8_s008b_3040 flags)
{
    uint result = 0;
    if (noLoad != 0)
        return 0;

    if (*(int*)((char*)obj + 0x1c) != 0) {
        char* q = *(char**)((char*)obj + 0x184);
        PFRRec_s008b_3040* r = *(PFRRec_s008b_3040**)(q + 0x28);
        int16_s008b_3040 sx = r->x;
        int16_s008b_3040 sy = r->y;
        int16_s008b_3040 sz = r->z;

        if ((flags & 8) == 0)
            key = FUN_008b3400((PFRClass_s008b_3040*)r, (int16_s008b_3040)key);

        if ((( r->x != (int16_s008b_3040)key || sy != r->y || sz != r->z ) &&
             (AddPointRange((PFRClass_s008b_3040*)r, (int16_s008b_3040)key, 0, sy, sz),
              r->x != (int16_s008b_3040)key || sy != r->y || sz != r->z)))
            return 0;

        result = 1;
        void* buf = tsi_AllocMem(*(tsiMemObject**)r, r->size74);
        r->buf70 = buf;
        if (buf == 0)
            return 0;

        Seek_InputStream(*(InputStream**)((char*)r + 4), *(int*)((char*)r + 0x2c) + r->off78);
        PeekInt16(*(InputStream**)((char*)r + 4), r->buf70, r->size74);
        FUN_008b2250((PFRClass_s008b_3040*)r, 0, 0, 0);
        tsi_DeAllocMem(*(tsiMemObject**)r, r->buf70);
        r->buf70 = 0;
        if (flags & 0x20) {
            tsi_DeAllocMem(*(tsiMemObject**)r, r->buf7c);
            r->buf7c = 0;
        }

        *(void**)((char*)obj + 0x118) = r->buf7c;
        r->buf7c = 0;
        *(int*)((char*)obj + 0xd0) = r->f58;
        *(int*)((char*)obj + 0xd4) = 0;
        *(int*)((char*)obj + 0x114) = r->f68;
        r->f68 = 0;
        *(int*)((char*)obj + 0x10c) = r->f48;
        *(int*)((char*)obj + 0x110) = r->f4c;
        *(int*)((char*)obj + 0xcc) = 1;
        *(int*)((char*)obj + 0xe4) = r->f50 >> 10;
        *(int*)((char*)obj + 0xe0) = r->f54 >> 10;
        int v = r->f58;
        *(int*)((char*)obj + 0xd0) = v;
        *(int*)((char*)obj + 0xd8) = v;
        v = r->f5c;
        *(int*)((char*)obj + 0xd4) = v;
        *(int*)((char*)obj + 0xdc) = v;
        *(int*)((char*)obj + 0xe8) = 1;
        *(int*)((char*)obj + 0x100) = r->f5c >> 10;
        *(int*)((char*)obj + 0xfc)  = r->f60 >> 10;
        v = r->f64;
        *(int*)((char*)obj + 0xf0) = v;
        *(int*)((char*)obj + 0xf8) = v;
        v = r->f58;
        *(int*)((char*)obj + 0xec) = v;
        *(int*)((char*)obj + 0xf4) = v;

        if (*(char*)((char*)r + 0x1c) != 0) {
            *(int*)((char*)obj + 0xcc) = 0;
            return 1;
        }
        *(int*)((char*)obj + 0xe8) = 0;
    }
    return result;
}

// @ 0x008b3ae0
extern "C" void PFRBuildChar(PFRClass* pfr, uint8* data, int param_3, uint16 dataLen, int p5, int p6, int p7, int p8, PFROutline* out)
{
    uint8* cur = data + 1;
    uint8 flags = *data;
    PFRRec rec;
    PFRPts pts;

    if ((int8_t)flags < 0) {
        // composite glyph: a list of component records
        if (flags & 0x40) {
            uint32 n = *cur;
            cur = SkipItems(cur + 1, n);
        }
        int count = (int16)(flags & 0x3f);
        for (; count > 0; --count) {
            FUN_008b2630(pfr, &cur, &rec, &param_3);
            int off = rec.offset;
            Seek_InputStream(pfr->stream, pfr->dataBase + off);
            uint32 sz = rec.size & 0xffff;
            uint8* buf = (uint8*)tsi_AllocMem(pfr->mem, sz);
            PeekInt16(pfr->stream, buf, sz);
            PFRBuildChar(pfr, buf, off, (uint16)rec.size, rec.v[0], rec.v[2], rec.v[1], rec.v[3], out);
            tsi_DeAllocMem(pfr->mem, buf);
        }
        return;
    }

    GlyphBuilder* g = pfr->glyph;
    pts.ny = 0; pts.curX = 0; pts.nx = 0; pts.curY = 0;
    FUN_008b0920(pfr, flags, &cur, &pts);

    uint8* extra = 0;
    if (flags & 8) {
        extra = cur;
        cur = SkipItems(cur + 1, *cur);
    }

    // save the transform, then compose the component's scale/offset into it
    rec.v[0] = pfr->m[0]; rec.v[1] = pfr->m[1]; rec.v[2] = pfr->m[2]; rec.v[3] = pfr->m[3];
    rec.offset = pfr->m[4]; rec.size = pfr->m[5];
    SetupTrans(pfr, p5, p6, p7, p8);

    if (out != 0) {
        if (extra != 0)
            FUN_008b3390(out, pfr, &extra);

        // ---- x coordinate set ----
        int16 n = pts.nx;
        if (n < 1) {
            out->xAll[out->cntXPts + out->cntXSet] = -999;
            if (out->capXSet <= out->cntXSet + 1) {
                out->capXSet += 0x14;
                out->xSetArr = (int16*)tsi_ReAllocMem(out->mem, out->xSetArr, out->capXSet * 2);
            }
            out->xSetArr[out->cntXSet] = pfr->glyph->contour;
            out->cntXSet++;
        } else {
            if (out->capXPts <= out->cntXPts + n) {
                int16 add = (n < 0x14) ? 0x14 : n;
                out->capXPts += add;
                out->xPts = (int16*)tsi_ReAllocMem(out->mem, out->xPts, out->capXPts * 2);
            }
            if (out->capXAll <= out->cntXPts + out->cntXSet + n) {
                int16 add = (n < 0x14) ? 0x14 : n;
                out->capXAll += out->cntXSet + add;
                out->xAll = (int16*)tsi_ReAllocMem(out->mem, out->xAll, out->capXAll * 2);
            }
            for (int i = 0; i < pts.nx; i++) {
                int ox, oy;
                TransformPoint(pfr, pts.xs[i] << 16, 1, &ox, &oy);
                out->xPts[out->cntXPts + i] = (int16)(ox >> 16);
                out->xAll[out->cntXSet + out->cntXPts + i] = pfr->glyph->contour;
            }
        }
        out->cntXPts += pts.nx;

        // ---- y coordinate set ----
        n = pts.ny;
        if (n < 1) {
            out->yAll[out->cntYSet + out->cntYPts] = -999;
            if (out->capYSet <= out->cntYSet + 1) {
                out->capYSet += 0x14;
                out->ySetArr = (int16*)tsi_ReAllocMem(out->mem, out->ySetArr, out->capYSet * 2);
            }
            out->ySetArr[out->cntYSet] = pfr->glyph->contour;
            out->cntYSet++;
        } else {
            if (out->capYPts <= out->cntYPts + n) {
                int16 add = (n < 0x14) ? 0x14 : n;
                out->capYPts += add;
                out->yPts = (int16*)tsi_ReAllocMem(out->mem, out->yPts, out->capYPts * 2);
            }
            if (out->capYAll <= out->cntYPts + out->cntYSet + n) {
                int16 add = (n < 0x14) ? 0x14 : n;
                out->capYAll += out->cntYSet + add;
                out->yAll = (int16*)tsi_ReAllocMem(out->mem, out->yAll, out->capYAll * 2);
            }
            for (int i = 0; i < pts.ny; i++) {
                int ox, oy;
                TransformPoint(pfr, 1, pts.ys[i] << 16, &ox, &oy);
                out->yPts[out->cntYPts + i] = (int16)(oy >> 16);
                out->yAll[out->cntYPts + out->cntYSet + i] = pfr->glyph->contour;
            }
        }
        out->cntYPts += pts.ny;
        out->numChars++;
    }

    if (pfr->ver == 0) {
        // simple command stream
        pfr->inContour = 0;
        for (;;) {
            uint32 b = *cur++;
            switch (b >> 4) {
            case 0:
                if (pfr->inContour) {
                    glyph_CloseContour(g);
                    pfr->inContour = 0;
                }
                pfr->m[0] = rec.v[0]; pfr->m[1] = rec.v[1]; pfr->m[2] = rec.v[2]; pfr->m[3] = rec.v[3];
                pfr->m[4] = rec.offset; pfr->m[5] = rec.size;
                return;
            case 1: {
                uint32 a, c; int ox, oy;
                FUN_008b0f10(&cur, b, &pts, &a, &c);
                TransformPoint(pfr, (int16)a << 16, (int16)c << 16, &ox, &oy);
                glyph_AddPoint(g, (int16)(ox >> 16), (int16)(oy >> 16), 1);
                break;
            }
            case 2: {
                int ox, oy;
                pts.curX = pts.xs[b & 0xf];
                TransformPoint(pfr, pts.curX << 16, pts.curY << 16, &ox, &oy);
                glyph_AddPoint(g, (int16)(ox >> 16), (int16)(oy >> 16), 1);
                break;
            }
            case 3: {
                int ox, oy;
                pts.curY = pts.ys[b & 0xf];
                TransformPoint(pfr, pts.curX << 16, pts.curY << 16, &ox, &oy);
                glyph_AddPoint(g, (int16)(ox >> 16), (int16)(oy >> 16), 1);
                break;
            }
            case 4:
            case 5: {
                uint32 a, c; int ox, oy;
                FUN_008b0f10(&cur, b, &pts, &a, &c);
                if (pfr->inContour)
                    glyph_CloseContour(g);
                TransformPoint(pfr, (int16)a << 16, (int16)c << 16, &ox, &oy);
                glyph_AddPoint(g, (int16)(ox >> 16), (int16)(oy >> 16), 1);
                pfr->inContour = 1;
                break;
            }
            case 6: {
                uint32 a1, b1, a2, b2, a3, b3; int x1, y1, x2, y2, x3, y3;
                FUN_008b0f10(&cur, 0xe, &pts, &a1, &b1);
                FUN_008b0f10(&cur, 8, &pts, &a2, &b2);
                FUN_008b0f10(&cur, 0xb, &pts, &a3, &b3);
                TransformPoint(pfr, (int16)a1 << 16, (int16)b1 << 16, &x1, &y1);
                TransformPoint(pfr, (int16)a2 << 16, (int16)b2 << 16, &x2, &y2);
                TransformPoint(pfr, (int16)a3 << 16, (int16)b3 << 16, &x3, &y3);
                glyph_AddPoint(g, (int16)(x1 >> 16), (int16)(y1 >> 16), 0);
                glyph_AddPoint(g, (int16)(x2 >> 16), (int16)(y2 >> 16), 0);
                glyph_AddPoint(g, (int16)(x3 >> 16), (int16)(y3 >> 16), 1);
                break;
            }
            case 7: {
                uint32 a1, b1, a2, b2, a3, b3; int x1, y1, x2, y2, x3, y3;
                FUN_008b0f10(&cur, 0xb, &pts, &a1, &b1);
                FUN_008b0f10(&cur, 2, &pts, &a2, &b2);
                FUN_008b0f10(&cur, 0xe, &pts, &a3, &b3);
                TransformPoint(pfr, (int16)a1 << 16, (int16)b1 << 16, &x1, &y1);
                TransformPoint(pfr, (int16)a2 << 16, (int16)b2 << 16, &x2, &y2);
                TransformPoint(pfr, (int16)a3 << 16, (int16)b3 << 16, &x3, &y3);
                glyph_AddPoint(g, (int16)(x1 >> 16), (int16)(y1 >> 16), 0);
                glyph_AddPoint(g, (int16)(x2 >> 16), (int16)(y2 >> 16), 0);
                glyph_AddPoint(g, (int16)(x3 >> 16), (int16)(y3 >> 16), 1);
                break;
            }
            default: {
                uint32 a1, b1, a2, b2, a3, b3; int x1, y1, x2, y2, x3, y3;
                FUN_008b0f10(&cur, b, &pts, &a1, &b1);
                uint32 b2byte = *cur++;
                FUN_008b0f10(&cur, b2byte, &pts, &a2, &b2);
                FUN_008b0f10(&cur, b2byte >> 4, &pts, &a3, &b3);
                Xf(pfr, (int16)a1, (int16)b1, &x1, &y1);
                Xf(pfr, (int16)a2, (int16)b2, &x2, &y2);
                Xf(pfr, (int16)a3, (int16)b3, &x3, &y3);
                glyph_AddPoint(g, (int16)(x1 >> 16), (int16)(y1 >> 16), 0);
                glyph_AddPoint(g, (int16)(x2 >> 16), (int16)(y2 >> 16), 0);
                glyph_AddPoint(g, (int16)(x3 >> 16), (int16)(y3 >> 16), 1);
                break;
            }
            }
        }
    }

    // ver != 0: command stream decoded by FUN_008b3680
    uint8* end = data + (dataLen - 1);
    PFRState st;
    int16 pt[6];
    pts.w2 = 0; pts.w4 = 0; pts.curX = 0; pts.curY = 0;
    st.cur = cur;
    st.flag = 0;
    int type = -1;
    pfr->inContour = 0;
    while (st.cur < end || (st.cur == end && st.flag == 0)) {
        FUN_008b3680(&pts, &st, pt, &type);
        if ((int16)type == 0) {
            if (pfr->inContour)
                glyph_CloseContour(g);
            int x, y;
            Xf(pfr, pt[0], pt[1], &x, &y);
            glyph_AddPoint(g, (int16)(x >> 16), (int16)(y >> 16), 1);
            pfr->inContour = 1;
        } else if ((int16)type == 1) {
            int x16 = pt[0] << 16;
            int y16 = pt[1] << 16;
            int tx = util_FixMul(p5, x16) + p7;
            int ty = util_FixMul(p6, y16) + p8;
            int t2 = util_FixMul(ty, pfr->fb4);
            util_FixMul(tx + t2, pfr->f28);
            util_FixMul(ty, pfr->f28);
            int x, y;
            Xf(pfr, pt[0], pt[1], &x, &y);
            glyph_AddPoint(g, (int16)(x >> 16), (int16)(y >> 16), 1);
        } else if ((int16)type == 2) {
            int x1, y1, x2, y2, x3, y3;
            Xf(pfr, pt[0], pt[1], &x1, &y1);
            Xf(pfr, pt[2], pt[3], &x2, &y2);
            Xf(pfr, pt[4], pt[5], &x3, &y3);
            glyph_AddPoint(g, (int16)(x1 >> 16), (int16)(y1 >> 16), 0);
            glyph_AddPoint(g, (int16)(x2 >> 16), (int16)(y2 >> 16), 0);
            glyph_AddPoint(g, (int16)(x3 >> 16), (int16)(y3 >> 16), 1);
        }
    }
    pfr->m[0] = rec.v[0]; pfr->m[1] = rec.v[1]; pfr->m[2] = rec.v[2]; pfr->m[3] = rec.v[3];
    pfr->m[4] = rec.offset; pfr->m[5] = rec.size;
    if (pfr->inContour) {
        glyph_CloseContour(g);
        pfr->inContour = 0;
    }
}

// @ 0x008b4f00
extern "C" int16_s008b_4cc0 FUN_008b4f00(PFRClass_s008b_4cc0* o)
{
    int16_s008b_4cc0 l10, lc, l8, l4;

    o->f110 = 0;
    o->f114 = 0x7fff;
    o->f118 = 0xffff8001;
    o->f11c = 0x7fff;

    // FUN_008b19e0(handle20, handle24, id, a, b, c): fetch the record with the id.
    if (((HRec*)*(void**)((char*)o + 0x20))->FUN_008b19e0(*(void**)((char*)o + 0x24), 2, &l10, &lc, &l4) != 0 &&
        ((HRec*)*(void**)((char*)o + 0x20))->FUN_008b19e0(*(void**)((char*)o + 0x24), 7, &l10, &lc, &l4) != 0)
        goto after_records;

    o->f114 = l10;
    o->f118 = -(int)lc;
    o->f11c = l8;
    o->f120 = l4;

after_records:
    o->f124 = *(uint32_s008b_4cc0*)((char*)o + 0xb8);

    {
        uint16_s008b_4cc0 i = 0;
        if ((int16_s008b_4cc0)o->numChars > 0) {
            do {
                int16_s008b_4cc0* p = *(int16_s008b_4cc0**)(*(int*)((char*)o + 0x100) + 0xc);
                p[i] = 0;
                i = (uint16_s008b_4cc0)(i + 1);
            } while ((int)i < (int)(int16_s008b_4cc0)o->numChars);
        }
    }

    if (o->f114 == 0x7fff) {
        l4 = 0;
        FUN_008b1c70(o, 0x66, &l4);
        g_foundKey = l4;
        *(uint*)((char*)o + 0x1ec) = (uint)(FoundIdx() & 0xff);
        if (l4 != 0) {
            PFRGlyph* g = (PFRGlyph*)FUN_008b4cc0(o, (uint)KeyIdx(), &l10, (uint16_s008b_4cc0*)&lc, 0);
            if (g != 0) {
                int16_s008b_4cc0* py = g->py;
                int16_s008b_4cc0  mx = py[0];
                for (int i = 1; i < g->cnt; i++)
                    if (mx < py[i]) mx = py[i];
                o->f114 = mx;
                Delete_GlyphClass(g);
            }
        }
    }

    if (o->f118 == 0xffff8001) {
        l4 = 0;
        FUN_008b1c70(o, 0x67, &l4);
        g_foundKey = l4;
        *(uint*)((char*)o + 0x1ec) = (uint)(FoundIdx() & 0xff);
        if (l4 != 0) {
            PFRGlyph* g = (PFRGlyph*)FUN_008b4cc0(o, (uint)KeyIdx(), &l10, (uint16_s008b_4cc0*)&lc, 0);
            if (g != 0) {
                int16_s008b_4cc0* py = g->py;
                int16_s008b_4cc0  mn = py[0];
                for (int i = 1; i < g->cnt; i++)
                    if (py[i] < mn) mn = py[i];
                o->f118 = mn;
                Delete_GlyphClass(g);
            }
        }
    }

    o->f110 = 0x20;
    if (o->f114 == 0x7fff) {
        int t = (int)o->width * 3;
        o->f114 = (int)(t + ((uint32_s008b_4cc0)t >> 31 & 3)) >> 2;
    }
    if (o->f118 == 0xffff8001) {
        int w = (int)o->width;
        o->f118 = -(int)(w + ((uint32_s008b_4cc0)w >> 31 & 3)) >> 2;
    }
    if (o->f11c == 0x7fff)
        o->f11c = (o->width - o->f114) + o->f118;
    if (o->f11c < 0)
        o->f11c = 0;
    return 0;
}
