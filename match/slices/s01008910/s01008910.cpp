// s01008910 -- SP::cSPSimulatorSpaceGame galaxy / solar-system NPC-UFO helpers.
//
//   0x01008910 GalaxyTestForIntercept
//   0x01008e60 SpawnNPC_UFOs
//   0x010091d0 SolarSystemSpawnNPC_UFOs
//   0x01009470 DestroyNPC_UFOs
//   0x010095e0 StartAmbush
//   0x010097f0 StartSetiAmbush
//
// Layout note: the field offsets below are taken from the disassembly of this
// build, where the NPC-UFO vector (SPVector<AutoRefCount>) sits at this+0x78 and
// the civilisations come from this+0x30.  The shipped SporeApp.pdb types
// cSPSimulatorSpaceGame with that vector at +0xa8; the call targets of the
// helpers in this block are ICF-folded aliases, so the code is the authority.
#include "types.h"

#define nullptr 0

// ---------------------------------------------------------------------------
// small engine types
// ---------------------------------------------------------------------------
struct Vec3 { float x, y, z; };

// EA::RefCountVTemplate<int> -- virtual AddRef/Release.
class IRefCount {
public:
    virtual void AddRef();          // +0x00
    virtual void Release();         // +0x04
};

struct AutoRefCount {
    IRefCount* mpObject;            // +0x00
};

struct VectorAllocHeader {
    int32_t mnCapacity;             // stored in front of an eastl sp_vector block
};

// EA::ResourceMan::Key
struct ResourceKey {
    uint32_t mnInstanceId;          // +0x00
    uint16_t mnGroupId;             // +0x04
    uint16_t mnTypeId;              // +0x06
};

void __cdecl operator_delete_array(void* pBlock);           // 0x00f47380

// ---------------------------------------------------------------------------
// SPVector<EA::AutoRefCount<T> >
// ---------------------------------------------------------------------------
class SPVector {
public:
    AutoRefCount* mpBegin;          // +0x00
    AutoRefCount* mpEnd;            // +0x04
    AutoRefCount* mpCapacity;       // +0x08

    void DoInsertPtr(AutoRefCount* pPos, const AutoRefCount& rValue);   // 0x00aea5d0
    void PushBack(const AutoRefCount& rValue);                          // 0x00e1c7f0
    void DestroyListedUFOs(SPVector* pList);                            // 0x01008600

    void Destroy()
    {
        for (AutoRefCount* p = mpBegin; p < mpEnd; ++p) {
            if (p->mpObject != nullptr)
                p->mpObject->Release();
        }
        if (mpBegin != nullptr &&
            reinterpret_cast<VectorAllocHeader*>(mpBegin)[-1].mnCapacity != 0) {
            operator_delete_array(mpBegin);
        }
    }
};

// ---------------------------------------------------------------------------
// game data nouns
// ---------------------------------------------------------------------------
class cEmpire;
class cStarMap;
class cStarManager;
class cUFOFactory;
class cTerrainSphere;
class cSimUniverse;
class cStarMapVisual;
class cPlanet;
class cSPGameDataUFO;
class cPlayerInventory;
class cLocalCivContext;

namespace SP { class cSPSimulatorSpaceGame; }

class cGameData {                   // cGameNounManager / cStarRecord noun
public:
    uint8_t mPad00[0x28];           // +0x000
    int32_t mnField28;              // +0x028
    uint8_t mPad2c[0x70 - 0x2c];    // +0x02c
    int32_t mnStarId;               // +0x070

    int32_t GetAvatar();            // 0x00b1fdb0
    float* GetCities();             // 0x005c65e0
    float* GetCities(void* pFilter);    // 0x005c65e0 (folded alias)
    bool IsColonizable();           // 0x00b8d970
};

class cEmpire {
public:
    uint32_t GetUFOKey(const void* pKeyOut = nullptr);  // 0x00c326b0
    bool HasUFO();                                      // 0x00c31640
};

class cStarRecordVisual {
public:
    virtual void V00();             // +0x00
    virtual void V04();             // +0x04
    virtual void SetVisible(bool bVisible);     // +0x08
    virtual void V0c();             // +0x0c
    virtual bool IsVisible();       // +0x10
    virtual void V14();             // +0x14
    virtual void V18();             // +0x18
    virtual void V1c();             // +0x1c
    virtual void V20();             // +0x20
    virtual void V24();             // +0x24
    virtual void V28();             // +0x28
    virtual void V2c();             // +0x2c
    virtual void V30();             // +0x30
    virtual void V34();             // +0x34
    virtual void V38();             // +0x38
    virtual void V3c();             // +0x3c
    virtual void V40();             // +0x40
    virtual void SetFlags(int32_t nA, void* pB, int32_t nC);    // +0x44
};

class cStarMap {
public:
    bool HasRecordVisuals();                                    // 0x010449e0
    cStarRecordVisual* GetRecordVisual();                       // 0x01045190
    void RemoveVisual();                                        // 0x01045ae0
    void CreateStarRecordVisual(cGameData* pTarget, uint32_t nType, uint32_t nKey); // 0x010458f0
};

class cStarManager {
public:
    cEmpire* GetEmpireByID(int32_t nEmpireId);                  // 0x00ba9370
    void GetStarRecords(SPVector* pOut);                        // 0x00bb1080
    cPlanet* GetOrActivatePlanet(cGameData* pRecord, cPlanet** ppOut); // 0x00bb59b0
};

class cRelationshipManager {
public:
    bool IsAllied(int32_t nEmpireA, int32_t nEmpireB);          // 0x00d01fb0
    bool AreAtWar(cEmpire* pEmpireA, cEmpire* pEmpireB);        // 0x00d01ff0
};

class cTerrainSphere {
public:
    bool IsSpace();                                             // 0x00c77410
    void FUN_00c79f20(cGameData* pNoun);                        // 0x00c79f20
};

class cNounManager {
public:
    cTerrainSphere* GetCurrentTerrainSphere();                  // 0x00f67d90
};

class cProperty {
public:
    uint8_t mPad00[0x12];           // +0x00
    uint16_t mnType;                // +0x12
    float* GetFloat();              // 0x0041ea70
};

class ISimPropertyHost {
public:
    virtual void V00();             // +0x00
    virtual void V04();             // +0x04
    virtual void V08();             // +0x08
    virtual void V0c();             // +0x0c
    virtual void V10();             // +0x10
    virtual void V14();             // +0x14
    virtual void V18();             // +0x18
    virtual void V1c();             // +0x1c
    virtual void V20();             // +0x20
    virtual bool GetProperty(uint32_t nPropertyId, void** ppOut);   // +0x24
};

class cSimUniverse {
public:
    uint8_t mPad00[0x10];           // +0x00
    ISimPropertyHost* mpPropertyHost;   // +0x10
};

class cSPLivingUniverse {
public:
    uint8_t mPad00[0x84];           // +0x00
    int32_t mnPlayerEmpire;         // +0x84
};

class cInventoryPosition {
public:
    virtual void V00();             // +0x00
    virtual void V04();             // +0x04
    virtual void V08();             // +0x08
    virtual void V0c();             // +0x0c
    virtual void V10();             // +0x10
    virtual void V14();             // +0x14
    virtual void V18();             // +0x18
    virtual void V1c();             // +0x1c
    virtual void V20();             // +0x20
    virtual void V24();             // +0x24
    virtual void V28();             // +0x28
    virtual Vec3* GetPosition();    // +0x2c
};

class cPlayerInventory {
public:
    uint8_t mPad00[0x34];           // +0x00
    cInventoryPosition mPosition;   // +0x34
};

class cLocomotiveObject {
public:
    virtual void V00();             // +0x00
    virtual void V04();             // +0x04
    virtual void V08();             // +0x08
    virtual void V0c();             // +0x0c
    virtual void V10();             // +0x10
    virtual void V14();             // +0x14
    virtual void V18();             // +0x18
    virtual void V1c();             // +0x1c
    virtual void V20();             // +0x20
    virtual void V24();             // +0x24
    virtual void V28();             // +0x28
    virtual void V2c();             // +0x2c
    virtual void V30();             // +0x30
    virtual void V34();             // +0x34
    virtual void V38();             // +0x38
    virtual void V3c();             // +0x3c
    virtual void SetScale(float fScale);    // +0x40
};

// The UFO game data object (state at +0x714, target at +0x7b0).
class cSPGameDataUFO : public IRefCount {
public:
    uint8_t mPad04[0x34 - 0x04];        // +0x004
    cLocomotiveObject mLocation;        // +0x034
    uint8_t mPad38[0x6bc - 0x38];       // +0x038
    Vec3 mVec6bc;                       // +0x6bc
    uint8_t mPad6c8[0x714 - 0x6c8];     // +0x6c8
    int32_t mnState;                    // +0x714
    Vec3 mVec718;                       // +0x718
    uint8_t mPad724[0x7b0 - 0x724];     // +0x724
    cGameData* mpTarget;                // +0x7b0  (ambush target)

    void SetDesiredModel(const ResourceKey& rKey, int32_t nFlags);  // 0x00c37180
    void PopToDestination();                                        // 0x00c37e60
    void SetDestination(const Vec3* pPosition);                     // 0x00c3bfe0
    void SetDestination(cPlanet* pPlanet);                          // 0x00c3c190
    void SetLocalPosition(const Vec3* pPosition);                   // 0x00c3dae0
    void SetTarget(cGameData* pTarget);                             // 0x00c3c360
};

// cPlanet's vtable is wide; only the +0xc0 slot (Release) is used in this block.
class cPlanetVtblPrefix {
public:
    virtual void V000(); virtual void V004(); virtual void V008(); virtual void V00c();
    virtual void V010(); virtual void V014(); virtual void V018(); virtual void V01c();
    virtual void V020(); virtual void V024(); virtual void V028(); virtual void V02c();
    virtual void V030(); virtual void V034(); virtual void V038(); virtual void V03c();
    virtual void V040(); virtual void V044(); virtual void V048(); virtual void V04c();
    virtual void V050(); virtual void V054(); virtual void V058(); virtual void V05c();
    virtual void V060(); virtual void V064(); virtual void V068(); virtual void V06c();
    virtual void V070(); virtual void V074(); virtual void V078(); virtual void V07c();
    virtual void V080(); virtual void V084(); virtual void V088(); virtual void V08c();
    virtual void V090(); virtual void V094(); virtual void V098(); virtual void V09c();
    virtual void V0a0(); virtual void V0a4(); virtual void V0a8(); virtual void V0ac();
    virtual void V0b0(); virtual void V0b4(); virtual void V0b8(); virtual void V0bc();
};

class cPlanet : public cPlanetVtblPrefix {
public:
    virtual void ReleaseObject();   // +0x0c0
};

class cUFOFactory {
public:
    virtual void V00();             // +0x00
    virtual void V04();             // +0x04
    virtual void V08();             // +0x08
    virtual void V0c();             // +0x0c
    virtual void V10();             // +0x10
    virtual void V14();             // +0x14
    virtual void V18();             // +0x18
    virtual bool HasUFOTypeA(uint32_t nKey);    // +0x1c
    virtual void V20();             // +0x20
    virtual void V24();             // +0x24
    virtual void V28();             // +0x28
    virtual void V2c();             // +0x2c
    virtual void V30();             // +0x30
    virtual void V34();             // +0x34
    virtual void V38();             // +0x38
    virtual bool HasUFOTypeB(uint32_t nKey);    // +0x3c
    virtual void V40();             // +0x40
    virtual void V44();             // +0x44
    virtual void V48();             // +0x48
    virtual void SetUFOTypeC(uint32_t nKey);    // +0x4c
};

class cSpaceTokenTranslator {
public:
    uint8_t mPad00[0x1c];           // +0x00
    cEmpire* mpEmpire;              // +0x1c
};

class cCamInfo {
public:
    int32_t mData[24];              // opaque camera description
    void Init(float* pCity);        // 0x00ad79d0
};

class cActionTarget {
public:
    int32_t mData[8];               // opaque action parameter
    cActionTarget* Init(void* pArg, int32_t nZero);     // 0x00ad7a30
    void Destroy();                 // 0x00ad7ad0
};

class cTriggerMgr {
public:
    void PostAction(uint32_t nAction, void* pParam, int32_t nFlags);    // 0x00ae09b0
};

// A filter/query block handed to cCivData::GetCities when collecting star records.
struct StarRecordFilter {
    int32_t mnFlags;                // +0x00
    int32_t mnTypeMask;             // +0x04
    int32_t mnField08;              // +0x08
    int32_t mnField0c;              // +0x0c
    int32_t mnField10;              // +0x10
    int32_t mnField14;              // +0x14
    int32_t mnField18;              // +0x18
    float mfMinValue;               // +0x1c
    float mfZero;                   // +0x20
    float mfScale;                  // +0x24
    int32_t mnField28;              // +0x28
};

class RandomLinearCongruential {
public:
    double RandomDoubleUniform();                   // 0x009360d0
    uint32_t RandomUint32Uniform(uint32_t nRange);  // 0x00a68fb0
};

class cUFOTypeOwner {
public:
    void GetModelKey(ResourceKey* pKey);            // 0x0102f660
};

class cAmbushContext {
public:
    uint8_t mPad00[0x160];          // +0x000
    cUFOTypeOwner mUFOTypeOwner;    // +0x160
};

class cSpaceStageUniverse {
public:
    uint8_t mPad00[0x68];           // +0x000
    SPVector mVisibleCivs;          // +0x068
    uint8_t mPad74[0x7c - 0x74];    // +0x074
    SPVector mCivs;                 // +0x07c
};

class cStarRecordHolder {
public:
    SPVector* GetStarRecords();     // 0x00bba790
};

class cLocalCivContext {
public:
    uint8_t mPad00[0x48];           // +0x000
    cStarRecordHolder mRecords;     // +0x048
};

// ---------------------------------------------------------------------------
// engine accessors / free routines (absolute call targets are relocated)
// ---------------------------------------------------------------------------
cNounManager*        __cdecl NounManager();         // 0x00b3d300
cStarManager*        __cdecl StarManager();         // 0x00b3d2a0
cRelationshipManager* __cdecl RelationshipManager();    // 0x00b3d2c0
cTriggerMgr*         __cdecl GetTriggerMgr();       // 0x00b3d4d0
cUFOFactory*         __cdecl UFOFactory();          // 0x00401010
SP::cSPSimulatorSpaceGame* __cdecl GetUFOSimulator();   // 0x00ffbe50
cSPLivingUniverse*   __cdecl GetLivingUniverse();   // 0x01021300
int32_t              __cdecl GetPlayerEmpireID();   // 0x01021090
cGameData*           __cdecl GetLocalCiv();         // 0x01021240
cLocalCivContext*    __cdecl GetLocalCivContext();  // 0x01021230
cAmbushContext*      __cdecl GetAmbushContext();    // 0x00fd9c60
void*                __cdecl GetSelectedStar();     // 0x00885c90
void                 __cdecl GetAmbushOffset(Vec3* pOut);   // 0x00ebbb40
void                 __cdecl ShowTutorialText(const char* pText, uint32_t nId, int32_t nOne); // 0x01041c50
void                 __cdecl ShuffleStarRecords(AutoRefCount* pBegin, AutoRefCount* pEnd,
                                                RandomLinearCongruential* pRandom); // 0x00b96130

cStarMap* __cdecl   GetStarMap0();                                          // 0x01046fc0
cStarMap* __stdcall GetStarMap1(int32_t nType);                             // 0x01046fc0
cStarMap* __stdcall GetStarMap3(int32_t nStarId, uint32_t nKey, int32_t nFlags);    // 0x01046fc0
cStarMap* __stdcall GetStarMap4(int32_t nStarId, uint32_t nKey, int32_t nFlags, int32_t nOne);  // 0x01046fc0

cSPGameDataUFO* __cdecl CreateUFOForSolarOrGalaxy(int32_t nState, cEmpire* pEmpire);   // 0x0102ac50
void __cdecl DestroyCreature(cSPGameDataUFO* pUFO, int32_t nFlags);                    // 0x0102c340
extern "C" double __cdecl exp(double);      // expanded inline by clx (f2xm1/fscale)

extern "C" cSimUniverse* gSimUniverse;                          // 0x016dc798
extern "C" cSpaceTokenTranslator* gSpaceTokenTranslator;        // 0x016e0d08
extern "C" RandomLinearCongruential gRandom;                    // 0x01601760

extern "C" float    gfCityInterceptScale;       // 0x015b689c
extern "C" float    gfNPCMinChance;             // 0x015b68a0
extern "C" int32_t  gnMaxNPCUFOs;               // 0x015b68a4
extern "C" float    gfNPCCountScale;            // 0x015b68a8
extern "C" float    gfNPCDivisor;               // 0x015b68ac
extern "C" float    gfUFOAmbushScale;           // 0x015b68b0
extern "C" float    gfSolarNPCDivisor;          // 0x015b68b4
extern "C" int32_t  gnAmbushUFOCount;           // 0x015b68b8

// ---------------------------------------------------------------------------
// SP::cSPSimulatorSpaceGame
// ---------------------------------------------------------------------------
namespace SP {

class cSPSimulatorSpaceGame {
public:
    void GalaxyTestForIntercept();                                  // 0x01008910
    void SpawnNPC_UFOs(float fChance);                              // 0x01008e60
    void SolarSystemSpawnNPC_UFOs(float fChance);                   // 0x010091d0
    void DestroyNPC_UFOs(char bParam2, char bParam3, int32_t nFlags);   // 0x01009470
    void StartAmbush();                                             // 0x010095e0
    void StartSetiAmbush();                                         // 0x010097f0

    cPlayerInventory* GetPlayerInventory();                         // 0x00a1ad60
    void FUN_01008270(int32_t nZero);                               // 0x01008270
    void FUN_010077e0();                                            // 0x010077e0

private:
    uint8_t mPad00[0x30];               // +0x000
    cSpaceStageUniverse* mpUniverse;    // +0x030
    uint8_t mPad34[0x78 - 0x34];        // +0x034
    SPVector mNPC_UFOs;                 // +0x078
};

} // namespace SP

// Append a UFO to a UFO list, exactly as the inlined SPVector insert does.
static void InsertUFO(SPVector& rVector, cSPGameDataUFO* pUFO)
{
    AutoRefCount temp;
    temp.mpObject = pUFO;
    pUFO->AddRef();
    if (rVector.mpEnd < rVector.mpCapacity) {
        if (rVector.mpEnd != nullptr) {
            rVector.mpEnd->mpObject = pUFO;
            pUFO->AddRef();
        }
        ++rVector.mpEnd;
    } else {
        rVector.DoInsertPtr(rVector.mpEnd, temp);
    }
    if (temp.mpObject != nullptr)
        temp.mpObject->Release();
}

static int32_t VectorCount(const SPVector& rVector)
{
    return (int32_t)(rVector.mpEnd - rVector.mpBegin);
}

// ---------------------------------------------------------------------------
// 0x01008910 -- entry test: is the player about to meet an NPC UFO?
// ---------------------------------------------------------------------------
void SP::cSPSimulatorSpaceGame::GalaxyTestForIntercept()
{
    float fRadius = 10.0f;                      // 0x01473c70

    cTerrainSphere* pTerrain = NounManager()->GetCurrentTerrainSphere();
    bool bNotSpace = (pTerrain->IsSpace() == false);

    cProperty* pProperty = nullptr;
    ISimPropertyHost* pPropertyHost = gSimUniverse->mpPropertyHost;
    if (pPropertyHost != nullptr) {
        if (pPropertyHost->GetProperty(0x55e7dad, (void**)&pProperty) &&
            pProperty->mnType == 0xd) {
            fRadius = *pProperty->GetFloat();
        }
    }
    float fRadiusSq = fRadius * fRadius;

    StarManager();
    cRelationshipManager* pRelationships = RelationshipManager();
    cStarMap* pStarMap = GetStarMap0();
    cTerrainSphere* pTerrain2 = NounManager()->GetCurrentTerrainSphere();
    cPlayerInventory* pInventory = GetUFOSimulator()->GetPlayerInventory();
    Vec3* pPlayerPos = pInventory->mPosition.GetPosition();
    int32_t nPlayerEmpire = GetLivingUniverse()->mnPlayerEmpire;

    cGameData* pLocalCiv = GetLocalCiv();
    if (pLocalCiv != nullptr && pLocalCiv->GetAvatar() == nPlayerEmpire) {
        Vec3* pCity = (Vec3*)pLocalCiv->GetCities();
        float dz = pCity->z - pPlayerPos->z;
        float dy = pCity->y - pPlayerPos->y;
        float dx = pCity->x - pPlayerPos->x;
        float fDistSq = dz * dz + dy * dy + dx * dx;
        if (fDistSq < fRadiusSq)
            return;
    }

    SPVector* pCivs = &mpUniverse->mVisibleCivs;

    bool bHasUFO = false;
    if (pLocalCiv != nullptr) {
        cEmpire* pEmpire = StarManager()->GetEmpireByID(pLocalCiv->GetAvatar());
        if (pEmpire != nullptr && pEmpire->HasUFO())
            bHasUFO = true;
    }

    if (!bHasUFO) {
        for (AutoRefCount* pElem = pCivs->mpBegin; pElem != pCivs->mpEnd; ++pElem) {
            cGameData* pCiv = (cGameData*)pElem->mpObject;
            int32_t nEmpire = pCiv->GetAvatar();
            if (nEmpire != nPlayerEmpire &&
                !pRelationships->IsAllied(nEmpire, nPlayerEmpire)) {
                continue;
            }
            Vec3* pCity = (Vec3*)pCiv->GetCities();
            float dz = pCity->z - pPlayerPos->z;
            float dy = pCity->y - pPlayerPos->y;
            float dx = pCity->x - pPlayerPos->x;
            float fDistSq = dz * dz + dy * dy + dx * dx;
            if (fDistSq < gfCityInterceptScale * fRadiusSq)
                return;
        }
    }

    StarManager();
    int32_t nSelectedStar = (int32_t)GetSelectedStar();

    for (AutoRefCount* pElem = pCivs->mpBegin; pElem != pCivs->mpEnd; ++pElem) {
        cGameData* pCiv = (cGameData*)pElem->mpObject;
        int32_t nEmpire = pCiv->GetAvatar();
        if (nEmpire == nPlayerEmpire)
            continue;
        if (bNotSpace && nEmpire != nSelectedStar)
            continue;

        Vec3* pCity = (Vec3*)pCiv->GetCities();
        float dz = pCity->z - pPlayerPos->z;
        float dy = pCity->y - pPlayerPos->y;
        float dx = pCity->x - pPlayerPos->x;
        float fDistSq = dz * dz + dy * dy + dx * dx;
        if (fRadiusSq <= fDistSq)
            continue;

        cEmpire* pEmpire = StarManager()->GetEmpireByID(nEmpire);
        if (!pEmpire->HasUFO())
            continue;

        bool bFound = false;
        for (AutoRefCount* p = mNPC_UFOs.mpBegin; p != mNPC_UFOs.mpEnd; ++p) {
            if (((cSPGameDataUFO*)p->mpObject)->mpTarget == pCiv) {
                bFound = true;
                break;
            }
        }

        if (!bFound) {
            if (UFOFactory()->HasUFOTypeA(pEmpire->GetUFOKey(0))) {
                cSPGameDataUFO* pUFO = CreateUFOForSolarOrGalaxy(8, pEmpire);
                pUFO->mpTarget = pCiv;
                pUFO->SetTarget(pCiv);
                pUFO->PopToDestination();
                pUFO->mLocation.SetScale(0.5f);
                pUFO->SetDestination(pPlayerPos);
                InsertUFO(mNPC_UFOs, pUFO);

                if (GetStarMap1(2)->HasRecordVisuals()) {
                    cStarRecordVisual* pVisual =
                        GetStarMap3(pCiv->mnStarId, 0xb7735c3, 0)->GetRecordVisual();
                    if (pVisual == nullptr) {
                        pStarMap->CreateStarRecordVisual(pCiv, 0x70930c64, 0xb7735c3);
                        pVisual = GetStarMap3(pCiv->mnStarId, 0xb7735c3, 0)->GetRecordVisual();
                        ResourceKey visualKey;
                        visualKey.mnInstanceId = 0;
                        visualKey.mnGroupId = 0;
                        visualKey.mnTypeId = 1;
                        pVisual->SetFlags(1, &visualKey, 1);
                    }
                    if (!pVisual->IsVisible())
                        pVisual->SetVisible(false);
                }

                gSpaceTokenTranslator->mpEmpire = pEmpire;

                cCamInfo camInfo;
                camInfo.Init(pCiv->GetCities());
                GetTriggerMgr()->PostAction(0x5f4a3cdb, &camInfo, 0);

                cActionTarget actionTarget;
                actionTarget.Init(pStarMap, 0);
                GetTriggerMgr()->PostAction(0xc0976a1e, &actionTarget, 0);
                actionTarget.Destroy();

                ShowTutorialText("SPG_FirstEntryEnemyTerritory", 0x5079f9fa, 1);
            } else if (!UFOFactory()->HasUFOTypeB(pEmpire->GetUFOKey())) {
                ResourceKey key;
                key.mnInstanceId = 0;
                key.mnGroupId = 0;
                key.mnTypeId = 1;
                UFOFactory()->SetUFOTypeC(pEmpire->GetUFOKey(&key));
            }
        }

        pTerrain2->FUN_00c79f20(pCiv);
    }
}

// ---------------------------------------------------------------------------
// 0x01008e60 -- spawn an NPC UFO somewhere in the galaxy
// ---------------------------------------------------------------------------
void SP::cSPSimulatorSpaceGame::SpawnNPC_UFOs(float fChance)
{
    double fRoll = gRandom.RandomDoubleUniform();
    float fSpawnChance =
        1.0f - (float)exp((double)(fChance / gfNPCDivisor * -0.30103f));
    if (!(fSpawnChance > fRoll))
        return;

    GetLocalCivContext();

    SPVector* pCivs = &mpUniverse->mCivs;
    int32_t nCivCount = VectorCount(*pCivs);
    if (nCivCount <= 1)
        return;

    int32_t nStateSix = 0;
    for (AutoRefCount* p = mNPC_UFOs.mpBegin; p != mNPC_UFOs.mpEnd; ++p) {
        if (((cSPGameDataUFO*)p->mpObject)->mnState == 6)
            ++nStateSix;
    }

    int32_t nLimit = (int32_t)((float)nCivCount * gfNPCCountScale);
    if (nLimit >= gnMaxNPCUFOs)
        nLimit = gnMaxNPCUFOs;
    if (nLimit < 2)
        nLimit = 1;
    if (nStateSix >= nLimit)
        return;

    cGameData* pCiv =
        (cGameData*)pCivs->mpBegin[gRandom.RandomUint32Uniform((uint32_t)nCivCount)].mpObject;
    cEmpire* pEmpire = StarManager()->GetEmpireByID(pCiv->GetAvatar());
    if (pEmpire == nullptr)
        return;

    if (UFOFactory()->HasUFOTypeA(pEmpire->GetUFOKey(0))) {
        StarRecordFilter filter;
        filter.mnFlags = 0x1ffd;
        filter.mnTypeMask = 0x20;
        filter.mnField08 = 0;
        filter.mnField0c = 0;
        filter.mnField10 = 0;
        filter.mnField14 = 0;
        filter.mnField18 = 0;
        filter.mfMinValue = -1.0f;
        filter.mfZero = 0.0f;
        filter.mfScale = gfNPCMinChance;
        filter.mnField28 = 0;

        SPVector records;
        records.mpBegin = nullptr;
        records.mpEnd = nullptr;
        records.mpCapacity = nullptr;

        pCiv->GetCities(&filter);
        StarManager()->GetStarRecords(&records);

        cGameData* pRecord = nullptr;
        bool bFound = false;
        int32_t nRecords = VectorCount(records);
        while (nRecords > 0 && !bFound) {
            uint32_t nIndex = gRandom.RandomUint32Uniform((uint32_t)nRecords);
            pRecord = (cGameData*)records.mpBegin[nIndex].mpObject;
            if (pRecord != pCiv) {
                if (pRecord->GetAvatar() == pCiv->GetAvatar()) {
                    bFound = true;
                } else {
                    cEmpire* pEmpireA = StarManager()->GetEmpireByID(pCiv->GetAvatar());
                    cEmpire* pEmpireB = StarManager()->GetEmpireByID(pRecord->GetAvatar());
                    if (RelationshipManager()->AreAtWar(pEmpireB, pEmpireA))
                        bFound = true;
                }
            }
            if (!bFound) {
                AutoRefCount* pSlot = &records.mpBegin[nIndex];
                IRefCount* pOld = pSlot->mpObject;
                IRefCount* pLast = (records.mpEnd - 1)->mpObject;
                if (pLast != pOld) {
                    if (pLast != nullptr)
                        pLast->AddRef();
                    pSlot->mpObject = pLast;
                    if (pOld != nullptr)
                        pOld->Release();
                }
                --records.mpEnd;
                if (records.mpEnd->mpObject != nullptr)
                    records.mpEnd->mpObject->Release();
                nRecords = VectorCount(records);
            }
        }

        if (bFound && pRecord != nullptr) {
            cSPGameDataUFO* pUFO = CreateUFOForSolarOrGalaxy(6, pEmpire);
            pUFO->SetTarget(pCiv);
            pUFO->PopToDestination();
            pUFO->mLocation.SetScale(0.5f);
            pUFO->SetTarget(pRecord);
            InsertUFO(mNPC_UFOs, pUFO);
        }
        records.Destroy();
    } else if (!UFOFactory()->HasUFOTypeB(pEmpire->GetUFOKey())) {
        ResourceKey key;
        key.mnInstanceId = 0;
        key.mnGroupId = 0;
        key.mnTypeId = 2;
        UFOFactory()->SetUFOTypeC(pEmpire->GetUFOKey(&key));
    }
}

// ---------------------------------------------------------------------------
// 0x010091d0 -- spawn an NPC UFO inside the current solar system
// ---------------------------------------------------------------------------
void SP::cSPSimulatorSpaceGame::SolarSystemSpawnNPC_UFOs(float fChance)
{
    int32_t nUFOs = VectorCount(mNPC_UFOs);
    for (int32_t i = 0; i < nUFOs; ++i) {
        if (((cSPGameDataUFO*)mNPC_UFOs.mpBegin[i].mpObject)->mnState == 6)
            return;
    }

    SPVector* pRecords = GetLocalCivContext()->mRecords.GetStarRecords();

    if (pRecords->mpBegin == pRecords->mpEnd)
        return;

    double fRoll = gRandom.RandomDoubleUniform();
    float fSpawnChance =
        1.0f - (float)exp((double)(fChance / gfSolarNPCDivisor * -0.30103f));
    if (!(fSpawnChance > fRoll))
        return;

    SPVector* pCivs = &mpUniverse->mCivs;
    int32_t nCivCount = VectorCount(*pCivs);
    if (nCivCount <= 1)
        return;

    cGameData* pCiv =
        (cGameData*)pCivs->mpBegin[gRandom.RandomUint32Uniform((uint32_t)nCivCount)].mpObject;
    if (pCiv->GetAvatar() == GetPlayerEmpireID())
        return;

    cGameData* pRecord = nullptr;
    int32_t nTries = 9;
    int32_t nRecords = VectorCount(*pRecords);
    do {
        uint32_t nIndex = gRandom.RandomUint32Uniform((uint32_t)nRecords);
        pRecord = (cGameData*)pRecords->mpBegin[nIndex].mpObject;
        if (pRecord->mnField28 != 0 && !pRecord->IsColonizable())
            break;
        nTries = nTries - 1;
    } while (nTries > 0);

    if (pRecord == nullptr)
        return;
    if (pRecord->mnField28 == 0 || pRecord->IsColonizable())
        return;

    cPlanet* pPlanet = nullptr;
    StarManager()->GetOrActivatePlanet(pRecord, &pPlanet);

    cEmpire* pEmpire = StarManager()->GetEmpireByID(pCiv->GetAvatar());
    if (UFOFactory()->HasUFOTypeA(pEmpire->GetUFOKey(0))) {
        cSPGameDataUFO* pUFO = CreateUFOForSolarOrGalaxy(6, pEmpire);
        Vec3 vecPos;
        GetAmbushOffset(&vecPos);
        vecPos.x = gfUFOAmbushScale * vecPos.x;
        vecPos.y = gfUFOAmbushScale * vecPos.y;
        vecPos.z = gfUFOAmbushScale * 0.0f;
        pUFO->SetLocalPosition(&vecPos);
        pUFO->SetDestination(pPlanet);
        pUFO->mVec6bc = pUFO->mVec718;
        InsertUFO(mNPC_UFOs, pUFO);
    } else if (!UFOFactory()->HasUFOTypeB(pEmpire->GetUFOKey(nullptr))) {
        ResourceKey key;
        key.mnInstanceId = 0;
        key.mnGroupId = 0;
        key.mnTypeId = 1;
        UFOFactory()->SetUFOTypeC(pEmpire->GetUFOKey(&key));
    }

    if (pPlanet != nullptr)
        pPlanet->ReleaseObject();
}

// ---------------------------------------------------------------------------
// 0x01009470 -- drop NPC UFOs (optionally collecting them into a list first)
// ---------------------------------------------------------------------------
void SP::cSPSimulatorSpaceGame::DestroyNPC_UFOs(char bParam2, char bParam3, int32_t nFlags)
{
    SPVector vecDestroy;
    vecDestroy.mpBegin = nullptr;
    vecDestroy.mpEnd = nullptr;
    vecDestroy.mpCapacity = nullptr;

    for (AutoRefCount* pElem = mNPC_UFOs.mpBegin; pElem != mNPC_UFOs.mpEnd; ++pElem) {
        cSPGameDataUFO* pUFO = (cSPGameDataUFO*)pElem->mpObject;

        if (pUFO->mnState == 3) {
            if (bParam3 == 0) {
                DestroyCreature(pUFO, nFlags);
                continue;
            }
        } else if (pUFO->mnState == 8) {
            if (bParam2 == 0) {
                if (pUFO->mpTarget != nullptr) {
                    int32_t nStarId = pUFO->mpTarget->mnStarId;
                    GetStarMap4(nStarId, 0xb7735c3, 0, 1)->RemoveVisual();
                }
                DestroyCreature(pUFO, nFlags);
                continue;
            }
        } else {
            DestroyCreature(pUFO, nFlags);
            continue;
        }

        InsertUFO(vecDestroy, pUFO);
    }

    mNPC_UFOs.DestroyListedUFOs(&vecDestroy);

    for (AutoRefCount* p = vecDestroy.mpBegin; p < vecDestroy.mpEnd; ++p) {
        if (p->mpObject != nullptr)
            p->mpObject->Release();
    }
    vecDestroy.Destroy();
}

// ---------------------------------------------------------------------------
// 0x010095e0 -- start an ambush against the current held-back UFO list
// ---------------------------------------------------------------------------
void SP::cSPSimulatorSpaceGame::StartAmbush()
{
    cGameData* pCiv = GetLocalCiv();

    ResourceKey modelKey;
    modelKey.mnInstanceId = 0;
    modelKey.mnGroupId = 0;
    modelKey.mnTypeId = 0;

    GetAmbushContext()->mUFOTypeOwner.GetModelKey(&modelKey);

    float fRadius = 10.0f;
    cProperty* pProperty = nullptr;
    ISimPropertyHost* pPropertyHost = gSimUniverse->mpPropertyHost;
    if (pPropertyHost != nullptr &&
        pPropertyHost->GetProperty(0x55e7dad, (void**)&pProperty) &&
        pProperty->mnType == 0xd) {
        fRadius = *pProperty->GetFloat();
    }

    StarRecordFilter filter;
    filter.mnFlags = 0x1ffd;
    filter.mnTypeMask = 0x1f;
    filter.mnField08 = 0;
    filter.mnField0c = 0;
    filter.mnField10 = 0;
    filter.mnField14 = 0;
    filter.mnField18 = 0;
    filter.mfMinValue = -1.0f;
    filter.mfZero = 0.0f;
    filter.mfScale = fRadius;
    filter.mnField28 = 0;

    SPVector records;
    records.mpBegin = nullptr;
    records.mpEnd = nullptr;
    records.mpCapacity = nullptr;

    pCiv->GetCities(&filter);
    StarManager()->GetStarRecords(&records);

    ShuffleStarRecords(records.mpBegin, records.mpEnd, &gRandom);

    int32_t nSpawned = 0;
    cGameData* pTarget = pCiv;
    while (nSpawned < gnAmbushUFOCount) {
        if (nSpawned > 0) {
            if (records.mpBegin == records.mpEnd)
                break;
            pTarget = (cGameData*)(records.mpEnd - 1)->mpObject;
            --records.mpEnd;
            if (records.mpEnd->mpObject != nullptr)
                records.mpEnd->mpObject->Release();
        }

        cSPGameDataUFO* pUFO = CreateUFOForSolarOrGalaxy(8, nullptr);
        pUFO->SetDesiredModel(modelKey, 1);
        pUFO->mpTarget = pTarget;
        InsertUFO(mNPC_UFOs, pUFO);
        ++nSpawned;
        pTarget = pCiv;
    }

    records.Destroy();
}

// ---------------------------------------------------------------------------
// 0x010097f0 -- SETI ambush entry point
// ---------------------------------------------------------------------------
void SP::cSPSimulatorSpaceGame::StartSetiAmbush()
{
    StartAmbush();
    FUN_01008270(0);
    FUN_010077e0();
}
