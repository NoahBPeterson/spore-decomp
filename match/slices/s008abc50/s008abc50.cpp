// Slice s008abc50 — 0x008abc50 .. 0x008acb50, FontFusion Type-1 hinting engine
// (module "EA-UTF", object UTFSpore_Win32/fft1hint.obj / type1.obj).
//
// Two groups:
//  * FFT1HintClass hint setup/rounding helpers (0x008abc50 .. 0x008ac070) — see
//    src/game/UTFSpore_Win32/fft1hint.cpp for the same class.
//  * Type-1 charstring interpreter state + orthogonal-matrix opcodes
//    (0x008ac1a0 .. 0x008acb50).  The interpreter state lives in a 0xa0-byte
//    "decode context" whose first 0x60 bytes are a shared TM_State prefix
//    (same prefix as src/game/UTFSpore_Win32/t2k.cpp uses), the opcode
//    dispatch table at +0x50 and the operand stack at +0x6c.
//
// Compile with /O2 /MD /Gy /TP /arch:SSE /fp:fast (all functions are leaf or
// simple-call; the module's own codegen is VS2008 SP1).

typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;

struct tsiMemObject;

// FontFusion fixed-point helpers.
extern "C" int util_FixMul(int a, int b);                     // 0x008d1590
extern "C" int util_FixDiv(int a, int b);                     // 0x008d16d0
extern "C" int util_ShortFracMul(int a, int b);               // 0x008d1670
extern "C" int util_EuclidianDistance(int a, int b);          // 0x008d17d0
extern "C" void __cdecl longjmp(int* buf, int val);

// ===========================================================================
// FFT1HintClass (retail layout, 0x378 bytes — matches the dev PDB)
// ===========================================================================
struct blueZone_tag { int minPix; int maxPix; int refPix; };
struct stemSnap_tag { int minPix; int maxPix; int refPix; };

struct FFT1HintClass {                  // size 0x378
    tsiMemObject* mem;                  // +0x000
    int xPixelsPerEm;                   // +0x004
    int yPixelsPerEm;                   // +0x008
    int xScale;                         // +0x00c
    int yScale;                         // +0x010
    int xpos;                           // +0x014
    int ypos;                           // +0x018
    int upem;                           // +0x01c
    blueZone_tag pBlueZones[14];        // +0x020
    int bluevalues[14];                 // +0x0c8
    int numBlueValues;                  // +0x100
    int BlueFuzz;                       // +0x104
    int BlueScale;                      // +0x108
    int BlueShift;                      // +0x10c
    int BlueShiftPix;                   // +0x110
    stemSnap_tag pSnapV[12];            // +0x114
    stemSnap_tag pSnapH[12];            // +0x1a4
    int snapHWVals[12];                 // +0x234
    int snapVWVals[12];                 // +0x264
    int numSnapV;                       // +0x294
    int numSnapH;                       // +0x298
    int numSnapVZones;                  // +0x29c
    int numSnapHZones;                  // +0x2a0
    int StdHW;                          // +0x2a4
    int StdVW;                          // +0x2a8
    short numHintSets;                  // +0x2ac
    short* hintmarkers_x_ptr;           // +0x2b0
    short  hintmarkers_x_ml;            // +0x2b4
    short  num_hintmarkers_x;           // +0x2b6
    short* hintmarkers_y_ptr;           // +0x2b8
    short  hintmarkers_y_ml;            // +0x2bc
    short  num_hintmarkers_y;           // +0x2be
    short* xgcount_ptr;                 // +0x2c0
    short  xgcount_ml;                  // +0x2c4
    short  num_xgcount;                 // +0x2c6
    short* ygcount_ptr;                 // +0x2c8
    short  ygcount_ml;                  // +0x2cc
    short  num_ygcount;                 // +0x2ce
    short* xbgcount_ptr;                // +0x2d0
    short  xbgcount_ml;                 // +0x2d4
    short  numxbgcount;                 // +0x2d6
    short* ybgcount_ptr;                // +0x2d8
    short  ybgcount_ml;                 // +0x2dc
    short  numybgcount;                 // +0x2de
    short* xOrus_ptr;                   // +0x2e0
    short  xOrus_num_ml;                // +0x2e4
    short  numxOrus;                    // +0x2e6
    short* yOrus_ptr;                   // +0x2e8
    short  yOrus_num_ml;                // +0x2ec
    short  numyOrus;                    // +0x2ee
    short* nxIntOrus_ptr;               // +0x2f0
    short  xInt_num_ml;                 // +0x2f4
    short  numxIntOrus;                 // +0x2f6
    short* nyIntOrus_ptr;               // +0x2f8
    short  yInt_num_ml;                 // +0x2fc
    short  numyIntOrus;                 // +0x2fe
    void*  x_hints;                     // +0x300  (hints_t*)
    void*  y_hints;                     // +0x304  (hints_t*)
    void*  x_strokes;                   // +0x308  (extraStroke_t*)
    void*  y_strokes;                   // +0x30c  (extraStroke_t*)
    short num_x_hint_sets_ml;           // +0x310
    short num_y_hint_sets_ml;           // +0x312
    void*  x_edges;                     // +0x314  (extraEdge_t*)
    void*  y_edges;                     // +0x318
    int onepix;                         // +0x31c
    int pixrnd;                         // +0x320
    int pixfix;                         // +0x324
    int suppressOvershoots;             // +0x328
    short* extraXStrokeOrus_ptr;        // +0x32c
    short  extraXStrokeOrus_ml;         // +0x330
    short  numextraXStroke;             // +0x332
    short* extraYStrokeOrus_ptr;        // +0x334
    short  extraYStrokeOrus_ml;         // +0x338
    short  numextraYStroke;             // +0x33a
    short* extraXStrokeGlyphCount_ptr;  // +0x33c
    short  extraXStrokeGlyphCount_ml;   // +0x340
    short  numextraXStrokeGlyphCount;   // +0x342
    short* extraYStrokeGlyphCount_ptr;  // +0x344
    short  extraYStrokeGlyphCount_ml;   // +0x348
    short  numextraYStrokeGlyphCount;   // +0x34a
    short num_tcb;                      // +0x34c
    short numextraXEdge;                // +0x34e
    short numextraYEdge;                // +0x350
    short extraEdgeX_ml;                // +0x352
    short extraEdgeY_ml;                // +0x354
    short* extraXEdgeThresh_ptr;        // +0x358
    short* extraYEdgeThresh_ptr;        // +0x35c
    short* extraXEdgeDelta_ptr;         // +0x360
    short* extraYEdgeDelta_ptr;         // +0x364
    short* extraXEdgeIndex_ptr;         // +0x368
    short* extraYEdgeIndex_ptr;         // +0x36c
    short* extraXEdgeGlyphCount_ptr;    // +0x370
    short* extraYEdgeGlyphCount_ptr;    // +0x374
};

// Retail objects that the migration will place properly; addresses in comments.
extern "C" void SetupStemWeights(FFT1HintClass* h, int scale, int* src, int count,
                                 int refWidth, int* out, int* pNum);       // 0x008a7c90
extern "C" void SetupInput(FFT1HintClass* h);                              // 0x008a9220
extern "C" void SetInterpolation(FFT1HintClass* h);                        // 0x008a7e30

// Rounding modes of the BlueValues snapping (the fnt_* free functions below).
extern "C" unsigned int fnt_RoundToGrid(int d, int a, int b);              // 0x008ac040
extern "C" unsigned int fnt_RoundToHalfGrid(int d, int a, int b);          // 0x008ac070
extern "C" unsigned int FUN_008abfb0(int d, int a, int b);                 // 0x008abfb0extern "C" unsigned int FUN_008abfe0(int d, int a, int b);                 // 0x008abfe0
extern "C" unsigned int FUN_008ac010(int d, int a, int b);                 // 0x008ac010extern "C" int FUN_008ac360(int d, int a, int b);                          // 0x008ac360
extern "C" int FUN_008ac0b0(void* st, int d, int a);                       // 0x008ac0b0
extern "C" int FUN_008ac100(void* st, int d, int a);                       // 0x008ac100
extern "C" int FUN_010cca50(int h, int d, int a);                          // 0x010cca50

// ===========================================================================
// Type-1 interpreter state
// ===========================================================================
// Shared TM_State prefix (same as t2k.cpp): curve [0x00..0x0b], cx [0x0c],
// cy [0x10], flags [0x14], stack pointer [0x20].  The 32-bit scale field sits
// at [0x1c] in the vector/opcode frames (FUN_008ac0b0 masks it over the stack).
struct TM_State {                       // shared prefix, size >= 0x24
    int   curve[3];                     // +0x00 (three 4-byte values)
    int*  cx;                           // +0x0c  x coordinate array pointer
    int*  cy;                           // +0x10  y coordinate array pointer
    short opFlags;                      // +0x14
    short pad16;
    int   vec1;                         // +0x18
    int   scale;                        // +0x1c
    int*  sBase;                        // +0x20  operand stack base (grows down)
};

struct T1Exec {                         // full charstring decode context, size 0x60
    TM_State s;                         // +0x00
    void*    fp;                        // +0x24  function pointers block / free list
    int      pad28;                     // +0x28
    int      pad2c;                     // +0x2c  == param_5 (interp or no-interp)
    int      pad30;                     // +0x30
    int      pad34;                     // +0x34
    char     opbuf[0x1c];               // +0x38  the 28-byte T1 opcode buffer
    /* +0x38: [0x38] v[0]  [0x3c] vector[0]  [0x40] vector[1]  [0x44] op1
       +0x48: [0x48] op2    [0x4c] op3       [0x50] interp */
};

struct T1Ops {                          // pointer block at T1Exec::fp
    void* fn[11];                       // +0x00 .. +0x28
    void* move[2];                      // +0x2c, +0x30   (MovePoint / duplicate)
    void* ops[14];                      // +0x34 .. +0x68:
    //  +0x34 op0 (calloc)      +0x38 op1 (calloc)      +0x3c op2 (calloc)
    //  +0x40 op3 (calloc)      +0x44 fnt_MovePoint      +0x48 project/pair
    //  +0x4c project/pair       +0x50 stack-copy table  +0x54 op4 (calloc)
    //  +0x58 op5 (calloc)      +0x5c fnt_GetSingleWidthSlow
    //  +0x60 singleWidth
};

// T1 opcode-buffer payload: the 28 bytes described above, starting at +0x38.
struct T1Vec {
    int   v0;                           // +0x00 (frame +0x38)
    short vec0;                         // +0x04 (frame +0x3c)
    short pad06;
    short vec1;                         // +0x08 (frame +0x40)
    short pad0a;
    union {
        void* op[3];                    // +0x0c/0x10/0x14 (frame +0x44/48/4c)
        struct { short x; short y; } v14;   // +0x0c (frame +0x44)
        struct { short x; short y; } v18;   // +0x10 (frame +0x48)
        struct { short x; short y; } v1c;   // +0x14 (frame +0x4c)
    };
};

// calloc-like helper used to fill the opcode buffer (retail 0x0120f9b0).
extern "C" void* FUN_0120f9b0(void* dst, int size);                        // 0x0120f9b0
// cblock / setjmp3 (retail 0x011e0cac), as used by the other EA-UTF readers.
extern "C" int __cdecl setjmp3(void* jb, int arg);                         // 0x011e0cac

// --------------------------------------------------------------------------
// FFT1HintClass: global blue-zone / snap setup
// --------------------------------------------------------------------------
// @ 0x008abc50
void SetupGlobalHints(FFT1HintClass* h, int numBlue, int* blueVals, int blueFuzz,
                      int blueScale, int blueShift, int* stds, int* stems,
                      int numStems, int refHV, int nSnap, int* snapVals,
                      int nSnap2, int* snapVals2)
{
    int i;

    h->numBlueValues = numBlue;
    h->bluevalues[0] = blueVals[0];
    h->bluevalues[1] = blueVals[1];
    h->BlueFuzz = blueFuzz;
    h->BlueScale = blueScale;
    h->BlueShift = blueShift;
    h->BlueShiftPix = util_FixMul(blueShift, h->yScale);

    for (i = 0; i < numBlue; i++)
        h->bluevalues[i] = blueVals[i];

    int numZones = numBlue >> 1;
    for (i = 0; i < numBlue; i += 2) {
        short lo = (i == 0) ? 0 : (short)h->bluevalues[i];
        h->pBlueZones[i / 2].maxPix = util_FixMul((int)lo, h->yScale);
        h->pBlueZones[i / 2].minPix =
            util_FixMul((int)(short)(h->bluevalues[i] - h->BlueFuzz), h->yScale);
        h->pBlueZones[i / 2].refPix =
            util_FixMul((int)(short)(h->bluevalues[i + 1] + h->BlueFuzz), h->yScale);
    }

    // Bubble-sort the zones by minPix.
    int k = numZones - 2;
    bool swapped;
    do {
        swapped = false;
        for (int j = k; j >= 0; j--) {
            blueZone_tag* z = &h->pBlueZones[j];
            if (z[1].minPix < z[0].minPix) {
                int lo1 = z[0].minPix, hi1 = z[0].maxPix, rf1 = z[0].refPix;
                z[0] = z[1];
                z[1].minPix = lo1;
                z[1].maxPix = hi1;
                z[1].refPix = rf1;
                swapped = true;
            }
        }
    } while (swapped);

    // Shrink each zone to a pixel (a "TCB") when vertical strict zones are on.
    if (h->num_tcb > 0 && numZones > 0) {
        int lim = h->pBlueZones[0].maxPix - 0x10;
        if (h->pBlueZones[0].minPix > lim)
            h->pBlueZones[0].minPix = lim;
        for (int j = 1; j < numZones; j++) {
            blueZone_tag* z = &h->pBlueZones[j];
            int mid = (z->minPix + z->refPix) >> 1;
            int a0 = z->maxPix + 0x10;
            if (a0 > mid) a0 = mid;
            if (z->minPix < a0) z->minPix = a0;
            int a1 = z->refPix - 0x10;
            if (a1 < mid) a1 = mid;
            if (z->refPix > a1) z->refPix = a1;
        }
        int a2 = h->pBlueZones[numZones].minPix + 0x10;
        if (h->pBlueZones[numZones].maxPix < a2)
            h->pBlueZones[numZones].maxPix = a2;
    }

    // Bubble-sort again (the snap above can reorder neighbours).
    do {
        swapped = false;
        for (int j = k; j >= 0; j--) {
            blueZone_tag* z = &h->pBlueZones[j];
            if (z[1].minPix < z[0].minPix) {
                int lo1 = z[0].minPix, hi1 = z[0].maxPix, rf1 = z[0].refPix;
                z[0] = z[1];
                z[1].minPix = lo1;
                z[1].maxPix = hi1;
                z[1].refPix = rf1;
                swapped = true;
            }
        }
    } while (swapped);

    if (h->num_tcb > 0)
        h->suppressOvershoots = h->yPixelsPerEm - h->BlueScale < 0;
    else
        h->suppressOvershoots =
            h->yPixelsPerEm - util_FixMul(h->BlueScale, h->upem) < 0;

    // Standard widths and snap zones.
    if (nSnap < 1) {
        h->numSnapV = 0;
    } else {
        for (i = 0; i < nSnap; i++)
            h->snapVWVals[i] = snapVals[i];
        h->numSnapV = nSnap;
    }
    if (nSnap2 < 1) {
        h->numSnapH = 0;
    } else {
        for (i = 0; i < nSnap2; i++)
            h->snapHWVals[i] = snapVals2[i];
        h->numSnapH = nSnap2;
    }
    h->StdHW = stds[0];
    h->StdVW = stds[1];

    SetupStemWeights(h, h->xScale, h->snapVWVals, h->numSnapV, stds[1],
                     (int*)h->pSnapV, &h->numSnapVZones);
    SetupStemWeights(h, h->yScale, h->snapHWVals, h->numSnapH, h->StdHW,
                     (int*)h->pSnapH, &h->numSnapHZones);
    SetupInput(h);
}

// ===========================================================================
// Blue-value snapping / rounding modes (free functions)
// ===========================================================================
// The three "round a distance d to a grid" modes share one shape: the
// un-rounded result is out (out is 0 when the value cannot be represented).
#define GRID_ROUND(NAME, UNIT, BIAS0, BIAS1)                                   \
    uint32 r;                                                                  \
    if (d < 0)                                                                 \
        r = (uint32)(-(int)((unsigned)(a - d + BIAS0) & (0u - (uint32)UNIT))); \
    else                                                                       \
        r = (uint32)((a + d + BIAS1) & (0u - (uint32)UNIT));                   \
    if ((int)(r ^ (uint32)d) < 0 && d != 0)                                    \
        r = 0;                                                                 \
    return r;

// @ 0x008abf90  (BlueShiftPix bookkeeping; the original tail-calls longjmp so
// it is not reproducible in a normal function)
void* fnt_SuperRound_Err(FFT1HintClass* h)
{
    longjmp((int*)((char*)h + 0x5c), 0x1101);
    return 0;
}

// @ 0x008abfe0
uint32 FUN_008abfe0(int unused, int d, int a)
{
    (void)unused;
    uint32 r;
    if (d < 0) {
        r = (uint32)(0u - ((unsigned)(a - d) & 0xffffffc0u));
    } else {
        r = (uint32)((a + d) & 0xffffffc0u);
    }
    if ((int)(r ^ (uint32)d) < 0 && d != 0)
        r = 0;
    return r;
}

// @ 0x008ac010
uint32 FUN_008ac010(int unused, int d, int a)
{
    (void)unused;
    uint32 r;
    if (d < 0)
        r = (uint32)(0u - ((unsigned)(0x3f + (a - d)) & 0xffffffc0u));
    else
        r = (uint32)((d + a + 0x3f) & 0xffffffc0u);
    if ((int)(r ^ (uint32)d) < 0 && d != 0)
        r = 0;
    return r;
}

// @ 0x008ac040
uint32 fnt_RoundToGrid(int unused, int d, int a)
{
    (void)unused;
    uint32 r;
    if (d < 0)
        r = (uint32)(0u - ((unsigned)(0x20 + (a - d)) & 0xffffffc0u));
    else
        r = (uint32)((d + a + 0x20) & 0xffffffc0u);
    if ((int)(r ^ (uint32)d) < 0 && d != 0)
        r = 0;
    return r;
}

// @ 0x008ac070
uint32 fnt_RoundToHalfGrid(int unused, int d, int a)
{
    (void)unused;
    uint32 r;
    if (d < 0)
        r = (uint32)(0xffffffe0u - ((unsigned)(a - d) & 0xffffffc0u));
    else
        r = (uint32)(((a + d) & 0xffffffc0u) + 0x20);
    if ((int)(r ^ (uint32)d) < 0 && d != 0)
        r = (uint32)(((d < 1 ? 0 : -1) & 0x40) - 0x20);
    return r;
}

// ===========================================================================
// Type-1 interpreter state
// ===========================================================================
// @ 0x008abfb0
uint32 FUN_008abfb0(int unused, int d, int a)
{
    (void)unused;
    uint32 r;
    if (d < 0)
        r = (uint32)(0u - ((unsigned)(0x10 + (a - d)) & 0xffffffe0u));
    else
        r = (uint32)((d + a + 0x10) & 0xffffffe0u);
    if ((int)(r ^ (uint32)d) < 0 && d != 0)
        r = 0;
    return r;
}

// @ 0x008ac0b0  (a division-like blue-zone rounding mode)
int FUN_008ac0b0(void* st, int d, int a)
{
    int* p  = *(int**)((char*)st + 0x28);
    int  c8 = *(int*)((char*)p + 0x80) - *(short*)((char*)p + 0x7e);
    int  m  = *(int*)((char*)p + 0x74);
    int  e  = *(short*)((char*)p + 0x7e);
    int  r;
    if (d < 0) {
        r = 0u - (((unsigned)(c8 - d + a) & (unsigned)m) + e);
    } else {
        r = ((unsigned)(c8 + d + a) & (unsigned)m) + e;
    }
    if ((r ^ d) < 0 && d != 0)
        r = (e < 1) ? (d < 1 ? e : -e) : e;
    return r;
}

// @ 0x008ac100  (fnt_Super45Round)
int FUN_008ac100(void* st, int d, int a)
{
    int* p  = *(int**)((char*)st + 0x28);
    int  c8 = *(int*)((char*)p + 0x80) - *(short*)((char*)p + 0x7e);
    int  u  = *(int*)((char*)p + 0x74) >> 14;
    int  e  = *(short*)((char*)p + 0x7e);
    int  r;
    if (d < 0)
        r = -(util_FixMul(util_FixDiv(c8 - d + a, u) & 0xffffffc0, u) + e);
    else
        r = util_FixMul(util_FixDiv(c8 + d + a, u) & 0xffffffc0, u) + e;
    if ((r ^ d) < 0 && d != 0)
        r = (e < 1) ? (d < 1 ? e : -e) : e;
    return r;
}

// @ 0x008ac1a0  (fnt_MovePoint)
// (state, idx, delta, flag): moves the point at `idx` by `delta` along the
// current x/y axis, using the direct short-fraction path when the axis scale is
// exactly 0x4000 and the fixmul/fixdiv path otherwise.
void fnt_MovePoint(void* st, int idx, int delta, int flag)
{
    int   v0 = *(unsigned short*)((char*)st + 0x18);
    int   v1 = *(unsigned short*)((char*)st + 0x1a);
    short dy = *(short*)((char*)st + 0x40);
    void** sp    = (void**)st;
    int*   cx    = (int*)sp[0];
    int*   cy    = (int*)sp[1];
    char*  marks = (char*)sp[10];

    if (dy == 0x4000) {
        if (v0 != 0) {
            cx[idx] += util_ShortFracMul(delta, v0);
            marks[idx] |= 1;
        }
        if (v1 != 0) {
            cy[idx] += util_ShortFracMul(delta, v1);
            marks[idx] |= 2;
        }
    } else {
        if (v0 != 0) {
            cx[idx] += (util_FixMul(delta, util_FixDiv((short)v0 << 4, (int)dy)) + 4) >> 4;
            marks[idx] |= 1;
        }
        if (v1 != 0) {
            cy[idx] += (util_FixMul(delta, util_FixDiv((short)v1 << 4, (int)dy)) + 4) >> 4;
            marks[idx] |= 2;
        }
    }
}

// @ 0x008ac2a0
int* FUN_008ac2a0(int unused, void** st, int idx, int delta)
{
    int*  p = (int*)*st + idx;
    int*  m;
    (void)unused;
    *p += delta;
    m = (int*)st[10];
    *((char*)m + idx) |= 1;
    return (int*)((char*)m + idx);
}

// @ 0x008ac2d0
int* FUN_008ac2d0(int unused, void** st, int idx, int delta)
{
    int*  p = (int*)st[1] + idx;
    int*  m;
    (void)unused;
    *p += delta;
    m = (int*)st[10];
    *((char*)m + idx) |= 2;
    return (int*)((char*)m + idx);
}

// @ 0x008ac300  (fnt_Project)
int fnt_Project(void* st, int x, int y)
{
    return util_ShortFracMul(x, *(unsigned short*)((char*)st + 0x14)) +
           util_ShortFracMul(y, *(unsigned short*)((char*)st + 0x16));
}

// @ 0x008ac330  (fnt_OldProject)
int fnt_OldProject(void* st, int x, int y)
{
    return util_ShortFracMul(x, *(unsigned short*)((char*)st + 0x1c)) +
           util_ShortFracMul(y, *(unsigned short*)((char*)st + 0x1e));
}

// @ 0x008ac370  (fnt_GetCVTScale) — the vector state is the first argument.
int fnt_GetCVTScale(T1Exec* s)
{
    int  cx = *(unsigned short*)((char*)s + 0x14);
    int* p  = *(int**)((char*)s + 0x28);
    int  cy = *(unsigned short*)((char*)s + 0x16);
    int  a, b;

    if (cy == 0)
        return *(int*)((char*)p + 0xb8);
    if (cx == 0)
        return *(int*)((char*)p + 0xbc);
    a = util_ShortFracMul(*(int*)((char*)p + 0xbc), (cy * cy + 0x2000) >> 14);
    b = util_ShortFracMul(*(int*)((char*)p + 0xb8), (cx * cx + 0x2000) >> 14);
    return b + a;
}

// @ 0x008ac3e0
int FUN_008ac3e0(T1Exec* s, int idx)
{
    return *(int*)(*(int*)(*(int*)((char*)s + 0x28) + 8) + idx * 4);
}

// @ 0x008ac400  (fnt_GetCVTEntrySlow)
int fnt_GetCVTEntrySlow(T1Exec* s, int idx)
{
    int v = *(int*)(*(int*)(*(int*)((char*)s + 0x28) + 8) + idx * 4);
    return (util_FixMul(v * 2, fnt_GetCVTScale(s)) + 1) >> 1;
}

// @ 0x008ac430
int FUN_008ac430(T1Exec* s)
{
    return *(int*)(*(int*)((char*)s + 0x28) + 0x60);
}

// @ 0x008ac440  (fnt_GetSingleWidthSlow)
int fnt_GetSingleWidthSlow(T1Exec* s)
{
    return util_FixMul(*(int*)(*(int*)((char*)s + 0x28) + 0x60), fnt_GetCVTScale(s));
}

// @ 0x008ac460  (fnt_ChangeCvt)
int* fnt_ChangeCvt(T1Exec* s, int idx, int delta)
{
    int* p;
    if (*(char*)(*(int*)((char*)s + 0x28) + 0xb6) == 0) {
        int sc = fnt_GetCVTScale(s);
        if (sc != 0x10000 && sc != 0) {
            p = (int*)(*(int*)(*(int*)((char*)s + 0x28) + 8) + idx * 4);
            *p += (util_FixDiv(delta * 2, sc) + 1) >> 1;
            return p;
        }
    }
    p = (int*)(*(int*)(*(int*)((char*)s + 0x28) + 8) + idx * 4);
    *p += delta;
    return p;
}

// Snap a 2.14 projection scale: if it is out of the legal (0x4000-based) range,
// clamp it to +/-0x4000 with the sign of the value.
static inline int SnapProjScale(unsigned short c)
{
    if ((unsigned short)(c + 0x3ff) <= 0x7fe) {
        int t = ((short)c >= 0) ? 1 : 0;
        return ((t - 1) & 0xffff8000) + 0x4000;
    }
    return c;
}

// @ 0x008ac7a0  (fnt_ComputeAndCheck_PF_Proj)
void fnt_ComputeAndCheck_PF_Proj(void* s)
{
    int a = *(short*)((char*)s + 0x1a) * *(short*)((char*)s + 0x16) + 0x2000;
    int b = *(short*)((char*)s + 0x18) * *(short*)((char*)s + 0x14) + 0x2000;
    unsigned short c = (unsigned short)((a >> 14) + (b >> 14));
    if ((unsigned short)(c + 0x3ff) <= 0x7fe)
        c = (unsigned short)SnapProjScale(c);
    *(short*)((char*)s + 0x40) = c;
}

// @ 0x008ac800
void FUN_008ac800(void* s)
{
    *(short*)((char*)s + 0x14) = 0;
    *(short*)((char*)s + 0x18) = 0;
    *(short*)((char*)s + 0x16) = 0x4000;
    *(int*)((char*)s + 0x48) = 0x10cca50;
    *(int*)((char*)s + 0x4c) = 0x10cca50;
    *(short*)((char*)s + 0x1a) = 0x4000;
    *(int*)((char*)s + 0x44) = 0x8ac2d0;
    *(short*)((char*)s + 0x40) = 0x4000;
}
// @ 0x008ac840
void FUN_008ac840(void* s)
{
    *(short*)((char*)s + 0x14) = 0x4000;
    *(short*)((char*)s + 0x16) = 0;
    *(short*)((char*)s + 0x18) = 0x4000;
    *(int*)((char*)s + 0x48) = 0x8ac360;
    *(int*)((char*)s + 0x4c) = 0x8ac360;
    *(short*)((char*)s + 0x1a) = 0;
    *(int*)((char*)s + 0x44) = 0x8ac2a0;
    *(short*)((char*)s + 0x40) = 0x4000;
}

// @ 0x008ac880  (fnt_SPVTCA)
void fnt_SPVTCA(void* s)
{
    if (*(unsigned char*)((char*)s + 4) & 1) {
        *(short*)((char*)s + 0x14) = 0x4000;
        *(short*)((char*)s + 0x16) = 0;
        *(int*)((char*)s + 0x48) = 0x8ac360;
        *(short*)((char*)s + 0x40) = *(short*)((char*)s + 0x18);
    } else {
        *(short*)((char*)s + 0x14) = 0;
        *(short*)((char*)s + 0x16) = 0x4000;
        *(int*)((char*)s + 0x48) = 0x10cca50;
        *(short*)((char*)s + 0x40) = *(short*)((char*)s + 0x1a);
    }
    unsigned short c = *(unsigned short*)((char*)s + 0x40);
    if ((unsigned short)(c + 0x3ff) <= 0x7fe)
        *(short*)((char*)s + 0x40) = (short)SnapProjScale(c);
    *(int*)((char*)s + 0x44) = 0x8ac1a0;
    *(int*)((char*)s + 0x4c) = *(int*)((char*)s + 0x48);
}

// @ 0x008ac900  (fnt_SFVTCA)
void fnt_SFVTCA(void* s)
{
    if (*(unsigned char*)((char*)s + 4) & 1) {
        *(short*)((char*)s + 0x18) = 0x4000;
        *(short*)((char*)s + 0x1a) = 0;
        *(short*)((char*)s + 0x40) = *(short*)((char*)s + 0x14);
    } else {
        *(short*)((char*)s + 0x18) = 0;
        *(short*)((char*)s + 0x1a) = 0x4000;
        *(short*)((char*)s + 0x40) = *(short*)((char*)s + 0x16);
    }
    unsigned short c = *(unsigned short*)((char*)s + 0x40);
    if ((unsigned short)(c + 0x3ff) <= 0x7fe)
        *(short*)((char*)s + 0x40) = (short)SnapProjScale(c);
    *(int*)((char*)s + 0x44) = 0x8ac1a0;
}

// @ 0x008ac970  (fnt_SPVTL)
void fnt_SPVTL(void* s)
{
    int**  sp = (int**)((char*)s + 0x20);
    int    i2, i1, dx, dy, dist;
    int**  m1 = (int**)*(int**)((char*)s + 0x0c);
    int**  m2 = (int**)*(int**)((char*)s + 0x10);

    *sp = (int*)((char*)*sp - 4);
    i2  = **sp;
    *sp = (int*)((char*)*sp - 4);
    i1  = **sp;
    dx = (*(int*)((char*)*m1 + i1 * 4) - *(int*)((char*)*m2 + i2 * 4)) << 10;
    dy = (*(int*)((char*)m1[1] + i1 * 4) - *(int*)((char*)m2[1] + i2 * 4)) << 10;
    dist = util_EuclidianDistance(dx, dy);
    if (dist != 0) {
        dx = util_FixDiv(dx, dist);
        dy = util_FixDiv(dy, dist);
    }
    *(short*)((char*)s + 0x14) = (short)((dx + 1) >> 2);
    *(short*)((char*)s + 0x16) = (short)((dy + 1) >> 2);
    if (*(unsigned char*)((char*)s + 4) & 1) {
        short y0 = *(short*)((char*)s + 0x16);
        short x0 = *(short*)((char*)s + 0x14);
        *(short*)((char*)s + 0x16) = x0;
        *(short*)((char*)s + 0x14) = (short)-y0;
    }
    fnt_ComputeAndCheck_PF_Proj(s);
    *(int*)((char*)s + 0x44) = 0x8ac1a0;
    *(int*)((char*)s + 0x48) = 0x8ac300;
    *(int*)((char*)s + 0x4c) = 0x8ac300;
}

// @ 0x008aca20  (fnt_SDPVTL)
void fnt_SDPVTL(void* s)
{
    int**  sp = (int**)((char*)s + 0x20);
    int    i2, i1, dx, dy, dist;
    int**  m1 = (int**)*(int**)((char*)s + 0x0c);
    int**  m2 = (int**)*(int**)((char*)s + 0x10);
    int    ax, ay;

    *sp = (int*)((char*)*sp - 4);
    i2  = **sp;
    *sp = (int*)((char*)*sp - 4);
    i1  = **sp;
    dx = (*(int*)((char*)*m1 + i1 * 4) - *(int*)((char*)*m2 + i2 * 4)) << 10;
    dy = (*(int*)((char*)m1[1] + i1 * 4) - *(int*)((char*)m2[1] + i2 * 4)) << 10;
    dist = util_EuclidianDistance(dx, dy);
    if (dist != 0) {
        dx = util_FixDiv(dx, dist);
        dy = util_FixDiv(dy, dist);
    }
    *(short*)((char*)s + 0x14) = (short)((dx + 1) >> 2);
    *(short*)((char*)s + 0x16) = (short)((dy + 1) >> 2);

    ax = (*(int*)((char*)m1[2] + i1 * 4) - *(int*)((char*)m2[2] + i2 * 4)) << 10;
    ay = (*(int*)((char*)m1[3] + i1 * 4) - *(int*)((char*)m2[3] + i2 * 4)) << 10;
    dist = util_EuclidianDistance(ax, ay);
    if (dist != 0) {
        ax = util_FixDiv(ax, dist);
        ay = util_FixDiv(ay, dist);
    }
    *(short*)((char*)s + 0x1c) = (short)((ax + 1) >> 2);
    *(short*)((char*)s + 0x1e) = (short)((ay + 1) >> 2);

    if (*(unsigned char*)((char*)s + 4) & 1) {
        short x0 = *(short*)((char*)s + 0x14);
        short y0 = *(short*)((char*)s + 0x16);
        short x1 = *(short*)((char*)s + 0x1c);
        short y1 = *(short*)((char*)s + 0x1e);
        *(short*)((char*)s + 0x14) = (short)-y0;
        *(short*)((char*)s + 0x16) = x0;
        *(short*)((char*)s + 0x1c) = (short)-y1;
        *(short*)((char*)s + 0x1e) = x1;
    }
    fnt_ComputeAndCheck_PF_Proj(s);
    *(int*)((char*)s + 0x44) = 0x8ac1a0;
    *(int*)((char*)s + 0x48) = 0x8ac300;
    *(int*)((char*)s + 0x4c) = 0x8ac330;
}

// @ 0x008acb50  (fnt_SFVTL)
void fnt_SFVTL(void* s)
{
    int**  sp = (int**)((char*)s + 0x20);
    int    i2, i1, dx, dy, dist;
    int**  m1 = (int**)*(int**)((char*)s + 0x0c);
    int**  m2 = (int**)*(int**)((char*)s + 0x10);

    *sp = (int*)((char*)*sp - 4);
    i2  = **sp;
    *sp = (int*)((char*)*sp - 4);
    i1  = **sp;
    dx = (*(int*)((char*)*m1 + i1 * 4) - *(int*)((char*)*m2 + i2 * 4)) << 10;
    dy = (*(int*)((char*)m1[1] + i1 * 4) - *(int*)((char*)m2[1] + i2 * 4)) << 10;
    dist = util_EuclidianDistance(dx, dy);
    if (dist != 0) {
        dx = util_FixDiv(dx, dist);
        dy = util_FixDiv(dy, dist);
    }
    *(short*)((char*)s + 0x18) = (short)((dx + 1) >> 2);
    *(short*)((char*)s + 0x1a) = (short)((dy + 1) >> 2);
    if (*(unsigned char*)((char*)s + 4) & 1) {
        short y0 = *(short*)((char*)s + 0x1a);
        short x0 = *(short*)((char*)s + 0x18);
        *(short*)((char*)s + 0x1a) = x0;
        *(short*)((char*)s + 0x18) = (short)-y0;
    }
    fnt_ComputeAndCheck_PF_Proj(s);
    *(int*)((char*)s + 0x44) = 0x8ac1a0;
}

// @ 0x008ac4c0
void fnt_InterpChars(uint32* st, uint32 ip, uint32 end)
{
    if (st[0xb] != 0) {
        uint32 prev = *st;
        int    tbl  = *(int*)(st[10] + 0x8c);
        *st = ip;
        while ((uint32)*st < end) {
            void* f = *(void**)(st[10] + 0x70);
            short mode;
            if (f == (void*)0x8ac040)
                mode = 1;
            else if (f == (void*)0x8ac070)
                mode = 0;
            else if (f == (void*)0x8abfb0)
                mode = 2;
            else if (f == (void*)0x8abfe0)
                mode = 3;
            else if (f == (void*)0x8ac010)
                mode = 4;
            else if (f == (void*)0x8ac360)
                mode = 5;
            else if (f == (void*)0x8ac0b0)
                mode = 6;
            else if (f == (void*)0x8ac100)
                mode = 7;
            else
                mode = (short)-1;
            *(short*)((char*)st + 0x3c) = mode;
            ((void (__cdecl*)(void*))st[0xb])(st);
            if (st[0xb] == 0)
                break;
            unsigned int op = *(unsigned char*)*st;
            st[1] = op;
            void* h = *(void**)(tbl + op * 4);
            *st += 1;
            ((void (__cdecl*)(void*))h)(st);
        }
        *st = prev;
    }
}

// @ 0x008ac5c0
void fnt_NoInterpChars(uint32* st, uint32 ip, uint32 end)
{
    uint32 prev = *st;
    int    tbl  = *(int*)(st[10] + 0x8c);
    *st = ip;
    while ((uint32)*st < end) {
        unsigned int op = *(unsigned char*)*st;
        st[1] = op;
        void* h = *(void**)(tbl + op * 4);
        *st += 1;
        ((void (__cdecl*)(void*))h)(st);
    }
    *st = prev;
}

// @ 0x008ac600  (fnt_Execute)
//
// The decode context is a 0x64-byte frame built on the stack:
//   +0x00 ip, +0x04 op, +0x08/+0x0c/+0x10 master pointers (all == ctx),
//   +0x14..0x1e the 2x2 matrix (xx,xy,yx,yy) + translation,
//   +0x20 operand stack pointer, +0x24 ctx, +0x28 the font/env object,
//   +0x2c the interpreter callback, +0x3c rounding mode,
//   +0x40 projection scale, +0x44..0x4c point/project ops, +0x50 loop,
//   +0x54/+0x58 the CVT-entry / single-width accessors.
struct T1Decode {
    uint32 ip;          // +0x00
    int    op;          // +0x04
    void*  m0;          // +0x08
    void*  m1;          // +0x0c
    void*  m2;          // +0x10
    short  xx;          // +0x14
    short  xy;          // +0x16
    short  yx;          // +0x18
    short  yy;          // +0x1a
    short  tx;          // +0x1c
    short  ty;          // +0x1e
    int*   sptr;        // +0x20
    void*  ctx;         // +0x24
    char*  env;         // +0x28
    void*  interp;      // +0x2c
    int    z30;         // +0x30
    int    z34;         // +0x34
    int    z38;         // +0x38
    short  mode;        // +0x3c
    short  pad3e;
    short  projScale;   // +0x40
    short  pad42;
    void*  movePoint;   // +0x44
    void*  project;     // +0x48
    void*  dualProject; // +0x4c
    void*  loop;        // +0x50
    void*  cvtEntry;    // +0x54
    void*  singleWidth; // +0x58
};

int fnt_Execute(void* ctx, uint32 ip, uint32 end, char* env, void* interp)
{
    T1Decode d;
    int      cblock[16];
    int      rc;
    void*    t;

    d.z38 = 0;
    d.z34 = 0;
    d.z30 = 0;
    t = *(char*)(env + 0xc8) == 0 ? (char*)ctx + 0x2c : ctx;

    d.m0 = t;
    d.m1 = t;
    d.m2 = t;
    d.ctx = t;
    d.env = env;
    d.xx = 0x4000;
    d.xy = 0;
    d.yx = 0x4000;
    d.yy = 0;
    d.tx = 0x4000;
    d.ty = 0;
    d.project = (void*)0x8ac360;
    d.dualProject = (void*)0x8ac360;
    d.projScale = 0x4000;
    d.movePoint = (void*)0x8ac2a0;
    d.pad42 = 0;
    d.cvtEntry = (void*)0x8ac3e0;
    d.singleWidth = (void*)0x8ac430;

    if (*(unsigned char*)(env + 0xc9) != 1) {
        if (*(unsigned short*)(env + 0x0c) < 2)
            return 0;
        if (*(unsigned char*)(env + 0xb6) == 0) {
            d.cvtEntry = (void*)0x8ac400;
            d.singleWidth = (void*)0x8ac440;
            if (util_FixMul(*(int*)(env + 0x10), *(int*)(env + 0xb8)) < 0x10001)
                return 0;
            if (util_FixMul(*(int*)(env + 0x10), *(int*)(env + 0xbc)) < 0x10001)
                return 0;
        }
        if (*(unsigned char*)(env + 0xc8) == 0 &&
            *(short*)(env + 0x88) != 0) {
            int (*fn)(void*, int) = *(int (**)(void*, int))(env + 0x98);
            *(int*)(env + 0x60) = fn(env, *(short*)(env + 0x88));
        }
    }

    rc = setjmp3(cblock, 0);
    if (rc == 0) {
        *(unsigned short*)(env + 0xca) = 0;
        *(int*)(env + 0xc0) = 0x1432238;
        *(int*)(env + 0xc4) = 0x14322d8;
        d.interp = interp;
        d.loop = interp != 0 ? (void*)0x8ac4c0 : (void*)0x8ac5c0;
        ((void (__cdecl*)(void*, uint32, uint32))d.loop)(&d, ip, end);
        return 0;
    }
    return rc;
}
