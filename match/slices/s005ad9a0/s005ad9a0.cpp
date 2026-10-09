// SP::cSPEditorManipulationInterpenetration (ctor, DoOnMouseDown) and
// SP::cSPEditorManipulationLimb (Spore creature editor limb dragging).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
// Retail layouts differ from the 2008 dev PDB (sp_vector_allocator is 8 bytes, Limb has extra
// symmetric limb structures and joint vectors); offsets below are taken from the retail code.
#include <math.h>
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void operator delete(void* p);  // EASTL_allocator_deallocate
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* memmove(void* dst, const void* src, unsigned int n);  // 0x011e0744 (static)

#define PV(n) virtual void pv##n();

namespace rw { namespace math { namespace fpu {
template <typename T, int N>
class Vector3Template {
 public:
  T x, y, z;
  Vector3Template() {}
  Vector3Template(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
template <typename T, int N>
inline Vector3Template<T, N> operator+(const Vector3Template<T, N>& a, const Vector3Template<T, N>& b) {
  return Vector3Template<T, N>(a.x + b.x, a.y + b.y, a.z + b.z);
}
template <typename T, int N>
inline Vector3Template<T, N> operator-(const Vector3Template<T, N>& a, const Vector3Template<T, N>& b) {
  return Vector3Template<T, N>(a.x - b.x, a.y - b.y, a.z - b.z);
}
template <typename T, int N>
inline Vector3Template<T, N> operator-(const Vector3Template<T, N>& a) {
  return Vector3Template<T, N>(-a.x, -a.y, -a.z);
}
template <typename T, int N>
inline Vector3Template<T, N> operator*(const Vector3Template<T, N>& a, T s) {
  return Vector3Template<T, N>(a.x * s, a.y * s, a.z * s);
}
template <typename T, int N>
inline T Dot(const Vector3Template<T, N>& a, const Vector3Template<T, N>& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
}}}  // namespace rw::math::fpu

struct cSPVector3 : public rw::math::fpu::Vector3Template<float, 0> {
  typedef rw::math::fpu::Vector3Template<float, 0> base;
  cSPVector3() {}
  cSPVector3(float ax, float ay, float az) : base(ax, ay, az) {}
  cSPVector3(const base& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3& operator=(const base& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

extern cSPVector3 kSPEditorUpAxis;  // 0x015e9308

struct cSPBoundingBox { cSPVector3 mMin, mMax; };

// eastl::bitset<54>
struct eastl_bitset54 {
  uint32_t mWord[2];
  bool test(unsigned int i) const { return ((mWord[i >> 5] >> (i & 31)) & 1) != 0; }
};

namespace eastl {
struct sp_vector_allocator {
  uint32_t mData[2];
  void deallocate(void* p, uint32_t) {
    if (((int*)p)[-1])
      EASTL_allocator_deallocate(p);
  }
};

// eastl::vector<T, sp_vector_allocator>
template <typename T>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator mAllocator;
  sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector() {
    if (mpBegin)
      mAllocator.deallocate(mpBegin, (uint32_t)(mpCapacity - mpBegin));
  }
  T* begin() { return mpBegin; }
  T* end() { return mpEnd; }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  sp_vector& operator=(const sp_vector& x);  // 0x0050d4e0 (float)
  T* erase(T* first, T* last);               // out of line for non-trivial T
  void clear() { erase(mpBegin, mpEnd); }
};

// vector of plain pointers: erase is inlined (memmove)
template <typename T>
class sp_ptr_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator mAllocator;
  sp_ptr_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_ptr_vector() {
    if (mpBegin)
      mAllocator.deallocate(mpBegin, (uint32_t)(mpCapacity - mpBegin));
  }
  T* erase(T* first, T* last) {
    memmove(first, last, (unsigned int)((char*)mpEnd - (char*)last));
    mpEnd -= (last - first);
    return first;
  }
  void clear() { erase(mpBegin, mpEnd); }
  int size() const { return (int)(mpEnd - mpBegin); }
  unsigned int usize() const { return (unsigned int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
};

template <typename InputIterator, typename T>
inline InputIterator find(InputIterator first, InputIterator last, const T& value) {
  while ((first != last) && !(*first == value))
    ++first;
  return first;
}
}  // namespace eastl

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
template <typename T>
inline bool operator==(const AutoRefCount<T>& a, const AutoRefCount<T>& b) { return a.mpObject == b.mpObject; }

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
};
}
}  // namespace EA

namespace SP {

class cViewer {
 public:
  bool GetWorldRayFromScreenCoords(float x, float y, cSPVector3& origin, cSPVector3& direction);
  void GetCameraLocationInfo(cSPVector3& position, cSPVector3& direction, int a, int b);
};

class cSPApp {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual cViewer* GetViewer();
};
cSPApp* App();

// intrusive refcount at +4 (vtable) / +8 (count) inside cSPEditorModel
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

class cSPEditorModelBase { public: PV(0) };
class cSPEditorModel : public cSPEditorModelBase, public RefCountedBase {
 public:
  void GetBoundingBox(cSPBoundingBox& box, bool includeHidden);  // FUN_004ad550
  float GetHeight();                                             // FUN_004adb40
  bool IsUsingSymmetry();                                        // FUN_004adc40
};

class cSPEditorBlockPart {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
  virtual void SetState(int a, int b);  // +0x30
};

class cSPEditorBlock {
 public:
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  char pad04[0x28 - 4];
  cSPEditorModel* mEditorModel;   // +0x28
  char pad2c[0x48 - 0x2c];
  cSPVector3 mPosition;           // +0x48
  char pad54[0x33c - 0x54];
  void* mpParent;                 // +0x33c (guessed: current pin parent)
  char pad340[0x3e0 - 0x340];
  cSPEditorBlock* mSymmetricBlock;  // +0x3e0
  char pad3e4[0x3ec - 0x3e4];
  cSPEditorBlockPart* mpPart;     // +0x3ec
  char pad3f0[0xdc8 - 0x3f0];
  eastl_bitset54 mFlags;          // +0xdc8
  void SetFlag(int flag, bool value);  // FUN_00435a10
  void OnManipulationEnd();            // FUN_0044ede0
  bool IsPinned();                     // FUN_00435c80
  void SetPartActive(cSPEditorBlockPart* part, bool b);  // FUN_0043cfc0
};

class cSPEditorLimbJoint {
 public:
  cSPEditorBlock* mJointBlock;                        // +0x0
  cSPEditorLimbJoint* mUpperJoint;                    // +0x4
  eastl::sp_ptr_vector<cSPEditorLimbJoint*> mLowerJoints;  // +0x8
  cSPVector3 mTargetPosition;                         // +0x1c
  void RemoveLowerJoint(cSPEditorLimbJoint* joint);   // FUN_00487140
  void CopyFrom(cSPEditorLimbJoint* joint);           // FUN_00487290
};

typedef eastl::sp_vector<EA::AutoRefCount<cSPEditorBlock> > BlockRefVector;

class cSPEditorLimbStructure {
 public:
  ~cSPEditorLimbStructure();                                     // FUN_00488900
  void Clear();                                                  // FUN_00488980
  void Rebuild();                                                // FUN_0048a4c0
  void Finalize();                                               // FUN_00488a50
  cSPEditorBlock* GetRootBlock();                                // FUN_007f99a0
  BlockRefVector* GetBlocks();                                   // FUN_00402ab0
  cSPEditorBlock* GetEndBlock();                                 // FUN_0048c700
  void GetJoints(eastl::sp_ptr_vector<cSPEditorLimbJoint*>& joints);  // FUN_0048b1e0
  cSPEditorLimbJoint* GetJoint(cSPEditorBlock* block);           // FUN_0048b2c0
  float GetMinHeight();                                          // FUN_0048bca0
  void Attach(cSPEditorBlock* block);                            // FUN_0048a560
};

class cSPEditorSkinManager;

class cSPEditorAnimatedEventInfo {
 public:
  cSPEditorAnimatedEventInfo();
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  void MessagePost(uint32_t id, cSPEditorBlock* block, cSPEditorModel* model, int a, int b, float c, int d, int e, float f);
  char pad[0x30 - 4];
};

class cISPEditorBadnessCalculator {
 public:
  virtual void AddRef();
  virtual void Release();
};

namespace EditorUtils {
void SetSymmetricBlocksUIState(cSPEditorBlock* block, int a, int b);
void DeleteInvalidBlocks(cSPEditorBlock* block, BlockRefVector* blocks);
}

void GetPile(cSPEditorBlock* block, BlockRefVector& pile, bool b);    // FUN_0048c790
void SetPileState(cSPEditorBlock* block, BlockRefVector* pile);       // FUN_004961d0
void SetPileStateSymmetric(cSPEditorBlock* block, BlockRefVector* pile);  // FUN_004a8860
void UpdateSkin(cSPEditorModel* model, cSPEditorSkinManager* skin);   // FUN_004a6ca0
void RefreshBlock(cSPEditorBlock* block);                             // FUN_0049cfd0
void ClearHighlights(eastl::sp_ptr_vector<cSPEditorLimbJoint*>* joints);  // FUN_0049cb90
cSPVector3 MirrorPosition(const cSPVector3& v);                       // FUN_004a8f40

class cSPEditorManipulationObject : public EA::COM::IUnknown32 {
 public:
  cSPEditorManipulationObject();  // FUN_005b0f80
  virtual ~cSPEditorManipulationObject() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};

EA::AutoRefCount<cSPEditorBlock>* remove_copy(EA::AutoRefCount<cSPEditorBlock>* first, EA::AutoRefCount<cSPEditorBlock>* last,
                                              EA::AutoRefCount<cSPEditorBlock>* result,
                                              const EA::AutoRefCount<cSPEditorBlock>& value);  // FUN_005aa740

inline EA::AutoRefCount<cSPEditorBlock>* remove(EA::AutoRefCount<cSPEditorBlock>* first, EA::AutoRefCount<cSPEditorBlock>* last,
                                               const EA::AutoRefCount<cSPEditorBlock>& value) {
  first = eastl::find(first, last, value);
  if (first != last) {
    EA::AutoRefCount<cSPEditorBlock>* i(first);
    return remove_copy(++i, last, first, value);
  }
  return first;
}

class cSPEditorManipulationInterpenetration : public cSPEditorManipulationObject, public EA::RefCountVTemplate<int> {
 public:
  EA::AutoRefCount<cSPEditorBlock> mBlock;  // +0x1c
  cSPEditorBlock* mOriginalParent;          // +0x20
  BlockRefVector mPileList;                 // +0x24
  cSPVector3 mMouseOffset;                  // +0x38
  bool mZAxisOnly;                          // +0x44

  cSPEditorManipulationInterpenetration();
  virtual int AddRef();
  virtual int Release();
  bool DoOnMouseDown(int button, float x, float y, int modifiers);
};

// @ 0x005AD9A0
cSPEditorManipulationInterpenetration::cSPEditorManipulationInterpenetration()
    : mOriginalParent(0), mMouseOffset(0.0f, 0.0f, 0.0f) {
  mChangedObject = false;
}

// @ 0x005ADA50
bool cSPEditorManipulationInterpenetration::DoOnMouseDown(int button, float x, float y, int modifiers) {
  mPileList.clear();
  GetPile(mBlock, mPileList, false);
  mPileList.erase(remove(mPileList.begin(), mPileList.end(), mBlock), mPileList.end());
  SetPileState(mBlock, &mPileList);
  return false;
}

struct cSPEditortLimbTry {
  cSPVector3 mLoc;                          // +0x0
  float mBadness;                           // +0xc
  eastl::sp_vector<float> mDebugVals;       // +0x10
  cSPEditortLimbTry& operator=(const cSPEditortLimbTry& x);
};

// @ 0x005AE840
cSPEditortLimbTry& cSPEditortLimbTry::operator=(const cSPEditortLimbTry& x) {
  mLoc = x.mLoc;
  mBadness = x.mBadness;
  mDebugVals = x.mDebugVals;
  return *this;
}

typedef eastl::sp_ptr_vector<cSPEditorLimbJoint*> JointVector;

class cSPEditorManipulationLimb : public cSPEditorManipulationObject, public EA::RefCountVTemplate<int> {
 public:
  cSPEditorSkinManager* mSkin;                       // +0x1c
  cSPEditorLimbStructure* mLimbStructure;            // +0x20
  cSPEditorLimbStructure* mSymmetricLimbStructure;   // +0x24 (retail only)
  cSPEditorLimbStructure* mMirrorLimbStructure;      // +0x28 (retail only)
  JointVector mManipulatingJoints;                   // +0x2c
  JointVector mSymmetricJoints;                      // +0x40
  JointVector mJoints54;                             // +0x54
  JointVector mHighlightJoints;                      // +0x68
  JointVector mSymmetricHighlightJoints;             // +0x7c
  JointVector mAllJoints;                            // +0x90
  JointVector mAllSymmetricJoints;                   // +0xa4
  cSPEditorBlock* mBlock;                            // +0xb8
  cSPEditorBlock* mOriginalParent;                   // +0xbc
  float mX;                                          // +0xc0
  float mY;                                          // +0xc4
  float mOldX;                                       // +0xc8
  float mOldY;                                       // +0xcc
  unsigned int mModifiers;                           // +0xd0
  cSPVector3 mMouseOffset;                           // +0xd4
  cSPVector3 mOriginalMouseOffset;                   // +0xe0
  cSPVector3 mOriginalBlockPosition;                 // +0xec
  int mManipType;                                    // +0xf8
  int mOriginalManipType;                            // +0xfc
  bool mIsOutsideBounds;                             // +0x100
  bool mIsStacking;                                  // +0x101
  EA::AutoRefCount<cISPEditorBadnessCalculator> mBadnessCalculator;  // +0x104
  cSPVector3 mMissPlanePosition;                     // +0x108
  cSPVector3 mMissPlaneNormal;                       // +0x114
  cSPVector3 mLimbMissPlanePosition;                 // +0x120
  cSPVector3 mLimbMissPlaneNormal;                   // +0x12c
  int mBestIndex;                                    // +0x138
  cSPEditortLimbTry mBestTry;                        // +0x13c
  cSPEditortLimbTry mWorstTry;                       // +0x160
  cSPEditortLimbTry mTries[400];                     // +0x184

  cSPEditorManipulationLimb();
  ~cSPEditorManipulationLimb();
  virtual int AddRef();
  virtual int Release();
  bool OnMouseUp(int button, float x, float y, int modifiers);
  bool DoOnMouseDown(int button, float x, float y, int modifiers);
  bool DoOnMouseMove(float x, float y, int modifiers);
  void Shutdown();
  void ClearSymmetricHighlights();
  float GetMaxLimbPlacementHeight();
  void UpdateSymmetricJointPositions();
  void CopyJointsToSymmetricLimbs();
  void RecalculateLimbMissPlane();
  void RefreshJointLists();
};

// @ 0x005ADB00
void cSPEditorManipulationLimb::ClearSymmetricHighlights() {
  if (mSymmetricLimbStructure) {
    ClearHighlights(&mHighlightJoints);
    ClearHighlights(&mSymmetricHighlightJoints);
  }
}

// @ 0x005ADB20
bool cSPEditorManipulationLimb::OnMouseUp(int button, float x, float y, int modifiers) {
  EA::AutoRefCount<cSPEditorBlock> block(mBlock);
  cSPVector3 origin, direction;
  App()->GetViewer()->GetWorldRayFromScreenCoords(mX, mY, origin, direction);
  cSPEditorBlock* rootBlock = mLimbStructure->GetRootBlock();
  cSPEditorBlock* eventBlock = mLimbStructure->GetEndBlock();
  if (!eventBlock)
    eventBlock = mBlock;
  if (mChangedObject) {
    if (mOriginalParent) {
      if (mBlock->mpParent) {
        EA::AutoRefCount<cSPEditorAnimatedEventInfo> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo());
        info->MessagePost(0xda95baa5, eventBlock, eventBlock == 0 ? 0 : eventBlock->mEditorModel, 0, 0, 0.0f, 0, -1, 1.0f);
      } else {
        EA::AutoRefCount<cSPEditorAnimatedEventInfo> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo());
        info->MessagePost(0x0428e920, eventBlock, eventBlock == 0 ? 0 : eventBlock->mEditorModel, 0, 0, 0.0f, 0, -1, 1.0f);
      }
    } else if (mBlock->mpParent) {
      EA::AutoRefCount<cSPEditorAnimatedEventInfo> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo());
      info->MessagePost(0x8e04ce1a, eventBlock, eventBlock == 0 ? 0 : eventBlock->mEditorModel, 0, 0, 0.0f, 0, -1, 1.0f);
    }
  }
  mLimbStructure->Rebuild();
  mLimbStructure->Finalize();
  if (mSymmetricLimbStructure) {
    mSymmetricLimbStructure->Rebuild();
    mSymmetricLimbStructure->Finalize();
  }
  if (mMirrorLimbStructure) {
    mMirrorLimbStructure->Rebuild();
    mMirrorLimbStructure->Finalize();
  }
  mBlock->OnManipulationEnd();
  EditorUtils::SetSymmetricBlocksUIState(rootBlock, 0, 0);
  UpdateSkin(mBlock->mEditorModel, mSkin);
  EditorUtils::DeleteInvalidBlocks(block, mLimbStructure->GetBlocks());
  cSPEditorBlockPart* part = mBlock->mpPart;
  if (part)
    part->SetState(3, 1);
  if (mBlock->IsPinned())
    RefreshBlock(mBlock);
  return true;
}

// @ 0x005ADDB0
float cSPEditorManipulationLimb::GetMaxLimbPlacementHeight() {
  cSPBoundingBox box;
  mBlock->mEditorModel->GetBoundingBox(box, true);
  return mBlock->mEditorModel->GetHeight() * 0.95f;
}

// @ 0x005ADDF0
void cSPEditorManipulationLimb::UpdateSymmetricJointPositions() {
  int i = 0;
  int count = mManipulatingJoints.size();
  for (; i < count; i++) {
    cSPEditorLimbJoint* joint = mManipulatingJoints[i];
    cSPEditorBlock* symmetricBlock = joint->mJointBlock->mSymmetricBlock;
    int symCount = mSymmetricJoints.size();
    for (int j = 0; j < symCount; j++) {
      cSPEditorLimbJoint* symJoint = mSymmetricJoints[j];
      if (symmetricBlock == symJoint->mJointBlock)
        symJoint->mTargetPosition = MirrorPosition(joint->mTargetPosition);
    }
    if (joint->mUpperJoint && joint->mUpperJoint->mJointBlock && joint->mUpperJoint->mJointBlock->mSymmetricBlock) {
      cSPEditorLimbStructure* other = mMirrorLimbStructure ? mMirrorLimbStructure : mSymmetricLimbStructure;
      if (other) {
        cSPEditorLimbJoint* symUpper = other->GetJoint(joint->mUpperJoint->mJointBlock->mSymmetricBlock);
        if (symUpper) {
          cSPVector3 pos = MirrorPosition(joint->mTargetPosition);
          unsigned int n = symUpper->mLowerJoints.usize();
          for (unsigned int k = 0; k < n; k++)
            symUpper->mLowerJoints[k]->mTargetPosition = pos;
        }
      }
    }
  }
}

// @ 0x005ADF10
void cSPEditorManipulationLimb::CopyJointsToSymmetricLimbs() {
  if (mSymmetricLimbStructure) {
    int count = mAllJoints.size();
    for (int i = 0; i < count; i++) {
      cSPEditorLimbJoint* joint = mAllJoints[i];
      if (joint->mUpperJoint) {
        cSPEditorBlock* symmetricBlock = joint->mUpperJoint->mJointBlock->mSymmetricBlock;
        cSPEditorLimbJoint* sym = mSymmetricLimbStructure->GetJoint(symmetricBlock);
        if (sym)
          sym->CopyFrom(joint);
      }
    }
    count = mAllSymmetricJoints.size();
    for (int i = 0; i < count; i++) {
      cSPEditorLimbJoint* joint = mAllSymmetricJoints[i];
      if (joint->mUpperJoint) {
        cSPEditorBlock* symmetricBlock = joint->mUpperJoint->mJointBlock->mSymmetricBlock;
        cSPEditorLimbJoint* sym = mLimbStructure->GetJoint(symmetricBlock);
        if (sym)
          sym->CopyFrom(joint);
      }
    }
  }
}

// Recursive helper that mirrors a joint tree onto a symmetric limb structure.
struct cSPEditorJointMirror {
  cSPEditorLimbStructure* mpTarget;
  void Mirror(cSPEditorLimbJoint* joint);
};

// @ 0x005ADFD0
void cSPEditorJointMirror::Mirror(cSPEditorLimbJoint* joint) {
  if (joint->mJointBlock->mSymmetricBlock) {
    cSPEditorLimbJoint* sym = mpTarget->GetJoint(joint->mJointBlock->mSymmetricBlock);
    sym->mTargetPosition = MirrorPosition(joint->mTargetPosition);
  } else if (joint->mUpperJoint && joint->mUpperJoint->mJointBlock && joint->mUpperJoint->mJointBlock->mSymmetricBlock) {
    cSPEditorLimbJoint* symUpper = mpTarget->GetJoint(joint->mUpperJoint->mJointBlock->mSymmetricBlock);
    if (symUpper) {
      cSPVector3 pos = MirrorPosition(joint->mTargetPosition);
      unsigned int n = symUpper->mLowerJoints.usize();
      for (unsigned int k = 0; k < n; k++)
        symUpper->mLowerJoints[k]->mTargetPosition = pos;
    }
  }
  unsigned int count = joint->mLowerJoints.usize();
  for (unsigned int i = 0; i < count; i++)
    Mirror(joint->mLowerJoints[i]);
}

// @ 0x005AE0B0
bool cSPEditorManipulationLimb::DoOnMouseMove(float x, float y, int modifiers) {
  mX = x;
  mModifiers = modifiers;
  mY = y;
  if (mBlock->mFlags.test(35) && !mBlock->mFlags.test(51)) {
    mBlock->SetFlag(0x23, false);
    mBlock->SetFlag(0x33, true);
  }
  return true;
}

// @ 0x005AE120
void cSPEditorManipulationLimb::Shutdown() {
  if (mLimbStructure) {
    mLimbStructure->Clear();
    delete mLimbStructure;
    mLimbStructure = 0;
  }
  if (mSymmetricLimbStructure) {
    mSymmetricLimbStructure->Clear();
    delete mSymmetricLimbStructure;
    mSymmetricLimbStructure = 0;
  }
  if (mMirrorLimbStructure) {
    mMirrorLimbStructure->Clear();
    delete mMirrorLimbStructure;
    mMirrorLimbStructure = 0;
  }
}

// @ 0x005AE1B0
cSPEditorManipulationLimb::~cSPEditorManipulationLimb() {}

// @ 0x005AE300
void cSPEditorManipulationLimb::RecalculateLimbMissPlane() {
  mLimbMissPlanePosition = mLimbStructure->GetRootBlock()->mPosition;
  float minHeight = mLimbStructure->GetMinHeight();
  cSPBoundingBox box;
  mBlock->mEditorModel->GetBoundingBox(box, true);
  float maxHeight = GetMaxLimbPlacementHeight();
  if (mLimbMissPlanePosition.z < minHeight)
    mLimbMissPlanePosition.z = minHeight;
  if (mLimbMissPlanePosition.z > maxHeight)
    mLimbMissPlanePosition.z = maxHeight;
  cSPVector3 cameraPosition, cameraDirection;
  App()->GetViewer()->GetCameraLocationInfo(cameraPosition, cameraDirection, 0, 0);
  cSPVector3 toCamera = -cameraDirection;
  float t = fabsf(Dot(kSPEditorUpAxis, cameraDirection));
  mLimbMissPlaneNormal = toCamera + (kSPEditorUpAxis - toCamera) * t;
}

// @ 0x005AE480
bool cSPEditorManipulationLimb::DoOnMouseDown(int button, float x, float y, int modifiers) {
  EA::AutoRefCount<cSPEditorModel> model(mBlock->mEditorModel);
  mModifiers = modifiers;
  mX = x;
  mY = y;
  mOldX = x;
  mOldY = y;
  SetPileState(mLimbStructure->GetRootBlock(), mLimbStructure->GetBlocks());
  if (mSymmetricLimbStructure)
    SetPileState(mSymmetricLimbStructure->GetRootBlock(), mSymmetricLimbStructure->GetBlocks());
  if (mMirrorLimbStructure)
    SetPileState(mMirrorLimbStructure->GetRootBlock(), mMirrorLimbStructure->GetBlocks());
  if (!model->IsUsingSymmetry())
    SetPileStateSymmetric(mLimbStructure->GetRootBlock(), mLimbStructure->GetBlocks());
  mLimbStructure->Attach(mBlock);
  mBlock->SetPartActive(mBlock->mpPart, true);
  mBlock->mpPart->SetState(2, 1);
  RecalculateLimbMissPlane();
  return true;
}

// @ 0x005AE610
cSPEditorManipulationLimb::cSPEditorManipulationLimb()
    : mSkin(0),
      mLimbStructure(0),
      mBlock(0),
      mOriginalParent(0),
      mX(0.0f),
      mY(0.0f),
      mOldX(0.0f),
      mOldY(0.0f),
      mModifiers(0),
      mMouseOffset(0.0f, 0.0f, 0.0f),
      mOriginalMouseOffset(0.0f, 0.0f, 0.0f),
      mIsOutsideBounds(false) {
  mChangedObject = false;
}

// @ 0x005AE750
void cSPEditorManipulationLimb::RefreshJointLists() {
  mAllJoints.clear();
  mLimbStructure->GetJoints(mAllJoints);
  if (mSymmetricLimbStructure) {
    mAllSymmetricJoints.clear();
    mSymmetricLimbStructure->GetJoints(mAllSymmetricJoints);
  }
  int count = mAllJoints.size();
  for (int i = 0; i < count; i++) {
    cSPEditorLimbJoint* joint = mAllJoints[i];
    if (joint->mUpperJoint)
      joint->mUpperJoint->RemoveLowerJoint(joint);
  }
  count = mAllSymmetricJoints.size();
  for (int i = 0; i < count; i++) {
    cSPEditorLimbJoint* joint = mAllSymmetricJoints[i];
    if (joint->mUpperJoint)
      joint->mUpperJoint->RemoveLowerJoint(joint);
  }
}

}  // namespace SP
