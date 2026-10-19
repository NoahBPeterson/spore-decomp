// src/game/SPEditors/SPEditorPaletteItemUI.cpp -- migrated from slice(s) s005c7500, s005c6340 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorPaletteItemUI.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPaletteItemUISelectable.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Messaging/IHandlerRC.h"
#include "EA/Messaging/Server.h"
#include "EA/ResourceMan/Key.h"
#include "EA/Variant.h"
#include "SP/cISPPaletteItemUI.h"
#include "SP/cPropertyList.h"
#include "SP/cSPPalette.h"
#include "SP/cSPPaletteItem.h"
#include "SP/cSPPaletteItemRollover.h"
#include "SP/cSPPaletteItemUI.h"
#include "cSPUIPropertyLayout.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p);                       // 0x00f47380
#include <new>
#include "SP/cSPOLDPaletteItemUI.h"
#include "SP/cSPPaletteCategory.h"
#include "SP/cSPPalettePage.h"
#include "SP/cSPSwatch.h"
#include "cSPUILayout.h"
#include "cSPUITooltipWinProc.h"
#include "SP/cString.h"

// ---- items of slice s005c6340 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p);                       // 0x00f47380
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                     const char* file, int line);                           // 0x00f473a0
#define PV(n) virtual void pv##n();
namespace EA {
template <typename T>
class AutoRefCount_s005c_6340 {
 public:
  T* mpObject;
  AutoRefCount_s005c_6340() : mpObject(0) {}
  AutoRefCount_s005c_6340(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005c_6340() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005c_6340& operator=(T* p) {
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
  T** AsPPTypeParam();  // 0x00a16f40 (out of line)
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005c_6340 {
 public:
  RefCountVTemplate_s005c_6340() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005c_6340() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005c_6340 {
 public:
  ~IUnknown32_s005c_6340() {}
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};  // namespace COM
}
}
namespace EA {
namespace ResourceMan {
struct Key_s005c_6340 {
  unsigned int mInstance, mType, mGroup;
};
}
}
namespace EA {
struct RectT_s005c_6340 {
  float left, top, right, bottom;
  RectT_s005c_6340(const RectT_s005c_6340& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
};
}
namespace EA {
namespace UTFWin {
class IWinProc_s005c_6340;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005c_6340 : public COM::IUnknown32_s005c_6340 {
 public:
  PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual const RectT_s005c_6340& GetRealArea();  // +0x34
  virtual const RectT_s005c_6340& GetArea();      // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27)
  PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40)
  PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53)
  PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s005c_6340* proc);     // +0x104
  virtual void RemoveWinProc(IWinProc_s005c_6340* proc);  // +0x108
};
}
}
namespace EA {
namespace UTFWin {
struct Message_s005c_6340 {
  uint32_t pad0[2];
  int mEventType;   // +0x8
  int mParam0c;     // +0xc
  uint32_t pad10[2];
  int mButton;      // +0x18
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005c_6340 : public COM::IUnknown32_s005c_6340 {
 public:
  virtual int GetEventFlags();
  virtual bool DoMessage(IWindow_s005c_6340* window, const Message_s005c_6340& message) = 0;
};
}
}
namespace EA {
namespace UTFWin {
class IWindowManager {
 public:
  PV(0)
  virtual IWindow_s005c_6340* GetMainWindow();  // +0x4
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
  virtual IWindow_s005c_6340* GetCapture(int which);  // +0x48
};
}
}
namespace EA {
namespace Messaging {
class IHandler_s005c_6340 {
 public:
  virtual bool HandleMessage(uint32_t messageID, void* message) = 0;
};
}
}
namespace EA {
namespace Messaging {
class IHandlerRC_s005c_6340 : public IHandler_s005c_6340 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
};
}
}
namespace EA {
namespace Messaging {
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void MessageSend(uint32_t messageID, void* message, IHandler_s005c_6340* handler);       // +0x14
  PV(6) PV(7)
  virtual void AddHandler(IHandlerRC_s005c_6340* handler, uint32_t messageID);                     // +0x20
  PV(9) PV(10)
  virtual void RemoveHandler(IHandlerRC_s005c_6340* handler, uint32_t messageID, int priority);    // +0x2c
};
}
}
using EA::AutoRefCount_s005c_6340;
using EA::ResourceMan::Key_s005c_6340;
using EA::UTFWin::IWindow_s005c_6340;
using EA::UTFWin::IWinProc_s005c_6340;
using EA::UTFWin::Message_s005c_6340;
using EA::RectT_s005c_6340;
namespace eastl {
template <typename T, int kAllocatorWords = 2>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[kAllocatorWords];
  sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector() {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
  T* begin() { return mpBegin; }
  T* end() { return mpEnd; }
};  // namespace eastl
}
namespace SP {
EA::Messaging::IMessageServer* MessageServer();                                     // 0x0067dcc0
}
namespace SP {
EA::UTFWin::IWindowManager* WindowManager();                                        // 0x0067caa0
}
namespace SP {
bool IsKeyDown(int key);                                                            // 0x008d2fb0
}
namespace SP {
bool IsDescendant(IWindow_s005c_6340* window, IWindow_s005c_6340* child);                                 // 0x00805150
}
namespace SP {
int GetAudioSystem();                                                               // 0x00435e90
}
namespace SP {
void PlayAudio(uint32_t id, int system);                                            // 0x00435ed0
}
namespace SP {
enum eModelType_s005c_6340 {};
}
namespace SP {
class cSPPaletteCategory_s005c_6340;
}
namespace SP {
class cSPPalette_s005c_6340 : public EA::RefCountVTemplate_s005c_6340<int>, public EA::COM::IUnknown32_s005c_6340 {
 public:
  eastl::sp_vector<AutoRefCount_s005c_6340<cSPPaletteCategory_s005c_6340>, 1> mCategories;  // +0xc
  unsigned int mLayoutInstanceID;     // +0x1c
  unsigned int mImageGroupID;         // +0x20
  unsigned int mOptionalImageGroupID; // +0x24
  int mStartupCategory;               // +0x28
  eModelType_s005c_6340 mModelType;              // +0x2c
  unsigned int mPaletteGroupID;       // +0x30
  unsigned int mParam34;              // +0x34
  int mThemeIndex;                    // +0x38
  unsigned int mParam3c;              // +0x3c

  virtual int AddRef();
  virtual int Release();
  bool Init(const Key_s005c_6340& key, unsigned int param3c, unsigned int param34, unsigned int imageGroupID,
            unsigned int optionalImageGroupID, int startupCategory, eModelType_s005c_6340 modelType);
  void LoadDefinitionPart(const Key_s005c_6340& key);  // 0x005c6010
};
}
namespace SP {
class cSPPaletteItem_s005c_6340 : public EA::RefCountVTemplate_s005c_6340<int>, public EA::COM::IUnknown32_s005c_6340 {
 public:
  enum eItemType {
    kItemTypeUnknown = -1,
    kBlock = 0xa2e50993,
    kBakedModel = 0x674ab27,
    kSwatch = 0x2c7c0887,
  };
  Key_s005c_6340 mItemKey;          // +0xc
  Key_s005c_6340 mThumbnailKey;     // +0x18
  eItemType mItemType;   // +0x24
  int mPriority;         // +0x28
  Key_s005c_6340 mSwatchKey;        // +0x2c
  uint32_t mSwatchColor; // +0x38
  Key_s005c_6340 mSwatchKey2;       // +0x3c
  int mIndex;            // +0x48
  bool mbHidden;         // +0x4c
  AutoRefCount_s005c_6340<EA::COM::IUnknown32_s005c_6340> mpData;  // +0x50

  virtual int AddRef();
  virtual int Release();
  bool Init(const Key_s005c_6340& key, int index, uint32_t thumbnailGroup);  // 0x005c6810 (SP::cSPPaletteItem::Init)
  void Shutdown();  // 0x005c6710 (SP::cSPPaletteItem::Shutdown)
};
}
namespace SP {
struct cTargetInner {
  PV(0) PV(1) PV(2)
  virtual void* Cast(uint32_t typeID);  // +0xc
};
}
namespace SP {
struct cItemTarget {
  uint32_t pad[2];
  cTargetInner mInner;  // +0x8
};
}
namespace SP {
class cISPPaletteItemUI_s005c_6340 {
 public:
  enum eItemUIInterfaceID { kItemUIUnknown = -1 };
  cISPPaletteItemUI_s005c_6340() : mInterfaceID(kItemUIUnknown) {}
  virtual ~cISPPaletteItemUI_s005c_6340() {}
  virtual void Init(cSPPaletteItem_s005c_6340* item, IWindow_s005c_6340* window, int a, int b) = 0;  // +0x4
  virtual void Shutdown() = 0;                                              // +0x8
  PV(3)
  virtual struct cItemTarget* GetTarget();                                  // +0x10
  PV(5) PV(6)
  virtual void OnRollover() = 0;                                            // +0x1c
  virtual void OffRollover() = 0;                                           // +0x20
  virtual void OnMouseDown();                                               // +0x24
  virtual void OnMouseUp();                                                 // +0x28
  PV(11) PV(12) PV(13) PV(14)
  virtual void Select();                                                    // +0x3c
  virtual void Deselect();                                                  // +0x40

  AutoRefCount_s005c_6340<cSPPaletteItem_s005c_6340> mPaletteItem;  // +0x4
  eItemUIInterfaceID mInterfaceID;            // +0x8
};
}
namespace SP {
class cSPPaletteItemUI_s005c_6340 : public cISPPaletteItemUI_s005c_6340, public IWinProc_s005c_6340, public EA::RefCountVTemplate_s005c_6340<int> {
 public:
  cSPPaletteItemUI_s005c_6340();
  ~cSPPaletteItemUI_s005c_6340();
  virtual void Init(cSPPaletteItem_s005c_6340* item, IWindow_s005c_6340* window, int a, int b);  // 0x005c6ca0 (SP::cSPPaletteItemUI::Init)
  virtual void Shutdown();  // 0x005c6d20 (SP::cSPPaletteItemUI::Shutdown)
  virtual void OnRollover();  // 0x005c6f00 (SP::cSPPaletteItemUI::OnRollover)
  virtual void OffRollover();  // 0x005c6f40 (SP::cSPPaletteItemUI::OffRollover)
  void Trigger();  // 0x005c73d0 (SP::cSPPaletteItemUI::Trigger)
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual bool DoMessage(IWindow_s005c_6340* window, const Message_s005c_6340& message);  // 0x005c6d70 (SP::cSPPaletteItemUI::DoMessage)

  bool mIsRolledOver;               // +0x18
  AutoRefCount_s005c_6340<IWindow_s005c_6340> mWinRoot;   // +0x1c
};
}
namespace SP {
struct RolloverMessage {
  RolloverMessage(uint32_t id) : mID(id) {}
  void SetSource(IWinProc_s005c_6340* source) { mpSource = source; }
  IWinProc_s005c_6340* mpSource;
  uint32_t mPad4;
  uint32_t mID;
  uint32_t mPadC;
};
}
namespace SP {
class IMessageBase {
 public:
  virtual ~IMessageBase() {}
};
}
namespace SP {
class IMessageBase2 {
 public:
  IMessageBase2() : mRefCount(0) {}
  virtual void f();
  int mRefCount;  // +0x8
};
}
namespace SP {
class cPaletteItemMessage : public IMessageBase, public IMessageBase2 {
 public:
  cPaletteItemMessage(uint32_t id, int interfaceID)
      : mInterfaceID(interfaceID), mField14(0), mField18(0), mField1c(0) {
    mID = id;
  }
  uint32_t mID;
  int mInterfaceID;
  int mField14;
  int mField18;
  int mField1c;
  AutoRefCount_s005c_6340<EA::COM::IUnknown32_s005c_6340> mpTarget;  // +0x20
  AutoRefCount_s005c_6340<EA::COM::IUnknown32_s005c_6340> mpExtra;   // +0x24
};
}
namespace SP {
class cSPPaletteItemUISelectable_s005c_6340 : public cSPPaletteItemUI_s005c_6340, public EA::Messaging::IHandlerRC_s005c_6340 {
 public:
  cSPPaletteItemUISelectable_s005c_6340();
  virtual void Init(cSPPaletteItem_s005c_6340* item, IWindow_s005c_6340* window, int a, int b, uint32_t selectionGroup);  // 0x005c6f80 (SP::cSPPaletteItemUISelectable::Init)
  virtual void Shutdown();  // 0x005c6fd0 (SP::cSPPaletteItemUISelectable::Shutdown)
  virtual void* Cast(uint32_t typeID) const;
  virtual void SetIsSelected(bool selected);
  virtual bool HandleMessage(uint32_t messageID, void* message);
  virtual int AddRef();
  virtual int Release();

  bool mSelected;             // +0x24
  uint32_t mSelectionGroup;   // +0x28
};
}
namespace SP {
class cSPEditorVehicleAbilities {
 public:
  cSPEditorVehicleAbilities(Key_s005c_6340 key, uint32_t modelType, uint32_t layoutID, int a, bool b);  // 0x0059f030
  virtual ~cSPEditorVehicleAbilities();
  virtual int AddRef();
  virtual int Release();
  uint32_t mData[24];
};
}
namespace SP {
class cSPUIPropertyLayout {
 public:
  void SetItem(cSPPaletteItem_s005c_6340* item, cSPPalette_s005c_6340* palette, cSPEditorVehicleAbilities* content, bool show);  // 0x005ee480
  void SetMode(int mode);                                           // 0x005ed320
  void SetPositionAndOffset(float x, float y, float dx, float dy);  // 0x008283a0
  void Hide();                                                      // 0x005ed6c0
  void Remove(EA::COM::IUnknown32_s005c_6340* obj);                            // 0x005f0a60
};
}
namespace SP {
class cEditorUI {
 public:
  cSPUIPropertyLayout* GetPropertyLayout();  // 0x0113ae10
  void RemoveContent(EA::COM::IUnknown32_s005c_6340* obj);  // 0x005f0a60
};
}
namespace SP {
cEditorUI* GetEditorUI();  // 0x00401020
}
namespace SP {
class cSPPaletteItemRollover_s005c_6340 : public EA::RefCountVTemplate_s005c_6340<int>, public IWinProc_s005c_6340 {
 public:
  cSPPaletteItemRollover_s005c_6340();
  ~cSPPaletteItemRollover_s005c_6340();
  virtual int AddRef();
  virtual int Release();
  PV(3)
  virtual void OnRollover();   // +0x10
  virtual void OffRollover();  // +0x14
  void Shutdown();
  virtual void* Cast(uint32_t typeID) const;
  virtual bool DoMessage(IWindow_s005c_6340* window, const Message_s005c_6340& message);

  AutoRefCount_s005c_6340<cSPPaletteItem_s005c_6340> mpItem;          // +0xc
  AutoRefCount_s005c_6340<cSPPalette_s005c_6340> mpPalette;           // +0x10
  AutoRefCount_s005c_6340<EA::COM::IUnknown32_s005c_6340> mpContent;  // +0x14
  AutoRefCount_s005c_6340<IWindow_s005c_6340> mpWindow;               // +0x18
  bool mIsRolledOver;                           // +0x1c
};
}
// ---- items of slice s005c6340 end

// ---- items of slice s005c7500 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <typename T>
class AutoRefCount_s005c_7500 {
 public:
  T* mpObject;
  AutoRefCount_s005c_7500() : mpObject(0) {}
  AutoRefCount_s005c_7500(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s005c_7500(const AutoRefCount_s005c_7500& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005c_7500() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005c_7500& operator=(T* p) {
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
class RefCountVTemplate_s005c_7500 {
 public:
  RefCountVTemplate_s005c_7500() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005c_7500() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005c_7500 {
 public:
  ~IUnknown32_s005c_7500() {}
  virtual int AddRef();
  virtual int Release();
};  // namespace COM
}
}
namespace EA {
namespace ResourceMan {
struct Key_s005c_7500 {
  unsigned int mInstance, mType, mGroup;
  Key_s005c_7500() {}
  Key_s005c_7500(unsigned int i, unsigned int t, unsigned int g) : mInstance(i), mType(t), mGroup(g) {}
};  // namespace ResourceMan
}
}
using EA::AutoRefCount_s005c_7500;
namespace SP {
class cSPPaletteItem_s005c_7500;
}
namespace SP {
class cSPSwatch_s005c_7500;
}
namespace SP {
class cSPPaletteItem_s005c_7500 : public EA::RefCountVTemplate_s005c_7500<int>, public EA::COM::IUnknown32_s005c_7500 {
 public:
  using EA::RefCountVTemplate_s005c_7500<int>::AddRef;
  using EA::RefCountVTemplate_s005c_7500<int>::Release;
  enum eItemType {
    kItemTypeUnknown = -1,
    kBlock = 0xa2e50993,
    kBakedModel = 0x674ab27,
    kSwatch = 0x2c7c0887,
  };
  EA::ResourceMan::Key_s005c_7500 mItemKey;          // +0xc
  EA::ResourceMan::Key_s005c_7500 mThumbnailKey;     // +0x18
  eItemType mItemType;                    // +0x24
  int mPriority;                          // +0x28
  EA::ResourceMan::Key_s005c_7500 mSwatchKey;        // +0x2c
  uint32_t mSwatchColor;                  // +0x38
  EA::ResourceMan::Key_s005c_7500 mSwatchKey2;       // +0x3c
  int mIndex;                             // +0x48
  bool mbHidden;                          // +0x4c
  AutoRefCount_s005c_7500<EA::COM::IUnknown32_s005c_7500> mpData;  // +0x50
  void Shutdown();                        // 0x005c6710
  // Out-of-line trivial accessors / checks called by cSPOLDPaletteItemUI::Init.
  int GetPriority();                      // 0x00641770: return [this+0x28]
  EA::ResourceMan::Key_s005c_7500* GetPlanetKey();   // 0x00b7e380: return &[this+0x2c]
  uint32_t GetSwatchColor();              // 0x00a1ad10: return [this+0x38]
  EA::ResourceMan::Key_s005c_7500* GetCities();      // 0x005c65e0: return &[this+0x3c]
  bool IsHidden();                        // 0x005c6620: return mbHidden
  bool CheckInfo(struct SwatchInfo* info);  // 0x005c65f0, ret 4
};
}
namespace SP {
class cSPSwatch_s005c_7500 : public EA::RefCountVTemplate_s005c_7500<int>, public EA::COM::IUnknown32_s005c_7500 {
 public:
  using EA::RefCountVTemplate_s005c_7500<int>::AddRef;
  using EA::RefCountVTemplate_s005c_7500<int>::Release;
  char pad0c[0x140 - 0x0c];
};
}
namespace SP {
typedef EA::ResourceMan::Key_s005c_7500 ResKey;
}
namespace SP {
struct Rect4 {
  float x0, y0, x1, y1;
};
}
namespace SP {
class UIWindow {
 public:
  void** vptr;
  int AddRef() { return ((int(__thiscall*)(UIWindow*))vptr[0])(this); }
  int Release() { return ((int(__thiscall*)(UIWindow*))vptr[1])(this); }
  Rect4* GetArea() { return ((Rect4*(__thiscall*)(UIWindow*))vptr[0x38 / 4])(this); }
  UIWindow* FindWindowByID(uint32_t id, bool recurse) {
    return ((UIWindow*(__thiscall*)(UIWindow*, uint32_t, bool))vptr[0xf0 / 4])(this, id, recurse);
  }
  void SetField60(int v) { ((void(__thiscall*)(UIWindow*, int))vptr[0x60 / 4])(this, v); }
  void SetFlag(int mask, bool on) {
    ((void(__thiscall*)(UIWindow*, int, bool))vptr[0x7c / 4])(this, mask, on);
  }
  void AddChild(UIWindow* w) { ((void(__thiscall*)(UIWindow*, UIWindow*))vptr[0xd8 / 4])(this, w); }
  void AddWinProc(void* proc) { ((void(__thiscall*)(UIWindow*, void*))vptr[0x104 / 4])(this, proc); }
};
}
namespace SP {
template <typename T>
class WinRef {
 public:
  T* mpObject;
  WinRef() : mpObject(0) {}
  ~WinRef() { if (mpObject) mpObject->Release(); }
  WinRef& operator=(T* p) {
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
  void SetOol(T* p);  // 0x00b5f950: AutoRefCount<T>::operator=(T*), not inlined
  operator T*() const { return mpObject; }
  T* operator->() const { return mpObject; }
};
}
namespace SP {
struct SwatchInfo {
  bool Has(uint64_t key);  // 0x00595110, ret 8
};
}
namespace SP {
class SwatchVerifier {
 public:
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual int Query(const ResKey* key, int arg);  // slot 4
};
}
namespace SP {
struct SwatchView {
  int pad0;
  int pad4;
  SwatchVerifier* mVerifier;  // +8
  int pad0c;
  SwatchInfo* mInfo;          // +0x10
};
}
namespace SP {
class cSPUILayout {
 public:
  cSPUILayout();                                                // 0x00810000
  ~cSPUILayout();                                               // 0x00811fe0
  void Init(const ResKey* key, bool flag, uint32_t id);         // 0x008120d0
  UIWindow* FindWindowByID(uint32_t id, bool recurse);          // 0x008105b0
  int pad[3];
};
}
namespace SP {
class cString_s005c_7500 {
 public:
  cString_s005c_7500(uint32_t table, uint32_t instance, const wchar_t* def);  // 0x006b5770
  ~cString_s005c_7500();                                                       // 0x006b5240
  const wchar_t* GetText();                                         // 0x006b55c0
  int pad[7];
};
}
namespace SP {
struct Vec2 {
  float x, y;
};
}
namespace SP {
class cSPUITooltipWinProc {
 public:
  cSPUITooltipWinProc(const wchar_t* name, uint32_t id, const wchar_t* text, const Vec2* pos,
                      int a, const void* b, int c);  // 0x00835e30, ret 0x1c
  static void* operator new(unsigned int size, unsigned int align, const char* name, void* alloc);  // 0x009512d0
  virtual int AddRef();
  virtual int Release();
  int pad[0x68 / 4 - 1];
};
}
namespace SP {
class DragAndBuy {
 public:
  DragAndBuy();  // 0x005f7380
  virtual int AddRef();
  virtual int Release();
  void Init(const ResKey* key, UIWindow* win, UIWindow* parent, uint32_t msg, cSPPaletteItem_s005c_7500* item,
            cSPSwatch_s005c_7500* swatch, bool flag);  // 0x005f4310, ret 0x1c
  static void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
  int pad[0x1c8 / 4 - 1];
};
}
namespace SP {
struct DragAndBuyRef {
  DragAndBuy* mpObject;
  DragAndBuyRef(DragAndBuy* p);  // 0x00572660
};
}
namespace SP {
class cSPSwatchManager {
 public:
  DragAndBuy* CreateSwatch(DragAndBuy* existing);  // 0x005f0ca0, ret 4
};
}
namespace SP {
cSPSwatchManager* GetSwatchManager();                                       // 0x00401020
}
namespace SP {
uint64_t MakeKey64(uint32_t hi, uint32_t lo);                                // 0x00593980
}
namespace SP {
void* GetUIAllocator();                                                     // 0x009512c0
}
namespace SP {
UIWindow* CreateWindowFor(UIWindow* parent);                                // 0x00806370
}
namespace SP {
UIWindow* CreateImageWindow(const ResKey* key, float x, float y, UIWindow* parent);  // 0x00807880
}
namespace SP {
void SetImageIcon(UIWindow* w, void* image, int a);                         // 0x00806aa0
}
namespace SP {
void CenterWindowInRect(UIWindow* w, Rect4* r);                             // 0x00806d10
}
namespace SP {
void* GetImageFromLayout(uint32_t id);                                      // 0x00458de0
}
namespace SP {
extern char* g_ptr15fd918;                                                  // 0x015fd918
}
namespace SP {
extern int g_data13f80fc;                                                   // 0x013f80fc
}
namespace SP {
inline bool EditorFlag() { return *(int*)(*(char**)(g_ptr15fd918 + 0x3c) + 0x118) != 0; }
}
namespace SP {
class cSPOLDPaletteItemUI_s005c_7500 : public EA::COM::IUnknown32_s005c_7500, public EA::RefCountVTemplate_s005c_7500<int> {
 public:
  AutoRefCount_s005c_7500<cSPPaletteItem_s005c_7500> mData;  // +0xc
  AutoRefCount_s005c_7500<cSPSwatch_s005c_7500> mSwatch;     // +0x10
  WinRef<DragAndBuy> mDragAndBuy;      // +0x14
  AutoRefCount_s005c_7500<UIWindow> mWindow;      // +0x18
  void Init(cSPPaletteItem_s005c_7500* item, UIWindow* parent, int arg3, cSPSwatch_s005c_7500* swatch);  // 0x005c7500 (SP::cSPOLDPaletteItemUI::Init)
};
}
// ---- items of slice s005c7500 end

// @ 0x005c6a30
namespace SP {
void* cSPPaletteItemUI_s005c_6340::Cast(uint32_t typeID) const
{
  switch ((int)typeID) {
    case 0x4785a3d:
    case 0x4784b27:
      return (cSPPaletteItemUI_s005c_6340*)this;
    case (int)0xee3f516e:
    case 0x2f009dd0:
      return (IWinProc_s005c_6340*)this;
  }
  return 0;
}
}  // namespace SP

// @ 0x005c6b10
namespace SP {
bool cSPPaletteItemUISelectable_s005c_6340::HandleMessage(uint32_t messageID, void* message)
{
  if (messageID == 0x47a9a20) {
    cSPPaletteItemUISelectable_s005c_6340* sender = (cSPPaletteItemUISelectable_s005c_6340*)message;
    if (sender && sender->mSelectionGroup == mSelectionGroup) {
      bool isThis = sender == this;
      if (isThis == true) {
        Select();
      } else if (isThis != mSelected) {
        Deselect();
      }
      mSelected = isThis;
    }
  }
  return false;
}
}  // namespace SP

// @ 0x005c6ba0
namespace SP {
void cSPPaletteItemRollover_s005c_6340::OffRollover()
{
  cSPUIPropertyLayout* layout = GetEditorUI()->GetPropertyLayout();
  if (layout)
    layout->Hide();
}
}  // namespace SP

// @ 0x005c6bf0
namespace SP {
cSPPaletteItemUI_s005c_6340::cSPPaletteItemUI_s005c_6340()
: mIsRolledOver(false) {}
}  // namespace SP

// @ 0x005c6c50
namespace SP {
cSPPaletteItemUI_s005c_6340::~cSPPaletteItemUI_s005c_6340()
{}
}  // namespace SP

// @ 0x005c6ca0
namespace SP {
void cSPPaletteItemUI_s005c_6340::Init(cSPPaletteItem_s005c_6340* item, IWindow_s005c_6340* window, int, int)
{
  mWinRoot = window;
  mWinRoot->AddWinProc(this);
  mPaletteItem = item;
}
}  // namespace SP

// @ 0x005c6d20
namespace SP {
void cSPPaletteItemUI_s005c_6340::Shutdown()
{
  if (mWinRoot) {
    mWinRoot->RemoveWinProc(this);
    mWinRoot.AsOutParam();
  }
  if (mPaletteItem) {
    mPaletteItem->Shutdown();
    mPaletteItem.AsOutParam();
  }
  mIsRolledOver = false;
}
}  // namespace SP

// @ 0x005c6d70
namespace SP {
bool cSPPaletteItemUI_s005c_6340::DoMessage(IWindow_s005c_6340* window, const Message_s005c_6340& message)
{
  switch (message.mEventType) {
    case 0x1c:
      if (message.mParam0c == 1 && mIsRolledOver) {
        if (!IsDescendant(mWinRoot.mpObject, WindowManager()->GetCapture(1))) {
          mIsRolledOver = false;
          OffRollover();
        }
      }
      break;
    case 0x1b:
      if (message.mParam0c == 1 && !mIsRolledOver) {
        bool shift = IsKeyDown(1000);
        bool ctrl = IsKeyDown(0x3ea);
        bool alt = IsKeyDown(0x3e9);
        if (!shift && !ctrl && !alt) {
          mIsRolledOver = true;
          OnRollover();
        }
      }
      break;
    case 6:
      if (message.mButton == 1000)
        OnMouseDown();
      break;
    case 7:
      if (message.mButton == 1000) {
        OnMouseUp();
        PlayAudio(0xa03e74b2, GetAudioSystem());
      }
      break;
  }
  return false;
}
}  // namespace SP

// @ 0x005c6f00
namespace SP {
void cSPPaletteItemUI_s005c_6340::OnRollover()
{
  RolloverMessage msg(0x522f9cd);
  msg.SetSource(this);
  MessageServer()->MessageSend(msg.mID, &msg, 0);
}
}  // namespace SP

// @ 0x005c6f40
namespace SP {
void cSPPaletteItemUI_s005c_6340::OffRollover()
{
  RolloverMessage msg(0x522f9ce);
  msg.SetSource(this);
  MessageServer()->MessageSend(msg.mID, &msg, 0);
}
}  // namespace SP

// @ 0x005c6f80
namespace SP {
void cSPPaletteItemUISelectable_s005c_6340::Init(cSPPaletteItem_s005c_6340* item, IWindow_s005c_6340* window, int a, int b, uint32_t selectionGroup)
{
  mSelectionGroup = selectionGroup;
  MessageServer()->AddHandler(this, 0x47a9a20);
  cSPPaletteItemUI_s005c_6340::Init(item, window, a, b);
}
}  // namespace SP

// @ 0x005c6fd0
namespace SP {
void cSPPaletteItemUISelectable_s005c_6340::Shutdown()
{
  MessageServer()->RemoveHandler(this, 0x47a9a20, -9999);
  cSPPaletteItemUI_s005c_6340::Shutdown();
}
}  // namespace SP

// @ 0x005c7010
namespace SP {
cSPPaletteItemRollover_s005c_6340::cSPPaletteItemRollover_s005c_6340()
: mIsRolledOver(false) {}
}  // namespace SP

// @ 0x005c7050
namespace SP {
cSPPaletteItemRollover_s005c_6340::~cSPPaletteItemRollover_s005c_6340()
{}
}  // namespace SP

// @ 0x005c70d0
namespace SP {
void cSPPaletteItemRollover_s005c_6340::OnRollover()
{
  cSPUIPropertyLayout* layout = GetEditorUI()->GetPropertyLayout();
  if (layout && mpWindow) {
    AutoRefCount_s005c_6340<cSPEditorVehicleAbilities> content(
        new ("Editor", 0, 0, 0, 0) cSPEditorVehicleAbilities(mpItem->mItemKey, mpPalette->mModelType,
                                                              0x14880158, 0, true));
    layout->SetItem(mpItem, mpPalette, content, true);
    layout->SetMode(2);
    RectT_s005c_6340 screen = WindowManager()->GetMainWindow()->GetRealArea();
    RectT_s005c_6340 area = mpWindow->GetArea();
    layout->SetPositionAndOffset((area.left + area.right) * 0.5f, (area.top + area.bottom) * 0.5f,
                                 (screen.right - screen.left) * 0.05f, (screen.bottom - screen.top) * 0.0f);
  }
}
}  // namespace SP

// @ 0x005c7260
namespace SP {
bool cSPPaletteItemRollover_s005c_6340::DoMessage(IWindow_s005c_6340* window, const Message_s005c_6340& message)
{
  switch (message.mEventType) {
    case 0x1b:
      if (message.mParam0c == 1 && !mIsRolledOver) {
        bool shift = IsKeyDown(1000);
        bool ctrl = IsKeyDown(0x3ea);
        bool alt = IsKeyDown(0x3e9);
        if (!shift && !ctrl && !alt) {
          mIsRolledOver = true;
          OnRollover();
        }
      }
      break;
    case 0x1c:
      if (message.mParam0c == 1 && mIsRolledOver) {
        if (!IsDescendant(mpWindow.mpObject, WindowManager()->GetCapture(1))) {
          mIsRolledOver = false;
          OffRollover();
        }
      }
      break;
  }
  return false;
}
}  // namespace SP

// @ 0x005c7320
namespace SP {
void cSPPaletteItemRollover_s005c_6340::Shutdown()
{
  if (mpContent) {
    GetEditorUI()->RemoveContent(mpContent);
    mpContent.AsOutParam();
  }
  if (mpWindow)
    mpWindow->RemoveWinProc(this);
}
}  // namespace SP

// @ 0x005c73d0
namespace SP {
void cSPPaletteItemUI_s005c_6340::Trigger()
{
  cPaletteItemMessage msg(0xb2e18705, mInterfaceID);
  cItemTarget* target = GetTarget();
  msg.mpTarget = target ? (EA::COM::IUnknown32_s005c_6340*)target->mInner.Cast(0xee3f516e) : 0;
  MessageServer()->MessageSend(msg.mID, &msg, 0);
}
}  // namespace SP

// @ 0x005c74a0
namespace SP {
cSPPaletteItemUISelectable_s005c_6340::cSPPaletteItemUISelectable_s005c_6340()
: mSelected(false), mSelectionGroup(0) {}
}  // namespace SP

// @ 0x005c7500
namespace SP {
void cSPOLDPaletteItemUI_s005c_7500::Init(cSPPaletteItem_s005c_7500* item, UIWindow* parent, int arg3, cSPSwatch_s005c_7500* swatch)
{
  mData = item;
  mSwatch = swatch;
  bool isHidden = false;
  bool checkResult = true;
  bool hasImage = true;
  bool flagged = false;
  uint32_t type = mData->mItemType;
  if (type == 0x81c74dbc || type == 0x8bfac054 || type == 0xe1e54b3b)
    hasImage = false;
  WinRef<UIWindow> win;
  void* iconId = 0;
  uint32_t iconValue = 0;

  if (hasImage) {
    if (EditorFlag() && item)
      flagged = item->mIndex < 0;
    if (swatch) {
      SwatchInfo* info = ((SwatchView*)swatch)->mInfo;
      if (info) {
        uint64_t k = MakeKey64(item->mItemKey.mGroup, item->mItemKey.mInstance);
        isHidden = !info->Has(k);
        if (!isHidden && !flagged) {
          int r = 1;
          SwatchVerifier* v = ((SwatchView*)swatch)->mVerifier;
          if (v)
            r = v->Query(&item->mItemKey, 0);
          isHidden = r == 7;
        }
      }
    }
    if (item)
      checkResult = item->CheckInfo(((SwatchView*)swatch)->mInfo);

    if (isHidden) {
      ResKey key;
      key.mInstance = 0;
      key.mType = 0;
      key.mGroup = 0;
      if (!checkResult) {
        iconValue = item->GetSwatchColor();
        key = *item->GetCities();
      } else {
        iconValue = item->GetPriority();
        key = *item->GetPlanetKey();
      }
      if (key.mInstance != 0) {
        cSPUILayout layout;
        layout.Init(&key, true, 0x5b598fa);
        win.SetOol(layout.FindWindowByID(0x902d3163, true));
      }
      if (win && key.mInstance != 0) {
        parent->AddChild(win);
        Rect4 r = *win->GetArea();
        r.x1 = r.x1 - r.x0;
        r.y1 = r.y1 - r.y0;
        r.x0 = 0.0f;
        r.y0 = 0.0f;
        CenterWindowInRect(win, &r);
        UIWindow* child = win->FindWindowByID(0x4976e19, false);
        if (child && iconValue) {
          child->SetFlag(0x10, true);
          SetImageIcon(child, GetImageFromLayout(iconValue), 0);
        }
      } else {
        ResKey fallback(0x3cf13a01, 0x2f7d0004, 0x11c0bde);
        win.SetOol(CreateImageWindow(&fallback, 0.0f, 0.0f, parent));
      }
    } else if (EditorFlag() && flagged) {
      ResKey lockedKey(0x43c6e503, 0x2f7d0004, 0x11c0bde);
      win.SetOol(CreateImageWindow(&lockedKey, 0.0f, 0.0f, parent));
    } else {
      win = CreateImageWindow(&mData->mThumbnailKey, 0.0f, 0.0f, parent);
    }
  } else {
    win = CreateWindowFor(parent);
  }

  if (win) {
    win->SetField60(arg3);
    if (isHidden) {
      if (item && item->IsHidden()) {
        win->AddWinProc((char*)this + 8);
        win->SetFlag(0x10, false);
        win->SetFlag(2, true);
      } else {
        win->SetFlag(0x10, true);
        win->SetFlag(2, false);
      }
    } else if (EditorFlag() && flagged) {
      Vec2 pos;
      pos.x = 5.0f;
      pos.y = -15.0f;
      cString_s005c_7500 text(0x496bfb26, 0x538602b, 0);
      cSPUITooltipWinProc* tip = new (4, "UI/Tooltip", GetUIAllocator())
          cSPUITooltipWinProc(L"Tooltips", 0x3754e6c, text.GetText(), &pos, 0, &g_data13f80fc, 0);
      if (tip)
        tip->AddRef();
      win->AddWinProc(tip);
      if (tip)
        tip->Release();
    } else {
      DragAndBuy* obj;
      switch (mData->mItemType) {
        case 0x4d863c8b:
        case 0x0fcafd26:
        case 0x2b885df4:
        case 0xe73759f3:
          if (!swatch)
            goto done;
          obj = GetSwatchManager()->CreateSwatch(new ("Editor", 0, 0, 0, 0) DragAndBuy());
          if (obj)
            obj->AddRef();
          break;
        case 0xa2e50993:
        case 0xc9db779b: {
          if (!swatch)
            goto done;
          DragAndBuyRef r(
              GetSwatchManager()->CreateSwatch(new ("Editor", 0, 0, 0, 0) DragAndBuy()));
          obj = r.mpObject;
          break;
        }
        default:
          goto done;
      }
      obj->Init(&mData->mItemKey, win, parent, 0xb2e18705, mData, swatch, true);
      mDragAndBuy.SetOol(obj);
      if (obj)
        obj->Release();
    }
  }
done:
  mWindow = win;
}
}  // namespace SP
