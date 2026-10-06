// slice s005b2d90 — SP::cSPEditorManipulationPinning::DoOnMouseMove (5075 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Local and callee names come from the 2008 dev build (work/devbuild: SporeApp.pdb module
// SPEditorManipulationPinning.obj, function 0x00d66700 and the functions it calls). Retail offsets
// differ from the PDB (cSPEditorBlock grew; the pinning class gained a bool at +0xe8), so every
// member offset below was read from the retail disassembly.
#include <new>
#include <math.h>
#include "types.h"

#define PV(n) virtual void pv##n();

// ---------------------------------------------------------------- math
struct cSPVector3 {
  float x, y, z;
  cSPVector3() {}
  cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
  cSPVector3(const cSPVector3& v) : x(v.x), y(v.y), z(v.z) {}
  float Length() const { return sqrtf(x * x + y * y + z * z); }
};
inline cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b) {
  return cSPVector3(a.x - b.x, a.y - b.y, a.z - b.z);
}
inline cSPVector3 operator*(const cSPVector3& a, float s) {
  return cSPVector3(a.x * s, a.y * s, a.z * s);
}

// rw::math::fpu::Matrix33Template<float,0>; the copy ctor is out of line (0x0041cb40).
struct cSPMatrix3 {
  cSPVector3 xAxis, yAxis, zAxis;
  cSPMatrix3() {}
  cSPMatrix3(const cSPMatrix3& m);  // 0x0041cb40
};

struct cSPQuaternion {
  float x, y, z, w;
  cSPQuaternion() {}
  cSPQuaternion(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
  cSPQuaternion Normalized() const {
    float inv = 1.0f / sqrtf(w * w + z * z + y * y + x * x);
    return cSPQuaternion(x * inv, y * inv, z * inv, w * inv);
  }
};

struct hkAabb {
  float mMin[4];
  float mMax[4];
};

namespace rw { namespace math { namespace fpu {
cSPQuaternion QuaternionFromMatrix33(const cSPMatrix3& m, float tolerance);  // 0x00472b80
}}}

extern const cSPVector3 kEditorUpAxis;       // 0x015e9a70
extern const cSPVector3 kZeroVector;         // 0x015e9a24
extern const cSPMatrix3 kIdentityMatrix3;    // 0x015e9ba0
extern uint32_t kPinningAlignOnFeedback;     // 0x015e9a0c
extern uint32_t kPinningAlignOffFeedback;    // 0x015e99a4

// ---------------------------------------------------------------- EA
namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) {
    if (mpObject)
      mpObject->AddRef();
  }
  AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) {
    if (mpObject)
      mpObject->AddRef();
  }
  ~AutoRefCount() {
    if (mpObject)
      mpObject->Release();
  }
  AutoRefCount& operator=(T* p);  // 0x004b09b0 (cSPEditorBlock instance)
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

namespace Swarm {
// EA::Swarm::cTransform (0x38 bytes)
struct cTransform {
  uint16_t mFlags;        // +0x00
  uint16_t mChangeCount;  // +0x02
  cSPVector3 mOffset;     // +0x04
  float mScale;           // +0x10
  cSPMatrix3 mRotation;   // +0x14
  cTransform()
      : mFlags(0), mChangeCount(0), mOffset(kZeroVector), mScale(1.0f), mRotation(kIdentityMatrix3) {}
  void SetOffset(const cSPVector3& v) {
    mOffset = v;
    mChangeCount++;
    mFlags |= 4;
  }
  void SetRotation(const cSPMatrix3& m) {
    mRotation = m;
    mFlags |= 2;
    mChangeCount++;
  }
  void SetScale(float s) {
    mScale = s;
    mChangeCount++;
  }
};
}  // namespace Swarm
}  // namespace EA

namespace eastl {
struct sp_vector_allocator {  // retail: 8 bytes, so a vector is 0x14 bytes
  uint32_t mName[2];
  sp_vector_allocator() {}
};
template <typename T>
class vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator mAllocator;
  vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~vector();                                       // 0x00453eb0
  void DoInsertValue(T* position, const T& value);  // 0x00454ee0
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};
}  // namespace eastl

// ---------------------------------------------------------------- SP
namespace SP {

class cSPEditorBlock;
typedef eastl::vector<EA::AutoRefCount<cSPEditorBlock> > PileList;

class cSPEditorModel {
 public:
  bool UsingSymmetry();  // 0x004adc40
};

class cSPEditorSkinManager {
 public:
  virtual int AddRef();
  virtual int Release();
};

// Boolean attribute indices of the bitset at +0xdc8.
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

class cSPEditorBlock {
 public:
  virtual ~cSPEditorBlock();
  virtual int AddRef();
  virtual int Release();
  uint32_t pad04[(0x28 - 0x04) / 4];
  cSPEditorModel* mpEditorModel;         // +0x28
  uint32_t pad2c[(0x3c - 0x2c) / 4];
  int mUIState;                          // +0x3c
  uint32_t pad40[(0x48 - 0x40) / 4];
  cSPVector3 mPosition;                  // +0x48
  cSPVector3 mHistoryPosition;           // +0x54
  cSPMatrix3 mOrientation;               // +0x60
  cSPMatrix3 mHistoryOrientation;        // +0x84
  cSPMatrix3 mBaseOrientation;           // +0xa8
  cSPMatrix3 mHistoryBaseOrientation;    // +0xcc
  cSPMatrix3 mUserOrientation;           // +0xf0
  uint32_t pad114[(0x18c - 0x114) / 4];
  void* mpPhysicsBlock;                  // +0x18c
  uint32_t pad190[(0x33c - 0x190) / 4];
  cSPEditorBlock* mpParent;              // +0x33c (AutoRefCount)
  uint32_t pad340[(0x3c8 - 0x340) / 4];
  bool pad3c8;
  bool mIsOnGround;                      // +0x3c9
  uint8_t pad3ca[2];
  uint32_t pad3cc[(0x3e0 - 0x3cc) / 4];
  cSPEditorBlock* mpSymmetricBlock;      // +0x3e0 (AutoRefCount)
  uint32_t pad3e4[(0xdc8 - 0x3e4) / 4];
  uint32_t mBooleanAttributes[2];        // +0xdc8 (bitset)

  bool GetBooleanAttribute(int index) const {
    return (mBooleanAttributes[index >> 5] >> (index & 31)) & 1;
  }
  void SetBooleanAttribute(int index, bool value);                 // 0x00435a10
  void SetSnapType(int type);                                      // 0x0044e7c0
  void GetPhysicsAABB(hkAabb& box, bool b);                        // 0x0044aaa0
  void SetParentTriangle(int triangleIndex, bool hitHull);         // 0x00451240
  void SetIsOnGround(bool onGround);                               // 0x0049c0f0
  void SetUserOrientation(cSPMatrix3 orientation);                 // 0x0043ffa0
  int GetSymmetrySign();                                           // 0x0044f220
  int CalculateSymmetrySign();                                     // 0x0044f240
  void RemoveChild(cSPEditorBlock* child);                         // 0x00438a40
  void AddChild(cSPEditorBlock* child);                            // 0x00438700
  cSPVector3 GetTrianglePickDirection(bool b);                     // 0x00438120
  int GetParentTriangle();                                         // 0x004511f0
  void RecordPosition(int triangle, cSPVector3 position, cSPVector3 direction, bool b);  // 0x004370a0
  void UpdateAfterMove();                                          // 0x0044ede0 (name guessed)
  void SetModelBasedOnSymmetrySign(int sign, bool a, bool b, bool c, bool d);  // 0x00439110
  void SetSymmetrySign(int sign);                                  // 0x0044e980 (name guessed)
  void SetUIState(int state, bool a, bool b, bool c);              // 0x0043a5e0
  cSPMatrix3 GetNeutralOrientation(cSPVector3 direction);          // 0x004494b0
  void SetBlockPickDirection(cSPVector3 direction);                // 0x00438270
};

cSPMatrix3 Matrix3FromQuaternion(const cSPQuaternion& q);          // 0x0059c190
cSPQuaternion QuaternionFromMatrix3(const cSPMatrix3& m);          // 0x0046d660
cSPQuaternion normalized(const cSPQuaternion& q);                  // 0x00799320

class cSPEditorEffects {
 public:
  void SetVisibility(uint32_t id, bool visible);                   // 0x0045b110
  int Get(uint32_t id);                                            // 0x0045b210
  void Stop(uint32_t id);                                          // 0x0045b000
  void SetTransform(uint32_t id, cSPEditorBlock* block);           // 0x0045b080
  void SetTransform(uint32_t id, const EA::Swarm::cTransform& t);  // 0x0045b040
};
cSPEditorEffects* EditorEffects();                                 // 0x00401050

class ICursorMover {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual void SetCursorPosition(int x, int y);                    // +0x10
};
class cCursorManagerBase {
 public:
  virtual void pv0();
  uint32_t mField4;
};
class cCursorManager : public cCursorManagerBase, public ICursorMover {};
cCursorManager* CursorManager();                                   // 0x0067cab0

class cViewer {
 public:
  void GetWorldRayFromScreenCoords(float x, float y, cSPVector3& origin, cSPVector3& direction);  // 0x007c4730
};
class cApp {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual cViewer* GetViewer();                                    // +0x58
};
cApp* App();                                                       // 0x0067dd10

namespace EditorUtils {
bool MoveBlockAndPile(cSPEditorBlock* block, cSPVector3 position, cSPMatrix3 orientation, bool b);  // 0x0049fbd0
int GetOrientToSurfaces(cSPEditorBlock* block, cSPVector3 origin, cSPVector3 direction,
                        EA::AutoRefCount<cSPEditorSkinManager> skin, cSPVector3& hitPoint,
                        cSPVector3& hitNormal, PileList& pileList);                                 // 0x00499410
cSPEditorBlock* GetSnapPoint(cSPEditorBlock* block, PileList& pileList, cSPVector3 origin,
                             cSPVector3 direction, cSPVector3& snapPoint);                         // 0x004a3dc0
void UnsnapBlock(cSPEditorBlock* block);                                                           // 0x004a1070
void RecordBlockAndPileHistory(cSPEditorBlock* block, PileList& pileList);                         // 0x004961d0
bool MoveBlockOrientToSurfaces(cSPEditorBlock* block, PileList& pileList, cSPVector3 origin,
                               cSPVector3 direction, EA::AutoRefCount<cSPEditorSkinManager> skin,
                               cSPVector3& stackingPosition, cSPVector3* pickNormal, bool animate,
                               bool b);                                                            // 0x0049a2a0
void CalculateMissPlane(cSPEditorBlock* block, cSPVector3 direction, cSPVector3* planePosition,
                        cSPVector3* planeNormal);                                                  // 0x0049b8b0
void PlaceBlockInScene(cSPEditorBlock* block, cSPVector3 origin, cSPVector3 direction,
                       cSPVector3 planePosition, cSPVector3 planeNormal, bool b);                 // 0x0049bcc0
void SnapBlockToSocket(cSPEditorBlock* block, PileList& pileList, cSPEditorBlock* parent);         // 0x004a29a0
void CheckAndSnapBlockToPlaneOfSymmetry(cSPEditorBlock* block, bool b, float scale, bool c);       // 0x004982b0
bool CheckAndSnapBlockToPlaneOfSymmetry(cSPEditorBlock* block, cSPVector3& position,
                                        cSPMatrix3& orientation, cSPMatrix3& userOrientation,
                                        bool a, float scale, bool b, bool c);                     // 0x00498470
cSPEditorBlock* PickBlocks(PileList& pickList, cSPVector3 origin, cSPVector3 direction,
                           cSPVector3& pickPoint, cSPVector3& pickNormal, int* triangleIndex,
                           bool& hitHull, int* pickLevel);                                         // 0x004a4840
cSPMatrix3 CalculateTopOrientation(cSPEditorBlock* parent, cSPVector3 position);                   // 0x0049b460
bool GetRotationAndPositionBasedOnBehavior(cSPEditorBlock* block, cSPVector3& position,
                                           cSPMatrix3& orientation, cSPVector3 oldPosition,
                                           bool a, bool isOnTopOfParent);                         // 0x004942b0
float GetAlignmentPosition(cSPEditorBlock* block, PileList& pileList, cSPVector3 position,
                           cSPMatrix3 orientation, cSPVector3& newPosition, cSPMatrix3& newOrientation,
                           bool& setOnGround, bool isOnTopOfParent, cSPMatrix3 oldOrientation);   // 0x00490a70
cSPEditorBlock* PickBlockForPinning(cSPEditorBlock* block, PileList& pileList, cSPVector3 origin,
                                    cSPVector3 direction, cSPVector3& hitPoint, cSPVector3& hitNormal,
                                    bool& hitHull, int* triangleIndex);                           // 0x004a4d60
void PlayFeedback(uint32_t id);                                                                    // 0x004a88d0 (name guessed)
cSPEditorBlock* GetSurfaceSnapReplace(cSPEditorBlock* block, cSPVector3 position);                // 0x004a3c70
bool UnsnapReplaceBlock(cSPEditorBlock* block);                                                    // 0x004a1e10
bool DoSnapReplace(cSPEditorBlock* block, cSPEditorBlock* replace, cSPVector3& position,
                   cSPMatrix3& orientation);                                                       // 0x004a2350
void DoPlaneOfSymmetryEffect(cSPEditorBlock* block, bool wasOnPlane);                              // 0x004983d0
void SetSymmetricBlocksUIState(cSPEditorBlock* block, PileList* pileList, bool b);                 // 0x004a7f30
void MarkInvalidBlocks(cSPEditorBlock* block, PileList* pileList, bool a, bool b, bool c, bool d,
                       bool e, bool f);                                                            // 0x004a6d20
cSPVector3 GetNearestBlockDirection(cSPEditorBlock* block);                                        // 0x0049a0c0
}  // namespace EditorUtils

const uint32_t kPinningEffect = 0x3f1bf5d;
const uint32_t kPinningCursorEffect = 0x3f1bf5e;

class cSPEditorManipulationPinning {
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
  cSPEditorBlock* mBlock;                             // +0x1c (AutoRefCount)
  EA::AutoRefCount<cSPEditorBlock> mBumpedBlock;      // +0x20
  cSPEditorBlock* mOriginalParent;                    // +0x24
  PileList mPileList;                                 // +0x28
  cSPVector3 mMouseOffset;                            // +0x3c
  EA::AutoRefCount<cSPEditorSkinManager> mSkin;       // +0x48
  bool mUseOffset;                                    // +0x4c
  cSPVector3 mMouseOffset2D;                          // +0x50
  cSPVector3 mMouseOffset3D;                          // +0x5c
  float mDistanceAlongOffset;                         // +0x68
  float mTotalElapsedTime;                            // +0x6c
  int mX;                                             // +0x70
  int mY;                                             // +0x74
  bool mListenToMouseChange;                          // +0x78
  float mEffectScale;                                 // +0x7c
  bool mMoveCursor;                                   // +0x80
  bool mHaveNotAlreadyPlayedPinningEffect;            // +0x81
  int mParentPreviousState;                           // +0x84
  cSPQuaternion mStartOrientation;                    // +0x88
  cSPQuaternion mGoalOrientation;                     // +0x98
  cSPQuaternion mTargetOrientation;                   // +0xa8
  cSPVector3 mTargetPosition;                         // +0xb8
  float mTotalOrientationTime;                        // +0xc4
  float mElapsedOrientationTime;                      // +0xc8
  cSPVector3 mMissPlanePosition;                      // +0xcc
  cSPVector3 mMissPlaneNormal;                        // +0xd8
  bool mIsAnimatingOrientation;                       // +0xe4
  bool mDidNotStack;                                  // +0xe5
  bool mManipulateCursor;                             // +0xe6
  bool mDidMoveCursor;                                // +0xe7
  bool mAlignFeedbackOn;                              // +0xe8 (retail only)

  bool DoOnMouseMove(float x, float y, uint32_t modifiers);
};

// @ 0x005b2d90
bool cSPEditorManipulationPinning::DoOnMouseMove(float x, float y, uint32_t modifiers)
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

  cSPVector3 trueBlockOriginalPosition = mBlock->mPosition;
  cSPMatrix3 trueBlockOriginalRotation(mBlock->mBaseOrientation);
  EditorUtils::MoveBlockAndPile(mBlock, mTargetPosition, Matrix3FromQuaternion(mTargetOrientation), false);
  cSPMatrix3 blockOriginalRotation(mBlock->mBaseOrientation);

  if (mUseOffset) {
    x += mMouseOffset2D.x;
    y += mMouseOffset2D.y;
  }

  cSPVector3 origin;
  cSPVector3 dir;
  App()->GetViewer()->GetWorldRayFromScreenCoords(x, y, origin, dir);

  cSPVector3 originalPosition = mBlock->mPosition;
  cSPEditorBlock* originalParent = mBlock->mpParent;

  cSPVector3 skinHitPoint;
  cSPVector3 skinHitNormal;
  int orientResult = EditorUtils::GetOrientToSurfaces(mBlock, origin, dir, mSkin, skinHitPoint,
                                                      skinHitNormal, mPileList);
  cSPVector3 snapHitPoint;
  cSPEditorBlock* snapParent = EditorUtils::GetSnapPoint(mBlock, mPileList, origin, dir, snapHitPoint);

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

    cSPVector3 stackingPosition;
    cSPVector3 pickNormal;
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

    cSPVector3 newPosition = mBlock->mPosition;
    cSPMatrix3 newRotation(mBlock->mBaseOrientation);

    if (mBlock->mpParent) {
      cSPVector3 physicsPickPoint = mBlock->mPosition;
      cSPVector3 physicsPickNormal = pickNormal;
      eastl::vector<EA::AutoRefCount<cSPEditorBlock> > pickList;
      pickList.push_back(EA::AutoRefCount<cSPEditorBlock>(mBlock->mpParent));
      int physicsTriangleIndex;
      bool hitHull;
      int pickLevel = 2;
      EditorUtils::PickBlocks(pickList, origin, dir, physicsPickPoint, physicsPickNormal,
                              &physicsTriangleIndex, hitHull, &pickLevel);

      bool isOnTopOfParent = false;
      if (mBlock->mpParent->mpPhysicsBlock) {
        hkAabb physicsBlockAABB;
        mBlock->mpParent->GetPhysicsAABB(physicsBlockAABB, false);
        if (fabsf(physicsBlockAABB.mMax[1] - physicsPickPoint.z) < 0.5f &&
            pickNormal.x * kEditorUpAxis.x + pickNormal.y * kEditorUpAxis.y +
                    pickNormal.z * kEditorUpAxis.z > 0.99)
          isOnTopOfParent = true;
      }

      cSPMatrix3 currentRotation(newRotation);
      bool fiddledWithBlock = false;
      cSPMatrix3 topRotation(mBlock->mBaseOrientation);
      bool setOnGround = false;
      cSPVector3 positionBeforeAlign = mBlock->mPosition;
      mBlock->SetSnapType(-2);
      bool allowTop = mBlock->mpParent && mBlock->mpParent->GetBooleanAttribute(kAttrAllowTopBehaviors);
      if (isOnTopOfParent && allowTop)
        topRotation = EditorUtils::CalculateTopOrientation(mBlock->mpParent, positionBeforeAlign);

      cSPVector3 behaviorPosition = mBlock->mPosition;
      cSPMatrix3 behaviorRotation(mBlock->mBaseOrientation);
      EditorUtils::GetRotationAndPositionBasedOnBehavior(mBlock, behaviorPosition, behaviorRotation,
                                                         positionBeforeAlign, false, isOnTopOfParent);
      if (EditorUtils::GetAlignmentPosition(mBlock, mPileList, originalPosition, topRotation, newPosition,
                                            newRotation, setOnGround, isOnTopOfParent,
                                            behaviorRotation) != -1.0f) {
        int triangleIndex = -1;
        bool hitHull2 = false;
        fiddledWithBlock = true;
        shouldSnap = true;
        cSPVector3 hitPoint;
        cSPVector3 hitNormal;
        cSPEditorBlock* pinBlock = EditorUtils::PickBlockForPinning(
            mBlock, mPileList, newPosition - newRotation.yAxis * 10.0f, newRotation.yAxis, hitPoint,
            hitNormal, hitHull2, &triangleIndex);
        cSPVector3 alignmentDistance = hitPoint - newPosition;
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

      cSPMatrix3 newUserOrientation(mBlock->mUserOrientation);
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
        cSPEditorBlock* grandParent = mBlock->mpParent->mpParent;
        mBlock->mpParent->RemoveChild(mBlock);
        grandParent->AddChild(mBlock);
      }

      cSPEditorBlock* replaceBlock = EditorUtils::GetSurfaceSnapReplace(mBlock, newPosition);
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
    EA::Swarm::cTransform effectXform;
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
    cSPMatrix3 badPositionOrientation = mBlock->GetNeutralOrientation(dir);
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
