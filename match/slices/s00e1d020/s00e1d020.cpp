// s00e1d020 -- SP::cUIMissionCardPanel refresh / slot handling, the mission
// message handler and the space-trading tab that wraps the same card machinery.
//
//   0x00e1d020 cUIMissionCardPanel::Refresh      (mission list -> card slots)
//   0x00e1d610 cUIMissionCardPanel::SetSlot
//   0x00e1d710 cMissionSlot::OnNotify
//   0x00e1d7a0 cUIMissionsHandler::DoMessage
//   0x00e1dae0 cTradeUI::Activate
//   0x00e1db60 cUITradingActivity::Deactivate
//   0x00e1dbd0 FUN_00e1dbd0                      (shut the trading tab down)
//   0x00e1dc20 cTradeUI::Destroy                 (scalar deleting destructor)
//   0x00e1dc70 FUN_00e1dc70                      (restart the trading tab)
//   0x00e1dc80 cUITradingActivity::SetMission
//   0x00e1de60 FUN_00e1de60                      (strip control chars)
//
// Layout note: the trading tab is one global object at 0x015a51b4 whose second
// polymorphic base subobject starts at +0x04 (its vtable word is +0x04) and
// whose cSPUILayout member sits at +0x08.  The mission-card panel keeps the
// mission slot vector at +0x44, its two feed-list categories at +0x70/+0x74,
// the pressed mission-button id at +0x8c and the selected slot at +0x90; the
// notify handler is a member of the slot subobject at +0x40, so its fields are
// the panel fields shifted by 0x40.
#include "types.h"

#define nullptr 0

// ---------------------------------------------------------------------------
// engine interfaces
// ---------------------------------------------------------------------------

// EA::UTFWin::IWindow / IWinButton vtable, addressed by byte offset.  Only the
// slots this file calls are named; the rest keep their offset in the name.
class IWindow {
public:
    virtual void Slot000();             // +0x000
    virtual void Slot004();             // +0x004
    virtual void Slot008();             // +0x008
    virtual void* GetObject(uint32_t nID);      // +0x00c
    virtual void* GetOwner();                   // +0x010
    virtual void Slot014();             // +0x014
    virtual void Slot018();             // +0x018
    virtual uint32_t GetID();                   // +0x01c
    virtual void Slot020();             // +0x020
    virtual void Slot024();             // +0x024
    virtual void SetFlags(int32_t nA, int32_t nB);  // +0x028
    virtual uint32_t GetState();                // +0x02c
    virtual void Slot030();             // +0x030
    virtual void Slot034();             // +0x034
    virtual void Slot038();             // +0x038
    virtual void Slot03c();             // +0x03c
    virtual void Slot040();             // +0x040
    virtual void Slot044();             // +0x044
    virtual void Slot048();             // +0x048
    virtual void Slot04c();             // +0x04c
    virtual void Slot050();             // +0x050
    virtual const wchar_t* GetCaption();        // +0x054
    virtual void Slot058();             // +0x058
    virtual void Slot05c();             // +0x05c
    virtual void Slot060();             // +0x060
    virtual void Slot064();             // +0x064
    virtual void Slot068();             // +0x068
    virtual void Slot06c();             // +0x06c
    virtual void Slot070();             // +0x070
    virtual void Slot074();             // +0x074
    virtual void Slot078();             // +0x078
    virtual void SetMode(int32_t nMode, int32_t nFlag);     // +0x07c
    virtual void Slot080();             // +0x080
    virtual void Slot084();             // +0x084
    virtual void Slot088();             // +0x088
    virtual void Slot08c();             // +0x08c
    virtual void Slot090();             // +0x090
    virtual void Slot094();             // +0x094
    virtual void Slot098();             // +0x098
    virtual void Slot09c();             // +0x09c
    virtual void Slot0a0();             // +0x0a0
    virtual void Slot0a4();             // +0x0a4
    virtual void Slot0a8();             // +0x0a8
    virtual void Slot0ac();             // +0x0ac
    virtual void Slot0b0();             // +0x0b0
    virtual void Slot0b4();             // +0x0b4
    virtual void Slot0b8();             // +0x0b8
    virtual void Slot0bc();             // +0x0bc
    virtual void Slot0c0();             // +0x0c0
    virtual void Slot0c4();             // +0x0c4
    virtual void Slot0c8();             // +0x0c8
    virtual void Slot0cc();             // +0x0cc
    virtual void Slot0d0();             // +0x0d0
    virtual void Slot0d4();             // +0x0d4
    virtual void Slot0d8();             // +0x0d8
    virtual void Slot0dc();             // +0x0dc
    virtual void SetParent(void* pParent);      // +0x0e0
    virtual void Slot0e4();             // +0x0e4
    virtual void Slot0e8();             // +0x0e8
    virtual void Slot0ec();             // +0x0ec
    virtual void Slot0f0();             // +0x0f0
    virtual void Slot0f4();             // +0x0f4
    virtual void Slot0f8();             // +0x0f8
    virtual void Slot0fc();             // +0x0fc
    virtual void Slot100();             // +0x100
    virtual void SetOwner(void* pOwner);        // +0x104
    virtual void OnActivate(void* pOwner);      // +0x108
};

// SP::cUILayout -- the tab's UI layout object (0x18 bytes in this build).
class cSPUILayout {
public:
    bool Init(const wchar_t* pszName, uint32_t nStyle, bool bVisible, uint32_t nFlags);
    IWindow* FindWindowByID(uint32_t nWindowID, int32_t nRecursive);
    void Shutdown(uint32_t nFlags);
    void Destroy();

private:
    uint8_t mPad00[0x18];       // no data members are read by this file
};

void __cdecl SPUIHelpers_BeginModal(IWindow* pWindow, void* pContext, bool bModal);
void __cdecl SPUIHelpers_EndModal(IWindow* pWindow, int32_t nA, int32_t nB);

class cGameTimeManager {
public:
    void IncPauseGate(uint32_t nGate);
    void DecPauseGate(uint32_t nGate);
};

cGameTimeManager* __cdecl GameTimeManager();

extern wchar_t gEmptyString16[];                                // 0x01667bac

void __cdecl operator_delete_array(void* pBlock);               // 0x00f47380

// eastl::basic_string<wchar_t> -- three pointers; the empty state is the shared
// static empty string and its capacity points one past it.
class WString {
public:
    wchar_t* mpBegin;           // +0x00
    wchar_t* mpEnd;             // +0x04
    wchar_t* mpCapacity;        // +0x08

    WString()
    {
        mpBegin = gEmptyString16;
        mpEnd = gEmptyString16;
        mpCapacity = gEmptyString16 + 1;
    }

    ~WString()
    {
        if (mpEnd - mpBegin > 1 && mpBegin != nullptr)
            operator_delete_array(mpBegin);
    }

    void push_back(wchar_t wc);                                     // 0x004f6510
    WString& assign(const wchar_t* pFirst, const wchar_t* pLast);    // 0x00423650
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};

bool __cdecl FUN_004f56f0(wchar_t wc);                          // 0x004f56f0

// ---------------------------------------------------------------------------
// feed list / category (the panel's message list)
// ---------------------------------------------------------------------------
struct FeedItem;

class FeedList {
public:
    void SetPaused(bool bPaused);           // 0x00662920
    void Select(FeedItem* pItem);           // 0x00662c10
};

class FeedListCategory {
public:
    void ShutdownChildren();                        // 0x006657a0
    FeedItem* Find(int32_t nKey);                   // 0x006646c0
};

class cUIHints {
public:
    int32_t SetFlag(int32_t nFlag, int32_t nValue);     // 0x0067c420
};

cUIHints* __cdecl GetUIHints();                     // 0x0067cac0

namespace SP {

class cString {
public:
    cString(uint32_t nTable, uint32_t nIndex, const wchar_t* pszText);  // 0x006b5770
    ~cString();                                                         // 0x006b5240
    const wchar_t* GetText();                                           // 0x006b55c0
private:
    uint8_t mPad00[0x14];
};

} // namespace SP

// ---------------------------------------------------------------------------
// missions
// ---------------------------------------------------------------------------
class cSPMission {
public:
    bool IsVisibleInUI();           // 0x00c45340
    bool IsActive();                // 0x00c44c80
    void* GetOwnerEmpire();

    void* mpVtbl;                   // +0x000
    uint8_t mPad04[0x178];          // +0x004
    uint32_t mnFlags;               // +0x17c
};

// one entry of the global mission list returned by FUN_009892e0
struct MissionList {
    cSPMission** mpBegin;           // +0x00
    cSPMission** mpEnd;             // +0x04
};

// ---------------------------------------------------------------------------
// mission card panel
// ---------------------------------------------------------------------------
class SlotVector {
public:
    void** mpBegin;             // +0x00
    void** mpEnd;               // +0x04
    void** mpCapacity;          // +0x08
    void Erase(void** pFirst, void** pLast);        // 0x00e25bd0
};

class cUIMissionCardPanel {
public:
    void Refresh();                             // 0x00e1d020
    void SetSlot(void* pMission);               // 0x00e1d610
    void SetVisibleSlot(void* pMission);        // 0x00e18860
    void SetTitle(const wchar_t* pszText);      // 0x00e18890
    void SetTracked();                          // 0x00e1bbc0

    uint8_t mPad00[0x10];           // +0x000
    int32_t mnMissionType;          // +0x010
    uint8_t mPad14[0x30];           // +0x014
    SlotVector mSlots;              // +0x044
    uint8_t mPad50[0x1c];           // +0x050
    FeedList* mpFeedList;           // +0x06c
    FeedListCategory* mpCategoryA;  // +0x070
    FeedListCategory* mpCategoryB;  // +0x074
    uint8_t mPad78[0x14];           // +0x078
    uint32_t mMissionButtonId;      // +0x08c
    int32_t mnSelected;             // +0x090
};

// the notify handler is a member of the subobject at panel+0x40
class cMissionSlot {
public:
    void OnNotify(void* pSender, uint32_t nMessage);   // 0x00e1d710

    uint8_t mPad00[0x04];           // +0x000
    void** mppBegin;                // +0x004  (panel+0x44)
    void** mppEnd;                  // +0x008  (panel+0x48)
    uint8_t mPad0c[0x44];           // +0x00c
    int32_t mnSelected;             // +0x050  (panel+0x90)
    int32_t mnMessage;              // +0x054  (panel+0x94)
};

void __cdecl FUN_00c485d0();        // 0x00c485d0

// @ 0x00e1d710
void cMissionSlot::OnNotify(void* pSender, uint32_t nMessage)
{
    if (pSender != nullptr) {
        IWindow* pWindow = (IWindow*)pSender;
        if (pWindow->GetOwner() != nullptr)
            ((IWindow*)pWindow->GetOwner())->SetParent(pSender);
    }

    if (mnMessage == (int32_t)0xbf7ce923 && (int32_t)nMessage == 0x5107b1a
        && mnSelected >= 0 && mnSelected < (int32_t)(mppEnd - mppBegin)) {
        IWindow* pSlot = (IWindow*)mppBegin[mnSelected];
        if (pSlot != nullptr) {
            void* pMission = pSlot->GetObject(0x2aa5ada);
            if (pMission != nullptr) {
                FUN_00c485d0();
                ((cUIMissionCardPanel*)((uint8_t*)this - 0x40))->Refresh();
            }
        }
    }
    mnMessage = 0;
}

// @ 0x00e1d610
void cUIMissionCardPanel::SetSlot(void* pMission)
{
    SetVisibleSlot(pMission);

    if (GetUIHints() != nullptr)
        GetUIHints()->SetFlag(0, 1);

    Refresh();

    if (mpFeedList != nullptr)
        mpFeedList->SetPaused(true);

    SP::cString str(0x8b96f855, 0x60c9908, nullptr);
    SetTitle(str.GetText());

    if (pMission != nullptr) {
        IWindow* pMissionWindow = (IWindow*)pMission;
        void* pObject = pMissionWindow->GetObject(0x34066a80);
        if (pObject != nullptr) {
            int32_t nCount = (int32_t)(mSlots.mpEnd - mSlots.mpBegin);
            for (int32_t i = 0; i < nCount; ++i) {
                if (pObject == mSlots.mpBegin[i])
                    mnSelected = i;
            }

            FeedItem* pItem = mpCategoryA->Find(mnSelected + 0x6146391);
            if (pItem == nullptr)
                pItem = mpCategoryB->Find(mnSelected + 0x6146391);
            if (pItem != nullptr)
                mpFeedList->Select(pItem);

            SetTracked();
        }
    }
}

// ---------------------------------------------------------------------------
// card refresh
// ---------------------------------------------------------------------------
MissionList* __cdecl FUN_009892e0();                // 0x009892e0
uint32_t __cdecl FUN_00d37cb0();                    // 0x00d37cb0
uint32_t __cdecl FUN_00cd3440();                    // 0x00cd3440
uint32_t __cdecl FUN_00d004b0();                    // 0x00d004b0
void __cdecl FUN_00e1c7f0(cSPMission** ppMission);  // 0x00e1c7f0
void __cdecl FUN_00e1c830(void** pSlots, void** pEnd, int32_t nSelected);   // 0x00e1c830
void __cdecl FUN_00e1c930(void** pSlots, void** pEnd, int32_t nSelected);   // 0x00e1c930
void __cdecl FUN_00e1c9b0(void** pSlots, void** pEnd, int32_t nSelected);   // 0x00e1c9b0
void __cdecl FUN_00e1cb80(void** pSlots, void** pEnd, int32_t nSelected);   // 0x00e1cb80
void __cdecl FUN_00aea5d0(void** ppSlotEnd, cSPMission** ppMission);        // 0x00aea5d0
void* __cdecl FUN_00665410(uint32_t nType, int32_t nIndex);                 // 0x00665410
void __cdecl FUN_006668e0(void* pA, void* pB, void* pC);                    // 0x006668e0
void __cdecl FUN_00666a40(void* pItem);                                     // 0x00666a40
void __cdecl FUN_00668000(void* pText);                                     // 0x00668000
uint32_t __cdecl FUN_00664600();                                            // 0x00664600
void __cdecl FUN_006644e0(int32_t nValue);                                  // 0x006644e0
void __cdecl FUN_00664580(int32_t nValue);                                  // 0x00664580
void __cdecl FUN_00febf80(cSPMission* pMission);                            // 0x00febf80

extern uint32_t gDefaultCardColors[3];              // 0x015a50d4
extern uint32_t gSelectedCardColors[3];             // 0x015a50e0

// appends every mission of the list returned by pfnGet to the slot vector
__forceinline void AppendMissions(SlotVector* pSlots, uint32_t (*pfnGet)(), bool bFilter)
{
    if (pfnGet() == 0)
        return;
    MissionList* pList = FUN_009892e0();
    cSPMission** ppEnd = pList->mpEnd;
    for (cSPMission** pp = pList->mpBegin; pp != ppEnd; ++pp) {
        cSPMission* pMission = *pp;
        if (bFilter) {
            if (pMission->mnFlags != 0)
                continue;
            if (!pMission->IsVisibleInUI())
                continue;
            if (!pMission->IsActive())
                continue;
            cSPMission* pRef = pMission;
            FUN_00e1c7f0(&pRef);
        } else {
            cSPMission* pRef = pMission;
            if (pRef != nullptr)
                ((IWindow*)pRef)->GetOwner();
            if (pSlots->mpEnd < pSlots->mpCapacity) {
                *pSlots->mpEnd = pRef;
                pSlots->mpEnd = pSlots->mpEnd + 1;
                if (pRef != nullptr)
                    ((IWindow*)pRef)->GetOwner();
            } else {
                FUN_00aea5d0(pSlots->mpEnd, &pRef);
                pSlots->mpEnd = pSlots->mpEnd + 1;
            }
        }
    }
}

// @ 0x00e1d020
void cUIMissionCardPanel::Refresh()
{
    if (mpCategoryA != nullptr)
        mpCategoryA->ShutdownChildren();
    if (mpCategoryB != nullptr)
        mpCategoryB->ShutdownChildren();

    mSlots.Erase(mSlots.mpBegin, mSlots.mpEnd);
    SetTracked();

    switch (mnMissionType) {
    case 0x1654c01:
        AppendMissions(&mSlots, FUN_00d37cb0, false);
        break;
    case 0x1654c02:
        AppendMissions(&mSlots, FUN_00cd3440, false);
        break;
    case 0x1654c04:
        AppendMissions(&mSlots, FUN_00d004b0, false);
        break;
    case 0x1654c05:
        AppendMissions(&mSlots, FUN_00d37cb0, true);
        if (mMissionButtonId == 0x67a2be0)
            FUN_00e1c9b0(mSlots.mpBegin, mSlots.mpEnd, mnSelected);
        else if (mMissionButtonId == 0x67a2b48)
            FUN_00e1c930(mSlots.mpBegin, mSlots.mpEnd, mnSelected);
        else if (mMissionButtonId == 0x67a2ae0)
            FUN_00e1cb80(mSlots.mpBegin, mSlots.mpEnd, mnSelected);
        else if (mMissionButtonId == 0x67a2878)
            FUN_00e1c830(mSlots.mpBegin, mSlots.mpEnd, mnSelected);
        break;
    default:
        break;
    }

    int32_t nSlotCount = (int32_t)(mSlots.mpEnd - mSlots.mpBegin);
    if (nSlotCount == 0)
        mnSelected = -1;
    else
        mnSelected = (int32_t)((uint32_t)mnSelected % (uint32_t)nSlotCount);

    if (mpFeedList != nullptr) {
        for (int32_t i = 0; i < nSlotCount; ++i) {
            IWindow* pSlot = (IWindow*)mSlots.mpBegin[i];
            if (mnMissionType != 0x1654c05)
                pSlot->GetCaption();

            if (FUN_00665410(0x81b50b35, -1) != nullptr) {
                WString sText;
                IWindow* pParent = (IWindow*)pSlot;
                if (pParent != nullptr)
                    pParent->GetObject(0x2aa5ada);
                IWindow* pCard = pParent != nullptr
                    ? (IWindow*)pParent->GetObject(0x14066ce5) : nullptr;
                if (pCard != nullptr) {
                    pCard->Slot084();
                    pCard->Slot090();
                    pCard->Slot088();
                } else {
                    cSPMission* pMission = (cSPMission*)pSlot->GetObject(0x14066ce5);
                    if (pMission != nullptr) {
                        void* pCities = pMission->GetOwnerEmpire();
                        if (pCities != nullptr)
                            sText.assign((const wchar_t*)pCities, (const wchar_t*)pCities);
                    }
                    FUN_006668e0(gDefaultCardColors, gDefaultCardColors + 1,
                                 gDefaultCardColors + 2);
                    FUN_00febf80(pMission);
                    FUN_00666a40(pSlot);
                }
                FUN_00668000(sText.mpBegin);
            }
        }
        if (mnMissionType == 0x1654c05) {
            FUN_006644e0(FUN_00664600() != 0);
        } else {
            FUN_00664580(FUN_00664600() != 0);
        }
        FUN_00664580(FUN_00664600() != 0);
    }

    FeedItem* pItem = mpCategoryA->Find(mnSelected + 0x6146391);
    if (pItem == nullptr)
        pItem = mpCategoryB->Find(mnSelected + 0x6146391);
    if (pItem != nullptr)
        mpFeedList->Select(pItem);

    SetTracked();
}

// ---------------------------------------------------------------------------
// mission message handler
// ---------------------------------------------------------------------------
class cUIMissionsHandler {
public:
    bool DoMessage(void* pMessage, int32_t nParam);     // 0x00e1d7a0

    uint8_t mPad00[0x84];           // +0x000
    uint32_t mnLastButton;          // +0x084
    int32_t mnCardIndex;            // +0x088
    uint32_t mnButtonId;            // +0x08c
};

void* __cdecl FUN_00e1a1a0();                       // 0x00e1a1a0
void* __cdecl FUN_00b3d400();                       // 0x00b3d400
bool __cdecl FUN_00fec960(cSPMission* pMission);    // 0x00fec960
void __cdecl FUN_00febe00(cSPMission* pMission);    // 0x00febe00
void __cdecl FUN_00e18200(void* pMission, int32_t nA, int32_t nB, int32_t nC);  // 0x00e18200
void __cdecl FUN_00809db0(void* pTarget, const uint32_t* pColor);   // 0x00809db0
void* __cdecl FUN_00e39ab0(uint32_t nType, int32_t nA, void* pB, void* pC,
                           int32_t nD, int32_t nE, void* pF, void* pG);    // 0x00e39ab0

struct MissionMessage {
    IWindow* mpSender;          // +0x00
    uint32_t mPad04;            // +0x04
    uint32_t mnMessageType;     // +0x08
};

// @ 0x00e1d7a0
bool cUIMissionsHandler::DoMessage(void* pMessage, int32_t nParam)
{
    MissionMessage* pMsg = (MissionMessage*)pMessage;
    if (pMsg->mnMessageType != 0x287259f6)
        return false;

    uint32_t nButtonId = pMsg->mpSender->GetID();

    if (nButtonId == 0x3c4925e) {
        mnButtonId = 0xbf7ce923;
        uint32_t colors[3] = { 0xbf7ce923, 0xb1b104, 0xf5f6fde8 };
        FUN_00809db0((uint8_t*)this + 0x38, colors);
        return true;
    }

    if (nButtonId == 0x51d2fb8) {
        bool bPressed = (pMsg->mpSender->GetState() & 4) == 4;
        void* pMission = FUN_00e1a1a0();
        if (pMission == nullptr)
            return true;
        cUIMissionCardPanel* pPanel = (cUIMissionCardPanel*)FUN_00b3d400();
        if (pPanel == nullptr)
            return true;

        if (bPressed) {
            FUN_00febe00((cSPMission*)pMission);
            if (FUN_00fec960((cSPMission*)pMission)) {
                FUN_00e18200(pMission, 0, 1, 0);
            } else {
                mnButtonId = 0x29bcd888;
                uint32_t colors[3] = { 0x29bcd888, 0xb1b104, 0xf5f6fde8 };
                FUN_00809db0((uint8_t*)this + 0x38, colors);
                pMsg->mpSender->SetFlags(4, 0);
            }
        } else {
            FUN_00febe00((cSPMission*)pMission);
        }

        FeedItem* pItem = ((FeedListCategory*)mnCardIndex)->Find(mnButtonId + 0x6146391);
        if (pItem != nullptr) {
            FUN_00febf80((cSPMission*)pMission);
            FUN_00666a40(pItem);
        }
        return true;
    }

    if (nButtonId != 0x67a2878 && nButtonId != 0x67a2ae0
        && nButtonId != 0x67a2b48 && nButtonId != 0x67a2be0)
        return false;

    uint32_t nId = pMsg->mpSender->GetID();
    if (nId == mnLastButton)
        return false;
    mnLastButton = nId;
    ((cUIMissionCardPanel*)((uint8_t*)this - 0x08))->Refresh();
    return true;
}

// ---------------------------------------------------------------------------
// space trading tab
// ---------------------------------------------------------------------------
extern const uint32_t gaTradingWindowIds[3];        // 0x01480300

class cTradeUI {
public:
    void Activate();                    // 0x00e1dae0
    void* Destroy(uint32_t nFlags);     // 0x00e1dc20

    void* mpVtbl0;              // +0x000  first base vtable
    void* mpTraceVtbl;          // +0x004  tracer base vtable
    cSPUILayout mLayout;        // +0x008
    bool mbInitialized;         // +0x020
};

// the second base subobject of the trading tab (its `this` is gTradeUI+4)
class cUITradingActivity {
public:
    void Deactivate(uint32_t nReason);                  // 0x00e1db60
    void SetMission(void* pMission, int32_t nReason);   // 0x00e1dc80

    cTradeUI* Owner() const { return (cTradeUI*)((uint8_t*)this - 4); }

    uint8_t mPad00[0x04];       // +0x000  (gTradeUI+0x04)
    cSPUILayout mLayout;        // +0x004  (gTradeUI+0x008)
};

extern cTradeUI gTradeUI;                       // 0x015a51b4
extern cUITradingActivity gTradingActivity;     // 0x015a51b8

void __cdecl FUN_00e1dbd0();        // 0x00e1dbd0

// @ 0x00e1dbd0
void FUN_00e1dbd0()
{
    if (gTradeUI.mbInitialized) {
        IWindow* pWindow = gTradeUI.mLayout.FindWindowByID(0x7d4c266, 1);
        if (pWindow != nullptr) {
            pWindow->SetMode(1, 0);
            SPUIHelpers_EndModal(pWindow, 0, 1);
        }
        gTradeUI.mbInitialized = false;
        gTradeUI.mLayout.Shutdown(1);
    }
}

// @ 0x00e1dae0
void cTradeUI::Activate()
{
    if (!mbInitialized) {
        mLayout.Init(L"ScenarioNameCaptain", 0x40464100, true, 0x5b598fa);
        IWindow* pWindow = mLayout.FindWindowByID(0x7d4c266, 1);
        if (pWindow != nullptr) {
            pWindow->SetMode(1, 1);
            void* pContext = (void*)&mpTraceVtbl;
            SPUIHelpers_BeginModal(pWindow, pContext, true);
            IWindow* pSecond = mLayout.FindWindowByID(0x7d4de46, 1);
            if (pSecond != nullptr)
                pSecond->SetMode(2, 0);
        }
        mbInitialized = true;
    }
}

// @ 0x00e1db60
void cUITradingActivity::Deactivate(uint32_t nReason)
{
    cGameTimeManager* pTime = GameTimeManager();
    pTime->IncPauseGate(0x4bf38a7);

    // the window-id block is walked as three raw dwords
    cSPUILayout* pLayout = &mLayout;
    for (uint32_t nOffset = 0; nOffset < 3 * sizeof(uint32_t); nOffset += sizeof(uint32_t)) {
        IWindow* pWindow = pLayout->FindWindowByID(
            *(const uint32_t*)((size_t)(const void*)gaTradingWindowIds + nOffset), 1);
        if (pWindow != nullptr)
            pWindow->SetOwner(Owner());
    }
}

// @ 0x00e1dc20
void* cTradeUI::Destroy(uint32_t nFlags)
{
    mpVtbl0 = (void*)0x1480344;
    mpTraceVtbl = (void*)0x1480338;
    mLayout.Shutdown(1);
    mLayout.Destroy();
    mpVtbl0 = (void*)0x13eb938;
    if ((nFlags & 1) != 0)
        operator_delete_array(this);
    return this;
}

// @ 0x00e1dc70
void FUN_00e1dc70()
{
    FUN_00e1dbd0();
    gTradeUI.Activate();
}

void* __cdecl FUN_005bf3a0(void* pSource, int32_t nFlags);          // 0x005bf3a0
void __cdecl FUN_00eebf90(void* pAsset, const wchar_t* pszText);    // 0x00eebf90

// @ 0x00e1dc80
void cUITradingActivity::SetMission(void* pMission, int32_t nReason)
{
    GameTimeManager()->DecPauseGate(0x4bf38a7);

    if (nReason == 1) {
        IWindow* pWindow = mLayout.FindWindowByID(0x7d4c4be, 1);
        if (pWindow != nullptr) {
            IWindow* pCard = (IWindow*)pWindow->GetObject(0xcf428691);
            if (pCard != nullptr) {
                void* pAsset = FUN_005bf3a0((void*)0x15a51d8, 0);
                const wchar_t* pszCaption = pCard->GetCaption();
                FUN_00eebf90(pAsset, pszCaption);
                FUN_00e39ab0(0xbbc2a4ef, 0, nullptr, nullptr, 0, 0, nullptr, pAsset);
            }
        }
    }

    const uint32_t* pEnd = gaTradingWindowIds + 3;
    for (const uint32_t* p = gaTradingWindowIds; p != pEnd; ++p) {
        IWindow* pWindow = mLayout.FindWindowByID(*p, 1);
        if (pWindow != nullptr)
            pWindow->OnActivate(Owner());
    }
}

// @ 0x00e1de60
bool __stdcall FUN_00e1de60(WString* pString)
{
    WString temp;
    bool bChanged = false;

    if (pString->size() != 0) {
        for (uint32_t i = 0; i < pString->size(); ++i) {
            wchar_t wc = pString->mpBegin[i];
            if (!FUN_004f56f0(wc))
                bChanged = true;
            else
                temp.push_back(wc);
        }
        if (bChanged && &temp != pString)
            pString->assign(temp.mpBegin, temp.mpEnd);
    }
    return bChanged;
}
