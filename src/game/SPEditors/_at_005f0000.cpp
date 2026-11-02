// src/game/SPEditors/_at_005f0000.cpp -- migrated from slice(s) s005f07e0 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_005f0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Messaging/Server.h"
#include "SP/cCollectableItems.h"
#include "SP/cICameraManager.h"
#include "SP/cISPCreatureAnimWorld.h"
#include "SP/cISPPaletteItemUI.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorEconomy.h"
#include "SP/cSPPaletteInfo.h"
#include "SP/cSPPaletteItem.h"
#include "SP/cSPPaletteItemRollover.h"
#include "SP/cSPPaletteItemUI.h"
#include "SP/cSPSwatch.h"
#include "cSPUILayout.h"
#include "SP/cString.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380
#include <new>

// ---- items of slice s005f07e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);  // 0x00f473a0
#define EASTL_ALLOCATOR_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define PV(n) virtual void pv##n();
namespace EA {
template <typename T>
class AutoRefCount_s005f_07e0 {
 public:
  T* mpObject;
  AutoRefCount_s005f_07e0() : mpObject(0) {}
  AutoRefCount_s005f_07e0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s005f_07e0(const AutoRefCount_s005f_07e0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005f_07e0() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005f_07e0& operator=(T* p) {
    if (p != mpObject) {
      T* const pTemp = mpObject;
      if (p)
        p->AddRef();
      mpObject = p;
      if (pTemp)
        pTemp->Release();
    }
    return *this;
  }
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
template <typename T>
class RefCountTemplate_s005f_07e0 {
 public:
  RefCountTemplate_s005f_07e0() : mRefCount(0) {}
  virtual ~RefCountTemplate_s005f_07e0() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005f_07e0 {
 public:
  RefCountVTemplate_s005f_07e0() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005f_07e0() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005f_07e0 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};  // namespace COM
}
}
namespace EA {
namespace ResourceMan {
class Key_s005f_07e0 { public:
  unsigned int mInstance, mType, mGroup;
  Key_s005f_07e0() : mInstance(0), mType(0), mGroup(0) {}
  Key_s005f_07e0(unsigned int instance, unsigned int type, unsigned int group)
      : mInstance(instance), mType(type), mGroup(group) {}
};  // namespace ResourceMan
}
}
namespace EA {
class RectT_s005f_07e0 { public:
  float left, top, right, bottom;
  RectT_s005f_07e0(const RectT_s005f_07e0& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
};
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_07e0;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005f_07e0 : public COM::IUnknown32_s005f_07e0 {
 public:
  PV(3)
  virtual IWindow_s005f_07e0* GetParent();                     // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual uint32_t GetFlags();                      // +0x28
  PV(11) PV(12) PV(13)
  virtual const RectT_s005f_07e0& GetRealArea();               // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
  virtual void SetShadeColor(uint32_t color);       // +0x5c
  PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);       // +0x7c
  virtual void SetCaption(const wchar_t* caption);  // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45)
  PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s005f_07e0* proc);     // +0x104
  virtual void RemoveWinProc(IWinProc_s005f_07e0* proc);  // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class Message_s005f_07e0 { public:
  uint32_t pad0[2];
  uint32_t mEventType;  // +0x8
  uint32_t mControlID;  // +0xc
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_07e0 : public COM::IUnknown32_s005f_07e0 {
 public:
  virtual int GetEventFlags();
  virtual bool DoMessage(IWindow_s005f_07e0* window, const Message_s005f_07e0& message) = 0;
};
}
}
using EA::AutoRefCount_s005f_07e0;
using EA::ResourceMan::Key_s005f_07e0;
using EA::UTFWin::IWindow_s005f_07e0;
using EA::UTFWin::IWinProc_s005f_07e0;
using EA::UTFWin::Message_s005f_07e0;
namespace SP {
class cSPPaletteItem_s005f_07e0 : public EA::RefCountVTemplate_s005f_07e0<int>, public EA::COM::IUnknown32_s005f_07e0 {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  Key_s005f_07e0 mItemKey;       // +0xc
  Key_s005f_07e0 mThumbnailKey;  // +0x18
};
}
namespace SP {
class cCollectableItems_s005f_07e0 {
 public:
  void Lock(uint64_t id);               // 0x00596e10
  void Unlock(uint64_t id, int flags);  // 0x00596da0
};
}
namespace SP {
class cSPEditorEconomy_s005f_07e0 {
 public:
  PV(0) PV(1)
  virtual bool IsItemAvailable(const Key_s005f_07e0* key);    // +0x8
  virtual bool CanAfford(int currency, int cost);  // +0xc
};
}
namespace SP {
struct cSPPaletteInfo_s005f_07e0 : public EA::RefCountTemplate_s005f_07e0<int> {
  cSPEditorEconomy_s005f_07e0* mEconomy;            // +0x8
  void* mTheme;                          // +0xc
  cCollectableItems_s005f_07e0* mCollectableItems;  // +0x10
  cCollectableItems_s005f_07e0* GetCollectableItems() const { return mCollectableItems; }
};
}
namespace SP {
class cSPSwatch_s005f_07e0 : public IWinProc_s005f_07e0 {
 public:
  cSPSwatch_s005f_07e0();  // 0x005f6bd0
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual bool DoMessage(IWindow_s005f_07e0* window, const Message_s005f_07e0& message);
  void Init(const Key_s005f_07e0& key, IWindow_s005f_07e0* window, int a, int b, int c, int d, int e);  // 0x005f4f80
  void SetBackground(uint32_t id);       // 0x005f2270
  void SetShowName(bool show);           // 0x005f2260
  void SetPlannerMode(bool on);          // 0x005f21c0
  void SetImage(uint32_t id, bool on);   // 0x005f2d00
  PV(5) PV(6)
  virtual void Shutdown();                   // +0x1c
  virtual void Update(uint32_t deltaTime);   // +0x20
  virtual void SetModelKey(const Key_s005f_07e0* key);  // +0x24 0x005f4080
  uint32_t pad4[0x5d];
  uint32_t mID;  // +0x178
};
}
namespace SP {
class cSPRolloverData : public EA::RefCountTemplate_s005f_07e0<int> {};
}
template <> EA::AutoRefCount_s005f_07e0<SP::cSPRolloverData>& EA::AutoRefCount_s005f_07e0<SP::cSPRolloverData>::operator=(SP::cSPRolloverData* p);
namespace SP {
class cSPPaletteItemRollover_s005f_07e0 {
 public:
  void Setup(cSPPaletteItem_s005f_07e0* item, cSPPaletteInfo_s005f_07e0* info, cSPRolloverData* data, bool showCost);  // 0x005ee480
  void SetMode(int mode);  // 0x005ed320
  void Hide();             // 0x005ed6c0
  void SetPositionAndOffset(float x, float y, float offsetX, float offsetY);  // 0x008283a0
};
}
namespace SP {
class cSPSwatchManager;
}
namespace eastl {
struct rbtree_node_base_s005f_07e0 {
  rbtree_node_base_s005f_07e0* mpNodeRight;
  rbtree_node_base_s005f_07e0* mpNodeLeft;
  rbtree_node_base_s005f_07e0* mpNodeParent;
  char mColor;
};  // namespace eastl
}
extern "C++" void RBTreeInsert(eastl::rbtree_node_base_s005f_07e0* pNode, eastl::rbtree_node_base_s005f_07e0* pNodeParent,
                               eastl::rbtree_node_base_s005f_07e0* pNodeAnchor, int insertionSide);  // 0x009216a0
eastl::rbtree_node_base_s005f_07e0* RBTreeIncrement(const eastl::rbtree_node_base_s005f_07e0* pNode);       // 0x00921580
void RBTreeErase(eastl::rbtree_node_base_s005f_07e0* pNode, eastl::rbtree_node_base_s005f_07e0* pNodeAnchor);  // 0x00921880
void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                               const char* file, int line);
namespace eastl {
struct true_type {};
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s005f_07e0 {
  T1 first;
  T2 second;
  pair_s005f_07e0(const T1& x, const T2& y) : first(x), second(y) {}
};
}
namespace eastl {
template <typename K, typename V>
struct rbtree_node_s005f_07e0 : public rbtree_node_base_s005f_07e0 {
  pair_s005f_07e0<const K, V> mValue;
};
}
namespace eastl {
template <typename K, typename V>
struct rbtree_iterator_s005f_07e0 {
  rbtree_node_s005f_07e0<K, V>* mpNode;
  rbtree_iterator_s005f_07e0() : mpNode(0) {}
  explicit rbtree_iterator_s005f_07e0(rbtree_node_s005f_07e0<K, V>* p) : mpNode(p) {}
  rbtree_iterator_s005f_07e0(const rbtree_iterator_s005f_07e0& x) : mpNode(x.mpNode) {}
  rbtree_iterator_s005f_07e0& operator++() {
    mpNode = (rbtree_node_s005f_07e0<K, V>*)RBTreeIncrement(mpNode);
    return *this;
  }
  bool operator!=(const rbtree_iterator_s005f_07e0& x) const { return mpNode != x.mpNode; }
  bool operator==(const rbtree_iterator_s005f_07e0& x) const { return mpNode == x.mpNode; }
  pair_s005f_07e0<const K, V>* operator->() const { return &mpNode->mValue; }
  rbtree_iterator_s005f_07e0 operator++(int) {
    rbtree_iterator_s005f_07e0 temp(*this);
    mpNode = (rbtree_node_s005f_07e0<K, V>*)RBTreeIncrement(mpNode);
    return temp;
  }
};
}
namespace eastl {
class allocator_s005f_07e0 {
 public:
  allocator_s005f_07e0(const char* = 0) {}
};
}
namespace eastl {
template <typename K, typename V>
class rbtree_s005f_07e0 {
 public:
  typedef rbtree_node_s005f_07e0<K, V> node_type;
  typedef rbtree_iterator_s005f_07e0<K, V> iterator;
  typedef pair_s005f_07e0<const K, V> value_type;

  int mCompare;               // +0x0 (empty less<>)
  rbtree_node_base_s005f_07e0 mAnchor;   // +0x4
  unsigned int mnSize;        // +0x14
  allocator_s005f_07e0 mAllocator;       // +0x18

  rbtree_s005f_07e0() : mAnchor(), mnSize(0) { reset(); }
  ~rbtree_s005f_07e0() { DoNukeSubtree((node_type*)mAnchor.mpNodeParent); }
  void reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  void clear() {
    DoNukeSubtree((node_type*)mAnchor.mpNodeParent);
    reset();
  }
  iterator begin() { return iterator((node_type*)mAnchor.mpNodeLeft); }
  iterator end() { return iterator((node_type*)&mAnchor); }
  iterator find(const K& key);  // out of line (0x00e5c780)
  iterator lower_bound(const K& key) {
    node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
    node_type* pRangeEnd = (node_type*)&mAnchor;
    while (pCurrent) {
      if (!(pCurrent->mValue.first < key)) {
        pRangeEnd = pCurrent;
        pCurrent = (node_type*)pCurrent->mpNodeLeft;
      } else
        pCurrent = (node_type*)pCurrent->mpNodeRight;
    }
    return iterator(pRangeEnd);
  }
  iterator DoInsertValue(iterator position, const value_type& value, true_type);  // out of line
  iterator insert(iterator position, const value_type& value) {
    return DoInsertValue(position, value, true_type());
  }
  V& operator[](const K& key) {
    iterator itLower(lower_bound(key));
    if ((itLower == end()) || (key < itLower->first))
      itLower = insert(itLower, value_type(key, V()));
    return itLower->second;
  }
  void DoNukeSubtree(node_type* pNode);  // out of line

  node_type* DoCreateNode(const value_type& value) {
    node_type* const pNode = (node_type*)EASTL_allocator_allocate(
        sizeof(node_type), "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    ::new (&pNode->mValue) value_type(value);
    return pNode;
  }
  void DoFreeNode(node_type* pNode) {
    pNode->mValue.~value_type();
    EASTL_allocator_deallocate(pNode);
  }
  iterator DoInsertValueImpl(rbtree_node_base_s005f_07e0* pNodeParent, const value_type& value, bool bForceToLeft);
  iterator erase(iterator position) {
    const iterator iErase(position);
    --mnSize;
    ++position;
    RBTreeErase(iErase.mpNode, &mAnchor);
    DoFreeNode(iErase.mpNode);
    return position;
  }
  unsigned int erase(const K& key);
};
}
namespace eastl {
template <typename K, typename V>
typename rbtree_s005f_07e0<K, V>::iterator rbtree_s005f_07e0<K, V>::DoInsertValueImpl(rbtree_node_base_s005f_07e0* pNodeParent,
                                                                 const value_type& value,
                                                                 bool bForceToLeft) {
  int side;
  if (bForceToLeft || (pNodeParent == &mAnchor) ||
      (value.first < ((node_type*)pNodeParent)->mValue.first))
    side = 0;
  else
    side = 1;
  node_type* const pNodeNew = DoCreateNode(value);
  RBTreeInsert(pNodeNew, pNodeParent, &mAnchor, side);
  mnSize++;
  return iterator(pNodeNew);
}
}
namespace eastl {
template <typename K, typename V>
unsigned int rbtree_s005f_07e0<K, V>::erase(const K& key) {
  iterator it(find(key));
  if (it != end()) {
    erase(it);
    return 1;
  }
  return 0;
}
}
typedef eastl::rbtree_s005f_07e0<unsigned int, AutoRefCount_s005f_07e0<SP::cSPSwatch_s005f_07e0> > SwatchIDMap;
typedef eastl::rbtree_s005f_07e0<AutoRefCount_s005f_07e0<SP::cSPSwatch_s005f_07e0>, float> SwatchFloatMap;
template <> SwatchIDMap::iterator SwatchIDMap::erase(SwatchIDMap::iterator position);
template float& SwatchFloatMap::operator[](const AutoRefCount_s005f_07e0<SP::cSPSwatch_s005f_07e0>&);
namespace SP {
class cICameraManager_s005f_07e0 {
 public:
  PV(0) PV(1)
  virtual int AddRef();   // +0x8
  virtual int Release();  // +0xc
  virtual void SetName(const char* name);  // +0x10
  virtual void Shutdown();                 // +0x14
  PV(6)
  virtual void* GetActiveCamera();         // +0x1c
  virtual void RegisterCamera(uint32_t id, void* (*factory)());  // +0x20
  PV(9)
  virtual void Initialize();               // +0x28
  virtual void Update(uint32_t deltaTime);  // +0x2c
};
}
namespace SP {
class cSPPaletteItemRolloverRC {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Initialize();  // +0x1c
  PV(8)
  virtual void Shutdown();    // +0x24
};
}
namespace SP {
class cISPCreatureAnimWorld_s005f_07e0 {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Initialize(int renderer, bool a, bool b, int c, int d);  // +0x1c
  virtual void Shutdown();                                              // +0x20
  virtual void Update(float deltaTime, int flags);                     // +0x24
};
}
namespace SP {
class cSPUICursorManager {
 public:
  void RemoveCursor(uint32_t id);  // 0x008024e0
};
}
namespace SP {
cSPUICursorManager* CursorManager();  // 0x0067cab0
}
namespace SP {
class cSPSwatchManager : public EA::RefCountTemplate_s005f_07e0<int> {
 public:
  cSPSwatchManager();
  ~cSPSwatchManager();
  void Shutdown();
  void Update(uint32_t deltaTime);
  void ReleaseSwatch(cSPSwatch_s005f_07e0* swatch);
  void SetSwatchTimeout(cSPSwatch_s005f_07e0* swatch, float timeout);
  cSPSwatch_s005f_07e0* CreateSwatch(cSPSwatch_s005f_07e0* swatch);
  cSPPaletteItemRollover_s005f_07e0* GetSwatchRollover();  // 0x0113ae10

  SwatchIDMap mIDToSwatchMap;                              // +0x8
  SwatchFloatMap mSwatchTimeouts;                          // +0x24
  uint32_t mCurrentID;                                     // +0x40
  AutoRefCount_s005f_07e0<cSPPaletteItemRolloverRC> mSwatchRollover;  // +0x44
  AutoRefCount_s005f_07e0<cSPPaletteItemRolloverRC> mModelRollover;   // +0x48
  AutoRefCount_s005f_07e0<cISPCreatureAnimWorld_s005f_07e0> mpCreatureAnimWorld; // +0x4c
  AutoRefCount_s005f_07e0<cICameraManager_s005f_07e0> mCameraManager;            // +0x50
};
}
namespace SP {
template <typename T>
inline const T& min_alt(const T& a, const T& b) { return (b < a) ? b : a; }
}
// ---- items of slice s005f07e0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C++" void RBTreeInsert(eastl::rbtree_node_base_s005f_07e0* pNode, eastl::rbtree_node_base_s005f_07e0* pNodeParent,
                               eastl::rbtree_node_base_s005f_07e0* pNodeAnchor, int insertionSide);  // 0x009216a0

// @ 0x005f07e0
namespace SP {
cSPSwatchManager::~cSPSwatchManager()
{}
}  // namespace SP

// @ 0x005f0850
namespace SP {
void cSPSwatchManager::Shutdown()
{
  CursorManager()->RemoveCursor(0x6493807);
  CursorManager()->RemoveCursor(0x648fbf1);
  mSwatchTimeouts.clear();
  mIDToSwatchMap.clear();
  if (mSwatchRollover) {
    mSwatchRollover->Shutdown();
    mSwatchRollover = 0;
  }
  if (mModelRollover) {
    mModelRollover->Shutdown();
    mModelRollover = 0;
  }
  if (mpCreatureAnimWorld) {
    mpCreatureAnimWorld->Shutdown();
    mpCreatureAnimWorld = 0;
  }
  if (mCameraManager) {
    mCameraManager->Shutdown();
    mCameraManager = 0;
  }
}
}  // namespace SP

// @ 0x005f0940
namespace SP {
void cSPSwatchManager::Update(uint32_t deltaTime)
{
  const float dt = deltaTime * 0.001f;
  for (SwatchFloatMap::iterator it = mSwatchTimeouts.begin(); it != mSwatchTimeouts.end();) {
    it->first->Update(deltaTime);
    if (it->second > dt)
      (it++)->second -= dt;
    else
      it = mSwatchTimeouts.erase(it);
  }
  if (mpCreatureAnimWorld) {
    const float kMaxStep = 0.2f;
    float step = deltaTime * 0.001;
    mpCreatureAnimWorld->Update(min_alt(step, kMaxStep), 0);
  }
  if (mCameraManager && mCameraManager->GetActiveCamera())
    mCameraManager->Update(deltaTime);
}
}  // namespace SP

// @ 0x005f0a60
namespace SP {
void cSPSwatchManager::ReleaseSwatch(cSPSwatch_s005f_07e0* swatch)
{
  SwatchIDMap::iterator it;
  it = mIDToSwatchMap.find(swatch->mID);
  if (it != mIDToSwatchMap.end() && it->second) {
    mSwatchTimeouts.erase(it->second);
    it->second->Shutdown();
    mIDToSwatchMap.erase(it);
  }
}
}  // namespace SP

// @ 0x005f0ac0
namespace SP {
cSPSwatchManager::cSPSwatchManager()
: mCurrentID(0) {}
}  // namespace SP

// @ 0x005f0b40
template AutoRefCount_s005f_07e0<SP::cSPSwatch_s005f_07e0>& SwatchIDMap::operator[](const unsigned int&)
;
