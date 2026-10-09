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
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
  virtual void SetStyle(int style);             // +0x5c
  PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);   // +0x7c
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43)
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
// Large functions: signature-only stubs (partial).
class cSPEditorSellBackDetachedRollover {
 public:
  void Show(int a, int b);
};
// @ 0x005CC120
void cSPEditorSellBackDetachedRollover::Show(int a, int b) {
  (void)a;
  (void)b;
}

class cSPEditorSellBackRollover {
 public:
  void Show(int a, int b);
};
// @ 0x005CC750
void cSPEditorSellBackRollover::Show(int a, int b) {
  (void)a;
  (void)b;
}

// @ 0x005CC520
void cSellBackRolloverCtor(void* a) {
  (void)a;
}

// @ 0x005CCBB0
void cShoppingTokenTranslatorCtor(void* a) {
  (void)a;
}

// @ 0x005CCC00
void cShoppingTokenTranslatorDtor(void* a) {
  (void)a;
}
