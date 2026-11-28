// src/game/SPCreatureAnim/_at_009d0000.cpp -- migrated from slice(s) s009dd6a0, s009db6d0, s009da640, s009d9620, s009d8720, s009d75b0, s009d63e0, s009d5600, s009d3950, s009d29b0, s009d1b40, s009d0c90, s009cfd40 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/_at_009d0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern float g_2pi;    // 0x0155145c = 6.28318548f   (2*pi)
extern float g_eps;    // 0x014479b0 = 1.0e-6f
extern float g_m1;     // 0x013eb1bc = -1.0f
extern float g_2;      // 0x01470f1c = 2.0f
extern float g_half;   // 0x01471064 = 0.5f
#pragma intrinsic(_ReadWriteBarrier)
#include <math.h>
#include <xmmintrin.h>
#include <intrin.h>
#include <string.h>
#include <stddef.h>
#include <new>

// ---- items of slice s009cfd40 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
extern float g_2pi;    // 0x0155145c = 6.28318548f   (2*pi)
extern float g_eps;    // 0x014479b0 = 1.0e-6f
extern float g_m1;     // 0x013eb1bc = -1.0f
extern float g_2;      // 0x01470f1c = 2.0f
extern float g_half;   // 0x01471064 = 0.5f
struct SA {
    void*    q0_0;                // +0x00 pointer used by 009d0460/009d0b10
    void*    p04;                 // +0x04 pointer
    char     pad08[0x48 - 0x08];
    float    f48;                 // +0x48
    float    f4c;                 // +0x4c
    char     pad50[0x58 - 0x50];
    int      f58;                 // +0x58
    char     pad5c[0x6c - 0x5c];
    float    f6c;                 // +0x6c
    char     pad70[0x7c - 0x70];
    float    f7c;                 // +0x7c
    float    f80;                 // +0x80
    float    f84;                 // +0x84
    float    f88, f8c, f90, f94, f98;
    float    f9c;                 // +0x9c
    float    fa0;                 // +0xa0
    float    fa4;                 // +0xa4
    char     padA8[0xc8 - 0xa8];
    void*    fC8;                 // +0xc8
    char     padCC[0x114 - 0xcc];
    float    f114;                // +0x114
    char     pad118[0x350 - 0x118];
    float    f350;                // +0x350
    float    f354;                // +0x354
    float    f358;                // +0x358
    char     pad35c[0x434 - 0x35c];
    float    f434;                // +0x434

    void   Integrate(float dt, float* v, void* a3);                    // ?Bone_IntegrateVelocity@@..
    float* FA90(float* out, void* p, float a, float b, float c, float d);   // 0x009cfa90
    float* F370(float* out, void* p, float a, float b, float c);            // 0x009ce370
};
struct BN {
    float  f0, f4, f8;            // +0x00 vec3
    char   pad0c[0x58 - 0x0c];
    int    f58;                   // +0x58
    char   pad5c[0xc8 - 0x5c];
    void*  fC8;                   // +0xc8
};
struct BP {
    char  pad[0x350];
    float f350, f354, f358;       // +0x350
    char  pad35c[0x434 - 0x35c];
    float f434;                   // +0x434
};
struct HostR {
    char  pad[4];
    BN**  f4;                     // +0x04 -> array of 2 BN*
    char  pad08[0x28 - 0x08];
    float f28;                    // +0x28
    float f2c;                    // +0x2c
    float f30;                    // +0x30
    void  FUN_009d0280();
};
struct HostG {
    SA**   f0;                    // +0x00 -> one SA*
    SA**   begin;                 // +0x04
    SA**   end;                   // +0x08
    void FUN_009d0b10();
};
struct HostH {
    char  pad[4];
    SA**  begin;                  // +0x04
    SA**  end;                    // +0x08
    char  pad0c[0x34 - 0x0c];
    float f34;                    // +0x34
    void FUN_009d0b80();
};
// ---- items of slice s009cfd40 end

// ---- items of slice s009d0c90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" const float g_animEpsilon_014479b0;   // 0x014479b0  1.0e-6f
extern "C" const float g_animSentinel_014479b4;  // 0x014479b4  1.0e6f
extern "C" const float g_negSentinel_013ef654;   // 0x013ef654  -1.0e6f
extern "C" const float g_centi_013eb960;         // 0x013eb960  0.01f
extern "C" const float g_one_01485720;           // 0x01485720  1.0f
extern "C" const float g_twoPi_0155145c;         // 0x0155145c  2*pi
extern "C" const float g_dynClampLo_0166c090;    // 0x0166c090
extern "C" const float g_dynClampHi_0166c098;    // 0x0166c098
extern "C" const float g_angleScale_0166c78c;    // 0x0166c78c
extern "C" double crtFn_011e0906(double x);      // 0x011e0906
#ifndef S009D0C90_H
#endif
struct AnimBone
{
    char pad0[0x6C];
    float m_field6C;        // +0x6C
    float m_field70;        // +0x70
    float m_field74;        // +0x74
    float m_field78;        // +0x78
    float m_field7C;        // +0x7C
    float m_field80;        // +0x80
    float m_field84;        // +0x84
    float m_field88;        // +0x88
    char pad8C[0x98 - 0x8C];
    float m_field98;        // +0x98
    char pad9C[0xAC - 0x9C];
    float m_fieldAC;        // +0xAC  (the scalar the min/max reductions read)
    char padB0[0xD4 - 0xB0];
    float m_fieldD4;        // +0xD4
    float m_fieldD8;        // +0xD8
    char padDC[0x108 - 0xDC];
};
struct AnimSkeleton
{
    char pad0[0x24];
    AnimBone* m_bones;      // +0x24
};
struct AnimDynamicsLayer
{
    char pad0[4];
    AnimBone** m_begin;     // +0x04
    AnimBone** m_end;       // +0x08
    char pad0C[0x38 - 0x0C];

    void destroy();         // 0x009D0B80
};
struct AnimPhase
{
    float m_angle;          // +0x00
    float m_field04;        // +0x04
    float m_field08;        // +0x08
};
struct AnimPhaseData
{
    char pad0[4];
    float m_f04;            // +0x04
    int m_count;            // +0x08  (-1 = no phase data)
    AnimPhase* m_begin;     // +0x0C
    AnimPhase* m_end;       // +0x10
    char pad14[0x34 - 0x14];
    float m_f34;            // +0x34
    float m_f38;            // +0x38
    float m_f3c;            // +0x3C
    float m_f40;            // +0x40
    float m_f44;            // +0x44
    float m_f48;            // +0x48
    float m_f4c;            // +0x4C
    float m_f50;            // +0x50
    float m_f54;            // +0x54
    float m_f58;            // +0x58
    float m_f5c;            // +0x5C
    float m_f60;            // +0x60
    float m_f64;            // +0x64
    float m_f68;            // +0x68
    float m_f6c;            // +0x6C
    float m_f70;            // +0x70
    float m_f74;            // +0x74
    float m_f78;            // +0x78
    float m_f7c;            // +0x7C
    float m_f80;            // +0x80
    float m_f84;            // +0x84
    float m_f88;            // +0x88
    float m_f8c;            // +0x8C
    float m_f90;            // +0x90
    float m_f94;            // +0x94
    float m_f98;            // +0x98
};
struct Vec4
{
    float x, y, z, w;
};
class nSPCreatureAnimDynamics
{
public:
    char pad0[0x10];
    float m_field10[14];            // +0x10..+0x44
    AnimSkeleton* m_skeleton;       // +0x48
    AnimDynamicsLayer* m_layers;    // +0x4C
    AnimDynamicsLayer* m_layersEnd; // +0x50
    char pad54[0x60 - 0x54];
    float m_field60;                // +0x60
    float m_field64;                // +0x64
    float m_field68;                // +0x68
    float m_field6C;                // +0x6C
    float m_field70;                // +0x70
    float m_field74;                // +0x74
    float m_field78;                // +0x78
    float m_field7C;                // +0x7C
    float m_field80;                // +0x80
    float m_field84;                // +0x84
    float m_field88;                // +0x88
    char pad8C[0x98 - 0x8C];
    float m_field98;                // +0x98
    char pad9C[0xBC - 0x9C];
    int* m_activeBones;             // +0xBC
    int* m_activeBonesEnd;          // +0xC0
    char padC4[0xD4 - 0xC4];
    float m_fieldD4;                // +0xD4
    float m_fieldD8;                // +0xD8
    char padDC[0xE0 - 0xDC];
    float m_boundMin[3];            // +0xE0
    float m_boundMax[3];            // +0xEC
    float m_sum[3];                 // +0xF8

    float getMaxBoneValue() const;                                  // 0x009D0C90
    float getMinBoneValue() const;                                  // 0x009D0DB0
    int findSteepestBone() const;                                   // 0x009D0EE0
    void destroyLayers();                                           // 0x009D1050
    void computeBounds(AnimBone** bones);                           // 0x009D1090
    void getExtentAndCentre(Vec4& extent, Vec4& centre) const;      // 0x009D12C0
    void resetBoneFields(const AnimPhaseData* data);                // 0x009D13A0
    void accumulate(float dt, const AnimPhaseData* data);           // 0x009D15E0
    void computeAngles(const AnimPhaseData* data);                  // 0x009D19B0
};
static __inline const float& hkMin2(const float& a, const float& b)
{
    return a > b ? b : a;
}
static __inline const float& hkMax2(const float& a, const float& b)
{
    return a > b ? a : b;
}
// ---- items of slice s009d0c90 end

// ---- items of slice s009d1b40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int32_t  g_1550b6c;   // 0x01550b6c  layout mode (5 -> derive from game data)
extern uint32_t g_15515dc;   // 0x015515dc  enable per-entry atlas offsets
extern uint8_t  g_1551256;   // 0x01551256  enable per-entry shear correction
extern float    g_166c680;   // 0x0166c680  lazily initialised: pi/2
extern float    g_166c684;   // 0x0166c684  lazily initialised: 75deg / 30deg
extern uint32_t g_166c688;   // 0x0166c688  lazy-init bit flags
extern float    g_big;       // 0x014479b4  largest useful 1e6
extern float    g_tiny;      // 0x01551258  1e-12
struct Group                                        // 0x38 bytes
{
    void*       head;                               // +0x00  object whose +0x110 is a float
    uint8_t**   items;                              // +0x04  entry pointer array
    uint8_t**   end;                                // +0x08
    uint8_t     pad0c[0x2c];
};
struct Src                                          // layout description handed in
{
    uint8_t     pad00[0x10];
    int32_t     mode;                               // +0x10  -1 = no per-entry pass
    uint8_t*    first;                              // +0x14  0xc-byte records
    uint8_t*    last;                               // +0x18
    uint8_t     pad1c[0x20];
    float       f3c, f40, f44, f48;                 // +0x3c
    float       f4c, f50, f54, f58;                 // +0x4c
    float       f5c, f60, f64, f68;                 // +0x5c
    float       seq[14];                            // +0x6c .. +0xa3
    uint8_t     pad_a4[4];
    float       fa8;                                // +0xa8
    void*       pac;                                // +0xac
    void*       pb0;                                // +0xb0

    bool        WantsOffsets();                     // 0x009de630
};
struct Vec3
{
    float x, y, z;
};
struct Atlas                                        // object reached through Layout::f48
{
    uint8_t     pad00[0x24];
    uint8_t*    base;                               // +0x24  entry array base
};
struct Layout
{
    uint8_t     pad00[0x10];
    float       f10, f14, f18, f1c;                 // +0x10
    float       f20, f24, f28, f2c;                 // +0x20
    float       f30, f34, f38, f3c;                 // +0x30
    float       f40, f44;                           // +0x40
    Atlas*      f48;                                // +0x48
    Group*      gb;                                 // +0x4c  group array
    Group*      ge;                                 // +0x50
    uint8_t     pad54[0x0c];
    float       f60;                                // +0x60
    float       f64;                                // +0x64  accumulated advance
    float       f68, f6c, f70, f74;                 // +0x68
    float       f78, f7c, f80;                      // +0x78
    float       f84;                                // +0x84
    float       f88;                                // +0x88
    uint8_t     pad8c[0x0c];
    float       f98;                                // +0x98
    uint8_t     pad9c[0x20];
    int32_t*    ib;                                 // +0xbc
    int32_t*    ie;                                 // +0xc0
    uint8_t     padc4[0x10];
    float       fd4, fd8;                           // +0xd4
    uint8_t     paddc[0x1c];
    float       ff8;                                // +0xf8

    void        Apply(Src* s);                      // 0x009d1b40
    void        AlignLines();                       // 0x009d1c90
    void        SetupFrom(Src* s);                  // 0x009d2160
    void        BuildStops(int n, void* a2, void* a3, void* a4, int32_t* a5);  // 0x009d24c0
    float       MinThickness(Vec3 v);                // 0x009d25b0
    float       AngleScale(float angle);            // 0x009d2700

    void        GetExtents(void* extents, void* centres);   // 0x009d12c0
    void        BeginGradient(void* p);             // 0x009d13a0
    void        AddStop(float v, void* p);          // 0x009d15e0
    void        EndGradient(void* p);               // 0x009d19b0
};
struct Box                                          // six contiguous floats
{
    float ex, ey, ez;                               // extents
    float cx, cy, cz;                               // centres
};
static inline uint8_t* EntryOf(Atlas* a, int32_t i)
{
    return a->base + i * 0x108;
}
// ---- items of slice s009d1b40 end

// ---- items of slice s009d29b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) double __cdecl ceil(double);
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
#pragma intrinsic(sqrt, sin, cos, atan2, fabs)
static __forceinline float Sqrt(float x) { return (float)sqrt((double)x); }
static __forceinline float Sin(float x) { return (float)sin((double)x); }
static __forceinline float Cos(float x) { return (float)cos((double)x); }
static __forceinline float Fabs(float x) { return (float)fabs((double)x); }
struct Vec2 { float x, y; };
struct Vec3Arg { float x, y, z; Vec3Arg(const Vec3Arg& v) : x(v.x), y(v.y), z(v.z) {} };
template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
template <class T> inline T Reload(const T& v) { return *(const volatile T*)&v; }
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
// ---- items of slice s009d29b0 end

// ---- items of slice s009d3950 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_01551258;   // distance threshold
extern float DAT_01551500;   // sqrt domain constant
extern float DAT_01551504;   // gait time scale
extern float  DAT_0166c69c;                             // sScale
typedef unsigned char  uint8;
typedef unsigned int   uint32;
struct R30 {
    int   i0, i4;                                   // 0x00
    float f8, fc;                                   // 0x08
    float f10[8];                                   // 0x10

    R30& operator=(const R30& o)
    {
        i0 = o.i0;
        i4 = o.i4;
        f8 = o.f8;
        fc = o.fc;
        f10[0] = o.f10[0];
        f10[1] = o.f10[1];
        f10[2] = o.f10[2];
        f10[3] = o.f10[3];
        f10[4] = o.f10[4];
        f10[5] = o.f10[5];
        f10[6] = o.f10[6];
        f10[7] = o.f10[7];
        return *this;
    }
};
struct Obj2;
struct Bone_s009d_3950 {                                       // the object the record points at (+0x48)
    uint8  _00[0x4c];
    float  f4c, f50, f54;                           // 0x4c
    uint8  _58[0x64 - 0x58];
    float  f64;                                     // 0x64
    uint8  _68[0x80 - 0x68];
    float  f80;                                     // 0x80
};
struct Rec {
    uint8  _00[0x48];
    void*  p48;                                     // 0x48  -> Bone
    uint8  _4c[0xa4 - 0x4c];
    float  fA4;                                     // 0xa4
    float  fA8, fAC, fB0, fB4;                      // 0xa8
    uint8  _b8[0xd0 - 0xb8];
    float  fD0;                                     // 0xd0
    uint8  _d4[0x104 - 0xd4];
};
struct GaitState {
    int    state;                                   // 0x00
    int    prev;                                    // 0x04
    float  f08;                                     // 0x08
    float  f0c;                                     // 0x0c
    uint8  _10[0x38 - 0x10];
    void*  p38;                                     // 0x38  begin of the 0x30-byte record vector
    void*  p3c;                                     // 0x3c  end

    void   FUN_009d3f70(Obj2* p);                   // 0x009d3f70
};
struct Obj2 {
    void*  p00;                                     // 0x00  -> [p00 + 0x3ec] float
    uint8  _04[0x70 - 0x04];
    float  f70;                                     // 0x70
    uint8  _74[0x84 - 0x74];
    float  f84;                                     // 0x84
    float  f88;                                     // 0x88
    uint8  _8c[0xa8 - 0x8c];
    float  fa8, fac, fb0, fb4;                      // 0xa8
    uint8  _b8[0xf8 - 0xb8];
    float  ff8;                                     // 0xf8
    uint8  _fc[0x2d5 - 0xfc];
    uint8  b2d5;                                    // 0x2d5
    uint8  _2d6[0x1684 - 0x2d6];
    int    i1684;                                   // 0x1684
};
struct vector_3 { float x, y, z; };
struct AnimDyn {
    float  f00, f04, f08;                           // 0x00
    uint8  _0c[0x10 - 0x0c];
    void*  p10;                                     // 0x10  begin of the 0x104-byte record vector
    void*  p14;                                     // 0x14  end
    float  f18, f1c, f20;                           // 0x18  outputs of 0x009d42b0
    uint8  _24[0x4c - 0x24];
    float  f4c, f50, f54;                           // 0x4c
    int    i58;                                     // 0x58
    uint8  _5c[0x64 - 0x5c];
    float  f64, f68;                                // 0x64
    uint8  _6c[0x78 - 0x6c];
    float  f78, f7c, f80, f84;                      // 0x78
    uint8  _88[0xc0 - 0x88];
    float  fC0;                                     // 0xc0
    uint8  _c4[0xc8 - 0xc4];
    void*  pC8;                                     // 0xc8
    uint8  _cc[0xd0 - 0xcc];
    float  fD0, fD4, fD8;                           // 0xd0
    float  fDC, fE0, fE4, fE8, fEC, fF0, fF4;       // 0xdc
    float  fF8, fFC;                                // 0xf8

    float  FUN_009d3790(float t);                   // 0x009d3790
    float  FUN_009d3840(int x);                     // 0x009d3840
    float  FUN_009d3710(Obj2* p, float a, float b); // 0x009d3710
    float  FUN_009d3950(Obj2* p, float dt, int x);  // 0x009d3950
    float  FUN_009d3a20(Obj2* p, float a, int x, float b);  // 0x009d3a20
    void   FUN_009d3b50(float t);                   // 0x009d3b50
    vector_3* SampleBlendPos(vector_3* out, float t);        // 0x009cede0
    float     CalcBendBlendFactor(Obj2* pRoot, float t);     // 0x009cf740
    void   FUN_009d42b0(Obj2* p);                   // 0x009d42b0
};
template <class T> inline const T& eastl_max(const T& a, const T& b) { return (a < b) ? b : a; }
extern uint32 DAT_0166c6a0;                             // its guard dword
// ---- items of slice s009d3950 end

// ---- items of slice s009d5600 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_1485720;   // 0x01485720  1.0f
extern const float g_1485378;   // 0x01485378  0.0f
extern const float g_14479b0;   // 0x014479b0  1e-6f
extern const float g_1471064;   // 0x01471064  0.5f
extern const float g_13ec488;   // 0x013ec488 -0.5f
extern const float g_1551520;   // 0x01551520  3.0f
extern const float g_13f89bc;   // 0x013f89bc  1e-5f
extern const float g_15514e4;   // 0x015514e4  1.0f
extern const float g_1551524;   // 0x01551524  0.1f
typedef unsigned char u8;
struct Q4 { float x, y, z, w; };
struct Ent;
struct Obj48
{
    u8     pad00[8];
    float  f08;            // +0x08
    float  f0c;            // +0x0c
    u8     pad10[0x24 - 0x10];
    void*  o24;            // +0x24
    u8     pad28[0x80 - 0x28];
    float  f80;            // +0x80
};
struct Obj2_s009d_5600
{
    u8 raw[0x1700];
};
struct Ent
{
    u8     pad00[0x24];
    Q4     v24;            // +0x24
    u8     pad34[0x48 - 0x34];
    Obj48* o48;            // +0x48
    u8     pad4c[0x58 - 0x4c];
    int    o58;            // +0x58
    u8     o5c;            // +0x5c
    u8     o5d;            // +0x5d
    u8     pad5e[2];
    float  f60;            // +0x60
    void*  o64;            // +0x64
    void*  o68;            // +0x68
    float  f6c;            // +0x6c
    u8     pad70[8];
    float  f78;            // +0x78
    float  f7c;            // +0x7c
    float  f80;            // +0x80
    float  f84;            // +0x84
    Q4     q88;            // +0x88
    float  f98;            // +0x98
    float  f9c;            // +0x9c
    float  fa0;            // +0xa0
    float  fa4;            // +0xa4
    float  fa8;            // +0xa8
    float  fac;            // +0xac
    float  fb0;            // +0xb0
    float  fb4;            // +0xb4
    u8     padb8[4];
    int*   o_bc;           // +0xbc
    u8     padc0[8];
    Obj2_s009d_5600*  o_c8;           // +0xc8
    u8     padcc[4];
    float  fd0;            // +0xd0
    float  fd4;            // +0xd4
    float  fd8;            // +0xd8
    float  fdc;            // +0xdc
    u8     pade0[8];
    float  fe8;            // +0xe8
    u8     padec[4];
    float  ff0;            // +0xf0
    u8     padf4[4];
    float  ff8;            // +0xf8
    u8     padfc[4];
    float  f100;           // +0x100
    float  f104;           // +0x104

    void  Fn5600(Ent* p, float a);                                        // 0x009d5600
    void  Fn5b50(Ent* p, float a);                                        // 0x009d5b50
    void  Fn5f10(Ent* p, float a, float b, float c, float d);             // 0x009d5f10
    float Fn62a0(float d);                                                // 0x009d62a0

    // Collaborators (bodies live in other translation units of the original).
    void  FnCeec0(float* out, float v);                                   // 0x009ceec0
    void  FnCf080(Ent* p, float a, float b);                              // 0x009cf080
    void  Fn49b0(Ent* p, float a, float b);                               // 0x009d49b0
    void  Fn42b0(Ent* p);                                                 // 0x009d42b0
    void  Fn46d0(Ent* p);                                                 // 0x009d46d0
    void  Fn52f0(Ent* p, float a, float b, float c, float d, float e, float f); // 0x009d52f0
};
// ---- items of slice s009d5600 end

// ---- items of slice s009d63e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_15514e0;    // 1.0f
extern const float g_1447a38;    // 1.6651092f
extern const float g_166c7d4;    // exp clamp threshold
extern int         g_15509f0;
typedef unsigned int u32;
#define EASTL_FILE                                                            \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define GAIT_NAME "Anim/gait/untagged"
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                          // 0x00f473a0
void  __cdecl EastlFree(void* p);                                        // 0x00f47380
void* __cdecl FUN_011e0744(void* dst, const void* src, unsigned n);      // 0x011e0744 (game memcpy)
#define GAIT_ALLOC(n) operator new((n), GAIT_NAME, 0, 0, EASTL_FILE, 0xd1)
struct SA_s009d_63e0 {
    float f00, f04, f08;    // +0x00, +0x04, +0x08
    char  pad0c[0x18];
    float f24, f28, f2c, f30;   // +0x24 .. +0x30
    char  pad34[0x24];
    int   i58;          // +0x58
    char  pad5c[0x1c];
    float f78;          // +0x78
    float f7c;          // +0x7c
    float f80;          // +0x80
    char  pad84[0x28];
    float fac;          // +0xac
    char  padB0[0x14];
    int   iC4;          // +0xc4
    int   iC8;          // +0xc8  (phase/group object pointer)
    char  padCc[0x10];
    float fdc;          // +0xdc
    char  padE0[0x20];
    float f100;         // +0x100
    float f104;         // +0x104

    SA_s009d_63e0(const SA_s009d_63e0& o) { FUN_009ce790((SA_s009d_63e0*)&o); }
    SA_s009d_63e0& operator=(const SA_s009d_63e0& o) { FUN_009ce790((SA_s009d_63e0*)&o); return *this; }
    void FUN_009ce790(SA_s009d_63e0* src);  // 0x009ce790 (SA::FUN_009ce790)
};
struct Vec38 {
    char* b;
    char* e;
    char* c;
    Vec38* DoAllocate(unsigned n, void* a);      // 0x009d6a10
};
struct VecU32 {
    u32* b;
    u32* e;
    u32* c;
    void DoInsertValue(u32* pos, const u32& v);  // 0x009d6ef0
};
struct Anim {
    char  pad04[4];
    char* b4;           // +0x04
    char* e8;           // +0x08
    int   i0c;          // +0x0c
    char* p10;          // +0x10  (0x104-byte element array)
    char* p14;          // +0x14
    char  pad18[0xc];
    char* p24;          // +0x24  (0x108-byte SA array)
    char* p28;          // +0x28
    char  pad2c[0xc];
    char* p38;          // +0x38
    char  pad3c[0xc];
    void* ctx48;        // +0x48
    float f4c, f50, f54;    // +0x4c
    char  pad58[0xc];
    float f64;          // +0x64
    int   i68;          // +0x68
    float f6c;          // +0x6c
    float f70;          // +0x70
    float f74;          // +0x74
    char  pad78[0x2c];
    float fa4;          // +0xa4
    char  padA8[0x14];
    u32*  pbc;          // +0xbc  (indices into the SA table)

    void  FUN_009d2f50(void* out1, void* out2);   // 0x009d2f50
    float FUN_009d62a0(float x);                  // 0x009d62a0 (Ent::DistRadius)

    void  m63e0(void* param2);                    // 0x009d63e0
    float m65f0(float dt, void* e);               // 0x009d65f0
    void  m6700(float dt);                        // 0x009d6700
};
void  __cdecl FUN_009cfb00(void* a, void* b, void* c, void* d, float e, void* f, void* g);
void  __cdecl FUN_009cfd40(void* a, void* b, void* c);
void  __cdecl FUN_009c0860(void* a);
// ---- items of slice s009d63e0 end

// ---- items of slice s009d75b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_01550b24, g_01550b28, g_01550b2c, g_01550b30, g_01550b34, g_01550b38, g_01550b3c;
extern const float g_01550b44, g_01550b48, g_01550b4c, g_01550b50, g_01550b54, g_01550b58, g_01550b5c;
extern const float g_01550b60, g_01550b64, g_01550b68, g_01471064;
extern const float g_0166c024, g_0166c028, g_0166c02c, g_0166c038, g_0166c03c, g_0166c040, g_0166c044;
void* __cdecl EastlAlloc(u32 size, const char* name, int flags, u32 align, const char* file, int line);
void* __cdecl memcpy(void* d, const void* s, unsigned int n);   // 0x11e0744
static inline void FreeArr(void* p)
{
    if (p && ((int*)p)[-1])
        EastlFree(p);
}
struct Item;
struct ItemVec;
struct PtrVec {
    u32* b;
    u32* e;
    u32* c;
    u32 alloc;
    u32* DoAllocate(u32 n, u32* first, u32* last);      // 0x9d7560
    void DoAllocateN(u32 n, void* a);                   // 0x9d69b0
    PtrVec& Assign(const PtrVec& o);                    // 0x9d7bb0 operator= (named so the checker finds it)
};
struct Item {
    u32 key;
    PtrVec v;
    u32 pad14;
    float f18, f1c, f20;
    uint8_t b24;
    float f28, f2c, f30, f34;
    Item& operator=(const Item& o);                     // 0x9d7e50
    Item(const Item& o);                                // 0x9d7dd0
};
Item** __cdecl UninitCopyOut(Item** out, Item* first, Item* last, Item* dst, u32 n);   // 0x9d7ea0
void __cdecl SortRangeA(void* first, void* last, u32 pred);   // 0x9d7a40
void __cdecl SortRangeB(void* first, void* last, u32 pred);   // 0x9d79d0
void __cdecl SortRangeC(void* first, void* last, u32 pred);   // 0x9d7ab0
struct EmptyPred {};
u32 __cdecl MakePred(EmptyPred tag);                             // 0x921240
struct ItemVec {
    Item* b;
    Item* e;
    Item* c;
    u32 alloc;
    void DoAllocateN(u32 n, void* a);                   // 0x9d6a10
    ItemVec* CopyInit(ItemVec* src);                    // 0x9d86c0
    void DestroyRange(Item* first, Item* last);         // 0x9c15f0
};
struct FloatVec {
    int* b;
    int* e;
    int* c;
    u32 alloc;
    u32 pad;
};
struct S;
struct Owner {
    char pad0[0x24];
    char* arr;        // array of 0x108-byte elements
};
struct S {
    u32 w0[4];
    float wf[14];
    Owner* owner;
    ItemVec items;
    u32 itemsPad;
    float w1[22];
    u32 hw;
    FloatVec idx;
    float w2[13];
    S(const S& o);                      // 0x9d8720
    S& operator=(const S& o);           // 0x9d9620
    ~S()
    {
        FreeArr(idx.b);
        items.DestroyRange(items.b, items.e);
        FreeArr(items.b);
    }
};
struct LessIdx { bool operator()(S a, S b); };    // 0x9d7840
struct LessWord { bool operator()(S a, S b); };   // 0x9d7920
template <class T> static inline T& at(void* p, int off) { return *(T*)((char*)p + off); }
struct GaitElemInit {
    char raw[0x108];
    GaitElemInit* Init();
};
struct GaitSorter {
    char pad[0x48];
    int dummy;
    void Sort3(PtrVec* vec, float a, float b);                                         // 0x9d8020
    void Sort4(PtrVec* vec, float a, float b, float c, float d, float e, float f);     // 0x9d81f0
    void SortAll();                                                                    // 0x9d84f0
};
static inline float PX(u32 p) { return *(float*)(p + 0x7c); }
static inline float PZ(u32 p) { return *(float*)(p + 0x80); }
static inline float Sq2(float dx, float dz) { return dz * dz + dx * dx; }
static inline void SortA(u32* b, u32* e, EmptyPred pr) { SortRangeA(b, e, MakePred(pr)); }
static inline void SortB(u32* b, u32* e, EmptyPred pr) { SortRangeB(b, e, MakePred(pr)); }
struct ItemOps {
    void Query(float* a, float* b, float* c, float* d, float* e, float* f);   // 0x9cfdc0
    void Update();                                                            // 0x9d0b10
};
// ---- items of slice s009d75b0 end

// ---- items of slice s009d8720 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl EAAllocate(unsigned size, const char* tag, int a, int b, int c, int d); // 0x00f473a0
void* __cdecl mem_copy(void* dst, const void* src, unsigned n);                        // 0x011e0744 (memcpy)
struct Step;
struct Gait;
Step* __cdecl uninit_copy_step(Step* first, Step* last, Step* dst);        // 0x009d7f20
Step* __cdecl copy_backward_step(Step* first, Step* last, Step* dst);      // 0x009d7fa0
Step* __cdecl uninit_move_step(Step* first, Step* last, Step* dst);        // 0x009d7ee0
Step* __cdecl destroy_move_step(Step* first, Step* last, Step* dst);       // 0x009d6aa0
void  __cdecl destroy_step(Step* first, Step* last);                       // 0x009c15f0
Step* __cdecl copy_step(Step* first, Step* last, Step* dst);               // 0x009d6a70
void* __cdecl uninit_copy_slot(void** slot, Step* first, Step* last, Step* dst, const void* extra); // 0x009d7ea0
struct Vec32 {
    u32*  begin;   // +0x00
    u32*  end;     // +0x04
    u32*  cap;     // +0x08
    void* alloc;   // +0x0c
    Vec32() : begin(0), end(0), cap(0), alloc(0) {}
    Vec32* init_count(u32 n, const void* a);                            // 0x00a69430
    __forceinline Vec32(const Vec32& o) {
        init_count((u32)(o.end - o.begin), &o.alloc);
        ptrdiff_t bytes = (const char*)o.end - (const char*)o.begin;
        u32*      dst   = begin;
        u32* p = (u32*)mem_copy(dst, o.begin, (unsigned)bytes);
        end = p + (bytes >> 2);
    }
};
struct StepSub {
    u32*  begin;   // +0x00
    u32*  end;     // +0x04
    u32*  cap;     // +0x08
    void* alloc;   // +0x0c
    StepSub() : begin(0), end(0), cap(0), alloc(0) {}
    StepSub& operator=(const StepSub& o);                               // 0x009d7bb0
};
struct Step {
    void*  obj;       // +0x00
    StepSub sub;      // +0x04
    u32    unused14;  // +0x14
    float  f18;       // +0x18
    float  f1c;       // +0x1c
    float  f20;       // +0x20
    u8     b24;       // +0x24
    u8     pad25[3];
    float  f28;       // +0x28
    float  f2c;       // +0x2c
    float  f30;       // +0x30
    float  f34;       // +0x34

    Step() : obj(0), unused14(0), f18(0.f), f1c(0.f), f20(0.f), b24(0),
             f28(0.f), f2c(0.f), f30(0.f), f34(0.f) {}
    Step(const Step& o);                                                // 0x009d7dd0

    Step& operator=(const Step& o) {
        obj = o.obj;
        sub = o.sub;
        f18 = o.f18;
        f1c = o.f1c;
        f20 = o.f20;
        b24 = o.b24;
        f28 = o.f28;
        f2c = o.f2c;
        f30 = o.f30;
        f34 = o.f34;
        return *this;
    }
};
struct GaitSub {
    Step* begin;   // +0x00
    Step* end;     // +0x04
    Step* cap;     // +0x08
    void* alloc;   // +0x0c
    GaitSub() : begin(0), end(0), cap(0), alloc(0) {}
    GaitSub(const GaitSub& o);                                          // 0x009d86c0
};
struct Gait {
    u32 a00, a04, a08, a0c;                                             // +0x00
    float f10, f14, f18, f1c, f20, f24, f28, f2c;                       // +0x10
    float f30, f34, f38, f3c, f40, f44;                                 // +0x30
    u32 a48;                                                            // +0x48
    GaitSub sub;                                                        // +0x4c
    u32 pad5c;                                                          // +0x5c
    float f60, f64, f68, f6c, f70, f74, f78, f7c;                       // +0x60
    float f80, f84, f88, f8c, f90, f94, f98, f9c;                       // +0x80
    float fa0, fa4, fa8, fac, fb0, fb4;                                 // +0xa0
    u32 ab8;                                                            // +0xb8
    Vec32 v;                                                            // +0xbc
    u32 padcc;                                                          // +0xcc
    float fd0, fd4, fd8, fdc, fe0, fe4, fe8, fec;                       // +0xd0
    float ff0, ff4, ff8, ffc, f100;                                     // +0xf0

    Gait(const Gait& o);                                                // 0x009d8720
};
struct GaitCmp1 { bool operator()(Gait a, Gait b) const; };             // 0x009d7840
struct GaitCmp2 { bool operator()(Gait a, Gait b) const; };             // 0x009d7920
struct VectorStep {
    Step* begin;   // +0x00
    Step* end;     // +0x04
    Step* cap;     // +0x08
    void* alloc;   // +0x0c

    Step* alloc_n_copy(u32 n, const Step* first, const Step* last);      // 0x009d8660
    Step* erase(Step* first, Step* last);
    void  destroy(Step* first, Step* last);                             // 0x009c15f0
    void  insert(Step* pos, const Step& value);
    VectorStep& operator=(const VectorStep& o);
};
// ---- items of slice s009d8720 end

// ---- items of slice s009d9620 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Item_s009d_9620;
struct PtrVec_s009d_9620 {
    u32* b;
    u32* e;
    u32* c;
    u32 alloc;
    void PushSlow(u32* pos, u32* val);      // 0x9d6ef0
};
struct Item_s009d_9620 {
    u32 key;
    PtrVec_s009d_9620 v;
    u32 pad14;
    float f18, f1c, f20;
    uint8_t b24;
    float f28, f2c, f30, f34;
    Item_s009d_9620() {}
    Item_s009d_9620(const Item_s009d_9620& o);                    // 0x9d7dd0
    ~Item_s009d_9620() { FreeArr(v.b); }
};
struct ItemVec_s009d_9620 {
    Item_s009d_9620* b;
    Item_s009d_9620* e;
    Item_s009d_9620* c;
    u32 alloc;
    ItemVec_s009d_9620& operator=(const ItemVec_s009d_9620& o);   // 0x9d8fd0
    void DestroyRange(Item_s009d_9620* first, Item_s009d_9620* last);    // 0x9c15f0 range destroy
    Item_s009d_9620* Erase(Item_s009d_9620* first, Item_s009d_9620* last);          // 0x9d8e20 erase(first,last), returns first
    void DoInsertValue(Item_s009d_9620* pos, const Item_s009d_9620& v);  // 0x9d8e80
};
struct FloatVec_s009d_9620 {
    int* b;
    int* e;
    int* c;
    u32 alloc;
    u32 pad;
    FloatVec_s009d_9620& operator=(const FloatVec_s009d_9620& o);        // eastl::vector<float,sp_vector_allocator>::operator=
};
struct S_s009d_9620;
struct S_s009d_9620 {
    u32 w0[4];
    float wf[14];
    Owner* owner;
    ItemVec_s009d_9620 items;
    u32 itemsPad;
    float w1[22];
    u32 hw;
    FloatVec_s009d_9620 idx;
    float w2[13];
    S_s009d_9620(const S_s009d_9620& o);                      // 0x9d8720
    S_s009d_9620& operator=(const S_s009d_9620& o);           // 0x9d9620
    ~S_s009d_9620()
    {
        FreeArr(idx.b);
        items.DestroyRange(items.b, items.e);
        FreeArr(items.b);
    }
    void FillGroups(void* y);           // 0x9da000
    void SortGroups(u32 unused);        // 0x9da5b0 (ret 4: one unused stack arg)
};
struct LessIdx_s009d_9620 { bool operator()(S_s009d_9620 a, S_s009d_9620 b); };    // 0x9d7840
struct LessWord_s009d_9620 { bool operator()(S_s009d_9620 a, S_s009d_9620 b); };   // 0x9d7920
struct PredTag { char c; };
u32 __cdecl MakePred(PredTag tag);        // 0x921240
void __cdecl SortGroupsSmall(Item_s009d_9620* first, Item_s009d_9620* last, u32 pred);   // 0x9d9420
void __cdecl SortGroupsLarge(Item_s009d_9620* first, Item_s009d_9620* last, u32 pred);   // 0x9d9520
template <void (__cdecl *F)(Item_s009d_9620*, Item_s009d_9620*, u32)>
static inline void SortRange(Item_s009d_9620* first, Item_s009d_9620* last)
{
    F(first, last, MakePred(PredTag()));
}
static inline int ISize(const ItemVec_s009d_9620& v) { return v.e - v.b; }
static inline u32 FSize(const FloatVec_s009d_9620& v) { return v.e - v.b; }
// ---- items of slice s009d9620 end

// ---- items of slice s009da640 begin (TODO(rewrite): local stubs, replace by canonical classes)
void operator delete(void*);
struct Ops {
    void Copy(void* src);        // 0x009d8720  copy-construct this from src
    void Assign(void* src);      // 0x009d9620  assign src to this
    void Ctor();                 // 0x009d75b0  default-construct this
    void F000(void* p);          // 0x009da000
    void F5b0(void* p);          // 0x009da5b0
    void F84f0();                // 0x009d84f0
    void F1090(void* p);         // 0x009d1090
    void F30b0();                // 0x009d30b0
    void F2dd0(void* p1, void* p2, void* p3);  // 0x009d2dd0
};
struct Elem {
    char b[0x104];

    u32 FUN_009d0ee0();            // 0x009d0ee0  thiscall, reads this

    Elem() { ((Ops*)this)->Ctor(); }
    Elem(const Elem& o) { ((Ops*)this)->Copy((void*)&o); }
    Elem& operator=(const Elem& o) { ((Ops*)this)->Assign((void*)&o); return *this; }
    ~Elem()
    {
        // the element owns an eastl::vector of 0x38-byte records (each holding a counted buffer
        // at +4) at +0x4c; the record vector and its buffer are released with the -4 cookie test.
        char* p = *(char**)(b + 0x4c);
        char* e = *(char**)(b + 0x50);
        if (p != e) {
            int n = (int)(e - p - 1) / 0x38 + 1;
            do {
                void* q = *(void**)(p + 4);
                if (q && *(int*)((char*)q - 4))
                    ::operator delete(q);
                p += 0x38;
            } while (--n);
        }
        void* buf = *(void**)(b + 0x4c);
        if (buf && *(int*)((char*)buf - 4))
            ::operator delete(buf);
    }
};
struct Compare {
    void* mp;
    bool CmpA(Elem a, Elem b);   // 0x009d7840
    bool CmpB(Elem a, Elem b);   // 0x009d7920
};
struct PhaseVec {
    Elem* mpBegin;
    Elem* mpEnd;
    Elem* mpCap;
    void DoDestroyValues(Elem* first, Elem* last);   // 0x009c3240
    void Grow(Elem* pos, const Elem* value);         // 0x009dada0
};
struct U32Vec {
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCap;
    void DoInsertValue(u32* pos, const u32& value);  // 0x004558a0
};
struct Solver;
struct Bone;
struct Solver {
    bool Fn3430(Bone* a, Bone* b);   // 0x009b3430
    bool Fn5700(Bone* a, Bone* b);   // 0x009b5700
    int  Fn57b0(Bone* a, Bone* b);   // 0x009b57b0
};
int  FUN_009da170(Elem* first, int hole, int len, int top, Elem value, Compare cmp);  // 0x009da170
int  FUN_009da2d0(Elem* first, int hole, int len, int top, Elem value, Compare cmp);  // 0x009da2d0
void FUN_009d9f80(Elem* a, Elem* b);                                                  // 0x009d9f80
Elem* FUN_009d8be0(Elem* a, Elem* b, Elem* c, Compare c1, Compare c2);               // 0x009d8be0
Elem* FUN_009d8ce0(Elem* a, Elem* b, Elem* c, Compare c1, Compare c2);               // 0x009d8ce0
void FUN_009d9840(Elem* first, Elem* last, Compare cmp);                              // 0x009d9840
void FUN_009d9970(Elem* first, Elem* last, Compare cmp);                              // 0x009d9970
void FUN_009d9a90(Elem* first, Elem* last, Compare cmp);                              // 0x009d9a90
void FUN_009d9bc0(Elem* first, Elem* last, Compare cmp);                              // 0x009d9bc0
void FUN_009da730(Elem* first, Elem* last, Compare cmp);                              // 0x009da730
void FUN_009da800(Elem* first, Elem* last, Compare cmp);                              // 0x009da800
void* FUN_009d9ce0(void* a, void* b, void* c);                                        // 0x009d9ce0
struct Anim_s009d_a640 {
    int  FUN_009d3410(float f);               // 0x009d3410  thiscall, reads this
    void A640(void* ctx);                     // 0x009da640
    void A1d0();                              // 0x009db1d0
    void A270();                              // 0x009db270
    Elem* A330();                             // 0x009db330
    void A3f0(void* vec, int count);          // 0x009db3f0
    void A4d0(float f);                       // 0x009db4d0
    int  A590(void* a, void* b, int c);       // 0x009db590
    int  A630(Solver** ps, Bone** a, Bone** b, int c);  // 0x009db630
};
// ---- items of slice s009da640 end

// ---- items of slice s009db6d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SegObj {
    char pad[4];
    char active;            // +0x04
};
struct Seg {                // 0x30
    SegObj* obj;            // +0x00
    char pad[0x2c];
};
struct Part {               // 0x104
    char pad0[0xbc];
    int* ids_begin;         // +0xbc
    int* ids_end;           // +0xc0
    char pad1[0x40];        // +0xc4
    float Time();           // 0x009d0db0
};
struct Particle {           // 0x108
    char pad0[0xa8];
    float v0;               // +0xa8
    float v1;               // +0xac
    char pad1[0x14];
    int index;              // +0xc4
    char pad2[0x40];
};
struct World {
    char pad[0x3e0];
    int f3e0;               // +0x3e0
};
float __cdecl sub_9DB0B0(void* begin, void* end, int flags);      // 0x009db0b0
void __cdecl sub_9DB140(void* begin, void* end, int flags);       // 0x009db140
float* __cdecl sub_99CC70(float* out, const float* a, const float* b, float t);  // 0x0099cc70
struct Layout_s009d_b6d0 {
    char pad0[0x10];
    Part* parts_begin;      // +0x10
    Part* parts_end;        // +0x14
    char pad1[0x0c];
    char* particles;        // +0x24
    char pad2[0x10];
    Seg* seg_begin;         // +0x38
    Seg* seg_end;           // +0x3c

    int Call630(World** ctx, Seg* start, Seg* end, int total);    // 0x009db630
    void Build(float ratio, World** ctx);
};
struct Val3 {               // 0x0c -- one interpolated sample
    float x;                // +0x00
    float y;                // +0x04
    int z;                  // +0x08
};
struct Blend9 {
    char pad0[8];
    float v[3];             // +0x08
    float r[3][4];          // +0x14, only the first two floats of every row blend
    void Pos(const Blend9* a, float t, const Blend9* b);
    void All(const Blend9* a, float t, const Blend9* b);
};
struct BlendQ {
    char pad0[8];
    float q[4];             // +0x08
    float r[4][4];          // +0x18, only the first two floats of every row blend
    void All(const BlendQ* a, float t, const BlendQ* b);
};
struct Track {
    void* vtbl;             // +0x00
    int count;              // +0x04
    char pad0[0x74];        // +0x08 .. +0x7b
    float w[1];             // +0x7c
    float Channel(int i) const
    {
        return *(const float*)((const char*)this + 0x140 + i * 0xb4);
    }
    float Total();
};
struct Grid {
    char pad[0x1c];
    void* m[4][4];          // +0x1c
    void* Set(void* value, int row, int col);
};
struct Path104 {            // 0xa4
    char pad0[0x10];
    Val3* begin;            // +0x10
    Val3* end;              // +0x14
    char pad1[0x8c];
};
struct Track2 {
    char pad0[0x18];
    int count;              // +0x18
    Path104* paths;         // +0x1c
    int TotalItems();
};
// ---- items of slice s009db6d0 end

// ---- items of slice s009dd6a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short u16;
typedef int            i32;
namespace {

struct cArguments;                                        // EA::ArgScript::cArguments
struct Curve760 { void CopyInto(char* dst); };            // 0x009dc760
void  FUN_009dc760(Curve760* c, char* dst);               // 0x009dc760  CopyInto

// The ArgScript argument block.  MainArguments returns the raw 32-bit argument array.
struct cArguments {
    u32* MainArguments(int n);                            // 0x00838320
};

// The evaluated float object: picks the +0x98 vtable slot (a thiscall returning float).
struct FloatEval {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
    virtual float Eval(i32 v);                // +0x98
};

// The evaluated-argument host: self+0xc is the track2/block owner chain, self+4 is the
// float-evaluator object whose +0x98 vtable slot converts script tokens to float.
struct Self {
    u8  pad00[0x04];
    FloatEval* mEval;        // +0x04
    u8  pad08[0x04];
    i32 mOwner;              // +0x0c

    void Cmd3(cArguments* a);                         // 0x009ddca0
    void Cmd4(cArguments* a);                         // 0x009ddcf0
    void CmdTable8(cArguments* a);                    // 0x009ddd70
    void CmdTable16(cArguments* a);                   // 0x009ddf80
};

}  // (anonymous)

// A Track2 block descriptor (0xa4 bytes).  Only the touched members are named.
struct Block {
    u8  pad00[0x0c];
    i32 mHitTest;            // +0x0c  (0xffffffff = empty slot)
    i32 mPointsBegin;        // +0x10
    i32 mPointsEnd;          // +0x14
    u8  pad18[0x08];
    i32 mIdsBegin;           // +0x20
    i32 mIdsEnd;             // +0x24
    i32 mGroupsBegin;        // +0x28
    u32 mGroupsEnd;          // +0x2c
    u8  pad30[0x08];
    float mTime;             // +0x38
    float mCone[7];          // +0x3c .. +0x57
    u8  pad58[0x4c];
};

// The Track2 object.  `mBlockCount`/`mBlocks` prefix an inline data region; the walk uses
// 0xa4-byte strides.
struct Track2_s009d_d6a0 {
    u8  pad00[0x18];
    u32 mCount;              // +0x18
    Block* mBlocks;          // +0x1c

    void Grids(void* p);                              // 0x009dd780
    i32  ItemCount();                                 // 0x009dd6a0
    i32  TotalItems();                                // 0x009dc6a0
};

i32   Track2_TotalItems(Track2_s009d_d6a0* t);                       // 0x009dc6a0  Track2::TotalItems
void  FUN_009dd780(Track2_s009d_d6a0* t, void* p);                   // 0x009dd780  (defined below)
i32   FUN_009dd6a0(Track2_s009d_d6a0* t);                            // 0x009dd6a0  (defined below)
// ---- items of slice s009dd6a0 end

// @ 0x009d0280
void HostR::FUN_009d0280()
{
    BN** v = f4;
    BN*  a = v[0];
    BN*  b = v[1];
    int  offA = *(int*)((char*)a->fC8 + 0x2e4) + a->f58 * 0x2bc;
    int  offB = *(int*)((char*)b->fC8 + 0x2e4) + b->f58 * 0x2bc;
    BP*  X = (BP*)*(int*)(*(int*)(offA + 8));
    BP*  Y = (BP*)*(int*)(*(int*)(offB + 8));
    float xlen = sqrtf(X->f350 * X->f350 + X->f354 * X->f354 + X->f358 * X->f358);
    float ylen = sqrtf(Y->f350 * Y->f350 + Y->f354 * Y->f354 + Y->f358 * Y->f358);
    float dx = Y->f350 - X->f350;
    float dy = Y->f354 - X->f354;
    float dz = Y->f358 - X->f358;
    float d = sqrtf((dx * dx + dz * dz) + dy * dy);
    f28 = d;
    if (d > g_eps) {
        float f = (xlen * xlen - ylen * ylen + d * d) / ((d * xlen) * g_2);
        if (f > g_m1) {
            if (f > 1.0f)
                f = 1.0f;
        } else {
            f = g_m1;
        }
        float t = 1.0f - f * f;
        float z = 0.0f;
        float* pv = &z;
        if (0.0f <= t)
            pv = &t;
        f2c = (f / d) * xlen;
        f30 = sqrtf(*pv) * xlen;
    } else {
        f28 = 0.0f;
        f2c = g_half;
        f30 = 0.0f;
    }
}

// @ 0x009d0b10
void HostG::FUN_009d0b10()
{
    uint n = (uint)((char*)end - (char*)begin) >> 2;
    if (n != 0) {
        SA** p = begin;
        SA*  q = *f0;
        do {
            SA* e = *p++;
            --n;
            e->f9c = atan2f(e->f80, e->f7c);
            e->fa0 = atan2f(q->f114, e->f80);
            e->fa4 = atan2f(e->f84, e->f7c);
        } while (n != 0);
    }
}

// @ 0x009d0b80
void HostH::FUN_009d0b80()
{
    uint n = (uint)((char*)end - (char*)begin) >> 2;
    if (1 < n) {
        float ss = 0.0f;
        float sc = 0.0f;
        SA** p = begin;
        for (uint i = n; i != 0; --i) {
            SA* e = *p++;
            float a = e->f6c * g_2pi;
            ss = ss + sinf(a);
            sc = sc + cosf(a);
        }
        f34 = sqrtf(ss * ss + sc * sc) / (float)n;
    }
}

// @ 0x009d0c90
float nSPCreatureAnimDynamics::getMaxBoneValue() const
{
    int n = (int)(m_activeBonesEnd - m_activeBones);
    float best = g_animEpsilon_014479b0;
    for (int i = 0; i < n; i++)
    {
        const AnimBone* bone = &m_skeleton->m_bones[m_activeBones[i]];
        float v = bone->m_fieldAC;
        if (v > best)
            best = v;
    }
    return best;
}

// @ 0x009d0db0
float nSPCreatureAnimDynamics::getMinBoneValue() const
{
    int n = (int)(m_activeBonesEnd - m_activeBones);
    float best = g_animSentinel_014479b4;
    for (int i = 0; i < n; i++)
    {
        const AnimBone* bone = &m_skeleton->m_bones[m_activeBones[i]];
        float v = bone->m_fieldAC;
        if (v < best)
            best = v;
    }
    return g_animEpsilon_014479b0 > best ? g_animEpsilon_014479b0 : best;
}

// @ 0x009d0ee0
int nSPCreatureAnimDynamics::findSteepestBone() const
{
    const int* p = m_activeBones;
    int n = (int)(m_activeBonesEnd - m_activeBones);
    const AnimBone* cur = &m_skeleton->m_bones[p[0]];
    float bestDelta = 0.0f;
    int best = -1;
    for (int i = 1; i < n; i++)
    {
        float d = cur->m_fieldAC - m_skeleton->m_bones[p[i]].m_fieldAC;
        if (d > bestDelta)
        {
            bestDelta = d;
            best = i;
        }
        cur = &m_skeleton->m_bones[p[i]];
    }
    return best;
}

// @ 0x009d1050
void nSPCreatureAnimDynamics::destroyLayers()
{
    int n = (int)(m_layersEnd - m_layers);
    for (int i = 0; i < n; i++)
        m_layers[i].destroy();
}

// @ 0x009d1090
void nSPCreatureAnimDynamics::computeBounds(AnimBone** bones)
{
    int n = (int)(m_activeBonesEnd - m_activeBones);

    m_boundMin[0] = g_animSentinel_014479b4;
    m_boundMin[1] = g_animSentinel_014479b4;
    m_boundMin[2] = g_animSentinel_014479b4;
    m_boundMax[0] = g_negSentinel_013ef654;
    m_boundMax[1] = g_negSentinel_013ef654;
    m_boundMax[2] = g_negSentinel_013ef654;
    m_sum[0] = 0.0f;
    m_sum[1] = 0.0f;
    m_sum[2] = 0.0f;

    for (int i = 0; i < n; i++)
    {
        const AnimBone* b = &(*bones)[m_activeBones[i]];
        m_sum[0] += b->m_field7C;
        m_sum[1] += b->m_field80;
        m_sum[2] += b->m_field84;
        m_boundMin[0] = hkMin2(m_boundMin[0], b->m_field7C);
        m_boundMax[0] = hkMax2(b->m_field7C, m_boundMax[0]);
        m_boundMin[1] = hkMin2(m_boundMin[1], b->m_field80);
        m_boundMax[1] = hkMax2(b->m_field80, m_boundMax[1]);
        m_boundMin[2] = hkMin2(m_boundMin[2], b->m_field84);
        m_boundMax[2] = hkMax2(b->m_field84, m_boundMax[2]);
    }

    if (n > 1)
    {
        float inv = 1.0f / (float)n;
        m_sum[0] *= inv;
        m_sum[1] *= inv;
        m_sum[2] *= inv;
    }
    if (fabsf(m_sum[0]) < g_animEpsilon_014479b0)
        m_sum[0] = 0.0f;
    if (fabsf(m_sum[1]) < g_animEpsilon_014479b0)
        m_sum[1] = 0.0f;
    if (fabsf(m_sum[2]) < g_animEpsilon_014479b0)
        m_sum[2] = 0.0f;
}

// @ 0x009d12c0
void nSPCreatureAnimDynamics::getExtentAndCentre(Vec4& extent, Vec4& centre) const
{
    float cx = m_boundMin[0] + m_boundMax[0];
    float cy = m_boundMin[1] + m_boundMax[1];
    float cz = m_boundMin[2] + m_boundMax[2];
    centre.x = cx * 0.5f;
    centre.y = cy * 0.5f;
    centre.z = cz * 0.5f;

    extent.x = m_boundMax[0] - m_boundMin[0];
    extent.y = m_boundMax[1] - m_boundMin[1];
    extent.z = m_boundMax[2] - m_boundMin[2];

    int n = (int)(m_activeBonesEnd - m_activeBones);
    if (extent.x < 0.01f || (n == 2 && extent.y > extent.x))
        extent.x = 0.0f;
    if (extent.y < 0.01f || (n == 2 && extent.x > extent.y))
        extent.y = 0.0f;
}

// @ 0x009d13a0
void nSPCreatureAnimDynamics::resetBoneFields(const AnimPhaseData* data)
{
    m_field60 = 0.0f;
    m_field68 = 0.0f;
    m_field6C = 0.0f;
    m_field70 = 0.0f;
    m_field74 = 0.0f;
    m_field78 = 0.0f;
    m_field7C = 0.0f;
    m_field80 = 0.0f;
    m_field84 = 0.0f;
    m_field88 = 0.0f;
    m_fieldD4 = 0.0f;
    m_fieldD8 = 0.0f;
    m_field98 = 0.0f;

    if (data->m_count != -1)
    {
        int nIdx = (int)(m_activeBonesEnd - m_activeBones);
        int n12 = (int)(data->m_end - data->m_begin);
        int limit = (unsigned)nIdx < (unsigned)n12 ? nIdx : n12;
        if (limit != 0)
        {
            int nLayers = (int)(m_layersEnd - m_layers);
            int used = 0;
            for (int L = 0; L < nLayers; L++)
            {
                AnimDynamicsLayer& layer = m_layers[L];
                int cnt = (int)(layer.m_end - layer.m_begin);
                for (int k = 0; k < cnt; k++)
                {
                    if (used >= n12)
                        break;
                    AnimBone* b = layer.m_begin[k];
                    b->m_field6C = 0.0f;
                    b->m_field70 = 0.0f;
                    b->m_field74 = 0.0f;
                    b->m_field78 = 0.0f;
                    used++;
                }
            }
            m_field64 = 0.0f;
        }
    }

    for (int i = 0; i < 14; i++)
        m_field10[i] = 0.0f;
}

// @ 0x009d15e0
void nSPCreatureAnimDynamics::accumulate(float dt, const AnimPhaseData* data)
{
    m_field60 += data->m_f04 * dt;
    m_field68 += data->m_f44 * dt;
    m_field6C += data->m_f48 * dt;
    m_field70 += data->m_f4c * dt;
    m_field74 += data->m_f50 * dt;
    m_field78 += data->m_f54 * dt;
    m_field7C += data->m_f58 * dt;
    m_field80 += data->m_f5c * dt;
    m_field84 += (g_one_01485720 - data->m_f60 * g_centi_013eb960) * dt;
    m_field88 += data->m_f34 * dt;
    m_fieldD4 += data->m_f38 * dt;
    m_fieldD8 += data->m_f3c * dt;
    m_field98 += data->m_f40 * dt;

    if (data->m_count != -1)
    {
        int nIdx = (int)(m_activeBonesEnd - m_activeBones);
        int n12 = (int)(data->m_end - data->m_begin);
        int limit = (unsigned)nIdx < (unsigned)n12 ? nIdx : n12;
        if (limit != 0)
        {
            int nLayers = (int)(m_layersEnd - m_layers);
            int used = 0;
            float sum = 0.0f;
            for (int L = 0; L < nLayers; L++)
            {
                AnimDynamicsLayer& layer = m_layers[L];
                int cnt = (int)(layer.m_end - layer.m_begin);
                for (int k = 0; k < cnt; k++)
                {
                    if (used >= limit)
                        break;
                    AnimBone* b = layer.m_begin[k];
                    float phase = data->m_begin[used].m_angle * g_twoPi_0155145c;
                    b->m_field70 += sinf(phase) * dt;
                    b->m_field74 += cosf(phase) * dt;
                    float w = data->m_begin[used].m_field04 * dt;
                    b->m_field78 += w;
                    sum += w;
                    used++;
                }
            }
            m_field64 += sum / (float)limit;
        }
    }

    m_field10[0] += data->m_f64 * dt;
    m_field10[1] += data->m_f68 * dt;
    m_field10[2] += data->m_f6c * dt;
    m_field10[3] += data->m_f70 * dt;
    m_field10[4] += data->m_f74 * dt;
    m_field10[5] += data->m_f78 * dt;
    m_field10[6] += data->m_f7c * dt;
    m_field10[7] += data->m_f80 * dt;
    m_field10[8] += data->m_f84 * dt;
    m_field10[9] += data->m_f88 * dt;
    m_field10[10] += data->m_f8c * dt;
    m_field10[11] += data->m_f90 * dt;
    m_field10[12] += data->m_f94 * dt;
    m_field10[13] += data->m_f98 * dt;
}

// @ 0x009d19b0
void nSPCreatureAnimDynamics::computeAngles(const AnimPhaseData* data)
{
    float v = m_field64;
    if (v < g_dynClampLo_0166c090)
        v = g_dynClampLo_0166c090;
    if (v > g_dynClampHi_0166c098)
        v = g_dynClampHi_0166c098;
    m_field64 = v;

    if (data->m_count != -1)
    {
        int nIdx = (int)(m_activeBonesEnd - m_activeBones);
        int n12 = (int)(data->m_end - data->m_begin);
        int limit = (unsigned)nIdx < (unsigned)n12 ? nIdx : n12;
        if (limit != 0)
        {
            int nLayers = (int)(m_layersEnd - m_layers);
            int used = 0;
            for (int L = 0; L < nLayers; L++)
            {
                AnimDynamicsLayer& layer = m_layers[L];
                int cnt = (int)(layer.m_end - layer.m_begin);
                for (int k = 0; k < cnt; k++)
                {
                    if (used >= n12)
                        break;
                    AnimBone* b = layer.m_begin[k];
                    float y = b->m_field70;
                    float x = b->m_field74;
                    if (x * x + y * y > g_animEpsilon_014479b0)
                    {
                        float angle = atan2f(y, x) * g_angleScale_0166c78c;
                        b->m_field6C = angle - (float)crtFn_011e0906(angle);
                    }
                    else
                    {
                        b->m_field6C = 0.0f;
                    }
                    used++;
                }
            }
        }
    }
}

// @ 0x009d1b40
void Layout::Apply(Src* s)
{
    uint32_t n    = (uint32_t)((int)(s->last - s->first) / 0xc);
    uint32_t cap  = (uint32_t)(ie - ib);
    const uint32_t& limit = (cap < n) ? cap : n;
    if (limit == 0)
        return;

    int groups = (int)(ge - gb);
    if (groups <= 0)
        return;

    int      off = 0;
    uint32_t idx = 0;
    do
    {
        Group* g   = (Group*)((uint8_t*)gb + off);
        int    cnt = (int)(g->end - g->items);
        if (cnt > 0)
        {
            int srcOff = 0;
            int i      = 0;
            do
            {
                if ((int)limit <= (int)idx)
                    break;
                uint8_t* e = g->items[i];
                if (g_15515dc == 0 || s->WantsOffsets() == false)
                {
                    *(float*)(e + 0x60) = 0.0f;
                    *(void**)(e + 0x64) = 0;
                    *(void**)(e + 0x68) = 0;
                }
                else
                {
                    *(float*)(e + 0x60) = s->fa8;
                    int off2 = *(int*)(s->first + srcOff + 8) * 0x40;
                    *(uint8_t**)(e + 0x64) = *(uint8_t**)((uint8_t*)s->pac + 0x20) + off2;
                    *(uint8_t**)(e + 0x68) = *(uint8_t**)((uint8_t*)s->pb0 + 0x20) + off2;
                }
                srcOff += 0xc;
                ++idx;
                ++i;
            } while (i < cnt);
        }
        off += 0x38;
    } while (--groups != 0);
}

// @ 0x009d1c90
void Layout::AlignLines()
{
    Box b;
    GetExtents(&b.ex, &b.cx);

    int   count = (int)(ie - ib);
    float fn    = (float)count;
    if (count < 0)
        fn += 4294967296.0f;

    float lineH = ((fn + 2.0f) / fn) * b.ey;

    uint32_t mode = (uint32_t)g_1550b6c;
    if (g_1550b6c == 5)
    {
        uint8_t* a  = *(uint8_t**)((uint8_t*)f48 + 0x24);
        uint8_t* c8 = *(uint8_t**)(a + 0xc8);
        uint8_t* arr = *(uint8_t**)(c8 + 0x2e4);
        uint8_t* rec = *(uint8_t**)(arr + *(int*)(a + 0x58) * 700 + 4);
        int cnt = (*(int*)(rec + 0x2e8) - *(int*)(rec + 0x2e4)) / 700;
        mode = (uint32_t)(cnt % 5);
    }

    int groups = (int)(ge - gb);

    switch (mode)
    {
    case 1:
    {
        if (groups <= 0)
            return;
        int off = 0;
        int gc  = groups;
        do
        {
            Group* g   = (Group*)((uint8_t*)gb + off);
            int    cnt = (int)(g->end - g->items);
            if (cnt > 0)
            {
                uint8_t** it = g->items;
                int       k  = cnt;
                do
                {
                    uint8_t* e    = *it;
                    float    flag = (*(float*)(e + 0x7c) <= b.cx) ? 0.5f : 0.0f;
                    float    x;
                    if (b.ey > 0.0f)
                        x = (*(float*)(e + 0x80) - (b.cy - b.ey * 0.5f)) / lineH;
                    else
                        x = 0.0f;
                    float sum = x + flag;
                    *(float*)(e + 0x6c) = sum - (float)floor((double)sum);
                    ++it;
                } while (--k);
            }
            off += 0x38;
        } while (--gc);
        return;
    }
    case 2:
    {
        int base = 0;
        if (groups <= 0)
            return;
        int off = 0;
        do
        {
            Group* g   = (Group*)((uint8_t*)gb + off);
            int    cnt = (int)(g->end - g->items);
            if (cnt > 0)
            {
                uint8_t** it = g->items;
                int       i  = 0;
                do
                {
                    float v = (float)(i + base) * 0.5f;
                    *(float*)(*it + 0x6c) = v - (float)floor((double)v);
                    ++i;
                    ++it;
                } while (i < cnt);
            }
            off += 0x38;
            ++base;
        } while (base < groups);
        return;
    }
    case 3:
    {
        if (groups <= 0)
            return;
        int off = 0;
        int gc  = groups;
        do
        {
            Group* g   = (Group*)((uint8_t*)gb + off);
            int    cnt = (int)(g->end - g->items);
            if (cnt > 0)
            {
                uint8_t** it = g->items;
                int       k  = cnt;
                do
                {
                    uint8_t* e = *it;
                    float    x;
                    if (b.ey > 0.0f)
                        x = (*(float*)(e + 0x80) - (b.cy - b.ey * 0.5f)) / lineH;
                    else
                        x = 0.0f;
                    *(float*)(e + 0x6c) = x - (float)floor((double)x);
                    ++it;
                } while (--k);
            }
            off += 0x38;
        } while (--gc);
        return;
    }
    case 4:
    {
        if (groups <= 0)
            return;
        int off = 0;
        int gc  = groups;
        do
        {
            Group*   g   = (Group*)((uint8_t*)gb + off);
            float    top = *(float*)((uint8_t*)g->head + 0x110);
            int      cnt = (int)(g->end - g->items);
            if (cnt > 0)
            {
                uint8_t** it = g->items;
                int       k  = cnt;
                do
                {
                    uint8_t* e = *it;
                    float    x;
                    if (b.ey > 0.0f)
                        x = (top - (b.cy - b.ey * 0.5f)) / lineH;
                    else
                        x = 0.0f;
                    *(float*)(e + 0x6c) = x - (float)floor((double)x);
                    ++it;
                } while (--k);
            }
            off += 0x38;
        } while (--gc);
        return;
    }
    default:
    {
        if (groups <= 0)
            return;
        int off = 0;
        int gc  = groups;
        do
        {
            Group* g   = (Group*)((uint8_t*)gb + off);
            int    cnt = (int)(g->end - g->items);
            if (cnt > 0)
            {
                float  d   = b.ex * 0.1f;
                float  lo  = b.cx - d;
                float  hi  = d + b.cx;
                uint8_t** it = g->items;
                int       k  = cnt;
                do
                {
                    uint8_t* e = *it;
                    float    add = 0.0f;
                    if (lo <= *(float*)(e + 0x7c))
                        add = (*(float*)(e + 0x7c) <= hi) ? 0.25f : 0.5f;
                    float sum = *(float*)(e + 0x6c) + add;
                    *(float*)(e + 0x6c) = sum - (float)floor((double)sum);
                    ++it;
                } while (--k);
            }
            off += 0x38;
        } while (--gc);
    }
    }
}

// @ 0x009d2160
void Layout::SetupFrom(Src* s)
{
    f60 = *(float*)((uint8_t*)s + 0x0c);
    f68 = s->f4c;
    f6c = s->f50;
    f70 = s->f54;
    f74 = s->f58;
    f78 = s->f5c;
    f7c = s->f60;
    f80 = s->f64;
    f84 = 1.0f - *(float*)((uint8_t*)s + 0x68) * 0.01f;
    f88 = s->f3c;
    fd4 = s->f40;
    fd8 = s->f44;
    f98 = s->f48;

    if (s->mode != -1)
    {
        uint32_t n   = (uint32_t)((int)(s->last - s->first) / 0xc);
        uint32_t cap = (uint32_t)(ie - ib);
        const uint32_t& limit = (cap < n) ? cap : n;
        if (limit != 0)
        {
            f64 = 0.0f;
            int groups = (int)(ge - gb);
            if (groups > 0)
            {
                int      off = 0;
                uint32_t idx = 0;
                int      gc  = groups;
                do
                {
                    Group* g   = (Group*)((uint8_t*)gb + off);
                    int    cnt = (int)(g->end - g->items);
                    if (cnt > 0)
                    {
                        uint8_t** it = g->items;
                        int       i  = 0;
                        do
                        {
                            if ((int)limit <= (int)idx)
                                break;
                            uint8_t* e = it[i];
                            *(float*)(e + 0x6c) = *(float*)(s->first + (size_t)idx * 0xc);
                            float v = *(float*)(s->first + (size_t)idx * 0xc + 4);
                            *(float*)(e + 0x78) = v;
                            f64 = v + f64;
                            ++idx;
                            ++i;
                        } while (i < cnt);
                    }
                    off += 0x38;
                } while (--gc);
            }
            f64 = f64 / (float)limit;
        }
        Apply(s);
    }

    if (s->mode == 7)
        AlignLines();

    f10 = s->seq[0];  f14 = s->seq[1];  f18 = s->seq[2];  f1c = s->seq[3];
    f20 = s->seq[4];  f24 = s->seq[5];  f28 = s->seq[6];  f2c = s->seq[7];
    f30 = s->seq[8];  f34 = s->seq[9];  f38 = s->seq[10]; f3c = s->seq[11];
    f40 = s->seq[12]; f44 = s->seq[13];
}

// @ 0x009d25b0
float Layout::MinThickness(Vec3 v)
{
    float best = g_big;
    float dx   = v.x;
    float dy   = v.y;
    float len  = sqrtf(dy * dy + dx * dx);
    if (len != 0.0f)
    {
        float inv = 1.0f / len;
        dy = inv * dy;
        dx = inv * dx;
    }

    int n = (int)(ie - ib);
    if (n > 0)
    {
        Atlas*   a    = f48;
        int32_t* p    = ib;
        int      cnt  = n;
        float    lens = dy * dy + dx * dx;
        do
        {
            uint8_t* e = EntryOf(a, *p);
            float    r;
            if (lens <= g_tiny)
                r = g_eps;
            else
            {
                float ac = *(float*)(e + 0xac);
                float u  = ac * dx;
                float a8 = *(float*)(e + 0xa8);
                float w  = a8 * dy;
                r = (a8 / sqrtf(w * w + u * u)) * ac;
            }
            if (r < best)
                best = r;
            ++p;
        } while (--cnt != 0);
    }
    return (g_eps > best) ? g_eps : best;
}

// @ 0x009d2700
float Layout::AngleScale(float angle)
{
    int n = (int)(ie - ib);

    if ((g_166c688 & 1) == 0)
    {
        g_166c688 |= 1;
        g_166c684 = (n < 7) ? 1.30899692f : 0.52359879f;
    }

    float best = g_166c684;
    if (n > 0)
    {
        float    base = f84;
        float    f98v = ff8;
        Atlas*   a    = f48;
        int32_t* p    = ib;
        int      cnt  = n;
        do
        {
            uint8_t* e     = EntryOf(a, *p);
            float    scale = base;
            if (g_1551256 != 0)
            {
                if ((g_166c688 & 2) == 0)
                {
                    g_166c688 |= 2;
                    g_166c680 = 1.57079637f;
                }
                float t = fabsf(angle) / g_166c680;
                if (t > 1.0f)
                    t = 1.0f;
                scale = base - ((*(float*)(e + 0xc0) * t) * t) * t;
            }
            float h  = *(float*)(e + 0x80);
            float th = fabsf(*(float*)(e + 0x7c)) +
                       ((scale - 1.0f) * fabsf(*(float*)(e + 0x7c) - f98v)) * 2.5f;
            float r = best;
            if (1e-12f < h * h + th * th)
            {
                float norm = sqrtf(h * h + th * th);
                float nx = h, ny = th;
                if (norm != 0.0f)
                {
                    nx = (1.0f / norm) * h;
                    ny = (1.0f / norm) * th;
                }
                float cur;
                if (ny * ny + nx * nx <= 1e-12f)
                    cur = 1e-6f;
                else
                {
                    float ac = *(float*)(e + 0xac);
                    float a8 = *(float*)(e + 0xa8);
                    float u  = ac * nx;
                    float v  = a8 * ny;
                    cur = (a8 / sqrtf(u * u + v * v)) * ac;
                }
                r = (1.75f - *(float*)(e + 0xc0) * 1.5f) * (cur / norm);
            }
            if (r < best)
                best = r;
            ++p;
        } while (--cnt != 0);
    }
    return (1e-6f > best) ? 1e-6f : best;
}

// @ 0x009d29b0
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

// @ 0x009d2b90
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

// @ 0x009d2c80
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

// @ 0x009d2dd0
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

// @ 0x009d2f50
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

// @ 0x009d3020
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

// @ 0x009d30b0
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

// @ 0x009d3170
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

// @ 0x009d3200
void Locomotion::Integrate(Vec3* vel, float speed)
{
    mPrevVelocity.x = mVelocity.x;
    mPrevVelocity.y = mVelocity.y;
    mPrevVelocity.z = mVelocity.z;
    mVelocity.x = vel->x;
    mVelocity.y = vel->y;
    mVelocity.z = vel->z;
    mVelocity.z = 0.0f;
    mSmoothedTurn = mSmoothedTurn * kSmooth + (1.0f - kSmooth) * speed;
    mSmoothedSpeed = mSmoothedSpeed * kSmooth +
        Sqrt(mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y + mVelocity.z * mVelocity.z) * (1.0f - kSmooth);
    mPrevSpeed = mSpeed;
    mSpeed = speed;
    if (mSmoothedSpeed < kTiny)
        mSmoothedSpeed = 0.0f;
    if (Fabs(mSmoothedTurn) < kTiny)
        mSmoothedTurn = 0.0f;
}

// @ 0x009d32d0
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

// @ 0x009d33a0
void Locomotion::ComputeLimbs(LimbParams* p)
{
    uint32_t count = p->mCount;
    uint8_t* base = (uint8_t*)p;
    for (uint32_t i = 0; i < count; ++i) {
        mLimbsBegin[i].Compute(p->mItems[i], base + 0x7c + 0x10 * i, base + 0x7c + 0x60 + 0x10 * i,
                               base + 0x140 + 0x2d0 * i, base + 0x13c);
    }
}

// @ 0x009d3410
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

// @ 0x009d34a0
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

// @ 0x009d3530
float Locomotion::GetMaxSpeed()
{
    float a = Fabs(mSpeed) * kSpeedBlend;
    float b = Sqrt(mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y + mVelocity.z * mVelocity.z);
    return Max(b, a);
}

// @ 0x009d3580
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

// @ 0x009d3610
float Locomotion::GetAmplitude(MoveObj* o, float angle)
{
    if (g_RampScale > kZero) {
        float scale = o->mScale;
        Vec2* v = (Vec2*)&o->info->vx;
        float vx = v->x * scale;
        float vy = v->y * scale;
        static const float sMax = kMaxAngle;   // 0x166c694 (guard bit 1 of 0x166c698)
        float a = Fabs(angle);
        float t = g_RampLow < a ? a : g_RampLow;
        if (sMax < t)
            t = sMax;
        // vx/vy are live across the static guard (frame is materialised, so ecx stays untouched)
        float speed = Sqrt(vy * vy + vx * vx);
        return (((kAmpA - g_RampLowOut) / (sMax - g_RampLow)) * g_RampScale * t) * speed + 1.0f;
    }
    return 1.0f;
}

// @ 0x009d3710
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

// @ 0x009d3790
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

// @ 0x009d3950
float AnimDyn::FUN_009d3950(Obj2* p, float dt, int x)
{
    float r = 0.0f;
    if (f4c * f4c + f50 * f50 + f54 * f54 > DAT_01551258) {
        float a = FUN_009d3790(dt);
        if (1e-06f < a) {
            float b = FUN_009d3840(x);
            if (p->b2d5 != 0)
                r = ((f08 / a) * b) * 1.1f;
            else
                return sqrtf(f4c * f4c + f50 * f50 + f54 * f54) / a * b;
        }
    }
    return r;
}

// @ 0x009d3a20
float AnimDyn::FUN_009d3a20(Obj2* p, float a, int x, float b)
{
    float sScale = (DAT_0166c6a0 & 1) ? DAT_0166c69c
                                      : (DAT_0166c6a0 |= 1, DAT_0166c69c = 1.0f / sqrtf(DAT_01551500));

    // lo = per-axis extent, hi = pose term; the two branches differ only in the lo term
    // (sqrt(f70)*sqrt(|v|^2) vs sqrt(f70)*f08) and the retail keeps both on the x87 stack.
    float sum = (p->b2d5 != 0)
        ? sqrtf(p->f70) * f08 + fabsf(f64 * 0.31830987f)
        : sqrtf(p->f70) * sqrtf(f4c * f4c + f50 * f50 + f54 * f54) + fabsf(f64 * 0.31830987f);

    float q = sum + sScale;
    float d = 1.0f / (q * q);

    float r1 = FUN_009d3950(p, a, x);
    float r2 = FUN_009d3710(p, a, b);
    float m = eastl_max(r1, r2);
    float n = eastl_max(m, d);
    float v = f80 * n;
    return eastl_max(v, 0.1f);
}

// @ 0x009d3b50
void AnimDyn::FUN_009d3b50(float t)
{
    f7c = f78;
    f78 = t;

    int    count = (int)((char*)p14 - (char*)p10) / 0x104;
    Rec*   base  = (Rec*)p10;
    for (int i = 0; i < count; ++i) {
        Rec* rec = base + i;
        float f  = rec->fD0 * f78;
        rec->fA4 = f;
        if (f < 0.001f) {
            rec->fA8 = 0.0f;
            rec->fAC = 0.0f;
            rec->fB0 = 0.0f;
            rec->fB4 = 0.0f;
        }
        else {
            Bone_s009d_3950* b   = (Bone_s009d_3950*)rec->p48;
            float inv = 1.0f / f;
            rec->fA8  = (b->f4c * inv) * b->f80;
            rec->fAC  = (b->f50 * inv) * b->f80;
            rec->fB0  = (b->f54 * inv) * b->f80;
            rec->fB4  = (b->f64 / rec->fA4) * b->f80;
        }
    }
}

// @ 0x009d3f70
void GaitState::FUN_009d3f70(Obj2* p)
{
    float v = *(float*)((char*)p->p00 + 0x3ec);

    prev  = state;
    int n = (int)((char*)p3c - (char*)p38) / 0x30;
    float h = (1.0f - DAT_01551504) * 0.2f;
    if (n != 0) {
        state = 3;
        return;
    }

    // DAT_01551504 is the gait time scale; the retail reloads it per use instead of
    // keeping it in a named local (which would take a stack home and a frame slot).
    bool b3 = (f08 * p->f70 <= DAT_01551504 * v) && (fabsf(f0c) <= DAT_01551504 * 0.2f);
    bool b5 = ((1.0f - DAT_01551504) * v < f08 * p->f70) || (h < fabsf(f0c));
    bool b4 = (p->i1684 == 0) && (fabsf(f0c) <= h);

    switch (state) {
    case 0:
        if (!b3 && !b4) {
            state = 1;
            return;
        }
        break;
    case 1:
        if (!b3) {
            if (!b5) return;
            if (b4) return;
            state = 3;
            return;
        }
        goto setState2;
    case 2:
        if (b3 || b4) {
            state = 0;
            return;
        }
        if (b5) {
            state = 1;
            return;
        }
        break;
    case 3:
        if (b5 && !b4)
            return;
    setState2:
        state = 2;
    }
}

// @ 0x009d41b0
R30* copy30(R30* first, R30* last, R30* result)
{
    for (; first != last; ++first, ++result)
        *result = *first;
    return result;
}

// @ 0x009d5f10
void __thiscall Ent::Fn5f10(Ent* p, float q3, float q4, float q5, float q6)
{
    if (!(0.0f < p->fa4)) return;

    float ph = p->f9c;
    float step0 = p->fac;
    float fVar1 = p->fb0;
    float left = p->fa0;

    fd0 = f78 * (p->fa8 * g_13ec488);
    fd8 = f78 * (fVar1 * g_13ec488);
    fd4 = f78 * (step0 * g_13ec488);
    fe8 = (p->fb4 * f78) * g_13ec488;
    o5d = 0;

    if (left > g_1551520) left = fmodf(left, g_1551520);

    while (left > g_1485378)
    {
        float v1 = (f6c + ph) - (float)floor((double)(f6c + ph));
        float lo = f100;
        float hi = f104;
        u8 fl = (v1 < lo || hi <= v1);
        o5c = fl;

        float w;
        if (v1 < lo) w = (g_1485720 - hi) + v1;
        else
        {
            float t = lo;
            if (hi <= v1) t = hi;
            w = v1 - t;
        }

        float span;
        if (fl != 0) span = (g_1485720 - hi) + lo;
        else span = hi - lo;
        w = span - w;

        float step = (left <= w) ? left : w;
        step = step + g_13f89bc;
        float frac = step / p->fa4;
        float scl = (g_14479b0 <= frac) ? frac : g_1485378;

        float ph2 = (f6c + ph) + step;
        float v2 = ph2 - (float)floor((double)ph2);
        f98 = v2;

        if (fl == 0)
        {
            float r = (ph2 - lo) / span;
            if (r > g_1485378) { if (r > g_1485720) r = g_1485720; }
            else r = g_1485378;
            Fn49b0(p, scl, r);
            Fn5600(p, r);
        }
        else
        {
            float t = (v2 <= hi) ? (g_1485720 - hi) + v2 : v2 - hi;
            float r = t / span;
            float r2 = g_1485378;
            if (r > g_1485378) { r2 = r; if (r > g_1485720) r2 = g_1485720; }
            Fn52f0(p, scl, r2, q3, q4, q5, q6);
            Fn5b50(p, r2);
        }

        if (left > step || w <= step)
        {
            if (o5c == 0) Fn46d0(p);
            else Fn42b0(p);
            o5d = 1;
        }

        ph = step + ph;
        left = left - step;
    }
}

// @ 0x009d62a0
float __thiscall Ent::Fn62a0(float d)
{
    Obj48* o = o48;
    float local = fabsf(o->f0c) * g_15514e4;
    const float& mv = (local > o->f08) ? local : o->f08;

    char* base = (char*)o->o24;
    char* e1 = *(char**)(base + 0xc8);
    char* tbl = *(char**)(e1 + 0x384);
    char* x0 = tbl + *(int*)(base + o_bc[0] * 0x108 + 0x58) * 0x468;
    char* x1 = tbl + *(int*)(base + o_bc[1] * 0x108 + 0x58) * 0x468;

    float dx = *(float*)(x0 + 0x10c) - *(float*)(x1 + 0x10c);
    float dy = *(float*)(x0 + 0x110) - *(float*)(x1 + 0x110);
    float dz = *(float*)(x0 + 0x114) - *(float*)(x1 + 0x114);

    float dist = sqrtf(dx * dx + dy * dy + dz * dz);
    float R = dist + (mv / fa4) * o->f80 * g_1471064;
    float diff = R * R - d * d;
    float zero = g_1485378;
    const float& q = (diff > g_1485378) ? diff : zero;
    return sqrtf(q) * g_1551524;
}

// @ 0x009d63e0
void Anim::m63e0(void* param2)
{
    if (!(fa4 >= g_14479b0))
        return;
    if ((unsigned)(e8 - b4) < 2)
        return;

    u32 i0 = pbc[0];
    u32 i1 = pbc[1];
    char* arr = *(char**)((char*)ctx48 + 0x24);
    char* a0 = arr + i0 * 0x108;
    char* a1 = arr + i1 * 0x108;
    char* obj = *(char**)(a0 + 0xc8);
    unsigned mid = (unsigned)((char*)e8) + (unsigned)((char*)b4);

    void* out34 = 0;
    float f0 = 0.0f, f1 = 0.0f, f2 = 0.0f, one = 0.0f;
    FUN_009d2f50(&f0, &obj);
    float dist = FUN_009d62a0(*(float*)&f0);
    mid >>= 1;

    if (obj[0x260] != 0) {
        one = 1.0f;
        if (b4 < (char*)i0c && (char*)i0c < e8) {
            FUN_009cfb00(&f1, &f2, a0, a1, dist, &f0, &out34);
            FUN_009cfd40(&f1, &f2, param2);
        }
        if (mid != (unsigned)i0c) {
            FUN_009cfb00(&f1, &f2, a0, a1, dist, &f0, &out34);
            FUN_009cfd40(&f1, &f2, param2);
        }
    }
    if (g_15509f0 != 0 && obj[0x168c] != 0) {
        char* t = (char*)i0c;
        if (b4 < t && t < e8)
            FUN_009c0860(p38 + (unsigned)t * 0x30);
        if (mid != (unsigned)i0c) {
            FUN_009c0860(p38 + mid * 0x30);
            return;
        }
    }
}

// @ 0x009d65f0
float Anim::m65f0(float dt, void* e)
{
    if (!(dt > g_14479b0))
        return *(float*)((char*)e + 0xdc);
    float p = (float)pow(0.1, (double)(dt / f70));
    float a = (float)fabs((double)f64) * g_15514e0;
    float r = (float)sqrt((double)(f4c * f4c + f50 * f50 + f54 * f54));
    float m = (a > r) ? a : r;
    f6c = (1.0f - p) * m + f6c * p;
    float x = f6c * g_1447a38;
    x = x * x;
    if (x > -g_166c7d4)
        return g_1485720;
    return 1.0f - (float)exp((double)-x);
}

// @ 0x009d6a10
Vec38* Vec38::DoAllocate(unsigned n, void* a)
{
    char* data;
    if (n != 0)
        data = (char*)GAIT_ALLOC(n * 0x38);
    else
        data = 0;
    b = data;
    e = data;
    c = data + n * 0x38;
    return this;
}

// @ 0x009d6a70
void __cdecl FUN_009d6a70(char* first, char* last)
{
    for (; first != last; first += 0x38) {
        void* q = *(void**)(first + 4);
        if (q != 0 && *(int*)((char*)q - 4) != 0)
            EastlFree(q);
    }
}

// @ 0x009d6bb0
SA_s009d_63e0** __cdecl FUN_009d6bb0(SA_s009d_63e0** f1, SA_s009d_63e0** l1, SA_s009d_63e0** f2, SA_s009d_63e0** l2, SA_s009d_63e0** out)
{
    while (f1 != l1 && f2 != l2) {
        SA_s009d_63e0* b = *f2;
        SA_s009d_63e0* a = *f1;
        if (b->f7c > a->f7c) {
            *out = b;
            ++f2;
        } else {
            *out = a;
            ++f1;
        }
        ++out;
    }
    out = (SA_s009d_63e0**)((char*)FUN_011e0744(out, f1, (unsigned)((char*)l1 - (char*)f1)) + (((int)((char*)l1 - (char*)f1)) >> 2) * 4);
    out = (SA_s009d_63e0**)((char*)FUN_011e0744(out, f2, (unsigned)((char*)l2 - (char*)f2)) + (((int)((char*)l2 - (char*)f2)) >> 2) * 4);
    return out;
}

// @ 0x009d6c20
SA_s009d_63e0** __cdecl FUN_009d6c20(SA_s009d_63e0** f1, SA_s009d_63e0** l1, SA_s009d_63e0** f2, SA_s009d_63e0** l2, SA_s009d_63e0** out)
{
    while (f1 != l1 && f2 != l2) {
        SA_s009d_63e0* b = *f2;
        SA_s009d_63e0* a = *f1;
        if (b->f80 > a->f80) {
            *out = b;
            ++f2;
        } else {
            *out = a;
            ++f1;
        }
        ++out;
    }
    out = (SA_s009d_63e0**)FUN_011e0744(out, f1, (unsigned)((uintptr_t)l1 - (uintptr_t)f1)) + (l1 - f1);
    out = (SA_s009d_63e0**)FUN_011e0744(out, f2, (unsigned)((uintptr_t)l2 - (uintptr_t)f2)) + (l2 - f2);
    return out;
}

// @ 0x009d6ca0
SA_s009d_63e0** __cdecl FUN_009d6ca0(SA_s009d_63e0** f1, SA_s009d_63e0** l1, SA_s009d_63e0** f2, SA_s009d_63e0** l2, SA_s009d_63e0** out)
{
    for (;;) {
        if (f1 == l1)
            break;
        if (f2 == l2)
            break;
        SA_s009d_63e0* a = *f1;
        SA_s009d_63e0* b = *f2;
        bool takeB;
        if (b->f80 == a->f80)
            takeB = b->f7c > a->f7c;
        else
            takeB = b->f80 > a->f80;
        if (takeB) {
            *out = b;
            ++f2;
        } else {
            *out = a;
            ++f1;
        }
        ++out;
    }
    int n1 = (int)((char*)l1 - (char*)f1);
    out = (SA_s009d_63e0**)((char*)FUN_011e0744(out, f1, (unsigned)n1) + (n1 >> 2) * 4);
    int n2 = (int)((char*)l2 - (char*)f2);
    out = (SA_s009d_63e0**)((char*)FUN_011e0744(out, f2, (unsigned)n2) + (n2 >> 2) * 4);
    return out;
}

// @ 0x009d6ef0
void VecU32::DoInsertValue(u32* pos, const u32& v)
{
    if (e != c) {
        const u32* pv = &v;
        if (pv >= pos && pv < e)
            ++pv;
        if (e)
            *e = *(e - 1);
        u32* last = e - 1;
        memmove(e - (last - pos), pos, (char*)last - (char*)pos);
        *pos = *pv;
        ++e;
    } else {
        u32 cnt = (u32)(e - b);
        u32 n = cnt > 0 ? 2 * cnt : 1;
        u32* nb = n ? (u32*)GAIT_ALLOC(n * 4) : 0;
        int n1 = (int)((char*)pos - (char*)b);
        u32* np = (u32*)FUN_011e0744(nb, b, (unsigned)n1);
        np += n1 >> 2;
        if (np)
            *np = v;
        ++np;
        int n2 = (int)((char*)e - (char*)pos);
        np = (u32*)FUN_011e0744(np, pos, (unsigned)n2);
        np += n2 >> 2;
        if (b && ((int*)b)[-1])
            EastlFree(b);
        b = nb;
        e = np;
        c = nb + n;
    }
}

// 0x009d75b0: not byte-exact; the byte-exact version is the lifted one in match/slices/s009d75b0/s009d75b0_lifted.cpp
GaitElemInit* GaitElemInit::Init()
{
    char* p = (char*)this;
    at<float>(p, 0xb0) = 0.0f;
    at<float>(p, 0xac) = 0.0f;
    at<float>(p, 0xa8) = 0.0f;
    at<float>(p, 0xe8) = 0.0f;
    at<float>(p, 0xe4) = 0.0f;
    at<float>(p, 0xe0) = 0.0f;
    at<float>(p, 0xf4) = 0.0f;
    at<float>(p, 0xf0) = 0.0f;
    at<float>(p, 0xec) = 0.0f;
    at<float>(p, 0x100) = 0.0f;
    at<float>(p, 0xfc) = 0.0f;
    at<float>(p, 0xf8) = 0.0f;
    at<int>(p, 0x4c) = 0;
    at<int>(p, 0x50) = 0;
    at<int>(p, 0x54) = 0;
    at<int>(p, 0xbc) = 0;
    at<int>(p, 0xc0) = 0;
    at<int>(p, 0xc4) = 0;
    at<float>(p, 0xd0) = 1.0f;
    at<float>(p, 0x9c) = 0.0f;
    at<int>(p, 0) = -1;
    at<float>(p, 0x88) = g_01550b24;
    at<float>(p, 0x90) = g_0166c024;
    at<float>(p, 0xd4) = g_0166c024;
    at<float>(p, 0x94) = g_0166c028;
    at<float>(p, 0xd8) = g_0166c028;
    at<float>(p, 0x98) = g_0166c02c;
    at<float>(p, 0x60) = 1.0f;
    at<float>(p, 0x64) = g_01550b28;
    at<float>(p, 0x68) = g_01550b2c;
    at<float>(p, 0x6c) = g_01550b30;
    at<float>(p, 0x70) = g_01550b34;
    at<float>(p, 0x74) = g_01550b38;
    at<float>(p, 0x78) = g_01550b3c;
    at<float>(p, 0x7c) = 0.0f;
    at<float>(p, 0x80) = g_01471064;
    at<float>(p, 0x84) = 1.0f;
    at<float>(p, 0xa4) = 1.0f;
    at<float>(p, 0xa8) = 0.0f;
    at<float>(p, 0xac) = 0.0f;
    at<float>(p, 0xb0) = 0.0f;
    at<float>(p, 0xb4) = 0.0f;
    at<float>(p, 0x8c) = 1.0f;
    at<float>(p, 0xa0) = 0.0f;
    at<float>(p, 0xdc) = 0.0f;
    at<float>(p, 0x10) = g_01550b44;
    at<float>(p, 0x14) = g_0166c038;
    at<float>(p, 0x18) = g_01550b48;
    at<float>(p, 0x1c) = g_01550b4c;
    at<float>(p, 0x20) = g_0166c03c;
    at<float>(p, 0x24) = g_0166c040;
    at<float>(p, 0x28) = g_01550b50;
    at<float>(p, 0x2c) = g_01550b54;
    at<float>(p, 0x30) = g_01550b58;
    at<float>(p, 0x34) = g_01550b5c;
    at<float>(p, 0x38) = g_0166c044;
    at<float>(p, 0x3c) = g_01550b60;
    at<float>(p, 0x40) = g_01550b64;
    at<float>(p, 0x44) = g_01550b68;
    at<float>(p, 0xf8) = 0.0f;
    at<float>(p, 0xfc) = 0.0f;
    at<float>(p, 0x100) = 0.0f;
    at<int>(p, 0xc) = -1;
    at<int>(p, 4) = -1;
    at<int>(p, 8) = -1;
    at<int>(p, 0xb8) = -1;
    return this;
}

// @ 0x009d7840
bool LessIdx::operator()(S a, S b)
{
    float fa = *(float*)(a.owner->arr + *a.idx.b * 0x108 + 0xac);
    float fb = *(float*)(b.owner->arr + *b.idx.b * 0x108 + 0xac);
    return fa > fb;
}

// @ 0x009d7920
bool LessWord::operator()(S a, S b)
{
    return a.hw < b.hw;
}

// @ 0x009d7bb0
PtrVec& PtrVec::Assign(const PtrVec& o)
{
    if (&o != this) {
        u32* oe = o.e;
        u32* ob = o.b;
        u32* tb = b;
        u32 n = ((char*)oe - (char*)ob) >> 2;
        u32 capn = ((char*)c - (char*)tb) >> 2;
        if (n > capn) {
            u32* p = DoAllocate(n, ob, oe);
            FreeArr(b);
            b = p;
            c = p + n;
            e = p + n;
            return *this;
        }
        u32 cur = ((char*)e - (char*)tb) >> 2;
        if (cur < n) {
            memcpy(tb, ob, cur * 4);
            u32 cur2 = ((char*)e - (char*)b) >> 2;
            u32* src = (u32*)((char*)ob + cur2 * 4);
            memcpy(e, src, (char*)oe - (char*)src);
            e = b + n;
        } else {
            memcpy(tb, ob, (char*)oe - (char*)ob);
            e = b + n;
        }
    }
    return *this;
}

// @ 0x009d7c80
S* __cdecl DestroyRecords(S* first, S* last, S* dst)
{
    if (first != last) {
        do {
            FreeArr(first->idx.b);
            Item* end = first->items.e;
            Item* it = first->items.b;
            for (; it < end; ++it)
                FreeArr(it->v.b);
            FreeArr(first->items.b);
            ++first;
            ++dst;
        } while (first != last);
        return dst;
    }
    return dst;
}

// @ 0x009d7dd0
Item::Item(const Item& o)
{    key = o.key;
    PtrVec& dv = v;
    dv.DoAllocateN(o.v.e - o.v.b, (void*)&o.v.alloc);
    u32* ob = o.v.b;
    int nbytes = (char*)o.v.e - (char*)ob;
    u32* dst = *(u32* volatile*)&dv.b;
    u32* r = (u32*)memcpy(dst, ob, nbytes);
    dv.e = r + (nbytes >> 2);
    f18 = o.f18;
    f1c = o.f1c;
    f20 = o.f20;
    uint8_t b = *(const volatile uint8_t*)&o.b24;
    b24 = b;
    f28 = o.f28;
    f2c = o.f2c;
    f30 = o.f30;
    f34 = o.f34;}

// @ 0x009d7e50
Item& Item::operator=(const Item& o)
{
    key = o.key;
    v.Assign(o.v);
    f18 = o.f18;
    f1c = o.f1c;
    f20 = o.f20;
    b24 = o.b24;
    f28 = o.f28;
    f2c = o.f2c;
    f30 = o.f30;
    f34 = o.f34;
    return *this;
}

// @ 0x009d7f20
Item* __cdecl CopyItems(Item* first, Item* last, Item* dst)
{
    if (first != last) {
        do {
            *dst = *first;
            ++first;
            ++dst;
        } while (first != last);
        return dst;
    }
    return dst;
}

// @ 0x009d7fa0
Item* __cdecl CopyItemsBackward(Item* first, Item* last, Item* dst)
{
    if (last != first) {
        do {
            --last;
            --dst;
            *dst = *last;
        } while (last != first);
        return dst;
    }
    return dst;
}

// @ 0x009d8020
void GaitSorter::Sort3(PtrVec* vec, float a, float b)
{
    if (a < 1e-06f || 100.0f < b / a) {
        SortRangeA(vec->b, vec->e, MakePred(EmptyPred()));
    } else if (b < 1e-06f || 100.0f < a / b) {
        u32* p = vec->b;
        u32 t = p[0];
        if (PX(p[1]) > PX(t)) {
            p[0] = p[1];
            p[1] = t;
        }
        p = vec->b;
        t = p[0];
        if (PX(p[2]) > PX(t)) {
            p[0] = p[2];
            p[2] = t;
        }
        p = vec->b;
        t = p[1];
        if (PX(t) > PX(p[2])) {
            p[1] = p[2];
            p[2] = t;
        }
    } else {
        u32* p = vec->b;
        float mean = ((PZ(p[0]) + PZ(p[1])) + PZ(p[2])) * 0.33333334f;
        int below = 0;
        if (PZ(p[0]) < mean)
            ++below;
        if (PZ(p[1]) < mean)
            ++below;
        if (PZ(p[2]) < mean)
            ++below;
        if (below > 1) {
            int i = 0;
            u32* q = p;
            do {
                if (PZ(*q) > mean) {
                    u32 t = p[2];
                    p[2] = p[i];
                    p[i] = t;
                    break;
                }
                ++i;
                ++q;
            } while (i < 2);
            p = vec->b;
            u32 t = p[0];
            if (PX(t) > PX(p[1])) {
                p[0] = p[1];
                p[1] = t;
            }
        } else {
            int i = 0;
            u32* q = p;
            do {
                if (mean > PZ(*q)) {
                    u32 t = p[2];
                    p[2] = p[i];
                    p[i] = t;
                    break;
                }
                ++i;
                ++q;
            } while (i < 2);
            p = vec->b;
            u32 t = p[0];
            if (PX(t) > PX(p[1])) {
                p[0] = p[1];
                p[1] = t;
            }
        }
    }
}

// @ 0x009d81f0
void GaitSorter::Sort4(PtrVec* vec, float a, float b, float c, float d, float e, float f)
{
    if (a == 0.0f) {
        SortA(vec->b, vec->e, EmptyPred());
        return;
    }
    if (b == 0.0f) {
        SortB(vec->b, vec->e, EmptyPred());
        return;
    }
    u32* p = vec->b;
    if (Sq2(PX(p[0]) - d, PZ(p[0]) - f) > Sq2(PX(p[1]) - d, PZ(p[1]) - f)) {
        u32 t = p[0];
        p[0] = p[1];
        p[1] = t;
    }
    p = vec->b;
    if (Sq2(PX(p[0]) - d, PZ(p[0]) - f) > Sq2(PX(p[2]) - d, PZ(p[2]) - f)) {
        u32 t = p[0];
        p[0] = p[2];
        p[2] = t;
    }
    p = vec->b;
    if (Sq2(PX(p[0]) - d, PZ(p[0]) - f) > Sq2(PX(p[3]) - d, PZ(p[3]) - f)) {
        u32 t = p[0];
        p[0] = p[3];
        p[3] = t;
    }
    p = vec->b;
    if (Sq2(PX(p[1]) - c, PZ(p[1]) - f) > Sq2(PX(p[2]) - c, PZ(p[2]) - f)) {
        u32 t = p[1];
        p[1] = p[2];
        p[2] = t;
    }
    p = vec->b;
    if (Sq2(PX(p[1]) - c, PZ(p[1]) - f) > Sq2(PX(p[3]) - c, PZ(p[3]) - f)) {
        u32 t = p[1];
        p[1] = p[3];
        p[3] = t;
    }
    p = vec->b;
    if (Sq2(PX(p[2]) - d, PZ(p[2]) - e) > Sq2(PX(p[3]) - d, PZ(p[3]) - e)) {
        u32 t = p[2];
        p[2] = p[3];
        p[3] = t;
    }
}

// @ 0x009d84f0
void __fastcall GaitSorter_SortAll(GaitSorter* self)
{
    ItemVec* items = (ItemVec*)((char*)self + 0x4c);
    int count = items->e - items->b;
    if (count > 0) {
        int off = 0;
        do {
            Item* it = (Item*)((char*)items->b + off);
            int n = it->v.e - it->v.b;
            float fa, fb, f0, f1, f2, f3;
            ((ItemOps*)it)->Query(&fa, &fb, &f0, &f1, &f2, &f3);
            ((ItemOps*)it)->Update();
            switch (n) {
            case 0:
            case 1:
                break;
            case 2:
                if (fa > fb)
                    SortRangeB(it->v.b, it->v.e, MakePred(EmptyPred()));
                else
                    SortRangeA(it->v.b, it->v.e, MakePred(EmptyPred()));
                break;
            case 3:
                self->Sort3(&it->v, fa, fb);
                break;
            case 4:
                self->Sort4(&it->v, fa, fb, f0, f1, f2, f3);
                break;
            default:
                SortRangeC(it->v.b, it->v.e, MakePred(EmptyPred()));
                break;
            }
            off += 0x38;
        } while (--count);
    }
}

// @ 0x009d8660
Item* __stdcall AllocCopyItems(u32 n, Item* first, Item* last)
{
    Item* p;
    if (n)
        p = (Item*)EastlAlloc(n * 0x38, "Anim/gait/untagged", 0, 0,
                              "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                              0xd1);
    else
        p = 0;
    UninitCopyOut((Item**)&n, first, last, p, *(volatile u32*)&n);
    return p;
}

// @ 0x009d86c0
ItemVec* ItemVec::CopyInit(ItemVec* src)
{
    DoAllocateN(src->e - src->b, &src->alloc);
    ItemVec* slot = src;
    UninitCopyOut((Item**)&slot, src->b, src->e, b, (u32)slot);
    e = (Item*)slot;
    return this;
}

// @ 0x009d8720
Gait::Gait(const Gait& o)
: a00(o.a00), a04(o.a04), a08(o.a08), a0c(o.a0c),
    f10(o.f10), f14(o.f14), f18(o.f18), f1c(o.f1c), f20(o.f20), f24(o.f24),
    f28(o.f28), f2c(o.f2c), f30(o.f30), f34(o.f34), f38(o.f38), f3c(o.f3c),
    f40(o.f40), f44(o.f44),
    a48(o.a48), sub(o.sub),
    f60(o.f60), f64(o.f64), f68(o.f68), f6c(o.f6c), f70(o.f70), f74(o.f74),
    f78(o.f78), f7c(o.f7c), f80(o.f80), f84(o.f84), f88(o.f88), f8c(o.f8c),
    f90(o.f90), f94(o.f94), f98(o.f98), f9c(o.f9c), fa0(o.fa0), fa4(o.fa4),
    fa8(o.fa8), fac(o.fac), fb0(o.fb0), fb4(o.fb4),
    ab8(o.ab8), v(o.v),
    fd0(o.fd0), fd4(o.fd4), fd8(o.fd8), fdc(o.fdc), fe0(o.fe0), fe4(o.fe4),
    fe8(o.fe8), fec(o.fec), ff0(o.ff0), ff4(o.ff4), ff8(o.ff8), ffc(o.ffc),
    f100(o.f100)
{
}

// @ 0x009d8980
void merge_by_subcount(Step* f1, Step* l1, Step* f2, Step* l2, Step* out, GaitCmp1 cmp)
{
    while (f1 != l1 && f2 != l2) {
        u32 c1 = (u32)(f1->sub.end - f1->sub.begin);
        u32 c2 = (u32)(f2->sub.end - f2->sub.begin);
        if (c2 <= c1) {
            *out = *f1;
            ++f1;
        } else {
            *out = *f2;
            ++f2;
        }
        ++out;
    }
    Step* e = uninit_copy_step(f1, l1, out);
    uninit_copy_step(f2, l2, e);
}

// @ 0x009d8ab0
void merge_by_key(Step* f1, Step* l1, Step* f2, Step* l2, Step* out, GaitCmp2 cmp)
{
    while (f1 != l1 && f2 != l2) {
        float k2 = *(float*)((char*)f2->obj + 0x110);
        float k1 = *(float*)((char*)f1->obj + 0x110);
        if (k2 <= k1) {
            *out = *f1;
            ++f1;
        } else {
            *out = *f2;
            ++f2;
        }
        ++out;
    }
    Step* e = uninit_copy_step(f1, l1, out);
    uninit_copy_step(f2, l2, e);
}

// @ 0x009d8be0
Gait* select_median_subcount(Gait* a, Gait* b, Gait* c, GaitCmp1 cmp)
{
    if (cmp(*a, *b)) {
        if (cmp(*b, *c))
            return b;
        if (cmp(*a, *c))
            return c;
        return a;
    } else {
        if (cmp(*a, *c))
            return a;
        if (cmp(*b, *c))
            return c;
        return b;
    }
}

// @ 0x009d8ce0
Gait* select_median_key(Gait* a, Gait* b, Gait* c, GaitCmp2 cmp)
{
    if (cmp(*a, *b)) {
        if (cmp(*b, *c))
            return b;
        if (cmp(*a, *c))
            return c;
        return a;
    } else {
        if (cmp(*a, *c))
            return a;
        if (cmp(*b, *c))
            return c;
        return b;
    }
}

// @ 0x009d8e20
Step* VectorStep::erase(Step* first, Step* last)
{
    Step* newend = uninit_copy_step(last, end, first);
    destroy(newend, end);
    end -= last - first;
    return first;
}

// @ 0x009d8e80
void VectorStep::insert(Step* pos, const Step& value)
{
    if (end != cap) {
        const Step* v = &value;
        if (v >= pos && v < end)
            ++v;
        if (end)
            new (end) Step(*(end - 1));
        copy_backward_step(pos, end - 1, end);
        *pos = *v;
        ++end;
        return;
    }

    u32 n = (u32)(end - begin);
    u32 ncap = (n == 0) ? 1 : n * 2;
    Step* buf = ncap ? (Step*)EAAllocate(ncap * 0x38, "Anim/gait/untagged", 0, 0, 0x13ebb38, 0xd1) : 0;

    Step* mid = uninit_move_step(begin, pos, buf);
    destroy_move_step(begin, pos, buf);
    if (mid)
        new (mid) Step(value);
    Step* newend = uninit_move_step(pos, end, mid + 1);
    destroy_move_step(pos, end, mid + 1);

    if (begin != 0 && ((int*)begin)[-1] != 0)
        ::operator delete(begin);

    end   = newend;
    begin = buf;
    cap   = buf + ncap;
}

// @ 0x009d8fd0
VectorStep& VectorStep::operator=(const VectorStep& o)
{
    if (this != &o) {
        u32 n = (u32)(o.end - o.begin);
        if (n > (u32)(cap - begin)) {
            Step* p = alloc_n_copy(n, o.begin, o.end);
            destroy(begin, end);
            if (begin != 0 && ((int*)begin)[-1] != 0)
                ::operator delete(begin);
            begin = p;
            cap   = p + n;
        } else if (n > (u32)(end - begin)) {
            Step* dst = end;
            uninit_copy_step(o.begin, o.begin + (end - begin), begin);
            void* slot;
            uninit_copy_slot(&slot, o.begin + (end - begin), o.end, dst, &o);
        } else {
            Step* newend = uninit_copy_step(o.begin, o.end, begin);
            destroy_step(newend, end);
        }
        end = begin + n;
    }
    return *this;
}

// @ 0x009d9120
void merge_sort_subcount(Step* first, Step* last, Step* buffer, GaitCmp1 cmp)
{
    ptrdiff_t n = last - first;
    if (n > 1) {
        ptrdiff_t h = n / 2;
        Step* mid = first + h;

        if (h > 1) {
            ptrdiff_t q = h / 2;
            merge_sort_subcount(first, first + q, buffer, cmp);
            merge_sort_subcount(first + q, mid, buffer + q, cmp);
            merge_by_subcount(first, first + q, first + q, mid, buffer, cmp);
        } else {
            *buffer = *first;
        }

        if (n - h > 1) {
            ptrdiff_t q = (h + n) / 2;
            merge_sort_subcount(mid, first + q, buffer + h, cmp);
            merge_sort_subcount(first + q, last, buffer + q, cmp);
            merge_by_subcount(mid, first + q, first + q, last, buffer + h, cmp);
        } else {
            *(buffer + h) = *mid;
        }

        merge_by_subcount(buffer, buffer + h, buffer + h, buffer + n, first, cmp);
    }
}

// @ 0x009d92a0
void merge_sort_key(Step* first, Step* last, Step* buffer, GaitCmp2 cmp)
{
    ptrdiff_t n = last - first;
    if (n > 1) {
        ptrdiff_t h = n / 2;
        Step* mid = first + h;

        if (h > 1) {
            ptrdiff_t q = h / 2;
            merge_sort_key(first, first + q, buffer, cmp);
            merge_sort_key(first + q, mid, buffer + q, cmp);
            merge_by_key(first, first + q, first + q, mid, buffer, cmp);
        } else {
            *buffer = *first;
        }

        if (n - h > 1) {
            ptrdiff_t q = (h + n) / 2;
            merge_sort_key(mid, first + q, buffer + h, cmp);
            merge_sort_key(first + q, last, buffer + q, cmp);
            merge_by_key(mid, first + q, first + q, last, buffer + h, cmp);
        } else {
            *(buffer + h) = *mid;
        }

        merge_by_key(buffer, buffer + h, buffer + h, buffer + n, first, cmp);
    }
}

// @ 0x009d9420
void stable_sort_subcount(Step* first, Step* last, GaitCmp1 cmp)
{
    ptrdiff_t n = last - first;
    if (n > 1) {
        Step* buf = (Step*)EAAllocate((u32)(n * 0x38), "Anim/gait/untagged", 0, 0, 0x13ebb38, 0xd1);
        Step  empty;
        Step* e = buf + n;
        for (Step* p = buf; p != e; ++p)
            new (p) Step(empty);
        merge_sort_subcount(first, last, buf, cmp);
        copy_step(buf, e, last);
        ::operator delete(buf);
    }
}

// @ 0x009d9520
void stable_sort_key(Step* first, Step* last, GaitCmp2 cmp)
{
    ptrdiff_t n = last - first;
    if (n > 1) {
        Step* buf = (Step*)EAAllocate((u32)(n * 0x38), "Anim/gait/untagged", 0, 0, 0x13ebb38, 0xd1);
        Step  empty;
        Step* e = buf + n;
        for (Step* p = buf; p != e; ++p)
            new (p) Step(empty);
        merge_sort_key(first, last, buf, cmp);
        copy_step(buf, e, last);
        ::operator delete(buf);
    }
}

// @ 0x009d9620
S_s009d_9620& S_s009d_9620::operator=(const S_s009d_9620& o)
{
    w0[0] = o.w0[0];
    w0[1] = o.w0[1];
    w0[2] = o.w0[2];
    w0[3] = o.w0[3];
    wf[0] = o.wf[0];
    wf[1] = o.wf[1];
    wf[2] = o.wf[2];
    wf[3] = o.wf[3];
    wf[4] = o.wf[4];
    wf[5] = o.wf[5];
    wf[6] = o.wf[6];
    wf[7] = o.wf[7];
    wf[8] = o.wf[8];
    wf[9] = o.wf[9];
    wf[10] = o.wf[10];
    wf[11] = o.wf[11];
    wf[12] = o.wf[12];
    wf[13] = o.wf[13];
    owner = o.owner;
    items = o.items;
    w1[0] = o.w1[0];
    w1[1] = o.w1[1];
    w1[2] = o.w1[2];
    w1[3] = o.w1[3];
    w1[4] = o.w1[4];
    w1[5] = o.w1[5];
    w1[6] = o.w1[6];
    w1[7] = o.w1[7];
    w1[8] = o.w1[8];
    w1[9] = o.w1[9];
    w1[10] = o.w1[10];
    w1[11] = o.w1[11];
    w1[12] = o.w1[12];
    w1[13] = o.w1[13];
    w1[14] = o.w1[14];
    w1[15] = o.w1[15];
    w1[16] = o.w1[16];
    w1[17] = o.w1[17];
    w1[18] = o.w1[18];
    w1[19] = o.w1[19];
    w1[20] = o.w1[20];
    w1[21] = o.w1[21];
    hw = o.hw;
    idx = o.idx;
    w2[0] = o.w2[0];
    w2[1] = o.w2[1];
    w2[2] = o.w2[2];
    w2[3] = o.w2[3];
    w2[4] = o.w2[4];
    w2[5] = o.w2[5];
    w2[6] = o.w2[6];
    w2[7] = o.w2[7];
    w2[8] = o.w2[8];
    w2[9] = o.w2[9];
    w2[10] = o.w2[10];
    w2[11] = o.w2[11];
    w2[12] = o.w2[12];
    return *this;
}

// @ 0x009d9840
void __cdecl InsertionSortIdx(S_s009d_9620* first, S_s009d_9620* last)
{
    LessIdx_s009d_9620 predI;
    if (first != last) {
        for (S_s009d_9620* it = first + 1; it != last; ++it) {
            S_s009d_9620 val(*it);
            S_s009d_9620* hole = it;
            while (hole != first) {
                S_s009d_9620* prev = hole - 1;
                if (!predI(val, *prev))
                    break;
                *hole = *prev;
                hole = prev;
            }
            *hole = val;
        }
    }
}

// @ 0x009d9970
void __cdecl UnguardedInsertionSortIdx(S_s009d_9620* first, S_s009d_9620* last)
{
    LessIdx_s009d_9620 predI;
    for (; first != last; ++first) {
        S_s009d_9620 val(*first);
        S_s009d_9620* hole = first;
        for (;;) {
            S_s009d_9620* prev = hole - 1;
            if (!predI(val, *prev))
                break;
            *hole = *prev;
            hole = prev;
        }
        *hole = val;
    }
}

// @ 0x009d9a90
void __cdecl InsertionSortWord(S_s009d_9620* first, S_s009d_9620* last)
{
    LessWord_s009d_9620 predW;
    if (first != last) {
        for (S_s009d_9620* it = first + 1; it != last; ++it) {
            S_s009d_9620 val(*it);
            S_s009d_9620* hole = it;
            while (hole != first) {
                S_s009d_9620* prev = hole - 1;
                if (!predW(val, *prev))
                    break;
                *hole = *prev;
                hole = prev;
            }
            *hole = val;
        }
    }
}

// @ 0x009d9bc0
void __cdecl UnguardedInsertionSortWord(S_s009d_9620* first, S_s009d_9620* last)
{
    LessWord_s009d_9620 predW;
    for (; first != last; ++first) {
        S_s009d_9620 val(*first);
        S_s009d_9620* hole = first;
        for (;;) {
            S_s009d_9620* prev = hole - 1;
            if (!predW(val, *prev))
                break;
            *hole = *prev;
            hole = prev;
        }
        *hole = val;
    }
}

// @ 0x009d9d60
void __cdecl PushHeapIdx(S_s009d_9620* first, int top, int hole, S_s009d_9620 value)
{
    LessIdx_s009d_9620 predI;
    int parent = (hole - 1) >> 1;
    while (top < hole && predI(first[parent], value)) {
        first[hole] = first[parent];
        hole = parent;
        parent = (hole - 1) >> 1;
    }
    first[hole] = value;
}

// @ 0x009d9e70
void __cdecl PushHeapWord(S_s009d_9620* first, int top, int hole, S_s009d_9620 value)
{
    LessWord_s009d_9620 predW;
    int parent = (hole - 1) >> 1;
    while (top < hole && predW(first[parent], value)) {
        first[hole] = first[parent];
        hole = parent;
        parent = (hole - 1) >> 1;
    }
    first[hole] = value;
}

// @ 0x009d9f80
void __cdecl SwapRecords(S_s009d_9620* a, S_s009d_9620* b)
{
    S_s009d_9620 tmp(*a);
    *a = *b;
    *b = tmp;
}

// @ 0x009da000
void S_s009d_9620::FillGroups(void* y)
{
    int n = idx.e - idx.b;
    items.Erase(items.b, items.e);
    for (int i = 0; i < n; ++i) {
        char* elem = owner->arr + idx.b[i] * 0x108;
        char* ybase = *(char**)((char*)y + 0x2e4);
        u32 ia = *(u32*)(elem + 0x58);
        char* rec = *(char**)(ybase + ia * 700);
        u32 ib = *(u32*)(rec + 0x430);
        Item_s009d_9620 it;
        it.key = (u32)(ybase + ib * 700);
        it.v.b = 0;
        it.v.c = 0;
        memcpy(0, 0, 0);
        it.v.e = 0;
        it.f18 = 0.0f;
        it.f1c = 0.0f;
        it.f20 = 0.0f;
        it.f34 = 0.0f;
        u32 elemp = (u32)elem;
        Item_s009d_9620* f = items.b;
        Item_s009d_9620* last = items.e;
        for (; f != last; ++f)
            if (it.key == f->key)
                break;
        if (f == last) {
            it.v.PushSlow(0, &elemp);
            Item_s009d_9620* pe = items.e;
            if (pe < items.c) {
                items.e = pe + 1;
                if (pe)
                    new (pe) Item_s009d_9620(it);
            } else {
                items.DoInsertValue(pe, it);
            }
        } else {
            PtrVec_s009d_9620& pv = f->v;
            u32* pe = pv.e;
            if (pe < pv.c) {
                pv.e = pe + 1;
                if (pe)
                    *pe = elemp;
            } else {
                pv.PushSlow(pe, &elemp);
            }
        }
    }
}

// @ 0x009da170
void __cdecl AdjustHeapIdx(S_s009d_9620* first, int top, int len, int hole, S_s009d_9620 value)
{
    LessIdx_s009d_9620 predI;
    int child = hole * 2 + 2;
    while (child < len) {
        if (predI(first[child], first[child - 1]))
            --child;
        first[hole] = first[child];
        hole = child;
        child = hole * 2 + 2;
    }
    if (child == len) {
        first[hole] = first[child - 1];
        hole = child - 1;
    }
    PushHeapIdx(first, top, hole, value);
}

// @ 0x009da2d0
void __cdecl AdjustHeapWord(S_s009d_9620* first, int top, int len, int hole, S_s009d_9620 value)
{
    LessWord_s009d_9620 predW;
    int child = hole * 2 + 2;
    while (child < len) {
        if (predW(first[child], first[child - 1]))
            --child;
        first[hole] = first[child];
        hole = child;
        child = hole * 2 + 2;
    }
    if (child == len) {
        first[hole] = first[child - 1];
        hole = child - 1;
    }
    PushHeapWord(first, top, hole, value);
}

// @ 0x009da430
void __cdecl PopHeapIdx(S_s009d_9620* first, S_s009d_9620* last)
{
    S_s009d_9620 val(last[-1]);
    last[-1] = *first;
    AdjustHeapIdx(first, 0, (int)(last - first) - 1, 0, val);
}

// @ 0x009da4f0
void __cdecl PopHeapWord(S_s009d_9620* first, S_s009d_9620* last)
{
    S_s009d_9620 val(last[-1]);
    last[-1] = *first;
    AdjustHeapWord(first, 0, (int)(last - first) - 1, 0, val);
}

// @ 0x009da5b0
void S_s009d_9620::SortGroups(u32)
{
    if (FSize(idx) == 3 && ISize(items) == 2)
        SortRange<SortGroupsSmall>(items.b, items.e);
    else
        SortRange<SortGroupsLarge>(items.b, items.e);
}

// 0x009da640: not byte-exact; the byte-exact version is the lifted one in match/slices/s009da640/s009da640_lifted.cpp
void Anim_s009d_a640::A640(void* ctx)
{
    // The original spills the loop counter into a 4-byte frame slot (its `push ecx` /
    // `pop ecx` frame), and the slot is only written once the non-empty guard is passed,
    // so on the empty path `pop ecx` still returns the incoming `this` in ecx.  A
    // volatile counter in an explicit guard reproduces that frame, so our ecx ends
    // where the original's does instead of leaking the trailing call's ecx clobber.
    int n = (*(int*)((char*)this + 0x14) - *(int*)((char*)this + 0x10)) / 0x104;
    int off = 0;
    if (n != 0) {
        volatile int count;
        for (count = n; count != 0; --count) {
            char* p = *(char**)((char*)this + 0x10) + off;
            ((Ops*)p)->F000(ctx);
            ((Ops*)p)->F5b0(ctx);
            ((Ops*)p)->F84f0();
            ((Ops*)p)->F1090((char*)this + 0x24);
            off += 0x104;
        }
    }
    ((Ops*)this)->F30b0();
}

// @ 0x009da6c0
void FUN_009da6c0(Elem* first, Elem* last, Compare cmp)
{
    int n = (int)((char*)last - (char*)first) / 0x104;
    if (n >= 2) {
        int i = ((n - 2) >> 1) + 1;
        Elem* p = (Elem*)((char*)first + i * 0x104);
        do {
            --i;
            p = (Elem*)((char*)p - 0x104);
            FUN_009da170(first, i, n, i, *p, cmp);
        } while (i != 0);
    }
}

// @ 0x009da790
void FUN_009da790(Elem* first, Elem* last, Compare cmp)
{
    int n = (int)((char*)last - (char*)first) / 0x104;
    if (n >= 2) {
        int i = ((n - 2) >> 1) + 1;
        Elem* p = (Elem*)((char*)first + i * 0x104);
        do {
            --i;
            p = (Elem*)((char*)p - 0x104);
            FUN_009da2d0(first, i, n, i, *p, cmp);
        } while (i != 0);
    }
}

// @ 0x009da860
Elem* FUN_009da860(Elem* first, Elem* last, Elem pivot, Compare cmp)
{
    for (;;) {
        while (cmp.CmpA(*first, pivot))
            ++first;
        do {
            last = (Elem*)((char*)last - 0x104);
        } while (cmp.CmpA(pivot, *last));
        if (first >= last)
            return first;
        FUN_009d9f80(first, last);
        ++first;
    }
}

// @ 0x009da980
void FUN_009da980(Elem* first, Elem* middle, Elem* last, Compare cmp)
{
    FUN_009da6c0(first, middle, cmp);
    for (Elem* i = middle; i < last; ++i) {
        if (cmp.CmpA(*i, *first)) {
            Elem temp(*i);
            *i = *first;
            FUN_009da170(first, 0, (int)((char*)middle - (char*)first) / 0x104, 0, temp, cmp);
        }
    }
    FUN_009da730(first, middle, cmp);
}

// @ 0x009dab00
Elem* FUN_009dab00(Elem* first, Elem* last, Elem pivot, Compare cmp)
{
    for (;;) {
        while (cmp.CmpB(*first, pivot))
            ++first;
        do {
            last = (Elem*)((char*)last - 0x104);
        } while (cmp.CmpB(pivot, *last));
        if (first >= last)
            return first;
        FUN_009d9f80(first, last);
        ++first;
    }
}

// @ 0x009dac20
void FUN_009dac20(Elem* first, Elem* middle, Elem* last, Compare cmp)
{
    FUN_009da790(first, middle, cmp);
    for (Elem* i = middle; i < last; ++i) {
        if (cmp.CmpB(*i, *first)) {
            Elem temp(*i);
            *i = *first;
            FUN_009da2d0(first, 0, (int)((char*)middle - (char*)first) / 0x104, 0, temp, cmp);
        }
    }
    FUN_009da800(first, middle, cmp);
}

// @ 0x009daef0
void FUN_009daef0(Elem* first, Elem* last, int depth, Compare cmp)
{
    while (((char*)last - (char*)first) / 0x104 > 0x1c && depth > 0) {
        Elem* mid = (Elem*)((char*)first + ((char*)last - (char*)first) / 0x208 * 0x104);
        Elem* med = FUN_009d8be0(first, mid, (Elem*)((char*)last - 0x104), cmp, cmp);
        Elem* cut = FUN_009da860(first, last, *med, cmp);
        --depth;
        FUN_009daef0(cut, last, depth, cmp);
        last = cut;
    }
    if (depth == 0)
        FUN_009da980(first, last, last, cmp);
}

// @ 0x009dafd0
void FUN_009dafd0(Elem* first, Elem* last, int depth, Compare cmp)
{
    while (((char*)last - (char*)first) / 0x104 > 0x1c && depth > 0) {
        Elem* mid = (Elem*)((char*)first + ((char*)last - (char*)first) / 0x208 * 0x104);
        Elem* med = FUN_009d8ce0(first, mid, (Elem*)((char*)last - 0x104), cmp, cmp);
        Elem* cut = FUN_009dab00(first, last, *med, cmp);
        --depth;
        FUN_009dafd0(cut, last, depth, cmp);
        last = cut;
    }
    if (depth == 0)
        FUN_009dac20(first, last, last, cmp);
}

// @ 0x009db0b0
void FUN_009db0b0(Elem* first, Elem* last, Compare cmp)
{
    if (first != last) {
        int n = (int)((char*)last - (char*)first) / 0x104;
        int i = n;
        int depth = 0;
        while (i != 0) {
            i >>= 1;
            ++depth;
        }
        FUN_009daef0(first, last, depth * 2 - 2, cmp);
        if (n > 0x1c) {
            FUN_009d9840(first, (Elem*)((char*)first + 0x1c70), cmp);
            FUN_009d9970((Elem*)((char*)first + 0x1c70), last, cmp);
        } else {
            FUN_009d9840(first, last, cmp);
        }
    }
}

// @ 0x009db140
void FUN_009db140(Elem* first, Elem* last, Compare cmp)
{
    if (first != last) {
        int n = (int)((char*)last - (char*)first) / 0x104;
        int i = n;
        int depth = 0;
        while (i != 0) {
            i >>= 1;
            ++depth;
        }
        FUN_009dafd0(first, last, depth * 2 - 2, cmp);
        if (n > 0x1c) {
            FUN_009d9a90(first, (Elem*)((char*)first + 0x1c70), cmp);
            FUN_009d9bc0((Elem*)((char*)first + 0x1c70), last, cmp);
        } else {
            FUN_009d9a90(first, last, cmp);
        }
    }
}

// @ 0x009db270
void Anim_s009d_a640::A270()
{
    *(float*)((char*)this + 0x78) = 1.0f;
    *(float*)((char*)this + 0x7c) = 1.0f;
    *(float*)((char*)this + 0x6c) = 0.0f;
    *(float*)((char*)this + 0x70) = 0.1f;
    *(float*)((char*)this + 0x4c) = 0.0f;
    *(float*)((char*)this + 0x50) = 0.0f;
    *(float*)((char*)this + 0x54) = 0.0f;
    *(float*)((char*)this + 0x58) = 0.0f;
    *(float*)((char*)this + 0x5c) = 0.0f;
    *(float*)((char*)this + 0x60) = 0.0f;
    *(float*)((char*)this + 0x08) = 0.0f;
    *(float*)((char*)this + 0x64) = 0.0f;
    *(float*)((char*)this + 0x68) = 0.0f;
    *(float*)((char*)this + 0x0c) = 0.0f;
    *(float*)((char*)this + 0x74) = 1.0f;
    *(int*)((char*)this + 0x00) = 0;
    *(int*)((char*)this + 0x04) = 0;
    *(float*)((char*)this + 0x80) = 1.0f;

    PhaseVec* v = (PhaseVec*)((char*)this + 0x10);
    Elem* begin = v->mpBegin;
    Elem* end = v->mpEnd;
    void* r = FUN_009d9ce0(end, end, begin);
    v->DoDestroyValues((Elem*)r, v->mpEnd);
    long x = (long)((char*)begin - (char*)end);
    v->mpEnd = (Elem*)((char*)end + x / 0x104 * 0x104);
}

// @ 0x009db330
Elem* Anim_s009d_a640::A330()
{
    int n = (*(int*)((char*)this + 0x14) - *(int*)((char*)this + 0x10)) / 0x104;
    Elem tmp;
    *(int*)(tmp.b + 0x48) = (int)this;
    *(int*)(tmp.b + 0xb8) = n;

    PhaseVec* v = (PhaseVec*)((char*)this + 0x10);
    Elem* p = v->mpEnd;
    if (p < v->mpCap) {
        v->mpEnd = p + 1;
        if (p)
            ((Ops*)p)->Copy(&tmp);
    } else {
        v->Grow(p, &tmp);
    }
    return (Elem*)((char*)v->mpBegin + n * 0x104);
}

// @ 0x009db3f0
void Anim_s009d_a640::A3f0(void* vec, int count)
{
    int n = (*(int*)((char*)vec + 0xc0) - *(int*)((char*)vec + 0xbc)) >> 2;
    int last = (int)vec;
    for (int i = n - 1; i >= count; --i) {
        last = *(int*)(*(int*)((char*)vec + 0xbc) + i * 4);
        *(int*)((char*)vec + 0xc0) -= 4;
    }

    Elem* e = A330();
    int num = n - count;
    int top = (*(int*)((char*)this + 0x14) - *(int*)((char*)this + 0x10)) / 0x104 - 1;
    U32Vec* sv = (U32Vec*)((char*)e + 0xbc);
    for (int i = 0; i < num; ++i) {
        u32* p = sv->mpEnd;
        if (p < sv->mpCap) {
            sv->mpEnd = p + 1;
            if (p)
                *p = (u32)last;
        } else {
            sv->DoInsertValue(p, (const u32&)last);
        }
        int k = *(int*)(sv->mpBegin + i);
        *(int*)(k * 0x108 + *(int*)((char*)this + 0x24) + 0xc4) = top;
        ++last;
    }
}

// @ 0x009db590
int Anim_s009d_a640::A590(void* a, void* b, int c)
{
    Elem* e = A330();
    U32Vec* sv = (U32Vec*)((char*)e + 0xbc);
    u32* p = sv->mpEnd;
    if (p < sv->mpCap) {
        sv->mpEnd = p + 1;
        if (p)
            *p = (u32)c;
    } else {
        sv->DoInsertValue(p, (const u32&)c);
    }
    int r = 1;
    if (a != b) {
        c = c + 1;
        p = sv->mpEnd;
        if (p < sv->mpCap) {
            sv->mpEnd = p + 1;
            if (p)
                *p = (u32)c;
        } else {
            sv->DoInsertValue(p, (const u32&)c);
        }
        r = 2;
    }
    ((Ops*)e)->F2dd0((char*)this + 0x38, a, b);
    return r;
}

// @ 0x009db630
int Anim_s009d_a640::A630(Solver** ps, Bone** pa, Bone** pb, int c)
{
    Solver* s = *ps;
    Bone* a = *pa;
    Bone* b = *pb;
    if (!s->Fn3430(a, b) || s->Fn5700(a, b)) {
        int i = s->Fn57b0(a, b);
        pa = pb = (Bone**)(i * 0x30 + *(int*)((char*)this + 0x38));
    }
    unsigned n = (unsigned)((*(int*)((char*)this + 0x14) - *(int*)((char*)this + 0x10)) / 0x104);
    if (n < 6)
        return A590(pa, pb, c);
    return 0;
}

// @ 0x009db6d0
void Layout_s009d_b6d0::Build(float ratio, World** ctx)
{
    uint32 count = (uint32)(seg_end - seg_begin);
    Seg* start = 0;
    Seg* last = 0;
    int total = 0;

    if ((*ctx)->f3e0 == 0) {
        Call630(ctx, seg_begin, seg_begin + count - 1, 0);
    } else {
        for (uint32 i = 0; i < count; ++i) {
            Seg* seg = seg_begin + i;
            char active = seg->obj->active;
            if (active) {
                if (start == 0)
                    start = seg;
                last = seg;
            }
            if (start != 0 && last != 0 && (!active || i == count - 1)) {
                total += Call630(ctx, start, last, total);
                last = 0;
                start = 0;
            }
        }
    }

    sub_9DB0B0(parts_begin, parts_end, 0);

    uint32 parts = (uint32)(parts_end - parts_begin);
    if (parts > 1) {
        float first = parts_begin[0].Time();
        uint32 split = 1;
        while (split < parts) {
            if (parts_begin[split].Time() / first > ratio)
                break;
            ++split;
        }
        if (split > 1) {
            float lastTime = parts_begin[split - 1].Time();
            uint32 n = split - 1;
            if (n != 0) {
                Part* part = parts_begin;
                do {
                    float scale = part->Time() / lastTime;
                    int* ids = part->ids_begin;
                    uint32 used = (uint32)(part->ids_end - part->ids_begin);
                    for (uint32 k = 0; k < used; ++k) {
                        Particle* p = (Particle*)(particles + ids[k] * sizeof(Particle));
                        p->v0 = p->v0 * scale;
                        p->v1 = scale * p->v1;
                    }
                    ++part;
                } while (--n != 0);
            }
        }
    }

    sub_9DB140(parts_begin, parts_end, 0);

    for (uint32 i = 0; i < parts; ++i) {
        Part* part = parts_begin + i;
        int* ids = part->ids_begin;
        uint32 used = (uint32)(part->ids_end - part->ids_begin);
        for (uint32 k = 0; k < used; ++k) {
            Particle* p = (Particle*)(particles + ids[k] * sizeof(Particle));
            p->index = (int)i;
        }
    }
}

// @ 0x009dba20
void Blend9::Pos(const Blend9* a, float t, const Blend9* b)
{
    float inv = 1.0f - t;
    v[0] = a->v[0] * inv + b->v[0] * t;
    v[1] = a->v[1] * inv + b->v[1] * t;
    v[2] = a->v[2] * inv + b->v[2] * t;
}

// @ 0x009dbd50
float Track::Total()
{
    float acc[3] = { 0.0f, 0.0f, 0.0f };
    int n = count;
    int j = 0;
    if (n >= 2) {
        int pairs = ((unsigned)(n - 2) >> 1) + 1;
        const float* c = (const float*)((const char*)this + 0x140 + 0xb4);
        const float* wv = (const float*)((const char*)this + 0x7c) + 1;
        j = pairs * 2;
        do {
            acc[1] = c[-0x2d] * wv[-1] + acc[1];
            acc[2] = c[0] * wv[0] + acc[2];
            wv += 2;
            c += 0x5a;
        } while (--pairs);
    }
    if (j < n)
        acc[2] = w[j] * Channel(j);
    return acc[0] + acc[1] + acc[2];
}

// @ 0x009dbe10
void* Grid::Set(void* value, int row, int col)
{
    return m[row][col] = value;
}

// @ 0x009dc410
void Blend9::All(const Blend9* a, float t, const Blend9* b)
{
    float inv = 1.0f - t;
    v[0] = a->v[0] * inv + b->v[0] * t;
    v[1] = a->v[1] * inv + b->v[1] * t;
    v[2] = a->v[2] * inv + b->v[2] * t;
    float* d = &r[0][0];
    const float* pa = &a->r[0][0];
    const float* pb = &b->r[0][0];
    for (int i = 3; i != 0; --i) {
        d[0] = pa[0] * inv + pb[0] * t;
        d[1] = pa[1] * inv + pb[1] * t;
        d += 4;
        pa += 4;
        pb += 4;
    }
}

// @ 0x009dc4f0
void BlendQ::All(const BlendQ* a, float t, const BlendQ* b)
{
    float buf[4];
    float* res = sub_99CC70(buf, a->q, b->q, t);
    q[0] = res[0];
    q[1] = res[1];
    q[2] = res[2];
    q[3] = res[3];
    float inv = 1.0f - t;
    for (int i = 0; i < 4; ++i) {
        r[i][0] = a->r[i][0] * inv + b->r[i][0] * t;
        r[i][1] = a->r[i][1] * inv + b->r[i][1] * t;
    }
}

// @ 0x009dc6a0
int Track2::TotalItems()
{
    int n = count;
    int sumA = 0;
    int sumB = 0;
    int tail = 0;
    unsigned i = 0;
    if (n > 1) {
        const Path104* p = paths;
        unsigned pairs = ((unsigned)(n - 2) >> 1) + 1;
        i = pairs * 2;
        do {
            sumA += (int)(p[0].end - p[0].begin) * 8;
            sumB += (int)(p[1].end - p[1].begin) * 8;
            p += 2;
        } while (--pairs != 0);
    }
    if (i < (unsigned)n)
        tail = (int)(paths[i].end - paths[i].begin) * 8;
    return sumA + sumB + tail;
}

// @ 0x009dd6a0
i32 Track2_s009d_d6a0::ItemCount()
{    i32 total = 0;
    u32 nb = mCount;
    if (nb > 0) {
        u8* b = (u8*)mBlocks + 0x24;
        u32 bn = nb;
        do {
            i32 n = (*(i32*)(b + 4) - *(i32*)b) >> 6;
            u32 k = 0;
            if ((u32)n > 0) {
                i32* it = (i32*)(*(volatile i32*)b + 0x30);
                do {
                    total += ((*(it - 10) - *(it - 11)) / 0x44) * 0x44;
                    total += ((*(it - 5)  - *(it - 6))  / 0x58) * 0x58;
                    total += ((*(it)      - *(it - 1))  / 0x1c) * 0x1c;
                    total += 0xc;
                    ++k;
                    it += 0x10;
                } while (k < (u32)n);
            }
            b += 0xa4;
        } while (--bn != 0);
    }
    return total;
}

// @ 0x009dd780
void __thiscall Track2_s009d_d6a0::Grids(void* dstp)
{
    u8*  dst = (u8*)dstp;
    u8*  cur;
    u32  bi;

    *(i32*)(dst + 0x14) = (i32)mCount;
    cur = dst + 0x18 + *(i32*)(dst + 0x10) * 8;
    bi = 0;
    if (mCount == 0) return;

    for (;;) {
        Block* b = (Block*)((u8*)mBlocks + bi * 0xa4);
        u8*  tmp = cur;

        if (b->mHitTest == -1) goto next;

        // header copy: 0x1c words
        {
            u8* s = (u8*)b;
            *(u32*)(cur + 0x00) = *(u32*)(s + 0x00);
            *(u32*)(cur + 0x04) = *(u32*)(s + 0x04);
            *(u32*)(cur + 0x08) = *(u32*)(s + 0x08);
            *(u32*)(cur + 0x0c) = *(u32*)(s + 0x38);
            *(u32*)(cur + 0x10) = *(u32*)(s + 0x3c);
            *(u32*)(cur + 0x14) = *(u32*)(s + 0x40);
            *(u32*)(cur + 0x18) = *(u32*)(s + 0x44);
            *(u32*)(cur + 0x1c) = *(u32*)(s + 0x48);
            *(u32*)(cur + 0x20) = *(u32*)(s + 0x4c);
            *(u32*)(cur + 0x24) = *(u32*)(s + 0x50);
            *(u32*)(cur + 0x28) = *(u32*)(s + 0x54);
            *(u32*)(cur + 0x2c) = *(u32*)(s + 0x58);
            *(u32*)(cur + 0x30) = *(u32*)(s + 0x5c);
            *(u32*)(cur + 0x34) = *(u32*)(s + 0x60);
            *(u32*)(cur + 0x38) = *(u32*)(s + 0x64);
            *(u32*)(cur + 0x3c) = *(u32*)(s + 0x68);
            *(u32*)(cur + 0x40) = *(u32*)(s + 0x6c);
            *(u32*)(cur + 0x44) = *(u32*)(s + 0x70);
            *(u32*)(cur + 0x48) = *(u32*)(s + 0x74);
            *(u32*)(cur + 0x4c) = *(u32*)(s + 0x78);
            *(u32*)(cur + 0x50) = *(u32*)(s + 0x7c);
            *(u32*)(cur + 0x54) = *(u32*)(s + 0x80);
            *(u32*)(cur + 0x58) = *(u32*)(s + 0x84);
            *(u32*)(cur + 0x5c) = *(u32*)(s + 0x88);
            *(u32*)(cur + 0x60) = *(u32*)(s + 0x8c);
            *(u32*)(cur + 0x64) = *(u32*)(s + 0x90);
            *(u32*)(cur + 0x68) = *(u32*)(s + 0x94);
            *(u32*)(cur + 0x6c) = *(u32*)(s + 0x98);
            *(u32*)(cur + 0x70) = *(u32*)(s + 0x9c);
        }

        // point-pair count and the static pair array (0x74 = (end-begin)/0xc)
        {
            i32 n = (*(i32*)((u8*)b + 0x14) - *(i32*)((u8*)b + 0x10)) / 0xc;
            i32* ptr = (i32*)((u8*)b + 0x10);
            i32* dst74 = (i32*)(cur + 0x74);
            *dst74 = n;
            tmp = (u8*)b + 0x7c;
            if (n != 0) {
                i32 j = 0;
                u8* o = (u8*)cur + 0x7c;
                for (i32 i = 0; i < n; ++i) {
                    *(float*)o = *(float*)(*ptr + j);
                    *(float*)(o + 4) = *(float*)(*ptr + j + 4);
                    o += 8;
                    j += 0xc;
                }
                tmp = o;
            }
            (void)dst74;
        }

        // item-group count (+0x78 = (end-begin)>>6)
        {
            i32 ngroups = (*(i32*)((u8*)b + 0x28) - *(i32*)((u8*)b + 0x24)) >> 6;
            *(i32*)(cur + 0x78) = ngroups;
            u32 gi = 0;
            u8* out = tmp;
            if (ngroups == 0) goto after_groups;

            for (;;) {
                u8* g = (u8*)(*(i32*)((u8*)b + 0x24) + gi * 0x40);
                i32 na, nb, nc;
                *(i32*)out = (*(i32*)(g + 8) - *(i32*)(g + 4)) / 0x44;
                *(i32*)(out + 4) = (*(i32*)(g + 0x1c) - *(i32*)(g + 0x18)) / 0x58;
                *(i32*)(out + 8) = (*(i32*)(g + 0x30) - *(i32*)(g + 0x2c)) / 0x1c;
                na = *(i32*)out;
                nb = *(i32*)(out + 4);
                nc = *(i32*)(out + 8);

                u8* p = out + 0xc;                        // item array start

                // item headers: 0x44 bytes each, 0x11 dwords copied
                for (i32 i = 0; i < na; ++i) {
                    u8* src = (u8*)(*(i32*)(g + 4) + i * 0x44);
                    u8* d = p + i * 0x44;
                    *(u32*)(d + 0x00) = *(u32*)(src + 0x04);
                    *(u32*)(d + 0x04) = *(u32*)(src + 0x08);
                    *(u32*)(d + 0x08) = *(u32*)(src + 0x0c);
                    *(u32*)(d + 0x0c) = *(u32*)(src + 0x10);
                    *(u32*)(d + 0x10) = *(u32*)(src + 0x14);
                    *(u32*)(d + 0x14) = *(u32*)(src + 0x18);
                    *(u32*)(d + 0x18) = *(u32*)(src + 0x1c);
                    *(u32*)(d + 0x1c) = *(u32*)(src + 0x20);
                    *(u32*)(d + 0x20) = *(u32*)(src + 0x24);
                    *(u32*)(d + 0x24) = *(u32*)(src + 0x28);
                    *(u32*)(d + 0x28) = *(u32*)(src + 0x2c);
                    *(u32*)(d + 0x2c) = *(u32*)(src + 0x30);
                    *(u32*)(d + 0x30) = *(u32*)(src + 0x34);
                    *(u32*)(d + 0x34) = *(u32*)(src + 0x38);
                    *(u32*)(d + 0x38) = *(u32*)(src + 0x3c);
                    *(u32*)(d + 0x3c) = *(u32*)(src + 0x40);
                    *(u32*)(d + 0x40) = *(u32*)(src + 0x44);
                }
                p += na * 0x44;

                // cone groups: 0x58 bytes each, 0x16 dwords copied
                for (i32 i = 0; i < nb; ++i) {
                    u8* src = (u8*)(*(i32*)(g + 0x18) + i * 0x58);
                    u8* d = p + i * 0x58;
                    *(u32*)(d + 0x00) = *(u32*)(src + 0x04);
                    *(u32*)(d + 0x04) = *(u32*)(src + 0x08);
                    *(u32*)(d + 0x08) = *(u32*)(src + 0x0c);
                    *(u32*)(d + 0x0c) = *(u32*)(src + 0x10);
                    *(u32*)(d + 0x10) = *(u32*)(src + 0x14);
                    *(u32*)(d + 0x14) = *(u32*)(src + 0x18);
                    *(u32*)(d + 0x18) = *(u32*)(src + 0x1c);
                    *(u32*)(d + 0x1c) = *(u32*)(src + 0x20);
                    *(u32*)(d + 0x20) = *(u32*)(src + 0x24);
                    *(u32*)(d + 0x24) = *(u32*)(src + 0x28);
                    *(u32*)(d + 0x28) = *(u32*)(src + 0x2c);
                    *(u32*)(d + 0x2c) = *(u32*)(src + 0x30);
                    *(u32*)(d + 0x30) = *(u32*)(src + 0x34);
                    *(u32*)(d + 0x34) = *(u32*)(src + 0x38);
                    *(u32*)(d + 0x38) = *(u32*)(src + 0x3c);
                    *(u32*)(d + 0x3c) = *(u32*)(src + 0x40);
                    *(u32*)(d + 0x40) = *(u32*)(src + 0x44);
                    *(u32*)(d + 0x44) = *(u32*)(src + 0x48);
                    *(u32*)(d + 0x48) = *(u32*)(src + 0x4c);
                    *(u32*)(d + 0x4c) = *(u32*)(src + 0x50);
                    *(u32*)(d + 0x50) = *(u32*)(src + 0x54);
                }
                p += nb * 0x58;

                // weight records: 0x1c bytes each, header at p, 4 dwords after a 2-dword gap
                for (i32 i = 0; i < nc; ++i) {
                    u8* src = (u8*)(*(i32*)(g + 0x2c) + i * 0x1c);
                    u8* d = p + i * 0x1c;
                    *(u32*)(d + 0x04) = *(u32*)(src + 0x04);
                    *(u32*)(d + 0x08) = *(u32*)(src + 0x08);
                    *(u32*)(d + 0x0c) = *(u32*)(src + 0x0c);
                    *(u32*)(d + 0x10) = *(u32*)(src + 0x10);
                    *(u32*)(d + 0x14) = *(u32*)(src + 0x14);
                    *(u32*)(d + 0x18) = *(u32*)(src + 0x18);
                }
                p += nc * 0x1c;

                out = p;
                if (++gi >= (u32)ngroups) break;
            }
            tmp = out;
        }

    after_groups:
        cur = tmp;

    next:
        if (++bi >= mCount) break;
    }
    return;
}

// @ 0x009ddca0
void Self::Cmd3(cArguments* args)
{
    u32* a = args->MainArguments(3);
    for (int i = 0; i < 3; ++i) {
        float* d = (float*)(*(u8**)((u8*)mOwner + 4) + 0x7c) + i;
        *d = mEval->Eval((i32)a[i]);
    }
}

// @ 0x009ddcf0
void Self::Cmd4(cArguments* args)
{
    u32* a = args->MainArguments(4);
    for (int i = 0; i < 4; ++i) {
        float* d = (float*)(*(u8**)((u8*)mOwner + 4) + 0x24) + i;
        *d = mEval->Eval((i32)a[i]);
    }
}

// @ 0x009ddd70
void Self::CmdTable8(cArguments* args)
{
    u8*  base = *(u8**)((u8*)mOwner + 4);
    i32 mode = *(i32*)(base + 0xc4);

    if (mode == 0) {
        u32* a = args->MainArguments(6);
        u8*  p = base + (*(i32*)(base + 0xd8) - *(i32*)(base + 0xd4)) / 0x44 * 0x44
                    + *(i32*)(base + 0xd4) - 0x28;
        for (i32 r = 0; r < 3; ++r) {
            for (i32 c = 0; c < 2; ++c) {
                float f = mEval->Eval((i32)*a++);
                *(u8*)(p + c) = (u8)(i32)f;
            }
            p += 0x10;
        }
    } else if (mode == 1) {
        u32* a = args->MainArguments(8);
        u8*  p = base + (*(i32*)(base + 0xec) - *(i32*)(base + 0xe8)) / 0x58 * 0x58
                    + *(i32*)(base + 0xe8) - 0x38;
        for (i32 r = 0; r < 4; ++r) {
            for (i32 c = 0; c < 2; ++c) {
                float f = mEval->Eval((i32)*a++);
                *(u8*)(p + c) = (u8)(i32)f;
            }
            p += 0x10;
        }
    } else if (mode == 2) {
        u32* a = args->MainArguments(2);
        u8*  p = base + (*(i32*)(base + 0x100) - *(i32*)(base + 0xfc)) / 0x1c * 0x1c
                    + *(i32*)(base + 0xfc) - 0x1c;
        for (i32 c = 0; c < 2; ++c) {
            float f = mEval->Eval((i32)*a++);
            *(u8*)(p + 0x13 + c) = (u8)(i32)f;
        }
    }
}

// @ 0x009ddf80
void Self::CmdTable16(cArguments* args)
{
    u8*  base = *(u8**)((u8*)mOwner + 4);
    i32 mode = *(i32*)(base + 0xc4);

    if (mode == 0) {
        u32* a = args->MainArguments(3);
        u8*  p = base + (*(i32*)(base + 0xd8) - *(i32*)(base + 0xd4)) / 0x44 * 0x44
                    + *(i32*)(base + 0xd4) - 0x26;
        for (i32 i = 0; i < 3; ++i) {
            float f = mEval->Eval((i32)a[i]);
            *(u16*)(p + i * 0x10) = (u16)(i32)f;
        }
    } else if (mode == 1) {
        u32* a = args->MainArguments(4);
        u8*  p = base + (*(i32*)(base + 0xec) - *(i32*)(base + 0xe8)) / 0x58 * 0x58
                    + *(i32*)(base + 0xe8) - 0x36;
        for (i32 i = 0; i < 4; ++i) {
            float f = mEval->Eval((i32)a[i]);
            *(u16*)(p + i * 0x10) = (u16)(i32)f;
        }
    } else if (mode == 2) {
        u32* a = args->MainArguments(1);
        u8*  p = base + (*(i32*)(base + 0x100) - *(i32*)(base + 0xfc)) / 0x1c * 0x1c
                    + *(i32*)(base + 0xfc) - 6;
        float f = mEval->Eval((i32)a[0]);
        *(u16*)p = (u16)(i32)f;
    }
}
