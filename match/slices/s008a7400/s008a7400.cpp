// Slice s008a7400 (bfs2 #20), 32-bit MSVC 2008.
// Bitstream FontFusion Type-1 hinting engine (prebuilt module; different codegen from cl 15.00).
// No function here reached byte-exact except the trivial memory-hook setter.
#include <intrin.h>

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

// ---------------------------------------------------------------------------
// memory hooks (FontFusion public API)
// ---------------------------------------------------------------------------
typedef void* (__cdecl *ff_alloc_t)(unsigned);
typedef void  (__cdecl *ff_free_t)(void*);
typedef void* (__cdecl *ff_realloc_t)(void*, unsigned);

ff_alloc_t   g_ff_malloc;
ff_free_t    g_ff_free;
ff_realloc_t g_ff_realloc;

// @ 0x008a7760
void* ff_malloc(unsigned n)
{
    if (g_ff_malloc == 0)
        __debugbreak();
    return g_ff_malloc(n);
}

// @ 0x008a7770
void ff_free(void* p)
{
    if (g_ff_free == 0)
        __debugbreak();
    g_ff_free(p);
}

// @ 0x008a7780
void* ff_realloc(void* p, unsigned n)
{
    if (g_ff_realloc == 0)
        __debugbreak();
    return g_ff_realloc(p, n);
}

// @ 0x008a7790
void ff_set_memfuncs(ff_alloc_t a, ff_free_t f, ff_realloc_t r)
{
    g_ff_malloc = a;
    g_ff_free = f;
    g_ff_realloc = r;
}

// ---------------------------------------------------------------------------
// FontFusion types (real names from the 2008 dev PDB)
// ---------------------------------------------------------------------------
struct tsiMemObject {
    uint32 stamp1;        // +0x00
    int    numPointers;   // +0x04
    int    maxPointers;   // +0x08
    void** base;          // +0x0c
    int    env[16];       // +0x10
    void*  fast_base[7];  // +0x50
    uint32 fast_size[7];  // +0x6c
    int    fast_free[7];  // +0x88
    uint32 ii;            // +0xa4
    uint32 state;         // +0xa8
    uint32 stamp2;        // +0xac
};

struct GlyphClass {
    tsiMemObject* mem;              // +0x00
    short contourCountMax;          // +0x04
    int   pointCountMax;            // +0x08
    int   colorPlaneCount;          // +0x0c
    int   colorPlaneCountMax;       // +0x10
    short ctrBuffer[16];            // +0x14
    short curveType;                // +0x34
    short contourCount;             // +0x36
    short pointCount;               // +0x38
    short* sp;                      // +0x3c
    short* ep;                      // +0x40
    short* oox;                     // +0x44
    short* ooy;                     // +0x48
    uint8* onCurve;                 // +0x4c
    int*  x;                        // +0x50
    int*  y;                        // +0x54
    short* componentData;           // +0x58
    int   componentSize;            // +0x5c
    int   componentSizeMax;         // +0x60
    uint8* hintFragment;            // +0x64
    int   hintLength;               // +0x68
    short xmin;                     // +0x6c
    short ymin;                     // +0x6e
    short xmax;                     // +0x70
    short ymax;                     // +0x72
    char  dropOutControl;           // +0x74
    uint16 myGlyphIndex;            // +0x76
};

struct blueZone_tag { int minPix; int maxPix; int refPix; };
struct stemSnap_tag { int minPix; int maxPix; int refPix; };

struct hints_t {
    short* hint_array;   // +0x00
    short  num_hints_ml; // +0x04
    short  num_hints;    // +0x06
    int*   hint_pix;     // +0x08
    int*   offset_ptr;   // +0x0c
    short* IntOrus;      // +0x10
    int*   mult_ptr;     // +0x14
};

struct extraStroke_t {
    short* hint_array;   // +0x00
    short  num_hints_ml; // +0x04
    short  num_hints;    // +0x06
};

struct extraEdge_t {
    short* EdgeThresh;   // +0x00
    short* EdgeDelta;    // +0x04
    short* EdgeIndex;    // +0x08
    short  numEdges_ml;  // +0x0c
    short  numEdges;     // +0x0e
};

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
    hints_t* x_hints;                   // +0x300
    hints_t* y_hints;                   // +0x304
    extraStroke_t* x_strokes;           // +0x308
    extraStroke_t* y_strokes;           // +0x30c
    short num_x_hint_sets_ml;           // +0x310
    short num_y_hint_sets_ml;           // +0x312
    extraEdge_t* x_edges;               // +0x314
    extraEdge_t* y_edges;               // +0x318
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

// FontFusion helpers / runtime
extern "C" void* tsi_AllocMem(void* mem, unsigned size);          // 0x008d1260
extern "C" int   util_FixMul(int a, int b);                       // 0x008d1590
extern "C" int   util_FixDiv(int a, int b);                       // 0x008d16d0
extern "C" float FUN_008a6430(void* a, void* b);                  // 0x008a6430
extern "C" void  FUN_008a5880(void* a, void* b, void* c, int d);  // 0x008a5880
extern "C" void* operator_new_array(unsigned size);               // 0x011e073e

// ---------------------------------------------------------------------------
// @ 0x008a77b0
void FlipContourDirection(GlyphClass* g, short dir)
{
    short* p0;
    short* p1;
    int*   q0;
    int*   q1;
    if (dir == 0) {
        p0 = g->oox;
        p1 = g->ooy;
    } else {
        q0 = g->x;
        q1 = g->y;
    }
    for (short i = 0; i < g->contourCount; i++) {
        short sp = g->sp[i];
        short ep = g->ep[i];
        short n = (short)((unsigned short)((ep - sp) / 2));
        short j = sp + 1;
        if (dir == 0) {
            while (n--) {
                short t0 = p0[j];
                short t1 = p1[j];
                p0[j] = p0[ep];
                p1[j] = p1[ep];
                p0[ep] = t0;
                p1[ep] = t1;
                j++;
                ep--;
            }
        } else {
            while (n--) {
                int t0 = q0[j];
                int t1 = q1[j];
                q0[j] = q0[ep];
                q1[j] = q1[ep];
                q0[ep] = t0;
                q1[ep] = t1;
                j++;
                ep--;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x008a7c90
void SetupStemWeights(FFT1HintClass* h, int scale, int* src, int count, int refWidth,
                      int* out, int* pNum)
{
    int n = count;
    int i = 0;
    if (count > 0) {
        int* e = out - 2;
        do {
            int v = util_FixMul(src[i], scale);
            int lo = v - 0x10;
            if (i > 0 && lo < e[0]) {
                if (v < e[0]) e[0] = v;
                if (lo < e[1]) lo = e[1];
                lo = (e[0] + lo) >> 1;
                e[0] = lo;
            }
            e[3] = v + 0x10;
            e[2] = lo;
            e[4] = v;
            i++;
            e += 3;
        } while (i < count);
    }
    if (refWidth < 1) {
        *pNum = count;
        return;
    }
    i = util_FixMul(refWidth, scale);
    unsigned u2 = (unsigned)h->onepix;
    if ((int)u2 <= i)
        u2 = (unsigned)(h->pixrnd + i) & (unsigned)h->pixfix;
    int a = i - 0x17;
    if (i - 0x17 <= (int)(u2 - 0x2e)) a = (int)(u2 - 0x2e);
    if (i < a) a = i;
    int b = i + 0x46;
    if ((int)(u2 + 0x58) <= i + 0x46) b = (int)(u2 + 0x58);
    if (b < i) b = i;
    count = 0;
    if (n > 0) {
        int* p3 = out + 1;
        int* p4 = out;
        do {
            if (p3[1] < a || b < p3[1]) {
                count++;
                p4[0] = p3[-1];
                p4[1] = p3[0];
                p4[2] = p3[1];
                p4 += 3;
            } else {
                if (p3[-1] < a) a = p3[-1];
                if (b < p3[0]) b = p3[0];
            }
            p3 += 3;
            n--;
        } while (n != 0);
    }
    int k = count - 1;
    if (k >= 0) {
        int* q = out + count + 2 + k * 2;
        do {
            if (q[-1] <= i) {
                if (k >= 0 && a < out[k * 3 + 1]) a = out[k * 3 + 1];
                break;
            }
            q[0] = q[-3];
            q[1] = q[-2];
            q[2] = q[-1];
            k--;
            q -= 3;
        } while (k >= 0);
    }
    k++;
    if (k < count && out[k * 3] < b)
        b = out[k * 3 + 1];
    int* r = out + k * 3;
    r[2] = i;
    r[1] = b;
    r[0] = a;
    *pNum = count + 1;
}

// ---------------------------------------------------------------------------
// @ 0x008a7930
// FFT1HintClass constructor (allocates the pointer/count scratch arrays).
FFT1HintClass* New_FFT1HintClass(tsiMemObject* mem, short upem)
{
    FFT1HintClass* p = (FFT1HintClass*)tsi_AllocMem(mem, 0x378);
    p->upem = upem;
    p->xPixelsPerEm = -1;
    p->yPixelsPerEm = -1;
    p->xScale = -1;
    p->yScale = -1;
    p->numBlueValues = -1;
    p->BlueFuzz = -1;
    p->BlueShift = -1;
    p->StdHW = -1;
    p->StdVW = -1;
    p->mem = mem;
    p->BlueShiftPix = 0;
    p->numSnapV = 0;
    p->numSnapH = 0;
    p->numSnapVZones = 0;
    p->numSnapHZones = 0;
    p->numHintSets = 0;
    p->onepix = 0x40;
    p->pixrnd = 0x20;
    p->pixfix = -0x40;
    p->xpos = 0;
    p->ypos = 0;
    p->num_tcb = 0;
    p->suppressOvershoots = 1;
    p->numextraXStroke = 0;
    p->numextraYStroke = 0;
    p->numextraXEdge = 0;
    p->numextraYEdge = 0;

    p->xgcount_ptr  = (short*)tsi_AllocMem(mem, 0x28);
    p->xgcount_ml   = 0x14; p->num_xgcount = 0;
    for (int i = 0; i < 10; i++) ((int*)p->xgcount_ptr)[i] = 0;
    p->ygcount_ptr  = (short*)tsi_AllocMem(mem, 0x28);
    p->ygcount_ml   = 0x14; p->num_ygcount = 0;
    for (int i = 0; i < 10; i++) ((int*)p->ygcount_ptr)[i] = 0;
    p->xOrus_ptr    = (short*)tsi_AllocMem(mem, 0x28);
    p->xOrus_num_ml = 0x14; p->numxOrus = 0;
    p->yOrus_ptr    = (short*)tsi_AllocMem(mem, 0x28);
    p->yOrus_num_ml = 0x14; p->numyOrus = 0;
    p->xbgcount_ptr = (short*)tsi_AllocMem(mem, 0x28);
    p->xbgcount_ml  = 0x14; p->numxbgcount = 0;
    for (int i = 0; i < 10; i++) ((int*)p->xbgcount_ptr)[i] = 0;
    p->ybgcount_ptr = (short*)tsi_AllocMem(mem, 0x28);
    p->ybgcount_ml  = 0x14; p->numybgcount = 0;
    for (int i = 0; i < 10; i++) ((int*)p->ybgcount_ptr)[i] = 0;

    p->extraXStrokeOrus_ptr = (short*)tsi_AllocMem(mem, 0x28);
    p->extraXStrokeOrus_ml = 0x14; p->numextraXStroke = 0;
    p->extraYStrokeOrus_ptr = (short*)tsi_AllocMem(mem, 0x28);
    p->extraYStrokeOrus_ml = 0x14; p->numextraYStroke = 0;
    p->extraXStrokeGlyphCount_ptr = (short*)tsi_AllocMem(mem, 0x28);
    p->extraXStrokeGlyphCount_ml = 0x14; p->numextraXStrokeGlyphCount = 0;
    p->extraYStrokeGlyphCount_ptr = (short*)tsi_AllocMem(mem, 0x28);
    p->extraYStrokeGlyphCount_ml = 0x14; p->numextraYStrokeGlyphCount = 0;
    p->extraXEdgeThresh_ptr = (short*)tsi_AllocMem(mem, 0x28);
    p->extraYEdgeThresh_ptr = (short*)tsi_AllocMem(mem, 0x28);
    p->extraXEdgeDelta_ptr  = (short*)tsi_AllocMem(mem, 0x28);
    p->extraYEdgeDelta_ptr  = (short*)tsi_AllocMem(mem, 0x28);
    p->extraXEdgeIndex_ptr  = (short*)tsi_AllocMem(mem, 0x28);
    p->extraYEdgeIndex_ptr  = (short*)tsi_AllocMem(mem, 0x28);
    p->extraXEdgeGlyphCount_ptr = (short*)tsi_AllocMem(mem, 0x28);
    p->extraYEdgeGlyphCount_ptr = (short*)tsi_AllocMem(mem, 0x28);
    return p;
}

// ---------------------------------------------------------------------------
// The remaining three are large glyph-hinting passes over the hint-class scratch
// arrays plus opaque helper structs; only their high-level structure is reproduced.
// ---------------------------------------------------------------------------

// @ 0x008a7400
void FUN_008a7400(void* self, int a2)
{
    // PARTIAL: complex stem/blue-zone fit pass over hintmarkers + x_strokes/y_strokes
    // scratch arrays with a float reference-width search and operator new[] scratch.
    (void)self; (void)a2;
}

// @ 0x008a76e0
void FUN_008a76e0(int a1, void* a2, int a3, int a4, int a5)
{
    // PARTIAL: dispatch wrapper building a 0x430-byte scratch record and branching on
    // a tag field, then calling the setup passes.
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5;
}

// @ 0x008a7e30
void SetInterpolation(FFT1HintClass* h)
{
    // PARTIAL: per-hint-set interpolation table builder (two passes over x_hints/y_hints).
    (void)h;
}

// @ 0x008a8180
void DoVStrokes(void)
{
    // PARTIAL: vertical-stroke fitting inner loop; the original takes its first value and
    // its hint-class pointer in registers (EAX/EDI), a non-C register ABI.
}
