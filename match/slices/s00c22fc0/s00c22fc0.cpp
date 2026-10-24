// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00c22fc0.
//
// Creature citizen bundle placement and tool selection, the creature base
// identity color / tool lookup helpers and the tribe tool interaction scan.

typedef unsigned int size_t;
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long long uint64_t;
typedef int intptr_t;
#define nullptr 0

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

class cSPTimer {
public:
    virtual void Start();
    virtual void Stop();
    virtual bool IsRunning();
    virtual void SetElapsed(uint64_t nElapsed);
    virtual uint64_t GetElapsedTime();

    void* mVftable;                             // 0x00
    int mRefCount;                              // 0x04
    uint64_t mElapsedTime;                      // 0x08
    uint8_t mBaseTime;                          // 0x10
    uint8_t mPad11[0x03];                       // 0x11
    uint32_t mBaseTimeHigh;                     // 0x14
};

class cSpatialObject : public IRefCounted {
public:
    Vec3* GetPosition();
};

class cPlanetModel {
public:
    void DirectionToSurfacePosition(const Vec3* pDirection, Vec3* pOut);
    void GetSurfacePoint(const Vec3* pPoint, Vec3* pOut, float fHeight);
};

class cSpeciesProfile {
public:
    float GetScaleModifier();
};

class cBundle {
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
    virtual void SetRotation(const Vec3* pRotation);
    virtual void SetPosition(const Vec3* pPosition);
};

class cToolOwner {
public:
    void* GetOwnerCreature();
    Vec3* GetColor();
};

class cCreatureBase : public cSpatialObject {
public:
    Vec3* GetIdentityColor();
    Vec3* GetActiveToolColor();
    void* GetToolById(int nToolId);
    void* GetActiveTool();
    void SetToolTarget(float fX, float fY, float fZ);
    void SetCasted(bool bCasted);
    float CalculateScale();
    char ApplyAttack(void* pTarget, void* pAttack, void* pContext);

    uint8_t mPad04[0x30];                       // 0x04
    cSpatialObject* mpSpatialObject;            // 0x34
    uint8_t mPad38[0x3d];                       // 0x38
    uint8_t mbCastedFlag;                       // 0x75
    uint8_t mPad76[0x4a];                       // 0x76
    uint8_t* mpIdentityColorSource;             // 0xc0
    uint8_t mPadC4[0x0c];                       // 0xc4
    uint8_t mPadD0[0x40];                       // 0xd0
    cSpeciesProfile* mpSpeciesProfile;          // 0x110
    uint8_t mPad114[0x80c];                     // 0x114
    void* mpToolTable;                          // 0x920
    uint8_t mPad924[0x6de];                     // 0x924
    uint8_t mbIsCastTarget;                     // 0x1002
    uint8_t mPad1003;                           // 0x1003
    float mfToolTargetX;                        // 0x1004
    float mfToolTargetY;                        // 0x1008
    float mfToolTargetZ;                        // 0x100c
    void* mpActiveTool;                         // 0x1010
    void* mpPendingTool;                        // 0x1014
    uint8_t mPad1018[0x14];                     // 0x1018
    void* mpInteractionState;                   // 0x102c
};

class cSPCreatureBase : public cCreatureBase {
public:
    uint32_t GetCurrentAnimationGUID(uint32_t* pFlags);
    void PerformSocialAction(int nMode, uint32_t nAnimation);
};

class cSPCreatureCitizen : public cSPCreatureBase {
public:
    void SetBundlePlacement(cBundle* pBundle);
    Vec3* GetBundlePosition(Vec3* pOut);
    bool IsLeader();
    bool IsBefriended();
    int GetToolEffect(uint32_t nToolId);
    bool HasSpecializedTool(int nToolId);

    uint8_t mPad1030[0x10];                     // 0x1030
    uint32_t mnIdentity;                        // 0x1040
    uint8_t mPad1044[0x11c];                    // 0x1044
    uint8_t mbBundleHidden;                     // 0x1160
    uint8_t mPad1161[0x3d];                     // 0x1161
    void* mpBundle;                             // 0x119e
};

class cGameNounManager : public IRefCounted {
public:
    void* GetPlayerTribe();
    void RemoveNoun(void* pNoun);
};

class cCommunity {
public:
    static void* GetLeader();
};

class cTimerOwner {
public:
    uint8_t mPad00[0x18];                       // 0x00
    cSPTimer mSocialTimer;                      // 0x18
    uint8_t mPad30[0x28];                       // 0x30
    Vec3 mTargetPosition;                       // 0x58
};

void* operator_new(size_t nSize);
void operator_delete__(void* pMemory);
void* PlanetModelGet();
void* NounManager();
void* GetCurrentGameMode();
void* GetCreatureRoot();
float GetRandomFloat(float fMin, float fMax);
void PreserveAnimation(uint32_t nAnimationGuid, uint32_t nFlags);
void PlayCreatureSocialAnimation(int a, int b, void* pCreature, float fSpeed, void* pParams, int c);
void* GetCreatureBehaviour(int nMode);
void SetCreatureFacing(void* pCreature, float fYaw);
void TimerReset(cSPTimer* pTimer);
uint64_t cSPTimerGetElapsedTime(cSPTimer* pTimer);
void* GetCreatureToolSlot(int a, int b, int c, int d);
void QueueCreatureInteraction(int a, int b, int c);
void* CreateInteractionEffect(int nFlags, int a, float fValue, void* pOwner);
void* GetCreatureSocialTarget(void* pCreature);
void ReportInteraction(uint32_t nType, void* pEffect);
bool IsToolUsable(void* pTool, float fA, float fB);
int CompareCreatureTraits(void* pA, void* pB, int nMode);
void* FindToolInventoryItem(int nKey, void** ppParams);
int GetCreatureActionState(void* pCreature);
int GetCreatureType(void* pCreature);
float GetCreatorScaleModifier(cSpeciesProfile* pProfile);
float ApplyCreatureScale(int nCharacterLevel, float fScale);
float GetCreatureObjectScale(void* pCreature);
char IsCitizenLeader(void* pCreature);
uint32_t GetLeaderOfCommunity();
int GetCreatureSocialRelation(void* pA, void* pB, int nMode);
void* GetCreatureToolByKey(uint32_t nKey);
bool IsCreatureVisibleInUI(void* pCreature);
bool IsCreatureLeader(void* pCreature);
char ApplyAttackEffect(void* pTarget, void* pAttack, void* pContext);
void* GetCreatureChain(void* pCreature);
bool HasCreatureTribeFlag(void* pCreature);
uint32_t GetCreatureAttackKind(void* pOwner, uint32_t nKey);
void RunCreatureAttackEffect(void* pCreature);
void PlayToolEffect(int a, void* pTarget, void* pOwner);

extern void* gPlanetModel;
extern uint8_t gDefaultIdentityColor[0x10];
extern float gLeaderScaleBonus;
extern float gFollowerScaleBonus;
extern void* gCreatureToolContext;
extern void* gToolInventoryTable;
extern float gCreatureToolRange;
extern float gMaxFloat;

// ---------------------------------------------------------------------------
// 0x00c22fc0  SP::cSPCreatureCitizen::SetBundlePlacement
// ---------------------------------------------------------------------------
// @ 0x00c22fc0
void cSPCreatureCitizen::SetBundlePlacement(cBundle* pBundle)
{
    if (pBundle == nullptr || mbBundleHidden != 0)
        return;

    Vec3 position;
    Vec3* pOrigin = ((cSpatialObject*)mpSpatialObject)->GetPosition();
    position.mX = pOrigin->mX;
    position.mY = pOrigin->mY;
    position.mZ = pOrigin->mZ;

    Vec3 offset;
    Vec3* pOffset = GetBundlePosition(&offset);
    position.mX = position.mX + pOffset->mX;
    position.mY = pOffset->mY + position.mY;
    position.mZ = pOffset->mZ + position.mZ;

    Vec3 surface;
    cPlanetModel* pPlanet = (cPlanetModel*)PlanetModelGet();
    pPlanet->DirectionToSurfacePosition(&position, &surface);

    Vec3 height;
    cPlanetModel* pPlanet2 = (cPlanetModel*)PlanetModelGet();
    pPlanet2->GetSurfacePoint(&surface, &height, 5.0f);

    Vec3 placement;
    placement.mX = height.mX;
    placement.mY = height.mY;
    placement.mZ = height.mZ;

    pBundle->SetPosition(&placement);
    pBundle->SetRotation(&position);
}

// ---------------------------------------------------------------------------
// 0x00c23110  SP::cSPCreatureCitizen::GetBundlePosition
// ---------------------------------------------------------------------------
// @ 0x00c23110
Vec3* cSPCreatureCitizen::GetBundlePosition(Vec3* pOut)
{
    if (mbBundleHidden == 0) {
        Vec3* pPosition = ((cSpatialObject*)mpSpatialObject)->GetPosition();
        pOut->mX = pPosition->mX;
        pOut->mY = pPosition->mY;
        pOut->mZ = pPosition->mZ;
        float fOffsetY = mfToolTargetY;
        float fOffsetZ = mfToolTargetZ;
        pOut->mX = pOut->mX + mfToolTargetX;
        pOut->mY = fOffsetY + pOut->mY;
        pOut->mZ = fOffsetZ + pOut->mZ;
        return pOut;
    }

    void* pCreature = GetCreatureChain(this);
    void* pPart = nullptr;
    if (pCreature != nullptr)
        pPart = GetCreatureRoot();
    if (pPart != nullptr) {
        Vec3 orientation;
        GetBundlePosition(pOut);
        pOut->mX = orientation.mX;
        return pOut;
    }

    Vec3* pPosition = ((cSpatialObject*)mpSpatialObject)->GetPosition();
    pOut->mX = pPosition->mX;
    pOut->mY = pPosition->mY;
    pOut->mZ = pPosition->mZ;
    return pOut;
}

// ---------------------------------------------------------------------------
// 0x00c23200  Simulator::cCreatureBase::GetIdentityColor
// ---------------------------------------------------------------------------
// @ 0x00c23200
Vec3* cCreatureBase::GetIdentityColor()
{
    if (mpActiveTool != nullptr)
        return ((cToolOwner*)mpActiveTool)->GetColor();
    if (mpPendingTool != nullptr) {
        Vec3* pColor = (Vec3*)(intptr_t)GetCreatureToolByKey(*(uint32_t*)((uint8_t*)mpPendingTool + 0x234));
        return pColor;
    }
    return (Vec3*)&gDefaultIdentityColor[0];
}

// ---------------------------------------------------------------------------
// 0x00c23230  Simulator::cCreatureBase::GetToolById
// ---------------------------------------------------------------------------
// @ 0x00c23230
void* cCreatureBase::GetToolById(int nToolId)
{
    int nIndex = GetCreatureActionState(&nToolId);
    if (nIndex != -1)
        return *(void**)((uint32_t*)mpToolTable + nIndex);

    if (mpInteractionState != nullptr) {
        void* pSlot = GetCreatureToolSlot((int)(intptr_t)mpInteractionState, 0, 0, 0);
        void* pEntry = *(void**)((uint8_t*)pSlot + 0x24);
        if (pEntry != nullptr && *(int*)((uint8_t*)pEntry + 8) == nToolId)
            return pEntry;
    }
    return nullptr;
}

// ---------------------------------------------------------------------------
// 0x00c23290  Simulator::cCreatureBase::GetActiveTool
// ---------------------------------------------------------------------------
// @ 0x00c23290
void* cCreatureBase::GetActiveTool()
{
    void* pTool = mpActiveTool;
    if (pTool == nullptr)
        pTool = mpPendingTool;
    return pTool;
}

// ---------------------------------------------------------------------------
// 0x00c232d0  SP::cSPCreatureCitizen::IsLeader
// ---------------------------------------------------------------------------
// @ 0x00c232d0
bool cSPCreatureCitizen::IsLeader()
{
    cToolOwner* pTool = (cToolOwner*)mpActiveTool;
    if (pTool == nullptr) {
        pTool = (cToolOwner*)mpPendingTool;
        if (pTool == nullptr)
            return false;
    }
    return pTool->GetOwnerCreature() == this;
}

// ---------------------------------------------------------------------------
// 0x00c23300  SP::cSPCreatureBase::PerformSocialAction
// ---------------------------------------------------------------------------
// @ 0x00c23300
void cSPCreatureBase::PerformSocialAction(int nMode, uint32_t nAnimation)
{
    void* pSpatial = mpSpatialObject;
    int nEffect = (**(int (__stdcall***)(void))(*(uint8_t**)pSpatial + 0xac))();

    if (nEffect == 0 || mbCastedFlag == 0)
        return;

    uint32_t nAnimationGuid = nAnimation;
    if (nAnimation == 0xffffffffu)
        nAnimationGuid = *(uint32_t*)((uint8_t*)&mpToolTable + 0x10);

    void* pParams = nullptr;
    void* pTool = GetCreatureToolSlot((int)(intptr_t)pSpatial, (int)(intptr_t)&pParams, 0, 0);
    if (pTool == nullptr) {
        pTool = FindToolInventoryItem((int)nAnimationGuid, &pParams);
        if (pTool == nullptr)
            return;
    }
    if (*(void**)((uint8_t*)pTool + 0x20) == pSpatial)
        return;
    if (GetCreatureBehaviour((int)(intptr_t)pSpatial) != nullptr)
        return;

    QueueCreatureInteraction((int)(intptr_t)pSpatial, (int)(intptr_t)pParams, 1);
    *(uint32_t*)((uint8_t*)pTool + 8) = 0x5f08f08;
    *(uint32_t*)((uint8_t*)pTool + 4) = 0x1f;

    uint32_t nFlags = 0;
    float fRadius = *(float*)((uint8_t*)&mpSpeciesProfile + 0x10);
    GetCurrentAnimationGUID(&nFlags);
    PreserveAnimation(*(uint32_t*)((uint8_t*)(intptr_t)fRadius + 0x184), nFlags);

    void* pAnimation = pParams;
    PlayCreatureSocialAnimation(5, 0, this, gMaxFloat, &pAnimation, 0);
    (void)nAnimationGuid;

    int nToolState = GetCreatureActionState((void*)(intptr_t)pSpatial);
    if (nToolState != 0) {
        if (*(uint8_t*)((uint8_t*)pTool + 0x18) != 0) {
            *(float*)((uint8_t*)nToolState + 0x18) = 1.0f;
            *(float*)((uint8_t*)nToolState + 0x1c) = 0.0f;
            *(float*)((uint8_t*)nToolState + 0x20) = 0.0f;
            *(float*)((uint8_t*)nToolState + 0x24) = 0.0f;
        }
        if (GetCreatureType((void*)(intptr_t)pSpatial) != 0) {
            *(float*)((uint8_t*)nToolState + 0x18) = 0.0f;
            *(float*)((uint8_t*)nToolState + 0x1c) = 0.0f;
            *(float*)((uint8_t*)nToolState + 0x20) = 1.0f;
            *(float*)((uint8_t*)nToolState + 0x24) = 0.0f;
        }
    }
    (void)nMode;
}

// ---------------------------------------------------------------------------
// 0x00c234a0  Simulator::cCreatureBase::SetToolTarget
// ---------------------------------------------------------------------------
// @ 0x00c234a0
void cCreatureBase::SetToolTarget(float fX, float fY, float fZ)
{
    float fScale = *(float*)((uint8_t*)mpIdentityColorSource + 0x74) + 0.2f;
    mfToolTargetX = fX * fScale;
    mfToolTargetY = fY * fScale;
    mbIsCastTarget = 0;
    mfToolTargetZ = fZ * fScale;

    void* pCreature = GetCreatureChain(this);
    if (pCreature != nullptr) {
        void* pTarget = GetCreatureRoot();
        if (pTarget == nullptr)
            PlayToolEffect(0, nullptr, nullptr);
        else
            PlayToolEffect((int)(intptr_t)pTarget, nullptr, nullptr);

        void* pSpatial = mpSpatialObject;
        void* pOwner = GetCreatureChain(this);
        (**(void (__stdcall***)(void*))(*(uint8_t**)pSpatial + 0x30))(pOwner);
    }
}

// ---------------------------------------------------------------------------
// 0x00c23570  Simulator::cCreatureBase::SetCasted
// ---------------------------------------------------------------------------
// @ 0x00c23570
void cCreatureBase::SetCasted(bool bCasted)
{
    mbCastedFlag = bCasted ? 0 : 1;
    if (!bCasted)
        return;

    if (mpInteractionState != nullptr) {
        (**(void (__stdcall***)(void*))(*(uint8_t**)mpInteractionState + 0xa0))(this);
        return;
    }
    if (mbCastedFlag == 0) {
        if (mpIdentityColorSource != nullptr) {
            PlayToolEffect(0, nullptr, nullptr);
            return;
        }
    } else {
        RunCreatureAttackEffect(this);
        if (IsCreatureVisibleInUI(this))
            return;
    }
    cGameNounManager* pNouns = (cGameNounManager*)NounManager();
    pNouns->RemoveNoun(this);
}

// ---------------------------------------------------------------------------
// 0x00c235e0  SP::cSPCreatureCitizen::GetToolEffect
// ---------------------------------------------------------------------------
// @ 0x00c235e0
int cSPCreatureCitizen::GetToolEffect(uint32_t nToolId)
{
    cToolOwner* pTool = (cToolOwner*)mpActiveTool;
    if (pTool == nullptr)
        pTool = (cToolOwner*)mpPendingTool;
    if (pTool != nullptr && pTool->GetOwnerCreature() == this) {
        switch (nToolId) {
        case 1:
        case 2:
        case 7:
        case 8:
        case 0xb:
            return 0x11;
        default:
            return 0;
        }
    }

    switch (nToolId) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 0xe;
    case 5:
        return 0xd;
    case 6:
        return 0xf;
    case 7:
        return 0x10;
    case 8:
        return 4;
    case 9:
        return 0x12;
    case 0xb:
        return 0x11;
    default:
        return 0;
    }
}

// ---------------------------------------------------------------------------
// 0x00c236e0  SP::cSPCreatureCitizen::HasSpecializedTool
// ---------------------------------------------------------------------------
// @ 0x00c236e0
bool cSPCreatureCitizen::HasSpecializedTool(int nToolId)
{
    if (nToolId == 0)
        return true;

    cToolOwner* pTool = (cToolOwner*)mpActiveTool;
    if (pTool == nullptr)
        pTool = (cToolOwner*)mpPendingTool;
    if (pTool != nullptr && pTool->GetOwnerCreature() == this) {
        switch (nToolId) {
        case 1:
        case 2:
        case 7:
        case 8:
        case 0xb:
            return true;
        default:
            break;
        }
    }
    return *(int*)((uint8_t*)&mpToolTable + 0x08) == nToolId;
}

// ---------------------------------------------------------------------------
// 0x00c23750  Simulator::GetCreatureToolInteraction
// ---------------------------------------------------------------------------
// @ 0x00c23750
uint32_t GetCreatureToolInteraction()
{
    uint32_t* pInteraction = (uint32_t*)GetCreatureBehaviour(0);
    if (pInteraction == nullptr)
        return 0;

    switch (*pInteraction) {
    case 7: {
        void* pCitizen = (void*)GetLeaderOfCommunity();
        if (pCitizen != nullptr) {
            int* pOwner = *(int**)((uint8_t*)pCitizen + 0x1014);
            if (pOwner != nullptr) {
                Vec3* pToolPos = (Vec3*)(intptr_t)((cSpatialObject*)*(void**)((uint8_t*)pOwner + 0x48))->GetPosition();
                Vec3* pOwnerPos = (Vec3*)(intptr_t)((cSpatialObject*)*(void**)((uint8_t*)pCitizen + 0xc0))->GetPosition();
                float fRange = (**(float (__stdcall***)(void))(*(uint8_t**)pOwner + 0x60))();
                float fDx = pOwnerPos->mX - pToolPos->mX;
                float fDy = pOwnerPos->mY - pToolPos->mY;
                float fDz = pOwnerPos->mZ - pToolPos->mZ;
                if (fDz * fDz + (fDx * fDx + fDy * fDy) < fRange * fRange)
                    return 0xad1a17du;
            }
        }
        return 0;
    }
    case 8:
        return 0x460fe7c5u;
    case 9:
    case 0x15:
        return 0xf72dd75du;
    case 0xf:
        return 0xad1a17du;
    default:
        return 0;
    }
}

// ---------------------------------------------------------------------------
// 0x00c238b0  Simulator::UpdateCreatureToolInteractions
// ---------------------------------------------------------------------------
// @ 0x00c238b0
void UpdateCreatureToolInteractions(void* pManager)
{
    uint32_t* pState = (uint32_t*)pManager;
    uint8_t bCasted = 0;
    (void)bCasted;

    uint8_t* pOwner = (uint8_t*)*(uint32_t*)((uint8_t*)pState + 0xc0);
    uint8_t bOwnerFlag = (**(uint8_t (__stdcall***)(void))(pOwner + 0x58))();

    uint32_t* pBegin = *(uint32_t**)((uint8_t*)pState + 0x338);
    uint32_t* pEnd = *(uint32_t**)((uint8_t*)pState + 0x33c);
    void* pSelf = (void*)GetCreatureToolSlot(0, 0, 0, 0);
    (void)pSelf;

    for (; pBegin != pEnd; ++pBegin) {
        uint8_t* pEntry = (uint8_t*)*pBegin;
        if (pEntry == nullptr)
            continue;

        uint8_t* pTool = (uint8_t*)(**(intptr_t (__stdcall***)(uint32_t))(*(uint8_t**)pEntry + 0xb8))(0x17f243b);
        if (*(uint8_t*)(pEntry + 0x75) == 0)
            continue;

        int nToolKind = (**(int (__stdcall***)(void))(pTool + 0x2c))();
        if (nToolKind != 0)
            continue;

        intptr_t nKind = (**(intptr_t (__stdcall***)(void))(pTool + 0x20))();
        if (nKind == 1) {
            if (*(uint8_t*)((uint8_t*)pTool + 0xb5e) != 1)
                continue;
            void* pEffect = CreateInteractionEffect(0x400000, 0, 10.0f, pTool);
            if (pEffect == nullptr)
                continue;
            Vec3* pPosition = (Vec3*)(intptr_t)((cSpatialObject*)*(void**)((uint8_t*)pTool + 0xc0))->GetPosition();
            *(float*)((uint8_t*)pEffect + 0x0c) = pPosition->mX;
            *(float*)((uint8_t*)pEffect + 0x10) = pPosition->mY;
            *(float*)((uint8_t*)pEffect + 0x14) = pPosition->mZ;
            continue;
        }

        if (nKind != 2)
            continue;

        if (*(uint8_t*)((uint8_t*)pTool + 0xb5e) != 0) {
            void* pTarget = GetCreatureSocialTarget(*(void**)((uint8_t*)pState + 0x1014));
            Vec3* pToolPos = (Vec3*)(intptr_t)((cSpatialObject*)*(void**)(pTool + 0x30))->GetPosition();
            Vec3* pTargetPos = (Vec3*)(intptr_t)((cSpatialObject*)*(void**)((uint8_t*)pTarget + 0x34))->GetPosition();
            float fToolRange = (**(float (__stdcall***)(void))(*(uint8_t**)(pTool + 0x30) + 0x74))();
            float fTargetRange = (**(float (__stdcall***)(void))(*(uint8_t**)((uint8_t*)pTarget + 0x34) + 0x74))();
            float fRange = fToolRange + fTargetRange;
            float fDx = pTargetPos->mX - pToolPos->mX;
            float fDy = pTargetPos->mY - pToolPos->mY;
            float fDz = pTargetPos->mZ - pToolPos->mZ;
            if (fRange * fRange <= fDz * fDz + (fDx * fDx + fDy * fDy)) {
                void* pEffect = CreateInteractionEffect(0x400000, 0, 10.0f, pTool);
                if (pEffect != nullptr) {
                    Vec3* pPosition = (Vec3*)(intptr_t)((cSpatialObject*)*(void**)(pTool + 0x30))->GetPosition();
                    *(float*)((uint8_t*)pEffect + 0x0c) = pPosition->mX;
                    *(float*)((uint8_t*)pEffect + 0x10) = pPosition->mY;
                    *(float*)((uint8_t*)pEffect + 0x14) = pPosition->mZ;
                }
            }
            continue;
        }

        if (bOwnerFlag != 0)
            continue;
        if (IsCreatureLeader((void*)pTool))
            continue;
        void* pToolOwner = pTool;
        ((IRefCounted*)pToolOwner)->v10();
        if ((int)(intptr_t)pToolOwner == (int)(intptr_t)pSelf)
            continue;
        int nRelation = CompareCreatureTraits(pSelf, pTool, 1);
        if (nRelation == -1)
            continue;
        cTimerOwner* pOwner2 = (cTimerOwner*)((uint8_t*)pState + 0xc0);
        float fDistance = (float)GetCreatureActionState(pOwner2);
        bool bUsable = IsToolUsable(pTool, 1.0f, fDistance);
        if (!bUsable)
            bUsable = IsToolUsable(pState, 1.0f, fDistance);
        if (!bUsable)
            continue;
        (void)nRelation;
        if (nRelation < 2) {
            uint64_t nElapsed = cSPTimerGetElapsedTime(&pOwner2->mSocialTimer);
            if ((int)(nElapsed >> 32) != 0 || (uint32_t)nElapsed > 20000)
                CreateInteractionEffect(0, 0x1000, 10.0f, pTool);
            int nSlot = (int)(intptr_t)GetCreatureToolSlot(0, 2, 0, 0);
            if (nSlot == -1) {
                nSlot = (int)(intptr_t)GetCreatureToolSlot(1, 2, 0, 0);
                if (nSlot == -1)
                    CreateInteractionEffect(0, 0x2000, 10.0f, pTool);
            }
        } else if (nRelation < 5) {
            uint64_t nElapsed = cSPTimerGetElapsedTime(&pOwner2->mSocialTimer);
            if ((int)(nElapsed >> 32) != 0 || (uint32_t)nElapsed > 20000)
                CreateInteractionEffect(0, 0x1000, 10.0f, pTool);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00c23cf0  Simulator::cCreatureBase::CalculateScale
// ---------------------------------------------------------------------------
// @ 0x00c23cf0
float cCreatureBase::CalculateScale()
{
    float fScale = GetRandomFloat(0.0f, 1.0f);
    if (mpIdentityColorSource != nullptr || mpSpeciesProfile == nullptr)
        return fScale;

    fScale = GetCreatorScaleModifier(mpSpeciesProfile) * fScale;
    if (IsCitizenLeader(this)) {
        if (IsCreatureLeader(this))
            fScale = gLeaderScaleBonus * fScale;
        else
            fScale = GetRandomFloat(gFollowerScaleBonus, gLeaderScaleBonus) * fScale;
    }
    int nBrainLevel = GetCreatureActionState(this);
    fScale = ApplyCreatureScale(nBrainLevel, fScale);
    return fScale * GetCreatureObjectScale(this);
}

// ---------------------------------------------------------------------------
// 0x00c23da0  SP::cSPCreatureCitizen::IsBefriended
// ---------------------------------------------------------------------------
// @ 0x00c23da0
bool cSPCreatureCitizen::IsBefriended()
{
    bool bBefriended = false;
    uint8_t bFlag = (**(uint8_t (__stdcall***)(void))((uint8_t*)this + 0xd0))();
    if (bFlag == 0) {
        void* pCreature = GetCreatureRoot();
        if (pCreature != nullptr) {
            int nRelation = GetCreatureSocialRelation((void*)((uint8_t*)this + 0xd0), nullptr, 0);
            bBefriended = nRelation == 6;
        }
    } else if (*(int*)((uint8_t*)&mpToolTable + 0x18) != 0) {
        cGameNounManager* pNouns = (cGameNounManager*)NounManager();
        int* pTribe = (int*)pNouns->GetPlayerTribe();
        void* pOther = *(void**)((uint8_t*)&mpToolTable + 0x18);
        int nRelation = GetCreatureSocialRelation(pOther, pTribe, 1);
        bBefriended = nRelation == 4;
    }

    if (((*(uint32_t*)((uint8_t*)this + 0xb60) >> 7) & 1) == 0 && !bBefriended)
        return false;
    return true;
}

// ---------------------------------------------------------------------------
// 0x00c23e90  Simulator::cCreatureBase::ApplyAttack
// ---------------------------------------------------------------------------
// @ 0x00c23e90
char cCreatureBase::ApplyAttack(void* pTarget, void* pAttack, void* pContext)
{
    float fDamage = GetRandomFloat(0.0f, 1.0f);
    char bApplied = ApplyAttackEffect(pTarget, pAttack, pContext);
    if (bApplied == 0 || fDamage <= 0.0f)
        return bApplied;

    if (GetCurrentGameMode() != &gCreatureToolContext)
        return bApplied;
    if (!(**(uint8_t (__stdcall***)(void))((uint8_t*)this + 0x58))())
        return bApplied;
    if (pTarget == nullptr)
        return bApplied;

    int nKey = (**(int (__stdcall***)(uint32_t))(*(uint8_t**)pTarget + 0x5c))(0xce9f6639);
    if (nKey == 0)
        return bApplied;
    if (GetCreatureType(pTarget) == 0)
        return bApplied;

    Vec3 offset;
    offset.mX = 0.0f;
    offset.mY = 0.0f;
    offset.mZ = 0.0f;
    uint32_t nEffect = (uint32_t)(intptr_t)GetCreatureChain((void*)&offset);
    RunCreatureAttackEffect((void*)(intptr_t)nEffect);
    ReportInteraction(0x7ae0330du, (void*)(intptr_t)nEffect);
    return bApplied;
}
