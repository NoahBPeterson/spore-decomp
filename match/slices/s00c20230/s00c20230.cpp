// Slice s00c20230 -- SP::cSPCreatureBase::ApplyAttackEffect (0x00c20230, 3676 bytes).
// ModAPI: Simulator::cCreatureBase::funcB8h(cCombatant* target, int abilityIndex, Vector3* hitPosition),
// vtable slot 0xb8.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the AutoRefCount / vector locals have no EH frame).
//
// Applies one attack of ability <abilityIndex> to <target>:
//  * computes the damage (raze damage against tribe buildings, species bonus, baby / age /
//    stealth / random / herd / damage-boost / adventure multipliers, the target's armor boost),
//  * runs the ability-type special (mind-melded posse member, knock back, interrupt a charge,
//    "attacked" slot message),
//  * deals the damage to the target and to every combatant inside the area of effect (with a
//    reaction animation for animals),
//  * rolls each combat effect of the ability (extra damage, stun, motive effect, cone damage
//    or cone stun) and plays its effect on the target creature,
//  * makes the target play the follower animation that answers the attacker's animation.
// Returns true when the target is dead afterwards.
// Member names from ModAPI cCreatureBase.h / cCreatureAbility.h / cCombatant.h / cSpatialObject.h.
#include "types.h"
#include <stddef.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define CHECK_OFFSET(T, m, off) typedef char PVCAT(check_, __COUNTER__)[offsetof(T, m) == (off) ? 1 : -1]

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; }
};
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float f) { return Vector3(a.x * f, a.y * f, a.z * f); }

struct BoundingBox {
    Vector3 mMin;
    Vector3 mMax;
    Vector3 GetCenter() const
    {
        return Vector3((mMin.x + mMax.x) * 0.5f, (mMin.y + mMax.y) * 0.5f, (mMin.z + mMax.z) * 0.5f);
    }
};

// SSE max/min helpers of this module (maxss/minss through inline asm).
inline float Max0(float value)
{
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, value
        movss value, xmm0
    }
    return value;
}
inline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}
inline double Clamp(double value, double minValue, double maxValue)
{
    return value >= maxValue ? maxValue : (minValue > value ? minValue : value);
}

Vector3 normalized_safe(const Vector3& v);                                        // 0x00449c20
float RandomFloatRange(float a, float b);                                         // 0x00572a10

extern Vector3 sZeroVector;              // 0x0168d910
extern char sGameModeAdventure;          // 0x01654c10
extern float sBabyAttackerDamageScale;   // 0x01582e78 (1.5)
extern float sAdultDamageScale;          // 0x0150c888 (0.25, attacker not adult)
extern float sStealthDamageScale;        // 0x01582ee0 (1.5)
extern float sDamageRandomMin;           // 0x01582ed8 (0.8)
extern float sDamageRandomMax;           // 0x01582edc (1.0)
extern float sBabyTargetDamageScale;     // 0x01582ee4 (1.0)
extern float sKnockbackScale;            // 0x01582ed0 (10.0)

enum {
    kTribeTool        = 0x018c8f0c,
    kTribeHut         = 0x01e4daae,
    kTribeFood        = 0x018c6de8,
    kTribeTotem       = 0x070703b3,
    kCreatureAnimal   = 0x018eb45e,
    kCreatureBaseType = 0xce9f6639,
    kCombatantType    = 0x013f94d4,
    kCreatureAnimalType = 0xd0036e08,
};

namespace EA { namespace Random {
class RandomLinearCongruential {
public:
    double RandomDoubleUniform();                                                 // 0x009360d0
};
}}
extern EA::Random::RandomLinearCongruential sMathRandom;                          // 0x01601760

struct PropertyList;
float GetPropertyFloat(PropertyList* list, uint32_t id, float defaultValue);      // 0x004e1c70 GetPropertyT<float>

// App message with a 10-dword payload (MessageBasicRC<5>, size 0x3c).
struct SlotMessage {
    uint32_t pad00[2];
    uint32_t mData[10];          // 0x08
    uint32_t mId;                // 0x30
    uint32_t pad34[2];
    SlotMessage(uint32_t id);    // 0x00421c80
    ~SlotMessage();              // 0x00421cf0
};
class IMessageServer {
public:
    PV4 PV
    virtual void PostMSG(uint32_t id, void* msg, int);   // 0x14
};
IMessageServer* MessageServer();                                                  // 0x0067dcc0

struct XformMsg {
    XformMsg();                                        // 0x00434040
    void SetPosition(const Vector3& v);                // 0x00571d40
    uint32_t pad[0x38 / 4];
};
class cIVisualEffect {
public:
    virtual int AddRef();                              // 0x00
    virtual int Release();                             // 0x04
    virtual void Start(int);                           // 0x08
    PV2 PV
    virtual void SetTransform(const XformMsg& xform);  // 0x18
};
struct IVisualEffectPtr {
    cIVisualEffect* mpObject;
    IVisualEffectPtr() : mpObject(0) {}
    ~IVisualEffectPtr() { if (mpObject) mpObject->Release(); }
    cIVisualEffect* operator->() const { return mpObject; }
    cIVisualEffect** AsPPTypeParam();                  // 0x00a16f40
};
class cEffectsManager {
public:
    PV8 PV2 PV
    virtual bool CreateVisualEffect(uint32_t id, int, cIVisualEffect** dst);   // 0x2c
};
cEffectsManager* EffectsManager();                                                // 0x0067ddd0

namespace SP {

class cGameData;
class cCombatant;
class cSPCreatureBase;

class cSpatialObject {
public:
    PV8 PV2 PV                                         // 0x00-0x28
    virtual const Vector3& GetPosition();              // 0x2c
    PV8 PV2
    virtual bool IsPlayerOwned();                      // 0x58
    virtual Vector3 GetDirection();                    // 0x5c
    PV2 PV
    virtual BoundingBox GetBoundingBox();              // 0x6c
    PV
    virtual float GetFootprintRadius();                // 0x74
    PV16
    virtual void* Cast(uint32_t type);                 // 0xb8
    virtual int AddRef();                              // 0xbc
    virtual int Release();                             // 0xc0
};

class cLocomotiveObject : public cSpatialObject {
public:
    void AddVelocity(const Vector3& v, int flags);     // 0x00c446d0
};

// EA::AutoRefCount<cSpatialObject>
struct cSpatialObjectPtr {
    cSpatialObject* mpObject;
    cSpatialObjectPtr(cSpatialObject* p) : mpObject(p) { if (p) p->AddRef(); }
    ~cSpatialObjectPtr() { if (mpObject) mpObject->Release(); }
};

inline void destruct(cSpatialObjectPtr* first, cSpatialObjectPtr* last)
{
    for (; first < last; ++first)
        first->~cSpatialObjectPtr();
}

// eastl::vector<cSpatialObjectPtr, sp_vector_allocator>
struct SpatialObjectVectorBase {
    cSpatialObjectPtr* mpBegin;
    cSpatialObjectPtr* mpEnd;
    cSpatialObjectPtr* mpCapacity;
};
cSpatialObjectPtr* unique(cSpatialObjectPtr* first, cSpatialObjectPtr* last);   // 0x00c0fc40 (eastl::unique)
struct SpatialObjectVector : SpatialObjectVectorBase {
    SpatialObjectVector() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~SpatialObjectVector()
    {
        destruct(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
    void push_back(const cSpatialObjectPtr& value);                      // 0x00afc470
    cSpatialObjectPtr* erase(cSpatialObjectPtr* first, cSpatialObjectPtr* last);   // 0x00b48e40
    cSpatialObjectPtr& operator[](int i) { return mpBegin[i]; }
};
// eastl::fixed_vector<cSpatialObjectPtr, 8>
struct FixedSpatialObjectVector : SpatialObjectVectorBase {
    uint32_t mOverflowAllocator[2];
    uint32_t mNodeCount;
    cSpatialObject* mBuffer[8];
    FixedSpatialObjectVector()
    {
        mNodeCount = 0;
        mpBegin = (cSpatialObjectPtr*)mBuffer;
        mpEnd = (cSpatialObjectPtr*)mBuffer;
        mpCapacity = (cSpatialObjectPtr*)mBuffer + 8;
    }
    ~FixedSpatialObjectVector();                                         // 0x00ad92d0
};

typedef bool (*ObjectFilter)(cSpatialObject* obj, void* context);
bool ConeFilter(cSpatialObject* obj, void* context);                     // 0x00d9a9c0
class cObjectQuery {
public:
    PV16 PV2
    virtual bool GetObjectsInRadius(const Vector3& center, float radius, SpatialObjectVectorBase& dst,
                                    bool b, ObjectFilter filter, void* context);   // 0x48
};
cObjectQuery* ObjectQuery();
void* GetCurrentGameMode();                                              // 0x00b5b800                                             // 0x00b3d240

class cGameData {
public:
    PV2 PV
    virtual void* Cast(uint32_t type);                 // 0x0c
    PV4
    virtual uint32_t GetNounID();                      // 0x20
    PV8 PV2
    virtual uint32_t GetPoliticalID();                 // 0x4c
};

class cCombatant {
public:
    PV2
    virtual cSpatialObject* ToSpatialObject();         // 0x08
    virtual cGameData* ToGameData();                   // 0x0c
    virtual uint32_t GetPoliticalID();                 // 0x10
    PV
    virtual int TakeDamage(float damage, uint32_t attackerPoliticalID, int damageType,
                           const Vector3& direction, cCombatant* pAttacker);   // 0x18
    PV16
    virtual void* Cast(uint32_t type);                 // 0x5c

    int GetDamageState();                              // 0x008e7f80

    uint32_t pad004[(0x568 - 4) / 4];
};

struct cCreatureAbility {
    uint32_t pad00[2];
    int mType;                       // 0x08
    uint32_t pad0c[(0x3c - 0x0c) / 4];
    float mDamage;                   // 0x3c
    float mRangedDamage;             // 0x40
    float mRazeDamage;               // 0x44
    uint32_t* mAnimationIDsBegin;    // 0x48
    uint32_t* mAnimationIDsEnd;      // 0x4c
    uint32_t pad50[3];
    uint32_t* mFollowerAnimationIDsBegin;   // 0x5c
    uint32_t* mFollowerAnimationIDsEnd;     // 0x60
    uint32_t pad64[(0x7c - 0x64) / 4];
    int mEffectKind;                 // 0x7c
    float mEffectDuration;           // 0x80
    float mEffectDamage;             // 0x84
    uint32_t pad88[3];
    float mConeDist;                 // 0x94
    float mConeRadius;               // 0x98
    uint32_t pad9c[(0xb8 - 0x9c) / 4];
    uint32_t* mCombatEffectTypesBegin;          // 0xb8
    uint32_t* mCombatEffectTypesEnd;            // 0xbc
    uint32_t padc0[3];
    float* mCombatEffectPercentagesBegin;       // 0xcc
    uint32_t padd0[4];
    uint32_t* mCombatEffectEffectIdsBegin;      // 0xe0
    uint32_t* mCombatEffectEffectIdsEnd;        // 0xe4
    uint32_t pade8[3];
    float mRushingRange;             // 0xf4
    uint32_t mRushingAnimationID;    // 0xf8
    uint32_t padfc[(0x11c - 0xfc) / 4];
    float mAreaOfEffect;             // 0x11c
    uint32_t mReactionAnimation;     // 0x120
    uint32_t mReactionDeathAnimation;   // 0x124
    uint32_t mReactionLiveAnimation;    // 0x128
    float mReactionDuration;         // 0x12c
    PropertyList* mpPropList;        // 0x130

    bool IsRushing();                // 0x00c0b000
};
CHECK_OFFSET(cCreatureAbility, mFollowerAnimationIDsBegin, 0x5c);
CHECK_OFFSET(cCreatureAbility, mCombatEffectPercentagesBegin, 0xcc);
CHECK_OFFSET(cCreatureAbility, mCombatEffectEffectIdsBegin, 0xe0);
CHECK_OFFSET(cCreatureAbility, mpPropList, 0x130);

struct cSpeciesProfile { uint32_t pad[0x63c / 4]; float mDamageBonus; };   // 0x63c

struct cAnimRequest { uint32_t pad[3]; int mMode; };   // 0x0c
struct cAnimRequestOut { uint32_t pad[5]; uint32_t mLiveAnimation; uint32_t mDeathAnimation; };   // 0x14, 0x18
struct cCreatureAnimator {
    cAnimRequest* PlayIdleAnimation(int flags, int);   // 0x00bc96a0
};
struct cBehaviorData {
    uint32_t pad00[2];
    cCreatureAnimator mAnimator;       // 0x08
};

struct cMotiveEffect {
    float mRate;                       // 0x00
    float mValue;                      // 0x04
    float mDamage;                     // 0x08
    int mType;                         // 0x0c
    uint32_t pad10[7];
    float mDuration;                   // 0x2c
};
struct cMotiveEffects {
    int Find(int, int, cSPCreatureBase* target, cSPCreatureBase* source);                   // 0x00bca0c0
    int Add(int, int, cSPCreatureBase* target, float duration, int, cSPCreatureBase* source);   // 0x00bca810
    cMotiveEffect* Get(int index);                                                            // 0x00bc9a50
};

class cEffectObject {
public:
    PV2
    virtual void Start(int);                           // 0x08
};

struct cHerd { uint32_t pad[0x158 / 4]; float mDamageScale; };            // 0x158
struct cAdventureData { uint32_t pad[0x494 / 4]; float mDamageScale; };   // 0x494
struct cHungerData { uint8_t pad[0x388]; bool mbBusy; };                  // 0x388

class cSPCreatureAnimal;
class cSPCreatureBase;
class cCreatureAnimal {
public:
    uint8_t pad000[0x137];
    bool field_137;                                    // 0x137
    uint8_t pad138[0xb58 - 0x138];
    uint32_t mGeneralFlags;                            // 0xb58

    cHerd* GetHerd();                                  // 0x00c04590
    cAdventureData* GetAdventureData();                // 0x00c04750
    cAnimRequestOut* PlayAnimation(int, int, int, int, float duration, int, int, uint32_t animID,
                                   int, int, int);     // 0x00c0bf10
};
cCreatureAnimal* GameDataCast(cSPCreatureBase* obj, uint32_t noun);       // 0x00ac80d0
cSPCreatureAnimal* interface_cast_Animal(cSPCreatureBase* obj);           // 0x00ac8960

class cPosseSimulator {
public:
    static cPosseSimulator* Instance();                // 0x00d539d0
    void AddPosseMember(cSPCreatureAnimal* animal);    // 0x00d54330
};

class cSPCreatureBase {
public:
    PV2 PV
    virtual void* Cast(uint32_t type);                 // 0x0c
    PV4
    virtual uint32_t GetNounID();                      // 0x20
    PV8 PV2
    virtual uint32_t GetPoliticalID();                 // 0x4c
    PV16 PV
    virtual void func94h(float duration);              // 0x94
    PV4 PV2
    virtual int GetAbilitiesCount();                   // 0xb0
    virtual cCreatureAbility* GetAbility(int index);   // 0xb4
    virtual bool ApplyAttackEffect(cCombatant* target, uint32_t abilityIndex, Vector3* hitPosition);   // 0xb8
    PV4 PV
    virtual bool IsDefaultSpecies();                   // 0xd0

    void SetStealthed(bool, bool);                     // 0x00c1aed0
    bool IsPlayerControlled();                         // 0x00c0c0e0
    cEffectObject* CreateEffect(uint32_t effectID);    // 0x00c1d290
    uint32_t GetCurrentAnimationGUID();                // 0x00c0e040
    void InterruptAnimation(uint32_t animID, int, int);    // 0x00c12310

    bool IsBaby() const { return (mGeneralFlags >> 9) & 1; }

    uint32_t pad004[(0xc0 - 4) / 4];
    cLocomotiveObject mLoco;                           // 0xc0
    uint32_t pad0c4[(0x5a8 - 0xc4) / 4];
    cCombatant mCombatant;                             // 0x5a8
    bool mHasDamageBoost;                              // 0xb10
    float mDamageBoostAmount;                          // 0xb14
    bool mHasArmorBoost;                               // 0xb18
    float mArmorBoostAmount;                           // 0xb1c
    cSpeciesProfile* mpSpeciesProfile;                 // 0xb20
    uint32_t padb24[(0xb34 - 0xb24) / 4];
    int mAge;                                          // 0xb34
    uint32_t padb38[(0xb48 - 0xb38) / 4];
    cMotiveEffects* field_B48;                         // 0xb48
    cBehaviorData* field_B4C;                          // 0xb4c
    uint32_t padb50[2];
    uint32_t mGeneralFlags;                            // 0xb58
    uint8_t padb5c[0xbb1 - 0xb5c];
    bool mbStealthed;                                  // 0xbb1
    uint8_t padbb2[0xe68 - 0xbb2];
    bool mbMindMelded;                                 // 0xe68
    int field_E6C;                                     // 0xe6c
    uint32_t pade70[(0xe84 - 0xe70) / 4];
    cHungerData* field_E84;                            // 0xe84
    uint32_t field_E88;
    uint32_t mCurrentAttackIdx;                        // 0xe8c
    uint32_t mCurrentAttackAnimId;                     // 0xe90
};
CHECK_OFFSET(cSPCreatureBase, mLoco, 0xc0);
CHECK_OFFSET(cSPCreatureBase, mCombatant, 0x5a8);
CHECK_OFFSET(cSPCreatureBase, mHasDamageBoost, 0xb10);
CHECK_OFFSET(cSPCreatureBase, mpSpeciesProfile, 0xb20);
CHECK_OFFSET(cSPCreatureBase, mAge, 0xb34);
CHECK_OFFSET(cSPCreatureBase, field_B48, 0xb48);
CHECK_OFFSET(cSPCreatureBase, mGeneralFlags, 0xb58);
CHECK_OFFSET(cSPCreatureBase, mbStealthed, 0xbb1);
CHECK_OFFSET(cSPCreatureBase, mbMindMelded, 0xe68);
CHECK_OFFSET(cSPCreatureBase, field_E84, 0xe84);
CHECK_OFFSET(cSPCreatureBase, mCurrentAttackAnimId, 0xe90);

} // namespace SP

namespace SP {

// 0x00c0c0e0 (same translation unit: inlined at one call site, and the other relies on ECX surviving it)
bool cSPCreatureBase::IsPlayerControlled()
{
    cHungerData* p = field_E84;
    return p != 0 && p->mbBusy != 0;
}

// 0x00c0b190 (same translation unit: the caller relies on it leaving ECX alone).
__declspec(noinline) bool CanPlayReaction(cCreatureAnimal* animal, cCreatureAbility* ability)
{
    if (animal && (!((animal->mGeneralFlags >> 9) & 1) || ability->mType != 0x3d) &&
        ability->mReactionAnimation != (uint32_t)-1)
        return true;
    return false;
}

// @ 0x00c20230
bool cSPCreatureBase::ApplyAttackEffect(cCombatant* target, uint32_t abilityIndex, Vector3* hitPosition)
{
    if (!target || abilityIndex >= (uint32_t)GetAbilitiesCount())
        return false;

    bool bAdventure = GetCurrentGameMode() == &sGameModeAdventure;
    cCreatureAbility* ability = GetAbility(abilityIndex);
    float damage = Max0(ability->mDamage);
    cSPCreatureBase* targetCreature = (cSPCreatureBase*)target->Cast(kCreatureBaseType);

    switch ((int)target->ToGameData()->GetNounID())
    {
    case kTribeHut:
    case kTribeFood:
    case kTribeTool:
    case kTribeTotem:
        damage = ability->mRazeDamage;
        break;
    }

    if (ability->mEffectKind == 0)
        damage += mpSpeciesProfile->mDamageBonus;
    if (IsBaby())
        damage *= sBabyAttackerDamageScale;
    if (mAge != 1)
        damage *= sAdultDamageScale;

    int type = ability->mType;
    if (targetCreature && mbStealthed && (type == 0x1e || type == 0x21))
    {
        damage *= sStealthDamageScale;
        IVisualEffectPtr effect;
        if (EffectsManager()->CreateVisualEffect(0x10907a60, 0, effect.AsPPTypeParam()))
        {
            XformMsg xform;
            xform.SetPosition(targetCreature->mLoco.GetPosition());
            effect->SetTransform(xform);
            effect->Start(0);
        }
    }
    SetStealthed(false, false);

    if (!bAdventure)
        damage *= RandomFloatRange(sDamageRandomMin, sDamageRandomMax);

    if (!IsDefaultSpecies())
    {
        cCreatureAnimal* animal = GameDataCast(this, kCreatureAnimal);
        if (animal && animal->GetHerd())
            damage *= animal->GetHerd()->mDamageScale;
    }
    if (targetCreature && targetCreature->mAge == 0)
        damage *= sBabyTargetDamageScale;
    if (mHasDamageBoost)
        damage *= mDamageBoostAmount;
    if (bAdventure)
    {
        cAdventureData* data = ((cCreatureAnimal*)Cast(kCreatureAnimalType))->GetAdventureData();
        if (data)
            damage *= data->mDamageScale;
    }
    if (targetCreature && targetCreature->mHasArmorBoost)
        damage /= targetCreature->mArmorBoostAmount;

    switch (ability->mType)
    {
    case 0x49:
    {
        cSPCreatureAnimal* animal = interface_cast_Animal(targetCreature);
        if (animal)
        {
            targetCreature->mbMindMelded = true;
            targetCreature->field_E6C = 15000;
            cPosseSimulator::Instance()->AddPosseMember(animal);
        }
        break;
    }
    case 0x1d:
    {
        SlotMessage msg(0);
        msg.mData[0] = (uint32_t)target;
        MessageServer()->PostMSG(0x3ec1631, &msg, 0);
        break;
    }
    case 0x1f:
        if (targetCreature && !targetCreature->IsBaby())
        {
            const Vector3& position = mLoco.GetPosition();
            Vector3 direction = normalized_safe(targetCreature->mLoco.GetPosition() - position);
            float strength = Clamp(ability->mDamage * 0.01f, 0.1f, 1.0f);
            Vector3 impulse = direction * strength * sKnockbackScale;
            targetCreature->mLoco.AddVelocity(impulse, 0);
        }
        break;
    case 0x20:
        if (targetCreature && targetCreature->mCurrentAttackIdx != (uint32_t)-1)
        {
            cCreatureAbility* targetAbility = targetCreature->GetAbility(targetCreature->mCurrentAttackIdx);
            if (targetAbility && targetAbility->mType == 0x1f)
                targetCreature->func94h(ability->mEffectDuration);
        }
        break;
    }

    SpatialObjectVector objects;
    {
        cSpatialObjectPtr targetObject(target->ToSpatialObject());
        objects.push_back(targetObject);
    }
    if (ability->mAreaOfEffect > 0.0f)
    {
        Vector3 center(target->ToSpatialObject()->GetPosition());
        if (hitPosition)
            center = *hitPosition;
        ObjectQuery()->GetObjectsInRadius(center, ability->mAreaOfEffect, objects, true, 0, 0);
        objects.erase(unique(objects.mpBegin, objects.mpEnd), objects.mpEnd);
    }

    uint32_t politicalID = GetPoliticalID();
    int count = objects.mpEnd - objects.mpBegin;
    for (int i = 0; i < count; i++)
    {
        cSpatialObject* object = objects[i].mpObject;
        if (!object)
            continue;
        cCombatant* combatant = (cCombatant*)object->Cast(kCombatantType);
        if (!combatant || combatant == &mCombatant)
            continue;
        if (bAdventure && politicalID == combatant->ToGameData()->GetPoliticalID())
            continue;

        bool bWasDead = combatant->GetDamageState() == 2;
        combatant->TakeDamage(damage, GetPoliticalID(), 2, sZeroVector, &mCombatant);
        if (bAdventure && IsBaby())
        {
            SlotMessage msg(0x7c63e20);
            *(float*)&msg.mData[0] = damage;
            MessageServer()->PostMSG(msg.mId, &msg, 0);
        }

        cCreatureAnimal* animal = (cCreatureAnimal*)combatant->Cast(kCreatureAnimalType);
        if (animal && !bWasDead && CanPlayReaction(animal, ability) &&
            (ability->mType != 0x3d || animal->field_137))
        {
            cAnimRequestOut* request = animal->PlayAnimation(0, 0x20000, 0x1000, 0, ability->mReactionDuration,
                                                             0, 0x4000000, ability->mReactionAnimation, 0, 0, 0);
            request->mLiveAnimation = ability->mReactionLiveAnimation;
            request->mDeathAnimation = ability->mReactionDeathAnimation;
        }
    }

    bool bDead = target->GetDamageState() == 2;
    int effectCount = ability->mCombatEffectTypesEnd - ability->mCombatEffectTypesBegin;
    for (int i = 0; i < effectCount; i++)
    {
        float chance = ability->mCombatEffectPercentagesBegin[i];
        int effectType = ability->mCombatEffectTypesBegin[i];
        if (!(chance > 0.0f))
            continue;
        if (!(Clamp(sMathRandom.RandomDoubleUniform(), 0.0, 1.0) <= chance))
            continue;

        switch (effectType)
        {
        case 0:
            if (!bDead)
                target->TakeDamage(damage, GetPoliticalID(), 2, sZeroVector, &mCombatant);
            break;
        case 1:
            if (!bDead && targetCreature && !targetCreature->IsPlayerControlled())
            {
                targetCreature->func94h(ability->mEffectDuration);
                if (ability->mType == 0x3a)
                {
                    cAnimRequest* request = targetCreature->field_B4C->mAnimator.PlayIdleAnimation(0x1000, 0);
                    if (request)
                        request->mMode = 2;
                }
            }
            break;
        case 2:
            if (!bDead && targetCreature)
            {
                int index = targetCreature->field_B48->Find(0, 0, targetCreature, this);
                if (index == -1)
                    index = targetCreature->field_B48->Add(0, 0, targetCreature, ability->mEffectDuration, 0, this);
                cMotiveEffect* motive = targetCreature->field_B48->Get(index);
                if (motive)
                {
                    motive->mRate = 0.25f;
                    motive->mValue = 0.0f;
                    motive->mDamage = ability->mEffectDamage;
                    motive->mType = ability->mType;
                    motive->mDuration = ability->mEffectDuration;
                }
            }
            break;
        case 3:
        case 4:
        {
            float reach = mLoco.GetFootprintRadius() + ability->mConeDist;
            Vector3 offset = mLoco.GetDirection() * reach;
            Vector3 center = mLoco.GetBoundingBox().GetCenter() + offset;
            FixedSpatialObjectVector hits;
            bool bFound = ObjectQuery()->GetObjectsInRadius(center, ability->mConeRadius, hits, false, ConeFilter, this);
            uint32_t targetPoliticalID = target->GetPoliticalID();
            bool bStun = effectType == 4;
            if (bFound)
            {
                float coneDamage = GetPropertyFloat(ability->mpPropList, 0x564f152, 1.0f) * damage;
                uint32_t hitCount = hits.mpEnd - hits.mpBegin;
                for (uint32_t j = 0; j < hitCount; j++)
                {
                    cSpatialObject* object = hits.mpBegin[j].mpObject;
                    if (!object)
                        continue;
                    cSPCreatureBase* creature = (cSPCreatureBase*)object->Cast(kCreatureBaseType);
                    if (!creature || creature == targetCreature)
                        continue;
                    if (mLoco.IsPlayerOwned() && creature->mLoco.IsPlayerOwned())
                        continue;
                    if (creature->GetPoliticalID() != targetPoliticalID)
                        continue;
                    if (creature->mpSpeciesProfile == mpSpeciesProfile)
                        continue;
                    if (bStun)
                    {
                        creature->func94h(ability->mEffectDuration);
                        if (ability->mType == 0x3a)
                        {
                            cAnimRequest* request = creature->field_B4C->mAnimator.PlayIdleAnimation(0x1000, 0);
                            if (request)
                                request->mMode = 2;
                        }
                    }
                    else
                    {
                        creature->mCombatant.TakeDamage(coneDamage, GetPoliticalID(), 2, sZeroVector, 0);
                    }
                }
            }
            break;
        }
        default:
            continue;
        }

        if (i < ability->mCombatEffectEffectIdsEnd - ability->mCombatEffectEffectIdsBegin && targetCreature)
        {
            cEffectObject* effect = targetCreature->CreateEffect(ability->mCombatEffectEffectIdsBegin[i]);
            if (effect)
                effect->Start(0);
        }
    }

    bool bTargetDead = target->GetDamageState() == 2;
    if (!bTargetDead && targetCreature && !targetCreature->IsPlayerControlled())
    {
        cSPCreatureBase* creature = (cSPCreatureBase*)target->Cast(kCreatureBaseType);
        if (creature && creature->mCurrentAttackIdx == (uint32_t)-1)
        {
            uint32_t animID = mCurrentAttackAnimId;
            if (animID != (uint32_t)-1)
            {
                uint32_t numAnims = ability->mAnimationIDsEnd - ability->mAnimationIDsBegin;
                uint32_t numFollowers = ability->mFollowerAnimationIDsEnd - ability->mFollowerAnimationIDsBegin;
                uint32_t index;
                if (ability->IsRushing() && animID == ability->mRushingAnimationID)
                {
                    if (numFollowers == 0)
                        goto done;
                    index = 0;
                }
                else
                {
                    if (numAnims != numFollowers)
                        goto done;
                    for (index = 0; index < numAnims; index++)
                        if (ability->mAnimationIDsBegin[index] == animID)
                            break;
                }
                if (index < numFollowers)
                {
                    uint32_t followerAnim = ability->mFollowerAnimationIDsBegin[index];
                    if (creature->GetCurrentAnimationGUID() != followerAnim)
                        creature->InterruptAnimation(followerAnim, -1, 0);
                }
            }
        }
    }
done:
    return bTargetDead;
}

} // namespace SP
