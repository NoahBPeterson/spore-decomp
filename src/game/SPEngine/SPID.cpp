// src/game/SPEngine/SPID.cpp -- migrated from slice(s) s0068c330, s005f7da0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPID.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include "EA/ResourceMan/Key.h"

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
// ---- items of slice s005f7da0 end

// ---- items of slice s0068c330 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int   __cdecl iswctype(unsigned short c, unsigned t);
extern "C" __declspec(dllimport) int   __cdecl isdigit(int c);
extern "C" __declspec(dllimport) int   __cdecl isxdigit(int c);
extern "C" __declspec(dllimport) unsigned long __cdecl strtoul(const char* s, char** e, int base);
typedef unsigned int   uint32;
typedef unsigned char  uint8;
extern "C" __declspec(dllimport) char* __cdecl strchr_s0068_c330(const char* s, int c);
extern "C" __declspec(dllimport) void* __cdecl memchr_s0068_c330(const void* s, int c, unsigned n);
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

    PackStr* InsertCStr(uint32 id, const char* s);
    void __declspec(noinline) Insert(char* pos, const char* first, const char* last);  // 0x0068C9E0
};
void SPNameFromKeyW(const ResKey* key, void* out, const wchar_t* name);
void SPNameFromKeyA(const ResKey* key, void* out, const char* name);
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mAllocator;

    void Insert(wchar_t* pos, const wchar_t* first, const wchar_t* last); // 0x005F7DA0
};
void* FUN_0068C680(const char* s, unsigned n);          // Resource::HashNameN
void  FUN_0068D0B0(void* out, const void* tpl, const char* s); // fixed wstring ctor
// ---- items of slice s0068c330 end

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
    // EASTL string insert; body approximated (scratch only).
    (void)pos;
    (void)first;
    (void)last;
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
void PackStrSwap(PackStr* a, PackStr* b)
{
    if ((char*)a + 0xc == (char*)b + 0xc) {
        char* pa = (char*)a;
        char* pb = (char*)b;
        for (int i = 0; i < 3; ++i) {
            void* t = *(void**)(pa + i * 4);
            *(void**)(pa + i * 4) = *(void**)(pb + i * 4);
            *(void**)(pb + i * 4) = t;
        }
        return;
    }
    // Non-SSO swap uses a temp copy + assign; approximated.
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
    if (start == dot) {
        key->mInstance = 0xffffffff;
    } else {
        const char* hexs = GetExplicitIdStartA((char*)start, (char*)dot, 1, 1);
        if (hexs == 0)
            key->mInstance = (uint32)FUN_0068C680(name, (unsigned)(dot - name));
        else
            key->mInstance = (uint32)strtoul(hexs, 0, 16);
    }
    if (name != bang) {
        const char* p = bang;
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
            const char* us = FindLastCharA((char*)name, (char*)bang, "_");
            const char* s2 = name;
            if (us != 0)
                s2 = us + 1;
            const char* hexs = GetExplicitIdStartA((char*)s2, (char*)bang, 0, 0);
            if (hexs == 0) {
                key->mGroup = (uint32)FUN_0068C680(name, (unsigned)(bang - name));
                // cache the group name string
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
