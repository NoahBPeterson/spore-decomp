// Slice s0105a110: space tool-strategy action dispatch.
//   0x0105a110  cSPToolStrategy::DoToolAction        (1908 bytes)
//   0x0105a890  cSPScanToolStrategy::DoToolAction    (448 bytes)
//
// Both functions enter with `this` in ecx and four stack arguments
// (cSpaceToolData*, const Vector3&, int, int).
#include "types.h"

struct Vector3 {
    float x;
    float y;
    float z;
};

struct ResourceKey {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
};

// ---------------------------------------------------------------------------
// forward declarations
// ---------------------------------------------------------------------------
class cSpaceToolData;
class cOwnerObject;
class cSpatialObject;
class cInteraction;
class cBuilding;
class cArtifact;
class cArtifactSub;
class cPlanet;
class cCreature;
class cUFO;
class cSPMission;
class cSPSimulatorSpaceGame;
class cSPSpaceInventory;
class cSPSpaceInventoryItem;
class cMessageServer;
class cTerrainEditor;
class cWalkAround;
class cToolManager;

// ---------------------------------------------------------------------------
// generic object model
// ---------------------------------------------------------------------------
class cSpatialObject {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void* Cast(uint32_t typeID);       // +0x0c
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual bool Flag2c();                     // +0x2c
};

class cOwnerObject {
public:
    cSpatialObject* FUN_006e87e0();            // 0x006e87e0, [this+0x1e0]
    void FUN_00cb5bb0();                       // 0x00cb5bb0
    uint8_t pad04[0x11c - 0x04];
    uint8_t field11c;                          // +0x11c
};

class cInteraction {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c(uint32_t typeID, void* pObject, int flags);  // +0x0c
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void* v20();                       // +0x20
};

class cArtifactSub {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c(uint32_t typeID, void* pObject, int flags);  // +0x0c
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void* v20();                       // +0x20
    virtual uint32_t GetID();                  // +0x24
};

class cBuilding {
public:
    uint8_t pad00[0x58];
    cInteraction mInteraction;                 // +0x58
    uint8_t pad5c[0x2b0 - (0x58 + sizeof(cInteraction))];
    uint32_t field2b0;                         // +0x2b0
    uint8_t pad2b4[0xb58 - 0x2b4];
    uint32_t flags_b58;                        // +0xb58
    uint8_t padb5c[0xb67 - 0xb5c];
    uint8_t byte_b67;                          // +0xb67
    bool Flag388();                            // 0x00c0c0e0
    void* FUN_00c0bc00(int a, int b);          // 0x00c0bc00
};

class cArtifact {
public:
    uint8_t pad00[0x224];
    uint32_t field224;                         // +0x224
    uint8_t pad228[0x5d0 - 0x228];
    cArtifactSub mSub5d0;                      // +0x5d0
    cArtifactSub mSub5e8;                      // +0x5e8
    uint8_t pad5ec[0x638 - (0x5e8 + sizeof(cArtifactSub))];
    uint32_t field638;                         // +0x638
    uint8_t pad63c[0x658 - 0x63c];
    int field658;                              // +0x658
    uint8_t byte65c;                           // +0x65c
    uint8_t pad65d;
    uint8_t byte65e;                           // +0x65e
    void* FUN_00ad2620(void* pOut);            // 0x00ad2620
    void* FUN_00c3e1e0(void* pOut);            // 0x00c3e1e0
};

class cPlanet {
public:
    uint8_t pad00[0x54];
    uint32_t field54;                          // +0x54
    uint8_t pad58[0x7c - 0x58];
    uint8_t speciesData[0x88 - 0x7c];          // +0x7c
    uint32_t field88;                          // +0x88
};

class cCreature {
public:
    uint8_t pad00[0x54];
    uint32_t field54;                          // +0x54
    uint8_t pad58[0x5e8 - 0x58];
    cArtifactSub mSub5e8;                      // +0x5e8
    void* FUN_00c3e1e0(void* pOut);            // 0x00c3e1e0
};

class cUFO {
public:
    uint8_t pad00[0x714];
    int field714;                              // +0x714
};

class cSPMission {
public:
    uint32_t GetMissionID();                   // 0x01030e10
};

class cSPSpaceInventoryItem {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(void*); virtual void v18(); virtual void v1c();
    uint8_t pad04[0x10 - 0x04];
    uint32_t field10;                          // +0x10
    uint32_t field14;                          // +0x14
    void Construct();                          // 0x00c87660
};

class cSPSpaceInventory {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual bool v80(cSPSpaceInventoryItem* pItem, int a, int b);  // +0x80
};

class cSPSimulatorSpaceGame {
public:
    cSPSpaceInventory* GetPlayerInventory();   // 0x00a1ad60
};

class cTerrainEditor {
public:
    cTerrainEditor* GetCurrentTerrainSphere(); // 0x00f67d90
    void FUN_00c77bf0(uint32_t id);            // 0x00c77bf0
};

class cWalkAround {
public:
    bool FUN_01016470(void* pPlant);           // 0x01016470
    void SetHighLODPlant(void* pPlant);        // 0x010166c0
    void* FUN_01015fa0(void* pPlant);          // 0x01015fa0
};

class cToolManager {
public:
    bool CreateToolFromToolID(void* pPropertyList);  // 0x0104e340
};

class cGlobalManager {
public:
    void FUN_00b2c980(void* pObject, int flag);     // 0x00b2c980
};

class cBehaviorManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void v38(void* pBehavior);              // +0x38
};

class IAudioSystem {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void* v20();                       // +0x20
};

// ---------------------------------------------------------------------------
// message types
// ---------------------------------------------------------------------------
class ToolHitMessage {
public:
    void Construct(int flags);                 // 0x00421c80
    void Destruct();                           // 0x00421cf0
    struct Slot {
        const void* mpData;
        uint32_t mType;
    };
    uint32_t mVtable;                          // +0x00
    uint32_t mRefCount;                        // +0x04
    Slot mData[5];                             // +0x08
    uint32_t mMessageID;                       // +0x30
    uint32_t pad34;
    uint32_t mFlags;                           // +0x38
    uint32_t pad3c;
};

class cMessageServer {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void MessageSend(uint32_t messageID, void* pMessage, int flags);  // +0x14
};

// ---------------------------------------------------------------------------
// tool data / strategy
// ---------------------------------------------------------------------------
class cSpaceToolData {
public:
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
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual void vf0(); virtual void vf4(); virtual void vf8(); virtual void vfc();
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c();
    virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c();
    virtual void v120();
    uint8_t pad04[0x30 - 0x04];
    void* mpToolProperties;                    // +0x30
    uint8_t pad34[0x114 - 0x34];
    cSpatialObject* mpToolOwner;               // +0x114
    uint8_t pad118[0x124 - 0x118];
    cOwnerObject* mpOwnerObject;               // +0x124
    uint8_t pad128[0x170 - 0x128];
    uint32_t mLastErrorID;                     // +0x170
};

class AutoRefCountIWinText {
public:
    void operator=(void* pText);               // 0x00b5f950
    void* mpText;
};

class cSPToolStrategy {
public:
    virtual bool DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);
    bool CanDoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);
};

class cSPScanToolStrategy : public cSPToolStrategy {
public:
    virtual bool DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);
};

// ---------------------------------------------------------------------------
// free helpers (out-of-line; addresses in comments)
// ---------------------------------------------------------------------------
bool __cdecl FUN_0105a050(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);  // 0x0105a050
bool __cdecl FUN_01058950(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);  // 0x01058950

void* __cdecl GetActivePlanet();                                  // 0x01021260
cSPSimulatorSpaceGame* __cdecl SpaceGameGet();                    // 0x01002bd0
cToolManager* __cdecl NounManager();                              // 0x00b3d300
void* __cdecl FUN_00c0c380(void* pObject);                        // 0x00c0c380
void* __cdecl FUN_00b3d480();                                     // 0x00b3d480
void* __cdecl FUN_00ace2c0();                                     // 0x00ace2c0
void* __cdecl FUN_00ac9dd0(void* pList, const Vector3& position); // 0x00ac9dd0
void* __cdecl FUN_00acd9d0();                                     // 0x00acd9d0
void* __cdecl FUN_00c52f80(void* pList, const Vector3& position); // 0x00c52f80
void* __cdecl FUN_00c8e7e0(void* pObject);                        // 0x00c8e7e0
void __cdecl FUN_01062e70(void* pTarget, int a, cSpaceToolData* pTool, float f);  // 0x01062e70
void* __cdecl FUN_00c9f040(void* pOwner);                         // 0x00c9f040
void* __cdecl FUN_00b2a390(void* pObject);                        // 0x00b2a390
void* __cdecl FUN_010536c0(void* pObject);                        // 0x010536c0
void* __cdecl FUN_01030e40(void* pObject);                        // 0x01030e40
void* __cdecl FUN_00ae6760(void* pObject);                        // 0x00ae6760
void* __cdecl FUN_00b67720(void* pObject);                        // 0x00b67720
void* __cdecl FUN_00b67740(void* pObject);                        // 0x00b67740
void* __cdecl FUN_00bd8460(void* pObject);                        // 0x00bd8460
void* __cdecl FUN_00b3d3b0();                                     // 0x00b3d3b0
void* __cdecl FUN_00b3d390();                                     // 0x00b3d390
void* __cdecl FUN_01030e60(void* pObject);                        // 0x01030e60
cMessageServer* __cdecl MessageServer();                          // 0x0067dcc0
cBehaviorManager* __cdecl BehaviorManager();                      // 0x00b3d260
void* __cdecl FUN_00b3d420();                                     // 0x00b3d420
void* __cdecl FUN_00b3d450();                                     // 0x00b3d450
void* __cdecl FUN_00c463d0(void* pStack);                         // 0x00c463d0
void* __cdecl FUN_00c77bf0(cTerrainEditor* pEditor, uint32_t id); // 0x00c77bf0
void* __cdecl FUN_00c878d0(void* pObject);                        // 0x00c878d0
void* __cdecl FUN_00ad2620(cArtifact* pArtifact, void* pOut);     // 0x00ad2620
void __cdecl FUN_00ac0cb0(void* pList, void* pSpecies, int a, int b);  // 0x00ac0cb0
void* __cdecl FUN_00acd2d0(void* pObject, void* pArg);            // 0x00acd2d0
void* __cdecl FUN_00b90410(void* pManager, void* pSpecies);       // 0x00b90410
void* __cdecl FUN_0061df40(void* pList, void* pItem);             // 0x0061df40
void* __cdecl operator_new(uint32_t size, const char* pName, int a, int b, int c, int d);  // 0x00f473a0
void* __cdecl FUN_00c77bf0_2(cTerrainEditor* pEditor, uint32_t id);  // alias
void* __cdecl FUN_01015df0();                                     // 0x01015df0
bool __cdecl FUN_01016470(void* pPlant);                          // 0x01016470
void* __cdecl FUN_01015fa0(void* pPlant);                         // 0x01015fa0
void* __cdecl FUN_00c3e1e0(cCreature* pCreature, void* pOut);     // 0x00c3e1e0
void* __cdecl FUN_00b3d420_2();                                   // 0x00b3d420
IAudioSystem* __cdecl GetSystemAT();                              // 0x00a206f0
void __cdecl KillSetiEffects(uint32_t id, void* pAudio);          // 0x00435ed0
int __cdecl SetErrorEvent(cSpaceToolData* pTool, uint32_t eventID, bool post);  // 0x010527f0

bool __cdecl ScanBuilding(void* pBuilding);                       // 0x01058680
bool __cdecl ScanAllSpecies(void* pPlanet);                       // 0x010534c0
bool __cdecl ScanTribe(void* pTribe);                             // 0x01053320
bool __cdecl ScanSpecies(void* pPlanet);                          // 0x01053240
bool __cdecl ScanColony(void* pColony);                           // 0x010533d0

void* __cdecl interface_cast_ce9f6639(void* pObject);             // vtable Cast
void* __cdecl interface_cast_3ed590d(void* pObject);              // vtable Cast

extern void* DAT_016df2f4;
extern uint32_t DAT_0167eb10;

// ---------------------------------------------------------------------------
// 0x0105a110  cSPToolStrategy::DoToolAction
// ---------------------------------------------------------------------------
// @ 0x0105a110
bool cSPToolStrategy::DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4)
{
    if (!CanDoToolAction(pTool, position, a3, 0))
        return true;

    if (!pTool->mpOwnerObject)
        goto LAB_838;

    {
        cSpatialObject* pSpatial = pTool->mpOwnerObject->FUN_006e87e0();
        if (!pSpatial)
            goto LAB_838;

        pSpatial = pTool->mpOwnerObject->FUN_006e87e0();
        if (pSpatial->Flag2c())
            goto LAB_838;
    }

    cUFO* pUFO = (cUFO*)FUN_00c9f040(&pTool->mpToolOwner);
    if (pUFO && pUFO->field714 != 0 && pUFO->field714 != 7) {
        return FUN_01058950(pTool, position, a3, a4);
    }

    {
        cSpatialObject* pSpatial = pTool->mpOwnerObject->FUN_006e87e0();
        cBuilding* pBuilding = 0;
        if (pSpatial) {
            pBuilding = (cBuilding*)pSpatial->Cast(0xce9f6639);
        }

        if (pBuilding) {
            cInteraction* pInteraction = &pBuilding->mInteraction;
            cSPMission* pMission = (cSPMission*)FUN_01030e60(pInteraction->v20());
            int nMission = (int)FUN_01030e60(pInteraction->v20());
            bool bFlag = pBuilding->Flag388();
            if (!bFlag
                && ((pBuilding->flags_b58 >> 9) & 1) == 0
                && ((pBuilding->flags_b58 >> 8) & 1) == 0
                && nMission == 0
                && (!pMission || pMission->GetMissionID() == 2)) {
                if (!pUFO || pUFO->field714 == 0 || pUFO->field714 == 7) {
                    FUN_00c0c380(pSpatial);
                    if (pBuilding->byte_b67) {
                        FUN_00acd2d0(FUN_00b3d480(), pBuilding);
                    }
                    pBuilding->field2b0 = 4;

                    void* pOwnerPart = pTool->mpOwnerObject ? (void*)((uint8_t*)pTool->mpOwnerObject + 0x11c) : 0;
                    pInteraction->v0c((uint32_t)DAT_016df2f4, pOwnerPart, 0);
                    ((AutoRefCountIWinText*)((uint8_t*)pTool + 0x128))->operator=(pInteraction->v20());

                    NounManager();
                    void* pNoun = FUN_00ace2c0();
                    void* pFound = FUN_00ac9dd0(pNoun, position);
                    if (pFound) {
                        *(float*)((uint8_t*)pFound + 0x2d4) = position.x;
                        *(float*)((uint8_t*)pFound + 0x2d8) = position.y;
                        *(float*)((uint8_t*)pFound + 0x2dc) = position.z;
                    }

                    void* pTribeList = FUN_00acd9d0();
                    void* pTribe = FUN_00c52f80(pTribeList, position);
                    if (pTribe) {
                        void* pTarget = FUN_00c8e7e0(pTribe);
                        FUN_01062e70(pTarget, 6, pTool, 200.0f);
                    }
                }
                else {
                    cSPSimulatorSpaceGame* pGame = SpaceGameGet();
                    pGame->GetPlayerInventory();

                    int bHas = FUN_00c0c380(pSpatial) != 0;
                    void* pSpecies = pBuilding->FUN_00c0bc00(1, bHas);
                    void* pList = FUN_00c463d0(0);
                    void* pMgr = FUN_00b3d450();
                    FUN_00ac0cb0(pList, pSpecies, 1, bHas);
                    if (pUFO->field714 == 0)
                        goto LAB_3f5;
                }
                goto LAB_825;
            }
        }
        else {
            cCreature* pCreature = (cCreature*)FUN_00b2a390(pSpatial);
            cPlanet* pPlanet = (cPlanet*)FUN_010536c0(pSpatial);
            if (!(pCreature == 0 && (pPlanet == 0 || (pPlanet->field88 != 0 && pPlanet->field88 != 1 && pPlanet->field88 != 2)))) {
                // human / plant path
                uint8_t bResult = 1;
                if (pUFO == 0 || pUFO->field714 != 0)
                    goto LAB_756;

                cSPSimulatorSpaceGame* pGame = SpaceGameGet();
                cSPSpaceInventory* pInventory = pGame->GetPlayerInventory();

                void* pSpecies;
                if (pCreature)
                    pSpecies = pCreature->FUN_00c3e1e0(0);
                else
                    pSpecies = (uint8_t*)pPlanet + 0x7c;

                void* pSpeciesMgr = FUN_00b3d420();
                void* pSpeciesObj = FUN_00b90410(pSpeciesMgr, pSpecies);
                AutoRefCountIWinText ref;
                ref.mpText = 0;
                void* pProp = FUN_00c463d0(&ref);
                ((cSPSpaceInventoryItem*)pSpeciesObj)->v14(pProp);
                uint8_t bOk = pInventory->v80((cSPSpaceInventoryItem*)pSpeciesObj, 0, 0);
                if (!bOk) {
                    SetErrorEvent(pTool, 0xb24b77da, true);
                    pCreature = 0;
                    bResult = 0;
                }
                else {
                    bResult = 1;
                }
                FUN_00c463d0(&ref);
                if (bResult)
                    goto LAB_756;
                goto LAB_796;

LAB_756:
                if (!pCreature) {
                    cWalkAround* pWalk = (cWalkAround*)FUN_01015df0();
                    if (!pWalk)
                        goto LAB_825;
                    pWalk = (cWalkAround*)FUN_01015df0();
                    if (!FUN_01016470(pPlanet) && pPlanet->field54 != 0)
                        pWalk->SetHighLODPlant(pPlanet);
                    pCreature = (cCreature*)FUN_01015fa0(pPlanet);
                }

LAB_796:
                if (!pCreature)
                    goto LAB_825;

                if (pUFO && pUFO->field714 == 0) {
                    cArtifactSub* pSub = &pCreature->mSub5e8;
                    if (pSub->GetID() != 0x114242e6) {
                        BehaviorManager()->v38(pSub);
                        void* pOwnerPart = pTool->mpOwnerObject ? (void*)((uint8_t*)pTool->mpOwnerObject + 0x11c) : 0;
                        pSub->v0c((uint32_t)DAT_016df2f4, pOwnerPart, 0);
                        ((AutoRefCountIWinText*)((uint8_t*)pTool + 0x128))->operator=(pSub->v20());
                        ((cGlobalManager*)FUN_00b3d3b0())->FUN_00b2c980(pCreature, 1);
                    }
                }
                goto LAB_825;
            }

            // artifact path
            cArtifact* pArtifact = (cArtifact*)FUN_01030e40(pSpatial);
            if (!pUFO || pUFO->field714 != 0 || !pArtifact)
                goto LAB_825;
            if (pArtifact->mSub5d0.GetID() == 0x114242e6)
                goto LAB_825;
            if (!pArtifact->byte65e)
                goto LAB_825;

            uint8_t bResult = 0;
            cSPSimulatorSpaceGame* pGame = SpaceGameGet();
            cSPSpaceInventory* pInventory = pGame->GetPlayerInventory();

            switch (pArtifact->field658) {
            case 2: {
                ResourceKey key;
                void* pKey = pArtifact->FUN_00ad2620(&key);
                if (pKey != (void*)0x16e1b20 && pArtifact->field638 != 0) {
                    AutoRefCountIWinText ref;
                    ref.mpText = 0;
                    void* pProp = FUN_00c463d0(&ref);
                    ResourceKey key2;
                    void* pKey2 = pArtifact->FUN_00ad2620(&key2);
                    void* pMgr = FUN_00b3d390();
                    if (((cToolManager*)pMgr)->CreateToolFromToolID(pProp))
                        bResult = 1;
                    FUN_00c463d0(&ref);
                }
                if (bResult)
                    goto LAB_642;
                break;
            }
            case 4: {
                cSPSpaceInventoryItem* pItem = (cSPSpaceInventoryItem*)operator_new(0x7c, "Simulator/cSpaceInventoryItem", 0, 0, 0, 0);
                if (pItem)
                    pItem->Construct();
                FUN_0061df40(0, pItem);
                if (pArtifact->field638 != 0) {
                    pItem->field14 = 4;
                    ResourceKey key;
                    void* pKey = pArtifact->FUN_00ad2620(&key);
                    pItem->v14(pKey);
                    pItem->field10 = pArtifact->field638;
                    pArtifact->byte65c = 1;
                    bool bOk = pInventory->v80(pItem, 0, 0);
                    pItem->v08();
                    bResult = bOk;
                }
                if (bResult)
                    goto LAB_642;
                break;
            }
            case 5: {
                ResourceKey key;
                void* pKey = pArtifact->FUN_00ad2620(&key);
                AutoRefCountIWinText ref;
                ref.mpText = 0;
                void* pProp = FUN_00c463d0(&ref);
                FUN_00c878d0(pKey);
                FUN_00c463d0(&ref);
                break;
            }
            case 7:
LAB_642: {
                cArtifactSub* pSub = &pArtifact->mSub5d0;
                BehaviorManager()->v38(pSub);
                pArtifact->field224 = 4;
                void* pOwnerPart = pTool->mpOwnerObject ? (void*)((uint8_t*)pTool->mpOwnerObject + 0x11c) : 0;
                pSub->v0c((uint32_t)DAT_016df2f4, pOwnerPart, 0);
                ((AutoRefCountIWinText*)((uint8_t*)pTool + 0x128))->operator=(pSub->v20());
                goto LAB_825;
            }
            default:
                break;
            }
        }
    }

LAB_3f5:
    SetErrorEvent(pTool, 0xb24b77da, true);
    goto LAB_825;

LAB_825:
    if (pTool->mpOwnerObject)
        pTool->mpOwnerObject->FUN_00cb5bb0();

LAB_838:
    {
        cTerrainEditor* pEditor = (cTerrainEditor*)NounManager();
        if (pEditor->GetCurrentTerrainSphere()) {
            cTerrainEditor* pEditor2 = (cTerrainEditor*)NounManager();
            pEditor2 = pEditor2->GetCurrentTerrainSphere();
            pEditor2->FUN_00c77bf0(0x56d1874);
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x0105a890  cSPScanToolStrategy::DoToolAction
// ---------------------------------------------------------------------------
// @ 0x0105a890
bool cSPScanToolStrategy::DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4)
{
    GetActivePlanet();

    if (!CanDoToolAction(pTool, position, a3, 0))
        return true;

    if (!pTool->mpOwnerObject)
        return true;

    if (!pTool->mpOwnerObject->FUN_006e87e0())
        return true;

    uint8_t bResult = 0;
    cSpatialObject* pSpatial = pTool->mpOwnerObject->FUN_006e87e0();
    if (pSpatial) {
        void* pBuilding = pSpatial->Cast(0xce9f6639);
        if (pBuilding) {
            bResult = ScanBuilding(pBuilding);
            goto LAB_aa0e;
        }

        void* pPlanet = pSpatial->Cast(0x3ed590d);
        if (pPlanet) {
            uint32_t nType = *(uint32_t*)((uint8_t*)pPlanet + 0x88);
            if (nType == 0 || nType == 1 || nType == 2) {
                bResult = ScanAllSpecies((uint8_t*)pPlanet + 0x7c);
                goto LAB_aa0e;
            }
        }
    }

    void* pTribe = FUN_00ae6760(pSpatial);
    if (pTribe) {
        bResult = ScanTribe(pTribe);
        goto LAB_aa0e;
    }

    void* pBuilding2 = FUN_00b67720(pSpatial);
    if (pBuilding2) {
        bResult = ScanSpecies(pBuilding2);
        goto LAB_aa0e;
    }

    void* pColony = FUN_00b67740(pSpatial);
    if (pColony) {
        bResult = ScanColony(pColony);
        goto LAB_aa0e;
    }

    void* pArtifact = FUN_01030e40(pSpatial);
    if (pArtifact) {
        ToolHitMessage msg;
        msg.Construct(0);
        msg.mData[0].mpData = pArtifact;
        cMessageServer* pServer = (cMessageServer*)MessageServer();
        pServer->MessageSend(0xf46092d3, &msg, 0);
        msg.Destruct();
    }
    else {
        void* pOther = FUN_00bd8460(pSpatial);
        if (pOther) {
            ToolHitMessage msg;
            msg.Construct(0);
            msg.mData[0].mpData = pOther;
            cMessageServer* pServer = (cMessageServer*)MessageServer();
            pServer->MessageSend(0xf46093da, &msg, 0);
            msg.Destruct();
        }
    }

LAB_aa0e:
    if (pTool->mpOwnerObject)
        pTool->mpOwnerObject->FUN_00cb5bb0();

    if (bResult) {
        IAudioSystem* pAudio = GetSystemAT();
        void* pAudioArg = pAudio ? pAudio->v20() : 0;
        KillSetiEffects(0x75c412dd, pAudioArg);
    }
    return true;
}
