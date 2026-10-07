// Slice s00c3cd60 - SP::cSPGameDataUFO::TakeHit (the cCombatant::TakeHit override; `this` is the
// cCombatant subobject at +0x508, members of the full UFO are reached through this-0x508).
// Layout notes: retail offsets follow the ModAPI cGameDataUFO header (cGameData @0, cLocomotiveObject @0x34,
// cCombatant @0x508), not the 2008 PDB.
#include "types.h"
#include <math.h>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3 operator*(float f) const { return Vector3(x * f, y * f, z * f); }
    Vector3 operator+(const Vector3& o) const { return Vector3(x + o.x, y + o.y, z + o.z); }
    Vector3 operator-(const Vector3& o) const { return Vector3(x - o.x, y - o.y, z - o.z); }
    Vector3& operator+=(const Vector3& o) { x += o.x; y += o.y; z += o.z; return *this; }
    Vector3& operator-=(const Vector3& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
    float Dot(const Vector3& o) const { return x * o.x + y * o.y + z * o.z; }
    float SquaredLength() const { return x * x + y * y + z * z; }
};
struct Quaternion { float x, y, z, w; };
struct Matrix3 { float m[9]; };

Vector3 Vector3_Normalize(const Vector3& v);                 // 0x436ce0
Matrix3 Quaternion_ToMatrix(const Quaternion& q);            // 0x4a9b40

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};

// Transform (retail: flags, change count, offset, scale, rotation)
struct Transform {
    int16_t mnFlags;            // +0x00
    int16_t mnTransformCount;   // +0x02
    Vector3 mOffset;            // +0x04
    float   mfScale;            // +0x10
    Matrix3 mRotation;          // +0x14
    Transform();                                // 0x434040
    void SetOffset(const Vector3& v);           // 0x571d40
    void SetScale(float v) { mfScale = v; mnTransformCount++; }
    __forceinline void SetRotation(const Quaternion& q)
    {
        mRotation = Quaternion_ToMatrix(q);
        mnFlags |= 2;
        mnTransformCount++;
    }
};

namespace EA { namespace Swarm {
struct cIVisualEffect {
    virtual int  AddRef() = 0;
    virtual int  Release() = 0;
    virtual void Start(int hardStart) = 0;                                  // 0x08
    virtual int  Stop(int) = 0;
    virtual int  IsRunning() = 0;
    virtual void SetRigidTransform(const Transform& t) = 0;
    virtual void SetSourceTransform(const Transform& t) = 0;                // 0x18
    virtual void v1c() = 0; virtual void v20() = 0; virtual void v24() = 0; virtual void v28() = 0;
    virtual void v2c() = 0; virtual void v30() = 0; virtual void v34() = 0; virtual void v38() = 0;
    virtual void v3c() = 0; virtual bool v40() = 0;
    virtual bool SetFloatParams(int param, const float* data, int count) = 0;   // 0x44
    virtual bool SetIntParams(int param, const int* data, int count) = 0;       // 0x48
};
struct IEffectsManager {
    virtual void v00() = 0; virtual void v04() = 0; virtual void v08() = 0; virtual void v0c() = 0;
    virtual void v10() = 0; virtual void v14() = 0; virtual void v18() = 0; virtual void v1c() = 0;
    virtual void v20() = 0; virtual void v24() = 0; virtual void v28() = 0;
    virtual bool CreateVisualEffect(uint32_t instanceID, uint32_t groupID, cIVisualEffect** dst) = 0;   // 0x2c
};
}}

namespace EA {
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    explicit AutoRefCount(T* p);        // 0x61df40 (tool instance)
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T** AsPPTypeParam();                // 0xa16f40
    T* operator->() const { return mpObject; }
    operator bool() const { return mpObject != 0; }
};
namespace Random {
struct RandomLinearCongruential { double RandomDoubleUniform(); };   // 0x9360d0
}
}

namespace SP {

struct cEmpire {
    uint32_t pad00[0x58 / 4];
    int      mArchetype;        // +0x58
    const ResourceKey& GetUFOKey();     // 0xc326b0
};

struct cGameData {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool IsDestroyed();                     // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual int  GetPoliticalID();                  // 0x4c
    uint32_t pad04[(0x34 - 4) / 4];
};

struct cLocomotiveObject {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3&    GetPosition();        // 0x2c
    virtual const Quaternion& GetOrientation();     // 0x30
    virtual float             GetBoundingRadius();  // 0x34
    uint32_t pad04[(0x4d4 - 4) / 4];
};

struct cSpaceToolData {
    virtual void v00();
    virtual int  AddRef();
    virtual int  Release();
    uint32_t pad04[(0x13c - 4) / 4];
    bool     mbInUse;           // +0x13c
};

struct cCombatant {
    virtual ~cCombatant();
    virtual bool v04();
    virtual void v08();
    virtual cGameData* ToGameData();                // 0x0c
    virtual int  v10();
    virtual void v14();
    virtual void TakeHit(float damage, int attackerPoliticalID, int damageType,
                         const Vector3& direction, cCombatant* pAttacker);   // 0x18
    virtual void AddHostileUnit(cCombatant* pAttacker);                      // 0x1c

    bool IsInvulnerable();          // 0xbfc480

    uint32_t pad04[(0x2c - 4) / 4];
    float    mMaxHealthPoints;      // +0x2c
    uint32_t pad30;
    int      mDeathState;           // +0x34
    float    mHealthPoints;         // +0x38
    uint32_t pad3c[(0xc8 - 0x3c) / 4];
};

struct cGonzagoTimer { void Stop(); };   // 0xbc3110

struct cMission { uint8_t pad[0x21c]; bool mbIgnoreAwareness; };   // +0x21c

class cSPGameDataUFO : public cGameData, public cLocomotiveObject, public cCombatant {
public:
    void TakeHit(float damage, int attackerPoliticalID, int damageType,
                 const Vector3& direction, cCombatant* pAttacker);
    void StartPlayerDeathSequence();    // 0xc3c520
    bool IsOnMission();                 // 0xc372c0

    uint32_t      pad5d0[(0x60c - 0x5d0) / 4];
    Vector3       mOffsetDueToDamage;   // +0x60c
    Vector3       mDamageVelocity;      // +0x618
    bool          mbRotateTowardsDestination;   // +0x624
    uint32_t      pad628[(0x648 - 0x628) / 4];
    cGonzagoTimer mHoverTimer;          // +0x648
    uint32_t      pad64c[(0x714 - 0x64c) / 4];
    int           mUFOType;             // +0x714
    Vector3       mNextPosition;        // +0x718
    uint32_t      pad724[(0x74c - 0x724) / 4];
    bool          mbAtDestination;      // +0x74c
    Vector3       mDestination;         // +0x750
    uint32_t      pad75c[(0x76c - 0x75c) / 4];
    int           mCombatState;         // +0x76c
    uint32_t      pad770[(0x780 - 0x770) / 4];
    int           mModelKeyInstance;    // +0x780 (mDesiredModelKey)
    int           mModelKeyType;        // +0x784
    int           mModelKeyGroup;       // +0x788
    uint32_t      pad78c[(0x800 - 0x78c) / 4];
    int           mOwnerMission;        // +0x800
};

struct cUFOSimulator {
    bool IsPlayerDying();                                   // 0xffc090
    int  ffc320();
    int  ffc2d0();
    void ffd710(cSpaceToolData* tool, cCombatant* attacker);
    void RemovePoliticalID(int politicalID, int);           // 0x1001700
};
struct cPlayerInventory { cSpaceToolData* GetActiveTool(); };          // 0xff3f00
struct cSPSimulatorSpaceGame {
    cPlayerInventory* GetPlayerInventory();                 // 0xa1ad60
    void f1005180(int);
};
struct cSpaceCombatTuning {
    float GetDamageMultiplier();                            // 0x102a5e0
    float GetLootDropChance(int ufoType);                   // 0x102a1d0
};
struct cStarManager { cEmpire* GetEmpireByID(int id); };    // 0xba9370
struct cRelationshipManager {
    float RecordEvent(int politicalID1, int politicalID2, uint32_t eventType, float scale);   // 0xd06240
};
struct cSPUIEventLog {
    void PostFeedbackEvent(uint32_t a, uint32_t b, int c, int d, int e, int f);   // 0xdd8640
};
struct cSimulatorUniverse {
    void AdjustAwareness(int politicalID, int amount);      // 0x1014a80
    void OnPlayerDeath(int attackerPoliticalID);            // 0x100e6e0
    static cSimulatorUniverse* sInstance;                   // 0x16dc798
};
struct cAchievementsController {
    void Trigger(uint32_t id, int a, int b);                // 0x676ed0
    void AutoTest(uint32_t id, int a);                      // 0x676e90
};
struct cGameViewManager {
    bool a98020();
    int  GetAccessFlags();                                  // 0xff0420
};
struct cPlanet {
    bool HasFlag(uint32_t id);                              // 0xc772c0
    void SetFlag(uint32_t id);                              // 0xc77bf0
};
struct cTerrainEditor { cPlanet* GetCurrentTerrainSphere(); };   // 0xf67d90
struct cMissionManager { bool IsRunning(); };               // 0xfeba90
struct cTutorial { void Trigger(uint32_t id); };            // 0x106dcd0
struct cSpaceTokenTranslator { uint32_t pad[0x30 / 4]; cGameData* mpDestroyedUFO; };   // +0x30
struct cSpatialObject;
struct cMessageData {
    cMessageData(cLocomotiveObject* obj, int);              // 0xad7a30
    ~cMessageData();                                        // 0xad7ad0
    uint32_t pad[8];
};
struct cMessageRouter { void Post(uint32_t id, const cMessageData& data); };   // 0xae09b0

void* GetCurrentGameMode();                                 // 0xb5b800
bool  IsGamePaused();                                       // 0x1041d10
int   GetUniverseContext();                                 // 0x1021080
int   GetPlayerEmpireID();                                  // 0x1021090
cEmpire* GetPlayerEmpire();                                 // 0x1021300
cUFOSimulator* GetUFOSimulator();                           // 0xffbe50
cSPGameDataUFO* CombatantToUFO(cCombatant* c);              // 0xae3370
void* CombatantToBuilding(cCombatant* c);                   // 0xbcd430
cSpaceCombatTuning* GetSpaceCombatTuning();                 // 0x1029940
cStarManager* StarManager();                                // 0xb3d2a0
cRelationshipManager* RelationshipManager();                // 0xb3d2c0
cSPUIEventLog* EventLog();                                  // 0xb3d3e0
cTerrainEditor* NounManager();                              // 0xb3d300
cMessageRouter* MessageRouter();                            // 0xb3d4d0
cSPSimulatorSpaceGame* SpaceGameGet();                      // 0x1002bd0
cAchievementsController* AchievementsController();         // 0x675250
cGameViewManager* GameViewManager();                        // 0x1015df0
EA::Swarm::IEffectsManager* EffectsManager();               // 0x67ddd0
cMissionManager* GetMissionManager();                       // 0xfeb9f0
cTutorial* TutorialManager();                               // 0x10666a0
cMission* GetMissionByID(int id);                           // 0xb67700
bool  ToolCanTarget(cSpaceToolData* tool, cGameData* target);   // 0x102af80
void  DropLoot(Vector3 position, cSPGameDataUFO* ufo);      // 0x102ba30
void  OnUFODestroyed(cSPGameDataUFO* ufo, int);             // 0x102c340
void  PostUFOEvent(uint32_t id, cEmpire* empire, const ResourceKey& ufoKey, ResourceKey* a,
                   int b, int c, ResourceKey* d, ResourceKey* e);   // 0xe39ab0
void  TriggerTutorialEvent(const char* name, uint32_t id, int);    // 0x1041c50
void* Audio_GetState();                                     // 0x435e90
void  Audio_PlaySound(uint32_t id, void* state);            // 0x435ed0

extern char gGameModeSpace;                                 // 0x1654c10
extern char gGameModeSpaceAlt;                              // 0x1654c05
extern cSpaceTokenTranslator* gpSpaceTokenTranslator;       // 0x16e0d08
struct cUFOTuning { uint32_t pad[5]; float mImpulseScale; float mImpulseScale2;
                           uint32_t pad1c[(0x178 - 0x1c) / 4]; float mImpulseBase; };
extern cUFOTuning* gpUFOTuning;   // 0x168df68
extern EA::Random::RandomLinearCongruential sMathRandom;   // 0x1601760

static __forceinline void PlayEmpireHitSound(cEmpire* empire)
{
    uint32_t id = 0;
    switch (empire->mArchetype) {
    case 0: id = 0x681fca05; break;
    case 1: id = 0xbd17d8bc; break;
    case 2: id = 0x69f8ac9d; break;
    case 3: id = 0x2db4202e; break;
    case 4: id = 0x7e0f4c24; break;
    case 5: id = 0x4669212d; break;
    case 6: id = 0x79d83254; break;
    case 7: id = 0xfef69e24; break;
    case 8: id = 0x9df6192d; break;
    default:
        if (empire == GetPlayerEmpire())
            id = 0xdc553e7f;
        break;
    }
    Audio_PlaySound(id, Audio_GetState());
}

static __forceinline void PlayEmpireDestroyedSound(cEmpire* empire)
{
    uint32_t id = 0;
    switch (empire->mArchetype) {
    case 0: id = 0x50d22af7; break;
    case 1: id = 0xe1ab9994; break;
    case 2: id = 0x62c31dff; break;
    case 3: id = 0x9b657912; break;
    case 4: id = 0x85c96a4c; break;
    case 5: id = 0xaf8f406f; break;
    case 6: id = 0xe2f6ca9c; break;
    case 7: id = 0xcadac04c; break;
    case 8: id = 0x2434a86f; break;
    default:
        if (empire == GetPlayerEmpire())
            id = 0x1fe441d5;
        break;
    }
    Audio_PlaySound(id, Audio_GetState());
}

// @ 0xc3cd60
void cSPGameDataUFO::TakeHit(float damage, int attackerPoliticalID, int damageType,
                             const Vector3& direction, cCombatant* pAttacker)
{
    if (GetCurrentGameMode() == &gGameModeSpace && mUFOType == 0)
        return;

    if (damageType == 10) {
        cCombatant::TakeHit(damage, attackerPoliticalID, damageType, direction, pAttacker);
        return;
    }

    if (IsInvulnerable() || IsGamePaused() || mDeathState == 2)
        return;
    if (mCombatState == 3 && damageType != 5)
        return;
    if (GetUniverseContext() == 0 && mUFOType == 0 && GetUFOSimulator()->IsPlayerDying())
        return;

    if (pAttacker && pAttacker->ToGameData()->IsDestroyed())
        pAttacker = 0;

    cSPGameDataUFO* pAttackerUFO = CombatantToUFO(pAttacker);
    if (pAttackerUFO) {
        if (pAttackerUFO->mUFOType == 3)
            attackerPoliticalID = GetPlayerEmpireID();
        if (GetPoliticalID() == attackerPoliticalID)
            return;
        if (mUFOType == 3) {
            if (attackerPoliticalID == GetPlayerEmpireID())
                return;
            if (pAttackerUFO->mUFOType == 3)
                return;
        }
    }

    void* pAttackerBuilding = CombatantToBuilding(pAttacker);
    if (pAttackerBuilding) {
        if (GetPoliticalID() == attackerPoliticalID)
            return;
        if (mUFOType == 3 && attackerPoliticalID == GetPlayerEmpireID())
            return;
    }

    AddHostileUnit(pAttacker);

    int type = mUFOType;
    if (type != 0 && type != 3 &&
        (pAttackerBuilding ||
         (pAttackerUFO && pAttackerUFO->mUFOType != 0 && pAttackerUFO->mUFOType != 3)))
    {
        damage *= GetSpaceCombatTuning()->GetDamageMultiplier();
    }

    if (GetUniverseContext() == 0 && damageType != 8) {
        Vector3 impulse = direction * damage;
        float lengthSq = impulse.SquaredLength();
        if (lengthSq > 1.5258789e-05f) {
            Vector3 up = Vector3_Normalize(GetPosition());
            impulse -= up * up.Dot(impulse) * 0.9f;
            impulse = Vector3_Normalize(impulse);
            if (mbAtDestination)
                mbRotateTowardsDestination = false;
            float scale1 = gpUFOTuning->mImpulseScale;
            float scale2 = gpUFOTuning->mImpulseScale2;
            float base = gpUFOTuning->mImpulseBase;
            mbAtDestination = false;
            mHoverTimer.Stop();
            float length = sqrtf(lengthSq);
            float k1 = length * scale1 + base;
            float k2 = length * scale2 + base;
            Vector3 a = impulse * k1;
            mDestination += a;
            Vector3 b = impulse * k2;
            mDamageVelocity += b;
            mOffsetDueToDamage += b;
        }
    }

    if (mUFOType == 3 && mHealthPoints == mMaxHealthPoints && damage > 0.0f) {
        cEmpire* empire = StarManager()->GetEmpireByID(GetPoliticalID());
        if (empire)
            PlayEmpireHitSound(empire);
    }

    cCombatant::TakeHit(damage, attackerPoliticalID, damageType, direction, pAttacker);

    if (mUFOType == 0) {
        EA::AutoRefCount<cSpaceToolData> tool(SpaceGameGet()->GetPlayerInventory()->GetActiveTool());
        if (tool)
            tool->mbInUse = true;
        mCombatState = 1;
        if (pAttacker) {
            cSpaceToolData* activeTool = SpaceGameGet()->GetPlayerInventory()->GetActiveTool();
            cUFOSimulator* sim = GetUFOSimulator();
            if (!sim->ffc320() && !sim->ffc2d0() && ToolCanTarget(activeTool, pAttacker->ToGameData()))
                sim->ffd710(activeTool, pAttacker);
        }
    }

    if (GetCurrentGameMode() == &gGameModeSpaceAlt && attackerPoliticalID == GetPlayerEmpireID()) {
        cMission* mission = GetMissionByID(mOwnerMission);
        if (!mission || !mission->mbIgnoreAwareness)
        {
            cSimulatorUniverse* universe = cSimulatorUniverse::sInstance;
            universe->AdjustAwareness(GetPoliticalID(), 5);
        }
    }

    bool destroyed = false;
    if (mHealthPoints <= 0.0f) {
        if (mUFOType == 0) {
            SpaceGameGet()->f1005180(10);
            AchievementsController()->Trigger(0xd456d958, 0x10, 1);
            if (!GameViewManager()->a98020() && !GameViewManager()->GetAccessFlags())
                StartPlayerDeathSequence();
            ResourceKey key1(0, 0, 0);
            ResourceKey key2(0, 0, 0);
            ResourceKey key3(0, 0, 0);
            PostUFOEvent(0x949ace8, 0, GetPlayerEmpire()->GetUFOKey(), &key3, 0, 0, &key2, &key1);
            cSimulatorUniverse::sInstance->OnPlayerDeath(attackerPoliticalID);
        }
        else {
            if (pAttackerUFO && (pAttackerUFO->mUFOType == 0 || pAttackerUFO->mUFOType == 3) &&
                GetUniverseContext() == 0)
            {
                float chance = GetSpaceCombatTuning()->GetLootDropChance(mUFOType);
                if (sMathRandom.RandomDoubleUniform() <= chance)
                    DropLoot(mNextPosition, this);
            }

            if (mUFOType == 3) {
                cEmpire* empire = StarManager()->GetEmpireByID(GetPoliticalID());
                if (empire)
                    PlayEmpireDestroyedSound(empire);
                if (GetPoliticalID() != GetPlayerEmpireID()) {
                    if (!NounManager()->GetCurrentTerrainSphere()->HasFlag(0xfce7461)) {
                        gpSpaceTokenTranslator->mpDestroyedUFO = this;
                        MessageRouter()->Post(0x39c4d972, cMessageData(this, 0));
                        TriggerTutorialEvent("SPG_PlayerDestroyedPossee", 0xfce7461, 1);
                    }
                    int politicalID = GetPoliticalID();
                    if (politicalID != -1 && politicalID != GetPlayerEmpireID()) {
                        RelationshipManager()->RecordEvent(GetPoliticalID(), GetPlayerEmpireID(), 0x526e542, 1.0f);
                        EventLog()->PostFeedbackEvent(0x86862dec, 0x131a9f54, 0, 0, 1, 0);
                    }
                    EA::AutoRefCount<EA::Swarm::cIVisualEffect> effect;
                    if (EffectsManager()->CreateVisualEffect(0x3e2cc60, 0, effect.AsPPTypeParam())) {
                        Transform transform;
                        transform.SetOffset(GetPosition());
                        effect->SetSourceTransform(transform);
                        effect->Start(0);
                    }
                }
                GetUFOSimulator()->RemovePoliticalID(GetPoliticalID(), 0);
            }
            else if (mUFOType != 0) {
                if (GetPoliticalID() != -1 && attackerPoliticalID != -1) {
                    cMission* mission = GetMissionByID(mOwnerMission);
                    if (!mission || !mission->mbIgnoreAwareness)
                        RelationshipManager()->RecordEvent(GetPoliticalID(), attackerPoliticalID, 0x591f833, 1.0f);
                    cEmpire* empire = StarManager()->GetEmpireByID(GetPoliticalID());
                    if (empire) {
                        ResourceKey key1(0, 0, 0);
                        ResourceKey key2(0, 0, 0);
                        ResourceKey key3(0, 0, 0);
                        PostUFOEvent(0xbc7c7b37, empire, empire->GetUFOKey(), &key3, 0, 0, &key2, &key1);
                    }
                }
            }

            EA::AutoRefCount<EA::Swarm::cIVisualEffect> effect;
            if (mUFOType == 4)
                EffectsManager()->CreateVisualEffect(0x3d6f82d, 0, effect.AsPPTypeParam());
            else
                EffectsManager()->CreateVisualEffect(0x3d6f830, 0, effect.AsPPTypeParam());
            if (effect) {
                int modelIDs[2] = { mModelKeyInstance, mModelKeyGroup };
                effect->SetIntParams(6, modelIDs, 2);
                float radius = GetBoundingRadius();
                effect->SetFloatParams(1, &radius, 1);
                Transform transform;
                transform.SetRotation(GetOrientation());
                transform.SetOffset(GetPosition());
                transform.SetScale(radius);
                effect->SetSourceTransform(transform);
                effect->Start(0);
            }
            destroyed = true;
            OnUFODestroyed(this, 0);
        }
    }

    if (GetCurrentGameMode() == &gGameModeSpaceAlt && attackerPoliticalID == GetPlayerEmpireID() && destroyed)
        AchievementsController()->AutoTest(0x2a7c313d, 1);

    if (mUFOType == 0 && IsOnMission()) {
        if (GetMissionManager()->IsRunning()) {
            cPlanet* planet = NounManager()->GetCurrentTerrainSphere();
            if (planet && !planet->HasFlag(0x6627799)) {
                planet->SetFlag(0x6627799);
                TutorialManager()->Trigger(0xe8aec881);
            }
        }
    }
}

}
