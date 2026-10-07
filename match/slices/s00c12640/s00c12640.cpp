// Slice s00c12640 -- SP::cSPCreatureBase::UpdateRangedAttacks (PDB candidate), 0x00c12640, 3318 bytes.
//
// Per-frame update of a creature's in-flight ranged attacks (spit/throw projectiles). Up to 4 records
// (PDB cSPCreatureBase::cRangedAttack, 0x34 bytes, retail at +0xeb0) are flagged in a bitset<88>
// (retail +0xc04). For every flagged record:
//   kMoving: aim at the target's (scaled) bounding-box centre, or 10 m ahead of the creature when the
//            target has no spatial object; integrate a ballistic step under planet gravity until it
//            dips below the aim height, then home in on the aim point; move the trail effect along.
//            Inside the target's box, a cylinder test against the target's footprint radius turns it
//            into a hit (impact effect, body impulse, attack callback); otherwise it is dropped once
//            it has travelled past the attack range.
//   kHit:    kept until the hit effect stops.
// Dropped records are cleared from the bitset and reset.
//
// Module flags: /O2 /arch:SSE /fp:fast, no EH frame.
#include "types.h"
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    float SquaredLength() const { return x * x + y * y + z * z; }
};
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
inline Vector3 operator*(float s, const Vector3& a) { return Vector3(s * a.x, s * a.y, s * a.z); }
inline Vector3 Cross(const Vector3& a, const Vector3& b)
{
    return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

struct Quaternion {
    float x, y, z, w;
};

struct Matrix3 {
    float m[9];
};

struct BoundingBox {
    Vector3 mMin;
    Vector3 mMax;
    BoundingBox();                                   // 0x00576b40
    void Set(const BoundingBox& other);              // 0x00571d60
};

struct Transform {
    unsigned short mFlags;     // bit0 scaled, bit1 rotated, bit2 translated
    unsigned short mVersion;
    Vector3 mPos;
    float mScale;
    Matrix3 mRot;

    Transform();                                     // 0x00434040
    void SetOffsetOutOfLine(const Vector3& v);       // 0x00571d40
    void SetOffset(const Vector3& v) { mFlags |= 4; mVersion++; mPos = v; }
    void SetScale(float s) { mScale = s; mVersion++; }
    void SetRotation(const Matrix3& m) { mRot = m; mFlags |= 2; mVersion++; }
};

template <typename T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }

// ---- callees (cdecl unless noted) ----
Vector3 normalized_safe(const Vector3& v);                                         // 0x00449c20
Vector3 Vector3_Normalize(const Vector3& v);                                       // 0x00436ce0
Matrix3 Matrix3FromFacingAndUp(const Vector3& facing, const Vector3& up);          // 0x0069b440
Matrix3 Matrix3FromAxes(const Vector3& x, const Vector3& y, const Vector3& z);     // 0x00afa0c0
Vector3 RotateVector(const Vector3& v, const Quaternion& q);                       // 0x0059aed0

extern const Vector3 kUpAxis;                // 0x0168db54

static const uint32_t kGameDataUFO = 0x18ebadc;

namespace EA { namespace Swarm {
struct cIVisualEffect {
    PV2
    virtual void Start(int flags);                   // +0x08
    virtual void Stop(int flags);                    // +0x0c
    virtual bool IsRunning();                        // +0x10
    PV
    virtual void SetTransform(const Transform& t);   // +0x18
    PV
    virtual const Transform& GetTransform(Transform& out); // +0x20
};
} }

struct VisualEffectRef {
    EA::Swarm::cIVisualEffect* mpObject;
    void** AsPPTypeParam();                          // 0x00a16f40
};

struct cEffectsManager {
    PV8 PV2 PV
    virtual bool CreateVisualEffect(uint32_t id, int flags, void** ppEffect);  // +0x2c
};
cEffectsManager* EffectsManager();                   // 0x0067ddd0

struct cPlanetModel {
    float GetGravity();                              // 0x00b7e490
};
namespace SP { cPlanetModel* PlanetModel(); }        // 0x00b3d350

namespace nSPCreatureAnim {
struct creature_instance_data {
    void HitBody(int a, const Vector3* impulse, int b, int c, float d);   // 0x009bb680
};
}

struct cAnimatedCreature {
    uint32_t pad00[0x5f];
    nSPCreatureAnim::creature_instance_data* mpInstanceData;   // +0x17c
};

struct cCreatureAbility {
    uint32_t pad00[0xf];
    float mDamage;                                   // +0x3c
    uint32_t pad40[0x14];
    uint32_t mImpactEffectID;                        // +0x90
    uint32_t pad94[5];
    float mRange;                                    // +0xa8
    uint32_t padAC;
    float mSpeed;                                    // +0xb0
    uint32_t padB4[0x10];
    float mRushingRange;                             // +0xf4
};

struct cSpatialObject {
    PV8 PV2 PV
    virtual const Vector3& GetPosition();            // +0x2c
    virtual const Quaternion& GetOrientation();      // +0x30
    virtual float GetScale();                        // +0x34
    PV8 PV
    virtual Vector3 GetDirection();                  // +0x5c
    PV2
    virtual const BoundingBox& GetLocalExtents();    // +0x68
    virtual BoundingBox GetBoundingBox();           // +0x6c
    PV
    virtual float GetFootprintRadius();              // +0x74
};

struct cGameData {
    PV8
    virtual uint32_t GetNounID();                    // +0x20
    uint32_t pad04[0xc];
    cSpatialObject mSpatial;                         // +0x34 (cGameDataUFO)
};

struct cCombatant {
    PV2
    virtual cSpatialObject* ToSpatialObject();       // +0x08
    virtual cGameData* ToGameData();                 // +0x0c
    PV8 PV8 PV2 PV
    virtual void* Cast(uint32_t type);               // +0x5c
};

struct cTargetCreature {
    PV8 PV2 PV
    virtual bool IsDead();                           // +0x2c
    uint32_t pad04[0x4c];
    uint8_t pad134;
    bool mb135;                                      // +0x135
    uint8_t pad136[0xa1e];
    cAnimatedCreature* mpAnimatedCreature;           // +0xb54
    uint32_t padB58;
    uint8_t padB5C[2];
    bool mbB5E;                                      // +0xb5e
};

struct cRangedAttack {                               // 0x34
    bool mbAlwaysHit;
    bool mbHoming;                                   // +0x01
    int mState;                                      // +0x04 (1 moving, 2 hit)
    Vector3 mPosition;                               // +0x08
    Vector3 mVelocity;                               // +0x14
    uint32_t mAttackIndex;                           // +0x20
    float mDistanceTraveled;                         // +0x24
    cCombatant* mpTarget;                            // +0x28
    EA::Swarm::cIVisualEffect* mpTrailEffect;        // +0x2c
    VisualEffectRef mpHitEffect;                     // +0x30
    void Reset();                                    // 0x00c0f490
};

struct bitset88 {
    uint32_t mWord[3];
    bool any() const
    {
        for (uint32_t i = 0; i < 3; ++i)
            if (mWord[i] != 0)
                return true;
        return false;
    }
    bool test(uint32_t i) const
    {
        if (i < 88)
            return (mWord[i >> 5] & (1 << (i & 31))) != 0;
        return false;
    }
};

float GetAttackRangeScale(int a, struct cCreatureBase* creature);          // 0x00d38a30

struct cCreatureBase {
    PV8 PV8 PV8 PV8 PV8 PV4 PV
    virtual cCreatureAbility* GetAbility(int index);                         // +0xb4
    virtual void OnRangedAttackHit(cCombatant* target, int abilityIndex, Vector3* hitPosition);  // +0xb8
    uint32_t pad04[0x2f];
    cSpatialObject mSpatial;                         // +0xc0
    uint32_t padC4[0x2d0];
    bitset88 mInUseRangedAttackBits;                 // +0xc04
    uint32_t padC10[0xa8];
    cRangedAttack mRangedAttacks[4];                 // +0xeb0

    void UpdateRangedAttacks(float deltaTime);
};

// @ 0x00c12640
void cCreatureBase::UpdateRangedAttacks(float deltaTime)
{
    if (!mInUseRangedAttackBits.any())
        return;
    float rangeScale = GetAttackRangeScale(0, this);
    float gravity = SP::PlanetModel()->GetGravity();
    bitset88 pending = mInUseRangedAttackBits;

    cRangedAttack* attack = &mRangedAttacks[0];
    for (uint32_t i = 0; pending.any() && i < 4; i++, attack++) {
        if (!pending.test(i))
            continue;
        uint32_t word = i >> 5;
        uint32_t clearMask = ~(1 << (i & 31));
        pending.mWord[word] &= clearMask;

        cCombatant* target = attack->mpTarget;
        cTargetCreature* creature = target ? (cTargetCreature*)target->Cast(0xce9f6639) : 0;
        cSpatialObject* targetSpatial = target ? target->ToSpatialObject() : 0;

        bool bRemove;
        switch (attack->mState) {
        case 1:
            if (creature && (creature->mbB5E || !creature->mb135)) {
                bRemove = true;
            } else {
                bRemove = false;
                BoundingBox box;
                float boxScale = 1.0f;
                Vector3 aim;
                if (targetSpatial) {
                    cGameData* gameData;
                    if (target && (gameData = target->ToGameData()) != 0 && gameData->GetNounID() == kGameDataUFO)
                        boxScale = gameData->mSpatial.GetScale();
                    box.Set(targetSpatial->GetBoundingBox());
                    // scale the box about its centre
                    Vector3 center((box.mMax.x + box.mMin.x) * 0.5f, (box.mMax.y + box.mMin.y) * 0.5f,
                                   (box.mMax.z + box.mMin.z) * 0.5f);
                    box.mMin = (box.mMin - center) * boxScale + center;
                    box.mMax = (box.mMax - center) * boxScale + center;
                    aim = (box.mMax + box.mMin) * 0.5f;
                } else {
                    cSpatialObject* self = &mSpatial;
                    const BoundingBox& extents = self->GetLocalExtents();
                    Vector3 up = normalized_safe(self->GetPosition()) * extents.mMax.z;
                    Vector3 ahead = self->GetDirection() * 10.0f;
                    aim = ahead + self->GetPosition() + up;
                }

                Vector3 delta = aim - attack->mPosition;
                float len = delta.Length() + 1e-8f;
                Vector3 dir = delta * (1.0f / len);
                cCreatureAbility* ability = GetAbility(attack->mAttackIndex);
                float step = Min(ability->mSpeed * deltaTime, len);
                attack->mDistanceTraveled += step;

                Vector3 newPos;
                if (!attack->mbHoming || !targetSpatial) {
                    // ballistic step under planet gravity
                    Vector3 up = normalized_safe(attack->mPosition);
                    float g = gravity * deltaTime;
                    attack->mVelocity.x += up.x * g;
                    attack->mVelocity.y += up.y * g;
                    attack->mVelocity.z += up.z * g;
                    newPos.x = attack->mVelocity.x * deltaTime + attack->mPosition.x;
                    newPos.y = deltaTime * attack->mVelocity.y + attack->mPosition.y;
                    newPos.z = attack->mVelocity.z * deltaTime + attack->mPosition.z;
                    attack->mbHoming = newPos.SquaredLength() < aim.SquaredLength();
                }
                if (attack->mbHoming) {
                    Vector3 from;
                    if (attack->mpTrailEffect) {
                        Transform t;
                        from = attack->mpTrailEffect->GetTransform(t).mPos;
                    } else
                        from = attack->mPosition;
                    newPos = dir * step + from;
                }
                if (attack->mpTrailEffect) {
                    Transform t;
                    t.SetOffset(newPos);
                    Transform current;
                    t.SetScale(attack->mpTrailEffect->GetTransform(current).mScale);
                    t.SetRotation(Matrix3FromFacingAndUp(Vector3_Normalize(dir), Vector3_Normalize(newPos)));
                    attack->mpTrailEffect->SetTransform(t);
                }

                if (targetSpatial && newPos.x >= box.mMin.x && box.mMax.x >= newPos.x && newPos.y >= box.mMin.y &&
                    box.mMax.y >= newPos.y && newPos.z >= box.mMin.z && box.mMax.z >= newPos.z) {
                    // cylinder test around the target's up axis
                    Vector3 axis = RotateVector(kUpAxis, targetSpatial->GetOrientation());
                    const Vector3& targetPos = targetSpatial->GetPosition();
                    Vector3 rel = newPos - targetPos;
                    float along = rel.z * axis.z + rel.y * axis.y + rel.x * axis.x;
                    Vector3 perp = rel - axis * along;
                    float radius = targetSpatial->GetFootprintRadius() * boxScale;
                    if (radius * radius >= perp.SquaredLength()) {
                        attack->mState = 2;
                        if (attack->mpTrailEffect)
                            attack->mpTrailEffect->Stop(0);
                        if (EffectsManager()->CreateVisualEffect(ability->mImpactEffectID, 0,
                                                                 attack->mpHitEffect.AsPPTypeParam())) {
                            Transform t;
                            t.SetOffsetOutOfLine(attack->mPosition);
                            Vector3 up = Vector3_Normalize(targetSpatial->GetPosition());
                            Vector3 side = Cross(dir, up);
                            t.SetRotation(Matrix3FromAxes(dir, up, side));
                            attack->mpHitEffect.mpObject->SetTransform(t);
                            attack->mpHitEffect.mpObject->Start(0);
                        }
                        if (creature && !creature->IsDead()) {
                            Vector3 impulse = dir * ability->mDamage * 1000000.0f;
                            creature->mpAnimatedCreature->mpInstanceData->HitBody(0, &impulse, 0, 0, 1.5f);
                        }
                        OnRangedAttackHit(attack->mpTarget, attack->mAttackIndex, &newPos);
                    }
                } else {
                    float reach = mSpatial.GetFootprintRadius() * 2.0f;
                    if (targetSpatial)
                        reach = targetSpatial->GetFootprintRadius() + reach;
                    if (attack->mDistanceTraveled >
                        (ability->mRushingRange + ability->mRange) * rangeScale + reach + 3.0f)
                        bRemove = true;
                }
                attack->mPosition = newPos;
            }
            break;
        case 2:
            bRemove = !attack->mpHitEffect.mpObject || !attack->mpHitEffect.mpObject->IsRunning();
            break;
        default:
            continue;
        }

        if (bRemove) {
            mInUseRangedAttackBits.mWord[word] &= clearMask;
            attack->Reset();
        }
    }
}
