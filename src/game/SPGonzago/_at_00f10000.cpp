// src/game/SPGonzago/_at_00f10000.cpp -- migrated from slice(s) s00f1faa0, s00f1e020, s00f1bcf0, s00f1ae10, s00f18eb0, s00f17f70, s00f170c0, s00f16580, s00f15890, s00f145a0, s00f13330, s00f12340, s00f114a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00f10000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPaletteItem.h"
#include "SP/cSPPaletteItemUI.h"
#include "SP/cSPPaletteCategoryUI.h"
#include "cSPUIPropertyLayout.h"
#include "SP/cString.h"
#include <intrin.h>
#include "SP/cSPCreatureBase.h"
#include "cSPUILayout.h"
#include "SP/cSPPalette.h"
#include "SP/cSPPaletteCategory.h"
#include "EA/UTFWin/CustomWindow.h"
#include "SP/cGameNounManager.h"
#include "SP/cCombatant.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Stopwatch.h"

// unnamed retail callees and globals (address in the comment)
extern const char g_148bfc8[];                // 0x0148bfc8 "TriggerConfigScenarioMode"
extern const char g_1477758[];                // 0x01477758 "TriggerConfigWASD_fr-fr"
extern const char g_1477770[];                // 0x01477770 "TriggerConfigWASD"
extern const char g_148bfb0[];                // 0x0148bfb0 "UIMachineScenarioMode"
extern const wchar_t g_1403c98[];             // 0x01403c98 L"fr-fr"
extern const wchar_t g_147a7d4[];             // "cursor-target"
extern const wchar_t g_1476df0[];             // "cursor-mate"
extern const wchar_t g_1476ef8[];             // "cursor-heal"
extern const wchar_t g_1476eac[];             // "cursor-eat-fruit"
extern const wchar_t g_1476ed0[];             // "cursor-eat-carcass"
extern const wchar_t g_1476e24[];             // "cursor_atk"
extern const wchar_t g_147a7b8[];             // "cursor-evolve"
extern const wchar_t g_147a798[];             // "cursor-validate"
extern const wchar_t g_1476d30[];             // "cursor_social"
extern const wchar_t g_147a77c[];             // "cursor_friend"
extern const wchar_t g_147a75c[];             // "cursor_socialNo"
extern const wchar_t g_147a734[];             // "cursor-crg-addposse"
extern const wchar_t g_13fecec[];             // "cursor-crg-pickup"
extern const wchar_t g_147a70c[];             // "cursor-crg-putdown"
extern const wchar_t g_147a6f0[];             // "cur_ClaimNest"
extern const wchar_t g_147a6d0[];             // "cursor-crg-give"
extern const wchar_t g_13fecc8[];             // "cursor-crg-throw"
extern const wchar_t g_147a6a0[];             // "cursor-target-creature"
extern const wchar_t g_147a67c[];             // "cursor_skeleton2"
extern const wchar_t g_148bf94[];             // "cursor-talkto"
extern const wchar_t g_148bf70[];             // "cursor-talktoGoal"
extern const wchar_t g_148bf34[];             // "cursor-target-creature-friend"
extern const wchar_t g_148bef8[];             // "cursor-target-creature-enemy"
extern "C" void FUN_00efcae0();                       // ScenarioTutorials_CloseWindow
extern "C" void __fastcall FUN_00d37b60(void*);       // base dtor
extern "C" bool FUN_006ab760(void* obj, const wchar_t* tag);

// ---- items of slice s00f114a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  u32;
typedef unsigned char u8;
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
struct Vec2 { float x, y; };
struct CObj {
    PV
    virtual int AddRef();       // +0x04
    virtual int Release();      // +0x08
};
struct IWin {
    PV8 PV4 PV2                                  // 0x00 .. 0x34
    virtual float* GetRect();                    // +0x38
    PV16                                         // 0x3c .. 0x78
    virtual void SetVisible(int group, bool on); // +0x7c
    virtual void SetText(const wchar_t* text);   // +0x80
    PV8 PV4 PV2 PV                               // 0x84 .. 0xbc
    virtual void* FUN_c0(Vec2 size, void* out);  // +0xc0
};
struct InputManager {
    PV PV PV PV
    virtual void SetTriggerConfig(const char* name, int a, int b); // +0x10
    PV PV PV
    virtual void FUN_slot20(void* out, int a, int b);              // +0x20
    PV PV PV PV PV PV
    virtual void SetUIMachine(const char* name);                   // +0x3c
};
struct DevMgr {
    PV8 PV4 PV2
    virtual void AddSub(void* sub, int on);   // +0x38
    PV
    virtual void RemoveSub(void* sub);        // +0x40
};
struct Loc {
    PV PV PV PV PV
    virtual void* FUN_slot14();               // +0x14
};
struct CursorTable {
    u32 AddCursor(void* id, const wchar_t* name, int a, int b, int c); // 0x00802050
};
struct MsgServer {
    PV8 PV
    virtual void AddHandler(void* target, u32 msgId); // +0x24
};
struct EList {                       // empty eastl list header
    void* next;                      // +0x00
    void* prev;                      // +0x04
    u32   n;                         // +0x08
    u8    b;                         // +0x0c
    u8    pad[3];
    u32   f10;                       // +0x10
};
struct E4 { void FUN_00e4b990(void* arg); };   // 0x00e4b990
struct B1 { void FUN_00b1b830(void* arg); };   // 0x00b1b830
struct cCreatureModeInputStrategy {
    void* volatile mpVt;              // +0x00
    char  pad04[0x3c - 4];
    void* volatile mpVt3c;            // +0x3c
    char  pad40[4];
    void* volatile mpVt44;            // +0x44
    void* volatile mpVt48;            // +0x48
    void* volatile mpVt4c;            // +0x4c
    char  pad50[4];
    u8    mActive;                    // +0x54
    char  pad55[0x108 - 0x55];
    void* volatile m108;              // +0x108 (messaging server)
    u32   volatile m10c;              // +0x10c (handler object)
    void* volatile m110;              // +0x110 (message table)
    u32   volatile m114;              // +0x114 (message count)
    u32   volatile m118;              // +0x118

    void*  FUN_00f11b60();            // ctor-equivalent (returns this)
    void   FUN_00f11c30();            // dtor-equivalent
    void   FUN_00f11ca0();
    void   FUN_00f11f90();
    void   FUN_00f11ac0(int arg);
    bool   FUN_00f11b10(u32 msg, u32 arg);
    bool   HandleMessage(u32 msg, u32 arg);       // 0x00d35190
    void   FUN_00d32fb0(int arg);                 // 0x00d32fb0
    void   FUN_00d342d0();                        // 0x00d342d0
    void   SetInputPriorityStrategy(int s);       // 0x00d33ec0
};
struct Key { u32 a, b, c; };
class cSPUILayout_s00f1_14a0 : public CObj { public:
    void* ctor();                                              // 0x00810000
    bool Init(const Key& key, bool b, u32 id);                 // 0x008120d0
    bool SetParentWin(IWin* parent, bool b, u32 id);           // 0x008121b0
    IWin* FindWindowByID(u32 id, bool recursive);              // 0x008105b0
    char pad[0x18 - 0x0c];
};
struct cSPPaletteItem : CObj {
    char pad[0x54 - 0x0c];
};
struct cSPPaletteItemUI {
    char pad[0x20];
    void Init(void* a, void* b, void* c, void* d);   // 0x005c6ca0
    void Shutdown();                                 // 0x005c6d20
    cSPPaletteItemUI();                              // 0x005c6bf0
};
template <class T> struct AutoRefCount {
    T* mp;
    AutoRefCount& operator=(T* p)
    {
        T* old = mp;
        if (p != old) {
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
};
struct cScenarioUnlockItemUI : cSPPaletteItemUI {
    AutoRefCount<cSPUILayout_s00f1_14a0>     mpLayout;    // +0x20
    AutoRefCount<cSPPaletteItem>  mpItem;      // +0x24
    u32 m28, m2c, m30;                         // +0x28

    void Init(void* a, void* b, void* c, cSPPaletteItem* d);   // 0x00f12140
    void Shutdown();                                            // 0x00f12270
};
extern u32   g_148be90[];                     // 0x0148be90 26 registered message ids
extern const char g_148bfc8[];                // 0x0148bfc8 "TriggerConfigScenarioMode"
extern const char g_1477758[];                // 0x01477758 "TriggerConfigWASD_fr-fr"
extern const char g_1477770[];                // 0x01477770 "TriggerConfigWASD"
extern const char g_148bfb0[];                // 0x0148bfb0 "UIMachineScenarioMode"
extern const wchar_t g_1403c98[];             // 0x01403c98 L"fr-fr"
extern const wchar_t g_147a7d4[];             // "cursor-target"
extern const wchar_t g_1476df0[];             // "cursor-mate"
extern const wchar_t g_1476ef8[];             // "cursor-heal"
extern const wchar_t g_1476eac[];             // "cursor-eat-fruit"
extern const wchar_t g_1476ed0[];             // "cursor-eat-carcass"
extern const wchar_t g_1476e24[];             // "cursor_atk"
extern const wchar_t g_147a7b8[];             // "cursor-evolve"
extern const wchar_t g_147a798[];             // "cursor-validate"
extern const wchar_t g_1476d30[];             // "cursor_social"
extern const wchar_t g_147a77c[];             // "cursor_friend"
extern const wchar_t g_147a75c[];             // "cursor_socialNo"
extern const wchar_t g_147a734[];             // "cursor-crg-addposse"
extern const wchar_t g_13fecec[];             // "cursor-crg-pickup"
extern const wchar_t g_147a70c[];             // "cursor-crg-putdown"
extern const wchar_t g_147a6f0[];             // "cur_ClaimNest"
extern const wchar_t g_147a6d0[];             // "cursor-crg-give"
extern const wchar_t g_13fecc8[];             // "cursor-crg-throw"
extern const wchar_t g_147a6a0[];             // "cursor-target-creature"
extern const wchar_t g_147a67c[];             // "cursor_skeleton2"
extern const wchar_t g_148bf94[];             // "cursor-talkto"
extern const wchar_t g_148bf70[];             // "cursor-talktoGoal"
extern const wchar_t g_148bf34[];             // "cursor-target-creature-friend"
extern const wchar_t g_148bef8[];             // "cursor-target-creature-enemy"
extern Key g_15ad898;                         // 0x015ad898 layout key
extern Key g_15ad8c0;                         // 0x015ad8c0 path key
extern "C" InputManager* FUN_00b3d250();
extern "C" DevMgr* FUN_00b3d230();
extern "C" Loc* FUN_0067de40();
extern "C" CursorTable* FUN_0067cab0();
extern "C" MsgServer* FUN_00883860();
extern "C" void FUN_00efcae0();                       // ScenarioTutorials_CloseWindow
extern "C" void __fastcall FUN_00d37b60(void*);       // base dtor
extern "C" bool FUN_006ab760(void* obj, const wchar_t* tag);
extern "C" void FUN_00571db0(void*, void*, void*, u32, u32); // EA::Messaging::RemoveHandler
extern "C" void __cdecl SetWindowAreaToParent(IWin* win);    // 0x00806bf0
extern "C" void* __cdecl EAAllocate(u32 size, const char* name, int, int, int, int); // 0x00f473a0
struct QI {
    u32 FUN_00f12090(u32 id);
};
struct KeySink {
    void FUN_00e0a4c0(u32 value, const void* key);   // 0x00e0a4c0
};
struct KeyForwarder {
    char pad[8];
    KeySink sink;                     // +0x08
    void FUN_00f120c0(u32 value);
};
// ---- items of slice s00f114a0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern u32   g_148be90[];                     // 0x0148be90 26 registered message ids
extern Key g_15ad898;                         // 0x015ad898 layout key
extern Key g_15ad8c0;                         // 0x015ad8c0 path key
extern "C" InputManager* FUN_00b3d250();
extern "C" DevMgr* FUN_00b3d230();
extern "C" Loc* FUN_0067de40();
extern "C" CursorTable* FUN_0067cab0();
extern "C" MsgServer* FUN_00883860();
extern "C" void FUN_00571db0(void*, void*, void*, u32, u32); // EA::Messaging::RemoveHandler
extern "C" void __cdecl SetWindowAreaToParent(IWin* win);    // 0x00806bf0
extern "C" void* __cdecl EAAllocate(u32 size, const char* name, int, int, int, int); // 0x00f473a0

// ---- items of slice s00f12340 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char vtbl_148c034[], vtbl_148c018[], vtbl_148c008[];
extern char vtbl_148c0e4[], vtbl_148c0d4[], vtbl_148c0b8[];
extern char vtbl_13eb938[], vtbl_13ec458[], vtbl_13eb394[];
struct Sub900;   // object at *(host+0x14)+0x10 : has Set(int)
struct SubUI;    // the UI object living at host+0x1c
struct SubUI2;   // the UI object living at host+0x20 (IUnknown at +0x10)
class cSPUILayout_s00f1_2340;
struct cSPPalette;
struct cSPPaletteCategory;
struct cSPPaletteCategoryUI;
struct cSPPalettePage;
struct cSPPalettePageUI;
struct cSPPaletteItem;
struct EAKey;
struct ResourceKey { unsigned a, b, c; };
struct Sub900b {
  virtual void vv0();
  virtual void vv1();
  void Set(int b);      // 0x5970d0  (thiscall)
};
struct RefObj {
  virtual void AddRef();
  virtual void Release();
};
struct WinObjRef {              // AutoRefCount<WinObj>
  RefObj* mpObject;
  WinObjRef() : mpObject(0) {}
  ~WinObjRef() { if (mpObject) mpObject->Release(); }
  operator RefObj*() const { return mpObject; }
};
struct Sub900 {
  char pad[0x10];
  WinObjRef mpWin;      // +0x10  (an AutoRefCount<WinObj>)
};
struct SubUI {
  virtual void AddRef();      // +0x00
  virtual void Release();     // +0x04
  virtual void vv2();         // +0x08
  virtual void vv3();         // +0x0c
  virtual void vv4();         // +0x10
  virtual void vv5();         // +0x14
  virtual void vv6();         // +0x18
  virtual void vv7();         // +0x1c
  virtual void Shutdown2();   // +0x20
};
struct SubRef {               // the IUnknown at +0x10 of the +0x20 object
  virtual void AddRef();      // +0x00
  virtual void Release();     // +0x04
};
struct SubUI2 {
  virtual void vv0();         // vptr at +0x00
  virtual void Update(void* p);   // +0x04
  virtual void vv2();
  virtual void vv3();
  char pad[0x0c];
  SubRef mRef;                // +0x10
};
struct WinObj2v {
  virtual void q0();            // +0x00
  virtual void q1();
  virtual void q2();
  virtual void q3();
  virtual void q4();
  virtual void q5();
  virtual void q6();
  virtual void q7();
  virtual void q8();
  virtual void q9();
  virtual void SetIdx4(int a, int b);   // +0x28
};
struct WinObj {                 // a UTFWin IWindow
  virtual void AddRef();        // +0x00
  virtual void Release();       // +0x04
  virtual void vv2();           // +0x08
  virtual WinObj2v* Cast(unsigned typeID);  // +0x0c
  virtual WinObj* Child();      // +0x10
  virtual void vv5();           // +0x14
  virtual void vv6();           // +0x18
  virtual void vv7();           // +0x1c
  virtual void vv8();           // +0x20
  virtual void vv9();           // +0x24
  virtual void vv10();          // +0x28
  virtual void vv11();          // +0x2c
  virtual void vv12();          // +0x30
  virtual void vv13();          // +0x34
  virtual void vv14();          // +0x38
  virtual void vv15();          // +0x3c
  virtual void vv16();          // +0x40
  virtual void vv17();          // +0x44
  virtual void vv18();          // +0x48
  virtual void vv19();          // +0x4c
  virtual void vv20();          // +0x50
  virtual void vv21();          // +0x54
  virtual void vv22();          // +0x58
  virtual void vv23();          // +0x5c
  virtual void vv24();          // +0x60
  virtual void vv25();          // +0x64
  virtual void vv26();          // +0x68
  virtual void vv27();          // +0x6c
  virtual void vv28();          // +0x70
  virtual void vv29();          // +0x74
  virtual void vv30();          // +0x78
  virtual void SetVisible(int a, int b);  // +0x7c
};
class cSPUILayout_s00f1_2340 { public:
  virtual void vv0();
  virtual void AddRef();       // +0x04
  virtual void Release();      // +0x08
  void Shutdown(unsigned a);   // 0x811ad0
  void SetVisibility(bool v);  // 0x810590
  WinObj* FindWindowByID(unsigned id, bool a);   // 0x8105b0
  char Init(const EAKey* key, bool a, int b);            // 0x8120d0
  char SetParentWin(void* parent, bool a, int b);        // 0x8121b0
};
void EAMessaging_RemoveHandler(int a, int b, int c, int d, int e);                 // 0x571db0
void* f_00e09ca0(void* layout, int col, int row);                                  // 0xe09ca0
void SPUIHelpers_BeginModal(void* win, int a, int b);                              // 0x8099a0
void SPUIHelpers_EndModal(WinObj* win, int a, int b);                              // 0x809c50
unsigned char f_00807cb0(void* win, void* a, int b);                               // 0x807cb0
void SPUIHelpers_AnchorWindowToWindow(void* a, void* b, int c, int d);             // 0x807340
char f_00eed9c0(void* a, void* b);                                                 // 0xeed9c0
void f_00ed1350(void* win, int a);                                                 // 0xed1350
void GetPropertyAsKey(void* item, unsigned key, void* out);                        // 0x6a1250
void* SP_PropertyManager();                                                        // 0x67de30
void* GetEditorUI();                                                               // 0x401020
struct EVeh {
  void* Init(ResourceKey key, unsigned x, unsigned y, unsigned z, bool w);  // 0x59f030
};
unsigned long long f_00593980_(int a, int b);                                      // 0x593980
void EAAllocate_free(void* p);                                                     // 0xf47380
struct Host {
  char pad00[0x04];
  void* mWnd;                    // +0x04
  char pad08[0x04];
  cSPUILayout_s00f1_2340* mLayout;          // +0x0c
  cSPPalette* mPalette;          // +0x10
  char* mItemHost;               // +0x14
  cSPPaletteCategoryUI* mCatUI;  // +0x18
  SubUI* mSel;                   // +0x1c
  SubUI2* mSub;                  // +0x20
  char* mPageBase;               // +0x24
  unsigned mKeyA;                // +0x28
  unsigned mKeyB;                // +0x2c
  unsigned mKeyC;                // +0x30
  char pad34[0x08];
  char mFlag3c;                  // +0x3c
  char pad3d[0x03];
  unsigned mGroup;               // +0x40
  char pad44[0x04];
  void* mHandler;                // +0x48
  int   mH0;                     // +0x4c
  int   mH1;                     // +0x50
  int   mH2;                     // +0x54
  int   mH3;                     // +0x58

  // The slice's functions (members of Host, i.e. __thiscall like the original).
  void FUN_00f12340();
  void* FUN_00f12690();
  void FUN_00f126d0();
  void FUN_00f12700(void* parent);
  void FUN_00f128f0();
  void FUN_00f12970();
  void FUN_00f12a60();
  Host* FUN_00f12b00(unsigned flags);
  void FUN_00f12b50(cSPPaletteItem* item);
  void FUN_00f12de0();
  void FUN_00f12eb0();
  bool FUN_00f12fc0(void* unused, void* msg);
};
struct PageVec { void Clear(); };                       // 0xf12ac0
struct PIB { void Dtor(); };                            // 0x5c6c50
struct PIB2 { void SetPaletteItem(void* item); };       // 0x5c6ec0
struct ConnDialog { ConnDialog* ctor(); };              // 0x810000
struct Obj1c {                                          // the object at +0x1c
  virtual void AddRef();        // +0x00
  virtual void Release();       // +0x04
  virtual void a08();           // +0x08
  virtual void a0c();           // +0x0c
  virtual void a10();           // +0x10
  virtual void a14();           // +0x14
  virtual void a18();           // +0x18
  virtual void Setup(void*, void*, void*, void*);  // +0x1c
  virtual void a20();           // +0x20
  virtual void a24();           // +0x24
  virtual void a28();           // +0x28
  virtual void a2c();           // +0x2c
  virtual void SetMode(int a, int b);              // +0x30
};
struct PageBase {                                       // the per-page UI base
  void Reset();                                    // 0xe0a5c0
  void Attach(void* p);                            // 0xe0a4c0
  void Fill(void* panel, int count);               // 0xe0a780
};
struct ConnObj { void* Init(); };                       // 0xec41e0
struct ConnObj2 { void* Init(); };                      // 0xef3b40
struct cStringObj {                                     // SP::cString (0x14 bytes)
  void* mpTableResource;
  void* mpLocalString;
  void* mpSourceCStr;
  unsigned char mFlags[8];
  cStringObj();                                         // 0x6b5060
  ~cStringObj();                                        // 0x6b5240
};
void* SPUI_SetWindowAreaToParent(void* win);            // 0x806bf0
char FUN_005c6730f(void* p);                            // 0x5c6730
char FUN_005c65f0f(void* p);                            // 0x5c65f0
#define PV_s00f1_2340(n) virtual void pv##n();
struct CatUI {                                   // cSPPaletteCategoryUI
  void Shutdown();                               // 0x5c4e40
  void Init(void* cat, void* win, void* info);   // 0x5c53c0
  void SetVisibility(bool v);                    // 0x5c2960
  cSPPalettePageUI* GetPageUI(int index);        // 0x5c2e50
};
struct Palette {                                 // cSPPalette
  cSPPaletteCategory* GetCategory(int index);    // 0x5c5de0
};
struct Cat {                                     // cSPPaletteCategory
  cSPPalettePage* GetPage(int index);            // 0x5c1ce0
  cSPPaletteCategory* GetSubCategory(int index); // 0x5cae30
};
struct ObjUI {                                   // the window object at pageUI+0x10
  PV_s00f1_2340(0) PV_s00f1_2340(1) PV_s00f1_2340(2) PV_s00f1_2340(3) PV_s00f1_2340(4) PV_s00f1_2340(5) PV_s00f1_2340(6) PV_s00f1_2340(7) PV_s00f1_2340(8) PV_s00f1_2340(9)
  PV_s00f1_2340(10) PV_s00f1_2340(11) PV_s00f1_2340(12) PV_s00f1_2340(13) PV_s00f1_2340(14) PV_s00f1_2340(15) PV_s00f1_2340(16) PV_s00f1_2340(17) PV_s00f1_2340(18) PV_s00f1_2340(19)
  PV_s00f1_2340(20) PV_s00f1_2340(21) PV_s00f1_2340(22) PV_s00f1_2340(23) PV_s00f1_2340(24) PV_s00f1_2340(25) PV_s00f1_2340(26) PV_s00f1_2340(27) PV_s00f1_2340(28) PV_s00f1_2340(29)
  PV_s00f1_2340(30) PV_s00f1_2340(31) PV_s00f1_2340(32) PV_s00f1_2340(33) PV_s00f1_2340(34) PV_s00f1_2340(35) PV_s00f1_2340(36) PV_s00f1_2340(37) PV_s00f1_2340(38) PV_s00f1_2340(39)
  PV_s00f1_2340(40) PV_s00f1_2340(41) PV_s00f1_2340(42) PV_s00f1_2340(43) PV_s00f1_2340(44) PV_s00f1_2340(45) PV_s00f1_2340(46) PV_s00f1_2340(47) PV_s00f1_2340(48) PV_s00f1_2340(49)
  PV_s00f1_2340(50) PV_s00f1_2340(51) PV_s00f1_2340(52) PV_s00f1_2340(53) PV_s00f1_2340(54) PV_s00f1_2340(55) PV_s00f1_2340(56) PV_s00f1_2340(57) PV_s00f1_2340(58) PV_s00f1_2340(59)
  virtual void* Get(unsigned id, int a, void* out);   // +0xf0
};
struct PageUI { char pad[0x10]; ObjUI* mObj; };       // cSPPalettePageUI
struct EvObj {                       // ev: release is the 3rd slot
  virtual void a0();                 // +0x00
  virtual void a4();                 // +0x04
  virtual void Release8();           // +0x08
};
struct GObjX {                       // objects with AddRef(0)/Release(4) and +0x104
  virtual void AddRef();             // +0x00
  virtual void Release();            // +0x04
  PV_s00f1_2340(2) PV_s00f1_2340(3) PV_s00f1_2340(4) PV_s00f1_2340(5) PV_s00f1_2340(6) PV_s00f1_2340(7) PV_s00f1_2340(8) PV_s00f1_2340(9)
  PV_s00f1_2340(10) PV_s00f1_2340(11) PV_s00f1_2340(12) PV_s00f1_2340(13) PV_s00f1_2340(14) PV_s00f1_2340(15) PV_s00f1_2340(16) PV_s00f1_2340(17) PV_s00f1_2340(18) PV_s00f1_2340(19)
  PV_s00f1_2340(20) PV_s00f1_2340(21) PV_s00f1_2340(22) PV_s00f1_2340(23) PV_s00f1_2340(24) PV_s00f1_2340(25) PV_s00f1_2340(26) PV_s00f1_2340(27) PV_s00f1_2340(28) PV_s00f1_2340(29)
  PV_s00f1_2340(30) PV_s00f1_2340(31) PV_s00f1_2340(32) PV_s00f1_2340(33) PV_s00f1_2340(34) PV_s00f1_2340(35) PV_s00f1_2340(36) PV_s00f1_2340(37) PV_s00f1_2340(38) PV_s00f1_2340(39)
  PV_s00f1_2340(40) PV_s00f1_2340(41) PV_s00f1_2340(42) PV_s00f1_2340(43) PV_s00f1_2340(44) PV_s00f1_2340(45) PV_s00f1_2340(46) PV_s00f1_2340(47) PV_s00f1_2340(48) PV_s00f1_2340(49)
  PV_s00f1_2340(50) PV_s00f1_2340(51) PV_s00f1_2340(52) PV_s00f1_2340(53) PV_s00f1_2340(54) PV_s00f1_2340(55) PV_s00f1_2340(56) PV_s00f1_2340(57) PV_s00f1_2340(58) PV_s00f1_2340(59)
  PV_s00f1_2340(60) PV_s00f1_2340(61) PV_s00f1_2340(62) PV_s00f1_2340(63) PV_s00f1_2340(64)
  virtual void SetHandler(void* p);  // +0x104
};
struct SubRec {                      // the object at (subcategory + 0x1c)
  PV_s00f1_2340(0) PV_s00f1_2340(1) PV_s00f1_2340(2) PV_s00f1_2340(3) PV_s00f1_2340(4) PV_s00f1_2340(5) PV_s00f1_2340(6) PV_s00f1_2340(7) PV_s00f1_2340(8) PV_s00f1_2340(9)
  PV_s00f1_2340(10) PV_s00f1_2340(11) PV_s00f1_2340(12) PV_s00f1_2340(13) PV_s00f1_2340(14) PV_s00f1_2340(15) PV_s00f1_2340(16) PV_s00f1_2340(17) PV_s00f1_2340(18) PV_s00f1_2340(19)
  PV_s00f1_2340(20) PV_s00f1_2340(21) PV_s00f1_2340(22) PV_s00f1_2340(23) PV_s00f1_2340(24) PV_s00f1_2340(25) PV_s00f1_2340(26) PV_s00f1_2340(27) PV_s00f1_2340(28) PV_s00f1_2340(29)
  PV_s00f1_2340(30) PV_s00f1_2340(31) PV_s00f1_2340(32) PV_s00f1_2340(33) PV_s00f1_2340(34) PV_s00f1_2340(35) PV_s00f1_2340(36) PV_s00f1_2340(37) PV_s00f1_2340(38) PV_s00f1_2340(39)
  PV_s00f1_2340(40) PV_s00f1_2340(41) PV_s00f1_2340(42) PV_s00f1_2340(43) PV_s00f1_2340(44) PV_s00f1_2340(45) PV_s00f1_2340(46) PV_s00f1_2340(47) PV_s00f1_2340(48) PV_s00f1_2340(49)
  PV_s00f1_2340(50) PV_s00f1_2340(51) PV_s00f1_2340(52) PV_s00f1_2340(53) PV_s00f1_2340(54) PV_s00f1_2340(55) PV_s00f1_2340(56) PV_s00f1_2340(57) PV_s00f1_2340(58) PV_s00f1_2340(59)
  virtual WinObj* Make(unsigned id, int a);   // +0xf0
};
struct Page {                        // cSPPalettePage
  cSPPaletteItem* GetItem(int index);         // 0x5c7f00
};
struct PropVal {                     // a property value object
  PV_s00f1_2340(0) PV_s00f1_2340(1) PV_s00f1_2340(2) PV_s00f1_2340(3) PV_s00f1_2340(4) PV_s00f1_2340(5) PV_s00f1_2340(6) PV_s00f1_2340(7) PV_s00f1_2340(8) PV_s00f1_2340(9)
  virtual void* M28(unsigned key);            // +0x28
  void* GetTPTR();                            // 0x454b10
};
struct PropMgr {                     // SP::PropertyManager()
  PV_s00f1_2340(0) PV_s00f1_2340(1) PV_s00f1_2340(2) PV_s00f1_2340(3) PV_s00f1_2340(4) PV_s00f1_2340(5) PV_s00f1_2340(6) PV_s00f1_2340(7) PV_s00f1_2340(8) PV_s00f1_2340(9) PV_s00f1_2340(10)
  virtual char Get(unsigned a, unsigned b, void* out);   // +0x2c
};
struct EObj {                        // message source / property objects
  PV_s00f1_2340(0) PV_s00f1_2340(1) PV_s00f1_2340(2) PV_s00f1_2340(3)
  virtual EObj* Child();                      // +0x10
  PV_s00f1_2340(5) PV_s00f1_2340(6)
  virtual unsigned GetType();                 // +0x1c
  PV_s00f1_2340(8) PV_s00f1_2340(9) PV_s00f1_2340(10) PV_s00f1_2340(11) PV_s00f1_2340(12) PV_s00f1_2340(13)
  virtual float* GetRect();                   // +0x38
  PV_s00f1_2340(15) PV_s00f1_2340(16) PV_s00f1_2340(17) PV_s00f1_2340(18) PV_s00f1_2340(19) PV_s00f1_2340(20) PV_s00f1_2340(21) PV_s00f1_2340(22) PV_s00f1_2340(23) PV_s00f1_2340(24)
  PV_s00f1_2340(25) PV_s00f1_2340(26) PV_s00f1_2340(27) PV_s00f1_2340(28) PV_s00f1_2340(29) PV_s00f1_2340(30) PV_s00f1_2340(31) PV_s00f1_2340(32) PV_s00f1_2340(33) PV_s00f1_2340(34)
  PV_s00f1_2340(35) PV_s00f1_2340(36) PV_s00f1_2340(37) PV_s00f1_2340(38) PV_s00f1_2340(39) PV_s00f1_2340(40) PV_s00f1_2340(41) PV_s00f1_2340(42) PV_s00f1_2340(43) PV_s00f1_2340(44)
  virtual EObj* GetByType(unsigned id);       // +0xb4
  PV_s00f1_2340(46) PV_s00f1_2340(47)
  virtual void vc0(float* out, float a, float b);   // +0xc0
};
struct WinObj8 {                     // a window with the +0xb8 slot
  PV_s00f1_2340(0) PV_s00f1_2340(1) PV_s00f1_2340(2) PV_s00f1_2340(3) PV_s00f1_2340(4) PV_s00f1_2340(5) PV_s00f1_2340(6) PV_s00f1_2340(7) PV_s00f1_2340(8) PV_s00f1_2340(9)
  PV_s00f1_2340(10) PV_s00f1_2340(11) PV_s00f1_2340(12) PV_s00f1_2340(13) PV_s00f1_2340(14) PV_s00f1_2340(15) PV_s00f1_2340(16) PV_s00f1_2340(17) PV_s00f1_2340(18) PV_s00f1_2340(19)
  PV_s00f1_2340(20) PV_s00f1_2340(21) PV_s00f1_2340(22) PV_s00f1_2340(23) PV_s00f1_2340(24) PV_s00f1_2340(25) PV_s00f1_2340(26) PV_s00f1_2340(27) PV_s00f1_2340(28) PV_s00f1_2340(29)
  PV_s00f1_2340(30) PV_s00f1_2340(31) PV_s00f1_2340(32) PV_s00f1_2340(33) PV_s00f1_2340(34) PV_s00f1_2340(35) PV_s00f1_2340(36) PV_s00f1_2340(37) PV_s00f1_2340(38) PV_s00f1_2340(39)
  PV_s00f1_2340(40) PV_s00f1_2340(41) PV_s00f1_2340(42) PV_s00f1_2340(43) PV_s00f1_2340(44) PV_s00f1_2340(45)
  virtual void SetKey(unsigned id, void* p);  // +0xb8
};
struct PLayout {                     // cSPUIPropertyLayout
  PV_s00f1_2340(0) PV_s00f1_2340(1) PV_s00f1_2340(2) PV_s00f1_2340(3) PV_s00f1_2340(4) PV_s00f1_2340(5) PV_s00f1_2340(6) PV_s00f1_2340(7)
  virtual void v20();                         // +0x20
  void* GetRootWindow();                      // 0x828100
  void SetPositionAndOffset(float a, float b, float c, float d);  // 0x8283a0
  void SetItem(void* a, void* b, void* c, int d);  // 0x5ee480
  void SetMode(int mode);                     // 0x5ed320
  void Hide();                                // 0x5ed6c0
  void SetActive();                           // 0x599530
  void SetInactive();                         // 0x599560
  void ShowRolloverA(void* p);                // 0x599be0
  void ShowRolloverB(void* p);                // 0x599c10
};
struct Collect {
  char Lock(unsigned long long k);            // 0x596e10
  char Unlock(unsigned long long k, int a);   // 0x596da0
};
struct Slot14 { void m572620(void* p); };
struct EUI { PLayout* GetPropertyLayout(); };   // 0x113ae10
struct EdObj {
  void Init(void* v);                           // 0x61df40
};
// ---- items of slice s00f12340 end

// ---- items of slice s00f13330 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char* g_pMagic;                 // 0x016c7aa4
extern "C" void  operator_delete(void*);   // 0x00f47380
extern "C" void  EA_Messaging_RemoveHandler(void*, void*, void*, void*, void*); // 0x00571db0
extern "C" void* __fastcall FUN_00e0a390(void*);  // 0x00e0a390  ctor helper on obj+8 (thiscall)
extern "C" void  __fastcall FUN_00e0a400(void*);  // 0x00e0a400  dtor helper on obj+8 (thiscall)
extern "C" void  FUN_00e0a4c0(void*, void*, void*); // 0x00e0a4c0 (self, arg)
extern "C" void* __fastcall eastl_vector_dtor(void*);  // 0x005c7f10  vector<...>::~vector (thiscall)
extern "C" void  FUN_00eadb10(void*, int);   // 0x00eadb10
extern "C" void  FUN_00eed9c0(void*, void*); // 0x00eed9c0
extern "C" void  FUN_00eeda20(void*, void*); // 0x00eeda20
extern "C" void* FUN_0067cb30();             // 0x0067cb30
extern "C" void  FUN_00610cb0(void*, void*, void*); // 0x00610cb0  PostTxn0x18
extern "C" void  FUN_00f12a60(void*);        // 0x00f12a60
extern "C" void  FUN_00f12eb0();             // 0x00f12eb0
extern "C" void* FUN_00607a60();             // 0x00607a60  AuthManager
extern "C" void  FUN_00f46920(void*, void*);// 0x00f46920  cOnlineTab::Shutdown
extern "C" void* EA_ResourceMan_GetManager();  // 0x0067dcd0
extern "C" void  FUN_00f12700(void*, void*);// 0x00f12700
extern "C" void* FUN_00f46b50(void*);        // 0x00f46b50
extern "C" int   FUN_008105b0(void*, int, int); // 0x008105b0  cSPUILayout::FindWindowByID
extern "C" int   FUN_008120d0(void*, void*, int, int); // 0x008120d0  cSPUILayout::Init
extern "C" int   FUN_00810590(void*, int);   // 0x00810590  cSPUILayout::SetVisibility
extern "C" void  FUN_00806e40(void*, int, int); // 0x00806e40  SPUIHelpers::AutoSizeWindowForText
extern "C" void* FUN_00810000(void*);        // 0x00810000  cConnectionDialog ctor
extern "C" void* FUN_0054e530(void*, void*, void*, int); // 0x0054e530  GetServerId
extern "C" void* memmove(void*, const void*, unsigned int);  // msvcr90!memmove
typedef void  (__thiscall *FnV)(void*);
typedef void* (__thiscall *FnP)(void*);
typedef void* (__thiscall *FnPI)(void*, int);
typedef void* (__thiscall *FnPII)(void*, int, int);
typedef void  (__thiscall *FnVI)(void*, int);
typedef void  (__thiscall *FnVII)(void*, int, int);
extern "C" void* operator_new(uint32_t size, const char* name, int, int, const char*, int); // 0x00f473a0
extern "C" void* DoInsertValue(void*, void*, uint32_t);      // 0x011e0744
struct RewardUI {
    void*    mVtbl;        // +0x00
    void*    mVtbl04;      // +0x04
    void*    mVtbl08;      // +0x08
    uint32_t mField0c;     // +0x0c
    uint32_t mField10;     // +0x10
    uint32_t mField14;     // +0x14
    uint32_t mField18;     // +0x18
    uint32_t mField1c;     // +0x1c
    uint32_t mField20;     // +0x20
    uint32_t mField24;     // +0x24
    uint32_t mField28;     // +0x28
    uint32_t mField2c;     // +0x2c
    uint8_t  mField30[0x70]; // +0x30 .. +0x9f  embedded content-validation summarizer
    uint32_t mFielda0;     // +0xa0
    uint32_t mFielda4;     // +0xa4
    uint32_t mFielda8;     // +0xa8
    uint32_t mFieldac;     // +0xac
    uint32_t mFieldb0;     // +0xb0
    uint32_t mFieldb4;     // +0xb4
    uint32_t mFieldb8;     // +0xb8
    float    mFbc;         // +0xbc
    float    mFc0;         // +0xc0
    float    mFc4;         // +0xc4
    float    mFc8;         // +0xc8
    float    mFcc;         // +0xcc
    uint32_t mFieldd0;     // +0xd0
    uint32_t mFieldd4;     // +0xd4
    uint32_t mFieldd8;     // +0xd8
    uint32_t mFielddc;     // +0xdc
    uint32_t mFielde0;     // +0xe0
    uint32_t mFielde4;     // +0xe4
    uint32_t mFielde8;     // +0xe8
    uint32_t mFieldec;     // +0xec
    uint32_t mFieldf0;     // +0xf0
    uint32_t mFieldf4;     // +0xf4

    int  FUN_00f133d0(uint32_t, int*);
    void FUN_00f139f0();
};
// ---- items of slice s00f13330 end

// ---- items of slice s00f145a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  EADelete(void* p);                                                        // 0x00f47380
extern "C" void* memcpy_(void* dst, const void* src, uint32_t n);                          // 0x011e0744
extern "C" void* do_copy(void* first, void* last, void* result);                           // 0x0062ffd0
extern "C" void* uninit_copy(void* out, void* first, void* last, void* dst, void* extra);  // 0x01022c60
extern "C" void  SetNumberString(int lo, int hi, wchar_t* buf, int n);                     // 0x00881ae0
extern "C" void* GetSingleton();                                                           // 0x0067de40
typedef int   (__thiscall *FnII)(void*, int);
class cString {
public:
    uint32_t mData[5];
    cString(uint32_t tableID, uint32_t instanceID, const wchar_t* source);  // 0x006b5770
    ~cString();                                                             // 0x006b5240
    const wchar_t* GetText() const;                                         // 0x006b55c0
};
struct TextZoomName {
    TextZoomName* Init();                                                // 0x008345c0
    void Shutdown();                                                     // 0x00834e30
    void Setup(int r, int a, void* win, int b, int s0, int s1, int s2);  // 0x00834fa0
};
struct Vec12 {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    Vec12* assign(const Vec12* src);                    // 0x00f145a0
    void*  DoAllocate(int n, void* first, void* last);  // 0x00f137b0
    void   DoDestroy(void* first, void* last);          // 0x00ae6710
    void*  Allocate(int n, void* alloc);                // 0x00b93c60
};
struct VecF {
    void* mpBegin; void* mpEnd; void* mpCapacity; void* mAlloc;
    void* Allocate(int n, void* alloc);   // 0x004aa350
    VecF* operator=(const VecF& src);     // 0x0050d4e0
};
struct Tail5 { int v0, v1, v2, v3, v4; };
struct Rec70 {
    void* mpVtbl;   // +0x00
    void* mRef4;    // +0x04  AutoRefCount
    void* mRef8;    // +0x08  AutoRefCount
    int   mField0c; // +0x0c
    int   mField10; // +0x10
    int   mField14; // +0x14
    Vec12 mVec18;   // +0x18  (+0x24 allocator)
    int   mAlloc24; // +0x24
    int   mField28; // +0x28
    int   mField2c; // +0x2c
    VecF  mVec30;   // +0x30  (+0x3c allocator)
    int   mField40; // +0x40
    float mF44, mF48, mF4c, mF50, mF54, mF58;  // +0x44 .. +0x58
    Tail5 mTail;                               // +0x5c .. +0x6c
    Rec70* CopyFrom(const Rec70& src);   // 0x00f14690
    Rec70* operator=(const Rec70& src);  // 0x00f147e0
};
struct Layout {
    void* FindWindowByID(int id, int flag);  // 0x008105b0
};
struct Sub8 {
    void  Clear();      // 0x00e0a640
    int   Check(int);   // 0x00e0a800
    int   Count();      // 0x00e09c80
    void* At(int);      // 0x00e09c90
};
struct Vec78 {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    void  DoInsertValue(void* pos, void* value);  // 0x00f14270
    void* Erase(void* first, void* last);         // 0x005c2170
};
struct RecV {
    int   f00;   // +0x00
    int   f04;   // +0x04
    int   f08;   // +0x08
    int   f0c;   // +0x0c
    int   f10;   // +0x10
    int   f14;   // +0x14
    int   f18;   // +0x18
    int   f1c;   // +0x1c
    int   f20;   // +0x20
    int   f24;   // +0x24
    int   f28;   // +0x28
    int   f2c;   // +0x2c
    int   f30;   // +0x30
    int   f34;   // +0x34
    int   f38;   // +0x38
    float f3c;   // +0x3c
    float f40;   // +0x40
    float f44;   // +0x44
};
struct Owner {
    void Reset();                                                     // 0x00f14980
    void Setup(const wchar_t* text, int flag, uint32_t id);           // 0x00f149d0
    void SetLocalized(int value, const cString& name, uint32_t id);   // 0x00f14b30
    void SetPlain(int seconds, uint32_t id);                          // 0x00f14ba0
    void Update(const RecV& rec);                                     // 0x00f14d90
};
// ---- items of slice s00f145a0 end

// ---- items of slice s00f15890 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int size);
extern void* gSporeApp;                                     // 0x016c7aa4
typedef unsigned int uint;
typedef long long int64;
struct PartHolder {
    char pad00[8];
    struct Part { void Destroy(); } mPart;                  // +0x08, 0x00e0a5c0
    void ReleaseParts();                                    // 0x00f14980
    void Cleanup();                                         // 0x00f16260
};
struct ListNode {
    ListNode* mpNext;                                       // +0x00
    int       mPad;                                         // +0x04
    int64     mValue;                                       // +0x08
};
struct ListIterator {
    ListNode* mpNode;
    ListIterator& operator++()      { mpNode = mpNode->mpNext; return *this; }
    int64&        operator*() const { return mpNode->mValue; }
    bool operator==(const ListIterator& other) const { return mpNode == other.mpNode; }
};
inline int64* CopyRange64(const int64* first, const int64* last, int64* dst)
{
    memcpy(dst, first, (uint)((const char*)last - (const char*)first));
    return dst + (last - first);
}
struct Int64ListVector {
    int64* mpBegin;                                         // +0x00
    int64* mpEnd;                                           // +0x04
    int64* mpCapacity;                                      // +0x08

    void InsertList(int64* pos, ListIterator first, ListIterator last, ListIterator first2); // 0x00f143c0
    void AssignFromList(ListIterator first, ListIterator last, int tag);   // 0x00f16280
};
struct Element {
    Element(const Element* other);                          // 0x00f14690
    virtual void Destroy(int flags);                        // +0x00
    void DestroySelf();                                     // 0x00e0a400
    int mData[0x1b];
};
struct BlockHeader {
    unsigned int mSize;
};
Element* MoveElements(Element* first, Element* last, Element* dst);          // 0x00f14900
Element* CopyConstructRange(Element* first, Element* last, Element* dst);    // 0x00f148c0
Element* DestroyRange(Element* first, Element* last, Element* dst);          // 0x00f120e0
Element* CopyConstructBackward(Element* first, Element* last, Element* dstEnd); // 0x00f14940
Element** CopyConstructSaved(Element** result, Element* first, Element* last,
                             Element* dst);                                  // 0x00f147a0
void     FillUninitialized(Element* dst, unsigned int n, const Element* value); // 0x00f16230
void     FillAssigned(Element* first, Element* last, const Element* value);  // 0x00f16300
void     FreeRawBlock(void* block);                                          // 0x00f47380
void* operator new(unsigned int size, const char* name, int flags, int align,
                   const char* file, int line);
inline void* AllocElementBlock(unsigned int size, int line)
{
    return ::operator new(size, "Simulator", 0, 0, "EASTL/allocator.h", line);
}
struct ElementVector {
    Element* mpBegin;                                       // +0x00
    Element* mpEnd;                                         // +0x04
    Element* mpCapacity;                                    // +0x08

    Element* EraseRange(Element* last, Element* pos);       // 0x00f16330
    void     InsertN(Element* position, unsigned int n, const Element* value); // 0x00f16390
};
struct IWindow {
    virtual void AddRef() = 0;                                  // +0x00  (slot 0)
    virtual void Release() = 0;                                 // +0x04  (slot 1)
    virtual void s02() = 0; virtual void s03() = 0; virtual void s04() = 0; virtual void s05() = 0;
    virtual void s06() = 0; virtual void s07() = 0; virtual void s08() = 0;
    virtual bool GetTag(void** out, unsigned int id) = 0;       // +0x24  (slot 9)
    virtual void s10() = 0; virtual void s11() = 0; virtual void s12() = 0; virtual void s13() = 0;
    virtual const float* GetVertex() = 0;                       // +0x38  (slot 14)
    virtual void s15() = 0; virtual void s16() = 0; virtual void s17() = 0; virtual void s18() = 0;
    virtual void s19() = 0; virtual void s20() = 0; virtual void s21() = 0; virtual void s22() = 0;
    virtual void s23() = 0; virtual void s24() = 0; virtual void s25() = 0; virtual void s26() = 0;
    virtual void SetVertex(const float* v) = 0;                 // +0x6c  (slot 27)
    virtual void s28() = 0; virtual void s29() = 0; virtual void s30() = 0;
    virtual void SetVisible(int visible, int state) = 0;        // +0x7c  (slot 31)
    virtual void SetText(const wchar_t* text) = 0;              // +0x80  (slot 32)
    virtual void s33() = 0; virtual void s34() = 0; virtual void s35() = 0; virtual void s36() = 0;
    virtual void s37() = 0; virtual void s38() = 0; virtual void s39() = 0; virtual void s40() = 0;
    virtual void s41() = 0; virtual void s42() = 0; virtual void s43() = 0; virtual void s44() = 0;
    virtual void s45() = 0; virtual void s46() = 0; virtual void s47() = 0; virtual void s48() = 0;
    virtual void s49() = 0; virtual void s50() = 0; virtual void s51() = 0; virtual void s52() = 0;
    virtual void s53() = 0; virtual void s54() = 0; virtual void s55() = 0; virtual void s56() = 0;
    virtual void s57() = 0; virtual void s58() = 0; virtual void s59() = 0;
    virtual IWindow* FindChild(unsigned int id, int flag) = 0;  // +0xf0  (slot 60)
};
struct IWindowManager {
    virtual void w00() = 0; virtual void w01() = 0; virtual void w02() = 0; virtual void w03() = 0;
    virtual void w04() = 0; virtual void w05() = 0; virtual void w06() = 0; virtual void w07() = 0;
    virtual void w08() = 0; virtual void w09() = 0; virtual void w10() = 0; virtual void w11() = 0;
    virtual void w12() = 0; virtual void w13() = 0; virtual void w14() = 0; virtual void w15() = 0;
    virtual void w16() = 0; virtual void w17() = 0;
    virtual void ShowWindow(int mode, IWindow* window) = 0;     // +0x4c  (slot 19)
};
struct cSPUILayout_s00f1_5890 {
    IWindow* FindWindowByID(unsigned int id);                   // 0x008105b0
    IWindow* FindWindowByID(unsigned int id, int flag);         // 0x008105b0
};
struct cCreatureInfo {
    char           mPad00[0x54];    // +0x00
    const wchar_t* mpText54;        // +0x54  label text handed to the window (slot 0x80)
    char        mPad58[0x38];       // +0x58
    int         mState90;           // +0x90  compared with 5 (path finished)
    int  Count();                   // 0x00f191a0
    int  ElapsedMs();               // 0x00f19190
    float Ratio();                  // 0x00f19d10  (x87 float return)
};
template <class T> struct AutoRefCount_s00f1_5890 {
    T* mpObject;                                            // +0x00
    void Assign(T* p)
    {
        if (p != mpObject) {
            if (p)
                p->AddRef();
            T* old = mpObject;
            mpObject = p;
            if (old)
                old->Release();
        }
    }
};
struct cPathFollower {                                      // the object at +0x28
    void SetTarget(void* target);                           // 0x00f14d90
};
struct cPathStepper {                                       // the object at +0x20
    void Step(int a, int b, int c);                          // 0x00f46cf0
};
struct cSPCreatureBase {
    char                       mPad00[0x10];                // +0x00
    cCreatureInfo*             mpInfo;                      // +0x10
    cSPUILayout_s00f1_5890*               mpLayout;                    // +0x18
    char                       mPad1c[4];                   // +0x1c
    cPathStepper*              mpStepper;                   // +0x20
    char                       mPad24[4];                   // +0x24
    cPathFollower              mFollower;                   // +0x28
    char                       mPad2c[0x8c];                // +0x2c
    void*                      mpDataB8;                    // +0xb8  tagged data object (vtable +0x24)
    float                      mBc;                         // +0xbc
    float                      mC0;                         // +0xc0
    float                      mC4;                         // +0xc4
    float                      mC8;                         // +0xc8
    float                      mCc;                         // +0xcc
    int                        mD0;                         // +0xd0
    AutoRefCount_s00f1_5890<IWindow>      mWndDc;                      // +0xdc
    AutoRefCount_s00f1_5890<IWindow>      mWndE0;                      // +0xe0

    void OnPathCompleted();                                 // 0x00f15890
};
IWindowManager* __cdecl WindowManager();                                 // 0x0067caa0
int*   __cdecl EA_Hash_FNV1_String8();                                   // 0x0041e990
int    __cdecl FUN_00eec540(int key);                                    // 0x00eec540
int    __cdecl FUN_00eec580(int value);                                  // 0x00eec580
int    __cdecl FUN_00eec570();                                           // 0x00eec570
float  __cdecl FUN_00eec5b0();                                           // 0x00eec5b0
bool   __cdecl FUN_00552450(void* owner, void** out);                    // 0x00552450
void*  __cdecl FUN_005507a0(void* handle);                               // 0x005507a0
bool   __cdecl FUN_00f19640();                                           // 0x00f19640
void   __cdecl FUN_00f39110(void* out);                                  // 0x00f39110
void   __cdecl FUN_00f14d90(cPathFollower* self, void* target);          // 0x00f14d90
void   __cdecl FUN_00f46cf0(cPathStepper* self, int a, int b, int c);    // 0x00f46cf0
void*  __cdecl FUN_00f3bcb0(void* owner);                                // 0x00f3bcb0
bool   __cdecl FUN_00f3cb60(void* owner);                                // 0x00f3cb60
void*  __cdecl FUN_008dc790(cCreatureInfo* self);                        // 0x008dc790
void*  __cdecl FUN_00675250(unsigned int id, int flag);                  // 0x00675250
void   __cdecl FUN_00676e90(void* controller);                           // 0x00676e90
void*  __cdecl FUN_0067cb30(void* owner);                                // 0x0067cb30
void   __cdecl FUN_0060e600(void* owner, const long long* values, int n); // 0x0060e600
void   __cdecl FUN_00806a60(IWindow* w);                                 // 0x00806a60
void   __cdecl SetNumberString(wchar_t* buf, int size, long long value);  // 0x00881ae0
void   __cdecl SetNumberStringReal(double value, int size, wchar_t* buf, int flag); // 0x00881f00
struct cLocalizedText {
    cLocalizedText(unsigned int table, unsigned int id, int flags);  // 0x006b5770
    ~cLocalizedText();                                               // 0x006b5240
    const wchar_t* c_str();                                          // 0x006b55c0
    char mData[0x1c];
};
struct cStringRef {
    const wchar_t* c_str();                                          // 0x006b55c0
    int mTableId;                                                    // +0x00
};
struct cTimeStrings {
    int         mKind;                                               // +0x00
    cStringRef  mOuter;                                              // +0x04
    int         mPad08;                                              // +0x08
    cStringRef  mInner;                                              // +0x0c
};
struct cString_s00f1_5890 {
    cString_s00f1_5890() {}                                                     // no constructor call in the original
    cString_s00f1_5890(int value);                                              // 0x006b55c0
    cString_s00f1_5890(unsigned int key, unsigned int id, int flag);             // 0x006b5770
    ~cString_s00f1_5890();                                                      // 0x006b5240
    const wchar_t* Data() const { return mpData; }
    int            mTableId;                                        // +0x00
    wchar_t*       mpData;                                          // +0x04
    int            mLength;                                         // +0x08
    int            mCapacity;                                       // +0x0c
    wchar_t        mInline[6];                                      // +0x10 (inline buffer)
};
cString_s00f1_5890* __cdecl FormatString(cString_s00f1_5890* out, const wchar_t* fmt, ...);    // 0x00f14120
// ---- items of slice s00f15890 end

// ---- items of slice s00f16580 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void operator_delete_array(void* p);       // 0x00f47380 (operator delete[])
inline void* operator new(unsigned int, void* p) { return p; }
namespace eastl {
class allocator_s00f1_6580 { public: allocator_s00f1_6580() {} };
}
namespace eastl {
struct bidirectional_iterator_tag { bidirectional_iterator_tag() {} };
}
namespace eastl {
extern wchar_t gEmptyString16[2];                     // 0x01667bac
}
namespace eastl {
struct string16_s00f1_6580
{
    wchar_t*  mpBegin;
    wchar_t*  mpEnd;
    wchar_t*  mpCapacity;
    allocator_s00f1_6580 mAllocator;

    string16_s00f1_6580()
    {
        mpBegin = gEmptyString16;
        mpEnd = gEmptyString16;
        mpCapacity = gEmptyString16 + 1;
    }
    ~string16_s00f1_6580() { DeallocateSelf(); }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator_delete_array(mpBegin);
    }
};
}
namespace eastl {
template <typename T>
struct ListNode_s00f1_6580
{
    ListNode_s00f1_6580* mpNext;
    ListNode_s00f1_6580* mpPrev;
    T         mValue;
};
}
namespace eastl {
template <typename T>
struct list_iterator
{
    ListNode_s00f1_6580<T>* mpNode;
    list_iterator(ListNode_s00f1_6580<T>* p) : mpNode(p) {}
};
}
namespace eastl {
template <typename T>
class list_s00f1_6580
{ public:
    ListNode_s00f1_6580<T>* mpNext;    // anchor
    ListNode_s00f1_6580<T>* mpPrev;
    unsigned int mSize;
    list_iterator<T> begin() { return list_iterator<T>(mpNext); }
    list_iterator<T> end() { return list_iterator<T>((ListNode_s00f1_6580<T>*)this); }
};
}
namespace eastl {
template <unsigned int size, unsigned int alignment>
struct aligned_buffer { __declspec(align(8)) char buffer[size]; };
}
namespace eastl {
class fixed_vector_allocator
{ public:
    allocator_s00f1_6580 mOverflowAllocator;
    void*     mpPoolBegin;
};
}
namespace eastl {
struct fixed_vector_int64_32
{
    int64_t*               mpBegin;
    int64_t*               mpEnd;
    int64_t*               mpCapacity;
    fixed_vector_allocator mAllocator;
    aligned_buffer<32 * sizeof(int64_t), 8> mBuffer;

    fixed_vector_int64_32()
    {
        mpBegin = (int64_t*)mBuffer.buffer;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 32;
        mAllocator.mpPoolBegin = mpBegin;
    }
    ~fixed_vector_int64_32()
    {
        if (mpBegin && mpBegin != mAllocator.mpPoolBegin)
            operator_delete_array(mpBegin);
    }

    int64_t* data() { return mpBegin; }
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }

    void push_back(const int64_t& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) int64_t(value);
        else
            DoInsertValue(mpEnd, value);
    }

    template <typename T>
    void assign(list_iterator<T> first, list_iterator<T> last)
    {
        DoAssignFromIterator(first, last, bidirectional_iterator_tag());
    }

    void DoInsertValue(int64_t* position, const int64_t& value);   // 0x00f14140
    void DoAssignFromIterator(list_iterator<int64_t> first, list_iterator<int64_t> last,
                              bidirectional_iterator_tag);        // 0x00f16280
};
}
namespace eastl {
template <typename T>
struct intrusive_ptr
{
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr()
    {
        if (mpObject)
            mpObject->Release();
    }
    T* get() const { return mpObject; }
    intrusive_ptr& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
}
namespace EA {
struct Variant_s00f1_6580
{
    uint32_t       mData[4];
    unsigned short mFlags;   // +0x10
    unsigned short mTypeId;  // +0x12
    Variant_s00f1_6580() : mFlags(0), mTypeId(0) {}
    ~Variant_s00f1_6580()
    {
        if (mFlags & 4)
            Destruct(0);  // 0x0093db80 (EA::Variant::Destruct)
    }
    void Destruct(int);                                                   // EA::Variant::Destruct 0x0093db80
    Variant_s00f1_6580& operator=(const int& v);                                     // EA::Variant::operator=<int> 0x00422eb0
    void Set(int type, int flags, const void* data, int elemSize, int count);  // EA::Variant::Set 0x0093dd80
};  // namespace EA
}
struct ResourceKey_s00f1_6580 { uint32_t mInstance, mType, mGroup; };
struct Property
{
    uint32_t       pad_00[0x12 / 4];
    unsigned short pad_10;
    unsigned short mType;    // +0x12
    int* GetInt();           // Property::GetInt 0x0041e990
};
namespace App {
class PropertyList
{
public:
    virtual void AddRef();
    virtual void Release();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void SetProperty(uint32_t id, const EA::Variant_s00f1_6580& value);   // +0x14
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& result);         // +0x24
};
}
namespace App {
class IMessageManager
{
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void PostMSG(uint32_t messageID, void* pMessage, void* pListener);   // +0x14
};
}
namespace App {
IMessageManager* MessageServer();                                   // SP::MessageServer 0x0067dcc0
}
namespace SP {
namespace Achievements {
class Controller
{
public:
    void AwardAchievement(uint32_t id);                             // 0x00676710
};
}
}
namespace SP {
Achievements::Controller* AchievementsController();                // 0x00675250
}
namespace SP {
class cPollinator_s00f1_6580
{ public:
    void UpdateProperty2(uint32_t id, const ResourceKey_s00f1_6580* key, EA::Variant_s00f1_6580* v);                 // 0x0060d920
    void UpdatePropertyInt(uint32_t id, const ResourceKey_s00f1_6580* key, uint32_t a, uint32_t b);       // 0x0060e600
};
}
namespace SP {
cPollinator_s00f1_6580* GetPollinator();                                       // 0x0067cb30
}
namespace Simulator {
struct cScenarioPlaySummary
{
    int   mNumCreaturesKilled;        // +0x00
    int   mNumBuildingsDestroyed;     // +0x04
    int   mNumVehiclesDestroyed;      // +0x08
    int   mNumCastMembersDefended;    // +0x0c
    int   mNumCreaturesBefriended;    // +0x10
    int   mNumObjectsCollected;       // +0x14
    int   field_18;                   // +0x18
    int   mNumGoalsCompleted;         // +0x1c
    int   mNumDeaths;                 // +0x20
    int   mNumPosseMembersLost;       // +0x24
    int   mAmountDamageDealt;         // +0x28
    int   mNumTimesUsedJetPack;       // +0x2c
    int   mNumTimesUsedSprint;        // +0x30
    int   mNumBarrelsDestroyed;       // +0x34
    int   mNumCastMembersTalkedTo;    // +0x38
    float mAmountHealthRegained;      // +0x3c
    float mAmountDamageReceived;      // +0x40
    float mAmountEnergyUsed;          // +0x44
};
}
namespace Simulator {
struct cScenarioPlayMode
{
    uint32_t pad_000[0x90 / 4];
    int      mCurrentPlayModeState;   // +0x90

    cScenarioPlaySummary* GetSummary();   // 0x008dc790 (lea eax,[ecx+0xc]; COMDAT-folded)
    int GetElapsedTimeMS();               // 0x00f19190 (name guessed)
};
}
namespace Simulator {
struct cCollectableItems
{
    virtual void v00();
    virtual void Release();               // +0x04 (as released by the conditional temporary)
    void AddRef();
    void Refresh(int flags);                          // 0x005970d0 (name guessed)
    eastl::list_s00f1_6580<int64_t>& GetUnlockedItems();          // 0x005939a0 (lea eax,[ecx+0x6d80])
};
}
namespace Simulator {
struct cPlayerData                        // what the holder points to at +0x14 (name guessed)
{
    uint32_t pad_000[0x10 / 4];
    eastl::intrusive_ptr<cCollectableItems> mpCollectableItems;  // +0x10
};
}
namespace Simulator {
struct cPendingObject
{
    virtual void v00();
    virtual void v04();
    virtual void Release();               // +0x08
    void AddRef();
};
}
namespace Simulator {
struct cCollectablesHolder                // the object at owner+0x24 (name guessed)
{
    uint32_t     pad_000[0x14 / 4];
    cPlayerData* mpPlayerData;                                     // +0x14
    uint32_t     pad_018[(0x20 - 0x18) / 4];
    eastl::intrusive_ptr<cPendingObject> mpPending;                // +0x20
    void Update();                        // 0x00f12340 (name guessed)
};
}
struct cScenarioData                      // g_ScenarioManager->+0x74 (name guessed)
{
    uint32_t pad_000[0x10 / 4];
    struct cScenarioResource* mpResource;      // +0x10
    const ResourceKey_s00f1_6580* GetKey();               // 0x00f3bcb0 (return &mpResource->+0x130)
};
struct cScenarioResource { uint32_t pad_000[2]; uint32_t mHeader[1]; };   // +0x08 passed below
struct cScenarioManager { uint32_t pad_000[0x74 / 4]; cScenarioData* mpData; };
extern cScenarioManager* g_ScenarioManager;   // 0x016c7aa4
void RecordPlayedAdventure(App::PropertyList* list_s00f1_6580, const uint32_t* header);   // 0x00eef330 (name guessed)
int  FindFirstGE(int points);                                                  // 0x00eec540
int  AddToIntProperty(App::PropertyList* list_s00f1_6580, uint32_t id, int delta);        // 0x005bf470
void SaveCollectableItems(App::PropertyList* list_s00f1_6580, Simulator::cCollectableItems* items);    // 0x005bf610
bool SaveEditorPropertyList(const ResourceKey_s00f1_6580* key, App::PropertyList* list_s00f1_6580, int flags, void* db);  // 0x005bf120
void GetAdventureName(const ResourceKey_s00f1_6580* key, eastl::string16_s00f1_6580* out);           // 0x00eed920
inline int GetIntProperty(App::PropertyList* list_s00f1_6580, uint32_t id)
{
    int value = 0;
    Property* prop;
    if (list_s00f1_6580 && list_s00f1_6580->GetProperty(id, prop) && prop->mType == 9)
        value = *prop->GetInt();
    return value;
}
class cScenarioResultsRecorder
{
public:
    uint32_t                        pad_000[0x10 / 4];
    Simulator::cScenarioPlayMode*   mpPlayMode;    // +0x10
    uint32_t                        pad_014[(0x24 - 0x14) / 4];
    Simulator::cCollectablesHolder* mpHolder;      // +0x24
    uint32_t                        pad_028[(0xb8 - 0x28) / 4];
    App::PropertyList*              mpPlayerProps; // +0xb8
    uint32_t                        pad_0bc[(0xc8 - 0xbc) / 4];
    float                           mPoints;       // +0xc8

    void RecordResults(bool finished);
};
#define PAL_V4(a) virtual void a##0(); virtual void a##1(); virtual void a##2(); virtual void a##3();
struct cPaletteRef8 {                       // Release is vtable slot 2
virtual void v00();
virtual void v04();
    virtual void Release();                 // +0x08
};
class cSPPalette_s00f1_6580 {                          // SP::cSPPalette
public:
virtual void v00();
virtual void v04();
    virtual void Release();                 // +0x08
    void Shutdown();                        // 0x005c5c20
};
class cSPPaletteCategoryUI_s00f1_6580 {                 // SP::cSPPaletteCategoryUI_s005c_4500
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual void Release();                 // +0x0c
    void Shutdown();                        // 0x005c4e40
};
class cPaletteListener {                    // detaches through slot 0x108
public:
virtual void v00();
virtual void Release();
virtual void v08();
virtual void v0c();
    PAL_V4(x10) PAL_V4(x20) PAL_V4(x30) PAL_V4(x40) PAL_V4(x50) PAL_V4(x60) PAL_V4(x70)
    PAL_V4(x80) PAL_V4(x90) PAL_V4(xa0) PAL_V4(xb0) PAL_V4(xc0) PAL_V4(xd0) PAL_V4(xe0) PAL_V4(xf0)
virtual void v100();
virtual void v104();
    virtual void Detach(void* owner);       // +0x108
};
class cPaletteChain {                       // the helper held at +0x38
public:
virtual void v00();
virtual void Release();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual void Build();                   // +0x24
};
class cPaletteManager {
public:
virtual void v00();
virtual void v04();
    virtual void Reset(uint32_t tag);       // +0x08
};
cPaletteManager* __cdecl FUN_0067ca90();    // 0x0067ca90
namespace EA {
namespace Messaging {
void __cdecl RemoveHandler(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);   // 0x00571db0
}
}
template <class T> struct PaletteRef {
    T* mp;
    __forceinline void reset() { if (mp) { T* p = mp; mp = 0; p->Release(); } }
    __forceinline T* operator->() const { return mp; }
};
struct PaletteElementVector {               // the vector at +0x24
    void*    mpBegin;                       // +0x24
    void*    mpEnd;                         // +0x28
    void*    mpCapacity;                    // +0x2c
    uint32_t mAllocator;                    // +0x30
    uint32_t mPad34;                        // +0x34
    void EraseRange(void* first, void* last);   // 0x00f16330
};
class cScenarioPaletteOwner {
public:
    uint32_t mPad000[(0x0c - 0x00) / 4];                     // +0x00
    uint32_t mAttachOwner;                                   // +0x0c
    PaletteRef<cSPPalette_s00f1_6580>           mpPalette;              // +0x10
    PaletteRef<cPaletteRef8>         mp14;                   // +0x14
    PaletteRef<cSPPaletteCategoryUI_s00f1_6580> mpCategory;             // +0x18
    PaletteRef<cPaletteListener>     mpListener;             // +0x1c
    PaletteRef<cPaletteRef8>         mp20;                   // +0x20
    PaletteElementVector             mElements;              // +0x24
    PaletteRef<cPaletteChain>        mpChain;                // +0x38
    uint32_t mPad3c[(0x48 - 0x3c) / 4];                      // +0x3c
    uint32_t mHandler;                                       // +0x48
    uint32_t mHandlerIds[4];                                 // +0x4c
    void Shutdown();                                         // 0x00f16fd0
};
// ---- items of slice s00f16580 end

// ---- items of slice s00f170c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_slot15ad8a4;                               // 0x015ad8a4 global slot
extern uint32_t g_handlerIds15ad8e4[2];                      // 0x015ad8e4 handler message ids
extern char     g_16c7aa4[];                                 // 0x016c7aa4 globals struct
void* __cdecl operator new(unsigned int size, const char* tag, int a, int b, int c, int d);   // 0x00f473a0
void  __cdecl operator delete(void* p);                                                       // 0x00f47380
struct IWin_s00f1_70c0 {
	virtual void AddRef();                                   // +0x00
	virtual void Release();                                  // +0x04
	PV2 PV2 PV                                               // +0x08..+0x18
	virtual int GetWindowType();                             // +0x1c
	PV2                                                      // +0x20..+0x24
	virtual bool IsVisible();                                // +0x28
	PV2 PV                                                   // +0x2c..+0x34
	virtual void GetRect(int id);                            // +0x38
	PV8 PV8                                                  // +0x3c..+0x78
	virtual void SetVisible(int a, bool b);                  // +0x7c
	PV8 PV8 PV8 PV8 PV2 PV                                   // +0x80..+0x108
	virtual int GetOwnerId(int a);                           // +0x10c
};
struct IWinContainer {
	virtual void AddRef();                                   // +0x00
	virtual void Release();                                  // +0x04
	PV2 PV2 PV                                               // +0x08..+0x18
	virtual int GetWindowType();                             // +0x1c
	PV2                                                      // +0x20..+0x24
	virtual bool IsVisible();                                // +0x28
	PV2 PV                                                   // +0x2c..+0x34
	virtual void GetRect(int id);                            // +0x38
	PV8 PV8                                                  // +0x3c..+0x78
	virtual void SetVisible(int a, bool b);                  // +0x7c
	PV8 PV8 PV8 PV4                                          // +0x80..+0xec
	virtual IWin_s00f1_70c0* FindChildWindow(uint id, int a, int b);    // +0xf0
	PV2 PV2 PV                                               // +0xf4..+0x108
	virtual int GetOwnerId(int a);                           // +0x10c
};
struct LayoutObj {
	virtual void v0();                                       // +0x00
	virtual void v1();                                       // +0x04
	virtual void Release();                                  // +0x08
	void SetVisibility(int visible);                         // 0x00810590
	IWin_s00f1_70c0* FindWindowByID(uint id, int recurse);              // 0x008105b0
	bool IsVisible();                                        // 0x00810070
	void Shutdown(uint flags);                               // 0x00811ad0
};
struct IObj20 {
	virtual void v0();                                       // +0x00
	virtual void Release();                                  // +0x04
	bool Teardown();                                         // 0x00f46a40
};
struct IObjB4 {
	virtual void v0();                                       // +0x00
	virtual void Release();                                  // +0x04
	void Teardown();                                         // 0x00f128f0
	void FUN_00f12970();                                     // 0x00f12970
};
struct IHandler_s00f1_70c0 { PV8 };
struct IServer {
	PV4 PV
	virtual void Send(uint32_t id, int a, int b);            // +0x14
	PV2 PV
	virtual void AddHandler(IHandler_s00f1_70c0* h, uint32_t id);       // +0x24
};
IServer* MessageServer_s00f1_70c0();                                    // 0x0067dcc0
namespace EA {
namespace Messaging {
void RemoveHandler(IServer* server, IHandler_s00f1_70c0* h, uint32_t id, int prio, int flags);   // 0x00571db0
}
}
namespace EA {
namespace ResourceMan {
struct Key_s00f1_70c0 { uint32_t mData[4]; };                           // resource key (passed by reference)
}
}
struct Property_s00f1_70c0;
struct PropertyList_s00f1_70c0 {
	virtual void v0();                                       // +0x00
	virtual void Release();                                  // +0x04
	PV4 PV2 PV
	virtual bool GetPropertyByKey(uint32_t name, Property_s00f1_70c0** out);   // +0x24
	virtual Property_s00f1_70c0* GetProperty(uint32_t name);            // +0x28
};
struct Property_s00f1_70c0 {
	uint32_t mValue;                                         // +0x00
	uint32_t pad04[3];                                       // +0x04
	uint8_t mFlags;                                          // +0x10
	uint8_t pad11;                                           // +0x11
	uint16_t mType;                                          // +0x12
	uint8_t* GetBool();                                      // 0x0041e920
};
bool GetEditorPropertyList(const EA::ResourceMan::Key_s00f1_70c0& key, PropertyList_s00f1_70c0** out);   // 0x005bf0e0
bool LoadCollectableItems(PropertyList_s00f1_70c0* list, void** out);                         // 0x005bf1e0
void FUN_005970d0(int arg);                                                        // 0x005970d0
void* FUN_00556140(const EA::ResourceMan::Key_s00f1_70c0* key, uint32_t name);                // 0x00556140
void* FUN_00556140(const EA::ResourceMan::Key_s00f1_70c0* key, uint32_t name, void* parent);  // 0x00556140
void* FUN_00556440(void* node);                                                    // 0x00556440
void  FUN_00555e80(void* node, void* outVector);                                   // 0x00555e80
extern EA::ResourceMan::Key_s00f1_70c0 g_key15ad8a8;                    // 0x015ad8a8 palette key
struct Updater {
	int ResetSlots();                                        // 0x00ae8ea0 (CommHost::ResetSlots)
};
Updater* GetUpdater();                                       // 0x00b3d490
struct GameTimeManager {
	void DecPauseGate(uint32_t gate);                        // 0x00b32250
};
GameTimeManager* GameTimeManager();                          // 0x00b3d380
struct IWinContent { virtual void v0(); };
struct WinOwnerBase { virtual void v0(); };
struct WinOwner : WinOwnerBase, IWinContent {                // IWinContent lives at +0x04
	void Set(bool on);                                       // 0x00812d60
};
struct IWindowManager_s00f1_70c0 {
	virtual void v0();                                       // +0x00
	virtual IWinContent* GetActiveContent();                 // +0x04
	PV8 PV8 PV2                                              // +0x08..+0x48
	virtual void ContentSet(int a, IWin_s00f1_70c0* w);                 // +0x4c
};
IWindowManager_s00f1_70c0* WindowManager_s00f1_70c0();                             // 0x0067caa0
void SPUIHelpersEndModal(IWin_s00f1_70c0* win, int a, int b);           // 0x00809c50
struct IGlobalSlots {
	virtual void v0();                                       // +0x00
	virtual void Set(void* slot, int value);                 // +0x04
};
IGlobalSlots* GlobalSlots();                                 // 0x0067ca90
struct IAudioSystem {
	virtual void v0();                                       // +0x00
	PV8 PV8 PV8 PV
	virtual int GetSomething();                              // +0x20
};
IAudioSystem* EAAudioGetSystemAT();                          // 0x00a206f0
void  KillSetiEffects(uint32_t id, uint32_t value);          // 0x00435ed0
uint32_t GetRecorderState();                                 // 0x00435e90
bool  FUN_00f0e250(void* win);                               // 0x00f0e250 (window visibility test)
void  FUN_00e12f80(void* win, int value);                    // 0x00e12f80 (SetVisible wrapper)
void  FUN_00e12fc0(void* win, void* value);                  // 0x00e12fc0 (SetText wrapper)
bool  FUN_00806a60(void* win, void* layout, int a, int b);   // 0x00806a60
void* FUN_00eec570_s00f1_70c0();                                        // 0x00eec570
void  FUN_00f14120(void* out, const wchar_t* fmt, int a, void* b);  // 0x00f14120
struct cString_s00f1_70c0 {
	uint32_t mPad00;                                         // +0x00
	uint32_t mPad04;                                         // +0x04
	uint32_t mText;                                          // +0x08 (inline text pointer)
	uint32_t mPad0c;                                         // +0x0c
	uint32_t mPad10;                                         // +0x10
	void ctor(uint32_t tag, uint32_t id, const wchar_t* s);  // 0x006b5770
	const wchar_t* GetText();                                // 0x006b55c0
	void dtor();                                             // 0x006b5240
};
struct PaletteHolder {
	bool IsVisible();                                        // 0x005c2940
	IWin_s00f1_70c0* mpLayout;                                          // +0x18
};
struct IObj3 {
	virtual void v0();                                       // +0x00
	virtual void AddRef();                                   // +0x04
	virtual void Release();                                  // +0x08
};
struct SubA {
	uint32_t pad00;                                          // +0x00
	IObj3 mRef;                                              // +0x04 (Release at +0x08)
	uint32_t pad08[4];                                       // +0x08
	PaletteHolder* mpPalette;                                // +0x18
	uint32_t pad1c;                                          // +0x1c
	void* mpField20;                                         // +0x20
	void FUN_00f16fd0();                                     // 0x00f16fd0
	void FUN_00f126d0();                                     // 0x00f126d0
};
struct ListObj {
	void Reset();                                            // 0x00f14980
};
struct Obj30 {
	void Destroy();                                          // 0x00e0a5c0
};
struct Pair28 {
	ListObj mList;                                           // +0x00
	uint32_t pad04;                                          // +0x04
	Obj30 mObj;                                              // +0x08
};
struct PanelIface {
	uint32_t pad00;                                          // +0x00
	IObj3 mRef;                                              // +0x04 (Release at +0x08)
	uint32_t pad08[(0x90 - 8) / 4];                          // +0x08
	int mMode;                                               // +0x90
};
struct IUiEffect {
	virtual void AddRef();                                   // +0x00
	virtual void Release();                                  // +0x04
	virtual void v2();                                       // +0x08
	virtual void Stop(int a);                                // +0x0c
	PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV4 PV
	virtual void SetTarget(void* target);                    // +0x104
};
struct PanelPrimary { virtual void v0(); };
struct PanelHandlerBase : IHandler_s00f1_70c0 {
	virtual bool HandleMessage(uint msg, void* payload);
};
class cSPUIProgress : public PanelPrimary, public PanelHandlerBase {
public:
	uint32_t pad08[2];                                       // +0x08
	PanelIface* mpWindow;                                    // +0x10
	void* mpScenario;                                        // +0x14
	LayoutObj* mpLayout;                                     // +0x18
	IUiEffect* mpEffect;                                     // +0x1c
	IObj20* mpField20;                                       // +0x20
	SubA* mpSubA;                                            // +0x24
	Pair28 mPair28;                                          // +0x28
	uint32_t pad34[(0xb4 - 0x34) / 4];                       // +0x34
	IObjB4* mpFieldB4;                                       // +0xb4
	PropertyList_s00f1_70c0* mpPropList;                                // +0xb8
	float mTimer;                                            // +0xbc
	float mTimeC0;                                           // +0xc0
	uint32_t padC4;                                          // +0xc4
	float mTimeC8;                                           // +0xc8
	uint32_t padCc;                                          // +0xcc
	int mCountD0;                                            // +0xd0
	int mState;                                              // +0xd4
	int mState2;                                             // +0xd8
	IWinContainer* mpWinA;                                   // +0xdc
	IWinContainer* mpWinB;                                   // +0xe0
	IServer* mpServer;                                       // +0xe4
	IHandler_s00f1_70c0* mpHandler;                                     // +0xe8
	uint32_t mMsg;                                           // +0xec
	int mPrio;                                               // +0xf0
	int mFlags;                                              // +0xf4

	void FUN_00f12eb0();                                     // 0x00f12eb0 page/category switch

	void StartNextAnimation();                               // 0x00f17870
	void Shutdown();                                         // 0x00f17ea0

	bool DoMessage(uint32_t msg, int* data);                 // 0x00f170c0
	bool FUN_00f135b0(int a);                                // 0x00f135b0
	void FUN_00f16580(int a);                                // 0x00f16580
};
struct SimMessage {
	void* m_vtbl;                                            // +0x00
	long m_refCount;                                         // +0x04
	void* m_payload;                                         // +0x08
	uint32_t m_pad0c[9];                                     // +0x0c
	uint32_t m_field30;                                      // +0x30
	uint32_t m_pad34;                                        // +0x34
	uint32_t m_field38;                                      // +0x38
	uint32_t m_pad3c;                                        // +0x3c

	SimMessage* Construct()
	{
		m_field30 = 0;
		m_vtbl = (void*)0x013eb90c;                          // RefBaseA22 (base message)
		_InterlockedExchange(&m_refCount, 0);
		m_vtbl = (void*)0x013eb844;                          // concrete message vtable
		m_field38 = 0;
		return this;
	}
};
struct Item70 {
	uint32_t m_pad00[0x1c];                                  // +0x00
	Item70* Init();                                          // 0x00e0a390
	void Destroy();                                          // 0x00e0a400
};
struct cItemVector {
	Item70* m_begin;                                         // +0x00
	Item70* m_end;                                           // +0x04

	void Resize(uint count);                                 // 0x00f17a70
	void Insert(Item70* where, int count, Item70* src);      // 0x00f16390
	void Erase(Item70* first, Item70* last);                 // 0x00f16330
};
struct ISimItems {
	virtual void AddRef();                                   // +0x00
	virtual void Release();                                  // +0x04
};
struct cSPPaletteCategory_s00f1_70c0 {
	virtual void v0();                                       // +0x00
	virtual void v1();                                       // +0x04
	uint32_t pad08;                                          // +0x08
	int* m_begin;                                            // +0x0c
	int* m_end;                                              // +0x10
	uint32_t pad14[3];                                       // +0x14
	uint32_t mField20;                                       // +0x20
	uint32_t pad24[2];                                       // +0x24
	uint32_t mField2c;                                       // +0x2c
};
struct cSPPalette_s00f1_70c0 {
	virtual void v0();                                       // +0x00
	virtual void AddRef();                                   // +0x04
	virtual void Release();                                  // +0x08
	cSPPalette_s00f1_70c0* Construct();                                 // 0x005c5e30
	bool Init(const EA::ResourceMan::Key_s00f1_70c0& key, uint a, uint b, uint c, uint d, int e, int modelType);  // 0x005c6340
	cSPPaletteCategory_s00f1_70c0* GetCategory(int index);              // 0x005c5de0
};
struct cCategoryHolder {
	virtual void v0();                                       // +0x00
	virtual void AddRef();                                   // +0x04
	virtual void Release();                                  // +0x08
	uint32_t pad0c;                                          // +0x0c
	ISimItems* mpItems;                                      // +0x10
	uint32_t pad14[3];                                       // +0x14
	uint32_t mField20;                                       // +0x20
	uint32_t pad24[2];                                       // +0x24
	uint32_t mField2c;                                       // +0x2c
	cCategoryHolder* Construct();                            // 0x005c64e0
};
struct cPaletteCategoryUI {
	virtual void v0();                                       // +0x00
	virtual void v1();                                       // +0x04
	virtual void AddRef();                                   // +0x08
	virtual void Release();                                  // +0x0c
	cPaletteCategoryUI* Construct();                         // 0x005c3e00
};
struct cSpaceInventory {
	virtual void AddRef();                                   // +0x00
	virtual void Release();                                  // +0x04
	PV4 PV
	virtual void Setup();                                    // +0x1c
	void Init(uint a, uint b);                               // 0x00827fa0
	cSpaceInventory* Construct();                            // 0x005994d0
};
class cSimScreen {
public:
	uint32_t pad00[3];                                       // +0x00
	uint32_t mParam0c;                                       // +0x0c
	cSPPalette_s00f1_70c0* mpPalette;                                   // +0x10
	cCategoryHolder* mpCategory;                             // +0x14
	cPaletteCategoryUI* mpCategoryUI;                        // +0x18
	IUiEffect* mpEffect;                                     // +0x1c
	uint32_t pad20;                                          // +0x20
	cItemVector mItems;                                      // +0x24
	uint32_t pad2c[(0x38 - 0x2c) / 4];                       // +0x2c
	cSpaceInventory* mpInventory;                            // +0x38
	bool mShowCollectables;                                  // +0x3c
	uint8_t pad3d[3];                                        // +0x3d
	uint32_t mCollectableId;                                 // +0x40
	uint32_t pad44;                                          // +0x44
	IServer* mpServer;                                       // +0x48
	IHandler_s00f1_70c0* mpHandler;                                     // +0x4c
	uint32_t mMsg[2];                                        // +0x50
	int mPrio;                                               // +0x54
	int mFlags;                                              // +0x58

	void FUN_00f12eb0();                                     // 0x00f12eb0 page/category switch
	bool Init(IUiEffect* effect, const EA::ResourceMan::Key_s00f1_70c0& key);   // 0x00f17b00
};
// ---- items of slice s00f170c0 end

// ---- items of slice s00f17f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IWin_s00f1_7f70 {
    virtual void AddRef();                           // +0x00
    virtual void Release();                          // +0x04
    PV8 PV4
    virtual float* GetRect();                        // +0x38
    PV8 PV4
    virtual void SetRect(const float* rect);         // +0x6c
    virtual void SetPosition(float x, float y);      // +0x70
    virtual void SetSize(float w, float h);          // +0x74
    PV
    virtual void SetVisible(int a, bool b);          // +0x7c
    virtual void SetText(const wchar_t* text);       // +0x80
};
struct IWinContainer_s00f1_7f70 {
    uint pad04[0x8c / 4];                            // +0x04
    int  mMode;                                      // +0x90
    uint pad94[(0xf0 - 0x94) / 4];                   // +0x94
    virtual void AddRef();                           // +0x00
    virtual void Release();                          // +0x04
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV2
    virtual IWin_s00f1_7f70* FindChild(uint id, int recurse);   // +0xf0
};
struct Layout_s00f1_7f70 {
    IWin_s00f1_7f70* FindWindowByID(uint id, int recurse);      // 0x008105b0
    void  SetVisibility(int visible);                // 0x00810590
    bool  IsVisible();                               // 0x00810070
};
struct PaletteHolder_s00f1_7f70 {
    void Update(uint deltaMS);                       // 0x005c28b0 (cSPPaletteCategoryUI::Update)
};
struct SubA_s00f1_7f70 {
    uint pad00[0x18 / 4];
    PaletteHolder_s00f1_7f70* mpPalette;                        // +0x18
    uint pad1c;
    void* mpField20;                                 // +0x20
    int  GetLevelData();                             // 0x00f12690
    void SetAnimWindow(IWin_s00f1_7f70* win);                   // 0x00f17b00
};
struct Rect4 { float x, y, z, w; };
inline float fabsf(float x) { return x < 0.0f ? -x : x; }
inline const float& FMin(const float& a, const float& b) { return (b < a) ? b : a; }
inline const float& FMax(const float& a, const float& b) { return (a < b) ? b : a; }
struct IHandler_s00f1_7f70 { PV8 };
struct IServer_s00f1_7f70 {
    PV4
    virtual void Send(uint32_t id, int a, int b);            // +0x14
    PV2 PV
    virtual void AddHandler(IHandler_s00f1_7f70* h, uint32_t id);       // +0x24
};
namespace EA {
namespace Messaging {
void RemoveHandler(IServer_s00f1_7f70* server, IHandler_s00f1_7f70* h, uint32_t id, int prio, int flags);  // 0x00571db0
}
}
struct PanelHandlerBase_s00f1_7f70 : IHandler_s00f1_7f70 {
    virtual bool HandleMessage(uint msg, void* payload);     // 0x00f18970
};
struct IRef {
    virtual void v0();
    virtual void AddRef();                                   // +0x04
    virtual void Release();                                  // +0x08
};
struct PanelIface_s00f1_7f70 {
    uint pad00;                                              // +0x00
    IRef mRef;                                               // +0x04
    uint pad08[(0x90 - 8) / 4];                              // +0x08
    int  mMode;                                              // +0x90
};
struct Property_s00f1_7f70;
struct PropertyList_s00f1_7f70 {
    virtual void v0();
    virtual void Release();                                  // +0x04
    PV8
    virtual Property_s00f1_7f70* GetProperty(uint32_t key);             // +0x28
};
struct Property_s00f1_7f70 {
    union Value { int mInt; Property_s00f1_7f70* mpValue; } mValue;     // +0x00
    uint pad04[3];                                           // +0x04
    uint8_t mFlags;                                          // +0x10
    uint8_t pad11;                                           // +0x11
    uint16_t mType;                                          // +0x12
};
struct IFx;
class cSPUIProgress_s00f1_7f70 : public PanelPrimary, public PanelHandlerBase_s00f1_7f70 {
public:
    uint pad08[2];                                   // +0x08
    PanelIface_s00f1_7f70* mpWindow;                            // +0x10
    void* mpUnknown14;                               // +0x14
    Layout_s00f1_7f70* mpLayout;                                // +0x18
    IFx* mpEffect;                                   // +0x1c
    uint pad20;                                      // +0x20
    SubA_s00f1_7f70* mpSubA;                                    // +0x24
    uint pad28[(0xb8 - 0x28) / 4];
    PropertyList_s00f1_7f70* mpPropList;                        // +0xb8
    float mTimer;                                    // +0xbc
    float mCur;                                      // +0xc0
    float mStart;                                    // +0xc4
    float mEnd;                                      // +0xc8
    float mNext;                                     // +0xcc
    int   mLevel;                                    // +0xd0
    int   mState;                                    // +0xd4
    uint  mDelay;                                    // +0xd8
    IWinContainer_s00f1_7f70* mpWinA;                           // +0xdc
    IWinContainer_s00f1_7f70* mpWinB;                           // +0xe0
    IServer_s00f1_7f70* mpServer;                               // +0xe4
    IHandler_s00f1_7f70* mpHandler;                             // +0xe8
    uint  mMsg;                                      // +0xec
    int   mPrio;                                     // +0xf0
    int   mFlags;                                    // +0xf4

    void StartNextAnimation();                       // 0x00f17870
    bool CheckFlag(int a);                           // 0x00f135b0
    void Show(PanelIface_s00f1_7f70* window);                   // 0x00f18660
    void FUN_00f17ea0();                             // 0x00f17ea0
    int  FUN_00f13b10();                             // 0x00f13b10
    void FUN_00f15890();                             // 0x00f15890

    void Update(uint deltaMS);
};
namespace UI {
class cScenarioPlayProgressBar {
public:
    uint pad00[3];                                   // +0x00
    uint mpField0c;                                  // +0x0c
    IWinContainer_s00f1_7f70* mpWindow;                         // +0x10
    IWin_s00f1_7f70* mpBar;                                     // +0x14
    Rect4 mRect;                                     // +0x18 (left, top, right, bottom)
    float mCur;                                      // +0x28
    float mTarget;                                   // +0x2c
    bool mFlag30;                                    // +0x30
    bool mFlag31;                                    // +0x31
    uint8_t pad32[2];                                // +0x32
    uint pad34[8];                                   // +0x34 cSPUIAnimator
    IServer_s00f1_7f70* mpServer;                               // +0x54
    IHandler_s00f1_7f70* mpHandler;                             // +0x58
    uint mMsg;                                       // +0x5c
    int mPrio;                                       // +0x60
    int mFlags;                                      // +0x64

    void SetValue(float value);                      // 0x00f18a00
    void SetWindow(IWinContainer_s00f1_7f70* window);           // 0x00f18a50
    void Clear();                                    // 0x00f18d60
    void Update(uint deltaMS);                       // 0x00f18dc0
};
}
struct IFx {
    PV
    virtual void Release();                          // +0x04
    virtual void SetState(int state);                // +0x08
};
struct MsgPayload {
    uint pad00[4];
    uint mKey10;                                     // +0x10
    uint pad14;                                      // +0x14
    uint mKey18;                                     // +0x18
};
static inline cSPUIProgress_s00f1_7f70* PanelOwner(PanelHandlerBase_s00f1_7f70* h)
{
    return (cSPUIProgress_s00f1_7f70*)((char*)h - 4);
}
// ---- items of slice s00f17f70 end

// ---- items of slice s00f18eb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#ifndef S00F18EB0_H
#endif
namespace UI {
class cScenarioPlayProgressBar_s00f1_8eb0
{
public:
    cScenarioPlayProgressBar_s00f1_8eb0();               // 0x00f18eb0
    ~cScenarioPlayProgressBar_s00f1_8eb0();              // 0x00f18f50

    void    Tick();                           // 0x00f19050
    void    Reset();                          // 0x00f190a0
    void    Release();                        // 0x00f19130
    float   GetProgressF();                   // 0x00f19160
    void*   IsEnabled();                      // 0x00f191a0
    bool    IsActive();                       // 0x00f19b80
    uint8_t GetByte(int idx);                 // 0x00f19be0
    int     GetField(int idx);                // 0x00f19c00
    int     GetField2(int idx);               // 0x00f19c20
    int     GetField3(int idx);               // 0x00f19c40
    int     GetDelta(int idx);                // 0x00f19c60
    uint8_t GetKind(int idx);                 // 0x00f19c80
    bool    IsKindAb(int idx);                // 0x00f19cc0
    void    Apply(bool a, bool flag);         // 0x00f198f0
    void    Setup(uint32_t a, uint32_t b, uint32_t c, uint32_t d,
                  uint32_t e, uint32_t f, uint32_t g, uint32_t h,
                  uint32_t i);                // 0x00f19940
    void    Remove(void* a, uint32_t b);      // 0x00f19ac0
    float   ScanFrac();                       // 0x00f19d10
    void    EachChild(uint32_t* a, uint32_t b); // 0x00f19660
};
}
namespace UI {
struct MissionCard {              // [sim + 0x6c][+0x148]
    char    pad0[0x10];
    uint8_t mFlag10;              // +0x10
    void setFlag(bool on);        // 0x00e16a70
    void initForCreature(int a, int b);   // 0x00e133b0
    void resizeToContent(int a, int b);   // 0x00e13b50
};
}
namespace UI {
extern "C" void __cdecl sub_571db0(int e, int d, int c, int b, int a);
}
namespace UI {
extern "C" void __cdecl sub_572020(void* p, int n);
}
namespace UI {
extern "C" int  __stdcall sub_b320d0(unsigned int id);
}
namespace UI {
struct Xb32250 { void  Release(unsigned int id); };
}
namespace UI {
extern "C" int  __cdecl sub_b3d380(void);
}
namespace UI {
extern "C" void* __cdecl sub_b3d300(void);
}
namespace UI {
struct Xb1fdb0 { void* Find(void* a); };
}
namespace UI {
struct Xc15d50 { void  Add(void* a, int b, int c); };
}
namespace UI {
struct X7f83e0 { void  Ctor(); };
}
namespace UI {
struct X7f8c20 { void  Dtor(); };
}
namespace UI {
struct X93a2e0 { void  Reset(); };
}
namespace UI {
struct Xefcae0 { void  Tick(); };
}
namespace UI {
struct Xf3be60 { void* Find(int id); };
}
namespace UI {
bool  __cdecl cScenarioPlayProgressBar_HasFlag();            // 0x00f18ff0
}
namespace UI {
bool  __cdecl cScenarioPlayProgressBar_KindOk(void* p);      // 0x00f19220
}
namespace UI {
void  __cdecl cScenarioPlayProgressBar_Link(void* a);        // 0x00f195a0
}
namespace UI {
bool  __cdecl cScenarioPlayProgressBar_IsReady();            // 0x00f19640
}
namespace UI {
bool  __cdecl cScenarioPlayProgressBar_Pred(void* a);        // 0x00f19e00
}
// ---- items of slice s00f18eb0 end

// ---- items of slice s00f1ae10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_00f19530(void*);                         // 0x00f19530
extern "C" void* EA_Audio_GetSystemAT();                      // 0x00a206f0
typedef unsigned short wchar16;
struct VP {
    float x, y, z, f;
    VP() {}
    VP(float a, float b, float c, float d) : x(a), y(b), z(c), f(d) {}
};   // {position, scalar} pushed by value
struct WString {
    wchar16* mpBegin;
    wchar16* mpEnd;
    wchar16* mpCap;
    void assign(const wchar16* first, const wchar16* last);   // 0x00423650
};
struct CString {
    uint pad[5];
    CString();                                                // 0x006b5060
    CString(uint a, uint b, const wchar16* c);                // 0x006b5770
    ~CString();                                               // 0x006b5240
    bool Load(uint a, uint b, int c);                         // 0x006b54b0
    const wchar16* GetText();                                 // 0x006b55c0
};
typedef void* (__thiscall* PFnQI)(void*, uint);
inline void*  QI_s00f1_ae10(void* p, uint id) { return ((PFnQI)((void**)*(void**)p)[3])(p, id); }   // +0x0c
struct Ctr {                       // avatar / mission / interactable object
    void** vtbl;                   // +0x00
    char   pad04[0x18];
    int    f1c;                    // +0x1c
    char   pad20[4];
    int    f24;                    // +0x24
};
struct PBEl {
    char disabled;      // +0x00
    char flag1;         // +0x01
    char pad02[2];
    int  count;         // +0x04
    char sub8[0x1c];    // +0x08
    int  type;          // +0x24
    int  id;            // +0x28
    int  aux;           // +0x2c
    int  threshold;     // +0x30
    char flag34;        // +0x34
    char pad35[0x1ac - 0x35];
};
struct PB;
struct AvMgr {
    Ctr* GetAvatar();               // 0x00b1fdb0
};
extern "C" AvMgr* SPNounManager();  // 0x00b3d300
typedef int  (__thiscall* PFnV20)(void*);
typedef void (__thiscall* PFnV38)(void*, uint);
typedef void (__thiscall* PFnV40)(void*, uint, int);
typedef void (__thiscall* PFnV58)(void*);
inline int  Audio20(void* p)          { return ((PFnV20)((void**)*(void**)p)[8])(p); }   // +0x20
inline void Audio38(void* p, uint a)  { ((PFnV38)((void**)*(void**)p)[0x0e])(p, a); }    // +0x38
inline void Audio40(void* p, uint a, int b) { ((PFnV40)((void**)*(void**)p)[0x10])(p, a, b); } // +0x40
inline void Audio58(void* p)          { ((PFnV58)((void**)*(void**)p)[0x16])(p); }       // +0x58
extern "C" void* MessageServer_s00f1_ae10();                             // 0x0067dcc0
struct Msg {
    void V04();                     // +0x04
    void V08();                     // +0x08
};
struct MsgServer_s00f1_ae10 {
    void Post(int id, void* msg, int b);   // +0x14
};
static int Len16(const wchar16* p)
{
    const wchar16* q = p;
    while (*q) ++q;
    return (int)(q - p);
}
static void AssignStr(WString& w, const wchar16* p)
{
    w.assign(p, p + Len16(p));
}
class PB {
public:
    void  Add(PBEl* e, void* a, void* b);            // 0x00f1ae10
    void  Event(void* a, void* ev);                  // 0x00f1aff0
    void  Release(void* a, void* ev);                // 0x00f1b180
    void  Unlink(void* a, void* b, int c);           // 0x00f1b260
    char  TryAdd(void* a);                           // 0x00f1b2f0
    void  SetKind(int a);                            // 0x00f1b360
    void  PlaySound(int a, int b);                   // 0x00f1b370
    void  RefreshAll();                              // 0x00f1b450
    void  RemoveByType(void* a);                     // 0x00f1b590
    void  SetText(int kind);                         // 0x00f1b640
    void  SetMode(int a, PBEl* ev, int kind);        // 0x00f1b730
    Ctr*  FindNearest(void* a, int q, void* excl);   // 0x00f1b820
    void  GetNameA(WString* out);                    // 0x00f1b9b0
    void  GetNameB(WString* out);                    // 0x00f1ba00
    void  GetInfo(int idx, WString* out);            // 0x00f1ba50
    void  GetNameC(int i, WString* out);             // 0x00f1bcb0
    void  GetNameD(int i, WString* out);             // 0x00f1bcd0
    void  Setup(VP a, VP b, PBEl* e);                // 0x00f19940
    void  Remove(PBEl* e, void* p);                  // 0x00f19ac0
    void  Apply(int a, int b);                       // 0x00f198f0
    int   ByIndex(void* p);                          // 0x00f19840
    char  FUN_00f1a070(void* p);                     // 0x00f1a070
    void  FUN_00f1a120(PBEl* e, void* p);            // 0x00f1a120
    bool  FUN_00f1a7a0(int a, void* p);              // 0x00f1a7a0
    void  FUN_00f1a7f0(void* p);                     // 0x00f1a7f0
    void  FUN_00f1aae0(int a);                       // 0x00f1aae0
    int   EachChild(int id, int b);                  // 0x00f19660

    char    pad00[4];
    int     f04;            // +0x04
    char    pad08[0x54 - 0x08];
    WString ws54;           // +0x54
    char    pad60[4];
    PBEl*   begin;          // +0x64
    PBEl*   end;            // +0x68
    char    pad6c[0x90 - 0x6c];
    int     state;          // +0x90
    char    pad94[0xb0 - 0x94];
    int     f_b0;           // +0xb0
    char    padb4[4];
    int     f_b8;           // +0xb8
    char    padbc[0xec - 0xbc];
    char    f_ec;           // +0xec
};
struct FreeName {
    void Name(int id, WString* out);
};
// ---- items of slice s00f1ae10 end

// ---- items of slice s00f1bcf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_00f264d0(int a, int b, int c);        // cdecl, 3 args
extern "C" bool  FUN_00f3c870(void* a, void* b, float f, int c);  // 0x00f3c870 stdcall, 4 args
extern "C" void* EA_GetSystemAT();                          // 0x00a206f0 cdecl, 0 args
extern "C" void* SP_NounManager();                          // 0x00b3d300 cdecl, 0 args
static __inline const wchar_t* wend(const wchar_t* s)
{
    const wchar_t* p = s;
    while (*p)
        ++p;
    return p;
}
typedef void  (__thiscall *FnVIII)(void*, int, int, int);
typedef char  (__thiscall *FnC)(void*);
extern int g_16c7aa4_s00f1_bcf0;                                       // the global at 0x016c7aa4
struct WString_s00f1_bcf0 {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; void* mAlloc;  // 0x10
    WString_s00f1_bcf0* assign(const wchar_t* first, const wchar_t* last);            // 0x00423650
};
struct cString_s00f1_bcf0 {
    uint32_t mData[5];
    cString_s00f1_bcf0();                                                             // 0x006b5060
    cString_s00f1_bcf0(uint32_t tableID, uint32_t instanceID, const wchar_t* source); // 0x006b5770
    ~cString_s00f1_bcf0();                                                            // 0x006b5240
    const wchar_t* GetText() const;                                        // 0x006b55c0
    bool Load(uint32_t tableID, uint32_t instanceID, int flag);            // 0x006b54b0
};
struct Rec1ac {
    uint8_t mFlag;      // +0x00
    uint8_t mPad01[0x24 - 1];
    int     mType;      // +0x24
    int     mId28;      // +0x28
    int     mId2c;      // +0x2c
    uint8_t mPad30[0x1ac - 0x30];
};
struct Rec44Name {                                  // the +4 sub-object of a 0x44 record
    const wchar_t* Get();                           // 0x00f26360
};
struct Vec {
    void** mpBegin; void** mpEnd; void** mpCapacity;   // 0xc
    Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~Vec();                                            // 0x00ae6970
};
struct G74 {
    void  Fill(int arg, Vec* out);            // 0x00f40d00 thiscall 2
    void* Lookup(int arg);                    // 0x00f3e8a0 thiscall 1
    bool  Test(void* p);                      // 0x00f25670 thiscall 0
    bool  Query3(void* a, int b, void* c);    // 0x00f41dc0 thiscall 3
    bool  Cmp2(void* a, void* b);             // 0x00f3b3b0 thiscall 2
    bool  Find(int a, int b, int c, void* d, void* e);  // 0x00f420d0 thiscall 5
};
struct Combatant {
    int GetDamageState();                     // 0x008e7f80 thiscall 0
};
struct Creature {
    int   Count();                            // 0x00c0f780 thiscall 0
    void* At(int i);                          // 0x00c0f8a0 thiscall 1
    int   Next(int i);                        // 0x00c0f810 thiscall 1
};
struct CreatureBase {
    void Show();                              // 0x00c0f2b0
    int  Count2();                            // 0x00c0f4f0
    void* At(int i);                          // 0x00c0f8a0
    void* GetTargetAsCreature();              // 0x00c0ee70
};
struct NounManager {
    void* GetAvatar();                        // 0x00b1fdb0 thiscall 0
};
struct cSPEditorVerbTray {
    uint8_t mPad00[0x54];
    WString_s00f1_bcf0 mText54;        // +0x54
    Rec1ac* mBegin64;       // +0x64
    Rec1ac* mEnd68;         // +0x68
    uint8_t mPad6c[0x90 - 0x6c];
    int     mField90;       // +0x90
    uint8_t mPad94[0xb0 - 0x94];
    int     mFieldB0;       // +0xb0
    uint8_t mPadB4[0xb8 - 0xb4];
    int     mFieldB8;       // +0xb8
    uint8_t mPadBc[0xc8 - 0xbc];
    int     mFieldC8;       // +0xc8
    void*   mFieldCc;       // +0xcc
    uint8_t mPadD0[0xd4 - 0xd0];
    int     mFieldD4;       // +0xd4

    void GetName(int index, WString_s00f1_bcf0* out);                                  // 0x00f1bcf0
    void Refresh(void* pSel, void* target);                                 // 0x00f1be10
    int  FindPair(int a, int b, char c, int* out1, int* out2);              // 0x00f1c030
    void Toggle();                                                          // 0x00f1c2f0
    bool Step();                                                            // 0x00f1c4b0

    void Sub1ae10(int a, int b, int c);                                     // 0x00f1ae10
    void Sub1aae0(int a);                                                   // 0x00f1aae0
    void Sub1b730(int a, void* b, int c);                                   // 0x00f1b730
};
// ---- items of slice s00f1bcf0 end

// ---- items of slice s00f1e020 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gBarVtbl0[];             // 0x0148c2fc
extern char gBarVtbl1[];             // 0x0148c2ec
extern char gBaseVtbl1[];            // 0x013ec458
extern char gBaseVtbl0[];            // 0x013eb394
extern void* gMsgIdTable[20];        // 0x0148c268
extern uint8_t gEmptyString16[];     // 0x01667bac
extern float gCfg0;                  // 0x016c826c
extern float gCfg1;                  // 0x016c8270
extern float gCfg2;                  // 0x016c8274
extern float gFtoc;                  // 0x0148c2b8
extern float gT924;                  // 0x015ad924
extern float gT928;                  // 0x015ad928
extern float gT92c;                  // 0x015ad92c
extern float gT930;                  // 0x015ad930
extern float gT934;                  // 0x015ad934
extern float gT938;                  // 0x015ad938
extern float gT93c;                  // 0x015ad93c
extern float gT940;                  // 0x015ad940
extern float gT944;                  // 0x015ad944
extern float gT948;                  // 0x015ad948
extern float gT958;                  // 0x015ad958
extern float gT95c;                  // 0x015ad95c
extern void* gT82bc;                 // 0x016c82bc
extern void* gT82d0;                 // 0x016c82d0
extern void* gT82e4;                 // 0x016c82e4
extern void* gT82f8;                 // 0x016c82f8
extern void* gStartup;               // 0x016c7aa4
void operator_delete__(void*);                      // 0x00f47380  ??3@YAXPAX@Z
struct Stopwatch                                 // EA::Stopwatch, 0x18 bytes
{
    char raw[0x18];
    void Init(int a, int b);                     // 0x0093a560
    void SetUnits(int units);                    // 0x0093a1a0
};
typedef void (__thiscall *MsgSendFn)(void*, void*, uint);   // vtable slot +0x24
struct BarIface                                     // object released through slot +0x100
{
    virtual void vt00();
    virtual void vt04();
};
void* SP_MessageServer();                           // 0x0067dcc0
void  Messaging__RemoveHandler(void*, void*, void*, void*, void*);   // 0x00571db0
void* SP_TerrainMgr();                              // 0x00b3d320
struct TerrainMgr
{
    void* GetTerrain();                             // 0x00b1de80
};
struct ActHost
{
    void* GetAct(void* id);                         // 0x00f3be60
    void* FindCreature(void* id);                   // 0x00f3e8a0
    void* BuildGoal(void* a, void* e, void* b, void* g, int, int, int, int);  // 0x00f416b0
};
struct CreatureObj
{
    int IsMarked();                                 // 0x00f25ed0
};
struct Inventory
{
    void* GetItemID();                              // 0x00b1f9c0
};
struct ItemObj
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* v3(int, int);
};
void* GetGameDataVector(void*, int, int, int, int, int);   // 0x00b21340
void* EachChild2(void*);                            // 0x00f196f0
void* EachChild(void*, uint*, uint);                // 0x00f19660
void  FUN_00f1dcc0(void* vec, void* first, void* last);    // string16 vector assign
void  StringVec__resize(void* vec, unsigned n);     // 0x00553be0
void  FUN_006a0b50(void* obj, int key, int* count, void** data);   // 0x006a0b50
uint*  SP_GetPropertyAsUInt(void* p);               // 0x0041ea00
void*  Alloc(unsigned size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
int   FUN_00ca6db0(void*);                          // 0x00ca6db0
void* FUN_00989360(void*);                          // 0x00989360
void* FUN_00c04590(void*);                          // 0x00c04590
void  FUN_00c06f70(void*);                          // 0x00c06f70
uint8_t FUN_00f3b390(void*);                          // 0x00f3b390
float* GetProperty(void* prop);                     // 0x0041ea70 (float accessor body)
struct MapNode                                      // node of the list owned by GoalMap
{
    MapNode* child;                                 // +0x00 subtree / payload destroyed by 0x009a9600
    MapNode* next;                                  // +0x04
};
struct GoalMap                                      // eastl container at goal+0x08 (0x1c bytes)
{
    void*    f00; void* f04; void* f08;             // +0x00 .. +0x0b
    MapNode* head;                                  // +0x0c first node of the list
    void*    f10; void* f14; void* f18;             // +0x10 .. +0x1b
    void      Construct(const GoalMap&);            // 0x00b96560  copy-ctor body
    GoalMap&  operator=(const GoalMap&);            // 0x00b962d0  operator=
    void      destroyNode(MapNode* n);              // 0x009a9600  recursive node/subtree release
    void      destroy()                             // release the whole node list
    {
        MapNode* n = head;
        while (n) {
            destroyNode(n->child);
            MapNode* next = n->next;
            operator_delete__(n);
            n = next;
        }
    }
};
struct StepBody                                     // +0x04 of a 0x44-byte step element
{
    char raw[0x40];                                 // payload (two eastl string/vector members)
    void destroy();                                 // 0x00f280f0  element payload destructor
};
struct StepElem                                     // 0x44-byte element stored by Vec44
{
    int      key;                                   // +0x00
    StepBody body;                                  // +0x04 (0x40 bytes)
};
struct Vec44                                        // inline-buffer vector at goal+0x3c
{
    void* b; void* e; void* c;                      // +0x3c / +0x40 / +0x44
    int   f48; int f4c; int f50;                    // +0x48 / +0x4c / +0x50
    char  buf[0x154];                               // +0x54
    void  assignFrom(const Vec44&);                 // 0x00dfcb00  operator=
    void  Construct(const Vec44& x)                 // fixed_vector copy-construction
    {
        f50 = 0;
        b = buf;
        e = buf;
        c = buf + 0x154;
        assignFrom(x);
    }
    void  destroy()                                 // element teardown + heap-buffer release
    {
        StepElem* qEnd = (StepElem*)e;
        StepElem* q = (StepElem*)b;
        while (q < qEnd) {
            q->body.destroy();
            q++;
        }
        if (b && ((int*)b)[-1] != 0)
            operator_delete__(b);
    }
};
struct ActStep                                      // 0x188-byte act-step record at goal+0x24
{
    int f0; int f4; int f8; int fc;                 // +0x24 .. +0x30
    char f10; char pad11[3]; int f14;               // +0x34, +0x38
    Vec44 vec;                                      // +0x3c
    int f184;                                       // +0x1a8
    void Construct(const ActStep&);                 // 0x00dfd020  copy-ctor body
    __declspec(noinline) void ctor();               // 0x00f2bd10  default-ctor body
};
struct Goal                                         // 0x1ac bytes
{
    uint8_t b0; uint8_t b1; char pad2[2]; int i4;       // +0x00 .. +0x08
    GoalMap map;                                    // +0x08 (0x1c)
    ActStep act;                                    // +0x24 (0x188)
    Goal();
    void destroy();                                 // 0x00f1dec0
    Goal& operator=(const Goal&);                   // 0x00f1e810
};
struct GoalVec                                      // eastl::vector<Goal, ...>
{
    Goal* b; Goal* e; Goal* c;
    __declspec(noinline) void destroyRange(Goal* first, Goal* last);     // 0x00f1dfa0
    void Insert(Goal* pos, const Goal& val);        // 0x00f1eaa0
    void emplace_back();                            // 0x00f1ec50
};
void* DestroyActRange(ActStep* first, ActStep* last);   // 0x00f1df10
static inline void InitGoal(Goal* p)
{
    char* q = (char*)p;
    char* s = q + 0xc;
    *(void**)(q + 0x10) = 0;
    *(void**)(q + 0x14) = 0;
    *(void**)(q + 0x18) = 0;
    *(void**)s = s;
    *(void**)(q + 0x10) = s;
    *(void**)(q + 0x14) = 0;
    *(uint8_t*)(q + 0x18) = 0;
    *(void**)(q + 0x1c) = 0;
    p->act.ctor();
}
Goal::Goal()
{
    char* q = (char*)this;
    char* s = q + 0xc;
    *(void**)(q + 0x10) = 0;
    *(void**)(q + 0x14) = 0;
    *(void**)(q + 0x18) = 0;
    *(void**)s = s;
    *(void**)(q + 0x10) = s;
    *(void**)(q + 0x14) = 0;
    *(uint8_t*)(q + 0x18) = 0;
    *(void**)(q + 0x1c) = 0;
    act.ctor();
}
struct Bar
{
    void* v00;                       // +0x00
    void* v04;                       // +0x04
    void* v08;                       // +0x08
    char  pad0c[0x10];               // +0x0c .. +0x1b
    void* f1c;
    char  pad20[0x28];               // +0x20 .. +0x47
    float f48; float f4c; float f50; // +0x48 ..
    void* f54; void* f58; void* f5c; // string16 at +0x54
    char  pad60[4];
    GoalVec goals;                   // +0x64 .. +0x6f
    void* f70; void* f74; void* f78; // +0x70 ..
    void* f7c;                       // +0x7c  message server + handler args
    void* f80; void* f84; void* f88; void* f8c;
    char  pad90[8];                  // +0x90
    char  sw98[0x18];                // +0x98  EA::Stopwatch
    char  padb0[8];                  // +0xb0
    void* fb8;                       // +0xb8
    int   fbc;                       // +0xbc
    void* fc0;                       // +0xc0
    char  padc4[0x18];               // +0xc4 .. +0xdb
    float fdc;                       // +0xdc
    float fe0; float fe4; float fe8; // +0xe0 ..
    uint8_t fec;                       // +0xec
    char  paded[3];
    void* ff0; void* ff4;            // +0xf0
    float ff8;                       // +0xf8
    uint8_t ffc; uint8_t ffd;            // +0xfc, +0xfd
    uint8_t pade[2];
    void* f100;                      // +0x100

    Bar();
    ~Bar();
    void Init();
    void Update();
    void Scans();
    void Reset();                                   // 0x00f190a0
    void* EachChild(void* id, int cnt);             // 0x00f19660
    void AddGoal8(void* g, void* c, int x);         // 0x00f1ae10
    void AddGoal5(void* g, void* c);                // 0x00f1ae10
};
extern uint  gT94c;                  // 0x015ad94c
extern uint  gT950;                  // 0x015ad950
extern uint  gT954;                  // 0x015ad954
static inline bool GETPROP(void* obj, int id, void** out)
{
    void* p;
    return ((uint8_t(*)(void*, int, void**))(*(void**)((*(char**)obj) + 0x24)))(obj, id, out) != 0;
}
#define PROP(id, type, dst)                                              \
    if (GETPROP(t, id, &prop) && *(short*)((uint8_t*)prop + 0x12) == (type)) {   \
        dst = *GetProperty(prop);                                        \
    }
// ---- items of slice s00f1e020 end

// ---- items of slice s00f1faa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00ef73c0();
extern uint32_t g_015ad94c, g_015ad950, g_015ad954;
extern float g_015ad948;
struct Stopwatch_s00f1_faa0 {
    uint64_t start;
    uint64_t elapsed;
    int mode;
    uint64_t GetElapsedTime();   // 0x0093a5e0
    void Stop();                 // 0x0093a2e0
};
struct cGameTimeManager {
    void IncPauseGate(uint32_t gate);   // 0x00b32220
    void DecPauseGate(uint32_t gate);   // 0x00b32250
    bool FUN_00f18ff0();                // 0x00f18ff0 : is gate 0x4bf38a7 held
};
struct AssetBrowserT { char pad[0x1c]; char flag1c; };
struct IVisualEffect {
    virtual void v0();
    virtual void Release();                 // +4
    virtual void v2(int);                   // +8
    virtual void v3(int);                   // +0xc
};
struct EffectRef {
    IVisualEffect* p;
    IVisualEffect** AsPPTypeParam();   // 0x00a16f40
};
struct EffectsManagerT {
virtual void e0();
virtual void e1();
virtual void e2();
virtual void e3();
virtual void e4();
virtual void e5();
virtual void e6();
virtual void e7();
virtual void e8();
virtual void e9();
    virtual void e10();
    virtual bool GetEffect(uint32_t id, int arg, IVisualEffect** out);   // +0x2c
};
struct TriggerMgr {
    char pad[0x2c];
    int state;
    void FUN_00ad7e90(int);                                                          // 0x00ad7e90
    void PostTrigger(uint32_t id, int a, int b, int c, int d, int e);                // 0x00ae0930
    void FUN_00adde90(uint32_t id, void* data, int z);                               // 0x00adde90
};
struct RandomLCG {
    uint32_t RandomUint32Uniform(uint32_t n);   // 0x00a68fb0
};
struct cUICard { void SetVisible(int);          // 0x00e13360
};
struct cMissionPanel { void FUN_00e16a70(bool); // 0x00e16a70
};
struct PanelMgr {
    char pad0[0x148];
    cUICard* card;
    void FUN_00f0e4a0(int);                      // 0x00f0e4a0
};
struct UIRoot { char pad[0x6c]; PanelMgr* panels; };
extern UIRoot* g_UIRoot;                         // 0x016c7aa4
struct AvatarComp {
    char pad[0x80]; float f80;
    char pad1[0x17c - 0x84]; struct AvatarComp2* sub;   // +0x17c
    char* bits;                                  // +0x180 -> bitset storage at +0x44
};
struct GlyphIterator {
    void* node;
    void** bucket;
    GlyphIterator() {}
    GlyphIterator(const GlyphIterator& o) : node(o.node), bucket(o.bucket) {}
    GlyphIterator& operator++();                 // 0x009a69d0
};
struct GlyphTable {
    uint32_t alloc;
    void** buckets;
    uint32_t nBuckets;
    GlyphIterator begin();                       // 0x00594410
};
struct GlyphNode { void* next; struct GlyphVal* val; };
struct GlyphVal { char pad[0x8c]; struct GlyphObj* obj; };
struct GlyphObj {
virtual void g0();
virtual void g1();
virtual void g2();
virtual void g3();
    virtual bool IsActive();                     // +0x10
virtual void g5();
virtual void g6();
virtual void g7();
virtual void g8();
virtual void g9();
virtual void g10();
    virtual void SetA(int);                      // +0x2c
    virtual void SetB(int);                      // +0x30
};
struct ModelManagerT {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
    virtual uint32_t GetIndex(uint32_t id, int z);   // +0x28
};
struct AvatarComp2 { char pad[0x17a0]; GlyphTable glyphs; };
struct Avatar {
    char pad[0xb54];
    AvatarComp* comp;       // +0xb54
    uint32_t flags;         // +0xb58
};
struct NounMgr {
    Avatar* GetAvatar();   // 0x00b1fdb0
};
extern "C" AssetBrowserT* FUN_00401030();
extern "C" cGameTimeManager* FUN_00b3d380();
extern "C" NounMgr* FUN_00b3d300();
extern "C" TriggerMgr* FUN_00b3d4d0();
extern "C" EffectsManagerT* FUN_0067ddd0();
extern "C" ModelManagerT* FUN_0067dd80();
extern RandomLCG g_Random;                       // 0x01601760
struct TrigEntry { uint32_t id; uint32_t pad[3]; };   // 16-byte list entries
extern TrigEntry* g_016c82d0; extern TrigEntry* g_016c82d4;
extern TrigEntry* g_016c82e4; extern TrigEntry* g_016c82e8;
extern TrigEntry* g_016c82f8; extern TrigEntry* g_016c82fc;
struct TrigData { uint32_t a; uint32_t b; uint32_t c; };
struct Ctl {
    char pad0[0x78 - 0x0]; char f78;
    char pad1[0x90 - 0x79]; int state;
    int f94;
    Stopwatch_s00f1_faa0 sw;            // +0x98
    int fb0;
    char fb4;
    char padb5[7];
    int fbc;
    uint32_t fc0;
    char pad2[0xf8 - 0xc4]; float ff8;
    char ffc; char ffd;
    char pad3[2];
    EffectRef eff;   // +0x100

    void FUN_00f1f600();       // 0x00f1f600
    void FUN_00f1f3b0();       // 0x00f1f3b0
    void FUN_00f1b640(int);    // 0x00f1b640
    void FUN_00f1aae0(int);    // 0x00f1aae0
    void Update(uint32_t dt);
};
// ---- items of slice s00f1faa0 end

// @ 0x00f11c30
void cCreatureModeInputStrategy::FUN_00f11c30()
{
    mpVt = (void*)0x148be68;
    mpVt3c = (void*)0x148be50;
    mpVt44 = (void*)0x148be34;
    mpVt48 = (void*)0x148be24;
    mpVt4c = (void*)0x148be14;

    void* server = m108;
    if (server) {
        FUN_00571db0(server, (void*)m10c, m110, m114, m118);
        m108 = 0;
    }
    FUN_00d37b60(this);
}

// @ 0x00f11ca0
void cCreatureModeInputStrategy::FUN_00f11ca0()
{
    InputManager* im = FUN_00b3d250();
    mActive = 1;
    void* sub = (void*)&mpVt3c;

    DevMgr* dm = FUN_00b3d230();
    dm->AddSub(sub, 1);

    im->SetTriggerConfig(g_148bfc8, 0, 1);

    const char* cfg = FUN_006ab760(FUN_0067de40()->FUN_slot14(), g_1403c98)
                          ? g_1477758 : g_1477770;
    im->SetTriggerConfig(cfg, 0, 0);
    im->SetUIMachine(g_148bfb0);

    CursorTable* ct = FUN_0067cab0();
    ct->AddCursor((void*)0x514ab7b0u, g_147a7d4, 1, 0, 0);
    ct->AddCursor((void*)0x314ab7b1u, g_1476df0, 1, 0, 0);
    ct->AddCursor((void*)0xf14ab7b3u, g_1476ef8, 1, 0, 0);
    ct->AddCursor((void*)0xb14ab7b6u, g_1476eac, 1, 0, 0);
    ct->AddCursor((void*)0x514ab7b7u, g_1476ed0, 1, 0, 0);
    ct->AddCursor((void*)0xb14ab7b9u, g_1476e24, 1, 0, 0);
    ct->AddCursor((void*)0x114ab7bau, g_147a7b8, 1, 0, 0);
    ct->AddCursor((void*)0x514abe0bu, g_147a798, 1, 0, 0);
    ct->AddCursor((void*)0x71664d85u, g_1476d30, 1, 0, 0);
    ct->AddCursor((void*)0x755c4eb5u, g_147a77c, 1, 0, 0);
    ct->AddCursor((void*)0xf4f6c345u, g_147a75c, 1, 0, 0);
    ct->AddCursor((void*)0x3b360d8u, g_147a734, 1, 0, 0);
    ct->AddCursor((void*)0x3b360dcu, g_13fecec, 1, 0, 0);
    ct->AddCursor((void*)0x3b360dfu, g_147a70c, 1, 0, 0);
    ct->AddCursor((void*)0x7542cdb5u, g_147a6f0, 1, 0, 0);
    ct->AddCursor((void*)0x3b360e2u, g_147a6d0, 1, 0, 0);
    ct->AddCursor((void*)0x3b360e4u, g_13fecc8, 1, 0, 0);
    ct->AddCursor((void*)0xf36a0c84u, g_147a6a0, 1, 0, 0);
    ct->AddCursor((void*)0x342d221fu, g_147a67c, 1, 0, 0);
    ct->AddCursor((void*)0x7a2a419u, g_148bf94, 1, 0, 0);
    ct->AddCursor((void*)0x8054deau, g_148bf70, 1, 0, 0);
    ct->AddCursor((void*)0x7e849beu, g_148bf34, 1, 0, 0);
    ct->AddCursor((void*)0x7e849c5u, g_148bef8, 1, 0, 0);

    MsgServer* srv = FUN_00883860();
    m108 = srv;
    m10c = (u32)((char*)this + 0x48);
    m110 = (void*)g_148be90;
    m114 = 0x1a;
    m118 = 0;
    if (srv && (char*)this + 0x48) {
        u32 off = 0;
        do {
            srv->AddHandler((char*)this + 0x48, *(u32*)((char*)g_148be90 + off));
            off += 4;
        } while (off < 0x68);
    }

    SetInputPriorityStrategy(0);
    (*(void (__thiscall**)(void*))((char*)*(void**)this + 8))(this);
}

// @ 0x00f11f90
void cCreatureModeInputStrategy::FUN_00f11f90()
{
    FUN_00efcae0();

    void* server = m108;
    if (server) {
        FUN_00571db0(server, (void*)m10c, m110, m114, m118);
        m108 = 0;
    }

    InputManager* im = FUN_00b3d250();
    EList a;
    EList b;
    void* out = 0;
    a.next = &a; a.prev = &a; a.n = 0; a.b = 0; a.f10 = 0;
    b.next = &b; b.prev = &b; b.n = 0; b.b = 0; b.f10 = 0;
    im->FUN_slot20(&out, 0, 0);
    ((E4*)&b)->FUN_00e4b990((void*)b.n);
    ((B1*)&a)->FUN_00b1b830((void*)a.n);

    void* sub = this ? (void*)((char*)this + 0x3c) : 0;
    FUN_00b3d230()->RemoveSub(sub);
    mActive = 0;
}

// @ 0x00f12090
u32 QI::FUN_00f12090(u32 id)
{
    if (id != 0x2f009dd0)
        return 0;
    return ((char*)this - 0xc) ? (u32)this : 0;
}

// @ 0x00f120c0
void KeyForwarder::FUN_00f120c0(u32 value)
{
    sink.FUN_00e0a4c0(value, &g_15ad8c0);
}

// @ 0x00f12140
void cScenarioUnlockItemUI::Init(void* a, void* b, void* c, cSPPaletteItem* d)
{
    cSPPaletteItemUI::Init(a, b, c, d);

    mpItem = d;

    cSPUILayout_s00f1_14a0* alloc = (cSPUILayout_s00f1_14a0*)EAAllocate(0x18, "Simulator", 0, 0, 0, 0);
    cSPUILayout_s00f1_14a0* layout = alloc ? (cSPUILayout_s00f1_14a0*)alloc->ctor() : 0;
    mpLayout = layout;

    if (mpLayout.mp->Init(g_15ad898, 1, 0x5b598fa)) {
        mpLayout.mp->SetParentWin((IWin*)b, 1, 0x5b598fa);
        IWin* win = mpLayout.mp->FindWindowByID(0x7c4af80, 1);
        SetWindowAreaToParent(win);

        u32 ids[3];
        ids[0] = 0xa2e50993;
        ids[1] = 0x4d7d9be4;
        ids[2] = 0x0e03db96;
        for (int i = 0; i < 3; i++) {
            u32 id = ids[i];
            IWin* w = mpLayout.mp->FindWindowByID(id, 1);
            if (w)
                w->SetVisible(1, 0);
        }
        (*(void (__thiscall**)(void*, void*))((char*)*(void**)this + 0xc))(this, a);
    }
}

// @ 0x00f12270
void cScenarioUnlockItemUI::Shutdown()
{
    cSPPaletteItemUI::Shutdown();

    cSPUILayout_s00f1_14a0* layout = mpLayout.mp;
    if (layout) {
        mpLayout.mp = 0;
        layout->Release();
    }
    cSPPaletteItem* item = mpItem.mp;
    if (item) {
        mpItem.mp = 0;
        item->Release();
    }
}

// @ 0x00f122e0
IWin* __stdcall FUN_00f122e0(u32, u32)
{
    cScenarioUnlockItemUI* p =
        (cScenarioUnlockItemUI*)EAAllocate(0x34, "cScenarioUnlockItemUI", 0, 0, 0, 0);
    if (!p)
        return 0;
    p->cSPPaletteItemUI::cSPPaletteItemUI();
    *(void**)p = (void*)0x148c034;
    *(void**)((char*)p + 0x10) = (void*)0x148c008;
    *(void**)((char*)p + 0xc) = (void*)0x148c018;
    p->mpLayout.mp = 0;
    p->mpItem.mp = 0;
    p->m28 = 0;
    p->m2c = 0;
    p->m30 = 0;
    return (IWin*)((char*)p + 0xc);
}

// @ 0x00f12340
void Host::FUN_00f12340()
{
    cSPPaletteCategory* cat = ((Palette*)this->mPalette)->GetCategory(0);
    int nPages = (*(int*)((char*)this->mCatUI + 0x8c) - *(int*)((char*)this->mCatUI + 0x88)) >> 3;
    char* pageBase = this->mPageBase;
    for (int p = 0; p < nPages; ++p) {
        cSPPalettePage* page = ((Cat*)cat)->GetPage(p);
        ((CatUI*)this->mCatUI)->GetPageUI(p);
        int nItems = (*(int*)((char*)page + 0x74) - *(int*)((char*)page + 0x70)) >> 2;
        int cols = *(int*)((char*)page + 0x50);
        for (int i = 0; i < nItems; ++i) {
            int row = i / cols;
            int col = i % cols;
            if (row <= 0)
                continue;
            cSPPaletteItem* a = ((Page*)page)->GetItem(i);
            cSPPaletteItem* b = ((Page*)page)->GetItem((row - 1) * cols + col);
            cSPUILayout_s00f1_2340* lay = (cSPUILayout_s00f1_2340*)f_00e09ca0(pageBase, col, row - 1);
            char selA = 0;
            unsigned char prevDiff = 0;
            bool isSelf = false;
            char visB = 0;
            char* host = (char*)this;
            if (*(int*)((char*)a + 0x24) == (int)0xa2e50993) {
                prevDiff = *(int*)((char*)b + 0x24) != 0x4d7d9be4;
                selA = FUN_005c6730f(*(void**)(*(char**)(host + 0x14) + 0x10));
                isSelf = a == *(cSPPaletteItem**)(host + 0x20);
                char selB = FUN_005c65f0f(*(void**)(*(char**)(host + 0x14) + 0x10));
                visB = (selB && !selA && *(void**)(host + 0x20) == 0) ? 1 : 0;
                cSPPaletteCategory* sub = ((Cat*)cat)->GetSubCategory(i);
                WinObj* w = ((SubRec*)(*(void**)((char*)sub + 0x1c)))->Make(0xa2e50993, 1);
                char showW = (selA || prevDiff) ? 1 : 0;
                if (w) {
                    w->SetVisible(2, showW);
                    WinObj2v* v = w->Cast(0x8ed27e7a);
                    if (v)
                        v->SetIdx4(4, (int)cat);
                    WinObj* c2 = w->Child();
                    if (c2)
                        c2->SetVisible(2, visB);
                }
            } else if (*(int*)((char*)a + 0x24) == (int)0xe03db96) {
                prevDiff = *(unsigned char*)(host + 0x3c);
                selA = FUN_005c6730f(*(void**)(*(char**)(host + 0x14) + 0x10));
                isSelf = b == *(cSPPaletteItem**)(host + 0x20);
                cSPPaletteCategory* sub = ((Cat*)cat)->GetSubCategory(i);
                int subKey = *(int*)((char*)sub + 0x28);
                int grp = *(int*)(host + 0x40);
                WinObj* w = ((SubRec*)(*(void**)((char*)sub + 0x1c)))->Make(0xe03db96, 1);
                if (w) {
                    w->SetVisible(1, *(unsigned char*)(host + 0x3c));
                    WinObj2v* v = w->Cast(0x8ed27e7a);
                    if (v) {
                        char vis = (selA || isSelf || subKey == grp) ? 1 : 0;
                        v->SetIdx4(4, vis);
                    }
                }
            }
            lay->SetVisibility(prevDiff);
            char vis2 = (!selA || isSelf) ? 0 : 1;
            WinObj* w1 = lay->FindWindowByID(0x7e64f60, true);
            if (w1)
                w1->SetVisible(1, vis2);
            WinObj* w2 = lay->FindWindowByID(0x7e66af0, true);
            if (w2)
                w2->SetVisible(1, isSelf);
        }
        pageBase += 0x70;
    }
}

// @ 0x00f12690
void* Host::FUN_00f12690()
{
    Sub900* h = (Sub900*)this->mItemHost;
    return h ? (void*)h->mpWin.mpObject : 0;
}

// @ 0x00f126d0
void Host::FUN_00f126d0()
{
    Sub900* h = (Sub900*)this->mItemHost;
    ((Sub900b*)h->mpWin.mpObject)->Set(1);
    FUN_00f12340();
}

// @ 0x00f12700
void Host::FUN_00f12700(void* parent)
{
    char* self = (char*)this;
    void* obj = EAAllocate(0x18, "Simulator", 0, 0, 0, 0);
    if (obj)
        obj = ((ConnDialog*)obj)->ctor();
    else
        obj = 0;
    cSPUILayout_s00f1_2340* old = *(cSPUILayout_s00f1_2340**)(self + 0x0c);
    if ((cSPUILayout_s00f1_2340*)obj != old) {
        if (obj)
            ((GObjX*)obj)->AddRef();
        *(void**)(self + 0x0c) = obj;
        if (old)
            ((GObjX*)old)->Release();
    }
    cSPUILayout_s00f1_2340* lay = *(cSPUILayout_s00f1_2340**)(self + 0x0c);
    lay->Init((const EAKey*)0x15ad8cc, false, 0x5b598fa);
    lay->SetParentWin(parent, true, 0x5b598fa);
    WinObj* w = lay->FindWindowByID(0x7ece6d8, true);
    if (w) {
        w->AddRef();
        ((GObjX*)w)->SetHandler(this);
    }
    SPUI_SetWindowAreaToParent(w);
    int* i4 = *(int**)((char*)(*(int*)((char*)(*(int*)0x16c7aa4) + 0x74)) + 0x10);
    *(void**)(self + 0x10) = *(void**)((char*)i4 + 8);
    *(void**)(self + 0x14) = *(void**)((char*)i4 + 0xc);
    void* cat = *(void**)((char*)i4 + 0x10);
    *(void**)(self + 0x18) = cat;
    if (*(void**)(self + 0x10)) {
        void* s[4];
        s[0] = *(void**)(self + 0x10);
        s[1] = *(void**)(self + 0x14);
        s[2] = cat;
        s[3] = 0;
        int o2 = *(int*)(self + 0x20);
        int n2 = (int)EAAllocate(0x8c, "Simulator", 0, 0, 0, 0);
        if (n2)
            n2 = (int)((ConnObj*)n2)->Init();
        if (n2 != o2) {
            if (n2)
                ((SubUI2*)n2)->mRef.AddRef();
            *(int*)(self + 0x20) = n2;
            if (o2)
                ((SubUI2*)o2)->mRef.Release();
        }
        ((SubUI2*)n2)->Update(&s);
        int o1 = *(int*)(self + 0x1c);
        int n1 = (int)EAAllocate(0x150, "Simulator", 0, 0, 0, 0);
        if (n1)
            n1 = (int)((ConnObj2*)n1)->Init();
        if (n1 != o1) {
            if (n1)
                ((Obj1c*)n1)->AddRef();
            *(int*)(self + 0x1c) = n1;
            if (o1)
                ((Obj1c*)o1)->Release();
        }
        WinObj* fw = lay->FindWindowByID(0x7ce9360, true);
        ((Obj1c*)n1)->Setup(fw, *(void**)(self + 0x20), 0, 0);
        ((Obj1c*)n1)->SetMode(0, 0);
    }
    if (w)
        w->Release();
}

// @ 0x00f128f0
void Host::FUN_00f128f0()
{
    if (this->mSel) {
        this->mSel->Shutdown2();
        SubUI* sel = this->mSel;
        if (sel) {
            this->mSel = 0;
            sel->Release();
        }
    }
    if (this->mSub) {
        this->mSub->vv2();
        SubUI2* sub = this->mSub;
        if (sub) {
            SubRef* r = &sub->mRef;
            this->mSub = 0;
            r->Release();
        }
    }
    if (this->mLayout) {
        this->mLayout->Shutdown(1);
        cSPUILayout_s00f1_2340* lay = this->mLayout;
        if (lay) {
            this->mLayout = 0;
            lay->Release();
        }
    }
}

// @ 0x00f12970
void Host::FUN_00f12970()
{
    WinObj* w = this->mLayout->FindWindowByID(0x774b418, true);
    if (w) {
        w->AddRef();
        w->SetVisible(1, 1);
    }
    SPUIHelpers_BeginModal(this->mLayout->FindWindowByID(0x7ece6d8, true), 0, 0);
    struct { int a; int b; int c; } s = {-1, 0x7fffffff, 0x7fffffff};
    if (f_00eed9c0((char*)this + 0x10, &s) && s.c != 0x7fffffff) {
        if (s.c < 0) {
            WinObj* p = this->mLayout->FindWindowByID(0x7ce91d8, true);
            if (p) {
                WinObj2v* q = p->Cast(0x8ed27e7a);
                if (q)
                    q->SetIdx4(4, 1);
            }
        } else if (s.c > 0) {
            f_00ed1350(this->mLayout->FindWindowByID(0x5107b1a, true), 1);
        }
    }
    if (w)
        w->Release();
}

// @ 0x00f12a60
void Host::FUN_00f12a60()
{
    WinObj* w = this->mLayout->FindWindowByID(0x774b418, true);
    if (w) {
        w->AddRef();
        w->SetVisible(1, 0);
    }
    SPUIHelpers_EndModal(this->mLayout->FindWindowByID(0x7ece6d8, true), 0, 0);
    if (w)
        w->Release();
}

// @ 0x00f12b00
Host* Host::FUN_00f12b00(unsigned flags)
{
    *(void**)((char*)this + 0x00) = (void*)&vtbl_148c034;
    *(void**)((char*)this + 0x0c) = (void*)&vtbl_148c018;
    *(void**)((char*)this + 0x10) = (void*)&vtbl_148c008;
    _ReadWriteBarrier();
    SubUI* a = *(SubUI**)((char*)this + 0x24);
    if (a)
        a->vv2();
    SubUI* b = *(SubUI**)((char*)this + 0x20);
    if (b)
        b->vv2();
    ((PIB*)this)->Dtor();
    if (flags & 1)
        EAAllocate_free(this);
    return this;
}

// @ 0x00f12b50
void Host::FUN_00f12b50(cSPPaletteItem* item)
{
    ((PIB2*)this)->SetPaletteItem(item);
    char* self = (char*)this;
    char* it = (char*)item;
    int local20 = 0;
    int l18 = 0;
    int l1c = 0;
    cStringObj cs;
    int type = *(int*)(it + 0x24);
    PropVal* local24 = 0;
    if (type == (int)0xe03db96) {
        char* key = *(char**)(self + 4) + 0xc;
        PropMgr* pm = (PropMgr*)SP_PropertyManager();
        PropVal* dead = local24;
        if (dead) {
            local24 = 0;
            ((GObjX*)dead)->Release();
        }
        if (pm->Get(*(unsigned*)key, *(unsigned*)(key + 8), &local24)) {
            PropVal* pv = (PropVal*)local24->M28(0x7e5b81e);
            unsigned* pe = (unsigned*)pv->GetTPTR();
            *(unsigned*)(self + 0x28) = pe[0];
            *(unsigned*)(self + 0x2c) = pe[1];
            *(unsigned*)(self + 0x30) = pe[2];
            PropVal* tmp2 = 0;
            PropMgr* pm2 = (PropMgr*)SP_PropertyManager();
            PropVal* dead2 = tmp2;
            if (dead2) {
                tmp2 = 0;
                ((GObjX*)dead2)->Release();
            }
            if (pm2->Get(*(unsigned*)(self + 0x28), *(unsigned*)(self + 0x30), &tmp2))
                GetPropertyAsKey(item, 0xd4d959e2, &local20);
            PropVal* rel = tmp2;
            if (rel) {
                tmp2 = 0;
                ((GObjX*)rel)->Release();
            }
        }
    } else if (type == (int)0x4d7d9be4) {
        char* key = *(char**)(self + 4) + 0xc;
        PropMgr* pm = (PropMgr*)SP_PropertyManager();
        PropVal* dead = local24;
        if (dead) {
            local24 = 0;
            ((GObjX*)dead)->Release();
        }
        if (pm->Get(*(unsigned*)key, *(unsigned*)(key + 8), &local24)) {
            PropVal* pv = (PropVal*)local24->M28(0x7e5b81e);
            unsigned* pe = (unsigned*)pv->GetTPTR();
            *(unsigned*)(self + 0x28) = pe[0];
            *(unsigned*)(self + 0x2c) = pe[1];
            *(unsigned*)(self + 0x30) = pe[2];
            PropVal* tmp2 = 0;
            PropMgr* pm2 = (PropMgr*)SP_PropertyManager();
            PropVal* dead2 = tmp2;
            if (dead2) {
                tmp2 = 0;
                ((GObjX*)dead2)->Release();
            }
            if (pm2->Get(*(unsigned*)(self + 0x28), *(unsigned*)(self + 0x30), &tmp2))
                GetPropertyAsKey(item, 0x54d95162, &local20);
            PropVal* rel = tmp2;
            if (rel) {
                tmp2 = 0;
                ((GObjX*)rel)->Release();
            }
        }
    } else if (type == (int)0xa2e50993) {
        local20 = *(int*)(it + 0x18);
        l18 = *(int*)(it + 0x1c);
        l1c = *(int*)(it + 0x20);
        *(int*)(self + 0x28) = *(int*)(it + 0xc);
        *(int*)(self + 0x2c) = *(int*)(it + 0x10);
        *(int*)(self + 0x30) = *(int*)(it + 0x14);
    }
    if (local24)
        ((GObjX*)local24)->Release();
    WinObj* w = ((cSPUILayout_s00f1_2340*)(*(void**)(self + 0x20)))->FindWindowByID(
        *(unsigned*)(*(char**)(self + 4) + 0x24), true);
    if (w)
        w->SetVisible(1, 1);
    f_00807cb0(w, &local20, 0);
    ((WinObj8*)w)->SetKey(0x7f1fe63, self + 0xc);
}

// @ 0x00f12de0
void Host::FUN_00f12de0()
{
    *(void**)((char*)this + 0x00) = (void*)&vtbl_148c0e4;
    *(void**)((char*)this + 0x04) = (void*)&vtbl_148c0d4;
    *(void**)((char*)this + 0x0c) = (void*)&vtbl_148c0b8;
    _ReadWriteBarrier();
    int h = *(int*)((char*)this + 0x48);
    if (h) {
        int a = *(int*)((char*)this + 0x4c);
        int b = *(int*)((char*)this + 0x50);
        int c = *(int*)((char*)this + 0x54);
        int d = *(int*)((char*)this + 0x58);
        *(int*)((char*)this + 0x48) = 0;
        EAMessaging_RemoveHandler(h, a, b, c, d);
    }
    SubUI* p38 = *(SubUI**)((char*)this + 0x38);
    if (p38)
        p38->Release();
    ((PageVec*)((char*)this + 0x24))->Clear();
    SubUI* p20 = *(SubUI**)((char*)this + 0x20);
    if (p20)
        p20->vv2();
    SubUI* p1c = *(SubUI**)((char*)this + 0x1c);
    if (p1c)
        p1c->Release();
    SubUI* p18 = *(SubUI**)((char*)this + 0x18);
    if (p18)
        p18->vv3();
    SubUI* p14 = *(SubUI**)((char*)this + 0x14);
    if (p14)
        p14->vv2();
    SubUI* p10 = *(SubUI**)((char*)this + 0x10);
    if (p10)
        p10->vv2();
    *(void**)((char*)this + 0x0c) = (void*)&vtbl_13eb938;
    *(void**)((char*)this + 0x04) = (void*)&vtbl_13ec458;
    *(void**)((char*)this + 0x00) = (void*)&vtbl_13eb394;
}

// @ 0x00f12eb0
void Host::FUN_00f12eb0()
{
    cSPPaletteCategory* cat = ((Palette*)this->mPalette)->GetCategory(0);
    SubUI2* p20 = this->mSub;
    if (p20) {
        this->mSub = 0;
        p20->vv2();
    }
    CatUI* cu = (CatUI*)this->mCatUI;
    cu->Shutdown();
    cu->Init(cat, *(void**)((char*)this + 0x1c), *(void**)((char*)this + 0x14));
    cu->SetVisibility(true);
    char* base = this->mPageBase;
    int n = (*(int*)((char*)this->mCatUI + 0x8c) - *(int*)((char*)this->mCatUI + 0x88)) >> 3;
    int off = 0;
    for (int i = 0; i < n; ++i) {
        cSPPalettePage* page = ((Cat*)cat)->GetPage(i);
        cSPPalettePageUI* pui = cu->GetPageUI(i);
        PageBase* pb = (PageBase*)(base + off);
        pb->Reset();
        ObjUI* obj = ((PageUI*)pui)->mObj;
        struct { void* a; void* b; void* c; } s;
        s.a = 0;
        s.b = 0;
        s.c = 0;
        void* panel = obj->Get(0x7e654e8, 1, &s);
        pb->Attach(panel);
        int cnt = ((*(int*)((char*)page + 0x74) - *(int*)((char*)page + 0x70)) >> 2) - *(int*)((char*)page + 0x50);
        pb->Fill((void*)0x15ad8b4, cnt);
        off += 0x70;
    }
    FUN_00f12340();
}

// @ 0x00f12fc0
bool Host::FUN_00f12fc0(void* unused, void* msg)
{
    (void)unused;
    char* self = (char*)this;
    char* m = (char*)msg;
    volatile bool retv = false;
    int id = *(int*)(m + 8);
    float f10 = 0.0f;
    PLayout*& pl = *(PLayout**)(self + 0x2c);
    switch (id) {
    case 0x1b: {
        EObj* src = *(EObj**)m;
        unsigned t = src->GetType();
        if (t == 0xe03db96u || t == 0x4d7d9be4u) {
            EObj* o = src->GetByType(0x7f1fe63);
            int i1 = o ? ((int)o - 0xc) : 0;
            unsigned t2 = src->GetType();
            if (t2 == 0x4d7d9be4u)
                pl->ShowRolloverA(*(void**)(i1 + 0x28));
            else
                pl->ShowRolloverB(*(void**)(i1 + 0x28));
            pl->v20();
            pl->SetActive();
            SPUIHelpers_AnchorWindowToWindow(*(void**)(i1 + 0x1c), pl->GetRootWindow(), 0x41, 0);
        } else if (t == (unsigned)(-0x5d1af66d)) {
            EObj* o = src->GetByType(0x7f1fe63);
            EObj* p = o ? ((EObj*)((char*)o - 0xc)) : 0;
            ((EUI*)GetEditorUI())->GetPropertyLayout();
            void* ed = EAAllocate(100, "Editor", 0, 0, 0, 0);
            void* ev;
            if (!ed) {
                ev = 0;
            } else {
                char* g = *(char**)(self + 8);
                void* ch = ((EObj*)p)->Child();
                ResourceKey key;
                key.a = *(unsigned*)((char*)ch + 0xc);
                key.b = *(unsigned*)((char*)ch + 0x10);
                key.c = *(unsigned*)((char*)ch + 0x14);
                ev = ((EVeh*)ed)->Init(key, *(unsigned*)(g + 0x2c),
                                       0x14880158, 0, true);
            }
            ((EdObj*)&ed)->Init(ev);
            char* g2 = *(char**)(self + 8);
            void* ch2 = ((EObj*)p)->Child();
            pl->SetItem(ch2, g2, ed, 1);
            float* rect = ((EObj*)(*(void**)((char*)p + 0x1c)))->GetRect();
            f10 = rect[2] - rect[0];
            float out[2];
            ((EObj*)(*(void**)((char*)p + 0x1c)))->vc0(out, f10 * 0.5f, (rect[3] - rect[1]) * 0.5f);
            pl->SetPositionAndOffset(out[0], out[1], out[0] * 0.5f, 0.0f);
            pl->SetMode(2);
            if (ev)
                ((EvObj*)ev)->Release8();
        }
        break;
    }
    case 0x1c: {
        EObj* src = *(EObj**)m;
        unsigned t = src->GetType();
        if (t == 0xe03db96u || t == 0x4d7d9be4u) {
            pl->SetInactive();
        } else if (t == (unsigned)(-0x5d1af66d)) {
            ((PLayout*)((EUI*)GetEditorUI())->GetPropertyLayout())->Hide();
        }
        break;
    }
    case 0x287259f6: {
        EObj* src = *(EObj**)m;
        unsigned t = src->GetType();
        if (t == (unsigned)(-0x5d1af66d)) {
            EObj* o = src->GetByType(0x7f1fe63);
            EObj* p = o ? ((EObj*)((char*)o - 0xc)) : 0;
            char* g = *(char**)(self + 0x14);
            unsigned long long k = 0;
            if (g)
                k = f_00593980_(*(int*)(g + 0xc), *(int*)(g + 0x14));
            Collect* col = *(Collect**)(*(char**)(self + 8) + 0x10);
            col->Lock(k);
            void* ch = ((EObj*)p)->Child();
            ((Slot14*)(self + 0x14))->m572620(ch);
            char* g2 = *(char**)(self + 0x14);
            if (g2) {
                unsigned long long k2 = f_00593980_(*(int*)(g2 + 0xc), *(int*)(g2 + 0x14));
                col->Unlock(k2, 0);
            }
            ((Host*)(self - 0xc))->FUN_00f12340();
            retv = true;
        }
        break;
    }
    }
    return retv;
}

// @ 0x00f13330
extern "C" uint8_t __stdcall FUN_00f13330(uint32_t msg, int* data)
{
    if (msg != 0x65ff54a)
        return 1;
    if (*(uint32_t*)((char*)data + 0x10) != 0x40464100u)
        return 1;
    uint32_t kind = *(uint32_t*)((char*)data + 0x18);
    if (kind == 0x146f54c || kind == 0x67c078ceu || kind == 0x88f71bcfu)
        FUN_00f12eb0();
    return 1;
}

// @ 0x00f13370
extern "C" void* __fastcall FUN_00f13370(void* self, int, uint8_t freeFlag)
{
    char* s = (char*)self;
    *(void**)(s + 0x00) = (void*)0x148c09c;
    *(void**)(s + 0x04) = (void*)0x148c08c;
    _ReadWriteBarrier();
    void** p20 = *(void***)(s + 0x20);
    if (p20)
        ((FnV)(*(void***)((char*)p20 + 0x10))[4 / 4])((char*)p20 + 0x10);
    void** p1c = *(void***)(s + 0x1c);
    if (p1c)
        ((FnV)(*(void***)p1c)[4 / 4])(p1c);
    void** p0c = *(void***)(s + 0x0c);
    if (p0c)
        ((FnV)(*(void***)p0c)[8 / 4])(p0c);
    *(void**)(s + 0x04) = (void*)0x13ec458;
    *(void**)(s + 0x00) = (void*)0x13eb938;
    if (freeFlag & 1)
        operator_delete(s);
    return self;
}

// @ 0x00f133d0
int RewardUI::FUN_00f133d0(uint32_t, int* msg)
{
    char* self = (char*)this;

    if (*(int*)((char*)msg + 8) == 1) {
        if (*(int*)((char*)msg + 0x10) != 0x1b)
            return 1;
        uint32_t srv[3];
        srv[0] = 0xffffffffu;
        srv[1] = 0x7fffffffu;
        srv[2] = 0x7fffffffu;
        FUN_00eed9c0(self + 0x10, srv);
        if (srv[2] == 0x7fffffffu)
            srv[2] = 0;
        FUN_00eeda20(self + 0x10, srv);
        FUN_00f12a60(self);
        return 1;
    }

    if (*(int*)((char*)msg + 8) != 0x287259f6)
        return 0;

    uint32_t kind = *(uint32_t*)((char*)msg + 0xc);
    if (kind == 0x5107b1a || kind == 0x7ce91d8) {
        void* am = FUN_0067cb30();
        void* key = (void*)((char*)am + 0x58);
        uint32_t serverId[2];
        FUN_0054e530(key, self + 0x10, serverId, 1);
        void* poll = FUN_0067cb30();
        FUN_00610cb0(poll, (void*)serverId[0], (void*)(kind == 0x5107b1a ? 1u : 0u));
        uint32_t srv[3];
        srv[0] = 0xffffffffu;
        srv[1] = 0x7fffffffu;
        srv[2] = 0x7fffffffu;
        FUN_00eed9c0(self + 0x10, srv);
        srv[2] = (kind == 0x5107b1a) ? 1u : 0xffffffffu;
        FUN_00eeda20(self + 0x10, srv);
        FUN_00f12a60(self);
        return 1;
    }
    if (kind == 0x7737870) {
        uint32_t srv[3];
        srv[0] = 0xffffffffu;
        srv[1] = 0x7fffffffu;
        srv[2] = 0x7fffffffu;
        FUN_00eed9c0(self + 0x10, srv);
        if (srv[2] == 0x7fffffffu)
            srv[2] = 0;
        FUN_00eeda20(self + 0x10, srv);
        FUN_00f12a60(self);
        return 1;
    }
    return 1;
}

// @ 0x00f135b0
extern "C" int __fastcall FUN_00f135b0(void* this_, int)
{
    char* self = (char*)this_;
    void** am = (void**)FUN_00607a60();
    if (((FnP)(*(void***)am)[0x24 / 4])(am))
        return 0;
    if (!*(uint32_t*)(g_pMagic + 0xd0))
        return 0;

    char* t = *(char**)(*(char**)(g_pMagic + 0x74) + 0x10);
    uint32_t a = *(uint32_t*)(t + 8);
    uint32_t b = *(uint32_t*)(t + 0x10);

    struct { uint32_t k0; uint32_t k1; uint32_t k2; } key;
    key.k0 = a;
    key.k1 = 0x30bdee3;
    key.k2 = b;
    uint32_t holder = 0;
    uint32_t out = 0;

    void** mgr = (void**)EA_ResourceMan_GetManager();
    uint32_t dummy = 0;
    if (holder) {
        holder = 0;
        ((FnV)(*(void***)holder)[4 / 4])((void*)holder);
    }
    if (!((FnPII)(*(void***)mgr)[0xc / 4])(mgr, (int)&key, (int)&out))
        return 0;
    holder = out;
    void* meta = (void*)((FnPI)(*(void***)holder)[0xc / 4])((void*)holder, 0x30bdee3);
    if (!meta)
        return 0;
    void* idp = ((FnP)(*(void***)meta)[0])(meta);
    uint64_t id = *(uint64_t*)idp;
    if (id == 0xffffffffffffffffull) {
        // release and fail
        if (holder)
            ((FnV)(*(void***)holder)[4 / 4])((void*)holder);
        if (meta)
            ((FnV)(*(void***)meta)[4 / 4])(meta);
        return 0;
    }
    void** am2 = (void**)FUN_00607a60();
    uint64_t myId = 0;
    ((FnP)(*(void***)am2)[0x40 / 4])(am2);
    // compare - returns ecx:edx
    (void)myId;
    (void)dummy;
    if (holder)
        ((FnV)(*(void***)holder)[4 / 4])((void*)holder);
    if (meta)
        ((FnV)(*(void***)meta)[4 / 4])(meta);
    return 0;
}

// @ 0x00f13810
extern "C" void* __fastcall FUN_00f13810(void* self)
{
    char* s = (char*)self;
    *(void**)(s + 0x04) = (void*)0x13ec458;
    *(void**)(s + 0x0c) = (void*)0x14426a0;
    *(uint32_t*)(s + 0x08) = 0;
    *(void**)(s + 0x00) = (void*)0x148c0e4;
    *(void**)(s + 0x04) = (void*)0x148c0d4;
    *(void**)(s + 0x0c) = (void*)0x148c0b8;
    *(uint32_t*)(s + 0x10) = 0;
    *(uint32_t*)(s + 0x14) = 0;
    *(uint32_t*)(s + 0x18) = 0;
    *(uint32_t*)(s + 0x1c) = 0;
    *(uint32_t*)(s + 0x20) = 0;
    *(uint32_t*)(s + 0x24) = 0;
    *(uint32_t*)(s + 0x28) = 0;
    *(uint32_t*)(s + 0x2c) = 0;
    *(uint32_t*)(s + 0x38) = 0;
    *(uint8_t*)(s + 0x3c) = 0;
    *(uint32_t*)(s + 0x40) = 0;
    *(uint8_t*)(s + 0x44) = 0;
    *(uint32_t*)(s + 0x48) = 0;
    *(uint32_t*)(s + 0x4c) = 0;
    *(uint32_t*)(s + 0x50) = 0;
    *(uint32_t*)(s + 0x54) = 0;
    *(uint32_t*)(s + 0x58) = 0;
    return self;
}

// @ 0x00f13890
extern "C" void* __fastcall FUN_00f13890(void* self)
{
    char* s = (char*)self;
    *(uint32_t*)(s + 0x04) = 0;
    *(void**)(s + 0x00) = (void*)0x148c0ec;
    FUN_00e0a390(s + 8);
    *(uint32_t*)(s + 0x78) = 0;
    *(uint32_t*)(s + 0x7c) = 0;
    *(uint32_t*)(s + 0x80) = 0;
    return self;
}

// @ 0x00f138c0
extern "C" void __fastcall FUN_00f138c0(void* self)
{
    char* s = (char*)self;
    *(void**)(s + 0x00) = (void*)0x148c0ec;
    eastl_vector_dtor(s + 0x78);
    FUN_00e0a400(s + 8);
    *(void**)(s + 0x00) = (void*)0x13ec458;
}

// @ 0x00f138f0
extern "C" void* __fastcall FUN_00f138f0(void* self)
{
    char* s = (char*)self;
    *(void**)(s + 0x04) = (void*)0x13eb394;
    *(void**)(s + 0x08) = (void*)0x13ec458;
    *(uint32_t*)(s + 0x0c) = 0;
    *(void**)(s + 0x00) = (void*)0x148c114;
    *(void**)(s + 0x04) = (void*)0x148c10c;
    *(void**)(s + 0x08) = (void*)0x148c0fc;
    *(uint32_t*)(s + 0x10) = 0;
    *(uint32_t*)(s + 0x14) = 0;
    *(uint32_t*)(s + 0x18) = 0;
    *(uint32_t*)(s + 0x1c) = 0;
    *(uint32_t*)(s + 0x20) = 0;
    *(uint32_t*)(s + 0x24) = 0;
    *(uint32_t*)(s + 0x2c) = 0;
    *(void**)(s + 0x28) = (void*)0x148c0ec;
    FUN_00e0a390(s + 0x30);
    *(uint32_t*)(s + 0xa0) = 0;
    *(uint32_t*)(s + 0xa4) = 0;
    *(uint32_t*)(s + 0xa8) = 0;
    *(uint32_t*)(s + 0xb4) = 0;
    *(uint32_t*)(s + 0xb8) = 0;
    *(uint32_t*)(s + 0xd0) = 0;
    *(uint32_t*)(s + 0xd4) = 0;
    *(uint32_t*)(s + 0xd8) = 0;
    *(uint32_t*)(s + 0xbc) = 0;
    *(uint32_t*)(s + 0xc0) = 0;
    *(uint32_t*)(s + 0xc4) = 0;
    *(uint32_t*)(s + 0xc8) = 0;
    *(uint32_t*)(s + 0xcc) = 0;
    *(uint32_t*)(s + 0xdc) = 0;
    *(uint32_t*)(s + 0xe0) = 0;
    *(uint32_t*)(s + 0xe4) = 0;
    *(uint32_t*)(s + 0xe8) = 0;
    *(uint32_t*)(s + 0xec) = 0;
    *(uint32_t*)(s + 0xf0) = 0;
    *(uint32_t*)(s + 0xf4) = 0;
    return self;
}

// @ 0x00f139f0
void RewardUI::FUN_00f139f0()
{
    char* s = (char*)this;
    *(void**)(s + 0x00) = (void*)0x148c114;
    *(void**)(s + 0x04) = (void*)0x148c10c;
    *(void**)(s + 0x08) = (void*)0x148c0fc;
    _ReadWriteBarrier();

    uint32_t h = *(uint32_t*)(s + 0xe4);
    if (h) {
        *(uint32_t*)(s + 0xe4) = 0;
        EA_Messaging_RemoveHandler((void*)h, *(void**)(s + 0xe8), *(void**)(s + 0xec),
                                   *(void**)(s + 0xf0), *(void**)(s + 0xf4));
    }
    void** p38 = *(void***)(s + 0xe0);
    if (p38)
        ((FnV)(*(void***)p38)[4 / 4])(p38);
    void** p37 = *(void***)(s + 0xdc);
    if (p37)
        ((FnV)(*(void***)p37)[4 / 4])(p37);
    void** p2e = *(void***)(s + 0xb8);
    if (p2e)
        ((FnV)(*(void***)p2e)[4 / 4])(p2e);
    void** p2d = *(void***)(s + 0xb4);
    if (p2d)
        ((FnV)(*(void***)p2d)[4 / 4])(p2d);

    *(void**)(s + 0x28) = (void*)0x148c0ec;
    eastl_vector_dtor(s + 0xa0);
    FUN_00e0a400(s + 0x30);
    *(void**)(s + 0x28) = (void*)0x13ec458;
    _ReadWriteBarrier();

    void** p9 = *(void***)(s + 0x24);
    if (p9)
        ((FnV)(*(void***)((char*)p9 + 4))[8 / 4])((char*)p9 + 4);
    void** p8 = *(void***)(s + 0x20);
    if (p8)
        ((FnV)(*(void***)p8)[4 / 4])(p8);
    void** p7 = *(void***)(s + 0x1c);
    if (p7)
        ((FnV)(*(void***)p7)[4 / 4])(p7);
    void** p6 = *(void***)(s + 0x18);
    if (p6)
        ((FnV)(*(void***)p6)[8 / 4])(p6);
    void** p4 = *(void***)(s + 0x10);
    if (p4)
        ((FnV)(*(void***)((char*)p4 + 4))[8 / 4])((char*)p4 + 4);

    *(void**)(s + 0x08) = (void*)0x13ec458;
    *(void**)(s + 0x04) = (void*)0x13eb394;
    *(void**)(s + 0x00) = (void*)0x13eb938;
}

// @ 0x00f13b10
extern "C" int __fastcall FUN_00f13b10(void* self)
{
    char* s = (char*)self;

    // --- create the connection dialog and store at +0x18 ---
    void* nd = operator_new(0x18, "Simulator", 0, 0, 0, 0);
    if (nd)
        nd = FUN_00810000(nd);
    void* oldd = *(void**)(s + 0x18);
    if (nd != oldd) {
        if (nd)
            ((FnV)(*(void***)nd)[4 / 4])(nd);
        *(void**)(s + 0x18) = nd;
        if (oldd)
            ((FnV)(*(void***)oldd)[8 / 4])(oldd);
    }

    if (!FUN_008120d0(*(void**)(s + 0x18), (void*)0x15ad8d8, 1, 0x5b598f7))
        return 1;

    FUN_00810590(*(void**)(s + 0x18), 0);
    {
        void* w = (void*)FUN_008105b0(*(void**)(s + 0x18), -1, 1);
        if (w)
            ((FnVI)(*(void***)w)[0x104 / 4])(w, (int)s);
    }

    static const uint32_t tabIds4[4] = { 0x7c79918, 0x7db8991, 0x7db8990, 0x7c66c00 };
    for (int i = 0; i < 4; ++i) {
        void* w = (void*)FUN_008105b0(*(void**)(s + 0x18), (int)tabIds4[i], 1);
        if (w)
            ((FnVII)(*(void***)w)[0x7c / 4])(w, 1, 0);
    }
    static const uint32_t showIds2[2] = { 0x7e098d0, 0x7e09668 };
    for (int i = 0; i < 2; ++i) {
        void* w = (void*)FUN_008105b0(*(void**)(s + 0x18), (int)showIds2[i], 1);
        if (w)
            ((FnVII)(*(void***)w)[0x7c / 4])(w, 1, 1);
    }

    static const uint32_t pageIds[2] = { 0x7c796d0, 0x7c79820 };
    static const uint32_t subIds[2] = { 0x7c79d78, 0x7e09670 };
    for (int page = 0; page < 2; ++page) {
        void* w = (void*)FUN_008105b0(*(void**)(s + 0x18), (int)pageIds[page], 1);
        if (w)
            ((FnVII)(*(void***)w)[0x7c / 4])(w, 1, 0);
        for (int j = 0; j < 2; ++j) {
            void* sub = (void*)((FnPI)(*(void***)w)[0xf0 / 4])(w, (int)subIds[j]);
            if (sub)
                ((FnVII)(*(void***)sub)[0x7c / 4])(sub, 1, 0);
        }
        void* t1 = (void*)((FnPI)(*(void***)w)[0xf0 / 4])(w, 0x7c79948);
        FUN_00806e40(t1, 0, 0);
        void* t2 = (void*)((FnPI)(*(void***)w)[0xf0 / 4])(w, 0x7c79940);
        FUN_00806e40(t2, 0, 0);
        float* r1 = (float*)((FnP)(*(void***)t1)[0x38 / 4])(t1);
        float* r2 = (float*)((FnP)(*(void***)t2)[0x38 / 4])(t2);
        float arg1 = r1[0] - (r2[2] - r2[0]);
        float arg2 = r2[1];
        ((FnVII)(*(void***)t2)[0x70 / 4])(t2, *(int*)&arg1, *(int*)&arg2);
        void* t3 = (void*)((FnPI)(*(void***)w)[0xf0 / 4])(w, 0x7c79c50);
        FUN_00806e40(t3, 0, 0);
    }

    // --- content-validation summarizer at +0x20 ---
    {
        void* np = operator_new(0xa0, "Simulator", 0, 0, 0, 0);
        if (np)
            np = FUN_00f46b50(np);
        void* oldp = *(void**)(s + 0x20);
        if (np != oldp) {
            if (np)
                ((FnV)(*(void***)np)[0 / 4])(np);
            *(void**)(s + 0x20) = np;
            if (oldp)
                ((FnV)(*(void***)oldp)[4 / 4])(oldp);
        }
    }
    FUN_00f46920(*(void**)(s + 0x20), (void*)FUN_008105b0(*(void**)(s + 0x18), 0x7c7e188, 1));

    // --- cContentValidationSummarizer (0x24 bytes) at +0xb4 ---
    {
        char* np = (char*)operator_new(0x24, "Simulator", 0, 0, 0, 0);
        if (np) {
            *(void**)(np + 0x04) = (void*)0x13ec458;
            *(uint32_t*)(np + 0x08) = 0;
            *(void**)(np + 0x00) = (void*)0x148c09c;
            *(void**)(np + 0x04) = (void*)0x148c08c;
            *(uint32_t*)(np + 0x0c) = 0;
            *(uint32_t*)(np + 0x10) = 0;
            *(uint32_t*)(np + 0x14) = 0;
            *(uint32_t*)(np + 0x18) = 0;
            *(uint32_t*)(np + 0x1c) = 0;
            *(uint32_t*)(np + 0x20) = 0;
        }
        void* oldp = *(void**)(s + 0xb4);
        if (np != oldp) {
            if (np)
                ((FnV)(*(void***)np)[0 / 4])(np);
            *(void**)(s + 0xb4) = np;
            if (oldp)
                ((FnV)(*(void***)oldp)[4 / 4])(oldp);
        }
    }
    FUN_00f12700(*(void**)(s + 0xb4), (void*)FUN_008105b0(*(void**)(s + 0x18), -1, 1));

    // --- reward-UI sub-object (0x5c bytes) at +0x24 ---
    {
        char* np = (char*)operator_new(0x5c, "Simulator", 0, 0, 0, 0);
        if (np) {
            *(void**)(np + 0x04) = (void*)0x13ec458;
            *(uint32_t*)(np + 0x08) = 0;
            *(void**)(np + 0x0c) = (void*)0x14426a0;
            *(void**)(np + 0x00) = (void*)0x148c0e4;
            *(void**)(np + 0x04) = (void*)0x148c0d4;
            *(void**)(np + 0x0c) = (void*)0x148c0b8;
            for (unsigned i = 0x10; i <= 0x2c; i += 4)
                *(uint32_t*)(np + i) = 0;
            *(uint32_t*)(np + 0x38) = 0;
            *(uint8_t*)(np + 0x3c) = 0;
            *(uint32_t*)(np + 0x40) = 0;
            *(uint8_t*)(np + 0x44) = 0;
            *(uint32_t*)(np + 0x48) = 0;
            *(uint32_t*)(np + 0x4c) = 0;
            *(uint32_t*)(np + 0x50) = 0;
            *(uint32_t*)(np + 0x54) = 0;
            *(uint32_t*)(np + 0x58) = 0;
        }
        char* oldp = *(char**)(s + 0x24);
        if (np != oldp) {
            if (np)
                ((FnV)(*(void***)(np + 4))[4 / 4])(np + 4);
            *(void**)(s + 0x24) = np;
            if (oldp)
                ((FnV)(*(void***)(oldp + 4))[8 / 4])(oldp + 4);
        }
    }

    FUN_00e0a4c0((void*)FUN_008105b0(*(void**)(s + 0x18), 0x7c7e1b0, 1), (void*)0x15ad8c0, 0);

    FUN_00f135b0(s, 0);
    {
        void* w = (void*)FUN_008105b0(*(void**)(s + 0x18), 0x7e20437, 1);
        if (w)
            ((FnVII)(*(void***)w)[0x7c / 4])(w, 1, 0);
    }
    return 1;
}

// @ 0x00f14060
extern "C" void FUN_00f14060(uint32_t* node, uint32_t* end, uint32_t* out)
{
    if (node == end)
        return;
    do {
        *out = node[2];
        out[1] = node[3];
        out += 2;
        node = (uint32_t*)node[0];
    } while (node != end);
}

// @ 0x00f14090
extern "C" void FUN_00f14090(uint32_t start, uint32_t* end, uint32_t* out)
{
    if ((uint32_t*)start == end)
        return;
    do {
        start = *(uint32_t*)(start + 4);
        out[-2] = *(uint32_t*)(start + 8);
        out[-1] = *(uint32_t*)(start + 0xc);
        out -= 2;
    } while ((uint32_t*)start != end);
}

// @ 0x00f140c0
extern "C" void* __fastcall FUN_00f140c0(void* self, int, uint8_t freeFlag)
{
    char* s = (char*)self;
    *(void**)(s + 0x00) = (void*)0x148c0ec;
    eastl_vector_dtor(s + 0x78);
    FUN_00e0a400(s + 8);
    *(void**)(s + 0x00) = (void*)0x13ec458;
    if (freeFlag & 1)
        operator_delete(s);
    return self;
}

// @ 0x00f14140
extern "C" void FUN_00f14140(char* self, uint32_t* pos, uint32_t* value)
{
    uint32_t* end = *(uint32_t**)(self + 4);
    uint32_t* cap = *(uint32_t**)(self + 8);
    if (end != cap) {
        uint32_t* src = value;
        if ((uint32_t)pos <= (uint32_t)value && (uint32_t)value < (uint32_t)end)
            src = value + 2;
        if (end) {
            end[0] = end[-2];
            end[1] = end[-1];
        }
        uint32_t n = (uint32_t)((char*)end - 8 - (char*)pos);
        memmove((void*)((char*)end - n), pos, n);
        pos[0] = src[0];
        pos[1] = src[1];
        *(uint32_t**)(self + 4) = end + 2;
        return;
    }
    int count = (int)((char*)end - *(char**)self) >> 3;
    int newCap;
    char* dst;
    if (count == 0) {
        newCap = 1;
    } else {
        newCap = count * 2;
    }
    if (newCap == 0) {
        dst = 0;
    } else {
        dst = (char*)operator_new((uint32_t)(newCap * 8), "Simulator", 0, 0,
                                  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    {
        uint32_t n1 = (uint32_t)((char*)pos - *(char**)self);
        char* mid = (char*)DoInsertValue(dst, *(void**)self, n1);
        uint32_t* at = (uint32_t*)(mid + (n1 >> 3) * 8);
        if (at) {
            at[0] = value[0];
            at[1] = value[1];
        }
        uint32_t n2 = (uint32_t)(*(char**)(self + 4) - (char*)pos);
        char* r = (char*)DoInsertValue(at + 2, pos, n2);
        uint32_t* old = *(uint32_t**)self;
        if (old != 0 && old != *(uint32_t**)(self + 0x10))
            operator_delete(old);
        *(char**)self = dst;
        *(char**)(self + 4) = r + (n2 >> 3) * 8;
        *(char**)(self + 8) = dst + newCap * 8;
    }
    return;
}

// @ 0x00f143c0
extern "C" void FUN_00f143c0(char* self, uint32_t* pos, uint32_t* first, uint32_t* last)
{
    if (first == last)
        return;
    unsigned n = 0;
    for (uint32_t* p = first; p != last; p = (uint32_t*)p[0])
        ++n;
    uint32_t* end = *(uint32_t**)(self + 4);
    unsigned room = (unsigned)((char*)*(uint32_t**)(self + 8) - (char*)end) >> 3;
    if (n > room) {
        unsigned used = (unsigned)((char*)end - *(char**)self) >> 3;
        unsigned grow = used * 2;
        if (used == 0)
            grow = 1;
        unsigned want = n + used;
        if (want > grow)
            grow = want;
        char* dst = grow ? (char*)operator_new(grow * 8, "Simulator", 0, 0,
                          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        uint32_t n1 = (uint32_t)((char*)pos - *(char**)self);
        char* mid = (char*)DoInsertValue(dst, *(void**)self, n1);
        uint32_t* at = (uint32_t*)(mid + (n1 >> 3) * 8);
        for (uint32_t* p = first; p != last; p = (uint32_t*)p[0]) {
            at[0] = p[2];
            at[1] = p[3];
            at += 2;
        }
        uint32_t n2 = (uint32_t)(*(char**)(self + 4) - (char*)pos);
        char* r = (char*)DoInsertValue(at, pos, n2);
        uint32_t* old = *(uint32_t**)self;
        if (old != 0 && old != *(uint32_t**)(self + 0x10))
            operator_delete(old);
        *(char**)(self + 4) = r + (n2 >> 3) * 8;
        *(char**)self = dst;
        *(char**)(self + 8) = dst + grow * 8;
        return;
    }

    unsigned tail = (unsigned)((char*)end - (char*)pos) >> 3;
    if (n < tail) {
        uint32_t* src = end - n * 2;
        DoInsertValue((void*)end, src, (uint32_t)((char*)end - (char*)src));
        *(char**)(self + 4) += n * 8;
        memmove((void*)((char*)(end - n * 2) - ((char*)src - (char*)pos)), pos, (uint32_t)((char*)src - (char*)pos));
        FUN_00f14060(first, last, pos);
        return;
    }
    uint32_t* mid = first;
    FUN_00eadb10(&mid, (int)tail);
    FUN_00f14060(mid, last, end);
    *(char**)(self + 4) += (n - tail) * 8;
    DoInsertValue(*(void**)(self + 4), pos, (uint32_t)(*(char**)(self + 4) - (char*)pos));
    *(char**)(self + 4) += tail * 8;
    FUN_00f14090((uint32_t)first, mid, (uint32_t*)((char*)pos + tail * 8));
}

// @ 0x00f145a0
Vec12* Vec12::assign(const Vec12* src)
{
    if (src == this)
        return this;

    uint32_t n = (uint32_t)(((char*)src->mpEnd - (char*)src->mpBegin) >> 2);
    if (n > (uint32_t)(((char*)mpCapacity - (char*)mpBegin) >> 2)) {
        void* pNew = DoAllocate(n, src->mpBegin, src->mpEnd);
        DoDestroy(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            EADelete(mpBegin);
        mpCapacity = (char*)pNew + n * 4;
        mpEnd = (char*)pNew + n * 4;
        mpBegin = pNew;
        return this;
    }

    if (n > (uint32_t)(((char*)mpEnd - (char*)mpBegin) >> 2)) {
        do_copy(src->mpBegin,
                (char*)src->mpBegin + (uint32_t)(((char*)mpEnd - (char*)mpBegin) >> 2) * 4,
                mpBegin);
        void* out;
        uninit_copy(&out,
                    (char*)src->mpBegin + (uint32_t)(((char*)mpEnd - (char*)mpBegin) >> 2) * 4,
                    src->mpEnd, mpEnd, (void*)src);
        mpEnd = (char*)mpBegin + n * 4;
        return this;
    }

    void* r = do_copy(src->mpBegin, src->mpEnd, mpBegin);
    DoDestroy(r, mpEnd);
    mpEnd = (char*)mpBegin + n * 4;
    return this;
}

// @ 0x00f14690
Rec70* Rec70::CopyFrom(const Rec70& src)
{
    mpVtbl = (void*)0x147f604;

    mRef4 = src.mRef4;
    if (mRef4)
        ((FnV)(*(void***)mRef4)[0])(mRef4);
    mRef8 = src.mRef8;
    if (mRef8)
        ((FnV)(*(void***)mRef8)[0])(mRef8);

    mField0c = src.mField0c;
    mField10 = src.mField10;
    mField14 = src.mField14;

    Vec12* v18 = &mVec18;
    uint32_t n = (uint32_t)(((char*)src.mVec18.mpEnd - (char*)src.mVec18.mpBegin) >> 2);
    v18->Allocate(n, (void*)&src.mAlloc24);
    void* out;
    uninit_copy(&out, src.mVec18.mpBegin, src.mVec18.mpEnd, v18->mpBegin, (void*)&src);
    v18->mpEnd = out;

    mField2c = src.mField2c;

    VecF* v30 = &mVec30;
    uint32_t fn = (uint32_t)(((char*)src.mVec30.mpEnd - (char*)src.mVec30.mpBegin) >> 2);
    v30->Allocate(fn, (void*)&src.mVec30.mAlloc);
    void* r = memcpy_(v30->mpBegin, src.mVec30.mpBegin,
                      (uint32_t)((char*)src.mVec30.mpEnd - (char*)src.mVec30.mpBegin));
    v30->mpEnd = (char*)r + fn * 4;

    mF44 = src.mF44; mF48 = src.mF48; mF4c = src.mF4c;
    mF50 = src.mF50; mF54 = src.mF54; mF58 = src.mF58;

    mTail = src.mTail;

    return this;
}

// @ 0x00f147e0
Rec70* Rec70::operator=(const Rec70& src)
{
    void* s4 = src.mRef4;
    void* old4 = mRef4;
    if (s4 != old4) {
        if (s4)
            ((FnV)(*(void***)s4)[0])(s4);
        mRef4 = s4;
        if (old4)
            ((FnV)(*(void***)old4)[1])(old4);
    }

    void* s8 = src.mRef8;
    void* old8 = mRef8;
    if (s8 != old8) {
        if (s8)
            ((FnV)(*(void***)s8)[0])(s8);
        mRef8 = s8;
        if (old8)
            ((FnV)(*(void***)old8)[1])(old8);
    }

    mField0c = src.mField0c;
    mField10 = src.mField10;
    mField14 = src.mField14;

    mVec18.assign(&src.mVec18);
    mField2c = src.mField2c;
    mVec30.operator=(src.mVec30);

    mF44 = src.mF44; mF48 = src.mF48; mF4c = src.mF4c;
    mF50 = src.mF50; mF54 = src.mF54; mF58 = src.mF58;

    mTail = src.mTail;

    return this;
}

// @ 0x00f14980
void Owner::Reset()
{
    char* self = (char*)this;
    ((Sub8*)(self + 8))->Clear();

    Vec78* vec = (Vec78*)(self + 0x78);
    int n = (int)((char*)vec->mpEnd - (char*)vec->mpBegin) >> 2;
    for (int i = 0; i < n; ++i)
        ((TextZoomName**)vec->mpBegin)[i]->Shutdown();
    vec->Erase(vec->mpBegin, vec->mpEnd);
}

// @ 0x00f149d0
void Owner::Setup(const wchar_t* text, int flag, uint32_t id)
{
    char* self = (char*)this;
    Sub8* sub = (Sub8*)(self + 8);
    if (!sub->Check(1))
        return;

    void* layout = sub->At(sub->Count() - 1);

    TextZoomName* zoom = (TextZoomName*)EAAllocate(0x78, "Simulator", 0, 0, 0, 0);
    if (zoom)
        zoom = zoom->Init();
    else
        zoom = 0;

    TextZoomName* tmp = zoom;
    if (zoom)
        ((FnV)(*(void***)zoom)[1])(zoom);          // AddRef

    Vec78* vec = (Vec78*)(self + 0x78);
    if (vec->mpEnd < vec->mpCapacity) {
        TextZoomName** slot = (TextZoomName**)vec->mpEnd;
        vec->mpEnd = (char*)vec->mpEnd + 4;
        if (slot) {
            *slot = zoom;
            if (zoom)
                ((FnV)(*(void***)zoom)[1])(zoom);  // AddRef
        }
    } else {
        vec->DoInsertValue(vec->mpEnd, &tmp);
        zoom = tmp;
    }

    if (zoom)
        ((FnV)(*(void***)zoom)[2])(zoom);          // Release

    TextZoomName* z = *(TextZoomName**)((char*)vec->mpEnd - 4);

    void* win1 = ((Layout*)layout)->FindWindowByID(0x7fb67c0, 1);
    void* win2 = ((Layout*)layout)->FindWindowByID(0x7c7e1e0, 1);

    int r = 0;
    if (win2)
        r = ((FnII)(*(void***)win2)[3])(win2, 0xf15f4bd);

    z->Setup(r, 0, win1, 1, 0, 0, 0);

    if (win1)
        ((FnVII)(*(void***)win1)[0x7c / 4])(win1, 2, flag);
    if (win2)
        ((FnVI)(*(void***)win2)[0x80 / 4])(win2, (int)text);

    void* w = ((Layout*)layout)->FindWindowByID((int)id, 1);
    if (w)
        ((FnVII)(*(void***)w)[0x7c / 4])(w, 1, 1);
}

// @ 0x00f14b30
void Owner::SetLocalized(int value, const cString& name, uint32_t id)
{
    wchar_t buf[0x20];
    SetNumberString(value, value >> 31, buf, 0x20);

    void* mgr = GetSingleton();
    void* fmt = ((FnP)(*(void***)mgr)[0x20 / 4])(mgr);
    ((FnVII)(*(void***)fmt)[0x34 / 4])(fmt, (int)buf, 0);

    Setup(name.GetText(), value != 0, id);
}

// @ 0x00f14ba0
void Owner::SetPlain(int seconds, uint32_t id)
{
    bool flag = seconds != 0;

    int totalMinutes = seconds / 60;
    int hoursFull = totalMinutes / 60;
    int days = hoursFull / 24;
    int hours = hoursFull - days * 24;
    int minutes = totalMinutes - hoursFull * 60;
    int secs = seconds - totalMinutes * 60;

    wchar_t buf0[0x20], buf1[0x20], buf2[0x20], buf3[0x20];

    SetNumberString(secs, secs >> 31, buf0, 0x20);
    { void* m = GetSingleton(); void* f = ((FnP)(*(void***)m)[0x20 / 4])(m);
      ((FnVII)(*(void***)f)[0x34 / 4])(f, (int)buf0, 0); }

    SetNumberString(minutes, minutes >> 31, buf1, 0x20);
    { void* m = GetSingleton(); void* f = ((FnP)(*(void***)m)[0x20 / 4])(m);
      ((FnVII)(*(void***)f)[0x34 / 4])(f, (int)buf1, 1); }

    SetNumberString(hours, hours >> 31, buf2, 0x20);
    { void* m = GetSingleton(); void* f = ((FnP)(*(void***)m)[0x20 / 4])(m);
      ((FnVII)(*(void***)f)[0x34 / 4])(f, (int)buf2, 2); }

    SetNumberString(days, days >> 31, buf3, 0x20);
    { void* m = GetSingleton(); void* f = ((FnP)(*(void***)m)[0x20 / 4])(m);
      ((FnVII)(*(void***)f)[0x34 / 4])(f, (int)buf3, 3); }

    uint32_t nameId;
    if (days > 0)
        nameId = 0x773632d;
    else if (hours > 0)
        nameId = 0x773632c;
    else if (minutes > 0)
        nameId = 0x773632b;
    else
        nameId = 0x773632a;

    cString name(0xea25b547, nameId, 0);
    Setup(name.GetText(), flag, id);
}

// @ 0x00f14d90
void Owner::Update(const RecV& rec)
{
    Reset();

    SetLocalized(rec.f1c, cString(0xea25b547, 0x7736316, 0), 0x7ca2b50);
    SetLocalized(rec.f20, cString(0xea25b547, 0x773631c, 0), 0x7ca2b66);
    SetLocalized(rec.f24, cString(0xea25b547, 0x773631d, 0), 0x7ca2b61);
    SetLocalized(rec.f28, cString(0xea25b547, 0x773631e, 0), 0x7ca2b63);
    SetLocalized((int)rec.f44, cString(0xea25b547, 0x7736323, 0), 0x7ca2b62);
    SetLocalized((int)rec.f40, cString(0xea25b547, 0x773631f, 0), 0x7ca2b64);
    SetLocalized((int)rec.f3c, cString(0xea25b547, 0x7736322, 0), 0x7ca2b65);
    SetLocalized(rec.f00, cString(0xea25b547, 0x7736317, 0), 0x7ca2b51);
    SetLocalized(rec.f08, cString(0xea25b547, 0x7736319, 0), 0x7ca2b51);
    SetLocalized(rec.f04, cString(0xea25b547, 0x7736318, 0), 0x7ca2b51);
    SetLocalized(rec.f34, cString(0xea25b547, 0x7736324, 0), 0x7ca2b51);
    SetLocalized(rec.f38, cString(0xea25b547, 0x7736325, 0), 0x7ca2b54);
    SetLocalized(rec.f10, cString(0xea25b547, 0x773631a, 0), 0x7ca2b52);
    SetLocalized(rec.f0c, cString(0xea25b547, 0x7736326, 0), 0x7ca2b55);
    SetLocalized(rec.f14, cString(0xea25b547, 0x773631b, 0), 0x7ca2b53);
    SetLocalized(rec.f2c, cString(0xea25b547, 0x7736320, 0), 0x7ca2b68);
    SetLocalized(rec.f30, cString(0xea25b547, 0x7736321, 0), 0x7ca2b67);
}

// @ 0x00f15890
void cSPCreatureBase::OnPathCompleted()
{
    const char bFinished = (char)(mpInfo->mState90 == 5);   // "path completed" flag
    const int  nTotal = mpInfo->Count();                    // 0x00f191a0

    if (mpDataB8 == 0) {
        // no tagged data: just swap the two progress windows
        mWndDc.Assign(mpLayout->FindWindowByID(0x7c79820));
        IWindow* wIdle = mpLayout->FindWindowByID(0x7c796d0, 1);
        if (wIdle)
            wIdle->SetVisible(1, 0);
    } else {
        mWndDc.Assign(mpLayout->FindWindowByID(0x7c796d0, 1));
        IWindow* wDone = mpLayout->FindWindowByID(0x7c79820, 1);
        if (wDone)
            wDone->SetVisible(1, 0);

        int nKey = 0;
        if (mpDataB8 != 0) {
            void* tag = 0;
            if (((IWindow*)mpDataB8)->GetTag(&tag, 0xcf837237) && *(short*)((char*)tag + 0x12) == 9)
                nKey = *EA_Hash_FNV1_String8();
        }

        mD0 = FUN_00eec540(nKey);
        mC4 = (float)FUN_00eec580(mD0);
        mCc = (float)FUN_00eec580(mD0 + 1);
        mC0 = (float)nKey;
        mC8 = (float)nTotal + (float)nKey;

        if (FUN_00eec570() <= mD0 + 1)
            if (mC8 > mCc)
                mC8 = mCc;
        if (mC4 > mCc - 1.0f)
            mC4 = mCc - 1.0f;
        if (mC0 != mC8)
            mBc = FUN_00eec5b0();

        // the progress bar: take the bar rectangle of the two helper windows and move its low edge
        IWindow* wBar = mpLayout->FindWindowByID(0x7c7a310, 1);
        IWindow* wRange = mpLayout->FindWindowByID(0x7c7a318, 1);
        const float* range = wRange->GetVertex();
        const float lo = range[1];
        const float hi = range[3];
        float bar[4];
        memcpy(bar, wBar->GetVertex(), sizeof(bar));
        float t = 1.0f - (mC0 - mC4) / (mCc - mC4);
        if (t < 0.0f)
            t = 0.0f;
        bar[1] = lo + (hi - lo) * t;
        wBar->SetVertex(bar);

        // the progress label
        wchar_t text[0x10];
        IWindow* wLabel = mpLayout->FindWindowByID(0x7c7a088, 1);
        SetNumberString(text, 0x20, (long long)mCc);
        if (wLabel)
            wLabel->SetText(text);
        const char bMoved = (char)(bar[1] != lo);          // NaN counts as moved
        if (wLabel)
            wLabel->SetVisible(1, bMoved);

        SetNumberString(text, 0x20, (long long)mC0);
        IWindow* wLabel2 = mpLayout->FindWindowByID(0x7c79fd8, 1);
        if (wLabel2)
            wLabel2->SetText(text);

        cString_s00f1_5890 progress;
        FormatString(&progress, L"%d/%d", mD0, FUN_00eec570());
        IWindow* wProgress = mpLayout->FindWindowByID(0x7c79af8, 1);
        if (wProgress)
            wProgress->SetText(progress.Data());

        FUN_00806a60(mpLayout->FindWindowByID(0x7c55300, 1));
        void* info = FUN_00f3bcb0(gSporeApp);
        int* dest = (int*)((char*)gSporeApp + 0x7c);   // the UI state block follows the app object
        dest[5] = *(int*)info;                          // +0x14
        dest[6] = ((int*)info)[1];                      // +0x18
        dest[7] = ((int*)info)[2];                      // +0x1c
        dest[8] = -1;                                   // +0x20

        cLocalizedText flagA(0x623d2fc0, 0x7ceb16a, 0);   // 0x006b5770
        IWindow* wFlagA = mpLayout->FindWindowByID(0x7c79b20, 1);
        if (wFlagA)
            wFlagA->SetText(flagA.c_str());
        cLocalizedText flagB(0x623d2fc0, 0x7ceb16b, 0);
        IWindow* wFlagB = mpLayout->FindWindowByID(0x7c79b21, 1);
        if (wFlagB)
            wFlagB->SetText(flagB.c_str());
    }

    if (mWndDc.mpObject)
        mWndDc.mpObject->SetVisible(1, 1);
    IWindowManager* wm = WindowManager();
    wm->ShowWindow(0, mWndDc.mpObject);

    if (mWndDc.mpObject) {
        IWindow* w = mWndDc.mpObject->FindChild(0x7c7aa60, 1);
        if (w)
            w->SetVisible(1, bFinished);
        IWindow* w2 = mWndDc.mpObject->FindChild(0x7c7aa50, 1);
        if (w2)
            w2->SetVisible(1, !bFinished);
    }

    wchar_t buf[0x10];
    SetNumberString(buf, 0x20, (long long)nTotal);
    if (mWndDc.mpObject) {
        IWindow* w = mWndDc.mpObject->FindChild(0x7c79d78, 1);
        if (w)
            w->SetText(buf);
    }

    {
        const int nTicks = (int)(mpInfo->Ratio() * *(const float*)0x13ec4d0);
        SetNumberStringReal((double)nTicks, 0x20, buf, 0);
        if (mWndDc.mpObject) {
            IWindow* w = mWndDc.mpObject->FindChild(0x7c79e00, 1);
            if (w)
                w->SetText(buf);
        }
    }

    {
        cTimeStrings timeStrings;
        FUN_00f39110(&timeStrings);
        const int ms = mpInfo->ElapsedMs();
        const int minutes = ms / 60000;
        const int hours = minutes / 60;
        const int days = hours / 60;
        cString_s00f1_5890 text;
        FormatString(&text, L"%02d%s%02d%s%02d", days, timeStrings.mInner.c_str(),
                     hours % 60, timeStrings.mOuter.c_str(), minutes % 60);
        if (mWndDc.mpObject) {
            IWindow* w = mWndDc.mpObject->FindChild(0x7c79d98, 1);
            if (w)
                w->SetText(text.Data());
        }
    }

    if (mWndDc.mpObject) {
        IWindow* w = mWndDc.mpObject->FindChild(0x7c7c590, 1);
        if (w) {
            w->SetVisible(1, !bFinished);
            if (!bFinished)
                w->SetText(mpInfo->mpText54);
        }
    }

    mWndE0.Assign(mpLayout->FindWindowByID(0x7c79918, 1));
    if (mWndE0.mpObject) {
        mWndE0.mpObject->SetVisible(1, 0);
        IWindow* w = mWndE0.mpObject->FindChild(0x7c7aa60, 1);
        if (w)
            w->SetVisible(1, bFinished);
        IWindow* w2 = mWndE0.mpObject->FindChild(0x7c7aa50, 1);
        if (w2)
            w2->SetVisible(1, !bFinished);
    }

    // simulator bookkeeping / achievements
    void* pair[2] = {0, 0};
    int  v0 = 0, v1 = 0;
    void* mgr = *(void**)((char*)gSporeApp + 0x74);
    if (FUN_00552450(*(void**)((char*)mgr + 0x10), pair)) {
        void* p = FUN_005507a0(pair[0]);
        v0 = *(int*)p;
        v1 = ((int*)p)[1];
    }

    {
        const int ms = mpInfo->ElapsedMs();
        const int nTicks = (int)(mpInfo->Ratio() * *(const float*)0x13ec5b4);
        FUN_00f46cf0(mpStepper, v0, v1, nTicks);
        FUN_00f14d90(&mFollower, FUN_008dc790(mpInfo));
    }

    if (FUN_00f19640()) {
        if (!FUN_00f3cb60(*(void**)((char*)gSporeApp + 0x74))) {
            const unsigned int id = bFinished ? 0xf332be69u : 0x23346746u;
            FUN_00676e90(FUN_00675250(id, 1));
        }
        const int key = 0x706ccb27 + (bFinished ? 0xbcecb854 : 0);
        int dbg[2] = {0, 0};
        if (mpDataB8 != 0) {
            void* p = FUN_00f3bcb0(*(void**)((char*)gSporeApp + 0x74));
            void* q = FUN_0067cb30(*(void**)((char*)gSporeApp + 0x74));
            FUN_0054e530(q, p, dbg, 0);
        }
        long long values[4];
        values[0] = (long long)(int)(mpInfo->Ratio() * *(const float*)0x13ec5b4);
        values[1] = (long long)mpInfo->ElapsedMs();
        values[2] = (long long)mpInfo->Count();
        values[3] = (long long)dbg[0] | ((long long)dbg[1] << 32);
        void* ctrl = FUN_0067cb30(*(void**)((char*)gSporeApp + 0x74));
        FUN_0060e600(ctrl, values, 4);
        (void)key;
    }

    if (pair[1])
        ((IWindow*)pair[1])->Release();
}

// @ 0x00f16260
void PartHolder::Cleanup()
{
    ReleaseParts();
    mPart.Destroy();
}

// @ 0x00f16280
void Int64ListVector::AssignFromList(ListIterator first, ListIterator last, int tag)
{
    int64* p = mpBegin;
    if (p != mpEnd) {
        do {
            if (first == last)
                break;
            *p = *first;
            ++first;
            ++p;
        } while (p != mpEnd);
    }
    if (first == last) {
        int64* lastPos = mpEnd;
        CopyRange64(lastPos, mpEnd, p);
        mpEnd -= lastPos - p;
    } else {
        InsertList(mpEnd, first, last, first);
    }
}

// @ 0x00f16330
Element* ElementVector::EraseRange(Element* last, Element* pos)
{
    Element* p = MoveElements(pos, mpEnd, last);
    Element* end = mpEnd;
    for (; p < end; ++p)
        p->Destroy(0);
    mpEnd -= pos - last;
    return last;
}

// @ 0x00f16390
void ElementVector::InsertN(Element* position, unsigned int n, const Element* value)
{
    unsigned int freeCount = (unsigned int)(mpCapacity - mpEnd);
    if (n <= freeCount) {
        if (n == 0)
            return;

        Element temp(value);

        Element* oldEnd = mpEnd;
        unsigned int tail = (unsigned int)(oldEnd - position);
        if (n < tail) {
            // the new elements fit before the end: move the last n elements into the unused space,
            // then shift the middle part right
            Element* src = oldEnd - n;
            Element* dst = oldEnd;
            CopyConstructSaved(&dst, src, oldEnd, oldEnd);
            mpEnd = mpEnd + n;
            CopyConstructBackward(position, src, mpEnd);
            FillAssigned(position, position + n, &temp);
        } else {
            // the tail is shorter than the insert: fill the unused space, then move the tail behind
            // the inserted block
            FillUninitialized(oldEnd, n - tail, &temp);
            mpEnd = mpEnd + (n - tail);
            Element* dst = oldEnd;
            CopyConstructSaved(&dst, position, oldEnd, mpEnd);
            mpEnd = mpEnd + tail;
            FillAssigned(position, oldEnd, &temp);
        }
        temp.DestroySelf();
        return;
    }

    int oldSize = (int)(mpEnd - mpBegin);
    int newCapacity = oldSize * 2;
    if (oldSize == 0)
        newCapacity = 1;
    int total = oldSize + (int)n;
    if (total < newCapacity)
        total = newCapacity;

    Element* newData = 0;
    if (total != 0)
        newData = (Element*)AllocElementBlock((unsigned int)(total * (int)sizeof(Element)), 0xd1);

    Element* p = CopyConstructRange(mpBegin, position, newData);
    DestroyRange(mpBegin, position, newData);
    FillUninitialized(p, n, value);
    p += n;
    Element* newEnd = CopyConstructRange(position, mpEnd, p);
    DestroyRange(position, mpEnd, p);

    if (mpBegin != 0 && ((BlockHeader*)mpBegin)[-1].mSize != 0)
        FreeRawBlock(mpBegin);

    mpBegin = newData;
    mpEnd = newEnd;
    mpCapacity = newData + total;
}

// @ 0x00f16580
void cScenarioResultsRecorder::RecordResults(bool finished)
{
    if (mpPlayerProps == 0)
        return;

    if (finished && mpPlayMode->mCurrentPlayModeState == 5)
        RecordPlayedAdventure(mpPlayerProps, g_ScenarioManager->mpData->mpResource->mHeader);

    const int oldLevel = FindFirstGE(GetIntProperty(mpPlayerProps, 0xcf837237));

    int points = (int)mPoints;
    {
        EA::Variant_s00f1_6580 v;
        v = points;
        mpPlayerProps->SetProperty(0xcf837237, v);
    }
    int level = FindFirstGE(points);
    {
        EA::Variant_s00f1_6580 v;
        v = level;
        mpPlayerProps->SetProperty(0x5888ef41, v);
    }

    if (oldLevel != 10 && level == 10) {
        SP::AchievementsController()->AwardAchievement(0x8b16db09);
        App::MessageServer()->PostMSG(0x7ca274b, 0, 0);
    }

    eastl::fixed_vector_int64_32 stats;
    stats.push_back(points);
    stats.push_back(level);

    Simulator::cScenarioPlaySummary* s = mpPlayMode->GetSummary();
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x5ff28470, s->mNumGoalsCompleted));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xfbec5f0c, s->mNumCreaturesKilled));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x02e88517, s->mNumBuildingsDestroyed));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xb77e5335, s->mNumVehiclesDestroyed));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xf27fefd1, s->mNumBarrelsDestroyed));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x76134ba7, s->mNumCreaturesBefriended));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xa55c05aa, s->mNumObjectsCollected));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x547fecc1, s->mNumCastMembersTalkedTo));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x9d8493b2, s->mNumCastMembersDefended));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xdbcffa7d, s->mNumDeaths));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x384fb43e, s->mNumPosseMembersLost));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xf469cdc3, s->mAmountDamageDealt));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xad4e4ce0, (int)s->mAmountDamageReceived));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xceb2889b, s->mNumTimesUsedJetPack));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xc5ff81b3, s->mNumTimesUsedSprint));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xebed2519, (int)s->mAmountHealthRegained));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x42abfeab, (int)s->mAmountEnergyUsed));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x99a62668, 1));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x0db76cb8, mpPlayMode->mCurrentPlayModeState == 5));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x59df6558, mpPlayMode->mCurrentPlayModeState == 6));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x86a6dced, mpPlayMode->GetElapsedTimeMS() / 1000));

    Simulator::cCollectablesHolder* holder = mpHolder;
    holder->mpPending = 0;
    holder->mpPlayerData->mpCollectableItems.get()->Refresh(0);
    holder->Update();

    Simulator::cCollectableItems* items =
        (mpHolder->mpPlayerData ? mpHolder->mpPlayerData->mpCollectableItems
                                : eastl::intrusive_ptr<Simulator::cCollectableItems>()).get();
    SaveCollectableItems(mpPlayerProps, items);

    const ResourceKey_s00f1_6580* key = g_ScenarioManager->mpData->GetKey();
    SaveEditorPropertyList(key, mpPlayerProps, 0, 0);
    SP::GetPollinator()->UpdatePropertyInt(0xd9d7edf2, key, (uint32_t)stats.data(), stats.size());

    eastl::string16_s00f1_6580 name;
    GetAdventureName(key, &name);
    {
        EA::Variant_s00f1_6580 v;
        v.Set(0x13, 9, &name, 0x10, 1);
        SP::GetPollinator()->UpdateProperty2(0xa31b4d50, key, &v);
    }

    Simulator::cCollectableItems* items2 =
        (mpHolder->mpPlayerData ? mpHolder->mpPlayerData->mpCollectableItems
                                : eastl::intrusive_ptr<Simulator::cCollectableItems>()).get();
    eastl::list_s00f1_6580<int64_t>& unlocked = items2->GetUnlockedItems();
    stats.assign(unlocked.begin(), unlocked.end());
    SP::GetPollinator()->UpdatePropertyInt(0x0fdb0e00, key, (uint32_t)stats.data(), stats.size());
}

// @ 0x00f16fd0
void cScenarioPaletteOwner::Shutdown()
{
    if (mHandler != 0) {
        uint32_t handler = mHandler;
        mHandler = 0;
        EA::Messaging::RemoveHandler(handler, mHandlerIds[0], mHandlerIds[1],
                                     mHandlerIds[2], mHandlerIds[3]);
    }
    if (mpListener.mp != 0) {
        mpListener->Detach(&mAttachOwner);
        mpListener.reset();
    }
    mp14.reset();
    if (mpPalette.mp != 0) {
        mpPalette->Shutdown();
        mpPalette.reset();
    }
    if (mpCategory.mp != 0) {
        mpCategory->Shutdown();
        mpCategory.reset();
    }
    mp20.reset();
    mElements.EraseRange(mElements.mpBegin, mElements.mpEnd);
    if (mpChain.mp != 0) {
        mpChain->Build();
        mpChain.reset();
    }
    FUN_0067ca90()->Reset(0x15ad8a4);
}

// @ 0x00f170c0
bool cSPUIProgress::DoMessage(uint32_t msg, int* data)
{
	bool ok = false;
	int news = data[2];

	if (news == 1) {
		if (data[4] != 0x1b)
			return false;
		if (mState != 0)
			return false;
		if (mpWinB != 0 && mpWinB->IsVisible()) {
			FUN_00e12f80(mpWinB, 0);
			mState = 9;
			return true;
		}
		if (!FUN_00f0e250(mpWinA))
			return true;
		FUN_00e12f80(mpWinA, 0);
		mpScenario = (void*)1;
		mState = 10;
		FUN_00f16580(1);
		return true;
	}

	if (news == 0x287259f6) {
		switch (data[3]) {
		case 0x7c79940:
		case 0x7c79948:
			if (mpWinA != 0)
				((IWin_s00f1_70c0*)mpWinA)->SetVisible(1, false);
			mpScenario = (void*)((data[3] != 0x7c79948) + 1);
			mState = 10;
			FUN_00f16580(1);
			return true;

		case 0x7c79c50:
			{
				IAudioSystem* sysA = EAAudioGetSystemAT();
				KillSetiEffects(0x9ef448c0, sysA != 0 ? sysA->GetSomething() : 0);
			}
			if (mpWinA != 0)
				((IWin_s00f1_70c0*)mpWinA)->SetVisible(1, false);
			mState = 9;
			return true;

		case 0x7c79c78:
			{
				IAudioSystem* sysB = EAAudioGetSystemAT();
				KillSetiEffects(0x9ef448c0, sysB != 0 ? sysB->GetSomething() : 0);
			}
			if (mpWinB != 0)
				((IWin_s00f1_70c0*)mpWinB)->SetVisible(1, false);
			mState = 9;
			return true;

		case 0x7e20437:
			if (!FUN_00f135b0(0))
				return true;
			mpFieldB4->FUN_00f12970();
			return true;

		default:
			return false;
		}
	}

	if (news != 0x7e1a521)
		return false;

	IWin_s00f1_70c0* win = (IWin_s00f1_70c0*)data[0];
	if (win->GetOwnerId(0) != data[6])
		return false;
	bool notVis = !(win != 0 && win->IsVisible());
	bool visA = win != 0 && win->IsVisible();
	uint type = win->GetWindowType();

	switch (type) {
	case 0x774b418:
		if (!notVis)
			return false;
		if (mState == 10)
			mState2 = 3;
		return false;

	case 0x7c79d78:
		if (mState != 2)
			return true;
		if (!visA)
			return true;
		if (mTimer > 0.0f) {
			mState = 3;
			return true;
		}
		mState = 0;
		return true;

	case 0x7db8990:
		if (mState == 6 && visA) {
			FUN_00e12f80(mpLayout->FindWindowByID(0x7e09668, 1), 0);
			mState = 7;
			return true;
		}
		if (!notVis)
			return true;
		FUN_00e12f80(mpLayout->FindWindowByID(0x7e09668, 1), 1);
		return true;

	case 0x7e098d0:
		if (mState != 5)
			return true;
		if (!notVis)
			return true;
		FUN_00e12f80(mpLayout->FindWindowByID(0x7db8991, 1), 0);
		FUN_00e12f80(mpLayout->FindWindowByID(0x7db8990, 1), 1);
		mState = 6;
		KillSetiEffects(0x3c035721, GetRecorderState());
		{
			LayoutObj* layout = mpLayout;
			int arg = mCountD0 + 0x7d10de0;
			FUN_00806a60(layout->FindWindowByID(0x7c55300, 1), layout, arg, -1);
			*(uint32_t*)(*(char**)(g_16c7aa4 + 0x7c) + 0x20) = mCountD0;
			cString_s00f1_70c0 a;
			a.ctor(0x623d2fc0, 0x7ceb16a, 0);
			FUN_00e12fc0(mpLayout->FindWindowByID(0x7c79b20, 1), (void*)a.GetText());
			cString_s00f1_70c0 b;
			b.ctor(0x623d2fc0, 0x7ceb16b, 0);
			FUN_00e12fc0(mpLayout->FindWindowByID(0x7c79b21, 1), (void*)b.GetText());
			b.dtor();
			a.dtor();
		}
		return true;

	case 0x7e09668:
		if (mState != 7)
			return true;
		if (!notVis)
			return true;
		FUN_00e12f80(mpLayout->FindWindowByID(0x7db8990, 1), 0);
		FUN_00e12f80(mpLayout->FindWindowByID(0x7c66c00, 1), 1);
		{
			cString_s00f1_70c0 out;
			FUN_00f14120(&out, L"%d/%d", mCountD0, FUN_00eec570_s00f1_70c0());
			FUN_00e12fc0(mpLayout->FindWindowByID(0x7c79af8, 1), (void*)out.mText);
			mpSubA->FUN_00f126d0();
			out.dtor();
		}
		mState = 8;
		return true;

	case 0x7e09670:
		if (!visA)
			return true;
		FUN_00e12f80(win, 0);
		return true;

	case 0x7eb2740:
		if (mState == 4 && visA) {
			FUN_00e12f80(mpLayout->FindWindowByID(0x7e098d0, 1), 0);
			mState = 5;
			return true;
		}
		if (!notVis)
			return true;
		FUN_00e12f80(mpLayout->FindWindowByID(0x7e098d0, 1), 1);
		return true;

	case 0x7c796d0:
	case 0x7c79820:
	case 0x7c79918:
		break;

	default:
		return false;
	}

	if (mState == 1 && visA) {
		IWin_s00f1_70c0* w = mpWinA->FindChildWindow(0x7c79d78, 1, 1);
		FUN_00e12f80(w, 0);
		if (mpWindow->mMode == 5) {
			w = mpWinA->FindChildWindow(0x7e09670, 1, 1);
			FUN_00e12f80(w, 0);
		}
		if (mTimeC0 != mTimeC8) {
			mState = 2;
			return true;
		}
	} else if (mState == 10 && notVis) {
		if (mpScenario != (void*)1 || !FUN_00f135b0(1)) {
			mState2 = 3;
			return true;
		}
		mpFieldB4->FUN_00f12970();
		return true;
	} else {
		if (mState != 9)
			return true;
		if (!notVis)
			return true;
		IWin_s00f1_70c0* w = (void*)data[0] == (void*)mpWinA ? (IWin_s00f1_70c0*)mpWinB : (IWin_s00f1_70c0*)mpWinA;
		FUN_00e12f80(w, 1);
		WindowManager_s00f1_70c0()->ContentSet(0, w);
	}
	mState = 0;
	return true;
}

// @ 0x00f17870
void cSPUIProgress::StartNextAnimation()
{
	IServer* server = MessageServer_s00f1_70c0();
	int finishing = mpWindow->mMode == 5 ? 1 : 0;
	server->Send(0x7e36045, finishing, 0);

	if (mpServer) {
		IServer* oldServer = mpServer;
		mpServer = 0;
		EA::Messaging::RemoveHandler(oldServer, mpHandler, mMsg, mPrio, mFlags);
	}

	mpLayout->SetVisibility(0);
	if (mpWinA)
		mpWinA->SetVisible(1, false);
	if (mpWinB)
		mpWinB->SetVisible(1, false);
	IWin_s00f1_70c0* win = mpLayout->FindWindowByID(0x7c62860, 1);
	if (win)
		win->SetVisible(2, false);

	if (mpWinA) {
		IWinContainer* old = mpWinA;
		mpWinA = 0;
		old->Release();
	}
	if (mpWinB) {
		IWinContainer* old = mpWinB;
		mpWinB = 0;
		old->Release();
	}
	if (mpPropList) {
		PropertyList_s00f1_70c0* old = mpPropList;
		mpPropList = 0;
		old->Release();
	}
	if (mpWindow) {
		PanelIface* old = mpWindow;
		mpWindow = 0;
		old->mRef.Release();
	}

	mTimer = 0.0f;
	mpSubA->FUN_00f16fd0();
	mPair28.mList.Reset();
	GetUpdater()->ResetSlots();
	GameTimeManager()->DecPauseGate(0x4bf38a7);

	if (mpEffect) {
		mpEffect->Stop(0);
		IUiEffect* fx = mpEffect;
		if (fx) {
			mpEffect = 0;
			fx->Release();
		}
	}

	WinOwner* owner = (WinOwner*)WindowManager_s00f1_70c0()->GetActiveContent();
	owner->Set(false);

	win = mpLayout->FindWindowByID(0xffffffff, 1);
	SPUIHelpersEndModal(win, 0, 1);
	mState = 0;

	if (mpScenario) {
		SimMessage* msg = (SimMessage*)operator new(0x40, "Simulator", 0, 0, 0, 0);
		if (msg)
			msg = msg->Construct();
		msg->m_payload = mpScenario;
		MessageServer_s00f1_70c0()->Send(0x70b18c7, (int)msg, 0);
	}
}

// @ 0x00f17a70
void cItemVector::Resize(uint count)
{
	if (count > (uint)(int)(m_end - m_begin)) {
		Item70 tmp;
		Item70* created = tmp.Init();
		Insert(m_end, (int)count - (int)(m_end - m_begin), created);
		tmp.Destroy();
		return;
	}
	Erase(m_begin + count, m_end);
}

// @ 0x00f17b00
bool cSimScreen::Init(IUiEffect* effect, const EA::ResourceMan::Key_s00f1_70c0& key)
{
	PropertyList_s00f1_70c0* propList = 0;
	GetEditorPropertyList(key, &propList);
	void* items = 0;
	LoadCollectableItems(propList, &items);
	FUN_005970d0(0);

	mShowCollectables = false;
	if (propList) {
		Property_s00f1_70c0* prop = 0;
		if (propList->GetPropertyByKey(0xc54c543b, &prop) && prop->mType == 1)
			mShowCollectables = *prop->GetBool() != 0;
	}

	mCollectableId = 0;
	if (mShowCollectables) {
		void* node = FUN_00556140(&key, 0x2db6dad3);
		if (node == 0) {
			void* a = FUN_00556140(&key, 0xbeb528cb);
			void* b = FUN_00556140(&key, 0xf71fa311, a);
			void* c = FUN_00556140(&key, 0xad56080c, b);
			void* d = FUN_00556140(&key, 0xa426730b, c);
			node = FUN_00556440(d);
		}
		void* found[3] = {0, 0, 0};
		FUN_00555e80(node, found);
		if (found[0] != found[1])
			mCollectableId = *(uint32_t*)found[0];
		if (found[0] && ((uint32_t*)found[0])[-1] != 0)
			operator delete(found[0]);
	}

	GlobalSlots()->Set(&g_slot15ad8a4, 0);

	cSPPalette_s00f1_70c0* palette = 0;
	{
		cSPPalette_s00f1_70c0* mem = (cSPPalette_s00f1_70c0*)operator new(0x40, "Simulator", 0, 0, 0, 0);
		if (mem)
			palette = mem->Construct();
	}
	if (palette != mpPalette) {
		if (palette)
			palette->AddRef();
		cSPPalette_s00f1_70c0* old = mpPalette;
		mpPalette = palette;
		if (old)
			old->Release();
	}

	cCategoryHolder* category = 0;
	{
		cCategoryHolder* mem = (cCategoryHolder*)operator new(0x34, "Simulator", 0, 0, 0, 0);
		if (mem)
			category = mem->Construct();
	}
	if (category != mpCategory) {
		if (category)
			category->AddRef();
		cCategoryHolder* old = mpCategory;
		mpCategory = category;
		if (old)
			old->Release();
	}

	cPaletteCategoryUI* categoryUI = 0;
	{
		cPaletteCategoryUI* mem = (cPaletteCategoryUI*)operator new(0xfc, "Simulator", 0, 0, 0, 0);
		if (mem)
			categoryUI = mem->Construct();
	}
	if (categoryUI != mpCategoryUI) {
		if (categoryUI)
			categoryUI->AddRef();
		cPaletteCategoryUI* old = mpCategoryUI;
		mpCategoryUI = categoryUI;
		if (old)
			old->Release();
	}

	mpPalette->Init(g_key15ad8a8, 0x4178b8e8, 0x41b6160a, 0, 0, 0, 0x7c3bd3e);

	ISimItems* oldItems = mpCategory->mpItems;
	if (items != oldItems) {
		if (items)
			((ISimItems*)items)->AddRef();
		mpCategory->mpItems = (ISimItems*)items;
		if (oldItems)
			oldItems->Release();
	}
	mpCategory->mField2c = 0x4178b8e8;                       // float 15.5
	mpCategory->mField20 = 0x2b978c46;                       // float 4.3125e-13

	cSPPaletteCategory_s00f1_70c0* cat = mpPalette->GetCategory(0);
	int count = (int)((cat->m_end - cat->m_begin) / 4);
	mItems.Resize((uint)count);

	cSpaceInventory* inventory = 0;
	{
		cSpaceInventory* mem = (cSpaceInventory*)operator new(0xb0, "Simulator", 0, 0, 0, 0);
		if (mem)
			inventory = mem->Construct();
	}
	if (inventory != mpInventory) {
		if (inventory)
			inventory->AddRef();
		cSpaceInventory* old = mpInventory;
		mpInventory = inventory;
		if (old)
			old->Release();
	}
	mpInventory->Init(0x146f54c, 0x40464100);
	mpInventory->Setup();

	if (effect != mpEffect) {
		if (effect)
			effect->AddRef();
		IUiEffect* old = mpEffect;
		mpEffect = effect;
		if (old)
			old->Release();
	}
	mpEffect->SetTarget(&mParam0c);

	FUN_00f12eb0();

	IServer* server = MessageServer_s00f1_70c0();
	mpServer = server;
	mpHandler = (IHandler_s00f1_70c0*)this;
	mMsg[0] = 0x15ad8e4;
	mMsg[1] = 2;
	mPrio = 0;
	if (server) {
		for (int i = 0; i < 2; i++)
			server->AddHandler((IHandler_s00f1_70c0*)this, g_handlerIds15ad8e4[i]);
	}

	if (items)
		((ISimItems*)items)->Release();
	if (propList)
		propList->Release();
	return true;
}

// @ 0x00f17ea0
void cSPUIProgress::Shutdown()
{
	if (mpLayout && mpLayout->IsVisible())
		StartNextAnimation();

	if (mpLayout) {
		mpLayout->Shutdown(1);
		LayoutObj* old = mpLayout;
		if (old) {
			mpLayout = 0;
			old->Release();
		}
	}
	if (mpField20) {
		mpField20->Teardown();
		IObj20* old = mpField20;
		if (old) {
			mpField20 = 0;
			old->Release();
		}
	}
	if (mpFieldB4) {
		mpFieldB4->Teardown();
		IObjB4* old = mpFieldB4;
		if (old) {
			mpFieldB4 = 0;
			old->Release();
		}
	}
	if (mpSubA && mpSubA->mpPalette && mpSubA->mpPalette->IsVisible()) {
		mpSubA->FUN_00f16fd0();
		SubA* old = mpSubA;
		if (old) {
			mpSubA = 0;
			old->mRef.Release();
		}
	}
	Pair28* pair = &mPair28;
	pair->mList.Reset();
	pair->mObj.Destroy();
}

// @ 0x00f18970
bool PanelHandlerBase_s00f1_7f70::HandleMessage(uint msg, void* payload)
{    if (msg != 0x65ff54a)
        return false;
    MsgPayload* p = (MsgPayload*)payload;
    if (p->mKey10 != 0x40464100)
        return false;
    if (p->mKey18 != 0x3098258b)
        return false;

    Layout_s00f1_7f70* layout = PanelOwner(this)->mpLayout;
    bool visible;
    if (!layout)
        visible = false;
    else
        visible = layout->IsVisible();

    PanelIface_s00f1_7f70* window = PanelOwner(this)->mpWindow;
    cSPUIProgress_s00f1_7f70* self = PanelOwner(this);
    if (window) window->mRef.AddRef();
    if (visible) self->StartNextAnimation();
    self->FUN_00f17ea0();
    self->FUN_00f13b10();
    if (visible) self->Show(window);
    if (window) window->mRef.Release();
    return false;
}

// @ 0x00f18a00
void UI::cScenarioPlayProgressBar::SetValue(float value)
{
    mTarget = FMin(FMax(value, 0.0f), 1.0f);
}

// @ 0x00f18d60
void UI::cScenarioPlayProgressBar::Clear()
{
    if (mpServer) {
        IServer_s00f1_7f70* server = mpServer;
        mpServer = 0;
        EA::Messaging::RemoveHandler(server, mpHandler, mMsg, mPrio, mFlags);
    }
    if (mpWindow) {
        IWinContainer_s00f1_7f70* w = mpWindow;
        mpWindow = 0;
        w->Release();
    }
    if (mpBar) {
        IWin_s00f1_7f70* b = mpBar;
        mpBar = 0;
        b->Release();
    }
}

// @ 0x00f18dc0
void UI::cScenarioPlayProgressBar::Update(uint deltaMS)
{
    float d = mTarget - mCur;
    if (1.5258789e-05f < fabsf(d)) {
        float step = (float)deltaMS * 0.0005f;
        float zero = 0.0f;
        if (d > zero)
            d = FMin(FMax(d, zero), step);
        else
            d = FMin(FMax(d, -step), zero);
        mCur = mCur + d;
        mpBar->SetSize((mRect.z - mRect.x) * mCur, mRect.w - mRect.y);
    }
}

// @ 0x00f18eb0
namespace UI {
cScenarioPlayProgressBar_s00f1_8eb0::cScenarioPlayProgressBar_s00f1_8eb0()
{
    int* i = (int*)this;
    i[1] = 0x13eb394;
    i[2] = 0x13ec458;
    i[3] = 0;
    i[0] = 0x148c180;
    i[1] = 0x148c178;
    i[2] = 0x148c168;
    i[4] = 0;
    i[5] = 0;
    *(float*)((char*)this + 0x18) = 0.0f;
    *(float*)((char*)this + 0x1c) = 0.0f;
    *(float*)((char*)this + 0x20) = 0.0f;
    *(float*)((char*)this + 0x24) = 0.0f;
    *(float*)((char*)this + 0x28) = 1.0f;
    *(float*)((char*)this + 0x2c) = 0.0f;
    *(uint8_t*)((char*)this + 0x30) = 0;
    *(uint8_t*)((char*)this + 0x31) = 0;
    ((X7f83e0*)((char*)this + 0x34))->Ctor();
    i[0x15] = 0;
    i[0x16] = 0;
    i[0x17] = 0;
    i[0x18] = 0;
    i[0x19] = 0;
}
}  // namespace UI

// @ 0x00f18f50
namespace UI {
cScenarioPlayProgressBar_s00f1_8eb0::~cScenarioPlayProgressBar_s00f1_8eb0()
{
    int* i = (int*)this;
    *(void**)this = (void*)0x148c180;
    *(void**)((char*)this + 4) = (void*)0x148c178;
    *(void**)((char*)this + 8) = (void*)0x148c168;
    if (*(volatile int*)((char*)this + 0x54)) {
        int a = i[0x19];
        int b = i[0x18];
        int c = i[0x17];
        int d = i[0x16];
        int e = i[0x15];
        i[0x15] = 0;
        sub_571db0(e, d, c, b, a);
    }
    ((X7f8c20*)((char*)this + 0x34))->Dtor();
    if (i[5])
        ((void (__thiscall*)(void*))(*(void***)i[5])[1])((void*)i[5]);
    if (i[4])
        ((void (__thiscall*)(void*))(*(void***)i[4])[1])((void*)i[4]);
    i[2] = 0x13ec458;
    i[1] = 0x13eb394;
    i[0] = 0x13eb938;
}
}  // namespace UI

// @ 0x00f18ff0
namespace UI {
bool __cdecl cScenarioPlayProgressBar_HasFlag()
{
    return sub_b320d0(0x04bf38a7u) > 0;
}
}  // namespace UI

// @ 0x00f19050
namespace UI {
void cScenarioPlayProgressBar_s00f1_8eb0::Tick()
{
    int s = *(int*)((char*)this + 0x90);
    if (s - 5 > 1)
        return;
    if (*(int*)((char*)this + 0x94))
        return;
    ((X93a2e0*)((char*)this + 0x98))->Reset();
    int g = sub_b3d380();
    if (sub_b320d0(0x04bf38a7u) > 0)
        ((Xb32250*)(void*)g)->Release(0x04bf38a7u);
    ((Xefcae0*)this)->Tick();
}
}  // namespace UI

// @ 0x00f190a0
namespace UI {
void cScenarioPlayProgressBar_s00f1_8eb0::Reset()
{
    uint32_t tmp[0x12];
    for (int k = 0; k < 0x12; ++k)
        tmp[k] = 0;
    float* fp = (float*)&tmp[0x11];
    fp[0] = 0.0f;
    fp[1] = 0.0f;
    fp[2] = 0.0f;
    uint32_t* dst = (uint32_t*)((char*)this + 0xc);
    for (int k = 0; k < 0x12; ++k)
        dst[k] = tmp[k];
    *(int*)((char*)this + 0x90) = 2;
    *(int*)((char*)this + 0xc0) = 0;
    *(int*)((char*)this + 0xb8) = 0;
    *(uint8_t*)((char*)this + 0xec) = 0;
}
}  // namespace UI

// @ 0x00f19130
namespace UI {
void cScenarioPlayProgressBar_s00f1_8eb0::Release()
{
    void* p = *(void**)((char*)this + 0xf0);
    if (!p)
        return;
    sub_572020(p, 0);
    *(int*)((char*)this + 0xf0) = 0;
    *(int*)((char*)this + 0xf4) = 0;
}
}  // namespace UI

// @ 0x00f19160
namespace UI {
float cScenarioPlayProgressBar_s00f1_8eb0::GetProgressF()
{
    return (float)*(int*)((char*)this + 0xbc) * 0.001f;
}
}  // namespace UI

// @ 0x00f191a0
namespace UI {
void* cScenarioPlayProgressBar_s00f1_8eb0::IsEnabled()
{
    if (*(int*)((char*)this + 0x90) == 5) {
        int* g = *(int**)0x16c7aa4;
        if (g[0xd0 / 4])
            return *(void**)((char*)this + 0xc4);
    }
    return 0;
}
}  // namespace UI

// @ 0x00f19220
namespace UI {
bool __cdecl cScenarioPlayProgressBar_KindOk(void* p)
{
    if (!p)
        return false;
    void* q = ((void* (__thiscall*)(void*, uint32_t))(*(void***)p)[0xb8 / 4])(p, 0x175cdc9);
    if (!q)
        return false;
    uint32_t k = *(uint32_t*)((char*)q + 0x38) - 6;
    if (k > 9)
        return true;
    return true;
}
}  // namespace UI

// @ 0x00f195a0
namespace UI {
void __cdecl cScenarioPlayProgressBar_Link(void* a)
{
    void* g = sub_b3d300();
    void* h = ((Xb1fdb0*)g)->Find(0);
    if (h)
        ((Xc15d50*)h)->Add(a, 0, 0);
    if (!a)
        return;
    void* c = ((void* (__thiscall*)(void*, uint32_t))(*(void***)a)[0xb8 / 4])(a, 0xce9f6639);
    if (c)
        ((void (__thiscall*)(void*, int))(*(void***)c)[0xc8 / 4])(c, 1);
}
}  // namespace UI

// @ 0x00f19640
namespace UI {
bool __cdecl cScenarioPlayProgressBar_IsReady()
{
    int* g = *(int**)0x16c7aa4;
    int* p = (int*)g[0x74 / 4];
    return *(uint8_t*)((char*)p + 0x14) == 0 && g[0xd0 / 4] != 0;
}
}  // namespace UI

// @ 0x00f198f0
namespace UI {
void cScenarioPlayProgressBar_s00f1_8eb0::Apply(bool a, bool flag)
{
    int* g = *(int**)0x16c7aa4;
    void* panel = *(void**)((char*)g + 0x6c);
    MissionCard* card = *(MissionCard**)((char*)panel + 0x148);
    if (!card)
        return;
    card->setFlag(a);
    if (!flag)
        return;
    if (card->mFlag10)
        card->initForCreature(0, 0);
    else
        card->resizeToContent(0, 0);
}
}  // namespace UI

// @ 0x00f19b80
namespace UI {
bool cScenarioPlayProgressBar_s00f1_8eb0::IsActive()
{
    int* g = *(int**)0x16c7aa4;
    void* p = ((Xf3be60*)(void*)g[0x74 / 4])->Find(*(int*)((char*)this + 0xb8));
    if (p)
        if (*(uint8_t*)((char*)p + 0x7c))
            return *(int*)((char*)this + 0xbc) > 0;
    return false;
}
}  // namespace UI

// @ 0x00f19be0
namespace UI {
uint8_t cScenarioPlayProgressBar_s00f1_8eb0::GetByte(int idx)
{
    char* base = *(char**)((char*)this + 0x64);
    return *(uint8_t*)(base + (uint32_t)idx * 0x1ac + 0x34);
}
}  // namespace UI

// @ 0x00f19c00
namespace UI {
int cScenarioPlayProgressBar_s00f1_8eb0::GetField(int idx)
{
    char* base = *(char**)((char*)this + 0x64);
    return *(int*)(base + (uint32_t)idx * 0x1ac + 0x24);
}
}  // namespace UI

// @ 0x00f19c20
namespace UI {
int cScenarioPlayProgressBar_s00f1_8eb0::GetField2(int idx)
{
    char* base = *(char**)((char*)this + 0x64);
    return *(int*)(base + (uint32_t)idx * 0x1ac + 0x4);
}
}  // namespace UI

// @ 0x00f19c40
namespace UI {
int cScenarioPlayProgressBar_s00f1_8eb0::GetField3(int idx)
{
    char* base = *(char**)((char*)this + 0x64);
    return *(int*)(base + (uint32_t)idx * 0x1ac + 0x30);
}
}  // namespace UI

// @ 0x00f19c60
namespace UI {
int cScenarioPlayProgressBar_s00f1_8eb0::GetDelta(int idx)
{
    int* base = (int*)*(int*)((char*)this + 0x64);
    return base[idx * 0x6b + 0xc] - base[idx * 0x6b + 1];
}
}  // namespace UI

// @ 0x00f19c80
namespace UI {
uint8_t cScenarioPlayProgressBar_s00f1_8eb0::GetKind(int idx)
{
    char* end = *(char**)((char*)this + 0x68);
    char* beg = *(char**)((char*)this + 0x64);
    int count = (int)(end - beg) / 0x1ac;
    if (idx >= count)
        return 0;
    return *(uint8_t*)(*(int*)((char*)this + 0x64) + idx * 0x1ac);
}
}  // namespace UI

// @ 0x00f19cc0
namespace UI {
bool cScenarioPlayProgressBar_s00f1_8eb0::IsKindAb(int idx)
{
    char* end = *(char**)((char*)this + 0x68);
    char* beg = *(char**)((char*)this + 0x64);
    int count = (int)(end - beg) / 0x1ac;
    if (idx >= count)
        return false;
    int k = *(int*)(*(int*)((char*)this + 0x64) + idx * 0x1ac + 0x24);
    return k == 0xa || k == 0xb;
}
}  // namespace UI

// @ 0x00f19e00
namespace UI {
bool __cdecl cScenarioPlayProgressBar_Pred(void* a)
{
    bool ok = false;
    void* p = *(void**)((char*)a + 0x64);
    if (p) {
        void* q = ((void* (__thiscall*)(void*, unsigned))(*(void***)p)[0x0c / 4])(p, 0x17f243b);
        if (q) {
            if (((unsigned (__thiscall*)(void*))(*(void***)q)[0x20 / 4])(q) != 0x2e72cae) {
                if (((unsigned (__thiscall*)(void*))(*(void***)q)[0x20 / 4])(q) != 0x18eb45e) {
                    ok = true;
                } else {
                    ((void (__thiscall*)(void*, unsigned))(*(void***)q)[0x0c / 4])(q, 0xd0036e08);
                    void* av = ((Xb1fdb0*)sub_b3d300())->Find(0);
                    ok = q != av;
                }
            }
        }
    }
    return ok;
}
}  // namespace UI

// @ 0x00f1b180
void PB::Release(void* a, void* ev)
{
    if (state == 3 && a) {
        void* ag = QI_s00f1_ae10(a, 0xd0036e08);
        if (ag) {
            Ctr* av = SPNounManager()->GetAvatar();
            if (ag == (void*)av) {
                int id = ((Ctr*)ev)->f1c;
                if (id != -1) {
                    for (PBEl* e = begin; e != end; ++e) {
                        if (e->type == 8 && e->id == id) {
                            if (e->count == 1) {
                                if (e->flag1) Remove(e, (char*)ag + 0xc0);
                            } else {
                                --e->count;
                            }
                        }
                        if (e->type == 9 && e->id == id && !e->disabled)
                            Apply(0, 1);
                    }
                }
            }
        }
    }
    if (FUN_00f1a7a0(8, ev)) FUN_00f19530(ev);
}

// @ 0x00f1b260
void PB::Unlink(void* a, void* b, int)
{
    if (state != 3) return;
    int ia = ((Ctr*)a)->f1c;
    int ib = ((Ctr*)b)->f1c;
    for (PBEl* e = begin; e != end; ++e) {
        switch (e->type) {
        case 6:
            if ((e->id == ia && e->aux == ib) || (e->id == ib && e->aux == ia)) {
                if (!e->disabled) Add(e, 0, 0);
                e->flag1 = 0;
            }
            break;
        case 8:
            if (e->id == ib) e->flag1 = 0;
            break;
        }
    }
}

// @ 0x00f1b2f0
char PB::TryAdd(void* a)
{
    char r = 0;
    if (state == 3) {
        int id = ((Ctr*)a)->f1c;
        if (id != -1 && FUN_00f1a070(a)) {
            for (PBEl* e = begin; e != end; ++e) {
                if (!e->disabled && e->type == 2 && id == e->id) {
                    r = 1;
                    FUN_00f1a120(e, a);
                    break;
                }
            }
        }
    }
    return r;
}

// @ 0x00f1b360
void PB::SetKind(int a)
{
    FUN_00f1a7a0(2, (void*)a);
}

// @ 0x00f1b370
void PB::PlaySound(int, int b)
{
    void* au = EA_Audio_GetSystemAT();
    int v = 0;
    if (au) v = Audio20(au);
    au = EA_Audio_GetSystemAT();
    if (au) {
        Audio38(au, 0x3475365);
        Audio40(au, 0x3475381, 0xe76c9b4f);
        Audio40(au, 0x3475385, v);
        Audio58(au);
    }
    char* m = (char*)EAAllocate(0x40, "App", 0, 0, 0, 0);
    if (m) {
        *(int*)(m + 0x30) = 0;
        *(int*)m = 0x13eb90c;
        _InterlockedExchange((volatile long*)(m + 4), 0);
        *(int*)m = 0x13eb844;
        *(int*)(m + 0x38) = 0;
        ((Msg*)m)->V04();
    }
    *(int*)(m + 0x30) = f04;
    *(int*)(m + 8) = b;
    void* ms = MessageServer_s00f1_ae10();
    ((MsgServer_s00f1_ae10*)ms)->Post(*(int*)(m + 0x30), m, 0);
    ((Msg*)m)->V08();
}

// @ 0x00f1b640
void PB::SetText(int kind)
{
    f_b0 = kind;
    CString s;
    switch (kind) {
    case 0:
        s.Load(0x21851ebe, 0x796cee4, 0);
        AssignStr(ws54, s.GetText());
        break;
    case 1:
        s.Load(0x21851ebe, 0x796cfdd, 0);
        AssignStr(ws54, s.GetText());
        break;
    case 4:
        s.Load(0x21851ebe, 0x7c50b5f, 0);
        AssignStr(ws54, s.GetText());
        break;
    }
}

// @ 0x00f1bcb0
void PB::GetNameC(int i, WString* out)
{
    ((FreeName*)this)->Name(((PBEl*)((char*)begin + i * 0x1ac))->id, out);
}

// @ 0x00f1bcd0
void PB::GetNameD(int i, WString* out)
{
    ((FreeName*)this)->Name(((PBEl*)((char*)begin + i * 0x1ac))->aux, out);
}

// @ 0x00f1bcf0
void cSPEditorVerbTray::GetName(int index, WString_s00f1_bcf0* out)
{
    void* g = *(void**)&g_16c7aa4_s00f1_bcf0;
    int v = (int)FUN_00f264d0(*(int*)(*(int*)((char*)g + 0x74) + 0x10),
                         mFieldB8,
                         *(int*)((char*)mFieldCc + 0x1c));
    cString_s00f1_bcf0 cs(0x21851ebe, 0x75f8fc0, 0);

    if (index < (*(int*)(v + 0x1c) - *(int*)(v + 0x18)) / 0x44) {
        char* rec = (char*)*(void**)(v + 0x18) + index * 0x44;
        const wchar_t* name = ((Rec44Name*)(rec + 4))->Get();
        out->assign(name, wend(name));
        if (out->mpEnd != out->mpBegin)
            return;
        const wchar_t* t = cs.GetText();
        out->assign(t, wend(t));
    } else {
        const wchar_t* t = cs.GetText();
        out->assign(t, wend(t));
    }
}

// @ 0x00f1be10
void cSPEditorVerbTray::Refresh(void* pSel, void* target)
{
    if (mField90 != 3)
        return;
    int sel = *(int*)((char*)pSel + 0x1c);
    if (sel == -1)
        return;
    Rec1ac* e = mEnd68;
    Rec1ac* p = mBegin64;
    if (p == e)
        return;

    do {
        if (p->mFlag == 0) {
            switch (p->mType) {
            case 1:
            case 7:
                if (p->mId28 == sel && target != 0 && ((*(uint32_t*)((char*)target + 0xb58) >> 9) & 1))
                    Sub1ae10((int)p, 0, 0);
                break;
            case 6:
            case 10: {
                int other;
                if (p->mId28 == sel)
                    other = p->mId2c;
                else if (p->mId2c == sel)
                    other = p->mId28;
                else
                    break;

                bool bl = (*(int*)((char*)target + 0x1c) == other);
                Creature* cr = (Creature*)target;
                for (int i = cr->Count(); i != -1; i = cr->Next(i)) {
                    if (bl)
                        break;
                    bl = false;
                    void* obj = cr->At(i);
                    if (obj) {
                        void* res = ((FnPI)(*(void***)obj)[0xc / 4])(obj, 0x17f243b);
                        if (res && *(int*)((char*)res + 0x1c) == other)
                            bl = true;
                    }
                }
                if (!bl)
                    break;

                if (p->mType == 6) {
                    Sub1ae10((int)p, 0, 0);
                } else {
                    void* g = *(void**)&g_16c7aa4_s00f1_bcf0;
                    void* reg = *(void**)((char*)g + 0x7c);
                    if (reg)
                        *(int*)((char*)reg + 0xc) = (int)(((char*)p - (char*)mBegin64) / 0x1ac);
                    cString_s00f1_bcf0 cs;
                    uint32_t nameId = (p->mType == 10) ? 0x796cfe1
                                    : (p->mType == 0xb)  ? 0x796cfe5 : 0x796d59a;
                    cs.Load(0x21851ebe, nameId, 0);
                    const wchar_t* t = cs.GetText();
                    mText54.assign(t, wend(t));
                    mFieldB0 = 2;
                    Sub1aae0(6);
                }
                break;
            }
            default:
                break;
            }
        }
        p = (Rec1ac*)((char*)p + 0x1ac);
    } while (p != e);
}

// @ 0x00f1c030
int cSPEditorVerbTray::FindPair(int a, int b, char c, int* out1, int* out2)
{
    void* g = *(void**)&g_16c7aa4_s00f1_bcf0;
    G74* g74 = (G74*)*(void**)((char*)g + 0x74);

    Vec v1; Vec v2;
    g74->Fill(a, &v1);
    g74->Fill(b, &v2);

    int n1 = (int)((char*)v1.mpEnd - (char*)v1.mpBegin) >> 2;
    int n2 = (int)((char*)v2.mpEnd - (char*)v2.mpBegin) >> 2;

    if (n1 > 0 && n2 > 0) {
        bool f1 = false;
        {
            void* p = g74->Lookup(a);
            bool bl = false;
            if (p) {
                if (g74->Test(p) && *(char*)(mFieldB8 * 0x4e0 + 2 + *(int*)((char*)p + 0x70)) != 0)
                    bl = true;
            }
            f1 = (c != 0) && bl;
        }
        bool f2 = false;
        {
            void* p = g74->Lookup(b);
            bool bl = false;
            if (p) {
                if (g74->Test(p) && *(char*)(mFieldB8 * 0x4e0 + 2 + *(int*)((char*)p + 0x70)) != 0)
                    bl = true;
            }
            f2 = (c != 0) && bl;
        }

        for (int i = 0; i < n1; ++i) {
            void* o1 = v1.mpBegin[i];
            if (!o1)
                continue;
            void* q1 = ((FnPI)(*(void***)o1)[0xc / 4])(o1, 0x13f94d4);
            if (q1 && ((Combatant*)q1)->GetDamageState() == 2 && f1)
                continue;
            void* r1 = ((FnPI)(*(void***)o1)[0xc / 4])(o1, 0x1186577);
            if (!r1)
                continue;
            for (int j = 0; j < n2; ++j) {
                void* o2 = v2.mpBegin[j];
                if (o1 == o2 || !o2)
                    continue;
                void* q2 = ((FnPI)(*(void***)o2)[0xc / 4])(o2, 0x13f94d4);
                if (q2 && ((Combatant*)q2)->GetDamageState() == 2 && f2)
                    continue;
                void* r2 = ((FnPI)(*(void***)o2)[0xc / 4])(o2, 0x1186577);
                if (!r2)
                    continue;
                if (FUN_00f3c870(r1, r2, *(float*)0x15ad944, 0)) {
                    if (out1)
                        *out1 = (int)r1;
                    if (out2)
                        *out2 = (int)r2;
                    v2.~Vec();
                    v1.~Vec();
                    return 1;
                }
            }
        }
    }

    for (void** p = v2.mpBegin; p < v2.mpEnd; ++p)
        if (*p)
            ((FnV)(*(void***)*p)[0x4 / 4])(*p);
    if (v2.mpBegin && ((int*)v2.mpBegin)[-1] != 0)
        operator_delete(v2.mpBegin);
    for (void** p = v1.mpBegin; p < v1.mpEnd; ++p)
        if (*p)
            ((FnV)(*(void***)*p)[0x4 / 4])(*p);
    if (v1.mpBegin && ((int*)v1.mpBegin)[-1] != 0)
        operator_delete(v1.mpBegin);
    return 0;
}

// @ 0x00f1c2f0
void cSPEditorVerbTray::Toggle()
{
    void* audio = EA_GetSystemAT();
    if (audio) {
        ((FnVI)(*(void***)audio)[0x38 / 4])(audio, 0x7f43dd0);
        ((FnV)(*(void***)audio)[0x58 / 4])(audio);
    }

    void* pcc = mFieldCc;
    int arg;
    if (pcc != 0)
        arg = (int)((FnPI)(*(void***)pcc)[0xc / 4])(pcc, 0x1186577);
    else
        arg = 0;
    Sub1ae10(mFieldC8, arg, 0);

    void* avatar = ((NounManager*)SP_NounManager())->GetAvatar();
    void* cr;
    if (avatar != 0)
        cr = ((FnPI)(*(void***)avatar)[0xc / 4])(avatar, 0xce9f6639);
    else
        cr = 0;

    ((CreatureBase*)cr)->Show();

    int i = 0;
    int n = ((CreatureBase*)cr)->Count2();
    for (; i < n; ++i) {
        void* obj = ((CreatureBase*)cr)->At(i);
        if (!obj)
            continue;
        void* a = ((FnPI)(*(void***)obj)[0xb8 / 4])(obj, 0x3a25119);
        if (a) {
            ((FnVI)(*(void***)a)[0x60 / 4])(a, 1);
        } else {
            void* b = ((FnPI)(*(void***)obj)[0xb8 / 4])(obj, 0x17f243b);
            if (!b || *(int*)((char*)b + 0x14) == 0)
                continue;
            ((FnVI)(*(void***)*(void**)((char*)b + 0x14))[0x10 / 4])(*(void**)((char*)b + 0x14), 1);
        }
    }

    int cont = *(int*)((char*)cr + 0xb54);
    int tree = *(int*)((char*)cont + 0x17c);
    void** root = *(void***)((char*)tree + 0x17a4);
    void* node = *root;
    if (node == 0) {
        ++root;
        while (*root == 0)
            ++root;
        node = *root;
    }
    void* endNode = (*(void***)((char*)tree + 0x17a4))[*(int*)((char*)tree + 0x17a8)];
    while (node != endNode) {
        void* r = *(void**)(*(int*)((char*)node + 4) + 0x8c);
        if (r && ((FnC)(*(void***)r)[0x10 / 4])(r)) {
            ((FnVI)(*(void***)r)[0x2c / 4])(r, 0);
            ((FnVI)(*(void***)r)[0x30 / 4])(r, 0);
        }
        node = *(void**)((char*)node + 8);
        while (node == 0) { ++root; node = *root; }
    }

    void* tgt = ((CreatureBase*)cr)->GetTargetAsCreature();
    if (tgt)
        ((FnVIII)(*(void***)tgt)[0x84 / 4])(tgt, 0, 0, 0);
    ((FnVIII)(*(void***)cr)[0x84 / 4])(cr, 0, 0, 0);
}

// @ 0x00f1c4b0
bool cSPEditorVerbTray::Step()
{
    void* g = *(void**)&g_16c7aa4_s00f1_bcf0;
    G74* g74 = (G74*)*(void**)((char*)g + 0x74);

    uint32_t n = (uint32_t)(((char*)mEnd68 - (char*)mBegin64) / 0x1ac);
    char found = 1;
    uint32_t count = 0;
    if (n != 0) {
        uint32_t off = 0;
        do {
            if (!found)
                return 0;
            Rec1ac* p = (Rec1ac*)((char*)mBegin64 + off);
            if (p->mFlag == 0) {
                if (!g74->Query3((char*)p + 0x24, mFieldB8, p)) {
                    int type = p->mType;
                    int t = 3;
                    if (type == 10 || type == 0xb)
                        t = 2;
                    Sub1b730((int)count, p, t);
                    found = 0;
                    goto next;
                }
            }
            /* LAB: */
            {
                if (count != 0) {
                    for (uint32_t j = 0; j < count; ++j) {
                        if (g74->Cmp2((char*)p + 0x24, (char*)((char*)mBegin64 + j * 0x1ac) + 0x24)) {
                            mFieldB0 = 4;
                            cString_s00f1_bcf0 cs;
                            cs.Load(0x21851ebe, 0x7c50b5f, 0);
                            const wchar_t* t = cs.GetText();
                            mText54.assign(t, wend(t));
                            Sub1aae0(6);
                            found = 0;
                            goto next;
                        }
                    }
                }
            }
        next:
            off += 0x1ac;
            ++count;
        } while (count < n);
        if (!found)
            return 0;
    }

    if (g74->Find(mFieldB8, 0, -1, &n, &mBegin64)) {
        int idx = (int)n;
        Rec1ac* p = (Rec1ac*)((char*)mBegin64 + idx * 0x1ac);
        int type = p->mType;
        int t = 3;
        if (type == 10 || type == 0xb)
            t = 2;
        Sub1b730(idx, p, t);
        return 0;
    }
    return found;
}

// @ 0x00f1dfa0
void GoalVec::destroyRange(Goal* first, Goal* last)
{
    if (first >= last)
        return;
    do {
        first->act.vec.destroy();
        first->map.destroy();
        first += 1;
    } while (first < last);
}

// @ 0x00f1e020
void ReadConfig()
{
    void* t = ((TerrainMgr*)SP_TerrainMgr())->GetTerrain();
    if (t) {
        void* prop;
        PROP(0x6d95f3cc, 0xd, gT924)
        PROP(0x75960042, 0xd, gT928)
        PROP(0x557d26dd, 0xd, gT92c)
        PROP(0x5d7d3333, 0xd, gT930)
        PROP(0xf1088439, 0xd, gT934)
        PROP(0xe90877c7, 0xd, gT938)
        PROP(0xf5a523fa, 0xd, gT93c)
        PROP(0x11fbb285, 0xd, gT940)
        PROP(0x4c764f09, 0xd, gT944)
        PROP(0x5830f113, 0xd, gT948)
        if (GETPROP(t, 0xc4331ecc, &prop) && *(short*)((uint8_t*)prop + 0x12) == 0xa) {
            gT94c = *SP_GetPropertyAsUInt(prop);
        }
        if (GETPROP(t, 0x9944b6fb, &prop) && *(short*)((uint8_t*)prop + 0x12) == 0xa) {
            gT950 = *SP_GetPropertyAsUInt(prop);
        }
        if (GETPROP(t, 0x5356e603, &prop) && *(short*)((uint8_t*)prop + 0x12) == 0xa) {
            gT954 = *SP_GetPropertyAsUInt(prop);
        }

        unsigned n = 0;
        void* data = 0;
        FUN_006a0b50(t, 0x10f28fd, (int*)&n, &data);
        StringVec__resize(&gT82bc, n);
        FUN_00f1dcc0(&gT82bc, data, (char*)data + (n << 4));

        n = 0; data = 0;
        FUN_006a0b50(t, 0x3ddba715, (int*)&n, &data);
        StringVec__resize(&gT82d0, n);
        FUN_00f1dcc0(&gT82d0, data, (char*)data + (n << 4));

        n = 0; data = 0;
        FUN_006a0b50(t, 0xb7afd508, (int*)&n, &data);
        StringVec__resize(&gT82e4, n);
        FUN_00f1dcc0(&gT82e4, data, (char*)data + (n << 4));

        n = 0; data = 0;
        FUN_006a0b50(t, 0x5a651c41, (int*)&n, &data);
        StringVec__resize(&gT82f8, n);
        FUN_00f1dcc0(&gT82f8, data, (char*)data + (n << 4));

        PROP(0x92c289d3, 0xd, gT958)
        PROP(0x8ea88cc3, 0xd, gT95c)
    }
}

// @ 0x00f1e450
Bar::Bar()
{
    char* p = (char*)this;
    v04 = gBaseVtbl1;
    v08 = 0;
    v00 = gBarVtbl0;
    v04 = gBarVtbl1;
    *(void**)(p + 0x0c) = 0;
    *(void**)(p + 0x10) = 0;
    *(void**)(p + 0x14) = 0;
    *(void**)(p + 0x18) = 0;
    *(void**)(p + 0x1c) = 0;
    *(void**)(p + 0x20) = 0;
    *(void**)(p + 0x24) = 0;
    *(void**)(p + 0x28) = 0;
    *(void**)(p + 0x2c) = 0;
    *(void**)(p + 0x30) = 0;
    *(void**)(p + 0x34) = 0;
    *(void**)(p + 0x38) = 0;
    *(void**)(p + 0x3c) = 0;
    *(void**)(p + 0x40) = 0;
    *(void**)(p + 0x44) = 0;
    *(float*)(p + 0x48) = 0.0f;
    *(float*)(p + 0x4c) = 0.0f;
    *(float*)(p + 0x50) = 0.0f;
    *(void**)(p + 0x5c) = gEmptyString16 + 2;
    *(void**)(p + 0x54) = gEmptyString16;
    *(void**)(p + 0x58) = gEmptyString16;
    *(void**)(p + 0x64) = 0;
    *(void**)(p + 0x68) = 0;
    *(void**)(p + 0x6c) = 0;
    ((Stopwatch*)sw98)->Init(0, 0);
    *(void**)(p + 0x7c) = 0;
    *(void**)(p + 0x80) = 0;
    *(void**)(p + 0x84) = 0;
    *(void**)(p + 0x88) = 0;
    *(void**)(p + 0x8c) = 0;
    *(void**)(p + 0xbc) = 0;
    *(void**)(p + 0xc0) = 0;
    *(float*)(p + 0xdc) = 0.0f;
    *(float*)(p + 0xe0) = gCfg0;
    *(float*)(p + 0xe4) = gCfg1;
    *(float*)(p + 0xe8) = gCfg2;
    *(uint8_t*)(p + 0xec) = 0;
    *(void**)(p + 0xf0) = 0;
    *(void**)(p + 0xf4) = 0;
    *(uint8_t*)(p + 0xfc) = 0;
    *(uint8_t*)(p + 0xfd) = 0;
    *(float*)(p + 0xf8) = 0.0f;
    *(void**)(p + 0x100) = 0;
}

// @ 0x00f1e580
Bar::~Bar()
{
    if (f100)
        ((BarIface*)f100)->vt04();
    if (f7c) {
        void* h = f7c;
        f7c = 0;
        Messaging__RemoveHandler(h, f80, f84, f88, f8c);
    }
    goals.destroyRange(goals.b, goals.e);
    if (goals.b && ((int*)goals.b)[-1] != 0)
        operator_delete__(goals.b);
    if ((((char*)f5c - (char*)f54) & ~1) > 2 && f54)
        operator_delete__(f54);
    v04 = gBaseVtbl1;
    v00 = gBaseVtbl0;
}

// @ 0x00f1e620
void Bar::Init()
{
    ((Stopwatch*)sw98)->SetUnits(4);
    ReadConfig();
    ffd = 0;
    void* m = SP_MessageServer();
    f7c = m;
    f80 = this;
    f84 = gMsgIdTable;
    f88 = (void*)0x14;
    f8c = 0;
    if (m) {
        uint i = 0;
        do {
            ((MsgSendFn)(*(void**)((char*)(*(void**)m) + 0x24)))(m, this, *(uint*)((char*)gMsgIdTable + i));
            i += 4;
        } while (i < 0x50);
    }
    Reset();
}

// @ 0x00f1e6a0
void Bar::Scans()
{
    // creature-base pass
    {
        uint8_t* v = (uint8_t*)GetGameDataVector(SP_NounManager(), 0xcd7d10, 0xd3d420,
                                            0xae72d0, 0xb1e500, 0x18c6de8);
        void** b = (void**)(v + 4);
        void** e = (void**)(v + 8);
        for (void** i = b; i != e; ++i) {
            uint8_t* o = (uint8_t*)*i;
            FUN_00ca6db0(o);
            EachChild2(o ? o + 0x508 : 0);
        }
    }
    // creature pass (skipping the active one)
    {
        void* active = FUN_00989360(SP_NounManager());
        uint8_t* v = (uint8_t*)GetGameDataVector(SP_NounManager(), 0xcd7d10, 0xd3d420,
                                            0xace0f0, 0xb1e500, 0x18eb45e);
        void** b = (void**)(v + 4);
        void** e = (void**)(v + 8);
        for (void** i = b; i != e; ++i) {
            uint8_t* o = (uint8_t*)*i;
            if (FUN_00c04590(o) != active) {
                FUN_00c06f70(o);
                EachChild2(o ? o + 0x5a8 : 0);
            }
        }
    }
    // space-inventory pass
    {
        uint8_t* v = (uint8_t*)GetGameDataVector(SP_NounManager(), 0xcd7d10, 0xd3d420,
                                            0xb5f990, 0xb1e520, 0x70704db);
        void** b = (void**)(v + 4);
        void** e = (void**)(v + 8);
        for (void** i = b; i != e; ++i) {
            uint8_t* o = (uint8_t*)*i;
            uint8_t* q = o ? (uint8_t*)(*(void*(**)(uint8_t*, int))((char*)(*(void**)o) + 0xc))(o, 0x70704db) : 0;
            (*(void(**)(uint8_t*))((char*)(*(void**)q) + 0x90))(q);
            EachChild2(q + 0x120);
        }
    }
}

// @ 0x00f1e810
Goal& Goal::operator=(const Goal& s)
{
    b0 = s.b0;
    b1 = s.b1;
    i4 = s.i4;
    map = s.map;
    act.f0 = s.act.f0;
    act.f4 = s.act.f4;
    act.f8 = s.act.f8;
    act.fc = s.act.fc;
    act.f10 = s.act.f10;
    act.f14 = s.act.f14;
    act.vec.assignFrom(s.act.vec);
    act.f184 = s.act.f184;
    return *this;
}

// @ 0x00f1e880
Goal* MoveRangeUninit(Goal* first, Goal* last, Goal* out)
{
    if (first != last) {
        do {
            if (out) {
                out->b0 = first->b0;
                out->b1 = first->b1;
                out->i4 = first->i4;
                out->map.Construct(first->map);
                out->act.f0 = first->act.f0;
                out->act.f4 = first->act.f4;
                out->act.f8 = first->act.f8;
                out->act.fc = first->act.fc;
                out->act.f10 = first->act.f10;
                out->act.f14 = first->act.f14;
                out->act.vec.Construct(first->act.vec);
                out->act.f184 = first->act.f184;
            }
            first += 1;
            out += 1;
        } while (first != last);
        return out;
    }
    return out;
}

// @ 0x00f1e940
Goal* MoveRangeAssign(Goal* first, Goal* last, Goal* out)
{
    if (first != last) {
        do {
            *out = *first;
            first += 1;
            out += 1;
        } while (first != last);
        return out;
    }
    return out;
}

// @ 0x00f1e9f0
Goal* MoveRangeBack(Goal* first, Goal* last, Goal* out)
{
    if (last != first) {
        do {
            last -= 1;
            out -= 1;
            out->b0 = last->b0;
            out->b1 = last->b1;
            out->i4 = last->i4;
            out->map = last->map;
            out->act.f0 = last->act.f0;
            out->act.f4 = last->act.f4;
            out->act.f8 = last->act.f8;
            out->act.fc = last->act.fc;
            out->act.f10 = last->act.f10;
            out->act.f14 = last->act.f14;
            out->act.vec.assignFrom(last->act.vec);
            out->act.f184 = last->act.f184;
        } while (last != first);
        return out;
    }
    return out;
}

// @ 0x00f1eaa0
void GoalVec::Insert(Goal* pos, const Goal& val)
{
    Goal* end = e;
    if (end != c) {
        if (pos <= &val && &val < end)
            pos += 1;
        if (end) {
            end->b0 = end[-1].b0;
            end->b1 = end[-1].b1;
            end->i4 = end[-1].i4;
            end->map.Construct(end[-1].map);
            end->act.Construct(end[-1].act);
        }
        MoveRangeBack(pos, e - 1, e);
        *pos = val;
        e = e + 1;
        return;
    }
    int n = (int)((e - b) / 0x1ac);
    int cap;
    void* mem;
    if (n == 0) {
        cap = 1;
    } else {
        cap = n * 2;
        if (cap == 0) {
            mem = 0;
            goto alloc_done;
        }
    }
    mem = Alloc(cap * 0x1ac, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
alloc_done:
    Goal* raw = (Goal*)mem;
    Goal* newEnd = MoveRangeUninit(b, pos, raw);
    DestroyActRange((ActStep*)b, (ActStep*)pos);
    if (newEnd) {
        newEnd->b0 = val.b0;
        newEnd->b1 = val.b1;
        newEnd->i4 = val.i4;
        newEnd->map.Construct(val.map);
        newEnd->act.Construct(val.act);
    }
    Goal* last = e;
    Goal* ret = MoveRangeUninit(pos, last, newEnd + 1);
    DestroyActRange((ActStep*)pos, (ActStep*)last);
    if (b && ((int*)b)[-1] != 0)
        operator_delete__(b);
    b = raw;
    e = ret;
    c = (Goal*)((char*)raw + cap * 0x1ac);
}

// @ 0x00f1ec50
void GoalVec::emplace_back()
{
    char tmpbuf[0x1ac];
    Goal* p = e;
    if (p < c) {
        e = p + 1;
        if (p)
            InitGoal(p);
        return;
    }
    Goal* t = (Goal*)tmpbuf;
    InitGoal(t);
    Insert(e, *t);
    t->destroy();
}

// @ 0x00f1ecf0
void Bar::Update()
{
    Goal* ob = goals.b;
    Goal* oe = goals.e;
    Goal* r = MoveRangeAssign(oe, oe, ob);
    goals.destroyRange(r, goals.e);
    goals.e += (oe - ob);

    uint8_t* base = (uint8_t*)this;
    base[0x78] = 0;
    base[0x79] = 0;
    fdc = gFtoc;
    fe0 = gCfg0;
    fe4 = gCfg1;
    fe8 = gCfg2;

    if ((char*)f54 != (char*)f58) {
        *(short*)f54 = 0;
        f58 = f54;
    }

    void* host = *(void**)((char*)gStartup + 0x74);
    void* act = ((ActHost*)host)->GetAct(fb8);
    if (act) {
        uint8_t* a = (uint8_t*)act;
        *(int*)(base + 0xbc) = *(int*)(a + 0x78) * 1000;
        uint8_t* ei = *(uint8_t**)(a + 0x84);
        uint8_t* ee = *(uint8_t**)(a + 0x88);
        int idx = 0;
        int goalOff = 0;
        if (ei != ee) {
            do {
                goals.emplace_back();
                uint8_t* g = (uint8_t*)goals.e - 0x1ac;
                g[0x00] = 0;
                g[0x01] = FUN_00f3b390(*(void**)ei);
                *(int*)(g + 0x04) = 0;
                *(void**)(g + 0x24) = *(void**)(ei + 0x00);
                *(void**)(g + 0x28) = *(void**)(ei + 0x04);
                *(void**)(g + 0x2c) = *(void**)(ei + 0x08);
                *(void**)(g + 0x30) = *(void**)(ei + 0x0c);
                g[0x34] = ei[0x10];
                *(void**)(g + 0x38) = *(void**)(ei + 0x14);
                *(Vec44*)(g + 0x3c) = *(Vec44*)(ei + 0x18);
                *(void**)(g + 0x1a8) = *(void**)(ei + 0x184);
                if (*(int*)(ei + 0x0c) == 0) {
                    void* p = ((ActHost*)host)->FindCreature(*(void**)(ei + 0x04));
                    if (p == 0 || ((CreatureObj*)p)->IsMarked() == 0) {
                        void* rr = ((ActHost*)host)->BuildGoal(fb8, ei, *(void**)(ei + 4), g, 0, 0, 0, 1);
                        *(void**)(g + 0x30) = rr;
                    }
                }
                if (*(int*)(g + 0x24) == 8) {
                    if (*(int*)(g + 0x30) != 1)
                        *(int*)(g + 0x30) = 1;
                    int cnt = 0;
                    void* c = EachChild(*(void**)(ei + 4), (int)&cnt);
                    if (c) {
                        AddGoal8(g, c, 0);
                        if (cnt > 1)
                            *(int*)(g + 0x04) += cnt - 1;
                    }
                }
                if (*(int*)(g + 0x24) == 5) {
                    uint8_t* inv = (uint8_t*)((Inventory*)SP_NounManager())->GetItemID();
                    int cnt = (int)(*(uint8_t**)(inv + 4) - *(uint8_t**)inv) >> 2;
                    for (int j = 0; j < cnt; ++j) {
                        uint8_t* it = *(uint8_t**)(*(uint8_t**)inv + j * 4);
                        if (*(int*)(it + 0x1c) == *(int*)(g + 0x28)) {
                            void* rv = ((ItemObj*)it)->v3(0x1186577, 0);
                            AddGoal5(g, rv);
                        }
                    }
                }
                int total = (int)(goals.e - goals.b);
                int g24 = *(int*)((char*)goals.b + goalOff + 0x24);
                if (idx < total && (g24 == 10 || g24 == 11))
                    base[0x79] = 1;
                else
                    base[0x78] = 1;
                ++idx;
                goalOff += 0x1ac;
                ei += 0x188;
            } while (ei != ee);
        }
    }
}

// @ 0x00f1faa0
void Ctl::Update(uint32_t dt)
{
    char on = FUN_00401030()->flag1c;
    if (on) {
        if (!fb4) {
            cGameTimeManager* g = FUN_00b3d380();
            g->IncPauseGate(0x4bf38a7);
        }
    } else if (fb4) {
        cGameTimeManager* g = FUN_00b3d380();
        g->DecPauseGate(0x4bf38a7);
    }
    fb4 = on;
    FUN_00f1f600();

    switch (state) {
    case 1:
        if (ffc) {
            float fdt = (float)dt;
            ff8 = ff8 - fdt;
            Avatar* av = FUN_00b3d300()->GetAvatar();
            if (av) {
                if (ff8 > 0.0f) {
                    av->comp->f80 = (1.0f / g_015ad948) * (float)dt + av->comp->f80;
                    return;
                }
                av->comp->f80 = 1.0f;
                av->flags &= 0xfffff7ff;
                ModelManagerT* mm = FUN_0067dd80();
                AvatarComp* comp = av->comp;
                uint32_t idx = mm->GetIndex(0x6669387, 0);
                if (idx < 0x40) {
                    uint32_t* w = (uint32_t*)(comp->bits + 0x44) + (idx >> 5);
                    *w &= ~(1u << (idx & 0x1f));
                }
                ffc = 0;
                AvatarComp2* sub = av->comp->sub;
                GlyphTable* tbl = &sub->glyphs;
                GlyphIterator it = tbl->begin();
                void* end = tbl->buckets[tbl->nBuckets];
                while (it.node != end) {
                    GlyphObj* o = ((GlyphNode*)it.node)->val->obj;
                    if (o && o->IsActive()) {
                        o->SetA(0);
                        o->SetB(0);
                    }
                    ++it;
                }
            }
        }
        break;
    case 2:
    case 4:
        break;
    case 3: {
        int st = FUN_00b3d4d0()->state;
        if (st != 1 && st != 2 && !fb4) {
            fc0 += dt;
            if (fbc > 0) {
                int v = fbc - dt;
                fbc = v;
                if (v <= 0) {
                    if (f78) {
                        FUN_00f1b640(1);
                        FUN_00f1aae0(6);
                    } else {
                        FUN_00f1f3b0();
                    }
                } else {
                    cUICard* c = g_UIRoot->panels->card;
                    if (c)
                        ((cMissionPanel*)c)->FUN_00e16a70(true);
                }
            }
        }
        if (!ffd && fc0 > 1000) {
            FUN_00ef73c0();
            ffd = 1;
        }
        break;
    }
    case 5: {
        if (f94 == 0) {
            cGameTimeManager* gtm = FUN_00b3d380();
            if (sw.GetElapsedTime() > (uint64_t)g_015ad94c && eff.p == 0) {
                g_UIRoot->panels->FUN_00f0e4a0(0);
                cUICard* c = g_UIRoot->panels->card;
                if (c) c->SetVisible(0);
                EffectsManagerT* em = FUN_0067ddd0();
                if (em->GetEffect(0x63ef90d9, 0, eff.AsPPTypeParam()))
                    eff.p->v2(1);
            }
            if (sw.GetElapsedTime() > (uint64_t)g_015ad950) {
                if (!gtm->FUN_00f18ff0())
                    gtm->IncPauseGate(0x4bf38a7);
            }
            if (sw.GetElapsedTime() > (uint64_t)g_015ad954) {
                gtm->DecPauseGate(0x4bf38a7);
                if (eff.p) {
                    eff.p->v3(0);
                    IVisualEffect* o = eff.p;
                    if (o) { eff.p = 0; o->Release(); }
                }
                sw.Stop();
                FUN_00b3d4d0()->FUN_00ad7e90(1);
                uint32_t i = g_Random.RandomUint32Uniform(g_016c82d4 - g_016c82d0);
                uint32_t id = g_016c82d0[i].id;
                FUN_00b3d4d0()->PostTrigger(id, 1, 0, 0, 0, 1);
                TrigData d;
                d.a = 0x7be2d40;
                d.b = 0;
                d.c = 0x21851ebe;
                FUN_00b3d4d0()->FUN_00adde90(0x498b0990, &d, 0);
                f94 = 1;
            }
        }
        break;
    }
    case 6: {
        if (f94 == 0) {
            cGameTimeManager* gtm = FUN_00b3d380();
            if (sw.GetElapsedTime() > (uint64_t)g_015ad94c && eff.p == 0) {
                g_UIRoot->panels->FUN_00f0e4a0(0);
                cUICard* c = g_UIRoot->panels->card;
                if (c) c->SetVisible(0);
                EffectsManagerT* em = FUN_0067ddd0();
                if (em->GetEffect(0x63ef90d9, 0, eff.AsPPTypeParam()))
                    eff.p->v2(1);
            }
            if (sw.GetElapsedTime() > (uint64_t)g_015ad950) {
                if (!gtm->FUN_00f18ff0())
                    gtm->IncPauseGate(0x4bf38a7);
            }
            if (sw.GetElapsedTime() > (uint64_t)g_015ad954) {
                gtm->DecPauseGate(0x4bf38a7);
                if (eff.p) {
                    eff.p->v3(0);
                    IVisualEffect* o = eff.p;
                    if (o) { eff.p = 0; o->Release(); }
                }
                sw.Stop();
                FUN_00b3d4d0()->FUN_00ad7e90(1);
                uint32_t id;
                if (fb0 == 0) {
                    uint32_t i = g_Random.RandomUint32Uniform(g_016c82fc - g_016c82f8);
                    id = g_016c82f8[i].id;
                } else {
                    uint32_t i = g_Random.RandomUint32Uniform(g_016c82e8 - g_016c82e4);
                    id = g_016c82e4[i].id;
                }
                FUN_00b3d4d0()->PostTrigger(id, 1, 0, 0, 0, 1);
                TrigData d;
                d.a = 0x7be2d41;
                d.b = 0;
                d.c = 0x21851ebe;
                FUN_00b3d4d0()->FUN_00adde90(0xa93873, &d, 0);
                f94 = 1;
            }
        }
        break;
    }
    }
}
