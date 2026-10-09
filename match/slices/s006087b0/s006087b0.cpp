// SP::Pollen::cAuthManager (Spore.com login) part 2: Init, the login layout, SavePrefs, Login,
// message/UI handlers; plus the two HTTP request filters (cCanvasResFilter, buddy-mode filter).
// Declarations are shared with s00607800. Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

#define PV(n) virtual void pv##n();

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
struct ICoreAllocator;
ICoreAllocator* GetDefaultAllocator();  // FUN_009512c0
// EA::UTFWin::MultiHeapObject::operator new (FUN_009512d0)
void* operator new(unsigned int size, int alignment, const char* name, ICoreAllocator* pAllocator);
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
  basic_string(CtorSprintf, const T* pFormat, ...);  // 0x00473020 (wchar_t), 0x00472f50 (char)
  basic_string& sprintf(const T* pFormat, ...);       // 0x00472fe0 (char)
  // (out of line at 0x0057cb10 elsewhere; this TU inlines it with AllocateSelf expanded)
  basic_string(const basic_string& x) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(x.mAllocator) {
    RangeInitializeInl(x.mpBegin, x.mpEnd);
  }
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
  basic_string& operator=(const T* p) { return assign(p, p + strlen(p)); }
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
  size_type find(T c, size_type position = 0) const;  // 0x00607580 (char)
  bool empty() const { return (mpBegin == mpEnd); }
  size_type size() const { return (size_type)(mpEnd - mpBegin); }
  T* DoAllocate(size_type n) {
    return (T*)EASTL_allocator_allocate(n * sizeof(T), "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
  }
  void AllocateSelf() {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  void AllocateSelfN(size_type n) {
    if (n > 1) {
      mpBegin = DoAllocate(n);
      mpEnd = mpBegin;
      mpCapacity = mpBegin + n;
    } else
      AllocateSelf();
  }
  void RangeInitializeInl(const T* pBegin, const T* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelfN(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
};
}  // namespace eastl
typedef eastl::basic_string<char> string8;
typedef eastl::basic_string<wchar_t> string16;

// Same-TU EASTL instantiations: bodies visible to the optimizer but not inlined (as in the original
// object; compare/substr/left are verified in s00607800, find(char) at 0x00607580 is not in this batch).
template <>
__declspec(noinline) int eastl::basic_string<char>::compare(const char* p) const {
  return compare(mpBegin, mpEnd, p, p + strlen(p));
}
template <>
__declspec(noinline) string8 eastl::basic_string<char>::substr(size_type position, size_type n) const {
  return basic_string(mpBegin + position,
                      mpBegin + position + min_alt(n, (size_type)(mpEnd - mpBegin) - position),
                      mAllocator);
}
template <>
__declspec(noinline) string8 eastl::basic_string<char>::left(size_type n) const {
  const size_type nLength = length();
  if (n < nLength) return substr(0, n);
  return *this;
}
template <>
__declspec(noinline) string8::size_type eastl::basic_string<char>::find(char c, size_type position) const {
  if (position < (size_type)(mpEnd - mpBegin)) {
    const char* p = mpBegin + position;
    while (p != mpEnd && *p != c) ++p;
    if (p != mpEnd) return (size_type)(p - mpBegin);
  }
  return (size_type)npos;
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
  AutoRefCount(T* pObject) : mpObject(pObject) {
    if (mpObject) mpObject->AddRef();
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
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMSG(uint32_t messageID, void* p1, void* p2);  // +0x14
  PV(6) PV(7) PV(8)
  virtual void AddListener(Messaging::IHandler* pHandler, uint32_t messageID);  // +0x24
  PV(10)
  virtual void RemoveListener(Messaging::IHandler* pHandler, uint32_t messageID, int priority);  // +0x2c
};
namespace Messaging {
IMessageServer* GetServer();  // 0x00883860
}
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
  virtual int AddRef();
  virtual int Release();
  PV(2)
  virtual class IWinControl* QueryControl(uint32_t type);  // +0xc
  PV(4) PV(5) PV(6)
  virtual uint32_t GetControlID();  // +0x1c
  PV(8) PV(9) PV(10)
  virtual uint32_t GetFlags();  // +0x2c
  PV(12) PV(13) PV(14)
  virtual const wchar_t* GetCaption();  // +0x3c
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(uint32_t flag, bool value);  // +0x7c
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
class IWinControl {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetFlag(uint32_t flag, bool value);  // +0x28
};
class __declspec(novtable) IModalWindowCallback {
 public:
  virtual void pv0() = 0;
  virtual void OnModalEnd(IWindow* pWindow, uint32_t id) = 0;
};
class ISerializable {
 public:
  virtual void pv0();
};
class MultiHeapObject {};
class CustomWinProc : public IWinProc, public ISerializable, public MultiHeapObject {
 public:
  CustomWinProc() : mRefCount(0) {}
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t type) const;
  bool HandleUIMessage(IWindow* pWindow, const Message& msg);  // 0x00950ef0
  int mRefCount;  // +0x8
};
class IWindowManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  PV(15) PV(16) PV(17) PV(18)
  virtual void SetFocus(int a, IWindow* pWindow);  // +0x4c
};
}  // namespace UTFWin
}  // namespace EA

struct ResourceKey {
  uint32_t mInstance, mType, mGroup;
  static ResourceKey Make(uint32_t instance, uint32_t type, uint32_t group) {
    ResourceKey k;
    k.mInstance = instance;
    k.mType = type;
    k.mGroup = group;
    return k;
  }
};
class cSPUILayout {
 public:
  cSPUILayout();           // 0x00810000
  virtual ~cSPUILayout();
  bool Init(const ResourceKey& key, int a, uint32_t b);                // 0x008120d0
  EA::UTFWin::IWindow* FindWindowByID(uint32_t id, bool recursive);    // 0x008105b0
  void Shutdown(bool b);                                               // 0x00811ad0
  uint32_t pad[5];
};
namespace SPUIHelpers {
bool BeginModal(EA::UTFWin::IWindow* pWindow, int a, bool b);  // 0x008099a0
void EndModal(EA::UTFWin::IWindow* pWindow, uint32_t id, bool b);  // 0x00809c50
bool BeginModal(EA::UTFWin::IWindow* pWindow, EA::UTFWin::IModalWindowCallback* pCallback, bool b);
void AutoSizeWindowForText(EA::UTFWin::IWindow* pWindow, bool a, bool b);  // 0x00806e40
void AnchorWindowToWindow(EA::UTFWin::IWindow* pWindow, EA::UTFWin::IWindow* pAnchor, uint32_t flags, int a);  // 0x00807340
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
  uint8_t pad[0xf1];
  bool mbBuddyMode;  // +0xf1 (guess)
  bool IsBuddyMode() const { return mbBuddyMode; }
};
EA::IMessageServer* MessageServer();          // 0x0067dcc0
EA::UTFWin::IWindowManager* WindowManager();  // 0x0067caa0
class IConfigManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
  virtual int GetInt(uint32_t id);  // +0x30
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
  virtual void GetUserName(int a, string8& out);  // +0x4c
};
IConfigManager* ConfigManager();  // 0x0067dd30
cPollinator* Pollinator();  // FUN_0067cb30
class IMessageBox {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void AddTokenTranslator(class cStringTokenTranslator* p);  // +0x1c
  PV(8) PV(9) PV(10) PV(11) PV(12)
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
  virtual bool Init() = 0;  // 4
  virtual void pv5();
  virtual void SetUserPassword(const string8& user, const string8& password) = 0;  // 6
  virtual void GetUserPassword(string8& user, string8& password) = 0;              // 7
  virtual void ShowLoginDialog(bool b) = 0;                                        // 8 +0x20
  virtual void pv9();
  virtual void SetRememberPassword(bool b) = 0;  // 10 +0x28
  virtual bool GetRememberPassword() = 0;  // 11 +0x2c
  virtual const string8& GetUser() = 0;      // 12 +0x30
  virtual const string8& GetPassword() = 0;  // 13 +0x34
  virtual void pv14();
  virtual void pv15();
  virtual void pv16();
  virtual void pv17();
  virtual void ShowLoginLayout(bool bOfflineAvailable) = 0;  // 18
  virtual void Login() = 0;                                  // 19 +0x4c
  virtual void ProcessLoginResults(short result) = 0;  // 20 +0x50
  virtual void SavePrefs() = 0;                        // 21 +0x54
  virtual bool IsRegistered() = 0;                     // 22 +0x58
  virtual void FinishLogin(bool b) = 0;                // 23 +0x5c
};

class IServiceRegistry {
 public:
  PV(0) PV(1) PV(2)
  virtual IAuthManager* Get(uint32_t id);  // +0xc
};
extern IServiceRegistry* gServiceRegistry;  // 0x015f3814

struct cSPVector4 {
  float x, y, z, w;
  cSPVector4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
};
namespace {
class cConnectingDialog : public EA::UTFWin::CustomWinProc {
 public:
  cConnectingDialog()
      : mTimeout(30.0f), mEndConnecting(false), mEndConnected(false), mRotation(0.0f, 0.0f, 1.0f, 0.0f) {}
  bool Init();                       // 0x00606c40
  void HandleResults(bool success);  // 0x006075c0
  void Show(const char* text);       // 0x00608710
  EA::AutoRefCount<EA::UTFWin::IWindow> mpWindow;  // +0xc
  float mStartTime;                                // +0x10
  float mTimeout;                                  // +0x14
  bool mEndConnecting;                             // +0x18
  bool mEndConnected;                              // +0x19
  cSPVector4 mRotation;                            // +0x1c
  cSPUILayout mLayout;                             // +0x2c
};
EA::AutoRefCount<cConnectingDialog> gpConnectingDialog;  // 0x015f3670

class cLoginHelpDialog : public EA::UTFWin::CustomWinProc {
 public:
  cLoginHelpDialog();  // 0x00607480
  bool Show();         // 0x00607cf0
  bool HandleUIMessage(EA::UTFWin::IWindow* pWindow, const EA::UTFWin::Message& msg);
  cSPUILayout mLayout;  // +0xc
};
class cOfflineConfirmationDialog : public EA::UTFWin::CustomWinProc {
 public:
  cOfflineConfirmationDialog();  // 0x00607450
  bool Init();                   // 0x00607050
  void SetCallback(EA::UTFWin::IModalWindowCallback* pCallback);  // 0x00606cd0
  cSPUILayout mLayout;  // +0xc
};
}  // namespace
class cRegistrationDialog : public EA::UTFWin::IWinProc {
 public:
  void Show(bool b);  // 0x00620050
};

class cAuthManager : public EA::UTFWin::IWinProc,
                     public EA::UTFWin::IModalWindowCallback,
                     public EA::Messaging::IHandler,
                     public EA::XHTML::Resource::IAuthenticationService,
                     public cStringTokenTranslator,
                     public IAuthManager {
 public:
  cAuthManager();
  void EndLoginDialog();  // 0x00606d80
  void LoadSavedPrefs();  // 0x00608120
  void Logout();          // 0x006073a0
  void ReadLoginLayout();
  virtual bool Init();
  virtual bool GetRememberPassword();
  virtual void ShowLoginLayout(bool bOfflineAvailable);
  virtual void Login();
  virtual bool IsRegistered();
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
  EA::AutoRefCount<cRegistrationDialog> pReg;  // +0x6c
};

// ---------------------------------------------------------------------------------------------
// Some dialog with a "skip/offline" button (class unknown).
class cOfflinePromptDialog : public EA::UTFWin::CustomWinProc {
 public:
  bool HandleUIMessage(EA::UTFWin::IWindow* pWindow, const EA::UTFWin::Message& msg);
  uint32_t padc[3];
  bool mbClosed;  // +0x18
};
bool FUN_00685520(int mode);

// Login/"play offline" prompt with a "don't ask again" checkbox (class unknown).
class cLoginPromptDialog : public EA::UTFWin::CustomWinProc {
 public:
  bool HandleUIMessage(EA::UTFWin::IWindow* pWindow, const EA::UTFWin::Message& msg);
  cSPUILayout mLayout;  // +0xc
};

string8& GetEmptyString8();  // 0x006083b0
struct Property {
  Property() : mnFlags(0), mnType(0) {}
  ~Property() {
    if (mnFlags & 4) Destruct(false);
  }
  void Set(uint16_t type, uint32_t flags, const void* pData, unsigned int elementSize, unsigned int count);  // 0x0093dd80
  void SetValueBool(const bool& value);  // 0x00422e20
  void Destruct(bool b);                 // 0x0093db80
  const void* GetDataPtr() const {
    if (mnFlags & 0x30) return *(void* const*)this;
    return mnType ? this : 0;
  }
  const string8* GetValueString8() const {
    if (mnType == 0x12 || mnType == 0x10) return (const string8*)GetDataPtr();
    return &GetEmptyString8();
  }
  uint32_t mData[4];
  uint16_t mnFlags;  // +0x10
  uint16_t mnType;   // +0x12
};
class IPropertyList {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4)
  virtual void SetProperty(uint32_t id, const Property* prop);  // +0x14
  PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property*& prop);  // +0x24
  virtual Property* GetPropertyPtr(uint32_t id);           // +0x28
};
class cPropertyList : public IPropertyList {
 public:
  cPropertyList();  // 0x006a1c40
  uint32_t pad4;
  ResourceKey mResourceKey;  // +0x8
  uint32_t pad14[9];
};
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instance, uint32_t group, IPropertyList*& out);  // +0x2c
  PV(12)
  virtual void AddPropertyList(IPropertyList* pList, uint32_t instance, uint32_t group);  // +0x34
};
void* GetSaveArea(uint32_t group);                                            // 0x006b1f90
void SaveNamedResource(IPropertyList* pList, const wchar_t* name, void* area);  // 0x006b4010
IPropertyManager* PropertyManager();  // 0x0067de30
bool GetPropertyAsString8(IPropertyList* pList, uint32_t id, string8& out);  // 0x006a13b0
}  // namespace Pollen
}  // namespace SP
namespace EA {
namespace Hash {
uint32_t FNV1_String16(const wchar_t* p, uint32_t seed, int caseMode);  // 0x00932f30
uint32_t FNV1_String8(const char* p, uint32_t seed, int caseMode);      // 0x00932e80
}
}  // namespace EA
void Decrypt(const string8& in, string8& out);  // 0x0060bf00
void Encrypt(const string8& in, string8& out);  // 0x0060bcf0
extern const wchar_t* kLoginPrefsName;            // 0x0151e23c (L"login")
namespace SP {
namespace Pollen {

extern IPropertyList* sAppProperties;  // 0x015fd918

}  // namespace Pollen
}  // namespace SP
namespace EA {
namespace XHTML {
namespace Resource {
struct HeaderMap {
  void Set(const char* name, const char* value);  // 0x00944d00
  void AddHeaderEntry(const char* name, const string8& value);  // 0x00944cb0
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
// Not inlined here (out-of-line copy at 0x00572660, shared by identical instantiations).
template <>
__declspec(noinline) EA::AutoRefCount<SP::Pollen::cLoginHelpDialog>::AutoRefCount(SP::Pollen::cLoginHelpDialog* pObject)
    : mpObject(pObject) {
  if (mpObject) mpObject->AddRef();
}
namespace SP {
namespace Pollen {

// @ 0x006087b0
bool cAuthManager::Init() {
  LoadSavedPrefs();
  string8 autoLogin(*sAppProperties->GetPropertyPtr(0x5e8af796)->GetValueString8());
  if (!autoLogin.empty()) {
    if (autoLogin.compare("OptOut") == 0) {
      ShowLoginDialog(true);
    } else {
      const string8::size_type pos = autoLogin.find(',', 0);
      if (pos != (string8::size_type)string8::npos && pos != autoLogin.length() - 1)
        SetUserPassword(autoLogin.left(pos), autoLogin.substr(pos + 1, (string8::size_type)string8::npos));
    }
    SetRememberPassword(false);
    mbDontSavePrefs = true;
  }
  mbLoggedIn = mUser.size() > 0;
  EA::IMessageServer* pServer = MessageServer();
  if (pServer) {
    pServer->AddListener(static_cast<EA::Messaging::IHandler*>(this), 0x4bf2fc9);
    pServer->AddListener(static_cast<EA::Messaging::IHandler*>(this), 0xce7afa41);
    pServer->AddListener(static_cast<EA::Messaging::IHandler*>(this), 0x5b85672);
  }
  ConfigManager()->GetUserName(0, mScreenName);
  mnUserServerID = (uint64_t)-2;
  mnUserLocalID = EA::Hash::FNV1_String8(mScreenName.c_str(), 0x811c9dc5, 1);
  UIManager()->GetMessageBox()->AddTokenTranslator(static_cast<cStringTokenTranslator*>(this));
  return true;
}

extern const ResourceKey kLoginLayout;  // 0x0151e5b0

// @ 0x00608a10
void cAuthManager::ShowLoginLayout(bool bOfflineAvailable) {
  mpLoginLayout = new ("LoginLayout", 0, 0, 0, 0) cSPUILayout();
  if (mpLoginLayout->Init(kLoginLayout, 0, 0x5b598f7)) {
    MessageServer()->PostMSG(0x4fd2bce, 0, 0);
    EA::UTFWin::IWindow* pDialog = mpLoginLayout->FindWindowByID(0x40cf9b0, true);
    pDialog->AddWinProc(this);
    EA::UTFWin::IWindow* pRemember = mpLoginLayout->FindWindowByID(0x40cf210, true);
    if (pRemember) {
      EA::UTFWin::IWinControl* pCheck = pRemember->QueryControl(0x8ed27e7a);
      if (pCheck) pCheck->SetFlag(4, GetRememberPassword() == false);
    }
    EA::UTFWin::IWindow* pLoginButton = mpLoginLayout->FindWindowByID(0x40cf208, true);
    EA::UTFWin::IWindow* pCancel = mpLoginLayout->FindWindowByID(0x451a478, true);
    mpLoginLayout->FindWindowByID(0x40e7fa8, true)->SetFlag(1, bOfflineAvailable);
    EA::UTFWin::IWindow* pBuddy = mpLoginLayout->FindWindowByID(0x5091898, true);
    pBuddy->SetFlag(1, Pollinator()->IsBuddyMode());
    pCancel->SetFlag(1, !bOfflineAvailable);
    SPUIHelpers::AutoSizeWindowForText(pLoginButton, true, false);
    EA::UTFWin::IWindow* pHelp = mpLoginLayout->FindWindowByID(0x5121ff8, true);
    if (pHelp) SPUIHelpers::AutoSizeWindowForText(pHelp, true, false);
    if (bOfflineAvailable)
      SPUIHelpers::AutoSizeWindowForText(mpLoginLayout->FindWindowByID(0x40e7fa8, true), false, false);
    else
      SPUIHelpers::AutoSizeWindowForText(pCancel, false, false);
    SPUIHelpers::AnchorWindowToWindow(pLoginButton, pCancel, 0x820, 0);
    if (mUser.length() == 0) {
      SPUIHelpers::BeginModal(pDialog, static_cast<EA::UTFWin::IModalWindowCallback*>(this), true);
      WindowManager()->SetFocus(0, mpLoginLayout->FindWindowByID(0x40cf1f8, true));
    } else {
      mpLoginLayout->FindWindowByID(0x40cf1f8, true)
          ->SetCaption(string16(string16::CtorSprintf(), L"%hs", mUser.c_str()).c_str());
      SPUIHelpers::BeginModal(pDialog, static_cast<EA::UTFWin::IModalWindowCallback*>(this), true);
      WindowManager()->SetFocus(0, mpLoginLayout->FindWindowByID(0x40cf200, true));
    }
  } else {
    delete mpLoginLayout;
    mpLoginLayout = 0;
  }
}

// @ 0x00608cc0
void cAuthManager::SavePrefs() {
  if (mbDontSavePrefs) return;
  EA::AutoRefCount<IPropertyList> pList;
  const uint32_t instance = EA::Hash::FNV1_String16(kLoginPrefsName, 0x811c9dc5, 1);
  PropertyManager()->GetPropertyList(instance, 0x11ac192, pList.AsOutParam());
  if (!pList) {
    pList = new ("Pollinator", 0, 0, 0, 0) cPropertyList();
    static_cast<cPropertyList*>(pList.mpObject)->mResourceKey = ResourceKey::Make(instance, 0xb1b104, 0x11ac192);
  }
  if (!mbPlayOffline) {
    {
      Property prop;
      prop.Set(0x12, 9, &mUser, 0x10, 1);
      pList->SetProperty(0x40512ef, &prop);
    }
    string8 encrypted;
    Encrypt(mPassword, encrypted);
    {
      Property prop;
      prop.Set(0x12, 9, &encrypted, 0x10, 1);
      pList->SetProperty(0x40512f4, &prop);
    }
  }
  if (mbSavedPrefsFlag) {
    Property prop;
    prop.SetValueBool(mbSavedPrefsFlag);
    pList->SetProperty(0x6390ede, &prop);
  }
  {
    Property prop;
    prop.SetValueBool(mbPlayOffline);
    pList->SetProperty(0x40e3d98, &prop);
  }
  {
    Property prop;
    prop.SetValueBool(mbPrompt);
    pList->SetProperty(0x440a514, &prop);
  }
  void* pSaveArea = GetSaveArea(0x11ac192);
  if (pSaveArea) {
    SaveNamedResource(pList, kLoginPrefsName, pSaveArea);
    EA::AutoRefCount<IPropertyList> pExisting;
    IPropertyManager* pPropMgr = PropertyManager();
    IPropertyList*& pExistingOut = pExisting.AsOutParam();
    pPropMgr->GetPropertyList(instance, 0x11ac192, pExistingOut);
    if (!pExisting) PropertyManager()->AddPropertyList(pList, instance, 0x11ac192);
  }
}

// @ 0x00608ff0
void cAuthManager::Login() {
  gpConnectingDialog = new (4, "UI/cConnectionDialog", GetDefaultAllocator()) cConnectingDialog();
  if (gpConnectingDialog->Init()) gpConnectingDialog->Show(mUser.c_str());
  Pollinator()->Login(mUser.c_str(), mPassword.c_str(), 0);
}

// @ 0x006090e0
void cAuthManager::ReadLoginLayout() {
  ShowLoginDialog(false);
  string8 user(string8::CtorSprintf(), "%ls", mpLoginLayout->FindWindowByID(0x40cf1f8, true)->GetCaption());
  string8 password(string8::CtorSprintf(), "%ls", mpLoginLayout->FindWindowByID(0x40cf200, true)->GetCaption());
  SetUserPassword(user, password);
  SetRememberPassword(!((mpLoginLayout->FindWindowByID(0x40cf210, true)->GetFlags() >> 2) & 1));
}

struct LoginInfoMessage {
  const wchar_t* mpScreenName;  // +0x0
  uint32_t pad4[5];
  uint64_t mnUserServerID;  // +0x18
};
struct DialogMessage {
  uint32_t pad[2];
  int mButton;  // +0x8
};

// @ 0x006091e0
bool cAuthManager::HandleMessage(uint32_t messageID, void* pMessage) {
  if (messageID == 0x4bf2fc9) {
    LoginInfoMessage* pInfo = (LoginInfoMessage*)pMessage;
    mnUserServerID = pInfo->mnUserServerID;
    mScreenName.sprintf("%ls", pInfo->mpScreenName);
    mnUserLocalID = EA::Hash::FNV1_String8(mScreenName.c_str(), 0x811c9dc5, 1);
    return true;
  }
  if (messageID == 0xce7afa41) {
    Logout();
    EA::IMessageServer* pServer = MessageServer();
    if (pServer) pServer->RemoveListener(static_cast<EA::Messaging::IHandler*>(this), 0xce7afa41, -9999);
    return false;
  }
  if (messageID == 0x5b85672) {
    DialogMessage* pDialogMsg = (DialogMessage*)pMessage;
    if (pDialogMsg->mButton == 0x1510d07) return true;
    switch (mDialogInProgress) {
      case 1:
        if (pDialogMsg->mButton == -0xf) FinishLogin(true);
        ShowLoginDialog(true);
        return true;
    }
  }
  return false;
}

// @ 0x006092b0
bool cAuthManager::HandleUIMessage(EA::UTFWin::IWindow* pWindow, const EA::UTFWin::Message& msg) {
  if (msg.mEventType == 0x287259f6) {
    const uint32_t id = msg.mpSource->GetControlID();
    if (id == 0x40cf208) {
      ReadLoginLayout();
      mpLoginLayout->FindWindowByID(0x40cf9b0, true)->SetFlag(1, false);
      Login();
      return true;
    }
    if (id == 0x40e7fa8 || id == 0x5091898) {
      EA::AutoRefCount<cOfflineConfirmationDialog> pDialog =
          new (4, "UI/cOfflineConfirmationDialog", GetDefaultAllocator()) cOfflineConfirmationDialog();
      if (pDialog->Init()) {
        FinishLogin(false);
        pDialog->SetCallback(this);
        return true;
      }
      return false;
    }
    if (id == 0x451a478) {
      EndLoginDialog();
      MessageServer()->PostMSG(0x5b96086, 0, 0);
      if (!IsRegistered()) pReg->Show(true);
      return true;
    }
    if (id == 0x5121ff8) {
      EA::AutoRefCount<cLoginHelpDialog> pDialog(new (4, "UI/cLoginHelpDialog", GetDefaultAllocator()) cLoginHelpDialog());
      pDialog->Show();
      FinishLogin(false);
      return true;
    }
  } else if (msg.mEventType == 1) {
    if (msg.mKey == 0xd) {
      ReadLoginLayout();
      mpLoginLayout->FindWindowByID(0x40cf9b0, true)->SetFlag(1, false);
      Login();
      return true;
    }
    if (msg.mKey == 0x42) return true;
  }
  return false;
}

}  // namespace Pollen
}  // namespace SP

// ---------------------------------------------------------------------------------------------
namespace EA {
namespace Thread {
template <typename T>
struct AtomicInt {
  AtomicInt() { _InterlockedExchange((volatile long*)&mValue, 0); }
  volatile T mValue;
};
}  // namespace Thread
namespace COM {
template <typename T>
class RefCountTemplate {
 public:
  virtual ~RefCountTemplate() {}
  T mRefCount;
};
}  // namespace COM
namespace Internet {
class IRequestResponseFilter : public COM::RefCountTemplate<Thread::AtomicInt<int> > {
 public:
  virtual void Filter(XHTML::Resource::Request* pRequest) = 0;
  void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
}  // namespace Internet
}  // namespace EA

namespace SP {
namespace Pollen {
class cCanvasResFilter : public EA::Internet::IRequestResponseFilter {
 public:
  cCanvasResFilter();
  virtual ~cCanvasResFilter() {}
  virtual void Filter(EA::XHTML::Resource::Request* pRequest);
  bool UpdateHeaderString();
  bool Init();
  bool mbInited;                // +0x8
  string8 mHeaderString;        // +0xc
};

// Sends the "BuddyMode" header (class name not in the PDB; guessed).
class cBuddyModeFilter : public EA::Internet::IRequestResponseFilter, public EA::Messaging::IHandler {
 public:
  cBuddyModeFilter();
  virtual ~cBuddyModeFilter() {}
  virtual void Filter(EA::XHTML::Resource::Request* pRequest);
  virtual bool HandleMessage(uint32_t messageID, void* pMessage);
  bool UpdateHeaderString();
  bool Init();
  bool mbInited;                // +0xc
  string8 mHeaderString;        // +0x10
};

// @ 0x00609460
void cCanvasResFilter::Filter(EA::XHTML::Resource::Request* pRequest) {
  pRequest->mHeaders.AddHeaderEntry("AppResolution", mHeaderString);
}

// @ 0x00609480
void cBuddyModeFilter::Filter(EA::XHTML::Resource::Request* pRequest) {
  pRequest->mHeaders.AddHeaderEntry("BuddyMode", mHeaderString);
}

// @ 0x006094a0
cCanvasResFilter::cCanvasResFilter() : mbInited(false) {}

// @ 0x006094e0
cBuddyModeFilter::cBuddyModeFilter() : mbInited(false) {}

// @ 0x00609540  (cCanvasResFilter scalar deleting destructor, emitted with the vtable)
// @ 0x00609580  (cBuddyModeFilter scalar deleting destructor, emitted with the vtable)

// @ 0x006095d0
bool cBuddyModeFilter::UpdateHeaderString() {
  if (ConfigManager()) {
    if (ConfigManager()->GetInt(0x5de7b4a) == 1)
      mHeaderString = "true";
    else
      mHeaderString = "false";
    return true;
  }
  return false;
}

// @ 0x00609630
bool cBuddyModeFilter::Init() {
  if (!mbInited) {
    UpdateHeaderString();
    EA::IMessageServer* pServer = EA::Messaging::GetServer();
    if (pServer) {
      pServer->AddListener(this, 0x5de7b4a);
      pServer->AddListener(this, 0x238de9c);
      mbInited = true;
    }
  }
  return mbInited;
}

// @ 0x00609690
bool cBuddyModeFilter::HandleMessage(uint32_t messageID, void* pMessage) {
  switch (messageID) {
    case 0x238de9c: {
      EA::IMessageServer* pServer = EA::Messaging::GetServer();
      if (pServer) {
        pServer->RemoveListener(static_cast<EA::Messaging::IHandler*>(this), 0x5de7b4a, -9999);
        pServer->RemoveListener(static_cast<EA::Messaging::IHandler*>(this), 0x238de9c, -9999);
        mbInited = false;
      }
      break;
    }
    case 0x5de7b4a:
      UpdateHeaderString();
      return true;
  }
  return true;
}

struct Rect {
  int left, top, right, bottom;
};
class ICanvas {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual void GetClientRect(Rect& r);  // +0x3c
};
ICanvas* Canvas();  // 0x0067dcf0

// @ 0x00609710
bool cCanvasResFilter::UpdateHeaderString() {
  ICanvas* pCanvas = Canvas();
  if (pCanvas) {
    Rect r;
    pCanvas->GetClientRect(r);
    mHeaderString.sprintf("%dx%d", r.right - r.left, r.bottom - r.top);
    return true;
  }
  return false;
}

// @ 0x00609760
bool cCanvasResFilter::Init() {
  if (!mbInited) {
    UpdateHeaderString();
    EA::Messaging::GetServer();
    mbInited = true;
  }
  return mbInited;
}

}  // namespace Pollen
}  // namespace SP
