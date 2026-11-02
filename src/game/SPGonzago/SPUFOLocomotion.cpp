// src/game/SPGonzago/SPUFOLocomotion.cpp -- migrated from slice(s) s01060df0, s0105f2d0, s0105e6d0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUFOLocomotion.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cStarManager.h"

// unnamed retail callees and globals (address in the comment)
extern float __cdecl GetStarRadius(int starType);
extern const float kHitMiss;               // 0x013eb1bc: -1.0f
extern const float kAvoidRadiusScale;      // 0x01485548: 1.5f
extern const float kAvoidDistanceScale;    // 0x013ec4b4: 0.9f
extern const float kMinTargetLength;       // 0x0149bfc0: 1.5258789e-05f
extern const float kRadiusForKindOne;      // 0x015b8e18
extern const float kRadiusForOtherKinds;   // 0x015b8e14
#include <math.h>
#include <stddef.h>
#include "SP/cCivData.h"
#include "SP/cSPTimer.h"
#include "SP/cSPGameDataUFO.h"
#include "SP/cCameraManager.h"
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cPlanetModel.h"
#include "SP/cSpatialObject.h"
#include <xmmintrin.h>

// ---- items of slice s0105e6d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char uchar;
struct Vector3 {
    float x;
    float y;
    float z;
};
struct Quaternion {
    float x;
    float y;
    float z;
    float w;
};
extern Vector3* __cdecl Vector3_Normalize(Vector3* out, const Vector3* v);
extern Vector3* __cdecl normalized_safe(Vector3* out, const Vector3* v);
extern Vector3* __cdecl ClosestPointOnSegment(Vector3* out, const Vector3* a, const Vector3* b,
                                              const Vector3* p);
extern bool __cdecl IntersectRaySphere(const Vector3* origin, const Vector3* dir,
                                       const Vector3* center, float radius, float* hitTime);
extern float __cdecl GetStarRadius(int starType);
extern const Vector3 kOrigin;              // 0x016e2114: (0,0,0)
extern const Vector3 kAvoidOrigin;         // 0x016e2190: (0,0,0)
extern const float kHitMiss;               // 0x013eb1bc: -1.0f
extern const float kAvoidRadiusScale;      // 0x01485548: 1.5f
extern const float kAvoidDistanceScale;    // 0x013ec4b4: 0.9f
extern const float kMinTargetLength;       // 0x0149bfc0: 1.5258789e-05f
extern const float kRadiusForKindOne;      // 0x015b8e18
extern const float kRadiusForOtherKinds;   // 0x015b8e14
struct SpatialObject {
    virtual void vf00();
    virtual void vf01();
    virtual void vf02();
    virtual void vf03();
    virtual void vf04();
    virtual void vf05();
    virtual void vf06();
    virtual void vf07();
    virtual void vf08();
    virtual void vf09();
    virtual void vf10();
    virtual Vector3* GetPosition();                 // +0x2c
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void SetOrientation(const Quaternion* q); // +0x3c
};
struct BodyRecord {
    char mPad00[0xa0];
    Vector3 mPosition;                              // +0xa0
};
struct ObstacleKindData {
    char mPad00[0x28];
    int mKind;                                      // +0x28
};
struct Obstacle : SpatialObject {
    char mPad04[0x138];
    ObstacleKindData* mpKindData;                   // +0x13c

    // Retail 0x00c70880: kind stored in the attached kind record, or 2.
    int GetKind();
};
struct PlayerInventory {
    char mPad00[0x10];
    Obstacle** mpObstacleBegin;                     // +0x10
    Obstacle** mpObstacleEnd;                       // +0x14
    char mPad18[0x20];
    BodyRecord* mpStarRecord;                       // +0x38
    BodyRecord* mpPlanetRecord;                     // +0x3c
};
struct UFOState {
    virtual void vf00();
    virtual void vf01();
    virtual void vf02();
    virtual void vf03();
    virtual void vf04();
    virtual void vf05();
    virtual void vf06();
    virtual void vf07();
    virtual void vf08();
    virtual void vf09();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void* GetPlanet();                      // +0x4c

    char mPad04[0x10];
    SpatialObject* mpSpatialObject;                 // +0x14: points at mSpatial
    char mPad18[0x1c];
    SpatialObject mSpatial;                         // +0x34
    char mPad38[0x718 - 0x38];
    Vector3 mDesiredVelocity;                       // +0x718
    char mPad724[0x730 - 0x724];
    Quaternion mOrientation;                        // +0x730
    char mPad740[0x74c - 0x740];
    uchar mIgnoreAvoidance;                         // +0x74c
    char mPad74d[0x13];
};
struct cSPSimulatorSpaceGame {
    char mPad00[0x34];
    int mCurrentStarType;                           // +0x34
    char mPad38[8];
    PlayerInventory* mpPlayerState;                 // +0x40
    __declspec(noinline) PlayerInventory* GetPlayerInventory();
    __declspec(noinline) bool IsGalaxyView();
    __declspec(noinline) int GetCurrentStarType();
};
extern cSPSimulatorSpaceGame* __cdecl GetUFOSimulator();
extern Obstacle* __cdecl GetActivePlanet();
struct MotionOutput {
    Vector3 mVelocity;                              // +0x00
    float mPad0c;
    float mTurnAmount;                              // +0x10
    SpatialObject* mpSpatial;                       // +0x14
};
namespace SP {
class cUFOLocomotion {
public:
    virtual void vf00();
    virtual void vf01();
    virtual void vf02();
    virtual void vf03();
    char mPad04[0xc];
    Vector3 mFacing;                                // +0x10

    void FUN_0105eb90(MotionOutput* out);
    void AvoidSolarObstacles(cSPSimulatorSpaceGame* sim, UFOState* ufo, Vector3* position);
};  // namespace SP
}
int __thiscall Obstacle::GetKind()
{
    return mpKindData ? mpKindData->mKind : 2;
}
PlayerInventory* __thiscall cSPSimulatorSpaceGame::GetPlayerInventory()
{
    return mpPlayerState;
}
bool __thiscall cSPSimulatorSpaceGame::IsGalaxyView()
{
    return false; // retail 0x00c8b7e0
}
int __thiscall cSPSimulatorSpaceGame::GetCurrentStarType()
{
    return 0; // retail 0x00c8b550
}
// ---- items of slice s0105e6d0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern Vector3* __cdecl Vector3_Normalize(Vector3* out, const Vector3* v);
extern Vector3* __cdecl normalized_safe(Vector3* out, const Vector3* v);
extern Vector3* __cdecl ClosestPointOnSegment(Vector3* out, const Vector3* a, const Vector3* b,
                                              const Vector3* p);
extern bool __cdecl IntersectRaySphere(const Vector3* origin, const Vector3* dir,
                                       const Vector3* center, float radius, float* hitTime);
extern const Vector3 kOrigin;              // 0x016e2114: (0,0,0)
extern const Vector3 kAvoidOrigin;         // 0x016e2190: (0,0,0)
extern cSPSimulatorSpaceGame* __cdecl GetUFOSimulator();
extern Obstacle* __cdecl GetActivePlanet();

// ---- items of slice s0105f2d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_fSolarZeroX;               // 0x016e2114 (zero-initialised)
extern float g_fSolarZeroY;               // 0x016e2118
extern float g_fSolarZeroZ;               // 0x016e211c
extern uint8_t g_bSolarAvoidEnabled;      // 0x015b8e24
extern float g_fSolarArrivePlanet;        // 0x015b8e20 = 0.5f
extern float g_fSolarArriveStar;          // 0x015b8e1c = 0.001f
extern float g_fSolarBodyRadius;          // 0x015b8e28 = 20.0f
extern void* g_ufoBodyFilter;        // 0x018ebadc
class cSPVector3_s0105_f2d0 {
public:
    float mX;                    // +0x00
    float mY;                    // +0x04
    float mZ;                    // +0x08
};
class cSPVector4_s0105_f2d0 {
public:
    float mX;                    // +0x00
    float mY;                    // +0x04
    float mZ;                    // +0x08
    float mW;                    // +0x0c
};
extern cSPVector3_s0105_f2d0 g_vSolarAxisX;          // 0x015b8d9c = (1, 0, 0)
extern cSPVector3_s0105_f2d0 g_vSolarAxisY;          // 0x015b8da8 = (0, 1, 0)
extern cSPVector3_s0105_f2d0 g_vSolarAxisZ;          // 0x015b8db4 = (0, 0, 1)
class cSPTimer {
public:
    void Restart();                                      // 0x00bc3130
    uint64_t GetElapsedTime();                           // 0x00bc3190
    uint8_t mnPad000[0x48];                              // opaque timer payload
};
class cUFODockState {                                    // lives at ship + 0x628
public:
    void UpdateDockedParent();                           // 0x00bc3170
    uint8_t mnPad000[0x20];
};
class cUFOWaypoint {                                     // referenced by +0x75c
public:
    cSPVector3_s0105_f2d0* GetPosition();                           // vtable slot +0x2c
};
class cCivData {                                         // referenced by +0x764
public:
    cSPVector3_s0105_f2d0* GetCities();                             // 0x005c65e0
};
class cUFOShipState {
public:
    uint8_t mnPad000[0x628];        // +0x000
    cUFODockState mDockState;       // +0x628
    cSPTimer mTimer;                // +0x648 (0x48 bytes)
    bool mbSolarActive;             // +0x690
    uint8_t mnPad691[0x83];         // +0x691
    int32_t mnSolarTarget;          // +0x714
    cSPVector3_s0105_f2d0 mSolarPosition;      // +0x718
    cSPVector3_s0105_f2d0 mSolarVelocity;      // +0x724
    cSPVector4_s0105_f2d0 mSolarHeading;       // +0x730
    bool mbSolarArrived;            // +0x74c
    uint8_t mnPad74d[3];            // +0x74d
    cSPVector3_s0105_f2d0 mSolarDestination;   // +0x750
    cUFOWaypoint* mpSolarWaypoint;  // +0x75c
    uint32_t mnPad760;              // +0x760
    cCivData* mpCivData;            // +0x764
    uint32_t mnPad768;              // +0x768
    int32_t mnWarpGroup;            // +0x76c

    bool PopToDestination();                             // 0x00c37e60
};
class cSPSimulatorSpaceGame_s0105_f2d0 {
public:
    void* GetPlayerInventory();                          // 0x00a1ad60
    void OnStarMoveDone();                               // 0x00fff6a0
    void OnPlanetMoveDone();                             // 0x01000520
};
class cUFOKinestheticsTuning {
public:
    uint8_t mnPad000[0x114];        // +0x000
    float mGalaxyMaxPlump;          // +0x114
    float mGalaxyMinPlumpDistance;  // +0x118
    float mGalaxyMaxPlumpDistance;  // +0x11c
    float mBaseUFODamagePush;       // +0x120
    float GetGalaxyWarpMultiplier(int32_t nWarpGroup, int32_t nTarget);  // 0x00c3b880
};
class cGameContext {
public:
    uint8_t mnPad000[0x2c];         // +0x000
    int32_t mnGameMode;             // +0x2c
    uint8_t mnPad030[0x118];        // +0x030
    int32_t mnModeToken;            // +0x148
};
class cUniverseContext {
public:
    bool IsPlayerControlled();                           // 0x00c8b800
};
class cUFOState {
public:
    uint8_t mnPad000[0x10];         // +0x000
    float mDeltaSeconds;            // +0x10
    void* mpShipBase;               // +0x14

    cSPSimulatorSpaceGame_s0105_f2d0* GetSimulator();               // 0x00ffbe50
};
struct cUFOViewVTable {
    uint8_t mnPad000[0xc8];          // +0x000
    void (__thiscall* mpPushBody)(void* pThis, cSPVector3_s0105_f2d0* pDirection,
                                  float fDistance, int32_t nMode);       // +0x0c8
};
class cUFOView {
public:
    cUFOViewVTable* mpVTable;        // +0x00
};
class cGameDataObject {
public:
    uint8_t mnPad000[0x34];          // +0x000
    void* mpVTableHolder;            // +0x34
    cSPVector3_s0105_f2d0* GetCollisionPosition();                          // vtable slot +0x2c
};
struct cGameDataVector {
    intptr_t* mpBegin;               // +0x00
    intptr_t* mpEnd;                 // +0x04
};
cGameDataVector* __cdecl FindGameDataVector(void* pContext, void* pFilter); // 0x00b21340
void* __cdecl FindGameDataContext();                                      // 0x00b3d300
cUFOKinestheticsTuning* __cdecl GetKinestheticsTuning();                  // 0x00c37360
int32_t __cdecl GetUniverseContext();                                     // 0x01021080
cUniverseContext* __cdecl GetUniverseContextObject();                     // 0x01021230
cGameContext* __cdecl GetGameContext();                                   // 0x00b3d4d0
void __cdecl PhysicsMoveUFO(cSPVector3_s0105_f2d0* pPosition, cSPVector3_s0105_f2d0* pVelocity,
                            const cSPVector3_s0105_f2d0* pTarget, float fMaxPlump,
                            float fPush, float fDeltaSeconds);            // 0x010426a0
cSPVector3_s0105_f2d0* __cdecl RotateVectorByQuaternion(cSPVector3_s0105_f2d0* pOut,
                                             const cSPVector3_s0105_f2d0* pAxis,
                                             const cSPVector4_s0105_f2d0* pQuat);     // 0x0059aed0
cSPVector4_s0105_f2d0* __cdecl QuaternionFromFacingAndUp(cSPVector4_s0105_f2d0* pOut,
                                              const cSPVector3_s0105_f2d0* pFacing,
                                              const cSPVector3_s0105_f2d0* pUp);      // 0x0069b600
cSPVector3_s0105_f2d0* __cdecl RotateVectorInPlace(cSPVector3_s0105_f2d0* pVector,
                                        const cSPVector4_s0105_f2d0* pQuat);          // 0x00799320
cSPVector4_s0105_f2d0* __cdecl SlerpHeading(const cSPVector4_s0105_f2d0* pFrom, cSPVector4_s0105_f2d0* pOut,
                                 const cSPVector3_s0105_f2d0* pDirection,
                                 float fScale);                            // 0x005b26f0
cSPVector4_s0105_f2d0* __cdecl SlerpHeadingSlow(const cSPVector3_s0105_f2d0* pDirection,
                                     const cSPVector4_s0105_f2d0* pFrom,
                                     const cSPVector4_s0105_f2d0* pTo,
                                     float fScale);                        // 0x005b2500
cSPVector3_s0105_f2d0* __cdecl NormalizeVectorGuarded(cSPVector3_s0105_f2d0* pOut,
                                           const cSPVector3_s0105_f2d0* pIn);         // 0x00449c20
cSPVector3_s0105_f2d0* __cdecl NormalizeVector(cSPVector3_s0105_f2d0* pOut,
                                    const cSPVector3_s0105_f2d0* pIn);                // 0x00436ce0
cSPVector3_s0105_f2d0* __cdecl ClosestPointOnSegment(cSPVector3_s0105_f2d0* pOut,
                                          const cSPVector3_s0105_f2d0* pA,
                                          const cSPVector3_s0105_f2d0* pB,
                                          const cSPVector3_s0105_f2d0* pP);           // 0x00698e00
cUFOView* __cdecl GetSolarView();                                         // 0x0067de00
class cUFOLocomotion_s0105_f2d0 {
public:
    void UpdateSolarGalaxyLocomotion(cUFOState* pState, int32_t nDeltaMs);   // @ 0x0105f2d0
    void UpdateCourse(cUFOState* pState, int32_t nDeltaMs);                  // 0x0105e290
    void AvoidSolarObstacles(cUniverseContext* pUniverse, cUFOShipState* pShip,
                             cSPVector3_s0105_f2d0* pTarget);                           // 0x0105eeb0
    void UpdateSolarCourse(cUFOShipState* pShip, cSPVector3_s0105_f2d0* pTarget);       // 0x0105d200
};
void UpdateSolarAvoidance(cUFOShipState* pShip, float fAmplitude,
                          int32_t nDeltaMs);                             // @ 0x0105f760
cSPVector3_s0105_f2d0* __stdcall UpdateSolarBody(cSPVector3_s0105_f2d0* pOut,
                                      cUFOShipState* pShip);             // @ 0x0105fbc0
// ---- items of slice s0105f2d0 end

// ---- items of slice s01060df0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#ifndef NULL
#define NULL 0
#endif
extern const float   kPI;                    // 0x015B8D98
extern const float kDamageOffsetMaxLength;   // 0x015B8E2C 0.5
extern const float kDamageOffsetDecayRate;   // 0x015B8E30 0.7
extern const float kArriveDistanceSq;        // 0x015B8E34 1.0
extern const float kRecentCollisionMs;       // 0x015B8E38 300.0
extern const float kZoomAltitudeTolerance;   // 0x015B8E3C 2.0
extern const float kNearbyRadiusScale;       // 0x015B8E40 2.0
extern const float kNearbyMinAltitude;       // 0x015B8E44 30.0
#pragma intrinsic(sqrt, sin, cos, fabs)
struct Vector3_s0106_0df0 {
    float x, y, z;

    Vector3_s0106_0df0() {}
    Vector3_s0106_0df0(float ax, float ay, float az) : x(ax), y(ay), z(az) {}

    Vector3_s0106_0df0 operator+(const Vector3_s0106_0df0& o) const { return Vector3_s0106_0df0(x + o.x, y + o.y, z + o.z); }
    Vector3_s0106_0df0 operator-(const Vector3_s0106_0df0& o) const { return Vector3_s0106_0df0(x - o.x, y - o.y, z - o.z); }
    Vector3_s0106_0df0 operator-() const { return Vector3_s0106_0df0(-x, -y, -z); }
    Vector3_s0106_0df0 operator*(float s) const { return Vector3_s0106_0df0(x * s, y * s, z * s); }
    Vector3_s0106_0df0& operator+=(const Vector3_s0106_0df0& o) { x += o.x; y += o.y; z += o.z; return *this; }

    float Dot(const Vector3_s0106_0df0& o) const { return x * o.x + y * o.y + z * o.z; }
    float SquaredLength() const { return x * x + y * y + z * z; }
    __forceinline float Length() const { return (float)sqrt(x * x + y * y + z * z); }
    // v / |v| (no epsilon)
    __forceinline Vector3_s0106_0df0 Normalized() const { float inv = 1.0f / (float)sqrt(x * x + y * y + z * z); return Vector3_s0106_0df0(x * inv, y * inv, z * inv); }
    // v / sqrt(|v|^2 + 1e-8)
    __forceinline Vector3_s0106_0df0 SafeNormalized() const { float inv = 1.0f / (float)sqrt(x * x + y * y + z * z + 1e-08f); return Vector3_s0106_0df0(x * inv, y * inv, z * inv); }
    Vector3_s0106_0df0 Cross(const Vector3_s0106_0df0& o) const { return Vector3_s0106_0df0(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x); }

    static const Vector3_s0106_0df0 ZERO;     // 0x016E2114
};
struct Vector2 {
    float x, y;
    Vector2(float ax, float ay) : x(ax), y(ay) {}
};
struct Quaternion_s0106_0df0 {
    float x, y, z, w;

    Quaternion_s0106_0df0() {}
    Quaternion_s0106_0df0(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}

    // rotation of `angle` radians about a unit axis (no normalization)
    static Quaternion_s0106_0df0 AxisAngle(const Vector3_s0106_0df0& axis, float angle)
    {
        float s = (float)sin(angle * 0.5f);
        float c = (float)cos(angle * 0.5f);
        return Quaternion_s0106_0df0(axis.x * s, axis.y * s, axis.z * s, c);
    }
    Quaternion_s0106_0df0 Normalized() const
    {
        float inv = 1.0f / (float)sqrt(x * x + y * y + z * z + w * w);
        return Quaternion_s0106_0df0(x * inv, y * inv, z * inv, w * inv);
    }
    // *this = *this * q (Hamilton product, inline)
    Quaternion_s0106_0df0& operator*=(const Quaternion_s0106_0df0& q)
    {
        float nx = w * q.x + q.w * x + (y * q.z - z * q.y);
        float ny = w * q.y + q.w * y + (z * q.x - x * q.z);
        float nz = w * q.z + q.w * z + (x * q.y - y * q.x);
        float nw = q.w * w - (x * q.x + y * q.y + z * q.z);
        x = nx; y = ny; z = nz; w = nw;
        return *this;
    }
};
Quaternion_s0106_0df0 operator*(const Quaternion_s0106_0df0& a, const Quaternion_s0106_0df0& b);                    // 0x007DCB00
Vector3_s0106_0df0    RotateVector(const Vector3_s0106_0df0& v, const Quaternion_s0106_0df0& q);                     // 0x0059AED0
Vector3_s0106_0df0    Normalize(const Vector3_s0106_0df0& v);                                             // 0x00436CE0
Quaternion_s0106_0df0 Normalize(const Quaternion_s0106_0df0& q);                                          // 0x00799320
Quaternion_s0106_0df0 Slerp(const Quaternion_s0106_0df0& from, const Quaternion_s0106_0df0& to, float t);            // 0x005B26F0
template <typename T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
template <typename T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
inline float Clamp(float v, float lo, float hi)
{
    _mm_store_ss(&v, _mm_min_ss(_mm_max_ss(_mm_load_ss(&v), _mm_load_ss(&lo)), _mm_load_ss(&hi)));
    return v;
}
extern const Vector3_s0106_0df0 kXAxis;                 // 0x015B8D9C (1,0,0)
extern const Vector3_s0106_0df0 kYAxis;                 // 0x015B8DA8 (0,1,0)
static const float kDegToRad = 0.017453292f;
namespace SP {
Quaternion_s0106_0df0 QuaternionFromFacingAndUp(const Vector3_s0106_0df0& facing, const Vector3_s0106_0df0& up);    // 0x0069B600
}
namespace SP {
class cGonzagoTimer_s0106_0df0 {                              // 0x20 bytes
public:
    bool             IsRunning();                  // 0x00FEBA90
    unsigned __int64 GetElapsedTime();             // 0x00BC3190 (ms)
    void             Stop();                       // 0x00BC3110
    void             Restart();                    // 0x00BC3130
    uint32_t pad[8];
};
}
namespace SP {
class cUFOKinestheticsTuning_s0106_0df0 {
public:
    static cUFOKinestheticsTuning_s0106_0df0* Get();          // 0x00C37360 (global 0x0168DF68)
    float GetMinAltitude();                        // 0x00FB7BA0 (+0x0C)
    float GetBrakeAcceleration();                  // 0x00C37440 (+0xB0)
    float GetDescendFactor();                      // 0x00C37450 (+0xBC)
    float GetAscendFactor();                       // 0x00C37460 (+0xC0)
    float GetRotationRate();                       // 0x00C37490 (+0xD0)
    float GetNoseTiltFactor();                     // 0x00C374A0 (+0xD4)
    float GetNoseTiltRate();                       // 0x007DBD40 (+0xD8)
    float GetMaxNoseTilt();                        // 0x00F19170 (+0xDC) degrees
    float GetVerticalTiltFactor();                 // 0x00C374C0 (+0xE0)
    float GetMaxVerticalTilt();                    // 0x00C374B0 (+0xE4) degrees
    float GetBankTiltFactor();                     // 0x00C374D0 (+0xE8)
    float GetBankTiltRate();                       // 0x00C374E0 (+0xEC)
    float GetMaxBankTilt();                        // 0x00C374F0 (+0xF0) degrees

    uint32_t pad00[0x17C / 4];
    float mMaxDamageSpeed;                         // +0x17C
    float mDamageVelocityDecayTime;                // +0x180
};
}
namespace SP {
class cSpatialObject_s0106_0df0 {                             // cLocomotiveObject's primary base
public:
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
    virtual const Vector3_s0106_0df0& GetPosition();          // slot 11 (+0x2C)
virtual void v12();
virtual void v13();
    virtual void SetPosition(const Vector3_s0106_0df0& pos);  // slot 14 (+0x38)
};
}
namespace SP {
class cNounBounds {                                // returned by cGameData slot 27
public:
    uint32_t pad00[0x25C / 4];
    float mRadius;                                 // +0x25C
};
}
namespace SP {
class cGameDataBase {
public:
virtual void g00();
virtual void g01();
virtual void g02();
virtual void g03();
virtual void g04();
virtual void g05();
virtual void g06();
virtual void g07();
virtual void g08();
virtual void g09();
virtual void g10();
virtual void g11();
virtual void g12();
virtual void g13();
virtual void g14();
virtual void g15();
virtual void g16();
virtual void g17();
virtual void g18();
virtual void g19();
virtual void g20();
virtual void g21();
virtual void g22();
virtual void g23();
virtual void g24();
virtual void g25();
virtual void g26();
    virtual cNounBounds* GetBounds();              // slot 27 (+0x6C)
};
}
namespace SP {
class cNearbyNounPad : public cGameDataBase { public: uint32_t pad04[(0x120 - 4) / 4]; };
}
namespace SP {
class cNearbyNoun : public cNearbyNounPad, public cSpatialObject_s0106_0df0 {};
}
namespace SP {
class cGameDataUFOPad : public cGameDataBase { public: uint32_t pad04[(0x34 - 4) / 4]; };
}
namespace SP {
class cGameDataUFO : public cGameDataUFOPad, public cSpatialObject_s0106_0df0 {
public:
    float GetMaxSpeed();                           // 0x00C38900
    float GetAcceleration();                       // 0x00C38840

    uint32_t pad038[(0x5EC - 0x38) / 4];
    float         mCurrentBankAmount;              // +0x5EC
    float         mCurrentNoseTilt;                // +0x5F0
    Vector3_s0106_0df0       mLastTangentialVelocity;         // +0x5F4
    float         field_600;                       // +0x600
    float         mKeyboardRotation;               // +0x604
    uint32_t      field_608;                       // +0x608
    Vector3_s0106_0df0       mOffsetDueToDamage;              // +0x60C
    Vector3_s0106_0df0       mDamageVelocity;                 // +0x618
    bool          mRotateTowardsDestination;       // +0x624
    uint8_t       pad625[3];
    cGonzagoTimer_s0106_0df0 mMovementTimer;                  // +0x628
    cGonzagoTimer_s0106_0df0 mHoverTimer;                     // +0x648
    cGonzagoTimer_s0106_0df0 mCollisionTimer;                 // +0x668
    bool          mHittingTheBrakes;               // +0x688
    bool          mBackingUp;                      // +0x689
    uint8_t       pad68a[2];
    uint32_t      mNPCFollowUFO;                   // +0x68C
    bool          mIgnoreAvoidance;                // +0x690
    bool          mIgnoreLocomotion;               // +0x691
    uint8_t       pad692[2];
    uint32_t      pad694[(0x714 - 0x694) / 4];
    int           mUFOType;                        // +0x714
    Vector3_s0106_0df0       mNextPosition;                   // +0x718
    Vector3_s0106_0df0       mNextVelocity;                   // +0x724
    Quaternion_s0106_0df0    mNextOrientation;                // +0x730
    Vector3_s0106_0df0       mOffsetFromPosition;             // +0x740
    bool          mAtDestination;                  // +0x74C
    uint8_t       pad74d[3];
    Vector3_s0106_0df0       mDestination;                    // +0x750
    uint32_t      mDestinationPlanet;              // +0x75C
    uint32_t      mPreviousPlanet;                 // +0x760
    uint32_t      field_764;                       // +0x764
    float         mZoomAltitude;                   // +0x768
};
}
namespace SP {
struct tGameDataVector_s0106_0df0 {
    void*         vtbl;
    cNearbyNoun** mpBegin;                         // +0x04
    cNearbyNoun** mpEnd;                           // +0x08
};
}
namespace SP {
class cGameNounManager_s0106_0df0 {
public:
    tGameDataVector_s0106_0df0* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);  // 0x00B21340
};
}
namespace SP {
class cAvatar {
public:
    void UpdateUFOLocomotion(cGameDataUFO* ufo, float dt);  // 0x00FF6520
};
}
namespace SP {
class cSpaceGame {
public:
    cAvatar* GetAvatar();                          // 0x00B1FDB0
};
}
namespace SP {
class cUFOSimulator {
public:
    cGameDataUFO* GetPlayerUFO();                  // 0x00A1AD60 (+0x40)
    uint8_t pad00[0x55];
    bool    mbMouseSteering;                       // +0x55
};
}
namespace SP {
class cPlanetModel_s0106_0df0 {
public:
    Quaternion_s0106_0df0 BuildSurfaceOrientation(const Vector3_s0106_0df0& pos, const Vector3_s0106_0df0& forward);  // 0x00B7F250
};
}
namespace SP {
class cPlanetCamera {                              // QueryInterface(0x303154CD) result
public:
    float GetUFOEscapeAltitude();                  // 0x01017240
    uint32_t pad00[0x94 / 4];
    Vector3_s0106_0df0 mFacing;                               // +0x94
};
}
namespace SP {
class cCameraInterface {
public:
virtual void c00();
virtual void c01();
virtual void c02();
    virtual cPlanetCamera* QueryCamera(uint32_t id);   // slot 3 (+0x0C)
};
}
namespace SP {
class cCameraManager_s0106_0df0 {
public:
virtual void m00();
virtual void m01();
virtual void m02();
virtual void m03();
virtual void m04();
virtual void m05();
virtual void m06();
virtual void m07();
virtual void m08();
virtual void m09();
virtual void m10();
virtual void m11();
virtual void m12();
virtual void m13();
    virtual cCameraInterface* GetActiveCamera();   // slot 14 (+0x38)
};
}
namespace SP {
class cApp {
public:
virtual void a00();
virtual void a01();
virtual void a02();
virtual void a03();
virtual void a04();
virtual void a05();
virtual void a06();
virtual void a07();
virtual void a08();
virtual void a09();
virtual void a10();
virtual void a11();
virtual void a12();
virtual void a13();
virtual void a14();
virtual void a15();
virtual void a16();
virtual void a17();
virtual void a18();
virtual void a19();
    virtual cCameraManager_s0106_0df0* GetCameraManager();    // slot 20 (+0x50)
};
}
namespace SP {
class cGameTimeManager { public: uint8_t pad00[0x48]; uint8_t mFlags; };   // bit 0: paused
}
namespace SP {
struct cGameModeState   { uint32_t pad00[0x2C / 4]; int mState; };
}
namespace SP {
cApp*              App();                          // 0x0067DD10
}
namespace SP {
cGameNounManager_s0106_0df0*  NounManager();                  // 0x00B3D300
}
namespace SP {
cGameTimeManager*  GameTimeManager();              // 0x00B3D380
}
namespace SP {
cGameModeState*    GameModeState();                // 0x00B3D4D0
}
namespace SP {
cPlanetModel_s0106_0df0*      PlanetModel();                  // 0x00B3D350
}
namespace SP {
int                GetCurrentGameMode();           // 0x00B5B800
}
namespace SP {
cSpaceGame*        SpaceGameGet();                 // 0x01002BD0
}
namespace SP {
cUFOSimulator*     GetUFOSimulator_s0106_0df0();              // 0x00FFBE50
}
namespace SP {
void  GameDataTypeFn0();                           // 0x00CD7D10
}
namespace SP {
void  GameDataTypeFn1();                           // 0x00D3D420
}
namespace SP {
void  GameDataTypeFn2();                           // 0x00ACDFF0
}
namespace SP {
void  GameDataTypeFn3();                           // 0x00B1E500
}
namespace SP {
extern uint32_t kNearbyNounTypeData;               // 0x018C43E8
}
namespace SP {
void SpringToTarget(Vector3_s0106_0df0* pos, Vector3_s0106_0df0* vel, const Vector3_s0106_0df0* target, const Vector3_s0106_0df0* targetVel,
                    const Vector2* params, float accel, float maxSpeed, float dtMs);       // 0x01042AA0
}
namespace SP {
void SeekTarget(Vector3_s0106_0df0* pos, Vector3_s0106_0df0* vel, const Vector3_s0106_0df0* target,
                float accel, float speed, float dtMs);                                     // 0x010426A0
}
namespace SP {
struct cLocomotionContext {
    uint32_t        pad00[5];
    cSpatialObject_s0106_0df0* mpObject;                      // +0x14 (the UFO's cLocomotiveObject base)
};
}
namespace SP {
class cUFOLocomotion_s0106_0df0 {
public:
    void UpdatePlanetLocomotion(cLocomotionContext* pContext, unsigned int deltaTime);

    void ClampAltitude(cGameDataUFO* ufo, Vector3_s0106_0df0* pos, float minAltitude);  // 0x0105C7E0
    void UpdateAltitude(cGameDataUFO* ufo);                                  // 0x0105C8D0
    void ResolvePlanetaryCollisions(cGameDataUFO* ufo, float dt);            // 0x01060150
    Vector3_s0106_0df0 GetTargetPosition(cGameDataUFO* ufo);                            // 0x0105FBC0
    static void BeginLeavePlanet(cGameDataUFO* ufo, float t, unsigned int deltaTime);  // 0x0105F760

    uint32_t pad[4];
};
}
namespace SP {
static __forceinline cPlanetCamera* GetPlanetCamera()
{
    cCameraInterface* pCamera = App()->GetCameraManager()->GetActiveCamera();
    if (pCamera == NULL) return NULL;
    return pCamera->QueryCamera(0x303154CD);
}
}
static inline float MinDamageOffsetSq() { return 1.0f / 65536.0f; }
// ---- items of slice s01060df0 end

// @ 0x0105e6d0
void __stdcall FUN_0105e6d0(cSPSimulatorSpaceGame* sim, UFOState* ufo, Vector3* target, float radiusScale, Vector3* outPosition, float* outRadius)
{
    float bestHit = kHitMiss;
    Vector3* ufoPosition = ufo->mSpatial.GetPosition();

    float dx = target->x - ufoPosition->x;
    float dy = target->y - ufoPosition->y;
    float dz = target->z - ufoPosition->z;
    float invLength = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz));
    Vector3 dir;
    dir.x = dx * invLength;
    dir.y = dy * invLength;
    dir.z = dz * invLength;

    cSPSimulatorSpaceGame* context = GetUFOSimulator();
    PlayerInventory* playerState = context->GetPlayerInventory();
    bool isPlayerUFO = ((void*)ufo == (void*)playerState);
    PlayerInventory* inventory = sim->GetPlayerInventory();

    if (sim->IsGalaxyView()) {
        BodyRecord* record = inventory->mpStarRecord;
        Vector3* bodyPosition = &record->mPosition;
        float radius = GetStarRadius(sim->mCurrentStarType) * radiusScale;
        float hitTime = 0.0f;

        dx = ufoPosition->x - bodyPosition->x;
        dy = ufoPosition->y - bodyPosition->y;
        dz = ufoPosition->z - bodyPosition->z;
        if (dx * dx + (dy * dy + dz * dz) < radius * radius ||
            IntersectRaySphere(ufoPosition, &dir, bodyPosition, radius, &hitTime)) {
            *outPosition = *bodyPosition;
            bestHit = hitTime;
            *outRadius = radius;
        }

        record = inventory->mpPlanetRecord;
        bodyPosition = &record->mPosition;
        radius = GetStarRadius(sim->mCurrentStarType) * radiusScale;
        hitTime = 0.0f;

        dx = ufoPosition->x - bodyPosition->x;
        dy = ufoPosition->y - bodyPosition->y;
        dz = ufoPosition->z - bodyPosition->z;
        if ((dx * dx + (dy * dy + dz * dz) < radius * radius ||
             IntersectRaySphere(ufoPosition, &dir, bodyPosition, radius, &hitTime)) &&
            !(bestHit >= 0.0f && bestHit <= hitTime)) {
            *outPosition = *bodyPosition;
            bestHit = hitTime;
            *outRadius = radius;
        }
    } else {
        float radius = GetStarRadius(sim->GetCurrentStarType()) * radiusScale;
        float hitTime = 0.0f;

        dx = ufoPosition->x - kOrigin.x;
        dy = ufoPosition->y - kOrigin.y;
        dz = ufoPosition->z - kOrigin.z;
        if (dx * dx + (dy * dy + dz * dz) < radius * radius ||
            IntersectRaySphere(ufoPosition, &dir, &kOrigin, radius, &hitTime)) {
            *outPosition = kOrigin;
            bestHit = hitTime;
            *outRadius = radius;
        }
    }

    int count = (int)(inventory->mpObstacleEnd - inventory->mpObstacleBegin);
    for (int i = 0; i < count; ++i) {
        Obstacle* obstacle = inventory->mpObstacleBegin[i];
        if (obstacle->GetKind() == 0)
            continue;
        if (isPlayerUFO && obstacle == GetActivePlanet())
            continue;

        Vector3* obstaclePosition = obstacle->GetPosition();
        int kind = obstacle->GetKind();
        float baseRadius = (kind == 1) ? kRadiusForKindOne : kRadiusForOtherKinds;
        float radius = baseRadius * radiusScale;
        float hitTime = 0.0f;

        dx = ufoPosition->x - obstaclePosition->x;
        dy = ufoPosition->y - obstaclePosition->y;
        dz = ufoPosition->z - obstaclePosition->z;
        if ((dx * dx + (dy * dy + dz * dz) < radius * radius ||
             IntersectRaySphere(ufoPosition, &dir, obstaclePosition, radius, &hitTime)) &&
            (bestHit < 0.0f || hitTime < bestHit)) {
            *outPosition = *obstaclePosition;
            *outRadius = baseRadius;
            bestHit = hitTime;
        }
    }
}

// @ 0x0105eeb0
void __thiscall SP::cUFOLocomotion::AvoidSolarObstacles(cSPSimulatorSpaceGame* sim, UFOState* ufo, Vector3* position)
{
    if (ufo->mIgnoreAvoidance)
        return;

    Vector3 avoidPoint = kAvoidOrigin;
    float avoidRadius = 0.0f;
    FUN_0105e6d0(sim, ufo, position, kAvoidRadiusScale, &avoidPoint, &avoidRadius);
    if (!(avoidRadius > 0.0f))
        return;

    Vector3* ufoPosition = ufo->mSpatial.GetPosition();
    Vector3 target = *position;
    float dx = target.x - ufoPosition->x;
    float dy = target.y - ufoPosition->y;
    float dz = target.z - ufoPosition->z;
    float targetLength = sqrtf(dy * dy + (dz * dz + dx * dx));
    if (!(targetLength > kMinTargetLength))
        return;

    float invLength = 1.0f / targetLength;
    Vector3 toUfo;
    toUfo.x = ufoPosition->x - avoidPoint.x;
    toUfo.y = ufoPosition->y - avoidPoint.y;
    toUfo.z = ufoPosition->z - avoidPoint.z;

    Vector3 dir;
    dir.x = dx * invLength;
    dir.y = dy * invLength;
    dir.z = dz * invLength;

    float limit = avoidRadius * kAvoidRadiusScale;
    float obstacleDistance = sqrtf(toUfo.x * toUfo.x +
                                   (toUfo.y * toUfo.y + toUfo.z * toUfo.z)) *
                             kAvoidDistanceScale;
    if (limit > obstacleDistance)
        limit = obstacleDistance;

    float targetDistance = sqrtf((target.x - avoidPoint.x) * (target.x - avoidPoint.x) +
                                 ((target.y - avoidPoint.y) * (target.y - avoidPoint.y) +
                                  (target.z - avoidPoint.z) * (target.z - avoidPoint.z)));
    if (limit > targetDistance)
        limit = targetDistance;
    if (limit < avoidRadius)
        limit = avoidRadius;

    float hitTime = 0.0f;
    bool hit = (toUfo.x * toUfo.x + (toUfo.y * toUfo.y + toUfo.z * toUfo.z) < limit * limit) ||
               IntersectRaySphere(ufoPosition, &dir, &avoidPoint, limit, &hitTime);
    if (!(hit && hitTime < targetLength))
        return;

    Vector3 closest;
    ClosestPointOnSegment(&closest, &avoidPoint, ufoPosition, &target);

    Vector3 offset;
    offset.x = closest.x - avoidPoint.x;
    offset.y = closest.y - avoidPoint.y;
    offset.z = closest.z - avoidPoint.z;

    normalized_safe(&dir, &offset);

    Vector3 corrected;
    corrected.x = avoidPoint.x + dir.x * limit - ufoPosition->x;
    corrected.y = avoidPoint.y + dir.y * limit - ufoPosition->y;
    corrected.z = avoidPoint.z + dir.z * limit - ufoPosition->z;

    Vector3 normal;
    Vector3_Normalize(&normal, &corrected);

    float distance = sqrtf((target.x - ufoPosition->x) * (target.x - ufoPosition->x) +
                           ((target.y - ufoPosition->y) * (target.y - ufoPosition->y) +
                            (target.z - ufoPosition->z) * (target.z - ufoPosition->z)));
    position->x = ufoPosition->x + normal.x * distance;
    position->y = ufoPosition->y + normal.y * distance;
    position->z = ufoPosition->z + normal.z * distance;
}

// @ 0x0105f2d0
void cUFOLocomotion_s0105_f2d0::UpdateSolarGalaxyLocomotion(cUFOState* pState, int32_t nDeltaMs)
{
    float fDeltaSeconds = (float)(uint32_t)nDeltaMs * 0.001f;

    cUFOShipState* pShip;
    if (pState->mpShipBase == 0)
        pShip = 0;
    else
        pShip = (cUFOShipState*)((char*)pState->mpShipBase - 0x34);

    cSPSimulatorSpaceGame_s0105_f2d0* pSimulator = pState->GetSimulator();
    void* pPlayer = pSimulator->GetPlayerInventory();
    bool bIsPlayer = (pShip == pPlayer);
    cUFOKinestheticsTuning* pTuning = GetKinestheticsTuning();

    cSPVector3_s0105_f2d0 target;
    target.mX = g_fSolarZeroX;
    target.mY = g_fSolarZeroY;
    target.mZ = g_fSolarZeroZ;

    float fAccel = fDeltaSeconds * 5.0f;
    float fOne = 1.0f;
    float* pfSpeedScale = &fAccel;
    if (fOne <= fAccel)
        pfSpeedScale = &fOne;
    float fSpeedScale = *pfSpeedScale;

    int32_t nContext = GetUniverseContext();

    if (nContext == 1) {
        cUniverseContext* pUniverse = GetUniverseContextObject();
        if (!pUniverse->IsPlayerControlled()) {
            cGameContext* pContext = GetGameContext();
            int32_t nMode = pContext->mnGameMode;
            if ((nMode == 1 || nMode == 2) &&
                GetGameContext()->mnModeToken == 0x2f7c7bda)
                return;
            this->UpdateCourse(pState, nDeltaMs);
            return;
        }
        if (pShip->mpSolarWaypoint != 0) {
            cSPVector3_s0105_f2d0* pPos = pShip->mpSolarWaypoint->GetPosition();
            pShip->mSolarDestination.mX = pPos->mX;
            pShip->mSolarDestination.mY = pPos->mY;
            pShip->mSolarDestination.mZ = pPos->mZ;
        }
        target.mX = pShip->mSolarDestination.mX;
        target.mY = pShip->mSolarDestination.mY;
        target.mZ = pShip->mSolarDestination.mZ;
        this->AvoidSolarObstacles(pUniverse, pShip, &target);
    }
    else {
        if (pShip->mpCivData != 0) {
            cSPVector3_s0105_f2d0* pCity = pShip->mpCivData->GetCities();
            pShip->mSolarDestination.mX = pCity->mX;
            pShip->mSolarDestination.mY = pCity->mY;
            pShip->mSolarDestination.mZ = pCity->mZ;
        }
        target.mX = pShip->mSolarDestination.mX;
        target.mY = pShip->mSolarDestination.mY;
        target.mZ = pShip->mSolarDestination.mZ;
    }

    if (pShip->mbSolarArrived) {
        pShip->PopToDestination();
        pShip->mDockState.UpdateDockedParent();
        pShip->mnWarpGroup = 0;
        return;
    }

    float fMaxPlump;
    float fPush;
    if (nContext == 1) {
        fMaxPlump = pTuning->mGalaxyMaxPlump;
        fPush = pTuning->mGalaxyMinPlumpDistance;
    }
    else {
        this->UpdateSolarCourse(pShip, &target);
        float fMultiplier = pTuning->GetGalaxyWarpMultiplier(pShip->mnWarpGroup,
                                                             pShip->mnSolarTarget);
        fMaxPlump = pTuning->mGalaxyMaxPlumpDistance * fMultiplier;
        fPush = pTuning->mBaseUFODamagePush * fMultiplier;
    }

    PhysicsMoveUFO(&pShip->mSolarPosition, &pShip->mSolarVelocity, &target,
                   fMaxPlump, fPush, fDeltaSeconds);

    float fDeltaX = target.mX - pShip->mSolarPosition.mX;
    float fDeltaY = target.mY - pShip->mSolarPosition.mY;
    float fDeltaZ = target.mZ - pShip->mSolarPosition.mZ;
    float fLengthSq = fDeltaX * fDeltaX + fDeltaY * fDeltaY + fDeltaZ * fDeltaZ;
    if (1.5258789e-05f < fLengthSq) {
        float fInvLength = 1.0f / sqrtf(fLengthSq);

        cSPVector3_s0105_f2d0 directionA;
        directionA.mX = fDeltaX * fInvLength;
        directionA.mY = fDeltaY * fInvLength;
        directionA.mZ = fDeltaZ * fInvLength;

        cSPVector3_s0105_f2d0 directionB;
        directionB.mX = fDeltaX * fInvLength;
        directionB.mY = fDeltaY * fInvLength;
        directionB.mZ = fDeltaZ * fInvLength;

        float fAxisDot = directionB.mX * g_vSolarAxisZ.mX
                       + directionB.mY * g_vSolarAxisZ.mY
                       + directionB.mZ * g_vSolarAxisZ.mZ;
        if (fabsf(fAxisDot) < 0.999f) {
            cSPVector4_s0105_f2d0 quat;
            QuaternionFromFacingAndUp(&quat, &directionB, &g_vSolarAxisZ);
            RotateVectorInPlace(&directionA, &quat);
            SlerpHeading(&quat, &pShip->mSolarHeading, &directionA, fSpeedScale);
        }
    }

    float fDistX = pShip->mSolarPosition.mX - target.mX;
    float fDistY = pShip->mSolarPosition.mY - target.mY;
    float fDistZ = pShip->mSolarPosition.mZ - target.mZ;
    float fDistance = sqrtf(fDistX * fDistX + fDistY * fDistY + fDistZ * fDistZ);

    float fArriveThreshold;
    if (nContext == 1)
        fArriveThreshold = g_fSolarArrivePlanet;
    else
        fArriveThreshold = g_fSolarArriveStar;

    if (fDistance < fArriveThreshold) {
        pShip->mbSolarArrived = true;
        pShip->mTimer.Restart();
        if (bIsPlayer) {
            if (nContext == 1)
                pSimulator->OnPlanetMoveDone();
            else if (nContext == 2)
                pSimulator->OnStarMoveDone();
        }
    }

    cUFOView* pView = GetSolarView();
    pView->mpVTable->mpPushBody(pView, &target, 500.0f, 1);
}

// @ 0x0105f760
void UpdateSolarAvoidance(cUFOShipState* pShip, float fAmplitude, int32_t nDeltaMs)
{
    if (!g_bSolarAvoidEnabled) {
        pShip->mSolarPosition.mX = pShip->mSolarDestination.mX;
        pShip->mSolarPosition.mY = pShip->mSolarDestination.mY;
        pShip->mSolarPosition.mZ = pShip->mSolarDestination.mZ;
        return;
    }

    float fSwing = fAmplitude * 1.5f;
    float fTime = (float)pShip->mTimer.GetElapsedTime() * 0.001f;

    cSPVector3_s0105_f2d0 vAxisY;
    RotateVectorByQuaternion(&vAxisY, &g_vSolarAxisY, &pShip->mSolarHeading);
    cSPVector3_s0105_f2d0 vAxisX;
    RotateVectorByQuaternion(&vAxisX, &g_vSolarAxisX, &pShip->mSolarHeading);
    cSPVector3_s0105_f2d0 vAxisZ;
    RotateVectorByQuaternion(&vAxisZ, &g_vSolarAxisZ, &pShip->mSolarHeading);

    float fSinY = sinf(fTime * 0.23f);
    float fSinX = sinf(fTime * 0.61f);
    float fSinZ = sinf(fTime * 1.01f);

    float fOffsetZ = fSinY * (fAmplitude * 0.75f);
    float fOffsetY = fSwing * fSinZ;
    float fOffsetX = fSwing * fSinX;

    pShip->mSolarPosition.mX = pShip->mSolarDestination.mX
                             + vAxisZ.mX * fOffsetZ
                             + vAxisY.mX * fOffsetY
                             + vAxisX.mX * fOffsetX;
    pShip->mSolarPosition.mY = pShip->mSolarDestination.mY
                             + vAxisZ.mY * fOffsetZ
                             + vAxisY.mY * fOffsetY
                             + vAxisX.mY * fOffsetX;
    pShip->mSolarPosition.mZ = pShip->mSolarDestination.mZ
                             + vAxisZ.mZ * fOffsetZ
                             + vAxisY.mZ * fOffsetY
                             + vAxisX.mZ * fOffsetX;

    int32_t nContext = GetUniverseContext();
    if (nContext == 1 || nContext == 2) {
        float fStep = (float)(uint32_t)nDeltaMs * 0.002f;
        float fOne = 1.0f;
        float* pfScale = &fStep;
        if (fOne <= fStep)
            pfScale = &fOne;

        cSPVector3_s0105_f2d0 vFacing;
        RotateVectorByQuaternion(&vFacing, &g_vSolarAxisY, &pShip->mSolarHeading);

        float fPlaneDot = vFacing.mX * g_vSolarAxisZ.mX
                        + vFacing.mY * g_vSolarAxisZ.mY
                        + vFacing.mZ * g_vSolarAxisZ.mZ;

        cSPVector3_s0105_f2d0 vDirection;
        vDirection.mX = vFacing.mX - g_vSolarAxisZ.mX * fPlaneDot;
        vDirection.mY = vFacing.mY - g_vSolarAxisZ.mY * fPlaneDot;
        vDirection.mZ = vFacing.mZ - g_vSolarAxisZ.mZ * fPlaneDot;

        float fLength = sqrtf(vDirection.mX * vDirection.mX
                            + vDirection.mY * vDirection.mY
                            + vDirection.mZ * vDirection.mZ);
        float fInvLength = 1.0f / fLength;
        vDirection.mX *= fInvLength;
        vDirection.mY *= fInvLength;
        vDirection.mZ *= fInvLength;

        cSPVector4_s0105_f2d0 quat;
        QuaternionFromFacingAndUp(&quat, &vDirection, &g_vSolarAxisZ);

        float fQuatLength = sqrtf(quat.mX * quat.mX + quat.mY * quat.mY
                                + quat.mZ * quat.mZ + quat.mW * quat.mW);
        float fInvQuat = 1.0f / fQuatLength;
        quat.mX *= fInvQuat;
        quat.mY *= fInvQuat;
        quat.mZ *= fInvQuat;
        quat.mW *= fInvQuat;

        SlerpHeadingSlow(&vDirection, &pShip->mSolarHeading, &quat, *pfScale);
    }
}

// @ 0x0105fbc0
cSPVector3_s0105_f2d0* __stdcall UpdateSolarBody(cSPVector3_s0105_f2d0* pOut, cUFOShipState* pShip)
{
    pOut->mX = pShip->mSolarDestination.mX;
    pOut->mY = pShip->mSolarDestination.mY;
    pOut->mZ = pShip->mSolarDestination.mZ;

    if (pShip->mnSolarTarget == 0 || pShip->mbSolarActive)
        return pOut;

    float fDistX = pOut->mX - pShip->mSolarPosition.mX;
    float fDistY = pOut->mY - pShip->mSolarPosition.mY;
    float fDistZ = pOut->mZ - pShip->mSolarPosition.mZ;
    float fDistance = sqrtf(fDistX * fDistX + fDistY * fDistY + fDistZ * fDistZ);
    if (fDistance <= 1.0f)
        return pOut;

    // walk every game-data object that shares our parent collection
    void* context = FindGameDataContext();                    // 0x00b3d300
    cGameDataVector* pCollection = FindGameDataVector(context, &g_ufoBodyFilter);

    intptr_t* pIt = pCollection->mpBegin;
    intptr_t* pEnd = pCollection->mpEnd;
    while (pIt != pEnd) {
        cGameDataObject* pOther = (cGameDataObject*)*pIt;
        if (pOther != (cGameDataObject*)pShip) {
            cSPVector3_s0105_f2d0* pOtherPos = pOther->GetCollisionPosition();  // vtable +0x2c

            float fOtherX = pOtherPos->mX - pShip->mSolarPosition.mX;
            float fOtherY = pOtherPos->mY - pShip->mSolarPosition.mY;
            float fOtherZ = pOtherPos->mZ - pShip->mSolarPosition.mZ;
            float fOutX = pOut->mX - pShip->mSolarPosition.mX;
            float fOutY = pOut->mY - pShip->mSolarPosition.mY;
            float fOutZ = pOut->mZ - pShip->mSolarPosition.mZ;
            float fAlong = fOutX * fOtherX + fOutY * fOtherY + fOutZ * fOtherZ;

            if (0.0f < fAlong) {
                cSPVector3_s0105_f2d0 closest;
                ClosestPointOnSegment(&closest, pOtherPos,
                                      &pShip->mSolarPosition, pOut);

                float fPosLength = sqrtf(pShip->mSolarPosition.mX
                                             * pShip->mSolarPosition.mX
                                       + pShip->mSolarPosition.mY
                                             * pShip->mSolarPosition.mY
                                       + pShip->mSolarPosition.mZ
                                             * pShip->mSolarPosition.mZ);
                float fClosestLength = sqrtf(closest.mX * closest.mX
                                           + closest.mY * closest.mY
                                           + closest.mZ * closest.mZ
                                           + 1e-8f);
                float fInvClosest = 1.0f / fClosestLength;

                cSPVector3_s0105_f2d0 vRadial;
                vRadial.mX = closest.mX * fInvClosest * fPosLength - pOtherPos->mX;
                vRadial.mY = closest.mY * fInvClosest * fPosLength - pOtherPos->mY;
                vRadial.mZ = closest.mZ * fInvClosest * fPosLength - pOtherPos->mZ;

                float fRadialLength = sqrtf(vRadial.mX * vRadial.mX
                                          + vRadial.mY * vRadial.mY
                                          + vRadial.mZ * vRadial.mZ);
                if (fRadialLength < g_fSolarBodyRadius) {
                    cSPVector3_s0105_f2d0 vDelta;
                    vDelta.mX = pOut->mX - pOtherPos->mX;
                    vDelta.mY = pOut->mY - pOtherPos->mY;
                    vDelta.mZ = pOut->mZ - pOtherPos->mZ;
                    if (vDelta.mX * vDelta.mX + vDelta.mY * vDelta.mY
                            + vDelta.mZ * vDelta.mZ < 1.5258789e-05f) {
                        vDelta.mX = pOut->mX - pShip->mSolarPosition.mX;
                        vDelta.mY = pOut->mY - pShip->mSolarPosition.mY;
                        vDelta.mZ = pOut->mZ - pShip->mSolarPosition.mZ;
                    }

                    cSPVector3_s0105_f2d0 vDeltaNormalized;
                    NormalizeVectorGuarded(&vDeltaNormalized, &vDelta);

                    float fDot = vRadial.mX * vDeltaNormalized.mX
                               + vRadial.mY * vDeltaNormalized.mY
                               + vRadial.mZ * vDeltaNormalized.mZ;
                    cSPVector3_s0105_f2d0 vTangential;
                    vTangential.mX = vRadial.mX - vDeltaNormalized.mX * fDot;
                    vTangential.mY = vRadial.mY - vDeltaNormalized.mY * fDot;
                    vTangential.mZ = vRadial.mZ - vDeltaNormalized.mZ * fDot;

                    cSPVector3_s0105_f2d0 vOtherNormalized;
                    NormalizeVector(&vOtherNormalized, pOtherPos);

                    float fDot2 = vTangential.mX * vOtherNormalized.mX
                                + vTangential.mY * vOtherNormalized.mY
                                + vTangential.mZ * vOtherNormalized.mZ;
                    cSPVector3_s0105_f2d0 vPlane;
                    vPlane.mX = vTangential.mX - vOtherNormalized.mX * fDot2;
                    vPlane.mY = vTangential.mY - vOtherNormalized.mY * fDot2;
                    vPlane.mZ = vTangential.mZ - vOtherNormalized.mZ * fDot2;

                    cSPVector3_s0105_f2d0 vPlaneNormalized;
                    NormalizeVectorGuarded(&vPlaneNormalized, &vPlane);

                    cSPVector3_s0105_f2d0 vPush;
                    vPush.mX = vPlaneNormalized.mX * g_fSolarBodyRadius
                             + pOtherPos->mX - pShip->mSolarPosition.mX;
                    vPush.mY = vPlaneNormalized.mY * g_fSolarBodyRadius
                             + pOtherPos->mY - pShip->mSolarPosition.mY;
                    vPush.mZ = vPlaneNormalized.mZ * g_fSolarBodyRadius
                             + pOtherPos->mZ - pShip->mSolarPosition.mZ;

                    cSPVector3_s0105_f2d0 vPushNormalized;
                    NormalizeVectorGuarded(&vPushNormalized, &vPush);

                    cSPVector3_s0105_f2d0 target;
                    target.mX = vPushNormalized.mX * fDistance
                              + pShip->mSolarPosition.mX;
                    target.mY = vPushNormalized.mY * fDistance
                              + pShip->mSolarPosition.mY;
                    target.mZ = vPushNormalized.mZ * fDistance
                              + pShip->mSolarPosition.mZ;

                    float fOutLength = sqrtf(pOut->mX * pOut->mX
                                           + pOut->mY * pOut->mY
                                           + pOut->mZ * pOut->mZ);

                    cSPVector3_s0105_f2d0 vTargetNormalized;
                    NormalizeVector(&vTargetNormalized, &target);

                    pOut->mX = vTargetNormalized.mX * fOutLength;
                    pOut->mY = vTargetNormalized.mY * fOutLength;
                    pOut->mZ = vTargetNormalized.mZ * fOutLength;
                }
            }
        }
        ++pIt;
    }

    return pOut;
}

// @ 0x01060df0
void SP::cUFOLocomotion_s0106_0df0::UpdatePlanetLocomotion(SP::cLocomotionContext* pContext, unsigned int deltaTime)
{
    SP::cUFOKinestheticsTuning_s0106_0df0* pTuning = SP::cUFOKinestheticsTuning_s0106_0df0::Get();
    SP::cGameDataUFO* ufo = static_cast<SP::cGameDataUFO*>(pContext->mpObject);

    if (ufo->mIgnoreLocomotion)
        return;

    float minAltitude = pTuning->GetMinAltitude();

    // A nearby noun (within twice its radius) raises the minimum altitude toward 30.
    if (ufo->mUFOType == 0 && minAltitude < kNearbyMinAltitude) {
        float minDistSq = 3.402823466e+38F;
        SP::cNearbyNoun* pNearest = NULL;
        SP::tGameDataVector_s0106_0df0* pVec = SP::NounManager()->GetGameDataVector(
            (void*)SP::GameDataTypeFn0, (void*)SP::GameDataTypeFn1, (void*)SP::GameDataTypeFn2,
            (void*)SP::GameDataTypeFn3, &SP::kNearbyNounTypeData);
        for (SP::cNearbyNoun** it = pVec->mpBegin; it != pVec->mpEnd; ++it) {
            SP::cNearbyNoun* pNoun = *it;
            const Vector3_s0106_0df0& myPos = ufo->GetPosition();
            const Vector3_s0106_0df0& pos = pNoun->GetPosition();
            float distSq = (pos - myPos).SquaredLength();
            if (distSq < minDistSq) {
                minDistSq = distSq;
                pNearest = pNoun;
            }
        }
        if (pNearest != NULL) {
            const Vector3_s0106_0df0& myPos = ufo->GetPosition();
            const Vector3_s0106_0df0& pos = pNearest->GetPosition();
            float dist = (pos - myPos).Length();
            float radius = pNearest->GetBounds()->mRadius;
            if (kNearbyRadiusScale * radius > dist) {
                float t = (kNearbyRadiusScale - dist / radius) / (kNearbyRadiusScale - 1.0f);
                t = Clamp(t, 0.0f, 1.0f);
                minAltitude = (kNearbyMinAltitude - minAltitude) * t + minAltitude;
            }
        }
    }

    float maxSpeed = ufo->GetMaxSpeed();
    float accel = ufo->GetAcceleration();

    // Paused game (outside game-mode states 1 and 2): only settle vertically, then return.
    if ((SP::GameTimeManager()->mFlags & 1) != 0) {
        int state = SP::GameModeState()->mState;
        if (state != 1 && state != 2) {
            Vector3_s0106_0df0 oldPos = ufo->mNextPosition;
            ClampAltitude(ufo, &ufo->mDestination, minAltitude);

            Vector2 params(0.3f, 0.0f);
            if (ufo->mNextPosition.SquaredLength() > ufo->mDestination.SquaredLength())
                params.x = pTuning->GetDescendFactor();
            else
                params.x = pTuning->GetAscendFactor();

            Vector3_s0106_0df0 up = ufo->mNextPosition.Normalized();
            Vector3_s0106_0df0 vel = ufo->mNextVelocity + ufo->mDamageVelocity;
            float vertical = (float)fabs(vel.Dot(up));
            Vector3_s0106_0df0 verticalVel = vel * vertical;
            Vector3_s0106_0df0 lateralVel = vel - verticalVel;

            SP::SpringToTarget(&ufo->mNextPosition, &verticalVel, &ufo->mDestination, &Vector3_s0106_0df0::ZERO,
                           &params, accel, maxSpeed, (float)deltaTime);
            ufo->mNextVelocity = (lateralVel + verticalVel) - ufo->mDamageVelocity;
            UpdateAltitude(ufo);

            // keep the horizontal position, take only the new altitude
            float altitude = ufo->mNextPosition.Length();
            ufo->mNextPosition = oldPos.Normalized() * altitude;
            ufo->SetPosition(ufo->mNextPosition);
            return;
        }
    }

    Vector3_s0106_0df0 oldPos = ufo->mNextPosition;
    Vector3_s0106_0df0 target = ufo->mNextVelocity;

    if (ufo->mHittingTheBrakes) {
        float speedSq = target.SquaredLength();
        if (speedSq > 1.5258789e-05f) {
            float speed = ufo->GetMaxSpeed();
            float brake = pTuning->GetBrakeAcceleration() * speed;
            float stopDistance = speedSq / (brake + brake);
            ufo->mDestination = target.SafeNormalized() * stopDistance + oldPos;
            ClampAltitude(ufo, &ufo->mDestination, minAltitude);
        }
        ufo->mHittingTheBrakes = false;
    }

    if (!ufo->mAtDestination) {
        ClampAltitude(ufo, &ufo->mNextPosition, minAltitude);

        bool bRecentCollision = false;
        if (ufo->mCollisionTimer.IsRunning()) {
            bRecentCollision = true;
            if (!((float)ufo->mCollisionTimer.GetElapsedTime() < kRecentCollisionMs))
                bRecentCollision = false;
        }

        Vector2 params(0.3f, 1.0f);
        if (ufo->mNextPosition.SquaredLength() > ufo->mDestination.SquaredLength())
            params.x = pTuning->GetDescendFactor();
        else
            params.x = pTuning->GetAscendFactor();

        float maxDamageSpeed = pTuning->mMaxDamageSpeed;
        if (ufo->mDamageVelocity.Length() > maxDamageSpeed)
            ufo->mDamageVelocity = ufo->mDamageVelocity.Normalized() * maxDamageSpeed;

        Vector3_s0106_0df0 desiredVel = ufo->mDamageVelocity + ufo->mNextVelocity;
        target = GetTargetPosition(ufo);

        float seekSpeed;
        bool bSeek;
        if (bRecentCollision) {
            seekSpeed = maxSpeed * 0.2f;
            bSeek = true;
        } else {
            bSeek = false;
            if (ufo->mUFOType != 0) {
                Vector3_s0106_0df0 targetDir = Normalize(target);
                Vector3_s0106_0df0 posDir = Normalize(ufo->mNextPosition);
                if ((posDir - targetDir).SquaredLength() <= 0.25f &&
                    SP::GetCurrentGameMode() != 0x1654C01 && SP::GetCurrentGameMode() != 0x1654C02) {
                    seekSpeed = maxSpeed;
                    bSeek = true;
                }
            }
        }

        float dtMs = (float)deltaTime;
        if (bSeek)
            SP::SeekTarget(&ufo->mNextPosition, &desiredVel, &target, accel, seekSpeed, dtMs);
        else
            SP::SpringToTarget(&ufo->mNextPosition, &desiredVel, &target, &Vector3_s0106_0df0::ZERO,
                           &params, accel, maxSpeed, dtMs);

        ufo->mNextVelocity = desiredVel - ufo->mDamageVelocity;
        UpdateAltitude(ufo);

        // damage knock-back decays linearly
        float decay = dtMs / pTuning->mDamageVelocityDecayTime;
        float damageSpeed = ufo->mDamageVelocity.Length();
        if (decay > damageSpeed)
            decay = damageSpeed;
        if (damageSpeed > 0.0f)
            ufo->mDamageVelocity = ufo->mDamageVelocity.Normalized() * (damageSpeed - decay);
        else
            ufo->mDamageVelocity = Vector3_s0106_0df0::ZERO;

        if ((ufo->mNextPosition - ufo->mDestination).SquaredLength() < kArriveDistanceSq) {
            ufo->mDestination = ufo->mNextPosition;
            ufo->mAtDestination = true;
            ufo->mNextVelocity = Vector3_s0106_0df0::ZERO;
            ufo->mRotateTowardsDestination = true;
            ufo->mHoverTimer.Restart();
        }
    } else if ((float)fabs(ufo->mZoomAltitude - ufo->mDestination.Length()) <= kZoomAltitudeTolerance) {
        ufo->mNextPosition = ufo->mDestination;
        ufo->mNextVelocity = Vector3_s0106_0df0::ZERO;
        ufo->mLastTangentialVelocity = Vector3_s0106_0df0::ZERO;
        SP::cPlanetCamera* pCamera = SP::GetPlanetCamera();
        if (pCamera != NULL && pCamera->GetUFOEscapeAltitude() > ufo->mZoomAltitude)
            BeginLeavePlanet(ufo, 1.0f, deltaTime);
        UpdateAltitude(ufo);
    } else {
        // zoom altitude changed: leave the hover state and snap to the destination
        ufo->mAtDestination = false;
        ufo->mHoverTimer.Stop();
        ufo->mNextPosition = ufo->mDestination;
        ufo->SetPosition(ufo->mNextPosition);
        UpdateAltitude(ufo);
    }

    float dt = (float)deltaTime * 0.001f;
    if (!ufo->mAtDestination)
        ResolvePlanetaryCollisions(ufo, dt);

    SP::cSpaceGame* pSpaceGame = SP::SpaceGameGet();
    if (pSpaceGame != NULL) {
        SP::cAvatar* pAvatar = pSpaceGame->GetAvatar();
        if (pAvatar != NULL)
            pAvatar->UpdateUFOLocomotion(ufo, dt);
    }

    // ---- orientation
    Vector3_s0106_0df0 up = ufo->mNextPosition.Normalized();

    Vector3_s0106_0df0 tangentVel = ufo->mNextVelocity - up * up.Dot(ufo->mNextVelocity);
    float tangentSq = tangentVel.SquaredLength();
    if (tangentSq > accel * 0.01f)
        ufo->mLastTangentialVelocity = tangentVel * (1.0f / (float)sqrt(tangentSq));
    Vector3_s0106_0df0 lastTangent = ufo->mLastTangentialVelocity - up * up.Dot(ufo->mLastTangentialVelocity);
    ufo->mLastTangentialVelocity = lastTangent.SafeNormalized();

    Vector3_s0106_0df0 forward = RotateVector(kYAxis, ufo->mNextOrientation);
    ufo->mNextOrientation = SP::PlanetModel()->BuildSurfaceOrientation(ufo->mNextPosition, forward);

    SP::cUFOSimulator* pSim = SP::GetUFOSimulator_s0106_0df0();
    bool bIsPlayer = (pSim != NULL && ufo == pSim->GetPlayerUFO()) ? true : false;

    Vector3_s0106_0df0 facing = forward - up * forward.Dot(up);
    Quaternion_s0106_0df0 targetOrientation;
    bool bTurn = false;

    if (bIsPlayer && ufo->mKeyboardRotation != 0.0f) {
        // keyboard rotation about the local up axis
        float rotation = Clamp(ufo->mKeyboardRotation, -1.0f, 1.0f) * 0.5f;
        ufo->mKeyboardRotation = 0.0f;
        const Vector3_s0106_0df0* pAxisSource = &ufo->mNextPosition;
        if (ufo->mAtDestination && (SP::GameTimeManager()->mFlags & 1) == 0)
            pAxisSource = &ufo->mDestination;
        Vector3_s0106_0df0 axis = pAxisSource->SafeNormalized();
        Quaternion_s0106_0df0 spin = Quaternion_s0106_0df0::AxisAngle(axis, rotation).Normalized();
        facing = RotateVector(forward, spin);
        targetOrientation = Normalize(SP::QuaternionFromFacingAndUp(facing, up));
        bTurn = true;
    } else if (bIsPlayer && pSim->mbMouseSteering && !ufo->mAtDestination) {
        // mouse steering: face where the planet camera looks
        SP::cPlanetCamera* pCamera = SP::GetPlanetCamera();
        if (pCamera != NULL) {
            facing = pCamera->mFacing;
            targetOrientation = Normalize(SP::QuaternionFromFacingAndUp(facing, up));
            bTurn = true;
        }
    } else if (ufo->mRotateTowardsDestination && !ufo->mAtDestination &&
               ufo->mDamageVelocity.SquaredLength() < 1.5258789e-05f) {
        // turn toward the destination (projected onto the tangent plane)
        Vector3_s0106_0df0 toDest = ufo->mDestination - oldPos;
        toDest = toDest - up * toDest.Dot(up);
        if (ufo->mBackingUp)
            toDest = -toDest;
        float dist = toDest.Length();
        if (dist > 5.0f)
            facing = toDest * (1.0f / dist);
        targetOrientation = Normalize(SP::QuaternionFromFacingAndUp(facing, up));
        bTurn = true;
    }

    if (bTurn) {
        float t = Min(pTuning->GetRotationRate() * dt, 1.0f);
        ufo->mNextOrientation = Slerp(ufo->mNextOrientation, targetOrientation, t);
    }

    // ---- nose tilt from forward speed and climb rate
    if (ufo->mUFOType != 1) {
        float noseFactor = pTuning->GetNoseTiltFactor();
        float maxNose = pTuning->GetMaxNoseTilt() * kDegToRad;
        float verticalFactor = pTuning->GetVerticalTiltFactor();
        float maxVertical = pTuning->GetMaxVerticalTilt() * kDegToRad;
        float maxTilt = Max(maxNose, maxVertical);
        float rate = pTuning->GetNoseTiltRate();

        Vector3_s0106_0df0 nose = RotateVector(kYAxis, ufo->mNextOrientation);
        float forwardAmount = Clamp(ufo->mNextVelocity.Dot(nose) * noseFactor, -1.0f, 1.0f);
        float invDt = 1.0f / (dt + 0.001f);
        Vector3_s0106_0df0 climbVel = (ufo->mNextPosition - oldPos) * invDt;
        float climbAmount = Clamp(climbVel.Dot(up) * verticalFactor, -1.0f, 1.0f);

        float tilt = Clamp(maxNose * forwardAmount - maxVertical * climbAmount, -maxTilt, maxTilt);
        float blend = Min(rate * dt, 1.0f);
        ufo->mCurrentNoseTilt = (tilt - ufo->mCurrentNoseTilt) * blend + ufo->mCurrentNoseTilt;
        ufo->mNextOrientation *= Quaternion_s0106_0df0::AxisAngle(kXAxis, -ufo->mCurrentNoseTilt);
    }

    // ---- bank from sideways turning
    if (ufo->mUFOType != 1) {
        float bankFactor = pTuning->GetBankTiltFactor();
        float bankRate = pTuning->GetBankTiltRate();
        float maxBank = pTuning->GetMaxBankTilt() * kDegToRad;

        Vector3_s0106_0df0 right = RotateVector(kXAxis, ufo->mNextOrientation);
        float bank = right.Dot(facing) * bankFactor;
        float blend = Min(bankRate * dt, 1.0f);
        ufo->mCurrentBankAmount = (bank - ufo->mCurrentBankAmount) * blend + ufo->mCurrentBankAmount;
        ufo->mNextOrientation *= Quaternion_s0106_0df0::AxisAngle(kYAxis, maxBank * ufo->mCurrentBankAmount);
    }

    // ---- damage wobble: the offset decays and tilts the hull away from it
    float decayBlend = Min(dt * kDamageOffsetDecayRate, 1.0f);
    ufo->mOffsetDueToDamage += (Vector3_s0106_0df0::ZERO - ufo->mOffsetDueToDamage) * decayBlend;

    static const float sMinOffsetSq = MinDamageOffsetSq();
    if (ufo->mOffsetDueToDamage.SquaredLength() > sMinOffsetSq) {
        static const float sMaxWobbleAngle = kPI * 0.125f;
        float amount = Min(ufo->mOffsetDueToDamage.Length() / kDamageOffsetMaxLength, 1.0f);
        Vector3_s0106_0df0 axis = ufo->mOffsetDueToDamage.Cross(ufo->mNextPosition);
        float axisLength = axis.Length();
        if (axisLength > 1.5258789e-05f) {
            Quaternion_s0106_0df0 wobble = Quaternion_s0106_0df0::AxisAngle(axis * (1.0f / axisLength), amount * sMaxWobbleAngle);
            ufo->mNextOrientation = wobble * ufo->mNextOrientation;
        }
    }
}
