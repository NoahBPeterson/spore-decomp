// Slice s00c91ca0 -- SP::cSpear::Update (0x00c91ca0, 3318 bytes).
//
// Per-frame update of a thrown tribal spear. The function is the cSpear override reached through the
// cProjectile base (ModAPI layout: cGameData @0x00, cLocomotiveObject @0x34, cProjectile @0x504), so
// `this` is the cProjectile subobject and the other bases sit at this-0x504 / this-0x4d0.
//
// It traces the segment from the last position to the current one (CombatLineTest). On a miss it just
// records the position. On a ground hit (result 1) the owner's tribe plants a spear prop where it
// landed, the target (if any) takes the damage, and a "thud" sound plays. On a combatant hit (other
// political ID) it resolves the hit point on the victim's body (bone lookup), turns a tribe ornament
// into a spear stuck in the victim (slot 0x2735290 + n of the victim's attachments), applies damage and
// plays the impact sound. Returns true while the spear keeps flying.
//
// Module flags: /O2 /arch:SSE /fp:fast (scalar SSE math, x87 sqrt), no EH frame.
#include "types.h"
#include <math.h>
#include <float.h>

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
    Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
};
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
inline Vector3 operator-(const Vector3& a) { return Vector3(-a.x, -a.y, -a.z); }

struct Quaternion {
    float x, y, z, w;
};

// Hamilton-style product used by the attachment code: a * conj(b)
__forceinline Quaternion MulConj(const Quaternion& a, const Quaternion& b)
{
    Quaternion r;
    r.x = a.x * b.w - a.w * b.x + a.y * b.z - a.z * b.y;
    r.y = a.y * b.w - a.w * b.y - a.x * b.z + a.z * b.x;
    r.z = a.x * b.y - a.w * b.z - a.y * b.x + a.z * b.w;
    r.w = a.y * b.y + a.z * b.z + a.w * b.w + a.x * b.x;
    return r;
}

struct Matrix3 {
    float m[9];
};

struct Transform {
    unsigned short mFlags;     // bit0 scaled, bit1 rotated, bit2 translated
    unsigned short mVersion;   // bumped on every change
    Vector3 mPos;
    float mScale;
    Matrix3 mRot;

    Transform();                                // 0x00409930
    void RotateY(float angle);                  // 0x004099b0
    void SetRotation(const Matrix3& m) { mRot = m; mFlags |= 2; mVersion++; }
    void SetOffset(const Vector3& v) { mFlags |= 4; mVersion++; mPos = v; }
    void SetScale(float s) { mScale = s; mVersion++; }
};

// ---- callees (cdecl unless noted) ----
Vector3 normalized_safe(const Vector3& v);                                         // 0x00449c20
Quaternion QuaternionFromDirections(const Vector3& from, const Vector3& to);       // 0x00698180
Matrix3 Matrix3FromQuaternion(const Quaternion& q);                                // 0x0059c190
Vector3 RotateByQuaternion(const Quaternion& q, const Vector3& v);                  // 0x0099c310
void Start3dSoundByName(uint32_t name, int system, Vector3 pos);                   // 0x00571f80

extern const float kHalfPi;            // 0x0157aad4
extern const Vector3 kXAxis;           // 0x0157aad8
extern const Vector3 kSpearHitDefault; // 0x01695374
extern const char kCombatantIID[];     // 0x013f94d4

static const uint32_t kSpearSlotBase = 0x2735290;   // first body-attachment slot used for spears

struct IAudioSystem {
    PV8
    virtual int GetHandle();                         // +0x20
};
namespace EA { namespace Audio { IAudioSystem* GetSystemAT(); } }        // 0x00a206f0

struct cSpatialObject;
struct cCombatant;

struct cGameObject {
    PV8 PV8 PV4 PV2 PV
    virtual void* Cast(uint32_t type);               // +0x5c
};

struct IUnknown32 {
    virtual int AddRef();                            // +0x00
    virtual int Release();                           // +0x04
    PV
    virtual void* AsInterface(const void* iid);      // +0x0c
};

struct cSpatialObject : IUnknown32 {};

struct cCombatantData {
    uint32_t pad00[0x1d];
    uint8_t pad74;
    bool mbCanBeDamaged;                             // +0x75
};

struct cCombatant {
    PV2
    virtual cCombatantData* GetData();               // +0x08
    PV
    virtual int GetPoliticalID();                    // +0x10
    PV
    virtual void TakeDamage(float damage, int attackerPoliticalID, int damageType,
                            const Vector3* direction, cCombatant* attacker);   // +0x18
    PV8 PV4 PV2 PV2
    virtual void* Cast(uint32_t type);               // +0x5c
    PV
    virtual void Release();                          // +0x64
};

struct cModel {
    uint32_t pad00[6];
    Vector3 mPosition;                               // +0x18
    uint32_t pad24[6];
    Quaternion mOrientation;                         // +0x3c
    uint32_t pad4c[0xa6];
    char* mpBones;                                   // +0x2e4, records of 0x2bc bytes
};

struct cBone {
    uint32_t pad00[4];
    Vector3 mOffset;                                 // +0x10
    Quaternion mOrientation;                         // +0x1c
};

struct cAttachedModel {
    uint32_t pad00[0x5f];
    cModel* mpModel;                                 // +0x17c
};

struct IEffectOwner {
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV2 PV
    virtual void StopEffect(void* effect, int flags); // +0x16c
};

struct cEffect {
    IEffectOwner* mpOwner;
    void Stop();                                      // 0x00571d90
};

struct cAttachment {
    uint32_t pad00[3];
    Vector3 mOffset;                                 // +0x0c
    Quaternion mOrientation;                         // +0x18
    uint32_t pad28[0x1a];
    cEffect* mpEffect;                               // +0x90
    uint32_t pad94[4];
    IUnknown32* mpObject;                            // +0xa4
};

struct cInteractiveOrnament;
cInteractiveOrnament* interface_cast_Ornament(IUnknown32* const& p);              // 0x00c8ec90

struct cCreatureBase;

struct cAttachmentOwner {
    cAttachment* GetAttachment(uint32_t slot);                                  // 0x00c0dfb0
    void RemoveAttachment(uint32_t slot, int flags);                            // 0x00c15150
};

struct cSpatialPart {
    PV8 PV8
    virtual void SetScale(float scale);              // +0x40
};

struct cInteractiveOrnament {
    PV8 PV4
    virtual int GetModelKey();                       // +0x30
    virtual void AttachTo(cCreatureBase* creature);  // +0x34
    uint32_t pad04[0xc];
    cSpatialPart mSpatial;                           // +0x34
    uint32_t pad38[0x1b];
    uint8_t padA4;
    bool mbA5;                                       // +0xa5
    uint8_t padA6[3];
    bool mbA9;                                       // +0xa9
    uint8_t padAA[0x196];
    int mPriority;                                   // +0x240
    void SetLifetime(float seconds, int flags);      // 0x00c40830
};

struct sSlotRange {
    uint32_t mFirst;
    int mCount;
};

struct cBehaviorTracker {
    int Find(int a, int b, cCreatureBase* c, int d);                               // 0x00bca0c0
    void Add(int a, int b, cCreatureBase* c, float t, const sSlotRange* r, int d);  // 0x00bca810
};

struct cSPSubC0 {
    PV8 PV8 PV2
    virtual bool IsVisible();                        // +0x48
};

struct cCreatureBase : cAttachmentOwner {
    uint32_t pad00[0x30];
    cSPSubC0 mSubC0;                                 // +0xc0
    uint32_t padC4[0x2a1];
    cBehaviorTracker* mpTracker;                     // +0xb48
    uint32_t padB4C[2];
    cAttachedModel* mpAttachedModel;                 // +0xb54
    uint32_t padB58;
    uint8_t padB5C[2];
    bool mbB5E;                                      // +0xb5e
    uint8_t padB5F;
    uint32_t padB60[0xcb];
    int mE8C;                                        // +0xe8c

    bool IsFlagSet();                                                            // 0x00c0c0e0
    void InterruptAnimation(uint32_t anim, int a, int b);                        // 0x00c12310
    void CreateBodyEffect(int bone, int a, cSpatialPart* obj, uint32_t slot);    // 0x00c11f50
};

cCreatureBase* GetCreatureBase(cCombatant* const& p);                           // 0x00c0c3a0
cAttachmentOwner* FindAttachmentOwner(int modelKey);                            // 0x00f19200

struct cPoliticalPart {
    PV8 PV8 PV4 PV2
    virtual bool GetTribeIndex();                    // +0x58
};

struct cTribe {
    uint32_t pad00[0x48];
    cPoliticalPart mPolitical;                       // +0x120
};

struct cCreatureCitizen {
    PV8 PV8 PV2 PV
    virtual int GetPoliticalID();                    // +0x4c
    uint32_t pad04[0x169];
    cCombatant mCombatant;                           // +0x5a8
    cTribe* GetTribe();                              // 0x00c22f50
};

struct cTribeDisplayStrategy {
    int GetGroundSpearIndex(bool tribe);                                                     // 0x00cc89f0
    void SetGroundSpearTransform(bool tribe, int index, const Transform& t, int lifetimeMs);  // 0x00cca9e0
    cInteractiveOrnament* GetSpearOrnament(cTribe* tribe);                                   // 0x00cc98e0
};

struct cTribeModeStrategy {
    static cTribeModeStrategy* Instance();           // 0x00cd40b0
    PV8 PV8 PV8 PV2 PV
    virtual cTribeDisplayStrategy* GetDisplayStrategy(); // +0x6c
};

bool CombatLineTest(const Vector3& start, const Vector3& dir, float length, cSpatialObject** ppHit,
                    Vector3* pHitPos, cGameObject* pIgnore, int flags);              // 0x00cb69e0
bool SweepTestModel(const Vector3& start, const Vector3& dir, cModel* model, int* pBone, int a,
                    Vector3* pHitPos, int b, int c);                                // 0x009b6450

struct cGameDataPart {
    PV8 PV8 PV2 PV
    virtual int GetPoliticalID();                    // +0x4c
};

struct cLocomotivePart {
    PV8 PV2 PV
    virtual const Vector3& GetPosition();            // +0x2c
    virtual const Quaternion& GetOrientation();      // +0x30
    virtual float GetScale();                        // +0x34
    virtual void SetPosition(const Vector3& v);      // +0x38
    PV8 PV4 PV2
    virtual float GetFootprintRadius();              // +0x74
};

// AutoRefCount<cSpatialObject> (no EH: the module is built without /EHsc)
struct SpatialRef {
    cSpatialObject* mpObject;
    SpatialRef() : mpObject(0) {}
    ~SpatialRef() { if (mpObject) mpObject->Release(); }
};

struct CombatantRef {
    cCombatant* mpObject;
    __forceinline CombatantRef& operator=(cCombatant* p)
    {
        if (p != mpObject) {
            cCombatant* const pTemp = mpObject;
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    cCombatant* operator->() const { return mpObject; }
    operator cCombatant*() const { return mpObject; }
};

// cProjectile subobject of cSpear (at +0x504 of the full object).
struct cSpear {
    PV4 PV2
    virtual cGameObject* GetOwner();                 // +0x18
    uint32_t pad04[4];
    Vector3 mLastPosition;                           // +0x14 (cArtilleryProjectile 0x518)
    uint32_t pad20[5];
    float mDamage;                                   // +0x34 (cSpear 0x538)
    CombatantRef mpTarget;                           // +0x38 (cSpear 0x53c)

    cGameDataPart* AsGameData() { return (cGameDataPart*)((char*)this - 0x504); }
    cLocomotivePart* AsLocomotive() { return (cLocomotivePart*)((char*)this - 0x4d0); }

    bool Update();
};

// @ 0x00c91ca0
bool cSpear::Update()
{
    cLocomotivePart* loco = AsLocomotive();
    Vector3 delta = loco->GetPosition() - mLastPosition;
    float dist = delta.Length();
    Vector3 dir = delta;
    if (dist > 0.0f) {
        dir *= 1.0f / dist;
        Vector3 hitPos = kSpearHitDefault;
        SpatialRef hit;
        int result = CombatLineTest(mLastPosition, dir, dist + loco->GetFootprintRadius(), &hit.mpObject,
                                    &hitPos, GetOwner(), 4);
        if (result != 3) {
            cCombatant* victim = hit.mpObject ? (cCombatant*)hit.mpObject->AsInterface(kCombatantIID) : 0;
            if (!victim) {
                if (result == 1) {
                    cGameObject* owner = GetOwner();
                    cCreatureCitizen* thrower;
                    if (owner && (thrower = (cCreatureCitizen*)owner->Cast(0x4f176642)) != 0) {
                        cTribe* tribe = thrower->GetTribe();
                        cTribeDisplayStrategy* display = cTribeModeStrategy::Instance()->GetDisplayStrategy();
                        if (tribe && display) {
                            Vector3 n = normalized_safe(hitPos - loco->GetPosition());
                            Quaternion q = QuaternionFromDirections(kXAxis, -n);
                            int index = display->GetGroundSpearIndex(tribe->mPolitical.GetTribeIndex());
                            if (index >= 0) {
                                Transform t;
                                t.SetRotation(Matrix3FromQuaternion(loco->GetOrientation()));
                                t.RotateY(kHalfPi);
                                t.SetOffset(hitPos);
                                t.SetScale(loco->GetScale());
                                display->SetGroundSpearTransform(tribe->mPolitical.GetTribeIndex(), index, t, 15000);
                            }
                        }
                        Vector3 hitDir = normalized_safe(hitPos - loco->GetPosition());
                        if (mDamage > 0.0f && mpTarget && mpTarget->GetData()->mbCanBeDamaged) {
                            mpTarget->TakeDamage(mDamage, thrower->GetPoliticalID(), 2, &hitDir, &thrower->mCombatant);
                            cCreatureBase* creature = GetCreatureBase(mpTarget.mpObject);
                            if (creature && creature->mE8C == -1 && !creature->mbB5E && !creature->IsFlagSet())
                                creature->InterruptAnimation(0x2c39422, -1, 0);
                            mpTarget = 0;
                        }
                    }
                }
                IAudioSystem* audio = EA::Audio::GetSystemAT();
                Start3dSoundByName(0x3516e5d7, audio ? audio->GetHandle() : 0, hitPos);
                loco->SetPosition(hitPos);
                return false;
            }
            if (AsGameData()->GetPoliticalID() != victim->GetPoliticalID()) {
                int slotCount = 5;
                cGameObject* owner = GetOwner();
                cCreatureCitizen* attacker = owner ? (cCreatureCitizen*)owner->Cast(0x4f176642) : 0;
                cTribe* tribe = attacker->GetTribe();
                cCreatureBase* creature = (cCreatureBase*)victim->Cast(0xce9f6639);
                if (creature) {
                    if (creature->IsFlagSet())
                        slotCount = 20;
                    Vector3 hitDir = normalized_safe(hitPos - loco->GetPosition());
                    Vector3 start = mLastPosition;
                    Vector3 sweepDir = hitDir;
                    Vector3 bodyHit = hitPos;
                    int bone = 0;
                    bool bHitBody = false;
                    if (creature->mSubC0.IsVisible()) {
                        bHitBody = SweepTestModel(start, sweepDir, creature->mpAttachedModel->mpModel, &bone, 0,
                                                  &bodyHit, 0, 0);
                        if (!bHitBody) {
                            mLastPosition = loco->GetPosition();
                            return true;
                        }
                    }
                    if (cTribeModeStrategy::Instance()->GetDisplayStrategy()) {
                        cInteractiveOrnament* ornament =
                            cTribeModeStrategy::Instance()->GetDisplayStrategy()->GetSpearOrnament(tribe);
                        if (ornament) {
                            // detach the ornament from whoever carried it before
                            cAttachmentOwner* prev = FindAttachmentOwner(ornament->GetModelKey());
                            if (prev) {
                                for (uint32_t slot = kSpearSlotBase; slot < kSpearSlotBase + slotCount; slot++) {
                                    cAttachment* a = prev->GetAttachment(slot);
                                    if (a && a->mpObject && ornament == interface_cast_Ornament(a->mpObject)) {
                                        if (a->mpEffect)
                                            a->mpEffect->Stop();
                                        prev->RemoveAttachment(slot, 1);
                                        break;
                                    }
                                }
                            }
                            cSpatialPart* spatial = &ornament->mSpatial;
                            spatial->SetScale(loco->GetScale());

                            // pick a free slot on the victim, else recycle the lowest-priority one
                            uint32_t freeSlot = 0;
                            uint32_t bestSlot = kSpearSlotBase;
                            float bestPriority = FLT_MAX;
                            for (uint32_t slot = kSpearSlotBase; slot < kSpearSlotBase + slotCount; slot++) {
                                cAttachment* a = creature->GetAttachment(slot);
                                if (!a) {
                                    freeSlot = slot;
                                    break;
                                }
                                cInteractiveOrnament* o;
                                if (a->mpObject && (o = interface_cast_Ornament(a->mpObject)) != 0) {
                                    float priority = (float)o->mPriority;
                                    if (priority < bestPriority) {
                                        bestPriority = priority;
                                        bestSlot = slot;
                                    }
                                }
                            }
                            if (!freeSlot)
                                freeSlot = bestSlot;
                            cAttachment* old = creature->GetAttachment(freeSlot);
                            if (old) {
                                cEffect* effect = old->mpEffect;
                                if (effect)
                                    effect->mpOwner->StopEffect(effect, 0);
                                creature->RemoveAttachment(freeSlot, 1);
                            }

                            ornament->AttachTo(creature);
                            ornament->mbA9 = true;
                            ornament->mbA5 = true;
                            ornament->SetLifetime(10.0f, 0);
                            creature->CreateBodyEffect(bone, 0, spatial, freeSlot);

                            cAttachment* att = creature->GetAttachment(freeSlot);
                            if (att) {
                                cModel* model = creature->mpAttachedModel->mpModel;
                                cBone* b = (cBone*)(model->mpBones + bone * 0x2bc);
                                if (bHitBody) {
                                    Vector3 local = RotateByQuaternion(model->mOrientation, bodyHit - model->mPosition);
                                    Vector3 offset = (local - b->mOffset) * 0.5f;
                                    Vector3 r = RotateByQuaternion(b->mOrientation, offset);
                                    att->mOffset.x = r.x;
                                    att->mOffset.y = r.y;
                                    att->mOffset.z = r.z;
                                }
                                Quaternion q = MulConj(loco->GetOrientation(), model->mOrientation);
                                att->mOrientation = MulConj(q, b->mOrientation);
                            }

                            if (creature->mpTracker && creature->mpTracker->Find(2, 0, creature, 0) == -1) {
                                sSlotRange range;
                                range.mFirst = kSpearSlotBase;
                                range.mCount = slotCount;
                                creature->mpTracker->Add(2, 0, creature, FLT_MAX, &range, 0);
                            }
                        }
                    }
                    if (mDamage > 0.0f && mpTarget) {
                        mpTarget->TakeDamage(mDamage, attacker->GetPoliticalID(), 2, &hitDir,
                                             attacker ? &attacker->mCombatant : 0);
                        mpTarget = 0;
                    }
                    IAudioSystem* audio = EA::Audio::GetSystemAT();
                    Start3dSoundByName(0xaa6d7524, audio ? audio->GetHandle() : 0, hitPos);
                }
                loco->SetPosition(hitPos);
                mpTarget = 0;
                return false;
            }
        }
    }
    mLastPosition = loco->GetPosition();
    return true;
}
