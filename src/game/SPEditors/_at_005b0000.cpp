// src/game/SPEditors/_at_005b0000.cpp -- migrated from slice(s) s005ba320, s005bdca0, s005bc0f0, s005b7460, s005b0f80 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_005b0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorModel.h"
#include <new>
#include <math.h>
#include "SP/cSPEditorAnimatedEventInfo.h"
#include "SP/cSPEditorManipulationObject.h"
#include "SP/cSPEditorPhysicsWorld.h"
#include "SP/cViewer.h"
#include <string.h>
#include "cSPBoundingBox.h"
#include "cSPVector3.h"
#include "hkAabb.h"
#include "hkAllCdPointCollector.h"
#include "hkCdBody.h"
#include "hkCdPointCollector.h"
#include "hkCollidable.h"
#include "hkContactPoint.h"
#include "hkLinearCastInput.h"
#include "hkMotion.h"
#include "hkRigidBody.h"
#include "hkRootCdPoint.h"
#include "hkShape.h"
#include "hkTransform.h"
#include "hkVector4.h"

// unnamed retail callees and globals (address in the comment)
extern float g_1477fbc;                                  // 0x1477fbc (~200.0f)
extern float g_14853e0;                                  // 0x14853e0 (4.0f)
extern float g_13f6a28;                                  // 0x13f6a28 (-4.0f)
extern float g_15e97f8, g_15e97fc, g_15e9800;            // 0x15e97f8.. (direction)
extern float g_1488874;                                  // 0x1488874
extern float g_15e9874, g_15e9878, g_15e987c;            // 0x15e9874.. (direction)

// ---- items of slice s005b0f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_13f5c90;                                  // 0x13f5c90 (0.45f)
extern float g_1485378;                                  // 0x1485378 (0.0f)
struct cSPEditorBlock;
struct cSPEditorModel;
struct BBox {
  float mnx, mny, mnz;   // +0x00
  float mxx, mxy, mxz;   // +0x0c
};
struct BlockVtblObject {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24(void* out);
};
struct cSPEditorModel {
  char  pad_00[0x28];
  void* mSpine;                       // +0x28
  float FUN_004adaa0();               // 0x4adaa0
};
struct cSPEditorBlock {
  char pad_00[0x28];
  cSPEditorModel* mModel;             // +0x28
  char pad_2c[0x48 - 0x2c];
  float mPosX, mPosY, mPosZ;          // +0x48
  char pad_54[0x340 - 0x54];
  uint32_t* mChildBegin;              // +0x340
  uint32_t* mChildEnd;                // +0x344
  char pad_348[0x3e0 - 0x348];
  void* mField3E0;                    // +0x3e0
  BlockVtblObject* mField3EC;         // +0x3ec
  float* mField3F0;                   // +0x3f0
  char pad_3f4[0xdc8 - 0x3f4];
  uint32_t mFlagsDC8;                 // +0xdc8
  float F_43f250();                   // 0x43f250
  float F4d0();                       // 0x43f4d0
  BBox  GetBBox(int a, bool b, int c); // 0x44ae00
};
struct SPVectorU {
  uint32_t* mb;                        // +0x0 begin
  uint32_t* me;                        // +0x4 end
  uint32_t* mc;                        // +0x8 capacity
  void DoInsertValueI(uint32_t* pos, const uint32_t* value); // 0x4558a0
};
bool __cdecl IntersectRaySphere(const float* origin, const float* dir, const float* point,
                                float t, float* tOut);                     // 0x5a9c40
int  __cdecl FUN_011e0810(void);                                          // 0x11e0810
void* __cdecl SP_EditorUtils_FindRootSpine(cSPEditorModel* model);        // 0x4a5a70
void* __cdecl FUN_004a5970(void* block);                                  // 0x4a5970
float __cdecl SP_EditorUtils_GetSkinRadius(void* block);                  // 0x4a5c40
void __cdecl FUN_00f47380(void* p);                                       // 0xf47380 (operator delete)
struct S80 {
  float m0, m1, m2, m3, m4, m5;   // +0x0..+0x14
  bool  m18;                      // +0x18
  void Set(float a, float b, float c, float d, float e, float f);
  S80(float a, float b, float c, float d, float e, float f);
};
void S80::Set(float a, float b, float c, float d, float e, float f) {
  S80* self = this;
  self->m0 = a; self->m1 = b; self->m2 = c; self->m3 = d; self->m4 = e; self->m5 = f;
  self->m18 = false;
}
struct Sd0 {
  float mOriginX, mOriginY, mOriginZ;   // +0x00
  float mDirX, mDirY, mDirZ;            // +0x0c
  bool  mHasBest;                       // +0x18
  char  pad_19[3];
  union { float mBestX; uint32_t mBestXBits; };     // +0x1c
  union { float mBestY; uint32_t mBestYBits; };     // +0x20
  union { float mBestZ; uint32_t mBestZBits; };     // +0x24
  union { float mBestDist; uint32_t mBestDistBits; }; // +0x28
  __declspec(noinline) void Consider(float x, float y, float z);
  __declspec(noinline) void FUN_005b1130(float a, float b, float c, float t);
  __declspec(noinline) void FUN_005b11e0(float px, float py, float pz, float dx, float dy, float dz, bool b);
  __declspec(noinline) void FUN_005b1310(float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9);
  __declspec(noinline) void FUN_005b15e0(cSPEditorBlock* block, cSPEditorBlock* other);
  __declspec(noinline) void FUN_005b1870(cSPEditorBlock* block, cSPEditorBlock* other,
                    float p3, float p4, float p5, float p6, float p7, float p8);
};
// ---- items of slice s005b0f80 end

// ---- items of slice s005b7460 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
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
struct eastl_bitset54 {
  uint32_t mWord[2];
  bool test(unsigned int i) const { return ((mWord[i >> 5] >> (i & 31)) & 1) != 0; }
};
namespace SP {
class cViewer_s005b_7460 {
 public:
  bool GetWorldRayFromScreenCoords(float x, float y, cSPVector3_s005b_7460& origin, cSPVector3_s005b_7460& direction);  // 0x007c4730 (SP::cViewer::GetWorldRayFromScreenCoords)
};
}
namespace SP {
class cSPApp {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
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
class cSPEditorModelBase { public: PV(0) };
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
class cSPEditorSpinePart {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
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
template <typename K, typename V>
struct pair_s005b_7460 {
  K first;
  V second;
};
}
namespace eastl {
typedef pair_s005b_7460<SP::cSPEditorBlock_s005b_7460* const, EA::AutoRefCount_s005b_7460<SP::cSPEditorSkinPart_s005b_7460> > BlockLimbPair;
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
class cSPEditorManipulationSpine : public cSPEditorManipulationObject_s005b_7460, public EA::RefCountVTemplate_s005b_7460<int> {
 public:
  cSPEditorBlock_s005b_7460* mBlock;      // +0x1c
  cSPVector3_s005b_7460 mMouseOffset;     // +0x20
  cSPEditorSpine_s005b_7460* mSpine;      // +0x2c
  bool mModelUsingSymmetry;    // +0x30

  cSPEditorManipulationSpine();
  void Init(cSPEditorBlock_s005b_7460* block, cSPVector3_s005b_7460 mouseOffset, cSPEditorSpine_s005b_7460* spine);
  bool OnMouseUp(int button, float x, float y, int modifiers);
  bool DoOnMouseDown(int button, float x, float y, int modifiers);
  bool DoOnMouseMove(float x, float y, int modifiers);
};
}
// ---- items of slice s005b7460 end

// ---- items of slice s005bc0f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
struct cSPVector3_s005b_c0f0 {
  float x, y, z;
  cSPVector3_s005b_c0f0() {}
  cSPVector3_s005b_c0f0(float a, float b, float c) : x(a), y(b), z(c) {}
  cSPVector3_s005b_c0f0(const cSPVector3_s005b_c0f0& v) : x(v.x), y(v.y), z(v.z) {}
};
namespace EA {
template <typename T>
class AutoRefCount_s005b_c0f0 {
 public:
  T* mpObject;
  AutoRefCount_s005b_c0f0() : mpObject(0) {}
  AutoRefCount_s005b_c0f0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005b_c0f0() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005b_c0f0& operator=(T* p) {
    if (p != mpObject) { T* t = mpObject; if (p) p->AddRef(); mpObject = p; if (t) t->Release(); }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005b_c0f0 {
 public:
  RefCountVTemplate_s005b_c0f0() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005b_c0f0() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace eastl {
struct sp_vector_allocator_s005b_c0f0 {
  int mAllocId;
  int mAllocPad;
};
}
namespace eastl {
template <typename T, typename Alloc>
class vector_s005b_c0f0 {
 public:
  T* mpBegin;      // +0x0
  T* mpEnd;        // +0x4
  T* mpCapacity;   // +0x8
  Alloc mAllocator;

  ~vector_s005b_c0f0() { if (mpBegin && ((int*)mpBegin)[-1] != 0) EASTL_allocator_deallocate(mpBegin); }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  T* erase(T* first, T* last);                                  // 0x00454280
  void* Grow(unsigned int n, const T* first, const T* last);    // 0x005bc8e0
  vector_s005b_c0f0& operator=(const vector_s005b_c0f0& x);
};
}
namespace SP {
class cSPEditorBlock_s005b_c0f0;
}
namespace SP {
class cSPEditorModel_s005b_c0f0;
}
namespace SP {
class cSPEditorPhysicsWorld_s005b_c0f0;
}
namespace SP {
struct cSPMatrix3 {
  float m[9];
  cSPMatrix3() {}
  cSPMatrix3(const cSPMatrix3& o);              // 0x0041cb40
  void Assign(const cSPMatrix3& o);             // 0x0041cb40
};
}
namespace SP {
struct ModelRefCount {
  virtual void Destroy(int flag);   // slot 0: scalar deleting destructor
  int mnRefCount;                   // +0x8 in cSPEditorModel
  void AddRef() { ++mnRefCount; }
  __forceinline int Release() {
    int n = --mnRefCount;
    if (n == 0) {
      mnRefCount = 1;
      Destroy(1);
    }
    return n;
  }
};
}
namespace SP {
class cSPEditorPhysicsWorld_s005b_c0f0 {
 public:
  char pad00[0xc];
  void* mpFloorBody;                // +0xc
};
}
namespace SP {
class cSPEditorModel_s005b_c0f0 {
 public:
  virtual void v0();                            // +0x0 vtable
  ModelRefCount rc;                             // +0x4
  void AddRef() { rc.AddRef(); }
  int Release() { return rc.Release(); }
  cSPEditorPhysicsWorld_s005b_c0f0* GetPhysicsWorld();     // 0x004ad450
  float GetScale();                             // 0x004adaa0
  bool UsingSymmetry() const;                   // 0x004adc40
};
}
namespace EA {
namespace Swarm {
class cIVisualEffect_s005b_c0f0 {
 public:
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void Update(int mode);    // +0xc
};
}
}
namespace SP {
class cSPEditorBlock_s005b_c0f0 {
 public:
  virtual void v0();
  virtual int AddRef();
  virtual int Release();

  char pad04[0x28 - 4];
  cSPEditorModel_s005b_c0f0* mpModel;                      // +0x28
  char pad2c[0x48 - 0x2c];
  cSPVector3_s005b_c0f0 mPosition;                         // +0x48
  char pad54[0x60 - 0x54];
  cSPMatrix3 mOrientation;                      // +0x60
  char pad84[0xa8 - 0x84];
  cSPMatrix3 mBaseOrientation;                  // +0xa8
  char padcc[0x33c - 0xcc];
  cSPEditorBlock_s005b_c0f0* mpParent;                     // +0x33c
  char pad340[0x3c9 - 0x340];
  char mbOnFloor;                               // +0x3c9
  char pad3ca[0x3e0 - 0x3ca];
  cSPEditorBlock_s005b_c0f0* mpSymmetric;                  // +0x3e0
  char pad3e4[0xdc8 - 0x3e4];
  unsigned int mFlagsA;                         // +0xdc8
  unsigned int mFlagsB;                         // +0xdcc

  void SetPosition(const cSPVector3_s005b_c0f0& pos, bool notify);   // 0x00448e90
  void SetIsOnGround(bool onGround);                      // 0x0049c0f0
  bool Unk43bbc0(int a);                                  // 0x0043bbc0
  bool NeedPostUpdate();                                  // 0x00435c80
};
}
namespace SP {
class cSPEditorManipulationObject_s005b_c0f0 {
 public:
  __declspec(noinline) cSPEditorManipulationObject_s005b_c0f0();
  virtual ~cSPEditorManipulationObject_s005b_c0f0() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};
}
namespace SP {
typedef eastl::vector_s005b_c0f0<EA::AutoRefCount_s005b_c0f0<cSPEditorBlock_s005b_c0f0>, eastl::sp_vector_allocator_s005b_c0f0> BlockRefVector;
}
namespace SP {
typedef eastl::vector_s005b_c0f0<EA::Swarm::cIVisualEffect_s005b_c0f0*, eastl::sp_vector_allocator_s005b_c0f0> EffectVector;
}
namespace SP {
class cSPEditorManipulationStacking : public cSPEditorManipulationObject_s005b_c0f0, public EA::RefCountVTemplate_s005b_c0f0<int> {
 public:
  char pad1c[0x24 - 0x1c];
  cSPEditorBlock_s005b_c0f0* mpBlock;                      // +0x24
  BlockRefVector mPileList;                     // +0x28
  cSPVector3_s005b_c0f0 mMouseOffset;                      // +0x3c
  cSPVector3_s005b_c0f0 mStartPos;                         // +0x48
  float mLastX;                                 // +0x54
  float mLastY;                                 // +0x58
  int mLastFlags;                               // +0x5c
  cSPVector3_s005b_c0f0 mPosition;                         // +0x60
  char pad6c[0x8a - 0x6c];
  bool mAlignmentState;                         // +0x8a

  int MoveBlockStacking(cSPEditorBlock_s005b_c0f0* block, BlockRefVector* pile, cSPVector3_s005b_c0f0 rayOrigin,
                        cSPVector3_s005b_c0f0 rayDirection);                             // 0x005bb5a0
  virtual bool DoOnMouseMove(float x, float y, int flags);
};
}
namespace SP {
struct cViewer_s005b_c0f0 {
  void GetWorldRayFromScreenCoords(float x, float y, cSPVector3_s005b_c0f0* origin, cSPVector3_s005b_c0f0* dir);  // 0x007c4730
};
}
namespace SP {
struct cAppSystem {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
  virtual cViewer_s005b_c0f0* GetViewer();                 // +0x58
};
}
namespace SP {
cAppSystem* App_s005b_c0f0();                              // 0x0067dd10
}
namespace SP {
extern const float g_defaultBlockScale;         // 0x014853e0 (4.0f)
}
namespace SP {
extern const float g_stackScaleFactor;          // 0x013f5698 (0.667f)
}
namespace SP {
extern const float g_alignmentEpsilon;          // 0x013eb960 (0.01f)
}
namespace SP {
extern const float g_minusOne;                  // 0x013eb1bc (-1.0f)
}
namespace SP {
extern int g_killSetAlignmentOff;               // 0x015ea600
}
namespace SP {
extern int g_killSetAlignmentOn;                // 0x015ea668
}
namespace SP {
void KillSeti(int id);                                                          // 0x004a88d0
}
namespace SP {
cSPEditorBlock_s005b_c0f0* FUN_004a3dc0(cSPEditorBlock_s005b_c0f0* block, void* pile, cSPVector3_s005b_c0f0 origin,
                             cSPVector3_s005b_c0f0 dir, cSPVector3_s005b_c0f0* outPosition);          // 0x004a3dc0
}
namespace SP {
void FUN_004a1070(cSPEditorBlock_s005b_c0f0* block);                                       // 0x004a1070
}
namespace SP {
bool FUN_004982b0(cSPEditorBlock_s005b_c0f0* block, char unk0, float scale, char unk1);    // 0x004982b0
}
namespace SP {
void FUN_00496300(cSPEditorBlock_s005b_c0f0* block, void* pile, cSPVector3_s005b_c0f0 origin, cSPVector3_s005b_c0f0 dir,
                  cSPVector3_s005b_c0f0 startPos, int unk);                                // 0x00496300
}
namespace SP {
void FUN_004a6d20(cSPEditorBlock_s005b_c0f0* block, void* pile, int flag, int a, int b, int c,
                  int d, int e);                                                // 0x004a6d20
}
namespace SP {
void SnapBlockToSocket(cSPEditorBlock_s005b_c0f0* block, void* pile, cSPEditorBlock_s005b_c0f0* socket); // 0x004a29a0
}
namespace SP {
void SetSymmetricBlocksUIState(cSPEditorBlock_s005b_c0f0* block, void* pile, int state);   // 0x004a7f30
}
namespace SP {
float GetAlignmentPosition(cSPEditorBlock_s005b_c0f0* block, void* pile, cSPVector3_s005b_c0f0 pos, cSPMatrix3 m2,
                           cSPVector3_s005b_c0f0* outPos, cSPMatrix3* outRot, bool* flag, int mode,
                           cSPMatrix3 m1);                                      // 0x00490a70
}
namespace SP {
volatile int g_s59_sink;
}
namespace SP {
__declspec(noinline) cSPEditorManipulationObject_s005b_c0f0::cSPEditorManipulationObject_s005b_c0f0() { g_s59_sink = 1; }
}
namespace eastl {
template class vector_s005b_c0f0<EA::Swarm::cIVisualEffect_s005b_c0f0*, sp_vector_allocator_s005b_c0f0>;  // namespace eastl
}
// ---- items of slice s005bc0f0 end

// ---- items of slice s005bdca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" const float F_013f7944;        // 0x013f7944  FLT_MAX
extern "C" const float F_013f51ac;        // 0x013f51ac  -FLT_MAX
void* FUN_005b0f80(void* self);                      // 0x005b0f80  base ctor
struct CSpEditorManip {
  void* vt00;             // +0x00
  char  f04;              // +0x04
  char  pad05[0x0f];
  void* vt14;             // +0x14
  int   f18;              // +0x18
  int   f1c;              // +0x1c
  int   f20;              // +0x20
  int   f24;              // +0x24
  int   f28;              // +0x28
  int   f2c;              // +0x2c
  char  pad30[8];
  char  f38;              // +0x38
  float f3c, f40, f44;    // +0x3c
  char  pad48[4];
  int   f4c;              // +0x4c
  int   f50;              // +0x50
  int   f54;              // +0x54
  int   f58;              // +0x58
  int   f5c;              // +0x5c
  float f64, f68, f6c;    // +0x64
  float f70, f74, f78;    // +0x70
  CSpEditorManip* init();
};
// ---- items of slice s005bdca0 end

// ---- items of slice s005ba320 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" double __cdecl fabs(double);
extern "C" double __cdecl sqrt(double);
extern float gStackingHeightTolerance;  // 0x015134dc (0.05)
#pragma intrinsic(fabs, sqrt)
typedef unsigned int size_type;
void __cdecl operator delete[](void* p);  // 0x00f47380
struct cSPVector3_s005b_a320 {
    float x, y, z;
    cSPVector3_s005b_a320() {}
    cSPVector3_s005b_a320(float fx, float fy, float fz) : x(fx), y(fy), z(fz) {}
    cSPVector3_s005b_a320(const cSPVector3_s005b_a320& v) : x(v.x), y(v.y), z(v.z) {}
    void Set(float fx, float fy, float fz) { x = fx; y = fy; z = fz; }
    cSPVector3_s005b_a320 operator+(const cSPVector3_s005b_a320& v) const { return cSPVector3_s005b_a320(x + v.x, y + v.y, z + v.z); }
    cSPVector3_s005b_a320 operator*(float f) const { return cSPVector3_s005b_a320(x * f, y * f, z * f); }
    cSPVector3_s005b_a320 operator-() const { return cSPVector3_s005b_a320(-x, -y, -z); }
    float Dot(const cSPVector3_s005b_a320& v) const { return x * v.x + y * v.y + z * v.z; }
};
extern cSPVector3_s005b_a320 kSPUpAxis;   // 0x015ea68c
#define FLT_MAX_VALUE 3.402823466e+38F
#define FLT_MIN_VALUE 1.175494351e-38F
#define HK_ALIGN16 __declspec(align(16))
#define HK_REAL_MAX 3.40282e+38f
#define HK_REAL_EPSILON 1.192092896e-07F
struct HK_ALIGN16 hkVector4_s005b_a320 {
    float x, y, z, w;
    hkVector4_s005b_a320() {}
    hkVector4_s005b_a320(float a, float b, float c, float d = 0.0f) : x(a), y(b), z(c), w(d) {}
    hkVector4_s005b_a320(const hkVector4_s005b_a320& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    float& operator()(int i) { return (&x)[i]; }
    const float& operator()(int i) const { return (&x)[i]; }
    void setTransformedInversePos(const class hkTransform_s005b_a320& t, const hkVector4_s005b_a320& v);  // 0x010813d0
};
class hkTransform_s005b_a320 { public:
    hkVector4_s005b_a320 m_rotation[3];
    hkVector4_s005b_a320 m_translation;
    static const hkTransform_s005b_a320& getIdentity() { return s_identity; }
    static const hkTransform_s005b_a320 s_identity;   // 0x015b9b20
};
class hkAabb_s005b_a320 { public:
    hkVector4_s005b_a320 m_min;
    hkVector4_s005b_a320 m_max;
};
class hkThreadMemory { public:
    void deallocateChunk(void* p, int nbytes, int cls);  // 0x0107db10
    static unsigned long s_threadMemoryInstance;          // 0x016e4174 (TLS index)
    static hkThreadMemory& getInstance() { return *static_cast<hkThreadMemory*>(TlsGetValue(s_threadMemoryInstance)); }
};
enum { HK_MEMORY_CLASS_COLLIDE = 0x14 };
template <typename T>
class hkArray { public:
    enum { CAPACITY_MASK = 0x3fffffff, DONT_DEALLOCATE_FLAG = 0x80000000 };
    T* m_data;
    int m_size;
    int m_capacityAndFlags;
    int getSize() const { return m_size; }
    int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
    T& operator[](int i) { return m_data[i]; }
    ~hkArray()
    {
        if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
            hkThreadMemory::getInstance().deallocateChunk(m_data, getCapacity() * sizeof(T), HK_MEMORY_CLASS_COLLIDE);
    }
};
template <typename T, int N>
class hkInplaceArray : public hkArray<T> { public:
    T m_storage[N];
    hkInplaceArray()
    {
        this->m_data = m_storage;
        this->m_size = 0;
        this->m_capacityAndFlags = N | hkArray<T>::DONT_DEALLOCATE_FLAG;
    }
};
class hkShape_s005b_a320 { public:
    virtual ~hkShape_s005b_a320();
    virtual void calcStatistics(void* collector) const;
    virtual int getType() const;
    virtual void getAabb(const hkTransform_s005b_a320& localToWorld, float tolerance, hkAabb_s005b_a320& out) const;  // +0xc
    virtual float getMaximumProjection(const hkVector4_s005b_a320& direction) const;                     // +0x10
};
class hkCdBody_s005b_a320 { public:
    const hkShape_s005b_a320* m_shape;
    unsigned int m_shapeKey;
    const void* m_motion;
    const hkCdBody_s005b_a320* m_parent;
    const hkShape_s005b_a320* getShape() const { return m_shape; }
};
class hkCollidable_s005b_a320 : public hkCdBody_s005b_a320 { public:
    int m_ownerOffset;               // +0x10
    unsigned int m_broadPhaseHandle[3];
    float m_allowedPenetrationDepth;
    void* getOwner() const { return (void*)((char*)this + m_ownerOffset); }
};
class hkMotionState { public:
    hkTransform_s005b_a320 m_transform;
};
class hkMotion_s005b_a320 { public:
    void* vtbl_;
    unsigned int m_memSizeAndRefCount;
    int m_solverData;
    unsigned int pad_;
    hkMotionState m_motionState;     // +0x10
};
class hkRigidBody_s005b_a320 { public:
    void* vtbl_;                     // +0x0
    unsigned int m_memSizeAndRefCount;
    unsigned int m_world;
    unsigned int m_userData;
    char* m_name;
    unsigned int m_multithreadLock[2];
    hkCollidable_s005b_a320 m_collidable;       // +0x1c
    unsigned int m_collisionEntries[3];  // +0x40 hkArray
    unsigned int m_properties[3];
    hkMotion_s005b_a320* m_motion;              // +0x58

    const hkCollidable_s005b_a320* getCollidable() const { return &m_collidable; }
    const hkTransform_s005b_a320& getTransform() const { return m_motion->m_motionState.m_transform; }
    const hkVector4_s005b_a320& getPosition() const { return getTransform().m_translation; }
    void setPosition(const hkVector4_s005b_a320& position);  // 0x01087820
};
class hkContactPoint_s005b_a320 { public:
    hkVector4_s005b_a320 m_position;
    hkVector4_s005b_a320 m_separatingNormal;
    const hkVector4_s005b_a320& getPosition() const { return m_position; }
    float getDistance() const { return m_separatingNormal.w; }
};
struct hkRootCdPoint_s005b_a320 {
    hkContactPoint_s005b_a320 m_contact;
    const hkCollidable_s005b_a320* m_rootCollidableA;
    unsigned int m_shapeKeyA;
    const hkCollidable_s005b_a320* m_rootCollidableB;
    unsigned int m_shapeKeyB;
};
class hkCdPointCollector_s005b_a320 { public:
    hkCdPointCollector_s005b_a320() { m_earlyOutDistance = HK_REAL_MAX; }
    virtual ~hkCdPointCollector_s005b_a320() {}
    virtual void addCdPoint(const void* point) = 0;
    float m_earlyOutDistance;
};
class hkAllCdPointCollector_s005b_a320 : public hkCdPointCollector_s005b_a320 { public:
    hkAllCdPointCollector_s005b_a320() {}
    virtual ~hkAllCdPointCollector_s005b_a320() {}
    virtual void addCdPoint(const void* point);
    hkInplaceArray<hkRootCdPoint_s005b_a320, 8> m_hits;     // +0x10
    hkArray<hkRootCdPoint_s005b_a320>& getHits() { return m_hits; }
    void sortPoints();                            // 0x010c2570
};
struct hkLinearCastInput_s005b_a320 {
    hkVector4_s005b_a320 m_to;
    float m_maxExtraPenetration;
    float m_startPointTolerance;
    hkLinearCastInput_s005b_a320() : m_maxExtraPenetration(HK_REAL_EPSILON), m_startPointTolerance(HK_REAL_EPSILON) {}
};
class hkWorld_s005b_a320 { public:
    void linearCast(const hkCollidable_s005b_a320* collA, const hkLinearCastInput_s005b_a320& input,
                    hkCdPointCollector_s005b_a320& castCollector, hkCdPointCollector_s005b_a320* startCollector = 0);  // 0x01082b90
};
namespace eastl {
struct sp_vector_allocator_s005b_a320 {
    const char* mpName;
    unsigned int mFlags;
    sp_vector_allocator_s005b_a320() {}
    void deallocate(void* p, size_type)
    {
        if (((unsigned int*)p)[-1])
            delete[] (char*)p;
    }
};
}
namespace eastl {
template <typename T, typename Allocator = sp_vector_allocator_s005b_a320>
struct VectorBase_s005b_a320 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    VectorBase_s005b_a320() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase_s005b_a320()
    {
        if (mpBegin)
            DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
    }
    void DoFree(T* p, size_type n) { mAllocator.deallocate(p, n * sizeof(T)); }
};
}
namespace eastl {
template <typename T, typename Allocator = sp_vector_allocator_s005b_a320>
class vector_s005b_a320 : public VectorBase_s005b_a320<T, Allocator> { public:
    using VectorBase_s005b_a320<T, Allocator>::mpBegin;
    using VectorBase_s005b_a320<T, Allocator>::mpEnd;
    using VectorBase_s005b_a320<T, Allocator>::mpCapacity;

    vector_s005b_a320() {}
    ~vector_s005b_a320() { DoDestroyValues(mpBegin, mpEnd); }
    void DoDestroyValues(T* first, T* last)
    {
        for (; first < last; ++first)
            first->~T();
    }
    bool empty() const { return mpBegin == mpEnd; }
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    T& operator[](size_type n) { return mpBegin[n]; }
    void resize(size_type n);                              // 0x00473810 (vector<cSPVector3>)
    void DoInsertValue(T* position, const T& value);       // 0x00630b30 (pointer vectors)
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
    }
};
}
namespace EA {
template <typename T>
class AutoRefCount_s005b_a320 { public:
    T* mpObject;
    ~AutoRefCount_s005b_a320()
    {
        if (mpObject)
            mpObject->Release();
    }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};  // namespace EA
}
namespace SP {
struct cSPPlane {
    cSPVector3_s005b_a320 mNormal;
    float mD;
    cSPPlane(const cSPVector3_s005b_a320& normal, const cSPVector3_s005b_a320& point) : mNormal(normal), mD(-normal.Dot(point)) {}
};
}
namespace SP {
struct cSPBoundingBox {
    cSPVector3_s005b_a320 mMin;
    cSPVector3_s005b_a320 mMax;
};
}
namespace SP {
class cSPEditorPhysicsWorld_s005b_a320 { public:
    void SetFloorFilter(bool enable);   // 0x004b9440
    hkWorld_s005b_a320* World();                   // 0x004b91c0
};
}
namespace SP {
class cSPEditorModel_s005b_a320 { public:
    cSPEditorPhysicsWorld_s005b_a320* GetPhysicsWorld();   // 0x004ad450
    void NumberBlocks();                        // 0x004ad4e0
    float GetGridSize();                        // 0x004adaa0 (returns +0x38)
};
}
namespace SP {
class cSPEditorBlock_s005b_a320 { public:
    virtual void Dispose();
    virtual int AddRef();
    virtual int Release();
    uint32_t pad04[9];
    cSPEditorModel_s005b_a320* mEditorModel;   // +0x28
    uint32_t pad2c[7];
    cSPVector3_s005b_a320 mPosition;           // +0x48
    uint32_t pad54[78];
    hkRigidBody_s005b_a320* mpRigidBody;       // +0x18c

    void GetBBox(cSPBoundingBox* box, int a, int b, int c);  // 0x0044ae00
};
}
namespace SP {
struct cSPCamera {
    cSPVector3_s005b_a320 WorldToProjection(const cSPVector3_s005b_a320& p);  // 0x007c4180
};
}
namespace SP {
struct cSPApp_s005b_a320 {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
    virtual cSPCamera* GetCamera();   // +0x58
};
}
namespace SP {
cSPApp_s005b_a320* App_s005b_a320();   // 0x0067dd10
}
namespace SP {
typedef eastl::vector_s005b_a320<EA::AutoRefCount_s005b_a320<cSPEditorBlock_s005b_a320> > BlockList;
}
namespace SP {
void GetStackCandidates(cSPEditorBlock_s005b_a320* block, int mode, BlockList* out);              // 0x004905d0
}
namespace SP {
void PrepareBlockForStacking(cSPEditorBlock_s005b_a320* block, int mode, int a, int b, int c);   // 0x004a6690
}
namespace SP {
class cSPEditorManipulationStacking_s005b_a320 { public:
    uint32_t pad00[8];
    EA::AutoRefCount_s005b_a320<cSPEditorBlock_s005b_a320> mBlock;   // +0x20
    uint32_t pad24[9];
    cSPVector3_s005b_a320 mTargetPosition;                // +0x48

    hkRigidBody_s005b_a320* FindStackingTarget(cSPEditorBlock_s005b_a320* block, int mode, cSPVector3_s005b_a320 rayOrigin,
                                    cSPVector3_s005b_a320 rayDirection, cSPVector3_s005b_a320* outPosition);
};
}
namespace SP {
inline void cSPBoundingBox_GetCorners(const cSPBoundingBox& box, cSPVector3_s005b_a320* c)
{
    const cSPVector3_s005b_a320& mn = box.mMin;
    const cSPVector3_s005b_a320& mx = box.mMax;
    c[0].Set(mn.x, mn.y, mn.z);
    c[1].Set(mx.x, mn.y, mn.z);
    c[2].Set(mn.x, mx.y, mn.z);
    c[3].Set(mx.x, mx.y, mn.z);
    c[4].Set(mn.x, mn.y, mx.z);
    c[5].Set(mx.x, mn.y, mx.z);
    c[6].Set(mn.x, mx.y, mx.z);
    c[7].Set(mx.x, mx.y, mx.z);
}
}
namespace SP {
__forceinline void GetAabbCorners(const hkAabb_s005b_a320& aabb, cSPVector3_s005b_a320* c)
{
    c[0] = cSPVector3_s005b_a320(aabb.m_min(0), aabb.m_min(1), aabb.m_min(2));
    c[1] = cSPVector3_s005b_a320(aabb.m_max(0), aabb.m_min(1), aabb.m_min(2));
    c[2] = cSPVector3_s005b_a320(aabb.m_min(0), aabb.m_max(1), aabb.m_min(2));
    c[3] = cSPVector3_s005b_a320(aabb.m_max(0), aabb.m_max(1), aabb.m_min(2));
    c[4] = cSPVector3_s005b_a320(aabb.m_min(0), aabb.m_min(1), aabb.m_max(2));
    c[5] = cSPVector3_s005b_a320(aabb.m_max(0), aabb.m_min(1), aabb.m_max(2));
    c[6] = cSPVector3_s005b_a320(aabb.m_min(0), aabb.m_max(1), aabb.m_max(2));
    c[7] = cSPVector3_s005b_a320(aabb.m_max(0), aabb.m_max(1), aabb.m_max(2));
}
}
namespace SP {
template <typename T> inline const T& max_alt(const T& a, const T& b) { return (a < b) ? b : a; }
}
namespace SP {
template <typename T> inline const T& min_alt(const T& a, const T& b) { return (b < a) ? b : a; }
}
// ---- items of slice s005ba320 end

// @ 0x005b1080
S80::S80(float a, float b, float c, float d, float e, float f)
: m0(a), m1(b), m2(c), m3(d), m4(e), m5(f), m18(false) {}

// @ 0x005b10d0
void Sd0::Consider(float x, float y, float z)
{
  float dx = mOriginX - x;
  float dy = mOriginY - y;
  float dz = mOriginZ - z;
  float d = sqrtf(dx * dx + dy * dy + dz * dz);
  if (!mHasBest || d < mBestDist) {
    // The retail code copies the arguments with integer loads/stores (it leaves
    // eax = the z bits on return), so store the argument bit patterns instead
    // of using float moves.
    mBestXBits = *(uint32_t*)&x;
    mBestYBits = *(uint32_t*)&y;
    mHasBest = true;
    mBestDist = d;
    mBestZBits = *(uint32_t*)&z;
  }
}

// @ 0x005b1130
void Sd0::FUN_005b1130(float a, float b, float c, float t)
{
  float local[3];
  local[0] = a;
  local[1] = b;
  local[2] = c;
  if (IntersectRaySphere(&mOriginX, &mDirX, local, t, &t)) {
    float px = mOriginX + mDirX * t;
    float py = mOriginY + mDirY * t;
    float pz = mOriginZ + mDirZ * t;
    Consider(px, py, pz);
  }
}

// @ 0x005b11e0
void Sd0::FUN_005b11e0(float px, float py, float pz, float dx, float dy, float dz, bool b)
{
  if (!b || g_13f5c90 < fabsf(mDirZ * dz + mDirY * dy + mDirX * dx)) {
    float denom = mDirZ * dz + mDirY * dy + mDirX * dx;
    if (denom != g_1485378) {
      // Keep the retail association: inner = (py*dy + pz*dz) + px*dx and
      // outer = (mOriginZ*dz + mOriginY*dy) + mOriginX*dx; reassociating the
      // sums changes the last bit of the resulting t.
      float inner = (py * dy + pz * dz) + px * dx;
      float outer = (mOriginZ * dz + mOriginY * dy) + mOriginX * dx;
      float t = -((outer - inner) / denom);
      if (t >= g_1485378) {
        Consider(mOriginX + t * mDirX, mOriginY + t * mDirY, mOriginZ + t * mDirZ);
      }
    }
  }
}

// @ 0x005b1310
void Sd0::FUN_005b1310(float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9)
{
  int n = FUN_011e0810();
  if (n > 0) {
    float ox = mOriginX;
    float oy = mOriginY;
    float oz = mOriginZ;
    for (int i = 1; i <= n; i++) {
      float f = (float)i / (float)n;
      float f13 = oy - ((p7 - p3) * f + p3);
      float f12 = ox - ((p6 - p2) * f + p2);
      float f10 = oz - ((p8 - p4) * f + p4);
      float f11 = (p9 - p5) * f + p5;
      float f7 = mDirY * f13 + mDirZ * f10 + mDirX * f12;
      float f9 = mDirX * mDirX + mDirY * mDirY + mDirZ * mDirZ;
      float disc = f7 * f7 - (((f10 * f10 + f13 * f13) + f12 * f12) - f11 * f11) * f9;
      if (disc >= 0.0f) {
        float s = sqrtf(disc);
        float t0 = -f7 - s;
        if (0.0f <= s - f7) {
          float t = (t0 > 0.0f) ? t0 / f9 : 0.0f;
          float cx = ox + mDirX * t;
          float cy = oy + mDirY * t;
          float cz = oz + mDirZ * t;
          float e1 = ox - cx;
          float e2 = oy - cy;
          float e3 = oz - cz;
          float dist = sqrtf(e1 * e1 + (e2 * e2 + e3 * e3));
          if (mHasBest == false || dist < mBestDist) {
            mBestX = cx;
            mBestY = cy;
            mBestZ = cz;
            mHasBest = true;
            mBestDist = dist;
          }
        }
      }
    }
  }
}

// @ 0x005b15e0
void Sd0::FUN_005b15e0(cSPEditorBlock* block, cSPEditorBlock* other)
{
  if (((block->mFlagsDC8 >> 0xb) & 1) == 0) {
    if (block != other) {
      BBox bb = block->GetBBox(1, 0, 0);
      float cx = block->mPosX + (bb.mxx + bb.mnx) * 0.5f;
      float cy = block->mPosY + (bb.mxy + bb.mny) * 0.5f;
      float cz = block->mPosZ + (bb.mxz + bb.mnz) * 0.5f;
      BBox bb2 = block->GetBBox(1, 0, 0);
      float rad = sqrtf(bb2.mnx * bb2.mnx + (bb2.mny * bb2.mny + bb2.mnz * bb2.mnz)) * 0.5f;
      FUN_005b1130(cx, cy, cz, rad);
    }
  } else if (block != other) {
    cSPEditorBlock* ob3e0 = (cSPEditorBlock*)other->mField3E0;
    if (block != ob3e0) {
      int count = (int)(block->mChildEnd - block->mChildBegin) >> 2;
      int i = 0;
      bool found = false;
      if (0 < count) {
        do {
          cSPEditorBlock* ch = (cSPEditorBlock*)block->mChildBegin[i];
          if (ch == other || ch == ob3e0) {
            found = true;
            break;
          }
          i = i + 1;
        } while (i < count);
      }
      float L[3];
      if (found) {
        block->mField3EC->v24(L);
        float f = block->F_43f250();
        FUN_005b1130(L[0], L[1], L[2], f);
      } else {
        block->mField3EC->v24(L);
        float E[3];
        E[0] = block->mField3F0[3];
        E[1] = block->mField3F0[4];
        E[2] = block->mField3F0[5];
        float f6 = block->F_43f250();
        float f7 = block->F4d0();
        FUN_005b1310(L[0], L[1], L[2], f6, E[0], E[1], E[2], f7);
      }
    }
  }
  {
    int count = (int)(block->mChildEnd - block->mChildBegin) >> 2;
    int i = 0;
    if (0 < count) {
      do {
        FUN_005b15e0((cSPEditorBlock*)block->mChildBegin[i], other);
        i = i + 1;
      } while (i < count);
    }
  }
}

// @ 0x005b1870
void Sd0::FUN_005b1870(cSPEditorBlock* block, cSPEditorBlock* other, float p3, float p4, float p5, float p6, float p7, float p8)
{
  SPVectorU vec;
  vec.mb = 0;
  vec.me = 0;
  vec.mc = 0;
  void* cur = SP_EditorUtils_FindRootSpine(block->mModel);
  while (cur != 0) {
    if (vec.me < vec.mc) {
      uint32_t* pos = vec.me;
      vec.me = pos + 1;
      if (pos != 0)
        *pos = (uint32_t)cur;
    } else {
      vec.DoInsertValueI(vec.me, (const uint32_t*)&cur);
    }
    cur = FUN_004a5970(cur);
  }
  int count = (int)(vec.me - vec.mb) >> 2;
  int i = 0;
  if (0 < count) {
    do {
      cSPEditorBlock* b = (cSPEditorBlock*)vec.mb[i];
      int cc = (int)(b->mChildEnd - b->mChildBegin) >> 2;
      int j = 0;
      if (0 < cc) {
        do {
          FUN_005b15e0((cSPEditorBlock*)b->mChildBegin[j], other);
          j = j + 1;
        } while (j < cc);
      }
      BBox bb = b->GetBBox(0, 0, 0);
      float rad = SP_EditorUtils_GetSkinRadius(b);
      float cx = (bb.mxx + bb.mnx) * 0.5f;
      float cy = (bb.mxy + bb.mny) * 0.5f;
      float cz = (bb.mxz + bb.mnz) * 0.5f;
      FUN_005b1310(cx, cy, cz, rad, cx, cy, g_1477fbc, rad);
      FUN_005b1310(cx, cy, cz, rad, cx, cy, 0.0f, rad * 0.5f);
      i = i + 1;
    } while (i < count);
  }
  FUN_005b11e0(0.0f, 0.0f, g_1488874, g_15e97f8, g_15e97fc, g_15e9800, false);
  if (block->mModel != 0) {
    float f = block->mModel->FUN_004adaa0();
    FUN_005b11e0(0.0f, f * g_14853e0, 0.0f,
                 -g_15e9874, -g_15e9878, -g_15e987c, true);
    FUN_005b11e0(0.0f, f * g_13f6a28, 0.0f,
                 g_15e9874, g_15e9878, g_15e987c, true);
    FUN_005b11e0(p3 + p6 * f * g_14853e0, p4 + p7 * f * g_14853e0, p5 + p8 * f * g_14853e0,
                 -p6, -p7, -p8, true);
  }
  if (vec.mb != 0 && ((int*)vec.mb)[-1] != 0) {
    FUN_00f47380(vec.mb);
  }
}

// @ 0x005b7460
namespace SP {
void cSPEditorManipulationSpine::Init(cSPEditorBlock_s005b_7460* block, cSPVector3_s005b_7460 mouseOffset, cSPEditorSpine_s005b_7460* spine)
{
  mBlock = block;
  mMouseOffset = mouseOffset;
  mSpine = spine;
}
}  // namespace SP

// @ 0x005b7490
namespace SP {
cSPEditorManipulationSpine::cSPEditorManipulationSpine()
: mBlock(0), mMouseOffset(0.0f, 0.0f, 0.0f), mSpine(0), mModelUsingSymmetry(false) {
  mChangedObject = false;
}
}  // namespace SP

// @ 0x005b74f0
namespace SP {
bool cSPEditorManipulationSpine::OnMouseUp(int button, float x, float y, int modifiers)
{
  if (mBlock && mSpine) {
    cSPVector3_s005b_7460 origin, dir;
    App()->GetViewer()->GetWorldRayFromScreenCoords(x, y, origin, dir);
    origin = origin + mMouseOffset;
    mSpine->MoveBlock(mBlock, origin, dir);
  }
  mBlock->mEditorModel->SetUsingSymmetry(mModelUsingSymmetry);
  return false;
}
}  // namespace SP

// @ 0x005b75e0
namespace SP {
bool cSPEditorManipulationSpine::DoOnMouseDown(int button, float x, float y, int modifiers)
{
  EA::AutoRefCount_s005b_7460<cSPEditorModel_s005b_7460> model(mBlock->mEditorModel);
  mModelUsingSymmetry = model->IsUsingSymmetry();
  model->SetUsingSymmetry(false);
  if (mBlock && mSpine) {
    cSPVector3_s005b_7460 origin, dir;
    App()->GetViewer()->GetWorldRayFromScreenCoords(x, y, origin, dir);
    origin = mMouseOffset + origin;
    mSpine->StartDrag(&mBlock, origin, dir);
    model->SetDirty(true);
    mSpine->Rebuild(true, true);
  }
  return false;
}
}  // namespace SP

// @ 0x005b7720
namespace SP {
bool cSPEditorManipulationSpine::DoOnMouseMove(float x, float y, int modifiers)
{
  if (mBlock && mSpine) {
    cSPVector3_s005b_7460 origin, dir;
    App()->GetViewer()->GetWorldRayFromScreenCoords(x, y, origin, dir);
    origin = origin + mMouseOffset;
    mSpine->Drag(&mBlock, origin, dir);
    if (!mChangedObject)
      mChangedObject = true;
    return true;
  }
  return false;
}
}  // namespace SP

// @ 0x005ba320
namespace SP {
hkRigidBody_s005b_a320* cSPEditorManipulationStacking_s005b_a320::FindStackingTarget(cSPEditorBlock_s005b_a320* block, int mode, cSPVector3_s005b_a320 rayOrigin, cSPVector3_s005b_a320 rayDirection, cSPVector3_s005b_a320* outPosition)
{
    cSPEditorModel_s005b_a320* pModel = block->mEditorModel;
    hkRigidBody_s005b_a320* pBody = block->mpRigidBody;
    if (pBody == 0)
        return 0;

    // Screen-space x extent of the dragged block.
    hkAabb_s005b_a320 aabb;
    pBody->getCollidable()->getShape()->getAabb(pBody->getTransform(), 0.0f, aabb);
    cSPVector3_s005b_a320 corners[8];
    GetAabbCorners(aabb, corners);
    float blockTop = aabb.m_max(2);
    float blockMinX = FLT_MAX_VALUE;
    float blockMaxX = FLT_MIN_VALUE;
    for (int i = 0; i < 8; ++i) {
        cSPVector3_s005b_a320 p = App_s005b_a320()->GetCamera()->WorldToProjection(corners[i]);
        if (blockMinX > p.x) blockMinX = p.x;
        if (p.x > blockMaxX) blockMaxX = p.x;
    }
    cSPVector3_s005b_a320 blockScreenPos = App_s005b_a320()->GetCamera()->WorldToProjection(block->mPosition);

    BlockList candidates;
    GetStackCandidates(block, mode, &candidates);
    int bestIndex = -1;
    if (!candidates.empty()) {
        int count = (int)candidates.size();
        cSPVector3_s005b_a320 horizontal(rayDirection.x, rayDirection.y, 0.0f);
        eastl::vector_s005b_a320<cSPVector3_s005b_a320> hits;
        hits.resize(count);
        float bestScore = FLT_MAX_VALUE;
        for (int i = 0; i < count; ++i) {
            cSPEditorBlock_s005b_a320* candidate = candidates[i];
            cSPVector3_s005b_a320 position(candidate->mPosition);
            if (candidate == mBlock)
                position = mTargetPosition;

            // vertical plane through the candidate, facing the camera
            cSPPlane plane(-horizontal, position);
            float denom = plane.mNormal.Dot(rayDirection);
            if (denom == 0.0f)
                continue;
            float t = -((plane.mNormal.Dot(rayOrigin) + plane.mD) / denom);
            if (t >= 0.0f) {
                hits[i] = rayOrigin + rayDirection * t;
                cSPVector3_s005b_a320& hit = hits[i];
                float dx = hit.x - block->mPosition.x;
                float dy = hit.y - block->mPosition.y;
                float distToBlock = (float)sqrt(dx * dx + dy * dy);

                cSPVector3_s005b_a320 candCorners[8];
                float candTop;
                if (candidates[i]->mpRigidBody) {
                    hkRigidBody_s005b_a320* body = candidates[i]->mpRigidBody;
                    hkAabb_s005b_a320 candAabb;
                    body->getCollidable()->getShape()->getAabb(body->getTransform(), 0.0f, candAabb);
                    GetAabbCorners(candAabb, candCorners);
                    candTop = candAabb.m_max(2);
                } else {
                    cSPBoundingBox box;
                    candidates[i]->GetBBox(&box, 0, 0, 0);
                    cSPBoundingBox_GetCorners(box, candCorners);
                    candTop = box.mMax.z;
                }
                float ex = hit.x - position.x;
                float ey = hit.y - position.y;
                float distToCandidate = (float)sqrt(ex * ex + ey * ey);
                float heightDiff = (float)fabs(candTop - blockTop);

                float minX = FLT_MAX_VALUE;
                float maxX = FLT_MIN_VALUE;
                for (int k = 0; k < 8; ++k) {
                    cSPVector3_s005b_a320 p = App_s005b_a320()->GetCamera()->WorldToProjection(candCorners[k]);
                    if (minX > p.x) minX = p.x;
                    if (p.x > maxX) maxX = p.x;
                }
                float overlap = maxX - minX + blockMaxX - blockMinX
                              - (max_alt(maxX, blockMaxX) - min_alt(minX, blockMinX));
                if (overlap > 0.0f) {
                    float score = (heightDiff + distToCandidate + distToBlock) / overlap;
                    if (bestScore > score) {
                        bestScore = score;
                        bestIndex = i;
                    }
                }
            }
        }

        if (bestIndex != -1) {
            cSPVector3_s005b_a320* bestHit = &hits[bestIndex];
            cSPVector3_s005b_a320 start(*bestHit);
            start.z = pModel->GetGridSize() * 0.05f + start.z;
            cSPVector3_s005b_a320 down = -kSPUpAxis;
            cSPEditorModel_s005b_a320* model = block->mEditorModel;
            model->NumberBlocks();
            hkRigidBody_s005b_a320* rb = block->mpRigidBody;
            if (rb == 0)
                return 0;
            hkVector4_s005b_a320 savedPosition(rb->getPosition());
            PrepareBlockForStacking(block, mode, 0, 1, 1);
            model->GetPhysicsWorld()->SetFloorFilter(true);

            hkLinearCastInput_s005b_a320 input;
            cSPVector3_s005b_a320 to = start + down * 20.0f;
            input.m_to = hkVector4_s005b_a320(to.x, to.y, to.z, 0.0f);
            rb->setPosition(hkVector4_s005b_a320(start.x, start.y, start.z, 0.0f));
            rb->getCollidable()->getShape()->getMaximumProjection(hkVector4_s005b_a320(0.0f, 0.0f, -1.0f, 0.0f));

            hkAllCdPointCollector_s005b_a320 collector;
            model->GetPhysicsWorld()->World()->linearCast(block->mpRigidBody->getCollidable(), input, collector);

            bool found = false;
            if (collector.getHits().getSize() > 0) {
                collector.sortPoints();
                hkRigidBody_s005b_a320* foundBody = 0;
                cSPVector3_s005b_a320 foundPosition;
                eastl::vector_s005b_a320<hkRigidBody_s005b_a320*> visited;
                int numHits = collector.getHits().getSize();
                hkAabb_s005b_a320 rbAabb;
                rb->getCollidable()->getShape()->getAabb(hkTransform_s005b_a320::getIdentity(), 0.0f, rbAabb);
                hkTransform_s005b_a320 rbTransform(rb->getTransform());
                for (int i = 0; i < numHits; ++i) {
                    hkRootCdPoint_s005b_a320& pt = collector.getHits()[i];
                    hkRigidBody_s005b_a320* hitBody = (hkRigidBody_s005b_a320*)pt.m_rootCollidableB->getOwner();
                    hkContactPoint_s005b_a320 contact(pt.m_contact);
                    int n = (int)visited.size();
                    int j;
                    for (j = 0; j < n; ++j)
                        if (visited[j] == hitBody)
                            break;
                    if (j < n)
                        continue;
                    visited.push_back(hitBody);

                    hkVector4_s005b_a320 contactPos(contact.getPosition());
                    hkVector4_s005b_a320 localPos;
                    localPos.setTransformedInversePos(rbTransform, contactPos);

                    float fraction = contact.getDistance();
                    cSPVector3_s005b_a320 castTo(input.m_to(0), input.m_to(1), input.m_to(2));
                    cSPVector3_s005b_a320 p = castTo * fraction + start * (1.0f - fraction);

                    hkAabb_s005b_a320 hitAabb;
                    hitBody->getCollidable()->getShape()->getAabb(hkTransform_s005b_a320::getIdentity(), 0.0f, hitAabb);
                    if (fabs((rbAabb.m_min(2) + p.z) - (hitBody->getPosition()(2) + hitAabb.m_max(2)))
                        < gStackingHeightTolerance) {
                        float drop = bestHit->z - p.z;
                        float stackOffset = pModel->GetGridSize() * 0.05f;
                        if (drop < stackOffset * 3.0f) {
                            foundPosition = p;
                            foundBody = hitBody;
                            found = true;
                            break;
                        }
                    }
                }
                model->NumberBlocks();
                rb->setPosition(savedPosition);
                if (found && foundBody && foundBody != rb) {
                    *outPosition = foundPosition;
                    return foundBody;
                }
            }
        }
    }
    return 0;
}
}  // namespace SP

// @ 0x005bc0f0
namespace SP {
bool cSPEditorManipulationStacking::DoOnMouseMove(float x, float y, int flags)
{
  cSPEditorBlock_s005b_c0f0* block = mpBlock;
  if (!block)
    return false;

  if ((mLastX != x || mLastY != y) && !mChangedObject)
    mChangedObject = true;
  mLastX = x;
  mLastY = y;
  mLastFlags = flags;

  cSPVector3_s005b_c0f0 startPos = block->mPosition;
  cSPEditorModel_s005b_c0f0* model = block->mpModel;

  cSPVector3_s005b_c0f0 origin, dir;
  App_s005b_c0f0()->GetViewer()->GetWorldRayFromScreenCoords(x, y, &origin, &dir);

  origin.x = origin.x + mMouseOffset.x;
  origin.y = origin.y + mMouseOffset.y;
  origin.z = origin.z + mMouseOffset.z;

  cSPVector3_s005b_c0f0 snapped;
  cSPEditorBlock_s005b_c0f0* hit = FUN_004a3dc0(block, &mPileList, origin, dir, &snapped);
  if (hit) {
    if (hit == block->mpParent)
      return true;

    mPosition = snapped;
    cSPVector3_s005b_c0f0 delta;
    delta.x = startPos.x - snapped.x;
    delta.y = startPos.y - snapped.y;
    delta.z = startPos.z - snapped.z;

    SnapBlockToSocket(block, &mPileList, hit);

    mMouseOffset.x = mMouseOffset.x + delta.x;
    mMouseOffset.y = mMouseOffset.y + delta.y;
    mMouseOffset.z = mMouseOffset.z + delta.z;

    SetSymmetricBlocksUIState(block, &mPileList, 0);
    FUN_004a6d20(block, &mPileList, 1, 0, 0, 0, 1, 1);
  } else {
    if ((block->mFlagsA >> 12) & 1)
      FUN_004a1070(block);

    int socket = MoveBlockStacking(block, &mPileList, origin, dir);
    if (model) {
      if (socket == 0 || model->GetPhysicsWorld()->mpFloorBody != (void*)socket) {
        block->SetIsOnGround(false);
      } else {
        block->mbOnFloor = 1;
        if (block->mpSymmetric)
          block->mpSymmetric->mbOnFloor = 1;
      }
    }

    float scale = g_defaultBlockScale;
    if (block->mpModel)
      scale = block->mpModel->GetScale() * g_stackScaleFactor;
    bool positioned = FUN_004982b0(block, 0, scale, 1);

    mPosition = block->mPosition;

    if (!positioned) {
      bool flagC = block->Unk43bbc0(0);
      cSPMatrix3 outRot;
      float score = GetAlignmentPosition(block, &mPileList, startPos, block->mBaseOrientation,
                                        &mPosition, &outRot, &flagC, 1, block->mBaseOrientation);
      if (score == g_minusOne) {
        if (mAlignmentState) {
          KillSeti(g_killSetAlignmentOff);
          mAlignmentState = false;
        }
      } else if (!mAlignmentState) {
        KillSeti(g_killSetAlignmentOn);
        mAlignmentState = true;
      }

      if (score == g_minusOne || score <= g_alignmentEpsilon) {
        block->SetPosition(startPos, true);
      } else {
        block->SetPosition(mPosition, true);
        block->SetIsOnGround(flagC);
      }
    }

    FUN_00496300(block, &mPileList, origin, dir, startPos, 0);
    SetSymmetricBlocksUIState(block, &mPileList, 0);
    FUN_004a6d20(block, &mPileList, 1, 0, 0, 0, 1, 1);

    if ((block->mFlagsA >> 15) & 1)
      SetSymmetricBlocksUIState(block, &mPileList, 0);
  }
  return true;
}
}  // namespace SP

// @ 0x005bdca0
CSpEditorManip* CSpEditorManip::init()
{
  FUN_005b0f80(this);                       // SP::cSPEditorManipulationObject::ctor
  vt14 = (void*)0x013ec458;                 // vtbl_cContentValidationSummarizer
  f18 = 0;
  vt00 = (void*)0x013f796c;
  vt14 = (void*)0x013f795c;
  f1c = 0; f20 = 0; f24 = 0; f28 = 0; f2c = 0;
  f38 = 0;
  f3c = 0.0f; f40 = 0.0f; f44 = 0.0f;
  float c0 = F_013f7944;
  f50 = 0; f54 = 0; f58 = 0;
  int head = (int)this + 0x4c;
  f50 = head;
  f4c = head;
  f54 = 0;
  *(char*)&f58 = 0;
  f5c = 0;
  f64 = c0; f68 = c0; f6c = c0;
  float c1 = F_013f51ac;
  f70 = c1; f74 = c1; f78 = c1;
  f04 = 0;
  return this;
}
