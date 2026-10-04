// slice s005f7da0 - EASTL string16 insert/replace, pair<string16,Key> helpers, Key->Key hash maps
// and the editor key-mapping table that saves them.
// Flags: /O2 /MD /Gy /TP
#include "types.h"
#include <string.h>

#define PV(n) virtual void _pv##n();

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);
inline void* operator new(size_t, void* p) throw() { return p; }

#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

namespace EA {
namespace ResourceMan {
struct Key {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
  bool operator==(const Key& b) const { return instanceID == b.instanceID && typeID == b.typeID && groupID == b.groupID; }
};
}  // namespace ResourceMan
namespace IO {
namespace File {
bool Exists(const wchar_t* path);  // 0x00931fa0
}
}  // namespace IO
}  // namespace EA
using EA::ResourceMan::Key;

namespace eastl {
struct allocator {
  void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
  void deallocate(void* p) { operator delete[](p); }
};

struct sp_vector_allocator {
  const char* mpName;
  uint32_t mFlags;
  void deallocate(void* p) {
    if (((int*)p)[-1]) operator delete[](p);
  }
};

template <typename T>
class pod_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator mAllocator;
  pod_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~pod_vector() {
    if (mpBegin) mAllocator.deallocate(mpBegin);
  }
};

template <typename T>
inline const T& min_alt(const T& a, const T& b) {
  return b < a ? b : a;
}
template <typename T>
inline const T& max_alt(const T& a, const T& b) {
  return a < b ? b : a;
}

extern char gEmptyString8[2];
extern wchar_t gEmptyString16[2];
inline const char* GetEmptyString(char) { return gEmptyString8; }
inline const wchar_t* GetEmptyString(wchar_t) { return gEmptyString16; }

template <typename T>
inline size_t CharStrlen(const T* p) {
  const T* pCurrent = p;
  while (*pCurrent) ++pCurrent;
  return (size_t)(pCurrent - p);
}

template <typename T>
class basic_string {
 public:
  typedef T* iterator;
  typedef size_t size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  allocator mAllocator;

  basic_string() { AllocateSelf(); }
  basic_string(const basic_string& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
  basic_string(size_type n, T c, const allocator& a);
  ~basic_string() { DeallocateSelf(); }

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
  basic_string& replace(iterator pBegin, iterator pEnd, const T* pBegin2, const T* pEnd2);
  basic_string& replace(size_type position, size_type n, const T* p);
  static int compare(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2);  // 0x00576970
  int compare(const T* p) const { return compare(mpBegin, mpEnd, p, p + CharStrlen(p)); }
};

typedef basic_string<char> string;
typedef basic_string<wchar_t> string16;

// @ 0x005f7da0
template <typename T>
void basic_string<T>::insert(iterator p, const T* pBegin, const T* pEnd) {
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

// @ 0x005f8400
template <typename T>
basic_string<T>& basic_string<T>::replace(iterator pBegin, iterator pEnd, const T* pBegin2, const T* pEnd2) {
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

// @ 0x005f8f80
template <typename T>
basic_string<T>& basic_string<T>::replace(size_type position, size_type n, const T* p) {
  const size_type nLength = min_alt(n, (size_type)(mpEnd - mpBegin) - position);
  return replace(mpBegin + position, mpBegin + position + nLength, p, p + CharStrlen(p));
}

// @ 0x005f8f30
template <typename T>
basic_string<T>::basic_string(size_type n, T c, const allocator&) : mpBegin(0), mpEnd(0), mpCapacity(0) {
  RangeInitialize(n, c);
}

template class basic_string<wchar_t>;
template basic_string<char>::basic_string(size_type, char, const allocator&);

template <typename T1, typename T2>
struct pair {
  T1 first;
  T2 second;
  pair(const T1& x, const T2& y) : first(x), second(y) {}
  pair(const pair& p) : first(p.first), second(p.second) {}
  ~pair() {}
};

// @ 0x005f8690 pair<string16,Key>::pair(const string16&, const Key&)
// @ 0x005f8700 pair<Key,string16>::pair(const Key&, const string16&)
// @ 0x005f8320 pair<string16,Key>::pair(const pair&)
// @ 0x005f8390 pair<Key,string16>::pair(const pair&)
// @ 0x005f8d80 pair<Key,string16>::~pair()
template struct pair<string16, Key>;
template struct pair<Key, string16>;

template <typename Value>
struct hash_node {
  Value mValue;
  hash_node* mpNext;
};

template <typename Node>
struct hashtable_iterator_base {
  Node* mpNode;
  Node** mpBucket;
  hashtable_iterator_base(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
};

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

struct true_type {};

struct prime_rehash_policy {
  float mfMaxLoadFactor;
  float mfGrowthFactor;
  uint32_t mnNextResize;
  struct RehashResult {
    bool first;
    uint32_t second;
  };
  RehashResult GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd);  // 0x00921440
};

struct KeyGroupHash {
  uint32_t operator()(const Key& k) const { return k.groupID; }
};
struct KeyMixHash {
  uint32_t operator()(const Key& k) const { return k.instanceID ^ k.groupID; }
};

template <typename Value, typename Hash>
class hashtable {
 public:
  typedef hash_node<Value> node_type;
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
  prime_rehash_policy mRehashPolicy;  // +0x10
  allocator mAllocator;              // +0x1c

  iterator begin();  // out of line
  iterator begin_inline() {
    iterator i(mpBucketArray);
    if (!i.mpNode) i.increment_bucket();
    return i;
  }
  iterator end() { return iterator(mpBucketArray + mnBucketCount); }

  __forceinline node_type* DoFindNode(node_type* pNode, const Key& k) {
    for (; pNode; pNode = pNode->mpNext) {
      if (k == pNode->mValue.first) return pNode;
    }
    return 0;
  }
  void DoFreeNode(node_type* pNode) { mAllocator.deallocate(pNode); }
  void DoRehash(uint32_t nNewBucketCount);
  node_type* DoAllocateNode(const Value& value);

  iterator find(const Key& k);
  pair<iterator, iterator> equal_range(const Key& k);
  uint32_t erase(const Key& k);
  insert_return_type DoInsertValue(const Value& value, true_type);
};

template <typename T1, typename T2>
struct kv_pair {  // hash map value_type
  T1 first;
  T2 second;
};

// @ 0x005f8050
template <typename Value, typename Hash>
typename hashtable<Value, Hash>::iterator hashtable<Value, Hash>::find(const Key& k) {
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type* const pNode = DoFindNode(mpBucketArray[n], k);
  return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
}

// @ 0x005f7fa0
template <typename Value, typename Hash>
pair<typename hashtable<Value, Hash>::iterator, typename hashtable<Value, Hash>::iterator> hashtable<Value, Hash>::equal_range(const Key& k) {
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
    return pair<iterator, iterator>(first, last);
  }
  return pair<iterator, iterator>(iterator(mpBucketArray + mnBucketCount), iterator(mpBucketArray + mnBucketCount));
}

// @ 0x005f80d0
template <typename Value, typename Hash>
uint32_t hashtable<Value, Hash>::erase(const Key& k) {
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

// @ 0x005f8170
template <typename Value, typename Hash>
typename hashtable<Value, Hash>::insert_return_type hashtable<Value, Hash>::DoInsertValue(const Value& value, true_type) {
  const uint32_t c = mHash(value.first);
  uint32_t n = c % mnBucketCount;
  node_type* const pNode = DoFindNode(mpBucketArray[n], value.first);
  if (pNode == 0) {
    const prime_rehash_policy::RehashResult bRehash = mRehashPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
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

typedef kv_pair<Key, Key> KeyKeyPair;
typedef hashtable<KeyKeyPair, KeyGroupHash> KeyKeyMap;

struct KeyRecord {  // 0x1c-byte multimap value
  Key first;
  uint32_t value[4];
};
typedef hashtable<KeyRecord, KeyMixHash> KeyRecordMultiMap;

template KeyKeyMap::iterator KeyKeyMap::find(const Key&);
template uint32_t KeyKeyMap::erase(const Key&);
template KeyKeyMap::insert_return_type KeyKeyMap::DoInsertValue(const KeyKeyPair&, true_type);
template pair<KeyRecordMultiMap::iterator, KeyRecordMultiMap::iterator> KeyRecordMultiMap::equal_range(const Key&);
}  // namespace eastl

using eastl::string;
using eastl::string16;

// key-mapped key map with a separately compiled find (0x00b74860)
struct KeyRemapHash {
  uint32_t operator()(const Key& k) const;
};

// eight-bit string block, destroyed member by member
struct cStringBlock9 {
  string mStrings0;
  string mStrings1;
  string mStrings2;
  string mStrings3;
  string mStrings4;
  string mStrings5;
  string mStrings6;
  string mStrings7;
  string mStrings8;
  ~cStringBlock9();
};

// @ 0x005f8910
cStringBlock9::~cStringBlock9() {}

// wide-string record with a sp-vector payload (ctor 0x005f8e00, dtor 0x005f8e40)
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

// @ 0x005f8e00
cKeyNameRecord::cKeyNameRecord() {}

// @ 0x005f8e40
cKeyNameRecord::~cKeyNameRecord() {}

// @ 0x005f8da0
bool IsPathMissingOrEqual(const string16& path, const wchar_t* other) {
  if (other && path.compare(other) == 0) return true;
  return !EA::IO::File::Exists(path.c_str());
}

namespace EA {
namespace IO {
class IStream {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual bool Write(const void* pData, uint32_t nSize);  // +0x38
};
}  // namespace IO
}  // namespace EA

namespace SP {
class IResourceRecord {
 public:
  PV(0) PV(1)
  virtual int Release();                   // +0x08
  PV(3) PV(4) PV(5)
  virtual EA::IO::IStream* GetStream();    // +0x18
  PV(7) PV(8)
  virtual void RecordClose();              // +0x24
};

class ISaveArea {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual bool OpenRecord(const Key& key, IResourceRecord** ppRecord, int access, int mode, int create, int flags);  // +0x34
};
ISaveArea* GetSaveArea(uint32_t id);  // 0x006b1f90
}  // namespace SP

extern const Key kKeyMappingRecordKey;   // 0x0151c9e0
extern const uint32_t kKeyMappingVersion;  // 0x013fa028

class AutoRecord {
 public:
  SP::IResourceRecord* mpObject;
  AutoRecord() : mpObject(0) {}
  ~AutoRecord() {
    if (mpObject) mpObject->Release();
  }
};

typedef eastl::kv_pair<string16, Key> NameKeyPair;
typedef eastl::hashtable<NameKeyPair, KeyRemapHash> NameKeyMap;
typedef eastl::hashtable<eastl::KeyKeyPair, KeyRemapHash> RemapKeyMap;

inline bool WriteUInt32(EA::IO::IStream* s, uint32_t value) { return s->Write(&value, 4); }

__forceinline bool WriteKey(EA::IO::IStream* s, const Key& key) {
  return s->Write(&key.typeID, 4) && s->Write(&key.groupID, 4) && s->Write(&key.instanceID, 4);
}

class cKeyMappingTable {
 public:
  uint32_t mUnknown00;           // +0x00
  NameKeyMap mNameMap;           // +0x04
  uint32_t mUnknown24[9];        // +0x24
  eastl::KeyKeyMap mKeyMap;      // +0x48
  RemapKeyMap mRemapMap;         // +0x68

  bool GetRemappedKey(const Key& key, Key* pOut);
  bool GetMappedKey(const Key& key, Key* pOut);
  bool Save();
};

// @ 0x005f8a10
bool cKeyMappingTable::GetRemappedKey(const Key& key, Key* pOut) {
  RemapKeyMap::iterator it = mRemapMap.find(key);
  if (it != mRemapMap.end()) {
    if (pOut) *pOut = it->second;
    return true;
  }
  return false;
}

// @ 0x005f8a70
bool cKeyMappingTable::GetMappedKey(const Key& key, Key* pOut) {
  eastl::KeyKeyMap::iterator it = mKeyMap.find(key);
  if (it != mKeyMap.end()) {
    if (pOut) *pOut = it->second;
    return true;
  }
  return false;
}

// @ 0x005f8ad0
bool cKeyMappingTable::Save() {
  SP::ISaveArea* area = SP::GetSaveArea(0x11ac19d);
  if (!area) return false;
  AutoRecord record;
  if (!area->OpenRecord(kKeyMappingRecordKey, &record.mpObject, 2, 2, 1, 0)) return false;
  EA::IO::IStream* s = record.mpObject->GetStream();

  bool ok = s->Write(&kKeyMappingVersion, 4);
  uint32_t n = mNameMap.mnElementCount;
  ok = ok && s->Write(&n, 4);
  for (NameKeyMap::const_iterator it = mNameMap.begin(), itEnd = mNameMap.end(); ok && it != itEnd; ++it) {
    n = it->first.length();
    ok = ok && s->Write(&n, 4) && s->Write(it->first.c_str(), n * 2);
    ok = ok && WriteKey(s, it->second);
  }

  n = mRemapMap.mnElementCount;
  ok = ok && s->Write(&n, 4);
  for (RemapKeyMap::const_iterator it = mRemapMap.begin_inline(), itEnd = mRemapMap.end(); ok && it != itEnd; ++it) {
    ok = ok && WriteKey(s, it->first);
    ok = ok && s->Write(&it->second.instanceID, 4) && s->Write(&it->second.typeID, 4) && s->Write(&it->second.groupID, 4);
  }
  record.mpObject->RecordClose();
  return ok;
}

namespace EA {
namespace Allocator {
class ICoreAllocator {
 public:
  virtual ~ICoreAllocator() {}
  virtual void* Alloc(size_t size, const char* name, unsigned int flags);
  virtual void* AllocFlags(size_t size, const char* name, unsigned int flags);  // +0x08
};
}  // namespace Allocator
}  // namespace EA

namespace eastl {
struct core_allocator_adapter {
  EA::Allocator::ICoreAllocator* mpCoreAllocator;
  unsigned int mnFlags;
  void* allocate(size_t n) { return mpCoreAllocator->AllocFlags(n, 0, mnFlags); }
};

template <typename T, typename Allocator, unsigned kDequeSubarraySize>
struct DequeIterator {
  T* mpCurrent;
  T* mpBegin;
  T* mpEnd;
  T** mpCurrentArrayPtr;
  void SetSubarray(T** pCurrentArrayPtr) {
    mpCurrentArrayPtr = pCurrentArrayPtr;
    mpBegin = *pCurrentArrayPtr;
    mpEnd = mpBegin + kDequeSubarraySize;
  }
};

template <typename T, typename Allocator, unsigned kDequeSubarraySize>
class DequeBase {
 public:
  typedef DequeIterator<T, Allocator, kDequeSubarraySize> iterator;
  T** mpPtrArray;          // +0x00
  size_t mnPtrArraySize;   // +0x04
  iterator mItBegin;       // +0x08
  iterator mItEnd;         // +0x18
  Allocator mAllocator;    // +0x28

  T** DoAllocatePtrArray(size_t n) { return (T**)mAllocator.allocate(n * sizeof(T*)); }
  T* DoAllocateSubarray() { return (T*)mAllocator.allocate(kDequeSubarraySize * sizeof(T)); }
  void DoInit(size_t n);
};

// @ 0x005f8840
template <typename T, typename Allocator, unsigned kDequeSubarraySize>
void DequeBase<T, Allocator, kDequeSubarraySize>::DoInit(size_t n) {
  const size_t nNewPtrArraySize = (size_t)((n / kDequeSubarraySize) + 1);
  const size_t kMinPtrArraySize_ = 8;

  mnPtrArraySize = max_alt(kMinPtrArraySize_, (nNewPtrArraySize + 2));
  mpPtrArray = DoAllocatePtrArray(mnPtrArraySize);

  T** const pPtrArrayBegin = (mpPtrArray + ((mnPtrArraySize - nNewPtrArraySize) / 2));
  T** const pPtrArrayEnd = pPtrArrayBegin + nNewPtrArraySize;
  T** pPtrArrayCurrent = pPtrArrayBegin;

  while (pPtrArrayCurrent < pPtrArrayEnd) *pPtrArrayCurrent++ = DoAllocateSubarray();

  mItBegin.SetSubarray(pPtrArrayBegin);
  mItBegin.mpCurrent = mItBegin.mpBegin;

  mItEnd.SetSubarray(pPtrArrayEnd - 1);
  mItEnd.mpCurrent = mItEnd.mpBegin + (ptrdiff_t)(n % kDequeSubarraySize);
}

struct DequeEntry48 {
  uint32_t mData[12];
};
template class DequeBase<DequeEntry48, core_allocator_adapter, 4>;
}  // namespace eastl
