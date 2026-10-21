// slice s00f12340 -- SP palette-item UI editor family (utl/SP*.obj)
//  00f12340  refresh layout pass over palette category pages/items
//  00f12690  accessor: the item window from the host's +0x10 slot
//  00f126d0  set the window id, then refresh
//  00f12700  Init (allocate the layout, hook windows, install the sub item UIs)
//  00f128f0  Shutdown (release the layout and the two sub item UIs)
//  00f12970  open the modal page selector
//  00f12a60  close the modal page selector
//  00f12b00  scalar deleting destructor (selectable variant)
//  00f12b50  SetPaletteItem override
//  00f12de0  destructor
//  00f12eb0  page/category switch (Shutdown + Init + rebuild pages)
//  00f12fc0  DoMessage (0x1b / 0x1c / item-type dispatch)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>

// --- external helper types (only the members this slice calls) --------------
struct Sub900;   // object at *(host+0x14)+0x10 : has Set(int)
struct SubUI;    // the UI object living at host+0x1c
struct SubUI2;   // the UI object living at host+0x20 (IUnknown at +0x10)
struct cSPUILayout;
struct cSPPalette;
struct cSPPaletteCategory;
struct cSPPaletteCategoryUI;
struct cSPPalettePage;
struct cSPPalettePageUI;
struct cSPPaletteItem;
struct cSPUIPropertyLayout;
struct cSPEditorVehicleAbilities;
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

struct WinObj2;
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

struct cSPUILayout {
  virtual void vv0();
  virtual void AddRef();       // +0x04
  virtual void Release();      // +0x08
  void Shutdown(unsigned a);   // 0x811ad0
  void SetVisibility(bool v);  // 0x810590
  WinObj* FindWindowByID(unsigned id, bool a);   // 0x8105b0
  char Init(const EAKey* key, bool a, int b);            // 0x8120d0
  char SetParentWin(void* parent, bool a, int b);        // 0x8121b0
};

// --- free helpers (real addresses) -----------------------------------------
cSPPaletteCategory* Palette_GetCategory(cSPPalette* pal, int index);               // 0x5c5de0
cSPPalettePage* Category_GetPage(cSPPaletteCategory* cat, int index);              // 0x5c1ce0
cSPPalettePageUI* CategoryUI_GetPageUI(cSPPaletteCategoryUI* ui, int index);       // 0x5c2e50
cSPPaletteItem* Page_GetItem(cSPPalettePage* page, int index);                     // 0x5c7f00
cSPPaletteCategory* Category_GetSubCategory(cSPPaletteCategoryUI* ui, int index);  // 0x5cae30
void CategoryUI_Shutdown(cSPPaletteCategoryUI* ui);                                // 0x5c4e40
void CategoryUI_Init(cSPPaletteCategoryUI* ui, cSPPaletteCategory* cat, void* win,
                     void* info);                                                  // 0x5c53c0
void CategoryUI_SetVisibility(cSPPaletteCategoryUI* ui, bool visible);             // 0x5c2960
void PaletteItemUI_SetPaletteItem_(void* self, cSPPaletteItem* item);              // 0x5c6ec0
void PaletteItemUI_Dtor(void* self);                                               // 0x5c6c50
void f_00f12ac0(void* self);                                                       // 0xf12ac0
void EAMessaging_RemoveHandler(int a, int b, int c, int d, int e);                 // 0x571db0
void* f_00e09ca0(void* layout, int col, int row);                                  // 0xe09ca0
char Layout_SetVisibility(cSPUILayout* layout, bool visible);                      // 0x810590
char Layout_Init(cSPUILayout* layout, const EAKey* key, bool a, int b);            // 0x8120d0
char Layout_SetParentWin(cSPUILayout* layout, void* parent, bool a, int b);        // 0x8121b0
void SPUIHelpers_SetWindowAreaToParent(void* win);                                 // 0x806bf0
void SPUIHelpers_BeginModal(void* win, int a, int b);                              // 0x8099a0
void SPUIHelpers_EndModal(WinObj* win, int a, int b);                              // 0x809c50
unsigned char f_00807cb0(void* win, void* a, int b);                               // 0x807cb0
void SPUIHelpers_AnchorWindowToWindow(void* a, void* b, int c, int d);             // 0x807340
void cPL_SetPositionAndOffset(cSPUIPropertyLayout* self, float, float, float, float); // 0x8283a0
void cPL_SetMode(cSPUIPropertyLayout* self, int mode);                             // 0x5ed320
void cPL_Hide(cSPUIPropertyLayout* self);                                          // 0x5ed6c0
void cPL_SetItem(cSPUIPropertyLayout* self, cSPPaletteItem* item, void* palette, void* content,
                 bool show);                                                       // 0x5ee480
char f_00eed9c0(void* a, void* b);                                                 // 0xeed9c0
void f_00ed1350(void* win, int a);                                                 // 0xed1350
void cString_ctor(void* self);                                                     // 0x6b5060
void cString_dtor(void* self);                                                     // 0x6b5240
void GetPropertyAsKey(void* item, unsigned key, void* out);                        // 0x6a1250
void* SP_PropertyManager();                                                        // 0x67de30
void* EAAllocate(unsigned size, const char* name, int, int, int, int);             // 0xf473a0
void* cConnectionDialog_ctor_(void* self);                                         // 0x810000
void* f_00ec41e0_(void* self);                                                     // 0xec41e0
void* f_00ef3b40_(void* self);                                                     // 0xef3b40
void* GetEditorUI();                                                               // 0x401020
cSPUIPropertyLayout* EditorUI_GetPropertyLayout(void* self);                       // 0x113ae10
struct EVeh {
  void* Init(ResourceKey key, unsigned x, unsigned y, unsigned z, bool w);  // 0x59f030
};
void cSpaceInventory_SetInactive(void* self);                                      // 0x599560
void cSpaceInventory_SetActive(void* self);                                        // 0x599530
void cSpaceInventory_ShowRolloverA(void* self, int a);                             // 0x599be0
void cSpaceInventory_ShowRolloverB(void* self, int a);                             // 0x599c10
unsigned long long f_00593980_(int a, int b);                                      // 0x593980
char cCollectableItems_Lock(void* self, unsigned long long key);                   // 0x596e10
char f_00596da0_(unsigned long long key, int a);                                   // 0x596da0
void f_00572620_(void* self, void* a);                                             // 0x572620
void EAAllocate_free(void* p);                                                     // 0xf47380

// --- the host object --------------------------------------------------------
struct Host {
  char pad00[0x04];
  void* mWnd;                    // +0x04
  char pad08[0x04];
  cSPUILayout* mLayout;          // +0x0c
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


// ---------------------------------------------------------------------------
// @ 0x00f12690
void* Host::FUN_00f12690() {
    Sub900* h = (Sub900*)this->mItemHost;
    return h ? (void*)h->mpWin.mpObject : 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f126d0
void Host::FUN_00f126d0() {
    Sub900* h = (Sub900*)this->mItemHost;
    ((Sub900b*)h->mpWin.mpObject)->Set(1);
    FUN_00f12340();
}

// ---------------------------------------------------------------------------
// @ 0x00f128f0
void Host::FUN_00f128f0() {
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
        cSPUILayout* lay = this->mLayout;
        if (lay) {
            this->mLayout = 0;
            lay->Release();
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f12a60
void Host::FUN_00f12a60() {
    WinObj* w = this->mLayout->FindWindowByID(0x774b418, true);
    if (w) {
        w->AddRef();
        w->SetVisible(1, 0);
    }
    SPUIHelpers_EndModal(this->mLayout->FindWindowByID(0x7ece6d8, true), 0, 0);
    if (w)
        w->Release();
}

// ---------------------------------------------------------------------------
// @ 0x00f12970
void Host::FUN_00f12970() {
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

// ===========================================================================
// Additional scaffolding for the remaining functions.
// ===========================================================================
struct PageVec { void Clear(); };                       // 0xf12ac0
struct PIB { void Dtor(); };                            // 0x5c6c50
struct PIB2 { void SetPaletteItem(void* item); };       // 0x5c6ec0
struct ConnDialog { ConnDialog* ctor(); };              // 0x810000
struct Obj10 { virtual void AddRef(); virtual void Release(); };  // IUnknown at +0x10

struct Obj20 {                                          // the object at +0x20
  virtual void a00();           // +0x00
  virtual void Update(void* p); // +0x04
  char pad[0x08];
  Obj10 mRef;                   // +0x10
};

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

struct PropLayout;   // cSPUIPropertyLayout

extern char vtbl_148c034[], vtbl_148c018[], vtbl_148c008[];
extern char vtbl_148c0e4[], vtbl_148c0d4[], vtbl_148c0b8[];
extern char vtbl_13eb938[], vtbl_13ec458[], vtbl_13eb394[];

extern char g_016c7aa4[];   // global manager pointer (DAT_016c7aa4)

void* EAAllocate2(unsigned size, const char* name);     // 0xf473a0 (5 extra 0 args)

// helpers used by the large functions
void* SPUI_SetWindowAreaToParent(void* win);            // 0x806bf0
char FUN_005c6730f(void* p);                            // 0x5c6730
char FUN_005c65f0f(void* p);                            // 0x5c65f0
void FUN_00599be0f(void* p);                            // 0x599be0
void FUN_00599c10f(void* p);                            // 0x599c10
void FUN_00599530f(void);                               // 0x599530
void FUN_00599560f(void);                               // 0x599560
void* FUN_00401020f(void);                              // 0x401020
void* FUN_0113ae10f(void);                              // 0x113ae10
void FUN_0061df40f(void* p);                            // 0x61df40
void FUN_005ee480f(void* layout, void* item, void* a, int b);  // 0x5ee480
void FUN_005ed320f(int mode);                           // 0x5ed320
void FUN_005ed6c0f(void);                               // 0x5ed6c0
unsigned long long FUN_00593980f(int a, int b);         // 0x593980
char FUN_00596e10f(unsigned long long k);               // 0x596e10
char FUN_00596da0f(unsigned long long k, int a);        // 0x596da0
void FUN_00572620f(void* p);                            // 0x572620
void* FUN_006bb640f(void);                              // 0x6bb640
void* PropertyManager(void);                            // 0x67de30
void* cSPUIPropertyLayout_SetPositionAndOffset(void* self, float a, float b, float c, float d);
                                                        // 0x8283a0
void FUN_00ed1350f(void* win, int a);                   // 0xed1350

// ---------------------------------------------------------------------------
// @ 0x00f12b00  scalar deleting destructor of the selectable item UI
Host* Host::FUN_00f12b00(unsigned flags) {
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

// ---------------------------------------------------------------------------
// @ 0x00f12de0  destructor
void Host::FUN_00f12de0() {
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

// ===========================================================================
// 00f12eb0 -- page/category switch
// ===========================================================================
#define PV(n) virtual void pv##n();

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
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
  PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
  PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
  virtual void* Get(unsigned id, int a, void* out);   // +0xf0
};

struct PageUI { char pad[0x10]; ObjUI* mObj; };       // cSPPalettePageUI

// ---------------------------------------------------------------------------
// @ 0x00f12eb0  page/category switch (Shutdown + Init + rebuild pages)
// ---------------------------------------------------------------------------
void Host::FUN_00f12eb0() {
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

// ===========================================================================
// vtable-slot models for the remaining functions
// ===========================================================================
struct EvObj {                       // ev: release is the 3rd slot
  virtual void a0();                 // +0x00
  virtual void a4();                 // +0x04
  virtual void Release8();           // +0x08
};

struct GObjX {                       // objects with AddRef(0)/Release(4) and +0x104
  virtual void AddRef();             // +0x00
  virtual void Release();            // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
  PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
  PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
  PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void SetHandler(void* p);  // +0x104
};

struct SubRec {                      // the object at (subcategory + 0x1c)
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
  PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
  PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
  virtual WinObj* Make(unsigned id, int a);   // +0xf0
};

struct Page {                        // cSPPalettePage
  cSPPaletteItem* GetItem(int index);         // 0x5c7f00
};

struct PropVal {                     // a property value object
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void* M28(unsigned key);            // +0x28
  void* GetTPTR();                            // 0x454b10
};

struct PropMgr {                     // SP::PropertyManager()
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual char Get(unsigned a, unsigned b, void* out);   // +0x2c
};

struct EObj {                        // message source / property objects
  PV(0) PV(1) PV(2) PV(3)
  virtual EObj* Child();                      // +0x10
  PV(5) PV(6)
  virtual unsigned GetType();                 // +0x1c
  PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual float* GetRect();                   // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34)
  PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44)
  virtual EObj* GetByType(unsigned id);       // +0xb4
  PV(46) PV(47)
  virtual void vc0(float* out, float a, float b);   // +0xc0
};

struct EObjB {                       // same object, slot +0x10 with 3 args
  PV(0) PV(1) PV(2) PV(3)
  virtual void* C10(void* a, void* b, int c); // +0x10
  void DoIt(void* p);                          // 0x572620
};

struct WinObj8 {                     // a window with the +0xb8 slot
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
  PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41) PV(42) PV(43) PV(44) PV(45)
  virtual void SetKey(unsigned id, void* p);  // +0xb8
};

struct PLayout {                     // cSPUIPropertyLayout
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
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

// ===========================================================================
// @ 0x00f12340  refresh layout pass over palette category pages/items
// ===========================================================================
void Host::FUN_00f12340() {
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
            cSPUILayout* lay = (cSPUILayout*)f_00e09ca0(pageBase, col, row - 1);
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

// ===========================================================================
// @ 0x00f12700  Init
// ===========================================================================
void Host::FUN_00f12700(void* parent) {
    char* self = (char*)this;
    void* obj = EAAllocate(0x18, "Simulator", 0, 0, 0, 0);
    if (obj)
        obj = ((ConnDialog*)obj)->ctor();
    else
        obj = 0;
    cSPUILayout* old = *(cSPUILayout**)(self + 0x0c);
    if ((cSPUILayout*)obj != old) {
        if (obj)
            ((GObjX*)obj)->AddRef();
        *(void**)(self + 0x0c) = obj;
        if (old)
            ((GObjX*)old)->Release();
    }
    cSPUILayout* lay = *(cSPUILayout**)(self + 0x0c);
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

// ===========================================================================
// @ 0x00f12b50  SetPaletteItem override
// ===========================================================================
void Host::FUN_00f12b50(cSPPaletteItem* item) {
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
    WinObj* w = ((cSPUILayout*)(*(void**)(self + 0x20)))->FindWindowByID(
        *(unsigned*)(*(char**)(self + 4) + 0x24), true);
    if (w)
        w->SetVisible(1, 1);
    f_00807cb0(w, &local20, 0);
    ((WinObj8*)w)->SetKey(0x7f1fe63, self + 0xc);
}

// ===========================================================================
// @ 0x00f12fc0  DoMessage
// ===========================================================================
bool Host::FUN_00f12fc0(void* unused, void* msg) {
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
