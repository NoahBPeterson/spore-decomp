// slice s00a82d90: EA::Swarm::cVisualEffect::UpdateTransforms (0x00a82d90).
// Rebuilds the composed ("Cmpt") rigid/source transforms of a visual effect from its
// rigid and source transforms and the effect description flags (ignore scale /
// orientation, LOD size scale, screen-size range clamp, Z-pole orientation, rigid
// always, view-relative / camera facing), pushes them to every component
// (IComponent::SetTransforms, vtable slot 6) and updates the world position / up.
// Retail layout: ModAPI Swarm::cVisualEffect (0x188 bytes); description flags
// and cGlobalParams from the 2008 dev PDB (offsets confirmed against the asm).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE, x87 fsqrt).
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------- math
struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
  Vector3& operator+=(const Vector3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
};
static inline Vector3 operator*(const Vector3& v, float s) { return Vector3(v.x * s, v.y * s, v.z * s); }
static inline Vector3 operator-(const Vector3& a, const Vector3& b) {
  return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

// rw::math::fpu::Matrix33Template<float> (rows), out-of-line copy at 0x0041cb40
struct Matrix3 {
  Vector3 row[3];
  Matrix3() {}
  Matrix3(const Matrix3& m);                          // 0x0041cb40
};

struct Vector4 {
  Vector3 v3;
  float w;
};
struct Matrix4 {
  Vector4 row[4];
};

extern const Vector3 kSwarmVector3Zero;               // 0x01677a2c
extern const Matrix3 kSwarmMatrix3Identity;           // 0x01677ad8

Vector3 Normalize(const Vector3& v);                  // 0x006e6df0 (cdecl, sret)
float SmoothStepClamp(float x, float lo, float hi);   // 0x00a81de0
float FastAtan2(float y, float x);                    // 0x00a78d90

static inline Vector3 Cross(const Vector3& a, const Vector3& b) {
  return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

// Row vector times rotation matrix.
static inline Vector3 Rotate(const Vector3& v, const Matrix3& m) {
  return Vector3(v.x * m.row[0].x + v.y * m.row[1].x + v.z * m.row[2].x,
                 v.x * m.row[0].y + v.y * m.row[1].y + v.z * m.row[2].y,
                 v.x * m.row[0].z + v.y * m.row[1].z + v.z * m.row[2].z);
}

// rw::math-style SSE clamp helper (inline asm, as in other /arch:SSE Swarm modules);
// it is also what gives the function its 16-byte aligned frame.
static __forceinline float Clamp(float v, float lo, float hi) {
  __asm {
    movss xmm0, v
    maxss xmm0, lo
    minss xmm0, hi
    movss v, xmm0
  }
  return v;
}

// ---------------------------------------------------------------- EA::Swarm types
namespace EA { namespace Swarm {

template <int N> struct bitset {
  uint32_t mWord;
  bool test(int i) const { return ((mWord >> i) & 1) != 0; }
  void set(int i) { mWord |= 1u << i; }
  void reset(int i) { mWord &= ~(1u << i); }
};

// cTransform (0x38): flags, mod count, offset, scale, rotation.
struct cTransform {
  enum { kScale = 1, kRotation = 2, kOffset = 4 };
  uint16_t mFlags;                                    // +0x00
  uint16_t mModCount;                                 // +0x02
  Vector3 mOffset;                                    // +0x04
  float mScale;                                       // +0x10
  Matrix3 mRotation;                                  // +0x14

  cTransform()
      : mFlags(0), mModCount(0), mOffset(kSwarmVector3Zero), mScale(1.0f),
        mRotation(kSwarmMatrix3Identity) {}
  cTransform(const cTransform& t)
      : mFlags(t.mFlags), mModCount(t.mModCount), mOffset(t.mOffset), mScale(t.mScale),
        mRotation(t.mRotation) {}
  cTransform& operator=(const cTransform& t);         // 0x00537dc0
  void PreTransformBy(const cTransform& t);           // 0x00537f40
  void Apply(Vector3& v) const;                       // 0x007cdee0: v = (v*R)*scale + offset
  void RotateZ(float angle);                          // 0x007d1ac0
  void Reset();                                       // 0x00832dc0: identity
  // Same body as Apply (0x007cdee0).
  void ApplyInline(Vector3& v) const {
    if (mFlags & kRotation)
      v = Rotate(v, mRotation);
    float s = mScale;
    v.y *= s;
    v.z *= s;
    v.x *= s;
    v += mOffset;
  }
  void ApplyRotation(Vector3& v) const {
    if (mFlags & kRotation)
      v = Rotate(v, mRotation);
  }
  void FixPoint(const Vector3& p);                    // 0x00a72bf0 (see FixPointInline)

  void SetScale(float s) {
    mScale = s;
    ++mModCount;
  }
  void Scale(float s) {
    mScale = mScale * s;
    mFlags |= kScale;
    ++mModCount;
  }
  void Translate(const Vector3& v) {
    mOffset += v;
    mFlags |= kOffset;
    ++mModCount;
  }
  void SetRotation(const Matrix3& m) {
    mRotation = m;
    mFlags |= kRotation;
    ++mModCount;
  }
  void ClearRotation() {
    mRotation = kSwarmMatrix3Identity;
    mFlags &= ~kRotation;
    ++mModCount;
  }
  // Same body as FixPoint (0x00a72bf0): move the offset so that p maps onto itself.
  void FixPointInline(const Vector3& p) {
    mOffset += p - Rotate(p * mScale, mRotation);
    mFlags |= kOffset;
    ++mModCount;
  }
};

// r = b, then r.PreTransformBy(a)
cTransform operator*(const cTransform& a, const cTransform& b);  // 0x007d5590

struct cVisualEffectDescription {
  enum {
    kFlagViewRelative = 0, kFlagCameraFacing = 1, kFlagRigidAlways = 6, kFlagIgnoreScale = 9,
    kFlagIgnoreOrientation = 10, kFlagOrientationZPole = 11, kFlagDetach = 14,
    kFlagScreenSizeRange = 15, kFlagNoSmoothStepClamp = 16
  };
  bitset<22> mFlags;                                  // +0x00
  uint32_t mComponentAppFlagsMask;                    // +0x04
  uint32_t mNotifyMessageID;                          // +0x08
  float mScreenSizeRange[2];                          // +0x0c
};

struct cGlobalParams {
  uint32_t pad0[7];
  Matrix4 mProjectionMatrix;                          // +0x1c
  Matrix3 mCameraOrientation;                         // +0x5c
  Vector3 mCameraTranslation;                         // +0x80
};

struct IComponent {
  virtual void Initialize(void*, void*, void*) = 0;
  virtual void Dispose() = 0;
  virtual void Start(int) = 0;
  virtual int Stop(int) = 0;
  virtual int IsRunning() = 0;
  virtual void ApplyEffect(float, float, void*) = 0;
  virtual void SetTransforms(const cTransform& source, const cTransform& rigid) = 0;  // +0x18
};

struct cComponentRec {                                // 0x5c
  cTransform mLocalXform;                             // +0x00
  IComponent* mComponent;                             // +0x38 (AutoRefCount)
  uint32_t mDescRecIndex;                             // +0x3c
  float mTimeScale;                                   // +0x40
  bitset<8> mFlags;                                   // +0x44
  uint32_t mStateDescIndices[5];                      // +0x48
};

class cVisualEffect {
public:
  enum {
    kFlagTransformsDirty = 2, kFlagHasBeenPositioned = 7, kFlagIsRunning = 9
  };
  enum { kRecFlagRigidSource = 6 };
  void UpdateTransforms();

  uint32_t pad0[10];                                  // vtables, refcount, manager, ids
  cVisualEffectDescription* mpDescription;            // +0x28
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
  cComponentRec* mComponentRecsBegin;                 // +0x144 (eastl::vector)
  cComponentRec* mComponentRecsEnd;                   // +0x148
  uint32_t mComponentRecsRest[3];                     // +0x14c
  void* mRigidBone;                                   // +0x158
  uint32_t mRigidBoneModCount;                        // +0x15c
  void* mSourceBone;                                  // +0x160
  uint32_t mSourceBoneModCount;                       // +0x164
  float mLODSizeScale[2];                             // +0x168
  float mSizeScaleLOD;                                // +0x170
  void* mWorld;                                       // +0x174
  cGlobalParams* mGlobalParams;                       // +0x178
};

// @ 0x00a82d90
void cVisualEffect::UpdateTransforms() {
  mFlags.reset(kFlagTransformsDirty);
  cVisualEffectDescription* desc = mpDescription;
  if (desc == 0)
    return;
  if (mFlags.test(kFlagHasBeenPositioned) && mFlags.test(kFlagIsRunning) &&
      desc->mFlags.test(cVisualEffectDescription::kFlagDetach))
    return;

  if (desc->mFlags.test(cVisualEffectDescription::kFlagIgnoreScale)) {
    mSourceTransform.SetScale(1.0f);
    mRigidTransform.SetScale(1.0f);
  }
  if (mpDescription->mFlags.test(cVisualEffectDescription::kFlagIgnoreOrientation)) {
    mSourceTransform.ClearRotation();
    mRigidTransform.ClearRotation();
  }

  mCmptSourceTransform = mSourceTransform;
  mCmptRigidTransform = mRigidTransform;

  // LOD size scale, about the source position
  if (mSizeScaleLOD >= 0.0f) {
    Vector3 pivot(mCmptSourceTransform.mOffset);
    mCmptRigidTransform.Scale(mSizeScaleLOD);
    mCmptRigidTransform.Translate(pivot - pivot * mSizeScaleLOD);
  }

  // screen-size range: clamp the projected size of the effect
  if (mpDescription->mFlags.test(cVisualEffectDescription::kFlagScreenSizeRange)) {
    Vector3 pos(mCmptSourceTransform.mOffset);
    mCmptRigidTransform.Apply(pos);
    const Matrix4& proj = mGlobalParams->mProjectionMatrix;
    float x0 = proj.row[0].v3.x, x1 = proj.row[0].v3.y, x2 = proj.row[0].v3.z;
    float y0 = proj.row[1].v3.x, y1 = proj.row[1].v3.y, y2 = proj.row[1].v3.z;
    float w = pos.y * proj.row[1].w + pos.z * proj.row[2].w + pos.x * proj.row[0].w + proj.row[3].w;
    if (w > 0.0f) {
      float size = sqrtf((x0 * x0 + x1 * x1 + x2 * x2) + (y0 * y0 + y1 * y1 + y2 * y2)) /
                   w * 10.0f;
      cVisualEffectDescription* d = mpDescription;
      float clamped;
      if (d->mFlags.test(cVisualEffectDescription::kFlagNoSmoothStepClamp))
        clamped = Clamp(size, d->mScreenSizeRange[0], d->mScreenSizeRange[1]);
      else
        clamped = SmoothStepClamp(size, d->mScreenSizeRange[0], d->mScreenSizeRange[1]);
      if (clamped != size) {
        cTransform t;
        t.SetScale(clamped / size);
        t.FixPoint(mCmptSourceTransform.mOffset);
        mCmptRigidTransform.PreTransformBy(t);
      }
    }
  }

  // orientation from the source X axis, rotated about the Z pole only
  if (mpDescription->mFlags.test(cVisualEffectDescription::kFlagOrientationZPole)) {
    Matrix3 m(kSwarmMatrix3Identity);
    float x = mCmptSourceTransform.mRotation.row[0].x;
    float y = mCmptSourceTransform.mRotation.row[0].y;
    float len = sqrtf(x * x + y * y);
    if (len > 0.0f) {
      float inv = 1.0f / len;
      m.row[0].x = inv * x;
      m.row[0].y = inv * y;
      m.row[1].x = -m.row[0].y;
      m.row[1].y = m.row[0].x;
    }
    mCmptSourceTransform.SetRotation(m);
  }

  if (mpDescription->mFlags.test(cVisualEffectDescription::kFlagRigidAlways)) {
    mCmptRigidTransform = mCmptSourceTransform * mCmptRigidTransform;
    mCmptSourceTransform.Reset();
  }

  // view relative: orient toward the camera (camera facing) or with the camera roll
  if (mpDescription->mFlags.test(cVisualEffectDescription::kFlagViewRelative)) {
    cTransform t;
    Vector3 pos(mCmptSourceTransform.mOffset);
    mCmptRigidTransform.Apply(pos);
    const cGlobalParams* gp = mGlobalParams;
    if (mpDescription->mFlags.test(cVisualEffectDescription::kFlagCameraFacing)) {
      Vector3 up(gp->mCameraOrientation.row[2]);
      Vector3 dir(gp->mCameraTranslation.x - pos.x, gp->mCameraTranslation.y - pos.y,
                  gp->mCameraTranslation.z - pos.z);
      Vector3 f = Normalize(dir);
      Vector3 r = Cross(up, f);
      Matrix3 m;
      m.row[0] = f;
      float len = sqrtf(r.x * r.x + r.y * r.y + r.z * r.z);
      if (len > 0.0f) {
        float inv = 1.0f / len;
        r.x = r.x * inv;
        r.y = r.y * inv;
        r.z = r.z * inv;
        up = Cross(f, r);
      } else {
        r = Vector3(1.0f, 0.0f, 0.0f);
        up = Vector3(0.0f, 1.0f, 0.0f);
      }
      m.row[1] = r;
      m.row[2] = up;
      t.SetRotation(m);
    } else {
      t.RotateZ(FastAtan2(gp->mCameraOrientation.row[1].y, gp->mCameraOrientation.row[1].x));
    }
    t.FixPointInline(pos);
    mCmptRigidTransform = mCmptRigidTransform * t;
  }

  for (cComponentRec *rec = mComponentRecsBegin, *end = mComponentRecsEnd; rec != end; ++rec) {
    IComponent* comp = rec->mComponent;
    if (rec->mFlags.test(kRecFlagRigidSource)) {
      cTransform rigid(mCmptRigidTransform);
      rigid.PreTransformBy(mCmptSourceTransform);
      comp->SetTransforms(rec->mLocalXform, rigid);
    } else {
      cTransform source(mCmptSourceTransform);
      source.PreTransformBy(rec->mLocalXform);
      comp->SetTransforms(source, mCmptRigidTransform);
    }
  }

  mWorldPosition = mSourceTransform.mOffset;
  mRigidTransform.ApplyInline(mWorldPosition);
  mWorldUp = mSourceTransform.mRotation.row[2];
  mRigidTransform.ApplyRotation(mWorldUp);

  mFlags.set(kFlagHasBeenPositioned);
}

}}  // namespace EA::Swarm
