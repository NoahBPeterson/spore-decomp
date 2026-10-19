// src/game/SPCreatureAnim/gait_dynamics.cpp -- migrated from slice(s) s005af200, s005ad9a0 by tools/migrate/rewrite.py
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

// ---- items of slice s005ad9a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void operator delete(void* p);  // EASTL_allocator_deallocate
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* memmove(void* dst, const void* src, unsigned int n);  // 0x011e0744 (static)
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
struct cSPVector3_s005a_d9a0 : public rw::math::fpu::Vector3Template_s005a_d9a0<float, 0> {
  typedef rw::math::fpu::Vector3Template_s005a_d9a0<float, 0> base;
  cSPVector3_s005a_d9a0() {}
  cSPVector3_s005a_d9a0(float ax, float ay, float az) : base(ax, ay, az) {}
  cSPVector3_s005a_d9a0(const base& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3_s005a_d9a0& operator=(const base& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
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
