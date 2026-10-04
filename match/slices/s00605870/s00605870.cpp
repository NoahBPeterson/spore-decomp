// SP::cSPVerbTrayCollection (editor verb-icon tray collection) with its window->trays map,
// the SPORE-disc check helpers, a resource-cast helper, the FunctionalMatch constraint tree
// node helpers and the archive-folder path helper.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef unsigned int size_t;

#define PV(n) virtual void pv##n();

// EA allocator entry points (0x00F473A0 / 0x00F47380)
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
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  AutoRefCount& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  AutoRefCount& operator=(const AutoRefCount& x) { return operator=(x.mpObject); }
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

namespace COM {
class IUnknown32 {
 public:
  ~IUnknown32() {}
  virtual int AddRef();
  virtual int Release();
  PV(2)
  virtual void* Cast(uint32_t typeID);  // +0xc
};
}  // namespace COM

template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  T mRefCount;
};

namespace UTFWin {
class IWindow {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44)
  PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59)
  virtual IWindow* FindWindowByID(uint32_t controlID, bool recursive);  // +0xf0
};
}  // namespace UTFWin
}  // namespace EA

using EA::AutoRefCount;
using EA::UTFWin::IWindow;

// ---------------------------------------------------------------------------
// EASTL subset
namespace eastl {
struct allocator {};
struct sp_vector_allocator {
  uint32_t mData[2];
  sp_vector_allocator() {}
  void deallocate(void* p, size_t) {
    if (((uint32_t*)p)[-1]) operator delete[](p);
  }
};
struct true_type {};
struct false_type { false_type() {} };

template <typename T>
struct copy_result {
  T* mpResult;
  copy_result() {}
};
template <typename T, typename Tag>
copy_result<T> uninitialized_copy_impl(const T* first, const T* last, T* dest, Tag);  // 0x00829110
template <typename T>
inline T* uninitialized_copy_ptr(const T* first, const T* last, T* result) {
  const copy_result<T> r = uninitialized_copy_impl(first, last, result, false_type());
  return r.mpResult;
}

template <typename T>
struct VectorBase {
  T* mpBegin;                       // +0x0
  T* mpEnd;                         // +0x4
  T* mpCapacity;                    // +0x8
  sp_vector_allocator mAllocator;   // +0xc
  VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  VectorBase(size_t n, const sp_vector_allocator& allocator);  // 0x0066AEC0 (folded)
  ~VectorBase() {
    if (mpBegin) mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
  }
};

template <typename T>
class vector : public VectorBase<T> {
 public:
  vector() {}
  vector(const vector& x) : VectorBase<T>((size_t)(x.mpEnd - x.mpBegin), x.mAllocator) {
    this->mpEnd = uninitialized_copy_ptr(x.mpBegin, x.mpEnd, this->mpBegin);
  }
  ~vector() { DoDestroyValues(this->mpBegin, this->mpEnd); }
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
      DoInsertValue(this->mpEnd, value);
  }
};

template <typename T1, typename T2>
struct pair {
  T1 first;
  T2 second;
  pair(const T1& a, const T2& b) : first(a), second(b) {}
  pair(const pair& x) : first(x.first), second(x.second) {}
};

struct rbtree_node_base {
  rbtree_node_base* mpNodeRight;
  rbtree_node_base* mpNodeLeft;
  rbtree_node_base* mpNodeParent;
  char mColor;
};
template <typename T>
struct rbtree_node : public rbtree_node_base {
  T mValue;  // +0x10
};
template <typename T>
struct rbtree_iterator {
  typedef rbtree_node<T> node_type;
  node_type* mpNode;
  rbtree_iterator() : mpNode(0) {}
  explicit rbtree_iterator(const node_type* pNode) : mpNode((node_type*)pNode) {}
  rbtree_iterator(const rbtree_iterator& x) : mpNode(x.mpNode) {}
  T* operator->() const { return &mpNode->mValue; }
  bool operator==(const rbtree_iterator& x) const { return mpNode == x.mpNode; }
};
template <typename T>
struct less {
  bool operator()(const T& a, const T& b) const { return a < b; }
};

template <typename Key, typename T>
class map {
 public:
  typedef pair<const Key, T> value_type;
  typedef rbtree_node<value_type> node_type;
  typedef rbtree_iterator<value_type> iterator;

  less<Key> mCompare;         // +0x0
  rbtree_node_base mAnchor;   // +0x4
  uint32_t mnSize;            // +0x14
  allocator mAllocator;       // +0x18

  map() : mAnchor(), mnSize(0) { reset(); }
  ~map() { DoNukeSubtree((node_type*)mAnchor.mpNodeParent); }
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
    rbtree_node_base* pRangeEnd = &mAnchor;
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
}  // namespace eastl

// ---------------------------------------------------------------------------
namespace App {
class Property {
 public:
  bool* GetValueBool();  // 0x0041e920
  uint16_t pad[9];
  uint16_t mnType;       // +0x12  (1 = bool)
};
}  // namespace App

namespace SP {
class cPropertyList {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool HasProperty(uint32_t propertyID);                        // +0x1c
  PV(8)
  virtual bool GetProperty(uint32_t propertyID, App::Property*& result);  // +0x24
};
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** ppList);  // +0x2c
};
IPropertyManager* PropertyManager();
bool GetPropertyAsKey(const cPropertyList* list, uint32_t propertyID, ResourceKey& result);  // 0x6a1250
bool GetPropertyArrayKey(const cPropertyList* list, uint32_t propertyID, int& count, const ResourceKey*& keys);  // 0x6a0ae0

inline bool GetBoolProperty(cPropertyList* list, uint32_t propertyID, bool& result) {
  App::Property* pProp;
  if (list && list->GetProperty(propertyID, pProp) && pProp->mnType == 1) {
    result = *pProp->GetValueBool();
    return true;
  }
  return false;
}

class cSPVerbTrayCollection;

class cSPEditorVerbIconTray {
 public:
  cSPEditorVerbIconTray();
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Init(IWindow* window, ResourceKey trayKey, int justification, bool animate, int useDefaultImages);  // +0x1c
  virtual void Shutdown();                                                // +0x20
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
  AutoRefCount<EA::COM::IUnknown32> mpCollection;  // +0x11c (retail)
};

class cSPVerbTrayCollection : public EA::COM::IUnknown32, public EA::RefCountVTemplate<int> {
 public:
  typedef eastl::vector<AutoRefCount<cSPEditorVerbIconTray> > TrayVector;
  typedef eastl::map<AutoRefCount<IWindow>, TrayVector> TrayMap;

  cSPVerbTrayCollection();
  ~cSPVerbTrayCollection();
  PV(4) PV(5) PV(6) PV(7)
  virtual IWindow* GetTrayWindow(uint32_t controlID);                          // +0x20
  virtual void InitTrays(ResourceKey propList, const ResourceKey* trayKeys, int trayCount);  // +0x24
  virtual void Layout();                                                         // +0x28

  void SetValue(void* value);
  float GetTotalLevel();
  IWindow* FindWindow(uint32_t controlID);
  void SetVerbIconList(void* list);
  void Init(IWindow* parent, ResourceKey propList, const ResourceKey* trayKeys, int trayCount, bool ignoreKeyPress);
  void ShutdownTrays();

  TrayVector mVerbTrays;                  // +0xc
  AutoRefCount<IWindow> mWinParent;       // +0x20
  AutoRefCount<IWindow> mWinVerbTray;     // +0x24
  TrayMap mWindowsToVerbTrays;            // +0x28
  int mJustification;                     // +0x44
  bool mAnimateValues;                    // +0x48
  uint32_t mImageGroup;                   // +0x4c
  bool mIgnoreKeyPress;                   // +0x50
};
}  // namespace SP

using namespace SP;

// @ 0x605870
void cSPVerbTrayCollection::SetValue(void* value) {
  int count = (int)mVerbTrays.size();
  for (int i = 0; i < count; i++) mVerbTrays[i]->SetValue(value);
}

// @ 0x6058b0
float cSPVerbTrayCollection::GetTotalLevel() {
  float total = 0.0f;
  int count = (int)mVerbTrays.size();
  for (int i = 0; i < count; i++) total += mVerbTrays[i]->GetLevel();
  return total;
}

// @ 0x605900
IWindow* cSPVerbTrayCollection::FindWindow(uint32_t controlID) {
  if (controlID) {
    IWindow* window = mWinParent->FindWindowByID(controlID, true);
    if (window) return window;
  }
  return mWinVerbTray;
}

// @ 0x605940
void cSPVerbTrayCollection::SetVerbIconList(void* list) {
  if (list) {
    int count = (int)mVerbTrays.size();
    for (int i = 0; i < count; i++) mVerbTrays[i]->SetVerbIconList(list);
  }
}

// @ 0x605980
void cSPVerbTrayCollection::Init(IWindow* parent, ResourceKey propList, const ResourceKey* trayKeys, int trayCount, bool ignoreKeyPress) {
  mWinParent = parent;
  if (!mWinVerbTray) {
    mWinVerbTray = mWinParent->FindWindowByID(0x3ed7919, true);
    if (!mWinVerbTray) mWinVerbTray = mWinParent;
  }
  mIgnoreKeyPress = ignoreKeyPress;
  InitTrays(propList, trayKeys, trayCount);
  Layout();
}

// @ 0x605a60
template struct eastl::pair<const AutoRefCount<IWindow>, cSPVerbTrayCollection::TrayVector>;
// @ 0x605ac0  (pair(const T1&, const T2&), emitted by the instantiation above)

// @ 0x605b20
template <typename Key, typename T>
void eastl::map<Key, T>::DoNukeSubtree(node_type* pNode) {
  while (pNode) {
    DoNukeSubtree((node_type*)pNode->mpNodeRight);
    node_type* const pNodeLeft = (node_type*)pNode->mpNodeLeft;
    DoFreeNode(pNode);
    pNode = pNodeLeft;
  }
}
template void cSPVerbTrayCollection::TrayMap::DoNukeSubtree(cSPVerbTrayCollection::TrayMap::node_type*);

// @ 0x605cb0
cSPVerbTrayCollection::~cSPVerbTrayCollection() {}

// @ 0x605d10
void cSPVerbTrayCollection::ShutdownTrays() {
  int count = (int)mVerbTrays.size();
  for (int i = 0; i < count; i++) mVerbTrays[i]->Shutdown();
  if (mWinParent) mWinParent = 0;
  if (mWinVerbTray) mWinVerbTray = 0;
  mVerbTrays.clear();
}

// @ 0x605e60
cSPVerbTrayCollection::cSPVerbTrayCollection()
    : mJustification(0), mAnimateValues(true), mImageGroup(0xb5ac9c22), mIgnoreKeyPress(false) {}

// @ 0x605ee0
template <typename Key, typename T>
T& eastl::map<Key, T>::operator[](const Key& key) {
  iterator itLower(lower_bound(key));
  if ((itLower == end()) || mCompare(key, (*itLower.mpNode).mValue.first))
    itLower = insert(itLower, value_type(key, T()));
  return (*itLower.mpNode).mValue.second;
}
template cSPVerbTrayCollection::TrayVector& cSPVerbTrayCollection::TrayMap::operator[](const AutoRefCount<IWindow>&);

// @ 0x605f90
void cSPVerbTrayCollection::InitTrays(ResourceKey propListKey, const ResourceKey* trayKeys, int trayCount) {
  AutoRefCount<cPropertyList> propList;
  PropertyManager()->GetPropertyList(propListKey.mInstance, propListKey.mGroup, &propList.AsOutParam());

  ResourceKey justification;
  if (GetPropertyAsKey(propList, 0x4a213b2, justification)) mJustification = justification.mInstance;
  mAnimateValues = false;
  GetBoolProperty(propList, 0x4aa4002, mAnimateValues);
  mImageGroup = 0xb5ac9c22;
  ResourceKey imageGroup;
  if (GetPropertyAsKey(propList, 0x4b43aa3, imageGroup)) mImageGroup = imageGroup.mInstance;
  ResourceKey layoutKey;
  GetPropertyAsKey(propList, 0x4a20fe1, layoutKey);
  ResourceKey iconKey;
  GetPropertyAsKey(propList, 0x4acea45, iconKey);
  bool showIcons = true;
  if (propList->HasProperty(0x4bf1b5f)) GetBoolProperty(propList, 0x4bf1b5f, showIcons);

  const ResourceKey* keys;
  int count = 0;
  bool ok;
  if (propList->HasProperty(0x4aa3838)) {
    ok = GetPropertyArrayKey(propList, 0x4aa3838, count, keys);
  } else {
    keys = trayKeys;
    count = trayCount;
    ok = true;
  }
  if (count > 0 && ok) {
    mVerbTrays.resize(count);
    for (int i = 0; i < count; i++) {
      cSPEditorVerbIconTray* pTray = new ("Editor", 0, 0, 0, 0) cSPEditorVerbIconTray();
      AutoRefCount<cSPEditorVerbIconTray> tray(pTray);
      AutoRefCount<cPropertyList> trayProps;
      PropertyManager()->GetPropertyList(keys[i].mInstance, 0xaf028f41, &trayProps.AsOutParam());
      if (keys[i].mGroup)
        pTray->SetLayoutGroup(keys[i].mGroup);
      else if (layoutKey.mInstance)
        pTray->SetLayoutKey(layoutKey);
      if (iconKey.mInstance) pTray->SetIconKey(iconKey);
      if (propList->HasProperty(0x4c8b6b3)) {
        bool showLevel = false;
        GetBoolProperty(propList, 0x4c8b6b3, showLevel);
        pTray->SetShowLevel(showLevel);
      }
      if (propList->HasProperty(0x4c8b6ae)) {
        bool resize = false;
        GetBoolProperty(propList, 0x4c8b6ae, resize);
        pTray->SetResizeStyle(resize);
      }
      pTray->SetShowIcons(showIcons);
      pTray->SetIgnoreKeyPress(mIgnoreKeyPress);
      int useDefaultImages = 0;
      if (mImageGroup == 0xb5ac9c22) useDefaultImages = 1;
      IWindow* window = GetTrayWindow(keys[i].mType);
      pTray->mpCollection = (EA::COM::IUnknown32*)Cast(0xee3f516e);
      pTray->Init(window, keys[i], mJustification, mAnimateValues, useDefaultImages);
      mWindowsToVerbTrays[AutoRefCount<IWindow>(window)].push_back(tray);
      mVerbTrays[i] = tray;
    }
  }
}

// ---------------------------------------------------------------------------
// SPORE disc detection (copy protection).
extern "C" __declspec(dllimport) unsigned int __stdcall GetDriveTypeA(const char* root);
extern "C" __declspec(dllimport) int __stdcall GetVolumeInformationA(const char* root, char* name, unsigned long nameSize,
                                                                     unsigned long* serial, unsigned long* maxComponent,
                                                                     unsigned long* flags, char* fsName, unsigned long fsNameSize);
extern "C" __declspec(dllimport) int __stdcall GetDiskFreeSpaceExA(const char* dir, uint64_t* freeToCaller, uint64_t* total, uint64_t* totalFree);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLogicalDrives();
extern "C" __declspec(dllimport) int __cdecl strncmp(const char* a, const char* b, size_t n);

// @ 0x6064c0
bool IsSporeDisc(const char* root) {
  char decoded[8];
  uint64_t totalBytes;
  unsigned long flags;
  char volumeName[128];
  if (GetDriveTypeA(root) != 5 /*DRIVE_CDROM*/) return false;
  if (!GetVolumeInformationA(root, volumeName, 0x7f, 0, 0, &flags, 0, 0)) return false;
  char* d = decoded;
  for (const char* s = volumeName; *s; s++) *d++ = *s ^ 0x2a;
  *d = 0;
  if (strncmp(decoded, "yzexo", 6) != 0) return false;  // "SPORE" xor 0x2a
  if (!GetDiskFreeSpaceExA(root, 0, &totalBytes, 0)) return false;
  if (totalBytes < 0x80000000ull) return false;
  return true;
}

// @ 0x606590
bool FindSporeDisc(char* driveLetter, const char* hint) {
  if (hint && IsSporeDisc(hint)) {
    *driveLetter = *hint;
    return true;
  }
  unsigned long drives = GetLogicalDrives();
  char root[3] = {'C', ':', 0};
  unsigned int mask = 1;
  for (unsigned int i = 0; i < 26; i++, mask += mask) {
    if (drives & mask) {
      root[0] = (char)('A' + i);
      if (IsSporeDisc(root)) {
        *driveLetter = root[0];
        return true;
      }
    }
  }
  return false;
}

// @ 0x606610
int CheckSporeDisc(const char* hint) {
  char drive;
  return FindSporeDisc(&drive, hint) ? 0 : 2;
}

// ---------------------------------------------------------------------------
namespace EA {
namespace ResourceMan {
class IResourceManager {
 public:
  PV(0) PV(1) PV(2)
  virtual bool GetResource(const ResourceKey& key, void* result, int a, int b, int c, int d);  // +0xc
};
IResourceManager* GetManager();  // 0x8de1a0
}  // namespace ResourceMan
}  // namespace EA

// @ 0x606640
void* GetResourceAs30bdee3(const ResourceKey& key) {
  AutoRefCount<EA::COM::IUnknown32> resource;
  if (EA::ResourceMan::GetManager()->GetResource(ResourceKey(key.mInstance, 0x30bdee3, key.mGroup),
                                                 &resource.AsOutParam(), 0, 0, 0, 0)) {
    void* result = resource ? resource->Cast(0x30bdee3) : 0;
    return result;
  }
  return 0;
}

// ---------------------------------------------------------------------------
// FunctionalMatch constraint tree node: a Constraint plus a vector of child nodes.
namespace SP {
namespace FunctionalMatch {
struct Constraint {
  uint32_t mParameter;  // +0x0
  int mType;            // +0x4
  union {
    struct { int mMin, mMax; } mIntVal;
    struct { float mMin, mMax; } mFloatVal;
  };                    // +0x8
  Constraint(const Constraint& x)
      : mParameter(x.mParameter), mType(x.mType), mIntVal(x.mIntVal), mFloatVal(x.mFloatVal) {}
};
struct ConstraintNode {
  Constraint mConstraint;                  // +0x0
  eastl::vector<ConstraintNode> mChildren; // +0x10
  ConstraintNode(const ConstraintNode& x);
  ~ConstraintNode();
};
}  // namespace FunctionalMatch
}  // namespace SP
using SP::FunctionalMatch::ConstraintNode;

template <> eastl::vector<ConstraintNode>::vector(const vector& x);  // 0x004e38d0

// @ 0x6066f0
ConstraintNode::~ConstraintNode() {}

namespace eastl {
// @ 0x606730
template <typename T>
T* uninitialized_relocate_commit(T* first, T* last, T* dest) {
  for (; first != last; ++first, ++dest) first->~T();
  return dest;
}
template ConstraintNode* uninitialized_relocate_commit<ConstraintNode>(ConstraintNode*, ConstraintNode*, ConstraintNode*);
}  // namespace eastl

// ---------------------------------------------------------------------------
namespace SP {
class cString {
 public:
  cString(uint32_t instanceID, uint32_t groupID, const wchar_t* defaultText);  // 0x6b5770
  ~cString();                                                                  // 0x6b5240
  const wchar_t* c_str();                                                      // 0x6b55c0
  uint32_t pad[5];
};
}  // namespace SP
struct WStr {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  uint32_t mAllocator;
  WStr& append(const wchar_t* first, const wchar_t* last);                 // 0x429580
  WStr& replace(size_t position, size_t n, const wchar_t* p);              // 0x5f8f80
  size_t size() const { return (size_t)(mpEnd - mpBegin); }
  wchar_t back() const { return mpBegin[size() - 1]; }
  const wchar_t* c_str() const { return mpBegin; }
};
inline size_t wstrlen(const wchar_t* p) {
  const wchar_t* e = p;
  while (*e) e++;
  return (size_t)(e - p);
}
inline WStr& operator+=(WStr& s, const wchar_t* p) { return s.append(p, p + wstrlen(p)); }
extern const wchar_t kSlash[];                                     // 0x13fa030  L"/"
bool GetSpecialFolder(uint32_t folderID, WStr& path, int flags);   // 0x688830
bool CreateFolder(const wchar_t* path);                            // 0x932ae0

// @ 0x606790
bool GetArchiveFolder(WStr& path) {
  SP::cString archive(0x19f76d11, 0x6244eb0, L"Archive/");
  GetSpecialFolder(0xa0214b, path, 0);
  path += archive.c_str();
  if (path.back() == 0xff0f)
    path.replace(path.size() - 1, 1, kSlash);
  else if (path.back() != L'/')
    path += kSlash;
  if (CreateFolder(path.c_str())) return true;
  return false;
}

// @ 0x606880
ConstraintNode::ConstraintNode(const ConstraintNode& x) : mConstraint(x.mConstraint), mChildren(x.mChildren) {}
