// src/game/SPEngine/SPIDGenerator.cpp -- migrated from slice(s) s005f7da0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPIDGenerator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>

// ---- items of slice s005f7da0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);
inline void* operator new(size_t, void* p) throw() { return p; }
#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
namespace EA {
namespace ResourceMan {
struct Key_s005f_7da0 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
  bool operator==(const Key_s005f_7da0& b) const { return instanceID == b.instanceID && typeID == b.typeID && groupID == b.groupID; }
};  // namespace ResourceMan
}
}
using EA::ResourceMan::Key_s005f_7da0;
namespace eastl {
struct allocator_s005f_7da0 {
  void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
  void deallocate(void* p) { operator delete[](p); }
};
}
namespace eastl {
struct sp_vector_allocator_s005f_7da0 {
  const char* mpName;
  uint32_t mFlags;
  void deallocate(void* p) {
    if (((int*)p)[-1]) operator delete[](p);
  }
};
}
namespace eastl {
template <typename T>
class pod_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator_s005f_7da0 mAllocator;
  pod_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~pod_vector() {
    if (mpBegin) mAllocator.deallocate(mpBegin);
  }
};
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
struct cKeyNameRecord {
  uint32_t mData[10];       // +0x00
  string16 mName;           // +0x28
  uint32_t mValue38;        // +0x38
  uint32_t mValue3C;        // +0x3c
  string16 mDisplayName;    // +0x40
  string16 mDescription;    // +0x50
  string16 mPath;           // +0x60
  eastl::pod_vector<uint32_t> mIDs;  // +0x70
  cKeyNameRecord();
  ~cKeyNameRecord();
};
// ---- items of slice s005f7da0 end

// @ 0x005f8e40
cKeyNameRecord::~cKeyNameRecord()
{}
