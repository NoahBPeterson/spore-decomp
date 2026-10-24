// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00aee680.
//
// UFO locomotion avoidance bitmasks, the behavior resource lookups and the
// debug behavior subsystem (tick, ownership, blending and velocity helpers).

typedef unsigned int size_t;
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef int intptr_t;
#define nullptr 0

struct Vec4 {
    float mX;
    float mY;
    float mZ;
    float mW;
};

class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};

class cGameNounManager {
public:
    void* GetPlayerCivilization();
    void* GetGameDataVector(void* pFilterA, void* pFilterB, void* pFilterC,
                            void* pFilterD, void* pOutput);
};

class cCity {
public:
    void* GetCivilization();
};

class cILocomotion : public IRefCounted {
public:
    uint8_t mPad14[0x04];                       // 0x14
};

class cUFOLocomotion : public cILocomotion {
public:
    uint32_t* CalculateAvoidanceDestination(uint32_t* pOut, void* pTarget,
                                            void* pUnused, int nFilter);
    uint8_t mPad18[0x08];                       // 0x18
};

class cOwnerRelease {
public:
    virtual void Release();
    void ReleaseOwnerRef(uint8_t* pFlag, void* pOwnerRef);
};

class cTimerThing {
public:
    void BindAnimation(void* pTarget);
    void Snap(const Vec4* pTransform);
};

class cVec4Snap {
public:
    void Snap(int nUnused);
};

class cDebugBehavior {
public:
    void* GetOwner();
    void ReleaseOwner();
    void UpdateTransform();
    void SetEnabled(uint8_t bEnabled, float fRate);
    void Update(float fDelta);
    void SetTransform(const Vec4* pTransform, bool bSnap);
    void AddVelocity(const Vec4* pVelocity);

    uint8_t mbBlendActive;                      // 0x00
    uint8_t mbBlendToEnabled;                   // 0x01
    uint8_t mPad02[0x02];                       // 0x02
    float mfBlend;                              // 0x04
    uint8_t mPad08[0x08];                       // 0x08
    Vec4 mCurrent;                              // 0x10
    uint8_t mPad20[0x20];                       // 0x20
    Vec4 mTransform;                            // 0x40
    void* mpOwner;                              // 0x50
    void* mpOwnerRef;                           // 0x54
    uint8_t mPad58[0x18];                       // 0x58
    uint8_t mPad70[0x04];                       // 0x70
    uint8_t mbEnabled;                          // 0x74
    uint8_t mPad75[0x03];                       // 0x75
    float mfRate;                               // 0x78
    uint8_t mPad7c[0x14];                       // 0x7c
    Vec4 mTarget;                               // 0x90
    Vec4 mVelocity;                             // 0xa0
    float mfScale;                              // 0xb0
};

class cBehaviorRecord {
public:
    uint8_t mPad00[0x10];                       // 0x00
    uint8_t mbFlag10;                           // 0x10
    uint8_t mbFlag11;                           // 0x11
    uint8_t mbFlag12;                           // 0x12
    uint8_t mbFlag13;                           // 0x13
    uint8_t mbFlag14;                           // 0x14
    uint8_t mPad15[0x03];                       // 0x15
    uint32_t mnId18;                            // 0x18
    uint32_t mnId1c;                            // 0x1c
    uint32_t mnId20;                            // 0x20
    uint32_t mnId24;                            // 0x24
};

class cBehaviorTable {
public:
    void* Find(void* pKey);
    void* FindSubRecord(void* pKey);
    uint32_t* CollectLongVectors(void* pKey);
    void CollectFilters(void* pKey, uint32_t* pMask, uint32_t* pList);

    uint8_t mPad00[0x10];                       // 0x00
    uint8_t mbFlag10;                           // 0x10
    uint8_t mbFlag11;                           // 0x11
    uint8_t mbFlag12;                           // 0x12
    uint8_t mbFlag13;                           // 0x13
    uint8_t mbFlag14;                           // 0x14
    uint8_t mPad15[0x03];                       // 0x15
    uint32_t mnId18;                            // 0x18
    uint32_t mnId1c;                            // 0x1c
    uint32_t mnId20;                            // 0x20
    uint32_t mnId24;                            // 0x24
    uint32_t mnId28;                            // 0x28
    uint8_t mPad2c[0x10];                       // 0x2c
    uint32_t mnEntryBegin3c;                    // 0x3c
    uint32_t mnEntryEnd40;                      // 0x40
};

class cBehaviorRecordSlot {
public:
    uint32_t mFilter[5];                        // 0x00
    uint32_t mMask[5];                          // 0x14
    uint8_t mPad28[0x20];                       // 0x28
};

class cBehaviorRange {
public:
    void* mpBegin;                              // 0x00
    void* mpEnd;                                // 0x04
};

class cBehaviorSubRecord {
public:
    uint8_t mPad00[0x50];                       // 0x00
    uint32_t mnValue50;                         // 0x50
    uint32_t mnValue54;                         // 0x54
    uint32_t mnValue58;                         // 0x58
    uint32_t mnValue5c;                         // 0x5c
    uint8_t mPad60[0x04];                       // 0x60
    uint8_t mbFlag64;                           // 0x64
    uint8_t mPad65[0x5f];                       // 0x65
};

class cGameDataVector {
public:
    uint8_t mPad00[0x04];                       // 0x00
    void** mpBegin;                             // 0x04
    void** mpEnd;                               // 0x08
};

class cPropertyList {
public:
    virtual void v00();
    virtual void Release();
    virtual void v08();
    virtual void v0c();
};

class cDebugOwner {
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
    virtual void SetPosition(const Vec4* pPosition);
};

void* operator_new(size_t nSize);
void operator_delete__(void* pMemory);
void* NounManager();
void* ResourceManagerGet();
void* LookupResource(void* pKey);
void* LookupResourceRecord(void* pKey);
int32_t GetCivilizationDistance(void* pA, void* pB, int nFlag);
uint32_t GetCivilizationLevel(void* pCivilization);
void* GetPlayerAvatarNouns();
int32_t GetContinentDistance(int a, void* pCity, int b);
int32_t GetDistanceToCity(void* pTarget, int nFilter);
bool IsCivilizationNomadic(void* pCivilization);
void NotifyAvoidanceUpdated(int a, void* pRecord);
void ApplyBehaviorRecordFlags(void* pRecord, void* pKey);
void CollectBehaviorTimerRanges(void* pAnimContext, void* pFilterA, void* pFilterB,
                                 void* pFilterC, void* pFilterD);
bool MatchesBehaviorFilter(void* pRecord, void* pKey);
void GatherBehaviorValues(void* pOut, void* pKey, int a, int b, int c);
void GatherBehaviorVectors(void* pOut, void* pKey, void* pExtra, int a, int b);
void DebugBehaviorInit();
void DebugBehaviorShutdown();
void DebugBehaviorStopTimers(void* pTimers);
void DebugBehaviorReleaseOwnerRef(void* pOwnerRef);
void DebugBehaviorDropTimers();
void DebugBehaviorApplyFetch(void* pOwnerRef);
void DebugBehaviorResetState(void* pAnimation);
void DebugBehaviorBindAnimation(void* pAnimation);
void DebugBehaviorFetchAnimation(void* pOwnerRef, int a);
void DebugBehaviorClearTransform(void* pTransform);
void DebugBehaviorSnapTransform(const Vec4* pTransform);
void DebugBehaviorSetOwnerScale(void* pOwnerRef);
void RandomUint32Uniform(void* pRandom, uint32_t nRange);

extern void* gBehaviorResourceBlock;
extern void* gRandomState;
extern uint32_t gAvoidanceFilterTable[0x40];

// ---------------------------------------------------------------------------
// 0x00aee680  SP::FilterAvoidanceRecords
// ---------------------------------------------------------------------------
// @ 0x00aee680
uint32_t FilterAvoidanceRecords(cBehaviorRange* pRange, const uint32_t* pMask)
{
    cBehaviorRecordSlot* pSlot = (cBehaviorRecordSlot*)pRange->mpBegin;
    while (pSlot != (cBehaviorRecordSlot*)pRange->mpEnd) {
        uint32_t localMask[5];
        localMask[0] = pMask[0] & pSlot->mMask[0];
        localMask[1] = pMask[1] & pSlot->mMask[1];
        localMask[2] = pMask[2] & pSlot->mMask[2];
        localMask[3] = pMask[3] & pSlot->mMask[3];
        localMask[4] = pMask[4] & pSlot->mMask[4];

        uint32_t i = 0;
        bool bHasMask = false;
        while (i < 5) {
            if (localMask[i] != 0) {
                bHasMask = true;
                break;
            }
            ++i;
        }

        if (!bHasMask) {
            uint32_t localFilter[5];
            localFilter[0] = pSlot->mFilter[0] ^ (pMask[0] & pSlot->mFilter[0]);
            localFilter[1] = pSlot->mFilter[1] ^ (pMask[1] & pSlot->mFilter[1]);
            localFilter[2] = pSlot->mFilter[2] ^ (pMask[2] & pSlot->mFilter[2]);
            localFilter[3] = pSlot->mFilter[3] ^ (pMask[3] & pSlot->mFilter[3]);
            localFilter[4] = pSlot->mFilter[4] ^ (pMask[4] & pSlot->mFilter[4]);

            i = 0;
            bool bHasFilter = false;
            while (i < 5) {
                if (localFilter[i] != 0) {
                    bHasFilter = true;
                    break;
                }
                ++i;
            }
            if (!bHasFilter)
                NotifyAvoidanceUpdated(0, pSlot);
        }
        pSlot = (cBehaviorRecordSlot*)((uint8_t*)pSlot + 0x48);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00aee830  SP::cUFOLocomotion::CalculateAvoidanceDestination
// ---------------------------------------------------------------------------
// @ 0x00aee830
uint32_t* cUFOLocomotion::CalculateAvoidanceDestination(uint32_t* pOut, void* pTarget,
                                                        void* pUnused, int nFilter)
{
    pOut[0] = 0;
    pOut[1] = 0;
    pOut[2] = 0;
    pOut[3] = 0;
    pOut[4] = 0;

    cGameNounManager* pNouns = (cGameNounManager*)NounManager();
    uint32_t* pPlayerCiv = (uint32_t*)pNouns->GetPlayerCivilization();

    if (pTarget != nullptr && pPlayerCiv != nullptr && pTarget != pPlayerCiv) {
        void* pCivA = pPlayerCiv;
        void* pCivB = pTarget;
        ((IRefCounted*)pCivA)->v10();
        ((IRefCounted*)pCivB)->v10();

        NounManager();
        void* pNounsB = GetPlayerAvatarNouns();
        int nLevel = GetCivilizationLevel(pTarget);
        if (nLevel < 2)
            pOut[0] |= 0x40;

        int nRelation = GetCivilizationDistance(pCivB, pCivA, 1);
        switch (nRelation) {
        case 0:
            pOut[1] |= 0x80000000;
            pOut[2] |= 0x380;
            break;
        case 1:
            pOut[2] |= 0x391;
            break;
        case 2:
            pOut[2] |= 0x332;
            break;
        case 3:
            pOut[2] |= 0x274;
            break;
        case 4:
            pOut[2] |= 0x78;
            break;
        default:
            break;
        }
        (void)pNounsB;
    }

    float fDistance = (float)pPlayerCiv[0x26];
    if (fDistance < 4000.0f)
        pOut[2] |= 0x400;
    if (fDistance < 2000.0f)
        pOut[2] |= 0x800;
    if (fDistance < 1000.0f)
        pOut[2] |= 0x1000;
    if (31999.998f < fDistance)
        pOut[2] |= 0x2000;
    if (23999.998f < fDistance)
        pOut[2] |= 0x4000;
    if (15999.999f < fDistance)
        pOut[2] |= 0x8000;
    if (7999.999f < fDistance)
        pOut[2] |= 0x10000;
    if (3999.999f < fDistance)
        pOut[2] |= 0x20000;

    if (pTarget == nullptr)
        return pOut;

    void* pCivilization = NounManager();
    int nType = GetContinentDistance(0, pCivilization, 1);
    if (nType == 0)
        pOut[2] |= 0x200000;
    else if (nType == 1)
        pOut[2] |= 0x400000;
    else if (nType == 2)
        pOut[2] |= 0x800000;

    cGameDataVector* pCities = (cGameDataVector*)GetPlayerAvatarNouns();
    uint32_t nCityCount = (uint32_t)(pCities->mpEnd - pCities->mpBegin);
    if (nCityCount < 4) {
        pOut[2] |= 0x1000000;
        if (nCityCount < 7) {
            if (1 < nCityCount)
                pOut[2] |= 0x8000000;
            if (9 < nCityCount)
                pOut[2] |= 0x10000000;
            goto checkFlags;
        }
    } else if (nCityCount < 7) {
        pOut[2] |= 0x2000000;
        if (1 < nCityCount)
            pOut[2] |= 0x8000000;
        if (9 < nCityCount)
            pOut[2] |= 0x10000000;
        goto checkFlags;
    }
    if (nCityCount < 10)
        pOut[2] |= 0x4000000;
    if (1 < nCityCount)
        pOut[2] |= 0x8000000;
    if (9 < nCityCount)
        pOut[2] |= 0x10000000;

checkFlags:
    if (((uint32_t*)pTarget)[0xab] != 0)
        pOut[2] |= 0x20000000;
    if (((uint32_t*)pTarget)[0xb4] != 0)
        pOut[2] |= 0x40000000;
    if (((uint32_t*)pTarget)[0xbe] != 0)
        pOut[2] |= 0x80000000;
    if (((uint8_t*)pTarget)[200] != 0)
        pOut[3] |= 1;
    if (((uint8_t*)pTarget)[0xd2] != 0)
        pOut[3] |= 2;
    if (((uint8_t*)pTarget)[0xdc] != 0)
        pOut[3] |= 4;
    if (((uint8_t*)pTarget)[0xe6] != 0)
        pOut[3] |= 8;
    if (((uint8_t*)pTarget)[0xf0] != 0)
        pOut[3] |= 0x10;

    cGameNounManager* pNouns2 = (cGameNounManager*)NounManager();
    cGameDataVector* pData = (cGameDataVector*)pNouns2->GetGameDataVector(
        (void*)&gAvoidanceFilterTable[0], (void*)&gAvoidanceFilterTable[1],
        (void*)&gAvoidanceFilterTable[2], (void*)&gAvoidanceFilterTable[3],
        (void*)&gBehaviorResourceBlock);

    int nCityDataCount = (int)(pData->mpEnd - pData->mpBegin);
    int nOtherCivs = 0;
    if (0 < nCityDataCount) {
        for (int i = 0; i < nCityDataCount; ++i) {
            cCity* pCity = (cCity*)pData->mpBegin[i];
            void* pCiv1 = pCity->GetCivilization();
            if (pCiv1 != pTarget) {
                void* pCiv2 = pCity->GetCivilization();
                if (pCiv2 != pPlayerCiv)
                    ++nOtherCivs;
            }
        }
    }

    uint32_t nBit = 0x65;
    do {
        int nIndex = (int)(nBit - 0x65);
        if (nIndex < nOtherCivs && nBit < 0x9a)
            pOut[nBit >> 5] |= 1 << (nBit & 0x1f);
        ++nBit;
    } while ((int)(nBit - 100) < 10);

    if (nFilter != 0) {
        int nCityDistance = GetDistanceToCity((void*)pPlayerCiv, nFilter);
        if ((float)nCityDistance <= fDistance)
            pOut[3] |= 0x8000;
    }

    if (IsCivilizationNomadic((void*)pPlayerCiv))
        pOut[4] |= 0x80000;
    return pOut;
}

// ---------------------------------------------------------------------------
// 0x00aeebe0  SP::FilterBehaviorResource
// ---------------------------------------------------------------------------
// @ 0x00aeebe0
void FilterBehaviorResource(void* pKey)
{
    cPropertyList* pRecord = (cPropertyList*)LookupResource(pKey);
    if (pRecord != nullptr)
        ApplyBehaviorRecordFlags((uint8_t*)pRecord + 0x10, pKey);
    if (pRecord != nullptr)
        pRecord->Release();
}

// ---------------------------------------------------------------------------
// 0x00aeec90  SP::GetBehaviorVectorFromResource
// ---------------------------------------------------------------------------
// @ 0x00aeec90
uint32_t* GetBehaviorVectorFromResource(uint32_t* pOut, void* pKey, int a, int b, int c)
{
    cBehaviorTable* pTable = (cBehaviorTable*)LookupResourceRecord(pKey);
    if (pTable != nullptr) {
        GatherBehaviorValues((uint8_t*)pTable + 0x3c, pKey, a, b, c);
        GatherBehaviorVectors(&pTable->mnId24, pKey, (void*)b, a, c);
        pOut[0] = pTable->mnId18;
        pOut[1] = pTable->mnId1c;
        pOut[2] = pTable->mnId20;
        pOut[3] = pTable->mnId24;
        ((cPropertyList*)pTable)->Release();
        return pOut;
    }
    pOut[1] = 0;
    pOut[2] = 0;
    pOut[3] = 0;
    return pOut;
}

// ---------------------------------------------------------------------------
// 0x00aeeda0  SP::GetBehaviorUnlockFlag
// ---------------------------------------------------------------------------
// @ 0x00aeeda0
uint8_t GetBehaviorUnlockFlag(void* pKey)
{
    cBehaviorTable* pTable = (cBehaviorTable*)LookupResourceRecord(pKey);
    if (pTable == nullptr)
        return 0;
    uint8_t nFlag = pTable->mbFlag14;
    ((cPropertyList*)pTable)->Release();
    return nFlag;
}

// ---------------------------------------------------------------------------
// 0x00aeee50  SP::GetBehaviorFlags
// ---------------------------------------------------------------------------
// @ 0x00aeee50
void GetBehaviorFlags(uint8_t* pFlags, void* pKey)
{
    cBehaviorTable* pTable = (cBehaviorTable*)LookupResourceRecord(pKey);
    if (pTable != nullptr) {
        pFlags[0] = pTable->mbFlag13;
        pFlags[1] = pTable->mbFlag10;
        pFlags[2] = pTable->mbFlag11;
        pFlags[3] = pTable->mbFlag12;
        ((cPropertyList*)pTable)->Release();
    }
}

// ---------------------------------------------------------------------------
// 0x00aeef00  SP::CountBehaviorSubRecords
// ---------------------------------------------------------------------------
// @ 0x00aeef00
int CountBehaviorSubRecords(void* pKey)
{
    int nCount = 0;
    cBehaviorTable* pTable = (cBehaviorTable*)LookupResourceRecord(pKey);
    if (pTable != nullptr) {
        cBehaviorSubRecord* pEntry = (cBehaviorSubRecord*)pTable->mnEntryBegin3c;
        if (pEntry != (cBehaviorSubRecord*)pTable->mnEntryEnd40) {
            do {
                if (MatchesBehaviorFilter(pEntry, pKey))
                    ++nCount;
                pEntry = (cBehaviorSubRecord*)((uint8_t*)pEntry + 0xc4);
            } while (pEntry != (cBehaviorSubRecord*)pTable->mnEntryEnd40);
        }
        ((cPropertyList*)pTable)->Release();
    }
    return nCount;
}

// ---------------------------------------------------------------------------
// 0x00aeefc0  SP::GetBehaviorSubRecordValues
// ---------------------------------------------------------------------------
// @ 0x00aeefc0
uint32_t* GetBehaviorSubRecordValues(uint32_t* pOut, void* pKey, int nWanted, int a)
{
    int nIndex = 0;
    cBehaviorTable* pTable = (cBehaviorTable*)LookupResourceRecord(pKey);
    if (pTable != nullptr) {
        cBehaviorSubRecord* pEntry = (cBehaviorSubRecord*)pTable->mnEntryBegin3c;
        if (pEntry != (cBehaviorSubRecord*)pTable->mnEntryEnd40) {
            do {
                if (MatchesBehaviorFilter(pEntry, pKey)) {
                    if (nIndex == nWanted) {
                        if (a != 0)
                            GatherBehaviorValues((uint8_t*)pEntry + 0x60, pKey, 0, 0, a);
                        pOut[0] = pEntry->mnValue50;
                        pOut[1] = pEntry->mnValue54;
                        pOut[2] = pEntry->mnValue58;
                        pOut[3] = pEntry->mnValue5c;
                        ((cPropertyList*)pTable)->Release();
                        return pOut;
                    }
                    ++nIndex;
                }
                pEntry = (cBehaviorSubRecord*)((uint8_t*)pEntry + 0xc4);
            } while (pEntry != (cBehaviorSubRecord*)pTable->mnEntryEnd40);
        }
        ((cPropertyList*)pTable)->Release();
    }
    pOut[1] = 0;
    pOut[2] = 0;
    pOut[3] = 0;
    return pOut;
}

// ---------------------------------------------------------------------------
// 0x00aef0e0  SP::DEBUG_BEHAVIOR_Tick
// ---------------------------------------------------------------------------
// @ 0x00aef0e0
void DEBUG_BEHAVIOR_Tick(void* pBehavior, uint32_t nAction, uint32_t* pOutA, uint32_t* pOutB)
{
    switch (nAction) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
    case 8:
    case 9:
    case 0xb:
    case 0xe:
    case 0x12:
    case 10:
    case 0xf:
    case 0x11:
    case 0xc:
    case 0xd:
    case 0x10:
    default:
        break;
    }

    *pOutA = 0;
    *pOutB = 0;

    cBehaviorTable* pTable = (cBehaviorTable*)LookupResource((void*)&gRandomState);
    if (pTable != nullptr) {
        uint32_t nMaskCount = (pTable->mnId28 - pTable->mnId24) >> 2;
        if (0 < (int)nMaskCount) {
            uint32_t nIndex = 0;
            RandomUint32Uniform(&gRandomState, nMaskCount);
            *pOutA = *(uint32_t*)(pTable->mnId24 + nIndex * 4);
        }
        uint32_t nFilterCount = (pTable->mnId1c - pTable->mnId18) >> 2;
        if (0 < (int)nFilterCount) {
            uint32_t nIndex = 0;
            RandomUint32Uniform(&gRandomState, nFilterCount);
            *pOutB = *(uint32_t*)(pTable->mnId18 + nIndex * 4);
        }
        ((cPropertyList*)pTable)->Release();
    }
    (void)pBehavior;
}

// ---------------------------------------------------------------------------
// 0x00aef2c0  SP::DEBUG_BEHAVIOR_Init
// ---------------------------------------------------------------------------
// @ 0x00aef2c0
void DEBUG_BEHAVIOR_Init()
{
    DebugBehaviorInit();
}

// ---------------------------------------------------------------------------
// 0x00aef2d0  SP::DEBUG_BEHAVIOR_Shutdown
// ---------------------------------------------------------------------------
// @ 0x00aef2d0
void DEBUG_BEHAVIOR_Shutdown()
{
    DebugBehaviorShutdown();
}

// ---------------------------------------------------------------------------
// 0x00aef2e0  SP::cDebugBehavior::GetOwner
// ---------------------------------------------------------------------------
// @ 0x00aef2e0
void* cDebugBehavior::GetOwner()
{
    int nPresent = *(int*)((uint8_t*)mpOwnerRef + 8);
    return (void*)((intptr_t)mpOwnerRef & (nPresent != 0 ? -1 : 0));
}

// ---------------------------------------------------------------------------
// 0x00aef2f0  SP::cDebugBehavior::ReleaseOwner
// ---------------------------------------------------------------------------
// @ 0x00aef2f0
void cDebugBehavior::ReleaseOwner()
{
    if (*(int*)((uint8_t*)mpOwnerRef + 8) != 0) {
        DebugBehaviorStopTimers((uint8_t*)this + 0x58);
        uint8_t bFlag = 0;
        ((cOwnerRelease*)mpOwner)->ReleaseOwnerRef(&bFlag, mpOwnerRef);
        ((cPropertyList*)mpOwnerRef)->Release();
    }
    mpOwnerRef = nullptr;
}

// ---------------------------------------------------------------------------
// 0x00aef330  SP::cDebugBehavior::UpdateTransform
// ---------------------------------------------------------------------------
// @ 0x00aef330
void cDebugBehavior::UpdateTransform()
{
    if (*(int*)((uint8_t*)mpOwnerRef + 8) != 0) {
        DebugBehaviorBindAnimation((uint8_t*)this + 0x90);
        ((cTimerThing*)mpOwnerRef)->BindAnimation((uint8_t*)this + 0x40);
        void* pOwnerRef = mpOwnerRef;
        ((cPropertyList*)pOwnerRef)->v0c();
        ((cDebugOwner*)*(void**)((uint8_t*)pOwnerRef + 0x58))->SetPosition(&mVelocity);
        DebugBehaviorFetchAnimation(pOwnerRef, 1);
    }
}

// ---------------------------------------------------------------------------
// 0x00aef390  SP::cDebugBehavior::SetEnabled
// ---------------------------------------------------------------------------
// @ 0x00aef390
void cDebugBehavior::SetEnabled(uint8_t bEnabled, float fRate)
{
    mbEnabled = bEnabled;
    mfRate = 1.0f / fRate;
    if (bEnabled != 0) {
        *(float*)((uint8_t*)mpOwnerRef + 0x68) = 1.0f;
        return;
    }
    *(float*)((uint8_t*)mpOwnerRef + 0x68) = 0.1f;
}

// ---------------------------------------------------------------------------
// 0x00aef410  SP::cDebugBehavior::Update
// ---------------------------------------------------------------------------
// @ 0x00aef410
void cDebugBehavior::Update(float fDelta)
{
    if (*(int*)((uint8_t*)mpOwnerRef + 8) == 0 || mbBlendActive != 0) {
        mCurrent.mX = mTarget.mX;
        mCurrent.mY = mTarget.mY;
        mCurrent.mZ = mTarget.mZ;
        mCurrent.mW = mTarget.mW;
        return;
    }

    float fGoal = mbBlendToEnabled == 0 ? 0.0f : 1.0f;
    mfBlend = (fGoal - mfBlend) * 0.5f + mfBlend;
    if (0.001f <= mfBlend) {
        if (0.999f < mfBlend) {
            mfBlend = 1.0f;
            mbBlendActive = 0;
        }
    } else {
        mfBlend = 0.0f;
    }

    float fBlend = mfBlend;
    void* pOwner = *(void**)((uint8_t*)mpOwnerRef + 0x58);
    float fInverse = 1.0f - fBlend;
    mCurrent.mX = mTarget.mX * fInverse + *(float*)((uint8_t*)pOwner + 0x40) * fBlend;
    mCurrent.mY = mTarget.mY * fInverse + *(float*)((uint8_t*)pOwner + 0x44) * fBlend;
    mCurrent.mZ = mTarget.mZ * fInverse + *(float*)((uint8_t*)pOwner + 0x48) * fBlend;
    mCurrent.mW = mTarget.mW * fInverse + *(float*)((uint8_t*)pOwner + 0x4c) * fBlend;
    (void)fDelta;
}

// ---------------------------------------------------------------------------
// 0x00aef530  SP::cDebugBehavior::SetTransform
// ---------------------------------------------------------------------------
// @ 0x00aef530
void cDebugBehavior::SetTransform(const Vec4* pTransform, bool bSnap)
{
    mTransform.mX = pTransform->mX;
    mTransform.mY = pTransform->mY;
    mTransform.mZ = pTransform->mZ;
    mTransform.mW = pTransform->mW;
    if (*(int*)((uint8_t*)mpOwnerRef + 8) != 0 && bSnap)
        ((cTimerThing*)mpOwnerRef)->Snap(pTransform);
}

// ---------------------------------------------------------------------------
// 0x00aef570  SP::cDebugBehavior::AddVelocity
// ---------------------------------------------------------------------------
// @ 0x00aef570
void cDebugBehavior::AddVelocity(const Vec4* pVelocity)
{
    float fInverse = 1.0f / mfScale;
    mVelocity.mX = pVelocity->mX * fInverse + mVelocity.mX;
    mVelocity.mY = pVelocity->mY * fInverse + mVelocity.mY;
    mVelocity.mZ = pVelocity->mZ * fInverse + mVelocity.mZ;
    mVelocity.mW = pVelocity->mW * fInverse + mVelocity.mW;
}
