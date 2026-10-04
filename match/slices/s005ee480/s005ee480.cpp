// slice s005ee480 -- SP::cSPPaletteItemUIDrag, SP::cSPPaletteItemUIOneClickPaint and
// SP::cSPPaletteItemUIPlannerEdit members, plus cSPUIPropertyLayout::SetItem.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include <intrin.h>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);                       // 0x00f47380
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                     const char* file, int line);                           // 0x00f473a0

#define PV(n) virtual void pv##n();

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  AutoRefCount& operator=(T* p) {
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

template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};

namespace COM {
class IUnknown32 {
 public:
  ~IUnknown32() {}
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};
}  // namespace COM

namespace ResourceMan {
struct Key {
  unsigned int mInstance, mType, mGroup;
  Key() {}
  Key(unsigned int instance, unsigned int type, unsigned int group) {
    mType = type;
    mGroup = group;
    mInstance = instance;
  }
};
}  // namespace ResourceMan

struct RectT {
  float left, top, right, bottom;
  RectT() {}
  RectT(const RectT& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
};
template <typename T> struct Point2DT {
  T x, y;
  Point2DT(T ax, T ay) : x(ax), y(ay) {}
  Point2DT(const Point2DT& p) : x(p.x), y(p.y) {}
};

namespace UTFWin {
class IWinProc;
class IWindow : public COM::IUnknown32 {
 public:
  PV(3)
  virtual IWindow* GetParent();                    // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual uint32_t GetFlags();                     // +0x28
  PV(11) PV(12)
  virtual const RectT& GetRealArea();              // +0x34
  virtual const RectT& GetArea();                  // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
  virtual void SetLayer(int layer);                // +0x5c
  virtual void SetArea(const RectT& area);         // +0x60
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);      // +0x7c
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
  virtual void SetShadeColor(uint32_t color);      // +0xac
  PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57)
  PV(58)
  virtual void AddWindow(IWindow* child);          // +0xec
  virtual IWindow* FindWindowByID(uint32_t id, bool recursive);  // +0xf0
  PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc* proc);         // +0x104
  virtual void RemoveWinProc(IWinProc* proc);      // +0x108
};

struct Message {
  uint32_t pad0[2];
  int mEventType;
  int mParam0c;
};

class IWinProc : public COM::IUnknown32 {
 public:
  virtual int GetEventFlags();
  virtual bool DoMessage(IWindow* window, const Message& message) = 0;
};

class IWindowManager {
 public:
  PV(0)
  virtual IWindow* GetMainWindow();  // +0x4
};
}  // namespace UTFWin

namespace Messaging {
class IHandler {
 public:
  virtual bool HandleMessage(uint32_t messageID, void* message) = 0;
};
class IHandlerRC : public IHandler {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
};
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void MessageSend(uint32_t messageID, void* message, IHandler* handler);  // +0x14
  PV(6) PV(7) PV(8)
  virtual void AddHandler(IHandler* handler, uint32_t messageID);                  // +0x24
};
typedef IMessageServer Server;
void RemoveHandler(Server* server, IHandler* handler, const uint32_t* ids, uint32_t count,
                   int priority);  // 0x00571db0

class AutoHandler {
 public:
  AutoHandler() : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0), mnPriority(0) {}
  void Init(Server* pServer, IHandler* pHandler, const uint32_t* pIdArray, uint32_t nIdArrayCount,
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
      Server* const pServer = mpServer;
      mpServer = 0;
      RemoveHandler(pServer, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
    }
  }
  Server* mpServer;             // +0x0
  IHandler* mpHandler;          // +0x4
  const uint32_t* mpIdArray;    // +0x8
  uint32_t mnIdArrayCount;      // +0xc
  int mnPriority;               // +0x10
};
}  // namespace Messaging

class Stopwatch {
 public:
  enum Units { kUnitsCycles = 0, kUnitsMilliseconds = 4 };
  Stopwatch(int nUnits = kUnitsCycles, bool bStartImmediately = false);  // 0x0093a560
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
}  // namespace EA

using EA::AutoRefCount;
using EA::ResourceMan::Key;
using EA::UTFWin::IWindow;
using EA::UTFWin::IWinProc;
using EA::UTFWin::Message;
using EA::RectT;

class cSPUILayout {
 public:
  cSPUILayout();  // 0x00810000
  virtual ~cSPUILayout();
  virtual int AddRef();
  virtual int Release();
  bool Init(const Key& key, bool bVisible, uint32_t parentID);          // 0x008120d0
  void SetParentWin(IWindow* parent, bool bFit, uint32_t parentID);     // 0x008121b0
  IWindow* FindWindowByID(uint32_t id, bool recursive);                 // 0x008105b0
  void Shutdown(bool bRemove);                                          // 0x00811ad0
  uint32_t mData[5];
};

class cSPUIPropertyLayout;
namespace SPUIHelpers {
void SetWindowAreaToParent(IWindow* window);              // 0x00806bf0
void SetWindowScale(IWindow* window, float scale);        // 0x00808210
void SetWindowAlpha(IWindow* window, float alpha);        // 0x00804fc0
bool IsWindowVisible(IWindow* window);                    // 0x008050b0
RectT GetWindowScreenArea(IWindow* window);               // 0x00805fe0
IWindow* CreateImageWindow(const Key& image, EA::Point2DT<float> pos, IWindow* parent);  // 0x00807880
}

namespace SP {
EA::Messaging::IMessageServer* MessageServer();   // 0x0067dcc0
EA::UTFWin::IWindowManager* WindowManager();      // 0x0067caa0
int GetAudioSystem();                             // 0x00435e90
void PlayAudio(uint32_t id, int system);          // 0x00435ed0

class cSPEditorEconomy;
class cCollectableItems;
struct cSPPaletteInfo {
  virtual ~cSPPaletteInfo();
  virtual int AddRef();
  virtual int Release();
  int mRefCount;                            // +0x4
  cSPEditorEconomy* mEconomy;               // +0x8
  uint32_t mPad0c;
  cCollectableItems* mCollectableItems;     // +0x10
  uint32_t mPad14;
  wchar_t mCurrencyChar;                    // +0x18
  uint32_t mPad1c[4];
  uint32_t mModelType;                      // +0x2c
};

class cSPPaletteItem : public EA::RefCountVTemplate<int>, public EA::COM::IUnknown32 {
 public:
  virtual int AddRef();
  virtual int Release();
  bool IsUnlocked(cCollectableItems* items);   // 0x005c6630
  bool IsNew(cCollectableItems* items);        // 0x005c6670
  Key mItemKey;          // +0xc
  Key mThumbnailKey;     // +0x18
};

class cSPEditorVehicleAbilities {
 public:
  cSPEditorVehicleAbilities(Key key, uint32_t modelType, uint32_t layoutID, uint32_t textID, bool b);  // 0x0059f030
  virtual ~cSPEditorVehicleAbilities();
  virtual int AddRef();
  virtual int Release();
  uint32_t mData[24];
};

class cSPSwatch : public IWinProc {
 public:
  PV(5) PV(6)
  virtual void Shutdown();              // +0x1c
  virtual void SetLocked(bool locked);  // +0x20
  PV(9) PV(10)
  virtual void SetShowLock(bool show);  // +0x2c
  virtual bool IsLocked();              // +0x30
  PV(13)
  virtual void SetHighlight(bool on);   // +0x38
  bool Init(const Key* key, IWindow* window, bool a, int b, bool c, int d, int e);  // 0x005f4f80
  void PlayEffect(uint32_t id, bool b);  // 0x005f2d00
  char pad[0x80];
  float mX;   // +0x84
  float mY;   // +0x88
};

class cEditorUI {
 public:
  cSPSwatch* CreateSwatch(int type);            // 0x005f0ca0
  void RemoveContent(cSPSwatch* content);       // 0x005f0a60
  ::cSPUIPropertyLayout* GetPropertyLayout();  // 0x0113ae10
};
cEditorUI* GetEditorUI();  // 0x00401020
}  // namespace SP

class cSPUIPropertyLayout {
 public:
  void SetItem(SP::cSPPaletteItem* item, SP::cSPPaletteInfo* info, SP::cSPEditorVehicleAbilities* content,
               bool show);
  void SetContents(const Key* key, SP::cSPEditorVehicleAbilities* content, SP::cSPEditorEconomy* economy,
                   wchar_t currency, bool unlocked, bool show);    // 0x005ed750
  void SetMode(int mode);                                           // 0x005ed320
  void SetPositionAndOffset(float x, float y, float dx, float dy);  // 0x008283a0
  char pad[0xb0];
  AutoRefCount<SP::cSPPaletteInfo> mpPaletteInfo;  // +0xb0
};

// @ 0x005ee480
void cSPUIPropertyLayout::SetItem(SP::cSPPaletteItem* item, SP::cSPPaletteInfo* info,
                                  SP::cSPEditorVehicleAbilities* content, bool show) {
  if (item && info) {
    mpPaletteInfo = info;
    SP::cSPPaletteInfo* const pInfo = mpPaletteInfo;
    SP::cCollectableItems* const pItems = pInfo->mCollectableItems;
    SP::cSPEditorEconomy* const pEconomy = pInfo->mEconomy;
    SetContents(&item->mItemKey, content, pEconomy, pInfo->mCurrencyChar, item->IsUnlocked(pItems), show);
  }
}

namespace SP {
class cISPPaletteItemUI {
 public:
  cISPPaletteItemUI() : mInterfaceID(-1) {}
  virtual ~cISPPaletteItemUI() {}
  virtual void Init(cSPPaletteItem* item, IWindow* window, int a, cSPPaletteInfo* info) = 0;  // +0x4
  virtual void Shutdown() = 0;                    // +0x8
  PV(3)
  virtual cSPPaletteItem* GetPaletteItem();       // +0x10
  virtual void Trigger();                         // +0x14
  virtual void Update(float dt);                  // +0x18
  virtual void OnRollover() = 0;                  // +0x1c
  virtual void OffRollover() = 0;                 // +0x20
  virtual void OnMouseDown();                     // +0x24
  virtual void OnMouseUp();                       // +0x28
  PV(11)

  AutoRefCount<cSPPaletteItem> mPaletteItem;  // +0x4
  int mInterfaceID;                           // +0x8
};

class cSPPaletteItemUI : public cISPPaletteItemUI, public IWinProc, public EA::RefCountVTemplate<int> {
 public:
  cSPPaletteItemUI();   // 0x005c6bf0
  ~cSPPaletteItemUI();  // 0x005c6c50
  virtual void Init(cSPPaletteItem* item, IWindow* window, int a, cSPPaletteInfo* info);  // 0x005c6ca0
  virtual void Shutdown();     // 0x005c6d20
  virtual void OnRollover();   // 0x005c6f00
  virtual void OffRollover();  // 0x005c6f40
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual bool DoMessage(IWindow* window, const Message& message);

  bool mIsRolledOver;               // +0x18
  AutoRefCount<IWindow> mWinRoot;   // +0x1c
};

class cSPPaletteItemUISelectable : public cSPPaletteItemUI, public EA::Messaging::IHandlerRC {
 public:
  cSPPaletteItemUISelectable();  // 0x005c74a0
  virtual void Init(cSPPaletteItem* item, IWindow* window, int a, cSPPaletteInfo* info,
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

// ---------------------------------------------------------------------------------------------
class cSPPaletteItemUIDrag : public cSPPaletteItemUI {
 public:
  cSPPaletteItemUIDrag();
  virtual ~cSPPaletteItemUIDrag() {}
  virtual void Init(cSPPaletteItem* item, IWindow* window, int a, cSPPaletteInfo* info);
  virtual void Shutdown();
  virtual void* Cast(uint32_t typeID) const;
  virtual void OnSelected();    // +0x30
  virtual void OnDeselected();  // +0x34

  AutoRefCount<cSPSwatch> mSwatch;  // +0x20
};

// @ 0x005ee500
void* cSPPaletteItemUIDrag::Cast(uint32_t typeID) const {
  switch ((int)typeID) {
    case 0x4784b27:
      return (cSPPaletteItemUIDrag*)this;
    case (int)0xee3f516e:
    case 0x2f009dd0:
      return (IWinProc*)this;
    case 0x71fa7d3f:
      return (cSPPaletteItemUIDrag*)this;
  }
  return 0;
}


// @ 0x005ee540
cSPPaletteItemUIDrag::cSPPaletteItemUIDrag() {
  mInterfaceID = 0x71fa7d3f;
}

// @ 0x005ee590  cSPPaletteItemUIDrag scalar deleting dtor (compiler-generated ??_G from ~cSPPaletteItemUIDrag)

// @ 0x005ee5e0
void cSPPaletteItemUIDrag::Init(cSPPaletteItem* item, IWindow* window, int a, cSPPaletteInfo* info) {
  if (item && window) {
    mSwatch = GetEditorUI()->CreateSwatch(0);
    mSwatch->Init(&item->mItemKey, window, true, 0, true, 0, -1);
    cSPPaletteItemUI::Init(item, window, a, info);
  }
}

// @ 0x005ee660
void cSPPaletteItemUIDrag::Shutdown() {
  if (mSwatch) {
    GetEditorUI()->RemoveContent(mSwatch);
    mSwatch.AsOutParam();
  }
  cSPPaletteItemUI::Shutdown();
}

// @ 0x005ee6a0
void cSPPaletteItemUIDrag::OnSelected() {
  if (mWinRoot) mWinRoot->SetShadeColor(0x8800bbbb);
  Trigger();
}

// @ 0x005ee6d0
void cSPPaletteItemUIDrag::OnDeselected() {
  if (mWinRoot) mWinRoot->SetShadeColor(0xffffff);
}

// ---------------------------------------------------------------------------------------------
struct MessageData {
  MessageData() : mID(0) {}
  long mRefCount;     // +0x4
  uint32_t mData[10];
  uint32_t mID;       // +0x30
  uint32_t mPad34;
};
struct BehaviorMessage : public MessageData {
  BehaviorMessage() { _InterlockedExchange(&mRefCount, 0); }
  virtual ~BehaviorMessage();  // 0x00421cf0
};
struct cPaintThemeMessage : public BehaviorMessage {
  cPaintThemeMessage(uint32_t id) : mField38(0) { mID = id; }
  uint32_t mField38;  // +0x38
  uint32_t mPad3c;
};

class cSPPaletteItemUIOneClickPaint : public cSPPaletteItemUISelectable {
 public:
  cSPPaletteItemUIOneClickPaint(uint32_t paintGroupId);
  cSPPaletteItemUIOneClickPaint();
  virtual void Init(cSPPaletteItem* item, IWindow* window, int a, cSPPaletteInfo* info);
  virtual void Shutdown();
  virtual void Trigger();
  virtual void Update(float dt);
  virtual void OnRollover();
  virtual void OffRollover();
  virtual void SetIsSelected(bool selected);
  virtual void OnSelected();
  virtual void OnDeselected();
  virtual void OnPaintThemeSelected(uint32_t paintID, uint32_t groupID, int unused);  // +0x44
  virtual void SendPaintMessage();                                                    // +0x48
  virtual void SendTriggerMessage();                                                  // +0x4c
  virtual bool HandleMessage(uint32_t messageID, void* message);

  uint32_t mPaintGroupId;                       // +0x2c
  AutoRefCount<IWindow> mWinThumbnail;          // +0x30
  AutoRefCount<IWindow> mWinNewItem;            // +0x34
  AutoRefCount<cSPUILayout> mSelectedLayout;    // +0x38
  AutoRefCount<cSPUILayout> mRolloverLayout;    // +0x3c
  AutoRefCount<IWindow> mWinBase;               // +0x40
  EA::Messaging::AutoHandler mAutoHandler;      // +0x44
  bool mLocked;                                 // +0x58
  bool mNewItem;                                // +0x59
  EA::Stopwatch mUnlockTimer;                   // +0x60
};

static const uint32_t kOneClickPaintMessages[2] = {0x5090434, 0x578dedb};  // 0x013f9984

// @ 0x005ee710
void cSPPaletteItemUIOneClickPaint::SetIsSelected(bool selected) {
  if (selected != mSelected) {
    mSelected = selected;
    if (selected)
      OnSelected();
    else
      OnDeselected();
  }
}

// @ 0x005ee740
void cSPPaletteItemUIOneClickPaint::Trigger() {
  SendTriggerMessage();
  SendPaintMessage();
}

// @ 0x005ee760
void cSPPaletteItemUIOneClickPaint::OnPaintThemeSelected(uint32_t paintID, uint32_t groupID, int) {
  if (groupID == mPaintGroupId || groupID == 0xffffffff) {
    if (paintID == GetPaletteItem()->mItemKey.mInstance)
      SetIsSelected(true);
    else
      SetIsSelected(false);
  } else if (mPaintGroupId == 0xffffffff)
    SetIsSelected(false);
}

// @ 0x005ee7b0
cSPPaletteItemUIOneClickPaint::cSPPaletteItemUIOneClickPaint(uint32_t paintGroupId)
    : mPaintGroupId(paintGroupId), mLocked(false), mNewItem(false), mUnlockTimer(0, false) {
  mInterfaceID = 0xeccc3657;
}

// @ 0x005ee820
cSPPaletteItemUIOneClickPaint::cSPPaletteItemUIOneClickPaint()
    : mPaintGroupId(0xffffffff), mUnlockTimer(0, false) {
  mInterfaceID = 0xeccc3657;
}

// @ 0x005ee880
void cSPPaletteItemUIOneClickPaint::Init(cSPPaletteItem* item, IWindow* window, int a, cSPPaletteInfo* info) {
  mNewItem = false;
  mLocked = false;
  mWinNewItem.AsOutParam();
  if (item && window) {
    mSelectedLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout();
    mSelectedLayout->Init(Key(0xd71d1992, 0x510a95b, 0x40464100), true, 0x5b598fa);
    mRolloverLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout();
    mRolloverLayout->Init(Key(0xdd1d231a, 0x510a95b, 0x40464100), true, 0x5b598fa);
    mWinBase = window;
    IWindow* const pThumbnail = window->FindWindowByID(0x5cb2c81, true);
    mSelectedLayout->SetParentWin(mWinBase, true, 0x5b598fa);
    IWindow* pWindow = mSelectedLayout->FindWindowByID(0x5caddd5, true);
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
      mWinNewItem = SPUIHelpers::CreateImageWindow(Key(0x1249ff0f, 0x2f7d0004, 0x100d976e),
                                                   EA::Point2DT<float>(0.0f, 0.0f), window->GetParent());
      if (mWinNewItem) {
        RectT area = mWinBase->GetRealArea();
        mWinNewItem->SetArea(area);
        SPUIHelpers::SetWindowAlpha(mWinNewItem, 0.0f);
        mWinNewItem->SetFlag(2, false);
        mWinNewItem->SetFlag(0x10, true);
        mWinNewItem->SetLayer(-1);
        mUnlockTimer.SetUnits(EA::Stopwatch::kUnitsMilliseconds);
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
    cSPPaletteItemUISelectable::Init(item, window, a, info, mPaintGroupId);
    mAutoHandler.Init(MessageServer(), this, kOneClickPaintMessages, 2, 0);
  }
}

// @ 0x005eece0
void cSPPaletteItemUIOneClickPaint::Update(float) {
  if (mWinNewItem) {
    if (!mUnlockTimer.IsRunning() && mLocked) {
      SPUIHelpers::SetWindowAlpha(mWinNewItem, 0.0f);
      const RectT area = SPUIHelpers::GetWindowScreenArea(mWinBase);
      const RectT screen = WindowManager()->GetMainWindow()->GetRealArea();
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

// @ 0x005eef80
void cSPPaletteItemUIOneClickPaint::Shutdown() {
  mAutoHandler.Shutdown();
  if (mSelectedLayout) mSelectedLayout->Shutdown(true);
  if (mRolloverLayout) mRolloverLayout->Shutdown(true);
  cSPPaletteItemUISelectable::Shutdown();
}

struct PaintMessageData {
  uint32_t pad[2];
  uint32_t mPaintID;  // +0x8
  uint32_t pad0c;
  uint32_t mGroupID;  // +0x10
  uint32_t pad14;
  int mField18;       // +0x18
};

// @ 0x005eefd0
bool cSPPaletteItemUIOneClickPaint::HandleMessage(uint32_t messageID, void* message) {
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
  return cSPPaletteItemUISelectable::HandleMessage(messageID, message);
}

// @ 0x005ef030
void cSPPaletteItemUIOneClickPaint::OnSelected() {
  if (mSelectedLayout && mRolloverLayout) {
    IWindow* pWindow = mSelectedLayout->FindWindowByID(0x5caddd5, true);
    if (pWindow) pWindow->SetFlag(1, true);
    pWindow = mRolloverLayout->FindWindowByID(0x5caddd5, true);
    if (pWindow) pWindow->SetFlag(1, false);
  }
}

// @ 0x005ef080
void cSPPaletteItemUIOneClickPaint::OnDeselected() {
  if (mSelectedLayout) {
    IWindow* pWindow = mSelectedLayout->FindWindowByID(0x5caddd5, true);
    if (pWindow) pWindow->SetFlag(1, false);
  }
}

// @ 0x005ef0b0
void cSPPaletteItemUIOneClickPaint::OnRollover() {
  if (mRolloverLayout && !IsSelected()) {
    IWindow* pWindow = mRolloverLayout->FindWindowByID(0x5caddd5, true);
    if (pWindow) pWindow->SetFlag(1, true);
  }
  cSPPaletteItemUI::OnRollover();
}

// @ 0x005ef0f0
void cSPPaletteItemUIOneClickPaint::OffRollover() {
  if (mRolloverLayout && !IsSelected()) {
    IWindow* pWindow = mRolloverLayout->FindWindowByID(0x5caddd5, true);
    if (pWindow) pWindow->SetFlag(1, false);
  }
  cSPPaletteItemUI::OffRollover();
}

// @ 0x005ef130
void cSPPaletteItemUIOneClickPaint::SendPaintMessage() {
  cPaintThemeMessage msg(0x5090434);
  PaintMessageData* pData = (PaintMessageData*)&msg;
  pData->mPaintID = GetPaletteItem()->mItemKey.mInstance;
  pData->mGroupID = mPaintGroupId;
  pData->mField18 = 0;
  MessageServer()->MessageSend(msg.mID, &msg, 0);
}

// ---------------------------------------------------------------------------------------------
class cSPPaletteItemUIPlannerEdit : public cSPPaletteItemUI, public EA::Messaging::IHandlerRC {
 public:
  virtual void Shutdown();
  virtual void* Cast(uint32_t typeID) const;
  virtual void OnRollover();
  void SetLocked(bool locked);

  AutoRefCount<IWindow> mWinSwatch;          // +0x24
  AutoRefCount<IWindow> mWinRoot2;           // +0x28
  AutoRefCount<IWindow> mWinIcon;            // +0x2c
  AutoRefCount<IWindow> mWinLockedIcon;      // +0x30
  AutoRefCount<IWindow> mWinEditButton;      // +0x34
  AutoRefCount<cSPUILayout> mLayout;         // +0x38
  AutoRefCount<cSPSwatch> mSwatch;           // +0x3c
  EA::Messaging::AutoHandler mAutoMsgHandler;  // +0x40
  Key mModelKey;                             // +0x54
  int mWhichEditor;                          // +0x60
  AutoRefCount<cSPPaletteInfo> mInfo;        // +0x64
  bool mLocked;                              // +0x68
  uint32_t mID;                              // +0x6c
};

// @ 0x005ef1b0
void* cSPPaletteItemUIPlannerEdit::Cast(uint32_t typeID) const {
  switch ((int)typeID) {
    case (int)0xee3f516e:
      return (IWinProc*)this;
    case 0x4784b27:
    case (int)0xb4e4f69b:
      return (cSPPaletteItemUIPlannerEdit*)this;
    case 0x2f009dd0:
      return (IWinProc*)this;
  }
  return 0;
}

// @ 0x005ef1f0
void cSPPaletteItemUIPlannerEdit::Shutdown() {
  if (mSwatch) {
    mSwatch->Shutdown();
    GetEditorUI()->RemoveContent(mSwatch);
    mSwatch.AsOutParam();
  }
  mAutoMsgHandler.Shutdown();
}

// @ 0x005ef250
void cSPPaletteItemUIPlannerEdit::SetLocked(bool locked) {
  if (mSwatch) {
    mSwatch->SetLocked(locked);
    if (mSwatch->IsLocked() && !SPUIHelpers::IsWindowVisible(mWinSwatch))
      mSwatch->SetShowLock(false);
    else if (!mSwatch->IsLocked() && SPUIHelpers::IsWindowVisible(mWinSwatch))
      mSwatch->SetShowLock(true);
  }
}

// @ 0x005ef2d0
void cSPPaletteItemUIPlannerEdit::OnRollover() {
  if (mSwatch) {
    cSPUIPropertyLayout* layout = GetEditorUI()->GetPropertyLayout();
    if (layout) {
      const uint32_t textID = mLocked ? 0x4ecf388 : 0x4ecf38a;
      AutoRefCount<cSPEditorVehicleAbilities> content(new ("Editor", 0, 0, 0, 0) cSPEditorVehicleAbilities(
          mPaletteItem->mItemKey, mInfo->mModelType, 0xa592740e, textID, false));
      layout->SetItem(mPaletteItem, mInfo, content, true);
      layout->SetMode(2);
      const RectT screen = WindowManager()->GetMainWindow()->GetRealArea();
      layout->SetPositionAndOffset(mSwatch->mX, mSwatch->mY, (screen.right - screen.left) * 0.1875f,
                                   (screen.bottom - screen.top) * 0.0f);
    }
    mSwatch->SetShowLock(true);
    mSwatch->SetHighlight(true);
    mSwatch->PlayEffect(0x5385a40f, true);
  }
  cSPPaletteItemUI::OnRollover();
}
}  // namespace SP
