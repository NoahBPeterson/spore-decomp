// slice s005ef440 -- SP::cSPPaletteItemUIPlannerEdit (planner palette item: ctor/dtor, Init,
// SetLocked, HandleMessage, DoMessage, OffRollover), SP::SPSpineCollisionFilter (a copy of
// Havok's hkpGroupFilter: ctor/dtor, isCollisionEnabled overloads, layer helpers),
// SP::cSPSwatchManager::Init and three eastl::map<> helpers instantiated in the same TU.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);  // 0x00f473a0
#define EASTL_ALLOCATOR_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

#define PV(n) virtual void pv##n();

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  AutoRefCount& operator=(T* p) {
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

template <typename T>
class RefCountTemplate {
 public:
  RefCountTemplate() : mRefCount(0) {}
  virtual ~RefCountTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};

template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};

namespace COM {
class IUnknown32 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};
}  // namespace COM

namespace ResourceMan {
struct Key {
  unsigned int mInstance, mType, mGroup;
  Key() : mInstance(0), mType(0), mGroup(0) {}
  Key(unsigned int instance, unsigned int type, unsigned int group)
      : mInstance(instance), mType(type), mGroup(group) {}
};
}  // namespace ResourceMan

namespace UTFWin {
class IWinProc;
class IWindow : public COM::IUnknown32 {
 public:
  PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  PV(30)
  virtual void SetFlag(int flag, bool value);       // +0x7c
  virtual void SetCaption(const wchar_t* caption);  // +0x80
};

struct Message {
  uint32_t pad0[2];
  uint32_t mEventType;  // +0x8
  uint32_t mControlID;  // +0xc
};

class IWinProc : public COM::IUnknown32 {
 public:
  virtual int GetEventFlags();
  virtual bool DoMessage(IWindow* window, const Message& message) = 0;
};
}  // namespace UTFWin

namespace Messaging {
class IHandler {
 public:
  virtual ~IHandler() {}
  virtual bool HandleMessage(uint32_t messageID, void* message) = 0;
};
class IHandlerRC : public IHandler {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
};
class Server {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void MessageSend(uint32_t messageID, void* message, IHandler* handler);  // +0x14
  PV(6) PV(7) PV(8)
  virtual void AddHandler(IHandler* handler, uint32_t messageID);  // +0x24
};
void RemoveHandler(Server* server, IHandler* handler, const uint32_t* ids, uint32_t count,
                   int priority);  // 0x00571db0

struct AutoHandler {
  Server* mpServer;
  IHandler* mpHandler;
  const uint32_t* mpIdArray;
  uint32_t mnIdArrayCount;
  int mnPriority;
  AutoHandler() : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0), mnPriority(0) {}
  ~AutoHandler() { Clear(); }
  void Clear() {
    if (mpServer) {
      Server* const pServer = mpServer;
      mpServer = 0;
      RemoveHandler(pServer, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
    }
  }
};
}  // namespace Messaging
}  // namespace EA

using EA::AutoRefCount;
using EA::ResourceMan::Key;
using EA::UTFWin::IWindow;
using EA::UTFWin::IWinProc;
using EA::UTFWin::Message;

struct cDirectPropertyList;
class cSPUILayout : public EA::RefCountVTemplate<int> {
 public:
  cSPUILayout();                                                                   // 0x00810000
  void Init(const Key& key, bool visible, uint32_t parentID);                      // 0x008120d0
  void SetParentWin(IWindow* window, bool visible, uint32_t parentID);             // 0x008121b0
  IWindow* FindWindowByID(uint32_t id, bool recursive);                            // 0x008105b0
  uint32_t pad[4];
};

namespace SPUIHelpers {
void SetWindowAreaToParent(IWindow* window);                    // 0x00806bf0
void SetWindowImage(IWindow* window, const Key* key, int index);  // 0x00807bb0
}  // namespace SPUIHelpers

namespace SP {
namespace Editor { enum eEditorConfig {}; }

class cString {
 public:
  cString();                    // 0x006b5060
  ~cString();                   // 0x006b5240
  const wchar_t* GetText();     // 0x006b55c0
  uint32_t pad[5];
};

class cPropertyList {
 public:
  virtual int AddRef();
  virtual int Release();
};
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList*& result);  // +0x2c
};
IPropertyManager* PropertyManager();                                           // 0x0067de30
EA::Messaging::Server* MessageServer();                                        // 0x0067dcc0
bool GetPropertyAsUint32(cPropertyList* list, uint32_t id, uint32_t* result);  // 0x004af210
bool GetPropertyAsText(cPropertyList* list, uint32_t id, cString* result);     // 0x006a1360
bool GetPropertyAsKey(cPropertyList* list, uint32_t id, Key* result);          // 0x006a1250
bool GetPropertyAsKeyInstance(cPropertyList* list, uint32_t id, void* result); // 0x006a12a0

extern bool gbSwatchPlannerMode;  // 0x0151b854

class cSPPaletteItem : public EA::RefCountVTemplate<int>, public EA::COM::IUnknown32 {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  Key mItemKey;       // +0xc
  Key mThumbnailKey;  // +0x18
};

class cCollectableItems {
 public:
  void Lock(uint64_t id);               // 0x00596e10
  void Unlock(uint64_t id, int flags);  // 0x00596da0
};
uint64_t MakeCollectableID(uint32_t groupID, uint32_t instanceID);  // 0x00593980

struct cSPPaletteInfo : public EA::RefCountTemplate<int> {
  void* mEconomy;                        // +0x8
  void* mTheme;                          // +0xc
  cCollectableItems* mCollectableItems;  // +0x10
  cCollectableItems* GetCollectableItems() const { return mCollectableItems; }
};

class cSPSwatch : public IWinProc {
 public:
  void Init(const Key& key, IWindow* window, int a, int b, int c, int d, int e);  // 0x005f4f80
  void SetBackground(uint32_t id);       // 0x005f2270
  void SetShowName(bool show);           // 0x005f2260
  void SetPlannerMode(bool on);          // 0x005f21c0
  void SetImage(uint32_t id, bool on);   // 0x005f2d00
  PV(4) PV(5) PV(6) PV(7)
  virtual void SetModelKey(const Key* key);  // +0x24
  PV(10)
  virtual void SetRotatable(bool on);    // +0x2c
  PV(12) PV(13)
  virtual void SetZoomable(bool on);     // +0x38
};

class cSPPaletteItemRollover {
 public:
  void Hide();  // 0x005ed6c0
};

class cSPSwatchManager;
cSPSwatchManager* SwatchManager();  // 0x00401020

class cISPPaletteItemUI {
 public:
  enum eItemUIInterfaceID { kItemUIUnknown = -1 };
  cISPPaletteItemUI() : mInterfaceID(kItemUIUnknown) {}
  virtual ~cISPPaletteItemUI() {}
  virtual void Init(cSPPaletteItem* item, IWindow* window, int a, cSPPaletteInfo* info) = 0;
  virtual void Shutdown() = 0;
  PV(3) PV(4) PV(5) PV(6)
  virtual void OnRollover() = 0;
  virtual void OffRollover() = 0;

  AutoRefCount<cSPPaletteItem> mPaletteItem;  // +0x4
  eItemUIInterfaceID mInterfaceID;            // +0x8
};

class cSPPaletteItemUI : public cISPPaletteItemUI, public IWinProc, public EA::RefCountVTemplate<int> {
 public:
  cSPPaletteItemUI();   // 0x005c6bf0
  ~cSPPaletteItemUI();  // 0x005c6c50
  virtual void Init(cSPPaletteItem* item, IWindow* window, int a, cSPPaletteInfo* info);  // 0x005c6ca0
  virtual void Shutdown();
  virtual void OnRollover();
  virtual void OffRollover();  // 0x005c6f40
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual bool DoMessage(IWindow* window, const Message& message);  // 0x005c6d70

  bool mIsRolledOver;               // +0x18
  AutoRefCount<IWindow> mWinRoot;   // +0x1c
};

// message 0x53850bae / 0x53850baf payload
class cPlannerEditMessage : public EA::Messaging::IHandler, public EA::RefCountVTemplate<int> {
 public:
  virtual bool HandleMessage(uint32_t, void*);
  Editor::eEditorConfig mWhichEditor;  // +0xc
  Key mModelKey;                       // +0x10
  uint32_t mSlotID;                    // +0x1c
};

class cSPPaletteItemUIPlannerEdit : public cSPPaletteItemUI, public EA::Messaging::IHandlerRC {
 public:
  cSPPaletteItemUIPlannerEdit();
  ~cSPPaletteItemUIPlannerEdit();
  virtual void Init(cSPPaletteItem* item, IWindow* window, int a, cSPPaletteInfo* info);
  virtual void OffRollover();
  virtual bool DoMessage(IWindow* window, const Message& message);
  virtual bool HandleMessage(uint32_t messageID, void* message);
  virtual int AddRef();
  virtual int Release();
  void SetLocked(bool locked);

  AutoRefCount<IWindow> mWinSwatch;          // +0x24
  AutoRefCount<IWindow> mWinRoot;            // +0x28
  AutoRefCount<IWindow> mWinIcon;            // +0x2c
  AutoRefCount<IWindow> mWinLockedIcon;      // +0x30
  AutoRefCount<IWindow> mWinEditButton;      // +0x34
  AutoRefCount<cSPUILayout> mLayout;         // +0x38
  AutoRefCount<cSPSwatch> mSwatch;           // +0x3c
  EA::Messaging::AutoHandler mAutoMsgHandler;  // +0x40
  Key mModelKey;                             // +0x54
  Editor::eEditorConfig mWhichEditor;        // +0x60
  AutoRefCount<cSPPaletteInfo> mInfo;        // +0x64
  bool mLocked;                              // +0x68
  uint32_t mID;                              // +0x6c
  uint32_t mSlotID;                          // +0x70
};

}  // namespace SP

// ---------------------------------------------------------------------------------------------
// Havok collision filter (SP::SPSpineCollisionFilter is a renamed hkpGroupFilter)
typedef unsigned int hkUint32;
typedef unsigned short hkUint16;

class hkBool {
 public:
  hkBool(bool b) : m_bool(b) {}
  operator bool() const { return m_bool != 0; }
  char m_bool;
};

class hkMemory {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void deallocateChunk(void* p, int nbytes, int cl);  // +0x14
  static hkMemory* s_instance;  // 0x016e4178
  static hkMemory& getInstance() { return *s_instance; }
};

class hkBaseObject {
 public:
  virtual ~hkBaseObject() {}
};

class hkReferencedObject : public hkBaseObject {
 public:
  hkReferencedObject() : m_referenceCount(1) {}
  void operator delete(void* p) {
    hkReferencedObject* b = static_cast<hkReferencedObject*>(p);
    hkMemory::getInstance().deallocateChunk(p, b->m_memSizeAndFlags, 0x24);
  }
  hkUint16 m_memSizeAndFlags;  // +0x4
  hkUint16 m_referenceCount;   // +0x6
};

struct hkpCollidable;
struct hkpCdBody {
  const struct hkpShape* m_shape;  // +0x0
  hkUint32 m_shapeKey;             // +0x4
  const void* m_motion;            // +0x8
  const hkpCdBody* m_parent;       // +0xc
  const hkpCdBody* getParent() const { return m_parent; }
  const hkpShape* getShape() const { return m_shape; }
  hkUint32 getShapeKey() const { return m_shapeKey; }
};
struct hkpCollidable : public hkpCdBody {
  uint32_t pad10[3];
  hkUint32 m_collisionFilterInfo;  // +0x1c
  hkUint32 getCollisionFilterInfo() const { return m_collisionFilterInfo; }
};
inline const hkpCollidable* getRootCollidable(const hkpCdBody* body) {
  while (body->getParent())
    body = body->getParent();
  return static_cast<const hkpCollidable*>(body);
}
class hkpShapeContainer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual hkUint32 getCollisionFilterInfo(hkUint32 key) const;  // +0x2c
};
struct hkpShape {
  PV(0) PV(1)
  virtual int getType() const;  // +0x8
  PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual hkUint32 getCollisionFilterInfo(hkUint32 key) const;  // +0x2c (hkpShapeCollection)
  uint32_t pad4[2];
  const hkpShape* m_child;  // +0xc (hkpBvTreeShape container)
};
struct hkpCollisionDispatcher {
  uint32_t pad[0x43];
  hkUint32 m_hasAlternateType[1];  // +0x10c
  hkBool hasAlternateType(int type, int alternateType) const {
    return hkBool(((m_hasAlternateType[type] >> alternateType) & 1) != 0);
  }
};
struct hkpCollisionInput {
  hkpCollisionDispatcher* m_dispatcher;  // +0x0
};
struct hkpShapeRayCastInput {
  uint32_t pad[8];
  hkUint32 m_filterInfo;  // +0x20
};
struct hkpWorldRayCastInput;

class hkpCollidableCollidableFilter {
 public:
  virtual ~hkpCollidableCollidableFilter() {}
  virtual hkBool isCollisionEnabled(const hkpCollidable& a, const hkpCollidable& b) const = 0;
};
class hkpShapeCollectionFilter {
 public:
  virtual ~hkpShapeCollectionFilter() {}
  virtual hkBool isCollisionEnabled(const hkpCollisionInput& input, const hkpCdBody& a,
                                    const hkpCdBody& b, const hkpShapeContainer& bContainer,
                                    hkUint32 bKey) const = 0;
};
class hkpRayShapeCollectionFilter {
 public:
  virtual ~hkpRayShapeCollectionFilter() {}
  virtual hkBool isCollisionEnabled(const hkpShapeRayCastInput& aInput,
                                    const hkpShapeContainer& bContainer, hkUint32 bKey) const = 0;
};
class hkpRayCollidableFilter {
 public:
  virtual ~hkpRayCollidableFilter() {}
  virtual hkBool isCollisionEnabled(const hkpWorldRayCastInput& a, const hkpCollidable& collidableB) const = 0;
};

class hkCollisionFilter : public hkReferencedObject,
                          public hkpCollidableCollidableFilter,
                          public hkpShapeCollectionFilter,
                          public hkpRayShapeCollectionFilter,
                          public hkpRayCollidableFilter {
 public:
};

namespace SP {
class SPSpineCollisionFilter : public hkCollisionFilter {
 public:
  SPSpineCollisionFilter();
  virtual ~SPSpineCollisionFilter();
  virtual hkBool isCollisionEnabled(const hkpCollidable& a, const hkpCollidable& b) const;
  virtual hkBool isCollisionEnabled(const hkpCollisionInput& input, const hkpCdBody& a,
                                    const hkpCdBody& b, const hkpShapeContainer& bContainer,
                                    hkUint32 bKey) const;
  virtual hkBool isCollisionEnabled(const hkpShapeRayCastInput& aInput,
                                    const hkpShapeContainer& bContainer, hkUint32 bKey) const;
  virtual hkBool isCollisionEnabled(const hkpWorldRayCastInput& a, const hkpCollidable& collidableB) const;
  hkBool isCollisionEnabled(hkUint32 infoA, hkUint32 infoB) const;
  void enableCollisionsBetween(int layerA, int layerB);
  void disableCollisionsUsingBitfield(hkUint32 layerBitsA, hkUint32 layerBitsB);

  int m_nextFreeSystemGroup;             // +0x18
  hkUint32 m_collisionLookupTable[32];   // +0x1c
};

// @ 0x005EFD40
SPSpineCollisionFilter::~SPSpineCollisionFilter() {}

// @ 0x005EFD70
int AddTwo(int x) { return x + 2; }

// @ 0x005EFD80
hkBool SPSpineCollisionFilter::isCollisionEnabled(hkUint32 infoA, hkUint32 infoB) const {
  hkUint32 zeroIfSameSystemGroup = (infoA ^ infoB) & 0xffff0000;
  if (zeroIfSameSystemGroup == 0 && (infoA & 0xffff0000) != 0) {
    int idA = (infoA >> 5) & 0x1f;
    int idB = (infoB >> 5) & 0x1f;
    int dontCollideA = (infoA >> 10) & 0x1f;
    int dontCollideB = (infoB >> 10) & 0x1f;
    int d = idA - idB;
    if (d < 0)
      d = -d;
    if (d > dontCollideA && d > dontCollideB)
      return true;
    return false;
  }
  hkUint32 f = 0x1f;
  hkUint32 layerBitsA = m_collisionLookupTable[infoA & f];
  hkUint32 layerBitsB = hkUint32(1 << (infoB & f));
  return 0 != (layerBitsA & layerBitsB);
}

// @ 0x005EFE30
hkBool SPSpineCollisionFilter::isCollisionEnabled(const hkpCollisionInput& input, const hkpCdBody& a,
                                                  const hkpCdBody& b,
                                                  const hkpShapeContainer& bContainer,
                                                  hkUint32 bKey) const {
  hkUint32 infoB = bContainer.getCollisionFilterInfo(bKey);
  hkUint32 infoA;
  if (a.getShapeKey() == 0xffffffff) {
    infoA = getRootCollidable(&a)->getCollisionFilterInfo();
  } else {
    const hkpCdBody* parent = a.getParent();
    do {
      int shapeType = parent->getShape()->getType();
      if (input.m_dispatcher->hasAlternateType(shapeType, 2)) {
        infoA = parent->getShape()->getCollisionFilterInfo(a.getShapeKey());
        goto done;
      }
      if (input.m_dispatcher->hasAlternateType(shapeType, 3)) {
        infoA = parent->getShape()->m_child->getCollisionFilterInfo(a.getShapeKey());
        goto done;
      }
      if (input.m_dispatcher->hasAlternateType(shapeType, 11)) {
        infoA = getRootCollidable(&a)->getCollisionFilterInfo();
        goto done;
      }
      parent = parent->getParent();
    } while (parent);
    infoA = 0;
  }
done:
  return isCollisionEnabled(infoA, infoB);
}

// @ 0x005EFF00
hkBool SPSpineCollisionFilter::isCollisionEnabled(const hkpShapeRayCastInput& aInput,
                                                  const hkpShapeContainer& bContainer,
                                                  hkUint32 bKey) const {
  hkUint32 infoB = bContainer.getCollisionFilterInfo(bKey);
  return isCollisionEnabled(aInput.m_filterInfo, infoB);
}

// @ 0x005EFF70
void SPSpineCollisionFilter::enableCollisionsBetween(int layerA, int layerB) {
  m_collisionLookupTable[layerA] |= hkUint32(1 << layerB);
  m_collisionLookupTable[layerB] |= hkUint32(1 << layerA);
}

// @ 0x005EFFA0
void SPSpineCollisionFilter::disableCollisionsUsingBitfield(hkUint32 layerBitsA, hkUint32 layerBitsB) {
  for (int i = 0; i < 32; i++) {
    int b = 1 << i;
    if (b & layerBitsA)
      m_collisionLookupTable[i] &= ~layerBitsB;
    if (b & layerBitsB)
      m_collisionLookupTable[i] &= ~layerBitsA;
  }
}

// @ 0x005EFFE0
SPSpineCollisionFilter::SPSpineCollisionFilter() {
  for (int i = 0; i < 32; i++)
    m_collisionLookupTable[i] = 0xffffffff;
  m_nextFreeSystemGroup = 0;
}
}  // namespace SP

// @ 0x005F00F0 (scalar deleting destructor, emitted from the vtable)

// ---------------------------------------------------------------------------------------------
namespace eastl {
struct rbtree_node_base {
  rbtree_node_base* mpNodeRight;
  rbtree_node_base* mpNodeLeft;
  rbtree_node_base* mpNodeParent;
  char mColor;
};
}  // namespace eastl
extern "C++" void RBTreeInsert(eastl::rbtree_node_base* pNode, eastl::rbtree_node_base* pNodeParent,
                               eastl::rbtree_node_base* pNodeAnchor, int insertionSide);  // 0x009216a0
eastl::rbtree_node_base* RBTreeIncrement(const eastl::rbtree_node_base* pNode);       // 0x00921580
void RBTreeErase(eastl::rbtree_node_base* pNode, eastl::rbtree_node_base* pNodeAnchor);  // 0x00921880
void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                               const char* file, int line);

namespace eastl {
template <typename T1, typename T2>
struct pair {
  T1 first;
  T2 second;
};

template <typename K, typename V>
struct rbtree_node : public rbtree_node_base {
  pair<K, V> mValue;
};

template <typename K, typename V>
struct rbtree_iterator {
  rbtree_node<K, V>* mpNode;
  rbtree_iterator() : mpNode(0) {}
  explicit rbtree_iterator(rbtree_node<K, V>* p) : mpNode(p) {}
  rbtree_iterator& operator++() {
    mpNode = (rbtree_node<K, V>*)RBTreeIncrement(mpNode);
    return *this;
  }
  bool operator!=(const rbtree_iterator& x) const { return mpNode != x.mpNode; }
};

// eastl::map<K, V> (less<K>, eastl::allocator)
template <typename K, typename V>
class rbtree {
 public:
  typedef rbtree_node<K, V> node_type;
  typedef rbtree_iterator<K, V> iterator;
  typedef pair<K, V> value_type;

  int mCompare;               // +0x0 (empty less<>)
  rbtree_node_base mAnchor;   // +0x4
  unsigned int mnSize;        // +0x14
  const char* mAllocator;     // +0x18

  iterator end() { return iterator((node_type*)&mAnchor); }
  iterator find(const K& key);  // out of line (0x00e5c780)

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
  iterator DoInsertValueImpl(rbtree_node_base* pNodeParent, const value_type& value, bool bForceToLeft);
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

template <typename K, typename V>
typename rbtree<K, V>::iterator rbtree<K, V>::DoInsertValueImpl(rbtree_node_base* pNodeParent,
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

template <typename K, typename V>
unsigned int rbtree<K, V>::erase(const K& key) {
  iterator it(find(key));
  if (it != end()) {
    erase(it);
    return 1;
  }
  return 0;
}
}  // namespace eastl

typedef eastl::rbtree<unsigned int, AutoRefCount<SP::cSPSwatch> > SwatchIDMap;
typedef eastl::rbtree<AutoRefCount<SP::cSPSwatch>, float> SwatchFloatMap;

// @ 0x005F0390
template SwatchIDMap::iterator SwatchIDMap::DoInsertValueImpl(eastl::rbtree_node_base*, const SwatchIDMap::value_type&, bool);
// @ 0x005F0420
template SwatchFloatMap::iterator SwatchFloatMap::DoInsertValueImpl(eastl::rbtree_node_base*, const SwatchFloatMap::value_type&, bool);
// @ 0x005F05E0
template unsigned int SwatchFloatMap::erase(const AutoRefCount<SP::cSPSwatch>&);

namespace SP {
class cICameraManager {
 public:
  PV(0) PV(1)
  virtual int AddRef();   // +0x8
  virtual int Release();  // +0xc
  virtual void SetName(const char* name);  // +0x10
  PV(5) PV(6) PV(7)
  virtual void RegisterCamera(uint32_t id, void* (*factory)());  // +0x20
  PV(9)
  virtual void Initialize();  // +0x28
};
cICameraManager* CreateCameraManager();  // 0x007c7700
void* CreateSwatchCamera();              // 0x005a4150

class cSPPaletteItemRolloverRC {
 public:
  cSPPaletteItemRolloverRC(bool swatch);  // 0x005ed360
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Initialize();  // +0x1c
  uint32_t pad[0x31];
};

class cISPCreatureAnimWorld {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Initialize(int renderer, bool a, bool b, int c, int d);  // +0x1c
  PV(8) PV(9) PV(10) PV(11)
  virtual void* LoadCreature(uint32_t a, uint32_t b, const void* p, const void* q, bool c);  // +0x30
  PV(13) PV(14) PV(15)
  virtual void SetCreatureVisible(void* creature, uint32_t b, bool c);  // +0x40
};
class cAnimWorldManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual cISPCreatureAnimWorld* CreateAnimWorld(const wchar_t* name);  // +0x20
  PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual void SetDebugFlag(uint32_t id);  // +0x3c
};
cAnimWorldManager* AnimWorldManager();  // 0x0067cb20
class cRenderMgr { public: int GetRenderer(); };  // 0x006c10e0
cRenderMgr* RenderManager();                       // 0x0067cad0
class cSPUICursorManager {
 public:
  void AddCursor(uint32_t id, const wchar_t* name, bool a, int b, int c);  // 0x00802050
};
cSPUICursorManager* CursorManager();  // 0x0067cab0

struct AppPropertiesData { char pad[0x118]; int mDebugBlock; };
struct AppProperties { char pad[0x3c]; AppPropertiesData* mpData; };
extern AppProperties* sAppProperties;  // 0x015fd918
extern const uint32_t gSwatchCreatureTransform[];  // 0x015f17f4
extern const uint32_t gSwatchCreatureOptions[];    // 0x0151bfb8

class cSPSwatchManager : public EA::RefCountTemplate<int> {
 public:
  cSPSwatch* CreateSwatch(int flags);           // 0x005f0ca0
  cSPPaletteItemRollover* GetSwatchRollover();  // 0x0113ae10
  void Init();
  void* LoadCreature(uint32_t a, uint32_t b);
  SwatchIDMap mIDToSwatchMap;                              // +0x8
  uint32_t pad24[8];                                       // +0x24
  AutoRefCount<cSPPaletteItemRolloverRC> mSwatchRollover;  // +0x44
  AutoRefCount<cSPPaletteItemRolloverRC> mModelRollover;   // +0x48
  AutoRefCount<cISPCreatureAnimWorld> mpCreatureAnimWorld; // +0x4c
  AutoRefCount<cICameraManager> mCameraManager;            // +0x50
};

// @ 0x005F0140
void cSPSwatchManager::Init() {
  mSwatchRollover = new ("Editor", 0, 0, 0, 0) cSPPaletteItemRolloverRC(true);
  mSwatchRollover->Initialize();
  mModelRollover = new ("Editor", 0, 0, 0, 0) cSPPaletteItemRolloverRC(true);
  mModelRollover->Initialize();
  int renderer = RenderManager()->GetRenderer();
  mpCreatureAnimWorld = AnimWorldManager()->CreateAnimWorld(L"SwatchManager");
  if (sAppProperties->mpData->mDebugBlock)
    AnimWorldManager()->SetDebugFlag(0x4373c4f);
  mpCreatureAnimWorld->Initialize(renderer, true, true, 0, 0);
  mCameraManager = CreateCameraManager();
  if (mCameraManager) {
    mCameraManager->SetName("swatchcamera");
    mCameraManager->RegisterCamera(0xfcc521, CreateSwatchCamera);
    mCameraManager->Initialize();
  }
  CursorManager()->AddCursor(0x648fbf1, L"cursor-grab_open", true, 0, 0);
  CursorManager()->AddCursor(0x6493807, L"cursor-grab_close", true, 0, 0);
}

// @ 0x005F0330
void* cSPSwatchManager::LoadCreature(uint32_t a, uint32_t b) {
  void* creature = mpCreatureAnimWorld->LoadCreature(a, b, gSwatchCreatureTransform, gSwatchCreatureOptions, true);
  if (creature)
    mpCreatureAnimWorld->SetCreatureVisible(creature, b, true);
  return creature;
}
}  // namespace SP

// ---------------------------------------------------------------------------------------------
namespace SP {
// @ 0x005EF440
void cSPPaletteItemUIPlannerEdit::OffRollover() {
  if (cSPPaletteItemRollover* rollover = SwatchManager()->GetSwatchRollover())
    rollover->Hide();
  cSPPaletteItemUI::OffRollover();
}

// @ 0x005EF470
void cSPPaletteItemUIPlannerEdit::SetLocked(bool locked) {
  if (locked) {
    if (mWinLockedIcon)
      mWinLockedIcon->SetFlag(1, true);
    if (mWinIcon)
      mWinIcon->SetFlag(1, false);
    if (mWinSwatch)
      mWinSwatch->SetFlag(1, false);
    if (mWinEditButton)
      mWinEditButton->SetFlag(1, false);
    if (mInfo && mInfo->mCollectableItems) {
      const uint64_t id = MakeCollectableID(mPaletteItem->mItemKey.mGroup, mPaletteItem->mItemKey.mInstance);
      mInfo->mCollectableItems->Lock(id);
    }
  } else {
    if (mWinLockedIcon)
      mWinLockedIcon->SetFlag(1, false);
    if (mWinIcon)
      mWinIcon->SetFlag(1, true);
    if (mWinSwatch)
      mWinSwatch->SetFlag(1, true);
    if (mWinEditButton)
      mWinEditButton->SetFlag(1, true);
    if (mInfo && mInfo->mCollectableItems) {
      const uint64_t id = MakeCollectableID(mPaletteItem->mItemKey.mGroup, mPaletteItem->mItemKey.mInstance);
      mInfo->mCollectableItems->Unlock(id, 0);
    }
  }
  mLocked = locked;
}

// @ 0x005EF590
bool cSPPaletteItemUIPlannerEdit::HandleMessage(uint32_t messageID, void* message) {
  if (messageID == 0x53850baf && mSwatch) {
    cPlannerEditMessage* msg = (cPlannerEditMessage*)message;
    if (msg->mSlotID == mSlotID) {
      mModelKey = msg->mModelKey;
      SetLocked(mModelKey.mInstance == 0);
      mSwatch->SetModelKey(&mModelKey);
      if (gbSwatchPlannerMode) {
        uint32_t imageID = 0x5d6a7be;
        switch ((int)mID) {
          case 0x372e2c04: imageID = 0x5d6a7cc; break;
          case (int)0xccc35c46: imageID = 0x5d6a7d0; break;
          case (int)0x9ea3031a: imageID = 0x5d6a7be; break;
          case 0x4178b8e8:
          case 0x65672ade: imageID = 0x5da8e76; break;
        }
        mSwatch->SetImage(imageID, true);
      }
    }
  }
  return true;
}

// @ 0x005EF6B0
cSPPaletteItemUIPlannerEdit::cSPPaletteItemUIPlannerEdit()
    : mInfo(), mID(0xffffffff), mSlotID(0) {
  mInterfaceID = (eItemUIInterfaceID)0xb4e4f69b;
}

// @ 0x005EF760
cSPPaletteItemUIPlannerEdit::~cSPPaletteItemUIPlannerEdit() {}

static const uint32_t kPlannerEditMessages[] = {0x53850baf};

// @ 0x005EF850
void cSPPaletteItemUIPlannerEdit::Init(cSPPaletteItem* item, IWindow* window, int a,
                                       cSPPaletteInfo* info) {
  if (!item || !window)
    return;
  mInfo = info;
  mLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout();
  mLayout->Init(Key(0x4e39eb54, 0x510a95b, 0x40464100), true, 0x5b598fa);
  mLayout->SetParentWin(window, true, 0x5b598fa);
  mWinRoot = mLayout->FindWindowByID(0xffffffff, true);
  SPUIHelpers::SetWindowAreaToParent(mWinRoot);
  mWinEditButton = mLayout->FindWindowByID(0x5384f7b5, true);
  mWinSwatch = mLayout->FindWindowByID(0x5384f7b6, true);
  if (mWinSwatch) {
    mSwatch = SwatchManager()->CreateSwatch(0);
    if (mSwatch) {
      mSwatch->Init(Key(0, 0, 0), mWinSwatch, 1, 0, 2, 0, -1);
      mSwatch->SetBackground(0xb0d43c20);
      if (gbSwatchPlannerMode) {
        mSwatch->SetShowName(false);
        mSwatch->SetRotatable(true);
        mSwatch->SetZoomable(true);
        mSwatch->SetPlannerMode(true);
      } else {
        mSwatch->SetRotatable(false);
        mSwatch->SetZoomable(false);
      }
    }
  }
  AutoRefCount<cPropertyList> propList;
  if (PropertyManager()->GetPropertyList(item->mItemKey.mInstance, item->mItemKey.mGroup,
                                         propList.AsOutParam())) {
    GetPropertyAsUint32(propList, 0x4294750, &mSlotID);
    cString caption;
    IWindow* captionWin = mLayout->FindWindowByID(0x33854f3f, true);
    if (captionWin && GetPropertyAsText(propList, 0x33854b51, &caption))
      captionWin->SetCaption(caption.GetText());
    Key imageKey(0, 0, 0);
    mWinIcon = mLayout->FindWindowByID(0xd38561ca, true);
    if (mWinIcon && GetPropertyAsKey(propList, 0x4294753, &imageKey))
      SPUIHelpers::SetWindowImage(mWinIcon, &imageKey, -1);
    mWinLockedIcon = mLayout->FindWindowByID(0x73878078, true);
    if (mWinLockedIcon && GetPropertyAsKey(propList, 0x4294753, &imageKey))
      SPUIHelpers::SetWindowImage(mWinLockedIcon, &imageKey, -1);
    GetPropertyAsKeyInstance(propList, 0x4b8e99d, &mWhichEditor);
    uint32_t id = 0;
    GetPropertyAsKeyInstance(propList, 0x5338876f, &id);
    if (id)
      mID = id;
  }
  cSPPaletteItemUI::Init(item, window, a, info);

  EA::Messaging::IHandlerRC* const handler = this;
  mAutoMsgHandler.mpServer = MessageServer();
  mAutoMsgHandler.mpHandler = handler;
  mAutoMsgHandler.mpIdArray = kPlannerEditMessages;
  mAutoMsgHandler.mnIdArrayCount = 1;
  mAutoMsgHandler.mnPriority = 0;
  if (mAutoMsgHandler.mpServer && handler)
    mAutoMsgHandler.mpServer->AddHandler(handler, 0x53850baf);

  uint32_t buttonID;
  switch ((int)mID) {
    case 0x372e2c04: buttonID = 0x673a8f1; break;
    case (int)0xccc35c46: buttonID = 0x673a8f0; break;
    case 0x4178b8e8:
    case 0x65672ade: buttonID = 0x673a8f2; break;
    default: goto done;
  }
  if (IWindow* button = mLayout->FindWindowByID(buttonID, true))
    button->SetFlag(1, true);
done:
  SetLocked(true);
}

// @ 0x005EFCB0
bool cSPPaletteItemUIPlannerEdit::DoMessage(IWindow* window, const Message& message) {
  if (message.mEventType == 0x287259f6 && message.mControlID == 0x5384f7b5 && mSwatch) {
    cPlannerEditMessage msg;
    msg.mModelKey = mModelKey;
    msg.mWhichEditor = mWhichEditor;
    msg.mSlotID = mSlotID;
    MessageServer()->MessageSend(0x53850bae, &msg, 0);
  }
  return cSPPaletteItemUI::DoMessage(window, message);
}
}  // namespace SP
