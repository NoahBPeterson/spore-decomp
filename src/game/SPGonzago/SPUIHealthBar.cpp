// src/game/SPGonzago/SPUIHealthBar.cpp -- migrated from slice(s) s00e07bb0, s00e06d90, s00e06220 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIHealthBar.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCivilization.h"
#include "SP/cGameNounManager.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "cSPUILayout.h"
#include "SP/cCommunity.h"
#include "SP/cString.h"

// ---- items of slice s00e06220 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct ISubWindow {
    PV16 PV8 PV2 PV                              // 0x00 .. 0x24
    virtual void SetState(int32_t nState, bool bOn);      // +0x28
};
class cSPUILayout_s00e0_6220 {
public:
    bool Init(const wchar_t* pName, uint32_t nID, bool bDeep, uint32_t nFlags);   // 0x00812160
    IWindow* FindWindowByID(uint32_t nID, bool bDeep);          // 0x008105b0
    void Shutdown(uint32_t nFlags);                             // 0x00811ad0
    bool IsVisible();                                           // 0x00810070

    IWindow* m_pRoot;                            // +0x00
};
cSPUILayout_s00e0_6220* __cdecl CreateLayout(uint32_t nSize, const char* pName, int32_t a, int32_t b,
                                  int32_t c, int32_t d);    // 0x00810000
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
class cCommManager {
public:
    bool IsActive();                             // 0x00ae9390
};
cCommManager* __cdecl CommManager();             // 0x00b3d4a0
class cLinkObject {
public:
    bool IsAvailable();                          // 0x00c88e30
};
struct cCivMessage {
    uint8_t m_pad000[8];
    int32_t m_nType;                             // +0x08
    uint8_t m_pad00c[4];                         // +0x0c
    cCivilization* m_pCiv;                       // +0x10
};
class cRandom {
public:
    uint32_t RandomUint32Uniform(uint32_t nRange);   // 0x00a68fb0
};
extern cRandom gMathRandom;                      // 0x01601760
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
    cSPUILayout_s00e0_6220* mLayout;                               // +0x10
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
// ---- items of slice s00e06220 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cRandom gMathRandom;                      // 0x01601760

// ---- items of slice s00e06d90 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cSPUILayout {
    void* mpVtable;                                          // +0x00
    char IsVisible();                                        // 0x00810070
    void SetVisibility(int visible);                         // 0x00810590
};
}
namespace SP {
struct cSPUILoyaltyMeter_s00e0_6d90 {
    void*        mpVtable;                                   // +0x00
    uint32_t     mPad04[3];                                  // +0x04 .. +0x0f
    cSPUILayout* mpLayout;                                   // +0x10
    uint32_t     mPad14[3];                                  // +0x14 .. +0x1f
    uint32_t     mValue20;                                   // +0x20
    uint32_t     mValue24;                                   // +0x24
    uint32_t     mPad28;                                     // +0x28
    void*        mpExtra2c;                                  // +0x2c

    void Show();
    void Hide();
    void ShowExpanded();
    void HideExpanded();
};
}
// ---- items of slice s00e06d90 end

// ---- items of slice s00e07bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cSPUILayout_s00e0_7bb0;
}
namespace SP {
class cCommunity_s00e0_7bb0;
}
namespace SP {
class cNoun;
}
namespace SP {
struct WStr {
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCapacity;    // +0x08
    uint32_t mAllocator;    // +0x0c

    WStr() : mpBegin(0), mpEnd(0), mpCapacity(0) {}

    ~WStr()
    {
        if ((((int)((char*)mpCapacity - (char*)mpBegin) & 0xfffffffe) > 2) && mpBegin)
            operator delete(mpBegin);
    }

    void RangeInitialize(const wchar_t* p);     // 0x00579a90
    void append(const wchar_t* p);              // 0x005c3d90
};
}
namespace SP {
struct NameSlot {
    union {
        uint32_t mPad;
        float    mPhase;
        int      mPhaseInt;
    };
    WStr mName;
};
}
namespace SP {
void __cdecl operator delete(void* p);          // 0x00f47380
}
namespace SP {
struct cString_s00e0_7bb0 {
    char mData[0x14];

    cString_s00e0_7bb0(uint32_t a, uint32_t b, int c);     // 0x006b5770
    ~cString_s00e0_7bb0();                                 // 0x006b5240
    const wchar_t* GetText();                   // 0x006b55c0
};
}
namespace SP {
class IWindow_s00e0_7bb0 {
public:
    virtual void v00();                          // +0x00
    virtual void SetProgress(float value);       // +0x04
    virtual void v08();                          // +0x08
    virtual IWindow_s00e0_7bb0* GetSubWindow(uint32_t id);  // +0x0c
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
    virtual void v58();
    virtual void SetColor(uint32_t color);       // +0x5c
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void SetVisible(int a, int b);       // +0x7c
    virtual void SetText(const wchar_t* text);   // +0x80
};
}
namespace SP {
class cSPUILayout_s00e0_7bb0 {
public:
    IWindow_s00e0_7bb0* FindWindowByID(uint32_t id, int deep);   // 0x008105b0
};
}
namespace SP {
class cNounName {
public:
    virtual void v00();                          // +0x00
    virtual const wchar_t* GetText();            // +0x04
    uint32_t mPad;                               // +0x08
};
}
namespace SP {
class cNounColor {
public:
    uint32_t mValue;                             // +0x00
    uint32_t GetPacked();                        // 0x00b6f310
};
}
namespace SP {
class cNoun {
public:
    uint32_t pad00[0x0d];                        // +0x00 .. +0x33
    cNounName mName;                             // +0x34
    cNounColor mColor;                           // +0x3c
    uint32_t pad40[0x12];                        // +0x40 .. +0x87
    uint8_t pad88;                               // +0x88
    uint8_t mFlag89;                             // +0x89
};
}
namespace SP {
class cCommunity_s00e0_7bb0 {
public:
    float GetPhaseRatio();                       // 0x00bfdea0
    float ReadPhase(int phase);                  // 0x00bfde50
    cNoun* GetNoun();                            // 0x00bfdf80
};
}
namespace SP {
float __cdecl FUN_00bd80d0(cNoun* pNoun);        // 0x00bd80d0
}
namespace SP {
void __cdecl FUN_00881ea0(double value, void* buffer, int maxLen, int flags);   // 0x00881ea0
}
namespace SP {
extern wchar_t DAT_013ec468[];                   // 0x013ec468
}
namespace SP {
class cSPUIMineralBar {
public:
    void* mVtbl0;                                // +0x00
    void* mVtbl1;                                // +0x04
    uint32_t m_nFlags08;                         // +0x08
    uint8_t m_bRangeType;                        // +0x0c
    uint8_t m_pad0d[3];                          // +0x0d
    cSPUILayout_s00e0_7bb0* mLayout;                        // +0x10
    void* m_pSource;                             // +0x14
    uint32_t m_nRootID;                          // +0x18
    uint32_t m_nWindowID;                        // +0x1c
    uint32_t m_nStart;                           // +0x20
    uint32_t m_nNext;                            // +0x24
    cCommunity_s00e0_7bb0* mpCommunity;                     // +0x28
    int32_t m_nModelExtra;                       // +0x2c
    void* m_pTracked;                            // +0x30
    void* m_pLinkA;                              // +0x34
    void* m_pLinkB;                              // +0x38

    void UpdateMeter();                          // 0x00e07bb0
};
}
// ---- items of slice s00e07bb0 end

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

    cSPUILayout_s00e0_6220* pNew = CreateLayout(0x18, "Simulator/cUIMeter", 0, 0, 0, 0);
    cSPUILayout_s00e0_6220* pOld = mLayout;
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

// @ 0x00e06a10
cSPUILoyaltyMeter::cSPUILoyaltyMeter(uint32_t nDelay, int32_t nRootID, uint32_t nFlags, const wchar_t* pName, uint32_t nLayoutFlags)
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

// @ 0x00e07950
namespace SP {
void cSPUILoyaltyMeter_s00e0_6d90::Show()
{
    if (mpLayout && mpLayout->IsVisible())
        return;
    mpLayout->SetVisibility(1);
    ((void (__thiscall*)(cSPUILoyaltyMeter_s00e0_6d90*))((void**)mpVtable)[0x24 / 4])(this);
    ((void (__thiscall*)(cSPUILoyaltyMeter_s00e0_6d90*))((void**)mpVtable)[0x28 / 4])(this);
    mValue24 = mValue20;
}
}  // namespace SP

// @ 0x00e07990
namespace SP {
void cSPUILoyaltyMeter_s00e0_6d90::Hide()
{
    if (mpLayout && mpLayout->IsVisible()) {
        mpLayout->SetVisibility(0);
        mValue24 = mValue20;
    }
}
}  // namespace SP

// @ 0x00e07b20
namespace SP {
void cSPUILoyaltyMeter_s00e0_6d90::ShowExpanded()
{
    if (mpExtra2c) {
        ((void (__thiscall*)(void*, int, int))((void**)*(void**)mpExtra2c)[0x7c / 4])
            (mpExtra2c, 1, 1);
    }
    if (mpLayout && mpLayout->IsVisible())
        return;
    mpLayout->SetVisibility(1);
    ((void (__thiscall*)(cSPUILoyaltyMeter_s00e0_6d90*))((void**)mpVtable)[0x24 / 4])(this);
    ((void (__thiscall*)(cSPUILoyaltyMeter_s00e0_6d90*))((void**)mpVtable)[0x28 / 4])(this);
    mValue24 = mValue20;
}
}  // namespace SP

// @ 0x00e07b70
namespace SP {
void cSPUILoyaltyMeter_s00e0_6d90::HideExpanded()
{
    if (mpLayout && mpLayout->IsVisible()) {
        mpLayout->SetVisibility(0);
        mValue24 = mValue20;
    }
    if (mpExtra2c) {
        ((void (__thiscall*)(void*, int, int))((void**)*(void**)mpExtra2c)[0x7c / 4])
            (mpExtra2c, 1, 0);
    }
}
}  // namespace SP

// @ 0x00e07bb0
namespace SP {
void cSPUIMineralBar::UpdateMeter()
{
    if (mLayout == 0)
        return;
    if (mpCommunity == 0)
        return;

    float value = mpCommunity->GetPhaseRatio() * 100.0f;

    IWindow_s00e0_7bb0* pMeter = mLayout->FindWindowByID(m_nWindowID, 1);
    IWindow_s00e0_7bb0* pSub = pMeter->GetSubWindow(0x10edf11);
    if (pSub != 0) {
        float clamped = value;
        if (clamped < 0.0f)
            clamped = 0.0f;
        if (clamped > 100.0f)
            clamped = 100.0f;
        pSub->SetProgress(clamped);
    }

    cNoun* pNoun = mpCommunity->GetNoun();
    uint32_t color = 0x8c79898d;
    NameSlot nameSlot;
    nameSlot.mName.RangeInitialize(DAT_013ec468);

    if (pNoun != 0) {
        color = pNoun->mColor.GetPacked();
        nameSlot.mName.append(pNoun->mName.GetText());
    }
    else {
        nameSlot.mName.append(cString_s00e0_7bb0(0x2db6dad3, 0x63c3d96, 0).GetText());
    }

    IWindow_s00e0_7bb0* pWindow = mLayout->FindWindowByID(0x62478b8, 1);
    if (pWindow != 0)
        pWindow->SetColor(color);

    pWindow = mLayout->FindWindowByID(0x6245a18, 1);
    if (pWindow != 0)
        pWindow->SetText(nameSlot.mName.mpBegin);

    pWindow = mLayout->FindWindowByID(0x46adf86, 1);
    pSub = pWindow->GetSubWindow(0x10edf11);
    if (pSub != 0) {
        pWindow->SetVisible(1, (pNoun != 0 && pNoun->mFlag89 == 0)
                                 ? (pSub->SetProgress(FUN_00bd80d0(pNoun)), 1)
                                 : 0);
    }

    nameSlot.mPhase = mpCommunity->ReadPhase(0);
    nameSlot.mPhaseInt = (int)nameSlot.mPhase;
    wchar_t buffer[40];
    buffer[0] = 0;
    FUN_00881ea0((double)nameSlot.mPhaseInt, buffer, 0x28, 0);

    WStr phaseText;
    phaseText.RangeInitialize(buffer);

    pWindow = mLayout->FindWindowByID(0x55155f9, 1);
    if (pWindow != 0) {
        pSub = pWindow->GetSubWindow(0xeeee8218);
        if (pSub != 0)
            pSub->SetText(phaseText.mpBegin);
    }
}
}  // namespace SP
