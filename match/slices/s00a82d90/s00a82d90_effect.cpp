// slice s00a82d90 (extra): EA::Swarm::cVisualEffect::ApplyEffect (0x00a83940) and
// EA::Swarm::cVisualEffect::SetTransforms (0x00a83bd0).
//
// cVisualEffect : cIVisualEffect (vtable, +0x00), cComponentBase (cIComponent vtable
// +0x04, RefCountTemplate vtable +0x08, refcount +0x0c).  The two functions are
// overrides of cIComponent virtuals, so they run with the cComponentBase pointer
// (object+4); MSVC folds the -4 bias into the member displacements and only
// materialises object+0 for the cVisualEffect calls.  Retail cVisualEffect (= dev
// PDB layout minus the 0x10-byte mEffectID/mDescID/mStartTransition block):
//   0x10 mRefCount, 0x14 mName(0x10), 0x24 mSimTime, 0x28 mDesc, 0x2c mFlags,
//   0x30 mWorldPosition, 0x3c mWorldUp, 0x48 mCurrentLOD, 0x4c mCurrentLODLerp,
//   0x50 mCurrentRange, 0x58 mLODDistanceScale, 0x5c/0x60 notify id/user,
//   0x64/0x9c/0xd4/0x10c the four cTransforms, 0x144 mComponentRecs(0x14),
//   0x158 mRigidBone, 0x15c mod, 0x160 mSourceBone, 0x164 mod, 0x168 mLODSizeScale,
//   0x170 mSizeScaleLOD, 0x174 mWorld, 0x178 mGlobalParams, 0x17c mParams, 0x180 mSeed.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace EA {

template <class T> struct RefCountTemplate {
  virtual void Destroy();
  T mRefCount;                                        // +0x04
};

namespace Swarm {

struct Vector3 {
  float x, y, z;
};

struct Matrix3 {
  Vector3 row[3];
};

// cTransform (0x38): flags, mod count, offset, scale, rotation.
struct cTransform {
  enum { kScale = 1, kRotation = 2, kOffset = 4 };
  uint16_t mFlags;                                    // +0x00
  uint16_t mModCount;                                 // +0x02
  Vector3 mOffset;                                    // +0x04
  float mScale;                                       // +0x10
  Matrix3 mRotation;                                  // +0x14

  cTransform& operator=(const cTransform& t);         // 0x00537dc0
};

template <int N> struct bitset {
  uint32_t mWord;
  bool test(int i) const { return ((mWord >> i) & 1) != 0; }
  void set(int i) { mWord |= 1u << i; }
  void reset(int i) { mWord &= ~(1u << i); }
};

struct cComponentStats {
  int mPad0;                                          // +0x00
  int mNumApplies;                                    // +0x04
  int mNumComponents;                                 // +0x08
  int mNumRunning;                                    // +0x0c
};

struct cGlobalParams {
  uint32_t mProjection[23];                           // +0x00 (0x5c bytes)
  Matrix3 mCameraOrientation;                         // +0x5c
  Vector3 mCameraTranslation;                         // +0x80
};

struct cVisualEffectDescription {
  enum {
    kFlagViewRelative = 0, kFlagCameraFacing = 1, kFlagInCameraSpace = 2,
    kFlagInCameraSpaceRigid = 3, kFlagScreenSizeRange = 15
  };
  bitset<22> mFlags;                                  // +0x00
  uint32_t mComponentAppFlagsMask;                    // +0x04
  uint32_t mNotifyMessageID;                          // +0x08
  float mScreenSizeRange[2];                          // +0x0c
};

struct cIBone {
  virtual bool GetTransform(uint32_t* pModCount, cTransform* pTransform);  // slot 0
};

struct cIComponent {
  virtual void Init(void*, void*, void*) = 0;
  virtual void Shutdown() = 0;
  virtual void Start(int) = 0;
  virtual void Stop(int) = 0;
  virtual bool IsRunning() = 0;
  virtual void ApplyEffect(float, float, cComponentStats*) = 0;            // +0x14
  virtual void SetTransforms(const cTransform& source, const cTransform& rigid) = 0;  // +0x18
};

struct cComponentBase : cIComponent, RefCountTemplate<int> {};

struct cComponentRec {                                // 0x5c
  enum { kFlagBlendOverride = 7, kFlagBlendZero = 8 };
  cTransform mLocalXform;                             // +0x00
  cIComponent* mComponent;                            // +0x38
  uint32_t mDescRecIndex;                             // +0x3c
  float mTimeScale;                                   // +0x40
  uint32_t mFlags;                                    // +0x44
  uint32_t mStateDescIndices[5];                      // +0x48
};

struct cIVisualEffect {
  virtual int AddRef();                               // vtable only
};

struct cVisualEffectDescription;

class cVisualEffect : public cIVisualEffect, public cComponentBase {
public:
  enum {
    kFlagHidden = 1, kFlagTransformsDirty = 2, kFlagNeedsPriming = 8,
    kFlagTimestepPreroll = 12
  };

  virtual void ApplyEffect(float timeScale, float dt, cComponentStats* stats);
  virtual void SetTransforms(const cTransform& source, const cTransform& rigid);

  void PrerollEffect(float dt, cComponentStats* stats);   // 0x00a825c0
  void UpdateTransforms();                               // 0x00a82d90

  int mRefCount;                                      // +0x10
  uint32_t mName[4];                                  // +0x14
  float mSimTime;                                     // +0x24
  cVisualEffectDescription* mDesc;                    // +0x28
  bitset<13> mFlags;                                  // +0x2c
  Vector3 mWorldPosition;                             // +0x30
  Vector3 mWorldUp;                                   // +0x3c
  int mCurrentLOD;                                    // +0x48
  float mCurrentLODLerp;                              // +0x4c
  float mCurrentRange[2];                             // +0x50
  float mLODDistanceScale;                            // +0x58
  uint32_t mNotifyMessageID;                          // +0x5c
  uint32_t mNotifyMessageUserData;                    // +0x60
  cTransform mRigidTransform;                         // +0x64
  cTransform mSourceTransform;                        // +0x9c
  cTransform mCmptRigidTransform;                     // +0xd4
  cTransform mCmptSourceTransform;                    // +0x10c
  cComponentRec* mComponentRecsBegin;                 // +0x144
  cComponentRec* mComponentRecsEnd;                   // +0x148
  uint32_t mComponentRecsRest[3];                     // +0x14c
  cIBone* mRigidBone;                                 // +0x158
  uint32_t mRigidBoneModCount;                        // +0x15c
  cIBone* mSourceBone;                                // +0x160
  uint32_t mSourceBoneModCount;                       // +0x164
  float mLODSizeScale[2];                             // +0x168
  float mSizeScaleLOD;                                // +0x170
  void* mWorld;                                       // +0x174
  cGlobalParams* mGlobalParams;                       // +0x178
  void* mParams;                                      // +0x17c
  uint32_t mSeed;                                     // +0x180
};

// Set the rigid and/or source transform from the camera, then step the LOD size
// scale towards its target and refresh the composed transforms when anything moved.
// @ 0x00a83940
void cVisualEffect::ApplyEffect(float timeScale, float dt, cComponentStats* stats) {
  if (mDesc == 0)
    return;

  bool dirty = true;
  stats->mNumApplies++;

  if (mFlags.test(kFlagTimestepPreroll)) {
    PrerollEffect(dt, stats);
    mFlags.reset(kFlagTimestepPreroll);
  }
  mFlags.reset(kFlagNeedsPriming);

  if (!mFlags.test(kFlagHidden)) {
    const bool bRelevant =
        mDesc->mFlags.test(cVisualEffectDescription::kFlagViewRelative) ||
        mDesc->mFlags.test(cVisualEffectDescription::kFlagCameraFacing) ||
        mDesc->mFlags.test(cVisualEffectDescription::kFlagScreenSizeRange);
    if (!mFlags.test(kFlagTransformsDirty) && !bRelevant)
      dirty = false;

    if (mDesc->mFlags.test(cVisualEffectDescription::kFlagInCameraSpaceRigid)) {
      mRigidTransform.mModCount++;
      mRigidTransform.mScale = 1.0f;
      mRigidTransform.mRotation = mGlobalParams->mCameraOrientation;
      mRigidTransform.mFlags |= cTransform::kRotation;
      mRigidTransform.mModCount++;
      mRigidTransform.mOffset = mGlobalParams->mCameraTranslation;
      mRigidTransform.mFlags |= cTransform::kOffset;
      mRigidTransform.mModCount++;
      dirty = true;
    }
    if (mDesc->mFlags.test(cVisualEffectDescription::kFlagInCameraSpace)) {
      mSourceTransform.mModCount++;
      mSourceTransform.mScale = 1.0f;
      mSourceTransform.mRotation = mGlobalParams->mCameraOrientation;
      mSourceTransform.mFlags |= cTransform::kRotation;
      mSourceTransform.mModCount++;
      mSourceTransform.mOffset = mGlobalParams->mCameraTranslation;
      mSourceTransform.mFlags |= cTransform::kOffset;
      mSourceTransform.mModCount++;
      dirty = true;
    }

    if (mRigidBone != 0 &&
        mRigidBone->GetTransform(&mRigidBoneModCount, &mRigidTransform))
      dirty = true;
    if (mSourceBone != 0 &&
        mSourceBone->GetTransform(&mSourceBoneModCount, &mSourceTransform))
      dirty = true;

    float lo = mLODSizeScale[0];
    if (lo >= 0.0f) {
      float old = mSizeScaleLOD;
      mSizeScaleLOD = (mLODSizeScale[1] - lo) * dt + lo;
      if (dirty || mSizeScaleLOD != old)
        UpdateTransforms();
    } else if (dirty) {
      UpdateTransforms();
    }
  }

  cComponentRec* end = mComponentRecsEnd;
  for (cComponentRec* rec = mComponentRecsBegin; rec != end; ++rec) {
    stats->mNumComponents++;
    if (!rec->mComponent->IsRunning())
      continue;
    stats->mNumRunning++;
    float blend;
    if (rec->mFlags & (1u << cComponentRec::kFlagBlendOverride))
      blend = (rec->mFlags & (1u << cComponentRec::kFlagBlendZero)) ? 0.0f : 1.0f;
    else
      blend = mCurrentLODLerp;
    rec->mComponent->ApplyEffect(rec->mTimeScale * timeScale, blend, stats);
  }
}

// @ 0x00a83bd0
void cVisualEffect::SetTransforms(const cTransform& source, const cTransform& rigid) {
  mSourceTransform = source;
  mRigidTransform = rigid;
  UpdateTransforms();
}

}}  // namespace EA::Swarm
