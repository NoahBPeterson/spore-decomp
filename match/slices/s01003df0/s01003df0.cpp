// Slice s01003df0 -- FUN_01003df0 (0x01003df0, 3515 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Space game: per-frame update of an NPC "interceptor" UFO that is escorting / circling the
// player (PDB candidate SP::cSPSimulatorSpaceGame::UpdateInterceptorUFO; the retail layout
// differs from the 2008 PDB, so members are named by retail offset and role).
//   - returns true when the UFO is gone (vtable +0x2c) or has no target star;
//   - galaxy context (2): give up (state 6, drop the star-map visual) when forced, when the
//     player is badly damaged, when the empire is neither hostile nor at war, or when the
//     player / the target are out of the "intercept range" property; otherwise fly to the
//     player, circling it on a timer when both are in flight, and pick the nearest
//     attacking UFO (or the player) as combat target;
//   - solar-system context (1): circle the player at (radius + 1) * 15 along the UFO's orbit
//     axis, pick the nearest attacking UFO as combat target, or (if neither hostile nor at
//     war) send the UFO 3000 units out along its position.
#include "types.h"

#include <math.h>

namespace {

struct Vector3 {
    float x, y, z;
};

struct Quaternion {
    float x, y, z, w;
};

inline Vector3 operator-(const Vector3& a, const Vector3& b)
{
    Vector3 r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}

} // namespace

// ---- external helpers -------------------------------------------------------------------
Vector3*    normalized_safe(Vector3* out, const Vector3* v);                                   // 0x00449c20
Quaternion* QuaternionFromFacingAndUp(Quaternion* out, const Vector3* facing, const Vector3* up); // 0x0069b600
void        GetFloatProperty(void* propList, uint32_t id, float* value);                       // 0x0040cf10

extern const Vector3 kYAxis;           // 0x015b64c4 (0,1,0)
extern const Vector3 kZAxis;           // 0x015b64d0 (0,0,1)
extern const float   kOrbitRadiusScale;  // 0x015b6874 15
extern const float   kEscortDistance;  // 0x015b6878 0.15
extern const float   kOrbitWobble;     // 0x015b687c 0.2
extern const float   kOrbitPeriodScale;  // 0x015b6880 3
extern const int     kOrbitPeriodBias; // 0x015b6884 5
extern float         gOrbitSpeed;      // 0x016dc720

namespace SP {

struct cSimulatorUniverse {
    uint32_t pad0[0x10 / 4];
    void*    mpPropList;               // +0x10
};
extern cSimulatorUniverse* sSimulatorUniverse;   // 0x016dc798

struct cStarRecord {
    uint32_t pad0[0x70 / 4];
    uint32_t mStarID;                  // +0x70
    const Vector3& GetPosition();      // 0x005c65e0
};

struct cPlanetRecordHolder {           // returned by 0x01021240
    int GetOwnerID();                  // 0x00b1fdb0
    const Vector3& GetPosition();      // 0x005c65e0
};
cPlanetRecordHolder* GetCurrentStar();   // 0x01021240 (compared with the target star)

struct cEmpire {
    bool IsHostileToPlayer();          // 0x00c309e0
    bool IsAtWarWithPlayer();          // 0x00c31640
};
struct cStarManager {
    cEmpire* GetEmpireByID(int id);    // 0x00ba9370
};
cStarManager* StarManager();           // 0x00b3d2a0

struct cTerrainSphere {
    bool HasModel(uint32_t id);        // 0x00c772c0
};
struct cTerrainEditor {
    cTerrainSphere* GetCurrentTerrainSphere();   // 0x00f67d90
};
cTerrainEditor* NounManager();         // 0x00b3d300

struct cGameMode {
    bool IsPaused();                   // 0x00ac80f0
};
cGameMode* GameModeManager();          // 0x00b3d4d0

void* GetPlayerEmpire();               // 0x01021300
int   GetUniverseContext();            // 0x01021080

struct cStarMap {
    void RemoveVisual(uint32_t starID, uint32_t effectID, int a, int b);   // 0x01045ae0
};
cStarMap* StarMap();                   // 0x01046fc0

struct cSpatialObject {   // cSPGameDataUFO + 0x34
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3* GetPosition();   // +0x2c
};

struct cCombatant {       // cSPGameDataUFO + 0x508
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void SetTarget(cCombatant* target);   // +0x50
    int GetDamageState();              // 0x008e7f80
};

struct cSPTimer {
    bool IsRunning();                  // 0x00feba90
    void Restart();                    // 0x00bc3130
    void Reset();                      // 0x00bc3170 (clears times and running flag)
    unsigned __int64 GetElapsedTime(); // 0x00bc3190
};

struct cSPGameDataUFO {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool IsDestroyed();        // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual int  GetPoliticalID();     // +0x4c

    void  SetDestination(const Vector3* p);         // 0x00c3bfe0
    void  PopToDestination();                       // 0x00c37e60
    void  SetOrientation(const Quaternion* q);      // 0x00c5ae00
    void  LeaveStar(cStarRecord* star);             // 0x00c3c360
    float GetSize();                                // 0x00c3ae70

    uint32_t       pad04[(0x34 - 0x04) / 4];
    cSpatialObject mSpatial;                        // +0x34
    uint32_t       pad38[(0x508 - 0x38) / 4];
    cCombatant     mCombatant;                      // +0x508
    uint32_t       pad50c[(0x648 - 0x50c) / 4];
    cSPTimer       mOrbitTimer;                     // +0x648
    uint32_t       pad64c[(0x694 - 0x64c) / 4];
    Vector3        mOrbitAxis;                      // +0x694
    uint32_t       pad6a0[(0x6b0 - 0x6a0) / 4];
    int            mOrbitPeriod;                    // +0x6b0
    uint32_t       pad6b4[(0x714 - 0x6b4) / 4];
    int            mState;                          // +0x714 (3 = attacking, 6 = leaving)
    uint32_t       pad718[(0x74c - 0x718) / 4];
    bool           mbInFlight;                      // +0x74c
    uint8_t        pad74d[3];
    uint32_t       pad750[(0x76c - 0x750) / 4];
    int            mDamageMode;                     // +0x76c (3 = disabled)
    uint32_t       pad770[(0x7b0 - 0x770) / 4];
    cStarRecord*   mpTargetStar;                    // +0x7b0
};

class cSPSimulatorSpaceGame {
public:
    cSPGameDataUFO* GetPlayerInventory();           // 0x00a1ad60
    bool UpdateInterceptorUFO(cSPGameDataUFO* ufo, bool abandon);

    uint32_t         pad00[0x78 / 4];
    cSPGameDataUFO** mUFOsBegin;                    // +0x78
    cSPGameDataUFO** mUFOsEnd;                      // +0x7c
};
cSPSimulatorSpaceGame* GetUFOSimulator();           // 0x00ffbe50

} // namespace SP

using namespace SP;

// @ 0x01003df0
bool SP::cSPSimulatorSpaceGame::UpdateInterceptorUFO(cSPGameDataUFO* ufo, bool abandon)
{
    if (ufo->IsDestroyed() || !ufo->mpTargetStar)
        return true;

    GetPlayerEmpire();
    cSPGameDataUFO* player = GetUFOSimulator()->GetPlayerInventory();
    const Vector3& playerPos = *player->mSpatial.GetPosition();
    bool bothInFlight = player->mbInFlight && ufo->mbInFlight;

    cEmpire* empire = StarManager()->GetEmpireByID(ufo->GetPoliticalID());
    cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
    bool atWar = sphere->HasModel(0x5f1f0bc) && !sphere->HasModel(0x5f1f0ca);
    bool hostile = !empire || empire->IsHostileToPlayer();
    atWar = !empire || empire->IsAtWarWithPlayer() || atWar;

    switch (GetUniverseContext()) {
    case 2: {
        float range = 10.0f;
        GetFloatProperty(sSimulatorUniverse->mpPropList, 0x55e7dad, &range);
        range = range * range;

        bool leave = false;
        if (abandon || player->mCombatant.GetDamageState() == 2 || (!hostile && !atWar)) {
            leave = true;
        } else {
            cPlanetRecordHolder* cur = GetCurrentStar();
            if (cur && cur->GetOwnerID() != -1) {
                int id = ufo->GetPoliticalID();
                if (cur->GetOwnerID() != id) {
                    Vector3 d = cur->GetPosition() - playerPos;
                    if (d.x * d.x + d.y * d.y + d.z * d.z < range)
                        leave = true;
                }
            }
            if (!leave) {
                Vector3 d = playerPos - ufo->mpTargetStar->GetPosition();
                if (d.x * d.x + d.z * d.z + d.y * d.y > range)
                    leave = true;
            }
        }
        if (leave) {
            ufo->mState = 6;
            ufo->LeaveStar(ufo->mpTargetStar);
            uint32_t starID = ufo->mpTargetStar->mStarID;
            StarMap()->RemoveVisual(starID, 0xb7735c3, 0, 0);
            return false;
        }

        const Vector3& tp = ufo->mpTargetStar->GetPosition();
        Vector3 tmp;
        const Vector3* pDir;
        if (ufo->mpTargetStar == (cStarRecord*)GetCurrentStar()) {
            pDir = &kYAxis;
        } else {
            Vector3 d = tp - playerPos;
            pDir = normalized_safe(&tmp, &d);
        }
        Vector3 dir = *pDir;

        if (!bothInFlight || GameModeManager()->IsPaused()) {
            ufo->mOrbitTimer.Reset();
            Vector3 dest;
            dest.x = playerPos.x + dir.x * kEscortDistance;
            dest.y = playerPos.y + kEscortDistance * dir.y;
            dest.z = playerPos.z + dir.z * kEscortDistance;
            ufo->SetDestination(&dest);
        } else {
            cSPTimer& timer = ufo->mOrbitTimer;
            if (!timer.IsRunning())
                timer.Restart();
            unsigned __int64 elapsed = timer.GetElapsedTime();
            int period = ufo->mOrbitPeriod + kOrbitPeriodBias;
            float t = (float)elapsed * 0.001f;

            Vector3 tmp2;
            const Vector3* pUp;
            if (fabsf(dir.z) < 0.99998474f) {
                Vector3 p;
                p.x = kZAxis.x - dir.x * dir.z;
                p.y = kZAxis.y - dir.z * dir.y;
                p.z = kZAxis.z - dir.z * dir.z;
                pUp = normalized_safe(&tmp2, &p);
            } else {
                pUp = &kYAxis;
            }
            Vector3 up = *pUp;

            float fPeriod = (float)period;
            float angle = -((gOrbitSpeed * t) / (fPeriod * kOrbitPeriodScale));
            Vector3 neg;
            neg.x = -dir.x;
            neg.y = -dir.y;
            neg.z = -dir.z;
            Vector3 c;
            c.x = neg.y * up.z - neg.z * up.y;
            c.y = up.x * neg.z - neg.x * up.z;
            c.z = neg.x * up.y - up.x * neg.y;
            Vector3 side;
            normalized_safe(&side, &c);
            float r = sinf(fPeriod * angle) * kOrbitWobble;
            float ca = cosf(angle) * r;
            float sa = sinf(angle) * r;
            Vector3 n;
            n.x = up.x * ca + dir.x + side.x * sa;
            n.y = ca * up.y + dir.y + sa * side.y;
            n.z = dir.z + ca * up.z + sa * side.z;
            normalized_safe(&dir, &n);

            Vector3 dest;
            dest.x = playerPos.x + dir.x * kEscortDistance;
            dest.y = playerPos.y + dir.y * kEscortDistance;
            dest.z = playerPos.z + dir.z * kEscortDistance;
            ufo->SetDestination(&dest);

            Vector3 facing;
            facing.x = -dir.x;
            facing.y = -dir.y;
            facing.z = -dir.z;
            Quaternion q;
            QuaternionFromFacingAndUp(&q, &facing, &up);
            ufo->SetOrientation(&q);
            ufo->PopToDestination();
        }

        cSPGameDataUFO* best = 0;
        if (hostile && ufo->mDamageMode != 3) {
            if (player->mDamageMode != 3)
                best = player;
            Vector3 pos = *ufo->mSpatial.GetPosition();
            float bestDist = 3.402823466e+38F;
            for (cSPGameDataUFO** it = mUFOsBegin; it != mUFOsEnd; ++it) {
                cSPGameDataUFO* other = *it;
                if (other->mState == 3 && other->mDamageMode != 3) {
                    const Vector3* op = other->mSpatial.GetPosition();
                    float dy = pos.y - op->y;
                    float dx = pos.x - op->x;
                    float dz = pos.z - op->z;
                    float d = dz * dz + dy * dy + dx * dx;
                    if (d < bestDist) {
                        bestDist = d;
                        best = other;
                    }
                }
            }
            if (best) {
                ufo->mCombatant.SetTarget(&best->mCombatant);
                return false;
            }
        }
        break;
    }
    case 1: {
        float radius = (player->GetSize() + 1.0f) * kOrbitRadiusScale;
        if (!bothInFlight || GameModeManager()->IsPaused()) {
            ufo->mOrbitTimer.Reset();
            Vector3 dest;
            dest.x = ufo->mOrbitAxis.x * radius + playerPos.x;
            dest.y = playerPos.y + ufo->mOrbitAxis.y * radius;
            dest.z = playerPos.z + ufo->mOrbitAxis.z * radius;
            ufo->SetDestination(&dest);
        } else {
            cSPTimer& timer = ufo->mOrbitTimer;
            if (!timer.IsRunning())
                timer.Restart();
            unsigned __int64 elapsed = timer.GetElapsedTime();
            int period = ufo->mOrbitPeriod + kOrbitPeriodBias;
            float t = (float)elapsed * 0.001f;

            const Vector3& axis = ufo->mOrbitAxis;
            Vector3 tmp;
            const Vector3* pUp;
            if (axis.z * kZAxis.z + axis.y * kZAxis.y + axis.x * kZAxis.x < 0.99998474f) {
                float d = axis.x * kZAxis.x + axis.y * kZAxis.y + axis.z * kZAxis.z;
                Vector3 p;
                p.x = kZAxis.x - d * axis.x;
                p.y = kZAxis.y - d * axis.y;
                p.z = kZAxis.z - d * axis.z;
                pUp = normalized_safe(&tmp, &p);
            } else {
                pUp = &kYAxis;
            }
            Vector3 up = *pUp;

            float fPeriod = (float)period;
            float angle = -((t * gOrbitSpeed) / (fPeriod * kOrbitPeriodScale));
            Vector3 neg;
            neg.x = -axis.x;
            neg.y = -axis.y;
            neg.z = -axis.z;
            Vector3 c;
            c.x = neg.y * up.z - neg.z * up.y;
            c.y = up.x * neg.z - neg.x * up.z;
            c.z = neg.x * up.y - up.x * neg.y;
            Vector3 side;
            normalized_safe(&side, &c);
            float r = sinf(fPeriod * angle) * kOrbitWobble;
            float ca = cosf(angle) * r;
            float sa = sinf(angle) * r;
            Vector3 n;
            n.x = up.x * ca + axis.x + side.x * sa;
            n.y = axis.y + ca * up.y + sa * side.y;
            n.z = axis.z + ca * up.z + sa * side.z;
            Vector3 dir;
            normalized_safe(&dir, &n);

            Vector3 dest;
            dest.x = dir.x * radius + playerPos.x;
            dest.y = playerPos.y + dir.y * radius;
            dest.z = playerPos.z + dir.z * radius;
            ufo->SetDestination(&dest);

            Vector3 facing;
            facing.x = -dir.x;
            facing.y = -dir.y;
            facing.z = -dir.z;
            Quaternion q;
            QuaternionFromFacingAndUp(&q, &facing, &up);
            ufo->SetOrientation(&q);
            ufo->PopToDestination();
        }

        if (hostile) {
            Vector3 pos = *ufo->mSpatial.GetPosition();
            cSPGameDataUFO* best = player;
            float bestDist = 3.402823466e+38F;
            for (cSPGameDataUFO** it = mUFOsBegin; it != mUFOsEnd; ++it) {
                cSPGameDataUFO* other = *it;
                if (other->mState == 3) {
                    const Vector3* op = other->mSpatial.GetPosition();
                    float dz = pos.z - op->z;
                    float dy = pos.y - op->y;
                    float dx = pos.x - op->x;
                    float d = dz * dz + dy * dy + dx * dx;
                    if (d < bestDist) {
                        bestDist = d;
                        best = other;
                    }
                }
            }
            if (best) {
                ufo->mCombatant.SetTarget(&best->mCombatant);
                return false;
            }
        } else {
            if (!atWar) {
                ufo->mState = 6;
                Vector3 tmp;
                const Vector3* n = normalized_safe(&tmp, ufo->mSpatial.GetPosition());
                Vector3 dest;
                dest.x = n->x * 3000.0f;
                dest.y = n->y * 3000.0f;
                dest.z = n->z * 3000.0f;
                ufo->SetDestination(&dest);
            }
            return false;
        }
        break;
    }
    default:
        return false;
    }

    ufo->mCombatant.SetTarget(0);
    return false;
}
