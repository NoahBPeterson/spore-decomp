// slice s005fe1d0 - SP::cSPUICredits (retail layout), two small modal UI dialogs (a two-choice
// dialog and a popup-menu dialog), an ID-collecting message listener, and EA::Stopwatch helpers.
// Flags: /O2 /MD /Gy /TP /GS- (EA::Stopwatch::GetElapsedTimeFloat: add /fp:fast)
#include "types.h"
#include <string.h>
#include <intrin.h>

#define PV(n) virtual void _pv##n();
#define PV10(n) PV(n##0) PV(n##1) PV(n##2) PV(n##3) PV(n##4) PV(n##5) PV(n##6) PV(n##7) PV(n##8) PV(n##9)

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);
inline void* operator new(size_t, void* p) throw() { return p; }

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* lpPerformanceCount);

namespace EA {
namespace ResourceMan {
struct Key {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
  Key() : instanceID(0), typeID(0), groupID(0) {}
  Key(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
}  // namespace ResourceMan

template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  ~AutoRefCount() {
    if (mpObject) mpObject->Release();
  }
  AutoRefCount& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  // @ 0x005fe320 (AutoRefCount<cPropertyList>::Reset, emitted out of line)
  void Reset() {
    if (mpObject) {
      T* const pTemp = mpObject;
      mpObject = 0;
      pTemp->Release();
    }
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};

class Stopwatch {
 public:
  uint64_t mnStartTime;                          // +0x00
  uint64_t mnTotalElapsedTime;                   // +0x08
  int mnUnits;                                   // +0x10
  float mfStopwatchCyclesToUnitsCoefficient;     // +0x14
  int64_t GetElapsedTimeCycles() const;          // 0x0093a3a0
  float GetElapsedTimeFloat() const;
  static uint64_t GetStopwatchCycle() {
    int64_t t;
    QueryPerformanceCounter(&t);
    return (uint64_t)t;
  }
};

class LimitStopwatch : public Stopwatch {
 public:
  uint64_t mnEndTime;  // +0x18
  bool IsTimeUp() const;
};

// @ 0x005ff1a0
float Stopwatch::GetElapsedTimeFloat() const { return (float)GetElapsedTimeCycles() * mfStopwatchCyclesToUnitsCoefficient; }

// @ 0x005ff1c0
bool LimitStopwatch::IsTimeUp() const {
  const uint64_t t = GetStopwatchCycle();
  return ((int64_t)(mnEndTime - t) < 0);
}

struct AtomicInt32 {
  int mValue;
  int Decrement() { return _InterlockedExchangeAdd((long*)&mValue, -1) - 1; }
  int Increment() { return _InterlockedExchangeAdd((long*)&mValue, 1) + 1; }
  int GetValue() { return _InterlockedExchangeAdd((long*)&mValue, 0); }
};

class IRefCounted {
 public:
  virtual int AddRef();
  virtual int Release();
};

namespace Messaging {
class IHandler {
 public:
  virtual ~IHandler() {}
  virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
};
void RemoveHandler(void* pServer, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x00571db0
}  // namespace Messaging

template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mnRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mnRefCount;
};

namespace UTFWin {
struct Message {
  class IWindow* source;   // +0x00
  uint32_t pad04;
  uint32_t eventType;      // +0x08
  uint32_t param0C;        // +0x0c (button: control ID)
  uint32_t param10;        // +0x10 (key: virtual key)
  uint32_t param14;        // +0x14 (key: modifiers)
};

class IWinProc;

class IWindow {
 public:
  PV(0) PV(1) PV(2)
  virtual void* Cast(uint32_t typeID);              // +0x0c
  virtual IWindow* GetParent();                     // +0x10
  PV(5) PV(6)
  virtual uint32_t GetControlID();                  // +0x1c
  PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual void* GetArea();                          // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(uint32_t flag, bool value);  // +0x7c
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV10(4)
  PV(50) PV(51) PV(52) PV(53)
  virtual void AddWindow(IWindow* pWindow);         // +0xd8
  PV(55) PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc* pWinProc);      // +0x104
  virtual void RemoveWinProc(IWinProc* pWinProc);   // +0x108
};

class IButton {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual uint32_t GetButtonStateFlags();                  // +0x20
  PV(9)
  virtual void SetButtonStateFlag(uint32_t flag, bool v);  // +0x28
};

class ITextWin {
 public:
  PV10(0) PV10(1) PV(20) PV(21) PV(22) PV(23)
  virtual void SetText(const wchar_t* text, int flags);  // +0x60
};

class IWindowManager {
 public:
  PV(0)
  virtual IWindow* GetMainWindow();                // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV10(1) PV10(2)
  PV(30) PV(31)
  virtual bool IsModal(IWindow* pWindow);          // +0x80
};

class IWinProc {
 public:
  virtual ~IWinProc() {}
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual uint32_t GetEventFlags() const = 0;
  virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) = 0;
};
}  // namespace UTFWin
}  // namespace EA

using EA::ResourceMan::Key;
using EA::UTFWin::IWindow;

// shared UI pieces
class cSPUILayout {
 public:
  virtual ~cSPUILayout();
  virtual int AddRef();
  virtual int Release();
  cSPUILayout();                                                    // 0x00810000
  bool Init(const Key& key, bool bVisible, uint32_t parentID);      // 0x008120d0
  void SetReloadCallback(void (*pFn)(void*, uint32_t, bool), void* pData);  // 0x00810090
  void SetParentWin(IWindow* pParent, bool b, uint32_t id);         // 0x008121b0
  IWindow* FindWindowByID(uint32_t id, bool recursive);             // 0x008105b0
  void Shutdown(bool b);                                            // 0x00811ad0
  uint32_t pad[5];
};

class cSPUILayoutManager {
 public:
  IWindow* GetWorldMainWindow(uint32_t id);  // 0x00810620
};

class cSPUIPopupMenuWin {
 public:
  virtual int AddRef();
  virtual int Release();
  int AddMenuItem(const Key& icon, int flags, const wchar_t* text, int data);  // 0x0081b6a0
  void OnMenuItemSelected(int a, int index);                                  // 0x0081bef0
  void RemoveAllItems();                                                      // 0x0081cce0
  uint32_t pad04[0x22a];
  int mSelectedIndex;  // +0x8ac
};

namespace SPUIHelpers {
cSPUILayoutManager* GetLayoutManager();                                                // 0x00805070
void AnchorWindowToWindow(IWindow* anchor, IWindow* window, uint32_t flags, int a);    // 0x00807340
void BeginModal(IWindow* window, void* callback, int a);                              // 0x008099a0
void EndModal(IWindow* window, uint32_t result, int a);                               // 0x00809c50
void* GetImageFromLayout(cSPUILayout* layout, uint32_t id);                           // 0x008061c0
void SetWindowImage(IWindow* window, void* image, int a);                             // 0x008068d0
void AutoSizeWindowForText(IWindow* window, int a, int b);                            // 0x00806e40
void FitWindowToArea(IWindow* window, void* area);                                    // 0x00806d10
}  // namespace SPUIHelpers

namespace SP {
EA::UTFWin::IWindowManager* WindowManager();  // 0x0067caa0
}

inline bool IsButtonDown(IWindow* window) {
  if (window) {
    EA::UTFWin::IButton* button = (EA::UTFWin::IButton*)window->Cast(0x8ed27e7a);
    if (button && (button->GetButtonStateFlags() & 4)) return true;
  }
  return false;
}

namespace eastl {
extern wchar_t gEmptyString16[2];

struct allocator {};

class string16 {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  allocator mAllocator;
  string16() {
    mpBegin = gEmptyString16;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  ~string16() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin) operator delete[](mpBegin);
  }
  const wchar_t* c_str() const { return mpBegin; }
  string16& operator=(const wchar_t* p);                  // 0x005c3d90
  string16& assign(const wchar_t* pBegin, const wchar_t* pEnd);  // 0x00423650
  string16& assign(const wchar_t* p) { return assign(p, p + CharStrlen(p)); }
  int sprintf(const wchar_t* pFormat, ...);               // 0x0041e050
  static size_t CharStrlen(const wchar_t* p) {
    const wchar_t* pCurrent = p;
    while (*pCurrent) ++pCurrent;
    return (size_t)(pCurrent - p);
  }
};

struct sp_vector_allocator {
  const char* mpName;
  uint32_t mFlags;
};

template <typename T>
class vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator mAllocator;
  T* erase(T* first, T* last) {
    memcpy(first, last, (size_t)((char*)mpEnd - (char*)last));
    mpEnd -= (last - first);
    return first;
  }
  void clear() { erase(mpBegin, mpEnd); }
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
  void DoInsertValue(T* position, const T& value);  // 0x004558a0
};
}  // namespace eastl

namespace SP {
class cString {  // localized string
 public:
  cString();                                                // 0x006b5060
  ~cString();                                               // 0x006b5240
  void SetText(uint32_t tableID, uint32_t instanceID, int a);  // 0x006b54b0
  const wchar_t* GetText();                                 // 0x006b55c0
  uint32_t mData[5];
};

struct cStringKey {  // table/instance pair with an inline text buffer
  uint32_t mTableID;
  uint32_t mInstanceID;
  wchar_t mBuffer[256];
  cStringKey() : mTableID(0xffffffff), mInstanceID(0xffffffff) { mBuffer[0] = 0; }
};
void LookupLocalizedString(const cStringKey& key, cString& out);  // 0x006b56d0

struct cLocalizedEntry {  // 12-byte localized string reference
  uint32_t mInstanceID;
  uint32_t mUnknown04;
  uint32_t mTableID;
};

struct Property {
  uint32_t pad00[4];
  uint16_t pad10;
  int16_t mnType;  // +0x12
  uint32_t* GetValueUInt32();  // 0x0041ea00
};

class cPropertyList {
 public:
  PV(0)
  virtual int Release();  // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property*& pOut);  // +0x24
  int AddRef();
};

class cPropertyManager {
 public:
  PV10(0) PV(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, EA::AutoRefCount<cPropertyList>& pOut);  // +0x2c
};
cPropertyManager* PropertyManager();  // 0x0067de30
bool GetPropertyAsKey(cPropertyList* list, uint32_t id, Key* pOut);                  // 0x006a1250
bool GetPropertyAsText(cPropertyList* list, uint32_t id, cString* pOut);             // 0x006a1360
bool GetPropertyArrayText(cPropertyList* list, uint32_t id, int* pCount, cLocalizedEntry** pArray);  // 0x006a0ae0

inline bool GetPropertyUInt32(cPropertyList* list, uint32_t id, uint32_t& value) {
  Property* prop;
  if (list && list->GetProperty(id, prop) && prop->mnType == 10) {
    value = *prop->GetValueUInt32();
    return true;
  }
  return false;
}

class cSPUICredits {
 public:
  EA::AutoRefCount<cPropertyList> mCreditNamesProperties;  // +0x00
  int mNumCreditNames;                                     // +0x04
  cLocalizedEntry* mCreditNames;                           // +0x08
  eastl::string16 mReturnString;                           // +0x0c
  uint32_t mScrollSpeed;                                   // +0x1c
  uint32_t mPropertyID;                                    // +0x20
  Key mBackgroundKey;                                      // +0x24
  Key mMusicKey;                                           // +0x30
  cString mTitle;                                          // +0x3c
  uint32_t mLineSpacing;                                   // +0x50
  uint32_t mFadeTime;                                      // +0x54

  cSPUICredits();
  ~cSPUICredits();
  void LoadNamesFromProp();
  void SetPropertyID(uint32_t id);
  uint32_t GetCreditNameTable(uint16_t index);
  const wchar_t* GetCreditName(uint16_t index);
};

// @ 0x005fe470
cSPUICredits::cSPUICredits() : mNumCreditNames(0), mCreditNames(0) {}

// @ 0x005fe4b0
cSPUICredits::~cSPUICredits() {}

// @ 0x005fe340
void cSPUICredits::LoadNamesFromProp() {
  mCreditNamesProperties.Reset();
  mCreditNames = 0;
  cPropertyManager* pm = PropertyManager();
  mCreditNamesProperties.Reset();
  pm->GetPropertyList(mPropertyID, 0x9a76ea1a, mCreditNamesProperties);
  GetPropertyUInt32(mCreditNamesProperties, 0x77384c4, mScrollSpeed);
  GetPropertyUInt32(mCreditNamesProperties, 0x7bfe364, mLineSpacing);
  GetPropertyUInt32(mCreditNamesProperties, 0x7bfe376, mFadeTime);
  GetPropertyAsKey(mCreditNamesProperties, 0x774b42e, &mBackgroundKey);
  GetPropertyAsKey(mCreditNamesProperties, 0x7a2cc3d, &mMusicKey);
  GetPropertyAsText(mCreditNamesProperties, 0x7a55691, &mTitle);
  GetPropertyArrayText(mCreditNamesProperties, 0x463d294, &mNumCreditNames, &mCreditNames);
}

// @ 0x005fe4f0
void cSPUICredits::SetPropertyID(uint32_t id) {
  mPropertyID = id;
  LoadNamesFromProp();
}

// @ 0x005fe300
uint32_t cSPUICredits::GetCreditNameTable(uint16_t index) {
  if (mCreditNames) return mCreditNames[index].mTableID;
  return 0;
}


// @ 0x005fe500
const wchar_t* cSPUICredits::GetCreditName(uint16_t index) {
  cString unused;
  if (mCreditNames) {
    cString text;
    const uint32_t tableID = mCreditNames[index].mTableID;
    if (tableID == 0)
      mReturnString.assign(L" ");
    else if (tableID == 1 || (tableID == 0xabe0cc37 && mCreditNames[index].mInstanceID == 0))
      mReturnString = L" ";
    else {
      cStringKey key;
      key.mTableID = mCreditNames[index].mTableID;
      key.mInstanceID = mCreditNames[index].mInstanceID;
      LookupLocalizedString(key, text);
      mReturnString = text.GetText();
    }
  }
  return mReturnString.c_str();
}
}  // namespace SP

// ---------------------------------------------------------------------------
// listener that collects message IDs (IHandler at +8)
class IAppComponent {
 public:
  virtual void _c0();
};
class IAppComponent2 {
 public:
  virtual void _d0();
};

class cSPUIIDCollector : public IAppComponent, public IAppComponent2, public EA::Messaging::IHandler {
 public:
  uint32_t mUnknown0C;                              // +0x0c
  void* mpMessageServer;                            // +0x10
  uint32_t mHandlerInfo[4];                         // +0x14
  uint32_t mUnknown24[3];                           // +0x24
  eastl::vector<uint32_t> mIDs;                     // +0x30
  cSPUILayout* mpLayout;                            // +0x44
  struct SharedState {
    uint32_t pad[2];
    EA::AtomicInt32 mRefCount;                      // +0x08
  }* mpSharedState;                                 // +0x48
  uint32_t mUnknown4C[3];                           // +0x4c
  EA::AutoRefCount<EA::IRefCounted> mpWinProc0;     // +0x58
  EA::AutoRefCount<EA::IRefCounted> mpWinProc1;     // +0x5c
  EA::AutoRefCount<EA::IRefCounted> mpWinProc2;     // +0x60

  void Shutdown();
  virtual bool HandleMessage(uint32_t messageID, void* pMessage);
};

// @ 0x005fe1d0
void cSPUIIDCollector::Shutdown() {
  mIDs.clear();
  if (mpMessageServer) {
    void* const pServer = mpMessageServer;
    mpMessageServer = 0;
    EA::Messaging::RemoveHandler(pServer, mHandlerInfo[0], mHandlerInfo[1], mHandlerInfo[2], mHandlerInfo[3]);
  }
  mpWinProc0.Reset();
  mpWinProc1.Reset();
  mpWinProc2.Reset();
  if (mpSharedState) {
    SharedState* const pState = mpSharedState;
    mpSharedState = 0;
    pState->mRefCount.Decrement();
    if (pState->mRefCount.GetValue() < 1)
      pState->mRefCount.Increment();
    else
      pState->mRefCount.GetValue();
  }
  if (mpLayout) {
    mpLayout->Shutdown(true);
    delete mpLayout;
    mpLayout = 0;
  }
}

// @ 0x005fe2b0
bool cSPUIIDCollector::HandleMessage(uint32_t messageID, void* pMessage) {
  if (messageID != 0x5c6930e) return false;
  mIDs.push_back(*(uint32_t*)pMessage);
  return true;
}

// ---------------------------------------------------------------------------
// two-choice modal dialog
class cSPUIChoiceDialog : public EA::UTFWin::IWinProc, public EA::RefCountVTemplate<int> {
 public:
  EA::AutoRefCount<cSPUILayout> mpLayout;  // +0x0c
  bool mbActive;                           // +0x10
  bool mbCancelled;                        // +0x11
  int mFirstChoice;                        // +0x14
  int mSecondChoice;                       // +0x18
  void* mpModalCallback;                   // +0x1c

  cSPUIChoiceDialog(void* pModalCallback);
  virtual int AddRef();
  virtual int Release();
  virtual uint32_t GetEventFlags() const;
  virtual bool HandleUIMessage(IWindow* pWindow, const EA::UTFWin::Message& message);

  void Close();
  void Show();
  bool IsButtonChecked(uint32_t id);
  void Accept();
  void Cancel() {
    mbActive = false;
    mbCancelled = true;
    Close();
  }
  void Init(uint32_t imageID, bool bShowExtra);
  static void OnLayoutReload(void* pData, uint32_t, bool bLoaded);
};

// @ 0x005fe600
cSPUIChoiceDialog::cSPUIChoiceDialog(void* pModalCallback)
    : mbActive(false), mbCancelled(false), mFirstChoice(-1), mSecondChoice(-1), mpModalCallback(pModalCallback) {}

// @ 0x005fe650
void cSPUIChoiceDialog::Close() {
  if (mpLayout) {
    IWindow* window = mpLayout->FindWindowByID(0x61b2daa, true);
    if (window && SP::WindowManager()->IsModal(window)) {
      window->SetFlag(1, false);
      SPUIHelpers::EndModal(window, 0, 0);
    }
    mpLayout->Shutdown(true);
    mpLayout.Reset();
  }
  mbActive = false;
}

// @ 0x005fe6c0
void cSPUIChoiceDialog::Show() {
  mbActive = true;
  mbCancelled = false;
  mFirstChoice = -1;
  mSecondChoice = -1;
  if (IWindow* window = mpLayout->FindWindowByID(0x61b5e4e, true)) {
    if (EA::UTFWin::IButton* button = (EA::UTFWin::IButton*)window->Cast(0x8ed27e7a)) button->SetButtonStateFlag(4, true);
  }
  if (IWindow* window = mpLayout->FindWindowByID(0x61f3ce5, true)) {
    if (EA::UTFWin::IButton* button = (EA::UTFWin::IButton*)window->Cast(0x8ed27e7a)) button->SetButtonStateFlag(4, true);
  }
  if (IWindow* window = mpLayout->FindWindowByID(0x61b2daa, true)) SPUIHelpers::BeginModal(window, mpModalCallback, 0);
}

// @ 0x005fe760
bool cSPUIChoiceDialog::IsButtonChecked(uint32_t id) { return IsButtonDown(mpLayout->FindWindowByID(id, true)); }

// @ 0x005fe7a0
void cSPUIChoiceDialog::Accept() {
  mbActive = false;
  mbCancelled = false;
  if (IsButtonDown(mpLayout->FindWindowByID(0x61b5e4d, true)))
    mFirstChoice = 0;
  else if (IsButtonDown(mpLayout->FindWindowByID(0x61b5e4e, true)))
    mFirstChoice = 1;
  else if (IsButtonChecked(0x61b5e4f))
    mFirstChoice = 2;

  if (IsButtonDown(mpLayout->FindWindowByID(0x61f3ce5, true)))
    mSecondChoice = 0;
  else if (IsButtonDown(mpLayout->FindWindowByID(0x61f3ce6, true)))
    mSecondChoice = 2;
  else if (IsButtonChecked(0x61f3ce7))
    mSecondChoice = 1;
  Close();
}

// @ 0x005fe8e0
bool cSPUIChoiceDialog::HandleUIMessage(IWindow* pWindow, const EA::UTFWin::Message& message) {
  if (mpLayout) {
    switch (message.eventType) {
      case 1:
        if (!(message.param14 & 0x47)) {
          if (message.param10 == 0xd) Accept();
          if (message.param10 == 0x1b) Cancel();
        }
        return true;
      case 0x287259f6:
        if (message.param0C == 0x61c282f) {
          Cancel();
          return true;
        }
        if (message.param0C == 0x61c282e) Accept();
        return true;
      case 2:
      case 5:
        return true;
    }
  }
  return false;
}

// @ 0x005fe970
void cSPUIChoiceDialog::OnLayoutReload(void* pData, uint32_t, bool bLoaded) {
  cSPUIChoiceDialog* self = (cSPUIChoiceDialog*)pData;
  if (!bLoaded) {
    if (self->mpLayout) {
      if (IWindow* window = self->mpLayout->FindWindowByID(0x61b2daa, true)) window->RemoveWinProc(self);
    }
  } else {
    IWindow* parent = SPUIHelpers::GetLayoutManager()->GetWorldMainWindow(0x5b598f7);
    self->mpLayout->SetParentWin(parent, true, 0x5b598fa);
    if (IWindow* window = self->mpLayout->FindWindowByID(0x61b2daa, true)) {
      window->AddWinProc(self);
      SPUIHelpers::AnchorWindowToWindow(parent, window, 0x300, 0);
    }
  }
}

// @ 0x005fea60
void cSPUIChoiceDialog::Init(uint32_t imageID, bool bShowExtra) {
  mpLayout = new ("UI", 0, 0, 0, 0) cSPUILayout();
  const Key key(0x90a57bfa, 0x510a95b, 0x40464100);
  mpLayout->Init(key, true, 0x5b598fa);
  mpLayout->SetReloadCallback(OnLayoutReload, this);
  IWindow* parent = SPUIHelpers::GetLayoutManager()->GetWorldMainWindow(0x5b598f7);
  mpLayout->SetParentWin(parent, true, 0x5b598fa);
  if (IWindow* window = mpLayout->FindWindowByID(0x61b2daa, true)) {
    window->AddWinProc(this);
    SPUIHelpers::AnchorWindowToWindow(parent, window, 0x300, 0);
  }
  if (IWindow* window = mpLayout->FindWindowByID(0x61f3c8b, true)) window->SetFlag(1, bShowExtra);
  if (imageID) {
    if (IWindow* window = mpLayout->FindWindowByID(0x62e9622, true)) {
      void* image = SPUIHelpers::GetImageFromLayout(mpLayout, imageID);
      SPUIHelpers::SetWindowImage(window, image, -1);
    }
  }
}

// ---------------------------------------------------------------------------
// popup-menu modal dialog
extern const uint32_t kPopupLayoutType;  // 0x0151d5a4

class cSPUIPopupMenuDialog : public EA::UTFWin::IWinProc, public EA::RefCountVTemplate<int> {
 public:
  EA::AutoRefCount<cSPUILayout> mpLayout;        // +0x0c
  EA::AutoRefCount<cSPUIPopupMenuWin> mpMenu;    // +0x10
  uint32_t mResult;                              // +0x14
  int mItemCount;                                // +0x18
  SP::cString mTitle;                            // +0x1c
  void* mpModalCallback;                         // +0x30
  eastl::string16 mText;                         // +0x34

  cSPUIPopupMenuDialog();
  virtual ~cSPUIPopupMenuDialog();
  virtual int AddRef();
  virtual int Release();
  virtual uint32_t GetEventFlags() const;
  virtual bool HandleUIMessage(IWindow* pWindow, const EA::UTFWin::Message& message);

  bool Shutdown();
  bool Close();
  bool Show();
  int GetSelectedIndex();
  void SelectItem(int index);
  int AddItem(const wchar_t* text);
  bool Init(void* pModalCallback);
  void ClearItems();
  void SetText(const wchar_t* text);
};

// @ 0x005feff0
cSPUIPopupMenuDialog::cSPUIPopupMenuDialog() : mResult(0), mItemCount(0), mpModalCallback(0) {}

// @ 0x005ff050
cSPUIPopupMenuDialog::~cSPUIPopupMenuDialog() {}

// @ 0x005febf0
bool cSPUIPopupMenuDialog::Shutdown() {
  mpMenu.Reset();
  if (mpLayout) {
    mpLayout->Shutdown(true);
    mpLayout.Reset();
  }
  return true;
}

// @ 0x005fec30
bool cSPUIPopupMenuDialog::Close() {
  if (IWindow* window = mpLayout->FindWindowByID(0x40cf9b0, true)) {
    window->SetFlag(1, false);
    window->RemoveWinProc(this);
    if (SP::WindowManager()->IsModal(window)) SPUIHelpers::EndModal(window, mResult, 0);
  }
  return true;
}

// @ 0x005fec90
bool cSPUIPopupMenuDialog::Show() {
  mResult = 0;
  IWindow* window = mpLayout->FindWindowByID(0x40cf9b0, true);
  if (window) window->AddWinProc(this);
  EA::UTFWin::IWindowManager* wm = SP::WindowManager();
  if (window) {
    IWindow* parent = SPUIHelpers::GetLayoutManager()->GetWorldMainWindow(0x5b598f7);
    if (!window->GetParent()) parent->AddWindow(window);
    window->SetFlag(1, true);
    SPUIHelpers::AnchorWindowToWindow(wm->GetMainWindow(), window, 0x300, 0);
    SPUIHelpers::FitWindowToArea(window, wm->GetMainWindow()->GetArea());
    if (!wm->IsModal(window)) SPUIHelpers::BeginModal(window, mpModalCallback, 0);
  }
  return true;
}

// @ 0x005fed70
int cSPUIPopupMenuDialog::GetSelectedIndex() {
  if (mpMenu) return mpMenu->mSelectedIndex;
  return -1;
}

// @ 0x005fed90
void cSPUIPopupMenuDialog::SelectItem(int index) {
  if (mpMenu) mpMenu->OnMenuItemSelected(0, index);
}

// @ 0x005fedb0
int cSPUIPopupMenuDialog::AddItem(const wchar_t* text) {
  int result = 0;
  if (mpMenu) {
    const Key icon(0xa10d844a, 0x510a95b, 0x40464100);
    result = mpMenu->AddMenuItem(icon, 0, text, 0);
    ++mItemCount;
    if (IWindow* window = mpLayout->FindWindowByID(0x6163290, true)) window->SetFlag(2, true);
  }
  return result;
}

// @ 0x005fee20
bool cSPUIPopupMenuDialog::HandleUIMessage(IWindow* pWindow, const EA::UTFWin::Message& message) {
  switch (message.eventType) {
    case 1:
      if (!(message.param14 & 0x47) && (message.param10 == 0xd || message.param10 == 0x1b)) {
        mResult = 0x6163280;
        Close();
        return true;
      }
      return true;
    case 2:
    case 5:
      return true;
    case 0x287259f6: {
      const uint32_t id = message.source->GetControlID();
      switch (id) {
        case 0x6163280:
        case 0x6163290:
          mResult = id;
          Close();
          return true;
      }
      return false;
    }
  }
  return false;
}

// @ 0x005feea0
bool cSPUIPopupMenuDialog::Init(void* pModalCallback) {
  mpModalCallback = pModalCallback;
  mTitle.SetText(0x7c6511a1, 0x6162c22, 0);
  mpLayout = new ("Sporepedia", 0, 0, 0, 0) cSPUILayout();
  const Key key(0x2b47985b, 0x510a95b, kPopupLayoutType);
  if (mpLayout->Init(key, true, 0x5b598f7)) {
    IWindow* menuWindow = mpLayout->FindWindowByID(0x6849178, true);
    mpMenu = menuWindow ? (cSPUIPopupMenuWin*)menuWindow->Cast(0x4c058d5) : 0;
    IWindow* okButton = mpLayout->FindWindowByID(0x6163280, true);
    SPUIHelpers::AutoSizeWindowForText(okButton, 0, 0);
    IWindow* cancelButton = mpLayout->FindWindowByID(0x6163290, true);
    SPUIHelpers::AutoSizeWindowForText(cancelButton, 1, 0);
    Close();
    return true;
  }
  return false;
}

// @ 0x005ff0d0
void cSPUIPopupMenuDialog::ClearItems() {
  if (mpMenu) {
    mpMenu->RemoveAllItems();
    mItemCount = 0;
    if (IWindow* window = mpLayout->FindWindowByID(0x6163290, true)) window->SetFlag(2, false);
  }
  if (IWindow* window = mpLayout->FindWindowByID(0x6163256, true)) {
    if (EA::UTFWin::ITextWin* textWin = (EA::UTFWin::ITextWin*)window->Cast(0xcf428691)) {
      static eastl::string16 sEmpty;
      textWin->SetText(sEmpty.c_str(), 0);
    }
  }
}

// @ 0x005ff180
void cSPUIPopupMenuDialog::SetText(const wchar_t* text) { mText.sprintf(L"%ls", text); }
