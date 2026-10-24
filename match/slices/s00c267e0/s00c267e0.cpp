// Creature citizen construction, per frame update, tool use and the small
// container/name helpers that live next to it.

typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define nullptr 0

// ---------------------------------------------------------------------------
// Raw dispatch helper for interface slots that are too high to spell out as
// virtual members of the reconstructed classes.
// ---------------------------------------------------------------------------
struct cVTable {
    void* mpSlots[0x100];                       // 0x000
};

class cDispatchObject {
public:
    void* Call(int nSlot) {
        return ((void* (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    int32_t CallInt(int nSlot) {
        return ((int32_t (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    void CallVoid(int nSlot) {
        ((void (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    void CallVoidArg(int nSlot, void* pArg) {
        ((void (*)(cDispatchObject*, void*))mpTable->mpSlots[nSlot >> 2])(this, pArg);
    }

    cVTable* mpTable;                           // 0x000
};

// Reference counted interfaces: slot 0 is add, slot 4 is release.
class cRefCounted {
public:
    virtual void AddRef();                      // slot 0x00
    virtual void Release();                     // slot 0x04
};

// ---------------------------------------------------------------------------
// Sub objects and services used by the citizen.
// ---------------------------------------------------------------------------
class cCommunity {
public:
    void* GetLeader();                          // 0x00c00650
};

class cLocomotive {
public:
    void ResetLocomotion();                     // 0x00c44040
    void SetStrategy(void* pStrategy);          // 0x00c421b0
    void AddStrategy(void* pStrategy);          // 0x00c43fe0
    int32_t IsHidden();                         // slot 0x58 of the interface

    void* mpVtblLocal;                          // 0x000
    uint8_t mPad004[0xd0];                      // 0x004
};

class cBehaviorAgent {
public:
    void SetActive(int32_t nActive);            // slot 0x14 of the interface

    void* mpVtblLocal;                          // 0x000
    uint8_t mPad004[0x64];                      // 0x004
};

class cGonzagoTimer {
public:
    void Reset();
    void Restart();
    void Destroy();                             // 0x00b638b0

    uint8_t mbField20[0x20];                    // 0x000
    int32_t mnField24;                          // 0x020
    int32_t mnField28;                          // 0x024
    int32_t mnField2c;                          // 0x028
    int32_t mnField30;                          // 0x02c
    uint8_t mbField34;                          // 0x030
    uint8_t mPad035;                            // 0x031
    uint8_t mbField36;                          // 0x032
    uint8_t mPad037;                            // 0x033
    float mafOffset[3];                         // 0x034
};

class cStarRecordVector {
public:
    void Destroy();                             // 0x00ae6970
    cStarRecordVector& CopyFrom(cStarRecordVector* pOther);

    void* mpBegin;                              // 0x000
    void* mpEnd;                                // 0x004
    void* mpCapacity;                           // 0x008
};

class cCreatureCitizen {
public:
    void TakeToolHit(int32_t nToolIndex, int32_t nSource, int32_t nFlags, int32_t nUnused,
                     void* pInfo);
    void CreateLocomotionStrategy();
    void ApplyToolOrder(uint32_t nToolMask, void* pOrder);
    void UpdateSelectionFlags();
    cCreatureCitizen* Construct();
    void Destroy();
    void UpdateFrame(void* pTransform, int32_t nMode, int32_t nFlags, void* pContext);
    void* GiveOrder(void* pOrderInfo, void* pTarget, void* pParams);
    int32_t SelectSpeciesProfile(void* pSpeciesKey);
    void SetCreatureName(const char* pName);
    int32_t GetToolEffect(int32_t nTool);
    void ApplyOrder(int32_t nTool, void* pOrder);
    int32_t OnProfileSelected(void* pSpeciesKey);
    void SetLocalizedName(char** ppText);       // 0x00c43e40

    void* mpVtbl00;                             // 0x000
    void* mpVtbl04;                             // 0x004
    uint8_t mPad008[0x2c];                      // 0x008
    void* mpVtbl34;                             // 0x034
    uint8_t mPad038[0x20];                      // 0x038
    cBehaviorAgent mAgent;                      // 0x058
    cLocomotive mLocomotion;                    // 0x0c0
    void* mpVtbl194;                            // 0x194
    uint8_t mPad198[0x118];                     // 0x198
    int32_t mnPlanetCorrection;                 // 0x2b0
    uint8_t mPad2b4[0x2dc];                     // 0x2b4
    void* mpVtbl590;                            // 0x590
    uint8_t mPad594[0x14];                      // 0x594
    void* mpVtbl5a8;                            // 0x5a8
    uint8_t mPad5ac[0x34];                      // 0x5ac
    float mfToolDurability;                     // 0x5e0
    uint8_t mPad5e4[0x8c];                      // 0x5e4
    void* mpVtbl670;                            // 0x670
    uint8_t mPad674[0x4ac];                     // 0x674
    void* mpProfile;                            // 0xb20
    uint8_t mPadB24[0x04];                      // 0xb24
    uint8_t mSpeciesKey[0x20];                  // 0xb28
    void* mpFieldB48;                           // 0xb48
    cDispatchObject* mpFieldB4C;                // 0xb4c
    uint8_t mPadB50[0x0e];                      // 0xb50
    uint8_t mbFieldB5E;                         // 0xb5e
    uint8_t mPadB5f[0x2e1];                     // 0xb5f
    void* mpListBegin;                          // 0xe40
    void* mpListEnd;                            // 0xe44
    uint8_t mPadE48[0x188];                     // 0xe48
    cGonzagoTimer mTimer;                       // 0xfd0
    cRefCounted* mpOwnerCity;                   // 0x1010
    cRefCounted* mpOwnerTribe;                  // 0x1014
    cStarRecordVector mStarRecords;             // 0x1018
    int32_t mnSpecializedTool;                  // 0x1024
    cRefCounted* mpHitSphere;                   // 0x1028
    int32_t mnToolEffectIndex;                  // 0x102c
    cRefCounted* mpRequest;                     // 0x1030
};

// ---------------------------------------------------------------------------
// Services and free helpers.
// ---------------------------------------------------------------------------
class cCreatureBase {
public:
    void ConstructBase();
    void DestroyBase();                         // 0x00c1bbd0
    void OnTakeHit(int32_t nSource, int32_t nFlags, int32_t nUnused, void* pInfo);
};

class cSimulatorService {
public:
    void* GetWorldStrategy();
    void* GetDefaultStrategy();
};

class cFlagOwner {
public:
    int32_t mnFlags;                            // 0x5fc
};

class cCitizenQueue {
public:
    int32_t mnFlagsA;
    int32_t mnFlagsB;
    int32_t mnFlagsC;
};

void* __cdecl operator_new(uint32_t nSize, const char* pName, int32_t nFlags,
                           int32_t nAlignment, const char* pFile, int32_t nLine);
void __cdecl operator_delete_array(void* pBlock);

cSimulatorService* GetSimulatorService();       // 0x00b3d310
void PlanetLocomotionStrategy();
void SpaceLocomotionStrategy();
void RestartCitizenTimers();                    // 0x00c0ba10
int32_t UpdateCitizenEffects();                 // 0x00c0b770
void ForceOrdersUpdate(cCreatureCitizen* pCitizen);   // 0x00c26450
void __stdcall RebuildCitizenOrderList(int32_t nIndex);   // 0x00c26310
void PlayCitizenEffect(int32_t nEffect, int32_t nFlags, float fScale, void* pTarget);
void OnCitizenFlagChanged(int32_t nId, int32_t nValue);
int32_t GetSettingId(void* pKey);               // 0x00401090
void* GetProfileFromKey(void* pKey);            // 0x004df550
void FUN_00bc8fa0(void* pData);
void FUN_00bcb660(void* pData);
void FUN_00bc9a30(int32_t nId, void* pData);
void FUN_00c0cf50();
void* FUN_00bd99e0();
void* FUN_00b6f0c0(void* pData);
void FUN_00c0d950(int32_t nValue);
void FUN_00c21090();
void FUN_00c24110(cCreatureCitizen* pCitizen);
void* CreateCitizenNoun(int32_t nNounId);
void FUN_00c3f160(float fA, float fB);
void FUN_00c3f2d0(cCreatureCitizen* pCitizen);
void* FUN_00bca2c0();
void FUN_00bca470();
void FUN_00c26730(void* pOrder);
void* FUN_00bcaf70(void* pTarget, void* pParams, int32_t nFlags);
int32_t FUN_00bca180(void* pOrder);
void FUN_00bca120();
void CopyStarRecordRange(cStarRecordVector*& rpCursor, void* pBegin, void* pEnd, void* pBuffer,
                         cStarRecordVector* pSource);   // 0x00c266c0

class cGonzagoTempText {
public:
    cGonzagoTempText(const char* pText);        // 0x00b46d90

    char* mpText;                               // 0x000
    uint8_t mPad004[0x6c];                      // 0x004
};

class cTextAllocation {
public:
    int32_t mnSize;                             // 0x000 (stored right before the characters)
};

extern const char gsAllocatorFile[];
cCitizenQueue g_citizenQueue;
uint8_t g_bCitizenQueueInitialized = 0;
uint8_t g_bCitizenGlobalsReady = 0;
float g_fOffsetX = 0.0f;
float g_fOffsetY = 0.0f;
float g_fOffsetZ = 0.0f;
float g_fCitizenScale = 0.0f;
int32_t g_nCitizenMode = 0;
float g_fMaxFloat = 3.402823466e38f;

// ---------------------------------------------------------------------------
// 0x00c267e0  cCreatureCitizen::TakeToolHit
// ---------------------------------------------------------------------------
// @ 0x00c267e0
void cCreatureCitizen::TakeToolHit(int32_t nToolIndex, int32_t nSource, int32_t nFlags,
                                   int32_t nUnused, void* pInfo)
{
    float fOldDurability = mfToolDurability;
    ((cCreatureBase*)this)->OnTakeHit(nSource, nFlags, nUnused, pInfo);

    if (mfToolDurability >= 0.000015258789f) {
        if (mpOwnerTribe != nullptr) {
            if (nToolIndex != -1) {
                void* pTool = ((cDispatchObject*)this)->Call(0x4c);
                PlayCitizenEffect(0, nToolIndex, 1.0f, pTool);
            }
            if (pInfo != nullptr) {
                void* pEffect = ((cDispatchObject*)pInfo)->Call(0x08);
                void* pTarget = ((cDispatchObject*)pInfo)->Call(0x0c);
                int32_t nAmount = ((cDispatchObject*)pEffect)->CallInt(0x74);
                ((cDispatchObject*)pTarget)->Call(0x2c);
                OnCitizenFlagChanged((int32_t)0xb9d14c31u, nAmount);
            }
        }
    }
    else if (mpOwnerTribe != nullptr && fOldDurability > 0.000015258789f) {
        if (((cDispatchObject*)this)->CallInt(0x58) == 0) {
            if (((cDispatchObject*)this)->CallInt(0x58) == 0 && mpOwnerTribe != nullptr) {
                if (pInfo != nullptr)
                    ((cDispatchObject*)pInfo)->Call(0x0c);
                OnCitizenFlagChanged(0x7c5b1068, 0);
            }
        }
        else {
            if (pInfo != nullptr)
                ((cDispatchObject*)pInfo)->CallVoid(0x20);
            OnCitizenFlagChanged((int32_t)0xb9d14c31u, 2);
        }
    }

    if (mpOwnerTribe != nullptr && pInfo != nullptr)
        OnCitizenFlagChanged((int32_t)0xd0036e08u, 0);
    else if (pInfo != nullptr && ((cDispatchObject*)pInfo)->CallInt(0x5c) != 0)
        PlayCitizenEffect(0, 0x80, 5.0f, nullptr);

    UpdateCitizenEffects();
}

// ---------------------------------------------------------------------------
// 0x00c26c10  cCreatureCitizen::CreateLocomotionStrategy
// ---------------------------------------------------------------------------
// @ 0x00c26c10
void cCreatureCitizen::CreateLocomotionStrategy()
{
    mnPlanetCorrection = 0;
    mLocomotion.ResetLocomotion();

    if (mpOwnerTribe != nullptr) {
        mLocomotion.SetStrategy(GetSimulatorService()->GetWorldStrategy());
        return;
    }

    mLocomotion.AddStrategy((void*)&PlanetLocomotionStrategy);
    mLocomotion.AddStrategy((void*)&SpaceLocomotionStrategy);
    mLocomotion.SetStrategy(GetSimulatorService()->GetDefaultStrategy());
}

// ---------------------------------------------------------------------------
// 0x00c26c80  RebuildCitizenOrderListDefault
// ---------------------------------------------------------------------------
// @ 0x00c26c80
void RebuildCitizenOrderListDefault()
{
    RebuildCitizenOrderList(-1);
}

// ---------------------------------------------------------------------------
// 0x00c26c90  cCreatureCitizen::ApplyToolOrder
// ---------------------------------------------------------------------------
// @ 0x00c26c90
void cCreatureCitizen::ApplyToolOrder(uint32_t nToolMask, void* pOrder)
{
    uint32_t nEffect;

    if (mnToolEffectIndex != 0) {
        nEffect = (uint32_t)GetToolEffect(mnToolEffectIndex);
        if (nEffect == 0)
            goto default_order;
    }
    else {
        cCommunity* pCommunity = (cCommunity*)mpOwnerCity;
        if (pCommunity == nullptr) {
            pCommunity = (cCommunity*)mpOwnerTribe;
            if (pCommunity == nullptr)
                goto default_order;
        }
        if (pCommunity->GetLeader() != this)
            goto default_order;
        nEffect = 0x11;
    }

    if ((nToolMask & (1u << nEffect)) != 0) {
        ApplyOrder((int32_t)nEffect, pOrder);
        return;
    }

default_order:
    ApplyOrder(0, pOrder);
}

// ---------------------------------------------------------------------------
// 0x00c26d10  cCreatureCitizen::UpdateSelectionFlags
// ---------------------------------------------------------------------------
// @ 0x00c26d10
void cCreatureCitizen::UpdateSelectionFlags()
{
    if (mpOwnerTribe == nullptr && mbFieldB5E == 0)
        return;

    if (!g_bCitizenQueueInitialized) {
        FUN_00bc8fa0(&g_citizenQueue);
        g_bCitizenQueueInitialized = 1;
    }
    FUN_00bcb660(&g_citizenQueue);

    cFlagOwner* pFlags = (cFlagOwner*)mpFieldB4C;
    int32_t nHidden = mLocomotion.IsHidden();
    int32_t nFlags = pFlags->mnFlags;
    pFlags->mnFlags = nFlags | (nHidden != 0 ? 1 : 0);

    nFlags = pFlags->mnFlags;
    int32_t nAlive = UpdateCitizenEffects() != 0 ? 2 : 0;
    pFlags->mnFlags = nFlags | nAlive;

    bool bLeader;
    if (mpOwnerCity != nullptr || mpOwnerTribe != nullptr) {
        cCommunity* pCommunity = (cCommunity*)(mpOwnerCity != nullptr ? mpOwnerCity : mpOwnerTribe);
        bLeader = pCommunity->GetLeader() == this;
    }
    else {
        bLeader = false;
    }
    pFlags->mnFlags |= bLeader ? 0x20 : 0;

    mAgent.SetActive(1);
    ForceOrdersUpdate(this);
}

// ---------------------------------------------------------------------------
// 0x00c26e00  cCreatureCitizen::Construct
// ---------------------------------------------------------------------------
// @ 0x00c26e00
cCreatureCitizen* cCreatureCitizen::Construct()
{
    ((cCreatureBase*)this)->ConstructBase();

    mpVtbl00 = (void*)0x146ad60;
    mpVtbl04 = (void*)0x146ad4c;
    mpVtbl34 = (void*)0x146ad08;
    mAgent.mpVtblLocal = (void*)0x146aca0;
    mLocomotion.mpVtblLocal = (void*)0x146aba0;
    mpVtbl194 = (void*)0x146ab94;
    mpVtbl590 = (void*)0x146ab78;
    mpVtbl5a8 = (void*)0x146ab10;
    mpVtbl670 = (void*)0x146aaf8;

    mTimer.mbField20[0] = 0;
    mTimer.mbField20[1] = 0;
    mTimer.mbField20[2] = 0;
    mTimer.mbField20[3] = 0;
    mTimer.mbField20[4] = 1;
    mTimer.mnField24 = 3;
    mTimer.Reset();
    mTimer.mnField28 = 0;
    mTimer.mnField2c = -1;
    mTimer.mnField30 = 0;
    mTimer.mbField34 = 0;
    mTimer.mbField36 = 1;
    mTimer.mafOffset[0] = g_fOffsetX;
    mTimer.mafOffset[1] = g_fOffsetY;
    mTimer.mafOffset[2] = g_fOffsetZ;
    mpOwnerCity = nullptr;
    mpOwnerTribe = nullptr;
    mStarRecords.mpBegin = nullptr;
    mStarRecords.mpEnd = nullptr;
    mStarRecords.mpCapacity = nullptr;
    mnSpecializedTool = 0;
    mpHitSphere = nullptr;

    RestartCitizenTimers();
    CreateLocomotionStrategy();
    mTimer.Restart();

    if (!g_bCitizenGlobalsReady) {
        g_bCitizenGlobalsReady = 1;
        g_fCitizenScale = 0.0f;
        g_nCitizenMode = 1;
    }

    if (mpFieldB48 != nullptr)
        FUN_00bc9a30(2, &g_citizenQueue);

    return this;
}

// ---------------------------------------------------------------------------
// 0x00c27120  cCreatureCitizen::Destroy
// ---------------------------------------------------------------------------
// @ 0x00c27120
void cCreatureCitizen::Destroy()
{
    mpVtbl00 = (void*)0x146ad60;
    mpVtbl04 = (void*)0x146ad4c;
    mpVtbl34 = (void*)0x146ad08;
    mAgent.mpVtblLocal = (void*)0x146aca0;
    mLocomotion.mpVtblLocal = (void*)0x146aba0;
    mpVtbl194 = (void*)0x146ab94;
    mpVtbl590 = (void*)0x146ab78;
    mpVtbl5a8 = (void*)0x146ab10;
    mpVtbl670 = (void*)0x146aaf8;

    if (mpRequest != nullptr)
        mpRequest->Release();
    mStarRecords.Destroy();
    if (mpOwnerTribe != nullptr)
        mpOwnerTribe->Release();
    if (mpOwnerCity != nullptr)
        mpOwnerCity->Release();
    mTimer.Destroy();
    ((cCreatureBase*)this)->DestroyBase();
}

// ---------------------------------------------------------------------------
// 0x00c271d0  cCreatureCitizen::UpdateFrame
// ---------------------------------------------------------------------------
// @ 0x00c271d0
void cCreatureCitizen::UpdateFrame(void* pTransform, int32_t nMode, int32_t nFlags, void* pContext)
{
    ((cDispatchObject*)&mLocomotion)->CallVoid(0x38);
    ((cDispatchObject*)this)->CallVoid(0x3c);
    FUN_00c0cf50();
    UpdateCitizenEffects();

    int32_t nHidden = mLocomotion.IsHidden();
    if (nHidden == 0) {
        if (mpOwnerTribe == nullptr) {
            if (mpFieldB48 != nullptr)
                FUN_00bd99e0();
        }
        else {
            FUN_00b6f0c0(mpListBegin);
        }
    }
    FUN_00c0d950(nHidden == 0);

    if (mpOwnerTribe != nullptr)
        FUN_00c21090();
    FUN_00c24110(this);
    UpdateSelectionFlags();

    if (mpListEnd == nullptr) {
        void* pNoun = CreateCitizenNoun(0x2e72cae);
        if (pNoun != nullptr)
            pNoun = ((cDispatchObject*)pNoun)->Call(0x0c);
        cRefCounted* pOld = mpOwnerTribe;
        if (pNoun != (void*)pOld) {
            if (pNoun != nullptr)
                ((cRefCounted*)pNoun)->AddRef();
            mpOwnerTribe = (cRefCounted*)pNoun;
            if (pOld != nullptr)
                pOld->Release();
        }
        FUN_00c3f160(0.5f, 2.0f);
        FUN_00c3f2d0(this);
    }

    mbFieldB5E = mpOwnerTribe != nullptr ? 1 : 0;
    (void)pTransform;
    (void)nMode;
    (void)nFlags;
    (void)pContext;
}

// ---------------------------------------------------------------------------
// 0x00c275b0  cCreatureCitizen::GiveOrder
// ---------------------------------------------------------------------------
// @ 0x00c275b0
void* cCreatureCitizen::GiveOrder(void* pOrderInfo, void* pTarget, void* pParams)
{
    void* pExisting = FUN_00bca2c0();
    FUN_00bca470();
    if (pExisting != nullptr)
        FUN_00c26730(pExisting);

    void* pOrder = FUN_00bcaf70(pTarget, pParams, 1);
    if (pOrder == nullptr)
        return nullptr;

    ((cDispatchObject*)pOrder)->CallVoid(0x38);
    if (pOrderInfo != nullptr)
        ((cDispatchObject*)pOrder)->CallVoidArg(0x39, pOrderInfo);

    if (pTarget != nullptr) {
        void* pFirst = ((cDispatchObject*)pTarget)->Call(0x0c);
        void* pSecond = ((cDispatchObject*)pTarget)->Call(0x0c);
        if (pFirst == nullptr) {
            float* pPosition = (float*)((uint8_t*)pSecond + 0x10);
            OnCitizenFlagChanged((int32_t)pPosition[0], (int32_t)pPosition[1]);
        }
        else {
            ((cDispatchObject*)pFirst)->Call(0x2c);
        }
    }

    ForceOrdersUpdate(this);
    if (pExisting != nullptr) {
        if (FUN_00bca180(pOrder) == 0)
            PlayCitizenEffect(0x4000, 0, g_fMaxFloat, nullptr);
    }
    FUN_00bca120();
    return pOrder;
}

// ---------------------------------------------------------------------------
// 0x00c276d0  cCreatureCitizen::SelectSpeciesProfile
// ---------------------------------------------------------------------------
// @ 0x00c276d0
int32_t cCreatureCitizen::SelectSpeciesProfile(void* pSpeciesKey)
{
    void* pKey = mSpeciesKey;
    if (GetSettingId(pKey) < 0)
        return 0;

    void* pProfile = GetProfileFromKey(pKey);
    if (OnProfileSelected(pSpeciesKey) == 0)
        return 0;

    if (mpProfile != nullptr && mpOwnerTribe != nullptr) {
        if (pProfile != mpProfile)
            return 0;
        int32_t nCount = (int32_t)(((uint8_t*)mpListEnd - (uint8_t*)mpListBegin) / 0x48);
        if ((float)nCount >= mfToolDurability)
            return 1;
    }

    mpProfile = pProfile;
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00c277f0  cStarRecordVector::CopyFrom
// ---------------------------------------------------------------------------
// @ 0x00c277f0
cStarRecordVector& cStarRecordVector::CopyFrom(cStarRecordVector* pOther)
{
    int32_t nCount = (int32_t)(((uint8_t*)pOther->mpEnd - (uint8_t*)pOther->mpBegin) / 0x18);
    void* pBuffer;
    if (nCount == 0)
        pBuffer = nullptr;
    else
        pBuffer = operator_new(nCount * 0x18, "Simulator", 0, 0, gsAllocatorFile, 0xd1);

    mpCapacity = (uint8_t*)pBuffer + nCount * 0x18;
    mpBegin = pBuffer;
    mpEnd = pBuffer;
    CopyStarRecordRange(pOther, pOther->mpBegin, pOther->mpEnd, pBuffer, pOther);
    mpEnd = pOther;
    return *this;
}

// ---------------------------------------------------------------------------
// 0x00c278a0  cCreatureCitizen::SetCreatureName
// ---------------------------------------------------------------------------
// @ 0x00c278a0
void cCreatureCitizen::SetCreatureName(const char* pName)
{
    cGonzagoTempText temp(pName);
    SetLocalizedName(&temp.mpText);
    if (temp.mpText != nullptr) {
        if (((cTextAllocation*)temp.mpText - 1)->mnSize != 0)
            operator_delete_array(temp.mpText);
    }
}
