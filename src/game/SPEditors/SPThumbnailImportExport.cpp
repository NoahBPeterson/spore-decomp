// src/game/SPEditors/SPThumbnailImportExport.cpp -- migrated from slice(s) s005fd260, s005fc330, s005fb430, s005fa8d0, s005f9920, s005f8fe0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPThumbnailImportExport.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stdarg.h>
#include "eastl/string.h"
#include "EA/Allocator/ZoneObject.h"
#include <string.h>
#include <stdlib.h>
#include "EA/IO/FileStream.h"

// ---- items of slice s005f8fe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
template <typename T>
class basic_string_s005f_8fe0 {
 public:
  basic_string_s005f_8fe0* append_sprintf(const char* fmt, ...);
  void append_sprintf_va_list(const char* fmt, va_list* args);  // 0x00475930
  char pad[16];
};  // namespace eastl
}
namespace SP {
namespace Thumbnail {
class cImportExport {
 public:
  void SetupExportFolderPath();  // 0x005f9310
};  // namespace Thumbnail
}  // namespace SP
}
namespace eastl {
template class basic_string_s005f_8fe0<char>;  // namespace eastl
}
// ---- items of slice s005f8fe0 end

// ---- items of slice s005f9920 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gEmptyString[];  // 0x01667bac (EASTL empty-string storage)
void EA_Deallocate(void* p);  // 0x00f47380
struct Str8 {  // eastl::basic_string<char> (3 pointers)
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  int mAllocator;
  Str8() {
    mpBegin = gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  ~Str8() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin)
      EA_Deallocate(mpBegin);
  }
};
struct WStr {  // eastl::basic_string<wchar_t>
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  int mAllocator;
  WStr() {
    mpBegin = (wchar_t*)gEmptyString;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  WStr(const WStr& o);  // 0x0056e2d0
  ~WStr() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin)
      EA_Deallocate(mpBegin);
  }
  void resize(unsigned n);                          // 0x00429520
  void assign(const wchar_t* b, const wchar_t* e);  // 0x00423650
};
struct Key3 {
  unsigned a, b, c;
  Key3() {}
  Key3(unsigned a_, unsigned b_, unsigned c_) : a(a_), b(b_), c(c_) {}
};
void __cdecl StrSprintf(Str8* s, const char* fmt, ...);        // 0x00472fe0
void __cdecl StrAppendSprintf(Str8* s, const char* fmt, ...);  // 0x005f9450
bool __cdecl Str16Equal(const void* a, const void* b);         // 0x0087d9a0
void* __cdecl operator new(unsigned size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
struct IWriter {  // 0x0067da60 memory writer
  IWriter(int a, int b);  // ret 8
  virtual void v0();
  virtual int AddRef();   // +4
  virtual int Release();  // +8
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual bool IsOk();  // +0x18
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual bool Write(const void* p, int n);  // +0x38
  virtual void v15();
  virtual void v16();
  virtual void v17();
  virtual bool Attach(void* req, int n);  // +0x48
  char pad[0x2c];
};
struct IRequest {  // Graphics::GraphicsFactoryAsyncRequest
  IRequest(int a, int b, const char* name);  // 0x0093c270 (ret 0xc)
  void SetProperty(int id, float v);         // 0x0093bb40 (ret 8)
  int Describe(int sz);                      // 0x0093ba70 (ret 4)
  virtual void v0();
  virtual int AddRef();   // +4
  virtual int Release();  // +8
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual int GetSize();  // +0x1c
  virtual void v8();
  virtual void v9();
  virtual void Start(int a, int b);  // +0x28
  char pad[0x20];
};
struct IObj {  // 0x008e2380
  static void* __cdecl operator new(unsigned size, const char* name, int a, int b, int c, int d);  // 0x00926020
  IObj(int a, IWriter* w, Key3* key, int c, int d);  // ret 0x14
  virtual void v0();
  virtual int AddRef();   // +4
  virtual int Release();  // +8
  virtual void v3();
  virtual Key3* GetInfo();  // +0x10
  char pad[0x20];
};
struct IRes {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual bool Place(void* a, IObj* o, int b, int c);  // +0x28
};
struct IMgr {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual void v14();
  virtual void v15();
  virtual void v16();
  virtual void v17();
  virtual IRes* Lookup(unsigned a, int b);  // +0x48
};
IMgr* __cdecl GetManager();  // 0x0067dcd0
struct cAssetMetadata_s005f_9920 {
  Key3* GetKey();                 // 0x005507c0
  unsigned long long* GetA();     // 0x005507a0
  unsigned long long* GetB();     // 0x00550840
  const wchar_t* GetNameW();      // 0x00550880
  unsigned long long GetAssetKey();  // 0x005508a0
  const wchar_t* GetNameW2();     // 0x00414e10
  const wchar_t* GetNameW3();     // 0x005508c0
  unsigned GetYCount();           // 0x005509b0
  const wchar_t* GetY(unsigned i);  // 0x005509e0
  unsigned GetZCount();           // 0x00550a30
  unsigned GetZ(unsigned i);      // 0x00550a60
};
namespace SP {
namespace Pollen {
void __cdecl GetParentServerID(cAssetMetadata_s005f_9920* m, unsigned long long* a, unsigned long long* b);  // 0x00552080
}
}
struct JobLock {
  bool H3(int a);  // 0x0068eef0
  bool H(int a);   // 0x0068eca0
  bool H2(int a);  // 0x0068ed70
};
struct IStream {
  virtual void v0();
  virtual int AddRef();   // +4
  virtual int Release();  // +8
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void* GetReader();  // +0x18
  virtual void v7();
  virtual void v8();
  virtual void Close();  // +0x24
};
struct IReader {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual int Read(void* p, int n);  // +0x30
};
struct ISaveArea {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual bool Open(void* key, IStream** out, int a, int b, int c, int d);  // +0x34
};
ISaveArea* __cdecl GetSaveArea(int id);  // 0x006b1f90
void __cdecl FixPath(WStr* s);           // 0x005f7970
struct PathBuf {  // 0x0092fcc0
  char d[0x420];
  PathBuf();
  void AssignW(const wchar_t* p);        // 0x00930da0 (ret 4)
  void SetName(const wchar_t* p, int a);  // 0x00931100 (ret 8)
  const wchar_t* c_str();                // 0x00572590
};
struct PairWK {  // pair<wstring, key>   0x005f8690
  WStr s;
  Key3 k;
  PairWK(const WStr& a, const Key3& b);  // 0x005f8690
};
struct ValueWK {  // pair<const wstring, key>   0x005f8320
  WStr s;
  Key3 k;
  ValueWK(const PairWK& p);  // 0x005f8320
};
struct PairKW {  // 0x005f8700
  Key3 k;
  WStr s;
  PairKW(const Key3& a, const WStr& b);  // 0x005f8700
};
struct ValueKW {  // 0x005f8390
  Key3 k;
  WStr s;
  ValueKW(const PairKW& p);  // 0x005f8390
};
struct PairKK {
  Key3 a, b;
  PairKK(const Key3& x, const Key3& y) : a(x), b(y) {}
};
struct IterBool { int it[3]; };
struct MapWK {  // 0x005f9470
  char d[0x20];
  void Insert(IterBool* out, const ValueWK& v, bool b);  // 0x005f9470
};
struct MapKW {  // 0x005f95a0
  char d[0x20];
  void Insert(IterBool* out, const ValueKW& v, bool b);  // 0x005f95a0
};
struct MapKK {  // 0x005f8170
  char d[0x20];
  void Insert(IterBool* out, const PairKK& v, bool b);  // 0x005f8170
};
struct MapKK2 {  // 0x005f8240
  char d[0x20];
  void Insert(IterBool* out, const PairKK& v, bool b);  // 0x005f8240
};
namespace SP {
namespace Thumbnail {
class cImportExport_s005f_9920 {
 public:
  bool WriteAssetDataToImage(cAssetMetadata_s005f_9920* meta, void* a, int b);  // 0x005f9920
  bool RestoreImportTable();                                         // 0x005fa290
  void ResolveName(unsigned id, WStr* out);                          // 0x005f9230
  char pad0[4];
  MapWK mWK;      // +4
  MapKW mKW;      // +0x24
  unsigned mField44;
  MapKK mKK;      // +0x48
  MapKK2 mKK2;    // +0x68
  JobLock mLock;  // +0x88
};  // namespace Thumbnail
}
}
struct StrNode {
  WStr key;        // 0x10 bytes (with allocator)
  StrNode* next;   // +0x10
};
struct StrTable {
  unsigned pad0;
  StrNode** mBuckets;  // +4
  unsigned mBucketCount;  // +8
  int mSize;  // +0xc
  unsigned erase(const WStr* key);
};
// ---- items of slice s005f9920 end

// ---- items of slice s005fa8d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void _pv##n();
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
void  operator delete(void* p); // 0x00f47380
inline void* operator new(size_t, void* p) throw() { return p; }
namespace EA {
namespace ResourceMan {
struct Key_s005f_a8d0 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
}
}
namespace EA {
namespace ResourceMan {
bool operator==(const Key_s005f_a8d0& a, const Key_s005f_a8d0& b);
}
}
namespace EA {
namespace ResourceMan {
struct KeyHash_s005f_a8d0 {
  uint32_t operator()(const Key_s005f_a8d0& k) const;
};
}
}
using EA::ResourceMan::Key_s005f_a8d0;
namespace eastl {
struct allocator_s005f_a8d0 {
  void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, "allocator.h", 0xd1); }
  void deallocate(void* p) { operator delete(p); }
};
}
namespace eastl {
extern wchar_t gEmptyString16[2];
}
namespace eastl {
inline wchar_t* GetEmptyStringW() { return gEmptyString16; }
}
namespace eastl {
template <typename T>
class basic_string_s005f_a8d0 {
 public:
  typedef T* iterator;
  typedef size_t size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  allocator_s005f_a8d0 mAllocator;

  basic_string_s005f_a8d0() { AllocateSelf(); }
  basic_string_s005f_a8d0(const basic_string_s005f_a8d0& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
  ~basic_string_s005f_a8d0() { DeallocateSelf(); }

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
  basic_string_s005f_a8d0& assign(const T* pBegin, const T* pEnd);
  basic_string_s005f_a8d0& operator=(const basic_string_s005f_a8d0& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
};
}
namespace eastl {
typedef basic_string_s005f_a8d0<wchar_t> string16_s005f_a8d0;
}
namespace eastl {
bool operator==(const basic_string_s005f_a8d0<wchar_t>& a, const basic_string_s005f_a8d0<wchar_t>& b); // 0x0087d9a0
}
namespace eastl {
struct hash_s005f_a8d0 {
  uint32_t operator()(const string16_s005f_a8d0& s) const {
    const wchar_t* p = s.mpBegin;
    uint32_t h = 0x811c9dc5;
    uint32_t c = (uint32_t)*p;
    while (c) { h = h * 0x1000193 ^ c; ++p; c = (uint32_t)*p; }
    return h;
  }
};
}
namespace eastl {
struct equal_to_s005f_a8d0 {
  bool operator()(const string16_s005f_a8d0& a, const string16_s005f_a8d0& b) const { return a == b; }
};
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s005f_a8d0 {
  T1 first;
  T2 second;
  pair_s005f_a8d0(const T1& x, const T2& y) : first(x), second(y) {}
  pair_s005f_a8d0(const pair_s005f_a8d0& p) : first(p.first), second(p.second) {}
  ~pair_s005f_a8d0() {}
};
}
namespace eastl {
template <typename Value>
struct hash_node_s005f_a8d0 {
  Value mValue;
  hash_node_s005f_a8d0* mpNext;
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
}
namespace eastl {
struct RehashResult { bool first; uint32_t second; };
}
namespace eastl {
struct prime_rehash_policy_s005f_a8d0 {
  float mfMaxLoadFactor;
  float mfGrowthFactor;
  uint32_t mnNextResize;
  RehashResult GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd);
};
}
namespace eastl {
extern void* gEmptyBucketArray;   // 0x0154df28
}
namespace eastl {
template <typename Value, typename KeyT, typename Hash, typename Equal = equal_to_s005f_a8d0>
class hashtable_s005f_a8d0 {
 public:
  typedef hash_node_s005f_a8d0<Value> node_type;
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
  prime_rehash_policy_s005f_a8d0 mRehashPolicy;
  allocator_s005f_a8d0 mAllocator;

  hashtable_s005f_a8d0() : mpBucketArray((node_type**)&gEmptyBucketArray), mnBucketCount(1), mnElementCount(0) {
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
  pair_s005f_a8d0<iterator, iterator> equal_range(const KeyT& k);
  uint32_t erase(const KeyT& k);
  iterator erase(const_iterator i);
  void DoFreeNodes(node_type** pBucketArray, uint32_t n);
  void clear() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
  }
  ~hashtable_s005f_a8d0() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1) mAllocator.deallocate(mpBucketArray);
  }
};
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
typename hashtable_s005f_a8d0<V, K, H, E>::iterator hashtable_s005f_a8d0<V, K, H, E>::find(const K& k) {
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type* const pNode = DoFindNode(mpBucketArray[n], k);
  return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
}
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
pair_s005f_a8d0<typename hashtable_s005f_a8d0<V, K, H, E>::iterator, typename hashtable_s005f_a8d0<V, K, H, E>::iterator>
hashtable_s005f_a8d0<V, K, H, E>::equal_range(const K& k) {
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
    return pair_s005f_a8d0<iterator, iterator>(first, last);
  }
  return pair_s005f_a8d0<iterator, iterator>(iterator(mpBucketArray + mnBucketCount), iterator(mpBucketArray + mnBucketCount));
}
}
namespace eastl {
typedef pair_s005f_a8d0<string16_s005f_a8d0, Key_s005f_a8d0> NameKeyPair;
}
namespace eastl {
typedef pair_s005f_a8d0<Key_s005f_a8d0, string16_s005f_a8d0> KeyNamePair;
}
namespace eastl {
typedef hashtable_s005f_a8d0<NameKeyPair, string16_s005f_a8d0, hash_s005f_a8d0, equal_to_s005f_a8d0> NameKeyMap;
}
namespace eastl {
typedef hashtable_s005f_a8d0<KeyNamePair, Key_s005f_a8d0, EA::ResourceMan::KeyHash_s005f_a8d0> KeyNameMap;
}
namespace SP {
namespace Thumbnail {
struct AssetGUID {
  uint32_t mnMachineID;
  uint32_t mnAssetGroup;
  uint32_t mnAssetInstance;
};
}
}
namespace SP {
namespace Thumbnail {
bool operator==(const AssetGUID& a, const AssetGUID& b);
}
}
namespace SP {
namespace Thumbnail {
struct AssetGUIDHash {
  uint32_t operator()(const AssetGUID& g) const;
};
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s005f_a8d0<AssetGUID, Key_s005f_a8d0> GuidKeyPair;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s005f_a8d0<Key_s005f_a8d0, AssetGUID> KeyGuidPair;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s005f_a8d0<GuidKeyPair, AssetGUID, AssetGUIDHash> GuidKeyMap;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s005f_a8d0<KeyGuidPair, Key_s005f_a8d0, EA::ResourceMan::KeyHash_s005f_a8d0> KeyGuidMap;
}
}
namespace SP {
namespace Thumbnail {
struct IMessageServerStub {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void vt2c(void* p, uint32_t a, int b);   // +0x2c
};
}
}
namespace SP {
namespace Thumbnail {
IMessageServerStub* GetMessageServer();   // 0x0067dcc0
}
}
namespace SP {
namespace Thumbnail {
class cImportExport_s005f_a8d0 {
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
  Key_s005f_a8d0 mCurImage;                     // +0xe0
  eastl::string16_s005f_a8d0 mExportCellFolderPath;       // +0xec
  eastl::string16_s005f_a8d0 mExportCreaturesFolderPath;  // +0xfc
  eastl::string16_s005f_a8d0 mExportBuildingsFolderPath;  // +0x10c
  eastl::string16_s005f_a8d0 mExportPlantsFolderPath;     // +0x11c
  eastl::string16_s005f_a8d0 mExportVehiclesFolderPath;   // +0x12c
  eastl::string16_s005f_a8d0 mExportUFOsFolderPath;       // +0x13c
  eastl::string16_s005f_a8d0 mExportCityMusicFolderPath;  // +0x14c
  bool mUseShipDir;                            // +0x15c

  bool CreateExportThumb(void* pImage, const Key_s005f_a8d0& key, void* pInfo);   // 0x005fa8d0
  bool RemoveExportThumb(const Key_s005f_a8d0& key);                              // 0x005faec0
  bool ImportFromFolder(const Key_s005f_a8d0& key, void* pArg);                   // 0x005fafb0
  bool Shutdown();                                                     // 0x005fae40
  bool Save();                                                         // 0x005f8ad0
};
}
}
struct PodVectorF {
  float* mpBegin;
  float* mpEnd;
  float* mpCapacity;
  const char* mpName;
  uint32_t mFlags;
  PodVectorF& operator=(const PodVectorF& x);
};
struct cImportInfo {
  uint32_t mKey0, mKey4, mKey8;                 // +0x00, +0x04, +0x08
  uint32_t mEmpty0c;                            // +0x0c
  uint32_t m10, m14, m18, m1c, m20, m24;        // +0x10 .. +0x24
  eastl::string16_s005f_a8d0 mName;                        // +0x28
  uint32_t m38, m3c;                            // +0x38, +0x3c
  eastl::string16_s005f_a8d0 mDisplayName;                 // +0x40
  eastl::string16_s005f_a8d0 mDescription;                 // +0x50
  eastl::string16_s005f_a8d0 mPath;                        // +0x60
  PodVectorF mIDs;                              // +0x70
  uint32_t m84, m88, m8c;                       // +0x84 .. +0x8c
  cImportInfo& operator=(const cImportInfo& o);
};
namespace EA {
namespace IO {
namespace File {
bool Remove(const wchar_t* path);   // 0x00931fd0
}
}
}
template class eastl::hashtable_s005f_a8d0<eastl::NameKeyPair, eastl::string16_s005f_a8d0, eastl::hash_s005f_a8d0, eastl::equal_to_s005f_a8d0>;
template class eastl::hashtable_s005f_a8d0<eastl::KeyNamePair, Key_s005f_a8d0, EA::ResourceMan::KeyHash_s005f_a8d0, eastl::equal_to_s005f_a8d0>;
// ---- items of slice s005fa8d0 end

// ---- items of slice s005fb430 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace ResourceMan {
struct Key_s005f_b430 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
}
}
namespace EA {
namespace ResourceMan {
bool operator==(const Key_s005f_b430& a, const Key_s005f_b430& b);
}
}
namespace EA {
namespace ResourceMan {
struct KeyHash_s005f_b430 {
  uint32_t operator()(const Key_s005f_b430& k) const;
};
}
}
using EA::ResourceMan::Key_s005f_b430;
namespace eastl {
struct allocator_s005f_b430 {
  void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, "allocator.h", 0xd1); }
  void deallocate(void* p) { operator delete(p); }
};
}
namespace eastl {
template <typename T>
class basic_string_s005f_b430 {
 public:
  typedef T* iterator;
  typedef size_t size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  allocator_s005f_b430 mAllocator;

  basic_string_s005f_b430() { AllocateSelf(); }
  basic_string_s005f_b430(const basic_string_s005f_b430& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
  ~basic_string_s005f_b430() { DeallocateSelf(); }

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
  basic_string_s005f_b430& assign(const T* pBegin, const T* pEnd);
  basic_string_s005f_b430& operator=(const basic_string_s005f_b430& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
};
}
namespace eastl {
typedef basic_string_s005f_b430<wchar_t> string16_s005f_b430;
}
namespace eastl {
bool operator==(const basic_string_s005f_b430<wchar_t>& a, const basic_string_s005f_b430<wchar_t>& b); // 0x0087d9a0
}
namespace eastl {
struct hash_s005f_b430 {
  uint32_t operator()(const string16_s005f_b430& s) const {
    const wchar_t* p = s.mpBegin;
    uint32_t h = 0x811c9dc5;
    uint32_t c = (uint32_t)*p;
    while (c) { h = h * 0x1000193 ^ c; ++p; c = (uint32_t)*p; }
    return h;
  }
};
}
namespace eastl {
struct equal_to_s005f_b430 {
  bool operator()(const string16_s005f_b430& a, const string16_s005f_b430& b) const { return a == b; }
};
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s005f_b430 {
  T1 first;
  T2 second;
  pair_s005f_b430(const T1& x, const T2& y) : first(x), second(y) {}
  pair_s005f_b430(const pair_s005f_b430& p) : first(p.first), second(p.second) {}
  ~pair_s005f_b430() {}
};
}
namespace eastl {
template <typename Value>
struct hash_node_s005f_b430 {
  Value mValue;
  hash_node_s005f_b430* mpNext;
};
}
namespace eastl {
struct prime_rehash_policy_s005f_b430 {
  float mfMaxLoadFactor;
  float mfGrowthFactor;
  uint32_t mnNextResize;
  RehashResult GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd);
};
}
namespace eastl {
template <typename Value, typename KeyT, typename Hash, typename Equal = equal_to_s005f_b430>
class hashtable_s005f_b430 {
 public:
  typedef hash_node_s005f_b430<Value> node_type;
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
  prime_rehash_policy_s005f_b430 mRehashPolicy;
  allocator_s005f_b430 mAllocator;

  hashtable_s005f_b430() : mpBucketArray((node_type**)&gEmptyBucketArray), mnBucketCount(1), mnElementCount(0) {
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
  pair_s005f_b430<iterator, iterator> equal_range(const KeyT& k);
  uint32_t erase(const KeyT& k);
  iterator erase(const_iterator i);
  void DoFreeNodes(node_type** pBucketArray, uint32_t n);
  void clear() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
  }
  ~hashtable_s005f_b430() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1) mAllocator.deallocate(mpBucketArray);
  }
};
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
typename hashtable_s005f_b430<V, K, H, E>::iterator hashtable_s005f_b430<V, K, H, E>::find(const K& k) {
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type* const pNode = DoFindNode(mpBucketArray[n], k);
  return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
}
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
pair_s005f_b430<typename hashtable_s005f_b430<V, K, H, E>::iterator, typename hashtable_s005f_b430<V, K, H, E>::iterator>
hashtable_s005f_b430<V, K, H, E>::equal_range(const K& k) {
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
    return pair_s005f_b430<iterator, iterator>(first, last);
  }
  return pair_s005f_b430<iterator, iterator>(iterator(mpBucketArray + mnBucketCount), iterator(mpBucketArray + mnBucketCount));
}
}
namespace eastl {
typedef pair_s005f_b430<string16_s005f_b430, Key_s005f_b430> NameKeyPair_s005f_b430;
}
namespace eastl {
typedef pair_s005f_b430<Key_s005f_b430, string16_s005f_b430> KeyNamePair_s005f_b430;
}
namespace eastl {
typedef hashtable_s005f_b430<NameKeyPair_s005f_b430, string16_s005f_b430, hash_s005f_b430, equal_to_s005f_b430> NameKeyMap_s005f_b430;
}
namespace eastl {
typedef hashtable_s005f_b430<KeyNamePair_s005f_b430, Key_s005f_b430, EA::ResourceMan::KeyHash_s005f_b430> KeyNameMap_s005f_b430;
}
namespace SP {
namespace Thumbnail {
struct AssetGUID_s005f_b430 {
  uint32_t mnMachineID;
  uint32_t mnAssetGroup;
  uint32_t mnAssetInstance;
};
}
}
namespace SP {
namespace Thumbnail {
bool operator==(const AssetGUID_s005f_b430& a, const AssetGUID_s005f_b430& b);
}
}
namespace SP {
namespace Thumbnail {
struct AssetGUIDHash_s005f_b430 {
  uint32_t operator()(const AssetGUID_s005f_b430& g) const;
};
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s005f_b430<AssetGUID_s005f_b430, Key_s005f_b430> GuidKeyPair_s005f_b430;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s005f_b430<Key_s005f_b430, AssetGUID_s005f_b430> KeyGuidPair_s005f_b430;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s005f_b430<GuidKeyPair_s005f_b430, AssetGUID_s005f_b430, AssetGUIDHash_s005f_b430> GuidKeyMap_s005f_b430;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s005f_b430<KeyGuidPair_s005f_b430, Key_s005f_b430, EA::ResourceMan::KeyHash_s005f_b430> KeyGuidMap_s005f_b430;
}
}
struct RefVec {
  void* mpBegin;
  ~RefVec() {
    if (mpBegin && ((int*)mpBegin)[-1]) operator delete(mpBegin);
  }
};
struct IHandlerBase {
  virtual void s0();
  virtual void s1();
  virtual void s2();
  virtual ~IHandlerBase() {}
};
struct cImportExportRetail : IHandlerBase {
  eastl::NameKeyMap_s005f_b430 mNameToKeyMap;   // +0x04
  eastl::KeyNameMap_s005f_b430 mKeyToNameMap;   // +0x24
  uint32_t mnMachineID;              // +0x44
  SP::Thumbnail::GuidKeyMap_s005f_b430 mGuidToKeyMap;  // +0x48
  SP::Thumbnail::KeyGuidMap_s005f_b430 mKeyToGuidMap;  // +0x68
  RefVec mVec88;                     // +0x88
  char pad8c[0xe0 - 0x8c];           // +0x8c
  RefVec mVecE0;                     // +0xe0
  char padE4[0x104 - 0xe4];          // +0xe4
  eastl::string16_s005f_b430 s104, s114, s124, s134, s144, s154, s164, s174;
  ~cImportExportRetail();

  unsigned char UpdateExportThumb(void* param_2);   // 0x005fb430
};
// ---- items of slice s005fb430 end

// ---- items of slice s005fc330 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace ResourceMan {
struct Key_s005f_c330 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
}
}
namespace EA {
namespace ResourceMan {
bool operator==(const Key_s005f_c330& a, const Key_s005f_c330& b);
}
}
namespace EA {
namespace ResourceMan {
struct KeyHash_s005f_c330 {
  uint32_t operator()(const Key_s005f_c330& k) const;
};
}
}
using EA::ResourceMan::Key_s005f_c330;
namespace eastl {
struct allocator_s005f_c330 {
  void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, "allocator.h", 0xd1); }
  void deallocate(void* p) { operator delete(p); }
};
}
namespace eastl {
template <typename T>
class basic_string_s005f_c330 {
 public:
  typedef T* iterator;
  typedef size_t size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  allocator_s005f_c330 mAllocator;

  basic_string_s005f_c330() { AllocateSelf(); }
  basic_string_s005f_c330(const basic_string_s005f_c330& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
  ~basic_string_s005f_c330() { DeallocateSelf(); }

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
  basic_string_s005f_c330& assign(const T* pBegin, const T* pEnd);
  basic_string_s005f_c330& operator=(const basic_string_s005f_c330& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
};
}
namespace eastl {
typedef basic_string_s005f_c330<wchar_t> string16_s005f_c330;
}
namespace eastl {
bool operator==(const basic_string_s005f_c330<wchar_t>& a, const basic_string_s005f_c330<wchar_t>& b); // 0x0087d9a0
}
namespace eastl {
struct hash_s005f_c330 {
  uint32_t operator()(const string16_s005f_c330& s) const {
    const wchar_t* p = s.mpBegin;
    uint32_t h = 0x811c9dc5;
    uint32_t c = (uint32_t)*p;
    while (c) { h = h * 0x1000193 ^ c; ++p; c = (uint32_t)*p; }
    return h;
  }
};
}
namespace eastl {
struct equal_to_s005f_c330 {
  bool operator()(const string16_s005f_c330& a, const string16_s005f_c330& b) const { return a == b; }
};
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s005f_c330 {
  T1 first;
  T2 second;
  pair_s005f_c330(const T1& x, const T2& y) : first(x), second(y) {}
  pair_s005f_c330(const pair_s005f_c330& p) : first(p.first), second(p.second) {}
  ~pair_s005f_c330() {}
};
}
namespace eastl {
template <typename Value>
struct hash_node_s005f_c330 {
  Value mValue;
  hash_node_s005f_c330* mpNext;
};
}
namespace eastl {
struct true_type {};
}
namespace eastl {
struct prime_rehash_policy_s005f_c330 {
  float mfMaxLoadFactor;
  float mfGrowthFactor;
  uint32_t mnNextResize;
  RehashResult GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd);
};
}
namespace eastl {
template <typename Value, typename KeyT, typename Hash, typename Equal = equal_to_s005f_c330>
class hashtable_s005f_c330 {
 public:
  typedef hash_node_s005f_c330<Value> node_type;
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
  prime_rehash_policy_s005f_c330 mRehashPolicy;
  allocator_s005f_c330 mAllocator;

  hashtable_s005f_c330() : mpBucketArray((node_type**)&gEmptyBucketArray), mnBucketCount(1), mnElementCount(0) {
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
  pair_s005f_c330<iterator, iterator> equal_range(const KeyT& k);
  uint32_t erase(const KeyT& k);
  iterator erase(const_iterator i);
  void DoFreeNodes(node_type** pBucketArray, uint32_t n);
  void clear() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
  }
  ~hashtable_s005f_c330() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1) mAllocator.deallocate(mpBucketArray);
  }
};
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
typename hashtable_s005f_c330<V, K, H, E>::iterator hashtable_s005f_c330<V, K, H, E>::find(const K& k) {
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type* const pNode = DoFindNode(mpBucketArray[n], k);
  return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
}
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
pair_s005f_c330<typename hashtable_s005f_c330<V, K, H, E>::iterator, typename hashtable_s005f_c330<V, K, H, E>::iterator>
hashtable_s005f_c330<V, K, H, E>::equal_range(const K& k) {
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
    return pair_s005f_c330<iterator, iterator>(first, last);
  }
  return pair_s005f_c330<iterator, iterator>(iterator(mpBucketArray + mnBucketCount), iterator(mpBucketArray + mnBucketCount));
}
}
namespace eastl {
typedef pair_s005f_c330<string16_s005f_c330, Key_s005f_c330> NameKeyPair_s005f_c330;
}
namespace eastl {
typedef pair_s005f_c330<Key_s005f_c330, string16_s005f_c330> KeyNamePair_s005f_c330;
}
namespace eastl {
typedef hashtable_s005f_c330<NameKeyPair_s005f_c330, string16_s005f_c330, hash_s005f_c330, equal_to_s005f_c330> NameKeyMap_s005f_c330;
}
namespace eastl {
typedef hashtable_s005f_c330<KeyNamePair_s005f_c330, Key_s005f_c330, EA::ResourceMan::KeyHash_s005f_c330> KeyNameMap_s005f_c330;
}
namespace SP {
namespace Thumbnail {
struct AssetGUID_s005f_c330 {
  uint32_t mnMachineID;
  uint32_t mnAssetGroup;
  uint32_t mnAssetInstance;
};
}
}
namespace SP {
namespace Thumbnail {
bool operator==(const AssetGUID_s005f_c330& a, const AssetGUID_s005f_c330& b);
}
}
namespace SP {
namespace Thumbnail {
struct AssetGUIDHash_s005f_c330 {
  uint32_t operator()(const AssetGUID_s005f_c330& g) const;
};
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s005f_c330<AssetGUID_s005f_c330, Key_s005f_c330> GuidKeyPair_s005f_c330;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s005f_c330<Key_s005f_c330, AssetGUID_s005f_c330> KeyGuidPair_s005f_c330;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s005f_c330<GuidKeyPair_s005f_c330, AssetGUID_s005f_c330, AssetGUIDHash_s005f_c330> GuidKeyMap_s005f_c330;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s005f_c330<KeyGuidPair_s005f_c330, Key_s005f_c330, EA::ResourceMan::KeyHash_s005f_c330> KeyGuidMap_s005f_c330;
}
}
struct RefVec8 {
  void* mpBegin;
  ~RefVec8() {
    if (mpBegin && ((int*)mpBegin)[-1]) operator delete(mpBegin);
  }
};
struct IHandlerBase8 {
  virtual void s0();
  virtual void s1();
  virtual ~IHandlerBase8() {}
};
struct cImageDataEmbed8 {
  RefVec8 v0;
  char pad0[0x58 - 4];
  RefVec8 v58;
  char pad58[0x70 - 0x5c];
  cImageDataEmbed8();
  void Serialize(void* stream, int flag);   // 0x0068e1a0
};
namespace IN {
struct wstr { const wchar_t* b; const wchar_t* e; const wchar_t* c; uint32_t alloc; };
}
namespace IN {
struct IRefObj { virtual void _a0(); virtual void _a1(); virtual void Release(); };
}
namespace IN {
struct IRecordS {
  virtual void _r0(); virtual void AddRef(); virtual void Release();
  PV(3) PV(4) PV(5)
  virtual void* GetStream();            // +0x18
  PV(7) PV(8)
  virtual void _r9();
  virtual bool RecordClose();           // +0x24
};
}
namespace IN {
struct ResObjS {
  virtual void AddRef(); virtual void Release();
  int rc; Key_s005f_c330 key;
};
}
namespace IN {
struct AssetMeta {
  virtual void AddRef(); virtual void Release();
  char pad[0xd8 - 4];
  AssetMeta();
  void SetMetadata(Key_s005f_c330* k, uint64_t id, uint64_t t, const wchar_t* name, uint64_t aid, const wchar_t* aname,
                   const wchar_t* desc, const wchar_t* tags, const char* authors, bool b);  // 0x551620
  void SetParentAssetID(uint64_t id);   // 0x551b60
  void SetFlag(bool b);                 // 0x550990
  void AddTrait(uint32_t t);            // 0x550b00
};
}
namespace IN {
struct MemRecord : IRecordS {
  char pad[0x24 - 4];
  MemRecord(uint32_t a, IRefObj* o, Key_s005f_c330* k, uint32_t b, uint32_t c);   // 0x8e2380
  static void* operator new(size_t, const char*, int, int, int, int);   // 0x926020
  static void operator delete(void*, const char*, int, int, int, int) {}
};
}
namespace IN {
struct Database {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual bool OpenRecord(Key_s005f_c330* k, IRecordS** pp, int access, int cd, int b, int c);   // +0x34
};
}
namespace IN {
struct IResourceFactory {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool CreateResource(IRecordS* rec, ResObjS** pDst, void* extra, uint32_t type);   // +0x1c
};
}
namespace IN {
struct IResourceManager {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual bool WriteResource(void* res, void* extra, Database* db, void* fac, const Key_s005f_c330* nameKey);   // +0x20
  PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
  virtual IResourceFactory* FindFactory(uint32_t type, uint32_t recType);   // +0x48
};
}
namespace IN {
struct IIDGen {
  PV(0) PV(1)
  virtual void Generate(Key_s005f_c330* out, uint32_t a, uint32_t b);   // +8
};
}
namespace IN {
struct IKeyLookup {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual int Lookup(Key_s005f_c330* k);   // +0x58
};
}
namespace IN {
struct IMsgServer {
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void Post(uint32_t msg, Key_s005f_c330* data, int b);   // +0x14
};
}
namespace IN {
struct AssetDirectory {
  bool GetLocalKey(uint64_t id, Key_s005f_c330* out);          // 0x54e460
  void RemoveMapping(uint64_t id, int b);           // 0x54ed50
  void AddMapping(uint64_t id, Key_s005f_c330* k);             // 0x54e250
};
}
namespace IN {
struct PollenModule { char pad[0x58]; AssetDirectory* mpAssetDir; };
}
namespace IN {
PollenModule* GetPollenModule();                    // 0x0067cb30
}
namespace IN {
IKeyLookup* GetKeyLookup();                         // 0x008de1a0
}
namespace IN {
IIDGen* GetIDGenerator();                           // 0x0067de60
}
namespace IN {
IResourceManager* GetManager_s005f_c330();                     // 0x0067dcd0
}
namespace IN {
IMsgServer* GetMessageServer();                     // 0x0067dcc0
}
namespace IN {
Database* GetSaveArea(uint32_t id);                 // 0x006b1f90
}
namespace IN {
void FUN_006ad010(void* p);
}
namespace IN {
void FUN_006ac0a0(int a, void* p);
}
namespace IN {
struct FileStream {
  void* vptr; char pad[0x21c - 4];
  FileStream(const wchar_t* path);                  // 0x00931e10
  void AddRef();                                    // 0x009317b0
  bool Open(int a, int b, int c, int d);            // 0x009318f0
  void Close();                                     // 0x00931a70
  ~FileStream();                                    // 0x00931e70
};
}
namespace IN {
static wchar_t sEmptyStr[2];
}
namespace IN {
struct ImpInfo {
  uint32_t u0, idA, idB, u0c;
  uint64_t assetId;     // +0x10
  uint64_t parentId;    // +0x18
  uint64_t timeCreated; // +0x20
  wstr name;            // +0x28
  uint64_t authorId;    // +0x38
  wstr authorName;      // +0x40
  wstr desc;            // +0x50
  wstr tags;            // +0x60
  uint32_t* idsBegin; uint32_t* idsEnd; uint32_t* idsCap;   // +0x70
  uint32_t u7c, u80;
  SP::Thumbnail::AssetGUID_s005f_c330 guid;   // +0x84
  ImpInfo() {
    const wchar_t* e = sEmptyStr;
    name.b = name.e = e; name.c = e + 1;
    authorName.b = authorName.e = e; authorName.c = e + 1;
    desc.b = desc.e = e; desc.c = e + 1;
    tags.b = tags.e = e; tags.c = e + 1;
    idsBegin = 0; idsEnd = 0; idsCap = 0;
  }
  ~ImpInfo();                                       // 0x005f8e40
};
}
namespace IN {
struct GuidMapX : SP::Thumbnail::GuidKeyMap_s005f_c330 {
  iterator find(const SP::Thumbnail::AssetGUID_s005f_c330& g);   // 0x005f8050
  insert_return_type DoInsertValue(const SP::Thumbnail::GuidKeyPair_s005f_c330& v, eastl::true_type);   // 0x005f8170
};
}
namespace IN {
struct KeyGuidMapX : SP::Thumbnail::KeyGuidMap_s005f_c330 {
  insert_return_type DoInsertValue(const SP::Thumbnail::KeyGuidPair_s005f_c330& v, eastl::true_type);   // 0x005f8240
};
}
void* operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0
struct cImportExportCtor : IHandlerBase8 {
  eastl::NameKeyMap_s005f_c330 mNameToKeyMap;             // +0x04
  eastl::KeyNameMap_s005f_c330 mKeyToNameMap;             // +0x24
  uint32_t mnMachineID;                        // +0x44
  SP::Thumbnail::GuidKeyMap_s005f_c330 mGuidToKeyMap;     // +0x48
  SP::Thumbnail::KeyGuidMap_s005f_c330 mKeyToGuidMap;     // +0x68
  cImageDataEmbed8 mEmbed;                     // +0x88
  uint32_t xf8, xfc, x100;                     // +0xf8
  eastl::string16_s005f_c330 s104, s114, s124, s134, s144, s154, s164, s174;

  cImportExportCtor();                         // 0x005fcf40
  bool CreateKey(IN::FileStream* s, IN::ImpInfo* info, IN::IRefObj** pp);   // 0x005fbb00
  unsigned char ScanForImports();              // 0x005fd0a0
  bool ImportNewAsset(const wchar_t* path, Key_s005f_c330* pOut);   // 0x005fc330
  bool ScanFolder(const void* a, void* b, void* c);   // 0x005fc9f0
};
__declspec(noinline) cImageDataEmbed8::cImageDataEmbed8() { v0.mpBegin = 0; v58.mpBegin = 0; }
// ---- items of slice s005fc330 end

// ---- items of slice s005fd260 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace ResourceMan {
struct Key_s005f_d260 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
}
}
namespace EA {
namespace ResourceMan {
bool operator==(const Key_s005f_d260& a, const Key_s005f_d260& b);
}
}
namespace EA {
namespace ResourceMan {
struct KeyHash_s005f_d260 {
  uint32_t operator()(const Key_s005f_d260& k) const;
};
}
}
using EA::ResourceMan::Key_s005f_d260;
namespace eastl {
struct allocator_s005f_d260 {
  void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, "allocator.h", 0xd1); }
  void deallocate(void* p) { operator delete(p); }
};
}
namespace eastl {
template <typename T>
class basic_string_s005f_d260 {
 public:
  typedef T* iterator;
  typedef size_t size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  allocator_s005f_d260 mAllocator;

  basic_string_s005f_d260() { AllocateSelf(); }
  basic_string_s005f_d260(const basic_string_s005f_d260& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
  ~basic_string_s005f_d260() { DeallocateSelf(); }

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
  basic_string_s005f_d260& assign(const T* pBegin, const T* pEnd);
  basic_string_s005f_d260& operator=(const basic_string_s005f_d260& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
};
}
namespace eastl {
typedef basic_string_s005f_d260<wchar_t> string16_s005f_d260;
}
namespace eastl {
bool operator==(const basic_string_s005f_d260<wchar_t>& a, const basic_string_s005f_d260<wchar_t>& b); // 0x0087d9a0
}
namespace eastl {
struct hash_s005f_d260 {
  uint32_t operator()(const string16_s005f_d260& s) const {
    const wchar_t* p = s.mpBegin;
    uint32_t h = 0x811c9dc5;
    uint32_t c = (uint32_t)*p;
    while (c) { h = h * 0x1000193 ^ c; ++p; c = (uint32_t)*p; }
    return h;
  }
};
}
namespace eastl {
struct equal_to_s005f_d260 {
  bool operator()(const string16_s005f_d260& a, const string16_s005f_d260& b) const { return a == b; }
};
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s005f_d260 {
  T1 first;
  T2 second;
  pair_s005f_d260(const T1& x, const T2& y) : first(x), second(y) {}
  pair_s005f_d260(const pair_s005f_d260& p) : first(p.first), second(p.second) {}
  ~pair_s005f_d260() {}
};
}
namespace eastl {
template <typename Value>
struct hash_node_s005f_d260 {
  Value mValue;
  hash_node_s005f_d260* mpNext;
};
}
namespace eastl {
struct prime_rehash_policy_s005f_d260 {
  float mfMaxLoadFactor;
  float mfGrowthFactor;
  uint32_t mnNextResize;
  RehashResult GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd);
};
}
namespace eastl {
template <typename Value, typename KeyT, typename Hash, typename Equal = equal_to_s005f_d260>
class hashtable_s005f_d260 {
 public:
  typedef hash_node_s005f_d260<Value> node_type;
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
  prime_rehash_policy_s005f_d260 mRehashPolicy;
  allocator_s005f_d260 mAllocator;

  hashtable_s005f_d260() : mpBucketArray((node_type**)&gEmptyBucketArray), mnBucketCount(1), mnElementCount(0) {
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
  pair_s005f_d260<iterator, iterator> equal_range(const KeyT& k);
  uint32_t erase(const KeyT& k);
  iterator erase(const_iterator i);
  void DoFreeNodes(node_type** pBucketArray, uint32_t n);
  void clear() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
  }
  ~hashtable_s005f_d260() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1) mAllocator.deallocate(mpBucketArray);
  }
};
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
typename hashtable_s005f_d260<V, K, H, E>::iterator hashtable_s005f_d260<V, K, H, E>::find(const K& k) {
  const uint32_t n = mHash(k) % mnBucketCount;
  node_type* const pNode = DoFindNode(mpBucketArray[n], k);
  return pNode ? iterator(pNode, mpBucketArray + n) : iterator(mpBucketArray + mnBucketCount);
}
}
namespace eastl {
template <typename V, typename K, typename H, typename E>
pair_s005f_d260<typename hashtable_s005f_d260<V, K, H, E>::iterator, typename hashtable_s005f_d260<V, K, H, E>::iterator>
hashtable_s005f_d260<V, K, H, E>::equal_range(const K& k) {
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
    return pair_s005f_d260<iterator, iterator>(first, last);
  }
  return pair_s005f_d260<iterator, iterator>(iterator(mpBucketArray + mnBucketCount), iterator(mpBucketArray + mnBucketCount));
}
}
namespace eastl {
typedef pair_s005f_d260<string16_s005f_d260, Key_s005f_d260> NameKeyPair_s005f_d260;
}
namespace eastl {
typedef pair_s005f_d260<Key_s005f_d260, string16_s005f_d260> KeyNamePair_s005f_d260;
}
namespace eastl {
typedef hashtable_s005f_d260<NameKeyPair_s005f_d260, string16_s005f_d260, hash_s005f_d260, equal_to_s005f_d260> NameKeyMap_s005f_d260;
}
namespace eastl {
typedef hashtable_s005f_d260<KeyNamePair_s005f_d260, Key_s005f_d260, EA::ResourceMan::KeyHash_s005f_d260> KeyNameMap_s005f_d260;
}
namespace SP {
namespace Thumbnail {
struct AssetGUID_s005f_d260 {
  uint32_t mnMachineID;
  uint32_t mnAssetGroup;
  uint32_t mnAssetInstance;
};
}
}
namespace SP {
namespace Thumbnail {
bool operator==(const AssetGUID_s005f_d260& a, const AssetGUID_s005f_d260& b);
}
}
namespace SP {
namespace Thumbnail {
struct AssetGUIDHash_s005f_d260 {
  uint32_t operator()(const AssetGUID_s005f_d260& g) const;
};
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s005f_d260<AssetGUID_s005f_d260, Key_s005f_d260> GuidKeyPair_s005f_d260;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::pair_s005f_d260<Key_s005f_d260, AssetGUID_s005f_d260> KeyGuidPair_s005f_d260;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s005f_d260<GuidKeyPair_s005f_d260, AssetGUID_s005f_d260, AssetGUIDHash_s005f_d260> GuidKeyMap_s005f_d260;
}
}
namespace SP {
namespace Thumbnail {
typedef eastl::hashtable_s005f_d260<KeyGuidPair_s005f_d260, Key_s005f_d260, EA::ResourceMan::KeyHash_s005f_d260> KeyGuidMap_s005f_d260;
}
}
struct VecHandle { void* mpBegin; uint32_t a; uint32_t b; uint32_t c; uint32_t d; };
void __stdcall FUN_005fd260(void* p, VecHandle* out);      // 0x005fd260
struct HandlerStub {
  bool Handler(uint32_t id, void* p);
};
// ---- items of slice s005fd260 end

// @ 0x005f9310
void SP::Thumbnail::cImportExport::SetupExportFolderPath()
{}






// @ 0x005f9450
namespace eastl {
basic_string_s005f_8fe0<char>* basic_string_s005f_8fe0<char>::append_sprintf(const char* fmt, ...)
{
  append_sprintf_va_list(fmt, (va_list*)(&fmt + 1));
  return this;
}
}  // namespace eastl






// @ 0x005f9470
void FUN_005f9470()
{}






// @ 0x005f95a0
void FUN_005f95a0()
{}






// @ 0x005f9680
void FUN_005f9680()
{}






// @ 0x005f96c0
void FUN_005f96c0()
{}






// @ 0x005f9760
void FUN_005f9760()
{}






// @ 0x005f97c0
void FUN_005f97c0()
{}





// @ 0x005f9920
bool SP::Thumbnail::cImportExport_s005f_9920::WriteAssetDataToImage(cAssetMetadata_s005f_9920* meta, void* a, int b)
{
  Str8 s;
  Str8 t;
  IRequest* req = new ("Thumbnail_cImportExport", 0, 0, 0, 0) IRequest(0, 0, "UTF/MemoryStream");
  if (req)
    req->AddRef();
  req->SetProperty(1, 1.0f);
  req->SetProperty(2, 2.0f);
  req->Start(0, 0);
  IWriter* w = new ("Thumbnail_cImportExport", 0, 0, 0, 0) IWriter(0, -1);
  if (w)
    w->AddRef();
  bool result;
  bool ok = w->Attach(req, -1);
  if (!ok) {
    result = false;
    goto done;
  }
  ok = w->Write("spore", 5);
  StrSprintf(&s, "%04d", 6);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  StrSprintf(&s, "%08x", meta->GetKey()->b);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  StrSprintf(&s, "%08x", meta->GetKey()->c);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  StrSprintf(&s, "%08x", meta->GetKey()->a);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  StrSprintf(&s, "%08x", mField44);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  {
    unsigned long long* pa = meta->GetA();
    StrSprintf(&s, "%016llx", *pa);
    ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  }
  {
    unsigned long long parent = (unsigned long long)-1;
    unsigned long long server = (unsigned long long)-1;
    SP::Pollen::GetParentServerID(meta, &parent, &server);
    StrSprintf(&s, "%016llx", parent);
    ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  }
  {
    unsigned long long* pb = meta->GetB();
    StrSprintf(&s, "%016llx", *pb);
    ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  }
  StrSprintf(&t, "%ls", meta->GetNameW());
  StrSprintf(&s, "%02x", t.mpEnd - t.mpBegin);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin) && w->Write(t.mpBegin, t.mpEnd - t.mpBegin);
  StrSprintf(&s, "%016llx", meta->GetAssetKey());
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
  StrSprintf(&t, "%ls", meta->GetNameW2());
  StrSprintf(&s, "%02x", t.mpEnd - t.mpBegin);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin) && w->Write(t.mpBegin, t.mpEnd - t.mpBegin);
  StrSprintf(&t, "%ls", meta->GetNameW3());
  StrSprintf(&s, "%03x", t.mpEnd - t.mpBegin);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin) && w->Write(t.mpBegin, t.mpEnd - t.mpBegin);
  {
    unsigned n = meta->GetYCount();
    if (n != 0) {
      StrSprintf(&t, "%ls", meta->GetY(0));
      for (unsigned i = 1; i < n; i++)
        StrAppendSprintf(&t, ", %ls", meta->GetY(i));
    } else if (t.mpBegin != t.mpEnd) {
      *t.mpBegin = 0;
      t.mpEnd = t.mpBegin;
    }
  }
  StrSprintf(&s, "%02x", t.mpEnd - t.mpBegin);
  ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin) && w->Write(t.mpBegin, t.mpEnd - t.mpBegin);
  {
    unsigned zc = meta->GetZCount();
    StrSprintf(&s, "%02x", zc);
    ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
    unsigned i = 0;
    if (ok) {
      do {
        if (i >= zc)
          break;
        StrSprintf(&s, "%08x", meta->GetZ(i));
        ok = ok && w->Write(s.mpBegin, s.mpEnd - s.mpBegin);
        i++;
      } while (ok);
    }
  }
  {
    IMgr* mgr = GetManager();
    IRes* res = mgr->Lookup(meta->GetKey()->b, -1);
    if (ok && res) {
      IObj* obj = new ("Thumbnail_cImportExport", 0, 0, 0, 0) IObj(0, w, meta->GetKey(), 0, 0);
      if (obj)
        obj->AddRef();
      ok = res->Place(a, obj, 0, obj->GetInfo()->b) != 0;
      obj->Release();
    } else {
      ok = false;
    }
  }
  if (w->IsOk() && ok) {
    result = true;
    if (!mLock.H3(b))
      goto done;
    int sz = req->GetSize();
    if (mLock.H(req->Describe(sz)) && mLock.H2(1)) {
      result = true;
      goto done;
    }
  }
  result = false;
done:
  w->Release();
  req->Release();
  return result;
}





// @ 0x005fa100
unsigned StrTable::erase(const WStr* key)
{
  unsigned h = 0x811c9dc5;
  const unsigned short* p = (const unsigned short*)key->mpBegin;
  unsigned c = *p;
  while (c) {
    h = (h * 0x1000193) ^ c;
    p++;
    c = *p;
  }
  StrNode** pp = &mBuckets[h % mBucketCount];
  int before = mSize;
  if (*pp) {
    do {
      StrNode* n = *pp;
      if (Str16Equal(key, n))
        break;
      pp = &n->next;
    } while (*pp);
    while (*pp) {
      StrNode* n = *pp;
      if (!Str16Equal(key, n))
        break;
      *pp = n->next;
      if ((n->key.mpCapacity - n->key.mpBegin) > 1 && n->key.mpBegin)
        EA_Deallocate(n->key.mpBegin);
      EA_Deallocate(n);
      mSize--;
    }
  }
  return before - mSize;
}





// @ 0x005fa1d0
void __stdcall ClearBucketsA(int** buckets, unsigned count)
{
  for (unsigned i = 0; i < count; i++) {
    int* p = buckets[i];
    while (p) {
      int* cur = p;
      int* next = (int*)p[7];
      int s0 = cur[0];
      int d = (cur[2] - cur[0]) & 0xfffffffe;
      if (d > 2 && s0 != 0)
        EA_Deallocate((void*)s0);
      EA_Deallocate(cur);
      p = next;
    }
    buckets[i] = 0;
  }
}





// @ 0x005fa230
void __stdcall ClearBucketsB(int** buckets, unsigned count)
{
  for (unsigned i = 0; i < count; i++) {
    int* p = buckets[i];
    while (p) {
      int* next = (int*)p[7];
      int* cur = p;
      int s3 = cur[3];
      int d = (cur[5] - cur[3]) & 0xfffffffe;
      if (d > 2 && s3 != 0)
        EA_Deallocate((void*)s3);
      EA_Deallocate(cur);
      p = next;
    }
    buckets[i] = 0;
  }
}





// @ 0x005fa290
bool SP::Thumbnail::cImportExport_s005f_9920::RestoreImportTable()
{
  ISaveArea* save = GetSaveArea(0x11ac19d);
  if (!save)
    return false;
  IStream* stream = 0;
  if (!save->Open((void*)0x151c9e0, 0, 1, 6, 1, 0)) {
    if (stream)
      stream->Release();
    return true;
  }
  if (stream) {
    IStream* t = stream;
    stream = 0;
    t->Release();
  }
  if (!save->Open((void*)0x151c9e0, &stream, 1, 3, 1, 0)) {
    if (stream)
      stream->Release();
    return true;
  }
  IReader* r = (IReader*)stream->GetReader();
  unsigned version, count, len;
  bool ok;
  if (r->Read(&version, 4) && version <= 3 && r->Read(&count, 4))
    ok = true;
  else
    ok = false;
  WStr str;
  if (ok) {
    while (count-- != 0) {
      bool got;
      if (ok && r->Read(&len, 4)) {
        str.resize(len);
        got = r->Read(str.mpBegin, len * 2) != 0;
      } else {
        got = false;
      }
      Key3 k;
      k.a = 0;
      k.b = 0;
      k.c = 0;
      if (!got || !r->Read(&k.b, 4) || !r->Read(&k.c, 4) || !r->Read(&k.a, 4)) {
        ok = false;
        break;
      }
      ok = true;
      if (version < 3) {
        WStr tmp;
        ResolveName(k.b, &tmp);
        PathBuf pb;
        pb.AssignW(tmp.mpBegin);
        pb.SetName(str.mpBegin, 0);
        const wchar_t* p = pb.c_str();
        const wchar_t* e = p;
        while (*e)
          e++;
        str.assign(p, e);
        FixPath(&str);
      }
      {
        PairWK pa(WStr(str), Key3(k.a, k.b, k.c));
        ValueWK va(pa);
        IterBool ib;
        mWK.Insert(&ib, va, false);
      }
      {
        PairKW pb2(Key3(k.a, k.b, k.c), WStr(str));
        ValueKW vb(pb2);
        IterBool ib;
        mKW.Insert(&ib, vb, false);
      }
    }
  }
  if (version >= 2) {
    if (!ok || !r->Read(&count, 4)) {
      ok = false;
    } else {
      ok = true;
      while (count-- != 0) {
        Key3 k;
        k.a = 0;
        k.b = 0;
        k.c = 0;
        Key3 y;
        if (!r->Read(&k.b, 4) || !r->Read(&k.c, 4) || !r->Read(&k.a, 4) ||
            !r->Read(&y.a, 4) || !r->Read(&y.b, 4) || !r->Read(&y.c, 4)) {
          ok = false;
          break;
        }
        {
          PairKK p1(y, k);
          IterBool ib;
          mKK.Insert(&ib, p1, false);
        }
        {
          PairKK p2(k, y);
          IterBool ib;
          mKK2.Insert(&ib, p2, false);
        }
        ok = true;
      }
    }
  }
  stream->Close();
  if (stream)
    stream->Release();
  return ok;
}




// @ 0x005fa8d0
bool SP::Thumbnail::cImportExport_s005f_a8d0::CreateExportThumb(void* pImage, const Key_s005f_a8d0& key, void* pInfo)
{
  if (!pInfo) return false;
  // Reconstructed (behavioural) form; the exact inner sprite/file pipeline is not reproduced.
  return false;
}




// @ 0x005face0
namespace eastl {
template <typename V, typename K, typename H, typename E> uint32_t hashtable_s005f_a8d0<V, K, H, E>::erase(const K& k)
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




// @ 0x005fae40
bool SP::Thumbnail::cImportExport_s005f_a8d0::Shutdown()
{
  GetMessageServer()->vt2c(this, 0x24ce123, 0xffffd8f1);
  mNameToKeyMap.clear();
  mKeyToNameMap.clear();
  mGuidToKeyMap.clear();
  mKeyToGuidMap.clear();
  return true;
}




// @ 0x005faec0
bool SP::Thumbnail::cImportExport_s005f_a8d0::RemoveExportThumb(const Key_s005f_a8d0& key)
{
  eastl::KeyNameMap::iterator it = mKeyToNameMap.equal_range(key).first;
  if (it != mKeyToNameMap.end()) {
    eastl::string16_s005f_a8d0 name = it.mpNode->mValue.second;
    EA::IO::File::Remove(name.c_str());
    mNameToKeyMap.erase(name);
    mKeyToNameMap.erase(it);
    Save();
  }
  return true;
}




// @ 0x005fafb0
bool SP::Thumbnail::cImportExport_s005f_a8d0::ImportFromFolder(const Key_s005f_a8d0& key, void* pArg)
{
  // Reconstructed (behavioural) form of the folder scanning loop.
  (void)key;
  (void)pArg;
  return false;
}




// @ 0x005fb350
cImportInfo& cImportInfo::operator=(const cImportInfo& o)
{
  mKey0 = o.mKey0;
  mKey4 = o.mKey4;
  mKey8 = o.mKey8;
  m10 = o.m10; m14 = o.m14; m18 = o.m18; m1c = o.m1c; m20 = o.m20; m24 = o.m24;
  mName = o.mName;
  m38 = o.m38; m3c = o.m3c;
  mDisplayName = o.mDisplayName;
  mDescription = o.mDescription;
  mPath = o.mPath;
  mIDs = o.mIDs;
  m84 = o.m84; m88 = o.m88; m8c = o.m8c;
  return *this;
}



// @ 0x005fb430
unsigned char cImportExportRetail::UpdateExportThumb(void* param_2)
{
  // Reconstructed (behavioural) form of the multi-step image-update routine.
  (void)param_2;
  return 0;
}



// @ 0x005fb900
cImportExportRetail::~cImportExportRetail()
{}


// @ 0x005fc330
bool cImportExportCtor::ImportNewAsset(const wchar_t* path, Key_s005f_c330* pOut)
{
  pOut->instanceID = (uint32_t)-1;
  pOut->typeID = (uint32_t)-1;
  pOut->groupID = (uint32_t)-1;
  bool bResult = false;
  IN::FileStream stream(path);
  stream.AddRef();
  if (stream.Open(1, 3, 1, 0)) {
    IN::PollenModule* pollen = IN::GetPollenModule();
    IN::ImpInfo info;
    IN::IRefObj* pObj = 0;
    bResult = CreateKey(&stream, &info, &pObj);
    stream.Close();
    SP::Thumbnail::AssetGUID_s005f_c330 guid = info.guid;
    IN::GuidMapX* gm = (IN::GuidMapX*)&mGuidToKeyMap;
    IN::GuidMapX::iterator it = gm->find(guid);
    if (it.mpNode != gm->mpBucketArray[gm->mnBucketCount]) {
      pOut->instanceID = it.mpNode->mValue.second.instanceID;
      pOut->typeID = it.mpNode->mValue.second.typeID;
      pOut->groupID = it.mpNode->mValue.second.groupID;
      if (pObj) pObj->Release();
      return false;
    }
    Key_s005f_c330 found = {0, 0, 0};
    if (pollen->mpAssetDir->GetLocalKey(info.assetId, &found)) {
      IN::IKeyLookup* kl = IN::GetKeyLookup();
      if (kl->Lookup(&found)) {
        *pOut = found;
        if (pObj) pObj->Release();
        return false;
      }
    }
    if (bResult) {
      Key_s005f_c330 newKey = {0, 0, 0};
      IN::GetIDGenerator()->Generate(&newKey, info.idA, info.idB);
      IN::AssetMeta* pMeta = new ("Thumbnail_cImportExport", 0, 0, 0, 0) IN::AssetMeta();
      if (pMeta) pMeta->AddRef();
      pMeta->SetMetadata(&newKey, info.assetId, info.timeCreated, info.name.b, info.authorId,
                         info.authorName.b, info.desc.b, info.tags.b, "tag:spore.com,2006:ImportedContent", true);
      pMeta->SetParentAssetID(info.parentId);
      if (info.guid.mnMachineID == mnMachineID) pMeta->SetFlag(true);
      for (uint32_t* p = info.idsBegin; p != info.idsEnd; ++p) pMeta->AddTrait(*p);
      IN::IRecordS* pStreamRec = 0;
      IN::Database* saveArea = IN::GetSaveArea(0x11ac19d);
      IN::IResourceFactory* factory = IN::GetManager_s005f_c330()->FindFactory(newKey.typeID, (uint32_t)-1);
      if (!factory) {
        bResult = false;
      } else {
        IN::ResObjS* pDst = 0;
        IN::IRecordS* rec = new ("Thumbnail_cImportExport", 0, 0, 0, 0) IN::MemRecord(0, pObj, &newKey, 0, 0);
        if (rec) rec->AddRef();
        if (pDst) { IN::ResObjS* t = pDst; pDst = 0; t->Release(); }
        if (!factory->CreateResource(rec, &pDst, 0, newKey.typeID)) {
          bResult = false;
        } else {
          pDst->key = newKey;
          IN::FUN_006ad010(pDst);
          bResult = IN::GetManager_s005f_c330()->WriteResource(pDst, 0, saveArea, 0, 0);
          IN::FUN_006ac0a0(2, pDst);
          IN::FUN_006ad010(pMeta);
          bResult = bResult && IN::GetManager_s005f_c330()->WriteResource(pMeta, 0, saveArea, 0, 0);
          IN::FUN_006ac0a0(2, pMeta);
          Key_s005f_c330 imgKey = newKey;
          imgKey.typeID = 0x2f7d0004;
          if (!bResult) {
            bResult = false;
          } else {
            if (pStreamRec) { IN::IRecordS* t = pStreamRec; pStreamRec = 0; t->Release(); }
            if (!saveArea->OpenRecord(&imgKey, &pStreamRec, 2, 6, 1, 0)) {
              bResult = false;
            } else {
              bResult = true;
              mEmbed.Serialize(pStreamRec->GetStream(), 0);
              pStreamRec->RecordClose();
            }
          }
        }
        if (rec) rec->Release();
        if (pDst) pDst->Release();
        if (bResult) {
          *pOut = newKey;
          xf8 = newKey.instanceID;
          xfc = newKey.typeID;
          x100 = newKey.groupID;
          if (info.assetId != (uint64_t)-1) {
            IN::AssetDirectory* dir = pollen->mpAssetDir;
            if (dir->GetLocalKey(info.assetId, 0)) dir->RemoveMapping(info.assetId, 1);
            dir->AddMapping(info.assetId, &newKey);
          }
          SP::Thumbnail::GuidKeyPair_s005f_c330 gp(info.guid, *pOut);
          gm->DoInsertValue(gp, eastl::true_type());
          IN::KeyGuidMapX* kgm = (IN::KeyGuidMapX*)&mKeyToGuidMap;
          SP::Thumbnail::KeyGuidPair_s005f_c330 kp(*pOut, info.guid);
          kgm->DoInsertValue(kp, eastl::true_type());
          IN::GetMessageServer()->Post(0x5132ed1, &newKey, 0);
        }
      }
      if (pStreamRec) pStreamRec->Release();
      if (pMeta) pMeta->Release();
    }
    if (pObj) pObj->Release();
  }
  return bResult;
}


// @ 0x005fc9f0
bool cImportExportCtor::ScanFolder(const void* a, void* b, void* c)
{
  (void)a;
  (void)b;
  (void)c;
  return false;
}


// @ 0x005fcf40
cImportExportCtor::cImportExportCtor()
{}


// @ 0x005fd0a0
unsigned char cImportExportCtor::ScanForImports()
{
  // Reconstructed (behavioural) skeleton: scans the eight folder paths.
  return 0;
}

// @ 0x005fd260
void FUN_005fd260()
{
}

// @ 0x005fd880
void FUN_005fd880()
{
}

// @ 0x005fda40
bool HandlerStub::Handler(uint32_t id, void* p)
{
  if (id == 0x24ce123 && p) {
    VecHandle v;
    VecHandle* pv = &v;
    v.mpBegin = 0; v.a = 0; v.b = 0;
    FUN_005fd260(p, pv);
    if (v.mpBegin && ((int*)v.mpBegin)[-1]) operator delete(v.mpBegin);
  }
  return true;
}
