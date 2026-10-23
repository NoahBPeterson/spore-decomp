// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00e14a30.
//
// Mission-card UI panel cluster: panel event handling, card layout, card
// initialisation and the mission-card constructor / destructor.

typedef unsigned int size_t;
typedef unsigned int uint32_t;
#define nullptr 0
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uintptr_t32;

class cUICard;
bool CardLessThan(cUICard* pLeft, cUICard* pRight);

namespace EA {
template <class T>
struct RectT {
    T mLeft;
    T mTop;
    T mRight;
    T mBottom;
};
}  // namespace EA

// ---------------------------------------------------------------------------
// Minimal UI object model
// ---------------------------------------------------------------------------

struct IWindow;

// A reference counted object whose vtable starts with AddRef/Release.
struct IRefCounted {
    virtual void AddRef();
    virtual void Release();
};

// Layout object handed out by the UI resource system.
class cSPUILayout {
public:
    virtual void v00();
    virtual void AddRef();
    virtual void Release();

    bool SetVisibility(bool visible);
    bool Init(const wchar_t* pName, uint32_t instanceId, bool bFlag, uint32_t resourceId);
    bool Init(const void* pKey, bool bFlag, uint32_t resourceId);
    IWindow* FindWindowByID(uint32_t windowId, bool bRecursive);

    // +0x00 vftable, rest opaque.
    void* mvUnused04;
};

// Window interface. Only the slots used by this slice are named; the gaps are
// padding so that the slot byte offsets stay meaningful.
struct IWindow {
    virtual void AddRef();                                         // 0x00
    virtual void Release();                                        // 0x04
    virtual void v08();                                            // 0x08
    virtual IWindow* FindChild(uint32_t windowId);                 // 0x0c
    virtual IWindow* CreateChild(int a, uint32_t b, int c, int d, int e);  // 0x10
    virtual void v14();                                            // 0x14
    virtual void v18();                                            // 0x18
    virtual int GetObjectId();                                     // 0x1c
    virtual void v20();                                            // 0x20
    virtual void v24();                                            // 0x24
    virtual void v28();                                            // 0x28
    virtual void v2c();                                            // 0x2c
    virtual void v30();                                            // 0x30
    virtual void* GetExtent();                                     // 0x34
    virtual EA::RectT<float>* GetArea();                           // 0x38
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c(int a, int b);                                 // 0x4c
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void SetPosition(float x, float y);                     // 0x70
    virtual void v74();
    virtual void v78();
    virtual void Show(int show, int immediate);                     // 0x7c
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8c();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9c();
    virtual void vA0();
    virtual int GetValue();                                         // 0xa4
    virtual void vA8();
    virtual void vAc();
    virtual void vB0();
    virtual void vB4();
    virtual void vB8();
    virtual void vBc();
    virtual void vC0();
    virtual void vC4();
    virtual void vC8();
    virtual void vCc();
    virtual void vD0();
    virtual void vD4();
    virtual void vD8();
    virtual void vDc();
    virtual void vE0();
    virtual void vE4();
    virtual void vE8();
    virtual void vEc();
    virtual IWindow* FindWindowByID(uint32_t windowId, int recursive);  // 0xf0
    virtual void vF4();
    virtual void vF8();
    virtual void vFc();
    virtual void SetWinProc(void* pProc);                            // 0x104
};

class cSPUIAnimator {
public:
    cSPUIAnimator();
    void* mvState[7];
};

class MissionCardAnimator : public cSPUIAnimator {
public:
    MissionCardAnimator();
    void* mvExtra[4];
};

namespace UI {
class TextZoomName : public IRefCounted {
public:
    TextZoomName(const wchar_t* pName);
    void Shutdown();
    void Activate(bool bActivate);
    void Deactivate(bool bDeactivate);
    void Init(IWindow* pWindow, uint32_t textId, int a, int b, int c, int d, int e);

    uint8_t mPad08[0x74];
};
}  // namespace UI

// Small intrusive pointer used by the UI: Assign() performs AddRef/Release
// around the pointer swap, exactly like the inlined sequences in the binary.
template <class T>
struct AutoRefCount {
    T* mpObject;

    T* Get() const { return mpObject; }
    operator T*() const { return mpObject; }
};

struct IWinProc;

// ---------------------------------------------------------------------------
// Card / event model
// ---------------------------------------------------------------------------

struct EventMsg {
    void* mpVtbl;         // 0x00
    uint32_t mpad04;      // 0x04
    uint32_t mType;       // 0x08
    uint32_t mSubType;    // 0x0c
    uint32_t mpad10;      // 0x10
    uint32_t mpad14;      // 0x14
    IWindow* mpSource;    // 0x18
};

class cUICard {
public:
    virtual void AddRef();     // 0x00
    virtual void Release();    // 0x04
    virtual void v08();
    virtual cUICard* FindChild(uint32_t windowId);   // 0x0c
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void Expand();     // 0x20
    virtual void Collapse();   // 0x24

    bool Init(bool bVisible);  // 0x00e15060

    uint8_t mPad08[8];                 // 0x08
    uint8_t mbFlag10;                  // 0x10
    uint8_t mbExpanded;                // 0x11
    uint8_t mPad12[2];                 // 0x12
    float mOffsetX;                    // 0x14
    float mOffsetY;                    // 0x18
    AutoRefCount<cSPUILayout> mLayout;         // 0x1c
    AutoRefCount<IWindow> mpMainWin;           // 0x24
    cSPUIAnimator* mpAnimator;                 // 0x28
    AutoRefCount<IWindow> mpDescriptionWin;    // 0x2c
    AutoRefCount<IWindow> mpBackgroundWin;     // 0x30
    AutoRefCount<IWindow> mpClipFrameWin;      // 0x34
    AutoRefCount<IWindow> mpCompletedBackgroundWin;  // 0x38
    AutoRefCount<IWindow> mpMissionIconWin;    // 0x3c
    AutoRefCount<IWindow> mpJournalIconWin;    // 0x40
    uint32_t mPad44;
    EA::RectT<float> mIconArea;                // 0x48
    EA::RectT<float> mBackgroundInitialArea;   // 0x58
    EA::RectT<float> mClipFrameInitialArea;    // 0x68
    EA::RectT<float> mCompletedBackgroundInitialArea;  // 0x78
    EA::RectT<float> mDescriptionInitialArea;  // 0x88
};

// One entry of the card vector.
typedef AutoRefCount<cUICard> CardRef;

// ---------------------------------------------------------------------------
// Panel
// ---------------------------------------------------------------------------

struct cPanelConfig {
    const wchar_t* mpName;   // 0x00
};

class cUIMissionCardPanel {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void Expand();     // 0x20
    virtual void Collapse();   // 0x24

    bool OnEvent(int bUnused, EventMsg* pMsg);            // 0x00e14a30
    void UpdateCardPositions();                           // 0x00e14b70
    void SetCardsVisibility(bool bVisible);               // 0x00e14c10
    cSPUILayout* GetPanelLayout();                        // 0x00e14c70
    void SetPanelArea(EA::RectT<float> area);             // 0x00e14d00
    static void InsertionSortSubrange(CardRef* pFirst, CardRef* pLast);   // 0x00e14d90
    static void InsertionSort(CardRef* pFirst, CardRef* pLast);           // 0x00e14e60
    void UpdateProgressWindows();                         // 0x00e154d0
    void UpdateScenarioWindows();                         // 0x00e15620
    void ExpandMissionCard(int missionId);                // 0x00e15b90
    void ShowAllCards();                                  // 0x00e15b70

    // 0x28: vector of cards.
    CardRef* mpCardsBegin;
    CardRef* mpCardsEnd;
    CardRef* mpCardsCapacity;
    void* mPad34;
    void* mPad38;
    AutoRefCount<cSPUILayout> mPanelBackdrop;   // 0x3c
    void* mpMsgHandler;                         // 0x40
    int mHandlerOwner;                          // 0x44
    int mHandlerId;                             // 0x48
    int mHandlerCount;                          // 0x4c
    int mHandlerExtra;                          // 0x50
    AutoRefCount<cSPUILayout> mPanelLayout;     // 0x54
    float mCardSpacing;                         // 0x58
    float mCardStride;                          // 0x5c
    float mCardStartY;                          // 0x60
    uint8_t mPad64[0x1c];                       // 0x64
    AutoRefCount<IWindow> mpMainWin;             // 0x80
    uint8_t mPad84[0x70];                       // 0x84
    UI::TextZoomName* mpTextZoom;               // 0xf4
    cUIMissionCardPanel();
    ~cUIMissionCardPanel();
};

class cUICardMissionCard : public cUICard {
public:
    virtual void ExpandCard(bool bExpand);   // 0x28
    bool InitCard(bool bVisible);   // 0x00e15780
    ~cUICardMissionCard();          // 0x00e15910

    UI::TextZoomName* mpTextZoom;   // 0x98
    int mMissionId;                 // 0x9c
    float mCardHeight;              // 0xa0
    uint8_t mPadA0[0x54];
};

// ---------------------------------------------------------------------------
// External services
// ---------------------------------------------------------------------------

enum eGameMode {
    eGameModeClg = 0x1654c00,
    eGameModeCrg = 0x1654c01,
    eGameModeTrg = 0x1654c02,
    eGameModeCvg = 0x1654c04,
    eGameModeSpg = 0x1654c05,
    eGameModeScenario = 0x1654c10,
};

uint32_t GetCurrentGameMode();
int GetRecorderState();
void* MessageServer();
void* PropertyManager();
void* FindGameData();

struct cScenarioProgressBar;
class cGameData {
public:
    uint8_t mPad00[0x78];
    cScenarioProgressBar* mpProgressBar;   // 0x78
    uint8_t mPad7c[0x54];
    int mModeState;                        // 0xd0
};

struct Property {
    virtual void p00();
    virtual void p04();
    virtual void p08();
    virtual void p0c();
    virtual void p10();
    virtual void p14();
    virtual void p18();
    virtual void p1c();
    virtual void p20();
    virtual bool GetPropertyFrom(uint32_t propertyId, Property** ppProperty);  // 0x24
    uint8_t mPad04[0x0e];
    uint16_t mType;             // 0x12
};

struct IPropertyContainer {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t propertyId, Property** ppProperty);   // 0x24
};

float GetPropertyAsFloat(Property* pProperty);
int GetPropertyAsInt(Property* pProperty);

class cScenarioProgressBar {
public:
    int GetCount();
    uint8_t GetByte(int index);
    uint8_t GetKind(int index);
    float GetProgressF();
};

void* operator new(size_t size, const char* pSource, int a, int b, int c, int d);
void operator delete(void* p);

// ---------------------------------------------------------------------------
// 0x00e14a30  cUIMissionCardPanel::OnEvent
// ---------------------------------------------------------------------------
// @ 0x00e14a30
bool cUIMissionCardPanel::OnEvent(int bUnused, EventMsg* pMsg)
{
    uint32_t type = pMsg->mType;

    if (type < 0x1d) {
        if (type == 0x1c) {
            if (pMsg->mSubType == 1 && pMsg->mpSource->GetObjectId() == 0x5397388) {
                mpTextZoom->Deactivate(true);
                return false;
            }
            return false;
        }
        if (type == 0xc) {
            Collapse();
            return false;
        }
        if (type == 0x1b && pMsg->mSubType == 1 &&
            pMsg->mpSource->GetObjectId() == 0x5397388) {
            mpTextZoom->Activate(true);
            return false;
        }
        return false;
    }

    if (type != 0x287259f6)
        return false;

    if (pMsg->mSubType == 0x5235138) {
        // Panel collapsed: let the owning panel handle it.
        cUIMissionCardPanel* pOwner = (cUIMissionCardPanel*)-0xc;
        (void)pOwner;
        return true;
    }
    if (pMsg->mSubType == 0x5235aa8) {
        GetRecorderState();
        mCardSpacing = mCardSpacing;
        Expand();
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00e14b30  cUIMissionCardPanel::~cUIMissionCardPanel
// ---------------------------------------------------------------------------
// @ 0x00e14b30
cUIMissionCardPanel::~cUIMissionCardPanel()
{
    UI::TextZoomName* pTextZoom = mpTextZoom;
    if (pTextZoom != nullptr) {
        pTextZoom->Shutdown();
        if (mpTextZoom != nullptr) {
            mpTextZoom = nullptr;
            pTextZoom->Release();
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00e14b70  cUIMissionCardPanel::UpdateCardPositions
// ---------------------------------------------------------------------------
// @ 0x00e14b70
void cUIMissionCardPanel::UpdateCardPositions()
{
    int count = (int)(mpCardsEnd - mpCardsBegin);
    float y = mCardStartY;
    float x = mCardStride;

    for (int i = 0; i < count; ++i) {
        cUICard* pCard = mpCardsBegin[i].mpObject;
        if (pCard == nullptr)
            continue;

        IWindow* pMain = pCard->mpMainWin.mpObject;
        pCard->mOffsetY = x;
        pCard->mLayout.mpObject = (cSPUILayout*)&y;
        pMain->SetPosition(x, y);

        void* pExtent = pCard->mpCompletedBackgroundWin.mpObject->GetExtent();
        float* pFloats = (float*)pExtent;
        y = (pFloats[3] - pFloats[1]) + mCardSpacing + y;
    }
}

// ---------------------------------------------------------------------------
// 0x00e14c10  cUIMissionCardPanel::SetCardsVisibility
// ---------------------------------------------------------------------------
// @ 0x00e14c10
void cUIMissionCardPanel::SetCardsVisibility(bool bVisible)
{
    int count = (int)(mpCardsEnd - mpCardsBegin);
    for (int i = 0; i < count; ++i) {
        cUICard* pCard = mpCardsBegin[i].mpObject;
        if (pCard == nullptr || pCard->mLayout.mpObject == nullptr)
            continue;
        pCard->mLayout.mpObject->SetVisibility(bVisible);
        if (pCard->mpMainWin.mpObject != nullptr)
            pCard->mpMainWin.mpObject->Show(1, bVisible);
    }
}

// ---------------------------------------------------------------------------
// 0x00e14c70  cUIMissionCardPanel::GetPanelLayout
// ---------------------------------------------------------------------------
// @ 0x00e14c70
cSPUILayout* cUIMissionCardPanel::GetPanelLayout()
{
    if (mPanelLayout.mpObject == nullptr) {
        static const uint32_t sLayoutKey[3] = {0x2ac364a7, 0x0510a95b, 0x40464100};
        cSPUILayout* pOld = mPanelLayout.mpObject;
        cSPUILayout* pNew = new ("Simulator", 0, 0, 0, 0) cSPUILayout();
        if (pNew != pOld) {
            if (pNew != nullptr)
                pNew->AddRef();
            mPanelLayout.mpObject = pNew;
            if (pOld != nullptr)
                pOld->Release();
        }
        mPanelLayout.mpObject->Init(sLayoutKey, false, 0x5b598fa);
    }
    return mPanelLayout.mpObject;
}

// ---------------------------------------------------------------------------
// 0x00e14d00  cUIMissionCardPanel::SetPanelArea
// ---------------------------------------------------------------------------
// @ 0x00e14d00
void cUIMissionCardPanel::SetPanelArea(EA::RectT<float> area)
{
    if (mPanelBackdrop.mpObject == nullptr) {
        cSPUILayout* pOld = mPanelBackdrop.mpObject;
        cSPUILayout* pNew = new ("Simulator", 0, 0, 0, 0) cSPUILayout();
        if (pNew != pOld) {
            if (pNew != nullptr)
                pNew->AddRef();
            mPanelBackdrop.mpObject = pNew;
            if (pOld != nullptr)
                pOld->Release();
        }
        mPanelBackdrop.mpObject->Init(&area.mLeft, false, 0);
    }
    mPanelBackdrop.mpObject->SetVisibility(true);
}

// ---------------------------------------------------------------------------
// 0x00e14d90  cUIMissionCardPanel::InsertionSortSubrange
// ---------------------------------------------------------------------------
// @ 0x00e14d90
void cUIMissionCardPanel::InsertionSortSubrange(CardRef* pFirst, CardRef* pLast)
{
    if (pFirst == pLast)
        return;

    for (CardRef* pCur = pFirst + 1; pCur != pLast; ++pCur) {
        cUICard* pValue = pCur->mpObject;
        if (pValue != nullptr)
            pValue->AddRef();

        CardRef* pPos = pCur;
        while (pPos != pFirst && CardLessThan(pValue, (pPos - 1)->mpObject)) {
            cUICard* pPrev = (pPos - 1)->mpObject;
            cUICard* pOld = pPos->mpObject;
            if (pPrev != pOld) {
                if (pPrev != nullptr)
                    pPrev->AddRef();
                pPos->mpObject = pPrev;
                if (pOld != nullptr)
                    pOld->Release();
            }
            --pPos;
        }

        cUICard* pOld = pPos->mpObject;
        if (pValue != pOld) {
            if (pValue != nullptr)
                pValue->AddRef();
            pPos->mpObject = pValue;
            if (pOld != nullptr)
                pOld->Release();
        }
        if (pValue != nullptr)
            pValue->Release();
    }
}

// ---------------------------------------------------------------------------
// 0x00e14e60  cUIMissionCardPanel::InsertionSort
// ---------------------------------------------------------------------------
// @ 0x00e14e60
void cUIMissionCardPanel::InsertionSort(CardRef* pFirst, CardRef* pLast)
{
    for (; pFirst != pLast; ++pFirst) {
        cUICard* pValue = pFirst->mpObject;
        if (pValue != nullptr)
            pValue->AddRef();

        CardRef* pPos = pFirst;
        while (CardLessThan(pValue, (pPos - 1)->mpObject)) {
            cUICard* pPrev = (pPos - 1)->mpObject;
            cUICard* pOld = pPos->mpObject;
            if (pPrev != pOld) {
                if (pPrev != nullptr)
                    pPrev->AddRef();
                pPos->mpObject = pPrev;
                if (pOld != nullptr)
                    pOld->Release();
            }
            --pPos;
        }

        cUICard* pOld = pPos->mpObject;
        if (pValue != pOld) {
            if (pValue != nullptr)
                pValue->AddRef();
            pPos->mpObject = pValue;
            if (pOld != nullptr)
                pOld->Release();
        }
        if (pValue != nullptr)
            pValue->Release();
    }
}

// ---------------------------------------------------------------------------
// 0x00e15060  cUICard::Init
// ---------------------------------------------------------------------------
// @ 0x00e15060
bool cUICard::Init(bool bVisible)
{
    cSPUILayout* pOldLayout = mLayout.mpObject;
    cSPUILayout* pNewLayout = new ("Simulator", 0, 0, 0, 0) cSPUILayout();
    if (pNewLayout != pOldLayout) {
        if (pNewLayout != nullptr)
            pNewLayout->AddRef();
        mLayout.mpObject = pNewLayout;
        if (pOldLayout != nullptr)
            pOldLayout->Release();
    }
    if (mLayout.mpObject == nullptr)
        return false;

    const wchar_t* pLayoutName = nullptr;
    uint32_t gameMode = GetCurrentGameMode();
    switch (gameMode) {
    case eGameModeClg:
        pLayoutName = L"ClgMissionCard";
        break;
    case eGameModeCrg:
        pLayoutName = L"CrgMissionCard";
        break;
    case eGameModeTrg:
        pLayoutName = L"TrgMissionCard";
        break;
    case eGameModeCvg:
        pLayoutName = L"CvgMissionCard";
        break;
    case eGameModeSpg:
        pLayoutName = L"SpgMissionCard";
        break;
    case eGameModeScenario:
        pLayoutName = L"ScenarioMissionCard";
        break;
    default:
        break;
    }
    if (pLayoutName != nullptr)
        mLayout.mpObject->Init(pLayoutName, 1, true, 0xec2fd2c3);

    IWindow* pOldMain = mpMainWin.mpObject;
    IWindow* pNewMain = mLayout.mpObject->FindWindowByID(0x55ebc68, true);
    if (pNewMain != pOldMain) {
        if (pNewMain != nullptr)
            pNewMain->AddRef();
        mpMainWin.mpObject = pNewMain;
        if (pOldMain != nullptr)
            pOldMain->Release();
    }
    if (mpMainWin.mpObject == nullptr)
        return false;

    mLayout.mpObject->SetVisibility(bVisible);
    mpMainWin.mpObject->Show(1, bVisible ? 1 : 0);

    if (mpAnimator == nullptr)
        mpAnimator = new ("UI/MissionCardAnimator", 0, 0, 0, 0) MissionCardAnimator();

    mpMainWin.mpObject->SetWinProc(this);
    mpMainWin.mpObject->SetPosition(mOffsetY, mOffsetX);
    mbExpanded = true;

    IWindow* pDesc = mpMainWin.mpObject->FindWindowByID(0x65b94b7, 1);
    if (pDesc != mpDescriptionWin.mpObject) {
        if (pDesc != nullptr)
            pDesc->AddRef();
        IWindow* pOld = mpDescriptionWin.mpObject;
        mpDescriptionWin.mpObject = pDesc;
        if (pOld != nullptr)
            pOld->Release();
    }

    IWindow* pBg = mpMainWin.mpObject->FindWindowByID(0x5235140, 1);
    if (pBg != mpBackgroundWin.mpObject) {
        if (pBg != nullptr)
            pBg->AddRef();
        IWindow* pOld = mpBackgroundWin.mpObject;
        mpBackgroundWin.mpObject = pBg;
        if (pOld != nullptr)
            pOld->Release();
    }

    IWindow* pClip = mpMainWin.mpObject->FindWindowByID(0x74cb0c14, 1);
    if (pClip != mpClipFrameWin.mpObject) {
        if (pClip != nullptr)
            pClip->AddRef();
        IWindow* pOld = mpClipFrameWin.mpObject;
        mpClipFrameWin.mpObject = pClip;
        if (pOld != nullptr)
            pOld->Release();
    }

    IWindow* pCompleted = mpMainWin.mpObject->FindWindowByID(0x54bf5692, 1);
    if (pCompleted != mpCompletedBackgroundWin.mpObject) {
        if (pCompleted != nullptr)
            pCompleted->AddRef();
        IWindow* pOld = mpCompletedBackgroundWin.mpObject;
        mpCompletedBackgroundWin.mpObject = pCompleted;
        if (pOld != nullptr)
            pOld->Release();
    }

    IWindow* pIcon = mpMainWin.mpObject->FindWindowByID(0x74bf56ae, 1);
    if (pIcon != mpMissionIconWin.mpObject) {
        if (pIcon != nullptr)
            pIcon->AddRef();
        IWindow* pOld = mpMissionIconWin.mpObject;
        mpMissionIconWin.mpObject = pIcon;
        if (pOld != nullptr)
            pOld->Release();
    }

    IWindow* pJournal = mpMainWin.mpObject->FindWindowByID(0xd5a34260, 1);
    if (pJournal != mpJournalIconWin.mpObject) {
        if (pJournal != nullptr)
            pJournal->AddRef();
        IWindow* pOld = mpJournalIconWin.mpObject;
        mpJournalIconWin.mpObject = pJournal;
        if (pOld != nullptr)
            pOld->Release();
    }

    if (mpBackgroundWin.mpObject != nullptr && mpCompletedBackgroundWin.mpObject != nullptr &&
        mpMissionIconWin.mpObject != nullptr && mpJournalIconWin.mpObject != nullptr) {
        mBackgroundInitialArea = *mpBackgroundWin.mpObject->GetArea();
        mClipFrameInitialArea = *mpCompletedBackgroundWin.mpObject->GetArea();
        mCompletedBackgroundInitialArea = *mpMissionIconWin.mpObject->GetArea();
        mDescriptionInitialArea = *mpJournalIconWin.mpObject->GetArea();
    }

    if (mpDescriptionWin.mpObject != nullptr) {
        EA::RectT<float>* pRect = mpDescriptionWin.mpObject->GetArea();
        mIconArea.mLeft = pRect->mLeft;
        mIconArea.mTop = pRect->mTop;
        mIconArea.mRight = pRect->mRight;
        mIconArea.mBottom = pRect->mBottom;
    }

    return true;
}

// ---------------------------------------------------------------------------
// 0x00e154d0  cUIMissionCardPanel::UpdateProgressWindows
// ---------------------------------------------------------------------------
// @ 0x00e154d0
void cUIMissionCardPanel::UpdateProgressWindows()
{
    IWindow* pMain = mpMainWin.mpObject;
    IWindow* pWin = pMain->FindWindowByID(0x7a15028, 1);
    pWin->Show(1, 0);
    pWin = pMain->FindWindowByID(0x7a15027, 1);
    pWin->Show(1, 0);
    pWin = pMain->FindWindowByID(0x7a15027, 1);
    pWin->Show(1, 1);

    int value = pMain->FindWindowByID(0x792f6d1, 1)->GetValue();

    cGameData* pGameData = (cGameData*)FindGameData();
    if (!mCardStartY)
        return;

    int count = pGameData->mpProgressBar->GetCount();
    if (count > 0) {
        int id = 0x792dcc5;
        for (int i = 0; i < count; ++i) {
            pMain->FindWindowByID(id + 0x41, 1)->Show(1, 0);
            IWindow* pRow = pMain->FindWindowByID(id, 1);
            pRow->Show(2, 0);
            pRow->FindChild(0x8ed27e7a)->v4c(1, value);
            pMain->FindWindowByID(id + 0x101b8b, 1)->Show(1, 1);
            ++id;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00e15620  cUIMissionCardPanel::UpdateScenarioWindows
// ---------------------------------------------------------------------------
// @ 0x00e15620
void cUIMissionCardPanel::UpdateScenarioWindows()
{
    IWindow* pMain = mpMainWin.mpObject;
    pMain->FindWindowByID(0x7a15028, 1)->Show(1, 0);
    pMain->FindWindowByID(0x7a15027, 1)->Show(1, 0);
    pMain->FindWindowByID(0x7a15028, 1)->Show(1, 1);

    cGameData* pGameData = (cGameData*)FindGameData();
    bool bShowAll = (pGameData->mModeState == 0);
    cScenarioProgressBar* pProgress = pGameData->mpProgressBar;
    int count = pProgress->GetCount();

    for (int i = 0; i < count; ++i) {
        if (pProgress->GetByte(i) == 0 && !bShowAll)
            continue;
        if (pProgress->GetKind(i) != 0)
            continue;
        pMain->FindWindowByID(0x792dd06 + i, 1)->Show(1, 0);
        pMain->FindWindowByID(0x7a286d0 + i, 1)->Show(1, 1);
    }

    if (pProgress->GetProgressF() <= 0.0f) {
        IWindow* pBar = pMain->FindWindowByID(0x754f66e, 1);
        if (pBar != nullptr)
            pBar = pBar->FindChild(0xf15f4bd);
        pBar->v28();
    }
}

// ---------------------------------------------------------------------------
// 0x00e15780  cUICardMissionCard::InitCard
// ---------------------------------------------------------------------------
// @ 0x00e15780
bool cUICardMissionCard::InitCard(bool bVisible)
{
    if (!Init(bVisible))
        return false;

    mCardHeight = 0.0f;
    mpTextZoom = nullptr;

    void* pExtent = mpMainWin.mpObject->FindWindowByID(0x792dcc5, 1)->GetExtent();
    float* pFloats = (float*)pExtent;
    mCardHeight = pFloats[3] - pFloats[1];

    cGameData* pGameData = (cGameData*)FindGameData();
    if (pGameData->mModeState != 0) {
        void* pPos = mpMainWin.mpObject->FindWindowByID(0x796d0f0, 1)->GetExtent();
        float* pP = (float*)pPos;
        mOffsetY = -pP[0];
        mOffsetX = -pP[1];
        mpMainWin.mpObject->SetPosition(mOffsetY, mOffsetX);
    }

    UI::TextZoomName* pOldZoom = mpTextZoom;
    UI::TextZoomName* pNewZoom = new ("UI/cSPUITextZoom", 0, 0, 0, 0) UI::TextZoomName(nullptr);
    if (pNewZoom != pOldZoom) {
        if (pNewZoom != nullptr)
            pNewZoom->AddRef();
        mpTextZoom = pNewZoom;
        if (pOldZoom != nullptr)
            pOldZoom->Release();
    }

    IWindow* pText = mpMainWin.mpObject->FindWindowByID(0x52350c8, 1);
    IWindow* pTextCtrl = nullptr;
    if (pText != nullptr)
        pTextCtrl = pText->FindChild(0xf15f4bd);

    IWindow* pChild = mpMainWin.mpObject->CreateChild(0, 0, 0, 0, 0);
    mpTextZoom->Init(pTextCtrl, (uint32_t)(uintptr_t32)pChild, 0, 0, 0, 0, 0);
    return true;
}

// ---------------------------------------------------------------------------
// 0x00e15910  cUICardMissionCard::~cUICardMissionCard
// ---------------------------------------------------------------------------
// @ 0x00e15910
cUICardMissionCard::~cUICardMissionCard()
{
    if (mpTextZoom != nullptr)
        mpTextZoom->Release();
}

// ---------------------------------------------------------------------------
// 0x00e15a10  cUIMissionCardPanel::cUIMissionCardPanel
// ---------------------------------------------------------------------------
// @ 0x00e15a10
cUIMissionCardPanel::cUIMissionCardPanel()
{
    mCardSpacing = 0.0f;
    mCardStride = 0.0f;
    mCardStartY = 0.0f;

    IPropertyContainer* pProperties = (IPropertyContainer*)PropertyManager();
    Property* pRoot = nullptr;
    if (pProperties != nullptr && pProperties->GetProperty(0x5c770db7, &pRoot) &&
        pRoot != nullptr) {
        Property* pValue = nullptr;
        if (pRoot->GetPropertyFrom(0xedf3b85e, &pValue) && pValue != nullptr &&
            pValue->mType == 0xd) {
            mCardSpacing = GetPropertyAsFloat(pValue);
        }
        pValue = nullptr;
        if (pRoot->GetPropertyFrom(0x59d87305, &pValue) && pValue != nullptr &&
            pValue->mType == 0xd) {
            mCardStartY = GetPropertyAsFloat(pValue);
        }
        pValue = nullptr;
        if (pRoot->GetPropertyFrom(0x296a0412, &pValue) && pValue != nullptr &&
            pValue->mType == 0xd) {
            mCardStride = GetPropertyAsFloat(pValue);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00e15b70  cUIMissionCardPanel::ShowAllCards
// ---------------------------------------------------------------------------
// @ 0x00e15b70
bool IsJournalOpen();

void cUIMissionCardPanel::ShowAllCards()
{
    if (!IsJournalOpen())
        SetCardsVisibility(true);
}

// ---------------------------------------------------------------------------
// 0x00e15b90  cUIMissionCardPanel::ExpandMissionCard
// ---------------------------------------------------------------------------
// @ 0x00e15b90
void cUIMissionCardPanel::ExpandMissionCard(int missionId)
{
    int count = (int)(mpCardsEnd - mpCardsBegin);
    for (int i = 0; i < count; ++i) {
        cUICard* pCard = mpCardsBegin[i].mpObject;
        if (pCard == nullptr)
            continue;
        cUICardMissionCard* pTarget = (cUICardMissionCard*)pCard->FindChild(0x334c6eec);
        if (pTarget != nullptr && pTarget->mMissionId == missionId) {
            pTarget->ExpandCard(true);
            return;
        }
    }
}
