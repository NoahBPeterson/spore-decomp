// src/game/SPEditors/SPAuthentication.cpp -- migrated from slice(s) s006087b0, s00607800, s006068c0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPAuthentication.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Pollen/cAuthManager.h"
#include "SP/cSPPaletteItemUIOneClickPaint.h"
#include "SP/FunctionalMatch/Constraint.h"
#include "EA/DateTime/DateTime.h"
#include "EA/UTFWin/IModalWindowCallback.h"
#include "EA/UTFWin/ISerializable.h"
#include "EA/UTFWin/CustomWindow.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cPollinator.h"
#include "SP/Pollen/cRegistrationDialog.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "EA/Variant.h"
#include "SP/cStringTokenTranslator.h"
#include "EA/Audio/ConfigurationAggregate.h"
#include "EA/Internet/HTTPHeaders.h"
#include "EA/Internet/IRequestResponseFilter.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/Message.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cPropertyList.h"
#include "cSPVector4.h"
#include "EA/Messaging/IHandler.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __cdecl toupper(int c);
extern "C" __declspec(dllimport) int __cdecl tolower(int c);

// ---- items of slice s006068c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);
void operator delete(void* p);
inline void* operator new(size_t, void* p) { return p; }
struct ResourceKey {
  uint32_t mInstance;  // +0x0
  uint32_t mType;      // +0x4
  uint32_t mGroup;     // +0x8
  ResourceKey() : mInstance(0), mType(0), mGroup(0) {}
  ResourceKey(uint32_t i, uint32_t t, uint32_t g) : mInstance(i), mType(t), mGroup(g) {}
};
namespace EA {
template <typename T>
class AutoRefCount_s0060_68c0 {
 public:
  T* mpObject;
  AutoRefCount_s0060_68c0() : mpObject(0) {}
  ~AutoRefCount_s0060_68c0() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s0060_68c0& operator=(T* pObject) {
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
}
namespace EA {
namespace UTFWin {
struct Rect {
  float left, top, right, bottom;
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s0060_68c0;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s0060_68c0 {
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
  virtual IWindow_s0060_68c0* FindWindowByID(uint32_t controlID, bool recursive);  // +0xf0
  PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s0060_68c0* proc);               // +0x104
  virtual void RemoveWinProc(IWinProc_s0060_68c0* proc);            // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class __declspec(novtable) IWinProc_s0060_68c0 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};
}
}
namespace EA {
namespace UTFWin {
class ISerializable_s0060_68c0 {
 public:
  virtual bool Serialize(void* stream);
};
}
}
namespace EA {
namespace UTFWin {
class MultiHeapObject_s0060_68c0 {};
}
}
namespace EA {
namespace UTFWin {
class __declspec(novtable) CustomWinProc_s0060_68c0 : public IWinProc_s0060_68c0, public ISerializable_s0060_68c0, public MultiHeapObject_s0060_68c0 {
 public:
  CustomWinProc_s0060_68c0() : mRefCount(0) {}
  int mRefCount;  // +0x8
};
}
}
namespace EA {
namespace UTFWin {
class IModalWindowCallback_s0060_68c0 {
 public:
  virtual void OnModalWindowEnd(IWindow_s0060_68c0* window, uint32_t result);
};
}
}
namespace EA {
namespace Messaging {
class IHandler_s0060_68c0 {
 public:
  virtual bool HandleMessage(uint32_t messageID, void* message);
};
}
}
namespace EA {
namespace Messaging {
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMSG(uint32_t messageID, void* data, void* source);               // +0x14
  PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void RemoveHandler(IHandler_s0060_68c0* handler, uint32_t messageID, int priority);  // +0x2c
};
}
}
using EA::AutoRefCount_s0060_68c0;
using EA::UTFWin::IWindow_s0060_68c0;
class cSPUILayout_s0060_68c0 {
 public:
  cSPUILayout_s0060_68c0();                                    // 0x810000
  virtual ~cSPUILayout_s0060_68c0();
  virtual int AddRef();
  virtual int Release();
  bool Init(const ResourceKey& key, bool b, uint32_t groupID);  // 0x008120d0 (cSPUILayout::Init)
  IWindow_s0060_68c0* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
  void Shutdown(bool b);  // 0x00811ad0 (cSPUILayout::Shutdown)
  uint32_t pad[2];
};
namespace SPUIHelpers {
void AutoSizeWindowForText(IWindow_s0060_68c0* window, int a, int b);
}
namespace SPUIHelpers {
void BeginModal(IWindow_s0060_68c0* window, EA::UTFWin::IModalWindowCallback_s0060_68c0* callback, bool b);
}
namespace SPUIHelpers {
void EndModal(IWindow_s0060_68c0* window, EA::UTFWin::IModalWindowCallback_s0060_68c0* callback, bool b);
}
namespace SPUIHelpers {
float GetElapsedSeconds();
}
namespace SPUIHelpers {
void SetWindowRotation(IWindow_s0060_68c0* window, const void* rotation);  // 0x808230
}
namespace SPUIHelpers {
void ShowErrorDialog(int a, const void* key);                   // 0x809db0
}
namespace eastl {
template <typename T>
class basic_string_s0060_68c0 {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  uint32_t mAllocator;
  basic_string_s0060_68c0();
  ~basic_string_s0060_68c0() {
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
}
namespace eastl {
extern wchar_t gEmptyString16[2];  // 0x01667BAC
}
namespace eastl {
template <> inline basic_string_s0060_68c0<wchar_t>::basic_string_s0060_68c0()
    : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
}
namespace eastl {
inline wchar_t CharToUpper(wchar_t c) {
  if ((unsigned)c <= 0xff) return (wchar_t)toupper((unsigned char)c);
  return c;
}
}
namespace eastl {
template void basic_string_s0060_68c0<wchar_t>::make_upper();
}
namespace eastl {
inline char CharToLower(char c) { return (char)tolower((unsigned char)c); }
}
namespace eastl {
template size_t basic_string_s0060_68c0<char>::find(char, size_t) const;
}
namespace SP {
EA::Messaging::IMessageServer* MessageServer();
}
namespace SP {
class IConfigManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
  virtual int GetValue(uint32_t id);                                  // +0x30
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
  virtual void GetString(uint32_t id, eastl::basic_string_s0060_68c0<char>& s);  // +0x4c
};
}
namespace SP {
IConfigManager* ConfigManager();
}
namespace SP {
class cDirectPropertyList_s0060_68c0 {
 public:
  int GetIntProperty(uint32_t id);  // 0x6a2660
  char pad[0x3c];
  struct Values {
    char pad[0x118];
    int mbGalacticAdventures;  // +0x118
  }* mpValues;                 // +0x3c
};
}
namespace SP {
extern cDirectPropertyList_s0060_68c0* sAppProperties;  // 0x15fd918
}
namespace SP {
class cPollinator_s0060_68c0 {
 public:
  void SetEnabledState(uint32_t state);  // 0x0060cec0 (SP::cPollinator::SetEnabledState)
};
}
namespace SP {
cPollinator_s0060_68c0* Pollinator();  // 0x67cb30
}
namespace SP {
class IXHTMLResources {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual void RemoveListener(void* listener);  // +0x20
};
}
namespace SP {
class IXHTMLManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual IXHTMLResources* GetResources();  // +0x20
};
}
namespace SP {
IXHTMLManager* XHTMLManager();  // 0x67de40
}
uint32_t FNVHash(const char* s, uint32_t seed, bool lower);  // 0x932e80
namespace SP {
namespace Pollen {
namespace {
class cConnectingDialog : public EA::UTFWin::CustomWinProc_s0060_68c0 {
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
  AutoRefCount_s0060_68c0<IWindow_s0060_68c0> mpWindow;  // +0xc
  float mStartTime;                // +0x10
  float mTimeout;                  // +0x14
  bool mEndConnecting;             // +0x18
  bool mEndConnected;              // +0x19
  float mRotation[4];              // +0x1c
  cSPUILayout_s0060_68c0 mLayout;             // +0x2c
};

class cOfflineConfirmationDialog : public EA::UTFWin::CustomWinProc_s0060_68c0 {
 public:
  cOfflineConfirmationDialog();
  bool Init();
  void Show(EA::UTFWin::IModalWindowCallback_s0060_68c0* callback);
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  cSPUILayout_s0060_68c0 mLayout;  // +0xc
};

class cLoginHelpDialog : public EA::UTFWin::CustomWinProc_s0060_68c0 {
 public:
  cLoginHelpDialog();
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  bool IsReturnKey(void* a, void* b, int key, void* c);
  cSPUILayout_s0060_68c0 mLayout;  // +0xc
};
}  // namespace
}
}
namespace SP {
namespace Pollen {
class cString {
 public:
  cString(uint32_t instanceID, uint32_t groupID, const wchar_t* defaultText);  // 0x6b5770
  ~cString();                                                                  // 0x6b5240
  const wchar_t* c_str();                                                      // 0x6b55c0
  uint32_t pad[5];
};
}
}
namespace SP {
namespace Pollen {
bool IsFeatureEnabled(int feature);  // 0x685520
}
}
namespace SP {
namespace Pollen {
class cRegistrationDialog_s0060_68c0 {
 public:
  cRegistrationDialog_s0060_68c0();  // 0x620740
  virtual int AddRef();
  virtual int Release();
  void Show(bool b);      // 0x6208c0
  char pad[0x6c - 4];
};
}
}
namespace SP {
namespace Pollen {
struct cAuthBase0c {
  virtual void v0c();
  uint32_t m10;
};
}
}
namespace SP {
namespace Pollen {
struct cAuthBase14 {
  virtual void v14();
  uint32_t m18;
};
}
}
namespace SP {
namespace Pollen {
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
}
}
namespace SP {
namespace Pollen {
class cAuthManager_s0060_68c0 : public EA::UTFWin::IWinProc_s0060_68c0,
                     public EA::UTFWin::IModalWindowCallback_s0060_68c0,
                     public EA::Messaging::IHandler_s0060_68c0,
                     public cAuthBase0c,
                     public cAuthBase14,
                     public IAuthenticationService {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  void* AsInterface(uint32_t typeID);  // 0x00606d00 (SP::Pollen::cAuthManager::AsInterface)
  void EndLoginDialog();  // 0x00606d80 (SP::Pollen::cAuthManager::EndLoginDialog)
  void SetOfflineUserID();  // 0x006072d0 (SP::Pollen::cAuthManager::SetOfflineUserID)
  void ShowLoginDialog(bool b);
  void InitialLogin();
  virtual void OnModalWindowEnd(IWindow_s0060_68c0* window, uint32_t result);
  virtual uint64_t GetUserServerID();
  virtual void SetLoginDialogVisible(bool visible);
  virtual void SetPlayOffline(bool offline);
  virtual void ShowLogin();
  virtual bool Shutdown();

  eastl::basic_string_s0060_68c0<char> mUser;        // +0x20
  eastl::basic_string_s0060_68c0<char> mPassword;    // +0x30
  eastl::basic_string_s0060_68c0<char> mScreenName;  // +0x40
  uint64_t mnUserServerID;                // +0x50
  uint32_t mnUserLocalID;                 // +0x58
  bool mbPlayOffline;                     // +0x5c
  bool mbPrompt;                          // +0x5d
  cSPUILayout_s0060_68c0* mpLoginLayout;             // +0x60
  bool mbDontSavePrefs;                   // +0x64
  int mDialogInProgress;                  // +0x68
  AutoRefCount_s0060_68c0<cRegistrationDialog_s0060_68c0> pReg; // +0x6c
};
}
}
namespace SP {
namespace Pollen {
static AutoRefCount_s0060_68c0<cConnectingDialog> sConnectingDialog;  // 0x15f3670
}
}
namespace SP {
namespace Pollen {
static AutoRefCount_s0060_68c0<cAuthManager_s0060_68c0> sAuthManager;  // 0x15f3814
}
}
namespace SP {
namespace Pollen {
class IUnknownCast {
 public:
  PV(0) PV(1) PV(2)
  virtual void* Cast(uint32_t typeID);  // +0xc
};
}
}
// Retail's scalar deleting dtor stores no vtable pointer before deleting, so cl's generated ??_G
// (which always writes [this] = vftable) cannot be used; it is written out as the equivalent
// thiscall member: ecx = this, one flags argument, returns this in eax.
struct cAuthMessage {
  void* ScalarDeletingDtor(unsigned flags);
};
// ---- items of slice s006068c0 end

// ---- items of slice s00607800 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" unsigned int __cdecl strlen(const char*);
extern char gEmptyString[];  // 0x01667bac (shared "" for char and wchar_t strings)
extern const char DAT_0151e5f0[], DAT_0151e5e0[], DAT_0151e5ec[], DAT_0151e5d4[];
extern const wchar_t* kLoginPrefsName;            // 0x0151e23c (L"login")
#pragma intrinsic(strlen)
namespace eastl {
struct allocator_s0060_7800 {
  allocator_s0060_7800() {}
};
}
namespace eastl {
template <typename T>
inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
}
namespace eastl {
int Compare(const char* p1, const char* p2, unsigned int n);  // FUN_00606ea0
}
namespace eastl {
template <typename I1, typename I2>
I1 search(I1 first1, I1 last1, I2 first2, I2 last2);  // 0x005e8ff0
}
namespace eastl {
template <typename T, typename A = allocator_s0060_7800>
struct basic_string_s0060_7800 {
  typedef unsigned int size_type;
  enum { npos = -1 };
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;

  basic_string_s0060_7800() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  basic_string_s0060_7800(const T* pBegin, const T* pEnd, const A& allocator_s0060_7800)
      : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator_s0060_7800) {
    RangeInitialize(pBegin, pEnd);
  }
  struct CtorSprintf {};
  basic_string_s0060_7800(CtorSprintf, const T* pFormat, ...);  // 0x00473020 (wchar_t)
  basic_string_s0060_7800(const basic_string_s0060_7800& x);  // 0x0057cb10 (char)
  ~basic_string_s0060_7800() { DeallocateSelf(); }

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
  basic_string_s0060_7800& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0 (char), 0x00423650 (wchar_t)
  basic_string_s0060_7800& operator=(const basic_string_s0060_7800& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  basic_string_s0060_7800& replace(size_type position, size_type n, const T* p);  // 0x005f8f80 (wchar_t)
  void Trim();                                                       // 0x00606e60 (wchar_t)

  static int compare(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2) {
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int nMin = min_alt(n1, n2);
    const int cmp = Compare(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
  }
  int compare(const T* p) const;
  basic_string_s0060_7800 substr(size_type position, size_type n) const;
  basic_string_s0060_7800 left(size_type n) const;
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
}
typedef eastl::basic_string_s0060_7800<char> string8;
typedef eastl::basic_string_s0060_7800<wchar_t> string16;
namespace EA {
namespace COM {
class IUnknown32_s0060_7800 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t type) const = 0;
  virtual void pvUnknown3();
  ~IUnknown32_s0060_7800() {}
};  // namespace COM
}
}
namespace EA {
template <typename T>
class RefCountTemplate_s0060_7800 {
 public:
  RefCountTemplate_s0060_7800() : mRefCount(0) {}
  virtual ~RefCountTemplate_s0060_7800() {}
  T mRefCount;
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s0060_7800 {
 public:
  virtual ~RefCountVTemplate_s0060_7800() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
template <typename T>
class AutoRefCount_s0060_7800 {
 public:
  T* mpObject;
  AutoRefCount_s0060_7800() : mpObject(0) {}
  ~AutoRefCount_s0060_7800() {
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
class IHandler_s0060_7800 {
 public:
  virtual ~IHandler_s0060_7800() {}
  virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
};  // namespace Messaging
}
}
namespace EA {
namespace XHTML {
namespace Resource {
class IAuthenticationService_s0060_7800 : public RefCountTemplate_s0060_7800<int> {
 public:
  virtual bool AddAuthentication(void* pResource, struct Request* pRequest) = 0;
};  // namespace Resource
}
}
}
namespace EA {
namespace UTFWin {
class IWindow_s0060_7800;
}
}
namespace EA {
namespace UTFWin {
struct Message_s0060_7800 {
  IWindow_s0060_7800* mpSource;  // +0x0
  uint32_t pad4;
  uint32_t mEventType;  // +0x8
  uint32_t padc;
  uint32_t mKey;  // +0x10
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s0060_7800 {
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
  virtual void AddWinProc(class IWinProc_s0060_7800* p);     // +0x104
  virtual void RemoveWinProc(class IWinProc_s0060_7800* p);  // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s0060_7800 : public COM::IUnknown32_s0060_7800 {
 public:
  virtual uint32_t GetEventFlags();
  virtual bool HandleUIMessage(IWindow_s0060_7800* pWindow, const Message_s0060_7800& msg) = 0;
};
}
}
namespace EA {
namespace UTFWin {
class __declspec(novtable) IModalWindowCallback_s0060_7800 {
 public:
  virtual void pv0() = 0;
  virtual void OnModalEnd(IWindow_s0060_7800* pWindow, uint32_t id) = 0;
};
}
}
namespace EA {
namespace UTFWin {
class CustomWinProc_s0060_7800 : public IWinProc_s0060_7800 {
 public:
  bool HandleUIMessage(IWindow_s0060_7800* pWindow, const Message_s0060_7800& msg);  // 0x00950ef0
  uint32_t pad4[2];
};
}
}
struct ResourceKey_s0060_7800 {
  uint32_t mInstance, mType, mGroup;
};
class cSPUILayout_s0060_7800 {
 public:
  bool Init(const ResourceKey_s0060_7800& key, int a, uint32_t b);                // 0x008120d0
  EA::UTFWin::IWindow_s0060_7800* FindWindowByID(uint32_t id, bool recursive);    // 0x008105b0
  void Shutdown(bool b);                                               // 0x00811ad0
  uint32_t pad[3];
};
namespace SPUIHelpers {
bool BeginModal(EA::UTFWin::IWindow_s0060_7800* pWindow, int a, bool b);  // 0x008099a0
}
void FUN_00809db0(const void* a, const void* b);
namespace SP {
class cString_s0060_7800 {
 public:
  cString_s0060_7800();                                                    // 0x006b5060
  ~cString_s0060_7800();                                                   // 0x006b5240
  void Load(uint32_t tableID, uint32_t instanceID, const wchar_t* pDefault);  // 0x006b54b0
  const wchar_t* GetText(bool b);                                 // 0x006b55c0
  uint32_t pad[5];
};
}
namespace SP {
class cStringTokenTranslator_s0060_7800 : public EA::RefCountVTemplate_s0060_7800<int> {
 public:
  cStringTokenTranslator_s0060_7800();   // 0x006b5870
  ~cStringTokenTranslator_s0060_7800();  // 0x005725a0
  virtual void pv3();
  virtual bool TranslateToken(const wchar_t* pToken, string16& out) = 0;
};
}
namespace SP {
class cPollinator_s0060_7800 {
 public:
  void SetEnabledState(uint32_t state);  // 0x0060cec0
  void FUN_00612270();
  void FUN_00611540();
  void Login(const char* user, const char* password, const wchar_t* path);  // FUN_00611480
};
}
namespace SP {
cPollinator_s0060_7800* Pollinator_s0060_7800();  // FUN_0067cb30
}
namespace SP {
class IMessageBox_s0060_7800 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual void Show(const wchar_t* text);  // +0x34
};
}
namespace SP {
class IUIManager_s0060_7800 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual IMessageBox_s0060_7800* GetMessageBox();  // +0x20
};
}
namespace SP {
IUIManager_s0060_7800* UIManager_s0060_7800();  // FUN_0067de40
}
namespace SP {
namespace Pollen {
bool GetURL(uint32_t id, string16& out);  // 0x006214c0
}
}
namespace SP {
namespace Pollen {
class IAuthManager : public EA::COM::IUnknown32_s0060_7800 {
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
}
}
namespace SP {
namespace Pollen {
class IServiceRegistry {
 public:
  PV(0) PV(1) PV(2)
  virtual IAuthManager* Get(uint32_t id);  // +0xc
};
}
}
namespace SP {
namespace Pollen {
extern IServiceRegistry* gServiceRegistry;  // 0x015f3814
}
}
namespace SP {
namespace Pollen {
namespace {
class cConnectingDialog_s0060_7800 : public EA::UTFWin::CustomWinProc_s0060_7800 {
 public:
  void HandleResults(bool success);  // 0x006075c0
  void Show(const wchar_t* text);
  EA::AutoRefCount_s0060_7800<EA::UTFWin::IWindow_s0060_7800> mpWindow;  // +0xc
  float mStartTime;                                // +0x10
  float mTimeout;                                  // +0x14
  bool mEndConnecting;                             // +0x18
  bool mEndConnected;                              // +0x19
  float mRotation[4];                              // +0x1c
  cSPUILayout_s0060_7800 mLayout;                             // +0x2c
};
cConnectingDialog_s0060_7800* gpConnectingDialog;  // 0x015f3670

class cLoginHelpDialog_s0060_7800 : public EA::UTFWin::CustomWinProc_s0060_7800 {
 public:
  bool Show();
  bool HandleUIMessage(EA::UTFWin::IWindow_s0060_7800* pWindow, const EA::UTFWin::Message_s0060_7800& msg);
  cSPUILayout_s0060_7800 mLayout;  // +0xc
};
}  // namespace
}
}
namespace SP {
namespace Pollen {
class cAuthManager_s0060_7800 : public EA::UTFWin::IWinProc_s0060_7800,
                     public EA::UTFWin::IModalWindowCallback_s0060_7800,
                     public EA::Messaging::IHandler_s0060_7800,
                     public EA::XHTML::Resource::IAuthenticationService_s0060_7800,
                     public cStringTokenTranslator_s0060_7800,
                     public IAuthManager {
 public:
  cAuthManager_s0060_7800();
  void EndLoginDialog();  // 0x00606d80
  void LoadSavedPrefs();  // 0x00608120 (SP::Pollen::cAuthManager::LoadSavedPrefs)
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t type) const;
  virtual bool HandleUIMessage(EA::UTFWin::IWindow_s0060_7800* pWindow, const EA::UTFWin::Message_s0060_7800& msg);
  virtual bool HandleMessage(uint32_t messageID, void* pMessage);
  virtual bool AddAuthentication(void* pResource, EA::XHTML::Resource::Request* pRequest);
  virtual bool TranslateToken(const wchar_t* pToken, string16& out);
  virtual void SetUserPassword(const string8& user, const string8& password);
  virtual void GetUserPassword(string8& user, string8& password);
  virtual void ShowLoginDialog(bool b);
  virtual void SetRememberPassword(bool b);
  virtual const string8& GetUser();
  virtual const string8& GetPassword();
  virtual void ProcessLoginResults(short result);  // 0x00607800 (SP::Pollen::cAuthManager::ProcessLoginResults)
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
  cSPUILayout_s0060_7800* mpLoginLayout; // +0x60
  bool mbDontSavePrefs;       // +0x64
  bool mbLoggedIn;            // +0x65
  int mDialogInProgress;      // +0x68
  EA::AutoRefCount_s0060_7800<EA::COM::IUnknown32_s0060_7800> pReg;  // +0x6c
};
}
}
namespace SP {
namespace Pollen {
class cOfflinePromptDialog : public EA::UTFWin::CustomWinProc_s0060_7800 {
 public:
  bool HandleUIMessage(EA::UTFWin::IWindow_s0060_7800* pWindow, const EA::UTFWin::Message_s0060_7800& msg);
  uint32_t padc[3];
  bool mbClosed;  // +0x18
};
}
}
namespace SP {
namespace Pollen {
bool FUN_00685520(int mode);
}
}
namespace SP {
namespace Pollen {
struct Property_s0060_7800 {
  uint32_t pad[4];
  uint16_t pad10;
  uint16_t mnType;  // +0x12
  bool* GetBool();  // 0x0041e920
};
}
}
namespace SP {
namespace Pollen {
class IPropertyList_s0060_7800 {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property_s0060_7800*& prop);  // +0x24
};
}
}
namespace SP {
namespace Pollen {
class IPropertyManager_s0060_7800 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instance, uint32_t group, IPropertyList_s0060_7800*& out);  // +0x2c
};
}
}
namespace SP {
namespace Pollen {
IPropertyManager_s0060_7800* PropertyManager_s0060_7800();  // 0x0067de30
}
}
namespace SP {
namespace Pollen {
bool GetPropertyAsString8(IPropertyList_s0060_7800* pList, uint32_t id, string8& out);  // 0x006a13b0
}
}
namespace EA {
namespace Hash {
uint32_t FNV1_String16(const wchar_t* p, uint32_t seed, int caseMode);  // 0x00932f30
}
}
void Decrypt(const string8& in, string8& out);  // 0x0060bf00
namespace SP {
namespace Pollen {
struct cAppProperties {
  uint32_t pad[15];
  struct Inner {
    uint32_t pad[70];
    int mValue;  // +0x118
  }* mpInner;  // +0x3c
};
}
}
namespace SP {
namespace Pollen {
extern cAppProperties* sAppProperties_s0060_7800;  // 0x015fd918
}
}
namespace SP {
namespace Pollen {
extern const wchar_t* kRegKeyA;        // 0x0151e234
}
}
namespace SP {
namespace Pollen {
extern const wchar_t* kRegKeyB;        // 0x0151e238
}
}
namespace SP {
namespace Pollen {
bool ReadRegistryString(const wchar_t* key, string16& out);  // 0x006aba80
}
}
namespace EA {
namespace XHTML {
namespace Resource {
struct HeaderMap {
  void Set(const char* name, const char* value);  // 0x00944d00
};
}
}
}
namespace EA {
namespace XHTML {
namespace Resource {
struct URLInfo {
  int GetScheme();  // 0x0094baa0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Resource {
struct Request {
  uint32_t pad[12];
  URLInfo mURL;  // +0x30
  uint32_t pad34[176];
  HeaderMap mHeaders;  // +0x2f4
};
}
}
}
namespace EA {
namespace Internet {
namespace URL {
void ConvertPathToEncodedForm(const char* p, string8& out, int flags);  // 0x0094b610
}
}
}
namespace SP {
namespace Pollen {
void FUN_006b8f00(const char* name, string16& out);
}
}
// ---- items of slice s00607800 end

// ---- items of slice s006087b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
struct ICoreAllocator;
ICoreAllocator* GetDefaultAllocator();  // FUN_009512c0
void* operator new(unsigned int size, int alignment, const char* name, ICoreAllocator* pAllocator);
namespace eastl {
struct allocator_s0060_87b0 {
  allocator_s0060_87b0() {}
};
}
namespace eastl {
template <typename T, typename A = allocator_s0060_87b0>
struct basic_string_s0060_87b0 {
  typedef unsigned int size_type;
  enum { npos = -1 };
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;

  basic_string_s0060_87b0() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  basic_string_s0060_87b0(const T* pBegin, const T* pEnd, const A& allocator_s0060_87b0)
      : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator_s0060_87b0) {
    RangeInitialize(pBegin, pEnd);
  }
  struct CtorSprintf {};
  basic_string_s0060_87b0(CtorSprintf, const T* pFormat, ...);  // 0x00473020 (wchar_t), 0x00472f50 (char)
  basic_string_s0060_87b0& sprintf(const T* pFormat, ...);       // 0x00472fe0 (char)
  // (out of line at 0x0057cb10 elsewhere; this TU inlines it with AllocateSelf expanded)
  basic_string_s0060_87b0(const basic_string_s0060_87b0& x) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(x.mAllocator) {
    RangeInitializeInl(x.mpBegin, x.mpEnd);
  }
  ~basic_string_s0060_87b0() { DeallocateSelf(); }

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
  basic_string_s0060_87b0& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0 (char), 0x00423650 (wchar_t)
  basic_string_s0060_87b0& operator=(const T* p) { return assign(p, p + strlen(p)); }
  basic_string_s0060_87b0& operator=(const basic_string_s0060_87b0& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  basic_string_s0060_87b0& replace(size_type position, size_type n, const T* p);  // 0x005f8f80 (wchar_t)
  void Trim();                                                       // 0x00606e60 (wchar_t)

  static int compare(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2) {
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int nMin = min_alt(n1, n2);
    const int cmp = Compare(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
  }
  int compare(const T* p) const;
  basic_string_s0060_87b0 substr(size_type position, size_type n) const;
  basic_string_s0060_87b0 left(size_type n) const;
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
typedef eastl::basic_string_s0060_87b0<char> string8_s0060_87b0;
typedef eastl::basic_string_s0060_87b0<wchar_t> string16_s0060_87b0;
template <>
__declspec(noinline) int eastl::basic_string_s0060_87b0<char>::compare(const char* p) const {
  return compare(mpBegin, mpEnd, p, p + strlen(p));
}
template <>
__declspec(noinline) string8_s0060_87b0 eastl::basic_string_s0060_87b0<char>::substr(size_type position, size_type n) const {
  return basic_string_s0060_87b0(mpBegin + position,
                      mpBegin + position + min_alt(n, (size_type)(mpEnd - mpBegin) - position),
                      mAllocator);
}
template <>
__declspec(noinline) string8_s0060_87b0 eastl::basic_string_s0060_87b0<char>::left(size_type n) const {
  const size_type nLength = length();
  if (n < nLength) return substr(0, n);
  return *this;
}
template <>
__declspec(noinline) string8_s0060_87b0::size_type eastl::basic_string_s0060_87b0<char>::find(char c, size_type position) const {
  if (position < (size_type)(mpEnd - mpBegin)) {
    const char* p = mpBegin + position;
    while (p != mpEnd && *p != c) ++p;
    if (p != mpEnd) return (size_type)(p - mpBegin);
  }
  return (size_type)npos;
}
namespace EA {
namespace COM {
class IUnknown32_s0060_87b0 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t type) const = 0;
  virtual void pvUnknown3();
  ~IUnknown32_s0060_87b0() {}
};  // namespace COM
}
}
namespace EA {
template <typename T>
class RefCountTemplate_s0060_87b0 {
 public:
  RefCountTemplate_s0060_87b0() : mRefCount(0) {}
  virtual ~RefCountTemplate_s0060_87b0() {}
  T mRefCount;
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s0060_87b0 {
 public:
  virtual ~RefCountVTemplate_s0060_87b0() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
template <typename T>
class AutoRefCount_s0060_87b0 {
 public:
  T* mpObject;
  AutoRefCount_s0060_87b0() : mpObject(0) {}
  AutoRefCount_s0060_87b0(T* pObject) : mpObject(pObject) {
    if (mpObject) mpObject->AddRef();
  }
  AutoRefCount_s0060_87b0& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  ~AutoRefCount_s0060_87b0() {
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
class IHandler_s0060_87b0 {
 public:
  virtual ~IHandler_s0060_87b0() {}
  virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
};  // namespace Messaging
}
}
namespace EA {
namespace XHTML {
namespace Resource {
class IAuthenticationService_s0060_87b0 : public RefCountTemplate_s0060_87b0<int> {
 public:
  virtual bool AddAuthentication(void* pResource, struct Request_s0060_87b0* pRequest) = 0;
};  // namespace Resource
}
}
}
namespace EA {
class IMessageServer_s0060_87b0 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMSG(uint32_t messageID, void* p1, void* p2);  // +0x14
  PV(6) PV(7) PV(8)
  virtual void AddListener(Messaging::IHandler_s0060_87b0* pHandler, uint32_t messageID);  // +0x24
  PV(10)
  virtual void RemoveListener(Messaging::IHandler_s0060_87b0* pHandler, uint32_t messageID, int priority);  // +0x2c
};
}
namespace EA {
namespace UTFWin {
class IWindow_s0060_87b0;
}
}
namespace EA {
namespace UTFWin {
struct Message_s0060_87b0 {
  IWindow_s0060_87b0* mpSource;  // +0x0
  uint32_t pad4;
  uint32_t mEventType;  // +0x8
  uint32_t padc;
  uint32_t mKey;  // +0x10
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s0060_87b0 {
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
  virtual void AddWinProc(class IWinProc_s0060_87b0* p);     // +0x104
  virtual void RemoveWinProc(class IWinProc_s0060_87b0* p);  // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s0060_87b0 : public COM::IUnknown32_s0060_87b0 {
 public:
  virtual uint32_t GetEventFlags();
  virtual bool HandleUIMessage(IWindow_s0060_87b0* pWindow, const Message_s0060_87b0& msg) = 0;
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
class __declspec(novtable) IModalWindowCallback_s0060_87b0 {
 public:
  virtual void pv0() = 0;
  virtual void OnModalEnd(IWindow_s0060_87b0* pWindow, uint32_t id) = 0;
};
}
}
namespace EA {
namespace UTFWin {
class ISerializable_s0060_87b0 {
 public:
  virtual void pv0();
};
}
}
namespace EA {
namespace UTFWin {
class MultiHeapObject_s0060_87b0 {};
}
}
namespace EA {
namespace UTFWin {
class CustomWinProc_s0060_87b0 : public IWinProc_s0060_87b0, public ISerializable_s0060_87b0, public MultiHeapObject_s0060_87b0 {
 public:
  CustomWinProc_s0060_87b0() : mRefCount(0) {}
  virtual int AddRef();
  virtual int Release();  // 0x0097da40 (EA::UTFWin::CustomWinProc::Release)
  virtual void* Cast(uint32_t type) const;
  bool HandleUIMessage(IWindow_s0060_87b0* pWindow, const Message_s0060_87b0& msg);  // 0x00950ef0
  int mRefCount;  // +0x8
};
}
}
namespace EA {
namespace UTFWin {
class IWindowManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  PV(15) PV(16) PV(17) PV(18)
  virtual void SetFocus(int a, IWindow_s0060_87b0* pWindow);  // +0x4c
};
}
}
struct ResourceKey_s0060_87b0 {
  uint32_t mInstance, mType, mGroup;
  static ResourceKey_s0060_87b0 Make(uint32_t instance, uint32_t type, uint32_t group) {
    ResourceKey_s0060_87b0 k;
    k.mInstance = instance;
    k.mType = type;
    k.mGroup = group;
    return k;
  }
};
class cSPUILayout_s0060_87b0 {
 public:
  cSPUILayout_s0060_87b0();           // 0x00810000
  virtual ~cSPUILayout_s0060_87b0();
  bool Init(const ResourceKey_s0060_87b0& key, int a, uint32_t b);                // 0x008120d0
  EA::UTFWin::IWindow_s0060_87b0* FindWindowByID(uint32_t id, bool recursive);    // 0x008105b0
  void Shutdown(bool b);                                               // 0x00811ad0
  uint32_t pad[5];
};
namespace SPUIHelpers {
bool BeginModal(EA::UTFWin::IWindow_s0060_87b0* pWindow, int a, bool b);  // 0x008099a0
}
namespace SPUIHelpers {
bool BeginModal(EA::UTFWin::IWindow_s0060_87b0* pWindow, EA::UTFWin::IModalWindowCallback_s0060_87b0* pCallback, bool b);
}
namespace SPUIHelpers {
void AutoSizeWindowForText(EA::UTFWin::IWindow_s0060_87b0* pWindow, bool a, bool b);  // 0x00806e40
}
namespace SPUIHelpers {
void AnchorWindowToWindow(EA::UTFWin::IWindow_s0060_87b0* pWindow, EA::UTFWin::IWindow_s0060_87b0* pAnchor, uint32_t flags, int a);  // 0x00807340
}
namespace SP {
class cStringTokenTranslator_s0060_87b0 : public EA::RefCountVTemplate_s0060_87b0<int> {
 public:
  cStringTokenTranslator_s0060_87b0();   // 0x006b5870
  ~cStringTokenTranslator_s0060_87b0();  // 0x005725a0
  virtual void pv3();
  virtual bool TranslateToken(const wchar_t* pToken, string16_s0060_87b0& out) = 0;
};
}
namespace SP {
class cPollinator_s0060_87b0 {
 public:
  void SetEnabledState(uint32_t state);  // 0x0060cec0
  void FUN_00612270();
  void FUN_00611540();
  void Login(const char* user, const char* password, const wchar_t* path);  // FUN_00611480
  uint8_t pad[0xf1];
  bool mbBuddyMode;  // +0xf1 (guess)
  bool IsBuddyMode() const { return mbBuddyMode; }
};
}
namespace SP {
EA::IMessageServer_s0060_87b0* MessageServer_s0060_87b0();          // 0x0067dcc0
}
namespace SP {
EA::UTFWin::IWindowManager* WindowManager();  // 0x0067caa0
}
namespace SP {
class IConfigManager_s0060_87b0 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
  virtual int GetInt(uint32_t id);  // +0x30
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
  virtual void GetUserName(int a, string8_s0060_87b0& out);  // +0x4c
};
}
namespace SP {
IConfigManager_s0060_87b0* ConfigManager_s0060_87b0();  // 0x0067dd30
}
namespace SP {
cPollinator_s0060_87b0* Pollinator_s0060_87b0();  // FUN_0067cb30
}
namespace SP {
class IMessageBox {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void AddTokenTranslator(class cStringTokenTranslator_s0060_87b0* p);  // +0x1c
  PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual void Show(const wchar_t* text);  // +0x34
};
}
namespace SP {
class IUIManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual IMessageBox* GetMessageBox();  // +0x20
};
}
namespace SP {
IUIManager* UIManager();  // FUN_0067de40
}
namespace SP {
namespace Pollen {
class IAuthManager_s0060_87b0 : public EA::COM::IUnknown32_s0060_87b0 {
 public:
  IAuthManager_s0060_87b0() {}
  virtual bool Init() = 0;  // 4
  virtual void pv5();
  virtual void SetUserPassword(const string8_s0060_87b0& user, const string8_s0060_87b0& password) = 0;  // 6
  virtual void GetUserPassword(string8_s0060_87b0& user, string8_s0060_87b0& password) = 0;              // 7
  virtual void ShowLoginDialog(bool b) = 0;                                        // 8 +0x20
  virtual void pv9();
  virtual void SetRememberPassword(bool b) = 0;  // 10 +0x28
  virtual bool GetRememberPassword() = 0;  // 11 +0x2c
  virtual const string8_s0060_87b0& GetUser() = 0;      // 12 +0x30
  virtual const string8_s0060_87b0& GetPassword() = 0;  // 13 +0x34
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
}
}
namespace SP {
namespace Pollen {
struct cSPVector4 {
  float x, y, z, w;
  cSPVector4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
};
}
}
namespace SP {
namespace Pollen {
namespace {
class cConnectingDialog_s0060_87b0 : public EA::UTFWin::CustomWinProc_s0060_87b0 {
 public:
  cConnectingDialog_s0060_87b0()
      : mTimeout(30.0f), mEndConnecting(false), mEndConnected(false), mRotation(0.0f, 0.0f, 1.0f, 0.0f) {}
  bool Init();                       // 0x00606c40
  void HandleResults(bool success);  // 0x006075c0
  void Show(const char* text);       // 0x00608710
  EA::AutoRefCount_s0060_87b0<EA::UTFWin::IWindow_s0060_87b0> mpWindow;  // +0xc
  float mStartTime;                                // +0x10
  float mTimeout;                                  // +0x14
  bool mEndConnecting;                             // +0x18
  bool mEndConnected;                              // +0x19
  cSPVector4 mRotation;                            // +0x1c
  cSPUILayout_s0060_87b0 mLayout;                             // +0x2c
};
EA::AutoRefCount_s0060_87b0<cConnectingDialog_s0060_87b0> gpConnectingDialog_s0060_87b0;  // 0x015f3670

class cLoginHelpDialog_s0060_87b0 : public EA::UTFWin::CustomWinProc_s0060_87b0 {
 public:
  cLoginHelpDialog_s0060_87b0();  // 0x00607480
  bool Show();         // 0x00607cf0
  bool HandleUIMessage(EA::UTFWin::IWindow_s0060_87b0* pWindow, const EA::UTFWin::Message_s0060_87b0& msg);
  cSPUILayout_s0060_87b0 mLayout;  // +0xc
};
class cOfflineConfirmationDialog_s0060_87b0 : public EA::UTFWin::CustomWinProc_s0060_87b0 {
 public:
  cOfflineConfirmationDialog_s0060_87b0();  // 0x00607450
  bool Init();                   // 0x00607050
  void SetCallback(EA::UTFWin::IModalWindowCallback_s0060_87b0* pCallback);  // 0x00606cd0
  cSPUILayout_s0060_87b0 mLayout;  // +0xc
};
}  // namespace
}
}
namespace SP {
namespace Pollen {
class cRegistrationDialog_s0060_87b0 : public EA::UTFWin::IWinProc_s0060_87b0 {
 public:
  void Show(bool b);  // 0x00620050
};
}
}
namespace SP {
namespace Pollen {
class cAuthManager_s0060_87b0 : public EA::UTFWin::IWinProc_s0060_87b0,
                     public EA::UTFWin::IModalWindowCallback_s0060_87b0,
                     public EA::Messaging::IHandler_s0060_87b0,
                     public EA::XHTML::Resource::IAuthenticationService_s0060_87b0,
                     public cStringTokenTranslator_s0060_87b0,
                     public IAuthManager_s0060_87b0 {
 public:
  cAuthManager_s0060_87b0();
  void EndLoginDialog();  // 0x00606d80
  void LoadSavedPrefs();  // 0x00608120
  void Logout();          // 0x006073a0
  void ReadLoginLayout();
  virtual bool Init();  // 0x006087b0 (SP::Pollen::cAuthManager::Init)
  virtual bool GetRememberPassword();
  virtual void ShowLoginLayout(bool bOfflineAvailable);
  virtual void Login();
  virtual bool IsRegistered();
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t type) const;
  virtual bool HandleUIMessage(EA::UTFWin::IWindow_s0060_87b0* pWindow, const EA::UTFWin::Message_s0060_87b0& msg);
  virtual bool HandleMessage(uint32_t messageID, void* pMessage);
  virtual bool AddAuthentication(void* pResource, EA::XHTML::Resource::Request_s0060_87b0* pRequest);
  virtual bool TranslateToken(const wchar_t* pToken, string16_s0060_87b0& out);
  virtual void SetUserPassword(const string8_s0060_87b0& user, const string8_s0060_87b0& password);
  virtual void GetUserPassword(string8_s0060_87b0& user, string8_s0060_87b0& password);
  virtual void ShowLoginDialog(bool b);
  virtual void SetRememberPassword(bool b);
  virtual const string8_s0060_87b0& GetUser();
  virtual const string8_s0060_87b0& GetPassword();
  virtual void ProcessLoginResults(short result);  // 0x00607800 (SP::Pollen::cAuthManager::ProcessLoginResults)
  virtual void SavePrefs();
  virtual void FinishLogin(bool b);

  string8_s0060_87b0 mUser;              // +0x20
  string8_s0060_87b0 mPassword;          // +0x30
  string8_s0060_87b0 mScreenName;        // +0x40
  uint64_t mnUserServerID;    // +0x50
  uint32_t mnUserLocalID;     // +0x58
  bool mbPlayOffline;         // +0x5c
  bool mbPrompt;              // +0x5d
  bool mbSavedPrefsFlag;      // +0x5e
  bool mbRetryLogin;          // +0x5f
  cSPUILayout_s0060_87b0* mpLoginLayout; // +0x60
  bool mbDontSavePrefs;       // +0x64
  bool mbLoggedIn;            // +0x65
  int mDialogInProgress;      // +0x68
  EA::AutoRefCount_s0060_87b0<cRegistrationDialog_s0060_87b0> pReg;  // +0x6c
};
}
}
namespace SP {
namespace Pollen {
string8_s0060_87b0& GetEmptyString8();  // 0x006083b0
}
}
namespace SP {
namespace Pollen {
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
  const string8_s0060_87b0* GetValueString8() const {
    if (mnType == 0x12 || mnType == 0x10) return (const string8_s0060_87b0*)GetDataPtr();
    return &GetEmptyString8();
  }
  uint32_t mData[4];
  uint16_t mnFlags;  // +0x10
  uint16_t mnType;   // +0x12
};
}
}
namespace SP {
namespace Pollen {
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
}
}
namespace SP {
namespace Pollen {
class cPropertyList : public IPropertyList {
 public:
  cPropertyList();  // 0x006a1c40
  uint32_t pad4;
  ResourceKey_s0060_87b0 mResourceKey;  // +0x8
  uint32_t pad14[9];
};
}
}
namespace SP {
namespace Pollen {
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instance, uint32_t group, IPropertyList*& out);  // +0x2c
  PV(12)
  virtual void AddPropertyList(IPropertyList* pList, uint32_t instance, uint32_t group);  // +0x34
};
}
}
namespace SP {
namespace Pollen {
void* GetSaveArea(uint32_t group);                                            // 0x006b1f90
}
}
namespace SP {
namespace Pollen {
void SaveNamedResource(IPropertyList* pList, const wchar_t* name, void* area);  // 0x006b4010
}
}
namespace SP {
namespace Pollen {
IPropertyManager* PropertyManager();  // 0x0067de30
}
}
namespace EA {
namespace Hash {
uint32_t FNV1_String8(const char* p, uint32_t seed, int caseMode);      // 0x00932e80
}
}
void Encrypt(const string8_s0060_87b0& in, string8_s0060_87b0& out);  // 0x0060bcf0
namespace SP {
namespace Pollen {
extern IPropertyList* sAppProperties_s0060_87b0;  // 0x015fd918
}
}
namespace EA {
namespace XHTML {
namespace Resource {
struct HeaderMap_s0060_87b0 {
  void Set(const char* name, const char* value);  // 0x00944d00
  void AddHeaderEntry(const char* name, const string8_s0060_87b0& value);  // 0x00944cb0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Resource {
struct Request_s0060_87b0 {
  uint32_t pad[12];
  URLInfo mURL;  // +0x30
  uint32_t pad34[176];
  HeaderMap_s0060_87b0 mHeaders;  // +0x2f4
};
}
}
}
template <>
__declspec(noinline) EA::AutoRefCount_s0060_87b0<SP::Pollen::cLoginHelpDialog_s0060_87b0>::AutoRefCount_s0060_87b0(SP::Pollen::cLoginHelpDialog_s0060_87b0* pObject)
    : mpObject(pObject) {
  if (mpObject) mpObject->AddRef();
}
namespace SP {
namespace Pollen {
extern const ResourceKey_s0060_87b0 kLoginLayout;  // 0x0151e5b0
}
}
namespace SP {
namespace Pollen {
struct LoginInfoMessage {
  const wchar_t* mpScreenName;  // +0x0
  uint32_t pad4[5];
  uint64_t mnUserServerID;  // +0x18
};
}
}
namespace SP {
namespace Pollen {
struct DialogMessage {
  uint32_t pad[2];
  int mButton;  // +0x8
};
}
}
namespace EA {
namespace COM {
template <typename T>
class RefCountTemplate_s0060_87b0 {
 public:
  virtual ~RefCountTemplate_s0060_87b0() {}
  T mRefCount;
};  // namespace COM
}
}
// ---- items of slice s006087b0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace SP { namespace Pollen { IAuthManager* AuthManager(); }}  // 0x00607a60 (stays in the slice: not this object's)

// @ 0x00606d00
void * SP::Pollen::cAuthManager::AsInterface(EA::COM::InterfaceId typeID)
{
  switch ((int)typeID) {
    case 0x40f7cee: return this;
    case 0x7201461:
    case (int)0xee3f516e: return static_cast<IAuthenticationService*>(this);
    case 0x2f009dd0: return this;
  }
  return 0;
}

// @ 0x00606d70
namespace SP { namespace Pollen {
uint64_t cAuthManager_s0060_68c0::GetUserServerID()
{
  return mnUserServerID;
}
}}  // namespace SP::Pollen

// @ 0x00606d80
namespace SP { namespace Pollen {
void cAuthManager_s0060_68c0::EndLoginDialog()
{
  MessageServer()->PostMSG(0x4fd2bd3, 0, 0);
  SPUIHelpers::EndModal(mpLoginLayout->FindWindowByID(0x40cf9b0, true), 0, true);
  mpLoginLayout->Shutdown(true);
  delete mpLoginLayout;
  mpLoginLayout = 0;
}
}}  // namespace SP::Pollen

// @ 0x00606de0
namespace SP { namespace Pollen {
void cAuthManager_s0060_68c0::SetLoginDialogVisible(bool visible)
{
  if (mpLoginLayout) {
    mpLoginLayout->FindWindowByID(0x40cf9b0, true)->SetFlag(1, visible);
    IWindow_s0060_68c0* w = mpLoginLayout->FindWindowByID(0x40cf9b0, true);
    if (visible)
      SPUIHelpers::BeginModal(w, 0, true);
    else
      SPUIHelpers::EndModal(w, 0, true);
  } else
    MessageServer()->PostMSG(0x5c5594a, 0, 0);
}
}}  // namespace SP::Pollen

// @ 0x00606e60
namespace eastl {
template <typename T> void basic_string_s0060_68c0<T>::make_upper()
{
  for (T* p = mpBegin; p < mpEnd; ++p) *p = (T)CharToUpper(*p);
}
}  // namespace eastl

// @ 0x00606ea0
namespace eastl {
int CompareI(const char* p1, const char* p2, size_t n)
{
  for (; n > 0; ++p1, ++p2, --n) {
    const char c1 = CharToLower(*p1);
    const char c2 = CharToLower(*p2);
    if (c1 != c2) return (c1 < c2) ? -1 : 1;
  }
  return 0;
}
}  // namespace eastl

// @ 0x00606f30
void* cAuthMessage::ScalarDeletingDtor(unsigned flags)
{
  if (flags & 1) operator delete(this);
  return this;
}

// @ 0x00606f60
namespace SP { namespace Pollen {
bool cLoginHelpDialog::IsReturnKey(void* a, void* b, int key, void* c)
{
  if (key == 0xd) return true;
  return false;
}
}}  // namespace SP::Pollen

// @ 0x00606f80
namespace SP { namespace Pollen {
void cConnectingDialog::end_dialog(bool connected)
{
  SPUIHelpers::EndModal(mpWindow, 0, true);
  mpWindow->RemoveWinProc(this);
  mpWindow = 0;
  mLayout.Shutdown(true);
  MessageServer()->PostMSG(0x44db12e, (void*)(connected != 0), 0);
}
}}  // namespace SP::Pollen

// @ 0x00607050
namespace SP { namespace Pollen {
bool cOfflineConfirmationDialog::Init()
{
  if (mLayout.Init(ResourceKey(0xf69e2034, 0x510a95b, 0x40464100), true, 0x5b598f7)) {
    IWindow_s0060_68c0* message = mLayout.FindWindowByID(0x50fad88, true);
    if (message) {
      SPUIHelpers::AutoSizeWindowForText(message, 1, 0);
      IWindow_s0060_68c0* button = mLayout.FindWindowByID(0x50fb5d0, true);
      if (button) {
        SPUIHelpers::AutoSizeWindowForText(button, 0, 0);
        const EA::UTFWin::Rect* area = &button->GetArea();
        float width = area->right - area->left;
        float x = message->GetArea().left - width;
        button->SetLocation(x, area->top);
      }
    }
    IWindow_s0060_68c0* root = mLayout.FindWindowByID(0x50f92d8, true);
    if (root) {
      root->AddWinProc(this);
      return true;
    }
    mLayout.Shutdown(true);
  }
  return false;
}
}}  // namespace SP::Pollen

// @ 0x00607190
namespace SP { namespace Pollen {
bool cAuthManager_s0060_68c0::Shutdown()
{
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
}}  // namespace SP::Pollen

// @ 0x00607290
namespace SP { namespace Pollen {
void cAuthManager_s0060_68c0::SetPlayOffline(bool offline)
{
  mbPlayOffline = offline;
  if (offline) {
    mPassword.clear();
    EA::Messaging::IMessageServer* server = MessageServer();
    if (server) server->PostMSG(0x5ff8006, 0, 0);
  }
}
}}  // namespace SP::Pollen

// @ 0x006072d0
namespace SP { namespace Pollen {
void cAuthManager_s0060_68c0::SetOfflineUserID()
{
  ConfigManager()->GetString(0, mScreenName);
  mnUserServerID = (uint64_t)-2;
  mnUserLocalID = FNVHash(mScreenName.c_str(), 0x811c9dc5, true);
}
}}  // namespace SP::Pollen

// @ 0x00607310
namespace SP { namespace Pollen {
void cAuthManager_s0060_68c0::ShowLoginDialog(bool b)
{
  if (!IsLoginUIAvailable()) {
    if (!pReg) pReg = new ("UI/cRegistrationDialog", 0, 0, 0, 0) cRegistrationDialog_s0060_68c0();
    pReg->Show(b);
  } else
    ShowLoginUI(b);
}
}}  // namespace SP::Pollen

// @ 0x006073a0
namespace SP { namespace Pollen {
void cAuthManager_s0060_68c0::InitialLogin()
{
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
}}  // namespace SP::Pollen

// @ 0x00607450
namespace SP { namespace Pollen {
cOfflineConfirmationDialog::cOfflineConfirmationDialog()
{}
}}  // namespace SP::Pollen

// @ 0x00607480
namespace SP { namespace Pollen {
cLoginHelpDialog::cLoginHelpDialog()
{}
}}  // namespace SP::Pollen

// @ 0x006074b0
namespace SP { namespace Pollen {
void cAuthManager_s0060_68c0::OnModalWindowEnd(IWindow_s0060_68c0* window, uint32_t result)
{
  if (window->GetControlID() == 0x50f92d8 && result == 0x50fad88) {
    CancelLogin();
    Pollinator()->SetEnabledState(0x4c4d2cd);
    MessageServer()->PostMSG(0x5b85ff5, 0, 0);
    MessageServer()->PostMSG(0x44db12e, 0, 0);
    EndLoginDialog();
    SetOfflineUserID();
  }
}
}}  // namespace SP::Pollen

// @ 0x00607530
namespace SP { namespace Pollen {
void SetAuthManager(IUnknownCast* object)
{
  sAuthManager = object ? (cAuthManager_s0060_68c0*)object->Cast(0x40f7cee) : 0;
}
}}  // namespace SP::Pollen

// @ 0x00607580
namespace eastl {
template <typename T> size_t basic_string_s0060_68c0<T>::find(T c, size_t position) const
{
  if (position < (size_t)(mpEnd - mpBegin)) {
    const T* p = mpBegin + position;
    for (; p != mpEnd; ++p)
      if (*p == c) break;
    if (p != mpEnd) return (size_t)(p - mpBegin);
  }
  return (size_t)-1;
}
}  // namespace eastl

// @ 0x006075c0
namespace SP { namespace Pollen {
void cConnectingDialog::HandleResults(bool success)
{
  if (success)
    mEndConnecting = true;
  else
    end_dialog(false);
}
}}  // namespace SP::Pollen

// @ 0x00607630
namespace SP { namespace Pollen {
bool cConnectingDialog::OnTick(int a)
{
  if (mEndConnecting && SPUIHelpers::GetElapsedSeconds() - mStartTime > mTimeout) {
    if (!mEndConnected) {
      mEndConnected = true;
      mStartTime = SPUIHelpers::GetElapsedSeconds();
      mTimeout = 1.5f;
      cString text(0xb7bcef68, 0x662da01, L"Connected to Spore server");
      IWindow_s0060_68c0* w = mpWindow->FindWindowByID(0x5006000, true);
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
}}  // namespace SP::Pollen

// @ 0x006077f0
namespace SP { namespace Pollen {
void cAuthManager_s0060_68c0::ShowLogin()
{
  ShowLoginDialog(false);
}
}}  // namespace SP::Pollen

// @ 0x00607800
namespace SP { namespace Pollen {
void cAuthManager_s0060_7800::ProcessLoginResults(short result)
{
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
      cConnectingDialog_s0060_7800* p = gpConnectingDialog;
      gpConnectingDialog = 0;
      p->Release();
    }
  }
  if (kResultSuccess != result) {
    mbRetryLogin = false;
    cString_s0060_7800 text;
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
    UIManager_s0060_7800()->GetMessageBox()->Show(text.GetText(false));
    FUN_00809db0(DAT_0151e5ec, DAT_0151e5d4);
    mDialogInProgress = 1;
    if (mpLoginLayout) FinishLogin(false);
  } else {
    if (mbRetryLogin) mbSavedPrefsFlag = true;
    mbLoggedIn = true;
    SavePrefs();
    Pollinator_s0060_7800()->SetEnabledState(0x4c4d2c3);
    Pollinator_s0060_7800()->FUN_00612270();
    if (mpLoginLayout) EndLoginDialog();
  }
}
}}  // namespace SP::Pollen

// @ 0x00607a80
template <> int eastl::basic_string_s0060_7800<char>::compare(const char* p) const
{
  return compare(mpBegin, mpEnd, p, p + strlen(p));
}

// @ 0x00607b70
namespace SP { namespace Pollen {
bool cOfflinePromptDialog::HandleUIMessage(EA::UTFWin::IWindow_s0060_7800* pWindow, const EA::UTFWin::Message_s0060_7800& msg)
{
  if (msg.mEventType == 0x287259f6 && FUN_00685520(2) && msg.mpSource->GetControlID() == 0x5d2bdf8 &&
      !mbClosed) {
    Pollinator_s0060_7800()->FUN_00611540();
    IAuthManager* pAuth = AuthManager();
    if (pAuth) pAuth->ProcessLoginResults(6);
    return true;
  }
  return CustomWinProc_s0060_7800::HandleUIMessage(pWindow, msg);
}
}}  // namespace SP::Pollen

// @ 0x00607cf0
namespace SP { namespace Pollen {
bool cLoginHelpDialog_s0060_7800::Show()
{
  ResourceKey_s0060_7800 key = {0xd5aabe49, 0x510a95b, 0x40464100};
  if (mLayout.Init(key, 0, 0x5b598f7)) {
    EA::UTFWin::IWindow_s0060_7800* pText = mLayout.FindWindowByID(0x56c14b8, true);
    if (pText) {
      string16 url;
      if (GetURL(0x56bbbd1, url)) pText->SetCaption(url.c_str());
    }
    EA::UTFWin::IWindow_s0060_7800* pWindow = mLayout.FindWindowByID(0x56c1908, true);
    if (pWindow) {
      pWindow->AddWinProc(this);
      return SPUIHelpers::BeginModal(pWindow, 0, true);
    }
    mLayout.Shutdown(true);
  }
  return false;
}
}}  // namespace SP::Pollen

// @ 0x00607f30
namespace SP { namespace Pollen {
cAuthManager_s0060_7800::cAuthManager_s0060_7800()
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
}}  // namespace SP::Pollen

// @ 0x00608120
namespace SP { namespace Pollen {
void cAuthManager_s0060_7800::LoadSavedPrefs()
{
  EA::AutoRefCount_s0060_7800<IPropertyList_s0060_7800> pList;
  IPropertyManager_s0060_7800* pPropMgr = PropertyManager_s0060_7800();
  IPropertyList_s0060_7800*& pListOut = pList.AsOutParam();
  const uint32_t instance = EA::Hash::FNV1_String16(kLoginPrefsName, 0x811c9dc5, 1);
  if (pPropMgr->GetPropertyList(instance, 0x11ac192, pListOut)) {
    Property_s0060_7800* prop;
    if (pList && pList->GetProperty(0x40e3d98, prop) && prop->mnType == 1) mbPlayOffline = *prop->GetBool();
    if (pList && pList->GetProperty(0x440a514, prop) && prop->mnType == 1) mbPrompt = *prop->GetBool();
    GetPropertyAsString8(pList, 0x40512ef, mUser);
    string8 encrypted;
    if (GetPropertyAsString8(pList, 0x40512f4, encrypted)) Decrypt(encrypted, mPassword);
    if (pList && pList->GetProperty(0x6390ede, prop) && prop->mnType == 1) mbSavedPrefsFlag = true;
  }
}
}}  // namespace SP::Pollen

// @ 0x006082a0
template <> string8 eastl::basic_string_s0060_7800<char>::substr(size_type position, size_type n) const
{
  return basic_string_s0060_7800(mpBegin + position,
                      mpBegin + position + min_alt(n, (size_type)(mpEnd - mpBegin) - position),
                      mAllocator);
}

// @ 0x00608310
template <> string8 eastl::basic_string_s0060_7800<char>::left(size_type n) const
{
  const size_type nLength = length();
  if (n < nLength) return substr(0, n);
  return *this;
}

// @ 0x006083b0
string8& GetEmptyString8()
{
  static string8 sEmpty;
  return sEmpty;
}

// @ 0x006083f0
namespace SP { namespace Pollen {
void __stdcall OnAuthMessage(uint32_t unused, uint32_t messageID)
{
  IAuthManager* pAuth = gServiceRegistry ? gServiceRegistry->Get(0x7201461) : 0;
  cPollinator_s0060_7800* pPollinator = Pollinator_s0060_7800();
  if (pPollinator && pAuth) {
    if (messageID == 0x5107b1a) {
      string16 path;
      if (ReadRegistryString(sAppProperties_s0060_7800->mpInner->mValue ? kRegKeyA : kRegKeyB, path)) {
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
}}  // namespace SP::Pollen

// @ 0x00608550
namespace SP { namespace Pollen {
void cAuthManager_s0060_7800::SetUserPassword(const string8& user, const string8& password)
{
  mUser = user;
  mPassword = password;
  mbPlayOffline = false;
}
}}  // namespace SP::Pollen

// @ 0x00608590
namespace SP { namespace Pollen {
void cAuthManager_s0060_7800::GetUserPassword(string8& user, string8& password)
{
  user = mUser;
  password = mPassword;
}
}}  // namespace SP::Pollen

// @ 0x006085d0
namespace SP { namespace Pollen {
bool cAuthManager_s0060_7800::AddAuthentication(void* pResource, EA::XHTML::Resource::Request* pRequest)
{
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
}}  // namespace SP::Pollen

// @ 0x006086b0
namespace SP { namespace Pollen {
bool cAuthManager_s0060_7800::TranslateToken(const wchar_t* pToken, string16& out)
{
  if (EA::Hash::FNV1_String16(pToken, 0x811c9dc5, 1) != 0xfae0227d) return false;
  if (!mbPlayOffline) {
    FUN_006b8f00(mScreenName.c_str(), out);
    return true;
  }
  out.assign(L"", L"");
  return true;
}
}}  // namespace SP::Pollen

// @ 0x00608710
namespace SP { namespace Pollen {
void cConnectingDialog_s0060_7800::Show(const wchar_t* text)
{
  EA::UTFWin::IWindow_s0060_7800* pText = mLayout.FindWindowByID(0x42e2e38, true);
  if (pText) pText->SetCaption(string16(string16::CtorSprintf(), L"%ls", text).c_str());
  EA::UTFWin::IWindow_s0060_7800* pWindow = mLayout.FindWindowByID(0x431e538, true);
  if (pWindow) SPUIHelpers::BeginModal(pWindow, 0, true);
}
}}  // namespace SP::Pollen

// @ 0x006087b0
namespace SP { namespace Pollen {
bool cAuthManager_s0060_87b0::Init()
{
  LoadSavedPrefs();
  string8_s0060_87b0 autoLogin(*sAppProperties_s0060_87b0->GetPropertyPtr(0x5e8af796)->GetValueString8());
  if (!autoLogin.empty()) {
    if (autoLogin.compare("OptOut") == 0) {
      ShowLoginDialog(true);
    } else {
      const string8_s0060_87b0::size_type pos = autoLogin.find(',', 0);
      if (pos != (string8_s0060_87b0::size_type)string8_s0060_87b0::npos && pos != autoLogin.length() - 1)
        SetUserPassword(autoLogin.left(pos), autoLogin.substr(pos + 1, (string8_s0060_87b0::size_type)string8_s0060_87b0::npos));
    }
    SetRememberPassword(false);
    mbDontSavePrefs = true;
  }
  mbLoggedIn = mUser.size() > 0;
  EA::IMessageServer_s0060_87b0* pServer = MessageServer_s0060_87b0();
  if (pServer) {
    pServer->AddListener(static_cast<EA::Messaging::IHandler_s0060_87b0*>(this), 0x4bf2fc9);
    pServer->AddListener(static_cast<EA::Messaging::IHandler_s0060_87b0*>(this), 0xce7afa41);
    pServer->AddListener(static_cast<EA::Messaging::IHandler_s0060_87b0*>(this), 0x5b85672);
  }
  ConfigManager_s0060_87b0()->GetUserName(0, mScreenName);
  mnUserServerID = (uint64_t)-2;
  mnUserLocalID = EA::Hash::FNV1_String8(mScreenName.c_str(), 0x811c9dc5, 1);
  UIManager()->GetMessageBox()->AddTokenTranslator(static_cast<cStringTokenTranslator_s0060_87b0*>(this));
  return true;
}
}}  // namespace SP::Pollen

// @ 0x00608a10
namespace SP { namespace Pollen {
void cAuthManager_s0060_87b0::ShowLoginLayout(bool bOfflineAvailable)
{
  mpLoginLayout = new ("LoginLayout", 0, 0, 0, 0) cSPUILayout_s0060_87b0();
  if (mpLoginLayout->Init(kLoginLayout, 0, 0x5b598f7)) {
    MessageServer_s0060_87b0()->PostMSG(0x4fd2bce, 0, 0);
    EA::UTFWin::IWindow_s0060_87b0* pDialog = mpLoginLayout->FindWindowByID(0x40cf9b0, true);
    pDialog->AddWinProc(this);
    EA::UTFWin::IWindow_s0060_87b0* pRemember = mpLoginLayout->FindWindowByID(0x40cf210, true);
    if (pRemember) {
      EA::UTFWin::IWinControl* pCheck = pRemember->QueryControl(0x8ed27e7a);
      if (pCheck) pCheck->SetFlag(4, GetRememberPassword() == false);
    }
    EA::UTFWin::IWindow_s0060_87b0* pLoginButton = mpLoginLayout->FindWindowByID(0x40cf208, true);
    EA::UTFWin::IWindow_s0060_87b0* pCancel = mpLoginLayout->FindWindowByID(0x451a478, true);
    mpLoginLayout->FindWindowByID(0x40e7fa8, true)->SetFlag(1, bOfflineAvailable);
    EA::UTFWin::IWindow_s0060_87b0* pBuddy = mpLoginLayout->FindWindowByID(0x5091898, true);
    pBuddy->SetFlag(1, Pollinator_s0060_87b0()->IsBuddyMode());
    pCancel->SetFlag(1, !bOfflineAvailable);
    SPUIHelpers::AutoSizeWindowForText(pLoginButton, true, false);
    EA::UTFWin::IWindow_s0060_87b0* pHelp = mpLoginLayout->FindWindowByID(0x5121ff8, true);
    if (pHelp) SPUIHelpers::AutoSizeWindowForText(pHelp, true, false);
    if (bOfflineAvailable)
      SPUIHelpers::AutoSizeWindowForText(mpLoginLayout->FindWindowByID(0x40e7fa8, true), false, false);
    else
      SPUIHelpers::AutoSizeWindowForText(pCancel, false, false);
    SPUIHelpers::AnchorWindowToWindow(pLoginButton, pCancel, 0x820, 0);
    if (mUser.length() == 0) {
      SPUIHelpers::BeginModal(pDialog, static_cast<EA::UTFWin::IModalWindowCallback_s0060_87b0*>(this), true);
      WindowManager()->SetFocus(0, mpLoginLayout->FindWindowByID(0x40cf1f8, true));
    } else {
      mpLoginLayout->FindWindowByID(0x40cf1f8, true)
          ->SetCaption(string16_s0060_87b0(string16_s0060_87b0::CtorSprintf(), L"%hs", mUser.c_str()).c_str());
      SPUIHelpers::BeginModal(pDialog, static_cast<EA::UTFWin::IModalWindowCallback_s0060_87b0*>(this), true);
      WindowManager()->SetFocus(0, mpLoginLayout->FindWindowByID(0x40cf200, true));
    }
  } else {
    delete mpLoginLayout;
    mpLoginLayout = 0;
  }
}
}}  // namespace SP::Pollen

// @ 0x00608cc0
namespace SP { namespace Pollen {
void cAuthManager_s0060_87b0::SavePrefs()
{
  if (mbDontSavePrefs) return;
  EA::AutoRefCount_s0060_87b0<IPropertyList> pList;
  const uint32_t instance = EA::Hash::FNV1_String16(kLoginPrefsName, 0x811c9dc5, 1);
  PropertyManager()->GetPropertyList(instance, 0x11ac192, pList.AsOutParam());
  if (!pList) {
    pList = new ("Pollinator", 0, 0, 0, 0) cPropertyList();
    static_cast<cPropertyList*>(pList.mpObject)->mResourceKey = ResourceKey_s0060_87b0::Make(instance, 0xb1b104, 0x11ac192);
  }
  if (!mbPlayOffline) {
    {
      Property prop;
      prop.Set(0x12, 9, &mUser, 0x10, 1);
      pList->SetProperty(0x40512ef, &prop);
    }
    string8_s0060_87b0 encrypted;
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
    EA::AutoRefCount_s0060_87b0<IPropertyList> pExisting;
    IPropertyManager* pPropMgr = PropertyManager();
    IPropertyList*& pExistingOut = pExisting.AsOutParam();
    pPropMgr->GetPropertyList(instance, 0x11ac192, pExistingOut);
    if (!pExisting) PropertyManager()->AddPropertyList(pList, instance, 0x11ac192);
  }
}
}}  // namespace SP::Pollen

// @ 0x00608ff0
namespace SP { namespace Pollen {
void cAuthManager_s0060_87b0::Login()
{
  gpConnectingDialog_s0060_87b0 = new (4, "UI/cConnectionDialog", GetDefaultAllocator()) cConnectingDialog_s0060_87b0();
  if (gpConnectingDialog_s0060_87b0->Init()) gpConnectingDialog_s0060_87b0->Show(mUser.c_str());
  Pollinator_s0060_87b0()->Login(mUser.c_str(), mPassword.c_str(), 0);
}
}}  // namespace SP::Pollen

// @ 0x006091e0
namespace SP { namespace Pollen {
bool cAuthManager_s0060_87b0::HandleMessage(uint32_t messageID, void* pMessage)
{
  if (messageID == 0x4bf2fc9) {
    LoginInfoMessage* pInfo = (LoginInfoMessage*)pMessage;
    mnUserServerID = pInfo->mnUserServerID;
    mScreenName.sprintf("%ls", pInfo->mpScreenName);
    mnUserLocalID = EA::Hash::FNV1_String8(mScreenName.c_str(), 0x811c9dc5, 1);
    return true;
  }
  if (messageID == 0xce7afa41) {
    Logout();
    EA::IMessageServer_s0060_87b0* pServer = MessageServer_s0060_87b0();
    if (pServer) pServer->RemoveListener(static_cast<EA::Messaging::IHandler_s0060_87b0*>(this), 0xce7afa41, -9999);
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
}}  // namespace SP::Pollen

// @ 0x006092b0
namespace SP { namespace Pollen {
bool cAuthManager_s0060_87b0::HandleUIMessage(EA::UTFWin::IWindow_s0060_87b0* pWindow, const EA::UTFWin::Message_s0060_87b0& msg)
{
  if (msg.mEventType == 0x287259f6) {
    const uint32_t id = msg.mpSource->GetControlID();
    if (id == 0x40cf208) {
      ReadLoginLayout();
      mpLoginLayout->FindWindowByID(0x40cf9b0, true)->SetFlag(1, false);
      Login();
      return true;
    }
    if (id == 0x40e7fa8 || id == 0x5091898) {
      EA::AutoRefCount_s0060_87b0<cOfflineConfirmationDialog_s0060_87b0> pDialog =
          new (4, "UI/cOfflineConfirmationDialog", GetDefaultAllocator()) cOfflineConfirmationDialog_s0060_87b0();
      if (pDialog->Init()) {
        FinishLogin(false);
        pDialog->SetCallback(this);
        return true;
      }
      return false;
    }
    if (id == 0x451a478) {
      EndLoginDialog();
      MessageServer_s0060_87b0()->PostMSG(0x5b96086, 0, 0);
      if (!IsRegistered()) pReg->Show(true);
      return true;
    }
    if (id == 0x5121ff8) {
      EA::AutoRefCount_s0060_87b0<cLoginHelpDialog_s0060_87b0> pDialog(new (4, "UI/cLoginHelpDialog", GetDefaultAllocator()) cLoginHelpDialog_s0060_87b0());
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
}}  // namespace SP::Pollen
