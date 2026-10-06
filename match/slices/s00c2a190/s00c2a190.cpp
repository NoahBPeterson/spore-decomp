// UpdateCreatureMoveVelocity (0x00c2a190, 3730 bytes; name guessed). Called only from the
// creature steering update at 0x00c2d220 as f(state, creature).
// Splits the creature's velocity into the planet-normal ("vertical") and tangential parts,
// handles flying/falling (gravity impulse with an optional hover bob), picks a target ground
// speed, steers toward the current locomotion goal (or the player-controlled direction while
// the creature is the avatar), and when the goal is reached pops the next waypoint or stops.
// Layouts: Spore ModAPI cCreatureBase / cLocomotiveObject / cLocomotionRequest (retail offsets
// confirmed in the disassembly).
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    float Dot(const Vector3& o) const { return x * o.x + y * o.y + z * o.z; }
    float LengthSq() const { return x * x + y * y + z * z; }
    bool operator==(const Vector3& o) const { return x == o.x && y == o.y && z == o.z; }
    bool operator!=(const Vector3& o) const { return x != o.x || y != o.y || z != o.z; }
};
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
inline Vector3 operator*(float s, const Vector3& a) { return Vector3(s * a.x, s * a.y, s * a.z); }

extern const Vector3 kZeroVector;   // 0x0168dd78

// v / |v| with a tiny bias so a zero vector stays finite (inline twin of SP::normalized_safe)
__forceinline Vector3 SafeNormalized(Vector3 v)
{
    float inv = 1.0f / sqrtf(v.LengthSq() + 1e-8f);
    return Vector3(v.x * inv, v.y * inv, v.z * inv);
}
__forceinline Vector3 Normalized(Vector3 v)
{
    float inv = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    return Vector3(v.x * inv, v.y * inv, v.z * inv);
}

// minss/maxss helper of the /arch:SSE modules
inline float Clamp(float v, float lo, float hi)
{
    __asm {
        movss xmm0, v
        maxss xmm0, lo
        minss xmm0, hi
        movss v, xmm0
    }
    return v;
}
inline bool IsPlayerControlled(const struct cCreatureBase* c);
template <class T> inline const T& Min(const T& a, const T& b) { return (a < b) ? a : b; }

namespace SP {
Vector3 normalized_safe(const Vector3& v);   // 0x00449c20
}

extern "C" void __cdecl EA_Free(void* p);    // 0x00f47380

struct cWaypoint {                           // 0x3c bytes, the vector element of a request
    Vector3 dstPos;                          // +0x0
    float goalStopDistance;                  // +0xc
    uint32_t data[11];
};

struct cWaypointVector {                     // eastl::vector<cWaypoint>
    cWaypoint* mpBegin;
    cWaypoint* mpEnd;
    cWaypoint* mpCapacity;
    uint32_t mAllocator[2];
    ~cWaypointVector()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            EA_Free(mpBegin);
    }
    bool empty() const { return mpBegin == mpEnd; }
    cWaypoint* erase(cWaypoint* it);         // 0x00b47520
};

struct cLocomotionRequest {                  // size 0x74
    cLocomotionRequest();                    // 0x00ac9850
    cWaypointVector mWaypoints;              // +0x0
    cWaypoint mCurrent;                      // +0x14 (dstPos, goalStopDistance, ...)
    Vector3 field_50;                        // +0x50
    int field_5C;                            // +0x5c
    float acceptableStopDistance;            // +0x60
    float facingThreshold;                   // +0x64
    float field_68;
    float field_6C;
    int field_70;
};

class cLocomotiveObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();                       // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
    virtual Vector3 GetDirection();                             // +0x5c
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0();
    virtual void SetDesiredSpeed(float speed, int flags);       // +0xc4
    virtual float GetDesiredSpeed();                            // +0xc8
    virtual float GetStandardSpeed();                           // +0xcc
    virtual void vd0(); virtual void vd4(); virtual void vd8();
    virtual void SetLocomotionRequest(const cLocomotionRequest& request);   // +0xdc

    cLocomotionRequest* GetLocomotionRequest();                 // 0x00c41ec0
    bool IsNearGoal();                                          // 0x00c42e20
    const Vector3& GetVelocity();                               // 0x00d20610
    Vector3 GetSteeringVelocity();                              // 0x00c44080
    void ApplyImpulse(const Vector3& impulse, bool b);          // 0x00c446d0
};

struct cAnimLocomotion { void SetHeightAboveGround(float h); };   // 0x009ce740
struct cAnimWorld { uint32_t pad[0x15b8 / 4]; cAnimLocomotion mLocomotion; };
struct AnimatedCreature { uint32_t pad[0x17c / 4]; cAnimWorld* mpWorld; };

struct cSpeciesProfile {
    uint32_t pad0[0x54c / 4];
    float mFallSpeed;                         // +0x54c
    float mFlySpeed;                          // +0x550
    uint32_t pad554[(0x61c - 0x554) / 4];
    uint32_t mCanFly;                         // +0x61c
};

struct cCreatureBase {
    uint32_t pad0[0xc0 / 4];
    cLocomotiveObject mLocomotion;            // +0xc0
    uint32_t padc4[(0x2a8 - 0xc4) / 4];
    float field_2A8;                          // +0x2a8
    uint32_t pad2ac[(0xb20 - 0x2ac) / 4];
    cSpeciesProfile* mpSpeciesProfile;        // +0xb20
    uint32_t padb24[(0xb54 - 0xb24) / 4];
    AnimatedCreature* mpAnimatedCreature;     // +0xb54
    uint32_t mGeneralFlags;                   // +0xb58
    bool field_B5C;                           // +0xb5c
    uint8_t padb5d[0xf90 - 0xb5d];
    bool field_F90;                           // +0xf90
};

inline bool IsPlayerControlled(const cCreatureBase* c) { return (c->mGeneralFlags >> 9) & 1; }
struct cPlanetModel {
    float GetGravity();                                   // 0x00b7e490
    Vector3 GetSurfacePoint(const Vector3& pos);          // 0x00b81630
};

struct cGameTimeManager { uint64_t GetGameTimeMS(); };    // 0x00b316c0

struct cViewer {
    void GetCameraLocationInfo(void* a, Vector3* position, void* b, void* c);   // 0x007c3d30
};
struct cRenderer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual cViewer* GetViewer();                         // +0x1c
};
struct cApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual cRenderer* GetRenderer();                     // +0x50
};
struct cGameNounManager { cCreatureBase* GetAvatar(); };   // 0x00b1fdb0

namespace SP {
void* GetCurrentGameMode();                  // 0x00b5b800
cPlanetModel* PlanetModel();                 // 0x00b3d350
cGameTimeManager* GameTimeManager();         // 0x00b3d380
cGameNounManager* NounManager();             // 0x00b3d300
cApp* App();                                 // 0x0067dd10
}
namespace cUIBanningContent { bool StartBanMode(int mode); }   // 0x008d2fb0

float SteerTowards(cCreatureBase* creature, Vector3* direction, const Vector3* target, float dt,
                   float speed, float turnRate, bool playerControlled);   // 0x00c29b10

extern float gFallingSpeedThreshold;       // 0x01582fc0 (10.0)
extern bool gPlayerSteerActive;            // 0x0169e381
extern bool gPlayerSteerFaceMove;          // 0x0169e37f
extern Vector3 gPlayerSteerDirection;      // 0x0169e388

struct cMoveState {
    Vector3 velocity;                      // +0x0
    float pad;                             // +0xc
    float dt;                              // +0x10
};

void UpdateCreatureMoveVelocity(cMoveState* state, cCreatureBase* creature)
{
    SP::GetCurrentGameMode();
    cPlanetModel* planet = SP::PlanetModel();
    float gravity = planet->GetGravity();
    bool playerControlled = IsPlayerControlled(creature);
    cLocomotiveObject* loco = &creature->mLocomotion;
    const Vector3& pos = loco->GetPosition();
    Vector3 up = SafeNormalized(pos);

    cLocomotionRequest* request = loco->GetLocomotionRequest();
    bool hasGoal = request->field_5C != 0;
    float stopDistance = request->mCurrent.goalStopDistance;
    loco->IsNearGoal();
    bool done = request->field_5C != 3 && !creature->field_B5C;
    loco->GetDesiredSpeed();
    float turnScale = creature->field_2A8;
    bool canFly = creature->mpSpeciesProfile->mCanFly > 0 || creature->mpSpeciesProfile->mFlySpeed > 0.0f;

    state->velocity = loco->GetVelocity();
    Vector3 surface = planet->GetSurfacePoint(pos);
    Vector3 h = surface - pos;
    creature->mpAnimatedCreature->mpWorld->mLocomotion.SetHeightAboveGround(sqrtf(h.LengthSq()));
    float distToGoal;
    if (hasGoal) {
        Vector3 g = surface - request->mCurrent.dstPos;
        distToGoal = sqrtf(g.LengthSq());
    } else {
        distToGoal = 0.0f;
    }

    // split the velocity along the planet normal
    Vector3 velocity = state->velocity;
    float vdot = velocity.Dot(up);
    bool falling = vdot < 0.0f;
    Vector3 vertical = up * vdot;
    Vector3 finalVertical = vertical;
    Vector3 horizontal = velocity - vertical;
    float horizontalSq = horizontal.LengthSq();
    float horizontalSpeed = sqrtf(horizontalSq);
    Vector3 direction = loco->GetDirection();

    float approach = Clamp(10.0f / (distToGoal + 10.0f), 0.0f, 1.0f);
    float turnFactor = approach * 0.25f + 0.75f;

    bool arrived;
    if (hasGoal) {
        Vector3 g = surface - request->mCurrent.dstPos;
        arrived = stopDistance * stopDistance > g.LengthSq();
    } else {
        arrived = true;
    }

    float climbSpeed = falling ? creature->mpSpeciesProfile->mFallSpeed : 0.0f;
    if (!playerControlled && arrived && done && request->mWaypoints.empty())
        climbSpeed = 0.0f;

    if (falling && (creature->mGeneralFlags & 0x1000) && distToGoal > 10.0f) {
        climbSpeed = 0.0f;
        float bob = 0.0f;
        if (creature->field_F90) {
            float seconds = (float)SP::GameTimeManager()->GetGameTimeMS() * 0.001f;
            bob = cosf(seconds * 0.5f) * 0.5f * 0.05f;
        }
        Vector3 impulse = state->dt * (up * (bob - gravity));
        loco->ApplyImpulse(impulse, false);
    }
    Vector3 climb = up * (state->dt * climbSpeed);

    // steering direction in the tangent plane
    Vector3 steer = loco->GetSteeringVelocity();
    Vector3 tangent = steer - up * steer.Dot(up);
    Vector3 heading;
    if (tangent == kZeroVector)
        heading = SafeNormalized(horizontal);
    else
        heading = SafeNormalized(tangent);
    Vector3 newVelocity = state->velocity;
    Vector3 target = pos + direction;

    float threshold;
    if (canFly && falling)
        threshold = gFallingSpeedThreshold;
    else
        threshold = loco->GetStandardSpeed() * 0.2f;
    float speed = horizontalSpeed;
    if (threshold > horizontalSpeed) {
        float k = state->dt * 2.0f;
        float one = 1.0f;
        speed = (threshold - horizontalSpeed) * Min(k, one) + horizontalSpeed;
    }

    if (playerControlled && gPlayerSteerActive) {
        Vector3 steerDir = gPlayerSteerDirection;
        if (gPlayerSteerFaceMove) {
            if (direction.Dot(steerDir) > 0.0f)
                target = pos + steerDir;
            else
                target = pos - steerDir;
        }
        newVelocity = SafeNormalized(steerDir) * speed + vertical;
        Vector3 seek = target;
        if (IsPlayerControlled(creature) && cUIBanningContent::StartBanMode(0x3ea)) {
            cCreatureBase* avatar = SP::NounManager()->GetAvatar();
            cViewer* viewer = SP::App()->GetRenderer()->GetViewer();
            Vector3 cameraPos;
            viewer->GetCameraLocationInfo(0, &cameraPos, 0, 0);
            Vector3 avatarUp = SP::normalized_safe(avatar->mLocomotion.GetPosition());
            avatarUp = cameraPos - avatarUp * avatarUp.Dot(cameraPos);
            Vector3 toCamera = SP::normalized_safe(avatarUp);
            seek = toCamera + pos;
        }
        SteerTowards(creature, &direction, &seek, state->dt, speed, turnFactor * turnScale,
                     IsPlayerControlled(creature));
    } else if (hasGoal) {
        target = pos + heading;
        SteerTowards(creature, &direction, &target, state->dt, speed, turnFactor * turnScale,
                     IsPlayerControlled(creature));
        newVelocity = direction * speed + vertical;
    }
    state->velocity = newVelocity + climb;

    if (!hasGoal)
        return;
    if (!done) {
        Vector3 toGoal = SafeNormalized(target - request->mCurrent.dstPos);
        Vector3 n = Normalized(pos);
        Vector3 t = toGoal - n * n.Dot(toGoal);
        if (t != kZeroVector)
            toGoal = Normalized(t);
        done = toGoal.Dot(direction) > request->facingThreshold;
    }
    if (!arrived)
        return;
    if (!request->mWaypoints.empty()) {
        request->mCurrent = *request->mWaypoints.mpBegin;
        request->mWaypoints.erase(request->mWaypoints.mpBegin);
        return;
    }
    if (!done)
        return;
    loco->SetLocomotionRequest(cLocomotionRequest());
    loco->SetDesiredSpeed(0.0f, 1);
    state->velocity = finalVertical;
}
