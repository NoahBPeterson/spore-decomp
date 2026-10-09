// SP::cSPEditorPaintLikeThis (palette "paint like this" item), its base
// cSPPaletteItemUIOneClickPaint dtor, a palette-item message class and small find helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380

#define PV(n) virtual void pv##n();

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  AutoRefCount& operator=(T* pObject) {
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

template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};

namespace ResourceMan {
struct Key {
  unsigned int mInstance, mType, mGroup;
  Key() {}
  Key(unsigned int i, unsigned int t, unsigned int g) : mInstance(i), mType(t), mGroup(g) {}
};
class IResourceManager {
 public:
  PV(0) PV(1) PV(2)
  virtual bool GetResource(const Key& key, void* result, int a, int b, int c, int d);  // +0xc
};
IResourceManager* GetManager();
}  // namespace ResourceMan

namespace UTFWin {
class IWinProc;
class IWindow {
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
  virtual void AddWinProc(IWinProc* proc);              // +0x104
  virtual void RemoveWinProc(IWinProc* proc);           // +0x108
};
class IWinProc {
 public:
  ~IWinProc() {}
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4)
  virtual bool HandleUIMessage(IWindow* window, const void* message);  // +0x14
};
struct Message {
  IWindow* mpSource;  // +0x0
  uint32_t pad4;
  int mType;          // +0x8
};
}  // namespace UTFWin

namespace Messaging {
class Server;
class IHandler {
 public:
  ~IHandler() {}
  virtual bool HandleMessage(uint32_t messageID, void* message);
};
class IHandlerRC : public IHandler {
 public:
  virtual int AddRef();
  virtual int Release();
};
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMSG(uint32_t messageID, void* data, void* source);  // +0x14
  PV(6) PV(7) PV(8)
  virtual void AddHandler(IHandler* handler, uint32_t messageID);      // +0x24
};
void RemoveHandler(IMessageServer* server, IHandler* handler, const uint32_t* ids, unsigned int count, int priority);
class AutoHandler {
 public:
  IMessageServer* mpServer;    // +0x0
  IHandler* mpHandler;         // +0x4
  const uint32_t* mpIdArray;   // +0x8
  unsigned int mnIdArrayCount; // +0xc
  int mnPriority;              // +0x10
  AutoHandler() : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0), mnPriority(0) {}
  ~AutoHandler() { RemoveHandlers(); }
  void RemoveHandlers() {
    if (mpServer) {
      IMessageServer* const pServer = mpServer;
      mpServer = 0;
      RemoveHandler(pServer, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
    }
  }
  void AddHandlers(IMessageServer* server, IHandler* handler, const uint32_t* ids, unsigned int count, int priority) {
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
}  // namespace Messaging
}  // namespace EA

using EA::UTFWin::IWindow;
using EA::UTFWin::IWinProc;

class cSPUILayout {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  cSPUILayout();
  IWindow* FindWindowByID(uint32_t id, bool recursive);
  bool Init(const EA::ResourceMan::Key& key, bool b, uint32_t id);
  void SetParentWin(IWindow* parent, bool b, uint32_t id);
  void Shutdown(bool b);
  char pad[0x18 - 4];
};

class cSPUITooltipWinProc : public IWinProc {
 public:
  cSPUITooltipWinProc(const wchar_t* name, uint32_t id, const wchar_t* text, int a, const void* b, int c);  // UI::Tooltip::Tooltip
  void SetText(const wchar_t* text);
};
void* TooltipAlloc(unsigned int size, unsigned int align, const char* name, void* allocator);  // FUN_009512d0
void* GetUIAllocator();                                                                        // FUN_009512c0

struct cDirectPropertyList {
  char pad[0x3c];
  struct Values {
    char pad[0x118];
    int mbGalacticAdventures;
  }* mpValues;
};
extern cDirectPropertyList* sAppProperties;

namespace SP {
EA::Messaging::IMessageServer* MessageServer();
class IConfigManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void SetValue(uint32_t id, int value);  // +0x2c
  virtual int GetValue(uint32_t id);              // +0x30
  PV(13) PV(14)
  virtual void Save();                            // +0x3c
};
IConfigManager* ConfigManager();
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, class cPropertyList*& result);  // +0x2c
};
IPropertyManager* PropertyManager();
class cPropertyList {
 public:
  virtual int AddRef();
  virtual int Release();
};
void ShowSporepediaHint(const void* a, const void* b);  // FUN_00809db0
extern char g_SporepediaHintA[];                         // 0x01514bbc
extern char g_SporepediaHintB[];                         // 0x015eb84c

class cString {
 public:
  cString();
  ~cString();  // SP::cString::c_str (0x006b5240) is the out-of-line destructor
  void Load(uint32_t tableID, uint32_t stringID, int flags);
  const wchar_t* GetText(int a, int b);  // 0x006b55c0
  const wchar_t* GetText(void* tmp, int a, const void* b, int c);
  char pad[0xc];
};

class cSPPaletteItem {
 public:
  cSPPaletteItem();  // FUN_005c66a0
  PV(0)
  virtual int AddRef();
  virtual int Release();
  void Init(const EA::ResourceMan::Key* key, int a, int b);
  void Shutdown();
  char pad04[4];
  struct Iface {
    PV(0) PV(1) PV(2)
    virtual void* Cast(uint32_t id);  // +0xc
  } mIface;  // +0x8
  char pad0c[0x54 - 0xc];
};
class cSPPaletteInfo {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  char pad04[0x8];
  EA::ResourceMan::Key mKey;  // +0xc
};

class cSPUIAssetBrowserCallback {
 public:
  virtual void OnAssetBrowserSelection(const EA::ResourceMan::Key& key);
};
namespace cSPUIAssetBrowser {
void Launch(uint32_t type, cSPUIAssetBrowserCallback* callback, uint32_t flags);
}

class cSPPaletteItemPtr;
class cISPPaletteItemUI {
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
struct PaletteItemInfo {
  char pad[0xc];
  uint32_t mID;  // +0xc
};

class cSPPaletteItemUI : public cISPPaletteItemUI, public IWinProc, public EA::RefCountVTemplate<int> {
 public:
  ~cSPPaletteItemUI();  // FUN_005c6c50
  bool HandleUIMessage(IWindow* window, const void* message);  // SP::cSPPaletteItemUI::DoMessage (0x005c6d70)
  void OnLeftMouseUp();                                       // FUN_005c6ab0
  bool mIsRolledOver;                  // +0x18
  EA::AutoRefCount<IWindow> mWinRoot;  // +0x1c
};

class cSPPaletteItemUISelectable : public cSPPaletteItemUI, public EA::Messaging::IHandlerRC {
 public:
  ~cSPPaletteItemUISelectable() {}
  bool mSelected;                // +0x24
  unsigned int mSelectionGroup;  // +0x28
};

struct Stopwatch { uint64_t mStartTime; uint64_t mTotalTime; uint32_t mUnits; uint32_t mFlags; };

class cSPPaletteItemUIOneClickPaint : public cSPPaletteItemUISelectable {
 public:
  cSPPaletteItemUIOneClickPaint();                    // 0x005ee820
  cSPPaletteItemUIOneClickPaint(unsigned int group);  // 0x005ee7b0
  ~cSPPaletteItemUIOneClickPaint();
  bool HandleMessage(uint32_t messageID, void* message);  // 0x005eefd0
  void Init(cSPPaletteInfo* info, IWindow* button, int a, void* b);
  void Shutdown();
  void OnSelected();
  void OnRollover();
  void OffRollover();
  unsigned int mPaintGroupId;                        // +0x2c
  EA::AutoRefCount<IWindow> mWinThumbnail;           // +0x30
  EA::AutoRefCount<IWindow> mWinNewItem;             // +0x34
  EA::AutoRefCount<cSPUILayout> mSelectedLayout;     // +0x38
  EA::AutoRefCount<cSPUILayout> mRolloverLayout;     // +0x3c
  EA::AutoRefCount<IWindow> mWinBase;                // +0x40
  EA::Messaging::AutoHandler mAutoHandler;           // +0x44
  bool mLocked;                                      // +0x58
  bool mNewItem;                                     // +0x59
  Stopwatch mUnlockTimer;                            // +0x60
};

// @ 0x005C0E40
cSPPaletteItemUIOneClickPaint::~cSPPaletteItemUIOneClickPaint() {}

struct ModelChosenMessage {
  uint32_t mGroup;       // +0x0
  uint32_t pad04;
  uint32_t mInstance;    // +0x8
  uint32_t pad0c;
  uint32_t mType;        // +0x10
  uint32_t pad14;
  uint32_t mPaintGroup;  // +0x18
  uint32_t pad1c;
  IWindow* mpWindow;     // +0x20
  uint32_t pad24[3];
  uint32_t mFlags;       // +0x30
  uint32_t pad34;
};

class cSPEditorPaintLikeThis : public cSPPaletteItemUIOneClickPaint, public cSPUIAssetBrowserCallback {
 public:
  EA::AutoRefCount<cSPUILayout> mLayout;                          // +0x7c
  bool mReadyForMessages;                                         // +0x80
  bool mModelChosen;                                              // +0x81
  unsigned int mModelType;                                        // +0x84
  EA::ResourceMan::Key mModelKey;                                 // +0x88
  EA::ResourceMan::Key mDefaultKey;                               // +0x94
  EA::AutoRefCount<cSPPaletteInfo> mInfo;                         // +0xa0
  EA::AutoRefCount<cPropertyList> mPropList;                      // +0xa4
  EA::AutoRefCount<cSPPaletteItem> mModelToPaintLikePaletteItem;  // +0xa8
  EA::AutoRefCount<cSPUITooltipWinProc> mTooltip;                 // +0xac
  IWindow* mWinThumbnail;                                         // +0xb0
  IWindow* mWinRoot;                                              // +0xb4
  IWindow* mBtnLoadMain;                                          // +0xb8
  IWindow* mBtnLoadTray;                                          // +0xbc
  IWindow* mWinRolloverCatcher;                                   // +0xc0
  IWindow* mWinBackground;                                        // +0xc4
  IWindow* mWinLoadHighlight;                                     // +0xc8
  int mShowingHint;                                               // +0xcc
  EA::Messaging::AutoHandler mAutoHandler;                        // +0xd0

  cSPEditorPaintLikeThis(unsigned int paintGroup);
  ~cSPEditorPaintLikeThis();
  void SetImage(EA::ResourceMan::Key key);
  void OnPaintThemeSelected(uint32_t themeID, int unused, IWindow* window);
  void OnSelected();
  void OnRollover();
  void OffRollover();
  void OnLeftMouseUp();
  void LaunchSporepedia();
  bool HandleUIMessage(IWindow* window, const void* message);
  void Shutdown();
  void OnAssetBrowserSelection(const EA::ResourceMan::Key& key);
  void SendPaletteItemMessage();
  void SendPaintMessage();
  void SetModel(const EA::ResourceMan::Key& key);
  bool HandleMessage(uint32_t messageID, void* message);
  void Init(cSPPaletteInfo* info, IWindow* parent, int a, void* palette);
};

// @ 0x005C0C00
void cSPEditorPaintLikeThis::OnPaintThemeSelected(uint32_t themeID, int unused, IWindow* window) {
  if (themeID != mPaintGroupId && themeID != 0xffffffff) {
    SetIsSelected(false);
    return;
  }
  if (themeID == GetPaletteItem()->mID && window == mWinThumbnail)
    SetIsSelected(true);
  else
    SetIsSelected(false);
}

// @ 0x005C0C60
void cSPEditorPaintLikeThis::OnSelected() {
  if (mModelChosen)
    cSPPaletteItemUIOneClickPaint::OnSelected();
}

// @ 0x005C0C80
void cSPEditorPaintLikeThis::OnRollover() {
  if (mModelChosen)
    cSPPaletteItemUIOneClickPaint::OnRollover();
}

// @ 0x005C0C90
void cSPEditorPaintLikeThis::OffRollover() {
  if (mModelChosen)
    cSPPaletteItemUIOneClickPaint::OffRollover();
}

// @ 0x005C0CA0
void cSPEditorPaintLikeThis::OnLeftMouseUp() {
  if (mModelChosen && !IsLocked())
    cSPPaletteItemUI::OnLeftMouseUp();
}

// @ 0x005C0CD0
void cSPEditorPaintLikeThis::LaunchSporepedia() {
  uint32_t type = sAppProperties->mpValues->mbGalacticAdventures ? 0x1701f8d6 : 0x55cace93;
  cSPUIAssetBrowser::Launch(type, this, 0xad0e52);
}

// @ 0x005C0D20
bool cSPEditorPaintLikeThis::HandleUIMessage(IWindow* window, const void* message) {
  if (window != mWinRolloverCatcher && window != mBtnLoadTray)
    return cSPPaletteItemUI::HandleUIMessage(window, message);
  const EA::UTFWin::Message* msg = (const EA::UTFWin::Message*)message;
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

// @ 0x005C0F40
cSPEditorPaintLikeThis::cSPEditorPaintLikeThis(unsigned int paintGroup)
    : mReadyForMessages(false), mModelChosen(false), mModelType(0), mModelKey(0, 0, 0), mDefaultKey(0, 0, 0),
      mWinThumbnail(0), mBtnLoadMain(0), mBtnLoadTray(0), mWinRolloverCatcher(0) {
  cSPPaletteItemUIOneClickPaint((unsigned int)paintGroup);
}

// @ 0x005C1050
cSPEditorPaintLikeThis::~cSPEditorPaintLikeThis() {}

// @ 0x005C1130
void cSPEditorPaintLikeThis::Shutdown() {
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
  cSPPaletteItemUIOneClickPaint::Shutdown();
}

// palette item selection message (vtables 0x013f7e34 / 0x013f7e30)
class cMessageBase {
 public:
  ~cMessageBase() {}
  virtual void v0();
};
class cPaletteItemMessage : public cMessageBase, public EA::RefCountVTemplate<int> {
 public:
  uint32_t mMessageID;                           // +0xc
  int mInterfaceID;                              // +0x10
  uint32_t mField14;                             // +0x14
  uint32_t mField18;                             // +0x18
  uint32_t mField1c;                             // +0x1c
  EA::AutoRefCount<IWindow> mpObject;            // +0x20
  EA::AutoRefCount<IWindow> mpWindow;            // +0x24
  cPaletteItemMessage() : mField14(0), mField18(0), mField1c(0) {}
  virtual void v0();
};

// @ 0x005C1280
cPaletteItemMessage* ConstructPaletteItemMessage(cPaletteItemMessage* p) { return new (p) cPaletteItemMessage(); }

// @ 0x005C12C0 / 0x005C12F0: ~cPaletteItemMessage (plain and scalar deleting)
class cPaletteItemMessageD : public cPaletteItemMessage {
 public:
  ~cPaletteItemMessageD() {}
};

// @ 0x005C1340
void cSPEditorPaintLikeThis::OnAssetBrowserSelection(const EA::ResourceMan::Key& key) {
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

// @ 0x005C13B0
void cSPEditorPaintLikeThis::SendPaletteItemMessage() {
  cPaletteItemMessage msg;
  msg.mInterfaceID = mInterfaceID;
  msg.mMessageID = 0xb2e18705;
  if (mModelToPaintLikePaletteItem)
    msg.mpObject = (IWindow*)mModelToPaintLikePaletteItem->mIface.Cast(0xee3f516e);
  MessageServer()->PostMSG(msg.mMessageID, &msg, 0);
}

extern "C" long __cdecl _InterlockedExchange(volatile long* target, long value);
#pragma intrinsic(_InterlockedExchange)
struct AtomicInt {
  volatile long mValue;
  AtomicInt() { _InterlockedExchange(&mValue, 0); }
};
class BehaviorMessage {
 public:
  BehaviorMessage() {}
  virtual void v0();
  AtomicInt mRefCount;  // +0x4
};
class cPaintMessage : public BehaviorMessage {
 public:
  cPaintMessage() : mMessageID(0), mFlags(0) {}
  ~cPaintMessage();  // SlotMessage::Destruct (0x00421cf0)
  virtual void v0();
  uint32_t mItemID;     // +0x8
  uint32_t pad0c;
  uint32_t mGroup;      // +0x10
  uint32_t pad14;
  IWindow* mpWindow;    // +0x18
  uint32_t pad1c[5];
  uint32_t mMessageID;  // +0x30
  uint32_t pad34;
  uint32_t mFlags;      // +0x38
  uint32_t pad3c;
};

// @ 0x005C14F0
void cSPEditorPaintLikeThis::SendPaintMessage() {
  cPaintMessage msg;
  msg.mMessageID = 0x5090434;
  msg.mItemID = GetPaletteItem()->mID;
  msg.mGroup = mPaintGroupId;
  msg.mpWindow = mWinThumbnail;
  MessageServer()->PostMSG(msg.mMessageID, &msg, 0);
}

struct cSPEditorStrings {
  char pad[0x1c];
  const wchar_t* mpModelName;  // +0x1c
  void SetModelName(const wchar_t* name);  // FUN_005d60c0
};
extern cSPEditorStrings* g_EditorStrings;  // 0x015eebec
struct cSPModelResource { const wchar_t* GetName(); /* FUN_00414e10 */ };

namespace eastl {
extern wchar_t gEmptyString[2];
class wstring {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  int mAllocator;
  wstring(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
  ~wstring() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
  void RangeInitialize(const wchar_t* p);
};
}

// @ 0x005C1570
void cSPEditorPaintLikeThis::SetModel(const EA::ResourceMan::Key& key) {
  if (mModelChosen && key.mInstance == 0)
    return;
  mModelKey = key;
  if (key.mInstance) {
    mModelToPaintLikePaletteItem->Init(&mModelKey, 0, 0);
    mModelChosen = true;
    if (mWinRolloverCatcher)
      mWinRolloverCatcher->SetFlag(1, true);
    if (mBtnLoadTray) {
      mBtnLoadTray->SetFlag(1, false);
      mBtnLoadTray->SetFlag(2, false);
    }
    if (mWinRoot)
      mWinRoot->SetFlag(1, true);
    if (mWinLoadHighlight)
      mWinLoadHighlight->SetFlag(1, true);
    SetImage(mModelKey);
    if (mTooltip) {
      eastl::wstring oldName(g_EditorStrings->mpModelName);
      cString text;
      EA::ResourceMan::Key resKey = mModelKey;
      resKey.mType = 0x30bdee3;
      EA::AutoRefCount<cPropertyList> resource;
      EA::ResourceMan::IResourceManager* rm = EA::ResourceMan::GetManager();
      if (rm->GetResource(resKey, &resource.AsOutParam(), 0, 0, 0, 0)) {
        cSPModelResource* model = resource ? (cSPModelResource*)((EA::UTFWin::IWindow*)resource.mpObject)->Cast(0x30bdee3) : 0;
        g_EditorStrings->SetModelName(model->GetName());
      }
      text.Load(0xc0152a6d, 0x5af4a05, 0);
      cSPUITooltipWinProc* tip = mTooltip ? (cSPUITooltipWinProc*)((IWindow*)mTooltip.mpObject)->Cast(0x3796ce5) : 0;
      tip->SetText(text.GetText(-1, 1));
      g_EditorStrings->SetModelName(oldName.mpBegin);
    }
  } else {
    mModelChosen = false;
    if (mWinRolloverCatcher)
      mWinRolloverCatcher->SetFlag(1, false);
    if (mBtnLoadTray) {
      mBtnLoadTray->SetFlag(1, true);
      mBtnLoadTray->SetFlag(2, true);
    }
    if (mWinRoot)
      mWinRoot->SetFlag(1, false);
    if (mWinLoadHighlight)
      mWinLoadHighlight->SetFlag(1, false);
    if (mTooltip) {
      cString text;
      text.Load(0xc0152a6d, 0x5af4a04, 0);
      cSPUITooltipWinProc* tip = mTooltip ? (cSPUITooltipWinProc*)((IWindow*)mTooltip.mpObject)->Cast(0x3796ce5) : 0;
      tip->SetText(text.GetText(-1, 1));
    }
    SetIsSelected(false);
  }
}

// @ 0x005C1870
bool cSPEditorPaintLikeThis::HandleMessage(uint32_t messageID, void* message) {
  if (messageID == 0x57a4bc9) {
    ModelChosenMessage* msg = (ModelChosenMessage*)message;
    if (msg->mpWindow == mWinThumbnail) {
      EA::ResourceMan::Key key(msg->mInstance, msg->mType, msg->mGroup);
      if (msg->mPaintGroup == mPaintGroupId || msg->mPaintGroup == 0xffffffff)
        SetModel(key);
    }
    return false;
  }
  if (sAppProperties->mpValues->mbGalacticAdventures && messageID == 0x604efa1) {
    uint32_t button = ((uint32_t*)message)[2];
    if (button == 0x1510d07)
      return false;
    if (mShowingHint == 1) {
      switch (button) {
        case 0x5107b17:
          ConfigManager()->SetValue(0x604a561, 0);
          ConfigManager()->Save();
        case 0x5107b1a:
          mShowingHint = 0;
          break;
      }
      LaunchSporepedia();
    }
    return false;
  }
  return cSPPaletteItemUIOneClickPaint::HandleMessage(messageID, message);
}

static const uint32_t sPaintLikeThisMessages[2] = {0x57a4bc9, 0x604efa1};

// @ 0x005C1960
void cSPEditorPaintLikeThis::Init(cSPPaletteInfo* info, IWindow* parent, int a, void* palette) {
  if (parent) {
    if (palette)
      mModelType = ((uint32_t*)palette)[0x2c / 4];
    mLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout();
    mLayout->Init(EA::ResourceMan::Key(0x6d7fbf32, 0x510a95b, 0x40464100), true, 0x5b598fa);
    mLayout->SetParentWin(parent, true, 0x5b598fa);
    mBtnLoadMain = mLayout->FindWindowByID(0x4a1cb70, true);
    mWinRolloverCatcher = mLayout->FindWindowByID(0x4a1cb6d, true);
    mBtnLoadTray = mLayout->FindWindowByID(0x5ca82b7, true);
    mWinRoot = mLayout->FindWindowByID(0x5cab74a, true);
    mWinBackground = mLayout->FindWindowByID(0x5cb24da, true);
    mWinLoadHighlight = mLayout->FindWindowByID(0x5cb2c81, true);
    cSPPaletteItemUIOneClickPaint::Init(info, mBtnLoadMain, a, palette);
    mAutoHandler.AddHandlers(MessageServer(), this, sPaintLikeThisMessages, 2, 0);
    const EA::ResourceMan::Key& infoKey = info->mKey;
    PropertyManager()->GetPropertyList(infoKey.mInstance, infoKey.mGroup, mPropList.AsOutParam());
    SetModel(EA::ResourceMan::Key(0, 0, 0));
    cString text;
    text.Load(0xc0152a6d, 0x5af4a04, 0);
    void* mem = TooltipAlloc(0x68, 4, "UI/Tooltip", GetUIAllocator());
    char tmp[4];
    mTooltip = mem ? new (mem) cSPUITooltipWinProc(L"Tooltips", 0x3754e6c, text.GetText(tmp, 0, (const void*)0x13f7c8c, 0), 0,
                                                  0, 0)
                   : 0;
    mBtnLoadMain->AddWinProc(mTooltip);
    mBtnLoadTray->AddWinProc(mTooltip);
    mBtnLoadTray->AddWinProc(this);
    mWinRolloverCatcher->AddWinProc(this);
    mReadyForMessages = true;
    mModelToPaintLikePaletteItem = new ("Editor", 0, 0, 0, 0) cSPPaletteItem();
    mModelToPaintLikePaletteItem->Init(&infoKey, 0, 0);
    mWinThumbnail = (IWindow*)(cSPPaletteItem*)mModelToPaintLikePaletteItem;
  }
}

// @ 0x005C1CC0  eastl::find<T**, T*>
template <typename InputIterator, typename T>
InputIterator find(InputIterator first, InputIterator last, const T& value) {
  while ((first != last) && !(*first == value))
    ++first;
  return first;
}
template cSPPaletteItem** find<cSPPaletteItem**, cSPPaletteItem*>(cSPPaletteItem**, cSPPaletteItem**, cSPPaletteItem* const&);

struct cSPPaletteCategory {
  char pad[0xc];
  struct Page { char pad[0x5c]; uint32_t mCategory; }** mPagesBegin;  // +0xc
  Page** mPagesEnd;                                                  // +0x10
  char pad14[0x34 - 0x14];
  cSPPaletteItem** mItemsBegin;  // +0x34
  cSPPaletteItem** mItemsEnd;    // +0x38
  int CountPagesInCategory(uint32_t category);
  bool HasItem(cSPPaletteItem* item);
};

// @ 0x005C1D10
int cSPPaletteCategory::CountPagesInCategory(uint32_t category) {
  int n = (int)(mPagesEnd - mPagesBegin);
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (mPagesBegin[i]->mCategory == category)
      count++;
  }
  return count;
}

// @ 0x005C1D40
bool cSPPaletteCategory::HasItem(cSPPaletteItem* item) {
  return find(mItemsBegin, mItemsEnd, item) != mItemsEnd;
}
}  // namespace SP
