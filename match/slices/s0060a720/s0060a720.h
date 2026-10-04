// Shared declarations for the Pollen cookie handler + editor DB-check dialog region (b003 slice 0).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-  (no /EHsc)
#pragma once
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
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
  basic_string& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0
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
