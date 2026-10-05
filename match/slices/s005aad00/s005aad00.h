// Shared scaffolding for the SP editor manipulation slices (s005aad00, s005ab7a0, s005ac950).
// Real class layouts: 2008 dev PDB with the retail eastl::sp_vector shift (+4 per vector, since
// the retail sp_vector_allocator is 8 bytes). Only the members the retail code touches are named.
#ifndef SP_EDITOR_MANIP_SCAFFOLD_H
#define SP_EDITOR_MANIP_SCAFFOLD_H
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);

namespace rw { namespace math { namespace fpu {
template <typename T, int N>
class Vector3Template {
 public:
  T x, y, z;
  Vector3Template() {}
  Vector3Template(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
template <typename T, int N>
class Matrix33Template {
 public:
  Vector3Template<T, N> xAxis, yAxis, zAxis;
  Matrix33Template() {}
};
}}}  // namespace rw::math::fpu

struct cSPVector3 : public rw::math::fpu::Vector3Template<float, 0> {
  typedef rw::math::fpu::Vector3Template<float, 0> base;
  cSPVector3() {}
  cSPVector3(float ax, float ay, float az) : base(ax, ay, az) {}
  cSPVector3(const base& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3& operator=(const base& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPMatrix3 : public rw::math::fpu::Matrix33Template<float, 0> {};

namespace eastl {
struct sp_vector_allocator {
  uint32_t mData[2];
  sp_vector_allocator() {}
  void deallocate(void* p, uint32_t) {
    if (((int*)p)[-1])
      EASTL_allocator_deallocate(p);
  }
};
template <typename T>
class VectorBase {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator mAllocator;
  VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  VectorBase(size_t n, const sp_vector_allocator& allocator);   // out-of-line (0x66aec0)
  ~VectorBase() {
    for (T* p = mpBegin; p != mpEnd; ++p)
      p->~T();
    if (mpBegin)
      mAllocator.deallocate(mpBegin, (uint32_t)(mpCapacity - mpBegin));
  }
};
template <typename T>
struct copy_result {
  T* mpResult;
  copy_result() {}
};
template <typename T>
copy_result<T> uninitialized_copy_impl(const T* first, const T* last, T* dest);   // 0x4b2220
template <typename T>
inline T* uninitialized_copy_ptr(const T* first, const T* last, T* result) {
  copy_result<T> r = uninitialized_copy_impl(first, last, result);
  return r.mpResult;
}
template <typename T>
class sp_vector : public VectorBase<T> {
 public:
  sp_vector() : VectorBase<T>() {}
  sp_vector(const sp_vector& x) : VectorBase<T>((size_t)(x.mpEnd - x.mpBegin), x.mAllocator) {
    this->mpEnd = uninitialized_copy_ptr(x.mpBegin, x.mpEnd, this->mpBegin);
  }
};
}  // namespace eastl

namespace EA {
namespace COM {
class IUnknown32 {
 public:
  virtual int AddRef();
  virtual int Release();
};
}  // namespace COM
template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  ~AutoRefCount() {
    if (mpObject)
      mpObject->Release();
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}  // namespace EA

namespace SP {

class cSPEditorModel;
class cSPEditorSkinManager;
class cMWModel;
class cMesh;

class cSPEditorBlock : public EA::RefCountVTemplate<int> {
 public:
  char pad_08[4];                 // +0x08 IUnknown32 vptr
  char pad_0c[0x28 - 0x0c];
  cSPEditorModel* mEditorModel;   // +0x28
  char pad_2c[0x48 - 0x2c];
  cSPVector3 mPosition;           // +0x48
  cSPVector3 mHistoryPosition;    // +0x54
  cSPMatrix3 mOrientation;        // +0x60
  cSPMatrix3 mHistoryOrientation; // +0x84
  cSPMatrix3 mBaseOrientation;    // +0xa8
  char pad_cc[0x138 - 0xcc];
  cSPVector3 mSurfaceNormal;             // +0x138
  cSPVector3 mReplacePartDisplacement;   // +0x144
  char pad_150[0x33c - 0x150];
  EA::AutoRefCount<cMWModel> mSocketConnector;  // +0x33c
  char pad_340[0xdc8 - 0x340];
  uint32_t mFlags[2];   // +0xdc8 (bitset<54>)
};

class cSPEditorSkinManager : public EA::COM::IUnknown32 {
 public:
  char pad_4[0xc - 0x4];
};

class cSPEditorManipulationObject : public EA::COM::IUnknown32 {
 public:
  virtual ~cSPEditorManipulationObject() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  char pad_7;
  float mDeadZoneSize;   // +0x8
  float mInitialX;       // +0xc
  float mInitialY;       // +0x10
};

class cSPEditorManipulationCellPinning : public cSPEditorManipulationObject, public EA::RefCountVTemplate<int> {
 public:
  eastl::sp_vector<EA::AutoRefCount<cSPEditorBlock> > mPileList;  // +0x1c
  EA::AutoRefCount<cSPEditorBlock> mBlock;                        // +0x30
  EA::AutoRefCount<cSPEditorBlock> mBumpedBlock;                  // +0x34
  cSPVector3 mMouseOffset;            // +0x38
  bool mRecalculateMouseOffset;       // +0x44
  char pad_45[3];
  cSPVector3 mMouseOffset3D;                 // +0x48
  cSPVector3 mVertexOffset;                  // +0x54
  cSPMatrix3 mInverseNormalTransform;        // +0x60
  cSPMatrix3 mInverseNormalTransform2;       // +0x84
  float mOffsetLength;                       // +0xa8
  float mOffsetRotation;                     // +0xac
  cSPVector3 mUnTransformedPosition;         // +0xb0
  cSPMatrix3 mUnTransformedOrientation;      // +0xbc
  EA::AutoRefCount<cSPEditorSkinManager> mSkin;  // +0xe0
  cMesh* mInflatedMesh;                          // +0xe4
  eastl::sp_vector<cSPVector3> mEdgePositions;    // +0xe8
  eastl::sp_vector<cSPVector3> mEdgeNormals;      // +0xfc
  eastl::sp_vector<cSPVector3> mEdgeTrueNormals;  // +0x110
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
  virtual eastl::sp_vector<EA::AutoRefCount<cSPEditorBlock> > GetPileList();

  void RecalculateMouseOffset(float x, float y);
  void CalculateInflatedMesh();   // 0x005aa7a0
};

}  // namespace SP
#endif  // SP_EDITOR_MANIP_SCAFFOLD_H
