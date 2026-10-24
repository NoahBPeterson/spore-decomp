// s00e06220 -- the civilization global-UI panel and the loyalty meter it shows.
//
//  0x00e06220  cSPUIGlobalUICiv::Update
//  0x00e063d0  cSPUIGlobalUICiv::SetCommScreenVisibility
//  0x00e064f0  cSPUIGlobalUICiv::AssignCommRelPanel
//  0x00e06560  cSPUIGlobalUICiv::HandleMessage
//  0x00e065c0  cSPUIGlobalUICiv::InitCommRelPanels
//  0x00e06630  cSPUIGlobalUICiv::AssignFreeCommRelPanel
//  0x00e066a0  cSPUILoyaltyMeter::AsInterface
//  0x00e066d0  cSPUIMeter::SetStart
//  0x00e066e0  cSPUIMeter::SetTrackedObject
//  0x00e06710  cSPUILoyaltyMeter::SetModel
//  0x00e06730  cSPUILoyaltyMeter::SetRange
//  0x00e06790  cSPUIMeter::cSPUIMeter
//  0x00e06870  cSPUIMeter::~cSPUIMeter
//  0x00e068e0  cSPUIMeter::Update
//  0x00e06940  cSPUIMeter::Shutdown
//  0x00e06970  cSPUIMeter::IsVisible
//  0x00e06990  cSPUIMeter::UpdateFromSource
//  0x00e06a10  cSPUILoyaltyMeter::cSPUILoyaltyMeter
//  0x00e06ac0  cSPUILoyaltyMeter::~cSPUILoyaltyMeter
//  0x00e06b20  cSPUILoyaltyMeter::Update
//  0x00e06c50  cSPUIMeter::SetLink
//  0x00e06ca0  cSPUIMeter::SetLinkB
//  0x00e06cf0  cSPUIMeter::SetSource
//  0x00e06d50  cSPUILoyaltyMeter::PullToFront
#include "types.h"

#define nullptr 0

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

class cCivilization;
class cSPUIMeter;
class cSPUILoyaltyMeter;

// ---------------------------------------------------------------------------
// window and link interfaces (the vtable slots the game code calls)
// ---------------------------------------------------------------------------

// the object the meter is wired to (a link / data source)
struct ILink {
    virtual void AddRef();                       // +0x00
    virtual void Release();                      // +0x04
    virtual void S08();                          // +0x08
    virtual void* GetObject(uint32_t nKey);      // +0x0c
    PV16 PV8 PV2 PV                              // 0x10 .. 0x78
    virtual bool GetRange(uint8_t nType, float* pOut);   // +0x7c
    PV8 PV4 PV2 PV                               // 0x80 .. 0xb8
    virtual void AddRef2();                      // +0xbc
    virtual void Release2();                     // +0xc0

    int32_t GetValue();                          // 0x00b8de30
};

// the top-level windows of the civilization screen
struct IWindow {
    virtual void AddRef();                       // +0x00
    virtual void S04();                          // +0x04
    virtual void Release();                      // +0x08
    virtual struct ISubWindow* GetSubWindow(uint32_t nKey);   // +0x0c
    virtual IWindow* GetDecorator();             // +0x10
    PV2                                          // 0x14, 0x18
    virtual void Select();                       // +0x1c
    virtual void S20();                          // +0x20
    virtual void S24();                          // +0x24
    virtual bool IsVisible();                    // +0x28
    PV2                                          // 0x2c, 0x30
    virtual float* GetArea();                    // +0x34
    PV8 PV2 PV                                   // 0x38 .. 0x60
    virtual void SetProgress(float fValue, float fRange);   // +0x64
    PV4 PV                                       // 0x68 .. 0x78
    virtual void SetState(int32_t nState, bool bOn);      // +0x7c
    PV4                                          // 0x80 .. 0x8c
    virtual void Refresh();                      // +0x90
    PV16 PV4 PV                                  // 0x94 .. 0xe4
    virtual void BringToFront(IWindow* pWindow); // +0xe8
    virtual void AttachChild(IWindow* pWindow);  // +0xec
    virtual IWindow* CreateChild(void* pOwner, int32_t nFlags);   // +0xf0
    PV4                                          // 0xf4 .. 0x100
    virtual void AttachOwner(cSPUIMeter* pOwner);   // +0x104
};

// the child windows inside a panel
struct ISubWindow {
    PV16 PV8 PV2 PV                              // 0x00 .. 0x24
    virtual void SetState(int32_t nState, bool bOn);      // +0x28
};

// ---------------------------------------------------------------------------
// the concrete layout wrapper the meter keeps
// ---------------------------------------------------------------------------

class cSPUILayout {
public:
    bool Init(const wchar_t* pName, uint32_t nID, bool bDeep, uint32_t nFlags);   // 0x00812160
    IWindow* FindWindowByID(uint32_t nID, bool bDeep);          // 0x008105b0
    void Shutdown(uint32_t nFlags);                             // 0x00811ad0
    bool IsVisible();                                           // 0x00810070

    IWindow* m_pRoot;                            // +0x00
};

cSPUILayout* __cdecl CreateLayout(uint32_t nSize, const char* pName, int32_t a, int32_t b,
                                  int32_t c, int32_t d);    // 0x00810000

// ---------------------------------------------------------------------------
// civilization and noun manager
// ---------------------------------------------------------------------------

class cCivilization {
public:
    virtual void AddRef();                       // +0x00
    virtual void Release();                      // +0x04

    uint32_t m_nFlags04;                         // +0x04
    uint8_t m_pad008[0x82];                      // +0x08
    bool m_bNotPlayable;                         // +0x8a
    bool m_bVisible;                             // +0x8b
    uint8_t m_pad08c[0x20c];                     // +0x8c
    int32_t m_nStage;                            // +0x298
    int32_t m_nPanelIndex;                       // +0x29c

    int32_t GetTurn();                           // 0x00bf01e0
};

class cCivilizationList {
public:
    cCivilization** m_pBegin;                    // +0x00
    cCivilization** m_pEnd;                      // +0x04
    cCivilization** m_pCapacity;                 // +0x08
};

class cGameNounManager {
public:
    cCivilization* GetPlayerCivilization();      // 0x00b25fb0
    cCivilizationList* GetCivilizationList();    // 0x00b25ca0
};

cGameNounManager* __cdecl NounManager();         // 0x00b3d300

class cCommManager {
public:
    bool IsActive();                             // 0x00ae9390
};

cCommManager* __cdecl CommManager();             // 0x00b3d4a0

// the game object a link hands out
class cLinkObject {
public:
    bool IsAvailable();                          // 0x00c88e30
};

// the index map keyed by civilization
class cCivIndexMap {
public:
    struct Node {
        void* m_pLeft;                           // +0x00
        void* m_pRight;                          // +0x04
        void* m_pParent;                         // +0x08
        uint32_t m_nColor;                       // +0x0c
        uint32_t m_nKey;                         // +0x10
        uint32_t m_nValue;                       // +0x14
    };

    Node*& Find(cCivilization* const& pCiv);                // 0x00e5c780
    uint32_t& GetCounter(cCivilization* const& pCiv);       // 0x00badea0

    void* m_pAllocator;                          // +0x00
    Node m_stHeader;                             // +0x04
    Node* m_pRoot;                               // +0x0c
    uint32_t m_nSize;                            // +0x10
};

// ---------------------------------------------------------------------------
// the civilization panel
// ---------------------------------------------------------------------------

// one comm-rel panel slot
struct cCommRelPanel {
    cCivilization* m_pData;                      // +0x00
    bool m_bActive;                              // +0x04
    bool m_bShown;                               // +0x05
    uint8_t m_pad006[2];                         // +0x06
    cCivilization* m_pCiv;                       // +0x08
};

class cSPUIGlobalUI {
public:
    IWindow* FindWindowByID(uint32_t nID);               // 0x00e012b0
    void HandleMessage(uint32_t nMessage, void* pData);  // 0x00e03f80

    uint8_t m_pad000[0x88];
};

class cSPUIGlobalUICiv : public cSPUIGlobalUI {
public:
    void Update(int32_t nDelta);                                       // 0x00e06220
    void SetCommScreenVisibility(cCivilization* pCiv, bool bOn);       // 0x00e063d0
    void AssignCommRelPanel(int32_t nIndex, cCivilization* pCiv);      // 0x00e064f0
    void HandleMessage(uint32_t nMessage, void* pData);                // 0x00e06560
    void InitCommRelPanels();                                          // 0x00e065c0
    void AssignFreeCommRelPanel(cCivilization* pCiv);                  // 0x00e06630

    void SetMinimapStateFromButton(int32_t nState);                    // 0x00e04560
    void UpdateCommRelPanel(int32_t nDelta, int32_t nIndex);           // 0x00e04d10
    void ActivateCommRelPanel(int32_t nIndex);                         // 0x00e04770
    void BindCommRelData(uint32_t nKey, void** ppData, int32_t nIndex);   // 0x00e060c0
    void RefreshCommRelPanels();                                       // 0x00e04aa0
    void SetCommRelProgress(uint32_t a, uint32_t b, uint32_t c, int32_t nValue);  // 0x00e05ab0

    bool m_bFlag88;                              // +0x88
    bool m_bCommScreenActive;                    // +0x89
    uint8_t m_pad08a[2];                         // +0x8a
    cCommRelPanel m_commRelPanels[4];            // +0x8c
    float m_fCommRelTimer;                       // +0xbc
    uint8_t m_pad0c0[8];                         // +0xc0
    void* m_apCommRelData[4];                    // +0xc8
    uint32_t m_nFlags0d8;                        // +0xd8
    cCivIndexMap mCivToIndex;                    // +0xdc
};

int32_t __cdecl GetCurrentTurn();                              // 0x00922bf0
int32_t __cdecl GetLastTurn();                                 // 0x00befd30
void __stdcall FUN_00e05930(int32_t nMode);                     // 0x00e05930
int32_t __cdecl FUN_00b8de30(void* pObject);                   // 0x00b8de30

// the message payload that carries a civilization
struct cCivMessage {
    uint8_t m_pad000[8];
    int32_t m_nType;                             // +0x08
    uint8_t m_pad00c[4];                         // +0x0c
    cCivilization* m_pCiv;                       // +0x10
};

static const uint32_t kCommWindowIDs[2] = { 0x063bf17c, 0x063bf17d };
static const uint32_t kCommRelDataKeys[4] = { 0x05a55b10, 0x05a55b20, 0x05a55b30, 0x05a55b40 };
static const uint32_t kRelPanelMainWindow = 0x046977ff;
static const uint32_t kRelPanelSubWindow = 0x055d626f;
static const uint32_t kRelPanelChildKey = 0x8ed27e7a;

static const uint32_t kProgressCurrentA = 0x0643d8b3;
static const uint32_t kProgressCurrentB = 0x04cac3c5;
static const uint32_t kProgressCurrentC = 0x0643edb7;
static const uint32_t kProgressLoyaltyA = 0x0643d8da;
static const uint32_t kProgressLoyaltyB = 0xf47c278d;
static const uint32_t kProgressLoyaltyC = 0x0643edbe;

static const uint32_t kMessageCommCivA = 0x03ac86ad;
static const uint32_t kMessageCommCivB = 0x03ac86b5;
static const uint32_t kMessageCommClose = 0x052f1544;

// ---------------------------------------------------------------------------
// the civilization panel
// ---------------------------------------------------------------------------

// @ 0x00e06220
void cSPUIGlobalUICiv::Update(int32_t nDelta)
{
    m_fCommRelTimer += (float)(uint32_t)nDelta;

    bool bCommActive = CommManager()->IsActive();
    const uint32_t aWindowIDs[2] = { kCommWindowIDs[0], kCommWindowIDs[1] };
    for (int32_t i = 0; i < 2; ++i) {
        IWindow* pWindow = FindWindowByID(aWindowIDs[i]);
        if (pWindow == nullptr)
            continue;
        bool bVisible = pWindow->IsVisible();
        if (bVisible != bCommActive)
            pWindow->SetState(1, bVisible == 0);
    }

    if (bCommActive != m_bCommScreenActive)
        SetMinimapStateFromButton(bCommActive);
    m_bCommScreenActive = bCommActive;

    for (int32_t i = 0; i < 4; ++i) {
        if (m_commRelPanels[i].m_bActive && m_commRelPanels[i].m_pCiv != nullptr)
            UpdateCommRelPanel(nDelta, i);
    }

    BindCommRelData(kCommRelDataKeys[0], &m_apCommRelData[0], 0);
    BindCommRelData(kCommRelDataKeys[1], &m_apCommRelData[1], 1);
    BindCommRelData(kCommRelDataKeys[2], &m_apCommRelData[2], 2);
    BindCommRelData(kCommRelDataKeys[3], &m_apCommRelData[3], 3);

    RefreshCommRelPanels();

    cCivilization* pCiv = NounManager()->GetPlayerCivilization();
    if (pCiv != nullptr) {
        int32_t nTurn = pCiv->GetTurn();
        SetCommRelProgress(kProgressCurrentA, kProgressCurrentB, kProgressCurrentC,
                           pCiv->m_nStage < 3 ? GetCurrentTurn() - nTurn : 0);
        SetCommRelProgress(kProgressLoyaltyA, kProgressLoyaltyB, kProgressLoyaltyC,
                           pCiv->m_nStage < 4 ? GetLastTurn() - nTurn : 0);
    }
}

// @ 0x00e063d0
void cSPUIGlobalUICiv::SetCommScreenVisibility(cCivilization* pCiv, bool bOn)
{
    if (pCiv == NounManager()->GetPlayerCivilization())
        return;
    if (mCivToIndex.Find(pCiv) == &mCivToIndex.m_stHeader)
        return;

    uint32_t nIndex = mCivToIndex.GetCounter(pCiv);
    cCommRelPanel* pPanel = &m_commRelPanels[nIndex];

    IWindow* pMain = FindWindowByID(kRelPanelMainWindow)->CreateChild(pPanel->m_pData, 0);
    IWindow* pSub = FindWindowByID(kRelPanelSubWindow)->CreateChild(pPanel->m_pData, 0);

    pMain->Select();
    pMain->SetState(0x10, bOn);
    pSub->SetState(0x10, bOn);

    ISubWindow* pMainChild = pMain->GetSubWindow(kRelPanelChildKey);
    ISubWindow* pSubChild = pSub->GetSubWindow(kRelPanelChildKey);

    pMainChild->SetState(4, bOn);
    pSubChild->SetState(4, bOn);

    pMain->Refresh();
    pSub->Refresh();
}

// @ 0x00e064f0
void cSPUIGlobalUICiv::AssignCommRelPanel(int32_t nIndex, cCivilization* pCiv)
{
    mCivToIndex.GetCounter(pCiv) = nIndex;

    cCommRelPanel* pPanel = &m_commRelPanels[nIndex];
    pPanel->m_bActive = true;
    pPanel->m_bShown = false;

    cCivilization* pOld = pPanel->m_pCiv;
    if (pCiv != pOld) {
        if (pCiv != nullptr)
            pCiv->AddRef();
        pPanel->m_pCiv = pCiv;
        if (pOld != nullptr)
            pOld->Release();
    }

    ActivateCommRelPanel(nIndex);
}

// @ 0x00e06560
void cSPUIGlobalUICiv::HandleMessage(uint32_t nMessage, void* pData)
{
    switch (nMessage) {
    case kMessageCommCivA:
    case kMessageCommCivB:
        SetCommScreenVisibility(((cCivMessage*)pData)->m_pCiv, nMessage == kMessageCommCivA);
        break;
    case kMessageCommClose:
        FUN_00e05930(-1);
        break;
    }
    cSPUIGlobalUI::HandleMessage(nMessage, pData);
}

// @ 0x00e065c0
void cSPUIGlobalUICiv::InitCommRelPanels()
{
    bool bAny = false;
    cCivilizationList* pList = NounManager()->GetCivilizationList();
    cCivilization** pCiv = pList->m_pBegin;
    cCivilization** pCivEnd = pList->m_pEnd;
    if (pCiv != pCivEnd) {
        do {
            cCivilization* pCur = *pCiv;
            if (!pCur->m_bNotPlayable && pCur->m_bVisible) {
                AssignCommRelPanel(pCur->m_nPanelIndex, pCur);
                bAny = true;
            }
            ++pCiv;
        } while (pCiv != pCivEnd);

        if (bAny) {
            m_bFlag88 = true;
            SetMinimapStateFromButton(0);
        }
    }
}

// @ 0x00e06630
void cSPUIGlobalUICiv::AssignFreeCommRelPanel(cCivilization* pCiv)
{
    if (mCivToIndex.Find(pCiv) != &mCivToIndex.m_stHeader)
        return;

    uint32_t nIndex = 0;
    while (nIndex < 4 && m_commRelPanels[nIndex].m_bActive)
        ++nIndex;

    AssignCommRelPanel(nIndex, pCiv);
    pCiv->m_nPanelIndex = nIndex;

    if (nIndex == 0) {
        m_bFlag88 = true;
        SetMinimapStateFromButton(0);
    }
}

// ---------------------------------------------------------------------------
// the meter base
// ---------------------------------------------------------------------------

class cRandom {
public:
    uint32_t RandomUint32Uniform(uint32_t nRange);   // 0x00a68fb0
};

extern cRandom gMathRandom;                      // 0x01601760

// the meter carries two vtable pointers (its content-validation base and the
// interface it exposes), so the object layout is base, base, fields.
class cSPUIMeterBaseA {
public:
    virtual void V00();                                 // +0x00
    PV8                                                 // 0x04 .. 0x20
    ~cSPUIMeterBaseA() {}
};

class cSPUIMeterBaseB {
public:
    virtual void V00();                                 // +0x00
    ~cSPUIMeterBaseB() {}
};

class cSPUIMeter : public cSPUIMeterBaseA, public cSPUIMeterBaseB {
public:
    cSPUIMeter(int32_t nRootID, uint32_t nFlags, const wchar_t* pName, uint32_t nLayoutFlags);  // 0x00e06790
    ~cSPUIMeter();                                      // 0x00e06870

    void SetStart(uint32_t nStart);                     // 0x00e066d0
    void SetTrackedObject(ILink* pObject);              // 0x00e066e0
    bool Update(int32_t nDelta, void* pMessage);        // 0x00e068e0
    void Shutdown(uint32_t nFlags);                     // 0x00e06940
    bool IsVisible();                                   // 0x00e06970
    void UpdateFromSource();                            // 0x00e06990
    void SetLink(ILink* pLink);                         // 0x00e06c50
    void SetLinkB(ILink* pLink);                        // 0x00e06ca0
    void SetSource(ILink* pSource);                     // 0x00e06cf0

    virtual void OnValueChanged();                      // +0x24
    virtual void OnLayoutChanged();                     // +0x28

    uint32_t m_nFlags08;                                // +0x08
    bool m_bRangeType;                                  // +0x0c
    uint8_t m_pad00d[3];                                // +0x0d
    cSPUILayout* mLayout;                               // +0x10
    ILink* m_pSource;                                   // +0x14
    uint32_t m_nRootID;                                 // +0x18
    uint32_t m_nLayoutFlags;                            // +0x1c
    uint32_t m_nStart;                                  // +0x20
    uint32_t m_nNext;                                   // +0x24
    int32_t m_nModel;                                   // +0x28
    int32_t m_nModelExtra;                              // +0x2c
    ILink* m_pTracked;                                  // +0x30
    ILink* m_pLinkA;                                    // +0x34
    ILink* m_pLinkB;                                    // +0x38
};

// @ 0x00e066d0
void cSPUIMeter::SetStart(uint32_t nStart)
{
    m_nModelExtra = nStart;
    m_nNext = m_nStart;
}

// @ 0x00e066e0
void cSPUIMeter::SetTrackedObject(ILink* pObject)
{
    m_pTracked = pObject;
    if (pObject != nullptr) {
        m_nModelExtra = pObject->GetValue();
        m_nNext = m_nStart;
        return;
    }
    m_nNext = m_nStart;
}

// @ 0x00e06790
cSPUIMeter::cSPUIMeter(int32_t nRootID, uint32_t nFlags, const wchar_t* pName, uint32_t nLayoutFlags)
{
    m_nFlags08 = 0;
    m_bRangeType = false;
    mLayout = nullptr;
    m_pSource = nullptr;
    m_nRootID = nRootID;
    m_nLayoutFlags = nFlags;
    m_nStart = 0;
    m_nNext = 0;

    cSPUILayout* pNew = CreateLayout(0x18, "Simulator/cUIMeter", 0, 0, 0, 0);
    cSPUILayout* pOld = mLayout;
    if (pNew != pOld) {
        if (pNew != nullptr)
            ((IWindow*)pNew)->S04();
        mLayout = pNew;
        if (pOld != nullptr)
            ((IWindow*)pOld)->Release();
    }
    mLayout->Init(pName, 0x40464100, true, nLayoutFlags);

    IWindow* pOwner = mLayout->FindWindowByID(nRootID, true);
    if (pOwner != nullptr)
        pOwner->AttachOwner(this);
}

// @ 0x00e06870
cSPUIMeter::~cSPUIMeter()
{
    if (mLayout != nullptr)
        mLayout->Shutdown(1);
    if (mLayout != nullptr) {
        IWindow* pLayout = (IWindow*)mLayout;
        mLayout = nullptr;
        pLayout->Release();
    }
    if (m_pSource != nullptr)
        m_pSource->Release2();
    if (mLayout != nullptr)
        ((IWindow*)mLayout)->Release();
}

// @ 0x00e068e0
bool cSPUIMeter::Update(int32_t nDelta, void* pMessage)
{
    if (((cCivMessage*)pMessage)->m_nType == 0xc) {
        if (m_nStart >= m_nNext) {
            m_nNext = m_nStart + 1;
            if (mLayout != nullptr && mLayout->IsVisible()) {
                OnValueChanged();
                OnLayoutChanged();
                ++m_nStart;
                return false;
            }
            m_nNext += gMathRandom.RandomUint32Uniform(10);
        }
        ++m_nStart;
    }
    return false;
}

// @ 0x00e06940
void cSPUIMeter::Shutdown(uint32_t nFlags)
{
    if (mLayout != nullptr)
        mLayout->Shutdown(nFlags);
    if (mLayout != nullptr) {
        IWindow* pLayout = (IWindow*)mLayout;
        mLayout = nullptr;
        pLayout->Release();
    }
}

// @ 0x00e06970
bool cSPUIMeter::IsVisible()
{
    return mLayout != nullptr && mLayout->IsVisible();
}

// @ 0x00e06990
void cSPUIMeter::UpdateFromSource()
{
    if (mLayout == nullptr)
        return;
    ILink* pSource = m_pSource;
    if (pSource == nullptr)
        return;

    float afRange[2];
    if (!pSource->GetRange(m_bRangeType, afRange))
        return;

    IWindow* pWindow = mLayout->FindWindowByID(m_nRootID, true);
    if (pWindow == nullptr)
        return;

    float* pArea = pWindow->GetArea();
    float fLow = pArea[1];
    float fHigh = pArea[3];
    pWindow->SetProgress(afRange[0], (fHigh - fLow) * 2.0f + afRange[1]);
}

// @ 0x00e06c50
void cSPUIMeter::SetLink(ILink* pLink)
{
    ILink* pOld = m_pLinkA;
    if (pLink != pOld) {
        if (pLink != nullptr)
            pLink->AddRef();
        m_pLinkA = pLink;
        if (pOld != nullptr)
            pOld->Release();
    }
    m_nNext = m_nStart;
}

// @ 0x00e06ca0
void cSPUIMeter::SetLinkB(ILink* pLink)
{
    ILink* pOld = m_pLinkB;
    if (pLink != pOld) {
        if (pLink != nullptr)
            pLink->AddRef();
        m_pLinkB = pLink;
        if (pOld != nullptr)
            pOld->Release();
    }
    m_nNext = m_nStart;
}

// @ 0x00e06cf0
void cSPUIMeter::SetSource(ILink* pSource)
{
    ILink* pOld = m_pSource;
    if (pSource != pOld) {
        if (pSource != nullptr)
            pSource->AddRef2();
        m_pSource = pSource;
        if (pOld != nullptr)
            pOld->Release2();
    }
    m_nNext = m_nStart;
}

// ---------------------------------------------------------------------------
// the loyalty meter
// ---------------------------------------------------------------------------

class cCivModeState {
public:
    uint8_t m_pad000[0x80];
    cLinkObject* m_pCity;                        // +0x80
};

class cCivModeStrategy {
public:
    static cCivModeStrategy* __cdecl Get();      // 0x00cf74c0
    cCivModeState* GetState();                   // 0x00cf74f0
};

class cMissionPanel {
public:
    bool ShouldShow();                           // 0x00e18c70
};

class cWindowManager {
public:
    virtual void W00();                          // +0x00
    PV16 PV8 PV4 PV2 PV2 PV8 PV4 PV2 PV PV16 PV8 PV4 PV2 PV2      // 0x04 .. 0x80
    virtual bool IsModalOpen();                  // +0x84
};

cWindowManager* __cdecl WindowManager();         // 0x0067caa0
cMissionPanel* __cdecl MissionPanel(int32_t nMode);   // 0x00b3d3f0

class cTriggerManager {
public:
    bool IsBlocking();                           // 0x00ac80f0
};

cTriggerManager* __cdecl GetTriggerMgr();        // 0x00b3d4d0

uint32_t __cdecl GetCurrentGameModeId();         // 0x00b5b800
bool __cdecl IsCityBlocked(cLinkObject* pCity);  // 0x00d09660

class cSPUILoyaltyMeter : public cSPUIMeter {
public:
    cSPUILoyaltyMeter* AsInterface(uint32_t nIID);              // 0x00e066a0
    cSPUILoyaltyMeter(uint32_t nDelay, int32_t nRootID, uint32_t nFlags,
                      const wchar_t* pName, uint32_t nLayoutFlags);  // 0x00e06a10
    ~cSPUILoyaltyMeter();                                       // 0x00e06ac0
    void SetModel(int32_t nModel, int32_t nExtra);              // 0x00e06710
    void SetRange(float fLow, float fHigh);                     // 0x00e06730
    void Update(int32_t nDelta, void* pMessage);                // 0x00e06b20
    void PullToFront();                                         // 0x00e06d50

    uint32_t m_nDelay;                           // +0x3c
    bool m_bRangeSet;                            // +0x40
    uint8_t m_pad041[3];                         // +0x41
    float m_fLow;                                // +0x44
    float m_fHigh;                               // +0x48
    int32_t m_nModelExtra2;                      // +0x4c
};

static const uint32_t kLoyaltyInterfaceIDs[4] = { 0x0404fb83, 0xee3f516e, 0x034c6eec, 0x2f009dd0 };
static const uint32_t kMeterObjectKey = 0x01186577;
static const uint32_t kModeCivA = 0x00dbdba1;
static const uint32_t kModeCivB = 0x01654c04;

// @ 0x00e066a0
cSPUILoyaltyMeter* cSPUILoyaltyMeter::AsInterface(uint32_t nIID)
{
    if (nIID == kLoyaltyInterfaceIDs[0])
        return this;
    if (nIID == kLoyaltyInterfaceIDs[1])
        return this;
    if (nIID == kLoyaltyInterfaceIDs[2])
        return this;
    return nIID == kLoyaltyInterfaceIDs[3] ? this : nullptr;
}

// @ 0x00e06710
void cSPUILoyaltyMeter::SetModel(int32_t nModel, int32_t nExtra)
{
    m_nModel = nModel;
    m_nModelExtra2 = nExtra;
    OnLayoutChanged();
}

// @ 0x00e06730
void cSPUILoyaltyMeter::SetRange(float fLow, float fHigh)
{
    m_fLow = fLow;
    m_fHigh = fHigh;
    m_bRangeSet = true;
    OnValueChanged();
}

// @ 0x00e06a10
cSPUILoyaltyMeter::cSPUILoyaltyMeter(uint32_t nDelay, int32_t nRootID, uint32_t nFlags,
                                     const wchar_t* pName, uint32_t nLayoutFlags)
    : cSPUIMeter(nRootID, nFlags, pName, nLayoutFlags)
{
    m_nModel = -1;
    m_nModelExtra = 0;
    m_pTracked = nullptr;
    m_pLinkA = nullptr;
    m_pLinkB = nullptr;
    m_bRangeSet = true;
    m_fLow = 0.0f;
    m_fHigh = 0.0f;
    m_nModelExtra2 = -1;
    m_bRangeType = true;
    m_nDelay = nDelay;
    m_nNext = m_nStart;

    IWindow* pOwner = mLayout->FindWindowByID(m_nRootID, true);
    if (pOwner != nullptr) {
        IWindow* pDecorator = pOwner->GetDecorator();
        pDecorator->AttachChild(pOwner);
    }
}

// @ 0x00e06ac0
cSPUILoyaltyMeter::~cSPUILoyaltyMeter()
{
    if (m_pLinkA != nullptr) {
        ILink* pLinkA = m_pLinkA;
        m_pLinkA = nullptr;
        pLinkA->Release();
    }
    if (m_pLinkB != nullptr) {
        ILink* pLinkB = m_pLinkB;
        m_pLinkB = nullptr;
        pLinkB->Release();
    }
    if (m_pLinkB != nullptr)
        m_pLinkB->Release();
    if (m_pLinkA != nullptr)
        m_pLinkA->Release();
}

// @ 0x00e06b20
void cSPUILoyaltyMeter::Update(int32_t nDelta, void* pMessage)
{
    if (((cCivMessage*)pMessage)->m_nType == 0xc && m_nStart >= m_nNext) {
        ILink* pLink = m_pLinkA != nullptr ? m_pLinkA : m_pLinkB;
        if (pLink != nullptr) {
            cLinkObject* pObject = (cLinkObject*)pLink->GetObject(kMeterObjectKey);
            if (pObject != nullptr) {
                bool bShow = pObject->IsAvailable()
                    || CommManager()->IsActive()
                    || MissionPanel(0)->ShouldShow()
                    || WindowManager()->IsModalOpen()
                    || GetTriggerMgr()->IsBlocking()
                    || GetCurrentGameModeId() == kModeCivA;
                if (!bShow) {
                    bShow = GetCurrentGameModeId() == kModeCivB
                        && cCivModeStrategy::Get() != nullptr
                        && cCivModeStrategy::Get()->GetState() != nullptr
                        && cCivModeStrategy::Get()->GetState()->m_pCity != nullptr
                        && IsCityBlocked(cCivModeStrategy::Get()->GetState()->m_pCity);
                }
                if (bShow)
                    OnLayoutChanged();
                else
                    OnValueChanged();
            }
        }
    }
    cSPUIMeter::Update(nDelta, pMessage);
}

// @ 0x00e06d50
void cSPUILoyaltyMeter::PullToFront()
{
    if (mLayout == nullptr)
        return;
    IWindow* pWindow = mLayout->FindWindowByID(m_nRootID, true);
    if (pWindow == nullptr)
        return;
    IWindow* pDecorator = pWindow->GetDecorator();
    pDecorator->BringToFront(pWindow);
}
