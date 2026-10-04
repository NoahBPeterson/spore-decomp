// slice s005e9440 -- EASTL template instances emitted in the SP editor TU (verb icon trays):
// rbtree insert/find/lower_bound/DoNuke/clear for set<uint16>, map<Key3,uint32>, set<wstring>,
// map<wstring,int>, map<uint32,cKeyedBuffers>; vector<wchar_t>::DoInsertValue,
// vector<wstring>::DoInsertFromIterator, vector<bool>(n), basic_string<char>(p,n) and helpers.
// Written as the real EASTL (2008) code so cl makes the same inline choices.
// Key3 / cKeyedBuffers are placeholder names for the element types (layout from the code).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <string.h>
#include <new>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380
void* operator new[](unsigned int n, const char* name, int flags, unsigned int debugFlags,
                     const char* file, int line);  // 0x00f473a0

namespace eastl {
struct true_type {};
struct false_type {};
struct iterator_tag { iterator_tag() {} };

struct allocator {
  allocator() {}
  allocator(const allocator&) {}
  void* allocate(size_t n) {
    return operator new[](n, "Editor", 0, 0, "c:\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  }
  void deallocate(void* p) { EASTL_allocator_deallocate(p); }
};
struct sp_vector_allocator {
  sp_vector_allocator() {}
  void* allocate(size_t n) {
    return operator new[](n, "Editor", 0, 0, "c:\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  }
  void deallocate(void* p) {
    if (p && ((int*)p)[-1] != 0) EASTL_allocator_deallocate(p);
  }
};

template <typename T> inline const T& min_alt(const T& a, const T& b) { return (b < a) ? b : a; }

inline int Compare(const wchar_t* p1, const wchar_t* p2, size_t n) {
  for (; n > 0; ++p1, ++p2, --n) {
    if (*p1 != *p2) return (*p1 < *p2) ? -1 : 1;
  }
  return 0;
}

template <typename T, typename A = allocator>
class basic_string {
 public:
  typedef T value_type;
  typedef size_t size_type;
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;
  basic_string(const basic_string& x) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(x.mAllocator) {
    RangeInitialize(x.mpBegin, x.mpEnd);
  }
  basic_string(const T* p, size_type n, const A& a = A()) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {
    RangeInitialize(p, p + n);
  }
  ~basic_string() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin) EASTL_allocator_deallocate(mpBegin);
  }
  basic_string& operator=(const basic_string& x) {
    if (&x != this) assign(x.mpBegin, x.mpEnd);
    return *this;
  }
  basic_string& assign(const T* pBegin, const T* pEnd);  // 0x00423650
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
typedef basic_string<wchar_t> wstring;
typedef basic_string<char> string;

template <typename T, typename A>
inline bool operator<(const basic_string<T, A>& a, const basic_string<T, A>& b) {
  return basic_string<T, A>::compare(a.mpBegin, a.mpEnd, b.mpBegin, b.mpEnd) < 0;
}

template <typename T> struct less {
  bool operator()(const T& a, const T& b) const { return a < b; }
};
template <typename T> struct use_self {
  const T& operator()(const T& x) const { return x; }
};
template <typename P> struct use_first {
  const typename P::first_type& operator()(const P& x) const { return x.first; }
};
template <typename T1, typename T2> struct pair {
  typedef T1 first_type;
  T1 first;
  T2 second;
  pair(const T1& a, const T2& b) : first(a), second(b) {}
};

// ---- generic iterator helpers ----
template <typename It> struct generic_iterator {
  It mIterator;
  generic_iterator() : mIterator(0) {}
  explicit generic_iterator(It p) : mIterator(p) {}
  It base() const { return mIterator; }
};
template <typename T>
generic_iterator<T*> uninitialized_copy_impl(generic_iterator<T*> first, generic_iterator<T*> last,
                                             generic_iterator<T*> dest, iterator_tag);  // 0x0054b510
template <typename T> inline T* uninitialized_copy_ptr(T* first, T* last, T* result) {
  const generic_iterator<T*> i(uninitialized_copy_impl(generic_iterator<T*>(first), generic_iterator<T*>(last),
                                                       generic_iterator<T*>(result), iterator_tag()));
  return i.base();
}
template <typename T> T* uninitialized_relocate_start(T* first, T* last, T* dest);  // 0x0054b400
template <typename T> T* uninitialized_relocate_commit(T* first, T* last, T* dest) {
  for (; first != last; ++first, ++dest) first->~T();
  return dest;
}
template <typename T> inline T* uninitialized_relocate_ptr(T* first, T* last, T* dest) {
  T* result = uninitialized_relocate_start(first, last, dest);
  eastl::uninitialized_relocate_commit(first, last, dest);
  return result;
}
template <typename T> inline T* copy_backward_trivial(const T* first, const T* last, T* result) {
  return (T*)memmove(result - (last - first), first, (size_t)((uintptr_t)last - (uintptr_t)first));
}
template <typename T> inline T* uninitialized_copy_trivial(const T* first, const T* last, T* result) {
  return (T*)memcpy(result, first, (size_t)((uintptr_t)last - (uintptr_t)first)) + (last - first);
}
template <typename BI1, typename BI2> BI2 copy_backward(BI1 first, BI1 last, BI2 resultEnd) {
  while (last != first) *--resultEnd = *--last;
  return resultEnd;
}
template <typename T> T* copy(T* first, T* last, T* result);  // 0x0084ab40

// ---- vector ----
template <typename T, typename A = sp_vector_allocator>
class vector {
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
  explicit vector(size_type n, const A& a = A());
  ~vector() {
    for (T* p = mpBegin; p < mpEnd; ++p) p->~T();
    DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
  }
  void DoInsertValue(iterator position, const T& value);
  void DoInsertFromIterator(iterator position, const T* first, const T* last, iterator_tag);
};

template <typename T, typename A>
vector<T, A>::vector(size_type n, const A& a) : mAllocator(a) {
  mpBegin = DoAllocate(n);
  mpEnd = mpBegin;
  mpCapacity = mpBegin + n;
  if (n > 0) memset(mpBegin, 0, n);
  mpEnd = mpBegin + n;
}

template <typename T, typename A>
void vector<T, A>::DoInsertValue(iterator position, const T& value) {
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

template <typename T, typename A>
void vector<T, A>::DoInsertFromIterator(iterator position, const T* first, const T* last, iterator_tag) {
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

// ---- rbtree ----
struct rbtree_node_base {
  rbtree_node_base* mpNodeRight;
  rbtree_node_base* mpNodeLeft;
  rbtree_node_base* mpNodeParent;
  char mColor;
};
enum RBTreeSide { kRBTreeSideLeft, kRBTreeSideRight };
}
eastl::rbtree_node_base* RBTreeIncrement(const eastl::rbtree_node_base* pNode);  // 0x00921580
eastl::rbtree_node_base* RBTreeDecrement(const eastl::rbtree_node_base* pNode);  // 0x009215c0
void RBTreeInsert(eastl::rbtree_node_base* pNode, eastl::rbtree_node_base* pNodeParent,
                  eastl::rbtree_node_base* pNodeAnchor, eastl::RBTreeSide insertionSide);  // 0x009216a0
namespace eastl {
template <typename V> struct rbtree_node : public rbtree_node_base { V mValue; };
template <typename V> struct rbtree_iterator {
  rbtree_node<V>* mpNode;
  rbtree_iterator() : mpNode(0) {}
  explicit rbtree_iterator(const rbtree_node<V>* p) : mpNode((rbtree_node<V>*)p) {}
  rbtree_iterator(const rbtree_iterator& x) : mpNode(x.mpNode) {}
  rbtree_iterator& operator++() {
    mpNode = (rbtree_node<V>*)RBTreeIncrement(mpNode);
    return *this;
  }
};

template <typename K, typename V, typename C, typename E>
class rbtree {
 public:
  typedef rbtree_node<V> node_type;
  typedef rbtree_iterator<V> iterator;
  typedef V value_type;
  typedef K key_type;
  typedef E extract_key;
  C mCompare;
  rbtree_node_base mAnchor;
  size_t mnSize;
  allocator mAllocator;

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
  pair<iterator, bool> DoInsertValue(const value_type& value, true_type);
  iterator DoInsertValue(iterator position, const value_type& value, true_type);
  pair<iterator, bool> insert(const value_type& value) { return DoInsertValue(value, true_type()); }
  iterator insert(iterator position, const value_type& value) { return DoInsertValue(position, value, true_type()); }
  void insert(const value_type* first, const value_type* last) {
    for (; first != last; ++first) DoInsertValue(*first, true_type());
  }
};

template <typename K, typename V, typename C, typename E>
void rbtree<K, V, C, E>::DoNuke(node_type* pNode) {
  while (pNode) {
    DoNuke((node_type*)pNode->mpNodeRight);
    node_type* const pNodeLeft = (node_type*)pNode->mpNodeLeft;
    DoFreeNode(pNode);
    pNode = pNodeLeft;
  }
}

template <typename K, typename V, typename C, typename E>
typename rbtree<K, V, C, E>::iterator rbtree<K, V, C, E>::find(const key_type& key) {
  extract_key extractKey;
  node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
  rbtree_node_base* pRangeEnd = &mAnchor;
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

template <typename K, typename V, typename C, typename E>
typename rbtree<K, V, C, E>::iterator rbtree<K, V, C, E>::lower_bound(const key_type& key) {
  extract_key extractKey;
  node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
  rbtree_node_base* pRangeEnd = &mAnchor;
  while (pCurrent) {
    if (!mCompare(extractKey(pCurrent->mValue), key)) {
      pRangeEnd = pCurrent;
      pCurrent = (node_type*)pCurrent->mpNodeLeft;
    } else
      pCurrent = (node_type*)pCurrent->mpNodeRight;
  }
  return iterator((node_type*)pRangeEnd);
}

template <typename K, typename V, typename C, typename E>
typename rbtree<K, V, C, E>::iterator
rbtree<K, V, C, E>::DoInsertValueImpl(node_type* pNodeParent, const value_type& value, bool bForceToLeft) {
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

template <typename K, typename V, typename C, typename E>
pair<typename rbtree<K, V, C, E>::iterator, bool>
rbtree<K, V, C, E>::DoInsertValue(const value_type& value, true_type) {
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
      return pair<iterator, bool>(itResult, true);
    }
  }
  if (mCompare(extractKey(pLowerBound->mValue), extractKey(value))) {
    const iterator itResult(DoInsertValueImpl(pParent, value, false));
    return pair<iterator, bool>(itResult, true);
  }
  return pair<iterator, bool>(iterator(pLowerBound), false);
}

template <typename K, typename V, typename C, typename E>
typename rbtree<K, V, C, E>::iterator
rbtree<K, V, C, E>::DoInsertValue(iterator position, const value_type& value, true_type) {
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
    const pair<iterator, bool> itResult(DoInsertValue(value, true_type()));
    return itResult.first;
  }
  if (mnSize && mCompare(extractKey(((node_type*)mAnchor.mpNodeRight)->mValue), extractKey(value)))
    return DoInsertValueImpl((node_type*)mAnchor.mpNodeRight, value, false);
  const pair<iterator, bool> itResult(DoInsertValue(value, true_type()));
  return itResult.first;
}

template <typename K, typename T, typename C = less<K> >
class map : public rbtree<K, pair<const K, T>, C, use_first<pair<const K, T> > > {
 public:
  typedef rbtree<K, pair<const K, T>, C, use_first<pair<const K, T> > > base_type;
  typedef typename base_type::iterator iterator;
  typedef pair<const K, T> value_type;
  T& operator[](const K& key) {
    iterator itLower(this->lower_bound(key));
    if ((itLower == this->end()) || this->mCompare(key, (*itLower.mpNode).mValue.first))
      itLower = base_type::insert(itLower, value_type(key, T()));
    return itLower.mpNode->mValue.second;
  }
};
template <typename V> inline bool operator==(const rbtree_iterator<V>& a, const rbtree_iterator<V>& b) {
  return a.mpNode == b.mpNode;
}
template <typename K, typename C = less<K> >
class set : public rbtree<K, K, C, use_self<K> > {
 public:
  typedef rbtree<K, K, C, use_self<K> > base_type;
};
}  // namespace eastl

struct Key3 { uint16_t a, b, c; };
inline bool operator<(const Key3& x, const Key3& y) {
  return (x.a < y.a) || (!(y.a < x.a) && (x.b < y.b)) || (!(y.a < x.a) && !(y.b < x.b) && (x.c < y.c));
}
struct cKeyedBuffers {
  eastl::vector<uint8_t> mA;
  uint32_t mFlags;
  eastl::vector<uint8_t> mB;
};

typedef eastl::set<uint16_t> U16Set;
typedef eastl::map<Key3, uint32_t> Key3Map;
typedef eastl::set<eastl::wstring> WStringSet;
typedef eastl::map<eastl::wstring, int> WStringIntMap;
typedef eastl::map<uint32_t, cKeyedBuffers> BufferMap;
typedef U16Set::base_type U16Tree;
typedef Key3Map::base_type Key3Tree;
typedef WStringSet::base_type WStringTree;
typedef WStringIntMap::base_type WStringIntTree;
typedef BufferMap::base_type BufferTree;

// @ 0x005e9440
template U16Tree::iterator U16Tree::DoInsertValueImpl(node_type*, const value_type&, bool);
// @ 0x005e94c0
template Key3Tree::iterator Key3Tree::DoInsertValueImpl(node_type*, const value_type&, bool);
// @ 0x005e9550
template eastl::wstring* eastl::uninitialized_relocate_commit<eastl::wstring>(eastl::wstring*, eastl::wstring*, eastl::wstring*);
// @ 0x005e95a0
template eastl::pair<Key3Tree::iterator, bool> Key3Tree::DoInsertValue(const value_type&, eastl::true_type);
// @ 0x005e96a0
template eastl::basic_string<char, eastl::allocator>::basic_string(const char*, size_t, const eastl::allocator&);
// @ 0x005e96f0
template WStringTree::iterator WStringTree::find(const eastl::wstring&);
// @ 0x005e97e0
template WStringIntTree::iterator WStringIntTree::lower_bound(const eastl::wstring&);
// @ 0x005e9890
template eastl::pair<U16Tree::iterator, bool> U16Tree::DoInsertValue(const value_type&, eastl::true_type);
// @ 0x005e9930
template WStringTree::iterator WStringTree::DoInsertValueImpl(node_type*, const value_type&, bool);
// @ 0x005e99c0
template eastl::wstring* eastl::copy_backward<eastl::wstring*, eastl::wstring*>(eastl::wstring*, eastl::wstring*, eastl::wstring*);
// @ 0x005e9a00
template void eastl::vector<wchar_t>::DoInsertValue(wchar_t*, const wchar_t&);
// @ 0x005e9b10
template eastl::pair<WStringTree::iterator, bool> WStringTree::DoInsertValue(const value_type&, eastl::true_type);
// @ 0x005e9c40
template Key3Tree::iterator Key3Tree::DoInsertValue(iterator, const value_type&, eastl::true_type);
// @ 0x005e9d50
template WStringIntTree::iterator WStringIntTree::DoInsertValueImpl(node_type*, const value_type&, bool);
// @ 0x005e9de0
template eastl::pair<WStringIntTree::iterator, bool> WStringIntTree::DoInsertValue(const value_type&, eastl::true_type);
// @ 0x005e9f10
template void WStringTree::insert(const value_type*, const value_type*);
// @ 0x005e9f50
template eastl::vector<bool>::vector(size_t, const eastl::sp_vector_allocator&);
// @ 0x005e9fb0
template void BufferTree::DoNuke(node_type*);
// @ 0x005ea010
template void WStringTree::clear();
// @ 0x005ea040
template uint32_t& Key3Map::operator[](const Key3&);
// @ 0x005ea0d0
template WStringIntTree::iterator WStringIntTree::DoInsertValue(iterator, const value_type&, eastl::true_type);
// @ 0x005ea200
template void eastl::vector<eastl::wstring>::DoInsertFromIterator(eastl::wstring*, const eastl::wstring*, const eastl::wstring*, eastl::iterator_tag);
