// slice s005f07e0 -- SP::cSPSwatchManager (ctor/dtor, Shutdown, Update, CreateSwatch,
// ReleaseSwatch, swatch timeouts and the two eastl::map operator[] instances) and
// SP::cSPSwatchPlanner (ctor/dtor, Shutdown, button/cost state, rollover, SetImage, HandleMessage).
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
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
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

struct RectT {
  float left, top, right, bottom;
  RectT(const RectT& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
};

namespace UTFWin {
class IWinProc;
class IWindow : public COM::IUnknown32 {
 public:
  PV(3)
  virtual IWindow* GetParent();                     // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual uint32_t GetFlags();                      // +0x28
  PV(11) PV(12) PV(13)
  virtual const RectT& GetRealArea();               // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
  virtual void SetShadeColor(uint32_t color);       // +0x5c
  PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);       // +0x7c
  virtual void SetCaption(const wchar_t* caption);  // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45)
  PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc* proc);     // +0x104
  virtual void RemoveWinProc(IWinProc* proc);  // +0x108
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
  PV(10)
  virtual void RemoveHandler(IHandler* handler, uint32_t messageID, int priority);  // +0x2c
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
  void Shutdown(bool destroyWindows);                                              // 0x00811ad0
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

class cSPEditorEconomy {
 public:
  PV(0) PV(1)
  virtual bool IsItemAvailable(const Key* key);    // +0x8
  virtual bool CanAfford(int currency, int cost);  // +0xc
};

struct cSPPaletteInfo : public EA::RefCountTemplate<int> {
  cSPEditorEconomy* mEconomy;            // +0x8
  void* mTheme;                          // +0xc
  cCollectableItems* mCollectableItems;  // +0x10
  cCollectableItems* GetCollectableItems() const { return mCollectableItems; }
};

class cSPSwatch : public IWinProc {
 public:
  cSPSwatch();  // 0x005f6bd0
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual bool DoMessage(IWindow* window, const Message& message);
  void Init(const Key& key, IWindow* window, int a, int b, int c, int d, int e);  // 0x005f4f80
  void SetBackground(uint32_t id);       // 0x005f2270
  void SetShowName(bool show);           // 0x005f2260
  void SetPlannerMode(bool on);          // 0x005f21c0
  void SetImage(uint32_t id, bool on);   // 0x005f2d00
  PV(5) PV(6)
  virtual void Shutdown();                   // +0x1c
  virtual void Update(uint32_t deltaTime);   // +0x20
  virtual void SetModelKey(const Key* key);  // +0x24
  uint32_t pad4[0x5d];
  uint32_t mID;  // +0x178
};

class cSPRolloverData : public EA::RefCountTemplate<int> {};
class cSPRolloverItemData : public cSPRolloverData {  // size 0x64
 public:
  cSPRolloverItemData(Key itemKey, uint32_t modelType, uint32_t layoutID, uint32_t textID, int flags);  // 0x0059f030
  uint32_t pad8[0x17];
};
class cSPRolloverModelData : public cSPRolloverData {  // size 0x5c
 public:
  cSPRolloverModelData(const Key& modelKey, const Key& itemKey, uint32_t layoutID, uint32_t layoutGroup,
                       uint32_t textID);  // 0x005e0370
  uint32_t pad8[0x15];
};

}  // namespace SP
// retail calls the out-of-line instance of this assignment (0x00572620)
template <> EA::AutoRefCount<SP::cSPRolloverData>& EA::AutoRefCount<SP::cSPRolloverData>::operator=(SP::cSPRolloverData* p);
namespace SP {

class cSPPaletteItemRollover {
 public:
  void Setup(cSPPaletteItem* item, cSPPaletteInfo* info, cSPRolloverData* data, bool showCost);  // 0x005ee480
  void SetMode(int mode);  // 0x005ed320
  void Hide();             // 0x005ed6c0
  void SetPositionAndOffset(float x, float y, float offsetX, float offsetY);  // 0x008283a0
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
  // Shutdown 0x005c6d20, OnRollover 0x005c6f00, OffRollover 0x005c6f40

  bool mIsRolledOver;               // +0x18
  AutoRefCount<IWindow> mWinRoot;   // +0x1c
};

// message 0x53850bae / 0x53850baf payload
}  // namespace SP

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
struct true_type {};

template <typename T1, typename T2>
struct pair {
  T1 first;
  T2 second;
  pair(const T1& x, const T2& y) : first(x), second(y) {}
};

template <typename K, typename V>
struct rbtree_node : public rbtree_node_base {
  pair<const K, V> mValue;
};

template <typename K, typename V>
struct rbtree_iterator {
  rbtree_node<K, V>* mpNode;
  rbtree_iterator() : mpNode(0) {}
  explicit rbtree_iterator(rbtree_node<K, V>* p) : mpNode(p) {}
  rbtree_iterator(const rbtree_iterator& x) : mpNode(x.mpNode) {}
  rbtree_iterator& operator++() {
    mpNode = (rbtree_node<K, V>*)RBTreeIncrement(mpNode);
    return *this;
  }
  bool operator!=(const rbtree_iterator& x) const { return mpNode != x.mpNode; }
  bool operator==(const rbtree_iterator& x) const { return mpNode == x.mpNode; }
  pair<const K, V>* operator->() const { return &mpNode->mValue; }
  rbtree_iterator operator++(int) {
    rbtree_iterator temp(*this);
    mpNode = (rbtree_node<K, V>*)RBTreeIncrement(mpNode);
    return temp;
  }
};

class allocator {
 public:
  allocator(const char* = 0) {}
};

// eastl::map<K, V> (less<K>, eastl::allocator)
template <typename K, typename V>
class rbtree {
 public:
  typedef rbtree_node<K, V> node_type;
  typedef rbtree_iterator<K, V> iterator;
  typedef pair<const K, V> value_type;

  int mCompare;               // +0x0 (empty less<>)
  rbtree_node_base mAnchor;   // +0x4
  unsigned int mnSize;        // +0x14
  allocator mAllocator;       // +0x18

  rbtree() : mAnchor(), mnSize(0) { reset(); }
  ~rbtree() { DoNukeSubtree((node_type*)mAnchor.mpNodeParent); }
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
// the id map's erase(iterator) is called out of line (0x01045590)
template <> SwatchIDMap::iterator SwatchIDMap::erase(SwatchIDMap::iterator position);

// @ 0x005F0B40 (SwatchIDMap::operator[])
template AutoRefCount<SP::cSPSwatch>& SwatchIDMap::operator[](const unsigned int&);
// @ 0x005F0BC0 (SwatchFloatMap::operator[])
template float& SwatchFloatMap::operator[](const AutoRefCount<SP::cSPSwatch>&);

namespace SP {
class cICameraManager {
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

class cSPPaletteItemRolloverRC {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Initialize();  // +0x1c
  PV(8)
  virtual void Shutdown();    // +0x24
};

class cISPCreatureAnimWorld {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Initialize(int renderer, bool a, bool b, int c, int d);  // +0x1c
  virtual void Shutdown();                                              // +0x20
  virtual void Update(float deltaTime, int flags);                     // +0x24
};

class cSPUICursorManager {
 public:
  void RemoveCursor(uint32_t id);  // 0x008024e0
};
cSPUICursorManager* CursorManager();  // 0x0067cab0

class cSPSwatchManager : public EA::RefCountTemplate<int> {
 public:
  cSPSwatchManager();
  ~cSPSwatchManager();
  void Shutdown();
  void Update(uint32_t deltaTime);
  void ReleaseSwatch(cSPSwatch* swatch);
  void SetSwatchTimeout(cSPSwatch* swatch, float timeout);
  cSPSwatch* CreateSwatch(cSPSwatch* swatch);
  cSPPaletteItemRollover* GetSwatchRollover();  // 0x0113ae10

  SwatchIDMap mIDToSwatchMap;                              // +0x8
  SwatchFloatMap mSwatchTimeouts;                          // +0x24
  uint32_t mCurrentID;                                     // +0x40
  AutoRefCount<cSPPaletteItemRolloverRC> mSwatchRollover;  // +0x44
  AutoRefCount<cSPPaletteItemRolloverRC> mModelRollover;   // +0x48
  AutoRefCount<cISPCreatureAnimWorld> mpCreatureAnimWorld; // +0x4c
  AutoRefCount<cICameraManager> mCameraManager;            // +0x50
};

// @ 0x005F07E0
cSPSwatchManager::~cSPSwatchManager() {}

// @ 0x005F0850
void cSPSwatchManager::Shutdown() {
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

template <typename T>
inline const T& min_alt(const T& a, const T& b) { return (b < a) ? b : a; }

// @ 0x005F0940
void cSPSwatchManager::Update(uint32_t deltaTime) {
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

// @ 0x005F0A60
void cSPSwatchManager::ReleaseSwatch(cSPSwatch* swatch) {
  SwatchIDMap::iterator it;
  it = mIDToSwatchMap.find(swatch->mID);
  if (it != mIDToSwatchMap.end() && it->second) {
    mSwatchTimeouts.erase(it->second);
    it->second->Shutdown();
    mIDToSwatchMap.erase(it);
  }
}

// @ 0x005F0AC0
cSPSwatchManager::cSPSwatchManager() : mCurrentID(0) {}


// @ 0x005F0C60
void cSPSwatchManager::SetSwatchTimeout(cSPSwatch* swatch, float timeout) {
  if (swatch)
    mSwatchTimeouts[swatch] = timeout;
}

// @ 0x005F0CA0
cSPSwatch* cSPSwatchManager::CreateSwatch(cSPSwatch* swatch) {
  if (!swatch)
    swatch = new ("Editor", 0, 0, 0, 0) cSPSwatch();
  mIDToSwatchMap[mCurrentID] = swatch;
  swatch->mID = mCurrentID;
  mCurrentID++;
  mSwatchTimeouts[swatch] = 1.0e12f;
  return swatch;
}

// ---------------------------------------------------------------------------------------------
struct cSwatchPlannerMessage {
  uint32_t pad0[2];
  uint32_t mModelType;     // +0x8
  uint32_t pad0c;
  const Key* mpModelKey;   // +0x10
  uint32_t pad14;
  const Key* mpImageKey;   // +0x18
  uint32_t pad1c;
  cSPPaletteItem* mpItem;  // +0x20
};

bool GetPropertyAsKeyArray(cPropertyList* list, uint32_t id, int& count, const Key*& keys);  // 0x006a0ae0

class cSPSwatchPlanner : public cSPPaletteItemUI, public EA::Messaging::IHandler {
 public:
  cSPSwatchPlanner();
  ~cSPSwatchPlanner();
  virtual void Shutdown();
  virtual void OnRollover();
  virtual void OffRollover();
  virtual bool HandleMessage(uint32_t messageID, void* message);
  void UpdateCost();
  void UpdateButtonStatus();
  bool CanDrag();
  IWindow* GetImageWindow();
  void SetImage(const Key& key);

  AutoRefCount<cSPUILayout> mLayout;       // +0x24
  AutoRefCount<cSPSwatch> mSwatch;         // +0x28
  AutoRefCount<IWinProc> mLargeNewTooltip; // +0x2c
  AutoRefCount<IWinProc> mNewTooltip;      // +0x30
  AutoRefCount<IWinProc> mEditTooltip;     // +0x34
  AutoRefCount<IWinProc> mLoadTooltip;     // +0x38
  uint32_t mModelType;                     // +0x3c
  uint32_t mCost;                          // +0x40
  bool mIsLocked;                          // +0x44
  bool mCanDrag;                           // +0x45
  bool mIsEditable;                        // +0x46
  bool mReadyForMessages;                  // +0x47
  bool mModelChosen;                       // +0x48
  Key mModelKey;                           // +0x4c
  Key mImageKey;                           // +0x58
  AutoRefCount<cPropertyList> mPropList;   // +0x64
  AutoRefCount<cSPPaletteInfo> mInfo;      // +0x68
};

// @ 0x005F0D80
cSPSwatchPlanner::cSPSwatchPlanner()
    : mModelType(0), mCost(0), mIsLocked(false), mCanDrag(true), mIsEditable(false),
      mReadyForMessages(false), mModelChosen(false) {}

// @ 0x005F0E30
cSPSwatchPlanner::~cSPSwatchPlanner() {}

// @ 0x005F0EF0
void cSPSwatchPlanner::Shutdown() {
  mReadyForMessages = false;
  MessageServer()->RemoveHandler(this, 0x3150c27, -9999);
  MessageServer()->RemoveHandler(this, 0x4a344e9, -9999);
  if (mInfo)
    mInfo = 0;
  if (mLargeNewTooltip) {
    if (IWindow* window = mLayout->FindWindowByID(0x4a1cb71, true))
      window->RemoveWinProc(mLargeNewTooltip);
    mLargeNewTooltip = 0;
  }
  if (mNewTooltip) {
    if (IWindow* window = mLayout->FindWindowByID(0x4a1cb6b, true))
      window->RemoveWinProc(mNewTooltip);
    mNewTooltip = 0;
  }
  if (mEditTooltip) {
    if (IWindow* window = mLayout->FindWindowByID(0x4a1cb6c, true))
      window->RemoveWinProc(mEditTooltip);
    mEditTooltip = 0;
  }
  if (mLoadTooltip) {
    if (IWindow* window = mLayout->FindWindowByID(0x4a1cb6d, true))
      window->RemoveWinProc(mLoadTooltip);
    mLoadTooltip = 0;
  }
  if (mSwatch) {
    mSwatch->Shutdown();
    mSwatch = 0;
  }
  if (mLayout) {
    mLayout->Shutdown(true);
    mLayout = 0;
  }
  mPropList = 0;
  cSPPaletteItemUI::Shutdown();
}

// @ 0x005F10B0
void cSPSwatchPlanner::UpdateCost() {
  if (IWindow* costWindow = mLayout->FindWindowByID(0x64c0c9b, true)) {
    if (mInfo->mEconomy && !mInfo->mEconomy->CanAfford(0, mCost))
      costWindow->SetShadeColor(0xffff0000);
    else
      costWindow->SetShadeColor(0xff032045);
  }
}

// @ 0x005F1110
void cSPSwatchPlanner::UpdateButtonStatus() {
  IWindow* newButton = mLayout->FindWindowByID(0x4a1cb6b, true);
  IWindow* editButton = mLayout->FindWindowByID(0x4a1cb6c, true);
  IWindow* loadButton = mLayout->FindWindowByID(0x4a1cb6d, true);
  IWindow* costWindow = mLayout->FindWindowByID(0x6443438, true);
  if (newButton && editButton && loadButton && costWindow) {
    if (mIsEditable && !mIsLocked) {
      if (mImageKey.mInstance == 0) {
        newButton->SetFlag(1, false);
        editButton->SetFlag(1, false);
        loadButton->SetFlag(1, true);
      } else {
        newButton->SetFlag(1, true);
        editButton->SetFlag(1, true);
        loadButton->SetFlag(1, true);
      }
    } else {
      newButton->SetFlag(1, false);
      editButton->SetFlag(1, false);
      loadButton->SetFlag(1, false);
    }
    if (mInfo->mEconomy &&
        (!mModelChosen || !mInfo->mEconomy->IsItemAvailable(&mPaletteItem->mItemKey)))
      costWindow->SetFlag(2, false);
    else
      costWindow->SetFlag(2, true);
  }
}

// @ 0x005F1240
void cSPSwatchPlanner::OnRollover() {
  if (!mReadyForMessages)
    return;
  UpdateButtonStatus();
  if (cSPPaletteItemRollover* rollover = SwatchManager()->GetSwatchRollover()) {
    bool showCost = true;
    uint32_t textID = 0x4ecf38a;
    if (mIsLocked)
      textID = 0x4ecf388;
    else if (!mModelChosen) {
      textID = 0x4ecf389;
      showCost = false;
    }
    AutoRefCount<cSPRolloverData> data;
    switch (mModelType) {
      case 0x7d433fad:
      case 0x2a5147a9:
      case 0x1a4e0708:
      case 0x1f2a25b6:
      case 0x441cd3e6:
      case 0x449c040f:
      case 0xc0b74287:
      case 0x8f963dcb:
      case 0x9ad7d4aa:
      case 0xf670aa43:
        if (!mIsLocked && mModelChosen) {
          data = new ("Editor", 0, 0, 0, 0)
              cSPRolloverModelData(mModelKey, mPaletteItem->mItemKey, 0xa592740e, 0xfbf87a32, textID);
          break;
        }
      default:
        data = new ("Editor", 0, 0, 0, 0)
            cSPRolloverItemData(mPaletteItem->mItemKey, mModelType, 0xa592740e, textID, 0);
        break;
    }
    rollover->Setup(mPaletteItem, mInfo, data, showCost);
    rollover->SetMode(2);
    const EA::RectT area = mWinRoot->GetParent()->GetRealArea();
    rollover->SetPositionAndOffset(area.left, area.top, (area.right - area.left) + 25.0f, 0.0f);
  }
  cSPPaletteItemUI::OnRollover();
}

// @ 0x005F1430
void cSPSwatchPlanner::OffRollover() {
  if (!mReadyForMessages)
    return;
  UpdateButtonStatus();
  if (cSPPaletteItemRollover* rollover = SwatchManager()->GetSwatchRollover())
    rollover->Hide();
  cSPPaletteItemUI::OffRollover();
}

// @ 0x005F1460
bool cSPSwatchPlanner::CanDrag() {
  if (mIsLocked)
    return false;
  if (!mCanDrag)
    return false;
  if (!mModelKey.mInstance)
    return false;
  if (mInfo->mEconomy && !mInfo->mEconomy->IsItemAvailable(&mPaletteItem->mItemKey))
    return false;
  return true;
}

// @ 0x005F14A0
IWindow* cSPSwatchPlanner::GetImageWindow() {
  IWindow* window = mLayout->FindWindowByID(0x4a1cb6e, true);
  if (window && (window->GetFlags() & 1))
    return window;
  window = mLayout->FindWindowByID(0x4a1cb71, true);
  if (window && (window->GetFlags() & 1))
    return window;
  return mLayout->FindWindowByID(0x4a1cb70, true);
}

// @ 0x005F1500
void cSPSwatchPlanner::SetImage(const Key& key) {
  mImageKey = key;
  UpdateButtonStatus();
  IWindow* imageWindow = mLayout->FindWindowByID(0x4a1cb6e, true);
  IWindow* defaultWindow = mLayout->FindWindowByID(0x4a1cb71, true);
  if (mIsLocked) {
    if (imageWindow)
      imageWindow->SetFlag(1, false);
    if (defaultWindow)
      defaultWindow->SetFlag(1, false);
  } else if (key.mInstance == 0) {
    int count = 0;
    const Key* keys;
    if (GetPropertyAsKeyArray(mPropList, 0x983c9f8f, count, keys)) {
      for (int i = 0; i < count; i++)
        SPUIHelpers::SetWindowImage(defaultWindow, &keys[i], i);
    }
    if (imageWindow)
      imageWindow->SetFlag(1, false);
    if (defaultWindow)
      defaultWindow->SetFlag(1, true);
  } else {
    SPUIHelpers::SetWindowImage(imageWindow, &key, -1);
    if (imageWindow)
      imageWindow->SetFlag(1, true);
    if (defaultWindow)
      defaultWindow->SetFlag(1, false);
  }
}

// @ 0x005F1630
bool cSPSwatchPlanner::HandleMessage(uint32_t messageID, void* message) {
  if (mReadyForMessages) {
    switch (messageID) {
      case 0x3150c27:
        UpdateCost();
        UpdateButtonStatus();
        break;
      case 0x4a344e9: {
        cSwatchPlannerMessage* msg = (cSwatchPlannerMessage*)message;
        if (msg->mpItem == 0) {
          if (msg->mModelType != mModelType)
            return false;
        } else if (msg->mpItem != mPaletteItem)
          return false;
        const Key* modelKey = msg->mpModelKey;
        mSwatch->SetModelKey(modelKey);
        if (modelKey->mInstance) {
          mModelChosen = true;
          UpdateButtonStatus();
        }
        mModelKey = *modelKey;
        SetImage(*msg->mpImageKey);
        return true;
      }
    }
  }
  return false;
}
}  // namespace SP
