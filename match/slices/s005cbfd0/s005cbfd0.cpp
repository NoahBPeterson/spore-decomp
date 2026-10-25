// slice s005cbfd0 -- SP sell-back rollover UI: window flag helpers, Init, ctor, and the
// shopping-token translator ctor/dtor. Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);

#define PV(n) virtual void pv##n();

namespace EA {
namespace UTFWin {
class IUnknown32 {
 public:
  virtual int AddRef();   // +0
  virtual int Release();  // +4
};
class IWindow : public IUnknown32 {
 public:
  PV(2) PV(3)
  virtual void* GetLayout();                    // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual int GetFlag();                        // +0x28
  PV(11) PV(12)
  virtual void* GetPos0();                      // +0x34
  virtual void* GetPos1();                      // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
  virtual void SetStyle(int style);             // +0x5c
  virtual void SetPosition(const void* pos);    // +0x60
  virtual void SetSize(float w, float h);       // +0x64
  PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);   // +0x7c
  virtual void SetText(const void* text);       // +0x80
  PV(33) PV(34) PV(35)
  virtual void Update();                        // +0x90
  PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43)
  PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52)
  PV(53)
  virtual void SetParent(IWindow* parent);      // +0xd8
};
}  // namespace UTFWin
}  // namespace EA
using EA::UTFWin::IWindow;

class cSPUILayout {
 public:
  IWindow* FindWindowByID(unsigned int id, bool recursive);  // 0x008105b0
};

class cSPUILayoutManager {
 public:
  IWindow* GetWorldMainWindow();  // 0x00810620
};
cSPUILayoutManager* __stdcall SPUIHelpers_GetLayoutManager(unsigned int id);  // 0x00805070

// ---------------------------------------------------------------------------------------------
// Detached rollover (windows at +0x78, flag bool at +0x96)
class cDetachedRollover {
 public:
  bool BaseInit();  // 0x00828250 (cSPUIPropertyLayout::Init)
  bool Init(unsigned short value);   // 0x005cbfd0
  void HideWin();                    // 0x005cc0e0
  bool IsWinVisible();               // 0x005cc100

  char pad0[0xc];
  cSPUILayout mLayout;               // +0xc
  char pad10[0x78 - 0x10];
  IWindow* mWin;                     // +0x78
  IWindow* mWin7c;                   // +0x7c
  IWindow* mWin80;                   // +0x80
  IWindow* mWin84;                   // +0x84
  IWindow* mWin88;                   // +0x88
  IWindow* mWin8c;                   // +0x8c
  IWindow* mWin90;                   // +0x90
  unsigned short mWord94;            // +0x94
  bool mFlag96;                      // +0x96
};

// @ 0x005CBFD0
bool cDetachedRollover::Init(unsigned short value) {
  bool ok = BaseInit();
  if (ok) {
    mWin = mLayout.FindWindowByID(0, true);
    if (mWin) {
      mWin->SetStyle(0xffffff);
      mWin7c = mLayout.FindWindowByID(0x125f2c4f, true);
      mWin80 = mLayout.FindWindowByID(0x325f2c75, true);
      mWin8c = mLayout.FindWindowByID(0x70524f6b, true);
      mWin90 = mLayout.FindWindowByID(0xb25f2df9, true);
      mWin84 = mLayout.FindWindowByID(0x23288a3, true);
      IWindow* p88 = mLayout.FindWindowByID(0x925f2dc4, true);
      mWord94 = value;
      mWin88 = p88;
      if (!mWin->GetLayout()) {
        IWindow* main = SPUIHelpers_GetLayoutManager(0x5b598fa)->GetWorldMainWindow();
        main->SetParent(mWin);
      }
    }
    mFlag96 = false;
  }
  return ok;
}

// @ 0x005CC0E0
void cDetachedRollover::HideWin() {
  if (!mFlag96 && mWin)
    mWin->SetFlag(1, false);
}

// @ 0x005CC100
bool cDetachedRollover::IsWinVisible() {
  if (!mFlag96 && mWin)
    return mWin->GetFlag() & 1;
  return false;
}

// ---------------------------------------------------------------------------------------------
// Sell-back rollover (window at +0x80, flag bool at +0x9e)
class cSellBackRollover {
 public:
  bool BaseInit();  // 0x00828250
  bool Init(unsigned short value);   // 0x005cc5a0
  void HideWin();                    // 0x005cc690
  bool IsWinVisible();               // 0x005cc6c0

  char pad0[0xc];
  cSPUILayout mLayout;               // +0xc
  char pad10[0x80 - 0x10];
  IWindow* mWin;                     // +0x80
  IWindow* mWin84;                   // +0x84
  IWindow* mWin88;                   // +0x88
  IWindow* mWin8c;                   // +0x8c
  IWindow* mWin90;                   // +0x90
  IWindow* mWin94;                   // +0x94
  IWindow* mWin98;                   // +0x98
  unsigned short mWord9c;            // +0x9c
  bool mFlag9e;                      // +0x9e
};

// @ 0x005CC5A0
bool cSellBackRollover::Init(unsigned short value) {
  bool ok = BaseInit();
  if (ok) {
    mWin = mLayout.FindWindowByID(0, true);
    if (mWin) {
      mWin->SetStyle(0xffffff);
      mWin84 = mLayout.FindWindowByID(0x125f2c4f, true);
      mWin88 = mLayout.FindWindowByID(0x325f2c75, true);
      mWin94 = mLayout.FindWindowByID(0x70524f6b, true);
      mWin98 = mLayout.FindWindowByID(0xb25f2df9, true);
      mWin8c = mLayout.FindWindowByID(0x23288a3, true);
      mWin90 = mLayout.FindWindowByID(0x925f2dc4, true);
      mWord9c = value;
    }
    mFlag9e = false;
  }
  return ok;
}

// @ 0x005CC690
void cSellBackRollover::HideWin() {
  if (!mFlag9e && mWin)
    mWin->SetFlag(1, false);
}

// @ 0x005CC6C0
bool cSellBackRollover::IsWinVisible() {
  if (!mFlag9e && mWin)
    return mWin->GetFlag() & 1;
  return false;
}

// ---------------------------------------------------------------------------------------------
// Sell-back rollover editors.
//
// These classes embed objects whose vftables are installed by hand, so they carry a named
// leading vftable pointer instead of C++ virtual functions.
struct Vector2 { float x, y; };

struct IWnd90 {                                     // object at *[win] used for SetVisible
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
    virtual void SetVisible(int on);                // +0x1c
};

struct CRolloverVtbl {                              // vftable of the editor base at +0
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual void SetKey(unsigned short key);        // +0x28
};

// Base class of the sell-back rollovers; its ctor/dtor/SetKey live at 0x00801280 / 0x00827fc0.
class cSPUICursorAttachmentLayout {
 public:
  cSPUICursorAttachmentLayout();                                    // 0x00801280
  void SetKey(const wchar_t* key, unsigned int id);                // 0x00827fc0
};
extern "C" IWnd90* FUN_005994b0(IWindow* win);      // window -> visibility helper
extern "C" void  FUN_008822e0(...);                 // EA::Locale::SetMoneyString
extern "C" void  FUN_00579a90(void*, const wchar_t*);  // eastl::wstring::range_initialize (decl only)

// Base class of the translator; its ctor/dtor live at 0x006b5870 / 0x005725a0.
class cStringTokenTranslator {
 public:
  cStringTokenTranslator();        // 0x006b5870
  ~cStringTokenTranslator();       // 0x005725a0
};

extern char    vtbl_013f8708[];
extern char    vtbl_013f7a10[];
extern char    vtbl_013f86ec[];
extern char    vtbl_013f8798[];
// eastl::gEmptyString16 halves: 0x01667bac (begin/end) and 0x01667bae (cap).
extern wchar_t g_01667bac[];
extern wchar_t g_01667bae[];

// --- cSPEditorSellBackDetachedRollover (0x005cc120) ------------------------------------------
class cSPEditorSellBackDetachedRollover {
 public:
  void* mpVftable;                   // +0x00
  char pad4[0x78 - 4];
  IWindow* mWin78;                   // +0x78
  IWindow* mWin7c;                   // +0x7c
  IWindow* mWin80;                   // +0x80
  IWindow* mWin84;                   // +0x84
  IWindow* mWin88;                   // +0x88
  IWindow* mWin8c;                   // +0x8c
  IWindow* mWin90;                   // +0x90
  unsigned short mWord94;            // +0x94
  bool mFlag96;                      // +0x96
  int  mPrice98;                     // +0x98

  void Show(const wchar_t* text, int price, bool bVisible);   // 0x005cc120
};

// @ 0x005CC120
void cSPEditorSellBackDetachedRollover::Show(const wchar_t* text, int price, bool bVisible) {
  bool needInit = mFlag96;
  mPrice98 = price;
  if (needInit)
    ((CRolloverVtbl*)mpVftable)->SetKey(mWord94);

  if (!mWin78 || !mWin80 || !mWin7c || !mWin84 || !mWin88 || !mWin8c || !mWin90)
    return;

  mWin8c->SetText((void*)text);
  mWin90->SetText((void*)text);
  FUN_005994b0(mWin8c)->SetVisible(1);
  FUN_005994b0(mWin90)->SetVisible(1);

  wchar_t buf[64];
  FUN_008822e0(mPrice98, 0, 0x13ec5a0, mWord94, buf, 0x28, 0);
  mWin84->SetText(buf);
  mWin88->SetText(buf);
  FUN_005994b0(mWin84)->SetVisible(1);
  FUN_005994b0(mWin88)->SetVisible(1);

  Vector2* pA = (Vector2*)mWin8c->GetPos0();
  float hA = ((Vector2*)pA)->x;
  Vector2* pB = (Vector2*)mWin84->GetPos0();
  float hB = ((Vector2*)pB)->x;
  float h = hB > hA ? ((Vector2*)mWin84->GetPos0())->x
                    : ((Vector2*)mWin8c->GetPos0())->x;
  Vector2* t = (Vector2*)mWin8c->GetPos1();
  float yTop = t->y;
  mWin84->SetSize(yTop + 5.0f, h + 5.0f);
  mWin88->SetSize(yTop + 7.0f, h + 5.0f);

  Vector2* sh = (Vector2*)mWin84->GetPos0();
  float sy = sh->y;
  Vector2* tx = (Vector2*)mWin78->GetPos0();
  float txx = tx->x, txy = tx->y;
  Vector2* t2 = (Vector2*)mWin7c->GetPos0();
  float t2x = t2->x, t2y = t2->y;
  Vector2* c = (Vector2*)mWin84->GetPos1();
  Vector2 vText, vShadow, vPrice;
  vText.x = txx;                     vText.y = txy;
  vText.y = t2y + h + 5.0f;
  vShadow.x = t2x;                   vShadow.y = t2y + h + 5.0f;
  vPrice.x = sy;                     vPrice.y = h + 5.0f;
  mWin7c->SetPosition((const Vector2*)&vText);
  mWin80->SetPosition((const Vector2*)&vShadow);
  mWin78->SetPosition((const Vector2*)&vPrice);

  mWin84->SetStyle(bVisible ? 0xffff0000 : 0x00000000);
  mWin7c->SetFlag(1, bVisible);
  mWin80->SetFlag(1, !bVisible);

  mWin8c->Update();
  mWin90->Update();
  mWin84->Update();
  mWin88->Update();
  mWin78->SetFlag(1, 1);
}

// --- cSPEditorSellBackRollover (0x005cc750 Show, 0x005cc520 ctor) ----------------------------
class cSPEditorSellBackRollover : public cSPUICursorAttachmentLayout {
 public:
  void* mpVftable;                   // +0x00
  void* mpVftable2;                  // +0x04
  char pad8[0x78 - 8];
  void* mpVftable78;                 // +0x78
  char pad7c[0x80 - 0x7c];
  IWindow* mWin80;                   // +0x80
  IWindow* mWin84;                   // +0x84
  IWindow* mWin88;                   // +0x88
  IWindow* mWin8c;                   // +0x8c
  IWindow* mWin90;                   // +0x90
  IWindow* mWin94;                   // +0x94
  IWindow* mWin98;                   // +0x98
  unsigned short mWord9c;            // +0x9c
  bool mFlag9e;                      // +0x9e
  int  mPriceA0;                     // +0xa0

  cSPEditorSellBackRollover();       // 0x005cc520
  void Show(const wchar_t* text, int price, bool bVisible);   // 0x005cc750
};

// @ 0x005CC520
cSPEditorSellBackRollover::cSPEditorSellBackRollover() {
  mWord9c = 0;
  mpVftable = vtbl_013f8708;
  mpVftable2 = vtbl_013f7a10;
  mpVftable78 = vtbl_013f86ec;
  mWin80 = 0; mWin84 = 0; mWin88 = 0; mWin8c = 0;
  mWin90 = 0; mWin94 = 0; mWin98 = 0;
  mFlag9e = true;
  mPriceA0 = 0;
  SetKey(L"RolloverEditorSellBack", 0x40464100);
}

// @ 0x005CC750
void cSPEditorSellBackRollover::Show(const wchar_t* text, int price, bool bVisible) {
  bool needInit = mFlag9e;
  mPriceA0 = price;
  if (needInit)
    ((CRolloverVtbl*)mpVftable)->SetKey(mWord9c);

  if (!mWin80 || !mWin88 || !mWin84 || !mWin8c || !mWin90 || !mWin94 || !mWin98)
    return;

  mWin94->SetText((void*)text);
  mWin98->SetText((void*)text);
  FUN_005994b0(mWin94)->SetVisible(1);
  FUN_005994b0(mWin98)->SetVisible(1);
  FUN_005994b0(mWin94)->SetVisible(0);
  FUN_005994b0(mWin98)->SetVisible(0);

  wchar_t buf[64];
  FUN_008822e0(mPriceA0, 0, 0x13ec5a0, mWord9c, buf, 0x28, 0);
  mWin8c->SetText(buf);
  mWin90->SetText(buf);
  FUN_005994b0(mWin8c)->SetVisible(0);
  FUN_005994b0(mWin90)->SetVisible(0);

  Vector2* pA = (Vector2*)mWin94->GetPos0();
  float hA = pA->x;
  Vector2* pB = (Vector2*)mWin8c->GetPos0();
  float hB = pB->x;
  float h = hB > hA ? ((Vector2*)mWin8c->GetPos0())->x
                    : ((Vector2*)mWin94->GetPos0())->x;
  Vector2* t = (Vector2*)mWin94->GetPos1();
  float yTop = t->y;
  mWin8c->SetSize(yTop + 7.0f, h + 5.0f);
  mWin90->SetSize(yTop + 9.0f, h + 5.0f);

  Vector2* sh = (Vector2*)mWin8c->GetPos0();
  float sy = sh->y;
  Vector2* tx = (Vector2*)mWin80->GetPos0();
  float txx = tx->x, txy = tx->y;
  Vector2* t2 = (Vector2*)mWin84->GetPos0();
  float t2x = t2->x, t2y = t2->y;
  Vector2* c = (Vector2*)mWin8c->GetPos1();

  Vector2 vText, vShadow, vPrice;
  vText.x = txx;                     vText.y = txy;
  vText.y = t2y + h + 7.0f;
  vShadow.x = t2x;                   vShadow.y = t2y + h + 5.0f;
  vPrice.x = sy;                     vPrice.y = h + 5.0f;
  mWin84->SetPosition((const Vector2*)&vText);
  mWin88->SetPosition((const Vector2*)&vShadow);
  mWin80->SetPosition((const Vector2*)&vPrice);

  mWin84->GetPos1();
  mWin88->GetPos1();

  mWin8c->SetStyle(bVisible ? 0xffff0000 : 0x00000000);
  mWin84->SetFlag(1, bVisible);
  mWin88->SetFlag(1, !bVisible);

  mWin94->Update();
  mWin98->Update();
  mWin8c->Update();
  mWin90->Update();
  mWin80->SetFlag(1, 1);
}

// --- cSPEditorShoppingTokenTranslator (0x005ccbb0 ctor, 0x005ccc00 dtor) ---------------------
// eastl::basic_string<wchar_t> sub-object: four words (begin, end, cap, allocator).
class cEAWString16 {
 public:
  void* mpBegin;                     // +0x00
  void* mpEnd;                       // +0x04
  void* mpCap;                       // +0x08
  void* mpAllocator;                 // +0x0c
  void range_initialize(const wchar_t* s);   // 0x00579a90
};

class cSPEditorShoppingTokenTranslator : public cStringTokenTranslator {
 public:
  void*        mpVftable;            // +0x00
  char         pad4[0x08 - 4];
  cEAWString16 mStr1;                // +0x08
  cEAWString16 mStr2;                // +0x18
  char         pad28[0x68 - 0x28];
  cEAWString16 mStr3;                // +0x68

  cSPEditorShoppingTokenTranslator();          // 0x005ccbb0
  ~cSPEditorShoppingTokenTranslator();         // 0x005ccc00
};

// @ 0x005CCBB0
cSPEditorShoppingTokenTranslator::cSPEditorShoppingTokenTranslator() {
  mpVftable = vtbl_013f8798;
  mStr1.mpBegin = 0; mStr1.mpEnd = 0; mStr1.mpCap = 0;
  mStr1.range_initialize(L"UnsetName");
  mStr2.mpBegin = g_01667bac;
  mStr2.mpEnd = g_01667bac;
  mStr2.mpCap = g_01667bae;
  mStr3.mpBegin = g_01667bac;
  mStr3.mpEnd = g_01667bac;
  mStr3.mpCap = g_01667bae;
}

// @ 0x005CCC00
cSPEditorShoppingTokenTranslator::~cSPEditorShoppingTokenTranslator() {
  mpVftable = vtbl_013f8798;
  if (((int)((char*)mStr3.mpCap - (char*)mStr3.mpBegin) & ~1) > 2 && mStr3.mpBegin)
    EASTL_allocator_deallocate(mStr3.mpBegin);
  if (((int)((char*)mStr2.mpCap - (char*)mStr2.mpBegin) & ~1) > 2 && mStr2.mpBegin)
    EASTL_allocator_deallocate(mStr2.mpBegin);
  if (((int)((char*)mStr1.mpCap - (char*)mStr1.mpBegin) & ~1) > 2 && mStr1.mpBegin)
    EASTL_allocator_deallocate(mStr1.mpBegin);
}

