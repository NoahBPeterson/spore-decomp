// src/game/UTFSpore_Win32/fft1hint.cpp -- migrated from slice(s) s008a9220, s008a8280, s008a7400 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/fft1hint.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.
// Flags: /O2 /MD /Gy /EHsc /TP

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* tsi_AllocMem(void* mem, unsigned size);          // 0x008d1260
extern "C" int   util_FixMul(int a, int b);                       // 0x008d1590
#include <intrin.h>

// ---- items of slice s008a7400 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
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
extern "C" void* tsi_AllocMem(void* mem, unsigned size);          // 0x008d1260
extern "C" int   util_FixMul(int a, int b);                       // 0x008d1590
// ---- items of slice s008a7400 end

// ---- items of slice s008a8280 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int   util_FixDiv(int a, int b);                         // 0x008d16d0
struct tsiMemObject;
struct GlyphClass;
extern "C" void  tsi_DeAllocMem(tsiMemObject* mem, void* p);        // 0x008d1440
extern "C" void  DoVStrokes(FFT1HintClass* h, int first, int count, short* hint_array,
                            int* hint_pix, int flag);               // 0x008a8180
void FlipContourDirection(GlyphClass* g, short dir);                // 0x008a77b0
void DoHStrokes(FFT1HintClass* h, int first, int count, short* hint_array, int* hint_pix, int nb);
static void InterpolateAxis(FFT1HintClass* h, int start, short* markers, short* nInt, hints_t* hints,
                            const short* src, int* dst, int plainScale)
{
    if (markers[0] == -999) {
        markers[0] = (short)start;
        markers[1] = (short)start;
    } else {
        markers[h->numHintSets] = (short)start;
    }
    int set = 0;                       // current hint set
    for (int i = 0; i < start; i++) {
        if (i < markers[set + 1]) {
            int n = nInt[set];
            if (n < 1) {
                dst[i] = util_FixMul(src[i], plainScale);
            } else {
                hints_t* hs = &hints[set];
                int k = 0;
                if (n > 0) {
                    const short* p = hs->IntOrus;
                    k = 0;
                    do {
                        if (src[i] <= *p) break;
                        k++;
                        p++;
                    } while (k < nInt[set]);
                }
                if (k == n)
                    dst[i] = util_FixMul(src[i], hs->mult_ptr[n]) + hs->offset_ptr[nInt[set]];
                else
                    dst[i] = util_FixMul(src[i], hs->mult_ptr[k]) + hs->offset_ptr[k];
            }
        } else {
            set++;
            i--;
        }
    }
}
// ---- items of slice s008a8280 end

// ---- items of slice s008a9220 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define HINT_MARKER_END (-999)
extern "C" void* tsi_ReAllocMem(tsiMemObject* mem, void* p, uint32 size);  // 0x008d1330
static __forceinline void InitHintSet(tsiMemObject* mem, hints_t* hs)
{
    hs->num_hints = 0;
    hs->num_hints_ml = 20;
    hs->hint_array = (short*)tsi_AllocMem(mem, 20 * sizeof(short));
    hs->hint_pix   = (int*)  tsi_AllocMem(mem, 20 * sizeof(int));
    hs->offset_ptr = (int*)  tsi_AllocMem(mem, 20 * sizeof(int));
    hs->IntOrus    = (short*)tsi_AllocMem(mem, 20 * sizeof(short));
    hs->mult_ptr   = (int*)  tsi_AllocMem(mem, 20 * sizeof(int));
}
static __forceinline void AllocHintSetArrays(tsiMemObject* mem, hints_t* hs)
{
    hs->hint_array = (short*)tsi_AllocMem(mem, 20 * sizeof(short));
    hs->hint_pix   = (int*)  tsi_AllocMem(mem, 20 * sizeof(int));
    hs->offset_ptr = (int*)  tsi_AllocMem(mem, 20 * sizeof(int));
    hs->IntOrus    = (short*)tsi_AllocMem(mem, 20 * sizeof(short));
    hs->mult_ptr   = (int*)  tsi_AllocMem(mem, 20 * sizeof(int));
}
static __forceinline void GrowHintSet(tsiMemObject* mem, hints_t* hs)
{
    hs->num_hints_ml += 20;
    hs->hint_array = (short*)tsi_ReAllocMem(mem, hs->hint_array, hs->num_hints_ml * sizeof(short));
    hs->hint_pix   = (int*)  tsi_ReAllocMem(mem, hs->hint_pix,   hs->num_hints_ml * sizeof(int));
    hs->offset_ptr = (int*)  tsi_ReAllocMem(mem, hs->offset_ptr, hs->num_hints_ml * sizeof(int));
    hs->mult_ptr   = (int*)  tsi_ReAllocMem(mem, hs->mult_ptr,   hs->num_hints_ml * sizeof(int));
    hs->IntOrus    = (short*)tsi_ReAllocMem(mem, hs->IntOrus,    hs->num_hints_ml * sizeof(short));
}
static __forceinline void FreeHintSet(tsiMemObject* mem, hints_t* hs)
{
    tsi_DeAllocMem(mem, hs->hint_array);
    tsi_DeAllocMem(mem, hs->hint_pix);
    tsi_DeAllocMem(mem, hs->offset_ptr);
    tsi_DeAllocMem(mem, hs->IntOrus);
    tsi_DeAllocMem(mem, hs->mult_ptr);
}
static __forceinline void GrowMarkers(tsiMemObject* mem, short** a, short* aml, short** b, short* bml,
                               bool bUsesAml)
{
    *aml += 10;
    *a = (short*)tsi_ReAllocMem(mem, *a, *aml * sizeof(short));
    *bml += 10;
    *b = (short*)tsi_ReAllocMem(mem, *b, (bUsesAml ? *aml : *bml) * sizeof(short));
}
static __forceinline void GrowHintSets(tsiMemObject* mem,
                                hints_t** ah, extraStroke_t** as, extraEdge_t** ae, short* aml,
                                hints_t** bh, extraStroke_t** bs, extraEdge_t** be, short* bml,
                                bool bFromA)
{
    int old = *aml;
    *aml += 10;
    *ah = (hints_t*)      tsi_ReAllocMem(mem, *ah, *aml * sizeof(hints_t));
    *as = (extraStroke_t*)tsi_ReAllocMem(mem, *as, *aml * sizeof(extraStroke_t));
    *ae = (extraEdge_t*)  tsi_ReAllocMem(mem, *ae, *aml * sizeof(extraEdge_t));
    if (bFromA)
        *bml = *aml + 10;
    else
        *bml += 10;
    *bh = (hints_t*)      tsi_ReAllocMem(mem, *bh, *bml * sizeof(hints_t));
    *bs = (extraStroke_t*)tsi_ReAllocMem(mem, *bs, *bml * sizeof(extraStroke_t));
    *be = (extraEdge_t*)  tsi_ReAllocMem(mem, *be, *bml * sizeof(extraEdge_t));
    for (int i = old; i < *aml; i++) {
        (*ah)[i].hint_array = 0;
        (*as)[i].num_hints = 0;
        (*ae)[i].numEdges = 0;
        (*bh)[i].hint_array = 0;
        (*bs)[i].num_hints = 0;
        (*be)[i].numEdges = 0;
    }
}
static __forceinline void GrowIntOrus(tsiMemObject* mem, short** a, short* aml, short** b, short* bml)
{
    *aml += 10;
    *a = (short*)tsi_ReAllocMem(mem, *a, *aml * sizeof(short));
    *bml += 10;
    *b = (short*)tsi_ReAllocMem(mem, *b, *bml * sizeof(short));
}
static __forceinline int GroupHints(FFT1HintClass* h, int dir)
{
    tsiMemObject* mem = h->mem;
    const bool isX = (dir == 0);

    hints_t**       ah   = isX ? &h->x_hints   : &h->y_hints;
    extraStroke_t** as   = isX ? &h->x_strokes : &h->y_strokes;
    extraEdge_t**   ae   = isX ? &h->x_edges   : &h->y_edges;
    short*          aml  = isX ? &h->num_x_hint_sets_ml : &h->num_y_hint_sets_ml;
    hints_t**       bh   = isX ? &h->y_hints   : &h->x_hints;
    extraStroke_t** bs   = isX ? &h->y_strokes : &h->x_strokes;
    extraEdge_t**   be   = isX ? &h->y_edges   : &h->x_edges;
    short*          bml  = isX ? &h->num_y_hint_sets_ml : &h->num_x_hint_sets_ml;

    short** mk     = isX ? &h->hintmarkers_x_ptr : &h->hintmarkers_y_ptr;
    short*  mkml   = isX ? &h->hintmarkers_x_ml  : &h->hintmarkers_y_ml;
    short*  nmk    = isX ? &h->num_hintmarkers_x : &h->num_hintmarkers_y;
    short** omk    = isX ? &h->hintmarkers_y_ptr : &h->hintmarkers_x_ptr;
    short*  omkml  = isX ? &h->hintmarkers_y_ml  : &h->hintmarkers_x_ml;

    short** io     = isX ? &h->nxIntOrus_ptr : &h->nyIntOrus_ptr;
    short*  ioml   = isX ? &h->xInt_num_ml   : &h->yInt_num_ml;
    short** oio    = isX ? &h->nyIntOrus_ptr : &h->nxIntOrus_ptr;
    short*  oioml  = isX ? &h->yInt_num_ml   : &h->xInt_num_ml;

    short*  gcount  = isX ? h->xgcount_ptr  : h->ygcount_ptr;
    short*  bgcount = isX ? h->xbgcount_ptr : h->ybgcount_ptr;
    short*  orus    = isX ? h->xOrus_ptr    : h->yOrus_ptr;
    short*  pnOrus  = isX ? &h->numxOrus    : &h->numyOrus;

    int   j = 0;        // index into orus
    int   k = 0;        // index into gcount
    int   m = 0;        // index into bgcount
    int   num = 0;      // current hint set
    short cur = 0;      // current group value
    int   result = 0;

    InitHintSet(mem, &(*ah)[0]);

    if (*pnOrus > 0) {
        do {
            short s = gcount[k];
            for (; cur == s && cur != HINT_MARKER_END && j < *pnOrus; j++) {
                hints_t* hs = &(*ah)[num];
                hs->hint_array[hs->num_hints] = orus[j];
                hs->num_hints++;
                if (hs->num_hints_ml <= hs->num_hints)
                    GrowHintSet(mem, hs);
                (*mk)[num] = cur;
                k++;
                s = gcount[k];
            }
            (*nmk)++;
            cur = gcount[k];
            if (cur == HINT_MARKER_END) {
                bool nonEmpty = (*ah)[num].num_hints > 0;
                if (nonEmpty)
                    num++;
                if (*mkml <= *nmk)
                    GrowMarkers(mem, mk, mkml, omk, omkml, isX /* quirk: X uses x count */);
                (*mk)[num] = bgcount[m];
                m++;
                k++;
                cur = gcount[k];
                if (*aml <= num)
                    GrowHintSets(mem, ah, as, ae, aml, bh, bs, be, bml, isX /* quirk */);
                if (*ioml <= num)
                    GrowIntOrus(mem, io, ioml, oio, oioml);
                if (nonEmpty)
                    InitHintSet(mem, &(*ah)[num]);
                (*nmk)++;
                num++;
                if (*mkml <= *nmk)
                    GrowMarkers(mem, mk, mkml, omk, omkml, false);
                if (*aml <= num)
                    GrowHintSets(mem, ah, as, ae, aml, bh, bs, be, bml, false);
                if (*ioml <= num)
                    GrowIntOrus(mem, io, ioml, oio, oioml);
                InitHintSet(mem, &(*ah)[num]);
            } else {
                num++;
                if (*mkml <= *nmk)
                    GrowMarkers(mem, mk, mkml, omk, omkml, !isX /* quirk: Y uses y count */);
                if (*aml <= num)
                    GrowHintSets(mem, ah, as, ae, aml, bh, bs, be, bml, false);
                if (*ioml <= num)
                    GrowIntOrus(mem, io, ioml, oio, oioml);
                InitHintSet(mem, &(*ah)[num]);
            }
            result = num;
        } while (j < *pnOrus);
    }
    return result;
}
static __forceinline void GroupExtraStrokes(tsiMemObject* mem, extraStroke_t* strokes, short* markers,
                              short* glyphCount, short* strokeOrus, short count)
{
    int   j = 0;
    int   num = 0;
    short cur = 0;

    strokes[0].hint_array = (short*)tsi_AllocMem(mem, 20 * sizeof(short));
    strokes[0].num_hints = 0;
    strokes[0].num_hints_ml = 20;
    if (count > 0) {
        do {
            while (cur == glyphCount[j] && j < count) {
                extraStroke_t* st = &strokes[num];
                st->hint_array[st->num_hints] = strokeOrus[j];
                st->num_hints++;
                if (st->num_hints_ml <= st->num_hints) {
                    st->num_hints_ml += 20;
                    st->hint_array = (short*)tsi_ReAllocMem(mem, st->hint_array,
                                                            st->num_hints_ml * sizeof(short));
                }
                j++;
            }
            if (strokes[num].num_hints == 0)
                tsi_DeAllocMem(mem, strokes[num].hint_array);
            cur = markers[num + 1];
            num++;
            strokes[num].hint_array = (short*)tsi_AllocMem(mem, 20 * sizeof(short));
            strokes[num].num_hints = 0;
            strokes[num].num_hints_ml = 20;
        } while (j < count);
    }
    tsi_DeAllocMem(mem, strokes[num].hint_array);
}
static __forceinline void GroupExtraEdges(tsiMemObject* mem, extraEdge_t* edges, short* markers,
                            short* glyphCount, short* thresh, short* delta, short* index,
                            short count)
{
    int   j = 0;
    int   num = 0;
    short cur = 0;

    edges[0].EdgeThresh = (short*)tsi_AllocMem(mem, 20 * sizeof(short));
    edges[0].EdgeDelta  = (short*)tsi_AllocMem(mem, 20 * sizeof(short));
    edges[0].EdgeIndex  = (short*)tsi_AllocMem(mem, 20 * sizeof(short));
    edges[0].numEdges = 0;
    edges[0].numEdges_ml = 20;
    if (count > 0) {
        do {
            while (cur == glyphCount[j] && j < count) {
                extraEdge_t* e = &edges[num];
                e->EdgeThresh[e->numEdges] = thresh[j];
                e->EdgeDelta[e->numEdges]  = delta[j];
                e->EdgeIndex[e->numEdges]  = index[j];
                e->numEdges++;
                if (e->numEdges_ml <= e->numEdges) {
                    e->numEdges_ml += 20;
                    e->EdgeThresh = (short*)tsi_ReAllocMem(mem, e->EdgeThresh, e->numEdges_ml * sizeof(short));
                    e->EdgeDelta  = (short*)tsi_ReAllocMem(mem, e->EdgeDelta,  e->numEdges_ml * sizeof(short));
                    e->EdgeIndex  = (short*)tsi_ReAllocMem(mem, e->EdgeIndex,  e->numEdges_ml * sizeof(short));
                }
                j++;
            }
            if (edges[num].numEdges == 0) {
                tsi_DeAllocMem(mem, edges[num].EdgeThresh);
                tsi_DeAllocMem(mem, edges[num].EdgeDelta);
                tsi_DeAllocMem(mem, edges[num].EdgeIndex);
            }
            cur = markers[num + 1];
            num++;
            edges[num].EdgeThresh = (short*)tsi_AllocMem(mem, 20 * sizeof(short));
            edges[num].EdgeDelta  = (short*)tsi_AllocMem(mem, 20 * sizeof(short));
            edges[num].EdgeIndex  = (short*)tsi_AllocMem(mem, 20 * sizeof(short));
            edges[num].numEdges = 0;
            edges[num].numEdges_ml = 20;
        } while (j < count);
    }
    tsi_DeAllocMem(mem, edges[num].EdgeThresh);
    tsi_DeAllocMem(mem, edges[num].EdgeDelta);
    tsi_DeAllocMem(mem, edges[num].EdgeIndex);
}
static __forceinline void SortStemPairs(hints_t* hs)
{
    if (hs->num_hints > 0) {
        bool swapped;
        do {
            swapped = false;
            int i = hs->num_hints - 4;
            if (i < 0)
                break;
            do {
                short* a = hs->hint_array;
                if (a[i + 2] < a[i]) {
                    short t = a[i];
                    a[i] = a[i + 2];
                    hs->hint_array[i + 2] = t;

                    int* p = hs->hint_pix;
                    int tp = p[i];
                    p[i] = p[i + 2];
                    hs->hint_pix[i + 2] = tp;

                    a = hs->hint_array;
                    t = a[i + 1];
                    a[i + 1] = a[i + 3];
                    hs->hint_array[i + 3] = t;

                    p = hs->hint_pix;
                    tp = p[i + 1];
                    p[i + 1] = p[i + 3];
                    swapped = true;
                    hs->hint_pix[i + 3] = tp;
                }
                i -= 2;
            } while (i >= 0);
        } while (swapped);
    }
}
// ---- items of slice s008a9220 end

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

// @ 0x008a7930
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

// @ 0x008a7c90
int* SetupStemWeights(FFT1HintClass* h, int scale, int* src, int count, int refWidth, int* out, int* pNum)
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
        return pNum;
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
    return pNum;
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

// @ 0x008a8280
void DoHStrokes(FFT1HintClass* h, int first, int count, short* hint_array, int* hint_pix, int nb)
{
    int  zone = 0;                   // bottom-zone cursor
    int  edgeLo = 0;                 // fitted bottom edge (snapped to a blue zone)
    int  edgeHi = 0;                 // fitted top edge
    int  numZones = h->numBlueValues >> 1;
    int  topZone;
    int  nBottom;
    if (numZones > 0) { nBottom = 1; topZone = 1; }
    else              { numZones = 0; nBottom = 0; topZone = 0; }

    for (int i = first; i < count; i += 2) {
        short lo = hint_array[i];
        short hi = hint_array[i + 1];
        int   hit = 0;               // bit0: bottom edge in zone, bit1: top edge in zone
        int   width;

        if (zone < nBottom) {
            int p = util_FixMul(lo, h->yScale);
            const blueZone_tag* z = &h->pBlueZones[zone];
            do {
                if (p <= z->maxPix) {
                    if (zone < nBottom && h->pBlueZones[zone].minPix <= p) {
                        hit = 1;
                        int ov = 0;
                        if (h->suppressOvershoots == 0)
                            ov = ((h->pBlueZones[zone].refPix + h->pixrnd) - p) & h->pixfix;
                        edgeLo = ((h->pBlueZones[zone].refPix + h->pixrnd) & h->pixfix) - ov;
                    }
                    break;
                }
                zone++;
                z++;
            } while (zone < nBottom);
        }
        if (topZone < numZones) {
            int p = util_FixMul(hi, h->yScale);
            const blueZone_tag* z = &h->pBlueZones[topZone];
            do {
                if (p <= z->maxPix) {
                    if (topZone < numZones && h->pBlueZones[topZone].minPix <= p) {
                        hit |= 2;
                        int ov;
                        if (h->suppressOvershoots == 0) {
                            int d = p - h->pBlueZones[topZone].refPix;
                            if (d < h->pixrnd && h->BlueShiftPix <= d)
                                ov = h->onepix;
                            else
                                ov = (d + h->pixrnd) & h->pixfix;
                        } else {
                            ov = 0;
                        }
                        edgeHi = ((h->pBlueZones[topZone].refPix + h->pixrnd) & h->pixfix) + ov;
                    }
                    break;
                }
                topZone++;
                z++;
            } while (topZone < numZones);
        }

        if (hi == lo) {
            width = 0;
        } else {
            int w = util_FixMul(hi - lo, h->yScale);
            int k = 0;
            if (h->numSnapHZones > 0) {
                const stemSnap_tag* s = &h->pSnapH[0];
                do {
                    if (w < s->minPix) break;
                    if (w <= s->maxPix) { w = s->refPix; break; }
                    k++;
                    s++;
                } while (k < h->numSnapHZones);
            }
            width = h->onepix;
            if (width <= w)
                width = (h->pixrnd + w) & h->pixfix;
        }

        switch (hit) {
        case 0: {
            int mid, off;
            if (nb < 0) {
                mid = hi + 1 + lo;
                off = 1 - width;
            } else {
                mid = (hi - hint_array[nb + 1]) - hint_array[nb] + lo;
                off = (hint_pix[nb + 1] - width) + hint_pix[nb];
            }
            int m = util_FixMul((short)(mid >> 1), h->yScale);
            uint32 b = (m + h->pixrnd + (off >> 1)) & h->pixfix;
            hint_pix[i] = b;
            hint_pix[i + 1] = b + width;
            break;
        }
        case 1:
            hint_pix[i + 1] = width + edgeLo;
            hint_pix[i] = edgeLo;
            break;
        case 2:
            hint_pix[i] = edgeHi - width;
            hint_pix[i + 1] = edgeHi;
            break;
        case 3:
            hint_pix[i + 1] = edgeHi;
            hint_pix[i] = edgeLo;
            break;
        }
    }
}

// @ 0x008a8590
void DoExtraStrokes(FFT1HintClass* h, short* nxh, short* xhint, int* xpix, short* nyh, short* yhint, int* ypix, short* nxs, short* xs, short* nys, short* ys)
{
    bool   second = false;
    short* cnt   = nxh;
    short* arr   = xhint;
    int*   pix   = xpix;
    short* ecnt  = nxs;
    short* earr  = xs;
    for (;;) {
        int n = *cnt;                 // hint count before appending
        int cur = n;                  // running count
        int pos = 0;                  // cursor into the existing pairs
        if (*ecnt > 0) {
            for (int k = 0; k < *ecnt; k += 2) {
                short lo = earr[k];
                short hi = earr[k + 1];
                arr[cur] = lo;
                arr[cur + 1] = hi;
                if (pos < n) {
                    const short* p = &arr[pos + 1];
                    do {
                        if (lo <= *p) break;
                        pos += 2;
                        p += 2;
                    } while (pos < n);
                }
                int nb;
                if (n <= pos || (nb = pos, hi <= arr[pos]))
                    nb = 0;
                if (second)
                    DoHStrokes(h, cur, cur + 2, arr, pix, nb);
                else
                    DoVStrokes(h, cur, cur + 2, arr, pix, nb);
                cur += 2;
            }
        }
        if (second) {
            *cnt = (short)cur;
            return;
        }
        *cnt = (short)cur;
        second = true;
        cnt = nyh; arr = yhint; pix = ypix; ecnt = nys; earr = ys;
    }
}

// @ 0x008a8700
void DoExtraEdges(FFT1HintClass* h, short* nxh, short* xhint, int* xpix, short* nyh, short* yhint, int* ypix, short* xEdgeDelta, short* yEdgeDelta, short* xEdgeIndex, short* yEdgeIndex, short* xEdgeThresh, short* yEdgeThresh, short* nxEdges, short* nyEdges)
{
    bool   second = false;
    short* cnt    = nxh;
    short* arr    = xhint;
    int*   pix    = xpix;
    short* delta  = xEdgeDelta;
    short* index  = xEdgeIndex;
    short* thresh = xEdgeThresh;
    short* nEdges = nxEdges;
    int n;
    for (;;) {
        n = *cnt;
        for (int k = 0; k < *nEdges; k++) {
            arr[n] = (short)(arr[index[k]] + delta[k]);
            int scale = second ? h->yScale : h->xScale;
            int v = util_FixMul(delta[k], scale);
            int t = thresh[k];
            int fix;
            if (v < t * 4 && -(t * 4) < v)
                fix = 0;
            else
                fix = (h->pixrnd + v) & h->pixfix;
            pix[n] = pix[index[k]] + fix;
            n++;
        }
        if (second) break;
        *cnt = (short)n;
        second = true;
        cnt = nyh; arr = yhint; pix = ypix;
        delta = yEdgeDelta; index = yEdgeIndex; thresh = yEdgeThresh; nEdges = nyEdges;
    }
    *cnt = (short)n;
}

// @ 0x008a8830
void SetScale_FFT1HintClass(FFT1HintClass* h, int xppem, int yppem)
{
    if (h == 0) return;
    if (h->xPixelsPerEm == xppem && h->yPixelsPerEm == yppem) return;
    int upem = h->upem;
    h->xPixelsPerEm = xppem;
    h->yPixelsPerEm = yppem;
    h->xScale = util_FixDiv(xppem << 6, upem);
    h->yScale = util_FixDiv(yppem << 6, upem);
}

// @ 0x008a8880
void ApplyHints_FFT1HintClass(FFT1HintClass* h, short start, short count, GlyphClass* g)
{
    if (h == 0) return;
    FlipContourDirection(g, 0);
    int*   px  = g->x;
    int*   py  = g->y;
    short* ox  = g->oox;
    short* oy  = g->ooy;
    int    s   = start;

    for (int i = s; i < count + s; i++) {
        px[i] = util_FixMul(ox[i], h->xScale);
        py[i] = util_FixMul(oy[i], h->yScale);
    }
    if (h->numHintSets == 0) {
        for (int i = 0; i < s; i++) {
            px[i] = util_FixMul(ox[i], h->xScale);
            py[i] = util_FixMul(oy[i], h->yScale);
        }
    } else {
        InterpolateAxis(h, s, h->hintmarkers_x_ptr, h->nxIntOrus_ptr, h->x_hints, ox, px, h->xScale);
        InterpolateAxis(h, s, h->hintmarkers_y_ptr, h->nyIntOrus_ptr, h->y_hints, oy, py, h->yScale);
    }

    h->numxOrus = 0;
    h->numybgcount = 0;
    h->numextraYStroke = 0;
    h->numyOrus = 0;
    h->num_tcb = 0;
    h->numextraXEdge = 0;
    h->numSnapV = 0;
    h->numSnapH = 0;
    h->numSnapVZones = 0;
    h->numSnapHZones = 0;
    h->numxbgcount = 0;
    h->numextraXStroke = 0;
    h->numextraYEdge = 0;
    int* z;
    z = (int*)h->ybgcount_ptr; for (int i = 0; i < 10; i++) z[i] = 0;
    z = (int*)h->xbgcount_ptr; for (int i = 0; i < 10; i++) z[i] = 0;
    z = (int*)h->ygcount_ptr;  for (int i = 0; i < 10; i++) z[i] = 0;
    z = (int*)h->xgcount_ptr;  for (int i = 0; i < 10; i++) z[i] = 0;

    tsi_DeAllocMem(h->mem, h->hintmarkers_x_ptr);
    tsi_DeAllocMem(h->mem, h->hintmarkers_y_ptr);
    tsi_DeAllocMem(h->mem, h->nxIntOrus_ptr);
    tsi_DeAllocMem(h->mem, h->nyIntOrus_ptr);
    for (int set = 0; set < h->numHintSets; set++) {
        hints_t* xh = &h->x_hints[set];
        tsi_DeAllocMem(h->mem, xh->hint_array);
        tsi_DeAllocMem(h->mem, xh->hint_pix);
        tsi_DeAllocMem(h->mem, xh->offset_ptr);
        tsi_DeAllocMem(h->mem, xh->IntOrus);
        tsi_DeAllocMem(h->mem, xh->mult_ptr);
        hints_t* yh = &h->y_hints[set];
        tsi_DeAllocMem(h->mem, yh->hint_array);
        tsi_DeAllocMem(h->mem, yh->hint_pix);
        tsi_DeAllocMem(h->mem, yh->offset_ptr);
        tsi_DeAllocMem(h->mem, yh->IntOrus);
        tsi_DeAllocMem(h->mem, yh->mult_ptr);
        extraStroke_t* xs = &h->x_strokes[set];
        if (xs->num_hints != 0)
            tsi_DeAllocMem(h->mem, xs->hint_array);
        if (h->y_strokes[set].num_hints != 0)
            tsi_DeAllocMem(h->mem, h->y_strokes[set].hint_array);
        extraEdge_t* xe = &h->x_edges[set];
        if (xe->numEdges != 0) {
            tsi_DeAllocMem(h->mem, xe->EdgeThresh);
            tsi_DeAllocMem(h->mem, xe->EdgeDelta);
            tsi_DeAllocMem(h->mem, xe->EdgeIndex);
        }
        extraEdge_t* ye = &h->y_edges[set];
        if (ye->numEdges != 0) {
            tsi_DeAllocMem(h->mem, ye->EdgeThresh);
            tsi_DeAllocMem(h->mem, ye->EdgeDelta);
            tsi_DeAllocMem(h->mem, ye->EdgeIndex);
        }
    }
    h->numHintSets = 0;
    tsi_DeAllocMem(h->mem, h->x_hints);
    tsi_DeAllocMem(h->mem, h->y_hints);
    tsi_DeAllocMem(h->mem, h->x_strokes);
    tsi_DeAllocMem(h->mem, h->y_strokes);
    tsi_DeAllocMem(h->mem, h->x_edges);
    tsi_DeAllocMem(h->mem, h->y_edges);
    FlipContourDirection(g, 1);
}

static __declspec(noinline) FFT1HintClass* FFT1HintClass_releaseMem_impl(FFT1HintClass* h)
{
    h->numSnapV = 0;
    h->numSnapH = 0;
    h->numSnapVZones = 0;
    h->numSnapHZones = 0;
    h->numxOrus = 0;
    h->numyOrus = 0;
    h->numxbgcount = 0;
    h->numybgcount = 0;
    h->num_tcb = 0;
    h->numextraXStroke = 0;
    h->numextraYStroke = 0;
    h->numextraXEdge = 0;
    h->numextraYEdge = 0;
    int* z;
    z = (int*)h->ybgcount_ptr; for (int i = 0; i < 10; i++) z[i] = 0;
    z = (int*)h->xbgcount_ptr; for (int i = 0; i < 10; i++) z[i] = 0;
    z = (int*)h->ygcount_ptr;  for (int i = 0; i < 10; i++) z[i] = 0;
    z = (int*)h->xgcount_ptr;  for (int i = 0; i < 10; i++) z[i] = 0;
    h->numHintSets = 0;
    return h;
}

// 0x008a8ff0 (byte-exact lifted version: match/slices/s008a8ff0/s008a8ff0.cpp)
void FFT1HintClass_releaseMem(FFT1HintClass* h)
{
    FFT1HintClass_releaseMem_impl(h);
}

// @ 0x008a90f0
void Delete_FFT1HintClass(FFT1HintClass* h)
{
    if (h == 0) return;
    tsiMemObject* m = h->mem;
    tsi_DeAllocMem(m, h->extraXStrokeOrus_ptr);
    tsi_DeAllocMem(m, h->extraYStrokeOrus_ptr);
    tsi_DeAllocMem(m, h->extraXStrokeGlyphCount_ptr);
    tsi_DeAllocMem(m, h->extraYStrokeGlyphCount_ptr);
    tsi_DeAllocMem(m, h->extraXEdgeThresh_ptr);
    tsi_DeAllocMem(m, h->extraYEdgeThresh_ptr);
    tsi_DeAllocMem(m, h->extraXEdgeDelta_ptr);
    tsi_DeAllocMem(m, h->extraYEdgeDelta_ptr);
    tsi_DeAllocMem(m, h->extraXEdgeIndex_ptr);
    tsi_DeAllocMem(m, h->extraYEdgeIndex_ptr);
    tsi_DeAllocMem(m, h->extraXEdgeGlyphCount_ptr);
    tsi_DeAllocMem(m, h->extraYEdgeGlyphCount_ptr);
    tsi_DeAllocMem(m, h->xgcount_ptr);
    tsi_DeAllocMem(m, h->ygcount_ptr);
    tsi_DeAllocMem(m, h->xbgcount_ptr);
    tsi_DeAllocMem(m, h->ybgcount_ptr);
    tsi_DeAllocMem(m, h->xOrus_ptr);
    tsi_DeAllocMem(m, h->yOrus_ptr);
    tsi_DeAllocMem(m, h);
}

// @ 0x008a9220
void SetupInput(FFT1HintClass* h)
{
    tsiMemObject* mem;
    int i;

    // --- initial tables: 10 hint markers / hint sets / IntOrus per direction -----------------
    h->hintmarkers_x_ptr = (short*)tsi_AllocMem(h->mem, 10 * sizeof(short));
    h->hintmarkers_x_ml = 10;
    h->num_hintmarkers_x = 0;
    ((uint32*)h->hintmarkers_x_ptr)[0] = 0;
    ((uint32*)h->hintmarkers_x_ptr)[1] = 0;
    ((uint32*)h->hintmarkers_x_ptr)[2] = 0;
    ((uint32*)h->hintmarkers_x_ptr)[3] = 0;
    ((uint32*)h->hintmarkers_x_ptr)[4] = 0;
    h->num_x_hint_sets_ml = 10;
    h->x_hints   = (hints_t*)      tsi_AllocMem(h->mem, 10 * sizeof(hints_t));
    h->x_strokes = (extraStroke_t*)tsi_AllocMem(h->mem, 10 * sizeof(extraStroke_t));
    h->x_edges   = (extraEdge_t*)  tsi_AllocMem(h->mem, 10 * sizeof(extraEdge_t));
    h->nxIntOrus_ptr = (short*)tsi_AllocMem(h->mem, 10 * sizeof(short));
    h->xInt_num_ml = 10;
    h->numxIntOrus = 0;

    h->hintmarkers_y_ptr = (short*)tsi_AllocMem(h->mem, 10 * sizeof(short));
    h->num_hintmarkers_y = 0;
    h->hintmarkers_y_ml = 10;
    ((uint32*)h->hintmarkers_y_ptr)[0] = 0;
    ((uint32*)h->hintmarkers_y_ptr)[1] = 0;
    ((uint32*)h->hintmarkers_y_ptr)[2] = 0;
    ((uint32*)h->hintmarkers_y_ptr)[3] = 0;
    ((uint32*)h->hintmarkers_y_ptr)[4] = 0;
    h->num_y_hint_sets_ml = 10;
    h->y_hints   = (hints_t*)      tsi_AllocMem(h->mem, 10 * sizeof(hints_t));
    h->y_strokes = (extraStroke_t*)tsi_AllocMem(h->mem, 10 * sizeof(extraStroke_t));
    h->y_edges   = (extraEdge_t*)  tsi_AllocMem(h->mem, 10 * sizeof(extraEdge_t));
    h->nyIntOrus_ptr = (short*)tsi_AllocMem(h->mem, 10 * sizeof(short));
    h->yInt_num_ml = 10;
    h->numyIntOrus = 0;

    for (i = 0; i < 10; i++) {
        h->x_hints[i].hint_array = 0;
        h->x_hints[i].num_hints = 0;
        h->x_hints[i].num_hints_ml = 20;
        h->y_hints[i].hint_array = 0;
        h->y_hints[i].num_hints = 0;
        h->y_hints[i].num_hints_ml = 20;
        h->x_strokes[i].hint_array = 0;
        h->x_strokes[i].num_hints = 0;
        h->y_strokes[i].hint_array = 0;
        h->y_strokes[i].num_hints = 0;
        h->x_edges[i].EdgeThresh = 0;
        h->x_edges[i].EdgeDelta = 0;
        h->x_edges[i].EdgeIndex = 0;
        h->x_edges[i].numEdges = 0;
        h->y_edges[i].EdgeThresh = 0;
        h->y_edges[i].EdgeDelta = 0;
        h->y_edges[i].EdgeIndex = 0;
        h->y_edges[i].numEdges = 0;
    }

    // --- X: group xOrus into hint sets -------------------------------------------------------
    int n = GroupHints(h, 0);
    h->numHintSets = (short)n;
    mem = h->mem;
    FreeHintSet(mem, &h->x_hints[n]);
    h->x_hints[n].hint_array = 0;
    if (h->numHintSets == 1) {
        h->hintmarkers_x_ptr[0] = HINT_MARKER_END;
        h->numHintSets = 1;
    }

    // --- Y: group yOrus into hint sets -------------------------------------------------------
    n = GroupHints(h, 1);
    if (h->numHintSets < n)
        h->numHintSets = (short)n;
    mem = h->mem;
    FreeHintSet(mem, &h->y_hints[n]);
    h->y_hints[n].hint_array = 0;
    if (h->numHintSets == 1) {
        h->hintmarkers_y_ptr[0] = HINT_MARKER_END;
        h->numHintSets = 1;
    }

    // --- make sure every hint set has arrays in both directions ------------------------------
    for (i = 0; i < h->numHintSets; i++) {
        if (h->x_hints[i].hint_array == 0)
            AllocHintSetArrays(h->mem, &h->x_hints[i]);
        if (h->y_hints[i].hint_array == 0)
            AllocHintSetArrays(h->mem, &h->y_hints[i]);
    }

    // --- extra strokes and extra edges --------------------------------------------------------
    GroupExtraStrokes(h->mem, h->x_strokes, h->hintmarkers_x_ptr,
                      h->extraXStrokeGlyphCount_ptr, h->extraXStrokeOrus_ptr, h->numextraXStroke);
    GroupExtraStrokes(h->mem, h->y_strokes, h->hintmarkers_y_ptr,
                      h->extraYStrokeGlyphCount_ptr, h->extraYStrokeOrus_ptr, h->numextraYStroke);
    GroupExtraEdges(h->mem, h->x_edges, h->hintmarkers_x_ptr, h->extraXEdgeGlyphCount_ptr,
                    h->extraXEdgeThresh_ptr, h->extraXEdgeDelta_ptr, h->extraXEdgeIndex_ptr,
                    h->numextraXEdge);
    GroupExtraEdges(h->mem, h->y_edges, h->hintmarkers_y_ptr, h->extraYEdgeGlyphCount_ptr,
                    h->extraYEdgeThresh_ptr, h->extraYEdgeDelta_ptr, h->extraYEdgeIndex_ptr,
                    h->numextraYEdge);

    // --- sort each set's stem pairs -----------------------------------------------------------
    for (i = 0; i < h->numHintSets; i++) {
        SortStemPairs(&h->x_hints[i]);
        SortStemPairs(&h->y_hints[i]);
    }

    // --- fit strokes, merge extra strokes / edges --------------------------------------------
    for (i = 0; i < h->numHintSets; i++) {
        hints_t* xh = &h->x_hints[i];
        DoVStrokes(h, 0, xh->num_hints, xh->hint_array, xh->hint_pix, -1);
        hints_t* yh = &h->y_hints[i];
        DoHStrokes(h, 0, yh->num_hints, yh->hint_array, yh->hint_pix, -1);

        short nxs = h->x_strokes[i].num_hints;
        if (nxs > 0 || h->y_strokes[i].num_hints > 0) {
            xh = &h->x_hints[i];
            if (xh->num_hints_ml <= (int)xh->num_hints + (int)nxs)
                GrowHintSet(h->mem, xh);
            yh = &h->y_hints[i];
            if (yh->num_hints_ml <= (int)h->y_strokes[i].num_hints + (int)yh->num_hints)
                GrowHintSet(h->mem, yh);
            extraStroke_t* xs = &h->x_strokes[i];
            extraStroke_t* ys = &h->y_strokes[i];
            xh = &h->x_hints[i];
            yh = &h->y_hints[i];
            DoExtraStrokes(h,
                           &xh->num_hints, xh->hint_array, xh->hint_pix,
                           &yh->num_hints, yh->hint_array, yh->hint_pix,
                           &xs->num_hints, xs->hint_array, &ys->num_hints, ys->hint_array);
        }

        short nxe = h->x_edges[i].numEdges;
        if (nxe > 0 || h->y_edges[i].numEdges > 0) {
            xh = &h->x_hints[i];
            if (xh->num_hints_ml <= (int)xh->num_hints + (int)nxe)
                GrowHintSet(h->mem, xh);
            yh = &h->y_hints[i];
            if (yh->num_hints_ml <= (int)h->y_edges[i].numEdges + (int)yh->num_hints)
                GrowHintSet(h->mem, yh);
            extraEdge_t* xe = &h->x_edges[i];
            extraEdge_t* ye = &h->y_edges[i];
            xh = &h->x_hints[i];
            yh = &h->y_hints[i];
            DoExtraEdges(h,
                         &xh->num_hints, xh->hint_array, xh->hint_pix,
                         &yh->num_hints, yh->hint_array, yh->hint_pix,
                         xe->EdgeDelta, ye->EdgeDelta, xe->EdgeIndex, ye->EdgeIndex,
                         xe->EdgeThresh, ye->EdgeThresh, &xe->numEdges, &ye->numEdges);
        }
    }

    SetInterpolation(h);
}

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
