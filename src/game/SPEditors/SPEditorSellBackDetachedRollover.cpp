// src/game/SPEditors/SPEditorSellBackDetachedRollover.cpp -- migrated from slice(s) s005cbfd0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorSellBackDetachedRollover.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorSellBackDetachedRollover.h"
#include "EA/UTFWin/IWindow.h"
#include "SP/cSPEditorSellBackRollover.h"
#include "cSPUILayout.h"
#include "cSPUILayoutManager.h"
#include <new>

// ---- items of slice s005cbfd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
namespace EA {
namespace UTFWin {
class IUnknown32 {
 public:
  virtual int AddRef();   // +0
  virtual int Release();  // +4
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005c_bfd0 : public IUnknown32 {
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
  virtual void SetParent(IWindow_s005c_bfd0* parent);      // +0xd8
};
}
}
using EA::UTFWin::IWindow_s005c_bfd0;
class cSPUILayout_s005c_bfd0 {
 public:
  IWindow_s005c_bfd0* FindWindowByID(unsigned int id, bool recursive);  // 0x008105b0
};
class cSPUILayoutManager_s005c_bfd0 {
 public:
  IWindow_s005c_bfd0* GetWorldMainWindow();  // 0x00810620
};
cSPUILayoutManager_s005c_bfd0* __stdcall SPUIHelpers_GetLayoutManager(unsigned int id);  // 0x00805070
class cDetachedRollover {
 public:
  bool BaseInit();  // 0x00828250 (cSPUIPropertyLayout::Init)
  bool Init(unsigned short value);   // 0x005cbfd0
  void HideWin();                    // 0x005cc0e0
  bool IsWinVisible();               // 0x005cc100

  char pad0[0xc];
  cSPUILayout_s005c_bfd0 mLayout;               // +0xc
  char pad10[0x78 - 0x10];
  IWindow_s005c_bfd0* mWin;                     // +0x78
  IWindow_s005c_bfd0* mWin7c;                   // +0x7c
  IWindow_s005c_bfd0* mWin80;                   // +0x80
  IWindow_s005c_bfd0* mWin84;                   // +0x84
  IWindow_s005c_bfd0* mWin88;                   // +0x88
  IWindow_s005c_bfd0* mWin8c;                   // +0x8c
  IWindow_s005c_bfd0* mWin90;                   // +0x90
  unsigned short mWord94;            // +0x94
  bool mFlag96;                      // +0x96
};
// ---- items of slice s005cbfd0 end

// @ 0x005cbfd0
bool cDetachedRollover::Init(unsigned short value)
{
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
      IWindow_s005c_bfd0* p88 = mLayout.FindWindowByID(0x925f2dc4, true);
      mWord94 = value;
      mWin88 = p88;
      if (!mWin->GetLayout()) {
        IWindow_s005c_bfd0* main = SPUIHelpers_GetLayoutManager(0x5b598fa)->GetWorldMainWindow();
        main->SetParent(mWin);
      }
    }
    mFlag96 = false;
  }
  return ok;
}

// @ 0x005cc0e0
void cDetachedRollover::HideWin()
{
  if (!mFlag96 && mWin)
    mWin->SetFlag(1, false);
}

// @ 0x005cc100
bool cDetachedRollover::IsWinVisible()
{
  if (!mFlag96 && mWin)
    return mWin->GetFlag() & 1;
  return false;
}

// @ 0x005cc120
void SP::cSPEditorSellBackDetachedRollover::Show(wchar_t const * a, int b, bool a3)
{
    int a_v = (int)a;
  (void)a_v;
  (void)b;
}

// @ 0x005cc520
void cSellBackRolloverCtor(void* a)
{
  (void)a;
}
