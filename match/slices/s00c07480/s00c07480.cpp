// Slice s00c07480: the single function in this slice is
//   0x00C07480  Simulator::cCreatureAnimal::TakeDamage   (3112 bytes, __thiscall, ret 0x14)
//
// cCombatant::TakeDamage override (slot 0x18 of the cCombatant vtable at 0x01469e90); `this`
// is the cCombatant subobject at creature+0x5a8. Member offsets follow the ModAPI
// cCreatureBase / cCreatureAnimal layout (retail).
//
//   - dead combatants and damage below 2^-16 are ignored;
//   - charm damage (type 3 with an attacker): accumulates per attacker (same political id
//     keeps the sum), notifies the behavior tree while below the threshold, and once it is
//     reached resets it, sets the charm time and (civ game, player empire, epic creature)
//     logs the event and plays an audio cue;
//   - otherwise runs cCreatureBase::TakeDamage, restarts the no-damage timer, clears
//     stealth, posts the avatar damage message / retaliates (scenario mode), alerts nearby
//     creatures on death, notifies the behavior trees, applies relationship changes, the
//     creature-game "killed" stats and pollinator ids, warns the herd and plays the tribe
//     game attack reaction.
//
// Build flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the message local has a
// destructor but the original has no EH frame).
#include "types.h"

#pragma warning(disable: 4100)

extern "C" long __cdecl _InterlockedExchange(volatile long* target, long value);
#pragma intrinsic(_InterlockedExchange)

enum {
    kGameCreature = 0x1654C01,
    kGameTribe    = 0x1654C02,
    kGameCiv      = 0x1654C04,
    kScenarioMode = 0x1654C10,
};
enum {
    kCreatureBaseType   = 0xCE9F6639,   // cCreatureBase::TYPE
    kCreatureAnimalNoun = 0x18EB45E,    // cCreatureAnimal::NOUN_ID
};

struct Vector3 { float x, y, z; };
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey() {}
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};

struct cSPTimer {
    uint32_t data[8];
    void Restart();                 // 0x00bc3130
    bool IsRunning();               // 0x00feba90
    uint64_t GetElapsedTime();      // 0x00bc3190
};

struct cSpeciesProfile {
    uint32_t pad[0x504 / 4];
    ResourceKey mCreatureKey;       // 0x504
};

// Behavior-tree event record returned by cBehaviorEvents::Add.
struct cBehaviorEvent {
    uint32_t pad[3];
    int field_0C;
    int field_10;
    int field_14;
};
struct cBehaviorEvents {
    cBehaviorEvent* Add(int type, int arg, float priority, void* source);   // 0x00bc97f0
};
struct cBehaviorPerception {
    void Alert(int type, float radius, void* source, int arg);              // 0x00bc9d40
};
struct cBehaviorSubTree { uint32_t pad[0x10 / 4]; int field_10; };
struct cBehaviorTreeData {
    uint32_t pad[8 / 4];
    cBehaviorEvents mEvents;        // 0x08
    uint32_t pad0c[(0x1d8 - 0xc) / 4];
    uint32_t mTreeID;               // 0x1d8
    uint32_t pad1dc[(0x600 - 0x1dc) / 4];
    cBehaviorSubTree* field_600;    // 0x600
};
struct cAnimationQueue {
    int Find(int a, int b, int c, int d);   // 0x00bca0c0
    void Stop(int index);                   // 0x00bca040
};

class cCombatant;
class cCreatureBase;

class cGameData {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual uint32_t GetNounID();                   // 0x20
    virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual uint32_t GetPoliticalID();              // 0x4c
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80();
    virtual void AttackTarget(cCombatant* target, int a, int b);   // 0x84
    virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual bool IsBusy();                          // 0xd0
    uint32_t gameDataFields[0x30 / 4];
    uint32_t creatureBases34[(0xc0 - 0x34) / 4];    // cGameBundleContainer, cBehaviorAgent
};

class cLocomotiveObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();           // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool IsMoving();                        // 0x58
    virtual void v5c(); virtual void v60(); virtual void v64(); virtual void v68();
    virtual void v6c(); virtual void v70();
    virtual float GetBoundingRadius();              // 0x74
    uint32_t pad04[(0x590 - 0xc4) / 4];
    uint32_t behaviorList[(0x5a8 - 0x590) / 4];     // cBehaviorList base
};

class cCombatant {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cGameData* ToGameData();                // 0x0c
    virtual void v10(); virtual void v14();
    virtual void TakeDamage(float damage, uint32_t attackerPoliticalID, int damageType,
                            const Vector3& direction, cCombatant* pAttacker);   // 0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
    virtual void* Cast(uint32_t type);              // 0x5c

    int GetDamageState();                           // 0x008e7f80 (returns field_34; 2 = dead)
    uint32_t pad04[(0xc8 - 4) / 4];
};

// intrusive_ptr<cCombatant> with the out-of-line assignment
struct cCombatantPtr {
    cCombatant* mpObject;
    cCombatant* get() const { return mpObject; }
    cCombatantPtr& operator=(cCombatant* p);        // 0x00ae6690
};

class cCreatureBase : public cGameData, public cLocomotiveObject, public cCombatant {
public:
    bool IsEpic();                                  // 0x00c0c0e0
    bool IsBaby();                                  // 0x00c0b770
    const ResourceKey* GetSpeciesKey();             // 0x00c0bc00
    cSpeciesProfile* GetSpeciesProfile();           // 0x00c0bbd0
    cCombatant* GetCombatantTarget();               // 0x00c0ee60
    float GetAttackDamage(int arg);                 // 0x00c04140
    void SetStealthed(int a, int b);                // 0x00c1aed0
    void StopAttacking(int arg);                    // 0x00c14750
    void SetIntention(int arg);                     // 0x00c073a0

    virtual void TakeDamage(float damage, uint32_t attackerPoliticalID, int damageType,
                            const Vector3& direction, cCombatant* pAttacker);   // 0x00c1a3c0

    bool IsPlayerAvatar() const { return (mGeneralFlags >> 9) & 1; }

    uint32_t pad670[(0xb20 - 0x670) / 4];
    cSpeciesProfile* mpSpeciesProfile;              // 0xb20
    uint32_t mProfileSeq;                           // 0xb24
    ResourceKey mSpeciesKey;                        // 0xb28
    int mAge;                                       // 0xb34
    uint32_t padb38[(0xb48 - 0xb38) / 4];
    cAnimationQueue* field_B48;                     // 0xb48
    cBehaviorTreeData* mpBehaviorTree;              // 0xb4c
    uint32_t padb50[2];
    uint32_t mGeneralFlags;                         // 0xb58
    bool field_B5C;
    bool mbTeleport;
    bool mbDead;                                    // 0xb5e
    uint8_t padb5f;
    uint32_t padb60[(0xfc0 - 0xb60) / 4];
};

struct cHerd {
    uint32_t pad[0x88 / 4];
    uint32_t field_88;                              // 0x88
    uint32_t pad8c[(0xf0 - 0x8c) / 4];
    uint32_t field_F0;                              // 0xf0
    uint32_t padf4[(0x164 - 0xf4) / 4];
    cCreatureBase* mpLeader;                        // 0x164
};

struct cSpeciesArchetype {
    uint32_t pad[0x434 / 4];
    float mAlertRadius;                             // 0x434
    int mMaxDefenders;                              // 0x438
};
struct cSpeciesArchetypeManager {
    cSpeciesArchetype* GetArchetype(uint32_t a, uint32_t b);   // 0x004e0050
};
cSpeciesArchetypeManager* SpeciesArchetypeManager();          // 0x00401090

// Entries of the "nearby creatures" list (creature+0x1124).
struct cNearbyEntry { uint32_t pad[2]; cCreatureBase* mpCreature; };
struct cNearbyVector { cNearbyEntry** mpBegin; cNearbyEntry** mpEnd; };
struct cNearbyFilter { bool operator()(cNearbyEntry* e); };   // 0x00c02600
struct cNearbyIterator {
    cNearbyEntry** mpCurrent;
    cNearbyEntry** mpEnd;
    cNearbyFilter mFilter;
    cNearbyIterator(const cNearbyVector& v, const cNearbyFilter& f);   // 0x00b41a40
    void Next();                                                       // 0x00b3d850
};

class cCreatureAnimal : public cCreatureBase {
public:
    virtual void TakeDamage(float damage, uint32_t attackerPoliticalID, int damageType,
                            const Vector3& direction, cCombatant* pAttacker);

    cSPTimer mNoDamageTimer;                        // 0xfc0
    cSPTimer mLastAvatarDamageTimer;                // 0xfe0
    uint32_t pad1000[(0x1124 - 0x1000) / 4];
    cNearbyVector mNearby;                          // 0x1124
    uint32_t pad112c[(0x1624 - 0x112c) / 4];
    cBehaviorPerception* mpPerception;              // 0x1624
    uint32_t pad1628[(0x1674 - 0x1628) / 4];
    cHerd* mpHerd;                                  // 0x1674
    uint32_t pad1678[(0x1694 - 0x1678) / 4];
    float mCharmDamage;                             // 0x1694
    cCombatantPtr mpCharmer;                        // 0x1698
    float mCharmTime;                               // 0x169c
};


// --- globals and managers ---
extern float kCharmThreshold;                       // 0x01582fe4
extern float kCharmThresholdEpic;                   // 0x01582fe8
extern float kCharmDuration;                        // 0x01582fec
extern float kAvatarProvokeTime;                    // 0x01582f84

struct cCivilizationBase { virtual void v00(); uint32_t pad[(0x3c - 4) / 4]; };
struct cIdentityColorable {
    virtual void v00();
    uint32_t mIdentityColor;
    uint32_t GetIdentityColor() const { return mIdentityColor; }
};
struct cCivilization : public cCivilizationBase, public cIdentityColorable {
    cSpeciesProfile* GetSpeciesProfile();           // 0x00bef950
};
struct cGameNounManager {
    cCivilization* GetPlayerCivilization();         // 0x00b25fb0
    uint32_t GetPlayerPoliticalID();                // 0x00b1f9d0
    cCreatureBase* GetAvatar();                     // 0x00b1fdb0
    struct cTerrainSphere* GetPlanet();             // 0x00f67d90
};
cGameNounManager* GameNounManager();                // 0x00b3d300
uint32_t GetCurrentGameMode();                      // 0x00b5b800
void __cdecl LogEvent(uint32_t eventID, const ResourceKey* a, const ResourceKey* b,
                      const ResourceKey* c, uint32_t color, int d, int e);   // 0x00e3c7c0

struct cTerrainSphere { void OnCreatureKilled(float value, int arg); };   // 0x00c756a0
void __cdecl NotifyCreatureKilled(float value);     // 0x00d2e8a0

struct cAudioManager {
    uint32_t pad[0x58 / 4];
    struct cPollinator* field_58;                   // 0x58
    void PlayForSpecies(uint32_t id, const ResourceKey* key);   // 0x0060d860
};
struct cServerID { uint32_t a, b; };
struct cPollinator {
    bool GetServerID(const ResourceKey* key, struct cServerID* id, int arg);   // 0x0054e530
};
cAudioManager* AudioManager();                      // 0x0067cb30

struct cRelationshipManager {
    int GetRelationship(const ResourceKey* key, cCreatureBase* avatar, cCreatureBase* creature);   // 0x00ba3f90
    void ApplyEvent(int type, const ResourceKey* key, cCreatureBase* creature);                   // 0x00ba48b0
};
cRelationshipManager* RelationshipManager();        // 0x00b3d4c0

struct cPosseSimulator { void OnEvent(int type, int arg); };   // 0x00d52e90
cPosseSimulator* PosseSimulator();                  // 0x00d539d0

struct cCreatureStat { uint32_t pad[0x2c / 4]; int field_2C; int field_30; int field_34; };
struct cCreatureStatRecord { uint32_t pad[0xc / 4]; cCreatureStat* mpStat; };
struct cKillInfo { cCreatureBase* mpVictim; int field_4; int mDamageType; };
struct cCreatureModeStrategy {
    void OnCreatureEvent(uint32_t id, cKillInfo* info);   // 0x00d39360
    void SignalCreatureEvent(uint32_t id);                 // 0x00d3cdc0
    cCreatureStatRecord* AddStat(int a, int b);            // 0x00d39670
};
cCreatureModeStrategy* CreatureModeStrategy();      // 0x00d38840

struct cAchievements { void Trigger(uint32_t id, int a, int b); };   // 0x00676ed0
cAchievements* AchievementsController();            // 0x00675250

struct cCombatAlertManager {
    void AlertCreatures(const Vector3& pos, float radius, int arg, uint32_t politicalID);   // 0x00f315a0
};
cCombatAlertManager* CombatAlertManager();          // 0x00c03260

struct cTribeReactions {
    void React(uint32_t id, const Vector3& pos, float radius, float time,
               cCreatureBase* attacker, cCreatureBase* victim);   // 0x00bc8400
};
cTribeReactions* TribeReactions();                  // 0x00bc8000

float __cdecl DistanceBetween(cLocomotiveObject* a, cLocomotiveObject* b, int arg);   // 0x00d99ac0
bool __cdecl IsValidRetaliationTarget(cCombatant* attacker);                        // 0x00d30f60

struct cCameraState { uint32_t pad[0x54 / 4]; bool field_54; };
struct cCameraMode { uint32_t pad[0x90 / 4]; int mMode; void SetLock(int a); void SetMode(int m); };   // 0x00f1b640 / 0x00f1aae0
struct cCameraManager {
    uint32_t pad[0x68 / 4];
    cCameraState* field_68;                         // 0x68
    uint32_t pad6c[(0x78 - 0x6c) / 4];
    cCameraMode* field_78;                          // 0x78
};
extern cCameraManager* g_pCameraManager;           // 0x016c7aa4

// Message posted to the message server (vtable 0x013eb844, base 0x013eb90c).
class cBehaviorMessage {
public:
    virtual void _v00();
    volatile long mnRefCount;                       // +04
    cBehaviorMessage() { _InterlockedExchange(&mnRefCount, 0); }
};
class cDamageMessage : public cBehaviorMessage {
public:
    float mDamage;                                  // +08
    uint32_t field_C[9];
    uint32_t mMessageID;                            // +30
    uint32_t field_34;
    void* mpData;                                   // +38

    cDamageMessage(uint32_t id) : mMessageID(id), mpData(0) {}
    virtual void _v00();
    ~cDamageMessage();                              // 0x00421cf0
};
struct IMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void PostMSG(uint32_t id, void* msg, void* p);   // 0x14
};
IMessageServer* MessageServer();                    // 0x0067dcc0

template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

// @ 0x00c07480
void cCreatureAnimal::TakeDamage(float damage, uint32_t attackerPoliticalID, int damageType,
                                 const Vector3& direction, cCombatant* pAttacker)
{
    if (GetDamageState() == 2)
        return;
    if (damage < 1.5258789e-05f)
        return;

    if (damageType == 3 && pAttacker) {
        // charm damage
        if (pAttacker == mpCharmer.get()) {
            mCharmDamage += damage;
        }
        else {
            float charm = damage;
            if (mpCharmer.get()) {
                cGameData* pCharmer = mpCharmer.get()->ToGameData();
                if (pAttacker->ToGameData()->GetPoliticalID() == pCharmer->GetPoliticalID())
                    charm = mCharmDamage + damage;
            }
            mCharmDamage = charm;
            mpCharmer = pAttacker;
        }

        if (mCharmDamage >= (IsEpic() ? kCharmThresholdEpic : kCharmThreshold)) {
            mCharmTime = kCharmDuration;
            mCharmDamage = 0.0f;
            if (GetCurrentGameMode() == kGameCiv
                && attackerPoliticalID == GameNounManager()->GetPlayerPoliticalID()
                && IsEpic())
            {
                cCivilization* pCiv = GameNounManager()->GetPlayerCivilization();
                ResourceKey key(0, 0, 0);
                LogEvent(0x13525C87, &GameNounManager()->GetPlayerCivilization()->GetSpeciesProfile()->mCreatureKey,
                         &mpSpeciesProfile->mCreatureKey, &key, pCiv->GetIdentityColor(), 0, 0);
                AudioManager()->PlayForSpecies(0x280FCA87, GetSpeciesKey());
            }
        }
        else {
            cBehaviorEvent* pEvent = mpBehaviorTree->mEvents.Add(0x400, 0, 4.0f, pAttacker->ToGameData());
            if (pEvent) {
                pEvent->field_0C = 3;
                *(float*)&pEvent->field_10 = mCharmDamage;
            }
        }
        return;
    }

    cCreatureBase::TakeDamage(damage, attackerPoliticalID, damageType, direction, pAttacker);

    cCreatureBase* pAttackerCreature;
    cCreatureAnimal* pAttackerAnimal = 0;
    if (pAttacker) {
        pAttackerCreature = (cCreatureBase*)pAttacker->Cast(kCreatureBaseType);
        cGameData* pData = pAttacker->ToGameData();
        if (pData && pData->GetNounID() == kCreatureAnimalNoun)
            pAttackerAnimal = (cCreatureAnimal*)pData;
    }
    else {
        pAttackerCreature = 0;
    }

    bool bIsAvatar = IsPlayerAvatar();
    mNoDamageTimer.Restart();
    SetStealthed(0, 0);

    if (GetCurrentGameMode() == kScenarioMode) {
        if (bIsAvatar) {
            {
                cDamageMessage msg(0x7C6551E);
                msg.mDamage = damage;
                MessageServer()->PostMSG(msg.mMessageID, &msg, 0);
            }
            if (!GetCombatantTarget() && pAttacker && IsValidRetaliationTarget(pAttacker))
                AttackTarget(pAttacker, 1, 0);
        }
        if (GetDamageState() == 2) {
            if (bIsAvatar) {
                g_pCameraManager->field_68->field_54 = false;
                cCameraMode* pMode = g_pCameraManager->field_78;
                if (pMode && pMode->mMode == 3) {
                    pMode->SetLock(0);
                    pMode->SetMode(6);
                }
            }
            CombatAlertManager()->AlertCreatures(GetPosition(), GetBoundingRadius(), 1, GetPoliticalID());
        }
    }

    if ((pAttackerAnimal && pAttackerAnimal->IsPlayerAvatar()) || GetDamageState() == 2) {
        int index = field_B48->Find(1, 1, 0, 0);
        if (index != -1)
            field_B48->Stop(index);
        index = field_B48->Find(2, 1, 0, 0);
        if (index != -1)
            field_B48->Stop(index);
    }

    if (pAttackerCreature && pAttackerCreature->IsPlayerAvatar())
        mLastAvatarDamageTimer.Restart();

    if (pAttacker || GetDamageState() == 2) {
        cGameData* pSource = pAttacker ? pAttacker->ToGameData() : 0;
        cBehaviorEvent* pEvent = mpBehaviorTree->mEvents.Add(0x400, 0, 10.0f, pSource);
        if (pEvent) {
            pEvent->field_0C = damageType;
            if (bIsAvatar)
                PosseSimulator()->OnEvent(0x400, 0);
        }
    }

    bool bProvoked;
    if (pAttackerAnimal) {
        if (pAttackerAnimal->IsMoving())
            bProvoked = true;
        else if (RelationshipManager()->GetRelationship(&pAttackerAnimal->mSpeciesKey,
                     GameNounManager()->GetAvatar(), pAttackerAnimal) == 6
                 && mLastAvatarDamageTimer.IsRunning()
                 && (float)mLastAvatarDamageTimer.GetElapsedTime() * 0.001f < kAvatarProvokeTime)
            bProvoked = true;
        else
            bProvoked = false;
    }
    else {
        bProvoked = false;
    }

    bool bRetaliate;
    if (pAttackerCreature && pAttackerCreature->IsMoving() && !IsBusy()) {
        bRetaliate = true;
        RelationshipManager()->ApplyEvent(2, &mSpeciesKey, this);
    }
    else {
        bRetaliate = false;
    }

    int eventType;
    cCreatureBase* pExclude;
    if (GetDamageState() == 2) {
        if (bProvoked) {
            float value = GetAttackDamage(0);
            NotifyCreatureKilled(value);
            GameNounManager()->GetPlanet()->OnCreatureKilled(value, 0);
        }
        if (bRetaliate || bProvoked)
            RelationshipManager()->ApplyEvent(IsBaby() ? 0 : 5, &mSpeciesKey, this);

        if (pAttackerAnimal) {
            if (bIsAvatar)
                RelationshipManager()->ApplyEvent(1, &pAttackerAnimal->mSpeciesKey, pAttackerAnimal);
            if (pAttackerAnimal->IsEpic() && GetCurrentGameMode() == kGameTribe)
                AudioManager()->PlayForSpecies(0x6E77F36F, &pAttackerAnimal->GetSpeciesProfile()->mCreatureKey);
        }

        eventType = 0x80000;
        pExclude = pAttackerAnimal;
        if (bIsAvatar && GetCurrentGameMode() == kGameCreature) {
            cKillInfo info;
            info.mpVictim = this;
            info.field_4 = 0;
            info.mDamageType = damageType;
            CreatureModeStrategy()->OnCreatureEvent(0xD3353639, &info);
            CreatureModeStrategy()->SignalCreatureEvent(0xD3353639);
            AchievementsController()->Trigger(0xD456D958, 2, 1);
            cCreatureStatRecord* pRecord = CreatureModeStrategy()->AddStat(5, 3);
            pRecord->mpStat->field_34 = damageType;
            if (pAttackerAnimal) {
                cPollinator* pPollinator = AudioManager()->field_58;
                if (pPollinator) {
                    cServerID id;
                    id.a = 0xFFFFFFFF;
                    id.b = 0xFFFFFFFF;
                    if (pPollinator->GetServerID(pAttackerAnimal->GetSpeciesKey(), &id, 0)
                        && (id.a & id.b) != 0xFFFFFFFF)
                    {
                        pRecord->mpStat->field_2C = id.b;
                        pRecord->mpStat->field_30 = id.a;
                    }
                }
            }
        }

        if (mpHerd && mpHerd->mpLeader == this) {
            for (cNearbyIterator it(mNearby, cNearbyFilter()); it.mpCurrent != it.mpEnd; it.Next()) {
                cCreatureBase* pCreature = (*it.mpCurrent)->mpCreature;
                if (pCreature && pCreature->GetNounID() == kCreatureAnimalNoun && !pCreature->IsBaby()
                    && pCreature->mpSpeciesProfile == mpSpeciesProfile)
                {
                    pCreature->mpBehaviorTree->mEvents.Add(0, 2, 10.0f, pAttackerCreature);
                }
            }
        }

        if (GetCurrentGameMode() == kGameCiv
            && attackerPoliticalID == GameNounManager()->GetPlayerPoliticalID()
            && IsEpic())
        {
            cCivilization* pCiv = GameNounManager()->GetPlayerCivilization();
            ResourceKey key(0, 0, 0);
            LogEvent(0x1ECB526C, &GameNounManager()->GetPlayerCivilization()->GetSpeciesProfile()->mCreatureKey,
                     &mpSpeciesProfile->mCreatureKey, &key, pCiv->GetIdentityColor(), 0, 0);
        }
    }
    else {
        if (bRetaliate && pAttackerCreature && pAttackerCreature->IsPlayerAvatar() && !mbDead
            && damageType != 7 && !IsEpic())
        {
            StopAttacking(1);
            SetIntention(-1);
        }
        pExclude = this;
        eventType = 0x200;
    }

    if (pAttackerCreature) {
        int defenders = 0;
        int alertRadius = 0;
        if (eventType == 0x200 && defenders == 0 && mpHerd) {
            cSpeciesArchetype* pArchetype = SpeciesArchetypeManager()->GetArchetype(mpHerd->field_88, mpHerd->field_F0);
            if (pArchetype) {
                int busy = 0;
                if (mpBehaviorTree->mTreeID == 0x2D852E6 && mpBehaviorTree->field_600)
                    busy = mpBehaviorTree->field_600->field_10 - 1;
                defenders = Max(pArchetype->mMaxDefenders - busy, 0);
                alertRadius = (int)pArchetype->mAlertRadius;
            }
        }

        for (cNearbyIterator it(mNearby, cNearbyFilter()); it.mpCurrent != it.mpEnd; it.Next()) {
            cCreatureBase* pCreature = (*it.mpCurrent)->mpCreature;
            bool bDefend = false;
            if (pCreature && pCreature->GetNounID() == kCreatureAnimalNoun && !pCreature->mbDead
                && !pCreature->IsPlayerAvatar() && pCreature != pExclude)
            {
                bool bSameSpecies = pCreature->mpSpeciesProfile == mpSpeciesProfile;
                cBehaviorEvent* pEvent = pCreature->mpBehaviorTree->mEvents.Add(eventType, 0, 5.0f, pExclude);
                pEvent->field_0C = bSameSpecies;
                pEvent->field_10 = (int)pAttackerCreature;
                if (defenders > 0 && pCreature->mpSpeciesProfile == mpSpeciesProfile) {
                    if (DistanceBetween(static_cast<cCreatureBase*>(this), pCreature, 1) <= alertRadius) {
                        defenders--;
                        bDefend = true;
                    }
                }
                pEvent->field_14 = bDefend;
                ((cCreatureAnimal*)pCreature)->mpPerception->Alert(0x21, 15.0f, pExclude, 0);
            }
        }

        if (GetCurrentGameMode() == kGameTribe) {
            TribeReactions()->React(0xB9D14C31, GetPosition(),
                                    pAttackerCreature->GetBoundingRadius() + GetBoundingRadius(),
                                    5.0f, pAttackerCreature, this);
        }
    }

    if (bIsAvatar && GetCurrentGameMode() == kGameCreature)
        CreatureModeStrategy()->SignalCreatureEvent(0x533535DE);
}
