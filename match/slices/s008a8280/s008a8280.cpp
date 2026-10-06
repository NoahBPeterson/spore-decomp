// Slice s008a8280 (cl1_new #68), 32-bit MSVC 2008.
// Bitstream FontFusion Type-1 hinting engine (module "EA-UTF", prebuilt; register-ABI statics
// from a whole-program build, see s008a7400 / s008a9220).  Real names from the 2008 dev PDB.
//
// Register ABI of the original, modelled as ordinary C parameters:
//   DoHStrokes   h -> EDI, first -> ECX, remaining args on the stack
//   DoExtraStrokes / DoExtraEdges   h -> EDI/stack, leading args in EAX/ECX/EDX
typedef unsigned int uint32;
typedef unsigned char uint8;
typedef unsigned short uint16;

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

struct GlyphClass;
extern "C" void  tsi_DeAllocMem(tsiMemObject* mem, void* p);        // 0x008d1440
extern "C" int   util_FixMul(int a, int b);                         // 0x008d1590
extern "C" int   util_FixDiv(int a, int b);                         // 0x008d16d0
extern "C" void  DoVStrokes(FFT1HintClass* h, int first, int count, short* hint_array,
                            int* hint_pix, int flag);               // 0x008a8180
void FlipContourDirection(GlyphClass* g, short dir);                // 0x008a77b0
void DoHStrokes(FFT1HintClass* h, int first, int count, short* hint_array, int* hint_pix, int nb);

// ---------------------------------------------------------------------------
// @ 0x008a8280
// Fit horizontal stems (y direction) of one hint set against the blue zones.
// hint_array[i], hint_array[i+1] = bottom/top edge of a stem; results in hint_pix[i], hint_pix[i+1].
// nb is the index of an already-fitted neighbouring stem, or < 0 for none.
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

// ---------------------------------------------------------------------------
// @ 0x008a8590   (dev PDB candidate name DoExtraStrokes)
// Append the extra strokes (xs / ys pairs) to the x and y hint lists and fit each new pair.
void DoExtraStrokes(FFT1HintClass* h,
                    short* nxh, short* xhint, int* xpix,
                    short* nyh, short* yhint, int* ypix,
                    short* nxs, short* xs, short* nys, short* ys)
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

// ---------------------------------------------------------------------------
// @ 0x008a8700
// Append the extra edges (reference index + delta) to the x and y hint lists.
void DoExtraEdges(FFT1HintClass* h,
                  short* nxh, short* xhint, int* xpix,
                  short* nyh, short* yhint, int* ypix,
                  short* xEdgeDelta, short* yEdgeDelta,
                  short* xEdgeIndex, short* yEdgeIndex,
                  short* xEdgeThresh, short* yEdgeThresh,
                  short* nxEdges, short* nyEdges)
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

// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Interpolate one coordinate axis of the glyph through the hint sets.
// src: unscaled coordinates, dst: result, markers: hintmarkers_x/y_ptr (point index where each set ends),
// nInt: n{x,y}IntOrus_ptr, hints: x_hints/y_hints, plainScale: scale for points outside any hinted range
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

// ---------------------------------------------------------------------------
// @ 0x008a8880
// Scale the glyph's design-unit outline (oox/ooy) into pixel coordinates (x/y), snapping through the
// hint tables built by SetupInput, then free all per-glyph hint memory.
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

// ---------------------------------------------------------------------------
// @ 0x008a8ff0
void FFT1HintClass_releaseMem(FFT1HintClass* h)
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
}

// ---------------------------------------------------------------------------
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
