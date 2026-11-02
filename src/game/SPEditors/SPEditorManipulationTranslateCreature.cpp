// src/game/SPEditors/SPEditorManipulationTranslateCreature.cpp -- migrated from slice(s) s005beaf0, s005bdca0, s005bccc0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorManipulationTranslateCreature.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorAnimatedEventInfo.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorPhysicsWorld.h"
#include "SP/cSPEditorSpine.h"
#include "SP/cViewer.h"
#include <math.h>
#include <string.h>
#include <new>
#include <float.h>

// ---- items of slice s005bccc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t n, const char* name, int a, int b, int c, int d);   // EA 6-arg operator new (0x00f473a0)
void* operator new(size_t n, const char* name, int a, int b, const char* file, int line);
void RBTreeInsert(void* node, void* parent, void* anchor, int side);   // 0x009216a0
void operator_delete__(void* p);                                              // 0x00f47380
struct Vec3 { float x, y, z; Vec3() {} Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; } };
typedef Vec3 Vec3C;
inline void* operator new(size_t, void* p, int) { return p; }
struct Mat3 {                       // 3x3 float matrix, by-value copies go through Matrix3::Assign (0x0041cb40)
    float m[9];
    Mat3() {}
    Mat3(const Mat3& o) { Assign(o); }
    void Assign(const Mat3& o);     // @ 0x0041cb40
};
class hkVector4_s005b_ccc0 { public: float x, y, z, w; };
class hkMotionState { public: char pad[0x40]; Vec3 pos; };                 // position at +0x40
class hkRigidBody_s005b_ccc0 { public:
    char pad[0x1c];
    char collidable[0x3c];          // +0x1c
    hkMotionState* mpMotion;        // +0x58
    void setPosition(const hkVector4_s005b_ccc0& p);   // @ 0x01087820
};
struct hkLinearCastInput_s005b_ccc0 {          // at +0x90 of the frame
    hkVector4_s005b_ccc0 to;
    float maxExtraPenetration;
    float startPointTolerance;
};
struct CdCollector {                // closest-point collector at +0xd0 of the frame
    void* vptr;                     // 0x013ef52c
    float earlyOutDistance;
    char pad[0x24];
    float hitFraction;              // +0x2c
    int numHits;                    // +0x30
    char pad2[4];
    int* hitBody;                   // +0x38
};
class hkWorld_s005b_ccc0 { public:
    void linearCast(void* collidable, hkLinearCastInput_s005b_ccc0* in, CdCollector* collector, void* startCollector);   // @ 0x01082b90
};
struct cSPEditorPhysicsWorld_s005b_ccc0 {
    char pad[0xc];
    int* mpFloorBody;               // +0xc
    hkWorld_s005b_ccc0* World();               // @ 0x004b91c0
    void SetDefaultFloorFilter();   // @ 0x004b9470
    void UpdateCollisionFilters();  // @ 0x004b9420
};
struct RefCountV {                  // EA::RefCountVTemplate<int> sub-object (vptr + count)
    virtual ~RefCountV() {}
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    __forceinline int Release()
    {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) {
            mnRefCount = 1;
            delete this;
        }
        return n;
    }
};
struct cSPEditorModel_s005b_ccc0 {
    virtual void v0();
    RefCountV rc;                   // +4 vptr, +8 count
    char pad0[0x24];
    void AddRef() { rc.AddRef(); }
    cSPEditorPhysicsWorld_s005b_ccc0* GetWorld();   // @ 0x004ad450
    void SetFlag(int v);                 // @ 0x004ad470
    void SetColliding(bool b);           // @ 0x004adc20
    bool IsColliding();                  // @ 0x004adc40
    float GetScale();                    // @ 0x004adaa0
};
struct cSPEditorSpine_s005b_ccc0 {
    virtual void v0();
    virtual int AddRef();           // +4
    virtual int Release();          // +8
    char pad[0xe8 - 4];
    int mnVertebrae;                // +0xe8
    void Prepare();                 // @ 0x005d2790
    void Update(int a, cSPEditorModel_s005b_ccc0* m);   // @ 0x005d07f0
};
struct cSPEditorBlock_s005b_ccc0 {
    char pad0[0x28];
    cSPEditorModel_s005b_ccc0* mpModel;        // +0x28
    char pad1[0x48 - 0x2c];
    Vec3 mPosition;                 // +0x48
    char pad2[0x60 - 0x54];
    Mat3 mOrientation;              // +0x60
    char pad3[0xa8 - 0x84];
    Mat3 mBaseOrientation;          // +0xa8
    char pad4[0x18c - 0xcc];
    hkRigidBody_s005b_ccc0* mpBody;            // +0x18c
    char pad5[0x33c - 0x190];
    cSPEditorBlock_s005b_ccc0* mpParent;       // +0x33c
    char pad6[0x3c9 - 0x340];
    char mbOnFloor;                 // +0x3c9
    char pad7[0x3e0 - 0x3ca];
    cSPEditorBlock_s005b_ccc0* mpSymmetric;    // +0x3e0
    char pad8[0xdc8 - 0x3e4];
    uint32_t mFlagsA;               // +0xdc8
    uint32_t mFlagsB;               // +0xdcc
    void GetBBox(float* out6, int a, int b, int c);      // @ 0x0044ae00
    int GetSymmetryIndex();                                // @ 0x0044f220
    int CalculateSymmetrySign();                           // @ 0x0044f240
    void SetModelBasedOnSymmetrySign(int sign, int a, int b, int c, int d);   // @ 0x00439110
    void RecursiveFlagA();                                 // @ 0x0044ede0
    char Unk43bbc0(int a);                                 // @ 0x0043bbc0
    void DetachFrom(cSPEditorBlock_s005b_ccc0* b);                    // @ 0x00438a40 (called on the parent)
};
struct IAnimEvent {                 // cSPEditorAnimatedEventInfo (refcounted message)
    virtual void v0();
    virtual int AddRef();           // +4
    virtual int Release();          // +8
    IAnimEvent* Construct();        // @ 0x0059d960
    void MessagePost(uint32_t id, int a, void* obj, int b, int c, float d, int e, int f, float g);   // @ 0x0059d840
};
namespace EditorUtils {
    void DeleteInvalidBlocks(int count, int flag);                     // 0x004a6f10
}
struct cViewer_s005b_ccc0 {
    void GetWorldRayFromScreenCoords(float x, float y, Vec3* origin, Vec3* dir);   // 0x007c4730
};
struct cIAppViewer {                 // cIApp: GetViewer is vtable slot 22 (+0x58)
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
    virtual cViewer_s005b_ccc0* GetViewer();    // +0x58
};
namespace SP {
    cIAppViewer* App();              // 0x0067dd10
}
namespace SP {
    inline cViewer_s005b_ccc0* GetViewer() { return App()->GetViewer(); }
}
namespace SP {
struct cLimb { void Unk48a4c0(); };   // @ 0x0048a4c0
}
namespace SP {
struct cSPEditorManipulationBase { virtual ~cSPEditorManipulationBase() {} char pad[0x10]; };
}
namespace SP {
struct cRefCountBase { virtual ~cRefCountBase() {} int mnRefCount; };
}
namespace SP {
struct PosMapAnchor {
    uint32_t right, left, parent, color;
};
}
namespace SP {
struct PosMap {                        // eastl::map<cSPEditorBlock*, Vec3>: rbtree at +0
    uint32_t pad0;
    PosMapAnchor anchor;               // +4
    uint32_t mnSize;                   // +0x14
    char pad18[0x1c - 0x18];
    ~PosMap() { DoNukeSubtree((void*)anchor.parent); }
    void DoNukeSubtree(void* node);   // @ 0x009a9600 (rbtree::DoNukeSubtree)
    struct Value { uint32_t key; Vec3C v; Value() {} Value(const Value& o) : key(o.key), v(o.v) {} };
    struct Iter { void* node; };
    Iter* DoInsertValueImpl(Iter* out, void* hint, const Value* v, bool bForceToLeft);   // 0x005bdb60
};
}
namespace SP {
struct ModelRef {                      // EA::AutoRefCount<cSPEditorModel>
    cSPEditorModel_s005b_ccc0* mpObject;
    ~ModelRef() { if (mpObject) mpObject->rc.Release(); }
    ModelRef& operator=(cSPEditorModel_s005b_ccc0* p)
    {
        if (p != mpObject) {
            cSPEditorModel_s005b_ccc0* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->rc.Release();
        }
        return *this;
    }
};
}
namespace SP {
struct SpineRef {                      // EA::AutoRefCount<cSPEditorSpine>
    cSPEditorSpine_s005b_ccc0* mpObject;
    ~SpineRef() { if (mpObject) mpObject->Release(); }
    SpineRef& operator=(cSPEditorSpine_s005b_ccc0* p)
    {
        if (p != mpObject) {
            cSPEditorSpine_s005b_ccc0* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
}
namespace SP {
struct cSPVec { cSPEditorBlock_s005b_ccc0** mpBegin; cSPEditorBlock_s005b_ccc0** mpEnd; cSPEditorBlock_s005b_ccc0** mpCapacity;
                ~cSPVec() { if (mpBegin && ((int*)mpBegin)[-1]) operator_delete__(mpBegin); } };
}
namespace SP {
class cSPEditorManipulationTranslateCreature : public cSPEditorManipulationBase, public cRefCountBase {
 public:
  ModelRef mModel;                   // +0x1c
  SpineRef mSpine;                   // +0x20
  cSPVec mLimbs;                     // +0x24
  char pad30[0x38 - 0x30];
  bool mModelUsingSymmetry;          // +0x38
  char pad39[3];
  Vec3 mOriginalPlanarPosition;      // +0x3c
  PosMap mOriginalPositions;         // +0x48

  // @ 0x005bd650
  bool OnMouseUp(int a, int b, int c, int d);
  // @ 0x005bd750
  void SetTargets(cSPEditorModel_s005b_ccc0* model, cSPEditorSpine_s005b_ccc0* spine);
  // @ 0x005bd7c0
  Vec3* PickPlaneOfSymmetry(Vec3* out, float x, float y, float unused);
  // @ 0x005bdad0
  ~cSPEditorManipulationTranslateCreature();
};
}
// ---- items of slice s005bccc0 end

// ---- items of slice s005beaf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
class Vector3Template_s005b_eaf0 {
 public:
  T x, y, z;
  Vector3Template_s005b_eaf0() {}
  Vector3Template_s005b_eaf0(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005b_eaf0<T, N> operator+(const Vector3Template_s005b_eaf0<T, N>& a, const Vector3Template_s005b_eaf0<T, N>& b) {
  return Vector3Template_s005b_eaf0<T, N>(a.x + b.x, a.y + b.y, a.z + b.z);
}
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005b_eaf0<T, N> operator-(const Vector3Template_s005b_eaf0<T, N>& a, const Vector3Template_s005b_eaf0<T, N>& b) {
  return Vector3Template_s005b_eaf0<T, N>(a.x - b.x, a.y - b.y, a.z - b.z);
}
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline Vector3Template_s005b_eaf0<T, N> operator*(const Vector3Template_s005b_eaf0<T, N>& a, T s) {
  return Vector3Template_s005b_eaf0<T, N>(a.x * s, a.y * s, a.z * s);
}
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
inline T Dot(const Vector3Template_s005b_eaf0<T, N>& a, const Vector3Template_s005b_eaf0<T, N>& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
}
}
}
struct cSPVector3_s005b_eaf0 : public rw::math::fpu::Vector3Template_s005b_eaf0<float, 0> {
  typedef rw::math::fpu::Vector3Template_s005b_eaf0<float, 0> base;
  cSPVector3_s005b_eaf0() {}
  cSPVector3_s005b_eaf0(float ax, float ay, float az) : base(ax, ay, az) {}
  cSPVector3_s005b_eaf0(const cSPVector3_s005b_eaf0& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3_s005b_eaf0(const base& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3_s005b_eaf0& operator=(const base& v) { x = v.x; y = v.y; z = v.z; return *this; }
  float Dot(const cSPVector3_s005b_eaf0& o) const { return x * o.x + y * o.y + z * o.z; }
};
struct cSPMatrix3_s005b_eaf0 { float m[9]; };
struct cSPBoundingBox_s005b_eaf0 {
  cSPVector3_s005b_eaf0 mMin;  // +0x0
  cSPVector3_s005b_eaf0 mMax;  // +0xc
  cSPBoundingBox_s005b_eaf0(const cSPVector3_s005b_eaf0& mn, const cSPVector3_s005b_eaf0& mx) { mMin = mn; mMax = mx; }
};
namespace EA {
template <typename T>
class AutoRefCount_s005b_eaf0 {
 public:
  T* mpObject;
  AutoRefCount_s005b_eaf0() : mpObject(0) {}
  AutoRefCount_s005b_eaf0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005b_eaf0() { if (mpObject) mpObject->Release(); }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
  T*& AsOutParam() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return mpObject;
  }
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005b_eaf0 {
 public:
  virtual ~RefCountVTemplate_s005b_eaf0() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
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
  sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector() {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  T* DoInsertValue(T* position, const T& value);
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};  // namespace eastl
}
namespace SP {
class cSPEditorBlock_s005b_eaf0 {
 public:
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  char pad04[0x48 - 4];
  cSPVector3_s005b_eaf0 mPosition;                 // +0x48
  cSPVector3_s005b_eaf0 mHistoryPosition;          // +0x54
  cSPMatrix3_s005b_eaf0 mOrientation;              // +0x60
  cSPMatrix3_s005b_eaf0 mHistoryOrientation;       // +0x84
  cSPMatrix3_s005b_eaf0 mBaseOrientation;          // +0xa8
  cSPMatrix3_s005b_eaf0 mHistoryBaseOrientation;   // +0xcc
};
}
namespace SP {
class cSPEditorModel_s005b_eaf0 {
 public:
  void SetUsingSymmetry(bool b);         // FUN_004adc20
  bool IsUsingSymmetry();                // FUN_004adc40
  int GetNumBlocks();                    // FUN_004accf0
  cSPEditorBlock_s005b_eaf0* GetBlock(int index);   // FUN_004accb0
};
}
namespace SP {
class cSPEditorSpine_s005b_eaf0 {
 public:
  void Rebuild(bool a, bool b);  // FUN_005d1600
};
}
namespace SP {
class cSPEditorLimbStructure_s005b_eaf0 {
 public:
  cSPEditorLimbStructure_s005b_eaf0();                                   // FUN_00488850
  void Init(cSPEditorBlock_s005b_eaf0* limbRoot, int a, int b);          // FUN_004891a0
  char pad[0x54];
};
}
namespace SP {
namespace EditorUtils {
void GetAllLimbs(cSPEditorBlock_s005b_eaf0* root, eastl::sp_vector<cSPEditorBlock_s005b_eaf0*>& limbs, int flags);
}
}
namespace SP {
class BlockPositionMap {
 public:
  cSPVector3_s005b_eaf0& operator[](cSPEditorBlock_s005b_eaf0* const& key);  // FUN_005bded0
  char pad[0x1c];
};
}
namespace SP {
class cSPEditorManipulationObject_s005b_eaf0 {
 public:
  virtual ~cSPEditorManipulationObject_s005b_eaf0() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};
}
namespace SP {
class cSPEditorManipulationTranslateCreature_s005b_eaf0 : public cSPEditorManipulationObject_s005b_eaf0, public EA::RefCountVTemplate_s005b_eaf0<int> {
 public:
  cSPEditorModel_s005b_eaf0* mModel;                                  // +0x1c (AutoRefCount)
  cSPEditorSpine_s005b_eaf0* mSpine;                                  // +0x20 (AutoRefCount)
  eastl::sp_vector<cSPEditorLimbStructure_s005b_eaf0*> mLimbs;        // +0x24
  bool mModelUsingSymmetry;                                // +0x38
  cSPVector3_s005b_eaf0 mOriginalPlanarPosition;                      // +0x3c
  BlockPositionMap mOriginalPositions;                     // +0x48
  cSPBoundingBox_s005b_eaf0 mCurrModelBounds;                         // +0x64

  cSPVector3_s005b_eaf0 PickPlaneOfSymmetry(float x, float y, bool b);  // 0x005bd7c0 (SP::cSPEditorManipulationTranslateCreature::PickPlaneOfSymmetry)
  void CalcBoundsForMovement(const cSPVector3_s005b_eaf0& delta, cSPBoundingBox_s005b_eaf0& bounds, cSPBoundingBox_s005b_eaf0& limits, bool b);  // FUN_005bdf70
  bool DoOnMouseDown(int button, float x, float y, int modifiers);
};
}
// ---- items of slice s005beaf0 end

// ---- items of slice s005bdca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" const float F_013f7944;        // 0x013f7944  FLT_MAX
extern "C" const float F_013f51ac;        // 0x013f51ac  -FLT_MAX
extern "C" const float G_015eabf4[9];     // 0x015eabf4  orientation basis table
extern "C" void* memcpy(void*, const void*, unsigned int);  // 0x011e0744
typedef unsigned int uint;
typedef unsigned char uchar;
void FUN_00454280(void* a, void* b);                 // 0x00454280
int  FUN_00435d40();                                 // 0x00435d40  Entity::HasAnyBlockFlag
int  FUN_004a6270(void* block);                      // 0x004a6270  SP::EditorUtils::IsLimbPart
void FUN_00454ee0(void* end, void* value);           // 0x00454ee0
int  FUN_004accf0();                                 // 0x004accf0  cSPEditorModel::GetBlockCount
void* FUN_004accb0(uint i);                          // 0x004accb0  cSPEditorModel::GetBlock
char FUN_004adaa0();                                 // 0x004adaa0
float FUN_004adb00();                                // 0x004adb00
float FUN_004adb40();                                // 0x004adb40
void FUN_00448e90(void* p, int n);                   // 0x00448e90  cSPEditorBlock::SetPosition
char FUN_004adc40();                                 // 0x004adc40  cSPEditorModel::UsingSymmetry
void FUN_004adc20(uint x);                           // 0x004adc20
void* FUN_007f99a0();                                // 0x007f99a0
void FUN_004890e0(int x);                            // 0x004890e0
void FUN_00489ae0();                                 // 0x00489ae0
void FUN_004a6d20(int* vertebrae, int a, int b, int c,
                  int d, int e, int f, int g);       // 0x004a6d20
void FUN_00409dd0(void* box, const void* xform);     // 0x00409dd0  BoundingBox_TransformBy
void FUN_005ce680(void* spine, float a, uchar* p,
                  float* out);                       // 0x005ce680  CalcVertebraPhysicsBoundingBox
void FUN_0049fbd0(void* block, const float* vec,
                  const float* mat, int flag);       // 0x0049fbd0  RepinBlockToTorso
void FUN_005bdd90(void* key, void* parent, void* val, uint flag);  // 0x005bdd90
void FUN_00f47380(void* p);                          // 0x00f47380  operator delete
void* FUN_0044ae00(void* blk, int a, int b);         // 0x0044ae00  cSPEditorBlock::GetBBox
void* FUN_005bd7c0(void* self, void* out, float a,
                   float b, float c);                // 0x005bd7c0  PickPlaneOfSymmetry
struct cSPEditorBlock {
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
};
struct cSPEditorLimbStructure {
  void Release();                 // 0x00488980
  void Destroy();                 // 0x00488900
};
struct cSPEditorManipulationTranslateCreature_s005b_dca0 {
  char  pad04[0x04];
  int   mMapHead[4];              // +0x04
  char  pad14[0x0c];
  void* mSpine;                   // +0x20
  void* mLimbsBegin;              // +0x24
  void* mLimbsEnd;                // +0x28
  void* mLimbsCap;                // +0x2c
  void* mModel;                   // +0x30
  void* mOrigPosBegin;            // +0x38 (heading used by 005be500)
  float mOrigPlanar_x;            // +0x48
  float mOrigPlanar_y;            // +0x4c
  float mOrigPlanar_z;            // +0x50
  float mCurrBounds[6];           // +0x54  min.xyz max.xyz
  char  pad6c[0x18];
  int   mChangedObject;           // +0xa4 (byte)
  void  fn5de60();                // 0x005bde60
  float* fn5ded0(float* key);     // 0x005bded0
  void  CalcBoundsForMovement(float* offset, float* boxA,
                              float* boxB, void* vec);      // 0x005bdf70
  uint  fn5e500(float a, float b);                          // 0x005be500
};
struct cSPVector3_s005b_dca0 { float x, y, z; };
struct cSPBoundingBox_s005b_dca0 { cSPVector3_s005b_dca0 mMin; cSPVector3_s005b_dca0 mMax; };
// ---- items of slice s005bdca0 end

// @ 0x005bd650
namespace SP {
bool cSPEditorManipulationTranslateCreature::OnMouseUp(int, int, int, int)
{
    if (mModel.mpObject)
        mModel.mpObject->SetColliding(mModelUsingSymmetry);
    if (mSpine.mpObject) {
        mSpine.mpObject->Prepare();
        mSpine.mpObject->Update(0, mModel.mpObject);
    }
    bool colliding = mModel.mpObject->IsColliding();
    mModel.mpObject->SetColliding(false);
    int n = (int)(mLimbs.mpEnd - mLimbs.mpBegin);
    for (int i = 0; i < n; i++)
        ((cLimb*)mLimbs.mpBegin[i])->Unk48a4c0();
    mModel.mpObject->SetColliding(colliding);
    ::EditorUtils::DeleteInvalidBlocks(mSpine.mpObject->mnVertebrae, 0);
    IAnimEvent* evt;
    void* mem = operator new(0x30, "Editor", 0, 0, 0, 0);
    evt = mem ? ((IAnimEvent*)mem)->Construct() : 0;
    if (evt)
        evt->AddRef();
    evt->MessagePost(0xd77440ff, 0, mModel.mpObject, 0, 0, 0.0f, 0, -1, 1.0f);
    if (evt)
        evt->Release();
    return false;
}
}  // namespace SP

// @ 0x005bd750
namespace SP {
void cSPEditorManipulationTranslateCreature::SetTargets(cSPEditorModel_s005b_ccc0* model, cSPEditorSpine_s005b_ccc0* spine)
{
    mModel = model;
    mSpine = spine;
}
}  // namespace SP

// @ 0x005bd7c0
namespace SP {
Vec3* cSPEditorManipulationTranslateCreature::PickPlaneOfSymmetry(Vec3* out, float x, float y, float)
{
    Vec3 o, d;
    SP::GetViewer()->GetWorldRayFromScreenCoords(x, y, &o, &d);

    // direction to the origin in the ground plane
    float inv = 1.0f / sqrtf((-o.x) * (-o.x) + (-o.y) * (-o.y));
    float nx = -o.x * inv;
    float ny = -o.y * inv;
    float dotx = fabsf((inv * 0.0f + ny) * 0.0f + nx);

    Vec3 n;                              // candidate plane normal
    n.x = 1.0f; n.y = 0.0f; n.z = 0.0f;
    if (dotx < 0.5f) {
        float s = 1.0f;
        if ((o.x > 0.0f && o.y < 0.0f) || (o.x < 0.0f && o.y > 0.0f))
            s = -1.0f;
        float t = dotx * 2.0f;
        n.x = t;
        n.y = -s * t + s;
        n.z = t * 0.0f;
    }
    Vec3 p = mOriginalPlanarPosition;
    *out = p;
    float denom = d.x * n.x + d.y * n.y + d.z * n.z;
    if (denom != 0.0f) {
        float t = -((o.x * n.x + o.y * n.y + o.z * n.z) - (p.x * n.x + p.y * n.y + p.z * n.z)) / denom;
        if (t >= 0.0f) {
            out->x = 0.0f;
            out->y = d.y * t + o.y;
            out->z = d.z * t + o.z;
            return out;
        }
    }
    // second try: horizontal plane through the original position
    float denom2 = (d.y + d.x) * 0.0f + d.z;
    if (denom2 != 0.0f) {
        float t = -(((o.y + o.x) * 0.0f + ((p.y + p.x) * -0.0f - p.z)) + o.z) / denom2;
        if (t >= 0.0f) {
            out->x = 0.0f;
            out->y = d.y * t + o.y;
            out->z = d.z * t + o.z;
        }
    }
    return out;
}
}  // namespace SP

// @ 0x005bdad0
namespace SP {
cSPEditorManipulationTranslateCreature::~cSPEditorManipulationTranslateCreature()
{
    // members are destroyed in reverse order: mOriginalPositions, mLimbs, mSpine, mModel
}
}  // namespace SP

// @ 0x005bdb60
namespace SP {
PosMap::Iter* PosMap::DoInsertValueImpl(Iter* out, void* hint, const Value* v, bool bForceToLeft)
{
    int side;                          // RBTreeSide: left = 0, right = 1
    if (bForceToLeft || hint == (void*)&anchor || v->key < *(uint32_t*)((char*)hint + 0x10))
        side = 0;
    else
        side = 1;
    char* node = (char*)operator new(0x20, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (node + 0x10, 0) Value(*v);
    RBTreeInsert(node, hint, &anchor, side);
    mnSize++;
    out->node = node;
    return out;
}
}  // namespace SP

// @ 0x005bde60
void cSPEditorManipulationTranslateCreature_s005b_dca0::fn5de60()
{
  int n = (int)((char*)mLimbsEnd - (char*)mLimbsBegin) >> 2;
  for (int i = 0; i < n; ++i) {
    void* p = ((void**)mLimbsBegin)[i];
    ((cSPEditorLimbStructure*)p)->Release();
    p = ((void**)mLimbsBegin)[i];
    if (p != 0) {
      ((cSPEditorLimbStructure*)p)->Destroy();
      FUN_00f47380(p);
    }
  }
  void* s = mLimbsEnd;
  void* d = mLimbsBegin;
  memcpy(d, s, 0);
  mLimbsEnd = (void*)((char*)mLimbsEnd + (((char*)s - (char*)d) >> 2) * -4);
}

// @ 0x005bded0
float* cSPEditorManipulationTranslateCreature_s005b_dca0::fn5ded0(float* key)
{
  char* header = (char*)this + 0x04;
  char* parent = header;
  char* node = *(char**)((char*)this + 0x0c);
  while (node != 0) {
    if (*(float*)(node + 0x10) < *key) {
      node = *(char**)(node + 0x00);
    } else {
      parent = node;
      node = *(char**)(node + 0x04);
    }
  }
  if (parent != header && *key >= *(float*)(parent + 0x10))
    return (float*)(parent + 0x14);
  float k = *key;
  void* out = 0;
  FUN_005bdd90(key, parent, &k, 0);
  return (float*)((char*)out + 0x14);
}

// @ 0x005bdf70
void cSPEditorManipulationTranslateCreature_s005b_dca0::CalcBoundsForMovement( float* offset, float* boxA, float* boxB, void* vec)
{
  for (int i = 0; i < 3; ++i) {
    boxA[i] = F_013f7944;
    boxA[3 + i] = F_013f51ac;
    boxB[i] = F_013f7944;
    boxB[3 + i] = F_013f51ac;
  }
  if (vec != 0 && *(void**)vec != 0)
    FUN_00454280(*(void**)vec, ((void**)vec)[1]);

  int count = FUN_004accf0();
  for (int i = 0; i < count; ++i) {
    cSPEditorBlock* blk = (cSPEditorBlock*)FUN_004accb0((uint)i);
    if (blk != 0) blk->AddRef();
    if (FUN_00435d40() == 0 || FUN_004a6270(blk) != 0) {
      if (blk != 0) blk->Release();
      continue;
    }

    cSPEditorBlock* key = blk;
    float* v = fn5ded0((float*)&key);
    float pos[3];
    pos[0] = v[0] + offset[0];
    pos[1] = v[1] + offset[1];
    pos[2] = v[2] + offset[2];

    float xform[12];
    xform[0] = G_015eabf4[0];
    xform[1] = G_015eabf4[1];
    xform[2] = G_015eabf4[2];
    xform[3] = G_015eabf4[3];
    xform[4] = G_015eabf4[4];
    xform[5] = G_015eabf4[5];
    xform[6] = G_015eabf4[6];
    xform[7] = G_015eabf4[7];
    xform[8] = G_015eabf4[8];
    xform[9] = pos[0];
    xform[10] = pos[1];
    xform[11] = pos[2];

    cSPBoundingBox_s005b_dca0 box;
    box.mMin.x = F_013f7944; box.mMin.y = F_013f7944; box.mMin.z = F_013f7944;
    box.mMax.x = F_013f51ac; box.mMax.y = F_013f51ac; box.mMax.z = F_013f51ac;

    if (((*(uint*)((char*)blk + 0x60) >> 7) & 1) == 0) {
      float* bb = (float*)FUN_0044ae00(blk, 0, 0);
      box.mMax.x = bb[3]; box.mMax.y = bb[4]; box.mMax.z = bb[5];
      box.mMin.x = bb[0]; box.mMin.y = bb[1]; box.mMin.z = bb[2];
      FUN_00409dd0(&box, xform);
    } else {
      FUN_005ce680(mSpine, *(float*)((char*)blk + 0x3c), (uchar*)xform,
                   &box.mMin.x);
    }

    if (boxA[0] <= boxA[3]) {
      if (box.mMin.x < boxA[0]) boxA[0] = box.mMin.x;
      if (boxA[3] < box.mMax.x) boxA[3] = box.mMax.x;
      if (box.mMin.y < boxA[1]) boxA[1] = box.mMin.y;
      if (boxA[4] <= box.mMax.y && box.mMax.y != boxA[4]) boxA[4] = box.mMax.y;
      if (box.mMin.z < boxA[2]) boxA[2] = box.mMin.z;
      if (boxA[5] <= box.mMax.z && box.mMax.z != boxA[5]) boxA[5] = box.mMax.z;
    } else {
      boxA[0] = box.mMin.x; boxA[1] = box.mMin.y;
      boxA[3] = box.mMax.x; boxA[4] = box.mMax.y;
      boxA[2] = box.mMin.z; boxA[5] = box.mMax.z;
    }

    if (((*(uint*)((char*)blk + 0x60) >> 7) & 1) != 0) {
      if (boxB[0] <= boxB[3]) {
        if (box.mMin.x < boxB[0]) boxB[0] = box.mMin.x;
        if (boxB[3] < box.mMax.x) boxB[3] = box.mMax.x;
        if (box.mMin.y < boxB[1]) boxB[1] = box.mMin.y;
        if (boxB[4] <= box.mMax.y && box.mMax.y != boxB[4]) boxB[4] = box.mMax.y;
        if (box.mMin.z < boxB[2]) boxB[2] = box.mMin.z;
        if (boxB[5] <= box.mMax.z && box.mMax.z != boxB[5]) boxB[5] = box.mMax.z;
      } else {
        boxB[0] = box.mMin.x; boxB[1] = box.mMin.y;
        boxB[3] = box.mMax.x; boxB[4] = box.mMax.y;
        boxB[2] = box.mMin.z; boxB[5] = box.mMax.z;
      }
    }

    if (vec != 0) {
      void** end = (void**)((char*)vec + 4);
      void** cap = (void**)((char*)vec + 8);
      if (*end < *cap) {
        void* slot = *end;
        *end = (char*)slot + 4;
        if (slot != 0) {
          *(void**)slot = blk;
          blk->AddRef();
        }
      } else {
        FUN_00454ee0(*end, &blk);
      }
    }

    if (blk != 0) blk->Release();
  }
}

// @ 0x005be500
uint cSPEditorManipulationTranslateCreature_s005b_dca0::fn5e500(float param_2, float param_3)
{
  if (mModel == 0 || mSpine == 0) return 0;

  float planar[3];
  FUN_005bd7c0(this, planar, param_2, param_3, 0.0f);

  float offX = planar[0] - mOrigPlanar_x;
  float offY = planar[1] - mOrigPlanar_y;
  float offZ = planar[2] - mOrigPlanar_z;

  float boxA[6], boxB[6];
  void* list[4];
  list[0] = 0; list[1] = 0; list[2] = 0; list[3] = 0;

  float cur[3];
  cur[0] = offX; cur[1] = offY; cur[2] = offZ;
  CalcBoundsForMovement(cur, boxA, boxB, list);

  cur[1] = 0.0f; cur[2] = 0.0f;

  char sym = FUN_004adaa0();
  float wide = (float)FUN_004adb00() * 0.5f;
  float tall = (float)FUN_004adb40();

  float dMinY, dMaxX;
  if (-wide <= boxA[3]) {
    dMinY = cur[1];
    if (wide < boxA[4]) dMinY = -(boxA[4] - wide);
  } else {
    dMinY = -(boxA[3] + wide);
  }
  if (boxA[5] <= tall) {
    dMaxX = cur[2];
    if (boxA[2] < tall) {
      float t = tall;
      if (t > boxA[2]) t = boxA[2];
      dMaxX = t - boxA[2];
    }
  } else {
    dMaxX = -(boxA[5] - tall);
  }

  mCurrBounds[1] = boxA[4];
  mCurrBounds[2] = boxA[5];
  float f18v = mCurrBounds[1];
  mCurrBounds[2] = mCurrBounds[2] + dMinY;
  mCurrBounds[1] = f18v;
  mCurrBounds[0] = boxA[0] + dMaxX;
  float f23v = mCurrBounds[1];
  mCurrBounds[2] = mCurrBounds[2] + dMinY;
  mCurrBounds[1] = f23v;
  (void)sym;

  int n = (int)((char*)list[1] - (char*)list[0]) >> 2;
  float base = offX;
  for (int i = 0; i < n; ++i) {
    float key = ((float*)list[0])[i];
    float* v = fn5ded0(&key);
    float p[3];
    p[0] = v[0] + base;
    p[1] = v[1] + (dMinY + offY);
    p[2] = v[2] + offZ;
    FUN_00448e90(p, 1);
  }

  uchar old = FUN_004adc40();
  FUN_004adc20(0);

  int limbs = (int)((char*)mLimbsEnd - (char*)mLimbsBegin) >> 2;
  for (int i = 0; i < limbs; ++i) {
    void* limb = FUN_007f99a0();
    if (limb != 0) {
      float mat[9];
      float pos[3];
      mat[0] = *(float*)((char*)limb + 0xd8);
      mat[1] = *(float*)((char*)limb + 0xdc);
      mat[2] = *(float*)((char*)limb + 0xe0);
      mat[3] = *(float*)((char*)limb + 0xe4);
      mat[4] = *(float*)((char*)limb + 0xe8);
      mat[5] = *(float*)((char*)limb + 0xec);
      mat[6] = *(float*)((char*)limb + 0xf0);
      mat[7] = *(float*)((char*)limb + 0xf4);
      mat[8] = *(float*)((char*)limb + 0xf8);
      pos[0] = *(float*)((char*)limb + 0xac);
      pos[1] = *(float*)((char*)limb + 0xb0);
      pos[2] = *(float*)((char*)limb + 0xb4);
      float* v = fn5ded0(pos);
      FUN_0049fbd0(limb, v, mat, 0);
    }
    FUN_004890e0(1);
    FUN_00489ae0();
  }

  FUN_004adc20(old);

  int blocks = FUN_004accf0();
  for (int i = 0; i < blocks; ++i) {
    char* blk = (char*)FUN_004accb0((uint)i);
    *(uint*)(blk + 0x54) = *(uint*)(blk + 0x48);
    *(uint*)(blk + 0x58) = *(uint*)(blk + 0x4c);
    *(uint*)(blk + 0x5c) = *(uint*)(blk + 0x50);
    for (int j = 0; j < 9; ++j) {
      *(uint*)(blk + 0x84 + j * 4) = *(uint*)(blk + 0x60 + j * 4);
      *(uint*)(blk + 0xcc + j * 4) = *(uint*)(blk + 0xa8 + j * 4);
    }
  }

  if (mChangedObject == 0) mChangedObject = 1;

  int* vertebra = (int*)((char*)mSpine + 0x00);
  FUN_004a6d20(vertebra, 0, 0, 0, 0, 0, 1, 1);

  void** p3 = (void**)list[0];
  void** p4 = (void**)list[1];
  for (void** it = p3; it < p4; ++it) {
    if (*it != 0) {
      void** vtbl = *(void***)it;
      ((void (*)(void))vtbl[2])();
    }
  }
  if (p3 != 0 && p3[-1] != 0) FUN_00f47380(p3);

  return 1;
}

// @ 0x005beaf0
namespace SP {
bool cSPEditorManipulationTranslateCreature_s005b_eaf0::DoOnMouseDown(int button, float x, float y, int modifiers)
{
  if (mModel) {
    mModelUsingSymmetry = mModel->IsUsingSymmetry();
    mModel->SetUsingSymmetry(false);
    int numBlocks = mModel->GetNumBlocks();
    for (int i = 0; i < numBlocks; i++) {
      EA::AutoRefCount_s005b_eaf0<cSPEditorBlock_s005b_eaf0> block(mModel->GetBlock(i));
      block->mHistoryPosition = block->mPosition;
      block->mHistoryOrientation = block->mOrientation;
      block->mHistoryBaseOrientation = block->mBaseOrientation;
      cSPEditorBlock_s005b_eaf0* key = block;
      mOriginalPositions[key] = block->mPosition;
    }
    if (numBlocks > 0) {
      eastl::sp_vector<cSPEditorBlock_s005b_eaf0*> limbs;
      EditorUtils::GetAllLimbs(mModel->GetBlock(0), limbs, 0);
      int numLimbs = limbs.size();
      for (int i = 0; i < numLimbs; i++) {
        cSPEditorLimbStructure_s005b_eaf0* limb = new ("Editor", 0, 0, 0, 0) cSPEditorLimbStructure_s005b_eaf0();
        limb->Init(limbs[i], 0, 0);
        mLimbs.push_back(limb);
      }
    }
    if (mSpine)
      mSpine->Rebuild(false, true);
    mOriginalPlanarPosition = PickPlaneOfSymmetry(x, y, false);
    cSPBoundingBox_s005b_eaf0 limits(cSPVector3_s005b_eaf0(FLT_MAX, FLT_MAX, FLT_MAX), cSPVector3_s005b_eaf0(-FLT_MAX, -FLT_MAX, -FLT_MAX));
    CalcBoundsForMovement(cSPVector3_s005b_eaf0(0.0f, 0.0f, 0.0f), mCurrModelBounds, limits, false);
  }
  return false;
}
}  // namespace SP
