// Slice s0105c8d0 -- FUN_0105c9d0: moving-object steering update (re-seats the object on the
// point-on-sphere constraint around a center, blends its velocity toward a heading, re-aims the
// target point and refreshes the follow position).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: no EH-requiring locals).
#include "types.h"
#include <math.h>

#define VPAD(n) virtual void vpad##n()

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
};
Vector3 normalized_safe(const Vector3& v);              // 0x00449c20 (cdecl, hidden sret)

struct cSpatialPart {                                   // sub-object at +0x34
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual const Vector3* GetPosition();               // +0x2c
};

struct cSPTimer {
    void Stop();                                        // 0x00bc3110
    void Restart();                                     // 0x00bc3130
    void Clear();                                       // 0x00bc3170
    uint64_t GetElapsedTime();                          // 0x00bc3190
    bool IsRunning();                                   // 0x00feba90
};

struct cSteerConfig {                                   // singleton at 0x0168df68
    uint32_t pad00[0x11c / 4];
    float mGalaxyMaxPlumpDistance;                      // +0x11c
    uint32_t pad120[(0x184 - 0x120) / 4];
    uint8_t mbGalaxyWarpEnabled;                        // +0x184
    float GetBlend();                                   // 0x00c37470 (+0xc8)
    float GetDamping();                                 // 0x00c37480 (+0xcc)
    float GetKinestheticBlend();                        // 0x00a0ab60
    float GetGalaxyWarpMultiplier(int kind, int mode);  // 0x00c3b880
    float GetGalaxyWarpTime(int kind, int mode, float dist);    // 0x00c3a1b0
};
cSteerConfig* SteerConfig();                            // 0x00c37360

extern const float kCoupling;                           // 0x015b8df4 = 5.0
extern const float kMinSpeed;                           // 0x015b8df0 = 0.001
extern const float kHeadingDot;                         // 0x015b8dec = -0.8
extern const float kRetargetDist;                       // 0x015b8de8 = 5.0
extern const float kDirDot;                             // 0x015b8de4 = -0.8
extern const float kLead;                               // 0x015b8de0 = 2.0

struct cSteered {
    uint32_t pad00[0x34 / 4];
    cSpatialPart mAnchor;                               // +0x34
    uint32_t pad38[(0x60c - 0x38) / 4];
    Vector3 mPush;                                      // +0x60c
    uint32_t pad618[(0x624 - 0x618) / 4];
    uint8_t mb624;
    uint8_t pad625[0x648 - 0x625];
    cSPTimer mTimerA;                                   // +0x648
    uint32_t pad64c[(0x668 - 0x64c) / 4];
    cSPTimer mTimerB;                                   // +0x668
    uint32_t pad66c[(0x718 - 0x66c) / 4];
    Vector3 mPos;                                       // +0x718
    Vector3 mVel;                                       // +0x724
    uint32_t pad730[(0x74c - 0x730) / 4];
    uint8_t mbTargetValid;                              // +0x74c
    uint8_t pad74d[3];
    Vector3 mTarget;                                    // +0x750
    uint32_t pad75c[(0x768 - 0x75c) / 4];
    float mTargetDist;                                  // +0x768 (read via GetTargetDist)

    float GetTargetDist();                              // 0x00c37120
    void SetTargetDist(float d);                        // 0x00c3daa0
    float GetFollowDist();                              // 0x00c3be10
    void SetFollow(float w, const Vector3* v);          // 0x00c3db50
};

// @ 0x0105c9d0
void __stdcall FUN_0105c9d0(cSteered* o, const Vector3* a2, const Vector3* a3, float a4)
{
    const Vector3* c = o->mAnchor.GetPosition();
    Vector3 pos = o->mPos;
    float iu = 1.0f / sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + 1e-8f);
    Vector3 up(pos.x * iu, pos.y * iu, pos.z * iu);
    Vector3 d(pos.x - c->x, pos.y - c->y, pos.z - c->z);
    float speed = sqrtf(o->mVel.x * o->mVel.x + o->mVel.y * o->mVel.y + o->mVel.z * o->mVel.z);
    float dl = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
    float delta = dl - sqrtf(a2->x * a2->x + a2->y * a2->y + a2->z * a2->z);
    float id = 1.0f / sqrtf(d.x * d.x + d.y * d.y + d.z * d.z + 1e-8f);
    o->mPos.x = a2->x + (c->x + (id * d.x) * delta);
    o->mPos.y = a2->y + (c->y + (id * d.y) * delta);
    o->mPos.z = a2->z + (c->z + (id * d.z) * delta);

    float blend = SteerConfig()->GetBlend();
    float damp = SteerConfig()->GetDamping();
    float k = fabsf(o->mVel.x * a3->x + o->mVel.z * a3->z + o->mVel.y * a3->y) * (blend + 1.0f);
    Vector3 t(a3->x * k, a3->y * k, a3->z * k);
    o->mPush.y += t.y * kCoupling;
    o->mPush.x += t.x * kCoupling;
    o->mPush.z += t.z * kCoupling;
    Vector3 nv(t.x + o->mVel.x, o->mVel.y + t.y, o->mVel.z + t.z);
    if (nv.z * nv.z + nv.y * nv.y + nv.x * nv.x < 1.52587890625e-05f)
        nv = up;

    Vector3 heading;
    const Vector3* h;
    if (speed > 1.52587890625e-05f) {
        float vx = o->mVel.x, vy = o->mVel.y, vz = o->mVel.z;
        float iv = 1.0f / sqrtf(vz * vz + vy * vy + vx * vx + 1e-8f);
        heading = Vector3(iv * vx, iv * vy, iv * vz);
        h = &heading;
    } else {
        h = &up;
    }
    float dot = (h->z * a3->z + h->y * a3->y) + h->x * a3->x;
    float blendDot = dot + 1.0f;
    float in = 1.0f / sqrtf(nv.x * nv.x + nv.y * nv.y + nv.z * nv.z + 1e-8f);
    Vector3 nd(in * nv.x, nv.y * in, in * nv.z);
    if (blendDot <= 0.0f)
        blendDot = 0.0f;
    if (1.0f <= blendDot)
        blendDot = 1.0f;
    const float* sp = &speed;
    if (speed <= kMinSpeed)
        sp = &kMinSpeed;
    float nspeed = *sp * ((1.0f - damp) * blendDot + damp);
    o->mVel.x = nd.x * nspeed;
    o->mVel.y = nd.y * nspeed;
    o->mVel.z = nd.z * nspeed;

    float len;
    bool reaim = true;
    if (!o->mbTargetValid && !(dot < kHeadingDot)) {
        Vector3 tg(o->mTarget.x - pos.x, o->mTarget.y - pos.y, o->mTarget.z - pos.z);
        float tl = sqrtf(tg.y * tg.y + tg.z * tg.z + tg.x * tg.x);
        if (!(tl < kRetargetDist)) {
            Vector3 dir = normalized_safe(tg);
            const Vector3& aim = normalized_safe(*a2);
            if (!((aim.y * dir.y + aim.z * dir.z) + dir.x * aim.x < kDirDot))
                reaim = false;
        }
    }
    if (reaim) {
        float l2 = a2->x * a2->x + a2->y * a2->y + a2->z * a2->z;
        float lead = sqrtf(l2) + kLead;
        float il = 1.0f / sqrtf(l2 + 1e-8f);
        o->mTarget.x = (a2->x * il) * lead + pos.x;
        o->mTarget.y = (a2->y * il) * lead + pos.y;
        o->mTarget.z = (a2->z * il) * lead + pos.z;
        o->mbTargetValid = 0;
        o->mTimerA.Stop();
        o->mb624 = 0;
        len = sqrtf(o->mTarget.x * o->mTarget.x + o->mTarget.y * o->mTarget.y + o->mTarget.z * o->mTarget.z);
        o->SetTargetDist(len);
    } else {
        len = sqrtf(o->mTarget.x * o->mTarget.x + o->mTarget.y * o->mTarget.y + o->mTarget.z * o->mTarget.z);
        if (len > o->GetTargetDist())
            o->SetTargetDist(len);
    }
    o->mTimerB.Restart();
    float f = o->GetFollowDist();
    float ia = 1.0f / sqrtf(a2->z * a2->z + (a2->y * a2->y + a2->x * a2->x) + 1e-8f);
    Vector3 np(o->mPos.x - (a2->x * ia) * f, o->mPos.y - (a2->y * ia) * f, o->mPos.z - (a2->z * ia) * f);
    o->SetFollow(a4, &np);
}

// ---------------------------------------------------------------------------
//  s0105c8d0: kinesthetics tuning / content-validation summarizer helpers
// ---------------------------------------------------------------------------
struct cWarpDaemon {                                    // drive object at +0x508 (vtable)
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7);
    VPAD(8); VPAD(9); VPAD(10); VPAD(11); VPAD(12); VPAD(13);       // +0x00..0x34
    virtual void StartWarp();                           // +0x38
};
struct cMaterialTable {                                 // object at +0x730 (opaque storage)
    uint32_t pad00[(0x76c - 0x730) / 4];
};
const Vector3* RotateByQuat(Vector3* out, const void* key, const cMaterialTable* table);  // 0x0059aed0

struct cSPGameDataUFO {                                 // the UFO's state block (0x718 = position)
    uint32_t pad00[0x508 / 4];
    cWarpDaemon mWarpDaemon;                            // +0x508 (vptr; 15 vtable slots)
    uint8_t pad50c[0x628 - 0x50c];
    cSPTimer mWarpClock;                                // +0x628 (methods only)
    uint8_t pad629[0x714 - 0x629];
    int mMode;                                          // +0x714
    Vector3 mPos;                                       // +0x718
    Vector3 mVel;                                       // +0x724
    cMaterialTable mMaterial;                           // +0x730
    int mWarpState;                                     // +0x76c
    uint8_t pad770[0x7f4 - 0x770];
    float mWarpSpeed;                                   // +0x7f4
    bool CanWarp();                                     // 0x00c37040
};

struct cPlanetModel {
    float FUN_b7e4d0();                                 // 0x00b7e4d0
};
cPlanetModel* PlanetModel();                            // 0x00b3d350

struct cSPSpacePlanetCameraController {
    float GetMouseWheelSpeed();                         // 0x01017e80
};
struct cControllerHolder {
    VPAD(0); VPAD(1); VPAD(2);                          // +0x00..0x08
    virtual cSPSpacePlanetCameraController* FindController(uint32_t key);   // +0x0c
};
struct cAppInner {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7);
    VPAD(8); VPAD(9); VPAD(10); VPAD(11); VPAD(12); VPAD(13);               // +0x00..0x34
    virtual cControllerHolder* GetControllers();        // +0x38
};
struct cAppObj {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17);
    VPAD(18); VPAD(19);                                 // +0x00..0x4c
    virtual cAppInner* GetSimulator();                  // +0x50
};
cAppObj* App();                                         // 0x0067dd10

// @ 0x0105c8d0
// Caps the plump distance stored at +0x718: the effective cap is the kinesthetic
// blend of the steering config, or - while the UFO is not warping (mode 0) - the
// wheel speed of the space camera controller, whichever is smaller.
void __stdcall GetMaxHeight(cSPGameDataUFO* o)
{
    float len = sqrtf(o->mPos.x * o->mPos.x + o->mPos.y * o->mPos.y + o->mPos.z * o->mPos.z);
    float cap = SteerConfig()->GetKinestheticBlend() + PlanetModel()->FUN_b7e4d0();
    float ratio;
    if (o->mMode == 0) {
        cControllerHolder* holder = App()->GetSimulator()->GetControllers();
        if (holder) {
            cSPSpacePlanetCameraController* ctl = holder->FindController(0x303154cd);
            if (ctl) {
                float wheel = ctl->GetMouseWheelSpeed();
                if (wheel < len) {
                    ratio = wheel / len;
                    goto apply;
                }
                return;
            }
        }
    }
    if (!(len > cap))
        return;
    ratio = cap / len;
apply:
    {
        o->mPos.x = o->mPos.x * ratio;
        o->mPos.y = o->mPos.y * ratio;
        o->mPos.z = o->mPos.z * ratio;
    }
}

// vtable objects of the two summarizer constructors
extern void* g_vtCVS[];                 // 0x013ec458
extern void* g_vtD180Class[];           // 0x0149bfc8
extern void* g_vtD180Base[];            // 0x01475114
extern void* g_vtD1D0Class[];           // 0x0149bfd8
extern const Vector3 kDefaultSummarizerExtents;         // 0x016e2114

struct cSummarizerD180 {
    void** mClassVt;                    // +0x00
    uint32_t mPad04;                    // +0x04
    void** volatile mBaseVt;            // +0x08
    uint32_t mField0C;                  // +0x0c
    Vector3 mExtents;                   // +0x10
};

// @ 0x0105d180
void* __fastcall FUN_0105d180(cSummarizerD180* s)
{
    s->mBaseVt = g_vtCVS;
    s->mField0C = 0;
    s->mClassVt = g_vtD180Class;
    s->mBaseVt = g_vtD180Base;
    s->mExtents.x = kDefaultSummarizerExtents.x;
    s->mExtents.y = kDefaultSummarizerExtents.y;
    s->mExtents.z = kDefaultSummarizerExtents.z;
    return s;
}

struct cSummarizerD1D0 {
    void** mClassVt;                    // +0x00
    uint32_t mPad04;                    // +0x04
    void** volatile mBaseVt;            // +0x08
    uint32_t mField0C;                  // +0x0c
};

// @ 0x0105d1d0
void* __fastcall FUN_0105d1d0(cSummarizerD1D0* s)
{
    s->mBaseVt = g_vtCVS;
    s->mField0C = 0;
    s->mClassVt = g_vtD1D0Class;
    s->mBaseVt = g_vtD180Base;
    return s;
}

// ---------------------------------------------------------------------------
//  0105d200: UFO galaxy warp-mode state machine.  The state field at +0x76c
//  runs idle(0) -> charging(1) -> aiming(2) -> plumping(3) -> warping(4); the
//  reach/time of every phase comes from the galaxy warp tuning on the steering
//  config singleton and the distances are measured against the plump point at
//  +0x718 (the UFO's stored offset from the destination).
// ---------------------------------------------------------------------------
struct cSPPlayerInventory {
    uint32_t pad00[0x76c / 4];
    int mWarpMode;                                      // +0x76c
};
struct cSPSimulatorSpaceGame {
    cSPPlayerInventory* GetPlayerInventory();           // 0x00a1ad60
    float GetMaxTravelDistance();                       // 0x00ffbfc0
};
cSPSimulatorSpaceGame* GetUFOSimulator();               // 0x00ffbe50

extern uint32_t g_warpAxisKey;                          // 0x016e2160
extern const float kMsToSeconds;                        // 0x013f9428 (0.001f)
extern const float kMinWarpExtent;                      // 0x0149bfc0 (1.5258789e-05f)
extern const float kWarpFacingThreshold;                // 0x01486cd8 (0.999f)

__forceinline float Length(const Vector3& v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}
__forceinline float Distance(const Vector3& a, const Vector3& b)
{
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

// @ 0x0105d200
void __stdcall UpdateWarpMode(cSPGameDataUFO* ufo, const Vector3* dest)
{
    cSteerConfig* cfg = SteerConfig();

    if (!cfg->mbGalaxyWarpEnabled) {
        if (ufo->mWarpState == 0) {
            ufo->mWarpState = ufo->CanWarp() ? 3 : 1;
            return;
        }
        if (ufo->mMode == 0 && ufo->mWarpSpeed <= 0.0f)
            ufo->mWarpState = 1;
        return;
    }

    cSPPlayerInventory* inv = GetUFOSimulator()->GetPlayerInventory();
    if (ufo->mMode == 3 && inv->mWarpMode != 1 &&
        (ufo->mWarpState == 1 || ufo->mWarpState == 4))
        ufo->mWarpState = 0;

    if (ufo->mWarpState == 4) {
        float reach = cfg->GetGalaxyWarpMultiplier(4, ufo->mMode) * cfg->mGalaxyMaxPlumpDistance;
        float ms = (Distance(ufo->mPos, *dest) / reach) * kMsToSeconds;
        float warpTime = cfg->GetGalaxyWarpTime(4, ufo->mMode, 0.0f);
        if (ms > warpTime * 2.0f)
            ufo->mWarpState = 0;
    }

    if (ufo->mWarpState == 0) {
        ufo->mWarpState = 1;
        if (ufo->CanWarp()) {
            ufo->mWarpDaemon.StartWarp();
            float dist = Distance(ufo->mPos, *dest);
            float plump = cfg->mGalaxyMaxPlumpDistance;
            float m1 = cfg->GetGalaxyWarpMultiplier(1, ufo->mMode) * plump;
            float m3 = cfg->GetGalaxyWarpMultiplier(3, ufo->mMode) * plump;
            float travel = GetUFOSimulator()->GetMaxTravelDistance();
            float warpTime = cfg->GetGalaxyWarpTime(2, ufo->mMode, dist / travel);
            if ((dist / m3) * kMsToSeconds + warpTime < (dist / m1) * kMsToSeconds) {
                ufo->mWarpState = 2;
                ufo->mWarpClock.Restart();
            }
        }
    }

    if (ufo->mWarpState == 2) {
        if (!ufo->mWarpClock.IsRunning())
            ufo->mWarpClock.Restart();
        float elapsed = (float)ufo->mWarpClock.GetElapsedTime() * kMsToSeconds;
        float dist = Distance(ufo->mPos, *dest);
        float travel = GetUFOSimulator()->GetMaxTravelDistance();
        float warpTime = cfg->GetGalaxyWarpTime(2, ufo->mMode, dist / travel);
        if (elapsed > warpTime) {
            Vector3 axisTmp;
            const Vector3* axis = RotateByQuat(&axisTmp, &g_warpAxisKey, &ufo->mMaterial);
            Vector3 toDest(dest->x - ufo->mPos.x, dest->y - ufo->mPos.y, dest->z - ufo->mPos.z);
            Vector3 dir = normalized_safe(toDest);
            if (kWarpFacingThreshold < dir.x * axis->x + dir.y * axis->y + dir.z * axis->z) {
                ufo->mWarpState = 3;
                float reach = cfg->GetGalaxyWarpMultiplier(3, ufo->mMode) * cfg->mGalaxyMaxPlumpDistance;
                float len = Length(ufo->mVel);
                if (len > kMinWarpExtent) {
                    float s = reach / len;
                    ufo->mVel.x = ufo->mVel.x * s;
                    ufo->mVel.y = ufo->mVel.y * s;
                    ufo->mVel.z = ufo->mVel.z * s;
                }
            }
        }
        return;
    }

    if (ufo->mWarpState == 3) {
        float reach = cfg->GetGalaxyWarpMultiplier(4, ufo->mMode) * cfg->mGalaxyMaxPlumpDistance;
        float ms = (Distance(ufo->mPos, *dest) / reach) * kMsToSeconds;
        float warpTime = cfg->GetGalaxyWarpTime(4, ufo->mMode, 0.0f);
        if (!(ms < warpTime))
            return;
        ufo->mWarpState = 4;
        float len = Length(ufo->mVel);
        if (len > kMinWarpExtent) {
            float s = reach / len;
            ufo->mVel.x = ufo->mVel.x * s;
            ufo->mVel.y = ufo->mVel.y * s;
            ufo->mVel.z = ufo->mVel.z * s;
        }
        ufo->mWarpClock.Clear();
    }
}
