// match/slices/s00d0a160/s00d0a160.cpp
// Object file: SPEditors/SPCommunityEditor.obj (SP::cCommunityEditor).
// Functions: 00d0a160 00d0a1e0 00d0a390 00d0a3f0 00d0a470 00d0a540 00d0a5b0
//            00d0a630 00d0a670 00d0a6e0 00d0a760 00d0aa70 00d0abd0 00d0ae50
//            00d0b010
// Flags: /O2 /MD /Gy /EHsc /TP   (scalar FP is x87: no /arch:SSE2)
//
// The editor object's retail layout is only partly known, so it is modelled
// here with local role+offset stub structs. Every field is named by role.

typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   SIZE_T;

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };

// ---------------------------------------------------------------------------
// Ref-counted object: slot 0 AddRef, slot 1 Release.
// ---------------------------------------------------------------------------
struct RefCnt {
  virtual void  AddRef();               // 0x00
  virtual void  Release();              // 0x04
};

// ---------------------------------------------------------------------------
// A UI window. Slot offsets are the retail vtable byte offsets.
// ---------------------------------------------------------------------------
struct IWindow {
  virtual void  AddRef();               // 0x00
  virtual void  Release();              // 0x04
  virtual void  Slot08();               // 0x08
  virtual void* Slot0c(u32 id);         // 0x0c (query interface)
  virtual void  Slot10();               // 0x10
  virtual void  Slot14(s32 v);          // 0x14
  virtual void  Slot18();               // 0x18
  virtual void  Slot1c(s32 v);          // 0x1c (is-max-value query)
  virtual void  Slot20();               // 0x20
  virtual void  Slot24();               // 0x24
  virtual void  Slot28();               // 0x28
  virtual void  Slot2c();               // 0x2c
  virtual void* Slot30();               // 0x30
  virtual void  Slot34();               // 0x34
  virtual Vec4* Slot38();               // 0x38 (area/rect accessor)
  virtual void  Slot3c(void* a, s32 b);  // 0x3c
  virtual void  Slot40();               // 0x40
  virtual void  Slot44();               // 0x44
  virtual void  Slot48();               // 0x48
  virtual void  Slot4c();               // 0x4c
  virtual void  Slot50();               // 0x50
  virtual void  Slot54();               // 0x54
  virtual void  Slot58(s32 v, void* p);  // 0x58
  virtual void  Slot5c(s32 v, void* p);  // 0x5c
  virtual void  Slot60();               // 0x60
  virtual void  Slot64();               // 0x64
  virtual void  Slot68();               // 0x68
  virtual void  Slot6c(Vec4* v);        // 0x6c
  virtual void  Slot70();               // 0x70
  virtual void  Slot74();               // 0x74
  virtual void  Slot78(s32 v);          // 0x78
  virtual void  Slot7c(s32 a, s32 b);   // 0x7c
  virtual void  Slot80();               // 0x80
  virtual void  Slot84();               // 0x84
  virtual void  Slot88();               // 0x88
  virtual void  Slot8c();               // 0x8c
  virtual void  Slot90();               // 0x90
  virtual void  Slot94();               // 0x94
  virtual void  Slot98();               // 0x98
  virtual void  Slot9c();               // 0x9c
  virtual void  SlotA0();               // 0xa0
  virtual void  SlotA4();               // 0xa4
  virtual void  SlotA8();               // 0xa8
  virtual void  SlotAc();               // 0xac
  virtual void  SlotB0();               // 0xb0
  virtual void  SlotB4();               // 0xb4
  virtual void* SlotB8(u32 id);         // 0xb8
  virtual void  SlotBc();               // 0xbc
  virtual void  SlotC0();               // 0xc0
  virtual void  SlotC4();               // 0xc4
  virtual void  SlotC8();               // 0xc8
  virtual void  SlotCc();               // 0xcc
  virtual void  SlotD0();               // 0xd0
  virtual void  SlotD4();               // 0xd4
  virtual void  SlotD8(void* p);        // 0xd8
  virtual void  SlotDc();               // 0xdc
  virtual void  SlotE0();               // 0xe0
  virtual void  SlotE4();               // 0xe4
  virtual void  SlotE8();               // 0xe8
  virtual void  SlotEc();               // 0xec
  virtual void  SlotF0();               // 0xf0
  virtual void  SlotF4();               // 0xf4
  virtual void  SlotF8();               // 0xf8
  virtual void  SlotFc();               // 0xfc
  virtual void  Slot100();              // 0x100
  virtual void  Slot104(void* handler); // 0x104 (set win proc)
};

// ---------------------------------------------------------------------------
// A UI property object (property list / key instance).
// ---------------------------------------------------------------------------
struct IProperty {
  virtual void  AddRef();                    // 0x00
  virtual void  Release();                   // 0x04
  virtual void  Slot08();                    // 0x08
  virtual void* Slot0c(u32 id);              // 0x0c
  virtual void  Slot10();                    // 0x10
  virtual void  Slot14(u32 id, void* var);   // 0x14
  virtual void  Slot18();                    // 0x18
  virtual u8    Slot1c(u32 id);              // 0x1c
  virtual void  Slot20();                    // 0x20
  virtual void  Slot24();                    // 0x24
  virtual void  Slot28();                    // 0x28
  virtual u8    Slot2c(u32 a, u32 b, void** out);  // 0x2c
  virtual void  Slot30();                    // 0x30
  virtual void  Slot34();                    // 0x34
  virtual void  Slot38();                    // 0x38
  virtual void  Slot3c();                    // 0x3c
  virtual void  Slot40();                    // 0x40
  virtual void  Slot44();                    // 0x44
  virtual void  Slot48();                    // 0x48
  virtual void  Slot4c();                    // 0x4c
  virtual void  Slot50();                    // 0x50
  virtual void  Slot54();                    // 0x54
  virtual u32   Slot58();                    // 0x58
  virtual float Slot5c();                    // 0x5c
  virtual void  Slot60();                    // 0x60
  virtual void  Slot64();                    // 0x64
  virtual void  Slot68();                    // 0x68
  virtual void  Slot6c();                    // 0x6c
  virtual void  Slot70();                    // 0x70
  virtual void  Slot74();                    // 0x74
  virtual void  Slot78();                    // 0x78
  virtual void  Slot7c();                    // 0x7c
  virtual void  Slot80();                    // 0x80
  virtual void  Slot84();                    // 0x84
  virtual void  Slot88();                    // 0x88
  virtual void  Slot8c();                    // 0x8c
  virtual void  Slot90();                    // 0x90
  virtual void  Slot94();                    // 0x94
  virtual void  Slot98();                    // 0x98
  virtual void  Slot9c();                    // 0x9c
  virtual void  SlotA0();                    // 0xa0
  virtual void  SlotA4();                    // 0xa4
  virtual void  SlotA8();                    // 0xa8
  virtual void  SlotAc();                    // 0xac
  virtual void  SlotB0();                    // 0xb0
  virtual void  SlotB4();                    // 0xb4
  virtual void* SlotB8(u32 id);              // 0xb8
};

// ---------------------------------------------------------------------------
// A sellback rollover / detached rollover widget.
// ---------------------------------------------------------------------------
struct IRollover {
  virtual void  Show(void* window);     // 0x00
  virtual void  Release();              // 0x04
  virtual void  Slot08();               // 0x08
};

// Window manager singleton.
struct IWindowMgr {
  virtual void  Slot00();
  virtual void  Slot04();
  virtual void  Slot08();
  virtual void  Slot0c();
  virtual void  Slot10();
  virtual void  Slot14();
  virtual void  Slot18();
  virtual void  Slot1c();
  virtual void  Slot20();
  virtual void  Slot24();
  virtual void  Slot28();
  virtual void  Slot2c();
  virtual void  Slot30();
  virtual void  Slot34();
  virtual void  Slot38();
  virtual void  Slot3c();
  virtual void  Slot40();
  virtual void  Slot44();
  virtual void  Slot48();
  virtual void  Slot4c();
  virtual void  Slot50();
  virtual void  Slot54();
  virtual void  Slot58(s32 v, void* p);   // 0x58
  virtual void  Slot5c(s32 v, void* p);   // 0x5c
};

// The application object.
struct IApp {
  virtual void  Slot00();
  virtual void  Slot04();
  virtual void  Slot08();
  virtual void  Slot0c();
  virtual void  Slot10();
  virtual void  Slot14();
  virtual void  Slot18();
  virtual void* Slot1c(void* a, void* b);  // 0x1c
  virtual void  Slot20();
  virtual void  Slot24();
  virtual void  Slot28();
  virtual void  Slot2c();
  virtual void  Slot30();
  virtual void  Slot34();
  virtual void  Slot38();
  virtual void  Slot3c();
  virtual void  Slot40();
  virtual void  Slot44();
  virtual void  Slot48();
  virtual void  Slot4c();
  virtual void* Slot50();                  // 0x50
};

// The community object (SP::cCommunity) as used here.
struct CommunityStub {
  virtual void* Slot0c(u32 id);          // 0x0c (query interface)
  u8 pad04[0x34 - 0x04];
  IWindow mNameProvider_34;              // 0x34 (embedded provider, slot 1 = name)
};

// A creature/object as seen through the selection list.
struct SelectableObj {
  u8  pad00[0xb1c];
  u32 mKeyA_b1c;                         // 0xb1c
  u32 mKeyB_b20;                         // 0xb20
};

// A game-mode property block returned by PropertyManager().
struct PropMgr {
  virtual void  Slot00();
  virtual void  Slot04();
  virtual void  Slot08();
  virtual void  Slot0c();
  virtual void  Slot10();
  virtual void  Slot14();
  virtual void  Slot18();
  virtual void  Slot1c();
  virtual void  Slot20();
  virtual void  Slot24();
  virtual void  Slot28();
  virtual u8    Slot2c(u32 a, u32 b, void** out);  // 0x2c
};

// A "model type" record (noun definition key pair + property list).
struct ModelType {
  u8  pad00[0x0c];
  u32 mKeyA_0c;                          // 0x0c
  u8  pad10[0x14 - 0x10];
  u32 mKeyB_14;                          // 0x14
};

// The editor's UI layout object (cSPUILayout, 0xc0 bytes).
struct UiLayoutStub {
  u8 pad00[0xc0];
};

// A body of the editor object: a control with an embedded window at +4.
struct WindowCtrl {
  u32     mFlags_00;                     // 0x00
  IWindow mWindow_04;                    // 0x04
};

// A 0x2c-byte value copied by operator= (two refcounted pointers + floats).
struct CopyValue {
  IWindow* mpA_00;                       // 0x00
  IWindow* mpB_04;                       // 0x04
  float    mF_08;                        // 0x08
  float    mF_0c;                        // 0x0c
  float    mF_10;                        // 0x10
  float    mF_14;                        // 0x14
  float    mF_18;                        // 0x18
  float    mF_1c;                        // 0x1c
  u32      mU32_20;                      // 0x20
  u32      mU32_24;                      // 0x24
  u8       mB_28;                        // 0x28

  CopyValue* AssignFrom(const CopyValue* src);   // 0x00d0a670
};

// An ordered-position tree node / tree header used by the map lookup.
struct PosNode {
  PosNode* mpLeft_00;                    // 0x00
  PosNode* mpRight_04;                   // 0x04
  u8       pad08[0x10 - 0x08];
  s32      mKey0_10;                     // 0x10
  s32      mKey1_14;                     // 0x14
};

struct PosTree {
  u32      mCount_00;                    // 0x00
  PosNode* mpSentinel_04;                // 0x04 (header node anchor)
  u32      mFlags_08;                    // 0x08
  PosNode* mpRoot_0c;                    // 0x0c

  void InsertPos(PosNode** out, const s32* key);   // 0x00d0a630
};

// A UI string (SP::cString, 0x10 bytes). Member calls are external.
struct cString {
  u32 mD[4];
  void Ctor();                                 // 0x006b5060
  void Dtor();                                 // 0x006b5240
  bool Load(u32 a, u32 b, s32 c);              // 0x006b54b0
  const u16* GetText();                        // 0x006b55c0
};

struct TooltipLocals {
  u32     mPad_00;                             // 0x00
  cString mStr_04;                             // 0x04
};

// A UI layout: only the lookup entry point is used here.
struct UiLayout {
  u8 mBytes_00[0x1c];                          // 0x00 (cSPUILayout body)
  void* FindWindowByID(u32 id, s32 flag);      // 0x008105b0
};

// The budget display object.
struct BudgetObj {
  void SetText(const u16* text);               // 0x00458b50
};

// The editor itself. Only the fields this slice touches are modelled.
struct cCommunityEditor {
  u8  pad00[0x40];
  CommunityStub* mpCommunity_40;         // 0x40
  u8  pad44[0x6c - 0x44];
  IWindow*  mpBudget_6c;                 // 0x6c (cSPEditorBudget)
  u8  pad70[0x7c - 0x70];
  IRollover* mpSellback_7c;              // 0x7c
  u32        mLimitMode_80;              // 0x80
  IRollover* mpRollover_84;              // 0x84
  UiLayout  mEditorUI_88;                // 0x88 (cSPUILayout, 0x1c bytes here)
  IWindow*   mpVerbIconTray_a4;          // 0xa4
  u8  padA8[0xb0 - 0xa8];
  void*      mpProjector_b0;             // 0xb0
  u8  padB4[0xbc - 0xb4];
  void*      mpRotationRing_bc;          // 0xbc (created noun)
  void*      mpPreviewObject_c0;         // 0xc0
  void*      mpRingDefinition_c4;        // 0xc4
  u8  padC8[0x108 - 0xc8];
  Vec3       mPreviewPos_108;            // 0x108
  u8  pad114[0x1e4 - 0x114];
  Vec3       mWavePos_1e4;               // 0x1e4
  s32*       mpSelectedIds_1f0;          // 0x1f0 (vector begin)
  s32*       mpSelectedEnd_1f4;          // 0x1f4 (vector end)
  u8  pad1f8[0x208 - 0x1f8];
  u8         mFlag_208;                  // 0x208
  u8  pad209[0x2f8 - 0x209];
  WindowCtrl* mpWindowCtrl_2f8;          // 0x2f8
  u8  pad2fc[0x340 - 0x2fc];
  IWindow*   mpBlockerWindow_340;        // 0x340 (embedded window holder)

  u8  CanShowPreview();                  // 0x00d0a160
  void UpdateLimitMeter(s32 mode);       // 0x00d0a1e0
  void RefreshTooltip();                 // 0x00d0a390
  s32  GetSelectedCost(SelectableObj* p); // 0x00d0a3f0
  void ShowRolloverWindows(u32 idA, u32 idB); // 0x00d0a470
  void ShowPlacementCursor();            // 0x00d0a540
  void HidePlacementCursor();            // 0x00d0a5b0
  void Init(u32 const* pLayoutId, u32 propKey, IWindow* pBudget, u8 bFlag); // 0x00d0a760
  void RefreshBuildingCosts();           // 0x00d0aa70
  s32  GetObjectCost(IWindow* pObj, u8 bRefund, u32 typeKey); // 0x00d0abd0
  u32  UpdateVehiclePlacement();         // 0x00d0ae50
  void SetRotationRingVisibility(u8 bShow); // 0x00d0b010
};

extern "C" {
void* __cdecl GetCurrentGameMode();                       // 0xb5b800
void  __cdecl SetBudgetTooltipText(u32 text);             // 0x458b50
void* __cdecl PropertyManager();                          // 0xbd9d10-ish
void* __cdecl MessageServer();                            // 0x67dcc0
void* __cdecl WindowManagerObj();                         // 0x67caa0
void* __cdecl AppObject();                                // SP::App
void* __cdecl NounManagerObj();                           // 0xb3d300
void* __cdecl NounManager(void* noun);                    // 0xb3d300
void  __cdecl NounMgr_RemoveNoun(void* mgr, void* noun);  // 0xb225d0
void* __cdecl NounMgr_CreateNoun(void* mgr, u32 id);      // 0xb20c60
void* __cdecl GetPlayerEmpire();                          // 0x1021300
void* __cdecl SporeAlloc(u32 size, const char* pName, u32 a, u32 b, u32 c, u32 d); // 0xf473a0
void  __cdecl SporeFreeArray(void* p);                    // 0xf47380
s32   __cdecl SPIDFromName(const char* pName, ...);       // variadic id builder
}

// thiscall shims: ecx = object, edx = dummy, rest on the stack.
void* __fastcall Layout_FindWindowByID(void* layout, int dummy, u32 id, s32 flag); // 0x8105b0
void  __fastcall cString_ctor(cString* s, int dummy);                     // 0x6b5060
void  __fastcall cString_dtor(cString* s, int dummy);                     // 0x6b5240
u8    __fastcall cString_Load(cString* s, int dummy, u32 a, u32 b, s32 c); // 0x6b54b0
const u16* __fastcall cString_GetText(cString* s, int dummy);             // 0x6b55c0
void* __fastcall BudgetSetTooltip(void* budget, int dummy, const u16* text); // 0x458b50

// Remaining free callees.
void* __cdecl FUN_00d06eb0(u32 a);        // 0xd06eb0
void* __cdecl FUN_00d1deb0(u32 a);        // 0xd1deb0
void* __cdecl FUN_00d07420(u32 a);        // 0xd07420
void* __cdecl FUN_00d07720(u32 a);        // 0xd07720
void* __cdecl FUN_00d07a40(cCommunityEditor* self); // 0xd07a40
void* __cdecl FUN_005c7b80();             // 0x5c7b80
void  __cdecl FUN_005c7bc0(u32 a);        // 0x5c7bc0
u32   __cdecl FUN_005c7e80(u32,u32,u32,u32); // 0x5c7e80
u32   __cdecl FUN_005c7e20(u32,u32,u32,u32); // 0x5c7e20
s32   __cdecl GetPlayerBuildingCostFromType(); // 0xc9e7c0
s32   __cdecl FUN_00c9e7c0_();            // fallback (same idea)
s32   __cdecl FUN_00bda3b0(u32 id);       // 0xbda3b0
s32   __cdecl FUN_00c9cec0(u32 a);        // 0xc9cec0
s32   __cdecl FUN_00c9cfd0();             // 0xc9cfd0
u8    __cdecl FUN_00d09710(IWindow* p);   // 0xd09710
u8    __cdecl FUN_00d096b0(IWindow* p);   // 0xd096b0
u8    __cdecl FUN_00d096e0(IWindow* p);   // 0xd096e0
s32   __cdecl FUN_00bd0110();             // 0xbd0110
float __fastcall FUN_00bf2170(void* civ, int dummy);       // 0xbf2170
void  __fastcall City_GetCivilization(void* city, int dummy, u32 a, u32 b); // 0xbd9bf0
s32   __cdecl FUN_00cf74c0();             // 0xcf74c0
float __cdecl FUN_00cf7a50();             // 0xcf7a50
s32   __cdecl GetDamageState(void* combatant); // 0xc??
void  __cdecl FUN_007c4900(void* a, void* b);  // 0x7c4900
void* __cdecl FUN_00b3d240();             // 0xb3d240
void  __cdecl FUN_00698e00(void* a, void* b, void* c, void* d); // 0x698e00
void  __cdecl PlanetModel(void* out, void* a, void* b);        // 0x?
void  __cdecl FUN_00b7f1f0(void* a, void* b, void* c);         // 0xb7f1f0
void* __cdecl FUN_00b33e60(u32 a);        // 0xb33e60
void  __cdecl Rollover_Show(IRollover* r, u32 v1, u32 v2, u32 v3); // 0x?
void  __cdecl FUN_0067cab0(void* a);      // 0x67cab0
void  __cdecl FUN_008017f0(void* a);      // 0x8017f0
void  __cdecl FUN_005cc690();             // 0x5cc690
void* __cdecl GetPropertyAsKeyInstance(void* p, u32 id, void** out); // 0x6a12a0
void  __cdecl DeclareMenuCommands();      // 0x?
void* __cdecl SellbackDetachedRollover_ctor(void* p);  // 0x?
void  __fastcall UiLayout_Init(void* layout, int dummy, u32 a, u32 b, s32 c, u32 d); // 0x?
void  __fastcall UiLayout_SetVisibility(void* layout, int dummy, s32 v); // 0x?
void* __cdecl Window_New(u32 size, u32 a, const char* pClass, void* b); // 0x9512d0
void* __cdecl FUN_009512c0();             // 0x9512c0
u8    __cdecl PropMgr_Get(u32 a, u32 b, void** out); // PropertyManager slot 0x2c

// The pointer values compared against GetCurrentGameMode() results.

// ---------------------------------------------------------------------------
// 0x00d0a160: "can the preview be shown?" -- name check + tray query.
// ---------------------------------------------------------------------------
static const u16 kPreviewName[] = { 'P','r','e','v','i','e','w','M','o','d','e','l', 0 };

// @ 0x00d0a160
u8 cCommunityEditor::CanShowPreview()
{
  if (mpPreviewObject_c0 == 0) {
    const u16* name = (const u16*)mpCommunity_40->mNameProvider_34.Slot0c(0);
    // (the retail build inlines a two-wchar-at-a-time compare here)
    const u16* a = name;
    const u16* b = kPreviewName;
    s32 cmp;
    for (;;) {
      u16 c = *a;
      if (c != *b) { cmp = (c < *b) ? -1 : 1; break; }
      if (c == 0) { cmp = 0; break; }
      c = a[1];
      if (c != b[1]) { cmp = (c < b[1]) ? -1 : 1; break; }
      a += 2; b += 2;
      if (c == 0) { cmp = 0; break; }
    }
    if (cmp != 0 || mpVerbIconTray_a4 == 0) {
      mFlag_208 = 1;
      return 1;
    }
    mpVerbIconTray_a4->Slot1c(1);
  }
  return 0;
}

// ---------------------------------------------------------------------------
// 0x00d0a1e0: choose and install the limit-meter rollover widget.
// ---------------------------------------------------------------------------
// @ 0x00d0a1e0
void cCommunityEditor::UpdateLimitMeter(s32 mode)
{
  u32 want = 0;
  if (mpCommunity_40 != 0) {
    void* p = mpCommunity_40->Slot0c(0xee9b2232);
    if (p != 0) {
      if (GetCurrentGameMode() == (void*)0x1654c05) {
        want = (mode != 1) ? 3u : 4u;
      } else if (mode == 1 || mode == 0) {
        want = 2;
      } else {
        want = 1;
      }
    }
  }
  if (want == mLimitMode_80)
    return;
  IRollover* old = mpSellback_7c;
  if (old != 0) {
    old->Release();
    SporeFreeArray(old);
    mpSellback_7c = 0;
  }
  u32 arg = 0;
  if (mpCommunity_40 != 0)
    arg = (u32)(SIZE_T)mpCommunity_40->Slot0c(0xee9b2232);
  IWindow* win = (IWindow*)mEditorUI_88.FindWindowByID(0x499da93, 1);
  IRollover* made = 0;
  if (win != 0) {
    switch (want) {
    case 1:
      if (SporeAlloc(0xc, "Editor", 0, 0, 0, 0) != 0)
        made = (IRollover*)FUN_00d06eb0(arg);
      break;
    case 2:
      if (SporeAlloc(0xc, "Editor", 0, 0, 0, 0) != 0)
        made = (IRollover*)FUN_00d1deb0(arg);
      break;
    case 3:
      if (SporeAlloc(0xc, "Editor", 0, 0, 0, 0) != 0)
        made = (IRollover*)FUN_00d07420((u32)(SIZE_T)GetPlayerEmpire());
      break;
    case 4:
      if (SporeAlloc(0xc, "Editor", 0, 0, 0, 0) != 0)
        made = (IRollover*)FUN_00d07720((u32)(SIZE_T)GetPlayerEmpire());
      break;
    default:
      break;
    }
    mpSellback_7c = made;
  }
  IRollover* cur = mpSellback_7c;
  if (cur != 0) {
    cur->Show(win);
    cur->Slot08();
  }
  mLimitMode_80 = want;
}

// ---------------------------------------------------------------------------
// 0x00d0a390: refresh the budget tooltip text.
// ---------------------------------------------------------------------------
// @ 0x00d0a390
void cCommunityEditor::RefreshTooltip()
{
  if (GetCurrentGameMode() != (void*)0x1654c04 &&
      GetCurrentGameMode() != (void*)0x1654c05)
    return;
  u32 pad_00;
  cString s;
  s.Ctor();
  s.Load(0xc0152a6d, 0x65f79f0, 0);
  ((BudgetObj*)mpBudget_6c)->SetText(s.GetText());
  s.Dtor();
  (void)pad_00;
}

// ---------------------------------------------------------------------------
// 0x00d0a3f0: cost of the selected object.
// ---------------------------------------------------------------------------
// @ 0x00d0a3f0
s32 cCommunityEditor::GetSelectedCost(SelectableObj* p)
{
  s32* it = mpSelectedIds_1f0;
  s32* end = mpSelectedEnd_1f4;
  if (it != end) {
    for (; it != end; ++it)
      if (*it == (s32)(SIZE_T)p) break;
    if (it != end && mpCommunity_40 != 0) {
      void* city = mpCommunity_40->Slot0c(0xee9b2232);
      if (city != 0) {
        City_GetCivilization(city, 0, p->mKeyA_b1c, p->mKeyB_b20);
        return (s32)FUN_00bf2170(city, 0);
      }
    }
  }
  return (s32)FUN_00c9e7c0_();
}

// ---------------------------------------------------------------------------
// 0x00d0a470: show the sell-back rollover on two windows.
// ---------------------------------------------------------------------------
// @ 0x00d0a470
void cCommunityEditor::ShowRolloverWindows(u32 idA, u32 idB)
{
  IWindow* wA = (IWindow*)mEditorUI_88.FindWindowByID(idA, 1);
  IWindow* wB = (IWindow*)mEditorUI_88.FindWindowByID(idB, 1);
  IWindow* wC = (wB != 0) ? (IWindow*)wB->Slot0c(0xf15f4bd) : 0;
  if (wA != 0 && wB != 0 && wC != 0) {
    wC->Slot14(1);
    wB->Slot38();
    Vec4* rA = wA->Slot38();
    Vec4* rB = (Vec4*)0;      // result of wB->Slot38(), kept local
    (void)rB;
    Vec4 v;
    v.x = rA->x;
    v.y = rA->y;
    v.z = rA->z;
    v.w = rA->w;
    wA->Slot6c(&v);
  }
}

// ---------------------------------------------------------------------------
// 0x00d0a540 / 0x00d0a5b0: show / hide the placement cursor.
// ---------------------------------------------------------------------------
// @ 0x00d0a540
void cCommunityEditor::ShowPlacementCursor()
{
  mpWindowCtrl_2f8->mWindow_04.Slot7c(1, 1);
  WindowCtrl* c = mpWindowCtrl_2f8;
  void* p = (c != 0) ? (void*)&c->mWindow_04 : 0;
  ((IWindowMgr*)WindowManagerObj())->Slot58(1, p);
  if (mpWindowCtrl_2f8 != 0) {
    ((IWindowMgr*)WindowManagerObj())->Slot58(0, &mpWindowCtrl_2f8->mWindow_04);
    return;
  }
  ((IWindowMgr*)WindowManagerObj())->Slot58(0, 0);
}

// @ 0x00d0a5b0
void cCommunityEditor::HidePlacementCursor()
{
  void* p = (mpWindowCtrl_2f8 != 0) ? (void*)&mpWindowCtrl_2f8->mWindow_04 : 0;
  ((IWindowMgr*)WindowManagerObj())->Slot5c(1, p);
  void* q = (mpWindowCtrl_2f8 != 0) ? (void*)&mpWindowCtrl_2f8->mWindow_04 : 0;
  ((IWindowMgr*)WindowManagerObj())->Slot5c(0, q);
  mpWindowCtrl_2f8->mWindow_04.Slot7c(1, 0);
}

// ---------------------------------------------------------------------------
// 0x00d0a630: lower-bound lookup in the ordered position tree.
// ---------------------------------------------------------------------------
void PosTree_InsertPos(PosTree* tree, PosNode** out, const s32* key); // 0xd0a630

// @ 0x00d0a630
void PosTree::InsertPos(PosNode** out, const s32* key)
{
  PosNode* node = this->mpRoot_0c;
  PosNode* best = (PosNode*)&this->mpSentinel_04;
  while (node != 0) {
    if (key[0] > node->mKey0_10 ||
        (key[0] == node->mKey0_10 && node->mKey1_14 < key[1])) {
      node = node->mpLeft_00;
    } else {
      best = node;
      node = node->mpRight_04;
    }
  }
  *out = best;
}

// ---------------------------------------------------------------------------
// 0x00d0a670: copy a CopyValue (adds refs, copies scalars).
// ---------------------------------------------------------------------------
// @ 0x00d0a670
CopyValue* CopyValue::AssignFrom(const CopyValue* src)
{
  this->mpA_00 = src->mpA_00;
  if (this->mpA_00 != 0)
    this->mpA_00->AddRef();
  this->mpB_04 = src->mpB_04;
  if (this->mpB_04 != 0)
    this->mpB_04->AddRef();
  this->mF_08 = src->mF_08;
  this->mF_0c = src->mF_0c;
  this->mF_10 = src->mF_10;
  this->mF_14 = src->mF_14;
  this->mF_18 = src->mF_18;
  this->mF_1c = src->mF_1c;
  this->mU32_20 = src->mU32_20;
  this->mU32_24 = src->mU32_24;
  this->mB_28 = src->mB_28;
  return this;
}

// ---------------------------------------------------------------------------
// 0x00d0a6e0: resolve the property "model type" key instance for a noun.
// ---------------------------------------------------------------------------
// @ 0x00d0a6e0
u32 __cdecl GetModelType(ModelType* p)
{
  u32 result = 0xffffffff;
  if (p == 0)
    return result;
  IProperty* mgr = (IProperty*)PropertyManager();
  IProperty* inst = 0;
  if (inst != 0) {
    inst = 0;
    inst->Release();
  }
  if (mgr->Slot2c(p->mKeyA_0c, p->mKeyB_14, (void**)&inst) != 0)
    GetPropertyAsKeyInstance(p, 0x5338876f, (void**)&result);
  if (p != 0)
    ((IProperty*)p)->Release();
  return result;
}

// ---------------------------------------------------------------------------
// 0x00d0a760: editor initialisation.
// ---------------------------------------------------------------------------
// @ 0x00d0a760
void cCommunityEditor::Init(u32 const* pLayoutId, u32 propKey,
                            IWindow* pBudget, u8 bFlag)
{
  DeclareMenuCommands();
  IRollover* roll = 0;
  if (SporeAlloc(0xa8, "Editor", 0, 0, 0, 0) != 0)
    roll = (IRollover*)SellbackDetachedRollover_ctor(SporeAlloc(0xa8, "Editor", 0, 0, 0, 0));
  IRollover* oldRoll = mpSellback_7c;
  if (roll != oldRoll) {
    if (roll != 0)
      roll->Show(0);
    mpSellback_7c = roll;
    if (oldRoll != 0)
      oldRoll->Release();
  }
  mpBudget_6c = pBudget;
  if (bFlag != 0) {
    IRollover* shopping = 0;
    if (SporeAlloc(0xc, "Editor", 0, 0, 0, 0) != 0)
      shopping = (IRollover*)FUN_00d07a40(this);
    IRollover* oldShop = (IRollover*)mpRollover_84;
    if (shopping != oldShop) {
      if (shopping != 0)
        shopping->Release();
      mpRollover_84 = shopping;
      if (oldShop != 0)
        oldShop->Slot08();
    }
  }
  UiLayout_Init(&mEditorUI_88, 0, *pLayoutId, 0x40464100, 1, 0x5b598fa);
  UiLayout_SetVisibility(&mEditorUI_88, 0, 0);
  IWindow* root = (IWindow*)mEditorUI_88.FindWindowByID(0xffffffff, 1);
  if (root != 0) {
    root->Slot104(this);
    void* cls = FUN_009512c0();
    IWindow* blocker = (IWindow*)Window_New(0x20c, 4, "UI/cUIBlockingWin", cls);
    if (blocker == 0)
      blocker = 0;
    IWindow* oldBlock = mpBlockerWindow_340;
    if (blocker != oldBlock) {
      if (blocker != 0)
        blocker->AddRef();
      mpBlockerWindow_340 = blocker;
      if (oldBlock != 0)
        oldBlock->Release();
    }
    mpBlockerWindow_340->Slot60();
    mpBlockerWindow_340->Slot7c(1, 0);
    mpBlockerWindow_340->Slot78(0x6493807);
    root->SlotD8(mpBlockerWindow_340);
  }
  mpVerbIconTray_a4 = (IWindow*)mEditorUI_88.FindWindowByID(0xd0527aad, 1);
  IProperty* pmgr = (IProperty*)PropertyManager();
  IProperty* cfg = 0;
  if (cfg != 0) {
    cfg = 0;
    cfg->Release();
  }
  pmgr->Slot2c(propKey, 0xa19b317d, (void**)&cfg);
  mpPreviewObject_c0 = (void*)mEditorUI_88.FindWindowByID(0xf006f308, 1);
  mpRingDefinition_c4 = MessageServer();
  if (mpRingDefinition_c4 != 0)
    ((IProperty*)mpRingDefinition_c4)->Slot24();
}

// ---------------------------------------------------------------------------
// 0x00d0aa70: push the player-building costs into the model property list.
// ---------------------------------------------------------------------------
// @ 0x00d0aa70
void cCommunityEditor::RefreshBuildingCosts()
{
  if (SporeAlloc(0x20, "Editor", 0, 0, 0, 0) == 0)
    return;
  void* iter = (void*)FUN_005c7b80();
  if (iter == 0)
    return;
  ((IWindow*)iter)->Release();
  FUN_005c7bc0((u32)(SIZE_T)mpProjector_b0);
  for (u32 i = FUN_005c7e80(0, 0, 0, 0); i != 0; i = FUN_005c7e20(0, 0, 0, 0)) {
    u32 type = GetModelType((ModelType*)i);
    s32 cost = GetPlayerBuildingCostFromType();
    if (cost != -1) {
      IProperty* inst = 0;
      IProperty* pmgr = (IProperty*)PropertyManager();
      if (inst != 0) {
        inst = 0;
        inst->Release();
      }
      if (pmgr->Slot2c(((ModelType*)i)->mKeyA_0c, ((ModelType*)i)->mKeyB_14,
                       (void**)&inst) != 0 &&
          inst->Slot1c(0x2166464) != 0) {
        u32 var[3];
        var[0] = 0;
        var[1] = 0;
        *(s32*)&var[2] = cost;
        inst->Slot14(0x2166464, var);
      }
      if (inst != 0)
        inst->Release();
    }
    (void)type;
  }
  ((IWindow*)iter)->Slot08();
}

// ---------------------------------------------------------------------------
// 0x00d0abd0: cost of a placed object (with optional refund adjustment).
// ---------------------------------------------------------------------------
// @ 0x00d0abd0
s32 cCommunityEditor::GetObjectCost(IWindow* pObj, u8 bRefund, u32 typeKey)
{
  float cost = 0.0f;
  if (pObj == 0)
    return 0;
  IWindow* a = (IWindow*)pObj->SlotB8(0x436f315);
  IWindow* b = (IWindow*)pObj->SlotB8(0xe9cb8ba);
  IWindow* c = (IWindow*)pObj->SlotB8(0x116d858);
  pObj->SlotB8(0x175cdc9);
  IWindow* d = (IWindow*)pObj->SlotB8(0x137e8e0);
  if (a != 0) {
    if (bRefund != 0 && GetDamageState((u8*)a + 0x588 * 0 + 0) == 2)
      return 0;
    cost = ((IProperty*)a)->Slot5c();
    if (bRefund != 0 && FUN_00d096e0(a) != 0) {
      FUN_00cf74c0();
      return (s32)(FUN_00cf7a50() * cost);
    }
    return (s32)cost;
  }
  if (b != 0) {
    if (bRefund != 0 && GetDamageState((u8*)b + 0x48 * 0 + 0) == 2)
      return 0;
    cost = ((IProperty*)b)->Slot5c();
    if (bRefund != 0 && FUN_00d096b0(b) != 0) {
      FUN_00cf74c0();
      return (s32)(FUN_00cf7a50() * cost);
    }
    return (s32)cost;
  }
  if (c != 0) {
    u32 id = ((IProperty*)c)->Slot58();
    s32 v = FUN_00c9cec0(id);
    cost = (float)*(s32*)((u8*)0 + 0x38 * 0 + (SIZE_T)v + 0x38 - 0x38);
    cost = (float)*(s32*)((u8*)(SIZE_T)v + 0x38);
    if (bRefund != 0 && FUN_00d09710(c) != 0) {
      s32 r = FUN_00c9cfd0();
      float frac = 0.0f;
      float adj = frac * (cost - (float)r);
      return (s32)(adj < 0.0f ? 0.0f : adj);
    }
    return (s32)cost;
  }
  if (d != 0) {
    s32 v = FUN_00bda3b0(SPIDFromName("CommunityEditor", 0,
                                      SPIDFromName("CivicObjectCost", 10)));
    cost = (float)v;
    return (s32)cost;
  }
  (void)d; (void)typeKey;
  return (s32)cost;
}

// ---------------------------------------------------------------------------
// 0x00d0ae50: update the vehicle placement preview.
// ---------------------------------------------------------------------------
// @ 0x00d0ae50
u32 cCommunityEditor::UpdateVehiclePlacement()
{
  if (mpCommunity_40 == 0)
    return 0;
  if (mpCommunity_40->Slot0c(0) == 0 || mpPreviewObject_c0 == 0)
    return 0;
  IApp* app = (IApp*)AppObject();
  IApp* sub = (IApp*)app->Slot50();
  u8 a[8], b[4];
  sub->Slot1c(a, b);
  FUN_007c4900(a, b);
  void* pm = FUN_00b3d240();
  ((IWindow*)pm)->Slot3c(b, 1);
  Vec3 pos = mPreviewPos_108;
  float t[4];
  FUN_00698e00(t, &pos, a, b);
  void* v = ((IWindow*)mpPreviewObject_c0)->Slot30();
  Vec3 out;
  PlanetModel(&out, t, v);
  FUN_00b7f1f0(&out, t, v);
  float dx = t[0] - mPreviewPos_108.x;
  float dy = t[1] - mPreviewPos_108.y;
  float dz = t[2] - mPreviewPos_108.z;
  float dist = dx * dx + dy * dy + dz * dz;
  if (dist >= 225.0f) {
    if (mpRollover_84 != 0) {
      u32 sel = (u32)(SIZE_T)FUN_00b33e60((u32)(SIZE_T)mpPreviewObject_c0);
      cString s;
      s.Ctor();
      s.Load(0xdc351566, 0x40000010, 0);
      u32 cost = (u32)GetSelectedCost((SelectableObj*)sel);
      u8 maxv = 0;
      (void)maxv;
      Rollover_Show(mpRollover_84, cost, 0, 1);
      if (mpRollover_84 != 0)
        FUN_0067cab0((u8*)mpRollover_84 + 0x78);
      FUN_0067cab0(mpRollover_84);
      FUN_008017f0(mpRollover_84);
      s.GetText();
      s.Dtor();
    }
  } else if (mpRollover_84 != 0) {
    FUN_005cc690();
  }
  ((IWindow*)mpPreviewObject_c0)->Slot38();
  ((IWindow*)mpPreviewObject_c0)->Slot3c(b, 0);
  return 0;
}

// ---------------------------------------------------------------------------
// 0x00d0b010: create or destroy the rotation-ring noun.
// ---------------------------------------------------------------------------
// @ 0x00d0b010
void cCommunityEditor::SetRotationRingVisibility(u8 bShow)
{
  void* ring = mpRotationRing_bc;
  if (ring != 0) {
    NounMgr_RemoveNoun(NounManager(ring), ring);
    mpRotationRing_bc = 0;
  }
  if (bShow != 0 && mpRingDefinition_c4 != 0 && mpCommunity_40 != 0) {
    void* noun = NounMgr_CreateNoun(NounManagerObj(), 0x2ee8ce8);
    IWindow* iface = 0;
    if (noun != 0)
      iface = (IWindow*)((IProperty*)noun)->Slot0c(0x2ee8eeb);
    mpRotationRing_bc = iface;
    iface->Slot54();
  }
}

