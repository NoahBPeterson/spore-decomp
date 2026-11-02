// src/game/SPCreatureAnim/gait_dynamics.cpp -- migrated from slice(s) s009da640, s009d75b0, s009d5600, s009d46d0, s009d3950, s009d29b0, s009d1b40, s009cfd40, s009cede0, s009cddf0, s009ccfe0, s005b0f80, s005ae870, s005af200, s005ad9a0 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/gait_dynamics.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* memmove(void* dst, const void* src, unsigned int n);  // 0x011e0744 (static)
#include <math.h>
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorLimbJoint.h"
#include "SP/cSPEditorLimbStructure.h"
#include "SP/cSPEditorManipulationObject.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorSkinManager.h"
#include "SP/cViewer.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cIParser.h"
#include <xmmintrin.h>
#include <intrin.h>

// ---- items of slice s005ad9a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void operator delete(void* p);  // EASTL_allocator_deallocate
#define PV(n) virtual void pv##n();
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
class Vector3Template_s005a_d9a0 {
 public:
  T x, y, z;
  Vector3Template_s005a_d9a0() {}
  Vector3Template_s005a_d9a0(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005a_d9a0<T, N> operator+(const Vector3Template_s005a_d9a0<T, N>& a, const Vector3Template_s005a_d9a0<T, N>& b) {
  return Vector3Template_s005a_d9a0<T, N>(a.x + b.x, a.y + b.y, a.z + b.z);
}
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005a_d9a0<T, N> operator-(const Vector3Template_s005a_d9a0<T, N>& a, const Vector3Template_s005a_d9a0<T, N>& b) {
  return Vector3Template_s005a_d9a0<T, N>(a.x - b.x, a.y - b.y, a.z - b.z);
}
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005a_d9a0<T, N> operator-(const Vector3Template_s005a_d9a0<T, N>& a) {
  return Vector3Template_s005a_d9a0<T, N>(-a.x, -a.y, -a.z);
}
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005a_d9a0<T, N> operator*(const Vector3Template_s005a_d9a0<T, N>& a, T s) {
  return Vector3Template_s005a_d9a0<T, N>(a.x * s, a.y * s, a.z * s);
}
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline T Dot_s005a_d9a0(const Vector3Template_s005a_d9a0<T, N>& a, const Vector3Template_s005a_d9a0<T, N>& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
}
}
}
struct cSPVector3_s005a_d9a0 : public rw::math::fpu::Vector3Template_s005a_d9a0<float, 0> {
  typedef rw::math::fpu::Vector3Template_s005a_d9a0<float, 0> base;
  cSPVector3_s005a_d9a0() {}
  cSPVector3_s005a_d9a0(float ax, float ay, float az) : base(ax, ay, az) {}
  cSPVector3_s005a_d9a0(const base& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3_s005a_d9a0& operator=(const base& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
extern cSPVector3_s005a_d9a0 kSPEditorUpAxis_s005a_d9a0;  // 0x015e9308
struct cSPBoundingBox_s005a_d9a0 { cSPVector3_s005a_d9a0 mMin, mMax; };
struct eastl_bitset54 {
  uint32_t mWord[2];
  bool test(unsigned int i) const { return ((mWord[i >> 5] >> (i & 31)) & 1) != 0; }
};
namespace eastl {
struct sp_vector_allocator_s005a_d9a0 {
  uint32_t mData[2];
  void deallocate(void* p, uint32_t) {
    if (((int*)p)[-1])
      EASTL_allocator_deallocate(p);
  }
};
}
namespace eastl {
template <typename T>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator_s005a_d9a0 mAllocator;
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
}
namespace eastl {
template <typename T>
class sp_ptr_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator_s005a_d9a0 mAllocator;
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
}
namespace EA {
template <typename T>
class AutoRefCount_s005a_d9a0 {
 public:
  T* mpObject;
  AutoRefCount_s005a_d9a0() : mpObject(0) {}
  AutoRefCount_s005a_d9a0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005a_d9a0() { if (mpObject) mpObject->Release(); }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
inline bool operator==(const AutoRefCount_s005a_d9a0<T>& a, const AutoRefCount_s005a_d9a0<T>& b) { return a.mpObject == b.mpObject; }
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005a_d9a0 {
 public:
  RefCountVTemplate_s005a_d9a0() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005a_d9a0() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005a_d9a0 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
};
}
}
namespace SP {
class cViewer_s005a_d9a0 {
 public:
  bool GetWorldRayFromScreenCoords(float x, float y, cSPVector3_s005a_d9a0& origin, cSPVector3_s005a_d9a0& direction);  // 0x007c4730 (SP::cViewer::GetWorldRayFromScreenCoords)
  void GetCameraLocationInfo(cSPVector3_s005a_d9a0& position, cSPVector3_s005a_d9a0& direction, int a, int b);  // 0x007c3d30 (SP::cViewer::GetCameraLocationInfo)
};
}
namespace SP {
class cSPApp {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual cViewer_s005a_d9a0* GetViewer();
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
class cSPEditorModelBase { public: PV(0) };
}
namespace SP {
class cSPEditorModel_s005a_d9a0 : public cSPEditorModelBase, public RefCountedBase {
 public:
  void GetBoundingBox(cSPBoundingBox_s005a_d9a0& box, bool includeHidden);  // FUN_004ad550
  float GetHeight();                                             // FUN_004adb40
  bool IsUsingSymmetry();                                        // FUN_004adc40
};
}
namespace SP {
class cSPEditorBlockPart {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
  virtual void SetState(int a, int b);  // +0x30
};
}
namespace SP {
class cSPEditorBlock_s005a_d9a0 {
 public:
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  char pad04[0x28 - 4];
  cSPEditorModel_s005a_d9a0* mEditorModel;   // +0x28
  char pad2c[0x48 - 0x2c];
  cSPVector3_s005a_d9a0 mPosition;           // +0x48
  char pad54[0x33c - 0x54];
  void* mpParent;                 // +0x33c (guessed: current pin parent)
  char pad340[0x3e0 - 0x340];
  cSPEditorBlock_s005a_d9a0* mSymmetricBlock;  // +0x3e0
  char pad3e4[0x3ec - 0x3e4];
  cSPEditorBlockPart* mpPart;     // +0x3ec
  char pad3f0[0xdc8 - 0x3f0];
  eastl_bitset54 mFlags;          // +0xdc8
  void SetFlag(int flag, bool value);  // FUN_00435a10
  void OnManipulationEnd();            // FUN_0044ede0
  bool IsPinned();                     // FUN_00435c80
  void SetPartActive(cSPEditorBlockPart* part, bool b);  // FUN_0043cfc0
};
}
namespace SP {
class cSPEditorLimbJoint_s005a_d9a0 {
 public:
  cSPEditorBlock_s005a_d9a0* mJointBlock;                        // +0x0
  cSPEditorLimbJoint_s005a_d9a0* mUpperJoint;                    // +0x4
  eastl::sp_ptr_vector<cSPEditorLimbJoint_s005a_d9a0*> mLowerJoints;  // +0x8
  cSPVector3_s005a_d9a0 mTargetPosition;                         // +0x1c
  void RemoveLowerJoint(cSPEditorLimbJoint_s005a_d9a0* joint);   // FUN_00487140
  void CopyFrom(cSPEditorLimbJoint_s005a_d9a0* joint);           // FUN_00487290
};
}
namespace SP {
typedef eastl::sp_vector<EA::AutoRefCount_s005a_d9a0<cSPEditorBlock_s005a_d9a0> > BlockRefVector;
}
namespace SP {
class cSPEditorLimbStructure_s005a_d9a0 {
 public:
  ~cSPEditorLimbStructure_s005a_d9a0();                                     // FUN_00488900
  void Clear();                                                  // FUN_00488980
  void Rebuild();                                                // FUN_0048a4c0
  void Finalize();                                               // FUN_00488a50
  cSPEditorBlock_s005a_d9a0* GetRootBlock();                                // FUN_007f99a0
  BlockRefVector* GetBlocks();                                   // FUN_00402ab0
  cSPEditorBlock_s005a_d9a0* GetEndBlock();                                 // FUN_0048c700
  void GetJoints(eastl::sp_ptr_vector<cSPEditorLimbJoint_s005a_d9a0*>& joints);  // FUN_0048b1e0
  cSPEditorLimbJoint_s005a_d9a0* GetJoint(cSPEditorBlock_s005a_d9a0* block);           // FUN_0048b2c0
  float GetMinHeight();                                          // FUN_0048bca0
  void Attach(cSPEditorBlock_s005a_d9a0* block);                            // FUN_0048a560
};
}
namespace SP {
class cSPEditorSkinManager_s005a_d9a0;
}
namespace SP {
class cSPEditorAnimatedEventInfo_s005a_d9a0 {
 public:
  cSPEditorAnimatedEventInfo_s005a_d9a0();
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  void MessagePost(uint32_t id, cSPEditorBlock_s005a_d9a0* block, cSPEditorModel_s005a_d9a0* model, int a, int b, float c, int d, int e, float f);  // 0x0059d840 (SP::cSPEditorAnimatedEventInfo::MessagePost)
  char pad[0x30 - 4];
};
}
namespace SP {
class cISPEditorBadnessCalculator {
 public:
  virtual void AddRef();
  virtual void Release();
};
}
namespace SP {
namespace EditorUtils {
void SetSymmetricBlocksUIState(cSPEditorBlock_s005a_d9a0* block, int a, int b);
}
}
namespace SP {
namespace EditorUtils {
void DeleteInvalidBlocks(cSPEditorBlock_s005a_d9a0* block, BlockRefVector* blocks);
}
}
namespace SP {
void SetPileState(cSPEditorBlock_s005a_d9a0* block, BlockRefVector* pile);       // FUN_004961d0
}
namespace SP {
void SetPileStateSymmetric(cSPEditorBlock_s005a_d9a0* block, BlockRefVector* pile);  // FUN_004a8860
}
namespace SP {
void UpdateSkin(cSPEditorModel_s005a_d9a0* model, cSPEditorSkinManager_s005a_d9a0* skin);   // FUN_004a6ca0
}
namespace SP {
void RefreshBlock(cSPEditorBlock_s005a_d9a0* block);                             // FUN_0049cfd0
}
namespace SP {
void ClearHighlights(eastl::sp_ptr_vector<cSPEditorLimbJoint_s005a_d9a0*>* joints);  // FUN_0049cb90
}
namespace SP {
cSPVector3_s005a_d9a0 MirrorPosition(const cSPVector3_s005a_d9a0& v);                       // FUN_004a8f40
}
namespace SP {
class cSPEditorManipulationObject_s005a_d9a0 : public EA::COM::IUnknown32_s005a_d9a0 {
 public:
  cSPEditorManipulationObject_s005a_d9a0();  // FUN_005b0f80
  virtual ~cSPEditorManipulationObject_s005a_d9a0() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};
}
namespace SP {
struct cSPEditortLimbTry {
  cSPVector3_s005a_d9a0 mLoc;                          // +0x0
  float mBadness;                           // +0xc
  eastl::sp_vector<float> mDebugVals;       // +0x10
  cSPEditortLimbTry& operator=(const cSPEditortLimbTry& x);
};
}
namespace SP {
typedef eastl::sp_ptr_vector<cSPEditorLimbJoint_s005a_d9a0*> JointVector;
}
namespace SP {
class cSPEditorManipulationLimb : public cSPEditorManipulationObject_s005a_d9a0, public EA::RefCountVTemplate_s005a_d9a0<int> {
 public:
  cSPEditorSkinManager_s005a_d9a0* mSkin;                       // +0x1c
  cSPEditorLimbStructure_s005a_d9a0* mLimbStructure;            // +0x20
  cSPEditorLimbStructure_s005a_d9a0* mSymmetricLimbStructure;   // +0x24 (retail only)
  cSPEditorLimbStructure_s005a_d9a0* mMirrorLimbStructure;      // +0x28 (retail only)
  JointVector mManipulatingJoints;                   // +0x2c
  JointVector mSymmetricJoints;                      // +0x40
  JointVector mJoints54;                             // +0x54
  JointVector mHighlightJoints;                      // +0x68
  JointVector mSymmetricHighlightJoints;             // +0x7c
  JointVector mAllJoints;                            // +0x90
  JointVector mAllSymmetricJoints;                   // +0xa4
  cSPEditorBlock_s005a_d9a0* mBlock;                            // +0xb8
  cSPEditorBlock_s005a_d9a0* mOriginalParent;                   // +0xbc
  float mX;                                          // +0xc0
  float mY;                                          // +0xc4
  float mOldX;                                       // +0xc8
  float mOldY;                                       // +0xcc
  unsigned int mModifiers;                           // +0xd0
  cSPVector3_s005a_d9a0 mMouseOffset;                           // +0xd4
  cSPVector3_s005a_d9a0 mOriginalMouseOffset;                   // +0xe0
  cSPVector3_s005a_d9a0 mOriginalBlockPosition;                 // +0xec
  int mManipType;                                    // +0xf8
  int mOriginalManipType;                            // +0xfc
  bool mIsOutsideBounds;                             // +0x100
  bool mIsStacking;                                  // +0x101
  EA::AutoRefCount_s005a_d9a0<cISPEditorBadnessCalculator> mBadnessCalculator;  // +0x104
  cSPVector3_s005a_d9a0 mMissPlanePosition;                     // +0x108
  cSPVector3_s005a_d9a0 mMissPlaneNormal;                       // +0x114
  cSPVector3_s005a_d9a0 mLimbMissPlanePosition;                 // +0x120
  cSPVector3_s005a_d9a0 mLimbMissPlaneNormal;                   // +0x12c
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
}
namespace SP {
struct cSPEditorJointMirror_s005a_d9a0 {
  cSPEditorLimbStructure_s005a_d9a0* mpTarget;
  void Mirror(cSPEditorLimbJoint_s005a_d9a0* joint);
};
}
// ---- items of slice s005ad9a0 end

// ---- items of slice s005af200 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPVector3_s005a_f200 {
  float x, y, z;
  cSPVector3_s005a_f200() {}
  cSPVector3_s005a_f200(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};
inline cSPVector3_s005a_f200 operator+(const cSPVector3_s005a_f200& a, const cSPVector3_s005a_f200& b) { return cSPVector3_s005a_f200(a.x + b.x, a.y + b.y, a.z + b.z); }
inline cSPVector3_s005a_f200 operator-(const cSPVector3_s005a_f200& a, const cSPVector3_s005a_f200& b) { return cSPVector3_s005a_f200(a.x - b.x, a.y - b.y, a.z - b.z); }
inline cSPVector3_s005a_f200 operator-(const cSPVector3_s005a_f200& a) { return cSPVector3_s005a_f200(-a.x, -a.y, -a.z); }
inline cSPVector3_s005a_f200 operator*(const cSPVector3_s005a_f200& a, float s) { return cSPVector3_s005a_f200(a.x * s, a.y * s, a.z * s); }
inline float Dot(const cSPVector3_s005a_f200& a, const cSPVector3_s005a_f200& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline float Length(const cSPVector3_s005a_f200& a) { return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z); }
struct cSPPlane {
  cSPVector3_s005a_f200 mNormal;
  float mD;
  __forceinline cSPPlane(const cSPVector3_s005a_f200& normal, const cSPVector3_s005a_f200& point) : mNormal(normal), mD(-Dot(point, normal)) {}
};
struct Matrix3 {
  float m[9];
  Matrix3& Assign(const Matrix3& other);  // 0x0041cb40
};
extern cSPVector3_s005a_f200 kSPEditorOrigin;       // 0x015e920c (point the up/right planes pass through)
extern cSPVector3_s005a_f200 kSPEditorUpAxis;       // 0x015e9308
extern cSPVector3_s005a_f200 kSPEditorRightAxis;    // 0x015e9330 (normal of the symmetry plane)
extern cSPVector3_s005a_f200 kSPEditorForwardAxis;  // 0x015e9384
bool IntersectRayPlane(const cSPVector3_s005a_f200& origin, const cSPVector3_s005a_f200& direction, const cSPPlane& plane, float& t);  // 0x0044e640
namespace eastl {
template <typename T>
class sp_ptr_vector_s005a_f200 {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  uint32_t mAllocator[2];
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
};  // namespace eastl
}
namespace EA {
template <typename T>
class AutoRefCount_s005a_f200 {
 public:
  T* mpObject;
  AutoRefCount_s005a_f200(T* p);  // 0x00572660 (out of line for the skin manager)
  AutoRefCount_s005a_f200(const AutoRefCount_s005a_f200& x);  // user copy ctor: by-value args are built in place
  ~AutoRefCount_s005a_f200() { if (mpObject) mpObject->Release(); }
};  // namespace EA
}
namespace SP {
class cViewer_s005a_f200 {
 public:
  bool GetWorldRayFromScreenCoords(float x, float y, cSPVector3_s005a_f200& origin, cSPVector3_s005a_f200& direction);  // 0x007c4730
};
}
namespace SP {
class cSPApp_s005a_f200 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual cViewer_s005a_f200* GetViewer();  // +0x58
};
}
namespace SP {
cSPApp_s005a_f200* App_s005a_f200();  // 0x0067dd10
}
namespace SP {
class cMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMessage(uint32_t id, int a, int b);  // +0x14
};
}
namespace SP {
cMessageServer* MessageServer();  // 0x0067dcc0
}
namespace SP {
class cEditorStateObject {
 public:
  void SetBool(uint32_t id, bool value);                  // 0x0045b110
  void SetBlock(uint32_t id, class cSPEditorBlock_s005a_f200* block);  // 0x0045b080
};
}
namespace SP {
cEditorStateObject* GetEditorStateObject();  // 0x00401050
}
namespace SP {
class cSPEditorModel_s005a_f200 {
 public:
  float GetSize();          // 0x004adaa0
  bool IsUsingSymmetry();   // 0x004adc40
};
}
namespace SP {
class cSPEditorSkinManager_s005a_f200 {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
namespace SP {
typedef EA::AutoRefCount_s005a_f200<cSPEditorSkinManager_s005a_f200> SkinRef;
}
namespace SP {
class cSPEditorBlock_s005a_f200 {
 public:
  virtual void v0();
  char pad04[0x28 - 4];
  cSPEditorModel_s005a_f200* mEditorModel;      // +0x28
  char pad2c[0x48 - 0x2c];
  cSPVector3_s005a_f200 mPosition;              // +0x48
  char pad54[0xa8 - 0x54];
  Matrix3 mOrientation;              // +0xa8
  char padcc[0x33c - 0xcc];
  cSPEditorBlock_s005a_f200* mpParent;          // +0x33c
  eastl::sp_ptr_vector_s005a_f200<cSPEditorBlock_s005a_f200*> mChildren;  // +0x340
  char pad354[0x3e0 - 0x354];
  cSPEditorBlock_s005a_f200* mSymmetricBlock;   // +0x3e0
  char pad3e4[0xdc8 - 0x3e4];
  eastl_bitset54 mFlags;             // +0xdc8
  void SetBooleanAttribute(int attr, bool value);  // 0x00435a10
  bool IsPinned();                                 // 0x00435c80
  bool HasAnyBlockFlag();                          // 0x00435d40
  void RecursiveFlagA();                           // 0x0044ede0
};
}
namespace SP {
typedef void BlockList;  // eastl::vector<AutoRefCount<cSPEditorBlock>> (opaque here)
}
namespace SP {
class cSPEditorLimbJoint_s005a_f200 {
 public:
  cSPEditorBlock_s005a_f200* mJointBlock;      // +0x0
  cSPEditorLimbJoint_s005a_f200* mUpperJoint;  // +0x4
  eastl::sp_ptr_vector_s005a_f200<cSPEditorLimbJoint_s005a_f200*> mLowerJoints;  // +0x8
  cSPVector3_s005a_f200 mTargetPosition;       // +0x1c
  char pad28[0x64 - 0x28];
  int mJointType;                   // +0x64
  int GetSign(bool b);                                   // 0x004874c0 (named Sign in symbols)
  int SignFromBlock(bool b);                             // 0x004876b0
  void SetTargetPosition(cSPVector3_s005a_f200 pos);                // 0x00485930
  void Translate(cSPVector3_s005a_f200 delta);                      // 0x00485a60
  cSPVector3_s005a_f200 GetUpperDirection(int n);                   // 0x00487e90
};
}
namespace SP {
typedef eastl::sp_ptr_vector_s005a_f200<cSPEditorLimbJoint_s005a_f200*> JointVector_s005a_f200;
}
namespace SP {
class cSPEditorLimbStructure_s005a_f200 {
 public:
  char pad00[0x18];
  cSPEditorLimbJoint_s005a_f200* mBaseJoint;  // +0x18
  BlockList* GetBlocks();                                         // 0x00402ab0
  cSPEditorBlock_s005a_f200* GetRootBlock();                                 // 0x007f99a0
  cSPEditorLimbJoint_s005a_f200* GetJoint(cSPEditorBlock_s005a_f200* block);            // 0x0048b2c0
  void SetHighlighting(bool b);                                   // 0x004890e0
  bool ClampJoints(JointVector_s005a_f200* joints);                          // 0x0048ae60
  void ResolveJoints(JointVector_s005a_f200* joints);                        // 0x0048af00
  bool CheckJoints(JointVector_s005a_f200* joints);                          // 0x0048b080
  void MoveJoint(cSPEditorLimbJoint_s005a_f200* joint, cSPVector3_s005a_f200 pos);      // 0x0048a650
  void UpdatePositions();                                         // 0x0048b1c0
  bool UpdateAllLengths(bool b);                                  // 0x0048bf40
  void RefreshTargets(JointVector_s005a_f200* joints, bool symmetric);       // 0x00489710
  void RefreshBlockTargets(cSPEditorBlock_s005a_f200* block, bool symmetric);  // 0x004897b0
  void SetFeetTargets(bool b);                                    // 0x0048bae0
  void SetHandsTargets(bool b);                                   // 0x0048bbb0
  void UpdateFeetTargets();                                       // 0x0048bdd0
  void UpdateBlocks();                                            // 0x00489cd0
  void UpdateAnimation(int a, int b);                             // 0x0048ae30
  void SolveJoint(cSPEditorLimbJoint_s005a_f200* joint, cSPEditorLimbJoint_s005a_f200* end);  // 0x00488fe0
  void ResetJoints(bool b);                                       // 0x00488d00
  int GetFootCount();                                             // 0x00488a20
  void Settle(cSPEditorBlock_s005a_f200* block);                             // 0x00488e80
};
}
namespace SP {
struct cSPEditorJointMirror {
  cSPEditorLimbStructure_s005a_f200* mpTarget;
  void Mirror(cSPEditorLimbJoint_s005a_f200* joint);  // 0x005adfd0
};
}
namespace SP {
struct cSPEditorHighlight { char data[0x3c]; };
}
namespace SP {
struct HighlightVector {
  cSPEditorHighlight* mpBegin;
  cSPEditorHighlight* mpEnd;
  cSPEditorHighlight* mpCapacity;
  uint32_t mAllocator[2];
  void clear();  // 0x005af1c0
};
}
namespace SP {
class cISPEditorBadnessCalculator_s005a_f200 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
  virtual bool IsEnabled();  // +0x18
};
}
namespace SP {
struct cSPEditortLimbTry_s005a_f200 {
  cSPVector3_s005a_f200 mLoc;                          // +0x0
  float mBadness;                           // +0xc
  eastl::sp_ptr_vector_s005a_f200<float> mDebugVals;   // +0x10
  cSPEditortLimbTry_s005a_f200& operator=(const cSPEditortLimbTry_s005a_f200& x);  // 0x005ae840
  ~cSPEditortLimbTry_s005a_f200();                                      // 0x00732a10
};
}
namespace SP {
void BuildHighlights(cSPEditorBlock_s005a_f200* root, HighlightVector* out, bool b);  // 0x0049c8f0
}
namespace SP {
void RefreshHighlights(HighlightVector* v);                                // 0x0049ce40
}
namespace SP {
cSPVector3_s005a_f200 GetLimbPlanePosition(cSPEditorBlock_s005a_f200* block);                    // 0x004a06c0
}
namespace SP {
bool SignChanged(int oldSign, int newSign, bool b);                        // 0x004a7ea0
}
namespace SP {
void PlayEditorSound(uint32_t id);                                         // 0x004a88d0
}
namespace SP {
void SetPileState(cSPEditorBlock_s005a_f200* block, BlockList* blocks);               // 0x004961d0
}
namespace SP {
void UpdateSkin(cSPEditorBlock_s005a_f200* block, BlockList* blocks, bool stacking, cSPEditorSkinManager_s005a_f200* skin,
                int a, int b, int c, int d);                               // 0x004a6d20
}
namespace SP {
cSPEditorBlock_s005a_f200* PickStackTarget(cSPEditorBlock_s005a_f200* block, cSPVector3_s005a_f200 origin, cSPVector3_s005a_f200 direction, SkinRef skin,
                                cSPVector3_s005a_f200* hitPosition, cSPVector3_s005a_f200* hitNormal, BlockList* blocks);  // 0x00499410
}
namespace SP {
cSPEditorBlock_s005a_f200* PickBlock(cSPEditorBlock_s005a_f200* block, BlockList* blocks, cSPVector3_s005a_f200 origin, cSPVector3_s005a_f200 direction,
                          cSPVector3_s005a_f200* hitPosition);                        // 0x004a3dc0
}
namespace SP {
void RepinBlock(cSPEditorBlock_s005a_f200* block, BlockList* blocks, cSPEditorBlock_s005a_f200* parent);  // 0x004a29a0
}
namespace SP {
void UnpinBlock(cSPEditorBlock_s005a_f200* block);                                    // 0x004a1070
}
namespace SP {
bool PlaceBlockOnBody(cSPEditorBlock_s005a_f200* block, BlockList* blocks, cSPVector3_s005a_f200 origin, cSPVector3_s005a_f200 direction, SkinRef skin,
                      cSPVector3_s005a_f200* hitPosition, int a, int b, int c);       // 0x0049a2a0
}
namespace SP {
void PlaceBlock(cSPEditorBlock_s005a_f200* block, int a, float scale, int b);         // 0x004982b0
}
namespace SP {
void GetMissPlane(cSPEditorBlock_s005a_f200* block, cSPVector3_s005a_f200 direction, cSPVector3_s005a_f200* position, cSPVector3_s005a_f200* normal);  // 0x0049b8b0
}
namespace SP {
void PlaceOnMissPlane(cSPEditorBlock_s005a_f200* block, cSPVector3_s005a_f200 origin, cSPVector3_s005a_f200 direction, cSPVector3_s005a_f200 planePosition,
                      cSPVector3_s005a_f200 planeNormal, int b);                      // 0x0049bcc0
}
namespace SP {
void GetLineForJoint(cSPEditorBlock_s005a_f200* block, cSPVector3_s005a_f200 origin, cSPVector3_s005a_f200 direction, cSPVector3_s005a_f200* lineStart,
                     cSPVector3_s005a_f200* lineEnd);                                 // 0x00496d30
}
namespace SP {
bool ConstrainOffset(cSPVector3_s005a_f200 offset, cSPVector3_s005a_f200* result, float scale);  // 0x00497f20
}
namespace SP {
cSPVector3_s005a_f200 MirrorPosition(const cSPVector3_s005a_f200& v);                            // 0x004a8f40
}
namespace SP {
namespace EditorUtils {
void SetSymmetricBlocksUIState(cSPEditorBlock_s005a_f200* block, int a, int b);  // 0x004a7f30
}
}
namespace SP {
namespace EditorUtils {
cSPEditorBlock_s005a_f200* GetFirstFootBlock(cSPEditorBlock_s005a_f200* block);              // 0x004a9840
}
}
namespace SP {
class cSPEditorManipulationObject_s005a_f200 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};
}
namespace SP {
class cRefCountV {
 public:
  virtual ~cRefCountV();
  int mRefCount;
};
}
namespace SP {
class cSPEditorManipulationLimb_s005a_f200 : public cSPEditorManipulationObject_s005a_f200, public cRefCountV {
 public:
  cSPEditorSkinManager_s005a_f200* mSkin;                       // +0x1c
  cSPEditorLimbStructure_s005a_f200* mLimbStructure;            // +0x20
  cSPEditorLimbStructure_s005a_f200* mSymmetricLimbStructure;   // +0x24
  cSPEditorLimbStructure_s005a_f200* mMirrorLimbStructure;      // +0x28
  JointVector_s005a_f200 mManipulatingJoints;                   // +0x2c
  JointVector_s005a_f200 mSymmetricJoints;                      // +0x40
  JointVector_s005a_f200 mMirrorJoints;                         // +0x54
  HighlightVector mHighlights;                       // +0x68
  HighlightVector mSymmetricHighlights;              // +0x7c
  JointVector_s005a_f200 mAllJoints;                            // +0x90
  JointVector_s005a_f200 mAllSymmetricJoints;                   // +0xa4
  cSPEditorBlock_s005a_f200* mBlock;                            // +0xb8
  cSPEditorBlock_s005a_f200* mOriginalParent;                   // +0xbc
  float mX;                                          // +0xc0
  float mY;                                          // +0xc4
  float mOldX;                                       // +0xc8
  float mOldY;                                       // +0xcc
  unsigned int mModifiers;                           // +0xd0
  cSPVector3_s005a_f200 mMouseOffset;                           // +0xd4
  cSPVector3_s005a_f200 mOriginalMouseOffset;                   // +0xe0
  cSPVector3_s005a_f200 mOriginalBlockPosition;                 // +0xec
  int mManipType;                                    // +0xf8
  int mOriginalManipType;                            // +0xfc
  bool mIsOutsideBounds;                             // +0x100
  bool mIsStacking;                                  // +0x101
  cISPEditorBadnessCalculator_s005a_f200* mBadnessCalculator;   // +0x104
  cSPVector3_s005a_f200 mMissPlanePosition;                     // +0x108
  cSPVector3_s005a_f200 mMissPlaneNormal;                       // +0x114
  cSPVector3_s005a_f200 mLimbMissPlanePosition;                 // +0x120
  cSPVector3_s005a_f200 mLimbMissPlaneNormal;                   // +0x12c
  int mBestIndex;                                    // +0x138
  cSPEditortLimbTry_s005a_f200 mBestTry;                        // +0x13c
  cSPEditortLimbTry_s005a_f200 mWorstTry;                       // +0x160
  cSPEditortLimbTry_s005a_f200 mTries[400];                     // +0x184

  void Update(float deltaTime);
  void ClearSymmetricHighlights();        // 0x005adb00
  float GetMaxLimbPlacementHeight();      // 0x005addb0
  void UpdateSymmetricJointPositions();   // 0x005addf0
  void CopyJointsToSymmetricLimbs();      // 0x005adf10
  void RecalculateLimbMissPlane();        // 0x005ae300
  void RefreshJointLists();               // 0x005ae750
  cSPEditortLimbTry_s005a_f200 PickOptimalPointOnLine(cSPEditorLimbJoint_s005a_f200* joint, cSPVector3_s005a_f200 lineStart, cSPVector3_s005a_f200 lineEnd,
                                           int numTries, cSPEditortLimbTry_s005a_f200* tries, cSPEditortLimbTry_s005a_f200* worstTry,
                                           int* bestIndex);  // 0x005aed80

 private:
  __forceinline void SetOutsideBounds(bool outside) {
    if (outside) {
      if (!mIsOutsideBounds) {
        mIsOutsideBounds = true;
        PlayEditorSound(0x11156337);
      }
    } else if (mIsOutsideBounds) {
      mIsOutsideBounds = false;
    }
  }
  __forceinline void FinishUpdate() {
    mBlock->RecursiveFlagA();
    EditorUtils::SetSymmetricBlocksUIState(mLimbStructure->GetRootBlock(), 0, 1);
  }
};
}
namespace SP {
static inline float Sign1(float v) { return v < 0.0f ? -1.0f : 1.0f; }
}
// ---- items of slice s005af200 end

// ---- items of slice s005ae870 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* FUN_005ae5d0(void* dst, void* first, void* last);  // 0x005ae5d0  copy 0x3c-stride records
struct HighlightVec {
    int  mBegin;   // +0  pointer to first 0x3c-stride record
    int  mEnd;     // +4  pointer past the last record
    void Clear();
};
// ---- items of slice s005ae870 end

// ---- items of slice s005b0f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct MObj {
  virtual ~MObj() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  char pad_7;
  float mDeadZoneSize;   // +0x8
  float mInitialX;       // +0xc
  float mInitialY;       // +0x10
  MObj();
  void* AsInterface(int typeID);
  void OnMouseDown(int a1, float a2, float a3, int a4);
  bool OnMouseMove(float a1, float a2, int a3);
};
// ---- items of slice s005b0f80 end

// ---- items of slice s009ccfe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_014479b0;   // 1e-06f
float __cdecl FUN_009cdbe0(float, float, float, float, float);                   // 0x009cdbe0 (self)
// ---- items of slice s009ccfe0 end

// ---- items of slice s009cddf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_01485720;   // 1.0f
extern float DAT_01551474;   // 0.15f
extern float DAT_014479a4;   // pi
extern float DAT_0155145c;   // 2*pi
typedef unsigned char uint8;
float __cdecl FUN_009b3c10(float x, float y);                       // 0x009b3c10
struct CurveOut { float v0, v1, v2, v3, v4, v5, v6; };            // 28-byte key-eval result
struct cCurveKey { void* __thiscall eval(void* out, float t); };
struct SA {
    float f00, f04, f08, f0c;                       // 0x00
    float f10, f14, f18, f1c;                       // 0x10
    float f20, f24, f28, f2c;                       // 0x20
    float f30, f34, f38, f3c;                       // 0x30
    float f40;                                      // 0x40
    int   i44, i48;                                 // 0x44
    float f4c;                                      // 0x4c
    int   i50;                                      // 0x50
    float f54;                                      // 0x54
    int   i58;                                      // 0x58
    uint8 b5c, b5d; uint8 pad5e[2];                 // 0x5c
    float f60;                                      // 0x60
    int   i64, i68;                                 // 0x64
    float f6c, f70, f74, f78, f7c, f80, f84, f88;   // 0x6c
    float f8c, f90, f94, f98, f9c, fa0, fa4, fa8;   // 0x8c
    float fac;                                      // 0xac
    int   iB0;                                      // 0xb0
    float fB4, fB8, fBC, fC0;                       // 0xb4
    int   iC4, iC8;                                 // 0xc4
    float fCC, fD0, fD4, fD8, fDC, fE0, fE4, fE8;   // 0xcc
    float fEC, fF0, fF4, fF8, fFC, f100, f104;      // 0xec

    void   FUN_009cddf0(int p1, float p2, float p3, float p4,
                        float p5, float p6, float p7, float p8);
    float  FUN_009cdfb0(float t);
    float  FUN_009ce100(char flag);
    float  FUN_009ce150(int idx, int* ptr, float a, float b, float c);
    float* FUN_009ce370(float* out, void* ptr, float a, float b, float c);
    void   FUN_009ce5e0();
    void   FUN_009ce720(int* a, int* b);
    void   FUN_009ce740(float x);
    void   FUN_009ce790(SA* src);
};
// ---- items of slice s009cddf0 end

// ---- items of slice s009cede0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace checkerlib {
class vector_3_s009c_ede0 { public: float x, y, z, w; };   // 16 bytes in this build: passed by value as four dwords
}
using checkerlib::vector_3_s009c_ede0;
namespace nSPCreatureAnim {
struct creature_body_static_data_s009c_ede0;
}
namespace nSPCreatureAnim {
struct creature_body_instance_data_s009c_ede0;
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009c_ede0;
}
namespace nSPCreatureAnim {
class dynamics_foot_s009c_ede0;
}
namespace nSPCreatureAnim {
struct curve_sample_a {                       // the object the [0x64]/[0x68] fields hold
    void* Sample(void* out, float t);         // 0x009dcc50  ret 8   (called at +4)
};
}
namespace nSPCreatureAnim {
struct curve_sample_b {
    void* Sample(void* out, float t);         // 0x009dd0c0  ret 8   (called at +0x18)
};
}
namespace nSPCreatureAnim {
void  FUN_0099cc70(float* out, const float* a, const float* b, float w);   // 0x0099cc70 cdecl
}
namespace nSPCreatureAnim {
void  FUN_009cda70(float* out, const float* m);                            // 0x009cda70 cdecl
}
namespace nSPCreatureAnim {
float nSPCreatureAnim_biasedSigmoid(float, float, float, float, float, float);  // 0x009cdce0 cdecl
}
namespace nSPCreatureAnim {
struct creature_body_static_data_s009c_ede0 {            // retail size 0x468
    char  pad_000[0x10c];
    float rest_cx, rest_cy, rest_cz;          // 0x10c
    float q_118, q_11c, q_120, q_124;         // 0x118 (quaternion, component order per the retail formulas)
    char  pad_128[0x154 - 0x128];
    uint8 flags_154;                          // 0x154
    char  pad_155[0x1f8 - 0x155];
    int   bidx;                               // 0x1f8
    char  pad_1fc[0x430 - 0x1fc];
    int   anim_group;                         // 0x430
    float f_434;                              // 0x434
    float f_438;                              // 0x438
    float f_43c;                              // 0x43c
    char  pad_440[0x468 - 0x440];
};
}
namespace nSPCreatureAnim {
struct creature_body_instance_data_s009c_ede0 {          // retail size 0x2bc
    char  pad_000[0x7c];
    float rest_x, rest_y, rest_z;             // 0x7c
    char  pad_088[0x2bc - 0x88];
};
}
namespace nSPCreatureAnim {
struct creature_static_data_s009c_ede0 {                 // partial; only the pieces this slice touches
    char  pad_000[0x384];
    creature_body_static_data_s009c_ede0* bodies_begin;  // 0x384
    float leg_len_a(float w, int bidx, int grp);   // 0x009b5080 ret 0xc
    float leg_len_b(float w, int bidx, int grp);   // 0x009b51c0 ret 0xc
    float leg_len_c(float w, int bidx, int grp);   // 0x009b5100 ret 0xc
    float leg_len_d(float w, int bidx, int grp);   // 0x009b5180 ret 0xc
};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009c_ede0 {
    creature_static_data_s009c_ede0* static_data;        // 0x000
    char  pad_004[0x2e4 - 4];
    creature_body_instance_data_s009c_ede0* bodies;      // 0x2e4
    char  pad_2e8[0x15b8 - 0x2e8];
    int   f_15b8;                             // 0x15b8
    int   f_15bc;                             // 0x15bc
};
}
namespace nSPCreatureAnim {
struct gait_src {
    char  pad_000[0x68];
    float f_68;                               // 0x68
    float f_6c;                               // 0x6c
    float f_70;                               // 0x70
    float f_74;                               // 0x74
    float f_78;                               // 0x78
    char  pad_07c[0xdc - 0x7c];
    float f_dc;                               // 0xdc
};
}
namespace nSPCreatureAnim {
class dynamics_foot_s009c_ede0 { public:
    float pos[3];                             // 0x000
    float prev_pos[3];                        // 0x00c
    float unk_18[3];                          // 0x018
    float orient[4];                          // 0x024
    float prev_orient[4];                     // 0x034
    float f_44;                               // 0x044
    float f_48;                               // 0x048
    float f_4c;                               // 0x04c
    float f_50;                               // 0x050
    float f_54;                               // 0x054
    int   index;                              // 0x058
    char  pad_05c;
    uint8 flag_5d;                            // 0x05d
    char  pad_05e[2];
    float ratio;                              // 0x060
    curve_sample_a* curve_64;                 // 0x064
    curve_sample_b* curve_68;                 // 0x068
    float f_6c;                               // 0x06c
    float f_70;                               // 0x070
    float f_74;                               // 0x074
    float phase;                              // 0x078
    float rest_angle[3];                      // 0x07c
    float orient2[4];                         // 0x088
    float phase_offset;                       // 0x098
    char  pad_09c[0x0c];
    float f_a8;                               // 0x0a8
    float f_ac;                               // 0x0ac
    int   motion;                             // 0x0b0
    char  pad_0b4[0x0c];
    float f_c0;                               // 0x0c0
    int   f_c4;                               // 0x0c4
    creature_instance_data_s009c_ede0* creature;         // 0x0c8
    char  pad_0cc[8];
    float turn;                               // 0x0d4
    char  pad_0d8[0x28];
    float phl;                                // 0x100
    float phu;                                // 0x104

    vector_3_s009c_ede0* SampleBlendPos(vector_3_s009c_ede0* out, float t);
    vector_3_s009c_ede0* SampleBlendRot(vector_3_s009c_ede0* out, float t);
    void      SetBendAngle(gait_src* p, float a, float b);
    void      AdvancePhase(float dt);
    void      UpdateStance();
    float     CalcBendBlendFactor(void* creature, float t);
    float     GetDeltaCoordinate(int idx, void* pRoot, vector_3_s009c_ede0 v);  // 0x009cf7d0 (nSPCreatureAnim::dynamics_foot::GetDeltaCoordinate)
    vector_3_s009c_ede0* CalcDeltaRootPosition(vector_3_s009c_ede0* out, void* pRoot, vector_3_s009c_ede0 v);
    float     FUN_009cdfb0(float x);          // 0x009cdfb0  ret 4  (ecx = this)
    float     FUN_009ce100(bool b);           // 0x009ce100  ret 4  (ecx = this)
};
}
namespace nSPCreatureAnim {
struct body_ref { creature_body_static_data_s009c_ede0* body; };
}
namespace nSPCreatureAnim {
struct foot_pair {
    char        pad_00[4];
    body_ref*   ref;                          // 0x004
    char        pad_08[0x24 - 8];
    float       f_24;                         // 0x024
    float       f_28;                         // 0x028
    float       f_2c;                         // 0x02c
    void BlendFeet(float* outPos, float* outQuat, dynamics_foot_s009c_ede0* footA, dynamics_foot_s009c_ede0* footB,
                   float w, float w2, float* inQuat);
};
}
namespace nSPCreatureAnim {
float GetAnimationBlend(void* body);          // 0x009b33f0 cdecl (1 arg)
}
namespace nSPCreatureAnim {
extern float DAT_0155125c;                    // 0x0155125c
}
namespace nSPCreatureAnim {
extern int   DAT_015515dc;                    // 0x015515dc
}
namespace nSPCreatureAnim {
extern float DAT_0155147c;                    // 0x0155147c
}
namespace nSPCreatureAnim {
extern float DAT_01551478;                    // 0x01551478
}
namespace nSPCreatureAnim {
extern float DAT_01551470;                    // 0x01551470
}
namespace nSPCreatureAnim {
extern float DAT_01551480;                    // 0x01551480
}
namespace nSPCreatureAnim {
extern float DAT_01551484;                    // 0x01551484
}
namespace nSPCreatureAnim {
extern float DAT_01551488;                    // 0x01551488
}
namespace nSPCreatureAnim {
extern float DAT_0155148c;                    // 0x0155148c
}
namespace nSPCreatureAnim {
extern float DAT_01551490;                    // 0x01551490
}
namespace nSPCreatureAnim {
extern float DAT_01551494;                    // 0x01551494
}
namespace nSPCreatureAnim {
extern float DAT_01551498;                    // 0x01551498
}
namespace nSPCreatureAnim {
extern float DAT_0155149c;                    // 0x0155149c
}
namespace nSPCreatureAnim {
extern float DAT_01550a10;                    // 0x01550a10
}
namespace nSPCreatureAnim {
extern float DAT_0166c67c;                    // 0x0166c67c
}
namespace nSPCreatureAnim {
extern float DAT_0166c7d0;                    // 0x0166c7d0
}
namespace nSPCreatureAnim {
extern uint8 DAT_01551254;                    // 0x01551254
}
namespace nSPCreatureAnim {
extern uint8 DAT_01551255;                    // 0x01551255
}
namespace nSPCreatureAnim {
extern uint8 DAT_01551256;                    // 0x01551256
}
namespace nSPCreatureAnim {
static inline float clampf(float v, float lo, float hi)
{
    return v < lo ? lo : (v > hi ? hi : v);
}
}
// ---- items of slice s009cede0 end

// ---- items of slice s009cfd40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_1e6;    // 0x014479b4 = 1000000.0f
extern float g_m1e6;   // 0x013ef654 = -1000000.0f
extern float g_08;     // 0x015514a0 = 0.8f
extern float g_h05;    // 0x015514a4 = 0.5f
extern float g_09;     // 0x015514a8 = 0.9f
typedef unsigned int uint;
struct Inner70 { char pad[0x70]; float c; };
struct SA_s009c_fd40 {
    void*    q0_0;                // +0x00 pointer used by 009d0460/009d0b10
    void*    p04;                 // +0x04 pointer
    char     pad08[0x48 - 0x08];
    float    f48;                 // +0x48
    float    f4c;                 // +0x4c
    char     pad50[0x58 - 0x50];
    int      f58;                 // +0x58
    char     pad5c[0x6c - 0x5c];
    float    f6c;                 // +0x6c
    char     pad70[0x7c - 0x70];
    float    f7c;                 // +0x7c
    float    f80;                 // +0x80
    float    f84;                 // +0x84
    float    f88, f8c, f90, f94, f98;
    float    f9c;                 // +0x9c
    float    fa0;                 // +0xa0
    float    fa4;                 // +0xa4
    char     padA8[0xc8 - 0xa8];
    void*    fC8;                 // +0xc8
    char     padCC[0x114 - 0xcc];
    float    f114;                // +0x114
    char     pad118[0x350 - 0x118];
    float    f350;                // +0x350
    float    f354;                // +0x354
    float    f358;                // +0x358
    char     pad35c[0x434 - 0x35c];
    float    f434;                // +0x434

    void   Integrate(float dt, float* v, void* a3);                    // ?Bone_IntegrateVelocity@@..
    float* FA90(float* out, void* p, float a, float b, float c, float d);   // 0x009cfa90
    float* F370(float* out, void* p, float a, float b, float c);            // 0x009ce370
};
struct Host40 {
    char  pad[4];
    SA_s009c_fd40*   f4;                     // +0x04
    void FUN_009cfd40(float* dir, void* a3, float dt);
};
struct HostBC {
    char  pad[4];
    SA_s009c_fd40**  begin;                  // +0x04
    SA_s009c_fd40**  end;                    // +0x08
    void FUN_009cfdc0(float* w, float* h, float* minX, float* maxX, float* minY, float* maxY);
};
struct Param0 {
    char  pad00[0x10];
    float f10, f14, f18;          // +0x10
    char  pad1c[0x24 - 0x1c];
    float f24;                    // +0x24
    char  pad28[0x30 - 0x28];
    float f30, f34, f38;          // +0x30
    char  pad3c[0x4c - 0x3c];
    int   f4c;                    // +0x4c
    int   f50;                    // +0x50
};
struct HostD {
    char  pad04[0x04 - 0x00];
    SA_s009c_fd40**  begin;                  // +0x04
    SA_s009c_fd40**  end;                    // +0x08
    char  pad0c[0x18 - 0x0c];
    float f18, f1c, f20;          // +0x18
    char  pad24[0x34 - 0x24];
    float f34;                    // +0x34
    void FUN_009d00a0(float* out, Param0* p);
};
struct HostF {
    char  pad[4];
    SA_s009c_fd40**  begin;                  // +0x04
    SA_s009c_fd40**  end;                    // +0x08
    float* FUN_009d0a40(float* out, Param0* p);
};
// ---- items of slice s009cfd40 end

// ---- items of slice s009d1b40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Group                                        // 0x38 bytes
{
    void*       head;                               // +0x00  object whose +0x110 is a float
    uint8_t**   items;                              // +0x04  entry pointer array
    uint8_t**   end;                                // +0x08
    uint8_t     pad0c[0x2c];
};
struct Src                                          // layout description handed in
{
    uint8_t     pad00[0x10];
    int32_t     mode;                               // +0x10  -1 = no per-entry pass
    uint8_t*    first;                              // +0x14  0xc-byte records
    uint8_t*    last;                               // +0x18
    uint8_t     pad1c[0x20];
    float       f3c, f40, f44, f48;                 // +0x3c
    float       f4c, f50, f54, f58;                 // +0x4c
    float       f5c, f60, f64, f68;                 // +0x5c
    float       seq[14];                            // +0x6c .. +0xa3
    uint8_t     pad_a4[4];
    float       fa8;                                // +0xa8
    void*       pac;                                // +0xac
    void*       pb0;                                // +0xb0

    bool        WantsOffsets();                     // 0x009de630
};
struct Vec3
{
    float x, y, z;
};
struct Atlas                                        // object reached through Layout::f48
{
    uint8_t     pad00[0x24];
    uint8_t*    base;                               // +0x24  entry array base
};
struct Layout
{
    uint8_t     pad00[0x10];
    float       f10, f14, f18, f1c;                 // +0x10
    float       f20, f24, f28, f2c;                 // +0x20
    float       f30, f34, f38, f3c;                 // +0x30
    float       f40, f44;                           // +0x40
    Atlas*      f48;                                // +0x48
    Group*      gb;                                 // +0x4c  group array
    Group*      ge;                                 // +0x50
    uint8_t     pad54[0x0c];
    float       f60;                                // +0x60
    float       f64;                                // +0x64  accumulated advance
    float       f68, f6c, f70, f74;                 // +0x68
    float       f78, f7c, f80;                      // +0x78
    float       f84;                                // +0x84
    float       f88;                                // +0x88
    uint8_t     pad8c[0x0c];
    float       f98;                                // +0x98
    uint8_t     pad9c[0x20];
    int32_t*    ib;                                 // +0xbc
    int32_t*    ie;                                 // +0xc0
    uint8_t     padc4[0x10];
    float       fd4, fd8;                           // +0xd4
    uint8_t     paddc[0x1c];
    float       ff8;                                // +0xf8

    void        Apply(Src* s);                      // 0x009d1b40
    void        AlignLines();                       // 0x009d1c90
    void        SetupFrom(Src* s);                  // 0x009d2160
    void        BuildStops(int n, void* a2, void* a3, void* a4, int32_t* a5);  // 0x009d24c0
    float       MinThickness(Vec3 v);                // 0x009d25b0
    float       AngleScale(float angle);            // 0x009d2700

    void        GetExtents(void* extents, void* centres);   // 0x009d12c0
    void        BeginGradient(void* p);             // 0x009d13a0
    void        AddStop(float v, void* p);          // 0x009d15e0
    void        EndGradient(void* p);               // 0x009d19b0
};
void FUN_009ce430(float* out, int32_t n);           // 0x009ce430
void FUN_009ce560(float* vec, int32_t n);           // 0x009ce560
// ---- items of slice s009d1b40 end

// ---- items of slice s009d29b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(sqrt, sin, cos, atan2, fabs)
static __forceinline float Sqrt(float x) { return (float)sqrt((double)x); }
static __forceinline float Sin(float x) { return (float)sin((double)x); }
static __forceinline float Cos(float x) { return (float)cos((double)x); }
static __forceinline float Atan2(float y, float x) { return (float)atan2((double)y, (double)x); }
struct Vec3Arg { float x, y, z; Vec3Arg(const Vec3Arg& v) : x(v.x), y(v.y), z(v.z) {} };
struct WaypointInfo { uint32_t pad0; uint8_t mFlag; };      // +4 byte tested by FUN_009d29b0
struct Bone { uint32_t pad[0x43]; float x, y, z; uint32_t pad2[(0x1f8 - 0x10c - 12) / 4]; int mChildCount; };  // x,y,z at +0x10c
struct Waypoint {                  // 0x30 bytes
    WaypointInfo* info;            // +0x00
    Bone** bone;                   // +0x04
    float x, y, z;                 // +0x08
    uint32_t pad14[(0x24 - 0x14) / 4];
    float mWeightA;                // +0x24
    float mWeightB;                // +0x28
    float mWeightC;                // +0x2c
};
struct LimbPoint {                 // 0x38 bytes
    int mId;
    uint32_t pad04[(0x24 - 4) / 4];
    uint8_t mActive;               // +0x24
    uint32_t pad25[(0x38 - 0x28) / 4];
    bool Check();                  // 0x9d0c10
    void Activate();               // 0x9d0280
};
struct Limb {                      // 0x104 bytes
    uint32_t mCount;               // +0x00
    uint32_t pad04[(0x4c - 4) / 4];
    LimbPoint* mPointsBegin;       // +0x4c
    LimbPoint* mPointsEnd;         // +0x50
    uint32_t pad54[(0x84 - 0x54) / 4];
    float mAccum;                  // +0x84
    float mPhase;                  // +0x88
    uint32_t pad8c[(0xbc - 0x8c) / 4];
    uint32_t* mIdsBegin;           // +0xbc
    uint32_t* mIdsEnd;             // +0xc0
    uint32_t padc4[(0xd0 - 0xc4) / 4];
    float mRatio;                  // +0xd0
    uint32_t padd4[(0x104 - 0xd4) / 4];
    float GetA();                  // 0x9d0c90
    float GetB();                  // 0x9d0db0
    void Compute(void* item, void* a, void* b, void* c, void* d);   // 0x9d24c0
    float GetStepTime(float speed);  // 0x9d2700
    float GetStepTime2(Vec3Arg vel); // 0x9d25b0
};
struct LimbParams {
    uint32_t mCount;
    void* mItems[0x1e];
    // +0x7c, +0xdc, +0x13c, +0x140 are consecutive arrays indexed by limb
};
struct MoveInfo { uint32_t pad[0xd9]; float vx, vy; };      // +0x364, +0x368
struct MoveObj { MoveInfo* info; uint32_t pad[(0x70 - 4) / 4]; float mScale; };   // +0x70
struct Locomotion {
    uint32_t pad0[2];
    float mSmoothedSpeed;          // +0x08
    float mSmoothedTurn;           // +0x0c
    Limb* mLimbsBegin;             // +0x10
    Limb* mLimbsEnd;               // +0x14
    uint32_t pad18[(0x24 - 0x18) / 4];
    uint8_t* mItemsBegin;          // +0x24 (0x108 stride)
    uint8_t* mItemsEnd;            // +0x28
    uint32_t pad2c[(0x38 - 0x2c) / 4];
    Waypoint* mWaypointsBegin;     // +0x38
    Waypoint* mWaypointsEnd;       // +0x3c
    uint32_t pad40[(0x4c - 0x40) / 4];
    Vec3 mVelocity;                // +0x4c
    Vec3 mPrevVelocity;            // +0x58
    float mSpeed;                  // +0x64
    float mPrevSpeed;              // +0x68

    bool IsPointUnique(LimbPoint* p);                          // 0x9d3020
    void RefreshPoints();                                      // 0x9d30b0
    void ClassifyLimbs();                                      // 0x9d3170
    void Integrate(Vec3* vel, float speed);                    // 0x9d3200
    void UpdatePhases();                                       // 0x9d32d0
    void ComputeLimbs(LimbParams* p);                          // 0x9d33a0
    Limb* FindLimbAboveThreshold(float threshold);             // 0x9d3410
    void ComputeRatios();                                      // 0x9d34a0
    float GetMaxSpeed();                                       // 0x9d3530
    float GetStepScale(float f);                               // 0x9d3580
    float GetAmplitude(MoveObj* o, float angle);               // 0x9d3610
    float GetStepRate(MoveObj* o, float f, float angle);       // 0x9d3710
    float GetStepScale2(float f);                              // 0x9d3790
    float GetTurnFactor(Vec3* v);                              // 0x9d3840
};
// ---- items of slice s009d29b0 end

// ---- items of slice s009d3950 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_01551258;   // distance threshold
extern float DAT_015515dc;   // gait blend toggle
extern char  DAT_01551256;   // gait bend toggle
extern float DAT_01551508;   // bend blend scale
extern float DAT_0155150c;   // hermite range
typedef unsigned int   uint32;
struct SA_s009d_3950 {
    float f00, f04, f08, f0c;                       // 0x00
    float f10, f14, f18, f1c;                       // 0x10
    float f20, f24, f28, f2c;                       // 0x20
    float f30, f34, f38, f3c;                       // 0x30
    float f40;                                      // 0x40
    int   i44, i48;                                 // 0x44
    float f4c;                                      // 0x4c
    int   i50;                                      // 0x50
    float f54;                                      // 0x54
    int   i58;                                      // 0x58
    uint8 b5c, b5d; uint8 pad5e[2];                 // 0x5c
    float f60;                                      // 0x60
    int   i64, i68;                                 // 0x64
    float f6c, f70, f74, f78, f7c, f80, f84, f88;   // 0x6c
    float f8c, f90, f94, f98, f9c, fa0, fa4, fa8;   // 0x8c
    float fac;                                      // 0xac
    int   iB0;                                      // 0xb0
    float fB4, fB8, fBC, fC0;                       // 0xb4
    int   iC4, iC8;                                 // 0xc4
    float fCC, fD0, fD4, fD8, fDC, fE0, fE4, fE8;   // 0xcc
    float fEC, fF0, fF4, fF8, fFC, f100, f104;      // 0xec

    SA_s009d_3950(const SA_s009d_3950& src);                              // 0x009ce790  member-wise copy
    SA_s009d_3950& operator=(const SA_s009d_3950& src);                   // 0x009ce790
};
struct SAGreater {
    uint32 mUnused;
    bool operator()(SA_s009d_3950 a, SA_s009d_3950 b) const { return a.fac > b.fac; }
};
void __cdecl promote_heap(SA_s009d_3950* first, int topPosition, int position, SA_s009d_3950 value, SAGreater compare);
struct Obj2;
struct Obj2 {
    void*  p00;                                     // 0x00  -> [p00 + 0x3ec] float
    uint8  _04[0x70 - 0x04];
    float  f70;                                     // 0x70
    uint8  _74[0x84 - 0x74];
    float  f84;                                     // 0x84
    float  f88;                                     // 0x88
    uint8  _8c[0xa8 - 0x8c];
    float  fa8, fac, fb0, fb4;                      // 0xa8
    uint8  _b8[0xf8 - 0xb8];
    float  ff8;                                     // 0xf8
    uint8  _fc[0x2d5 - 0xfc];
    uint8  b2d5;                                    // 0x2d5
    uint8  _2d6[0x1684 - 0x2d6];
    int    i1684;                                   // 0x1684
};
struct vector_3 { float x, y, z; };
struct GaitBlk {
    double FUN_009d3530();                          // 0x009d3530
};
struct AnimDyn {
    float  f00, f04, f08;                           // 0x00
    uint8  _0c[0x10 - 0x0c];
    void*  p10;                                     // 0x10  begin of the 0x104-byte record vector
    void*  p14;                                     // 0x14  end
    float  f18, f1c, f20;                           // 0x18  outputs of 0x009d42b0
    uint8  _24[0x4c - 0x24];
    float  f4c, f50, f54;                           // 0x4c
    int    i58;                                     // 0x58
    uint8  _5c[0x64 - 0x5c];
    float  f64, f68;                                // 0x64
    uint8  _6c[0x78 - 0x6c];
    float  f78, f7c, f80, f84;                      // 0x78
    uint8  _88[0xc0 - 0x88];
    float  fC0;                                     // 0xc0
    uint8  _c4[0xc8 - 0xc4];
    void*  pC8;                                     // 0xc8
    uint8  _cc[0xd0 - 0xcc];
    float  fD0, fD4, fD8;                           // 0xd0
    float  fDC, fE0, fE4, fE8, fEC, fF0, fF4;       // 0xdc
    float  fF8, fFC;                                // 0xf8

    float  FUN_009d3790(float t);                   // 0x009d3790
    float  FUN_009d3840(int x);                     // 0x009d3840
    float  FUN_009d3710(Obj2* p, float a, float b); // 0x009d3710
    float  FUN_009d3950(Obj2* p, float dt, int x);  // 0x009d3950
    float  FUN_009d3a20(Obj2* p, float a, int x, float b);  // 0x009d3a20
    void   FUN_009d3b50(float t);                   // 0x009d3b50
    vector_3* SampleBlendPos(vector_3* out, float t);        // 0x009cede0
    float     CalcBendBlendFactor(Obj2* pRoot, float t);     // 0x009cf740
    void   FUN_009d42b0(Obj2* p);                   // 0x009d42b0
};
float  LengthSqVec3(const float* v);                             // 0x009a49b0
static float FUN_009cddc0_s009d_3950(float /*unused*/, float v)
{
    if (v < 1e-06f)
        return -1.0f;
    if (1e-06f < v)
        return 1.0f;
    return 0.0f;
}
// ---- items of slice s009d3950 end

// ---- items of slice s009d46d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int   g_15515dc;      // path-1 enable
extern char  g_1551256;      // "damp" flag
extern float g_155125c;      // 100.0
extern float g_155151c;      // 2.5
extern float g_1551258;      // 1e-12 (min squared length)
extern float g_1551518;      // 1.2
extern float g_1551510;      // 1.2
extern float g_1551514;      // 2.5
extern float g_1551458;      // pi/2
extern float g_15514e0;      // 1.0 (extent scale)
extern char g_166c6b0;       // force full damping
extern char g_166c6b1;       // freeze the spin
float FUN_009a49b0(const Vec3* v);                                        // cdecl, returns |v|^2 in st0
static __declspec(noinline) float Sign(float x)                  // 0x009cddc0: arg in xmm1, result in xmm0
{
    if (1e-6f > x) return -1.0f;
    if (x > 1e-6f) return 1.0f;
    return 0.0f;
}
static __declspec(noinline) float Bias(float a, float b)         // 0x009cdb20: stack args, result in xmm0
{
    float r;
    if (fabs(b) < 1.0f) {
        r = (a * b - b + 1.0f) * a;
    } else if (0.0f > b) {
        r = (float)(1.0 - pow((double)(1.0f - a), pow(2.0, (double)-b)));
    } else {
        r = (float)pow((double)a, pow(2.0, (double)b));
    }
    if (!(r > 0.0f)) return 0.0f;
    if (r > 1.0f) return 1.0f;
    return r;
}
struct ExtentSrc { float sub_9d3530(); };       // thiscall, st0
struct Rec { char pad[0x138]; float f138; float f13c; char pad2[0x468 - 0x140]; };   // 0x468 bytes
struct Q { char pad[0x384]; Rec* recs; };
struct Arr108 { char* b; char* e; };
struct Obj {
    Q* q;
    char pad04[0x15b8 - 4];
    char ext[0x24];                // 0x15b8: ExtentSrc
    Arr108 arr;                    // 0x15dc
    char pad15e4[0x1604 - 0x15e4];
    float f1604, f1608, f160c;
    char pad1610[0x161c - 0x1610];
    float f161c;
    char pad1620[0x1638 - 0x1620];
    float f1638;
};
struct Params {
    char pad00[0x7c];
    float f7c, f80, f84, f88;
    char pad8c[4];
    float f90, f94, f98;
    char pad9c[0xa4 - 0x9c];
    float fa4;                     // 0xa4 zoom scale
    char padA8[0xf8 - 0xa8];
    float ff8;
};
struct Cam {
    float x, y, z;                 // 0x00
    char pad0c[0x0c];
    float px, py, pz;              // 0x18
    char pad24[0x58 - 0x24];
    int idx;                       // 0x58
    char pad5c[0x64 - 0x5c];
    void* p64; void* p68;          // 0x64
    char pad6c[0x78 - 0x6c];
    float f78, f7c, f80, f84;      // 0x78
    char pad88[0xb4 - 0x88];
    Vec3 fb4;                      // 0xb4  orbit velocity result
    float fc0; float pad_c4; Obj* obj; float pad_cc;   // 0xc0
    Vec3 d;                        // 0xd0
    Vec3 off;                      // 0xdc
    float fe8, fec, ff0, ff4, ff8, ffc;                // 0xe8
    float f100, f104;              // 0x100 zoom range

    Vec3* sub_9cede0(Vec3* out, float t);            // thiscall, ret 8
    float sub_9cf740(Params* p, float ext);          // thiscall, ret 8, st0
    void Update(Params* p, int unused, float t);     // @ 0x009d49b0, ret 0xc
    void UpdateOrbit(Params* p);                     // @ 0x009d46d0, ret 4
    void UpdateSpin(Params* p, float step, float blend, float spinRate,
                    float driveX, float driveY, float driveZ);        // @ 0x009d52f0
};
static __forceinline float EasePhase(float x)
{
    if (fabs(x) < 1.0f)
        return x + 1.0f;
    if (0.0f <= x)
        return (float)pow((double)x, 2.0);
    return 0.0f;
}
// ---- items of slice s009d46d0 end

// ---- items of slice s009d5600 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_1470f1c;   // 0x01470f1c  2.0f
extern const float g_1485720;   // 0x01485720  1.0f
extern const float g_1485378;   // 0x01485378  0.0f
extern const float g_14479b0;   // 0x014479b0  1e-6f
extern const float g_13eb1bc;   // 0x013eb1bc -1.0f
extern const float g_1471064;   // 0x01471064  0.5f
extern const int   g_15509e0;   // 0x015509e0  int 1
typedef unsigned int u32;
typedef unsigned char u8;
struct Q4 { float x, y, z, w; };
struct Ent;
struct Obj48
{
    u8     pad00[8];
    float  f08;            // +0x08
    float  f0c;            // +0x0c
    u8     pad10[0x24 - 0x10];
    void*  o24;            // +0x24
    u8     pad28[0x80 - 0x28];
    float  f80;            // +0x80
};
struct Obj2_s009d_5600
{
    u8 raw[0x1700];
};
struct Ent
{
    u8     pad00[0x24];
    Q4     v24;            // +0x24
    u8     pad34[0x48 - 0x34];
    Obj48* o48;            // +0x48
    u8     pad4c[0x58 - 0x4c];
    int    o58;            // +0x58
    u8     o5c;            // +0x5c
    u8     o5d;            // +0x5d
    u8     pad5e[2];
    float  f60;            // +0x60
    void*  o64;            // +0x64
    void*  o68;            // +0x68
    float  f6c;            // +0x6c
    u8     pad70[8];
    float  f78;            // +0x78
    float  f7c;            // +0x7c
    float  f80;            // +0x80
    float  f84;            // +0x84
    Q4     q88;            // +0x88
    float  f98;            // +0x98
    float  f9c;            // +0x9c
    float  fa0;            // +0xa0
    float  fa4;            // +0xa4
    float  fa8;            // +0xa8
    float  fac;            // +0xac
    float  fb0;            // +0xb0
    float  fb4;            // +0xb4
    u8     padb8[4];
    int*   o_bc;           // +0xbc
    u8     padc0[8];
    Obj2_s009d_5600*  o_c8;           // +0xc8
    u8     padcc[4];
    float  fd0;            // +0xd0
    float  fd4;            // +0xd4
    float  fd8;            // +0xd8
    float  fdc;            // +0xdc
    u8     pade0[8];
    float  fe8;            // +0xe8
    u8     padec[4];
    float  ff0;            // +0xf0
    u8     padf4[4];
    float  ff8;            // +0xf8
    u8     padfc[4];
    float  f100;           // +0x100
    float  f104;           // +0x104

    void  Fn5600(Ent* p, float a);                                        // 0x009d5600
    void  Fn5b50(Ent* p, float a);                                        // 0x009d5b50
    void  Fn5f10(Ent* p, float a, float b, float c, float d);             // 0x009d5f10
    float Fn62a0(float d);                                                // 0x009d62a0

    // Collaborators (bodies live in other translation units of the original).
    void  FnCeec0(float* out, float v);                                   // 0x009ceec0
    void  FnCf080(Ent* p, float a, float b);                              // 0x009cf080
    void  Fn49b0(Ent* p, float a, float b);                               // 0x009d49b0
    void  Fn42b0(Ent* p);                                                 // 0x009d42b0
    void  Fn46d0(Ent* p);                                                 // 0x009d46d0
    void  Fn52f0(Ent* p, float a, float b, float c, float d, float e, float f); // 0x009d52f0
};
struct XKey { bool IsInTable(u32 key, u8 def); };                 // 0x009b3050
Q4*  __cdecl QuatMul(Q4* out, const Q4* a, const Q4* b);          // 0x0099c0b0
static __declspec(noinline) void H9ce010(Q4* out, float v);
extern const float g_155125c_s009d_5600;   // 0x0155125c  100.0f
extern const int   g_15515dc_s009d_5600;   // 0x015515dc  int 1
static __declspec(noinline) void H9ce010(Q4* o, float ang)
{
    float h = ang * 0.5f;
    float s = sinf(h), c = cosf(h);
    float x = o->x, y = o->y, z = o->z, w = o->w;
    o->x = x * c + w * s + y * 0.0f - z * 0.0f;
    o->y = y * c + w * 0.0f - x * s + z * 0.0f;
    o->z = z * c + w * 0.0f + x * 0.0f - y * s;
    o->w = w * c - x * 0.0f - y * 0.0f - z * s;
}
static float sgn6(float v)
{
    if (g_14479b0 <= v)
    {
        if (v <= g_14479b0) return g_1485378;
        return g_1485720;
    }
    return g_13eb1bc;
}
// ---- items of slice s009d5600 end

// ---- items of slice s009d75b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct CmpObj { u32 v; };
inline void* operator new(unsigned int, void* p) { return p; }
struct V3 {
    float x, y, z;
    V3(const V3& o) { x = o.x; y = o.y; z = o.z; }
};
struct V4 {
    float x, y, z, w;
    V4(const V4& o) { x = o.x; y = o.y; z = o.z; w = o.w; }
};
struct TElem {
    u32 raw[0x42];
    TElem();                                            // 0x9ce5e0
    void Init(void* a, V3 p, V4 q);                     // 0x9cddf0
    TElem(const TElem& o);                              // 0x9ce790
};
struct TVec {
    TElem* b;
    TElem* e;
    TElem* c;
    void DoInsertValue(TElem* pos, const TElem& v);     // 0x9d7000
};
struct TOwner {
    char pad0[0x24];
    TVec v;
    int AddElem(void* a, const V3* p3, const V4* p4);   // 0x9d7d10
};
void __cdecl IntroLoop(TElem* first, TElem* last, int depth, CmpObj cmp);     // 0x9d7480
void __cdecl InsertionSort(TElem* first, TElem* last, CmpObj cmp);            // 0x9cea00
void __cdecl UnguardedInsertionSort(TElem* first, TElem* last, CmpObj cmp);   // 0x9ceab0
// ---- items of slice s009d75b0 end

// ---- items of slice s009da640 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Ops {
    void Copy(void* src);        // 0x009d8720  copy-construct this from src
    void Assign(void* src);      // 0x009d9620  assign src to this
    void Ctor();                 // 0x009d75b0  default-construct this
    void F000(void* p);          // 0x009da000
    void F5b0(void* p);          // 0x009da5b0
    void F84f0();                // 0x009d84f0
    void F1090(void* p);         // 0x009d1090
    void F30b0();                // 0x009d30b0
    void F2dd0(void* p1, void* p2, void* p3);  // 0x009d2dd0
};
struct Elem {
    char b[0x104];

    u32 FUN_009d0ee0();            // 0x009d0ee0  thiscall, reads this

    Elem() { ((Ops*)this)->Ctor(); }
    Elem(const Elem& o) { ((Ops*)this)->Copy((void*)&o); }
    Elem& operator=(const Elem& o) { ((Ops*)this)->Assign((void*)&o); return *this; }
    ~Elem()
    {
        // the element owns an eastl::vector of 0x38-byte records (each holding a counted buffer
        // at +4) at +0x4c; the record vector and its buffer are released with the -4 cookie test.
        char* p = *(char**)(b + 0x4c);
        char* e = *(char**)(b + 0x50);
        if (p != e) {
            int n = (int)(e - p - 1) / 0x38 + 1;
            do {
                void* q = *(void**)(p + 4);
                if (q && *(int*)((char*)q - 4))
                    ::operator delete(q);
                p += 0x38;
            } while (--n);
        }
        void* buf = *(void**)(b + 0x4c);
        if (buf && *(int*)((char*)buf - 4))
            ::operator delete(buf);
    }
};
struct PhaseVec {
    Elem* mpBegin;
    Elem* mpEnd;
    Elem* mpCap;
    void DoDestroyValues(Elem* first, Elem* last);   // 0x009c3240
    void Grow(Elem* pos, const Elem* value);         // 0x009dada0
};
struct U32Vec {
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCap;
    void DoInsertValue(u32* pos, const u32& value);  // 0x004558a0
};
struct Solver;
struct Bone;
struct Solver {
    bool Fn3430(Bone* a, Bone* b);   // 0x009b3430
    bool Fn5700(Bone* a, Bone* b);   // 0x009b5700
    int  Fn57b0(Bone* a, Bone* b);   // 0x009b57b0
};
void* FUN_009d9ce0(void* a, void* b, void* c);                                        // 0x009d9ce0
void FUN_009cecb0(void* a, void* b, void* c);                                         // 0x009cecb0
void FUN_009d41b0(void* a, void* b, void* c);                                         // 0x009d41b0
void FUN_009d7b20(void* a, void* b, int c);                                           // 0x009d7b20
struct Anim {
    int  FUN_009d3410(float f);               // 0x009d3410  thiscall, reads this
    void A640(void* ctx);                     // 0x009da640
    void A1d0();                              // 0x009db1d0
    void A270();                              // 0x009db270
    Elem* A330();                             // 0x009db330
    void A3f0(void* vec, int count);          // 0x009db3f0
    void A4d0(float f);                       // 0x009db4d0
    int  A590(void* a, void* b, int c);       // 0x009db590
    int  A630(Solver** ps, Bone** a, Bone** b, int c);  // 0x009db630
};
// ---- items of slice s009da640 end

// @ 0x005adb00
namespace SP {
void cSPEditorManipulationLimb::ClearSymmetricHighlights()
{
  if (mSymmetricLimbStructure) {
    ClearHighlights(&mHighlightJoints);
    ClearHighlights(&mSymmetricHighlightJoints);
  }
}
}  // namespace SP

// @ 0x005adb20
namespace SP {
bool cSPEditorManipulationLimb::OnMouseUp(int button, float x, float y, int modifiers)
{
  EA::AutoRefCount_s005a_d9a0<cSPEditorBlock_s005a_d9a0> block(mBlock);
  cSPVector3_s005a_d9a0 origin, direction;
  App()->GetViewer()->GetWorldRayFromScreenCoords(mX, mY, origin, direction);
  cSPEditorBlock_s005a_d9a0* rootBlock = mLimbStructure->GetRootBlock();
  cSPEditorBlock_s005a_d9a0* eventBlock = mLimbStructure->GetEndBlock();
  if (!eventBlock)
    eventBlock = mBlock;
  if (mChangedObject) {
    if (mOriginalParent) {
      if (mBlock->mpParent) {
        EA::AutoRefCount_s005a_d9a0<cSPEditorAnimatedEventInfo_s005a_d9a0> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo_s005a_d9a0());
        info->MessagePost(0xda95baa5, eventBlock, eventBlock == 0 ? 0 : eventBlock->mEditorModel, 0, 0, 0.0f, 0, -1, 1.0f);
      } else {
        EA::AutoRefCount_s005a_d9a0<cSPEditorAnimatedEventInfo_s005a_d9a0> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo_s005a_d9a0());
        info->MessagePost(0x0428e920, eventBlock, eventBlock == 0 ? 0 : eventBlock->mEditorModel, 0, 0, 0.0f, 0, -1, 1.0f);
      }
    } else if (mBlock->mpParent) {
      EA::AutoRefCount_s005a_d9a0<cSPEditorAnimatedEventInfo_s005a_d9a0> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo_s005a_d9a0());
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
}  // namespace SP

// @ 0x005addb0
namespace SP {
float cSPEditorManipulationLimb::GetMaxLimbPlacementHeight()
{
  cSPBoundingBox_s005a_d9a0 box;
  mBlock->mEditorModel->GetBoundingBox(box, true);
  return mBlock->mEditorModel->GetHeight() * 0.95f;
}
}  // namespace SP

// @ 0x005addf0
namespace SP {
void cSPEditorManipulationLimb::UpdateSymmetricJointPositions()
{
  int i = 0;
  int count = mManipulatingJoints.size();
  for (; i < count; i++) {
    cSPEditorLimbJoint_s005a_d9a0* joint = mManipulatingJoints[i];
    cSPEditorBlock_s005a_d9a0* symmetricBlock = joint->mJointBlock->mSymmetricBlock;
    int symCount = mSymmetricJoints.size();
    for (int j = 0; j < symCount; j++) {
      cSPEditorLimbJoint_s005a_d9a0* symJoint = mSymmetricJoints[j];
      if (symmetricBlock == symJoint->mJointBlock)
        symJoint->mTargetPosition = MirrorPosition(joint->mTargetPosition);
    }
    if (joint->mUpperJoint && joint->mUpperJoint->mJointBlock && joint->mUpperJoint->mJointBlock->mSymmetricBlock) {
      cSPEditorLimbStructure_s005a_d9a0* other = mMirrorLimbStructure ? mMirrorLimbStructure : mSymmetricLimbStructure;
      if (other) {
        cSPEditorLimbJoint_s005a_d9a0* symUpper = other->GetJoint(joint->mUpperJoint->mJointBlock->mSymmetricBlock);
        if (symUpper) {
          cSPVector3_s005a_d9a0 pos = MirrorPosition(joint->mTargetPosition);
          unsigned int n = symUpper->mLowerJoints.usize();
          for (unsigned int k = 0; k < n; k++)
            symUpper->mLowerJoints[k]->mTargetPosition = pos;
        }
      }
    }
  }
}
}  // namespace SP

// @ 0x005adf10
namespace SP {
void cSPEditorManipulationLimb::CopyJointsToSymmetricLimbs()
{
  if (mSymmetricLimbStructure) {
    int count = mAllJoints.size();
    for (int i = 0; i < count; i++) {
      cSPEditorLimbJoint_s005a_d9a0* joint = mAllJoints[i];
      if (joint->mUpperJoint) {
        cSPEditorBlock_s005a_d9a0* symmetricBlock = joint->mUpperJoint->mJointBlock->mSymmetricBlock;
        cSPEditorLimbJoint_s005a_d9a0* sym = mSymmetricLimbStructure->GetJoint(symmetricBlock);
        if (sym)
          sym->CopyFrom(joint);
      }
    }
    count = mAllSymmetricJoints.size();
    for (int i = 0; i < count; i++) {
      cSPEditorLimbJoint_s005a_d9a0* joint = mAllSymmetricJoints[i];
      if (joint->mUpperJoint) {
        cSPEditorBlock_s005a_d9a0* symmetricBlock = joint->mUpperJoint->mJointBlock->mSymmetricBlock;
        cSPEditorLimbJoint_s005a_d9a0* sym = mLimbStructure->GetJoint(symmetricBlock);
        if (sym)
          sym->CopyFrom(joint);
      }
    }
  }
}
}  // namespace SP

// @ 0x005adfd0
namespace SP {
void cSPEditorJointMirror_s005a_d9a0::Mirror(cSPEditorLimbJoint_s005a_d9a0* joint)
{
  if (joint->mJointBlock->mSymmetricBlock) {
    cSPEditorLimbJoint_s005a_d9a0* sym = mpTarget->GetJoint(joint->mJointBlock->mSymmetricBlock);
    sym->mTargetPosition = MirrorPosition(joint->mTargetPosition);
  } else if (joint->mUpperJoint && joint->mUpperJoint->mJointBlock && joint->mUpperJoint->mJointBlock->mSymmetricBlock) {
    cSPEditorLimbJoint_s005a_d9a0* symUpper = mpTarget->GetJoint(joint->mUpperJoint->mJointBlock->mSymmetricBlock);
    if (symUpper) {
      cSPVector3_s005a_d9a0 pos = MirrorPosition(joint->mTargetPosition);
      unsigned int n = symUpper->mLowerJoints.usize();
      for (unsigned int k = 0; k < n; k++)
        symUpper->mLowerJoints[k]->mTargetPosition = pos;
    }
  }
  unsigned int count = joint->mLowerJoints.usize();
  for (unsigned int i = 0; i < count; i++)
    Mirror(joint->mLowerJoints[i]);
}
}  // namespace SP

// @ 0x005ae0b0
namespace SP {
bool cSPEditorManipulationLimb::DoOnMouseMove(float x, float y, int modifiers)
{
  mX = x;
  mModifiers = modifiers;
  mY = y;
  if (mBlock->mFlags.test(35) && !mBlock->mFlags.test(51)) {
    mBlock->SetFlag(0x23, false);
    mBlock->SetFlag(0x33, true);
  }
  return true;
}
}  // namespace SP

// @ 0x005ae120
namespace SP {
void cSPEditorManipulationLimb::Shutdown()
{
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
}  // namespace SP

// @ 0x005ae1b0
namespace SP {
cSPEditorManipulationLimb::~cSPEditorManipulationLimb()
{}
}  // namespace SP

// @ 0x005ae300
namespace SP {
void cSPEditorManipulationLimb::RecalculateLimbMissPlane()
{
  mLimbMissPlanePosition = mLimbStructure->GetRootBlock()->mPosition;
  float minHeight = mLimbStructure->GetMinHeight();
  cSPBoundingBox_s005a_d9a0 box;
  mBlock->mEditorModel->GetBoundingBox(box, true);
  float maxHeight = GetMaxLimbPlacementHeight();
  if (mLimbMissPlanePosition.z < minHeight)
    mLimbMissPlanePosition.z = minHeight;
  if (mLimbMissPlanePosition.z > maxHeight)
    mLimbMissPlanePosition.z = maxHeight;
  cSPVector3_s005a_d9a0 cameraPosition, cameraDirection;
  App()->GetViewer()->GetCameraLocationInfo(cameraPosition, cameraDirection, 0, 0);
  cSPVector3_s005a_d9a0 toCamera = -cameraDirection;
  float t = fabsf(Dot_s005a_d9a0(kSPEditorUpAxis_s005a_d9a0, cameraDirection));
  mLimbMissPlaneNormal = toCamera + (kSPEditorUpAxis_s005a_d9a0 - toCamera) * t;
}
}  // namespace SP

// @ 0x005ae480
namespace SP {
bool cSPEditorManipulationLimb::DoOnMouseDown(int button, float x, float y, int modifiers)
{
  EA::AutoRefCount_s005a_d9a0<cSPEditorModel_s005a_d9a0> model(mBlock->mEditorModel);
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
}  // namespace SP

// @ 0x005ae610
namespace SP {
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
}  // namespace SP

// @ 0x005ae750
namespace SP {
void cSPEditorManipulationLimb::RefreshJointLists()
{
  mAllJoints.clear();
  mLimbStructure->GetJoints(mAllJoints);
  if (mSymmetricLimbStructure) {
    mAllSymmetricJoints.clear();
    mSymmetricLimbStructure->GetJoints(mAllSymmetricJoints);
  }
  int count = mAllJoints.size();
  for (int i = 0; i < count; i++) {
    cSPEditorLimbJoint_s005a_d9a0* joint = mAllJoints[i];
    if (joint->mUpperJoint)
      joint->mUpperJoint->RemoveLowerJoint(joint);
  }
  count = mAllSymmetricJoints.size();
  for (int i = 0; i < count; i++) {
    cSPEditorLimbJoint_s005a_d9a0* joint = mAllSymmetricJoints[i];
    if (joint->mUpperJoint)
      joint->mUpperJoint->RemoveLowerJoint(joint);
  }
}
}  // namespace SP

// @ 0x005ae840
namespace SP {
cSPEditortLimbTry& cSPEditortLimbTry::operator=(const cSPEditortLimbTry& x)
{
  mLoc = x.mLoc;
  mBadness = x.mBadness;
  mDebugVals = x.mDebugVals;
  return *this;
}
}  // namespace SP

// @ 0x005af1c0
void HighlightVec::Clear()
{
    int first = mBegin;
    int last  = mEnd;
    FUN_005ae5d0((void*)last, (void*)last, (void*)first);   // FUN_005ae5d0(dst, first, last)
    int size = (int)((char*)last - (char*)first);
    int count = size / 0x3c;
    mEnd += count * 0x3c;}

// @ 0x005af200
namespace SP {
void cSPEditorManipulationLimb_s005a_f200::Update(float deltaTime)
{
  if (!mBlock || !mBlock->mEditorModel)
    return;
  if (mX == mOldX && mY == mOldY)
    return;

  cSPEditorModel_s005a_f200* model = mBlock->mEditorModel;
  mIsStacking = false;
  if (!mChangedObject)
    mChangedObject = true;
  mOldX = mX;
  mOldY = mY;

  cSPVector3_s005a_f200 origin, direction;
  App_s005a_f200()->GetViewer()->GetWorldRayFromScreenCoords(mX, mY, origin, direction);
  float minOffset = model->GetSize() * 0.05f;

  // Dragging a whole limb across the symmetry plane: flip the ray to the block's side.
  if (mManipType == 7 || mManipType == 6) {
    if (fabsf(Dot(direction, kSPEditorForwardAxis)) < 0.8f && Length(mMouseOffset) > minOffset) {
      float blockSide = Sign1(mBlock->mPosition.x);
      float raySide = Sign1(origin.x);
      if (blockSide != raySide) {
        direction = direction * -1.0f;
        float dist = Length(origin) + Length(origin);
        origin = origin - direction * dist;
      }
    }
  }
  origin = origin + mMouseOffset;

  bool usingSymmetry = model->IsUsingSymmetry();
  mLimbStructure->SetHighlighting(true);
  if (mSymmetricLimbStructure)
    mSymmetricLimbStructure->SetHighlighting(true);
  if (mMirrorLimbStructure)
    mMirrorLimbStructure->SetHighlighting(true);
  mHighlights.clear();
  mSymmetricHighlights.clear();
  BuildHighlights(mLimbStructure->GetRootBlock(), &mHighlights, true);
  if (mSymmetricLimbStructure)
    BuildHighlights(mSymmetricLimbStructure->GetRootBlock(), &mSymmetricHighlights, true);
  if (mMirrorLimbStructure)
    BuildHighlights(mMirrorLimbStructure->GetRootBlock(), &mSymmetricHighlights, true);

  int oldSign = mManipulatingJoints[0]->SignFromBlock(true);

  switch (mManipType) {
    case 0: {
      // Limb root sliding over the body.
      cSPEditorLimbJoint_s005a_f200* joint = mLimbStructure->GetJoint(mBlock);
      float t;
      if (!IntersectRayPlane(origin, direction, cSPPlane(kSPEditorUpAxis, kSPEditorOrigin), t))
        return;
      cSPVector3_s005a_f200 planePos = GetLimbPlanePosition(mBlock);
      float s = (planePos.z - origin.z) / direction.z;
      cSPVector3_s005a_f200 hit = origin + direction * s;
      float x = hit.x;
      if (mBlock->mFlags.test(15) && usingSymmetry) {
        if (IntersectRayPlane(origin, direction, cSPPlane(kSPEditorRightAxis, kSPEditorOrigin), t)) {
          cSPVector3_s005a_f200 center = origin + direction * t;
          const cSPVector3_s005a_f200& pos = mBlock->mPosition;
          float toCenter = Length(center - pos);
          if (toCenter < Length(cSPVector3_s005a_f200(-hit.x, hit.y, hit.z) - pos) && toCenter < Length(hit - pos))
            x = 0.0f;
        }
      }
      joint->SetTargetPosition(cSPVector3_s005a_f200(x, hit.y, hit.z));
      bool pinned = mBlock->IsPinned();
      if (!mLimbStructure->ClampJoints(&mManipulatingJoints))
        mLimbStructure->ResolveJoints(&mManipulatingJoints);
      bool blocked = mLimbStructure->CheckJoints(&mManipulatingJoints);
      UpdateSymmetricJointPositions();
      int newSign = joint->GetSign(true);
      bool signChanged = false;
      if (!pinned && SignChanged(oldSign, newSign, false)) {
        RefreshJointLists();
        mLimbStructure->RefreshTargets(&mManipulatingJoints, false);
        if (mSymmetricLimbStructure)
          mSymmetricLimbStructure->RefreshTargets(&mSymmetricJoints, true);
        CopyJointsToSymmetricLimbs();
        signChanged = true;
      }
      mLimbStructure->MoveJoint(joint, joint->mTargetPosition);
      mLimbStructure->UpdatePositions();
      bool tooLong = mLimbStructure->UpdateAllLengths(false);
      if (mSymmetricLimbStructure) {
        cSPEditorLimbJoint_s005a_f200* symJoint = mSymmetricLimbStructure->GetJoint(mBlock->mSymmetricBlock);
        mSymmetricLimbStructure->MoveJoint(symJoint, MirrorPosition(joint->mTargetPosition));
        mSymmetricLimbStructure->UpdatePositions();
        mSymmetricLimbStructure->UpdateAllLengths(false);
      }
      SetOutsideBounds(tooLong || blocked);
      mLimbStructure->SetFeetTargets(false);
      mLimbStructure->UpdateBlocks();
      mLimbStructure->UpdateAnimation(0, 0);
      if (mSymmetricLimbStructure) {
        mSymmetricLimbStructure->SetFeetTargets(false);
        mSymmetricLimbStructure->UpdateBlocks();
        mSymmetricLimbStructure->UpdateAnimation(0, 0);
      }
      if (signChanged) {
        ClearSymmetricHighlights();
      } else {
        RefreshHighlights(&mHighlights);
        RefreshHighlights(&mSymmetricHighlights);
      }
      FinishUpdate();
      UpdateSkin(mBlock, mLimbStructure->GetBlocks(), mIsStacking, mSkin, 0, 0, 1, 1);
      return;
    }

    case 1:
    case 2:
    case 3: {
      // Single joint (knee, foot, hand...).
      cSPVector3_s005a_f200 target;
      if (mModifiers & 0x20) {
        // Camera-facing plane through the block.
        cSPPlane plane(-direction, mBlock->mPosition);
        float t;
        if (IntersectRayPlane(origin, direction, plane, t))
          target = origin + direction * t;
        else
          target = mBlock->mPosition;
      } else {
        cSPEditorLimbJoint_s005a_f200* joint = mLimbStructure->GetJoint(mBlock);
        cSPVector3_s005a_f200 lineStart, lineEnd;
        GetLineForJoint(mBlock, origin, direction, &lineStart, &lineEnd);
        mBestTry = PickOptimalPointOnLine(joint, lineStart, lineEnd, 400, mTries, &mWorstTry, &mBestIndex);
        if (mBadnessCalculator && mBadnessCalculator->IsEnabled()) {
          cSPVector3_s005a_f200 offset;
          if (ConstrainOffset(mBestTry.mLoc - joint->GetUpperDirection(2), &offset, 1.0f))
            mBestTry.mLoc = joint->GetUpperDirection(2) + offset;
        }
        target = mBestTry.mLoc;
      }
      int count = mManipulatingJoints.size();
      for (int i = 0; i < count; i++)
        mManipulatingJoints[i]->SetTargetPosition(target);
      bool clamped = mLimbStructure->ClampJoints(&mManipulatingJoints);
      UpdateSymmetricJointPositions();
      int newSign = mManipulatingJoints[0]->GetSign(true);
      bool signChanged = false;
      if (!mBlock->IsPinned() && SignChanged(oldSign, newSign, false)) {
        RefreshJointLists();
        mLimbStructure->RefreshTargets(&mManipulatingJoints, false);
        if (mSymmetricLimbStructure)
          mSymmetricLimbStructure->RefreshTargets(&mSymmetricJoints, true);
        CopyJointsToSymmetricLimbs();
        signChanged = true;
      }
      if (!clamped)
        mLimbStructure->ResolveJoints(&mManipulatingJoints);
      bool blocked = mLimbStructure->CheckJoints(&mManipulatingJoints);
      UpdateSymmetricJointPositions();
      bool hasFeet;
      if (mLimbStructure->GetFootCount() > 0 ||
          (mSymmetricLimbStructure && mSymmetricLimbStructure->GetFootCount() > 0) ||
          (mMirrorLimbStructure && mMirrorLimbStructure->GetFootCount() > 0)) {
        hasFeet = true;
      } else {
        hasFeet = false;
        int n = mManipulatingJoints.size();
        for (int i = 0; i < n; i++) {
          cSPEditorLimbJoint_s005a_f200* joint = mManipulatingJoints[i];
          if (joint->mJointType != 2)
            mLimbStructure->SolveJoint(joint, joint);
        }
        if (mSymmetricLimbStructure) {
          n = mSymmetricJoints.size();
          for (int i = 0; i < n; i++) {
            cSPEditorLimbJoint_s005a_f200* joint = mSymmetricJoints[i];
            if (joint->mJointType != 2)
              mSymmetricLimbStructure->SolveJoint(joint, joint);
          }
        }
        if (mMirrorLimbStructure) {
          n = mMirrorJoints.size();
          for (int i = 0; i < n; i++) {
            cSPEditorLimbJoint_s005a_f200* joint = mMirrorJoints[i];
            if (joint->mJointType != 2)
              mMirrorLimbStructure->SolveJoint(joint, joint);
          }
        }
      }
      mLimbStructure->UpdatePositions();
      bool tooLong = mLimbStructure->UpdateAllLengths(false);
      SetOutsideBounds(blocked || tooLong);
      mLimbStructure->SetFeetTargets(false);
      SetPileState(mLimbStructure->GetRootBlock(), mLimbStructure->GetBlocks());
      mLimbStructure->UpdateBlocks();
      if (mSymmetricLimbStructure) {
        mSymmetricLimbStructure->UpdatePositions();
        mSymmetricLimbStructure->UpdateAllLengths(false);
        mSymmetricLimbStructure->SetFeetTargets(false);
        SetPileState(mSymmetricLimbStructure->GetRootBlock(), mSymmetricLimbStructure->GetBlocks());
        mSymmetricLimbStructure->UpdateBlocks();
      }
      if (mMirrorLimbStructure) {
        mMirrorLimbStructure->UpdatePositions();
        mMirrorLimbStructure->UpdateAllLengths(false);
        mMirrorLimbStructure->SetFeetTargets(false);
        SetPileState(mMirrorLimbStructure->GetRootBlock(), mMirrorLimbStructure->GetBlocks());
        mMirrorLimbStructure->UpdateBlocks();
      }
      if (signChanged) {
        ClearSymmetricHighlights();
      } else {
        RefreshHighlights(&mHighlights);
        RefreshHighlights(&mSymmetricHighlights);
      }
      mLimbStructure->UpdateAnimation(0, 0);
      FinishUpdate();
      UpdateSkin(mBlock, mLimbStructure->GetBlocks(), mIsStacking, mSkin, 0, 0, 1, 1);
      if (mManipType != 2 && !hasFeet)
        mLimbStructure->Settle(mBlock);
      return;
    }

    case 4:
    case 5: {
      // Limb end (hand/foot block) being stacked onto a block or the miss plane.
      cSPEditorBlock_s005a_f200* oldParent = mBlock->mpParent;
      oldSign = mManipulatingJoints[0]->GetSign(true);
      cSPVector3_s005a_f200 stackPos, stackNormal, blockPos;
      cSPEditorBlock_s005a_f200* stackTarget = PickStackTarget(mBlock, origin, direction, SkinRef(mSkin), &stackPos, &stackNormal,
                                                    mLimbStructure->GetBlocks());
      cSPEditorBlock_s005a_f200* hitBlock = PickBlock(mBlock, mLimbStructure->GetBlocks(), origin, direction, &blockPos);
      bool notPlaced = true;
      bool useBlock = false;
      if (stackTarget) {
        if (hitBlock && Length(stackPos - origin) > Length(blockPos - origin) && !hitBlock->mFlags.test(7))
          useBlock = true;
      } else if (hitBlock) {
        useBlock = true;
      }
      bool repin = (mModifiers >> 1) & 1;
      if (useBlock && repin) {
        if (hitBlock != mBlock->mpParent) {
          SetPileState(mLimbStructure->GetRootBlock(), mLimbStructure->GetBlocks());
          RepinBlock(mBlock, mLimbStructure->GetBlocks(), hitBlock);
        }
      } else {
        if (mBlock->mFlags.test(12))
          UnpinBlock(mBlock);
        cSPVector3_s005a_f200 placePos;
        bool placed = PlaceBlockOnBody(mBlock, mLimbStructure->GetBlocks(), origin, direction, SkinRef(mSkin),
                                       &placePos, 0, 0, 1);
        notPlaced = placed;
        if (!mBlock->mpParent && (oldParent != 0 || (mIsStacking && placed)))
          GetMissPlane(mBlock, direction, &mMissPlanePosition, &mMissPlaneNormal);
        if (placed && !mBlock->mpParent)
          PlaceOnMissPlane(mBlock, origin, direction, mMissPlanePosition, mMissPlaneNormal, 1);
      }
      if (!mBlock->mpParent) {
        mBlock->SetBooleanAttribute(0xc, false);
        RecalculateLimbMissPlane();
        mManipType = 6;
      }
      int count = mManipulatingJoints.size();
      for (int i = 0; i < count; i++) {
        cSPEditorLimbJoint_s005a_f200*& joint = mManipulatingJoints[i];
        joint->SetTargetPosition(mBlock->mPosition);
      }
      mLimbStructure->ClampJoints(&mManipulatingJoints);
      count = mManipulatingJoints.size();
      for (int i = 0; i < count; i++) {
        cSPEditorLimbJoint_s005a_f200* joint = mManipulatingJoints[i];
        mLimbStructure->SolveJoint(joint, joint);
      }
      UpdateSymmetricJointPositions();
      int newSign = mManipulatingJoints[0]->GetSign(true);
      bool signChanged = false;
      if (!mBlock->IsPinned() && SignChanged(oldSign, newSign, false)) {
        RefreshJointLists();
        mLimbStructure->RefreshBlockTargets(mBlock, false);
        if (mSymmetricLimbStructure)
          mSymmetricLimbStructure->RefreshBlockTargets(mBlock->mSymmetricBlock, true);
        CopyJointsToSymmetricLimbs();
        signChanged = true;
      }
      if (mLimbStructure->GetFootCount() > 0) {
        mLimbStructure->UpdateFeetTargets();
        if (mSymmetricLimbStructure) {
          cSPEditorJointMirror mirror;
          mirror.mpTarget = mSymmetricLimbStructure;
          mirror.Mirror(mLimbStructure->mBaseJoint);
        }
      } else if (mSymmetricLimbStructure && mSymmetricLimbStructure->GetFootCount() > 0) {
        mSymmetricLimbStructure->UpdateFeetTargets();
        cSPEditorJointMirror mirror;
        mirror.mpTarget = mLimbStructure;
        mirror.Mirror(mSymmetricLimbStructure->mBaseJoint);
      }
      mLimbStructure->UpdatePositions();
      SetOutsideBounds(mLimbStructure->UpdateAllLengths(false));
      if (mSymmetricLimbStructure) {
        mSymmetricLimbStructure->UpdatePositions();
        mSymmetricLimbStructure->UpdateAllLengths(false);
      }
      mLimbStructure->SetFeetTargets(false);
      mLimbStructure->SetHandsTargets(false);
      if (mSymmetricLimbStructure) {
        mSymmetricLimbStructure->SetFeetTargets(false);
        mSymmetricLimbStructure->SetHandsTargets(false);
      }
      mLimbStructure->UpdateBlocks();
      if (mSymmetricLimbStructure)
        mSymmetricLimbStructure->UpdateBlocks();
      if (signChanged) {
        ClearSymmetricHighlights();
      } else {
        RefreshHighlights(&mHighlights);
        RefreshHighlights(&mSymmetricHighlights);
      }
      mLimbStructure->UpdateAnimation(0, 0);
      if (mSymmetricLimbStructure)
        mSymmetricLimbStructure->UpdateAnimation(0, 0);
      FinishUpdate();
      UpdateSkin(mBlock, mLimbStructure->GetBlocks(), mIsStacking, mSkin, 0, 0, 1, 1);
      mIsStacking = !notPlaced;
      return;
    }

    case 7:
      // Whole limb from its root: only with the modifier, or when the root block itself is dragged.
      if (!(mModifiers & 2) && mBlock != mLimbStructure->GetRootBlock())
        return;
      // fall through
    case 6: {
      cSPEditorBlock_s005a_f200* parent = mBlock->mpParent;
      if (parent && !parent->mFlags.test(7) && !(mModifiers & 2))
        return;
      oldSign = mManipulatingJoints[0]->GetSign(true);
      Matrix3 orientation;
      orientation.Assign(mBlock->mOrientation);
      cSPVector3_s005a_f200 stackPos, stackNormal, blockPos;
      cSPEditorBlock_s005a_f200* stackTarget = PickStackTarget(mBlock, origin, direction, SkinRef(mSkin), &stackPos, &stackNormal,
                                                    mLimbStructure->GetBlocks());
      cSPEditorBlock_s005a_f200* hitBlock = PickBlock(mBlock, mLimbStructure->GetBlocks(), origin, direction, &blockPos);
      bool placed = false;
      bool useBlock = false;
      if (stackTarget) {
        if (hitBlock && Length(stackPos - origin) > Length(blockPos - origin) && !hitBlock->mFlags.test(7))
          useBlock = true;
      } else if (hitBlock) {
        useBlock = true;
      }
      bool repin = (mModifiers >> 1) & 1;
      if (useBlock && repin) {
        if (hitBlock != mBlock->mpParent) {
          SetPileState(mLimbStructure->GetRootBlock(), mLimbStructure->GetBlocks());
          RepinBlock(mBlock, mLimbStructure->GetBlocks(), hitBlock);
          mMouseOffset = mMouseOffset + (mBlock->mPosition - blockPos);
          MessageServer()->PostMessage(0x52f180, 0x12, 0);
        }
      } else {
        if (mBlock->mFlags.test(12)) {
          UnpinBlock(mBlock);
          mMouseOffset = mOriginalMouseOffset;
        }
        SetPileState(mBlock, mLimbStructure->GetBlocks());
        cSPVector3_s005a_f200 placePos;
        placed = PlaceBlockOnBody(mBlock, mLimbStructure->GetBlocks(), origin, direction, SkinRef(mSkin), &placePos,
                                  0, 0, 1);
        if (mBlock->HasAnyBlockFlag()) {
          cSPEditorBlock_s005a_f200* block = mBlock;
          bool childFlagged = false;
          int n = block->mChildren.size();
          for (int i = 0; i < n; i++) {
            if (block->mChildren.mpBegin[i]->mFlags.test(44))
              childFlagged = true;
          }
          if (!childFlagged && block->mpParent->mFlags.test(7))
            mManipType = EditorUtils::GetFirstFootBlock(block) ? 4 : 5;
          if (mManipType != 5 && mManipType != 4)
            PlaceBlock(mBlock, 0, 1.0f, 0);
          GetEditorStateObject()->SetBool(0x3f1bf5d, false);
        } else {
          GetEditorStateObject()->SetBool(0x3f1bf5d, true);
        }
      }

      if (!mBlock->mpParent) {
        // Free-floating limb: follow the limb miss plane, capped at the placement height.
        float maxHeight = GetMaxLimbPlacementHeight();
        cSPVector3_s005a_f200 target;
        float t;
        if (IntersectRayPlane(origin, direction, cSPPlane(mLimbMissPlaneNormal, mLimbMissPlanePosition), t))
          target = origin + direction * t;
        if (target.z > maxHeight)
          target.z = maxHeight;
        int count = mManipulatingJoints.size();
        for (int i = 0; i < count; i++) {
          mManipulatingJoints[i]->mTargetPosition = target;
          mLimbStructure->SolveJoint(mManipulatingJoints[i], mManipulatingJoints[i]);
        }
        UpdateSymmetricJointPositions();
        if (mSymmetricLimbStructure) {
          int n = mSymmetricJoints.size();
          for (int i = 0; i < n; i++)
            mSymmetricLimbStructure->SolveJoint(mSymmetricJoints[i], mSymmetricJoints[i]);
        }
      } else {
        mLimbStructure->ResetJoints(false);
        if (mSymmetricLimbStructure)
          mSymmetricLimbStructure->ResetJoints(false);
      }

      cSPVector3_s005a_f200 oldTarget = mManipulatingJoints[0]->mTargetPosition;
      bool clamped = false;
      if (mBlock->mpParent)
        clamped = mLimbStructure->ClampJoints(&mManipulatingJoints);
      if (clamped) {
        cSPVector3_s005a_f200 delta = mManipulatingJoints[0]->mTargetPosition - oldTarget;
        int count = mManipulatingJoints.size();
        for (int i = 0; i < count; i++) {
          cSPEditorLimbJoint_s005a_f200*& joint = mManipulatingJoints[i];
          joint->Translate(delta);
        }
      }
      int newSign = mManipulatingJoints[0]->GetSign(true);
      UpdateSymmetricJointPositions();
      bool signChanged = false;
      if (SignChanged(oldSign, newSign, false)) {
        mLimbStructure->RefreshBlockTargets(mBlock, false);
        if (mSymmetricLimbStructure)
          mSymmetricLimbStructure->RefreshBlockTargets(mBlock->mSymmetricBlock, true);
        signChanged = true;
      }
      if (mBlock->mpParent) {
        mLimbStructure->UpdatePositions();
        if (mSymmetricLimbStructure)
          mSymmetricLimbStructure->UpdatePositions();
      }
      mLimbStructure->UpdateFeetTargets();
      bool floating = mBlock->mpParent == 0;
      mLimbStructure->UpdateAllLengths(floating);
      mLimbStructure->UpdateBlocks();
      mLimbStructure->UpdateAnimation(0, 0);
      if (mSymmetricLimbStructure) {
        mSymmetricLimbStructure->UpdateFeetTargets();
        mSymmetricLimbStructure->UpdateAllLengths(floating);
        mSymmetricLimbStructure->UpdateBlocks();
        mSymmetricLimbStructure->UpdateAnimation(0, 0);
      }
      if (signChanged) {
        ClearSymmetricHighlights();
      } else {
        RefreshHighlights(&mHighlights);
        RefreshHighlights(&mSymmetricHighlights);
      }
      FinishUpdate();
      bool stacking = !placed;
      UpdateSkin(mBlock, mLimbStructure->GetBlocks(), stacking, mSkin, 0, 0, 1, 1);
      GetEditorStateObject()->SetBlock(0x3f1bf5d, mBlock);
      mIsStacking = stacking;
      return;
    }
  }
}
}  // namespace SP

// @ 0x005b0f80
MObj::MObj()
: mChangedObject(false), mUseDeadZone(true), mMovedOutsideDeadZone(false),
      mDeadZoneSize(2.0f), mInitialX(0.0f), mInitialY(0.0f) {}

// @ 0x009cda70
float* __cdecl FUN_009cda70(float* out, const float* m)
{
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[0] = 0.0f;
    float fq = -m[6];
    float fVar2 = (float)sqrt((float)(1.0f - (float)(fq * fq)));
    out[1] = (float)atan2((double)fq, (double)fVar2);
    if (fq != 1.0f && fq != -1.0f) {
        float r = 1.0f / fVar2;
        out[0] = (float)atan2((double)(m[7] * r), (double)(m[8] * r));
        out[2] = (float)atan2((double)(m[3] * r), (double)(r * m[0]));
        return out;
    }
    out[0] = (float)atan2((double)(-m[5]), (double)(m[4]));
    out[2] = (float)atan2(0.0, 1.0);
    return out;
}

// @ 0x009cdb20
static float FUN_009cdb20(float a, float b)
{
    float res;
    if ((float)fabs((double)b) < 1.0f) {
        res = (a * b - b + 1.0f) * a;
    }
    else if (0.0f > b) {
        res = (float)(1.0 - pow((double)(1.0f - a), pow(2.0, (double)-b)));
    }
    else {
        res = (float)pow((double)a, pow(2.0, (double)b));
    }
    if (!(res > 0.0f)) return 0.0f;
    if (res > 1.0f) return 1.0f;
    return res;
}

// @ 0x009cdbe0
float __cdecl FUN_009cdbe0(float param_1, float param_2, float param_3, float param_4, float param_5)
{
    float range  = param_3 - param_2;
    float range2 = param_5 - param_4;
    if (param_1 <= param_2) param_1 = param_2;
    if (param_1 > param_3) param_1 = param_3;
    param_1 = (float)fabs((double)((param_1 - param_2) / range));
    float res = param_4;
    // 0x9cdc5a: fcompi |t| (st0) vs |range2*1e-06| (st1); jbe skips the hermite blend
    if (param_1 > (float)fabs((double)(range2 * 1e-06f)))
        res = (((((param_1 * 6.0f - 15.0f) * param_1 + 10.0f) * param_1) * param_1)
               * param_1) * range2 + param_4;
    if (range2 > 0.0f) {
        if (!(res > param_4)) res = param_4;
        if (res > param_5) res = param_5;
    }
    else {
        if (!(res > param_5)) res = param_5;
        if (res > param_4) res = param_4;
    }
    return res;
}

// @ 0x009cdce0
namespace nSPCreatureAnim {
float biasedSigmoid(float param_1, float param_2, float param_3, float param_4, float param_5, float param_6)
{
    float fVar1 = param_3 - param_2;
    if ((float)fabs((double)fVar1) <= 1e-06f)
        return (param_4 + param_5) * 0.5f;
    float fVar4 = (param_1 - param_2) / fVar1;
    float fVar2 = 0.0f;
    if (fVar4 <= 0.0f || (fVar2 = 1.0f, 1.0f < fVar4)) {
        fVar4 = fVar2;
    }
    float res;
    if (fVar4 < 1e-06f) {
        res = param_2;
    }
    else {
        res = (float)pow((double)fVar4, (double)param_6) * fVar1 + param_2;
    }
    return FUN_009cdbe0(res, param_2, param_3, param_4, param_5);
}
}  // namespace nSPCreatureAnim

// @ 0x009cddc0
static float FUN_009cddc0(float /*unused*/, float v)
{
    if (DAT_014479b0 > v)
        return -1.0f;
    if (v > DAT_014479b0)
        return 1.0f;
    return 0.0f;
}

// @ 0x009cddf0
void SA::FUN_009cddf0(int p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8)
{
    f04 = p3;
    f00 = p2;
    f08 = p4;
    f0c = p2;
    f10 = f04;
    f14 = f08;
    f18 = 0.0f;
    f1c = 0.0f;
    f20 = 0.0f;
    f24 = p5;
    f28 = p6;
    f2c = p7;
    f30 = p8;
    f34 = f24;
    f38 = f28;
    f3c = f2c;
    f40 = f30;
    f4c = 0.5f;
    i48 = 0;
    i44 = 0x47f0b3dc;
    f54 = 1.0f;
    f60 = 0.0f;
    b5d = 0;
    i68 = 0;
    i64 = 0;
    f7c = f00;
    f80 = f04;
    f84 = f08;
    f88 = f24;
    f8c = f28;
    f90 = f2c;
    f94 = f30;
    fa8 = 1.0f;
    fac = 1.0f;
    iB0 = 0;
    fB4 = 0.0f;
    fB8 = 0.0f;
    fBC = 0.0f;
    iC4 = 0;
    fC0 = 0.0f;
    iC8 = p1;
    fD0 = 0.0f;
    fD4 = 0.0f;
    fD8 = 0.0f;
    fDC = 0.0f;
    fE0 = 0.0f;
    fE4 = 0.0f;
    fE8 = 0.0f;
    fEC = 0.0f;
    fF0 = 0.0f;
    fF4 = 0.0f;
    f100 = 0.25f;
    fF8 = 1.0f;
    fFC = 1.0f;
    f104 = 0.75f;
}

// @ 0x009cdfb0
float SA::FUN_009cdfb0(float t)
{
    CurveOut loc0;
    CurveOut loc1;
    void* ra = ((cCurveKey*)((char*)i64 + 0x2c))->eval(&loc0, t);
    float a = (1.0f - f60) * *(float*)((char*)ra + 8);
    void* rb = ((cCurveKey*)((char*)i68 + 0x2c))->eval(&loc1, t);
    return *(float*)((char*)rb + 8) * f60 + a;
}

// @ 0x009ce010
void __cdecl FUN_009ce010(SA* q, float angle)
{
    float* qv = (float*)q;
    float s = sinf(angle * 0.5f);
    float c = cosf(angle * 0.5f);
    float x = qv[0], y = qv[1], z = qv[2], w = qv[3];
    qv[0] = x * c + w * 0.0f - z * 0.0f + y * s;
    qv[1] = y * c + z * 0.0f + w * 0.0f - x * s;
    qv[2] = z * c - y * 0.0f + w * s + x * 0.0f;
    qv[3] = w * c - x * 0.0f - y * 0.0f - z * s;
}

// @ 0x009ce100
float SA::FUN_009ce100(char flag)
{
    float r;
    if (flag)
        r = (DAT_01485720 - f104) + f100;
    else
        r = f104 - f100;
    return r;
}

// @ 0x009ce150
float SA::FUN_009ce150(int idx, int* ptr, float a, float b, float c)
{
    float v = ((float*)&a)[idx] + f98;
    v = v - (float)floor((double)v);

    float lo = f100;
    float hi = f104;
    bool hiEdge = (lo > v);
    bool loEdge = (v >= hi);
    bool wrapped;
    float t;
    if (hiEdge || loEdge) {
        wrapped = true;
        if (hiEdge)
            t = ((1.0f - hi) + v) / ((1.0f - hi) + lo);
        else
            t = (v - hi) / ((1.0f - hi) + lo);
    } else {
        wrapped = false;
        t = (v - lo) / (hi - lo);
    }
    if (t > 0.0f) {
        if (t > 1.0f) t = 1.0f;
    } else {
        t = 0.0f;
    }

    if (idx == 0) {
        if (wrapped)
            return atan2f(((t - 0.5f) * fD4) * 2.0f + f80, f7c);
        return atan2f(cosf(t * DAT_014479a4) * fD4 + f80, f7c);
    }
    if (idx == 1) {
        float axis = *(float*)((char*)*ptr + 0x18);
        if (wrapped)
            return atan2f(axis, ((t - 0.5f) * fD4) * 2.0f + f80);
        return atan2f(axis, cosf(t * DAT_014479a4) * fD4 + f80);
    }
    if (idx == 2) {
        if (wrapped)
            return atan2f(f84, f7c);
        return atan2f(sinf(t * DAT_014479a4) * fF4 + f84, f7c);
    }
    return 0.0f;
}

// @ 0x009ce370
float* SA::FUN_009ce370(float* out, void* ptr, float a, float b, float c)
{
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    float* pf = &f9c;
    for (int i = 0; i < 3; ++i) {
        float f = pf[i];
        out[i] = FUN_009b3c10(FUN_009ce150(i, (int*)ptr, a, b, c) - f,
                              DAT_0155145c);
    }
    return out;
}

// @ 0x009ce430
void __cdecl FUN_009ce430(float* dst, int n, const float* a, const float* b, float t)
{
    for (int i = 1; i < n; ++i)
        dst[i] = a[i] * (1.0f - t) + b[i] * t;
}

// @ 0x009ce560
void __cdecl FUN_009ce560(float* e, int n)
{
    float s = 1.0f;
    if (n > 1) {
        for (int i = 1; i < n; ++i)
            s = s - e[i];
    }
    e[0] = s;
}

// @ 0x009ce5e0
void SA::FUN_009ce5e0()
{
    f08 = 0.0f; f04 = 0.0f; f00 = 0.0f;
    f14 = 0.0f; f10 = 0.0f; f0c = 0.0f;
    f20 = 0.0f; f1c = 0.0f; f18 = 0.0f;
    f2c = 0.0f; f28 = 0.0f; f24 = 0.0f;
    f30 = 1.0f;
    f3c = 0.0f; f38 = 0.0f; f34 = 0.0f;
    f40 = 1.0f;
    f74 = 0.0f; f70 = 0.0f;
    f84 = 0.0f; f80 = 0.0f; f7c = 0.0f;
    f90 = 0.0f; f8c = 0.0f; f88 = 0.0f;
    f94 = 1.0f;
    fa4 = 0.0f; fa0 = 0.0f; f9c = 0.0f;
    fac = 0.0f; fa8 = 0.0f;
    fBC = 0.0f; fB8 = 0.0f; fB4 = 0.0f;
    fD8 = 0.0f; fD4 = 0.0f; fD0 = 0.0f;
    fE4 = 0.0f; fE0 = 0.0f; fDC = 0.0f;
}

// @ 0x009ce700
float __stdcall FUN_009ce700(float x)
{
    return (x * 0.2f) / (0.7f + x * 0.2f);
}

// @ 0x009ce720
void SA::FUN_009ce720(int* a, int* b)
{
    *a = *(int*)&f00;
    *b = *(int*)&f04;
}

// @ 0x009ce740
void SA::FUN_009ce740(float x)
{
    float v = DAT_01485720 - x * x;
    if (v > DAT_01551474) { }
    else v = DAT_01551474;
    if (v > DAT_01485720)
        v = DAT_01485720;
    f80 = v;
}

// @ 0x009ce790
void SA::FUN_009ce790(SA* src)
{
    f00 = src->f00; f04 = src->f04; f08 = src->f08; f0c = src->f0c;
    f10 = src->f10; f14 = src->f14; f18 = src->f18; f1c = src->f1c;
    f20 = src->f20; f24 = src->f24; f28 = src->f28; f2c = src->f2c;
    f30 = src->f30; f34 = src->f34; f38 = src->f38; f3c = src->f3c;
    f40 = src->f40;
    i44 = src->i44; i48 = src->i48; f4c = src->f4c;
    i50 = src->i50; f54 = src->f54; i58 = src->i58;
    b5c = src->b5c; b5d = src->b5d;
    f60 = src->f60;
    i64 = src->i64; i68 = src->i68;
    f6c = src->f6c; f70 = src->f70; f74 = src->f74; f78 = src->f78;
    f7c = src->f7c; f80 = src->f80; f84 = src->f84; f88 = src->f88;
    f8c = src->f8c; f90 = src->f90; f94 = src->f94; f98 = src->f98;
    f9c = src->f9c; fa0 = src->fa0; fa4 = src->fa4; fa8 = src->fa8;
    fac = src->fac;
    iB0 = src->iB0;
    fB4 = src->fB4; fB8 = src->fB8; fBC = src->fBC; fC0 = src->fC0;
    iC4 = src->iC4; iC8 = src->iC8;
    fCC = src->fCC; fD0 = src->fD0; fD4 = src->fD4; fD8 = src->fD8;
    fDC = src->fDC; fE0 = src->fE0; fE4 = src->fE4; fE8 = src->fE8;
    fEC = src->fEC; fF0 = src->fF0; fF4 = src->fF4; fF8 = src->fF8;
    fFC = src->fFC; f100 = src->f100; f104 = src->f104;
}

// @ 0x009cea00
void __cdecl FUN_009cea00(SA* begin, SA* end)
{
    if (begin == end)
        return;
    for (SA* p = begin + 1; p != end; ) {
        char key[0x108];
        p->FUN_009ce790((SA*)key);
        SA* j = p;
        if (p != begin) {
            do {
                SA* q = j - 1;
                char pv[0x108];
                char kc[0x108];
                q->FUN_009ce790((SA*)pv);
                ((SA*)key)->FUN_009ce790((SA*)kc);
                if (*(float*)(kc + 0xac) <= *(float*)(pv + 0xac))
                    break;
                j->FUN_009ce790(q);
                j = q;
            } while (j != begin);
        }
        j->FUN_009ce790((SA*)key);
        p = p + 1;
    }
}

// @ 0x009ceab0
void __cdecl FUN_009ceab0(SA* begin, SA* end)
{
    for (SA* p = begin; p != end; p = p + 1) {
        char key[0x108];
        p->FUN_009ce790((SA*)key);
        SA* j = p;
        for (;;) {
            SA* q = j - 1;
            char pv[0x108];
            char kc[0x108];
            q->FUN_009ce790((SA*)pv);
            ((SA*)key)->FUN_009ce790((SA*)kc);
            if (*(float*)(kc + 0xac) <= *(float*)(pv + 0xac))
                break;
            j->FUN_009ce790(q);
            j = q;
        }
        j->FUN_009ce790((SA*)key);
    }
}

// @ 0x009ceb50
SA* __cdecl FUN_009ceb50(SA* a, SA* b, SA* c)
{
    if (a->fac <= b->fac) {
        if (a->fac > c->fac)
            return a;
        if (b->fac > c->fac)
            return c;
        return b;
    } else {
        if (b->fac > c->fac)
            return b;
        if (a->fac <= c->fac)
            return a;
        return c;
    }
}

// @ 0x009ced30
void __cdecl FUN_009ced30(SA* base, int low, int index, SA value)
{
    char key[0x108];
    int parent = (index - 1) >> 1;
    while (index > low) {
        char pv[0x108];
        (&value)->FUN_009ce790((SA*)key);
        base[parent].FUN_009ce790((SA*)pv);
        if (*(float*)(pv + 0xac) <= *(float*)(key + 0xac))
            break;
        base[index].FUN_009ce790(&base[parent]);
        index = parent;
        parent = (index - 1) >> 1;
    }
    base[index].FUN_009ce790(&value);
}

// @ 0x009cede0
namespace nSPCreatureAnim {
vector_3_s009c_ede0* dynamics_foot_s009c_ede0::SampleBlendPos(vector_3_s009c_ede0* out, float t)
{
    float f = ratio;
    float g = 1.0f - f;

    float a[0x11];
    float b[0x11];
    ((curve_sample_a*)((char*)curve_68 + 4))->Sample(a, t);
    float ax = a[2] * f, ay = a[3] * f, az = a[4] * f;
    ((curve_sample_a*)((char*)curve_64 + 4))->Sample(b, t);

    out->x = b[2] * g + ax;
    out->y = b[3] * g + ay;
    out->z = b[4] * g + az;
    return out;
}
}  // namespace nSPCreatureAnim

// @ 0x009ceec0
namespace nSPCreatureAnim {
vector_3_s009c_ede0* dynamics_foot_s009c_ede0::SampleBlendRot(vector_3_s009c_ede0* out, float t)
{
    float f = ratio;

    float a[0x16];
    float b[0x16];
    curve_sample_b* ca = (curve_sample_b*)((char*)curve_68 + 0x18);
    curve_sample_b* cb = (curve_sample_b*)((char*)curve_64 + 0x18);
    ca->Sample(a, t);
    cb->Sample(b, t);

    float q[9];
    FUN_0099cc70(q, b + 2, a + 2, f);

    float e4 = q[0], e0 = q[1], dc = q[2], d8 = q[3];
    float m[9];
    m[0] = 1.0f - (dc * dc + e0 * e0) * 2.0f;
    m[1] = (e4 * e0 - d8 * dc) * 2.0f;
    m[2] = (d8 * e0 + dc * e4) * 2.0f;
    m[3] = (d8 * dc + e4 * e0) * 2.0f;
    m[4] = 1.0f - (dc * dc + e4 * e4) * 2.0f;
    m[5] = (dc * e0 - d8 * e4) * 2.0f;
    m[6] = (dc * e4 - d8 * e0) * 2.0f;
    m[7] = (d8 * e4 + dc * e0) * 2.0f;
    m[8] = 1.0f - (e0 * e0 + e4 * e4) * 2.0f;

    FUN_009cda70((float*)out, m);
    return out;
}
}  // namespace nSPCreatureAnim

// @ 0x009cf080
namespace nSPCreatureAnim {
void dynamics_foot_s009c_ede0::SetBendAngle(gait_src* p, float a, float b)
{
    float v;

    if (DAT_015515dc != 0 && curve_64 != 0 && curve_68 != 0) {
        double tv = (double)(phase_offset - phase * 0.5f);
        float frac = (float)(tv - floor(tv));
        float r = FUN_009cdfb0(frac * DAT_0155125c);
        v = r * p->f_dc + (1.0f - p->f_dc) * 0.5f;
    } else {
        float f4 = 0.5f - (p->f_dc * p->f_70) * p->f_68;
        f4 = clampf(f4, 0.0f, 1.0f);

        float f1 = p->f_6c;
        float f5 = p->f_74 * f1;
        float f3 = (1.0f - f1) * p->f_78 + f1;
        float f6 = 0.0f;
        if (f5 < a && a < f3) {
            float t = 0.0f;
            if (f1 <= a) {
                if (1e-6f < f3 - f1)
                    t = (f3 - a) / (f3 - f1);
            } else {
                if (1e-6f < f1 - f5)
                    t = (a - f5) / (f1 - f5);
            }
            float s = (float)sin((double)(t * (float)1.5707964));
            f6 = s * s;
        }
        float h = fabsf(b) * 0.31830987f + 0.5f;
        v = (1.0f - f6) * h + f6 * f4;
    }

    if (fabsf(v) < 1e-6f)
        v = 0.0f;
    f_44 = 123239.71875f;                     // bits 0x47f0b3dc: stored as an immediate by the original
    f_48 = 0.0f;
    f_4c = v;
    f_54 = 1.0f;
}
}  // namespace nSPCreatureAnim

// @ 0x009cf240
namespace nSPCreatureAnim {
void dynamics_foot_s009c_ede0::AdvancePhase(float dt)
{
    double tv = (double)(f_6c + dt);
    float frac = (float)((f_6c + dt) - floor(tv));

    bool bUp = phl > frac;
    bool bDown = frac >= phu;
    bool wrap = bUp || bDown;

    if (wrap) {
        int st = creature->f_15b8;
        if (st == 0 || st == 2)
            return;
        motion = 3;
        return;
    }

    if (creature == 0)
        return;

    if (creature->f_15bc != creature->f_15b8 && creature->f_15bc == 0) {
        float r = FUN_009ce100(false);
        float v = (frac - phl) / r;
        float c = clampf(v, 0.0f, 1.0f);
        motion = (c > DAT_0155147c) ? 0 : 3;
    }

    int st = creature->f_15b8;
    if (st != 0 && st != 2)
        return;

    float dx = pos[0] - rest_angle[0];
    float dy = pos[1] - rest_angle[1];
    float dxy = (float)sqrt((double)(dx * dx + dy * dy));
    if (dxy < f_ac * DAT_01551478 && fabsf(pos[2] - rest_angle[2]) < 1e-6f) {
        motion = 0;
        return;
    }
    motion = 3;
}
}  // namespace nSPCreatureAnim

// @ 0x009cf3c0
namespace nSPCreatureAnim {
void dynamics_foot_s009c_ede0::UpdateStance()
{
    creature_body_static_data_s009c_ede0* body =
        *(creature_body_static_data_s009c_ede0**)((char*)creature->bodies + index * 0x2bc);

    float ca = 1.0f;
    if (DAT_01551254 != 0 && body->f_434 > 1e-6f) {
        ca = (body->f_43c / body->f_434) * (DAT_0155148c - DAT_01551488) + DAT_01551488;
        ca = clampf(ca, 0.0f, 1.5f);
    }

    float cb = 1.0f;
    if (DAT_01551255 != 0 && body->f_434 > 1e-6f) {
        float r = body->f_438 / body->f_434;
        if (r > DAT_01551484)
            cb = ((r - DAT_01551484) / (1.0f - DAT_01551484)) * DAT_01550a10 + 1.0f;
    }

    if (DAT_01551256 != 0 && body->f_434 > 1e-6f) {
        float inv = 1.0f / body->f_434;
        float p8 = body->f_43c * inv;
        float p10 = (body->f_438 * inv - 0.75f) * 4.0f;
        p10 = clampf(p10, 0.0f, 1.0f);
        float pw = (float)pow((double)(1.0f - p8), *(double*)&DAT_0166c7d0);
        p8 = clampf(pw, 0.0f, 1.0f);
        f_c0 = (p10 <= p8) ? p10 : p8;
    }

    creature_static_data_s009c_ede0* sd = creature->static_data;

    float t1 = sd->leg_len_a(1.0f - f_c0, body->bidx, body->anim_group);
    float t2 = sd->leg_len_b(1.0f - f_c0, body->bidx, body->anim_group);

    float d = body->f_434 * body->f_434 - t1;
    float half2 = (float)(0.25 * sqrt((double)t2));
    float val = ((float)sqrt((double)(d > 0.0f ? d : 0.0f)) - (float)sqrt((double)t2)) * cb * ca;
    val = val + val;
    f_ac = (val <= half2) ? half2 : val;

    float p10b = f_c0 * DAT_01551480 + 1.0f;
    float u1 = sd->leg_len_c(1.0f - f_c0, body->bidx, body->anim_group);
    float u2 = sd->leg_len_d(1.0f - f_c0, body->bidx, body->anim_group);

    float half4 = (float)(sqrt((double)u2) * 0.25);
    float d2 = body->f_434 * body->f_434 - u1;
    float val2 = ((float)sqrt((double)d2) - (float)sqrt((double)u2)) * p10b * cb * ca;
    val2 = val2 + val2;
    f_a8 = (val2 <= half4) ? half4 : val2;
}
}  // namespace nSPCreatureAnim

// @ 0x009cf740
namespace nSPCreatureAnim {
float dynamics_foot_s009c_ede0::CalcBendBlendFactor(void* pRoot, float t)
{
    creature_static_data_s009c_ede0* sd = creature->static_data;
    creature_body_static_data_s009c_ede0* bd =
        (creature_body_static_data_s009c_ede0*)((char*)sd->bodies_begin + index * 0x468);

    float blend = GetAnimationBlend(bd);

    float fv;
    if ((bd->flags_154 & 8) != 0)
        fv = rest_angle[2];
    else
        fv = ((creature_body_static_data_s009c_ede0*)((char*)sd->bodies_begin +
                                           bd->anim_group * 0x468))->rest_cz;

    float ratio = (t * 0.2f) / (0.7f + t * 0.2f);
    return ((ratio * (fv + blend)) * *(float*)((char*)pRoot + 0x60)) * 0.5f;
}
}  // namespace nSPCreatureAnim

// @ 0x009cf7d0
namespace nSPCreatureAnim {
float dynamics_foot_s009c_ede0::GetDeltaCoordinate(int idx, void* pRoot, vector_3_s009c_ede0 v)
{
    float f = (&v.x)[idx] + phase_offset;
    float frac = f - (float)floor((double)f);

    bool bUp = phl > frac;
    bool bDown = frac >= phu;
    bool wrap = bUp || bDown;

    float num, den;
    if (bUp) {
        num = (1.0f - phu) + frac;
        den = (1.0f - phu) + phl;
    } else if (bDown) {
        num = frac - phu;
        den = (1.0f - phu) + phl;
    } else {
        num = frac - phl;
        den = phu - phl;
    }

    float r = clampf(num / den, 0.0f, 1.0f);

    if (idx == 0) {
        float s = (float)sin((double)(r * 3.1415927f)) * rest_angle[0];
        return wrap ? -s : s;
    }
    if (idx == 1) {
        if (!wrap)
            return (float)cos((double)(r * 3.1415927f)) * turn;
        return ((r - 0.5f) * turn) * 2.0f;
    }
    if (idx == 2) {
        float u = (1.0f - phase) * 0.63661975f;
        float c1 = -(DAT_0155149c * u);
        float c2 = (1.0f - u) * DAT_0155149c;
        float pp = (frac >= 0.5f) ? (1.0f - frac) : frac;
        if (DAT_015515dc != 0 && curve_64 != 0 && curve_68 != 0)
            return nSPCreatureAnim_biasedSigmoid(pp, DAT_0166c67c, DAT_01551494, c1, c2,
                                                 1.0f - DAT_01551498 * v.w);
        float l2 = (float)(log((double)(phase * 0.5f)) / 0.6931471805599453);
        float b = nSPCreatureAnim_biasedSigmoid(
            pp, DAT_0166c67c, DAT_01551494, c1, c2,
            (float)((double)DAT_0166c7d0 / (0.6931471805599453 * (double)l2)));
        double x = (double)b * DAT_01551470;
        double y = log(sqrt(x * x + 1.0) + x);
        return (float)((y / (double)DAT_01551470) * (double)DAT_01551490);
    }
    return 0.0f;
}
}  // namespace nSPCreatureAnim

// @ 0x009cfa90
namespace nSPCreatureAnim {
vector_3_s009c_ede0* dynamics_foot_s009c_ede0::CalcDeltaRootPosition(vector_3_s009c_ede0* out, void* pRoot, vector_3_s009c_ede0 v)
{
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = 0.0f;
    for (int i = 0; i < 3; ++i)
        (&out->x)[i] += GetDeltaCoordinate(i, pRoot, v);
    return out;
}
}  // namespace nSPCreatureAnim

// @ 0x009cfb00
namespace nSPCreatureAnim {
void foot_pair::BlendFeet(float* outPos, float* outQuat, dynamics_foot_s009c_ede0* footA, dynamics_foot_s009c_ede0* footB, float w, float w2, float* inQuat)
{
    creature_body_instance_data_s009c_ede0* ba =
        (creature_body_instance_data_s009c_ede0*)((char*)footA->creature->bodies + footA->index * 0x2bc);
    float f2 = f_24;
    float f3 = ba->rest_y;
    float f10 = 1.0f - f_24;
    creature_body_instance_data_s009c_ede0* bb =
        (creature_body_instance_data_s009c_ede0*)((char*)footB->creature->bodies + footB->index * 0x2bc);
    float f4 = bb->rest_y;
    float f5 = bb->rest_z;
    float f12 = ba->rest_z;

    outPos[0] = ba->rest_x * f10 + bb->rest_x * f2;
    outPos[1] = f3 * f10 + f4 * f2;
    outPos[2] = f12 * f10 + f5 * f2;

    creature_body_static_data_s009c_ede0* bd = ref->body;
    outPos[2] = (f_28 * f_28) * w + bd->rest_cz;

    float qx = bd->q_118;
    float qy = bd->q_11c;
    float qw = bd->q_120;
    float qz = bd->q_124;

    float ang = (float)atan2(((f_2c / w2) * f_28 * w) * 6.2831855f, 1.0f);
    float s = (float)sin((double)(ang * 0.5f));
    float c = (float)cos((double)(ang * 0.5f));

    float i0 = inQuat[0] * s;
    float i1 = inQuat[1] * s;
    float i2 = inQuat[2] * s;

    outQuat[0] = ((qx * c + qz * i0) - qy * i2) + qw * i1;
    outQuat[1] = ((qy * c + qx * i2) + qz * i1) - qw * i0;
    outQuat[2] = ((qz * i2 - qx * i1) + qw * c) + qy * i0;
    outQuat[3] = ((qz * c - qx * i0) - qy * i1) - qw * i2;
}
}  // namespace nSPCreatureAnim

// @ 0x009cfd40
void Host40::FUN_009cfd40(float* dir, void* a3, float dt)
{
    SA_s009c_fd40* b = f4;
    if (b->f48 < dt) {
        dt = dt - b->f48;
        b->f4c = dt;
        float c = ((Inner70*)b->p04)->c;
        float v[3];
        v[0] = dir[0] * c;
        v[1] = dir[1] * c;
        v[2] = dir[2] * c;
        b->Integrate(dt, v, a3);
    }
}

// @ 0x009cfdc0
void HostBC::FUN_009cfdc0(float* w, float* h, float* minX, float* maxX, float* minY, float* maxY)
{
    *minX = g_1e6;
    *maxX = g_m1e6;
    *minY = g_1e6;
    *maxY = g_m1e6;
    uint n = (uint)((char*)end - (char*)begin) >> 2;
    for (uint i = 0; i < n; i++) {
        SA_s009c_fd40* e = begin[i];
        float x = e->f7c;
        float y = e->f80;
        if (x > *maxX) *maxX = x;
        if (x < *minX) *minX = x;
        if (y > *maxY) *maxY = y;
        if (y < *minY) *minY = y;
    }
    *w = *maxX - *minX;
    *h = *maxY - *minY;
    if (*w < 0.01f || (n == 2 && *w < *h))
        *w = 0.0f;
    if (*h < 0.01f || (n == 2 && *h < *w))
        *h = 0.0f;
}

// @ 0x009d00a0
void HostD::FUN_009d00a0(float* out, Param0* p)
{
    float ax = 0.0f, ay = 0.0f, az = 0.0f;
    uint n = (uint)((char*)end - (char*)begin) >> 2;
    for (uint i = 0; i < n; i++) {
        SA_s009c_fd40* e = begin[i];
        float buf[3];
        float* r = e->FA90(buf, this, p->f18, p->f14, p->f10, p->f24);
        ax = ax + r[0];
        ay = ay + r[1];
        az = az + r[2];
    }
    if (n < 2) {
        int m = (p->f50 - p->f4c) / 0x38;
        if (m >= 2) {
            ax = g_h05 * ax;
            ay = g_h05 * ay;
            az = g_h05 * az;
        }
    } else {
        float inv = (float)(1.0 / (double)(int)n);
        float f = 1.0f - f34 * g_09;
        ax = ax * inv;
        ay = ay * inv;
        az = az * inv;
        ax = ax * f;
        ay = ay * f;
        az = az * f;
    }
    float k = g_08;
    float ik = 1.0f - k;
    ax = ax * ik;
    ay = ay * ik;
    az = az * ik;
    f18 = f18 * k + ax;
    f1c = f1c * k + ay;
    f20 = f20 * k + az;
    out[0] = f18;
    out[1] = f1c;
    out[2] = f20;
}

// @ 0x009d0a40
float* HostF::FUN_009d0a40(float* out, Param0* p)
{
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    float a = p->f30, b = p->f34, c = p->f38;
    uint n = (uint)((char*)end - (char*)begin) >> 2;
    for (uint i = 0; i < n; i++) {
        SA_s009c_fd40* e = begin[i];
        float buf[3];
        float* r = e->F370(buf, this, a, b, c);
        out[0] = out[0] + r[0];
        out[1] = out[1] + r[1];
        out[2] = out[2] + r[2];
    }
    return out;
}

// @ 0x009d24c0
void Layout::BuildStops(int n, void* a2, void* a3, void* a4, int32_t* a5)
{
    if (n > 1)
    {
        float w[4];
        float t = (float)(5 - *a5) * 0.2f;
        if (*a5 != 0)
            *a5 = *a5 - 1;
        FUN_009ce430(w, n);
        FUN_009ce560(w, n);
        uint8_t* base = (uint8_t*)a4 + 8;
        BeginGradient(base);
        for (int i = 0; i < n; ++i)
        {
            float v = w[i];
            if (1e-6f <= fabsf(v))
                AddStop(v, base + i * 0xb4);
        }
        EndGradient(base);
    }
    else
    {
        SetupFrom((Src*)a4);
    }
}

// @ 0x009d3840
float Locomotion::GetTurnFactor(Vec3* v)
{
    float vlen = Sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    float slen = Sqrt(mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y + mVelocity.z * mVelocity.z);
    extern const float kFactorA;   // 0x15514f0
    extern const float kFactorB;   // 0x15514f4
    extern const float kFactorC;   // 0x15514f8
    extern const float kFactorD;   // 0x15514fc
    float k = kFactorA;
    if ((slen * vlen) * 0.5f < (mVelocity.y * v->y + mVelocity.z * v->z) + v->x * mVelocity.x)
        k = kFactorB;
    // read the two components before the call so `this` (ecx) need not survive the call
    float vx = mVelocity.x;
    float vy = mVelocity.y;
    float f = FUN_009cdbe0(slen, 0.0f, kFactorD, kFactorC * k, 0.0f) * vlen;
    float ang = Atan2(vx, vy);
    float c = Cos(ang) * (f + 1.0f);
    float s = (f * 1.2f + 1.0f) * Sin(ang);
    return Sqrt(c * c + s * s);
}

// @ 0x009d40c0
void adjust_heap(SA_s009d_3950* first, int topPosition, int heapSize, int position, SA_s009d_3950 value, SAGreater compare)
{
    int childPosition = (2 * position) + 2;
    while (childPosition < heapSize) {
        if (compare(first[childPosition], first[childPosition - 1]))
            --childPosition;
        first[position] = first[childPosition];
        position = childPosition;
        childPosition = (2 * position) + 2;
    }
    if (childPosition == heapSize) {
        first[position] = first[childPosition - 1];
        position = childPosition - 1;
    }
    promote_heap(first, topPosition, position, value, compare);
}

// @ 0x009d4230
void pop_heap(SA_s009d_3950* first, SA_s009d_3950* last, SAGreater compare)
{
    const SA_s009d_3950 tempBottom(*(last - 1));
    *(last - 1) = *first;
    adjust_heap(first, 0, (int)(last - first - 1), 0, tempBottom, compare);
}

// @ 0x009d42b0
void AnimDyn::FUN_009d42b0(Obj2* p)
{
    if (DAT_015515dc == 0 || f64 == 0.0f || f68 == 0.0f)
        fF8 = cosf((1.0f - p->f88) * 1.5707964f);
    else
        fF8 = 0.0f;

    float half = fF8 * -0.5f;
    float t    = f78;
    fE4 = t * (p->fb0 * half);
    fDC = t * (p->fa8 * half);
    fE0 = t * (p->fac * half);
    fFC = 1.0f;
    fEC = (p->fb4 * t) * -0.5f;

    if (DAT_015515dc == 0 || f64 == 0.0f || f68 == 0.0f) {
        f18 = 0.0f;
        f1c = 0.0f;
        f20 = 0.0f;
        return;
    }

    float    l20  = f80;
    float    f84u = f84;
    vector_3 out;
    SampleBlendPos(&out, 0.0f);                                     // 0x009cede0

    float d = (float)((GaitBlk*)((char*)pC8 + 0x15b8))->FUN_009d3530();  // 0x009d3530
    float e = CalcBendBlendFactor(p, d);                            // 0x009cf740
    fF4  = e;
    f84u = e * out.z + f84u;

    float f15 = p->ff8;
    float s   = 1.0f;
    if (DAT_01551256 != 0) {
        // the first argument is the pose length, not f7c (the retail reloads it from
        // that local's slot, which still holds the 0x009d3530 result here)
        float r = FUN_009cdbe0(d, 0.0f, DAT_0155150c, 0.0f, 1.0f);  // 0x009cdbe0
        s = 1.0f - r * fC0;
    }

    // f7c is read only now: the calls above may write it, so the retail reloads it here
    float x  = f7c;
    float sg = (x < 1e-06f) ? -1.0f : ((x > 1e-06f) ? 1.0f : 0.0f);
    float xa = ((x - f15) * p->f84) * s + f15;
    xa = (sg * e * out.x) + xa;

    int* vec = (int*)((char*)pC8 + 0x15dc);
    if (vec != 0 && (vec[1] - vec[0]) / 0x108 == 2) {
        float* tbl = (float*)(*(int*)pC8 + 0x384 + i58 * 0x468);
        float  B   = tbl[0x4f];                                 // +0x13c
        float  A   = tbl[0x4e];                                 // +0x138
        float  fv2 = fabsf(f7c) - A;
        if (fv2 > 1e-06f && B / fv2 <= 1.0f) {
            float r = LengthSqVec3(&fD0);                           // 0x009a49b0
            if (DAT_01551258 < r) {
                float sg2 = FUN_009cddc0_s009d_3950(fv2, f7c);                 // 0x009cddc0
                float bf  = fD0;
                if (fv2 > 1e-06f)
                    bf = (bf / fv2) * sg2;
                if (bf <= -1.0f)
                    bf = -1.0f;
                else if (bf > 1.0f)
                    bf = 1.0f;
                l20 = l20 - ((bf * DAT_01551508) * (fabsf(fD0) / sqrtf(r))) * B;
            }
        }
    }

    float X  = fD0 * out.y + xa;
    float Y  = fD4 * out.y + l20;
    float Z  = fD8 * out.y + f84u;
    float sn = sinf(fEC);
    float cs = cosf(fEC);
    f18 = f00 - (cs * X - sn * Y);
    f1c = f04 - (cs * Y + sn * X);
    f20 = f08 - Z;
}

// @ 0x009d46d0
void Cam::UpdateOrbit(Params* p)
{
    if (g_15515dc && p64 && p68) {
        Vec3 out;
        sub_9cede0(&out, (1.0f - f78) * g_155125c);
        float ex = d.x * out.x;
        float ey = d.y * (out.y - -1.0f);
        py = ey;
        pz = d.z * out.z;
        px = ex;
        float s = sin(fec);
        float c = cos(fec);
        px = ex * c + ey * s;
        py = ey * c - ex * s;
        pz = pz;
    }

    float phaseA = EasePhase(p->f94);
    float phaseB = EasePhase(p->f90);

    double ang = ((p->f88 + 1.0f) * 0.5f) * 3.1415927;
    float lift = (float)(cos(ang) * p->f88) * phaseA;
    float swerve = -((float)(sin(ang) * p->f88) * phaseB);

    float extFlag = fabs(obj->f161c) * g_15514e0;
    float extPos = sqrt(obj->f1604 * obj->f1604 + obj->f1608 * obj->f1608 +
                        obj->f160c * obj->f160c);
    float extent = (extFlag <= extPos) ? extPos : extFlag;
    float radius = sub_9cf740(p, extent);
    ff4 = radius;

    swerve = p->f98 * lift + swerve;

    float halfTurn = cos(p->f88 * 1.5707964f);
    float scale = (1.0f / (f104 - f100)) * p->fa4;
    fb4.x = (d.x * swerve) * scale;
    fb4.y = (d.y * swerve) * scale;
    fb4.z = (d.z * swerve + (radius / (1.0f - halfTurn)) * lift) * scale;
}

// @ 0x009d49b0
void Cam::Update(Params* p, int unused, float t)
{
    (void)unused;
    float v1c, v20, v24;
    if (g_15515dc && p64 && p68) {
        v1c = f7c; v20 = f80; v24 = f84;
        Vec3 out;
        sub_9cede0(&out, (1.0f - f78) * g_155125c * t);
        float ext = ((ExtentSrc*)obj->ext)->sub_9d3530();
        float r = sub_9cf740(p, ext);
        ff4 = r;
        float f7s = f7c;
        v24 = r * out.z + v24;
        float s = (1e-6f > f7c) ? -1.0f : ((f7c > 1e-6f) ? 1.0f : 0.0f);
        float fx = s * r * out.x + v1c;
        float mod = 1.0f;
        if (g_1551256)
            mod = 1.0f - FUN_009cdbe0(ext, 0.0f, g_155151c, 0.0f, 1.0f) * fc0;
        float pf8 = p->ff8;
        v1c = (fx - pf8) * p->f84 * mod + pf8;
        Arr108* arr = &obj->arr;
        if (arr && ((int)(arr->e - arr->b)) / 0x108 == 2) {
            Rec* rec = obj->q->recs + idx;
            float r13c = rec->f13c;
            float dd = fabs(f7s) - rec->f138;
            if (dd > 1e-6f) {
                float q = r13c / dd;
                if (q <= 1.0f) {
                    float l2 = FUN_009a49b0(&d);
                    if (l2 > g_1551258) {
                        float xx = d.x;
                        float w = (float)(fabs((double)xx) / sqrt((double)l2));
                        float sg = Sign(f7s);
                        if (dd > 1e-6f) sg = xx / dd * sg;
                        if (!(sg > -1.0f)) sg = -1.0f;
                        else if (sg > 1.0f) sg = 1.0f;
                        v20 = v20 - sg * g_1551518 * w * r13c;
                    }
                }
            }
        }
        double c = cos((double)(t * 3.1415927f));   // stays in st0 (not rounded to float) in the original
        float dpos = out.y - ff8;
        off.y = d.y * dpos + off.y;
        off.x = dpos * d.x + off.x;
        off.z = off.z + d.z * dpos;
        ff8 = out.y;
        fec = (float)((c - ffc) * fe8 + fec);
        float v = *(volatile float*)&fec;   // reloaded from memory (rounded to float) for sin/cos
        ffc = (float)c;
        float sn = (float)sin((double)v);
        float cs = (float)cos((double)v);
        float ox = off.x + v1c;
        float oy = off.y + v20;
        float oz = off.z + v24;
        float vt = v * t;
        float it = 1.0f - t;
        x = px * it + (cs * ox - sn * oy);
        y = py * it + (cs * oy + sn * ox);
        z = pz * it + oz;
        ff0 = ff0 * it + vt;
    } else {
        v1c = f7c; v20 = f80; v24 = f84;
        float a1 = Bias(t, p->f90);
        float p88 = p->f88;
        float a2 = Bias(t, p->f94);
        float sA = (float)sin((double)(((a2 - 0.5f) * p88 + 0.5f) * 3.1415927f));
        float cB = (float)cos((double)(((a1 - 0.5f) * p88 + 0.5f) * 3.1415927f));
        float o2c = cB + p->f98 * sA;
        float ca = (float)cos((double)(a1 * 3.1415927f));
        float ext2;
        {
            Obj* o = obj;
            float a = (float)fabs((double)o->f161c) * g_15514e0;
            float len = (float)sqrt((double)(o->f1604 * o->f1604 + o->f1608 * o->f1608 + o->f160c * o->f160c));
            ext2 = (a > len) ? a : len;
        }
        float r = sub_9cf740(p, ext2);
        ff4 = r;
        float c88 = (float)cos((double)(p88 * 1.5707964f));
        float q = (sA - c88) / (1.0f - c88) * r;
        v24 = v24 + q;
        float s = (1e-6f > v1c) ? -1.0f : ((v1c > 1e-6f) ? 1.0f : 0.0f);
        float p80 = p->f80;
        float e;
        if (!(p80 < t))
            e = (float)sin((double)(g_1551458 / p80 * t));
        else
            e = (float)cos((double)((t - p80) / (1.0f - p80) * g_1551458));
        float vx = p->f7c * e * e * s * q + v1c;
        float mod = 1.0f;
        if (g_1551256)
            mod = 1.0f - FUN_009cdbe0(ext2, 0.0f, g_1551514, 0.0f, 1.0f) * fc0;
        float pf8 = p->ff8;
        vx = (vx - pf8) * p->f84 * mod + pf8;
        float dpos = o2c - ff8;
        off.x = dpos * d.x + off.x;
        off.y = d.y * dpos + off.y;
        off.z = off.z + d.z * dpos;
        ff8 = o2c;
        Arr108* arr = &obj->arr;
        if (arr && ((int)(arr->e - arr->b)) / 0x108 == 2) {
            Rec* rec = obj->q->recs + idx;
            float r13c = rec->f13c;
            float dd = fabs(f7c) - rec->f138;
            if (dd > 1e-6f) {
                float qq = r13c / dd;
                if (qq <= 1.0f) {
                    if (fabs(d.x) > fabs(d.y)) {
                        float sg = Sign(f7c);
                        if (dd > 1e-6f) sg = d.x / dd * sg;
                        if (!(sg > -1.0f)) sg = -1.0f;
                        else if (sg > 1.0f) sg = 1.0f;
                        v20 = v20 - sg * r13c * g_1551510;
                    }
                }
            }
        }
        float v = (ca - ffc) * fe8 + fec;
        ffc = ca;
        fec = v;
        float sn = (float)sin((double)v);
        float cs = (float)cos((double)v);
        float oz = (off.z + v24) * t;
        float ox = off.x + vx;
        float oy = off.y + v20;
        float vt = v * t;
        float it = 1.0f - t;
        float X = cs * ox - sn * oy;
        float Y = cs * oy + sn * ox;
        x = X * t + x * it;
        y = Y * t + y * it;
        z = oz + z * it;
        ff0 = ff0 * it + vt;
    }
}

// @ 0x009d52f0
void Cam::UpdateSpin(Params* p, float step, float blend, float spinRate, float driveX, float driveY, float driveZ)
{
    float scale = obj->f1638;
    float spin = (scale * step) * spinRate;
    float s = sin(spin);
    float c = cos(spin);

    float ox = px;
    float oy = py;
    px = (py * s + px * c) - (driveX * step) * scale;
    py = (py * c - ox * s) - (driveY * step) * scale;
    pz = f84 - (driveZ * step) * scale;

    float damp = 1.0f;
    if (g_166c6b1)
        damp = 0.0f;
    if (g_166c6b0)
        damp = 1.0f;
    if (!g_166c6b1 && !g_166c6b0) {
        static const float s_spinMin = 0.349f;
        static const float s_spinMax = 1.395f;
        damp = FUN_009cdbe0(fabs(ff0), s_spinMin, s_spinMax, 1.0f, 0.0f);
    }
    ff0 = ff0 - damp * spin;

    if (g_15515dc && p64 && p68) {
        Vec3 out;
        float one = 1.0f;
        sub_9cede0(&out, (one - (one - blend) * f78) * g_155125c);

        float ext = ((ExtentSrc*)obj->ext)->sub_9d3530();
        float radius = sub_9cf740(p, ext);
        ff4 = radius;

        x = x - px;
        y = y - py;
        z = z - pz;

        float sign;
        if (1e-6f <= f7c) {
            if (f7c <= 1e-6f)
                sign = 0.0f;
            else
                sign = 1.0f;
        } else {
            sign = -1.0f;
        }
        out.x = (radius * sign) * out.x;

        float fy = ((out.y - blend * 2.0f) + 1.0f) * d.y;
        py = fy * c - out.x * s;
        pz = pz;
        float fx = out.x * c + fy * s;
        px = fx;
        x = fx + x;
        y = py + y;
        z = (out.z * ff4 + pz) + z;
    }
}

// @ 0x009d5600
void __thiscall Ent::Fn5600(Ent* p, float a)
{
    Q4* v24 = &this->v24;
    *v24 = q88;

    char* o2 = (char*)o_c8;
    if (*(u8*)(*(char**)o2 + 0x3f5) != 0) return;
    void* arr = *(void**)(o2 + 0x2e4);
    void* q = *(void**)((char*)arr + o58 * 0x2bc);
    if (((XKey*)((char*)q + 0x150))->IsInTable(0x74667370, 0)) return;

    float A = *(float*)(o2 + 0x160c);
    float B = *(float*)(o2 + 0x1604);
    float C = *(float*)(o2 + 0x1608);
    float D = *(float*)(o2 + 0x161c);

    float local30 = B - f80 * D;
    float local2c = f7c * D + C;
    float local18 = A;

    float qx = q88.x, qy = q88.y, qz = q88.z, qw = q88.w;
    float X = (qz * qy + qw * qx) * g_1470f1c;
    float Y = g_1485720 - (qz * qz + qx * qx) * g_1470f1c;
    float Z = (qy * qx - qz * qw) * g_1470f1c;
    float dot = (-X * local18 + -Y * local2c) + -Z * local30;

    if (dot < g_1485378) a = g_1485720 - a;

    if (g_15515dc_s009d_5600 != 0 && o64 != 0 && o68 != 0)
    {
        float outv;
        FnCeec0(&outv, (g_1485720 - f78) * g_155125c_s009d_5600 * a);

        H9ce010(v24, sgn6(f7c) * local18 + ff0);

        float t;
        if (g_15509e0 != 0)
        {
            float den = local2c * local2c + local30 * local30;
            float f10 = (den <= g_14479b0) ? g_1485378 : (dot / den) * dot;
            t = (*(float*)((char*)p + 0xdc) * outv) * f10;
        }
        else t = g_1485378;

        Q4 qb, out, *r;
        qb.x = sinf(t * g_1471064);
        qb.y = g_1485378;
        qb.z = g_1485378;
        qb.w = cosf(t * g_1471064);
        r = QuatMul(&out, v24, &qb);
        v24->x = r->x; v24->y = r->y; v24->z = r->z; v24->w = r->w;

        if (g_15509e0 != 0) FnCf080(p, a, t);

        float s2 = sgn6(f7c);
        float ang = (s2 * local2c) * g_1471064;
        Q4 qb2;
        qb2.x = g_1485378;
        qb2.y = sinf(ang);
        qb2.z = g_1485378;
        qb2.w = cosf(ang);
        r = QuatMul(&out, v24, &qb2);
        v24->x = r->x; v24->y = r->y; v24->z = r->z; v24->w = r->w;
        return;
    }

    H9ce010(v24, ff0);

    float t;
    if (g_15509e0 != 0)
    {
        float den = local2c * local2c + local30 * local30;
        float f10 = (den <= g_14479b0) ? g_1485378 : (dot / den) * dot;
        t = ((((a - *(float*)((char*)p + 0x6c)) * (a - g_1485720)) *
              *(float*)((char*)p + 0xdc)) * *(float*)((char*)p + 0x68)) * f10 * a;
    }
    else t = g_1485378;

    float qx1 = v24->x, qy1 = v24->y, qz1 = v24->z, qw1 = v24->w;
    float sn = sinf(t * g_1471064);
    float cs = cosf(t * g_1471064);
    Q4 qb;
    qb.x = sn; qb.y = g_1485378; qb.z = g_1485378; qb.w = cs;
    float w = qw1, x = qx1, y = qy1, z = qz1;
    v24->x = ((x * cs + w * sn) - z * 0.0f) + y * 0.0f;
    v24->y = ((y * cs + w * 0.0f) - x * sn) + z * 0.0f;
    v24->z = ((z * cs + w * 0.0f) + x * 0.0f) - y * sn;
    v24->w = ((w * cs - x * 0.0f) - y * 0.0f) - z * sn;

    if (g_15509e0 != 0) FnCf080(p, a, t);
}

// @ 0x009d5b50
void __thiscall Ent::Fn5b50(Ent* p, float a)
{
    Q4* v24 = &this->v24;
    *v24 = q88;

    char* o2 = (char*)o_c8;
    if (*(u8*)(*(char**)o2 + 0x3f5) != 0) return;
    void* arr = *(void**)(o2 + 0x2e4);
    void* q = *(void**)((char*)arr + o58 * 0x2bc);
    if (((XKey*)((char*)q + 0x150))->IsInTable(0x74667370, 0)) return;

    if (g_15515dc_s009d_5600 == 0 || o64 == 0 || o68 == 0)
    {
        H9ce010(v24, ff0);
        return;
    }

    o2 = (char*)o_c8;
    float A = *(float*)(o2 + 0x160c);
    float B = *(float*)(o2 + 0x1604);
    float C = *(float*)(o2 + 0x1608);
    float D = *(float*)(o2 + 0x161c);

    float local30 = B - f80 * D;
    float local2c = f7c * D + C;
    float local18 = A;

    float qx = q88.x, qy = q88.y, qz = q88.z, qw = q88.w;
    float X = (qz * qy + qw * qx) * g_1470f1c;
    float Y = g_1485720 - (qz * qz + qx * qx) * g_1470f1c;
    float Z = (qy * qx - qz * qw) * g_1470f1c;
    float dot = (-X * local18 + -Y * local2c) + -Z * local30;

    float a2 = a;
    if (dot < g_1485378) a2 = g_1485720 - a;

    float outv;
    FnCeec0(&outv, (g_1485720 - (g_1485720 - a2) * f78) * g_155125c_s009d_5600);

    H9ce010(v24, sgn6(f7c) * local18 + ff0);

    float t;
    if (g_15509e0 != 0)
    {
        float den = local2c * local2c + local30 * local30;
        float f10 = (den <= g_14479b0) ? g_1485378 : (dot / den) * dot;
        t = (*(float*)((char*)p + 0xdc) * outv) * f10;
    }
    else t = g_1485378;

    Q4 qb, out, *r;
    qb.x = sinf(t * g_1471064);
    qb.y = g_1485378;
    qb.z = g_1485378;
    qb.w = cosf(t * g_1471064);
    r = QuatMul(&out, v24, &qb);
    v24->x = r->x; v24->y = r->y; v24->z = r->z; v24->w = r->w;

    if (g_15509e0 != 0) FnCf080(p, a2, t);

    float ang = (sgn6(f7c) * local2c) * g_1471064;
    Q4 qb2;
    qb2.x = g_1485378;
    qb2.y = sinf(ang);
    qb2.z = g_1485378;
    qb2.w = cosf(ang);
    r = QuatMul(&out, v24, &qb2);
    v24->x = r->x; v24->y = r->y; v24->z = r->z; v24->w = r->w;
}

// @ 0x009d7b20
void __cdecl SortElems(TElem* first, TElem* last, CmpObj cmp)
{
    if (first != last) {
        int n = last - first;
        int m = n;
        int lg = 0;
        while (m != 0) {
            m >>= 1;
            ++lg;
        }
        IntroLoop(first, last, lg * 2 - 2, cmp);
        if (n > 28) {
            InsertionSort(first, first + 28, cmp);
            UnguardedInsertionSort(first + 28, last, cmp);
        } else {
            InsertionSort(first, last, cmp);
        }
    }
}

// @ 0x009d7d10
int TOwner::AddElem(void* a, const V3* p3, const V4* p4)
{
    TVec& vec = v;
    int idx = vec.e - vec.b;
    TElem t;
    t.Init(a, *p3, *p4);
    TElem* pe = vec.e;
    if (pe < vec.c) {
        vec.e = pe + 1;
        if (pe)
            new (pe) TElem(t);
    } else {
        vec.DoInsertValue(pe, t);
    }
    return idx;
}

// @ 0x009db1d0
void Anim::A1d0()
{
    PhaseVec* v = (PhaseVec*)((char*)this + 0x10);
    Elem* begin = v->mpBegin;
    Elem* end = v->mpEnd;
    void* r = FUN_009d9ce0(end, end, begin);
    v->DoDestroyValues((Elem*)r, v->mpEnd);
    // Fold each end pointer back to begin + count*stride.  The count is taken from the
    // *end - begin* difference and multiplied back in, which is how the original computes
    // it (MSVC's negated reciprocal: 0x81f81f81 / 0xc1f07c1f / 0xd5555555).  Going the
    // other way - (begin - end)/stride - overflows the difference at -0x80000000 and then
    // rounds differently from the original on the edge input the harness probes.
    long x = (long)((char*)end - (char*)begin);
    v->mpEnd = (Elem*)((char*)v->mpEnd - x / 0x104 * 0x104);

    int b2 = *(int*)((char*)this + 0x24);
    int e2 = *(int*)((char*)this + 0x28);
    FUN_009cecb0((void*)e2, (void*)e2, (void*)b2);
    long x2 = (long)(e2 - b2);
    *(volatile int*)((char*)this + 0x28) -= x2 / 0x108 * 0x108;

    int b3 = *(volatile int*)((char*)this + 0x38);
    int e3 = *(volatile int*)((char*)this + 0x3c);
    FUN_009d41b0((void*)e3, (void*)e3, (void*)b3);
    long x3 = (long)(e3 - b3);
    *(int*)((char*)this + 0x3c) -= x3 / 0x30 * 0x30;
}

// @ 0x009db4d0
void Anim::A4d0(float f)
{
    // The original renders the leading flag argument as a single byte written into the
    // frame slot its prologue's `push ecx` left holding `this`, then re-reads that slot as
    // a dword, so the callee sees this with its low byte cleared instead of a plain 0.
    int clear = (int)this & ~0xFF;
    FUN_009d7b20(*(void**)((char*)this + 0x24), *(void**)((char*)this + 0x28), clear);
    Elem* e = A330();
    int n = (*(int*)((char*)this + 0x28) - *(int*)((char*)this + 0x24)) / 0x108;
    U32Vec* sv = (U32Vec*)((char*)e + 0xbc);
    for (int i = 0; i < n; ++i) {
        u32* p = sv->mpEnd;
        if (p < sv->mpCap) {
            sv->mpEnd = p + 1;
            if (p)
                *p = (u32)i;
        } else {
            sv->DoInsertValue(p, (const u32&)i);
        }
    }
    int x = FUN_009d3410(f);
    while (x != 0) {
        u32 v = ((Elem*)x)->FUN_009d0ee0();
        A3f0((void*)x, (int)v);
        x = FUN_009d3410(f);
    }
}
