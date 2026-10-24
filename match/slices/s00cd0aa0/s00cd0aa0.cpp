// s00cd0aa0 -- SP::cTribeInputStrategy::Init.  The tribe-cursor strategy is
// re-initialised once per cursor: the cursor id picked by GetTribeCursorId
// selects one of ~30 preparation steps (mode switch, mission hand-off,
// ShowSelection ring, space/tribe editor setup, ...) through a 0x30-entry
// switch.  The reconstruction below follows the retail control flow case by
// case; the jump table itself lives in the middle of the function in retail
// and is emitted by the compiler from the dense switch.
//
//   0x00cd0aa0 cTribeInputStrategy::Init(int*)
#include "types.h"

#define nullptr 0

// ---------------------------------------------------------------------------
// small engine types
// ---------------------------------------------------------------------------

struct Vector3 {
    float x;
    float y;
    float z;
};

// the property/variant flag word the temporary Variant carries at +0x0c
namespace EA {
class Variant {
public:
    void Destruct(bool bRelease);                // 0x0093db80
    void* BuildVectorVariant(const Vector3* pValue);  // 0x00b19970

    uint8_t m_pad000[0x0c];                      // +0x00
    uint32_t m_nFlags;                           // +0x0c
};
}

// ---------------------------------------------------------------------------
// the simulator nouns the lookups return
// ---------------------------------------------------------------------------

// the object the owner hands out for key 0x17f243b: the selected noun
class cNounTarget {
public:
    virtual void N00();  virtual void N04();  virtual void N08();  virtual void N0c();
    virtual void N10();  virtual void N14();  virtual void N18();  virtual void N1c();
    virtual int GetKindV20();                    // +0x20
    virtual void N24();
    virtual void N28();
    virtual Vector3* GetPositionV2c();           // +0x2c
};

// the object the owner hands out for key 0x1186577: the cursor's anchor data
class cTribeCursorData {
public:
    virtual void T00();  virtual void T04();  virtual void T08();  virtual void T0c();
    virtual void T10();  virtual void T14();  virtual void T18();  virtual void T1c();
    virtual void T20();  virtual void T24();  virtual void T28();
    virtual Vector3* GetAnchorV2c();             // +0x2c
    virtual void T30();
    virtual float GetRadiusV34();                // +0x34

    uint8_t m_pad038[0x77 - 0x38];               // +0x38
    uint8_t m_bFlags77;                          // +0x77
};

// a simulator noun a key lookup hands out (only the reached slot is named)
class cSimNoun {
public:
    virtual void K00();  virtual void K04();  virtual void K08();  virtual void K0c();
    virtual void K10();  virtual void K14();  virtual void K18();  virtual void K1c();
    virtual void K20();  virtual void K24();  virtual void K28();  virtual void K2c();
    virtual void K30();  virtual void K34();  virtual void K38();  virtual void K3c();
    virtual void K40();  virtual void K44();  virtual void K48();  virtual void K4c();
    virtual void K50();  virtual void K54();
    virtual void* GetMissionV58();               // +0x58
};

class cTribe;

// a creature citizen
class cSPCreatureCitizen {
public:
    cTribe* GetTribe();                          // 0x00c22f50
};

// the object the input strategy is initialised for
class cSPUIInputOwner {
public:
    virtual void O00();
    virtual void O04();
    virtual void O08();
    virtual void* GetV0c(uint32_t nKey);         // +0x0c
};

// a tribe
class cTribe {
public:
    virtual void C00();  virtual void C04();  virtual void C08();  virtual void C0c();
    virtual void C10();  virtual void C14();  virtual void C18();  virtual void C1c();
    virtual void C20();  virtual void C24();  virtual void C28();  virtual void C2c();
    virtual void C30();  virtual void C34();  virtual void C38();  virtual void C3c();
    virtual void C40();  virtual void C44();  virtual void C48();  virtual void C4c();
    virtual void C50();  virtual void C54();  virtual void C58();  virtual void C5c();
    virtual void C60();  virtual void C64();  virtual void C68();  virtual void C6c();
    virtual void C70();  virtual void C74();  virtual void C78();  virtual void C7c();
    virtual void C80();  virtual void C84();  virtual void C88();  virtual void C8c();
    virtual void C90();  virtual void C94();  virtual void C98();  virtual void C9c();
    virtual void Ca0();
    virtual int GetResourceCountA4();            // +0xa4
};

// a spatial object in the terrain cursor's list
class cSpatialObject {
public:
    virtual void S00();  virtual void S04();  virtual void S08();  virtual void S0c();
    virtual void S10();  virtual void S14();  virtual void S18();  virtual void S1c();
    virtual void S20();  virtual void S24();  virtual void S28();  virtual void S2c();
    virtual void S30();  virtual void S34();  virtual void S38();  virtual void S3c();
    virtual void S40();  virtual void S44();  virtual void S48();  virtual void S4c();
    virtual void S50();  virtual void S54();  virtual void S58();  virtual void S5c();
    virtual void S60();  virtual void S64();  virtual void S68();  virtual void S6c();
    virtual void S70();  virtual void S74();  virtual void S78();  virtual void S7c();
    virtual void S80();  virtual void S84();  virtual void S88();  virtual void S8c();
    virtual void S90();  virtual void S94();  virtual void S98();  virtual void S9c();
    virtual void Sa0();  virtual void Sa4();  virtual void Sa8();  virtual void Sac();
    virtual void Sb0();  virtual void Sb4();
    virtual void Sb8();
    virtual void Sbc();
    virtual void Sc0();                          // +0xc0
    virtual void ReleaseSc4();                   // +0xc4
};

// the sub-object a spatial object carries at +0x34
class cSpatialSubObject {
public:
    uint8_t m_pad000[0x12c];                     // +0x000
    int32_t m_nKind12c;                          // +0x12c
};

// the terrain cursor's object list (inline-storage eastl vector)
struct cSpatialObjectList {
    cSpatialObject** m_pBegin;                   // +0x00
    cSpatialObject** m_pEnd;                     // +0x04
    cSpatialObject** m_pCapacity;                // +0x08
    void* m_pStorage[0x1e];                      // +0x0c

    void Destruct();                             // 0x00ad92d0
    void Reserve(int32_t nCount);                // 0x00d01790
    void Append(cSpatialObject** pItem);         // 0x00afc470
};

// a reference-counted spatial object handle
class cAutoObjectRef {
public:
    void Assign(cSpatialObject* pObject);        // 0x00ad72e0

    cSpatialObject* m_pObject;                   // +0x00
};

// the terrain cursor the game exposes
class cGameTerrainCursor {
public:
    virtual void G00();  virtual void G04();  virtual void G08();  virtual void G0c();
    virtual void G10();  virtual void G14();  virtual void G18();  virtual void G1c();
    virtual void G20();  virtual void G24();  virtual void G28();  virtual void G2c();
    virtual void G30();  virtual void G34();  virtual void G38();  virtual void G3c();
    virtual void G40();  virtual void G44();  virtual void G48();  virtual void G4c();
    virtual void G50();  virtual void G54();  virtual void G58();
    virtual void GetObjectsV5c(cSpatialObjectList* pList);  // +0x5c
};

// the noun manager
class cGameNounManager {
public:
    cTribe* GetPlayerTribe();                    // 0x00bfc5f0

    class cTerrainSphere* GetCurrentTerrainSphere(uint32_t nKey);  // 0x00f67d90
};

class cTerrainSphere {
public:
    void Refresh();                              // 0x00c77bf0
};

// a planet
class cPlanet {
public:
    uint8_t IsMarketableAt(void* pPlace);        // 0x00c74400
    void MarkPlaceVisited(void* pPlace);         // 0x00c74470
};

// the cursor hit a terrain probe reports
struct cTerrainHit {
    Vector3 m_vNormal;                           // +0x00
    uint8_t m_pad00c[0x24];                      // +0x0c
};

// the object SP::PlanetModel returns and FUN_00b81630 finishes
class cPlanetSurface {
public:
    void Build();                                // 0x00b81630
};

// the object that builds the cursor hit from the default offset
class cTerrainCursorBuilder {
public:
    virtual void B00();  virtual void B04();  virtual void B08();  virtual void B0c();
    virtual void B10();  virtual void B14();  virtual void B18();  virtual void B1c();
    virtual void B20();  virtual void B24();  virtual void B28();  virtual void B2c();
    virtual void B30();  virtual void B34();
    virtual void BuildHit(cTerrainHit* pHit, int32_t nFlags, Vector3 vOffset);  // +0x38
};

// the mission the tribe-mode strategy switches to
class cTribeModeStrategy {
public:
    void SetMission(void* pMission);             // 0x00cd3bf0
};

// the event object FUN_0067cac0 hands out
class cUIEvent {
public:
    void Fire(uint32_t nKey);                    // 0x00cd0830 (see cSPUIEventObject below)
};

class cSPUIEventObject {
public:
    virtual void E00();  virtual void E04();  virtual void E08();  virtual void E0c();
    virtual void E10();
    void Post(uint32_t nKey);                    // 0x00cd0830
};

// the game state the strategy writes the pending resource amount into
class cGameState {
public:
    uint8_t m_pad000[0x0c];                      // +0x00
    int32_t m_nPendingAmount;                    // +0x0c
};

// ---------------------------------------------------------------------------
// namespace SP: the strategy under test
// ---------------------------------------------------------------------------

namespace SP {

class cTribeInputStrategy {
public:
    // the tribe cursor this strategy serves (0 when unavailable)
    int32_t GetTribeCursorId(cSPUIInputOwner* pOwner, int32_t nFlags);  // 0x00ccefb0

    // select the tribe mode and its target noun
    void SetTribeMode(int32_t nMode, void* pTarget, void* pExtra);  // 0x00cd07c0

    // attach the noun whose data the mode reads
    void SetModeNoun(void* pNoun);               // 0x00cd0830

    // switch the space cursor
    void SetSpaceCursor(int32_t nCursor);        // 0x00ccfc20

    // place the cursor ring on a terrain position
    void PlaceCursor(const void* pHit);          // 0x00cd02d0

    void Init(cSPUIInputOwner* pOwner);          // 0x00cd0aa0

    uint8_t m_pad000[0x58];                      // +0x00 .. +0x57 (base strategy)
};

}

// ---------------------------------------------------------------------------
// imports
// ---------------------------------------------------------------------------

cGameNounManager* __cdecl NounManager();         // 0x00b3d300
cGameTerrainCursor* __cdecl SP_GetGameTerrainCursor();  // 0x00b30d70
cPlanet* __cdecl SP_GetActivePlanet();           // 0x01021260
cTerrainCursorBuilder* __cdecl FUN_00b3d240();   // 0x00b3d240
cPlanetSurface* __stdcall SP_PlanetModel(Vector3* pOut, const Vector3* pDir);  // 0x00b3d350
float __cdecl SP_GetPropertyFloat(void* pOwner, uint32_t nKey, float fDef);  // 0x004e1c70
void* __cdecl FUN_00ac80d0(void* pOwner, uint32_t nKey);   // 0x00ac80d0
void* __cdecl FUN_00ac7880(uint32_t nId);        // 0x00ac7880
void* __cdecl FUN_00c9d9e0();                    // 0x00c9d9e0
void* __cdecl FUN_00c0c380(void* pNoun);         // 0x00c0c380
void* __cdecl FUN_00c22df0(void* pOwner);        // 0x00c22df0
int32_t __cdecl FUN_00c22dc0(void* pObject);     // 0x00c22dc0
cSpatialObject* __cdecl FUN_00c9f000(void* pEntry);        // 0x00c9f000
cSpatialSubObject* __cdecl FUN_00cee330(void* pObject);    // 0x00cee330
cTribeModeStrategy* __stdcall FUN_00cd3440(void* pMission);  // 0x00cd3440
void* __cdecl FUN_00cce9b0(cSpatialObjectList* pList, int32_t nMode, void* pOwner, int32_t nFlags);  // 0x00cce9b0
cSPUIEventObject* __cdecl FUN_0067cac0(uint32_t nKey);     // 0x0067cac0
void* __cdecl FUN_00c04590(void* pObject);       // 0x00c04590
void* __cdecl FUN_00b3d4c0(void* pObject, int32_t nA, int32_t nB);  // 0x00b3d4c0
int32_t __cdecl FUN_00ba3f90(void* pObject);     // 0x00ba3f90
void* __cdecl FUN_00b706a0(void* pObject);       // 0x00b706a0
void* __cdecl FUN_00c0c1a0(void* pObject);       // 0x00c0c1a0
int32_t __cdecl SP_GetTutorialToolPrice(void* pTool, uint32_t nKey, int32_t nCount);  // 0x004e1c30
int32_t __cdecl GetRecorderState();              // 0x00435e90
void __cdecl SP_KillSetiEffects(const char* pName, int32_t nState);  // 0x00435ed0
bool __cdecl SP_DomesticateAnimal(void* pAnimal, cTribe* pTribe);    // 0x00db5e80
void __cdecl ShowSelection(void* pTarget, uint32_t nKey, int32_t nMode, float fValue, int32_t nFlags);  // 0x00ccece0

// engine globals
extern Vector3 gDefaultCursorOffset;             // 0x0169b1c8
extern void* gGamePropertyOwner;                 // 0x0158128c
extern cGameState* gGameState;                   // 0x0169b41c
extern float gDefaultGatherRadius;               // 0x01473c70

// resource keys the cursor strategy reacts to
static const uint32_t kNounKey = 0x017f243b;
static const uint32_t kCursorDataKey = 0x01186577;

// ---------------------------------------------------------------------------
// the tribe-cursor initialisation
// ---------------------------------------------------------------------------

// @ 0x00cd0aa0
void SP::cTribeInputStrategy::Init(cSPUIInputOwner* pOwner)
{
    int32_t nCursorId = GetTribeCursorId(pOwner, 0);
    if (nCursorId == 0)
        return;

    NounManager()->GetPlayerTribe();

    cNounTarget* pNoun = nullptr;
    cTribeCursorData* pCursorData = nullptr;
    if (pOwner != nullptr) {
        pNoun = (cNounTarget*)pOwner->GetV0c(kNounKey);
        pCursorData = (cTribeCursorData*)pOwner->GetV0c(kCursorDataKey);
    }

    switch (nCursorId) {
    case 1:
    {
        cTerrainCursorBuilder* pBuilder = FUN_00b3d240();
        Vector3 vOffset;
        vOffset.x = gDefaultCursorOffset.x;
        vOffset.y = gDefaultCursorOffset.y;
        vOffset.z = gDefaultCursorOffset.z;

        cTerrainHit hit;
        pBuilder->BuildHit(&hit, 0, vOffset);

        Vector3 vPosition;
        SP_PlanetModel(&vPosition, &hit.m_vNormal)->Build();
        PlaceCursor(&vPosition);
        return;
    }

    case 9:
        SetTribeMode(0x18, pOwner, 0);
        return;

    case 0xa:
        SetTribeMode(7, pOwner, 0);
        return;

    case 0xb:
        SetTribeMode(0xa, pOwner, 0);
        NounManager()->GetCurrentTerrainSphere(0x055e9383)->Refresh();
        return;

    case 0xc:
    {
        cSimNoun* pNounLookup = (cSimNoun*)FUN_00ac80d0(pNoun, 0x01e4daae);
        FUN_00ac80d0(pNoun, 0x018c8f0c);
        void* pMission;
        if (pNounLookup == nullptr)
            pMission = FUN_00c9d9e0();
        else
            pMission = pNounLookup->GetMissionV58();
        FUN_00cd3440(pMission)->SetMission(pMission);
        SetTribeMode(0xf, pOwner, 0);
        return;
    }

    case 0xe:
    {
        float fThreshold = SP_GetPropertyFloat(gGamePropertyOwner, 0xfd444753,
                                               gDefaultGatherRadius);
        int32_t nThreshold = (int32_t)fThreshold;

        NounManager()->GetPlayerTribe();
        if (NounManager()->GetPlayerTribe()->GetResourceCountA4() < nThreshold) {
            bool bFound = false;
            cSpatialObjectList list;
            list.m_pBegin = (cSpatialObject**)list.m_pStorage;
            list.m_pEnd = (cSpatialObject**)list.m_pStorage;
            list.m_pCapacity = (cSpatialObject**)list.m_pStorage;

            SP_GetGameTerrainCursor()->GetObjectsV5c(&list);
            cSpatialObject** pCur = list.m_pBegin;
            while (pCur != list.m_pEnd) {
                cSpatialObject* pObject = FUN_00c9f000(*pCur);
                if (pObject != nullptr) {
                    void* pSub = (uint8_t*)pObject + 0x34;
                    if (FUN_00cee330(pSub) != nullptr
                        && FUN_00cee330(pSub)->m_nKind12c == 5) {
                        bFound = true;
                        break;
                    }
                }
                pCur++;
            }

            gGameState->m_nPendingAmount = nThreshold;
            FUN_0067cac0(0xa066f949)->Post(0xa066f949);
            list.Destruct();
            if (!bFound)
                return;
        }

        Vector3 vAnchor;
        vAnchor = *pCursorData->GetAnchorV2c();

        int32_t nKind = pNoun->GetKindV20();
        cTribe* pTribe = nullptr;
        if (nKind == 0x01e4daae) {
            pTribe = (cTribe*)((cSimNoun*)FUN_00ac80d0(pNoun, 0x01e4daae))
                         ->GetMissionV58();
        } else if (nKind == 0x018c431c) {
            void* pObj = FUN_00ac80d0(pNoun, 0x018c431c);
            void* pCreature = FUN_00ac7880(*(uint32_t*)((uint8_t*)pObj + 0x128));
            cTribeCursorData* pData =
                (cTribeCursorData*)*(uint32_t*)((uint8_t*)pCreature + 0x260);
            Vector3* pPos = pData->GetAnchorV2c();
            vAnchor.x = pPos->x;
            vAnchor.y = pPos->y;
            vAnchor.z = pPos->z;
            pTribe = (cTribe*)pCreature;
        } else if (nKind == 0x018eb4b7) {
            pTribe = ((cSPCreatureCitizen*)FUN_00ac80d0(pNoun, 0x018eb4b7))
                         ->GetTribe();
        } else if (nKind == 0x0629bafe) {
            void* pObj = FUN_00ac80d0(pNoun, 0x0629bafe);
            pTribe = (cTribe*)*(uint32_t*)((uint8_t*)pObj + 0x10c);
        }

        FUN_00cd3440(pTribe)->SetMission(pTribe);
        SetTribeMode(9, pTribe, 0);
        float fRadius = pCursorData->GetRadiusV34();
        ShowSelection(&vAnchor, 0x4ae30884, 0, fRadius, 1);
        return;
    }

    case 0xf:
        FUN_0067cac0(0x30d20036)->Post(0x30d20036);
        return;

    case 0x10:
    {
        float fThreshold = SP_GetPropertyFloat(gGamePropertyOwner, 0xfd444753,
                                               gDefaultGatherRadius);
        NounManager()->GetPlayerTribe();
        if (NounManager()->GetPlayerTribe()->GetResourceCountA4()
            < (int32_t)fThreshold) {
            gGameState->m_nPendingAmount = (int32_t)fThreshold;
            FUN_0067cac0(0xa066f949)->Post(0xa066f949);
            return;
        }

        Vector3 vAnchor;
        vAnchor = *pCursorData->GetAnchorV2c();

        void* pCreature = FUN_00c0c380(pNoun);
        if (pCreature == nullptr)
            return;

        cTribe* pTribe = ((cSPCreatureCitizen*)pCreature)->GetTribe();
        FUN_00cd3440(pTribe)->SetMission(pTribe);
        SetTribeMode(9, pTribe, 0);
        float fRadius = pCursorData->GetRadiusV34();
        ShowSelection(&vAnchor, 0x4ae30884, 0, fRadius, 1);
        return;
    }

    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
        SetModeNoun(FUN_00ac80d0(pNoun, 0x018c8f0c));
        return;

    case 0x1b:
        SetTribeMode(0xe, pOwner, 0);
        {
            float fRadius = pCursorData->GetRadiusV34();
            ShowSelection(pCursorData->GetAnchorV2c(), 0x4ae30884, 0, fRadius, 1);
        }
        return;

    case 0x1c:
    case 0x1d:
        SetTribeMode(0x1b, pOwner, 0);
        {
            float fRadius = pCursorData->GetRadiusV34();
            ShowSelection(pCursorData->GetAnchorV2c(), 0x4ae30884, 0, fRadius, 1);
        }
        return;

    case 0x1e:
    case 0x1f:
    case 0x20:
        SetTribeMode(0, pOwner, 0);
        {
            float fRadius = pCursorData->GetRadiusV34();
            ShowSelection(pCursorData->GetAnchorV2c(), 0x4ae30884, 0, fRadius, 1);
        }
        return;

    case 0x21:
    {
        void* pPlace = FUN_00ac80d0(pNoun, 0x0629bafe);
        void* pHolder = FUN_00ac80d0(pNoun, 0x018c431c);
        void* pTarget;
        if (pHolder == nullptr) {
            pTarget = *(void**)((uint8_t*)pPlace + 0x10c);
        } else {
            void* pCreature = FUN_00ac7880(*(uint32_t*)((uint8_t*)pHolder + 0x128));
            pTarget = *(void**)((uint8_t*)pCreature + 0x260);
        }
        SetTribeMode(8, pTarget, 0);
        {
            float fRadius = pCursorData->GetRadiusV34();
            cTribeCursorData* pAnchorData =
                (cTribeCursorData*)((uint8_t*)pPlace + 0x34);
            ShowSelection(pAnchorData->GetAnchorV2c(), 0x4ae30884, 0, fRadius, 1);
        }
        return;
    }

    case 0x22:
    {
        Vector3 vPosition;
        SP_PlanetModel(&vPosition, pCursorData->GetAnchorV2c())->Build();

        EA::Variant variant;
        void* pSelection = variant.BuildVectorVariant(&vPosition);
        SetTribeMode(1, 0, pSelection);
        if (variant.m_nFlags & 4)
            variant.Destruct(false);

        ShowSelection(&vPosition, 0xbadb68ea, 0, 1.0f, 0);
        NounManager()->GetCurrentTerrainSphere(0x055e9382)->Refresh();
        return;
    }

    case 0x23:
        SetTribeMode(0xd, pOwner, 0);
        {
            float fRadius = pCursorData->GetRadiusV34();
            ShowSelection(pCursorData->GetAnchorV2c(), 0x4ae30884, 0, fRadius, 1);
        }
        return;

    case 0x24:
        SetTribeMode(2, FUN_00ac80d0(pNoun, 0x02c9cc91), 0);
        NounManager()->GetCurrentTerrainSphere(0x055e9384)->Refresh();
        return;

    case 0x25:
        SetTribeMode(2, FUN_00c22df0(pOwner), 0);
        NounManager()->GetCurrentTerrainSphere(0x055e9384)->Refresh();
        return;

    case 0x27:
        SetTribeMode(0x1a, pOwner, 0);
        return;

    case 0x28:
    {
        cSpatialObjectList candidates;
        candidates.m_pBegin = (cSpatialObject**)candidates.m_pStorage;
        candidates.m_pEnd = (cSpatialObject**)candidates.m_pStorage;
        candidates.m_pCapacity = (cSpatialObject**)candidates.m_pStorage;
        SP_GetGameTerrainCursor()->GetObjectsV5c(&candidates);

        cSpatialObjectList selected;
        selected.m_pBegin = (cSpatialObject**)selected.m_pStorage;
        selected.m_pEnd = (cSpatialObject**)selected.m_pStorage;
        selected.m_pCapacity = (cSpatialObject**)selected.m_pStorage;
        selected.Reserve((int32_t)(candidates.m_pEnd - candidates.m_pBegin));

        cSpatialObject** pCur = candidates.m_pBegin;
        while (pCur != candidates.m_pEnd) {
            cSpatialObject* pObject = FUN_00c9f000(*pCur);
            if (pObject != nullptr && pObject != (cSpatialObject*)pNoun
                && FUN_00c22dc0(pObject) == 9) {
                cAutoObjectRef ref;
                ref.Assign((cSpatialObject*)((uint8_t*)pObject + 0xc0));
                selected.Append((cSpatialObject**)&ref);
                if (ref.m_pObject != nullptr)
                    ref.m_pObject->ReleaseSc4();
            }
            pCur++;
        }

        if (selected.m_pBegin != selected.m_pEnd) {
            if (FUN_00cce9b0(&selected, 5, pOwner, 0) == 0) {
                SetSpaceCursor(5);
                SP_KillSetiEffects((const char*)0x0cc04a90, GetRecorderState());
            }

            uint8_t bFlag = pCursorData->m_bFlags77;
            float fRadius = pCursorData->GetRadiusV34();
            uint32_t nKey = (bFlag != 0) ? 0x4ae30884 : 0x742deb5b;
            ShowSelection(pCursorData->GetAnchorV2c(), nKey, 0, fRadius, 1);
        }

        selected.Destruct();
        candidates.Destruct();
        return;
    }

    case 0x29:
    {
        void* pAnimal = FUN_00ac80d0(pNoun, 0x018eb45e);
        void* pInfo = FUN_00c04590(pAnimal);
        if (*(int32_t*)((uint8_t*)pInfo + 0x15c) == 7)
            return;

        void* pTameState = FUN_00b3d4c0((uint8_t*)pAnimal + 0xb28, 0, 0);
        if (FUN_00ba3f90(pTameState) == 6) {
            cTribe* pTribe = NounManager()->GetPlayerTribe();
            if (!SP_DomesticateAnimal(pAnimal, pTribe))
                return;
            SetTribeMode(0x19, pAnimal, 0);
            return;
        }

        FUN_00cd3440((void*)0x84f037b0)->SetMission((void*)0x84f037b0);
        FUN_00b706a0((void*)0x84f037b0);

        int32_t nPrice = 5;
        void* pTool = FUN_00c0c1a0(pAnimal);
        if (pTool != nullptr)
            nPrice = SP_GetTutorialToolPrice(*(void**)((uint8_t*)pTool + 0x43c),
                                            0xeb69140e, 5);

        if (NounManager()->GetPlayerTribe()->GetResourceCountA4() < (int32_t)nPrice) {
            gGameState->m_nPendingAmount = nPrice;
            FUN_0067cac0(0x6f902625)->Post(0x6f902625);
            return;
        }
        SetTribeMode(0x14, pAnimal, 0);
        return;
    }

    case 0x2a:
        FUN_0067cac0(0x3b052a35)->Post(0x3b052a35);
        // falls through
    case 7:
        SetSpaceCursor(0x29a);
        return;

    case 0x2b:
        FUN_0067cac0(0xf0fda5c1)->Post(0xf0fda5c1);
        return;

    case 0x2c:
        FUN_0067cac0(0x6b01d763)->Post(0x6b01d763);
        return;

    case 0x30:
    {
        void* pPlace = FUN_00ac80d0(pNoun, 0x018ebadc);
        cPlanet* pPlanet = SP_GetActivePlanet();
        if (pPlanet->IsMarketableAt((uint8_t*)pPlace + 0x780))
            return;
        pPlanet->MarkPlaceVisited((uint8_t*)pPlace + 0x780);
        return;
    }

    default:
        return;
    }
}
