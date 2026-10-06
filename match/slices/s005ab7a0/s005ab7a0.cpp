// slice s005ab7a0 — SP::cSPEditorManipulationCellPinning::DoOnMouseMove (4525 bytes).
// The per-frame pinning drag of a cell-editor part: casts the mouse ray, places the
// block on the cell skin (GetPlacement) or, when it misses, on the z = -0.1 plane
// (clamped to the pinned range, or slid along the rig/symmetric block), then runs the
// behavior/snap/replace logic, re-pins the symmetric twin and refreshes symmetry state.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Retail layouts: cSPEditorBlock = dev PDB + 8 from mPosition on (+0x48 mPosition,
// +0x60 mOrientation, +0xa8 mBaseOrientation, +0xf0 mUserOrientation, +0x138
// mSurfaceNormal, +0x33c mSymmetricBlock, +0xdc8 bitset<60> mFlags);
// cSPEditorManipulationCellPinning = dev PDB + 4 (+0x128/+0x134 are retail-only).
#include "types.h"

extern "C" double __cdecl fabs(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(fabs, sqrt)

inline float Abs(float f) { return (float)fabs(f); }
// x87 square-root helpers (the module computes in SSE but takes roots with inline fsqrt).
inline float Sqrt(float f) {
  __asm fld f
  __asm fsqrt
  __asm fstp f
  return f;
}
inline float Length2(float a, float b) {
  float r;
  __asm fld a
  __asm fmul st(0), st(0)
  __asm fld b
  __asm fmul st(0), st(0)
  __asm faddp st(1), st(0)
  __asm fsqrt
  __asm fstp r
  return r;
}

struct cSPVector3 {
  float x, y, z;
  cSPVector3() {}
  cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};
inline cSPVector3 operator-(const cSPVector3& v) { return cSPVector3(-v.x, -v.y, -v.z); }
inline cSPVector3 Cross(const cSPVector3& a, const cSPVector3& b) {
  return cSPVector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

struct cSPMatrix3 {
  cSPVector3 xAxis, yAxis, zAxis;
  cSPMatrix3() {}
  cSPMatrix3(const cSPMatrix3& o);   // @ 0x0041cb40 (out of line)
  __forceinline cSPMatrix3(const cSPVector3& x, const cSPVector3& y, const cSPVector3& z) : xAxis(x), yAxis(y), zAxis(z) {}
};
// Row vector times matrix.
inline cSPVector3 operator*(const cSPVector3& v, const cSPMatrix3& m) {
  return cSPVector3(v.x * m.xAxis.x + v.y * m.yAxis.x + v.z * m.zAxis.x,
                    v.x * m.xAxis.y + v.y * m.yAxis.y + v.z * m.zAxis.y,
                    v.x * m.xAxis.z + v.y * m.yAxis.z + v.z * m.zAxis.z);
}

extern const cSPVector3 kZero;   // 0x015e8814 (Vector3::ZERO)
extern const cSPVector3 kUp;     // 0x015e88dc (Z axis)

bool operator==(const cSPVector3& a, const cSPVector3& b);        // @ 0x004232c0
cSPVector3 Normalize(const cSPVector3& v);                        // @ 0x00436ce0
cSPMatrix3 OrientationFromDirection(const cSPVector3& dir, const cSPVector3& up);  // @ 0x004a89e0
bool IsValidDirection(const cSPVector3& v);                       // @ 0x0059ab70

namespace EA {
template <class T>
struct AutoRefCount {
  T* mpObject;
  AutoRefCount(T* p = 0) : mpObject(p) {
    if (mpObject)
      mpObject->AddRef();
  }
  AutoRefCount(const AutoRefCount& o) : mpObject(o.mpObject) {
    if (mpObject)
      mpObject->AddRef();
  }
  ~AutoRefCount() {
    if (mpObject)
      mpObject->Release();
  }
  AutoRefCount& operator=(T* p);   // @ 0x004b09b0 (out of line)
  void Reset() {
    if (mpObject) {
      T* const pTemp = mpObject;
      mpObject = 0;
      pTemp->Release();
    }
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}  // namespace EA

namespace SP {

class cSPEditorBlock;
cSPVector3 normalized_safe(const cSPVector3& v);   // @ 0x00449c20
class cSPEditorModel {
 public:
  bool IsSymmetryEnabled();   // @ 0x004adc40
};

class cMWModel;
class cIModelWorld {
 public:
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
  virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
  virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
  virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
  virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
  virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
  virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
  virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
  virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
  virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
  virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68();
  virtual void SetRegionState(cMWModel* model, int region, uint32_t* pState, int flags);   // +0x114
};

struct bitset60 {   // eastl::bitset<60>
  uint32_t mWord[2];
  bool test(uint32_t i) const { return ((mWord[i >> 5] >> (i & 31)) & 1) != 0; }
};

class cSPEditorBlock {
 public:
  virtual void v00();
  virtual int AddRef();    // +0x04
  virtual int Release();   // +0x08
  uint32_t pad04[3];
  cMWModel* mModel;                  // +0x10
  uint32_t pad14;
  cIModelWorld* mModelWorld;         // +0x18
  uint32_t pad1c[3];
  cSPEditorModel* mEditorModel;      // +0x28
  uint32_t pad2c[7];
  cSPVector3 mPosition;              // +0x48
  cSPVector3 mHistoryPosition;       // +0x54
  cSPMatrix3 mOrientation;           // +0x60
  cSPMatrix3 mHistoryOrientation;    // +0x84
  cSPMatrix3 mBaseOrientation;       // +0xa8
  cSPMatrix3 mHistoryBaseOrientation;  // +0xcc
  cSPMatrix3 mUserOrientation;       // +0xf0
  cSPMatrix3 mHistoryUserOrientation;  // +0x114
  cSPVector3 mSurfaceNormal;         // +0x138
  uint32_t pad144[(0x33c - 0x144) / 4];
  EA::AutoRefCount<cSPEditorBlock> mSymmetricBlock;   // +0x33c
  uint32_t pad340[(0xdc8 - 0x340) / 4];
  bitset60 mFlags;                   // +0xdc8

  void SetBooleanAttribute(int attr, bool value);                  // @ 0x00435a10
  void LinkSymmetricBlock(cSPEditorBlock* block);                  // @ 0x00438700
  void UnlinkSymmetricBlock(cSPEditorBlock* block);                // @ 0x00438a40
  void SetSurfaceNormal(cSPVector3 n);                             // @ 0x005aa580
  void SetUserOrientation(cSPMatrix3 m);                           // @ 0x0043ffa0
  void SetRegion(int region, bool b);                              // @ 0x00451240
  void* GetAnchor();                                               // @ 0x004511f0
  void Reposition(void* anchor, cSPVector3 pos, cSPVector3 up, bool b);   // @ 0x004370a0
  void SyncTransform(bool b);                                      // @ 0x00437400
  int GetSymmetryIndex();                                          // @ 0x0044f220
  int CalculateSymmetrySign();                                     // @ 0x0044f240
  void SetBaseJointScale(int sign);                                // @ 0x0044e980
  bool IsSymmetricModel(int i);                                    // @ 0x0044c4d0
  void SetModelBasedOnSymmetrySign(int sign, int a, int b, int c, int d);   // @ 0x00439110
  void RecursiveFlagA();                                           // @ 0x0044ede0
};

struct BlockVector {   // eastl::vector<EA::AutoRefCount<cSPEditorBlock>, sp_vector_allocator>
  EA::AutoRefCount<cSPEditorBlock>* mpBegin;
  EA::AutoRefCount<cSPEditorBlock>* mpEnd;
  EA::AutoRefCount<cSPEditorBlock>* mpCapacity;
  uint32_t mAllocator[2];
  BlockVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~BlockVector();                                                  // @ 0x00453eb0
  void push_back(const EA::AutoRefCount<cSPEditorBlock>& v);       // @ 0x004541f0
};

class cSPEditorSkinManager {
 public:
  virtual int AddRef();
  virtual int Release();
  cSPEditorBlock* GetSymmetricBlockAt(int skin, cSPVector3 pos);   // @ 0x004c4d30
  bool Raycast(int skin, cSPVector3 start, cSPVector3 dir, cSPVector3* hitPos,
               cSPVector3* hitNormal, float* dist, bool b);        // @ 0x004c4a30
};

class cMessageManager {
 public:
  void PostMSG(uint32_t id, int a, cSPEditorBlock* block, int b);  // @ 0x0045ae40
};
cMessageManager* MessageManager();                                 // @ 0x00401050

class cViewer {
 public:
  void GetWorldRayFromScreenCoords(float x, float y, cSPVector3& origin, cSPVector3& dir);   // @ 0x007c4730
};
class cApp {
 public:
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
  virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21();
  virtual cViewer* GetViewer();   // +0x58
};
cApp* App();                      // @ 0x0067dd10

namespace EditorUtils {
bool GetRotationAndPositionBasedOnBehavior(cSPEditorBlock* block, cSPVector3& pos, cSPMatrix3& orient,
                                           cSPVector3 dir, bool b1, bool b2);           // @ 0x004942b0
void RepinBlockToTorso(cSPEditorBlock* block, cSPVector3 pos, cSPMatrix3 orient, int flag);   // @ 0x0049fbd0
cSPEditorBlock* PickBlocks(BlockVector& ignore, cSPVector3 start, cSPVector3 dir, cSPVector3& hitPos,
                           cSPVector3& hitNormal, int* pIndex, bool& bHit, int* pLevel);  // @ 0x004a4840
bool DoSnapReplace(cSPEditorBlock* block, cSPEditorBlock* target, cSPVector3* pos, cSPMatrix3* orient);   // @ 0x004a2350
void SetSymmetricBlocksUIState(cSPEditorBlock* block, BlockVector* blocks, int state);  // @ 0x004a7f30
}  // namespace EditorUtils

// Unnamed editor helpers (cdecl).
void MoveBlockAndPile(cSPEditorBlock* block, BlockVector* pile, cSPVector3 pos, cSPMatrix3 orient);   // @ 0x0049ecf0
void PreparePileForRig(cSPEditorBlock* block, BlockVector* pile);                                   // @ 0x004961d0
void PinPileToRig(cSPEditorBlock* block, BlockVector* pile, cSPVector3 origin, cSPVector3 dir,
                  EA::AutoRefCount<cSPEditorSkinManager> skin, cSPVector3* outPos, cSPMatrix3* outOrient,
                  int a, int b);                                                                    // @ 0x0049a2a0
bool SnapToAxis(cSPEditorBlock* block, cSPVector3* pos, cSPMatrix3* orient, cSPMatrix3* userOrient,
                bool a, float f, bool c, int d);                                                     // @ 0x00498470
cSPEditorBlock* FindSnapTarget(cSPEditorBlock* block, cSPVector3 pos);                              // @ 0x004a3c70
bool UnbumpBlock(cSPEditorBlock* block);                                                            // @ 0x004a1e10
void ResetBlockSnap(cSPEditorBlock* block, bool flag);                                              // @ 0x004983d0
bool NeedsSymmetricModel(int symIndex, int sign, bool symmetric);                                   // @ 0x004a7ea0
void UpdateBlockAndPile(cSPEditorBlock* block, BlockVector* pile, int a, int b, int c, int d, int e, int f);  // @ 0x004a6d20

class cSPEditorManipulationObject {
 public:
  virtual ~cSPEditorManipulationObject() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};

class cRefCount {
 public:
  virtual ~cRefCount() {}
  int mRefCount;
};

class cSPEditorManipulationCellPinning : public cSPEditorManipulationObject, public cRefCount {
 public:
  BlockVector mPileList;                          // +0x1c
  EA::AutoRefCount<cSPEditorBlock> mBlock;        // +0x30
  EA::AutoRefCount<cSPEditorBlock> mBumpedBlock;  // +0x34
  cSPVector3 mMouseOffset;                        // +0x38
  bool mRecalculateMouseOffset;                   // +0x44
  cSPVector3 mMouseOffset3D;                      // +0x48
  cSPVector3 mVertexOffset;                       // +0x54
  cSPMatrix3 mInverseNormalTransform;             // +0x60
  cSPMatrix3 mInverseNormalTransform2;            // +0x84
  float mOffsetLength;                            // +0xa8
  float mOffsetRotation;                          // +0xac
  cSPVector3 mUnTransformedPosition;              // +0xb0
  cSPMatrix3 mUnTransformedOrientation;           // +0xbc
  EA::AutoRefCount<cSPEditorSkinManager> mSkin;   // +0xe0
  void* mInflatedMesh;                            // +0xe4
  uint32_t mEdgeVectors[15];                      // +0xe8 (three sp_vectors)
  bool mHadParentOnMouseDown;                     // +0x124
  cSPVector3 mPinBottom;                          // +0x128 (lowest pinned position)
  cSPVector3 mPinTop;                             // +0x134 (highest pinned position)
  float mX;                                       // +0x140
  float mY;                                       // +0x144
  bool mPinToRigBlocks;                           // +0x148

  virtual bool DoOnMouseMove(float x, float y, int modifiers);   // retail vtable slot 8 (other virtuals omitted)
  bool GetPlacement(cSPVector3 origin, cSPVector3 dir, cSPVector3* pos, cSPMatrix3* orient,
                    cSPVector3* normal);                           // @ 0x005aa9c0
  cSPVector3 ClampToPinnedRange(cSPVector3 pos, cSPEditorModel* model);   // @ 0x005aa5d0
};

// @ 0x005ab7a0
bool cSPEditorManipulationCellPinning::DoOnMouseMove(float x, float y, int) {
  mX = x;
  mY = y;

  cSPVector3 origin, dir;
  App()->GetViewer()->GetWorldRayFromScreenCoords(x, y, origin, dir);
  if (Abs(origin.x) < 0.0001f) {
    if (origin.x > 0.0f)
      origin.x = 0.0001f;
    else
      origin.x = -0.0001f;
  }

  if (!mBlock)
    return true;

  if (mBlock->mFlags.test(35) && !mBlock->mFlags.test(51)) {
    mBlock->SetBooleanAttribute(35, false);
    mBlock->SetBooleanAttribute(51, true);
  }

  cSPMatrix3 startOrientation(mBlock->mOrientation);
  cSPVector3 placedPos, placedNormal;
  cSPMatrix3 placedOrient;
  bool placed = GetPlacement(origin, dir, &placedPos, &placedOrient, &placedNormal);

  // Intersect the mouse ray with the z = -0.1 working plane.
  cSPVector3 planeHit;
  {
    cSPVector3 planePoint(kZero.x, kZero.y, -0.1f);
    cSPVector3 planeNormal(0.0f, 0.0f, 1.0f);
    float planeD = -planeNormal.x * planePoint.x - planeNormal.y * planePoint.y - planeNormal.z * planePoint.z;
    float denom = dir.x * planeNormal.x + dir.y * planeNormal.y + dir.z * planeNormal.z;
    if (denom != 0.0f) {
      float t = -((origin.x * planeNormal.x + origin.y * planeNormal.y + origin.z * planeNormal.z) + planeD) / denom;
      if (t >= 0.0f)
        planeHit = cSPVector3(t * dir.x + origin.x, t * dir.y + origin.y, t * dir.z + origin.z);
    }
  }

  cSPEditorBlock* prevSymmetric = mBlock->mSymmetricBlock;
  if (placed) {
    MoveBlockAndPile(mBlock, &mPileList, placedPos, placedOrient);
    mUnTransformedPosition = placedPos;
    mUnTransformedOrientation = placedOrient;
    cSPEditorBlock* symmetric = mSkin->GetSymmetricBlockAt(0, placedPos);
    if (!mBlock->mSymmetricBlock && symmetric)
      MessageManager()->PostMSG(0x3f1bf58, 0, mBlock, 0);
    if (mBlock->mSymmetricBlock != symmetric)
      symmetric->LinkSymmetricBlock(mBlock);
    mBlock->mSurfaceNormal = -placedOrient.yAxis;
  } else {
    if (mPinToRigBlocks) {
      PreparePileForRig(mBlock, &mPileList);
      cSPVector3 rigPos;
      cSPMatrix3 rigOrient;
      PinPileToRig(mBlock, &mPileList, origin, dir, mSkin, &rigPos, &rigOrient, 0, 1);
      prevSymmetric = mBlock->mSymmetricBlock;
    }
    if (!mPinToRigBlocks && mBlock->mSymmetricBlock)
      mBlock->mSymmetricBlock->UnlinkSymmetricBlock(mBlock);
  }
  if (prevSymmetric && !mBlock->mSymmetricBlock)
    MessageManager()->PostMSG(0x3f1bf59, 0, mBlock, 0);

  if (!mBlock->mSymmetricBlock) {
    // Free part: follow the plane point, clamped to the pinned range, facing away from it.
    cSPVector3 clamped = ClampToPinnedRange(planeHit, mBlock->mEditorModel);
    float dx = planeHit.x - clamped.x;
    float dy = planeHit.y - clamped.y;
    float len = Sqrt(dx * dx + dy * dy + 1e-08f);
    float inv = 1.0f / len;
    cSPVector3 facing(inv * dx, inv * dy, inv * 0.0f);
    cSPMatrix3 rot = OrientationFromDirection(facing, kUp);
    cSPVector3 newPos = mMouseOffset * rot;
    newPos = cSPVector3(newPos.x + planeHit.x, newPos.y + planeHit.y, newPos.z + planeHit.z);

    cSPVector3 clamped2 = ClampToPinnedRange(newPos, mBlock->mEditorModel);
    float dx2 = newPos.x - clamped2.x;
    float dy2 = newPos.y - clamped2.y;
    float len2 = Sqrt(dx2 * dx2 + dy2 * dy2);
    float inv2 = 1.0f / len2;
    cSPVector3 facing2(inv2 * dx2, inv2 * dy2, inv2 * 0.0f);
    cSPMatrix3 orient = OrientationFromDirection(facing2, kUp);
    EditorUtils::GetRotationAndPositionBasedOnBehavior(mBlock, newPos, orient, mBlock->mPosition, false, false);
    EditorUtils::RepinBlockToTorso(mBlock, newPos, orient, 0);
  }

  if (mBlock->mSymmetricBlock) {
    // Pinned to a symmetric twin: slide along the rig, then snap.
    bool onPlane = mBlock->mFlags.test(0);
    if (mBlock->mFlags.test(33)) {
      float tilt = Abs(mBlock->mOrientation.yAxis.z);
      float height = Abs(mBlock->mPosition.z - -0.1f);
      if (!(tilt < 0.4f && height < 0.1f))
        onPlane = false;
    }
    int pickIndex = -1;
    bool pickHit = false;
    cSPVector3 pos = mBlock->mPosition;
    cSPMatrix3 orient(mBlock->mOrientation);

    if (onPlane) {
      cSPMatrix3 slideOrient(mBlock->mOrientation);
      cSPEditorBlock* block = mBlock;
      cSPVector3 rayPos;
      rayPos.x = block->mPosition.x;
      rayPos.y = block->mPosition.y;
      cSPVector3 rayDir(block->mOrientation.yAxis.x, block->mOrientation.yAxis.y, 0.0f);
      if (Abs(planeHit.x) < 0.07f && planeHit.y > mPinBottom.y + 0.1f && planeHit.y < mPinTop.y - 0.1f) {
        rayPos = planeHit;
        if (planeHit.x > 0.0f) {
          rayPos.x = 10.0f;
          rayDir = cSPVector3(-1.0f, 0.0f, 0.0f);
        } else {
          rayPos.x = -10.0f;
          rayDir = cSPVector3(1.0f, 0.0f, 0.0f);
        }
      }
      float inv = 1.0f / Length2(rayDir.y, rayDir.x);
      rayDir = cSPVector3(inv * rayDir.x, rayDir.y * inv, inv * rayDir.z);
      if (!IsValidDirection(rayDir)) {
        cSPVector3 away = planeHit;
        if (planeHit == kZero)
          away.x = 1.0f;
        rayDir = normalized_safe(-away);
      }

      if (placed) {
        cSPVector3 hitNormal;
        float dist = 0.0f;
        cSPVector3 start(rayPos.x - rayDir.x * 2.0f, rayPos.y - rayDir.y * 2.0f, -0.1f - rayDir.z * 2.0f);
        if (mSkin->Raycast(0, start, rayDir, &rayPos, &hitNormal, &dist, true)) {
          rayPos.z = -0.1f;
          hitNormal.z = 0.0f;
          cSPVector3 yAxis = -Normalize(hitNormal);
          cSPVector3 xAxis = Normalize(Cross(yAxis, kUp));
          orient = cSPMatrix3(xAxis, yAxis, kUp);
          pos = rayPos;
          cSPEditorBlock* symmetric = mSkin->GetSymmetricBlockAt(0, rayPos);
          if (mBlock->mSymmetricBlock != symmetric)
            symmetric->LinkSymmetricBlock(mBlock);
          mBlock->SetSurfaceNormal(-yAxis);
        }
      } else {
        BlockVector ignore;
        ignore.push_back(EA::AutoRefCount<cSPEditorBlock>(block->mSymmetricBlock));
        cSPVector3 hitPos, hitNormal;
        cSPVector3 start(rayPos.x - rayDir.x * 4.0f, rayPos.y - rayDir.y * 4.0f, -0.1f - rayDir.z * 4.0f);
        if (EditorUtils::PickBlocks(ignore, start, rayDir, hitPos, hitNormal, &pickIndex, pickHit, 0)) {
          hitPos.z = -0.1f;
          hitNormal.z = 0.0f;
          hitNormal = Normalize(hitNormal);
          slideOrient = OrientationFromDirection(hitNormal, kUp);
          pos = hitPos;
          orient = slideOrient;
        }
      }
    }

    EditorUtils::GetRotationAndPositionBasedOnBehavior(mBlock, pos, orient, mBlock->mPosition, false, false);
    cSPMatrix3 userOrient(mBlock->mUserOrientation);
    cSPEditorBlock* block = mBlock;
    bool flag15 = block->mFlags.test(15);
    if (block->mFlags.test(33) || Abs(pos.y - mPinBottom.y) < 0.1f || Abs(pos.y - mPinTop.y) < 0.1f)
      SnapToAxis(block, &pos, &orient, &userOrient, true, 1.0f, false, 0);
    mBlock->SetUserOrientation(userOrient);

    cSPEditorBlock* target = FindSnapTarget(mBlock, pos);
    bool replaced = false;
    if (target) {
      if (target != mBumpedBlock && mBumpedBlock)
        UnbumpBlock(mBumpedBlock);
      replaced = EditorUtils::DoSnapReplace(mBlock, target, &pos, &orient);
      mBumpedBlock = target;
    } else if (mBumpedBlock) {
      UnbumpBlock(mBumpedBlock);
      mBumpedBlock.Reset();
    } else {
      ResetBlockSnap(mBlock, flag15);
    }
    MoveBlockAndPile(mBlock, &mPileList, pos, orient);

    if (pickIndex != -1 && !replaced) {
      cSPEditorBlock* symmetric = mBlock->mSymmetricBlock;
      uint32_t state;
      symmetric->mModelWorld->SetRegionState(symmetric->mModel, pickIndex, &state, 0);
      mBlock->SetRegion(pickIndex, pickHit);
    }
    if (mBlock->GetAnchor()) {
      cSPEditorBlock* b = mBlock;
      b->Reposition(b->GetAnchor(), mBlock->mPosition, mBlock->mOrientation.yAxis, true);
      mBlock->SyncTransform(true);
    }
  } else {
    cSPVector3 pos = mBlock->mPosition;
    cSPMatrix3 orient(mBlock->mBaseOrientation);
    EditorUtils::DoSnapReplace(mBlock, 0, &pos, &orient);
    mBumpedBlock.Reset();
  }

  int symmetryIndex = mBlock->GetSymmetryIndex();
  int sign = mBlock->CalculateSymmetrySign();
  bool symmetryEnabled = mBlock->mEditorModel ? mBlock->mEditorModel->IsSymmetryEnabled() : true;
  mBlock->SetBaseJointScale(sign);
  if (symmetryEnabled && NeedsSymmetricModel(symmetryIndex, sign, mBlock->IsSymmetricModel(0)))
    mBlock->SetModelBasedOnSymmetrySign(sign, 0, 1, 0, 0);
  mBlock->RecursiveFlagA();
  EditorUtils::SetSymmetricBlocksUIState(mBlock, &mPileList, 0);
  UpdateBlockAndPile(mBlock, &mPileList, 0, 0, 0, 0, 1, 1);
  if (!mChangedObject)
    mChangedObject = true;
  return true;
}

}  // namespace SP
