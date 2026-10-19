// src/game/SPEditors/SPSwatchManager.cpp -- migrated from slice(s) s005ef440 by tools/migrate/rewrite.py
// Object file: SPEditors/SPSwatchManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cCollectableItems.h"
#include "SP/cICameraManager.h"
#include "SP/cISPCreatureAnimWorld.h"
#include "SP/cISPPaletteItemUI.h"
#include "SP/cPropertyList.h"
#include "SP/cSPPaletteInfo.h"
#include "SP/cSPPaletteItem.h"
#include "SP/cSPPaletteItemRollover.h"
#include "SP/cSPPaletteItemUI.h"
#include "SP/cSPSwatch.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "hkBaseObject.h"
#include "hkBool.h"
#include "hkReferencedObject.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380
#include <new>

// ---- items of slice s005ef440 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);  // 0x00f473a0
#define EASTL_ALLOCATOR_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define PV(n) virtual void pv##n();
namespace EA {
template <typename T>
class AutoRefCount_s005e_f440 {
 public:
  T* mpObject;
  AutoRefCount_s005e_f440() : mpObject(0) {}
  AutoRefCount_s005e_f440(const AutoRefCount_s005e_f440& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005e_f440() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005e_f440& operator=(T* p) {
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
class RefCountTemplate_s005e_f440 {
 public:
  RefCountTemplate_s005e_f440() : mRefCount(0) {}
  virtual ~RefCountTemplate_s005e_f440() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005e_f440 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};  // namespace COM
}
}
namespace EA {
namespace ResourceMan {
struct Key_s005e_f440 {
  unsigned int mInstance, mType, mGroup;
  Key_s005e_f440() : mInstance(0), mType(0), mGroup(0) {}
  Key_s005e_f440(unsigned int instance, unsigned int type, unsigned int group)
      : mInstance(instance), mType(type), mGroup(group) {}
};  // namespace ResourceMan
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005e_f440;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005e_f440 : public COM::IUnknown32_s005e_f440 {
 public:
  PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  PV(30)
  virtual void SetFlag(int flag, bool value);       // +0x7c
  virtual void SetCaption(const wchar_t* caption);  // +0x80
};
}
}
namespace EA {
namespace UTFWin {
struct Message_s005e_f440 {
  uint32_t pad0[2];
  uint32_t mEventType;  // +0x8
  uint32_t mControlID;  // +0xc
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005e_f440 : public COM::IUnknown32_s005e_f440 {
 public:
  virtual int GetEventFlags();
  virtual bool DoMessage(IWindow_s005e_f440* window, const Message_s005e_f440& message) = 0;
};
}
}
using EA::AutoRefCount_s005e_f440;
using EA::ResourceMan::Key_s005e_f440;
using EA::UTFWin::IWindow_s005e_f440;
using EA::UTFWin::IWinProc_s005e_f440;
using EA::UTFWin::Message_s005e_f440;
namespace SP {
class cSPSwatch_s005e_f440 : public IWinProc_s005e_f440 {
 public:
  void Init(const Key_s005e_f440& key, IWindow_s005e_f440* window, int a, int b, int c, int d, int e);  // 0x005f4f80
  void SetBackground(uint32_t id);       // 0x005f2270
  void SetShowName(bool show);           // 0x005f2260
  void SetPlannerMode(bool on);          // 0x005f21c0
  void SetImage(uint32_t id, bool on);   // 0x005f2d00
  PV(4) PV(5) PV(6) PV(7)
  virtual void SetModelKey(const Key_s005e_f440* key);  // +0x24 0x005f4080
  PV(10)
  virtual void SetRotatable(bool on);    // +0x2c
  PV(12) PV(13)
  virtual void SetZoomable(bool on);     // +0x38
};
}
namespace SP {
class cSPPaletteItemRollover_s005e_f440 {
 public:
  void Hide();  // 0x005ed6c0
};
}
namespace SP {
class cSPSwatchManager;
}
namespace eastl {
struct rbtree_node_base_s005e_f440 {
  rbtree_node_base_s005e_f440* mpNodeRight;
  rbtree_node_base_s005e_f440* mpNodeLeft;
  rbtree_node_base_s005e_f440* mpNodeParent;
  char mColor;
};  // namespace eastl
}
extern "C++" void RBTreeInsert(eastl::rbtree_node_base_s005e_f440* pNode, eastl::rbtree_node_base_s005e_f440* pNodeParent,
                               eastl::rbtree_node_base_s005e_f440* pNodeAnchor, int insertionSide);  // 0x009216a0
eastl::rbtree_node_base_s005e_f440* RBTreeIncrement(const eastl::rbtree_node_base_s005e_f440* pNode);       // 0x00921580
void RBTreeErase(eastl::rbtree_node_base_s005e_f440* pNode, eastl::rbtree_node_base_s005e_f440* pNodeAnchor);  // 0x00921880
void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                               const char* file, int line);
namespace eastl {
template <typename T1, typename T2>
struct pair_s005e_f440 {
  T1 first;
  T2 second;
};
}
namespace eastl {
template <typename K, typename V>
struct rbtree_node_s005e_f440 : public rbtree_node_base_s005e_f440 {
  pair_s005e_f440<K, V> mValue;
};
}
namespace eastl {
template <typename K, typename V>
struct rbtree_iterator_s005e_f440 {
  rbtree_node_s005e_f440<K, V>* mpNode;
  rbtree_iterator_s005e_f440() : mpNode(0) {}
  explicit rbtree_iterator_s005e_f440(rbtree_node_s005e_f440<K, V>* p) : mpNode(p) {}
  rbtree_iterator_s005e_f440& operator++() {
    mpNode = (rbtree_node_s005e_f440<K, V>*)RBTreeIncrement(mpNode);
    return *this;
  }
  bool operator!=(const rbtree_iterator_s005e_f440& x) const { return mpNode != x.mpNode; }
};
}
namespace eastl {
template <typename K, typename V>
class rbtree_s005e_f440 {
 public:
  typedef rbtree_node_s005e_f440<K, V> node_type;
  typedef rbtree_iterator_s005e_f440<K, V> iterator;
  typedef pair_s005e_f440<K, V> value_type;

  int mCompare;               // +0x0 (empty less<>)
  rbtree_node_base_s005e_f440 mAnchor;   // +0x4
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
  iterator DoInsertValueImpl(rbtree_node_base_s005e_f440* pNodeParent, const value_type& value, bool bForceToLeft);
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
typename rbtree_s005e_f440<K, V>::iterator rbtree_s005e_f440<K, V>::DoInsertValueImpl(rbtree_node_base_s005e_f440* pNodeParent,
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
typedef eastl::rbtree_s005e_f440<unsigned int, AutoRefCount_s005e_f440<SP::cSPSwatch_s005e_f440> > SwatchIDMap;
typedef eastl::rbtree_s005e_f440<AutoRefCount_s005e_f440<SP::cSPSwatch_s005e_f440>, float> SwatchFloatMap;
template SwatchFloatMap::iterator SwatchFloatMap::DoInsertValueImpl(eastl::rbtree_node_base_s005e_f440*, const SwatchFloatMap::value_type&, bool);
template unsigned int SwatchFloatMap::erase(const AutoRefCount_s005e_f440<SP::cSPSwatch_s005e_f440>&);
namespace SP {
class cICameraManager_s005e_f440 {
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
}
namespace SP {
cICameraManager_s005e_f440* CreateCameraManager();  // 0x007c7700
}
namespace SP {
void* CreateSwatchCamera();              // 0x005a4150
}
namespace SP {
class cSPPaletteItemRolloverRC {
 public:
  cSPPaletteItemRolloverRC(bool swatch);  // 0x005ed360
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Initialize();  // +0x1c
  uint32_t pad[0x31];
};
}
namespace SP {
class cISPCreatureAnimWorld_s005e_f440 {
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
}
namespace SP {
class cAnimWorldManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual cISPCreatureAnimWorld_s005e_f440* CreateAnimWorld(const wchar_t* name);  // +0x20
  PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual void SetDebugFlag(uint32_t id);  // +0x3c
};
}
namespace SP {
cAnimWorldManager* AnimWorldManager();  // 0x0067cb20
}
namespace SP {
class cRenderMgr { public: int GetRenderer(); };  // 0x006c10e0
}
namespace SP {
cRenderMgr* RenderManager();                       // 0x0067cad0
}
namespace SP {
class cSPUICursorManager {
 public:
  void AddCursor(uint32_t id, const wchar_t* name, bool a, int b, int c);  // 0x00802050
};
}
namespace SP {
cSPUICursorManager* CursorManager();  // 0x0067cab0
}
namespace SP {
struct AppPropertiesData { char pad[0x118]; int mDebugBlock; };
}
namespace SP {
struct AppProperties { char pad[0x3c]; AppPropertiesData* mpData; };
}
namespace SP {
extern AppProperties* sAppProperties;  // 0x015fd918
}
namespace SP {
class cSPSwatchManager : public EA::RefCountTemplate_s005e_f440<int> {
 public:
  cSPSwatch_s005e_f440* CreateSwatch(int flags);           // 0x005f0ca0
  cSPPaletteItemRollover_s005e_f440* GetSwatchRollover();  // 0x0113ae10
  void Init();
  void* LoadCreature(uint32_t a, uint32_t b);
  SwatchIDMap mIDToSwatchMap;                              // +0x8
  uint32_t pad24[8];                                       // +0x24
  AutoRefCount_s005e_f440<cSPPaletteItemRolloverRC> mSwatchRollover;  // +0x44
  AutoRefCount_s005e_f440<cSPPaletteItemRolloverRC> mModelRollover;   // +0x48
  AutoRefCount_s005e_f440<cISPCreatureAnimWorld_s005e_f440> mpCreatureAnimWorld; // +0x4c
  AutoRefCount_s005e_f440<cICameraManager_s005e_f440> mCameraManager;            // +0x50
};
}
// ---- items of slice s005ef440 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C++" void RBTreeInsert(eastl::rbtree_node_base_s005e_f440* pNode, eastl::rbtree_node_base_s005e_f440* pNodeParent,
                               eastl::rbtree_node_base_s005e_f440* pNodeAnchor, int insertionSide);  // 0x009216a0

// @ 0x005f0140
namespace SP {
void cSPSwatchManager::Init()
{
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
}  // namespace SP
