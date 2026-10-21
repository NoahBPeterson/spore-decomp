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
struct hkVector4_s005b_ccc0 { float x, y, z, w; };
class hkMotionState { public: char pad[0x40]; Vec3 pos; };                 // position at +0x40
struct hkRigidBody_s005b_ccc0 {
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
struct hkWorld_s005b_ccc0 {
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
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
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

// @ 0x005bde60
void FUN_005bde60()
{}

// @ 0x005be500
void FUN_005be500()
{}

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
