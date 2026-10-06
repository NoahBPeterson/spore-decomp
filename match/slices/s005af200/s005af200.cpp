// slice s005af200 — SP::cSPEditorManipulationLimb::Update (7552 bytes): per-frame limb drag in the
// creature editor. Raycasts the mouse into the scene, moves the manipulated joints/blocks
// according to mManipType (0 = limb root on body, 1-3 = joint/foot on a line or plane,
// 4-5 = limb end attaching to a block or the miss plane, 6/7 = whole limb on the body /
// miss plane), then rebuilds lengths, symmetric copies, highlights and the skin.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same as the neighbouring
// cSPEditorManipulationLimb slice s005ad9a0. Retail offsets (differ from the 2008 PDB).
#include <math.h>
#include "types.h"

#define PV(n) virtual void pv##n();

struct cSPVector3 {
  float x, y, z;
  cSPVector3() {}
  cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};
inline cSPVector3 operator+(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline cSPVector3 operator-(const cSPVector3& a) { return cSPVector3(-a.x, -a.y, -a.z); }
inline cSPVector3 operator*(const cSPVector3& a, float s) { return cSPVector3(a.x * s, a.y * s, a.z * s); }
inline float Dot(const cSPVector3& a, const cSPVector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline float Length(const cSPVector3& a) { return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z); }

// Plane as consumed by IntersectRayPlane: normal + distance (d = -dot(point, normal)).
struct cSPPlane {
  cSPVector3 mNormal;
  float mD;
  __forceinline cSPPlane(const cSPVector3& normal, const cSPVector3& point) : mNormal(normal), mD(-Dot(point, normal)) {}
};

struct Matrix3 {
  float m[9];
  Matrix3& Assign(const Matrix3& other);  // 0x0041cb40
};

// Editor-wide axis/point constants (bss; names are guesses from usage).
extern cSPVector3 kSPEditorOrigin;       // 0x015e920c (point the up/right planes pass through)
extern cSPVector3 kSPEditorUpAxis;       // 0x015e9308
extern cSPVector3 kSPEditorRightAxis;    // 0x015e9330 (normal of the symmetry plane)
extern cSPVector3 kSPEditorForwardAxis;  // 0x015e9384

bool IntersectRayPlane(const cSPVector3& origin, const cSPVector3& direction, const cSPPlane& plane, float& t);  // 0x0044e640

struct eastl_bitset54 {
  uint32_t mWord[2];
  bool test(unsigned int i) const { return ((mWord[i >> 5] >> (i & 31)) & 1) != 0; }
};

namespace eastl {
template <typename T>
class sp_ptr_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  uint32_t mAllocator[2];
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
};
}  // namespace eastl

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount(T* p);  // 0x00572660 (out of line for the skin manager)
  AutoRefCount(const AutoRefCount& x);  // user copy ctor: by-value args are built in place
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};
}  // namespace EA

namespace SP {

class cViewer {
 public:
  bool GetWorldRayFromScreenCoords(float x, float y, cSPVector3& origin, cSPVector3& direction);  // 0x007c4730
};

class cSPApp {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual cViewer* GetViewer();  // +0x58
};
cSPApp* App();  // 0x0067dd10

class cMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMessage(uint32_t id, int a, int b);  // +0x14
};
cMessageServer* MessageServer();  // 0x0067dcc0

// Editor state object returned by the getter at 0x00401050 (global 0x015d0c14).
class cEditorStateObject {
 public:
  void SetBool(uint32_t id, bool value);                  // 0x0045b110
  void SetBlock(uint32_t id, class cSPEditorBlock* block);  // 0x0045b080
};
cEditorStateObject* GetEditorStateObject();  // 0x00401050

class cSPEditorModel {
 public:
  float GetSize();          // 0x004adaa0
  bool IsUsingSymmetry();   // 0x004adc40
};

class cSPEditorSkinManager {
 public:
  virtual int AddRef();
  virtual int Release();
};
typedef EA::AutoRefCount<cSPEditorSkinManager> SkinRef;

class cSPEditorBlock {
 public:
  virtual void v0();
  char pad04[0x28 - 4];
  cSPEditorModel* mEditorModel;      // +0x28
  char pad2c[0x48 - 0x2c];
  cSPVector3 mPosition;              // +0x48
  char pad54[0xa8 - 0x54];
  Matrix3 mOrientation;              // +0xa8
  char padcc[0x33c - 0xcc];
  cSPEditorBlock* mpParent;          // +0x33c
  eastl::sp_ptr_vector<cSPEditorBlock*> mChildren;  // +0x340
  char pad354[0x3e0 - 0x354];
  cSPEditorBlock* mSymmetricBlock;   // +0x3e0
  char pad3e4[0xdc8 - 0x3e4];
  eastl_bitset54 mFlags;             // +0xdc8
  void SetBooleanAttribute(int attr, bool value);  // 0x00435a10
  bool IsPinned();                                 // 0x00435c80
  bool HasAnyBlockFlag();                          // 0x00435d40
  void RecursiveFlagA();                           // 0x0044ede0
};

typedef void BlockList;  // eastl::vector<AutoRefCount<cSPEditorBlock>> (opaque here)

class cSPEditorLimbJoint {
 public:
  cSPEditorBlock* mJointBlock;      // +0x0
  cSPEditorLimbJoint* mUpperJoint;  // +0x4
  eastl::sp_ptr_vector<cSPEditorLimbJoint*> mLowerJoints;  // +0x8
  cSPVector3 mTargetPosition;       // +0x1c
  char pad28[0x64 - 0x28];
  int mJointType;                   // +0x64
  int GetSign(bool b);                                   // 0x004874c0 (named Sign in symbols)
  int SignFromBlock(bool b);                             // 0x004876b0
  void SetTargetPosition(cSPVector3 pos);                // 0x00485930
  void Translate(cSPVector3 delta);                      // 0x00485a60
  cSPVector3 GetUpperDirection(int n);                   // 0x00487e90
};
typedef eastl::sp_ptr_vector<cSPEditorLimbJoint*> JointVector;

class cSPEditorLimbStructure {
 public:
  char pad00[0x18];
  cSPEditorLimbJoint* mBaseJoint;  // +0x18
  BlockList* GetBlocks();                                         // 0x00402ab0
  cSPEditorBlock* GetRootBlock();                                 // 0x007f99a0
  cSPEditorLimbJoint* GetJoint(cSPEditorBlock* block);            // 0x0048b2c0
  void SetHighlighting(bool b);                                   // 0x004890e0
  bool ClampJoints(JointVector* joints);                          // 0x0048ae60
  void ResolveJoints(JointVector* joints);                        // 0x0048af00
  bool CheckJoints(JointVector* joints);                          // 0x0048b080
  void MoveJoint(cSPEditorLimbJoint* joint, cSPVector3 pos);      // 0x0048a650
  void UpdatePositions();                                         // 0x0048b1c0
  bool UpdateAllLengths(bool b);                                  // 0x0048bf40
  void RefreshTargets(JointVector* joints, bool symmetric);       // 0x00489710
  void RefreshBlockTargets(cSPEditorBlock* block, bool symmetric);  // 0x004897b0
  void SetFeetTargets(bool b);                                    // 0x0048bae0
  void SetHandsTargets(bool b);                                   // 0x0048bbb0
  void UpdateFeetTargets();                                       // 0x0048bdd0
  void UpdateBlocks();                                            // 0x00489cd0
  void UpdateAnimation(int a, int b);                             // 0x0048ae30
  void SolveJoint(cSPEditorLimbJoint* joint, cSPEditorLimbJoint* end);  // 0x00488fe0
  void ResetJoints(bool b);                                       // 0x00488d00
  int GetFootCount();                                             // 0x00488a20
  void Settle(cSPEditorBlock* block);                             // 0x00488e80
};

// Recursive helper that mirrors a joint tree onto another limb structure (slice s005ad9a0).
struct cSPEditorJointMirror {
  cSPEditorLimbStructure* mpTarget;
  void Mirror(cSPEditorLimbJoint* joint);  // 0x005adfd0
};

// 60-byte highlight records; clear() is the out-of-line erase at 0x005af1c0.
struct cSPEditorHighlight { char data[0x3c]; };
struct HighlightVector {
  cSPEditorHighlight* mpBegin;
  cSPEditorHighlight* mpEnd;
  cSPEditorHighlight* mpCapacity;
  uint32_t mAllocator[2];
  void clear();  // 0x005af1c0
};

class cISPEditorBadnessCalculator {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
  virtual bool IsEnabled();  // +0x18
};

struct cSPEditortLimbTry {
  cSPVector3 mLoc;                          // +0x0
  float mBadness;                           // +0xc
  eastl::sp_ptr_vector<float> mDebugVals;   // +0x10
  cSPEditortLimbTry& operator=(const cSPEditortLimbTry& x);  // 0x005ae840
  ~cSPEditortLimbTry();                                      // 0x00732a10
};

// free helpers (cdecl)
void BuildHighlights(cSPEditorBlock* root, HighlightVector* out, bool b);  // 0x0049c8f0
void ClearHighlights(HighlightVector* v);                                  // 0x0049cb90
void RefreshHighlights(HighlightVector* v);                                // 0x0049ce40
cSPVector3 GetLimbPlanePosition(cSPEditorBlock* block);                    // 0x004a06c0
bool SignChanged(int oldSign, int newSign, bool b);                        // 0x004a7ea0
void PlayEditorSound(uint32_t id);                                         // 0x004a88d0
void SetPileState(cSPEditorBlock* block, BlockList* blocks);               // 0x004961d0
void UpdateSkin(cSPEditorBlock* block, BlockList* blocks, bool stacking, cSPEditorSkinManager* skin,
                int a, int b, int c, int d);                               // 0x004a6d20
cSPEditorBlock* PickStackTarget(cSPEditorBlock* block, cSPVector3 origin, cSPVector3 direction, SkinRef skin,
                                cSPVector3* hitPosition, cSPVector3* hitNormal, BlockList* blocks);  // 0x00499410
cSPEditorBlock* PickBlock(cSPEditorBlock* block, BlockList* blocks, cSPVector3 origin, cSPVector3 direction,
                          cSPVector3* hitPosition);                        // 0x004a3dc0
void RepinBlock(cSPEditorBlock* block, BlockList* blocks, cSPEditorBlock* parent);  // 0x004a29a0
void UnpinBlock(cSPEditorBlock* block);                                    // 0x004a1070
bool PlaceBlockOnBody(cSPEditorBlock* block, BlockList* blocks, cSPVector3 origin, cSPVector3 direction, SkinRef skin,
                      cSPVector3* hitPosition, int a, int b, int c);       // 0x0049a2a0
void PlaceBlock(cSPEditorBlock* block, int a, float scale, int b);         // 0x004982b0
void GetMissPlane(cSPEditorBlock* block, cSPVector3 direction, cSPVector3* position, cSPVector3* normal);  // 0x0049b8b0
void PlaceOnMissPlane(cSPEditorBlock* block, cSPVector3 origin, cSPVector3 direction, cSPVector3 planePosition,
                      cSPVector3 planeNormal, int b);                      // 0x0049bcc0
void GetLineForJoint(cSPEditorBlock* block, cSPVector3 origin, cSPVector3 direction, cSPVector3* lineStart,
                     cSPVector3* lineEnd);                                 // 0x00496d30
bool ConstrainOffset(cSPVector3 offset, cSPVector3* result, float scale);  // 0x00497f20
cSPVector3 MirrorPosition(const cSPVector3& v);                            // 0x004a8f40

namespace EditorUtils {
void SetSymmetricBlocksUIState(cSPEditorBlock* block, int a, int b);  // 0x004a7f30
cSPEditorBlock* GetFirstFootBlock(cSPEditorBlock* block);              // 0x004a9840
}

class cSPEditorManipulationObject {
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

class cRefCountV {
 public:
  virtual ~cRefCountV();
  int mRefCount;
};

class cSPEditorManipulationLimb : public cSPEditorManipulationObject, public cRefCountV {
 public:
  cSPEditorSkinManager* mSkin;                       // +0x1c
  cSPEditorLimbStructure* mLimbStructure;            // +0x20
  cSPEditorLimbStructure* mSymmetricLimbStructure;   // +0x24
  cSPEditorLimbStructure* mMirrorLimbStructure;      // +0x28
  JointVector mManipulatingJoints;                   // +0x2c
  JointVector mSymmetricJoints;                      // +0x40
  JointVector mMirrorJoints;                         // +0x54
  HighlightVector mHighlights;                       // +0x68
  HighlightVector mSymmetricHighlights;              // +0x7c
  JointVector mAllJoints;                            // +0x90
  JointVector mAllSymmetricJoints;                   // +0xa4
  cSPEditorBlock* mBlock;                            // +0xb8
  cSPEditorBlock* mOriginalParent;                   // +0xbc
  float mX;                                          // +0xc0
  float mY;                                          // +0xc4
  float mOldX;                                       // +0xc8
  float mOldY;                                       // +0xcc
  unsigned int mModifiers;                           // +0xd0
  cSPVector3 mMouseOffset;                           // +0xd4
  cSPVector3 mOriginalMouseOffset;                   // +0xe0
  cSPVector3 mOriginalBlockPosition;                 // +0xec
  int mManipType;                                    // +0xf8
  int mOriginalManipType;                            // +0xfc
  bool mIsOutsideBounds;                             // +0x100
  bool mIsStacking;                                  // +0x101
  cISPEditorBadnessCalculator* mBadnessCalculator;   // +0x104
  cSPVector3 mMissPlanePosition;                     // +0x108
  cSPVector3 mMissPlaneNormal;                       // +0x114
  cSPVector3 mLimbMissPlanePosition;                 // +0x120
  cSPVector3 mLimbMissPlaneNormal;                   // +0x12c
  int mBestIndex;                                    // +0x138
  cSPEditortLimbTry mBestTry;                        // +0x13c
  cSPEditortLimbTry mWorstTry;                       // +0x160
  cSPEditortLimbTry mTries[400];                     // +0x184

  void Update(float deltaTime);
  void ClearSymmetricHighlights();        // 0x005adb00
  float GetMaxLimbPlacementHeight();      // 0x005addb0
  void UpdateSymmetricJointPositions();   // 0x005addf0
  void CopyJointsToSymmetricLimbs();      // 0x005adf10
  void RecalculateLimbMissPlane();        // 0x005ae300
  void RefreshJointLists();               // 0x005ae750
  cSPEditortLimbTry PickOptimalPointOnLine(cSPEditorLimbJoint* joint, cSPVector3 lineStart, cSPVector3 lineEnd,
                                           int numTries, cSPEditortLimbTry* tries, cSPEditortLimbTry* worstTry,
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

static inline float Sign1(float v) { return v < 0.0f ? -1.0f : 1.0f; }

// @ 0x005AF200
void cSPEditorManipulationLimb::Update(float deltaTime) {
  if (!mBlock || !mBlock->mEditorModel)
    return;
  if (mX == mOldX && mY == mOldY)
    return;

  cSPEditorModel* model = mBlock->mEditorModel;
  mIsStacking = false;
  if (!mChangedObject)
    mChangedObject = true;
  mOldX = mX;
  mOldY = mY;

  cSPVector3 origin, direction;
  App()->GetViewer()->GetWorldRayFromScreenCoords(mX, mY, origin, direction);
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
      cSPEditorLimbJoint* joint = mLimbStructure->GetJoint(mBlock);
      float t;
      if (!IntersectRayPlane(origin, direction, cSPPlane(kSPEditorUpAxis, kSPEditorOrigin), t))
        return;
      cSPVector3 planePos = GetLimbPlanePosition(mBlock);
      float s = (planePos.z - origin.z) / direction.z;
      cSPVector3 hit = origin + direction * s;
      float x = hit.x;
      if (mBlock->mFlags.test(15) && usingSymmetry) {
        if (IntersectRayPlane(origin, direction, cSPPlane(kSPEditorRightAxis, kSPEditorOrigin), t)) {
          cSPVector3 center = origin + direction * t;
          const cSPVector3& pos = mBlock->mPosition;
          float toCenter = Length(center - pos);
          if (toCenter < Length(cSPVector3(-hit.x, hit.y, hit.z) - pos) && toCenter < Length(hit - pos))
            x = 0.0f;
        }
      }
      joint->SetTargetPosition(cSPVector3(x, hit.y, hit.z));
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
        cSPEditorLimbJoint* symJoint = mSymmetricLimbStructure->GetJoint(mBlock->mSymmetricBlock);
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
      cSPVector3 target;
      if (mModifiers & 0x20) {
        // Camera-facing plane through the block.
        cSPPlane plane(-direction, mBlock->mPosition);
        float t;
        if (IntersectRayPlane(origin, direction, plane, t))
          target = origin + direction * t;
        else
          target = mBlock->mPosition;
      } else {
        cSPEditorLimbJoint* joint = mLimbStructure->GetJoint(mBlock);
        cSPVector3 lineStart, lineEnd;
        GetLineForJoint(mBlock, origin, direction, &lineStart, &lineEnd);
        mBestTry = PickOptimalPointOnLine(joint, lineStart, lineEnd, 400, mTries, &mWorstTry, &mBestIndex);
        if (mBadnessCalculator && mBadnessCalculator->IsEnabled()) {
          cSPVector3 offset;
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
          cSPEditorLimbJoint* joint = mManipulatingJoints[i];
          if (joint->mJointType != 2)
            mLimbStructure->SolveJoint(joint, joint);
        }
        if (mSymmetricLimbStructure) {
          n = mSymmetricJoints.size();
          for (int i = 0; i < n; i++) {
            cSPEditorLimbJoint* joint = mSymmetricJoints[i];
            if (joint->mJointType != 2)
              mSymmetricLimbStructure->SolveJoint(joint, joint);
          }
        }
        if (mMirrorLimbStructure) {
          n = mMirrorJoints.size();
          for (int i = 0; i < n; i++) {
            cSPEditorLimbJoint* joint = mMirrorJoints[i];
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
      cSPEditorBlock* oldParent = mBlock->mpParent;
      oldSign = mManipulatingJoints[0]->GetSign(true);
      cSPVector3 stackPos, stackNormal, blockPos;
      cSPEditorBlock* stackTarget = PickStackTarget(mBlock, origin, direction, SkinRef(mSkin), &stackPos, &stackNormal,
                                                    mLimbStructure->GetBlocks());
      cSPEditorBlock* hitBlock = PickBlock(mBlock, mLimbStructure->GetBlocks(), origin, direction, &blockPos);
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
        cSPVector3 placePos;
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
        cSPEditorLimbJoint*& joint = mManipulatingJoints[i];
        joint->SetTargetPosition(mBlock->mPosition);
      }
      mLimbStructure->ClampJoints(&mManipulatingJoints);
      count = mManipulatingJoints.size();
      for (int i = 0; i < count; i++) {
        cSPEditorLimbJoint* joint = mManipulatingJoints[i];
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
      cSPEditorBlock* parent = mBlock->mpParent;
      if (parent && !parent->mFlags.test(7) && !(mModifiers & 2))
        return;
      oldSign = mManipulatingJoints[0]->GetSign(true);
      Matrix3 orientation;
      orientation.Assign(mBlock->mOrientation);
      cSPVector3 stackPos, stackNormal, blockPos;
      cSPEditorBlock* stackTarget = PickStackTarget(mBlock, origin, direction, SkinRef(mSkin), &stackPos, &stackNormal,
                                                    mLimbStructure->GetBlocks());
      cSPEditorBlock* hitBlock = PickBlock(mBlock, mLimbStructure->GetBlocks(), origin, direction, &blockPos);
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
        cSPVector3 placePos;
        placed = PlaceBlockOnBody(mBlock, mLimbStructure->GetBlocks(), origin, direction, SkinRef(mSkin), &placePos,
                                  0, 0, 1);
        if (mBlock->HasAnyBlockFlag()) {
          cSPEditorBlock* block = mBlock;
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
        cSPVector3 target;
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

      cSPVector3 oldTarget = mManipulatingJoints[0]->mTargetPosition;
      bool clamped = false;
      if (mBlock->mpParent)
        clamped = mLimbStructure->ClampJoints(&mManipulatingJoints);
      if (clamped) {
        cSPVector3 delta = mManipulatingJoints[0]->mTargetPosition - oldTarget;
        int count = mManipulatingJoints.size();
        for (int i = 0; i < count; i++) {
          cSPEditorLimbJoint*& joint = mManipulatingJoints[i];
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
