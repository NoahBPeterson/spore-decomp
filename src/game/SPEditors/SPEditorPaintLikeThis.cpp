// src/game/SPEditors/SPEditorPaintLikeThis.cpp -- migrated from slice(s) s005c0c00, s005bfb90 by tools/migrate/rewrite.py
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
#include "EA/Messaging/AutoHandler.h"
#include "EA/Messaging/IHandlerRC.h"
#include "EA/UTFWin/Message.h"
#include "EA/Stopwatch.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cISPPaletteItemUI.h"
#include "SP/cPropertyList.h"
#include "SP/cSPPaletteCategory.h"
#include "SP/cSPPaletteInfo.h"
#include "SP/cSPPaletteItem.h"
#include "SP/cSPPaletteItemUI.h"
#include "SP/cSPPaletteItemUIOneClickPaint.h"
#include "SP/cSPPaletteItemUISelectable.h"
#include "SP/cSPUIAssetBrowserCallback.h"
#include "SP/cString.h"
#include "cSPUILayout.h"
#include "cSPUITooltipWinProc.h"

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

// ---- items of slice s005c0c00 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <typename T>
class AutoRefCount_s005c_0c00 {
 public:
  T* mpObject;
  AutoRefCount_s005c_0c00() : mpObject(0) {}
  ~AutoRefCount_s005c_0c00() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005c_0c00& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
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
class RefCountVTemplate_s005c_0c00 {
 public:
  RefCountVTemplate_s005c_0c00() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005c_0c00() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace ResourceMan {
struct Key_s005c_0c00 {
  unsigned int mInstance, mType, mGroup;
  Key_s005c_0c00() {}
  Key_s005c_0c00(unsigned int i, unsigned int t, unsigned int g) : mInstance(i), mType(t), mGroup(g) {}
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005c_0c00;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005c_0c00 {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2)
  virtual void* Cast(uint32_t typeID);                  // +0xc
  PV(4) PV(5) PV(6) PV(7)
  virtual uint32_t GetWindowType();                     // +0x20
  PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);           // +0x7c
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
  PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60) PV(61)
  PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s005c_0c00* proc);              // +0x104
  virtual void RemoveWinProc(IWinProc_s005c_0c00* proc);           // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005c_0c00 {
 public:
  ~IWinProc_s005c_0c00() {}
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4)
  virtual bool HandleUIMessage(IWindow_s005c_0c00* window, const void* message);  // +0x14
};
}
}
namespace EA {
namespace UTFWin {
struct Message_s005c_0c00 {
  IWindow_s005c_0c00* mpSource;  // +0x0
  uint32_t pad4;
  int mType;          // +0x8
};
}
}
namespace EA {
namespace Messaging {
class IHandler_s005c_0c00 {
 public:
  ~IHandler_s005c_0c00() {}
  virtual bool HandleMessage(uint32_t messageID, void* message);
};
}
}
namespace EA {
namespace Messaging {
class IHandlerRC_s005c_0c00 : public IHandler_s005c_0c00 {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
}
namespace EA {
namespace Messaging {
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMSG(uint32_t messageID, void* data, void* source);  // +0x14
  PV(6) PV(7) PV(8)
  virtual void AddHandler(IHandler_s005c_0c00* handler, uint32_t messageID);      // +0x24
};
}
}
namespace EA {
namespace Messaging {
void RemoveHandler(IMessageServer* server, IHandler_s005c_0c00* handler, const uint32_t* ids, unsigned int count, int priority);
}
}
namespace EA {
namespace Messaging {
class AutoHandler_s005c_0c00 {
 public:
  IMessageServer* mpServer;    // +0x0
  IHandler_s005c_0c00* mpHandler;         // +0x4
  const uint32_t* mpIdArray;   // +0x8
  unsigned int mnIdArrayCount; // +0xc
  int mnPriority;              // +0x10
  AutoHandler_s005c_0c00() : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0), mnPriority(0) {}
  ~AutoHandler_s005c_0c00() { RemoveHandlers(); }
  void RemoveHandlers() {
    if (mpServer) {
      IMessageServer* const pServer = mpServer;
      mpServer = 0;
      RemoveHandler(pServer, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
    }
  }
  void AddHandlers(IMessageServer* server, IHandler_s005c_0c00* handler, const uint32_t* ids, unsigned int count, int priority) {
    mpServer = server;
    mpHandler = handler;
    mpIdArray = ids;
    mnIdArrayCount = count;
    mnPriority = priority;
    if (server && handler) {
      for (unsigned int i = 0; i < count; i++)
        server->AddHandler(handler, ids[i]);
    }
  }
};
}
}
using EA::UTFWin::IWindow_s005c_0c00;
using EA::UTFWin::IWinProc_s005c_0c00;
class cSPUILayout_s005c_0c00 {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  cSPUILayout_s005c_0c00();
  IWindow_s005c_0c00* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
  bool Init(const EA::ResourceMan::Key_s005c_0c00& key, bool b, uint32_t id);  // 0x008120d0 (cSPUILayout::Init)
  void SetParentWin(IWindow_s005c_0c00* parent, bool b, uint32_t id);  // 0x008121b0 (cSPUILayout::SetParentWin)
  void Shutdown(bool b);  // 0x00811ad0 (cSPUILayout::Shutdown)
  char pad[0x18 - 4];
};
class cSPUITooltipWinProc_s005c_0c00 : public IWinProc_s005c_0c00 {
 public:
  cSPUITooltipWinProc_s005c_0c00(const wchar_t* name, uint32_t id, const wchar_t* text, float* pos, uint32_t a, const wchar_t* b, uint32_t c);  // 0x00835e30
  void SetText(const wchar_t* text, void* arg, char flag);  // 0x00835ed0 (ret 0xc)
};
struct cDirectPropertyList_s005c_0c00 {
  char pad[0x3c];
  struct Values {
    char pad[0x118];
    int mbGalacticAdventures;
  }* mpValues;
};
extern cDirectPropertyList_s005c_0c00* sAppProperties;
namespace SP {
EA::Messaging::IMessageServer* MessageServer();
}
namespace SP {
class IConfigManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void SetValue(uint32_t id, int value);  // +0x2c
  virtual int GetValue(uint32_t id);              // +0x30
  PV(13) PV(14)
  virtual void Save();                            // +0x3c
};
}
namespace SP {
IConfigManager* ConfigManager();
}
namespace SP {
class cPropertyList_s005c_0c00 {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
namespace SP {
void ShowSporepediaHint(const void* a, const void* b);  // FUN_00809db0
}
namespace SP {
extern char g_SporepediaHintA[];                         // 0x01514bbc
}
namespace SP {
extern char g_SporepediaHintB[];                         // 0x015eb84c
}
namespace SP {
class cSPPaletteItem_s005c_0c00 {
 public:
  cSPPaletteItem_s005c_0c00();  // FUN_005c66a0
  PV(0)
  virtual int AddRef();
  virtual int Release();
  void Init(const EA::ResourceMan::Key_s005c_0c00* key, int a, int b);  // 0x005c6810 (SP::cSPPaletteItem::Init)
  void Shutdown();  // 0x005c6710 (SP::cSPPaletteItem::Shutdown)
  char pad04[4];
  struct Iface {
    PV(0) PV(1) PV(2)
    virtual void* Cast(uint32_t id);  // +0xc
  } mIface;  // +0x8
  char pad0c[0x54 - 0xc];
};
}
namespace SP {
class cSPPaletteInfo_s005c_0c00 {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  char pad04[0x8];
  EA::ResourceMan::Key_s005c_0c00 mKey;  // +0xc
};
}
namespace SP {
class cSPUIAssetBrowserCallback_s005c_0c00 {
 public:
  virtual void OnAssetBrowserSelection(const EA::ResourceMan::Key_s005c_0c00& key);
};
}
namespace SP {
namespace cSPUIAssetBrowser {
void Launch(uint32_t type, cSPUIAssetBrowserCallback_s005c_0c00* callback, uint32_t flags);
}
}
namespace SP {
class cISPPaletteItemUI_s005c_0c00 {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual struct PaletteItemInfo* GetPaletteItem();     // +0x10
  virtual void Release5();                              // +0x14 (name unknown)
  PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual void SetIsSelected(bool selected);            // +0x34
  virtual bool IsLocked();                              // +0x38
  void* mPaletteItem;  // +0x4
  int mInterfaceID;    // +0x8
};
}
namespace SP {
struct PaletteItemInfo {
  char pad[0xc];
  uint32_t mID;  // +0xc
};
}
namespace SP {
class cSPPaletteItemUI_s005c_0c00 : public cISPPaletteItemUI_s005c_0c00, public IWinProc_s005c_0c00, public EA::RefCountVTemplate_s005c_0c00<int> {
 public:
  ~cSPPaletteItemUI_s005c_0c00();  // FUN_005c6c50
  bool HandleUIMessage(IWindow_s005c_0c00* window, const void* message);  // SP::cSPPaletteItemUI::DoMessage (0x005c6d70)
  void OnLeftMouseUp();                                       // FUN_005c6ab0
  bool mIsRolledOver;                  // +0x18
  EA::AutoRefCount_s005c_0c00<IWindow_s005c_0c00> mWinRoot;  // +0x1c
};
}
namespace SP {
class cSPPaletteItemUISelectable_s005c_0c00 : public cSPPaletteItemUI_s005c_0c00, public EA::Messaging::IHandlerRC_s005c_0c00 {
 public:
  ~cSPPaletteItemUISelectable_s005c_0c00() {}
  bool mSelected;                // +0x24
  unsigned int mSelectionGroup;  // +0x28
};
}
namespace SP {
struct Stopwatch { uint64_t mStartTime; uint64_t mTotalTime; uint32_t mUnits; uint32_t mFlags; };
}
namespace SP {
class cSPPaletteItemUIOneClickPaint_s005c_0c00 : public cSPPaletteItemUISelectable_s005c_0c00 {
 public:
  cSPPaletteItemUIOneClickPaint_s005c_0c00();                    // 0x005ee820
  cSPPaletteItemUIOneClickPaint_s005c_0c00(unsigned int group);  // 0x005ee7b0
  ~cSPPaletteItemUIOneClickPaint_s005c_0c00();
  bool HandleMessage(uint32_t messageID, void* message);  // 0x005eefd0
  void Init(cSPPaletteInfo_s005c_0c00* info, IWindow_s005c_0c00* button, int a, void* b);  // 0x005ee880 (SP::cSPPaletteItemUIOneClickPaint::Init)
  void Shutdown();  // 0x005eef80 (SP::cSPPaletteItemUIOneClickPaint::Shutdown)
  void OnSelected();  // 0x005ef030 (SP::cSPPaletteItemUIOneClickPaint::OnSelected)
  void OnRollover();  // 0x005ef0b0 (SP::cSPPaletteItemUIOneClickPaint::OnRollover)
  void OffRollover();  // 0x005ef0f0 (SP::cSPPaletteItemUIOneClickPaint::OffRollover)
  unsigned int mPaintGroupId;                        // +0x2c
  EA::AutoRefCount_s005c_0c00<IWindow_s005c_0c00> mWinThumbnail;           // +0x30
  EA::AutoRefCount_s005c_0c00<IWindow_s005c_0c00> mWinNewItem;             // +0x34
  EA::AutoRefCount_s005c_0c00<cSPUILayout_s005c_0c00> mSelectedLayout;     // +0x38
  EA::AutoRefCount_s005c_0c00<cSPUILayout_s005c_0c00> mRolloverLayout;     // +0x3c
  EA::AutoRefCount_s005c_0c00<IWindow_s005c_0c00> mWinBase;                // +0x40
  EA::Messaging::AutoHandler_s005c_0c00 mAutoHandler;           // +0x44
  bool mLocked;                                      // +0x58
  bool mNewItem;                                     // +0x59
  Stopwatch mUnlockTimer;                            // +0x60
};
}
namespace SP {
struct ModelChosenMessage {
  uint32_t mGroup;       // +0x0
  uint32_t pad04;
  uint32_t mInstance;    // +0x8
  uint32_t pad0c;
  uint32_t mType;        // +0x10
  uint32_t pad14;
  uint32_t mPaintGroup;  // +0x18
  uint32_t pad1c;
  IWindow_s005c_0c00* mpWindow;     // +0x20
  uint32_t pad24[3];
  uint32_t mFlags;       // +0x30
  uint32_t pad34;
};
}
namespace SP {
class cSPEditorPaintLikeThis_s005c_0c00 : public cSPPaletteItemUIOneClickPaint_s005c_0c00, public cSPUIAssetBrowserCallback_s005c_0c00 {
 public:
  EA::AutoRefCount_s005c_0c00<cSPUILayout_s005c_0c00> mLayout;                          // +0x7c
  bool mReadyForMessages;                                         // +0x80
  bool mModelChosen;                                              // +0x81
  unsigned int mModelType;                                        // +0x84
  EA::ResourceMan::Key_s005c_0c00 mModelKey;                                 // +0x88
  EA::ResourceMan::Key_s005c_0c00 mDefaultKey;                               // +0x94
  EA::AutoRefCount_s005c_0c00<cSPPaletteInfo_s005c_0c00> mInfo;                         // +0xa0
  EA::AutoRefCount_s005c_0c00<cPropertyList_s005c_0c00> mPropList;                      // +0xa4
  EA::AutoRefCount_s005c_0c00<cSPPaletteItem_s005c_0c00> mModelToPaintLikePaletteItem;  // +0xa8
  EA::AutoRefCount_s005c_0c00<cSPUITooltipWinProc_s005c_0c00> mTooltip;                 // +0xac
  IWindow_s005c_0c00* mWinThumbnail;                                         // +0xb0
  IWindow_s005c_0c00* mWinRoot;                                              // +0xb4
  IWindow_s005c_0c00* mBtnLoadMain;                                          // +0xb8
  IWindow_s005c_0c00* mBtnLoadTray;                                          // +0xbc
  IWindow_s005c_0c00* mWinRolloverCatcher;                                   // +0xc0
  IWindow_s005c_0c00* mWinBackground;                                        // +0xc4
  IWindow_s005c_0c00* mWinLoadHighlight;                                     // +0xc8
  int mShowingHint;                                               // +0xcc
  EA::Messaging::AutoHandler_s005c_0c00 mAutoHandler;                        // +0xd0

  cSPEditorPaintLikeThis_s005c_0c00(unsigned int paintGroup);
  ~cSPEditorPaintLikeThis_s005c_0c00();
  void SetImage(EA::ResourceMan::Key_s005c_0c00 key);  // 0x005c0ba0 (SP::cSPEditorPaintLikeThis::SetImage)
  void OnPaintThemeSelected(int paletteItemID, uint32_t paintGroupID, IWindow_s005c_0c00* window);  // 0x005c0c00 (SP::cSPEditorPaintLikeThis::OnPaintThemeSelected)
  void OnSelected();  // 0x005c0c60 (SP::cSPEditorPaintLikeThis::OnSelected)
  void OnRollover();  // 0x005c0c80 (SP::cSPEditorPaintLikeThis::OnRollover)
  void OffRollover();  // 0x005c0c90 (SP::cSPEditorPaintLikeThis::OffRollover)
  void OnLeftMouseUp();
  void LaunchSporepedia();  // 0x005c0cd0 (SP::cSPEditorPaintLikeThis::LaunchSporepedia)
  bool HandleUIMessage(IWindow_s005c_0c00* window, const void* message);
  void Shutdown();  // 0x005c1130 (SP::cSPEditorPaintLikeThis::Shutdown)
  void OnAssetBrowserSelection(const EA::ResourceMan::Key_s005c_0c00& key);
  void SendPaletteItemMessage();  // 0x005c13b0 (SP::cSPEditorPaintLikeThis::SendPaletteItemMessage)
  void SendPaintMessage();  // 0x005c14f0 (SP::cSPEditorPaintLikeThis::SendPaintMessage)
  void SetModel(const EA::ResourceMan::Key_s005c_0c00& key);
  bool HandleMessage(uint32_t messageID, void* message);  // 0x005c1340 (SP::cSPEditorPaintLikeThis::HandleMessage)
  void Init(cSPPaletteInfo_s005c_0c00* info, IWindow_s005c_0c00* parent, int a, void* palette);  // 0x005c1960 (SP::cSPEditorPaintLikeThis::Init)
};
}
namespace SP {
class cMessageBase {
 public:
  ~cMessageBase() {}
  virtual void v0();
};
}
namespace SP {
class cPaletteItemMessage : public cMessageBase, public EA::RefCountVTemplate_s005c_0c00<int> {
 public:
  uint32_t mMessageID;                           // +0xc
  int mInterfaceID;                              // +0x10
  uint32_t mField14;                             // +0x14
  uint32_t mField18;                             // +0x18
  uint32_t mField1c;                             // +0x1c
  EA::AutoRefCount_s005c_0c00<IWindow_s005c_0c00> mpObject;            // +0x20
  EA::AutoRefCount_s005c_0c00<IWindow_s005c_0c00> mpWindow;            // +0x24
  cPaletteItemMessage() : mField14(0), mField18(0), mField1c(0) {}
  virtual void v0();
};
}
namespace SP {
extern "C" long __cdecl _InterlockedExchange(volatile long* target, long value);
}
namespace SP {
struct AtomicInt {
  volatile long mValue;
  AtomicInt() { _InterlockedExchange(&mValue, 0); }
};
}
namespace SP {
class BehaviorMessage {
 public:
  BehaviorMessage() {}
  virtual void v0();
  AtomicInt mRefCount;  // +0x4
};
}
namespace SP {
class cPaintMessage : public BehaviorMessage {
 public:
  cPaintMessage() : mMessageID(0), mFlags(0) {}
  ~cPaintMessage();  // SlotMessage::Destruct (0x00421cf0)
  virtual void v0();
  uint32_t mItemID;     // +0x8
  uint32_t pad0c;
  uint32_t mGroup;      // +0x10
  uint32_t pad14;
  IWindow_s005c_0c00* mpWindow;    // +0x18
  uint32_t pad1c[5];
  uint32_t mMessageID;  // +0x30
  uint32_t pad34;
  uint32_t mFlags;      // +0x38
  uint32_t pad3c;
};
}
// ---- items of slice s005c0c00 end

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

// @ 0x005c0c00
namespace SP {
void cSPEditorPaintLikeThis_s005c_0c00::OnPaintThemeSelected(int paletteItemID, uint32_t paintGroupID, IWindow_s005c_0c00* window)
{
  if (paintGroupID != mPaintGroupId && paintGroupID != 0xffffffff) {
    SetIsSelected(false);
    return;
  }
  if (paletteItemID == GetPaletteItem()->mID && window == mWinThumbnail)
    SetIsSelected(true);
  else
    SetIsSelected(false);
}
}  // namespace SP

// @ 0x005c0c60
namespace SP {
void cSPEditorPaintLikeThis_s005c_0c00::OnSelected()
{
  if (mModelChosen)
    cSPPaletteItemUIOneClickPaint_s005c_0c00::OnSelected();
}
}  // namespace SP

// @ 0x005c0c80
void SP::cSPEditorPaintLikeThis::OnRollover()
{
  if (mModelChosen)
    cSPPaletteItemUIOneClickPaint::OnRollover();
}

// @ 0x005c0c90
void SP::cSPEditorPaintLikeThis::OffRollover()
{
  if (mModelChosen)
    cSPPaletteItemUIOneClickPaint::OffRollover();
}

// @ 0x005c0ca0
namespace SP {
void cSPEditorPaintLikeThis_s005c_0c00::OnLeftMouseUp()
{
  if (mModelChosen && !IsLocked())
    cSPPaletteItemUI_s005c_0c00::OnLeftMouseUp();
}
}  // namespace SP

// @ 0x005c0cd0
namespace SP {
void cSPEditorPaintLikeThis_s005c_0c00::LaunchSporepedia()
{
  uint32_t type = sAppProperties->mpValues->mbGalacticAdventures ? 0x1701f8d6 : 0x55cace93;
  cSPUIAssetBrowser::Launch(type, this, 0xad0e52);
}
}  // namespace SP

// @ 0x005c0d20
namespace SP {
bool cSPEditorPaintLikeThis_s005c_0c00::HandleUIMessage(IWindow_s005c_0c00* window, const void* message)
{
  if (window != mWinRolloverCatcher && window != mBtnLoadTray)
    return cSPPaletteItemUI_s005c_0c00::HandleUIMessage(window, message);
  const EA::UTFWin::Message_s005c_0c00* msg = (const EA::UTFWin::Message_s005c_0c00*)message;
  if (msg->mType == 0x287259f6 && msg->mpSource->GetWindowType() == 0x1040) {
    if (sAppProperties->mpValues->mbGalacticAdventures && ConfigManager()->GetValue(0x604a561)) {
      mShowingHint = 1;
      ShowSporepediaHint(g_SporepediaHintA, g_SporepediaHintB);
      return true;
    }
    LaunchSporepedia();
    return true;
  }
  return false;
}
}  // namespace SP

// @ 0x005c0e40
namespace SP {
cSPPaletteItemUIOneClickPaint_s005c_0c00::~cSPPaletteItemUIOneClickPaint_s005c_0c00()
{}
}  // namespace SP

// @ 0x005c0f40
namespace SP {
cSPEditorPaintLikeThis_s005c_0c00::cSPEditorPaintLikeThis_s005c_0c00(unsigned int paintGroup)
: mReadyForMessages(false), mModelChosen(false), mModelType(0), mModelKey(0, 0, 0), mDefaultKey(0, 0, 0),
      mWinThumbnail(0), mBtnLoadMain(0), mBtnLoadTray(0), mWinRolloverCatcher(0) {
  cSPPaletteItemUIOneClickPaint_s005c_0c00((unsigned int)paintGroup);
}
}  // namespace SP

// @ 0x005c1050
namespace SP {
cSPEditorPaintLikeThis_s005c_0c00::~cSPEditorPaintLikeThis_s005c_0c00()
{}
}  // namespace SP

// @ 0x005c1130
namespace SP {
void cSPEditorPaintLikeThis_s005c_0c00::Shutdown()
{
  mReadyForMessages = false;
  mAutoHandler.RemoveHandlers();
  if (mInfo)
    mInfo = 0;
  if (mWinRolloverCatcher)
    mWinRolloverCatcher->RemoveWinProc(this);
  if (mBtnLoadTray) {
    mBtnLoadTray->RemoveWinProc(this);
    if (mTooltip)
      mBtnLoadTray->RemoveWinProc(mTooltip);
  }
  if (mBtnLoadMain)
    mBtnLoadMain->RemoveWinProc(mTooltip);
  if (mLayout) {
    mLayout->Shutdown(true);
    mLayout = 0;
  }
  if (mModelToPaintLikePaletteItem) {
    mModelToPaintLikePaletteItem->Shutdown();
    mModelToPaintLikePaletteItem = 0;
  }
  if (mTooltip)
    mTooltip = 0;
  mPropList = 0;
  cSPPaletteItemUIOneClickPaint_s005c_0c00::Shutdown();
}
}  // namespace SP

// @ 0x005c1340
namespace SP {
void cSPEditorPaintLikeThis_s005c_0c00::OnAssetBrowserSelection(const EA::ResourceMan::Key_s005c_0c00& key)
{
  ModelChosenMessage msg;
  msg.mFlags = 0;
  msg.mGroup = key.mGroup;
  msg.mInstance = key.mInstance;
  msg.mType = key.mType;
  msg.mPaintGroup = mPaintGroupId;
  msg.mpWindow = mWinThumbnail;
  MessageServer()->PostMSG(0x57a4bc9, &msg, 0);
  if (key.mInstance)
    Release5();
}
}  // namespace SP

// @ 0x005c13b0
namespace SP {
void cSPEditorPaintLikeThis_s005c_0c00::SendPaletteItemMessage()
{
  cPaletteItemMessage msg;
  msg.mInterfaceID = mInterfaceID;
  msg.mMessageID = 0xb2e18705;
  if (mModelToPaintLikePaletteItem)
    msg.mpObject = (IWindow_s005c_0c00*)mModelToPaintLikePaletteItem->mIface.Cast(0xee3f516e);
  MessageServer()->PostMSG(msg.mMessageID, &msg, 0);
}
}  // namespace SP

// @ 0x005c14f0
namespace SP {
void cSPEditorPaintLikeThis_s005c_0c00::SendPaintMessage()
{
  cPaintMessage msg;
  msg.mMessageID = 0x5090434;
  msg.mItemID = GetPaletteItem()->mID;
  msg.mGroup = mPaintGroupId;
  msg.mpWindow = mWinThumbnail;
  MessageServer()->PostMSG(msg.mMessageID, &msg, 0);
}
}  // namespace SP
