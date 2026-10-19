// src/game/SPEditors/SPCanvasResFilter.cpp -- migrated from slice(s) s006087b0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPCanvasResFilter.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Internet/HTTPHeaders.h"
#include "EA/Internet/IRequestResponseFilter.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cPollinator.h"
#include "SP/cPropertyList.h"
#include "SP/Pollen/cRegistrationDialog.h"
#include "cSPUILayout.h"
#include "cSPVector4.h"
#include "SP/cString.h"
#include "SP/cStringTokenTranslator.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" unsigned int __cdecl strlen(const char*);
extern char gEmptyString[];  // 0x01667bac (shared "" for char and wchar_t strings)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(strlen)

// ---- items of slice s006087b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" unsigned int __cdecl strlen(const char*);
extern char gEmptyString[];  // 0x01667bac (shared "" for char and wchar_t strings)
namespace eastl {
struct allocator_s0060_87b0 {
  allocator_s0060_87b0() {}
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
typedef eastl::basic_string_s0060_87b0<char> string8;
template <>
__declspec(noinline) int eastl::basic_string_s0060_87b0<char>::compare(const char* p) const {
  return compare(mpBegin, mpEnd, p, p + strlen(p));
}
template <>
__declspec(noinline) string8 eastl::basic_string_s0060_87b0<char>::substr(size_type position, size_type n) const {
  return basic_string_s0060_87b0(mpBegin + position,
                      mpBegin + position + min_alt(n, (size_type)(mpEnd - mpBegin) - position),
                      mAllocator);
}
template <>
__declspec(noinline) string8 eastl::basic_string_s0060_87b0<char>::left(size_type n) const {
  const size_type nLength = length();
  if (n < nLength) return substr(0, n);
  return *this;
}
template <>
__declspec(noinline) string8::size_type eastl::basic_string_s0060_87b0<char>::find(char c, size_type position) const {
  if (position < (size_type)(mpEnd - mpBegin)) {
    const char* p = mpBegin + position;
    while (p != mpEnd && *p != c) ++p;
    if (p != mpEnd) return (size_type)(p - mpBegin);
  }
  return (size_type)npos;
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
namespace Messaging {
class IHandler_s0060_87b0 {
 public:
  virtual ~IHandler_s0060_87b0() {}
  virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
};  // namespace Messaging
}
}
namespace EA {
class IMessageServer {
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
namespace Messaging {
IMessageServer* GetServer();  // 0x00883860
}
}
namespace SP {
class IConfigManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
  virtual int GetInt(uint32_t id);  // +0x30
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
  virtual void GetUserName(int a, string8& out);  // +0x4c
};
}
namespace SP {
IConfigManager* ConfigManager();  // 0x0067dd30
}
namespace EA {
namespace XHTML {
namespace Resource {
struct HeaderMap {
  void Set(const char* name, const char* value);  // 0x00944d00
  void AddHeaderEntry(const char* name, const string8& value);  // 0x00944cb0
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
namespace Thread {
template <typename T>
struct AtomicInt_s0060_87b0 {
  AtomicInt_s0060_87b0() { _InterlockedExchange((volatile long*)&mValue, 0); }
  volatile T mValue;
};  // namespace Thread
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
namespace EA {
namespace Internet {
class IRequestResponseFilter_s0060_87b0 : public COM::RefCountTemplate_s0060_87b0<Thread::AtomicInt_s0060_87b0<int> > {
 public:
  virtual void Filter(XHTML::Resource::Request* pRequest) = 0;
  void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};  // namespace Internet
}
}
namespace SP {
namespace Pollen {
class cCanvasResFilter : public EA::Internet::IRequestResponseFilter_s0060_87b0 {
 public:
  cCanvasResFilter();
  virtual ~cCanvasResFilter() {}
  virtual void Filter(EA::XHTML::Resource::Request* pRequest);
  bool UpdateHeaderString();
  bool Init();
  bool mbInited;                // +0x8
  string8 mHeaderString;        // +0xc
};
}
}
namespace SP {
namespace Pollen {
class cBuddyModeFilter : public EA::Internet::IRequestResponseFilter_s0060_87b0, public EA::Messaging::IHandler_s0060_87b0 {
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
}
}
namespace SP {
namespace Pollen {
struct Rect {
  int left, top, right, bottom;
};
}
}
namespace SP {
namespace Pollen {
class ICanvas {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual void GetClientRect(Rect& r);  // +0x3c
};
}
}
namespace SP {
namespace Pollen {
ICanvas* Canvas();  // 0x0067dcf0
}
}
// ---- items of slice s006087b0 end

// @ 0x00609460
namespace SP { namespace Pollen {
void cCanvasResFilter::Filter(EA::XHTML::Resource::Request* pRequest)
{
  pRequest->mHeaders.AddHeaderEntry("AppResolution", mHeaderString);
}
}}  // namespace SP::Pollen

// @ 0x00609480
namespace SP { namespace Pollen {
void cBuddyModeFilter::Filter(EA::XHTML::Resource::Request* pRequest)
{
  pRequest->mHeaders.AddHeaderEntry("BuddyMode", mHeaderString);
}
}}  // namespace SP::Pollen

// @ 0x006094a0
namespace SP { namespace Pollen {
cCanvasResFilter::cCanvasResFilter()
: mbInited(false) {}
}}  // namespace SP::Pollen

// @ 0x006094e0
namespace SP { namespace Pollen {
cBuddyModeFilter::cBuddyModeFilter()
: mbInited(false) {}
}}  // namespace SP::Pollen

// @ 0x006095d0
namespace SP { namespace Pollen {
bool cBuddyModeFilter::UpdateHeaderString()
{
  if (ConfigManager()) {
    if (ConfigManager()->GetInt(0x5de7b4a) == 1)
      mHeaderString = "true";
    else
      mHeaderString = "false";
    return true;
  }
  return false;
}
}}  // namespace SP::Pollen

// @ 0x00609630
namespace SP { namespace Pollen {
bool cBuddyModeFilter::Init()
{
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
}}  // namespace SP::Pollen

// @ 0x00609690
namespace SP { namespace Pollen {
bool cBuddyModeFilter::HandleMessage(uint32_t messageID, void* pMessage)
{
  switch (messageID) {
    case 0x238de9c: {
      EA::IMessageServer* pServer = EA::Messaging::GetServer();
      if (pServer) {
        pServer->RemoveListener(static_cast<EA::Messaging::IHandler_s0060_87b0*>(this), 0x5de7b4a, -9999);
        pServer->RemoveListener(static_cast<EA::Messaging::IHandler_s0060_87b0*>(this), 0x238de9c, -9999);
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
}}  // namespace SP::Pollen

// @ 0x00609710
namespace SP { namespace Pollen {
bool cCanvasResFilter::UpdateHeaderString()
{
  ICanvas* pCanvas = Canvas();
  if (pCanvas) {
    Rect r;
    pCanvas->GetClientRect(r);
    mHeaderString.sprintf("%dx%d", r.right - r.left, r.bottom - r.top);
    return true;
  }
  return false;
}
}}  // namespace SP::Pollen
