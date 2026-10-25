// Slice s005b85d0 -- SP::cSPEditorManipulationSpineResize (Spore creature editor)
// Flags for this region: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (no /EHsc)
#include <new>
#include <math.h>
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, int debugFlags, const char* file, int line); // 0x00f473a0

namespace rw { namespace math { namespace fpu {
template <typename T, int N>
class Vector3Template {
 public:
  T x, y, z;
  Vector3Template() {}
  Vector3Template(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
}}}
struct cSPVector3 : public rw::math::fpu::Vector3Template<float, 0> {
  typedef rw::math::fpu::Vector3Template<float, 0> base;
  cSPVector3() {}
  cSPVector3(float ax, float ay, float az) : base(ax, ay, az) {}
  float Dot(const cSPVector3& o) const { return x * o.x + y * o.y + z * o.z; }
  cSPVector3 operator-(const cSPVector3& o) const { return cSPVector3(x - o.x, y - o.y, z - o.z); }
  cSPVector3 operator*(float s) const { return cSPVector3(x * s, y * s, z * s); }
};
struct cSPMatrix3 {
  float m[9];
  cSPMatrix3& Assign(const cSPMatrix3& o);  // 0x0041cb40
};
struct cSPVector2 { float x, y; };

struct TorsoFlags {
  TorsoFlags() : mA(false), mB(false) {}
  TorsoFlags(bool a, bool b) : mA(a), mB(b) {}
  bool mA;
  bool mB;
};

struct Leg {
  char pad[0xdc0];
  float mParam0;  // +0xdc0
  float mParam1;  // +0xdc4
};

struct eastl_bitset54 {
  uint32_t mWord[2];
  bool test(unsigned int i) const { return ((mWord[i >> 5] >> (i & 31)) & 1) != 0; }
};
enum { kBlockFlagHidden = 7, kBlockFlagSkinPart = 11 };

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
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
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
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
}  // namespace EA

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
  void DoInsertValue(T* position, const T& value);
};
void vector_DoInsertValue_thunk(void* self, void* position, const void* value);

struct rbtree_node_base {
  rbtree_node_base* mpNodeRight;
  rbtree_node_base* mpNodeLeft;
  rbtree_node_base* mpNodeParent;
  char mColor;
};
rbtree_node_base* RBTreeIncrement(const rbtree_node_base* pNode);
void RBTreeInsert(rbtree_node_base* pNode, rbtree_node_base* pNodeParent, rbtree_node_base* pNodeAnchor, int insertionSide);

template <typename K, typename V>
struct pair { K first; V second; };

class allocator { public: const char* mpName; };
}  // namespace eastl

namespace SP {

class cSPEditorBlock;
class cSPEditorModel;
class cSPEditorSkinPart;
class cSPEditorSkinManager;
class cSPEditorAppEconomy;
class cSPEditorSpine;
class cSPEditorLimbStructure;
struct cSPEditorTuning;

// 3-pointer float vector; push_back is inline with an out-of-line DoInsertValue slow path.
class FloatVector {
 public:
  float* mpBegin;
  float* mpEnd;
  float* mpCapacity;
  FloatVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~FloatVector() {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
  void push_back(const float& v) {
    if (mpEnd < mpCapacity) {
      float* p = mpEnd++;
      if (p)
        *p = v;
    } else {
      DoInsertValue(mpEnd, v);
    }
  }
  void DoInsertValue(float* position, const float& value);  // 0x00455660
};

class cSPEditorBlock {
 public:
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  char pad04[0x28 - 4];
  cSPEditorModel* mEditorModel;  // +0x28
  char pad2c[0x48 - 0x2c];
  cSPVector3 mPosition;          // +0x48
  char pad54[0x60 - 0x54];
  cSPMatrix3 mOrientation;       // +0x60
  char pad84[0x1d8 - 0x84];
  float mScale;                  // +0x1d8
  char pad1dc[0x340 - 0x1dc];
  cSPEditorBlock** mChildrenBegin;  // +0x340
  cSPEditorBlock** mChildrenEnd;    // +0x344
  char pad348[0xdc0 - 0x348];
  float mParam0;                 // +0xdc0
  float mParam1;                 // +0xdc4
  eastl_bitset54 mFlags;         // +0xdc8
  void SetHighlight(int color, int a, int b, int c);
};

class cSPEditorSkinPart {
 public:
  char pad[0xbc];
  struct Ref {
    virtual void AddRef();
    virtual void Release();
  } mRef;  // +0xbc
  void SetHighlight(bool on);
  void SetSomething(uint32_t id);  // FUN_004cd020
};

class cSPEditorSkinManager {
 public:
  virtual void AddRef();
  virtual void Release();
  char pad[0x200];
  cSPEditorSkinPart* GetSkinPart(cSPEditorBlock* block, int flags);  // FUN_004c44c0
  void UpdateTorso(TorsoFlags flags, int x);                         // FUN_004c3230
};

#define PV(n) virtual void pv##n();
class cSPEditorSpinePart {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void SetState(int a, int b);  // +0x14
};
#undef PV

class cSPEditorSpine {
 public:
  cSPEditorSpinePart* GetPart(cSPEditorBlock* block);  // FUN_005ce270
  void Rebuild(bool a, bool b);                        // FUN_005d1600
  bool Check();                                        // FUN_005d4970
  void Rebuild2();                                     // FUN_005d1640
  Leg* GetFirstLeg();                                  // FUN_005d0ce0
  Leg* GetLastLeg();                                   // FUN_005d0d90
  cSPVector2* NearestParam(cSPVector2* res, Leg* node);  // FUN_005cf110
  void Rescale(FloatVector* front, FloatVector* back);   // FUN_005d1780
  void RepinArea(float lo, float hi, cSPEditorSkinManager* skin);  // FUN_005d19e0
  float GetRadius();                                   // FUN_005cd990
  void Interp(float t, float s, float* a, float* b);   // FUN_005cd870
  cSPEditorBlock* GrowVertebra(cSPEditorBlock* block, cSPVector3* dir, cSPMatrix3* mat);  // FUN_005d27e0
  void RemoveVertebra(cSPEditorBlock* block);          // FUN_005d3300
  char pad[0xe0];
  unsigned int mCount;          // +0xe0
  int mUnkE4;                   // +0xe4
  cSPEditorBlock* mFrontBlock;  // +0xe8
  cSPEditorBlock* mBackBlock;   // +0xec
  char padF0[0x11c - 0xf0];
  float mRadius;                // +0x11c
};

class cSPEditorLimbStructure {
 public:
  cSPEditorLimbStructure();   // FUN_00488850
  ~cSPEditorLimbStructure();  // FUN_00488900
  void Cleanup();             // FUN_00488980
  void SetSource(cSPEditorLimbStructure* src, int a, int b);  // FUN_004891a0
  void Refresh(bool a);       // FUN_004890e0
  void FixAllJoints();        // FUN_00489ae0
};

class cSPEditorModel {
 public:
  char pad[0x4f];
  bool mUsingSymmetry;  // +0x4f
  bool IsUsingSymmetry() const;          // FUN_004adc40
  void SetUsingSymmetry(bool on);        // FUN_004adc20
};

class cSPEditorAppEconomy {
 public:
  virtual void e0();
  virtual void e1();
  virtual void e2();
  virtual void e3();
  virtual void e4();
  virtual void e5();
  virtual void e6();
  virtual void e7();
  virtual void e8();
  virtual void e9();
  virtual bool CanAffordBlock(cSPEditorBlock* block);  // vtable +0x28
};

class cSPEditorTuning {
 public:
  char pad[0x1c];
  float mSpineHandleDistance;  // +0x1c
};
cSPEditorTuning* EditorTuning();  // FUN_00401070

// free helpers
void quick_sort(float* begin, float* end);                                   // FUN_005b8560
void AxisAngleMatrix(cSPMatrix3* out, const cSPVector3* axis, float angle);   // FUN_00576b00
float FUN_0069b760(const cSPVector3* a, const cSPVector3* b, const cSPVector3* axis);  // FUN_0069b760
void SetSoundSymbol(uint32_t a, uint32_t b, const char* name);               // FUN_00572070
void RecordEvent4(uint32_t a, uint32_t b, float c, int d);                   // FUN_00435f40
void KillSeti(int id);                                                       // FUN_004a88d0

extern const cSPVector3 g_spineAxisFront;   // 0x015134c8
extern const cSPVector3 g_spineAxisBack;    // 0x015134bc
extern const cSPVector3 g_spineAxisX;       // 0x01513350
extern float g_spineAngleLimit;             // 0x01513340
extern float g_spineAngleAdjust;            // 0x015ea4c8
extern float g_eps;                         // 0x013f7748
extern float g_soundScale;                  // 0x013ec478

namespace EditorUtils {
void GetAllLimbs(cSPEditorBlock* block, eastl::sp_vector<cSPEditorBlock*>* out, int flag);  // FUN_004a0020
cSPEditorBlock* GetFirstFootBlock(cSPEditorBlock* block);                                   // FUN_004a9840
}  // namespace EditorUtils

// free helpers referenced by GenerateLimbs
void FUN_00438a40(cSPEditorBlock* child);
void FUN_004cd020(cSPEditorSkinPart* part, uint32_t id);
void FUN_00438700(cSPEditorBlock* child);
void FUN_004cced0(void* p);

}  // namespace SP

namespace EA {
template <>
class AutoRefCount<SP::cSPEditorSkinPart> {
 public:
  SP::cSPEditorSkinPart* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) {
    if (mpObject) mpObject->mRef.AddRef();
  }
  ~AutoRefCount() {
    if (mpObject) mpObject->mRef.Release();
  }
  AutoRefCount& operator=(SP::cSPEditorSkinPart* p) {
    if (p != mpObject) {
      SP::cSPEditorSkinPart* t = mpObject;
      if (p) p->mRef.AddRef();
      mpObject = p;
      if (t) t->mRef.Release();
    }
    return *this;
  }
  SP::cSPEditorSkinPart* operator->() const { return mpObject; }
  operator SP::cSPEditorSkinPart*() const { return mpObject; }
};
}  // namespace EA

// ---------- eastl rbtree map used by cSPEditorManipulationSpineResize ----------
namespace eastl {
using SP::cSPEditorBlock;
using SP::cSPEditorSkinPart;
typedef pair<cSPEditorBlock*, EA::AutoRefCount<cSPEditorSkinPart> > BlockLimbPair;

struct rbtree_node : public rbtree_node_base {
  BlockLimbPair mValue;
};

struct rbtree_iterator {
  rbtree_node* mpNode;
  rbtree_iterator(rbtree_node* p) : mpNode(p) {}
};

class BlockLimbMap {
 public:
  int mCompare;              // +0x00 (empty eastl::less)
  rbtree_node_base mAnchor;  // +0x04
  unsigned int mnSize;       // +0x14
  allocator mAllocator;      // +0x18

  ~BlockLimbMap() { DoNukeSubtree((rbtree_node*)mAnchor.mpNodeParent); }

  void reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  rbtree_node* DoCreateNode(const BlockLimbPair& value) {
    rbtree_node* const pNode = (rbtree_node*)EASTL_allocator_allocate(
        sizeof(rbtree_node), "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    ::new (&pNode->mValue) BlockLimbPair(value);
    return pNode;
  }
  rbtree_iterator DoInsertValueImpl(rbtree_node_base* pNodeParent, const BlockLimbPair& value, bool bForceToLeft);
  // The hinted insert FindOrCreate actually calls: it re-validates the hint against the root
  // and the anchor (walking one step when the hint sits at either end) and then forwards to
  // DoInsertValueImpl with the side it computed. Calling the bare DoInsertValueImpl with the
  // hint as parent corrupts a warm tree, so this stays a separate entry point.
  rbtree_iterator DoInsertValueWithHint(rbtree_node_base* pHint, const BlockLimbPair& value, bool bForceToLeft);  // 0x005b8340
  void DoNukeSubtree(rbtree_node* pNode);
  void clear();  // 0x005b8310 (defined in another slice)
  EA::AutoRefCount<cSPEditorSkinPart>* FindOrCreate(cSPEditorBlock* const& key);
};
}  // namespace eastl

namespace SP {

class cSPEditorManipulationObject {
 public:
  cSPEditorManipulationObject();
  virtual ~cSPEditorManipulationObject() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};

class cSPEditorManipulationSpineResize : public cSPEditorManipulationObject, public EA::RefCountVTemplate<int> {
 public:
  cSPEditorBlock* mBlock;                               // +0x1c
  cSPVector3 mMouseOffset;                              // +0x20
  eastl::sp_vector<cSPEditorLimbStructure*> mLimbs;     // +0x2c
  cSPEditorSpine* mSpine;                               // +0x40
  EA::AutoRefCount<cSPEditorSkinManager> mSkinManager;  // +0x44
  cSPEditorAppEconomy* mEconomy;                        // +0x48
  bool mHasRoutes;                                      // +0x4c
  float mFrontAnchor;                                   // +0x50
  float mBackAnchor;                                    // +0x54
  eastl::BlockLimbMap mBlockLimbs;                      // +0x58
  float mColorTimer;                                    // +0x74
  float mFrameDelay;                                    // +0x78
  bool mHasPlanePoint;                                  // +0x7c
  cSPVector3 mPlanePoint;                               // +0x80
  float mUnk8c;                                         // +0x8c

  cSPEditorManipulationSpineResize();
  void Shutdown();
  bool OnMouseDown(int button, float x, float y, int modifiers);
  void UpdatePlanePoint(float x, float y);  // FUN_005b7b80 (preceding slice)
  void GenerateLimbs(cSPEditorBlock* block);
  bool HighlightDeleteBlockers(cSPEditorBlock* block);
  bool RepinBlocks();
  void DoOnMouseMove();
  void SetBlockHighlight(cSPEditorBlock* block, bool highlight);
  void Update(float dt);
  cSPEditorBlock* GetNextVertebra();  // FUN_005b7a40
  void RepinSimple();                 // FUN_005b7cf0
};

cSPEditorManipulationObject::cSPEditorManipulationObject() {}

// @ 0x005b85d0
cSPEditorManipulationSpineResize::cSPEditorManipulationSpineResize()
    : mBlock(0), mMouseOffset(0.0f, 0.0f, 0.0f), mSpine(0), mEconomy(0), mHasRoutes(false),
      mFrontAnchor(0.0f), mBackAnchor(0.0f), mColorTimer(0.0f), mFrameDelay(0.0f),
      mHasPlanePoint(false), mUnk8c(1.0f / 250.0f) {
  mChangedObject = false;
  mUseDeadZone = false;
}

// @ 0x005b87f0
void cSPEditorManipulationSpineResize::Shutdown() {
  mColorTimer = 0.0f;
  SetBlockHighlight(mBlock, false);
  cSPEditorSpinePart* part = mSpine->GetPart(mBlock);
  if (part)
    part->SetState(1, 0);
  int count = mLimbs.size();
  for (int i = 0; i < count; i++) {
    mLimbs[i]->Cleanup();
    cSPEditorLimbStructure* limb = mLimbs[i];
    if (limb) {
      limb->~cSPEditorLimbStructure();
      EASTL_allocator_deallocate(limb);
    }
  }
  mLimbs.mpEnd = mLimbs.mpBegin;
  eastl::rbtree_node_base* anchor = &mBlockLimbs.mAnchor;
  for (eastl::rbtree_node_base* it = mBlockLimbs.mAnchor.mpNodeLeft; it != anchor;
       it = eastl::RBTreeIncrement(it)) {
    FUN_004cced0(&((eastl::rbtree_node*)it)->mValue.second);
  }
  mBlockLimbs.DoNukeSubtree((eastl::rbtree_node*)mBlockLimbs.mAnchor.mpNodeParent);
  mBlockLimbs.reset();
}

// @ 0x005b8690
bool cSPEditorManipulationSpineResize::OnMouseDown(int button, float x, float y, int modifiers) {
  (void)button;
  (void)modifiers;
  if (mBlock && mSpine) {
    eastl::sp_vector<cSPEditorBlock*> all;
    all.mpBegin = 0;
    all.mpEnd = 0;
    all.mpCapacity = 0;
    EditorUtils::GetAllLimbs(mBlock, &all, 0);
    int count = all.size();
    for (int i = 0; i < count; i++) {
      cSPEditorLimbStructure* limb = new ("Editor", 0, 0, 0, 0) cSPEditorLimbStructure();
      limb->SetSource((cSPEditorLimbStructure*)all[i], 0, 0);
      if (mLimbs.mpEnd < mLimbs.mpCapacity) {
        cSPEditorLimbStructure** p = mLimbs.mpEnd++;
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
    cSPEditorSpinePart* part = mSpine->GetPart(mBlock);
    part->SetState(2, 1);
    UpdatePlanePoint(x, y);
    if (all.mpBegin && ((int*)all.mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(all.mpBegin);
  }
  return false;
}

// @ 0x005b8da0
void cSPEditorManipulationSpineResize::GenerateLimbs(cSPEditorBlock* block) {
  eastl::sp_vector<cSPEditorBlock*> found;
  found.mpBegin = 0;
  found.mpEnd = 0;
  found.mpCapacity = 0;
  cSPEditorBlock** end = block->mChildrenEnd;
  for (cSPEditorBlock** it = block->mChildrenBegin; it != end; ++it) {
    EA::AutoRefCount<cSPEditorBlock> child(*it);
    if (child->mFlags.test(kBlockFlagSkinPart) && EditorUtils::GetFirstFootBlock(child) != 0) {
      if (found.mpEnd < found.mpCapacity) {
        cSPEditorBlock** p = found.mpEnd++;
        if (p)
          *p = child;
      } else {
        found.DoInsertValue(found.mpEnd, (cSPEditorBlock*)child);
      }
    }
  }
  if (found.mpBegin != found.mpEnd) {
    for (cSPEditorBlock** it = found.mpBegin; it != found.mpEnd; ++it) {
      cSPEditorBlock* child = *it;
      FUN_00438a40(child);
      cSPEditorSkinPart* part = mSkinManager->GetSkinPart(child, 0x20000000);
      part->SetSomething(0xa76db9a6);
      *(char*)((char*)part + 300) = 1;
      EA::AutoRefCount<cSPEditorSkinPart>* slot = mBlockLimbs.FindOrCreate(child);
      cSPEditorSkinPart* old = slot->mpObject;
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

// @ 0x005b8f20
bool cSPEditorManipulationSpineResize::HighlightDeleteBlockers(cSPEditorBlock* block) {
  cSPEditorBlock** end = block->mChildrenEnd;
  bool result = true;
  for (cSPEditorBlock** it = block->mChildrenBegin; it != end; ++it) {
    EA::AutoRefCount<cSPEditorBlock> child(*it);
    if (child->mFlags.test(kBlockFlagSkinPart) && EditorUtils::GetFirstFootBlock(child) != 0) {
      if (mBlockLimbs.mnSize == 0)
        GenerateLimbs(mBlock);
      SetBlockHighlight(child, true);
      result = false;
    }
  }
  return result;
}

// @ 0x005b9430
void cSPEditorManipulationSpineResize::Update(float dt) {
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

// @ 0x005b8950
bool cSPEditorManipulationSpineResize::RepinBlocks() {
  mSkinManager->UpdateTorso(TorsoFlags(false, false), 0);
  if (!mHasRoutes) {
    if (!mSpine->Check())
      return false;
    mSpine->Rebuild2();
    mFrontAnchor = mSpine->mFrontBlock->mParam0;
    mBackAnchor = mSpine->mBackBlock->mParam0;
    mHasRoutes = true;
    return false;
  }
  FloatVector front;
  FloatVector back;
  front.push_back(0.0f);
  front.push_back(1.0f);
  back.push_back(0.0f);
  back.push_back(1.0f);
  if (!mSpine->Check())
    return false;
  cSPEditorBlock* frontBlock = mSpine->mFrontBlock;
  cSPEditorBlock* backBlock = mSpine->mBackBlock;
  float lo = 0.0f;
  float hi = 1.0f;
  bool keep = true;
  if (mBlock == frontBlock) {
    Leg* leg = mSpine->GetFirstLeg();
    if (leg) {
      cSPVector2 legPos;
      legPos.x = leg->mParam0;
      legPos.y = leg->mParam1;
      cSPVector2 nearest;
      mSpine->NearestParam(&nearest, leg);
      keep = (mFrontAnchor + g_eps < legPos.x);
      front.push_back(legPos.x);
      back.push_back(nearest.x);
      hi = nearest.x - g_eps;
    }
    if (keep) {
      front.push_back(mFrontAnchor);
      back.push_back(frontBlock->mParam0);
    }
    front.push_back(mBackAnchor);
    back.push_back(backBlock->mParam0);
  } else {
    Leg* leg = mSpine->GetLastLeg();
    if (leg) {
      cSPVector2 legPos;
      legPos.x = leg->mParam0;
      legPos.y = leg->mParam1;
      cSPVector2 nearest;
      mSpine->NearestParam(&nearest, leg);
      keep = (legPos.x < mBackAnchor - g_eps);
      front.push_back(legPos.x);
      back.push_back(nearest.x);
      lo = nearest.x + g_eps;
    }
    front.push_back(mFrontAnchor);
    back.push_back(frontBlock->mParam0);
    if (keep) {
      front.push_back(mBackAnchor);
      back.push_back(backBlock->mParam0);
    }
  }
  quick_sort(front.mpBegin, front.mpEnd);
  quick_sort(back.mpBegin, back.mpEnd);
  mSpine->Rescale(&front, &back);
  mSpine->RepinArea(lo, hi, mSkinManager);
  mFrontAnchor = mSpine->mFrontBlock->mParam0;
  mBackAnchor = mSpine->mBackBlock->mParam0;
  return true;
}

// @ 0x005b8fb0
void cSPEditorManipulationSpineResize::DoOnMouseMove() {
  if (!mBlock || !mSpine)
    return;
  cSPMatrix3 mat;
  mat.Assign(mBlock->mOrientation);
  const cSPVector3& axis = (mBlock == mSpine->mFrontBlock) ? g_spineAxisFront : g_spineAxisBack;
  float ny = axis.z * mat.m[7] + axis.y * mat.m[4] + axis.x * mat.m[1];
  float nz = axis.z * mat.m[8] + axis.y * mat.m[5] + axis.x * mat.m[2];
  float invLen = 1.0f / sqrtf(ny * ny + nz * nz);
  cSPVector3 dir;
  dir = cSPVector3(0.0f, ny, nz) * invLen;
  cSPVector3 delta = mPlanePoint - mBlock->mPosition;
  if (!mSpine->GetPart(mBlock))
    return;
  float dist = delta.z * dir.z + delta.y * dir.y + delta.x * dir.x;
  dist -= EditorTuning()->mSpineHandleDistance;
  if (fabsf(dist) > mSpine->GetRadius() * 2.0f) {
    if (dist > 0.0f && mSpine->mCount < 0x14 && mEconomy->CanAffordBlock(mBlock)) {
      float scale = mBlock->mScale;
      float angLo;
      float angHi;
      mSpine->Interp(scale, scale, &angLo, &angHi);
      float angle = FUN_0069b760(&dir, &delta, &g_spineAxisX);
      if (angle > g_spineAngleLimit)
        angle -= g_spineAngleAdjust;
      angle = (angle < angLo) ? angLo : angle;
      angle = (angle > angHi) ? angHi : angle;
      AxisAngleMatrix(&mat, &g_spineAxisX, angle);
      cSPEditorBlock* grown = mSpine->GrowVertebra(mBlock, &dir, &mat);
      if (grown) {
        mColorTimer = 0.0f;
        SetBlockHighlight(mBlock, false);
        mBlockLimbs.clear();
        mBlock = grown;
        RepinBlocks();
        int count = mSpine->mCount;
        SetSoundSymbol(0xb07c3bbf, 0x1e8bda2a, "creature_spine");
        RecordEvent4(0xb07c3bbf, 0xfdedb725, (float)count * g_soundScale, 0);
        mFrameDelay = mUnk8c;
        mChangedObject = true;
      }
    } else if (dist < 0.0f) {
      if (mSpine->mCount > 2) {
        if (HighlightDeleteBlockers(mBlock)) {
          cSPEditorBlock* next = GetNextVertebra();
          mSpine->RemoveVertebra(mBlock);
          mBlock = next;
          if (!RepinBlocks())
            RepinSimple();
          int count = mSpine->mCount;
          SetSoundSymbol(0xb07c3bbf, 0x1e8bda2a, "creature_spine");
          RecordEvent4(0xb07c3bbf, 0xfdedb725, (float)count * g_soundScale, 0);
          mFrameDelay = mUnk8c;
          mChangedObject = true;
        } else if (mColorTimer == 0.0f) {
          mColorTimer = 1.0f;
          KillSeti(0xc355901a);
        }
      }
    }
  }
  if (mChangedObject) {
    bool symmetry = mBlock->mEditorModel->IsUsingSymmetry();
    mBlock->mEditorModel->SetUsingSymmetry(false);
    int count = mLimbs.size();
    for (int i = 0; i < count; i++) {
      mLimbs[i]->Refresh(true);
      mLimbs[i]->FixAllJoints();
    }
    mBlock->mEditorModel->SetUsingSymmetry(symmetry);
  }
}

}  // namespace SP

namespace eastl {

// @ 0x005b8070
rbtree_iterator BlockLimbMap::DoInsertValueImpl(rbtree_node_base* pNodeParent, const BlockLimbPair& value, bool bForceToLeft) {
  int side;
  if (bForceToLeft || (pNodeParent == &mAnchor) || (value.first < ((rbtree_node*)pNodeParent)->mValue.first))
    side = 0;
  else
    side = 1;
  rbtree_node* const pNodeNew = DoCreateNode(value);
  RBTreeInsert(pNodeNew, pNodeParent, &mAnchor, side);
  mnSize++;
  return rbtree_iterator(pNodeNew);
}

// @ 0x005b8250
void BlockLimbMap::DoNukeSubtree(rbtree_node* pNode) {
  while (pNode) {
    DoNukeSubtree((rbtree_node*)pNode->mpNodeRight);
    rbtree_node* const pNodeLeft = (rbtree_node*)pNode->mpNodeLeft;
    pNode->mValue.~BlockLimbPair();
    EASTL_allocator_deallocate(pNode);
    pNode = pNodeLeft;
  }
}

// @ 0x005b88d0
EA::AutoRefCount<SP::cSPEditorSkinPart>* BlockLimbMap::FindOrCreate(SP::cSPEditorBlock* const& key) {
  rbtree_node_base* pNode = mAnchor.mpNodeParent;
  rbtree_node_base* pLower = &mAnchor;
  if (pNode) {
    do {
      if (((rbtree_node*)pNode)->mValue.first >= key) {
        pLower = pNode;
        pNode = pNode->mpNodeLeft;
      } else {
        pNode = pNode->mpNodeRight;
      }
    } while (pNode);
  }
  if (pLower != &mAnchor && !(key < ((rbtree_node*)pLower)->mValue.first))
    return &((rbtree_node*)pLower)->mValue.second;
  // defaultValue-construct the pair in place: retail only zeroes the dword (`movl $0x0,0x20(%esp)`)
  // and needs no unwinding, while assigning a fresh AutoRefCount temporary leaves a release
  // call (and an SEH frame) behind.
  BlockLimbPair kv = { key };
  // The third argument is never read by 0x5b8340 (it computes the insertion side itself); it is
  // only pushed because the template signature carries it.
  rbtree_iterator it = DoInsertValueWithHint(pLower, kv, false);
  return &it.mpNode->mValue.second;
}

}  // namespace eastl
