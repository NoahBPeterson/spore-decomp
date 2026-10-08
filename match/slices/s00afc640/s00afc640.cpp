// Slice s00afc640 -- hexagonal point-spiral generator: fills a vector of 0x18-byte point records
// with the centre point and then successive hexagon rings around it (ring i has 6*i points), either on
// a flat plane or projected onto the planet surface (cPlanetModel::DirectionToSurfacePosition).
// With a non-zero argument, only the rings from floor(arg / cell) on are generated (the inner ones
// are skipped by advancing the start position).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc; x87 sqrt/fsin/fcos with SSE)
#include "types.h"
#include <new>

extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sin, cos, sqrt)

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};

// float -> int rounding down (the module's asm helper: cvtss2si + cmovb).
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

extern const Vec3 gZeroVec3;        // 0x0167aec4
extern const Vec3 gUpVec3;          // 0x0167af18
extern const float gTwoPi;          // 0x0167af14

struct IRefCounted { virtual void AddRef(); virtual void Release(); };   // Release at +4

struct PlanetModel {
    Vec3 DirectionToSurfacePosition(const Vec3& dir);                    // 0x00b815a0
};
PlanetModel* GetPlanetModel();                                           // 0x00b3d350

// 0x18-byte point record: {flag, refcounted handle, id, position}
struct PointElem {
    bool        mFlag;
    IRefCounted* mpRef;
    int         mId;
    Vec3        mPos;
    PointElem(bool f, IRefCounted* r, int id, const Vec3& p) : mFlag(f), mpRef(r), mId(id), mPos(p) {}
    ~PointElem() { if (mpRef) mpRef->Release(); }
};

struct PointVector {
    PointElem* mpBegin;
    PointElem* mpEnd;
    PointElem* mpCapacity;
    void erase(PointElem* first, PointElem* last);                       // 0x00afc0d0
    void DoInsertValue(PointElem* pos, const PointElem& v);              // 0x00afc150
    void push_back(const PointElem& v) {
        if (mpEnd < mpCapacity) {
            ::new((void*)mpEnd++) PointElem(v);
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
    void clear() { erase(mpBegin, mpEnd); }
};

struct cHexPointGenerator {
    Vec3        mAxis;              // +0x00 reference axis (rotated about the up vector to get the ring edges)
    float       mMaxRadius;         // +0x0c outer radius
    float       mCellRadius;        // +0x10 spacing unit (hex edge = 2 * this)
    Vec3        mDirection;         // +0x14 centre direction on the planet
    float       mScale;             // +0x20 surface radius multiplier
    int         mCount;             // +0x24 (reset here)
    bool        mbFlat;             // +0x28 flat plane instead of the planet surface
    char        pad29[0x50 - 0x29];
    PointVector mPoints;            // +0x50

    void Generate(float startDist);     // @ 0x00afc640
};

static inline Vec3 Mul(const Vec3& v, float s) { return Vec3(v.x * s, v.y * s, v.z * s); }
static inline Vec3 Add(const Vec3& a, const Vec3& b) { return Vec3(a.x + b.x, a.y + b.y, a.z + b.z); }

static inline float InvLength(float x, float y, float z)
{
    return 1.0f / (float)sqrt(((x * x + y * y) + z * z) + 1e-8f);
}

// @ 0x00afc640
void cHexPointGenerator::Generate(float startDist)
{
    mCount = 0;
    const Vec3* pc = &gZeroVec3;
    if (!mbFlat) pc = &mDirection;
    Vec3 center = *pc;

    Vec3 normal;
    const Vec3* pn;
    if (!mbFlat) {
        float inv = InvLength(mDirection.x, mDirection.y, mDirection.z);
        normal.x = mDirection.x * inv;
        normal.y = mDirection.y * inv;
        normal.z = mDirection.z * inv;
        pn = &normal;
    } else {
        pn = &gUpVec3;
    }
    Vec3 up = *pn;

    mPoints.clear();

    float edge = mCellRadius * 2.0f;
    float invEdge = 1.0f / edge;
    int numRings = FloorToInt((mMaxRadius - mCellRadius) * invEdge + 1.0f);

    Vec3 side;
    side.x = up.y * mAxis.z - up.z * mAxis.y;
    side.y = up.z * mAxis.x - up.x * mAxis.z;
    side.z = up.x * mAxis.y - up.y * mAxis.x;

    float angle = 0.0f;
    float step = gTwoPi * 0.16666667f;
    Vec3 ring[6];
    for (int k = 0; k < 6; ++k) {
        float s = (float)sin(angle);
        Vec3 sv = Mul(side, s);
        float c = (float)cos(angle);
        Vec3 av = Mul(mAxis, c);
        ring[k].x = (av.x + sv.x) * edge;
        ring[k].y = (av.y + sv.y) * edge;
        ring[k].z = (av.z + sv.z) * edge;
        angle = step + angle;
    }

    int first;
    Vec3 cur;
    if (startDist == 0.0f) {
        mPoints.push_back(PointElem(false, 0, 0, center));
        first = 1;
        cur = center;
    } else {
        int k = FloorToInt(invEdge * startDist);
        first = k + 1;
        float kf = (float)k;
        cur.x = ring[5].x * kf + center.x;
        cur.y = ring[5].y * kf + center.y;
        cur.z = ring[5].z * kf + center.z;
        int a = k + 2;
        int b = numRings;
        numRings = (b < a) ? a : b;
    }

    for (int i = first; i < numRings; ++i) {
        cur.x = ring[5].x + cur.x;
        cur.y = ring[5].y + cur.y;
        cur.z = ring[5].z + cur.z;
        for (int j = 0; j < 6; ++j) {
            if (i > 0) {
                Vec3 d = ring[j];
                for (int m = i; m != 0; --m) {
                    const Vec3* p = &cur;
                    Vec3 pt;
                    if (!mbFlat) {
                        float inv = InvLength(cur.x, cur.y, cur.z);
                        float sc = mScale;
                        Vec3 sd;
                        sd.x = (cur.x * inv) * sc;
                        sd.y = (cur.y * inv) * sc;
                        sd.z = (cur.z * inv) * sc;
                        Vec3 surf = GetPlanetModel()->DirectionToSurfacePosition(cur);
                        pt.x = sd.x + surf.x;
                        pt.y = surf.y + sd.y;
                        pt.z = surf.z + sd.z;
                        p = &pt;
                    }
                    mPoints.push_back(PointElem(false, 0, 0, *p));
                    cur.x = d.x + cur.x;
                    cur.y = d.y + cur.y;
                    cur.z = d.z + cur.z;
                }
            }
        }
    }
}
