// Slice s01038410 — SP::cSpaceTradeRouteManager per-tick update of every trade route:
// validates the route owners, posts relationship warnings, spawns merchant UFOs (galaxy and
// solar views), runs the periodic trade/spice exchange and advances the trade-capture progress.
// PDB candidate (caller-scored): SP::cSpaceTradeRouteManager::UpdateTradeRoutes.
// Layouts: SP::cTradeRouteData / cSpaceTradeRouteManager from the 2008 PDB (they match the asm).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>

// float->int with the current MXCSR rounding (asm helper in the original).
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    Vector3 Normalized() const
    {
        float inv = 1.0f / sqrtf(x * x + y * y + z * z);
        return Vector3(inv * x, y * inv, z * inv);
    }
};
struct Quaternion { float x, y, z, w; };

extern const Vector3 kZAxis;                                                  // 0x15b7d0c
Quaternion QuaternionFromFacingAndUp(const Vector3& facing, const Vector3& up);   // 0x69b600
Vector3 Vector3_Normalize(const Vector3& v);                                 // 0x436ce0

// ---- eastl rbtree pieces ------------------------------------------------------
namespace eastl {
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};
rbtree_node_base* RBTreeIncrement(const rbtree_node_base* pNode);              // 0x921580
void RBTreeErase(rbtree_node_base* pNode, rbtree_node_base* pNodeAnchor);     // 0x921880
}

// ---- simulator types ------------------------------------------------------------
struct cStarRecord {
    uint32_t pad00[0x70 / 4];
    uint32_t mKey;                                    // +0x70
    uint32_t GetPoliticalID();                        // 0xb1fdb0
    const Vector3& GetPosition();                     // 0x5c65e0
    struct CommEntry {
        int GetType();                                // 0xb8dab0
        int GetCommContext();                         // 0xce6950
    };
    struct CommVector { CommEntry** mpBegin; CommEntry** mpEnd; };
    CommVector& GetCommEntries();                     // 0xbba790
};

struct cEmpire {
    uint32_t pad00[0x50 / 4];
    uint32_t mFlags;                                  // +0x50
    uint32_t pad54[12];
    uint32_t mPoliticalID;                            // +0x84
    bool IsAIControlled() const { return (mFlags >> 6) & 1; }
    bool HasRelationshipWarning();                    // 0xc30890
    void SetRelationshipWarning(bool b);              // 0xc30860
};

struct cPlanetRecord;
struct cPlanet {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual int Release();                            // +0xc0
};
struct cPlanetPtr {
    cPlanet* mpObject;
    cPlanetPtr() : mpObject(0) {}
    ~cPlanetPtr() { if (mpObject) mpObject->Release(); }
};
cPlanetRecord* __cdecl GetPlanetRecordForStar(cStarRecord* star);              // 0xc8c420

struct cStarManager {
    cStarRecord* GetStarRecord(uint32_t starID);                                // 0xba6d80
    cEmpire* GetEmpire(uint32_t politicalID);                                   // 0xba9370
    bool GetOrActivatePlanet(cPlanetRecord* record, cPlanetPtr& dst);           // 0xbb59b0
};
namespace SP { cStarManager* StarManager(); }                                  // 0xb3d2a0

struct cLocomotion {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void SetSpeedScale(float s);              // +0x40
};
struct cGameDataBase { uint32_t pad00[0x34 / 4]; };
struct cSPGameDataUFO : cGameDataBase, cLocomotion {
    uint32_t pad38[(0x718 - 0x38) / 4];
    Vector3 mPosition;                                // +0x718
    uint32_t pad724[3];
    Quaternion mOrientation;                          // +0x730
    uint32_t pad740[4];
    Vector3 mDestination;                             // +0x750
    void SetDestinationStar(cStarRecord* star);           // 0xc3c360
    void SetDestinationPlanet(cPlanet* planet);             // 0xc3c190
    void SetDestinationPos(const Vector3& pos);          // 0xc3bfe0
    void PopToDestination();                          // 0xc37e60
};
cSPGameDataUFO* __cdecl CreateUFOForSolarOrGalaxy(int type, cEmpire* empire);   // 0x102ac50
struct cSpaceGame { void AddUFO(cSPGameDataUFO* ufo); };                         // 0x1009a40
namespace SP { cSpaceGame* SpaceGameGet(); }                                     // 0x1002bd0

struct cRelationshipManager {
    float GetRelationship(uint32_t polA, uint32_t polB, int flags);               // 0xd00a10
    float RecordEvent(uint32_t polA, uint32_t polB, uint32_t eventID, float scale);   // 0xd06240
};
namespace SP { cRelationshipManager* RelationshipManager(); }                    // 0xb3d2c0

struct cSPUIEventLog { void PostFeedbackEvent(uint32_t id, uint32_t group, int a, int b, int c, int d); };   // 0xdd8640
namespace SP { cSPUIEventLog* EventLog(); }                                      // 0xb3d3e0

struct cSpaceTokenTranslator {
    uint32_t pad00[4];
    cStarRecord* mpStar;                              // +0x10
    uint32_t pad14[2];
    cEmpire* mpEmpire;                                // +0x1c
};
extern cSpaceTokenTranslator* gpSpaceTokenTranslator;                           // 0x16e0d08

struct cSPSpaceEconomyTuning {
    float GetTradeRouteUFOInterval();                 // 0x10302f0
    float GetTradeRouteShipInterval();                // 0x10302a0
    float GetTradeRouteBundleInterval();              // 0x1030340
    float GetTradeCaptureDistanceBase();              // 0x10301b0
    float GetTradeCaptureDistanceFactor();            // 0x1030160
    float GetTradeCapturePerMS();                     // 0x1030110
    float GetTradeCaptureMinRate();                   // 0x1030200
    float GetTradeCaptureMaxRate();                   // 0x1030250
};
cSPSpaceEconomyTuning* __cdecl SpaceEconomyTuning();                            // 0x102f810

struct cSpaceRelationshipTuning { uint32_t pad00[0x58 / 4]; float mWarnThreshold; float mBreakThreshold; };
namespace SP { cSpaceRelationshipTuning* GetSpaceRelationshipTuning(); }        // 0x10407c0

namespace SP {
int GetUniverseContext();                             // 0x1021080
uint32_t GetPlayerEmpireID();                         // 0x1021090
cEmpire* GetPlayerEmpire();                           // 0x1021300
cStarRecord* GetActiveStarRecord();                   // 0x1021240
}

struct cPlanetTrade { void Exchange(cPlanetRecord* a, cPlanetRecord* b); };     // 0x103af90
cPlanetTrade* __cdecl PlanetTrade();                                             // 0xb3d3d0
struct cStarMap { void FilterHelperRebuild(int flags); };                        // 0x1048c10
cStarMap* __cdecl StarMap();                                                     // 0x1046fc0
struct cCommManager { void ShowCommEvent(uint32_t polID, cStarRecord* star, int ctx, uint32_t id, uint32_t group, int a, int b, int c); };   // 0xaeb3e0
cCommManager* __cdecl CommManager();                                             // 0xb3d4a0

extern const int kMerchantSchedule[10];                                          // 0x14999e0

// ---- trade route data / manager ----------------------------------------------------
struct cTradeRouteData {
    virtual ~cTradeRouteData() {}
    virtual bool Write(void* stream);
    virtual bool Read(void* stream);

    uint32_t mPoliticalID1;          // +0x04
    uint32_t mPoliticalID2;          // +0x08
    uint32_t mStarID1;               // +0x0c
    uint32_t mStarID2;               // +0x10
    float mTradeRouteProgress;       // +0x14
    bool mInDetectableRange;         // +0x18
    uint32_t mTimeSinceLastUFOMS;    // +0x1c
    uint32_t mTimeSinceLastSimMS;    // +0x20
    float mRouteLength;              // +0x24
    int mLastMerchantVoyage;         // +0x28
};

struct TradeKey { uint32_t first, second; };
struct TradeRouteNode : eastl::rbtree_node_base {
    TradeKey mKey;                   // +0x10
    cTradeRouteData mValue;          // +0x18
};

struct TradeRouteMap {
    uint32_t mCompare;               // +0x04 (empty less<>)
    eastl::rbtree_node_base mAnchor; // +0x08
    uint32_t mnSize;                 // +0x18
    uint32_t mAllocator;             // +0x1c

    TradeRouteNode* begin() { return (TradeRouteNode*)mAnchor.mpNodeLeft; }
    TradeRouteNode* end() { return (TradeRouteNode*)&mAnchor; }
    void DoFreeNode(TradeRouteNode* pNode)
    {
        pNode->~TradeRouteNode();
        operator delete[](pNode);   // 0xf47380
    }
    TradeRouteNode* erase(TradeRouteNode* position)
    {
        TradeRouteNode* const iErase = position;
        --mnSize;
        position = (TradeRouteNode*)eastl::RBTreeIncrement(position);
        eastl::RBTreeErase(iErase, &mAnchor);
        DoFreeNode(iErase);
        return position;
    }
};

struct cSpaceTradeRouteManager {
    virtual ~cSpaceTradeRouteManager();
    TradeRouteMap mTradeRoutes;      // +0x04
    uint32_t mLastStarID;            // +0x20

    void UpdateRouteLength(cTradeRouteData* route, Vector3 pos);   // 0x1037c30
    void Update(uint32_t deltaMS);
};

static __forceinline void OrientTowardDestination(cSPGameDataUFO* ufo)
{
    Vector3 dir = (ufo->mDestination - ufo->mPosition).Normalized();
    ufo->mOrientation = QuaternionFromFacingAndUp(dir, kZAxis);
}

void cSpaceTradeRouteManager::Update(uint32_t deltaMS)
{
    bool starChanged = false;
    uint32_t starID = SP::GetActiveStarRecord()->mKey;
    if (mLastStarID != starID) {
        mLastStarID = starID;
        starChanged = true;
    }
    cStarManager* starMgr = SP::StarManager();
    cStarRecord* activeStar = SP::GetActiveStarRecord();
    const Vector3& activePos = activeStar->GetPosition();
    bool inGalaxy = SP::GetUniverseContext() == 2;
    bool inSolar = SP::GetUniverseContext() == 1;
    uint32_t playerID = SP::GetPlayerEmpireID();
    uint32_t solarInterval = RoundToInt(SpaceEconomyTuning()->GetTradeRouteUFOInterval() * 1000.0f);
    uint32_t shipInterval = RoundToInt(SpaceEconomyTuning()->GetTradeRouteShipInterval() * 1000.0f);
    uint32_t bundleInterval = RoundToInt(SpaceEconomyTuning()->GetTradeRouteBundleInterval() * 1000.0f);

    for (TradeRouteNode* it = mTradeRoutes.begin(); it != mTradeRoutes.end(); ) {
        cTradeRouteData& route = it->mValue;
        route.mTimeSinceLastSimMS += deltaMS;
        route.mTimeSinceLastUFOMS += deltaMS;
        cStarRecord* starA = starMgr->GetStarRecord(route.mStarID1);
        cStarRecord* starB = starMgr->GetStarRecord(route.mStarID2);
        if (starA->GetPoliticalID() != route.mPoliticalID1 || starB->GetPoliticalID() != route.mPoliticalID2)
            goto removeRoute;

        cEmpire* empireA = starMgr->GetEmpire(route.mPoliticalID1);
        cEmpire* empireB = starMgr->GetEmpire(route.mPoliticalID2);
        bool involvesPlayer;
        if (empireA == SP::GetPlayerEmpire() || empireB == SP::GetPlayerEmpire())
            involvesPlayer = true;
        else
            involvesPlayer = false;

        if ((!empireA->IsAIControlled() || !empireB->IsAIControlled()) && involvesPlayer) {
            float warnThreshold = SP::GetSpaceRelationshipTuning()->mWarnThreshold;
            float breakThreshold = SP::GetSpaceRelationshipTuning()->mBreakThreshold;
            float relationA;
            if (empireA->IsAIControlled())
                relationA = 10.0f;
            else
                relationA = SP::RelationshipManager()->GetRelationship(route.mPoliticalID1, route.mPoliticalID2, 0);
            float relationB;
            if (empireB->IsAIControlled())
                relationB = 10.0f;
            else
                relationB = SP::RelationshipManager()->GetRelationship(route.mPoliticalID2, route.mPoliticalID1, 0);

            if (route.mPoliticalID1 == playerID || route.mPoliticalID2 == playerID) {
                cEmpire* other = route.mPoliticalID1 == playerID ? empireB : empireA;
                if (relationA < breakThreshold || relationB < breakThreshold) {
                    gpSpaceTokenTranslator->mpEmpire = other;
                    SP::EventLog()->PostFeedbackEvent(0xbcbbca05, 0x131a9f54, 0, 0, 1, 0);
                    other->SetRelationshipWarning(false);
                } else if (relationA < warnThreshold || relationB < warnThreshold) {
                    if (!other->HasRelationshipWarning()) {
                        gpSpaceTokenTranslator->mpEmpire = other;
                        SP::EventLog()->PostFeedbackEvent(0x2c4840c4, 0x131a9f54, 0, 0, 1, 0);
                        other->SetRelationshipWarning(true);
                    }
                } else {
                    other->SetRelationshipWarning(false);
                }
            }
            if (relationA < breakThreshold || relationB < breakThreshold) {
            removeRoute:
                it = mTradeRoutes.erase(it);
                continue;
            }
        }

        if (starChanged)
            UpdateRouteLength(&route, activePos);

        // Galaxy view: merchant ships fly between the two stars.
        if (inGalaxy && route.mInDetectableRange && route.mTimeSinceLastUFOMS > shipInterval) {
            route.mLastMerchantVoyage++;
            route.mTimeSinceLastUFOMS = 0;
            if (route.mLastMerchantVoyage == 10)
                route.mLastMerchantVoyage = 0;
            cEmpire* owner;
            cStarRecord* from = starA;
            cStarRecord* to = starB;
            switch (kMerchantSchedule[route.mLastMerchantVoyage]) {
            case 1:
                owner = starMgr->GetEmpire(route.mPoliticalID1);
                break;
            case 2:
                owner = starMgr->GetEmpire(route.mPoliticalID1);
                from = starB;
                to = starA;
                break;
            case 3:
                owner = starMgr->GetEmpire(route.mPoliticalID2);
                break;
            case 4:
                owner = starMgr->GetEmpire(route.mPoliticalID2);
                from = starB;
                to = starA;
                break;
            default:
                goto galaxyDone;
            }
            if (owner) {
                cSPGameDataUFO* ufo = CreateUFOForSolarOrGalaxy(9, owner);
                ufo->SetDestinationStar(from);
                ufo->PopToDestination();
                ufo->SetSpeedScale(1.0f / 65536.0f);
                ufo->SetDestinationStar(to);
                OrientTowardDestination(ufo);
                SP::SpaceGameGet()->AddUFO(ufo);
            }
        }
    galaxyDone:

        // Solar view: merchant ships fly in from / out to the other star.
        if (inSolar && (activeStar == starA || activeStar == starB) && route.mTimeSinceLastUFOMS > solarInterval) {
            route.mTimeSinceLastUFOMS = 0;
            cPlanetRecord* planetRecord = GetPlanetRecordForStar(activeStar);
            if (planetRecord) {
                cPlanetPtr planet;
                starMgr->GetOrActivatePlanet(planetRecord, planet);
                route.mLastMerchantVoyage++;
                if (route.mLastMerchantVoyage == 10)
                    route.mLastMerchantVoyage = 0;
                cEmpire* owner;
                cPlanet* fromPlanet = 0;
                cPlanet* toPlanet = 0;
                switch (kMerchantSchedule[route.mLastMerchantVoyage]) {
                case 1:
                    owner = starMgr->GetEmpire(route.mPoliticalID1);
                    fromPlanet = planet.mpObject;
                    break;
                case 2:
                    owner = starMgr->GetEmpire(route.mPoliticalID1);
                    toPlanet = planet.mpObject;
                    break;
                case 3:
                    owner = starMgr->GetEmpire(route.mPoliticalID2);
                    fromPlanet = planet.mpObject;
                    break;
                case 4:
                    owner = starMgr->GetEmpire(route.mPoliticalID2);
                    toPlanet = planet.mpObject;
                    break;
                default:
                    goto solarDone;
                }
                if (owner) {
                    Vector3 dir;
                    if (activeStar == starA)
                        dir = Vector3_Normalize(starB->GetPosition() - starA->GetPosition());
                    else
                        dir = Vector3_Normalize(starA->GetPosition() - starB->GetPosition());
                    Vector3 offscreen = dir * 3000.0f;
                    cSPGameDataUFO* ufo = CreateUFOForSolarOrGalaxy(9, owner);
                    if (fromPlanet)
                        ufo->SetDestinationPlanet(fromPlanet);
                    else
                        ufo->SetDestinationPos(offscreen);
                    ufo->PopToDestination();
                    ufo->SetSpeedScale(1.0f / 65536.0f);
                    if (toPlanet)
                        ufo->SetDestinationPlanet(toPlanet);
                    else
                        ufo->SetDestinationPos(offscreen);
                    OrientTowardDestination(ufo);
                    SP::SpaceGameGet()->AddUFO(ufo);
                }
            solarDone:;
            }
        }

        // Periodic trade exchange between the two systems.
        if (route.mTimeSinceLastSimMS > bundleInterval) {
            route.mTimeSinceLastSimMS = 0;
            if (involvesPlayer) {
                cPlanetRecord* recordA = GetPlanetRecordForStar(starA);
                cPlanetRecord* recordB = GetPlanetRecordForStar(starB);
                if (recordA && recordB)
                    PlanetTrade()->Exchange(recordA, recordB);
                if (starA->GetPoliticalID() == playerID)
                    SP::RelationshipManager()->RecordEvent(starB->GetPoliticalID(), starA->GetPoliticalID(), 0x667af08, 1.0f);
                else if (starB->GetPoliticalID() == playerID)
                    SP::RelationshipManager()->RecordEvent(starA->GetPoliticalID(), starB->GetPoliticalID(), 0x667af08, 1.0f);
            }
        }

        // Trade capture progress.
        if (involvesPlayer) {
            float scale = route.mRouteLength / SpaceEconomyTuning()->GetTradeCaptureDistanceBase();
            scale = SpaceEconomyTuning()->GetTradeCaptureDistanceFactor() * scale + 1.0f;
            float rate = SpaceEconomyTuning()->GetTradeCapturePerMS() / scale;
            float minRate = SpaceEconomyTuning()->GetTradeCaptureMinRate();
            float maxRate = SpaceEconomyTuning()->GetTradeCaptureMaxRate();
            rate = Clamp(rate, minRate, maxRate);
            float prevProgress = route.mTradeRouteProgress;
            bool wasCaptured = prevProgress >= 100.0f;
            route.mTradeRouteProgress = (float)deltaMS * rate + prevProgress;
            if (route.mTradeRouteProgress > 100.0f)
                route.mTradeRouteProgress = 100.0f;
            if (route.mTradeRouteProgress >= 100.0f && !wasCaptured) {
                StarMap()->FilterHelperRebuild(1);
                uint32_t player = SP::GetPlayerEmpireID();
                cStarRecord* other = 0;
                if (starA->GetPoliticalID() == player)
                    other = starB;
                if (starB->GetPoliticalID() == player)
                    other = starA;
                if (other) {
                    gpSpaceTokenTranslator->mpStar = other;
                    cEmpire* empire = starMgr->GetEmpire(other->GetPoliticalID());
                    gpSpaceTokenTranslator->mpEmpire = empire;
                    int commContext = -1;
                    cStarRecord::CommVector& entries = other->GetCommEntries();
                    int count = entries.mpEnd - entries.mpBegin;
                    for (int i = 0; i < count; i++) {
                        if (entries.mpBegin[i]->GetType() == 5)
                            commContext = entries.mpBegin[i]->GetCommContext();
                    }
                    CommManager()->ShowCommEvent(empire->mPoliticalID, other, commContext, 0x95bbbbfc, 0xdd33319c, 1, 0, 0);
                }
            }
        }

        it = (TradeRouteNode*)eastl::RBTreeIncrement(it);
    }
}
