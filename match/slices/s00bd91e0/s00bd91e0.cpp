// SporeApp.exe slice s00bd91e0 -- Simulator::cCity (footprint, layouts, culture targets) (gold6, worker 36)

#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// math / resource types
// ---------------------------------------------------------------------------

struct Vector3 {
    float x;                                                // +0x00
    float y;                                                // +0x04
    float z;                                                // +0x08
};

struct Vector4 {
    float x;                                                // +0x00
    float y;                                                // +0x04
    float z;                                                // +0x08
    float w;                                                // +0x0c
};

struct Quaternion {
    float x;                                                // +0x00
    float y;                                                // +0x04
    float z;                                                // +0x08
    float w;                                                // +0x0c
};

// Localized-text / callout key.
struct ResourceKey {
    uint32_t mInstanceID;                                   // +0x00
    uint32_t mGroupID;                                      // +0x04
    uint32_t mTypeID;                                       // +0x08
};

template <class T>
struct cVec {
    T*       mpBegin;                                       // +0x00
    T*       mpEnd;                                         // +0x04
    T*       mpCapacity;                                    // +0x08
    void*    mpAllocator;                                   // +0x0c
    uint32_t mPad10;                                        // +0x10

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T&       operator[](uint32_t nIndex) const { return mpBegin[nIndex]; }
};

// ---------------------------------------------------------------------------
// game objects
// ---------------------------------------------------------------------------

struct cCity;
struct cAnimatingCreature;

struct cGameData {
    virtual void       AddRef();                            // +0x00
    virtual void       Release();                           // +0x04
    virtual void       v08();                               // +0x08
    virtual cGameData* Cast(uint32_t nType);                // +0x0c
};

struct cPlanetModel {
    int32_t  GetContinent(const Vector3* pPosition);        // 0x00b88590
    Quaternion* BuildSurfaceOrientation(Quaternion* pOut, const Vector3* pPosition);  // 0x00b7f190
    Quaternion* BuildSurfaceOrientation2(Quaternion* pOut, const Vector3* pDirection,
                                         const Vector3* pPosition);                   // 0x00b7f250
    Vector3* GetSurfacePosition(Vector3* pOut, const Vector3* pPosition);           // 0x00b81630
};

struct cGameTimeManager {
    void IncPauseGate(uint32_t nGate);                      // 0x00b32220
};

struct cGameNounManager {
    cGameData* CreateNoun(uint32_t nNounID);                // 0x00b20c60
    int32_t    GetAvatar();                                 // 0x00b1fdb0
    void*      GetPlayerCivilization();                     // 0x00b25fb0
    void*      GetCurrentTerrainSphere();                   // 0x00f67d90
};

struct cStarEmpire;
struct cStarManager {
    cStarEmpire* GetEmpireByID(int32_t nEmpireID);          // 0x00ba9370
    cGameData*   GetEmpireData(cStarEmpire* pEmpire);       // 0x00baf700
};

struct cTerraformingManager {
    bool HasEvent(void* pOwner);                            // 0x00bbe5c0
};

struct cCivilization {
    uint8_t CanUseSuperweapon(bool bValue);                 // 0x00bf8a00
    char    mPad000[0xc4];                                  // +0x000 .. +0xc3
    uint8_t mDataC4;                                        // +0xc4
};

struct cHtmlReport {
    void AppendNumbers(int32_t nBuildingCount, int32_t nRoboPopulation, float fValue);   // 0x00ceeb20
};

struct cCivModeStrategy {
    static cCivModeStrategy* Get();                         // 0x00cf74c0
    void DoCityAction(void* pOwner, cCity* pCity, uint32_t nActionID, uint32_t nActionData,
                      const Vector3* pPosition, const Vector4* pParams, int32_t nA, int32_t nB);   // 0x00cf9110
};

// A modifier/feature object stored in an attack-target slot.
struct cSlotObjectVtbl {
    void* mpSlots00[0x30];                                  // +0x00 .. +0xbf
    void (*pRelease)(void* pThis);                          // +0xc0
};

struct cSlotObject {
    cSlotObjectVtbl* mpVtbl;                                // +0x00
};

struct cModeHelper;
cModeHelper* __cdecl GetLiveSimulator();                    // 0x00b3d240

// One slot of a city layout.
struct cLayoutSlot {
    cGameData* GetObject();                                 // 0x00fcc210
    void       Reserve(cGameData* pObject);                 // 0x00afa030

    bool       mbIsOccupied;                                // +0x00
    uint32_t   mPad04;                                      // +0x04
    cGameData* mpObject;                                    // +0x08
    Vector3    mPosition;                                   // +0x0c
};

// Ring of slots a city lays buildings / turrets on.
struct cCommunityLayout {
    cLayoutSlot* SlotAt(uint32_t nIndex);                   // 0x00af9ff0
    cLayoutSlot* FindSlotAt(const Vector3* pPosition);      // 0x00afad70
    void         SetAtCenter(const Vector3* pCenter, float fRadius, const Vector3* pFacing); // 0x00af9cf0
    void         EmitCopy(void* pOwner, float fScale);      // 0x00afec00

    Vector3           mDirection;                           // +0x00
    float             mField0C;                             // +0x0c
    float             mField10;                             // +0x10
    Vector3           mOrigin;                              // +0x14
    float             mField20;                             // +0x20
    int32_t           mField24;                             // +0x24
    bool              mbField28;                            // +0x28
    Quaternion        mOrientation;                         // +0x2c
    cVec<int32_t>     mField3C;                             // +0x3c
    cVec<cLayoutSlot> mSlots;                               // +0x50 .. +0x63
};

// World transform holder embedded in world objects (cCity+0x120, buildings+0x120, ...).
struct cSpatialObject {
    virtual void     v00();                                 // +0x00
    virtual void     v04();                                 // +0x04
    virtual void     v08();                                 // +0x08
    virtual void     v0c();                                 // +0x0c
    virtual void     v10();                                 // +0x10
    virtual void     v14();                                 // +0x14
    virtual void     v18();                                 // +0x18
    virtual void     v1c();                                 // +0x1c
    virtual void     v20();                                 // +0x20
    virtual void     v24();                                 // +0x24
    virtual void     v28();                                 // +0x28
    virtual Vector3*    GetPosition(const Vector4* pParams);   // +0x2c
    virtual Quaternion* GetOrientation();                   // +0x30
    virtual void        v34();                              // +0x34
    virtual void     SetPosition(const Vector3* pValue);    // +0x38
    virtual void     SetOrientation(const Quaternion* pValue);   // +0x3c
    virtual void     v40();                                 // +0x40
    virtual void     v44();                                 // +0x44
    virtual void     v48();                                 // +0x48
    virtual void     v4c();                                 // +0x4c
    virtual void     v50();                                 // +0x50
    virtual void     v54();                                 // +0x54
    virtual void*    GetPlanetPosition(void* pOut);         // +0x58
    virtual void*    v5c(void* pOut, float fAltitude);      // +0x5c

    int32_t GetObjectCount();                               // 0x008e7f80
};

// Transform holder embedded in a city hall (cCity+0x320, object+0x34).
struct cHallObject {
    virtual void     v00(void* pArg);                       // +0x00
    virtual void     v04();
    virtual void     v08();
    virtual void     v0c();
    virtual void     v10();
    virtual void     v14();
    virtual void     v18();
    virtual void     v1c();
    virtual void     v20();
    virtual void     v24();
    virtual void     v28();
    virtual Vector3*    GetPosition();                      // +0x2c
    virtual Quaternion* GetOrientation();                   // +0x30
    virtual void        v34();                              // +0x34
    virtual void        SetPosition(const Vector3* pValue); // +0x38
    virtual void        SetOrientation(const Quaternion* pValue);   // +0x3c
};

// City walls object: footprint centre and radius.
struct cWallsVtbl {
    void*    mpSlots00[0x1b];                               // +0x00 .. +0x6b
    int32_t (*pGetState)(void* pThis);                      // +0x6c
};

struct cCityWalls {
    cWallsVtbl* mpVtbl;                                     // +0x000
    char        mPad004[0x258];                             // +0x004 .. +0x25b
    float       mRadius;                                    // +0x25c

    int32_t     GetState();                                 // vtable slot +0x6c
    void        GetCenter(Vector3* pOut);                   // 0x00bec190
    bool        ContainsPoint(const Vector3* pPoint);       // 0x00bec0f0
    Vector3*    RequestPosition(Vector3* pOut, int32_t nWhich);   // 0x00bec2d0
};

// World-object vtable slots used by the city (position of the object itself).
struct cCityObjectVtbl {
    void*    mpSlots00[0x23];                               // +0x00 .. +0x8b
    Vector3* (__fastcall* pGetPosition)(void* pThis);       // +0x8c
};

// Generic world object as seen by the city (city hall, decorative building).
struct cCityObject {
    cCityObjectVtbl* mpVtbl;                                // +0x000
    char           mPad004[0x30];                           // +0x004 .. +0x033
    cHallObject    mObject34;                               // +0x034
    char           mPad038[0xe8];                           // +0x038 .. +0x11f
    cSpatialObject mSpatial120;                             // +0x120
    char           mPad124[0x165];                          // +0x124 .. +0x288
    uint8_t        mbFlag289;                               // +0x289
};

// Turret object.
struct cTurret {
    char           mPad000[0x34];                           // +0x000 .. +0x033
    cHallObject    mObject34;                               // +0x034
    char           mPad038[0x550];                          // +0x038 .. +0x587
    cSpatialObject mSpatial588;                             // +0x588
};

// Object whose position (c4/c8/cc) is turned into an action parameter block.
struct cActionTarget {
    char    mPad000[0xc4];                                  // +0x000 .. +0xc3
    Vector3 mPosition;                                      // +0xc4
};

// Timers.
struct cGonzagoTimer {
    virtual ~cGonzagoTimer();                               // +0x00

    void Reset();                                           // 0x00bc3170
    void Stop();                                            // 0x00bc3110

    uint32_t mRefCount;                                     // +0x04
    uint32_t mElapsedTime[2];                               // +0x08
    uint32_t mField10[2];                                   // +0x10
    uint8_t  mbRunning;                                     // +0x18
    uint32_t mpTimeFunction;                                // +0x1c
};

struct cCulturalTarget {
    void*   mpVtbl;                                         // +0x000
    char    mPad004[0x1d4];                                 // +0x004 .. +0x1d7
    int32_t mState;                                         // +0x1d8
};

struct tCultureTargetInfo {
    int32_t mBucketMaxPopulation[2];                        // +0x00
    int32_t mBucketPopulation[2];                           // +0x08
    int32_t mBucketEmigration[2];                           // +0x10
    int32_t mBucketImmigration[2];                          // +0x18
    bool    mbClearEverything;                              // +0x20
    char    mPad21[3];                                      // +0x21
    float   mAngryCrowdFraction;                            // +0x24
    float   mDancingCrowdFraction;                          // +0x28
    float   mIndifferentCrowdFraction;                      // +0x2c
    cGonzagoTimer mConvertCheckTimer;                       // +0x30
    cGonzagoTimer mConvertedTimer;                          // +0x50
    cSlotObject* mpAttackTarget;                            // +0x70
    bool    mbAttackTargetChanged;                          // +0x74
    char    mPad75[3];                                      // +0x75
    void*   mpCultureObject;                                // +0x78
    char    mPad7c[4];                                      // +0x7c
};

struct cCityPartner {
    void*   mpInterCityRoad;                                // +0x00 (first dword is the empire id)
    void*   mpPartnerCity;                                  // +0x04
    int32_t mField08;                                       // +0x08
};

// Creature-mode helper used when the city has an active creature.
struct cCreatureDisplay {
    virtual void v00();                                     // +0x00
    virtual void v04();                                     // +0x04
    virtual void v08();                                     // +0x08
    virtual void v0c();                                     // +0x0c
    virtual void v10();                                     // +0x10
    virtual void v14();                                     // +0x14
    virtual void v18();                                     // +0x18
    virtual void v1c();                                     // +0x1c
    virtual void v20();                                     // +0x20
    virtual void v24();                                     // +0x24
    virtual void v28();                                     // +0x28
    virtual void v2c();                                     // +0x2c
    virtual void v30();                                     // +0x30
    virtual void v34();                                     // +0x34
    virtual void v38();                                     // +0x38
    virtual void SetCreature(cAnimatingCreature* pCreature);   // +0x3c
};

struct cModeHelper {
    virtual void v00();                                     // +0x00
    virtual void v04();                                     // +0x04
    virtual void v08();                                     // +0x08
    virtual void v0c();                                     // +0x0c
    virtual void v10();                                     // +0x10
    virtual void v14();                                     // +0x14
    virtual void v18();                                     // +0x18
    virtual void v1c();                                     // +0x1c
    virtual void v20();                                     // +0x20
    virtual void v24();                                     // +0x24
    virtual void v28();                                     // +0x28
    virtual void v2c();                                     // +0x2c
    virtual void v30();                                     // +0x30
    virtual void v34();                                     // +0x34
    virtual void v38();                                     // +0x38
    virtual void v3c();                                     // +0x3c
    virtual void v40();                                     // +0x40
    virtual void v44();                                     // +0x44
    virtual void v48();                                     // +0x48
    virtual void v4c();                                     // +0x4c
    virtual void v50();                                     // +0x50
    virtual void v54();                                     // +0x54
    virtual void v58();                                     // +0x58
    virtual void v5c();                                     // +0x5c
    virtual void v60();                                     // +0x60
    virtual void v64();                                     // +0x64
    virtual void v68();                                     // +0x68
    virtual void v6c();                                     // +0x6c
    virtual void v70();                                     // +0x70
    virtual cCreatureDisplay* GetDisplay();                  // +0x74
};

struct cAnimatingCreature {
    void Release();                                         // 0x00a05270
};

// Another simulation section object owned by the city.
struct cSectionObject {
    void OnCityChanged(cCity* pCity, int32_t nValue);       // 0x00ff2810
};

// Active game-mode section (per-mode singleton).
struct cGameModeSection {
    char    mPad000[0x13c];                                 // +0x000 .. +0x13b
    int32_t mField13C;                                      // +0x13c
};

// Creature prototypes that resolve to a noun manager and a category.
struct cProtectorSource {
    cGameNounManager* GetNounManager();                     // 0x00b8de30
    int32_t           GetCategory();                        // 0x00b8dab0
};

// ---------------------------------------------------------------------------
// Simulator::cCity
// ---------------------------------------------------------------------------

struct cCityVtbl {
    void*    mpSlots00[0x16];                               // +0x00 .. +0x57
    void*    (*pGetPlanetPosition)(void* pThis, void* pOut);   // +0x58
    void*    mpSlot5C;                                      // +0x5c
    void*    mpSlots60[3];                                  // +0x60 .. +0x6b
    int32_t  (__fastcall* pGetState)(void* pThis);           // +0x6c
};

struct cCity {
    cCityVtbl*     mpVtbl;                                  // +0x000
    char           mPad004[0x11c];                          // +0x004 .. +0x11f
    cSpatialObject mSpatial;                                // +0x120
    char           mPad124[0xe0];                           // +0x124 .. +0x203
    cCityWalls*    mpLayoutWalls;                           // +0x204
    char           mPad208[0x6c];                           // +0x208 .. +0x273
    uint8_t        mFlagTable[0x28];                        // +0x274 .. +0x29b (overlaps a timer at +0x270)
    int32_t        mContextState;                           // +0x29c
    char           mPad2a0[0x50];                           // +0x2a0 .. +0x2ef
    cSectionObject* mpSection2F0;                           // +0x2f0
    char           mPad2f4[0x2c];                           // +0x2f4 .. +0x31f
    cCityObject*   mpCityHall;                              // +0x320
    cCityWalls*    mpCityWalls;                             // +0x324
    void*          mpCityTerritory;                         // +0x328
    Vector3        mCityPosition;                           // +0x32c
    char           mPad338[8];                              // +0x338 .. +0x33f
    cVec<cCityObject*> mBuildings;                          // +0x340
    cVec<cTurret*> mTurrets;                                // +0x354 (fixed_vector: 32 entries)
    char           mPad368[0x84];                           // +0x368 .. +0x3eb
    cCommunityLayout mBuildingsLayout;                      // +0x3ec
    cCommunityLayout mDecorationsLayout;                    // +0x450
    cCommunityLayout mTurretsLayout;                        // +0x4b4
    bool           mbSmallCity;                             // +0x518
    bool           mbField519;                              // +0x519
    char           mPad51a[2];                              // +0x51a
    Vector3        mPendingPosition;                        // +0x51c
    char           mPad528[0x18];                           // +0x528 .. +0x53f
    int32_t        mVehicleSpecialty;                       // +0x540
    char           mPad544[0x18];                           // +0x544 .. +0x55b
    cVec<cCityPartner> mTradePartners;                      // +0x55c
    char           mPad570[0x20];                           // +0x570 .. +0x58f
    cCivilization* mpCivilization;                          // +0x590
    char           mPad594[0x84];                           // +0x594 .. +0x617
    cVec<tCultureTargetInfo> mCultureTargetInfo;            // +0x618
    cVec<cCulturalTarget*> mCulturalTargets;                // +0x62c
    char           mPad640[0xc];                            // +0x640 .. +0x64b
    int32_t        mRoboPopulation;                         // +0x64c
    char           mPad650[0x114];                          // +0x650 .. +0x763
    cAnimatingCreature* mpCreature;                         // +0x764
    cGameData*     mpObject768;                             // +0x768
    char           mPad76c[4];                              // +0x76c
    cGonzagoTimer  mMessiahTimer;                           // +0x770
    char           mPad790[0x80];                           // +0x790 .. +0x80f
    cGameData*     mpTarget810;                             // +0x810
    char           mPad814[4];                              // +0x814 .. +0x817 (8-byte class alignment tail)

    // --- methods of this slice ---
    void ShowTransitionWarning();                           // 0x00bd91e0
    bool HasTradePartner(uint32_t nEmpireID);               // 0x00bd9260
    cCity* FindNearestCity(int32_t nReason);                // 0x00bd92d0
    void PrintBuildingCount(float fValue);                  // 0x00bd9440
    float GetCityRadius();                                  // 0x00bd9470
    Vector3* GetWallsCenter(Vector3* pOut);                 // 0x00bd9480
    void UpdateTurretLayout(void* pOwner);                  // 0x00bd94a0
    void SetField51C(const cVec<Vector3>* pPositions);      // 0x00bd9620
    bool SetDecoration(cCityObject* pObject);               // 0x00bd9660
    void UpdateCityPosition();                              // 0x00bd9710
    cLayoutSlot* FindFarthestTurretSlot();                  // 0x00bd98c0
    void* GetCivilizationData();                            // 0x00bd99e0
    void DoCityAction(cActionTarget* pTarget);              // 0x00bd9a00
    int32_t GetTurretSlotCount();                           // 0x00bd8b10 (helper used by 00bd98c0)
    int32_t CountEmptyTurrets();                            // 0x00bd9b70
    int32_t CountEmptyBuildings();                          // 0x00bd9bb0
    bool  ContainsPoint(const Vector3* pPoint);             // 0x00bd9c00
    bool  IsWithinRadius(const Vector3& rPoint, float fExtra);   // 0x00bd9c30
    Vector3* GetCenter(Vector3* pOut);                      // 0x00bd9ca0
    void* GetPlayerTerrainSphere();                         // 0x00bd9cf0
    bool  HasOnlyCityHall();                                // 0x00bd9d20
    void  ClearCreature();                                  // 0x00bd9dd0
    void  NotifySectionObject();                            // 0x00bd9e50
    tCultureTargetInfo* GetCultureTarget(int32_t nIndex);   // 0x00bd9e80
    void  SetCultureTargetBuckets(int32_t nIndex, int32_t nFirst, int32_t nSecond);   // 0x00bd9ea0
    void  ResetCultureTarget(int32_t nIndex);               // 0x00bd9ed0
    int32_t IsCultureActive();                              // 0x00bd9fa0
    bool  IsFestivalActive();                               // 0x00bd8f60 (helper used by 00bd9fa0)
    bool  HasCultureEvent(bool bValue);                     // 0x00c004c0 (helper used by 00bd9fa0)
    bool  HasLayoutFlag(int32_t nOffset);                   // 0x00bda000
    bool  CanUseSuperweapon(bool bValue);                   // 0x00bda080
    void  ClearCultureState();                              // 0x00bda0a0
    void  SetTarget810(cGameData* pNew);                    // 0x00bda120

    // --- helpers (no markers) ---
    int32_t GetBuildingCount() const { return (int32_t)(mBuildings.mpEnd - mBuildings.mpBegin); }

    void ReleaseCreature()
    {
        if (!mpCreature)
            return;
        cModeHelper* pSimulator = GetLiveSimulator();
        cCreatureDisplay* pDisplay = pSimulator->GetDisplay();
        pDisplay->SetCreature(mpCreature);
        cAnimatingCreature* pOld = mpCreature;
        mpCreature = 0;
        if (pOld)
            pOld->Release();
    }
};

typedef char cCitySizeCheck[(sizeof(cCity) == 0x818) ? 1 : -1];

// ---------------------------------------------------------------------------
// external engine entry points
// ---------------------------------------------------------------------------

namespace UI {
    void __cdecl CalloutMessageBox(const ResourceKey* pTable, const ResourceKey* pMessage);   // 0x00809db0
}

cGameTimeManager*     __cdecl GameTimeManager();            // 0x00b3d380
cGameNounManager*     __cdecl NounManager();                // 0x00b3d300
cStarManager*         __cdecl StarManager();                // 0x00b3d2a0
cPlanetModel*         __cdecl PlanetModel();                // 0x00b3d350
cTerraformingManager* __cdecl TerraformingManager();        // 0x00b3d430
cVec<cCity*>*         __fastcall GetCityList(int32_t nReason);   // 0x00bef6c0
int32_t               __cdecl GetPlayerEmpireID();          // 0x01021090
cGameModeSection*     __cdecl GetGameModeSection();         // 0x01021260
bool                  __cdecl IsOnTerraformedGround(int32_t nMode, const Vector3* pPosition);   // 0x00c9e8e0
bool                  __cdecl HasTerraformEvent(void* pOwner);   // 0x00c6fe50
void                  __cdecl GetPropertyFloat(void* pObject, uint32_t nProperty, float* pOut); // 0x0040cf10

extern cHtmlReport g_cityHtmlReport;                        // 0x0169c254

extern const float   kFloatMax;                             // 0x0146847c
extern const float   kTenFold;                              // 0x01473c70
extern const float   kEmitScale;                            // 0x01468468
extern const float   kOne;                                  // 0x01485720
extern const float   kSqrtEpsilon;                          // 0x013ec4b8
extern const float   kGrowStep;                             // 0x013eeda0
extern const Vector3 kDefaultCityPosition;                  // 0x0168bd70
extern const char    kDefaultCivilizationData;              // 0x0156e14c

extern const ResourceKey kTransitionWarningTable;           // 0x0156e29c
extern const ResourceKey kTransitionWarningEcoHostile;      // 0x0156e254
extern const ResourceKey kTransitionWarningEco;             // 0x0156e260
extern const ResourceKey kTransitionWarningTrader;          // 0x0156e26c
extern const ResourceKey kTransitionWarningTraderHostile;   // 0x0156e278
extern const ResourceKey kTransitionWarningMilitaryHostile; // 0x0156e284
extern const ResourceKey kTransitionWarningMilitary;        // 0x0156e290

// ---------------------------------------------------------------------------
// functions
// ---------------------------------------------------------------------------

// @ 0x00bd91e0
void cCity::ShowTransitionWarning()
{
    switch (mVehicleSpecialty) {
    case 0:
        if (mContextState == 1)
            UI::CalloutMessageBox(&kTransitionWarningTable, &kTransitionWarningTraderHostile);
        else
            UI::CalloutMessageBox(&kTransitionWarningTable, &kTransitionWarningTrader);
        break;
    case 1:
        if (mContextState == 2)
            UI::CalloutMessageBox(&kTransitionWarningTable, &kTransitionWarningMilitaryHostile);
        else
            UI::CalloutMessageBox(&kTransitionWarningTable, &kTransitionWarningMilitary);
        break;
    case 2:
        if (mContextState == 0)
            UI::CalloutMessageBox(&kTransitionWarningTable, &kTransitionWarningEcoHostile);
        else
            UI::CalloutMessageBox(&kTransitionWarningTable, &kTransitionWarningEco);
        break;
    }
    cGameTimeManager* pTimeManager = GameTimeManager();
    pTimeManager->IncPauseGate(0x4bf38a7);
}

// @ 0x00bd9260
bool cCity::HasTradePartner(uint32_t nEmpireID)
{
    for (uint32_t i = 0; i < mTradePartners.size(); ++i) {
        if ((uint32_t)mTradePartners[i].mpInterCityRoad == nEmpireID)
            return true;
    }
    return false;
}

// @ 0x00bd92d0
cCity* cCity::FindNearestCity(int32_t nReason)
{
    cCity* pBest = 0;
    float fBestDistance = kFloatMax;
    for (int32_t nPass = 0; nPass < 2; ++nPass) {
        cVec<cCity*>* pCities = GetCityList(nReason);
        for (uint32_t i = 0; i < pCities->size(); ++i) {
            cCity* pOther = (*pCities)[i];
            if (pOther == this)
                continue;
            if (pOther->mVehicleSpecialty != 2 && nPass <= 0)
                continue;
            Vector3* pOtherPosition = pOther->mSpatial.GetPosition(0);
            Vector3* pOwnPosition = mSpatial.GetPosition(0);
            float fDeltaY = pOwnPosition->y - pOtherPosition->y;
            float fDeltaZ = pOwnPosition->z - pOtherPosition->z;
            float fDeltaX = pOwnPosition->x - pOtherPosition->x;
            float fDistance = (fDeltaY * fDeltaY + fDeltaZ * fDeltaZ) + fDeltaX * fDeltaX;
            Vector3 ownKey;
            Vector3 otherKey;
            Vector3* pOwnKey = (Vector3*)mSpatial.GetPlanetPosition(&ownKey);
            int32_t nOwnContinent = PlanetModel()->GetContinent(pOwnKey);
            Vector3* pOtherKey = (Vector3*)pOther->mSpatial.GetPlanetPosition(&otherKey);
            int32_t nOtherContinent = PlanetModel()->GetContinent(pOtherKey);
            if (nOwnContinent != nOtherContinent)
                fDistance *= kTenFold;
            if (fDistance < fBestDistance) {
                fBestDistance = fDistance;
                pBest = pOther;
            }
        }
        if (pBest)
            break;
    }
    return pBest;
}

// @ 0x00bd9440
void cCity::PrintBuildingCount(float fValue)
{
    g_cityHtmlReport.AppendNumbers(GetBuildingCount(), mRoboPopulation, fValue);
}

// @ 0x00bd9470
float cCity::GetCityRadius()
{
    return mpLayoutWalls->mRadius;
}

// @ 0x00bd9480
Vector3* cCity::GetWallsCenter(Vector3* pOut)
{
    mpCityWalls->GetCenter(pOut);
    return pOut;
}

// @ 0x00bd94a0
void cCity::UpdateTurretLayout(void* pOwner)
{
    float fRadius = mpCityWalls->mRadius;
    Vector3 facing;
    mSpatial.v5c(&facing, 0.0f);
    Vector3* pCenter = mSpatial.GetPosition(0);
    mTurretsLayout.SetAtCenter(pCenter, fRadius, &facing);
    mTurretsLayout.EmitCopy(pOwner, kEmitScale);
    int32_t nCount = (int32_t)mTurrets.size();
    for (int32_t i = 0; i < nCount; ++i) {
        cTurret* pTurret = mTurrets[i];
        cLayoutSlot* pSlot = mTurretsLayout.FindSlotAt(pTurret->mObject34.GetPosition());
        if (!pSlot)
            continue;
        pSlot->Reserve((cGameData*)pTurret);
        Vector3 slotPosition = pSlot->mPosition;
        pTurret->mObject34.SetPosition(&slotPosition);
        Vector3 planetKey;
        Vector3* pPlanetPosition = (Vector3*)mpVtbl->pGetPlanetPosition(this, &planetKey);
        Vector3 delta;
        delta.x = slotPosition.x - pPlanetPosition->x;
        delta.y = slotPosition.y - pPlanetPosition->y;
        delta.z = slotPosition.z - pPlanetPosition->z;
        Quaternion orientation;
        PlanetModel()->BuildSurfaceOrientation2(&orientation, &delta, &slotPosition);
        pTurret->mObject34.SetOrientation(&orientation);
    }
}

// @ 0x00bd9620
void cCity::SetField51C(const cVec<Vector3>* pPositions)
{
    if ((int32_t)pPositions->size() > 0)
        mPendingPosition = (*pPositions)[0];
}

// @ 0x00bd9660
bool cCity::SetDecoration(cCityObject* pObject)
{
    cLayoutSlot* pSlot = mDecorationsLayout.FindSlotAt(pObject->mSpatial120.GetPosition(0));
    if (pSlot) {
        pSlot->Reserve((cGameData*)pObject);
        pObject->mSpatial120.SetPosition(&pSlot->mPosition);
        Quaternion orientation;
        PlanetModel()->BuildSurfaceOrientation(&orientation, &pSlot->mPosition);
        pObject->mSpatial120.SetOrientation(&orientation);
        return true;
    }
    pObject->mSpatial120.SetPosition(mpCityHall->mObject34.GetPosition());
    pObject->mSpatial120.SetOrientation(mpCityHall->mObject34.GetOrientation());
    return false;
}

// @ 0x00bd9710
void cCity::UpdateCityPosition()
{
    if (mpCityWalls->GetState() != 2 && mpCityWalls->GetState() != 3) {
        mCityPosition = kDefaultCityPosition;
        return;
    }
    Vector3 request;
    Vector3* pRequested = mpCityWalls->RequestPosition(&request, 3);
    mCityPosition = *pRequested;
    Vector3 wallsCenter;
    mpCityWalls->GetCenter(&wallsCenter);
    float fDeltaX = mCityPosition.x - wallsCenter.x;
    float fDeltaY = mCityPosition.y - wallsCenter.y;
    float fDeltaZ = mCityPosition.z - wallsCenter.z;
    float fScale = 1.0f / sqrtf(fDeltaZ * fDeltaZ + fDeltaY * fDeltaY + fDeltaX * fDeltaX + kSqrtEpsilon);
    Vector3 step;
    step.x = fDeltaX * fScale * kGrowStep;
    step.y = fDeltaY * fScale * kGrowStep;
    step.z = fDeltaZ * fScale * kGrowStep;
    mCityPosition.x += step.x;
    mCityPosition.y += step.y;
    mCityPosition.z += step.z;
    int32_t nTries = 0;
    while (!IsOnTerraformedGround(1, &mCityPosition)) {
        mCityPosition.x += step.x;
        mCityPosition.y += step.y;
        mCityPosition.z += step.z;
        if (++nTries >= 8)
            break;
    }
    Vector3 surface;
    Vector3* pSurface = PlanetModel()->GetSurfacePosition(&surface, &mCityPosition);
    mCityPosition = *pSurface;
}

// @ 0x00bd98c0
cLayoutSlot* cCity::FindFarthestTurretSlot()
{
    int32_t nLimit = GetTurretSlotCount();
    int32_t nSlotCount = (int32_t)mTurretsLayout.mSlots.size();
    if (nLimit > nSlotCount)
        nLimit = nSlotCount;
    if (nLimit > 8)
        nLimit = 8;
    cLayoutSlot* pBest = 0;
    float fBestScore = 0.0f;
    for (int32_t i = 0; i < nLimit; ++i) {
        cLayoutSlot* pSlot = mTurretsLayout.SlotAt(i);
        if (!pSlot)
            continue;
        if (pSlot->GetObject())
            continue;
        float fScore = kOne;
        for (int32_t j = 0; j < nLimit; ++j) {
            if (i == j)
                continue;
            cLayoutSlot* pOther = mTurretsLayout.SlotAt(j);
            if (!pOther)
                continue;
            if (!pOther->GetObject())
                continue;
            float fDeltaX = pSlot->mPosition.x - pOther->mPosition.x;
            float fDeltaY = pSlot->mPosition.y - pOther->mPosition.y;
            float fDeltaZ = pSlot->mPosition.z - pOther->mPosition.z;
            fScore += sqrtf(fDeltaZ * fDeltaZ + fDeltaY * fDeltaY + fDeltaX * fDeltaX);
        }
        if (fScore > fBestScore) {
            fBestScore = fScore;
            pBest = pSlot;
        }
    }
    return pBest;
}

// @ 0x00bd99e0
void* cCity::GetCivilizationData()
{
    if (mpCivilization)
        return &mpCivilization->mDataC4;
    return (void*)&kDefaultCivilizationData;
}

// @ 0x00bd9a00
void cCity::DoCityAction(cActionTarget* pTarget)
{
    Vector4 params;
    params.x = pTarget->mPosition.x;
    params.y = pTarget->mPosition.y;
    params.z = pTarget->mPosition.z;
    params.w = kOne;
    cCivModeStrategy::Get()->DoCityAction(pTarget, this, 0x459570dd, 0xaa9a8ed7,
                                          mSpatial.GetPosition(&params), &params, 0, 0);
}

// @ 0x00bd9a80
float __cdecl GetForeignCityMood(void* pObject)
{
    cProtectorSource* pSource = (cProtectorSource*)pObject;
    float fValue;
    cGameNounManager* pNouns = pSource->GetNounManager();
    fValue = 0.0f;
    if (pSource->GetCategory() == 5) {
        if (pNouns->GetAvatar() != GetPlayerEmpireID()) {
            cStarEmpire* pEmpire = StarManager()->GetEmpireByID((int32_t)pNouns->GetAvatar());
            cGameData* pEmpireData = StarManager()->GetEmpireData(pEmpire);
            if (HasTerraformEvent(pObject) || TerraformingManager()->HasEvent(pObject))
                GetPropertyFloat(pEmpireData, 0x68086e9, &fValue);
            else
                GetPropertyFloat(pEmpireData, 0x68086f3, &fValue);
        }
    }
    return fValue;
}

// @ 0x00bd9b70
int32_t cCity::CountEmptyTurrets()
{
    int32_t nCount = 0;
    cTurret** pIter = mTurrets.mpBegin;
    cTurret** pEnd = mTurrets.mpEnd;
    if (pIter != pEnd) {
        do {
            cTurret* pTurret = (*pIter);
            if (pTurret->mSpatial588.GetObjectCount() == 0)
                nCount = nCount + 1;
            ++pIter;
        } while (pIter != pEnd);
    }
    return nCount;
}

// @ 0x00bd9bb0
int32_t cCity::CountEmptyBuildings()
{
    int32_t nCount = 0;
    cCityObject** pIter = mBuildings.mpBegin;
    cCityObject** pEnd = mBuildings.mpEnd;
    if (pIter != pEnd) {
        do {
            cCityObject* pBuilding = (*pIter);
            if (pBuilding->mSpatial120.GetObjectCount() == 0)
                nCount = nCount + 1;
            ++pIter;
        } while (pIter != pEnd);
    }
    return nCount;
}

// @ 0x00bd9c00
bool cCity::ContainsPoint(const Vector3* pPoint)
{
    if (mpCityWalls) {
        if (mpCityWalls->ContainsPoint(pPoint))
            return true;
    }
    return false;
}

// @ 0x00bd9c30
bool cCity::IsWithinRadius(const Vector3& rPoint, float fExtra)
{
    if (mpCityWalls) {
        Vector3 center;
        mpCityWalls->GetCenter(&center);
        float fDeltaX = rPoint.x - center.x;
        float fDeltaY = rPoint.y - center.y;
        float fDeltaZ = rPoint.z - center.z;
        float fDistance = (float)sqrt(fDeltaZ * fDeltaZ + fDeltaY * fDeltaY + fDeltaX * fDeltaX);
        if (fDistance < mpCityWalls->mRadius + fExtra)
            return true;
    }
    return false;
}

// @ 0x00bd9ca0
Vector3* cCity::GetCenter(Vector3* pOut)
{
    cCityObject* pHall = mpCityHall;
    if (pHall) {
        Vector3* pPosition = pHall->mpVtbl->pGetPosition(pHall);
        pOut->x = pPosition->x;
        pOut->y = pPosition->y;
        pOut->z = pPosition->z;
        return pOut;
    }
    mpCityWalls->GetCenter(pOut);
    return pOut;
}

// @ 0x00bd9cf0
void* cCity::GetPlayerTerrainSphere()
{
    cCivilization* pCivilization = mpCivilization;
    if (pCivilization == NounManager()->GetPlayerCivilization())
        return NounManager()->GetCurrentTerrainSphere();
    return 0;
}

// @ 0x00bd9d20
bool cCity::HasOnlyCityHall()
{
    cCityObject** pBuilding = mBuildings.mpBegin;
    cCityObject** pEnd = mBuildings.mpEnd;
    while (true) {
        if (pBuilding == pEnd)
            return true;
        int32_t nObjectCount = (*pBuilding)->mSpatial120.GetObjectCount();
        if (nObjectCount != 2 && *pBuilding != mpCityHall)
            break;
        ++pBuilding;
    }
    return false;
}

// @ 0x00bd9d70
void* __cdecl CreateCityObject(void* pPosition, void* pParams)
{
    cGameNounManager* pNouns = NounManager();
    cGameData* pNoun = pNouns->CreateNoun(0x18c43e8);
    cCityObject* pCity = pNoun ? (cCityObject*)pNoun->Cast(0xee9b2232) : 0;
    if (pParams)
        pCity->mObject34.v00(pParams);
    pCity->mSpatial120.SetPosition((const Vector3*)pPosition);
    return pCity;
}

// @ 0x00bd9dd0
void cCity::ClearCreature()
{
    ReleaseCreature();
}

// @ 0x00bd9e50
void cCity::NotifySectionObject()
{
    if (!mpSection2F0)
        return;
    cGameModeSection* pSection = GetGameModeSection();
    mpSection2F0->OnCityChanged(this, pSection->mField13C);
}

// @ 0x00bd9e80
tCultureTargetInfo* cCity::GetCultureTarget(int32_t nIndex)
{
    if (nIndex < 0 || nIndex > 3)
        nIndex = 0;
    return &mCultureTargetInfo[nIndex];
}

// @ 0x00bd9ea0
void cCity::SetCultureTargetBuckets(int32_t nIndex, int32_t nFirst, int32_t nSecond)
{
    if ((uint32_t)nIndex > 3)
        return;
    mCultureTargetInfo[nIndex].mBucketMaxPopulation[0] = nFirst;
    mCultureTargetInfo[nIndex].mBucketMaxPopulation[1] = nSecond;
}

// @ 0x00bd9ed0
void cCity::ResetCultureTarget(int32_t nIndex)
{
    mCultureTargetInfo[nIndex].mBucketPopulation[0] = 0;
    mCultureTargetInfo[nIndex].mBucketEmigration[0] = 0;
    mCultureTargetInfo[nIndex].mBucketImmigration[0] = 0;
    mCultureTargetInfo[nIndex].mBucketPopulation[1] = 0;
    mCultureTargetInfo[nIndex].mBucketEmigration[1] = 0;
    mCultureTargetInfo[nIndex].mBucketImmigration[1] = 0;
    mCultureTargetInfo[nIndex].mbAttackTargetChanged = false;
    mCultureTargetInfo[nIndex].mAngryCrowdFraction = 0.0f;
    mCultureTargetInfo[nIndex].mDancingCrowdFraction = 0.0f;
    mCultureTargetInfo[nIndex].mIndifferentCrowdFraction = 0.0f;
    mCultureTargetInfo[nIndex].mConvertCheckTimer.Reset();
    mCultureTargetInfo[nIndex].mConvertedTimer.Reset();
    cSlotObject* pOld = mCultureTargetInfo[nIndex].mpAttackTarget;
    mCultureTargetInfo[nIndex].mpAttackTarget = 0;
    if (pOld)
        pOld->mpVtbl->pRelease(pOld);
}

// @ 0x00bd9fa0
int32_t cCity::IsCultureActive()
{
    bool bConverted = false;
    cCulturalTarget** pIter = mCulturalTargets.mpBegin;
    cCulturalTarget** pEnd = mCulturalTargets.mpEnd;
    if (pIter != pEnd) {
        do {
            if (bConverted)
                return 1;
            bConverted = (*pIter)->mState == 2;
            ++pIter;
        } while (pIter != pEnd);
        if (bConverted)
            return 1;
    }
    if (!IsFestivalActive() && !HasCultureEvent(false))
        return 0;
    return 1;
}

// @ 0x00bda000
bool cCity::HasLayoutFlag(int32_t nOffset)
{
    for (uint32_t i = 0; i < 14; ++i) {
        cLayoutSlot* pSlot = mBuildingsLayout.SlotAt(i);
        if (!pSlot)
            continue;
        cGameData* pObject = pSlot->GetObject();
        if (!pObject)
            continue;
        cCityObject* pBuilding = (cCityObject*)pObject->Cast(0xe9cb8ba);
        if (!pBuilding)
            continue;
        if (!pBuilding->mbFlag289)
            continue;
        int32_t nState = mpVtbl->pGetState(this);
        if (mFlagTable[nState + i * 14 + nOffset])
            return true;
    }
    return false;
}

// @ 0x00bda080
bool cCity::CanUseSuperweapon(bool bValue)
{
    return mpCivilization->CanUseSuperweapon(bValue);
}

// @ 0x00bda0a0
void cCity::ClearCultureState()
{
    ReleaseCreature();
    if (mpObject768) {
        mpObject768->Cast(0);
        cGameData* pReleased = mpObject768;
        mpObject768 = 0;
        if (pReleased)
            pReleased->Release();
    }
    mMessiahTimer.Stop();
}

// @ 0x00bda120
void cCity::SetTarget810(cGameData* pNew)
{
    if (mpTarget810) {
        mpTarget810->Cast(0);
        cGameData* pReleased = mpTarget810;
        mpTarget810 = 0;
        if (pReleased)
            pReleased->Release();
    }
    cGameData* pOld = mpTarget810;
    if (pNew != pOld) {
        if (pNew)
            pNew->AddRef();
        mpTarget810 = pNew;
        if (pOld)
            pOld->Release();
    }
}
