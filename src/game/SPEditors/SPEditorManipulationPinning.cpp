// src/game/SPEditors/SPEditorManipulationPinning.cpp -- migrated from slice(s) s005b2d90, s005b1e30, s005b0f80 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorManipulationPinning.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorAnimatedEventInfo.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorManipulationObject.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorSkinManager.h"
#include "SP/cViewer.h"
#include <math.h>
#include <new>

// ---- items of slice s005b1e30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gSlerpEpsilonAngle;   // 0x01512690 (about 5 degrees in radians)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
class Vector3Template_s005b_1e30 {
 public:
  T x, y, z;
  Vector3Template_s005b_1e30() {}
  Vector3Template_s005b_1e30(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
}  // namespace rw::math::fpu
}
}
struct cSPVector3_s005b_1e30 : public rw::math::fpu::Vector3Template_s005b_1e30<float, 0> {
  typedef rw::math::fpu::Vector3Template_s005b_1e30<float, 0> base;
  cSPVector3_s005b_1e30() {}
  cSPVector3_s005b_1e30(float ax, float ay, float az) : base(ax, ay, az) {}
  cSPVector3_s005b_1e30(const cSPVector3_s005b_1e30& v) { x = v.x; y = v.y; z = v.z; }
};
inline cSPVector3_s005b_1e30 operator+(const cSPVector3_s005b_1e30& a, const cSPVector3_s005b_1e30& b) { return cSPVector3_s005b_1e30(a.x + b.x, a.y + b.y, a.z + b.z); }
struct QuaternionBase {
  float x, y, z, w;
};
struct cSPQuaternion_s005b_1e30 {
  float x, y, z, w;
  cSPQuaternion_s005b_1e30() {}
  cSPQuaternion_s005b_1e30(const QuaternionBase& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
  cSPQuaternion_s005b_1e30(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
  cSPQuaternion_s005b_1e30(const cSPQuaternion_s005b_1e30& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
  cSPQuaternion_s005b_1e30 operator-() const { return cSPQuaternion_s005b_1e30(-x, -y, -z, -w); }
  static float Dot(const cSPQuaternion_s005b_1e30& a, const cSPQuaternion_s005b_1e30& b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
  float Length() const { return sqrtf(Dot(*this, *this)); }
  cSPQuaternion_s005b_1e30 Normalized() const {
    float s = 1.0f / Length();
    return cSPQuaternion_s005b_1e30(x * s, y * s, z * s, w * s);
  }
};
inline cSPQuaternion_s005b_1e30 operator*(const cSPQuaternion_s005b_1e30& q, float s) { return cSPQuaternion_s005b_1e30(q.x * s, q.y * s, q.z * s, q.w * s); }
inline cSPQuaternion_s005b_1e30 operator+(const cSPQuaternion_s005b_1e30& a, const cSPQuaternion_s005b_1e30& b) { return cSPQuaternion_s005b_1e30(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
struct cSPMatrix3_s005b_1e30 {
  float m[9];
  cSPMatrix3_s005b_1e30() {}
  cSPMatrix3_s005b_1e30(const cSPMatrix3_s005b_1e30& src);   // 0x0041cb40 (Matrix3::Assign)
};
#define PV(n) virtual void pv##n();
namespace SP {
class cViewer_s005b_1e30 {
 public:
  bool GetWorldRayFromScreenCoords(float x, float y, cSPVector3_s005b_1e30& origin, cSPVector3_s005b_1e30& direction);  // 0x007c4730
};
}
namespace SP {
class cSPApp {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual cViewer_s005b_1e30* GetViewer();
};
}
namespace SP {
cSPApp* App();   // 0x0067dd10
}
namespace SP {
class cSPEditorModel_s005b_1e30 {
 public:
  float GetScale();            // FUN_004adaa0
  bool IsUsingSymmetry();      // FUN_004adc40
};
}
namespace SP {
class cSPEditorBlock_s005b_1e30 {
 public:
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  char pad04[0x28 - 4];
  cSPEditorModel_s005b_1e30* mEditorModel;   // +0x28
  char pad2c[0x48 - 0x2c];
  cSPVector3_s005b_1e30 mPosition;           // +0x48
  char pad54[0x60 - 0x54];
  float mRot[9];                  // +0x60 (3x3, row-major)
  char pad84[0xa8 - 0x84];
  cSPMatrix3_s005b_1e30 mTransform;          // +0xa8
  char padCC[0x33c - 0xcc];
  cSPEditorBlock_s005b_1e30* mParent;        // +0x33c
  void SetHighlight(int color, int a, int b, int c);   // FUN_0043a5e0
  void SetVecC(cSPVector3_s005b_1e30 v);                           // Tracker::SetVecC 0x00438270
};
}
namespace SP {
class cSPEditorSkinManager_s005b_1e30 {
 public:
  virtual void AddRef();
  virtual void Release();
};
}
namespace SP {
class cSPEditorAnimatedEventInfo_s005b_1e30 {
 public:
  cSPEditorAnimatedEventInfo_s005b_1e30();   // 0x0059d960
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  void MessageSend(uint32_t id, cSPEditorBlock_s005b_1e30* block, cSPEditorModel_s005b_1e30* model, int a, int b, float c, int d, int e, float f);   // 0x0059d8b0
  char pad[0x30 - 4];
};
}
namespace SP {
class cEditorMsgSink {
 public:
  void Fire();                                                  // FUN_0045b150
  void FireBlock(bool a, cSPEditorBlock_s005b_1e30* block, int b);         // FUN_0045ae40
};
}
namespace SP {
cEditorMsgSink* __stdcall GetMsgSink(unsigned int id);          // FUN_00401050
}
namespace SP {
class ICursor {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual void SetCursorPos(int x, int y);   // slot 4
};
}
namespace SP {
class cInputObj {
 public:
  virtual void v0();
  char pad[4];
  ICursor mCursor;
};
}
namespace SP {
cInputObj* GetInputObj();   // FUN_0067cab0
}
namespace SP {
namespace EditorUtils {
void RepinBlockToTorso(cSPEditorBlock_s005b_1e30* block, cSPVector3_s005b_1e30 pos, cSPMatrix3_s005b_1e30 orient, int flag);   // 0x0049fbd0
}
}
namespace SP {
namespace EditorUtils {
void DeleteInvalidBlocks(cSPEditorBlock_s005b_1e30* block, void* pileList);                              // 0x004a6f10
}
}
namespace SP {
namespace EditorUtils {
void SetSymmetricBlocksUIState(cSPEditorBlock_s005b_1e30* block, void* pileList, int state);             // 0x004a7f30
}
}
namespace SP {
void BuildPileList(cSPEditorBlock_s005b_1e30* block, void* pileList, int flag);                          // 0x0048c790
}
namespace SP {
cSPMatrix3_s005b_1e30* Matrix3FromQuaternion(cSPMatrix3_s005b_1e30* out, const cSPQuaternion_s005b_1e30* q);                   // 0x0059c190
}
namespace rw {
namespace math {
namespace fpu {
cSPQuaternion_s005b_1e30 QuaternionFromMatrix33(const cSPMatrix3_s005b_1e30& m, float tol);                          // 0x00472b80
}
}
}
namespace EA {
template <typename T>
class AutoRefCount_s005b_1e30 {
 public:
  T* mpObject;
  AutoRefCount_s005b_1e30() : mpObject(0) {}
  AutoRefCount_s005b_1e30(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s005b_1e30(const AutoRefCount_s005b_1e30& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005b_1e30() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005b_1e30& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  AutoRefCount_s005b_1e30& operator=(const AutoRefCount_s005b_1e30& x) { return operator=(x.mpObject); }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005b_1e30 {
 public:
  RefCountVTemplate_s005b_1e30() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005b_1e30() {}
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
  ~sp_vector();                      // 0x00453eb0
  T* erase(T* first, T* last);       // 0x00454280
};
}
namespace eastl {
template <typename T>
T* remove_copy(T* first, T* last, T* result, const T& value);
}
namespace eastl {
template <typename T>
T* remove(T* first, T* last, const T& value) {
  while (first != last && !(*first == value))
    ++first;
  if (first != last) {
    T* i = first;
    return eastl::remove_copy(++i, last, first, value);
  }
  return first;
}
}
extern cSPVector3_s005b_1e30 gPinMouseOffset2D;   // 0x015e9974 (runtime-initialised)
void WorldToScreen(const cSPVector3_s005b_1e30* world, float* outX, float* outY);                      // FUN_004a3760
cSPMatrix3_s005b_1e30* InvertRot(cSPMatrix3_s005b_1e30* out, const float* rot);                                   // FUN_0041ded0
cSPVector3_s005b_1e30 GetBlockVecC(SP::cSPEditorBlock_s005b_1e30* block);                                         // FUN_0049a0c0
void RemoveSymmetricPartners(SP::cSPEditorBlock_s005b_1e30* block, void* pileList);                    // FUN_004961d0
void ClearSymmetry(SP::cSPEditorBlock_s005b_1e30* block, void* pileList);                              // FUN_004a8860
void GetMissPlane(SP::cSPEditorBlock_s005b_1e30* block, cSPVector3_s005b_1e30 dir, cSPVector3_s005b_1e30* outPos, cSPVector3_s005b_1e30* outNormal);   // FUN_0049b8b0
float GetAlignmentPosition(SP::cSPEditorBlock_s005b_1e30* block, void* pileList, cSPVector3_s005b_1e30 pos, cSPMatrix3_s005b_1e30 m2,
                           float* a, float* b, bool* c, int d, cSPMatrix3_s005b_1e30 m1);               // SP::EditorUtils::GetAlignmentPosition 0x00490a70
cSPQuaternion_s005b_1e30 Lerp(const cSPQuaternion_s005b_1e30& a, const cSPQuaternion_s005b_1e30& b, float t);               // FUN_005b1cd0
namespace SP {
class cSPEditorManipulationObject_s005b_1e30 {
 public:
  cSPEditorManipulationObject_s005b_1e30();   // FUN_005b0f80
  virtual ~cSPEditorManipulationObject_s005b_1e30() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};
}
namespace SP {
class cSPEditorManipulationPinning : public cSPEditorManipulationObject_s005b_1e30, public EA::RefCountVTemplate_s005b_1e30<int> {
 public:
  EA::AutoRefCount_s005b_1e30<cSPEditorBlock_s005b_1e30> mBlock;                  // +0x1c
  EA::AutoRefCount_s005b_1e30<cSPEditorBlock_s005b_1e30> mBumpedBlock;            // +0x20
  cSPEditorBlock_s005b_1e30* mOriginalParent;                          // +0x24
  eastl::sp_vector<EA::AutoRefCount_s005b_1e30<cSPEditorBlock_s005b_1e30> > mPileList;   // +0x28
  cSPVector3_s005b_1e30 mMouseOffset;                                  // +0x3c
  EA::AutoRefCount_s005b_1e30<cSPEditorSkinManager_s005b_1e30> mSkin;             // +0x48
  bool mUseOffset;                                          // +0x4c
  cSPVector3_s005b_1e30 mMouseOffset2D;                                // +0x50
  cSPVector3_s005b_1e30 mMouseOffset3D;                                // +0x5c
  float mDistanceAlongOffset;                               // +0x68
  float mTotalElapsedTime;                                  // +0x6c
  int mX;                                                   // +0x70
  int mY;                                                   // +0x74
  bool mListenToMouseChange;                                // +0x78
  float mEffectScale;                                       // +0x7c
  bool mMoveCursor;                                         // +0x80
  bool mHaveNotAlreadyPlayedPinningEffect;                  // +0x81
  int mParentPreviousState;                                 // +0x84
  cSPQuaternion_s005b_1e30 mStartOrientation;                          // +0x88
  cSPQuaternion_s005b_1e30 mGoalOrientation;                           // +0x98
  cSPQuaternion_s005b_1e30 mTargetOrientation;                         // +0xa8
  cSPVector3_s005b_1e30 mTargetPosition;                               // +0xb8
  float mTotalOrientationTime;                              // +0xc4
  float mElapsedOrientationTime;                            // +0xc8
  cSPVector3_s005b_1e30 mMissPlanePosition;                            // +0xcc
  cSPVector3_s005b_1e30 mMissPlaneNormal;                              // +0xd8
  bool mIsAnimatingOrientation;                             // +0xe4
  bool mDidNotStack;                                        // +0xe5
  bool mManipulateCursor;                                   // +0xe6
  bool mDidMoveCursor;                                      // +0xe7
  bool mFlagE8;                                             // +0xe8

  cSPEditorManipulationPinning();
  ~cSPEditorManipulationPinning();
  bool OnMouseUp(int button, float x, float y, int modifiers);
  void Init(const EA::AutoRefCount_s005b_1e30<cSPEditorBlock_s005b_1e30>& block, cSPVector3_s005b_1e30 mouseOffset,
            EA::AutoRefCount_s005b_1e30<cSPEditorSkinManager_s005b_1e30> skin, bool manipulateCursor);
  bool DoOnMouseDown(int button, float x, float y, int modifiers);
  void Update(float dt);
};
}
struct cSPQuaternionW {
  float x, y, z, w;
  cSPQuaternionW() {}
  cSPQuaternionW& operator=(const cSPQuaternion_s005b_1e30& q) { x = q.x; y = q.y; z = q.z; w = q.w; return *this; }
};
// ---- items of slice s005b1e30 end

// ---- items of slice s005b2d90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t kPinningAlignOnFeedback;     // 0x015e9a0c
extern uint32_t kPinningAlignOffFeedback;    // 0x015e99a4
struct cSPVector3_s005b_2d90 {
  float x, y, z;
  cSPVector3_s005b_2d90() {}
  cSPVector3_s005b_2d90(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
  cSPVector3_s005b_2d90(const cSPVector3_s005b_2d90& v) : x(v.x), y(v.y), z(v.z) {}
  float Length() const { return sqrtf(x * x + y * y + z * z); }
};
inline cSPVector3_s005b_2d90 operator-(const cSPVector3_s005b_2d90& a, const cSPVector3_s005b_2d90& b) {
  return cSPVector3_s005b_2d90(a.x - b.x, a.y - b.y, a.z - b.z);
}
inline cSPVector3_s005b_2d90 operator*(const cSPVector3_s005b_2d90& a, float s) {
  return cSPVector3_s005b_2d90(a.x * s, a.y * s, a.z * s);
}
struct cSPMatrix3_s005b_2d90 {
  cSPVector3_s005b_2d90 xAxis, yAxis, zAxis;
  cSPMatrix3_s005b_2d90() {}
  cSPMatrix3_s005b_2d90(const cSPMatrix3_s005b_2d90& m);  // 0x0041cb40
};
struct cSPQuaternion_s005b_2d90 {
  float x, y, z, w;
  cSPQuaternion_s005b_2d90() {}
  cSPQuaternion_s005b_2d90(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
  cSPQuaternion_s005b_2d90 Normalized() const {
    float inv = 1.0f / sqrtf(w * w + z * z + y * y + x * x);
    return cSPQuaternion_s005b_2d90(x * inv, y * inv, z * inv, w * inv);
  }
};
struct hkAabb_s005b_2d90 {
  float mMin[4];
  float mMax[4];
};
namespace rw {
namespace math {
namespace fpu {
cSPQuaternion_s005b_2d90 QuaternionFromMatrix33(const cSPMatrix3_s005b_2d90& m, float tolerance);  // 0x00472b80
}
}
}
extern const cSPVector3_s005b_2d90 kEditorUpAxis;       // 0x015e9a70
extern const cSPVector3_s005b_2d90 kZeroVector;         // 0x015e9a24
extern const cSPMatrix3_s005b_2d90 kIdentityMatrix3;    // 0x015e9ba0
namespace EA {
template <typename T>
class AutoRefCount_s005b_2d90 {
 public:
  T* mpObject;
  AutoRefCount_s005b_2d90() : mpObject(0) {}
  AutoRefCount_s005b_2d90(T* p) : mpObject(p) {
    if (mpObject)
      mpObject->AddRef();
  }
  AutoRefCount_s005b_2d90(const AutoRefCount_s005b_2d90& x) : mpObject(x.mpObject) {
    if (mpObject)
      mpObject->AddRef();
  }
  ~AutoRefCount_s005b_2d90() {
    if (mpObject)
      mpObject->Release();
  }
  AutoRefCount_s005b_2d90& operator=(T* p);  // 0x004b09b0 (cSPEditorBlock instance)
  operator T*() const { return mpObject; }
  T* operator->() const { return mpObject; }
  void Reset() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
  }
};
}
namespace EA {
namespace Swarm {
struct cTransform_s005b_2d90 {
  uint16_t mFlags;        // +0x00
  uint16_t mChangeCount;  // +0x02
  cSPVector3_s005b_2d90 mOffset;     // +0x04
  float mScale;           // +0x10
  cSPMatrix3_s005b_2d90 mRotation;   // +0x14
  cTransform_s005b_2d90()
      : mFlags(0), mChangeCount(0), mOffset(kZeroVector), mScale(1.0f), mRotation(kIdentityMatrix3) {}
  void SetOffset(const cSPVector3_s005b_2d90& v) {
    mOffset = v;
    mChangeCount++;
    mFlags |= 4;
  }
  void SetRotation(const cSPMatrix3_s005b_2d90& m) {
    mRotation = m;
    mFlags |= 2;
    mChangeCount++;
  }
  void SetScale(float s) {
    mScale = s;
    mChangeCount++;
  }
};  // namespace Swarm
}
}
namespace eastl {
struct sp_vector_allocator_s005b_2d90 {  // retail: 8 bytes, so a vector is 0x14 bytes
  uint32_t mName[2];
  sp_vector_allocator_s005b_2d90() {}
};
}
namespace eastl {
template <typename T>
class vector_s005b_2d90 {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator_s005b_2d90 mAllocator;
  vector_s005b_2d90() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~vector_s005b_2d90();                                       // 0x00453eb0
  void DoInsertValue(T* position, const T& value);  // 0x00454ee0
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};
}
namespace SP {
class cSPEditorBlock_s005b_2d90;
}
namespace SP {
typedef eastl::vector_s005b_2d90<EA::AutoRefCount_s005b_2d90<cSPEditorBlock_s005b_2d90> > PileList;
}
namespace SP {
class cSPEditorModel_s005b_2d90 {
 public:
  bool UsingSymmetry();  // 0x004adc40
};
}
namespace SP {
class cSPEditorSkinManager_s005b_2d90 {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
namespace SP {
enum {
  kAttrIsVertebra = 0x07,
  kAttrHasBallAndSocket = 0x0b,
  kAttrSnapped = 0x0c,
  kAttrOnSymmetryPlane = 0x0f,
  kAttrPreferToBeOnPlaneOfSymmetry = 0x22,
  kAttrCanBeParentless = 0x23,
  kAttrIsAllowedOutOfBounds = 0x33,
  kAttrAllowTopBehaviors = 0x37
};
}
namespace SP {
class cSPEditorBlock_s005b_2d90 {
 public:
  virtual ~cSPEditorBlock_s005b_2d90();
  virtual int AddRef();
  virtual int Release();
  uint32_t pad04[(0x28 - 0x04) / 4];
  cSPEditorModel_s005b_2d90* mpEditorModel;         // +0x28
  uint32_t pad2c[(0x3c - 0x2c) / 4];
  int mUIState;                          // +0x3c
  uint32_t pad40[(0x48 - 0x40) / 4];
  cSPVector3_s005b_2d90 mPosition;                  // +0x48
  cSPVector3_s005b_2d90 mHistoryPosition;           // +0x54
  cSPMatrix3_s005b_2d90 mOrientation;               // +0x60
  cSPMatrix3_s005b_2d90 mHistoryOrientation;        // +0x84
  cSPMatrix3_s005b_2d90 mBaseOrientation;           // +0xa8
  cSPMatrix3_s005b_2d90 mHistoryBaseOrientation;    // +0xcc
  cSPMatrix3_s005b_2d90 mUserOrientation;           // +0xf0
  uint32_t pad114[(0x18c - 0x114) / 4];
  void* mpPhysicsBlock;                  // +0x18c
  uint32_t pad190[(0x33c - 0x190) / 4];
  cSPEditorBlock_s005b_2d90* mpParent;              // +0x33c (AutoRefCount)
  uint32_t pad340[(0x3c8 - 0x340) / 4];
  bool pad3c8;
  bool mIsOnGround;                      // +0x3c9
  uint8_t pad3ca[2];
  uint32_t pad3cc[(0x3e0 - 0x3cc) / 4];
  cSPEditorBlock_s005b_2d90* mpSymmetricBlock;      // +0x3e0 (AutoRefCount)
  uint32_t pad3e4[(0xdc8 - 0x3e4) / 4];
  uint32_t mBooleanAttributes[2];        // +0xdc8 (bitset)

  bool GetBooleanAttribute(int index) const {
    return (mBooleanAttributes[index >> 5] >> (index & 31)) & 1;
  }
  void SetBooleanAttribute(int index, bool value);                 // 0x00435a10
  void SetSnapType(int type);                                      // 0x0044e7c0
  void GetPhysicsAABB(hkAabb_s005b_2d90& box, bool b);                        // 0x0044aaa0
  void SetParentTriangle(int triangleIndex, bool hitHull);         // 0x00451240
  void SetIsOnGround(bool onGround);                               // 0x0049c0f0
  void SetUserOrientation(cSPMatrix3_s005b_2d90 orientation);                 // 0x0043ffa0
  int GetSymmetrySign();                                           // 0x0044f220
  int CalculateSymmetrySign();                                     // 0x0044f240
  void RemoveChild(cSPEditorBlock_s005b_2d90* child);                         // 0x00438a40
  void AddChild(cSPEditorBlock_s005b_2d90* child);                            // 0x00438700
  cSPVector3_s005b_2d90 GetTrianglePickDirection(bool b);                     // 0x00438120
  int GetParentTriangle();                                         // 0x004511f0
  void RecordPosition(int triangle, cSPVector3_s005b_2d90 position, cSPVector3_s005b_2d90 direction, bool b);  // 0x004370a0
  void UpdateAfterMove();                                          // 0x0044ede0 (name guessed)
  void SetModelBasedOnSymmetrySign(int sign, bool a, bool b, bool c, bool d);  // 0x00439110
  void SetSymmetrySign(int sign);                                  // 0x0044e980 (name guessed)
  void SetUIState(int state, bool a, bool b, bool c);              // 0x0043a5e0
  cSPMatrix3_s005b_2d90 GetNeutralOrientation(cSPVector3_s005b_2d90 direction);          // 0x004494b0
  void SetBlockPickDirection(cSPVector3_s005b_2d90 direction);                // 0x00438270
};
}
namespace SP {
cSPMatrix3_s005b_2d90 Matrix3FromQuaternion(const cSPQuaternion_s005b_2d90& q);          // 0x0059c190
}
namespace SP {
cSPQuaternion_s005b_2d90 QuaternionFromMatrix3(const cSPMatrix3_s005b_2d90& m);          // 0x0046d660
}
namespace SP {
cSPQuaternion_s005b_2d90 normalized(const cSPQuaternion_s005b_2d90& q);                  // 0x00799320
}
namespace SP {
class cSPEditorEffects {
 public:
  void SetVisibility(uint32_t id, bool visible);                   // 0x0045b110
  int Get(uint32_t id);                                            // 0x0045b210
  void Stop(uint32_t id);                                          // 0x0045b000
  void SetTransform(uint32_t id, cSPEditorBlock_s005b_2d90* block);           // 0x0045b080
  void SetTransform(uint32_t id, const EA::Swarm::cTransform_s005b_2d90& t);  // 0x0045b040
};
}
namespace SP {
cSPEditorEffects* EditorEffects();                                 // 0x00401050
}
namespace SP {
class ICursorMover {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual void SetCursorPosition(int x, int y);                    // +0x10
};
}
namespace SP {
class cCursorManagerBase {
 public:
  virtual void pv0();
  uint32_t mField4;
};
}
namespace SP {
class cCursorManager : public cCursorManagerBase, public ICursorMover {};
}
namespace SP {
cCursorManager* CursorManager();                                   // 0x0067cab0
}
namespace SP {
class cViewer_s005b_2d90 {
 public:
  void GetWorldRayFromScreenCoords(float x, float y, cSPVector3_s005b_2d90& origin, cSPVector3_s005b_2d90& direction);  // 0x007c4730
};
}
namespace SP {
class cApp {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual cViewer_s005b_2d90* GetViewer();                                    // +0x58
};
}
namespace SP {
cApp* App_s005b_2d90();                                                       // 0x0067dd10
}
namespace SP {
namespace EditorUtils {
bool MoveBlockAndPile(cSPEditorBlock_s005b_2d90* block, cSPVector3_s005b_2d90 position, cSPMatrix3_s005b_2d90 orientation, bool b);  // 0x0049fbd0
}
}
namespace SP {
namespace EditorUtils {
int GetOrientToSurfaces(cSPEditorBlock_s005b_2d90* block, cSPVector3_s005b_2d90 origin, cSPVector3_s005b_2d90 direction,
                        EA::AutoRefCount_s005b_2d90<cSPEditorSkinManager_s005b_2d90> skin, cSPVector3_s005b_2d90& hitPoint,
                        cSPVector3_s005b_2d90& hitNormal, PileList& pileList);                                 // 0x00499410
}
}
namespace SP {
namespace EditorUtils {
cSPEditorBlock_s005b_2d90* GetSnapPoint(cSPEditorBlock_s005b_2d90* block, PileList& pileList, cSPVector3_s005b_2d90 origin,
                             cSPVector3_s005b_2d90 direction, cSPVector3_s005b_2d90& snapPoint);                         // 0x004a3dc0
}
}
namespace SP {
namespace EditorUtils {
void UnsnapBlock(cSPEditorBlock_s005b_2d90* block);                                                           // 0x004a1070
}
}
namespace SP {
namespace EditorUtils {
void RecordBlockAndPileHistory(cSPEditorBlock_s005b_2d90* block, PileList& pileList);                         // 0x004961d0
}
}
namespace SP {
namespace EditorUtils {
bool MoveBlockOrientToSurfaces(cSPEditorBlock_s005b_2d90* block, PileList& pileList, cSPVector3_s005b_2d90 origin,
                               cSPVector3_s005b_2d90 direction, EA::AutoRefCount_s005b_2d90<cSPEditorSkinManager_s005b_2d90> skin,
                               cSPVector3_s005b_2d90& stackingPosition, cSPVector3_s005b_2d90* pickNormal, bool animate,
                               bool b);                                                            // 0x0049a2a0
}
}
namespace SP {
namespace EditorUtils {
void CalculateMissPlane(cSPEditorBlock_s005b_2d90* block, cSPVector3_s005b_2d90 direction, cSPVector3_s005b_2d90* planePosition,
                        cSPVector3_s005b_2d90* planeNormal);                                                  // 0x0049b8b0
}
}
namespace SP {
namespace EditorUtils {
void PlaceBlockInScene(cSPEditorBlock_s005b_2d90* block, cSPVector3_s005b_2d90 origin, cSPVector3_s005b_2d90 direction,
                       cSPVector3_s005b_2d90 planePosition, cSPVector3_s005b_2d90 planeNormal, bool b);                 // 0x0049bcc0
}
}
namespace SP {
namespace EditorUtils {
void SnapBlockToSocket(cSPEditorBlock_s005b_2d90* block, PileList& pileList, cSPEditorBlock_s005b_2d90* parent);         // 0x004a29a0
}
}
namespace SP {
namespace EditorUtils {
void CheckAndSnapBlockToPlaneOfSymmetry(cSPEditorBlock_s005b_2d90* block, bool b, float scale, bool c);       // 0x004982b0
}
}
namespace SP {
namespace EditorUtils {
bool CheckAndSnapBlockToPlaneOfSymmetry(cSPEditorBlock_s005b_2d90* block, cSPVector3_s005b_2d90& position,
                                        cSPMatrix3_s005b_2d90& orientation, cSPMatrix3_s005b_2d90& userOrientation,
                                        bool a, float scale, bool b, bool c);                     // 0x00498470
}
}
namespace SP {
namespace EditorUtils {
cSPEditorBlock_s005b_2d90* PickBlocks(PileList& pickList, cSPVector3_s005b_2d90 origin, cSPVector3_s005b_2d90 direction,
                           cSPVector3_s005b_2d90& pickPoint, cSPVector3_s005b_2d90& pickNormal, int* triangleIndex,
                           bool& hitHull, int* pickLevel);                                         // 0x004a4840
}
}
namespace SP {
namespace EditorUtils {
cSPMatrix3_s005b_2d90 CalculateTopOrientation(cSPEditorBlock_s005b_2d90* parent, cSPVector3_s005b_2d90 position);                   // 0x0049b460
}
}
namespace SP {
namespace EditorUtils {
bool GetRotationAndPositionBasedOnBehavior(cSPEditorBlock_s005b_2d90* block, cSPVector3_s005b_2d90& position,
                                           cSPMatrix3_s005b_2d90& orientation, cSPVector3_s005b_2d90 oldPosition,
                                           bool a, bool isOnTopOfParent);                         // 0x004942b0
}
}
namespace SP {
namespace EditorUtils {
float GetAlignmentPosition(cSPEditorBlock_s005b_2d90* block, PileList& pileList, cSPVector3_s005b_2d90 position,
                           cSPMatrix3_s005b_2d90 orientation, cSPVector3_s005b_2d90& newPosition, cSPMatrix3_s005b_2d90& newOrientation,
                           bool& setOnGround, bool isOnTopOfParent, cSPMatrix3_s005b_2d90 oldOrientation);   // 0x00490a70
}
}
namespace SP {
namespace EditorUtils {
cSPEditorBlock_s005b_2d90* PickBlockForPinning(cSPEditorBlock_s005b_2d90* block, PileList& pileList, cSPVector3_s005b_2d90 origin,
                                    cSPVector3_s005b_2d90 direction, cSPVector3_s005b_2d90& hitPoint, cSPVector3_s005b_2d90& hitNormal,
                                    bool& hitHull, int* triangleIndex);                           // 0x004a4d60
}
}
namespace SP {
namespace EditorUtils {
void PlayFeedback(uint32_t id);                                                                    // 0x004a88d0 (name guessed)
}
}
namespace SP {
namespace EditorUtils {
cSPEditorBlock_s005b_2d90* GetSurfaceSnapReplace(cSPEditorBlock_s005b_2d90* block, cSPVector3_s005b_2d90 position);                // 0x004a3c70
}
}
namespace SP {
namespace EditorUtils {
bool UnsnapReplaceBlock(cSPEditorBlock_s005b_2d90* block);                                                    // 0x004a1e10
}
}
namespace SP {
namespace EditorUtils {
bool DoSnapReplace(cSPEditorBlock_s005b_2d90* block, cSPEditorBlock_s005b_2d90* replace, cSPVector3_s005b_2d90& position,
                   cSPMatrix3_s005b_2d90& orientation);                                                       // 0x004a2350
}
}
namespace SP {
namespace EditorUtils {
void DoPlaneOfSymmetryEffect(cSPEditorBlock_s005b_2d90* block, bool wasOnPlane);                              // 0x004983d0
}
}
namespace SP {
namespace EditorUtils {
void SetSymmetricBlocksUIState(cSPEditorBlock_s005b_2d90* block, PileList* pileList, bool b);                 // 0x004a7f30
}
}
namespace SP {
namespace EditorUtils {
void MarkInvalidBlocks(cSPEditorBlock_s005b_2d90* block, PileList* pileList, bool a, bool b, bool c, bool d,
                       bool e, bool f);                                                            // 0x004a6d20
}
}
namespace SP {
namespace EditorUtils {
cSPVector3_s005b_2d90 GetNearestBlockDirection(cSPEditorBlock_s005b_2d90* block);                                        // 0x0049a0c0
}
}
namespace SP {
const uint32_t kPinningEffect = 0x3f1bf5d;
}
namespace SP {
const uint32_t kPinningCursorEffect = 0x3f1bf5e;
}
namespace SP {
class cSPEditorManipulationPinning_s005b_2d90 {
 public:
  virtual void pv0();
  bool mChangedObject;                                // +0x04
  bool mUseDeadZone;                                  // +0x05
  bool mMovedOutsideDeadZone;                         // +0x06
  float mDeadZoneSize;                                // +0x08
  float mInitialX;                                    // +0x0c
  float mInitialY;                                    // +0x10
  void* mRefCountVtbl;                                // +0x14
  int mRefCount;                                      // +0x18
  cSPEditorBlock_s005b_2d90* mBlock;                             // +0x1c (AutoRefCount)
  EA::AutoRefCount_s005b_2d90<cSPEditorBlock_s005b_2d90> mBumpedBlock;      // +0x20
  cSPEditorBlock_s005b_2d90* mOriginalParent;                    // +0x24
  PileList mPileList;                                 // +0x28
  cSPVector3_s005b_2d90 mMouseOffset;                            // +0x3c
  EA::AutoRefCount_s005b_2d90<cSPEditorSkinManager_s005b_2d90> mSkin;       // +0x48
  bool mUseOffset;                                    // +0x4c
  cSPVector3_s005b_2d90 mMouseOffset2D;                          // +0x50
  cSPVector3_s005b_2d90 mMouseOffset3D;                          // +0x5c
  float mDistanceAlongOffset;                         // +0x68
  float mTotalElapsedTime;                            // +0x6c
  int mX;                                             // +0x70
  int mY;                                             // +0x74
  bool mListenToMouseChange;                          // +0x78
  float mEffectScale;                                 // +0x7c
  bool mMoveCursor;                                   // +0x80
  bool mHaveNotAlreadyPlayedPinningEffect;            // +0x81
  int mParentPreviousState;                           // +0x84
  cSPQuaternion_s005b_2d90 mStartOrientation;                    // +0x88
  cSPQuaternion_s005b_2d90 mGoalOrientation;                     // +0x98
  cSPQuaternion_s005b_2d90 mTargetOrientation;                   // +0xa8
  cSPVector3_s005b_2d90 mTargetPosition;                         // +0xb8
  float mTotalOrientationTime;                        // +0xc4
  float mElapsedOrientationTime;                      // +0xc8
  cSPVector3_s005b_2d90 mMissPlanePosition;                      // +0xcc
  cSPVector3_s005b_2d90 mMissPlaneNormal;                        // +0xd8
  bool mIsAnimatingOrientation;                       // +0xe4
  bool mDidNotStack;                                  // +0xe5
  bool mManipulateCursor;                             // +0xe6
  bool mDidMoveCursor;                                // +0xe7
  bool mAlignFeedbackOn;                              // +0xe8 (retail only)

  bool DoOnMouseMove(float x, float y, uint32_t modifiers);
};
}
// ---- items of slice s005b2d90 end

// @ 0x005b1c80
void Stub_005b1c80()
{}

// @ 0x005b1cd0
void Stub_005b1cd0()
{}

// @ 0x005b1e30
namespace SP {
bool cSPEditorManipulationPinning::OnMouseUp(int button, float x, float y, int modifiers)
{
  if (mManipulateCursor && mBlock.mpObject) {
    cSPVector3_s005b_1e30 world(
        mBlock->mPosition.x + ((mBlock->mRot[3] * mMouseOffset3D.y + mBlock->mRot[6] * mMouseOffset3D.z) +
                               mMouseOffset3D.x * mBlock->mRot[0]),
        mBlock->mPosition.y + ((mBlock->mRot[1] * mMouseOffset3D.x + mBlock->mRot[4] * mMouseOffset3D.y) +
                               mBlock->mRot[7] * mMouseOffset3D.z),
        mBlock->mPosition.z + ((mBlock->mRot[2] * mMouseOffset3D.x + mBlock->mRot[5] * mMouseOffset3D.y) +
                               mBlock->mRot[8] * mMouseOffset3D.z));
    float sx, sy;
    WorldToScreen(&world, &sx, &sy);
    float dx = sx - x;
    float dy = sy - y;
    float dist = sqrtf(dx * dx + dy * dy);
    if (mMoveCursor && dist > 20.0f)
      GetInputObj()->mCursor.SetCursorPos((int)sx, (int)sy);
  }

  cSPMatrix3_s005b_1e30 rot;
  Matrix3FromQuaternion(&rot, &mTargetOrientation);
  EditorUtils::RepinBlockToTorso(mBlock.mpObject, mTargetPosition, rot, 0);
  GetMsgSink(0x03f1bf5d)->Fire();
  GetMsgSink(0x03f1bf5e)->Fire();

  if (mChangedObject) {
    if (mOriginalParent) {
      if (mBlock.mpObject->mParent) {
        EA::AutoRefCount_s005b_1e30<cSPEditorAnimatedEventInfo_s005b_1e30> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo_s005b_1e30());
        info->MessageSend(0xda95baa5, mBlock.mpObject, mBlock.mpObject == 0 ? 0 : mBlock.mpObject->mEditorModel, 0, 0,
                          0.0f, 0, -1, 1.0f);
      } else {
        EA::AutoRefCount_s005b_1e30<cSPEditorAnimatedEventInfo_s005b_1e30> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo_s005b_1e30());
        info->MessageSend(0x0428e920, mBlock.mpObject, mBlock.mpObject == 0 ? 0 : mBlock.mpObject->mEditorModel, 0, 0,
                          0.0f, 0, -1, 1.0f);
      }
    } else if (mBlock.mpObject->mParent) {
      EA::AutoRefCount_s005b_1e30<cSPEditorAnimatedEventInfo_s005b_1e30> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo_s005b_1e30());
      info->MessageSend(0x8e04ce1a, mBlock.mpObject, mBlock.mpObject == 0 ? 0 : mBlock.mpObject->mEditorModel, 0, 0,
                        0.0f, 0, -1, 1.0f);
    }
  }

  if (mBlock.mpObject->mParent) {
    cSPEditorBlock_s005b_1e30* parent = mBlock.mpObject->mParent;
    parent->SetHighlight(mParentPreviousState, 1, 0, 1);
    cSPEditorBlock_s005b_1e30* b = mBlock.mpObject;
    b->SetVecC(*(cSPVector3_s005b_1e30*)&b->mRot[3]);
  }
  EditorUtils::DeleteInvalidBlocks(mBlock.mpObject, &mPileList);
  return true;
}
}  // namespace SP

// @ 0x005b2180
namespace SP {
void cSPEditorManipulationPinning::Init(const EA::AutoRefCount_s005b_1e30<cSPEditorBlock_s005b_1e30>& block, cSPVector3_s005b_1e30 mouseOffset, EA::AutoRefCount_s005b_1e30<cSPEditorSkinManager_s005b_1e30> skin, bool manipulateCursor)
{
  mManipulateCursor = manipulateCursor;
  mBlock = block.mpObject;
  mMouseOffset = mouseOffset;
  mSkin = skin;
  if (mBlock.mpObject) {
    mOriginalParent = mBlock.mpObject->mParent;
    if (mBlock.mpObject->mEditorModel)
      mEffectScale = mBlock.mpObject->mEditorModel->GetScale() * 0.0625f;
    const float nx = -mouseOffset.x;
    const float ny = -mouseOffset.y;
    const float nz = -mouseOffset.z;
    cSPMatrix3_s005b_1e30 invTmp;
    cSPMatrix3_s005b_1e30* inv = InvertRot(&invTmp, block->mRot);
    const float* m = inv->m;
    mMouseOffset3D.x = (m[6] * nz + m[3] * ny) + m[0] * nx;
    mMouseOffset3D.y = (m[7] * nz + m[4] * ny) + m[1] * nx;
    mMouseOffset3D.z = (m[8] * nz + m[5] * ny) + m[2] * nx;
    cSPEditorBlock_s005b_1e30* b = mBlock.mpObject;
    if (b->mParent == 0)
      b->SetVecC(GetBlockVecC(b));
  }
  mUseOffset = true;
  mDidNotStack = true;
}
}  // namespace SP

// @ 0x005b2350
cSPQuaternion_s005b_1e30 Nlerp(const cSPQuaternion_s005b_1e30& a, const cSPQuaternion_s005b_1e30& b, float t)
{
  return Lerp(a, b, t).Normalized();
}

// @ 0x005b23d0
namespace SP {
cSPEditorManipulationPinning::cSPEditorManipulationPinning()
: mBlock(), mBumpedBlock(), mPileList(), mMouseOffset(0.0f, 0.0f, 0.0f), mSkin(), mUseOffset(true),
      mMouseOffset2D(gPinMouseOffset2D), mListenToMouseChange(true), mEffectScale(1.0f), mMoveCursor(false),
      mHaveNotAlreadyPlayedPinningEffect(true), mIsAnimatingOrientation(false), mDidNotStack(false),
      mDidMoveCursor(false), mFlagE8(false) {
  mChangedObject = false;
}
}  // namespace SP

// @ 0x005b24a0
namespace SP {
cSPEditorManipulationPinning::~cSPEditorManipulationPinning()
{}
}  // namespace SP

// @ 0x005b2500
cSPQuaternion_s005b_1e30 Slerp(const cSPQuaternion_s005b_1e30& a, const cSPQuaternion_s005b_1e30& b, float t)
{
  cSPQuaternion_s005b_1e30 q0(a);
  cSPQuaternion_s005b_1e30 q1(b);
  float dot = cSPQuaternion_s005b_1e30::Dot(q0, q1);
  if (dot < 0.0f) {
    q0 = -q0;
    dot = -dot;
  }
  if (dot > cos(gSlerpEpsilonAngle))
    return Nlerp(q0, b, t);
  float omega = acos(dot);
  float inv = 1.0f / sin(omega);
  float s0 = sin((1.0f - t) * omega) * inv;
  float s1 = sin(t * omega) * inv;
  return q0 * s0 + q1 * s1;
}

// @ 0x005b26f0
cSPQuaternionW SlerpWrap(const cSPQuaternion_s005b_1e30& a, const cSPQuaternion_s005b_1e30& b, float t)
{
  cSPQuaternionW r;
  r = Slerp(a, b, t);
  return r;
}

// @ 0x005b2750
namespace SP {
void cSPEditorManipulationPinning::Update(float dt)
{
  cSPVector3_s005b_1e30 origin, dir;
  App()->GetViewer()->GetWorldRayFromScreenCoords((float)mX + mMouseOffset2D.x, (float)mY + mMouseOffset2D.y, origin, dir);

  cSPEditorBlock_s005b_1e30* b = mBlock.mpObject;
  cSPVector3_s005b_1e30 pos(b->mPosition.x, b->mPosition.y, b->mPosition.z);
  cSPVector3_s005b_1e30 newPos(b->mPosition.x, b->mPosition.y, b->mPosition.z);
  cSPMatrix3_s005b_1e30 m(b->mTransform);
  cSPQuaternion_s005b_1e30 q = rw::math::fpu::QuaternionFromMatrix33(m, 0.0f);
  float dts = dt * 0.001f;
  if (dts > 0.05f)
    dts = 0.05f;

  if (pos.x != mTargetPosition.x || pos.y != mTargetPosition.y || pos.z != mTargetPosition.z) {
    float dx = ((mTargetPosition.x - pos.x) * dts) * 12.0f;
    float dy = ((mTargetPosition.y - pos.y) * dts) * 12.0f;
    float dz = ((mTargetPosition.z - pos.z) * dts) * 12.0f;
    newPos = cSPVector3_s005b_1e30(pos.x + dx, pos.y + dy, pos.z + dz);
  }
  if (q.x != mTargetOrientation.x || q.y != mTargetOrientation.y || q.z != mTargetOrientation.z ||
      q.w != mTargetOrientation.w) {
    q = Slerp(q, mTargetOrientation, dts * 12.0f);
  }

  cSPMatrix3_s005b_1e30 rot;
  Matrix3FromQuaternion(&rot, &q);
  EditorUtils::RepinBlockToTorso(mBlock.mpObject, newPos, rot, 0);
  EditorUtils::SetSymmetricBlocksUIState(mBlock.mpObject, &mPileList, 0);

  if (mTotalElapsedTime < 1.0f) {
    mTotalElapsedTime += dts;
    if (mTotalElapsedTime >= 1.0f)
      mMoveCursor = false;
  }
}
}  // namespace SP

// @ 0x005b2a50
namespace SP {
bool cSPEditorManipulationPinning::DoOnMouseDown(int button, float x, float y, int modifiers)
{
  cSPEditorModel_s005b_1e30* model = mBlock.mpObject->mEditorModel;
  mX = (int)x;
  mY = (int)y;
  if (mBlock.mpObject) {
    float sx, sy;
    WorldToScreen(&mBlock.mpObject->mPosition, &sx, &sy);
    mMouseOffset2D.x = (float)(int)(sx - x);
    mMouseOffset2D.y = (float)(int)(sy - y);
  }
  mDistanceAlongOffset = 0.0f;
  mPileList.erase(mPileList.mpBegin, mPileList.mpEnd);
  BuildPileList(mBlock.mpObject, &mPileList, 0);
  EA::AutoRefCount_s005b_1e30<cSPEditorBlock_s005b_1e30>* end = mPileList.mpEnd;
  mPileList.erase(eastl::remove(mPileList.mpBegin, end, mBlock), end);
  RemoveSymmetricPartners(mBlock.mpObject, &mPileList);
  if (!model->IsUsingSymmetry())
    ClearSymmetry(mBlock.mpObject, &mPileList);
  EditorUtils::SetSymmetricBlocksUIState(mBlock.mpObject, &mPileList, 0);
  if (mBlock.mpObject->mParent) {
    mParentPreviousState = *(int*)((char*)mBlock.mpObject->mParent + 0x3c);
    mBlock.mpObject->mParent->SetHighlight(2, 1, 0, 1);
  }
  GetMsgSink(0x03f1bf5d)->FireBlock(true, mBlock.mpObject, 0);
  if (mManipulateCursor) {
    mMoveCursor = true;
    mTotalElapsedTime = 0.0f;
  }

  cSPVector3_s005b_1e30 origin, dir;
  App()->GetViewer()->GetWorldRayFromScreenCoords((float)mX, (float)mY, origin, dir);
  GetMissPlane(mBlock.mpObject, dir, &mMissPlanePosition, &mMissPlaneNormal);
  mTargetPosition = mBlock->mPosition;
  mTargetOrientation = rw::math::fpu::QuaternionFromMatrix33(mBlock->mTransform, 0.0f);
  mBumpedBlock = 0;

  cSPVector3_s005b_1e30 pos(mBlock->mPosition);
  cSPMatrix3_s005b_1e30 orientCopy(mBlock->mTransform);
  bool flag = false;
  float a, b;
  float r = GetAlignmentPosition(mBlock.mpObject, &mPileList, mBlock->mPosition, mBlock.mpObject->mTransform, &a, &b, &flag, 0,
                                 mBlock.mpObject->mTransform);
  if (r != -1.0f)
    mFlagE8 = true;
  return true;
}
}  // namespace SP

// @ 0x005b2d90
namespace SP {
bool cSPEditorManipulationPinning_s005b_2d90::DoOnMouseMove(float x, float y, uint32_t modifiers)
{
  if (mBlock->GetBooleanAttribute(kAttrCanBeParentless) &&
      !mBlock->GetBooleanAttribute(kAttrIsAllowedOutOfBounds)) {
    mBlock->SetBooleanAttribute(kAttrCanBeParentless, false);
    mBlock->SetBooleanAttribute(kAttrIsAllowedOutOfBounds, true);
  }

  if (mManipulateCursor && !mDidMoveCursor) {
    mUseOffset = false;
    x += mMouseOffset2D.x;
    y += mMouseOffset2D.y;
    mInitialX += mMouseOffset2D.x;
    mInitialY += mMouseOffset2D.y;
    CursorManager()->SetCursorPosition((int)x, (int)y);
    mDidMoveCursor = true;
  }

  mX = (int)x;
  mY = (int)y;

  cSPVector3_s005b_2d90 trueBlockOriginalPosition = mBlock->mPosition;
  cSPMatrix3_s005b_2d90 trueBlockOriginalRotation(mBlock->mBaseOrientation);
  EditorUtils::MoveBlockAndPile(mBlock, mTargetPosition, Matrix3FromQuaternion(mTargetOrientation), false);
  cSPMatrix3_s005b_2d90 blockOriginalRotation(mBlock->mBaseOrientation);

  if (mUseOffset) {
    x += mMouseOffset2D.x;
    y += mMouseOffset2D.y;
  }

  cSPVector3_s005b_2d90 origin;
  cSPVector3_s005b_2d90 dir;
  App_s005b_2d90()->GetViewer()->GetWorldRayFromScreenCoords(x, y, origin, dir);

  cSPVector3_s005b_2d90 originalPosition = mBlock->mPosition;
  cSPEditorBlock_s005b_2d90* originalParent = mBlock->mpParent;

  cSPVector3_s005b_2d90 skinHitPoint;
  cSPVector3_s005b_2d90 skinHitNormal;
  int orientResult = EditorUtils::GetOrientToSurfaces(mBlock, origin, dir, mSkin, skinHitPoint,
                                                      skinHitNormal, mPileList);
  cSPVector3_s005b_2d90 snapHitPoint;
  cSPEditorBlock_s005b_2d90* snapParent = EditorUtils::GetSnapPoint(mBlock, mPileList, origin, dir, snapHitPoint);

  bool shouldSnap = false;
  bool needToRePin = false;
  mDidNotStack = true;

  if (orientResult) {
    if (snapParent && (snapHitPoint - origin).Length() < (skinHitPoint - origin).Length() &&
        !snapParent->GetBooleanAttribute(kAttrIsVertebra))
      shouldSnap = true;
  } else if (snapParent) {
    shouldSnap = true;
  }

  if (shouldSnap) {
    if (snapParent != mBlock->mpParent) {
      EditorUtils::RecordBlockAndPileHistory(mBlock, mPileList);
      EditorUtils::SnapBlockToSocket(mBlock, mPileList, snapParent);
      float snapScale = 1.0f;
      if (mBlock->GetBooleanAttribute(kAttrPreferToBeOnPlaneOfSymmetry))
        snapScale = 1.5f;
      EditorUtils::CheckAndSnapBlockToPlaneOfSymmetry(mBlock, true, snapScale, false);
    }
  } else {
    if (mBlock->GetBooleanAttribute(kAttrSnapped))
      EditorUtils::UnsnapBlock(mBlock);
    EditorUtils::RecordBlockAndPileHistory(mBlock, mPileList);

    cSPVector3_s005b_2d90 stackingPosition;
    cSPVector3_s005b_2d90 pickNormal;
    mDidNotStack = EditorUtils::MoveBlockOrientToSurfaces(mBlock, mPileList, origin, dir, mSkin,
                                                          stackingPosition, &pickNormal,
                                                          mIsAnimatingOrientation, false);
    if (!mBlock->mpParent && originalParent)
      EditorUtils::CalculateMissPlane(mBlock, dir, &mMissPlanePosition, &mMissPlaneNormal);
    if (!mBlock->mpParent) {
      if (mDidNotStack)
        EditorUtils::PlaceBlockInScene(mBlock, origin, dir, mMissPlanePosition, mMissPlaneNormal, true);
      else
        EditorUtils::MoveBlockAndPile(mBlock, stackingPosition, mBlock->mBaseOrientation, false);
    }

    cSPVector3_s005b_2d90 newPosition = mBlock->mPosition;
    cSPMatrix3_s005b_2d90 newRotation(mBlock->mBaseOrientation);

    if (mBlock->mpParent) {
      cSPVector3_s005b_2d90 physicsPickPoint = mBlock->mPosition;
      cSPVector3_s005b_2d90 physicsPickNormal = pickNormal;
      eastl::vector_s005b_2d90<EA::AutoRefCount_s005b_2d90<cSPEditorBlock_s005b_2d90> > pickList;
      pickList.push_back(EA::AutoRefCount_s005b_2d90<cSPEditorBlock_s005b_2d90>(mBlock->mpParent));
      int physicsTriangleIndex;
      bool hitHull;
      int pickLevel = 2;
      EditorUtils::PickBlocks(pickList, origin, dir, physicsPickPoint, physicsPickNormal,
                              &physicsTriangleIndex, hitHull, &pickLevel);

      bool isOnTopOfParent = false;
      if (mBlock->mpParent->mpPhysicsBlock) {
        hkAabb_s005b_2d90 physicsBlockAABB;
        mBlock->mpParent->GetPhysicsAABB(physicsBlockAABB, false);
        if (fabsf(physicsBlockAABB.mMax[1] - physicsPickPoint.z) < 0.5f &&
            pickNormal.x * kEditorUpAxis.x + pickNormal.y * kEditorUpAxis.y +
                    pickNormal.z * kEditorUpAxis.z > 0.99)
          isOnTopOfParent = true;
      }

      cSPMatrix3_s005b_2d90 currentRotation(newRotation);
      bool fiddledWithBlock = false;
      cSPMatrix3_s005b_2d90 topRotation(mBlock->mBaseOrientation);
      bool setOnGround = false;
      cSPVector3_s005b_2d90 positionBeforeAlign = mBlock->mPosition;
      mBlock->SetSnapType(-2);
      bool allowTop = mBlock->mpParent && mBlock->mpParent->GetBooleanAttribute(kAttrAllowTopBehaviors);
      if (isOnTopOfParent && allowTop)
        topRotation = EditorUtils::CalculateTopOrientation(mBlock->mpParent, positionBeforeAlign);

      cSPVector3_s005b_2d90 behaviorPosition = mBlock->mPosition;
      cSPMatrix3_s005b_2d90 behaviorRotation(mBlock->mBaseOrientation);
      EditorUtils::GetRotationAndPositionBasedOnBehavior(mBlock, behaviorPosition, behaviorRotation,
                                                         positionBeforeAlign, false, isOnTopOfParent);
      if (EditorUtils::GetAlignmentPosition(mBlock, mPileList, originalPosition, topRotation, newPosition,
                                            newRotation, setOnGround, isOnTopOfParent,
                                            behaviorRotation) != -1.0f) {
        int triangleIndex = -1;
        bool hitHull2 = false;
        fiddledWithBlock = true;
        shouldSnap = true;
        cSPVector3_s005b_2d90 hitPoint;
        cSPVector3_s005b_2d90 hitNormal;
        cSPEditorBlock_s005b_2d90* pinBlock = EditorUtils::PickBlockForPinning(
            mBlock, mPileList, newPosition - newRotation.yAxis * 10.0f, newRotation.yAxis, hitPoint,
            hitNormal, hitHull2, &triangleIndex);
        cSPVector3_s005b_2d90 alignmentDistance = hitPoint - newPosition;
        if (pinBlock && alignmentDistance.Length() <= 0.2f) {
          newPosition = hitPoint;
          mBlock->SetParentTriangle(triangleIndex, hitHull2);
        }
        if (mBlock->mpParent) {
          mBlock->mIsOnGround = false;
          if (mBlock->mpSymmetricBlock)
            mBlock->mpSymmetricBlock->mIsOnGround = false;
        } else {
          mBlock->SetIsOnGround(setOnGround);
        }
        if (!mAlignFeedbackOn) {
          EditorUtils::PlayFeedback(kPinningAlignOnFeedback);
          mAlignFeedbackOn = true;
        }
      } else if (mAlignFeedbackOn) {
        EditorUtils::PlayFeedback(kPinningAlignOffFeedback);
        mAlignFeedbackOn = false;
      }

      bool moved = EditorUtils::GetRotationAndPositionBasedOnBehavior(
          mBlock, newPosition, newRotation, positionBeforeAlign, false, isOnTopOfParent);
      fiddledWithBlock = fiddledWithBlock || moved;

      cSPMatrix3_s005b_2d90 newUserOrientation(mBlock->mUserOrientation);
      float snapScale = 1.0f;
      if (mBlock->GetBooleanAttribute(kAttrPreferToBeOnPlaneOfSymmetry))
        snapScale = 1.5f;
      bool wasOnSymmetryPlane = mBlock->GetBooleanAttribute(kAttrOnSymmetryPlane);
      bool symmetrySnapped = EditorUtils::CheckAndSnapBlockToPlaneOfSymmetry(
          mBlock, newPosition, newRotation, newUserOrientation, true, snapScale, false, false);
      mBlock->SetUserOrientation(newUserOrientation);
      if (symmetrySnapped) {
        shouldSnap = true;
        fiddledWithBlock = true;
      }

      if (mBlock->mpParent && mBlock->mpParent->GetBooleanAttribute(kAttrHasBallAndSocket) &&
          mBlock->GetSymmetrySign() == 0 && mBlock->mpParent->GetSymmetrySign() != 0 &&
          mBlock->mpParent->mpParent) {
        cSPEditorBlock_s005b_2d90* grandParent = mBlock->mpParent->mpParent;
        mBlock->mpParent->RemoveChild(mBlock);
        grandParent->AddChild(mBlock);
      }

      cSPEditorBlock_s005b_2d90* replaceBlock = EditorUtils::GetSurfaceSnapReplace(mBlock, newPosition);
      if (replaceBlock) {
        if (replaceBlock != mBumpedBlock && mBumpedBlock)
          EditorUtils::UnsnapReplaceBlock(mBumpedBlock);
        EditorUtils::DoSnapReplace(mBlock, replaceBlock, newPosition, newRotation);
        shouldSnap = true;
        mBumpedBlock = replaceBlock;
        fiddledWithBlock = true;
      } else if (mBumpedBlock) {
        EditorUtils::UnsnapReplaceBlock(mBumpedBlock);
        mBumpedBlock.Reset();
      } else {
        EditorUtils::DoPlaneOfSymmetryEffect(mBlock, wasOnSymmetryPlane);
      }

      if (fiddledWithBlock) {
        EditorUtils::MoveBlockAndPile(mBlock, newPosition, newRotation, false);
        needToRePin = true;
      }
    }

    if (!mBlock->mpParent && mBumpedBlock) {
      EditorUtils::UnsnapReplaceBlock(mBumpedBlock);
      mBumpedBlock.Reset();
    }
  }

  bool recordPosition;
  if (mBlock->mpParent) {
    recordPosition = shouldSnap || needToRePin;
    EditorEffects()->SetVisibility(kPinningEffect, false);
    if (mManipulateCursor && (!originalParent || mHaveNotAlreadyPlayedPinningEffect))
      mHaveNotAlreadyPlayedPinningEffect = false;
  } else {
    EditorEffects()->SetVisibility(kPinningEffect, true);
    if (mManipulateCursor && EditorEffects()->Get(kPinningCursorEffect))
      EditorEffects()->Stop(kPinningCursorEffect);
    recordPosition = needToRePin;
  }
  if (recordPosition)
    mBlock->RecordPosition(mBlock->GetParentTriangle(), mBlock->mPosition,
                           mBlock->GetTrianglePickDirection(true), true);

  mBlock->UpdateAfterMove();
  EditorUtils::SetSymmetricBlocksUIState(mBlock, &mPileList, false);
  EditorUtils::MarkInvalidBlocks(mBlock, &mPileList, false, false, false, false, true, true);

  int oldSymmetrySign = mBlock->GetSymmetrySign();
  int symmetrySign = mBlock->CalculateSymmetrySign();
  if ((!mBlock->mpEditorModel || mBlock->mpEditorModel->UsingSymmetry()) && symmetrySign != oldSymmetrySign) {
    mBlock->SetModelBasedOnSymmetrySign(symmetrySign, false, true, false, false);
    EditorUtils::RecordBlockAndPileHistory(mBlock, mPileList);
  } else {
    mBlock->SetSymmetrySign(symmetrySign);
  }

  EditorEffects()->SetTransform(kPinningEffect, mBlock);
  if (EditorEffects()->Get(kPinningCursorEffect)) {
    EA::Swarm::cTransform_s005b_2d90 effectXform;
    effectXform.SetOffset(mBlock->mPosition);
    effectXform.SetRotation(mBlock->mOrientation);
    effectXform.SetScale(mEffectScale);
    EditorEffects()->SetTransform(kPinningCursorEffect, effectXform);
  }

  if (!mChangedObject)
    mChangedObject = true;

  if (originalParent != mBlock->mpParent) {
    if (originalParent)
      originalParent->SetUIState(mParentPreviousState, true, false, true);
    if (mBlock->mpParent) {
      mParentPreviousState = mBlock->mpParent->mUIState;
      mBlock->mpParent->SetUIState(2, true, false, true);
    }
  }

  if (!shouldSnap && !mBlock->mpParent && originalParent) {
    cSPMatrix3_s005b_2d90 badPositionOrientation = mBlock->GetNeutralOrientation(dir);
    mTargetOrientation = normalized(QuaternionFromMatrix3(badPositionOrientation));
  } else {
    mTargetOrientation = rw::math::fpu::QuaternionFromMatrix33(mBlock->mBaseOrientation, 0.0f).Normalized();
  }
  mTargetPosition = mBlock->mPosition;

  if (!mBlock->mpParent)
    mBlock->SetBlockPickDirection(EditorUtils::GetNearestBlockDirection(mBlock));
  else if (mDidNotStack)
    mDidNotStack = false;

  if (!shouldSnap)
    EditorUtils::MoveBlockAndPile(mBlock, trueBlockOriginalPosition, trueBlockOriginalRotation, false);
  return true;
}
}  // namespace SP
