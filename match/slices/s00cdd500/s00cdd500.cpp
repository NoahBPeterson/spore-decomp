// Slice s00cdd500: tribe mode transitions, the per-tribe "load tools" pass,
// terraforming tool placement and the player save-read.
//
// Targets: 00cdd500 00cdd960 00cdd9c0 00cddcf0 00cddda0 00cde160
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// The class layouts are recovered by role: every member is named after what the
// code does with it and the eastl containers keep their real three-pointer
// shape, so the rbtree, the SPVector<Key> fast path and the refcounted handles
// stay readable.  Vtable slots that have no typed owner in this file are called
// through VSLOT(), which emits exactly the `call dword ptr [reg + off]` the
// original binary performs.

#include "types.h"
#include <math.h>

typedef unsigned int  u32;
typedef int           s32;
typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { float x, y, z; };
struct Quat4 { float x, y, z, w; };
struct Mat3 { float m[9]; };

// Vtable call: VSLOT(<thiscall fn ptr type>, pObject, <byte offset>)(args...)
#define VSLOT(fnptr, obj, off) ((fnptr)((obj)->mpVtbl_00[(off) / 4]))

void operator_delete_array(void* p);                                  // 0x00f47380
void ReadInt32(u32 h, void* pDst, s32 nCount, s32 nFlags);            // 0x0093a780

// eastl's allocator keeps the block size four bytes in front of the payload.
inline bool BlockIsAllocated(const void* p)
{
    return p != 0 && ((const u32*)p)[-1] != 0;
}

// ---------------------------------------------------------------------------
// SPVector<Key> (Key = three floats, 12 bytes).  The inline fast path is the
// one MSVC emitted at every push_back site: bump mpEnd when there is room,
// otherwise hand the slot to DoInsertKey.
// ---------------------------------------------------------------------------
typedef Vec3 Key3;

struct KeyVec {
    Key3* mpBegin;
    Key3* mpEnd;
    Key3* mpCap;

    void Reserve(s32 n);                                        // 0x0041e4d0
    void DoInsertKey(Key3* pSlot, const Key3& value);            // 0x004e3e10
    Key3* Erase(Key3* pFirst, Key3* pLast);                      // 0x0050f740

    void PushBack(const Key3& value)
    {
        if (mpEnd < mpCap) {
            Key3* pSlot = mpEnd;
            ++mpEnd;
            if (pSlot)
                *pSlot = value;
        } else
            DoInsertKey(mpEnd, value);
    }

    void Destroy()
    {
        if (BlockIsAllocated(mpBegin))
            operator_delete_array(mpBegin);
    }
};

void SortKeys(Key3* pFirst, Key3* pLast);                        // 0x004f6b70
Key3* UniqueKeys(Key3* pFirst, Key3* pLast);                     // 0x004f6830

// ---------------------------------------------------------------------------
// Generic polymorphic object (only its vptr is modelled).
// ---------------------------------------------------------------------------
struct cPoly {
    void** mpVtbl_00;
};

// ---------------------------------------------------------------------------
// Noun manager / noun vectors
// ---------------------------------------------------------------------------
void F_cd7d10();
void F_d3d420();
void F_accc30();
void F_ace070();
void F_accbb0();
void F_b1e500();

template <class T>
struct PtrVec {
    T** mpBegin;
    T** mpEnd;
    T** mpCap;
};

// The noun manager hands out vectors whose first dword is a header; the live
// range starts at +4 (that is why the loops read [pVec + 4] / [pVec + 8]).
template <class T>
struct NounVecOut {
    u32 mHeader_00;
    PtrVec<T> mItems_04;
};

struct cGameNounManager {
    void* GetPlayerTribe();                                      // 0x00bfc5f0
    void* GetGameDataVector(void (*)(), void (*)(), void (*)(), void (*)(), u32); // 0x00b21340
};

cGameNounManager* NounManager();                                 // 0x00b3d300

// ---------------------------------------------------------------------------
// Small managers
// ---------------------------------------------------------------------------
struct cEffectsManager {
    void** mpVtbl_00;
};

struct cMsgSink {
    void** mpVtbl_00;
    void OnModeChange(u32 previousMode, u32 newMode)
    {
        VSLOT(void (__thiscall*)(cMsgSink*, u32, u32), this, 0x14)(this, previousMode, newMode);
    }
};

struct cBehaviorManager {
    u32 mPad_00;
    cMsgSink mSink_04;
};

cBehaviorManager* BehaviorManager();                             // 0x00b3d260
cEffectsManager* EffectsManagerPtr();                            // 0x0067ddd0
cPoly* PropertyManager();                                        // 0x0067de30
cPoly* GameInputManager();                                       // 0x00b3d250
cPoly* SimTicker();                                              // 0x00b3d330
cPoly* GetGameTerrainCursor();                                   // 0x00b30d70
cPoly* GetPlanetModel();                                         // 0x00b3d350
cPoly* GetTerraformingManager();                                 // 0x00b3d430

struct cTickerClient {
    void** mpVtbl_00;
    void Activate()
    {
        VSLOT(void (__thiscall*)(cTickerClient*), this, 0x20)(this);
    }
};

struct cSimTicker {
    void** mpVtbl_00;
    void QueueFlush(cTickerClient* pObject)
    {
        VSLOT(void (__thiscall*)(cSimTicker*, cTickerClient*), this, 0x54)(this, pObject);
    }
};

struct cCitySimulator {
    void PostMsg();                                              // 0x00ae6570
};

cTickerClient* FUN_00cc8b10();                                   // 0x00cc8b10
cCitySimulator* FUN_00bd83e0();                                  // 0x00bd83e0
cTickerClient* FUN_00d51660();                                   // 0x00d51660

// ---------------------------------------------------------------------------
// Community editor host (mode strategy member at +0x230)
// ---------------------------------------------------------------------------
struct cCommunityEditor {
    void** mpVtbl_00;
    void Deactivate(bool bA, bool bB);                            // 0x00d100b0
};

struct cEditorHost {
    void** mpVtbl_00;
    u8 mPad_04[0x58];
    cCommunityEditor* mpEditor_5c;

    void Shutdown()
    {
        VSLOT(void (__thiscall*)(cEditorHost*), this, 0x08)(this);
    }
    void ReleaseOwnership(s32 nMode)
    {
        VSLOT(void (__thiscall*)(cEditorHost*, s32), this, 0x00)(this, nMode);
    }
};

bool FUN_00d09660(cPoly* pEditor);                               // 0x00d09660
u32 FUN_00d09670(cPoly* pEditor);                                // 0x00d09670

// ---------------------------------------------------------------------------
// Tribe
// ---------------------------------------------------------------------------
struct RefCounted {
    void** mpVtbl_00;
    void Release()
    {
        VSLOT(void (__thiscall*)(RefCounted*), this, 0x04)(this);
    }
    void ReleaseEx()
    {
        VSLOT(void (__thiscall*)(RefCounted*), this, 0x08)(this);
    }
};

struct cTribeDisplayStrategy {
    u8 mPad_000[0x3c];
    RefCounted mRef_3c;
    void Deactivate();                                           // 0x00ccd050
};

// Sub-object at cTribe::+0x34: a tool layout slot owner.
struct cTribeToolSlot {
    void** mpVtbl_00;
    void SetTool(u32 nToolId)
    {
        VSLOT(void (__thiscall*)(cTribeToolSlot*, u32), this, 0x00)(this, nToolId);
    }
};

// Sub-object at noun/+0x120 and cTribe/+0x120: hut work area of a tribe.
struct cTribeWorkArea {
    void** mpVtbl_00;
    const Vec3* GetCenter()
    {
        return VSLOT(const Vec3* (__thiscall*)(cTribeWorkArea*), this, 0x2c)(this);
    }
    void Transform(const Vec3* pPoint)
    {
        VSLOT(void (__thiscall*)(cTribeWorkArea*, const Vec3*), this, 0x38)(this, pPoint);
    }
    bool IsPrime()
    {
        return VSLOT(bool (__thiscall*)(cTribeWorkArea*), this, 0x58)(this);
    }
};

// rbtree node of the tribe's tool map (eastl layout).
struct ToolNode {
    ToolNode* mpRight_00;
    ToolNode* mpLeft_04;
    ToolNode* mpParent_08;
    u32 mColor_0c;
    u32 mKey_10;
    u32 mValue_14;
};

// The map anchor is what end() points at; the root lives in mAnchor.mpParent.
struct ToolTree {
    u32 mCompare_00;
    ToolNode mAnchor_04;

    ToolNode* Find(u32 key)
    {
        ToolNode* pNode = mAnchor_04.mpParent_08;
        ToolNode* pLower = &mAnchor_04;
        while (pNode != 0) {
            if (pNode->mKey_10 < key)
                pNode = pNode->mpRight_00;
            else {
                pLower = pNode;
                pNode = pNode->mpLeft_04;
            }
        }
        if (pLower == &mAnchor_04 || key < pLower->mKey_10)
            return &mAnchor_04;
        return pLower;
    }
};

// An object stored by the tribe that accepts a serialized name string.
struct cNamedInserter {
    void** mpVtbl_00;
};

void FUN_00b6f380(cNamedInserter* pInserter, const void* pName);  // 0x00b6f380

// cTribe as used by ContinueLoading.
struct cTribe {
    void** mpVtbl_00;
    u8 mPad_004[0x30];
    cTribeToolSlot mToolSlot_034;
    u8 mPad_038[0xe8];
    cTribeWorkArea mWorkArea_120;
    u8 mPad_124[0x10c];
    cNamedInserter mNamedInserter_230;
    cTribeDisplayStrategy* mpDisplayStrategy_234;
    ToolTree mToolTree_238;

    void UpdateGridAndHutArea(float fDistance);                  // 0x00c99550
    void ResetToolLayout();                                      // 0x00c951d0
    void ReserveToolsSlots(bool bReserve);                       // 0x00c998c0
};

void cTribe_SetupHotSpot(const Vec3* pPoint, s32 nKind);         // 0x00c9afb0

// ---------------------------------------------------------------------------
// Planet, star manager, terraforming
// ---------------------------------------------------------------------------
struct cPlanetTree {
    u8 mPad_000[0xbc];
    Vec3* mpBegin_0bc;
    Vec3* mpEnd_0c0;
};

struct cPlanet {
    u8 mPad_000[0x13c];
    cPlanetTree* mpTree_13c;
};

struct cStarManager {
    void** mpVtbl_00;
    void BuildTribeSites(cPlanetTree* pTree, void* pParams)      // 0x00bb5930
    {
        VSLOT(void (__thiscall*)(cStarManager*, cPlanetTree*, void*), this, 0x00)(this, pTree, pParams);
    }
};

// StarManager() is a plain getter; the two argument pushes that precede the
// call in the original belong to BuildTribeSites().
cStarManager* StarManager();                                     // 0x00b3d2a0

cPlanet* FUN_01021260();                                         // 0x01021260
void FUN_00c71560(cPlanet* pPlanet, s32 nMode);                  // 0x00c71560
void FUN_00c73310(cPlanet* pPlanet);                             // 0x00c73310
void FUN_00c73330(cPlanet* pPlanet);                             // 0x00c73330
bool FUN_00c70c00(cPlanet* pPlanet);                             // 0x00c70c00
void FUN_008414c0(cPlanet* pPlanet);                             // 0x008414c0
void FUN_00c71e70(cPlanet* pPlanet);                             // 0x00c71e70
void FUN_00c82f80(void* pOwner);                                 // 0x00c82f80

// Parameters block built by 0x00ba7bd0 and consumed by the star manager.
struct PlanetSearchParams {
    u32 mRangeX_00;          // 0x7f
    u32 mRangeY_04;          // 0x3f
    u32 mRangeZ_08;          // 0x3f
    u8  mFlagA_0c;
    u8  mFlagB_0d;
    u8  mFlagC_0e;
    u8  mEnabled_0f;         // 1
    u32 mCountX_10;          // 0xf
    u32 mCountY_14;          // 0xf
    u32 mFlags_18;
    u32 mFlags2_1c;
    KeyVec mKeys_20;
    u8  mUnset_2c[8];        // not touched by the constructor
    KeyVec mPoints_34;

    PlanetSearchParams();                                    // 0x00ba7bd0
};

// Noun of the "tribe tool site" type (0x57f09e5e / 0x1be418e families).
struct cPlacement {
    void** mpVtbl_00;

    const Vec3* GetPosition()
    {
        return VSLOT(const Vec3* (__thiscall*)(cPlacement*), this, 0x2c)(this);
    }
    const Quat4* GetRotation()
    {
        return VSLOT(const Quat4* (__thiscall*)(cPlacement*), this, 0x30)(this);
    }
};

struct cNoun {
    void** mpVtbl_00;
    u8 mPad_004[0x30];
    cPlacement mPlacement_034;
    u8 mPad_038[0x6c];
    cPoly* mpCell_a4;
    u8 mPad_0a8[0x60];
    u32 mNounType_108;
    u8 mPad_10c[0x10];
    u32 mTerraformSlot_11c;
    cTribeWorkArea mWorkArea_120;

    bool IsRemoved()
    {
        return VSLOT(bool (__thiscall*)(cNoun*), this, 0x2c)(this) != 0;
    }
    void GetLinkedObjects(PtrVec<cPoly>* pOut)
    {
        VSLOT(void (__thiscall*)(cNoun*, PtrVec<cPoly>*), this, 0x90)(this, pOut);
    }
};

// Cell object hung off the noun at +0xa4; its position sits at +0x504.
struct cCell {
    u8 mPad_000[0x504];
    Vec3 mPosition_504;
};

// 20-byte cell of the surface list published by 0x0169b2c8.
struct cSurfaceCell {
    u8 mData[0x14];
};

struct cSurfaceCellList {
    u8 mPad_00[0x2c];
    cSurfaceCell* mpBegin_2c;
    cSurfaceCell* mpEnd_30;
};

extern cSurfaceCellList* gSurfaceCellList;                       // 0x0169b2c8

struct cTerraformingManager {
    void** mpVtbl_00;
    u32 AddPoke(const Vec3* pPosition, float fRadius)             // 0x00bbf730
    {
        return VSLOT(u32 (__thiscall*)(cTerraformingManager*, const Vec3*, float), this, 0x00)(this, pPosition, fRadius);
    }
    void AddSurfacePoint(cSurfaceCell* pCell, s32 nMode)          // 0x00bbd730
    {
        VSLOT(void (__thiscall*)(cTerraformingManager*, cSurfaceCell*, s32), this, 0x00)(this, pCell, nMode);
    }
    void Commit()                                                // 0x00bbc400
    {
        VSLOT(void (__thiscall*)(cTerraformingManager*), this, 0x00)(this);
    }
};

// ---------------------------------------------------------------------------
// Property list / terrain model
// ---------------------------------------------------------------------------
struct cPropertyList {
    void** mpVtbl_00;
    void Release()
    {
        VSLOT(void (__thiscall*)(cPropertyList*), this, 0x04)(this);
    }
};

float GetPropertyFloat(cPropertyList* pList, u32 nKey, float fDefault); // 0x004e1c70

// Terrain model instance handed to the renderer (0x38 bytes).
struct ModelInstance {
    u16 mFlags_00;
    u16 mCount_02;
    Vec3 mOrigin_04;
    float mScale_10;
    Mat3 mRotation_14;
};

Mat3 Matrix3FromQuaternion(const Quat4* pQuat);                  // 0x0059c190

struct cRenderEntity {
    void** mpVtbl_00;
    void AddInstance(const ModelInstance* pInstance, cPropertyList* pProperties)
    {
        VSLOT(void (__thiscall*)(cRenderEntity*, const ModelInstance*, cPropertyList*), this, 0x54)(this, pInstance, pProperties);
    }
};

struct cPlanetModel {
    void** mpVtbl_00;
    u8 mPad_004[0x20];
    cRenderEntity* mpEntity_024;

    bool RayCast(const Vec3* pStart, float fMaxDistance, Vec3* pOut,
                 float fScale, s32 nFlagsA, s32 nFlagsB)         // 0x00b88770
    {
        return VSLOT(bool (__thiscall*)(cPlanetModel*, const Vec3*, float, Vec3*, float, s32, s32),
                     this, 0x00)(this, pStart, fMaxDistance, pOut, fScale, nFlagsA, nFlagsB);
    }
};

// Globals used when a model instance is first assembled.
extern Vec3 gDefaultOrigin;                                      // 0x0169b2cc
extern Mat3 gDefaultRotation;                                    // 0x0169b378
extern float gModelScale;                                        // 0x01485720
extern float gMinTribeRadius;                                    // 0x01581268
extern float gHotSpotDistance;                                   // 0x0158125c
extern const u8 gPrimeToolLabel;                                 // 0x0157ef54

// ---------------------------------------------------------------------------
// Misc free functions used by the mode strategy
// ---------------------------------------------------------------------------
void FUN_00b6c280();                                             // 0x00b6c280
void FUN_00cd49a0();                                             // 0x00cd49a0
void FUN_00cc8940(cTribeDisplayStrategy* pStrategy, s32 nMode);   // 0x00cc8940
void FUN_00cc93b0(cTribeDisplayStrategy* pStrategy, s32 nMode);   // 0x00cc93b0
cPoly* FUN_0067ddc0();                                           // 0x0067ddc0
void* FUN_00cd4770(void* pNoun, void* pTribe);                   // 0x00cd4770
u32 __fastcall FUN_00b6f0c0(cTribeDisplayStrategy* pStrategy, cTribeDisplayStrategy* pArg); // 0x00b6f0c0
void FUN_00c0d950(cPoly* pObject, bool bFlag);                    // 0x00c0d950
void FUN_00b93c60(s32 nCount, const void* pExtra);                // 0x00b93c60
void FUN_00829110(void*** ppRemovedEnd, void** pFirst, void** pLast, void* pScratch, void* pTribe); // 0x00829110

struct cTribeTuningData {
    void Init();                                                 // 0x00ce6af0
};

extern cTribeTuningData gTribeTuningData;                        // 0x01581208
void LoadTribeToolData();                                        // 0x00c9de50
void LoadTribeArchetypeData();                                   // 0x00c97220

// String16 (the empty-string sentinel is the 2-byte global at 0x01667bac).
struct String16 {
    u16* mpBegin;
    u16* mpEnd;
    u16* mpCap;

    void SetEmpty()
    {
        extern u16 gEmptyString16[];
        mpBegin = gEmptyString16;
        mpEnd = gEmptyString16;
        mpCap = gEmptyString16 + 1;
    }

    ~String16()
    {
        if (mpCap - mpBegin > 1 && mpBegin != 0)
            operator_delete_array(mpBegin);
    }
};

struct cSpeciesProfile {
    void GetUiName(String16* pName);                             // 0x004da330
};

// Scratch pointer list built from the noun vector.
struct cNounScratch {
    void** mpBegin;
    void** mpEnd;
    void** mpCap;
    void Build(s32 nCount, const void* pExtra);                  // 0x00b93c60
};

// ---------------------------------------------------------------------------
// cTribeModeStrategy
// ---------------------------------------------------------------------------
struct cTribeModeStrategy {
    void** mpVtbl_00;
    u8 mPad_004[0x22c];
    cEditorHost* mpEditorHost_230;
    cTribeDisplayStrategy* mpDisplayStrategy_234;
    cTribeDisplayStrategy* mpLoadingStrategy_240;
    u8 mPad_238[0x144];
    u32 mSavedEditorValue_380;
    u32 mPad_384;
    cPoly* mpSaveObject_388;

    u32 GetMode()
    {
        return VSLOT(u32 (__thiscall*)(cTribeModeStrategy*), this, 0x1c)(this);
    }
    void SetMode(u32 nMode)
    {
        VSLOT(void (__thiscall*)(cTribeModeStrategy*, u32), this, 0x40)(this, nMode);
    }
    void Refresh()
    {
        VSLOT(void (__thiscall*)(cTribeModeStrategy*), this, 0x48)(this);
    }

    void PreGameModeTransition(u32 previousMode, u32 newMode);     // 0x00cdd500
    void ContinueLoading();                                        // 0x00cddda0
};

// @ 0x00cdd500
void cTribeModeStrategy::PreGameModeTransition(u32 previousMode, u32 newMode)
{
    if (GetMode() == newMode)
        return;

    SetMode(newMode);
    BehaviorManager()->mSink_04.OnModeChange(previousMode, newMode);

    if (previousMode == 0x1654c02) {
        cEffectsManager* pEffects = EffectsManagerPtr();
        VSLOT(void (__thiscall*)(cEffectsManager*, s32, s32), pEffects, 0x98)(pEffects, 9, 0);
        FUN_00b6c280();
        if (newMode != 0xdbdba1 && newMode != 0x1654c06)
            FUN_00cd49a0();

        if (mpEditorHost_230 != 0) {
            if (newMode == 0xdbdba1) {
                cCommunityEditor* pEditor = mpEditorHost_230->mpEditor_5c;
                if (pEditor != 0 && FUN_00d09660((cPoly*)pEditor)) {
                    mSavedEditorValue_380 = FUN_00d09670((cPoly*)pEditor);
                    pEditor->Deactivate(true, true);
                }
            } else {
                mpEditorHost_230->Shutdown();
                if (mpEditorHost_230 != 0)
                    mpEditorHost_230->ReleaseOwnership(1);
                mpEditorHost_230 = 0;
            }
        }

        FUN_00cc8940(mpDisplayStrategy_234, 0);
        FUN_00cc93b0(mpDisplayStrategy_234, 0);

        if (newMode != 0xdbdba1) {
            if (mpDisplayStrategy_234 != 0) {
                mpDisplayStrategy_234->Deactivate();
                if (mpDisplayStrategy_234 != 0) {
                    RefCounted* pRef = &mpDisplayStrategy_234->mRef_3c;
                    mpDisplayStrategy_234 = 0;
                    pRef->Release();
                }
            }

            cSimTicker* pTicker = (cSimTicker*)SimTicker();
            FUN_00cc8b10()->Activate();
            pTicker->QueueFlush(FUN_00cc8b10());
            FUN_00bd83e0()->PostMsg();
            pTicker->QueueFlush((cTickerClient*)FUN_00bd83e0());
            FUN_00d51660()->Activate();
            pTicker->QueueFlush(FUN_00d51660());

            VSLOT(void (__thiscall*)(cPoly*), mpSaveObject_388, 0x24)(mpSaveObject_388);
            if (mpSaveObject_388 != 0) {
                cPoly* pOld = mpSaveObject_388;
                mpSaveObject_388 = 0;
                VSLOT(void (__thiscall*)(cPoly*), pOld, 0x08)(pOld);
            }
        }

        if (FUN_0067ddc0() != 0) {
            cPoly* pObject = FUN_0067ddc0();
            VSLOT(void (__thiscall*)(cPoly*, s32), pObject, 0x28)(pObject, 0);
            pObject = FUN_0067ddc0();
            VSLOT(void (__thiscall*)(cPoly*), pObject, 0x24)(pObject);
        }

        cPlanet* pPlanet = FUN_01021260();
        if (pPlanet != 0 && newMode == 0x1654c04) {
            cPlanetTree* pTree = pPlanet->mpTree_13c;
            PlanetSearchParams params;

            s32 nCount = pTree->mpEnd_0c0 - pTree->mpBegin_0bc;
            params.mKeys_20.Reserve(nCount);
            for (s32 i = 0; i < nCount; ++i)
                params.mKeys_20.PushBack(pTree->mpBegin_0bc[i]);

            NounVecOut<cNoun>* pVec =
                (NounVecOut<cNoun>*)NounManager()->GetGameDataVector(F_cd7d10, F_d3d420, F_accc30, F_b1e500, 0x1be418e);
            s32 nSites = (s32)(pVec->mItems_04.mpEnd - pVec->mItems_04.mpBegin);
            params.mPoints_34.Reserve(nSites);
            for (cNoun** pIt = pVec->mItems_04.mpBegin; pIt != pVec->mItems_04.mpEnd; ++pIt) {
                cNoun* pNoun = *pIt;
                if (!pNoun->IsRemoved()) {
                    cCell* pCell = (cCell*)pNoun->mpCell_a4;
                    if (pCell != 0)
                        params.mPoints_34.PushBack(pCell->mPosition_504);
                }
            }

            SortKeys(params.mKeys_20.mpBegin, params.mKeys_20.mpEnd);
            Key3* pNewEnd = UniqueKeys(params.mKeys_20.mpBegin, params.mKeys_20.mpEnd);
            params.mKeys_20.Erase(pNewEnd, params.mKeys_20.mpEnd);

            FUN_00c71560(pPlanet, -9);
            FUN_00c73310(pPlanet);
            FUN_00c73330(pPlanet);
            StarManager()->BuildTribeSites(pTree, &params);
            void* pSiteOwner;
            if (FUN_00c70c00(pPlanet))
                pSiteOwner = pPlanet;
            else
                pSiteOwner = pPlanet;
            FUN_00c82f80(pSiteOwner);

            if (BlockIsAllocated(params.mPoints_34.mpBegin))
                operator_delete_array(params.mPoints_34.mpBegin);
            if (BlockIsAllocated(params.mKeys_20.mpBegin))
                operator_delete_array(params.mKeys_20.mpBegin);
        }
    } else if (newMode == 0x1654c02 && previousMode == 0xdbdba1) {
        cPoly* pInput = GameInputManager();
        --((u32*)pInput)[0x110 / 4];
        FUN_00cc8940(mpDisplayStrategy_234, 1);
        FUN_00cc93b0(mpDisplayStrategy_234, 1);
    }

    switch (newMode) {
    case 0x1654c02:
        break;
    case 0x1654c03:
    case 0x1654c07:
    case 0x1654c08:
        gTribeTuningData.Init();
        LoadTribeToolData();
        LoadTribeArchetypeData();
        break;
    }

    Refresh();
}

// @ 0x00cdd960
s32 FUN_00cdd960()
{
    void* pTribe = NounManager()->GetPlayerTribe();
    PtrVec<cNoun>* pItems =
        &((NounVecOut<cNoun>*)NounManager()->GetGameDataVector(F_cd7d10, F_d3d420, F_accc30, F_b1e500, 0x1be418e))->mItems_04;

    cNoun** pIt = pItems->mpBegin;
    cNoun** const pEnd = pItems->mpEnd;
    s32 nResult = (s32)pItems;
    while (pIt != pEnd) {
        nResult = (s32)FUN_00cd4770(*pIt, pTribe);
        ++pIt;
    }
    return nResult;
}

// @ 0x00cdd9c0
s32 FUN_00cdd9c0(bool bBuildInstances)
{
    cPropertyList* pList = 0;
    cPoly* pPropertyManager = PropertyManager();
    VSLOT(void (__thiscall*)(cPoly*, u32, u32, cPropertyList**), pPropertyManager, 0x2c)
        (pPropertyManager, 0x535dc193, 0x2be764e2, &pList);

    float fProperty = GetPropertyFloat(pList, 0x49b71de, gMinTribeRadius);
    float fValue = gMinTribeRadius > fProperty ? gMinTribeRadius : fProperty;

    cPlanetModel* pModel = (cPlanetModel*)GetPlanetModel();
    cRenderEntity* pEntity = pModel->mpEntity_024;
    cTerraformingManager* pTerra = (cTerraformingManager*)GetTerraformingManager();

    NounVecOut<cNoun>* pVec =
        (NounVecOut<cNoun>*)NounManager()->GetGameDataVector(F_cd7d10, F_d3d420, F_ace070, F_b1e500, 0x36be27e);
    s32 nCount = 0;
    cNoun** pIt = pVec->mItems_04.mpBegin;
    cNoun** const pEnd = pVec->mItems_04.mpEnd;
    while (pIt != pEnd) {
        cNoun* pNoun = *pIt;
        if (pNoun->mNounType_108 == 0x57f09e5e) {
            ++nCount;
            pNoun->mTerraformSlot_11c = pTerra->AddPoke(pNoun->mPlacement_034.GetPosition(), fValue);

            if (bBuildInstances) {
                ModelInstance instance;
                instance.mFlags_00 = 0;
                instance.mCount_02 = 0;
                instance.mOrigin_04 = gDefaultOrigin;
                instance.mScale_10 = gModelScale;
                instance.mRotation_14 = gDefaultRotation;
                instance.mRotation_14 = Matrix3FromQuaternion(pNoun->mPlacement_034.GetRotation());
                instance.mFlags_00 |= 2;
                ++instance.mCount_02;
                instance.mOrigin_04 = *pNoun->mPlacement_034.GetPosition();
                instance.mFlags_00 |= 4;
                ++instance.mCount_02;
                pEntity->AddInstance(&instance, pList);
            }
        }
        ++pIt;
    }

    cSurfaceCellList* pSurface = gSurfaceCellList;
    s32 nCells = pSurface->mpEnd_30 - pSurface->mpBegin_2c;
    for (s32 i = 0; i < nCells; ++i)
        pTerra->AddSurfacePoint(&pSurface->mpBegin_2c[i], 0);
    pTerra->Commit();

    if (pList != 0)
        pList->Release();
    return nCount;
}

// @ 0x00cddcf0
void FUN_00cddcf0()
{
    struct HotSpotQuery { float mMaxDistance; Vec3 mPoint; };
    HotSpotQuery query;
    query.mMaxDistance = gHotSpotDistance;

    NounVecOut<cNoun>* pVec =
        (NounVecOut<cNoun>*)NounManager()->GetGameDataVector(F_cd7d10, F_d3d420, F_ace070, F_b1e500, 0x36be27e);
    cNoun** pIt = pVec->mItems_04.mpBegin;
    cNoun** const pEnd = pVec->mItems_04.mpEnd;
    while (pIt != pEnd) {
        cNoun* pNoun = *pIt;
        if (pNoun->mNounType_108 == 0x57f09e5e) {
            cPlanetModel* pModel = (cPlanetModel*)GetPlanetModel();
            if (pModel->RayCast(pNoun->mPlacement_034.GetPosition(), query.mMaxDistance,
                                &query.mPoint, 1.0f, 1, 5))
                cTribe_SetupHotSpot(&query.mPoint, 1);
        }
        ++pIt;
    }
}

// @ 0x00cddda0
void cTribeModeStrategy::ContinueLoading()
{
    if (mpLoadingStrategy_240 != 0) {
        mpLoadingStrategy_240->Deactivate();
        if (mpLoadingStrategy_240 != 0) {
            RefCounted* pRef = &mpLoadingStrategy_240->mRef_3c;
            mpLoadingStrategy_240 = 0;
            pRef->Release();
        }
    }

    cTribe* pTribe = (cTribe*)NounManager()->GetPlayerTribe();
    if (pTribe != 0) {
        cPoly* pCursor = GetGameTerrainCursor();
        VSLOT(void (__thiscall*)(cPoly*, u32), pCursor, 0x58)
            (pCursor, VSLOT(u32 (__thiscall*)(cTribe*), pTribe, 0x94)(pTribe));
    }

    String16 name;
    name.SetEmpty();
    cPoly* pProfile = VSLOT(cPoly* (__thiscall*)(cTribe*, s32), pTribe, 0x00)(pTribe, 0);
    ((cSpeciesProfile*)pProfile)->GetUiName(&name);

    float fDistance = 0.0f;

    NounVecOut<cNoun>* pVec =
        (NounVecOut<cNoun>*)NounManager()->GetGameDataVector(F_cd7d10, F_d3d420, F_accbb0, F_b1e500, 0x18c6d19);
    cNounScratch scratch;
    scratch.Build((s32)(pVec->mItems_04.mpEnd - pVec->mItems_04.mpBegin), &pVec->mItems_04.mpCap);

    void** pRemovedEnd = 0;
    FUN_00829110(&pRemovedEnd, (void**)pVec->mItems_04.mpBegin,
                 (void**)pVec->mItems_04.mpEnd, scratch.mpBegin, pTribe);

    for (void** pIt = scratch.mpBegin; pIt != pRemovedEnd; ++pIt) {
        cNoun* pNoun = (cNoun*)*pIt;
        cTribeWorkArea* pArea = &pNoun->mWorkArea_120;
        const Vec3* pCenter = pArea->GetCenter();
        pArea->Transform(pCenter);
        float fSq = pCenter->x * pCenter->x + pCenter->y * pCenter->y + pCenter->z * pCenter->z;
        bool bPrime = pArea->IsPrime();
        if (bPrime)
            fDistance = sqrtf(fSq);

        PtrVec<cPoly> linked;
        pNoun->GetLinkedObjects(&linked);
        for (cPoly** pLinked = linked.mpBegin; pLinked != linked.mpEnd; ++pLinked) {
            cPoly* pEntry = *pLinked;
            if (pEntry == 0)
                continue;
            cPoly* pTool = VSLOT(cPoly* (__thiscall*)(cPoly*, u32), pEntry, 0x0c)(pEntry, 0x4f176642);
            if (pTool == 0)
                continue;
            if (bPrime)
                VSLOT(void (__thiscall*)(cPoly*, const void*), pTool, 0xe4)(pTool, &gPrimeToolLabel);
            else
                VSLOT(void (__thiscall*)(cPoly*, const void*), pTool, 0xe4)(pTool,
                    (const void*)FUN_00b6f0c0(pTribe->mpDisplayStrategy_234, pTribe->mpDisplayStrategy_234));
            FUN_00c0d950(pTool, !bPrime);
        }
    }

    for (void** pIt = scratch.mpBegin; pIt != pRemovedEnd; ++pIt) {
        cTribe* pLoaded = (cTribe*)*pIt;
        pLoaded->UpdateGridAndHutArea(fDistance);
        pLoaded->ResetToolLayout();
        pLoaded->ReserveToolsSlots(true);
        FUN_00b6f380(&pLoaded->mNamedInserter_230, &name);

        ToolNode* pNode;
        if (pLoaded == pTribe)
            pNode = pLoaded->mToolTree_238.Find(0xe);
        else
            pNode = pLoaded->mToolTree_238.Find(0);
        pLoaded->mToolSlot_034.SetTool(pNode->mValue_14);
    }

    FUN_00cdd9c0(false);

    for (void** pIt = scratch.mpBegin; pIt != pRemovedEnd; ++pIt) {
        cPoly* pEntry = (cPoly*)*pIt;
        if (pEntry != 0)
            VSLOT(void (__thiscall*)(cPoly*), pEntry, 0x04)(pEntry);
    }
    if (BlockIsAllocated(scratch.mpBegin))
        operator_delete_array(scratch.mpBegin);
}

// I/O stream / reader used by the save reader below.
struct cIOReader {
    void** mpVtbl_00;
    u32 GetHandle()
    {
        return VSLOT(u32 (__thiscall*)(cIOReader*), this, 0x18)(this);
    }
};

struct cIOStream {
    void** mpVtbl_00;
    cIOReader* GetReader()
    {
        return VSLOT(cIOReader* (__thiscall*)(cIOStream*), this, 0x20)(this);
    }
};

inline u32 StreamHandle(cIOStream* pStream)
{
    return pStream->GetReader()->GetHandle();
}

// One entry of the player's saved vector list (20 bytes: vector + 8 bytes).
struct cPlayerRow {
    Vec3* mpBegin;
    Vec3* mpEnd;
    Vec3* mpCap;
    u32 mField_0c;
    u32 mField_10;

    void Resize(s32 nCount);                                     // 0x00473810
};

// The serializable base of cPlayer sits 12 bytes in front of cPlayer::Read's this.
struct cVarListOwner {
    u32 mPad_00;
    u32 mPad_04;
    u32 mPad_08;
};

struct cVarListSerializer {
    u32 mState_0000[0xa01 / 4];                                  // 0xa04-byte serializer state
    cVarListSerializer(const cVarListOwner* pOwner, u32 nId, u32 nKey); // 0x00692f90
    bool Serialize(cIOStream* pStream);                          // 0x00693e10
};

struct cSpaceInventory {
    void Configure(u32 nId, u32 nKey, u32 nFlags);               // 0x00599440
};

void ResizePlayerRows(cPlayerRow** ppRows, u32 nCount);          // 0x00cde0e0

struct cPlayer {
    u8 mPad_000[0x20];
    cPlayerRow* mpRows_020;
    u8 mPad_024[0x16c];
    cSpaceInventory* mpInventory_190;

    bool Read(cIOStream* pStream);                               // 0x00cde160
};

extern u32 gSpaceInventoryFlags;                                 // 0x0157f18c

// @ 0x00cde160
bool cPlayer::Read(cIOStream* pStream)
{
    u32 nVersion = 0;
    ReadInt32(StreamHandle(pStream), &nVersion, 1, 0);

    cVarListSerializer serializer((const cVarListOwner*)this - 1, 0x157f290, 0x1a80d26);
    if (nVersion != 0x116dd1b || !serializer.Serialize(pStream))
        return false;

    u32 nRows = 0;
    ReadInt32(StreamHandle(pStream), &nRows, 1, 0);
    ResizePlayerRows(&mpRows_020, nRows);

    for (u32 i = 0; i < nRows; ++i) {
        cPlayerRow* pRow = mpRows_020 + i;
        u32 nPoints = 0;
        ReadInt32(StreamHandle(pStream), &nPoints, 1, 0);
        pRow->Resize((s32)nPoints);
        for (u32 j = 0; j < nPoints; ++j)
            ReadInt32(StreamHandle(pStream), &pRow->mpBegin[j], 3, 0);
    }

    if (mpInventory_190 != 0)
        mpInventory_190->Configure(0xf71fa311, 0x4a5c4493, gSpaceInventoryFlags);
    return true;
}
