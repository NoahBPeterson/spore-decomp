// Slice s0105e6d0: Spore's UFO solar-obstacle avoidance.  The three retail
// routines find the nearest star/planet/ship that intersects the UFO's desired
// travel ray, then steer the desired direction around it.  Reconstructed from
// the retail disassembly; the layout and field names below are the retail ones.

#include <math.h>
#include <stddef.h>

typedef unsigned char uchar;

// ---- small vector/quaternion helpers ----------------------------------------------------------

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

// The engine's vector/matrix helpers are free functions with these signatures.
extern Vector3* __cdecl TransformVector(Vector3* out, const Vector3* v, const Quaternion* q);
extern Vector3* __cdecl OrthogonalVector(Vector3* out, const Vector3* v);
extern Vector3* __cdecl RotateTowards(Vector3* out, const Vector3* from, const Vector3* to,
                                      float maxAngle);
extern Quaternion* __cdecl QuaternionFromFacingAndUp(Quaternion* out, const Vector3* facing,
                                                    const Vector3* up);
extern Vector3* __cdecl Vector3_Normalize(Vector3* out, const Vector3* v);
extern Vector3* __cdecl normalized_safe(Vector3* out, const Vector3* v);
extern Vector3* __cdecl ClosestPointOnSegment(Vector3* out, const Vector3* a, const Vector3* b,
                                              const Vector3* p);
extern bool __cdecl IntersectRaySphere(const Vector3* origin, const Vector3* dir,
                                       const Vector3* center, float radius, float* hitTime);
extern float __cdecl GetStarRadius(int starType);
extern float __cdecl GetVelocityLimit();

// ---- retail globals ----------------------------------------------------------------------------

extern const Vector3 kOrigin;              // 0x016e2114: (0,0,0)
extern const Vector3 kAvoidOrigin;         // 0x016e2190: (0,0,0)
extern const Vector3 kLocalForward;        // 0x015b8da8: local forward axis
extern const float kHitMiss;               // 0x013eb1bc: -1.0f
extern const float kAvoidRadiusScale;      // 0x01485548: 1.5f
extern const float kAvoidDistanceScale;    // 0x013ec4b4: 0.9f
extern const float kVectorEpsilon;         // 0x013ec4b8: 1e-8f
extern const float kHalf;                  // 0x01471064: 0.5f
extern const float kSpeedScale;            // 0x013ebc5c: 25.0f
extern const float kOne;                   // 0x01485720: 1.0f
extern const float kMinTargetLength;       // 0x0149bfc0: 1.5258789e-05f
extern const float kRadiusForKindOne;      // 0x015b8e18
extern const float kRadiusForOtherKinds;   // 0x015b8e14
extern const float kNormalSpeed;           // 0x015b8d8c
extern const float kBoostSpeed;            // 0x015b8d90

// ---- retail object layouts ---------------------------------------------------------------------

// An embedded spatial object.  Slot +0x2c returns its world position; slot
// +0x3c installs a quaternion orientation.
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

// The UFO game object.  Its embedded spatial object lives at +0x34; the
// remaining fields are the flight state touched by the avoidance code.
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

// A simulator that owns the player's space state.
struct cSPSimulatorSpaceGame {
    char mPad00[0x34];
    int mCurrentStarType;                           // +0x34
    char mPad38[8];
    PlayerInventory* mpPlayerState;                 // +0x40
    __declspec(noinline) PlayerInventory* GetPlayerInventory();
    __declspec(noinline) bool IsGalaxyView();
    __declspec(noinline) int GetCurrentStarType();
};

struct cStarManager {
    void* GetCurrentPlanet();
};

extern cSPSimulatorSpaceGame* __cdecl GetUFOSimulator();
extern Obstacle* __cdecl GetActivePlanet();
extern cStarManager* __cdecl GetStarManager();

// The locomotion component's steering output.  +0x10 is the requested turn
// amount and +0x14 points back at the UFO's embedded spatial object.
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
};
} // namespace SP

// ---- simulator / inventory accessors -----------------------------------------------------------

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

// ---- 0x0105e6d0 ---------------------------------------------------------------------------------

// @ 0x0105e6d0
void __stdcall FUN_0105e6d0(cSPSimulatorSpaceGame* sim, UFOState* ufo, Vector3* target,
                            float radiusScale, Vector3* outPosition, float* outRadius)
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

// ---- 0x0105eb90 ---------------------------------------------------------------------------------

// @ 0x0105eb90
void __thiscall SP::cUFOLocomotion::FUN_0105eb90(MotionOutput* out)
{
    UFOState* ufo = 0;
    if (out->mpSpatial)
        ufo = (UFOState*)((char*)out->mpSpatial - offsetof(UFOState, mSpatial));

    Vector3 local;
    TransformVector(&local, &kLocalForward, &ufo->mOrientation);

    Vector3 desired = ufo->mDesiredVelocity;
    float desiredInv = 1.0f / sqrtf(desired.x * desired.x +
                                    (desired.y * desired.y + desired.z * desired.z) +
                                    kVectorEpsilon);
    desired.x *= desiredInv;
    desired.y *= desiredInv;
    desired.z *= desiredInv;

    if (mFacing.x == kOrigin.x && mFacing.y == kOrigin.y && mFacing.z == kOrigin.z) {
        mFacing = local;
        float dot = desired.x * local.x + (desired.y * local.y + desired.z * local.z);
        if (dot < 0.0f) {
            Vector3 orthogonal;
            OrthogonalVector(&orthogonal, &desired);
            float orthoInv = 1.0f / sqrtf(orthogonal.x * orthogonal.x +
                                          (orthogonal.y * orthogonal.y +
                                           orthogonal.z * orthogonal.z) +
                                          kVectorEpsilon);
            mFacing.x = orthogonal.x * orthoInv;
            mFacing.y = orthogonal.y * orthoInv;
            mFacing.z = orthogonal.z * orthoInv;
        }
    }

    float turnAmount = out->mTurnAmount * kHalf;
    if (turnAmount > kOne)
        turnAmount = kOne;

    Vector3 rotated;
    RotateTowards(&rotated, &local, &mFacing, turnAmount);
    local = rotated;

    Quaternion orientation;
    QuaternionFromFacingAndUp(&orientation, &local, &desired);
    ufo->mSpatial.SetOrientation(&orientation);

    float speed = kNormalSpeed;
    cStarManager* starManager = GetStarManager();
    void* currentPlanet = starManager->GetCurrentPlanet();
    if (ufo->GetPlanet() == currentPlanet)
        speed = kBoostSpeed;
    speed *= kSpeedScale;

    out->mVelocity.x = local.x * speed;
    out->mVelocity.y = local.y * speed;
    out->mVelocity.z = local.z * speed;

    Vector3* ufoPosition = ufo->mSpatial.GetPosition();
    float distance = sqrtf(ufoPosition->x * ufoPosition->x +
                           (ufoPosition->y * ufoPosition->y +
                            ufoPosition->z * ufoPosition->z));
    if (GetVelocityLimit() < distance)
        out->mVelocity = kOrigin;
}

// ---- 0x0105eeb0 ---------------------------------------------------------------------------------

// @ 0x0105eeb0
void __thiscall SP::cUFOLocomotion::AvoidSolarObstacles(cSPSimulatorSpaceGame* sim, UFOState* ufo,
                                                         Vector3* position)
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
