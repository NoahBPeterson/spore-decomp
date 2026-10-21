// slice s005f8fe0 -- SP::Thumbnail::cImportExport import/export helpers and eastl string16 / hashtable
// glue (find + insert for the Key<->wstring maps and the editor string set, plus a deque ctor/dtor).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>

#include <stdarg.h>

typedef unsigned int uint32;

#define PV(n) virtual void _pv##n();

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);
inline void* operator new(size_t, void* p) throw() { return p; }

#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// allocator / deallocator used by every eastl container in this TU
void EASTL_allocator_deallocate(void* p);  // 0x00f47380

namespace eastl {
template <typename T>
class basic_string {
 public:
  basic_string* append_sprintf(const char* fmt, ...);
  void append_sprintf_va_list(const char* fmt, va_list* args);  // 0x00475930
  char pad[16];
};
}  // namespace eastl

namespace EA {
namespace Locale {
bool MakeLocaleAvailable(const void* p, const void* q);  // 0x0087d9a0
}
}  // namespace EA

void FUN_005f8690(void* a, void* b);  // 0x005f8690
void FUN_005f8700(void* a, void* b);  // 0x005f8700

namespace SP {
namespace Thumbnail {
class cImportExport {
 public:
  uint32 mPad[0x184 / 4];  // +0x000
  unsigned char mFlag184;  // +0x184
  bool SetupExportFolderPath(uint32 a, void* path, uint32 b);  // 0x005f9310
};
}  // namespace Thumbnail
}  // namespace SP

namespace eastl {
template class basic_string<char>;
// @ 0x005F9450
basic_string<char>* basic_string<char>::append_sprintf(const char* fmt, ...) {
  append_sprintf_va_list(fmt, (va_list*)(&fmt + 1));
  return this;
}
}  // namespace eastl

// ---------------------------------------------------------------------------------------------
// Shared eastl building blocks

void* EASTL_allocator_allocate(unsigned n, const char* name, int a, int b, int c, int d);  // 0xf473a0

namespace eastl {

class allocator { public:
  void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
  void deallocate(void* p) { operator delete[](p); }
};

struct true_type {};
struct false_type {};

// eastl::basic_string<wchar_t> (4 dwords: begin / end / capacity + empty allocator padding)
struct WStr {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  allocator mAllocator;
  WStr(const WStr& o);                     // 0x0056e2d0
  WStr& operator=(const WStr& o);          // 0x0057cb60
  void assign(const wchar_t* b, const wchar_t* e);  // 0x00423650
  void Append(const wchar_t* b, const wchar_t* e);  // 0x00429580
  WStr& replace(uint32 position, uint32 n, const wchar_t* p);  // 0x005f8f80
  ~WStr() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin) EASTL_allocator_deallocate(mpBegin);
  }
};

struct Key {
  uint32 a;
  uint32 b;
  uint32 c;
};
inline bool operator==(const Key& x, const Key& y) {
  return x.a == y.a && x.b == y.b && x.c == y.c;
}

template <typename T1, typename T2>
struct pair {
  T1 first;
  T2 second;
  pair(const T1& a, const T2& b) : first(a), second(b) {}
  pair(const pair& p);
};

template <typename T1, typename T2>
__declspec(noinline) pair<T1, T2>::pair(const pair& p) : first(p.first), second(p.second) {}

struct prime_rehash_policy {
  float mfMaxLoadFactor;
  float mfGrowthFactor;
  uint32 mnNextResize;
  struct RehashResult {
    bool first;
    uint32 second;
  };
  RehashResult GetRehashRequired(uint32 nBucketCount, uint32 nElementCount, uint32 nElementAdd);  // 0x00921440
};

// string comparison: (begin,end) of two WStr objects (cdecl)
bool __cdecl Str16Equal(const void* a, const void* b);  // 0x0087d9a0

}  // namespace eastl

using eastl::allocator;
using eastl::false_type;
using eastl::Key;
using eastl::pair;
using eastl::prime_rehash_policy;
using eastl::true_type;
using eastl::WStr;

// =============================================================================================
// hashtable<pair<WStr,Key>, ...> : wstring -> Key map (MapWK)

typedef pair<WStr, Key> PairWK;
struct NodeWK {
  PairWK mValue;
  NodeWK* mpNext;
};
struct IterWK {
  NodeWK* mpNode;
  NodeWK** mpBucket;
  IterWK(NodeWK* n, NodeWK** b) : mpNode(n), mpBucket(b) {}
  IterWK(NodeWK** b) : mpNode(*b), mpBucket(b) {}
  IterWK(const IterWK& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {}
};

struct MapWK {
  uint32 mHash;                       // +0x00
  NodeWK** mpBucketArray;             // +0x04
  uint32 mnBucketCount;               // +0x08
  uint32 mnElementCount;              // +0x0c
  prime_rehash_policy mRehashPolicy;  // +0x10
  allocator mAllocator;               // +0x1c

  __forceinline NodeWK* DoFindNode(NodeWK* pNode, const WStr& k) {
    for (; pNode; pNode = pNode->mpNext)
      if (Str16Equal(&k, &pNode->mValue.first)) return pNode;
    return 0;
  }
  __forceinline NodeWK* DoAllocateNode(const PairWK& value) {
    NodeWK* p = (NodeWK*)mAllocator.allocate(sizeof(NodeWK));
    if (p) new (p) PairWK(value);
    p->mpNext = 0;
    return p;
  }
  void DoRehash(uint32 nBucketCount);  // 0x005f85c0
  IterWK find(const WStr& k);
  pair<IterWK, bool> DoInsertValue(const PairWK& value, true_type);
};

// @ 0x005F8FE0
IterWK MapWK::find(const WStr& k) {
  const wchar_t* c = k.mpBegin;
  uint32 h = 0x811c9dc5u;
  uint32 ch;
  while ((ch = (uint32)*c++) != 0) h = (h * 16777619u) ^ ch;
  const uint32 cnt = mnBucketCount;
  const uint32 n = h % cnt;
  NodeWK** const arr = mpBucketArray;
  NodeWK** const pb = arr + n;
  NodeWK* pNode = *pb;
  for (; pNode; pNode = pNode->mpNext)
    if (Str16Equal(&k, &pNode->mValue.first)) break;
  return pNode ? IterWK(pNode, pb) : IterWK(arr + cnt);
}

// @ 0x005F9470
pair<IterWK, bool> MapWK::DoInsertValue(const PairWK& value, true_type) {
  const wchar_t* cp = value.first.mpBegin;
  uint32 c = 0x811c9dc5u;
  uint32 ch;
  while ((ch = (uint32)*cp++) != 0) c = (c * 16777619u) ^ ch;
  uint32 n = c % mnBucketCount;
  NodeWK* const pNode = DoFindNode(mpBucketArray[n], value.first);
  if (pNode == 0) {
    const prime_rehash_policy::RehashResult bRehash = mRehashPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
    NodeWK* const pNodeNew = DoAllocateNode(value);
    if (bRehash.first) {
      n = c % bRehash.second;
      DoRehash(bRehash.second);
    }
    pNodeNew->mpNext = mpBucketArray[n];
    mpBucketArray[n] = pNodeNew;
    ++mnElementCount;
    return pair<IterWK, bool>(IterWK(pNodeNew, mpBucketArray + n), true);
  }
  return pair<IterWK, bool>(IterWK(pNode, mpBucketArray + n), false);
}

// =============================================================================================
// hashtable<WStr, ...> : wstring set (uses same FNV hash + string equality)

struct NodeW {
  WStr mValue;
  NodeW* mpNext;
};
struct IterW {
  NodeW* mpNode;
  NodeW** mpBucket;
  IterW(NodeW* n, NodeW** b) : mpNode(n), mpBucket(b) {}
  IterW(NodeW** b) : mpNode(*b), mpBucket(b) {}
  IterW(const IterW& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {}
};

struct SetWStr {
  uint32 mHash;                       // +0x00
  NodeW** mpBucketArray;              // +0x04
  uint32 mnBucketCount;               // +0x08
  uint32 mnElementCount;              // +0x0c
  prime_rehash_policy mRehashPolicy;  // +0x10
  allocator mAllocator;               // +0x1c

  __forceinline NodeW* DoFindNode(NodeW* pNode, const WStr& k) {
    for (; pNode; pNode = pNode->mpNext)
      if (Str16Equal(&k, &pNode->mValue)) return pNode;
    return 0;
  }
  __forceinline NodeW* DoAllocateNode(const WStr& value) {
    NodeW* p = (NodeW*)mAllocator.allocate(sizeof(NodeW));
    if (p) new (p) WStr(value);
    p->mpNext = 0;
    return p;
  }
  void DoRehash(uint32 nBucketCount);  // 0x005f8770
  pair<IterW, bool> DoInsertValue(const WStr& value, true_type);
};

// @ 0x005F9100
pair<IterW, bool> SetWStr::DoInsertValue(const WStr& value, true_type) {
  const wchar_t* cp = value.mpBegin;
  uint32 h = 0x811c9dc5u;
  uint32 ch;
  while ((ch = (uint32)*cp++) != 0) h = (h * 16777619u) ^ ch;
  uint32 n = h % mnBucketCount;
  NodeW* const pNode = DoFindNode(mpBucketArray[n], value);
  if (pNode == 0) {
    const prime_rehash_policy::RehashResult bRehash = mRehashPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
    NodeW* const pNodeNew = DoAllocateNode(value);
    if (bRehash.first) {
      n = h % bRehash.second;
      DoRehash(bRehash.second);
    }
    pNodeNew->mpNext = mpBucketArray[n];
    mpBucketArray[n] = pNodeNew;
    ++mnElementCount;
    return pair<IterW, bool>(IterW(pNodeNew, mpBucketArray + n), true);
  }
  return pair<IterW, bool>(IterW(pNode, mpBucketArray + n), false);
}

// =============================================================================================
// hashtable<pair<Key,WStr>, KeyXorHash> : Key -> wstring multimap (MapKW)

typedef pair<Key, WStr> PairKW;
struct NodeKW {
  PairKW mValue;
  NodeKW* mpNext;
};
struct IterKW {
  NodeKW* mpNode;
  NodeKW** mpBucket;
  IterKW(NodeKW* n, NodeKW** b) : mpNode(n), mpBucket(b) {}
  IterKW(NodeKW** b) : mpNode(*b), mpBucket(b) {}
  IterKW(const IterKW& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {}
};

struct MapKW {
  uint32 mHash;                       // +0x00
  NodeKW** mpBucketArray;             // +0x04
  uint32 mnBucketCount;               // +0x08
  uint32 mnElementCount;              // +0x0c
  prime_rehash_policy mRehashPolicy;  // +0x10
  allocator mAllocator;               // +0x1c

  __forceinline NodeKW* DoAllocateNode(const PairKW& value) {
    NodeKW* p = (NodeKW*)mAllocator.allocate(sizeof(NodeKW));
    if (p) new (p) PairKW(value);
    p->mpNext = 0;
    return p;
  }
  void DoRehash(uint32 nBucketCount);  // 0x005f7ad0
  pair<IterKW, bool> DoInsertValue(const PairKW& value, false_type);
};

// @ 0x005F95A0
pair<IterKW, bool> MapKW::DoInsertValue(const PairKW& value, false_type) {
  const prime_rehash_policy::RehashResult bRehash = mRehashPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
  if (bRehash.first) DoRehash(bRehash.second);
  const uint32 n = (value.first.a ^ value.first.c) % mnBucketCount;
  NodeKW* const pNodeNew = DoAllocateNode(value);
  NodeKW* pNode = mpBucketArray[n];
  NodeKW* p = pNode;
  while (p && !(value.first == p->mValue.first)) p = p->mpNext;
  if (p) {
    pNodeNew->mpNext = p->mpNext;
    p->mpNext = pNodeNew;
  } else {
    pNodeNew->mpNext = pNode;
    mpBucketArray[n] = pNodeNew;
  }
  ++mnElementCount;
  return pair<IterKW, bool>(IterKW(pNodeNew, mpBucketArray + n), true);
}

// ---------------------------------------------------------------------------------------------
// eastl::pair copy-ctor instantiations used by the node allocators above
template struct pair<WStr, Key>;
template struct pair<Key, WStr>;

// =============================================================================================
// DequeBase<T, core_allocator_adapter, 4> : deque of 0x30-byte records with a string member.

namespace EA {
namespace Allocator {
class ICoreAllocator {
 public:
  PV(0) PV(1)
  virtual void* AllocFlags(size_t size, const char* name, unsigned flags);  // +0x08
  virtual void Free(void* p, size_t size);                                  // +0x0c
};
}  // namespace Allocator
}  // namespace EA

namespace eastl {

struct core_allocator_adapter {
  EA::Allocator::ICoreAllocator* mpCoreAllocator;
  unsigned mnFlags;
  void* allocate(size_t n) { return mpCoreAllocator->AllocFlags(n, 0, mnFlags); }
  void deallocate(void* p, size_t n) { mpCoreAllocator->Free(p, n); }
};

// 0x30-byte deque record: header dword + string16 at +4
struct DequeItem {
  uint32 mHead;
  WStr mName;         // +0x04
  uint32 mRest[7];    // +0x14
};

template <typename T, typename Allocator, unsigned kDequeSubarraySize>
struct DequeIterator {
  T* mpCurrent;
  T* mpBegin;
  T* mpEnd;
  T** mpCurrentArrayPtr;
  DequeIterator() : mpCurrent(0), mpBegin(0), mpEnd(0), mpCurrentArrayPtr(0) {}
  void SetSubarray() {
    mpBegin = *mpCurrentArrayPtr;
    mpEnd = mpBegin + kDequeSubarraySize;
  }
  DequeIterator& operator++() {
    ++mpCurrent;
    if (mpCurrent == mpEnd) {
      ++mpCurrentArrayPtr;
      SetSubarray();
      mpCurrent = mpBegin;
    }
    return *this;
  }
};

template <typename T, typename Allocator, unsigned kDequeSubarraySize>
struct DequeBase { private:
 public:
  typedef DequeIterator<T, Allocator, kDequeSubarraySize> iterator;
  T** mpPtrArray;         // +0x00
  size_t mnPtrArraySize;  // +0x04
  iterator mItBegin;      // +0x08
  iterator mItEnd;        // +0x18
  Allocator mAllocator;   // +0x28

  explicit DequeBase(const Allocator& allocator);
  ~DequeBase();
  T** DoAllocatePtrArray(size_t n) { return (T**)mAllocator.allocate(n * sizeof(T*)); }
  T* DoAllocateSubarray() { return (T*)mAllocator.allocate(kDequeSubarraySize * sizeof(T)); }
  void DoInit(size_t n);  // 0x005f8840
};

// @ 0x005F9680
template <typename T, typename Allocator, unsigned kDequeSubarraySize>
DequeBase<T, Allocator, kDequeSubarraySize>::DequeBase(const Allocator& allocator)
    : mpPtrArray(0), mnPtrArraySize(0), mAllocator(allocator) {
  DoInit(0);
}

// @ 0x005F96C0
template <typename T, typename Allocator, unsigned kDequeSubarraySize>
DequeBase<T, Allocator, kDequeSubarraySize>::~DequeBase() {
  T* p = mItBegin.mpCurrent;
  T** ppAry = mItBegin.mpCurrentArrayPtr;
  T* pSubEnd = mItBegin.mpEnd;
  while (p != mItEnd.mpCurrent) {
    p->~T();
    ++p;
    if (p == pSubEnd) {
      p = *++ppAry;
      pSubEnd = p + kDequeSubarraySize;
    }
  }
  if (mpPtrArray) {
    T** pEnd = mItEnd.mpCurrentArrayPtr + 1;
    for (T** q = mItBegin.mpCurrentArrayPtr; q < pEnd; ++q)
      if (*q) mAllocator.deallocate(*q, kDequeSubarraySize * sizeof(T));
  }
  if (mpPtrArray) mAllocator.deallocate(mpPtrArray, mnPtrArraySize * sizeof(T*));
}

template struct DequeBase<DequeItem, core_allocator_adapter, 4>;

}  // namespace eastl

// =============================================================================================
// eastl string16 -> Key pair construction shims (LTCG-generated single-object helpers).

// @ 0x005F9080
void* FUN_005f9080(PairWK* pThis, const WStr* pStr, const Key* pKey) {
  new (pThis) PairWK(*pStr, *pKey);
  return pThis;
}

// @ 0x005F90C0
void* FUN_005f90c0(PairKW* pThis, const Key* pKey, const WStr* pStr) {
  new (pThis) PairKW(*pKey, *pStr);
  return pThis;
}

// =============================================================================================
// eastl::basic_string<wchar_t> property accessor table (switch on a 32-bit field id).

namespace eastl {
struct StringProps {
  uint32 mPad[0x104 / 4];  // +0x000 .. +0x103
  WStr m104;               // +0x104
  WStr m114;               // +0x114
  WStr m124;               // +0x124
  WStr m134;               // +0x134
  WStr m144;               // +0x144
  WStr m154;               // +0x154
  WStr m164;               // +0x164
  WStr m174;               // +0x174
  bool Prop(uint32 code, WStr& out);
};

// @ 0x005F9230
bool StringProps::Prop(uint32 code, WStr& out) {
  switch (code) {
    case 0x2399be55u:
      out = m124;
      break;
    case 0x04f684a4u:
      out = m164;
      break;
    case 0x24682294u:
      out = m144;
      break;
    case 0x2b978c46u:
      out = m114;
      break;
    case 0x366a930du:
      if (&out != &m174) out.assign(m174.mpBegin, m174.mpEnd);
      break;
    case 0x438f6347u:
      if (&out != &m134) out.assign(m134.mpBegin, m134.mpEnd);
      break;
    case 0x3d97a8e4u:
      if (&out != &m104) out.assign(m104.mpBegin, m104.mpEnd);
      break;
    case 0x476a98c7u:
      out = m154;
      break;
    default:
      break;
  }
  return true;
}
}  // namespace eastl

// =============================================================================================
// SP::Thumbnail::cImportExport::SetupExportFolderPath

namespace SP {
class cString {
 public:
  cString(uint32 a, uint32 b, const wchar_t* s);  // 0x006b5770
  ~cString();                                     // 0x006b5240
  const wchar_t* GetText();                       // 0x006b55c0
};
}  // namespace SP

void FUN_00688830(uint32 a, void* p, int b);                 // 0x00688830
bool __cdecl EnsureDirectoryExists(const wchar_t* path);      // 0x00932ae0

extern wchar_t gSlashStr[];  // 0x013fa030

static const wchar_t* WEnd(const wchar_t* p) {
  while (*p) ++p;
  return p;
}

// @ 0x005F9310
bool SP::Thumbnail::cImportExport::SetupExportFolderPath(uint32 a, void* path, uint32 b) {
  if (b == 0xffffffffu) b = 0x19f76d11u;
  SP::cString text(b, a, L"Default Folder Thumb");
  FUN_00688830(0xa0214bu, path, 0);
  eastl::WStr* pPath = (eastl::WStr*)path;
  if (!mFlag184) {
    const wchar_t* pDir = L"Thumbnails/";
    pPath->Append(pDir, WEnd(pDir));
  }
  const wchar_t* pText = text.GetText();
  pPath->Append(pText, WEnd(pText));
  const uint32 nLen = (uint32)(pPath->mpEnd - pPath->mpBegin);
  const wchar_t cLast = pPath->mpBegin[nLen - 1];
  if (cLast == (wchar_t)0xff0f) {
    pPath->replace(nLen - 1, 1, gSlashStr);
  } else if (cLast != L'/') {
    pPath->Append(gSlashStr, WEnd(gSlashStr));
  }
  return EnsureDirectoryExists(pPath->mpBegin);
}

// @ 0x005F9760
void FUN_005f9760() {}
// @ 0x005F97C0
void FUN_005f97c0() {}
