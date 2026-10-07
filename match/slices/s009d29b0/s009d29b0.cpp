// SporeApp 0x9d29b0-0x9d3840: limb locomotion / path-section helpers (names are guesses; no PDB symbols).
// /O2 /arch:SSE /fp:fast: x87 math (fsin/fcos/fpatan/fsqrt are intrinsics), float args on the x87 stack.
#include "types.h"
#include <math.h>
#pragma intrinsic(sqrt, sin, cos, atan2, fabs)
static __forceinline float Sqrt(float x) { return (float)sqrt((double)x); }
static __forceinline float Sin(float x) { return (float)sin((double)x); }
static __forceinline float Cos(float x) { return (float)cos((double)x); }
static __forceinline float Atan2(float y, float x) { return (float)atan2((double)y, (double)x); }
static __forceinline float Fabs(float x) { return (float)fabs((double)x); }

extern "C" __declspec(dllimport) double __cdecl ceil(double);

struct Vec3 { float x, y, z; };
struct Vec2 { float x, y; };
// by-value Vec3 argument built with float loads/stores (fld/fstp), as the original passes it
struct Vec3Arg { float x, y, z; Vec3Arg(const Vec3Arg& v) : x(v.x), y(v.y), z(v.z) {} };
template <class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
template <class T> inline T Reload(const T& v) { return *(const volatile T*)&v; }

// ---- constants living in .rdata / .data of the original (values in comments) ----
extern const float kWaypointScale;     // 0x15514d0  0.5
extern const float kMinWeight;         // 0x15514cc  0.01
extern const float kLenToTime0;        // 0x15514d8  0.25
extern const float kLenToTime1;        // 0x15514d4  0.4
extern const float kSmooth;            // 0x15514dc  0.75
extern const float kTiny;              // 0x14479b0  1e-6
extern const float kSpeedBlend;        // 0x15514e0  1.0
extern const float kAmpA;              // 0x15514e8  1.0
extern const float kAmpB;              // 0x15514ec  1.0
extern float g_RampLow;                // 0x166c690  runtime tuning
extern float g_RampLowOut;             // 0x166c68c  runtime tuning
extern float g_RampScale;              // 0x1550b70  0.1
extern int g_RoundRatios;              // 0x166c048
extern const float kEpsSq;             // 0x15514bc  2.0
extern const float kEpsK;              // 0x15514c0  0.11
extern const float kBlendNear;         // 0x141b034  0.625
extern const float kBlendFar;          // 0x13fe14c  0.375
extern const float kHalfPi;            // 0x1447a08
extern const float kHalfSpeedTerm;     // 0x1485548  1.5
extern const float kZero;              // 0x1485378  0.0
extern const float kMaxAngle;          // 0x1447a2c  7.853982 (copied into a function-local static on first use)

// ------------------------------------------------------------------ path data
struct WaypointInfo { uint32_t pad0; uint8_t mFlag; };      // +4 byte tested by FUN_009d29b0
struct Bone { uint32_t pad[0x43]; float x, y, z; uint32_t pad2[(0x1f8 - 0x10c - 12) / 4]; int mChildCount; };  // x,y,z at +0x10c

struct Waypoint {                  // 0x30 bytes
    WaypointInfo* info;            // +0x00
    Bone** bone;                   // +0x04
    float x, y, z;                 // +0x08
    uint32_t pad14[(0x24 - 0x14) / 4];
    float mWeightA;                // +0x24
    float mWeightB;                // +0x28
    float mWeightC;                // +0x2c
};

struct WaypointList { Waypoint* mBegin; Waypoint* mEnd; };

struct SlotPair { int a, b; };

struct SlotOwner { uint32_t pad[9]; uint8_t* mItems; };     // items (0x108 stride) at +0x24

struct SlotItem {
    uint32_t pad[0x32];
    struct Owner2* mOwner;         // placeholder
};

struct PathSection {
    uint32_t pad0;
    uint32_t mStart;               // +0x04
    uint32_t mEnd;                 // +0x08
    uint32_t mFirstFree;           // +0x0c
    uint32_t pad10[(0x48 - 0x10) / 4];
    SlotOwner* mOwner;             // +0x48
    uint32_t pad4c[(0xbc - 0x4c) / 4];
    SlotPair* mSlots;              // +0xbc

    float ComputeLength(WaypointList* v, Waypoint* a, Waypoint* b);       // 0x9d2b90
    void AssignWeights(WaypointList* v, Waypoint* a, Waypoint* b);        // 0x9d2c80
    void Setup(WaypointList* v, Waypoint* a, Waypoint* b);                // 0x9d2dd0
    void GetSlotDirection(float* outLen, float* outDir);                  // 0x9d2f50
};

float __stdcall DistanceBetween(WaypointList* v, Waypoint* cur, bool useScale);   // 0x9d29b0

// ---------------------------------------------------------------- limb data
struct LimbPoint {                 // 0x38 bytes
    int mId;
    uint32_t pad04[(0x24 - 4) / 4];
    uint8_t mActive;               // +0x24
    uint32_t pad25[(0x38 - 0x28) / 4];
    bool Check();                  // 0x9d0c10
    void Activate();               // 0x9d0280
};

struct Limb {                      // 0x104 bytes
    uint32_t mCount;               // +0x00
    uint32_t pad04[(0x4c - 4) / 4];
    LimbPoint* mPointsBegin;       // +0x4c
    LimbPoint* mPointsEnd;         // +0x50
    uint32_t pad54[(0x84 - 0x54) / 4];
    float mAccum;                  // +0x84
    float mPhase;                  // +0x88
    uint32_t pad8c[(0xbc - 0x8c) / 4];
    uint32_t* mIdsBegin;           // +0xbc
    uint32_t* mIdsEnd;             // +0xc0
    uint32_t padc4[(0xd0 - 0xc4) / 4];
    float mRatio;                  // +0xd0
    uint32_t padd4[(0x104 - 0xd4) / 4];
    float GetA();                  // 0x9d0c90
    float GetB();                  // 0x9d0db0
    void Compute(void* item, void* a, void* b, void* c, void* d);   // 0x9d24c0
    float GetStepTime(float speed);  // 0x9d2700
    float GetStepTime2(Vec3Arg vel); // 0x9d25b0
};

struct LimbParams {
    uint32_t mCount;
    void* mItems[0x1e];
    // +0x7c, +0xdc, +0x13c, +0x140 are consecutive arrays indexed by limb
};

struct MoveInfo { uint32_t pad[0xd9]; float vx, vy; };      // +0x364, +0x368
struct MoveObj { MoveInfo* info; uint32_t pad[(0x70 - 4) / 4]; float mScale; };   // +0x70

struct XItem { uint32_t pad[0x16c / 4]; };

struct Locomotion {
    uint32_t pad0[2];
    float mSmoothedSpeed;          // +0x08
    float mSmoothedTurn;           // +0x0c
    Limb* mLimbsBegin;             // +0x10
    Limb* mLimbsEnd;               // +0x14
    uint32_t pad18[(0x24 - 0x18) / 4];
    uint8_t* mItemsBegin;          // +0x24 (0x108 stride)
    uint8_t* mItemsEnd;            // +0x28
    uint32_t pad2c[(0x38 - 0x2c) / 4];
    Waypoint* mWaypointsBegin;     // +0x38
    Waypoint* mWaypointsEnd;       // +0x3c
    uint32_t pad40[(0x4c - 0x40) / 4];
    Vec3 mVelocity;                // +0x4c
    Vec3 mPrevVelocity;            // +0x58
    float mSpeed;                  // +0x64
    float mPrevSpeed;              // +0x68

    bool IsPointUnique(LimbPoint* p);                          // 0x9d3020
    void RefreshPoints();                                      // 0x9d30b0
    void ClassifyLimbs();                                      // 0x9d3170
    void Integrate(Vec3* vel, float speed);                    // 0x9d3200
    void UpdatePhases();                                       // 0x9d32d0
    void ComputeLimbs(LimbParams* p);                          // 0x9d33a0
    Limb* FindLimbAboveThreshold(float threshold);             // 0x9d3410
    void ComputeRatios();                                      // 0x9d34a0
    float GetMaxSpeed();                                       // 0x9d3530
    float GetStepScale(float f);                               // 0x9d3580
    float GetAmplitude(MoveObj* o, float angle);               // 0x9d3610
    float GetStepRate(MoveObj* o, float f, float angle);       // 0x9d3710
    float GetStepScale2(float f);                              // 0x9d3790
    float GetTurnFactor(Vec3* v);                              // 0x9d3840
};

float __cdecl FUN_009cdbe0(float a, float b, float c, float d, float e);   // 0x9cdbe0

// @ 0x9d29b0
float __stdcall DistanceBetween(WaypointList* v, Waypoint* cur, bool useScale)
{
    Waypoint* begin = v->mBegin;
    int count = (int)(v->mEnd - begin);
    int idx = (int)(cur - begin);
    float before = 0.0f;
    float after = 0.0f;
    for (int i = idx - 1; i >= 0; --i) {
        Waypoint* w = &begin[i];
        if (w->info->mFlag != 0 || i == 0 || w->z < cur->z) {
            if (useScale) {
                before = w->z * kWaypointScale;
            } else {
                float dx = cur->x - w->x;
                float dy = cur->y - w->y;
                float dz = cur->z - w->z;
                dy = Reload(dy);   // the original rounds dy/dz to float (SSE subss + spill) but keeps dx on the x87 stack
                dz = Reload(dz);
                before = Sqrt(dy * dy + dz * dz + dx * dx);
            }
            break;
        }
    }
    for (int i = idx + 1; i < count; ++i) {
        Waypoint* w = &begin[i];
        if (w->info->mFlag != 0 || i == count - 1 || w->z < cur->z) {
            if (useScale) {
                after = w->z * kWaypointScale;
            } else {
                float dx = cur->x - w->x;
                float dy = cur->y - w->y;
                float dz = cur->z - w->z;
                dy = Reload(dy);
                dz = Reload(dz);
                after = Sqrt(dx * dx + dy * dy + dz * dz);
            }
            break;
        }
    }
    if (before > kMinWeight && after > kMinWeight)
        return before > after ? after : before;
    if (before > kMinWeight)
        return before;
    if (after < kMinWeight)
        return kMinWeight;
    return after;
}

// @ 0x9d2b90
float PathSection::ComputeLength(WaypointList* v, Waypoint* a, Waypoint* b)
{
    double dx = (double)a->x - b->x;   // x87, never rounded to float
    float dy = a->y - b->y;
    float dz = a->z - b->z;
    dy = Reload(dy);   // dy/dz rounded to float (SSE in the original), dx stays on the x87 stack
    dz = Reload(dz);
    float total = 0.0f;
    uint32_t start = mStart;
    if (start <= mEnd) {
        int n = (int)(mEnd - start) + 1;
        Waypoint* p = &v->mBegin[start];
        Bone* prev = *a->bone;
        do {
            Bone* cur = *p->bone;
            float ex = prev->x - cur->x;
            float ey = prev->y - cur->y;
            float ez = prev->z - cur->z;
            ey = Reload(ey);
            ez = Reload(ez);
            ++p;
            --n;
            total = Sqrt(ex * ex + ey * ey + ez * ez) + total;
            prev = cur;
        } while (n != 0);
    }
    return (float)sqrt(dy * dy + dz * dz + dx * dx) * kBlendFar + total * kBlendNear;
}

// @ 0x9d2c80
void PathSection::AssignWeights(WaypointList* v, Waypoint* a, Waypoint* b)
{
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    a->mWeightA = 0.0f;
    a->mWeightB = 0.0f;
    a->mWeightC = 1.0f;
    float len = Sqrt(dy * dy + dx * dx);
    for (uint32_t i = mStart + 1; i < mEnd; ++i) {
        Waypoint* p = &v->mBegin[i];
        float inv = 1.0f / len;
        float ax = p->x - a->x;
        float bx = p->x - b->x;
        float ay = p->y - a->y;
        float by = p->y - b->y;
        float t = ((Sqrt(ay * ay + ax * ax) - Sqrt(by * by + bx * bx)) * inv + 1.0f) * 0.5f;
        // NaN (a == b) clamps to 0: the original tests 0 < t first
        if (0.0f < t) {
            if (1.0f < t)
                t = 1.0f;
        } else {
            t = 0.0f;
        }
        p->mWeightA = t;
        p->mWeightB = Sin(t * 3.1415927f);
        p->mWeightC = Cos(t * 3.1415927f);
    }
    b->mWeightA = 1.0f;
    b->mWeightB = 0.0f;
    b->mWeightC = -1.0f;
}

// @ 0x9d2dd0
void PathSection::Setup(WaypointList* v, Waypoint* a, Waypoint* b)
{
    Waypoint* begin = v->mBegin;
    int count = (int)(v->mEnd - begin);
    Waypoint* cur = begin;
    for (int i = 0; i < count; ++i, ++cur) {
        if ((*cur->bone)->mChildCount == 0) {
            mFirstFree = (uint32_t)(cur - begin);
            break;
        }
    }
    mStart = (uint32_t)(a - begin);
    mEnd = (uint32_t)(b - begin);
    uint8_t* items = mOwner->mItems;
    uint8_t* item0 = (uint8_t*)(mSlots->a * 0x108 + items);
    if (a != b) {
        float len = ComputeLength(v, a, b);
        float* item1 = (float*)(mSlots->b * 0x108 + 0xa8 + items);
        float f = kLenToTime0 * len;
        item1[1] = kLenToTime1 * len;
        item1[0] = f;
        *(float*)(item0 + 0xa8) = f;
        *(float*)(item0 + 0xac) = item1[1];
        AssignWeights(v, a, b);
        return;
    }
    bool flag;
    if (item0 == 0 || *(uint8_t***)(item0 + 200) == 0 || **(uint8_t***)(item0 + 200) == 0)
        flag = false;
    else
        flag = (**(uint8_t***)(item0 + 200))[0x3f5] != 0;
    float r = DistanceBetween(v, a, flag);
    *(float*)(item0 + 0xa8) = r;
    *(float*)(item0 + 0xac) = r;
}

// @ 0x9d2f50
void PathSection::GetSlotDirection(float* outLen, float* outDir)
{
    uint8_t* items = mOwner->mItems;
    int i0 = mSlots->a * 0x108;
    int i1 = mSlots->b * 0x108;
    float dy = *(float*)(i0 + items) - *(float*)(i1 + items);
    float dx = -(*(float*)(i0 + 4 + items) - *(float*)(i1 + 4 + items));
    outDir[1] = dy;
    outDir[0] = dx;
    outDir[2] = 0.0f;
    float len = Sqrt(dy * dy + dx * dx);
    if (outLen)
        *outLen = len;
    if (len != 0.0f) {
        float inv = 1.0f / len;
        outDir[0] = inv * outDir[0];
        outDir[1] = inv * outDir[1];
        outDir[2] = outDir[2] * inv;
    }
}

// @ 0x9d3020
bool Locomotion::IsPointUnique(LimbPoint* p)
{
    uint32_t nLimbs = (uint32_t)(mLimbsEnd - mLimbsBegin);
    for (uint32_t i = 0; i < nLimbs; ++i) {
        Limb* limb = &mLimbsBegin[i];
        uint32_t nPoints = (uint32_t)(limb->mPointsEnd - limb->mPointsBegin);
        LimbPoint* e = limb->mPointsBegin;
        for (uint32_t j = 0; j < nPoints; ++j, ++e) {
            if (p != e && p->mId == e->mId)
                return false;
        }
    }
    return true;
}

// @ 0x9d30b0
void Locomotion::RefreshPoints()
{
    uint32_t nLimbs = (uint32_t)(mLimbsEnd - mLimbsBegin);
    for (uint32_t i = 0; i < nLimbs; ++i) {
        Limb* limb = &mLimbsBegin[i];
        uint32_t nPoints = (uint32_t)(limb->mPointsEnd - limb->mPointsBegin);
        for (uint32_t j = 0; j < nPoints; ++j) {
            LimbPoint* pt = &limb->mPointsBegin[j];
            int active;
            if (IsPointUnique(pt) && pt->Check())
                active = 1;
            else
                active = 0;
            pt->mActive = (char)active;
            if (pt->mActive)
                pt->Activate();
        }
    }
}

// @ 0x9d3170
void Locomotion::ClassifyLimbs()
{
    uint32_t nLimbs = (uint32_t)(mLimbsEnd - mLimbsBegin);
    uint32_t nWaypoints = (uint32_t)(mWaypointsEnd - mWaypointsBegin);
    for (uint32_t i = 0; i < nLimbs; ++i) {
        Limb* limb = &mLimbsBegin[i];
        if (nWaypoints != 0) {
            limb->mCount = 0;
        } else if ((uint32_t)(limb->mIdsEnd - limb->mIdsBegin) < 7) {
            limb->mCount = (uint32_t)(Reload(limb->mIdsEnd) - limb->mIdsBegin);
        } else {
            limb->mCount = 7;
        }
    }
}

// @ 0x9d3200
void Locomotion::Integrate(Vec3* vel, float speed)
{
    mPrevVelocity = mVelocity;
    float keep = 1.0f - kSmooth;
    mVelocity.x = vel->x;
    mVelocity.y = vel->y;
    mVelocity.z = vel->z;
    mVelocity.z = 0.0f;
    mSmoothedTurn = mSmoothedTurn * kSmooth + keep * speed;
    mSmoothedSpeed = mSmoothedSpeed * kSmooth +
        Sqrt(mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y + mVelocity.z * mVelocity.z) * keep;
    mPrevSpeed = mSpeed;
    mSpeed = speed;
    if (mSmoothedSpeed <= kTiny && mSmoothedSpeed != kTiny)
        mSmoothedSpeed = 0.0f;
    if (Fabs(mSmoothedTurn) < kTiny)
        mSmoothedTurn = 0.0f;
}

// @ 0x9d32d0
void Locomotion::UpdatePhases()
{
    uint32_t nLimbs = (uint32_t)(mLimbsEnd - mLimbsBegin);
    for (uint32_t i = 0; i < nLimbs; ++i) {
        Limb* limb = &mLimbsBegin[i];
        float v = (Fabs(mSpeed) * kEpsK) /
                  (Sqrt(mVelocity.y * mVelocity.y + mVelocity.z * mVelocity.z + mVelocity.x * mVelocity.x) * kEpsSq + 1.0f) +
                  limb->mAccum;
        limb->mAccum = v;
        if (0.0f < v) {
            if (2.0f < v)
                v = 2.0f;
        } else {
            v = 0.0f;
        }
        limb->mAccum = v;
    }
}

// @ 0x9d33a0
void Locomotion::ComputeLimbs(LimbParams* p)
{
    uint32_t count = p->mCount;
    uint8_t* base = (uint8_t*)p;
    for (uint32_t i = 0; i < count; ++i) {
        mLimbsBegin[i].Compute(p->mItems[i], base + 0x7c + 0x10 * i, base + 0x7c + 0x60 + 0x10 * i,
                               base + 0x140 + 0x2d0 * i, base + 0x13c);
    }
}

// @ 0x9d3410
Limb* Locomotion::FindLimbAboveThreshold(float threshold)
{
    uint32_t n = (uint32_t)(mLimbsEnd - mLimbsBegin);
    if (n > 6)
        return 0;
    Limb* limb = mLimbsBegin;
    for (int i = 0; i < (int)n; ++i, ++limb) {
        float ratio = limb->GetA() / limb->GetB();
        if (threshold < ratio && ratio > 1.0f)
            return limb;
    }
    return 0;
}

// @ 0x9d34a0
void Locomotion::ComputeRatios()
{
    float base = mLimbsBegin[0].GetB();
    int n = (int)(mLimbsEnd - mLimbsBegin);
    for (int i = 1; i < n; ++i) {
        Limb* limb = &mLimbsBegin[i];
        limb->mRatio = base / limb->GetB();
        if (g_RoundRatios != 0)
            limb->mRatio = (float)ceil(limb->mRatio);
    }
}

// @ 0x9d3530
float Locomotion::GetMaxSpeed()
{
    float a = Fabs(mSpeed) * kSpeedBlend;
    float b = Sqrt(mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y + mVelocity.z * mVelocity.z);
    return Max(b, a);
}

// @ 0x9d3580
float Locomotion::GetStepScale(float f)
{
    float s = Sin(mLimbsBegin->mPhase * kHalfPi) * *(float*)((uint8_t*)mLimbsBegin + 0x64);
    if ((mItemsEnd - mItemsBegin) / 0x108 != 0 && (mWaypointsEnd - mWaypointsBegin) == 0)
    {
        float r = mLimbsBegin->GetStepTime(mSpeed);
        float q = r / s;
        return q * f;
    }
    float r = mLimbsBegin->GetStepTime(mSpeed);
    float q = r * kHalfSpeedTerm;
    q = q / s;
    return q * f;
}

// @ 0x9d3610
float Locomotion::GetAmplitude(MoveObj* o, float angle)
{
    if (g_RampScale > kZero) {
        float scale = o->mScale;
        Vec2* v = (Vec2*)&o->info->vx;
        float vx = v->x * scale;
        float vy = v->y * scale;
        float speed = Sqrt(vy * vy + vx * vx);
        static const float sMax = kMaxAngle;   // 0x166c694 (guard bit 1 of 0x166c698)
        float a = Fabs(angle);
        float t = g_RampLow < a ? a : g_RampLow;
        if (sMax < t)
            t = sMax;
        return (((kAmpA - g_RampLowOut) / (sMax - g_RampLow)) * g_RampScale * t) * speed + 1.0f;
    }
    return 1.0f;
}

// @ 0x9d3710
float Locomotion::GetStepRate(MoveObj* o, float f, float angle)
{
    float rate = 0.0f;
    if (Fabs(mSpeed) > kTiny) {
        float scale = GetStepScale(f);
        if (scale > kTiny) {
            float amp = GetAmplitude(o, angle);
            rate = amp * (Fabs(mSpeed) / scale * kAmpB);
        }
    }
    return rate;
}

// @ 0x9d3790
float Locomotion::GetStepScale2(float f)
{
    Limb* limb = mLimbsBegin;
    float s = Sin(limb->mPhase * kHalfPi) * *(float*)((uint8_t*)limb + 0x64);
    if ((mItemsEnd - mItemsBegin) / 0x108 != 0 && (mWaypointsEnd - mWaypointsBegin) == 0)
    {
        float r = limb->GetStepTime2(*(Vec3Arg*)&mVelocity);
        float q = r / s;
        return q * f;
    }
    float r = limb->GetStepTime2(*(Vec3Arg*)&mVelocity);
    float q = r * kHalfSpeedTerm;
    q = q / s;
    return q * f;
}

// @ 0x9d3840
float Locomotion::GetTurnFactor(Vec3* v)
{
    float vlen = Sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    float slen = Sqrt(mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y + mVelocity.z * mVelocity.z);
    extern const float kFactorA, kFactorB, kFactorC, kFactorD;   // 0x15514f0, 0x15514f4, 0x15514f8, 0x15514fc
    float k = kFactorA;
    if ((slen * vlen) * 0.5f < (mVelocity.y * v->y + mVelocity.z * v->z) + v->x * mVelocity.x)
        k = kFactorB;
    float f = FUN_009cdbe0(slen, 0.0f, kFactorD, kFactorC * k, 0.0f) * vlen;
    float ang = Atan2(mVelocity.x, mVelocity.y);
    float c = Cos(ang) * (f + 1.0f);
    float s = (f * 1.2f + 1.0f) * Sin(ang);
    return Sqrt(c * c + s * s);
}
