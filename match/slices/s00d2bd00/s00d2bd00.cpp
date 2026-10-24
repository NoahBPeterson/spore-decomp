// Creature timer bar, display strategy visibility handling, the eastl style
// pool/hash helpers next to them and the creature display activation path.

typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long long uint64_t;

#define nullptr 0

// ---------------------------------------------------------------------------
// UI objects.
// ---------------------------------------------------------------------------
class cUIWindow {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual int32_t IsShown();                  // 0x028
    virtual void v2c(); virtual void v30(); virtual void v34();
    virtual float* GetPosition();               // 0x038
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void v5c();
    virtual void SetRect(void* pRect);          // 0x060
    virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void SetPosition(float fX, float fY);          // 0x070
    virtual void v74(); virtual void v78();
    virtual void SetVisible(int32_t nShow, int32_t nFade); // 0x07c
};

class cEventList {
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
    virtual void SetActive(int32_t nActive);    // 0x0c0

    uint8_t mPad004[0xa0];                      // 0x004
    void** mpEntryBegin;                        // 0x0a4
    void** mpEntryEnd;                          // 0x0a8
};

class cSPUILayout {
public:
    void* FindWindowByID(int32_t nId, int32_t nSearchChildren);   // 0x008105b0
};

class cSPTimer {
public:
    void Start();                               // 0x00bc30f0
    bool IsRunning();                           // 0x00feba90
    uint64_t GetElapsedTime();                  // 0x00bc3190
};

class cSPUIGlobalUI {
public:
    void Construct();                           // 0x00e03ab0
    void SetVisibility(int32_t nVisible);       // 0x00e01350
    void* FindWindowByID(int32_t nId, int32_t nSearchChildren);   // 0x00e012b0
};

class cSPUIEventLog {
public:
    void SetVisibility(int32_t nVisible);       // 0x00dd8da0
};

class cAvatar {
public:
    bool IsDisplayMode();                       // 0x00c0c120
};

class cRefCounted {
public:
    virtual void AddRef();                      // slot 0x00
    virtual void Release();                     // slot 0x04
};

class cCreatureTimerBar {
public:
    void Update(cAvatar* pAvatar, void* pCreature);
    void SetBarPosition(float fValue);
    void SetVisibility(int32_t nVisible);       // 0x00d2bc90

    uint8_t mbVisible;                          // 0x000
    uint8_t mPad001[0x03];                      // 0x001
    cSPUILayout* mpLayout;                      // 0x004
    float mafFillRect[4];                       // 0x008
    uint8_t mPad018[0x20];                      // 0x018
    cSPTimer mFadeTimer;                        // 0x038
};

class cCreatureData {
public:
    uint8_t mPad000[0x5c8];                     // 0x000
    int32_t mnHealth;                           // 0x5c8
};

class cCreature {
public:
    uint8_t mPad000[0xb20];                     // 0x000
    cCreatureData* mpData;                      // 0xb20
    uint8_t mPadB24[0x90];                      // 0xb24
    int32_t mnMaxHealth;                        // 0xbb4
};

class cCreatureDisplayStrategy {
public:
    void UpdateAfterEditor(void* pItem);
    void SetUIVisible(int32_t nVisible);
    void ReloadTuning();
    void AddPosseItem(void* pItem);
    void OnSelectItem(void* pSelection, int32_t nMode);
    void Activate(int32_t nMode, int32_t nFlags);

    uint8_t mPad000[0x04];                      // 0x000
    uint8_t mbField04;                          // 0x004
    uint8_t mPad005[0x50];                      // 0x005
    uint8_t mbField55;                          // 0x055
    uint8_t mPad056[0x02];                      // 0x056
    cSPUIGlobalUI* mpGlobalUI;                  // 0x058
    cEventList* mpEventList;                    // 0x05c
    uint8_t mPad060[0x48];                      // 0x060
    cCreatureTimerBar mTimerBar;                // 0x0a8
};

// ---------------------------------------------------------------------------
// eastl style intrusive hash table and pool allocator.
// ---------------------------------------------------------------------------
class cBucketNode {
public:
    uint32_t mnHash;                            // 0x000
    uint8_t mPad004[0x10];                      // 0x004
    cBucketNode* mpNext;                        // 0x014
};

class cBucketTable {
public:
    void Rebuild(uint32_t nBucketCount);

    uint8_t mPad000[0x04];                      // 0x000
    void** volatile mpBuckets;                  // 0x004
    uint32_t mnBucketCount;                     // 0x008
    uint8_t mPad00c[0x10];                      // 0x00c
    void* mpFreeHead;                           // 0x01c
    uint8_t mPad020[0x04];                      // 0x020
    void* mpPoolLo;                             // 0x024
    void* mpPoolHi;                             // 0x028
    uint8_t mPad02c[0x04];                      // 0x02c
    void* mpSentinel;                           // 0x030
};

class cPoolBlock {
public:
    uint8_t mPad000[0x04];                      // 0x000
    void* mpNextBlock;                          // 0x004
};

class cPool {
public:
    void Advance();
    void Allocate(void** ppValue);

    uint8_t mPad000[0x08];                      // 0x000
    uint8_t* mpCurrent;                         // 0x008
    uint8_t* mpBlock;                           // 0x00c
    uint8_t* mpBlockEnd;                        // 0x010
    cPoolBlock** mppBlockCursor;                // 0x014
};

class cAllocPool {
public:
    void Allocate(void** ppValue);

    cPoolBlock** mppBlockBase;                  // 0x000
    int32_t mnCapacity;                         // 0x004
    uint8_t mPad008[0x10];                      // 0x008
    void* mpFreeEntry;                          // 0x018
    uint8_t* mpBlock;                           // 0x01c
    uint8_t* mpBlockEnd;                        // 0x020
    cPoolBlock** mppBlockCursor;                // 0x024
};

class cListNode {
public:
    uint8_t mPad000[0x04];                      // 0x000
    cRefCounted* mpValue;                       // 0x004
    cListNode* mpNext;                          // 0x008
};

class cListIterator {
public:
    cListNode* mpNode;                          // 0x000
    void** mpSlot;                              // 0x004
};

class cNodeList {
public:
    cListIterator* Erase(cListIterator* pOut, cListNode* pNode, cListNode** ppHead);

    uint8_t mPad000[0x0c];                      // 0x000
    int32_t mnCount;                            // 0x00c
    uint8_t mPad010[0x0c];                      // 0x010
    cListNode* mpFreeHead;                      // 0x01c
    uint8_t mPad020[0x04];                      // 0x020
    void* mpPoolLo;                             // 0x024
    void* mpPoolHi;                             // 0x028
    uint8_t mPad02c[0x04];                      // 0x02c
    void* mpSentinel;                           // 0x030
};

// ---------------------------------------------------------------------------
// Free services and helpers.
// ---------------------------------------------------------------------------
void* __cdecl operator_new(uint32_t nSize, const char* pName, int32_t nFlags,
                           int32_t nAlignment, const char* pFile, int32_t nLine);
void __cdecl operator_delete_array(void* pBlock);

void* __stdcall AllocHashBuckets(uint32_t nBucketCount);  // 0x00c765a0
void __stdcall RaisePoolOverflow(int32_t nA, int32_t nB); // 0x01044f80
void ResetBarFade();                            // 0x00bc3170
void OnCreatureModeOff();                       // 0x00b6c280
cSPUIEventLog* EventLog();                      // 0x00b3d3e0
void* NounManager();                            // 0x00b3d300
void* GetAvatarNoun(void* pManager);            // 0x00b1fdb0
void* GetItemID(void* pNoun);                   // 0x00b1f9c0
void* FindPosseItem(void* pPosse, int32_t nIndex);      // 0x00e24c90
void SetWindowImage(void* pWindow, int32_t nImage);     // 0x00807bb0
int32_t CreateImageFromResource2(void* pRes, void** ppImage, int32_t nA, int32_t nB, int32_t nC); // 0x00806230
void FUN_00c0b780(void* pA, int32_t nB);
void FUN_00c0b7a0(void* pA, int32_t nB);
void FUN_00c0b950();
void FUN_00d49450(void* pA);
void FUN_00d2e4a0();
void FUN_00d2b8f0(void* pA, void* pB);
void FUN_00d2b5f0(void* pA);
void FUN_00d20950(void* pA, int32_t nB);
void FUN_00d49820(void* pA, int32_t nB);
void FUN_00d38780(void* pA, int32_t nB);
void FUN_00d4a570();
void FUN_00f924e0(void* pA);
void FUN_00c0bc00();
void FUN_00e39710(void* pA);
void FUN_00d38840();
void KillSetiEffects(uint32_t nId);             // 0x00435ed0
void* GetRecorderState();                       // 0x00435e90
void* App();                                    // 0x0067dd10
void* MessageServer();                          // 0x0067dcc0
void SlotMessage_Construct(void* pSlot, void* pMsg);    // 0x00421c80
void FUN_00b60a50(void* pA);
void FUN_00e25710(void* pA, void* pB);
void FUN_009512c0();
void* FUN_009512d0(void* pA, int32_t nLine);
void FUN_00ac8f00(void* pOut, uint32_t nId, int32_t nTag, float fA, float fB);
void FUN_00dd5a10(float fA, float fB);
void* cString_Construct(void* pOut, uint32_t nA, uint32_t nB, const wchar_t* pText); // 0x006b5770
const wchar_t* cString_GetText(void* pString);  // 0x006b55c0
void cString_Destroy(void* pString);            // 0x006b5240
void* GetTuningValue(void* pA);                 // 0x00c04590

class cSPVector2 {
public:
    float x;
    float y;
};

extern const char gsAllocatorFile[];
extern const char gsSimulatorTag[];
float g_fPoolSentinelValue = 0.0f;
float g_fTuningDefault = 0.0f;
float g_fOne = 1.0f;
uint8_t* g_pInstanceCreatureModeStrategy = nullptr;

// ---------------------------------------------------------------------------
// 0x00d2bd00  cCreatureTimerBar::Update
// ---------------------------------------------------------------------------
// @ 0x00d2bd00
void cCreatureTimerBar::Update(cAvatar* pAvatar, void* pCreature)
{
    struct cSPFillRect {
        float x;
        float y;
        float x2;
        float y2;
    };

    cUIWindow* pBar;

    if (!mbVisible || (!pAvatar->IsDisplayMode() && !mFadeTimer.IsRunning())) {
        pBar = (cUIWindow*)mpLayout->FindWindowByID(0x738ff863, 1);
        if ((pBar->IsShown() & 1) != 0) {
            mFadeTimer.Start();
            return;
        }
    }
    else {
        pBar = (cUIWindow*)mpLayout->FindWindowByID(0x738ff863, 1);
        pBar->SetVisible(1, 1);

        cCreature* pCreatureData = (cCreature*)pCreature;
        cCreatureData* pData = pCreatureData->mpData;

        float fFraction;
        if (pData->mnHealth > 0) {
            fFraction = (float)pCreatureData->mnMaxHealth - (float)pData->mnHealth;
            fFraction = fFraction / (float)pCreatureData->mnMaxHealth;
            if (fFraction < 0.0f)
                fFraction = 0.0f;
            if (fFraction > g_fOne)
                fFraction = g_fOne;
        }
        else {
            fFraction = 0.0f;
        }

        cUIWindow* pFill = (cUIWindow*)mpLayout->FindWindowByID(0x938ff6d1, 1);

        cSPFillRect rect;
        rect.x = mafFillRect[0];
        rect.y = mafFillRect[1];
        rect.x2 = (mafFillRect[2] - mafFillRect[0]) * fFraction + mafFillRect[0];
        rect.y2 = mafFillRect[3];
        pFill->SetRect(&rect);

        if (!mFadeTimer.IsRunning())
            return;

        if (pAvatar->IsDisplayMode()) {
            mFadeTimer.Start();
            return;
        }

        if (mFadeTimer.GetElapsedTime() <= 2000)
            return;

        ResetBarFade();
    }

    pBar->SetVisible(1, 0);
}

// ---------------------------------------------------------------------------
// 0x00d2beb0  cCreatureTimerBar::SetBarPosition
// ---------------------------------------------------------------------------
// @ 0x00d2beb0
void cCreatureTimerBar::SetBarPosition(float fValue)
{
    cUIWindow* pWindow = (cUIWindow*)mpLayout->FindWindowByID(0x738ff863, 1);
    float* pPosition = pWindow->GetPosition();
    pWindow->SetPosition(pPosition[0], fValue);
}

// ---------------------------------------------------------------------------
// 0x00d2bf60  cBucketTable::Rebuild
// ---------------------------------------------------------------------------
// @ 0x00d2bf60
void cBucketTable::Rebuild(uint32_t nBucketCount)
{
    void** pNewBuckets = (void**)AllocHashBuckets(nBucketCount);

    for (uint32_t nBucket = 0; nBucket < mnBucketCount; nBucket++) {
        cBucketNode* pNode = (cBucketNode*)mpBuckets[nBucket];
        while (pNode != nullptr) {
            uint32_t nHash = pNode->mnHash;
            mpBuckets[nBucket] = pNode->mpNext;
            pNode->mpNext = (cBucketNode*)pNewBuckets[nHash % nBucketCount];
            pNewBuckets[nHash % nBucketCount] = pNode;
            pNode = (cBucketNode*)mpBuckets[nBucket];
        }
    }

    void* pOldBuckets = mpBuckets;
    if (mnBucketCount > 1 && pOldBuckets != mpSentinel) {
        if (pOldBuckets >= mpPoolLo && pOldBuckets < mpPoolHi) {
            *(void**)pOldBuckets = mpFreeHead;
            mpFreeHead = pOldBuckets;
        }
        else {
            operator_delete_array(pOldBuckets);
        }
    }

    mpBuckets = pNewBuckets;
    mnBucketCount = nBucketCount;
}

// ---------------------------------------------------------------------------
// 0x00d2c000  cCreatureDisplayStrategy::UpdateAfterEditor
// ---------------------------------------------------------------------------
// @ 0x00d2c000
void cCreatureDisplayStrategy::UpdateAfterEditor(void* pItem)
{
    cUIWindow* pWindow;
    void* pAvatar = GetAvatarNoun(NounManager());
    void* pItemId = GetItemID(pItem);

    pWindow = (cUIWindow*)mpGlobalUI->FindWindowByID(0x3d99151, 1);
    SetWindowImage(pWindow, 1);

    void* pImage = nullptr;
    if (CreateImageFromResource2(pItemId, &pImage, 0, 0, 0) != 0)
        SetWindowImage(pWindow, (int32_t)pImage);

    FUN_00c0b780(pAvatar, 1);
    FUN_00c0b7a0(pWindow, 1);
    FUN_00c0b7a0(pWindow, 2);

    pWindow = (cUIWindow*)mpGlobalUI->FindWindowByID(0x578f7f8, 1);
    pWindow->SetVisible(1, 0);
    FUN_00d49450(pWindow);
    FUN_00c0b7a0(pWindow, 0);
    FUN_00d2e4a0();
}

// ---------------------------------------------------------------------------
// 0x00d2c200  cCreatureDisplayStrategy::SetUIVisible
// ---------------------------------------------------------------------------
// @ 0x00d2c200
void cCreatureDisplayStrategy::SetUIVisible(int32_t nVisible)
{
    if (mpGlobalUI != nullptr)
        mpGlobalUI->SetVisibility(nVisible);

    if (mpEventList != nullptr) {
        int32_t nEntryCount = (int32_t)(((uint8_t*)mpEventList->mpEntryEnd -
                                        (uint8_t*)mpEventList->mpEntryBegin) >> 3);
        mpEventList->SetActive((nVisible != 0 && (uint32_t)nEntryCount > 0) ? 1 : 0);
    }

    cSPUIEventLog* pEventLog = EventLog();
    if (pEventLog != nullptr)
        pEventLog->SetVisibility(nVisible);

    if (nVisible == 0)
        OnCreatureModeOff();

    mTimerBar.SetVisibility(nVisible);
    mbField55 = (uint8_t)nVisible;
}

// ---------------------------------------------------------------------------
// 0x00d2c280  cCreatureDisplayStrategy::ReloadTuning
// ---------------------------------------------------------------------------
// @ 0x00d2c280
void cCreatureDisplayStrategy::ReloadTuning()
{
    cSPVector2 values;
    values.x = 0.0f;
    values.y = g_fTuningDefault;

    FUN_00ac8f00(&values, 0xff259ba2, 0, 0.0f, -100.0f);
    FUN_00dd5a10(values.y, values.x);
    FUN_00dd5a10(values.x, values.y);
}

// ---------------------------------------------------------------------------
// 0x00d2c2e0  cCreatureDisplayStrategy::AddPosseItem
// ---------------------------------------------------------------------------
// @ 0x00d2c2e0
void cCreatureDisplayStrategy::AddPosseItem(void* pItem)
{
    void* pPosse = FindPosseItem(mpGlobalUI, (int32_t)pItem);
    if (pPosse != nullptr) {
        FUN_00d2b8f0(this, pPosse);
        FUN_009512c0();
        void* pItemUI = FUN_009512d0((void*)"UI/PosseItem", 0x14c);
        FUN_00e25710(pItemUI, pItem);
        FUN_00d2b5f0(pItemUI);
        SetWindowImage(pItemUI, 1);
        FUN_00c0b7a0(pItemUI, 1);
    }
}

// ---------------------------------------------------------------------------
// 0x00d2c570  cCreatureDisplayStrategy::OnSelectItem
// ---------------------------------------------------------------------------
// @ 0x00d2c570
void cCreatureDisplayStrategy::OnSelectItem(void* pSelection, int32_t nMode)
{
    if (nMode == 0) {
        FUN_00c0bc00();
        FUN_00e39710(pSelection);
        FUN_00d20950(this, 1);
        return;
    }

    if (nMode == 1) {
        void* pApp = App();
        FUN_00c0b950();
        KillSetiEffects(0x9203d717);
        FUN_00d38780(GetRecorderState(), 1);
        FUN_00d49820(this, 1);
        FUN_00d20950(this, 2);
        return;
    }

    if (nMode == 2) {
        void* pApp = App();
        FUN_00c0b950();
        FUN_00d4a570();
        FUN_00f924e0(pApp);
        KillSetiEffects(0xb7233c0e);
        FUN_00d38840();
        FUN_00d38780(this, 1);
        FUN_00d20950(this, 1);
        return;
    }

    GetRecorderState();
    KillSetiEffects(0x9203d717);
    FUN_00d20950(this, 3);
}

// ---------------------------------------------------------------------------
// 0x00d2c9b0  cPool::Advance
// ---------------------------------------------------------------------------
// @ 0x00d2c9b0
void cPool::Advance()
{
    uint8_t* pNext = mpCurrent + 8;
    if (pNext == mpBlockEnd) {
        if (mpBlock != nullptr)
            operator_delete_array(mpBlock);

        cPoolBlock** ppCursor = mppBlockCursor + 1;
        mppBlockCursor = ppCursor;
        mpBlock = (uint8_t*)*ppCursor;
        mpBlockEnd = mpBlock + 0x100;
        pNext = mpBlock;
    }
    mpCurrent = pNext;
}

// ---------------------------------------------------------------------------
// 0x00d2c9f0  cNodeList::Erase
// ---------------------------------------------------------------------------
// @ 0x00d2c9f0
cListIterator* cNodeList::Erase(cListIterator* pOut, cListNode* pNode, cListNode** ppHead)
{
    cListNode* pNext = pNode->mpNext;
    pOut->mpNode = pNext;
    pOut->mpSlot = (void**)ppHead;

    while (pOut->mpNode == nullptr) {
        pOut->mpSlot = (void**)((uint8_t*)pOut->mpSlot + 4);
        pOut->mpNode = (cListNode*)*pOut->mpSlot;
    }

    cListNode* pCur = *ppHead;
    if (pCur == pNode) {
        *ppHead = pCur->mpNext;
    }
    else {
        cListNode* pScan = pCur->mpNext;
        while (pScan != pNode) {
            pCur = pScan;
            pScan = pScan->mpNext;
        }
        pCur->mpNext = pScan->mpNext;
    }

    if (pNode->mpValue != nullptr)
        pNode->mpValue->Release();

    if (pNode != mpSentinel) {
        if ((void*)pNode >= mpPoolLo && (void*)pNode < mpPoolHi) {
            *(void**)pNode = mpFreeHead;
            mpFreeHead = pNode;
            mnCount--;
            return pOut;
        }
        operator_delete_array(pNode);
    }

    mnCount--;
    return pOut;
}

// ---------------------------------------------------------------------------
// 0x00d2ca90  cAllocPool::Allocate
// ---------------------------------------------------------------------------
// @ 0x00d2ca90
void cAllocPool::Allocate(void** ppValue)
{
    void* pFirst = ppValue[0];
    void* pSecond = ppValue[1];

    if ((int32_t)(mppBlockCursor - mppBlockBase) + 1 >= mnCapacity)
        RaisePoolOverflow(1, 1);

    void* pNewBlock = operator_new(0x100, "Simulator", 0, 0, gsAllocatorFile, 0xd1);
    mppBlockCursor[1] = (cPoolBlock*)pNewBlock;

    if (mpFreeEntry != nullptr) {
        void** pEntry = (void**)mpFreeEntry;
        pEntry[0] = pFirst;
        pEntry[1] = pSecond;
    }

    cPoolBlock** ppCursor = mppBlockCursor + 1;
    mppBlockCursor = ppCursor;
    mpBlock = (uint8_t*)*ppCursor;
    mpBlockEnd = mpBlock + 0x100;
    mpFreeEntry = mpBlock;
}

// ---------------------------------------------------------------------------
// 0x00d2cb10  cCreatureDisplayStrategy::Activate
// ---------------------------------------------------------------------------
// @ 0x00d2cb10
void cCreatureDisplayStrategy::Activate(int32_t nMode, int32_t nFlags)
{
    ReloadTuning();
    FUN_009512c0();
    void* pPosse = FUN_009512d0((void*)"UI/Posse", 0x20c);
    FUN_00e25710(pPosse, this);

    void* pNoun = GetAvatarNoun(NounManager());
    void* pItemId = GetItemID(pNoun);
    void* pValueA = GetTuningValue(pItemId);
    void* pValueB = GetTuningValue(pItemId);
    AddPosseItem(pValueA);
    AddPosseItem(pValueB);

    AddPosseItem(pValueB);

    cSPUIGlobalUI* pGlobal = (cSPUIGlobalUI*)operator_new(0x68, "Simulator", 0, 0, gsAllocatorFile, 0xd1);
    pGlobal->Construct();
    mpGlobalUI = pGlobal;

    if (nFlags != 0)
        KillSetiEffects(0xad56080c);

    mbField04 = (uint8_t)nMode;
}
