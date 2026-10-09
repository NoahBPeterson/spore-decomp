// SP::Pollen::cAuthManager (Spore.com login/authentication manager) plus the login help dialog,
// a few EASTL string members and small helpers around it.
// Flags: /O2 /MD /Gy /TP (no /EHsc: string locals have no unwind frames).
#include "types.h"

#define PV(n) virtual void pv##n();

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" unsigned int __cdecl strlen(const char*);
#pragma intrinsic(strlen)

extern char gEmptyString[];  // 0x01667bac (shared "" for char and wchar_t strings)

namespace eastl {
struct allocator {
  allocator() {}
};

template <typename T>
inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }

template <typename T>
inline unsigned int CharStrlen(const T* p) {
  const T* pCurrent = p;
  while (*pCurrent) ++pCurrent;
  return (unsigned int)(pCurrent - p);
}

int Compare(const char* p1, const char* p2, unsigned int n);  // FUN_00606ea0

template <typename I1, typename I2>
I1 search(I1 first1, I1 last1, I2 first2, I2 last2);  // 0x005e8ff0

template <typename T, typename A = allocator>
struct basic_string {
  typedef unsigned int size_type;
  enum { npos = -1 };
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;

  basic_string() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  basic_string(const T* pBegin, const T* pEnd, const A& allocator)
      : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator) {
    RangeInitialize(pBegin, pEnd);
  }
  struct CtorSprintf {};
  basic_string(CtorSprintf, const T* pFormat, ...);  // 0x00473020 (wchar_t)
  basic_string(const basic_string& x);  // 0x0057cb10 (char)
  ~basic_string() { DeallocateSelf(); }

  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1)
      DoFree(mpBegin, mpCapacity - mpBegin);
  }
  void DoFree(T* p, size_type) {
    if (p) EASTL_allocator_deallocate(p);
  }
  void AllocateSelf(size_type n);  // 0x00475ab0 (char)
  void RangeInitialize(const T* pBegin, const T* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelf(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
  static T* CharStringUninitializedCopy(const T* pSource, const T* pSourceEnd, T* pDestination) {
    memmove(pDestination, pSource, (size_t)(pSourceEnd - pSource) * sizeof(T));
    return pDestination + (pSourceEnd - pSource);
  }
  size_type length() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }
  void clear() {
    if (mpBegin != mpEnd) {
      *mpBegin = 0;
      mpEnd = mpBegin;
    }
  }
  basic_string& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0 (char), 0x00423650 (wchar_t)
  basic_string& operator=(const basic_string& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  basic_string& replace(size_type position, size_type n, const T* p);  // 0x005f8f80 (wchar_t)
  void Trim();                                                       // 0x00606e60 (wchar_t)

  static int compare(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2) {
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int nMin = min_alt(n1, n2);
    const int cmp = Compare(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
  }
  int compare(const T* p) const;
  basic_string substr(size_type position, size_type n) const;
  basic_string left(size_type n) const;
  size_type find(const T* p, size_type position, size_type n) const {
    T* const pBegin = mpBegin;
    T* const pEnd = mpEnd;
    if ((position + n) <= (size_type)(pEnd - pBegin)) {
      const T* const pResult = search(pBegin + position, pEnd, p, p + n);
      if ((pResult != pEnd) || (n == 0)) return (size_type)(pResult - pBegin);
    }
    return (size_type)npos;
  }
  size_type find(const T* p, size_type position = 0) const;
};
}  // namespace eastl
typedef eastl::basic_string<char> string8;
typedef eastl::basic_string<wchar_t> string16;

// @ 0x00607a80
template <>
int eastl::basic_string<char>::compare(const char* p) const {
  return compare(mpBegin, mpEnd, p, p + strlen(p));
}

// @ 0x006082a0
template <>
string8 eastl::basic_string<char>::substr(size_type position, size_type n) const {
  return basic_string(mpBegin + position,
                      mpBegin + position + min_alt(n, (size_type)(mpEnd - mpBegin) - position),
                      mAllocator);
}

// @ 0x00608310
template <>
string8 eastl::basic_string<char>::left(size_type n) const {
  const size_type nLength = length();
  if (n < nLength) return substr(0, n);
  return *this;
}

// @ 0x00608340
template <>
string16::size_type eastl::basic_string<wchar_t>::find(const wchar_t* p, size_type position) const {
  return find(p, position, CharStrlen(p));
}

// @ 0x006083b0
string8& GetEmptyString8() {
  static string8 sEmpty;
  return sEmpty;
}

// ---------------------------------------------------------------------------------------------
namespace EA {
namespace COM {
class IUnknown32 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t type) const = 0;
  virtual void pvUnknown3();
  ~IUnknown32() {}
};
}  // namespace COM
template <typename T>
class RefCountTemplate {
 public:
  RefCountTemplate() : mRefCount(0) {}
  virtual ~RefCountTemplate() {}
  T mRefCount;
};
template <typename T>
class RefCountVTemplate {
 public:
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  ~AutoRefCount() {
    if (mpObject) mpObject->Release();
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
namespace Messaging {
class IHandler {
 public:
  virtual ~IHandler() {}
  virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
};
}  // namespace Messaging
namespace XHTML {
namespace Resource {
class IAuthenticationService : public RefCountTemplate<int> {
 public:
  virtual bool AddAuthentication(void* pResource, struct Request* pRequest) = 0;
};
}  // namespace Resource
}  // namespace XHTML
namespace UTFWin {
class IWindow;
struct Message {
  IWindow* mpSource;  // +0x0
  uint32_t pad4;
  uint32_t mEventType;  // +0x8
  uint32_t padc;
  uint32_t mKey;  // +0x10
};
class IWindow {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual uint32_t GetControlID();  // +0x1c
  PV(8) PV(9) PV(10)
  virtual uint32_t GetFlags();  // +0x2c
  PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31)
  virtual void SetCaption(const wchar_t* text);  // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45)
  PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(class IWinProc* p);     // +0x104
  virtual void RemoveWinProc(class IWinProc* p);  // +0x108
};
class IWinProc : public COM::IUnknown32 {
 public:
  virtual uint32_t GetEventFlags();
  virtual bool HandleUIMessage(IWindow* pWindow, const Message& msg) = 0;
};
class __declspec(novtable) IModalWindowCallback {
 public:
  virtual void pv0() = 0;
  virtual void OnModalEnd(IWindow* pWindow, uint32_t id) = 0;
};
class CustomWinProc : public IWinProc {
 public:
  bool HandleUIMessage(IWindow* pWindow, const Message& msg);  // 0x00950ef0
  uint32_t pad4[2];
};
}  // namespace UTFWin
}  // namespace EA

struct ResourceKey {
  uint32_t mInstance, mType, mGroup;
};
class cSPUILayout {
 public:
  bool Init(const ResourceKey& key, int a, uint32_t b);                // 0x008120d0
  EA::UTFWin::IWindow* FindWindowByID(uint32_t id, bool recursive);    // 0x008105b0
  void Shutdown(bool b);                                               // 0x00811ad0
  uint32_t pad[3];
};
namespace SPUIHelpers {
bool BeginModal(EA::UTFWin::IWindow* pWindow, int a, bool b);  // 0x008099a0
void EndModal(EA::UTFWin::IWindow* pWindow, uint32_t id, bool b);  // 0x00809c50
}  // namespace SPUIHelpers
void FUN_00809db0(const void* a, const void* b);
extern const char DAT_0151e5f0[], DAT_0151e5e0[], DAT_0151e5ec[], DAT_0151e5d4[];

namespace SP {
class cString {
 public:
  cString();                                                    // 0x006b5060
  ~cString();                                                   // 0x006b5240
  void Load(uint32_t tableID, uint32_t instanceID, const wchar_t* pDefault);  // 0x006b54b0
  const wchar_t* GetText(bool b);                                 // 0x006b55c0
  uint32_t pad[5];
};
class cStringTokenTranslator : public EA::RefCountVTemplate<int> {
 public:
  cStringTokenTranslator();   // 0x006b5870
  ~cStringTokenTranslator();  // 0x005725a0
  virtual void pv3();
  virtual bool TranslateToken(const wchar_t* pToken, string16& out) = 0;
};
class cPollinator {
 public:
  void SetEnabledState(uint32_t state);  // 0x0060cec0
  void FUN_00612270();
  void FUN_00611540();
  void Login(const char* user, const char* password, const wchar_t* path);  // FUN_00611480
};
cPollinator* Pollinator();  // FUN_0067cb30
class IMessageBox {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual void Show(const wchar_t* text);  // +0x34
};
class IUIManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual IMessageBox* GetMessageBox();  // +0x20
};
IUIManager* UIManager();  // FUN_0067de40
class IAppSystem {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
  virtual void OpenURL(const wchar_t* url);  // +0x5c
};
IAppSystem* AppSystem();  // 0x0067dd00

namespace Pollen {
bool GetURL(uint32_t id, string16& out);  // 0x006214c0

// Retail-only interface at cAuthManager+0x1c (not in the 2008 PDB; name guessed).
class IAuthManager : public EA::COM::IUnknown32 {
 public:
  IAuthManager() {}
  virtual void pv4();
  virtual void pv5();
  virtual void SetUserPassword(const string8& user, const string8& password) = 0;  // 6
  virtual void GetUserPassword(string8& user, string8& password) = 0;              // 7
  virtual void ShowLoginDialog(bool b) = 0;                                        // 8 +0x20
  virtual void pv9();
  virtual void SetRememberPassword(bool b) = 0;  // 10 +0x28
  virtual void pv11();
  virtual const string8& GetUser() = 0;      // 12 +0x30
  virtual const string8& GetPassword() = 0;  // 13 +0x34
  virtual void pv14();
  virtual void pv15();
  virtual void pv16();
  virtual void pv17();
  virtual void pv18();
  virtual void pv19();
  virtual void ProcessLoginResults(short result) = 0;  // 20 +0x50
  virtual void SavePrefs() = 0;                        // 21 +0x54
  virtual void pv22();
  virtual void FinishLogin(bool b) = 0;                // 23 +0x5c
};

class IServiceRegistry {
 public:
  PV(0) PV(1) PV(2)
  virtual IAuthManager* Get(uint32_t id);  // +0xc
};
extern IServiceRegistry* gServiceRegistry;  // 0x015f3814

// @ 0x00607a60
IAuthManager* AuthManager() {
  if (gServiceRegistry) return gServiceRegistry->Get(0x7201461);
  return 0;
}

namespace {
class cConnectingDialog : public EA::UTFWin::CustomWinProc {
 public:
  void HandleResults(bool success);  // 0x006075c0
  void Show(const wchar_t* text);
  EA::AutoRefCount<EA::UTFWin::IWindow> mpWindow;  // +0xc
  float mStartTime;                                // +0x10
  float mTimeout;                                  // +0x14
  bool mEndConnecting;                             // +0x18
  bool mEndConnected;                              // +0x19
  float mRotation[4];                              // +0x1c
  cSPUILayout mLayout;                             // +0x2c
};
cConnectingDialog* gpConnectingDialog;  // 0x015f3670

class cLoginHelpDialog : public EA::UTFWin::CustomWinProc {
 public:
  bool Show();
  bool HandleUIMessage(EA::UTFWin::IWindow* pWindow, const EA::UTFWin::Message& msg);
  cSPUILayout mLayout;  // +0xc
};
}  // namespace

class cAuthManager : public EA::UTFWin::IWinProc,
                     public EA::UTFWin::IModalWindowCallback,
                     public EA::Messaging::IHandler,
                     public EA::XHTML::Resource::IAuthenticationService,
                     public cStringTokenTranslator,
                     public IAuthManager {
 public:
  cAuthManager();
  void EndLoginDialog();  // 0x00606d80
  void LoadSavedPrefs();
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t type) const;
  virtual bool HandleUIMessage(EA::UTFWin::IWindow* pWindow, const EA::UTFWin::Message& msg);
  virtual bool HandleMessage(uint32_t messageID, void* pMessage);
  virtual bool AddAuthentication(void* pResource, EA::XHTML::Resource::Request* pRequest);
  virtual bool TranslateToken(const wchar_t* pToken, string16& out);
  virtual void SetUserPassword(const string8& user, const string8& password);
  virtual void GetUserPassword(string8& user, string8& password);
  virtual void ShowLoginDialog(bool b);
  virtual void SetRememberPassword(bool b);
  virtual const string8& GetUser();
  virtual const string8& GetPassword();
  virtual void ProcessLoginResults(short result);
  virtual void SavePrefs();
  virtual void FinishLogin(bool b);

  string8 mUser;              // +0x20
  string8 mPassword;          // +0x30
  string8 mScreenName;        // +0x40
  uint64_t mnUserServerID;    // +0x50
  uint32_t mnUserLocalID;     // +0x58
  bool mbPlayOffline;         // +0x5c
  bool mbPrompt;              // +0x5d
  bool mbSavedPrefsFlag;      // +0x5e
  bool mbRetryLogin;          // +0x5f
  cSPUILayout* mpLoginLayout; // +0x60
  bool mbDontSavePrefs;       // +0x64
  bool mbLoggedIn;            // +0x65
  int mDialogInProgress;      // +0x68
  EA::AutoRefCount<EA::COM::IUnknown32> pReg;  // +0x6c
};

// @ 0x00607800
void cAuthManager::ProcessLoginResults(short result) {
  const short kResultSuccess = 0;
  const short kResultNoPrivileges = 7;
  if (kResultNoPrivileges == result && !mbSavedPrefsFlag) {
    mbRetryLogin = true;
    FUN_00809db0(DAT_0151e5f0, DAT_0151e5e0);
    return;
  }
  if (gpConnectingDialog) {
    gpConnectingDialog->HandleResults(kResultSuccess == result);
    if (gpConnectingDialog) {
      cConnectingDialog* p = gpConnectingDialog;
      gpConnectingDialog = 0;
      p->Release();
    }
  }
  if (kResultSuccess != result) {
    mbRetryLogin = false;
    cString text;
    if (result == 1) {
      text.Load(0xb7bcef68, 0x56bfcfc,
                L"There was an error connecting to the Spore web servers.  Please check your internet connection or try again later.");
    } else if (result == 3) {
      text.Load(0xb7bcef68, 0x662d9ed, L"There was an internal application error.  Please try again.");
    } else if (result == 2) {
      text.Load(0xb7bcef68, 0x56bfcfc, L"The Spore server encountered an error.  Please try again later.");
    } else if (result == 5) {
      text.Load(0xb7bcef68, 0x662da10,
                L"Your account has not been validated.  Please respond to the validation email sent to you on registration.  Use the help link on the login dialog if you need help.");
    } else if (result == 7) {
      text.Load(0xb7bcef68, 0x636e66e,
                L"You do not have the proper Spore.com privileges to use this product's online features.");
    } else if (result == 8) {
      text.Load(0xb7bcef68, 0x636e611,
                L"The code for this installation is invalid and cannot be used to link this product to your account.");
      mbSavedPrefsFlag = true;
      SavePrefs();
    } else if (result == 4) {
      text.Load(0xb7bcef68, 0x662d9eb, L"");
      mUser.clear();
      mPassword.clear();
    } else if (result == 6) {
      if (mpLoginLayout)
        FinishLogin(true);
      else
        ShowLoginDialog(true);
      return;
    }
    UIManager()->GetMessageBox()->Show(text.GetText(false));
    FUN_00809db0(DAT_0151e5ec, DAT_0151e5d4);
    mDialogInProgress = 1;
    if (mpLoginLayout) FinishLogin(false);
  } else {
    if (mbRetryLogin) mbSavedPrefsFlag = true;
    mbLoggedIn = true;
    SavePrefs();
    Pollinator()->SetEnabledState(0x4c4d2c3);
    Pollinator()->FUN_00612270();
    if (mpLoginLayout) EndLoginDialog();
  }
}

// ---------------------------------------------------------------------------------------------
// Some dialog with a "skip/offline" button (class unknown).
class cOfflinePromptDialog : public EA::UTFWin::CustomWinProc {
 public:
  bool HandleUIMessage(EA::UTFWin::IWindow* pWindow, const EA::UTFWin::Message& msg);
  uint32_t padc[3];
  bool mbClosed;  // +0x18
};
bool FUN_00685520(int mode);

// @ 0x00607b70
bool cOfflinePromptDialog::HandleUIMessage(EA::UTFWin::IWindow* pWindow, const EA::UTFWin::Message& msg) {
  if (msg.mEventType == 0x287259f6 && FUN_00685520(2) && msg.mpSource->GetControlID() == 0x5d2bdf8 &&
      !mbClosed) {
    Pollinator()->FUN_00611540();
    IAuthManager* pAuth = AuthManager();
    if (pAuth) pAuth->ProcessLoginResults(6);
    return true;
  }
  return CustomWinProc::HandleUIMessage(pWindow, msg);
}

// Login/"play offline" prompt with a "don't ask again" checkbox (class unknown).
class cLoginPromptDialog : public EA::UTFWin::CustomWinProc {
 public:
  bool HandleUIMessage(EA::UTFWin::IWindow* pWindow, const EA::UTFWin::Message& msg);
  cSPUILayout mLayout;  // +0xc
};

// @ 0x00607be0
bool cLoginPromptDialog::HandleUIMessage(EA::UTFWin::IWindow* pWindow, const EA::UTFWin::Message& msg) {
  if (msg.mEventType == 0x287259f6) {
    if (msg.mpSource->GetControlID() == 0x50fad88 || msg.mpSource->GetControlID() == 0x50fb5d0) {
      IAuthManager* pAuth = gServiceRegistry ? gServiceRegistry->Get(0x7201461) : 0;
      if (msg.mpSource->GetControlID() == 0x50fad88) {
        pAuth->ShowLoginDialog(true);
        EA::UTFWin::IWindow* pCheck = mLayout.FindWindowByID(0x50fad80, true);
        if (pCheck) pAuth->SetRememberPassword(!((pCheck->GetFlags() >> 2) & 1));
      }
      if (msg.mpSource->GetControlID() == 0x50fb5d0) pAuth->FinishLogin(true);
      EA::UTFWin::IWindow* pDialog = mLayout.FindWindowByID(0x50f92d8, true);
      if (pDialog) {
        SPUIHelpers::EndModal(pDialog, msg.mpSource->GetControlID(), true);
        pDialog->RemoveWinProc(this);
      }
      mLayout.Shutdown(true);
      return true;
    }
  }
  return false;
}

// @ 0x00607cf0
bool cLoginHelpDialog::Show() {
  ResourceKey key = {0xd5aabe49, 0x510a95b, 0x40464100};
  if (mLayout.Init(key, 0, 0x5b598f7)) {
    EA::UTFWin::IWindow* pText = mLayout.FindWindowByID(0x56c14b8, true);
    if (pText) {
      string16 url;
      if (GetURL(0x56bbbd1, url)) pText->SetCaption(url.c_str());
    }
    EA::UTFWin::IWindow* pWindow = mLayout.FindWindowByID(0x56c1908, true);
    if (pWindow) {
      pWindow->AddWinProc(this);
      return SPUIHelpers::BeginModal(pWindow, 0, true);
    }
    mLayout.Shutdown(true);
  }
  return false;
}

// @ 0x00607df0
bool cLoginHelpDialog::HandleUIMessage(EA::UTFWin::IWindow* pWindow, const EA::UTFWin::Message& msg) {
  if (msg.mEventType == 0x287259f6) {
    if (msg.mpSource->GetControlID() == 0x5d011f8) {
      EA::UTFWin::IWindow* pDialog = mLayout.FindWindowByID(0x56c1908, true);
      if (pDialog) {
        SPUIHelpers::EndModal(pDialog, 0, true);
        pDialog->RemoveWinProc(this);
      }
      mLayout.Shutdown(true);
      (gServiceRegistry ? gServiceRegistry->Get(0x7201461) : 0)->FinishLogin(true);
      return true;
    }
    if (msg.mpSource->GetControlID() == 0x56c03a0) {
      string16 url;
      if (GetURL(0x56bbbd1, url)) AppSystem()->OpenURL(url.c_str());
    }
  } else if (msg.mEventType == 1 && msg.mKey == 0x42) {
    return true;
  }
  return false;
}

// @ 0x00607f30
cAuthManager::cAuthManager()
    : mnUserServerID((uint64_t)-2),
      mnUserLocalID((uint32_t)-1),
      mbPlayOffline(false),
      mbPrompt(false),
      mbSavedPrefsFlag(false),
      mbRetryLogin(false),
      mpLoginLayout(0),
      mbDontSavePrefs(false),
      mbLoggedIn(false),
      mDialogInProgress(0) {}

// @ 0x00608090
void DestroyAuthManager(cAuthManager* p) { p->~cAuthManager(); }

struct cPropertyList;
struct Property {
  uint32_t pad[4];
  uint16_t pad10;
  uint16_t mnType;  // +0x12
  bool* GetBool();  // 0x0041e920
};
class IPropertyList {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property*& prop);  // +0x24
};
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instance, uint32_t group, IPropertyList*& out);  // +0x2c
};
IPropertyManager* PropertyManager();  // 0x0067de30
bool GetPropertyAsString8(IPropertyList* pList, uint32_t id, string8& out);  // 0x006a13b0
}  // namespace Pollen
}  // namespace SP
namespace EA {
namespace Hash {
uint32_t FNV1_String16(const wchar_t* p, uint32_t seed, int caseMode);  // 0x00932f30
}
}  // namespace EA
void Decrypt(const string8& in, string8& out);  // 0x0060bf00
extern const wchar_t* kLoginPrefsName;            // 0x0151e23c (L"login")
namespace SP {
namespace Pollen {

// @ 0x00608120
void cAuthManager::LoadSavedPrefs() {
  EA::AutoRefCount<IPropertyList> pList;
  IPropertyManager* pPropMgr = PropertyManager();
  IPropertyList*& pListOut = pList.AsOutParam();
  const uint32_t instance = EA::Hash::FNV1_String16(kLoginPrefsName, 0x811c9dc5, 1);
  if (pPropMgr->GetPropertyList(instance, 0x11ac192, pListOut)) {
    Property* prop;
    if (pList && pList->GetProperty(0x40e3d98, prop) && prop->mnType == 1) mbPlayOffline = *prop->GetBool();
    if (pList && pList->GetProperty(0x440a514, prop) && prop->mnType == 1) mbPrompt = *prop->GetBool();
    GetPropertyAsString8(pList, 0x40512ef, mUser);
    string8 encrypted;
    if (GetPropertyAsString8(pList, 0x40512f4, encrypted)) Decrypt(encrypted, mPassword);
    if (pList && pList->GetProperty(0x6390ede, prop) && prop->mnType == 1) mbSavedPrefsFlag = true;
  }
}

struct cAppProperties {
  uint32_t pad[15];
  struct Inner {
    uint32_t pad[70];
    int mValue;  // +0x118
  }* mpInner;  // +0x3c
};
extern cAppProperties* sAppProperties;  // 0x015fd918
extern const wchar_t* kRegKeyA;        // 0x0151e234
extern const wchar_t* kRegKeyB;        // 0x0151e238
bool ReadRegistryString(const wchar_t* key, string16& out);  // 0x006aba80

// @ 0x006083f0
void __stdcall OnAuthMessage(uint32_t unused, uint32_t messageID) {
  IAuthManager* pAuth = gServiceRegistry ? gServiceRegistry->Get(0x7201461) : 0;
  cPollinator* pPollinator = Pollinator();
  if (pPollinator && pAuth) {
    if (messageID == 0x5107b1a) {
      string16 path;
      if (ReadRegistryString(sAppProperties->mpInner->mValue ? kRegKeyA : kRegKeyB, path)) {
        string16::size_type pos;
        while ((pos = path.find(L"\"")) != (string16::size_type)string16::npos) path.replace(pos, 1, L"");
        path.Trim();
        pPollinator->Login(pAuth->GetUser().c_str(), pAuth->GetPassword().c_str(), path.c_str());
      } else {
        pAuth->ProcessLoginResults(3);
      }
    } else {
      pAuth->ProcessLoginResults(6);
    }
  }
}

// @ 0x00608550
void cAuthManager::SetUserPassword(const string8& user, const string8& password) {
  mUser = user;
  mPassword = password;
  mbPlayOffline = false;
}

// @ 0x00608590
void cAuthManager::GetUserPassword(string8& user, string8& password) {
  user = mUser;
  password = mPassword;
}

}  // namespace Pollen
}  // namespace SP
namespace EA {
namespace XHTML {
namespace Resource {
struct HeaderMap {
  void Set(const char* name, const char* value);  // 0x00944d00
};
struct URLInfo {
  int GetScheme();  // 0x0094baa0
};
struct Request {
  uint32_t pad[12];
  URLInfo mURL;  // +0x30
  uint32_t pad34[176];
  HeaderMap mHeaders;  // +0x2f4
};
}  // namespace Resource
}  // namespace XHTML
namespace Internet {
namespace URL {
void ConvertPathToEncodedForm(const char* p, string8& out, int flags);  // 0x0094b610
}
}  // namespace Internet
}  // namespace EA
namespace SP {
namespace Pollen {

// @ 0x006085d0
bool cAuthManager::AddAuthentication(void* pResource, EA::XHTML::Resource::Request* pRequest) {
  if (pRequest && pRequest->mURL.GetScheme() == 3) {
    string8 value(GetUser());
    EA::Internet::URL::ConvertPathToEncodedForm(value.c_str(), value, 0);
    pRequest->mHeaders.Set("Spore-User", value.c_str());
    value = GetPassword();
    EA::Internet::URL::ConvertPathToEncodedForm(value.c_str(), value, 0);
    pRequest->mHeaders.Set("Spore-Password", value.c_str());
    return true;
  }
  return false;
}

void FUN_006b8f00(const char* name, string16& out);

// @ 0x006086b0
bool cAuthManager::TranslateToken(const wchar_t* pToken, string16& out) {
  if (EA::Hash::FNV1_String16(pToken, 0x811c9dc5, 1) != 0xfae0227d) return false;
  if (!mbPlayOffline) {
    FUN_006b8f00(mScreenName.c_str(), out);
    return true;
  }
  out.assign(L"", L"");
  return true;
}

namespace {
// @ 0x00608710
void cConnectingDialog::Show(const wchar_t* text) {
  EA::UTFWin::IWindow* pText = mLayout.FindWindowByID(0x42e2e38, true);
  if (pText) pText->SetCaption(string16(string16::CtorSprintf(), L"%ls", text).c_str());
  EA::UTFWin::IWindow* pWindow = mLayout.FindWindowByID(0x431e538, true);
  if (pWindow) SPUIHelpers::BeginModal(pWindow, 0, true);
}
}  // namespace

}  // namespace Pollen
}  // namespace SP
