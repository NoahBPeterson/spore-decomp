// src/game/SPEditors/SPPaletteItemUIPlannerEdit.cpp -- migrated from slice(s) s005ef440, s005ee480 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPaletteItemUIPlannerEdit.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
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
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/Message.h"
#include "SP/cCollectableItems.h"
#include "SP/cICameraManager.h"
#include "SP/cISPCreatureAnimWorld.h"
#include "SP/cPropertyList.h"
#include "SP/cSPPaletteItemRollover.h"
#include "SP/cSPUILargeAssetView.h"
#include "SP/cString.h"
#include "hkBaseObject.h"
#include "hkBool.h"
#include "hkReferencedObject.h"

// ---- items of slice s005ee480 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                     const char* file, int line);                           // 0x00f473a0
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
namespace EA {
namespace UTFWin {
class IWindowManager {
 public:
  PV(0)
  virtual IWindow_s005e_e480* GetMainWindow();  // +0x4
};
}
}
namespace EA {
namespace Messaging {
class IHandler_s005e_e480 {
 public:
  virtual bool HandleMessage(uint32_t messageID, void* message) = 0;
};
}
}
namespace EA {
namespace Messaging {
class IHandlerRC_s005e_e480 : public IHandler_s005e_e480 {
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
  virtual void MessageSend(uint32_t messageID, void* message, IHandler_s005e_e480* handler);  // +0x14
  PV(6) PV(7) PV(8)
  virtual void AddHandler(IHandler_s005e_e480* handler, uint32_t messageID);                  // +0x24
};
}
}
namespace EA {
namespace Messaging {
typedef IMessageServer Server_s005e_e480;
}
}
namespace EA {
namespace Messaging {
void RemoveHandler(Server_s005e_e480* server, IHandler_s005e_e480* handler, const uint32_t* ids, uint32_t count,
                   int priority);  // 0x00571db0
}
}
namespace EA {
namespace Messaging {
class AutoHandler_s005e_e480 {
 public:
  AutoHandler_s005e_e480() : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0), mnPriority(0) {}
  void Init(Server_s005e_e480* pServer, IHandler_s005e_e480* pHandler, const uint32_t* pIdArray, uint32_t nIdArrayCount,
            int nPriority) {
    mpServer = pServer;
    mpHandler = pHandler;
    mpIdArray = pIdArray;
    mnIdArrayCount = nIdArrayCount;
    mnPriority = nPriority;
    if (pServer && pHandler) {
      for (uint32_t i = 0; i < nIdArrayCount; i++)
        pServer->AddHandler(pHandler, pIdArray[i]);
    }
  }
  void Shutdown() {
    if (mpServer) {
      Server_s005e_e480* const pServer = mpServer;
      mpServer = 0;
      RemoveHandler(pServer, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
    }
  }
  Server_s005e_e480* mpServer;             // +0x0
  IHandler_s005e_e480* mpHandler;          // +0x4
  const uint32_t* mpIdArray;    // +0x8
  uint32_t mnIdArrayCount;      // +0xc
  int mnPriority;               // +0x10
};
}
}
using EA::AutoRefCount_s005e_e480;
using EA::ResourceMan::Key_s005e_e480;
using EA::UTFWin::IWindow_s005e_e480;
using EA::UTFWin::IWinProc_s005e_e480;
using EA::UTFWin::Message_s005e_e480;
using EA::RectT_s005e_e480;
class cSPUILayout_s005e_e480 {
 public:
  cSPUILayout_s005e_e480();  // 0x00810000
  virtual ~cSPUILayout_s005e_e480();
  virtual int AddRef();
  virtual int Release();
  bool Init(const Key_s005e_e480& key, bool bVisible, uint32_t parentID);          // 0x008120d0
  void SetParentWin(IWindow_s005e_e480* parent, bool bFit, uint32_t parentID);     // 0x008121b0
  IWindow_s005e_e480* FindWindowByID(uint32_t id, bool recursive);                 // 0x008105b0
  void Shutdown(bool bRemove);                                          // 0x00811ad0
  uint32_t mData[5];
};
class cSPUIPropertyLayout_s005e_e480;
namespace SPUIHelpers {
bool IsWindowVisible(IWindow_s005e_e480* window);                    // 0x008050b0
}
namespace SP {
EA::UTFWin::IWindowManager* WindowManager();      // 0x0067caa0
}
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
class cSPPaletteItemUIPlannerEdit : public cSPPaletteItemUI_s005e_e480, public EA::Messaging::IHandlerRC_s005e_e480 {
 public:
  virtual void Shutdown();
  virtual void* Cast(uint32_t typeID) const;
  virtual void OnRollover();
  void SetLocked(bool locked);

  AutoRefCount_s005e_e480<IWindow_s005e_e480> mWinSwatch;          // +0x24
  AutoRefCount_s005e_e480<IWindow_s005e_e480> mWinRoot2;           // +0x28
  AutoRefCount_s005e_e480<IWindow_s005e_e480> mWinIcon;            // +0x2c
  AutoRefCount_s005e_e480<IWindow_s005e_e480> mWinLockedIcon;      // +0x30
  AutoRefCount_s005e_e480<IWindow_s005e_e480> mWinEditButton;      // +0x34
  AutoRefCount_s005e_e480<cSPUILayout_s005e_e480> mLayout;         // +0x38
  AutoRefCount_s005e_e480<cSPSwatch_s005e_e480> mSwatch;           // +0x3c
  EA::Messaging::AutoHandler_s005e_e480 mAutoMsgHandler;  // +0x40
  Key_s005e_e480 mModelKey;                             // +0x54
  int mWhichEditor;                          // +0x60
  AutoRefCount_s005e_e480<cSPPaletteInfo_s005e_e480> mInfo;        // +0x64
  bool mLocked;                              // +0x68
  uint32_t mID;                              // +0x6c
};
}
// ---- items of slice s005ee480 end

// ---- items of slice s005ef440 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380
#define EASTL_ALLOCATOR_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
namespace EA {
template <typename T>
class AutoRefCount_s005e_f440 {
 public:
  T* mpObject;
  AutoRefCount_s005e_f440() : mpObject(0) {}
  AutoRefCount_s005e_f440(const AutoRefCount_s005e_f440& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005e_f440() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005e_f440& operator=(T* p) {
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
class RefCountTemplate_s005e_f440 {
 public:
  RefCountTemplate_s005e_f440() : mRefCount(0) {}
  virtual ~RefCountTemplate_s005e_f440() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005e_f440 {
 public:
  RefCountVTemplate_s005e_f440() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005e_f440() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005e_f440 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};  // namespace COM
}
}
namespace EA {
namespace ResourceMan {
struct Key_s005e_f440 {
  unsigned int mInstance, mType, mGroup;
  Key_s005e_f440() : mInstance(0), mType(0), mGroup(0) {}
  Key_s005e_f440(unsigned int instance, unsigned int type, unsigned int group)
      : mInstance(instance), mType(type), mGroup(group) {}
};  // namespace ResourceMan
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005e_f440;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005e_f440 : public COM::IUnknown32_s005e_f440 {
 public:
  PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  PV(30)
  virtual void SetFlag(int flag, bool value);       // +0x7c
  virtual void SetCaption(const wchar_t* caption);  // +0x80
};
}
}
namespace EA {
namespace UTFWin {
struct Message_s005e_f440 {
  uint32_t pad0[2];
  uint32_t mEventType;  // +0x8
  uint32_t mControlID;  // +0xc
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005e_f440 : public COM::IUnknown32_s005e_f440 {
 public:
  virtual int GetEventFlags();
  virtual bool DoMessage(IWindow_s005e_f440* window, const Message_s005e_f440& message) = 0;
};
}
}
namespace EA {
namespace Messaging {
class IHandler_s005e_f440 {
 public:
  virtual ~IHandler_s005e_f440() {}
  virtual bool HandleMessage(uint32_t messageID, void* message) = 0;
};
}
}
namespace EA {
namespace Messaging {
class IHandlerRC_s005e_f440 : public IHandler_s005e_f440 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
};
}
}
namespace EA {
namespace Messaging {
class Server_s005e_f440 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void MessageSend(uint32_t messageID, void* message, IHandler_s005e_f440* handler);  // +0x14 0x008853b0
  PV(6) PV(7) PV(8)
  virtual void AddHandler(IHandler_s005e_f440* handler, uint32_t messageID);  // +0x24
};
}
}
namespace EA {
namespace Messaging {
void RemoveHandler(Server_s005e_f440* server, IHandler_s005e_f440* handler, const uint32_t* ids, uint32_t count,
                   int priority);  // 0x00571db0
}
}
namespace EA {
namespace Messaging {
struct AutoHandler_s005e_f440 {
  Server_s005e_f440* mpServer;
  IHandler_s005e_f440* mpHandler;
  const uint32_t* mpIdArray;
  uint32_t mnIdArrayCount;
  int mnPriority;
  AutoHandler_s005e_f440() : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0), mnPriority(0) {}
  ~AutoHandler_s005e_f440() { Clear(); }
  void Clear() {
    if (mpServer) {
      Server_s005e_f440* const pServer = mpServer;
      mpServer = 0;
      RemoveHandler(pServer, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
    }
  }
};
}
}
using EA::AutoRefCount_s005e_f440;
using EA::ResourceMan::Key_s005e_f440;
using EA::UTFWin::IWindow_s005e_f440;
using EA::UTFWin::IWinProc_s005e_f440;
using EA::UTFWin::Message_s005e_f440;
class cSPUILayout_s005e_f440 : public EA::RefCountVTemplate_s005e_f440<int> {
 public:
  cSPUILayout_s005e_f440();                                                                   // 0x00810000
  void Init(const Key_s005e_f440& key, bool visible, uint32_t parentID);                      // 0x008120d0
  void SetParentWin(IWindow_s005e_f440* window, bool visible, uint32_t parentID);             // 0x008121b0
  IWindow_s005e_f440* FindWindowByID(uint32_t id, bool recursive);                            // 0x008105b0
  uint32_t pad[4];
};
namespace SPUIHelpers {
void SetWindowAreaToParent(IWindow_s005e_f440* window);                    // 0x00806bf0
}
namespace SPUIHelpers {
void SetWindowImage(IWindow_s005e_f440* window, const Key_s005e_f440* key, int index);  // 0x00807bb0
}
namespace SP {
namespace Editor {
 enum eEditorConfig_s005e_f440 {}; 
}
}
namespace SP {
class cString_s005e_f440 {
 public:
  cString_s005e_f440();                    // 0x006b5060
  ~cString_s005e_f440();                   // 0x006b5240
  const wchar_t* GetText();     // 0x006b55c0
  uint32_t pad[5];
};
}
namespace SP {
class cPropertyList_s005e_f440 {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
namespace SP {
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList_s005e_f440*& result);  // +0x2c
};
}
namespace SP {
IPropertyManager* PropertyManager();                                           // 0x0067de30
}
namespace SP {
EA::Messaging::Server_s005e_f440* MessageServer();                                        // 0x0067dcc0
}
namespace SP {
bool GetPropertyAsUint32(cPropertyList_s005e_f440* list, uint32_t id, uint32_t* result);  // 0x004af210
}
namespace SP {
bool GetPropertyAsText(cPropertyList_s005e_f440* list, uint32_t id, cString_s005e_f440* result);     // 0x006a1360
}
namespace SP {
bool GetPropertyAsKey(cPropertyList_s005e_f440* list, uint32_t id, Key_s005e_f440* result);          // 0x006a1250
}
namespace SP {
bool GetPropertyAsKeyInstance(cPropertyList_s005e_f440* list, uint32_t id, void* result); // 0x006a12a0
}
namespace SP {
extern bool gbSwatchPlannerMode;  // 0x0151b854
}
namespace SP {
class cSPPaletteItem_s005e_f440 : public EA::RefCountVTemplate_s005e_f440<int>, public EA::COM::IUnknown32_s005e_f440 {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  Key_s005e_f440 mItemKey;       // +0xc
  Key_s005e_f440 mThumbnailKey;  // +0x18
};
}
namespace SP {
class cCollectableItems_s005e_f440 {
 public:
  void Lock(uint64_t id);               // 0x00596e10
  void Unlock(uint64_t id, int flags);  // 0x00596da0
};
}
namespace SP {
uint64_t MakeCollectableID(uint32_t groupID, uint32_t instanceID);  // 0x00593980
}
namespace SP {
struct cSPPaletteInfo_s005e_f440 : public EA::RefCountTemplate_s005e_f440<int> {
  void* mEconomy;                        // +0x8
  void* mTheme;                          // +0xc
  cCollectableItems_s005e_f440* mCollectableItems;  // +0x10
  cCollectableItems_s005e_f440* GetCollectableItems() const { return mCollectableItems; }
};
}
namespace SP {
class cSPSwatch_s005e_f440 : public IWinProc_s005e_f440 {
 public:
  void Init(const Key_s005e_f440& key, IWindow_s005e_f440* window, int a, int b, int c, int d, int e);  // 0x005f4f80
  void SetBackground(uint32_t id);       // 0x005f2270
  void SetShowName(bool show);           // 0x005f2260
  void SetPlannerMode(bool on);          // 0x005f21c0
  void SetImage(uint32_t id, bool on);   // 0x005f2d00
  PV(4) PV(5) PV(6) PV(7)
  virtual void SetModelKey(const Key_s005e_f440* key);  // +0x24 0x005f4080
  PV(10)
  virtual void SetRotatable(bool on);    // +0x2c
  PV(12) PV(13)
  virtual void SetZoomable(bool on);     // +0x38
};
}
namespace SP {
class cSPPaletteItemRollover_s005e_f440 {
 public:
  void Hide();  // 0x005ed6c0
};
}
namespace SP {
class cSPSwatchManager;
}
namespace SP {
cSPSwatchManager* SwatchManager();  // 0x00401020
}
namespace SP {
class cISPPaletteItemUI_s005e_f440 {
 public:
  enum eItemUIInterfaceID { kItemUIUnknown = -1 };
  cISPPaletteItemUI_s005e_f440() : mInterfaceID(kItemUIUnknown) {}
  virtual ~cISPPaletteItemUI_s005e_f440() {}
  virtual void Init(cSPPaletteItem_s005e_f440* item, IWindow_s005e_f440* window, int a, cSPPaletteInfo_s005e_f440* info) = 0;
  virtual void Shutdown() = 0;
  PV(3) PV(4) PV(5) PV(6)
  virtual void OnRollover() = 0;
  virtual void OffRollover() = 0;

  AutoRefCount_s005e_f440<cSPPaletteItem_s005e_f440> mPaletteItem;  // +0x4
  eItemUIInterfaceID mInterfaceID;            // +0x8
};
}
namespace SP {
class cSPPaletteItemUI_s005e_f440 : public cISPPaletteItemUI_s005e_f440, public IWinProc_s005e_f440, public EA::RefCountVTemplate_s005e_f440<int> {
 public:
  cSPPaletteItemUI_s005e_f440();   // 0x005c6bf0
  ~cSPPaletteItemUI_s005e_f440();  // 0x005c6c50
  virtual void Init(cSPPaletteItem_s005e_f440* item, IWindow_s005e_f440* window, int a, cSPPaletteInfo_s005e_f440* info);  // 0x005c6ca0
  virtual void Shutdown();  // 0x005c6d20 (SP::cSPPaletteItemUI::Shutdown)
  virtual void OnRollover();  // 0x005c6f00 (SP::cSPPaletteItemUI::OnRollover)
  virtual void OffRollover();  // 0x005c6f40
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual bool DoMessage(IWindow_s005e_f440* window, const Message_s005e_f440& message);  // 0x005c6d70

  bool mIsRolledOver;               // +0x18
  AutoRefCount_s005e_f440<IWindow_s005e_f440> mWinRoot;   // +0x1c
};
}
namespace SP {
class cPlannerEditMessage : public EA::Messaging::IHandler_s005e_f440, public EA::RefCountVTemplate_s005e_f440<int> {
 public:
  virtual bool HandleMessage(uint32_t, void*);
  Editor::eEditorConfig_s005e_f440 mWhichEditor;  // +0xc
  Key_s005e_f440 mModelKey;                       // +0x10
  uint32_t mSlotID;                    // +0x1c
};
}
namespace SP {
class cSPPaletteItemUIPlannerEdit_s005e_f440 : public cSPPaletteItemUI_s005e_f440, public EA::Messaging::IHandlerRC_s005e_f440 {
 public:
  cSPPaletteItemUIPlannerEdit_s005e_f440();
  ~cSPPaletteItemUIPlannerEdit_s005e_f440();
  virtual void Init(cSPPaletteItem_s005e_f440* item, IWindow_s005e_f440* window, int a, cSPPaletteInfo_s005e_f440* info);  // 0x005ef850 (SP::cSPPaletteItemUIPlannerEdit::Init)
  virtual void OffRollover();
  virtual bool DoMessage(IWindow_s005e_f440* window, const Message_s005e_f440& message);
  virtual bool HandleMessage(uint32_t messageID, void* message);
  virtual int AddRef();
  virtual int Release();
  void SetLocked(bool locked);

  AutoRefCount_s005e_f440<IWindow_s005e_f440> mWinSwatch;          // +0x24
  AutoRefCount_s005e_f440<IWindow_s005e_f440> mWinRoot;            // +0x28
  AutoRefCount_s005e_f440<IWindow_s005e_f440> mWinIcon;            // +0x2c
  AutoRefCount_s005e_f440<IWindow_s005e_f440> mWinLockedIcon;      // +0x30
  AutoRefCount_s005e_f440<IWindow_s005e_f440> mWinEditButton;      // +0x34
  AutoRefCount_s005e_f440<cSPUILayout_s005e_f440> mLayout;         // +0x38
  AutoRefCount_s005e_f440<cSPSwatch_s005e_f440> mSwatch;           // +0x3c
  EA::Messaging::AutoHandler_s005e_f440 mAutoMsgHandler;  // +0x40
  Key_s005e_f440 mModelKey;                             // +0x54
  Editor::eEditorConfig_s005e_f440 mWhichEditor;        // +0x60
  AutoRefCount_s005e_f440<cSPPaletteInfo_s005e_f440> mInfo;        // +0x64
  bool mLocked;                              // +0x68
  uint32_t mID;                              // +0x6c
  uint32_t mSlotID;                          // +0x70
};
}
namespace eastl {
struct rbtree_node_base_s005e_f440 {
  rbtree_node_base_s005e_f440* mpNodeRight;
  rbtree_node_base_s005e_f440* mpNodeLeft;
  rbtree_node_base_s005e_f440* mpNodeParent;
  char mColor;
};  // namespace eastl
}
extern "C++" void RBTreeInsert(eastl::rbtree_node_base_s005e_f440* pNode, eastl::rbtree_node_base_s005e_f440* pNodeParent,
                               eastl::rbtree_node_base_s005e_f440* pNodeAnchor, int insertionSide);  // 0x009216a0
eastl::rbtree_node_base_s005e_f440* RBTreeIncrement(const eastl::rbtree_node_base_s005e_f440* pNode);       // 0x00921580
void RBTreeErase(eastl::rbtree_node_base_s005e_f440* pNode, eastl::rbtree_node_base_s005e_f440* pNodeAnchor);  // 0x00921880
void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                               const char* file, int line);
namespace eastl {
template <typename T1, typename T2>
struct pair_s005e_f440 {
  T1 first;
  T2 second;
};
}
namespace eastl {
template <typename K, typename V>
struct rbtree_node_s005e_f440 : public rbtree_node_base_s005e_f440 {
  pair_s005e_f440<K, V> mValue;
};
}
namespace eastl {
template <typename K, typename V>
struct rbtree_iterator_s005e_f440 {
  rbtree_node_s005e_f440<K, V>* mpNode;
  rbtree_iterator_s005e_f440() : mpNode(0) {}
  explicit rbtree_iterator_s005e_f440(rbtree_node_s005e_f440<K, V>* p) : mpNode(p) {}
  rbtree_iterator_s005e_f440& operator++() {
    mpNode = (rbtree_node_s005e_f440<K, V>*)RBTreeIncrement(mpNode);
    return *this;
  }
  bool operator!=(const rbtree_iterator_s005e_f440& x) const { return mpNode != x.mpNode; }
};
}
namespace eastl {
template <typename K, typename V>
class rbtree_s005e_f440 {
 public:
  typedef rbtree_node_s005e_f440<K, V> node_type;
  typedef rbtree_iterator_s005e_f440<K, V> iterator;
  typedef pair_s005e_f440<K, V> value_type;

  int mCompare;               // +0x0 (empty less<>)
  rbtree_node_base_s005e_f440 mAnchor;   // +0x4
  unsigned int mnSize;        // +0x14
  const char* mAllocator;     // +0x18

  iterator end() { return iterator((node_type*)&mAnchor); }
  iterator find(const K& key);  // out of line (0x00e5c780)

  node_type* DoCreateNode(const value_type& value) {
    node_type* const pNode = (node_type*)EASTL_allocator_allocate(
        sizeof(node_type), "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    ::new (&pNode->mValue) value_type(value);
    return pNode;
  }
  void DoFreeNode(node_type* pNode) {
    pNode->mValue.~value_type();
    EASTL_allocator_deallocate(pNode);
  }
  iterator DoInsertValueImpl(rbtree_node_base_s005e_f440* pNodeParent, const value_type& value, bool bForceToLeft);
  iterator erase(iterator position) {
    const iterator iErase(position);
    --mnSize;
    ++position;
    RBTreeErase(iErase.mpNode, &mAnchor);
    DoFreeNode(iErase.mpNode);
    return position;
  }
  unsigned int erase(const K& key);
};
}
namespace eastl {
template <typename K, typename V>
typename rbtree_s005e_f440<K, V>::iterator rbtree_s005e_f440<K, V>::DoInsertValueImpl(rbtree_node_base_s005e_f440* pNodeParent,
                                                                 const value_type& value,
                                                                 bool bForceToLeft) {
  int side;
  if (bForceToLeft || (pNodeParent == &mAnchor) ||
      (value.first < ((node_type*)pNodeParent)->mValue.first))
    side = 0;
  else
    side = 1;
  node_type* const pNodeNew = DoCreateNode(value);
  RBTreeInsert(pNodeNew, pNodeParent, &mAnchor, side);
  mnSize++;
  return iterator(pNodeNew);
}
}
typedef eastl::rbtree_s005e_f440<unsigned int, AutoRefCount_s005e_f440<SP::cSPSwatch_s005e_f440> > SwatchIDMap;
typedef eastl::rbtree_s005e_f440<AutoRefCount_s005e_f440<SP::cSPSwatch_s005e_f440>, float> SwatchFloatMap;
template SwatchFloatMap::iterator SwatchFloatMap::DoInsertValueImpl(eastl::rbtree_node_base_s005e_f440*, const SwatchFloatMap::value_type&, bool);
template unsigned int SwatchFloatMap::erase(const AutoRefCount_s005e_f440<SP::cSPSwatch_s005e_f440>&);
namespace SP {
class cICameraManager_s005e_f440 {
 public:
  PV(0) PV(1)
  virtual int AddRef();   // +0x8
  virtual int Release();  // +0xc
  virtual void SetName(const char* name);  // +0x10
  PV(5) PV(6) PV(7)
  virtual void RegisterCamera(uint32_t id, void* (*factory)());  // +0x20
  PV(9)
  virtual void Initialize();  // +0x28
};
}
namespace SP {
class cSPPaletteItemRolloverRC {
 public:
  cSPPaletteItemRolloverRC(bool swatch);  // 0x005ed360
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Initialize();  // +0x1c
  uint32_t pad[0x31];
};
}
namespace SP {
class cISPCreatureAnimWorld_s005e_f440 {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Initialize(int renderer, bool a, bool b, int c, int d);  // +0x1c
  PV(8) PV(9) PV(10) PV(11)
  virtual void* LoadCreature(uint32_t a, uint32_t b, const void* p, const void* q, bool c);  // +0x30
  PV(13) PV(14) PV(15)
  virtual void SetCreatureVisible(void* creature, uint32_t b, bool c);  // +0x40
};
}
namespace SP {
class cSPSwatchManager : public EA::RefCountTemplate_s005e_f440<int> {
 public:
  cSPSwatch_s005e_f440* CreateSwatch(int flags);           // 0x005f0ca0
  cSPPaletteItemRollover_s005e_f440* GetSwatchRollover();  // 0x0113ae10
  void Init();
  void* LoadCreature(uint32_t a, uint32_t b);
  SwatchIDMap mIDToSwatchMap;                              // +0x8
  uint32_t pad24[8];                                       // +0x24
  AutoRefCount_s005e_f440<cSPPaletteItemRolloverRC> mSwatchRollover;  // +0x44
  AutoRefCount_s005e_f440<cSPPaletteItemRolloverRC> mModelRollover;   // +0x48
  AutoRefCount_s005e_f440<cISPCreatureAnimWorld_s005e_f440> mpCreatureAnimWorld; // +0x4c
  AutoRefCount_s005e_f440<cICameraManager_s005e_f440> mCameraManager;            // +0x50
};
}
namespace SP {
static const uint32_t kPlannerEditMessages[] = {0x53850baf};  // namespace SP
}
// ---- items of slice s005ef440 end

// @ 0x005ef1b0
namespace SP {
void* cSPPaletteItemUIPlannerEdit::Cast(uint32_t typeID) const
{
  switch ((int)typeID) {
    case (int)0xee3f516e:
      return (IWinProc_s005e_e480*)this;
    case 0x4784b27:
    case (int)0xb4e4f69b:
      return (cSPPaletteItemUIPlannerEdit*)this;
    case 0x2f009dd0:
      return (IWinProc_s005e_e480*)this;
  }
  return 0;
}
}  // namespace SP

// @ 0x005ef1f0
namespace SP {
void cSPPaletteItemUIPlannerEdit::Shutdown()
{
  if (mSwatch) {
    mSwatch->Shutdown();
    GetEditorUI()->RemoveContent(mSwatch);
    mSwatch.AsOutParam();
  }
  mAutoMsgHandler.Shutdown();
}
}  // namespace SP

// @ 0x005ef250
namespace SP {
void cSPPaletteItemUIPlannerEdit::SetLocked(bool locked)
{
  if (mSwatch) {
    mSwatch->SetLocked(locked);
    if (mSwatch->IsLocked() && !SPUIHelpers::IsWindowVisible(mWinSwatch))
      mSwatch->SetShowLock(false);
    else if (!mSwatch->IsLocked() && SPUIHelpers::IsWindowVisible(mWinSwatch))
      mSwatch->SetShowLock(true);
  }
}
}  // namespace SP

// @ 0x005ef2d0
namespace SP {
void cSPPaletteItemUIPlannerEdit::OnRollover()
{
  if (mSwatch) {
    cSPUIPropertyLayout_s005e_e480* layout = GetEditorUI()->GetPropertyLayout();
    if (layout) {
      const uint32_t textID = mLocked ? 0x4ecf388 : 0x4ecf38a;
      AutoRefCount_s005e_e480<cSPEditorVehicleAbilities> content(new ("Editor", 0, 0, 0, 0) cSPEditorVehicleAbilities(
          mPaletteItem->mItemKey, mInfo->mModelType, 0xa592740e, textID, false));
      layout->SetItem(mPaletteItem, mInfo, content, true);
      layout->SetMode(2);
      const RectT_s005e_e480 screen = WindowManager()->GetMainWindow()->GetRealArea();
      layout->SetPositionAndOffset(mSwatch->mX, mSwatch->mY, (screen.right - screen.left) * 0.1875f,
                                   (screen.bottom - screen.top) * 0.0f);
    }
    mSwatch->SetShowLock(true);
    mSwatch->SetHighlight(true);
    mSwatch->PlayEffect(0x5385a40f, true);
  }
  cSPPaletteItemUI_s005e_e480::OnRollover();
}
}  // namespace SP

// @ 0x005ef440
namespace SP {
void cSPPaletteItemUIPlannerEdit_s005e_f440::OffRollover()
{
  if (cSPPaletteItemRollover_s005e_f440* rollover = SwatchManager()->GetSwatchRollover())
    rollover->Hide();
  cSPPaletteItemUI_s005e_f440::OffRollover();
}
}  // namespace SP

// @ 0x005ef470
namespace SP {
void cSPPaletteItemUIPlannerEdit_s005e_f440::SetLocked(bool locked)
{
  if (locked) {
    if (mWinLockedIcon)
      mWinLockedIcon->SetFlag(1, true);
    if (mWinIcon)
      mWinIcon->SetFlag(1, false);
    if (mWinSwatch)
      mWinSwatch->SetFlag(1, false);
    if (mWinEditButton)
      mWinEditButton->SetFlag(1, false);
    if (mInfo && mInfo->mCollectableItems) {
      const uint64_t id = MakeCollectableID(mPaletteItem->mItemKey.mGroup, mPaletteItem->mItemKey.mInstance);
      mInfo->mCollectableItems->Lock(id);
    }
  } else {
    if (mWinLockedIcon)
      mWinLockedIcon->SetFlag(1, false);
    if (mWinIcon)
      mWinIcon->SetFlag(1, true);
    if (mWinSwatch)
      mWinSwatch->SetFlag(1, true);
    if (mWinEditButton)
      mWinEditButton->SetFlag(1, true);
    if (mInfo && mInfo->mCollectableItems) {
      const uint64_t id = MakeCollectableID(mPaletteItem->mItemKey.mGroup, mPaletteItem->mItemKey.mInstance);
      mInfo->mCollectableItems->Unlock(id, 0);
    }
  }
  mLocked = locked;
}
}  // namespace SP

// @ 0x005ef590
namespace SP {
bool cSPPaletteItemUIPlannerEdit_s005e_f440::HandleMessage(uint32_t messageID, void* message)
{
  if (messageID == 0x53850baf && mSwatch) {
    cPlannerEditMessage* msg = (cPlannerEditMessage*)message;
    if (msg->mSlotID == mSlotID) {
      mModelKey = msg->mModelKey;
      SetLocked(mModelKey.mInstance == 0);
      mSwatch->SetModelKey(&mModelKey);
      if (gbSwatchPlannerMode) {
        uint32_t imageID = 0x5d6a7be;
        switch ((int)mID) {
          case 0x372e2c04: imageID = 0x5d6a7cc; break;
          case (int)0xccc35c46: imageID = 0x5d6a7d0; break;
          case (int)0x9ea3031a: imageID = 0x5d6a7be; break;
          case 0x4178b8e8:
          case 0x65672ade: imageID = 0x5da8e76; break;
        }
        mSwatch->SetImage(imageID, true);
      }
    }
  }
  return true;
}
}  // namespace SP

// @ 0x005ef6b0
namespace SP {
cSPPaletteItemUIPlannerEdit_s005e_f440::cSPPaletteItemUIPlannerEdit_s005e_f440()
: mInfo(), mID(0xffffffff), mSlotID(0) {
  mInterfaceID = (eItemUIInterfaceID)0xb4e4f69b;
}
}  // namespace SP

// @ 0x005ef760
namespace SP {
cSPPaletteItemUIPlannerEdit_s005e_f440::~cSPPaletteItemUIPlannerEdit_s005e_f440()
{}
}  // namespace SP

// @ 0x005ef850
namespace SP {
void cSPPaletteItemUIPlannerEdit_s005e_f440::Init(cSPPaletteItem_s005e_f440* item, IWindow_s005e_f440* window, int a, cSPPaletteInfo_s005e_f440* info)
{
  if (!item || !window)
    return;
  mInfo = info;
  mLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout_s005e_f440();
  mLayout->Init(Key_s005e_f440(0x4e39eb54, 0x510a95b, 0x40464100), true, 0x5b598fa);
  mLayout->SetParentWin(window, true, 0x5b598fa);
  mWinRoot = mLayout->FindWindowByID(0xffffffff, true);
  SPUIHelpers::SetWindowAreaToParent(mWinRoot);
  mWinEditButton = mLayout->FindWindowByID(0x5384f7b5, true);
  mWinSwatch = mLayout->FindWindowByID(0x5384f7b6, true);
  if (mWinSwatch) {
    mSwatch = SwatchManager()->CreateSwatch(0);
    if (mSwatch) {
      mSwatch->Init(Key_s005e_f440(0, 0, 0), mWinSwatch, 1, 0, 2, 0, -1);
      mSwatch->SetBackground(0xb0d43c20);
      if (gbSwatchPlannerMode) {
        mSwatch->SetShowName(false);
        mSwatch->SetRotatable(true);
        mSwatch->SetZoomable(true);
        mSwatch->SetPlannerMode(true);
      } else {
        mSwatch->SetRotatable(false);
        mSwatch->SetZoomable(false);
      }
    }
  }
  AutoRefCount_s005e_f440<cPropertyList_s005e_f440> propList;
  if (PropertyManager()->GetPropertyList(item->mItemKey.mInstance, item->mItemKey.mGroup,
                                         propList.AsOutParam())) {
    GetPropertyAsUint32(propList, 0x4294750, &mSlotID);
    cString_s005e_f440 caption;
    IWindow_s005e_f440* captionWin = mLayout->FindWindowByID(0x33854f3f, true);
    if (captionWin && GetPropertyAsText(propList, 0x33854b51, &caption))
      captionWin->SetCaption(caption.GetText());
    Key_s005e_f440 imageKey(0, 0, 0);
    mWinIcon = mLayout->FindWindowByID(0xd38561ca, true);
    if (mWinIcon && GetPropertyAsKey(propList, 0x4294753, &imageKey))
      SPUIHelpers::SetWindowImage(mWinIcon, &imageKey, -1);
    mWinLockedIcon = mLayout->FindWindowByID(0x73878078, true);
    if (mWinLockedIcon && GetPropertyAsKey(propList, 0x4294753, &imageKey))
      SPUIHelpers::SetWindowImage(mWinLockedIcon, &imageKey, -1);
    GetPropertyAsKeyInstance(propList, 0x4b8e99d, &mWhichEditor);
    uint32_t id = 0;
    GetPropertyAsKeyInstance(propList, 0x5338876f, &id);
    if (id)
      mID = id;
  }
  cSPPaletteItemUI_s005e_f440::Init(item, window, a, info);

  EA::Messaging::IHandlerRC_s005e_f440* const handler = this;
  mAutoMsgHandler.mpServer = MessageServer();
  mAutoMsgHandler.mpHandler = handler;
  mAutoMsgHandler.mpIdArray = kPlannerEditMessages;
  mAutoMsgHandler.mnIdArrayCount = 1;
  mAutoMsgHandler.mnPriority = 0;
  if (mAutoMsgHandler.mpServer && handler)
    mAutoMsgHandler.mpServer->AddHandler(handler, 0x53850baf);

  uint32_t buttonID;
  switch ((int)mID) {
    case 0x372e2c04: buttonID = 0x673a8f1; break;
    case (int)0xccc35c46: buttonID = 0x673a8f0; break;
    case 0x4178b8e8:
    case 0x65672ade: buttonID = 0x673a8f2; break;
    default: goto done;
  }
  if (IWindow_s005e_f440* button = mLayout->FindWindowByID(buttonID, true))
    button->SetFlag(1, true);
done:
  SetLocked(true);
}
}  // namespace SP

// @ 0x005efcb0
namespace SP {
bool cSPPaletteItemUIPlannerEdit_s005e_f440::DoMessage(IWindow_s005e_f440* window, const Message_s005e_f440& message)
{
  if (message.mEventType == 0x287259f6 && message.mControlID == 0x5384f7b5 && mSwatch) {
    cPlannerEditMessage msg;
    msg.mModelKey = mModelKey;
    msg.mWhichEditor = mWhichEditor;
    msg.mSlotID = mSlotID;
    MessageServer()->MessageSend(0x53850bae, &msg, 0);
  }
  return cSPPaletteItemUI_s005e_f440::DoMessage(window, message);
}
}  // namespace SP
