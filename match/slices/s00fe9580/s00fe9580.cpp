// Slice s00fe9580 -- SP::cEmpireGrowthSim::TakeTurn (0x00fe9580, 3252 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the vector / effect locals have no EH frame).
//
// One growth turn of an AI empire: gathers the candidate stars around the empire (radius 4 jumps),
// scores every candidate with the rule set (ScoreStar, 0x00fe8f70) and applies the winning rule
// to the best star:
//   1 = terraform: re-scores the first T3 planet of an owned star (and plays the "grow" effect
//       when the player is in that star's system),
//   2 = raid: starts a raid mission against an unprotected T3 planet of the star,
//   0 = colonize: adds the star to the empire, makes it a T3 star and plays the effect,
//   3 = alliance / welcome the player,
//   4 = war / warn the player.
// Star / planet layout from ModAPI cStarRecord.h / cPlanetRecord.h.
#include "types.h"
#include <stddef.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; }
};
struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(const Vector2& v) { x = v.x; y = v.y; }
};

// rw::math::fpu::Matrix33Template<float,0>
struct Matrix3 {
    float m[9];
    Matrix3(const Matrix3& other);       // 0x0041cb40
};

extern Vector3 sZeroVector3;             // 0x016dabd8
extern Matrix3 sIdentityMatrix3;         // 0x016dabb4

// Transform (ModAPI Transform.h); inline constructor (0x00434040 is an out-of-line copy).
struct Transform {
    uint16_t mnFlags;            // 0x00
    uint16_t mnTransformCount;   // 0x02
    Vector3 mOffset;             // 0x04
    float mfScale;               // 0x10
    Matrix3 mRotation;           // 0x14
    Transform() : mnFlags(0), mnTransformCount(0), mOffset(sZeroVector3), mfScale(1.0f), mRotation(sIdentityMatrix3) {}
    void SetOffset(const Vector3& v)
    {
        mOffset = v;
        mnFlags |= 4;
        mnTransformCount++;
    }
};

// SSE clamp helper of this module (maxss/minss through inline asm).
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

class cIVisualEffect {
public:
    virtual int AddRef();                              // 0x00
    virtual int Release();                             // 0x04
    virtual void Start(int);                           // 0x08
    PV2 PV
    virtual void SetTransform(const Transform& xform); // 0x18
};
// EA::AutoRefCount<cIVisualEffect>
struct IVisualEffectPtr {
    cIVisualEffect* mpObject;
    IVisualEffectPtr() : mpObject(0) {}
    ~IVisualEffectPtr() { if (mpObject) mpObject->Release(); }
    cIVisualEffect* operator->() const { return mpObject; }
    cIVisualEffect** AsPPTypeParam()
    {
        if (mpObject) {
            cIVisualEffect* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};
class cEffectsManager {
public:
    PV8 PV2 PV
    virtual bool CreateVisualEffect(uint32_t id, int, cIVisualEffect** dst);   // 0x2c
};

namespace SP {

cEffectsManager* EffectsManager();                     // 0x0067ddd0
void* GetCurrentGameMode();                            // 0x00b5b800
extern char sGameModeSpace;                            // 0x01654c05
float DistanceSquared(const Vector3& a, const Vector3& b);   // 0x010434c0

class cStarRecord;

class cPlanetRecord {
public:
    uint32_t pad00[0x28 / 4];
    int mType;                   // 0x28
    int mFlags;                  // 0x2c
    uint32_t pad30[(0xb0 - 0x30) / 4];
    float mAtmosphereScore;      // 0xb0
    float mTemperatureScore;     // 0xb4
    float mWaterScore;           // 0xb8

    int GetPlanetTechLevel();               // 0x00b8dab0
    bool IsColonizable();                   // 0x00b8d9f0
    void UpdateTerrain();                   // 0x00b8de60
    void SetGenerated(bool);                // 0x00b8d920
    cStarRecord* GetStar();                 // 0x00b8de30
};
void SetPlanetTechLevel(cPlanetRecord* planet, int level);    // 0x00c706d0
void SetPlanetTechLevelData(cPlanetRecord* planet, int level);   // 0x00b96f40
Vector2 GetWaterScoreRange(float atmosphere, float temperature);   // 0x00fc20e0
bool IsPlanetOwnedByEmpire(cPlanetRecord* planet, uint32_t empireID);   // 0x00c8b920

struct PlanetVector {
    cPlanetRecord** mpBegin;
    cPlanetRecord** mpEnd;
    bool empty() const { return mpBegin == mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    cPlanetRecord*& operator[](uint32_t i) { return mpBegin[i]; }
};

class cStarRecord {
public:
    uint32_t pad00[0x54 / 4];
    uint32_t mEmpireID;          // 0x54
    uint32_t pad58;
    int mFlags;                  // 0x5c
    uint32_t pad60[(0xac - 0x60) / 4];
    char mPlanetCount;           // 0xac

    uint32_t GetEmpireID();                 // 0x00b1fdb0: returns mEmpireID
    int GetFlags();                         // 0x00c87040
    bool IsGrowthCandidate();               // 0x00bba8c0
    PlanetVector& GetPlanets();             // 0x00bba790
    int GetTechLevel();                     // 0x00bb9ae0
    void SetTechLevel(int);                 // 0x00bb9ad0
    void SetFlag(int flag, bool value);     // 0x00bb9b00
    void SetEmpireID(uint32_t id);          // 0x00a16a90
    const Vector3& GetPosition();           // 0x005c65e0
};

struct StarVector {
    cStarRecord** mpBegin;
    cStarRecord** mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
};

// eastl::vector<cStarRecord*>
struct StarRecordVector {
    cStarRecord** mpBegin;
    cStarRecord** mpEnd;
    cStarRecord** mpCapacity;
    uint32_t mAllocator[2];             // eastl::allocator (name, flags)
    StarRecordVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~StarRecordVector()
    {
        if (mpBegin)
            operator delete[](mpBegin);
    }
    void reserve(uint32_t n);               // 0x00eade60
    int size() const { return (int)(mpEnd - mpBegin); }
    cStarRecord*& operator[](int i) { return mpBegin[i]; }
};

class cEmpire;
class cStarRecordRef {
public:
    uint32_t GetCommContext();              // 0x00ce6950
};
class cEmpire {
public:
    uint32_t pad00[0x50 / 4];
    uint32_t mFlags;                        // 0x50
    uint32_t pad54[(0x84 - 0x54) / 4];
    uint32_t mEmpireID;                     // 0x84

    bool IsAggressive() { return (mFlags >> 6) & 1; }
    StarVector& GetStars();                 // 0x00c308d0
    void AddStar(cStarRecord* star);        // 0x00c341a0
    bool HasMetPlayer();                    // 0x00c30970
    void WelcomePlayer();                   // 0x00c31550
    void WarnPlayer();                      // 0x00c314a0
    uint32_t GetCommSpeaker();              // 0x00c30c60
    cStarRecordRef* GetHomePlanet(uint32_t a, uint32_t b, int c, int d, int e);   // 0x00c31730
    bool HasDemandedTribute();              // 0x00c30b30
    void SetDemandedTribute();              // 0x00c30b20
};

class cStarManager {
public:
    cEmpire* GetEmpireByID(uint32_t id);    // 0x00ba9370
    void ClaimPlanet(cPlanetRecord* planet, int);   // 0x00badd10
    void AbandonStar(cStarRecord* star, int);       // 0x00bb57b0
};
cStarManager* StarManager();                // 0x00b3d2a0

class cRelationshipManager {
public:
    bool IsAllied(uint32_t a, uint32_t b);                // 0x00d01fb0
    bool IsAtWar(uint32_t a, uint32_t b);                 // 0x00d01f20
    float GetRelationship(uint32_t a, uint32_t b, int);   // 0x00d00a10
    float RecordEvent(uint32_t a, uint32_t b, uint32_t eventID, float scale);   // 0x00d06240
    void DeclareWar(cEmpire* a, cEmpire* b);              // 0x00d065a0
    void StartAlliance(cEmpire* a, cEmpire* b);           // 0x00d06920
};
cRelationshipManager* RelationshipManager();              // 0x00b3d2c0

class cSpaceRelationshipTuning {
public:
    float GetAllianceChance(float relationship);          // 0x01040820
    float GetWarThreshold();                              // 0x00cbcaf0
};
cSpaceRelationshipTuning* GetSpaceRelationshipTuning();   // 0x010407c0

class cCommManager {
public:
    void ShowCommEvent(uint32_t empireID, uint32_t speaker, uint32_t context);   // 0x00aeb3e0
};
cCommManager* CommManager();                // 0x00b3d4a0

class cUFOSimulator {
public:
    float GetVisibleRadius();               // 0x00ffbfd0
};
cUFOSimulator* GetUFOSimulator();           // 0x00ffbe50

namespace cSPLivingUniverse {
int GetUniverseContext();                   // 0x01021080
uint32_t GetPlayerEmpireID();               // 0x01021090
cStarRecord* GetCurrentStar();              // 0x01021240
cEmpire* GetPlayerEmpire();                 // 0x01021300
}

class cSPMission {
public:
    PV2 PV
    virtual void* Cast(uint32_t type);      // 0x0c
    void Accept();                          // 0x00c485b0
};
class cSPRaidEvent : public cSPMission {
public:
    uint32_t pad004[(0x21e - 4) / 4];
    uint16_t pad21c;
    bool mbShowMessage;                     // 0x21e
    void SetAttackerEmpire(cEmpire* empire);   // 0x00c5b370
    void SetTargetPlanet(cPlanetRecord* planet);   // 0x00c47180
    int GenerateBomberCount();              // 0x00c5b530
    void SetBomberCount(int);               // 0x00c5b390
};
class cSPMissionManager {
public:
    cSPMission* CreateMissionFromID(uint32_t id, cPlanetRecord* planet, cEmpire* owner, int);   // 0x00fec590
};
cSPMissionManager* GetMissionManager();     // 0x00feb9f0

// eastl::map<uint32_t, ...> (rbtree with the key at +0x10 of the node)
struct rbtree_node {
    rbtree_node* mpNodeRight;    // 0x00
    rbtree_node* mpNodeLeft;     // 0x04
    rbtree_node* mpNodeParent;   // 0x08
    char mColor;                 // 0x0c
    uint32_t mKey;               // 0x10
};
struct rbtree_iterator {
    rbtree_node* mpNode;
};
struct EmpireEventMap {
    uint32_t mCompare;           // 0x00
    rbtree_node mAnchor;         // 0x04
    rbtree_iterator end() { rbtree_iterator it; it.mpNode = &mAnchor; return it; }
    rbtree_iterator find(const uint32_t& key);   // 0x00e5c780
    __forceinline rbtree_iterator find_inline(const uint32_t& key)
    {
        rbtree_node* pCurrent = mAnchor.mpNodeParent;
        rbtree_node* pRangeEnd = &mAnchor;
        while (pCurrent) {
            if (!(pCurrent->mKey < key)) {
                pRangeEnd = pCurrent;
                pCurrent = pCurrent->mpNodeLeft;
            } else {
                pCurrent = pCurrent->mpNodeRight;
            }
        }
        rbtree_iterator it;
        if (pRangeEnd != &mAnchor && !(key < pRangeEnd->mKey))
            it.mpNode = pRangeEnd;
        else
            it.mpNode = &mAnchor;
        return it;
    }
};
struct cSpaceGameData {
    uint32_t pad00[0xe4 / 4];
    EmpireEventMap mEmpireEvents;           // 0xe4
};
struct cSpaceGame {
    uint32_t pad00[0x30 / 4];
    cSpaceGameData* mpData;                 // 0x30
};
cSpaceGame* SpaceGameGet();                 // 0x01002bd0

int GetStarsInRange(cEmpire* empire, StarRecordVector& dst, int jumps);   // 0x00fe8c50

enum {
    kRuleColonize = 0,
    kRuleTerraform = 1,
    kRuleRaid = 2,
    kRuleAlliance = 3,
    kRuleWar = 4,
    kRuleNone = 5,
};

class cEmpireGrowthSim {
public:
    float ScoreStar(cStarRecord* star, cEmpire* empire, int* rule, int numStars, int numFreeStars);   // 0x00fe8f70
    bool IsPlayerProtected();               // 0x00fe8990
    void TakeTurn(uint32_t empireID);
};

void cEmpireGrowthSim::TakeTurn(uint32_t empireID)
{
    cEmpire* empire = StarManager()->GetEmpireByID(empireID);
    StarRecordVector candidates;
    candidates.reserve(300);
    GetStarsInRange(empire, candidates, 4);

    StarVector& stars = empire->GetStars();
    int numStars = stars.size();
    int numFreeStars = 0;
    for (int i = 0; i < numStars; i++) {
        if (!(stars.mpBegin[i]->GetFlags() & 0x100))
            numFreeStars++;
    }

    int numCandidates = candidates.size();
    cStarRecord* bestStar = 0;
    float bestScore = 1.0f;
    int bestRule = kRuleNone;
    for (int i = 0; i < numCandidates; i++) {
        cStarRecord* star = candidates[i];
        if (star->IsGrowthCandidate()) {
            int rule;
            float score = ScoreStar(star, empire, &rule, numStars, numFreeStars);
            if (score > bestScore) {
                bestScore = score;
                bestRule = rule;
                bestStar = star;
            }
        }
    }

    if (bestStar && bestStar->GetEmpireID() != (uint32_t)-1 &&
        bestStar->GetEmpireID() != cSPLivingUniverse::GetPlayerEmpireID()) {
        cEmpire* owner = StarManager()->GetEmpireByID(bestStar->GetEmpireID());
        if (owner && owner->IsAggressive())
            return;
    }

    if (bestRule == kRuleTerraform) {
        if (GetCurrentGameMode() == &sGameModeSpace && cSPLivingUniverse::GetUniverseContext() != 2 &&
            bestStar == cSPLivingUniverse::GetCurrentStar())
            return;
        if (bestStar->GetEmpireID() != empire->mEmpireID)
            return;
        bestStar->SetFlag(0x100, false);
        if (bestStar->mPlanetCount) {
            PlanetVector& planets = bestStar->GetPlanets();
            if (!planets.empty()) {
                for (uint32_t i = 0; i < planets.size(); i++) {
                    if (planets[i]->GetPlanetTechLevel() == 5) {
                        cPlanetRecord* planet = planets[i];
                        if (planet) {
                            SetPlanetTechLevel(planet, 5);
                            planet->mAtmosphereScore = 0.5f;
                            planet->mTemperatureScore = 0.65f;
                            Vector2 range = GetWaterScoreRange(0.5f, 0.65f);
                            planet->mWaterScore = Clamp(planet->mWaterScore, range.x, range.y);
                            planet->mType = 4;
                            if (planet->mFlags & 8) {
                                planet->mFlags &= ~8;
                                StarManager()->ClaimPlanet(planet, 0);
                            }
                            planet->UpdateTerrain();
                            SetPlanetTechLevelData(planet, 5);
                            planet->SetGenerated(true);
                        }
                        break;
                    }
                }
            }
        }
        if (GetCurrentGameMode() == &sGameModeSpace && cSPLivingUniverse::GetUniverseContext() == 2) {
            float radius = GetUFOSimulator()->GetVisibleRadius();
            if (DistanceSquared(bestStar->GetPosition(), cSPLivingUniverse::GetCurrentStar()->GetPosition()) <
                radius * radius) {
                IVisualEffectPtr effect;
                if (EffectsManager()->CreateVisualEffect(0x2edbd996, 0, effect.AsPPTypeParam())) {
                    effect->Start(0);
                    Transform xform;
                    xform.SetOffset(bestStar->GetPosition());
                    effect->SetTransform(xform);
                }
            }
        }
    } else if (bestRule == kRuleRaid) {
        if (GetCurrentGameMode() != &sGameModeSpace)
            return;
        if (bestStar->GetEmpireID() == cSPLivingUniverse::GetPlayerEmpireID() && IsPlayerProtected())
            return;
        if (bestStar->GetTechLevel() != 5)
            return;
        StarManager()->AbandonStar(bestStar, 0);
        PlanetVector& planets = bestStar->GetPlanets();
        uint32_t numPlanets = planets.size();
        for (uint32_t i = 0; i < numPlanets; i++) {
            cPlanetRecord* planet = planets[i];
            if (planet->GetPlanetTechLevel() == 5 && !IsPlanetOwnedByEmpire(planet, empire->mEmpireID)) {
                if (planet) {
                    cSPMission* mission = GetMissionManager()->CreateMissionFromID(
                        bestStar->GetEmpireID() != cSPLivingUniverse::GetPlayerEmpireID() ? 0xbbae6b99 : 0x77184bae,
                        planet, StarManager()->GetEmpireByID(bestStar->GetEmpireID()), 0);
                    cSPRaidEvent* raid;
                    if (mission && (raid = (cSPRaidEvent*)mission->Cast(0x3960c0a)) != 0) {
                        raid->SetAttackerEmpire(empire);
                        raid->SetTargetPlanet(planet);
                        raid->SetBomberCount(raid->GenerateBomberCount());
                        if (bestStar->GetEmpireID() != cSPLivingUniverse::GetPlayerEmpireID())
                            raid->mbShowMessage = false;
                        raid->Accept();
                    }
                    cEmpire* victim = StarManager()->GetEmpireByID(planet->GetStar()->GetEmpireID());
                    RelationshipManager()->DeclareWar(empire, victim);
                    if (victim != cSPLivingUniverse::GetPlayerEmpire()) {
                        EmpireEventMap& events = SpaceGameGet()->mpData->mEmpireEvents;
                        uint32_t victimID = victim->mEmpireID;
                        if (events.find_inline(victimID).mpNode == events.end().mpNode &&
                            events.find(empireID).mpNode == events.end().mpNode)
                            RelationshipManager()->RecordEvent(victimID, empireID, 0x526e53c, 20.0f);
                    }
                }
                break;
            }
        }
    } else if (bestRule == kRuleColonize) {
        if (GetCurrentGameMode() == &sGameModeSpace && cSPLivingUniverse::GetUniverseContext() != 2 &&
            bestStar == cSPLivingUniverse::GetCurrentStar())
            return;
        if (bestStar->GetTechLevel() == 5)
            return;
        cPlanetRecord* planet = 0;
        if (bestStar->mPlanetCount) {
            PlanetVector& planets = bestStar->GetPlanets();
            if (planets.empty())
                return;
            for (uint32_t i = 0; i < planets.size(); i++) {
                cPlanetRecord* p = planets[i];
                if (p->IsColonizable()) {
                    planet = p;
                    break;
                }
            }
            if (!planet)
                return;
        }
        empire->AddStar(bestStar);
        bestStar->SetEmpireID(empireID);
        bestStar->SetTechLevel(5);
        bestStar->SetFlag(0x100, true);
        if (bestStar->mPlanetCount) {
            SetPlanetTechLevel(planet, 5);
            SetPlanetTechLevelData(planet, 5);
            planet->SetGenerated(true);
        }
        if (GetCurrentGameMode() == &sGameModeSpace && cSPLivingUniverse::GetUniverseContext() == 2) {
            float radius = GetUFOSimulator()->GetVisibleRadius();
            if (DistanceSquared(bestStar->GetPosition(), cSPLivingUniverse::GetCurrentStar()->GetPosition()) <
                radius * radius) {
                IVisualEffectPtr effect;
                if (EffectsManager()->CreateVisualEffect(0x2edbd996, 0, effect.AsPPTypeParam())) {
                    effect->Start(0);
                    Transform xform;
                    xform.SetOffset(bestStar->GetPosition());
                    effect->SetTransform(xform);
                }
            }
        }
    } else if (bestRule == kRuleAlliance) {
        uint32_t starEmpireID = bestStar->GetEmpireID();
        if (GetCurrentGameMode() != &sGameModeSpace)
            return;
        if (starEmpireID == cSPLivingUniverse::GetPlayerEmpireID() && IsPlayerProtected())
            return;
        if (bestStar->GetTechLevel() != 5)
            return;
        if (starEmpireID == cSPLivingUniverse::GetPlayerEmpireID()) {
            cEmpire* ownEmpire = StarManager()->GetEmpireByID(empireID);
            cEmpire* playerEmpire = StarManager()->GetEmpireByID(starEmpireID);
            if (RelationshipManager()->IsAllied(empireID, starEmpireID))
                return;
            if (!ownEmpire->HasMetPlayer()) {
                ownEmpire->WelcomePlayer();
                return;
            }
            float chance = GetSpaceRelationshipTuning()->GetAllianceChance(
                RelationshipManager()->GetRelationship(empireID, starEmpireID, 0));
            if (chance > 0.5f)
                CommManager()->ShowCommEvent(ownEmpire->mEmpireID, ownEmpire->GetCommSpeaker(),
                                             ownEmpire->GetHomePlanet(0x95bbbbfc, 0x9431b1f, 2, 0, 0)->GetCommContext());
            else
                CommManager()->ShowCommEvent(ownEmpire->mEmpireID, ownEmpire->GetCommSpeaker(),
                                             ownEmpire->GetHomePlanet(0x95bbbbfc, 0x4fc08a9e, 2, 0, 0)->GetCommContext());
        } else {
            EmpireEventMap& events = SpaceGameGet()->mpData->mEmpireEvents;
            if (events.find(starEmpireID).mpNode == events.end().mpNode &&
                events.find(empireID).mpNode == events.end().mpNode) {
                RelationshipManager()->RecordEvent(starEmpireID, empireID, 0x577909a, 1.0f);
                RelationshipManager()->RecordEvent(empireID, starEmpireID, 0x577909a, 1.0f);
            }
            if (RelationshipManager()->IsAllied(empireID, starEmpireID))
                return;
            float chance = GetSpaceRelationshipTuning()->GetAllianceChance(
                RelationshipManager()->GetRelationship(empireID, starEmpireID, 0));
            if (chance > 0.5f) {
                cEmpire* ownEmpire = StarManager()->GetEmpireByID(empireID);
                cEmpire* otherEmpire = StarManager()->GetEmpireByID(starEmpireID);
                RelationshipManager()->StartAlliance(ownEmpire, otherEmpire);
            }
        }
    } else if (bestRule == kRuleWar) {
        uint32_t starEmpireID = bestStar->GetEmpireID();
        if (GetCurrentGameMode() != &sGameModeSpace)
            return;
        if (starEmpireID == cSPLivingUniverse::GetPlayerEmpireID() && IsPlayerProtected())
            return;
        if (bestStar->GetTechLevel() != 5)
            return;
        if (starEmpireID == cSPLivingUniverse::GetPlayerEmpireID()) {
            cEmpire* ownEmpire = StarManager()->GetEmpireByID(empireID);
            cEmpire* playerEmpire = StarManager()->GetEmpireByID(starEmpireID);
            if (RelationshipManager()->IsAtWar(empireID, starEmpireID))
                return;
            if (!ownEmpire->HasMetPlayer()) {
                ownEmpire->WarnPlayer();
                return;
            }
            float relationship = RelationshipManager()->GetRelationship(empireID, starEmpireID, 0);
            if (GetSpaceRelationshipTuning()->GetWarThreshold() < relationship) {
                if (!ownEmpire->HasDemandedTribute()) {
                    CommManager()->ShowCommEvent(ownEmpire->mEmpireID, ownEmpire->GetCommSpeaker(),
                                                 ownEmpire->GetHomePlanet(0x95bbbbfc, 0x7fc02fbc, 2, 0, 0)->GetCommContext());
                    ownEmpire->SetDemandedTribute();
                }
            } else {
                RelationshipManager()->DeclareWar(ownEmpire, playerEmpire);
            }
        } else {
            EmpireEventMap& events = SpaceGameGet()->mpData->mEmpireEvents;
            if (events.find(starEmpireID).mpNode == events.end().mpNode &&
                events.find(empireID).mpNode == events.end().mpNode) {
                RelationshipManager()->RecordEvent(empireID, starEmpireID, 0x577909b, 1.0f);
                RelationshipManager()->RecordEvent(starEmpireID, empireID, 0x577909b, 1.0f);
            }
            if (RelationshipManager()->IsAtWar(empireID, starEmpireID))
                return;
            float relationship = RelationshipManager()->GetRelationship(empireID, starEmpireID, 0);
            if (GetSpaceRelationshipTuning()->GetWarThreshold() < relationship)
                return;
            cEmpire* ownEmpire = StarManager()->GetEmpireByID(empireID);
            cEmpire* otherEmpire = StarManager()->GetEmpireByID(starEmpireID);
            RelationshipManager()->DeclareWar(ownEmpire, otherEmpire);
        }
    }
}

}  // namespace SP
