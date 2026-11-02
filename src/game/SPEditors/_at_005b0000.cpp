// src/game/SPEditors/_at_005b0000.cpp -- migrated from slice(s) s005bdca0, s005bc0f0, s005b7460, s005b0f80 by tools/migrate/rewrite.py
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

// unnamed retail callees and globals (address in the comment)
extern float g_1477fbc;                                  // 0x1477fbc (~200.0f)
extern float g_14853e0;                                  // 0x14853e0 (4.0f)
extern float g_13f6a28;                                  // 0x13f6a28 (-4.0f)
extern float g_15e97f8, g_15e97fc, g_15e9800;            // 0x15e97f8.. (direction)
extern float g_1488874;                                  // 0x1488874
extern float g_15e9874, g_15e9878, g_15e987c;            // 0x15e9874.. (direction)

// ---- items of slice s005b0f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
void* __cdecl SP_EditorUtils_FindRootSpine(cSPEditorModel* model);        // 0x4a5a70
void* __cdecl FUN_004a5970(void* block);                                  // 0x4a5970
float __cdecl SP_EditorUtils_GetSkinRadius(void* block);                  // 0x4a5c40
void __cdecl FUN_00f47380(void* p);                                       // 0xf47380 (operator delete)
extern float g_1477fbc;                                  // 0x1477fbc (~200.0f)
extern float g_14853e0;                                  // 0x14853e0 (4.0f)
extern float g_13f6a28;                                  // 0x13f6a28 (-4.0f)
extern float g_15e97f8, g_15e97fc, g_15e9800;            // 0x15e97f8.. (direction)
extern float g_1488874;                                  // 0x1488874
extern float g_15e9874, g_15e9878, g_15e987c;            // 0x15e9874.. (direction)
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

// @ 0x005b1080
S80::S80(float a, float b, float c, float d, float e, float f)
: m0(a), m1(b), m2(c), m3(d), m4(e), m5(f), m18(false) {}

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
