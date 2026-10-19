// src/game/SPEditors/SPCookie.cpp -- migrated from slice(s) s00609790, s0060a720 by tools/migrate/rewrite.py
// Object file: SPEditors/SPCookie.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Pollen/CookieHandler.h"
#include "EA/Thread/Futex.h"
#include "EA/Internet/HTTPHeaders.h"
#include "EA/Internet/HTTPResponse.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Messaging/Server.h"
#include "EA/Internet/IRequestResponseFilter.h"
#include "eastl/allocator.h"
#include "SP/Pollen/cCookie.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "EA/COM/AutoRefCount.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void* cs);
extern char gEmptyString[];  // 0x01667bac
#pragma intrinsic(strlen)
#pragma intrinsic(_InterlockedExchange)

// ---- items of slice s0060a720 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void operator delete(void*);
inline void* operator new(unsigned int, void* p) { return p; }
namespace eastl {
struct allocator_s0060_a720 {
  allocator_s0060_a720() {}
};
}
namespace eastl {
int CompareI(const char* p1, const char* p2, unsigned int n);  // 0x005f7870
}
namespace eastl {
template <typename T>
inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
}
namespace eastl {
template <typename T, typename A = allocator_s0060_a720>
struct basic_string_s0060_a720 {
  typedef unsigned int size_type;
  enum { npos = -1 };
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;

  basic_string_s0060_a720() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  basic_string_s0060_a720(const basic_string_s0060_a720& x);  // 0x0057cb10
  __forceinline ~basic_string_s0060_a720() { DeallocateSelf(); }
  __forceinline void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, mpCapacity - mpBegin);
  }
  void DoFree(T* p, size_type) {
    if (p) EASTL_allocator_deallocate(p);
  }
  basic_string_s0060_a720& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0
  __forceinline basic_string_s0060_a720& operator=(const basic_string_s0060_a720& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  int compare(const basic_string_s0060_a720& x) const;                          // 0x00609fe0
  int comparei(const basic_string_s0060_a720& x) const;                         // 0x00609ee0
  static int comparei(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2) {
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int nMin = min_alt(n1, n2);
    const int cmp = CompareI(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
  }
  size_type rfind(T c, size_type position) const;                    // 0x00609f40
  size_type find(const basic_string_s0060_a720& x, size_type position) const;   // 0x00609f90
  size_type find(T c, size_type position) const;                     // 0x00607580
  basic_string_s0060_a720 substr(size_type position, size_type n) const;        // 0x006082a0
};
}
typedef eastl::basic_string_s0060_a720<char> string8;
namespace EA {
namespace Thread {
template <typename T>
struct AtomicInt_s0060_a720 {
  AtomicInt_s0060_a720() { _InterlockedExchange((volatile long*)&mValue, 0); }
  volatile T mValue;
};
}
}
namespace EA {
namespace Thread {
struct Futex_s0060_a720 {
  uint32_t mCS[6];  // CRITICAL_SECTION
};
}
}
namespace EA {
namespace COM {
template <typename T>
class RefCountTemplate_s0060_a720 {
 public:
  RefCountTemplate_s0060_a720() : mRefCount(0) {}
  virtual ~RefCountTemplate_s0060_a720() {}
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
}
}
namespace EA {
namespace COM {
template <typename T>
class AutoRefCount_s0060_a720 {
 public:
  T* mpObject;
  AutoRefCount_s0060_a720() : mpObject(0) {}
  ~AutoRefCount_s0060_a720() {
    if (mpObject) mpObject->Release();
  }
  AutoRefCount_s0060_a720& operator=(const AutoRefCount_s0060_a720& x);  // 0x00609ea0
};
}
}
namespace SP {
namespace Pollen {
class cCookie_s0060_a720 : public EA::COM::RefCountTemplate_s0060_a720<int> {
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
}
}
namespace SP {
namespace Pollen {
struct cURLParts {
  cURLParts(const char* pURL);  // 0x0094a560
  ~cURLParts();                 // 0x0060a100
  string8& GetPart(int i);      // 0x0094baf0
  uint32_t pad[4];
  string8 mFull;                // +0x10
  string8 mParts[9];            // +0x20
};
}
}
struct ListNodeBase {
  ListNodeBase* mpNext;
  ListNodeBase* mpPrev;
};
namespace EA {
namespace Thread {
struct AutoFutex {
  void* mpFutex;
  AutoFutex(void* p) : mpFutex(p) { EnterCriticalSection(p); }
  ~AutoFutex() { LeaveCriticalSection(mpFutex); }
};  // namespace Thread
}
}
namespace EA {
namespace Internet {
struct HTTPHeaders_s0060_a720 {
  void RemoveHeaderEntry(int fieldID, int index);                        // 0x00944ac0
  bool SetHeaderEntry(int fieldID, const char* pValue);                  // 0x00944db0
  bool GetHeaderEntry(int fieldID, const char** ppValue, int index);     // 0x009420e0
};  // namespace Internet
}
}
struct FixedString512 {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  uint32_t mOverflowAllocator;
  void* mpPoolBegin;
  char mBuffer[512];
  FixedString512& append(const char* pBegin, const char* pEnd);  // 0x0060a150
};
void AppendFormat(FixedString512* pString, const char* pFormat, ...);  // 0x00619510 (sprintf_append)
struct FixedCookieVector {
  SP::Pollen::cCookie_s0060_a720** mpBegin;
  SP::Pollen::cCookie_s0060_a720** mpEnd;
  SP::Pollen::cCookie_s0060_a720** mpCapacity;
  uint32_t mOverflowAllocator;
  void* mpPoolBegin;
  uint32_t pad;
  SP::Pollen::cCookie_s0060_a720* mBuffer[32];
  void DoInsertValue(SP::Pollen::cCookie_s0060_a720** position, SP::Pollen::cCookie_s0060_a720* const& value);  // 0x0060a600
};
char* find_first_of_chars(char* first1, char* last1, const char* first2, const char* last2);  // 0x00609d50
namespace SP {
namespace Pollen {
typedef EA::COM::AutoRefCount_s0060_a720<cCookie_s0060_a720> CookiePtr;
}
}
namespace SP {
namespace Pollen {
struct CookieNode : public ListNodeBase {
  CookiePtr mValue;
};
}
}
namespace SP {
namespace Pollen {
struct CookieIterator {
  CookieNode* mpNode;
  CookieIterator(CookieNode* p) : mpNode(p) {}
  CookieIterator(const CookieIterator& x) : mpNode(x.mpNode) {}
  CookieIterator& operator++() {
    mpNode = (CookieNode*)mpNode->mpNext;
    return *this;
  }
};
}
}
namespace SP {
namespace Pollen {
struct CookieList {
  ListNodeBase mNode;
  uint32_t mAllocator;
  CookieIterator erase(CookieIterator position);  // 0x0060a5a0
  void DoClear();                                 // 0x0060a270
  void DoInit() {
    mNode.mpNext = &mNode;
    mNode.mpPrev = &mNode;
  }
};
}
}
namespace SP {
namespace Pollen {
struct HTTPRequest {
  uint32_t pad0[12];
  cURLParts mURL;                        // +0x30
  char pad1[0x2f4 - 0x30 - sizeof(cURLParts)];
  EA::Internet::HTTPHeaders_s0060_a720 mHeaders;    // +0x2f4
};
}
}
namespace SP {
namespace Pollen {
struct HTTPResponse {
  uint32_t pad0[2];
  const char* mpURL;                     // +0x8
  char pad1[0x4a4 - 0xc];
  EA::Internet::HTTPHeaders_s0060_a720 mHeaders;    // +0x4a4
};
}
}
namespace SP {
namespace Pollen {
class IRequestResponseFilter {
 public:
  IRequestResponseFilter() {}
  virtual ~IRequestResponseFilter() {}
  virtual const char* GetName() = 0;
  virtual bool Filter(HTTPResponse* pResponse) = 0;
  virtual bool Filter(HTTPRequest* pRequest) = 0;
  EA::Thread::AtomicInt_s0060_a720<int> mRefCount;  // +0x4
};
}
}
namespace SP {
namespace Pollen {
class CookieHandler_s0060_a720 : public IRequestResponseFilter {
 public:
  CookieHandler_s0060_a720(unsigned short maxCookies, unsigned int bufferSize);
  virtual ~CookieHandler_s0060_a720();
  virtual const char* GetName();  // 0x0060a710 (SP::Pollen::CookieHandler::GetName)
  virtual bool Filter(HTTPRequest* pRequest);
  virtual bool Filter(HTTPResponse* pResponse);

  void Clear();  // 0x0060a960 (SP::Pollen::CookieHandler::Clear)
  cCookie_s0060_a720* ParseCookieHeader(const char* pHeader);  // 0x0060a340
  bool ApplyURLDefaults(cCookie_s0060_a720* pCookie, const char* pURL);
  void AddCookie(const char* pHeader, const char* pURL);

  char* mCookieParseBuffer;       // +0x8
  unsigned int mBufferSize;       // +0xc
  unsigned short mMaxCookies;     // +0x10
  CookieList mCookies;            // +0x14
  unsigned short mNumCookies;     // +0x20
  char pad24[4];
  EA::Thread::Futex_s0060_a720 mFutex;       // +0x28
};
}
}
namespace SP {
namespace Pollen {
static __forceinline bool DomainMatchesInline(const string8& domain, const string8& host) {
  const int offset = (int)(host.mpEnd - host.mpBegin) - (int)(domain.mpEnd - domain.mpBegin);
  if (_stricmp(host.mpBegin + offset, domain.mpBegin) == 0) {
    if (offset == 0 || *domain.mpBegin == '.' || host.mpBegin[offset - 1] == '.') return true;
  }
  return false;
}
}
}
void operator delete(void* p, const char*);
// ---- items of slice s0060a720 end

// ---- items of slice s00609790 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memset(void*, int, unsigned int);
extern "C" char* __cdecl strcpy(char*, const char*);
#pragma intrinsic(memset)
#pragma intrinsic(strlen, strcpy)
namespace eastl {
struct allocator_s0060_9790 {
  allocator_s0060_9790() {}
};
}
namespace eastl {
int Compare(const char* p1, const char* p2, unsigned int n);   // 0x00606ea0
}
namespace eastl {
template <typename I1, typename I2>
I1 search(I1 first1, I1 last1, I2 first2, I2 last2) {
  if (first2 != last2) {
    I2 temp2(first2);
    ++temp2;
    if (temp2 == last2) return eastl::find(first1, last1, *first2);
    I1 cur1(first1);
    I2 p2;
    while (first1 != last1) {
      while ((first1 != last1) && !(*first1 == *first2)) ++first1;
      if (first1 != last1) {
        p2 = temp2;
        cur1 = first1;
        if (++cur1 != last1) {
          while (*cur1 == *p2) {
            if (++p2 == last2) return first1;
            if (++cur1 == last1) return last1;
          }
          ++first1;
          continue;
        }
      }
      return last1;
    }
  }
  return first1;
}
}
namespace eastl {
template <typename T, typename A = allocator_s0060_9790>
struct basic_string_s0060_9790 {
  typedef unsigned int size_type;
  enum { npos = -1 };
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;

  basic_string_s0060_9790() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mpBegin = (T*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  ~basic_string_s0060_9790() { DeallocateSelf(); }
  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, mpCapacity - mpBegin);
  }
  void DoFree(T* p, size_type) {
    if (p) EASTL_allocator_deallocate(p);
  }
  size_type length() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }
  basic_string_s0060_9790& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0 (char)
  basic_string_s0060_9790& assign(const T* p) { return assign(p, p + strlen(p)); }
  basic_string_s0060_9790& operator=(const T* p);  // 0x006a4380 (char)

  static int compare(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2) {
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int nMin = min_alt(n1, n2);
    const int cmp = Compare(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
  }
  static int comparei(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2) {
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int nMin = min_alt(n1, n2);
    const int cmp = CompareI(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
  }
  int compare(const basic_string_s0060_9790& x) const;
  int comparei(const basic_string_s0060_9790& x) const;
  size_type rfind(T c, size_type position) const;
  size_type find(const basic_string_s0060_9790& x, size_type position) const;
  size_type find(const T* p, size_type position, size_type n) const {
    T* const pBegin = mpBegin;
    T* const pEnd = mpEnd;
    if ((position + n) <= (size_type)(pEnd - pBegin)) {
      const T* const pResult = search(pBegin + position, pEnd, p, p + n);
      if ((pResult != pEnd) || (n == 0)) return (size_type)(pResult - pBegin);
    }
    return (size_type)npos;
  }
};
}
typedef eastl::basic_string_s0060_9790<char> string8_s0060_9790;
namespace SP {
namespace Pollen {
class cCookie_s0060_9790;  // namespace SP
}
}
namespace EA {
namespace COM {
template <typename T>
class RefCountTemplate_s0060_9790 {
 public:
  RefCountTemplate_s0060_9790() : mRefCount(0) {}
  virtual ~RefCountTemplate_s0060_9790() {}
  int AddRef() { return mRefCount += 1; }
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
}
}
namespace SP {
namespace Pollen {
class cCookie_s0060_9790 : public EA::COM::RefCountTemplate_s0060_9790<int> {
 public:
  cCookie_s0060_9790();
  string8_s0060_9790 mName;           // +0x8
  string8_s0060_9790 mValue;          // +0x18
  string8_s0060_9790 mDomain;         // +0x28
  bool mDomainDefaulted;   // +0x38
  unsigned int mMaxAge;    // +0x3c
  string8_s0060_9790 mPath;           // +0x40
  bool mPathDefaulted;     // +0x50
  unsigned short mVersion; // +0x52
};
}
}
// ---- items of slice s00609790 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace SP { namespace Pollen { __declspec(noinline) bool DomainMatches(const string8& domain, const string8& host); }}  // 0x0060a100 (stays in the slice: not this object's)

// @ 0x0060a040
namespace SP { namespace Pollen {
cCookie_s0060_9790::cCookie_s0060_9790()
{}
}}  // namespace SP::Pollen

// @ 0x0060a960
namespace SP { namespace Pollen {
void CookieHandler_s0060_a720::Clear()
{
  EnterCriticalSection(&mFutex);
  mCookies.DoClear();
  mCookies.DoInit();
  mNumCookies = 0;
  LeaveCriticalSection(&mFutex);
}
}}  // namespace SP::Pollen

// @ 0x0060a990
namespace SP { namespace Pollen {
CookieHandler_s0060_a720::CookieHandler_s0060_a720(unsigned short maxCookies, unsigned int bufferSize)
{
  mBufferSize = bufferSize;
  mMaxCookies = maxCookies;
  mCookies.DoInit();
  mNumCookies = 0;
  InitializeCriticalSection(&mFutex);
  mCookieParseBuffer = (char*)operator new(mBufferSize, "UTFInternet/char8_t", 0, 0, 0, 0);
}
}}  // namespace SP::Pollen

// @ 0x0060aa40
namespace SP { namespace Pollen {
bool CookieHandler_s0060_a720::Filter(HTTPRequest* pRequest)
{
  pRequest->mHeaders.RemoveHeaderEntry(0x36, 0);
  string8& host = pRequest->mURL.GetPart(3);
  string8& path = pRequest->mURL.GetPart(5);
  if (host.mpBegin != host.mpEnd && path.mpBegin != path.mpEnd) {
    EA::Thread::AutoFutex lock(&mFutex);
    FixedCookieVector matches;
    matches.mpBegin = matches.mpEnd = matches.mBuffer;
    matches.mpPoolBegin = matches.mBuffer;
    matches.mpCapacity = matches.mBuffer + 32;
    int version = 1;
    for (CookieNode* pNode = (CookieNode*)mCookies.mNode.mpNext; pNode != (CookieNode*)&mCookies.mNode;
         pNode = (CookieNode*)pNode->mpNext) {
      cCookie_s0060_a720* const pCookie = pNode->mValue.mpObject;
      if (path.mpBegin != path.mpEnd) {
        char* const pFound = find_first_of_chars(path.mpBegin, path.mpEnd, pCookie->mPath.mpBegin, pCookie->mPath.mpEnd);
        if (pFound != path.mpEnd && (pFound - path.mpBegin) == 0) {
          if (DomainMatchesInline(pCookie->mDomain, host)) {
            if (version > pNode->mValue.mpObject->mVersion) version = pNode->mValue.mpObject->mVersion;
            cCookie_s0060_a720* const pValue = pNode->mValue.mpObject;
            if (matches.mpEnd < matches.mpCapacity) {
              cCookie_s0060_a720** const pSlot = matches.mpEnd++;
              if (pSlot) *pSlot = pValue;
            } else {
              matches.DoInsertValue(matches.mpEnd, pValue);
            }
          }
        }
      }
    }
    if (matches.mpBegin != matches.mpEnd) {
      FixedString512 header;
      header.mBuffer[0] = 0;
      header.mpBegin = header.mpEnd = header.mBuffer;
      header.mpPoolBegin = header.mBuffer;
      header.mpCapacity = header.mBuffer + 512;
      if (version > 0) AppendFormat(&header, "$Version=%d; ", version);
      for (cCookie_s0060_a720** pp = matches.mpBegin; pp != matches.mpEnd; ++pp) {
        const char* const pName = (*pp)->mName.mpBegin;
        const char* const pValue = (*pp)->mValue.mpBegin;
        const char* e = pName;
        while (*e) ++e;
        header.append(pName, e);
        header.append("=", "=" + 1);
        e = pValue;
        while (*e) ++e;
        header.append(pValue, e);
        header.append("; ", "; " + 2);
        if (version > 0) {
          if (!(*pp)->mDomainDefaulted) {
            const char* const pDomain = (*pp)->mDomain.mpBegin;
            header.append("$Domain=", "$Domain=" + 8);
            e = pDomain;
            while (*e) ++e;
            header.append(pDomain, e);
            header.append("; ", "; " + 2);
          }
          if (!(*pp)->mPathDefaulted) {
            const char* const pPath = (*pp)->mPath.mpBegin;
            header.append("$Path=", "$Path=" + 6);
            e = pPath;
            while (*e) ++e;
            header.append(pPath, e);
            header.append("; ", "; " + 2);
          }
        }
      }
      pRequest->mHeaders.SetHeaderEntry(0x36, header.mpBegin);
      if ((header.mpCapacity - header.mpBegin) > 1 && header.mpBegin && header.mpBegin != header.mpPoolBegin)
        EASTL_allocator_deallocate(header.mpBegin);
    }
    if (matches.mpBegin && matches.mpBegin != matches.mpPoolBegin) EASTL_allocator_deallocate(matches.mpBegin);
  }
  return true;
}
}}  // namespace SP::Pollen

// @ 0x0060ada0
namespace SP { namespace Pollen {
void CookieHandler_s0060_a720::AddCookie(const char* pHeader, const char* pURL)
{
  struct RefHolder {
    cCookie_s0060_a720* mpObject;
  } ref;
  ref.mpObject = ParseCookieHeader(pHeader);
  cCookie_s0060_a720* const pNew = ref.mpObject;
  if (pNew) {
    pNew->AddRef();
    if (ApplyURLDefaults(pNew, pURL)) {
      for (CookieIterator it((CookieNode*)mCookies.mNode.mpNext); it.mpNode != (CookieNode*)&mCookies.mNode; ++it) {
        cCookie_s0060_a720* pOld = it.mpNode->mValue.mpObject;
        if (string8::comparei(pOld->mName.mpBegin, pOld->mName.mpEnd, pNew->mName.mpBegin, pNew->mName.mpEnd) == 0 &&
            pOld->mDomain.compare(pNew->mDomain) == 0 && pOld->mPath.comparei(pNew->mPath) == 0) {
          if (pNew->mMaxAge == 0) {
            mCookies.erase(it);
            --mNumCookies;
          } else {
            it.mpNode->mValue = *(CookiePtr*)&ref;
          }
          return;
        }
      }
      ListNodeBase* const pFirst = mCookies.mNode.mpNext;
      CookieNode* const pNode = (CookieNode*)EASTL_allocator_allocate(sizeof(CookieNode), "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
      if (&pNode->mValue) {
        pNode->mValue.mpObject = pNew;
        pNew->AddRef();
      }
      pNode->mpNext = pFirst;
      pNode->mpPrev = pFirst->mpPrev;
      pFirst->mpPrev->mpNext = pNode;
      pFirst->mpPrev = pNode;
      ++mNumCookies;
      if (mNumCookies > mMaxCookies) {
        CookieNode* const pLast = (CookieNode*)mCookies.mNode.mpPrev;
        pLast->mpPrev->mpNext = pLast->mpNext;
        pLast->mpNext->mpPrev = pLast->mpPrev;
        pLast->mValue.~CookiePtr();
        EASTL_allocator_deallocate(pLast);
        --mNumCookies;
      }
    }
    pNew->Release();
  }
}
}}  // namespace SP::Pollen

// @ 0x0060afa0
namespace SP { namespace Pollen {
bool CookieHandler_s0060_a720::Filter(HTTPResponse* pResponse)
{
  EA::Thread::AutoFutex lock(&mFutex);
  const char* pHeader;
  for (int i = 0; pResponse->mHeaders.GetHeaderEntry(0x34, &pHeader, i); ++i) AddCookie(pHeader, pResponse->mpURL);
  for (int i = 0; pResponse->mHeaders.GetHeaderEntry(0x35, &pHeader, i); ++i) AddCookie(pHeader, pResponse->mpURL);
  return true;
}
}}  // namespace SP::Pollen
