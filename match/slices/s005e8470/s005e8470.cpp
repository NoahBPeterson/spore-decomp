// slice s005e8470 -- SP::cSPEditorVerbIconTray::SetVerbIconList,
// SP::cSPEditorVerbTrayCollection::LayoutCollection and two forwarding thunks, plus EASTL /
// EA::Random template instances emitted in the same TU (wstring helpers, eastl::search,
// rbtree find/lower_bound over uint16 key tuples, RandomUint32WeightedChoice).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <string.h>
#include <ctype.h>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount& operator=(T* p) {
    if (p != mpObject) {
      T* const pTemp = mpObject;
      if (p) p->AddRef();
      mpObject = p;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}

void* operator new[](unsigned int n, const char* name, int flags, unsigned int debugFlags,
                     const char* file, int line);  // 0x00f473a0
namespace eastl {
struct allocator {
  allocator() {}
  void* allocate(size_t n) {
    return operator new[](n, "Editor", 0, 0, "c:\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  }
};
}
int Compare(const wchar_t* p1, const wchar_t* p2, size_t n);  // 0x008f96a0

namespace eastl {
template <typename T> inline const T& min_alt(const T& a, const T& b) { return (b < a) ? b : a; }

template <typename FI1, typename FI2>
FI1 search(FI1 first1, FI1 last1, FI2 first2, FI2 last2) {
  if (first2 != last2) {
    FI2 temp2(first2);
    ++temp2;
    if (temp2 == last2) {
      while ((first1 != last1) && !(*first1 == *first2)) ++first1;
      return first1;
    } else {
      FI1 cur1(first1);
      FI2 p2;
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
  }
  return first1;
}
// @ 0x005e8ff0
template wchar_t* search<wchar_t*, const wchar_t*>(wchar_t*, wchar_t*, const wchar_t*, const wchar_t*);

template <typename II, typename T> inline II find(II first, II last, const T& value) {
  while ((first != last) && !(*first == value)) ++first;
  return first;
}
inline wchar_t CharToLower(wchar_t c) {
  if ((unsigned)c <= 0xff) return (wchar_t)tolower((uint8_t)c);
  return c;
}

}

namespace eastl {
struct false_type { false_type() {} };
template <typename It> struct generic_iterator {
  It mIterator;
  generic_iterator() : mIterator(0) {}
  explicit generic_iterator(It p) : mIterator(p) {}
  It base() const { return mIterator; }
};
template <typename T>
generic_iterator<T*> uninitialized_copy_impl(generic_iterator<T*> first, generic_iterator<T*> last, generic_iterator<T*> dest, false_type);  // 0x00829110
template <typename T> inline T* uninitialized_copy_ptr(T* first, T* last, T* result) {
  const generic_iterator<T*> i(uninitialized_copy_impl(generic_iterator<T*>(first), generic_iterator<T*>(last), generic_iterator<T*>(result), false_type()));
  return i.base();
}
struct rbtree_node_base {
  rbtree_node_base* mpNodeRight;
  rbtree_node_base* mpNodeLeft;
  rbtree_node_base* mpNodeParent;
  char mColor;
};
}
extern "C++" eastl::rbtree_node_base* RBTreeIncrement(const eastl::rbtree_node_base* pNode);  // 0x00921580
namespace eastl {
struct sp_vector_allocator {
  void* allocate(unsigned int n) {
    return ::operator new[](n, "Editor", 0, 0, "c:\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  }
  sp_vector_allocator() {}
  explicit sp_vector_allocator(const char*) {}
  void deallocate(void* p) {
    if (p && ((int*)p)[-1] != 0) EASTL_allocator_deallocate(p);
  }
};
template <typename T, typename A = sp_vector_allocator>
class vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;
  T* DoAllocate(unsigned int n) { return n ? (T*)mAllocator.allocate(n * sizeof(T)) : 0; }
  __forceinline vector(const vector& x) : mAllocator(x.mAllocator) {
    mpBegin = DoAllocate(x.size());
    mpEnd = mpBegin;
    mpCapacity = mpBegin + x.size();
    mpEnd = uninitialized_copy_ptr(x.mpBegin, x.mpEnd, mpBegin);
  }
  ~vector() {
    for (T* p = mpBegin; p < mpEnd; ++p) p->~T();
    mAllocator.deallocate(mpBegin);
  }
  bool empty() const { return mpBegin == mpEnd; }
  vector(unsigned int n, const T& value, const A& a = A("EASTL vector"));  // out of line
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  T& operator[](unsigned int i) { return mpBegin[i]; }
  const T& operator[](unsigned int i) const { return mpBegin[i]; }
};
extern uint32_t gEmptyString[1];
template <typename T, typename A = allocator>
struct VectorBase {
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;
  T* DoAllocate(size_t n) { return n ? (T*)mAllocator.allocate(n * sizeof(T)) : 0; }
  VectorBase(size_t n, const A& allocator);
};
template <typename T, typename A>
VectorBase<T, A>::VectorBase(size_t n, const A& allocator) : mAllocator(allocator) {
  mpBegin = DoAllocate(n);
  mpEnd = mpBegin;
  mpCapacity = mpBegin + n;
}

template <typename V> struct rbtree_node : public rbtree_node_base { V mValue; };
template <typename V> struct rbtree_iterator {
  rbtree_node<V>* mpNode;
  rbtree_iterator() : mpNode(0) {}
  explicit rbtree_iterator(const rbtree_node<V>* p) : mpNode((rbtree_node<V>*)p) {}
};
template <typename T> struct less {
  bool operator()(const T& a, const T& b) const { return a < b; }
};
template <typename K, typename C = eastl::less<K> >
class rbtree {
 public:
  typedef rbtree_node<K> node_type;
  typedef rbtree_iterator<K> iterator;
  C mCompare;
  rbtree_node_base mAnchor;
  size_t mnSize;
  iterator find(const K& key);
  iterator lower_bound(const K& key);
};
template <typename K, typename C>
typename rbtree<K, C>::iterator rbtree<K, C>::find(const K& key) {
  node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
  rbtree_node_base* pRangeEnd = &mAnchor;
  while (pCurrent) {
    if (!mCompare(pCurrent->mValue, key)) {
      pRangeEnd = pCurrent;
      pCurrent = (node_type*)pCurrent->mpNodeLeft;
    } else
      pCurrent = (node_type*)pCurrent->mpNodeRight;
  }
  if ((pRangeEnd != &mAnchor) && !mCompare(key, ((node_type*)pRangeEnd)->mValue))
    return iterator((node_type*)pRangeEnd);
  return iterator((node_type*)&mAnchor);
}
template <typename K, typename C>
typename rbtree<K, C>::iterator rbtree<K, C>::lower_bound(const K& key) {
  node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
  rbtree_node_base* pRangeEnd = &mAnchor;
  while (pCurrent) {
    if (!mCompare(pCurrent->mValue, key)) {
      pRangeEnd = pCurrent;
      pCurrent = (node_type*)pCurrent->mpNodeLeft;
    } else
      pCurrent = (node_type*)pCurrent->mpNodeRight;
  }
  return iterator((node_type*)pRangeEnd);
}

template <typename T, typename A = allocator>
class basic_string {
 public:
  typedef T value_type;
  typedef size_t size_type;
  enum { npos = -1 };
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;
  ~basic_string() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin) EASTL_allocator_deallocate(mpBegin);
  }
  const T* c_str() const { return mpBegin; }
  void AllocateSelf() {
    mpBegin = (T*)&gEmptyString[0];
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  size_type size() const { return (size_type)(mpEnd - mpBegin); }
  T& operator[](size_type n) { return mpBegin[n]; }
  void make_lower() {
    for (T* p = mpBegin; p < mpEnd; ++p) *p = (T)CharToLower(*p);
  }
  size_type find(const T* p, size_type position, size_type n) const {
    if ((position + n) <= (size_type)(mpEnd - mpBegin)) {
      const T* const pTemp = eastl::search(mpBegin + position, mpEnd, p, p + n);
      if ((pTemp != mpEnd) || (n == 0)) return (size_type)(pTemp - mpBegin);
    }
    return (size_type)npos;
  }
  size_type find(T c, size_type position = 0) const {
    if (position < (size_type)(mpEnd - mpBegin)) {
      const T* const pResult = eastl::find(mpBegin + position, mpEnd, c);
      if (pResult != mpEnd) return (size_type)(pResult - mpBegin);
    }
    return (size_type)npos;
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
}

namespace EA { namespace ResourceMan {
struct Key { uint32_t instance, type, group; };
} }

namespace EA { namespace Random {
class RandomLinearCongruential {
 public:
  uint32_t mnSeed;
  uint32_t RandomUint32Uniform(uint32_t nLimit);
  double RandomDoubleUniform();
};
template <typename Random>
inline double RandomDoubleUniform(Random& r, double limit) {
  const double value = r.RandomDoubleUniform() * limit;
  return (value >= limit) ? limit : ((value < 0) ? 0 : value);
}
template <typename Random>
uint32_t RandomUint32WeightedChoice(Random& r, uint32_t nLimit, float weights[]) {
  if (nLimit >= 2) {
    float weightSum = 0;
    for (uint32_t i = 0; i < nLimit; i++) {
      const float weight = weights[i];
      if (weight > 0) weightSum += weight;
    }
    if (weightSum > 0) {
      float value = (float)RandomDoubleUniform(r, weightSum);
      for (uint32_t j = 0; j < nLimit; j++) {
        const float weight = weights[j];
        if (weight > 0) {
          if (value < weight) return j;
          value -= weight;
        }
      }
    } else
      return r.RandomUint32Uniform(nLimit);
  }
  return nLimit - 1;
}
// @ 0x005e8ec0
template uint32_t RandomUint32WeightedChoice<RandomLinearCongruential>(RandomLinearCongruential&, uint32_t, float[]);
} }

namespace SP { extern EA::Random::RandomLinearCongruential sMathRandom; }  // 0x01601760


namespace EA {
template <typename T> struct RectT {
  T x1, y1, x2, y2;
  RectT() {}
  RectT(const RectT& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
};
namespace UTFWin {
class IWindow {
 public:
  virtual void pv00(); virtual void pv04(); virtual void pv08(); virtual void pv0c();
  virtual void pv10(); virtual void pv14(); virtual void pv18(); virtual void pv1c();
  virtual void pv20(); virtual void pv24(); virtual void pv28(); virtual void pv2c();
  virtual void pv30(); virtual void pv34(); virtual const RectT<float>& GetArea(); virtual void pv3c();
  virtual void pv40(); virtual void pv44(); virtual void pv48(); virtual void pv4c();
  virtual void pv50(); virtual void pv54(); virtual void pv58(); virtual void pv5c();
  virtual void pv60(); virtual void pv64(); virtual void pv68(); virtual void pv6c();
  virtual void pv70(); virtual void pv74(); virtual void pv78();
  virtual void SetFlag(int flag, bool value);  // +0x7c
  virtual void SetCaption(const wchar_t* text);  // +0x80
};
class IWinProc;
} }

class cSPUILayout {
 public:
  EA::UTFWin::IWindow* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0
};

struct cCaptionStyle {
  virtual void pv00(); virtual void pv04(); virtual void pv08(); virtual void pv0c();
  virtual void pv10(); virtual void pv14(); virtual void pv18();
  virtual void Refresh(int);  // +0x1c
};
struct cCaptionWindow {
  virtual void pv00(); virtual void pv04(); virtual void pv08();
  virtual void* Cast(uint32_t type);  // +0xc
  virtual void pv10(); virtual void pv14(); virtual void pv18(); virtual void pv1c();
  virtual void pv20(); virtual void pv24(); virtual void pv28(); virtual void pv2c();
  virtual void pv30(); virtual void pv34(); virtual void pv38(); virtual void pv3c();
  virtual void pv40(); virtual void pv44(); virtual void pv48(); virtual void pv4c();
  virtual void pv50(); virtual void pv54(); virtual void pv58(); virtual void pv5c();
  virtual void pv60(); virtual void pv64(); virtual void pv68(); virtual void pv6c();
  virtual void pv70(); virtual void pv74(); virtual void pv78(); virtual void pv7c();
  virtual void SetCaption(const wchar_t* text);  // +0x80
};

namespace SP {
struct cLevelScale {
  char pad[0x110];
  float mScale;  // +0x110
};
struct cVerbIconProps {
  char pad[0xc4];
  cLevelScale* mpScale;  // +0xc4
};
class cSPEditorVerbIconData {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void pv08();
  virtual void* Cast(uint32_t type);  // +0xc
  virtual void pv10(); virtual void pv14(); virtual void pv18(); virtual void pv1c();
  virtual eastl::wstring GetName(int which);  // +0x20
  char pad04[0xd];
  bool mShowZeroLevel;  // +0x11
  char pad12[6];
  float mLevel;  // +0x18
  char pad1c[4];
  float mMaxLevel;  // +0x20
  uint32_t mType;  // +0x24
  char pad28[0x58];
  int mPreSpecifiedArrayIndex;  // +0x80
};
inline cVerbIconProps* GetProps(cSPEditorVerbIconData* p) {
  return p ? (cVerbIconProps*)p->Cast(0x4ac90b5) : 0;
}

class cSPEditorVerbIcon {
 public:
  virtual void pv00(); virtual void pv04(); virtual void pv08(); virtual void pv0c();
  virtual void pv10(); virtual void pv14(); virtual void pv18(); virtual void pv1c();
  virtual void pv20(); virtual void pv24(); virtual void pv28(); virtual void pv2c();
  virtual void pv30(); virtual void pv34(); virtual void pv38();
  virtual bool HasLevel();  // +0x3c
  cSPEditorVerbIconData* GetData();  // 0x005e2d00
  float GetLevel(bool bDisplayed);   // 0x005e2860
  struct Data94 { char pad[0x94]; uint32_t mImage; uint32_t mChargeImage; };
};
struct cIconImageData {
  char pad[0x94];
  uint32_t mImage;        // +0x94
  uint32_t mChargeImage;  // +0x98
};

class cSPEditorVerbIconTray {
 public:
  virtual int AddRef(); virtual int Release(); virtual void pv08(); virtual void pv0c();
  virtual void pv10(); virtual void pv14(); virtual void pv18(); virtual void pv1c();
  virtual void pv20(); virtual void pv24(); virtual void pv28(); virtual void pv2c();
  virtual void pv30();
  virtual void SetLevel(float level);  // +0x34
  virtual bool UsesFullSize();  // +0x38
  virtual void Layout();  // +0x3c

  void SetVerbIconList(const eastl::vector<cSPEditorVerbIconData*>& iconList);
  cSPEditorVerbIcon* AddVerbIcon(int slot, cSPEditorVerbIconData* data);  // 0x005e8130
  void RemoveVerbIconInternal(int index);  // 0x005e60d0
  void SetLevelText(float level);  // 0x005e7030
  float GetWidth();   // 0x00c373e0
  float GetHeight();  // 0x005e5ef0
  void SetArea(const EA::RectT<float>& area);  // 0x005e63b0
  int GetAbilityIndex(uint32_t type) const {
    for (int i = 0; i < mAbilityCount; i++)
      if (mAbilityArray[i] == type) return i;
    return -1;
  }

  char pad04[8];
  eastl::vector<EA::AutoRefCount<cSPEditorVerbIcon> > mVerbIcons;  // +0x0c
  char pad1c[4];
  EA::AutoRefCount<cSPEditorVerbIconData> mOverrideData;  // +0x20
  cSPEditorVerbIcon* mpRepresentativeIcon;  // +0x24
  cSPUILayout* mpIconPanel;  // +0x28
  char pad2c[0xc];
  void* mImageGroup;  // +0x38
  cCaptionWindow* mpCaptionWindow;  // +0x3c
  char pad40[0x30];
  bool mbCollapsed;  // +0x70
  bool mbHideLevelText;  // +0x71
  char pad72[0x16];
  float mLevelTotal;  // +0x88
  char pad8c[6];
  bool mbUseMaxLevel;  // +0x92
  char pad93[5];
  bool mShowVerbIconWhenCollapsed;  // +0x98
  char pad99[0x2f];
  int mAbilityCount;  // +0xc8
  char padcc[0xc];
  bool mDoIconLevelsExist;  // +0xd8
  bool mOverrideAggregate;  // +0xd9
  char padda[6];
  uint32_t mAlertID;  // +0xe0
  bool mSetHaveChargeDials;  // +0xe4
  char pade5[7];
  uint32_t mOverrideType;  // +0xec
  char padf0[0x24];
  uint32_t* mAbilityArray;  // +0x114
};
}


void* GetImageKey(uint32_t image);                    // 0x00458de0
int SetImage(void* group, void* key, int index);       // 0x008068d0

namespace SP {
// @ 0x005e8470
void cSPEditorVerbIconTray::SetVerbIconList(const eastl::vector<cSPEditorVerbIconData*>& iconList) {
  eastl::vector<bool> used(mVerbIcons.size(), false);
  const int numUsed = (int)used.size();
  if (numUsed > 0) memset(&used[0], 0, numUsed);

  mLevelTotal = 0.0f;
  mDoIconLevelsExist = false;
  const int count = (int)iconList.size();
  bool bFoundOverride = false;
  for (int i = 0; i < count; i++) {
    cSPEditorVerbIconData* pData = iconList[i];
    if (!pData) continue;
    const uint32_t type = pData->mType;
    if (type) {
      int slot = GetAbilityIndex(type);
      if (slot != -1 && pData->mPreSpecifiedArrayIndex != -1) slot = pData->mPreSpecifiedArrayIndex;
      if (slot >= 0 && (pData->mLevel > 0.0f || (pData->mLevel == 0.0f && pData->mShowZeroLevel))) {
        cSPEditorVerbIcon* pIcon = AddVerbIcon(slot, pData);
        const bool bHasLevel = pIcon->HasLevel();
        mDoIconLevelsExist = mDoIconLevelsExist || bHasLevel;
        if (!mOverrideAggregate) {
          cVerbIconProps* pProps = GetProps(pIcon->GetData());
          if (pProps && pProps->mpScale)
            mLevelTotal += pIcon->GetLevel(false) * pProps->mpScale->mScale;
          else
            mLevelTotal += pIcon->GetLevel(false);
        }
        if (slot < numUsed) used[slot] = true;
      }
    }
    if (mOverrideAggregate && type == mOverrideType) {
      bFoundOverride = true;
      mOverrideData = pData;
      if (mbUseMaxLevel)
        mLevelTotal = mOverrideData->mMaxLevel;
      else {
        cVerbIconProps* pProps = GetProps(mOverrideData);
        if (pProps && pProps->mpScale)
          mLevelTotal = pProps->mpScale->mScale * mOverrideData->mLevel;
        else
          mLevelTotal = mOverrideData->mLevel;
      }
      SetLevel(mLevelTotal);
    }
  }

  for (int i = 0; i < numUsed; i++)
    if (!used[i] && mVerbIcons[i]) RemoveVerbIconInternal(i);

  if (mOverrideAggregate && !bFoundOverride) {
    mLevelTotal = 0.0f;
    SetLevel(0.0f);
  }

  mpRepresentativeIcon = 0;
  if (!mbCollapsed && mShowVerbIconWhenCollapsed && mImageGroup) {
    const int numIcons = (int)mVerbIcons.size();
    for (int i = 0; i < numIcons; i++) {
      cSPEditorVerbIcon* pIcon = mVerbIcons[i];
      if (pIcon && pIcon->GetData()) {
        uint32_t image;
        if (mSetHaveChargeDials)
          image = ((cIconImageData*)pIcon->GetData())->mChargeImage;
        else
          image = ((cIconImageData*)pIcon->GetData())->mImage;
        if (image) {
          mpRepresentativeIcon = pIcon;
          SetImage(mImageGroup, GetImageKey(image), -1);
          EA::UTFWin::IWindow* pWindow = mpIconPanel->FindWindowByID(0x5b6b561, true);
          if (pWindow) pWindow->SetFlag(1, mVerbIcons[i]->GetData()->mType == mAlertID);
          break;
        }
      }
    }
  }

  if (mpCaptionWindow) {
    cSPEditorVerbIconData* pSource = 0;
    if (mpRepresentativeIcon)
      pSource = mpRepresentativeIcon->GetData();
    else if (mOverrideAggregate && bFoundOverride)
      pSource = mOverrideData;
    if (pSource) {
      mpCaptionWindow->SetCaption(pSource->GetName(0).c_str());
      cCaptionStyle* pStyle = mpCaptionWindow ? (cCaptionStyle*)mpCaptionWindow->Cast(0xf15f4bd) : 0;
      pStyle->Refresh(0);
    }
  }

  if (!mbHideLevelText) SetLevelText(mLevelTotal);
  Layout();
}
}

namespace SP {
typedef eastl::vector<EA::AutoRefCount<cSPEditorVerbIconTray> > TrayVector;
struct TrayMapNode : public eastl::rbtree_node_base {
  EA::AutoRefCount<EA::UTFWin::IWindow> first;  // +0x10
  TrayVector second;                            // +0x14
};

enum {
  kLayoutVertical = 0x3eb432,
  kLayoutVerticalReverse = 0xe816f049,
  kLayoutHorizontal = 0x406ccc4a,
  kLayoutHorizontalReverse = 0xe864ba60,
  kJustifyFill = 0xb5ac9c22,
  kJustifyLeft = 0xfea10e68,
  kJustifyCenter = 0x72d447d1
};

class cSPVerbTrayCollection {
 public:
  void InitTrays(EA::ResourceMan::Key key, int a, int b);  // 0x00605f90
  void FUN_00605980(int a, EA::ResourceMan::Key key, int b, int c, int d);
};
class cSPEditorVerbTrayCollection : public cSPVerbTrayCollection {
 public:
  void Init(EA::ResourceMan::Key key, int a, int b);
  void FUN_005e8940(int a, EA::ResourceMan::Key key, int b, int c, int d);
  void LayoutCollection();
  char pad00[0x28];
  char mCompare[4];                   // +0x28 (mWindowsToVerbTrays)
  eastl::rbtree_node_base mAnchor;    // +0x2c
  unsigned int mnSize;                // +0x3c
  char pad40[4];
  uint32_t mLayoutStyle;              // +0x44
  char pad48[4];
  uint32_t mJustification;            // +0x4c
};

// @ 0x005e89f0
void cSPEditorVerbTrayCollection::LayoutCollection() {
  for (eastl::rbtree_node_base* pNode = mAnchor.mpNodeLeft; pNode != &mAnchor;
       pNode = RBTreeIncrement(pNode)) {
    TrayMapNode* const pEntry = (TrayMapNode*)pNode;
    TrayVector trays(pEntry->second);
    EA::UTFWin::IWindow* const pWindow = pEntry->first;
    if (!trays.empty()) {
      const EA::RectT<float> area = pWindow->GetArea();
      const int count = (int)trays.size();
      float y = 0.0f;
      float x = 0.0f;
      float totalWidth = 0.0f;
      float totalHeight = 0.0f;
      int i;

      cSPEditorVerbIconTray* pFirst = 0;
      for (i = 0; i < count; i++) {
        if (trays[i]->UsesFullSize()) {
          pFirst = trays[i];
          break;
        }
      }
      if (!pFirst) pFirst = trays[0];
      float firstWidth = pFirst->GetWidth();
      float firstHeight = pFirst->GetHeight();

      for (i = 0; i < count; i++) {
        totalWidth += trays[i]->GetWidth();
        totalHeight += trays[i]->GetHeight();
      }

      float slotHeight;
      if (mLayoutStyle == kLayoutVertical || mLayoutStyle == kLayoutVerticalReverse)
        slotHeight = (area.y2 - area.y1) / (float)count;
      else
        slotHeight = area.y2 - area.y1;
      float slotWidth;
      if (mLayoutStyle == kLayoutHorizontal || mLayoutStyle == kLayoutHorizontalReverse)
        slotWidth = (area.x2 - area.x1) / (float)count;
      else
        slotWidth = area.x2 - area.x1;

      if (mJustification == kJustifyCenter) {
        if (mLayoutStyle == kLayoutVertical || mLayoutStyle == kLayoutVerticalReverse)
          y = ((area.y2 - area.y1) - totalHeight) * 0.5f;
        else
          x = ((area.x2 - area.x1) - totalWidth) * 0.5f;
      }

      EA::RectT<float> rect;
      for (i = 0; i < count; i++) {
        cSPEditorVerbIconTray* pTray = trays[i];
        if (mJustification == kJustifyFill) {
          rect.x1 = x;
          rect.x2 = slotWidth + x;
          rect.y1 = y;
          rect.y2 = slotHeight + y;
          if (mLayoutStyle == kLayoutVertical || mLayoutStyle == kLayoutVerticalReverse)
            y = rect.y2;
          else
            x = rect.x2;
        } else if (mJustification == kJustifyLeft || mJustification == kJustifyCenter) {
          if (mLayoutStyle == kLayoutVertical || mLayoutStyle == kLayoutVerticalReverse) {
            const float height = pTray->GetHeight();
            float width = pTray->UsesFullSize() ? slotWidth : pTray->GetWidth();
            if (mLayoutStyle == kLayoutVerticalReverse) {
              rect.x2 = slotWidth;
              rect.x1 = slotWidth - width;
            } else {
              rect.x1 = x;
              rect.x2 = width + x;
            }
            rect.y1 = y;
            rect.y2 = height + y;
            y = rect.y2;
          } else {
            const float width = pTray->GetWidth();
            float height = pTray->UsesFullSize() ? slotHeight : pTray->GetHeight();
            if (mLayoutStyle == kLayoutHorizontalReverse)
              height = slotHeight;
            else {
              rect.y1 = y;
              height = height + y;
            }
            rect.y2 = height;
            rect.x1 = x;
            rect.x2 = width + x;
            x = rect.x2;
          }
        }
        pTray->SetArea(rect);
      }
    }
  }
}

// @ 0x005e8940
void cSPEditorVerbTrayCollection::FUN_005e8940(int a, EA::ResourceMan::Key key, int b, int c, int d) { FUN_00605980(a, key, b, c, d); }
// @ 0x005e8980
void cSPEditorVerbTrayCollection::Init(EA::ResourceMan::Key key, int a, int b) { InitTrays(key, a, b); }
}

struct Key2 { uint16_t a, b; };
inline bool operator<(const Key2& x, const Key2& y) { return (x.a < y.a) || (!(y.a < x.a) && (x.b < y.b)); }
struct Key3 { uint16_t a, b, c; };
inline bool operator<(const Key3& x, const Key3& y) {
  return (x.a < y.a) || (!(y.a < x.a) && (x.b < y.b)) || (!(y.a < x.a) && !(y.b < x.b) && (x.c < y.c));
}
// @ 0x005e90a0
template eastl::rbtree<uint16_t>::iterator eastl::rbtree<uint16_t>::find(const uint16_t&);
// @ 0x005e90f0
template bool eastl::less<Key2>::operator()(const Key2&, const Key2&) const;
// @ 0x005e9120
template bool eastl::less<Key3>::operator()(const Key3&, const Key3&) const;
// @ 0x005e91c0
template eastl::rbtree<Key2>::iterator eastl::rbtree<Key2>::lower_bound(const Key2&);
// @ 0x005e9200
template eastl::rbtree<Key3>::iterator eastl::rbtree<Key3>::lower_bound(const Key3&);
// @ 0x005e93c0
template eastl::rbtree<Key3>::iterator eastl::rbtree<Key3>::find(const Key3&);
// @ 0x005e92c0
template eastl::VectorBase<uint16_t>::VectorBase(size_t, const eastl::allocator&);
// @ 0x005e93a0
template void eastl::wstring::AllocateSelf();


struct cEntry12 { int id; int a; int b; };
bool GetEntries(int a, int b, int* count, cEntry12** entries);  // 0x006a0ae0
// @ 0x005e9320
void RandomizeDigits(eastl::wstring& s) {
  bool bFirst = true;
  for (int pos = s.find(L'#'); pos != -1; pos = s.find(L'#')) {
    s[pos] = (wchar_t)(L'0' + (bFirst ? (bFirst = false, SP::sMathRandom.RandomUint32Uniform(9) + 1) : SP::sMathRandom.RandomUint32Uniform(10)));
  }
}
// @ 0x005e8e20
bool HasEntry(int a, int b, int id) {
  cEntry12* entries = 0;
  int count;
  if (GetEntries(a, b, &count, &entries)) {
    for (int i = 0; i < count; i++)
      if (entries[i].id == id) return true;
  }
  return false;
}


// @ 0x005e8e80
template void eastl::wstring::make_lower();
// @ 0x005e9170
template eastl::wstring::size_type eastl::wstring::find(const wchar_t*, size_t, size_t) const;
// @ 0x005e9260
template int eastl::wstring::compare(const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*);
