// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00e2f6e0.
//
// Asset discovery UI: card layout init, tuning reload, message handlers and
// the staged scale/rotation animation driver of the discovery manager.

typedef unsigned int size_t;
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef signed long long int64_t;
typedef unsigned long long uint64_t;
typedef int intptr_t;
#define nullptr 0

struct Vec3 {
    float mX;
    float mY;
    float mZ;
};

struct Rect {
    float mX;
    float mY;
    float mWidth;
    float mHeight;
};

class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};

class IWindow : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual void SetVisible(bool bVisible);
    virtual void v20();
    virtual void v24();
    virtual void v28(int a);
    virtual void v2c();
    virtual Rect* GetArea();
    virtual void SetPosition(float fX, float fY);
    virtual void SetScale(float fScale);
};

class cSPUILayout {
public:
    void Init(const wchar_t* pName, uint32_t a, int b, uint32_t c);
    IWindow* FindWindowByID(uint32_t nId, int bFind);
};

class cMessageServer {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20(void* pTarget, uint32_t nMessage);
    virtual void v24();
    virtual void v28(void* pTarget, uint32_t nMessage, int nData);
    virtual void v2c(void* pTarget, uint32_t nMessage, int nData);
};

class cSPUIAnimator {
public:
    void AddAnimation(void* pAnimation, void* pTarget, int nKind);
    void RemoveAnimation(void* pTarget, int nIndex);
    void Update();
};

class cSPAssetData : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    bool IsDiscovered();
    uint8_t mPad18[0x08];
};

class cSPUIAssetView : public IWindow {
public:
    void Bind(IWindow* pParent, cSPAssetData* pData, int a, int b);
};

class cMessageTarget {
public:
    virtual void v00();
    virtual void v04();
};

class cSPUIAssetDiscoveryCard : public IRefCounted {
public:
    void Init();
    void ApplyFrame(int* pData);
    cSPUIAssetDiscoveryCard* Clone();

    cSPUILayout* mpLayout;              // 0x00
    IWindow* mpParentWin;               // 0x04
    uint8_t mPad08[0x08];               // 0x08
    IWindow* mpTextWindow;              // 0x10
    cSPAssetData* mpAssetData;          // 0x14
    cSPUIAssetView* mpAssetView;        // 0x18
};

class cSPUIAssetDiscoveryManager : public cMessageTarget {
public:
    void Init();
    void ReloadTuning();
    void Shutdown();
    void Reset();
    void Update(uint nMilliseconds);
    int HandleCardMessage(int nMessage, int nData, int nFlags);
    int HandleAssetMessage(int nMessage, int nData);
    void ReleaseCurrentCard();
    void PushCard(cSPUIAssetDiscoveryCard** ppCard, int nFlags);

    uint8_t mPad14[0x0c];               // 0x14
    void* mpMessageTarget;              // 0x20
    uint8_t mPad24[0x08];               // 0x24
    cSPUIAssetDiscoveryCard** mpCardsBegin;   // 0x2c
    cSPUIAssetDiscoveryCard** mpCardsCur;     // 0x30
    cSPUIAssetDiscoveryCard** mpCardsEnd;     // 0x34
    cSPUIAssetDiscoveryCard** mpCardsCap;     // 0x38
    cSPUIAssetDiscoveryCard* mpCurrentCard;   // 0x3c
    cSPUIAssetDiscoveryCard* mpSelectedCard;  // 0x50
    int mnPaused;                       // 0x54
    int mnAnimationState;               // 0x58
    cSPUIAnimator* mpAnimator;          // 0x5c
    uint64_t mnElapsed;                 // 0x60
    int mnSlideInStart;                 // 0x68
    int mnSlideOutStart;                // 0x6c
    int mnRotateStart;                  // 0x70
    int mnZoomStart;                    // 0x74
    int mnStopLow;                      // 0x78
    int mnStopHigh;                     // 0x7c
    int mnScaleLow;                     // 0x80
    int mnScaleHigh;                    // 0x84
    int mnRotateLow;                    // 0x88
    int mnRotateHigh;                   // 0x8c
    int mnZoomLow;                      // 0x90
    int mnZoomHigh;                     // 0x94
    int mnFinalLow;                     // 0x98
    int mnFinalHigh;                    // 0x9c
    float mFinalScale;                  // 0xa0
    float mTimeStart;                   // 0xa4
    float mTimeScaleBack;               // 0xa8
    float mTimeRotate;                  // 0xac
    float mTimeStop;                    // 0xb0
    float mTime;                        // 0xb4
    int mCount;                         // 0xb8
    int64_t mTimeStopMS;                // 0xbc
    int64_t mTimeStartMS;               // 0xc4
    int64_t mTimeScaleBackMS;           // 0xcc
    int64_t mTimeRotateMS;              // 0xd4
    int64_t mTimeMS;                    // 0xdc
};

void* operator_new(size_t nSize, const char* pName, int a, int b, const char* pFile, int nLine);
void* operator_new(size_t nSize, const char* pName, int a, int b, int c, int d);
void operator_delete__(void* pMemory);
void* PropertyManager();
void* MessageServer();
uint32_t GetCurrentGameMode();
void* GetPropertyAsFloat();
void* GetPropertyAsKeyArray();
void* GetPropertyAsVariant(void* pValue, int a);
bool QueryTuningFloat(void* pDefinition, uint32_t nKey, float* pOut);
bool QueryTuningInt(void* pDefinition, uint32_t nKey, int* pOut);
bool QueryProperty(void* pData, uint32_t nKey, void** ppOut);
bool QueryDefinition(void* pPropertyManager, uint32_t nKey, void** ppOut);
void SetGlobalProperty(uint32_t key, uint32_t valueBits);
void* CenterWindowInRect(void* pLayout, void* pArea);
void GetMainWindowArea(Rect* pOut);
void* CreateAssetData(int nKind);
void* CreateAssetView();
void* CreateLayout();
void* CreateTimer();
void StartTimer(void* pTimer);
float GetElapsedSeconds(int nStart, int a, void* pTarget, int b);
void* CreateScaleAnimation(void* pBuffer, void* pTarget, int nStart, float fDuration);
void* CreateRotationAnimation(void* pBuffer, void* pTarget, int a, int b, int c, float fAngle,
                             float fDuration);
void* CreateTimerInterpolation(void* pBuffer, float fDuration);
void* CreateScaleAnimationFloat(void* pBuffer, void* pTarget, uint32_t fScale, void* pTimer);
void* Controller_Award(uint32_t nAchievement);
void AwardAchievement(void* pController, uint32_t nAchievement);
void SetWindowScale(void* pWindow, int a);
void SetWindowPosition(void* pWindow, float fX, float fY);
void UpdateWindowState(void* pWindow);
void* GetTutorialArea(Rect* pOut);
void GetTribeArea(Rect* pOut);
void* GetActiveStrategy(Rect* pOut);
void ResetCardState();
void ReleaseCardList();
void FlushCardAnimations();
void ResetTimer();
void ReloadCardList();
void RebuildCardFrames(int* pCard);
void ReleaseCardResource(int a);
void PushCardInternal();
void ResetAnimationState();
void ResetDiscoveryAnimation();
void CardMessageForward(int a);
bool IsCardVisible(void* pCard);
void* GetCardTarget(void* pCard);

extern uint8_t gGameModeSpace;
extern uint8_t gGameModeTribe;
extern const float gRotationAngle;

// ---------------------------------------------------------------------------
// 0x00e2f6e0  SP::cSPUIAssetDiscoveryCard::Init
// ---------------------------------------------------------------------------
// @ 0x00e2f6e0
void cSPUIAssetDiscoveryCard::Init()
{
    if (mpLayout == nullptr) {
        cSPUILayout* pLayout = nullptr;
        void* pMemory = (void*)(intptr_t)operator_new(0x18, "UI/AssetDiscovery_Layout", 0, 0, 0, 0);
        if (pMemory != nullptr) {
            Rect area;
            GetMainWindowArea(&area);
            pLayout = (cSPUILayout*)CenterWindowInRect(pMemory, &area);
        }

        cSPUILayout* pOldLayout = mpLayout;
        if (pLayout != pOldLayout) {
            if (pLayout != nullptr)
                ((IRefCounted*)pLayout)->AddRef();
            mpLayout = pLayout;
            if (pOldLayout != nullptr)
                pOldLayout->FindWindowByID(0, 0);
        }
        mpLayout->Init(L"AssetDiscovery", 0x40464100u, 1, 0x2edd95cau);
    }

    IWindow* pWindow = mpLayout->FindWindowByID(0xb4ae091du, 1);
    IWindow* pOldParent = mpParentWin;
    if (pWindow != pOldParent) {
        if (pWindow != nullptr)
            pWindow->AddRef();
        mpParentWin = pWindow;
        if (pOldParent != nullptr)
            pOldParent->Release();
    }

    IWindow* pText = mpLayout->FindWindowByID(0xd4e16e94u, 1);
    IWindow* pOldText = mpTextWindow;
    if (pText != pOldText) {
        if (pText != nullptr)
            pText->AddRef();
        mpTextWindow = pText;
        if (pOldText != nullptr)
            pOldText->Release();
    }

    Rect area;
    GetMainWindowArea(&area);
    mpParentWin->v28(0);

    if (mpAssetData == nullptr) {
        cSPAssetData* pData = nullptr;
        uint32_t nMode = GetCurrentGameMode();
        void* pMemory = nullptr;
        if (nMode == 0 || (nMode + 0xfe9ab3fcu) < 2)
            pMemory = (void*)(intptr_t)operator_new(0x9c, "UI/AssetDiscovery_Data", 0, 0, 0, 0);
        else
            pMemory = (void*)(intptr_t)operator_new(0xb0, "UI/AssetDiscovery_Data", 0, 0, 0, 0);

        if (pMemory != nullptr)
            pData = (cSPAssetData*)CreateAssetData(0);

        cSPAssetData* pOldData = mpAssetData;
        if (pData != pOldData) {
            if (pData != nullptr)
                pData->AddRef();
            mpAssetData = pData;
            if (pOldData != nullptr)
                pOldData->Release();
        }
    }

    mpAssetData->v14();
    if (mpAssetData->IsDiscovered()) {
        uint32_t nMode = GetCurrentGameMode();
        if (nMode != (uint32_t)(intptr_t)&gGameModeSpace) {
            void* pController = Controller_Award(0xbde3bf2fu);
            AwardAchievement(pController, 0xbde3bf2fu);
        }
    }

    if (mpAssetView == nullptr) {
        cSPUIAssetView* pView = nullptr;
        void* pMemory = (void*)(intptr_t)operator_new(0x108, "UI/AssetDiscovery_View", 0, 0, 0, 0);
        if (pMemory != nullptr)
            pView = (cSPUIAssetView*)CreateAssetView();

        cSPUIAssetView* pOldView = mpAssetView;
        if (pView != pOldView) {
            if (pView != nullptr)
                pView->AddRef();
            mpAssetView = pView;
            if (pOldView != nullptr)
                pOldView->Release();
        }
    }

    mpAssetView->Bind(mpParentWin, mpAssetData, 0, 0);
    ResetCardState();
    mpAssetView->v28(0);
}

// ---------------------------------------------------------------------------
// 0x00e2f980  SP::cSPUIAssetDiscoveryManager::ReloadTuning
// ---------------------------------------------------------------------------
// @ 0x00e2f980
void cSPUIAssetDiscoveryManager::ReloadTuning()
{
    void* pPropertyManager = PropertyManager();
    void* pDefinition = nullptr;

    if (QueryDefinition(pPropertyManager, 0x5c770db7u, &pDefinition)) {
        uint32_t nFlags = 0;
        int nValue = 0;

        if (QueryTuningFloat(pDefinition, 0x2b12f9ecu, &mTimeStart))
            nFlags = 1;
        if (QueryTuningFloat(pDefinition, 0xa6f83fb3u, &mTimeScaleBack))
            nFlags = 1;
        if (QueryTuningFloat(pDefinition, 0x907d189du, &mTimeRotate))
            nFlags = 1;
        if (QueryTuningInt(pDefinition, 0xfd338528u, &nValue))
            mCount = nValue;
        if (QueryTuningFloat(pDefinition, 0x56e50a98u, &mTime))
            nFlags = 1;
        if (QueryTuningInt(pDefinition, 0x74cff359u, &nValue))
            mCount = nValue;
        if (QueryTuningInt(pDefinition, 0x7a927f57u, &nValue))
            mCount = nValue;

        mTimeStopMS = (int64_t)(mTimeStart * 1000.0f + 0.5f);
        mTimeStartMS = (int64_t)(mTimeScaleBack * 1000.0f + 0.5f);
        mTimeScaleBackMS = (int64_t)(mTimeRotate * 1000.0f + 0.5f);
        mTimeRotateMS = (int64_t)((float)nValue * 1000.0f + 0.5f);
        mTimeMS = (int64_t)(mTime * 1000.0f + 0.5f);
        (void)nFlags;
    }
}

// ---------------------------------------------------------------------------
// 0x00e2fc40  cSPUIAssetDiscoveryManager::HandleCardMessage
// ---------------------------------------------------------------------------
// @ 0x00e2fc40
int cSPUIAssetDiscoveryManager::HandleCardMessage(int nMessage, int nData, int nFlags)
{
    if (nMessage == 0xf62def) {
        if (nData == 0x5c770db7)
            ReloadTuning();
        return 1;
    }
    if (nMessage != 0x533b6aa4) {
        if (nMessage == 0xd33b6aa2) {
            if (mpSelectedCard != nullptr)
                ((IRefCounted*)mpSelectedCard)->AddRef();
            ++mCount;
        }
        return 0;
    }
    if (mpSelectedCard != nullptr)
        ((IRefCounted*)mpSelectedCard)->AddRef();
    --mCount;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00e2fcb0  cSPUIAssetDiscoveryCard::ApplyFrame
// ---------------------------------------------------------------------------
// @ 0x00e2fcb0
void cSPUIAssetDiscoveryCard::ApplyFrame(int* pData)
{
    if (pData == nullptr)
        return;

    void* pValue = nullptr;
    if (QueryProperty(pData, 0x689fa1bu, &pValue)) {
        if (*(int16_t*)((uint8_t*)pValue + 0x12) == 10)
            mpAssetData = (cSPAssetData*)GetPropertyAsFloat();
    }
    if (QueryProperty(pData, 0x689fa1du, &pValue)) {
        if (*(int16_t*)((uint8_t*)pValue + 0x12) == 1)
            mpTextWindow = (IWindow*)GetPropertyAsKeyArray();
    }

    void* pVariant = nullptr;
    GetPropertyAsVariant(&pVariant, 0x689fa1cu);
    ReleaseCardResource(0);
}

// ---------------------------------------------------------------------------
// 0x00e2fd40  cSPUIAssetDiscoveryManager::ReleaseCurrentCard
// ---------------------------------------------------------------------------
// @ 0x00e2fd40
void cSPUIAssetDiscoveryManager::ReleaseCurrentCard()
{
    cSPUIAssetDiscoveryCard** ppCurrent = mpCardsBegin;
    if (ppCurrent + 1 == mpCardsEnd) {
        if (*ppCurrent != nullptr)
            (*ppCurrent)->Release();
        if (mpCardsCur != nullptr)
            operator_delete__(mpCardsCur);
        mpCardsCap = mpCardsEnd + 1;
        mpCardsEnd = (cSPUIAssetDiscoveryCard**)(intptr_t)*mpCardsCap;
        mpCardsCur = mpCardsEnd;
        mpCardsBegin = mpCardsCur;
    } else {
        mpCardsBegin = ppCurrent + 1;
        if (*ppCurrent != nullptr)
            (*ppCurrent)->Release();
    }
}

// ---------------------------------------------------------------------------
// 0x00e2fda0  cSPUIAssetDiscoveryCard::Clone
// ---------------------------------------------------------------------------
// @ 0x00e2fda0
cSPUIAssetDiscoveryCard* cSPUIAssetDiscoveryCard::Clone()
{
    cSPUIAssetDiscoveryCard* pCopy = (cSPUIAssetDiscoveryCard*)
        (intptr_t)operator_new(0x18, "Simulator", 0, 0, "EASTL/allocator.h", 0xd1);
    if (pCopy != nullptr) {
        pCopy->mpLayout = mpLayout;
        pCopy->mpParentWin = mpParentWin;
        if (mpTextWindow != nullptr)
            mpTextWindow->AddRef();
        pCopy->mpTextWindow = mpTextWindow;
        if (mpAssetData != nullptr)
            mpAssetData->AddRef();
        pCopy->mpAssetData = mpAssetData;
        if (mpAssetView != nullptr)
            mpAssetView->AddRef();
        pCopy->mpAssetView = mpAssetView;
    }
    if (pCopy != nullptr)
        pCopy->mpParentWin = nullptr;
    return pCopy;
}

// ---------------------------------------------------------------------------
// 0x00e2fe10  cSPUIAssetDiscoveryManager::Init
// ---------------------------------------------------------------------------
// @ 0x00e2fe10
void cSPUIAssetDiscoveryManager::Init()
{
    cMessageServer* pServer = (cMessageServer*)MessageServer();
    pServer->v20((cMessageTarget*)this, 0xf62defu);
    pServer = (cMessageServer*)MessageServer();
    pServer->v20((cMessageTarget*)this, 0xd33b6aa2u);
    pServer = (cMessageServer*)MessageServer();
    pServer->v20((cMessageTarget*)this, 0x533b6aa4u);

    ReloadTuning();

    if (mpAnimator == nullptr) {
        void* pMemory = (void*)(intptr_t)operator_new(0x20, "UI/AssetDiscoveryAnimator", 0, 0, 0, 0);
        if (pMemory != nullptr)
            mpAnimator = (cSPUIAnimator*)CreateTimer();
        else
            mpAnimator = nullptr;
    }
}

// ---------------------------------------------------------------------------
// 0x00e2feb0  cSPUIAssetDiscoveryManager::HandleAssetMessage
// ---------------------------------------------------------------------------
// @ 0x00e2feb0
int cSPUIAssetDiscoveryManager::HandleAssetMessage(int nMessage, int nData)
{
    if (nMessage == 0xf62def && nData == 0x689fa1a) {
        int nAssetId = 0;
        cSPUIAssetDiscoveryCard** ppCard = nullptr;
        GetCardTarget(&ppCard);
        cSPUIAssetDiscoveryCard** ppEnd = mpCardsBegin + 0;
        while (ppCard != ppEnd) {
            if (*(int*)ppCard == nAssetId)
                (*ppCard)->ApplyFrame((int*)(ppCard + 1));
            ppCard = (cSPUIAssetDiscoveryCard**)(intptr_t)((void**)ppCard)[5];
            while (ppCard == nullptr)
                ppCard = (cSPUIAssetDiscoveryCard**)(intptr_t)((void**)ppCard)[1];
        }
        return 1;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00e30010  cSPUIAssetDiscoveryManager::PushCard
// ---------------------------------------------------------------------------
// @ 0x00e30010
void cSPUIAssetDiscoveryManager::PushCard(cSPUIAssetDiscoveryCard** ppCard, int nFlags)
{
    cSPUIAssetDiscoveryCard* pCard = (cSPUIAssetDiscoveryCard*)*ppCard;
    if (pCard != nullptr)
        pCard->AddRef();

    if (mpCardsEnd - mpCardsCur <= 1)
        PushCardInternal();

    uint32_t pBlock = (uint32_t)(intptr_t)operator_new(0x100, "Simulator", 0, 0,
                                                       "EASTL/allocator.h", 0xd1);
    *(uint32_t*)(mpCardsCap + 1) = pBlock;
    if (mpCardsCur != nullptr) {
        *mpCardsCur = pCard;
        if (pCard != nullptr)
            pCard->AddRef();
    }

    cSPUIAssetDiscoveryCard** ppBlockStart = mpCardsCap;
    mpCardsCap = ppBlockStart + 1;
    mpCardsEnd = (cSPUIAssetDiscoveryCard**)(intptr_t)*(uint32_t*)(ppBlockStart + 1);
    mpCardsCur = mpCardsEnd;
    mpCardsBegin = mpCardsCur;

    if (pCard != nullptr)
        pCard->Release();
    (void)nFlags;
}

// ---------------------------------------------------------------------------
// 0x00e300f0  cSPUIAssetDiscoveryManager::Shutdown
// ---------------------------------------------------------------------------
// @ 0x00e300f0
void cSPUIAssetDiscoveryManager::Shutdown()
{
    cMessageServer* pServer = (cMessageServer*)MessageServer();
    pServer->v2c((cMessageTarget*)this, 0xf62defu, 0xffffd8f1);
    pServer = (cMessageServer*)MessageServer();
    pServer->v2c((cMessageTarget*)this, 0xd33b6aa2u, 0xffffd8f1);
    pServer = (cMessageServer*)MessageServer();
    pServer->v2c((cMessageTarget*)this, 0x533b6aa4u, 0xffffd8f1);

    if (mpSelectedCard != nullptr) {
        ((IRefCounted*)mpSelectedCard)->Release();
        ResetCardState();
        cSPUIAssetDiscoveryCard* pOldCard = mpSelectedCard;
        if (pOldCard != nullptr) {
            mpSelectedCard = nullptr;
            ((IRefCounted*)pOldCard)->Release();
        }
    }

    while (mpCardsBegin != mpCardsEnd) {
        ResetCardState();
        cSPUIAssetDiscoveryCard** ppCurrent = mpCardsBegin;
        if (ppCurrent + 1 == mpCardsEnd) {
            if (*ppCurrent != nullptr)
                (*ppCurrent)->Release();
            if (mpCardsCur != nullptr)
                operator_delete__(mpCardsCur);
            mpCardsCap = mpCardsEnd + 1;
            mpCardsEnd = (cSPUIAssetDiscoveryCard**)(intptr_t)*mpCardsCap;
            mpCardsCur = mpCardsEnd;
            mpCardsBegin = mpCardsCur;
        } else {
            mpCardsBegin = ppCurrent + 1;
            if (*ppCurrent != nullptr)
                (*ppCurrent)->Release();
        }
    }

    if (mpAnimator != nullptr) {
        mpAnimator->Update();
        mpAnimator = nullptr;
    }
}

// ---------------------------------------------------------------------------
// 0x00e30230  cSPUIAssetDiscoveryManager::Update
// ---------------------------------------------------------------------------
// @ 0x00e30230
void cSPUIAssetDiscoveryManager::Update(uint nMilliseconds)
{
    if (mnPaused >= 1)
        return;

    mnElapsed += nMilliseconds;
    switch (mnAnimationState) {
    case 0:
        if (mpCardsBegin != mpCardsEnd) {
            cSPUIAssetDiscoveryCard* pCard = *mpCardsBegin;
            if (IsCardVisible(pCard)) {
                ResetDiscoveryAnimation();
                SetGlobalProperty(0xb6225e24u, 0x3f800000u);
                void* pTarget = GetCardTarget(mpSelectedCard);
                SetWindowScale(pTarget, 0);

                cSPUIAssetDiscoveryCard* pView = *(cSPUIAssetDiscoveryCard**)(mpSelectedCard + 1);
                if (pView != nullptr) {
                    Rect bounds;
                    bounds.mX = 0.0f;
                    bounds.mY = 0.0f;
                    bounds.mWidth = 0.0f;
                    bounds.mHeight = 0.0f;
                    uint32_t nMode = GetCurrentGameMode();
                    if (nMode == (uint32_t)(intptr_t)&gGameModeSpace)
                        GetTutorialArea(&bounds);
                    else if (nMode == (uint32_t)(intptr_t)&gGameModeTribe)
                        GetTribeArea(&bounds);

                    Rect* pArea = ((IWindow*)pView)->GetArea();
                    float fOffset = pArea->mWidth < bounds.mY ? 0.0f : bounds.mWidth - bounds.mX;
                    SetWindowPosition(pTarget, pArea->mX - fOffset, pArea->mY);
                }

                float fDuration = GetElapsedSeconds(mnSlideInStart, 1, pTarget, 0);
                void* pAnimation = nullptr;
                pAnimation = CreateScaleAnimation(nullptr, pTarget, mnScaleLow, fDuration);
                mpAnimator->AddAnimation(pAnimation, pTarget, 0);
                UpdateWindowState(pTarget);
                ((IRefCounted*)pTarget)->AddRef();
                ReleaseCurrentCard();
                mnElapsed = 0;
                mnAnimationState = 1;
            }
        }
        break;

    case 1:
        if (mnElapsed >= (uint64_t)mnStopHigh) {
            if (mnElapsed != (uint64_t)mnStopHigh || (uint64_t)mnStopLow < mnElapsed) {
                void* pTarget = GetCardTarget(mpSelectedCard);
                mpAnimator->RemoveAnimation(pTarget, -1);
                float fDuration = GetElapsedSeconds(mnSlideOutStart, 1, pTarget, 0);
                void* pAnimation = CreateScaleAnimation(nullptr, pTarget, 0x3f800000, fDuration);
                mpAnimator->AddAnimation(pAnimation, pTarget, 0);
                UpdateWindowState(pTarget);
                mnElapsed = 0;
                mnAnimationState = 2;
            }
        }
        break;

    case 2:
        if (mnElapsed >= (uint64_t)mnScaleHigh) {
            if (mnElapsed != (uint64_t)mnScaleHigh || (uint64_t)mnScaleLow < mnElapsed) {
                void* pTarget = GetCardTarget(mpSelectedCard);
                mpAnimator->RemoveAnimation(pTarget, -1);
                float fDuration = GetElapsedSeconds(mnRotateStart, 1, pTarget, 2);
                void* pAnimation = CreateRotationAnimation(nullptr, pTarget, 0, 0x3f800000, 0,
                                                           gRotationAngle, fDuration);
                mpAnimator->AddAnimation(pAnimation, pTarget, 2);
                UpdateWindowState(pTarget);
                mnElapsed = 0;
                mnAnimationState = 3;
            }
        }
        break;

    case 3:
        if (mnElapsed >= (uint64_t)mnRotateHigh) {
            if (mnElapsed != (uint64_t)mnRotateHigh || (uint64_t)mnRotateLow < mnElapsed) {
                mnElapsed = 0;
                mnAnimationState = 4;
            }
        }
        break;

    case 4:
        if (mnElapsed >= (uint64_t)mnZoomHigh) {
            if (mnElapsed != (uint64_t)mnZoomHigh || (uint64_t)mnZoomLow < mnElapsed) {
                void* pTarget = GetCardTarget(mpSelectedCard);
                mpAnimator->RemoveAnimation(pTarget, -1);
                Rect area;
                GetMainWindowArea(&area);
                float fDuration = GetElapsedSeconds(mnZoomStart, 1, pTarget, 0);
                void* pTimer = CreateTimerInterpolation(nullptr, fDuration);
                void* pAnimation = CreateScaleAnimationFloat(nullptr, pTarget, 0x3d4ccccd, pTimer);
                mpAnimator->AddAnimation(pAnimation, pTarget, 0);
                UpdateWindowState(pTarget);
                ResetAnimationState();
                mnElapsed = 0;
                mnAnimationState = 5;
            }
        }
        break;

    case 5:
        if (mnElapsed >= (uint64_t)mnFinalHigh) {
            if (mnElapsed != (uint64_t)mnFinalHigh || (uint64_t)mnFinalLow < mnElapsed) {
                mnElapsed = 0;
                void* pCard = mpSelectedCard;
                ((IRefCounted*)pCard)->Release();
                ResetCardState();
                cSPUIAssetDiscoveryCard* pOldCard = mpSelectedCard;
                if (pOldCard != nullptr) {
                    mpSelectedCard = nullptr;
                    ((IRefCounted*)pOldCard)->Release();
                }
                mnAnimationState = 0;
            }
        }
        break;
    }

    if (mpSelectedCard != nullptr) {
        cSPUIAssetDiscoveryCard* pCard = mpSelectedCard;
        if (pCard->mpTextWindow != nullptr)
            pCard->mpTextWindow->v2c();
        if (pCard->mpParentWin != nullptr)
            FlushCardAnimations();
    }
    mpAnimator->Update();
}

// ---------------------------------------------------------------------------
// 0x00e30680  cSPUIAssetDiscoveryManager::Reset
// ---------------------------------------------------------------------------
// @ 0x00e30680
void cSPUIAssetDiscoveryManager::Reset()
{
    if (mpSelectedCard != nullptr) {
        ((IRefCounted*)mpSelectedCard)->Release();
        ResetCardState();
        cSPUIAssetDiscoveryCard* pOldCard = mpSelectedCard;
        if (pOldCard != nullptr) {
            mpSelectedCard = nullptr;
            ((IRefCounted*)pOldCard)->Release();
        }
    }

    while (mpCardsBegin != mpCardsEnd) {
        ResetCardState();
        cSPUIAssetDiscoveryCard** ppCurrent = mpCardsBegin;
        if (ppCurrent + 1 == mpCardsEnd) {
            if (*ppCurrent != nullptr)
                (*ppCurrent)->Release();
            if (mpCardsCur != nullptr)
                operator_delete__(mpCardsCur);
            mpCardsCap = mpCardsEnd + 1;
            mpCardsEnd = (cSPUIAssetDiscoveryCard**)(intptr_t)*mpCardsCap;
            mpCardsCur = mpCardsEnd;
            mpCardsBegin = mpCardsCur;
        } else {
            mpCardsBegin = ppCurrent + 1;
            if (*ppCurrent != nullptr)
                (*ppCurrent)->Release();
        }
    }

    mnAnimationState = 0;
}
