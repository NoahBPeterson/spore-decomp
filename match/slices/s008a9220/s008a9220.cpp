// Slice s008a9220 — 0x008a9220, 10800 bytes.
//
// Bitstream FontFusion Type-1 hinting engine (module "EA-UTF", prebuilt; its codegen differs
// from cl 15.00 /O2, see s008a7400).  Dev-PDB candidate name `SetupInput` (caller-single).
//
// SetupInput(FFT1HintClass* h) converts the raw hint input that the Type-1 charstring
// interpreter collected (xOrus/yOrus stem edges, xgcount/ygcount group markers with -999
// separators, xbgcount/ybgcount, extra strokes and extra edges) into per-hint-set tables:
//   x_hints/y_hints[set]      (hints_t:        hint_array/hint_pix/offset_ptr/IntOrus/mult_ptr)
//   x_strokes/y_strokes[set]  (extraStroke_t)
//   x_edges/y_edges[set]      (extraEdge_t)
// then bubble-sorts each set's stem pairs, fits them (DoVStrokes/DoHStrokes), merges the
// extra strokes/edges (DoExtraStrokes/DoExtraEdges) and builds interpolation (SetInterpolation).
//
// Register ABI of the original (prebuilt module): SetupInput takes h in EAX; DoVStrokes /
// DoHStrokes / DoExtraStrokes / DoExtraEdges take h in EDI and some leading arguments in
// EAX/ECX/EDX.  Those are modelled here as ordinary C parameters (documented per callee).
//
// Faithfully reproduced quirks of the original (verified in the disassembly, Ghidra gets the
// first one wrong):
//  * X pass, first hint-marker grow in the -999 branch: hintmarkers_y is reallocated with
//    hintmarkers_x_ml (not hintmarkers_y_ml) elements.
//  * X pass, first hint-set grow in the -999 branch: num_y_hint_sets_ml = num_x_hint_sets_ml + 10.
//  * Y pass, hint-marker grow in the non-separator branch: hintmarkers_x is reallocated with
//    hintmarkers_y_ml elements.
//  * The extra-stroke / extra-edge passes never grow x_strokes/x_edges/... arrays.

typedef unsigned int uint32;

struct tsiMemObject;

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

struct blueZone_tag { int minPix; int maxPix; int refPix; };
struct stemSnap_tag { int minPix; int maxPix; int refPix; };

struct FFT1HintClass {                  // size 0x378 (2008 dev PDB)
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

#define HINT_MARKER_END (-999)

// FontFusion memory manager
extern "C" void* tsi_AllocMem(tsiMemObject* mem, uint32 size);             // 0x008d1260
extern "C" void* tsi_ReAllocMem(tsiMemObject* mem, void* p, uint32 size);  // 0x008d1330
extern "C" void  tsi_DeAllocMem(tsiMemObject* mem, void* p);               // 0x008d1440

// Hinting helpers (other slices).  Register mapping of the original in the comments.
// h -> EDI, first -> EAX
extern "C" void DoVStrokes(FFT1HintClass* h, int first, int count, short* hint_array,
                           int* hint_pix, int flag);                                    // 0x008a8180
// h -> EDI, first -> ECX
extern "C" void DoHStrokes(FFT1HintClass* h, int first, int count, short* hint_array,
                           int* hint_pix, int flag);                                    // 0x008a8280
// h -> EDI (and pushed); nxh -> EAX, xpix -> ECX, nxs -> EDX
extern "C" void DoExtraStrokes(FFT1HintClass* h,
                               short* nxh, short* xhint, int* xpix,
                               short* nyh, short* yhint, int* ypix,
                               short* nxs, short* xs, short* nys, short* ys);           // 0x008a8590
// h -> EDI (and pushed); xhint -> EAX, xpix -> ECX, nxh -> EDX
extern "C" void DoExtraEdges(FFT1HintClass* h,
                             short* nxh, short* xhint, int* xpix,
                             short* nyh, short* yhint, int* ypix,
                             short* xEdgeDelta, short* yEdgeDelta,
                             short* xEdgeIndex, short* yEdgeIndex,
                             short* xEdgeThresh, short* yEdgeThresh,
                             short* nxEdges, short* nyEdges);                           // 0x008a8700
extern "C" void SetInterpolation(FFT1HintClass* h);                                     // 0x008a7e30

// ---------------------------------------------------------------------------
// Small helpers (the original repeats these blocks inline at every site)
// ---------------------------------------------------------------------------

// Fresh hint set: 20 slots in every per-hint array.
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

// Allocate a hint set's arrays (without touching the counts).
static __forceinline void AllocHintSetArrays(tsiMemObject* mem, hints_t* hs)
{
    hs->hint_array = (short*)tsi_AllocMem(mem, 20 * sizeof(short));
    hs->hint_pix   = (int*)  tsi_AllocMem(mem, 20 * sizeof(int));
    hs->offset_ptr = (int*)  tsi_AllocMem(mem, 20 * sizeof(int));
    hs->IntOrus    = (short*)tsi_AllocMem(mem, 20 * sizeof(short));
    hs->mult_ptr   = (int*)  tsi_AllocMem(mem, 20 * sizeof(int));
}

// Grow a hint set by 20 slots.
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

// Grow both hint-marker arrays by 10 ("a" is the direction being processed).
// sizeOfB: element count used for b's realloc (normally *bml after its += 10; two sites in
// the original use a's count instead).
static __forceinline void GrowMarkers(tsiMemObject* mem, short** a, short* aml, short** b, short* bml,
                               bool bUsesAml)
{
    *aml += 10;
    *a = (short*)tsi_ReAllocMem(mem, *a, *aml * sizeof(short));
    *bml += 10;
    *b = (short*)tsi_ReAllocMem(mem, *b, (bUsesAml ? *aml : *bml) * sizeof(short));
}

// Grow both directions' hint-set tables by 10 entries and clear the new entries.
// "a" is the direction being processed; bFromA reproduces the X-pass site that sets
// b's capacity to a's new capacity + 10.
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

// Grow both IntOrus arrays by 10.
static __forceinline void GrowIntOrus(tsiMemObject* mem, short** a, short* aml, short** b, short* bml)
{
    *aml += 10;
    *a = (short*)tsi_ReAllocMem(mem, *a, *aml * sizeof(short));
    *bml += 10;
    *b = (short*)tsi_ReAllocMem(mem, *b, *bml * sizeof(short));
}

// One direction's grouping pass (x: dir 0, y: dir 1).  Returns the number of hint sets.
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

// Distribute one direction's extra strokes over the hint sets.
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

// Distribute one direction's extra edges over the hint sets.
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

// Bubble-sort a hint set's stem pairs (lo,hi) by their low edge, carrying hint_pix along.
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

// @ 0x008a9220
// Original: static helper, h in EAX.
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
