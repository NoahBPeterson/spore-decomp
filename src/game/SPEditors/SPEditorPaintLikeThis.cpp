// src/game/SPEditors/SPEditorPaintLikeThis.cpp -- migrated from slice(s) s005bfb90 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorPaintLikeThis.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Messaging/Server.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cISPEditorNameProvider.h"
#include "SP/cSPEditorNaming.h"
#include "SP/cSPEditorPageControls.h"
#include "SP/cSPEditorPaintLikeThis.h"
#include "SP/cSPNameGuard.h"
#include "SP/cSPPaletteCategoryUI.h"
#include <new>
#include <string.h>

// ---- items of slice s005bfb90 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
namespace EA {
namespace ResourceMan {
struct Key_s005b_fb90 {
  unsigned int mInstance, mType, mGroup;
  Key_s005b_fb90(unsigned int i, unsigned int t, unsigned int g) : mInstance(i), mType(t), mGroup(g) {}
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005b_fb90;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005b_fb90 {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2)
  virtual void* Cast(uint32_t typeID);                  // +0xc
  PV(4) PV(5) PV(6)
  virtual uint32_t GetControlID();                      // +0x1c
  PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual const wchar_t* GetCaption();                  // +0x3c
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);           // +0x7c
  virtual void SetCaption(const wchar_t* text);         // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41)
  virtual IWindow_s005b_fb90* GetDrawable();                       // +0xa8
  PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s005b_fb90* proc);              // +0x104
  virtual void RemoveWinProc(IWinProc_s005b_fb90* proc);           // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005b_fb90 {
 public:
  ~IWinProc_s005b_fb90() {}
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4)
  virtual bool HandleUIMessage(IWindow_s005b_fb90* window, const void* message);  // +0x14
  PV(6)
};
}
}
using EA::UTFWin::IWindow_s005b_fb90;
namespace SP {
namespace SPUIHelpers {
void SetWindowImage(IWindow_s005b_fb90* window, const EA::ResourceMan::Key_s005b_fb90* key, int flags);
}
}
namespace SP {
class cSPEditorPaintLikeThis_s005b_fb90 {
 public:
  char pad00[0x94];
  EA::ResourceMan::Key_s005b_fb90 mDefaultKey;  // +0x94
  char padA0[0xb4 - 0xa0];
  IWindow_s005b_fb90* mWinRoot;                 // +0xb4
  void SetImage(EA::ResourceMan::Key_s005b_fb90 key);  // 0x005c0ba0 (SP::cSPEditorPaintLikeThis::SetImage)
};
}
// ---- items of slice s005bfb90 end

// @ 0x005c0ba0
namespace SP {
void cSPEditorPaintLikeThis_s005b_fb90::SetImage(EA::ResourceMan::Key_s005b_fb90 key)
{
  key.mType = 0x2f7d0004;
  if (key.mInstance == 0)
    SPUIHelpers::SetWindowImage(mWinRoot, &mDefaultKey, -1);
  else
    SPUIHelpers::SetWindowImage(mWinRoot, &key, -1);
  if (mWinRoot)
    mWinRoot->SetFlag(1, true);
}
}  // namespace SP
