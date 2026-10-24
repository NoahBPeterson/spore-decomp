// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s0104e060.
//
// Space tool manager: tool creation from property lists, charge lookup,
// selection/activation helpers, the charge effect driver and the tool data
// copy/assignment plus the effect tree teardown.

typedef unsigned int size_t;
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long long uint64_t;
typedef int intptr_t;
#define nullptr 0

float sqrtf(float);
#define __builtin_sqrtf sqrtf

struct Vec3 {
    float mX;
    float mY;
    float mZ;
};

class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};

class cIVisualEffect : public IRefCounted {
public:
    virtual void v14(void* pConfig);
    virtual void v18(void* pParams);
    virtual void SetEnabled(int bEnabled);
    virtual void SetParamBlock(void* pBlock);
    virtual void v24();
    virtual void v28();
};

class cSpatialObject : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
};

class cInteraction : public IRefCounted {
public:
};

class cEffectInfo : public IRefCounted {
public:
    Vec3* GetPosition();
    void* GetOrientation();
};

class cPropertyList {
public:
    virtual void v00();
    virtual void Release();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual bool GetProperty(uint32_t nKey, void** ppOut);
};

class cSPSimulatorSpaceGame {
public:
    void* GetPlayerInventory();
};

class cInventory {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
};

class cSPTimer {
public:
    virtual void Start();                       // 0x00
    virtual void Stop();                        // 0x04
    virtual bool IsRunning();                   // 0x08
    virtual void SetElapsed(uint64_t nElapsed); // 0x0c
    virtual uint64_t GetElapsedTime();          // 0x10

    void* mVftable;                             // 0x00
    int mRefCount;                              // 0x04
    uint64_t mElapsedTime;                      // 0x08
    uint8_t mBaseTime;                          // 0x10
    uint8_t mPad11[0x03];                       // 0x11
    uint32_t mBaseTimeHigh;                     // 0x14
};

class cSPUISpace : public IRefCounted {
public:
    void UpdateToolChargeBar(float fFraction);
};

class cSPSpaceInventoryItem : public IRefCounted {
public:
    cSPSpaceInventoryItem* operator=(cSPSpaceInventoryItem* pOther);
    bool IsDeselectedAfterUse();

    uint8_t mPad08[0x74];                       // 0x08
    int mnCharges;                              // 0x7c
    cSPTimer mRechargeTimer;                    // 0x80
    cSPTimer mAutoFireTimer;                    // 0x98
    cSPTimer mChargeHoldTimer;                  // 0xb0
    uint8_t mPadC8[0x18];                       // 0xc8
    void* mpName;                               // 0xe0
};

class cSPSpaceToolData : public cSPSpaceInventoryItem {
public:
    cSPSpaceToolData();
    cSPSpaceToolData* CopyFrom(cSPSpaceToolData* pOther);
    void SetPropertyList(uint32_t nPropertyKey);
    void TryDeselectAfterUse();
    void ReloadItemEffects();
    bool NeedsCharges();
    void FreeEffectBuffers();

    uint8_t mPadE4[0x24];                       // 0xe4
    cIVisualEffect* mpEffectStage0;             // 0x108
    cIVisualEffect* mpEffectStage1;             // 0x10c
    cIVisualEffect* mpEffectStage2;             // 0x110
    cEffectInfo* mpEffectInfo;                  // 0x114
    uint8_t mPad118[0x4c];                      // 0x118
    uint32_t mDelayedValue;                     // 0x164
    uint8_t mPad168[0x0c];                      // 0x168
    uint32_t mFlags;                            // 0x174
    uint8_t mPad178[0x5c];                      // 0x178
    float mChargeTime;                          // 0x1d4
    cSpatialObject* mpToolTarget;               // 0x1d8
    cSpatialObject* mpArea;                     // 0x1dc
    cSpatialObject* mpBeam;                     // 0x1e0
    cInteraction* mpBehavior;                   // 0x1e4
    uint8_t mPriority;                          // 0x1e8
};

struct cEffectConfig {
    void* mVftable;                             // 0x00
    Vec3 mColor;                                // 0x04
    uint32_t mPhase0;                           // 0x10
    uint32_t mPhase1;                           // 0x14
    uint32_t mPhase2;                           // 0x18
    uint32_t mPhase3;                           // 0x1c
    uint32_t mPhase4;                           // 0x20
    uint32_t mPhase5;                           // 0x24
    uint8_t mChannelMask;                       // 0x28
};

struct cSpaceInventoryItemData {
    void* mVftable;                             // 0x00
    uint8_t mPad04[0x0c];                       // 0x04
    uint32_t mnItemId;                          // 0x10
    uint8_t mPad14[0x1c];                       // 0x14
    uint32_t mnFlags;                           // 0x30
};

struct cToolCategoryNode {
    void* mpKey;                                // 0x00
    void* mpCategory;                           // 0x04
    uint8_t mPad08[0x0c];                       // 0x08
    void* mpObject;                             // 0x14
};

struct cEffectNode {
    void* mpLeft;                               // 0x00
    void* mpRight;                              // 0x04
    uint8_t mPad08[0x08];                       // 0x08
    void* mpObject;                             // 0x10
    void* mpEffect;                             // 0x14
};

struct cEffectLists {
    void* mpList0[3];                           // 0x00
    void* mpList1[3];                           // 0x0c
    void* mpList2[3];                           // 0x18
    void* mpList3[3];                           // 0x24
    uint8_t mPad30[0x14];                       // 0x30
};

class cSPToolManager : public IRefCounted {
public:
    bool CreateToolFromToolID(uint32_t nToolId);
    int GetChargesForDiscoverableTool(uint32_t nToolId);
    void SelectTool(void* pTool, int nFlags, int bInstant);
    void ActivateToolEffect(void* pTool);
    void ShutdownGonzagoSubsystem();
    void ClearToolEffects();

    uint8_t mPad14[0xe4];                       // 0x14
    void* mpPropertyList;                       // 0xf8
    uint8_t mPadFc[0x0c];                       // 0xfc
    cSPSpaceInventoryItem* mpSelectedTool;      // 0x108
    uint8_t mPad10c[0x08];                      // 0x10c
    void* mpEffectTreeRoot;                     // 0x114
    uint8_t mPad118[0x08];                      // 0x118
    void* mpHandlerNode;                        // 0x120
};

class cToolManagerOwning {
public:
    cSPToolManager* mpToolManager;              // 0x00
    cSpatialObject* mpToolTarget;               // 0x04
};

void* operator_new(size_t nSize, const char* pName, int a, int b, int c, int d);
void* operator_new(size_t nSize, const char* pName, int a, int b, const char* pFile, int nLine);
void operator_delete__(void* pMemory);
void* PropertyManager();
void* App();
void* SpaceGameGet();
void* EffectsManager();
void* GetCurrentGameMode();
void* NounManager();
cSPUISpace* GetSpaceUI();
void* CreateEffectInfo();
void* CreateEffectParams(void* pParams);
void ResetGeometryVectors(void* pOut);
void UnusedGeometryHelper(void* pOut);
void ReadCameraBasis(float* pForward, float* pUp);
void ComputeToolEffectPosition(Vec3* pOut, float fX, float fY, float fZ, float fRange);
float ComputeChargeFraction(uint64_t nElapsed, int nChargeMs);
void* GetEffectParams();
void* GetEffectInfoBlock();
void DestroyToolCategoryNode(void* pNode);
void RemoveEffectFromTree(void* pRoot, void* pKey);
void AdvanceToolEffect(void* pEffect);
void UnregisterEffectHandler();
void EraseToolStrategies(void* pTable);
void RemoveMessageHandler(void* pHandler);
void ReleaseEffectHandler(void* pNode);
void* HashString8(const char* pString);
uint32_t RandomUint32Uniform(int nRange);
void SetToolProperty(uint32_t nToolId);
void SetToolInventoryItem(cSPSpaceInventoryItem* pItem);
void ReleaseInventoryItem(cSPSpaceInventoryItem* pItem);
bool HasToolProperty(uint32_t nItemId, uint32_t nKey, void* pOut);
cSPSpaceToolData* CreateToolData(void* pSource);
cSPSpaceToolData* AllocateToolData();
cSPSpaceToolData* ConstructToolData(void* pMemory);
cSPSpaceToolData* CreateToolDataCopy(cSPSpaceToolData* pSource);
void* JoinToolEffect(void* pTool);
void* GetToolEffectConfig(void* pObject);
bool SelectInventoryTool(void* pItem);
bool AddSelectedToolToInventory(void* pItem);

extern void* gRandomGenerator;
extern const float gToolEffectEulerX;
extern const float gToolEffectEulerY;
extern const float gToolEffectEulerZ;
extern const uint32_t gSpaceGameMode;

// ---------------------------------------------------------------------------
// 0x0104e060  SP::ComputeToolEffectPosition
// ---------------------------------------------------------------------------
// @ 0x0104e060
void ComputeToolEffectPosition(Vec3* pOut, float fX, float fY, float fZ, float fRange)
{
    if (fRange == -1.0f)
        fRange = 5000.0f;

    void* pApp = App();
    (void)pApp;

    Vec3 origin;
    Vec3 forward;
    ReadCameraBasis(&origin.mX, &forward.mX);

    float fDistance = (forward.mZ * (fZ - origin.mZ) + forward.mY * (fY - origin.mY)) +
                      (fX - origin.mX) * forward.mX;
    float fPointX = forward.mX * fDistance + origin.mX;
    float fPointY = forward.mY * fDistance + origin.mY;
    float fPointZ = forward.mZ * fDistance + origin.mZ;

    float fDx = fX - fPointX;
    float fDy = fY - fPointY;
    float fDz = fZ - fPointZ;
    float fLength = sqrtf(fDx * fDx + (fDy * fDy + fDz * fDz));
    if (fLength < fRange) {
        fDistance = sqrtf(fRange * fRange - fLength * fLength) + fDistance;
        pOut->mY = forward.mY * fDistance + origin.mY;
        pOut->mZ = forward.mZ * fDistance + origin.mZ;
        pOut->mX = forward.mX * fDistance + origin.mX;
        return;
    }

    fDz = fPointZ - fZ;
    fDy = fPointY - fY;
    fDx = fPointX - fX;
    float fScale = 1.0f / sqrtf(fDx * fDx + (fDy * fDy + fDz * fDz));
    pOut->mY = (fDy * fScale) * fRange + fY;
    pOut->mZ = (fDz * fScale) * fRange + fZ;
    pOut->mX = (fScale * fDx) * fRange + fX;
}

// ---------------------------------------------------------------------------
// 0x0104e260  SP::cSPToolManager::TryDeselectAfterUse
// ---------------------------------------------------------------------------
// @ 0x0104e260
void cSPSpaceToolData::TryDeselectAfterUse()
{
    if (!IsDeselectedAfterUse())
        return;

    cSPSimulatorSpaceGame* pSpaceGame = (cSPSimulatorSpaceGame*)SpaceGameGet();
    void* pInventory = pSpaceGame->GetPlayerInventory();
    if (pInventory != nullptr)
        ReleaseInventoryItem(this);
}

// ---------------------------------------------------------------------------
// 0x0104e290  SP::SetEffectConfig
// ---------------------------------------------------------------------------
// @ 0x0104e290
void SetEffectConfig(cEffectConfig* pConfig, uint32_t nChannel, const Vec3* pColor)
{
    pConfig->mPhase3 = 0;
    pConfig->mPhase4 = 0;
    pConfig->mPhase5 = 0;
    pConfig->mChannelMask = (uint8_t)(1 << (nChannel & 0x1f));
    pConfig->mColor.mX = pColor->mX;
    pConfig->mColor.mY = pColor->mY;
    pConfig->mColor.mZ = pColor->mZ;
    pConfig->mPhase2 = 0;
}

// ---------------------------------------------------------------------------
// 0x0104e2f0  Simulator::cSpaceInventoryItem::GetItemCount
// ---------------------------------------------------------------------------
// @ 0x0104e2f0
uint32_t cSpaceInventoryItem_GetItemCount(cSpaceInventoryItemData* pItem, uint32_t* pCount)
{
    if (((pItem->mnFlags >> 5) & 1) != 0)
        *pCount = pItem->mnItemId;
    return pItem->mnFlags >> 5 & 0xffffff01;
}

// ---------------------------------------------------------------------------
// 0x0104e320  SP::cSPSpaceToolData::NeedsCharges
// ---------------------------------------------------------------------------
// @ 0x0104e320
bool cSPSpaceToolData::NeedsCharges()
{
    if (((mFlags >> 5) & 1) != 0 && mnCharges < 1)
        return true;
    return false;
}

// ---------------------------------------------------------------------------
// 0x0104e340  SP::cSPToolManager::CreateToolFromToolID
// ---------------------------------------------------------------------------
// @ 0x0104e340
bool cSPToolManager::CreateToolFromToolID(uint32_t nToolId)
{
    cPropertyList* pPropertyManager = (cPropertyList*)PropertyManager();
    pPropertyManager->v2c();

    cSPSpaceToolData* pTool = AllocateToolData();
    pTool->SetPropertyList(0x30608f0bu);
    pTool->mFlags = 0;
    pTool->mnCharges = 1;

    uint32_t nValue = 0;
    if (HasToolProperty(0x30608f0bu, 0xf0609eceu, &nValue))
        pTool->mpName = (void*)(intptr_t)nValue;
    if (HasToolProperty(0x30608f0bu, 0xf0609ed9u, &nValue))
        pTool->mDelayedValue = nValue;

    mpSelectedTool = pTool;
    pTool->Release();
    SetToolProperty(nToolId);
    return true;
}

// ---------------------------------------------------------------------------
// 0x0104e470  SP::cSPToolManager::GetChargesForDiscoverableTool
// ---------------------------------------------------------------------------
// @ 0x0104e470
int cSPToolManager::GetChargesForDiscoverableTool(uint32_t nToolId)
{
    int nMin = 0;
    int nMax = 0;

    cPropertyList* pPropertyManager = (cPropertyList*)PropertyManager();
    cSPSpaceToolData* pTool = nullptr;
    pPropertyManager->v2c();

    uint32_t nValue = 0;
    if (HasToolProperty(nToolId, 0x2e06e31u, &nValue))
        nMin = (int)nValue;
    if (pTool != nullptr && HasToolProperty(nToolId, 0x2e06e36u, &nValue))
        nMax = (int)nValue;

    if (nMin != 0 && nMax != 0) {
        int nRandom = (int)RandomUint32Uniform(nMax - nMin);
        if (pTool != nullptr)
            pTool->Release();
        return nRandom + nMin;
    }
    if (pTool != nullptr)
        pTool->Release();
    return 1;
}

// ---------------------------------------------------------------------------
// 0x0104e570  SP::cSPToolManager::SelectTool
// ---------------------------------------------------------------------------
// @ 0x0104e570
void cSPToolManager::SelectTool(void* pTool, int nFlags, int bInstant)
{
    if (pTool == nullptr)
        return;

    void* pCandidate = nullptr;
    SelectInventoryTool(pTool);
    RemoveEffectFromTree(pCandidate, pTool);

    cSpatialObject* pObject = (cSpatialObject*)pCandidate;
    if (pObject != nullptr) {
        uint32_t nValue = 0;
        (void)nValue;
        bool bAdded = AddSelectedToolToInventory(pCandidate);
        if (mpSelectedTool != nullptr || bAdded) {
            mpEffectTreeRoot = (void*)&pObject;
            if (!bAdded)
                mpEffectTreeRoot = (void*)((uint8_t*)mpEffectTreeRoot - 4);
        }
    }
    (void)nFlags;
    (void)bInstant;
}

// ---------------------------------------------------------------------------
// 0x0104e620  SP::cSPToolManager::ActivateToolEffect
// ---------------------------------------------------------------------------
// @ 0x0104e620
void cSPToolManager::ActivateToolEffect(void* pTool)
{
    if (pTool == nullptr)
        return;

    void* pEffect = nullptr;
    void* pObject = JoinToolEffect(pTool);
    if (pObject != nullptr) {
        bool bAdded = AddSelectedToolToInventory(pObject);
        if (mpSelectedTool != nullptr || bAdded) {
            void* pConfig = nullptr;
            pConfig = GetToolEffectConfig(pObject);
            mpEffectTreeRoot = (void*)&mpSelectedTool;
            if (!bAdded)
                mpEffectTreeRoot = (void*)((uint8_t*)mpEffectTreeRoot - 4);
        }
    }
    (void)pEffect;
}

// ---------------------------------------------------------------------------
// 0x0104e6f0  SP::cSPSpaceToolData::FreeEffectBuffers
// ---------------------------------------------------------------------------
// @ 0x0104e6f0
void cSPSpaceToolData::FreeEffectBuffers()
{
    uint8_t** ppBlock = (uint8_t**)this;
    if (ppBlock[0xf] != nullptr && *(int*)(ppBlock[0xf] - 4) != 0)
        operator_delete__(ppBlock[0xf]);
    if (ppBlock[10] != nullptr && *(int*)(ppBlock[10] - 4) != 0)
        operator_delete__(ppBlock[10]);
    if (ppBlock[5] != nullptr && *(int*)(ppBlock[5] - 4) != 0)
        operator_delete__(ppBlock[5]);
    if (ppBlock[0] != nullptr && *(int*)(ppBlock[0] - 4) != 0)
        operator_delete__(ppBlock[0]);
}

// ---------------------------------------------------------------------------
// 0x0104e7b0  Simulator::CreateToolCategoryNode
// ---------------------------------------------------------------------------
// @ 0x0104e7b0
cToolCategoryNode* CreateToolCategoryNode(cToolManagerOwning* pOwner)
{
    cToolCategoryNode* pNode = (cToolCategoryNode*)
        (intptr_t)operator_new(0x18, "Simulator", 0, 0,
                               "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                               0xd1);
    pOwner = pOwner;
    pNode->mpKey = pOwner->mpToolManager;
    if (pOwner->mpToolManager != nullptr)
        pOwner->mpToolManager->AddRef();
    pNode->mpObject = pOwner->mpToolTarget;
    if (pOwner->mpToolTarget != nullptr)
        pOwner->mpToolTarget->AddRef();
    return pNode;
}

// ---------------------------------------------------------------------------
// 0x0104e810  SP::cSPSpaceToolData::operator=
// ---------------------------------------------------------------------------
// @ 0x0104e810
cSPSpaceToolData* cSPSpaceToolData::CopyFrom(cSPSpaceToolData* pOther)
{
    cSPSpaceInventoryItem::operator=(pOther);
    if (this == pOther)
        return this;

    mRechargeTimer.mVftable = pOther->mRechargeTimer.mVftable;
    mRechargeTimer.mRefCount = pOther->mRechargeTimer.mRefCount;
    mRechargeTimer.mElapsedTime = pOther->mRechargeTimer.mElapsedTime;
    mRechargeTimer.mBaseTime = pOther->mRechargeTimer.mBaseTime;
    mRechargeTimer.mBaseTimeHigh = pOther->mRechargeTimer.mBaseTimeHigh;

    mAutoFireTimer.mVftable = pOther->mAutoFireTimer.mVftable;
    mAutoFireTimer.mRefCount = pOther->mAutoFireTimer.mRefCount;
    mAutoFireTimer.mElapsedTime = pOther->mAutoFireTimer.mElapsedTime;
    mAutoFireTimer.mBaseTime = pOther->mAutoFireTimer.mBaseTime;
    mAutoFireTimer.mBaseTimeHigh = pOther->mAutoFireTimer.mBaseTimeHigh;

    mChargeHoldTimer.mVftable = pOther->mChargeHoldTimer.mVftable;
    mChargeHoldTimer.mRefCount = pOther->mChargeHoldTimer.mRefCount;
    mChargeHoldTimer.mElapsedTime = pOther->mChargeHoldTimer.mElapsedTime;
    mChargeHoldTimer.mBaseTime = pOther->mChargeHoldTimer.mBaseTime;
    mChargeHoldTimer.mBaseTimeHigh = pOther->mChargeHoldTimer.mBaseTimeHigh;

    if (mpEffectStage1 != pOther->mpEffectStage1) {
        if (pOther->mpEffectStage1 != nullptr)
            pOther->mpEffectStage1->AddRef();
        mpEffectStage1 = pOther->mpEffectStage1;
        if (mpEffectStage1 != nullptr)
            mpEffectStage1->Release();
    }

    if (mpName != pOther->mpName) {
        if (pOther->mpName != nullptr)
            ((cIVisualEffect*)pOther->mpName)->AddRef();
        mpName = pOther->mpName;
        if (mpName != nullptr)
            ((cIVisualEffect*)mpName)->Release();
    }

    mPriority = pOther->mPriority;

    if (mpToolTarget != pOther->mpToolTarget) {
        if (pOther->mpToolTarget != nullptr)
            pOther->mpToolTarget->AddRef();
        mpToolTarget = pOther->mpToolTarget;
        if (mpToolTarget != nullptr)
            mpToolTarget->Release();
    }

    if (mpArea != pOther->mpArea) {
        if (pOther->mpArea != nullptr)
            pOther->mpArea->AddRef();
        mpArea = pOther->mpArea;
        if (mpArea != nullptr)
            mpArea->Release();
    }

    if (mpBeam != pOther->mpBeam) {
        if (pOther->mpBeam != nullptr)
            pOther->mpBeam->AddRef();
        mpBeam = pOther->mpBeam;
        if (mpBeam != nullptr)
            mpBeam->Release();
    }

    if (mpBehavior != pOther->mpBehavior) {
        if (pOther->mpBehavior != nullptr)
            pOther->mpBehavior->AddRef();
        mpBehavior = pOther->mpBehavior;
        if (mpBehavior != nullptr)
            mpBehavior->Release();
    }

    ReloadItemEffects();
    return this;
}

// ---------------------------------------------------------------------------
// 0x0104ea40  SP::CreateToolDataCopy
// ---------------------------------------------------------------------------
// @ 0x0104ea40
cSPSpaceToolData* CreateToolDataCopy(cSPSpaceToolData* pSource)
{
    cSPSpaceToolData* pTool = (cSPSpaceToolData*)
        (intptr_t)operator_new(0x2a0, "Simulator/cSpaceToolData", 0, 0, 0, 0);
    if (pTool == nullptr)
        return nullptr;

    pTool = ConstructToolData(pTool);
    if (pTool != nullptr)
        pTool->CopyFrom(pSource);
    return pTool;
}

// ---------------------------------------------------------------------------
// 0x0104ea80  DoChargeEffects
// ---------------------------------------------------------------------------
// @ 0x0104ea80
void DoChargeEffects(cSPSpaceToolData* pTool)
{
    uint32_t nChargeMs = (uint32_t)(pTool->mChargeTime * 1000.0f);
    if (!pTool->mChargeHoldTimer.IsRunning())
        return;

    cEffectConfig config;
    config.mColor.mX = gToolEffectEulerX;
    config.mColor.mY = gToolEffectEulerY;
    config.mColor.mZ = gToolEffectEulerZ;
    config.mPhase3 = 0;
    config.mPhase4 = 0;
    config.mPhase5 = 0;

    cEffectInfo* pEffectInfo = pTool->mpEffectInfo;
    config.mPhase0 = (uint32_t)(intptr_t)pEffectInfo->GetOrientation();
    config.mPhase1 = (uint32_t)(intptr_t)pEffectInfo->GetPosition();
    config.mPhase2 = (uint32_t)(intptr_t)GetEffectInfoBlock();

    if (GetCurrentGameMode() == &gSpaceGameMode) {
        uint64_t nElapsed = pTool->mChargeHoldTimer.GetElapsedTime();
        float fFraction = (float)nElapsed / (float)(int)nChargeMs;
        cSPUISpace* pSpaceUI = GetSpaceUI();
        pSpaceUI->UpdateToolChargeBar(fFraction);
    }

    uint64_t nElapsed = pTool->mChargeHoldTimer.GetElapsedTime();
    if (nElapsed < (uint64_t)(int)nChargeMs / 3) {
        if (pTool->mpEffectStage0 == nullptr) {
            if (pTool->mpEffectStage0 != nullptr) {
                pTool->mpEffectStage0->Release();
                pTool->mpEffectStage0 = nullptr;
            }
            if (CreateEffectInfo() != nullptr) {
                pTool->mpEffectStage0->v14(&config);
                pTool->mpEffectStage0->v18(&nChargeMs);
                pTool->mpEffectStage0->SetEnabled(0);
            }
        }
    } else if (nElapsed < (uint64_t)(int)(nChargeMs * 2) / 3) {
        if (pTool->mpEffectStage1 == nullptr) {
            if (pTool->mpEffectStage1 != nullptr) {
                pTool->mpEffectStage1->Release();
                pTool->mpEffectStage1 = nullptr;
            }
            if (CreateEffectInfo() != nullptr) {
                pTool->mpEffectStage1->v14(&config);
                pTool->mpEffectStage1->v18(&nChargeMs);
                pTool->mpEffectStage1->SetEnabled(0);
            }
            if (pTool->mpEffectStage0 != nullptr) {
                pTool->mpEffectStage0->SetEnabled(0);
                pTool->mpEffectStage0->Release();
                pTool->mpEffectStage0 = nullptr;
            }
        }
    } else if (nElapsed < (uint64_t)nChargeMs) {
        if (pTool->mpEffectStage2 == nullptr) {
            if (CreateEffectInfo() != nullptr) {
                pTool->mpEffectStage2->v14(&config);
                pTool->mpEffectStage2->v18(&nChargeMs);
                pTool->mpEffectStage2->SetEnabled(0);
            }
            if (pTool->mpEffectStage1 != nullptr) {
                pTool->mpEffectStage1->SetEnabled(0);
                pTool->mpEffectStage1->Release();
                pTool->mpEffectStage1 = nullptr;
            }
        }
    }

    cIVisualEffect** ppEffect = &pTool->mpEffectStage0;
    for (int i = 0; i < 3; ++i) {
        if (*ppEffect != nullptr)
            (*ppEffect)->v18(&config);
        ++ppEffect;
    }
}

// ---------------------------------------------------------------------------
// 0x0104ef00  SP::ClearEffectLists
// ---------------------------------------------------------------------------
// @ 0x0104ef00
void ClearEffectLists(cEffectLists* pLists)
{
    pLists->mpList0[0] = nullptr;
    pLists->mpList0[1] = nullptr;
    pLists->mpList0[2] = nullptr;
    pLists->mpList1[0] = nullptr;
    pLists->mpList1[1] = nullptr;
    pLists->mpList1[2] = nullptr;
    pLists->mpList2[0] = nullptr;
    pLists->mpList2[1] = nullptr;
    pLists->mpList2[2] = nullptr;
    pLists->mpList3[0] = nullptr;
    pLists->mpList3[1] = nullptr;
    pLists->mpList3[2] = nullptr;
}

// ---------------------------------------------------------------------------
// 0x0104ef30  SP::EraseEffectTree
// ---------------------------------------------------------------------------
// @ 0x0104ef30
void EraseEffectTree(cEffectNode* pNode)
{
    while (pNode != nullptr) {
        void* pNext = pNode->mpRight;
        ReleaseEffectHandler(pNode);
        if (pNode->mpEffect != nullptr)
            ((cIVisualEffect*)pNode->mpEffect)->v08();
        if (pNode->mpObject != nullptr)
            ((cIVisualEffect*)pNode->mpObject)->Release();
        operator_delete__(pNode);
        pNode = (cEffectNode*)pNext;
    }
}

// ---------------------------------------------------------------------------
// 0x0104f1f0  SP::cSPToolManager::ShutdownGonzagoSubsystem
// ---------------------------------------------------------------------------
// @ 0x0104f1f0
void cSPToolManager::ShutdownGonzagoSubsystem()
{
    EraseToolStrategies(this);
    mpHandlerNode = nullptr;
    if (mpHandlerNode != nullptr) {
        void* pHandler = mpHandlerNode;
        mpHandlerNode = nullptr;
        RemoveMessageHandler(pHandler);
    }
}

// ---------------------------------------------------------------------------
// 0x0104f250  SP::cSPToolManager::ClearToolEffects
// ---------------------------------------------------------------------------
// @ 0x0104f250
void cSPToolManager::ClearToolEffects()
{
    cEffectNode* pNode = (cEffectNode*)mpEffectTreeRoot;
    while (pNode != (cEffectNode*)this) {
        if (pNode->mpEffect != nullptr)
            ((cIVisualEffect*)pNode->mpEffect)->SetEnabled(1);
        pNode = (cEffectNode*)pNode->mpRight;
    }

    EraseEffectTree((cEffectNode*)mpEffectTreeRoot);
    mpEffectTreeRoot = (void*)this;
    pNode = (cEffectNode*)mpEffectTreeRoot;
    pNode->mpRight = (void*)pNode;
    mpEffectTreeRoot = nullptr;
}
