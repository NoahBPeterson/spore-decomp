// src/game/SPEditors/SPEditorManipulationSpineResize.cpp -- migrated from slice(s) s005bccc0, s005b85d0, s005b7460 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorManipulationSpineResize.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorAnimatedEventInfo.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorLimbStructure.h"
#include "SP/cSPEditorManipulationObject.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorSkinManager.h"
#include "SP/cSPEditorSkinPart.h"
#include "SP/cSPEditorSpine.h"
#include "SP/cViewer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
#include <new>
#include <math.h>
#include "SP/cSPEditorPhysicsWorld.h"
#include <string.h>

// ---- items of slice s005b7460 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, int debugFlags, const char* file, int line); // 0x00f473a0
#define PV_s005b_7460(n) virtual void pv##n();
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
class Vector3Template_s005b_7460 {
 public:
  T x, y, z;
  Vector3Template_s005b_7460() {}
  Vector3Template_s005b_7460(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005b_7460<T, N> operator+(const Vector3Template_s005b_7460<T, N>& a, const Vector3Template_s005b_7460<T, N>& b) {
  return Vector3Template_s005b_7460<T, N>(a.x + b.x, a.y + b.y, a.z + b.z);
}
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005b_7460<T, N> operator-(const Vector3Template_s005b_7460<T, N>& a, const Vector3Template_s005b_7460<T, N>& b) {
  return Vector3Template_s005b_7460<T, N>(a.x - b.x, a.y - b.y, a.z - b.z);
}
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005b_7460<T, N> operator*(const Vector3Template_s005b_7460<T, N>& a, T s) {
  return Vector3Template_s005b_7460<T, N>(a.x * s, a.y * s, a.z * s);
}
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline T Dot(const Vector3Template_s005b_7460<T, N>& a, const Vector3Template_s005b_7460<T, N>& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
}
}
}
struct cSPVector3_s005b_7460 : public rw::math::fpu::Vector3Template_s005b_7460<float, 0> {
  typedef rw::math::fpu::Vector3Template_s005b_7460<float, 0> base;
  cSPVector3_s005b_7460() {}
  cSPVector3_s005b_7460(float ax, float ay, float az) : base(ax, ay, az) {}
  cSPVector3_s005b_7460(const cSPVector3_s005b_7460& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3_s005b_7460(const base& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3_s005b_7460& operator=(const base& v) { x = v.x; y = v.y; z = v.z; return *this; }
  float Dot(const cSPVector3_s005b_7460& o) const { return x * o.x + y * o.y + z * o.z; }
};
struct cSPMatrix3_s005b_7460 { float m[9]; };
struct eastl_bitset54 {
  uint32_t mWord[2];
  bool test(unsigned int i) const { return ((mWord[i >> 5] >> (i & 31)) & 1) != 0; }
};
enum { kBlockFlagHidden = 7, kBlockFlagSkinPart = 11 };  // bit meanings guessed
namespace SP {
class cViewer_s005b_7460 {
 public:
  bool GetWorldRayFromScreenCoords(float x, float y, cSPVector3_s005b_7460& origin, cSPVector3_s005b_7460& direction);  // 0x007c4730 (SP::cViewer::GetWorldRayFromScreenCoords)
};
}
namespace SP {
class cSPApp {
 public:
  PV_s005b_7460(0) PV_s005b_7460(1) PV_s005b_7460(2) PV_s005b_7460(3) PV_s005b_7460(4) PV_s005b_7460(5) PV_s005b_7460(6) PV_s005b_7460(7) PV_s005b_7460(8) PV_s005b_7460(9) PV_s005b_7460(10)
  PV_s005b_7460(11) PV_s005b_7460(12) PV_s005b_7460(13) PV_s005b_7460(14) PV_s005b_7460(15) PV_s005b_7460(16) PV_s005b_7460(17) PV_s005b_7460(18) PV_s005b_7460(19) PV_s005b_7460(20) PV_s005b_7460(21)
  virtual cViewer_s005b_7460* GetViewer();
};
}
namespace SP {
cSPApp* App();
}
namespace SP {
class RefCountedBase {
 public:
  virtual ~RefCountedBase();
  volatile int mRefCount;
  void AddRef() { ++mRefCount; }
  int Release() {
    const int rc = --mRefCount;
    if (rc == 0) {
      mRefCount = 1;
      delete this;
    }
    return rc;
  }
};
}
namespace SP {
class cSPEditorModelBase { public: PV_s005b_7460(0) };
}
namespace SP {
class cSPEditorModel_s005b_7460 : public cSPEditorModelBase, public RefCountedBase {
 public:
  void SetUsingSymmetry(bool b);     // FUN_004adc20
  bool IsUsingSymmetry();            // FUN_004adc40
  void SetDirty(bool b);             // FUN_004adfc0
};
}
namespace SP {
class cSPEditorBlock_s005b_7460 {
 public:
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  char pad04[0x28 - 4];
  cSPEditorModel_s005b_7460* mEditorModel;  // +0x28
  char pad2c[0x48 - 0x2c];
  cSPVector3_s005b_7460 mPosition;          // +0x48
  char pad54[0x340 - 0x54];
  cSPEditorBlock_s005b_7460** mChildrenBegin;  // +0x340
  cSPEditorBlock_s005b_7460** mChildrenEnd;    // +0x344
  char pad348[0xdc8 - 0x348];
  eastl_bitset54 mFlags;            // +0xdc8 (eastl::bitset<54>)
  void SetHighlight(int color, int a, int b, int c);  // FUN_0043a5e0
};
}
namespace SP {
class cSPEditorSkinPart_s005b_7460;
}
namespace SP {
class cSPEditorSkinManager_s005b_7460 {
 public:
  virtual void AddRef();
  virtual void Release();
  struct Pinner { void Pin(cSPEditorBlock_s005b_7460* b); /* FUN_00438700 */ };
  bool Raycast(int a, cSPVector3_s005b_7460 origin, cSPVector3_s005b_7460 dir, cSPVector3_s005b_7460* hitPos, cSPVector3_s005b_7460* hitNormal, int b, int c);  // FUN_004c4a30
  Pinner* GetPinner(int a, cSPVector3_s005b_7460 pos);                                                                          // FUN_004c4d30
};
}
namespace SP {
class cSPEditorAppEconomy_s005b_7460;
}
namespace SP {
class cSPEditorLimbStructure_s005b_7460 { public: void Rebuild(); /* FUN_0048a4c0 */ };
}
namespace SP {
class cSPEditorSpinePart {
 public:
  PV_s005b_7460(0) PV_s005b_7460(1) PV_s005b_7460(2) PV_s005b_7460(3) PV_s005b_7460(4) PV_s005b_7460(5) PV_s005b_7460(6) PV_s005b_7460(7) PV_s005b_7460(8) PV_s005b_7460(9) PV_s005b_7460(10) PV_s005b_7460(11)
  virtual void SetState(int a, int b);  // +0x30
};
}
namespace SP {
class cSPEditorSpine_s005b_7460 {
 public:
  void MoveBlock(cSPEditorBlock_s005b_7460* block, cSPVector3_s005b_7460 origin, cSPVector3_s005b_7460 dir);   // FUN_005d3010
  void StartDrag(cSPEditorBlock_s005b_7460** block, cSPVector3_s005b_7460 origin, cSPVector3_s005b_7460 dir);  // FUN_005d43d0
  void Drag(cSPEditorBlock_s005b_7460** block, cSPVector3_s005b_7460 origin, cSPVector3_s005b_7460 dir);       // FUN_005d4630
  void Rebuild(bool a, bool b);                                              // FUN_005d1600
  cSPEditorSpinePart* GetPart(cSPEditorBlock_s005b_7460* block);                        // FUN_005ce270
  cSPEditorBlock_s005b_7460* GetFrontNext();                                            // FUN_005ce250
  cSPEditorBlock_s005b_7460* GetBackNext();                                             // FUN_005ce260
  char pad[0xe8];
  cSPEditorBlock_s005b_7460* mFrontBlock;  // +0xe8
  cSPEditorBlock_s005b_7460* mBackBlock;   // +0xec
};
}
namespace SP {
class cSPEditorAnimatedEventInfo_s005b_7460 {
 public:
  cSPEditorAnimatedEventInfo_s005b_7460();
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  void MessagePost(uint32_t id, cSPEditorBlock_s005b_7460* block, cSPEditorModel_s005b_7460* model, int a, int b, float c, int d, int e, float f);  // 0x0059d840 (SP::cSPEditorAnimatedEventInfo::MessagePost)
  char pad[0x30 - 4];
};
}
namespace SP {
class cSPEditorSkinPart_s005b_7460 {
 public:
  char pad[0xbc];
  struct Ref {
    virtual void AddRef();
    virtual void Release();
  } mRef;  // +0xbc
  void SetHighlight(bool on);  // FUN_004cca40
};
}
namespace SP {
namespace EditorUtils {
void RepinBlockToTorso(cSPEditorBlock_s005b_7460* block, cSPVector3_s005b_7460 pos, cSPMatrix3_s005b_7460 orient, int flag);
}
}
namespace SP {
namespace EditorUtils {
void UnpinBlock(cSPEditorBlock_s005b_7460* block, int flag);  // FUN_0049fee0
}
}
namespace EA {
template <typename T>
class AutoRefCount_s005b_7460 {
 public:
  T* mpObject;
  AutoRefCount_s005b_7460() : mpObject(0) {}
  AutoRefCount_s005b_7460(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005b_7460() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005b_7460& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005b_7460 {
 public:
  RefCountVTemplate_s005b_7460() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005b_7460() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
template <>
class AutoRefCount_s005b_7460<SP::cSPEditorSkinPart_s005b_7460> {
 public:
  SP::cSPEditorSkinPart_s005b_7460* mpObject;
  AutoRefCount_s005b_7460(const AutoRefCount_s005b_7460& x) : mpObject(x.mpObject) { if (mpObject) mpObject->mRef.AddRef(); }
  ~AutoRefCount_s005b_7460() { if (mpObject) mpObject->mRef.Release(); }
};
}
namespace eastl {
template <typename RandomAccessIterator, typename Distance, typename T>
inline void promote_heap(RandomAccessIterator first, Distance topPosition, Distance position, const T& value) {
  for (Distance parentPosition = (position - 1) >> 1; (position > topPosition) && (*(first + parentPosition) < value);
       parentPosition = (position - 1) >> 1) {
    *(first + position) = *(first + parentPosition);
    position = parentPosition;
  }
  *(first + position) = value;
}
}
namespace eastl {
template <typename RandomAccessIterator>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
  const float tempBottom(*(last - 1));
  *(last - 1) = *first;
  eastl::adjust_heap<RandomAccessIterator, int, float>(first, (int)0, (int)(last - first - 1), 0, tempBottom);
}
}
namespace eastl {
struct rbtree_node_base_s005b_7460 {
  rbtree_node_base_s005b_7460* mpNodeRight;
  rbtree_node_base_s005b_7460* mpNodeLeft;
  rbtree_node_base_s005b_7460* mpNodeParent;
  char mColor;
};
}
namespace eastl {
rbtree_node_base_s005b_7460* RBTreeIncrement(const rbtree_node_base_s005b_7460* pNode);
}
namespace eastl {
void RBTreeInsert(rbtree_node_base_s005b_7460* pNode, rbtree_node_base_s005b_7460* pNodeParent, rbtree_node_base_s005b_7460* pNodeAnchor, int insertionSide);
}
namespace eastl {
template <typename K, typename V>
struct pair_s005b_7460 {
  K first;
  V second;
};
}
namespace eastl {
typedef pair_s005b_7460<SP::cSPEditorBlock_s005b_7460* const, EA::AutoRefCount_s005b_7460<SP::cSPEditorSkinPart_s005b_7460> > BlockLimbPair;
}
namespace eastl {
struct rbtree_node_s005b_7460 : public rbtree_node_base_s005b_7460 {
  BlockLimbPair mValue;
};
}
namespace eastl {
struct rbtree_iterator_s005b_7460 {
  rbtree_node_s005b_7460* mpNode;
  rbtree_iterator_s005b_7460(rbtree_node_s005b_7460* p) : mpNode(p) {}
};
}
namespace eastl {
class allocator_s005b_7460 {
 public:
  const char* mpName;
};
}
namespace eastl {
class BlockLimbMap {
 public:
  int mCompare;                // empty less<> padded
  rbtree_node_base_s005b_7460 mAnchor;    // +4
  unsigned int mnSize;         // +0x14
  allocator_s005b_7460 mAllocator;        // +0x18

  ~BlockLimbMap() { DoNukeSubtree((rbtree_node_s005b_7460*)mAnchor.mpNodeParent); }

  void reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  void clear();

  rbtree_node_s005b_7460* DoCreateNode(const BlockLimbPair& value) {
    rbtree_node_s005b_7460* const pNode = (rbtree_node_s005b_7460*)EASTL_allocator_allocate(
        sizeof(rbtree_node_s005b_7460), "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    ::new (&pNode->mValue) BlockLimbPair(value);
    return pNode;
  }
  rbtree_iterator_s005b_7460 DoInsertValueImpl(rbtree_node_base_s005b_7460* pNodeParent, const BlockLimbPair& value, bool bForceToLeft);
  void DoNukeSubtree(rbtree_node_s005b_7460* pNode);
};
}
namespace eastl {
template <typename T>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  ~sp_vector() {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
};
}
namespace SP {
class cSPEditorManipulationObject_s005b_7460 {
 public:
  cSPEditorManipulationObject_s005b_7460();  // FUN_005b0f80
  virtual ~cSPEditorManipulationObject_s005b_7460() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};
}
namespace SP {
class cSPEditorManipulationSpineResize : public cSPEditorManipulationObject_s005b_7460, public EA::RefCountVTemplate_s005b_7460<int> {
 public:
  cSPEditorBlock_s005b_7460* mBlock;                                  // +0x1c
  cSPVector3_s005b_7460 mMouseOffset;                                 // +0x20
  eastl::sp_vector<cSPEditorLimbStructure_s005b_7460*> mLimbs;        // +0x2c
  cSPEditorSpine_s005b_7460* mSpine;                                  // +0x40
  EA::AutoRefCount_s005b_7460<cSPEditorSkinManager_s005b_7460> mSkinManager;     // +0x44
  cSPEditorAppEconomy_s005b_7460* mEconomy;                           // +0x48
  bool mHasRoutes;                                         // +0x4c
  float mFrontAnchor;                                      // +0x50
  float mBackAnchor;                                       // +0x54
  eastl::BlockLimbMap mBlockLimbs;                         // +0x58
  float mColorTimer;                                       // +0x74
  float mFrameDelay;                                       // +0x78
  bool mHasPlanePoint;                                     // +0x7c
  cSPVector3_s005b_7460 mPlanePoint;                                  // +0x80

  ~cSPEditorManipulationSpineResize();
  bool OnMouseUp(int button, float x, float y, int modifiers);
  cSPEditorBlock_s005b_7460* GetNextVertebra();
  void Init(cSPEditorBlock_s005b_7460* block, cSPVector3_s005b_7460 mouseOffset, cSPEditorSpine_s005b_7460* spine, cSPEditorSkinManager_s005b_7460* skinManager,
            cSPEditorAppEconomy_s005b_7460* economy);
  void UpdatePlanePoint(float x, float y);
  bool DoOnMouseDown(float x, float y, int modifiers);
  void RepinSimple();
  void SetBlockHighlight(cSPEditorBlock_s005b_7460* block, bool highlight);
};
}
namespace SP {
cSPMatrix3_s005b_7460 GetOrientationFromNormal(cSPEditorBlock_s005b_7460* block, cSPVector3_s005b_7460 normal);  // FUN_0049c140
}
// ---- items of slice s005b7460 end

// ---- items of slice s005b85d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
class Vector3Template_s005b_85d0 {
 public:
  T x, y, z;
  Vector3Template_s005b_85d0() {}
  Vector3Template_s005b_85d0(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
}
}
}
struct cSPVector3_s005b_85d0 : public rw::math::fpu::Vector3Template_s005b_85d0<float, 0> {
  typedef rw::math::fpu::Vector3Template_s005b_85d0<float, 0> base;
  cSPVector3_s005b_85d0() {}
  cSPVector3_s005b_85d0(float ax, float ay, float az) : base(ax, ay, az) {}
  cSPVector3_s005b_85d0(const cSPVector3_s005b_85d0& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3_s005b_85d0& operator=(const cSPVector3_s005b_85d0& v) { x = v.x; y = v.y; z = v.z; return *this; }
  float Dot(const cSPVector3_s005b_85d0& o) const { return x * o.x + y * o.y + z * o.z; }
};
namespace EA {
template <typename T>
class AutoRefCount_s005b_85d0 {
 public:
  T* mpObject;
  AutoRefCount_s005b_85d0() : mpObject(0) {}
  AutoRefCount_s005b_85d0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005b_85d0() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005b_85d0& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005b_85d0 {
 public:
  RefCountVTemplate_s005b_85d0() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005b_85d0() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace eastl {
template <typename T>
class sp_vector_s005b_85d0 {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  ~sp_vector_s005b_85d0() {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  void DoInsertValue(T* position, const T& value);
};
}
namespace eastl {
struct rbtree_node_base_s005b_85d0 {
  rbtree_node_base_s005b_85d0* mpNodeRight;
  rbtree_node_base_s005b_85d0* mpNodeLeft;
  rbtree_node_base_s005b_85d0* mpNodeParent;
  char mColor;
};
}
namespace eastl {
rbtree_node_base_s005b_85d0* RBTreeIncrement(const rbtree_node_base_s005b_85d0* pNode);
}
namespace eastl {
template <typename K, typename V>
struct pair_s005b_85d0 { K first; V second; };
}
namespace eastl {
class allocator_s005b_85d0 { public: const char* mpName; };
}
namespace SP {
class cSPEditorBlock_s005b_85d0;
}
namespace SP {
class cSPEditorModel_s005b_85d0;
}
namespace SP {
class cSPEditorSkinPart_s005b_85d0;
}
namespace SP {
class cSPEditorSkinManager_s005b_85d0;
}
namespace SP {
class cSPEditorAppEconomy_s005b_85d0;
}
namespace SP {
class cSPEditorSpine_s005b_85d0;
}
namespace SP {
class cSPEditorLimbStructure_s005b_85d0;
}
namespace SP {
class cSPEditorBlock_s005b_85d0 {
 public:
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  char pad04[0x28 - 4];
  cSPEditorModel_s005b_85d0* mEditorModel;  // +0x28
  char pad2c[0x48 - 0x2c];
  cSPVector3_s005b_85d0 mPosition;          // +0x48
  char pad54[0x340 - 0x54];
  cSPEditorBlock_s005b_85d0** mChildrenBegin;  // +0x340
  cSPEditorBlock_s005b_85d0** mChildrenEnd;    // +0x344
  char pad348[0xdc8 - 0x348];
  eastl_bitset54 mFlags;            // +0xdc8
  void SetHighlight(int color, int a, int b, int c);
};
}
namespace SP {
class cSPEditorSkinPart_s005b_85d0 {
 public:
  char pad[0xbc];
  struct Ref {
    virtual void AddRef();
    virtual void Release();
  } mRef;  // +0xbc
  void SetHighlight(bool on);
  void SetSomething(uint32_t id);  // FUN_004cd020
};
}
namespace SP {
class cSPEditorSkinManager_s005b_85d0 {
 public:
  virtual void AddRef();
  virtual void Release();
  char pad[0x200];
  cSPEditorSkinPart_s005b_85d0* GetSkinPart(cSPEditorBlock_s005b_85d0* block, int flags);  // FUN_004c44c0
};
}
namespace SP {
#define PV(n) virtual void pv##n();
}
namespace SP {
class cSPEditorSpinePart_s005b_85d0 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void SetState(int a, int b);  // +0x14
};
}
namespace SP {
class cSPEditorSpine_s005b_85d0 {
 public:
  cSPEditorSpinePart_s005b_85d0* GetPart(cSPEditorBlock_s005b_85d0* block);  // FUN_005ce270
  void Rebuild(bool a, bool b);                        // FUN_005d1600
  bool Check();                                        // FUN_005d4970
  void Rebuild2();                                     // FUN_005d1640
  char pad[0xe8];
  cSPEditorBlock_s005b_85d0* mFrontBlock;  // +0xe8
  cSPEditorBlock_s005b_85d0* mBackBlock;   // +0xec
};
}
namespace SP {
class cSPEditorLimbStructure_s005b_85d0 {
 public:
  cSPEditorLimbStructure_s005b_85d0();   // FUN_00488850
  ~cSPEditorLimbStructure_s005b_85d0();  // FUN_00488900
  void Cleanup();             // FUN_00488980
  void SetSource(cSPEditorLimbStructure_s005b_85d0* src, int a, int b);  // FUN_004891a0
};
}
namespace SP {
namespace EditorUtils {
void GetAllLimbs(cSPEditorBlock_s005b_85d0* block, eastl::sp_vector_s005b_85d0<cSPEditorBlock_s005b_85d0*>* out, int flag);  // FUN_004a0020
}
}
namespace SP {
namespace EditorUtils {
cSPEditorBlock_s005b_85d0* GetFirstFootBlock(cSPEditorBlock_s005b_85d0* block);                                   // FUN_004a9840
}
}
namespace SP {
void FUN_00438a40(cSPEditorBlock_s005b_85d0* child);
}
namespace SP {
void FUN_00438700(cSPEditorBlock_s005b_85d0* child);
}
namespace SP {
void FUN_004cced0(void* p);
}
namespace EA {
template <>
class AutoRefCount_s005b_85d0<SP::cSPEditorSkinPart_s005b_85d0> {
 public:
  SP::cSPEditorSkinPart_s005b_85d0* mpObject;
  AutoRefCount_s005b_85d0() : mpObject(0) {}
  AutoRefCount_s005b_85d0(const AutoRefCount_s005b_85d0& x) : mpObject(x.mpObject) {
    if (mpObject) mpObject->mRef.AddRef();
  }
  ~AutoRefCount_s005b_85d0() {
    if (mpObject) mpObject->mRef.Release();
  }
  AutoRefCount_s005b_85d0& operator=(SP::cSPEditorSkinPart_s005b_85d0* p) {
    if (p != mpObject) {
      SP::cSPEditorSkinPart_s005b_85d0* t = mpObject;
      if (p) p->mRef.AddRef();
      mpObject = p;
      if (t) t->mRef.Release();
    }
    return *this;
  }
  SP::cSPEditorSkinPart_s005b_85d0* operator->() const { return mpObject; }
  operator SP::cSPEditorSkinPart_s005b_85d0*() const { return mpObject; }
};  // namespace EA
}
namespace eastl {
using SP::cSPEditorBlock_s005b_85d0;
}
namespace eastl {
using SP::cSPEditorSkinPart_s005b_85d0;
}
namespace eastl {
typedef pair_s005b_85d0<cSPEditorBlock_s005b_85d0*, EA::AutoRefCount_s005b_85d0<cSPEditorSkinPart_s005b_85d0> > BlockLimbPair_s005b_85d0;
}
namespace eastl {
struct rbtree_node_s005b_85d0 : public rbtree_node_base_s005b_85d0 {
  BlockLimbPair_s005b_85d0 mValue;
};
}
namespace eastl {
struct rbtree_iterator_s005b_85d0 {
  rbtree_node_s005b_85d0* mpNode;
  rbtree_iterator_s005b_85d0(rbtree_node_s005b_85d0* p) : mpNode(p) {}
};
}
namespace eastl {
class BlockLimbMap_s005b_85d0 {
 public:
  int mCompare;              // +0x00 (empty eastl::less)
  rbtree_node_base_s005b_85d0 mAnchor;  // +0x04
  unsigned int mnSize;       // +0x14
  allocator_s005b_85d0 mAllocator;      // +0x18

  ~BlockLimbMap_s005b_85d0() { DoNukeSubtree((rbtree_node_s005b_85d0*)mAnchor.mpNodeParent); }

  void reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  rbtree_node_s005b_85d0* DoCreateNode(const BlockLimbPair_s005b_85d0& value) {
    rbtree_node_s005b_85d0* const pNode = (rbtree_node_s005b_85d0*)EASTL_allocator_allocate(
        sizeof(rbtree_node_s005b_85d0), "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    ::new (&pNode->mValue) BlockLimbPair_s005b_85d0(value);
    return pNode;
  }
  rbtree_iterator_s005b_85d0 DoInsertValueImpl(rbtree_node_base_s005b_85d0* pNodeParent, const BlockLimbPair_s005b_85d0& value, bool bForceToLeft);
  void DoNukeSubtree(rbtree_node_s005b_85d0* pNode);
  EA::AutoRefCount_s005b_85d0<cSPEditorSkinPart_s005b_85d0>* FindOrCreate(cSPEditorBlock_s005b_85d0* key);
};
}
namespace SP {
class cSPEditorManipulationObject_s005b_85d0 {
 public:
  cSPEditorManipulationObject_s005b_85d0();
  virtual ~cSPEditorManipulationObject_s005b_85d0() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};
}
namespace SP {
class cSPEditorManipulationSpineResize_s005b_85d0 : public cSPEditorManipulationObject_s005b_85d0, public EA::RefCountVTemplate_s005b_85d0<int> {
 public:
  cSPEditorBlock_s005b_85d0* mBlock;                               // +0x1c
  cSPVector3_s005b_85d0 mMouseOffset;                              // +0x20
  eastl::sp_vector_s005b_85d0<cSPEditorLimbStructure_s005b_85d0*> mLimbs;     // +0x2c
  cSPEditorSpine_s005b_85d0* mSpine;                               // +0x40
  EA::AutoRefCount_s005b_85d0<cSPEditorSkinManager_s005b_85d0> mSkinManager;  // +0x44
  cSPEditorAppEconomy_s005b_85d0* mEconomy;                        // +0x48
  bool mHasRoutes;                                      // +0x4c
  float mFrontAnchor;                                   // +0x50
  float mBackAnchor;                                    // +0x54
  eastl::BlockLimbMap_s005b_85d0 mBlockLimbs;                      // +0x58
  float mColorTimer;                                    // +0x74
  float mFrameDelay;                                    // +0x78
  bool mHasPlanePoint;                                  // +0x7c
  cSPVector3_s005b_85d0 mPlanePoint;                               // +0x80
  float mUnk8c;                                         // +0x8c

  cSPEditorManipulationSpineResize_s005b_85d0();
  void Shutdown();  // 0x005b87f0 (SP::cSPEditorManipulationSpineResize::Shutdown)
  bool OnMouseDown(int button, float x, float y, int modifiers);
  void UpdatePlanePoint(float x, float y);  // FUN_005b7b80 (preceding slice)
  void GenerateLimbs(cSPEditorBlock_s005b_85d0* block);  // 0x005b8da0 (SP::cSPEditorManipulationSpineResize::GenerateLimbs)
  bool HighlightDeleteBlockers(cSPEditorBlock_s005b_85d0* block);  // 0x005b8f20 (SP::cSPEditorManipulationSpineResize::HighlightDeleteBlockers)
  bool RepinBlocks();  // 0x005b8950 (SP::cSPEditorManipulationSpineResize::RepinBlocks)
  void DoOnMouseMove();  // 0x005b8fb0 (SP::cSPEditorManipulationSpineResize::DoOnMouseMove)
  void SetBlockHighlight(cSPEditorBlock_s005b_85d0* block, bool highlight);  // 0x005b7f70 (SP::cSPEditorManipulationSpineResize::SetBlockHighlight)
  void Update(float dt);  // 0x005b9430 (SP::cSPEditorManipulationSpineResize::Update)
};
}
namespace SP {
cSPEditorManipulationObject_s005b_85d0::cSPEditorManipulationObject_s005b_85d0() {}
}
namespace SP {
volatile int g_scratch_s005b85d0;
}
// ---- items of slice s005b85d0 end

// ---- items of slice s005bccc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPEditorPileList { void* p0; void* p1; void* p2; };
namespace SP {
class cSPEditorManipulationSpineResize_s005b_ccc0 {
 public:
  char pad[0x78];
  // @ 0x005bdc80
  cSPEditorPileList GetPileList();  // 0x005bdc80 (SP::cSPEditorManipulationSpineResize::GetPileList)
};
}
// ---- items of slice s005bccc0 end

// @ 0x005b7880
namespace eastl {
template <typename RandomAccessIterator> void insertion_sort(RandomAccessIterator first, RandomAccessIterator last)
{
  if (first != last) {
    for (RandomAccessIterator i = first + 1; i != last; ++i) {
      const float value(*i);
      RandomAccessIterator ins(i), insPrev(i);
      for (--insPrev; (ins != first) && (value < *insPrev); --ins, --insPrev)
        *ins = *insPrev;
      *ins = value;
    }
  }
}
}  // namespace eastl

// @ 0x005b78d0
namespace eastl {
template <typename RandomAccessIterator> void insertion_sort_simple(RandomAccessIterator first, RandomAccessIterator last)
{
  for (RandomAccessIterator current = first; current != last; ++current) {
    const float value(*current);
    RandomAccessIterator end(current), prev(current);
    for (--prev; value < *prev; --end, --prev)
      *end = *prev;
    *end = value;
  }
}
}  // namespace eastl

// @ 0x005b7920
namespace SP {
bool cSPEditorManipulationSpineResize::OnMouseUp(int button, float x, float y, int modifiers)
{
  if (mBlock && mSpine) {
    EditorUtils::UnpinBlock(mBlock, 0);
    if (mChangedObject) {
      EA::AutoRefCount_s005b_7460<cSPEditorAnimatedEventInfo_s005b_7460> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo_s005b_7460());
      info->MessagePost(0x503b1435, mBlock, mBlock == 0 ? 0 : mBlock->mEditorModel, 0, 0, 0.0f, 0, -1, 1.0f);
    }
    mSpine->Rebuild(false, true);
    mSpine->GetPart(mBlock)->SetState(3, 1);
    bool usingSymmetry = mBlock->mEditorModel->IsUsingSymmetry();
    mBlock->mEditorModel->SetUsingSymmetry(false);
    int count = mLimbs.size();
    for (int i = 0; i < count; i++)
      mLimbs[i]->Rebuild();
    mBlock->mEditorModel->SetUsingSymmetry(usingSymmetry);
  }
  mHasPlanePoint = false;
  return false;
}
}  // namespace SP

// @ 0x005b7a40
namespace SP {
cSPEditorBlock_s005b_7460* cSPEditorManipulationSpineResize::GetNextVertebra()
{
  if (mBlock == mSpine->mFrontBlock)
    return mSpine->GetFrontNext();
  if (mBlock == mSpine->mBackBlock)
    return mSpine->GetBackNext();
  return 0;
}
}  // namespace SP

// @ 0x005b7a70
namespace SP {
void cSPEditorManipulationSpineResize::Init(cSPEditorBlock_s005b_7460* block, cSPVector3_s005b_7460 mouseOffset, cSPEditorSpine_s005b_7460* spine, cSPEditorSkinManager_s005b_7460* skinManager, cSPEditorAppEconomy_s005b_7460* economy)
{
  mBlock = block;
  mMouseOffset = mouseOffset;
  mSpine = spine;
  mSkinManager = skinManager;
  mEconomy = economy;
}
}  // namespace SP

// @ 0x005b7af0
namespace eastl {
template <typename RandomAccessIterator, typename Distance, typename T> void adjust_heap(RandomAccessIterator first, Distance topPosition, Distance heapSize, Distance position, T value)
{
  Distance childPosition = (2 * position) + 2;
  for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
    if (*(first + childPosition) < *(first + (childPosition - 1)))
      --childPosition;
    *(first + position) = *(first + childPosition);
    position = childPosition;
  }
  if (childPosition == heapSize) {
    *(first + position) = *(first + (childPosition - 1));
    position = childPosition - 1;
  }
  eastl::promote_heap<RandomAccessIterator, Distance, T>(first, topPosition, position, value);
}
}  // namespace eastl

// @ 0x005b7b80
namespace SP {
void cSPEditorManipulationSpineResize::UpdatePlanePoint(float x, float y)
{
  cSPVector3_s005b_7460 point;
  if (mBlock && mSpine) {
    cSPVector3_s005b_7460 origin, dir;
    App()->GetViewer()->GetWorldRayFromScreenCoords(x, y, origin, dir);
    origin = origin + mMouseOffset;
    const cSPVector3_s005b_7460 normal(1.0f, 0.0f, 0.0f);
    float denom = dir.Dot(normal);
    if (denom != 0.0f) {
      float t = -(origin.Dot(normal) / denom);
      if (t >= 0.0f) {
        point = dir * t + origin;
        mPlanePoint = point;
        mPlanePoint.x = 0.0f;
        mHasPlanePoint = true;
        return;
      }
    }
    point = cSPVector3_s005b_7460(0.0f, 0.0f, 0.0f);
  } else {
    point = cSPVector3_s005b_7460(0.0f, 0.0f, 0.0f);
  }
  mPlanePoint = point;
  mHasPlanePoint = false;
}
}  // namespace SP

// @ 0x005b7cf0
namespace SP {
void cSPEditorManipulationSpineResize::RepinSimple()
{
  cSPEditorBlock_s005b_7460** end = mBlock->mChildrenEnd;
  for (cSPEditorBlock_s005b_7460** it = mBlock->mChildrenBegin; it != end; ++it) {
    EA::AutoRefCount_s005b_7460<cSPEditorBlock_s005b_7460> child(*it);
    if (!child->mFlags.test(kBlockFlagHidden)) {
      cSPVector3_s005b_7460 d = child->mPosition - mBlock->mPosition;
      float invLen = 1.0f / sqrtf(d.Dot(d) + 1e-8f);
      cSPVector3_s005b_7460 hitPos, hitNormal;
      if (mSkinManager->Raycast(0, mBlock->mPosition, d * invLen, &hitPos, &hitNormal, 0, 0)) {
        cSPMatrix3_s005b_7460 orient = GetOrientationFromNormal(child, hitNormal);
        EditorUtils::RepinBlockToTorso(child, hitPos, orient, 0);
        mSkinManager->GetPinner(0, hitPos)->Pin(child);
      }
    }
  }
}
}  // namespace SP

// @ 0x005b7f70
namespace SP {
void cSPEditorManipulationSpineResize::SetBlockHighlight(cSPEditorBlock_s005b_7460* block, bool highlight)
{
  int color = highlight ? 5 : 0;
  if (block) {
    if (block->mFlags.test(kBlockFlagSkinPart)) {
      for (eastl::rbtree_node_s005b_7460* it = (eastl::rbtree_node_s005b_7460*)mBlockLimbs.mAnchor.mpNodeLeft; it != (eastl::rbtree_node_s005b_7460*)&mBlockLimbs.mAnchor;
           it = (eastl::rbtree_node_s005b_7460*)eastl::RBTreeIncrement(it)) {
        if (it->mValue.first == block) {
          EA::AutoRefCount_s005b_7460<cSPEditorSkinPart_s005b_7460> part(it->mValue.second);
          part.mpObject->SetHighlight(highlight);
          break;
        }
      }
    } else if (!block->mFlags.test(kBlockFlagHidden)) {
      block->SetHighlight(color, 1, 0, 1);
    }
    cSPEditorBlock_s005b_7460** end = block->mChildrenEnd;
    for (cSPEditorBlock_s005b_7460** it = block->mChildrenBegin; it != end; ++it) {
      EA::AutoRefCount_s005b_7460<cSPEditorBlock_s005b_7460> child(*it);
      if (!child->mFlags.test(kBlockFlagHidden))
        SetBlockHighlight(child, highlight);
    }
  }
}
}  // namespace SP

// @ 0x005b8070
namespace eastl {
rbtree_iterator_s005b_7460 BlockLimbMap::DoInsertValueImpl(rbtree_node_base_s005b_7460* pNodeParent, const BlockLimbPair& value, bool bForceToLeft)
{
  int side;
  if (bForceToLeft || (pNodeParent == &mAnchor) || (value.first < ((rbtree_node_s005b_7460*)pNodeParent)->mValue.first))
    side = 0;
  else
    side = 1;
  rbtree_node_s005b_7460* const pNodeNew = DoCreateNode(value);
  RBTreeInsert(pNodeNew, pNodeParent, &mAnchor, side);
  mnSize++;
  return rbtree_iterator_s005b_7460(pNodeNew);
}
}  // namespace eastl

// @ 0x005b81a0
namespace eastl {
template <typename RandomAccessIterator> void make_heap(RandomAccessIterator first, RandomAccessIterator last)
{
  const int heapSize = (int)(last - first);
  if (heapSize >= 2) {
    int parentPosition = ((heapSize - 2) >> 1) + 1;
    do {
      --parentPosition;
      const float temp(*(first + parentPosition));
      eastl::adjust_heap<RandomAccessIterator, int, float>(first, parentPosition, heapSize, parentPosition, temp);
    } while (parentPosition != 0);
  }
}
}  // namespace eastl

// @ 0x005b81e0
namespace eastl {
template <typename RandomAccessIterator> void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
{
  for (; (last - first) > 1; --last)
    eastl::pop_heap<RandomAccessIterator>(first, last);
}
}  // namespace eastl

// @ 0x005b8230
namespace SP {
bool cSPEditorManipulationSpineResize::DoOnMouseDown(float x, float y, int modifiers)
{
  UpdatePlanePoint(x, y);
  return true;
}
}  // namespace SP

// @ 0x005b8250
namespace eastl {
void BlockLimbMap::DoNukeSubtree(rbtree_node_s005b_7460* pNode)
{
  while (pNode) {
    DoNukeSubtree((rbtree_node_s005b_7460*)pNode->mpNodeRight);
    rbtree_node_s005b_7460* const pNodeLeft = (rbtree_node_s005b_7460*)pNode->mpNodeLeft;
    pNode->mValue.~BlockLimbPair();
    EASTL_allocator_deallocate(pNode);
    pNode = pNodeLeft;
  }
}
}  // namespace eastl

// @ 0x005b82a0
namespace eastl {
template <typename RandomAccessIterator> void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last)
{
  eastl::make_heap<RandomAccessIterator>(first, middle);
  for (RandomAccessIterator i = middle; i < last; ++i) {
    if (*i < *first) {
      const float temp(*i);
      *i = *first;
      eastl::adjust_heap<RandomAccessIterator, int, float>(first, int(0), int(middle - first), int(0), temp);
    }
  }
  eastl::sort_heap<RandomAccessIterator>(first, middle);
}
}  // namespace eastl

// @ 0x005b8310
namespace eastl {
void BlockLimbMap::clear()
{
  DoNukeSubtree((rbtree_node_s005b_7460*)mAnchor.mpNodeParent);
  reset();
}
}  // namespace eastl

// @ 0x005b84f0
namespace SP {
cSPEditorManipulationSpineResize::~cSPEditorManipulationSpineResize()
{}
}  // namespace SP

// @ 0x005b85d0
namespace SP {
cSPEditorManipulationSpineResize_s005b_85d0::cSPEditorManipulationSpineResize_s005b_85d0()
: mBlock(0), mMouseOffset(0.0f, 0.0f, 0.0f), mSpine(0), mEconomy(0), mHasRoutes(false),
      mFrontAnchor(0.0f), mBackAnchor(0.0f), mColorTimer(0.0f), mFrameDelay(0.0f),
      mHasPlanePoint(false), mUnk8c(1.0f / 250.0f) {
  mChangedObject = false;
  mUseDeadZone = false;
}
}  // namespace SP

// @ 0x005b8690
namespace SP {
bool cSPEditorManipulationSpineResize_s005b_85d0::OnMouseDown(int button, float x, float y, int modifiers)
{
  (void)button;
  (void)modifiers;
  if (mBlock && mSpine) {
    eastl::sp_vector_s005b_85d0<cSPEditorBlock_s005b_85d0*> all;
    all.mpBegin = 0;
    all.mpEnd = 0;
    all.mpCapacity = 0;
    EditorUtils::GetAllLimbs(mBlock, &all, 0);
    int count = all.size();
    for (int i = 0; i < count; i++) {
      cSPEditorLimbStructure_s005b_85d0* limb = new ("Editor", 0, 0, 0, 0) cSPEditorLimbStructure_s005b_85d0();
      limb->SetSource((cSPEditorLimbStructure_s005b_85d0*)all[i], 0, 0);
      if (mLimbs.mpEnd < mLimbs.mpCapacity) {
        cSPEditorLimbStructure_s005b_85d0** p = mLimbs.mpEnd++;
        if (p)
          *p = limb;
      } else {
        mLimbs.DoInsertValue(mLimbs.mpEnd, limb);
      }
    }
    if (mSpine->Check()) {
      mHasRoutes = true;
      mSpine->Rebuild2();
      mFrontAnchor = *(float*)((char*)mSpine->mFrontBlock + 0xdc0);
      mBackAnchor = *(float*)((char*)mSpine->mBackBlock + 0xdc0);
    }
    mSpine->Rebuild(true, true);
    cSPEditorSpinePart_s005b_85d0* part = mSpine->GetPart(mBlock);
    part->SetState(2, 1);
    UpdatePlanePoint(x, y);
    if (all.mpBegin && ((int*)all.mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(all.mpBegin);
  }
  return false;
}
}  // namespace SP

// @ 0x005b87f0
namespace SP {
void cSPEditorManipulationSpineResize_s005b_85d0::Shutdown()
{
  mColorTimer = 0.0f;
  SetBlockHighlight(mBlock, false);
  cSPEditorSpinePart_s005b_85d0* part = mSpine->GetPart(mBlock);
  if (part)
    part->SetState(1, 0);
  int count = mLimbs.size();
  for (int i = 0; i < count; i++) {
    mLimbs[i]->Cleanup();
    cSPEditorLimbStructure_s005b_85d0* limb = mLimbs[i];
    if (limb) {
      limb->~cSPEditorLimbStructure_s005b_85d0();
      EASTL_allocator_deallocate(limb);
    }
  }
  mLimbs.mpEnd = mLimbs.mpBegin;
  eastl::rbtree_node_base_s005b_85d0* anchor = &mBlockLimbs.mAnchor;
  for (eastl::rbtree_node_base_s005b_85d0* it = mBlockLimbs.mAnchor.mpNodeLeft; it != anchor;
       it = eastl::RBTreeIncrement(it)) {
    FUN_004cced0(&((eastl::rbtree_node_s005b_85d0*)it)->mValue.second);
  }
  mBlockLimbs.DoNukeSubtree((eastl::rbtree_node_s005b_85d0*)mBlockLimbs.mAnchor.mpNodeParent);
  mBlockLimbs.reset();
}
}  // namespace SP

// @ 0x005b88d0
namespace eastl {
EA::AutoRefCount_s005b_85d0<SP::cSPEditorSkinPart_s005b_85d0>* BlockLimbMap_s005b_85d0::FindOrCreate(SP::cSPEditorBlock_s005b_85d0* key)
{
  rbtree_node_base_s005b_85d0* pNode = mAnchor.mpNodeParent;
  rbtree_node_base_s005b_85d0* pLower = &mAnchor;
  if (pNode) {
    do {
      if (((rbtree_node_s005b_85d0*)pNode)->mValue.first >= key) {
        pLower = pNode;
        pNode = pNode->mpNodeLeft;
      } else {
        pNode = pNode->mpNodeRight;
      }
    } while (pNode);
  }
  if (pLower != &mAnchor && !(key < ((rbtree_node_s005b_85d0*)pLower)->mValue.first))
    return &((rbtree_node_s005b_85d0*)pLower)->mValue.second;
  BlockLimbPair_s005b_85d0 kv;
  kv.first = key;
  kv.second = EA::AutoRefCount_s005b_85d0<SP::cSPEditorSkinPart_s005b_85d0>();
  rbtree_iterator_s005b_85d0 it = DoInsertValueImpl(pLower, kv, false);
  return &it.mpNode->mValue.second;
}
}  // namespace eastl

// @ 0x005b8950
namespace SP {
bool cSPEditorManipulationSpineResize_s005b_85d0::RepinBlocks()
{
  return false;
}
}  // namespace SP

// @ 0x005b8da0
namespace SP {
void cSPEditorManipulationSpineResize_s005b_85d0::GenerateLimbs(cSPEditorBlock_s005b_85d0* block)
{
  eastl::sp_vector_s005b_85d0<cSPEditorBlock_s005b_85d0*> found;
  found.mpBegin = 0;
  found.mpEnd = 0;
  found.mpCapacity = 0;
  cSPEditorBlock_s005b_85d0** end = block->mChildrenEnd;
  for (cSPEditorBlock_s005b_85d0** it = block->mChildrenBegin; it != end; ++it) {
    EA::AutoRefCount_s005b_85d0<cSPEditorBlock_s005b_85d0> child(*it);
    if (child->mFlags.test(kBlockFlagSkinPart) && EditorUtils::GetFirstFootBlock(child) != 0) {
      if (found.mpEnd < found.mpCapacity) {
        cSPEditorBlock_s005b_85d0** p = found.mpEnd++;
        if (p)
          *p = child;
      } else {
        found.DoInsertValue(found.mpEnd, (cSPEditorBlock_s005b_85d0*)child);
      }
    }
  }
  if (found.mpBegin != found.mpEnd) {
    for (cSPEditorBlock_s005b_85d0** it = found.mpBegin; it != found.mpEnd; ++it) {
      cSPEditorBlock_s005b_85d0* child = *it;
      FUN_00438a40(child);
      cSPEditorSkinPart_s005b_85d0* part = mSkinManager->GetSkinPart(child, 0x20000000);
      part->SetSomething(0xa76db9a6);
      *(char*)((char*)part + 300) = 1;
      EA::AutoRefCount_s005b_85d0<cSPEditorSkinPart_s005b_85d0>* slot = mBlockLimbs.FindOrCreate(child);
      cSPEditorSkinPart_s005b_85d0* old = slot->mpObject;
      if (part != old) {
        if (part)
          part->mRef.AddRef();
        slot->mpObject = part;
        if (old)
          old->mRef.Release();
      }
      FUN_00438700(child);
    }
  }
  if (found.mpBegin && ((int*)found.mpBegin)[-1] != 0)
    EASTL_allocator_deallocate(found.mpBegin);
}
}  // namespace SP

// @ 0x005b8f20
namespace SP {
bool cSPEditorManipulationSpineResize_s005b_85d0::HighlightDeleteBlockers(cSPEditorBlock_s005b_85d0* block)
{
  cSPEditorBlock_s005b_85d0** end = block->mChildrenEnd;
  bool result = true;
  for (cSPEditorBlock_s005b_85d0** it = block->mChildrenBegin; it != end; ++it) {
    EA::AutoRefCount_s005b_85d0<cSPEditorBlock_s005b_85d0> child(*it);
    if (child->mFlags.test(kBlockFlagSkinPart) && EditorUtils::GetFirstFootBlock(child) != 0) {
      if (mBlockLimbs.mnSize == 0)
        GenerateLimbs(mBlock);
      SetBlockHighlight(child, true);
      result = false;
    }
  }
  return result;
}
}  // namespace SP

// @ 0x005b8fb0
namespace SP {
__declspec(noinline) void cSPEditorManipulationSpineResize_s005b_85d0::DoOnMouseMove()
{ g_scratch_s005b85d0 = 1; }
}  // namespace SP

// @ 0x005b9430
namespace SP {
void cSPEditorManipulationSpineResize_s005b_85d0::Update(float dt)
{
  float delta = dt * 0.001f;
  if (mColorTimer > 0.0f) {
    float f = mColorTimer - delta;
    mColorTimer = f;
    if (f <= 0.0f) {
      mColorTimer = 0.0f;
      SetBlockHighlight(mBlock, false);
    }
  }
  if (mFrameDelay > 0.0f) {
    mFrameDelay = mFrameDelay - delta;
  }
  if (mFrameDelay <= 0.0f && mHasPlanePoint) {
    DoOnMouseMove();
  }
}
}  // namespace SP

// @ 0x005bdc80
namespace SP {
cSPEditorPileList cSPEditorManipulationSpineResize_s005b_ccc0::GetPileList()
{
  cSPEditorPileList v;
  v.p0 = 0;
  v.p1 = 0;
  v.p2 = 0;
  return v;
}
}  // namespace SP
