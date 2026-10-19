// src/game/SPEditors/SPVerbTrayCollection.cpp -- migrated from slice(s) s00605870 by tools/migrate/rewrite.py
// Object file: SPEditors/SPVerbTrayCollection.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPVerbTrayCollection.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/Variant.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorVerbIconTray.h"
#include "SP/cString.h"

// ---- items of slice s00605870 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);
inline void* operator new(size_t, void* p) { return p; }
struct ResourceKey {
  uint32_t mInstance;  // +0x0
  uint32_t mType;      // +0x4
  uint32_t mGroup;     // +0x8
  ResourceKey() : mInstance(0), mType(0), mGroup(0) {}
  ResourceKey(uint32_t i, uint32_t t, uint32_t g) : mInstance(i), mType(t), mGroup(g) {}
};
namespace EA {
template <typename T>
class AutoRefCount_s0060_5870 {
 public:
  T* mpObject;
  AutoRefCount_s0060_5870() : mpObject(0) {}
  AutoRefCount_s0060_5870(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s0060_5870(const AutoRefCount_s0060_5870& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s0060_5870() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s0060_5870& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  AutoRefCount_s0060_5870& operator=(const AutoRefCount_s0060_5870& x) { return operator=(x.mpObject); }
  T*& AsOutParam() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return mpObject;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace EA {
namespace COM {
class IUnknown32_s0060_5870 {
 public:
  ~IUnknown32_s0060_5870() {}
  virtual int AddRef();
  virtual int Release();
  PV(2)
  virtual void* Cast(uint32_t typeID);  // +0xc
};  // namespace COM
}
}
namespace EA {
template <typename T>
class RefCountVTemplate_s0060_5870 {
 public:
  RefCountVTemplate_s0060_5870() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s0060_5870() {}
  T mRefCount;
};
}
namespace EA {
namespace UTFWin {
class IWindow_s0060_5870 {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44)
  PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59)
  virtual IWindow_s0060_5870* FindWindowByID(uint32_t controlID, bool recursive);  // +0xf0
};  // namespace UTFWin
}
}
using EA::AutoRefCount_s0060_5870;
using EA::UTFWin::IWindow_s0060_5870;
namespace eastl {
struct allocator_s0060_5870 {};
}
namespace eastl {
struct sp_vector_allocator_s0060_5870 {
  uint32_t mData[2];
  sp_vector_allocator_s0060_5870() {}
  void deallocate(void* p, size_t) {
    if (((uint32_t*)p)[-1]) operator delete[](p);
  }
};
}
namespace eastl {
struct true_type {};
}
namespace eastl {
struct false_type { false_type() {} };
}
namespace eastl {
template <typename T>
struct copy_result {
  T* mpResult;
  copy_result() {}
};
}
namespace eastl {
template <typename T, typename Tag>
copy_result<T> uninitialized_copy_impl(const T* first, const T* last, T* dest, Tag);  // 0x00829110
}
namespace eastl {
template <typename T>
inline T* uninitialized_copy_ptr(const T* first, const T* last, T* result) {
  const copy_result<T> r = uninitialized_copy_impl(first, last, result, false_type());
  return r.mpResult;
}
}
namespace eastl {
template <typename T>
struct VectorBase_s0060_5870 {
  T* mpBegin;                       // +0x0
  T* mpEnd;                         // +0x4
  T* mpCapacity;                    // +0x8
  sp_vector_allocator_s0060_5870 mAllocator;   // +0xc
  VectorBase_s0060_5870() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  VectorBase_s0060_5870(size_t n, const sp_vector_allocator_s0060_5870& allocator_s0060_5870);  // 0x0066AEC0 (folded)
  ~VectorBase_s0060_5870() {
    if (mpBegin) mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
  }
};
}
namespace eastl {
template <typename T>
class vector_s0060_5870 : public VectorBase_s0060_5870<T> {
 public:
  vector_s0060_5870() {}
  vector_s0060_5870(const vector_s0060_5870& x) : VectorBase_s0060_5870<T>((size_t)(x.mpEnd - x.mpBegin), x.mAllocator) {
    this->mpEnd = uninitialized_copy_ptr(x.mpBegin, x.mpEnd, this->mpBegin);
  }
  ~vector_s0060_5870() { DoDestroyValues(this->mpBegin, this->mpEnd); }
  void DoDestroyValues(T* first, T* last) {
    for (; first < last; ++first) first->~T();
  }
  size_t size() const { return (size_t)(this->mpEnd - this->mpBegin); }
  T& operator[](size_t n) { return this->mpBegin[n]; }
  T* erase(T* first, T* last);                     // 0x00E25BD0 (folded)
  void clear() { erase(this->mpBegin, this->mpEnd); }
  void resize(size_t n);                           // 0x005E77E0
  T* DoInsertValue(T* position, const T& value);   // 0x006650C0
  void push_back(const T& value) {
    if (this->mpEnd < this->mpCapacity)
      ::new (this->mpEnd++) T(value);
    else
      DoInsertValue(this->mpEnd, value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
  }
};
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s0060_5870 {
  T1 first;
  T2 second;
  pair_s0060_5870(const T1& a, const T2& b) : first(a), second(b) {}
  pair_s0060_5870(const pair_s0060_5870& x) : first(x.first), second(x.second) {}
};
}
namespace eastl {
struct rbtree_node_base_s0060_5870 {
  rbtree_node_base_s0060_5870* mpNodeRight;
  rbtree_node_base_s0060_5870* mpNodeLeft;
  rbtree_node_base_s0060_5870* mpNodeParent;
  char mColor;
};
}
namespace eastl {
template <typename T>
struct rbtree_node_s0060_5870 : public rbtree_node_base_s0060_5870 {
  T mValue;  // +0x10
};
}
namespace eastl {
template <typename T>
struct rbtree_iterator_s0060_5870 {
  typedef rbtree_node_s0060_5870<T> node_type;
  node_type* mpNode;
  rbtree_iterator_s0060_5870() : mpNode(0) {}
  explicit rbtree_iterator_s0060_5870(const node_type* pNode) : mpNode((node_type*)pNode) {}
  rbtree_iterator_s0060_5870(const rbtree_iterator_s0060_5870& x) : mpNode(x.mpNode) {}
  T* operator->() const { return &mpNode->mValue; }
  bool operator==(const rbtree_iterator_s0060_5870& x) const { return mpNode == x.mpNode; }
};
}
namespace eastl {
template <typename T>
struct less_s0060_5870 {
  bool operator()(const T& a, const T& b) const { return a < b; }
};
}
namespace eastl {
template <typename Key, typename T>
class map_s0060_5870 {
 public:
  typedef pair_s0060_5870<const Key, T> value_type;
  typedef rbtree_node_s0060_5870<value_type> node_type;
  typedef rbtree_iterator_s0060_5870<value_type> iterator;

  less_s0060_5870<Key> mCompare;         // +0x0
  rbtree_node_base_s0060_5870 mAnchor;   // +0x4
  uint32_t mnSize;            // +0x14
  allocator_s0060_5870 mAllocator;       // +0x18

  map_s0060_5870() : mAnchor(), mnSize(0) { reset(); }
  ~map_s0060_5870() { DoNukeSubtree((node_type*)mAnchor.mpNodeParent); }
  void reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  iterator end() { return iterator((node_type*)&mAnchor); }
  iterator DoInsertValue(iterator position, const value_type& value, true_type);  // 0x00605D90
  iterator insert(iterator position, const value_type& value) {
    return DoInsertValue(position, value, true_type());
  }
  iterator lower_bound(const Key& key) {
    node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
    rbtree_node_base_s0060_5870* pRangeEnd = &mAnchor;
    while (pCurrent) {
      if (!mCompare(pCurrent->mValue.first, key)) {
        pRangeEnd = pCurrent;
        pCurrent = (node_type*)pCurrent->mpNodeLeft;
      } else
        pCurrent = (node_type*)pCurrent->mpNodeRight;
    }
    return iterator((node_type*)pRangeEnd);
  }
  T& operator[](const Key& key);
  void DoFreeNode(node_type* pNode) {
    pNode->~node_type();
    operator delete[](pNode);
  }
  void DoNukeSubtree(node_type* pNode);
};
}
namespace App {
class Property {
 public:
  bool* GetValueBool();  // 0x0041e920
  uint16_t pad[9];
  uint16_t mnType;       // +0x12  (1 = bool)
};  // namespace App
}
namespace SP {
class cPropertyList_s0060_5870 {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool HasProperty(uint32_t propertyID);                        // +0x1c 0x006a2470
  PV(8)
  virtual bool GetProperty(uint32_t propertyID, App::Property*& result);  // +0x24
};
}
namespace SP {
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList_s0060_5870** ppList);  // +0x2c
};
}
namespace SP {
IPropertyManager* PropertyManager();
}
namespace SP {
bool GetPropertyAsKey(const cPropertyList_s0060_5870* list, uint32_t propertyID, ResourceKey& result);  // 0x6a1250
}
namespace SP {
bool GetPropertyArrayKey(const cPropertyList_s0060_5870* list, uint32_t propertyID, int& count, const ResourceKey*& keys);  // 0x6a0ae0
}
namespace SP {
inline bool GetBoolProperty(cPropertyList_s0060_5870* list, uint32_t propertyID, bool& result) {
  App::Property* pProp;
  if (list && list->GetProperty(propertyID, pProp) && pProp->mnType == 1) {
    result = *pProp->GetValueBool();
    return true;
  }
  return false;
}
}
namespace SP {
class cSPVerbTrayCollection_s0060_5870;
}
namespace SP {
class cSPEditorVerbIconTray_s0060_5870 {
 public:
  cSPEditorVerbIconTray_s0060_5870();
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Init(IWindow_s0060_5870* window, ResourceKey trayKey, int justification, bool animate, int useDefaultImages);  // +0x1c 0x005e7830
  virtual void Shutdown();                                                // +0x20 0x005e76b0
  void SetVerbIconList(void* list);              // 0x5e8470
  void SetValue(void* value);                    // 0x5e61b0
  float GetLevel();                              // 0x5e6390
  void SetLayoutGroup(uint32_t groupID);         // 0x5e5e80
  void SetLayoutKey(ResourceKey key);            // 0x5e5e60
  void SetIconKey(ResourceKey key);              // 0x5e5e40
  void SetShowLevel(bool b);                     // 0x5e5ec0
  void SetResizeStyle(bool b);                   // 0x5e5ea0
  void SetShowIcons(bool b);                     // 0x5e6170
  void SetIgnoreKeyPress(bool b);                // 0x5e5ee0
  char pad[0x11c - 4];
  AutoRefCount_s0060_5870<EA::COM::IUnknown32_s0060_5870> mpCollection;  // +0x11c (retail)
};
}
namespace SP {
class cSPVerbTrayCollection_s0060_5870 : public EA::COM::IUnknown32_s0060_5870, public EA::RefCountVTemplate_s0060_5870<int> {
 public:
  typedef eastl::vector_s0060_5870<AutoRefCount_s0060_5870<cSPEditorVerbIconTray_s0060_5870> > TrayVector;
  typedef eastl::map_s0060_5870<AutoRefCount_s0060_5870<IWindow_s0060_5870>, TrayVector> TrayMap;

  cSPVerbTrayCollection_s0060_5870();
  ~cSPVerbTrayCollection_s0060_5870();
  PV(4) PV(5) PV(6) PV(7)
  virtual IWindow_s0060_5870* GetTrayWindow(uint32_t controlID);                          // +0x20
  virtual void InitTrays(ResourceKey propList, const ResourceKey* trayKeys, int trayCount);  // +0x24 0x00605f90
  virtual void Layout();                                                         // +0x28

  void SetValue(void* value);
  float GetTotalLevel();
  IWindow_s0060_5870* FindWindow(uint32_t controlID);
  void SetVerbIconList(void* list);
  void Init(IWindow_s0060_5870* parent, ResourceKey propList, const ResourceKey* trayKeys, int trayCount, bool ignoreKeyPress);
  void ShutdownTrays();

  TrayVector mVerbTrays;                  // +0xc
  AutoRefCount_s0060_5870<IWindow_s0060_5870> mWinParent;       // +0x20
  AutoRefCount_s0060_5870<IWindow_s0060_5870> mWinVerbTray;     // +0x24
  TrayMap mWindowsToVerbTrays;            // +0x28
  int mJustification;                     // +0x44
  bool mAnimateValues;                    // +0x48
  uint32_t mImageGroup;                   // +0x4c
  bool mIgnoreKeyPress;                   // +0x50
};
}
template struct eastl::pair_s0060_5870<const AutoRefCount_s0060_5870<IWindow_s0060_5870>, SP::cSPVerbTrayCollection_s0060_5870::TrayVector>;
template void SP::cSPVerbTrayCollection_s0060_5870::TrayMap::DoNukeSubtree(SP::cSPVerbTrayCollection_s0060_5870::TrayMap::node_type*);
template SP::cSPVerbTrayCollection_s0060_5870::TrayVector& SP::cSPVerbTrayCollection_s0060_5870::TrayMap::operator[](const AutoRefCount_s0060_5870<IWindow_s0060_5870>&);
namespace SP {
namespace FunctionalMatch {
struct Constraint_s0060_5870 {
  uint32_t mParameter;  // +0x0
  int mType;            // +0x4
  union {
    struct { int mMin, mMax; } mIntVal;
    struct { float mMin, mMax; } mFloatVal;
  };                    // +0x8
  Constraint_s0060_5870(const Constraint_s0060_5870& x)
      : mParameter(x.mParameter), mType(x.mType), mIntVal(x.mIntVal), mFloatVal(x.mFloatVal) {}
};
}
}
namespace SP {
namespace FunctionalMatch {
struct ConstraintNode {
  Constraint_s0060_5870 mConstraint;                  // +0x0
  eastl::vector_s0060_5870<ConstraintNode> mChildren; // +0x10
  ConstraintNode(const ConstraintNode& x);
  ~ConstraintNode();
};
}
}
using SP::FunctionalMatch::ConstraintNode;
template <> eastl::vector_s0060_5870<ConstraintNode>::vector_s0060_5870(const vector_s0060_5870& x);  // 0x004e38d0
// ---- items of slice s00605870 end

// @ 0x00605980
void SP::cSPVerbTrayCollection_s0060_5870::Init(IWindow_s0060_5870* parent, ResourceKey propList, const ResourceKey* trayKeys, int trayCount, bool ignoreKeyPress)
{
  mWinParent = parent;
  if (!mWinVerbTray) {
    mWinVerbTray = mWinParent->FindWindowByID(0x3ed7919, true);
    if (!mWinVerbTray) mWinVerbTray = mWinParent;
  }
  mIgnoreKeyPress = ignoreKeyPress;
  InitTrays(propList, trayKeys, trayCount);
  Layout();
}

// @ 0x00605f90
void SP::cSPVerbTrayCollection_s0060_5870::InitTrays(ResourceKey propListKey, const ResourceKey* trayKeys, int trayCount)
{
  AutoRefCount_s0060_5870<SP::cPropertyList_s0060_5870> propList;
  SP::PropertyManager()->GetPropertyList(propListKey.mInstance, propListKey.mGroup, &propList.AsOutParam());

  ResourceKey justification;
  if (SP::GetPropertyAsKey(propList, 0x4a213b2, justification)) mJustification = justification.mInstance;
  mAnimateValues = false;
  SP::GetBoolProperty(propList, 0x4aa4002, mAnimateValues);
  mImageGroup = 0xb5ac9c22;
  ResourceKey imageGroup;
  if (SP::GetPropertyAsKey(propList, 0x4b43aa3, imageGroup)) mImageGroup = imageGroup.mInstance;
  ResourceKey layoutKey;
  SP::GetPropertyAsKey(propList, 0x4a20fe1, layoutKey);
  ResourceKey iconKey;
  SP::GetPropertyAsKey(propList, 0x4acea45, iconKey);
  bool showIcons = true;
  if (propList->HasProperty(0x4bf1b5f)) SP::GetBoolProperty(propList, 0x4bf1b5f, showIcons);

  const ResourceKey* keys;
  int count = 0;
  bool ok;
  if (propList->HasProperty(0x4aa3838)) {
    ok = SP::GetPropertyArrayKey(propList, 0x4aa3838, count, keys);
  } else {
    keys = trayKeys;
    count = trayCount;
    ok = true;
  }
  if (count > 0 && ok) {
    mVerbTrays.resize(count);
    for (int i = 0; i < count; i++) {
      SP::cSPEditorVerbIconTray_s0060_5870* pTray = new ("Editor", 0, 0, 0, 0) SP::cSPEditorVerbIconTray_s0060_5870();
      AutoRefCount_s0060_5870<SP::cSPEditorVerbIconTray_s0060_5870> tray(pTray);
      AutoRefCount_s0060_5870<SP::cPropertyList_s0060_5870> trayProps;
      SP::PropertyManager()->GetPropertyList(keys[i].mInstance, 0xaf028f41, &trayProps.AsOutParam());
      if (keys[i].mGroup)
        pTray->SetLayoutGroup(keys[i].mGroup);
      else if (layoutKey.mInstance)
        pTray->SetLayoutKey(layoutKey);
      if (iconKey.mInstance) pTray->SetIconKey(iconKey);
      if (propList->HasProperty(0x4c8b6b3)) {
        bool showLevel = false;
        SP::GetBoolProperty(propList, 0x4c8b6b3, showLevel);
        pTray->SetShowLevel(showLevel);
      }
      if (propList->HasProperty(0x4c8b6ae)) {
        bool resize = false;
        SP::GetBoolProperty(propList, 0x4c8b6ae, resize);
        pTray->SetResizeStyle(resize);
      }
      pTray->SetShowIcons(showIcons);
      pTray->SetIgnoreKeyPress(mIgnoreKeyPress);
      int useDefaultImages = 0;
      if (mImageGroup == 0xb5ac9c22) useDefaultImages = 1;
      IWindow_s0060_5870* window = GetTrayWindow(keys[i].mType);
      pTray->mpCollection = (EA::COM::IUnknown32_s0060_5870*)Cast(0xee3f516e);
      pTray->Init(window, keys[i], mJustification, mAnimateValues, useDefaultImages);
      mWindowsToVerbTrays[AutoRefCount_s0060_5870<IWindow_s0060_5870>(window)].push_back(tray);
      mVerbTrays[i] = tray;
    }
  }
}
