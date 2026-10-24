// gold7 batch, worker 5 / slice s008c9e00: four T2K (Type 2000 font scaler) glyph helpers that
// build the stroked outline point lists. They ride on the same StrokeState / glyph scratch types as
// the committed s008c9e00.cpp (lineJoin), so the type model and the TU-local register-convention
// callees (StrokeDist / AddTwoPointsA) are reused.
//
//   0x008ca5b0  EndCap         - emit the two outline points of a line cap (flat / square / round /
//                                bevel variants), the offset vector scaled from the segment normal.
//   0x008ca760  glyph_EnsureSpaceForNPoints - grow the glyph's parallel point arrays (2-byte x/y
//                                payload + 1-byte tag) and shift the already-written points.
//   0x008ca820  IsOverExtended - does the closed outline bulge past the glyph box?
//   0x008ca980  glyph_MergePathIntoGlyph - append a path (forward or reversed) to the glyph arrays.
//
// Module flags: /O2 /MD /Gy /TP
#include "types.h"

typedef int32_t int32;

struct tsiMemObject;

// The stroker's point scratch (list A). Same layout as the committed s008c9e00.cpp.
struct StrokeState {
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

// A glyph's outline storage: the three parallel arrays at +0x3c/+0x40/+0x44 and their capacities,
// the current point count (+0x36) and the last index (+0x38).
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

// The path being merged (a source point list): count +0x04, x/y/tag triplets at +0x0c (forward),
// +0x10 (count for the reverse pass), +0x18 (reverse array).
struct TPath {
    uint8_t pad00[4];
    int n;                  // +0x04
    uint8_t pad08[4];
    short* pts;             // +0x0c  3 shorts per point
    int n2;                 // +0x10
    uint8_t pad14[4];
    short* ptsR;            // +0x18
};

extern "C" {
int util_FixMul(int a, int b);                                      // 0x008d1590
int util_FixDiv(int a, int b);                                      // 0x008d16d0
void tsi_DeAllocMem(void* obj, void* p);                            // 0x008d1440
void* tsi_ReAlloc(void* mem, void* p, int bytes);                   // 0x008d1330
void AllocGlyphPointMemory(Glyph* g, int n);                        // 0x008b0230
}

// Appends two points to list A; the stroker is passed in ESI (cl register convention).
static __declspec(noinline) void FUN_008c9b70(StrokeState* st, int x1, int y1, int on1,
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

// Approximate length of the vector (dx, dy), refined with two Newton steps. cl passes dx in EAX and
// dy in ECX. 0x008c9c40. Reused name: StrokeDist.
static __declspec(noinline) int FUN_008c9c40(int dy, int dx)                // @ 0x008c9c40
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

// Adds two outline points to list A; 0x008c9b70.
static void AddTwoPointsA(StrokeState* st, int x1, int y1, int on1, int x2, int y2, int on2)
{
    FUN_008c9b70(st, x1, y1, on1, x2, y2, on2);
}

// Scales the component v of a vector of length len to length w8 (rounded, sign-aware).
static __inline int ScaleTo(int w8, int v, int len)
{
    int half = len >> 1;
    if (v < 0)
        return -((half - w8 * v) / len);
    return (w8 * v + half) / len;
}

// @ 0x008ca5b0  EndCap
// (xdir, ydir) arrive in EAX / ECX; the stroker in ESI; joinType, cx, cy, w on the stack.
void EndCap(StrokeState* st, int xdir, int ydir, int joinType, int cx, int cy, int w)
{
    int len = FUN_008c9c40(2 * ydir, 2 * xdir);
    int s = (len == 0) ? 0x10000 : util_FixDiv(2 * w, len);
    int a = util_FixMul(ydir, s);
    int b = util_FixMul(xdir, s);
    int dd = FUN_008c9c40(8 * b, 8 * a);
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

// @ 0x008ca760  glyph_EnsureSpaceForNPoints   (this in ECX, requested count in EAX)
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

// @ 0x008ca820  IsOverExtended   (path in ECX)
static int OverAbs(int v)
{
    return v < 0 ? -v : v;
}

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

// @ 0x008ca980  glyph_MergePathIntoGlyph   (glyph in EBX, path in ESI, reverse in EAX)
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
