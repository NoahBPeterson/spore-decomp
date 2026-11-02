// src/game/UTFSpore_Win32/t2kstrk1.cpp -- migrated from slice(s) s008caba0, s008c9e00, s008c9000 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/t2kstrk1.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int util_FixMul(int a, int b);                                    // 0x008d1590
extern "C" int util_FixDiv(int a, int b);                                    // 0x008d16d0

// ---- items of slice s008c9000 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct tsiMemObject;
struct T2KInterSectType {          // size 0x8
    long coordinate25Dot6_flag1;   // 2 * coordinate (26.6) + direction flag
    T2KInterSectType* next;
};
struct tsiScanConv {               // size 0x2238 (dev PDB)
    long prevX0;                   // +0x0
    long prevY0;                   // +0x4
    long left;                     // +0x8
    long right;                    // +0xc
    long top;                      // +0x10
    long bottom;                   // +0x14
    long fTop26Dot6;               // +0x18
    long fLeft26Dot6;              // +0x1c
    long rowBytes;                 // +0x20
    unsigned char* baseAddr;       // +0x24
    int internal_baseAddr;         // +0x28
    int scanBBoxIsComputed;        // +0x2c
    long xminSC;                   // +0x30
    long xmaxSC;                   // +0x34
    long yminSC;                   // +0x38
    long ymaxSC;                   // +0x3c
    long outlineXMin;              // +0x40
    long outlineXMax;              // +0x44
    long outlineYMin;              // +0x48
    long outlineYMax;              // +0x4c
    int couldOverflowIntegerMath;  // +0x50
    T2KInterSectType* yBaseBuffer[32];      // +0x54
    T2KInterSectType** yEdgeHead;  // +0xd4
    T2KInterSectType** yBase;      // +0xd8
    long minYIndex;                // +0xdc
    long maxYIndex;                // +0xe0
    T2KInterSectType* xBaseBuffer[32];      // +0xe4
    T2KInterSectType** xEdgeHead;  // +0x164
    T2KInterSectType** xBase;      // +0x168
    long minXIndex;                // +0x16c
    long maxXIndex;                // +0x170
    T2KInterSectType* free;        // +0x174
    T2KInterSectType* freeEnd;     // +0x178
    T2KInterSectType firstMemBlockBuffer[1024];   // +0x17c
    T2KInterSectType* freeMemBlocksBuffer[32];    // +0x217c
    T2KInterSectType** freeMemBlocks;       // +0x21fc
    long freeMemBlockMaxCount;     // +0x2200
    long freeMemBlockN;            // +0x2204
    long maxError;                 // +0x2208
    unsigned char greyScaleLevel;  // +0x220c
    char xDropOutControl;          // +0x220d
    char yDropOutControl;          // +0x220e
    char includeStubs;             // +0x220f
    char smartDropout;             // +0x2210
    char doXEdges;                 // +0x2211
    int weDidXDropouts;            // +0x2214
    int weDidYDropouts;            // +0x2218
    short* startPoint;             // +0x221c
    short* endPoint;               // +0x2220
    short numberOfContours;        // +0x2224
    long* x;                       // +0x2228
    long* y;                       // +0x222c
    char* onCurve;                 // +0x2230
    tsiMemObject* mem;             // +0x2234
};
struct tsiMemObject {
    uint32_t pad00[0x18];           // +0x00
    tsiScanConv* currentScanConv;   // +0x60 scan converter owning the cached bitmap
    void* cachedBitmap;             // +0x64
    uint32_t pad18[0x0c];           // +0x68
    int scanConvKept;               // +0x98 scan converter was cached, do not free it
    int bitmapKept;                 // +0x9c bitmap was cached, do not free it
};
struct StrokeState {
    tsiMemObject* mem;              // +0x00
    int nA;                         // +0x04 number of shorts in list A
    int capA;                       // +0x08
    short* ptsA;                    // +0x0c
    int nB;                         // +0x10 number of shorts in list B
    int capB;                       // +0x14
    short* ptsB;                    // +0x18
};
extern "C" void* tsi_ReAllocMem(tsiMemObject* mem, void* p, int bytes);      // 0x008d1330
extern "C" int util_FixMul(int a, int b);                                    // 0x008d1590
extern "C" int util_FixDiv(int a, int b);                                    // 0x008d16d0
static __declspec(noinline) void FUN_008c9b70(StrokeState* st, short x1, short y1, short on1,
                                              short x2, short y2, short on2);
static __declspec(noinline) int FUN_008c9c40(int dy, int dx);
static __declspec(noinline) int IsIntersection(short x1, short y1, short x2, short y2,
                                               short x3, short y3, short x4, short y4,
                                               short* ox, short* oy);
// ---- items of slice s008c9000 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* tsi_ReAllocMem(tsiMemObject* mem, void* p, int bytes);      // 0x008d1330

// ---- items of slice s008c9e00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* tsi_ReAlloc(void* mem, void* p, int bytes);                   // 0x008d1330
extern "C" void util_ComputeIntersection(short x1, short y1, short x2, short y2, short x3, short y3,
short x4, short y4, short* ox, short* oy);   // 0x008d1890
struct StrokeState_s008c_9e00 {
    tsiMemObject* mem;      // +0x00
    int nA;                 // +0x04 shorts in list A
    int capA;               // +0x08
    short* ptsA;            // +0x0c
    int nB;                 // +0x10
    int capB;               // +0x14
    short* ptsB;            // +0x18
    int offX;               // +0x1c cached normal offset of the previous segment
    int offY;               // +0x20
    int lastIndex;          // +0x24 segment counter + 1 of the cached offset
};
void addPointA(StrokeState_s008c_9e00* st, int x, int y, int on);              // 0x008c9b10 (cdecl)
void addPointB(StrokeState_s008c_9e00* st, int x, int y, int on);              // 0x008c9be0 (cdecl)
static __declspec(noinline) void FUN_008c9b70_s008c_9e00(StrokeState_s008c_9e00* st, int x1, int y1, int on1,
                                                int x2, int y2, int on2)   // @ 0x008c9b70
{
    int n = st->nA;
    st->nA = n + 6;
    if (st->nA > st->capA) {
        st->capA = (n >> 1) + n + 0x10;
        st->ptsA = (short*)tsi_ReAlloc(st->mem, st->ptsA, st->capA * 2);
    }
    short* p = st->ptsA + n;
    p[0] = (short)x1;
    p[1] = (short)y1;
    p[2] = (short)on1;
    p[3] = (short)x2;
    p[4] = (short)y2;
    p[5] = (short)on2;
}
static __declspec(noinline) int FUN_008c9c40_s008c_9e00(int dy, int dx)                // @ 0x008c9c40
{
    if (dx == 0) {
        if (dy < 0)
            dy = -dy;
        return dy;
    }
    if (dy == 0) {
        if (dx < 0)
            dx = -dx;
        return dx;
    }
    if (dy < 0)
        dy = -dy;
    if (dx < 0)
        dx = -dx;
    int est;
    if (dy > dx)
        est = (dx >> 1) + dy;
    else
        est = (dy >> 1) + dx;
    int sq = dy * dy + dx * dx;
    est = (sq / est + est + 1) >> 1;
    return (sq / est + est + 1) >> 1;
}
static __declspec(noinline) int FUN_008c9ca0(short x1, short y1, short x2, short y2, short x3, short y3,
                                                short x4, short y4, short* ox, short* oy)   // @ 0x008c9ca0
{
    int result = 0;
    int dx34 = x4 - x3;
    int dy34 = y4 - y3;
    int dx12 = x2 - x1;
    int dy12 = y2 - y1;
    int p1 = dx34 * dy12;
    int p2 = dy34 * dx12;
    int det = p1 - p2;
    if (det == 0) {
        *ox = (short)((x2 + x3) / 2);
        *oy = (short)((y2 + y4) / 2);
        return result;
    }
    unsigned t = util_FixDiv((y3 - y1) * dx12 - (x3 - x1) * dy12, det);
    if (t <= 0x10000 && p2 - p1 != 0) {
        unsigned u = util_FixDiv((y1 - y3) * dx34 - (x1 - x3) * dy34, p2 - p1);
        result = u <= 0x10000 ? 1 : 0;
    }
    *ox = (short)(x3 + ((util_FixMul(dx34 * 4, t) + 2) >> 2));
    *oy = (short)(y3 + ((util_FixMul(dy34 * 4, t) + 2) >> 2));
    return result;
}
static __inline int ApproxLen(int a, int b)
{
    if (a < 0)
        a = -a;
    if (b < 0)
        b = -b;
    if (a < b)
        return (a >> 1) + b;
    return (b >> 1) + a;
}
static __inline int ScaleTo(int w8, int v, int len)
{
    int half = len >> 1;
    if (v < 0)
        return -((half - w8 * v) / len);
    return (w8 * v + half) / len;
}
typedef void (*AddPointFn)(StrokeState_s008c_9e00*, int, int, int);
// ---- items of slice s008c9e00 end

// ---- items of slice s008c9e00_g7 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void tsi_DeAllocMem(void* obj, void* p);                            // 0x008d1440
struct StrokeState_s008c_9e00__g7 {
    tsiMemObject* mem;      // +0x00
    int nA;                 // +0x04
    int capA;               // +0x08
    short* ptsA;            // +0x0c  list A: 3 shorts per point (x, y, on-curve)
    int nB;                 // +0x10
    int capB;               // +0x14
    short* ptsB;            // +0x18
    int offX;               // +0x1c
    int offY;               // +0x20
    int lastIndex;          // +0x24
};
struct Glyph {
    uint8_t pad00[0x36];
    short nPoints;          // +0x36
    short lastIndex;        // +0x38
    short* tp;              // +0x3c  tags / contour endpoints
    short* contour;         // +0x40
    short* xcoords;         // +0x44  x coordinates
    short* ycoords;         // +0x48  y coordinates
    uint8_t* tags;          // +0x4c  on-curve flags
    short cap54;            // +0x54
    uint8_t pad56[0x8c - 0x56];
    int flag8c;             // +0x8c
};
struct TPath {
    uint8_t pad00[4];
    int n;                  // +0x04
    uint8_t pad08[4];
    short* pts;             // +0x0c  3 shorts per point
    int n2;                 // +0x10
    uint8_t pad14[4];
    short* ptsR;            // +0x18
};
extern "C" void AllocGlyphPointMemory(Glyph* g, int n);                        // 0x008b0230
static __declspec(noinline) void FUN_008c9b70_s008c_9e00__g7(StrokeState_s008c_9e00__g7* st, int x1, int y1, int on1,
                                                int x2, int y2, int on2)   // @ 0x008c9b70
{
    int n = st->nA;
    st->nA = n + 6;
    if (st->nA > st->capA) {
        st->capA = (n >> 1) + n + 0x10;
        st->ptsA = (short*)tsi_ReAlloc(st->mem, st->ptsA, st->capA * 2);
    }
    short* p = st->ptsA + n;
    p[0] = (short)x1;
    p[1] = (short)y1;
    p[2] = (short)on1;
    p[3] = (short)x2;
    p[4] = (short)y2;
    p[5] = (short)on2;
}
static __declspec(noinline) int FUN_008c9c40_s008c_9e00__g7(int dy, int dx)                // @ 0x008c9c40
{
    if (dx == 0) {
        if (dy < 0)
            dy = -dy;
        return dy;
    }
    if (dy == 0) {
        if (dx < 0)
            dx = -dx;
        return dx;
    }
    if (dy < 0)
        dy = -dy;
    if (dx < 0)
        dx = -dx;
    int est;
    if (dy > dx)
        est = (dx >> 1) + dy;
    else
        est = (dy >> 1) + dx;
    int sq = dy * dy + dx * dx;
    est = (sq / est + est + 1) >> 1;
    return (sq / est + est + 1) >> 1;
}
static void AddTwoPointsA(StrokeState_s008c_9e00__g7* st, int x1, int y1, int on1, int x2, int y2, int on2)
{
    FUN_008c9b70_s008c_9e00__g7(st, x1, y1, on1, x2, y2, on2);
}
static int OverAbs(int v)
{
    return v < 0 ? -v : v;
}
// ---- items of slice s008c9e00_g7 end

// ---- items of slice s008caba0 begin (TODO(rewrite): local stubs, replace by canonical classes)
/* Slice s008caba0 -- T2K / Font Fusion (module "EA-UTF"): glyph stroking + hint application.
 *
 * COMPILE AS C: "/O2 /MD /Gy /TC /GS-"   (T2K is C, like s008bb550 / s008bdb70 / s008be260).
 * The retail binary was built with LTCG, so several of these routines take arguments in
 * caller-saved registers rather than on the stack; they are written here with those values as
 * ordinary leading/extra parameters and cannot be byte-exact from a single /O2 TU (see
 * nonmatching.txt).
 *
 * 008caba0 glyph_StrokeCtr            stroke one contour of a glyph (source glyph arrives in EDI)
 * 008cae30 ApplyHintsToStrokeGlyph    snap the x then y coordinates to the pixel grid (5th arg in EAX)
 * 008cb070 ff_glyph_StrokeGlyph       stroke a whole glyph into a freshly allocated GlyphClass
 * 008cb1b0 ff_Read2Numbers            bit-packed 2-number stream decoder
 * 008cb2e0 ff_Read4Numbers            bit-packed 4-number stream decoder
 * 008cb450 ReadLowUnsignedNumber      0xf0-prefixed 4-bits-per-byte variable-length number
 * 008cb520 AllocatePointSpaceIfNeeded grow the point arrays and copy the old points (glyph in ECX, count in EAX)
 * 008cb5e0 GetGlyphStream             open a sub-stream over one glyph's data (font in ESI)
 * 008cb6b0 Read_PreferredMappingTable decode the "preferred mapping" cmap sub-table
 * 008cb790 MapCodeToGlyph             binary search of a decoded mapping table
 */

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned int uint32;
typedef int int32;
typedef struct tsiMemObject_s008c_aba0 {
    uint8 pad00[0x54];
    void* base54;           // +0x54
    uint8 pad58[0x8c - 0x58];
    int32 flag8c;           // +0x8c
} tsiMemObject_s008c_aba0;
typedef int (*PF_READ_TO_RAM)(void* id, uint8* dest, int32 offset, int32 numBytes);
typedef struct InputStream {
    uint8* privateBase;            // +0x000
    PF_READ_TO_RAM ReadToRamFunc;  // +0x004
    void* nonRamID;                // +0x008
    uint8 tmp_ch[0x208];           // +0x00c
    uint32 cacheCount;             // +0x214
    uint32 posZero;                // +0x218
    uint32 pos;                    // +0x21c
    uint32 pad220[3];              // +0x220
    tsiMemObject_s008c_aba0* mem;             // +0x22c
} InputStream;
typedef struct GlyphClass {
    tsiMemObject_s008c_aba0* mem;      // +0x00
    int16 contourCount;     // +0x04
    int16 pad06;
    int32 pointCount32;     // +0x08
    int32 x0c;              // +0x0c
    int32 x10;              // +0x10
    int16 spBuffer[16];     // +0x14
    int16 x34;              // +0x34
    int16 contourCountMax;  // +0x36
    int16 pointCount;       // +0x38
    int16 pad3a;
    int16* sp;              // +0x3c
    int16* ep;              // +0x40
    int16* oox;             // +0x44
    int16* ooy;             // +0x48
    uint8* onCurve;         // +0x4c
    void* x50;              // +0x50
    void* x54;              // +0x54
    int16* componentData;   // +0x58
    int32 componentSize;    // +0x5c
    int32 componentSizeMax; // +0x60
    uint8* hintFragment;    // +0x64
    int32 hintLength;       // +0x68
    int16 xmin;             // +0x6c
    int16 ymin;             // +0x6e
    int16 xmax;             // +0x70
    int16 ymax;             // +0x72
    int32 x74;              // +0x74
} GlyphClass;
typedef struct T2KSFont {
    uint8 pad00[0x2c];
    void* sloc;                        // +0x2c
    uint8 pad30[0xdc - 0x30];
    InputStream* in;                   // +0xdc
    uint8 pade0[0xe8 - 0xe0];
    tsiMemObject_s008c_aba0* mem;                 // +0xe8
    uint8 padec[0xf0 - 0xec];
    int32 numGlyphs;                   // +0xf0
} T2KSFont;
typedef struct StrokeState_s008c_aba0 {
    tsiMemObject_s008c_aba0* mem;   // +0x00
    int nA;              // +0x04
    int capA;            // +0x08
    int16* ptsA;         // +0x0c
    int nB;              // +0x10
    int capB;            // +0x14
    int16* ptsB;         // +0x18
    int offX;            // +0x1c
    int offY;            // +0x20
    int lastIndex;       // +0x24
} StrokeState_s008c_aba0;
extern void* tsi_AllocMem(tsiMemObject_s008c_aba0* mem, int32 size);                     // 0x008d1260
extern void tsi_Error(tsiMemObject_s008c_aba0* mem, int32 errCode);                      // 0x008d10c0
extern void PrimeT2KInputStream(InputStream* in);                            // 0x008cc0b0
extern InputStream* New_InputStream2(tsiMemObject_s008c_aba0* mem, InputStream* in, uint32 offset,
                                     uint32 length, int32 unused, int* errCode); // 0x008cc330
extern void Seek_InputStream(InputStream* in, uint32 pos);                   // 0x008cc580
extern uint32 Tell_InputStream(InputStream* in);                             // 0x008cc5b0
extern int32 FF_SLOC_MapIndexToOffset(void* sloc, InputStream* in, int32 index); // 0x008cdec0
extern uint8* GetTableDirEntry_sfntClass(T2KSFont* font, uint32 tag);        // 0x008cebe0
extern int32 util_FixMul_s008c_aba0(int32 a, int32 b);                                  // 0x008d1590
extern int32 util_FixDiv_s008c_aba0(int32 a, int32 b);                                  // 0x008d16d0
extern GlyphClass* New_EmptyGlyph(tsiMemObject_s008c_aba0* mem, int a, int b, int c, int d); // 0x008b0480
extern void Delete_GlyphClass(GlyphClass* g);                                // 0x008b0280
extern void lineJoin(StrokeState_s008c_aba0* st, int joinType, int x0, int y0, int x1, int y1,
                     int outer, int index, int x2, int y2, int w);
extern void FUN_008ca5b0(StrokeState_s008c_aba0* st, int c, int x, int y, int w);
extern void FUN_008ca980(StrokeState_s008c_aba0* st, GlyphClass* dst, int closed);
#define T2K_ERR_TRANS_FAIL 10024
static __inline uint8 ReadUnsignedByteSlow(InputStream* in)
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
// ---- items of slice s008caba0 end

// @ 0x008c9b10
void addPointA(StrokeState* st, short x, short y, short on)
{
    int n = st->nA;
    st->nA = n + 3;
    if (st->nA > st->capA) {
        st->capA = (n >> 1) + n + 0x10;
        st->ptsA = (short*)tsi_ReAllocMem(st->mem, st->ptsA, st->capA * 2);
    }
    short* p = st->ptsA + n;
    p[0] = x;
    p[1] = y;
    p[2] = on;
}

// @ 0x008c9b70
static void FUN_008c9b70(StrokeState* st, short x1, short y1, short on1, short x2, short y2, short on2)
{
    int n = st->nA;
    st->nA = n + 6;
    if (st->nA > st->capA) {
        st->capA = (n >> 1) + n + 0x10;
        st->ptsA = (short*)tsi_ReAllocMem(st->mem, st->ptsA, st->capA * 2);
    }
    short* p = st->ptsA + n;
    p[0] = x1;
    p[1] = y1;
    p[2] = on1;
    p[3] = x2;
    p[4] = y2;
    p[5] = on2;
}

// @ 0x008c9be0
void addPointB(StrokeState* st, short x, short y, short on)
{
    int n = st->nB;
    st->nB = n + 3;
    if (st->nB > st->capB) {
        st->capB = (n >> 1) + n + 0x10;
        st->ptsB = (short*)tsi_ReAllocMem(st->mem, st->ptsB, st->capB * 2);
    }
    short* p = st->ptsB + n;
    p[0] = x;
    p[1] = y;
    p[2] = on;
}

// @ 0x008c9c40
static int FUN_008c9c40(int dy, int dx)
{
    if (dx == 0) {
        if (dy < 0)
            dy = -dy;
        return dy;
    }
    if (dy == 0) {
        if (dx < 0)
            dx = -dx;
        return dx;
    }
    if (dy < 0)
        dy = -dy;
    if (dx < 0)
        dx = -dx;
    int est;
    if (dy > dx)
        est = (dx >> 1) + dy;
    else
        est = (dy >> 1) + dx;
    int sq = dy * dy + dx * dx;
    est = (sq / est + est + 1) >> 1;
    return (sq / est + est + 1) >> 1;
}

// @ 0x008c9ca0
static int IsIntersection(short x1, short y1, short x2, short y2, short x3, short y3, short x4, short y4, short* ox, short* oy)
{
    int result = 0;
    int dx34 = x4 - x3;
    int dy34 = y4 - y3;
    int dx12 = x2 - x1;
    int dy12 = y2 - y1;
    int p1 = dx34 * dy12;
    int p2 = dy34 * dx12;
    int det = p1 - p2;
    if (det == 0) {
        *ox = (short)((x2 + x3) / 2);
        *oy = (short)((y2 + y3) / 2);
        return result;
    }
    unsigned t = util_FixDiv((y3 - y1) * dx12 - (x3 - x1) * dy12, det);
    if (t <= 0x10000 && p2 - p1 != 0) {
        unsigned u = util_FixDiv((y1 - y3) * dx34 - (x1 - x3) * dy34, p2 - p1);
        result = u <= 0x10000 ? 1 : 0;
    }
    *ox = (short)(x3 + ((util_FixMul(dx34 * 4, t) + 2) >> 2));
    *oy = (short)(y3 + ((util_FixMul(dy34 * 4, t) + 2) >> 2));
    return result;
}

// @ 0x008c9e00
void lineJoin(StrokeState_s008c_9e00* st, int joinType, int x0, int y0, int x1, int y1, int outer, int index, int x2, int y2, int w)
{
    int w2 = w * 2;
    int dy1 = y1 - y0;
    int dx1 = x1 - x0;
    int len1 = ApproxLen(dy1, dx1);
    int dy2 = y2 - y1;
    int dx2 = x2 - x1;
    int len2 = ApproxLen(dy2, dx2);
    int cross = dy2 * dx1 - dx2 * dy1;
    int acr = cross;
    if (acr < 0)
        acr = -acr;
    int dot = dx2 * dx1 + dy2 * dy1;
    int lenProd = len2 * len1;
    int s, o1x, o1y, o2x, o2y;

    if ((acr < (lenProd >> 3) && 0 < dot) || (outer == 0 && acr < (lenProd >> 2) && dot < 0)) {
        // nearly straight (or a hairpin turn on the inner side): a plain bevel across the corner
        int d = FUN_008c9c40_s008c_9e00(2 * (y0 - y2), 2 * (x2 - x0));
        if (d == 0)
            s = 0x10000;
        else
            s = util_FixDiv(w2, d);
        int ny = util_FixMul(y0 - y2, s);
        int nx = util_FixMul(x2 - x0, s);
        int dd = FUN_008c9c40_s008c_9e00(8 * ny, 8 * nx);
        if (0 < dd) {
            int w8 = w * 8;
            ny = ScaleTo(w8, ny, dd);
            nx = ScaleTo(w8, nx, dd);
        }
        addPointA(st, x1 + ny, nx + y1, outer);
        addPointB(st, x1 - ny, y1 - nx, outer);
        return;
    }

    if (index == st->lastIndex) {
        o1x = st->offX;
        o1y = st->offY;
    } else {
        int d = FUN_008c9c40_s008c_9e00(2 * (y0 - y1), 2 * dx1);
        if (d == 0)
            s = 0x10000;
        else
            s = util_FixDiv(w2, d);
        o1x = util_FixMul(y0 - y1, s);
        o1y = util_FixMul(dx1, s);
        int dd = FUN_008c9c40_s008c_9e00(8 * o1x, 8 * o1y);
        if (0 < dd) {
            int w8 = w * 8;
            o1x = ScaleTo(w8, o1x, dd);
            o1y = ScaleTo(w8, o1y, dd);
        }
    }
    {
        int d = FUN_008c9c40_s008c_9e00(2 * (y1 - y2), 2 * dx2);
        if (d == 0)
            s = 0x10000;
        else
            s = util_FixDiv(w2, d);
        o2x = util_FixMul(y1 - y2, s);
        o2y = util_FixMul(dx2, s);
        int dd = FUN_008c9c40_s008c_9e00(8 * o2x, 8 * o2y);
        if (0 < dd) {
            int w8 = w * 8;
            o2x = ScaleTo(w8, o2x, dd);
            o2y = ScaleTo(w8, o2y, dd);
        }
    }
    st->lastIndex = index + 1;
    st->offX = o2x;
    st->offY = o2y;

    uint32_t ixA, iyA, ixB, iyB;
    int hitA = FUN_008c9ca0(x0 + o1x, y0 + o1y, x1 + o1x, y1 + o1y, x1 + o2x, y1 + o2y,
                              x2 + o2x, y2 + o2y, (short*)&ixA, (short*)&iyA);
    int bx1 = x1 - o2x;
    int by1 = y1 - o1y;
    int by2 = y1 - o2y;
    int bx0 = x1 - o1x;
    int hitB = FUN_008c9ca0(x0 - o1x, y0 - o1y, bx0, by1, bx1, by2, x2 - o2x, y2 - o2y,
                              (short*)&ixB, (short*)&iyB);

    uint32_t px, py;
    AddPointFn add;
    if (cross > 0) {
        px = ixB & 0xffff;
        py = iyB & 0xffff;
        if (hitA == 0 && outer != 0) {
            FUN_008c9b70_s008c_9e00(st, x1 + o1x, y1 + o1y, outer, x1 + o2x, y1 + o2y, outer);
        } else {
            addPointA(st, ixA, iyA, outer);
        }
        add = addPointB;
        o2y = -o2y;
        o2x = -o2x;
        o1y = -o1y;
        o1x = -o1x;
    } else {
        px = ixA & 0xffff;
        py = iyA & 0xffff;
        if (hitB == 0 && outer != 0) {
            addPointB(st, bx0, by1, outer);
            addPointB(st, bx1, by2, outer);
        } else {
            addPointB(st, ixB, iyB, outer);
        }
        add = addPointA;
    }

    if (joinType == 0 || outer == 0) {
        int d = FUN_008c9c40_s008c_9e00((short)px - x1, (short)py - y1);
        if (d <= w2 || outer == 0) {
            add(st, px, py, outer);
            return;
        }
    } else {
        if (joinType == 1) {
            // round-ish join: a short extension along the miter direction closes the corner
            int ey = (short)((short)py - (short)y1);
            int ex = (short)((short)px - (short)x1);
            int d = FUN_008c9c40_s008c_9e00(ex, ey);
            if (d == 0)
                s = 0x10000;
            else
                s = util_FixDiv(w, d);
            uint32_t vx = util_FixMul(ex, s) & 0xffff;
            uint32_t vy = util_FixMul(ey, s) & 0xffff;
            uint32_t cx = x1 + vx & 0xffff;
            uint32_t cy = vy + y1 & 0xffff;
            uint32_t nvy = -(int)vy & 0xffff;
            int c2y = vx + cy;
            int c2x = nvy + cx;
            int l0y = o1y + y1;
            int l0x = o1x + x1;
            short ox1, oy1, ox2, oy2;
            util_ComputeIntersection(x0 + o1x, y0 + o1y, l0x, l0y, cx, cy, c2x, c2y, &ox1, &oy1);
            util_ComputeIntersection(x1 + o2x, y1 + o2y, x2 + o2x, y2 + o2y, cx, cy, c2x, c2y, &ox2, &oy2);
            add(st, l0x, l0y, 1);
            add(st, ox1, oy1, 0);
            add(st, ox2, oy2, 0);
            add(st, x1 + o2x, y1 + o2y, 1);
            return;
        }
        if (joinType != 2)
            return;
    }
    add(st, x1 + o1x, o1y + y1, 1);
    add(st, o2x + x1, o2y + y1, 1);
}

// @ 0x008ca5b0
void EndCap(StrokeState_s008c_9e00__g7* st, int xdir, int ydir, int joinType, int cx, int cy, int w)
{
    int len = FUN_008c9c40_s008c_9e00__g7(2 * ydir, 2 * xdir);
    int s = (len == 0) ? 0x10000 : util_FixDiv(2 * w, len);
    int a = util_FixMul(ydir, s);
    int b = util_FixMul(xdir, s);
    int dd = FUN_008c9c40_s008c_9e00__g7(8 * b, 8 * a);
    if (0 < dd) {
        int w8 = w * 8;
        a = ScaleTo(w8, a, dd);
        b = ScaleTo(w8, b, dd);
    }
    int py = b + cy;                 // iVar4 = iVar3 + param_5
    int px = cx + a;                 // iVar6 = param_4 + iVar1
    int ny = -b;                     // iVar7 = -iVar3
    int u, v;
    if (joinType == 3) {
        v = py - a;
        u = px + b;
        AddTwoPointsA(st, px + ny, a + py, 1, u, v, 1);
        return;
    }
    if (joinType == 0) {
        AddTwoPointsA(st, cx + ny, a + cy, 1, cx + b, cy - a, 1);
        return;
    }
    if (joinType == 1) {
        px = (a + 1) >> 1;
        py = (b + 1) >> 1;
    } else if (joinType != 4) {
        if (joinType == 2) {
            AddTwoPointsA(st, cx + ny, a + cy, 1, px + ny, py + a, 0);
            AddTwoPointsA(st, px + b, py - a, 0, cx + b, cy - a, 1);
        }
        return;
    } else {
        px = (a + 2) >> 2;
        py = (b + 2) >> 2;
    }
    px = px + cx;
    py = py + cy;
    v = py - a;
    AddTwoPointsA(st, px + ny, a + py, 1, px + b, v, 1);
}

// @ 0x008ca760
void glyph_EnsureSpaceForNPoints(Glyph* g, int count)
{
    if (count <= g->nPoints)
        return;
    short* oldX = g->xcoords;
    short* oldY = g->ycoords;
    uint8_t* oldT = g->tags;
    short* oldC = g->contour;
    AllocGlyphPointMemory(g, count + 4);
    short* nx = g->xcoords;
    short* ny = g->ycoords;
    uint8_t* nt = g->tags;
    int n = (short)g->lastIndex + 4;
    if (0 < n) {
        for (int i = 0; i < n; i++) {
            nx[i] = oldX[i];
            ny[i] = oldY[i];
            nt[i] = oldT[i];
        }
    }
    Glyph* owner = *(Glyph**)g;
    if (oldC == (short*)((char*)owner + 0x54)) {
        owner->flag8c = 1;
        return;
    }
    tsi_DeAllocMem(owner, oldC);
}

// @ 0x008ca820
bool IsOverExtended(TPath* p)
{
    int n2 = p->n2;
    int n = p->n;
    int iVar7 = n >> 1;
    int local_28 = 0;
    int local_24 = 0;
    if (0 < n) {
        short* ps = p->pts;
        short* base = p->ptsR;
        int iters = (n - 1) / 3 + 1;
        do {
            int idx = (((iVar7 / n) * 2 + 3) / 6) * 3;
            if (n2 <= idx)
                idx = n2 - 3;
            int a = ps[0] - base[idx];
            int b = ps[1] - base[idx + 1];
            a = OverAbs(a);
            b = OverAbs(b);
            idx += ((((n2 + 1) / 2) * 2 + 3) / 6) * 3;
            local_28 += b + a;
            if (n2 <= idx)
                idx -= n2;
            a = ps[0] - base[idx];
            b = ps[1] - base[idx + 1];
            a = OverAbs(a);
            b = OverAbs(b);
            iVar7 += n2 * 3;
            local_24 += b + a;
            ps += 3;
            iters--;
        } while (iters != 0);
    }
    return local_24 <= local_28;
}

// @ 0x008ca980
void glyph_MergePathIntoGlyph(Glyph* g, TPath* p, int reverse)
{
    short start = g->nPoints;
    g->nPoints = start + 1;
    g->tp[start] = g->lastIndex;
    glyph_EnsureSpaceForNPoints(g, (p->n + p->n2) / 3 + g->lastIndex);

    short* cx = g->xcoords;
    short* cy = g->ycoords;
    uint8_t* ct = g->tags;
    int idx = g->tp[start];
    uint8_t* src = (uint8_t*)p->pts;

    int n = p->n;
    if (0 < n) {
        for (int i = 0; i < n; i += 3) {
            cx[idx] = *(short*)(src + i * 2);
            cy[idx] = *(short*)(src + i * 2 + 2);
            ct[idx] = src[(i + 2) * 2];
            idx++;
        }
    }

    uint8_t* srcR = (uint8_t*)p->ptsR;
    int n2 = p->n2;
    if (reverse == 0) {
        if (!IsOverExtended(p)) {
            for (int k = n2 - 1; k >= 0; k -= 3) {
                ct[idx] = srcR[k * 2];
                cx[idx] = *(short*)(srcR + (k - 1) * 2);
                cy[idx] = *(short*)(srcR + (k - 2) * 2);
                idx++;
            }
        } else {
            for (int k = 0; k < n2; k += 3) {
                cx[idx] = *(short*)(srcR + k * 2);
                cy[idx] = *(short*)(srcR + k * 2 + 2);
                ct[idx] = srcR[(k + 2) * 2];
                idx++;
            }
        }
    } else {
        for (int k = n2 - 1; k >= 0; k -= 3) {
            ct[idx] = srcR[k * 2];
            cx[idx] = *(short*)(srcR + (k - 1) * 2);
            cy[idx] = *(short*)(srcR + (k - 2) * 2);
            idx++;
        }
    }

    int last = idx - 1;
    g->contour[start] = (short)last;
    g->lastIndex = (short)idx;
    g->contour[start] = (short)last;
}

// @ 0x008caba0
void FUN_008caba0(int contourIndex, GlyphClass* dst, int a, int b, int c, int d, GlyphClass* g)
{
    tsiMemObject_s008c_aba0* mem = g->mem;
    int flag = d;
    int closed = 0;
    StrokeState_s008c_aba0* st;
    int start, end, count, x0, y0, x1, y1, i;
    st = (StrokeState_s008c_aba0*)tsi_AllocMem(mem, 0x28);
    st->mem = mem;
    st->nA = 0;
    st->capA = 0x100;
    st->nB = 0;
    st->capB = 0x100;
    st->ptsA = (int16*)tsi_AllocMem(mem, 0x200);
    st->ptsB = (int16*)tsi_AllocMem(mem, st->capB * 2);
    st->lastIndex = -1;
    start = g->sp[contourIndex];
    end = g->ep[contourIndex];
    count = end - start + 1;
    if (count > 1) {
        x0 = g->oox[start];
        y0 = g->ooy[start];
        if (flag != 0) {
            int last = start + count - 1;
            if (x0 == g->oox[last] && y0 == g->ooy[last]) {
                flag = 0;
                closed = 1;
            }
        }
        x1 = g->oox[start + 1];
        y1 = g->ooy[start + 1];
        i = start + 2;
        if (flag == 0) {
            end -= closed;
            lineJoin(st, b, g->oox[end], g->ooy[end], x0, y0, g->onCurve[start], start, x1, y1, a);
        } else {
            FUN_008ca5b0(st, c, x0, y0, a);
        }
        while (i <= g->ep[contourIndex]) {
            int prevX = x1;
            int px = g->oox[i];
            int py = g->ooy[i];
            lineJoin(st, b, x0, y0, prevX, y1, g->onCurve[i - 1], i - 1, px, py, a);
            y0 = y1;
            i++;
            x0 = prevX;
            y1 = py;
            x1 = px;
        }
        if (flag == 0) {
            int e = g->ep[contourIndex];
            int first = g->sp[contourIndex] + closed;
            lineJoin(st, b, x0, y0, x1, y1, g->onCurve[e], e, g->oox[first], g->ooy[first], a);
        } else {
            FUN_008ca5b0(st, c, x1, y1, a);
        }
        FUN_008ca980(st, dst, flag);
    }
    tsi_DeAllocMem(mem, st->ptsA);
    tsi_DeAllocMem(mem, st->ptsB);
    tsi_DeAllocMem(mem, st);
}

// @ 0x008cae30
void ApplyHintsToStrokeGlyph(GlyphClass* g, int32 xScale, int32 yScale, int flag, int32 v)
{
    uint8 used[128];
    int pass;
    for (pass = 0; pass < 2; pass++) {
        int32 scale;
        int32 m;
        int16 s;
        int16* coords;
        uint32 t;
        uint32 phase;
        int contour;
        if (pass == 0) {
            scale = yScale;
            m = util_FixMul_s008c_aba0(v * 2, yScale);
            s = (int16)util_FixDiv_s008c_aba0(0x40, yScale);
            coords = g->ooy;
        } else {
            scale = xScale;
            m = util_FixMul_s008c_aba0(v * 2, xScale);
            s = (int16)util_FixDiv_s008c_aba0(0x40, xScale);
            coords = g->oox;
        }
        t = (uint32)(m + 0x20);
        if ((int)t < 0x40)
            t = 0x40;
        phase = (t >> 1) & 0x20;
        if (flag == 0) {
            int k;
            for (k = 0; k < 0x20; k += 4) {
                *(uint32*)(used + k * 4) = 0;
                *(uint32*)(used + (k + 1) * 4) = 0;
                *(uint32*)(used + (k + 2) * 4) = 0;
                *(uint32*)(used + (k + 3) * 4) = 0;
            }
        }
        for (contour = 0; contour < g->contourCountMax; contour++) {
            int start = g->sp[contour];
            int end = g->ep[contour];
            int16 prev = coords[start];
            int i = start + 1;
            while (i <= end) {
                int16 cur = coords[i];
                if ((uint16)((prev - cur) + 1) < 3) {
                    uint32 a = util_FixMul_s008c_aba0(prev, scale);
                    uint32 b;
                    uint32 idx;
                    if (phase == 0)
                        b = (a + 0x20) & 0xffffffc0;
                    else
                        b = (a & 0xffffffc0) + 0x20;
                    idx = (int)b >> 6;
                    if (flag != 0 || (used[idx & 0x7f] == 0 && used[(idx - 1) & 0x7f] == 0 &&
                                      used[(idx + 1) & 0x7f] == 0)) {
                        int16 d = (int16)b - (int16)a;
                        if (d < 0)
                            prev = (int16)(prev - (int16)((0x20 - (int)d * (int)s) >> 6));
                        else
                            prev = (int16)(prev + (int16)(((int)d * (int)s + 0x20) >> 6));
                        coords[i - 1] = prev;
                        coords[i] = prev;
                    }
                    used[idx & 0x7f] = 1;
                }
                prev = cur;
                i++;
            }
        }
    }
}

// @ 0x008cb070
GlyphClass* ff_glyph_StrokeGlyph(GlyphClass* g, int32 a, int b, int c, int d)
{
    GlyphClass* ng = New_EmptyGlyph(g->mem, 0, 0, 0, 0);
    int16 n = g->contourCountMax * 2;
    int i, gp, np;
    ng->contourCount = n;
    if (n <= 8) {
        ng->sp = ng->spBuffer;
        ng->ep = ng->spBuffer + 8;
    } else {
        int16* arr = (int16*)tsi_AllocMem(ng->mem, n * 4);
        ng->sp = arr;
        ng->ep = arr + n;
    }
    ng->ep[0] = 0;
    ng->sp[0] = 0;
    ng->contourCountMax = 0;
    for (i = 0; i < g->contourCountMax; i++)
        FUN_008caba0(i, ng, a, b, c, d, g);
    gp = g->pointCount;
    np = ng->pointCount;
    ng->ooy[np] = g->ooy[gp];
    ng->oox[np] = g->oox[gp];
    ng->ooy[np + 1] = g->ooy[gp + 1];
    ng->oox[np + 1] = g->oox[gp + 1];
    ng->ooy[np + 2] = g->ooy[gp + 2];
    ng->oox[np + 2] = g->oox[gp + 2];
    ng->ooy[np + 3] = g->ooy[gp + 3];
    ng->oox[np + 3] = g->oox[gp + 3];
    Delete_GlyphClass(g);
    return ng;
}

// @ 0x008cb450
uint32 ReadLowUnsignedNumber(InputStream* in)
{
    uint32 acc = 0;
    int shift = 0;
    for (;;) {
        uint8 b = ReadUnsignedByteMacro(in);
        if (b < 0xf0)
            return ((uint32)b << shift) | acc;
        acc |= (uint32)(b - 0xf0) << shift;
        shift += 4;
    }
}

// @ 0x008cb5e0
InputStream* GetGlyphStream(T2KSFont* font, int glyphIndex, int* len)
{
    InputStream* stream = 0;
    int length = 0;
    uint8* dir = GetTableDirEntry_sfntClass(font, 0x676c7966);   // 'glyf'
    void* sloc = font->sloc;
    if (dir != 0 && sloc != 0 && glyphIndex >= 0 && glyphIndex < font->numGlyphs) {
        uint32 savedPos = Tell_InputStream(font->in);
        int32 start = FF_SLOC_MapIndexToOffset(sloc, font->in, glyphIndex);
        int32 end = FF_SLOC_MapIndexToOffset(sloc, font->in, glyphIndex + 1);
        length = end - start;
        Seek_InputStream(font->in, savedPos);
        stream = New_InputStream2(font->mem, font->in, *(uint32*)(dir + 8) + start, length, 2, 0);
    }
    *len = length;
    return stream;
}
