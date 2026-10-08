// Slice s00ca1310 -- planet-surface turn/straight/turn path solver (0x00ca1310, 2382 bytes).
//
// Given a start and an end position on the unit sphere, each with a heading vector and a turn direction
// (clockwise flag), builds the bisector frame, projects both headings into the tangent plane, measures
// their signed angles about the bisector and works out the two tangent circles of radius `radius`. It then
// finds the tangent line joining them (outer tangent when both turns go the same way, inner tangent
// otherwise) and stores the two arc lengths, the straight length and the angles in the request.
// Returns false when the circles overlap too much for an inner tangent.
//
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (scalar SSE math, x87 sqrt/fsin/fcos/fpatan).
#include <math.h>

struct Vec3 {
    float x, y, z;
};

// The request: inputs at +0x00..+0x34, results from +0x40.
struct PathRequest {
    Vec3  startPos;      // +0x00
    Vec3  endPos;        // +0x0c
    Vec3  startHeading;  // +0x18
    Vec3  endHeading;    // +0x24
    bool  startCW;       // +0x30
    bool  endCW;         // +0x31
    char  pad32[2];
    float radius;        // +0x34
    char  pad38[8];
    float c0x, c0y;      // +0x40 center of the start circle (in the tangent frame)
    float c1x, c1y;      // +0x48 center of the end circle
    float t0x, t0y;      // +0x50 tangent point on the start circle
    float t1x, t1y;      // +0x58 tangent point on the end circle
    float arc0;          // +0x60 arc length on the start circle
    float arc1;          // +0x64 arc length on the end circle
    float straight;      // +0x68 straight segment length
    float total;         // +0x6c
    float ang0;          // +0x70 start angle on the start circle
    float ang1;          // +0x74 start angle on the end circle
    float lineAng;       // +0x78 heading of the straight segment
    float lineAng2;      // +0x7c
    Vec3  side;          // +0x80 normal of the travel plane
    Vec3  dir;           // +0x8c unit vector from start to end
    Vec3  mid;           // +0x98 normalized bisector
};

extern float gTwoPi;     // 0x0169a280
extern const float kHalfPi;   // 0x0157c724
extern const float kPi;       // 0x0157c728

float SignedAngle(const Vec3* a, const Vec3* b, const Vec3* axis);   // 0x006994a0 (cdecl)

static inline void WrapInline(float& x)
{
    while (gTwoPi < x) x -= gTwoPi;
    while (x < 0.0f) x += gTwoPi;
}

struct PathSolver {
    float WrapAngle(float a);          // 0x00ca11c0
    bool  Solve(PathRequest* p);       // 0x00ca1310
};

// @ 0x00ca11c0
__declspec(noinline) float PathSolver::WrapAngle(float a)
{
    while (gTwoPi < a) a -= gTwoPi;
    while (a < 0.0f) a += gTwoPi;
    return a;
}

// @ 0x00ca1310
bool PathSolver::Solve(PathRequest* p)
{
    if (p->startPos.x == p->endPos.x && p->startPos.y == p->endPos.y && p->startPos.z == p->endPos.z) {
        p->arc0 = 0.0f;
        p->straight = 0.0f;
        p->total = 0.0f;
        return true;
    }

    float ibx = 1.0f / sqrtf(((p->endPos.x * p->endPos.x + p->endPos.y * p->endPos.y) + p->endPos.z * p->endPos.z) + 1e-8f);
    float iax = 1.0f / sqrtf((p->startPos.x * p->startPos.x + (p->startPos.y * p->startPos.y + p->startPos.z * p->startPos.z)) + 1e-8f);
    Vec3 d;
    d.x = p->startPos.x * iax + p->endPos.x * ibx;
    d.z = p->startPos.z * iax + p->endPos.z * ibx;
    d.y = p->startPos.y * iax + p->endPos.y * ibx;
    float id = 1.0f / sqrtf((d.y * d.y + (d.z * d.z + d.x * d.x)) + 1e-8f);
    d.x = id * d.x;
    d.y = d.y * id;
    d.z = d.z * id;

    float t = (p->startHeading.x * d.x + p->startHeading.z * d.z) + p->startHeading.y * d.y;
    Vec3 u;
    float ux = p->startHeading.x - t * d.x;
    u.y = p->startHeading.y - d.y * t;
    u.z = p->startHeading.z - d.z * t;
    float iu = 1.0f / sqrtf((u.y * u.y + (u.z * u.z + ux * ux)) + 1e-8f);
    u.z = u.z * iu;
    u.y = u.y * iu;
    u.x = iu * ux;
    float dist = sqrtf((p->endPos.x - p->startPos.x) * (p->endPos.x - p->startPos.x) +
                       ((p->endPos.y - p->startPos.y) * (p->endPos.y - p->startPos.y) +
                        (p->endPos.z - p->startPos.z) * (p->endPos.z - p->startPos.z)));

    float t2 = (p->endHeading.x * d.x + p->endHeading.z * d.z) + p->endHeading.y * d.y;
    Vec3 v;
    float vx = p->endHeading.x - t2 * d.x;
    v.y = p->endHeading.y - d.y * t2;
    v.z = p->endHeading.z - d.z * t2;
    float iv = 1.0f / sqrtf((v.y * v.y + (v.z * v.z + vx * vx)) + 1e-8f);
    v.y = v.y * iv;
    v.z = v.z * iv;
    v.x = iv * vx;

    Vec3 dir;
    float idist = 1.0f / dist;
    dir.z = (p->endPos.z - p->startPos.z) * idist;
    dir.x = idist * (p->endPos.x - p->startPos.x);
    dir.y = (p->endPos.y - p->startPos.y) * idist;
    Vec3 n;
    n.x = dir.y * d.z - dir.z * d.y;
    n.y = dir.z * d.x - d.z * dir.x;
    n.z = d.y * dir.x - dir.y * d.x;

    float angU = SignedAngle(&n, &u, &d);
    float angV = SignedAngle(&n, &v, &d);
    p->side = n;
    p->dir = dir;
    p->mid = d;

    bool cwA = p->startCW;
    float ta, tb;
    if (cwA) ta = angU - kHalfPi; else ta = kHalfPi + angU;
    if (p->endCW) tb = angV - kHalfPi; else tb = kHalfPi + angV;
    WrapInline(ta);
    WrapInline(tb);

    float r = p->radius;
    float c0x = cosf(ta) * r;
    float c0y = sinf(ta) * r;
    float c1x = cosf(tb) * r;
    float c1y = sinf(tb) * r + dist;
    float dx = c1x - c0x;
    float dy = c1y - c0y;
    float seg = sqrtf(dx * dx + dy * dy);
    float ang = atan2f(dy, dx);
    WrapInline(ang);

    float arc0, arc1, ta2, h, tx0, ty0, tx1, ty1;
    if (cwA == p->endCW) {
        float off = kHalfPi;
        if (!cwA) off = -off;
        float hh = ang + off;
        WrapInline(hh);
        ta2 = ta + kPi;
        tx0 = cosf(hh) * r + c0x;
        ty0 = sinf(hh) * r + c0y;
        tx1 = tx0 + dx;
        ty1 = ty0 + dy;
        WrapInline(ta2);
        float a0 = cwA ? ta2 - hh : hh - ta2;
        WrapInline(a0);
        arc0 = a0 * r;
        float tbp = tb + kPi;
        WrapInline(tbp);
        float a1 = p->endCW ? hh - tbp : tbp - hh;
        WrapInline(a1);
        arc1 = a1 * r;
        h = hh;
    } else {
        float two = r * 2.0f;
        float dd = sqrtf((c0y - c1y) * (c0y - c1y) + (c0x - c1x) * (c0x - c1x));
        if (two > dd) return false;
        float ac = acosf(two / dd);
        float h0 = cwA ? ang + ac : ang - ac;
        float hh = WrapAngle(h0);
        h = WrapAngle(hh + kPi);
        tx0 = cosf(hh) * r + c0x;
        ty0 = sinf(hh) * r + c0y;
        tx1 = cosf(h) * r + c1x;
        ty1 = sinf(h) * r + c1y;
        float ey = ty1 - ty0;
        float ex = tx1 - tx0;
        ang = WrapAngle(atan2f(ey, ex));
        seg = sqrtf(ex * ex + ey * ey);
        ta2 = WrapAngle(ta + kPi);
        float a0 = cwA ? ta2 - hh : hh - ta2;
        arc0 = WrapAngle(a0) * r;
        float tbp = WrapAngle(tb + kPi);
        float a1 = p->endCW ? h - tbp : tbp - h;
        arc1 = WrapAngle(a1) * r;
    }
    p->c0x = c0x;
    p->c0y = c0y;
    p->arc1 = arc1;
    p->c1x = c1x;
    p->c1y = c1y;
    p->straight = seg;
    p->t0x = tx0;
    p->t0y = ty0;
    p->t1x = tx1;
    p->t1y = ty1;
    p->arc0 = arc0;
    p->total = (arc1 + arc0) + seg;
    p->ang0 = ta2;
    p->ang1 = tb;
    p->lineAng = ang;
    p->lineAng2 = h;
    return true;
}
