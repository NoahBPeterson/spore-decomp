// Slice s00c423d0: SP::cLocomotiveObject::EvaluateForces (0x00c42710).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// Sums the steering-force list (tForceData, 0x2c bytes each) of a tSteeringData into *out:
// 0 = smooth repulsion from a point, 1 = smooth attraction (inverted falloff), 2 = constant force,
// 3 = repulsion around a line segment (swirl when nearest to the interior), 4 = unsmoothed repulsion.
#include "types.h"
#include <math.h>

#pragma warning(disable : 4035)

struct Vec3 { float x, y, z; };
struct SVec : Vec3 {       // cSPVector3 passed by value: user copy ctor, inline math
    SVec() {}
    SVec(const SVec& o) { x = o.x; y = o.y; z = o.z; }
    SVec(float a, float b, float c) { x = a; y = b; z = c; }
};
inline SVec Sub3(SVec a, SVec b) { return SVec(a.x - b.x, a.y - b.y, a.z - b.z); }
inline float Length3(SVec v) { return sqrtf(v.z * v.z + v.y * v.y + v.x * v.x); }
struct OutVec : Vec3 {      // cSPVector3: user copy semantics (movss copies)
    OutVec& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

struct ForceData {          // SP::tForceData, 0x2c bytes
    uint32_t type;
    uint32_t priority;
    union {
        struct { Vec3 center; float magnitude; float innerRadius; float outerRadius; } sphere;   // types 0, 1, 4
        struct { Vec3 dir; } constant;                                                           // type 2
        struct { Vec3 a; Vec3 b; float magnitude; float innerRadius; float outerRadius; } line;  // type 3
    };
};

struct SteeringData {       // SP::tSteeringData
    Vec3 curPosition;
    char pad0[0x84 - 0xc];
    ForceData* forcesBegin;
    ForceData* forcesEnd;
};

extern Vec3 kZeroVec;       // 0x0168e7e4
extern float kEpsilon;      // 0x013ec4b8 (1e-8)

Vec3* __cdecl normalized_safe(Vec3* out, const Vec3* in);                              // 0x00449c20
float __cdecl PointSegmentDistance(const Vec3* p, const Vec3* a, const Vec3* b, int* region);  // 0x00698ca0

static inline float SmoothFalloff(float dist, float lo, float hi)
{
    float c = Clamp(dist, lo, hi);
    float t = (c - lo) / (hi - lo);
    return (3.0f - t * 2.0f) * t * t;
}

// @ 0x00c42710
OutVec* __stdcall EvaluateForces(OutVec* out, SteeringData* sd)
{
    int count = (int)(sd->forcesEnd - sd->forcesBegin);
    *out = kZeroVec;
    if (count != 0) {
        int off = 0;
        do {
            ForceData* f = (ForceData*)((char*)sd->forcesBegin + off);
            Vec3 r;
            switch (f->type) {
            case 0: {
                SVec d = Sub3(*(SVec*)&sd->curPosition, *(SVec*)&f->sphere.center);
                float dx = d.x, dy = d.y, dz = d.z;
                float lo = f->sphere.innerRadius, hi = f->sphere.outerRadius;
                float len = Length3(d);
                float s = SmoothFalloff(len, lo, hi);
                if (s != 0.0f) {
                    float inv = 1.0f / (len + kEpsilon);
                    float m = f->sphere.magnitude;
                    r.y = dy * inv * s * m;
                    r.z = dz * inv * s * m;
                    r.x = m * (inv * dx * s);
                } else {
                    r = kZeroVec;
                }
                break;
            }
            case 1: {
                SVec d = Sub3(*(SVec*)&sd->curPosition, *(SVec*)&f->sphere.center);
                float dx = d.x, dy = d.y, dz = d.z;
                float lo = f->sphere.innerRadius, hi = f->sphere.outerRadius;
                float len = Length3(d);
                float s = 1.0f - SmoothFalloff(len, lo, hi);
                if (s != 0.0f) {
                    float inv = 1.0f / (len + kEpsilon);
                    float m = f->sphere.magnitude;
                    r.y = dy * inv * s * m;
                    r.z = dz * inv * s * m;
                    r.x = m * (inv * dx * s);
                } else {
                    r = kZeroVec;
                }
                break;
            }
            case 2:
                r.y = f->constant.dir.y;
                r.z = f->constant.dir.z;
                r.x = f->constant.dir.x;
                break;
            case 3: {
                SVec a = *(SVec*)&f->line.a;
                SVec b = *(SVec*)&f->line.b;
                int region;
                float dist = PointSegmentDistance(&sd->curPosition, &a, &b, &region);
                float s = 1.0f - SmoothFalloff(dist, f->line.innerRadius, f->line.outerRadius);
                if (s != 0.0f) {
                    Vec3 v;
                    if (region == 0) {
                        SVec ab = Sub3(b, a);
                        Vec3 n1, n2;
                        Vec3* p1 = normalized_safe(&n1, &a);
                        Vec3* p2 = normalized_safe(&n2, &ab);
                        v.x = (p2->y * p1->z - p2->z * p1->y) * dist;
                        v.y = (p1->x * p2->z - p2->x * p1->z) * dist;
                        v.z = (p2->x * p1->y - p1->x * p2->y) * dist;
                    } else if (region == 1) {
                        v.x = sd->curPosition.x - a.x;
                        v.y = sd->curPosition.y - a.y;
                        v.z = sd->curPosition.z - a.z;
                    } else {
                        v.x = sd->curPosition.x - b.x;
                        v.y = sd->curPosition.y - b.y;
                        v.z = sd->curPosition.z - b.z;
                    }
                    float inv = 1.0f / (dist + kEpsilon);
                    float m = f->line.magnitude;
                    r.y = v.y * inv * s * m;
                    r.z = v.z * inv * s * m;
                    r.x = m * (inv * v.x * s);
                } else {
                    r = kZeroVec;
                }
                break;
            }
            case 4: {
                SVec d = Sub3(*(SVec*)&sd->curPosition, *(SVec*)&f->sphere.center);
                float dx = d.x, dy = d.y, dz = d.z;
                float inv = 1.0f / sqrtf((dx * dx + (dy * dy + dz * dz)) + kEpsilon);
                float m = f->sphere.magnitude;
                r.y = dy * inv * m;
                r.z = dz * inv * m;
                r.x = inv * dx * m;
                break;
            }
            default:
                r = kZeroVec;
                break;
            }
            off += 0x2c;
            --count;
            out->y = r.y + out->y;
            out->x = out->x + r.x;
            out->z = out->z + r.z;
        } while (count != 0);
    }
    return out;
}

// ===========================================================================
// cLocomotiveObject helpers (0x00c423d0 .. 0x00c43270)
// ===========================================================================

inline Vec3 SubVec(const Vec3& a, const Vec3& b)
{
    Vec3 r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}

inline float DotVec(const Vec3& a, const Vec3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vec3 Normalized(const Vec3& v)
{
    Vec3 o;
    normalized_safe(&o, &v);
    return o;
}

struct SteerParam {         // context block handed to the locomotion update
    Vec3 mPosition;         // +0x00
    float mfDistance;       // +0x0c
    float mfDeltaTime;      // +0x10
    void* mpOwner;          // +0x14
};

struct ILocomotion {
    virtual void S0();
    virtual void S1();
    virtual void S2();
    virtual void ApplyMotion(SteerParam* param);        // vtable +0x0c
};

struct CSpatialObject {
    virtual void S00(); virtual void S01(); virtual void S02(); virtual void S03();
    virtual void S04(); virtual void S05(); virtual void S06(); virtual void S07();
    virtual void S08(); virtual void S09(); virtual void S10(); virtual void S11();
    virtual void S12(); virtual void S13(); virtual void S14(); virtual void S15();
    virtual void S16(); virtual void S17(); virtual void S18(); virtual void S19();
    virtual void S20(); virtual void S21(); virtual void S22(); virtual void S23();
    virtual void S24(); virtual void S25(); virtual void S26(); virtual void S27();
    virtual void S28(); virtual void S29(); virtual void S30(); virtual void S31();
    virtual void S32(); virtual void S33(); virtual void S34(); virtual void S35();
    virtual void S36(); virtual void S37(); virtual void S38(); virtual void S39();
    virtual void S40(); virtual void S41(); virtual void S42(); virtual void S43();
    virtual void S44(); virtual void S45(); virtual void S46();
    virtual void AddRef();                              // vtable +0xbc
    virtual void Release();                             // vtable +0xc0
};

template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount& operator=(const AutoRefCount& o)
    {
        T* pNew = o.mpObject;
        T* pOld = mpObject;
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            mpObject = pNew;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }
    operator T*() const { return mpObject; }
};

struct GoalZone {           // 0x3c-byte navigation goal record
    Vec3 mPosition;         // +0x00
    float mfRadius;         // +0x0c
    uint32_t mType;         // +0x10
    Vec3 mAxis0;            // +0x14
    Vec3 mAxis1;            // +0x20
    Vec3 mAxis2;            // +0x2c
    float mfExtra;          // +0x38
};

struct CLocoObject {
    virtual void S00(); virtual void S01(); virtual void S02(); virtual void S03();
    virtual void S04(); virtual void S05(); virtual void S06(); virtual void S07();
    virtual void S08(); virtual void S09(); virtual void S10();
    virtual Vec3* GetPosition();                                    // vtable +0x2c
    virtual void S12(); virtual void S13(); virtual void S14(); virtual void S15();
    virtual void S16(); virtual void S17(); virtual void S18(); virtual void S19();
    virtual void S20(); virtual void S21(); virtual void S22();
    virtual Vec3* ComputeDirection(Vec3* out, const Vec3* v);        // vtable +0x5c
    virtual void S24(); virtual void S25(); virtual void S26(); virtual void S27();
    virtual void S28(); virtual void S29(); virtual void S30(); virtual void S31();
    virtual void S32(); virtual void S33(); virtual void S34(); virtual void S35();
    virtual void S36(); virtual void S37(); virtual void S38(); virtual void S39();
    virtual void S40(); virtual void S41(); virtual void S42(); virtual void S43();
    virtual void S44(); virtual void S45(); virtual void S46(); virtual void S47();
    virtual void S48(); virtual void S49();
    virtual float GetDistance();                                    // vtable +0xc8
    virtual void S51(); virtual void S52(); virtual void S53(); virtual void S54();
    virtual void S55(); virtual void S56(); virtual void S57(); virtual void S58();
    virtual void S59(); virtual void S60(); virtual void S61();
    virtual bool HasLineOfSight();                                  // vtable +0xf8

    char mPad0[0x190 - 4];
    Vec3 mNavGoalPos;               // +0x190
    unsigned char mbHasNavGoal;     // +0x19c
    char mPad1[0x1a0 - 0x19d];
    float mfGoalTime;               // +0x1a0
    char mPad2[0x1c8 - 0x1a4];
    Vec3 mSteeredPos;               // +0x1c8
    char mPad3[0x1f4 - 0x1d4];
    GoalZone* mpZoneBegin;          // +0x1f4
    GoalZone* mpZoneEnd;            // +0x1f8
    char mPad4[0x208 - 0x1fc];
    GoalZone mDefaultZone;          // +0x208
    Vec3 mForward;                  // +0x244
    int mGoalMode;                  // +0x250
    float mfInnerRadius;            // +0x254
    float mfGoalThreshold;          // +0x258
    char mPad5[0x260 - 0x25c];
    float mfOuterRadius;            // +0x260
    char mPad6[0x270 - 0x264];
    unsigned char mbStatusFlags;    // +0x270
    char mPad7[0x490 - 0x271];
    uint32_t* mpIdBegin;            // +0x490
    uint32_t* mpIdEnd;              // +0x494
    char mPad8[0x4cc - 0x498];
    ILocomotion* mpLocomotion;      // +0x4cc

    bool HasId(unsigned int id);
    Vec3* GetGoalPosition();
    bool IsNearGoal();
    void UpdateGoalProgress(unsigned int deltaMs);
    bool InRange(float dist2, float radius);    // 0x00c41ed0 (other slice)
};

float __cdecl Dot3(const Vec3* a, const Vec3* b);   // 0x00455cc0

// @ 0x00c423d0
bool __cdecl ClosestPointsOnSegments(const Vec3* a1, const Vec3* a2, const Vec3* b1, const Vec3* b2, Vec3* outA, Vec3* outB)
{
    Vec3 u, w, v;
    w.x = b2->x - b1->x;
    w.y = b2->y - b1->y;
    w.z = b2->z - b1->z;
    v.x = a1->x - b1->x;
    v.y = a1->y - b1->y;
    v.z = a1->z - b1->z;
    if (fabs(w.x) < *(const float*)0x0146cf30 && fabs(w.y) < *(const float*)0x0146cf30 && fabs(w.z) < *(const float*)0x0146cf30)
        return false;
    u.x = a2->x - a1->x;
    u.y = a2->y - a1->y;
    u.z = a2->z - a1->z;
    if (fabs(u.x) < *(const float*)0x0146cf30 && fabs(u.y) < *(const float*)0x0146cf30 && fabs(u.z) < *(const float*)0x0146cf30)
        return false;
    float wv = w.x * v.x + w.y * v.y + w.z * v.z;
    float uw = u.x * w.x + u.y * w.y + u.z * w.z;
    float ww = w.x * w.x + w.y * w.y + w.z * w.z;
    float uu = u.x * u.x + u.y * u.y + u.z * u.z;
    float denom = uu * ww - uw * uw;
    if (fabs(denom) < *(const float*)0x0146cf30)
        return false;
    float t = (uw * wv - (u.x * v.x + u.y * v.y + u.z * v.z) * ww) / denom;
    outA->x = a1->x + t * u.x;
    outA->y = a1->y + t * u.y;
    outA->z = a1->z + t * u.z;
    float s = (t * uw + wv) / ww;
    outB->x = b1->x + s * w.x;
    outB->y = b1->y + s * w.y;
    outB->z = b1->z + s * w.z;
    return true;
}

// @ 0x00c42650
bool __cdecl SegmentsNear(const Vec3* a1, const Vec3* a2, const Vec3* b1, const Vec3* b2, Vec3* outA)
{
    Vec3 outB;
    if (ClosestPointsOnSegments(a1, a2, b1, b2, outA, &outB)) {
        float dy = outB.y - outA->y;
        float dx = outB.x - outA->x;
        float dz = outB.z - outA->z;
        float d2 = dz * dz + dx * dx + dy * dy;
        return d2 < *(const float*)0x0146cf30;
    }
    return false;
}

// @ 0x00c426e0
bool CLocoObject::HasId(unsigned int id)
{
    uint32_t* end = mpIdEnd;
    uint32_t* it = mpIdBegin;
    while (it != end && *it != id)
        ++it;
    return it != end;
}

// @ 0x00c42de0
Vec3* CLocoObject::GetGoalPosition()
{
    uint32_t* end = mpIdEnd;
    uint32_t* it = mpIdBegin;
    for (; it != end; ++it) {
        if (*it == 0x00b49a50)
            break;
    }
    if (it != end && mbHasNavGoal)
        return &mNavGoalPos;
    return &mDefaultZone.mPosition;
}

// @ 0x00c42e20
bool CLocoObject::IsNearGoal()
{
    if (mbStatusFlags & 6)
        return false;
    if (mGoalMode == 0)
        return true;

    GoalZone* zone = (mpZoneBegin != mpZoneEnd) ? mpZoneEnd - 1 : &mDefaultZone;

    switch (zone->mType) {
    case 1: {
        Vec3 v0 = zone->mAxis0;
        Vec3 v1 = zone->mAxis1;
        Vec3 v2 = zone->mAxis2;
        Vec3 p = *GetPosition();
        Vec3 n0 = Normalized(SubVec(v0, p));
        Vec3 n1 = Normalized(SubVec(v1, p));
        Vec3 n2 = Normalized(SubVec(v2, p));
        float a0 = (float)acos(DotVec(n2, n1));
        float a1 = (float)acos(DotVec(n1, n0));
        float a2 = (float)acos(DotVec(n2, n0));
        float sum = a0 + a1 + a2;
        return fabs(sum - *(const float*)0x0168e818) < 0.01f;
    }
    case 0: {
        Vec3 p = *GetPosition();
        float dz = zone->mPosition.z - p.z;
        float dx = zone->mPosition.x - p.x;
        float dy = zone->mPosition.y - p.y;
        float dist2 = dz * dz + dy * dy + dx * dx;
        switch (mGoalMode - 1) {
        case 0:
            return InRange(dist2, zone->mfRadius);
        case 1:
        case 2:
        case 3: {
            if (!InRange(dist2, zone->mfRadius))
                return false;
            Vec3 v;
            Vec3* d = ComputeDirection(&v, &mForward);
            return Dot3(d, &v) > mfGoalThreshold;
        }
        default:
            return true;
        }
    }
    default:
        return true;
    }
}

// @ 0x00c431a0
void CLocoObject::UpdateGoalProgress(unsigned int deltaMs)
{
    if (mpLocomotion == 0)
        return;
    SteerParam param;
    param.mfDeltaTime = (float)deltaMs * 0.001f;
    if (HasLineOfSight())
        param.mfDistance = GetDistance();
    else
        param.mfDistance = 0.0f;
    param.mPosition = mSteeredPos;
    param.mpOwner = this;
    mpLocomotion->ApplyMotion(&param);
    if (mGoalMode != 0)
        mfGoalTime += param.mfDeltaTime;
    mSteeredPos = param.mPosition;
}

// @ 0x00c43270
AutoRefCount<CSpatialObject>* __cdecl RemoveCopyIfNeighbors(AutoRefCount<CSpatialObject>* first, AutoRefCount<CSpatialObject>* last, AutoRefCount<CSpatialObject>* result, bool (__cdecl* pred)(CSpatialObject*))
{
    for (; first != last; ++first) {
        if (!pred(*first)) {
            *result = *first;
            ++result;
        }
    }
    return result;
}
