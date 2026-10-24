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

struct cPlanetModel {
    void  FUN_00c9ff40(const void* pos, float* height, float* offset);
    void* FUN_00b7f190(void* out, const Vec3* pos);
};

struct SurfaceFrame {
    float m[4];
};

struct PathNode {
    Vec3  mPos;                 // +0x00
    char  mPad[0x30];           // +0x0c
};

struct PathSplineData {
    PathNode* mpBegin;          // +0x00
    PathNode* mpEnd;            // +0x04
    char      mPad08[0x0c];     // +0x08
    Vec3      mCenter;          // +0x14
    char      mPad20[0x24];     // +0x20
};

struct PathSegment {
    Vec3  mStartPos;            // +0x00
    char  mPad0c[0x24];         // +0x0c
    bool  mStartCW;             // +0x30
    bool  mEndCW;               // +0x31
    char  mPad32[2];            // +0x32
    float mRadius;              // +0x34
    char  mPad38[8];            // +0x38
    float mCenter40x;           // +0x40
    float mCenter40y;           // +0x44
    float mCenter48x;           // +0x48
    float mCenter48y;           // +0x4c
    float mCenter50x;           // +0x50
    float mCenter50y;           // +0x54
    char  mPad58[8];            // +0x58
    float mStartTime;           // +0x60
    float mMidFlag;             // +0x64
    float mMidDuration;         // +0x68
    float mEndTime;             // +0x6c
    float mPrePhase;            // +0x70
    char  mPad74[4];            // +0x74
    float mStraightAngle;       // +0x78
    float mMidPhase;            // +0x7c
    Vec3  mBasisU;              // +0x80
    Vec3  mBasisV;              // +0x8c
};

struct PathSolver {
    char mPad[0x10];                   // +0x00
    cPlanetModel* mPlanet;             // +0x10
    float WrapAngle(float a);          // 0x00ca11c0
    bool  Solve(PathRequest* p);       // 0x00ca1310
    void  FUN_00ca1c60(PathSplineData* p);                         // 0x00ca1c60
    void  FUN_00ca1dc0(PathSegment* seg, float t, Vec3* pos, Vec3* out); // 0x00ca1dc0
    Vec3* FUN_00ca1210(Vec3* out, const PathSegment* seg, float angle); // 0x00ca1210
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

cPlanetModel* FUN_00b3d350();                                                   // 0x00b3d350
void FUN_00a78ce0(float angle, float* outSin, float* outCos);                  // 0x00a78ce0
Vec3* FUN_0059aed0(Vec3* out, const Vec3* v, const void* orient);              // 0x0059aed0
bool FUN_0059ab70(const Vec3* v);                                              // 0x0059ab70

extern Vec3 kDefaultDir;   // 0x0169a28c

// @ 0x00ca1c60
void PathSolver::FUN_00ca1c60(PathSplineData* p)
{
    PathSolver* self = this;
    FUN_00b3d350();
    Vec3* center = &p->mCenter;
    float height;
    float offset;
    self->mPlanet->FUN_00c9ff40(center, &height, &offset);

    float inv = 1.0f / sqrtf(((center->x * center->x + center->y * center->y) +
                              center->z * center->z) + 1e-8f);
    volatile float vinv = inv;
    volatile float tx = center->x * vinv;
    volatile float ty = center->y * vinv;
    volatile float tz = center->z * vinv;
    center->x = tx * height;
    center->y = ty * height;
    center->z = tz * height;

    int n = p->mpEnd - p->mpBegin;
    for (int i = 0; i < n; i++) {
        Vec3* node = (Vec3*)((char*)p->mpBegin + i * 0x3c);
        self->mPlanet->FUN_00c9ff40(node, &height, &offset);
        float ninv = 1.0f / sqrtf(((node->x * node->x + node->y * node->y) +
                                   node->z * node->z) + 1e-8f);
        node->x = (node->x * ninv) * height * offset;
        node->y = (node->y * ninv) * height * offset;
        node->z = (node->z * ninv) * height * offset;
    }
}

// @ 0x00ca1dc0
void PathSolver::FUN_00ca1dc0(PathSegment* seg, float t, Vec3* pos, Vec3* out)
{
    if (seg->mEndTime == 0.0f) {
        *pos = seg->mStartPos;
        SurfaceFrame frame;
        void* orient = FUN_00b3d350()->FUN_00b7f190(&frame, pos);
        Vec3 tmp;
        Vec3* v = FUN_0059aed0(&tmp, &kDefaultDir, orient);
        *out = *v;
        if (!FUN_0059ab70(out)) {
            *out = kDefaultDir;
        }
        return;
    }

    float tt = t;
    if (seg->mEndTime < tt)
        tt = seg->mEndTime;
    float start = seg->mStartTime;

    float cosv;
    float sinv;

    if (start <= tt) {
        if (tt < seg->mMidDuration + start || seg->mMidFlag == 0.0f) {
            float ang = seg->mStraightAngle;
            float dt = tt - start;
            FUN_00a78ce0(ang, &sinv, &cosv);
            float x = cosv * dt + seg->mCenter50x;
            float y = sinv * dt + seg->mCenter50y;
            cosv = x;
            sinv = y;
            t = ang;
        } else {
            bool cw = seg->mEndCW;
            float sign = cw ? -1.0f : 1.0f;
            float ang = WrapAngle((sign / seg->mRadius) *
                                  (tt - (seg->mMidDuration + start)) + seg->mMidPhase);
            FUN_00a78ce0(ang, &sinv, &cosv);
            float x = seg->mRadius * cosv + seg->mCenter48x;
            float y = seg->mRadius * sinv + seg->mCenter48y;
            cosv = x;
            sinv = y;
            if (!cw)
                ang = kHalfPi + ang;
            else
                ang = ang - kHalfPi;
            ang = WrapAngle(ang);
            t = ang;
        }
    } else {
        bool cw = seg->mStartCW;
        float sign = cw ? -1.0f : 1.0f;
        float ang = (sign / seg->mRadius) * tt + seg->mPrePhase;
        while (gTwoPi < ang)
            ang -= gTwoPi;
        while (ang < 0.0f)
            ang += gTwoPi;
        FUN_00a78ce0(ang, &sinv, &cosv);
        float x = seg->mRadius * cosv + seg->mCenter40x;
        float y = seg->mRadius * sinv + seg->mCenter40y;
        cosv = x;
        sinv = y;
        if (!cw)
            ang = kHalfPi + ang;
        else
            ang = ang - kHalfPi;
        while (gTwoPi < ang)
            ang -= gTwoPi;
        while (ang < 0.0f)
            ang += gTwoPi;
        t = ang;
    }

    Vec3 p;
    p.x = seg->mStartPos.x + seg->mBasisU.x * cosv + seg->mBasisV.x * sinv;
    p.y = seg->mStartPos.y + seg->mBasisU.y * cosv + seg->mBasisV.y * sinv;
    p.z = seg->mStartPos.z + seg->mBasisU.z * cosv + seg->mBasisV.z * sinv;
    *pos = p;

    float height;
    float offset;
    mPlanet->FUN_00c9ff40(pos, &height, &offset);
    float inv = 1.0f / sqrtf(((pos->x * pos->x + pos->y * pos->y) +
                              pos->z * pos->z) + 1e-8f);
    pos->x = (pos->x * inv) * height;
    pos->y = (pos->y * inv) * height;
    pos->z = (pos->z * inv) * height;

    Vec3 tmp;
    Vec3* v = FUN_00ca1210(&tmp, seg, t);
    *out = *v;
}
