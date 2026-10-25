// SporeApp.exe slice s00bda190 (gold7, worker).
//
// A contiguous run that mixes three things:
//   * Simulator::cCulturalTarget methods  (ctor lives in 00bdab60, dtor 00bdace0)
//   * Simulator::cCity methods            (building list, trade partners, culture points)
//   * the eastl vector helper instantiations that sit between them
//
// Field offsets are taken from the retail disassembly.  Where the 2008 PDB and the
// community ModAPI headers agree on cCulturalTarget (mGateIndex +0x1d4, mAttackState
// +0x1d8, mAttackerPoliticalID +0x1dc, mAttackOrders +0x1e0, mAttackers +0x1f4,
// mpHitSphere +0x208, crowd fractions +0x20c/+0x210, anger level +0x214) the real names
// are used verbatim; the retail object is 0x218 bytes.

#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// math / container types
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

// An eastl vector redressed to the pointer triple the engine walks.
struct cPtrVec {
    void*    mpBegin;                                       // +0x00
    void*    mpEnd;                                         // +0x04
    void*    mpCapacity;                                    // +0x08
};

template <class T>
struct cVec {
    T*       mpBegin;                                       // +0x00
    T*       mpEnd;                                         // +0x04
    T*       mpCapacity;                                    // +0x08

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T&       operator[](uint32_t nIndex) const { return mpBegin[nIndex]; }
};

// ---------------------------------------------------------------------------
// game object base types
// ---------------------------------------------------------------------------

struct cCulturalTarget;
struct cHallTarget;

struct cGameData {
    virtual void       AddRef();                            // +0x00
    virtual void       Release();                           // +0x04
    virtual void       v08();                               // +0x08
    virtual cGameData* Cast(uint32_t nType);                // +0x0c
    virtual void       v10();                               // +0x10
    virtual void       v14();                               // +0x14
    virtual void       v18();                               // +0x18
    virtual void       v1c();                               // +0x1c
    virtual int32_t    GetDefinitionID();                   // +0x20
    virtual void       v24();                               // +0x24
    virtual void       v28();                               // +0x28
    virtual void       v2c();                               // +0x2c
    virtual void       v30();                               // +0x30
    virtual void       v34();                               // +0x34
    virtual void       v38();                               // +0x38
    virtual void       v3c();                               // +0x3c
    virtual void       v40();                               // +0x40
    virtual void       v44();                               // +0x44
    virtual void       v48();                               // +0x48
    virtual int32_t    GetPoliticalID();                    // +0x4c
    virtual void       v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void       v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void       v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void       v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void       v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void       va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void       vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void       ReleaseGameData();                   // +0xc0
};

// Vtable slots of a game object as reached through cCity's building list.
struct cObjectVtbl {
    void*    mpSlots00[0x8];                                // +0x00 .. +0x1f
    int32_t  (__thiscall* pGetDefinitionID)(void* pThis);   // +0x20
    void*    mpSlots24[0xa];                                // +0x24 .. +0x4b
    int32_t  (__thiscall* pGetPoliticalID)(void* pThis);    // +0x4c
};

// World transform holder embedded at +0x120 of every world object.  The only slots the
// slice touches are GetPosition (+0x2c), SetPosition (+0x38), SetOrientation (+0x3c),
// GetPlanetPosition (+0x58) and one more at +0x5c.
struct cSpatialVtbl {
    void*    mpSlots00[0xb];                                // +0x00 .. +0x2b
    Vector3* (*pGetPosition)(void* pThis, const Vector4* pParams);   // +0x2c
    void*    mpSlots30[2];                                  // +0x30 .. +0x37
    void     (*pSetPosition)(void* pThis, const Vector3* pValue);     // +0x38
    void     (*pSetOrientation)(void* pThis, const Quaternion* pValue);  // +0x3c
    void*    mpSlots40[6];                                  // +0x40 .. +0x57
    void*    (*pGetPlanetPosition)(void* pThis, void* pOut);   // +0x58
    void*    mpSlots5C[1];                                  // +0x5c
};

struct cSpatialObject {
    cSpatialVtbl* mVtbl;                                    // +0x00

    int32_t  GetObjectCount();                              // 0x008e7f80
    Vector3* GetPosition(const Vector4* pParams) { return mVtbl->pGetPosition(this, pParams); }
    void     SetPosition(const Vector3* pValue) { mVtbl->pSetPosition(this, pValue); }
    void     SetOrientation(const Quaternion* pValue) { mVtbl->pSetOrientation(this, pValue); }
    void*    GetPlanetPosition(void* pOut) { return mVtbl->pGetPlanetPosition(this, pOut); }
};

struct cSpatialObjectBase {
    cSpatialObject mSpatial;                                // +0x100 in cCulturalTarget
};

// A world object as reached through cCity's mBuildings list.
struct cWorldObject {
    cObjectVtbl*   mpVtbl;                                  // +0x000
    char           mPad004[0x11c];                          // +0x004 .. +0x11f
    cSpatialObject mSpatial120;                             // +0x120
};

// ---------------------------------------------------------------------------
// planet lookup (00bda200 / 00bda2f0)
// ---------------------------------------------------------------------------

struct cTerrainSphere {
    char  mPad000[0x25c];                                   // +0x000 .. +0x25b
    float mRadius;                                          // +0x25c
};

struct cPlanetObjectVtbl {
    void*    mpSlots00[0xb];                                // +0x00 .. +0x2b
    Vector3* (*pGetPosition)(void* pThis);                  // +0x2c
    void*    mpSlots30[0xa];                                // +0x30 .. +0x57
    bool     (*pIsOccupied)(void* pThis);                   // +0x58
    void*    mpSlots5C[4];                                  // +0x5c .. +0x6b
    void*    (*pGetTerrainSphere)(void* pThis);             // +0x6c
};

struct cPlanetObject {
    cPlanetObjectVtbl* mpVtbl;                              // +0x00
};

struct cPlanetModel {
    cPlanetObject* FindObjectAt(const Vector3* pPosition);  // 0x00b894a0
};

cPlanetModel* __cdecl PlanetModel();                        // 0x00b3d350

// ---------------------------------------------------------------------------
// property system (00bda3b0)
// ---------------------------------------------------------------------------

struct Variant {
    uint32_t mData[4];                                      // +0x00
    uint16_t mFlags;                                        // +0x10
    uint16_t mType;                                         // +0x12
    uint16_t m14;                                           // +0x14
    uint16_t m16;                                           // +0x16
};

struct cPropertyList {
    virtual int  AddRef();                                  // +0x00
    virtual int  Release();                                 // +0x04
    char    mPad008[0x1c];                                  // +0x08 .. +0x23
    virtual bool GetPropertyAsVariant(uint32_t nProperty, Variant* pOut);   // +0x24
};

struct cIPropertyManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyListRaw(uint32_t nInstanceID, uint32_t nGroupID, cPropertyList** ppList);   // +0x2c
};

cIPropertyManager* __cdecl PropertyManager();               // 0x0067de30

extern uint32_t g_kDefaultPropertyVariant;                  // 0x015d9c68

// ---------------------------------------------------------------------------
// IO stream (write side) used by the vector serializers
// ---------------------------------------------------------------------------

struct cBinaryWriter {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void* GetRaw();                                 // +0x18
};

struct cObjectStream {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void Close();                                   // +0x1c
    virtual cBinaryWriter* GetWriter();                     // +0x20
    virtual void v24(); virtual void v28();
    virtual void WriteInt(uint32_t nValue);                 // +0x2c
    virtual void v30();
    virtual void WriteBytes(const void* pData, uint32_t nCount);   // +0x34

    void SerializeText(void* pObject, uint32_t nGroup, const wchar_t* pName);   // 0x00695b40
};

struct cVarListSerializer {
    cVarListSerializer(void* pObject, uint32_t nGroup, uint32_t nKind);   // 0x00692f90
    int  Serialize(void* pObject);                          // 0x00692900
};

// ---------------------------------------------------------------------------
// Simulator::cCulturalTarget
// ---------------------------------------------------------------------------

class cCombatant {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
};

// 12-byte reference-counted triple held by mAttackOrders (int) and the partner vectors.
// Its members are AutoRefCount-style wrappers: AddRef at vtbl+0x0, Release at vtbl+0x4.
struct cAutoRefData {
    virtual void AddRef();                                  // +0x00
    virtual void Release();                                 // +0x04
};

struct cAutoRef12 {
    cAutoRefData* mpFirst;                                  // +0x00
    cAutoRefData* mpSecond;                                 // +0x04
    uint32_t      mField08;                                 // +0x08
};

// Host for the two register-argument helpers (this == the destination block).
struct cRefOps {
    cRefOps*    AssignRefPairObj(const cAutoRef12* pSrc);   // 0x00bda760
    void        CopyTransform50Obj(const void* pSrc);       // 0x00bda7d0
    void        DestroyGonzagoTimerObj();                   // 0x00b638b0 (~SP::cGonzagoTimer)
};

// Calls the timer destructor on the object at pTimer with `this` in ecx.
inline void DestroyGonzagoTimer(void* pTimer)
{
    ((cRefOps*)pTimer)->DestroyGonzagoTimerObj();
}

struct cCulturalTarget {
    cGameData      mGameData;                               // +0x000
    char           mPad004[0x34];                           // +0x004 .. +0x037
    cCombatant     mCombatant;                              // +0x038
    char           mPad03c[0xc4];                           // +0x03c .. +0x0ff
    char           mPad100[0xd4];                           // +0x100 .. +0x1d3
    int8_t         mGateIndex;                              // +0x1d4
    char           mPad1d5[3];                              // +0x1d5
    int32_t        mAttackState;                            // +0x1d8
    uint32_t       mAttackerPoliticalID;                    // +0x1dc
    cPtrVec        mAttackOrders;                           // +0x1e0 .. +0x1eb (vector<int>)
    char           mPad1ec[8];                              // +0x1ec .. +0x1f3
    cPtrVec        mAttackers;                              // +0x1f4 .. +0x1ff (vector<AutoRefCount>)
    char           mPad200[8];                              // +0x200 .. +0x207
    cGameData*     mpHitSphere;                             // +0x208
    float          mLastDancingCrowdFraction;               // +0x20c
    float          mLastAngryCrowdFraction;                 // +0x210
    int32_t        mAngerLevel;                             // +0x214

    cSpatialObject* GetSpatial() { return (cSpatialObject*)((char*)this + 0x100); }

    ~cCulturalTarget();                                     // 0x00bdace0
    bool RemoveAttacker(cGameData* pTarget);                // 0x00bdad60
};

typedef char cCulturalTargetSizeCheck[(sizeof(cCulturalTarget) == 0x218) ? 1 : -1];

// ---------------------------------------------------------------------------
// Simulator::cCity
// ---------------------------------------------------------------------------

struct cCityCivVtbl {
    void*    mpSlots00[0x13];                               // +0x00 .. +0x4b
    int32_t  (__thiscall* pGetPoliticalID)(void* pThis);    // +0x4c
};

struct cCityCiv {
    cCityCivVtbl* mpVtbl;                                   // +0x00

    int32_t GetPoliticalID() { return mpVtbl->pGetPoliticalID(this); }
};

// City reached through cCity's trade-partner list (civilization at +0x590).
struct cTradePartnerCity {
    char           mPad000[0x120];                          // +0x000 .. +0x11f
    cSpatialObject mSpatial;                                // +0x120
    char           mPad124[0x46c];                          // +0x124 .. +0x58f
    cCityCiv*      mpCivilization;                          // +0x590
};

struct cCulturalTargetArray {
    cCulturalTarget* mpTargets[4];                          // the four culture buckets
};

struct cCity {
    char           mPad000[0x120];                          // +0x000 .. +0x11f
    cSpatialObject mSpatial120;                             // +0x120
    char           mPad124[0x21c];                          // +0x124 .. +0x33f
    cPtrVec        mBuildings;                              // +0x340 .. +0x34b
    char           mPad34c[0x210];                          // +0x34c .. +0x55b
    cPtrVec        mTradePartners;                          // +0x55c .. +0x567
    char           mPad568[0xb0];                           // +0x568 .. +0x617
    cPtrVec        mCultureTargetInfo;                      // +0x618 .. +0x623
    char           mPad624[8];                              // +0x624 .. +0x62b
    cCulturalTarget* mCulturalTargets[4];                   // +0x62c .. +0x63b

    int32_t CountBuildings(int32_t nDefinitionID, int32_t nPoliticalID);   // 0x00bda190
    bool    HasTradePartnerCiv(int32_t nNounID);            // 0x00bdb200
    cCity*  FindTradePartnerCity(int32_t nNounID);          // 0x00bdb280
};

// ---------------------------------------------------------------------------
// the city hall / aggregation helper (00bdaea0 / 00bdaf50 / 00bdb0b0)
// ---------------------------------------------------------------------------

struct cHallTransform {
    virtual void      v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void      v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void      v20(); virtual void v24(); virtual void v28();
    virtual Vector3*  GetPosition();                        // +0x2c
    virtual void      v30(); virtual void v34(); virtual void v38();
    virtual void      v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void      v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void*     MakeTransform(void* pOut);            // +0x5c
    virtual void      v60(); virtual void v64();
    virtual cHallTarget* GetTarget();                       // +0x68
    virtual void      v6c();
    virtual float     GetRadius();                          // +0x70
};

// The object at cCityHall+0x344 (aggregation helper) that owns the radius at +0x238.
struct cHallTarget {
    char  mPad000[0x14];                                    // +0x000 .. +0x013
    float mScale;                                           // +0x014
    char  mPad018[0x220];                                   // +0x018 .. +0x237
    float mRadius;                                          // +0x238
};

struct cCityHall {
    char           mPad000[0x34];                           // +0x000 .. +0x033
    cHallTransform mTransform34;                            // +0x034
    char           mPad0b4[0x290];                          // +0x0b4 .. +0x343
    cHallTarget*   mpTarget344;                             // +0x344

    cHallTarget* GetHallTarget();                           // 0x00bebdb0
};

// City walls: footprint radius at +0x25c.
struct cCityWalls {
    char  mPad000[0x25c];                                   // +0x000 .. +0x25b
    float mRadius;                                          // +0x25c
};

// The object that owns mpCityHall / mpCityWalls (the culture-target host).  It is a
// cCity-like world object: its own spatial transform sits at +0x120.
struct cSimObject {
    char           mPad000[0x120];                          // +0x000 .. +0x11f
    cSpatialObject mSpatial120;                             // +0x120
    char           mPad124[0x178];                          // +0x124 .. +0x29b
    int32_t        mContextState;                           // +0x29c
    char           mPad2a0[0x46];                           // +0x2a0 .. +0x2e5
    uint8_t        mbField2E6;                              // +0x2e6
    char           mPad2e7[0x39];                           // +0x2e7 .. +0x31f
    cCityHall*     mpCityHall;                              // +0x320
    cCityWalls*    mpCityWalls;                             // +0x324
    char           mPad328[0x304];                          // +0x328 .. +0x62b
    cCulturalTarget* mCulturalTargets[4];                   // +0x62c .. +0x63b

    void UpdateAggregationRadius();                         // 0x00bdaea0
    void FillCulturalTargetPoints();                        // 0x00bdaf50
    void EmitCulturalEffect();                              // 0x00bdb0b0
};

// ---------------------------------------------------------------------------
// effects dispatcher (00bdb0b0)
// ---------------------------------------------------------------------------

struct cDispatcherVtbl {
    void*    mpSlots00[0x18];                               // +0x00 .. +0x5f
    void     (*pFire)(void* pThis, uint32_t nEffectID, const Vector3* pPosition, void* pTransform);   // +0x60
};

struct cDispatcher {
    cDispatcherVtbl* mpVtbl;                                // +0x00
};

cDispatcher* __cdecl GetDispatcher();                       // 0x00b3d240

// ---------------------------------------------------------------------------
// culture-target info (0x80 bytes) and its timers
// ---------------------------------------------------------------------------

struct cGonzagoTimer {
    virtual ~cGonzagoTimer();                               // +0x00
};

struct tCultureTargetInfo {
    int32_t mBucketMaxPopulation[2];                        // +0x00
    int32_t mBucketPopulation[2];                           // +0x08
    int32_t mBucketEmigration[2];                           // +0x10
    int32_t mBucketImmigration[2];                          // +0x18
    uint8_t mbClearEverything;                              // +0x20
    char    mPad21[3];                                      // +0x21
    float   mAngryCrowdFraction;                            // +0x24
    float   mDancingCrowdFraction;                          // +0x28
    float   mIndifferentCrowdFraction;                      // +0x2c
    char    mConvertCheckTimer[0x20];                       // +0x30 .. +0x4f
    char    mConvertedTimer[0x20];                          // +0x50 .. +0x6f
    cGameData*    mpAttackTarget;                           // +0x70
    uint8_t mbAttackTargetChanged;                          // +0x74
    char    mPad75[3];                                      // +0x75
    cGameData* mpCultureObject;                             // +0x78
    char    mPad7c[4];                                      // +0x7c
};

typedef char tCultureTargetInfoSizeCheck[(sizeof(tCultureTargetInfo) == 0x80) ? 1 : -1];

// ---------------------------------------------------------------------------
// external engine entry points
// ---------------------------------------------------------------------------

void  __cdecl operator_delete(void* p);                     // 0x00f47380
void* __cdecl GetCurrentGameMode();                         // 0x00b5b800
void  __cdecl FillPoints(void* pOut);                       // 0x00bed3c0
void* __cdecl BuildSurfaceOrientation2(void* pOut, const Vector3* pDirection, const Vector3* pPosition);  // 0x00b7f250
void  __cdecl DestroySpatialObject(void* pObject);          // 0x00c8a420 (~cSpatialObject)
void  __cdecl DestroyCombatant(void* pObject);              // 0x00bfcd00 (~cCombatant)
void  __cdecl DestroyGameData(void* pObject);               // 0x00b184c0 (~cGameData)
void  __cdecl DestroyAutoRefVector(void* pVector);          // 0x00ae6970 (~eastl::vector<AutoRefCount>)

void __cdecl EA_IO_WriteUint32(void* pWriter, const void* pValue, int nCount, int nZero);   // 0x0093aa70

// ---------------------------------------------------------------------------
// constants
// ---------------------------------------------------------------------------

const float    kSqrtEpsilon       = 1.0e-8f;                // 0x013ec4b8 (0x322bcc77)
const float    kCultureScaleSpace = 1.3f;                   // 0x013ef578 (0x3fa66666)
const float    kCultureScalePlanet = 0.8f;                  // 0x01486374 (0x3f4ccccd)
const float    kFloatMax          = 3.402823466e38f;        // 0x0146847c (0x7f7fffff)

const uint32_t kSpaceGameModeID   = 0x01654c05;
const uint32_t kCulturalEffect0   = 0x04aef54c;
const uint32_t kCulturalEffect1   = 0x05f2281e;
const uint32_t kCulturalEffect2   = 0x05f22835;
const uint32_t kSerializerGroup   = 0x0156e448;
const uint32_t kCultureTargetInfoNote = 0x01a80d26;
const uint32_t kCultureTargetCastType = 0x0137e8e0;
const wchar_t  kCultureTargetInfoName[] = L"tCultureTargetInfo";   // 0x014684a4

// ===========================================================================
// functions
// ===========================================================================

// @ 0x00bda190
int32_t cCity::CountBuildings(int32_t nDefinitionID, int32_t nPoliticalID)
{
    cWorldObject** pEnd = (cWorldObject**)mBuildings.mpEnd;
    cWorldObject** pIter = (cWorldObject**)mBuildings.mpBegin;
    int32_t nCount = 0;
    for (; pIter != pEnd; ++pIter) {
        cWorldObject* pObject = *pIter;
        if (pObject->mpVtbl->pGetDefinitionID(pObject) == nDefinitionID
            && pObject->mSpatial120.GetObjectCount() == 0
            && (nPoliticalID == -1 || pObject->mpVtbl->pGetPoliticalID(pObject) == nPoliticalID))
            ++nCount;
    }
    return nCount;
}

// @ 0x00bda200
Vector3* GetCulturalTargetPosition(Vector3* pOut, int32_t nKind, const Vector3* pPosition)
{
    if (nKind == 7 || nKind == 4 || nKind == 11) {
        cPlanetObject* pObject = PlanetModel()->FindObjectAt(pPosition);
        if (pObject) {
            Vector3* pObjectPosition = pObject->mpVtbl->pGetPosition(pObject);
            float fDeltaX = pPosition->x - pObjectPosition->x;
            float fDeltaY = pPosition->y - pObjectPosition->y;
            float fDeltaZ = pPosition->z - pObjectPosition->z;
            cTerrainSphere* pSphere = (cTerrainSphere*)pObject->mpVtbl->pGetTerrainSphere(pObject);
            float fDistance = sqrtf((fDeltaY * fDeltaY + fDeltaZ * fDeltaZ) + fDeltaX * fDeltaX);
            if (fDistance < pSphere->mRadius && !pObject->mpVtbl->pIsOccupied(pObject)) {
                Vector3* pFinal = pObject->mpVtbl->pGetPosition(pObject);
                pOut->x = pFinal->x;
                pOut->y = pFinal->y;
                pOut->z = pFinal->z;
                return pOut;
            }
        }
    }
    pOut->x = pPosition->x;
    pOut->y = pPosition->y;
    pOut->z = pPosition->z;
    return pOut;
}

// @ 0x00bda2f0
bool IsOnCulturalTarget(int32_t nKind, const Vector3* pPosition)
{
    if (nKind != 7 && nKind != 4 && nKind != 11)
        return true;
    cPlanetObject* pObject = PlanetModel()->FindObjectAt(pPosition);
    if (pObject) {
        Vector3* pObjectPosition = pObject->mpVtbl->pGetPosition(pObject);
        float fDeltaX = pPosition->x - pObjectPosition->x;
        float fDeltaY = pPosition->y - pObjectPosition->y;
        float fDeltaZ = pPosition->z - pObjectPosition->z;
        cTerrainSphere* pSphere = (cTerrainSphere*)pObject->mpVtbl->pGetTerrainSphere(pObject);
        float fDistance = sqrtf((fDeltaY * fDeltaY + fDeltaZ * fDeltaZ) + fDeltaX * fDeltaX);
        if (fDistance < pSphere->mRadius && !pObject->mpVtbl->pIsOccupied(pObject))
            return true;
    }
    return false;
}

// @ 0x00bda3b0
int32_t GetPropertyInt(uint32_t nInstanceID, uint32_t nGroupID, uint32_t nPropertyID, int32_t nDefault)
{
    cIPropertyManager* pManager = PropertyManager();
    cPropertyList* pList = 0;
    if (!pManager->GetPropertyListRaw(nInstanceID, nGroupID, &pList))
        return nDefault;
    Variant value;
    if (!pList->GetPropertyAsVariant(nPropertyID, &value)) {
        if (pList)
            pList->Release();
        return nDefault;
    }
    uint32_t nResult;
    uint16_t nType = value.mType;
    if (nType == 9 || nType == 0x10) {
        if (value.mFlags & 0x30)
            nResult = *(uint32_t*)value.mData;
        else if (nType != 0)
            nResult = (uint32_t)&value;
        else
            nResult = 0;
    } else {
        nResult = g_kDefaultPropertyVariant;
    }
    if (pList)
        pList->Release();
    return (int32_t)nResult;
}

// @ 0x00bda470
void SerializeTradePartners(cObjectStream* pStream, const cPtrVec* pPartners)
{
    int32_t nCount = (int32_t)(((char*)pPartners->mpEnd - (char*)pPartners->mpBegin) / 0xc);
    void* pRaw = pStream->GetWriter()->GetRaw();
    EA_IO_WriteUint32(pRaw, &nCount, 1, 0);
    cAutoRef12* pIter = (cAutoRef12*)pPartners->mpBegin;
    cAutoRef12* pEnd = (cAutoRef12*)pPartners->mpEnd;
    for (; pIter != pEnd; ++pIter) {
        pStream->WriteInt((uint32_t)pIter->mpSecond);
        pStream->WriteInt((uint32_t)pIter->mpFirst);
        pStream->WriteBytes(&pIter->mField08, 4);
    }
    pStream->Close();
}

// @ 0x00bda500
void SerializeCultureTargetInfo(cObjectStream* pStream, const cPtrVec* pInfos)
{
    int32_t nCount = (int32_t)(((char*)pInfos->mpEnd - (char*)pInfos->mpBegin) >> 7);
    void* pRaw = pStream->GetWriter()->GetRaw();
    EA_IO_WriteUint32(pRaw, &nCount, 1, 0);
    tCultureTargetInfo* pIter = (tCultureTargetInfo*)pInfos->mpBegin;
    tCultureTargetInfo* pEnd = (tCultureTargetInfo*)pInfos->mpEnd;
    for (; pIter != pEnd; pIter += 1) {
        cVarListSerializer serializer(pIter, kSerializerGroup, kCultureTargetInfoNote);
        serializer.Serialize(pStream);
    }
    pStream->Close();
}

// @ 0x00bda590
bool WriteTextCultureTargetInfo(cObjectStream* pStream, const cPtrVec* pInfos)
{
    tCultureTargetInfo* pIter = (tCultureTargetInfo*)pInfos->mpBegin;
    tCultureTargetInfo* pEnd = (tCultureTargetInfo*)pInfos->mpEnd;
    for (; pIter != pEnd; pIter += 1) {
        if (pIter)
            pStream->SerializeText(pIter, kSerializerGroup, kCultureTargetInfoName);
    }
    return true;
}

// @ 0x00bda6a0
bool ContainsInt(const cPtrVec* pVec, const int32_t* pValue)
{
    const int32_t* pEnd = (const int32_t*)pVec->mpEnd;
    const int32_t* pIter = (const int32_t*)pVec->mpBegin;
    while (pIter != pEnd) {
        if (*pIter == *pValue)
            break;
        ++pIter;
    }
    return pIter != pEnd;
}

// @ 0x00bda6d0
void __stdcall DestroyRefPairs(cAutoRef12* pFirst, cAutoRef12* pLast)
{
    for (; pFirst < pLast; pFirst += 1) {
        cAutoRefData* pSecond = pFirst->mpSecond;
        if (pSecond)
            pSecond->Release();
        cAutoRefData* pFirst0 = pFirst->mpFirst;
        if (pFirst0)
            pFirst0->Release();
    }
}

// @ 0x00bda710
void __stdcall DestroyCultureTargetInfo(tCultureTargetInfo* pFirst, tCultureTargetInfo* pLast)
{
    for (; pFirst < pLast; pFirst += 1) {
        cGameData* pCulture = pFirst->mpCultureObject;
        if (pCulture)
            pCulture->ReleaseGameData();
        cGameData* pTarget = pFirst->mpAttackTarget;
        if (pTarget)
            pTarget->ReleaseGameData();
        DestroyGonzagoTimer(pFirst->mConvertedTimer);
        DestroyGonzagoTimer(pFirst->mConvertCheckTimer);
    }
}

// @ 0x00bda760
cRefOps* __thiscall cRefOps::AssignRefPairObj(const cAutoRef12* pSrc)
{
    cAutoRef12* pDst = (cAutoRef12*)this;
    cAutoRefData* pNew = pSrc->mpFirst;
    cAutoRefData* pOld = pDst->mpFirst;
    if (pNew != pOld) {
        if (pNew)
            pNew->AddRef();
        pDst->mpFirst = pNew;
        if (pOld)
            pOld->Release();
    }
    pNew = pSrc->mpSecond;
    pOld = pDst->mpSecond;
    if (pNew != pOld) {
        if (pNew)
            pNew->AddRef();
        pDst->mpSecond = pNew;
        if (pOld)
            pOld->Release();
    }
    pDst->mField08 = pSrc->mField08;
    return this;
}

// @ 0x00bda7d0
void __thiscall cRefOps::CopyTransform50Obj(const void* pSrc)
{
    void* pDst = this;
    const uint32_t* pS = (const uint32_t*)pSrc;
    uint32_t* pD = (uint32_t*)pDst;
    pD[0] = pS[0];
    pD[1] = pS[1];
    for (int32_t n = 2; n < 0x14; ++n)
        ((float*)pD)[n] = ((const float*)pS)[n];
}

// @ 0x00bda850
void CopyBucket20(uint8_t* pSrc, uint8_t* pEnd, uint8_t* pDst)
{
    while (pSrc != pEnd) {
        if (pDst) {
            *(float*)(pDst + 0x00) = *(const float*)(pSrc + 0x00);
            *(float*)(pDst + 0x04) = *(const float*)(pSrc + 0x04);
            *(float*)(pDst + 0x08) = *(const float*)(pSrc + 0x08);
            *(float*)(pDst + 0x0c) = *(const float*)(pSrc + 0x0c);
            *(uint32_t*)(pDst + 0x10) = *(const uint32_t*)(pSrc + 0x10);
        }
        pSrc += 0x14;
        pDst += 0x14;
    }
}

// @ 0x00bda8d0
cAutoRef12* CopyRefPairs(cAutoRef12* pSrc, cAutoRef12* pEnd, cAutoRef12* pDst)
{
    while (pSrc != pEnd) {
        if (pDst) {
            cAutoRefData* pFirst = pSrc->mpFirst;
            pDst->mpFirst = pFirst;
            if (pFirst)
                pFirst->AddRef();
            cAutoRefData* pSecond = pSrc->mpSecond;
            pDst->mpSecond = pSecond;
            if (pSecond)
                pSecond->AddRef();
            pDst->mField08 = pSrc->mField08;
        }
        ++pSrc;
        ++pDst;
    }
    return pDst;
}

// @ 0x00bda930
cAutoRef12* DestroyRefPairsReturn(cAutoRef12* pSrc, cAutoRef12* pEnd, cAutoRef12* pDst)
{
    while (pSrc != pEnd) {
        cAutoRefData* pSecond = pSrc->mpSecond;
        if (pSecond)
            pSecond->Release();
        cAutoRefData* pFirst = pSrc->mpFirst;
        if (pFirst)
            pFirst->Release();
        ++pSrc;
        ++pDst;
    }
    return pDst;
}

// @ 0x00bda980
cAutoRef12* AssignRefPairRange(cAutoRef12* pSrc, cAutoRef12* pEnd, cAutoRef12* pDst)
{
    while (pSrc != pEnd) {
        cAutoRefData* pNew = pSrc->mpFirst;
        cAutoRefData* pOld = pDst->mpFirst;
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            pDst->mpFirst = pNew;
            if (pOld)
                pOld->Release();
        }
        pNew = pSrc->mpSecond;
        pOld = pDst->mpSecond;
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            pDst->mpSecond = pNew;
            if (pOld)
                pOld->Release();
        }
        pDst->mField08 = pSrc->mField08;
        ++pSrc;
        ++pDst;
    }
    return pDst;
}

// @ 0x00bdaa90
void CopyBucket28(uint8_t* pSrc, uint8_t* pEnd, uint8_t* pDst)
{
    while (pSrc != pEnd) {
        if (pDst) {
            *(float*)(pDst + 0x00) = *(const float*)(pSrc + 0x00);
            *(float*)(pDst + 0x04) = *(const float*)(pSrc + 0x04);
            *(float*)(pDst + 0x08) = *(const float*)(pSrc + 0x08);
            *(uint32_t*)(pDst + 0x0c) = *(const uint32_t*)(pSrc + 0x0c);
            *(uint32_t*)(pDst + 0x10) = *(const uint32_t*)(pSrc + 0x10);
            *(uint32_t*)(pDst + 0x14) = *(const uint32_t*)(pSrc + 0x14);
            *(pDst + 0x18) = *(pSrc + 0x18);
        }
        pSrc += 0x1c;
        pDst += 0x1c;
    }
}

// @ 0x00bdaae0
cAutoRef12* AssignRefPairRangeBackward(cAutoRef12* pFirst, cAutoRef12* pLast, cAutoRef12* pDstEnd)
{
    if (pLast == pFirst)
        return pDstEnd;
    do {
        cAutoRefData* pNew = (pLast - 1)->mpFirst;
        cAutoRefData* pOld = (pDstEnd - 1)->mpFirst;
        --pLast;
        --pDstEnd;
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            pDstEnd->mpFirst = pNew;
            if (pOld)
                pOld->Release();
        }
        pNew = pLast->mpSecond;
        pOld = pDstEnd->mpSecond;
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            pDstEnd->mpSecond = pNew;
            if (pOld)
                pOld->Release();
        }
        pDstEnd->mField08 = pLast->mField08;
    } while (pLast != pFirst);
    return pDstEnd;
}

// @ 0x00bdace0
cCulturalTarget::~cCulturalTarget()
{
    cCombatant* pCombatant = &mCombatant;
    cSpatialObject* pSpatial = (cSpatialObject*)((char*)this + 0x100);
    cGameData* pHitSphere = mpHitSphere;
    if (pHitSphere)
        pHitSphere->Release();
    DestroyAutoRefVector(&mAttackers);
    void* pOrders = mAttackOrders.mpBegin;
    if (pOrders && ((int32_t*)pOrders)[-1] != 0)
        operator_delete(pOrders);
    DestroySpatialObject(pSpatial);
    DestroyCombatant(pCombatant);
    DestroyGameData((cGameData*)this);
}

// @ 0x00bdad60
bool cCulturalTarget::RemoveAttacker(cGameData* pTarget)
{
    uint32_t nKey = pTarget ? (uint32_t)pTarget->Cast(kCultureTargetCastType) : 0;
    int32_t nCount = (int32_t)(((char*)mAttackers.mpEnd - (char*)mAttackers.mpBegin) >> 2);
    int32_t nIndex = -1;
    uint8_t bResult = 0;
    if (nCount > 0) {
        for (int32_t i = 0; i < nCount; ++i) {
            if (nIndex >= 0)
                break;
            if (((uint32_t*)mAttackers.mpBegin)[i] == nKey)
                nIndex = i;
        }
        if (nIndex >= 0) {
            for (; nIndex < nCount - 1; ++nIndex) {
                cGameData** pSlot = &((cGameData**)mAttackers.mpBegin)[nIndex];
                cGameData* pNew = pSlot[1];
                cGameData* pOld = pSlot[0];
                if (pNew != pOld) {
                    if (pNew)
                        pNew->AddRef();
                    pSlot[0] = pNew;
                    if (pOld)
                        pOld->Release();
                }
            }
            mAttackers.mpEnd = (char*)mAttackers.mpEnd - 4;
            cGameData* pLast = *(cGameData**)mAttackers.mpEnd;
            if (pLast)
                pLast->Release();
            bResult = 1;
        }
    }
    if (mAttackState != 0) {
        if (mAttackers.mpBegin == mAttackers.mpEnd) {
            mAttackState = 1;
            mAttackerPoliticalID = 0xffffffff;
            return bResult;
        }
        mAttackState = 2;
        cGameData* pFirst = *(cGameData**)mAttackers.mpBegin;
        cCityCiv* pCiv = (cCityCiv*)((char*)pFirst + 0x508);
        mAttackerPoliticalID = (uint32_t)pCiv->GetPoliticalID();
    }
    return bResult;
}

// @ 0x00bdaea0
void cSimObject::UpdateAggregationRadius()
{
    if (!mpCityHall)
        return;
    if (!mpCityHall->GetHallTarget())
        return;
    if (GetCurrentGameMode() == (void*)kSpaceGameModeID) {
        float fRadius = mpCityHall->mTransform34.GetRadius() * kCultureScaleSpace;
        mpCityHall->GetHallTarget()->mRadius = fRadius;
        return;
    }
    float fWallRadius = mpCityWalls->mRadius;
    mpCityHall->GetHallTarget()->mRadius = sqrtf(fWallRadius * fWallRadius) * kCultureScalePlanet;
}

// @ 0x00bdaf50
void cSimObject::FillCulturalTargetPoints()
{
    cPtrVec points;
    points.mpBegin = 0;
    points.mpEnd = 0;
    points.mpCapacity = 0;
    FillPoints(&points);
    uint32_t nOffset = 0;
    uint32_t nIndex = 0;
    do {
        cCulturalTarget* pTarget = mCulturalTargets[nIndex];
        Vector3* pPoint = (Vector3*)((char*)points.mpBegin + nOffset);
        pTarget->GetSpatial()->SetPosition(pPoint);
        Vector3 planetPosition;
        mSpatial120.GetPlanetPosition(&planetPosition);
        float fDeltaX = pPoint->x - planetPosition.x;
        float fDeltaY = pPoint->y - planetPosition.y;
        float fDeltaZ = pPoint->z - planetPosition.z;
        float fInvLen = 1.0f / sqrtf((fDeltaY * fDeltaY + fDeltaZ * fDeltaZ) + fDeltaX * fDeltaX + kSqrtEpsilon);
        Vector3 direction;
        direction.x = fInvLen * fDeltaX;
        direction.y = fInvLen * fDeltaY;
        direction.z = fInvLen * fDeltaZ;
        cCulturalTarget* pTarget2 = mCulturalTargets[nIndex];
        Quaternion orientation;
        PlanetModel();
        BuildSurfaceOrientation2(&orientation, &direction, pPoint);
        pTarget2->GetSpatial()->SetOrientation(&orientation);
        nOffset += 0xc;
        ++nIndex;
    } while (nIndex < 4);
    if (points.mpBegin && ((int32_t*)points.mpBegin)[-1] != 0)
        operator_delete(points.mpBegin);
}

// @ 0x00bdb0b0
void cSimObject::EmitCulturalEffect()
{
    cCityHall* pHall = mpCityHall;
    mbField2E6 = 0;
    if (!pHall)
        return;
    uint32_t nEffectID;
    if (mContextState == 0)
        nEffectID = kCulturalEffect0;
    else if (mContextState == 1)
        nEffectID = kCulturalEffect1;
    else if (mContextState == 2)
        nEffectID = kCulturalEffect2;
    else
        nEffectID = 0;
    cHallTransform* pTransform = &pHall->mTransform34;
    cHallTarget* pTarget = pTransform->GetTarget();
    Vector3* pPosition = pTransform->GetPosition();
    float fScale = pTarget->mScale;
    float fInvLen = 1.0f / sqrtf((pPosition->x * pPosition->x + pPosition->y * pPosition->y) +
                                 pPosition->z * pPosition->z + kSqrtEpsilon);
    Vector3 offset;
    offset.x = fScale * (fInvLen * pPosition->x);
    offset.y = fScale * (pPosition->y * fInvLen);
    offset.z = fScale * (pPosition->z * fInvLen);
    Vector3* pBase = pTransform->GetPosition();
    Vector3 position;
    position.x = offset.x + pBase->x;
    position.y = offset.y + pBase->y;
    position.z = offset.z + pBase->z;
    cDispatcher* pDispatcher = GetDispatcher();
    void* pXform = pTransform->MakeTransform(&offset);
    pDispatcher->mpVtbl->pFire(pDispatcher, nEffectID, &position, pXform);
}

// @ 0x00bdb200
bool cCity::HasTradePartnerCiv(int32_t nNounID)
{
    uint32_t nCount = (uint32_t)(((char*)mTradePartners.mpEnd - (char*)mTradePartners.mpBegin) / 0xc);
    if (nCount != 0) {
        uint32_t nIndex = 0;
        do {
            cTradePartnerCity* pPartner =
                *(cTradePartnerCity**)((char*)mTradePartners.mpBegin + nIndex * 0xc);
            if (pPartner->mpCivilization->GetPoliticalID() == nNounID)
                return true;
            ++nIndex;
            nCount = (uint32_t)(((char*)mTradePartners.mpEnd - (char*)mTradePartners.mpBegin) / 0xc);
        } while (nIndex < nCount);
    }
    return false;
}

// @ 0x00bdb280
cCity* cCity::FindTradePartnerCity(int32_t nNounID)
{
    float fBestDistance = kFloatMax;
    cCity* pBest = 0;
    uint32_t nCount = (uint32_t)(((char*)mTradePartners.mpEnd - (char*)mTradePartners.mpBegin) / 0xc);
    if (nCount != 0) {
        uint32_t nIndex = 0;
        do {
            cTradePartnerCity* pPartner =
                *(cTradePartnerCity**)((char*)mTradePartners.mpBegin + nIndex * 0xc);
            if (pPartner->mpCivilization->GetPoliticalID() == nNounID) {
                Vector3* pPartnerPosition = pPartner->mSpatial.GetPosition(0);
                Vector3* pOwnPosition = mSpatial120.GetPosition(0);
                float fDeltaX = pOwnPosition->x - pPartnerPosition->x;
                float fDeltaY = pOwnPosition->y - pPartnerPosition->y;
                float fDeltaZ = pOwnPosition->z - pPartnerPosition->z;
                float fDistance = sqrtf((fDeltaZ * fDeltaZ + fDeltaY * fDeltaY) + fDeltaX * fDeltaX);
                if (fDistance < fBestDistance) {
                    fBestDistance = fDistance;
                    pBest = (cCity*)pPartner;
                }
            }
            ++nIndex;
            nCount = (uint32_t)(((char*)mTradePartners.mpEnd - (char*)mTradePartners.mpBegin) / 0xc);
        } while (nIndex < nCount);
    }
    return pBest;
}

// ---------------------------------------------------------------------------
// Simulator::cCulturalTarget constructor (gold8 function 00bdab60).
// The retail class lives in namespace Simulator; the dtor above models the same
// object at global scope, so this constructor uses its own same-layout view.
// ---------------------------------------------------------------------------
namespace Simulator {

struct CGameDataPart {
    void* volatile mpVtbl;  // +0x00
    void Ctor();            // 0x00b18660
};

struct CCombatantPart {
    void* volatile mpVtbl;  // +0x00
    void Ctor();            // 0x00bfd4e0
};

struct CSpatialPart {
    void* volatile mpVtbl;  // +0x00
    void Ctor();            // 0x00c89630
};

struct VPtrVec {
    void* volatile mpBegin;     // +0x00
    void* volatile mpEnd;       // +0x04
    void* volatile mpCapacity;  // +0x08
};

struct cCulturalTarget {
    CGameDataPart  mGameData;                           // +0x000
    void* volatile mpVtbl04;                            // +0x004
    char           mPad008[0x30];                       // +0x008 .. +0x037
    CCombatantPart mCombatant;                          // +0x038
    char           mPad03c[0xc4];                       // +0x03c .. +0x0ff
    CSpatialPart   mSpatial;                            // +0x100
    char           mPad104[0xd0];                       // +0x104 .. +0x1d3
    uint8_t        volatile mGateIndex;                 // +0x1d4
    char           mPad1d5[3];                          // +0x1d5 .. +0x1d7
    int32_t        volatile mAttackState;               // +0x1d8
    uint32_t       volatile mAttackerPoliticalID;       // +0x1dc
    VPtrVec        mAttackOrders;                       // +0x1e0
    char           mPad1ec[8];                          // +0x1ec .. +0x1f3
    VPtrVec        mAttackers;                          // +0x1f4
    char           mPad200[8];                          // +0x200 .. +0x207
    void*          volatile mpHitSphere;                // +0x208
    float          mLastDancingCrowdFraction;           // +0x20c
    float          mLastAngryCrowdFraction;             // +0x210
    int32_t        volatile mAngerLevel;                // +0x214

    cCulturalTarget();
};

typedef char cCulturalTargetSizeCheck[(sizeof(cCulturalTarget) == 0x218) ? 1 : -1];

// @ 0x00bdab60
cCulturalTarget::cCulturalTarget()
{
    mGameData.Ctor();
    mCombatant.Ctor();
    mSpatial.Ctor();

    mAttackState = 0;

    mGameData.mpVtbl = (void*)0x1468618;
    mpVtbl04 = (void*)0x1468608;
    mCombatant.mpVtbl = (void*)0x14685a0;
    mSpatial.mpVtbl = (void*)0x14684d8;

    mGateIndex = 0xff;
    mAttackerPoliticalID = 0xffffffff;

    mAttackOrders.mpBegin = 0;
    mAttackOrders.mpEnd = 0;
    mAttackOrders.mpCapacity = 0;
    mAttackers.mpBegin = 0;
    mAttackers.mpEnd = 0;
    mAttackers.mpCapacity = 0;
    mpHitSphere = 0;
    mAngerLevel = 0;
    mLastDancingCrowdFraction = 0.0f;
    mLastAngryCrowdFraction = 0.0f;
}

}  // namespace Simulator
