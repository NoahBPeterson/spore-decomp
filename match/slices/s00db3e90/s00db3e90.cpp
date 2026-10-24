// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00db3e90.
//
// Tribe social behavior actions: target validation, target resolution,
// start / update / cancel steps of the socialize action and the placement
// of the resulting targets around the creature.

typedef unsigned int size_t;
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long long uint64_t;
typedef int int32_t;
typedef int intptr_t;
typedef int int16_t;
#define nullptr 0

struct Vec3 {
    float mX;
    float mY;
    float mZ;
};

struct Vec4 {
    float mX;
    float mY;
    float mZ;
    float mW;
};

class IRefCounted {
public:
    virtual void AddRef();
    virtual void Release();
    virtual void v08();
    virtual void* Query(const void* pType);
    virtual void v10();
};

// A raw dispatch table; slots are indexed by their byte offset / 4.
struct cMethodTable {
    void* mSlots[0x100];
};

struct cObject {
    cMethodTable* mpMethods;                    // 0x00

    void* Call(int nSlot) {
        return ((void* (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    void* Call(int nSlot, void* pArg1) {
        return ((void* (*)(void*, void*))mpMethods->mSlots[nSlot >> 2])(this, pArg1);
    }
    void* Call(int nSlot, uint32_t nArg1) {
        return ((void* (*)(void*, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1);
    }
    void* Call(int nSlot, uint32_t nArg1, void* pArg2) {
        return ((void* (*)(void*, uint32_t, void*))mpMethods->mSlots[nSlot >> 2])(this, nArg1, pArg2);
    }
    void* Call(int nSlot, void* pArg1, void* pArg2) {
        return ((void* (*)(void*, void*, void*))mpMethods->mSlots[nSlot >> 2])(this, pArg1, pArg2);
    }
    float CallFloat(int nSlot) {
        return ((float (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    char CallChar(int nSlot) {
        return ((char (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
};

class cSpatialObject : public IRefCounted {
public:
    Vec3* GetPosition();
    Vec4* GetOrientation();
};

class cPlanetModel {
public:
    Vec3* DirectionToSurfacePosition(Vec3* pOut, const Vec3* pDirection);
    float GetWaterHeight();
};

class cGameNounManager : public IRefCounted {
public:
    void* GetNounByKey(uint32_t nKey);
};

class cBehaviorStimuli {
public:
    void* GetAny();
    void* mPointers[8];                         // 0x00
};

struct cSocialTarget {
    cObject* mpObject;                          // 0x00
    float mfValue;                              // 0x04
    float mfX;                                  // 0x08
    float mfY;                                  // 0x0c
    float mfZ;                                  // 0x10
};

struct cGroupMovement {
    uint8_t mPad000[0x18c];                     // 0x000
    float mfCooldown;                           // 0x18c
    float mfValue2;                             // 0x190
    float mfX;                                  // 0x194
    float mfY;                                  // 0x198
    float mfZ;                                  // 0x19c
    uint8_t mPad1a0[0x20];                      // 0x1a0
    float mfRangeSq;                            // 0x1c0
    cObject* mpOwner;                           // 0x1c4

    void Stop();
};

struct cActionState {
    void* mpTarget;                             // 0x00
    int mnState;                                // 0x04
    int mnAnimation;                            // 0x08
    int mnLoopCount;                            // 0x0c
    int mnEffectId;                             // 0x10
};

struct cSocialData {
    cObject* mpOwner;                           // 0x00
    uint8_t mPad04[0x08];                       // 0x04
    uint32_t mnHandle;                          // 0x0c
    float mfOffset;                             // 0x10
    float mfX;                                  // 0x14
    float mfY;                                  // 0x18
    float mfZ;                                  // 0x1c
    Vec4 mRotation;                             // 0x20
    uint8_t mbSnap;                             // 0x30
};

class cSocialActionHost {
public:
    bool CheckSocialTarget(cSocialTarget* pTarget);
    bool ResolveTarget(cActionState* pState);
    void ReleaseTarget(cActionState* pState);
    int Start(cActionState* pState);
    int Update(cActionState* pState);
    float TryTribeTool(uint32_t nA, uint32_t nB, uint32_t nFlags,
                       cBehaviorStimuli* pStimuli, uint8_t* pbFlag);
    int Cancel();
    void PlaceTargets(cSocialData* pData, bool bSnap);

    uint8_t mPad000[0x0c];                      // 0x000
    cObject* mpSocialQuery;                     // 0x00c
    uint8_t mPad010[0x48];                      // 0x010
    void** mpBuckets;                           // 0x058
    uint32_t mnBucketCount;                     // 0x05c
    uint8_t mPad060[0x144];                     // 0x060
    uint32_t mnGroupHandle;                     // 0x1a4
    uint8_t mPad1a8[0x84];                      // 0x1a8
};

class cGroupMovementPool {
public:
    void* GetObject(uint32_t nHandle);
    void ReleaseObject(uint32_t nHandle);
};

class cTribe {
public:
    void* GetToolOfType(int nType);
};

class cCombatant {
public:
    int GetDamageState();
};

void* operator_new(size_t nSize);
void operator_delete__(void* pMemory);
void* ResizablePoolGet(uint32_t nHandle);
void ResizablePoolRelease(uint32_t nHandle);
char IsSocialQueryActive();
cObject* GetSocialQueryObject();
void* GetBehaviourStimuli(cObject* pObject, int nA, uint32_t nB);
void* GetSocialQueryManager();
void* GetTribe();
void* CreateSocialEffect(void* pThis);
void ReleaseSocialGroup(uint32_t nHandle);
char IsLeader(void* pCreature);
void PlaceTargetsEntry(void* pThis, cSocialData* pData, bool bSnap);
void* GetSpatialObjectByKey(cSocialActionHost* pHost, uint32_t nKey);
bool PlayIdleAnimation(cObject* pCreature, int nA, uint32_t nFlags);
void* WatchMemoryBlock(void* pAnimation);
int StartAnimation(cSocialActionHost* pHost, uint32_t nAnimId);
void ConfigureSocialQuery(cSocialActionHost* pHost, uint8_t* pBuffer, const char* pName);
void ResetGroupMovement(uint32_t nHandle);
void* GetCurrentActionTarget(cSocialActionHost* pHost, uint32_t nKey);
void BeginAnimation(cObject* pCreature, int nA, int nB);
void ReleaseState(cActionState* pState);
void* FindNearbyObjects(cSocialActionHost* pHost, float fRadius, uint32_t nFlags,
                        void* pCallback, int nMode);
void FinishSocialStep(cSocialActionHost* pHost);
int InterruptAnimation(cObject* pCreature, uint32_t nAnimId, uint32_t nFlags, int nMode);
char AnimationFinished(cObject* pCreature, int nAnimation);
char WaitForAnimEventOrEnd(cObject* pCreature, uint32_t nEventId, int* pOut,
                           int nA, int nAnimation, int nB);
void SetCurrentToolEffect(cSocialActionHost* pHost, int nEffect, int nType);
int PlayBehaviourAnimation(cObject* pCreature, int nA, uint32_t nFlags);
void ClearStimuli(cObject* pCreature, int nA, uint32_t nFlags);
int PressBehaviourButton(int nA, uint32_t nFlags, float fValue, int nB);
int FinishAction(cSocialActionHost* pHost, int nState);
void* LookupToolByKey(uint32_t nKey);
char SpendTribePoints(int nCost, int nMode);
float RandomRange(float fMin, float fMax);
float GetCreativeCreatureRate();
void SetSocialTargetPointers(cBehaviorStimuli* pStimuli, int nValue);
void AddSocialTarget(cObject* pObject, uint32_t nKey, const Vec3* pPosition,
                     const Vec3* pDirection, cObject* pOwner, const Vec3* pFacing);
float GetNearbyRadius(cObject* pObject);
void* GetNearbyEntry(int nIndex);
int GetCombatantDamageState(cObject* pCombatant);
void Matrix3FromQuaternion(float* pOut, const Vec4* pQuaternion);

extern void* gSocialQueryManager;
extern void* gPlanetModelPointer;
extern void* gRandomState;
extern uint8_t gEmptySocialTarget[0x20];
extern float gMaxFloat;
extern cGroupMovementPool gGroupMovementPool;

// ---------------------------------------------------------------------------
// 0x00db3e90  cSocialActionHost::CheckSocialTarget
// ---------------------------------------------------------------------------
// @ 0x00db3e90
bool cSocialActionHost::CheckSocialTarget(cSocialTarget* pTarget)
{
    if (IsSocialQueryActive() != 0)
        return false;

    cObject* pObject = pTarget->mpObject;
    float fValue = pTarget->mfValue;
    cGroupMovement* pGroup = (cGroupMovement*)ResizablePoolGet(mnGroupHandle);

    cObject* pOther = nullptr;
    if (pGroup->mfCooldown == 0.0f) {
        if (mpSocialQuery != nullptr && mpSocialQuery != gSocialQueryManager)
            return false;
        pOther = GetSocialQueryObject();
    } else {
        if (pGroup->mpOwner == nullptr)
            return false;
        pOther = (cObject*)LookupToolByKey(0xce9f6639);
    }

    if (pOther != nullptr) {
        if (pObject->Call(0x20) == pOther->Call(0x20)) {
            if (pObject->Call(0x4c) == pOther->Call(0x4c)) {
                Vec3* pMine = (Vec3*)pObject->Call(0x2c);
                Vec3* pTheirs = (Vec3*)pOther->Call(0x2c);
                float fDx = pTheirs->mX - pMine->mX;
                float fDy = pTheirs->mY - pMine->mY;
                float fDz = pTheirs->mZ - pMine->mZ;
                if (fDz * fDz + (fDx * fDx + fDy * fDy) < 5625.0f) {
                    if (fValue != 0.0f)
                        return pGroup->mfValue2 == fValue;
                    float gx = pGroup->mfX - pTarget->mfX;
                    float gy = pGroup->mfY - pTarget->mfY;
                    float gz = pGroup->mfZ - pTarget->mfZ;
                    if (gz * gz + (gx * gx + gy * gy) < pGroup->mfRangeSq)
                        return true;
                    return false;
                }
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00db4050  cSocialActionHost::ResolveTarget
// ---------------------------------------------------------------------------
// @ 0x00db4050
bool cSocialActionHost::ResolveTarget(cActionState* pState)
{
    if (pState != nullptr) {
        pState->mnLoopCount = 0;
        pState->mnEffectId = 0;
        *(uint32_t*)((uint8_t*)pState + 0x18) = 0;
        *(uint32_t*)((uint8_t*)pState + 0x1c) = 0;
    }

    cGameNounManager* pNouns = (cGameNounManager*)GetSocialQueryManager();
    if (pNouns == nullptr || *(uint32_t*)pNouns != 0x16)
        return false;

    int16_t nKind = *(int16_t*)((uint8_t*)pNouns + 0x4b);
    uint32_t* pKey;
    if (nKind == 10 || nKind == 0x10) {
        if ((*(uint8_t*)((uint8_t*)pNouns + 0x49) & 0x30) == 0)
            pKey = (uint32_t*)(nKind != 0 ? ((uint8_t*)pNouns + 0x39) : 0);
        else
            pKey = *(uint32_t**)((uint8_t*)pNouns + 0x39);
    } else {
        pKey = (uint32_t*)&gEmptySocialTarget[0];
    }

    uint32_t nKey = *pKey;
    pState->mpTarget = (void*)(intptr_t)nKey;
    pState->mnState = 0;
    pState->mnAnimation = 0;
    *(uint8_t*)((uint8_t*)pState + 0x14) = 0;

    void* pObject = *(void**)((uint8_t*)this + 0xb4);
    (void)pObject;
    void* pFound = nullptr;
    (void)pFound;
    return pState->mnLoopCount != 0;
}

// ---------------------------------------------------------------------------
// 0x00db40f0  cSocialActionHost::ReleaseTarget
// ---------------------------------------------------------------------------
// @ 0x00db40f0
void ReleaseSocialTargetState(void* pArg1, void* pArg2, void* pArg3, void* pArg4,
                              void* pArg5, cActionState* pState)
{
    (void)pArg1;
    (void)pArg2;
    (void)pArg3;
    (void)pArg4;
    (void)pArg5;
    if (pState == nullptr)
        return;

    void* pBlock = *(void**)((uint8_t*)pState + 0x14);
    if (pBlock != nullptr) {
        int nRefs = *(int*)((uint8_t*)pBlock - 4);
        if (nRefs != 0)
            operator_delete__(pBlock);
    }

    cObject* pTarget = (cObject*)*(void**)((uint8_t*)pState + 0x0c);
    if (pTarget == nullptr)
        return;
    int nRefs = *(int*)((uint8_t*)pTarget + 4);
    *(int*)((uint8_t*)pTarget + 4) = nRefs - 1;
    if (nRefs - 1 == 0) {
        *(int*)((uint8_t*)pTarget + 4) = 1;
        pTarget->Call(0x00, (uint32_t)1);
    }
}

// ---------------------------------------------------------------------------
// 0x00db4140  cSocialActionHost::Start
// ---------------------------------------------------------------------------
// @ 0x00db4140
int cSocialActionHost::Start(cActionState* pState)
{
    void* pAnimation = nullptr;
    (void)pAnimation;

    ConfigureSocialQuery(this, nullptr, nullptr);
    BeginAnimation((cObject*)this, 0, 0);

    if (IsLeader(this) != 0 && ((cObject*)this)->CallChar(0x58) != 0) {
        void* pBuffer = nullptr;
        (void)pBuffer;
        ConfigureSocialQuery(this, (uint8_t*)0x20, "SocialPower");
        int nQuery = StartAnimation(this, 0x10000000);

        *(uint32_t*)((uint8_t*)(intptr_t)nQuery + 0x1a8) = 0;
        *(uint32_t*)((uint8_t*)(intptr_t)nQuery + 0x1a4) = 0;
        *(uint8_t*)((uint8_t*)(intptr_t)nQuery + 0x1ac) = 0;
        *(void**)((uint8_t*)(intptr_t)nQuery + 0x224) = (void*)&PlaceTargetsEntry;

        cObject* pManager = (cObject*)GetSocialQueryManager();
        if (pManager != nullptr && *(uint32_t*)pManager == 0x16) {
            cObject* pQuery = (cObject*)GetCurrentActionTarget(this, 0);
            void* pFound = *(void**)((uint8_t*)pQuery + 0xb4);
            if (pFound != nullptr && *(int*)((uint8_t*)pFound + 8) == 0x38) {
                PressBehaviourButton(0, 1, 0.0f, 0);
                FinishAction((cSocialActionHost*)this, 0x16);

                void* pListA = nullptr;
                void* pListB = nullptr;
                (void)FindNearbyObjects(this, *(float*)((uint8_t*)pFound + 0xa8), 0,
                                        (void*)0, 0);
                for (; pListA != pListB; pListA = (uint8_t*)pListA + 4) {
                    cObject* pEntry = *(cObject**)pListA;
                    if (pEntry == nullptr)
                        continue;
                    cObject* pComp = (cObject*)pEntry->Call(0xb8, 0x4f176642);
                    if (pComp == nullptr)
                        continue;
                    if (GetCombatantDamageState(pComp) == 0)
                        continue;
                    if (pComp == (cObject*)this)
                        continue;
                    void* pAnim = (void*)(intptr_t)PressBehaviourButton(0, 0x10000000,
                                                                       10.0f, 0);
                    if (pAnim == nullptr)
                        continue;
                    *(uint32_t*)((uint8_t*)pAnim + 0x0c) = 1;
                }
            }
        }
    } else {
        int nAnim = PlayIdleAnimation((cObject*)this, 0, 0x10000000);
        if (nAnim != 0) {
            void* pBlock = WatchMemoryBlock((void*)(intptr_t)nAnim);
            intptr_t nOffset = pBlock == nullptr ? 0 : (intptr_t)pBlock + 0x5a8;
            ((cObject*)this)->Call(0x84, (void*)nOffset, (void*)(intptr_t)1);
        }
    }

    ResetGroupMovement(0);
    ((cObject*)this)->Call(0xec);
    pState->mpTarget = nullptr;
    pState->mnState = 0;
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00db4370  cSocialActionHost::Update
// ---------------------------------------------------------------------------
// @ 0x00db4370
int cSocialActionHost::Update(cActionState* pState)
{
    switch (pState->mnState) {
    case 0:
        {
            void* pTarget = *(void**)((uint8_t*)this + 0xb4);
            (void)pTarget;
            PressBehaviourButton(*(int*)((uint8_t*)pState), 1, 0.0f, 0);
            FinishAction((cSocialActionHost*)this, 0x16);
            int nAnimation = InterruptAnimation((cObject*)this, 0x6006753, 0xffffffff, 0);
            pState->mnAnimation = nAnimation;
            pState->mnState = 1;
        }
        break;

    case 1:
        {
            char bFinished = AnimationFinished((cObject*)this, pState->mnAnimation);
            if (bFinished == 0) {
                int nEvent = -1;
                if (WaitForAnimEventOrEnd((cObject*)this, 0x7d7502fc, &nEvent, 0,
                                          pState->mnAnimation, 1) != 0) {
                    SetCurrentToolEffect((cSocialActionHost*)this, 0x16, nEvent);
                    pState->mnEffectId = nEvent;
                }
                nEvent = -1;
                if (WaitForAnimEventOrEnd((cObject*)this, 0xe95450e, &nEvent, 0,
                                          pState->mnAnimation, 1) != 0) {
                    SetCurrentToolEffect((cSocialActionHost*)this, 0, nEvent);
                    pState->mnLoopCount = pState->mnLoopCount + 1;
                    pState->mnEffectId = -1;
                }
            }
            if (3 < pState->mnLoopCount) {
                void* pEffect = CreateSocialEffect(this);
                (void)pEffect;
                pState->mnState = 2;
                return 1;
            }
            if (bFinished != 0) {
                pState->mnState = (pState->mnLoopCount < 1) + 2;
                return 1;
            }
        }
        break;

    case 2:
        {
            int nAnim = PlayIdleAnimation((cObject*)this, 0, 0x10000000);
            char bFinished = AnimationFinished((cObject*)this, pState->mnAnimation);
            if ((nAnim != 0 && *(int*)((uint8_t*)nAnim + 0x0c) == 2) || bFinished != 0) {
                void* pTarget = *(void**)((uint8_t*)this + 0xb4);
                (void)pTarget;

                void* pListA = nullptr;
                void* pListB = nullptr;
                int nState = PressBehaviourButton(*(int*)((uint8_t*)pState), 1, 0.0f, 0);
                (void)nState;
                if (pTarget != nullptr) {
                    void* pOwner = (void*)(intptr_t)pTarget;
                    (void)FindNearbyObjects(this, *(float*)((uint8_t*)pOwner + 0xf4) +
                                            *(float*)((uint8_t*)pOwner + 0xa8),
                                            (uint32_t)pListA, (void*)0, 0);
                    uint32_t nCount = (uint32_t)(((uint8_t*)pListB - (uint8_t*)pListA) >> 2);
                    for (uint32_t i = 0; i < nCount; ++i) {
                        cObject* pEntry = ((cObject**)pListA)[i];
                        if (pEntry == nullptr)
                            continue;
                        cObject* pStimuli = (cObject*)pEntry->Call(0xb8, 0x013f94d4);
                        if (pStimuli == nullptr)
                            continue;
                        if (pStimuli == (cObject*)&gEmptySocialTarget[0])
                            continue;
                        if (pEntry->CallChar(0x58) != 0)
                            continue;
                        if (RandomRange(0.0f, 1.0f) <= 0.0f)
                            continue;

                        void* pAnimTarget = *(void**)((uint8_t*)pOwner + 0x3c);
                        Vec3* pMine = (Vec3*)pEntry->Call(0x2c);
                        Vec3* pOwnerPos = (Vec3*)((cObject*)this)->Call(0x2c);
                        Vec3 direction;
                        direction.mX = pOwnerPos->mX - pMine->mX;
                        direction.mY = pOwnerPos->mY - pMine->mY;
                        direction.mZ = pOwnerPos->mZ - pMine->mZ;

                        Vec3 normalised;
                        Matrix3FromQuaternion((float*)&normalised, (const Vec4*)&direction);
                        void* pFacing = (void*)0x4c;
                        (void)pFacing;
                        ((cObject*)this)->Call(0x4c, &normalised);
                        AddSocialTarget(pEntry, (uint32_t)(intptr_t)pAnimTarget,
                                        (const Vec3*)&normalised, (const Vec3*)&normalised,
                                        (cObject*)this, (const Vec3*)&normalised);

                        void* pResult;
                        if (SpendTribePoints(0x10, 0x10000) != 0)
                            pResult = (void*)0;
                        else
                            pResult = (void*)(intptr_t)GetCreativeCreatureRate();
                        (void)pResult;
                    }
                }
                ClearStimuli((cObject*)this, 0, 0x10000000);
                pState->mnState = 3;
                return 1;
            }
        }
        break;

    case 3:
        if (AnimationFinished((cObject*)this, pState->mnAnimation) != 0) {
            PressBehaviourButton(0, 0x20, gMaxFloat, 0);
            return FinishAction((cSocialActionHost*)this, 0x16);
        }
        break;

    default:
        break;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00db4900  cSocialActionHost::TryTribeTool
// ---------------------------------------------------------------------------
// @ 0x00db4900
float cSocialActionHost::TryTribeTool(uint32_t nA, uint32_t nB, uint32_t nFlags,
                                      cBehaviorStimuli* pStimuli, uint8_t* pbFlag)
{
    (void)nA;
    (void)nB;
    if (*(uint8_t*)((uint8_t*)this + 0xf90) == 0 || (nFlags & 0x400) != 0)
        return 0.0f;

    cTribe* pTribe = (cTribe*)GetTribe();
    int aTools[9];
    aTools[0] = 1;
    aTools[1] = 2;
    aTools[2] = 3;
    aTools[3] = 4;
    aTools[4] = 5;
    aTools[5] = 6;
    aTools[6] = 7;
    aTools[7] = 8;
    aTools[8] = 9;

    for (uint32_t i = 0; i < 9; ++i) {
        void* pTool = pTribe->GetToolOfType(aTools[i]);
        if (pTool == nullptr)
            continue;
        if ((*(uint8_t*)((uint8_t*)pTool + 0x84) & 0x10) != 0)
            continue;
        int nDamage = ((cCombatant*)((uint8_t*)pTool + 0x120))->GetDamageState();
        if (nDamage == 2)
            continue;
        if (SpendTribePoints(0, 0) != 0)
            continue;

        if (pStimuli != nullptr)
            pStimuli->GetAny();
        SetSocialTargetPointers(pStimuli, aTools[i]);
        *pbFlag = 1;
        return RandomRange(0.1f, 1.0f) * 0.5f;
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00db4a20  cSocialActionHost::Cancel
// ---------------------------------------------------------------------------
// @ 0x00db4a20
uint8_t CancelSocialAction(void* pThis)
{
    uint32_t nHandle = *(uint32_t*)((uint8_t*)pThis + 0x1a4);
    if (nHandle > 0) {
        cGroupMovement* pGroup = (cGroupMovement*)gGroupMovementPool.GetObject(nHandle);
        pGroup->Stop();
        gGroupMovementPool.ReleaseObject(nHandle & 0xbfffffff);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00db4a60  cSocialActionHost::PlaceTargets
// ---------------------------------------------------------------------------
// @ 0x00db4a60
void cSocialActionHost::PlaceTargets(cSocialData* pData, bool bSnap)
{
    cObject* pOwner = pData->mpOwner;
    uint32_t nHandle = pData->mnHandle;
    float fOffset = pData->mfOffset;
    (void)fOffset;
    (void)pOwner;

    uint32_t* pListA = nullptr;
    uint32_t* pListB = nullptr;
    (void)pListA;
    (void)pListB;

    if (bSnap)
        AddSocialTarget((cObject*)pOwner, 0x1f, (const Vec3*)&pData->mfX, nullptr,
                        nullptr, nullptr);

    float rotation[9];
    Matrix3FromQuaternion(rotation, &pData->mRotation);

    cPlanetModel* pPlanet = (cPlanetModel*)gPlanetModelPointer;
    float fWaterHeight = pPlanet->GetWaterHeight();

    int nIndex = 0;
    for (;;) {
        void* pEntry = GetNearbyEntry(nIndex);
        if (pEntry == nullptr) {
            for (uint32_t* p = pListA; p != pListB; ++p) {
                if (*(void**)(intptr_t)*p != nullptr)
                    (*(cObject**)(intptr_t)*p)->Call(0xc0);
            }
            if (pListA != nullptr && *(pListA - 1) != 0)
                operator_delete__(pListA);
            if (pListB != nullptr && *(pListB - 1) != 0)
                operator_delete__(pListB);
            return;
        }

        ++nIndex;
        if (*(uint8_t*)pEntry != 0 && *(int*)((uint8_t*)pEntry + 8) != 0)
            PressBehaviourButton(0, 0, 0.0f, 0);

        float fX = *(float*)((uint8_t*)pEntry + 0x0c);
        float fY = *(float*)((uint8_t*)pEntry + 0x10);
        float fZ = *(float*)((uint8_t*)pEntry + 0x14);

        if (pData->mbSnap != 0) {
            Vec3 position;
            position.mX = pData->mfX + (rotation[0] * fX + rotation[6] * fY + rotation[3] * fZ);
            position.mY = pData->mfY + (rotation[1] * fX + rotation[7] * fY + rotation[4] * fZ);
            position.mZ = pData->mfZ + (rotation[2] * fX + rotation[5] * fY + rotation[8] * fZ);
            Vec3* pSurface = pPlanet->DirectionToSurfacePosition(&position, &position);
            fX = pSurface->mX;
            fY = pSurface->mY;
            fZ = pSurface->mZ;
        }

        if (bSnap) {
            if (fWaterHeight * fWaterHeight < fX * fX + fZ * fZ + fY * fY) {
                for (uint32_t* p = pListA; p != pListB; ++p) {
                    uint8_t* pObject = (uint8_t*)(intptr_t)*p;
                    float fRadius = *(float*)(pObject + 0x44);
                    float dx = fX - *(float*)(pObject + 0x38);
                    float dy = fY - *(float*)(pObject + 0x3c);
                    float dz = fZ - *(float*)(pObject + 0x40);
                    if (dx * dx + dz * dz + dy * dy < fRadius * fRadius)
                        PressBehaviourButton(1, 0, 0.0f, 0);
                }
            } else {
                PressBehaviourButton(1, 0, 0.0f, 0);
            }
            continue;
        }

        for (uint32_t* p = pListA; p != pListB; ++p) {
            cObject* pObject = (cObject*)(intptr_t)*p;
            uint32_t nKey = 0;
            if (pObject != nullptr)
                nKey = (uint32_t)(intptr_t)pObject->Call(0xb8, 0x116dd1b);
            uint32_t nBucket = nKey % mnBucketCount;
            float fRadius = GetNearbyRadius(pObject);
            (void)nBucket;
            (void)fRadius;
            PressBehaviourButton(2, 0, 0.0f, 0);
        }
    }
}
