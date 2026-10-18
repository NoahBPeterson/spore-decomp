// src/game/SPEditors/SPNameGenerator.cpp -- migrated from slice(s) s005ec030, s005eb160, s005ea3d0, s005e9440 by tools/migrate/rewrite.py
// Object file: SPEditors/SPNameGenerator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380
#include <string.h>
#include <new>
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cDirectPropertyList.h"
#include "EA/Variant.h"
#include "SP/cSPNameGenerator.h"

// ---- items of slice s005e9440 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380
void* operator new[](unsigned int n, const char* name, int flags, unsigned int debugFlags,
                     const char* file, int line);  // 0x00f473a0
namespace eastl {
struct true_type {};
}
namespace eastl {
struct iterator_tag { iterator_tag() {} };
}
namespace eastl {
struct allocator_s005e_9440 {
  allocator_s005e_9440() {}
  allocator_s005e_9440(const allocator_s005e_9440&) {}
  void* allocate(size_t n) {
    return operator new[](n, "Editor", 0, 0, "c:\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  }
  void deallocate(void* p) { EASTL_allocator_deallocate(p); }
};
}
namespace eastl {
struct sp_vector_allocator_s005e_9440 {
  sp_vector_allocator_s005e_9440() {}
  void* allocate(size_t n) {
    return operator new[](n, "Editor", 0, 0, "c:\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  }
  void deallocate(void* p) {
    if (p && ((int*)p)[-1] != 0) EASTL_allocator_deallocate(p);
  }
};
}
namespace eastl {
template <typename T> inline const T& min_alt(const T& a, const T& b) { return (b < a) ? b : a; }
}
namespace eastl {
inline int Compare(const wchar_t* p1, const wchar_t* p2, size_t n) {
  for (; n > 0; ++p1, ++p2, --n) {
    if (*p1 != *p2) return (*p1 < *p2) ? -1 : 1;
  }
  return 0;
}
}
namespace eastl {
template <typename T, typename A = allocator_s005e_9440>
class basic_string_s005e_9440 {
 public:
  typedef T value_type;
  typedef size_t size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;
  basic_string_s005e_9440(const basic_string_s005e_9440& x) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(x.mAllocator) {
    RangeInitialize(x.mpBegin, x.mpEnd);
  }
  basic_string_s005e_9440(const T* p, size_type n, const A& a = A()) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {
    RangeInitialize(p, p + n);
  }
  ~basic_string_s005e_9440() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin) EASTL_allocator_deallocate(mpBegin);
  }
  basic_string_s005e_9440& operator=(const basic_string_s005e_9440& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  basic_string_s005e_9440& assign(const T* pBegin, const T* pEnd);  // 0x00423650
  void AllocateSelf(size_type n);  // 0x00475ab0
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
  static int compare(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2) {
    const ptrdiff_t n1 = pEnd1 - pBegin1;
    const ptrdiff_t n2 = pEnd2 - pBegin2;
    const ptrdiff_t nMin = eastl::min_alt(n1, n2);
    const int cmp = Compare(pBegin1, pBegin2, (size_t)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
  }
};
}
namespace eastl {
typedef basic_string_s005e_9440<wchar_t> wstring;
}
namespace eastl {
template <typename T, typename A>
inline bool operator<(const basic_string_s005e_9440<T, A>& a, const basic_string_s005e_9440<T, A>& b) {
  return basic_string_s005e_9440<T, A>::compare(a.mpBegin, a.mpEnd, b.mpBegin, b.mpEnd) < 0;
}
}
namespace eastl {
template <typename T> struct less_s005e_9440 {
  bool operator()(const T& a, const T& b) const { return a < b; }
};
}
namespace eastl {
template <typename T> struct use_self_s005e_9440 {
  const T& operator()(const T& x) const { return x; }
};
}
namespace eastl {
template <typename P> struct use_first_s005e_9440 {
  const typename P::first_type& operator()(const P& x) const { return x.first; }
};
}
namespace eastl {
template <typename T1, typename T2> struct pair_s005e_9440 {
  typedef T1 first_type;
  T1 first;
  T2 second;
  pair_s005e_9440(const T1& a, const T2& b) : first(a), second(b) {}
};
}
namespace eastl {
template <typename It> struct generic_iterator {
  It mIterator;
  generic_iterator() : mIterator(0) {}
  explicit generic_iterator(It p) : mIterator(p) {}
  It base() const { return mIterator; }
};
}
namespace eastl {
template <typename T>
generic_iterator<T*> uninitialized_copy_impl(generic_iterator<T*> first, generic_iterator<T*> last,
                                             generic_iterator<T*> dest, iterator_tag);  // 0x0054b510
}
namespace eastl {
template <typename T> inline T* uninitialized_copy_ptr(T* first, T* last, T* result) {
  const generic_iterator<T*> i(uninitialized_copy_impl(generic_iterator<T*>(first), generic_iterator<T*>(last),
                                                       generic_iterator<T*>(result), iterator_tag()));
  return i.base();
}
}
namespace eastl {
template <typename T> T* uninitialized_relocate_start(T* first, T* last, T* dest);  // 0x0054b400
}
namespace eastl {
template <typename T> T* uninitialized_relocate_commit(T* first, T* last, T* dest) {
  for (; first != last; ++first, ++dest) first->~T();
  return dest;
}
}
namespace eastl {
template <typename T> inline T* uninitialized_relocate_ptr(T* first, T* last, T* dest) {
  T* result = uninitialized_relocate_start(first, last, dest);
  eastl::uninitialized_relocate_commit(first, last, dest);
  return result;
}
}
namespace eastl {
template <typename T> inline T* copy_backward_trivial(const T* first, const T* last, T* result) {
  return (T*)memmove(result - (last - first), first, (size_t)((uintptr_t)last - (uintptr_t)first));
}
}
namespace eastl {
template <typename T> inline T* uninitialized_copy_trivial(const T* first, const T* last, T* result) {
  return (T*)memcpy(result, first, (size_t)((uintptr_t)last - (uintptr_t)first)) + (last - first);
}
}
namespace eastl {
template <typename BI1, typename BI2> BI2 copy_backward(BI1 first, BI1 last, BI2 resultEnd) {
  while (last != first) *--resultEnd = *--last;
  return resultEnd;
}
}
namespace eastl {
template <typename T> T* copy(T* first, T* last, T* result);  // 0x0084ab40
}
namespace eastl {
template <typename T, typename A = sp_vector_allocator_s005e_9440>
class vector_s005e_9440 {
 public:
  typedef T* iterator;
  typedef size_t size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;
  T* DoAllocate(size_type n) { return n ? (T*)mAllocator.allocate(n * sizeof(T)) : 0; }
  void DoFree(T* p, size_type) { mAllocator.deallocate(p); }
  size_type GetNewCapacity(size_type currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
  explicit vector_s005e_9440(size_type n, const A& a = A());
  ~vector_s005e_9440() {
    for (T* p = mpBegin; p < mpEnd; ++p) p->~T();
    DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
  }
  void DoInsertValue(iterator position, const T& value);
  void DoInsertFromIterator(iterator position, const T* first, const T* last, iterator_tag);
};
}
namespace eastl {
template <typename T, typename A>
vector_s005e_9440<T, A>::vector_s005e_9440(size_type n, const A& a) : mAllocator(a) {
  mpBegin = DoAllocate(n);
  mpEnd = mpBegin;
  mpCapacity = mpBegin + n;
  if (n > 0) memset(mpBegin, 0, n);
  mpEnd = mpBegin + n;
}
}
namespace eastl {
template <typename T, typename A>
void vector_s005e_9440<T, A>::DoInsertValue(iterator position, const T& value) {
  if (mpEnd != mpCapacity) {
    const T* pValue = &value;
    if ((pValue >= position) && (pValue < mpEnd)) ++pValue;
    ::new (mpEnd) T(*(mpEnd - 1));
    eastl::copy_backward_trivial(position, mpEnd - 1, mpEnd);
    *position = *pValue;
    ++mpEnd;
  } else {
    const size_type nPosSize = size_type(position - mpBegin);
    const size_type nPrevSize = size_type(mpEnd - mpBegin);
    const size_type nNewSize = nPrevSize ? (2 * nPrevSize) : 1;
    T* const pNewData = DoAllocate(nNewSize);
    T* pNewEnd = eastl::uninitialized_copy_trivial(mpBegin, position, pNewData);
    ::new (pNewEnd) T(value);
    pNewEnd = eastl::uninitialized_copy_trivial(position, mpEnd, ++pNewEnd);
    DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
    mpBegin = pNewData;
    mpEnd = pNewEnd;
    mpCapacity = pNewData + nNewSize;
  }
}
}
namespace eastl {
template <typename T, typename A>
void vector_s005e_9440<T, A>::DoInsertFromIterator(iterator position, const T* first, const T* last, iterator_tag) {
  if (first != last) {
    const size_type n = (size_type)(last - first);
    if (n <= size_type(mpCapacity - mpEnd)) {
      const size_type nExtra = static_cast<size_type>(mpEnd - position);
      T* const pEnd = mpEnd;
      if (n < nExtra) {
        eastl::uninitialized_copy_ptr(mpEnd - n, mpEnd, mpEnd);
        mpEnd += n;
        eastl::copy_backward(position, pEnd - n, pEnd);
        eastl::copy((T*)first, (T*)last, position);
      } else {
        T* iTemp = (T*)first + nExtra;
        eastl::uninitialized_copy_ptr(iTemp, (T*)last, mpEnd);
        mpEnd += n - nExtra;
        eastl::uninitialized_copy_ptr(position, pEnd, mpEnd);
        mpEnd += nExtra;
        eastl::copy_backward((T*)first, iTemp, position + nExtra);
      }
    } else {
      const size_type nPrevSize = size_type(mpEnd - mpBegin);
      const size_type nGrowSize = GetNewCapacity(nPrevSize);
      const size_type nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
      T* const pNewData = DoAllocate(nNewSize);
      T* pNewEnd = eastl::uninitialized_relocate_ptr(mpBegin, position, pNewData);
      pNewEnd = eastl::uninitialized_copy_ptr((T*)first, (T*)last, pNewEnd);
      pNewEnd = eastl::uninitialized_relocate_ptr(position, mpEnd, pNewEnd);
      DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
      mpBegin = pNewData;
      mpEnd = pNewEnd;
      mpCapacity = pNewData + nNewSize;
    }
  }
}
}
namespace eastl {
struct rbtree_node_base_s005e_9440 {
  rbtree_node_base_s005e_9440* mpNodeRight;
  rbtree_node_base_s005e_9440* mpNodeLeft;
  rbtree_node_base_s005e_9440* mpNodeParent;
  char mColor;
};
}
namespace eastl {
enum RBTreeSide { kRBTreeSideLeft, kRBTreeSideRight };
}
eastl::rbtree_node_base_s005e_9440* RBTreeIncrement(const eastl::rbtree_node_base_s005e_9440* pNode);  // 0x00921580
eastl::rbtree_node_base_s005e_9440* RBTreeDecrement(const eastl::rbtree_node_base_s005e_9440* pNode);  // 0x009215c0
void RBTreeInsert(eastl::rbtree_node_base_s005e_9440* pNode, eastl::rbtree_node_base_s005e_9440* pNodeParent,
                  eastl::rbtree_node_base_s005e_9440* pNodeAnchor, eastl::RBTreeSide insertionSide);  // 0x009216a0
namespace eastl {
template <typename V> struct rbtree_node_s005e_9440 : public rbtree_node_base_s005e_9440 { V mValue; };
}
namespace eastl {
template <typename V> struct rbtree_iterator_s005e_9440 {
  rbtree_node_s005e_9440<V>* mpNode;
  rbtree_iterator_s005e_9440() : mpNode(0) {}
  explicit rbtree_iterator_s005e_9440(const rbtree_node_s005e_9440<V>* p) : mpNode((rbtree_node_s005e_9440<V>*)p) {}
  rbtree_iterator_s005e_9440(const rbtree_iterator_s005e_9440& x) : mpNode(x.mpNode) {}
  rbtree_iterator_s005e_9440& operator++() {
    mpNode = (rbtree_node_s005e_9440<V>*)RBTreeIncrement(mpNode);
    return *this;
  }
};
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
class rbtree_s005e_9440 {
 public:
  typedef rbtree_node_s005e_9440<V> node_type;
  typedef rbtree_iterator_s005e_9440<V> iterator;
  typedef V value_type;
  typedef K key_type;
  typedef E extract_key;
  C mCompare;
  rbtree_node_base_s005e_9440 mAnchor;
  size_t mnSize;
  allocator_s005e_9440 mAllocator;

  iterator end() { return iterator((node_type*)&mAnchor); }
  node_type* DoAllocateNode() { return (node_type*)mAllocator.allocate(sizeof(node_type)); }
  void DoFreeNode(node_type* pNode) {
    pNode->~node_type();
    mAllocator.deallocate(pNode);
  }
  node_type* DoCreateNode(const value_type& value) {
    node_type* const pNode = DoAllocateNode();
    ::new (&pNode->mValue) value_type(value);
    return pNode;
  }
  void reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  void clear() {
    DoNuke((node_type*)mAnchor.mpNodeParent);
    reset();
  }
  void DoNuke(node_type* pNode);
  iterator find(const key_type& key);
  iterator lower_bound(const key_type& key);
  iterator DoInsertValueImpl(node_type* pNodeParent, const value_type& value, bool bForceToLeft);
  pair_s005e_9440<iterator, bool> DoInsertValue(const value_type& value, true_type);
  iterator DoInsertValue(iterator position, const value_type& value, true_type);
  pair_s005e_9440<iterator, bool> insert(const value_type& value) { return DoInsertValue(value, true_type()); }
  iterator insert(iterator position, const value_type& value) { return DoInsertValue(position, value, true_type()); }
  void insert(const value_type* first, const value_type* last) {
    for (; first != last; ++first) DoInsertValue(*first, true_type());
  }
};
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
typename rbtree_s005e_9440<K, V, C, E>::iterator
rbtree_s005e_9440<K, V, C, E>::DoInsertValueImpl(node_type* pNodeParent, const value_type& value, bool bForceToLeft) {
  RBTreeSide side;
  extract_key extractKey;
  if (bForceToLeft || (pNodeParent == &mAnchor) || mCompare(extractKey(value), extractKey(pNodeParent->mValue)))
    side = kRBTreeSideLeft;
  else
    side = kRBTreeSideRight;
  node_type* const pNodeNew = DoCreateNode(value);
  RBTreeInsert(pNodeNew, pNodeParent, &mAnchor, side);
  mnSize++;
  return iterator(pNodeNew);
}
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
pair_s005e_9440<typename rbtree_s005e_9440<K, V, C, E>::iterator, bool>
rbtree_s005e_9440<K, V, C, E>::DoInsertValue(const value_type& value, true_type) {
  extract_key extractKey;
  node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
  node_type* pLowerBound = (node_type*)&mAnchor;
  node_type* pParent;
  bool bValueLessThanNode = true;
  while (pCurrent) {
    bValueLessThanNode = mCompare(extractKey(value), extractKey(pCurrent->mValue));
    pLowerBound = pCurrent;
    if (bValueLessThanNode)
      pCurrent = (node_type*)pCurrent->mpNodeLeft;
    else
      pCurrent = (node_type*)pCurrent->mpNodeRight;
  }
  pParent = pLowerBound;
  if (bValueLessThanNode) {
    if (pLowerBound != (node_type*)mAnchor.mpNodeLeft)
      pLowerBound = (node_type*)RBTreeDecrement(pLowerBound);
    else {
      const iterator itResult(DoInsertValueImpl(pLowerBound, value, false));
      return pair_s005e_9440<iterator, bool>(itResult, true);
    }
  }
  if (mCompare(extractKey(pLowerBound->mValue), extractKey(value))) {
    const iterator itResult(DoInsertValueImpl(pParent, value, false));
    return pair_s005e_9440<iterator, bool>(itResult, true);
  }
  return pair_s005e_9440<iterator, bool>(iterator(pLowerBound), false);
}
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
typename rbtree_s005e_9440<K, V, C, E>::iterator
rbtree_s005e_9440<K, V, C, E>::DoInsertValue(iterator position, const value_type& value, true_type) {
  extract_key extractKey;
  if ((position.mpNode != mAnchor.mpNodeRight) && (position.mpNode != &mAnchor)) {
    iterator itNext(position);
    ++itNext;
    const bool bPositionLessThanValue = mCompare(extractKey(position.mpNode->mValue), extractKey(value));
    if (bPositionLessThanValue) {
      const bool bValueLessThanNext = mCompare(extractKey(value), extractKey(itNext.mpNode->mValue));
      if (bValueLessThanNext) {
        if (position.mpNode->mpNodeRight) return DoInsertValueImpl(itNext.mpNode, value, true);
        return DoInsertValueImpl(position.mpNode, value, false);
      }
    }
    const pair_s005e_9440<iterator, bool> itResult(DoInsertValue(value, true_type()));
    return itResult.first;
  }
  if (mnSize && mCompare(extractKey(((node_type*)mAnchor.mpNodeRight)->mValue), extractKey(value)))
    return DoInsertValueImpl((node_type*)mAnchor.mpNodeRight, value, false);
  const pair_s005e_9440<iterator, bool> itResult(DoInsertValue(value, true_type()));
  return itResult.first;
}
}
namespace eastl {
template <typename K, typename T, typename C = less_s005e_9440<K> >
class map_s005e_9440 : public rbtree_s005e_9440<K, pair_s005e_9440<const K, T>, C, use_first_s005e_9440<pair_s005e_9440<const K, T> > > {
 public:
  typedef rbtree_s005e_9440<K, pair_s005e_9440<const K, T>, C, use_first_s005e_9440<pair_s005e_9440<const K, T> > > base_type;
  typedef typename base_type::iterator iterator;
  typedef pair_s005e_9440<const K, T> value_type;
  T& operator[](const K& key) {
    iterator itLower(this->lower_bound(key));
    if ((itLower == this->end()) || this->mCompare(key, (*itLower.mpNode).mValue.first))
      itLower = base_type::insert(itLower, value_type(key, T()));
    return itLower.mpNode->mValue.second;
  }
};
}
namespace eastl {
template <typename V> inline bool operator==(const rbtree_iterator_s005e_9440<V>& a, const rbtree_iterator_s005e_9440<V>& b) {
  return a.mpNode == b.mpNode;
}
}
namespace eastl {
template <typename K, typename C = less_s005e_9440<K> >
class set_s005e_9440 : public rbtree_s005e_9440<K, K, C, use_self_s005e_9440<K> > {
 public:
  typedef rbtree_s005e_9440<K, K, C, use_self_s005e_9440<K> > base_type;
};
}
struct Key3 { uint16_t a, b, c; };
inline bool operator<(const Key3& x, const Key3& y) {
  return (x.a < y.a) || (!(y.a < x.a) && (x.b < y.b)) || (!(y.a < x.a) && !(y.b < x.b) && (x.c < y.c));
}
struct cKeyedBuffers {
  eastl::vector_s005e_9440<uint8_t> mA;
  uint32_t mFlags;
  eastl::vector_s005e_9440<uint8_t> mB;
};
typedef eastl::set_s005e_9440<uint16_t> U16Set;
typedef eastl::map_s005e_9440<Key3, uint32_t> Key3Map;
typedef eastl::set_s005e_9440<eastl::wstring> WStringSet;
typedef eastl::map_s005e_9440<eastl::wstring, int> WStringIntMap;
typedef eastl::map_s005e_9440<uint32_t, cKeyedBuffers> BufferMap;
typedef U16Set::base_type U16Tree;
typedef Key3Map::base_type Key3Tree;
typedef WStringSet::base_type WStringTree;
typedef WStringIntMap::base_type WStringIntTree;
typedef BufferMap::base_type BufferTree;
template WStringTree::iterator WStringTree::find(const eastl::wstring&);
template WStringIntTree::iterator WStringIntTree::lower_bound(const eastl::wstring&);
template void BufferTree::DoNuke(node_type*);
// ---- items of slice s005e9440 end

// ---- items of slice s005eb160 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl tolower(int);
extern wchar_t gEmptyW[];               // 0x1667bac: shared empty-string buffer (wchar_t[2] / char[2] overlay)
typedef unsigned int uint;
typedef unsigned short ushort;
#define VSLOT(obj, idx) ((*(void***)(obj))[idx])
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void* operator new(unsigned int, const char*, int, int, const char*, int);   // 0x00f473a0
void  operator delete[](void*);   // 0x00f47380
struct WStr {
    wchar_t* b;
    wchar_t* e;
    wchar_t* c;
    int      alloc;
    WStr() { b = e = gEmptyW; c = gEmptyW + 1; }
    ~WStr() { if (((((int)c - (int)b) & ~1) > 2) && b) operator delete[](b); }
    bool empty() const { return b == e; }
    // range initialisation: allocate (len + 1) chars unless the string is empty
    void Init(const wchar_t* sb, const wchar_t* se)
    {
        b = e = c = 0;
        uint n = (uint)(se - sb) + 1;
        if (n > 1) {
            b = (wchar_t*)operator new(n * 2, "Editor", 0, 0, ALLOC_FILE, 0xd1);
            e = b;
            c = b + n;
        } else {
            b = e = gEmptyW;
            c = gEmptyW + 1;
        }
        wchar_t* d = b;
        uint bytes = (uint)(se - sb) * 2;
        memcpy(d, sb, bytes);
        e = (wchar_t*)((char*)d + bytes);
        *e = 0;
    }
    void RangeInitialize(const wchar_t* p);                     // 00579a90
    void assign(const wchar_t* sb, const wchar_t* se);          // 00423650
    void Append(const wchar_t* sb, const wchar_t* se);          // 00429580
    void rtrim();                                               // 005541e0
    void make_lower();                                          // 005e8e80
    void CopyCtor(const WStr* o);                               // 0056e2d0
    void Fixup();                                               // 005e9320
    void clear() { if (b != e) { *b = 0; e = b; } }
    void ltrim(const wchar_t* set, const wchar_t* setEnd);
};
struct NStr {                                                   // eastl::string (char)
    char* b; char* e; char* c; int alloc;
    NStr() { b = e = (char*)gEmptyW; c = (char*)gEmptyW + 1; }
    ~NStr() { if (((int)c - (int)b) > 1 && b) operator delete[](b); }
};
const wchar_t* FindFirstNotOf(const wchar_t* b, const wchar_t* e, const wchar_t* sb, const wchar_t* se);   // 005497e0
void WStr::ltrim(const wchar_t* set, const wchar_t* setEnd)
{
    const wchar_t* p = FindFirstNotOf(b, e, set, setEnd);
    uint idx = (p == e) ? (uint)-1 : (uint)(p - b);
    uint len = (uint)(e - b);
    uint n = len < idx ? len : idx;
    wchar_t* q = b + n;
    if (b != q) {
        memmove(b, q, (uint)(((e - q)) * 2 + 2));
        e = e - n;
    }
}
WStr* WStrCopy(WStr* first, WStr* last, WStr* dest);             // 0084ab40 (eastl::copy)
struct WStrVec {
    WStr* b; WStr* e; WStr* c;
    void DoInsertValue(WStr* pos, const WStr* v);               // 00554c30
    void DoDestroyValues(WStr* first, WStr* last);              // 0084aad0
    void erase(WStr* first, WStr* last)
    {
        WStr* p = WStrCopy(last, e, first);
        DoDestroyValues(p, e);
        e = e - (last - first);
    }
    void clear() { erase(b, e); }
    void push_back(const WStr& s)
    {
        if (e < c) {
            WStr* p = e++;
            if (p) p->CopyCtor(&s);
        } else {
            DoInsertValue(e, &s);
        }
    }
};
struct NameList { WStrVec v; int pad[2]; };                     // stride 0x14
void  WStr_Format(WStr*, const wchar_t*, ...);                  // 0041e050
void  WStr_Format2(WStr*, const wchar_t*, ...);                 // 004e0850
const wchar_t* eastl_search(const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*);   // 005e8ff0
void  ConvertToString16(WStr* dst, NStr* src);                  // 0093c6d0
struct RandomLCG {
    uint Uniform(uint n);   // 0x00a68fb0
};
extern RandomLCG gMathRandom;                                   // 01601760
extern WStr gDefaultName;                                       // 015f0a1c (begin) / 015f0a20 (end)
struct ResKey { uint instance, type, group; };
int  OpenRecordAsStream(const ResKey* key, void** stream);      // 00686490
void CloseRecord(int h);                                        // 006861d0
void GetPropertyAsKey(void* props, uint id, ResKey* out);       // 006a1250
struct ByteVec {
    char* b; char* e; char* c;
    ByteVec(uint n, const void* alloc);                         // 005e9f50
    ~ByteVec() { if (b && ((int*)b)[-1]) operator delete[](b); }
};
struct StrNode { void* right; void* left; void* parent; int color; WStr key; int value; };
struct StrIter { StrNode* node; };
struct StrTree {
    StrIter* find(StrIter* out, const WStr& key);               // 005e96f0
    int* operator_index(const WStr& key);                       // 005eae50
};
struct cSPNameGenerator {
    char pad0[0x3c0];
    StrTree mNamesUsed;                 // +0x3c0 (anchor at +0x3c4)
    char pad3c1[0x3f8 - 0x3c1];
    WStrVec mDuplicateSuffixes;         // +0x3f8

    void LoadStringList(const ResKey* key, WStrVec* out, bool lower);
    void LoadStringListEx(void* obj, uint id, WStrVec* out, bool lower);
    void LoadAll(void* obj, void* a1, int a2, int a3, int a4, void* a5, int a6);
    WStr* CreateRandomCompoundName(WStr* ret, void* data, NameList* lists, StrTree* excl, WStrVec* exclSub, int unused, bool allowDup);
    WStr* CreateRandomName(WStr* ret, WStrVec* names, bool allowDup);
    bool  LoadProperty(void* props, uint id, WStrVec* out, bool lower);
    void  LoadPropertyKey(void* props, uint id, WStrVec* out);
};
struct NameFlagsObj { char pad[0x24]; uint flags; };
bool CheckFlag(void* a1, uint id, int a6);                      // 005e8e20
void ReserveLists(void* a1, int a2, int* count, void** data);   // 006a0ae0 (cdecl)
struct U16Pair { ushort first, second; };
struct MapVal { char data[0x28]; MapVal(const MapVal&); };       // 005ea8f0
struct MapValueType {
    U16Pair key; MapVal val;
    MapValueType(const MapValueType& o) : key(o.key), val(o.val) {}
};
struct MapNode { MapNode* right; MapNode* left; MapNode* parent; int color; MapValueType value; };
struct MapIter { MapNode* node; MapIter() {} MapIter(MapNode* n) : node(n) {} };
struct InsertResult { MapNode* node; bool inserted; };
struct UniqueKeysTag {};   // eastl::true_type (has_unique_keys)
void RBTreeInsert(MapNode* node, MapNode* parent, MapNode* anchor, int bInsertOnRight);   // 009216a0
MapNode* RBTreeDecrement(MapNode*);                                            // 009215c0
MapNode* RBTreeIncrement(MapNode*);                                            // 00921580
static inline bool KeyLess(const U16Pair& a, const U16Pair& b)
{
    return a.first < b.first || (!(b.first < a.first) && a.second < b.second);
}
struct U16Map {
    char pad0[4];
    MapNode* anchorRight;               // +4  (anchor node starts here)
    MapNode* anchorLeft;                // +8
    MapNode* anchorParent;              // +0xc
    int anchorColor;                    // +0x10
    uint mnSize;                        // +0x14
    MapNode* anchor() { return (MapNode*)((char*)this + 4); }
    bool KeyLessOOL(const U16Pair& a, const U16Pair& b);                       // 005e90f0

    MapNode** DoInsertValueImpl(MapNode** ret, MapNode* parent, const MapValueType* v, bool bForceToLeft);   // 005ebd10
    InsertResult* DoInsertValue(InsertResult* ret, const MapValueType* v, UniqueKeysTag);          // 005ebdb0
    MapNode** insert(MapNode** ret, MapIter pos, const MapValueType* v, UniqueKeysTag);           // 005ebf10
};
    void* operator new(unsigned int, char*, int, int, char*, int); // 0x00f473a0
// ---- items of slice s005eb160 end

// ---- items of slice s005ec030 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t g_EmptyWStr[2];                                                   // @ 0x01667bac
void* operator new(unsigned int, const char*, int, int, int, int);               // @ 0x00f473a0
void operator_delete_array(void* p);                                             // @ 0x00f47380 (operator delete[])
void* memcpy_thunk(void* d, const void* s, unsigned n);                          // @ 0x011e0744
static inline void SpFree(void* p) {
  if (p && ((int*)p)[-1] != 0) operator_delete_array(p);
}
struct WStr_s005e_c030 {  // eastl::basic_string<wchar_t>: begin, end, capacity, allocator (0x10 bytes)
  wchar_t* b;
  wchar_t* e;
  wchar_t* c;
  uint32_t alloc;
  void Init(const WStr_s005e_c030& s);             // @ 0x0056e2d0 (copy constructor)
  void AllocateSelf(unsigned n);        // @ 0x00429760
  void push_back(wchar_t ch);           // @ 0x004f6510
  void make_lower();                    // @ 0x005e8e80
  void assign(const wchar_t*, const wchar_t*);  // @ 0x00423650
  void append(const wchar_t*, const wchar_t*);  // @ 0x00429580
  void Free() {
    if ((((int)c - (int)b) & ~1) > 2 && b) operator_delete_array(b);
  }
};
extern WStr_s005e_c030 g_EmptyWStrObj;  // @ 0x015f0a1c (shared empty string object)
void sprintfW(WStr_s005e_c030* dst, const wchar_t* fmt, ...);  // @ 0x004e0850
const wchar_t* Search(const wchar_t* b1, const wchar_t* e1, const wchar_t* b2, const wchar_t* e2);  // @ 0x005e8ff0
void Normalize(WStr_s005e_c030* s);  // @ 0x005e9320
struct WStr_s005e_c030;
WStr_s005e_c030* CopyWStrRange(WStr_s005e_c030* first, WStr_s005e_c030* last, WStr_s005e_c030* dest);  // @ 0x0084ab40 (eastl::copy_impl::do_copy, cdecl)
struct StrVec {  // eastl::vector<wstring, sp_vector_allocator>
  WStr_s005e_c030* b;
  WStr_s005e_c030* e;
  WStr_s005e_c030* c;
  void DoDestroyValues(WStr_s005e_c030* first, WStr_s005e_c030* last);   // @ 0x0084aad0
  // erase(first, last), inlined: move the tail down, destroy the leftovers, shrink
  void erase(WStr_s005e_c030* first, WStr_s005e_c030* last) {
    WStr_s005e_c030* p = CopyWStrRange(last, e, first);
    DoDestroyValues(p, e);
    e -= (last - first);
  }
  void Insert(WStr_s005e_c030* pos, WStr_s005e_c030* first, WStr_s005e_c030* last, int tag);  // @ 0x005ea200
};
struct StrSet {  // eastl::set<wstring>, anchor at +4, size at +0x14
  uint32_t cmp;
  uint32_t anchor[4];
  uint32_t size;
  void insert(WStr_s005e_c030* first, WStr_s005e_c030* last);  // @ 0x005e9f10
};
struct Random { uint32_t pad; };
extern Random g_MathRandom;  // @ 0x01601760
uint32_t RandomWeightedChoice(Random* r, uint32_t n, const float* w);  // @ 0x005e8ec0 (cdecl)
struct RandomLCG_s005e_c030 { uint32_t Uniform(uint32_t n); };                      // @ 0x00a68fb0
extern RandomLCG_s005e_c030 g_MathRandomLCG;                                       // @ 0x01601760
struct NodeBase { NodeBase* right; NodeBase* left; NodeBase* parent; uint32_t color; };
void* RBTreeIncrement(void* n);  // @ 0x00921580
struct SpVecW {  // vector<wchar_t, sp_vector_allocator> (0x14 bytes)
  wchar_t* b; wchar_t* e; wchar_t* c; uint32_t alloc, pad;
  void DoInsertValue(wchar_t* pos, const wchar_t& v);  // @ 0x005e9a00
};
struct SpVecF {  // vector<float, sp_vector_allocator> (0x14 bytes)
  float* b; float* e; float* c; uint32_t alloc, pad;
  void push_back_slow(float* pos, const float& v);  // @ 0x00455660
};
struct ChainRow {
  SpVecW chars;
  SpVecF weights;
  ChainRow() { chars.b = 0; chars.e = 0; chars.c = 0; weights.b = 0; weights.e = 0; weights.c = 0; }
  ChainRow(const ChainRow& o);  // @ 0x005ea8f0
  ~ChainRow() { SpFree(weights.b); SpFree(chars.b); }
};
struct Key2 { wchar_t a, b; };
inline bool KeyLess_s005e_c030(const Key2& x, const Key2& y) { return x.a < y.a || (!(y.a < x.a) && x.b < y.b); }
struct ChainNode : NodeBase { Key2 key; ChainRow row; };
struct ChainPair { Key2 key; ChainRow row; ChainPair(const Key2& k, const ChainRow& r) : key(k), row(r) {} };
struct ChainIter {
  ChainNode* node;
  ChainIter() {}
  ChainIter(const ChainIter& o) : node(o.node) {}
  explicit ChainIter(ChainNode* n) : node(n) {}
  ChainIter& operator=(const ChainIter& o) { node = o.node; return *this; }
  bool operator==(const ChainIter& o) const { return node == o.node; }
};
struct UniqueKeys {};  // eastl::true_type (has_unique_keys_type), passed by value
struct ChainMap {  // eastl::map<pair<wchar_t,wchar_t>, chainData>
  uint32_t cmp;
  NodeBase anchor;  // +4
  uint32_t size, alloc;
  ChainIter end() { return ChainIter((ChainNode*)&anchor); }
  void lower_bound(ChainIter* out, const Key2* k);
  ChainIter lower_bound_v(const Key2* k) { ChainIter r; lower_bound(&r, k); return r; }                              // @ 0x005e91c0
  void DoInsertValueHint(ChainIter* out, ChainIter pos, const ChainPair& v, UniqueKeys);
  ChainIter DoInsertValue_v(ChainIter pos, const ChainPair& v, UniqueKeys u) { ChainIter r; DoInsertValueHint(&r, pos, v, u); return r; }      // @ 0x005ebf10
  ChainRow* FUN_005ec030(const Key2* key);
};
struct Key3_s005e_c030 { Key2 k2; wchar_t c; };
struct CountNode : NodeBase { Key3_s005e_c030 key; int pad; int count; int pad2[2]; };
struct CountIter { CountNode* node; CountIter() {} CountIter(const CountIter& o) : node(o.node) {} };
struct CountMap {
  uint32_t cmp;
  NodeBase anchor;
  uint32_t size, alloc;
  void find(CountIter* out, const Key3_s005e_c030* k);   // @ 0x005e93c0
  int* subscript(const Key3_s005e_c030* k);              // @ 0x005ea040
  void DoNukeSubtree(NodeBase* n);            // @ 0x009a9600
};
struct NameGenData {  // 0x28 bytes
  int minLen;
  int maxLen;
  ChainMap chains;  // +8
};
struct Property {
  uint8_t pad0[0x10];
  uint8_t flags;      // +0x10
  uint8_t pad1;
  uint16_t type;      // +0x12
  int* GetInt();      // @ 0x0041e990
};
struct PropList {
  virtual void v0();
  virtual void Release();   // +4
  virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
  virtual void v7(); virtual void v8();
  virtual bool GetProperty(uint32_t id, Property** out);  // +0x24
};
struct PropMgr {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10();
  virtual void GetPropertyList(uint32_t group, uint32_t instance, PropList** out);  // +0x2c
};
PropMgr* PropertyManager();  // @ 0x0067de30
bool GetPropertyAsString16(PropList* l, uint32_t id, WStr_s005e_c030* out);                         // @ 0x006a1400 (cdecl)
bool GetPropertyAsString16Array(PropList* l, uint32_t id, int* count, WStr_s005e_c030** arr);       // @ 0x006a0bc0 (cdecl)
struct TreeIter { NodeBase* node; TreeIter() {} TreeIter(const TreeIter& o) : node(o.node) {} };
struct U16Set_s005e_c030 {
  uint32_t cmp; NodeBase anchor; uint32_t size, alloc;
  TreeIter find(const uint32_t& k);          // @ 0x005e90a0
  void insert(uint32_t c);                   // @ 0x005e9890 (DoInsertValue)
  void DoNukeSubtree(void* n, void* x);      // @ 0x009a9600
};
struct WStrSetT {
  uint32_t cmp; NodeBase anchor; uint32_t size, alloc;
  TreeIter find(const WStr_s005e_c030& k);              // @ 0x005e96f0
};
struct NameNode : NodeBase { WStr_s005e_c030 key; int count; };  // count at +0x20
struct WStrMapT {
  uint32_t cmp; NodeBase anchor; uint32_t size, alloc;
  TreeIter find(const WStr_s005e_c030& k);              // @ 0x005e96f0
  int* subscript(const WStr_s005e_c030& k);             // @ 0x005eae50
};
#define FLD(T, off) (*(T*)((char*)this + (off)))
struct cSPNameGenerator_s005e_c030 {
  bool FUN_005ebe90(PropList* l, uint32_t id, void* vec, bool flag);   // @ 0x005ebe90
  void FUN_005eba70(PropList* l, uint32_t id, void* vec);              // @ 0x005eba70
  void FUN_005eb440(NameGenData* d, PropList* l, uint32_t a, uint32_t b, uint32_t c, void* vec,
                    uint32_t hash);                                    // @ 0x005eb440
  void FUN_005ec130(StrVec* names, NameGenData* data);
  WStr_s005e_c030* FUN_005ec370(WStr_s005e_c030* out, NameGenData* data, StrSet* excluded, StrVec* subs, StrVec* fallback,
                     bool allowDup);
  void Init();  // @ 0x005ec7c0
};
static inline void AutoRefAssignNull(PropList*& l) {
  PropList* old = l;
  if (old) { l = 0; old->Release(); }
}
static inline bool PropBool(PropList* l, uint32_t id, bool def) {
  Property* p;
  if (l && l->GetProperty(id, &p) && p->type == 1) {
    char* d = (char*)p;
    if (p->flags & 0x30) d = *(char**)p;
    return *d != 0;
  }
  return def;
}
// ---- items of slice s005ec030 end

// @ 0x005e9440
template U16Tree::iterator U16Tree::DoInsertValueImpl(node_type*, const value_type&, bool)
;




// @ 0x005e94c0
template Key3Tree::iterator Key3Tree::DoInsertValueImpl(node_type*, const value_type&, bool)
;




// @ 0x005e9550
template eastl::wstring* eastl::uninitialized_relocate_commit<eastl::wstring>(eastl::wstring*, eastl::wstring*, eastl::wstring*)
;




// @ 0x005e96a0
template eastl::basic_string_s005e_9440<char, eastl::allocator_s005e_9440>::basic_string_s005e_9440(const char*, size_t, const eastl::allocator_s005e_9440&)
;




// @ 0x005e96f0
namespace eastl {
template <typename K, typename V, typename C, typename E> typename rbtree_s005e_9440<K, V, C, E>::iterator rbtree_s005e_9440<K, V, C, E>::find(const key_type& key)
{
  extract_key extractKey;
  node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
  rbtree_node_base_s005e_9440* pRangeEnd = &mAnchor;
  while (pCurrent) {
    if (!mCompare(extractKey(pCurrent->mValue), key)) {
      pRangeEnd = pCurrent;
      pCurrent = (node_type*)pCurrent->mpNodeLeft;
    } else
      pCurrent = (node_type*)pCurrent->mpNodeRight;
  }
  if ((pRangeEnd != &mAnchor) && !mCompare(key, extractKey(((node_type*)pRangeEnd)->mValue)))
    return iterator((node_type*)pRangeEnd);
  return iterator((node_type*)&mAnchor);
}
}  // namespace eastl




// @ 0x005e9890
template eastl::pair_s005e_9440<U16Tree::iterator, bool> U16Tree::DoInsertValue(const value_type&, eastl::true_type)
;




// @ 0x005e9930
template WStringTree::iterator WStringTree::DoInsertValueImpl(node_type*, const value_type&, bool)
;




// @ 0x005e99c0
template eastl::wstring* eastl::copy_backward<eastl::wstring*, eastl::wstring*>(eastl::wstring*, eastl::wstring*, eastl::wstring*)
;




// @ 0x005e9d50
template WStringIntTree::iterator WStringIntTree::DoInsertValueImpl(node_type*, const value_type&, bool)
;




// @ 0x005e9f50
template eastl::vector_s005e_9440<bool>::vector_s005e_9440(size_t, const eastl::sp_vector_allocator_s005e_9440&)
;




// @ 0x005ea010
template void WStringTree::clear()
;




// @ 0x005ea200
template void eastl::vector_s005e_9440<eastl::wstring>::DoInsertFromIterator(eastl::wstring*, const eastl::wstring*, const eastl::wstring*, eastl::iterator_tag)
;



// @ 0x005ea3d0
void FUN_005ea3d0()
{}



// @ 0x005ea8f0
void FUN_005ea8f0()
{}



// @ 0x005ea970
void FUN_005ea970()
{}



// @ 0x005eae50
void FUN_005eae50()
{}



// @ 0x005eaef0
void FUN_005eaef0()
{}


// @ 0x005eb160
void cSPNameGenerator::LoadStringList(const ResKey* keyIn, WStrVec* out, bool lower)
{
    ResKey key;
    key.instance = keyIn->instance;
    key.type = 0x24a0e52;
    key.group = 0x461227d;
    void* stream = 0;
    int h = OpenRecordAsStream(&key, &stream);
    if (h == -1)
        return;

    typedef int  (__thiscall* SizeFn)(void*);
    typedef uint (__thiscall* ReadFn)(void*, void*, uint);
    bool dummyAlloc;
    ByteVec buf(((SizeFn)VSLOT(stream, 7))(stream), &dummyAlloc);
    uint got = ((ReadFn)VSLOT(stream, 12))(stream, buf.b, (uint)(buf.e - buf.b));
    CloseRecord(h);

    char* p = buf.b;
    if (got >= 3 && (unsigned char)buf.b[0] == 0xef && (unsigned char)buf.b[1] == 0xbb && (unsigned char)buf.b[2] == 0xbf)
        p = buf.b + 3;

    if (p != buf.e) {
        wchar_t ws[3];
        ws[0] = 0x20; ws[1] = 9; ws[2] = 0;
        do {
            char* lineBegin = p;
            char* q = p;
            if (q != buf.e) {
                do {
                    if (*q == '\r' || *q == '\n')
                        break;
                    q++;
                } while (q != buf.e);
                p = q;
            }
            char* lineEnd = q;
            if (q != buf.e && (*q == '\r' || *q == '\n'))
                p = q + 1;

            NStr line;
            uint len = (uint)(lineEnd - lineBegin);
            uint n = len + 1;
            if (n > 1) {
                line.b = (char*)operator new(n, "Editor", 0, 0, ALLOC_FILE, 0xd1);
                line.e = line.b;
                line.c = line.b + n;
            }
            memcpy(line.b, lineBegin, len);
            line.e = line.b + len;
            *line.e = 0;

            WStr w;
            w.b = w.e = w.c = 0;
            ConvertToString16(&w, &line);

            const wchar_t* wsEnd = ws;
            while (*wsEnd) wsEnd++;
            w.ltrim(ws, wsEnd);
            w.rtrim();
            if (!w.empty()) {
                if (lower)
                    w.make_lower();
                out->push_back(w);
            }
        } while (p != buf.e);
    }
}


// @ 0x005eb440
void cSPNameGenerator::LoadAll(void* obj, void* a1, int a2, int a3, int a4, void* a5, int a6)
{
    void* data[3]   = { 0, 0, 0 };
    int   counts[3] = { 0, 0, 0 };
    ReserveLists(a1, a2, &counts[0], &data[0]);
    ReserveLists(a1, a3, &counts[1], &data[1]);
    ReserveLists(a1, a4, &counts[2], &data[2]);
    if (CheckFlag(a1, 0x6664a3f, a6))
        ((NameFlagsObj*)obj)->flags |= 1;
    if (CheckFlag(a1, 0x6664a52, a6))
        ((NameFlagsObj*)obj)->flags |= 2;
    char* dst = (char*)a5;
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < counts[k]; i++)
            LoadStringList((const ResKey*)((char*)data[k] + i * 12), (WStrVec*)dst, false);
        dst += 0x14;
    }
}


// @ 0x005eb540
WStr* cSPNameGenerator::CreateRandomCompoundName(WStr* ret, void* data, NameList* lists, StrTree* excl, WStrVec* exclSub, int unused, bool allowDup)
{
    WStr name;
    bool done = false;
    int tries = 0;
    for (;;) {
        tries++;
        if (tries > 10)
            break;
        name.clear();
        {
            WStr parts[3];
            NameList* L = lists;
            for (int i = 0; i < 3; i++, L++) {
                if (L->v.b == L->v.e) {
                    if (i < 2) {
                        ret->b = ret->e = ret->c = 0;
                        ret->Init(gDefaultName.b, gDefaultName.e);
                        return ret;
                    }
                } else {
                    uint idx = gMathRandom.Uniform((uint)(L->v.e - L->v.b));
                    WStr* s = &L->v.b[idx];
                    if (s != &parts[i])
                        parts[i].assign(s->b, s->e);
                }
            }
            uint fl = ((NameFlagsObj*)data)->flags;
            const wchar_t* fmt;
            if (fl & 1) fmt = (fl & 2) ? L"%s %s %s" : L"%s %s%s";
            else        fmt = (fl & 2) ? L"%s%s %s"  : L"%s%s%s";
            WStr_Format(&name, fmt, parts[0].b, parts[1].b, parts[2].b);

            WStr lowerName;
            lowerName.Init(name.b, name.e);
            for (wchar_t* q = lowerName.b; q < lowerName.e; q++) {
                ushort ch = *q;
                if (ch <= 0xff)
                    ch = (ushort)tolower(ch & 0xff);
                *q = ch;
            }

            StrIter it;
            if (excl->find(&it, lowerName)->node == (StrNode*)((char*)excl + 4)) {
                bool rejected = false;
                for (WStr* s = exclSub->b; s != exclSub->e; s++) {
                    uint n = (uint)(s->e - s->b);
                    if (n <= (uint)(lowerName.e - lowerName.b)) {
                        const wchar_t* p = eastl_search(lowerName.b, lowerName.e, s->b, s->b + n);
                        if ((p != lowerName.e || n == 0) && (int)(p - lowerName.b) != -1) {
                            rejected = true;
                            break;
                        }
                    }
                }
                if (!rejected) {
                    if (allowDup) {
                        done = true;
                    } else {
                        StrIter it2;
                        if (mNamesUsed.find(&it2, name)->node == (StrNode*)((char*)this + 0x3c4))
                            done = true;
                    }
                }
            }
        }
        if (done)
            break;
    }
    if (done) {
        StrIter it;
        mNamesUsed.find(&it, name);
        if (it.node == (StrNode*)((char*)this + 0x3c4)) {
            *mNamesUsed.operator_index(name) = 1;
        } else if (allowDup) {
            int n = it.node->value;
            if (n - 1 < (int)(mDuplicateSuffixes.e - mDuplicateSuffixes.b)) {
                it.node->value = n + 1;
                WStr* s = &mDuplicateSuffixes.b[n - 1];
                name.Append(s->b, s->e);
            } else {
                it.node->value = n + 1;
                WStr_Format2(&name, L"%c%d", 0x2d, n + 1);
            }
        }
    }
    ret->b = ret->e = ret->c = 0;
    const wchar_t* z = name.b;
    while (*z) z++;
    ret->Init(name.b, z);
    return ret;
}


// @ 0x005eba70
void cSPNameGenerator::LoadPropertyKey(void* props, uint id, WStrVec* out)
{
    typedef bool (__thiscall* HasFn)(void*, uint);
    if (!((HasFn)VSLOT(props, 7))(props, id))
        return;
    out->clear();
    ResKey key = { 0, 0, 0 };
    GetPropertyAsKey(props, id, &key);
    LoadStringList(&key, out, false);
}


// @ 0x005ebb00
WStr* cSPNameGenerator::CreateRandomName(WStr* ret, WStrVec* names, bool allowDup)
{
    if (names->b == names->e) {
        ret->b = ret->e = ret->c = 0;
        ret->RangeInitialize(gDefaultName.b);
        return ret;
    }
    int tries = 0;
    WStr* elem;
    StrIter it;
    for (;;) {
        uint idx = gMathRandom.Uniform((uint)(names->e - names->b));
        elem = &names->b[idx];
        mNamesUsed.find(&it, *elem);
        if (it.node == (StrNode*)((char*)this + 0x3c4)) {
            *mNamesUsed.operator_index(*elem) = 1;
            WStr tmp;
            tmp.b = tmp.e = tmp.c = 0;
            tmp.RangeInitialize(elem->b);
            tmp.Fixup();
            ret->CopyCtor(&tmp);
            return ret;
        }
        if (allowDup)
            break;
        tries++;
        if (tries > 100) {
            WStr tmp;
            tmp.b = tmp.e = tmp.c = 0;
            tmp.RangeInitialize(elem->b);
            tmp.Fixup();
            ret->CopyCtor(&tmp);
            return ret;
        }
    }
    WStr tmp;
    tmp.CopyCtor(elem);
    int n = it.node->value;
    if (n - 1 < (int)(mDuplicateSuffixes.e - mDuplicateSuffixes.b)) {
        it.node->value = n + 1;
        WStr* s = &mDuplicateSuffixes.b[n - 1];
        tmp.Append(s->b, s->e);
    } else {
        it.node->value = n + 1;
        WStr_Format2(&tmp, L"%c%d", 0x2d, n + 1);
    }
    tmp.Fixup();
    ret->b = ret->e = ret->c = 0;
    ret->RangeInitialize(tmp.b);
    return ret;
}


// @ 0x005ebd10
MapNode** U16Map::DoInsertValueImpl(MapNode** ret, MapNode* parent, const MapValueType* v, bool bForceToLeft)
{
    int bInsertOnRight = (!bForceToLeft && parent != anchor() && !KeyLess(v->key, parent->value.key)) ? 1 : 0;
    MapNode* n = (MapNode*)operator new(0x3c, "Editor", 0, 0, ALLOC_FILE, 0xd1);
    new (&n->value) MapValueType(*v);
    RBTreeInsert(n, parent, anchor(), bInsertOnRight);
    mnSize++;
    *ret = n;
    return ret;
}


// @ 0x005ebdb0
InsertResult* U16Map::DoInsertValue(InsertResult* ret, const MapValueType* v, UniqueKeysTag)
{
    MapNode* pCurrent = anchorParent;
    MapNode* pLowerBound = anchor();
    bool bValueLessThanNode = true;
    while (pCurrent) {
        bValueLessThanNode = KeyLess(v->key, pCurrent->value.key);
        pLowerBound = pCurrent;
        pCurrent = bValueLessThanNode ? pCurrent->left : pCurrent->right;
    }
    MapNode* pParent = pLowerBound;
    if (bValueLessThanNode) {
        if (pLowerBound != anchorLeft)
            pLowerBound = RBTreeDecrement(pLowerBound);
        else {
            MapNode* n;
            DoInsertValueImpl(&n, pLowerBound, v, false);
            ret->node = n;
            ret->inserted = true;
            return ret;
        }
    }
    if (KeyLess(pLowerBound->value.key, v->key)) {
        MapNode* n;
        DoInsertValueImpl(&n, pParent, v, false);
        ret->node = n;
        ret->inserted = true;
        return ret;
    }
    ret->node = pLowerBound;
    ret->inserted = false;
    return ret;
}


// @ 0x005ebe90
bool cSPNameGenerator::LoadProperty(void* props, uint id, WStrVec* out, bool lower)
{
    struct Prop { char* data; int pad; int count; int pad2; ushort flags; ushort single; };
    typedef Prop* (__thiscall* GetFn)(void*, uint);
    Prop* p = ((GetFn)VSLOT(props, 10))(props, id);
    ushort mode = p->flags & 0x30;
    int count;
    char* first;
    if (mode != 0) {
        count = p->count;
        if (count <= 0)
            return false;
    } else {
        if (p->single == 0)
            return false;
        count = 1;
    }
    if (mode != 0)
        first = p->data;
    else
        first = p->single ? (char*)p : 0;
    if (count > 0) {
        do {
            LoadStringList((const ResKey*)first, out, lower);
            first += 0xc;
            count--;
        } while (count != 0);
    }
    return true;
}


// @ 0x005ebf10
MapNode** U16Map::insert(MapNode** ret, MapIter position, const MapValueType* v, UniqueKeysTag)
{
    if (position.node != anchorRight && position.node != anchor()) {
        MapIter itNext(position);
        itNext.node = RBTreeIncrement(itNext.node);
        const bool bPositionLessThanValue = KeyLess(position.node->value.key, v->key);
        if (bPositionLessThanValue) {
            const bool bValueLessThanNext = KeyLessOOL(v->key, itNext.node->value.key);
            if (bValueLessThanNext) {
                if (position.node->right)
                    return DoInsertValueImpl(ret, itNext.node, v, true);
                return DoInsertValueImpl(ret, position.node, v, false);
            }
        }
        InsertResult r;
        DoInsertValue(&r, v, UniqueKeysTag());
        *ret = r.node;
        return ret;
    }
    if (mnSize && KeyLess(anchorRight->value.key, v->key))
        return DoInsertValueImpl(ret, anchorRight, v, false);
    InsertResult r;
    DoInsertValue(&r, v, UniqueKeysTag());
    *ret = r.node;
    return ret;
}

// @ 0x005ec030
ChainRow* ChainMap::FUN_005ec030(const Key2* key)
{
  // eastl::map::operator[]
  ChainIter itLower;
  itLower = lower_bound_v(key);
  if (itLower.node == (ChainNode*)&anchor || KeyLess_s005e_c030(*key, itLower.node->key)) {
    ChainRow t;
    ChainPair v(*key, t);
    itLower = DoInsertValue_v(itLower, v, UniqueKeys());
  }
  return &itLower.node->row;
}

// @ 0x005ec130
void cSPNameGenerator_s005e_c030::FUN_005ec130(StrVec* names, NameGenData* data)
{
  data->minLen = 100;
  data->maxLen = 0;
  CountMap counts;
  counts.anchor.right = &counts.anchor;
  counts.anchor.left = &counts.anchor;
  counts.anchor.parent = 0;
  counts.anchor.color = 0;
  counts.size = 0;
  for (WStr_s005e_c030* s = names->b; s != names->e; s++) {
    int len = s->e - s->b;
    if (len <= 0) continue;
    if (len < data->minLen) data->minLen = len;
    if (len > data->maxLen) data->maxLen = len;
    wchar_t p2 = '^';
    wchar_t p1 = '^';
    for (wchar_t* p = s->b; p != s->e;) {
      wchar_t ch = *p;
      Key2 k2;
      k2.a = p2;
      k2.b = p1;
      data->chains.FUN_005ec030(&k2);
      Key3_s005e_c030 k3;
      k3.k2 = k2;
      k3.c = ch;
      CountIter it;
      counts.find(&it, &k3);
      if (it.node == (CountNode*)&counts.anchor) *counts.subscript(&k3) = 1;
      else it.node->count++;
      p++;
      if (p == s->e) {
        Key3_s005e_c030 e3;
        e3.k2.a = p1;
        e3.k2.b = ch;
        e3.c = '$';
        counts.find(&it, &e3);
        if (it.node == (CountNode*)&counts.anchor) *counts.subscript(&e3) = 1;
        else it.node->count++;
      }
      p2 = p1;
      p1 = ch;
    }
  }
  for (NodeBase* n = counts.anchor.left; n != &counts.anchor; n = (NodeBase*)RBTreeIncrement(n)) {
    CountNode* cn = (CountNode*)n;
    Key2 k2 = cn->key.k2;
    wchar_t c = cn->key.c;
    int cnt = cn->count;
    ChainRow* row = data->chains.FUN_005ec030(&k2);
    if (row->chars.e < row->chars.c) {
      if (row->chars.e) *row->chars.e = c;
      row->chars.e++;
    } else {
      row->chars.DoInsertValue(row->chars.e, c);
    }
    float w = (float)cnt;
    if (row->weights.e < row->weights.c) {
      if (row->weights.e) *row->weights.e = w;
      row->weights.e++;
    } else {
      row->weights.push_back_slow(row->weights.e, w);
    }
  }
  for (NodeBase* n = counts.anchor.parent; n;) {
    counts.DoNukeSubtree(n->right);
    NodeBase* nx = n->left;
    operator_delete_array(n);
    n = nx;
  }
}

// @ 0x005ec370
WStr_s005e_c030* cSPNameGenerator_s005e_c030::FUN_005ec370(WStr_s005e_c030* out, NameGenData* data, StrSet* excluded, StrVec* subs, StrVec* fallback, bool allowDup)
{
  if (data->maxLen < 1) {
    out->Init(g_EmptyWStrObj);
    return out;
  }
  WStr_s005e_c030 str;
  str.b = 0; str.e = 0; str.c = 0;
  str.AllocateSelf(data->maxLen + 2);
  *str.e = 0;
  bool accepted = false;
  int tries = 0;
  do {
    tries++;
    if (tries > 5000) {
      if (!accepted) {
        uint32_t idx = g_MathRandomLCG.Uniform(fallback->e - fallback->b);
        WStr_s005e_c030* f = &fallback->b[idx];
        if (f != &str) str.assign(f->b, f->e);
      }
      break;
    }
    if (str.e != str.b) {
      *str.b = 0;
      str.e = str.b;
    }
    int exactCount = 0;
    int len = 0;
    if (data->maxLen >= 0) {
      wchar_t a = '^';
      wchar_t b = '^';
      do {
        Key2 k;
        k.a = a;
        k.b = b;
        ChainRow* row = data->chains.FUN_005ec030(&k);
        uint32_t idx = RandomWeightedChoice(&g_MathRandom, row->weights.e - row->weights.b, row->weights.b);
        wchar_t c = row->chars.b[idx];
        uint32_t c32 = c;
        if (c == '$') break;
        if (FLD(uint32_t, 0x3f0) != 0) {
          U16Set_s005e_c030* ex = (U16Set_s005e_c030*)((char*)this + 0x3dc);
          if (ex->find(c32).node != &ex->anchor) {
            exactCount++;
            if (exactCount > 1) break;
          }
        }
        str.push_back(c);
        len++;
        a = b;
        b = c;
      } while (len <= data->maxLen);
    }
    if (FLD(uint32_t, 0x3f0) == 0 || exactCount == 1) {
      int slen = str.e - str.b;
      if (slen >= data->minLen && slen <= data->maxLen) {
        bool rejected = false;
        bool check = true;
        if (!allowDup) {
          WStrMapT* used = (WStrMapT*)((char*)this + 0x3c0);
          rejected = used->find(str).node != &used->anchor;
          if (rejected) check = false;
        }
        if (check) {
          WStr_s005e_c030 lower;
          lower.b = 0; lower.e = 0; lower.c = 0;
          lower.AllocateSelf(slen + 1);
          memcpy_thunk(lower.b, str.b, slen * 2);
          lower.e = lower.b + slen;
          *lower.e = 0;
          lower.make_lower();
          WStrSetT* exs = (WStrSetT*)excluded;
          if (exs->find(lower).node == &exs->anchor) {
            for (WStr_s005e_c030* sb = subs->b; sb != subs->e; sb++) {
              unsigned sl = sb->e - sb->b;
              unsigned ll = lower.e - lower.b;
              if (sl <= ll) {
                const wchar_t* pos = Search(lower.b, lower.e, sb->b, sb->b + sl);
                if ((pos != lower.e || sl == 0) && (pos - lower.b) != -1) {
                  rejected = true;
                  break;
                }
              }
            }
          } else {
            rejected = true;
          }
          lower.Free();
        }
        accepted = !rejected;
      }
    }
  } while (!accepted);
  Normalize(&str);
  WStrMapT* used = (WStrMapT*)((char*)this + 0x3c0);
  TreeIter res = used->find(str);
  if (res.node == &used->anchor) {
    *used->subscript(str) = 1;
  } else if (allowDup) {
    NameNode* nn = (NameNode*)res.node;
    int cnt = nn->count;
    if (cnt - 1 < (FLD(int, 0x3fc) - FLD(int, 0x3f8)) / 16) {
      nn->count = cnt + 1;
      WStr_s005e_c030* suf = (WStr_s005e_c030*)((char*)FLD(WStr_s005e_c030*, 0x3f8) + (cnt - 1) * 16);
      str.append(suf->b, suf->e);
    } else {
      nn->count = cnt + 1;
      sprintfW(&str, L"%c%d", '-', cnt + 1);
    }
  }
  out->b = 0; out->e = 0; out->c = 0;
  const wchar_t* sb = str.b;
  const wchar_t* sp = sb;
  while (*sp) sp++;
  int n = sp - sb;
  unsigned cap = n + 1;
  if (cap < 2) {
    out->b = g_EmptyWStr; out->e = g_EmptyWStr; out->c = g_EmptyWStr + 1;
  } else {
    wchar_t* p = (wchar_t*)operator new(cap * 2, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\internal\\string.h", 0xd1);
    out->b = p; out->e = p; out->c = p + cap;
  }
  wchar_t* ob = out->b;
  memcpy_thunk(ob, sb, n * 2);
  out->e = ob + n;
  *out->e = 0;
  str.Free();
  return out;
}

// @ 0x005ec7c0
void cSPNameGenerator_s005e_c030::Init()
{
  PropList* list = 0;
  PropMgr* pm = PropertyManager();
  AutoRefAssignNull(list);
  pm->GetPropertyList(0x0fd9c1e3, 0x0461227d, &list);
  if (!list) return;
  FLD(bool, 0x3b8) = FUN_005ebe90(list, 0x026efc90, (char*)this + 0x00, false);
  FLD(bool, 0x3b9) = FUN_005ebe90(list, 0x026efc89, (char*)this + 0x14, false);
  FLD(bool, 0x3ba) = FUN_005ebe90(list, 0x026efc92, (char*)this + 0x28, false);
  FLD(bool, 0x3bb) = FUN_005ebe90(list, 0x1204a915, (char*)this + 0x3c, false);
  FLD(bool, 0x3bc) = FUN_005ebe90(list, 0x042c9060, (char*)this + 0x50, false);
  FLD(bool, 0x3bd) = FUN_005ebe90(list, 0x042c9065, (char*)this + 0x64, false);
  FLD(bool, 0x3be) = FUN_005ebe90(list, 0x05527d05, (char*)this + 0x78, false);
  FLD(bool, 0x3bf) = FUN_005ebe90(list, 0x05527d06, (char*)this + 0x8c, false);
  int lo = 0;
  Property* prop;
  if (list && list->GetProperty(0x0553c23a, &prop) && prop->type == 9) lo = *prop->GetInt();
  int hi = 100;
  if (list && list->GetProperty(0x0553c24b, &prop) && prop->type == 9) hi = *prop->GetInt();
  // mExactlyOneOf set: clear, then refill from the property string
  U16Set_s005e_c030* exact = (U16Set_s005e_c030*)((char*)this + 0x3dc);
  exact->DoNukeSubtree((void*)FLD(uint32_t, 0x3e8), 0);
  exact->anchor.right = &exact->anchor;
  exact->anchor.left = &exact->anchor;
  exact->anchor.parent = 0;
  exact->anchor.color = 0;
  exact->size = 0;
  WStr_s005e_c030 exStr;
  exStr.b = g_EmptyWStr; exStr.e = g_EmptyWStr; exStr.c = g_EmptyWStr + 1;
  if (GetPropertyAsString16(list, 0x059346d9, &exStr)) {
    int n = exStr.e - exStr.b;
    for (int i = 0; i < n; i++) exact->insert(exStr.b[i]);
  }
  // mDuplicateSuffixes: clear, then refill from the property array
  StrVec* dup = (StrVec*)((char*)this + 0x3f8);
  dup->erase(dup->b, dup->e);
  int cnt = 0;
  WStr_s005e_c030* arr = 0;
  if (GetPropertyAsString16Array(list, 0x05944e2e, &cnt, &arr)) {
    int tag;
    dup->Insert(dup->b, arr, arr + cnt, tag);
  }
  FLD(bool, 0x244) = true;
  FLD(bool, 0x244) = PropBool(list, 0x0302842a, true);
  if (FLD(bool, 0x244)) {
    static const struct { int flag; int vec; int data; } T[8] = {
        {0x3b8, 0x00, 0x270}, {0x3b9, 0x14, 0x248}, {0x3ba, 0x28, 0x298}, {0x3bb, 0x3c, 0x2c0},
        {0x3bc, 0x50, 0x2e8}, {0x3bd, 0x64, 0x310}, {0x3be, 0x78, 0x338}, {0x3bf, 0x8c, 0x360}};
    for (int i = 0; i < 8; i++) {
      if (FLD(bool, T[i].flag)) {
        NameGenData* d = (NameGenData*)((char*)this + T[i].data);
        FUN_005ec130((StrVec*)((char*)this + T[i].vec), d);
        d->minLen = (lo < d->minLen) ? d->minLen : lo;
        d->maxLen = (d->maxLen < hi) ? d->maxLen : hi;
      }
    }
    FUN_005eba70(list, 0x046a3e66, (char*)this + 0x00);
    FUN_005eba70(list, 0x046a3e56, (char*)this + 0x14);
    FUN_005eba70(list, 0x046a4abf, (char*)this + 0x3c);
    FUN_005eba70(list, 0x046a3e75, (char*)this + 0x50);
    FUN_005eba70(list, 0x046a3e84, (char*)this + 0x64);
    FUN_005eba70(list, 0x05529c6a, (char*)this + 0x78);
    FUN_005eba70(list, 0x05529c6b, (char*)this + 0x8c);
    StrVec ex;
    ex.b = 0; ex.e = 0; ex.c = 0;
    FUN_005ebe90(list, 0x03028839, &ex, true);
    WStr_s005e_c030* eb = ex.b;
    WStr_s005e_c030* ee = ex.e;
    ((StrSet*)((char*)this + 0x388))->insert(eb, ee);
    FUN_005ebe90(list, 0x03028846, (char*)this + 0x3a4, true);
    if (!FLD(bool, 0x3b8)) FUN_005eb440((NameGenData*)((char*)this + 0x270), list, 0x046a3e6a, 0x046a3e6d, 0x046a3e71, (char*)this + 0xa0, 0x5f848353);
    if (!FLD(bool, 0x3b9)) FUN_005eb440((NameGenData*)((char*)this + 0x248), list, 0x04691528, 0x0469152e, 0x04691532, (char*)this + 0xdc, 0x21055651);
    if (!FLD(bool, 0x3bc)) FUN_005eb440((NameGenData*)((char*)this + 0x2e8), list, 0x046a3e78, 0x046a3e7d, 0x046a3e80, (char*)this + 0x118, 0xe44aea33);
    if (!FLD(bool, 0x3bd)) FUN_005eb440((NameGenData*)((char*)this + 0x310), list, 0x046a3e86, 0x046a3e8b, 0x046a3e8e, (char*)this + 0x154, 0xe7ca2d90);
    if (!FLD(bool, 0x3bb)) FUN_005eb440((NameGenData*)((char*)this + 0x2c0), list, 0x046a4ab3, 0x046a4ab7, 0x046a4abb, (char*)this + 0x190, 0x9ea3031a);
    if (!FLD(bool, 0x3be)) FUN_005eb440((NameGenData*)((char*)this + 0x338), list, 0x05529f2c, 0x05529f2d, 0x05529f2e, (char*)this + 0x1cc, 0x78bddf27);
    if (!FLD(bool, 0x3bf)) FUN_005eb440((NameGenData*)((char*)this + 0x360), list, 0x05529f3c, 0x05529f3d, 0x05529f3e, (char*)this + 0x208, 0xc710b6e9);
    ex.DoDestroyValues(eb, ee);
    SpFree(eb);
  }
  exStr.Free();
  if (list) list->Release();
}
