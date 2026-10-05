// Slice s005fa8d0 - SP::Thumbnail::cImportExport (retail layout) + the EASTL hash map
// internals it uses. /O2 /MD /Gy /TP.
#pragma once
#include "types.h"
#include <string.h>

#define PV(n) virtual void _pv##n();

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
void  operator delete(void* p);
inline void* operator new(size_t, void* p) throw() { return p; }

namespace EA {
namespace ResourceMan {
struct Key {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
bool operator==(const Key& a, const Key& b);
struct KeyHash {
  uint32_t operator()(const Key& k) const;
};
struct KeyEqual {
  bool operator()(const Key& a, const Key& b) const;
};
}  // namespace ResourceMan
}  // namespace EA
using EA::ResourceMan::Key;

namespace eastl {
struct allocator {
  void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, "allocator.h", 0xd1); }
  void deallocate(void* p) { operator delete(p); }
};

extern wchar_t gEmptyString16[2];
inline wchar_t* GetEmptyStringW() { return gEmptyString16; }

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
  ~basic_string() { DeallocateSelf(); }

  size_type length() const { return (size_type)(mpEnd - mpBegin); }
  const T* c_str() const { return mpBegin; }

  void AllocateSelf() {
    wchar_t* e = GetEmptyStringW();
    mpBegin = (T*)e;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  void AllocateSelf(size_type n);
  T* DoAllocate(size_type n) { return (T*)mAllocator.allocate(n * sizeof(T)); }
  void DoFree(T* p, size_type) { if (p) mAllocator.deallocate(p); }
  void DeallocateSelf() { if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, (size_type)(mpCapacity - mpBegin)); }
  size_type GetNewCapacity(size_type currentCapacity) { return (currentCapacity > 8) ? (2 * currentCapacity) : 8; }
  void RangeInitialize(const T* pBegin, const T* pEnd) {
    const size_type n = (size_type)(pEnd - pBegin);
    AllocateSelf(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
  static T* CharStringUninitializedCopy(const T* pSource, const T* pSourceEnd, T* pDestination) {
    memcpy(pDestination, pSource, (size_t)(pSourceEnd - pSource) * sizeof(T));
    return pDestination + (pSourceEnd - pSource);
  }
  iterator erase(iterator pFirst, iterator pLast) {
    if (pFirst != pLast) {
      memmove(pFirst, pLast, (size_t)((mpEnd - pLast) + 1) * sizeof(T));
      mpEnd = mpEnd - (pLast - pFirst);
    }
    return pFirst;
  }
  basic_string& assign(const T* pBegin, const T* pEnd);
  basic_string& operator=(const basic_string& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
};

typedef basic_string<wchar_t> string16;

bool operator==(const basic_string<wchar_t>& a, const basic_string<wchar_t>& b);

// FNV-1 hash over a wide string (inlined into hashtable::erase)
struct hash {
  uint32_t operator()(const string16& s) const {
    const wchar_t* p = s.mpBegin;
    uint32_t h = 0x811c9dc5;
    uint32_t c = (uint32_t)*p;
    while (c) { h = h * 0x1000193 ^ c; ++p; c = (uint32_t)*p; }
    return h;
  }
};
struct equal_to {
  bool operator()(const string16& a, const string16& b) const { return a == b; }
};

template <typename T1, typename T2>
struct pair {
  T1 first;
  T2 second;
  pair(const T1& x, const T2& y) : first(x), second(y) {}
  pair(const pair& p) : first(p.first), second(p.second) {}
  ~pair() {}
};

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
  hashtable_iterator(Node* pNode = 0, Node** pBucket = 0) : base_type(pNode, pBucket) {}
  explicit hashtable_iterator(Node** pBucket) : base_type(*pBucket, pBucket) {}
  hashtable_iterator(const hashtable_iterator& x) : base_type(x.mpNode, x.mpBucket) {}
  template <typename U>
  hashtable_iterator(const hashtable_iterator<U, Node>& x) : base_type(x.mpNode, x.mpBucket) {}
  void increment() {
    this->mpNode = this->mpNode->mpNext;
    while (this->mpNode == 0) this->mpNode = *++this->mpBucket;
  }
  void increment_bucket() {
    ++this->mpBucket;
    while (*this->mpBucket == 0) ++this->mpBucket;
    this->mpNode = *this->mpBucket;
  }
  bool operator!=(const hashtable_iterator& x) const { return this->mpNode != x.mpNode; }
  bool operator==(const hashtable_iterator& x) const { return this->mpNode == x.mpNode; }
  hashtable_iterator& operator++() { increment(); return *this; }
};

struct true_type {};

struct RehashResult { bool first; uint32_t second; };
struct prime_rehash_policy {
  float mfMaxLoadFactor;
  float mfGrowthFactor;
  uint32_t mnNextResize;
  RehashResult GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd);
};
extern void* gEmptyBucketArray;   // 0x0154df28

template <typename Value, typename KeyT, typename Hash, typename Equal = equal_to>
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

  Hash mHash;
  node_type** mpBucketArray;
  uint32_t mnBucketCount;
  uint32_t mnElementCount;
  prime_rehash_policy mRehashPolicy;
  allocator mAllocator;

  hashtable() : mpBucketArray((node_type**)&gEmptyBucketArray), mnBucketCount(1), mnElementCount(0) {
    mRehashPolicy.mfMaxLoadFactor = 1.0f;
    mRehashPolicy.mfGrowthFactor = 2.0f;
    mRehashPolicy.mnNextResize = 0;
  }

  iterator end() { return iterator(mpBucketArray + mnBucketCount); }
  __forceinline node_type* DoFindNode(node_type* pNode, const KeyT& k) {
    for (; pNode; pNode = pNode->mpNext)
      if (k == pNode->mValue.first) return pNode;
    return 0;
  }
  void DoFreeNode(node_type* pNode) { pNode->~node_type(); mAllocator.deallocate(pNode); }

  iterator find(const KeyT& k);
  pair<iterator, iterator> equal_range(const KeyT& k);
  uint32_t erase(const KeyT& k);
  iterator erase(const_iterator i);
  void DoFreeNodes(node_type** pBucketArray, uint32_t n);
  void clear() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
  }
  ~hashtable() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1) mAllocator.deallocate(mpBucketArray);
  }
};

template <typename V, typename K, typename H, typename E>
typename hashtable<V, K, H, E>::iterator hashtable<V, K, H, E>::find(const K& k) {
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type* const pNode = DoFindNode(mpBucketArray[n], k);
  return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
}

template <typename V, typename K, typename H, typename E>
pair<typename hashtable<V, K, H, E>::iterator, typename hashtable<V, K, H, E>::iterator>
hashtable<V, K, H, E>::equal_range(const K& k) {
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type** head = mpBucketArray + n;
  node_type* pNode = DoFindNode(*head, k);
  if (pNode) {
    node_type* p1 = pNode->mpNext;
    for (; p1; p1 = p1->mpNext)
      if (!(k == p1->mValue.first)) break;
    iterator first(pNode, head);
    iterator last(p1, head);
    if (!p1) last.increment_bucket();
    return pair<iterator, iterator>(first, last);
  }
  return pair<iterator, iterator>(iterator(mpBucketArray + mnBucketCount), iterator(mpBucketArray + mnBucketCount));
}

// @ 0x005face0
template <typename V, typename K, typename H, typename E>
uint32_t hashtable<V, K, H, E>::erase(const K& k) {
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

// @ 0x005fadb0
template <typename V, typename K, typename H, typename E>
typename hashtable<V, K, H, E>::iterator hashtable<V, K, H, E>::erase(const_iterator i) {
  iterator iNext(i.mpNode, i.mpBucket);
  ++iNext;
  node_type* pNode = i.mpNode;
  node_type* pNodeCurrent = *i.mpBucket;
  if (pNodeCurrent == pNode)
    *i.mpBucket = pNodeCurrent->mpNext;
  else {
    node_type* pNodeNext = pNodeCurrent->mpNext;
    while (pNodeNext != pNode) {
      pNodeCurrent = pNodeNext;
      pNodeNext = pNodeCurrent->mpNext;
    }
    pNodeCurrent->mpNext = pNodeNext->mpNext;
  }
  DoFreeNode(pNode);
  --mnElementCount;
  return iNext;
}

typedef pair<string16, Key> NameKeyPair;
typedef pair<Key, string16> KeyNamePair;
typedef hashtable<NameKeyPair, string16, hash, equal_to> NameKeyMap;
typedef hashtable<KeyNamePair, Key, EA::ResourceMan::KeyHash> KeyNameMap;
}  // namespace eastl

namespace SP {
namespace Thumbnail {

struct AssetGUID {
  uint32_t mnMachineID;
  uint32_t mnAssetGroup;
  uint32_t mnAssetInstance;
};
bool operator==(const AssetGUID& a, const AssetGUID& b);
struct AssetGUIDHash {
  uint32_t operator()(const AssetGUID& g) const;
};
typedef eastl::pair<AssetGUID, Key> GuidKeyPair;
typedef eastl::pair<Key, AssetGUID> KeyGuidPair;
typedef eastl::hashtable<GuidKeyPair, AssetGUID, AssetGUIDHash> GuidKeyMap;
typedef eastl::hashtable<KeyGuidPair, Key, EA::ResourceMan::KeyHash> KeyGuidMap;

struct IMessageServerStub {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void vt2c(void* p, uint32_t a, int b);   // +0x2c
};
IMessageServerStub* GetMessageServer();   // 0x0067dcc0

struct cImageDataEmbed;  // opaque

class cImportExport {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void slot2();
  virtual void slot3();

  eastl::NameKeyMap mNameToKeyMap;   // +0x4
  eastl::KeyNameMap mKeyToNameMap;   // +0x24
  uint32_t mnMachineID;              // +0x44
  GuidKeyMap mGuidToKeyMap;          // +0x48
  KeyGuidMap mKeyToGuidMap;          // +0x68
  uint8_t mImageEmbed[0x58];         // +0x88
  Key mCurImage;                     // +0xe0
  eastl::string16 mExportCellFolderPath;       // +0xec
  eastl::string16 mExportCreaturesFolderPath;  // +0xfc
  eastl::string16 mExportBuildingsFolderPath;  // +0x10c
  eastl::string16 mExportPlantsFolderPath;     // +0x11c
  eastl::string16 mExportVehiclesFolderPath;   // +0x12c
  eastl::string16 mExportUFOsFolderPath;       // +0x13c
  eastl::string16 mExportCityMusicFolderPath;  // +0x14c
  bool mUseShipDir;                            // +0x15c

  bool CreateExportThumb(void* pImage, const Key& key, void* pInfo);   // 0x005fa8d0
  bool RemoveExportThumb(const Key& key);                              // 0x005faec0
  bool ImportFromFolder(const Key& key, void* pArg);                   // 0x005fafb0
  bool Shutdown();                                                     // 0x005fae40
  bool Save();                                                         // 0x005f8ad0
};
}  // namespace Thumbnail
}  // namespace SP

// Vector-of-float with an out-of-line operator= (0x0050d4e0).
struct PodVectorF {
  float* mpBegin;
  float* mpEnd;
  float* mpCapacity;
  const char* mpName;
  uint32_t mFlags;
  PodVectorF& operator=(const PodVectorF& x);
};

// Import-info record copied by 0x005fb350 (copy assignment, retail layout 0x90).
struct cImportInfo {
  uint32_t mKey0, mKey4, mKey8;                 // +0x00, +0x04, +0x08
  uint32_t mEmpty0c;                            // +0x0c
  uint32_t m10, m14, m18, m1c, m20, m24;        // +0x10 .. +0x24
  eastl::string16 mName;                        // +0x28
  uint32_t m38, m3c;                            // +0x38, +0x3c
  eastl::string16 mDisplayName;                 // +0x40
  eastl::string16 mDescription;                 // +0x50
  eastl::string16 mPath;                        // +0x60
  PodVectorF mIDs;                              // +0x70
  uint32_t m84, m88, m8c;                       // +0x84 .. +0x8c
  cImportInfo& operator=(const cImportInfo& o);
};

// free helpers referenced by the reconstructed bodies (masked relocations in the original).
void* FUN_0068e8f0(uint32_t a, uint32_t b, uint32_t c);
bool FillSpriteTexture(void* p, int size);
bool WString_Assign(void* dst, const wchar_t* begin, const wchar_t* end);   // 0x00423650
void QualifyNameWithGroup();
bool FUN_005f97c0(void* a, void* b, void* c, int d, void* e);
void FUN_005f7970(void* p);
void FUN_005f7940(void* p, void* q);
void FUN_005f8320(void* p);
void FUN_005f8390(void* p);
void FUN_005f9080(void* p);
void FUN_005f90c0(void* p);
void FUN_005f8d80(void* p);
void FUN_005f8ed0(void* p, void* q);
void FUN_005f8f00(void* p, void* q);
void FUN_005fa0a0(void* p, void* q);
void FUN_005fa0d0(void* p, void* q);
void FUN_005f9470(void* a, void* b, uint32_t c);

