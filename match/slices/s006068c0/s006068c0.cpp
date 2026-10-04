// Downloaded-content cleanup, the Pollen login dialogs (cConnectingDialog,
// cOfflineConfirmationDialog, cLoginHelpDialog) and SP::Pollen::cAuthManager, plus a few
// EASTL string helpers from the same module.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef unsigned int size_t;

#define PV(n) virtual void pv##n();

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);
inline void* operator new(size_t, void* p) { return p; }

extern "C" __declspec(dllimport) int __cdecl toupper(int c);
extern "C" __declspec(dllimport) int __cdecl tolower(int c);

struct ResourceKey {
  uint32_t mInstance;  // +0x0
  uint32_t mType;      // +0x4
  uint32_t mGroup;     // +0x8
  ResourceKey() : mInstance(0), mType(0), mGroup(0) {}
  ResourceKey(uint32_t i, uint32_t t, uint32_t g) : mInstance(i), mType(t), mGroup(g) {}
};

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
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};

namespace UTFWin {
struct Rect {
  float left, top, right, bottom;
};
class IWinProc;
class IWindow {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual uint32_t GetControlID();                       // +0x1c
  PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual const Rect& GetArea();                         // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27)
  virtual void SetLocation(float x, float y);            // +0x70
  PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);            // +0x7c
  virtual void SetCaption(const wchar_t* text);          // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
  PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
  virtual IWindow* FindWindowByID(uint32_t controlID, bool recursive);  // +0xf0
  PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc* proc);               // +0x104
  virtual void RemoveWinProc(IWinProc* proc);            // +0x108
};
class __declspec(novtable) IWinProc {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};
class ISerializable {
 public:
  virtual bool Serialize(void* stream);
};
class MultiHeapObject {};
class __declspec(novtable) CustomWinProc : public IWinProc, public ISerializable, public MultiHeapObject {
 public:
  CustomWinProc() : mRefCount(0) {}
  int mRefCount;  // +0x8
};
class IModalWindowCallback {
 public:
  virtual void OnModalWindowEnd(IWindow* window, uint32_t result);
};
}  // namespace UTFWin

namespace Messaging {
class IHandler {
 public:
  virtual bool HandleMessage(uint32_t messageID, void* message);
};
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMSG(uint32_t messageID, void* data, void* source);               // +0x14
  PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void RemoveHandler(IHandler* handler, uint32_t messageID, int priority);  // +0x2c
};
}  // namespace Messaging
}  // namespace EA

using EA::AutoRefCount;
using EA::UTFWin::IWindow;

class cSPUILayout {
 public:
  cSPUILayout();                                    // 0x810000
  virtual ~cSPUILayout();
  virtual int AddRef();
  virtual int Release();
  bool Init(const ResourceKey& key, bool b, uint32_t groupID);
  IWindow* FindWindowByID(uint32_t id, bool recursive);
  void Shutdown(bool b);
  uint32_t pad[2];
};

namespace SPUIHelpers {
void AutoSizeWindowForText(IWindow* window, int a, int b);
void BeginModal(IWindow* window, EA::UTFWin::IModalWindowCallback* callback, bool b);
void EndModal(IWindow* window, EA::UTFWin::IModalWindowCallback* callback, bool b);
float GetElapsedSeconds();
void SetWindowRotation(IWindow* window, const void* rotation);  // 0x808230
void ShowErrorDialog(int a, const void* key);                   // 0x809db0
}  // namespace SPUIHelpers

namespace eastl {
template <typename T>
class basic_string {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  uint32_t mAllocator;
  basic_string();
  ~basic_string() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin) operator delete[](mpBegin);
  }
  size_t size() const { return (size_t)(mpEnd - mpBegin); }
  bool empty() const { return mpBegin == mpEnd; }
  const T* c_str() const { return mpBegin; }
  void clear() {
    if (mpBegin != mpEnd) {
      *mpBegin = 0;
      mpEnd = mpBegin;
    }
  }
  void make_upper();
  size_t find(T c, size_t position) const;
};
extern wchar_t gEmptyString16[2];  // 0x01667BAC
template <> inline basic_string<wchar_t>::basic_string()
    : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}

inline wchar_t CharToUpper(wchar_t c) {
  if ((unsigned)c <= 0xff) return (wchar_t)toupper((unsigned char)c);
  return c;
}
// @ 0x606e60
template <typename T>
void basic_string<T>::make_upper() {
  for (T* p = mpBegin; p < mpEnd; ++p) *p = (T)CharToUpper(*p);
}
template void basic_string<wchar_t>::make_upper();

inline char CharToLower(char c) { return (char)tolower((unsigned char)c); }
// @ 0x606ea0
int CompareI(const char* p1, const char* p2, size_t n) {
  for (; n > 0; ++p1, ++p2, --n) {
    const char c1 = CharToLower(*p1);
    const char c2 = CharToLower(*p2);
    if (c1 != c2) return (c1 < c2) ? -1 : 1;
  }
  return 0;
}

// @ 0x607580
template <typename T>
size_t basic_string<T>::find(T c, size_t position) const {
  if (position < (size_t)(mpEnd - mpBegin)) {
    const T* p = mpBegin + position;
    for (; p != mpEnd; ++p)
      if (*p == c) break;
    if (p != mpEnd) return (size_t)(p - mpBegin);
  }
  return (size_t)-1;
}
template size_t basic_string<char>::find(char, size_t) const;

struct sp_vector_allocator {
  uint32_t mData[2];
  void deallocate(void* p, size_t) {
    if (((uint32_t*)p)[-1]) operator delete[](p);
  }
};
template <typename T>
class vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator mAllocator;
  vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~vector() {
    DoDestroyValues(mpBegin, mpEnd);
    if (mpBegin) mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
  }
  void DoDestroyValues(T* first, T* last) {
    for (; first < last; ++first) first->~T();
  }
  size_t size() const { return (size_t)(mpEnd - mpBegin); }
  T* DoInsertValue(T* position, const T& value);
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};
}  // namespace eastl

// ---------------------------------------------------------------------------
namespace SP {
EA::Messaging::IMessageServer* MessageServer();
class IConfigManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
  virtual int GetValue(uint32_t id);                                  // +0x30
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
  virtual void GetString(uint32_t id, eastl::basic_string<char>& s);  // +0x4c
};
IConfigManager* ConfigManager();

namespace FunctionalMatch {
struct Constraint {
  uint32_t mParameter;
  int mType;
  int mMin, mMax;
};
struct ConstraintNode {
  Constraint mConstraint;                   // +0x0
  eastl::vector<ConstraintNode> mChildren;  // +0x10
  ConstraintNode(uint32_t parameter, int unused, int min, int max);  // 0x5589c0
  ConstraintNode(const ConstraintNode& x);                            // 0x606880
};
}  // namespace FunctionalMatch
using FunctionalMatch::ConstraintNode;
}  // namespace SP
template <> void eastl::vector<SP::ConstraintNode>::DoDestroyValues(SP::ConstraintNode* first, SP::ConstraintNode* last);  // 0x4e39a0
namespace SP {

class IObjectTemplateDB {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual void FindObjects(eastl::vector<ResourceKey>& keys, const eastl::vector<ConstraintNode>& constraints);  // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
  virtual void DeleteObject(const ResourceKey* key);                                   // +0x5c
  PV(24)
  virtual void GetOldestObjects(int count, eastl::vector<ResourceKey>& keys, void* area);  // +0x64
  PV(26) PV(27) PV(28) PV(29)
  virtual void RemoveObject(const ResourceKey* key, int flags);                        // +0x78
};
IObjectTemplateDB* ObjectTemplateDB();

class cAssetFiles {
 public:
  void Load();                         // 0x550970
  uint32_t GetFileCount();             // 0x5508e0
  const wchar_t* GetFile(uint32_t i);  // 0x550910
};
void DeleteAssetFile(const wchar_t* path);  // 0x5419c0

class IDatabase {
 public:
  void GetTotalSize(uint64_t& size);  // 0x6bc370
};
class ISaveAreaInterface {
 public:
  PV(0) PV(1) PV(2)
  virtual IDatabase* Cast(uint32_t typeID);  // +0xc
};
struct cSaveArea {
  uint32_t pad0;
  ISaveAreaInterface mInterface;  // +0x4
};
cSaveArea* GetSaveArea(const void* id);  // 0x6b1f90

class cDirectPropertyList {
 public:
  int GetIntProperty(uint32_t id);  // 0x6a2660
  char pad[0x3c];
  struct Values {
    char pad[0x118];
    int mbGalacticAdventures;  // +0x118
  }* mpValues;                 // +0x3c
};
extern cDirectPropertyList* sAppProperties;  // 0x15fd918

class cPollinator {
 public:
  void SetEnabledState(uint32_t state);
};
cPollinator* Pollinator();  // 0x67cb30

class IXHTMLResources {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual void RemoveListener(void* listener);  // +0x20
};
class IXHTMLManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual IXHTMLResources* GetResources();  // +0x20
};
IXHTMLManager* XHTMLManager();  // 0x67de40
}  // namespace SP

void* GetResourceAs30bdee3(const ResourceKey& key);           // 0x606640
bool GetArchiveFolder(eastl::basic_string<wchar_t>& path);    // 0x606790
uint32_t FNVHash(const char* s, uint32_t seed, bool lower);  // 0x932e80

namespace EA {
namespace DateTime {
struct DateTime {
  int64_t mnSeconds;
  DateTime(int timeFrame);  // 0x92e3d0
};
}  // namespace DateTime
}  // namespace EA

using namespace SP;

// @ 0x6068c0
bool PurgeDownloadedContent() {
  if (ConfigManager()->GetValue(0x626f940) == 1) {
    int maxAgeDays = ConfigManager()->GetValue(0x626f958);
    bool archive = ConfigManager()->GetValue(0x626f9c0) == 1;
    EA::DateTime::DateTime now(1);
    int hours = (int)((uint64_t)(now.mnSeconds - 63334831376LL) / 3600);
    eastl::vector<ConstraintNode> constraints;
    constraints.push_back(ConstraintNode(0x61ef9b1, 0, (int)0x80000000, hours - maxAgeDays * 24));
    eastl::vector<ResourceKey> keys;
    ObjectTemplateDB()->FindObjects(keys, constraints);
    eastl::basic_string<wchar_t> archivePath;
    if (archive) GetArchiveFolder(archivePath);
    for (ResourceKey* key = keys.mpBegin, *end = keys.mpEnd; key != end; ++key) {
      cAssetFiles* files = (cAssetFiles*)GetResourceAs30bdee3(*key);
      files->Load();
      uint32_t count = files->GetFileCount();
      for (uint32_t i = 0; i < count; i++) DeleteAssetFile(files->GetFile(i));
      ObjectTemplateDB()->DeleteObject(key);
    }
  }
  cSaveArea* area = GetSaveArea((const void*)0x11ac19c);
  if (area) {
    IDatabase* db = area->mInterface.Cast(0x6492c5f);
    if (db) {
      uint64_t size;
      db->GetTotalSize(size);
      uint64_t maxSize = (int64_t)sAppProperties->GetIntProperty(0x685c490) * 0x100000;
      if (maxSize) {
        IObjectTemplateDB* otdb = ObjectTemplateDB();
        bool more;
        do {
          if (size <= maxSize) break;
          eastl::vector<ResourceKey> oldest;
          otdb->GetOldestObjects(100, oldest, area);
          for (ResourceKey* key = oldest.mpBegin; key != oldest.mpEnd; ++key) {
            if (size > maxSize) {
              ObjectTemplateDB()->RemoveObject(key, 0);
              db->GetTotalSize(size);
            }
          }
          more = oldest.size() == 100;
        } while (more);
      }
    }
  }
  return true;
}

// ---------------------------------------------------------------------------
namespace SP {
namespace Pollen {
namespace {
class cConnectingDialog : public EA::UTFWin::CustomWinProc {
 public:
  bool Init();
  void end_dialog(bool connected);
  void HandleResults(bool success);
  bool OnTick(int a);
  void Close() {
    SPUIHelpers::EndModal(mpWindow, 0, true);
    mpWindow->RemoveWinProc(this);
    mpWindow = 0;
    mLayout.Shutdown(true);
  }
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  AutoRefCount<IWindow> mpWindow;  // +0xc
  float mStartTime;                // +0x10
  float mTimeout;                  // +0x14
  bool mEndConnecting;             // +0x18
  bool mEndConnected;              // +0x19
  float mRotation[4];              // +0x1c
  cSPUILayout mLayout;             // +0x2c
};

class cOfflineConfirmationDialog : public EA::UTFWin::CustomWinProc {
 public:
  cOfflineConfirmationDialog();
  bool Init();
  void Show(EA::UTFWin::IModalWindowCallback* callback);
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  cSPUILayout mLayout;  // +0xc
};

class cLoginHelpDialog : public EA::UTFWin::CustomWinProc {
 public:
  cLoginHelpDialog();
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  bool IsReturnKey(void* a, void* b, int key, void* c);
  cSPUILayout mLayout;  // +0xc
};
}  // namespace

// @ 0x606c40
bool cConnectingDialog::Init() {
  if (mLayout.Init(ResourceKey(0x834b03af, 0x510a95b, 0x40464100), false, 0x5b598f7)) {
    IWindow* text = mLayout.FindWindowByID(0x50fb5d0, true);
    if (text) SPUIHelpers::AutoSizeWindowForText(text, 0, 0);
    IWindow* root = mLayout.FindWindowByID(0x431e538, true);
    if (root) {
      root->AddWinProc(this);
      return true;
    }
    mLayout.Shutdown(true);
  }
  return false;
}

// @ 0x606cd0
void cOfflineConfirmationDialog::Show(EA::UTFWin::IModalWindowCallback* callback) {
  IWindow* root = mLayout.FindWindowByID(0x50f92d8, true);
  if (root) SPUIHelpers::BeginModal(root, callback, true);
}

// @ 0x606f60
bool cLoginHelpDialog::IsReturnKey(void* a, void* b, int key, void* c) {
  if (key == 0xd) return true;
  return false;
}

// @ 0x606f80
void cConnectingDialog::end_dialog(bool connected) {
  SPUIHelpers::EndModal(mpWindow, 0, true);
  mpWindow->RemoveWinProc(this);
  mpWindow = 0;
  mLayout.Shutdown(true);
  MessageServer()->PostMSG(0x44db12e, (void*)(connected != 0), 0);
}

// @ 0x607050
bool cOfflineConfirmationDialog::Init() {
  if (mLayout.Init(ResourceKey(0xf69e2034, 0x510a95b, 0x40464100), true, 0x5b598f7)) {
    IWindow* message = mLayout.FindWindowByID(0x50fad88, true);
    if (message) {
      SPUIHelpers::AutoSizeWindowForText(message, 1, 0);
      IWindow* button = mLayout.FindWindowByID(0x50fb5d0, true);
      if (button) {
        SPUIHelpers::AutoSizeWindowForText(button, 0, 0);
        const EA::UTFWin::Rect* area = &button->GetArea();
        float width = area->right - area->left;
        float x = message->GetArea().left - width;
        button->SetLocation(x, area->top);
      }
    }
    IWindow* root = mLayout.FindWindowByID(0x50f92d8, true);
    if (root) {
      root->AddWinProc(this);
      return true;
    }
    mLayout.Shutdown(true);
  }
  return false;
}

// @ 0x6075c0
void cConnectingDialog::HandleResults(bool success) {
  if (success)
    mEndConnecting = true;
  else
    end_dialog(false);
}

class cString {
 public:
  cString(uint32_t instanceID, uint32_t groupID, const wchar_t* defaultText);  // 0x6b5770
  ~cString();                                                                  // 0x6b5240
  const wchar_t* c_str();                                                      // 0x6b55c0
  uint32_t pad[5];
};
bool IsFeatureEnabled(int feature);  // 0x685520

// @ 0x607630
bool cConnectingDialog::OnTick(int a) {
  if (mEndConnecting && SPUIHelpers::GetElapsedSeconds() - mStartTime > mTimeout) {
    if (!mEndConnected) {
      mEndConnected = true;
      mStartTime = SPUIHelpers::GetElapsedSeconds();
      mTimeout = 1.5f;
      cString text(0xb7bcef68, 0x662da01, L"Connected to Spore server");
      IWindow* w = mpWindow->FindWindowByID(0x5006000, true);
      if (w) w->SetCaption(text.c_str());
      w = mpWindow->FindWindowByID(0x42e2e38, true);
      if (w) w->SetFlag(1, false);
      w = mpWindow->FindWindowByID(0x5005f78, true);
      if (w) {
        SPUIHelpers::SetWindowRotation(w, mRotation);
        w->SetFlag(1, true);
      }
      if (IsFeatureEnabled(2)) {
        w = mpWindow->FindWindowByID(0x5d2bdf8, true);
        if (w) w->SetFlag(1, false);
      }
      MessageServer()->PostMSG(0x56bbd7f, 0, 0);
      return true;
    }
    end_dialog(true);
    return true;
  }
  if (!mEndConnected) {
    mRotation[3] = (SPUIHelpers::GetElapsedSeconds() - mStartTime) * -4.18879032f;
    SPUIHelpers::SetWindowRotation(mpWindow->FindWindowByID(0x43322c0, true), mRotation);
    MessageServer()->PostMSG(0x56bbd7f, mRotation, 0);
  }
  return true;
}

// @ 0x607450
cOfflineConfirmationDialog::cOfflineConfirmationDialog() {}

// @ 0x607480
cLoginHelpDialog::cLoginHelpDialog() {}

// ---------------------------------------------------------------------------
class cRegistrationDialog {
 public:
  cRegistrationDialog();  // 0x620740
  virtual int AddRef();
  virtual int Release();
  void Show(bool b);      // 0x6208c0
  char pad[0x6c - 4];
};

struct cAuthBase0c {
  virtual void v0c();
  uint32_t m10;
};
struct cAuthBase14 {
  virtual void v14();
  uint32_t m18;
};
class IAuthenticationService {
 public:
  virtual void Shutdown_();                     // slot 0
  virtual uint64_t GetUserServerID();           // slot 1
  virtual void SetLoginDialogVisible(bool visible);
  virtual void SetPlayOffline(bool offline);
  virtual void ShowLogin();
  virtual bool Shutdown();
  PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
  virtual void ShowLoginUI(bool b);             // +0x48
  virtual void Login();                         // +0x4c
  PV(20)
  virtual void CancelLogin();                   // +0x54
  virtual bool IsLoginUIAvailable();            // +0x58
};

class cAuthManager : public EA::UTFWin::IWinProc,
                     public EA::UTFWin::IModalWindowCallback,
                     public EA::Messaging::IHandler,
                     public cAuthBase0c,
                     public cAuthBase14,
                     public IAuthenticationService {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  void* AsInterface(uint32_t typeID);
  void EndLoginDialog();
  void SetOfflineUserID();
  void ShowLoginDialog(bool b);
  void InitialLogin();
  virtual void OnModalWindowEnd(IWindow* window, uint32_t result);
  virtual uint64_t GetUserServerID();
  virtual void SetLoginDialogVisible(bool visible);
  virtual void SetPlayOffline(bool offline);
  virtual void ShowLogin();
  virtual bool Shutdown();

  eastl::basic_string<char> mUser;        // +0x20
  eastl::basic_string<char> mPassword;    // +0x30
  eastl::basic_string<char> mScreenName;  // +0x40
  uint64_t mnUserServerID;                // +0x50
  uint32_t mnUserLocalID;                 // +0x58
  bool mbPlayOffline;                     // +0x5c
  bool mbPrompt;                          // +0x5d
  cSPUILayout* mpLoginLayout;             // +0x60
  bool mbDontSavePrefs;                   // +0x64
  int mDialogInProgress;                  // +0x68
  AutoRefCount<cRegistrationDialog> pReg; // +0x6c
};

// @ 0x606d00
void* cAuthManager::AsInterface(uint32_t typeID) {
  switch ((int)typeID) {
    case 0x40f7cee: return this;
    case 0x7201461:
    case (int)0xee3f516e: return static_cast<IAuthenticationService*>(this);
    case 0x2f009dd0: return this;
  }
  return 0;
}

// @ 0x606d70
uint64_t cAuthManager::GetUserServerID() {
  return mnUserServerID;
}

// @ 0x606d80
void cAuthManager::EndLoginDialog() {
  MessageServer()->PostMSG(0x4fd2bd3, 0, 0);
  SPUIHelpers::EndModal(mpLoginLayout->FindWindowByID(0x40cf9b0, true), 0, true);
  mpLoginLayout->Shutdown(true);
  delete mpLoginLayout;
  mpLoginLayout = 0;
}

// @ 0x606de0
void cAuthManager::SetLoginDialogVisible(bool visible) {
  if (mpLoginLayout) {
    mpLoginLayout->FindWindowByID(0x40cf9b0, true)->SetFlag(1, visible);
    IWindow* w = mpLoginLayout->FindWindowByID(0x40cf9b0, true);
    if (visible)
      SPUIHelpers::BeginModal(w, 0, true);
    else
      SPUIHelpers::EndModal(w, 0, true);
  } else
    MessageServer()->PostMSG(0x5c5594a, 0, 0);
}

static AutoRefCount<cConnectingDialog> sConnectingDialog;  // 0x15f3670

// @ 0x607190
bool cAuthManager::Shutdown() {
  if (sConnectingDialog) {
    sConnectingDialog->Close();
    sConnectingDialog = 0;
  }
  XHTMLManager()->GetResources()->RemoveListener(static_cast<cAuthBase14*>(this));
  EA::Messaging::IMessageServer* server = MessageServer();
  if (server) {
    server->RemoveHandler(this, 0x4bf2fc9, -9999);
    server->RemoveHandler(this, 0xce7afa41, -9999);
    server->RemoveHandler(this, 0x5b85672, -9999);
  }
  return true;
}

// @ 0x607290
void cAuthManager::SetPlayOffline(bool offline) {
  mbPlayOffline = offline;
  if (offline) {
    mPassword.clear();
    EA::Messaging::IMessageServer* server = MessageServer();
    if (server) server->PostMSG(0x5ff8006, 0, 0);
  }
}

// @ 0x6072d0
void cAuthManager::SetOfflineUserID() {
  ConfigManager()->GetString(0, mScreenName);
  mnUserServerID = (uint64_t)-2;
  mnUserLocalID = FNVHash(mScreenName.c_str(), 0x811c9dc5, true);
}

// @ 0x607310
void cAuthManager::ShowLoginDialog(bool b) {
  if (!IsLoginUIAvailable()) {
    if (!pReg) pReg = new ("UI/cRegistrationDialog", 0, 0, 0, 0) cRegistrationDialog();
    pReg->Show(b);
  } else
    ShowLoginUI(b);
}

// @ 0x6073a0
void cAuthManager::InitialLogin() {
  if (!mbPrompt && (mbPlayOffline || (mUser.size() && mPassword.size()))) {
    if (mbPlayOffline) {
      MessageServer()->PostMSG(0x5b85ff5, 0, 0);
      if (!sAppProperties->mpValues->mbGalacticAdventures) SPUIHelpers::ShowErrorDialog(0, (const void*)0x151e5c8);
      Pollinator()->SetEnabledState(0x4c4d2cd);
      MessageServer()->PostMSG(0x44db12e, 0, 0);
      SetOfflineUserID();
    } else
      Login();
  } else
    ShowLoginDialog(true);
}

// @ 0x6074b0
void cAuthManager::OnModalWindowEnd(IWindow* window, uint32_t result) {
  if (window->GetControlID() == 0x50f92d8 && result == 0x50fad88) {
    CancelLogin();
    Pollinator()->SetEnabledState(0x4c4d2cd);
    MessageServer()->PostMSG(0x5b85ff5, 0, 0);
    MessageServer()->PostMSG(0x44db12e, 0, 0);
    EndLoginDialog();
    SetOfflineUserID();
  }
}

static AutoRefCount<cAuthManager> sAuthManager;  // 0x15f3814

class IUnknownCast {
 public:
  PV(0) PV(1) PV(2)
  virtual void* Cast(uint32_t typeID);  // +0xc
};

// @ 0x607530
void SetAuthManager(IUnknownCast* object) {
  sAuthManager = object ? (cAuthManager*)object->Cast(0x40f7cee) : 0;
}

// @ 0x6077f0
void cAuthManager::ShowLogin() {
  ShowLoginDialog(false);
}
}  // namespace Pollen
}  // namespace SP

// @ 0x606f30
// The original's scalar deleting dtor has no vptr store (likely a novtable interface);
// declaring it novtable here suppresses the emission entirely, so it stays ordinary.
struct cAuthMessage {
  virtual ~cAuthMessage();
};
cAuthMessage::~cAuthMessage() {}
