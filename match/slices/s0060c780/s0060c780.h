// Shared declarations for the HTTP multipart body stream tail, Pollinator helpers and EASTL deque instances (b003 slice 2).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-  (no /EHsc)
#pragma once
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);  // E8 call (0x011e0744)
extern "C" unsigned int __cdecl strlen(const char*);
#pragma intrinsic(strlen)
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void* cs);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void* cs);
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void operator delete(void*);
inline void* operator new(unsigned int, void* p) { return p; }

extern char gEmptyString[];  // 0x01667bac

namespace eastl {
struct allocator {
  allocator() {}
};
int CompareI(const char* p1, const char* p2, unsigned int n);  // 0x005f7870
template <typename T>
inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }

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
  basic_string(const basic_string& x);  // 0x0057cb10
  __forceinline ~basic_string() { DeallocateSelf(); }
  __forceinline void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, mpCapacity - mpBegin);
  }
  void DoFree(T* p, size_type) {
    if (p) EASTL_allocator_deallocate(p);
  }
  __forceinline basic_string(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) {
    const size_type n = (size_type)strlen(p);
    AllocateSelf(n + 1);
    T* const pDest = mpBegin;
    memcpy(pDest, p, n);
    mpEnd = pDest + n;
    *mpEnd = 0;
  }
  size_type size() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }
  basic_string& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0
  basic_string& assign(const T* p, size_type n);          // 0x0060bcd0
  basic_string& assign(const T* p);                       // 0x006a4380
  basic_string& append(const T* pBegin, const T* pEnd);   // 0x00455d60
  basic_string& append(const T* p);                       // 0x0060c4e0
  basic_string& sprintf(const T* pFormat, ...);           // 0x00472fe0
  void AllocateSelf(size_type n);                         // 0x00475ab0
  __forceinline basic_string& operator=(const basic_string& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  int compare(const basic_string& x) const;                          // 0x00609fe0
  int comparei(const basic_string& x) const;                         // 0x00609ee0
  static int comparei(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2) {
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int nMin = min_alt(n1, n2);
    const int cmp = CompareI(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
  }
  size_type rfind(T c, size_type position) const;                    // 0x00609f40
  size_type find(const basic_string& x, size_type position) const;   // 0x00609f90
  size_type find(T c, size_type position) const;                     // 0x00607580
  basic_string substr(size_type position, size_type n) const;        // 0x006082a0
};
}  // namespace eastl
typedef eastl::basic_string<char> string8;

namespace EA {
namespace Thread {
template <typename T>
struct AtomicInt {
  AtomicInt() { _InterlockedExchange((volatile long*)&mValue, 0); }
  volatile T mValue;
};
struct Futex {
  uint32_t mCS[6];  // CRITICAL_SECTION
};
}  // namespace Thread
namespace COM {
template <typename T>
class RefCountTemplate {
 public:
  RefCountTemplate() : mRefCount(0) {}
  virtual ~RefCountTemplate() {}
  int AddRef() { int n = mRefCount + 1; mRefCount = n; return n; }
  int Release() {
    int n = (*(volatile int*)&mRefCount += -1);
    if (n == 0) {
      mRefCount = 1;
      delete this;
      return 0;
    }
    return n;
  }
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
  AutoRefCount& operator=(const AutoRefCount& x);  // 0x00609ea0
};
}  // namespace COM
}  // namespace EA

namespace SP {
namespace Pollen {

class cCookie : public EA::COM::RefCountTemplate<int> {
 public:
  string8 mName;           // +0x8
  string8 mValue;          // +0x18
  string8 mDomain;         // +0x28
  bool mDomainDefaulted;   // +0x38
  unsigned int mMaxAge;    // +0x3c
  string8 mPath;           // +0x40
  bool mPathDefaulted;     // +0x50
  unsigned short mVersion; // +0x52
};

// Parsed URL pieces (class name guessed; the part indices are the ones the cookie code uses).
struct cURLParts {
  cURLParts(const char* pURL);  // 0x0094a560
  ~cURLParts();                 // 0x0060a100
  string8& GetPart(int i);      // 0x0094baf0
  uint32_t pad[4];
  string8 mFull;                // +0x10
  string8 mParts[9];            // +0x20
};

}  // namespace Pollen
}  // namespace SP

// ---- UI stubs (same as slice s0060a720) ----
#define PV(n) virtual void pv##n();

namespace UTFWin {
class IWinProc {
 public:
  virtual ~IWinProc() {}
  virtual void pv0() = 0;
  virtual void pv1() = 0;
  virtual void pv2() = 0;
  virtual void pv3() = 0;
};
class IWindow {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual uint32_t GetControlID();  // +0x1c
  PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31)
  virtual void SetCaption(const wchar_t* pText);  // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
  PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55)
  PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63)
  PV(64)
  virtual void AddWinProc(IWinProc* pWinProc);     // +0x104
  virtual void RemoveWinProc(IWinProc* pWinProc);  // +0x108
};
}  // namespace UTFWin

class IMessageListener {
 public:
  PV(0) PV(1)
};
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void MessageSend(uint32_t messageID, void* pData, void* pListener);  // +0x14
  virtual void MessagePost(uint32_t messageID, void* pData, int, int);  // +0x18
  PV(7) PV(8)
  virtual void AddListener(IMessageListener* pListener, uint32_t messageID);   // +0x24
  PV(10)
  virtual void RemoveListener(IMessageListener* pListener, uint32_t messageID, int priority);  // +0x2c
};
class IRefCounted {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void pv2();
  virtual IRefCounted* Query(uint32_t id);  // +0xc
};
class IObjectTemplateDB {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool IsBusy();  // +0x1c
  virtual void Reset();   // +0x20
};

namespace SP {
IMessageServer* MessageServer();           // 0x0067dcc0
IObjectTemplateDB* ObjectTemplateDB();     // 0x0067cb40
class cString {
 public:
  cString();                                              // 0x006b5060
  ~cString();                                             // 0x006b5240
  void Load(uint32_t tableID, uint32_t instanceID, int);  // 0x006b54b0
  const wchar_t* GetText();                               // 0x006b55c0
  char pad[0x14];
};
}  // namespace SP

struct ResourceKey {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
class cSPUILayout {
 public:
  cSPUILayout();                                                        // 0x00810000
  bool Init(const ResourceKey* pKey, int, uint32_t);                   // 0x008120d0
  UTFWin::IWindow* FindWindowByID(uint32_t controlID, int bRecursive);  // 0x008105b0
  void Shutdown(int);                                                   // 0x00811ad0
  ~cSPUILayout();                                                       // 0x00811fe0
  char pad[0x18];
};
namespace SPUIHelpers {
void BeginModal(UTFWin::IWindow* pWindow, void* pWinProc, int);  // 0x008099a0
void EndModal(UTFWin::IWindow* pWindow, uint32_t result, int);          // 0x00809c50
void AutoSizeWindowForText(UTFWin::IWindow* pWindow, int, int);    // 0x00806e40
}  // namespace SPUIHelpers
void MultiHeapObject_operator_delete(void* p);  // 0x00951330
void operator delete(void* p, const char*);
void* AllocUIObject(unsigned size, unsigned align, const char* pName, void* pHeap);  // 0x009512d0
void* GetUIHeap();                                                                   // 0x009512c0
extern IRefCounted* gpMessageHandle;  // 0x015f3f80

