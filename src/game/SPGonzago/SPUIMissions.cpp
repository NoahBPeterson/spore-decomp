// src/game/SPGonzago/SPUIMissions.cpp -- migrated from slice(s) s00e2e6e0, s00e1d020, s00e19dd0, s00e17c10, s00e14a30 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIMissions.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameData.h"
#include "SP/cSPMission.h"
#include "SP/cString.h"
#include "SP/cRelationshipManager.h"
#include "cSPUILayout.h"
#include "SP/cViewer.h"

// ---- items of slice s00e14a30 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
typedef unsigned long uintptr_t32;
class cUICard;
bool CardLessThan(cUICard* pLeft, cUICard* pRight);
namespace EA {
template <class T>
struct RectT_s00e1_4a30 {
    T mLeft;
    T mTop;
    T mRight;
    T mBottom;
};  // namespace EA
}
struct IWindow;
struct IRefCounted {
    virtual void AddRef();
    virtual void Release();
};
class cSPUILayout_s00e1_4a30 {
public:
    virtual void v00();
    virtual void AddRef();
    virtual void Release();

    bool SetVisibility(bool visible);  // 0x00810590 (cSPUILayout::SetVisibility)
    bool Init(const wchar_t* pName, uint32_t instanceId, bool bFlag, uint32_t resourceId);  // 0x00812160 (cSPUILayout::Init)
    bool Init(const void* pKey, bool bFlag, uint32_t resourceId);  // 0x008120d0 (cSPUILayout::Init)
    IWindow* FindWindowByID(uint32_t windowId, bool bRecursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)

    // +0x00 vftable, rest opaque.
    void* mvUnused04;
};
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
    virtual EA::RectT_s00e1_4a30<float>* GetArea();                           // 0x38
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
class cSPUIAnimator_s00e1_4a30 {
public:
    cSPUIAnimator_s00e1_4a30();
    void* mvState[7];
};
class MissionCardAnimator : public cSPUIAnimator_s00e1_4a30 {
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
};  // namespace UI
}
template <class T>
struct AutoRefCount {
    T* mpObject;

    T* Get() const { return mpObject; }
    operator T*() const { return mpObject; }
};
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
    AutoRefCount<cSPUILayout_s00e1_4a30> mLayout;         // 0x1c
    AutoRefCount<IWindow> mpMainWin;           // 0x24
    cSPUIAnimator_s00e1_4a30* mpAnimator;                 // 0x28
    AutoRefCount<IWindow> mpDescriptionWin;    // 0x2c
    AutoRefCount<IWindow> mpBackgroundWin;     // 0x30
    AutoRefCount<IWindow> mpClipFrameWin;      // 0x34
    AutoRefCount<IWindow> mpCompletedBackgroundWin;  // 0x38
    AutoRefCount<IWindow> mpMissionIconWin;    // 0x3c
    AutoRefCount<IWindow> mpJournalIconWin;    // 0x40
    uint32_t mPad44;
    EA::RectT_s00e1_4a30<float> mIconArea;                // 0x48
    EA::RectT_s00e1_4a30<float> mBackgroundInitialArea;   // 0x58
    EA::RectT_s00e1_4a30<float> mClipFrameInitialArea;    // 0x68
    EA::RectT_s00e1_4a30<float> mCompletedBackgroundInitialArea;  // 0x78
    EA::RectT_s00e1_4a30<float> mDescriptionInitialArea;  // 0x88
};
typedef AutoRefCount<cUICard> CardRef;
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
    cSPUILayout_s00e1_4a30* GetPanelLayout();                        // 0x00e14c70
    void SetPanelArea(EA::RectT_s00e1_4a30<float> area);             // 0x00e14d00
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
    AutoRefCount<cSPUILayout_s00e1_4a30> mPanelBackdrop;   // 0x3c
    void* mpMsgHandler;                         // 0x40
    int mHandlerOwner;                          // 0x44
    int mHandlerId;                             // 0x48
    int mHandlerCount;                          // 0x4c
    int mHandlerExtra;                          // 0x50
    AutoRefCount<cSPUILayout_s00e1_4a30> mPanelLayout;     // 0x54
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
void* FindGameData();
struct cScenarioProgressBar;
class cGameData {
public:
    uint8_t mPad00[0x78];
    cScenarioProgressBar* mpProgressBar;   // 0x78
    uint8_t mPad7c[0x54];
    int mModeState;                        // 0xd0
};
class cScenarioProgressBar {
public:
    int GetCount();
    uint8_t GetByte(int index);
    uint8_t GetKind(int index);
    float GetProgressF();
};
void* operator new(size_t size, const char* pSource, int a, int b, int c, int d);
bool IsJournalOpen();
// ---- items of slice s00e14a30 end

// ---- items of slice s00e17c10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  *SP_GetCurrentGameMode();                  // 0x00b5b800
extern "C" void  *FUN_00921580(void *node);                 // 0x00921580 RBTreeIncrement
extern "C" float  SPUI_GetElapsedSeconds();                 // 0x00805080
extern "C" bool   FUN_007f6340(void *animator);             // 0x007f6340 cSPUIAnimator::Empty
extern "C" void   FUN_007f63b0(void *animator);             // 0x007f63b0 cSPUIAnimator::Update
extern "C" bool   FUN_00c44c90(void *mission);              // 0x00c44c90
extern "C" bool   FUN_00e15060(void *card, char b);         // 0x00e15060 cUICard::Init
extern "C" void  *FUN_00e147a0(void *o);                     // 0x00e147a0
extern "C" void   FUN_00aea5d0(void **v, void *last, void *val); // 0x00aea5d0 vector push_back
extern "C" void   FUN_00e14b70(void *panel);                 // 0x00e14b70 UpdateCardPositions
extern "C" void   FUN_00e49360(void *o, void *v);            // 0x00e49360
extern "C" void  *FUN_006c0200(void *o);                     // 0x006c0200
extern "C" void   FUN_006782c0(void *first, void *last, void *dst); // 0x006782c0 copy
extern "C" void  *MessageServer();                           // 0x0067dcc0
typedef unsigned int   u32;
typedef unsigned char  u8;
extern "C" void   FUN_00571db0(u32 a, u32 b, u32 c, u32 d, u32 e); // 0x00571db0 RemoveHandler
extern "C" void  *operator_new(u32 size, u32 file, u32 line, u32 a, u32 b, u32 c); // 0x00f473a0
extern "C" void   FUN_00e168d0(void *card, u32 mission, u32 b);  // 0x00e168d0
extern "C" void   FUN_00e30990(void *o, u32 arg);           // 0x00e30990
struct cUIMissionCard {
    u8   m_pad00[0x10];
    u8   m_collapsed;       // +0x10
    u8   m_animated;        // +0x11
    u8   m_pad12[0x16];
    void *m_animator;       // +0x28
    u8   m_pad2c[0x70];
    void *m_mission;        // +0x9c

    void DoCollapse();      // 0x00e17d60
    void DoExpand();        // 0x00e17cf0
    void UpdateDetails(char flag); // 0x00e17c10
    void Update();          // 0x00e17d70
    void Setup(void *mission, char a, char b); // 0x00e17f40
    void UpdateFromMission(void *m); // 0x00e16090
    void SetMissionSub(void *m);     // 0x00e17570
    void InitForCreature(int a, int state); // 0x00e133b0
    void ResizeToContent(int a, int state); // 0x00e13b50
};
struct cPanelHead0c {               // +0x00
    void **m_vtbl00;                // +0x00
    void  *m_sub04;                 // +0x04
    void  *m_slotVtbl08;            // +0x08
};
struct cPanelMsg0c {                // +0x0c  (OnMessage's this)
    void  *m_slotVtbl0c;            // +0x0c
    u32    m_field10;               // +0x10
    void  *m_field14;               // +0x14
    void  *m_layout;                // +0x18
    void  *m_card;                  // +0x1c

    char   OnMessage(u32 msg, void *arg); // 0x00e18600
};
struct cPanelMsg24 {                // +0x20
    void  *m_handlerObj;            // +0x20
};
struct cPanelHandler24 {            // +0x24  (HandleMessage's this)
    void  *m_handlerArg1;           // +0x24

    char   HandleMessage(u32 msg, void *arg); // 0x00e18380
};
struct cUIMissionCardPanel_s00e1_7c10 : cPanelHead0c, cPanelMsg0c, cPanelMsg24, cPanelHandler24 {
    union {                 // +0x28: message-handler view / card-vector view
        struct {
            void *m_handlerArg2; // +0x28
            u32   m_handlerN;    // +0x2c
            void *m_handlerArg4; // +0x30
        };
        struct {
            void **m_vec28;      // +0x28 vector begin
            void **m_vec2c;      // +0x2c vector end
            union {              // +0x30: vector capacity / layout object
                void **m_vec30;
                void  *m_visObj;
            };
        };
    };
    void *m_treeBegin34;    // +0x34
    void *m_curMission;     // +0x38
    void *m_field3c;        // +0x3c
    void *m_treeBase40;     // +0x40
    u8    m_pad44[0x14];
    void *m_field58;        // +0x58
    void *m_field5c;        // +0x5c
    u8    m_pad60[0x14];
    void *m_tree74;         // +0x74

    void SetVisibleSlot(int v);          // 0x00e18860
    void ShutdownCard();                 // 0x00e18810
    void ClearTree();                    // 0x00e18a90
    void *FindMission(u32 id);           // 0x00e18b10
    bool  ShouldShow(u32 id);            // 0x00e18c70
    void  ForEach(u32 a, u32 b);         // 0x00e18ac0
    void  Refresh();                     // 0x00e17df0
    void  UpdateCardDetails(void *mission); // 0x00e17e40
    void  ShutdownA();                   // 0x00e18a30
    void  ShutdownB();                   // 0x00e18b50
    void  SetSlotAndMission(u32 slot); // 0x00e18cb0
    void *InitHints(void *param);        // 0x00e188b0
    void  DestroyMembers();              // 0x00e18980
    void *Construct();                   // 0x00e18bb0
    bool  RemoveMissionCard(void *mission); // 0x00e17fb0
    void *AddMissionCard(u32 mission);   // 0x00e18150
    void *SetupMissionCard(void *mission, u32 a, u32 b, char c); // 0x00e18200
    void  RefreshFromMissionList();      // 0x00e184d0
    void  OnNotify(u32 a, u32 b, u32 c, u32 d); // 0x00e186d0
};
void cUIMissionCardPanel_s00e1_7c10::ForEach(u32 a, u32 b)
{
    if (m_field58 != 0) {
        FUN_00e30990(m_field58, b);
    }
    void *node = m_treeBase40;
    void *base = (u8 *)this + 0x3c;
    while (node != base) {
        void *obj = *(void **)((u8 *)node + 0x14);
        ((void (__thiscall *)(void *, u32))(*(void ***)obj)[0x18 / 4])(obj, b);
        node = FUN_00921580(node);
    }
}
struct cUIMissionCardList {
    u8     m_pad00[0x28];
    void **m_vec28;         // +0x28 vector begin
    void **m_vec2c;         // +0x2c vector end
    u8     m_pad30[0xc];
    void  *m_field3c;       // +0x3c
    void  *m_handler40;     // +0x40
    u32    m_h44, m_h48, m_h4c, m_h50; // +0x44..+0x50
    void  *m_field54;       // +0x54

    void ReleaseAll();                   // 0x00e180d0
    void RemoveHandlerAndRelease();      // 0x00e18340
};
// ---- items of slice s00e17c10 end

// ---- items of slice s00e19dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct CIndexedArray
{
    /* 000h */ uint8_t   mPad_000[0x44];
    /* 044h */ uint32_t* mBegin_44;   // array begin
    /* 048h */ uint32_t* mEnd_48;     // array end
    /* 04ch */ uint8_t   mPad_04c[0x90 - 0x4c];
    /* 090h */ int32_t   mIndex_90;   // current index
};
// ---- items of slice s00e19dd0 end

// ---- items of slice s00e1d020 begin (TODO(rewrite): local stubs, replace by canonical classes)
class IWindow_s00e1_d020 {
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
class cString_s00e1_d020 {
public:
    cString_s00e1_d020(uint32_t nTable, uint32_t nIndex, const wchar_t* pszText);  // 0x006b5770
    ~cString_s00e1_d020();                                                         // 0x006b5240
    const wchar_t* GetText();                                           // 0x006b55c0
private:
    uint8_t mPad00[0x14];
};  // namespace SP
}
class SlotVector {
public:
    void** mpBegin;             // +0x00
    void** mpEnd;               // +0x04
    void** mpCapacity;          // +0x08
    void Erase(void** pFirst, void** pLast);        // 0x00e25bd0
};
class cUIMissionCardPanel_s00e1_d020 {
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
// ---- items of slice s00e1d020 end

// ---- items of slice s00e2e6e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*  g_stripVtable[];          // 0x01481804 the strip object's own vtable
void*    __cdecl FUN_00810000(void* pThis);                            // 0x00810000
class tIWindow;
class tIWindowEx;
class tIWindow {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04 Release
    virtual void* v08();                        // +0x08
    virtual void* v0c(uint32_t nKey);           // +0x0c
    virtual void* v10();                        // +0x10
    virtual void  v14(void* pState);            // +0x14
    virtual void  v18();                        // +0x18
    virtual void  v1c();                        // +0x1c
    virtual void  v20();                        // +0x20
    virtual void  v24();                        // +0x24
    virtual void  v28(int32_t nState);          // +0x28
    virtual void* v2c();                        // +0x2c
    virtual void  v30(int32_t nA, int32_t nB);  // +0x30
    virtual void*    v34();                     // +0x34
    virtual void*    v38();                     // +0x38
    virtual void*    v3c(uint32_t nKey, int32_t nFlag); // +0x3c
    virtual void*    v40();                     // +0x40
    virtual void*    v44();                     // +0x44
    virtual uint32_t v48();                     // +0x48
    virtual int32_t  v4c();                     // +0x4c
    virtual void*    v50();                     // +0x50
    virtual uint32_t v54();                     // +0x54
    virtual uint32_t v58();                     // +0x58
    virtual void     v5c(int32_t nState);       // +0x5c sets the strip state
    virtual void     v60(int32_t nState);       // +0x60
    virtual void     v64();                     // +0x64
    virtual void     v68();                     // +0x68
    virtual void     v6c();                     // +0x6c
    virtual float    v70();                     // +0x70
    virtual void     v74();                     // +0x74
    virtual void     v78();                     // +0x78
    virtual void     v7c(int32_t nA, int32_t nB); // +0x7c visible/state pair
    virtual void     v80();                     // +0x80
    virtual void     v84();                     // +0x84
    virtual void     v88();                     // +0x88
    virtual void     v8c(void* pValue);         // +0x8c
    virtual void     v90();                     // +0x90
    virtual void     v94();                     // +0x94
    virtual void*    v98();                     // +0x98
    virtual void*    v9c();                     // +0x9c
    virtual void*    va0();                     // +0xa0
    virtual void*    va4();                     // +0xa4
    virtual void*    va8();                     // +0xa8
    virtual void*    vac();                     // +0xac
    virtual void*    vb0();                     // +0xb0
    virtual void*    vb4();                     // +0xb4
    virtual void*    vb8();                     // +0xb8
    virtual void*    vbc();                     // +0xbc
    virtual void*    vc0();                     // +0xc0
    virtual void*    vc4();                     // +0xc4
    virtual void*    vc8();                     // +0xc8
    virtual void*    vcc();                     // +0xcc
    virtual void*    vd0();                     // +0xd0
    virtual void*    vd4();                     // +0xd4
    virtual void*    vd8();                     // +0xd8
    virtual void*    vdc();                     // +0xdc
    virtual void*    ve0();                     // +0xe0
    virtual void*    ve4();                     // +0xe4
    virtual void*    ve8();                     // +0xe8
    virtual void*    vec();                     // +0xec
    virtual void*    vf0(uint32_t nKey, int32_t nFlag); // +0xf0
};
class tIWindowEx : public tIWindow {
};
class tIProgressWindow {
public:
    virtual void*    v00();                     // +0x00
    virtual void*    v04();                     // +0x04
    virtual void*    v08();                     // +0x08
    virtual void*    v0c(uint32_t nKey);        // +0x0c
    virtual void*    v10();                     // +0x10
    virtual void     v14(void* pState);         // +0x14
    virtual void     v18();                     // +0x18
    virtual void     v1c();                     // +0x1c
    virtual void     v20();                     // +0x20
    virtual void     v24();                     // +0x24
    virtual void     v28(int32_t nState);       // +0x28
    virtual void     v2c();                     // +0x2c
    virtual void     v30(int32_t nA, int32_t nB);// +0x30
    virtual void*    v34();                     // +0x34
    virtual void*    v38();                     // +0x38
    virtual void*    v3c(uint32_t nKey, int32_t nFlag); // +0x3c
    virtual void*    v40();                     // +0x40
    virtual void*    v44();                     // +0x44
    virtual uint32_t v48();                     // +0x48
    virtual int32_t  v4c();                     // +0x4c
    virtual void*    v50();                     // +0x50
    virtual uint32_t v54();                     // +0x54 friendly count
    virtual uint32_t v58();                     // +0x58 neutral count
    virtual uint32_t v5c();                     // +0x5c hostile count
};
class cSPUILayout_s00e2_e6e0 {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08

    cSPUILayout_s00e2_e6e0* FUN_00810000();                                            // 0x00810000
    tIWindow* FindWindowByID(uint32_t nID, int32_t nFlag);                  // 0x008105b0
    bool      Init(const wchar_t* pName, uint32_t nColor, int32_t nA, int32_t nB); // 0x00812160
    bool      SetParentWin(tIWindow* pParent, int32_t nA, int32_t nB);      // 0x008121b0
    void      Shutdown(uint32_t nFlag);                                     // 0x00811ad0
};
class cSPUIRelationshipStrip {
public:
    uint32_t     mpVtable;          // +0x00 (0x01481804)
    uint32_t     mn04;              // +0x04
    cSPUILayout_s00e2_e6e0* mp08;              // +0x08 the strip layout

    void FUN_00e2ec40();                                            // 0x00e2ec40
    void Init(tIWindow* pParent);                                   // 0x00e2ec60
    void FUN_00e2ed40();                                            // 0x00e2ed40
    void FUN_00e2ed70(int32_t nState);                              // 0x00e2ed70
    void FUN_00e2ef80(float fAmount);                               // 0x00e2ef80
};
// ---- items of slice s00e2e6e0 end

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
        pCard->mLayout.mpObject = (cSPUILayout_s00e1_4a30*)&y;
        pMain->SetPosition(x, y);

        void* pExtent = pCard->mpCompletedBackgroundWin.mpObject->GetExtent();
        float* pFloats = (float*)pExtent;
        y = (pFloats[3] - pFloats[1]) + mCardSpacing + y;
    }
}

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

// @ 0x00e14c70
cSPUILayout_s00e1_4a30* cUIMissionCardPanel::GetPanelLayout()
{
    if (mPanelLayout.mpObject == nullptr) {
        static const uint32_t sLayoutKey[3] = {0x2ac364a7, 0x0510a95b, 0x40464100};
        cSPUILayout_s00e1_4a30* pOld = mPanelLayout.mpObject;
        cSPUILayout_s00e1_4a30* pNew = new ("Simulator", 0, 0, 0, 0) cSPUILayout_s00e1_4a30();
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

// @ 0x00e14d00
void cUIMissionCardPanel::SetPanelArea(EA::RectT_s00e1_4a30<float> area)
{
    if (mPanelBackdrop.mpObject == nullptr) {
        cSPUILayout_s00e1_4a30* pOld = mPanelBackdrop.mpObject;
        cSPUILayout_s00e1_4a30* pNew = new ("Simulator", 0, 0, 0, 0) cSPUILayout_s00e1_4a30();
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

// @ 0x00e15060
bool cUICard::Init(bool bVisible)
{
    cSPUILayout_s00e1_4a30* pOldLayout = mLayout.mpObject;
    cSPUILayout_s00e1_4a30* pNewLayout = new ("Simulator", 0, 0, 0, 0) cSPUILayout_s00e1_4a30();
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
        EA::RectT_s00e1_4a30<float>* pRect = mpDescriptionWin.mpObject->GetArea();
        mIconArea.mLeft = pRect->mLeft;
        mIconArea.mTop = pRect->mTop;
        mIconArea.mRight = pRect->mRight;
        mIconArea.mBottom = pRect->mBottom;
    }

    return true;
}

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

// @ 0x00e15b70
void cUIMissionCardPanel::ShowAllCards()
{
    if (!IsJournalOpen())
        SetCardsVisibility(true);
}

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

// @ 0x00e17c10
void cUIMissionCard::UpdateDetails(char flag)
{
    if (m_mission == 0) {
        return;
    }
    u32 mode = (u32)(unsigned long)SP_GetCurrentGameMode();
    switch (mode) {
    case 0x1654c00:
    case 0x1654c01:
    case 0x1654c02:
    case 0x1654c04: {
        void *pc = m_mission;
        void *sub;
        if (pc != 0) {
            sub = ((void *(__thiscall *)(void *, u32))(*(void ***)pc)[0x0c / 4])(pc, 0x14066ce5);
        } else {
            sub = 0;
        }
        UpdateFromMission(sub);
        break;
    }
    case 0x1654c05: {
        void *pc = m_mission;
        void *sub;
        if (pc != 0) {
            sub = ((void *(__thiscall *)(void *, u32))(*(void ***)pc)[0x0c / 4])(pc, 0x2aa5ada);
        } else {
            sub = 0;
        }
        SetMissionSub(sub);
        break;
    }
    }
    if (flag == 0) {
        int state;
        if (((bool (__thiscall *)(void *))(*(void ***)m_mission)[0x64 / 4])(m_mission)) {
            state = 1;
        } else if (((bool (__thiscall *)(void *))(*(void ***)m_mission)[0x68 / 4])(m_mission)) {
            state = 2;
        } else {
            state = 0;
        }
        if (m_collapsed != 0) {
            InitForCreature(1, state);
        } else {
            ResizeToContent(1, state);
        }
    }
}

// @ 0x00e17cf0
void cUIMissionCard::DoExpand()
{
    m_collapsed = 1;
    m_animated = 1;
    UpdateDetails(0);
    void *ms = MessageServer();
    ((void (__thiscall *)(void *, u32, void *))(*(void ***)ms)[0x14 / 4])(ms, 0xf46092d0, m_mission);
}

// @ 0x00e17d60
void cUIMissionCard::DoCollapse()
{
    m_collapsed = 0;
    m_animated = 1;
    UpdateDetails(0);
}

// @ 0x00e17d70
void cUIMissionCard::Update()
{
    SPUI_GetElapsedSeconds();
    if (m_animator != 0) {
        if (!((bool (__thiscall *)(void *))FUN_007f6340)(m_animator)) {
            m_animated = 1;
            ((void (__thiscall *)(void *))FUN_007f63b0)(m_animator);
        }
    }
    if ((u32)(unsigned long)SP_GetCurrentGameMode() == 0x1654c05) {
        void *sub;
        if (m_mission != 0) {
            sub = ((void *(__thiscall *)(void *, u32))(*(void ***)m_mission)[0x0c / 4])(m_mission, 0x2aa5ada);
        } else {
            sub = 0;
        }
        if (((bool (__thiscall *)(void *))FUN_00c44c90)(sub)) {
            u32 n = ((u32 (__thiscall *)(void *))(*(void ***)sub)[0xac / 4])(sub);
            if (n > 0) {
                UpdateDetails(1);
            }
        }
    }
}

// @ 0x00e17df0
void cUIMissionCardPanel_s00e1_7c10::Refresh()
{
    int n = (int)(m_vec2c - m_vec28);
    for (int i = 0; i < n; i++) {
        void *card = m_vec28[i];
        if (card == 0) {
            continue;
        }
        void *sub = ((void *(__thiscall *)(void *, u32))(*(void ***)card)[0x0c / 4])(card, 0x334c6eec);
        if (sub != 0) {
            ((cUIMissionCard *)sub)->UpdateDetails(0);
        }
    }
}

// @ 0x00e17e40
void cUIMissionCardPanel_s00e1_7c10::UpdateCardDetails(void *mission)
{
    int count = (int)(m_vec2c - m_vec28);
    for (int i = 0; i < count; i++) {
        void *card = m_vec28[i];
        if (card == 0) {
            continue;
        }
        void *sub = ((void *(__thiscall *)(void *, u32))(*(void ***)card)[0x0c / 4])(card, 0x334c6eec);
        if (sub == 0) {
            continue;
        }
        if (*(void **)((u8 *)sub + 0x9c) != mission) {
            continue;
        }
        ((cUIMissionCard *)sub)->UpdateDetails(0);
    }
}

// @ 0x00e17f40
void cUIMissionCard::Setup(void *mission, char a, char b)
{
    if (!((bool (__thiscall *)(void *, char))FUN_00e15060)(this, b)) {
        return;
    }
    if (mission != m_mission) {
        if (mission != 0) {
            ((void (__thiscall *)(void *))(*(void ***)mission)[0])(mission);
        }
        void *old = m_mission;
        m_mission = mission;
        if (old != 0) {
            ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
        }
    }
    UpdateDetails(0);
    void **vt = *(void ***)this;
    if (a != 0) {
        ((void (__thiscall *)(void *))vt[0x28 / 4])(this);
    } else {
        ((void (__thiscall *)(void *))vt[0x2c / 4])(this);
    }
}

// @ 0x00e17fb0
bool cUIMissionCardPanel_s00e1_7c10::RemoveMissionCard(void *mission)
{
    void **end = m_vec2c;
    for (void **it = m_vec28; it != end; ++it) {
        void *card = *it;
        if (card == 0) {
            continue;
        }
        void *sub = ((void *(__thiscall *)(void *, u32))(*(void ***)card)[0x0c / 4])(card, 0x334c6eec);
        if (sub == 0) {
            continue;
        }
        if (*(void **)((u8 *)sub + 0x9c) != mission) {
            continue;
        }
        if (m_field3c != 0) {
            if (((void *(__thiscall *)(void *))FUN_006c0200)(m_field3c) == sub) {
                ((void (__thiscall *)(void *, void *))FUN_00e49360)(m_field3c, 0);
            }
        }
        ((void (__thiscall *)(void *))(*(void ***)sub)[0x1c / 4])(sub);
        void **next = it + 1;
        if (next < m_vec2c) {
            FUN_006782c0(it, m_vec2c, next);
        }
        m_vec2c = m_vec2c - 1;
        void *tail = *m_vec2c;
        if (tail != 0) {
            ((void (__thiscall *)(void *))(*(void ***)tail)[1])(tail);
        }
        ((void (__thiscall *)(void *))FUN_00e14b70)(this);
        return true;
    }
    return false;
}

// @ 0x00e18150
void *cUIMissionCardPanel_s00e1_7c10::AddMissionCard(u32 mission)
{
    void *raw = operator_new(0x9c, 0x13f6b3c, 0, 0, 0, 0);
    void *card = 0;
    if (raw != 0) {
        card = ((void *(__thiscall *)(void *))FUN_00e147a0)(raw);
    }
    void *addref = card;
    if (card != 0) {
        ((void (__thiscall *)(void *))(*(void ***)card)[0])(card);
    }
    if (m_vec2c < m_vec30) {
        void **slot = m_vec2c;
        m_vec2c = slot + 1;
        if (slot != 0) {
            *slot = card;
            if (card != 0) {
                ((void (__thiscall *)(void *))(*(void ***)card)[0])(card);
            }
        }
    } else {
        FUN_00aea5d0((void **)&m_vec28, m_vec2c, &addref);
    }
    if (addref != 0) {
        ((void (__thiscall *)(void *))(*(void ***)addref)[1])(addref);
    }
    ((void (__thiscall *)(void *, u32, u32))FUN_00e168d0)(card, mission, 0);
    ((void (__thiscall *)(void *))FUN_00e14b70)(this);
    return card;
}

// @ 0x00e18340
void cUIMissionCardList::RemoveHandlerAndRelease()
{
    ReleaseAll();
    if (m_handler40 != 0) {
        u32 h = (u32)m_handler40;
        m_handler40 = 0;
        FUN_00571db0(h, m_h44, m_h48, m_h4c, m_h50);
    }
}

// @ 0x00e1a1a0
uint32_t __fastcall FUN_00e1a1a0(CIndexedArray* pThis)
{
    int32_t iIndex = pThis->mIndex_90;
    if ((iIndex >= 0) && (iIndex < (int32_t)(pThis->mEnd_48 - pThis->mBegin_44)))
        return pThis->mBegin_44[iIndex];
    return 0;
}

// @ 0x00e1d610
void cUIMissionCardPanel_s00e1_d020::SetSlot(void* pMission)
{
    SetVisibleSlot(pMission);

    if (GetUIHints() != nullptr)
        GetUIHints()->SetFlag(0, 1);

    Refresh();

    if (mpFeedList != nullptr)
        mpFeedList->SetPaused(true);

    SP::cString_s00e1_d020 str(0x8b96f855, 0x60c9908, nullptr);
    SetTitle(str.GetText());

    if (pMission != nullptr) {
        IWindow_s00e1_d020* pMissionWindow = (IWindow_s00e1_d020*)pMission;
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

// @ 0x00e1d710
void cMissionSlot::OnNotify(void* pSender, uint32_t nMessage)
{
    if (pSender != nullptr) {
        IWindow_s00e1_d020* pWindow = (IWindow_s00e1_d020*)pSender;
        if (pWindow->GetOwner() != nullptr)
            ((IWindow_s00e1_d020*)pWindow->GetOwner())->SetParent(pSender);
    }

    if (mnMessage == (int32_t)0xbf7ce923 && (int32_t)nMessage == 0x5107b1a
        && mnSelected >= 0 && mnSelected < (int32_t)(mppEnd - mppBegin)) {
        IWindow_s00e1_d020* pSlot = (IWindow_s00e1_d020*)mppBegin[mnSelected];
        if (pSlot != nullptr) {
            void* pMission = pSlot->GetObject(0x2aa5ada);
            if (pMission != nullptr) {
                FUN_00c485d0();
                ((cUIMissionCardPanel_s00e1_d020*)((uint8_t*)this - 0x40))->Refresh();
            }
        }
    }
    mnMessage = 0;
}

// @ 0x00e2e790
void __cdecl UpdateProgessIcons(cSPUILayout_s00e2_e6e0* pLayout, tIWindowEx* pWindow)
{
    if (pLayout == 0 || pWindow == 0)
        return;

    tIProgressWindow* pCounts = (tIProgressWindow*)pWindow;
    uint32_t nFriendly = pCounts->v54();
    uint32_t nNeutral = pCounts->v58();
    uint32_t nHostile = pCounts->v5c();
    uint32_t i = 0;
    tIWindowEx* pSlot = (tIWindowEx*)pLayout->FindWindowByID(0xf4440000, 1);
    while (pSlot != 0)
    {
        tIWindowEx* pIcon = (tIWindowEx*)pSlot->v0c(0x0105a93d);
        if (pIcon != 0)
        {
            if (i < nFriendly)
            {
                pSlot->v7c(1, 1);
                pIcon->v14((void*)0);
            }
            else if (i < nNeutral)
            {
                pSlot->v7c(1, 1);
                pIcon->v14((void*)1);
            }
            else if (i < nHostile && nHostile > 0)
            {
                pSlot->v7c(1, 1);
                pIcon->v14((void*)2);
            }
            else
            {
                pSlot->v7c(1, 0);
            }
        }
        ++i;
        pSlot = (tIWindowEx*)pLayout->FindWindowByID(0xf4440000 + i, 1);
    }
}

// @ 0x00e2ec40
void cSPUIRelationshipStrip::FUN_00e2ec40()
{
    mn04 = 0;
    mpVtable = (uint32_t)g_stripVtable;
    mp08 = 0;
}
