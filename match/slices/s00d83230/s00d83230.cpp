// Slice s00d83230 -- SP::AVATAR_IDLE_Tick (Simulator avatar idle-state tick).
// Flags: /O2 /MD /Gy /EHsc /TP /arch=SSE /fp=fast.  Callees are masked relocations.
typedef unsigned int uint;

const int kAvatarIdleGuid = 0x27844ad;

// ---------------------------------------------------------------------------------------------
// externs
// ---------------------------------------------------------------------------------------------
struct RandomLinearCongruential {
    unsigned int RandomUint32Uniform(unsigned int n);        // 0x00a68fb0
};

extern RandomLinearCongruential gRandom;                     // 0x01601760
extern unsigned char gAvatarIdleSuppressed;                  // 0x0169e381

// ---------------------------------------------------------------------------------------------
// animation provider queried for the current animation (vtable slot at +0x58)
// ---------------------------------------------------------------------------------------------
struct AnimProvider {
    virtual void v00();  virtual void v01();  virtual void v02();  virtual void v03();
    virtual void v04();  virtual void v05();  virtual void v06();  virtual void v07();
    virtual void v08();  virtual void v09();  virtual void v10();  virtual void v11();
    virtual void v12();  virtual void v13();  virtual void v14();  virtual void v15();
    virtual void v16();  virtual void v17();  virtual void v18();  virtual void v19();
    virtual void v20();  virtual void v21();
    virtual void QueryAnimation(int* pGuid, int unusedA, int* pDuration, int unusedB); // +0x58
};

struct Vector3 {
    float x;                                                 // +0x00
    float y;                                                 // +0x04
    float z;                                                 // +0x08
};

struct ContextInfo {
    char mPad00[0x5c];
    int  mField5c;                                           // +0x5c

    Vector3* GetFallbackPoint();                             // 0x00c423c0
};

// spatial subobject embedded at +0xc0 of the creature
struct Spatial {
    virtual void u00(); virtual void u01(); virtual void u02(); virtual void u03();
    virtual void u04(); virtual void u05(); virtual void u06(); virtual void u07();
    virtual void u08(); virtual void u09(); virtual void u10();
    virtual Vector3* GetPosition();                          // vtable +0x2c
    virtual void u12(); virtual void u13(); virtual void u14(); virtual void u15();
    virtual void u16(); virtual void u17(); virtual void u18(); virtual void u19();
    virtual void u20(); virtual void u21(); virtual void u22(); virtual void u23();
    virtual void u24(); virtual void u25(); virtual void u26(); virtual void u27();
    virtual void u28(); virtual void u29(); virtual void u30(); virtual void u31();
    virtual void u32(); virtual void u33(); virtual void u34(); virtual void u35();
    virtual void u36(); virtual void u37(); virtual void u38(); virtual void u39();
    virtual void u40(); virtual void u41(); virtual void u42(); virtual void u43();
    virtual void u44(); virtual void u45(); virtual void u46(); virtual void u47();
    virtual void u48(); virtual void u49(); virtual void u50(); virtual void u51();
    virtual void u52(); virtual void u53(); virtual void u54(); virtual void u55();
    virtual void u56(); virtual void u57(); virtual void u58(); virtual void u59();
    virtual void u60(); virtual void u61();
    virtual bool CanStep();                                  // vtable +0xf8

    ContextInfo* GetContext();                               // 0x00c41ec0
    Vector3* GetApproachPoint();                             // 0x00c421f0
    bool IsNearGoal();                                       // 0x00c42e20
};

// same vtable prefix as Spatial, for spatial subobjects that live at other offsets
struct LocoRef {
    virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
    virtual void w04(); virtual void w05(); virtual void w06(); virtual void w07();
    virtual void w08(); virtual void w09(); virtual void w10();
    virtual Vector3* GetPosition();                          // vtable +0x2c
};

// tuning block reached through Creature::Get()
struct CreatureTuning {
    char mPad000[0x108];
    float mField108;                                         // +0x108

    Vector3* GetPosition();                                  // 0x00c6acc0
};

struct PlayHandle {
    char  mPad000[8];
    float mSpeed;                                            // +0x08
    char  mPad00c[0x2c - 0x0c];
    int   mSoundId;                                          // +0x2c
};

struct BehaviourNode;
struct Creature;

struct FindStuffState {
    char mPad000[0x1a4];
    Vector3 mDestination;                                    // +0x1a4

    bool IsFinished();                                       // 0x00a75010
    Creature* CurrentId();                                   // 0x00bc9b10
};

struct AgentManager {
    char mPad000[8];
    struct OrderQueue {
        char mPad[4];
        PlayHandle* Play(int animId, int flags);             // 0x00bc96a0
        void PlayEx(int animId, int flags, float speed, int soundId); // 0x00bc97f0
        void ClearAll(int reason, int flags);                // 0x00bc98f0
    } mOrders;                                               // +0x08
    char mPad00c[0x600 - 0x0c];
    FindStuffState* mpFindStuff;                             // +0x600

    bool IsSourceEmpty();                                    // 0x00bca2a0
    bool QueueOrder(Creature* pSelf, int* pState, int a);     // 0x00bcb510
};

// ---------------------------------------------------------------------------------------------
// creature, only the members this tick touches
// ---------------------------------------------------------------------------------------------
struct Creature {
    char mPad000[0xc0];
    Spatial mSpatial;                                        // +0x0c0
    char mPad0c4[0x137 - 0xc4];
    char mState137;                                          // +0x137
    char mPad138[0xb4c - 0x138];
    AgentManager* mpAgentManager;                            // +0x0b4c
    char mPadB50[0xb54 - 0xb50];
    AnimProvider* mpAnimProvider;                            // +0x0b54
    char mPadB58[0xb5e - 0xb58];
    char mFieldB5e;                                          // +0x0b5e
    char mPadB5f[0xe3c - 0xb5f];
    int  mFieldE3c;                                          // +0x0e3c

    void UpdateLocomotion(int reason);                       // 0x00c14750
    bool CheckState();                                       // 0x00c0c130
    bool IsAnimationFinished(int);                           // 0x00c123f0
    bool HasAnimationEnded();                                // 0x00c0e420
    int  GetCurrentAnimationGUID();                          // 0x00c0e040
    void PlayAnimation(int guid, int loop, int blend);       // 0x00c12190

    void SetStealthed(int a, int b);                         // 0x00c1aed0
    CreatureTuning* Get();                                   // 0x00c04590
    int  SpeedClass();                                       // 0x00c0b750
    bool AcceptTarget(int handle);                           // 0x00c0b7c0
    void MoveToPointAtSpeed(int speedClass, const void* pPoint, float a, float b); // 0x00c1c1d0
    void InterruptAnimation(int animId, int a, int b);       // 0x00c12310
    void PlayGesture(int animId, float a, float b);          // 0x00c122c0
};

// timer pair: elapsed time at +0, current clip duration at +4
struct IdleTimer {
    float mElapsed;                                          // +0x00
    float mDuration;                                         // +0x04
};

// ---------------------------------------------------------------------------------------------
// @ 0x00d83230
bool AvatarIdleTick(Creature* self, int arg2, int arg3, int arg4, int arg5, IdleTimer* pTimer,
                    int arg7, float deltaTime)
{
    pTimer->mElapsed += deltaTime;

    if (self->mState137 == 0) {
        self->UpdateLocomotion(0);
        return true;
    }

    bool hasIdleAnim = false;
    AnimProvider* pProvider = self->mpAnimProvider;
    if (pProvider != 0) {
        int guid;
        int duration;
        pProvider->QueryAnimation(&guid, 0, &duration, 0);
        if (guid == kAvatarIdleGuid)
            hasIdleAnim = duration > 0;
    }

    if (self->mSpatial.GetContext()->mField5c != 0
            || self->CheckState()
            || gAvatarIdleSuppressed != 0
            || hasIdleAnim) {
        pTimer->mElapsed = 0.0f;
        if (self->GetCurrentAnimationGUID() == kAvatarIdleGuid)
            self->UpdateLocomotion(gAvatarIdleSuppressed);
        return true;
    }

    if (self->GetCurrentAnimationGUID() == kAvatarIdleGuid) {
        pTimer->mElapsed = 0.0f;
        return true;
    }

    if (pTimer->mElapsed > pTimer->mDuration) {
        if (self->mFieldE3c != -1)
            return true;

        if (!self->HasAnimationEnded() && !self->IsAnimationFinished(0))
            return true;

        pTimer->mElapsed = 0.0f;
        unsigned int roll = gRandom.RandomUint32Uniform(10);
        pTimer->mDuration = (float)(int)(roll + 5);
        self->PlayAnimation(kAvatarIdleGuid, 1, -1);
        return true;
    }
    return true;
}

// =============================================================================================
// 00d83370: SP::FIND_STUFF_Tick -- drive the "find stuff" behaviour toward its destination
// =============================================================================================
extern const float gkFoodSearchMinRadius;                    // 0x0147c034
extern const float gkFoodSearchDefaultRadius;                // 0x01582e8c
extern const float gkOne;                                    // 0x01485720
extern const float gkSearchTimeout;                          // 0x014853bc

struct PlanetModelResult {
    const void* GetPoint();                                  // 0x00b81630
};

extern "C" PlanetModelResult* __stdcall PlanetModel(Vector3* pOut, const Vector3* pDest); // 0x00b3d350
extern "C" Creature* __cdecl WatchMemoryBlock(const void* pHandle);          // 0x00d999d0
extern "C" void* __cdecl Find(const void* pHandle, int guid);                // 0x00d998d0
extern "C" bool __cdecl FindForageDestination(Creature* self, Vector3* pOut); // 0x00d7cfb0

// behaviour node the search results hang off of
struct BehaviourNode {
    char mPad000[0x34];
    LocoRef mSpatial34;                                      // +0x34
    char mPad038[0x120 - 0x38];
    LocoRef mSpatial120;                                     // +0x120
    char mPad124[0x210 - 0x124];
    int* mpHandles;                                          // +0x210
    int* mpHandlesEnd;                                       // +0x214

    Vector3* GetPoint(Vector3* pOut, int n);                 // 0x00c91190
};

struct AltNode {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08(); virtual void a09(); virtual void a10();
    virtual bool IsBlocked();                                // vtable +0x2c
    char mPad004[0x34 - 0x04];
    LocoRef mSpatial34;                                      // +0x34
};

// @ 0x00d83370
bool FindStuffTick(Creature* self, int arg2, int arg3, unsigned int flags, int arg5,
                   int* pState, int arg7, float deltaTime)
{
    FindStuffState* pFind = self->mpAgentManager->mpFindStuff;
    if (pFind == 0 || pFind->IsFinished())
        return false;

    bool skipDistanceCheck = (flags & 0x10000) != 0;
    if (skipDistanceCheck)
        self->SetStealthed(1, 1);

    Creature* pCurrent = pFind->CurrentId();
    if (pCurrent != self) {
        Vector3* pSelfPos = self->mSpatial.GetPosition();
        Vector3* pDestination = &pFind->mDestination;

        PlayHandle* pHandle = pCurrent->mpAgentManager->mOrders.Play(0x80000000, 0);
        if (pHandle != 0) {
            Creature* pWatched = WatchMemoryBlock(pHandle);
            if (pWatched != 0 && pWatched->mFieldB5e == 0)
                self->mpAgentManager->mOrders.PlayEx(0x80000000, 0, pHandle->mSpeed,
                                                     pHandle->mSoundId);
        }

        ContextInfo* pInfo = self->mSpatial.GetContext();
        float radius = (float)pState[2];
        Vector3* pFrom = pSelfPos;
        if (pInfo->mField5c != 0)
            pFrom = pInfo->GetFallbackPoint();

        float dx = pFrom->x - pDestination->x;
        float dy = pFrom->y - pDestination->y;
        float dz = pFrom->z - pDestination->z;
        float distSq = dx * dx + dy * dy + dz * dz;
        if (distSq <= radius * radius) {
            if (self->mSpatial.IsNearGoal() && *pState == 2) {
                self->PlayGesture(0x715be665, 0.5f, 0.0f);
                *pState = 3;
            }
            return true;
        }

        int speedClass = pCurrent->SpeedClass();
        if (speedClass == 0)
            speedClass = 2;
        Vector3 target;
        PlanetModelResult* pModel = PlanetModel(&target, pDestination);
        const void* pPoint = pModel->GetPoint();
        self->MoveToPointAtSpeed(speedClass, pPoint, radius, radius);
        if (!self->mSpatial.CanStep())
            self->UpdateLocomotion(0);
        *pState = 2;
        return true;
    }

    if (*pState > 1)
        *pState = 0;

    if (!self->mpAgentManager->IsSourceEmpty()) {
        if (self->mpAgentManager->QueueOrder(self, pState, 0))
            return true;
    }

    pState[1] -= deltaTime;
    if (*pState != 0)
        return true;

    Vector3* pSelfPos = self->mSpatial.GetPosition();
    float radius = (self->Get()->mField108 > gkFoodSearchMinRadius)
                       ? self->Get()->mField108 : gkFoodSearchDefaultRadius;
    float radiusSq = radius * radius;

    bool nearGoal = self->mSpatial.IsNearGoal();
    if (!nearGoal && (flags & 0x10) != 0)
        self->SetStealthed(1, 0);

    Vector3 vec;
    bool haveVec = false;

    PlayHandle* pIdle = self->mpAgentManager->mOrders.Play(0x80000000, 0);
    if (pIdle != 0) {
        Creature* pWatch = WatchMemoryBlock(pIdle);
        if (pWatch != 0 && pWatch->mFieldB5e == 0) {
            bool closeEnough = true;
            if (!skipDistanceCheck) {
                Vector3* pPos = pWatch->mSpatial.GetPosition();
                float dx = pPos->x - pSelfPos->x;
                float dy = pPos->y - pSelfPos->y;
                float dz = pPos->z - pSelfPos->z;
                closeEnough = dx * dx + dy * dy + dz * dz < radiusSq;
            }
            if (closeEnough) {
                vec = *pWatch->mSpatial.GetPosition();
                haveVec = true;
                if (pWatch->CheckState())
                    vec = *self->Get()->GetPosition();
            }
        }
    }

    PlayHandle* pObj = self->mpAgentManager->mOrders.Play(0, 0x100);
    if (pObj != 0) {
        BehaviourNode* pNode = (BehaviourNode*)Find(pObj, 0x4f396a66);
        if (pNode != 0) {
            vec = *pNode->mSpatial120.GetPosition();
            bool accepted = false;
            for (int* pIt = pNode->mpHandles; pIt != pNode->mpHandlesEnd; ++pIt) {
                if (self->AcceptTarget(*pIt)) {
                    vec = *((BehaviourNode*)*pIt)->mSpatial34.GetPosition();
                    accepted = true;
                    break;
                }
            }
            if (!accepted) {
                Vector3 scratch;
                vec = *pNode->GetPoint(&scratch, 1);
            }
        } else {
            AltNode* pAlt = (AltNode*)Find(pObj, 0x4ffcdeda);
            if (pAlt == 0 || pAlt->IsBlocked()) {
                self->mpAgentManager->mOrders.ClearAll(0, 0x100);
                return false;
            }
            vec = *pAlt->mSpatial34.GetPosition();
        }
        haveVec = true;
    }

    if (nearGoal) {
        pState[1] = gkSearchTimeout;
        if (!haveVec) {
            bool found = FindForageDestination(self, &vec);
            haveVec = found;
            Vector3* pPos = self->mSpatial.GetPosition();
            float dx = vec.x - pPos->x;
            float dy = vec.y - pPos->y;
            float dz = vec.z - pPos->z;
            if (dx * dx + dy * dy + dz * dz < gkOne || !found)
                vec = *self->Get()->GetPosition();
        }
    } else if (!haveVec) {
        return true;
    }

    pFind->mDestination = vec;

    if (nearGoal) {
        Vector3* pPos = self->mSpatial.GetPosition();
        float dx = vec.x - pPos->x;
        float dy = vec.y - pPos->y;
        float dz = vec.z - pPos->z;
        if (!(dx * dx + dy * dy + dz * dz > gkOne))
            return true;
    } else {
        float limit = (float)pState[2];
        Vector3* pApproach = self->mSpatial.GetApproachPoint();
        float dx = pApproach->x - vec.x;
        float dy = pApproach->y - vec.y;
        float dz = pApproach->z - vec.z;
        if (dx * dx + dy * dy + dz * dz <= limit * limit)
            return true;
    }

    self->MoveToPointAtSpeed(2, &vec, 1.0f, 2.0f);
    if (!self->mSpatial.CanStep())
        self->InterruptAnimation(0x2481de5, -1, 0);
    return true;
}
