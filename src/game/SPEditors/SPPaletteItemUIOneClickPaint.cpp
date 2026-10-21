// src/game/SPEditors/SPPaletteItemUIOneClickPaint.cpp -- migrated from slice(s) s005ee480 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPaletteItemUIOneClickPaint.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
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
template <typename T> class Point2DT { public:
  T x, y;
  Point2DT(T ax, T ay) : x(ax), y(ay) {}
  Point2DT(const Point2DT& p) : x(p.x), y(p.y) {}
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
namespace EA {
class Stopwatch_s005e_e480 {
 public:
  enum Units { kUnitsCycles = 0, kUnitsMilliseconds = 4 };
  Stopwatch_s005e_e480(int nUnits = kUnitsCycles, bool bStartImmediately = false);  // 0x0093a560
  void SetUnits(int nUnits);           // 0x0093a1a0
  void Restart();                      // 0x00571e80
  void Stop();                         // 0x0093a2e0
  uint64_t GetElapsedTime() const;     // 0x0093a5e0
  bool IsRunning() const { return (mnStartTime != 0); }
  uint64_t mnStartTime;                // +0x0
  uint64_t mnTotalElapsedTime;         // +0x8
  int mnUnits;                         // +0x10
  float mfStopwatchCyclesToUnitsCoefficient;  // +0x14
};
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
namespace SPUIHelpers {
void SetWindowAreaToParent(IWindow_s005e_e480* window);              // 0x00806bf0
}
namespace SPUIHelpers {
void SetWindowScale(IWindow_s005e_e480* window, float scale);        // 0x00808210
}
namespace SPUIHelpers {
void SetWindowAlpha(IWindow_s005e_e480* window, float alpha);        // 0x00804fc0
}
namespace SPUIHelpers {
RectT_s005e_e480 GetWindowScreenArea(IWindow_s005e_e480* window);               // 0x00805fe0
}
namespace SPUIHelpers {
IWindow_s005e_e480* CreateImageWindow(const Key_s005e_e480& image, EA::Point2DT<float> pos, IWindow_s005e_e480* parent);  // 0x00807880
}
namespace SP {
EA::Messaging::IMessageServer* MessageServer();   // 0x0067dcc0
}
namespace SP {
EA::UTFWin::IWindowManager* WindowManager();      // 0x0067caa0
}
namespace SP {
int GetAudioSystem();                             // 0x00435e90
}
namespace SP {
void PlayAudio(uint32_t id, int system);          // 0x00435ed0
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
class cSPPaletteItemUISelectable_s005e_e480 : public cSPPaletteItemUI_s005e_e480, public EA::Messaging::IHandlerRC_s005e_e480 {
 public:
  cSPPaletteItemUISelectable_s005e_e480();  // 0x005c74a0
  virtual void Init(cSPPaletteItem_s005e_e480* item, IWindow_s005e_e480* window, int a, cSPPaletteInfo_s005e_e480* info,
                    uint32_t selectionGroup);  // 0x005c6f80 (+0x30)
  virtual void SetIsSelected(bool selected);   // +0x34
  virtual bool IsSelected();                   // +0x38
  virtual void OnSelected();                   // +0x3c
  virtual void OnDeselected();                 // +0x40
  virtual void Shutdown();                     // 0x005c6fd0
  virtual bool HandleMessage(uint32_t messageID, void* message);  // 0x005c6b10
  virtual int AddRef();
  virtual int Release();

  bool mSelected;             // +0x24
  uint32_t mSelectionGroup;   // +0x28
};
}
namespace SP {
struct MessageData {
  MessageData() : mID(0) {}
  long mRefCount;     // +0x4
  uint32_t mData[10];
  uint32_t mID;       // +0x30
  uint32_t mPad34;
};
}
namespace SP {
struct BehaviorMessage : public MessageData {
  BehaviorMessage() { _InterlockedExchange(&mRefCount, 0); }
  virtual ~BehaviorMessage();  // 0x00421cf0
};
}
namespace SP {
struct cPaintThemeMessage : public BehaviorMessage {
  cPaintThemeMessage(uint32_t id) : mField38(0) { mID = id; }
  uint32_t mField38;  // +0x38
  uint32_t mPad3c;
};
}
namespace SP {
class cSPPaletteItemUIOneClickPaint_s005e_e480 : public cSPPaletteItemUISelectable_s005e_e480 {
 public:
  cSPPaletteItemUIOneClickPaint_s005e_e480(uint32_t paintGroupId);
  cSPPaletteItemUIOneClickPaint_s005e_e480();
  virtual void Init(cSPPaletteItem_s005e_e480* item, IWindow_s005e_e480* window, int a, cSPPaletteInfo_s005e_e480* info);  // 0x005ee880 (SP::cSPPaletteItemUIOneClickPaint::Init)
  virtual void Shutdown();  // 0x005eef80 (SP::cSPPaletteItemUIOneClickPaint::Shutdown)
  virtual void Trigger();  // 0x005ee740 (SP::cSPPaletteItemUIOneClickPaint::Trigger)
  virtual void Update(float dt);
  virtual void OnRollover();  // 0x005ef0b0 (SP::cSPPaletteItemUIOneClickPaint::OnRollover)
  virtual void OffRollover();  // 0x005ef0f0 (SP::cSPPaletteItemUIOneClickPaint::OffRollover)
  virtual void SetIsSelected(bool selected);  // 0x005ee710 (SP::cSPPaletteItemUIOneClickPaint::SetIsSelected)
  virtual void OnSelected();  // 0x005ef030 (SP::cSPPaletteItemUIOneClickPaint::OnSelected)
  virtual void OnDeselected();  // 0x005ef080 (SP::cSPPaletteItemUIOneClickPaint::OnDeselected)
  virtual void OnPaintThemeSelected(uint32_t paintID, uint32_t groupID, int unused);  // +0x44 0x005ee760
  virtual void SendPaintMessage();                                                    // +0x48 0x005ef130
  virtual void SendTriggerMessage();                                                  // +0x4c
  virtual bool HandleMessage(uint32_t messageID, void* message);  // 0x005eefd0 (SP::cSPPaletteItemUIOneClickPaint::HandleMessage)

  uint32_t mPaintGroupId;                       // +0x2c
  AutoRefCount_s005e_e480<IWindow_s005e_e480> mWinThumbnail;          // +0x30
  AutoRefCount_s005e_e480<IWindow_s005e_e480> mWinNewItem;            // +0x34
  AutoRefCount_s005e_e480<cSPUILayout_s005e_e480> mSelectedLayout;    // +0x38
  AutoRefCount_s005e_e480<cSPUILayout_s005e_e480> mRolloverLayout;    // +0x3c
  AutoRefCount_s005e_e480<IWindow_s005e_e480> mWinBase;               // +0x40
  EA::Messaging::AutoHandler_s005e_e480 mAutoHandler;      // +0x44
  bool mLocked;                                 // +0x58
  bool mNewItem;                                // +0x59
  EA::Stopwatch_s005e_e480 mUnlockTimer;                   // +0x60
};
}
namespace SP {
static const uint32_t kOneClickPaintMessages[2] = {0x5090434, 0x578dedb};  // 0x013f9984
}
namespace SP {
struct PaintMessageData {
  uint32_t pad[2];
  uint32_t mPaintID;  // +0x8
  uint32_t pad0c;
  uint32_t mGroupID;  // +0x10
  uint32_t pad14;
  int mField18;       // +0x18
};
}
// ---- items of slice s005ee480 end

// @ 0x005ee710
namespace SP {
void cSPPaletteItemUIOneClickPaint_s005e_e480::SetIsSelected(bool selected)
{
  if (selected != mSelected) {
    mSelected = selected;
    if (selected)
      OnSelected();
    else
      OnDeselected();
  }
}
}  // namespace SP

// @ 0x005ee740
namespace SP {
void cSPPaletteItemUIOneClickPaint_s005e_e480::Trigger()
{
  SendTriggerMessage();
  SendPaintMessage();
}
}  // namespace SP

// @ 0x005ee760
namespace SP {
void cSPPaletteItemUIOneClickPaint_s005e_e480::OnPaintThemeSelected(uint32_t paintID, uint32_t groupID, int)
{
  if (groupID == mPaintGroupId || groupID == 0xffffffff) {
    if (paintID == GetPaletteItem()->mItemKey.mInstance)
      SetIsSelected(true);
    else
      SetIsSelected(false);
  } else if (mPaintGroupId == 0xffffffff)
    SetIsSelected(false);
}
}  // namespace SP

// @ 0x005ee7b0
namespace SP {
cSPPaletteItemUIOneClickPaint_s005e_e480::cSPPaletteItemUIOneClickPaint_s005e_e480(uint32_t paintGroupId)
: mPaintGroupId(paintGroupId), mLocked(false), mNewItem(false), mUnlockTimer(0, false) {
  mInterfaceID = 0xeccc3657;
}
}  // namespace SP

// @ 0x005ee820
namespace SP {
cSPPaletteItemUIOneClickPaint_s005e_e480::cSPPaletteItemUIOneClickPaint_s005e_e480()
: mPaintGroupId(0xffffffff), mUnlockTimer(0, false) {
  mInterfaceID = 0xeccc3657;
}
}  // namespace SP

// @ 0x005ee880
namespace SP {
void cSPPaletteItemUIOneClickPaint_s005e_e480::Init(cSPPaletteItem_s005e_e480* item, IWindow_s005e_e480* window, int a, cSPPaletteInfo_s005e_e480* info)
{
  mNewItem = false;
  mLocked = false;
  mWinNewItem.AsOutParam();
  if (item && window) {
    mSelectedLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout_s005e_e480();
    mSelectedLayout->Init(Key_s005e_e480(0xd71d1992, 0x510a95b, 0x40464100), true, 0x5b598fa);
    mRolloverLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout_s005e_e480();
    mRolloverLayout->Init(Key_s005e_e480(0xdd1d231a, 0x510a95b, 0x40464100), true, 0x5b598fa);
    mWinBase = window;
    IWindow_s005e_e480* const pThumbnail = window->FindWindowByID(0x5cb2c81, true);
    mSelectedLayout->SetParentWin(mWinBase, true, 0x5b598fa);
    IWindow_s005e_e480* pWindow = mSelectedLayout->FindWindowByID(0x5caddd5, true);
    if (pWindow) {
      SPUIHelpers::SetWindowAreaToParent(pWindow);
      SPUIHelpers::SetWindowScale(pWindow, 0.8f);
      mWinBase->AddWindow(pWindow);
      if (pThumbnail) mWinBase->AddWindow(pThumbnail);
      pWindow->SetFlag(1, false);
    }
    mWinThumbnail = window->FindWindowByID(0x5cab74a, true);
    if (!mWinThumbnail) {
      mWinThumbnail = SPUIHelpers::CreateImageWindow(item->mThumbnailKey, EA::Point2DT<float>(0.0f, 0.0f), window);
      if (mWinThumbnail) {
        SPUIHelpers::SetWindowAreaToParent(mWinThumbnail);
        mWinThumbnail->SetFlag(2, false);
        mWinThumbnail->SetFlag(0x10, true);
      }
    }
    if (info && item->IsNew(info->mCollectableItems)) {
      mWinNewItem = SPUIHelpers::CreateImageWindow(Key_s005e_e480(0x1249ff0f, 0x2f7d0004, 0x100d976e),
                                                   EA::Point2DT<float>(0.0f, 0.0f), window->GetParent());
      if (mWinNewItem) {
        RectT_s005e_e480 area = mWinBase->GetRealArea();
        mWinNewItem->SetArea(area);
        SPUIHelpers::SetWindowAlpha(mWinNewItem, 0.0f);
        mWinNewItem->SetFlag(2, false);
        mWinNewItem->SetFlag(0x10, true);
        mWinNewItem->SetLayer(-1);
        mUnlockTimer.SetUnits(EA::Stopwatch_s005e_e480::kUnitsMilliseconds);
        mNewItem = true;
      }
      window->GetParent()->AddWindow(mWinNewItem);
    }
    mRolloverLayout->SetParentWin(mWinThumbnail, true, 0x5b598fa);
    pWindow = mRolloverLayout->FindWindowByID(0x5caddd5, true);
    if (pWindow) {
      SPUIHelpers::SetWindowAreaToParent(pWindow);
      SPUIHelpers::SetWindowScale(pWindow, 0.8f);
      pWindow->SetFlag(1, false);
    }
    cSPPaletteItemUISelectable_s005e_e480::Init(item, window, a, info, mPaintGroupId);
    mAutoHandler.Init(MessageServer(), this, kOneClickPaintMessages, 2, 0);
  }
}
}  // namespace SP

// @ 0x005eece0
namespace SP {
void cSPPaletteItemUIOneClickPaint_s005e_e480::Update(float)
{
  if (mWinNewItem) {
    if (!mUnlockTimer.IsRunning() && mLocked) {
      SPUIHelpers::SetWindowAlpha(mWinNewItem, 0.0f);
      const RectT_s005e_e480 area = SPUIHelpers::GetWindowScreenArea(mWinBase);
      const RectT_s005e_e480 screen = WindowManager()->GetMainWindow()->GetRealArea();
      if ((area.left + area.right) * 0.5f < (screen.right - screen.left)) {
        if (mWinBase->GetParent()->GetParent()->GetParent()->GetFlags() & 1) {
          if ((area.bottom - area.top) > 2.0f) {
            mUnlockTimer.Restart();
            PlayAudio(0xfd91ff9d, GetAudioSystem());
          }
        }
      }
    }
    if (mUnlockTimer.IsRunning()) {
      float t = (float)mUnlockTimer.GetElapsedTime() * 0.0005f;
      if (t < 0.5f) {
        t = t * 2.0f;
        SPUIHelpers::SetWindowAlpha(mWinBase, 0.0f);
        SPUIHelpers::SetWindowAlpha(mWinNewItem, t);
        SPUIHelpers::SetWindowScale(mWinNewItem, t * t * (1.2f - 0.25f) + 0.25f);
      } else if (t < 1.0f) {
        t = (t - 0.5f) * 2.0f;
        SPUIHelpers::SetWindowAlpha(mWinBase, t);
        SPUIHelpers::SetWindowAlpha(mWinNewItem, (1.0f - t) * (1.0f - 0.65f) + 0.65f);
        SPUIHelpers::SetWindowScale(mWinNewItem, (1.0f - t * t) * (1.2f - 0.9f) + 0.9f);
      } else {
        mLocked = false;
        SPUIHelpers::SetWindowAlpha(mWinBase, 1.0f);
        SPUIHelpers::SetWindowAlpha(mWinNewItem, 0.65f);
        SPUIHelpers::SetWindowScale(mWinNewItem, 0.9f);
        mUnlockTimer.Stop();
      }
    }
  }
}
}  // namespace SP

// @ 0x005eef80
namespace SP {
void cSPPaletteItemUIOneClickPaint_s005e_e480::Shutdown()
{
  mAutoHandler.Shutdown();
  if (mSelectedLayout) mSelectedLayout->Shutdown(true);
  if (mRolloverLayout) mRolloverLayout->Shutdown(true);
  cSPPaletteItemUISelectable_s005e_e480::Shutdown();
}
}  // namespace SP

// @ 0x005eefd0
namespace SP {
bool cSPPaletteItemUIOneClickPaint_s005e_e480::HandleMessage(uint32_t messageID, void* message)
{
  if (messageID == 0x5090434) {
    const PaintMessageData* pData = (const PaintMessageData*)message;
    OnPaintThemeSelected(pData->mPaintID, pData->mGroupID, pData->mField18);
    return false;
  }
  if (messageID == 0x578dedb) {
    if (mNewItem) mLocked = true;
    return false;
  }
  if (messageID == 0x47a9a20) return false;
  return cSPPaletteItemUISelectable_s005e_e480::HandleMessage(messageID, message);
}
}  // namespace SP

// @ 0x005ef030
namespace SP {
void cSPPaletteItemUIOneClickPaint_s005e_e480::OnSelected()
{
  if (mSelectedLayout && mRolloverLayout) {
    IWindow_s005e_e480* pWindow = mSelectedLayout->FindWindowByID(0x5caddd5, true);
    if (pWindow) pWindow->SetFlag(1, true);
    pWindow = mRolloverLayout->FindWindowByID(0x5caddd5, true);
    if (pWindow) pWindow->SetFlag(1, false);
  }
}
}  // namespace SP

// @ 0x005ef080
namespace SP {
void cSPPaletteItemUIOneClickPaint_s005e_e480::OnDeselected()
{
  if (mSelectedLayout) {
    IWindow_s005e_e480* pWindow = mSelectedLayout->FindWindowByID(0x5caddd5, true);
    if (pWindow) pWindow->SetFlag(1, false);
  }
}
}  // namespace SP

// @ 0x005ef0b0
namespace SP {
void cSPPaletteItemUIOneClickPaint_s005e_e480::OnRollover()
{
  if (mRolloverLayout && !IsSelected()) {
    IWindow_s005e_e480* pWindow = mRolloverLayout->FindWindowByID(0x5caddd5, true);
    if (pWindow) pWindow->SetFlag(1, true);
  }
  cSPPaletteItemUI_s005e_e480::OnRollover();
}
}  // namespace SP

// @ 0x005ef0f0
namespace SP {
void cSPPaletteItemUIOneClickPaint_s005e_e480::OffRollover()
{
  if (mRolloverLayout && !IsSelected()) {
    IWindow_s005e_e480* pWindow = mRolloverLayout->FindWindowByID(0x5caddd5, true);
    if (pWindow) pWindow->SetFlag(1, false);
  }
  cSPPaletteItemUI_s005e_e480::OffRollover();
}
}  // namespace SP

// @ 0x005ef130
namespace SP {
void cSPPaletteItemUIOneClickPaint_s005e_e480::SendPaintMessage()
{
  cPaintThemeMessage msg(0x5090434);
  PaintMessageData* pData = (PaintMessageData*)&msg;
  pData->mPaintID = GetPaletteItem()->mItemKey.mInstance;
  pData->mGroupID = mPaintGroupId;
  pData->mField18 = 0;
  MessageServer()->MessageSend(msg.mID, &msg, 0);
}
}  // namespace SP
