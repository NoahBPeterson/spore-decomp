// slice s005b1e30 -- SP::cSPEditorManipulationPinning (creature editor "pin a block to the body"
// manipulator): OnMouseUp, Init, DoOnMouseDown, Update, ctor/dtor, plus the quaternion
// Lerp/Nlerp/Slerp helpers the Update step uses.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <math.h>
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);

namespace rw { namespace math { namespace fpu {
template <typename T, int N>
class Vector3Template {
 public:
  T x, y, z;
  Vector3Template() {}
  Vector3Template(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
}}}  // namespace rw::math::fpu

struct cSPVector3 : public rw::math::fpu::Vector3Template<float, 0> {
  typedef rw::math::fpu::Vector3Template<float, 0> base;
  cSPVector3() {}
  cSPVector3(float ax, float ay, float az) : base(ax, ay, az) {}
  cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
};
inline cSPVector3 operator+(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x + b.x, a.y + b.y, a.z + b.z); }

struct QuaternionBase {
  float x, y, z, w;
};

struct cSPQuaternion {
  float x, y, z, w;
  cSPQuaternion() {}
  cSPQuaternion(const QuaternionBase& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
  cSPQuaternion(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
  cSPQuaternion(const cSPQuaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
  cSPQuaternion operator-() const { return cSPQuaternion(-x, -y, -z, -w); }
  static float Dot(const cSPQuaternion& a, const cSPQuaternion& b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
  float Length() const { return sqrtf(Dot(*this, *this)); }
  cSPQuaternion Normalized() const {
    float s = 1.0f / Length();
    return cSPQuaternion(x * s, y * s, z * s, w * s);
  }
};

struct cSPMatrix3 {
  float m[9];
  cSPMatrix3() {}
  cSPMatrix3(const cSPMatrix3& src);   // 0x0041cb40 (Matrix3::Assign)
};

#define PV(n) virtual void pv##n();

namespace SP {

class cViewer {
 public:
  bool GetWorldRayFromScreenCoords(float x, float y, cSPVector3& origin, cSPVector3& direction);  // 0x007c4730
};

class cSPApp {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual cViewer* GetViewer();
};
cSPApp* App();   // 0x0067dd10

class cSPEditorModel {
 public:
  float GetScale();            // FUN_004adaa0
  bool IsUsingSymmetry();      // FUN_004adc40
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
  char pad54[0x60 - 0x54];
  float mRot[9];                  // +0x60 (3x3, row-major)
  char pad84[0xa8 - 0x84];
  cSPMatrix3 mTransform;          // +0xa8
  char padCC[0x33c - 0xcc];
  cSPEditorBlock* mParent;        // +0x33c
  void SetHighlight(int color, int a, int b, int c);   // FUN_0043a5e0
  void SetVecC(cSPVector3 v);                           // Tracker::SetVecC 0x00438270
};

class cSPEditorSkinManager {
 public:
  virtual void AddRef();
  virtual void Release();
};

class cSPEditorAnimatedEventInfo {
 public:
  cSPEditorAnimatedEventInfo();   // 0x0059d960
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  void MessageSend(uint32_t id, cSPEditorBlock* block, cSPEditorModel* model, int a, int b, float c, int d, int e, float f);   // 0x0059d8b0
  char pad[0x30 - 4];
};

// Singleton-ish message sinks looked up by id (FUN_00401050 is __stdcall).
class cEditorMsgSink {
 public:
  void Fire();                                                  // FUN_0045b150
  void FireBlock(bool a, cSPEditorBlock* block, int b);         // FUN_0045ae40
};
cEditorMsgSink* __stdcall GetMsgSink(unsigned int id);          // FUN_00401050

// Cursor warp interface (sub-object at +8 of what FUN_0067cab0 returns).
class ICursor {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual void SetCursorPos(int x, int y);   // slot 4
};
class cInputObj {
 public:
  virtual void v0();
  char pad[4];
  ICursor mCursor;
};
cInputObj* GetInputObj();   // FUN_0067cab0

namespace EditorUtils {
void RepinBlockToTorso(cSPEditorBlock* block, cSPVector3 pos, cSPMatrix3 orient, int flag);   // 0x0049fbd0
void DeleteInvalidBlocks(cSPEditorBlock* block, void* pileList);                              // 0x004a6f10
void SetSymmetricBlocksUIState(cSPEditorBlock* block, void* pileList, int state);             // 0x004a7f30
}
void BuildPileList(cSPEditorBlock* block, void* pileList, int flag);                          // 0x0048c790
cSPMatrix3* Matrix3FromQuaternion(cSPMatrix3* out, const cSPQuaternion* q);                   // 0x0059c190

}  // namespace SP

namespace rw { namespace math { namespace fpu {
cSPQuaternion QuaternionFromMatrix33(const cSPMatrix3& m, float tol);                          // 0x00472b80
}}}

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  AutoRefCount& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  AutoRefCount& operator=(const AutoRefCount& x) { return operator=(x.mpObject); }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};

template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}  // namespace EA

namespace eastl {
// vector<AutoRefCount<cSPEditorBlock>, sp_vector_allocator>: dtor/erase are out-of-line instances.
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
// 0x005aa740: remove_copy(first, last, result, value)
template <typename T>
T* remove_copy(T* first, T* last, T* result, const T& value);
// eastl::remove: find then remove_copy
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
}  // namespace eastl

// Globals living in .data/.bss.
extern cSPVector3 gPinMouseOffset2D;   // 0x015e9974 (runtime-initialised)
void WorldToScreen(const cSPVector3* world, float* outX, float* outY);                      // FUN_004a3760
cSPMatrix3* InvertRot(cSPMatrix3* out, const float* rot);                                   // FUN_0041ded0
cSPVector3 GetBlockVecC(SP::cSPEditorBlock* block);                                         // FUN_0049a0c0
void RemoveSymmetricPartners(SP::cSPEditorBlock* block, void* pileList);                    // FUN_004961d0
void ClearSymmetry(SP::cSPEditorBlock* block, void* pileList);                              // FUN_004a8860
void GetMissPlane(SP::cSPEditorBlock* block, cSPVector3 dir, cSPVector3* outPos, cSPVector3* outNormal);   // FUN_0049b8b0
float GetAlignmentPosition(SP::cSPEditorBlock* block, void* pileList, cSPVector3 pos, cSPMatrix3 m2,
                           float* a, float* b, bool* c, int d, cSPMatrix3 m1);               // SP::EditorUtils::GetAlignmentPosition 0x00490a70
cSPQuaternion Lerp(const cSPQuaternion& a, const cSPQuaternion& b, float t);               // FUN_005b1cd0

namespace SP {

class cSPEditorManipulationObject {
 public:
  cSPEditorManipulationObject();   // FUN_005b0f80
  virtual ~cSPEditorManipulationObject() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};

class cSPEditorManipulationPinning : public cSPEditorManipulationObject, public EA::RefCountVTemplate<int> {
 public:
  EA::AutoRefCount<cSPEditorBlock> mBlock;                  // +0x1c
  EA::AutoRefCount<cSPEditorBlock> mBumpedBlock;            // +0x20
  cSPEditorBlock* mOriginalParent;                          // +0x24
  eastl::sp_vector<EA::AutoRefCount<cSPEditorBlock> > mPileList;   // +0x28
  cSPVector3 mMouseOffset;                                  // +0x3c
  EA::AutoRefCount<cSPEditorSkinManager> mSkin;             // +0x48
  bool mUseOffset;                                          // +0x4c
  cSPVector3 mMouseOffset2D;                                // +0x50
  cSPVector3 mMouseOffset3D;                                // +0x5c
  float mDistanceAlongOffset;                               // +0x68
  float mTotalElapsedTime;                                  // +0x6c
  int mX;                                                   // +0x70
  int mY;                                                   // +0x74
  bool mListenToMouseChange;                                // +0x78
  float mEffectScale;                                       // +0x7c
  bool mMoveCursor;                                         // +0x80
  bool mHaveNotAlreadyPlayedPinningEffect;                  // +0x81
  int mParentPreviousState;                                 // +0x84
  cSPQuaternion mStartOrientation;                          // +0x88
  cSPQuaternion mGoalOrientation;                           // +0x98
  cSPQuaternion mTargetOrientation;                         // +0xa8
  cSPVector3 mTargetPosition;                               // +0xb8
  float mTotalOrientationTime;                              // +0xc4
  float mElapsedOrientationTime;                            // +0xc8
  cSPVector3 mMissPlanePosition;                            // +0xcc
  cSPVector3 mMissPlaneNormal;                              // +0xd8
  bool mIsAnimatingOrientation;                             // +0xe4
  bool mDidNotStack;                                        // +0xe5
  bool mManipulateCursor;                                   // +0xe6
  bool mDidMoveCursor;                                      // +0xe7
  bool mFlagE8;                                             // +0xe8

  cSPEditorManipulationPinning();
  ~cSPEditorManipulationPinning();
  bool OnMouseUp(int button, float x, float y, int modifiers);
  void Init(const EA::AutoRefCount<cSPEditorBlock>& block, cSPVector3 mouseOffset,
            EA::AutoRefCount<cSPEditorSkinManager> skin, bool manipulateCursor);
  bool DoOnMouseDown(int button, float x, float y, int modifiers);
  void Update(float dt);
};

// @ 0x005b1e30  SP::cSPEditorManipulationPinning::OnMouseUp
bool cSPEditorManipulationPinning::OnMouseUp(int button, float x, float y, int modifiers) {
  if (mManipulateCursor && mBlock.mpObject) {
    cSPVector3 world(
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

  cSPMatrix3 rot;
  Matrix3FromQuaternion(&rot, &mTargetOrientation);
  EditorUtils::RepinBlockToTorso(mBlock.mpObject, mTargetPosition, rot, 0);
  GetMsgSink(0x03f1bf5d)->Fire();
  GetMsgSink(0x03f1bf5e)->Fire();

  if (mChangedObject) {
    if (mOriginalParent) {
      if (mBlock.mpObject->mParent) {
        EA::AutoRefCount<cSPEditorAnimatedEventInfo> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo());
        info->MessageSend(0xda95baa5, mBlock.mpObject, mBlock.mpObject == 0 ? 0 : mBlock.mpObject->mEditorModel, 0, 0,
                          0.0f, 0, -1, 1.0f);
      } else {
        EA::AutoRefCount<cSPEditorAnimatedEventInfo> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo());
        info->MessageSend(0x0428e920, mBlock.mpObject, mBlock.mpObject == 0 ? 0 : mBlock.mpObject->mEditorModel, 0, 0,
                          0.0f, 0, -1, 1.0f);
      }
    } else if (mBlock.mpObject->mParent) {
      EA::AutoRefCount<cSPEditorAnimatedEventInfo> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo());
      info->MessageSend(0x8e04ce1a, mBlock.mpObject, mBlock.mpObject == 0 ? 0 : mBlock.mpObject->mEditorModel, 0, 0,
                        0.0f, 0, -1, 1.0f);
    }
  }

  if (mBlock.mpObject->mParent) {
    cSPEditorBlock* parent = mBlock.mpObject->mParent;
    parent->SetHighlight(mParentPreviousState, 1, 0, 1);
    cSPEditorBlock* b = mBlock.mpObject;
    b->SetVecC(*(cSPVector3*)&b->mRot[3]);
  }
  EditorUtils::DeleteInvalidBlocks(mBlock.mpObject, &mPileList);
  return true;
}

// @ 0x005b2180  SP::cSPEditorManipulationPinning::Init
void cSPEditorManipulationPinning::Init(const EA::AutoRefCount<cSPEditorBlock>& block, cSPVector3 mouseOffset,
                                        EA::AutoRefCount<cSPEditorSkinManager> skin, bool manipulateCursor) {
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
    cSPMatrix3 invTmp;
    cSPMatrix3* inv = InvertRot(&invTmp, block->mRot);
    const float* m = inv->m;
    mMouseOffset3D.x = (m[6] * nz + m[3] * ny) + m[0] * nx;
    mMouseOffset3D.y = (m[7] * nz + m[4] * ny) + m[1] * nx;
    mMouseOffset3D.z = (m[8] * nz + m[5] * ny) + m[2] * nx;
    cSPEditorBlock* b = mBlock.mpObject;
    if (b->mParent == 0)
      b->SetVecC(GetBlockVecC(b));
  }
  mUseOffset = true;
  mDidNotStack = true;
}

// @ 0x005b23d0  SP::cSPEditorManipulationPinning::cSPEditorManipulationPinning
cSPEditorManipulationPinning::cSPEditorManipulationPinning()
    : mBlock(), mBumpedBlock(), mPileList(), mMouseOffset(0.0f, 0.0f, 0.0f), mSkin(), mUseOffset(true),
      mMouseOffset2D(gPinMouseOffset2D), mListenToMouseChange(true), mEffectScale(1.0f), mMoveCursor(false),
      mHaveNotAlreadyPlayedPinningEffect(true), mIsAnimatingOrientation(false), mDidNotStack(false),
      mDidMoveCursor(false), mFlagE8(false) {
  mChangedObject = false;
}

// @ 0x005b24a0  SP::cSPEditorManipulationPinning::~cSPEditorManipulationPinning
cSPEditorManipulationPinning::~cSPEditorManipulationPinning() {}

}  // namespace SP

// @ 0x005b2350  SP::cQuaternion Nlerp(a, b, t)
cSPQuaternion Nlerp(const cSPQuaternion& a, const cSPQuaternion& b, float t) {
  return Lerp(a, b, t).Normalized();
}

extern float gSlerpEpsilonAngle;   // 0x01512690 (about 5 degrees in radians)

// @ 0x005b2500  quaternion slerp (falls back to nlerp for nearly parallel inputs)
cSPQuaternion Slerp(const cSPQuaternion& a, const cSPQuaternion& b, float t) {
  cSPQuaternion q0(a);
  cSPQuaternion q1(b);
  float dot = cSPQuaternion::Dot(q0, q1);
  if (dot < 0.0f) {
    q0 = -q0;
    dot = -dot;
  }
  if (dot > cos(gSlerpEpsilonAngle))
    return Nlerp(q0, q1, t);
  float omega = acos(dot);
  float inv = 1.0f / sin(omega);
  float s0 = sin((1.0f - t) * omega) * inv;
  float s1 = sin(t * omega) * inv;
  return cSPQuaternion(q1.x * s1 + q0.x * s0, q1.y * s1 + q0.y * s0, q1.z * s1 + q0.z * s0, q1.w * s1 + q0.w * s0);
}

// Result type of the slerp wrapper: element-wise user assignment from the helper's result.
struct cSPQuaternionW {
  float x, y, z, w;
  cSPQuaternionW() {}
  cSPQuaternionW& operator=(const cSPQuaternion& q) { x = q.x; y = q.y; z = q.z; w = q.w; return *this; }
};

// @ 0x005b26f0  slerp wrapper (returns the Slerp result by value)
cSPQuaternionW SlerpWrap(const cSPQuaternion& a, const cSPQuaternion& b, float t) {
  cSPQuaternionW r;
  r = Slerp(a, b, t);
  return r;
}

namespace SP {

// @ 0x005b2750  SP::cSPEditorManipulationPinning::Update
void cSPEditorManipulationPinning::Update(float dt) {
  cSPVector3 origin, dir;
  App()->GetViewer()->GetWorldRayFromScreenCoords((float)mX + mMouseOffset2D.x, (float)mY + mMouseOffset2D.y, origin, dir);

  cSPEditorBlock* b = mBlock.mpObject;
  cSPVector3 pos(b->mPosition.x, b->mPosition.y, b->mPosition.z);
  cSPVector3 newPos(b->mPosition.x, b->mPosition.y, b->mPosition.z);
  cSPMatrix3 m(b->mTransform);
  cSPQuaternion q = rw::math::fpu::QuaternionFromMatrix33(m, 0.0f);
  float dts = dt * 0.001f;
  if (dts > 0.05f)
    dts = 0.05f;

  if (pos.x != mTargetPosition.x || pos.y != mTargetPosition.y || pos.z != mTargetPosition.z) {
    float dx = ((mTargetPosition.x - pos.x) * dts) * 12.0f;
    float dy = ((mTargetPosition.y - pos.y) * dts) * 12.0f;
    float dz = ((mTargetPosition.z - pos.z) * dts) * 12.0f;
    newPos = cSPVector3(pos.x + dx, pos.y + dy, pos.z + dz);
  }
  if (q.x != mTargetOrientation.x || q.y != mTargetOrientation.y || q.z != mTargetOrientation.z ||
      q.w != mTargetOrientation.w) {
    q = Slerp(q, mTargetOrientation, dts * 12.0f);
  }

  cSPMatrix3 rot;
  Matrix3FromQuaternion(&rot, &q);
  EditorUtils::RepinBlockToTorso(mBlock.mpObject, newPos, rot, 0);
  EditorUtils::SetSymmetricBlocksUIState(mBlock.mpObject, &mPileList, 0);

  if (mTotalElapsedTime < 1.0f) {
    mTotalElapsedTime += dts;
    if (mTotalElapsedTime >= 1.0f)
      mMoveCursor = false;
  }
}

// @ 0x005b2a50  SP::cSPEditorManipulationPinning::DoOnMouseDown
bool cSPEditorManipulationPinning::DoOnMouseDown(int button, float x, float y, int modifiers) {
  cSPEditorModel* model = mBlock.mpObject->mEditorModel;
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
  EA::AutoRefCount<cSPEditorBlock>* end = mPileList.mpEnd;
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

  cSPVector3 origin, dir;
  App()->GetViewer()->GetWorldRayFromScreenCoords((float)mX, (float)mY, origin, dir);
  GetMissPlane(mBlock.mpObject, dir, &mMissPlanePosition, &mMissPlaneNormal);
  mTargetPosition = mBlock->mPosition;
  mTargetOrientation = rw::math::fpu::QuaternionFromMatrix33(mBlock->mTransform, 0.0f);
  mBumpedBlock = 0;

  cSPVector3 pos(mBlock->mPosition);
  cSPMatrix3 orientCopy(mBlock->mTransform);
  bool flag = false;
  float a, b;
  float r = GetAlignmentPosition(mBlock.mpObject, &mPileList, mBlock->mPosition, mBlock.mpObject->mTransform, &a, &b, &flag, 0,
                                 mBlock.mpObject->mTransform);
  if (r != -1.0f)
    mFlagE8 = true;
  return true;
}

}  // namespace SP
