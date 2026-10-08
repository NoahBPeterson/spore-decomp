// Slice s008c9e00 -- T2K (Type 2000 font scaler) stroker: lineJoin (0x008c9e00, 1960 bytes).
//
// Joins two stroked line segments at the corner (x1,y1): the previous point is (x0,y0), the next one
// (x2,y2), the half stroke width w. The offset lines of both segments (normal * w) are intersected
// and the resulting outline points are appended to one of the stroker's two point lists (the outer
// side through addPointA/addPointB, the inner one through the other). joinType 0 = miter (falling
// back to a bevel when the miter gets too long), 1 = round-ish (extra construction points),
// 2 = bevel. The offset vector of the previous join is cached in the stroker (offX/offY, keyed by
// the segment counter) so a segment's normal is computed once.
//
// Names: lineJoin is the dev-PDB name; everything else is Claude-coined from the algorithm.
// Dist (0x008c9c40, eax/ecx), FUN_008c9ca0 (0x008c9ca0, ecx/edx + stack) and FUN_008c9b70
// (0x008c9b70, stroker in esi) are TU-local helpers with cl's register convention; their real
// bodies are given here so the call sites get that convention. Only lineJoin is claimed.
//
// Module flags: /O2 /MD /Gy /TP
#include "types.h"

typedef int32_t int32;

struct tsiMemObject;

struct StrokeState {
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

extern "C" {
void* tsi_ReAlloc(void* mem, void* p, int bytes);                   // 0x008d1330
int util_FixMul(int a, int b);                                      // 0x008d1590
int util_FixDiv(int a, int b);                                      // 0x008d16d0
void util_ComputeIntersection(short x1, short y1, short x2, short y2, short x3, short y3,
                              short x4, short y4, short* ox, short* oy);   // 0x008d1890
}

// Appends one point (x, y, onCurve) to list A / list B.
void addPointA(StrokeState* st, int x, int y, int on);              // 0x008c9b10 (cdecl)
void addPointB(StrokeState* st, int x, int y, int on);              // 0x008c9be0 (cdecl)

// Appends two points to list A; the stroker is passed in ESI.
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

// Approximate length of (dx, dy), refined with two Newton steps. cl passes dx in EAX, dy in ECX.
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

// Intersection of the segments (x1,y1)-(x2,y2) and (x3,y3)-(x4,y4). Returns 1 when both parameters
// lie in [0,1]; writes the intersection (or, for parallel lines, the midpoint of the middle points)
// to *ox, *oy. x1 in ECX, y1 in EDX.
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

// Approximate length (max + min/2).
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

// Scales the vector (vx, vy) to length w8 (rounded, sign-aware).
static __inline int ScaleTo(int w8, int v, int len)
{
    int half = len >> 1;
    if (v < 0)
        return -((half - w8 * v) / len);
    return (w8 * v + half) / len;
}

typedef void (*AddPointFn)(StrokeState*, int, int, int);

// @ 0x008c9e00  lineJoin
void lineJoin(StrokeState* st, int joinType, int x0, int y0, int x1, int y1, int outer, int index,
              int x2, int y2, int w)
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
        int d = FUN_008c9c40(2 * (y0 - y2), 2 * (x2 - x0));
        if (d == 0)
            s = 0x10000;
        else
            s = util_FixDiv(w2, d);
        int ny = util_FixMul(y0 - y2, s);
        int nx = util_FixMul(x2 - x0, s);
        int dd = FUN_008c9c40(8 * ny, 8 * nx);
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
        int d = FUN_008c9c40(2 * (y0 - y1), 2 * dx1);
        if (d == 0)
            s = 0x10000;
        else
            s = util_FixDiv(w2, d);
        o1x = util_FixMul(y0 - y1, s);
        o1y = util_FixMul(dx1, s);
        int dd = FUN_008c9c40(8 * o1x, 8 * o1y);
        if (0 < dd) {
            int w8 = w * 8;
            o1x = ScaleTo(w8, o1x, dd);
            o1y = ScaleTo(w8, o1y, dd);
        }
    }
    {
        int d = FUN_008c9c40(2 * (y1 - y2), 2 * dx2);
        if (d == 0)
            s = 0x10000;
        else
            s = util_FixDiv(w2, d);
        o2x = util_FixMul(y1 - y2, s);
        o2y = util_FixMul(dx2, s);
        int dd = FUN_008c9c40(8 * o2x, 8 * o2y);
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
            FUN_008c9b70(st, x1 + o1x, y1 + o1y, outer, x1 + o2x, y1 + o2y, outer);
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
        int d = FUN_008c9c40((short)px - x1, (short)py - y1);
        if (d <= w2 || outer == 0) {
            add(st, px, py, outer);
            return;
        }
    } else {
        if (joinType == 1) {
            // round-ish join: a short extension along the miter direction closes the corner
            int ey = (short)((short)py - (short)y1);
            int ex = (short)((short)px - (short)x1);
            int d = FUN_008c9c40(ex, ey);
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
