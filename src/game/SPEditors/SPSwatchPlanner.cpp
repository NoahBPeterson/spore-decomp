// src/game/SPEditors/SPSwatchPlanner.cpp -- migrated from slice(s) s005f16d0, s005f07e0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPSwatchPlanner.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Messaging/AutoHandler.h"
#include "EA/Messaging/IHandler.h"
#include "EA/ResourceMan/Key.h"
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
#include "EA/Variant.h"
#include "SP/cSPOLDPaletteItemUIDragAndBuy.h"
#include "cSPUILayeredObject.h"
#include "cSPUIModelsAndEffectsRenderer.h"
#include "cSPUITooltipWinProc.h"
#include "SP/cSwatch3DView.h"

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
struct Key_s005f_07e0 {
  unsigned int mInstance, mType, mGroup;
  Key_s005f_07e0() : mInstance(0), mType(0), mGroup(0) {}
  Key_s005f_07e0(unsigned int instance, unsigned int type, unsigned int group)
      : mInstance(instance), mType(type), mGroup(group) {}
};  // namespace ResourceMan
}
}
namespace EA {
struct RectT_s005f_07e0 {
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
struct Message_s005f_07e0 {
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
namespace EA {
namespace Messaging {
class IHandler_s005f_07e0 {
 public:
  virtual ~IHandler_s005f_07e0() {}
  virtual bool HandleMessage(uint32_t messageID, void* message) = 0;
};
}
}
namespace EA {
namespace Messaging {
class Server_s005f_07e0 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void MessageSend(uint32_t messageID, void* message, IHandler_s005f_07e0* handler);  // +0x14 0x008853b0
  PV(6) PV(7) PV(8)
  virtual void AddHandler(IHandler_s005f_07e0* handler, uint32_t messageID);  // +0x24
  PV(10)
  virtual void RemoveHandler(IHandler_s005f_07e0* handler, uint32_t messageID, int priority);  // +0x2c 0x00883aa0
};
}
}
namespace EA {
namespace Messaging {
void RemoveHandler(Server_s005f_07e0* server, IHandler_s005f_07e0* handler, const uint32_t* ids, uint32_t count,
                   int priority);  // 0x00571db0
}
}
using EA::AutoRefCount_s005f_07e0;
using EA::ResourceMan::Key_s005f_07e0;
using EA::UTFWin::IWindow_s005f_07e0;
using EA::UTFWin::IWinProc_s005f_07e0;
using EA::UTFWin::Message_s005f_07e0;
class cSPUILayout_s005f_07e0 : public EA::RefCountVTemplate_s005f_07e0<int> {
 public:
  void Shutdown(bool destroyWindows);                                              // 0x00811ad0
  cSPUILayout_s005f_07e0();                                                                   // 0x00810000
  void Init(const Key_s005f_07e0& key, bool visible, uint32_t parentID);                      // 0x008120d0
  void SetParentWin(IWindow_s005f_07e0* window, bool visible, uint32_t parentID);             // 0x008121b0
  IWindow_s005f_07e0* FindWindowByID(uint32_t id, bool recursive);                            // 0x008105b0
  uint32_t pad[4];
};
namespace SPUIHelpers {
void SetWindowImage(IWindow_s005f_07e0* window, const Key_s005f_07e0* key, int index);  // 0x00807bb0
}
namespace SP {
class cPropertyList_s005f_07e0 {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
namespace SP {
EA::Messaging::Server_s005f_07e0* MessageServer();                                        // 0x0067dcc0
}
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
namespace SP {
class cSPRolloverItemData : public cSPRolloverData {  // size 0x64
 public:
  cSPRolloverItemData(Key_s005f_07e0 itemKey, uint32_t modelType, uint32_t layoutID, uint32_t textID, int flags);  // 0x0059f030
  uint32_t pad8[0x17];
};
}
namespace SP {
class cSPRolloverModelData : public cSPRolloverData {  // size 0x5c
 public:
  cSPRolloverModelData(const Key_s005f_07e0& modelKey, const Key_s005f_07e0& itemKey, uint32_t layoutID, uint32_t layoutGroup,
                       uint32_t textID);  // 0x005e0370
  uint32_t pad8[0x15];
};
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
namespace SP {
cSPSwatchManager* SwatchManager();  // 0x00401020
}
namespace SP {
class cISPPaletteItemUI_s005f_07e0 {
 public:
  enum eItemUIInterfaceID { kItemUIUnknown = -1 };
  cISPPaletteItemUI_s005f_07e0() : mInterfaceID(kItemUIUnknown) {}
  virtual ~cISPPaletteItemUI_s005f_07e0() {}
  virtual void Init(cSPPaletteItem_s005f_07e0* item, IWindow_s005f_07e0* window, int a, cSPPaletteInfo_s005f_07e0* info) = 0;
  virtual void Shutdown() = 0;
  PV(3) PV(4) PV(5) PV(6)
  virtual void OnRollover() = 0;
  virtual void OffRollover() = 0;

  AutoRefCount_s005f_07e0<cSPPaletteItem_s005f_07e0> mPaletteItem;  // +0x4
  eItemUIInterfaceID mInterfaceID;            // +0x8
};
}
namespace SP {
class cSPPaletteItemUI_s005f_07e0 : public cISPPaletteItemUI_s005f_07e0, public IWinProc_s005f_07e0, public EA::RefCountVTemplate_s005f_07e0<int> {
 public:
  cSPPaletteItemUI_s005f_07e0();   // 0x005c6bf0
  ~cSPPaletteItemUI_s005f_07e0();  // 0x005c6c50
  virtual void Init(cSPPaletteItem_s005f_07e0* item, IWindow_s005f_07e0* window, int a, cSPPaletteInfo_s005f_07e0* info);  // 0x005c6ca0
  virtual void Shutdown();  // 0x005c6d20 (SP::cSPPaletteItemUI::Shutdown)
  virtual void OnRollover();  // 0x005c6f00 (SP::cSPPaletteItemUI::OnRollover)
  virtual void OffRollover();  // 0x005c6f40
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual bool DoMessage(IWindow_s005f_07e0* window, const Message_s005f_07e0& message);  // 0x005c6d70
  // Shutdown 0x005c6d20, OnRollover 0x005c6f00, OffRollover 0x005c6f40

  bool mIsRolledOver;               // +0x18
  AutoRefCount_s005f_07e0<IWindow_s005f_07e0> mWinRoot;   // +0x1c
};
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
struct cSwatchPlannerMessage {
  uint32_t pad0[2];
  uint32_t mModelType;     // +0x8
  uint32_t pad0c;
  const Key_s005f_07e0* mpModelKey;   // +0x10
  uint32_t pad14;
  const Key_s005f_07e0* mpImageKey;   // +0x18
  uint32_t pad1c;
  cSPPaletteItem_s005f_07e0* mpItem;  // +0x20
};
}
namespace SP {
bool GetPropertyAsKeyArray(cPropertyList_s005f_07e0* list, uint32_t id, int& count, const Key_s005f_07e0*& keys);  // 0x006a0ae0
}
namespace SP {
class cSPSwatchPlanner : public cSPPaletteItemUI_s005f_07e0, public EA::Messaging::IHandler_s005f_07e0 {
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
  IWindow_s005f_07e0* GetImageWindow();
  void SetImage(const Key_s005f_07e0& key);

  AutoRefCount_s005f_07e0<cSPUILayout_s005f_07e0> mLayout;       // +0x24
  AutoRefCount_s005f_07e0<cSPSwatch_s005f_07e0> mSwatch;         // +0x28
  AutoRefCount_s005f_07e0<IWinProc_s005f_07e0> mLargeNewTooltip; // +0x2c
  AutoRefCount_s005f_07e0<IWinProc_s005f_07e0> mNewTooltip;      // +0x30
  AutoRefCount_s005f_07e0<IWinProc_s005f_07e0> mEditTooltip;     // +0x34
  AutoRefCount_s005f_07e0<IWinProc_s005f_07e0> mLoadTooltip;     // +0x38
  uint32_t mModelType;                     // +0x3c
  uint32_t mCost;                          // +0x40
  bool mIsLocked;                          // +0x44
  bool mCanDrag;                           // +0x45
  bool mIsEditable;                        // +0x46
  bool mReadyForMessages;                  // +0x47
  bool mModelChosen;                       // +0x48
  Key_s005f_07e0 mModelKey;                           // +0x4c
  Key_s005f_07e0 mImageKey;                           // +0x58
  AutoRefCount_s005f_07e0<cPropertyList_s005f_07e0> mPropList;   // +0x64
  AutoRefCount_s005f_07e0<cSPPaletteInfo_s005f_07e0> mInfo;      // +0x68
};
}
// ---- items of slice s005f07e0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C++" void RBTreeInsert(eastl::rbtree_node_base_s005f_07e0* pNode, eastl::rbtree_node_base_s005f_07e0* pNodeParent,
                               eastl::rbtree_node_base_s005f_07e0* pNodeAnchor, int insertionSide);  // 0x009216a0

// ---- items of slice s005f16d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV_s005f_16d0(n) virtual void _pv##n();
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
namespace SW {
template <typename T>
class ARC {  // EA::AutoRefCount with inline operator=
 public:
  T* mpObject;
  ARC() : mpObject(0) {}
  ARC& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
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
};
}
namespace SW {
class IWinProc;
}
namespace SW {
struct UIMessage;
}
namespace SW {
template <typename T>
class ARCExt {  // EA::AutoRefCount<IWinText>: operator= stays out of line (0x00b5f950)
 public:
  T* mpObject;
  ARCExt& operator=(T* p);  // 0x00b5f950
};
}
namespace SW {
typedef ARCExt<IWinProc> ARCText;
}
namespace SW {
class IRC;
}
namespace SW {
struct Key {
  uint32_t mInstance, mType, mGroup;
};
}
namespace SW {
class IWindow {
 public:
  virtual int AddRef();
  virtual int Release();
  PV_s005f_16d0(2) PV_s005f_16d0(3) PV_s005f_16d0(4) PV_s005f_16d0(5) PV_s005f_16d0(6) PV_s005f_16d0(7) PV_s005f_16d0(8) PV_s005f_16d0(9) PV_s005f_16d0(10) PV_s005f_16d0(11) PV_s005f_16d0(12) PV_s005f_16d0(13)
  virtual const float* GetArea();  // +0x38
  PV_s005f_16d0(15) PV_s005f_16d0(16) PV_s005f_16d0(17) PV_s005f_16d0(18) PV_s005f_16d0(19) PV_s005f_16d0(20) PV_s005f_16d0(21) PV_s005f_16d0(22) PV_s005f_16d0(23) PV_s005f_16d0(24) PV_s005f_16d0(25) PV_s005f_16d0(26) PV_s005f_16d0(27) PV_s005f_16d0(28) PV_s005f_16d0(29)
  PV_s005f_16d0(30)
  virtual void SetFlag(int flag, bool value);    // +0x7c
  virtual void SetCaption(const wchar_t* text);  // +0x80
  PV_s005f_16d0(33) PV_s005f_16d0(34) PV_s005f_16d0(35) PV_s005f_16d0(36) PV_s005f_16d0(37) PV_s005f_16d0(38) PV_s005f_16d0(39) PV_s005f_16d0(40) PV_s005f_16d0(41) PV_s005f_16d0(42) PV_s005f_16d0(43) PV_s005f_16d0(44) PV_s005f_16d0(45) PV_s005f_16d0(46) PV_s005f_16d0(47)
  PV_s005f_16d0(48) PV_s005f_16d0(49) PV_s005f_16d0(50) PV_s005f_16d0(51) PV_s005f_16d0(52) PV_s005f_16d0(53) PV_s005f_16d0(54) PV_s005f_16d0(55) PV_s005f_16d0(56) PV_s005f_16d0(57) PV_s005f_16d0(58) PV_s005f_16d0(59) PV_s005f_16d0(60) PV_s005f_16d0(61) PV_s005f_16d0(62)
  PV_s005f_16d0(63) PV_s005f_16d0(64)
  virtual void AddWinProc(IWinProc* proc);  // +0x104
};
}
namespace SW {
class IWinProc {
 public:
  ~IWinProc() {}
  virtual int AddRef();
  virtual int Release();
  PV_s005f_16d0(2) PV_s005f_16d0(3) PV_s005f_16d0(4)
  virtual bool HandleUIMessage(IWindow* window, const UIMessage* message);  // +0x14
};
}
namespace SW {
class cSPUILayout {
 public:
  PV_s005f_16d0(0)
  virtual int AddRef();
  virtual int Release();
  cSPUILayout();  // 0x00810000
  IWindow* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0
  bool Init(const Key* key, bool b, uint32_t id);  // 0x008120d0
  void SetParentWin(IWindow* parent, bool b, uint32_t id);  // 0x008121b0
  char pad[0x18 - 4];
};
}
namespace SW {
class Property {
 public:
  char pad[0x12];
  uint16_t mType;  // +0x12
  bool* GetBool();  // 0x0041e920
  int* GetInt();  // 0x0041e990
};
}
namespace SW {
class cPropertyList {
 public:
  virtual int AddRef();
  virtual int Release();
  PV_s005f_16d0(2) PV_s005f_16d0(3) PV_s005f_16d0(4) PV_s005f_16d0(5) PV_s005f_16d0(6)
  virtual bool HasProperty(uint32_t id);                    // +0x1c
  PV_s005f_16d0(8)
  virtual bool GetProperty(uint32_t id, Property** result);  // +0x24
};
}
namespace SW {
class IPropertyManager {
 public:
  PV_s005f_16d0(0) PV_s005f_16d0(1) PV_s005f_16d0(2) PV_s005f_16d0(3) PV_s005f_16d0(4) PV_s005f_16d0(5) PV_s005f_16d0(6) PV_s005f_16d0(7) PV_s005f_16d0(8) PV_s005f_16d0(9) PV_s005f_16d0(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList*& result);  // +0x2c
};
}
namespace SW {
IPropertyManager* PropertyManager();  // 0x0067de30
}
namespace SW {
class IWindowManager {
 public:
  PV_s005f_16d0(0) PV_s005f_16d0(1) PV_s005f_16d0(2) PV_s005f_16d0(3) PV_s005f_16d0(4) PV_s005f_16d0(5) PV_s005f_16d0(6) PV_s005f_16d0(7) PV_s005f_16d0(8) PV_s005f_16d0(9) PV_s005f_16d0(10) PV_s005f_16d0(11) PV_s005f_16d0(12) PV_s005f_16d0(13) PV_s005f_16d0(14) PV_s005f_16d0(15)
  PV_s005f_16d0(16) PV_s005f_16d0(17)
  virtual IWindow* GetWindow(int which);  // +0x48
};
}
namespace SW {
IWindowManager* WindowManager();
}
namespace SW {
class IHandler {
 public:
  virtual bool HandleMessage(uint32_t messageID, void* message);
};
}
namespace SW {
class IMessageServer {
 public:
  PV_s005f_16d0(0) PV_s005f_16d0(1) PV_s005f_16d0(2) PV_s005f_16d0(3) PV_s005f_16d0(4)
  virtual void PostMSG(uint32_t messageID, void* data, void* source);  // +0x14
  PV_s005f_16d0(6) PV_s005f_16d0(7) PV_s005f_16d0(8)
  virtual void AddHandler(IHandler* handler, uint32_t messageID);      // +0x24
};
}
namespace SW {
IMessageServer* MessageServer();  // 0x0067dcc0
}
namespace SW {
class cString {
 public:
  cString();  // 0x006b5060
  ~cString();  // 0x006b5240
  const wchar_t* GetText(const void* v, int a, const void* b, int c);  // 0x006b55c0
  char pad[0x10];
};
}
namespace SW {
class cSPUITooltipWinProc : public IWinProc {
 public:
  cSPUITooltipWinProc(const wchar_t* name, uint32_t id, const wchar_t* text);  // 0x00835e30
};
}
namespace SW {
void* TooltipAlloc(unsigned int size, unsigned int align, const char* name, void* allocator);  // 0x009512d0
}
namespace SW {
void* GetUIAllocator();                                                                        // 0x009512c0
}
namespace SW {
extern const float kTipOffsetX;  // 0x013ec4d0
}
namespace SW {
extern const float kTipOffsetY;  // 0x013f9c6c
}
namespace SW {
extern const char kTipFmt[];     // 0x013f9c04
}
namespace SW {
struct Vec2 {
  float x, y;
  Vec2(float a, float b) : x(a), y(b) {}
};
}
namespace SW {
class IRC {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
namespace SW {
class IMsgA {
 public:
  virtual void ma();
};
}
namespace SW {
class IMsgB {
 public:
  IMsgB() : m08(0) {}
  virtual void mb();
  int m08;  // +0x8
};
}
namespace SW {
class cSPMessage : public IMsgA, public IMsgB {
 public:
  cSPMessage();  // 0x005c1280
  ~cSPMessage();  // 0x005c12c0
  virtual void ma();
  virtual void mb();
  uint32_t mID;     // +0xc
  int m10;          // +0x10
  Key mKey;         // +0x14
  ARCExt<IRC> mRefA;  // +0x20
  ARC<IRC> mRefB;   // +0x24
};
}
namespace SW {
class IPadBase {
 public:
  virtual void pa();
  int pad4;
};
}
namespace SW {
class cSPPaletteItem : public IPadBase, public IRC {
 public:
  Key mKey;    // +0xc
};
}
namespace SW {
class cISPPaletteItemUI {
 public:
  PV_s005f_16d0(0) PV_s005f_16d0(1) PV_s005f_16d0(2) PV_s005f_16d0(3) PV_s005f_16d0(4) PV_s005f_16d0(5) PV_s005f_16d0(6)
  virtual void OnRolloverBegin();  // +0x1c
  virtual void OnRolloverEnd();    // +0x20
  cSPPaletteItem* mPaletteItem;    // +0x4
  int mInterfaceID;                // +0x8
};
}
namespace SW {
struct UIMessage {
  IWindow* mpSource;  // +0x0
  uint32_t pad4;
  int mType;          // +0x8
  int mArg;           // +0xc
  uint32_t pad10, pad14;
  IWindow* mArg2;     // +0x18
};
}
namespace SW {
struct ShortMessage {
  uint32_t mData;
  int pad4;
  int mFlag;
  int padc;
  uint32_t mID;
};
}
namespace SW {
class RefCountVT {
 public:
  RefCountVT() : mRefCount(0) {}
  virtual ~RefCountVT() {}
  virtual int AddRef();
  virtual int Release();
  int mRefCount;
};
}
namespace SW {
class cSPPaletteItemUI : public cISPPaletteItemUI, public IWinProc, public RefCountVT {
 public:
  bool HandleUIMessage(IWindow* window, const UIMessage* message);  // 0x005c6d70
  void Init(cSPPaletteItem* info, IWindow* button, int a, void* b);  // 0x005c6ca0
  bool mIsRolledOver;     // +0x18
  ARC<IWindow> mWinRoot;  // +0x1c
};
}
namespace SW {
bool IsWithin(IWindow* a, IWindow* b);  // 0x00805150
}
namespace SW {
bool StartBanMode(int id);              // 0x008d2fb0
}
namespace SW {
void SetWindowAreaToParent(IWindow* w);                              // 0x00806bf0
}
namespace SW {
void SetWindowImage(IWindow* w, const Key* key, int flag);           // 0x00807bb0
}
namespace SW {
bool GetPropertyAsKey(cPropertyList* pl, uint32_t id, Key* out);     // 0x006a1250
}
namespace SW {
bool GetPropertyAsKeyInstance(cPropertyList* pl, uint32_t id, uint32_t* out);  // 0x006a12a0
}
namespace SW {
bool GetPropertyAsText(cPropertyList* pl, uint32_t id, cString* out);          // 0x006a1360
}
namespace SW {
void SetMoneyString(double v, wchar_t* buf, int size, const wchar_t* fmt, const wchar_t* sym);  // 0x008822e0
}
namespace SW {
class cSPPaletteInfo {
 public:
  PV_s005f_16d0(0)
  virtual int AddRef();
  virtual int Release();
  char pad04[0xc];
  int m10;
  char pad14[4];
  uint16_t mSymbol;  // +0x18
};
}
namespace SW {
class cSwatchItemInfo {
 public:
  char pad[0xc];
  Key mModelKey;  // +0xc
  Key mImageKey;  // +0x18
  bool Check(int arg);  // 0x005c6630
};
}
namespace SW {
class cSPPaletteSwatch {  // 0x1c8 bytes, ctor 0x005f7380
 public:
  virtual int AddRef();
  virtual int Release();
  PV_s005f_16d0(2) PV_s005f_16d0(3) PV_s005f_16d0(4) PV_s005f_16d0(5) PV_s005f_16d0(6) PV_s005f_16d0(7) PV_s005f_16d0(8)
  virtual void SetModelKey(const Key* k);  // +0x24
  PV_s005f_16d0(10) PV_s005f_16d0(11) PV_s005f_16d0(12) PV_s005f_16d0(13)
  virtual void SetShowCostV(bool b);       // +0x38
  cSPPaletteSwatch();  // 0x005f7380
  void Init(const Key* key, IWindow* w, int a, uint32_t id, cSwatchItemInfo* info, cSPPaletteInfo* pi, bool flag);  // 0x005f4310
  void SetShowCost(bool b);  // 0x005f49a0
  void FUN_005f2290(int a);  // 0x005f2290
  char padE[0x100 - 4];
  uint32_t m100;
};
}
namespace SW {
class cSPSwatchPlannerReal : public cSPPaletteItemUI, public IHandler {
 public:
  bool HandleUIMessage(IWindow* window, const UIMessage* message);
  void Init(cSwatchItemInfo* info, IWindow* parent, int a, cSPPaletteInfo* palInfo);
  IWindow* FindActiveButton();  // 0x005f14a0
  void SetImage(const Key* key);   // 0x005f1500
  void SetModelHelper();
  void FUN_005f10b0();
  void SetModel(cPropertyList*& out);
  ARC<cSPUILayout> mLayout;     // +0x24
  ARC<cSPPaletteSwatch> mSwatch;  // +0x28
  ARCText mLargeNewTooltip;     // +0x2c
  ARCText mNewTooltip;          // +0x30
  ARCText mEditTooltip;         // +0x34
  ARCText mLoadTooltip;         // +0x38
  uint32_t mModelType;          // +0x3c
  int mLockedLevel;             // +0x40
  bool mModelChosen;            // +0x44
  bool mShowCost;               // +0x45
  bool mFlag46;                 // +0x46
  bool mReadyForMessages;       // +0x47
  bool mHasModelKey;            // +0x48
  char pad49[3];
  Key mModelKey;                // +0x4c
  int mModelKind;               // +0x58
  char pad5c[8];
  ARC<cPropertyList> mPropList;  // +0x64
  ARC<cSPPaletteInfo> mInfo;     // +0x68
};
}
    void* operator new(unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s005f16d0 end

// @ 0x005f0e30
namespace SP {
cSPSwatchPlanner::~cSPSwatchPlanner()
{}
}  // namespace SP

// @ 0x005f0ef0
namespace SP {
void cSPSwatchPlanner::Shutdown()
{
  mReadyForMessages = false;
  MessageServer()->RemoveHandler(this, 0x3150c27, -9999);
  MessageServer()->RemoveHandler(this, 0x4a344e9, -9999);
  if (mInfo)
    mInfo = 0;
  if (mLargeNewTooltip) {
    if (IWindow_s005f_07e0* window = mLayout->FindWindowByID(0x4a1cb71, true))
      window->RemoveWinProc(mLargeNewTooltip);
    mLargeNewTooltip = 0;
  }
  if (mNewTooltip) {
    if (IWindow_s005f_07e0* window = mLayout->FindWindowByID(0x4a1cb6b, true))
      window->RemoveWinProc(mNewTooltip);
    mNewTooltip = 0;
  }
  if (mEditTooltip) {
    if (IWindow_s005f_07e0* window = mLayout->FindWindowByID(0x4a1cb6c, true))
      window->RemoveWinProc(mEditTooltip);
    mEditTooltip = 0;
  }
  if (mLoadTooltip) {
    if (IWindow_s005f_07e0* window = mLayout->FindWindowByID(0x4a1cb6d, true))
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
  cSPPaletteItemUI_s005f_07e0::Shutdown();
}
}  // namespace SP

// @ 0x005f10b0
namespace SP {
void cSPSwatchPlanner::UpdateCost()
{
  if (IWindow_s005f_07e0* costWindow = mLayout->FindWindowByID(0x64c0c9b, true)) {
    if (mInfo->mEconomy && !mInfo->mEconomy->CanAfford(0, mCost))
      costWindow->SetShadeColor(0xffff0000);
    else
      costWindow->SetShadeColor(0xff032045);
  }
}
}  // namespace SP

// @ 0x005f1110
namespace SP {
void cSPSwatchPlanner::UpdateButtonStatus()
{
  IWindow_s005f_07e0* newButton = mLayout->FindWindowByID(0x4a1cb6b, true);
  IWindow_s005f_07e0* editButton = mLayout->FindWindowByID(0x4a1cb6c, true);
  IWindow_s005f_07e0* loadButton = mLayout->FindWindowByID(0x4a1cb6d, true);
  IWindow_s005f_07e0* costWindow = mLayout->FindWindowByID(0x6443438, true);
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
}  // namespace SP

// @ 0x005f1240
namespace SP {
void cSPSwatchPlanner::OnRollover()
{
  if (!mReadyForMessages)
    return;
  UpdateButtonStatus();
  if (cSPPaletteItemRollover_s005f_07e0* rollover = SwatchManager()->GetSwatchRollover()) {
    bool showCost = true;
    uint32_t textID = 0x4ecf38a;
    if (mIsLocked)
      textID = 0x4ecf388;
    else if (!mModelChosen) {
      textID = 0x4ecf389;
      showCost = false;
    }
    AutoRefCount_s005f_07e0<cSPRolloverData> data;
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
    const EA::RectT_s005f_07e0 area = mWinRoot->GetParent()->GetRealArea();
    rollover->SetPositionAndOffset(area.left, area.top, (area.right - area.left) + 25.0f, 0.0f);
  }
  cSPPaletteItemUI_s005f_07e0::OnRollover();
}
}  // namespace SP

// @ 0x005f1430
namespace SP {
void cSPSwatchPlanner::OffRollover()
{
  if (!mReadyForMessages)
    return;
  UpdateButtonStatus();
  if (cSPPaletteItemRollover_s005f_07e0* rollover = SwatchManager()->GetSwatchRollover())
    rollover->Hide();
  cSPPaletteItemUI_s005f_07e0::OffRollover();
}
}  // namespace SP

// @ 0x005f1460
namespace SP {
bool cSPSwatchPlanner::CanDrag()
{
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
}  // namespace SP

// @ 0x005f14a0
namespace SP {
IWindow_s005f_07e0* cSPSwatchPlanner::GetImageWindow()
{
  IWindow_s005f_07e0* window = mLayout->FindWindowByID(0x4a1cb6e, true);
  if (window && (window->GetFlags() & 1))
    return window;
  window = mLayout->FindWindowByID(0x4a1cb71, true);
  if (window && (window->GetFlags() & 1))
    return window;
  return mLayout->FindWindowByID(0x4a1cb70, true);
}
}  // namespace SP

// @ 0x005f1500
namespace SP {
void cSPSwatchPlanner::SetImage(const Key_s005f_07e0& key)
{
  mImageKey = key;
  UpdateButtonStatus();
  IWindow_s005f_07e0* imageWindow = mLayout->FindWindowByID(0x4a1cb6e, true);
  IWindow_s005f_07e0* defaultWindow = mLayout->FindWindowByID(0x4a1cb71, true);
  if (mIsLocked) {
    if (imageWindow)
      imageWindow->SetFlag(1, false);
    if (defaultWindow)
      defaultWindow->SetFlag(1, false);
  } else if (key.mInstance == 0) {
    int count = 0;
    const Key_s005f_07e0* keys;
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
}  // namespace SP

// @ 0x005f1630
namespace SP {
bool cSPSwatchPlanner::HandleMessage(uint32_t messageID, void* message)
{
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
        const Key_s005f_07e0* modelKey = msg->mpModelKey;
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

// @ 0x005f16d0
namespace SW {
bool cSPSwatchPlannerReal::HandleUIMessage(IWindow* window, const UIMessage* message)
{
  switch (message->mType) {
    case 0x1b:
      if (message->mArg == 1 && !mIsRolledOver) {
        IWindow* const area = FindActiveButton();
        if (!IsWithin(area, message->mArg2)) return true;
        const bool a = StartBanMode(0x3e8);
        const bool b = StartBanMode(0x3ea);
        const bool c = StartBanMode(0x3e9);
        if (a || b || c) return true;
        mIsRolledOver = true;
        OnRolloverBegin();
        return true;
      }
    // fall through
    case 0x287259f6:
      switch (message->mArg) {
        case 0x4a1cb6d: {
          cSPMessage msg;
          cSPPaletteItem* const item = mPaletteItem;
          msg.mID = 0x133b269e;
          msg.mKey = item->mKey;
          msg.mRefA = item;
          MessageServer()->PostMSG(msg.mID, &msg, 0);
          return true;
        }
        case 0x6443438: {
          cSPMessage msg;
          cSPPaletteItem* const item = mPaletteItem;
          msg.mID = 0xb2e18705;
          msg.mKey = item->mKey;
          msg.mRefA = item;
          MessageServer()->PostMSG(msg.mID, &msg, 0);
          return true;
        }
        case 0x4a1cb6b:
        case 0x4a1cb71: {
          ShortMessage m;
          m.mData = mModelType;
          m.mFlag = 0;
          m.mID = 0x4a314e6;
          MessageServer()->PostMSG(m.mID, &m, 0);
          return true;
        }
        case 0x4a1cb6c: {
          ShortMessage m;
          m.mData = mModelType;
          m.mFlag = 1;
          m.mID = 0x4a314e6;
          MessageServer()->PostMSG(m.mID, &m, 0);
          return true;
        }
      }
      break;
    case 0x1c:
      if (message->mArg == 1 && mIsRolledOver) {
        IWindow* const area = FindActiveButton();
        if (!IsWithin(area, WindowManager()->GetWindow(1))) {
          mIsRolledOver = false;
          OnRolloverEnd();
        }
      }
      break;
  }
  return cSPPaletteItemUI::HandleUIMessage(window, message);
}
}  // namespace SW

// @ 0x005f1960
namespace SW {
void cSPSwatchPlannerReal::Init(cSwatchItemInfo* info, IWindow* parent, int a, cSPPaletteInfo* palInfo)
{
  if (!parent) return;
  mModelChosen = palInfo->m10 ? info->Check(palInfo->m10) : false;
  mInfo = palInfo;
  mLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout();
  Key layoutKey;
  layoutKey.mInstance = 0x4f087663;
  layoutKey.mType = 0x510a95b;
  layoutKey.mGroup = 0x40464100;
  mLayout->Init(&layoutKey, true, 0x5b598fa);
  mLayout->SetParentWin(parent, true, 0x5b598fa);
  IWindow* const root = mLayout->FindWindowByID(0x4a1cb70, true);
  SetWindowAreaToParent(root);
  cSPPaletteItemUI::Init((cSPPaletteItem*)info, root, a, palInfo);
  const Key* const modelKey = &info->mModelKey;
  SetImage(&info->mImageKey);
  IPropertyManager* const pm = PropertyManager();
  if (pm->GetPropertyList(modelKey->mInstance, modelKey->mGroup, mPropList.AsOutParam())) {
    IWindow* const imageWin = mLayout->FindWindowByID(0x4a1cb6f, true);
    Key k;
    k.mInstance = 0;
    k.mType = 0;
    k.mGroup = 0;
    uint32_t propId = 0x133c3cad;
    if (mModelChosen) {
      if (mPropList->HasProperty(0x643d3e1)) propId = 0x643d3e1;
    }
    if (GetPropertyAsKey(mPropList.mpObject, propId, &k)) SetWindowImage(imageWin, &k, 0);
    const bool chosen = mModelChosen;
    IWindow* const lockWin = mLayout->FindWindowByID(0x641a080, true);
    IWindow* const costWin = mLayout->FindWindowByID(0x642bea8, true);
    if (lockWin) {
      lockWin->SetFlag(1, !chosen);
      if (GetPropertyAsKey(mPropList.mpObject, 0x133c3cab, &k)) SetWindowImage(lockWin, &k, 0);
    }
    if (costWin) {
      costWin->SetFlag(1, chosen);
      if (GetPropertyAsKey(mPropList.mpObject, 0x133c3cac, &k)) SetWindowImage(costWin, &k, 0);
    }
    GetPropertyAsKeyInstance(mPropList.mpObject, 0x5338876f, &mModelType);
    Property* prop;
    if (mPropList.mpObject && mPropList->GetProperty(0x56097656, &prop) && prop->mType == 1)
      mFlag46 = *prop->GetBool();
    if (mPropList.mpObject && mPropList->GetProperty(0x4adb304, &prop) && prop->mType == 1)
      mShowCost = *prop->GetBool();
    if (!GetPropertyAsKey(mPropList.mpObject, 0x55dca4c, &mModelKey))
      GetPropertyAsKey(mPropList.mpObject, 0x4294752, &mModelKey);
    if (mPropList.mpObject && mPropList->GetProperty(0x2166464, &prop) && prop->mType == 9)
      mLockedLevel = *prop->GetInt();
    const bool showLocked = !mModelChosen && mLockedLevel > 0;
    IWindow* const lvlWin = mLayout->FindWindowByID(0x642c9be, true);
    if (lvlWin) lvlWin->SetFlag(1, showLocked);
    if (showLocked) {
      IWindow* const priceWin = mLayout->FindWindowByID(0x642bd0b, true);
      if (priceWin) {
        wchar_t sym[2];
        sym[0] = palInfo->mSymbol;
        sym[1] = 0;
        wchar_t buf[0x20];
        SetMoneyString((double)mLockedLevel, buf, 0x20, L"%-F%-p", sym);
        priceWin->SetCaption(buf);
      }
    }
    mLayout->FindWindowByID(0x4a1cb71, true);
    IWindow* const w1 = mLayout->FindWindowByID(0x4a1cb6b, true);
    IWindow* const w2 = mLayout->FindWindowByID(0x4a1cb6c, true);
    IWindow* const w3 = mLayout->FindWindowByID(0x4a1cb6d, true);
    cString text;
    if (w1) {
      if (GetPropertyAsText(mPropList.mpObject, 0x5a9e402d, &text)) {
        void* const mem = TooltipAlloc(0x68, 4, "UI/Tooltip", GetUIAllocator());
        cSPUITooltipWinProc* tip = 0;
        if (mem) {
          const Vec2 off(kTipOffsetX, kTipOffsetY);
          tip = new (mem) cSPUITooltipWinProc(L"Tooltips", 0x3754e6c, text.GetText(&off, 0, kTipFmt, 0));
        }
        mNewTooltip = tip;
        w1->AddWinProc(mNewTooltip.mpObject);
      }
    }
    if (w2) {
      if (GetPropertyAsText(mPropList.mpObject, 0x4ca3377, &text)) {
        void* const mem = TooltipAlloc(0x68, 4, "UI/Tooltip", GetUIAllocator());
        cSPUITooltipWinProc* tip = 0;
        if (mem) {
          const Vec2 off(kTipOffsetX, kTipOffsetY);
          tip = new (mem) cSPUITooltipWinProc(L"Tooltips", 0x3754e6c, text.GetText(&off, 0, kTipFmt, 0));
        }
        mEditTooltip = tip;
        w2->AddWinProc(mEditTooltip.mpObject);
      }
    }
    if (w3) {
      if (GetPropertyAsText(mPropList.mpObject, 0x6081d87b, &text)) {
        void* const mem = TooltipAlloc(0x68, 4, "UI/Tooltip", GetUIAllocator());
        cSPUITooltipWinProc* tip = 0;
        if (mem) {
          const Vec2 off(kTipOffsetX, kTipOffsetY);
          tip = new (mem) cSPUITooltipWinProc(L"Tooltips", 0x3754e6c, text.GetText(&off, 0, kTipFmt, 0));
        }
        mLoadTooltip = tip;
        w3->AddWinProc(mLoadTooltip.mpObject);
      }
    }
    IWindow* const swatchWin = mLayout->FindWindowByID(0x4a1cb6e, true);
    cSPPaletteSwatch* const swatch = new ("Editor", 0, 0, 0, 0) cSPPaletteSwatch();
    mSwatch = swatch;
    swatch->Init(&info->mModelKey, swatchWin, a, 0xb2e18705, info, palInfo, true);
    swatch->SetShowCost(mShowCost);
    swatch->SetShowCostV(mShowCost);
    swatch->FUN_005f2290(0);
    uint32_t kind = 0x71fa7d3f;
    uint32_t tmp;
    if (GetPropertyAsKeyInstance(mPropList.mpObject, 0x57fb25a, &tmp)) {
      kind = tmp;
      if (kind == 0x5e71ab9b) {
        swatch->m100 = 0x2ca33bdb;
      } else {
        swatch->m100 = kind;
      }
    } else {
      swatch->m100 = kind;
    }
    if (mModelKey.mInstance != 0) {
      mSwatch->SetModelKey(&mModelKey);
      mHasModelKey = true;
    }
    IWindow* const kindWin = mLayout->FindWindowByID(0x6443438, true);
    if (kindWin) {
      bool v;
      if (mModelChosen) v = false;
      else v = kind == 0x5e71ab9b;
      kindWin->SetFlag(1, v);
    }
  }
  FUN_005f10b0();
  MessageServer()->AddHandler(this, 0x4a344e9);
  MessageServer()->AddHandler(this, 0x3150c27);
  mReadyForMessages = true;
}
}  // namespace SW
