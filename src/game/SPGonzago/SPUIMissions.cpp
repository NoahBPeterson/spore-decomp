// src/game/SPGonzago/SPUIMissions.cpp -- migrated from slice(s) s00e1bbc0, s00e18d40, s00e16a70, s00e15c00, s00e13b50, s00e12f80, s00e2e6e0, s00e1d020, s00e19dd0, s00e17c10, s00e14a30 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIMissions.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameData.h"
#include "SP/cSPMission.h"
#include "SP/cString.h"
#include "SP/cRelationshipManager.h"
#include "cSPUILayout.h"
#include "SP/cViewer.h"
#include <math.h>
#include "cSPUIAnimator.h"
#include "EA/LimitStopwatch.h"
#include "SP/cIGonzagoSubsystem.h"
#include "SP/cSPUIFeedList.h"

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
extern "C" void   FUN_00811ad0(void *layout, int f);        // 0x00811ad0 cSPUILayout::Shutdown
extern "C" void  *FUN_00921580(void *node);                 // 0x00921580 RBTreeIncrement
extern "C" float  SPUI_GetElapsedSeconds();                 // 0x00805080
extern "C" bool   FUN_007f6340(void *animator);             // 0x007f6340 cSPUIAnimator::Empty
extern "C" void   FUN_007f63b0(void *animator);             // 0x007f63b0 cSPUIAnimator::Update
extern "C" bool   FUN_00c44c90(void *mission);              // 0x00c44c90
extern "C" bool   FUN_00e15060(void *card, char b);         // 0x00e15060 cUICard::Init
extern "C" void   FUN_00e25bd0(void *vec, void *first, void *last); // 0x00e25bd0 vector::erase
extern "C" void   FUN_00e492d0(void *o);                    // 0x00e492d0
extern "C" void  *FUN_00e147a0(void *o);                     // 0x00e147a0
extern "C" void  *FUN_00e141a0(void *o);                     // 0x00e141a0
extern "C" void  *FUN_00e4a6e0(void *o);                     // 0x00e4a6e0
extern "C" void   FUN_00aea5d0(void **v, void *last, void *val); // 0x00aea5d0 vector push_back
extern "C" void   FUN_00e14b70(void *panel);                 // 0x00e14b70 UpdateCardPositions
extern "C" void   FUN_00e49360(void *o, void *v);            // 0x00e49360
extern "C" void   FUN_00e49a40(void *o, void *v);            // 0x00e49a40
extern "C" void  *FUN_006c0200(void *o);                     // 0x006c0200
extern "C" void   FUN_006782c0(void *first, void *last, void *dst); // 0x006782c0 copy
extern "C" bool   FUN_00c44c80(void *mission);               // 0x00c44c80 cSPMission::IsActive
extern "C" void  *FUN_00febc70(void *mgr);                   // 0x00febc70
extern "C" void  *GetMissionManager();                       // 0x00feb9f0
extern "C" void  *FUN_00fedd50(void *mgr);                   // 0x00fedd50 GetMissionList
extern "C" void  *SP_SpaceGameGet();                         // 0x01002bd0
extern "C" void  *FUN_00bfc5f0(void *o);                     // 0x00bfc5f0 SetGameDataOwner2
extern "C" void  *FUN_00575ea0(void *o);                     // 0x00575ea0 GetDefaultIconDrawable
extern "C" bool   FUN_00e15cd0(void *panel, void *mission);  // 0x00e15cd0 HasMissionCard
extern "C" void   FUN_00e15c70(void *panel, void *mission);  // 0x00e15c70 CollapseOtherMissionCards
extern "C" void  *MessageServer();                           // 0x0067dcc0
typedef unsigned int   u32;
typedef unsigned char  u8;
extern "C" void   FUN_00571db0(u32 a, u32 b, u32 c, u32 d, u32 e); // 0x00571db0 RemoveHandler
extern "C" void  *operator_new(u32 size, u32 file, u32 line, u32 a, u32 b, u32 c); // 0x00f473a0
extern "C" void   FUN_00e168d0(void *card, u32 mission, u32 b);  // 0x00e168d0
extern "C" void   FUN_00e18050(void **a, void **b, u32 c);    // 0x00e18050
extern "C" bool   FUN_00febe50(void *mgr, void *mission, u32 b); // 0x00febe50
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
extern wchar_t gEmptyString16[];                                // 0x01667bac
extern uint32_t gDefaultCardColors[3];              // 0x015a50d4
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
void __cdecl operator_delete_array(void* pBlock);               // 0x00f47380
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
class cSPMission_s00e1_d020 {
public:
    bool IsVisibleInUI();           // 0x00c45340
    bool IsActive();                // 0x00c44c80
    void* GetOwnerEmpire();  // 0x00c451e0 (cSPMission::GetOwnerEmpire)

    void* mpVtbl;                   // +0x000
    uint8_t mPad04[0x178];          // +0x004
    uint32_t mnFlags;               // +0x17c
};
struct MissionList {
    cSPMission_s00e1_d020** mpBegin;           // +0x00
    cSPMission_s00e1_d020** mpEnd;             // +0x04
};
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
MissionList* __cdecl FUN_009892e0();                // 0x009892e0
uint32_t __cdecl FUN_00d37cb0();                    // 0x00d37cb0
uint32_t __cdecl FUN_00cd3440();                    // 0x00cd3440
uint32_t __cdecl FUN_00d004b0();                    // 0x00d004b0
void __cdecl FUN_00e1c7f0(cSPMission_s00e1_d020** ppMission);  // 0x00e1c7f0
void __cdecl FUN_00e1c830(void** pSlots, void** pEnd, int32_t nSelected);   // 0x00e1c830
void __cdecl FUN_00e1c930(void** pSlots, void** pEnd, int32_t nSelected);   // 0x00e1c930
void __cdecl FUN_00e1c9b0(void** pSlots, void** pEnd, int32_t nSelected);   // 0x00e1c9b0
void __cdecl FUN_00e1cb80(void** pSlots, void** pEnd, int32_t nSelected);   // 0x00e1cb80
void __cdecl FUN_00aea5d0(void** ppSlotEnd, cSPMission_s00e1_d020** ppMission);        // 0x00aea5d0
void* __cdecl FUN_00665410(uint32_t nType, int32_t nIndex);                 // 0x00665410
void __cdecl FUN_006668e0(void* pA, void* pB, void* pC);                    // 0x006668e0
void __cdecl FUN_00666a40(void* pItem);                                     // 0x00666a40
void __cdecl FUN_00668000(void* pText);                                     // 0x00668000
uint32_t __cdecl FUN_00664600();                                            // 0x00664600
void __cdecl FUN_006644e0(int32_t nValue);                                  // 0x006644e0
void __cdecl FUN_00664580(int32_t nValue);                                  // 0x00664580
void __cdecl FUN_00febf80(cSPMission_s00e1_d020* pMission);                            // 0x00febf80
__forceinline void AppendMissions(SlotVector* pSlots, uint32_t (*pfnGet)(), bool bFilter)
{
    if (pfnGet() == 0)
        return;
    MissionList* pList = FUN_009892e0();
    cSPMission_s00e1_d020** ppEnd = pList->mpEnd;
    for (cSPMission_s00e1_d020** pp = pList->mpBegin; pp != ppEnd; ++pp) {
        cSPMission_s00e1_d020* pMission = *pp;
        if (bFilter) {
            if (pMission->mnFlags != 0)
                continue;
            if (!pMission->IsVisibleInUI())
                continue;
            if (!pMission->IsActive())
                continue;
            cSPMission_s00e1_d020* pRef = pMission;
            FUN_00e1c7f0(&pRef);
        } else {
            cSPMission_s00e1_d020* pRef = pMission;
            if (pRef != nullptr)
                ((IWindow_s00e1_d020*)pRef)->GetOwner();
            if (pSlots->mpEnd < pSlots->mpCapacity) {
                *pSlots->mpEnd = pRef;
                pSlots->mpEnd = pSlots->mpEnd + 1;
                if (pRef != nullptr)
                    ((IWindow_s00e1_d020*)pRef)->GetOwner();
            } else {
                FUN_00aea5d0(pSlots->mpEnd, &pRef);
                pSlots->mpEnd = pSlots->mpEnd + 1;
            }
        }
    }
}
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
bool __cdecl FUN_00fec960(cSPMission_s00e1_d020* pMission);    // 0x00fec960
void __cdecl FUN_00febe00(cSPMission_s00e1_d020* pMission);    // 0x00febe00
void __cdecl FUN_00e18200(void* pMission, int32_t nA, int32_t nB, int32_t nC);  // 0x00e18200
void __cdecl FUN_00809db0(void* pTarget, const uint32_t* pColor);   // 0x00809db0
struct MissionMessage {
    IWindow_s00e1_d020* mpSender;          // +0x00
    uint32_t mPad04;            // +0x04
    uint32_t mnMessageType;     // +0x08
};
// ---- items of slice s00e1d020 end

// ---- items of slice s00e2e6e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*  g_stripVtable[];          // 0x01481804 the strip object's own vtable
extern char   g_szStatusNone[];         // 0x015a56bc
extern char   g_szStatusUnknown[];      // 0x015a56c8
extern char   g_szStatusTerraform[];    // 0x015a56d4
extern char   g_szStatusTerraformed[];  // 0x015a56e0
extern char   g_szStatusProbe[];        // 0x015a56ec
extern char   g_szStatusOther[];        // 0x015a56f8
extern char   g_szStatusLocked[];       // 0x015a5704
extern char   g_szStatusBusy[];         // 0x015a5710
extern float  g_kOne;                   // 0x01485720 1.0f
extern float  g_kHalf;                  // 0x01471064 0.5f
extern float  g_kTenPercent;            // 0x01488874 0.1f
extern float  g_kTwenty;                // 0x013eecd8 20.0f
void*    __cdecl App();                                                // 0x0067dd10
void*    __stdcall TerraformingManager(void* pNoun);                   // 0x00b3d430
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
class tAppBase {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    virtual void* v0c();                        // +0x0c
    virtual void* v10();                        // +0x10
    virtual void* v14();                        // +0x14
    virtual void* v18();                        // +0x18
    virtual void* v1c();                        // +0x1c
    virtual void* v20();                        // +0x20
    virtual void* v24();                        // +0x24
    virtual void* v28();                        // +0x28
    virtual void* v2c();                        // +0x2c
    virtual void* v30();                        // +0x30
    virtual void* v34();                        // +0x34
    virtual void* v38();                        // +0x38
    virtual void* v3c();                        // +0x3c
    virtual void* v40();                        // +0x40
    virtual void* v44();                        // +0x44
    virtual void* v48();                        // +0x48
    virtual void* v4c();                        // +0x4c
    virtual void* v50();                        // +0x50
    virtual void* v54();                        // +0x54
};
struct tArea;
class tViewer;
class tApp2 : public tAppBase {
public:
    virtual tViewer* v58();                     // +0x58 the viewer
};
class tViewer {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    virtual void* v0c();                        // +0x0c
    virtual void* v10();                        // +0x10
    virtual void* v14();                        // +0x14
    virtual void* v18();                        // +0x18
    virtual void* v1c();                        // +0x1c
    virtual void* v20();                        // +0x20
    virtual void* v24();                        // +0x24

    void GetCameraLocationInfo(int32_t nA, int32_t nB, tArea* pCamera, tArea* pDirection); // 0x007c3d30
    void CenterOverObject(tArea* pOut, tArea* pIn);                                       // 0x007c4180
};
class cTerraformingManager {
public:
    int32_t F670();                             // 0x00bbc670
};
class cSimNoun {
public:
    virtual void*     v00();                    // +0x00
    virtual void*     v04();                    // +0x04
    virtual void*     v08();                    // +0x08
    virtual void*     v0c();                    // +0x0c
    virtual void*     v10();                    // +0x10
    virtual void*     v14();                    // +0x14
    virtual void*     v18();                    // +0x18
    virtual void*     v1c();                    // +0x1c
    virtual void*     v20();                    // +0x20
    virtual void*     v24();                    // +0x24
    uint32_t          mPad04[0x0a];             // +0x004
    uint32_t          mn2c;                     // +0x02c flags
    uint32_t          mPad30[0x28];             // +0x030
    void*             mpd0;                     // +0x0d0
    void*             mpd4;                     // +0x0d4

    int32_t GetNounType();                      // 0x00b8dab0
    int32_t FUN_00b8d9b0();                     // 0x00b8d9b0
};
struct tArea {
    float x;                        // +0x00
    float y;                        // +0x04
    float z;                        // +0x08
    float w;                        // +0x0c
};
struct tRectEdge {
    float x0;                       // +0x00
    float y0;                       // +0x04
    float x1;                       // +0x08
    float y1;                       // +0x0c
};
tArea* __cdecl GetMainWindowArea(tArea* pOut);                                  // 0x00805ea0
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

// ---- items of slice s00e12f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float __cdecl SPUIHelpers_GetElapsedSeconds();     // 0x805080
extern "C" bool  __fastcall cSPUIAnimator_Empty(void* self);  // 0x7f6340
extern "C" void  __fastcall cSPUIAnimator_Update(void* self); // 0x7f63b0
extern "C" void  __cdecl FUN_00e2ed40();                      // 0xe2ed40
extern "C" void* __cdecl FUN_00b3d3f0(int a, void* b);        // 0xb3d3f0
extern "C" void  __fastcall FUN_00e18dd0(void* self);         // 0xe18dd0
static inline void** Vt(void* p) { return *(void***)p; }
struct Rect { float left, top, right, bottom; };
struct IWindow_s00e1_2f80 {
  virtual void AddRef();                              // 0x00
  virtual void Release();                             // 0x04
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
  virtual const Rect& GetArea();                      // 0x38
  virtual const void* GetCaption();                   // 0x3c
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
  virtual void SetSize(float w, float h);             // 0x68
  virtual void v6c();
  virtual void SetLayoutLocation(float x, float y);   // 0x70
virtual void v74();
virtual void v78();
  virtual void SetFlag(int flag, bool v);             // 0x7c
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8();
virtual void vec();
  virtual IWindow_s00e1_2f80* FindWindowByID(uint32_t id, bool recursive);  // 0xf0
};
struct IWinExt {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
  virtual void SetOption(bool v);                     // 0x14
};
struct IWinButton {
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
  virtual int Command(int a, int b);                 // 0x28
};
class cSPUIAnimator_s00e1_2f80 { public:
  void CancelAll();                                   // 0x7f8f00
  void AddAnimation(const struct AnimTmp& anim, IWindow_s00e1_2f80* w, int flags);   // 0x7f8d10
};
struct AnimTmp { uint32_t d[0x1f]; ~AnimTmp(); };     // dtor body 0x59a1e0
struct Vec2 { float x, y; Vec2(float a, float b) : x(a), y(b) {} };
class cSPUILayout_s00e1_2f80 { public:
  void Shutdown(int);          // 0x811ad0
  void SetVisibility(int);     // 0x810590
};
struct cUICard_s00e1_2f80 {
  void*    vtbl;    // +0x00
  void*    vtbl4;   // +0x04
  uint32_t pad8;    // +0x08
  void*    p0c;     // +0x0c cSPUILayout*
  uint8_t  b10;     // +0x10
  uint8_t  b11;     // +0x11
  uint8_t  pad12[0x0a];
  void*    p1c;     // +0x1c cSPUILayout*
  void*    p20;     // +0x20
  IWindow_s00e1_2f80* p24;     // +0x24
  cSPUIAnimator_s00e1_2f80* p28;     // +0x28
  IWindow_s00e1_2f80* p2c;     // +0x2c
  IWindow_s00e1_2f80* p30;     // +0x30
  IWindow_s00e1_2f80* p34;     // +0x34
  IWindow_s00e1_2f80* p38;     // +0x38
  IWindow_s00e1_2f80* p3c;     // +0x3c
  IWindow_s00e1_2f80* p40;     // +0x40
  IWindow_s00e1_2f80* p44;     // +0x44

  void Toggle();                     // 0xe12fe0
  void Release2();                   // 0xe13210 (destructor)
  void Teardown();                   // 0xe132c0
  void SetVisible(int);              // 0xe13360
  IWindow_s00e1_2f80* DoVcallF0(int);               // 0xe13390
  bool HandleMessage(int unused, void* msg);  // 0xe130b0
};
extern "C" void __cdecl AutoSizeWindowForText(IWindow_s00e1_2f80* w, int a, int b);   // 0x806e40
IWinExt*   __cdecl QueryWinExt(IWindow_s00e1_2f80** ref);                              // 0x5e1fd0
IWinButton* __cdecl CastWinButton(IWindow_s00e1_2f80* w);                              // 0x5ca960
AnimTmp __cdecl SPUICreateWindowAnimationTargetSize(IWindow_s00e1_2f80* win, const Vec2& size,
                                                    float duration, float from, int type);   // 0x7f8230
struct cUIMissionCard_s00e1_2f80 : cUICard_s00e1_2f80 {
  char  pad48[0x68 - 0x48];
  float f68, f6c, f70, f74;     // +0x68 rect
  float f78, f7c, f80, f84;     // +0x78 rect
  float f88, f8c, f90, f94;     // +0x88 rect
  __declspec(noinline) void InitForCreature(bool animate, int kind);  // 0x00e133b0 (cUIMissionCard::InitForCreature)
  void Expand(bool a);
};
static inline float Height(const Rect& r) { return r.bottom - r.top; }
// ---- items of slice s00e12f80 end

// ---- items of slice s00e13b50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Rect_s00e1_3b50 {
    float x1, y1, x2, y2;
    Rect_s00e1_3b50() {}
    Rect_s00e1_3b50(float a, float b, float c, float d) : x1(a), y1(b), x2(c), y2(d) {}
};
struct IWindow_s00e1_3b50 {
virtual void w0();
virtual void Release();
virtual void w2();
    virtual void* Cast(uint32_t id);                    // +0x0c
virtual void w4();
virtual void w5();
virtual void w6();
    virtual uint32_t GetID();                           // +0x1c
    virtual void w8();
virtual void w9();
virtual void w10();
virtual void w11();
    virtual uint32_t GetColor();                        // +0x30
    virtual void w13();
    virtual const Rect_s00e1_3b50& GetArea();                      // +0x38
    virtual const char* GetCaption();                   // +0x3c
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
virtual void w20();
virtual void w21();
virtual void w22();
    virtual void SetColor(uint32_t color);              // +0x5c
    virtual void w24();
    virtual bool IsChecked();                           // +0x64
    virtual void SetSize(float w, float h);             // +0x68
    virtual void w27();
    virtual void SetLocation(float x, float y);         // +0x70
virtual void w29();
virtual void w30();
    virtual void SetVisible(int a, bool b);             // +0x7c
    virtual void SetText(const void* text);             // +0x80
virtual void w33();
virtual void w34();
virtual void w35();
virtual void w36();
virtual void w37();
virtual void w38();
virtual void w39();
virtual void w40();
virtual void w41();
virtual void w42();
virtual void w43();
virtual void w44();
virtual void w45();
virtual void w46();
virtual void w47();
virtual void w48();
virtual void w49();
virtual void w50();
virtual void w51();
virtual void w52();
virtual void w53();
virtual void w54();
virtual void w55();
virtual void w56();
virtual void w57();
virtual void w58();
virtual void w59();
    virtual IWindow_s00e1_3b50* FindWindowByID(uint32_t id, bool recursive);   // +0xf0
virtual void w61();
virtual void w62();
virtual void w63();
virtual void w64();
virtual void w65();
    virtual void SetOwner(void* owner);                 // +0x108
};
int __cdecl GetCurrentGameMode_s00e1_3b50();                                  // 0x00b5b800
struct AnimBuf {
    uint32_t d[0x80 / 4];
    void Destroy();                                     // 0x0059a1e0
};
struct cAnimator {
    void AddAnimation(AnimBuf* anim, IWindow_s00e1_3b50* win, int flags);     // 0x007f8d10
    void Clear();                                                  // 0x007f8f00
};
struct cUICard_s00e1_3b50 {
    void*      vtbl0;
    void*      vtbl4;
    char       pad08[0x24 - 0x08];
    IWindow_s00e1_3b50*   mpMainWin;       // +0x24
    cAnimator* mpAnimator;      // +0x28
    IWindow_s00e1_3b50*   mpDescWin;       // +0x2c
    IWindow_s00e1_3b50*   mpTextWin;       // +0x30
    IWindow_s00e1_3b50*   pad34;
    IWindow_s00e1_3b50*   mpWinA;          // +0x38
    IWindow_s00e1_3b50*   mpWinB;          // +0x3c
    IWindow_s00e1_3b50*   pad40;
    IWindow_s00e1_3b50*   mpWinC;          // +0x44
    uint32_t   pad48[(0x68 - 0x48) / 4];
    Rect_s00e1_3b50       mAreaA;          // +0x68 initial area of mpWinA
    Rect_s00e1_3b50       mAreaB;          // +0x78 initial area of mpWinB
    Rect_s00e1_3b50       mAreaC;          // +0x88 initial area of mpWinC

    IWindow_s00e1_3b50* FindWindowByID(uint32_t id);               // 0x00e13390
    void UpdateLayout();                                // 0x00e132c0
    void ResizeToContent(bool animate, int style);      // @ 0x00e13b50
};
struct Vec3 { float x, y, z; };
struct IMissionBase;
struct IUIMission {                                     // object at card +0x9c
virtual void u00();
virtual void u01();
virtual void u02();
    virtual IMissionBase* Cast(uint32_t id);            // +0x0c
virtual void u04();
virtual void u05();
virtual void u06();
virtual void u07();
virtual void u08();
virtual void u09();
virtual void u10();
virtual void u11();
virtual void u12();
virtual void u13();
virtual void u14();
virtual void u15();
virtual void u16();
virtual void u17();
virtual void u18();
virtual void u19();
virtual void u20();
virtual void u21();
virtual void u22();
virtual void u23();
virtual void u24();
virtual void u25();
virtual void u26();
virtual void u27();
    virtual void u28();
    virtual uint32_t GetContentWinID();                 // +0x74
};
struct IMissionBase {                                   // result of IUIMission::Cast
virtual void m00();
virtual void m01();
virtual void m02();
    virtual IMissionBase* Cast(uint32_t id);            // +0x0c
virtual void m04();
virtual void m05();
virtual void m06();
virtual void m07();
virtual void m08();
virtual void m09();
virtual void m10();
virtual void m11();
virtual void m12();
virtual void m13();
virtual void m14();
virtual void m15();
virtual void m16();
virtual void m17();
virtual void m18();
virtual void m19();
virtual void m20();
virtual void m21();
virtual void m22();
virtual void m23();
virtual void m24();
virtual void m25();
virtual void m26();
virtual void m27();
virtual void m28();
virtual void m29();
virtual void m30();
virtual void m31();
virtual void m32();
virtual void m33();
virtual void m34();
virtual void m35();
virtual void m36();
virtual void m37();
virtual void m38();
virtual void m39();
virtual void m40();
virtual void m41();
virtual void m42();
virtual void m43();
virtual void m44();
virtual void m45();
virtual void m46();
virtual void m47();
virtual void m48();
virtual void m49();
virtual void m50();
virtual void m51();
virtual void m52();
virtual void m53();
virtual void m54();
virtual void m55();
virtual void m56();
virtual void m57();
virtual void m58();
virtual void m59();
virtual void m60();
virtual void m61();
    virtual bool IsComplete();                          // +0xf8
    virtual bool IsFailed();                            // +0xfc
virtual void m64();
virtual void m65();
virtual void m66();
virtual void m67();
virtual void m68();
virtual void m69();
virtual void m70();
virtual void m71();
virtual void m72();
virtual void m73();
virtual void m74();
virtual void m75();
virtual void m76();
virtual void m77();
virtual void m78();
virtual void m79();
virtual void m80();
virtual void m81();
virtual void m82();
virtual void m83();
virtual void m84();
virtual void m85();
    virtual bool IsHighlighted();                       // +0x158
    void SetFlag(bool v);                               // 0x00c44ed0 (declared only)
};
struct IMissionMultiStep : IMissionBase {
    IMissionBase* GetCurrSubMission();                  // 0x00c59d90 (declared only)
};
struct CMissionView {                                   // object returned by q->GetView()
    char mPad[0x504];
    Vec3 mPoint;                                        // +0x504
};
struct CMissionTarget {
virtual void q00();
virtual void q01();
virtual void q02();
virtual void q03();
virtual void q04();
virtual void q05();
virtual void q06();
virtual void q07();
virtual void q08();
virtual void q09();
virtual void q10();
virtual void q11();
virtual void q12();
virtual void q13();
virtual void q14();
virtual void q15();
virtual void q16();
virtual void q17();
virtual void q18();
virtual void q19();
virtual void q20();
virtual void q21();
virtual void q22();
virtual void q23();
virtual void q24();
virtual void q25();
virtual void q26();
virtual void q27();
virtual void q28();
virtual void q29();
virtual void q30();
virtual void q31();
virtual void q32();
virtual void q33();
virtual void q34();
virtual void q35();
virtual void q36();
virtual void q37();
virtual void q38();
virtual void q39();
virtual void q40();
virtual void q41();
virtual void q42();
virtual void q43();
virtual void q44();
virtual void q45();
virtual void q46();
virtual void q47();
virtual void q48();
virtual void q49();
virtual void q50();
virtual void q51();
virtual void q52();
virtual void q53();
virtual void q54();
virtual void q55();
virtual void q56();
virtual void q57();
virtual void q58();
virtual void q59();
virtual void q60();
virtual void q61();
virtual void q62();
virtual void q63();
virtual void q64();
virtual void q65();
virtual void q66();
virtual void q67();
virtual void q68();
virtual void q69();
virtual void q70();
virtual void q71();
virtual void q72();
virtual void q73();
virtual void q74();
virtual void q75();
virtual void q76();
virtual void q77();
virtual void q78();
virtual void q79();
virtual void q80();
virtual void q81();
virtual void q82();
virtual void q83();
virtual void q84();
virtual void q85();
virtual void q86();
virtual void q87();
virtual void q88();
virtual void q89();
virtual void q90();
virtual void q91();
virtual void q92();
virtual void q93();
virtual void q94();
virtual void q95();
virtual void q96();
virtual void q97();
virtual void q98();
virtual void q99();
virtual void q100();
virtual void q101();
virtual void q102();
virtual void q103();
virtual void q104();
virtual void q105();
virtual void q106();
virtual void q107();
virtual void q108();
virtual void q109();
virtual void q110();
virtual void q111();
virtual void q112();
virtual void q113();
virtual void q114();
virtual void q115();
virtual void q116();
virtual void q117();
virtual void q118();
virtual void q119();
virtual void q120();
virtual void q121();
virtual void q122();
virtual void q123();
virtual void q124();
virtual void q125();
virtual void q126();
virtual void q127();
virtual void q128();
virtual void q129();
virtual void q130();
virtual void q131();
virtual void q132();
virtual void q133();
virtual void q134();
virtual void q135();
virtual void q136();
virtual void q137();
virtual void q138();
virtual void q139();
virtual void q140();
virtual void q141();
virtual void q142();
virtual void q143();
virtual void q144();
virtual void q145();
virtual void q146();
virtual void q147();
virtual void q148();
virtual void q149();
virtual void q150();
virtual void q151();
virtual void q152();
virtual void q153();
virtual void q154();
virtual void q155();
virtual void q156();
virtual void q157();
virtual void q158();
virtual void q159();
virtual void q160();
virtual void q161();
virtual void q162();
virtual void q163();
virtual void q164();
virtual void q165();
virtual void q166();
virtual void q167();
virtual void q168();
virtual void q169();
virtual void q170();
virtual void q171();
virtual void q172();
virtual void q173();
virtual void q174();
virtual void q175();
virtual void q176();
virtual void q177();
virtual void q178();
virtual void q179();
virtual void q180();
virtual void q181();
virtual void q182();
virtual void q183();
virtual void q184();
virtual void q185();
virtual void q186();
virtual void q187();
virtual void q188();
virtual void q189();
virtual void q190();
virtual void q191();
virtual void q192();
virtual void q193();
virtual void q194();
virtual void q195();
virtual void q196();
virtual void q197();
virtual void q198();
virtual void q199();
virtual void q200();
virtual void q201();
virtual void q202();
virtual void q203();
virtual void q204();
virtual void q205();
virtual void q206();
virtual void q207();
virtual void q208();
virtual void q209();
virtual void q210();
virtual void q211();
virtual void q212();
virtual void q213();
virtual void q214();
virtual void q215();
virtual void q216();
virtual void q217();
virtual void q218();
virtual void q219();
virtual void q220();
virtual void q221();
virtual void q222();
virtual void q223();
virtual void q224();
virtual void q225();
virtual void q226();
virtual void q227();
virtual void q228();
virtual void q229();
virtual void q230();
virtual void q231();
virtual void q232();
virtual void q233();
virtual void q234();
virtual void q235();
virtual void q236();
virtual void q237();
virtual void q238();
virtual void q239();
virtual void q240();
virtual void q241();
virtual void q242();
virtual void q243();
virtual void q244();
virtual void q245();
virtual void q246();
virtual void q247();
virtual void q248();
virtual void q249();
virtual void q250();
virtual void q251();
virtual void q252();
virtual void q253();
virtual void q254();
virtual void q255();
virtual void q256();
virtual void q257();
virtual void q258();
virtual void q259();
virtual void q260();
virtual void q261();
virtual void q262();
virtual void q263();
virtual void q264();
virtual void q265();
virtual void q266();
virtual void q267();
virtual void q268();
virtual void q269();
virtual void q270();
virtual void q271();
virtual void q272();
virtual void q273();
virtual void q274();
virtual void q275();
virtual void q276();
virtual void q277();
virtual void q278();
virtual void q279();
virtual void q280();
virtual void q281();
virtual void q282();
virtual void q283();
virtual void q284();
virtual void q285();
virtual void q286();
virtual void q287();
virtual void q288();
virtual void q289();
virtual void q290();
virtual void q291();
virtual void q292();
virtual void q293();
virtual void q294();
virtual void q295();
virtual void q296();
virtual void q297();
virtual void q298();
virtual void q299();
virtual void q300();
virtual void q301();
virtual void q302();
virtual void q303();
virtual void q304();
virtual void q305();
virtual void q306();
virtual void q307();
virtual void q308();
virtual void q309();
virtual void q310();
virtual void q311();
virtual void q312();
virtual void q313();
virtual void q314();
virtual void q315();
virtual void q316();
virtual void q317();
virtual void q318();
virtual void q319();
virtual void q320();
virtual void q321();
virtual void q322();
virtual void q323();
virtual void q324();
virtual void q325();
virtual void q326();
virtual void q327();
virtual void q328();
virtual void q329();
virtual void q330();
virtual void q331();
virtual void q332();
virtual void q333();
virtual void q334();
virtual void q335();
virtual void q336();
virtual void q337();
virtual void q338();
virtual void q339();
virtual void q340();
virtual void q341();
virtual void q342();
virtual void q343();
virtual void q344();
virtual void q345();
virtual void q346();
virtual void q347();
virtual void q348();
virtual void q349();
virtual void q350();
virtual void q351();
virtual void q352();
virtual void q353();
virtual void q354();
virtual void q355();
virtual void q356();
virtual void q357();
virtual void q358();
virtual void q359();
virtual void q360();
virtual void q361();
virtual void q362();
virtual void q363();
virtual void q364();
virtual void q365();
virtual void q366();
virtual void q367();
virtual void q368();
virtual void q369();
virtual void q370();
virtual void q371();
virtual void q372();
virtual void q373();
virtual void q374();
virtual void q375();
virtual void q376();
virtual void q377();
virtual void q378();
virtual void q379();
virtual void q380();
virtual void q381();
virtual void q382();
virtual void q383();
virtual void q384();
virtual void q385();
virtual void q386();
virtual void q387();
virtual void q388();
virtual void q389();
virtual void q390();
virtual void q391();
virtual void q392();
virtual void q393();
virtual void q394();
virtual void q395();
virtual void q396();
virtual void q397();
virtual void q398();
virtual void q399();
virtual void q400();
virtual void q401();
virtual void q402();
virtual void q403();
virtual void q404();
virtual void q405();
virtual void q406();
virtual void q407();
virtual void q408();
virtual void q409();
virtual void q410();
virtual void q411();
virtual void q412();
virtual void q413();
virtual void q414();
virtual void q415();
virtual void q416();
virtual void q417();
virtual void q418();
virtual void q419();
virtual void q420();
virtual void q421();
virtual void q422();
virtual void q423();
virtual void q424();
virtual void q425();
virtual void q426();
virtual void q427();
virtual void q428();
virtual void q429();
virtual void q430();
virtual void q431();
virtual void q432();
virtual void q433();
virtual void q434();
virtual void q435();
virtual void q436();
virtual void q437();
virtual void q438();
virtual void q439();
virtual void q440();
virtual void q441();
virtual void q442();
virtual void q443();
virtual void q444();
virtual void q445();
virtual void q446();
virtual void q447();
virtual void q448();
virtual void q449();
virtual void q450();
virtual void q451();
virtual void q452();
virtual void q453();
virtual void q454();
virtual void q455();
virtual void q456();
virtual void q457();
virtual void q458();
virtual void q459();
virtual void q460();
virtual void q461();
virtual void q462();
virtual void q463();
virtual void q464();
virtual void q465();
virtual void q466();
virtual void q467();
virtual void q468();
virtual void q469();
virtual void q470();
virtual void q471();
virtual void q472();
virtual void q473();
virtual void q474();
virtual void q475();
virtual void q476();
virtual void q477();
virtual void q478();
virtual void q479();
virtual void q480();
virtual void q481();
virtual void q482();
virtual void q483();
virtual void q484();
virtual void q485();
virtual void q486();
virtual void q487();
virtual void q488();
virtual void q489();
virtual void q490();
virtual void q491();
virtual void q492();
virtual void q493();
virtual void q494();
virtual void q495();
virtual void q496();
virtual void q497();
virtual void q498();
virtual void q499();
    virtual void q500();
    virtual CMissionView* GetView();                    // 0x00c2e780
};
struct CardVtblView {                                   // primary vtable of the card
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual void v08();                                 // +0x20
    virtual void v09();                                 // +0x24
virtual void v10();
virtual void v11();
virtual void v12();
    virtual void v13();                                 // +0x34
};
struct ISelectable {                                    // source item of UpdateButtonStateB
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
    virtual bool IsSelected();                          // +0x68
};
struct Stopwatch {                                      // EA::LimitStopwatch, 0x20 bytes
    uint32_t mData[8];
    void Init(int type, bool b);                        // 0x0093a560
    void SetTimeLimit(uint32_t limit, bool b);          // 0x0093a480
};
struct CardEvent {
    uint32_t m00;                                       // +0x00
    uint32_t m04;                                       // +0x04
    uint32_t mType;                                     // +0x08
    uint32_t mId;                                       // +0x0c
    uint32_t m10;                                       // +0x10
    uint32_t m14;                                       // +0x14
    void*    mpSender;                                  // +0x18
};
struct EventCtx {                                       // 0x40-byte draw context
    uint32_t mColor;                                    // +0x00
    uint32_t mPad04[3];                                 // +0x04
    uint8_t  mFlag10;                                   // +0x10
    uint16_t mPad11;                                    // +0x11
    uint8_t  mFlag13;                                   // +0x13
    uint32_t mPad14;                                    // +0x14
    Vec3     mPos;                                      // +0x18
    uint8_t  mFlag24;                                   // +0x24
    uint8_t  mPad25[0x40 - 0x25];                       // +0x25
    void Init();                                        // 0x00644b10
    void Destroy();                                     // 0x00644b60
};
void __cdecl sub_64a990(void* ctx);                      // 0x0064a990
struct CStr {                                           // SP::cString temporary, 0x14 bytes
    uint32_t mData[5];
    void Init(uint32_t a, uint32_t b, const wchar_t* text);   // 0x006b5770
    const wchar_t* GetText();                                 // 0x006b55c0
    void Destroy();                                           // 0x006b5240
};
struct CPanel {
    void OpenPanel();                                    // 0x00e18dd0
};
CPanel* __stdcall GetMissionPanel(int id, void* mission);        // 0x00b3d3f0
struct CivStrategy {
    char mPad[0x148];
    uint8_t mFlag148;                                   // +0x148
};
CivStrategy* __cdecl GetCivStrategy();                   // 0x00cf74c0
struct TribeStrategy { bool TerrainNotHasKey(); };       // 0x00cd44a0
TribeStrategy* __cdecl GetTribeStrategy();               // 0x00cd40b0
struct SpaceUi { bool IsSomething(); };                  // 0x01065e20
SpaceUi* __cdecl GetSpaceUi();                           // 0x010666a0
struct ScrollHost { char mPad[0xb8]; int mCount; };      // +0xb8
struct ScrollSource { int GetScrollPos(); };             // 0x00f3be30
struct ScrollGlobals {
    char mPad74[0x74];
    ScrollSource* mpSource;                             // +0x74
    ScrollHost*   mpHost;                               // +0x78
};
struct CSPUILayout { void SetVisibility(bool on); };     // 0x00810590
union F32Bits { float f; uint32_t u; };
struct CardLayout {                                     // retail cards, 0xf8 bytes
    void*    mpVtbl0;                                   // +0x00
    void* volatile mpVtbl1;                             // +0x04
    uint32_t m08;                                       // +0x08
    uint32_t m0C;                                       // +0x0c
    uint8_t  m10;                                       // +0x10
    uint8_t  m11;                                       // +0x11
    uint16_t mPad12;                                    // +0x12
    float    m14;                                       // +0x14
    float    m18;                                       // +0x18
    CSPUILayout* m1C;                                   // +0x1c
    uint32_t m20;                                       // +0x20
    IWindow_s00e1_3b50* mpMainWin;                                 // +0x24
    IWindow_s00e1_3b50* mpAnimator;                                // +0x28
    IWindow_s00e1_3b50* mpDescWin;                                 // +0x2c
    IWindow_s00e1_3b50* mpTextWin;                                 // +0x30
    IWindow_s00e1_3b50* mp34;                                      // +0x34
    IWindow_s00e1_3b50* mpWinA;                                    // +0x38
    IWindow_s00e1_3b50* mpWinB;                                    // +0x3c
    IWindow_s00e1_3b50* mp40;                                      // +0x40
    IWindow_s00e1_3b50* mpWinC;                                    // +0x44
    uint32_t mPad48[0x50 / 4];                          // +0x48
    F32Bits  m98;                                       // +0x98
    IUIMission* mpMission;                              // +0x9c
    uint32_t mPadA0[0x10 / 4];                          // +0xa0
    Stopwatch mWatch0;                                  // +0xb0
    Stopwatch mWatch1;                                  // +0xd0
    int      mF0;                                       // +0xf0
    int      mF4;                                       // +0xf4

    void ResizeToStyle0(bool animate);
    CardLayout* InitA();
    void RefreshChildWindows();
    uint32_t GetCardColor();
    bool HandleEvent(void* sender, CardEvent* ev);
    uint32_t GetContentWinID();
    void UpdateButtonStateA(IWindow_s00e1_3b50* src);
    void UpdateButtonStateB(ISelectable* src);
    CardLayout* InitB();
    CardLayout* InitC();
    void ShowCard();
    void UpdateScrollButtons();
    void HideButtons();
};
// ---- items of slice s00e13b50 end

// ---- items of slice s00e15c00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char gNameUI[];       // 0x013f6b3c
typedef wchar_t char16;
struct Rect_s00e1_5c00 {
    float x1, y1, x2, y2;
    Rect_s00e1_5c00() {}
    Rect_s00e1_5c00(const Rect_s00e1_5c00& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
};
extern char16 gEmptyString[];   // 0x01667bac
extern const char16 gStr13ec468[];   // 0x013ec468
void operator delete[](void* p);  // 0x00f47380
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   int file, int line);   // 0x00f473a0
struct string16 {
    char16* mpBegin;
    char16* mpEnd;
    char16* mpCapacity;
    uint32_t  mAllocator;
    string16() : mpBegin(&gEmptyString[0]), mpEnd(&gEmptyString[0]), mpCapacity(&gEmptyString[1]) {}
    ~string16()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            delete[] mpBegin;
    }
};
struct ResourceKey {
    uint32_t a, b, c;
};
class IWindow_s00e1_5c00 {
public:
    virtual int   AddRef();                                         // 0x00
    virtual int   Release();                                        // 0x04
    virtual void  v08();                                            // 0x08
    virtual void* Cast(uint32_t typeID);                            // 0x0c
    virtual IWindow_s00e1_5c00* GetParent();                                   // 0x10
virtual void  v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void  v24();
virtual void v28();
virtual void v2c();
virtual void v30();
    virtual void  v34();
    virtual const Rect_s00e1_5c00& GetRealArea();                              // 0x38
virtual void  v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void  v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void  v5c();
virtual void v60();
virtual void v64();
    virtual void  SetSize(float w, float h);                        // 0x68
    virtual void  SetLayoutArea(const Rect_s00e1_5c00& area);                  // 0x6c
virtual void  v70();
virtual void v74();
virtual void v78();
    virtual void  SetFlag(uint32_t flag, bool value);               // 0x7c
    virtual void  SetCaption(const char16* caption);                // 0x80
virtual void  v84();
virtual void v88();
virtual void v8c();
virtual void v90();
    virtual void  v94();
virtual void  v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void  va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void  vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void  vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void  vd8();
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void  ve8();
virtual void vec();
    virtual IWindow_s00e1_5c00* FindWindowByID(uint32_t controlID, bool recursive);   // 0xf0
virtual void  vf4();
virtual void vf8();
virtual void vfc();
virtual void v100();
    virtual void  SetOwner(void* owner);                            // 0x104
};
class IWinText {
public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
    virtual void s10();
    virtual void SetEnabled(int on);                                // 0x14
};
class IMission {
public:
virtual void m00();
virtual void m04();
virtual void m08();
    virtual void* Cast(uint32_t typeID);                            // 0x0c
virtual void m10();
virtual void m14();
virtual void m18();
virtual void m1c();
virtual void m20();
virtual void m24();
virtual void m28();
virtual void m2c();
virtual void m30();
virtual void m34();
virtual void m38();
virtual void m3c();
virtual void m40();
virtual void m44();
virtual void m48();
virtual void m4c();
virtual void m50();
virtual void m54();
virtual void m58();
virtual void m5c();
    virtual int  GetKind();                                         // 0x60
virtual void m64();
virtual void m68();
virtual void m6c();
virtual void m70();
virtual void m74();
virtual void m78();
    virtual float GetProgress();                                    // 0x7c
    virtual void m80();
    virtual void OnShown();                                         // 0x84
    virtual void OnDone();                                          // 0x88
    virtual void GetTitleText(string16* out);                       // 0x8c
virtual void m90();
virtual void m94();
    virtual void GetText98(string16* out);                          // 0x98
    virtual void m9c();
    virtual void GetTextA0(string16* out);                          // 0xa0
    virtual int  GetStatusFill();                                   // 0xa4
    virtual void GetStatusText(string16* out);                      // 0xa8
virtual void mac();
virtual void mb0();
    virtual void GetTextB4(string16* out);                          // 0xb4

    int  FUN_00c2ec30();   // 0x00c2ec30 progress-bar layout id
    int  FUN_00c2ec80();   // 0x00c2ec80 progress-icons window id
    bool GetProgressIconLayout(ResourceKey* out);   // 0x00c2e4f0
};
class IMissionImage {
public:
    bool FUN_00c2f320(void** pTexture);   // 0x00c2f320
    int  FUN_00c2e820();                  // 0x00c2e820
};
class IMissionValue {
public:
    float FUN_00c2f650();                 // 0x00c2f650
};
class cSPUILayout_s00e1_5c00 {
public:
    virtual void d00();
    virtual void AddRef();                                          // 0x04
    virtual void Release();                                         // 0x08
    uint32_t d[5];
    cSPUILayout_s00e1_5c00();                                                  // 0x00810000
    IWindow_s00e1_5c00* FindWindowByID(uint32_t id, bool recursive);           // 0x008105b0
    void Shutdown(int arg);                                         // 0x00811ad0
    void Init(const ResourceKey* key, int arg, uint32_t id);        // 0x008120d0
    bool SetParentWin(IWindow_s00e1_5c00* win, int arg, uint32_t id);          // 0x008121b0
};
class cSPUIRelationshipStrip_s00e1_5c00 {
public:
    virtual void d00();
    virtual void AddRef();                                          // 0x04
    virtual void Release();                                         // 0x08
    uint32_t d[2];
    cSPUIRelationshipStrip_s00e1_5c00();                                       // 0x00e2ec40
    void Init(IWindow_s00e1_5c00* win);                                        // 0x00e2ec60
    void FUN_00e2ed70(int v);                                       // 0x00e2ed70
    void FUN_00e2ef80(float v);                                     // 0x00e2ef80
};
class cTextureInstanceWrapper {
public:
    virtual void AddRef();
    uint32_t d[4];
    cTextureInstanceWrapper(void* tex);                             // 0x008333b0
    uint32_t GetWidth();                                            // 0x008332a0
    uint32_t GetHeight();                                           // 0x008332d0
};
class UIImage {
public:
    virtual void AddRef();                                          // 0x00
    virtual void Release();                                         // 0x04
    uint32_t d[10];
    UIImage(cTextureInstanceWrapper* tex, uint32_t w, uint32_t h, float u0, float v0, float u1,
            float v1, int flags);                                   // 0x009579f0
};
template<class T> struct RefPtr {
    T* p;
    void Set(T* n);
};
typedef RefPtr<cSPUIRelationshipStrip_s00e1_5c00> StripPtr;
typedef RefPtr<cSPUILayout_s00e1_5c00> LayoutPtr;
void SetImageFromLayout(IWindow_s00e1_5c00* w, void* cache, int layoutId, int flags);   // 0x00806a60 (cdecl)
void SetDrawableImage(IWindow_s00e1_5c00* w, UIImage* img, int flags);                  // 0x008068d0 (cdecl)
void* GetImageCache();                                                       // 0x00b3d400 (cdecl)
IWinText* CastToText(IWindow_s00e1_5c00* w);                                            // 0x005994b0 (cdecl)
void UpdateProgessIcons(cSPUILayout_s00e1_5c00* layout, IMission* mission);             // 0x00e2e790 (cdecl)
class cImageCacheOwner {
public:
    void* FUN_00e14c70();   // 0x00e14c70
};
class cMissionTracker {
public:
    uint32_t  pad00[3];
    LayoutPtr mpLayout;            // +0x0c
    uint32_t  pad10[3];
    cSPUILayout_s00e1_5c00* mpPanelLayout;    // +0x1c
    StripPtr  mpStrip;             // +0x20
    IWindow_s00e1_5c00*  mpRoot;              // +0x24
    uint32_t  pad28;
    IWindow_s00e1_5c00*  mpStatusWin;         // +0x2c
    uint32_t  pad30[(0x98 - 0x30) / 4];
    float     mfProgress;          // +0x98

    void FUN_00e145b0(IMission* m);    // 0x00e145b0
    void FUN_00e14690(IMission* m);    // 0x00e14690
    void FUN_00e16090(IMission* m);
};
// ---- items of slice s00e15c00 end

// ---- items of slice s00e16a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_AlertTimeLimit;   // 0x015a4cc8
extern float g_TimerWarnSeconds; // 0x015a4cd8
extern uint32_t g_Limit15a4ccc;   // 0x015a4ccc
extern uint32_t g_Limit15a4cd0;   // 0x015a4cd0
extern uint32_t g_Limit15a4cd4;   // 0x015a4cd4
extern float    g_f10;            // 0x01473c70
extern float    g_f5;             // 0x01486110
struct Rect_s00e1_6a70 {
    float x1, y1, x2, y2;
    __forceinline Rect_s00e1_6a70(float l, float t, float r, float b) : x1(l), y1(t), x2(r), y2(b) {}
};
class IWindow_s00e1_6a70 {
public:
    virtual int   AddRef();                                         // 0x00
    virtual int   Release();                                        // 0x04
    virtual void  v08();                                            // 0x08
    virtual void* Cast(uint32_t typeID);                            // 0x0c
    virtual IWindow_s00e1_6a70* GetParent();                                   // 0x10
virtual void  v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void  v24();
virtual uint32_t GetState28();
virtual void v2c();
virtual void v30();
    virtual void  v34();
    virtual const Rect_s00e1_6a70& GetRealArea();                              // 0x38
virtual void  v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void  v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void  v5c();
virtual void v60();
virtual void v64();
virtual void v68();
    virtual void  SetLayoutArea(const Rect_s00e1_6a70& area);                  // 0x6c
    virtual void  v70();
    virtual void  SetLayoutSize(float w, float h);                  // 0x74
    virtual void  v78();
    virtual void  SetFlag(uint32_t flag, bool value);               // 0x7c
    virtual void  SetCaption(const char16* caption);              // 0x80
virtual void  v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void  v94();
virtual void v98();
virtual void v9c();
virtual void va0();
    virtual uint32_t GetFillColor();                                // 0xa4
virtual void  va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void  vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void  vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void  vd8();
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void  ve8();
virtual void vec();
    virtual IWindow_s00e1_6a70* FindWindowByID(uint32_t controlID, bool recursive);   // 0xf0
};
class IRowControl {
public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
    virtual IWindow_s00e1_6a70* GetWindow();                                   // 0x10
    virtual void SetEnabled(int on);                                // 0x14
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
    virtual void s48();
    virtual void SetValue(int index, uint32_t value);               // 0x4c
};
struct ResourceKey_s00e1_6a70 {
    uint32_t instanceID, typeID, groupID;
};
class cMissionLog {
public:
    void  GetTitle(string16* out);        // 0x00f1b9b0
    void  GetObjectiveTitle(string16* out);   // 0x00f1ba00
    int   GetEntryCount();                // 0x00f19bc0
    bool  IsEntryComplete(int i);         // 0x00f19be0
    void  GetEntryText(int i, string16* out);   // 0x00f1ba50
    bool  IsEntryActive(int i);           // 0x00f19cc0
    bool  IsEntryNew(int i);              // 0x00f19c80
    int   GetEntryProgress(int i);        // 0x00f19c20
    int   GetEntryIcon(int i);            // 0x00f19c00
    bool  HasTimer();                     // 0x00f19b80
    void  GetTimerText(string16* out);    // 0x00f1dc50
    float GetTimerSeconds();              // 0x00f19160
};
struct GameState {
    uint32_t pad00[0x78 / 4];
    cMissionLog* mpLog;        // +0x78
    uint32_t pad7c[(0xd0 - 0x7c) / 4];
    int mnPlayerCount;         // +0xd0
};
extern GameState* g_pGame;     // 0x016c7aa4
class LimitStopwatch {
public:
    int64_t  mStart;           // +0x00  (QPC start, low/high pair)
    uint32_t mPad08[4];        // +0x08
    int64_t  mDeadline;        // +0x18
    void SetTimeLimit(uint32_t limit, int units);   // 0x0093a480
    bool IsTimeUp();                                // 0x005ff1c0
    void SetBoolProperty();                         // 0x0093a2e0
};
class cSPUIAnimator_s00e1_6a70 {
public:
    bool Empty();      // 0x007f6340
    void Update();     // 0x007f63b0
};
class cUIPanelVtbl {
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
virtual void v28(int on);
virtual void v2c(int on);
};
void FillIconResource(ResourceKey_s00e1_6a70* out, int icon);                      // 0x00edcac0
void SetWindowImageResource(IWindow_s00e1_6a70* w, ResourceKey_s00e1_6a70* key, int flags);   // 0x00807cb0
class cMissionPanel : public cUIPanelVtbl {
public:
    uint8_t   pad04[0x10 - 0x04];  // +0x04 .. +0x0f
    uint8_t   mbFlag10;            // +0x10  (set by the two refresh entry points)
    uint8_t   mbAnimDirty;         // +0x11
    uint8_t   pad12[0x24 - 0x12];  // +0x12 .. +0x23
    IWindow_s00e1_6a70*  mpRoot;              // +0x24
    cSPUIAnimator_s00e1_6a70* mpAnimator;     // +0x28
    uint32_t  pad2c;               // +0x2c
    IWindow_s00e1_6a70*  mpTitleWin;          // +0x30
    IWindow_s00e1_6a70*  mpListWin;           // +0x34
    uint32_t  pad38[(0x98 - 0x38) / 4];
    float     mfMinRowHeight;      // +0x98
    int       mnProgress[3];       // +0x9c
    uint8_t   mbAlerted[3];        // +0xa8
    uint8_t   pada[5];
    LimitStopwatch mAlertTimer;    // +0xb0
    LimitStopwatch mStateTimer;    // +0xd0
    int       mState;              // +0xf0

    void FUN_00e154d0(int arg);    // 0x00e154d0
    void FUN_00e16a70(bool bSkipList);
    void FUN_00e170f0();           // 0x00e170f0
    void FUN_00e173b0();           // 0x00e173b0
    void FUN_00e173c0();           // 0x00e173c0
    void FUN_00e17470(int id);     // 0x00e17470

    // thiscall helpers that clean their stack arguments.
    void FUN_00e14900();                             // 0x00e14900
    void HideButtons();                              // 0x00e149e0
    void FUN_00e133b0(int a, int b);                 // 0x00e133b0 (ret 8)
    void FUN_00e17570(void* mission);                // 0x00e17570
    void FUN_00e145b0(void* mission);                // 0x00e145b0
    void FUN_00e14690(void* mission);                // 0x00e14690
    void FUN_00e14c10(int on);                       // 0x00e14c10
};
void FUN_00e12fa0(IWindow_s00e1_6a70* w, int on);                                  // 0x00e12fa0 (cdecl)
struct CardTarget {
    uint32_t pad00[0x98 / 4];
    int mId;                       // +0x98
    void FUN_00e16800();           // 0x00e16800 (thiscall)
};
struct LARGE_INTEGER { long long QuadPart; };
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER* out);
class GonzagoCtor { public: void Init(); };   // 0x00b5b960
class PaintSystem {
public:
    void* volatile mVtbl0;        // +0x00
    void* volatile mVtbl4;        // +0x04
    uint32_t mPad08[5];  // +0x08 .. +0x1b
    void* volatile mVtbl1c;       // +0x1c
    uint32_t mZero20;    // +0x20
    void* volatile mVtbl24;       // +0x24
    IWindow_s00e1_6a70** mpBegin;   // +0x28
    IWindow_s00e1_6a70** mpEnd;     // +0x2c
    IWindow_s00e1_6a70** mpCap;     // +0x30
    uint32_t m34;        // +0x34
    uint32_t m38;        // +0x38
    uint32_t m3c, m40, m44, m48, m4c, m50, m54;
    float    m58, m5c, m60;
    PaintSystem();               // 0x00e173d0
    void FUN_00e17470(int id);   // 0x00e17470
};
// ---- items of slice s00e16a70 end

// ---- items of slice s00e18d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cSPUILayout_s00e1_8d40 { public:
    void* FindWindowByID(int id, int flag);             // 0x008105b0  (ret 8)
    void  SetVisibility(int v);                         // 0x00810590  (ret 4)
    bool  IsVisible();                                  // 0x00810070
    void  Shutdown(int v);                              // 0x00811ad0  (ret 4)
};
struct cVerbWin { void FUN_00663350(int x); };          // 0x00663350
struct cMissionManager { void* GetMissionList(); };      // 0x00fedd50
struct cSortMissions { bool operator()(int* a, int* b); }; // 0x00e19d30
struct cMissionLog_s00e1_8d40;   // fwd
struct cMissionLog_s00e1_8d40 {
    char  pad00[0x18];
    void* mLayout;       // +0x18
    char  pad1c[0x34 - 0x1c];
    void* mListNext;     // +0x34 sentinel.next
    void* mListPrev;     // +0x38 sentinel.prev
    char  pad3c[0x6c - 0x3c];
    void* mField6c;      // +0x6c

    void FUN_00e19250(int value);                                   // 0x00e19250
    unsigned FUN_00e19c70(int mode);                                // 0x00e19c70
    void FUN_00e19d10(int x);                                       // 0x00e19d10
};
void* SP_GetMissionManager();                           // 0x00feb9f0
// ---- items of slice s00e18d40 end

// ---- items of slice s00e1bbc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define FR(o) (*(int*)(fr + (o)))
#define FP(o) (*(void**)(fr + (o)))
#define SI(p, o) (*(int*)((unsigned char*)(p) + (o)))
#define SPTR(p, o) (*(void**)((unsigned char*)(p) + (o)))
#define UI(p, o) (*(unsigned*)((unsigned char*)(p) + (o)))
#define VC0(RET, SELF, OFF) (((RET(__thiscall*)(void*))((*(void***)(SELF))[(OFF) / 4]))(SELF))
#define VC1(RET, SELF, OFF, T1, A1) \
    (((RET(__thiscall*)(void*, T1))((*(void***)(SELF))[(OFF) / 4]))((SELF), (A1)))
#define VC2(RET, SELF, OFF, T1, A1, T2, A2) \
    (((RET(__thiscall*)(void*, T1, T2))((*(void***)(SELF))[(OFF) / 4]))((SELF), (A1), (A2)))
#define FIND_WIN(L, ID) (((void*(__thiscall*)(void*, unsigned, int))(0x8105b0))((L), (ID), 1))
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
namespace SP {
struct float4 { float x, y, z, w; };
}
namespace SP {
class cSPUILayout;
}
namespace SP {
class cSPUIFeedList_s00e1_bbc0;
}
namespace SP {
class cSPUIFeedCategory;
}
namespace SP {
class cScrollFrameVertical;
}
namespace SP {
class IWinWindow;
}
namespace SP {
class IMessageServer;
}
namespace SP {
class IRefObj {                                     // intrusive ref count in slots 0 / 4
public:
    virtual void AddRef();                          // +0x00
    virtual void Release();                         // +0x04
};
}
namespace SP {
class IRefObjB {                                    // intrusive ref count in slots 8 / 0xc
public:
    PV2
    virtual void AddRef();                          // +0x08
    virtual void Release();                         // +0x0c
};
}
namespace SP {
class IObj5c {                                      // second release path in slot 8
public:
    PV2
    virtual void ReleaseB();                        // +0x08
};
}
namespace SP {
class IObj60 : public IObj5c {
public:
    void Stop();                                    // 0x00e2ed40
};
}
namespace SP {
class IObj64 {                                      // slot 8 + a ref-counted member at +0x10
public:
    PV                                              // +0x00
    PV                                              // +0x04
    virtual void Detach();                          // +0x08
    uint32_t mPad04[3];                             // +0x04 .. +0x0f
    IRefObj mSub10;                                 // +0x10
};
}
namespace SP {
class IObj68 {                                      // stop (slot 0x20) + release (slot 4)
public:
    PV                                              // +0x00
    virtual void Release();                         // +0x04
    PV PV PV PV PV PV                               // +0x08 .. +0x1c
    virtual void Stop();                            // +0x20
};
}
namespace SP {
class IWinWindow {
public:
    virtual void Attach();                          // +0x00
    virtual void Release();                         // +0x04
    PV2                                             // +0x08, +0x0c
    virtual void* GetContent();                     // +0x10
    virtual void Activate();                        // +0x14
    PV8                                             // +0x18 .. +0x34
    virtual float4* GetRect();                      // +0x38
    PV8 PV4                                         // +0x3c .. +0x68
    virtual void SetRect(void* pRect);              // +0x6c
    virtual void SetPosition(float x, float y);     // +0x70
    PV2                                             // +0x74, +0x78
    virtual void SetSize(int w, int h);             // +0x7c
    PV8 PV8 PV4 PV2                                 // +0x80 .. +0xd4
    virtual void SetParent(void* pParent);          // +0xd8
    virtual void SetOwner(void* pOwner);            // +0xdc
    PV8 PV2                                         // +0xe0 .. +0x104
    virtual void SetHandler(void* pHandler);        // +0x108
};
}
namespace SP {
class IMessageServer {
public:
    PV8 PV                                          // +0x00 .. +0x20
    virtual void Subscribe(void* pHandler, uint32_t messageId);   // +0x24
};
}
namespace SP {
class cSPUIFeedList_s00e1_bbc0 {
public:
    virtual void AddRef();                                           // +0x00
    virtual void Release();                                          // +0x04
    void* Ctor();                                                    // 0x00663040
    void AddWindow(void* pWindow, uint32_t id, void* a, void* b);    // 0x00663860
    void* FindEntry(uint32_t id);                                    // 0x00662a40
    void Shutdown();                                                 // 0x006628d0
    void SetEnabled(bool b);                                         // 0x00662920
};
}
namespace SP {
class cSPUIFeedCategory : public IRefObjB {
public:
    void ShutdownChildren();                                         // 0x006657a0
};
}
namespace SP {
class cScrollFrameVertical {
public:
    virtual void AddRef();                          // +0x00
    virtual void Release();                         // +0x04
    PV                                              // +0x08
    PV                                              // +0x0c
    uint32_t mPad04[3];                             // +0x04 .. +0x0f
    IWinWindow* mpObj10;                            // +0x10
    uint32_t mPad14;                                // +0x14
    IWinWindow* mpObj18;                            // +0x18
    void* Ctor();                                   // 0x0082a040 (returns this)
    bool Create(uint32_t id, int a, int b);         // 0x0082a140
    float GetScrollOffset();                        // 0x0082a4e0
    void Shutdown();                                // 0x0082a450
};
}
namespace SP {
class cStarRecordList {                             // eastl vector of star records at +0x44
public:
    void* mpBegin;                                  // +0x44
    void* mpEnd;                                    // +0x48
    void* mpCapacity;                               // +0x4c
    void erase(void* first, void* last);            // 0x00e25bd0
    ~cStarRecordList();                             // 0x00ae6970
};
}
namespace SP {
class cUIHints_s00e1_bbc0 {
public:
    int SetFlag(int flag, int value);               // 0x0067c420
};
}
namespace SP {
cUIHints_s00e1_bbc0* FUN_0067cac0();                           // 0x0067cac0
}
namespace SP {
class cSPUILayout {
public:
    IWinWindow* FindWindowByID(uint32_t id, int a); // 0x008105b0
};
}
namespace SP {
IMessageServer* MessageServer_s00e1_bbc0();                    // 0x0067dcc0
}
namespace SP {
void* operator_new(unsigned size, const char* pFile, int a, int b, int c, int d);   // 0x00f473a0
}
namespace SP {
void FUN_00e1c8b0(void* a, void* b, void* c);                                       // 0x00e1c8b0
}
namespace SP {
extern const uint32_t g_missionMessageIds[5];                                       // 0x014802b0
}
namespace SP {
namespace EA {
namespace Messaging {
void RemoveHandler(IMessageServer* pServer, void* pHandler, const uint32_t* pIds,
                   uint32_t count, uint32_t flags);                                 // 0x00571db0
}
}
}
namespace SP {
class cUIMissionCardPanel_s00e1_bbc0 {
public:
    void OnNotify(void* p1, void* p2, void* p3, void* p4);   // 0x00e186d0
    void ShutdownCard();                                     // 0x00e18810
    void DestroyMembers();                                   // 0x00e18980
    void ShutdownA();                                        // 0x00e18a30
};
}
namespace SP {
class cUIMissionButton {
public:
    void SetTracked();
    void Shutdown();                                                     // 0x00e1ca30
    void Destroy();                                                      // 0x00e1cba0
    void CreateMissionButton(void* p1, void* p2, void* p3, void* p4);    // 0x00e1cc80
    void ShutdownList();                                                 // 0x00e1cfb0

    void* mpVtbl00;                        // +0x00
    uint32_t mPad04;                       // +0x04
    void* mpVtbl08;                        // +0x08
    void* mpVtbl0c;                        // +0x0c
    uint32_t mTag10;                       // +0x10
    void* mpSelf14;                        // +0x14
    cSPUILayout* mpLayout;                 // +0x18
    uint32_t mPad1c;                       // +0x1c
    void* mpMission;                       // +0x20
    void* mpParent;                        // +0x24
    void* mpItem;                          // +0x28
    uint32_t mPad2c[5];                    // +0x2c
    void* mpVtbl40;                        // +0x40
    cStarRecordList mStars;                // +0x44
    uint32_t mPad50[2];                    // +0x50
    cScrollFrameVertical* mpScrollFrame;   // +0x58
    IObj5c* mpObj5c;                       // +0x5c
    IObj60* mpObj60;                       // +0x60
    IObj64* mpObj64;                       // +0x64
    IObj68* mpObj68;                       // +0x68
    cSPUIFeedList_s00e1_bbc0* mpFeedList;             // +0x6c
    cSPUIFeedCategory* mpCategoryA;        // +0x70
    cSPUIFeedCategory* mpCategoryB;        // +0x74
    IMessageServer* mpMessageServer;       // +0x78
    void* mpHandlerArg;                    // +0x7c
    const uint32_t* mpMessageIds;          // +0x80
    uint32_t mMessageIdCount;              // +0x84
    uint32_t mHandlerFlags;                // +0x88
    uint32_t mWindowId;                    // +0x8c
    int mIndex;                            // +0x90
};
}
namespace SP {
extern const uint32_t g_missionButtonVtbl00[];
}
namespace SP {
extern const uint32_t g_missionButtonVtbl08[];
}
namespace SP {
extern const uint32_t g_missionButtonVtbl0c[];
}
namespace SP {
extern const uint32_t g_missionButtonVtbl40[];
}
// ---- items of slice s00e1bbc0 end

// @ 0x00e12f80
void FUN_00e12f80(void* p, int v)
{
  if (p) ((void(__thiscall*)(void*, int, int))Vt(p)[0x7c / 4])(p, 1, v);
}

// @ 0x00e12fa0
void FUN_00e12fa0(void* p, int v)
{
  if (p) ((void(__thiscall*)(void*, int, int))Vt(p)[0x7c / 4])(p, 2, v);
}

// @ 0x00e12fc0
void FUN_00e12fc0(void* p, int v)
{
  if (p) ((void(__thiscall*)(void*, int))Vt(p)[0x80 / 4])(p, v);
}

// @ 0x00e12fe0
void cUICard_s00e1_2f80::Toggle()
{
  if (b10) ((void(__thiscall*)(void*, int))Vt(this)[0x2c / 4])(this, 1);
  else     ((void(__thiscall*)(void*, int))Vt(this)[0x28 / 4])(this, 1);
}

// @ 0x00e13000
void __fastcall FUN_00e13000(void* self)
{
  SPUIHelpers_GetElapsedSeconds();
  if (*(void**)((char*)self + 0x28)) {
    if (!cSPUIAnimator_Empty(*(void**)((char*)self + 0x28))) {
      *(uint8_t*)((char*)self + 0x11) = 1;
      cSPUIAnimator_Update(*(void**)((char*)self + 0x28));
      return;
    }
  }
}

// @ 0x00e130b0
bool cUICard_s00e1_2f80::HandleMessage(int, void* msg)
{
  struct CardMessage {
    int unknown[2];
    int type;   // +0x08
    int kind;   // +0x0c
  };
  CardMessage* m = (CardMessage*)msg;
  if (m->type == 0xc)
    ((void(__thiscall*)(void*))Vt(this)[0x24 / 4])(this);
  if (m->kind == 0x5235138) {
    if (m->type == 0x287259f6) {
      void* r = FUN_00b3d3f0(-0xc, this);
      FUN_00e18dd0(r);
    }
    return true;
  } else if (m->kind == 0x5235aa8) {
    if (m->type == 0x287259f6)
      ((void(__thiscall*)(void*))Vt(this)[0x20 / 4])(this);
    return true;
  }
  return false;
}

// @ 0x00e13160
int __stdcall FUN_00e13160(void* a, void* b)
{
  void* x;
  if (a) x = (void*)((int(__thiscall*)(void*, int))Vt(a)[0xc / 4])(a, 0x334c6eec);
  else x = 0;
  void* y;
  if (b) y = (void*)((int(__thiscall*)(void*, int))Vt(b)[0xc / 4])(b, 0x334c6eec);
  else y = 0;
  if (a) ((void(__thiscall*)(void*, int))Vt(a)[0xc / 4])(a, 0x334c6eef);
  void* z;
  if (b) z = (void*)((int(__thiscall*)(void*, int))Vt(b)[0xc / 4])(b, 0x334c6eef);
  else z = 0;
  if (x) {
    if (y) return *(float*)((char*)x + 0x98) > *(float*)((char*)y + 0x98);
    if (z) return (int)(((unsigned)z & 0xffffff00u) | 1u);
  }
  return (int)((unsigned)z & 0xffffff00u);
}

// @ 0x00e13210
void cUICard_s00e1_2f80::Release2()
{
  void* q;
  q = p44; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p40; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p3c; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p38; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p34; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p30; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p2c; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p24; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p20; if (q) ((void(__thiscall*)(void*))Vt(q)[8 / 4])(q);
  q = p1c; if (q) ((void(__thiscall*)(void*))Vt(q)[8 / 4])(q);
  q = p0c; if (q) ((void(__thiscall*)(void*))Vt(q)[8 / 4])(q);
  *(void**)((char*)this + 4) = (void*)0x13ec458;
  *(void**)this = (void*)0x13eb938;
}

// @ 0x00e132c0
void cUICard_s00e1_2f80::Teardown()
{
  void* q = p24;
  ((void(__thiscall*)(void*, void*))Vt(q)[0x108 / 4])(q, this);
  q = p24;
  if (q) { p24 = 0; ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q); }
  q = p1c;
  ((cSPUILayout_s00e1_2f80*)q)->Shutdown(1);
  q = p1c;
  if (q) { p1c = 0; ((void(__thiscall*)(void*))Vt(q)[8 / 4])(q); }
  q = p28;
  if (q) { ((void(__thiscall*)(void*, int))Vt(q)[0 / 4])(q, 1); p28 = 0; }
  q = p0c;
  if (q) {
    ((cSPUILayout_s00e1_2f80*)q)->Shutdown(1);
    q = p0c;
    if (q) { p0c = 0; ((void(__thiscall*)(void*))Vt(q)[8 / 4])(q); }
  }
  q = p20;
  if (q) FUN_00e2ed40();
  q = p20;
  if (q) { p20 = 0; ((void(__thiscall*)(void*))Vt(q)[8 / 4])(q); }
}

// @ 0x00e13360
void cUICard_s00e1_2f80::SetVisible(int v)
{
  if (p1c) {
    ((cSPUILayout_s00e1_2f80*)p1c)->SetVisibility(v);
    void* q = p24;
    if (q) ((void(__thiscall*)(void*, int, int))Vt(q)[0x7c / 4])(q, 1, v);
  }
}

// @ 0x00e13390
IWindow_s00e1_2f80* cUICard_s00e1_2f80::DoVcallF0(int v)
{
  return p24->FindWindowByID(v, true);
}

// @ 0x00e133b0
void cUIMissionCard_s00e1_2f80::InitForCreature(bool animate, int kind)
{
  IWindow_s00e1_2f80* card = DoVcallF0(((int(__thiscall*)(void*))Vt(this)[0x38 / 4])(this));
  IWindow_s00e1_2f80* old = p40;
  if (old && old != card) old->SetFlag(1, false);
  old = p40;
  if (card != old) {
    if (card) card->AddRef();
    p40 = card;
    if (old) old->Release();
  }
  if (!p30 || !p38 || !p3c || !p44 || !card) return;
  float t = SPUIHelpers_GetElapsedSeconds();
  p28->CancelAll();
  const Rect& compArea = p38->GetArea();
  const Rect& area3c = p3c->GetArea();
  const Rect& cardArea = card->GetArea();
  const Rect& area44 = p44->GetArea();
  AutoSizeWindowForText(p30, 0, 1);
  const Rect& bgArea = p30->GetArea();
  float top0 = bgArea.top;
  float bottom0 = bgArea.bottom;
  if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
    IWindow_s00e1_2f80* a = DoVcallF0(0x7f453b8);
    IWindow_s00e1_2f80* b = DoVcallF0(0x7f5abd0);
    b->GetArea();
    float h1 = Height(p30->GetArea());
    float h2 = Height(a->GetArea());
    bool big = h1 > h2;
    FUN_00e12f80(a, big);
    FUN_00e12f80(p30, !big);
    if (big) {
      const Rect& r = a->GetArea();
      top0 = r.top;
      bottom0 = r.bottom;
    }
  }
  float y = (bottom0 - top0) + top0;
  if (p2c && p2c->GetCaption()) {
    IWindow_s00e1_2f80* dw = p2c;
    dw->SetLayoutLocation(dw->GetArea().left, y);
    QueryWinExt(&p2c)->SetOption(true);
    const Rect& d = p2c->GetArea();
    y = (d.bottom - d.top) + y;
  }
  IWindow_s00e1_2f80* cw = p34;
  cw->SetLayoutLocation(cw->GetArea().left, y);
  bool notMode = SP_GetCurrentGameMode() != (void*)0x1654c10;
  IWinExt* ext = QueryWinExt(&p34);
  if (notMode) ext->SetOption(true);
  const Rect& c = p34->GetArea();
  float y2 = (c.bottom - c.top) + c.top;
  card->SetLayoutLocation(cardArea.left, y2);
  card->SetFlag(1, true);
  float y3 = (cardArea.bottom - cardArea.top) + y2;
  IWindow_s00e1_2f80* w;
  switch (kind) {
  case 1: w = DoVcallF0(0x574efda); break;
  case 2: w = DoVcallF0(0xf5a74bec); break;
  default: goto skip;
  }
  if (w) {
    const Rect& r = w->GetArea();
    float hh = r.bottom - r.top;
    float yy = y3 - top0;
    if (hh > yy) y3 = (hh - yy) + y3;
    w->SetLayoutLocation(r.left, (((y3 - top0) * 0.5f) + top0) - hh * 0.5f);
  }
skip:
  Rect ra, rb, rc;
  ra.left = f68;
  ra.top = f6c;
  ra.right = (f70 - f68) + f68;
  ra.bottom = (f6c + (float)fabs(y3 - f6c)) + 8.0f;
  rb.left = f78;
  rb.top = f7c;
  rb.right = (f80 - f78) + f78;
  rb.bottom = (f7c + (float)fabs(y3 - f7c)) + 8.0f;
  rc.left = f88;
  rc.top = f8c;
  rc.right = (f90 - f88) + f88;
  rc.bottom = ((ra.bottom - f74) + (f94 - f8c)) + f8c;
  IWindow_s00e1_2f80* w35 = DoVcallF0(0x35b08191);
  float wA = ra.bottom - ra.top;
  if (animate) {
    p28->AddAnimation(SPUICreateWindowAnimationTargetSize(p38, Vec2(ra.right - ra.left, wA), t,
        (float)fabs(wA - Height(compArea)) * 0.002f, 1), p38, 0);
    if (notMode) {
      float wB = rb.bottom - rb.top;
      p28->AddAnimation(SPUICreateWindowAnimationTargetSize(p3c, Vec2(rb.right - rb.left, wB), t,
          (float)fabs(wB - Height(area3c)) * 0.002f, 1), p3c, 0);
    }
    float wC = rc.bottom - rc.top;
    p28->AddAnimation(SPUICreateWindowAnimationTargetSize(p44, Vec2(rc.right - rc.left, wC), t,
        (float)fabs(wC - Height(area44)) * 0.002f, 1), p44, 0);
    if (w35) {
      p28->AddAnimation(SPUICreateWindowAnimationTargetSize(w35, Vec2(rc.right - rc.left, wC), t,
          (float)fabs(wC - Height(area44)) * 0.002f, 1), w35, 0);
    }
  } else {
    p38->SetSize(ra.right - ra.left, wA);
    if (notMode) p3c->SetSize(rb.right - rb.left, rb.bottom - rb.top);
    p44->SetSize(rc.right - rc.left, rc.bottom - rc.top);
    if (w35) w35->SetSize(rc.right - rc.left, rc.bottom - rc.top);
  }
  IWindow_s00e1_2f80* bw = DoVcallF0(0x5397388);
  if (bw) {
    IWinButton* btn = CastWinButton(bw);
    if (btn) btn->Command(4, 1);
  }
}

// @ 0x00e13b30
void cUIMissionCard_s00e1_2f80::Expand(bool a)
{
  InitForCreature(a, 0);
  ((void(__thiscall*)(void*))Vt(this)[0x30 / 4])(this);
}

// @ 0x00e14180
void CardLayout::ResizeToStyle0(bool animate)
{
    ((cUICard_s00e1_3b50*)this)->ResizeToContent(animate, 0);
    ((CardVtblView*)this)->v13();
}

// @ 0x00e141a0
CardLayout* CardLayout::InitA()
{
    mpVtbl1 = (void*)0x013ec458;
    m08 = 0;
    m0C = 0;
    m10 = 0;
    m11 = 0;
    m14 = 0.0f;
    m18 = 0.0f;
    m1C = 0;
    m20 = 0;
    mpMainWin = 0;
    mpAnimator = 0;
    mpDescWin = 0;
    mpTextWin = 0;
    mp34 = 0;
    mpWinA = 0;
    mpWinB = 0;
    mp40 = 0;
    mpWinC = 0;
    mpVtbl0 = (void*)0x0147fe14;
    mpVtbl1 = (void*)0x0147fe04;
    m98.f = 0.0f;
    mpMission = 0;
    return this;
}

// @ 0x00e14220
void CardLayout::RefreshChildWindows()
{
    IUIMission* mi = mpMission;
    if (mi) {
        IMissionBase* m = mi->Cast(0x2aa5ada);
        if (m)
            m->SetFlag(false);
    }
    IWindow_s00e1_3b50* w = mpMainWin->FindWindowByID(0x94a4a6ea, true);
    if (w)
        w->SetOwner(this);
    w = mpMainWin->FindWindowByID(0x54bf5692, true);
    if (w)
        w->SetOwner(this);
    w = mpMainWin->FindWindowByID(0x5397388, true);
    if (w)
        w->SetOwner(this);
    ((cUICard_s00e1_3b50*)this)->UpdateLayout();
}

// @ 0x00e142c0
uint32_t CardLayout::GetCardColor()
{
    if (mpMission == 0)
        return 0;
    IUIMission* mi = mpMission;
    if (mi == 0)
        return 0;
    IMissionBase* c = mi->Cast(0x2aa5ada);
    if (!c)
        return 0;
    if (c->IsHighlighted()) {
        IMissionBase* m = c->Cast(0x422227c);
        if (!m)
            return 0;
        c = ((IMissionMultiStep*)m)->GetCurrSubMission();
        if (!c)
            return 0;
    }
    if (c->IsComplete())
        return 0xff93bfa6;
    return (c->IsFailed() ? 0x3e2e7 : 0) + 0xffbbadbf;
}

// @ 0x00e14360
bool CardLayout::HandleEvent(void* sender, CardEvent* ev)
{
    if (ev->mType == 0xc)
        ((CardVtblView*)this)->v09();

    if (ev->mType == 0xa && ev->mId == 1) {
        IWindow_s00e1_3b50* w = (IWindow_s00e1_3b50*)sender;
        if (w->GetID() == 0x54bf5692 || w->GetID() == 0x5397388) {
            if (mpMission) {
                IMissionBase* m = mpMission->Cast(0x2aa5ada);
                if (m)
                    m->SetFlag(w == (IWindow_s00e1_3b50*)ev->mpSender);
            }
        }
    }

    switch (ev->mId) {
    case 0x5235aa8:
        if (ev->mType == 0x287259f6)
            ((CardVtblView*)this)->v08();
        return true;
    case 0x5235138:
        if (ev->mType == 0x287259f6) {
            if (GetCurrentGameMode_s00e1_3b50() == 0x1654c04 && GetCivStrategy()->mFlag148)
                return true;
            if (GetCurrentGameMode_s00e1_3b50() == 0x1654c02 && GetTribeStrategy()->TerrainNotHasKey())
                return true;
            if (GetCurrentGameMode_s00e1_3b50() == 0x1654c05 && GetSpaceUi()->IsSomething())
                return true;
            GetMissionPanel(-14, mpMission)->OpenPanel();
        }
        return true;
    case 0xf4e6882f:
        if (ev->mType == 0x287259f6 && mpMission) {
            CMissionTarget* q = (CMissionTarget*)mpMission->Cast(0x7406a570);
            if (q) {
                EventCtx ctx;
                ctx.Init();
                switch (GetCurrentGameMode_s00e1_3b50() - 0x1654c00) {
                case 0: ctx.mColor = 0x817d7b6d; break;
                case 1: ctx.mColor = 0x710c185a; break;
                case 2: ctx.mColor = 0x8799ddcb; break;
                case 4: ctx.mColor = 0x5126162d; break;
                case 5: ctx.mColor = 0xfeb98c35; break;
                default: break;
                }
                ctx.mFlag13 = 0;
                ctx.mFlag24 = 1;
                Vec3* p = &q->GetView()->mPoint;
                ctx.mPos = *p;
                sub_64a990(&ctx);
                ctx.Destroy();
            }
        }
        return true;
    default:
        return false;
    }
}

// @ 0x00e14590
uint32_t CardLayout::GetContentWinID()
{
    IUIMission* m = mpMission;
    if (m)
        return m->GetContentWinID();
    return 0x74bf58cb;
}

// @ 0x00e145b0
void CardLayout::UpdateButtonStateA(IWindow_s00e1_3b50* src)
{
    IWindow_s00e1_3b50* w1 = mpMainWin->FindWindowByID(0x574efda, true);
    IWindow_s00e1_3b50* w2 = mpMainWin->FindWindowByID(0x7591f955, true);
    if (!w1 || !w2)
        return;
    if (src->IsChecked()) {
        w1->SetVisible(1, 1);
        w2->SetColor(0x55ffffff);
        IWindow_s00e1_3b50* c = mpWinC;
        if (!c)
            return;
        c->SetVisible(1, 1);
        IWindow_s00e1_3b50* d = mpWinC;
        d->SetColor(d->GetColor() | 0x99000000);
    } else {
        w1->SetVisible(1, 0);
        w2->SetColor(0xffffffff);
        IWindow_s00e1_3b50* c = mpWinC;
        if (!c)
            return;
        c->SetVisible(1, 1);
        IWindow_s00e1_3b50* d = mpWinC;
        d->SetColor(d->GetColor() & 0xffffff);
    }
}

// @ 0x00e14690
void CardLayout::UpdateButtonStateB(ISelectable* src)
{
    IWindow_s00e1_3b50* w1 = mpMainWin->FindWindowByID(0xf5a74bec, true);
    IWindow_s00e1_3b50* w2 = mpMainWin->FindWindowByID(0x7591f955, true);
    if (!w1 || !w2)
        return;
    if (src->IsSelected()) {
        w1->SetVisible(1, 1);
        w2->SetColor(0x55ffffff);
        IWindow_s00e1_3b50* c = mpMainWin->FindWindowByID(0x35b08191, true);
        if (!c)
            return;
        c->SetVisible(1, 1);
        c->SetColor(c->GetColor() | 0x99000000);
    } else {
        w1->SetVisible(1, 0);
        w2->SetColor(0xffffffff);
        IWindow_s00e1_3b50* c = mpMainWin->FindWindowByID(0x35b08191, true);
        if (!c)
            return;
        c->SetVisible(1, 1);
        c->SetColor(c->GetColor() & 0xffffff);
    }
}

// @ 0x00e147a0
CardLayout* CardLayout::InitB()
{
    mpVtbl1 = (void*)0x013ec458;
    m08 = 0;
    m0C = 0;
    m10 = 0;
    m11 = 0;
    m14 = 0.0f;
    m18 = 0.0f;
    m1C = 0;
    m20 = 0;
    mpMainWin = 0;
    mpAnimator = 0;
    mpDescWin = 0;
    mpTextWin = 0;
    mp34 = 0;
    mpWinA = 0;
    mpWinB = 0;
    mp40 = 0;
    mpWinC = 0;
    mpVtbl0 = (void*)0x0147fe60;
    mpVtbl1 = (void*)0x0147fe50;
    m98.u = 0;
    return this;
}

// @ 0x00e14810
CardLayout* CardLayout::InitC()
{
    mpVtbl1 = (void*)0x013ec458;
    m08 = 0;
    m0C = 0;
    m10 = 0;
    m11 = 0;
    m14 = 0.0f;
    m18 = 0.0f;
    m1C = 0;
    m20 = 0;
    mpMainWin = 0;
    mpAnimator = 0;
    mpDescWin = 0;
    mpTextWin = 0;
    mp34 = 0;
    mpWinA = 0;
    mpWinB = 0;
    mp40 = 0;
    mpWinC = 0;
    mpVtbl0 = (void*)0x0147feac;
    mpVtbl1 = (void*)0x0147fe9c;
    m98.f = 0.0f;
    mWatch0.Init(5, false);
    mWatch0.SetTimeLimit(0, false);
    mWatch1.Init(4, false);
    mWatch1.SetTimeLimit(0, false);
    mF0 = 0;
    mF4 = 0;
    return this;
}

// @ 0x00e148d0
void CardLayout::ShowCard()
{
    if (m1C) {
        m1C->SetVisibility(true);
        if (mpMainWin)
            mpMainWin->SetVisible(1, 1);
    }
    mF0 = 1;
}

// @ 0x00e14900
void CardLayout::UpdateScrollButtons()
{
    if (mF0 == 1)
        return;
    ScrollGlobals* g = *(ScrollGlobals**)0x016c7aa4;
    int total = g->mpHost->mCount;
    int cur = g->mpSource->GetScrollPos();
    IWindow_s00e1_3b50* w = mpMainWin->FindWindowByID(0x74b5328, true);
    if (w)
        w->SetVisible(2, total > 0);
    w = mpMainWin->FindWindowByID(0x74b5329, true);
    if (w)
        w->SetVisible(2, total < cur - 1);
    CStr text;
    text.Init(0x21851ebe, 0x74bb7ec, 0);
    w = mpMainWin->FindWindowByID(0x74b6990, true);
    const wchar_t* str = text.GetText();
    if (w)
        w->SetText(str);
    text.Destroy();
}

// @ 0x00e149e0
void CardLayout::HideButtons()
{
    IWindow_s00e1_3b50* w = mpMainWin->FindWindowByID(0x7a15028, true);
    w->SetVisible(1, 0);
    w = mpMainWin->FindWindowByID(0x7a15027, true);
    w->SetVisible(1, 0);
}

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

// @ 0x00e15910
cUICardMissionCard::~cUICardMissionCard()
{
    if (mpTextZoom != nullptr)
        mpTextZoom->Release();
}

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

// @ 0x00e16090
void cMissionTracker::FUN_00e16090(IMission* m)
{
    if (!m)
        return;
    m->OnShown();
    if (mpStatusWin) {
        int fill = m->GetStatusFill();
        if (m->GetKind() == 5 || fill == 0) {
            mpStatusWin->SetFlag(1, false);
            mpStatusWin->SetCaption(gStr13ec468);
        } else {
            mpStatusWin->SetFlag(1, true);
            string16 status;
            m->GetStatusText(&status);
            mpStatusWin->SetCaption(status.mpBegin);
        }
    }

    IWindow_s00e1_5c00* wCount = mpRoot->FindWindowByID(0x740ea83e, true);
    IWindow_s00e1_5c00* wIcon = mpRoot->FindWindowByID(0x55d3e68, true);
    IWindow_s00e1_5c00* wTitle = mpRoot->FindWindowByID(0x52350c8, true);
    if (wCount && wIcon && wTitle) {
        string16 countText;
        m->GetTextB4(&countText);
        wCount->SetFlag(1, true);
        wCount->SetCaption(countText.mpBegin);
        if (countText.mpBegin == countText.mpEnd) {
            const Rect_s00e1_5c00& r = wCount->GetRealArea();
            Rect_s00e1_5c00 rc = r;
            rc.x1 = rc.x2;
            wCount->SetLayoutArea(rc);
        } else {
            IWinText* t = CastToText(wCount);
            if (t)
                t->SetEnabled(0);
        }
        bool hasLayout = false;
        int layoutId = m->FUN_00c2ec30();
        if (layoutId) {
            hasLayout = true;
            void* cache = ((cImageCacheOwner*)GetImageCache())->FUN_00e14c70();
            SetImageFromLayout(wIcon, cache, layoutId, -1);
        } else {
            wIcon->SetFlag(1, false);
        }
        const Rect_s00e1_5c00& countArea = wCount->GetRealArea();
        const Rect_s00e1_5c00& iconArea = wIcon->GetRealArea();
        Rect_s00e1_5c00 rc = iconArea;
        float width = rc.x2 - rc.x1;
        float x = countArea.x1;
        if (countText.mpBegin != countText.mpEnd)
            x -= 5.0f;
        rc.x2 = x;
        rc.x1 = x - width;
        wIcon->SetLayoutArea(rc);

        string16 titleText;
        m->GetTitleText(&titleText);
        wTitle->SetCaption(titleText.mpBegin);
        const Rect_s00e1_5c00& titleArea = wTitle->GetRealArea();
        float h = titleArea.y2 - titleArea.y1;
        wTitle->SetSize((hasLayout ? rc.x1 : rc.x2) - titleArea.x1, h);
    }

    string16 text98;
    m->GetTextA0(&text98);
    IWindow_s00e1_5c00* w5 = mpRoot->FindWindowByID(0x5235140, true);
    if (w5)
        w5->SetCaption(text98.mpBegin);
    string16 text9c;
    m->GetText98(&text9c);
    IWindow_s00e1_5c00* w6 = mpRoot->FindWindowByID(0x74cb0c14, true);
    if (w6)
        w6->SetCaption(text9c.mpBegin);

    IMissionImage* img = (IMissionImage*)m->Cast(0x7406a570);
    if (img) {
        IWindow_s00e1_5c00* wImage = mpRoot->FindWindowByID(0x5235098, true);
        void* tex = 0;
        if (wImage && img->FUN_00c2f320(&tex)) {
            cTextureInstanceWrapper* wrap = new(gNameUI, 0, 0, 0, 0) cTextureInstanceWrapper(tex);
            UIImage* im = new("UI/Image", 0, 0, 0, 0)
                UIImage(wrap, wrap->GetWidth(), wrap->GetHeight(), 0.0f, 0.0f, 1.0f, 1.0f, 0);
            if (im)
                im->AddRef();
            SetDrawableImage(wImage, im, -1);
            if (im)
                im->Release();
        }
        int stripVal = img->FUN_00c2e820();
        IWindow_s00e1_5c00* wStrip = mpRoot->FindWindowByID(0x94a4a6ea, true);
        if (wStrip) {
            if (!mpStrip.p) {
                mpStrip.Set(new(gNameUI, 0, 0, 0, 0) cSPUIRelationshipStrip_s00e1_5c00());
                mpStrip.p->Init(wStrip);
            }
            mpStrip.p->FUN_00e2ed70(stripVal);
            wStrip->SetFlag(1, true);
        }
    }

    IMissionValue* val = (IMissionValue*)m->Cast(0x34364118);
    if (val) {
        float v = val->FUN_00c2f650();
        IWindow_s00e1_5c00* wStrip = mpRoot->FindWindowByID(0x94a4a6ea, true);
        if (wStrip) {
            if (!mpStrip.p) {
                mpStrip.Set(new(gNameUI, 0, 0, 0, 0) cSPUIRelationshipStrip_s00e1_5c00());
                mpStrip.p->Init(wStrip);
            }
            mpStrip.p->FUN_00e2ef80(v);
            wStrip->SetOwner(this);
            wStrip->SetFlag(1, true);
        }
    }

    int iconWinId = m->FUN_00c2ec80();
    if (iconWinId) {
        IWindow_s00e1_5c00* wIcons = mpPanelLayout->FindWindowByID(iconWinId, true);
        if (wIcons) {
            ResourceKey key = {0, 0, 0};
            if (m->GetProgressIconLayout(&key)) {
                LayoutPtr* slot = &mpLayout;
                if (slot->p) {
                    slot->p->Shutdown(1);
                    if (slot->p) {
                        cSPUILayout_s00e1_5c00* old = slot->p;
                        slot->p = 0;
                        old->Release();
                    }
                }
                slot->Set(new(gNameUI, 0, 0, 0, 0) cSPUILayout_s00e1_5c00());
                slot->p->Init(&key, 1, 0x5b598fa);
                slot->p->SetParentWin(wIcons, 1, 0x5b598fa);
                wIcons->v94();
                wIcons->SetFlag(1, true);
                UpdateProgessIcons(slot->p, m);
            }
        }
    }

    FUN_00e145b0(m);
    FUN_00e14690(m);
    mfProgress = m->GetProgress();
    m->OnDone();
}

// @ 0x00e16a70
void cMissionPanel::FUN_00e16a70(bool bSkipList)
{
    string16 text;
    bool noPlayers = (g_pGame->mnPlayerCount == 0);
    cMissionLog* log = g_pGame->mpLog;

    if (!bSkipList) {
        IWindow_s00e1_6a70* titleCtl = mpRoot->FindWindowByID(0x52350c8, true);
        if (titleCtl) {
            log->GetTitle(&text);
            titleCtl->SetCaption(text.mpBegin);
        }
        if (mpTitleWin) {
            log->GetObjectiveTitle(&text);
            mpTitleWin->SetCaption(text.mpBegin);
            char16* caption = text.mpBegin;
            IWindow_s00e1_6a70* sub = mpRoot->FindWindowByID(0x7f5abd0, true);
            if (sub)
                sub->SetCaption(caption);
        }
        if (mpListWin) {
            float total = 0.0f;
            uint32_t colorA = mpRoot->FindWindowByID(0x792f6d0, true)->GetFillColor();
            uint32_t colorB = mpRoot->FindWindowByID(0x792f6d1, true)->GetFillColor();
            uint32_t colorC = mpRoot->FindWindowByID(0x7d78b80, true)->GetFillColor();
            int i = 0;
            int count = log->GetEntryCount();
            int* pProgress = mnProgress;

            for (; i < 3; i++, pProgress++) {
                uint32_t rowID = i + 0x792dcc5;
                IWindow_s00e1_6a70* rowWin = mpRoot->FindWindowByID(rowID + 0x2c53b, true);
                if (rowWin)
                    rowWin->SetFlag(2, true);

                bool done;
                if (i < count && log->IsEntryComplete(i))
                    done = true;
                else
                    done = false;

                bool show;
                if (i < count && (done || noPlayers))
                    show = true;
                else
                    show = false;
                if (rowWin)
                    rowWin->SetFlag(1, show);
                if (!show)
                    continue;

                IWindow_s00e1_6a70* container = mpRoot->FindWindowByID(rowID, true);
                IRowControl* ctl = container ? (IRowControl*)container->Cast(0x8ed27e7a) : 0;
                if (noPlayers && !done) {
                    ctl->SetValue(0, colorC);
                    ctl->SetValue(4, colorC);
                    ctl->SetValue(5, colorC);
                    ctl->SetValue(6, colorC);
                    ctl->SetValue(7, colorC);
                }
                string16 entryText;
                log->GetEntryText(i, &entryText);
                done = log->IsEntryActive(i);
                bool isNew = log->IsEntryNew(i);
                if (isNew) {
                    if (!done && !mbAlerted[i]) {
                        mbAlerted[i] = 1;
                        FUN_00e154d0(0);
                        mAlertTimer.SetTimeLimit(g_AlertTimeLimit, 1);
                    }
                } else {
                    mbAlerted[i] = 0;
                }
                int progress = log->GetEntryProgress(i);
                if (progress != *pProgress) {
                    *pProgress = progress;
                    if (rowWin)
                        rowWin->SetFlag(2, false);
                }

                bool notNew = !isNew;
                float adjust = 0.0f;
                const Rect_s00e1_6a70* area;
                if (ctl) {
                    container->SetFlag(2, noPlayers && notNew);
                    ctl->SetValue(1, notNew ? colorA : colorB);
                    area = &container->GetRealArea();
                    float oldHeight = area->y2 - area->y1;
                    float width = area->x2 - area->x1;
                    container->SetCaption(entryText.mpBegin);
                    ctl->SetEnabled(1);
                    float height = area->y2 - area->y1;
                    const float* pHeight = &mfMinRowHeight;
                    if (height > mfMinRowHeight)
                        pHeight = &height;
                    float newHeight = *pHeight;
                    ctl->GetWindow()->SetLayoutSize(width, newHeight);
                    adjust = newHeight - oldHeight;
                }
                const Rect_s00e1_6a70* rowArea = &rowWin->GetRealArea();
                Rect_s00e1_6a70 placed(rowArea->x1, total, rowArea->x2,
                            ((rowArea->y2 - rowArea->y1) + adjust) + total);
                rowWin->SetLayoutArea(placed);

                IWindow_s00e1_6a70* iconWin = mpRoot->FindWindowByID(i + 0x792dd06, true);
                if (iconWin) {
                    iconWin->SetFlag(1, notNew);
                    iconWin->SetFlag(0x10, !noPlayers);
                    if (notNew) {
                        ResourceKey_s00e1_6a70 key;
                        FillIconResource(&key, log->GetEntryIcon(i));
                        SetWindowImageResource(iconWin, &key, 0);
                    }
                }
                mpRoot->FindWindowByID(i + 0x7a2f850, true)->SetFlag(1, !notNew);
                total = ((rowArea->y2 - rowArea->y1) + total);
            }
            IWindow_s00e1_6a70* list = mpListWin;
            const Rect_s00e1_6a70& listArea = list->GetRealArea();
            list->SetLayoutSize(listArea.x2 - listArea.x1, total);
        }
    }

    IWindow_s00e1_6a70* timerWin = mpRoot->FindWindowByID(0x754f66e, true);
    if (timerWin) {
        bool hasTimer = log->HasTimer();
        timerWin->SetFlag(1, false);
        if (hasTimer) {
            log->GetTimerText(&text);
            timerWin->SetCaption(text.mpBegin);
            timerWin->SetFlag(2, log->GetTimerSeconds() < g_TimerWarnSeconds);
        }
    }
}

// @ 0x00e170f0
void cMissionPanel::FUN_00e170f0()
{
    if (mAlertTimer.mStart) {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        __int64 diff = mAlertTimer.mDeadline - now.QuadPart;
        if (diff < 0) {
            mAlertTimer.SetBoolProperty();
            HideButtons();
        }
    }

    switch (mState) {
    case 1:
        if (!(mpRoot->FindWindowByID(0x7a15027, true)->GetState28() & 1)) {
            if (mpRoot)
                mpRoot->SetFlag(2, false);
            mStateTimer.SetTimeLimit(g_Limit15a4ccc, 1);
            mState = 2;
        }
        break;
    case 2:
        if (mStateTimer.mStart && mStateTimer.IsTimeUp()) {
            FUN_00e12fa0(mpRoot, 1);
            FUN_00e14900();
            FUN_00e16a70(false);
            FUN_00e133b0(0, 0);
            v2c(0);
            mStateTimer.SetTimeLimit(g_Limit15a4ccc, 1);
            mState = 3;
        }
        break;
    case 3:
        if (mStateTimer.mStart && mStateTimer.IsTimeUp()) {
            mStateTimer.SetTimeLimit(g_Limit15a4cd0, 1);
            mState = 4;
        }
        break;
    case 4:
        if (mStateTimer.mStart && mStateTimer.IsTimeUp()) {
            v28(1);
            mStateTimer.SetTimeLimit(g_Limit15a4cd4, 1);
            mState = 5;
        }
        break;
    case 5:
        if (mStateTimer.mStart && mStateTimer.IsTimeUp()) {
            cMissionLog* log = g_pGame->mpLog;
            int noPlayers = (g_pGame->mnPlayerCount == 0);
            int count = log->GetEntryCount();
            for (int i = 0; i < count; ++i) {
                if (log->IsEntryComplete(i) || noPlayers) {
                    IWindow_s00e1_6a70* w = mpRoot->FindWindowByID(i + 0x795a200, true);
                    if (w)
                        w->SetFlag(2, false);
                    break;
                }
            }
            mStateTimer.SetBoolProperty();
            mState = 0;
        }
        break;
    }

    SPUIHelpers_GetElapsedSeconds();
    if (mpAnimator && !mpAnimator->Empty()) {
        mbAnimDirty = 1;
        mpAnimator->Update();
    }
}

// @ 0x00e173b0
void cMissionPanel::FUN_00e173b0()
{
    mbFlag10 = 1;
    FUN_00e16a70(false);
}

// @ 0x00e173c0
void cMissionPanel::FUN_00e173c0()
{
    mbFlag10 = 0;
    FUN_00e16a70(false);
}

// @ 0x00e173d0
PaintSystem::PaintSystem()
{
    ((GonzagoCtor*)this)->Init();      // SP::cGonzagoSubsystem::cGonzagoSubsystem
    mVtbl1c = (void*)0x13ec458;
    mZero20 = 0;
    mVtbl24 = (void*)0x13eb394;
    mVtbl0 = (void*)0x147ffe8;
    mVtbl4 = (void*)0x147ffe0;
    mVtbl1c = (void*)0x147ffd0;
    mVtbl24 = (void*)0x147ffc8;
    mpBegin = 0;
    mpEnd = 0;
    mpCap = 0;
    m3c = 0;
    m40 = 0;
    m44 = 0;
    m48 = 0;
    m4c = 0;
    m50 = 0;
    m54 = 0;
    m58 = g_f10;
    m5c = g_f5;
    m60 = g_f5;
}

// @ 0x00e17470
void PaintSystem::FUN_00e17470(int id)
{
    int i = 0;
    int count = (int)(mpEnd - mpBegin);
    for (; i < count; ++i) {
        IWindow_s00e1_6a70* p = mpBegin[i];
        if (p) {
            CardTarget* r = (CardTarget*)p->Cast(0x334c6eef);
            if (r && r->mId == id)
                r->FUN_00e16800();
        }
    }
}

// @ 0x00e17570
void cMissionPanel::FUN_00e17570(void* mission)
{
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

// @ 0x00e180d0
void cUIMissionCardList::ReleaseAll()
{
    int n = (int)(m_vec2c - m_vec28);
    for (int i = 0; i < n; i++) {
        void *obj = m_vec28[i];
        ((void (__thiscall *)(void *))(*(void ***)obj)[0x1c / 4])(obj);
    }
    ((void (__thiscall *)(void *, void **, void **))FUN_00e25bd0)(&m_vec28, m_vec28, m_vec2c);
    if (m_field54 != 0) {
        void *lay = m_field54;
        ((void (__thiscall *)(void *, int))FUN_00811ad0)(lay, 1);
        if (lay != 0) {
            m_field54 = 0;
            ((void (__thiscall *)(void *))(*(void ***)lay)[2])(lay);
        }
    }
    if (m_field3c != 0) {
        void *h = m_field3c;
        ((void (__thiscall *)(void *))FUN_00e492d0)(h);
        if (h != 0) {
            m_field3c = 0;
            ((void (__thiscall *)(void *))(*(void ***)h)[3])(h);
        }
    }
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

// @ 0x00e18200
void *cUIMissionCardPanel_s00e1_7c10::SetupMissionCard(void *mission, u32 a, u32 b, char c)
{
    void *raw = operator_new(0xa0, 0x13f6b3c, 0, 0, 0, 0);
    void *card = 0;
    if (raw != 0) {
        card = ((void *(__thiscall *)(void *))FUN_00e141a0)(raw);
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
    ((cUIMissionCard *)card)->Setup(mission, (char)a, (char)b);
    ((void (__thiscall *)(void **, void **, u32))FUN_00e18050)(m_vec28, m_vec2c, b);
    ((void (__thiscall *)(void *))FUN_00e14b70)(this);
    if (c != 0) {
        if (m_field3c != 0) {
            ((void (__thiscall *)(void *, void *))FUN_00e49360)(m_field3c, card);
        } else {
            void *rawObj = operator_new(0xa4, 0x13f09b4, 0, 0, 0, 0);
            void *obj = 0;
            if (rawObj != 0) {
                obj = ((void *(__thiscall *)(void *))FUN_00e4a6e0)(rawObj);
            }
            void *old = m_field3c;
            if (obj != old) {
                if (obj != 0) {
                    ((void (__thiscall *)(void *))(*(void ***)obj)[2])(obj);
                }
                m_field3c = obj;
                if (old != 0) {
                    ((void (__thiscall *)(void *))(*(void ***)old)[3])(old);
                }
            }
            ((void (__thiscall *)(void *, void *))FUN_00e49a40)(m_field3c, card);
        }
    }
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

// @ 0x00e18380
char cPanelHandler24::HandleMessage(u32 msg, void *arg)
{
    cUIMissionCardPanel_s00e1_7c10 *self = static_cast<cUIMissionCardPanel_s00e1_7c10 *>(this);
    if (msg == 0x38cf2fd) {
        void *p = *(void **)((u8 *)arg + 8);
        if (p == 0) {
            return 0;
        }
        void *mission = *(void **)((u8 *)p + 0x17c);
        if (mission == 0) {
            mission = p;
        }
        if (((bool (__thiscall *)(void *, void *))FUN_00e15cd0)(self, mission)) {
            if (((bool (__thiscall *)(void *))FUN_00c44c80)(mission)) {
                if (((bool (__thiscall *)(void *, void *, u32))FUN_00febe50)(GetMissionManager(), mission, 0)
                    || ((void *(__thiscall *)(void *))FUN_00febc70)(GetMissionManager()) == mission) {
                    self->UpdateCardDetails(mission);
                } else {
                    self->RemoveMissionCard(mission);
                }
            } else {
                self->RemoveMissionCard(mission);
            }
            return 0;
        }
        if (((bool (__thiscall *)(void *, void *, u32))FUN_00febe50)(GetMissionManager(), mission, 0)) {
            if ((u32)(unsigned long)SP_GetCurrentGameMode() == 0x1654c05) {
                self->SetupMissionCard(mission, 1, 1, 0);
            } else {
                u8 r = ((u8 (__thiscall *)(void *))(*(void ***)mission)[0x180 / 4])(mission);
                self->SetupMissionCard(mission, r, 1, 0);
            }
            return 0;
        }
        if (((void *(__thiscall *)(void *))FUN_00febc70)(GetMissionManager()) == mission) {
            if ((u32)(unsigned long)SP_GetCurrentGameMode() == 0x1654c05) {
                self->SetupMissionCard(mission, 1, 1, 0);
            } else {
                self->SetupMissionCard(mission, 1, 0, 0);
            }
        }
        return 0;
    }
    if (msg == 0x38cf2ff) {
        void *p = *(void **)((u8 *)arg + 8);
        self->RemoveMissionCard(p);
        return 0;
    }
    if (msg == 0xf46092d0) {
        void *p = *(void **)((u8 *)arg + 8);
        ((void (__thiscall *)(void *, void *))FUN_00e15c70)(self, p);
        // eax must be zero-extended on return (upper bits are compared).
        volatile int zero = 0;
        return (char)(zero + 1);
    }
    return 0;
}

// @ 0x00e184d0
void cUIMissionCardPanel_s00e1_7c10::RefreshFromMissionList()
{
    if ((u32)(unsigned long)SP_GetCurrentGameMode() != 0x1654c05) {
        return;
    }
    void *list = ((void *(__thiscall *)(void *))FUN_00fedd50)(GetMissionManager());
    void **begin = *(void ***)list;
    int n = (int)(*(void ***)((u8 *)list + 4) - begin);
    for (int i = 0; i < n; i++) {
        void *m = begin[i];
        if (m == 0) {
            continue;
        }
        void *mission = *(void **)((u8 *)m + 0x17c);
        if (mission == 0) {
            mission = m;
        }
        if (((bool (__thiscall *)(void *, void *))FUN_00e15cd0)(this, mission)) {
            continue;
        }
        if ((mission != 0 && ((bool (__thiscall *)(void *, void *, u32))FUN_00febe50)(GetMissionManager(), mission, 0))
            || ((void *(__thiscall *)(void *))FUN_00febc70)(GetMissionManager()) == mission) {
            SetupMissionCard(mission, 0, 1, 0);
        }
    }
    void *o = ((void *(__thiscall *)(void *))FUN_00575ea0)(
        ((void *(__thiscall *)(void *))FUN_00bfc5f0)(SP_SpaceGameGet()));
    if (o != 0) {
        AddMissionCard((u32)o);
    }
}

// @ 0x00e19c70
unsigned cMissionLog_s00e1_8d40::FUN_00e19c70(int mode)
{
    unsigned r = 0;
    switch (mode) {
    case (int)0x1654c01: r = 0xdb4fc333; break;
    case (int)0x1654c02: r = 0xe9c06b4e; break;
    case (int)0x1654c04: r = 0x355fd400; break;
    case (int)0x1654c05: r = 0x1cfaca92; break;
    }
    return r;
}

// @ 0x00e19d10
void cMissionLog_s00e1_8d40::FUN_00e19d10(int x)
{
    if (((cSPUILayout_s00e1_8d40*)mLayout)->IsVisible() && mField6c) {
        ((cVerbWin*)mField6c)->FUN_00663350(x);
    }
}

// @ 0x00e19d30
bool cSortMissions::operator()(int* a, int* b)
{
    int* pa = a ? (int*)(*(int(__thiscall**)(int*, int))((char*)(*(int**)a) + 0xc))(a, 0x2aa5ada) : 0;
    int* pb = b ? (int*)(*(int(__thiscall**)(int*, int))((char*)(*(int**)b) + 0xc))(b, 0x2aa5ada) : 0;
    void* list = ((cMissionManager*)SP_GetMissionManager())->GetMissionList();
    int* cur = (int*)*(int*)list;
    int n = (*((int*)list + 1) - (int)cur) >> 2;
    int k1 = -1;
    int k2 = -1;
    for (int i = 0; i < n; ++i) {
        int v = *cur;
        if (v == (int)pa) k1 = i;
        else if (v == (int)pb) k2 = i;
        if (k1 != -1 && k2 != -1) break;
        ++cur;
    }
    return k1 < k2;
}

// @ 0x00e1a1a0
uint32_t __fastcall FUN_00e1a1a0(CIndexedArray* pThis)
{
    int32_t iIndex = pThis->mIndex_90;
    if ((iIndex >= 0) && (iIndex < (int32_t)(pThis->mEnd_48 - pThis->mBegin_44)))
        return pThis->mBegin_44[iIndex];
    return 0;
}

// @ 0x00e1bbc0
namespace SP {
void cUIMissionButton::SetTracked()
{
    unsigned char* self;
    unsigned char fr[0x68];
    void* item;
    void* w;
    void* w2;
    void* t;
    void* s;
    void* t2;
    void* wnd;
    void* wnd2;
    void* wnd3;
    void* wnd4;
    void* wnd5;
    void* esi;
    void* ebp;
    void* ebx_;
    void* edi;
    void* mgr;
    void* empire;
    void* home;
    void* r;
    void* r2;
    void* obj;
    void* ownA;
    void* ownB;
    void* m;
    void* x;
    void* newp;
    void* o68;
    void* obj64;
    void* ecx5c;
    void* esiA;
    void* esiB;
    void* sel;
    void* newS;
    unsigned char al;
    unsigned f;
    int idx;
    int a;
    int b;
    int c;
    int kind;
    float fv;
    unsigned tag;

    self = (unsigned char*)this;
    FR(0x14) = (int)self;
    if (SPTR(self, 0x18) == 0) return;

    // Item for this button's index: array of pointers at +0x44 .. +0x48 (end).
    idx = SI(self, 0x90);
    item = 0;
    if (idx >= 0 && idx < ((SI(self, 0x48) - SI(self, 0x44)) >> 2))
        item = ((void**)SPTR(self, 0x44))[idx];

    FP(0x28) = item;
    FP(0x20) = 0;   // mission
    FP(0x10) = 0;   // sel
    FR(0x1c) = 0;   // ownB
    FP(0x24) = 0;   // ownA

    tag = UI(self, 0x10);
    if (tag == 0x1654c05) {
        if (item) FP(0x20) = VC1(void*, item, 0xc, unsigned, 0x2aa5ada);
    } else if (item) {
        FP(0x10) = VC1(void*, item, 0xc, unsigned, 0x14066ce5);
        if (FP(0x10)) {
            VC0(void, FP(0x10), 0x80);
            VC0(void, FP(0x10), 0x84);
            FP(0x24) = VC1(void*, FP(0x10), 0xc, unsigned, 0x7406a570);
            FR(0x1c) = (int)VC1(void*, FP(0x10), 0xc, unsigned, 0x34364118);
        }
    }

    // ---- window 0x51d2fb8: mission-type toggle ----
    w = FIND_WIN(SPTR(self, 0x18), 0x51d2fb8);
    if (w) {
        w2 = VC1(void*, w, 0xc, unsigned, 0x8ed27e7a);
        if (w2) {
            if (FP(0x20) == 0) {
                t = VC0(void*, w2, 0x10);
                VC2(void, t, 0x7c, int, 1, int, 0);
            } else {
                t = VC0(void*, w2, 0x10);
                VC2(void, t, 0x7c, int, 1, int, 1);
                VC2(void, w2, 0x28, int, 1, int, 1);
                mgr = ((void*(__stdcall*)(void*, int))(0xfeb9f0))(FP(0x20), 0);
                al = ((unsigned char(__thiscall*)(void*))(0xfebe50))(mgr);
                VC2(void, w2, 0x28, int, 4, int, (int)al);
            }
        }
    }

    // ---- window 0x3c4925e: enable flags ----
    s = FIND_WIN(SPTR(self, 0x18), 0x3c4925e);
    if (s) {
        if (FP(0x20) == 0) {
            VC2(void, s, 0x7c, int, 1, int, 0);
        } else {
            VC2(void, s, 0x7c, int, 1, int, 1);
            f = UI(FP(0x20), 0x130);
            if (((f >> 4) & 1) || (f & 1))
                VC2(void, s, 0x7c, int, 2, int, 0);
            else
                VC2(void, s, 0x7c, int, 2, int, 1);
        }
    }

    // ---- window 0x519cac8: title text ----
    t = FIND_WIN(SPTR(self, 0x18), 0x519cac8);
    if (t == 0) goto L_wnd_f3ec;
    VC2(void, t, 0x7c, int, 2, int, 1);
    FR(0x2c) = 0;   // wstring at 0x2c (begin), 0x30 (end), 0x34 (cap)
    FR(0x30) = 0;
    FR(0x34) = 0;
    ((void(__thiscall*)(void*, const wchar_t*))(0x579a90))(&FR(0x2c), (const wchar_t*)0x13ec468);
    if (FP(0x20) != 0) {
        VC1(void, FP(0x20), 0xc4, void*, &FR(0x2c));
    } else if (FP(0x10) != 0) {
        VC1(void, FP(0x10), 0x9c, void*, &FR(0x2c));
    } else if (FR(0x1c) != 0) {
        VC1(void, (void*)FR(0x1c), 0x9c, void*, &FR(0x2c));
    } else {
        ((void(__thiscall*)(void*, unsigned, unsigned, int))(0x6b5770))(&FR(0x3c), 0x8b96f855, 0x667c672, 0);
        obj = ((void*(__thiscall*)(void*))(0x6b55c0))(&FR(0x3c));
        ((void(__thiscall*)(void*, void*))(0x5c3d90))(&FR(0x2c), obj);
        ((void(__thiscall*)(void*))(0x6b5240))(&FR(0x3c));
    }
    VC1(void, t, 0x80, int, FR(0x2c));
    r = VC1(void*, t, 0xc, unsigned, 0xf15f4bd);
    if (r) VC1(void, r, 0x1c, int, 1);
    if (SPTR(self, 0x58)) ((void(__stdcall*)(int))(0x82a500))(1);
    if (((FR(0x34) - FR(0x2c)) & ~1) > 2 && FR(0x2c) != 0)
        ((void(__cdecl*)(void*))(0xf47380))((void*)FR(0x2c));

L_wnd_f3ec:
    // ---- window 0xf3ec5429: rewards text ----
    t2 = FIND_WIN(SPTR(self, 0x18), 0xf3ec5429);
    if (t2 == 0) goto L_release68;
    VC2(void, t2, 0x7c, int, 2, int, 1);
    FR(0x2c) = 0;
    FR(0x30) = 0;
    FR(0x34) = 0;
    ((void(__thiscall*)(void*, const wchar_t*))(0x579a90))(&FR(0x2c), (const wchar_t*)0x13ec468);
    if (FP(0x20) != 0) {
        ((void(__thiscall*)(void*, void*))(0xc48c20))(FP(0x20), &FR(0x2c));
    } else {
        m = FP(0x10);
        if (m != 0 && VC0(int, m, 0xa4)) {
            VC1(void, m, 0xa8, void*, &FR(0x2c));
        } else {
            m = (void*)FR(0x1c);
            if (m != 0 && VC0(int, m, 0xa4))
                VC1(void, m, 0xa8, void*, &FR(0x2c));
        }
    }
    VC1(void, t2, 0x80, int, FR(0x2c));
    if (((FR(0x34) - FR(0x2c)) & ~1) > 2 && FR(0x2c) != 0)
        ((void(__cdecl*)(void*))(0xf47380))((void*)FR(0x2c));

L_release68:
    // ---- release this+0x68 and this+0x64 ----
    if (SPTR(self, 0x68)) VC0(void, SPTR(self, 0x68), 0x20);
    if (SPTR(self, 0x64)) VC0(void, SPTR(self, 0x64), 0x8);

    // ---- window 0x519ccf8 + date/time ----
    ebx_ = FIND_WIN(SPTR(self, 0x18), 0x519ccf8);
    ((void(__thiscall*)(void*, int))(0x92e3d0))(&FR(0x50), 2);
    esi = 0;
    FR(0x5c) = 0;
    FR(0x60) = 0;
    FR(0x64) = 0;
    FR(0x18) = 0;
    if (ebx_ == 0) goto L_236;
    VC2(void, ebx_, 0x7c, int, 1, int, 0);
    if (FP(0x20) == 0) goto L_07f;
    empire = ((void*(__thiscall*)(void*))(0xc451e0))(FP(0x20));
    if (empire == 0) goto L_236;
    esi = ((void*(__thiscall*)(void*))(0xc30c80))(empire);
    if (esi == 0) goto L_236;
    ((void(__thiscall*)(void*, int))(0x7eb820))(&FR(0x50), 0xc);
    SI((void*)FR(0x5c), 4) = SI(esi, 0x508);
    SI((void*)FR(0x5c), 8) = SI(esi, 0x504);
    SI((void*)FR(0x5c), 0xc) = SI(esi, 0x50c);
    home = ((void*(__thiscall*)(void*))(0xc31730))(empire);
    if (home) SI((void*)FR(0x5c), 0x14) = (int)((void*(__thiscall*)(void*))(0xce6950))(home);
    SI((void*)FR(0x5c), 0x18) = 5;
    SI((void*)FR(0x5c), 0x1c) = SI(empire, 0x10);
    SI((void*)FR(0x5c), 0x24) = SI(empire, 0x84);
    SI((void*)FR(0x5c), 0x28) = 0;
    FR(0x18) = (int)&FR(0x50);
    goto L_159;

L_07f:
    if (FP(0x10) == 0) goto L_236;
    if (((void*(__cdecl*)())(0x67de90))() == 0) goto L_236;
    ownA = FP(0x24);
    if (ownA != 0 && ((void*(__thiscall*)(void*))(0xc2e780))(ownA) != 0) {
        r = ((void*(__thiscall*)(void*))(0xc2e780))(ownA);
        a = SI(r, 0x504);
        b = SI(r, 0x508);
        c = SI(r, 0x50c);
        obj = ((void*(__stdcall*)(int, int, int, int))(0x67de90))(8, a, b, c);
        goto L_ba54;
    }
    ownB = (void*)FR(0x1c);
    if (ownB == 0) goto L_236;
    if (((void*(__thiscall*)(void*))(0xc2f680))(ownB) == 0) goto L_236;
    FR(0x2c) = 0;
    FR(0x30) = 0;
    FR(0x34) = 0;
    r2 = ((void*(__thiscall*)(void*, int*))(0xc2f680))(ownB, &FR(0x2c));
    al = ((unsigned char(__thiscall*)(void*))(0xc8eb50))(r2);
    if (al == 0) goto L_236;
    a = FR(0x2c);
    b = FR(0x30);
    c = FR(0x34);
    kind = (UI(self, 0x10) != 0x1654c02) ? 10 : 9;
    obj = ((void*(__stdcall*)(int, int, int, int))(0x67de90))(kind, a, b, c);

L_ba54:
    FR(0x18) = (int)((void*(__thiscall*)(void*))(0xba54f0))(obj);
    if (FR(0x18) == 0) goto L_236;

L_159:
    // ---- stash the 0x18 object's sub-fields, then the this+0x64 / +0x68 objects ----
    esi = self + 0x64;
    FR(0x48) = FR(0x18);
    ecx5c = SPTR((void*)FR(0x18), 0xc);
    FR(0x3c) = SI(ecx5c, 8);
    FR(0x44) = SI(ecx5c, 0xc);
    FR(0x40) = SI(ecx5c, 4);
    if (SPTR(esi, 0) == 0) {
        newp = ((void*(__cdecl*)(unsigned, const char*, int, int, int, int))(0xf473a0))(0x9c, (const char*)0x1480298, 0, 0, 0, 0);
        if (newp) newp = ((void*(__thiscall*)(void*))(0xdd0da0))(newp);
        ((void(__thiscall*)(void*, void*))(0x6428c0))(esi, newp);
    }
    obj64 = SPTR(esi, 0);
    VC1(void, obj64, 0x4, void*, &FR(0x3c));
    ebp = self + 0x68;
    if (SPTR(ebp, 0) == 0) {
        newp = ((void*(__cdecl*)(unsigned, const char*, int, int, int, int))(0xf473a0))(0x108, (const char*)0x1480280, 0, 0, 0, 0);
        if (newp) newp = ((void*(__thiscall*)(void*))(0x657f70))(newp);
        ((void*(__thiscall*)(void*, void*))(0xb5f950))(ebp, newp);
    }
    o68 = SPTR(ebp, 0);
    ((void(__thiscall*)(void*, void*, void*, int, int))((*(void***)(o68))[0x1c / 4]))(o68, ebx_, SPTR(esi, 0), 0, 0);
    VC2(void, o68, 0x30, int, 0, int, 0);
    VC1(void, o68, 0x28, int, 1);
    VC2(void, ebx_, 0x7c, int, 1, int, 1);
    esi = 0;

L_236:
    // ---- window 0x94095992 ----
    wnd2 = FIND_WIN(SPTR(self, 0x18), 0x94095992);
    if (wnd2) VC2(void, wnd2, 0x7c, int, 1, int, 0);

    // ---- window 0xaaa0012: relationship strip ----
    wnd3 = FIND_WIN(SPTR(self, 0x18), 0xaaa0012);
    if (wnd3 == 0) goto L_370;
    VC2(void, wnd3, 0x7c, int, 1, int, 0);
    if (FR(0x18) != 0) goto L_370;
    FR(0x18) = 0;
    if (FP(0x20) != 0) {
        ((void(__thiscall*)(void*, int*))(0xc45ca0))(FP(0x20), &FR(0x2c));
        if (FR(0x18) != 0) {
            ecx5c = (void*)FR(0x18);
            FR(0x18) = 0;
            VC0(void, ecx5c, 0x4);
        }
        ((void(__cdecl*)(void*, void*, int, int, int))(0x806230))(&FR(0x2c), &FR(0x18), 0, -1, -1);
    } else {
        sel = FP(0x10);
        if (sel == 0) goto L_370;
        esiA = ((void*(__thiscall*)(void*))(0xa16f40))(&FR(0x18));
        VC1(void, sel, 0xb0, void*, esiA);
    }
    if (FR(0x18) == 0) goto L_370;
    if (wnd2) VC2(void, wnd2, 0x7c, int, 1, int, 1);
    VC2(void, wnd3, 0x7c, int, 1, int, 1);
    r = VC0(void*, wnd3, 0xa8);
    if (r) {
        r2 = VC1(void*, r, 0xc, unsigned, 0xef3c47cf);
        if (r2) VC1(void, r2, 0x14, int, FR(0x18));
    }
    VC0(void, wnd3, 0x90);
    if (FR(0x18)) VC0(void, (void*)FR(0x18), 0x4);

L_370:
    // ---- window 0x94a4a6ea: sub-widget ----
    wnd4 = FIND_WIN(SPTR(self, 0x18), 0x94a4a6ea);
    if (wnd4 == 0) goto L_424;
    VC2(void, wnd4, 0x7c, int, 1, int, 0);
    ebx_ = (void*)FR(0x24);
    ebp = (void*)FR(0x1c);
    if (ebx_ == 0 && ebp == 0) goto L_424;
    edi = self + 0x60;
    if (SPTR(edi, 0) == 0) {
        newS = ((void*(__cdecl*)(unsigned, const char*, int, int, int, int))(0xf473a0))(0xc, (const char*)0x13f6b3c, 0, 0, 0, 0);
        if (newS) newS = ((void*(__thiscall*)(void*))(0xe2ec40))(newS);
        ((void(__thiscall*)(void*, void*))(0x572620))(edi, newS);
        ((void(__thiscall*)(void*, void*))(0xe2ec60))(SPTR(edi, 0), wnd4);
    }
    if (ebx_ != 0) {
        r = ((void*(__thiscall*)(void*))(0xc2e820))(ebx_);
        ((void(__thiscall*)(void*, void*))(0xe2ed70))(SPTR(edi, 0), r);
    } else if (ebp != 0) {
        fv = ((float(__thiscall*)(void*))(0xc2f650))(ebp);
        ((void(__thiscall*)(void*, float))(0xe2ef80))(SPTR(edi, 0), fv);
    }
    VC2(void, wnd4, 0x7c, int, 1, int, 1);

L_424:
    if (FP(0x10) == 0) goto L_54f;
    sel = FP(0x10);
    x = ((void*(__thiscall*)(void*))(0xc2ec80))(sel);
    esi = self;
    if (x == 0) goto L_523;
    wnd5 = FIND_WIN(SPTR(self, 0x18), (unsigned)x);
    if (wnd5 == 0) goto L_542;
    FR(0x2c) = 0;
    FR(0x30) = 0;
    FR(0x34) = 0;
    al = ((unsigned char(__thiscall*)(void*, int*))(0xc2e4f0))(sel, &FR(0x2c));
    if (al == 0) goto L_542;
    esiA = self + 0x5c;
    ecx5c = SPTR(esiA, 0);
    if (ecx5c != 0) {
        ((void(__thiscall*)(void*, int, int, int))(0x8121b0))(ecx5c, 0, 1, 0x5b598fa);
        ((void(__thiscall*)(void*, int))(0x811ad0))(SPTR(esiA, 0), 1);
        ecx5c = SPTR(esiA, 0);
        if (ecx5c != 0) {
            SPTR(esiA, 0) = 0;
            VC0(void, ecx5c, 0x8);
        }
    }
    newS = ((void*(__cdecl*)(unsigned, const char*, int, int, int, int))(0xf473a0))(0x18, (const char*)0x13f6b3c, 0, 0, 0, 0);
    if (newS) newS = ((void*(__thiscall*)(void*))(0x810000))(newS);
    ((void(__thiscall*)(void*, void*))(0x572620))(esiA, newS);
    ((void(__thiscall*)(void*, int*, int, int))(0x8120d0))(SPTR(esiA, 0), &FR(0x2c), 1, 0x5b598fa);
    ((void(__thiscall*)(void*, void*, int, int))(0x8121b0))(SPTR(esiA, 0), wnd5, 1, 0x5b598fa);
    VC0(void, wnd5, 0x94);
    VC2(void, wnd5, 0x7c, int, 1, int, 1);
    ((void(__cdecl*)(void*, void*))(0xe2e790))(SPTR(esiA, 0), item);
    goto L_542;

L_523:
    esiA = self + 0x5c;
    if (SPTR(esiA, 0) == 0) goto L_542;
    ((void(__thiscall*)(void*, int))(0x811ad0))(SPTR(esiA, 0), 1);
    ecx5c = SPTR(esiA, 0);
    if (ecx5c == 0) goto L_542;
    SPTR(esiA, 0) = 0;
    VC0(void, ecx5c, 0x8);

L_542:
    VC0(void, sel, 0x88);

L_54f:
    if (FR(0x5c) != 0 && *(int*)(FR(0x5c) - 4) != 0)
        ((void(__cdecl*)(void*))(0xf47380))((void*)FR(0x5c));
}
}  // namespace SP

// @ 0x00e1ca30
namespace SP {
void cUIMissionButton::Shutdown()
{
    if (mpMessageServer != 0)
    {
        IMessageServer* pServer = mpMessageServer;
        mpMessageServer = 0;
        EA::Messaging::RemoveHandler(pServer, mpHandlerArg, mpMessageIds, mMessageIdCount, mHandlerFlags);
    }
    if (mpCategoryA != 0)
    {
        mpCategoryA->ShutdownChildren();
        if (mpCategoryA != 0)
        {
            cSPUIFeedCategory* pOld = mpCategoryA;
            mpCategoryA = 0;
            pOld->Release();
        }
    }
    if (mpCategoryB != 0)
    {
        mpCategoryB->ShutdownChildren();
        if (mpCategoryB != 0)
        {
            cSPUIFeedCategory* pOld = mpCategoryB;
            mpCategoryB = 0;
            pOld->Release();
        }
    }
    if (mpObj68 != 0)
    {
        mpObj68->Stop();
        if (mpObj68 != 0)
        {
            IObj68* pOld = mpObj68;
            mpObj68 = 0;
            pOld->Release();
        }
    }
    if (mpObj64 != 0)
    {
        mpObj64->Detach();
        if (mpObj64 != 0)
        {
            IObj64* pOld = mpObj64;
            mpObj64 = 0;
            pOld->mSub10.Release();
        }
    }
    if (mpObj60 != 0)
    {
        mpObj60->Stop();
        if (mpObj60 != 0)
        {
            IObj60* pOld = mpObj60;
            mpObj60 = 0;
            pOld->ReleaseB();
        }
    }
    mStars.erase(mStars.mpBegin, mStars.mpEnd);
    if (mpFeedList != 0)
    {
        mpFeedList->Shutdown();
        if (mpFeedList != 0)
        {
            cSPUIFeedList_s00e1_bbc0* pOld = mpFeedList;
            mpFeedList = 0;
            pOld->Release();
        }
    }
    if (mpScrollFrame != 0)
    {
        mpScrollFrame->Shutdown();
        if (mpScrollFrame != 0)
        {
            cScrollFrameVertical* pOld = mpScrollFrame;
            mpScrollFrame = 0;
            pOld->Release();
        }
    }
    if (mpLayout != 0)
    {
        IWinWindow* pHandlerWindow = mpLayout->FindWindowByID(0x5ee1ee0, 1);
        if (pHandlerWindow != 0)
            pHandlerWindow->SetHandler(&mpVtbl08);
    }
    reinterpret_cast<cUIMissionCardPanel_s00e1_bbc0*>(this)->ShutdownCard();
}
}  // namespace SP

// @ 0x00e1cb80
namespace SP {
void FUN_00e1cb80(void* p1, void* p2, void* p3)
{
    FUN_00e1c8b0(p1, p2, p3);
}
}  // namespace SP

// @ 0x00e1cba0
namespace SP {
void cUIMissionButton::Destroy()
{
    mpVtbl00 = (void*)&g_missionButtonVtbl00;
    mpVtbl08 = (void*)&g_missionButtonVtbl08;
    mpVtbl0c = (void*)&g_missionButtonVtbl0c;
    mpVtbl40 = (void*)&g_missionButtonVtbl40;

    Shutdown();

    // The original repeats the message-handler removal here (it is already done by Shutdown, so
    // this copy never runs; it is kept because the retail body contains it).
    if (mpMessageServer != 0)
    {
        IMessageServer* pServer = mpMessageServer;
        mpMessageServer = 0;
        EA::Messaging::RemoveHandler(pServer, mpHandlerArg, mpMessageIds, mMessageIdCount, mHandlerFlags);
    }

    if (mpCategoryB != 0)
        mpCategoryB->Release();
    if (mpCategoryA != 0)
        mpCategoryA->Release();
    if (mpFeedList != 0)
        mpFeedList->Release();
    if (mpObj68 != 0)
        mpObj68->Release();
    if (mpObj64 != 0)
        mpObj64->mSub10.Release();
    if (mpObj60 != 0)
        mpObj60->ReleaseB();
    if (mpObj5c != 0)
        mpObj5c->ReleaseB();
    if (mpScrollFrame != 0)
        mpScrollFrame->Release();

    mStars.~cStarRecordList();

    reinterpret_cast<cUIMissionCardPanel_s00e1_bbc0*>(this)->DestroyMembers();
}
}  // namespace SP

// @ 0x00e1cc80
namespace SP {
void cUIMissionButton::CreateMissionButton(void* p1, void* p2, void* p3, void* p4)
{
    ((IWinWindow*)this)->Activate();
    reinterpret_cast<cUIMissionCardPanel_s00e1_bbc0*>(this)->OnNotify(p1, p2, p3, p4);
    if (mpLayout == 0)
        return;

    void* pRawFeed = operator_new(0x6c, (const char*)0x13f6b3c, 0, 0, 0, 0);
    cSPUIFeedList_s00e1_bbc0* pNewFeed = pRawFeed != 0 ? (cSPUIFeedList_s00e1_bbc0*)((cSPUIFeedList_s00e1_bbc0*)pRawFeed)->Ctor() : 0;
    {
        cSPUIFeedList_s00e1_bbc0* pOldFeed = mpFeedList;
        if (pNewFeed != pOldFeed)
        {
            if (pNewFeed != 0)
                pNewFeed->AddRef();
            mpFeedList = pNewFeed;
            if (pOldFeed != 0)
                pOldFeed->Release();
        }
    }

    cSPUIFeedList_s00e1_bbc0* pFeed = mpFeedList;
    pFeed->AddWindow(mpLayout->FindWindowByID(0x519ab80, 1), 0x215ee951, 0, 0);

    {
        void* pNewCatA = mpFeedList->FindEntry(0x9e5ecccf);
        cSPUIFeedCategory* pOldCatA = mpCategoryA;
        if (pNewCatA != pOldCatA)
        {
            if (pNewCatA != 0)
                ((IRefObjB*)pNewCatA)->AddRef();
            mpCategoryA = (cSPUIFeedCategory*)pNewCatA;
            if (pOldCatA != 0)
                pOldCatA->Release();
        }
    }
    {
        void* pNewCatB = mpFeedList->FindEntry(0x897576da);
        cSPUIFeedCategory* pOldCatB = mpCategoryB;
        if (pNewCatB != pOldCatB)
        {
            if (pNewCatB != 0)
                ((IRefObjB*)pNewCatB)->AddRef();
            mpCategoryB = (cSPUIFeedCategory*)pNewCatB;
            if (pOldCatB != 0)
                pOldCatB->Release();
        }
    }

    IWinWindow* pScroll = mpLayout->FindWindowByID(0x519cac8, 1);
    if (pScroll != 0)
    {
        pScroll->Attach();

        void* pRawSfv = operator_new(0x48, "UI/cSPUIScrollFrameVertical", 0, 0, 0, 0);
        cScrollFrameVertical* pNewSfv =
            pRawSfv != 0 ? (cScrollFrameVertical*)((cScrollFrameVertical*)pRawSfv)->Ctor() : 0;
        {
            cScrollFrameVertical* pOldSfv = mpScrollFrame;
            if (pNewSfv != pOldSfv)
            {
                if (pNewSfv != 0)
                    pNewSfv->AddRef();
                mpScrollFrame = pNewSfv;
                if (pOldSfv != 0)
                    pOldSfv->Release();
            }
        }

        if (mpScrollFrame->Create(0xaef7d6ba, 1, 0))
        {
            IWinWindow* pContent = (IWinWindow*)pScroll->GetContent();
            IWinWindow* pObj10 = mpScrollFrame->mpObj10;
            IWinWindow* pObj18 = mpScrollFrame->mpObj18;
            pContent->SetParent(pObj10);

            float4* pRect = pScroll->GetRect();
            float4 rect;
            rect.x = pRect->x;
            rect.y = pRect->y;
            rect.z = pRect->z;
            rect.w = pRect->w;
            rect.z += mpScrollFrame->GetScrollOffset();
            pObj10->SetRect(&rect);

            pContent->SetOwner(pScroll);
            pObj18->SetParent(pScroll);
            pScroll->SetPosition(0.0f, 0.0f);
        }
    }

    IWinWindow* pWindow = mpLayout->FindWindowByID(0x67a2ae0, 1);
    if (pWindow != 0)
    {
        pWindow->Attach();
        pWindow->SetSize(4, 1);
        mWindowId = 0x67a2ae0;
    }

    if (mpCategoryA != 0)
        mpCategoryA->ShutdownChildren();
    if (mpCategoryB != 0)
        mpCategoryB->ShutdownChildren();
    mStars.erase(mStars.mpBegin, mStars.mpEnd);
    SetTracked();

    void* pHandlerArg = &mpVtbl0c;
    IMessageServer* pServer = MessageServer_s00e1_bbc0();
    mpMessageServer = pServer;
    mpHandlerArg = pHandlerArg;
    mpMessageIds = g_missionMessageIds;
    mMessageIdCount = 5;
    mHandlerFlags = 0;
    if (pServer != 0 && pHandlerArg != 0)
    {
        uint32_t offset = 0;
        do
        {
            pServer->Subscribe(pHandlerArg, *(const uint32_t*)((const char*)g_missionMessageIds + offset));
            offset += 4;
        } while (offset < 0x14);
    }

    if (pWindow != 0)
        pWindow->Release();
    if (pScroll != 0)
        pScroll->Release();
}
}  // namespace SP

// @ 0x00e1cfb0
namespace SP {
void cUIMissionButton::ShutdownList()
{
    if (mpFeedList != 0)
        mpFeedList->SetEnabled(false);
    if (mpCategoryA != 0)
        mpCategoryA->ShutdownChildren();
    if (mpCategoryB != 0)
        mpCategoryB->ShutdownChildren();
    mStars.erase(mStars.mpBegin, mStars.mpEnd);
    SetTracked();
    cUIHints_s00e1_bbc0* pHints = FUN_0067cac0();
    if (pHints != 0)
        FUN_0067cac0()->SetFlag(1, 1);
    reinterpret_cast<cUIMissionCardPanel_s00e1_bbc0*>(this)->ShutdownA();
}
}  // namespace SP

// @ 0x00e1d020
void cUIMissionCardPanel_s00e1_d020::Refresh()
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
            IWindow_s00e1_d020* pSlot = (IWindow_s00e1_d020*)mSlots.mpBegin[i];
            if (mnMissionType != 0x1654c05)
                pSlot->GetCaption();

            if (FUN_00665410(0x81b50b35, -1) != nullptr) {
                WString sText;
                IWindow_s00e1_d020* pParent = (IWindow_s00e1_d020*)pSlot;
                if (pParent != nullptr)
                    pParent->GetObject(0x2aa5ada);
                IWindow_s00e1_d020* pCard = pParent != nullptr
                    ? (IWindow_s00e1_d020*)pParent->GetObject(0x14066ce5) : nullptr;
                if (pCard != nullptr) {
                    pCard->Slot084();
                    pCard->Slot090();
                    pCard->Slot088();
                } else {
                    cSPMission_s00e1_d020* pMission = (cSPMission_s00e1_d020*)pSlot->GetObject(0x14066ce5);
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
        cUIMissionCardPanel_s00e1_d020* pPanel = (cUIMissionCardPanel_s00e1_d020*)FUN_00b3d400();
        if (pPanel == nullptr)
            return true;

        if (bPressed) {
            FUN_00febe00((cSPMission_s00e1_d020*)pMission);
            if (FUN_00fec960((cSPMission_s00e1_d020*)pMission)) {
                FUN_00e18200(pMission, 0, 1, 0);
            } else {
                mnButtonId = 0x29bcd888;
                uint32_t colors[3] = { 0x29bcd888, 0xb1b104, 0xf5f6fde8 };
                FUN_00809db0((uint8_t*)this + 0x38, colors);
                pMsg->mpSender->SetFlags(4, 0);
            }
        } else {
            FUN_00febe00((cSPMission_s00e1_d020*)pMission);
        }

        FeedItem* pItem = ((FeedListCategory*)mnCardIndex)->Find(mnButtonId + 0x6146391);
        if (pItem != nullptr) {
            FUN_00febf80((cSPMission_s00e1_d020*)pMission);
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
    ((cUIMissionCardPanel_s00e1_d020*)((uint8_t*)this - 0x08))->Refresh();
    return true;
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

// @ 0x00e2e8a0
void* __cdecl FUN_00e2e8a0(void* pBegin, void* pEnd, uint32_t nKeyA, uint32_t nKeyB)
{
    uint32_t* p = (uint32_t*)pBegin;
    uint32_t* pLast = (uint32_t*)pEnd;
    while (p != pLast && (p[0] != nKeyA || p[1] != nKeyB))
        p += 7;
    return p;
}

// @ 0x00e2e8d0
void __cdecl FUN_00e2e8d0(float fX, float fY, float fOffset, tRectEdge* pEdge, float* pfX, float* pfY, uint32_t* pFlag)
{
    float fHalfW = (pEdge->x1 - pEdge->x0) * g_kHalf;
    float fHigh = (pEdge->y1 - pEdge->y0) + fOffset;
    fHalfW = -fHalfW;
    fHigh = -fHigh;
    *pfX = fHalfW + fX;
    *pfY = fHigh + fY;

    tArea area;
    GetMainWindowArea(&area);
    if (area.x > *pfX)
        *pfX = area.x;

    float fExtent = pEdge->x1 - pEdge->x0;
    if (*pfX + fExtent > area.z)
    {
        *pfX = area.z - fExtent;
        *pFlag = 0;
        return;
    }
    *pFlag = 0;
}

// @ 0x00e2e990
void __cdecl FUN_00e2e990(tArea* pVec, float fOffset, tRectEdge* pEdge, float* pfX, float* pfY, uint32_t* pFlag)
{
    tArea vView;
    ((tApp2*)App())->v58()->CenterOverObject(&vView, pVec);

    tArea area;
    GetMainWindowArea(&area);
    *pfX = (vView.x + g_kOne) * area.z * g_kHalf;
    *pfY = (g_kOne - vView.y) * area.w * g_kHalf;

    float fHalfW = (pEdge->x1 - pEdge->x0) * g_kHalf;
    float fHigh = (pEdge->y1 - pEdge->y0) + fOffset;
    fHalfW = -fHalfW;
    fHigh = -fHigh;
    *pfX = fHalfW + *pfX;
    *pfY = fHigh + *pfY;

    tArea area2;
    GetMainWindowArea(&area2);
    if (area2.x > *pfX)
        *pfX = area2.x;

    float fExtent = pEdge->x1 - pEdge->x0;
    if (*pfX + fExtent > area2.z)
    {
        *pfX = area2.z - fExtent;
        *pFlag = 0;
        return;
    }
    *pFlag = 0;
}

// @ 0x00e2eab0
void __cdecl FUN_00e2eab0(tIWindowEx* pWindow, uint32_t nA, uint32_t nB, uint32_t nC, uint32_t nD, float fOffset)
{
    tArea vCamera;
    tArea vDir;
    ((tApp2*)App())->v58()->GetCameraLocationInfo(0, 0, &vCamera, &vDir);

    float fDistance = pWindow->v70();
    fDistance *= g_kTenPercent;
    if (fDistance <= g_kTwenty)
        fDistance = g_kTwenty;

    tArea* pPos = (tArea*)pWindow->v2c();
    tArea vOffset;
    vOffset.x = vDir.x * fDistance + pPos->x;
    vOffset.y = vDir.y * fDistance + pPos->y;
    vOffset.z = vDir.z * fDistance + pPos->z;

    FUN_00e2e990(&vOffset, fOffset, (tRectEdge*)nA, (float*)nB, (float*)nC, (uint32_t*)nD);
}

// @ 0x00e2eba0
char* __cdecl FUN_00e2eba0(cSimNoun* pNoun)
{
    switch (pNoun->GetNounType())
    {
    case 1:
        if (pNoun->FUN_00b8d9b0() != 0)
            return g_szStatusBusy;
        if (((cTerraformingManager*)TerraformingManager(pNoun))->F670() != 0)
        {
            if ((pNoun->mn2c & 0x800) != 0)
                return g_szStatusLocked;
            if (pNoun->mpd0 != pNoun->mpd4)
                return g_szStatusTerraform;
            return g_szStatusUnknown;
        }
        break;
    case 2:
        return g_szStatusTerraformed;
    case 4:
        return g_szStatusProbe;
    case 5:
        return g_szStatusOther;
    }
    return g_szStatusNone;
}

// @ 0x00e2ec40
void cSPUIRelationshipStrip::FUN_00e2ec40()
{
    mn04 = 0;
    mpVtable = (uint32_t)g_stripVtable;
    mp08 = 0;
}
