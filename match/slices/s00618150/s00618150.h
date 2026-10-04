// Shared declarations for the Pollen (Spore.com transactions) slices. Flags: /O2 /MD /Gy /TP (no /EHsc, no /arch).
#pragma once
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile*, long);
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(memcpy)
extern "C" unsigned int __cdecl strlen(const char*);
#pragma intrinsic(strlen)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file,
                   int line);
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}

extern char gEmptyString[];  // 0x01667bac (shared "" for char strings)

namespace eastl {
struct allocator {
  allocator() {}
};
template <typename T, typename A = allocator>
struct basic_string {
  typedef unsigned int size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;
  basic_string() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  ~basic_string() { DeallocateSelf(); }
  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin);
  }
  void DoFree(T* p) {
    if (p) EASTL_allocator_deallocate(p);
  }
  __forceinline explicit basic_string(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) {
    const size_type n = (size_type)strlen(p);
    AllocateSelfN(n + 1);
    memcpy(mpBegin, p, n * sizeof(T));
    mpEnd = mpBegin + n;
    *mpEnd = 0;
  }
  __forceinline void AllocateSelfN(size_type n) {
    if (n > 1) {
      mpBegin = (T*)EASTL_allocator_allocate(
          n * sizeof(T), "Editor", 0, 0,
          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
          0xd1);
      mpEnd = mpBegin;
      mpCapacity = mpBegin + n;
    } else {
      mpBegin = (T*)gEmptyString;
      mpEnd = mpBegin;
      mpCapacity = mpBegin + 1;
    }
  }
  struct CtorZero {};
  basic_string(CtorZero) : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  void RangeInit(const T* p);  // 0x0057cc10
  struct CtorDoNotInitialize {};
  basic_string(CtorDoNotInitialize, size_type n) : mpBegin(0), mpEnd(0), mpCapacity(0) {
    AllocateSelf(n + 1);
    *mpEnd = 0;
  }
  void AllocateSelf(size_type n);                        // 0x00475ab0
  basic_string& append(const T* pBegin, const T* pEnd);  // 0x00455d60
  basic_string& append(const basic_string& x) { return append(x.mpBegin, x.mpEnd); }
  basic_string& append_sprintf_va_list(const T* pFormat, void* args);
  void set_capacity(size_type n);  // 0x006174e0
  basic_string& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0 (char), 0x00423650 (wchar_t)
  basic_string& operator=(const basic_string& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  const T* c_str() const { return mpBegin; }
  size_type size() const { return (size_type)(mpEnd - mpBegin); }
};
}  // namespace eastl
typedef eastl::basic_string<char> string8;

namespace EA {
template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}  // namespace EA

namespace SP {
namespace Pollen {
class cITransaction : public EA::RefCountVTemplate<int> {
 public:
  virtual ~cITransaction() {}
};
}  // namespace Pollen
}  // namespace SP
typedef eastl::basic_string<wchar_t> string16;
