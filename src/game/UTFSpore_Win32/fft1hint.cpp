// src/game/UTFSpore_Win32/fft1hint.cpp -- migrated from slice(s) s008a8280, s008a7400 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/fft1hint.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

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
void SetupStemWeights(FFT1HintClass* h, int scale, int* src, int count, int refWidth, int* out, int* pNum)
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
