// src/game/SPEditors/SPEditorManipulationCellPinning.cpp -- migrated from slice(s) s005ac950, s005aad00, s005a9d40 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorManipulationCellPinning.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cMeshData.h"
#include "SP/cViewer.h"

// unnamed retail callees and globals (address in the comment)
extern const float g_lowInit;    // 0x013f70b0 (FLT_MAX)
extern const float g_highInit;   // 0x013f70ac (FLT_MIN)
#include <math.h>
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorManipulationObject.h"
#include "SP/cSPEditorSkinManager.h"

// ---- items of slice s005a9d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cBigThing {
public:
    char pad0[0x138];
    uint32_t mX;   // +0x138
    uint32_t mY;   // +0x13c
    uint32_t mZ;   // +0x140
    void SetVec(uint32_t x, uint32_t y, uint32_t z);
};
class cSkinManager {
public:
    void GetSkin(int index);
};
class cPinning {
public:
    char pad0[0xe0];
    cSkinManager* mSkinManager;   // +0xe0
    void Update(int deltaTime);
};
struct Vec3 { float x, y, z; };
struct Mat3 {
    float m[9];
    Mat3(const Mat3& o);   // out-of-line copy ctor (Matrix3::Assign at 0x0041cb40)
    Mat3() {}
};
extern Vec3 g_up2;           // 0x015e88dc
class cCamObj { public: char pad[0xc]; Vec3 pos; };
class cBlockInfo {
public:
    bool F4adc40();            // 0x004adc40 (thiscall)
};
class cBlock {
public:
    virtual void v0();
    virtual void AddRef();     // +4
    virtual void Release();    // +8
    char pad[0x28 - 4];
    cBlockInfo* mInfo;         // +0x28
    char pad2[0x48 - 0x2c];
    Vec3 pos;                  // +0x48
    char pad3[0x78 - 0x54];
    Vec3 up2;                  // +0x78
    char pad4[0x3f0 - 0x84];
    cCamObj* mCam;             // +0x3f0
    bool F43bc40(float f);     // 0x0043bc40
    bool HasAnyBlockFlag();    // Entity::HasAnyBlockFlag 0x00435d40
};
template <class T> class AutoRef {
public:
    T* p;
    AutoRef() : p(0) {}
    AutoRef(const AutoRef& o) : p(o.p) { if (p) p->AddRef(); }
    ~AutoRef() { if (p) p->Release(); }
    AutoRef& operator=(const AutoRef& o) {
        T* n = o.p;
        T* old = p;
        if (n != old) {
            if (n) n->AddRef();
            p = n;
            if (old) old->Release();
        }
        return *this;
    }
};
class cManipBase {
public:
    cManipBase();               // 0x005b0f80
    virtual void m0();
    bool mFlag4;
    char pad8[0x14 - 8];
};
class cRC {
public:
    cRC() : mnRefCount(0) {}
    virtual void r0();
    virtual void r1();
    int mnRefCount;
};
class cBlockSet {
public:
    int Count();                 // 0x004accf0
    class cBlockEntry* At(int);  // 0x004accb0
};
class cBlockEntry {
public:
    char pad0[0x48];
    Vec3 pos;                    // +0x48
    char pad1[0xdc8 - 0x54];
    uint32_t mFlags;             // +0xdc8
};
class cSkinMgrIface {
public:
    virtual void AddRef();
    virtual void Release();
};
class cMeshData {
public:
    char pad0[8];
    Vec3* mPositions;      // +8
    char pad1[0x1c - 0xc];
    Vec3* mNormals;        // +0x1c
    void F490(Vec3 v, Vec3* out);   // 0x0050c490, thiscall ret 0x10
    void F5a0(Vec3 v, Vec3* out);   // 0x0050c5a0, thiscall ret 0x10
};
class cSkin { public: char pad[0x34]; cMeshData* mMesh; };
class cSkinMgr { public: cSkin* GetSkin(int idx); };   // SP::cSPEditorSkinManager::GetSkin 0x004c49e0
class cEdgeObj {
public:
    char pad0[8];
    Vec3* mVerts;          // +8
    Vec3* mVertsEnd;       // +0xc
    bool F50bd90(const Vec3* a, const Vec3* b, int one, float* p5, float* p4, float* p3, float* p2, float* p1);   // 0x0050bd90 thiscall ret 0x20
};
class cPosObj { public: char pad[0x48]; float x, y; };      // helper objects with pos
class cPosHolder {
public:
    cPosObj* F4ac610();        // 0x004ac610
    cPosObj* F4ac710();        // 0x004ac710
};
class cCellPinning : public cManipBase, public cRC {
public:
    void* m1c; void* m20; void* m24;      // 0x1c..0x24
    char pad28[0x30 - 0x28];
    AutoRef<cBlock> mBlockRef;            // +0x30
    char pad34[0x38 - 0x34];
    float mOffX, mOffY, mOffZ;            // +0x38..0x40
    bool mFlag44;                         // +0x44
    char pad45[0xe0 - 0x45];
    AutoRef<cSkinMgrIface> mSkinRef;      // +0xe0
    cEdgeObj* mEdges;                     // +0xe4
    void* mE8; void* mEc; void* mF0;      // 0xe8..0xf0
    char padf4[0xfc - 0xf4];
    void* mFc; void* m100; void* m104;
    char pad108[0x110 - 0x108];
    void* m110; void* m114; void* m118;
    char pad11c[0x124 - 0x11c];
    bool m124;
    char pad125[0x128 - 0x125];
    Vec3 mV1;                             // +0x128
    Vec3 mV2;                             // +0x134
    float m140, m144;
    bool m148;
    cCellPinning();
    void CalculateInflatedMesh();
    bool GetPlacement(Vec3 a, Vec3 b, Vec3* o7, Mat3* o8, Vec3* o9);
    void Setup(const AutoRef<cBlock>& blk, float x, float y, float unused, AutoRef<cSkinMgrIface> skin, bool b1, bool b2);
};
// ---- items of slice s005a9d40 end

// ---- items of slice s005aad00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
#ifndef SP_EDITOR_MANIP_SCAFFOLD_H
#endif  // SP_EDITOR_MANIP_SCAFFOLD_H
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
class Vector3Template_s005a_ad00 {
 public:
  T x, y, z;
  Vector3Template_s005a_ad00() {}
  Vector3Template_s005a_ad00(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
class Matrix33Template_s005a_ad00 {
 public:
  Vector3Template_s005a_ad00<T, N> xAxis, yAxis, zAxis;
  Matrix33Template_s005a_ad00() {}
};
}
}
}
struct cSPVector3_s005a_ad00 : public rw::math::fpu::Vector3Template_s005a_ad00<float, 0> {
  typedef rw::math::fpu::Vector3Template_s005a_ad00<float, 0> base;
  cSPVector3_s005a_ad00() {}
  cSPVector3_s005a_ad00(float ax, float ay, float az) : base(ax, ay, az) {}
  cSPVector3_s005a_ad00(const base& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3_s005a_ad00& operator=(const base& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPMatrix3_s005a_ad00 : public rw::math::fpu::Matrix33Template_s005a_ad00<float, 0> {};
namespace eastl {
struct sp_vector_allocator_s005a_ad00 {
  uint32_t mData[2];
  sp_vector_allocator_s005a_ad00() {}
  void deallocate(void* p, uint32_t) {
    if (((int*)p)[-1])
      EASTL_allocator_deallocate(p);
  }
};
}
namespace eastl {
template <typename T>
class VectorBase_s005a_ad00 {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator_s005a_ad00 mAllocator;
  VectorBase_s005a_ad00() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  VectorBase_s005a_ad00(size_t n, const sp_vector_allocator_s005a_ad00& allocator);   // out-of-line (0x66aec0)
  ~VectorBase_s005a_ad00() {
    for (T* p = mpBegin; p != mpEnd; ++p)
      p->~T();
    if (mpBegin)
      mAllocator.deallocate(mpBegin, (uint32_t)(mpCapacity - mpBegin));
  }
};
}
namespace eastl {
template <typename T>
struct copy_result {
  T* mpResult;
  copy_result() {}
};
}
namespace eastl {
template <typename T>
copy_result<T> uninitialized_copy_impl(const T* first, const T* last, T* dest);   // 0x4b2220
}
namespace eastl {
template <typename T>
inline T* uninitialized_copy_ptr(const T* first, const T* last, T* result) {
  copy_result<T> r = uninitialized_copy_impl(first, last, result);
  return r.mpResult;
}
}
namespace eastl {
template <typename T>
class sp_vector : public VectorBase_s005a_ad00<T> {
 public:
  sp_vector() : VectorBase_s005a_ad00<T>() {}
  sp_vector(const sp_vector& x) : VectorBase_s005a_ad00<T>((size_t)(x.mpEnd - x.mpBegin), x.mAllocator) {
    this->mpEnd = uninitialized_copy_ptr(x.mpBegin, x.mpEnd, this->mpBegin);
  }
};
}
namespace EA {
namespace COM {
class IUnknown32_s005a_ad00 {
 public:
  virtual int AddRef();
  virtual int Release();
};  // namespace COM
}
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005a_ad00 {
 public:
  RefCountVTemplate_s005a_ad00() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005a_ad00() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
template <typename T>
class AutoRefCount_s005a_ad00 {
 public:
  T* mpObject;
  AutoRefCount_s005a_ad00() : mpObject(0) {}
  ~AutoRefCount_s005a_ad00() {
    if (mpObject)
      mpObject->Release();
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace SP {
class cSPEditorModel_s005a_ad00;
}
namespace SP {
class cSPEditorSkinManager_s005a_ad00;
}
namespace SP {
class cMWModel_s005a_ad00;
}
namespace SP {
class cMesh;
}
namespace SP {
class cSPEditorBlock_s005a_ad00 : public EA::RefCountVTemplate_s005a_ad00<int> {
 public:
  char pad_08[4];                 // +0x08 IUnknown32 vptr
  char pad_0c[0x28 - 0x0c];
  cSPEditorModel_s005a_ad00* mEditorModel;   // +0x28
  char pad_2c[0x48 - 0x2c];
  cSPVector3_s005a_ad00 mPosition;           // +0x48
  cSPVector3_s005a_ad00 mHistoryPosition;    // +0x54
  cSPMatrix3_s005a_ad00 mOrientation;        // +0x60
  cSPMatrix3_s005a_ad00 mHistoryOrientation; // +0x84
  cSPMatrix3_s005a_ad00 mBaseOrientation;    // +0xa8
  char pad_cc[0x138 - 0xcc];
  cSPVector3_s005a_ad00 mSurfaceNormal;             // +0x138
  cSPVector3_s005a_ad00 mReplacePartDisplacement;   // +0x144
  char pad_150[0x33c - 0x150];
  EA::AutoRefCount_s005a_ad00<cMWModel_s005a_ad00> mSocketConnector;  // +0x33c
  char pad_340[0xdc8 - 0x340];
  uint32_t mFlags[2];   // +0xdc8 (bitset<54>)
};
}
namespace SP {
class cSPEditorSkinManager_s005a_ad00 : public EA::COM::IUnknown32_s005a_ad00 {
 public:
  char pad_4[0xc - 0x4];
};
}
namespace SP {
class cSPEditorManipulationObject_s005a_ad00 : public EA::COM::IUnknown32_s005a_ad00 {
 public:
  virtual ~cSPEditorManipulationObject_s005a_ad00() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  char pad_7;
  float mDeadZoneSize;   // +0x8
  float mInitialX;       // +0xc
  float mInitialY;       // +0x10
};
}
namespace SP {
class cSPEditorManipulationCellPinning : public cSPEditorManipulationObject_s005a_ad00, public EA::RefCountVTemplate_s005a_ad00<int> {
 public:
  eastl::sp_vector<EA::AutoRefCount_s005a_ad00<cSPEditorBlock_s005a_ad00> > mPileList;  // +0x1c
  EA::AutoRefCount_s005a_ad00<cSPEditorBlock_s005a_ad00> mBlock;                        // +0x30
  EA::AutoRefCount_s005a_ad00<cSPEditorBlock_s005a_ad00> mBumpedBlock;                  // +0x34
  cSPVector3_s005a_ad00 mMouseOffset;            // +0x38
  bool mRecalculateMouseOffset;       // +0x44
  char pad_45[3];
  cSPVector3_s005a_ad00 mMouseOffset3D;                 // +0x48
  cSPVector3_s005a_ad00 mVertexOffset;                  // +0x54
  cSPMatrix3_s005a_ad00 mInverseNormalTransform;        // +0x60
  cSPMatrix3_s005a_ad00 mInverseNormalTransform2;       // +0x84
  float mOffsetLength;                       // +0xa8
  float mOffsetRotation;                     // +0xac
  cSPVector3_s005a_ad00 mUnTransformedPosition;         // +0xb0
  cSPMatrix3_s005a_ad00 mUnTransformedOrientation;      // +0xbc
  EA::AutoRefCount_s005a_ad00<cSPEditorSkinManager_s005a_ad00> mSkin;  // +0xe0
  cMesh* mInflatedMesh;                          // +0xe4
  eastl::sp_vector<cSPVector3_s005a_ad00> mEdgePositions;    // +0xe8
  eastl::sp_vector<cSPVector3_s005a_ad00> mEdgeNormals;      // +0xfc
  eastl::sp_vector<cSPVector3_s005a_ad00> mEdgeTrueNormals;  // +0x110
  bool mHadParentOnMouseDown;   // +0x124
  char pad_125[0x140 - 0x125];
  float mX;                     // +0x140
  float mY;                     // +0x144
  bool mPinToRigBlocks;         // +0x148

  cSPEditorManipulationCellPinning();
  virtual ~cSPEditorManipulationCellPinning();
  virtual int AddRef();
  virtual int Release();
  virtual void* AsInterface(uint32_t typeID);
  virtual bool OnMouseUp(int button, float x, float y, int modifiers);
  virtual bool DoOnMouseDown(int button, float x, float y, int modifiers);
  virtual bool DoOnMouseMove(float x, float y, int modifiers);
  virtual void Update();
  virtual eastl::sp_vector<EA::AutoRefCount_s005a_ad00<cSPEditorBlock_s005a_ad00> > GetPileList();

  void RecalculateMouseOffset(float x, float y);
  void CalculateInflatedMesh();   // 0x005aa7a0
};
}
// ---- items of slice s005aad00 end

// ---- items of slice s005ac950 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
class Vector3Template_s005a_c950 {
 public:
  T x, y, z;
  Vector3Template_s005a_c950() {}
  Vector3Template_s005a_c950(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
class Matrix33Template_s005a_c950 {
 public:
  Vector3Template_s005a_c950<T, N> xAxis, yAxis, zAxis;
  Matrix33Template_s005a_c950() {}
};
}
}
}
struct cSPVector3_s005a_c950 : public rw::math::fpu::Vector3Template_s005a_c950<float, 0> {
  typedef rw::math::fpu::Vector3Template_s005a_c950<float, 0> base;
  cSPVector3_s005a_c950() {}
  cSPVector3_s005a_c950(float ax, float ay, float az) : base(ax, ay, az) {}
  cSPVector3_s005a_c950(const base& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3_s005a_c950& operator=(const base& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPMatrix3_s005a_c950 : public rw::math::fpu::Matrix33Template_s005a_c950<float, 0> {};
namespace eastl {
struct sp_vector_allocator_s005a_c950 {
  uint32_t mData[2];
  sp_vector_allocator_s005a_c950() {}
  void deallocate(void* p, uint32_t) {
    if (((int*)p)[-1])
      EASTL_allocator_deallocate(p);
  }
};
}
namespace eastl {
template <typename T>
class VectorBase_s005a_c950 {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator_s005a_c950 mAllocator;
  VectorBase_s005a_c950() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  VectorBase_s005a_c950(size_t n, const sp_vector_allocator_s005a_c950& allocator);   // out-of-line (0x66aec0)
  ~VectorBase_s005a_c950() {
    for (T* p = mpBegin; p != mpEnd; ++p)
      p->~T();
    if (mpBegin)
      mAllocator.deallocate(mpBegin, (uint32_t)(mpCapacity - mpBegin));
  }
};
}
namespace eastl {
template <typename T>
class sp_vector_s005a_c950 : public VectorBase_s005a_c950<T> {
 public:
  sp_vector_s005a_c950() : VectorBase_s005a_c950<T>() {}
  sp_vector_s005a_c950(const sp_vector_s005a_c950& x) : VectorBase_s005a_c950<T>((size_t)(x.mpEnd - x.mpBegin), x.mAllocator) {
    this->mpEnd = uninitialized_copy_ptr(x.mpBegin, x.mpEnd, this->mpBegin);
  }
};
}
namespace EA {
namespace COM {
class IUnknown32_s005a_c950 {
 public:
  virtual int AddRef();
  virtual int Release();
};  // namespace COM
}
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005a_c950 {
 public:
  RefCountVTemplate_s005a_c950() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005a_c950() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
template <typename T>
class AutoRefCount_s005a_c950 {
 public:
  T* mpObject;
  AutoRefCount_s005a_c950() : mpObject(0) {}
  ~AutoRefCount_s005a_c950() {
    if (mpObject)
      mpObject->Release();
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace SP {
class cSPEditorModel_s005a_c950;
}
namespace SP {
class cSPEditorSkinManager_s005a_c950;
}
namespace SP {
class cMWModel_s005a_c950;
}
namespace SP {
class cSPEditorBlock_s005a_c950 : public EA::RefCountVTemplate_s005a_c950<int> {
 public:
  char pad_08[4];                 // +0x08 IUnknown32 vptr
  char pad_0c[0x28 - 0x0c];
  cSPEditorModel_s005a_c950* mEditorModel;   // +0x28
  char pad_2c[0x48 - 0x2c];
  cSPVector3_s005a_c950 mPosition;           // +0x48
  cSPVector3_s005a_c950 mHistoryPosition;    // +0x54
  cSPMatrix3_s005a_c950 mOrientation;        // +0x60
  cSPMatrix3_s005a_c950 mHistoryOrientation; // +0x84
  cSPMatrix3_s005a_c950 mBaseOrientation;    // +0xa8
  char pad_cc[0x138 - 0xcc];
  cSPVector3_s005a_c950 mSurfaceNormal;             // +0x138
  cSPVector3_s005a_c950 mReplacePartDisplacement;   // +0x144
  char pad_150[0x33c - 0x150];
  EA::AutoRefCount_s005a_c950<cMWModel_s005a_c950> mSocketConnector;  // +0x33c
  char pad_340[0xdc8 - 0x340];
  uint32_t mFlags[2];   // +0xdc8 (bitset<54>)
};
}
namespace SP {
class cSPEditorSkinManager_s005a_c950 : public EA::COM::IUnknown32_s005a_c950 {
 public:
  char pad_4[0xc - 0x4];
};
}
namespace SP {
class cSPEditorManipulationObject_s005a_c950 : public EA::COM::IUnknown32_s005a_c950 {
 public:
  virtual ~cSPEditorManipulationObject_s005a_c950() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  char pad_7;
  float mDeadZoneSize;   // +0x8
  float mInitialX;       // +0xc
  float mInitialY;       // +0x10
};
}
namespace SP {
class cSPEditorManipulationCellPinning_s005a_c950 : public cSPEditorManipulationObject_s005a_c950, public EA::RefCountVTemplate_s005a_c950<int> {
 public:
  eastl::sp_vector_s005a_c950<EA::AutoRefCount_s005a_c950<cSPEditorBlock_s005a_c950> > mPileList;  // +0x1c
  EA::AutoRefCount_s005a_c950<cSPEditorBlock_s005a_c950> mBlock;                        // +0x30
  EA::AutoRefCount_s005a_c950<cSPEditorBlock_s005a_c950> mBumpedBlock;                  // +0x34
  cSPVector3_s005a_c950 mMouseOffset;            // +0x38
  bool mRecalculateMouseOffset;       // +0x44
  char pad_45[3];
  cSPVector3_s005a_c950 mMouseOffset3D;                 // +0x48
  cSPVector3_s005a_c950 mVertexOffset;                  // +0x54
  cSPMatrix3_s005a_c950 mInverseNormalTransform;        // +0x60
  cSPMatrix3_s005a_c950 mInverseNormalTransform2;       // +0x84
  float mOffsetLength;                       // +0xa8
  float mOffsetRotation;                     // +0xac
  cSPVector3_s005a_c950 mUnTransformedPosition;         // +0xb0
  cSPMatrix3_s005a_c950 mUnTransformedOrientation;      // +0xbc
  EA::AutoRefCount_s005a_c950<cSPEditorSkinManager_s005a_c950> mSkin;  // +0xe0
  cMesh* mInflatedMesh;                          // +0xe4
  eastl::sp_vector_s005a_c950<cSPVector3_s005a_c950> mEdgePositions;    // +0xe8
  eastl::sp_vector_s005a_c950<cSPVector3_s005a_c950> mEdgeNormals;      // +0xfc
  eastl::sp_vector_s005a_c950<cSPVector3_s005a_c950> mEdgeTrueNormals;  // +0x110
  bool mHadParentOnMouseDown;   // +0x124
  char pad_125[0x140 - 0x125];
  float mX;                     // +0x140
  float mY;                     // +0x144
  bool mPinToRigBlocks;         // +0x148

  cSPEditorManipulationCellPinning_s005a_c950();
  virtual ~cSPEditorManipulationCellPinning_s005a_c950();
  virtual int AddRef();
  virtual int Release();
  virtual void* AsInterface(uint32_t typeID);  // 0x005ac950 (SP::cSPEditorManipulationCellPinning::AsInterface)
  virtual bool OnMouseUp(int button, float x, float y, int modifiers);  // 0x005aada0 (SP::cSPEditorManipulationCellPinning::OnMouseUp)
  virtual bool DoOnMouseDown(int button, float x, float y, int modifiers);  // 0x005ab5c0 (SP::cSPEditorManipulationCellPinning::DoOnMouseDown)
  virtual bool DoOnMouseMove(float x, float y, int modifiers);
  virtual void Update();  // 0x005aa5b0 (SP::cSPEditorManipulationCellPinning::Update)
  virtual eastl::sp_vector_s005a_c950<EA::AutoRefCount_s005a_c950<cSPEditorBlock_s005a_c950> > GetPileList();  // 0x005ab1b0 (SP::cSPEditorManipulationCellPinning::GetPileList)

  void RecalculateMouseOffset(float x, float y);  // 0x005ab220 (SP::cSPEditorManipulationCellPinning::RecalculateMouseOffset)
  void CalculateInflatedMesh();   // 0x005aa7a0
};
}
// ---- items of slice s005ac950 end

// @ 0x005aa580
void cBigThing::SetVec(uint32_t x, uint32_t y, uint32_t z)
{
    mX = x;
    mY = y;
    mZ = z;
}

// @ 0x005aa5b0
void cPinning::Update(int)
{
    mSkinManager->GetSkin(0);
}

// @ 0x005aa5d0
void __stdcall ClampToPinned(Vec3* out, float a, float y, float z, cBlockSet* set)
{
    Vec3 lo, hi;
    lo.x = 0.0f; lo.y = g_lowInit; lo.z = 0.0f;
    hi.x = 0.0f; hi.y = g_highInit; hi.z = 0.0f;
    int i = 0;
    int n = set->Count();
    for (; i < n; i++) {
        uint32_t fl = set->At(i)->mFlags;
        fl >>= 7;
        if (fl & 1) {
            cBlockEntry* e = set->At(i);
            Vec3 p;
            p.x = e->pos.x;
            p.z = e->pos.z;
            const Vec3* pp = &e->pos;
            p.y = pp->y;
            if (lo.y > p.y)
                lo = p;
            else if (p.y > hi.y)
                hi = p;
        }
    }
    if (lo.y > y) {
        out->x = lo.x; out->y = lo.y; out->z = lo.z;
    } else if (y > hi.y) {
        out->x = hi.x; out->y = hi.y; out->z = hi.z;
    } else {
        out->x = 0.0f; out->y = y; out->z = z;
    }
}

// @ 0x005aa740
AutoRef<cBlock>* RemoveCopyBlocks(AutoRef<cBlock>* first, AutoRef<cBlock>* last, AutoRef<cBlock>* dest, const AutoRef<cBlock>* value)
{
    for (; first != last; ++first) {
        if (first->p != value->p) {
            *dest = *first;
            ++dest;
        }
    }
    return dest;
}

// @ 0x005aa7a0
void cCellPinning::CalculateInflatedMesh()
{
    void BuildOrientation(Mat3* out, const Vec3* dir, const Vec3* up);
    cSkinMgr* skinMgr = (cSkinMgr*)mSkinRef.p;
    cMeshData* mesh = skinMgr->GetSkin(0)->mMesh;
    cEdgeObj* eo = mEdges;
    if (eo && mesh) {
        int n = (int)(eo->mVertsEnd - eo->mVerts);
        if (n > 0) {
            int off = 0;
            do {
                Vec3 nrm = *(Vec3*)((char*)mesh->mNormals + off);
                Vec3 pos = *(Vec3*)((char*)mesh->mPositions + off);
                Vec3 negN;
                negN.x = -nrm.x;
                negN.y = -nrm.y;
                negN.z = -nrm.z;
                Mat3 m;
                BuildOrientation(&m, &negN, &g_up2);
                float az = nrm.z < 0 ? -nrm.z : nrm.z;
                float f = 1.0f;
                if (az < 0.5f)
                    f = (1.0f - az) * 0.5f + 1.0f;
                if (sqrtf((mOffX * mOffX + mOffY * mOffY) + mOffZ * mOffZ) < 0.1f)
                    f = f * 1.5f;
                float a = mOffX * f;
                float b = mOffY * f;
                float c = mOffZ * f;
                Vec3* dst = (Vec3*)((char*)mEdges->mVerts + off);
                dst->x = ((m.m[6] * c + m.m[3] * b) + m.m[0] * a) + pos.x;
                dst->y = ((m.m[1] * a + m.m[4] * b) + m.m[7] * c) + pos.y;
                dst->z = ((m.m[8] * c + m.m[5] * b) + m.m[2] * a) + pos.z;
                off += 12;
                n--;
            } while (n != 0);
        }
    }
}

// @ 0x005aa9c0
bool cCellPinning::GetPlacement(Vec3 a, Vec3 b, Vec3* o7, Mat3* o8, Vec3* o9)
{
    void BuildOrientation(Mat3* out, const Vec3* dir, const Vec3* up);
    float buf[20];
    bool ok = mEdges->F50bd90(&a, &b, 1, &buf[1], &buf[0], &buf[2], &buf[5], &buf[15]);
    cSkin* skin = ((cSkinMgr*)mSkinRef.p)->GetSkin(0);
    cMeshData* mesh = skin->mMesh;
    if (!ok || !mesh)
        return false;
    *o9 = *(Vec3*)&buf[5];
    Vec3 A = *(Vec3*)&buf[1];
    Vec3 out1, out2;
    mesh->F490(A, &out1);
    mesh->F5a0(A, &out2);
    Mat3 m;
    BuildOrientation(&m, &out2, &g_up2);
    *o7 = out1;
    *o8 = m;
    return true;
}

// @ 0x005aab00
void cCellPinning::Setup(const AutoRef<cBlock>& blk, float x, float y, float, AutoRef<cSkinMgrIface> skin, bool b1, bool b2)
{
    float VecLength(void* obj);
    mBlockRef = blk;
    mOffX = x;
    mOffY = y;
    mOffZ = 0.0f;
    mSkinRef = skin;
    m148 = b1;
    mFlag44 = b2;
    cPosHolder* h = (cPosHolder*)mBlockRef.p->mInfo;
    cPosObj* p1 = h->F4ac610();
    cPosObj* p2 = h->F4ac710();
    mV1.x = p1->x;
    mV1.y = p1->y;
    mV1.x = 0.0f;
    mV1.z = 0.0f;
    mV1.y = mV1.y - VecLength(p1);
    mV2.x = p2->x;
    mV2.y = p2->y;
    mV2.x = 0.0f;
    mV2.z = 0.0f;
    mV2.y = VecLength(p2) + mV2.y;
}

// @ 0x005aac30
cCellPinning::cCellPinning()
{
    m1c = 0;
    m20 = 0;
    m24 = 0;
    mBlockRef.p = 0;
    *(void**)&pad34 = 0;
    mOffX = 0.0f;
    mOffY = 0.0f;
    mOffZ = 0.0f;
    mFlag44 = true;
    mSkinRef.p = 0;
    mE8 = 0; mEc = 0; mF0 = 0;
    mFc = 0; m100 = 0; m104 = 0;
    m110 = 0; m114 = 0; m118 = 0;
    m124 = false;
    m148 = false;
    mFlag4 = false;
    m140 = 0.0f;
    m144 = 0.0f;
}

// @ 0x005aad00
SP::cSPEditorManipulationCellPinning::~cSPEditorManipulationCellPinning()
{}

// @ 0x005aada0
bool SP::cSPEditorManipulationCellPinning::OnMouseUp(int, float, float, int)
{
  return true;
}

// @ 0x005ab1b0
eastl::sp_vector<EA::AutoRefCount_s005a_ad00<SP::cSPEditorBlock_s005a_ad00> > SP::cSPEditorManipulationCellPinning::GetPileList()
{
  return mPileList;
}

// @ 0x005ab220
void SP::cSPEditorManipulationCellPinning::RecalculateMouseOffset(float, float)
{
  CalculateInflatedMesh();
}

// @ 0x005ab5c0
bool SP::cSPEditorManipulationCellPinning::DoOnMouseDown(int, float, float, int)
{
  return true;
}

// @ 0x005ac950
void* SP::cSPEditorManipulationCellPinning_s005a_c950::AsInterface(uint32_t typeID)
{
  void* result = this;
  if (typeID != 0xee3f516e && typeID != 0xefdf6da5)
    result = 0;
  return result;
}
