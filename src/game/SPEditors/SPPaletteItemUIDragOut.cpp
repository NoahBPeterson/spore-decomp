// src/game/SPEditors/SPPaletteItemUIDragOut.cpp -- migrated from slice(s) s005ee480 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPaletteItemUIDragOut.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Messaging/AutoHandler.h"
#include "EA/Messaging/IHandler.h"
#include "EA/ResourceMan/Key.h"
#include "EA/Stopwatch.h"
#include "SP/cISPPaletteItemUI.h"
#include "SP/cSPPaletteInfo.h"
#include "SP/cSPPaletteItem.h"
#include "SP/cSPPaletteItemUI.h"
#include "SP/cSPPaletteItemUIOneClickPaint.h"
#include "SP/cSPPaletteItemUISelectable.h"
#include "SP/cSPSwatch.h"
#include "cSPUILayout.h"
#include "cSPUIPropertyLayout.h"
#include <new>
#include <intrin.h>

// ---- items of slice s005ee480 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
namespace EA {
template <typename T>
class AutoRefCount_s005e_e480 {
 public:
  T* mpObject;
  AutoRefCount_s005e_e480() : mpObject(0) {}
  AutoRefCount_s005e_e480(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005e_e480() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005e_e480& operator=(T* p) {
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
  T*& AsOutParam() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return mpObject;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005e_e480 {
 public:
  RefCountVTemplate_s005e_e480() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005e_e480() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005e_e480 {
 public:
  ~IUnknown32_s005e_e480() {}
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};  // namespace COM
}
}
namespace EA {
namespace ResourceMan {
struct Key_s005e_e480 {
  unsigned int mInstance, mType, mGroup;
  Key_s005e_e480() {}
  Key_s005e_e480(unsigned int instance, unsigned int type, unsigned int group) {
    mType = type;
    mGroup = group;
    mInstance = instance;
  }
};  // namespace ResourceMan
}
}
namespace EA {
struct RectT_s005e_e480 {
  float left, top, right, bottom;
  RectT_s005e_e480() {}
  RectT_s005e_e480(const RectT_s005e_e480& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
};
}
namespace EA {
namespace UTFWin {
class IWinProc_s005e_e480;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005e_e480 : public COM::IUnknown32_s005e_e480 {
 public:
  PV(3)
  virtual IWindow_s005e_e480* GetParent();                    // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual uint32_t GetFlags();                     // +0x28
  PV(11) PV(12)
  virtual const RectT_s005e_e480& GetRealArea();              // +0x34
  virtual const RectT_s005e_e480& GetArea();                  // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
  virtual void SetLayer(int layer);                // +0x5c
  virtual void SetArea(const RectT_s005e_e480& area);         // +0x60
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);      // +0x7c
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
  virtual void SetShadeColor(uint32_t color);      // +0xac
  PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57)
  PV(58)
  virtual void AddWindow(IWindow_s005e_e480* child);          // +0xec
  virtual IWindow_s005e_e480* FindWindowByID(uint32_t id, bool recursive);  // +0xf0
  PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s005e_e480* proc);         // +0x104
  virtual void RemoveWinProc(IWinProc_s005e_e480* proc);      // +0x108
};
}
}
namespace EA {
namespace UTFWin {
struct Message_s005e_e480 {
  uint32_t pad0[2];
  int mEventType;
  int mParam0c;
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005e_e480 : public COM::IUnknown32_s005e_e480 {
 public:
  virtual int GetEventFlags();
  virtual bool DoMessage(IWindow_s005e_e480* window, const Message_s005e_e480& message) = 0;
};
}
}
using EA::AutoRefCount_s005e_e480;
using EA::ResourceMan::Key_s005e_e480;
using EA::UTFWin::IWindow_s005e_e480;
using EA::UTFWin::IWinProc_s005e_e480;
using EA::UTFWin::Message_s005e_e480;
using EA::RectT_s005e_e480;
class cSPUIPropertyLayout_s005e_e480;
namespace SP {
class cSPEditorEconomy_s005e_e480;
}
namespace SP {
class cCollectableItems_s005e_e480;
}
namespace SP {
struct cSPPaletteInfo_s005e_e480 {
  virtual ~cSPPaletteInfo_s005e_e480();
  virtual int AddRef();
  virtual int Release();
  int mRefCount;                            // +0x4
  cSPEditorEconomy_s005e_e480* mEconomy;               // +0x8
  uint32_t mPad0c;
  cCollectableItems_s005e_e480* mCollectableItems;     // +0x10
  uint32_t mPad14;
  wchar_t mCurrencyChar;                    // +0x18
  uint32_t mPad1c[4];
  uint32_t mModelType;                      // +0x2c
};
}
namespace SP {
class cSPPaletteItem_s005e_e480 : public EA::RefCountVTemplate_s005e_e480<int>, public EA::COM::IUnknown32_s005e_e480 {
 public:
  virtual int AddRef();
  virtual int Release();
  bool IsUnlocked(cCollectableItems_s005e_e480* items);   // 0x005c6630
  bool IsNew(cCollectableItems_s005e_e480* items);        // 0x005c6670
  Key_s005e_e480 mItemKey;          // +0xc
  Key_s005e_e480 mThumbnailKey;     // +0x18
};
}
namespace SP {
class cSPEditorVehicleAbilities {
 public:
  cSPEditorVehicleAbilities(Key_s005e_e480 key, uint32_t modelType, uint32_t layoutID, uint32_t textID, bool b);  // 0x0059f030
  virtual ~cSPEditorVehicleAbilities();
  virtual int AddRef();
  virtual int Release();
  uint32_t mData[24];
};
}
namespace SP {
class cSPSwatch_s005e_e480 : public IWinProc_s005e_e480 {
 public:
  PV(5) PV(6)
  virtual void Shutdown();              // +0x1c
  virtual void SetLocked(bool locked);  // +0x20
  PV(9) PV(10)
  virtual void SetShowLock(bool show);  // +0x2c
  virtual bool IsLocked();              // +0x30
  PV(13)
  virtual void SetHighlight(bool on);   // +0x38
  bool Init(const Key_s005e_e480* key, IWindow_s005e_e480* window, bool a, int b, bool c, int d, int e);  // 0x005f4f80
  void PlayEffect(uint32_t id, bool b);  // 0x005f2d00
  char pad[0x80];
  float mX;   // +0x84
  float mY;   // +0x88
};
}
namespace SP {
class cEditorUI {
 public:
  cSPSwatch_s005e_e480* CreateSwatch(int type);            // 0x005f0ca0
  void RemoveContent(cSPSwatch_s005e_e480* content);       // 0x005f0a60
  ::cSPUIPropertyLayout_s005e_e480* GetPropertyLayout();  // 0x0113ae10
};
}
namespace SP {
cEditorUI* GetEditorUI();  // 0x00401020
}
class cSPUIPropertyLayout_s005e_e480 {
 public:
  void SetItem(SP::cSPPaletteItem_s005e_e480* item, SP::cSPPaletteInfo_s005e_e480* info, SP::cSPEditorVehicleAbilities* content,
               bool show);
  void SetContents(const Key_s005e_e480* key, SP::cSPEditorVehicleAbilities* content, SP::cSPEditorEconomy_s005e_e480* economy,
                   wchar_t currency, bool unlocked, bool show);    // 0x005ed750
  void SetMode(int mode);                                           // 0x005ed320
  void SetPositionAndOffset(float x, float y, float dx, float dy);  // 0x008283a0
  char pad[0xb0];
  AutoRefCount_s005e_e480<SP::cSPPaletteInfo_s005e_e480> mpPaletteInfo;  // +0xb0
};
namespace SP {
class cISPPaletteItemUI_s005e_e480 {
 public:
  cISPPaletteItemUI_s005e_e480() : mInterfaceID(-1) {}
  virtual ~cISPPaletteItemUI_s005e_e480() {}
  virtual void Init(cSPPaletteItem_s005e_e480* item, IWindow_s005e_e480* window, int a, cSPPaletteInfo_s005e_e480* info) = 0;  // +0x4
  virtual void Shutdown() = 0;                    // +0x8
  PV(3)
  virtual cSPPaletteItem_s005e_e480* GetPaletteItem();       // +0x10
  virtual void Trigger();                         // +0x14
  virtual void Update(float dt);                  // +0x18
  virtual void OnRollover() = 0;                  // +0x1c
  virtual void OffRollover() = 0;                 // +0x20
  virtual void OnMouseDown();                     // +0x24
  virtual void OnMouseUp();                       // +0x28
  PV(11)

  AutoRefCount_s005e_e480<cSPPaletteItem_s005e_e480> mPaletteItem;  // +0x4
  int mInterfaceID;                           // +0x8
};
}
namespace SP {
class cSPPaletteItemUI_s005e_e480 : public cISPPaletteItemUI_s005e_e480, public IWinProc_s005e_e480, public EA::RefCountVTemplate_s005e_e480<int> {
 public:
  cSPPaletteItemUI_s005e_e480();   // 0x005c6bf0
  ~cSPPaletteItemUI_s005e_e480();  // 0x005c6c50
  virtual void Init(cSPPaletteItem_s005e_e480* item, IWindow_s005e_e480* window, int a, cSPPaletteInfo_s005e_e480* info);  // 0x005c6ca0
  virtual void Shutdown();     // 0x005c6d20
  virtual void OnRollover();   // 0x005c6f00
  virtual void OffRollover();  // 0x005c6f40
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual bool DoMessage(IWindow_s005e_e480* window, const Message_s005e_e480& message);  // 0x005c6d70 (SP::cSPPaletteItemUI::DoMessage)

  bool mIsRolledOver;               // +0x18
  AutoRefCount_s005e_e480<IWindow_s005e_e480> mWinRoot;   // +0x1c
};
}
namespace SP {
class cSPPaletteItemUIDrag : public cSPPaletteItemUI_s005e_e480 {
 public:
  cSPPaletteItemUIDrag();
  virtual ~cSPPaletteItemUIDrag() {}
  virtual void Init(cSPPaletteItem_s005e_e480* item, IWindow_s005e_e480* window, int a, cSPPaletteInfo_s005e_e480* info);
  virtual void Shutdown();
  virtual void* Cast(uint32_t typeID) const;
  virtual void OnSelected();    // +0x30
  virtual void OnDeselected();  // +0x34

  AutoRefCount_s005e_e480<cSPSwatch_s005e_e480> mSwatch;  // +0x20
};
}
// ---- items of slice s005ee480 end

// @ 0x005ee500
namespace SP {
void* cSPPaletteItemUIDrag::Cast(uint32_t typeID) const
{
  switch ((int)typeID) {
    case 0x4784b27:
      return (cSPPaletteItemUIDrag*)this;
    case (int)0xee3f516e:
    case 0x2f009dd0:
      return (IWinProc_s005e_e480*)this;
    case 0x71fa7d3f:
      return (cSPPaletteItemUIDrag*)this;
  }
  return 0;
}
}  // namespace SP

// @ 0x005ee540
namespace SP {
cSPPaletteItemUIDrag::cSPPaletteItemUIDrag()
{
  mInterfaceID = 0x71fa7d3f;
}
}  // namespace SP

// @ 0x005ee5e0
namespace SP {
void cSPPaletteItemUIDrag::Init(cSPPaletteItem_s005e_e480* item, IWindow_s005e_e480* window, int a, cSPPaletteInfo_s005e_e480* info)
{
  if (item && window) {
    mSwatch = GetEditorUI()->CreateSwatch(0);
    mSwatch->Init(&item->mItemKey, window, true, 0, true, 0, -1);
    cSPPaletteItemUI_s005e_e480::Init(item, window, a, info);
  }
}
}  // namespace SP

// @ 0x005ee660
namespace SP {
void cSPPaletteItemUIDrag::Shutdown()
{
  if (mSwatch) {
    GetEditorUI()->RemoveContent(mSwatch);
    mSwatch.AsOutParam();
  }
  cSPPaletteItemUI_s005e_e480::Shutdown();
}
}  // namespace SP

// @ 0x005ee6a0
namespace SP {
void cSPPaletteItemUIDrag::OnSelected()
{
  if (mWinRoot) mWinRoot->SetShadeColor(0x8800bbbb);
  Trigger();
}
}  // namespace SP

// @ 0x005ee6d0
namespace SP {
void cSPPaletteItemUIDrag::OnDeselected()
{
  if (mWinRoot) mWinRoot->SetShadeColor(0xffffff);
}
}  // namespace SP
