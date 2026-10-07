// Slice s010593e0: space-tool hit handler (SP tool strategy OnHit, vtable slot 0x30).
// /O2 /MD /Gy /TP /arch:SSE /fp:fast (fsqrt inline; no /EHsc: the stack message has a dtor but there is no EH frame).
// Out-of-line callees are declared only; their original addresses are in the trailing comments.
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float SquaredLength() const { return z * z + y * y + x * x; }
};
inline Vector3 operator-(const Vector3& a, const Vector3& b) {
    Vector3 r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float fabsf_(float x) { return (float)fabs(x); }

struct ResourceKey {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
    ResourceKey() : mInstanceID(0), mTypeID(0), mGroupID(0) {}
};
inline bool KeyMatches(const ResourceKey& a, const ResourceKey& b) {
    return a.mInstanceID == b.mInstanceID && a.mTypeID == b.mTypeID && a.mGroupID == b.mGroupID;
}
bool operator==(const ResourceKey& a, const ResourceKey& b);       // 0x004eb930 (out of line, /Od module)

// Tool IDs (ResourceKey globals).
extern ResourceKey kToolCashInfusion;                               // 0x016e1f64
extern ResourceKey kToolPlanetConversion;                           // 0x016e1fd0
extern ResourceKey kToolCallForBackup;                              // 0x016e1fa0
extern ResourceKey kToolRaiderRally;                                // 0x016e1fc4
extern float gMaxRelationshipToolRadius;                            // 0x014853bc (30.0)

template<typename T> inline const T& min_alt(const T& a, const T& b) { return (b < a) ? b : a; }

// ---- messaging ---------------------------------------------------------------------------------
extern "C" long __cdecl _InterlockedExchange(volatile long* target, long value);
#pragma intrinsic(_InterlockedExchange)
struct AtomicInt {
    volatile long mValue;
    AtomicInt() { _InterlockedExchange(&mValue, 0); }
};
class BehaviorMessage {
public:
    BehaviorMessage() {}
    virtual void v0();
    AtomicInt mRefCount;                                            // +0x04
};
// MessageBasicRC<5> (vtable 0x013eb844); the dtor is SlotMessage::Destruct.
class ToolHitMessage : public BehaviorMessage {
public:
    ToolHitMessage() : mMessageID(0), mFlags(0) {}
    ~ToolHitMessage();                                              // 0x00421cf0
    virtual void v0();
    struct Slot { const void* mpData; uint32_t mType; };
    Slot mData[5];                                                  // +0x08
    uint32_t mMessageID;                                            // +0x30
    uint32_t pad34;
    uint32_t mFlags;                                                // +0x38
    uint32_t pad3c;
};
class IMessageServer {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void MessageSend(uint32_t messageID, void* pMessage, int flags);   // +0x14
};

// ---- simulator types (stubs; only the members used here) ----------------------------------------
class cPlanet;
class cPlanetRecord;
class cStarRecord;

class cSpaceToolData {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05();
    virtual const ResourceKey& GetToolID();                         // +0x18
    virtual void v07(); virtual void v08(); virtual void v09(); virtual void v0a();
    virtual void v0b(); virtual void v0c(); virtual void v0d();
    virtual ResourceKey GetStrategyKey();                           // +0x38

    uint32_t pad04[(0x30 - 0x04) / 4];
    int mbEnabled;                                                  // +0x30
    uint32_t pad34[(0x114 - 0x34) / 4];
    class cGameObject* mpToolOwner;                                 // +0x114

    int GetTerrainColorIndex();                                     // 0x0104bf70
    int GetWaterColorIndex();                                       // 0x0104bf80
    int GetAtmosphereColorIndex();                                  // 0x0104bf90
    float GetDamage();                                              // 0x0104bdc0
    float GetRelationshipDelta();                                   // 0x0104beb0
    float GetGalacticRelationshipDelta();                           // 0x0104bec0
    float GetGalacticRelationshipRadius();                          // 0x0104bed0
    float GetHitGroundAtmosphereVelocity();                         // 0x0104c040
    float GetHitGroundWaterVelocity();                              // 0x0104c050
    float GetHitGroundTemperatureVelocity();                        // 0x0104c060
    float GetHitWaterAtmosphereVelocity();                          // 0x0104c070
    float GetHitWaterWaterVelocity();                               // 0x0104c080
    float GetHitWaterTemperatureVelocity();                         // 0x0104c090
    float GetHitCombatantAtmosphereVelocity();                      // 0x0104c0a0
    float GetHitCombatantWaterVelocity();                           // 0x0104c0b0
    float GetHitCombatantTemperatureVelocity();                     // 0x0104c0c0
    float GetHitAirAtmosphereVelocity();                            // 0x0104c0d0
    float GetHitAirWaterVelocity();                                 // 0x0104c0e0
    float GetHitAirTemperatureVelocity();                           // 0x0104c0f0
    float GetDamageRadius();                                        // 0x00ce6930
};

class cSpaceShip {                                                  // owner cast target 0xb033b403
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual uint32_t GetPoliticalID();                              // +0x4c
    uint32_t pad04[(0x714 - 0x04) / 4];
    int mnDisabled;                                                 // +0x714
};
class cGameObject {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d();
    virtual cSpaceShip* Cast(uint32_t typeID);                      // +0xb8
};

class cLocatable {                                                  // embedded at +0x120
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual const Vector3& GetPosition();                           // +0x2c
};
class cCity {                                                       // the city/colony hit by the tool
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual uint32_t GetPoliticalID();                              // +0x4c
    uint32_t pad04[(0x120 - 0x04) / 4];
    cLocatable mLocation;                                           // +0x120
    bool IsPointInside(const Vector3& position);                    // 0x00bd9c00
    void OnAttacked();                                              // 0x00bdbf10
};
class cTribe {
public:
    uint32_t pad00[0x120 / 4];
    cLocatable mLocation;                                           // +0x120
};

class cNounManager {
public:
    void* GetCityList();                                            // 0x00ace2c0
    void* GetTribeList();                                           // 0x00acd9d0
};
cNounManager* NounManager();                                        // 0x00b3d300
cCity* FindCityAt(void* cities, const Vector3& position);           // 0x00ac9dd0
cTribe* FindTribeAt(void* tribes, const Vector3& position);         // 0x00c52f80

class cTerraformingManager {
public:
    void AddAtmosphere(cPlanet* planet, float amount);              // 0x00bbc340
    void AddWater(cPlanet* planet, float amount);                   // 0x00bbc370
    void AddTemperature(cPlanet* planet, float amount);             // 0x00bbc3c0
};
cTerraformingManager* TerraformingManager();                        // 0x00b3d430

class cPlanetPainter {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c();
    virtual void SetColorIndices(int terrain, int atmosphere, int water);       // +0x74
    virtual void GetColorIndices(int* terrain, int* atmosphere, int* water);    // +0x78
};
cPlanetPainter* PlanetPainter();                                    // 0x00f48aa0

class cRelationshipManager {
public:
    float RecordEvent(uint32_t empireA, uint32_t empireB, uint32_t eventID, float scale);  // 0x00d06240
};
cRelationshipManager* RelationshipManager();                        // 0x00b3d2c0
void DoCommunityReaction(cCity* city, float delta, const Vector3& position);   // 0x00ff5270
void DoCommunityReaction(cTribe* tribe, float delta, const Vector3& position);  // 0x00ff5270

class cMissionManager {
public:
    bool DoMissionsPreventHostility(cPlanet* planet, const ResourceKey& toolID);   // 0x00fedea0
    void* CreateMissionFromID(uint32_t missionID, cPlanetRecord* planet, int a, int b);   // 0x00fec590
};
cMissionManager* GetMissionManager();                               // 0x00feb9f0

class cEmpire;
class cPlayerEmpireHolder {
public:
    uint32_t pad00[0x70 / 4];
    uint32_t mHomeStarID;                                           // +0x70
    uint32_t GetEmpireID();                                         // 0x00b1fdb0
    cStarRecord* GetHomeStar();                                     // 0x005c65e0
};
cPlayerEmpireHolder* GetPlayerEmpire();                             // 0x01021240
uint32_t GetPlayerEmpireID();                                       // 0x01021090
cPlanet* GetActivePlanet();                                         // 0x01021260
cPlanetRecord* GetActivePlanetRecord();                             // 0x010212a0
int GetUniverseContext();                                           // 0x01021080
IMessageServer* MessageServer();                                    // 0x0067dcc0

class cEmpireOwner {
public:
    uint32_t GetEmpireID();                                         // 0x00b1fdb0
};
class cPlanetRecord {
public:
    cEmpireOwner* GetOwner();                                       // 0x00b8de30
    void* GetTradeRouteStar();                                      // 0x00b8d8f0
};
class cTradeRouteManager {
public:
    bool HasTradeRoute(void* star, uint32_t empireID);              // 0x01037d30
    void ResetPlayerProgressOnTradeRoute(void* star, uint32_t empireID, float amount);   // 0x01037eb0
};

namespace eastl {
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};
rbtree_node_base* RBTreeIncrement(const rbtree_node_base* pNode);  // 0x00921580
struct rbtree_node : public rbtree_node_base { uint32_t mValue; };
struct insert_result { rbtree_node_base* mpNode; bool mbInserted; };
// eastl::set<uint32_t>
struct uint_set {
    uint32_t mCompare;
    rbtree_node_base mAnchor;
    size_t mnSize;
    uint32_t mAllocator;
    __forceinline uint_set() : mAnchor(), mnSize(0) {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
    ~uint_set() { DoNuke((rbtree_node*)mAnchor.mpNodeParent); }
    insert_result insert(const uint32_t& value);                    // 0x00a18440
    void DoNuke(rbtree_node* pNode);                                // 0x009a9600
};
// eastl::vector<AutoRefCount<cStarRecord>, sp_vector_allocator>
struct star_vector {
    cStarRecord** mpBegin;
    cStarRecord** mpEnd;
    cStarRecord** mpCapacity;
    uint32_t mAllocator[2];
    star_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~star_vector();                                                 // 0x00ae6970
};
}

class cStarRecord {
public:
    uint32_t GetEmpireID();                                         // 0x00b1fdb0
};
struct tStarSearchCriteria {
    uint32_t mStarTypes;
    uint32_t mTechLevels;                                           // +0x04
    uint32_t mFlags;
    float mMinDistance;                                             // +0x0c
    float mMaxDistance;                                             // +0x10
    float field_14;
    uint32_t field_18;
    tStarSearchCriteria();                                          // 0x00ba6880
};
class cStarManager {
public:
    void UpdateStarRecords();                                       // 0x00885c90
    cTradeRouteManager* GetTradeRouteManager();                     // 0x00ba6490
    void GetStarRecords(cStarRecord* center, const tStarSearchCriteria& criteria, eastl::star_vector& results);  // 0x00bb1080
    cEmpire* GetEmpireByID(uint32_t empireID);                      // 0x00ba9370
};
cStarManager* StarManager();                                        // 0x00b3d2a0

// planet-conversion comm event
struct CommEventSource { uint32_t pad[1]; };
extern CommEventSource gPlanetConversionComm;                       // 0x016f8fdb4
void CreateCommEvent(CommEventSource* source, cEmpire* empire, const ResourceKey& a, const ResourceKey& b,
                     uint32_t starID, int flags, const ResourceKey& c, const ResourceKey& d);   // 0x00e39ab0
void ConvertPlanetToEmpire(cPlayerEmpireHolder* holder, uint32_t empireID);        // 0x00c35240

// call-for-backup
class cTerrainSphere {
public:
    uint32_t pad00[0x124c / 4];
    uint32_t mnMaxPosseSize;                                        // +0x124c
    void DismissPosseMember(int index);                             // 0x00c755c0
};
class cNounManager2 {
public:
    cTerrainSphere* GetPosseHolder();                               // 0x00f67d90
};
cNounManager2* NounManager2();                                      // 0x00b3d300 (same accessor)
struct PosseList { PosseList* mpNext; PosseList* mpPrev; };
class cPosseMember {
public:
    void SetTargetPosition(const Vector3& position);                // 0x00c3be70
    void SetTargetDistance(float distance);                         // 0x00c3daa0
    void MoveTo(const Vector3& position);                           // 0x00c3dae0
};
class cUFOSimulator {
public:
    PosseList* GetPosse();                                          // 0x0108db30
    cPosseMember* AddPosseMember(uint32_t empireID, int count);     // 0x010027b0
};
cUFOSimulator* GetUFOSimulator();                                   // 0x00ffbe50

// raider rally
class cRaidEvent {
public:
    uint32_t pad00[0x21c / 4];
    uint8_t pad21c[2];
    bool mbPlayerOwned;                                             // +0x21e
    void SetIsPlanetOwned(int flag);                                // 0x00c5b370
    void SetIsRallied(int flag);                                    // 0x00c5b360
    void SetTargetPlanet(cPlanetRecord* planet);                    // 0x00c47180
    int GenerateBomberCount();                                      // 0x00c5b530
    void SetBomberCount(int count);                                 // 0x00c5b390
    void SetRallyPoint(Vector3 position);                           // 0x00c5b3a0
    void Accept();                                                  // 0x00c485b0
};
cRaidEvent* CastToRaidEvent(void* mission);                         // 0x00b67700
void PreparePlanetForRaid(cPlanet* planet);                         // 0x0102c0c0

// Space game / owner chain (start-of-function strategy notification and raid UI hint).
class cGameDataOwner {
public:
    void Notify(int what, int flag);                                // 0x00fe5430
};
class cSpaceGame {
public:
    cGameDataOwner* GetDataOwner();                                 // 0x00bfc5f0
    class cPlayer* GetPlayer();                                     // 0x00b1fdb0
};
class cPlayer {
public:
    void ShowHint(const Vector3& position, uint32_t hintID);        // 0x00ff8e00
};
cSpaceGame* SpaceGameGet();                                         // 0x01002bd0

namespace SP {

class cSPToolStrategy {
public:
    bool OnHit(cSpaceToolData* pTool, const Vector3& position, int hitType, int);
};

__forceinline bool IsWithinToolRadius(cSpaceToolData* pTool, cLocatable& target, const Vector3& position) {
    Vector3 diff = target.GetPosition() - position;
    float radius = pTool->GetDamageRadius();
    return diff.SquaredLength() < radius * radius;
}

// @ 0x010593e0
bool cSPToolStrategy::OnHit(cSpaceToolData* pTool, const Vector3& position, int hitType, int) {
    if (!pTool || !pTool->mbEnabled)
        return true;

    cPlanet* planet = GetActivePlanet();
    float atmosphere = 0.0f;
    float water = 0.0f;
    float temperature = 0.0f;
    switch (hitType) {
    case 1:
        atmosphere = pTool->GetHitGroundAtmosphereVelocity();
        water = pTool->GetHitGroundWaterVelocity();
        temperature = pTool->GetHitGroundTemperatureVelocity();
        break;
    case 2:
        atmosphere = pTool->GetHitWaterAtmosphereVelocity();
        water = pTool->GetHitWaterWaterVelocity();
        temperature = pTool->GetHitWaterTemperatureVelocity();
        break;
    case 0:
        atmosphere = pTool->GetHitCombatantAtmosphereVelocity();
        water = pTool->GetHitCombatantWaterVelocity();
        temperature = pTool->GetHitCombatantTemperatureVelocity();
        break;
    case 3:
        atmosphere = pTool->GetHitAirAtmosphereVelocity();
        water = pTool->GetHitAirWaterVelocity();
        temperature = pTool->GetHitAirTemperatureVelocity();
        break;
    }

    if (pTool->GetStrategyKey().mInstanceID == 0xdcf656ba || pTool->GetStrategyKey().mInstanceID == 0xd9e70264) {
        SpaceGameGet()->GetDataOwner()->Notify(0x17, 1);
        MessageServer()->MessageSend(0xf46092db, 0, 0);
    }

    if (GetUniverseContext() != 0)
        return true;

    ToolHitMessage msg;
    ResourceKey toolID = pTool->GetToolID();
    msg.mData[0].mpData = &toolID;
    MessageServer()->MessageSend(0x56690bb, &msg, 0);

    cPlanetPainter* pPainter = PlanetPainter();
    cTerraformingManager* pTerraforming;
    if (pPainter && (pTerraforming = TerraformingManager()) != 0) {
        pTerraforming->AddAtmosphere(planet, atmosphere);
        pTerraforming->AddWater(planet, water);
        pTerraforming->AddTemperature(planet, temperature);
        if (pTool->GetWaterColorIndex() > -1 || pTool->GetAtmosphereColorIndex() > -1 || pTool->GetTerrainColorIndex() > -1) {
            int curTerrain, curAtmosphere, curWater;
            pPainter->GetColorIndices(&curTerrain, &curAtmosphere, &curWater);
            int newTerrain = -1;
            int newWater = -1;
            int newAtmosphere = -1;
            if ((uint32_t)pTool->GetTerrainColorIndex() <= 64 && pTool->GetTerrainColorIndex() != curTerrain)
                newTerrain = pTool->GetTerrainColorIndex();
            if (pTool->GetWaterColorIndex() > -1 && (uint32_t)pTool->GetWaterColorIndex() < 16 && pTool->GetWaterColorIndex() != curWater)
                newWater = pTool->GetWaterColorIndex();
            if (pTool->GetAtmosphereColorIndex() > -1 && (uint32_t)pTool->GetAtmosphereColorIndex() < 16 && pTool->GetAtmosphereColorIndex() != curAtmosphere)
                newAtmosphere = pTool->GetAtmosphereColorIndex();
            pPainter->SetColorIndices(newTerrain, newAtmosphere, newWater);
        }
    }

    cGameObject* pOwner = pTool->mpToolOwner;
    cSpaceShip* pShip;
    if (pOwner && (pShip = pOwner->Cast(0xb033b403)) != 0 && pShip->mnDisabled == 0) {
        if (!GetMissionManager()->DoMissionsPreventHostility(GetActivePlanet(), pTool->GetToolID())) {
            cNounManager* pNouns = NounManager();
            void* pCities = pNouns->GetCityList();
            cCity* pCity = FindCityAt(pCities, position);
            if (pCity) {
                uint32_t shipEmpire = pShip->GetPoliticalID();
                if (pCity->GetPoliticalID() != shipEmpire &&
                    (pCity->IsPointInside(position) || IsWithinToolRadius(pTool, pCity->mLocation, position))) {
                    if (pTool->GetDamage() > 0.0f && !pCity->IsPointInside(position) &&
                        IsWithinToolRadius(pTool, pCity->mLocation, position))
                        pCity->OnAttacked();

                    float delta = pTool->GetRelationshipDelta();
                    float reaction = 0.0f;
                    if (delta > 0.0f)
                        reaction = RelationshipManager()->RecordEvent(pCity->GetPoliticalID(), GetPlayerEmpireID(), 0x526e56a, delta);
                    if (delta < 0.0f)
                        reaction = RelationshipManager()->RecordEvent(pCity->GetPoliticalID(), GetPlayerEmpireID(), 0x526e545, fabsf_(delta));
                    DoCommunityReaction(pCity, reaction, pCity->mLocation.GetPosition());
                }
            }
            void* pTribes = pNouns->GetTribeList();
            cTribe* pTribe = FindTribeAt(pTribes, position);
            if (pTribe && IsWithinToolRadius(pTool, pTribe->mLocation, position))
                DoCommunityReaction(pTribe, pTool->GetRelationshipDelta(), pTribe->mLocation.GetPosition());
        }

        if (pTool->GetGalacticRelationshipDelta() != 0.0f && pTool->GetGalacticRelationshipRadius() > 0.0f) {
            uint32_t playerEmpire = GetPlayerEmpireID();
            StarManager()->UpdateStarRecords();
            float delta = pTool->GetGalacticRelationshipDelta();
            float radius = pTool->GetGalacticRelationshipRadius();
            uint32_t eventID;
            if (delta > 0.0f)
                eventID = 0x526e56a;
            if (delta < 0.0f) {
                delta = fabsf_(delta);
                eventID = 0x68b2971;
            }
            float maxRadius = gMaxRelationshipToolRadius;
            radius = min_alt(radius, maxRadius);

            tStarSearchCriteria criteria;
            criteria.mMinDistance = -1.0f;
            criteria.mMaxDistance = radius;
            criteria.mTechLevels = 0x20;
            eastl::star_vector stars;
            StarManager()->GetStarRecords(GetPlayerEmpire()->GetHomeStar(), criteria, stars);

            eastl::uint_set empires;
            for (cStarRecord** it = stars.mpBegin; it != stars.mpEnd; ++it) {
                uint32_t empireID = (*it)->GetEmpireID();
                empires.insert(empireID);
            }
            for (eastl::rbtree_node_base* pNode = empires.mAnchor.mpNodeLeft; pNode != &empires.mAnchor;
                 pNode = eastl::RBTreeIncrement(pNode)) {
                uint32_t empireID = ((eastl::rbtree_node*)pNode)->mValue;
                if (empireID != playerEmpire)
                    RelationshipManager()->RecordEvent(empireID, playerEmpire, eventID, delta);
            }
        }
    }

    if (KeyMatches(pTool->GetToolID(), kToolCashInfusion)) {
        cPlanetRecord* pRecord = GetActivePlanetRecord();
        if (pRecord) {
            uint32_t ownerID = pRecord->GetOwner()->GetEmpireID();
            if (ownerID != (uint32_t)-1 && ownerID != GetPlayerEmpireID()) {
                cTradeRouteManager* pTradeRoutes = StarManager()->GetTradeRouteManager();
                if (pTradeRoutes->HasTradeRoute(pRecord->GetTradeRouteStar(), ownerID))
                    pTradeRoutes->ResetPlayerProgressOnTradeRoute(pRecord->GetTradeRouteStar(), ownerID, 100.0f);
            }
        }
    } else if (KeyMatches(pTool->GetToolID(), kToolPlanetConversion)) {
        CreateCommEvent(&gPlanetConversionComm,
                        StarManager()->GetEmpireByID(GetPlayerEmpire()->GetEmpireID()),
                        ResourceKey(), ResourceKey(), GetPlayerEmpire()->mHomeStarID, 0, ResourceKey(), ResourceKey());
        ConvertPlanetToEmpire(GetPlayerEmpire(), GetPlayerEmpireID());
    } else if (pTool->GetToolID() == kToolCallForBackup) {
        PosseList* pPosse = GetUFOSimulator()->GetPosse();
        uint32_t count = 0;
        for (PosseList* p = pPosse->mpNext; p != pPosse; p = p->mpNext)
            ++count;
        if (count == NounManager2()->GetPosseHolder()->mnMaxPosseSize)
            NounManager2()->GetPosseHolder()->DismissPosseMember(1);
        cPosseMember* pMember = GetUFOSimulator()->AddPosseMember(GetPlayerEmpireID(), 1);
        pMember->SetTargetPosition(position);
        pMember->SetTargetDistance((float)sqrt(position.x * position.x + (position.y * position.y + position.z * position.z)));
        pMember->MoveTo(position);
    } else if (pTool->GetToolID() == kToolRaiderRally) {
        cRaidEvent* pRaid = CastToRaidEvent(GetMissionManager()->CreateMissionFromID(0xbe436935, GetActivePlanetRecord(), 0, 0));
        if (pRaid) {
            PreparePlanetForRaid(GetActivePlanet());
            pRaid->SetIsPlanetOwned(0);
            pRaid->SetIsRallied(1);
            pRaid->SetTargetPlanet(GetActivePlanetRecord());
            pRaid->SetBomberCount(pRaid->GenerateBomberCount());
            pRaid->SetRallyPoint(position);
            pRaid->mbPlayerOwned = false;
            pRaid->Accept();
            cPlayer* pPlayer = SpaceGameGet()->GetPlayer();
            pPlayer->ShowHint(position, 0x638207a);
        }
    }
    return true;
}

}
