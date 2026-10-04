// slice s005c6340 -- SP::cSPPalette::Init, SP::cSPPaletteItem::Init, SP::cSPPaletteItemUI /
// cSPPaletteItemUISelectable (ctor/dtor, Init/Shutdown, DoMessage, rollover, selection) and a
// rollover-tooltip helper class from the same TU.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
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
  T** AsPPTypeParam();  // 0x00a16f40 (out of line)
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

// intrusive count released inline (EA::RefCount-style): delete through the virtual dtor at 1
class RefCounted {
 public:
  virtual ~RefCounted();
  int mnRefCount;
  void AddRef() { mnRefCount++; }
  int Release() {
    const int count = mnRefCount - 1;
    mnRefCount = mnRefCount - 1;
    if (count)
      return count;
    mnRefCount = 1;
    delete this;
    return 0;
  }
};

template <typename T>
class RefPtr {
 public:
  T* mpObject;
  RefPtr() : mpObject(0) {}
  ~RefPtr() { if (mpObject) mpObject->Release(); }
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
};

class IResourceFilter {
 public:
  virtual ~IResourceFilter() {}
  virtual bool IsValid(const Key& key);
};

class StandardFileFilter : public IResourceFilter {
 public:
  StandardFileFilter(uint32_t instanceID, uint32_t groupID, uint32_t typeID, uint32_t subtypeID)
      : mInstanceID(instanceID), mGroupID(groupID), mTypeID(typeID), mSubtypeID(subtypeID) {}
  virtual bool IsValid(const Key& key);
  uint32_t mInstanceID;
  uint32_t mGroupID;
  uint32_t mTypeID;
  uint32_t mSubtypeID;
};
}  // namespace ResourceMan

struct RectT {
  float left, top, right, bottom;
  RectT(const RectT& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
};

namespace UTFWin {
class IWinProc;
class IWindow : public COM::IUnknown32 {
 public:
  PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual const RectT& GetRealArea();  // +0x34
  virtual const RectT& GetArea();      // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27)
  PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40)
  PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53)
  PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc* proc);     // +0x104
  virtual void RemoveWinProc(IWinProc* proc);  // +0x108
};

struct Message {
  uint32_t pad0[2];
  int mEventType;   // +0x8
  int mParam0c;     // +0xc
  uint32_t pad10[2];
  int mButton;      // +0x18
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
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
  virtual IWindow* GetCapture(int which);  // +0x48
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
  virtual void MessageSend(uint32_t messageID, void* message, IHandler* handler);       // +0x14
  PV(6) PV(7)
  virtual void AddHandler(IHandlerRC* handler, uint32_t messageID);                     // +0x20
  PV(9) PV(10)
  virtual void RemoveHandler(IHandlerRC* handler, uint32_t messageID, int priority);    // +0x2c
};
}  // namespace Messaging
}  // namespace EA

using EA::AutoRefCount;
using EA::ResourceMan::Key;
using EA::UTFWin::IWindow;
using EA::UTFWin::IWinProc;
using EA::UTFWin::Message;
using EA::RectT;

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
};
}  // namespace eastl

struct Property {
  char pad[0x12];
  unsigned short mType;  // +0x12
  int* GetInt();         // 0x0041e990
};

namespace EA { namespace ResourceMan {
class IResourceManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual int GetResourceKeyList(eastl::sp_vector<Key>* keys, IResourceFilter* filter, int flags);  // +0x38
};
}}
EA::ResourceMan::IResourceManager* ResourceManager();  // 0x008de1a0

class cDirectPropertyList;
namespace SP {
class cPropertyList {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property*& result);  // +0x24
};
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** result);  // +0x2c
};
IPropertyManager* PropertyManager();                                                // 0x0067de30
EA::Messaging::IMessageServer* MessageServer();                                     // 0x0067dcc0
EA::UTFWin::IWindowManager* WindowManager();                                        // 0x0067caa0
bool GetPropertyAsKeyInstance(cPropertyList* list, uint32_t id, uint32_t* result);  // 0x006a12a0
bool GetPropertyAsKeyGroup(cPropertyList* list, uint32_t id, uint32_t* result);     // 0x006a12e0
bool GetPropertyAsKey(cPropertyList* list, uint32_t id, Key* result);               // 0x006a1250
bool GetBoolProperty(cPropertyList* list, uint32_t id, bool* result);               // 0x00407190
bool IsKeyDown(int key);                                                            // 0x008d2fb0
bool IsDescendant(IWindow* window, IWindow* child);                                 // 0x00805150
int GetAudioSystem();                                                               // 0x00435e90
void PlayAudio(uint32_t id, int system);                                            // 0x00435ed0

struct AppPropertiesData { char pad[0x118]; int mDebugBlock; };
struct AppProperties { char pad[0x3c]; AppPropertiesData* mpData; };
extern AppProperties* sAppProperties;  // 0x015fd918

enum eModelType {};

class cSPPaletteCategory;

class cSPPalette : public EA::RefCountVTemplate<int>, public EA::COM::IUnknown32 {
 public:
  eastl::sp_vector<AutoRefCount<cSPPaletteCategory>, 1> mCategories;  // +0xc
  unsigned int mLayoutInstanceID;     // +0x1c
  unsigned int mImageGroupID;         // +0x20
  unsigned int mOptionalImageGroupID; // +0x24
  int mStartupCategory;               // +0x28
  eModelType mModelType;              // +0x2c
  unsigned int mPaletteGroupID;       // +0x30
  unsigned int mParam34;              // +0x34
  int mThemeIndex;                    // +0x38
  unsigned int mParam3c;              // +0x3c

  virtual int AddRef();
  virtual int Release();
  bool Init(const Key& key, unsigned int param3c, unsigned int param34, unsigned int imageGroupID,
            unsigned int optionalImageGroupID, int startupCategory, eModelType modelType);
  void LoadDefinitionPart(const Key& key);  // 0x005c6010
};

// @ 0x005C6340
inline bool GetIntProperty(cPropertyList* list, uint32_t id, int& value) {
  Property* prop;
  if (list->GetProperty(id, prop) && prop->mType == 9) {
    value = *prop->GetInt();
    return true;
  }
  return false;
}

bool cSPPalette::Init(const Key& key, unsigned int param3c, unsigned int param34, unsigned int imageGroupID,
                      unsigned int optionalImageGroupID, int startupCategory, eModelType modelType) {
  mParam3c = param3c;
  AutoRefCount<cPropertyList> list;
  IPropertyManager* pm = PropertyManager();
  pm->GetPropertyList(key.mInstance, key.mGroup, &list.AsOutParam());
  if (list) {
    GetIntProperty(list, 0x332b28b, mThemeIndex);
    GetPropertyAsKeyGroup(list, 0x2233661, &mPaletteGroupID);
    mParam34 = param34;
    if (imageGroupID)
      mImageGroupID = imageGroupID;
    else
      GetPropertyAsKeyInstance(list, 0xc46ec042, &mImageGroupID);
    mOptionalImageGroupID = optionalImageGroupID;
    mStartupCategory = startupCategory;
    mModelType = modelType;
    EA::ResourceMan::IResourceManager* rm = ResourceManager();
    eastl::sp_vector<Key> keys;
    EA::ResourceMan::StandardFileFilter filter(0xffffffff, (uint8_t)key.mInstance | 0x406b6b00, 0xb1b104,
                                               0xffffffff);
    rm->GetResourceKeyList(&keys, &filter, 0);
    Key* const end = keys.end();
    for (Key* it = keys.begin(); it != end; ++it) {
      Key partKey = *it;
      LoadDefinitionPart(partKey);
    }
    return true;
  }
  return false;
}

class cSPPaletteItem : public EA::RefCountVTemplate<int>, public EA::COM::IUnknown32 {
 public:
  enum eItemType {
    kItemTypeUnknown = -1,
    kBlock = 0xa2e50993,
    kBakedModel = 0x674ab27,
    kSwatch = 0x2c7c0887,
  };
  Key mItemKey;          // +0xc
  Key mThumbnailKey;     // +0x18
  eItemType mItemType;   // +0x24
  int mPriority;         // +0x28
  Key mSwatchKey;        // +0x2c
  uint32_t mSwatchColor; // +0x38
  Key mSwatchKey2;       // +0x3c
  int mIndex;            // +0x48
  bool mbHidden;         // +0x4c
  AutoRefCount<EA::COM::IUnknown32> mpData;  // +0x50

  virtual int AddRef();
  virtual int Release();
  bool Init(const Key& key, int index, uint32_t thumbnailGroup);
  void Shutdown();
};

// @ 0x005C6810
bool cSPPaletteItem::Init(const Key& key, int index, uint32_t thumbnailGroup) {
  mItemKey = key;
  mIndex = index;
  if (!mItemKey.mType)
    mItemKey.mType = 0xb1b104;
  mThumbnailKey = mItemKey;
  if (thumbnailGroup)
    mThumbnailKey.mGroup = thumbnailGroup;
  mThumbnailKey.mType = 0x2f7d0004;
  switch (mItemKey.mType) {
    case 0xb1b104: {
      if (sAppProperties->mpData->mDebugBlock && index < 0) {
        mItemType = kBlock;
        return true;
      }
      AutoRefCount<cPropertyList> list;
      if (PropertyManager()->GetPropertyList(mItemKey.mInstance, mItemKey.mGroup, list.AsPPTypeParam())) {
        if (!list)
          break;
        GetPropertyAsKeyInstance(list, 0x2196ad5, (uint32_t*)&mItemType);
        mPriority = 0;
        GetPropertyAsKeyInstance(list, 0x65f9e78, (uint32_t*)&mPriority);
        GetPropertyAsKey(list, 0x65f9e79, &mSwatchKey);
        mSwatchKey.mType = 0x510a95b;
        mSwatchKey.mGroup = 0x40464100;
        mSwatchColor = 0;
        GetPropertyAsKeyInstance(list, 0x65f9e7a, &mSwatchColor);
        GetPropertyAsKey(list, 0x65f9e7b, &mSwatchKey2);
        mSwatchKey2.mType = 0x510a95b;
        mSwatchKey2.mGroup = 0x40464100;
        mbHidden = false;
        GetBoolProperty(list, 0x6626a29, &mbHidden);
      }
      break;
    }
    case 0x2f7d0004:
      mItemType = kSwatch;
      mThumbnailKey = mItemKey;
      break;
    case 0x24682294:
    case 0x2399be55:
    case 0x2b978c46:
    case 0x476a98c7:
    case 0x3d97a8e4:
    case 0x438f6347:
    case 0xffffffff:
      mItemType = kBakedModel;
      break;
  }
  return mItemType != kItemTypeUnknown ? true : false;
}

// ---------------------------------------------------------------------------------------------
// palette-filter object (0x5c64e0 ctor / 0x5c6530 dtor) and its key checks
struct FilterKey { uint32_t lo, hi; };
FilterKey MakeFilterKey(void* a, void* b);  // 0x00593980 (__cdecl, 64-bit result)
class cFilterTarget {
 public:
  bool Accepts(FilterKey key);   // 0x005950c0
  bool Rejects(FilterKey key);   // 0x00595110
  bool Matches(FilterKey key);   // 0x00595190
};

class cPaletteFilterBase {
 public:
  cPaletteFilterBase() : mField4(0) {}
  virtual ~cPaletteFilterBase() {}
  int mField4;
};

class cPaletteFilter : public cPaletteFilterBase {
 public:
  cPaletteFilter();
  ~cPaletteFilter();
  bool CheckAccepts(cFilterTarget* target);
  bool CheckMatches(cFilterTarget* target);
  bool CheckRejected(cFilterTarget* target);
  bool NotRejected(cFilterTarget* target);

  EA::RefPtr<EA::RefCounted> mpOwner;         // +0x8
  AutoRefCount<EA::COM::IUnknown32> mpA;      // +0xc
  AutoRefCount<EA::COM::IUnknown32> mpC;      // +0x10
  AutoRefCount<EA::COM::IUnknown32> mpB;      // +0x14
  short mShort18;                             // +0x18
  int mField1c;                               // +0x1c
  int mField20;                               // +0x20
  float mMin;                                 // +0x24
  float mMax;                                 // +0x28
  int mIndex;                                 // +0x2c
  bool mbEnabled;                             // +0x30
  bool mbFlag31;                              // +0x31
};

// @ 0x005C64E0
cPaletteFilter::cPaletteFilter()
    : mShort18(0), mField1c(0), mField20(0), mMin(-1.0f), mMax(-1.0f), mIndex(-1),
      mbEnabled(true), mbFlag31(false) {}

// @ 0x005C6530
cPaletteFilter::~cPaletteFilter() {}

// @ 0x005C65F0
bool cPaletteFilter::CheckAccepts(cFilterTarget* target) {
  if (target)
    return target->Accepts(MakeFilterKey(mpB, mpA));
  return true;
}

// @ 0x005C6630
bool cPaletteFilter::NotRejected(cFilterTarget* target) {
  if (target)
    return !target->Rejects(MakeFilterKey(mpB, mpA));
  return false;
}

// @ 0x005C6670
bool cPaletteFilter::CheckMatches(cFilterTarget* target) {
  if (target)
    return target->Matches(MakeFilterKey(mpB, mpA));
  return false;
}

// @ 0x005C6730
bool cPaletteFilter::CheckRejected(cFilterTarget* target) {
  return !NotRejected(target);
}

// ---------------------------------------------------------------------------------------------
// 0x5c66a0: constructor of a refcounted object with a second interface at +8
class IPaletteListener : public EA::COM::IUnknown32 {
 public:
  virtual void OnEvent();
};

class cPaletteObject66a0 : public EA::RefCountVTemplate<int>, public IPaletteListener {
 public:
  cPaletteObject66a0();
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual void OnEvent();
  int mField0c, mField10, mField14, mField18, mField1c, mField20;
  int mIndex;  // +0x24
  int mField28, mField2c, mField30, mField34, mField38, mField3c, mField40, mField44, mField48;
  bool mbFlag4c;  // +0x4c
  int mField50;   // +0x50
};

// @ 0x005C66A0
cPaletteObject66a0::cPaletteObject66a0()
    : mField0c(0), mField10(0), mField14(0), mField18(0), mField1c(0), mField20(0), mIndex(-1),
      mField28(0), mField2c(0), mField30(0), mField34(0), mField38(0), mField3c(0), mField40(0),
      mField44(0), mField48(0), mbFlag4c(false), mField50(0) {}

// ---------------------------------------------------------------------------------------------
struct cTargetInner {
  PV(0) PV(1) PV(2)
  virtual void* Cast(uint32_t typeID);  // +0xc
};
struct cItemTarget {
  uint32_t pad[2];
  cTargetInner mInner;  // +0x8
};

class cISPPaletteItemUI {
 public:
  enum eItemUIInterfaceID { kItemUIUnknown = -1 };
  cISPPaletteItemUI() : mInterfaceID(kItemUIUnknown) {}
  virtual ~cISPPaletteItemUI() {}
  virtual void Init(cSPPaletteItem* item, IWindow* window, int a, int b) = 0;  // +0x4
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

  AutoRefCount<cSPPaletteItem> mPaletteItem;  // +0x4
  eItemUIInterfaceID mInterfaceID;            // +0x8
};

class cSPPaletteItemUI : public cISPPaletteItemUI, public IWinProc, public EA::RefCountVTemplate<int> {
 public:
  cSPPaletteItemUI();
  ~cSPPaletteItemUI();
  virtual void Init(cSPPaletteItem* item, IWindow* window, int a, int b);
  virtual void Shutdown();
  virtual void OnRollover();
  virtual void OffRollover();
  void Trigger();
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual bool DoMessage(IWindow* window, const Message& message);

  bool mIsRolledOver;               // +0x18
  AutoRefCount<IWindow> mWinRoot;   // +0x1c
};

// @ 0x005C6BF0
cSPPaletteItemUI::cSPPaletteItemUI() : mIsRolledOver(false) {}

// @ 0x005C6A30
void* cSPPaletteItemUI::Cast(uint32_t typeID) const {
  switch ((int)typeID) {
    case 0x4785a3d:
    case 0x4784b27:
      return (cSPPaletteItemUI*)this;
    case (int)0xee3f516e:
    case 0x2f009dd0:
      return (IWinProc*)this;
  }
  return 0;
}

// @ 0x005C6CA0
void cSPPaletteItemUI::Init(cSPPaletteItem* item, IWindow* window, int, int) {
  mWinRoot = window;
  mWinRoot->AddWinProc(this);
  mPaletteItem = item;
}

// @ 0x005C6D20
void cSPPaletteItemUI::Shutdown() {
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

// @ 0x005C6D70
bool cSPPaletteItemUI::DoMessage(IWindow* window, const Message& message) {
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

struct RolloverMessage {
  RolloverMessage(uint32_t id) : mID(id) {}
  void SetSource(IWinProc* source) { mpSource = source; }
  IWinProc* mpSource;
  uint32_t mPad4;
  uint32_t mID;
  uint32_t mPadC;
};

// @ 0x005C6F00
void cSPPaletteItemUI::OnRollover() {
  RolloverMessage msg(0x522f9cd);
  msg.SetSource(this);
  MessageServer()->MessageSend(msg.mID, &msg, 0);
}

// @ 0x005C6F40
void cSPPaletteItemUI::OffRollover() {
  RolloverMessage msg(0x522f9ce);
  msg.SetSource(this);
  MessageServer()->MessageSend(msg.mID, &msg, 0);
}

class IMessageBase {
 public:
  virtual ~IMessageBase() {}
};
class IMessageBase2 {
 public:
  IMessageBase2() : mRefCount(0) {}
  virtual void f();
  int mRefCount;  // +0x8
};
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
  AutoRefCount<EA::COM::IUnknown32> mpTarget;  // +0x20
  AutoRefCount<EA::COM::IUnknown32> mpExtra;   // +0x24
};

// @ 0x005C73D0
void cSPPaletteItemUI::Trigger() {
  cPaletteItemMessage msg(0xb2e18705, mInterfaceID);
  cItemTarget* target = GetTarget();
  msg.mpTarget = target ? (EA::COM::IUnknown32*)target->mInner.Cast(0xee3f516e) : 0;
  MessageServer()->MessageSend(msg.mID, &msg, 0);
}

class cSPPaletteItemUISelectable : public cSPPaletteItemUI, public EA::Messaging::IHandlerRC {
 public:
  cSPPaletteItemUISelectable();
  virtual void Init(cSPPaletteItem* item, IWindow* window, int a, int b, uint32_t selectionGroup);
  virtual void Shutdown();
  virtual void* Cast(uint32_t typeID) const;
  virtual void SetIsSelected(bool selected);
  virtual bool HandleMessage(uint32_t messageID, void* message);
  virtual int AddRef();
  virtual int Release();

  bool mSelected;             // +0x24
  uint32_t mSelectionGroup;   // +0x28
};

// @ 0x005C74A0
cSPPaletteItemUISelectable::cSPPaletteItemUISelectable() : mSelected(false), mSelectionGroup(0) {}

// @ 0x005C6A70
void* cSPPaletteItemUISelectable::Cast(uint32_t typeID) const {
  if (typeID == 0x47a9a1c)
    return (cSPPaletteItemUISelectable*)this;
  return cSPPaletteItemUI::Cast(typeID);
}

// @ 0x005C6AD0
void cSPPaletteItemUISelectable::SetIsSelected(bool selected) {
  if (selected) {
    MessageServer()->MessageSend(0x47a9a20, this, 0);
  } else if (mSelected) {
    mSelected = false;
    Deselect();
  }
}

// @ 0x005C6B10
bool cSPPaletteItemUISelectable::HandleMessage(uint32_t messageID, void* message) {
  if (messageID == 0x47a9a20) {
    cSPPaletteItemUISelectable* sender = (cSPPaletteItemUISelectable*)message;
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

// @ 0x005C6F80
void cSPPaletteItemUISelectable::Init(cSPPaletteItem* item, IWindow* window, int a, int b,
                                      uint32_t selectionGroup) {
  mSelectionGroup = selectionGroup;
  MessageServer()->AddHandler(this, 0x47a9a20);
  cSPPaletteItemUI::Init(item, window, a, b);
}

// @ 0x005C6FD0
void cSPPaletteItemUISelectable::Shutdown() {
  MessageServer()->RemoveHandler(this, 0x47a9a20, -9999);
  cSPPaletteItemUI::Shutdown();
}

// @ 0x005C6C50
cSPPaletteItemUI::~cSPPaletteItemUI() {}
// @ 0x005C7370  cSPPaletteItemUI scalar deleting dtor (compiler-generated ??_G)

// ---------------------------------------------------------------------------------------------
// rollover tooltip for a palette item
class cSPEditorVehicleAbilities {
 public:
  cSPEditorVehicleAbilities(Key key, uint32_t modelType, uint32_t layoutID, int a, bool b);  // 0x0059f030
  virtual ~cSPEditorVehicleAbilities();
  virtual int AddRef();
  virtual int Release();
  uint32_t mData[24];
};

class cSPUIPropertyLayout {
 public:
  void SetItem(cSPPaletteItem* item, cSPPalette* palette, cSPEditorVehicleAbilities* content, bool show);  // 0x005ee480
  void SetMode(int mode);                                           // 0x005ed320
  void SetPositionAndOffset(float x, float y, float dx, float dy);  // 0x008283a0
  void Hide();                                                      // 0x005ed6c0
  void Remove(EA::COM::IUnknown32* obj);                            // 0x005f0a60
};
class cEditorUI {
 public:
  cSPUIPropertyLayout* GetPropertyLayout();  // 0x0113ae10
  void RemoveContent(EA::COM::IUnknown32* obj);  // 0x005f0a60
};
cEditorUI* GetEditorUI();  // 0x00401020

class cSPPaletteItemRollover : public EA::RefCountVTemplate<int>, public IWinProc {
 public:
  cSPPaletteItemRollover();
  ~cSPPaletteItemRollover();
  virtual int AddRef();
  virtual int Release();
  PV(3)
  virtual void OnRollover();   // +0x10
  virtual void OffRollover();  // +0x14
  void Shutdown();
  virtual void* Cast(uint32_t typeID) const;
  virtual bool DoMessage(IWindow* window, const Message& message);

  AutoRefCount<cSPPaletteItem> mpItem;          // +0xc
  AutoRefCount<cSPPalette> mpPalette;           // +0x10
  AutoRefCount<EA::COM::IUnknown32> mpContent;  // +0x14
  AutoRefCount<IWindow> mpWindow;               // +0x18
  bool mIsRolledOver;                           // +0x1c
};

// @ 0x005C7010
cSPPaletteItemRollover::cSPPaletteItemRollover() : mIsRolledOver(false) {}

// @ 0x005C6BA0
void cSPPaletteItemRollover::OffRollover() {
  cSPUIPropertyLayout* layout = GetEditorUI()->GetPropertyLayout();
  if (layout)
    layout->Hide();
}

// @ 0x005C70D0
void cSPPaletteItemRollover::OnRollover() {
  cSPUIPropertyLayout* layout = GetEditorUI()->GetPropertyLayout();
  if (layout && mpWindow) {
    AutoRefCount<cSPEditorVehicleAbilities> content(
        new ("Editor", 0, 0, 0, 0) cSPEditorVehicleAbilities(mpItem->mItemKey, mpPalette->mModelType,
                                                              0x14880158, 0, true));
    layout->SetItem(mpItem, mpPalette, content, true);
    layout->SetMode(2);
    RectT screen = WindowManager()->GetMainWindow()->GetRealArea();
    RectT area = mpWindow->GetArea();
    layout->SetPositionAndOffset((area.left + area.right) * 0.5f, (area.top + area.bottom) * 0.5f,
                                 (screen.right - screen.left) * 0.05f, (screen.bottom - screen.top) * 0.0f);
  }
}

// @ 0x005C7260
bool cSPPaletteItemRollover::DoMessage(IWindow* window, const Message& message) {
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

// @ 0x005C7320
void cSPPaletteItemRollover::Shutdown() {
  if (mpContent) {
    GetEditorUI()->RemoveContent(mpContent);
    mpContent.AsOutParam();
  }
  if (mpWindow)
    mpWindow->RemoveWinProc(this);
}

// @ 0x005C7050
cSPPaletteItemRollover::~cSPPaletteItemRollover() {}

// ---------------------------------------------------------------------------------------------
class cPaletteWidget {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void Refresh();             // +0x14
  PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual void SetVisible(bool v);    // +0x34
  void Show();
};

// @ 0x005C6AB0
void cPaletteWidget::Show() {
  SetVisible(true);
  Refresh();
}
}  // namespace SP
