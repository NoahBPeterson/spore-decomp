// Slice s01060df0: the single function in this slice is
//   0x01060DF0  SP::cUFOLocomotion::UpdatePlanetLocomotion  (7919 bytes, __thiscall, ret 8)
//
// PDB candidate (caller-scored): SP::cUFOLocomotion::UpdatePlanetLocomotion.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar float, x87 fsqrt/fsin/fcos,
// 16-byte aligned frame).
//
// Per-frame planet-mode locomotion of one UFO. `this` is the (stateless) cUFOLocomotion
// strategy; the UFO is reached through the context argument (+0x14 holds the UFO's
// cLocomotiveObject base, which sits at +0x34 of the game-data object). The second
// argument is the frame delta in milliseconds (unsigned).
//
// Field names follow the retail layout from the Spore ModAPI header cGameDataUFO.h
// (offsets differ from the 2008 dev PDB's SP::cSPGameDataUFO, whose member names are
// used where the two clearly correspond). Tuning getters are named by their retail
// cUFOKinestheticsTuning offset because retail inserted fields relative to the PDB.
#include "types.h"
#include <math.h>
#include <xmmintrin.h>
#ifndef NULL
#define NULL 0
#endif

#pragma intrinsic(sqrt, sin, cos, fabs)

// ---------------------------------------------------------------- math types
struct Vector3 {
    float x, y, z;

    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}

    Vector3 operator+(const Vector3& o) const { return Vector3(x + o.x, y + o.y, z + o.z); }
    Vector3 operator-(const Vector3& o) const { return Vector3(x - o.x, y - o.y, z - o.z); }
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    Vector3& operator+=(const Vector3& o) { x += o.x; y += o.y; z += o.z; return *this; }

    float Dot(const Vector3& o) const { return x * o.x + y * o.y + z * o.z; }
    float SquaredLength() const { return x * x + y * y + z * z; }
    __forceinline float Length() const { return (float)sqrt(x * x + y * y + z * z); }
    // v / |v| (no epsilon)
    __forceinline Vector3 Normalized() const { float inv = 1.0f / (float)sqrt(x * x + y * y + z * z); return Vector3(x * inv, y * inv, z * inv); }
    // v / sqrt(|v|^2 + 1e-8)
    __forceinline Vector3 SafeNormalized() const { float inv = 1.0f / (float)sqrt(x * x + y * y + z * z + 1e-08f); return Vector3(x * inv, y * inv, z * inv); }
    Vector3 Cross(const Vector3& o) const { return Vector3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x); }

    static const Vector3 ZERO;     // 0x016E2114
};

struct Vector2 {
    float x, y;
    Vector2(float ax, float ay) : x(ax), y(ay) {}
};

struct Quaternion {
    float x, y, z, w;

    Quaternion() {}
    Quaternion(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}

    // rotation of `angle` radians about a unit axis (no normalization)
    static Quaternion AxisAngle(const Vector3& axis, float angle)
    {
        float s = (float)sin(angle * 0.5f);
        float c = (float)cos(angle * 0.5f);
        return Quaternion(axis.x * s, axis.y * s, axis.z * s, c);
    }
    Quaternion Normalized() const
    {
        float inv = 1.0f / (float)sqrt(x * x + y * y + z * z + w * w);
        return Quaternion(x * inv, y * inv, z * inv, w * inv);
    }
    // *this = *this * q (Hamilton product, inline)
    Quaternion& operator*=(const Quaternion& q)
    {
        float nx = w * q.x + q.w * x + (y * q.z - z * q.y);
        float ny = w * q.y + q.w * y + (z * q.x - x * q.z);
        float nz = w * q.z + q.w * z + (x * q.y - y * q.x);
        float nw = q.w * w - (x * q.x + y * q.y + z * q.z);
        x = nx; y = ny; z = nz; w = nw;
        return *this;
    }
};

Quaternion operator*(const Quaternion& a, const Quaternion& b);                    // 0x007DCB00
Vector3    RotateVector(const Vector3& v, const Quaternion& q);                     // 0x0059AED0
Vector3    Normalize(const Vector3& v);                                             // 0x00436CE0
Quaternion Normalize(const Quaternion& q);                                          // 0x00799320
Quaternion Slerp(const Quaternion& from, const Quaternion& to, float t);            // 0x005B26F0

template <typename T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
template <typename T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
// SSE clamp (maxss/minss against memory operands)
inline float Clamp(float v, float lo, float hi)
{
    _mm_store_ss(&v, _mm_min_ss(_mm_max_ss(_mm_load_ss(&v), _mm_load_ss(&lo)), _mm_load_ss(&hi)));
    return v;
}

extern const Vector3 kXAxis;                 // 0x015B8D9C (1,0,0)
extern const Vector3 kYAxis;                 // 0x015B8DA8 (0,1,0)
extern const float   kPI;                    // 0x015B8D98

// module constants (all data, not folded)
extern const float kDamageOffsetMaxLength;   // 0x015B8E2C 0.5
extern const float kDamageOffsetDecayRate;   // 0x015B8E30 0.7
extern const float kArriveDistanceSq;        // 0x015B8E34 1.0
extern const float kRecentCollisionMs;       // 0x015B8E38 300.0
extern const float kZoomAltitudeTolerance;   // 0x015B8E3C 2.0
extern const float kNearbyRadiusScale;       // 0x015B8E40 2.0
extern const float kNearbyMinAltitude;       // 0x015B8E44 30.0

static const float kDegToRad = 0.017453292f;

namespace SP {

Quaternion QuaternionFromFacingAndUp(const Vector3& facing, const Vector3& up);    // 0x0069B600

class cGonzagoTimer {                              // 0x20 bytes
public:
    bool             IsRunning();                  // 0x00FEBA90
    unsigned __int64 GetElapsedTime();             // 0x00BC3190 (ms)
    void             Stop();                       // 0x00BC3110
    void             Restart();                    // 0x00BC3130
    uint32_t pad[8];
};

class cUFOKinestheticsTuning {
public:
    static cUFOKinestheticsTuning* Get();          // 0x00C37360 (global 0x0168DF68)
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

class cSpatialObject {                             // cLocomotiveObject's primary base
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual const Vector3& GetPosition();          // slot 11 (+0x2C)
    virtual void v12(); virtual void v13();
    virtual void SetPosition(const Vector3& pos);  // slot 14 (+0x38)
};

class cNounBounds {                                // returned by cGameData slot 27
public:
    uint32_t pad00[0x25C / 4];
    float mRadius;                                 // +0x25C
};

class cGameDataBase {
public:
    virtual void g00(); virtual void g01(); virtual void g02(); virtual void g03();
    virtual void g04(); virtual void g05(); virtual void g06(); virtual void g07();
    virtual void g08(); virtual void g09(); virtual void g10(); virtual void g11();
    virtual void g12(); virtual void g13(); virtual void g14(); virtual void g15();
    virtual void g16(); virtual void g17(); virtual void g18(); virtual void g19();
    virtual void g20(); virtual void g21(); virtual void g22(); virtual void g23();
    virtual void g24(); virtual void g25(); virtual void g26();
    virtual cNounBounds* GetBounds();              // slot 27 (+0x6C)
};

// The nouns scanned for the "nearby object raises the minimum altitude" rule:
// a cGameData whose spatial base sits at +0x120.
class cNearbyNounPad : public cGameDataBase { public: uint32_t pad04[(0x120 - 4) / 4]; };
class cNearbyNoun : public cNearbyNounPad, public cSpatialObject {};

class cGameDataUFOPad : public cGameDataBase { public: uint32_t pad04[(0x34 - 4) / 4]; };

class cGameDataUFO : public cGameDataUFOPad, public cSpatialObject {
public:
    float GetMaxSpeed();                           // 0x00C38900
    float GetAcceleration();                       // 0x00C38840

    uint32_t pad038[(0x5EC - 0x38) / 4];
    float         mCurrentBankAmount;              // +0x5EC
    float         mCurrentNoseTilt;                // +0x5F0
    Vector3       mLastTangentialVelocity;         // +0x5F4
    float         field_600;                       // +0x600
    float         mKeyboardRotation;               // +0x604
    uint32_t      field_608;                       // +0x608
    Vector3       mOffsetDueToDamage;              // +0x60C
    Vector3       mDamageVelocity;                 // +0x618
    bool          mRotateTowardsDestination;       // +0x624
    uint8_t       pad625[3];
    cGonzagoTimer mMovementTimer;                  // +0x628
    cGonzagoTimer mHoverTimer;                     // +0x648
    cGonzagoTimer mCollisionTimer;                 // +0x668
    bool          mHittingTheBrakes;               // +0x688
    bool          mBackingUp;                      // +0x689
    uint8_t       pad68a[2];
    uint32_t      mNPCFollowUFO;                   // +0x68C
    bool          mIgnoreAvoidance;                // +0x690
    bool          mIgnoreLocomotion;               // +0x691
    uint8_t       pad692[2];
    uint32_t      pad694[(0x714 - 0x694) / 4];
    int           mUFOType;                        // +0x714
    Vector3       mNextPosition;                   // +0x718
    Vector3       mNextVelocity;                   // +0x724
    Quaternion    mNextOrientation;                // +0x730
    Vector3       mOffsetFromPosition;             // +0x740
    bool          mAtDestination;                  // +0x74C
    uint8_t       pad74d[3];
    Vector3       mDestination;                    // +0x750
    uint32_t      mDestinationPlanet;              // +0x75C
    uint32_t      mPreviousPlanet;                 // +0x760
    uint32_t      field_764;                       // +0x764
    float         mZoomAltitude;                   // +0x768
};

struct tGameDataVector {
    void*         vtbl;
    cNearbyNoun** mpBegin;                         // +0x04
    cNearbyNoun** mpEnd;                           // +0x08
};

class cGameNounManager {
public:
    tGameDataVector* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);  // 0x00B21340
};

class cAvatar {
public:
    void UpdateUFOLocomotion(cGameDataUFO* ufo, float dt);  // 0x00FF6520
};

class cSpaceGame {
public:
    cAvatar* GetAvatar();                          // 0x00B1FDB0
};

class cUFOSimulator {
public:
    cGameDataUFO* GetPlayerUFO();                  // 0x00A1AD60 (+0x40)
    uint8_t pad00[0x55];
    bool    mbMouseSteering;                       // +0x55
};

class cPlanetModel {
public:
    Quaternion BuildSurfaceOrientation(const Vector3& pos, const Vector3& forward);  // 0x00B7F250
};

class cPlanetCamera {                              // QueryInterface(0x303154CD) result
public:
    float GetUFOEscapeAltitude();                  // 0x01017240
    uint32_t pad00[0x94 / 4];
    Vector3 mFacing;                               // +0x94
};

class cCameraInterface {
public:
    virtual void c00(); virtual void c01(); virtual void c02();
    virtual cPlanetCamera* QueryCamera(uint32_t id);   // slot 3 (+0x0C)
};

class cCameraManager {
public:
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13();
    virtual cCameraInterface* GetActiveCamera();   // slot 14 (+0x38)
};

class cApp {
public:
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08(); virtual void a09(); virtual void a10(); virtual void a11();
    virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
    virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
    virtual cCameraManager* GetCameraManager();    // slot 20 (+0x50)
};

struct cGameTimeManager { uint8_t pad00[0x48]; uint8_t mFlags; };   // bit 0: paused
struct cGameModeState   { uint32_t pad00[0x2C / 4]; int mState; };

cApp*              App();                          // 0x0067DD10
cGameNounManager*  NounManager();                  // 0x00B3D300
cGameTimeManager*  GameTimeManager();              // 0x00B3D380
cGameModeState*    GameModeState();                // 0x00B3D4D0
cPlanetModel*      PlanetModel();                  // 0x00B3D350
int                GetCurrentGameMode();           // 0x00B5B800
cSpaceGame*        SpaceGameGet();                 // 0x01002BD0
cUFOSimulator*     GetUFOSimulator();              // 0x00FFBE50

// game-data type descriptors passed to GetGameDataVector
void  GameDataTypeFn0();                           // 0x00CD7D10
void  GameDataTypeFn1();                           // 0x00D3D420
void  GameDataTypeFn2();                           // 0x00ACDFF0
void  GameDataTypeFn3();                           // 0x00B1E500
extern uint32_t kNearbyNounTypeData;               // 0x018C43E8

// locomotion helpers in the same module
// spring-damped seek: integrates pos/vel toward target
void SpringToTarget(Vector3* pos, Vector3* vel, const Vector3* target, const Vector3* targetVel,
                    const Vector2* params, float accel, float maxSpeed, float dtMs);       // 0x01042AA0
// constant-speed seek
void SeekTarget(Vector3* pos, Vector3* vel, const Vector3* target,
                float accel, float speed, float dtMs);                                     // 0x010426A0

struct cLocomotionContext {
    uint32_t        pad00[5];
    cSpatialObject* mpObject;                      // +0x14 (the UFO's cLocomotiveObject base)
};

class cUFOLocomotion {
public:
    void UpdatePlanetLocomotion(cLocomotionContext* pContext, unsigned int deltaTime);

    void ClampAltitude(cGameDataUFO* ufo, Vector3* pos, float minAltitude);  // 0x0105C7E0
    void UpdateAltitude(cGameDataUFO* ufo);                                  // 0x0105C8D0
    void ResolvePlanetaryCollisions(cGameDataUFO* ufo, float dt);            // 0x01060150
    Vector3 GetTargetPosition(cGameDataUFO* ufo);                            // 0x0105FBC0
    static void BeginLeavePlanet(cGameDataUFO* ufo, float t, unsigned int deltaTime);  // 0x0105F760

    uint32_t pad[4];
};

static __forceinline cPlanetCamera* GetPlanetCamera()
{
    cCameraInterface* pCamera = App()->GetCameraManager()->GetActiveCamera();
    if (pCamera == NULL) return NULL;
    return pCamera->QueryCamera(0x303154CD);
}

}  // namespace SP

using namespace SP;

static inline float MinDamageOffsetSq() { return 1.0f / 65536.0f; }

// @ 0x01060DF0
void SP::cUFOLocomotion::UpdatePlanetLocomotion(cLocomotionContext* pContext, unsigned int deltaTime)
{
    cUFOKinestheticsTuning* pTuning = cUFOKinestheticsTuning::Get();
    cGameDataUFO* ufo = static_cast<cGameDataUFO*>(pContext->mpObject);

    if (ufo->mIgnoreLocomotion)
        return;

    float minAltitude = pTuning->GetMinAltitude();

    // A nearby noun (within twice its radius) raises the minimum altitude toward 30.
    if (ufo->mUFOType == 0 && minAltitude < kNearbyMinAltitude) {
        float minDistSq = 3.402823466e+38F;
        cNearbyNoun* pNearest = NULL;
        tGameDataVector* pVec = NounManager()->GetGameDataVector(
            (void*)GameDataTypeFn0, (void*)GameDataTypeFn1, (void*)GameDataTypeFn2,
            (void*)GameDataTypeFn3, &kNearbyNounTypeData);
        for (cNearbyNoun** it = pVec->mpBegin; it != pVec->mpEnd; ++it) {
            cNearbyNoun* pNoun = *it;
            const Vector3& myPos = ufo->GetPosition();
            const Vector3& pos = pNoun->GetPosition();
            float distSq = (pos - myPos).SquaredLength();
            if (distSq < minDistSq) {
                minDistSq = distSq;
                pNearest = pNoun;
            }
        }
        if (pNearest != NULL) {
            const Vector3& myPos = ufo->GetPosition();
            const Vector3& pos = pNearest->GetPosition();
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
    if ((GameTimeManager()->mFlags & 1) != 0) {
        int state = GameModeState()->mState;
        if (state != 1 && state != 2) {
            Vector3 oldPos = ufo->mNextPosition;
            ClampAltitude(ufo, &ufo->mDestination, minAltitude);

            Vector2 params(0.3f, 0.0f);
            if (ufo->mNextPosition.SquaredLength() > ufo->mDestination.SquaredLength())
                params.x = pTuning->GetDescendFactor();
            else
                params.x = pTuning->GetAscendFactor();

            Vector3 up = ufo->mNextPosition.Normalized();
            Vector3 vel = ufo->mNextVelocity + ufo->mDamageVelocity;
            float vertical = (float)fabs(vel.Dot(up));
            Vector3 verticalVel = vel * vertical;
            Vector3 lateralVel = vel - verticalVel;

            SpringToTarget(&ufo->mNextPosition, &verticalVel, &ufo->mDestination, &Vector3::ZERO,
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

    Vector3 oldPos = ufo->mNextPosition;
    Vector3 target = ufo->mNextVelocity;

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

        Vector3 desiredVel = ufo->mDamageVelocity + ufo->mNextVelocity;
        target = GetTargetPosition(ufo);

        float seekSpeed;
        bool bSeek;
        if (bRecentCollision) {
            seekSpeed = maxSpeed * 0.2f;
            bSeek = true;
        } else {
            bSeek = false;
            if (ufo->mUFOType != 0) {
                Vector3 targetDir = Normalize(target);
                Vector3 posDir = Normalize(ufo->mNextPosition);
                if ((posDir - targetDir).SquaredLength() <= 0.25f &&
                    GetCurrentGameMode() != 0x1654C01 && GetCurrentGameMode() != 0x1654C02) {
                    seekSpeed = maxSpeed;
                    bSeek = true;
                }
            }
        }

        float dtMs = (float)deltaTime;
        if (bSeek)
            SeekTarget(&ufo->mNextPosition, &desiredVel, &target, accel, seekSpeed, dtMs);
        else
            SpringToTarget(&ufo->mNextPosition, &desiredVel, &target, &Vector3::ZERO,
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
            ufo->mDamageVelocity = Vector3::ZERO;

        if ((ufo->mNextPosition - ufo->mDestination).SquaredLength() < kArriveDistanceSq) {
            ufo->mDestination = ufo->mNextPosition;
            ufo->mAtDestination = true;
            ufo->mNextVelocity = Vector3::ZERO;
            ufo->mRotateTowardsDestination = true;
            ufo->mHoverTimer.Restart();
        }
    } else if ((float)fabs(ufo->mZoomAltitude - ufo->mDestination.Length()) <= kZoomAltitudeTolerance) {
        ufo->mNextPosition = ufo->mDestination;
        ufo->mNextVelocity = Vector3::ZERO;
        ufo->mLastTangentialVelocity = Vector3::ZERO;
        cPlanetCamera* pCamera = GetPlanetCamera();
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

    cSpaceGame* pSpaceGame = SpaceGameGet();
    if (pSpaceGame != NULL) {
        cAvatar* pAvatar = pSpaceGame->GetAvatar();
        if (pAvatar != NULL)
            pAvatar->UpdateUFOLocomotion(ufo, dt);
    }

    // ---- orientation
    Vector3 up = ufo->mNextPosition.Normalized();

    Vector3 tangentVel = ufo->mNextVelocity - up * up.Dot(ufo->mNextVelocity);
    float tangentSq = tangentVel.SquaredLength();
    if (tangentSq > accel * 0.01f)
        ufo->mLastTangentialVelocity = tangentVel * (1.0f / (float)sqrt(tangentSq));
    Vector3 lastTangent = ufo->mLastTangentialVelocity - up * up.Dot(ufo->mLastTangentialVelocity);
    ufo->mLastTangentialVelocity = lastTangent.SafeNormalized();

    Vector3 forward = RotateVector(kYAxis, ufo->mNextOrientation);
    ufo->mNextOrientation = PlanetModel()->BuildSurfaceOrientation(ufo->mNextPosition, forward);

    cUFOSimulator* pSim = GetUFOSimulator();
    bool bIsPlayer = (pSim != NULL && ufo == pSim->GetPlayerUFO()) ? true : false;

    Vector3 facing = forward - up * forward.Dot(up);
    Quaternion targetOrientation;
    bool bTurn = false;

    if (bIsPlayer && ufo->mKeyboardRotation != 0.0f) {
        // keyboard rotation about the local up axis
        float rotation = Clamp(ufo->mKeyboardRotation, -1.0f, 1.0f) * 0.5f;
        ufo->mKeyboardRotation = 0.0f;
        const Vector3* pAxisSource = &ufo->mNextPosition;
        if (ufo->mAtDestination && (GameTimeManager()->mFlags & 1) == 0)
            pAxisSource = &ufo->mDestination;
        Vector3 axis = pAxisSource->SafeNormalized();
        Quaternion spin = Quaternion::AxisAngle(axis, rotation).Normalized();
        facing = RotateVector(forward, spin);
        targetOrientation = Normalize(QuaternionFromFacingAndUp(facing, up));
        bTurn = true;
    } else if (bIsPlayer && pSim->mbMouseSteering && !ufo->mAtDestination) {
        // mouse steering: face where the planet camera looks
        cPlanetCamera* pCamera = GetPlanetCamera();
        if (pCamera != NULL) {
            facing = pCamera->mFacing;
            targetOrientation = Normalize(QuaternionFromFacingAndUp(facing, up));
            bTurn = true;
        }
    } else if (ufo->mRotateTowardsDestination && !ufo->mAtDestination &&
               ufo->mDamageVelocity.SquaredLength() < 1.5258789e-05f) {
        // turn toward the destination (projected onto the tangent plane)
        Vector3 toDest = ufo->mDestination - oldPos;
        toDest = toDest - up * toDest.Dot(up);
        if (ufo->mBackingUp)
            toDest = -toDest;
        float dist = toDest.Length();
        if (dist > 5.0f)
            facing = toDest * (1.0f / dist);
        targetOrientation = Normalize(QuaternionFromFacingAndUp(facing, up));
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

        Vector3 nose = RotateVector(kYAxis, ufo->mNextOrientation);
        float forwardAmount = Clamp(ufo->mNextVelocity.Dot(nose) * noseFactor, -1.0f, 1.0f);
        float invDt = 1.0f / (dt + 0.001f);
        Vector3 climbVel = (ufo->mNextPosition - oldPos) * invDt;
        float climbAmount = Clamp(climbVel.Dot(up) * verticalFactor, -1.0f, 1.0f);

        float tilt = Clamp(maxNose * forwardAmount - maxVertical * climbAmount, -maxTilt, maxTilt);
        float blend = Min(rate * dt, 1.0f);
        ufo->mCurrentNoseTilt = (tilt - ufo->mCurrentNoseTilt) * blend + ufo->mCurrentNoseTilt;
        ufo->mNextOrientation *= Quaternion::AxisAngle(kXAxis, -ufo->mCurrentNoseTilt);
    }

    // ---- bank from sideways turning
    if (ufo->mUFOType != 1) {
        float bankFactor = pTuning->GetBankTiltFactor();
        float bankRate = pTuning->GetBankTiltRate();
        float maxBank = pTuning->GetMaxBankTilt() * kDegToRad;

        Vector3 right = RotateVector(kXAxis, ufo->mNextOrientation);
        float bank = right.Dot(facing) * bankFactor;
        float blend = Min(bankRate * dt, 1.0f);
        ufo->mCurrentBankAmount = (bank - ufo->mCurrentBankAmount) * blend + ufo->mCurrentBankAmount;
        ufo->mNextOrientation *= Quaternion::AxisAngle(kYAxis, maxBank * ufo->mCurrentBankAmount);
    }

    // ---- damage wobble: the offset decays and tilts the hull away from it
    float decayBlend = Min(dt * kDamageOffsetDecayRate, 1.0f);
    ufo->mOffsetDueToDamage += (Vector3::ZERO - ufo->mOffsetDueToDamage) * decayBlend;

    static const float sMinOffsetSq = MinDamageOffsetSq();
    if (ufo->mOffsetDueToDamage.SquaredLength() > sMinOffsetSq) {
        static const float sMaxWobbleAngle = kPI * 0.125f;
        float amount = Min(ufo->mOffsetDueToDamage.Length() / kDamageOffsetMaxLength, 1.0f);
        Vector3 axis = ufo->mOffsetDueToDamage.Cross(ufo->mNextPosition);
        float axisLength = axis.Length();
        if (axisLength > 1.5258789e-05f) {
            Quaternion wobble = Quaternion::AxisAngle(axis * (1.0f / axisLength), amount * sMaxWobbleAngle);
            ufo->mNextOrientation = wobble * ufo->mNextOrientation;
        }
    }
}
