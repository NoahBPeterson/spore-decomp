// src/game/SPGonzago/_at_00e10000.cpp -- migrated from slice(s) s00e1eab0, s00e1df10, s00e1d020, s00e18d40, s00e17c10 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00e10000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPMission.h"
#include "SP/cIGonzagoSubsystem.h"
#include "SP/cString.h"
#include <string.h>
#include <stddef.h>
#include <math.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void   FUN_00810590(void *layout, int v, int f); // 0x00810590 cSPUILayout::SetVisibility
extern "C" bool   FUN_00810070(void *layout);               // 0x00810070 cSPUILayout::IsVisible
extern "C" void   FUN_00e5c780(void *tree, void *out, void *key); // 0x00e5c780 eastl::rbtree find
extern "C" void  *FUN_00921580(void *node);                 // 0x00921580 RBTreeIncrement
extern "C" void  *operator_delete_array(void *p);           // 0x00f47380
extern "C" void  *FUN_00b3d3f0();                           // 0x00b3d3f0
extern "C" void  *MessageServer();                           // 0x0067dcc0
extern "C" bool   FUN_008120d0(void *layout, void *key, bool b, int c); // 0x008120d0 cSPUILayout::Init
extern "C" void  *FUN_008105b0(void *layout, int id, bool b); // 0x008105b0 FindWindowByID
extern "C" void  *FUN_00810000(void *o);                     // 0x00810000 cConnectionDialog ctor

// ---- items of slice s00e17c10 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
extern "C" void   FUN_00810590(void *layout, int v, int f); // 0x00810590 cSPUILayout::SetVisibility
extern "C" bool   FUN_00810070(void *layout);               // 0x00810070 cSPUILayout::IsVisible
extern "C" void   FUN_00e5c780(void *tree, void *out, void *key); // 0x00e5c780 eastl::rbtree find
extern "C" void  *FUN_00921580(void *node);                 // 0x00921580 RBTreeIncrement
extern "C" void  *operator_delete_array(void *p);           // 0x00f47380
extern "C" void  *FUN_00b3d3f0();                           // 0x00b3d3f0
extern "C" void   FUN_00e30a60(void *o, u32 v);             // 0x00e30a60
extern "C" void   FUN_00e30ae0(void *o, u32 v);             // 0x00e30ae0
extern "C" void   FUN_00571db0(u32 a, u32 b, u32 c, u32 d, u32 e); // 0x00571db0 RemoveHandler
extern "C" void  *operator_new(u32 size, u32 file, u32 line, u32 a, u32 b, u32 c); // 0x00f473a0
extern "C" void  *MessageServer();                           // 0x0067dcc0
extern "C" bool   FUN_008120d0(void *layout, void *key, bool b, int c); // 0x008120d0 cSPUILayout::Init
extern "C" void  *FUN_008105b0(void *layout, int id, bool b); // 0x008105b0 FindWindowByID
extern "C" void  *FUN_00810000(void *o);                     // 0x00810000 cConnectionDialog ctor
extern "C" void   FUN_00e30990(void *o, u32 arg);           // 0x00e30990
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
struct cUIMissionCardPanel : cPanelHead0c, cPanelMsg0c, cPanelMsg24, cPanelHandler24 {
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
void cUIMissionCardPanel::ForEach(u32 a, u32 b)
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
// ---- items of slice s00e17c10 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void   FUN_00e30a60(void *o, u32 v);             // 0x00e30a60
extern "C" void   FUN_00e30ae0(void *o, u32 v);             // 0x00e30ae0
extern "C" void   FUN_00571db0(u32 a, u32 b, u32 c, u32 d, u32 e); // 0x00571db0 RemoveHandler
extern "C" void  *operator_new(u32 size, u32 file, u32 line, u32 a, u32 b, u32 c); // 0x00f473a0
extern "C" void   FUN_00e30990(void *o, u32 arg);           // 0x00e30990

// ---- items of slice s00e18d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char vtbl_1480160[], vtbl_1480110[], vtbl_148010c[], vtbl_1480104[],
            vtbl_14800f4[], vtbl_1480080[], vtbl_14426a0[];
void* operator new(unsigned size, const char* name, int flags, int line, const char* file, int line2); // EA 0xf473a0
inline void* operator new(unsigned, void* p) { return p; }
void  operator_delete__(void* p);                       // 0x00f47380
static inline void** Vt(void* p) { return *(void***)p; }
class cSPUILayout_s00e1_8d40 { public:
    void* FindWindowByID(int id, int flag);             // 0x008105b0  (ret 8)
    void  SetVisibility(int v);                         // 0x00810590  (ret 4)
    bool  IsVisible();                                  // 0x00810070
    void  Shutdown(int v);                              // 0x00811ad0  (ret 4)
};
struct cGameTimeManager {
    bool IncPauseGate(void* k);                         // 0x00b32220
    bool DecPauseGate(void* k);                         // 0x00b32250
};
struct cWinMgr {                                        // cUIWindowManager
    bool FUN_00e2f3c0(int id);                          // 0x00e2f3c0
    void FUN_00e2f370();                                // 0x00e2f370
    void FUN_00e30dc0();                                // 0x00e30dc0
    void FUN_00e30e20(int a, int b, int c, int d, int e); // 0x00e30e20
    void FUN_00e31030(int a, int b, int c, int d);      // 0x00e31030
};
struct cTribeStrategy { bool FUN_00cd44a0(); };         // 0x00cd44a0
struct cSporepediaObj { bool FUN_01065e20(); };         // 0x01065e20
namespace SP {
class cGonzagoSubsystem_s00e1_8d40 { public:
    cGonzagoSubsystem_s00e1_8d40();                                // 0x00b5b960
    ~cGonzagoSubsystem_s00e1_8d40();                               // 0x00b5b9a0
    void PreGameModeTransition(int a, int b);           // 0x00b5b930
    void PostGameModeTransition(int a, int b);          // 0x00b5b900
};
}
struct cMissionLog;   // fwd
struct cFeedbackTree {
    void* m00;          // +0x00  (panel 0x3c)
    void* mAnchor;      // +0x04  (panel 0x40) end node (self)
    void* mRoot;        // +0x08  (panel 0x44) root / begin
    int   mSize;        // +0x0c  (panel 0x48)
    char  mFlag;        // +0x10  (panel 0x4c)
    char  pad11[3];
    int   mSize2;       // +0x14  (panel 0x50)

    void  FUN_00e19160(void* node);                                  // 0x00e19160
    void* FUN_00e191a0(void* out, void* key, void* flag);            // 0x00e191a0
    void  FUN_00e18d40(void** out, void* pos, int* value, char flag); // 0x00e18d40
    void* FUN_00e5c780(void* out, void* key);                        // 0x00e5c780
};
struct cPanel {
    char          pad00[0x2c];
    int           mMode;         // +0x2c
    cSPUILayout_s00e1_8d40*  mLayout;       // +0x30
    void*         mHolder;       // +0x34
    void*         mScrollRoot;   // +0x38
    cFeedbackTree mTree;         // +0x3c (0x18 bytes)
    char          pad54[4];      // +0x54
    void*         mBlurEffect;   // +0x58
    void*         mWinMgr;       // +0x5c
    void*         mMsgServer;    // +0x60
    void*         mHandlerPtr;   // +0x64
    void*         mHandlerId;    // +0x68
    int           mHandlerA;     // +0x6c
    int           mHandlerB;     // +0x70
    void*         mListNext;     // +0x74
    void*         mListPrev;     // +0x78

    cPanel();                                                       // 0x00e19680
    ~cPanel();                                                      // 0x00e193f0
    void FUN_00e188b0(int hash);                                    // 0x00e188b0
    void* FUN_00e18b10(void* p);                                    // 0x00e18b10
    void FUN_00e18b50();                                            // 0x00e18b50
    void FUN_00e18cb0(int id);                                      // 0x00e18cb0
    void FUN_00e18dd0(void* p, int a);                              // 0x00e18dd0
    void FUN_00e19010();                                            // 0x00e19010
    void FUN_00e190c0(void* p);                                     // 0x00e190c0
    bool FUN_00e192a0(int, void* msg);                              // 0x00e192a0
    void FUN_00e19350(unsigned key, int arg);                       // 0x00e19350
    void FUN_00e19590(int id, void* obj);                           // 0x00e19590
    void FUN_00e19630();                                            // 0x00e19630
    void FUN_00e19780();                                            // 0x00e19780
    void FUN_00e19820();                                            // 0x00e19820
    void FUN_00e19830(int a, int b);                                // 0x00e19830
    bool FUN_00e19850(int mode);                                    // 0x00e19850
    void FUN_00e19c40(int a, int b);                                // 0x00e19c40
};
struct cMissionLog {
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
struct cSkinPaintClear {
    void* mpVtbl;        // +0x00
    int   mField4;       // +0x04
    int   mField8;       // +0x08
    void FUN_00e19230(int);                                         // 0x00e19230
};
void* FUN_00b3d4d0();                                   // 0x00b3d4d0 trigger mgr getter
void* SP_GameTimeManager();                             // 0x00b3d380
void* SP_WindowManager();                               // 0x0067caa0
void* SP_EffectsManager();                              // 0x0067ddd0
void* SP_CheatManager();                                // 0x0067de20
void* SP_MessageServer();                               // 0x0067dcc0
void* EA_Audio_GetSystemAT();                           // 0x00a206f0
int   SP_GetCurrentGameMode();                          // 0x00b5b800
void* GET_CivModeStrategy();                            // 0x00cf74c0
void* SP_TribeModeStrategy_Instance();                  // 0x00cd40b0
void* FUN_010666a0();                                   // 0x010666a0
void  SPUIHelpers_BeginModal(void* win, int a, int b);  // 0x008099a0 (cdecl)
void  SPUIHelpers_EndModal(void* win, int a, int b);    // 0x00809c50 (cdecl)
void  SP_cSPUISpace_KillSetiEffects(int hash, void* a);  // 0x00435ed0 (cdecl)
void  EA_Messaging_RemoveHandler(void* s, void* a, void* b, void* c, void* d); // 0x00571db0
void  eastl_RBTreeInsert(void* node, void* pos, void* header, int flag); // 0x009216a0
void* eastl_RBTreeIncrement(void* node);                // 0x00921580
void  FUN_00c58360(void* key);                          // 0x00c58360
void* FUN_00e1f390();   // ctor of badges layout (0xe1f390)
void* FUN_00e1b2d0();   // ctor (0xe1b2d0)
void* FUN_01064a30();   // ctor (0x1064a30)
void* FUN_0107ae70();   // ctor (0x107ae70)
void* FUN_01063360();   // ctor (0x1063360)
void* FUN_00e31050();   // cUIFlashWindowManager ctor (0xe31050)
// ---- items of slice s00e18d40 end

// ---- items of slice s00e1d020 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyString16[];                                // 0x01667bac
extern const uint32_t gaTradingWindowIds[3];        // 0x01480300
#define nullptr 0
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
class cSPUILayout_s00e1_d020 {
public:
    bool Init(const wchar_t* pszName, uint32_t nStyle, bool bVisible, uint32_t nFlags);  // 0x00812160 (cSPUILayout::Init)
    IWindow* FindWindowByID(uint32_t nWindowID, int32_t nRecursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
    void Shutdown(uint32_t nFlags);  // 0x00811ad0 (cSPUILayout::Shutdown)
    void Destroy();

private:
    uint8_t mPad00[0x18];       // no data members are read by this file
};
void __cdecl SPUIHelpers_BeginModal(IWindow* pWindow, void* pContext, bool bModal);
void __cdecl SPUIHelpers_EndModal(IWindow* pWindow, int32_t nA, int32_t nB);
class cGameTimeManager_s00e1_d020 {
public:
    void IncPauseGate(uint32_t nGate);  // 0x00b32220 (cGameTimeManager::IncPauseGate)
    void DecPauseGate(uint32_t nGate);
};
cGameTimeManager_s00e1_d020* __cdecl GameTimeManager();
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
void* __cdecl FUN_00e39ab0(uint32_t nType, int32_t nA, void* pB, void* pC,
                           int32_t nD, int32_t nE, void* pF, void* pG);    // 0x00e39ab0
class cTradeUI {
public:
    void Activate();                    // 0x00e1dae0
    void* Destroy(uint32_t nFlags);     // 0x00e1dc20

    void* mpVtbl0;              // +0x000  first base vtable
    void* mpTraceVtbl;          // +0x004  tracer base vtable
    cSPUILayout_s00e1_d020 mLayout;        // +0x008
    bool mbInitialized;         // +0x020
};
class cUITradingActivity {
public:
    void Deactivate(uint32_t nReason);                  // 0x00e1db60
    void SetMission(void* pMission, int32_t nReason);   // 0x00e1dc80

    cTradeUI* Owner() const { return (cTradeUI*)((uint8_t*)this - 4); }

    uint8_t mPad00[0x04];       // +0x000  (gTradeUI+0x04)
    cSPUILayout_s00e1_d020 mLayout;        // +0x004  (gTradeUI+0x008)
};
extern cTradeUI gTradeUI;                       // 0x015a51b4
void __cdecl FUN_00e1dbd0();        // 0x00e1dbd0
void* __cdecl FUN_005bf3a0(void* pSource, int32_t nFlags);          // 0x005bf3a0
void __cdecl FUN_00eebf90(void* pAsset, const wchar_t* pszText);    // 0x00eebf90
// ---- items of slice s00e1d020 end

// ---- items of slice s00e1df10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl operator_new_(unsigned size, const char* name, int, int, const char* file, int line); // 0x00f473a0
struct RefObj {
    virtual void dtor();                                   // +0x00
    virtual void AddRef();                                 // +0x04
    virtual void Release();                                // +0x08
};
struct IWindow_s00e1_df10 {
    virtual void v00();                                    // +0x00
    virtual void v01();                                    // +0x04
    virtual void v02();                                    // +0x08
    virtual IWindow_s00e1_df10* QueryInterface(uint32_t id);          // +0x0c
    virtual void v04();                                    // +0x10
    virtual void v05();                                    // +0x14
    virtual void v06();                                    // +0x18
    virtual uint32_t GetID();                              // +0x1c
};
struct IWindowFull {
virtual void v00();
virtual void v01();
virtual void v02();
    virtual IWindowFull* QueryInterface(uint32_t id);      // +0x0c
virtual void v04();
virtual void v05();
virtual void v06();
    virtual uint32_t GetID();                              // +0x1c
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
    virtual void v20();
    virtual void* GetValue();                              // +0x54
virtual void v22();
virtual void v23();
    virtual void SetValue(uint32_t v, int flag);           // +0x60
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
    virtual void SetChecked(int a, bool b);                // +0x7c
};
struct MsgServer {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
    virtual void Send(void* listener, uint32_t msg, int param); // +0x2c
};
MsgServer* __cdecl GetMessageServer();                    // 0x0067dcc0
struct Layout {
    IWindow_s00e1_df10* FindWindowByID(uint32_t id, bool recurse);   // 0x008105b0
    bool IsVisible();                                     // 0x00810070
};
struct FeedList {
    void Shutdown();                                      // 0x006628d0
    void SetVisible(bool v);                              // 0x00662920
    void SetThing(void* p);                               // 0x00663350
};
struct PaletteCat;
struct Palette {
    void Shutdown();                                      // 0x005c5c20
    PaletteCat* GetCategory(int i);                       // 0x005c5de0
    bool Init(const void* key, uint32_t type, int a, int b, int c, int d, int e); // 0x005c6340
};
struct PaletteCat {
    virtual void v00();
    virtual void AddRef();                                // +0x04
    virtual void Release();                               // +0x08
    uint32_t mPad[0x1b];                                  // +0x0c..+0x73
    uint32_t mE0;                                         // +0x74
};
void __cdecl EndModal(void* w, int a, int b);             // 0x00809c50
void __cdecl StringCtor(void* out, uint32_t id);          // 0x004010a0
void __cdecl StringCtor2(void* out, uint32_t id);         // 0x005ecf80
struct Str16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void RangeInitialize(const wchar_t* s);               // 0x00579a90
};
bool __cdecl CheckString(Str16* s);                       // 0x00e1de60
void* __cdecl NounManager();                              // 0x00b3d300
void* __cdecl GetPlayerTribe(void* nm);                   // 0x00bfc5f0
uint16_t __cdecl TribeNameId(void* tribe);                // 0x00c8e9f0
struct DlgBase {
    void teardown();                                      // 0x00e18810
    void reset();                                         // 0x00e18a30
};
struct SubObj {
    void init();                                          // 0x00e0a5c0
};
struct PaletteCtor {
    RefObj* ctor();                                       // 0x005c5e30
    RefObj* ctor2();                                      // 0x005c64e0
};
static inline void assignObj(RefObj*& dst, RefObj* src);
struct Pair {
    uint32_t mKey;                                        // +0x00
    uint8_t  mFlag;                                       // +0x04
    uint8_t  mPad[3];
    RefObj*  mpObj;                                       // +0x08
    void assignFrom(const Pair& src) {
        mKey = src.mKey;
        mFlag = src.mFlag;
        assignObj(mpObj, src.mpObj);
    }
};
static inline void assignObj(RefObj*& dst, RefObj* src)
{
    RefObj* old = dst;
    if (src != old) {
        if (src)
            src->AddRef();
        dst = src;
        if (old)
            old->Release();
    }
}
static inline void assignObjLazy(RefObj*& dst, RefObj* src)
{
    if (dst != src) {
        if (src)
            src->AddRef();
        RefObj* old = dst;
        dst = src;
        if (old)
            old->Release();
    }
}
struct SearchDlg {
    uint32_t mPad00[2];                                   // +0x00
    uint8_t  mLayout[0x08];                               // +0x08 embedded cSPUILayout
    uint32_t mId10;                                       // +0x10
    uint32_t mId14;                                       // +0x14
    void*    mpAvatar;                                    // +0x18
    uint32_t mPad1C[9];                                   // +0x1c
    Palette* mpPalette;                                   // +0x40
    void*    mpModel;                                     // +0x44
    FeedList* mpFeed;                                     // +0x48
    uint8_t  mSub4C[0x70];                                // +0x4c sub-object
    void*    mpMedia;                                     // +0xbc
    uint32_t mPadC0[5];                                   // +0xc0
    uint32_t mD4;                                         // +0xd4
    uint32_t mD8[2];                                      // +0xd8
    uint32_t mE0;                                         // +0xe0
    uint16_t mE4;                                         // +0xe4

    Layout* layout() { return (Layout*)mLayout; }

    uint32_t handle(uint32_t* msg, int arg2);             // 0x00e1df10
    uint32_t getD4(int unused);                           // 0x00e1e100
    void shutdown();                                      // 0x00e1e120
    void hideFeed();                                      // 0x00e1e1f0
    void setThing(void* p);                               // 0x00e1e210
    void setupPalette(void* key, uint32_t a, uint32_t b, uint32_t c, uint32_t d); // 0x00e1e500
};
// ---- items of slice s00e1df10 end

// ---- items of slice s00e1eab0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00b3d300();                       // 0x00b3d300 SP::NounManager()
extern "C" void* __cdecl FUN_00a206f0();                       // 0x00a206f0 EA::Audio::GetSystemAT
extern "C" void* __cdecl FUN_0067de30();                       // 0x0067de30 SP::PropertyManager
extern "C" void* __cdecl FUN_0067dcc0();                       // 0x0067dcc0 MessageServer
extern "C" bool  __fastcall FUN_00c8e850(void* tribe);          // 0x00c8e850 tribe herbivore test (ecx)
extern "C" void* __fastcall FUN_00bfc5f0(void* nouns);          // 0x00bfc5f0 cGameNounManager::GetPlayerTribe (ecx)
extern "C" void* __cdecl FUN_0041ea00(void* prop);              // 0x0041ea00 Property::GetUInt
extern "C" void  __fastcall FUN_00e186d0(void* self, int, int a, int b, int c, int d); // 0x00e186d0 OnNotify (ecx=this)
extern "C" void  __fastcall FUN_00e0a390(void* p);              // 0x00e0a390 Init
extern "C" void  __fastcall FUN_00e0a400(void* p);              // 0x00e0a400 Destroy
extern "C" void  __fastcall FUN_00e18bb0(void* p);              // 0x00e18bb0 Construct
extern "C" void  __fastcall FUN_00e18980(void* p);              // 0x00e18980 DestroyMembers
extern "C" void  __fastcall FUN_00e1e120(void* p);              // 0x00e1e120
extern "C" void  __fastcall FUN_00e1f280(void* p);              // 0x00e1f280
extern "C" void  __fastcall FUN_00e0a4c0(void* self, int, void* w);  // 0x00e0a4c0
extern "C" void  __cdecl FUN_00f47380(void* p);                 // 0x00f47380 operator delete
extern "C" void  __cdecl FUN_00973d10(void* out, void* iter);   // 0x00973d10 ListErase
extern "C" void  __fastcall FUN_005ed320(void* p, int, int a);  // 0x005ed320 palette item enable
extern "C" void* __fastcall FUN_005ed360(void* p, int, int a);  // 0x005ed360 cSPPaletteItemRollover ctor (ecx)
extern "C" void  __fastcall FUN_005ed6c0(void* p);              // 0x005ed6c0 Hide
extern "C" void* __fastcall FUN_00663040(void* p);              // 0x00663040 cSPUIFeedList ctor
extern "C" int   __fastcall FUN_00662a10(void* p);              // 0x00662a10 feed list category count
extern "C" void* __fastcall FUN_00662a20(void* p, int, int i);  // 0x00662a20 feed list category at i
extern "C" int   __fastcall FUN_00664600(void* p);              // 0x00664600 item count
extern "C" void* __fastcall FUN_00664610(void* p, int, int i);  // 0x00664610 item at i
extern "C" void  __fastcall FUN_006644e0(void* p, int, int a);  // 0x006644e0 select category
extern "C" void  __fastcall FUN_00eada10(void* list, int, void* a); // 0x00eada10 cList push
extern "C" int   __cdecl FUN_00432f10(int a);                   // 0x00432f10 RemapTypeId
extern "C" void* __fastcall FUN_00a16f40(void* x);              // 0x00a16f40 AsPPTypeParam (ecx)
extern "C" void  __fastcall FUN_008283a0(void* self, int, float a, float b, float c, float d); // 0x008283a0 SetPositionAndOffset
extern "C" void* __cdecl FUN_00e1e240(void* dst, void* src, void* end); // 0x00e1e240 uninitialized_move
extern "C" void* __cdecl FUN_00e1e290(void* dst, void* src, void* end); // 0x00e1e290 destroy range
extern "C" void* __cdecl FUN_00e1e390(void* begin, void* end, void* val); // 0x00e1e390 lower_bound
extern "C" void  __cdecl FUN_00e1e3f0(void* a, void* b, void* c);       // 0x00e1e3f0 move_backward
extern "C" void  __cdecl FUN_00e1e450(void* a, void* b);                // 0x00e1e450 iter_swap
extern "C" void  __cdecl FUN_00e1e6d0(void* a, void* b, void* c);       // 0x00e1e6d0 heap/insertion
extern "C" void  __cdecl FUN_00e1e7d0(void* a, void* b, void* c);       // 0x00e1e7d0 heap/insertion
extern "C" void  __cdecl FUN_00e1f330(void* a, void* b, void* c); // 0x00e1f330 insertion sort
extern "C" void  __cdecl FUN_00e1f5c0(void* a, void* b, void* c, void* d); // 0x00e1f5c0 partial sort
#pragma warning(disable : 4100)
typedef unsigned short u16;
typedef          int   s32;
class RefObj_s00e1_eab0
{
  public:
    virtual void v00();            // +0x00
    virtual void AddRef();         // +0x04
    virtual void Release();        // +0x08
};
struct ListRec { u32 key; u8 flag; u8 pad[3]; RefObj_s00e1_eab0* ref; };   // 0xc
extern "C" u32   __cdecl FUN_00bda3b0(int a, int b, int c, int d); // 0x00bda3b0
extern "C" u32   __cdecl FUN_00932e80(const char* s, int seed, int flag); // 0x00932e80 FNVHash
extern "C" void  __fastcall FUN_00e1e500(void* self, int, u32 k, u32 a, u32 b, u32 c, u32 d); // 0x00e1e500
extern "C" void* __cdecl FUN_00f473a0(u32 size, const char* file, int line, int a, const char* f2, int b); // 0x00f473a0 operator new
extern "C" void  __fastcall FUN_00663860(void* p, int, void* w, u32 a, u32 b, u32 c); // 0x00663860 configure feed list
extern "C" void  __fastcall FUN_00e30a60_s00e1_eab0(void* self, int, int a);   // 0x00e30a60
extern "C" void  __cdecl FUN_006a1250(void* obj, u32 key, void* out); // 0x006a1250 GetPropertyAsKey
extern "C" void  __cdecl FUN_006a12a0(void* obj, u32 key, void* out); // 0x006a12a0 GetPropertyAsKeyInstance
extern "C" void* __fastcall FUN_0059f030(void* self, int, u32 rk0, u32 rk1, u32 rk2, u32 key, u32 a, u32 b, u32 c); // 0x0059f030 ctor
extern "C" void  __fastcall FUN_005ee480(void* self, int, void* rec, void* holder, void* veh, u32 flag); // 0x005ee480 SetItem
extern "C" void  __cdecl FUN_00435ed0(u32 id, void* audio);     // 0x00435ed0 KillSetiEffects
extern "C" void* __cdecl FUN_00e1e8c0(void* a, int b, int c, int d, u32 key, u8 flag, RefObj_s00e1_eab0* ref, void* cmp); // 0x00e1e8c0 heap adjust
class PanelBase
{
  public:
    void* mVt0;                    // 0x00 vtable
    unsigned char pad004[0x08];
    void* mMsg0c;                  // 0x0c message target
    unsigned char pad010[0x04];
    u32   mKey14;                  // 0x14 player tribe type key
    void* mLayout18;               // 0x18 UI layout
    unsigned char pad01c[0x40 - 0x1c];
    RefObj_s00e1_eab0* mpRef40;               // 0x40
    RefObj_s00e1_eab0* mpRef44;               // 0x44
    RefObj_s00e1_eab0* mpRef48;               // 0x48
    unsigned char pad04c[0xbc - 0x4c];
    RefObj_s00e1_eab0* mpRefBC;               // 0xbc
    unsigned char pad0c0[0xd4 - 0xc0];
    ListRec* mListBegin;           // 0xc0
    ListRec* mListEnd;             // 0xc4  (see note: helpers use +0xc0/+0xc4 as raw list)
    unsigned char pad0c8[0xd4 - 0xc8];
    u32 mPropD4;                   // 0xd4
    u32 mPropD8;                   // 0xd8
    u32 mPropDC;                   // 0xdc
    u32 mPropE0;                   // 0xe0
    u16 mWordE4;                   // 0xe4
};
// ---- items of slice s00e1eab0 end

// @ 0x00e188b0
void *cUIMissionCardPanel::InitHints(void *param)
{
    void *raw = operator_new(0x18, 0x13f6b3c, 0, 0, 0, 0);
    void *obj = 0;
    if (raw != 0) {
        obj = ((void *(__thiscall *)(void *))FUN_00810000)(raw);
    }
    void *old = m_visObj;
    if (obj != old) {
        if (obj != 0) {
            ((void (__thiscall *)(void *))(*(void ***)obj)[1])(obj);
        }
        m_visObj = obj;
        if (old != 0) {
            ((void (__thiscall *)(void *))(*(void ***)old)[2])(old);
        }
    }
    u32 key[3];
    key[0] = (u32)(unsigned long)param;
    key[1] = 0x510a95b;
    key[2] = 0x40464100;
    void *layout = m_visObj;
    if (((bool (__thiscall *)(void *, u32 *, bool, u32))FUN_008120d0)(layout, key, true, 0x8b96f855)) {
        ((void (__thiscall *)(void *, int))FUN_00810590)(layout, 0);
        void *w = ((void *(__thiscall *)(void *, int, bool))FUN_008105b0)(m_visObj, -1, true);
        return ((void *(__thiscall *)(void *, void *))(*(void ***)w)[0x104 / 4])(w, this);
    }
    if (m_visObj != 0) {
        m_visObj = 0;
        return ((void *(__thiscall *)(void *))(*(void ***)layout)[2])(layout);
    }
    return 0;
}

// @ 0x00e18980
void cUIMissionCardPanel::DestroyMembers()
{
    m_vtbl00 = (void **)0x14800bc;
    *(void **)((u8 *)this + 8) = (void *)0x14800a0;
    m_layout = (void *)0x1480098;
    void *base = (u8 *)this + 0x34;
    void *node = *(void **)base;
    while (node != base) {
        void *p = node;
        node = *(void **)node;
        operator_delete_array(p);
    }
    if (m_treeBase40 != 0) {
        u32 h = (u32)m_treeBase40;
        m_treeBase40 = 0;
        FUN_00571db0(h, (u32)m_field3c, (u32)m_curMission, 0, 0);
    }
    if (m_field3c != 0) {
        ((void (__thiscall *)(void *))(*(void ***)m_field3c)[1])(m_field3c);
    }
    if (m_layout != 0) {
        ((void (__thiscall *)(void *))(*(void ***)m_layout)[2])(m_layout);
    }
    m_layout = (void *)0x13eb394;
    *(void **)((u8 *)this + 8) = (void *)0x13eb938;
    m_vtbl00 = (void **)0x13ec458;
}

// @ 0x00e18a30
void cUIMissionCardPanel::ShutdownA()
{
    void *mgr = FUN_00b3d3f0();
    FUN_00e30a60(*(void **)((u8 *)mgr + 0x5c), m_field10);
    void *mgr2 = FUN_00b3d3f0();
    FUN_00e30ae0(*(void **)((u8 *)mgr2 + 0x5c), 0xf45f7d78);
    void *node = m_treeBegin34;
    void *base = &m_treeBegin34;
    while (node != base) {
        void *p = node;
        node = *(void **)node;
        operator_delete_array(p);
    }
    *(void **)base = base;
    *(void **)((u8 *)base + 4) = base;
    if (m_layout != 0) {
        ((void (__thiscall *)(void *, int))FUN_00810590)(m_layout, 0);
    }
}

// @ 0x00e18a90
void cUIMissionCardPanel::ClearTree()
{
    void *node = m_treeBegin34;
    void *base = &m_treeBegin34;
    while (node != base) {
        void *p = node;
        node = *(void **)node;
        operator_delete_array(p);
    }
    *(void **)base = base;
    *(void **)((u8 *)base + 4) = base;
}

// @ 0x00e18b10
void *cUIMissionCardPanel::FindMission(u32 id)
{
    void *result = 0;
    void *out;
    void *base = (u8 *)this + 0x40;
    ((void (__thiscall *)(void *, void **, u32 *))FUN_00e5c780)(
        (u8 *)this + 0x3c, &out, &id);
    if (base != out) {
        result = *(void **)((u8 *)out + 0x14);
    }
    return result;
}

// @ 0x00e18b50
void cUIMissionCardPanel::ShutdownB()
{
    if (m_field5c != 0) {
        FUN_00e30a60(m_field5c, 0x6244208);
    }
    void *node = m_tree74;
    void *base = (u8 *)this + 0x74;
    while (node != base) {
        void *p = node;
        node = *(void **)node;
        operator_delete_array(p);
    }
    *(void **)base = base;
    *(void **)((u8 *)base + 4) = base;
    void *n2 = m_treeBase40;
    void *b2 = (u8 *)this + 0x40;
    while (n2 != b2) {
        void *obj = *(void **)((u8 *)n2 + 0x14);
        ((void (__thiscall *)(void *))(*(void ***)obj)[0x2c / 4])(obj);
        n2 = FUN_00921580(n2);
    }
}

// @ 0x00e18bb0
void *cUIMissionCardPanel::Construct()
{
    m_sub04 = 0;
    m_slotVtbl08 = (void *)0x14426a0;
    m_slotVtbl0c = (void *)0x13eb394;
    m_vtbl00 = (void **)0x14800bc;
    m_slotVtbl08 = (void *)0x14800a0;
    m_slotVtbl0c = (void *)0x1480098;
    m_field10 = 0xffffffff;
    m_field14 = 0;
    m_layout = 0;
    m_card = 0;
    m_treeBegin34 = (u8 *)this + 0x34;
    m_curMission = (u8 *)this + 0x34;
    u32 hash = 0x65ff54a;
    void *ms = MessageServer();
    m_handlerObj = ms;
    m_handlerArg1 = (void *)((u8 *)this + 0xc);
    m_handlerArg2 = &hash;
    m_handlerN = 1;
    m_handlerArg4 = 0;
    if (ms != 0 && m_handlerArg1 != 0) {
        ((void (__thiscall *)(void *, void *, void *))(*(void ***)ms)[0x24 / 4])(ms, m_handlerArg1, &hash);
    }
    return this;
}

// @ 0x00e18c70
bool cUIMissionCardPanel::ShouldShow(u32 id)
{
    if (m_visObj == 0
        || !((bool (__thiscall *)(void *))FUN_00810070)(m_visObj)) {
        return false;
    }
    if (id == 0) {
        return true;
    }
    if (FindMission(id) == m_curMission) {
        return true;
    }
    return false;
}

// @ 0x00e18cb0
void cUIMissionCardPanel::SetSlotAndMission(u32 slot)
{
    void *out;
    ((void (__thiscall *)(void *, void **, u32 *))FUN_00e5c780)(
        (u8 *)this + 0x3c, &out, &slot);
    void *base = (u8 *)this + 0x40;
    if (out == base) {
        return;
    }
    void *m = *(void **)((u8 *)out + 0x14);
    if (m == 0) {
        return;
    }
    if (m_visObj != 0) {
        void *w = ((void *(__thiscall *)(void *, int, bool))FUN_008105b0)(m_visObj, (int)slot, true);
        if (w != 0) {
            void *sub = ((void *(__thiscall *)(void *, u32))(*(void ***)w)[0x0c / 4])(w, 0x8ed27e7a);
            if (sub != 0) {
                ((void (__thiscall *)(void *, int, int))(*(void ***)sub)[0x28 / 4])(sub, 4, 1);
            }
        }
    }
    m_treeBegin34 = (void *)slot;
    void *old = m_curMission;
    if (m != old) {
        if (m != 0) {
            ((void (__thiscall *)(void *))(*(void ***)m)[1])(m);
        }
        m_curMission = m;
        if (old != 0) {
            ((void (__thiscall *)(void *))(*(void ***)old)[2])(old);
        }
    }
}

// @ 0x00e18d40
void cFeedbackTree::FUN_00e18d40(void** out, void* pos, int* value, char flag)
{
    int b = 0;
    if (flag == 0 && pos != &mAnchor && (unsigned)*value >= *(unsigned*)((char*)pos + 0x10))
        b = 1;
    char* node = (char*)operator new(0x18, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    char* v = node + 0x10;
    if (v) {
        *(int*)v = value[0];
        int* rc = (int*)value[1];
        *(int**)(v + 4) = rc;
        if (rc)
            (*(void(__thiscall**)(int*))((char*)(*(int**)rc) + 4))(rc);
    }
    eastl_RBTreeInsert(node, pos, &mAnchor, b);
    ++mSize2;
    *out = node;
}

// @ 0x00e18dd0
void cPanel::FUN_00e18dd0(void* p, int)
{
    int state = *(int*)((char*)FUN_00b3d4d0() + 0x2c);
    if (state == 1 || state == 2) return;

    void* wm = SP_WindowManager();
    int r = (*(int(__thiscall**)(void*))((char*)Vt(wm) + 0x84))(wm);
    if (r != 0) {
        void* wm2 = SP_WindowManager();
        void* a = mLayout->FindWindowByID(-1, 1);
        int r2 = (*(int(__thiscall**)(void*))((char*)Vt(wm2) + 0x84))(wm2);
        if (a != (void*)r2) return;
    }
    if (mLayout && mLayout->IsVisible() && p) {
        if (mScrollRoot) (*(void(__thiscall**)(void*))((char*)Vt(mScrollRoot) + 0x20))(mScrollRoot);
        FUN_00e190c0(p);
        if (mScrollRoot) {
            (*(void(__thiscall**)(void*, void*))((char*)Vt(mScrollRoot) + 0x1c))(mScrollRoot, p);
        }
        return;
    }
    if (!mLayout) return;
    if (mWinMgr) {
        if (!((cWinMgr*)mWinMgr)->FUN_00e2f3c0(0x6244208))
            FUN_00e18b50();
    }
    mLayout->SetVisibility(1);
    void* at = EA_Audio_GetSystemAT();
    void* a = at ? (void*)(*(int(__thiscall**)(void*))((char*)Vt(at) + 0x20))(at) : 0;
    SP_cSPUISpace_KillSetiEffects(0xea8555f2, a);
    if (p) FUN_00e190c0(p);
    if (mScrollRoot) {
        (*(void(__thiscall**)(void*, void*))((char*)Vt(mScrollRoot) + 0x1c))(mScrollRoot, p);
    }
    {
        void* node = *(void**)((char*)this + 0x44);
        char* end = (char*)this + 0x40;
        while (node != end) {
            int* ev = *(int**)((char*)node + 0x14);
            void* win = mLayout->FindWindowByID(*(int*)((char*)node + 0x10), 1);
            if (win) {
                unsigned char c = (*(unsigned char(__thiscall**)(int*))((char*)(*(int**)ev) + 0x24))(ev);
                (*(void(__thiscall**)(void*, int, unsigned char))((char*)Vt(win) + 0x7c))(win, 2, c);
            }
            node = eastl_RBTreeIncrement(node);
        }
    }
    {
        void* em = SP_EffectsManager();
        void* slot = (char*)this + 0x58;
        void* old = *(void**)slot;
        if (old) {
            *(void**)slot = 0;
            (*(void(__thiscall**)(void*))((char*)Vt(old) + 4))(old);
        }
        char ok = (*(char(__thiscall**)(void*, int, int, void*))((char*)Vt(em) + 0x2c))(em, 0x4c4ba0a9, 0, slot);
        if (ok) {
            void* cur = *(void**)slot;
            (*(void(__thiscall**)(void*, int))((char*)Vt(cur) + 8))(cur, 0);
        }
    }
    if (mMode != (int)0x1654c05) {
        void* win = mLayout->FindWindowByID(-1, 1);
        SPUIHelpers_BeginModal(win, 0, 1);
    }
    {
        void* wm = SP_WindowManager();
        void* win = mLayout->FindWindowByID(-1, 1);
        (*(void(__thiscall**)(void*, int, void*))((char*)Vt(wm) + 0x4c))(wm, 0, win);
    }
    cGameTimeManager* gt = (cGameTimeManager*)SP_GameTimeManager();
    gt->IncPauseGate((void*)0x4bf38a4);
    for (void* n = *(void**)((char*)this + 0x74); n != (void*)((char*)this + 0x74); n = *(void**)n) {
        ((cWinMgr*)mWinMgr)->FUN_00e30e20(*(int*)((char*)n + 8), 0x6244208, (int)0xce0a0762, 1, 0x68b5a48);
    }
}

// @ 0x00e19010
void cPanel::FUN_00e19010()
{
    if (!mLayout || !mLayout->IsVisible()) return;
    FUN_00e18b50();
    SPUIHelpers_EndModal(mLayout->FindWindowByID(-1, 1), 0, 0);
    if (mBlurEffect) {
        (*(void(__thiscall**)(void*, int))((char*)Vt(mBlurEffect) + 0xc))(mBlurEffect, 1);
        if (mBlurEffect) {
            void* old = mBlurEffect;
            mBlurEffect = 0;
            (*(void(__thiscall**)(void*))((char*)Vt(old) + 4))(old);
        }
    }
    void* at = EA_Audio_GetSystemAT();
    void* a = at ? (void*)(*(int(__thiscall**)(void*))((char*)Vt(at) + 0x20))(at) : 0;
    SP_cSPUISpace_KillSetiEffects(0x5dc7f7a6, a);
    mLayout->SetVisibility(0);
    if (mScrollRoot) (*(void(__thiscall**)(void*))((char*)Vt(mScrollRoot) + 0x20))(mScrollRoot);
    cGameTimeManager* gt = (cGameTimeManager*)SP_GameTimeManager();
    gt->DecPauseGate((void*)0x4bf38a4);
}

// @ 0x00e190c0
void cPanel::FUN_00e190c0(void* p)
{
    if (mLayout && mLayout->IsVisible() && (p == 0 || FUN_00e18b10(p) == mScrollRoot)) {
        FUN_00e19010();
        return;
    }
    if (SP_GetCurrentGameMode() == (int)0x1654c04) {
        if (*(char*)((char*)GET_CivModeStrategy() + 0x148)) return;
    }
    if (SP_GetCurrentGameMode() == (int)0x1654c02) {
        cTribeStrategy* t = (cTribeStrategy*)SP_TribeModeStrategy_Instance();
        if (t->FUN_00cd44a0()) return;
    }
    if (SP_GetCurrentGameMode() == (int)0x1654c05) {
        if (((cSporepediaObj*)FUN_010666a0())->FUN_01065e20()) return;
    }
    FUN_00e18dd0(p, 0);
}

// @ 0x00e19230
void cSkinPaintClear::FUN_00e19230(int)
{
    cPanel* p = (cPanel*)FUN_00b3d3f0();
    p->FUN_00e190c0(0);
}

// @ 0x00e19250
void cMissionLog::FUN_00e19250(int value)
{
    char* sentinel = (char*)this + 0x34;
    char* node = (char*)operator new(0xc, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    int* v = (int*)(node + 8);
    if (v) *v = value;
    *(void**)node = sentinel;
    *(void**)(node + 4) = *(void**)(sentinel + 4);
    **(void***)(sentinel + 4) = node;
    *(void**)(sentinel + 4) = node;
}

// @ 0x00e192a0
bool cPanel::FUN_00e192a0(int, void* msg)
{
    int* m = (int*)msg;
    char bl = 0;
    int tag = m[2];
    if (tag == 1) {
        if (m[5] == 0 && (m[4] == 0x1b || m[4] == 0x4c)) {
            FUN_00e19010();
            return true;
        }
    } else if (tag == (int)0x287259f6) {
        int v = (*(int(__thiscall**)(int))((char*)Vt((void*)m[0]) + 0x1c))(m[0]);
        if (v == -0x10) {
            FUN_00e19010();
            return true;
        }
        if (FUN_00e18b10((void*)v) == 0)
            return false;
        void* at = EA_Audio_GetSystemAT();
        if (at)
            (*(void(__thiscall**)(void*))((char*)Vt(at) + 0x20))(at);
        SP_cSPUISpace_KillSetiEffects(0xc1f95c5a, at);
        FUN_00e18dd0((void*)v, 0);
        return true;
    }
    return bl != 0;
}

// @ 0x00e19350
void cPanel::FUN_00e19350(unsigned key, int arg)
{
    unsigned k = key;
    unsigned local4;
    local4 = 0;
    void* it = 0;
    unsigned* out = &local4;
    mTree.FUN_00e5c780(out, &k);
    it = (void*)local4;
    char* end = (char*)this + 0x40;
    if (it == end) return;

    if (mWinMgr) {
        if (!((cWinMgr*)mWinMgr)->FUN_00e2f3c0(0x6244208))
            FUN_00e18b50();
        ((cWinMgr*)mWinMgr)->FUN_00e31030(0x6244208, 0x77e5a05, 0, 0);
    }
    void* ev = *(void**)((char*)it + 0x14);
    (*(void(__thiscall**)(void*, int))((char*)Vt(ev) + 0x28))(ev, arg);
    {
        void* n = *(void**)((char*)this + 0x74);
        char* sent = (char*)this + 0x74;
        while (n != sent && *(unsigned*)((char*)n + 8) != key)
            n = *(void**)n;
        if (n != sent) return;
    }
    unsigned kk = key;
    FUN_00c58360(&kk);
}

// @ 0x00e193f0
cPanel::~cPanel()
{
    *(void**)this = vtbl_1480160;
    *(void**)((char*)this + 4) = vtbl_1480110;
    *(void**)((char*)this + 8) = vtbl_148010c;
    *(void**)((char*)this + 0x20) = vtbl_1480104;
    *(void**)((char*)this + 0x24) = vtbl_14800f4;

    void* node = mListNext;
    void* sent = (char*)this + 0x74;
    while (node != sent) {
        void* nxt = *(void**)node;
        operator_delete__(node);
        node = nxt;
    }
    if (mMsgServer) {
        mMsgServer = 0;
        EA_Messaging_RemoveHandler(mMsgServer, mHandlerPtr, mHandlerId, (void*)mHandlerA, (void*)mHandlerB);
    }
    if (mWinMgr)  (*(void(__thiscall**)(void*))((char*)Vt(mWinMgr) + 8))(mWinMgr);
    if (mBlurEffect) (*(void(__thiscall**)(void*))((char*)Vt(mBlurEffect) + 4))(mBlurEffect);
    mTree.FUN_00e19160(*(void**)((char*)this + 0x48));
    if (mScrollRoot) (*(void(__thiscall**)(void*))((char*)Vt(mScrollRoot) + 8))(mScrollRoot);
    if (mLayout)     (*(void(__thiscall**)(void*))((char*)Vt(mLayout) + 8))(mLayout);
    *(void**)((char*)this + 0x24) = vtbl_14426a0;
    *(void**)((char*)this + 0x20) = vtbl_1480160;
    SP::cGonzagoSubsystem_s00e1_8d40* g = (SP::cGonzagoSubsystem_s00e1_8d40*)((char*)this + 4);
    g->~cGonzagoSubsystem_s00e1_8d40();
    *(void**)this = vtbl_14426a0;
}

// @ 0x00e19590
void cPanel::FUN_00e19590(int id, void* obj)
{
    if (obj) (*(void(__thiscall**)(void*))((char*)Vt(obj) + 4))(obj);
    int local10 = id;
    void* localc = obj;
    if (obj) (*(void(__thiscall**)(void*))((char*)Vt(obj) + 4))(obj);
    unsigned flag = (unsigned)obj & 0xffffff00u;
    mTree.FUN_00e191a0(&local10, &localc, &flag);
    if (obj) {
        (*(void(__thiscall**)(void*))((char*)Vt(obj) + 8))(obj);
        (*(void(__thiscall**)(void*))((char*)Vt(obj) + 8))(obj);
    }
    cSPUILayout_s00e1_8d40* layout = mLayout;
    void* w1 = layout->FindWindowByID(-0xa, 1);
    void* w2 = layout->FindWindowByID(-4, 1);
    int mode = mMode;
    (*(void(__thiscall**)(void*, int, unsigned, void*, void*))((char*)Vt(obj) + 0x10))(obj, mode, flag, w2, w1);
}

// @ 0x00e19630
void cPanel::FUN_00e19630()
{
    char* self = (char*)this;
    void* it = *(void**)(self + 0x44);
    char* end = self + 0x40;
    while (it != end) {
        void* ev = *(void**)((char*)it + 0x14);
        (*(void(__thiscall**)(void*))((char*)Vt(ev) + 0x14))(ev);
        it = eastl_RBTreeIncrement(it);
    }
    mTree.FUN_00e19160(*(void**)(self + 0x48));
    void* a = self + 0x40;
    *(void**)(self + 0x44) = a;
    *(void**)a = a;
    *(int*)(self + 0x48) = 0;
    *(char*)(self + 0x4c) = 0;
    *(int*)(self + 0x50) = 0;
}

// @ 0x00e19680
cPanel::cPanel()
{
    *(void**)this = vtbl_14426a0;
    SP::cGonzagoSubsystem_s00e1_8d40* g = (SP::cGonzagoSubsystem_s00e1_8d40*)((char*)this + 4);
    new (g) SP::cGonzagoSubsystem_s00e1_8d40();
    *(void**)((char*)this + 0x20) = vtbl_1480104;
    *(void**)((char*)this + 0x24) = vtbl_14800f4;
    *(void**)this = vtbl_1480160;
    *(void**)((char*)this + 4) = vtbl_1480110;
    *(void**)((char*)this + 8) = vtbl_148010c;
    *(void**)((char*)this + 0x20) = vtbl_1480104;
    *(void**)((char*)this + 0x24) = vtbl_14800f4;
    mMode = -1;
    mHolder = 0;
    mScrollRoot = 0;
    mTree.m00 = 0;
    mTree.mAnchor = (char*)this + 0x40;
    mTree.mRoot = (char*)this + 0x40;
    mTree.mSize = 0;
    mTree.mFlag = 0;
    mTree.mSize2 = 0;
    *(void**)((char*)this + 0x54) = 0;
    mBlurEffect = 0;
    mWinMgr = 0;
    mMsgServer = 0;
    mHandlerPtr = 0;
    mHandlerId = 0;
    mHandlerA = 0;
    mHandlerB = 0;
    void* list = (char*)this + 0x74;
    *(void**)list = list;
    *(void**)((char*)list + 4) = list;
    int tag = 0x65ff54a;
    void* srv = SP_MessageServer();
    mMsgServer = srv;
    mHandlerPtr = (char*)this + 0x20;
    mHandlerId = &tag;
    mHandlerA = 1;
    mHandlerB = 0;
    if (srv && mHandlerPtr)
        (*(void(__thiscall**)(void*, void*, int))((char*)Vt(srv) + 0x24))(srv, mHandlerPtr, tag);
}

// @ 0x00e19780
void cPanel::FUN_00e19780()
{
    void* cm = SP_CheatManager();
    if (cm)
        (*(void(__thiscall**)(void*, const char*))((char*)Vt(cm) + 0x1c))(cm, "missionlog");
    if (mWinMgr) {
        ((cWinMgr*)mWinMgr)->FUN_00e30dc0();
        if (mWinMgr) {
            void* old = mWinMgr;
            mWinMgr = 0;
            (*(void(__thiscall**)(void*))((char*)Vt(old) + 8))(old);
        }
    }
    if (mBlurEffect) {
        (*(void(__thiscall**)(void*, int))((char*)Vt(mBlurEffect) + 0xc))(mBlurEffect, 1);
        if (mBlurEffect) {
            void* old = mBlurEffect;
            mBlurEffect = 0;
            (*(void(__thiscall**)(void*))((char*)Vt(old) + 4))(old);
        }
    }
    if (mScrollRoot) {
        void* old = mScrollRoot;
        mScrollRoot = 0;
        (*(void(__thiscall**)(void*))((char*)Vt(old) + 8))(old);
    }
    FUN_00e19630();
    if (mLayout) {
        mLayout->Shutdown(1);
        if (mLayout) {
            void* old = mLayout;
            mLayout = 0;
            (*(void(__thiscall**)(void*))((char*)Vt(old) + 8))(old);
        }
    }
}

// @ 0x00e19820
void cPanel::FUN_00e19820()
{
    ((cPanel*)((char*)this - 4))->FUN_00e19780();
}

// @ 0x00e19830
void cPanel::FUN_00e19830(int a, int b)
{
    SP::cGonzagoSubsystem_s00e1_8d40* g = (SP::cGonzagoSubsystem_s00e1_8d40*)this;
    g->PreGameModeTransition(a, b);
    ((cPanel*)((char*)this - 4))->FUN_00e19780();
}

// @ 0x00e19850
bool cPanel::FUN_00e19850(int mode)
{
    FUN_00e19780();
    mMode = mode;
    int id;
    switch (mode) {
    case (int)0x1654c00:
        FUN_00e188b0(0x375e8335);
        {
            void* o = operator new(0xe8, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o = o ? FUN_00e1f390() : 0;
            FUN_00e19590(-0xf, o);
        }
        id = -0xf;
        break;
    case (int)0x1654c01:
        FUN_00e188b0(0x2a843c80);
        {
            void* o = operator new(0xe8, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o = o ? FUN_00e1f390() : 0;
            FUN_00e19590(-0xf, o);
            void* o2 = operator new(0x98, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o2 = o2 ? FUN_00e1b2d0() : 0;
            FUN_00e19590(-0xe, o2);
        }
        id = -0xe;
        break;
    case (int)0x1654c02:
        FUN_00e188b0(0x71b4193f);
        {
            void* o = operator new(0xe8, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o = o ? FUN_00e1f390() : 0;
            FUN_00e19590(-0xf, o);
            void* o2 = operator new(0xe8, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o2 = o2 ? FUN_00e1f390() : 0;
            FUN_00e19590(0x6722bd6, o2);
            void* o3 = operator new(0x98, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o3 = o3 ? FUN_00e1b2d0() : 0;
            FUN_00e19590(-0xe, o3);
        }
        id = -0xe;
        break;
    case (int)0x1654c04:
        FUN_00e188b0(0x5f7781f5);
        {
            void* o = operator new(0x98, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o = o ? FUN_00e1b2d0() : 0;
            FUN_00e19590(-0xe, o);
        }
        id = -0xe;
        break;
    case (int)0x1654c05:
        FUN_00e188b0(0xd9b09d9d);
        {
            void* o = operator new(0x98, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o = o ? FUN_00e1b2d0() : 0;
            FUN_00e19590(-0xe, o);
            void* o2 = operator new(0xd8, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o2 = o2 ? FUN_01064a30() : 0;
            FUN_00e19590(-0xd, o2);
            void* o3 = operator new(0x150, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o3 = o3 ? FUN_0107ae70() : 0;
            FUN_00e19590(-0xb, o3);
            void* o4 = operator new(0x1b0, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o4 = o4 ? FUN_01063360() : 0;
            FUN_00e19590(-0xc, o4);
        }
        id = -0xe;
        break;
    default:
        return false;
    }
    FUN_00e18cb0(id);
    if (SP_CheatManager()) {
        void* cmd = operator new(0x10, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        if (cmd) {
            (*(void(__thiscall**)(void*))0x0083c800)(cmd);
            *(void**)cmd = vtbl_1480080;
        }
    }
    {
        void* wm = operator new(0x58, "UI/cUIFlashWindowManager", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        wm = wm ? FUN_00e31050() : 0;
        void* old = mWinMgr;
        if (wm != old) {
            if (wm) (*(void(__thiscall**)(void*))((char*)Vt(wm) + 4))(wm);
            mWinMgr = wm;
            if (old) (*(void(__thiscall**)(void*))((char*)Vt(old) + 8))(old);
        }
    }
    ((cWinMgr*)mWinMgr)->FUN_00e2f370();
    return true;
}

// @ 0x00e19c40
void cPanel::FUN_00e19c40(int a, int b)
{
    SP::cGonzagoSubsystem_s00e1_8d40* g = (SP::cGonzagoSubsystem_s00e1_8d40*)this;
    g->PostGameModeTransition(a, b);
    ((cPanel*)((char*)this - 4))->FUN_00e19850(b);
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
    cGameTimeManager_s00e1_d020* pTime = GameTimeManager();
    pTime->IncPauseGate(0x4bf38a7);

    // the window-id block is walked as three raw dwords
    cSPUILayout_s00e1_d020* pLayout = &mLayout;
    for (uint32_t nOffset = 0; nOffset < 3 * sizeof(uint32_t); nOffset += sizeof(uint32_t)) {
        IWindow* pWindow = pLayout->FindWindowByID(
            *(const uint32_t*)((size_t)(const void*)gaTradingWindowIds + nOffset), 1);
        if (pWindow != nullptr)
            pWindow->SetOwner(Owner());
    }
}

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

// @ 0x00e1df10
uint32_t SearchDlg::handle(uint32_t* msg, int arg2)
{
    IWindow_s00e1_df10* w = layout()->FindWindowByID(0x7d4c266, 1);
    uint32_t kind = msg[2];
    if (kind == 0x287259f6) {
        uint32_t sub = (*(uint32_t(__thiscall**)(void))**(void***)msg)();
        if (sub == 0x7d4de46) {
            EndModal(w, 1, 1);
            return 0;
        }
        if (sub != 0x5a725b4)
            return 0;
        Str16 range;
        range.mpBegin = 0;
        range.mpEnd = 0;
        range.mpCapacity = 0;
        StringCtor(&range, 0x51aa76bb);
        StringCtor2(&range, 0x51aa76bb);
        IWindow_s00e1_df10* listW = layout()->FindWindowByID(0x7d4c4be, 1);
        if (listW) {
            IWindowFull* list = (IWindowFull*)listW->QueryInterface(0xcf428691);
            if (list) {
                list->SetValue((uint32_t)(uintptr_t)range.mpBegin, 0);
                IWindowFull* check = (IWindowFull*)layout()->FindWindowByID(0x7d4de46, 1);
                if (check)
                    check->SetChecked(2, range.mpBegin != range.mpEnd);
            }
        }
        if ((int)(((char*)range.mpCapacity - (char*)range.mpBegin) & 0xfffffffe) > 2 && range.mpBegin)
            operator_delete__(range.mpBegin);
        return 0;
    }
    if (kind != 0x9b1552d8)
        return 0;
    uint32_t sub = (*(uint32_t(__thiscall**)(void))**(void***)msg)();
    if (sub != 0x7d4c4be)
        return 0;
    IWindow_s00e1_df10* listW = layout()->FindWindowByID(0x7d4c4be, 1);
    IWindowFull* list = listW ? (IWindowFull*)listW->QueryInterface(0xcf428691) : 0;
    wchar_t* text = (wchar_t*)list->GetValue();
    Str16 s;
    s.mpBegin = 0;
    s.mpEnd = 0;
    s.mpCapacity = 0;
    s.RangeInitialize(text);
    bool ok = CheckString(&s);
    wchar_t* lo = s.mpBegin;
    if (ok)
        list->SetValue((uint32_t)(uintptr_t)lo, 0);
    IWindowFull* check = (IWindowFull*)layout()->FindWindowByID(0x7d4de46, 1);
    if (check)
        check->SetChecked(2, lo != s.mpEnd);
    if ((int)(((char*)s.mpCapacity - (char*)lo) & 0xfffffffe) > 2 && lo)
        operator_delete__(lo);
    return 0;
}

// @ 0x00e1e100
uint32_t SearchDlg::getD4(int)
{
    return mD4;
}

// @ 0x00e1e120
void SearchDlg::shutdown()
{
    GetMessageServer()->Send(this ? (void*)((char*)this + 0xc) : 0, 0x5bf34455, 0xffffd8f1);
    GetMessageServer()->Send(this ? (void*)((char*)this + 0xc) : 0, 0x1e8c9e0, 0xffffd8f1);
    ((SubObj*)mSub4C)->init();
    if (mpMedia) {
        (*(void (__thiscall**)(void*))((*(void***)mpMedia)[9]))(mpMedia);   // +0x24
        void* m = mpMedia;
        if (m) {
            mpMedia = 0;
            (*(void (__thiscall**)(void*))((*(void***)m)[1]))(m);           // +0x04
        }
    }
    if (mpFeed) {
        mpFeed->Shutdown();
        FeedList* f = mpFeed;
        if (f) {
            mpFeed = 0;
            (*(void (__thiscall**)(void*))((*(void***)f)[1]))(f);
        }
    }
    if (mpPalette) {
        mpPalette->Shutdown();
        Palette* p = mpPalette;
        if (p) {
            mpPalette = 0;
            (*(void (__thiscall**)(void*))((*(void***)p)[2]))(p);           // +0x08
        }
    }
    ((DlgBase*)this)->teardown();
}

// @ 0x00e1e1f0
void SearchDlg::hideFeed()
{
    if (mpFeed)
        mpFeed->SetVisible(0);
    ((DlgBase*)this)->reset();
}

// @ 0x00e1e210
void SearchDlg::setThing(void* p)
{
    if (mpFeed) {
        Layout* l = (Layout*)mpAvatar;
        if (l->IsVisible())
            mpFeed->SetThing(p);
    }
}

// @ 0x00e1e240
Pair* __cdecl pairCopyConstruct(Pair* first, Pair* last, Pair* out) // 0x00e1e240
{
    while (first != last) {
        if (out) {
            out->mKey = first->mKey;
            out->mFlag = first->mFlag;
            RefObj* o = first->mpObj;
            out->mpObj = o;
            if (o)
                o->AddRef();
        }
        ++first;
        ++out;
    }
    return out;
}

// @ 0x00e1e2d0
void __cdecl pairSiftUp(Pair* base, int top, int hole, uint32_t key, uint8_t flag, RefObj* obj) // 0x00e1e2d0
{
    int parent = (hole - 1) >> 1;
    while (hole > top && base[parent].mKey < key) {
        base[hole].mKey = base[parent].mKey;
        base[hole].mFlag = base[parent].mFlag;
        assignObjLazy(base[hole].mpObj, base[parent].mpObj);
        hole = parent;
        parent = (parent - 1) >> 1;
    }
    base[hole].mKey = key;
    base[hole].mFlag = flag;
    assignObjLazy(base[hole].mpObj, obj);
    if (obj)
        obj->Release();
}

// @ 0x00e1e390
Pair* __cdecl pairAssign(Pair* first, Pair* last, Pair* out) // 0x00e1e390
{
    while (first != last) {
        out->assignFrom(*first);
        ++first;
        ++out;
    }
    return out;
}

// @ 0x00e1e3f0
Pair* __cdecl pairAssignBackward(Pair* first, Pair* last, Pair* out) // 0x00e1e3f0
{
    while (last != first) {
        --last;
        --out;
        out->assignFrom(*last);
    }
    return out;
}

// @ 0x00e1e450
void __cdecl pairSwap(Pair* a, Pair* b) // 0x00e1e450
{
    Pair tmp;
    tmp.mKey = a->mKey;
    tmp.mFlag = a->mFlag;
    tmp.mpObj = a->mpObj;
    if (tmp.mpObj)
        tmp.mpObj->AddRef();

    RefObj* oldA = a->mpObj;
    RefObj* newA = b->mpObj;
    a->mKey = b->mKey;
    a->mFlag = b->mFlag;
    if (newA != oldA) {
        if (newA)
            newA->AddRef();
        a->mpObj = newA;
        if (oldA)
            oldA->Release();
    }

    RefObj* oldB = b->mpObj;
    b->mKey = tmp.mKey;
    b->mFlag = tmp.mFlag;
    if (tmp.mpObj != oldB) {
        if (tmp.mpObj)
            tmp.mpObj->AddRef();
        b->mpObj = tmp.mpObj;
        if (oldB)
            oldB->Release();
    }

    if (tmp.mpObj)
        tmp.mpObj->Release();
}

// @ 0x00e1e500
void SearchDlg::setupPalette(void* key, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    if (!key)
        return;

    RefObj* pal = 0;
    void* mem = operator_new_(0x40, (const char*)0x013f6b3c, 0, 0, 0, 0);
    if (mem)
        pal = ((PaletteCtor*)mem)->ctor();
    if (pal != (RefObj*)mpPalette) {
        if (pal)
            pal->AddRef();
        Palette* old = mpPalette;
        mpPalette = (Palette*)pal;
        if (old)
            (*(void (__thiscall**)(void*))((*(void***)old)[2]))(old);
    }
    if (!mpPalette->Init(key, c, 0, 0, 0, 0, 0)) {
        Palette* p = mpPalette;
        if (p) {
            mpPalette = 0;
            (*(void (__thiscall**)(void*))((*(void***)p)[2]))(p);
        }
        return;
    }

    PaletteCat* cat = mpPalette->GetCategory(0);
    if (cat) {
        cat->AddRef();
        mE0 = cat->mE0;
    }

    RefObj* model = 0;
    void* mem2 = operator_new_(0x34, (const char*)0x013f6b3c, 0, 0, 0, 0);
    if (mem2)
        model = ((PaletteCtor*)mem2)->ctor2();
    if (model != (RefObj*)mpModel) {
        if (model)
            model->AddRef();
        void* old = mpModel;
        mpModel = model;
        if (old)
            (*(void (__thiscall**)(void*))((*(void***)old)[2]))(old);
    }

    if (mId10 == 0x1654c02 && mId14 == 0x6722bd6) {
        void* nm = NounManager();
        void* tribe = GetPlayerTribe(nm);
        if (tribe) {
            void* m = mpModel;
            void* nm2 = NounManager();
            void* tribe2 = GetPlayerTribe(nm2);
            *(uint16_t*)((char*)m + 0x18) = TribeNameId(tribe2);
            goto tail;
        }
    }
    *(uint16_t*)((char*)mpModel + 0x18) = mE4;

tail:
    {
        uint8_t* m = (uint8_t*)mpModel;
        RefObj* r = *(RefObj**)(m + 8);
        if (r) {
            *(void**)(m + 8) = 0;
            if (--*(int*)((char*)r + 4) == 0) {
                *(int*)((char*)r + 4) = 1;
                (*(void (__thiscall**)(void*, int))**(void***)r)(r, 1);
            }
        }
        RefObj* q = *(RefObj**)(m + 0xc);
        if (q) {
            *(void**)(m + 0xc) = 0;
            q->Release();
        }
        *(uint32_t*)(m + 0x2c) = c;
        *(uint32_t*)(m + 0x1c) = 0;
        *(uint32_t*)(m + 0x20) = d;
    }
    if (cat)
        cat->Release();
}

// @ 0x00e1e6d0
void __cdecl pairInsertionSort(Pair* first, Pair* last) // 0x00e1e6d0
{
    if (first == last)
        return;
    Pair* i = first + 1;
    if (i == last)
        return;
    do {
        uint32_t key = i->mKey;
        uint8_t flag = i->mFlag;
        RefObj* obj = i->mpObj;
        if (obj)
            obj->AddRef();
        Pair* hole = i;
        while (hole != first && key < hole[-1].mKey) {
            hole->mKey = hole[-1].mKey;
            hole->mFlag = hole[-1].mFlag;
            assignObj(hole->mpObj, hole[-1].mpObj);
            --hole;
        }
        hole->mKey = key;
        hole->mFlag = flag;
        assignObj(hole->mpObj, obj);
        if (obj)
            obj->Release();
        ++i;
    } while (i != last);
}

// @ 0x00e1e7d0
void __cdecl pairMakeHeap(Pair* first, Pair* last) // 0x00e1e7d0
{
    if (first == last)
        return;
    for (Pair* i = first + 1; i != last; ++i) {
        uint32_t key = i->mKey;
        uint8_t flag = i->mFlag;
        RefObj* obj = i->mpObj;
        if (obj)
            obj->AddRef();
        Pair* hole = i;
        while (hole != first && key < hole[-1].mKey) {
            hole->mKey = hole[-1].mKey;
            hole->mFlag = hole[-1].mFlag;
            assignObj(hole->mpObj, hole[-1].mpObj);
            --hole;
        }
        hole->mKey = key;
        hole->mFlag = flag;
        assignObj(hole->mpObj, obj);
        if (obj)
            obj->Release();
    }
}

// @ 0x00e1e8c0
void __cdecl pairSiftDown(Pair* base, int, int len, int hole, uint32_t key, uint8_t flag, RefObj* obj, int) // 0x00e1e8c0
{
    int child;
    for (;;) {
        child = hole * 2 + 2;
        if (len <= child)
            break;
        if (base[child].mKey < base[child - 1].mKey)
            child -= 1;
        base[hole].mKey = base[child].mKey;
        base[hole].mFlag = base[child].mFlag;
        assignObj(base[hole].mpObj, base[child].mpObj);
        hole = child;
    }
    if (child == len) {
        base[hole].mKey = base[child - 1].mKey;
        base[hole].mFlag = base[child - 1].mFlag;
        assignObj(base[hole].mpObj, base[child - 1].mpObj);
        hole = child - 1;
    }
    pairSiftUp(base, 0, hole, key, flag, obj);
}

// @ 0x00e1e9e0
void __cdecl pairPopHeap(Pair* first, Pair* last, int) // 0x00e1e9e0
{
    uint32_t key = last[-1].mKey;
    uint8_t flag = last[-1].mFlag;
    RefObj* obj = last[-1].mpObj;
    if (obj)
        obj->AddRef();

    last[-1].mKey = first->mKey;
    last[-1].mFlag = first->mFlag;
    assignObj(last[-1].mpObj, first->mpObj);

    int hole = (int)(last - first) - 1;
    pairSiftUp(first, 0, hole, key, flag, obj);
    if (obj)
        obj->Release();
}

// @ 0x00e1eab0
void __fastcall FUN_00e1eab0(PanelBase* self, int, int notifyId, int arg2, int arg3, int arg4)
{
    (*(void (__thiscall**)(PanelBase*))(*(char**)self + 0x14))(self);

    u32 key;
    if (notifyId == 0x01654c00)
        key = 0xa426730b;
    else if (notifyId == 0x01654c01)
        key = 0xad56080c;
    else
        key = ((u32)(-(s32)(arg2 != 0x6722bd6)) & 0xc5456627u) + 0x31da3cea;

    void* prop = 0;
    void* pm = FUN_0067de30();
    if (prop) {
        void* t = prop;
        prop = 0;
        (*(void (__thiscall**)(void*))(*(char**)t + 4))(t);
    }
    (*(void (__thiscall**)(void*, u32, u32, void**))(*(char**)pm + 0x2c))(pm, key, 0x7b2c1325, &prop);
    if (prop) {
        void* pv;
        if ((*(bool (__thiscall**)(void*, u32, void**))(*(char**)prop + 0x24))(prop, 0x5eea218, &pv)
                && *(u16*)((char*)pv + 0x12) == 10)
            self->mPropD4 = *(u32*)FUN_0041ea00(pv);
        if ((*(bool (__thiscall**)(void*, u32, void**))(*(char**)prop + 0x24))(prop, 0x9377367d, &pv)
                && *(u16*)((char*)pv + 0x12) == 10)
            self->mPropD8 = *(u32*)FUN_0041ea00(pv);
        if ((*(bool (__thiscall**)(void*, u32, void**))(*(char**)prop + 0x24))(prop, 0x55dd9f6, &pv)
                && *(u16*)((char*)pv + 0x12) == 10)
            self->mPropDC = *(u32*)FUN_0041ea00(pv);
    }
    u16 wE4 = 0x268b;
    if (prop) {
        void* pv;
        if ((*(bool (__thiscall**)(void*, u32, void**))(*(char**)prop + 0x24))(prop, 0x84ce9c17, &pv)
                && *(u16*)((char*)pv + 0x12) == 10)
            wE4 = *(u16*)FUN_0041ea00(pv);
    }
    self->mWordE4 = wE4;

    FUN_00e186d0(self, 0, notifyId, arg2, arg3, arg4);

    u32 s0 = 0xffffffff, s1 = 0xffffffff, s2 = 0;
    if (notifyId == 0x01654c00) { s0 = 0x1d2ec0a4; s1 = 0xdfad9f51; s2 = 0x3d97a8e4; }
    else if (notifyId == 0x01654c01) { s0 = 0x465c50ba; s1 = 0x9ea3031a; s2 = 0x2b978c46; }
    else if (notifyId == 0x01654c02) { s0 = 0x156276d1; s1 = 0x372e2c04; s2 = 0x2b978c46; }

    u32 qk = 0, qa = 0, qb = 0;
    if (self->mKey14 == 0x6722bd6) {
        void* nouns = FUN_00b3d300();
        void* tribe = FUN_00bfc5f0(nouns);
        if (tribe == 0) {
            void* ms = FUN_0067dcc0();
            (*(void (__thiscall**)(void*, void*, u32))(*(char**)ms + 0x24))(ms, self->mMsg0c, 0x1e8c9e0);
        } else {
            qa = 0xb1b104;
            qb = 0x406b6a00;
            void* nouns2 = FUN_00b3d300();
            void* tribe2 = FUN_00bfc5f0(nouns2);
            const char* name = FUN_00c8e850(tribe2) ? "PaletteIDTribeHerbivore" : "PaletteIDTribeCarnivore";
            u32 a = FUN_00932e80(name, 0x811c9dc5, 1);
            u32 b = FUN_00932e80("CommunityEditor", 0x811c9dc5, 1);
            qk = FUN_00bda3b0(b, 0, a, 0x41);
        }
    } else {
        void* prop2 = 0;
        void* pm2 = FUN_0067de30();
        if (prop2) {
            void* t = prop2;
            prop2 = 0;
            (*(void (__thiscall**)(void*))(*(char**)t + 4))(t);
        }
        (*(void (__thiscall**)(void*, u32, u32, void**))(*(char**)pm2 + 0x2c))(pm2, s0, 0x015a5200, &prop2);
        FUN_006a1250(prop2, 0xf5cbe065, &qk);
        if (prop2)
            (*(void (__thiscall**)(void*))(*(char**)prop2 + 4))(prop2);
    }

    FUN_00e1e500(self, 0, qk, qa, qb, s1, s2);

    if (self->mpRefBC == 0) {
        void* mem = FUN_00f473a0(0xc8, (const char*)0x013f6b3c, 0, 0, (const char*)0, 0);
        void* n = mem ? FUN_005ed360(mem, 0, 1) : 0;
        RefObj_s00e1_eab0* old = self->mpRefBC;
        if (n != old) {
            if (n)
                (*(void (__thiscall**)(void*))(*(char**)n + 0))(n);
            self->mpRefBC = (RefObj_s00e1_eab0*)n;
            if (old)
                (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)old + 4))(old);
        }
    }
    (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)self->mpRefBC + 0x1c))(self->mpRefBC);

    if (self->mPropDC != 0) {
        void* mem = FUN_00f473a0(0x6c, (const char*)0x013f6b3c, 0, 0, (const char*)0, 0);
        void* n = mem ? FUN_00663040(mem) : 0;
        RefObj_s00e1_eab0* old = self->mpRef48;
        if (n != old) {
            if (n)
                (*(void (__thiscall**)(void*))(*(char**)n + 0))(n);
            self->mpRef48 = (RefObj_s00e1_eab0*)n;
            if (old)
                (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)old + 4))(old);
        }
        void* w = FUN_008105b0(self->mLayout18, 0x5e95451, 1);
        FUN_00663860(self->mpRef48, 0, w, self->mPropDC, 0, 0);

        int ncat = FUN_00662a10(self->mpRef48);
        int cat = 0;
        int itemIdx = 0;
        while (cat < ncat) {
            void* c = FUN_00662a20(self->mpRef48, 0, cat);
            if (c != 0) {
                int nitems = FUN_00664600(c);
                for (int i = 0; i < nitems; ++i) {
                    void* it = FUN_00664610(c, 0, i);
                    if (it != 0) {
                        void* obj = *(void**)((char*)it + 0xa0);
                        ++itemIdx;
                        (*(void (__thiscall**)(void*, int))(*(char**)obj + 0x50))(obj, itemIdx + 0x66f5fde);
                    }
                }
            }
            ++cat;
        }
        if (FUN_00662a10(self->mpRef48) == 1) {
            void* c = FUN_00662a20(self->mpRef48, 0, 0);
            FUN_006644e0(c, 0, 0);
        }
        void* ms = FUN_0067dcc0();
        (*(void (__thiscall**)(void*, void*, u32))(*(char**)ms + 0x24))(ms, self->mMsg0c, 0x5bf34455);
    }

    void* w2 = FUN_008105b0(self->mLayout18, 0x5e9545c, 1);
    FUN_00e0a4c0((char*)self + 0x4c, 0, w2);

    if (prop)
        (*(void (__thiscall**)(void*))(*(char**)prop + 4))(prop);
}

// @ 0x00e1ef90
void __fastcall FUN_00e1ef90(void* self, int, void* item, int flag)
{
    if (item == 0)
        return;

    int idx = (*(int (__thiscall**)(void*))(*(char**)item + 0x1c))(item);
    int count = (*(int*)((char*)self + 0xc4) - *(int*)((char*)self + 0xc0)) / 0xc;
    int rec = idx - 0x66652c2;
    if ((u32)rec >= (u32)count)
        return;

    void* roll = (*(void* (__thiscall**)(void*, u32, int))(*(char**)item + 0xf0))(item, 0x60b0e48, 0);
    if (roll != 0)
        (*(void (__thiscall**)(void*, int, int))(*(char**)roll + 0x7c))(roll, 1, flag);

    if (flag == 0) {
        FUN_005ed6c0(*(void**)((char*)self + 0xbc));
        return;
    }

    void* audio = FUN_00a206f0();
    void* audioObj = audio ? (void*)(*(int (__thiscall**)(void*))(*(char**)audio + 0x20))(audio) : 0;
    FUN_00435ed0(0x8821b509, audioObj);

    void* recPtr = (char*)*(void**)((char*)self + 0xc0) + rec * 0xc;
    void* ref = *(void**)((char*)recPtr + 8);

    void* wrapObj = FUN_00b3d3f0();
    void* wrap = *(void**)((char*)wrapObj + 0x5c);
    FUN_00e30a60_s00e1_eab0(wrap, 0, idx);
    FUN_00eada10((char*)self + 0x34, 0, (char*)ref + 0xc);

    void* holder = *(void**)((char*)self + 0x44);
    int key = *(int*)((char*)holder + 0x2c);
    if (key != -1) {
        int mt = FUN_00432f10(key);
        if (mt != -1) {
            u32 loc[3] = { 0, 0, 0 };
            void* propObj = 0;
            void* pp = FUN_00a16f40((void*)&propObj);
            void* pm = FUN_0067de30();
            (*(void (__thiscall**)(void*, int, u32, void*))(*(char**)pm + 0x2c))(pm, mt, 0x015a5200, pp);
            if (propObj != 0) {
                FUN_006a1250(propObj, 0x4aa3989, loc);
                if (loc[0] != 0) {
                    void* propObj2 = 0;
                    void* pp2 = FUN_00a16f40((void*)&propObj2);
                    void* pm2 = FUN_0067de30();
                    (*(void (__thiscall**)(void*, u32, u32, void*))(*(char**)pm2 + 0x2c))(pm2, loc[1], loc[2], pp2);
                    if (propObj2 != 0) {
                        FUN_006a12a0(propObj2, 0x4ab54c1, &loc[0]);
                        (*(void (__thiscall**)(void*))(*(char**)propObj2 + 4))(propObj2);
                    }
                }
                (*(void (__thiscall**)(void*))(*(char**)propObj + 4))(propObj);
            }
        }
    }

    void* mem = FUN_00f473a0(0x64, (const char*)0x013f6b3c, 0, 0, (const char*)0, 0);
    void* veh = 0;
    if (mem != 0) {
        veh = FUN_0059f030(mem, 0, *(u32*)((char*)ref + 0), *(u32*)((char*)ref + 4), *(u32*)((char*)ref + 8),
                           *(u32*)((char*)holder + 0x2c), 0x14880158, 0, 1);
        if (veh != 0)
            (*(void (__thiscall**)(void*))(*(char**)veh + 4))(veh);
    }
    FUN_005ee480(*(void**)((char*)self + 0xbc), 0, ref, *(void**)((char*)self + 0x44), veh, 1);

    int* pv = (int*)(*(int (__thiscall**)(void*))(*(char**)item + 0x34))(item);
    float d = *(float*)((char*)pv + 0xc) - *(float*)((char*)pv + 4);
    float local[2] = { 0.0f, d };
    (*(void (__thiscall**)(void*, float*))(*(char**)item + 0xc0))(item, local);

    FUN_008283a0(*(void**)((char*)self + 0xbc), 0, local[0], local[1], -10.0f, 5.0f);
    FUN_005ed320(*(void**)((char*)self + 0xbc), 0, 2);

    if (veh != 0)
        (*(void (__thiscall**)(void*))(*(char**)veh + 8))(veh);
}

// @ 0x00e1f2c0
int __cdecl FUN_00e1f2c0(ListRec* first, ListRec* last, void* cmp)
{
    int n = (int)(((char*)last - (char*)first) / 0xc);
    int r = (int)(u32)(0x2aaaaaabu * (u32)((char*)last - (char*)first));
    if (n > 1) {
        int i = ((n - 2) >> 1) + 1;
        ListRec* p = first + i;
        do {
            u32 key = p[-1].key;
            u8 flag = p[-1].flag;
            RefObj_s00e1_eab0* ref = p[-1].ref;
            --i;
            if (ref)
                (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)ref + 4))(ref);
            r = (int)(size_t)FUN_00e1e8c0(first, i, n, i, key, flag, ref, cmp);
            --p;
        } while (i != 0);
    }
    return r;
}

// @ 0x00e1f390
void* __fastcall FUN_00e1f390(void* self)
{
    FUN_00e18bb0(self);
    *(void**)self = (void*)0x14803ac;
    *(void**)((char*)self + 8) = (void*)0x1480390;
    *(void**)((char*)self + 0xc) = (void*)0x1480388;
    *(void**)((char*)self + 0x40) = 0;
    *(void**)((char*)self + 0x44) = 0;
    *(void**)((char*)self + 0x48) = 0;
    FUN_00e0a390((char*)self + 0x4c);
    *(void**)((char*)self + 0xbc) = 0;
    *(void**)((char*)self + 0xc0) = 0;
    *(void**)((char*)self + 0xc4) = 0;
    *(void**)((char*)self + 0xc8) = 0;
    *(void**)((char*)self + 0xd4) = 0;
    *(void**)((char*)self + 0xd8) = 0;
    *(void**)((char*)self + 0xdc) = 0;
    *(void**)((char*)self + 0xe0) = 0;
    return self;
}

// @ 0x00e1f420
void __fastcall FUN_00e1f420(void* self)
{
    *(void**)self = (void*)0x14803ac;
    *(void**)((char*)self + 8) = (void*)0x1480390;
    *(void**)((char*)self + 0xc) = (void*)0x1480388;
    FUN_00e1e120(self);
    FUN_00e1f280((char*)self + 0xc0);
    RefObj_s00e1_eab0* r1 = *(RefObj_s00e1_eab0**)((char*)self + 0xbc);
    if (r1)
        (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)r1 + 4))(r1);
    FUN_00e0a400((char*)self + 0x4c);
    RefObj_s00e1_eab0* r2 = *(RefObj_s00e1_eab0**)((char*)self + 0x48);
    if (r2)
        (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)r2 + 4))(r2);
    RefObj_s00e1_eab0* r3 = *(RefObj_s00e1_eab0**)((char*)self + 0x44);
    if (r3)
        (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)r3 + 8))(r3);
    RefObj_s00e1_eab0* r4 = *(RefObj_s00e1_eab0**)((char*)self + 0x40);
    if (r4)
        (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)r4 + 8))(r4);
    FUN_00e18980(self);
}

// @ 0x00e1f4a0
u8 __fastcall FUN_00e1f4a0(void* self, int, void* arg1, void* msg)
{
    int* p = (int*)msg;
    (void)arg1;
    u32 r;
    if (p[2] == 0x1b) {
        r = (*(u32 (__thiscall**)(int))(*(int*)*p + 0x20))(*p);
        if (r == 0x66651c3)
            FUN_00e1ef90((char*)self - 8, 0, (void*)*p, 1);
    } else {
        r = (u32)p[2] - 0x1c;
        if (r == 0) {
            r = (*(u32 (__thiscall**)(int))(*(int*)*p + 0x20))(*p);
            if (r == 0x66651c3)
                FUN_00e1ef90((char*)self - 8, 0, (void*)*p, 0);
        }
    }
    return (u8)(r & 0xffffff00);
}

// @ 0x00e1f500
void __stdcall FUN_00e1f500(void* head, void* first, void* last, void* extra)
{
    char* cur = (char*)first;
    (void)extra;
    while (cur != last) {
        char* node = (char*)FUN_00f473a0(0x10, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        node = node;
        *(u32*)(node + 8) = *(u32*)(cur + 8);
        *(u32*)(node + 0xc) = *(u32*)(cur + 0xc);
        *(void**)node = head;
        *(void**)(node + 4) = *(void**)((char*)head + 4);
        *(void**)(*(void**)((char*)head + 4)) = node;
        *(void**)((char*)head + 4) = node;
        cur = *(char**)cur;
    }
}

// @ 0x00e1f570
void* __cdecl FUN_00e1f570(void* first, void* last, u32 key, u8 flag, RefObj_s00e1_eab0* ref, void* cmp)
{
    char* f = (char*)first;
    char* l = (char*)last;
    u32 pivot = key;
    for (;;) {
        while (*(u32*)f < pivot)
            f += 0xc;
        do {
            l -= 0xc;
        } while (pivot < *(u32*)l);
        if (f >= l)
            break;
        FUN_00e1e450(f, l);
        f += 0xc;
    }
    if (ref)
        (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)ref + 8))(ref);
    (void)flag;
    (void)cmp;
    return f;
}

// @ 0x00e1f5c0
void __cdecl FUN_00e1f5c0(void* a, void* b, void* c, void* d)
{
    ListRec* first  = (ListRec*)a;
    ListRec* middle = (ListRec*)b;
    char*    last   = (char*)c;
    void*    cmp    = d;

    FUN_00e1f2c0(first, middle, cmp);

    if ((char*)middle < last) {
        u32      count = ((u32)(last - (char*)middle) - 1) / 0xc + 1;
        ListRec* it    = middle;

        do {
            if (it->key < first->key) {
                ListRec tmp;                       // displaced record, holds its own reference
                RefObj_s00e1_eab0* old;

                tmp.key  = it->key;
                tmp.flag = it->flag;
                tmp.ref  = it->ref;
                if (tmp.ref != 0)
                    (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)tmp.ref + 4))(tmp.ref);

                old      = it->ref;
                it->key  = first->key;
                it->flag = first->flag;
                if (first->ref != old) {
                    if (first->ref != 0)
                        (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)first->ref + 4))(first->ref);
                    it->ref = first->ref;
                    if (old != 0)
                        (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)old + 8))(old);
                }

                // tmp is handed to adjust_heap by value, so the parameter carries a reference
                if (tmp.ref != 0)
                    (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)tmp.ref + 4))(tmp.ref);
                FUN_00e1e8c0(first, 0, (int)(((char*)middle - (char*)first) / 0xc), 0,
                              tmp.key, tmp.flag, tmp.ref, cmp);
                if (tmp.ref != 0)
                    (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)tmp.ref + 8))(tmp.ref);
            }
            ++it;
        } while (--count != 0);
    }

    FUN_00e1f330(first, middle, cmp);
}

// @ 0x00e1f700
void* __fastcall FUN_00e1f700(void* self, int, void* a, void* b)
{
    char* end = *(char**)((char*)self + 4);
    char* pos = (char*)FUN_00e1e390((char*)b, end, (char*)a);
    if (pos < end) {
        char* p = pos + 8;
        int n = (int)((end - pos) - 1) / 0xc + 1;
        do {
            RefObj_s00e1_eab0* r = *(RefObj_s00e1_eab0**)p;
            if (r)
                (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)r + 8))(r);
            p += 0xc;
            --n;
        } while (n != 0);
    }
    *(char**)((char*)self + 4) = end + (int)(((char*)a - (char*)b) / 0xc) * 0xc;
    return a;
}

// @ 0x00e1f780
void __fastcall FUN_00e1f780(void* self, int, void* pos, void* val)
{
    char* begin = *(char**)((char*)self);
    char* end = *(char**)((char*)self + 4);
    char* cap = *(char**)((char*)self + 8);
    if (end != cap) {
        if (pos <= val && val < end)
            val = (char*)val + 0xc;
        if (end) {
            *(u32*)end = *(u32*)(end - 0xc);
            *(u8*)(end + 4) = *(u8*)(end - 8);
            RefObj_s00e1_eab0* r = *(RefObj_s00e1_eab0**)(end - 4);
            *(RefObj_s00e1_eab0**)(end + 8) = r;
            if (r)
                (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)r + 4))(r);
        }
        FUN_00e1e3f0(pos, end - 0xc, end);
        *(u32*)pos = *(u32*)val;
        *(u8*)((char*)pos + 4) = *(u8*)((char*)val + 4);
        RefObj_s00e1_eab0* rn = *(RefObj_s00e1_eab0**)((char*)val + 8);
        RefObj_s00e1_eab0* ro = *(RefObj_s00e1_eab0**)((char*)pos + 8);
        if (rn != ro) {
            if (rn)
                (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)rn + 4))(rn);
            *(RefObj_s00e1_eab0**)((char*)pos + 8) = rn;
            if (ro)
                (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)ro + 8))(ro);
        }
        *(char**)((char*)self + 4) = end + 0xc;
        return;
    }

    int count = (int)((end - begin) / 0xc);
    int newcap;
    char* mem;
    if (count == 0) {
        newcap = 1;
    } else {
        newcap = count * 2;
        if (newcap == 0) {
            mem = 0;
            goto build;
        }
    }
    mem = (char*)FUN_00f473a0(newcap * 0xc, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
build:
    {
        char* mid = (char*)FUN_00e1e240(begin, pos, mem);
        FUN_00e1e290(begin, pos, mem);
        if (mid) {
            *(u32*)mid = *(u32*)val;
            *(u8*)(mid + 4) = *(u8*)((char*)val + 4);
            RefObj_s00e1_eab0* r = *(RefObj_s00e1_eab0**)((char*)val + 8);
            *(RefObj_s00e1_eab0**)(mid + 8) = r;
            if (r)
                (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)r + 4))(r);
        }
        char* tailEnd = (char*)FUN_00e1e240(pos, end, mid + 0xc);
        FUN_00e1e290(pos, end, mid + 0xc);
        if (begin && *(int*)(begin - 4) != 0)
            FUN_00f47380(begin);
        *(char**)((char*)self + 4) = tailEnd;
        *(char**)((char*)self) = mem;
        *(char**)((char*)self + 8) = mem + newcap * 0xc;
    }
}

// @ 0x00e1f920
void __cdecl FUN_00e1f920(char* first, char* last, int depth, void* cmp)
{
    while (0x1c < (int)((last - first) / 0xc) && depth > 0) {
        int n = (int)((last - first) / 0x18);
        char* mid = first + n * 0xc;
        u32 ukFirst = *(u32*)first;
        u32 ukMid = *(u32*)mid;
        u32 ukLast = *(u32*)(last - 0xc);
        char* med;
        if (ukFirst >= ukMid) {
            if (ukFirst >= ukLast)
                med = (ukMid >= ukLast) ? mid : last - 0xc;
            else
                med = first;
        } else {
            if (ukMid < ukLast)
                med = mid;
            else
                med = (ukFirst >= ukLast) ? first : last - 0xc;
        }

        ListRec pivot = *(ListRec*)med;
        if (pivot.ref)
            (*(void (__thiscall**)(RefObj_s00e1_eab0*))(*(char**)pivot.ref + 4))(pivot.ref);
        char* p = (char*)FUN_00e1f570(first, last, pivot.key, pivot.flag, pivot.ref, cmp);
        --depth;
        FUN_00e1f920(p, last, depth, cmp);
        last = p;
    }
    if (depth == 0)
        FUN_00e1f5c0(first, last, last, cmp);
}

// @ 0x00e1fa20
void* __fastcall FUN_00e1fa20(void* self, int, void* other)
{
    char* s = (char*)self;
    char* o = (char*)other;
    if (s != o) {
        char* p2 = *(char**)o;
        char* p1 = *(char**)s;
        while (p1 != s) {
            if (p2 == o)
                goto erase;
            *(void**)(p1 + 8) = *(void**)(p2 + 8);
            *(void**)(p1 + 0xc) = *(void**)(p2 + 0xc);
            p2 = *(char**)p2;
            p1 = *(char**)p1;
        }
        if (p2 == o) {
erase:
            FUN_00973d10(&o, p1);
            return self;
        }
        FUN_00e1f500(s, p2, o, o);
    }
    return self;
}

// @ 0x00e1fa90
void __cdecl FUN_00e1fa90(char* first, char* last, void* cmp)
{
    if (first != last) {
        int n = (int)((last - first) / 0xc);
        int bits = 0;
        for (int v = n; v != 0; v >>= 1)
            ++bits;
        FUN_00e1f920(first, last, bits * 2 - 2, cmp);
        if (n > 0x1c) {
            FUN_00e1e6d0(first, first + 0x150, cmp);
            FUN_00e1e7d0(first + 0x150, last, cmp);
        } else {
            FUN_00e1e6d0(first, last, cmp);
        }
    }
}
