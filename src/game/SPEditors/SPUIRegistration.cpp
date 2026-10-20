// src/game/SPEditors/SPUIRegistration.cpp -- migrated from slice(s) s00620bd0, s0061fbd0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUIRegistration.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Pollen/cRegistrationDialog.h"
#include "EA/UTFWin/CustomWinProc.h"
#include "EA/UTFWin/ISerializable.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/Message.h"
#include "EA/UTFWin/MultiHeapObject.h"
#include "eastl/allocator.h"
#include "SP/cPollinator.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "SP/cStringTokenTranslator.h"
#include "EA/UTFWinExtras/cXHTMLFrameSet.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" unsigned int __cdecl strlen(const char*);
extern char gEmptyString[];  // 0x01667bac (shared "" for char and wchar_t strings)
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
extern const wchar_t* gParamUserName;    // 0x01520a10
extern const wchar_t* gParamScreenName;  // 0x01520a14
extern const wchar_t* gParamPassword;    // 0x01520a18
extern void* gLocationChangeParam;       // 0x01520a0c
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(strlen)

// ---- items of slice s0061fbd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
struct ICoreAllocator;
void* operator new(unsigned int size, int alignment, const char* name, ICoreAllocator* pAllocator);
namespace eastl {
struct allocator_s0061_fbd0 {
  allocator_s0061_fbd0() {}
};
}
namespace eastl {
template <typename T>
inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
}
namespace eastl {
template <typename T>
inline unsigned int CharStrlen(const T* p) {
  const T* pCurrent = p;
  while (*pCurrent) ++pCurrent;
  return (unsigned int)(pCurrent - p);
}
}
namespace eastl {
int Compare(const char* p1, const char* p2, unsigned int n);  // FUN_00606ea0
}
namespace eastl {
template <typename I1, typename I2>
I1 search(I1 first1, I1 last1, I2 first2, I2 last2);  // 0x005e8ff0
}
namespace eastl {
template <typename T, typename A = allocator_s0061_fbd0>
struct basic_string_s0061_fbd0 {
  typedef unsigned int size_type;
  enum { npos = -1 };
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;

  basic_string_s0061_fbd0() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  basic_string_s0061_fbd0(const T* pBegin, const T* pEnd, const A& allocator_s0061_fbd0)
      : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator_s0061_fbd0) {
    RangeInitialize(pBegin, pEnd);
  }
  struct CtorSprintf {};
  basic_string_s0061_fbd0(CtorSprintf, const T* pFormat, ...);  // 0x00473020 (wchar_t), 0x00472f50 (char)
  basic_string_s0061_fbd0& sprintf(const T* pFormat, ...);       // 0x00472fe0 (char)
  // (out of line at 0x0057cb10 elsewhere; this TU inlines it with AllocateSelf expanded)
  basic_string_s0061_fbd0(const basic_string_s0061_fbd0& x) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(x.mAllocator) {
    RangeInitializeInl(x.mpBegin, x.mpEnd);
  }
  ~basic_string_s0061_fbd0() { DeallocateSelf(); }

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
  basic_string_s0061_fbd0& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0 (char), 0x00423650 (wchar_t)
  basic_string_s0061_fbd0& operator=(const T* p);  // 0x005c3d90 (wchar_t)
  basic_string_s0061_fbd0& assign(const T* p) { return assign(p, p + CharStrlen(p)); }
  basic_string_s0061_fbd0& operator=(const basic_string_s0061_fbd0& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  basic_string_s0061_fbd0& replace(size_type position, size_type n, const T* p);  // 0x005f8f80 (wchar_t)
  void Trim();                                                       // 0x00606e60 (wchar_t)

  static int compare(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2) {
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int nMin = min_alt(n1, n2);
    const int cmp = Compare(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
  }
  int compare(const T* p) const;
  basic_string_s0061_fbd0 substr(size_type position, size_type n) const;
  basic_string_s0061_fbd0 left(size_type n) const;
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
}
typedef eastl::basic_string_s0061_fbd0<char> string8;
typedef eastl::basic_string_s0061_fbd0<wchar_t> string16;
namespace EA {
namespace COM {
class IUnknown32_s0061_fbd0 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t type) const = 0;
  virtual void pvUnknown3();
  ~IUnknown32_s0061_fbd0() {}
};  // namespace COM
}
}
namespace EA {
template <typename T>
class RefCountVTemplate_s0061_fbd0 {
 public:
  RefCountVTemplate_s0061_fbd0() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s0061_fbd0() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
template <typename T>
class AutoRefCount_s0061_fbd0 {
 public:
  T* mpObject;
  AutoRefCount_s0061_fbd0() : mpObject(0) {}
  AutoRefCount_s0061_fbd0(T* pObject) : mpObject(pObject) {
    if (mpObject) mpObject->AddRef();
  }
  AutoRefCount_s0061_fbd0& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  ~AutoRefCount_s0061_fbd0() {
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
}
namespace EA {
namespace Messaging {
class IHandler_s0061_fbd0 {
 public:
  virtual ~IHandler_s0061_fbd0() {}
  virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
};  // namespace Messaging
}
}
namespace EA {
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMSG(uint32_t messageID, void* p1, void* p2);  // +0x14
  PV(6) PV(7)
  virtual void RegisterHandler(Messaging::IHandler_s0061_fbd0* pHandler, uint32_t messageID);  // +0x20
  virtual void AddListener(Messaging::IHandler_s0061_fbd0* pHandler, uint32_t messageID);  // +0x24
  PV(10)
  virtual void RemoveListener(Messaging::IHandler_s0061_fbd0* pHandler, uint32_t messageID, int priority);  // +0x2c
};
}
namespace EA {
namespace UTFWin {
class IWindow_s0061_fbd0;
}
}
namespace EA {
namespace UTFWin {
struct Message_s0061_fbd0 {
  IWindow_s0061_fbd0* mpSource;  // +0x0
  uint32_t pad4;
  uint32_t mEventType;  // +0x8
  uint32_t padc;
  uint32_t mKey;  // +0x10
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s0061_fbd0 {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2)
  virtual class IWinControl* QueryControl(uint32_t type);  // +0xc
  PV(4) PV(5) PV(6)
  virtual uint32_t GetControlID();  // +0x1c
  PV(8) PV(9) PV(10)
  virtual uint32_t GetFlags();  // +0x2c
  PV(12) PV(13)
  virtual const float* GetArea();  // +0x38
  virtual const wchar_t* GetCaption();  // +0x3c
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  PV(25) PV(26) PV(27)
  virtual void SetPosition(float x, float y);  // +0x70
  PV(29) PV(30)
  virtual void SetFlag(uint32_t flag, bool value);  // +0x7c
  virtual void SetCaption(const wchar_t* text);  // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45)
  PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(class IWinProc_s0061_fbd0* p);     // +0x104
  virtual void RemoveWinProc(class IWinProc_s0061_fbd0* p);  // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s0061_fbd0 : public COM::IUnknown32_s0061_fbd0 {
 public:
  virtual uint32_t GetEventFlags();
  virtual bool HandleUIMessage(IWindow_s0061_fbd0* pWindow, const Message_s0061_fbd0& msg) = 0;
};
}
}
namespace EA {
namespace UTFWin {
class IWinControl {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetFlag(uint32_t flag, bool value);  // +0x28
};
}
}
namespace EA {
namespace UTFWin {
class __declspec(novtable) IModalWindowCallback_s0061_fbd0 {
 public:
  virtual void pv0() = 0;
  virtual void OnModalEnd(IWindow_s0061_fbd0* pWindow, uint32_t id) = 0;
};
}
}
namespace EA {
namespace UTFWin {
class ISerializable_s0061_fbd0 {
 public:
  virtual void pv0();
};
}
}
namespace EA {
namespace UTFWin {
class MultiHeapObject_s0061_fbd0 {
 public:
  static void operator delete(void* p);  // 0x00951330
};
}
}
namespace EA {
namespace UTFWin {
class CustomWinProc_s0061_fbd0 : public IWinProc_s0061_fbd0, public ISerializable_s0061_fbd0, public MultiHeapObject_s0061_fbd0 {
 public:
  CustomWinProc_s0061_fbd0() : mRefCount(0) {}
  virtual ~CustomWinProc_s0061_fbd0() {}
  virtual int AddRef();
  virtual int Release();  // 0x0097da40 (EA::UTFWin::CustomWinProc::Release)
  virtual void* Cast(uint32_t type) const;
  bool HandleUIMessage(IWindow_s0061_fbd0* pWindow, const Message_s0061_fbd0& msg);  // 0x00950ef0
  int mRefCount;  // +0x8
};
}
}
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
class cSPUILayout_s0061_fbd0 {
 public:
  cSPUILayout_s0061_fbd0();           // 0x00810000
  virtual ~cSPUILayout_s0061_fbd0();
  bool Init(const ResourceKey& key, int a, uint32_t b);                // 0x008120d0
  EA::UTFWin::IWindow_s0061_fbd0* FindWindowByID(uint32_t id, bool recursive);    // 0x008105b0
  void Shutdown(bool b);                                               // 0x00811ad0
  uint32_t pad[5];
};
namespace SPUIHelpers {
bool BeginModal(EA::UTFWin::IWindow_s0061_fbd0* pWindow, int a, bool b);  // 0x008099a0
}
namespace SPUIHelpers {
void EndModal(EA::UTFWin::IWindow_s0061_fbd0* pWindow, uint32_t id, bool b);  // 0x00809c50
}
namespace SPUIHelpers {
bool BeginModal(EA::UTFWin::IWindow_s0061_fbd0* pWindow, EA::UTFWin::IModalWindowCallback_s0061_fbd0* pCallback, bool b);
}
namespace SPUIHelpers {
void AutoSizeWindowForText(EA::UTFWin::IWindow_s0061_fbd0* pWindow, bool a, bool b);  // 0x00806e40
}
namespace SPUIHelpers {
void AnchorWindowToWindow(EA::UTFWin::IWindow_s0061_fbd0* pWindow, EA::UTFWin::IWindow_s0061_fbd0* pAnchor, uint32_t flags, int a);  // 0x00807340
}
namespace SP {
EA::IMessageServer* MessageServer();          // 0x0067dcc0
}
namespace SP {
namespace Pollen {
bool GetURL(uint32_t id, string16& out);  // 0x006214c0
}
}
namespace SP {
namespace Pollen {
class IAuthManager : public EA::COM::IUnknown32_s0061_fbd0 {
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
}
}
namespace SP {
namespace Pollen {
IAuthManager* AuthManager();  // 0x00607a60
}
}
namespace EA {
namespace UTFWinExtras {
class cXHTMLFrameSet_s0061_fbd0 {
 public:
  cXHTMLFrameSet_s0061_fbd0(void* pCallback);  // 0x00996cc0
  virtual int AddRef();
  virtual int Release();
  void Shutdown();                                       // 0x00997140
  void SetEventIDs(int a, int b, int c, int d);          // 0x00996280
  bool Attach(EA::UTFWin::IWindow_s0061_fbd0* pWindow, uint32_t id);  // 0x009979f0
  void HandleLocationChange(int a, const wchar_t* url, void* p, int b);  // 0x00997730
  uint32_t pad[24];
};  // namespace UTFWinExtras
}
}
using EA::AutoRefCount_s0061_fbd0;
using EA::UTFWinExtras::cXHTMLFrameSet_s0061_fbd0;
struct UIRootState {
  uint8_t pad[0x118];
  int mbModalCursor;  // +0x118
};
struct UIRoot {
  uint8_t pad[0x3c];
  UIRootState* mpState;  // +0x3c
};
extern UIRoot* gpUIRoot;  // 0x015fd918
void FUN_00809930(bool b);
void FUN_00809950(EA::UTFWin::IWindow_s0061_fbd0* w);
namespace SP {
namespace Pollen {
using namespace EA;
}
}
namespace SP {
namespace Pollen {
using namespace EA::UTFWin;
}
}
namespace SP {
namespace Pollen {
class cRegistrationDialog_s0061_fbd0 : public IWinProc_s0061_fbd0,
                            public EA::Messaging::IHandler_s0061_fbd0,
                            public IModalWindowCallback_s0061_fbd0,
                            public EA::RefCountVTemplate_s0061_fbd0<int> {
 public:
  cRegistrationDialog_s0061_fbd0();
  virtual ~cRegistrationDialog_s0061_fbd0();
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t type) const;
  virtual bool HandleUIMessage(IWindow_s0061_fbd0* pWindow, const Message_s0061_fbd0& msg);
  virtual bool HandleMessage(uint32_t messageID, void* pMessage);
  virtual void OnModalEnd(IWindow_s0061_fbd0* pWindow, uint32_t id);

  void Show(bool b);              // 0x00620050
  void AutoSizeButtons();         // 0x006200c0
  void SetControlsEnabled(bool b);  // 0x00620110
  void SetButtonsEnabled(bool b);   // 0x006201a0
  __declspec(noinline) void End();  // 0x00620380
  void ConfirmLogin();            // 0x006205f0
  bool Show2(bool bEnterPressed);  // 0x006208c0
  static void FormParamCallback(const wchar_t* name, const wchar_t* value, cRegistrationDialog_s0061_fbd0* self);  // 0x00620b30 (SP::Pollen::cRegistrationDialog::FormParamCallback)

  cSPUILayout_s0061_fbd0 mLayout;                        // +0x14
  AutoRefCount_s0061_fbd0<cXHTMLFrameSet_s0061_fbd0> mpXHTMLFrameSet;  // +0x2c
  bool mbAutoExitAfterLogin;                  // +0x30
  string16 mUserName;                         // +0x34
  string16 mScreenName;                       // +0x44
  string16 mPassword;                         // +0x54
  bool mbEnterPressed;                        // +0x64
  bool mbFlag65;                              // +0x65
  int mState;                                 // +0x68
};
}
}
namespace eastl {
struct intrusive_list_node_s0061_fbd0 {
  intrusive_list_node_s0061_fbd0* mpNext;
  intrusive_list_node_s0061_fbd0* mpPrev;
};
}
namespace eastl {
struct intrusive_list_base_s0061_fbd0 {
  intrusive_list_node_s0061_fbd0 mAnchor;
  ~intrusive_list_base_s0061_fbd0();
};
}
namespace SP {
namespace Pollen {
class cCancelConfirmationDialog : public CustomWinProc_s0061_fbd0 {
 public:
  cCancelConfirmationDialog();
  virtual bool HandleUIMessage(IWindow_s0061_fbd0* pWindow, const Message_s0061_fbd0& msg);
  bool Init();                                   // 0x00620270
  void ShowModal(IModalWindowCallback_s0061_fbd0* pCallback);  // 0x00620020
  cSPUILayout_s0061_fbd0 mLayout;                           // +0xc
};
}
}
namespace SP {
namespace Pollen {
struct DomHook {  // eastl::intrusive_list_node
  DomHook* mpNext;
  DomHook* mpPrev;
};
}
}
namespace SP {
namespace Pollen {
struct DomNodeBase {
  virtual void pv0();
};
}
}
namespace SP {
namespace Pollen {
struct DomElement;
}
}
namespace SP {
namespace Pollen {
struct DomNode : DomNodeBase, DomHook {  // hook at +4
  int Type();              // 0x00fc7e50 (EA::XHTML::DOM::Node::Type)
  DomElement* AsElement();  // 0x008e52f0
};
}
}
namespace SP {
namespace Pollen {
struct DomNodeList {
  uint32_t pad;
  DomHook mAnchor;  // +4 relative to the list at element+0x14
};
}
}
namespace SP {
namespace Pollen {
struct DomElement : DomNode {
  uint32_t pad1[(0x14 - 0xc) / 4];
  DomNodeList mChildren;  // +0x14
  uint32_t pad2[(0x28 - 0x20) / 4];
  int mTag;  // +0x28
};
}
}
namespace SP {
namespace Pollen {
struct XHTMLHandlerBase {
  XHTMLHandlerBase(void* a, void* b, void* c);  // 0x008e4400
  virtual ~XHTMLHandlerBase();
  uint32_t pad[0x44 / 4 - 1];
};
}
}
namespace SP {
namespace Pollen {
class cXHTMLRegistrationHandler : public XHTMLHandlerBase {
 public:
  cXHTMLRegistrationHandler(void* a, void* b, void* c);
  DomElement* FindFirstTaggedElement(DomElement* e);  // 0x00620690
  uint32_t mUnk44;  // +0x44
};
}
}
// ---- items of slice s0061fbd0 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// ---- items of slice s00620bd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl FUN_00620050(int b);                                                  // 0x620050
static inline void** Vt(void* p) { return *(void***)p; }
struct cSPUILayout_s0062_0bd0 {
  void* FindWindowByID(uint32_t id, bool recursive);   // 0x8105b0
};
struct cXHTMLFrameSet {
  void* GetFrame(const void* name);
  bool  HandleLocationChange(int a, const void* url, const void* p, int b);
  bool  HandleFormSubmit(void* frame, int a);
  int   AddRef();
  int   Release();
};
struct cRegDialog {
  char pad00[0x14];
  cSPUILayout_s0062_0bd0 mLayout;             // +0x14
  char pad18[0x14];
  cXHTMLFrameSet* mpFrameSet;      // +0x2c
  bool  mbFlag30;                  // +0x30
  char pad31[0x34];
  char  mbFlag65;                  // +0x65
  int   mState;                    // +0x68
  char  mbKey64;                   // +0x64
  void SubmitRegistrationForm();   // 0x620bd0
  void ConfirmLogin();             // 0x6205f0
  void DialogUiNotify();           // 0x620e50
};
struct DialogSub {                 // this = cRegDialog + 8
  char pad0[0xc];
  cSPUILayout_s0062_0bd0* mpLayout;           // +0xc
  char pad10[0x50];
  int  mState;                     // +0x60
  void OnModalEnd(void* pWindow, int id);  // 0x620dc0
};
// ---- items of slice s00620bd0 end

// @ 0x006200c0
namespace SP { namespace Pollen {
void cRegistrationDialog_s0061_fbd0::AutoSizeButtons()
{
  IWindow_s0061_fbd0* w = mLayout.FindWindowByID(0x519e168, true);
  if (w) {
    SPUIHelpers::AutoSizeWindowForText(w, true, false);
    IWindow_s0061_fbd0* anchor = mLayout.FindWindowByID(0x519e308, true);
    if (anchor) SPUIHelpers::AnchorWindowToWindow(w, anchor, 0x820, 0);
  }
}
}}  // namespace SP::Pollen

// @ 0x00620110
namespace SP { namespace Pollen {
void cRegistrationDialog_s0061_fbd0::SetControlsEnabled(bool b)
{
  IWindow_s0061_fbd0* w = mLayout.FindWindowByID(0x6555818, true);
  if (gpUIRoot->mpState->mbModalCursor) {
    if (w) w->SetFlag(1, false);
  } else {
    if (w) w->SetFlag(1, b);
  }
  IWindow_s0061_fbd0* w2 = mLayout.FindWindowByID(0x519e168, true);
  if (w2) w2->SetFlag(1, b);
  IWindow_s0061_fbd0* w3 = mLayout.FindWindowByID(0x519e308, true);
  if (w3) w3->SetFlag(1, b);
}
}}  // namespace SP::Pollen

// @ 0x006201a0
namespace SP { namespace Pollen {
void cRegistrationDialog_s0061_fbd0::SetButtonsEnabled(bool b)
{
  IWindow_s0061_fbd0* w = mLayout.FindWindowByID(0x519d9b8, true);
  if (w) w->SetFlag(2, b);
  IWindow_s0061_fbd0* w2 = mLayout.FindWindowByID(0x519e168, true);
  if (w2) w2->SetFlag(2, b);
  IWindow_s0061_fbd0* w3 = mLayout.FindWindowByID(0xfffffff2, true);
  if (w3) w3->SetFlag(2, b);
  IWindow_s0061_fbd0* w4 = mLayout.FindWindowByID(0x65d20a8, true);
  if (w4) w4->SetFlag(2, b);
}
}}  // namespace SP::Pollen

// @ 0x00620230
namespace eastl {
intrusive_list_base_s0061_fbd0::~intrusive_list_base_s0061_fbd0()
{
  intrusive_list_node_s0061_fbd0* p = mAnchor.mpNext;
  while (p != &mAnchor) {
    intrusive_list_node_s0061_fbd0* pNext = p->mpNext;
    p->mpPrev = 0;
    p->mpNext = 0;
    p = pNext;
  }
  mAnchor.mpPrev = 0;
  mAnchor.mpNext = 0;
}
}  // namespace eastl

// @ 0x00620270
namespace SP { namespace Pollen {
bool cCancelConfirmationDialog::Init()
{
  ResourceKey key = ResourceKey::Make(0x6b5d940, 0x510a95b, 0x40464100);
  if (!mLayout.Init(key, 1, 0x5b598f7)) return false;
  IWindow_s0061_fbd0* wOk = mLayout.FindWindowByID(0xfffffff1, true);
  if (wOk) {
    SPUIHelpers::AutoSizeWindowForText(wOk, true, false);
    IWindow_s0061_fbd0* wCancel = mLayout.FindWindowByID(0xfffffff2, true);
    if (wCancel) {
      SPUIHelpers::AutoSizeWindowForText(wCancel, false, false);
      const float* rc = wCancel->GetArea();
      float width = rc[2] - rc[0];
      const float* rcOk = wOk->GetArea();
      float x = rcOk[0] - width;
      wCancel->SetPosition(x, rc[1]);
    }
  }
  IWindow_s0061_fbd0* w = mLayout.FindWindowByID(0x65cf488, true);
  if (w) {
    w->AddWinProc(this);
    return true;
  }
  mLayout.Shutdown(true);
  return false;
}
}}  // namespace SP::Pollen

// @ 0x00620380
namespace SP { namespace Pollen {
void cRegistrationDialog_s0061_fbd0::End()
{
  Messaging::IHandler_s0061_fbd0* h1 = static_cast<Messaging::IHandler_s0061_fbd0*>(this);
  MessageServer()->RemoveListener(h1, 0x44db12e, -9999);
  Messaging::IHandler_s0061_fbd0* h2 = static_cast<Messaging::IHandler_s0061_fbd0*>(this);
  MessageServer()->RemoveListener(h2, 0x238de9c, -9999);
  if (mpXHTMLFrameSet.mpObject) {
    mpXHTMLFrameSet.mpObject->Shutdown();
    if (mpXHTMLFrameSet.mpObject) {
      cXHTMLFrameSet_s0061_fbd0* p = mpXHTMLFrameSet.mpObject;
      mpXHTMLFrameSet.mpObject = 0;
      p->Release();
    }
  }
  IWindow_s0061_fbd0* w = mLayout.FindWindowByID(0xffffffff, true);
  if (w) {
    if (gpUIRoot->mpState->mbModalCursor) {
      FUN_00809950(0);
      FUN_00809930(false);
    }
    w->RemoveWinProc(this);
    SPUIHelpers::EndModal(w, 0, true);
  }
  MessageServer()->PostMSG(0x5dd52c7, 0, 0);
  mLayout.Shutdown(true);
}
}}  // namespace SP::Pollen

// @ 0x00620470
namespace SP { namespace Pollen {
bool cRegistrationDialog_s0061_fbd0::HandleMessage(uint32_t messageID, void* pMessage)
{
  if (messageID == 0x44db12e) {
    if (mbAutoExitAfterLogin && pMessage) {
      End();
      return false;
    }
  } else if (messageID == 0x238de9c) {
    End();
  }
  return false;
}
}}  // namespace SP::Pollen

// @ 0x006204b0
namespace SP { namespace Pollen {
cCancelConfirmationDialog::cCancelConfirmationDialog()
{}
}}  // namespace SP::Pollen

// @ 0x006204e0
namespace SP { namespace Pollen {
bool cCancelConfirmationDialog::HandleUIMessage(IWindow_s0061_fbd0* pWindow, const Message_s0061_fbd0& msg)
{
  if (pWindow->GetControlID() == 0x65cf488 && msg.mEventType == 0x287259f6) {
    if (msg.mpSource->GetControlID() == 0xfffffff1 || msg.mpSource->GetControlID() == 0xfffffff2) {
      IAuthManager* auth = AuthManager();
      if (msg.mpSource->GetControlID() == 0xfffffff1) {
        IWindow_s0061_fbd0* w = mLayout.FindWindowByID(0x65cf570, true);
        if (w) auth->SetRememberPassword(!((w->GetFlags() >> 2) & 1));
      }
      if (msg.mpSource->GetControlID() == 0xfffffff2) auth->FinishLogin(true);
      IWindow_s0061_fbd0* w2 = mLayout.FindWindowByID(0x65cf488, true);
      if (w2) {
        SPUIHelpers::EndModal(w2, msg.mpSource->GetControlID(), true);
        w2->RemoveWinProc(this);
      }
      mLayout.Shutdown(true);
      return true;
    }
  }
  return false;
}
}}  // namespace SP::Pollen

// @ 0x006205f0
namespace SP { namespace Pollen {
void cRegistrationDialog_s0061_fbd0::ConfirmLogin()
{
  IAuthManager* auth = AuthManager();
  auth->ShowLoginDialog(true);
  auth->SavePrefs();
  if (gpUIRoot->mpState->mbModalCursor) {
    FUN_00809950(0);
    FUN_00809930(false);
  }
  MessageServer()->PostMSG(0x5b98f52, 0, 0);
  End();
}
}}  // namespace SP::Pollen

// @ 0x00620690
namespace SP { namespace Pollen {
DomElement* cXHTMLRegistrationHandler::FindFirstTaggedElement(DomElement* e)
{
  if (e->mTag != 0x15) {
    DomNode* n = static_cast<DomNode*>(e->mChildren.mAnchor.mpNext);
    DomNode* end = (DomNode*)&e->mChildren;
    while (n != end) {
      if (n->Type() == 1) {
        DomElement* r = FindFirstTaggedElement(n->AsElement());
        if (r) return r;
      }
      n = static_cast<DomNode*>(n->mpNext);
    }
    return 0;
  }
  return e;
}
}}  // namespace SP::Pollen

// @ 0x006206f0
namespace SP { namespace Pollen {
cXHTMLRegistrationHandler::cXHTMLRegistrationHandler(void* a, void* b, void* c)
: XHTMLHandlerBase(a, b, c), mUnk44(0) {}
}}  // namespace SP::Pollen

// @ 0x00620740
namespace SP { namespace Pollen {
cRegistrationDialog_s0061_fbd0::cRegistrationDialog_s0061_fbd0()
: mbAutoExitAfterLogin(true), mbEnterPressed(false), mbFlag65(false), mState(0) {}
}}  // namespace SP::Pollen

// @ 0x006207f0
namespace SP { namespace Pollen {
cRegistrationDialog_s0061_fbd0::~cRegistrationDialog_s0061_fbd0()
{}
}}  // namespace SP::Pollen

// @ 0x006208c0
namespace SP { namespace Pollen {
bool cRegistrationDialog_s0061_fbd0::Show2(bool bEnterPressed)
{
  Messaging::IHandler_s0061_fbd0* h1 = static_cast<Messaging::IHandler_s0061_fbd0*>(this);
  MessageServer()->RegisterHandler(h1, 0x44db12e);
  Messaging::IHandler_s0061_fbd0* h2 = static_cast<Messaging::IHandler_s0061_fbd0*>(this);
  MessageServer()->RegisterHandler(h2, 0x238de9c);
  {
    ResourceKey key = ResourceKey::Make(0x34a6339e, 0x510a95b, 0x40464100);
    if (!mLayout.Init(key, 0, 0x5b598f7)) return false;
  }
  mbFlag65 = bEnterPressed;
  IWindow_s0061_fbd0* w = mLayout.FindWindowByID(0xffffffff, true);
  if (!w) return false;
  w->AddWinProc(this);
  mpXHTMLFrameSet = new ("Pollinator", 0, 0, 0, 0) cXHTMLFrameSet_s0061_fbd0((void*)0x623f40);
  mpXHTMLFrameSet.mpObject->SetEventIDs(0x1002, 0x1006, 0x1003, 0x1024);
  if (mpXHTMLFrameSet.mpObject->Attach(w, 0x451a4c0)) {
    MessageServer()->PostMSG(0x5bd6378, 0, 0);
    SPUIHelpers::BeginModal(w, 0, true);
    if (gpUIRoot->mpState->mbModalCursor) {
      FUN_00809950(w);
      FUN_00809930(true);
      IWindow_s0061_fbd0* w2 = mLayout.FindWindowByID(0x6555818, true);
      if (w2) w2->SetFlag(1, false);
    }
    IWindow_s0061_fbd0* w3 = mLayout.FindWindowByID(0x519d9b8, true);
    if (w3) w3->SetFlag(1, true);
    IWindow_s0061_fbd0* w4 = mLayout.FindWindowByID(0x65d20a8, true);
    if (w4) w4->SetFlag(1, false);
    AutoSizeButtons();
    string16 url;
    GetURL(0x538766b, url);
    mpXHTMLFrameSet.mpObject->HandleLocationChange(0, url.mpBegin, gLocationChangeParam, 0);
    return true;
  }
  if (mpXHTMLFrameSet.mpObject) {
    cXHTMLFrameSet_s0061_fbd0* p = mpXHTMLFrameSet.mpObject;
    mpXHTMLFrameSet.mpObject = 0;
    p->Release();
  }
  return false;
}
}}  // namespace SP::Pollen

// @ 0x00620b30
namespace SP { namespace Pollen {
void cRegistrationDialog_s0061_fbd0::FormParamCallback(const wchar_t* name, const wchar_t* value, cRegistrationDialog_s0061_fbd0* self)
{
  if (name) {
    if (_wcsicmp(name, gParamUserName) == 0) {
      self->mUserName.assign(value);
    } else if (_wcsicmp(name, gParamScreenName) == 0) {
      self->mScreenName = value;
    } else if (_wcsicmp(name, gParamPassword) == 0) {
      self->mPassword = value;
    }
  }
}
}}  // namespace SP::Pollen

// @ 0x00620dc0
void DialogSub::OnModalEnd(void* pWindow, int id)
{
  DialogSub* self = this;
  if (self->mState == 1) {
    if (id == -0xf) {
      ((cRegDialog*)((char*)self - 8))->ConfirmLogin();
      self->mState = 0;
      return;
    }
  } else if (self->mState == 2) {
    if (id == 0x5107b1a) {
      ((cRegDialog*)((char*)self - 8))->SubmitRegistrationForm();
      self->mState = 0;
      return;
    }
    void* w = self->mpLayout->FindWindowByID(0x6555770, true);
    if (w) {
      void* c = ((void*(__thiscall*)(void*, uint32_t))Vt(w)[3])(w, 0x8ed27e7a);  // +0xc
      if (c) ((void(__thiscall*)(void*, int, int))Vt(c)[10])(c, 4, 0);           // +0x28
    }
  }
  self->mState = 0;
  (void)pWindow;
}

// @ 0x00620ef0
int TOSDialog_DoMessage(int param_1, void* param_2, int* msg)
{
  int type = msg[2];
  if (type == 0x3326e8a) return 1;
  if (type == 0x51a1a2d) return 1;
  if (type == 0x43b0aee) return 1;
  if (type == 0x287259f6) {
    int code = ((int(__thiscall*)(int))Vt((void*)*msg)[7])(*msg);   // +0x1c
    if (code == -0xe) {
      int sub = ((int(__thiscall*)(int))Vt((void*)*msg)[8])(*msg);  // +0x20
      (void)sub;
      ((cRegDialog*)param_1)->ConfirmLogin();
      return 1;
    }
    if (code == 0x519d9b8) {
      ((cRegDialog*)param_1)->DialogUiNotify();
      return 1;
    }
    if (code == 0x519e168) {
      *(uint8_t*)(param_1 + 0x30) = 1;
      FUN_00620050(0);
      return 1;
    }
    if (code == 0x65d20a8) return 1;
  }
  (void)param_2;
  return 0;
}
