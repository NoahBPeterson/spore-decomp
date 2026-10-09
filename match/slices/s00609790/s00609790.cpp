// An AES-encrypting EA::IO::IStream wrapper (OpenSSL EVP), EASTL string/search helpers and the
// Pollen HTTP cookie handler (SP::Pollen::cCookie, CookieHandler::ParseCookieHeader).
// Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

#define PV(n) virtual void pv##n();

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);  // E8 call (not imported)
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)
extern "C" char* __cdecl strcpy(char*, const char*);
#pragma intrinsic(strlen, strcpy)
extern "C" __declspec(dllimport) int __cdecl isspace(int);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" __declspec(dllimport) char* __cdecl strchr(const char*, int);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
inline void* operator new(unsigned int, void* p) { return p; }

extern char gEmptyString[];  // 0x01667bac

namespace eastl {
struct allocator {
  allocator() {}
};
// fixed_vector_allocator<..., true, eastl::allocator>: overflow allocator + pool pointer.
struct fixed_allocator {
  allocator mOverflowAllocator;  // +0x0 (padded to 4)
  void* mpPoolBegin;             // +0x4
  void* allocate(unsigned int n) {
    return EASTL_allocator_allocate(n, "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
  }
  void deallocate(void* p) {
    if (p != mpPoolBegin) EASTL_allocator_deallocate(p);
  }
};

template <typename T>
inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
template <typename T>
inline const T& max_alt(const T& a, const T& b) { return a < b ? b : a; }

int Compare(const char* p1, const char* p2, unsigned int n);   // 0x00606ea0
int CompareI(const char* p1, const char* p2, unsigned int n);  // 0x005f7870

// @ 0x00609d50
template <typename I1, typename I2>
I1 find_first_of(I1 first1, I1 last1, I2 first2, I2 last2) {
  for (; first1 != last1; ++first1) {
    for (I2 i = first2; i != last2; ++i) {
      if (*first1 == *i) return first1;
    }
  }
  return last1;
}

// @ 0x00609d90
template <typename I1, typename I2>
inline I1 find(I1 first, I1 last, const I2& value) {
  while ((first != last) && !(*first == value)) ++first;
  return first;
}

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

template <typename T>
inline const T* CharTypeStringRFind(const T* pRBegin, const T* pREnd, const T c) {
  while (pRBegin > pREnd) {
    if (*(pRBegin - 1) == c) return pRBegin;
    --pRBegin;
  }
  return pREnd;
}

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
  ~basic_string() { DeallocateSelf(); }
  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, mpCapacity - mpBegin);
  }
  void DoFree(T* p, size_type) {
    if (p) EASTL_allocator_deallocate(p);
  }
  size_type length() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }
  basic_string& assign(const T* pBegin, const T* pEnd);  // 0x00454cb0 (char)
  basic_string& assign(const T* p) { return assign(p, p + strlen(p)); }
  basic_string& operator=(const T* p);  // 0x006a4380 (char)

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
  int compare(const basic_string& x) const;
  int comparei(const basic_string& x) const;
  size_type rfind(T c, size_type position) const;
  size_type find(const basic_string& x, size_type position) const;
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

// Same layout with the fixed (pool + overflow) allocator.
template <typename T>
struct fixed_string_base {
  typedef unsigned int size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  fixed_allocator mAllocator;  // +0xc

  T* DoAllocate(size_type n) { return (T*)mAllocator.allocate(n * sizeof(T)); }
  void DoFree(T* p, size_type) {
    if (p) mAllocator.deallocate(p);
  }
  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, mpCapacity - mpBegin);
  }
  static size_type GetNewCapacity(size_type currentCapacity) {
    return (currentCapacity > 8) ? (2 * currentCapacity) : 8;
  }
  static T* CharStringUninitializedCopy(const T* pSource, const T* pSourceEnd, T* pDestination) {
    memcpy(pDestination, pSource, (size_t)(pSourceEnd - pSource) * sizeof(T));
    return pDestination + (pSourceEnd - pSource);
  }
  T* erase(T* pFirst, T* pLast) {
    if (pFirst != pLast) {
      memmove(pFirst, pLast, (size_t)((mpEnd - pLast) + 1) * sizeof(T));
      mpEnd -= (pLast - pFirst);
    }
    return pFirst;
  }
  fixed_string_base& append(const T* pBegin, const T* pEnd);
  fixed_string_base& assign(const T* pBegin, const T* pEnd);
};

template <typename T>
struct fixed_vector_base {
  typedef unsigned int size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  fixed_allocator mAllocator;  // +0xc

  T* DoAllocate(size_type n) { return n ? (T*)mAllocator.allocate(n * sizeof(T)) : 0; }
  void DoFree(T* p, size_type) {
    if (p) mAllocator.deallocate(p);
  }
  static size_type GetNewCapacity(size_type currentCapacity) {
    return (currentCapacity > 0) ? (2 * currentCapacity) : 1;
  }
  void DoInsertValue(T* position, const T& value);
};

template <typename T>
inline T* copy_backward(T* first, T* last, T* resultEnd) {
  return (T*)memmove(resultEnd - (last - first), first, (size_t)((char*)last - (char*)first));
}
template <typename T>
inline T* uninitialized_move_ptr(T* first, T* last, T* dest) {
  return (T*)memcpy(dest, first, (size_t)((char*)last - (char*)first)) + (last - first);
}
}  // namespace eastl
typedef eastl::basic_string<char> string8;
template char* eastl::find_first_of<char*, const char*>(char*, char*, const char*, const char*);
template char* eastl::search<char*, const char*>(char*, char*, const char*, const char*);

// @ 0x00609ee0
template <>
int string8::comparei(const basic_string& x) const {
  return comparei(mpBegin, mpEnd, x.mpBegin, x.mpEnd);
}

// @ 0x00609f40
template <>
string8::size_type string8::rfind(char c, size_type position) const {
  const size_type nLength = (size_type)(mpEnd - mpBegin);
  if (nLength) {
    const char* const pEnd = mpBegin + min_alt(nLength - 1, position) + 1;
    const char* const pResult = CharTypeStringRFind(pEnd, mpBegin, c);
    if (pResult != mpBegin) return (size_type)((pResult - 1) - mpBegin);
  }
  return (size_type)npos;
}

// @ 0x00609f90
template <>
string8::size_type string8::find(const basic_string& x, size_type position) const {
  return find(x.mpBegin, position, (size_type)(x.mpEnd - x.mpBegin));
}

// @ 0x00609fe0
template <>
int string8::compare(const basic_string& x) const {
  return compare(mpBegin, mpEnd, x.mpBegin, x.mpEnd);
}

// @ 0x0060a150
template <>
eastl::fixed_string_base<char>& eastl::fixed_string_base<char>::append(const char* pBegin, const char* pEnd) {
  if (pBegin != pEnd) {
    const size_type nOldSize = (size_type)(mpEnd - mpBegin);
    const size_type n = (size_type)(pEnd - pBegin);
    const size_type nCapacity = (size_type)((mpCapacity - mpBegin) - 1);
    if ((nOldSize + n) > nCapacity) {
      const size_type nLength = max_alt((size_type)GetNewCapacity(nCapacity), (size_type)(nOldSize + n)) + 1;
      char* const pNewBegin = DoAllocate(nLength);
      char* pNewEnd = CharStringUninitializedCopy(mpBegin, mpEnd, pNewBegin);
      pNewEnd = CharStringUninitializedCopy(pBegin, pEnd, pNewEnd);
      *pNewEnd = 0;
      DeallocateSelf();
      mpBegin = pNewBegin;
      mpEnd = pNewEnd;
      mpCapacity = pNewBegin + nLength;
    } else {
      const char* const pTemp = pBegin + 1;
      CharStringUninitializedCopy(pTemp, pEnd, mpEnd + 1);
      mpEnd[n] = 0;
      *mpEnd = *pBegin;
      mpEnd += n;
    }
  }
  return *this;
}

// @ 0x0060a2c0
template <>
eastl::fixed_string_base<char>& eastl::fixed_string_base<char>::assign(const char* pBegin, const char* pEnd) {
  const size_type n = (size_type)(pEnd - pBegin);
  if (n <= (size_type)(mpEnd - mpBegin)) {
    memcpy(mpBegin, pBegin, n);
    erase(mpBegin + n, mpEnd);
  } else {
    memcpy(mpBegin, pBegin, (size_t)(mpEnd - mpBegin));
    append(pBegin + (size_type)(mpEnd - mpBegin), pEnd);
  }
  return *this;
}

namespace SP {
namespace Pollen {
class cCookie;
}
}  // namespace SP

// @ 0x0060a600
template <>
void eastl::fixed_vector_base<SP::Pollen::cCookie*>::DoInsertValue(SP::Pollen::cCookie** position,
                                                                  SP::Pollen::cCookie* const& value) {
  typedef SP::Pollen::cCookie* T;
  if (mpEnd != mpCapacity) {
    const T* pValue = &value;
    if ((pValue >= position) && (pValue < mpEnd)) ++pValue;
    ::new ((void*)mpEnd) T(*(mpEnd - 1));
    copy_backward(position, mpEnd - 1, mpEnd);
    *position = *pValue;
    ++mpEnd;
  } else {
    const size_type nPrevSize = (size_type)(mpEnd - mpBegin);
    const size_type nNewSize = GetNewCapacity(nPrevSize);
    T* const pNewData = DoAllocate(nNewSize);
    T* pNewEnd = uninitialized_move_ptr(mpBegin, position, pNewData);
    ::new ((void*)pNewEnd) T(value);
    pNewEnd = uninitialized_move_ptr(position, mpEnd, ++pNewEnd);
    DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
    mpBegin = pNewData;
    mpEnd = pNewEnd;
    mpCapacity = pNewData + nNewSize;
  }
}

// ---------------------------------------------------------------------------------------------
struct evp_cipher_st;
struct evp_cipher_ctx_st {
  uint32_t pad[35];  // size 0x8c
};
extern "C" {
void EVP_CIPHER_CTX_init(evp_cipher_ctx_st* ctx);
int EVP_CIPHER_CTX_cleanup(evp_cipher_ctx_st* ctx);
const evp_cipher_st* EVP_aes_128_cfb8();  // FUN_01176e10 (exact cipher unverified)
int EVP_EncryptInit_ex(evp_cipher_ctx_st* ctx, const evp_cipher_st* type, void* impl, const unsigned char* key,
                       const unsigned char* iv);
int EVP_EncryptUpdate(evp_cipher_ctx_st* ctx, unsigned char* out, int* outl, const unsigned char* in, int inl);
int EVP_DecryptUpdate(evp_cipher_ctx_st* ctx, unsigned char* out, int* outl, const unsigned char* in, int inl);
}

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
  RefCountTemplate() : mRefCount(0) {}
  virtual ~RefCountTemplate() {}
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
template <typename T>
class RefCountTemplateA {
 public:
  virtual ~RefCountTemplateA() {}
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
  AutoRefCount& operator=(const AutoRefCount& x) {
    T* const pObject = x.mpObject;
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
};
}  // namespace COM
namespace IO {
class IStream {
 public:
  virtual ~IStream() {}
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual uint32_t GetType() const = 0;
  virtual int GetAccessFlags() const = 0;
  virtual int GetState() const = 0;
  virtual bool Close() = 0;
  virtual uint32_t GetSize() const = 0;
  virtual bool SetSize(uint32_t size) = 0;
  virtual int GetPosition(int positionType) const = 0;
  virtual bool SetPosition(int position, int positionType) = 0;
  virtual uint32_t GetAvailable() const = 0;
  virtual uint32_t Read(void* pData, uint32_t nSize) = 0;
  virtual bool Flush() = 0;
  virtual bool Write(const void* pData, uint32_t nSize) = 0;
};
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount(T* p) : mpObject(p) {
    if (mpObject) mpObject->AddRef();
  }
  ~AutoRefCount() {
    if (mpObject) mpObject->Release();
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}  // namespace IO
}  // namespace EA

namespace SP {
namespace Pollen {

// AES stream wrapper (class name not in the PDB; guessed).
class cEncryptedStream : public EA::IO::IStream, public EA::COM::RefCountTemplateA<EA::Thread::AtomicInt<int> > {
 public:
  cEncryptedStream(EA::IO::IStream* pStream);
  virtual ~cEncryptedStream();
  virtual int AddRef();
  virtual int Release();
  virtual uint32_t GetType() const;
  virtual int GetAccessFlags() const;
  virtual int GetState() const;
  virtual bool Close();
  virtual uint32_t GetSize() const;
  virtual bool SetSize(uint32_t size);
  virtual int GetPosition(int positionType) const;
  virtual bool SetPosition(int position, int positionType);
  virtual uint32_t GetAvailable() const;
  virtual uint32_t Read(void* pData, uint32_t nSize);
  virtual bool Flush();
  virtual bool Write(const void* pData, uint32_t nSize);
  virtual bool Init(const uint8_t* pKey);  // +0x3c

  struct Key {
    uint32_t mData[4];
  };
  evp_cipher_ctx_st mContext;                   // +0xc
  EA::IO::AutoRefCount<EA::IO::IStream> mpStream;  // +0x98
  Key mKey;                                     // +0x9c
  int mState;                                   // +0xac
};

extern const uint8_t kKeyMask[16];  // 0x013fb0dc

// @ 0x00609790
cEncryptedStream::cEncryptedStream(EA::IO::IStream* pStream) : mpStream(pStream), mState(-2) {}

// @ 0x006097f0
bool cEncryptedStream::Init(const uint8_t* pKey) {
  if (mpStream) {
    uint8_t key[16];
    for (int i = 0; i < 16; ++i) key[i] = pKey[i] ^ kKeyMask[i];
    EVP_CIPHER_CTX_init(&mContext);
    if (EVP_EncryptInit_ex(&mContext, EVP_aes_128_cfb8(), 0, key, 0) > 0) {
      mKey = *(const Key*)pKey;
      mState = 0;
      return true;
    }
    mState = -1;
  }
  return false;
}

// @ 0x00609910
int cEncryptedStream::GetAccessFlags() const {
  if (mpStream && mState == 0) return mpStream->GetAccessFlags();
  return 0;
}

// @ 0x00609930
int cEncryptedStream::GetState() const {
  if (!mpStream) return -1;
  if (mState) return mState;
  return mpStream->GetState();
}

// @ 0x00609960
bool cEncryptedStream::Close() {
  if (!mpStream) return false;
  EVP_CIPHER_CTX_cleanup(&mContext);
  memset(&mKey, 0, sizeof(mKey));
  mState = -2;
  return mpStream->Close();
}

// @ 0x006099b0
uint32_t cEncryptedStream::GetSize() const {
  if (mpStream && mState == 0) return mpStream->GetSize();
  return (uint32_t)-1;
}

// @ 0x006099d0
int cEncryptedStream::GetPosition(int positionType) const {
  if (mpStream && mState == 0) return mpStream->GetPosition(positionType);
  return -1;
}

// @ 0x00609a00
bool cEncryptedStream::SetPosition(int position, int positionType) {
  if (mpStream && mState == 0) {
    if (position == 0 && positionType == 0) {
      if (!Init((const uint8_t*)&mKey)) return false;
      if (mpStream->SetPosition(0, 0)) return true;
    }
    mState = -1;
  }
  return false;
}

// @ 0x00609a70
uint32_t cEncryptedStream::GetAvailable() const {
  if (mpStream && mState == 0) return mpStream->GetAvailable();
  return (uint32_t)-1;
}

// @ 0x00609a90
uint32_t cEncryptedStream::Read(void* pData, uint32_t nSize) {
  uint8_t* pOut = (uint8_t*)pData;
  if (!pOut) mState = -1;
  if (mpStream && mState == 0) {
    uint32_t nTotal = 0;
    uint32_t nRead;
    do {
      uint8_t buffer[0x400];
      int nOut;
      nRead = mpStream->Read(buffer, sizeof(buffer));
      if (EVP_DecryptUpdate(&mContext, pOut, &nOut, buffer, (int)nRead) <= 0) return (uint32_t)-1;
      pOut += nOut;
      nTotal += nRead;
    } while (nRead > 0 && nRead < nSize);
    return nTotal;
  }
  return (uint32_t)-1;
}

// @ 0x00609b50
bool cEncryptedStream::SetSize(uint32_t size) {
  if (mpStream && mState == 0) return mpStream->SetSize(size);
  return false;
}

// @ 0x00609b80
bool cEncryptedStream::Flush() {
  if (mpStream && mState == 0) return mpStream->Flush();
  return false;
}

// @ 0x00609ba0
bool cEncryptedStream::Write(const void* pData, uint32_t nSize) {
  if (!pData) mState = -1;
  if (mpStream && mState == 0) {
    while (nSize > 0) {
      uint8_t buffer[0x400];
      int nOut;
      const uint32_t nChunk = nSize > sizeof(buffer) ? sizeof(buffer) : nSize;
      if (EVP_EncryptUpdate(&mContext, buffer, &nOut, (const uint8_t*)pData, (int)nChunk) > 0) {
        if (!mpStream->Write(buffer, (uint32_t)nOut)) return false;
        pData = (const uint8_t*)pData + nOut;
        nSize -= nOut;
      }
    }
    return true;
  }
  return false;
}

// @ 0x00609c70  (scalar deleting destructor)
cEncryptedStream::~cEncryptedStream() { Close(); }

// ---------------------------------------------------------------------------------------------
// Cookies

// @ 0x00609cc0
static char* TrimWhitespace(char* s) {
  if (!s) return s;
  int len = (int)strlen(s);
  while (len > 0) {
    if (!isspace((unsigned char)s[--len])) break;
    s[len] = 0;
  }
  while (*s) {
    if (!isspace((unsigned char)*s)) break;
    *s = 0;
    ++s;
  }
  return *s ? s : 0;
}

// @ 0x00609e50
static __declspec(noinline) bool DomainMatches(const string8& domain, const string8& host) {
  const int offset = (int)(host.mpEnd - host.mpBegin) - (int)(domain.mpEnd - domain.mpBegin);
  if (_stricmp(host.mpBegin + offset, domain.mpBegin) == 0) {
    if (offset == 0 || *domain.mpBegin == '.' || host.mpBegin[offset - 1] == '.') return true;
  }
  return false;
}

class cCookie : public EA::COM::RefCountTemplate<int> {
 public:
  cCookie();
  string8 mName;           // +0x8
  string8 mValue;          // +0x18
  string8 mDomain;         // +0x28
  bool mDomainDefaulted;   // +0x38
  unsigned int mMaxAge;    // +0x3c
  string8 mPath;           // +0x40
  bool mPathDefaulted;     // +0x50
  unsigned short mVersion; // +0x52
};

// Reconstruction-only caller so the static helper above is emitted (real caller not in this batch).
bool CookieDomainMatches(const cCookie* pCookie, const string8& host) { return DomainMatches(pCookie->mDomain, host); }

// @ 0x0060a040
cCookie::cCookie() {}

// @ 0x0060a080
void DestroyCookie(cCookie* p) { p->~cCookie(); }

// Parsed URL pieces (layout only; name guessed).
struct cURLParts {
  uint32_t pad[4];
  string8 mFull;         // +0x10
  string8 mParts[9];     // +0x20
};

// @ 0x0060a100
void DestroyURLParts(cURLParts* p) { p->~cURLParts(); }

}  // namespace Pollen
}  // namespace SP

// @ 0x00609e40
namespace EA {
namespace Thread {
struct Futex {
  void* mCS;
  void Unlock();
};
struct AutoFutex {
  void* mpFutex;
  ~AutoFutex();
};
}  // namespace Thread
}  // namespace EA
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);
EA::Thread::AutoFutex::~AutoFutex() { LeaveCriticalSection(mpFutex); }

// @ 0x00609ea0
template EA::COM::AutoRefCount<SP::Pollen::cCookie>& EA::COM::AutoRefCount<SP::Pollen::cCookie>::operator=(
    const AutoRefCount&);

namespace eastl {
struct ListNodeBase {
  ListNodeBase* mpNext;
  ListNodeBase* mpPrev;
  void remove() {
    mpPrev->mpNext = mpNext;
    mpNext->mpPrev = mpPrev;
  }
};
template <typename T>
struct ListNode : public ListNodeBase {
  T mValue;
};
template <typename T>
struct ListIterator {
  ListNode<T>* mpNode;
  ListIterator& operator++() {
    mpNode = (ListNode<T>*)mpNode->mpNext;
    return *this;
  }
};
template <typename T, typename A = allocator>
struct ListBase {
  ListNodeBase mNode;
  A mAllocator;
  void DoClear();
};
template <typename T, typename A = allocator>
struct list : public ListBase<T, A> {
  typedef ListIterator<T> iterator;
  void DoErase(ListNodeBase* pNode) {
    pNode->remove();
    ((ListNode<T>*)pNode)->~ListNode<T>();
    EASTL_allocator_deallocate(pNode);
  }
  iterator erase(iterator position);
};
}  // namespace eastl

typedef EA::COM::AutoRefCount<SP::Pollen::cCookie> CookiePtr;

// @ 0x0060a270
template <>
void eastl::ListBase<CookiePtr>::DoClear() {
  ListNode<CookiePtr>* p = (ListNode<CookiePtr>*)mNode.mpNext;
  while (p != (ListNode<CookiePtr>*)&mNode) {
    ListNode<CookiePtr>* const pTemp = p;
    p = (ListNode<CookiePtr>*)p->mpNext;
    pTemp->~ListNode<CookiePtr>();
    EASTL_allocator_deallocate(pTemp);
  }
}

// @ 0x0060a5a0
template <>
eastl::list<CookiePtr>::iterator eastl::list<CookiePtr>::erase(iterator position) {
  ++position;
  DoErase(position.mpNode->mpPrev);
  return position;
}

namespace SP {
namespace Pollen {
char* Strtok(char* str, const char* delims, char** context);  // FUN_0092cd20
extern const char* kCookieDomain;   // 0x0151eb8c ("domain")
extern const char* kCookieMaxAge;   // 0x0151eb90 ("max-age")
extern const char* kCookiePath;     // 0x0151eb94 ("path")
extern const char* kCookieVersion;  // 0x0151eb98 ("version")

class CookieHandler : public EA::COM::RefCountTemplateA<EA::Thread::AtomicInt<int> > {
 public:
  cCookie* ParseCookieHeader(const char* pHeader);
  char* mCookieParseBuffer;                // +0x8
  unsigned int mBufferSize;                // +0xc
  unsigned short mMaxCookies;              // +0x10
  eastl::list<CookiePtr> mCookies;         // +0x14
  unsigned short mNumCookies;              // +0x20
};

static inline void SplitNameValue(char*& pName, char*& pValue) {
  pValue = 0;
  if (pName) {
    char* const pEquals = strchr(pName, '=');
    if (pEquals) {
      *pEquals = 0;
      pValue = TrimWhitespace(pEquals + 1);
    }
  }
  pName = TrimWhitespace(pName);
}

// @ 0x0060a340
cCookie* CookieHandler::ParseCookieHeader(const char* pHeader) {
  if (strlen(pHeader) >= mBufferSize) return 0;
  strcpy(mCookieParseBuffer, pHeader);
  char* pContext;
  char* pName = Strtok(mCookieParseBuffer, ";", &pContext);
  char* pValue;
  SplitNameValue(pName, pValue);
  if (!pName || *pName == '$') return 0;
  cCookie* pCookie = new ("UTFInternet/SessionCookie", 0, 0, 0, 0) cCookie();
  pCookie->mVersion = 0;
  pCookie->mMaxAge = 1;
  pCookie->mDomainDefaulted = true;
  pCookie->mPathDefaulted = true;
  pCookie->mName.assign(pName);
  if (pValue) pCookie->mValue = pValue;
  while ((pName = Strtok(0, ";", &pContext)) != 0) {
    SplitNameValue(pName, pValue);
    if (pName) {
      if (_stricmp(pName, kCookieDomain) == 0) {
        if (pValue && strlen(pValue) > 2) {
          pCookie->mDomain = pValue;
          pCookie->mDomainDefaulted = false;
        }
      } else if (_stricmp(pName, kCookieMaxAge) == 0) {
        if (pValue && *pValue == '0') pCookie->mMaxAge = 0;
      } else if (_stricmp(pName, kCookiePath) == 0) {
        if (pValue && strlen(pValue)) {
          pCookie->mPathDefaulted = false;
          pCookie->mPath = pValue;
        }
      } else if (_stricmp(pName, kCookieVersion) == 0) {
        if (pValue && strlen(pValue) == 1 && *pValue == '1') pCookie->mVersion = 1;
      }
    }
  }
  return pCookie;
}

}  // namespace Pollen
}  // namespace SP
