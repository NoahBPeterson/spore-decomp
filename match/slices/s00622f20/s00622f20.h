// Declarations for the Pollen XHTML window (cXHTMLWin) slice.
// Declarations shared with s006087b0 (cAuthManager). Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#pragma once
#include "types.h"

#define PV(n) virtual void pv##n();

extern "C" void EASTL_allocator_deallocate(void* p);
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
  basic_string& operator=(const T* p);  // 0x005c3d90 (wchar_t)
  basic_string& assign(const T* p) { return assign(p, p + CharStrlen(p)); }
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
  RefCountVTemplate() : mRefCount(0) {}
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
  PV(6) PV(7)
  virtual void RegisterHandler(Messaging::IHandler* pHandler, uint32_t messageID);  // +0x20
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
struct SPPoint {
  float x, y;
  SPPoint() {}
  SPPoint(float x_, float y_) : x(x_), y(y_) {}
  SPPoint(const SPPoint& p) : x(p.x), y(p.y) {}
};
struct IWindowChildIter {  // eastl::intrusive_list iterator (value = node pointer)
  void* mpNode;
};
class IWindow {
 public:
  virtual int AddRef();                                    // +0
  virtual int Release();                                   // +4
  PV(2)
  virtual void* Cast(uint32_t type);                       // +0xc
  virtual IWindow* GetParent();                            // +0x10
  PV(5) PV(6)
  virtual uint32_t GetControlID();                         // +0x1c
  virtual uint32_t GetCommandID();                         // +0x20
  PV(9)
  virtual uint32_t GetFlags();                             // +0x28
  PV(11) PV(12)
  virtual const float* GetArea();                          // +0x34
  virtual const float* GetRealArea();                      // +0x38
  virtual const wchar_t* GetCaption();                     // +0x3c
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  PV(25)
  virtual void SetSize(float w, float h);                  // +0x68
  PV(27)
  virtual void SetPosition(float x, float y);              // +0x70
  PV(29) PV(30)
  virtual void SetFlag(uint32_t flag, bool value);         // +0x7c
  virtual void SetCaption(const wchar_t* text);            // +0x80
  PV(33) PV(34) PV(35)
  virtual int Invalidate();                                // +0x90
  PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
  virtual bool ToLocalCoordinates2(SPPoint globalPos, SPPoint* pOut);  // +0xc8
  virtual IWindowChildIter GetChildrenBegin();             // +0xcc
  virtual IWindowChildIter GetChildrenEnd();               // +0xd0
  PV(53) PV(54) PV(55)
  virtual void DisposeWindowFamily(IWindow* pChild);       // +0xe0
  PV(57) PV(58) PV(59) PV(60) PV(61) PV(62)
  virtual bool IsEnabled(int index);                       // +0xfc
  PV(64)
  virtual void AddWinProc(class IWinProc* p);              // +0x104
  virtual void RemoveWinProc(class IWinProc* p);           // +0x108
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
class MultiHeapObject {
 public:
  static void operator delete(void* p);  // 0x00951330
};
class CustomWinProc : public IWinProc, public ISerializable, public MultiHeapObject {
 public:
  CustomWinProc() : mRefCount(0) {}
  virtual ~CustomWinProc() {}
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
  virtual int AddRef();
  virtual int Release();
  bool SetVisibility(bool b);                                                    // 0x00810590
  void SetParentWin(EA::UTFWin::IWindow* pParent, bool b, uint32_t id);          // 0x008121b0
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

// ---------------------------------------------------------------------------------------------
namespace Pollen {
bool GetURL(uint32_t id, string16& out);  // 0x006214c0
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
  virtual bool GetRememberPassword() = 0;        // 11 +0x2c
  virtual const string8& GetUser() = 0;          // 12 +0x30
  virtual const string8& GetPassword() = 0;      // 13 +0x34
  virtual void pv14();
  virtual void pv15();
  virtual void pv16();
  virtual void pv17();
  virtual void ShowLoginLayout(bool bOfflineAvailable) = 0;  // 18
  virtual void Login() = 0;                                  // 19 +0x4c
  virtual void ProcessLoginResults(short result) = 0;        // 20 +0x50
  virtual void SavePrefs() = 0;                              // 21 +0x54
  virtual bool IsRegistered() = 0;                           // 22 +0x58
  virtual void FinishLogin(bool b) = 0;                      // 23 +0x5c
};
IAuthManager* AuthManager();  // 0x00607a60
}  // namespace Pollen
}  // namespace SP
