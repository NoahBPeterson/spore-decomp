// Creature behavior task helpers, the group movement leader picker and the
// social band object pool accessors.
//
// The three behavior task entry points (0x00d9dce0 / 0x00d9e570 / 0x00d9ea30)
// are dispatched by the behavior tree with a fixed argument frame: the first
// argument is the creature that owns the task and the last one is the task
// state block.  Only those two are read.

typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define nullptr 0

// ---------------------------------------------------------------------------
// Raw dispatch helper: retail reaches these interface slots directly through
// the method table of the component, which is too wide to spell out as virtual
// members of every interface.
// ---------------------------------------------------------------------------
struct cMethodTable {
    void* mpSlots[0x100];                       // 0x000
};

class cDispatchObject {
public:
    void* Call(int nSlot) {
        return ((void* (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    char CallChar(int nSlot) {
        return ((char (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    void CallVoid(int nSlot) {
        ((void (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    cMethodTable* mpTable;                      // 0x000
};

// ---------------------------------------------------------------------------
// Behavior tree stimuli: ClearAll / Play take a mask and a value.
// ---------------------------------------------------------------------------
class cBehaviorStimuli {
public:
    void ClearAll(uint32_t nFlags, uint32_t nValue);
    void* Play(uint32_t nFlags, uint32_t nValue);
};

class nBehaviorTree {
public:
    uint8_t mPad000[0x08];                      // 0x000
    cBehaviorStimuli mStimuli;                  // 0x008

    uint8_t mPad_600[0x600 - 0x008 - sizeof(cBehaviorStimuli)];
    void* mpCurrentTask;                        // 0x600
};

// ---------------------------------------------------------------------------
// The task state block shared by the behavior entry points.
// ---------------------------------------------------------------------------
struct cBehaviorTask {
    int32_t mnState;                            // 0x000
    uint32_t mnAnimId;                          // 0x004
};

struct cLeaderChoice {
    void* mpLeader;                             // 0x000
    uint32_t mnAnimId;                          // 0x004
    uint8_t mbChanged;                          // 0x008
};

struct cFoundTarget {
    void* mpObject;                             // 0x000
    uint32_t mnField04;                         // 0x004
    uint32_t mnField08;                         // 0x008
    uint32_t mnField0c;                         // 0x00c
    float mfField10;                            // 0x010
    uint32_t mnField14;                         // 0x014
};

struct cBehaviorCallback {
    void* mpTarget;                             // 0x000
    void* mpOwner;                              // 0x004
    void* mpHandler;                            // 0x008
};

struct cActionCircleLink {
    uint8_t mPad000[0x20c];                     // 0x000
    uint32_t mnLink;                            // 0x20c
};

struct cTargetData {
    uint8_t mPad000[0x43c];                     // 0x000
    int32_t mnCount;                            // 0x43c
};

// ---------------------------------------------------------------------------
// The location component hanging off the creature at +0x34.
// ---------------------------------------------------------------------------
class cLocationComponent {
public:
    void* GetObject();
    void* GetOwner();
};

class cActionObject;

class cSimCreature {
public:
    void* GetCombatTarget();
    void* GetTargetCreature();
    void* GetActionObject();
    int32_t GetBehaviorPhase();
    char IsGroupLeader();
    int32_t InterruptAnimation(uint32_t nAnimId, int32_t nA, int32_t nB);
    char AnimationFinished(uint32_t nAnimId);
    char WaitForAnimEvent(uint32_t nEventId, void* pData, int32_t nA,
                          uint32_t nAnimId, int32_t nB);
    void SetCombatEngaged(char bEngaged);
    void StopLocomotion(int32_t nA, int32_t nB);
    void* GetTargetData();
    void UpdatePose();
    void ResetPose();
    void UpdateTargetPose();
    void UpdateAttackTarget();
    void NotifyTargetLost();
    void UpdateWorldTarget();
    void* GetTargetRecord();

    uint8_t mPad000[0x34];                      // 0x000
    cLocationComponent mLocation;               // 0x034
    uint8_t mPad038[0x88];                      // 0x038
    cDispatchObject mMovement;                  // 0x0c0
    uint8_t mPad0c4[0xa88];                     // 0x0c4
    nBehaviorTree* mpBehaviorTree;              // 0xb4c
};

class cActionObject {
public:
    float GetRadius();
    void* GetBounds();
    void SetTarget(float fValue);
    void MoveTowards(float fValue);
};

class cNounManager {
public:
    void* GetInfo(void* pObject);
    void SetInfo(void* pObject, void* pInfo);
    float GetDistance(void* pObject, float fValue, int32_t nMode);
    void MoveTo(void* pObject, void* pTarget, float fValue, int32_t nMode);
};

class cWorldManager {
public:
    void* FindObject(void* pObject);
    void* GetObjectData(void* pObject);
};

class cEpisodeObject {
public:
    void* GetRecord();
};

// The completion handler stored in the behavior callback, the first two
// interface slots are used by the task entry points.
class cBehaviorHandler {
public:
    virtual void Method00();                    // slot 0x00
    virtual void Method04();                    // slot 0x04
};

// ---------------------------------------------------------------------------
// The social band object pool.  Every slot carries a four byte link header,
// the pooled object follows it; retail spells this pool as
// cResizableObjectPoolT<SP::cSocialBand> with a 0x210 byte stride.
// ---------------------------------------------------------------------------
class cPoolObject {
public:
    virtual void Destroy(char bFree);           // slot 0x00
    virtual void AddRef();                      // slot 0x04
};

struct cPoolSlot {
    union {
        uint32_t mnLinkFlags;                   // 0x000
        struct {
            uint32_t mnLink : 30;               // bits 0..29
            uint32_t mbFlag : 1;                // bit 30
            uint32_t mbUsed : 1;                // bit 31
        };
    };
    uint8_t mObject[0x20c];                     // 0x004
};

class cSocialBandPool {
public:
    cPoolObject* GetObject(uint32_t nIndex);
    void ReleaseObject(uint32_t nIndex);
    uint32_t GetNextFreeSlot(uint32_t nIndex);

    cPoolSlot* mpBegin;                         // 0x000
    cPoolSlot* mpEnd;                           // 0x004
    uint8_t mPad008[0x0c];                      // 0x008
    uint32_t mnTailIndex;                       // 0x014
    uint32_t mnHeadIndex;                       // 0x018
};

class cGroupMovement {
public:
    char PickLeader(cSimCreature* pCreature, void* pA, void* pB, void* pC,
                    void* pD, cLeaderChoice* pChoice);

    uint8_t mPad000[0x214];                     // 0x000
};

// ---------------------------------------------------------------------------
// Services called by the behavior entry points.
// ---------------------------------------------------------------------------
void* NounManager();
void* WorldManager();
void* __stdcall BehaviorManager(cSimCreature* pCreature);
void* GetObjectFromId(void* pId);
char IsValidCombatTarget(void* pTarget);
char IsValidBehaviorTarget(void* pTarget);
void* WatchMemoryBlock(void* pBlock);
void SetBehaviorState(cSimCreature* pCreature, int32_t nState);
int32_t GetUniverseConstant(int32_t nValue, uint32_t nSalt, int32_t nDefault);
int32_t GetWorldConstant(int32_t nValue, uint32_t nSalt, int32_t nDefault);
void* CreateEpisodeObject(void* pA, void* pB);
uint32_t RandomUint32Uniform(int32_t nRange);

static uint32_t* GetActionLink(cSimCreature* pCreature)
{
    cActionCircleLink* pLink = (cActionCircleLink*)pCreature->GetActionObject();
    if (pLink == nullptr)
        return nullptr;
    return &pLink->mnLink;
}

static void AttachTargetInfo(cSimCreature* pCreature, void* pTarget,
                             void* pLocation)
{
    cNounManager* pManager = (cNounManager*)NounManager();
    void* pInfo = pManager->GetInfo(pLocation);
    ((cNounManager*)NounManager())->SetInfo(pTarget, pInfo);
}

// ---------------------------------------------------------------------------
// 0x00d9dce0  RunCombatBehavior
// ---------------------------------------------------------------------------
// @ 0x00d9dce0
char RunCombatBehavior(cSimCreature* pCreature, void* pA, void* pB, void* pC,
                       void* pD, cBehaviorTask* pTask)
{
    uint8_t mEventData[0x44];
    void* pTarget = pCreature->GetCombatTarget();
    if (!IsValidCombatTarget(pTarget)) {
        SetBehaviorState(pCreature, 0x14);
        return 0;
    }

    switch (pTask->mnState) {
    case 0:
        if (pCreature->WaitForAnimEvent(0xbfa50b5a, mEventData, 0,
                                        pTask->mnAnimId, 0)) {
            void* pLocation = pCreature->mLocation.GetObject();
            if (pLocation != nullptr)
                AttachTargetInfo(pCreature, pTarget, pLocation);
        }
        if (pCreature->AnimationFinished(pTask->mnAnimId))
            pTask->mnState = 1;
        break;

    case 1:
        if (pCreature->WaitForAnimEvent(0xbfa50b5a, mEventData, 0,
                                        pTask->mnAnimId, 0)) {
            pCreature->StopLocomotion(0, -1);
            int32_t nCount = 5;
            void* pData = ((cSimCreature*)pTarget)->GetTargetData();
            if (pData != nullptr)
                nCount = GetUniverseConstant(((cTargetData*)pData)->mnCount,
                                             0xeb69140e, 5);
            void* pLocation = pCreature->mLocation.GetObject();
            uint32_t* pLink = GetActionLink(pCreature);
            float fDistance = ((cNounManager*)NounManager())->GetDistance(
                pLink, (float)nCount, 0);
            if (fDistance < 0.0f) {
                float fRadius = ((cActionObject*)pCreature->GetActionObject())
                                    ->GetRadius();
                ((cNounManager*)NounManager())->MoveTo(
                    pLocation, pLink, pTask->mnAnimId ? fDistance : fRadius, 6);
                SetBehaviorState(pCreature, 0x14);
                return 0;
            }
            pCreature->mMovement.CallVoid(0x2c);
            ((cNounManager*)NounManager())->MoveTo(pLocation, pLink, -fDistance,
                                                   6);
        }
        if (pCreature->AnimationFinished(pTask->mnAnimId))
            pTask->mnState = 2;
        break;

    case 2:
        pCreature->NotifyTargetLost();
        pCreature->ResetPose();
        break;

    case 3:
        if (pCreature->WaitForAnimEvent(0xbfa50b5a, mEventData, 0,
                                        pTask->mnAnimId, 0)) {
            void* pLocation = pCreature->mLocation.GetObject();
            if (pLocation != nullptr)
                AttachTargetInfo(pCreature, pTarget, pLocation);
            void* pWorld = WorldManager();
            void* pRecord = ((cWorldManager*)pWorld)->FindObject(pLocation);
            if (pRecord != nullptr) {
                void* pEpisode = ((cWorldManager*)WorldManager())
                                     ->GetObjectData(pRecord);
                if (pEpisode != nullptr)
                    ((cEpisodeObject*)pEpisode)->GetRecord();
            }
        }
        if (pCreature->AnimationFinished(pTask->mnAnimId))
            pTask->mnState = 4;
        break;

    case 4:
        if (pCreature->GetBehaviorPhase() == 1) {
            void* pEpisode = CreateEpisodeObject(pA, pB);
            if (pEpisode != nullptr)
                ((cEpisodeObject*)pEpisode)->GetRecord();
        }
        pCreature->UpdatePose();
        SetBehaviorState(pCreature, 0x14);
        pCreature->UpdateAttackTarget();
        SetBehaviorState(pCreature, 0x14);
        break;

    default:
        break;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d9e420  FinishBehaviorTask
// ---------------------------------------------------------------------------
// @ 0x00d9e420
void FinishBehaviorTask(cSimCreature* pCreature, void* pA, void* pB, void* pC,
                        void* pD, cBehaviorCallback* pCallback)
{
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0, 0x200);
    void* pManager = BehaviorManager(pCreature);
    ((cEpisodeObject*)pManager)->GetRecord();
    if (pCallback == nullptr)
        return;
    cBehaviorHandler* pHandler = (cBehaviorHandler*)pCallback->mpHandler;
    if (pHandler != nullptr)
        pHandler->Method04();
}

// ---------------------------------------------------------------------------
// 0x00d9e460  cGroupMovement::PickLeader
// ---------------------------------------------------------------------------
// @ 0x00d9e460
char cGroupMovement::PickLeader(cSimCreature* pCreature, void* pA, void* pB,
                                void* pC, void* pD, cLeaderChoice* pChoice)
{
    if (pChoice != nullptr)
        pChoice->mpLeader = nullptr;
    pChoice->mbChanged = 0;

    if (!pCreature->mMovement.CallChar(0x58)) {
        pChoice->mnAnimId = pCreature->InterruptAnimation(0x6578211, -1, 0);
        return 1;
    }

    if (pCreature->IsGroupLeader()) {
        pChoice->mnAnimId = pCreature->InterruptAnimation(0x6578207, -1, 0);
        void* pStimuli = pCreature->mpBehaviorTree->mStimuli.Play(0x800000, 0);
        void* pLeader = nullptr;
        if (pStimuli != nullptr)
            pLeader = ((cDispatchObject*)pStimuli)->Call(0x0c);
        void* pPrevious = pChoice->mpLeader;
        if (pLeader != pPrevious) {
            if (pLeader != nullptr)
                ((cPoolObject*)pLeader)->AddRef();
            pChoice->mpLeader = pLeader;
            if (pPrevious != nullptr)
                ((cPoolObject*)pPrevious)->Destroy(0);
        }
        return 1;
    }

    switch (pCreature->GetBehaviorPhase()) {
    case 4:
        pChoice->mnAnimId = pCreature->InterruptAnimation(0x657820b, -1, 0);
        return 1;
    case 5:
        pChoice->mnAnimId = pCreature->InterruptAnimation(0x657820e, -1, 0);
        return 1;
    case 6:
        pChoice->mnAnimId = pCreature->InterruptAnimation(0x6578208, -1, 0);
        return 1;
    default:
        break;
    }
    pChoice->mnAnimId = pCreature->InterruptAnimation(0x6578211, -1, 0);
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d9e570  RunTargetBehavior
// ---------------------------------------------------------------------------
// @ 0x00d9e570
char RunTargetBehavior(cSimCreature* pCreature, void* pA, void* pB, void* pC,
                       void* pD, cBehaviorTask* pTask)
{
    uint8_t mEventData[0x44];
    void* pTarget = pCreature->GetTargetCreature();
    if (!IsValidBehaviorTarget(pTarget)) {
        SetBehaviorState(pCreature, 0x15);
        return 0;
    }

    switch (pTask->mnState) {
    case 0:
        if (pCreature->WaitForAnimEvent(0xbfa50b5a, mEventData, 0,
                                        pTask->mnAnimId, 0)) {
            void* pLocation = pCreature->mLocation.GetObject();
            if (pLocation != nullptr)
                AttachTargetInfo(pCreature, pTarget, pLocation);
        }
        if (pCreature->AnimationFinished(pTask->mnAnimId))
            pTask->mnState = 1;
        break;

    case 1:
        if (pCreature->WaitForAnimEvent(0xbfa50b5a, mEventData, 0,
                                        pTask->mnAnimId, 0)) {
            pCreature->StopLocomotion(0, -1);
            int32_t nCount = 5;
            void* pData = pCreature->GetTargetRecord();
            if (pData != nullptr)
                nCount = GetWorldConstant(((cTargetData*)pData)->mnCount,
                                          0xeb69140e, 5);
            void* pLocation = pCreature->mLocation.GetObject();
            uint32_t* pLink = GetActionLink(pCreature);
            float fDistance = ((cNounManager*)NounManager())->GetDistance(
                pLink, (float)nCount, 0);
            if (fDistance < 0.0f) {
                ((cActionObject*)pCreature->GetActionObject())->SetTarget(
                    fDistance);
                ((cNounManager*)NounManager())->MoveTo(pLocation, pLink,
                                                       -fDistance, 6);
                SetBehaviorState(pCreature, 0x15);
                return 0;
            }
            ((cActionObject*)pCreature->GetActionObject())->MoveTowards(
                fDistance);
            ((cNounManager*)NounManager())->MoveTo(pLocation, pLink, fDistance,
                                                   6);
        }
        if (pCreature->AnimationFinished(pTask->mnAnimId))
            pTask->mnState = 2;
        break;

    case 2:
        pCreature->NotifyTargetLost();
        pCreature->ResetPose();
        break;

    case 3:
        if (pCreature->WaitForAnimEvent(0xbfa50b5a, mEventData, 0,
                                        pTask->mnAnimId, 0)) {
            void* pLocation = pCreature->mLocation.GetObject();
            if (pLocation != nullptr)
                AttachTargetInfo(pCreature, pTarget, pLocation);
            void* pRecord = ((cWorldManager*)WorldManager())->FindObject(
                pLocation);
            if (pRecord != nullptr) {
                void* pEpisode = ((cWorldManager*)WorldManager())
                                     ->GetObjectData(pRecord);
                if (pEpisode != nullptr)
                    ((cEpisodeObject*)pEpisode)->GetRecord();
            }
        }
        if (pCreature->AnimationFinished(pTask->mnAnimId)) {
            void* pNewTarget = pCreature->GetTargetCreature();
            if (IsValidBehaviorTarget(pNewTarget))
                pCreature->mMovement.CallVoid(0x2c);
        }
        break;

    case 4:
        pCreature->UpdateTargetPose();
        pCreature->UpdateWorldTarget();
        SetBehaviorState(pCreature, 0x15);
        pCreature->GetActionObject();
        SetBehaviorState(pCreature, 0x15);
        break;

    default:
        break;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d9ea30  StartFindTargetBehavior
// ---------------------------------------------------------------------------
// @ 0x00d9ea30
char StartFindTargetBehavior(cSimCreature* pCreature, void* pA, void* pB,
                             void* pC, cFoundTarget* pFound)
{
    if (pFound != nullptr)
        pFound->mpObject = nullptr;

    void* pAnimation = pCreature->mpBehaviorTree->mStimuli.Play(0x2000000, 0);
    void* pResult = GetObjectFromId(WatchMemoryBlock(pAnimation));
    if (pResult == nullptr || pResult == pCreature) {
        pCreature->mpBehaviorTree->mStimuli.ClearAll(0x2000000, 0);
        return 0;
    }

    pCreature->mMovement.CallVoid(0xec);
    pCreature->SetCombatEngaged(!pCreature->mMovement.CallChar(0xf8));

    void* pPrevious = pFound->mpObject;
    pFound->mnField14 = 0;
    if (pResult != pPrevious) {
        ((cPoolObject*)pResult)->AddRef();
        pFound->mpObject = pResult;
        if (pPrevious != nullptr)
            ((cPoolObject*)pPrevious)->Destroy(0);
    }

    const uint32_t* pAnimationData = (const uint32_t*)pAnimation;
    pFound->mnField04 = pAnimationData[3];
    pFound->mnField08 = pAnimationData[4];
    pFound->mnField0c = pAnimationData[5];
    pFound->mfField10 = ((const float*)pAnimationData)[6];
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d9eb20  CancelBehaviorTask
// ---------------------------------------------------------------------------
// @ 0x00d9eb20
void CancelBehaviorTask(cSimCreature* pCreature, void* pA, void* pB, void* pC,
                        void* pD, cBehaviorCallback* pCallback)
{
    pCreature->mMovement.CallVoid(0xec);
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0x2000000, 0);
    if (pCallback != nullptr && pCallback->mpTarget != nullptr)
        ((cBehaviorHandler*)pCallback->mpTarget)->Method04();
}

// ---------------------------------------------------------------------------
// 0x00d9eb70  cSocialBandPool::GetObject
// ---------------------------------------------------------------------------
// @ 0x00d9eb70
cPoolObject* cSocialBandPool::GetObject(uint32_t nIndex)
{
    uint32_t nCount = (uint32_t)(mpEnd - mpBegin);
    uint32_t nSlot = nIndex & 0xbfffffff;
    if (nSlot < nCount) {
        cPoolSlot* pSlot = &mpBegin[nSlot];
        uint32_t* pFlags = &pSlot->mnLinkFlags;
        if (pSlot->mbUsed == 0)
            return (cPoolObject*)(pFlags + 1);
    }
    return nullptr;
}

// ---------------------------------------------------------------------------
// 0x00d9ebc0  cSocialBandPool::ReleaseObject
// ---------------------------------------------------------------------------
// @ 0x00d9ebc0
void cSocialBandPool::ReleaseObject(uint32_t nIndex)
{
    cPoolSlot* pSlot = mpBegin + nIndex;
    ((cPoolObject*)pSlot->mObject)->Destroy(0);

    uint32_t nHead = mnHeadIndex;
    pSlot->mnLinkFlags = (pSlot->mnLinkFlags & 0xc0000000) | (nHead & 0x3fffffff) |
                         0x80000000;
    mnHeadIndex = nIndex;
    if (mnTailIndex == nIndex)
        mnTailIndex = GetNextFreeSlot(nIndex);
}
