// src/game/SPEngine/SPID.cpp -- migrated from slice(s) s005f6df0, s0068c330, s005f7da0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPID.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include "EA/ResourceMan/Key.h"
#include "EA/Stopwatch.h"
#include "SP/cISPCreatureAnimWorld.h"
#include "SP/cSPEditorPaintTheme.h"
#include "cSPMatrix3.h"
#include "SP/cSPSwatch.h"
#include "cSPUILayeredObject.h"
#include "cSPUIModelsAndEffectsRenderer.h"
#include "SP/cSwatch3DView.h"
#include <math.h>

// ---- items of slice s005f7da0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);
inline void* operator new(size_t, void* p) throw() { return p; }
#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
namespace EA {
namespace ResourceMan {
class Key_s005f_7da0 { public:
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
  bool operator==(const Key_s005f_7da0& b) const { return instanceID == b.instanceID && typeID == b.typeID && groupID == b.groupID; }
};  // namespace ResourceMan
}
}
using EA::ResourceMan::Key_s005f_7da0;
namespace eastl {
class allocator_s005f_7da0 { public:
  void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
  void deallocate(void* p) { operator delete[](p); }
};
}
namespace eastl {
template <typename T>
inline const T& max_alt(const T& a, const T& b) {
  return a < b ? b : a;
}
}
namespace eastl {
extern char gEmptyString8[2];
}
namespace eastl {
extern wchar_t gEmptyString16[2];
}
namespace eastl {
inline const char* GetEmptyString(char) { return gEmptyString8; }
}
namespace eastl {
inline const wchar_t* GetEmptyString(wchar_t) { return gEmptyString16; }
}
namespace eastl {
template <typename T>
inline size_t CharStrlen(const T* p) {
  const T* pCurrent = p;
  while (*pCurrent) ++pCurrent;
  return (size_t)(pCurrent - p);
}
}
namespace eastl {
template <typename T>
class basic_string_s005f_7da0 {
 public:
  typedef T* iterator;
  typedef size_t size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  allocator_s005f_7da0 mAllocator;

  basic_string_s005f_7da0() { AllocateSelf(); }
  basic_string_s005f_7da0(const basic_string_s005f_7da0& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
  basic_string_s005f_7da0(size_type n, T c, const allocator_s005f_7da0& a);
  ~basic_string_s005f_7da0() { DeallocateSelf(); }

  size_type length() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }

  void AllocateSelf() {
    mpBegin = const_cast<T*>(GetEmptyString(T()));
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  void AllocateSelf(size_type n);  // out of line
  T* DoAllocate(size_type n) { return (T*)mAllocator.allocate(n * sizeof(T)); }
  void DoFree(T* p, size_type) {
    if (p) mAllocator.deallocate(p);
  }
  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
  }
  size_type GetNewCapacity(size_type currentCapacity) { return (currentCapacity > 8) ? (2 * currentCapacity) : 8; }
  void RangeInitialize(const T* pBegin, const T* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelf(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
  void RangeInitialize(size_type n, T c) {
    AllocateSelf(n + 1);
    mpEnd = CharStringUninitializedFillN(mpBegin, n, c);
    *mpEnd = 0;
  }
  static T* CharStringUninitializedFillN(T* pDestination, size_t n, const T c) {
    memset(pDestination, (unsigned char)c, n);
    return pDestination + n;
  }
  static T* CharStringUninitializedCopy(const T* pSource, const T* pSourceEnd, T* pDestination) {
    memcpy(pDestination, pSource, (size_t)(pSourceEnd - pSource) * sizeof(T));
    return pDestination + (pSourceEnd - pSource);
  }
  iterator erase(iterator pFirst, iterator pLast) {
    if (pFirst != pLast) {
      memmove(pFirst, pLast, (size_t)((mpEnd - pLast) + 1) * sizeof(T));
      const iterator pNewEnd = mpEnd - (pLast - pFirst);
      mpEnd = pNewEnd;
    }
    return pFirst;
  }

  void insert(iterator p, const T* pBegin, const T* pEnd);
  basic_string_s005f_7da0& replace(iterator pBegin, iterator pEnd, const T* pBegin2, const T* pEnd2);
  basic_string_s005f_7da0& replace(size_type position, size_type n, const T* p);
  static int compare(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2);  // 0x00576970
  int compare(const T* p) const { return compare(mpBegin, mpEnd, p, p + CharStrlen(p)); }
};
}
namespace eastl {
typedef basic_string_s005f_7da0<wchar_t> string16;
}
namespace eastl {
template class basic_string_s005f_7da0<wchar_t>;
}
namespace eastl {
template basic_string_s005f_7da0<char>::basic_string_s005f_7da0(size_type, char, const allocator_s005f_7da0&);
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s005f_7da0 {
  T1 first;
  T2 second;
  pair_s005f_7da0(const T1& x, const T2& y) : first(x), second(y) {}
  pair_s005f_7da0(const pair_s005f_7da0& p) : first(p.first), second(p.second) {}
  ~pair_s005f_7da0() {}
};
}
namespace eastl {
template struct pair_s005f_7da0<Key_s005f_7da0, string16>;
}
namespace eastl {
template <typename Value>
struct hash_node_s005f_7da0 {
  Value mValue;
  hash_node_s005f_7da0* mpNext;
};
}
namespace eastl {
template <typename Node>
struct hashtable_iterator_base {
  Node* mpNode;
  Node** mpBucket;
  hashtable_iterator_base(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
};
}
namespace eastl {
template <typename T, typename Node>
struct hashtable_iterator : public hashtable_iterator_base<Node> {
  typedef hashtable_iterator_base<Node> base_type;
  using base_type::mpNode;
  using base_type::mpBucket;
  hashtable_iterator(Node* pNode = 0, Node** pBucket = 0) : base_type(pNode, pBucket) {}
  explicit hashtable_iterator(Node** pBucket) : base_type(*pBucket, pBucket) {}
  hashtable_iterator(const hashtable_iterator& x) : base_type(x.mpNode, x.mpBucket) {}
  template <typename U>
  hashtable_iterator(const hashtable_iterator<U, Node>& x) : base_type(x.mpNode, x.mpBucket) {}
  void increment() {
    mpNode = mpNode->mpNext;
    while (mpNode == 0) mpNode = *++mpBucket;
  }
  void increment_bucket() {
    ++mpBucket;
    while (*mpBucket == 0) ++mpBucket;
    mpNode = *mpBucket;
  }
  hashtable_iterator& operator++() {
    increment();
    return *this;
  }
  bool operator!=(const hashtable_iterator& x) const { return mpNode != x.mpNode; }
  bool operator==(const hashtable_iterator& x) const { return mpNode == x.mpNode; }
  T* operator->() const { return &mpNode->mValue; }
};
}
namespace eastl {
struct true_type {};
}
namespace eastl {
struct prime_rehash_policy_s005f_7da0 {
  float mfMaxLoadFactor;
  float mfGrowthFactor;
  uint32_t mnNextResize;
  struct RehashResult {
    bool first;
    uint32_t second;
  };
  RehashResult GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd);  // 0x00921440
};
}
namespace eastl {
struct KeyGroupHash {
  uint32_t operator()(const Key_s005f_7da0& k) const { return k.groupID; }
};
}
namespace eastl {
struct KeyMixHash {
  uint32_t operator()(const Key_s005f_7da0& k) const { return k.instanceID ^ k.groupID; }
};
}
namespace eastl {
template <typename Value, typename Hash>
class hashtable_s005f_7da0 {
 public:
  typedef hash_node_s005f_7da0<Value> node_type;
  typedef hashtable_iterator<Value, node_type> iterator;
  typedef hashtable_iterator<const Value, node_type> const_iterator;
  struct insert_return_type {
    iterator first;
    bool second;
    insert_return_type(const iterator& i, bool b) : first(i), second(b) {}
  };

  Hash mHash;                        // +0x00
  node_type** mpBucketArray;         // +0x04
  uint32_t mnBucketCount;            // +0x08
  uint32_t mnElementCount;           // +0x0c
  prime_rehash_policy_s005f_7da0 mRehashPolicy;  // +0x10
  allocator_s005f_7da0 mAllocator;              // +0x1c

  iterator begin();  // out of line
  iterator begin_inline() {
    iterator i(mpBucketArray);
    if (!i.mpNode) i.increment_bucket();
    return i;
  }
  iterator end() { return iterator(mpBucketArray + mnBucketCount); }

  __forceinline node_type* DoFindNode(node_type* pNode, const Key_s005f_7da0& k) {
    for (; pNode; pNode = pNode->mpNext) {
      if (k == pNode->mValue.first) return pNode;
    }
    return 0;
  }
  void DoFreeNode(node_type* pNode) { mAllocator.deallocate(pNode); }
  void DoRehash(uint32_t nNewBucketCount);
  node_type* DoAllocateNode(const Value& value);

  iterator find(const Key_s005f_7da0& k);
  pair_s005f_7da0<iterator, iterator> equal_range(const Key_s005f_7da0& k);
  uint32_t erase(const Key_s005f_7da0& k);
  insert_return_type DoInsertValue(const Value& value, true_type);
};
}
namespace eastl {
template <typename T1, typename T2>
struct kv_pair {  // hash map value_type
  T1 first;
  T2 second;
};
}
namespace eastl {
template struct pair_s005f_7da0<string16, Key_s005f_7da0>;
}
namespace eastl {
typedef kv_pair<Key_s005f_7da0, Key_s005f_7da0> KeyKeyPair;
}
namespace eastl {
typedef hashtable_s005f_7da0<KeyKeyPair, KeyGroupHash> KeyKeyMap;
}
namespace eastl {
struct KeyRecord {  // 0x1c-byte multimap value
  Key_s005f_7da0 first;
  uint32_t value[4];
};
}
namespace eastl {
typedef hashtable_s005f_7da0<KeyRecord, KeyMixHash> KeyRecordMultiMap;
}
namespace eastl {
template KeyKeyMap::iterator KeyKeyMap::find(const Key_s005f_7da0&);
}
namespace eastl {
template uint32_t KeyKeyMap::erase(const Key_s005f_7da0&);
}
namespace eastl {
template KeyKeyMap::insert_return_type KeyKeyMap::DoInsertValue(const KeyKeyPair&, true_type);
}
namespace eastl {
template pair_s005f_7da0<KeyRecordMultiMap::iterator, KeyRecordMultiMap::iterator> KeyRecordMultiMap::equal_range(const Key_s005f_7da0&);
}
using eastl::string16;
struct KeyRemapHash {
  uint32_t operator()(const Key_s005f_7da0& k) const;
};
typedef eastl::kv_pair<string16, Key_s005f_7da0> NameKeyPair;
typedef eastl::hashtable_s005f_7da0<NameKeyPair, KeyRemapHash> NameKeyMap;
typedef eastl::hashtable_s005f_7da0<eastl::KeyKeyPair, KeyRemapHash> RemapKeyMap;
class cKeyMappingTable {
 public:
  uint32_t mUnknown00;           // +0x00
  NameKeyMap mNameMap;           // +0x04
  uint32_t mUnknown24[9];        // +0x24
  eastl::KeyKeyMap mKeyMap;      // +0x48
  RemapKeyMap mRemapMap;         // +0x68

  bool GetRemappedKey(const Key_s005f_7da0& key, Key_s005f_7da0* pOut);
  bool GetMappedKey(const Key_s005f_7da0& key, Key_s005f_7da0* pOut);
  bool Save();
};
// ---- items of slice s005f7da0 end

// ---- items of slice s0068c330 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int   __cdecl iswctype(unsigned short c, unsigned t);
extern "C" __declspec(dllimport) int   __cdecl isdigit(int c);
extern "C" __declspec(dllimport) int   __cdecl isxdigit(int c);
extern "C" __declspec(dllimport) void* __cdecl memmove(void* dst, const void* src, unsigned n);
extern "C" __declspec(dllimport) void* __cdecl memcpy(void* dst, const void* src, unsigned n);
extern "C" __declspec(dllimport) unsigned long __cdecl strtoul(const char* s, char** e, int base);
typedef unsigned int   uint32;
typedef unsigned char  uint8;
extern "C" __declspec(dllimport) char* __cdecl strchr_s0068_c330(const char* s, int c);
extern "C" __declspec(dllimport) void* __cdecl memchr_s0068_c330(const void* s, int c, unsigned n);
void* EAAllocate(unsigned size, const char* area, int a, int b, const char* file, int line); // 0x00F473A0
void  EAFree(void* p);                                                                        // 0x00F47380
void* GetManager();                                                                           // 0x0067DCD0
void  WStr_Format(void* out, const wchar_t* fmt, ...);                                        // 0x0041E050
void  Str_Format(void* out, const char* fmt, ...);                                            // 0x00472FE0
void  Str_AppendFormat(void* out, const char* fmt, ...);                                      // 0x005F9450
void  StrFormatKey(void* out, const wchar_t* fmt, ...);                                       // 0x004E0850 (cdecl vararg)
struct ResKey {
    uint32 mInstance;   // +0x00
    uint32 mType;       // +0x04
    uint32 mGroup;      // +0x08
};
struct PackStr {
    char* mpBegin;    // +0x00
    char* mpEnd;      // +0x04
    char* mpCapacity; // +0x08
    void* mAllocator; // +0x0c (EASTL allocator; the empty string leaves this null)
    void* mEmptyRef;  // +0x10 (copied by the copy ctor; equals mpBegin for the shared empty string)

    PackStr* InsertCStr(uint32 id, const char* s);                  // 0x0068CD40
    void __declspec(noinline) Insert(char* pos, const char* first, const char* last);  // 0x0068C9E0

    void Swap(PackStr& other);                                     // 0x0068D1C0 (thiscall, ret 4)
    void reserve(unsigned n);                                       // 0x0068D480 (thiscall, ret 4)
};
void SPNameFromKeyW(const ResKey* key, void* out, const wchar_t* name);
void SPNameFromKeyA(const ResKey* key, void* out, const char* name);
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mAllocator;

    void Insert(wchar_t* pos, const wchar_t* first, const wchar_t* last); // 0x005F7DA0
    void resize(unsigned n);                                              // 0x00429520
};
void* FUN_0068C680(const char* s, unsigned n);          // Resource::HashNameN
void  FUN_0068D0B0(void* out, const void* tpl, const char* s); // fixed wstring ctor
struct PackStrOps {                                     // packed string (EASTL string) members
    void Ctor(PackStr* src);                            // 0x0068CF00  copy ctor
    void Assign(const char* first, const char* last);   // 0x0068CF60  assign/append range
    void Erase(unsigned n);                             // 0x0068CBB0  erase tail down to n
};
struct HashMap {
    void  Find(void** itOut, const uint32* key);        // 0x00A3B2C0  (thiscall, ret 8)
    void* Insert(void* itOut, void* pair, int flag);    // 0x0068CFF0

    void* Lookup(const uint32* pKey);                   // stands in for operator[](uint32)
};
// ---- items of slice s0068c330 end

// ---- items of slice s005f6df0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
template <typename Value>
struct hash_node_s005f_6df0 {
  Value mValue;
  hash_node_s005f_6df0* mpNext;
};
}
namespace eastl {
template <typename T, typename Node>
struct hashtable_iterator_s005f_6df0 {
  Node* mpNode;
  Node** mpBucket;
  hashtable_iterator_s005f_6df0() {}
  hashtable_iterator_s005f_6df0(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
  void increment() {
    mpNode = mpNode->mpNext;
    while (mpNode == 0) mpNode = *++mpBucket;
  }
  hashtable_iterator_s005f_6df0& operator++() {
    increment();
    return *this;
  }
};
}
namespace eastl {
class allocator_s005f_6df0 { public:
  void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
  void deallocate(void* p) { operator delete[](p); }
};
}
namespace eastl {
template <typename Value>
class hashtable_s005f_6df0 {
 public:
  typedef hash_node_s005f_6df0<Value> node_type;
  typedef hashtable_iterator_s005f_6df0<Value, node_type> iterator;

  uint32_t mHashCodeBase;          // +0x00
  node_type** mpBucketArray;       // +0x04
  uint32_t mnBucketCount;          // +0x08
  uint32_t mnElementCount;         // +0x0c
  float mRehashPolicy[3];          // +0x10
  allocator_s005f_6df0 mAllocator;            // +0x1c

  static uint32_t hash_of(const Value& v) { return v.first.groupID; }
  node_type** DoAllocateBuckets(uint32_t n) {
    node_type** const pBucketArray = (node_type**)mAllocator.allocate((n + 1) * sizeof(node_type*));
    memset(pBucketArray, 0, n * sizeof(node_type*));
    pBucketArray[n] = reinterpret_cast<node_type*>((uintptr_t)~0);
    return pBucketArray;
  }
  void DoFreeBuckets(node_type** pBucketArray, uint32_t n) {
    if (n > 1) mAllocator.deallocate(pBucketArray);
  }
  void DoFreeNode(node_type* pNode) { mAllocator.deallocate(pNode); }
  void DoRehash(uint32_t nNewBucketCount);
  node_type* DoAllocateNode(const Value& value);
  iterator erase(iterator i);
};
}
namespace eastl {
template <typename Value>
typename hashtable_s005f_6df0<Value>::node_type* hashtable_s005f_6df0<Value>::DoAllocateNode(const Value& value) {
  node_type* const pNode = (node_type*)mAllocator.allocate(sizeof(node_type));
  ::new (&pNode->mValue) Value(value);
  pNode->mpNext = 0;
  return pNode;
}
}
// ---- items of slice s005f6df0 end

// @ 0x005f7be0
namespace eastl {
template <typename Value> void hashtable_s005f_6df0<Value>::DoRehash(uint32_t nNewBucketCount)
{
  node_type** const pBucketArray = DoAllocateBuckets(nNewBucketCount);
  for (uint32_t i = 0; i < mnBucketCount; ++i) {
    node_type* pNode;
    while ((pNode = mpBucketArray[i]) != 0) {
      const uint32_t nNewBucketIndex = hash_of(pNode->mValue) % nNewBucketCount;
      mpBucketArray[i] = pNode->mpNext;
      pNode->mpNext = pBucketArray[nNewBucketIndex];
      pBucketArray[nNewBucketIndex] = pNode;
    }
  }
  DoFreeBuckets(mpBucketArray, mnBucketCount);
  mnBucketCount = nNewBucketCount;
  mpBucketArray = pBucketArray;
}
}  // namespace eastl

// @ 0x005f7da0
namespace eastl {
template <typename T> void basic_string_s005f_7da0<T>::insert(iterator p, const T* pBegin, const T* pEnd)
{
  const ptrdiff_t n = pEnd - pBegin;
  if (n) {
    const bool bCapacityIsSufficient = ((mpCapacity - mpEnd) >= (n + 1));
    const bool bSourceIsFromSelf = ((pEnd >= mpBegin) && (pBegin <= mpEnd));

    if (bCapacityIsSufficient && !bSourceIsFromSelf) {
      const ptrdiff_t nElementsAfter = (mpEnd - p);
      iterator pOldEnd = mpEnd;

      if (nElementsAfter >= n) {
        memmove(mpEnd + 1, mpEnd - n + 1, (size_t)n * sizeof(T));
        mpEnd += n;
        memmove(p + n, p, (size_t)((nElementsAfter - n) + 1) * sizeof(T));
        memcpy(p, pBegin, (size_t)(pEnd - pBegin) * sizeof(T));
      } else {
        const T* const pMid = pBegin + (nElementsAfter + 1);
        memmove(mpEnd + 1, pMid, (size_t)(pEnd - pMid) * sizeof(T));
        mpEnd += n - nElementsAfter;
        memmove(mpEnd, p, (size_t)(pOldEnd - p + 1) * sizeof(T));
        mpEnd += nElementsAfter;
        memcpy(p, pBegin, (size_t)(pMid - pBegin) * sizeof(T));
      }
    } else {
      const size_type nOldSize = (size_type)(mpEnd - mpBegin);
      const size_type nOldCap = (size_type)((mpCapacity - mpBegin) - 1);
      size_type nLength;

      if (bCapacityIsSufficient)
        nLength = nOldSize + (size_type)n + 1;
      else
        nLength = max_alt((size_type)GetNewCapacity(nOldCap), (size_type)(nOldSize + n)) + 1;

      T* pNewBegin = DoAllocate(nLength);
      T* pNewEnd = CharStringUninitializedCopy(mpBegin, p, pNewBegin);
      pNewEnd = CharStringUninitializedCopy(pBegin, pEnd, pNewEnd);
      pNewEnd = CharStringUninitializedCopy(p, mpEnd, pNewEnd);
      *pNewEnd = 0;

      DeallocateSelf();
      mpBegin = pNewBegin;
      mpEnd = pNewEnd;
      mpCapacity = pNewBegin + nLength;
    }
  }
}
}  // namespace eastl

// @ 0x005f7fa0
namespace eastl {
template <typename Value, typename Hash> pair_s005f_7da0<typename hashtable_s005f_7da0<Value, Hash>::iterator, typename hashtable_s005f_7da0<Value, Hash>::iterator> hashtable_s005f_7da0<Value, Hash>::equal_range(const Key_s005f_7da0& k)
{
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type** head = mpBucketArray + n;
  node_type* pNode = DoFindNode(*head, k);
  if (pNode) {
    node_type* p1 = pNode->mpNext;
    for (; p1; p1 = p1->mpNext) {
      if (!(k == p1->mValue.first)) break;
    }
    iterator first(pNode, head);
    iterator last(p1, head);
    if (!p1) last.increment_bucket();
    return pair_s005f_7da0<iterator, iterator>(first, last);
  }
  return pair_s005f_7da0<iterator, iterator>(iterator(mpBucketArray + mnBucketCount), iterator(mpBucketArray + mnBucketCount));
}
}  // namespace eastl

// @ 0x005f8050
namespace eastl {
template <typename Value, typename Hash> typename hashtable_s005f_7da0<Value, Hash>::iterator hashtable_s005f_7da0<Value, Hash>::find(const Key_s005f_7da0& k)
{
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type* const pNode = DoFindNode(mpBucketArray[n], k);
  return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
}
}  // namespace eastl

// @ 0x005f80d0
namespace eastl {
template <typename Value, typename Hash> uint32_t hashtable_s005f_7da0<Value, Hash>::erase(const Key_s005f_7da0& k)
{
  const uint32_t n = mHash(k) % mnBucketCount;
  const uint32_t nElementCountSaved = mnElementCount;
  node_type** pBucketArray = mpBucketArray + n;
  while (*pBucketArray && !(k == (*pBucketArray)->mValue.first)) pBucketArray = &(*pBucketArray)->mpNext;
  while (*pBucketArray && (k == (*pBucketArray)->mValue.first)) {
    node_type* const pNode = *pBucketArray;
    *pBucketArray = pNode->mpNext;
    DoFreeNode(pNode);
    --mnElementCount;
  }
  return nElementCountSaved - mnElementCount;
}
}  // namespace eastl

// @ 0x005f8170
namespace eastl {
template <typename Value, typename Hash> typename hashtable_s005f_7da0<Value, Hash>::insert_return_type hashtable_s005f_7da0<Value, Hash>::DoInsertValue(const Value& value, true_type)
{
  const uint32_t c = mHash(value.first);
  uint32_t n = c % mnBucketCount;
  node_type* const pNode = DoFindNode(mpBucketArray[n], value.first);
  if (pNode == 0) {
    const prime_rehash_policy_s005f_7da0::RehashResult bRehash = mRehashPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
    node_type* const pNodeNew = DoAllocateNode(value);
    if (bRehash.first) {
      n = c % bRehash.second;
      DoRehash(bRehash.second);
    }
    pNodeNew->mpNext = mpBucketArray[n];
    mpBucketArray[n] = pNodeNew;
    ++mnElementCount;
    return insert_return_type(iterator(pNodeNew, mpBucketArray + n), true);
  }
  return insert_return_type(iterator(pNode, mpBucketArray + n), false);
}
}  // namespace eastl

// @ 0x005f8400
namespace eastl {
template <typename T> basic_string_s005f_7da0<T>& basic_string_s005f_7da0<T>::replace(iterator pBegin, iterator pEnd, const T* pBegin2, const T* pEnd2)
{
  const size_type nLength1 = (size_type)(pEnd - pBegin);
  const size_type nLength2 = (size_type)(pEnd2 - pBegin2);

  if (nLength1 >= nLength2) {
    if ((pBegin2 > pEnd) || (pEnd2 <= pBegin))
      memcpy(pBegin, pBegin2, (size_t)(pEnd2 - pBegin2) * sizeof(T));
    else
      memmove(pBegin, pBegin2, (size_t)(pEnd2 - pBegin2) * sizeof(T));
    erase(pBegin + nLength2, pEnd);
  } else {
    if ((pBegin2 > pEnd) || (pEnd2 <= pBegin)) {
      const T* const pMid2 = pBegin2 + nLength1;
      if ((pEnd2 <= pBegin) || (pBegin2 > pEnd))
        memcpy(pBegin, pBegin2, (size_t)(pMid2 - pBegin2) * sizeof(T));
      else
        memmove(pBegin, pBegin2, (size_t)(pMid2 - pBegin2) * sizeof(T));
      insert(pEnd, pMid2, pEnd2);
    } else {
      const size_type nOldSize = (size_type)(mpEnd - mpBegin);
      const size_type nOldCap = (size_type)((mpCapacity - mpBegin) - 1);
      const size_type nNewCapacity = max_alt((size_type)GetNewCapacity(nOldCap), (size_type)(nOldSize + (nLength2 - nLength1))) + 1;

      T* pNewBegin = DoAllocate(nNewCapacity);
      T* pNewEnd = CharStringUninitializedCopy(mpBegin, pBegin, pNewBegin);
      pNewEnd = CharStringUninitializedCopy(pBegin2, pEnd2, pNewEnd);
      pNewEnd = CharStringUninitializedCopy(pEnd, mpEnd, pNewEnd);
      *pNewEnd = 0;

      DeallocateSelf();
      mpBegin = pNewBegin;
      mpEnd = pNewEnd;
      mpCapacity = pNewBegin + nNewCapacity;
    }
  }
  return *this;
}
}  // namespace eastl

// @ 0x005f8a70
bool cKeyMappingTable::GetMappedKey(const Key_s005f_7da0& key, Key_s005f_7da0* pOut)
{
  eastl::KeyKeyMap::iterator it = mKeyMap.find(key);
  if (it != mKeyMap.end()) {
    if (pOut) *pOut = it->second;
    return true;
  }
  return false;
}

// @ 0x0068c700
ResKey* InvalidEditorModelKey(ResKey* key, uint32 v)
{
    uint32 bits = (v << 0x18) ^ key->mGroup;
    bits &= 0x1f000000u;
    *(volatile uint32*)&key->mGroup ^= bits;
    return key;
}

// @ 0x0068c720
wchar_t* FindLastCharW(wchar_t* first, wchar_t* last, const wchar_t* c)
{
    if (last != first) {
        do {
            --last;
            if (*last == *c)
                return last;
        } while (last != first);
    }
    return 0;
}

// @ 0x0068c750
char* FindLastCharA(char* first, char* last, const char* c)
{
    if (last != first) {
        do {
            --last;
            if (*last == *c)
                return last;
        } while (last != first);
    }
    return 0;
}

// @ 0x0068c770
wchar_t* GetExplicitIdStartW(wchar_t* first, wchar_t* last, uint8 flag3, uint8 flag4)
{
    wchar_t* start = first;
    if (flag3 != 0) {
        if (last != first) {
            wchar_t* p = last;
            do {
                --p;
                if (*p == 0x5f) {
                    start = p + 1;
                    break;
                }
            } while (p != first);
        }
    }
    if (((int)((char*)last - (char*)start) & ~1) < 0x10)
        return 0;
    if (*start == 0x30 && (start[1] == 0x78 || start[1] == 0x58)) {
        start += 2;
    } else {
        if (iswctype(*start, 4) == 0)
            return 0;
    }
    {
        wchar_t* p = start;
        int n = 0;
        while (p != last) {
            if (iswctype(*p, 0x80) == 0)
                return 0;
            ++p;
            ++n;
        }
        if (n == 8)
            return start;
        if (n == 0x10 && flag4 != 0)
            return start;
    }
    return 0;
}

// @ 0x0068c820
char* GetExplicitIdStartA(char* first, char* last, uint8 flag3, uint8 flag4)
{
    char* start = first;
    if (flag3 != 0) {
        if (last != first) {
            char* p = last;
            do {
                --p;
                if (*p == 0x5f) {
                    start = p + 1;
                    break;
                }
            } while (p != first);
        }
    }
    if ((int)(last - start) < 8)
        return 0;
    if (*start == 0x30 && (start[1] == 0x78 || start[1] == 0x58)) {
        start += 2;
    } else {
        if (isdigit((unsigned char)*start) == 0)
            return 0;
    }
    {
        char* p = start;
        int n = 0;
        while (p != last) {
            if (isxdigit((unsigned char)*p) == 0)
                return 0;
            ++p;
            ++n;
        }
        if (n == 8)
            return start;
        if (n == 0x10 && flag4 != 0)
            return start;
    }
    return 0;
}

// @ 0x0068c9e0
void PackStr::Insert(char* pos, const char* first, const char* last)
{
    // eastl::string::insert(pos, first, last), inlined body (SSO or heap buffer).
    const unsigned n = (unsigned)(last - first);
    if (n == 0)
        return;
    const unsigned size = (unsigned)(mpEnd - mpBegin);
    const unsigned cap = (unsigned)(mpCapacity - mpBegin);
    const bool roomInBuffer = (n + 1) <= (cap - size);
    const bool overlap = !(last <= mpBegin || pos > mpEnd);
    if (roomInBuffer && !overlap) {
        const unsigned tail = (unsigned)(mpEnd - pos);
        if (n <= tail) {
            memmove(mpEnd + 1, mpEnd - n + 1, n);
            mpEnd += n;
            memmove(pos + n, pos, (tail - n) + 1);
        } else {
            const char* front = first + (tail + 1);
            memmove(mpEnd + 1, front, (unsigned)(last - front));
            mpEnd += n - tail;
            memmove(mpEnd, pos, (tail + 1));
            mpEnd += tail;
        }
        return;
    }
    unsigned newCap;
    if (roomInBuffer) {
        newCap = size + n + (1 - 0);
    } else {
        const unsigned need = size + n;
        const unsigned grow = (size > 8) ? size * 2 : 8;
        newCap = (need > grow ? need : grow) + 1;
    }
    char* dst = (char*)EAAllocate(newCap, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\"
                                          "SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\"
                                          "EASTL/allocator.h",
                                  0, 0, 0, 0xd1);
    const char* oldBegin = mpBegin;
    const unsigned head = (unsigned)(pos - oldBegin);
    memmove(dst, oldBegin, head);
    char* mid = dst + head;
    memmove(mid, first, n);
    memmove(mid + n, pos, size - head);
    mid[size - head + n] = 0;
    const char* newEnd = mid + (size - head) + n;
    if ((unsigned)(mpCapacity - oldBegin) > 1 && oldBegin != 0)
        EAFree((void*)oldBegin);
    mpBegin = dst;
    mpEnd = (char*)newEnd;
    mpCapacity = dst + newCap;
}

// @ 0x0068cd40
PackStr* PackStr::InsertCStr(uint32 id, const char* s)
{
    const char* e = s;
    while (*e++)
        ;
    Insert(mpBegin + id, s, e - 1);
    return this;
}

// @ 0x0068d0d0
void SPNameFromKeyW(const ResKey* key, void* out, const wchar_t* name)
{
    WStr_Format(out, L"0x%08x", key->mGroup);
    if (name != 0) {
        const wchar_t* pref = (const wchar_t*)0x013fe614;
        const wchar_t* e = pref;
        do {
            ++e;
        } while (*e);
        ((WStr*)out)->Insert(*(wchar_t**)out, pref, e);
        const wchar_t* n = name;
        const wchar_t* ne = n;
        while (*ne)
            ++ne;
        ((WStr*)out)->Insert(*(wchar_t**)out, n, ne);
    }
    void* mgr = GetManager();
    uint32 res = ((uint32(__thiscall*)(void*, uint32))(*(void***)mgr)[0x8c / 4])(mgr, key->mType);
    if (res != 0)
        StrFormatKey(out, L"!0x%08x.%ls", key->mInstance, res);
    else
        StrFormatKey(out, L"!0x%08x.0x%08x", key->mInstance, key->mType);
}

// @ 0x0068d1a0
void SPNameFromKeyThunk(const ResKey* key, void* out, int a3, int a4, const char* name)
{
    SPNameFromKeyA(key, out, name);
}

// @ 0x0068d1c0
void PackStr::Swap(PackStr& other)
{
    // Both sides are SSO (their inline buffers live at +0x0c): just swap the three pointers.
    if ((char*)this + 0xc == (char*)&other + 0xc) {
        char* a = (char*)this;
        char* b = (char*)&other;
        for (int i = 0; i < 3; ++i) {
            void* t = *(void**)(a + i * 4);
            *(void**)(a + i * 4) = *(void**)(b + i * 4);
            *(void**)(b + i * 4) = t;
        }
        return;
    }
    PackStr tmp;
    tmp.mpBegin = 0;
    tmp.mpEnd = 0;
    tmp.mpCapacity = 0;
    ((PackStrOps*)&tmp)->Ctor(this);
    if (&other != this)
        ((PackStrOps*)this)->Assign(other.mpBegin, other.mpEnd);
    if (&other != &tmp)
        ((PackStrOps*)&other)->Assign(tmp.mpBegin, tmp.mpEnd);
    if ((unsigned)(tmp.mpCapacity - tmp.mpBegin) > 2 && tmp.mpBegin != 0)
        EAFree(tmp.mpBegin);
}

// @ 0x0068d290
void SPNameFromKeyA(const ResKey* key, void* out, const char* name)
{
    Str_Format(out, "0x%08x", key->mGroup);
    if (name != 0) {
        ((PackStr*)out)->Insert(*(char**)out, (const char*)0x1403550, (const char*)0x1403551);
        const char* n = name;
        const char* ne = n;
        while (*ne)
            ++ne;
        ((PackStr*)out)->Insert(*(char**)out, n, ne);
    }
    void* mgr = GetManager();
    uint32 res = ((uint32(__thiscall*)(void*, uint32))(*(void***)mgr)[0x8c / 4])(mgr, key->mType);
    if (res != 0)
        Str_AppendFormat(out, "!0x%08x.%ls", key->mInstance, res);
    else
        Str_AppendFormat(out, "!0x%08x.0x%08x", key->mInstance, key->mType);
    if (name != 0)
        Str_Format(out, "%hs_%hs", name, *(char**)out);
}

// @ 0x0068d480
void PackStr::reserve(unsigned n)
{
    // eastl::string::reserve(n).
    PackStr* self = this;
    if (n != 0xffffffffu && (unsigned)((self->mpEnd - self->mpBegin) >> 1) < n) {
        const unsigned newBytes = n * 2;
        char* dst = (char*)EAAllocate(newBytes, "App", 0, 0,
                                      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\"
                                      "SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\"
                                      "EASTL/allocator.h",
                                      0xd1);
        const unsigned oldBytes = (unsigned)((self->mpEnd - self->mpBegin) >> 1) * 2;
        memcpy(dst, self->mpBegin, oldBytes);
        char* newEnd = dst + oldBytes;
        *(unsigned short*)newEnd = 0;
        char* old = self->mpBegin;
        if ((unsigned)(self->mpCapacity - old) > 2 && old != 0 && old != (char*)self->mEmptyRef)
            EAFree(old);
        self->mpBegin = dst;
        self->mpCapacity = dst + newBytes;
        self->mpEnd = newEnd;
        return;
    }
    PackStr tmp;
    if (n < (unsigned)((self->mpEnd - self->mpBegin) >> 1))
        ((PackStrOps*)self)->Erase(n);
    ((PackStrOps*)&tmp)->Ctor(self);
    self->Swap(tmp);
    char* b = tmp.mpBegin;
    if ((unsigned)((char*)tmp.mpCapacity - b) > 2 && b != 0 && b != (char*)tmp.mEmptyRef)
        EAFree(b);
}

// @ 0x0068d5a0
bool SPKeyFromName(ResKey* key, const char* name, uint32 type, uint32 defGroup)
{
    if (name == 0 || *name == 0)
        return false;
    key->mType = type;
    const char* dot = strchr_s0068_c330(name, '.');
    const char* ext = 0;
    const char* end;
    if (dot != 0) {
        ext = dot + 1;
        end = dot;
    } else {
        end = name;
        while (*end)
            ++end;
        dot = end;
    }
    const char* bang = (const char*)memchr_s0068_c330(name, '!', (unsigned)(dot - name));
    key->mGroup = (bang != 0) ? 0xffffffff : defGroup;
    const char* start = (bang != 0) ? bang + 1 : name;
    // memchr miss: the original folds the delimiter onto `name`, which skips the group block.
    const char* bangEnd = (bang != 0) ? bang : name;
    if (start == dot) {
        key->mInstance = 0xffffffff;
    } else {
        const char* hexs = GetExplicitIdStartA((char*)start, (char*)dot, 1, 1);
        if (hexs == 0)
            key->mInstance = (uint32)FUN_0068C680(start, (unsigned)(dot - start));
        else
            key->mInstance = (uint32)strtoul(hexs, 0, 16);
    }
    if (name != bangEnd) {
        const char* p = bangEnd;
        const char* at = 0;
        do {
            --p;
            if (*p == '@') {
                at = p;
                break;
            }
        } while (p != name);
        if (at != 0) {
            key->mGroup = 0;
        } else {
            char underscore = '_';
            const char* us = FindLastCharA((char*)name, (char*)bangEnd, &underscore);
            const char* s2 = name;
            if (us != 0)
                s2 = us + 1;
            const char* hexs = GetExplicitIdStartA((char*)s2, (char*)bangEnd, 0, 0);
            if (hexs == 0) {
                key->mGroup = (uint32)FUN_0068C680(name, (unsigned)(bangEnd - name));
                // cache the group name string (wide) in the global group->name map
                HashMap* groupNames = (HashMap*)0x0152C864;
                WStr* cached = (WStr*)groupNames->Lookup(&key->mGroup);
                cached->resize((unsigned)(bangEnd - name));
                wchar_t* dst = cached->mpBegin;
                for (const char* q = name; q != bangEnd; ++q)
                    *dst++ = (wchar_t)(signed char)*q;
            } else {
                key->mGroup = (uint32)strtoul(hexs, 0, 16);
            }
        }
    }
    if (ext != 0) {
        key->mType = 0xffffffff;
        if (*ext == 0)
            return true;
        const char* e = ext;
        while (*e)
            ++e;
        const char* hexs = GetExplicitIdStartA((char*)ext, (char*)e, 0, 0);
        if (hexs != 0) {
            key->mType = (uint32)strtoul(hexs, 0, 16);
            return true;
        }
        unsigned short tmp[16];
        tmp[0] = 0;
        FUN_0068D0B0(tmp, (const void*)0x013F3DA0, ext);
        void* mgr = GetManager();
        int id = ((int(__thiscall*)(void*, void*))(*(void***)mgr)[0x88 / 4])(mgr, tmp);
        if (id == -1)
            id = (int)FUN_0068C680(ext, (unsigned)(e - ext));
        key->mType = (uint32)id;
    }
    (void)end;
    return true;
}
