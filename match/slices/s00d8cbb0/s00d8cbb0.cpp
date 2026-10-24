// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 36 / slice s00d8cbb0.
//
// Creature behaviour-tree stimuli probes and simple action ticks:
//   - neighbour based "something happened nearby" probes,
//   - the egg-nearby and startled-response probes,
//   - the claim-nest and startled-response action ticks.
//
// Creature field names follow the offsets used by the whole behaviour family:
// the neighbour entry vector at +0x1124, the animation entry vector at
// +0x13d4, the animation player at +0xb4c and the stimulus slot at +0x5a8.

typedef unsigned int size_t;
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef int int32_t;
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

struct Mat3 {
    float mElements[9];
};

// ---------------------------------------------------------------------------
// Small shared objects
// ---------------------------------------------------------------------------

class cCreature;

// A spatial transform; position and orientation are virtual getters.
class cSpatial {
public:
    const Vec3* GetPosition() {
        return ((const Vec3* (__thiscall*)(cSpatial*))((void**)mpVtable)[0x2c / 4])(this);
    }
    const Vec4* GetOrientation() {
        return ((const Vec4* (__thiscall*)(cSpatial*))((void**)mpVtable)[0x30 / 4])(this);
    }

    void* mpVtable;                             // 0x00
};

// The playback sub-channel of a creature animation player (player + 0x08).
class cAnimationChannel {
public:
    void* PlayAnimation(int nFlags, int nMode);                          // 0x00bc96a0
    void Play(uint32_t nFlags, int nA, float fValue, void* pTarget);     // 0x00bc97f0

    uint8_t mPad[0x1c8];
};

class cAnimator {
public:
    uint8_t mPad000[0x08];                      // 0x000
    cAnimationChannel mChannel;                 // 0x008
    uint32_t mThreatSet;                        // 0x1d0
    uint8_t mPad1d4[0x428];                     // 0x1d4
    uint32_t mnFlags;                           // 0x5fc
};

// The controller object reached through cCreature::mpAnimationController.
class cAnimationController {
public:
    char TestFlag(uint32_t nFlag);                                       // 0x00bc9a00
    void SetFlag(uint32_t nFlag, float fValue, int nA, int nB);          // 0x00bc9d40
};

// One entry of the neighbour / animation entry vectors.
struct cNeighbourEntry {
    void* mpOwnerKey;                           // 0x00
    uint8_t mbFlag4;                            // 0x04
    uint8_t mbFlag5;                            // 0x05
    uint8_t mPad006[0x02];                      // 0x06
    cCreature* mpCreature;                      // 0x08
};

// Iterator over a neighbour entry vector.
class cNeighbourIterator {
public:
    char IsValid(cNeighbourEntry* pEntry);      // 0x00c02600
    void Advance();                             // 0x00b3d850

    void** mpCurrent;                           // 0x00
    void** mpEnd;                               // 0x04
};

// Iterator over the animation entry vector.
class cAnimIterator {
public:
    char IsValid(void* pEntry);                 // 0x00c02650
    cAnimIterator* Advance();                   // 0x00d7cf50

    void** mpCurrent;                           // 0x00
    void** mpEnd;                               // 0x04
};

// The query object embedded in the creature at +0xb28.
class cProximityQuery {
public:
    int Count();                                // 0x00ba3f90

    uint8_t mData[0x24];
};

// The game-data object returned by cCreature::GetGameData.
class cGameData {
public:
    uint8_t mPad000[0x15c];                     // 0x000
    uint32_t mnGameMode;                        // 0x15c
    void* mpLinkedObject;                       // 0x160
    void* mpActiveCreature;                     // 0x164
    void* mpCollisionList;                      // 0x168
    uint8_t mPad16c[0x4b8];                     // 0x16c
    uint32_t mnContextKey;                      // 0x624
};

// The behaviour stimulus slot filled in by the probes.
class cBehaviorStimuli {
public:
    void* GetAny();                             // 0x00d997e0

    void* mpReserved0;                          // 0x00
    void* mpTargetEntry;                        // 0x04
    uint8_t mPad008[0x14];                      // 0x08
    float mfStimulusValue;                      // 0x1c
};

// A nearby-object filter/context object held by the tree node.
class cStimulusContext {
public:
    uint8_t mPad000[0x2d];                      // 0x000
    uint8_t mnKey;                              // 0x02d
};

class cXformMsg {
public:
    cXformMsg();                                                // 0x00434040
    void SetPosition(const Vec3* pPosition);                    // 0x00571d40

    uint8_t mPad000[0x08];                      // 0x00
    uint16_t mnFlags;                           // 0x08
    uint16_t mnCount;                           // 0x0a
    uint8_t mPad00c[0x10];                      // 0x0c
    Mat3 mTransform;                            // 0x1c
};

class cVisualEffect {
public:
    void Send(const cXformMsg* pMessage);       // vtable 0x18
    void Release();                             // vtable 0x04
};

class cEffectManager {
public:
    char CreateEffect(uint32_t nEffectId, int nMode, cVisualEffect** ppEffect);   // vtable 0x2c
};

// The tick state block of the nest / response actions.
class cActionState {
public:
    int mnState;                                // 0x00
    cCreature* mpTarget;                        // 0x04
    int mnAnimation;                            // 0x08
    uint32_t mnAnimationId;                     // 0x0c
    int mnEvent;                                // 0x10
    uint8_t mPad014[0x08];                      // 0x14
    uint8_t mbReady;                            // 0x1c
};

// ---------------------------------------------------------------------------
// Creature
// ---------------------------------------------------------------------------

class cCreature {
public:
    cGameData* GetGameData();                                        // 0x00c04590
    uint32_t GetTypeId() {
        return ((uint32_t (__thiscall*)(cCreature*))((void**)mpVtable)[0x20 / 4])(this);
    }
    char IsScareable() {
        return ((char (__thiscall*)(cCreature*))((void**)mpVtable)[0xd0 / 4])(this);
    }
    char v2c() {
        return ((char (__thiscall*)(cCreature*))((void**)mpVtable)[0x2c / 4])(this);
    }
    char v0c0(cCreature* pOther, float fA, float fB) {
        return ((char (__thiscall*)(cCreature*, cCreature*, float, float))
                    ((void**)mpVtable)[0xc0 / 4])(this, pOther, fA, fB);
    }
    void* v084(void* pTarget, int nA, int nB) {
        return ((void* (__thiscall*)(cCreature*, void*, int, int))
                    ((void**)mpVtable)[0x84 / 4])(this, pTarget, nA, nB);
    }
    void SetLinkedObject(int nValue);                                // 0x00c69bb0
    void MoveToPointAtSpeed(int nMode, const Vec3* pPosition, float fA, float fB); // 0x00c1c1d0
    void MoveToPointAtSpeed(int nMode, const Vec3* pPosition);
    char IsNearGoal();                                               // 0x00c42e20
    int InterruptAnimation(uint32_t nAnimationId, int nFlags, int nMode); // 0x00c12310
    char AnimationFinished(int nAnimation);                          // 0x00c12400
    char WaitForAnimEventOrEnd(uint32_t nEventId, int* pOut, uint32_t nAnimationId,
                               int nAnimation, int nMode);           // 0x00c14ef0
    uint32_t GetSpeciesProfile();                                    // 0x00c0bbd0
    char Flag388();                                                  // 0x00c0c0e0
    char AcceptTarget(cCreature* pOther);                            // 0x00c0b860
    char IsProximityClose(cCreature* pOther, float fA, float fB);    // 0x00c0d560
    int FindNearby(cCreature* pOther, uint32_t nFilter, float fValue,
                   int nA, int nB, int nC, int nD);                  // 0x00c12410
    void PlayAnimation(uint32_t nAnimationId, int nA, int nFlags);    // 0x00c12190

    void* mpVtable;                             // 0x000
    uint8_t mPad004[0x30];                      // 0x004
    cSpatial mSpatial;                          // 0x034
    uint8_t mPad038[0x88];                      // 0x038
    cSpatial mLocomotive;                       // 0x0c0
    uint8_t mPad0c4[0x4e4];                     // 0x0c4
    int mStimulusTarget;                        // 0x5a8
    uint8_t mPad5ac[0x574];                     // 0x5ac
    uint32_t mnId;                              // 0xb20
    uint8_t mPadb24[0x04];                      // 0xb24
    cProximityQuery mProximityQuery;            // 0xb28
    cAnimator* mpAnimator;                      // 0xb4c
    uint8_t mPadb50[0x08];                      // 0xb50
    uint32_t mnFlags;                           // 0xb58
    uint8_t mPadb5c[0x02];                      // 0xb5c
    uint8_t mbHidden;                           // 0xb5e
    uint8_t mPadb5f[0x45a];                     // 0xb5f
    uint8_t mbStimulusCooldown;                 // 0xfb9
    uint8_t mPadfba[0x62];                      // 0xfba
    uint32_t mnBehaviourState;                  // 0x101c
    uint8_t mPad1020[0x104];                    // 0x1020
    void** mpNeighboursBegin;                   // 0x1124
    void** mpNeighboursEnd;                     // 0x1128
    uint8_t mPad112c[0x2a8];                    // 0x112c
    void** mpAnimEntriesBegin;                  // 0x13d4
    void** mpAnimEntriesEnd;                    // 0x13d8
    uint8_t mPad13dc[0x248];                    // 0x13dc
    cAnimationController* mpAnimationController; // 0x1624
};

// ---------------------------------------------------------------------------
// Helper functions
// ---------------------------------------------------------------------------

class cPlanetModel;

void* operator_new(size_t nSize);
void operator_delete__(void* pMemory);

class cNounManager {
public:
    cCreature* GetAvatar();                                 // 0x00b1fdb0
};
cNounManager* NounManager();                                // 0x00b3d300
cProximityQuery* ProximityQuery_Build(cProximityQuery* pQuery, cCreature* pOwner,
                                      cCreature* pTarget);  // 0x00b3d4c0
void* ProximityQuery_Find(void* pQuery, cCreature* pOwner, void* pTarget); // unused helper
float GetStimulusValue(int nSlot, cCreature* pCreature);    // 0x00d38a30
float GetDistance(cSpatial* pA, cSpatial* pB, int nMode);   // 0x00d99ac0
void* BehaviorSet_Get(void* pSet, int nKey);                // 0x00d99420
void* BehaviorSet_Lookup(void* pSet, cBehaviorStimuli* pStimuli); // 0x00d996e0
void* BehaviorSet_Resolve(void* pHandle);                   // 0x00d99470
void* Object_LookupByKey(void* pObject, uint32_t nKey);     // 0x00ac80d0
cProximityQuery* NeighbourVector_Find(cAnimIterator* pIterator, void** pVector,
                                      void* pFilter);       // 0x00b41a40
void ClaimNearbyNestForAvatar(cCreature* pCreature);        // 0x00d40cc0
void* GetClaimContext();                                    // 0x00d51660
int ClaimContext_GetValue(void* pThis);                     // 0x0113ae10
void* EffectsManagerPtr();                                  // 0x0067ddd0
void* AutoRefCount_AsPPTypeParam(void* pOut);               // 0x00a16f40
cPlanetModel* PlanetModel(Vec3* pOut, const Vec3* pDirection, float fA,
                          float fB);                        // 0x00b3d350
void Matrix3FromQuaternion(Mat3* pOut, const Vec4* pQuaternion); // 0x0059c190
char IsValidNeighbourEntry(cNeighbourIterator* pIterator, cNeighbourEntry* pEntry); // 0x00c02600

class cPlanetModel {
public:
    Vec3* DirectionToSurfacePosition(Vec3* pOut, const Vec3* pDirection); // 0x00b815a0
};

extern const float gStimulusValue;      // 0x01582fdc
extern const float gStimulusRange;      // 0x01582fe0
extern const float gRunSpeed;           // 0x01470f1c
extern const float gEggSightRangeSq;    // 0x013ec4d0
extern const float gEggSightRangeSq2;   // 0x014007f4
extern const float gFleeDistanceSq;     // 0x01486110
extern const float gStartleTrigger;     // 0x014853bc
extern const float gDirectionEpsilon;   // 0x013ec4b8
extern const float gStartleStep;        // 0x014853e0
extern const float gInitialBestSq;      // 0x0147c030

// ---------------------------------------------------------------------------
// 0x00d8cbb0  neighbour based stimulus probe
// ---------------------------------------------------------------------------
// @ 0x00d8cbb0
float StimulusProbe_Neighbour(cCreature* pCreature, int nUnused1, int nUnused2,
                              uint32_t nFlags, cBehaviorStimuli* pStimuli, uint8_t* pbFlag)
{
    if (pCreature->mnBehaviourState != 1)
        return 0.0f;

    if ((nFlags & 0x408) != 0) {
        if (pCreature->IsScareable())
            return 0.0f;
        cGameData* pGameData = pCreature->GetGameData();
        cCreature* pAvatar = NounManager()->GetAvatar();
        if (pAvatar == 0 || pAvatar->mbHidden)
            return 0.0f;
        if (pGameData != 0 && (pGameData->mnGameMode == 10 || pGameData->mnGameMode == 1)) {
            cProximityQuery* pQuery =
                ProximityQuery_Build(&pCreature->mProximityQuery, pCreature, pAvatar);
            if (pQuery->Count() == 3)
                return 0.0f;
        }
        if (pStimuli != 0)
            pStimuli->GetAny();
        *pbFlag = 1;
        pStimuli->mpTargetEntry = &pAvatar->mStimulusTarget;
        return 1.0f;
    }

    bool bCooldownExpired = false;
    if (pCreature->mbStimulusCooldown != 0) {
        cAnimationController* pController = pCreature->mpAnimationController;
        if (!pController->TestFlag(0x200))
            bCooldownExpired = true;
    }

    cNeighbourIterator iterator;
    iterator.mpCurrent = pCreature->mpNeighboursBegin;
    iterator.mpEnd = pCreature->mpNeighboursEnd;
    if (iterator.mpCurrent == iterator.mpEnd)
        return 0.0f;
    if (!IsValidNeighbourEntry(&iterator, (cNeighbourEntry*)*iterator.mpCurrent))
        iterator.Advance();

    while (iterator.mpCurrent != iterator.mpEnd) {
        cNeighbourEntry* pEntry = (cNeighbourEntry*)*iterator.mpCurrent;
        cCreature* pOther = pEntry->mpCreature;
        if ((pEntry->mbFlag4 != 0 || pEntry->mbFlag5 != 0)
            && pOther->IsScareable()
            && !pOther->mbHidden
            && pOther->GetTypeId() == 0x018eb4b7
            && (bCooldownExpired
                || GetDistance(&pCreature->mLocomotive, &pOther->mLocomotive, 1)
                       < gStimulusRange)) {
            pCreature->mbStimulusCooldown = 0;
            pCreature->mpAnimationController->SetFlag(0x200, gStimulusValue, 0, 0);
            if (pStimuli != 0)
                pStimuli->GetAny();
            *pbFlag = 1;
            pStimuli->mpTargetEntry = &pOther->mStimulusTarget;
            pStimuli->mfStimulusValue = gStimulusValue;
            return 1.0f;
        }

        do {
            ++iterator.mpCurrent;
            if (iterator.mpCurrent == iterator.mpEnd)
                return 0.0f;
        } while (!IsValidNeighbourEntry(&iterator, (cNeighbourEntry*)*iterator.mpCurrent));
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00d8cde0  self state stimulus probe
// ---------------------------------------------------------------------------
// @ 0x00d8cde0
float StimulusProbe_SelfState(cCreature* pCreature, int nUnused1, int nUnused2, int nUnused3,
                              cBehaviorStimuli* pStimuli, uint8_t* pbFlag, int nUnused4,
                              cStimulusContext* pContext)
{
    cGameData* pGameData = pCreature->GetGameData();
    if (pCreature == pGameData->mpActiveCreature
        && pGameData->mpCollisionList != &pGameData->mpCollisionList)
        return 0.0f;

    if (pStimuli != 0)
        pStimuli->GetAny();
    *pbFlag = 1;

    void* pSet = BehaviorSet_Get(&pCreature->mpAnimator->mThreatSet, pContext->mnKey);
    BehaviorSet_Lookup(pSet, pStimuli);

    cCreature* pOther = 0;
    if (pStimuli->mpTargetEntry != 0)
        pOther = (cCreature*)BehaviorSet_Resolve(
            ((void* (__thiscall*)(void*, uint32_t))
                ((void**)((void**)pStimuli->mpTargetEntry)[0])[0x5c / 4])
                (pStimuli->mpTargetEntry, 0xce9f6639));

    if (pOther == 0)
        return 0.0f;

    float fFirst = GetStimulusValue(2, pCreature);
    float fSecond = GetStimulusValue(1, pCreature);
    float fDistance = GetDistance(&pCreature->mLocomotive, &pOther->mLocomotive, 1);

    uint32_t nFilter[3] = {0, 0, 0};
    for (uint32_t i = 0; i < 3; ++i)
        nFilter[i] = ~nFilter[i];
    nFilter[2] &= 0xffffff;
    if (pCreature->Flag388())
        nFilter[0] &= 0x7fffffff;

    if (pCreature->AcceptTarget(pOther)) {
        if (pCreature->FindNearby(pOther, nFilter[0], fDistance, 0, 0, 0, 0) != -1
            || fDistance <= GetStimulusValue(5, pCreature)
            || pCreature->IsProximityClose(pOther, fSecond, fDistance)
            || pCreature->v0c0(pOther, fFirst, fDistance))
            return 1.0f;
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00d8cf80  nearby enemy egg probe
// ---------------------------------------------------------------------------
// @ 0x00d8cf80
float NEARBY_ENEMY_EGG_Decide(cCreature* pCreature)
{
    void* pAnimation = pCreature->mpAnimator->mChannel.PlayAnimation(0x80, 0);
    cCreature* pEgg = (cCreature*)BehaviorSet_Resolve(pAnimation);
    if (pEgg != 0 && pEgg->mnBehaviourState != 4 && pEgg->mnFlags == 0)
        return 1.0f;

    cAnimIterator iterator;
    iterator.mpCurrent = pCreature->mpAnimEntriesBegin;
    iterator.mpEnd = pCreature->mpAnimEntriesEnd;
    if (iterator.mpCurrent == iterator.mpEnd)
        return 0.0f;
    if (!iterator.IsValid(*iterator.mpCurrent))
        iterator.Advance();

    for (;;) {
        cNeighbourEntry* pEntry = (cNeighbourEntry*)*iterator.mpCurrent;
        cCreature* pOther = pEntry->mpCreature;
        if (pOther != 0 && pOther->mnId != 0) {
            cCreature* pNearby = (cCreature*)pEntry->mpOwnerKey;
            if (pNearby != 0 && pNearby->GetSpeciesProfile() != pCreature->GetSpeciesProfile()
                && pEntry->mbFlag4 != 0 && pOther->mnBehaviourState != 4) {
                const Vec3* pOtherPos = pNearby->mSpatial.GetPosition();
                const Vec3* pPos = pOther->mSpatial.GetPosition();
                float fX = pPos->mX - pOtherPos->mX;
                float fY = pPos->mY - pOtherPos->mY;
                float fZ = pPos->mZ - pOtherPos->mZ;
                float fDistanceSq = fZ * fZ + fY * fY + fX * fX;
                if (fDistanceSq > gEggSightRangeSq && pOther->mnFlags == 0) {
                    pCreature->mpAnimator->mChannel.Play(0x80, 0, 100.0f, pOther);
                    return 1.0f;
                }
            }
        }
        do {
            ++iterator.mpCurrent;
            if (iterator.mpCurrent == iterator.mpEnd)
                return 0.0f;
        } while (!iterator.IsValid(*iterator.mpCurrent));
    }
}

// ---------------------------------------------------------------------------
// 0x00d8d110  closest visible neighbour probe
// ---------------------------------------------------------------------------
// @ 0x00d8d110
float StimulusProbe_ClosestNeighbour(cCreature* pCreature, int nUnused1, int nUnused2,
                                     uint32_t nFlags, cBehaviorStimuli* pStimuli,
                                     uint8_t* pbFlag)
{
    if ((nFlags & 0x40000) != 0)
        return 0.0f;

    float fBestDistanceSq = gInitialBestSq;
    bool bHidden = ((nFlags >> 0x17) & 1) != 0;
    cCreature* pBest = 0;

    cNeighbourIterator iterator;
    iterator.mpCurrent = pCreature->mpNeighboursBegin;
    iterator.mpEnd = pCreature->mpNeighboursEnd;
    if (iterator.mpCurrent == iterator.mpEnd)
        return 0.0f;
    if (!IsValidNeighbourEntry(&iterator, (cNeighbourEntry*)*iterator.mpCurrent))
        iterator.Advance();

    while (iterator.mpCurrent != iterator.mpEnd) {
        cNeighbourEntry* pEntry = (cNeighbourEntry*)*iterator.mpCurrent;
        cCreature* pOther = pEntry->mpCreature;
        if (pOther != 0 && pOther->mnId != pCreature->mnId && !pOther->mbHidden
            && pOther->mpAnimator != 0) {
            bool bOtherHidden;
            if (pOther->GetTypeId() == 0x018eb45e)
                bOtherHidden = ((pOther->mpAnimator->mnFlags >> 0x17) & 1) != 0;
            else if (pOther->GetTypeId() == 0x018eb4b7)
                bOtherHidden = pOther->mpAnimator->mChannel.PlayAnimation(0x1000, 0) != 0;
            else
                bOtherHidden = false;

            if (bOtherHidden != bHidden) {
                const Vec3* pPos = pOther->mLocomotive.GetPosition();
                const Vec3* pOwnPos = pCreature->mLocomotive.GetPosition();
                float fX = pPos->mX - pOwnPos->mX;
                float fY = pPos->mY - pOwnPos->mY;
                float fZ = pPos->mZ - pOwnPos->mZ;
                float fDistanceSq = fZ * fZ + fY * fY + fX * fX;
                if (fDistanceSq < fBestDistanceSq) {
                    fBestDistanceSq = fDistanceSq;
                    pBest = pOther;
                }
            }
        }
        do {
            ++iterator.mpCurrent;
            if (iterator.mpCurrent == iterator.mpEnd)
                goto done;
        } while (!IsValidNeighbourEntry(&iterator, (cNeighbourEntry*)*iterator.mpCurrent));
    }

done:
    if (pBest != 0) {
        if (pStimuli != 0)
            pStimuli->GetAny();
        *pbFlag = 1;
        pStimuli->mpTargetEntry = &pBest->mStimulusTarget;
        return 1.0f;
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00d8d300  claim nest action tick
// ---------------------------------------------------------------------------
// @ 0x00d8d300
int CLAIM_NEST_Tick(int nUnused, cCreature* pCreature, int nUnused1, int nUnused2,
                    int nUnused3, cActionState* pState)
{
    cCreature* pTarget = pState->mpTarget;
    if (pTarget == 0 || !*(uint8_t*)&pTarget->mnBehaviourState)
        return 0;
    if (pTarget->v2c())
        return 0;

    switch (pState->mnState) {
    case 0:
        pCreature->MoveToPointAtSpeed(2, pTarget->mSpatial.GetPosition(), 1.0f, gRunSpeed);
        if (pCreature->IsNearGoal())
            pState->mnState = 1;
        return 1;

    case 1:
        if (pState->mnAnimation == 0) {
            pState->mnAnimation =
                pCreature->InterruptAnimation(pState->mnAnimationId, -1, 0);
            return 1;
        }
        if (pCreature->AnimationFinished(pState->mnAnimation) && pState->mbReady == 1) {
            pState->mnState = 3;
            return 1;
        }
        {
            int nEvent = -1;
            char bDone = pCreature->WaitForAnimEventOrEnd(0xed41b225, &nEvent,
                                                          pState->mnAnimationId,
                                                          pState->mnAnimation, 1);
            if (pState->mbReady != 0 || !bDone)
                return 1;

            pState->mbReady = 1;
            cGameData* pGameData = pCreature->GetGameData();
            ((cCreature*)pGameData->mpLinkedObject)->SetLinkedObject(0);
            ClaimNearbyNestForAvatar(pTarget);
            void* pContext = GetClaimContext();
            pTarget->SetLinkedObject(ClaimContext_GetValue(pContext));

            cProximityQuery query;
            NeighbourVector_Find((cAnimIterator*)&query, pCreature->mpNeighboursBegin,
                                 &query);
            cNeighbourIterator iterator;
            iterator.mpCurrent = pCreature->mpNeighboursBegin;
            iterator.mpEnd = pCreature->mpNeighboursEnd;
            if (iterator.mpCurrent != iterator.mpEnd) {
                if (!IsValidNeighbourEntry(&iterator,
                                           (cNeighbourEntry*)*iterator.mpCurrent))
                    iterator.Advance();
                while (iterator.mpCurrent != iterator.mpEnd) {
                    cNeighbourEntry* pEntry = (cNeighbourEntry*)*iterator.mpCurrent;
                    cCreature* pNearby =
                        (cCreature*)Object_LookupByKey(pEntry->mpCreature, 0x018eb45e);
                    if (pNearby != 0 && ((pNearby->mnFlags >> 9) & 1) == 0
                        && pNearby->IsScareable())
                        pNearby->mpAnimator->mChannel.Play(0x200000, 0, gFleeDistanceSq,
                                                           pState->mpTarget);
                    iterator.Advance();
                }
            }

            cEffectManager* pEffects = (cEffectManager*)EffectsManagerPtr();
            cVisualEffect* pEffect = 0;
            if (pEffects->CreateEffect(0x7a33577b, 0, &pEffect)) {
                cXformMsg message;
                message.SetPosition(pTarget->mSpatial.GetPosition());
                Matrix3FromQuaternion(&message.mTransform, pTarget->mSpatial.GetOrientation());
                message.mnFlags |= 2;
                ++message.mnCount;
                pEffect->Send(&message);
                pCreature->SetLinkedObject(0);
            }
            if (pEffect != 0)
                pEffect->Release();
            return 1;
        }

    case 3:
        return 0;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d8d5b0  startled response activation
// ---------------------------------------------------------------------------
// @ 0x00d8d5b0
int STARTLED_RESPONSE_Activate(cCreature* pCreature, int nUnused1, int nUnused2,
                               int nUnused3, int nUnused4, int nUnused5,
                               cActionState* pState)
{
    if (pState->mpTarget == 0)
        return 0;
    cCreature* pThreat = (cCreature*)BehaviorSet_Resolve(
        ((void* (__thiscall*)(void*, uint32_t))((void**)((void**)pState->mpTarget)[0])[0x5c / 4])
            (pState->mpTarget, 0xce9f6639));
    if (pThreat == 0)
        return 0;

    pCreature->v084(&pThreat->mStimulusTarget, 1, 0);
    pThreat->mnFlags = 0;

    if (!pCreature->AcceptTarget(pThreat))
        goto finish;

    {
        const Vec3* pThreatPos = pThreat->mLocomotive.GetPosition();
        const Vec3* pOwnPos = pCreature->mLocomotive.GetPosition();
        float fX = pThreatPos->mX - pOwnPos->mX;
        float fY = pThreatPos->mY - pOwnPos->mY;
        float fZ = pThreatPos->mZ - pOwnPos->mZ;
        float fScale = 1.0f / (fY * fY + (fX * fX + fZ * fZ) + gDirectionEpsilon);

        Vec3 aim;
        aim.mX = pOwnPos->mX + (fScale * fX) * gStartleStep;
        aim.mY = pOwnPos->mY + (fScale * fY) * gStartleStep;
        aim.mZ = pOwnPos->mZ + (fScale * fZ) * gStartleStep;

        Vec3 surface;
        cPlanetModel* pPlanet = PlanetModel(&surface, &aim, 1.0f, gRunSpeed);
        pCreature->MoveToPointAtSpeed(3, pPlanet->DirectionToSurfacePosition(&surface, &aim));

        cNeighbourIterator iterator;
        iterator.mpCurrent = pCreature->mpNeighboursBegin;
        iterator.mpEnd = pCreature->mpNeighboursEnd;
        if (iterator.mpCurrent != iterator.mpEnd) {
            if (!IsValidNeighbourEntry(&iterator, (cNeighbourEntry*)*iterator.mpCurrent))
                iterator.Advance();
            while (iterator.mpCurrent != iterator.mpEnd) {
                cNeighbourEntry* pEntry = (cNeighbourEntry*)*iterator.mpCurrent;
                cCreature* pNearby = pEntry->mpCreature;
                if (pNearby != 0 && pNearby->GetTypeId() == 0x018eb45e
                    && pNearby->GetSpeciesProfile() == pCreature->GetSpeciesProfile())
                    pNearby->mpAnimator->mChannel.Play(0, 0x40, gStartleTrigger, pThreat);
                do {
                    ++iterator.mpCurrent;
                    if (iterator.mpCurrent == iterator.mpEnd)
                        goto finish;
                } while (!IsValidNeighbourEntry(&iterator,
                                                (cNeighbourEntry*)*iterator.mpCurrent));
            }
        }
    }

finish:
    pCreature->InterruptAnimation(0x92314082, -1, 0);
    pCreature->PlayAnimation(0x52314083, 1, -1);
    return 1;
}
