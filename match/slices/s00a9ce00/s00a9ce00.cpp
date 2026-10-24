// Slice s00a9ce00: EA::Swarm::cParticlesEffect particle -> model transform (0x00a9ce00).
// Called per particle by StreamModelParticles (0x00a9f170, slice s00a9f170). Names are coined
// ("BuildParticleTransform"); layouts are retail (see s00a9f170): eastl::vector is 0x14 bytes, the
// description is cParticlesDescription (alignMode at +0x134, wiggles at +0x170).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE, x87 for sqrt and the unsigned convert).
#include "types.h"
#include <math.h>

struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

// rw::math::fpu::Matrix33Template<float,0>: its copy ctor is out of line (0x41cb40).
struct Matrix33 {
  float m[3][3];
  Matrix33() {}
  Matrix33(const Matrix33& o);                          // @ 0x41cb40
};

struct Quat {
  float x, y, z, w;
};

// eastl::vector<T, sp_vector_allocator> as laid out in retail (0x14 bytes)
template <typename T>
struct CurveVector {
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  uint32_t mAllocator[2];
  size_t size() const { return (size_t)(mpEnd - mpBegin); }
  bool empty() const { return mpBegin == mpEnd; }
};
struct Wiggle {
  float f[7];
};

// 0x34-byte description sub-block used by the particle path/curve code.
struct FxSub {
  uint32_t mWords[13];
};

// 0x18-byte per-particle state block (first float is the curve timer).
struct FxState {
  float mTimer;                                       // +0x00
  uint32_t mWords[5];                                 // +0x04
  void FUN_00a790a0(struct FxSub* sub);               // 0x00a790a0
  void FUN_00a79300(Vector3* out);                    // 0x00a79300
};

// 0x38-byte transform passed to the swarm path/snap helpers.
struct Xform {
  uint32_t mFlags;                                    // +0x00
  Vector3 mOffset;                                    // +0x04
  float mScale;                                       // +0x10
  float mRotation[9];                                 // +0x14
};

// Two-point path view embedded in the description.
struct PathView {
  void* mpBegin;                                      // +0x00
  void* mpEnd;                                        // +0x04
};

// 0x30-byte description path block; the +0x1c view is the fallback path.
struct SwarmPath {
  PathView mMain;                                     // +0x00
  uint32_t mUnknown08[5];                             // +0x08
  PathView mAlt;                                      // +0x1c
  uint32_t mUnknown24[3];                             // +0x24
};

// runtime-initialized per-module constants (.bss)
extern const Vector3 kTransformZero;                    // 0x01678f44
extern const Matrix33 kTransformIdentity;               // 0x01679010
extern const float kDegToRad;                           // 0x01678ffc

// EA::Swarm::cTransform (0x38): flags, mod count, offset, scale, rotation.
struct cTransform {
  uint16_t mFlags;                                      // +0x00
  uint16_t mModCount;                                   // +0x02
  Vector3 mOffset;                                      // +0x04
  float mScale;                                         // +0x10
  Matrix33 mRotation;                                   // +0x14
  cTransform()
      : mFlags(0), mModCount(0), mOffset(kTransformZero), mScale(1.0f),
        mRotation(kTransformIdentity) {}
  void RotateZ(float angle);                            // @ 0x007d1ac0
  void PreRotateX(float angle);                         // @ 0x005a2d90
  void RotateY(float angle);                            // @ 0x006b9050 (mixes rows 0 and 2)
};
struct cSPTransform {
  void operator=(const cTransform& t);                  // @ 0x00537dc0
};

struct cParticlesDescription {
  uint32_t mFlags00;                                    // +0x000
  uint32_t mFlags04;                                    // +0x004
  uint32_t mFlags08;                                    // +0x008 bits 25 (path), 23 (attractor), 20 (sub-curves), 12 (collision)
  uint32_t mFlags;                                      // +0x00c bit 2: particle carries an orientation quaternion
  uint32_t pad10[(0x7c - 0x10) / 4];
  float mRateCurveTime;                                 // +0x07c
  uint32_t pad80[(0x9c - 0x80) / 4];
  CurveVector<float> mRotXCurve;                        // +0x09c (PreRotateX)
  CurveVector<float> mRotYCurve;                        // +0x0b0 (RotateY)
  CurveVector<float> mRotZCurve;                        // +0x0c4 (RotateZ)
  uint32_t padD8[(0xe4 - 0xd8) / 4];
  float mRotXOffset;                                    // +0x0e4
  float mRotYOffset;                                    // +0x0e8
  float mRotZOffset;                                    // +0x0ec
  uint32_t padF0[(0x134 - 0xf0) / 4];
  uint8_t mAlignMode;                                   // +0x134 (2..4 = align an axis to the velocity)
  uint8_t pad135[3];
  uint32_t pad138[(0x144 - 0x138) / 4];
  Vector3 mOffset144;                                   // +0x144 acceleration offset
  uint32_t pad150[(0x168 - 0x150) / 4];
  float mDrag168;                                       // +0x168 velocity damping
  uint32_t pad16c[(0x170 - 0x16c) / 4];
  CurveVector<Wiggle> mWiggles;                         // +0x170
  uint32_t pad184[(0x200 - 0x184) / 4];
  FxSub mSubs[2];                                       // +0x200, +0x234 curve/sub-state blocks
  uint32_t pad268[(0x274 - 0x268) / 4];
  float mAlignLag;                                      // +0x274 (>0: smooth the spin angle)
  float mAlignSpin;                                     // +0x278
  float mSpinDamping;                                   // +0x27c
  uint32_t pad280[(0x28c - 0x280) / 4];
  SwarmPath mPath28c;                                   // +0x28c
  float mPathSpeed;                                     // +0x2bc
};

struct cParticle {
  uint32_t mNodeNext;                                   // +0x00
  uint32_t mNodePrev;                                   // +0x04
  float mAge;                                           // +0x08
  float mLife;                                          // +0x0c
  Vector3 mPosition;                                    // +0x10
  Vector3 mVelocity;                                    // +0x1c
  uint32_t pad28[(0x44 - 0x28) / 4];
  float mSpin;                                          // +0x44
  float mRotation;                                      // +0x48 (-999 = unset)
  FxState mState4c;                                     // +0x4c
  FxState mState64;                                     // +0x64
  uint32_t pad7c;                                       // +0x7c
  Quat mOrientation;                                    // +0x80
  uint32_t pad90[1];
  float mRotZVary;                                      // +0x94
  float mRotXVary;                                      // +0x98
  float mRotYVary;                                      // +0x9c
};

// Callees (all cdecl)
Vector3* __cdecl RotateByQuat(Vector3* out, const Vector3* v, const Quat* q);   // @ 0x0059aed0
void __cdecl QuatToMatrix(Matrix33* out, const Quat* q);                        // @ 0x004a9b40
void __cdecl AlignAxisX(const Vector3* dir, Matrix33* out);                     // @ 0x00a81a20
void __cdecl AlignAxisY(const Vector3* dir, Matrix33* out);                     // @ 0x00a818f0
void __cdecl AlignAxisZ(const Vector3* dir, Matrix33* out);                     // @ 0x00a81b80
float __cdecl MatrixAngle(const Matrix33* m);                                   // @ 0x00a9af40
void __cdecl WigglePoint(float time, const CurveVector<Wiggle>* wiggles, const Vector3* center,
                         Vector3* pos);                                         // @ 0x00a9aff0

// Piecewise-linear curve lookup, t in [0,1].
__forceinline float EvalCurve(const CurveVector<float>& v, float t) {
  size_t n = v.size() - 1;
  if (n == 0)
    return v.mpBegin[0];
  float f = (float)n * t;
  int i = (int)f;
  float frac = f - (float)i;
  if (frac > 0.0f)
    return (v.mpBegin[i + 1] - v.mpBegin[i]) * frac + v.mpBegin[i];
  return v.mpBegin[i];
}

struct cParticlesEffect {
  uint32_t pad00[3];
  cParticlesDescription* mDesc;                         // +0x00c
  uint32_t pad10[(0x34 - 0x10) / 4];
  Vector3 mCenter;                                      // +0x034
  uint32_t pad40[(0xa0 - 0x40) / 4];
  double mOverallTime;                                  // +0x0a0

  void BuildParticleTransform(cParticle* p, float t, float size, Vector3* pos,
                              cSPTransform* out);       // @ 0x00a9ce00
};

// Particle emitter instance used by the update/step routines (retail layout).
struct ParticleEmitter {
  uint32_t pad00[3];
  cParticlesDescription* mDesc;                         // +0x00c
  uint32_t pad10;
  void* mpFactory;                                      // +0x014
  uint32_t pad18;
  uint32_t u1c;                                         // +0x01c
  uint8_t pad20[2];
  uint8_t b22;                                          // +0x022
  uint8_t pad23[0x0d];
  Xform mXform30;                                       // +0x030
  Xform mXform68;                                       // +0x068
  uint32_t padA0[(0xcc - 0xa0) / 4];
  Vector3 mAccel;                                       // +0x0cc
  uint32_t padD8[(0x114 - 0xd8) / 4];
  Vector3 mAttractor;                                   // +0x114
  float mAttractorStrength;                             // +0x120
  uint32_t pad124[(0x194 - 0x124) / 4];
  void* mpCollisionObj;                                 // +0x194
  uint32_t pad198[(0x218 - 0x198) / 4];
  PathView mPath;                                       // +0x218

  bool FUN_00a9b8d0(cParticle* p, Vector3* pos);        // 0x00a9b8d0
  bool FUN_00a9bf20(cParticle* p, float dt);            // 0x00a9bf20
  bool FUN_00a9d640(cParticle* p, float dt);            // 0x00a9d640
};

// Callees used by the emitter update.
void __cdecl FUN_00a798d0(float* pos, float dt, PathView* path, float speed, Xform* xf);
bool __cdecl FUN_00a79500(SwarmPath* path, const Vector3* pos, float radius, Vector3* out);

extern const float kMaxStep;                            // 0x01458c2c
extern const float kTwo;                                // 0x01470f1c
extern const float kOne;                                // 0x01485720

// @ 0x00A9CE00
void cParticlesEffect::BuildParticleTransform(cParticle* p, float t, float size,
                                              Vector3* pos, cSPTransform* out) {
  cTransform tr;
  ++tr.mModCount;
  tr.mScale = size;
  cParticlesDescription* d = mDesc;
  uint8_t mode = d->mAlignMode;
  if (mode < 2 || mode > 4) {
    tr.RotateZ(p->mRotation * kDegToRad);
  } else {
    Matrix33 m(kTransformIdentity);
    Vector3 v = p->mVelocity;
    float len = (float)sqrt((v.z * v.z + v.y * v.y) + v.x * v.x);
    if (len > 0.0001f) {
      float inv = 1.0f / len;
      v.x = inv * v.x;
      v.y = v.y * inv;
      v.z = v.z * inv;
    } else {
      v.x = v.x * 10000.0f;
      v.y = v.y * 10000.0f;
      v.z = v.z * 10000.0f;
      (&v.x)[mode - 2] = (1.0f - len * 10000.0f) + (&v.x)[mode - 2];
    }
    d = mDesc;
    if ((d->mFlags >> 2) & 1) {
      Quat q;
      q.x = -p->mOrientation.x;
      q.y = -p->mOrientation.y;
      q.z = -p->mOrientation.z;
      q.w = p->mOrientation.w;
      Vector3 tmp;
      v = *RotateByQuat(&tmp, &v, &q);
    }
    switch (d->mAlignMode) {
    case 2: AlignAxisX(&v, &m); break;
    case 3: AlignAxisY(&v, &m); break;
    case 4: AlignAxisZ(&v, &m); break;
    }
    tr.mRotation = m;
    tr.mFlags |= 2;
    ++tr.mModCount;
    float lag = mDesc->mAlignLag;
    if (lag > 0.0f) {
      float cur = MatrixAngle(&m);
      float old = p->mRotation;
      float target;
      if (old == -999.0f) {
        target = cur;
      } else {
        if (old - 0.5f > cur)
          old = old - 1.0f;
        else if (cur > old + 0.5f)
          old = old + 1.0f;
        target = ((cur - old) / lag) * 0.06666667f + old;
      }
      tr.RotateZ((target - cur) * kDegToRad);
      p->mRotation = target;
    }
    d = mDesc;
    if (d->mAlignSpin != 0.0f) {
      switch (d->mAlignMode) {
      case 2: tr.PreRotateX(p->mSpin); break;
      case 3: tr.RotateY(p->mSpin); break;
      case 4: tr.RotateZ(p->mSpin); break;
      }
    }
  }
  if ((d->mFlags >> 2) & 1) {
    Matrix33 q;
    QuatToMatrix(&q, &p->mOrientation);
    Matrix33 r;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        r.m[i][j] = (tr.mRotation.m[i][0] * q.m[0][j] + tr.mRotation.m[i][1] * q.m[1][j]) +
                    tr.mRotation.m[i][2] * q.m[2][j];
    tr.mRotation = r;
    tr.mFlags |= 2;
    ++tr.mModCount;
  }
  d = mDesc;
  tr.RotateY((p->mRotYVary * EvalCurve(d->mRotYCurve, t) + d->mRotYOffset) * kDegToRad);
  d = mDesc;
  tr.PreRotateX((p->mRotXVary * EvalCurve(d->mRotXCurve, t) + d->mRotXOffset) * kDegToRad);
  d = mDesc;
  tr.RotateZ((p->mRotZVary * EvalCurve(d->mRotZCurve, t) + d->mRotZOffset) * kDegToRad);
  if (!d->mWiggles.empty())
    WigglePoint((float)(d->mRateCurveTime * mOverallTime), &d->mWiggles, &mCenter,
                pos);
  tr.mOffset.x = pos->x;
  tr.mOffset.y = pos->y;
  tr.mOffset.z = pos->z;
  tr.mFlags |= 4;
  ++tr.mModCount;
  *out = tr;
}

// @ 0x00A9D640
bool ParticleEmitter::FUN_00a9d640(cParticle* p, float dt) {
  p->mAge = p->mAge + dt;
  if (p->mLife <= p->mAge)
    return false;

  for (;;) {
    const float* stepPtr = &kMaxStep;
    if (!(dt > kMaxStep))
      stepPtr = &dt;
    float step = *stepPtr;

    Vector3 pos = p->mPosition;
    Vector3 vel = p->mVelocity;
    cParticlesDescription* d = this->mDesc;
    unsigned char pathFlag = (unsigned char)(d->mFlags08 >> 25);

    if (pathFlag & 1) {
      PathView* path;
      if (this->mPath.mpBegin != this->mPath.mpEnd)
        path = &this->mPath;
      else
        path = &d->mPath28c.mAlt;
      FUN_00a798d0(&p->mAge, step, path, d->mPathSpeed, &this->mXform30);
    } else {
      p->mPosition.x = pos.x + vel.x * step;
      p->mPosition.y = pos.y + vel.y * step;
      p->mPosition.z = pos.z + vel.z * step;
    }

    Vector3 accel = this->mAccel;
    unsigned char timerFlag = (unsigned char)(this->mDesc->mFlags08 >> 20);
    if (timerFlag & 1) {
      float t0 = p->mState4c.mTimer - step;
      p->mState4c.mTimer = t0;
      float t1 = p->mState64.mTimer - step;
      p->mState64.mTimer = t1;
      bool reset0 = t0 < 0.0f;
      bool reset1 = t1 < 0.0f;
      if (reset0)
        p->mState4c.FUN_00a790a0(&this->mDesc->mSubs[0]);
      p->mState4c.FUN_00a79300(&accel);
      if (reset1)
        p->mState64.FUN_00a790a0(&this->mDesc->mSubs[1]);
      p->mState64.FUN_00a79300(&accel);
    }

    d = this->mDesc;
    unsigned char quatFlag = (unsigned char)(d->mFlags >> 2);
    if (quatFlag & 1) {
      float f7 = p->mOrientation.z;
      float f8 = p->mOrientation.x;
      float f10 = p->mOrientation.y;
      float f11 = p->mOrientation.w;
      float f6 = (f7 * f8 - f11 * f10) * accel.x;
      float f9 = (f11 * f7 + f10 * f8) * accel.x;
      accel.x = ((f10 * f8 - f11 * f7) * accel.y +
                 (f11 * f10 + f7 * f8) * accel.z) * kTwo +
                (kOne - (f7 * f7 + f10 * f10) * kTwo) * accel.x;
      float local20 = (f9 + (f7 * f10 - f11 * f8) * accel.z) * kTwo +
                      (kOne - (f7 * f7 + f8 * f8) * kTwo) * accel.y;
      accel.z = (f6 + (f11 * f8 + f7 * f10) * accel.y) * kTwo +
                (kOne - (f10 * f10 + f8 * f8) * kTwo) * accel.z;
      accel.y = local20;
    }

    accel.y = d->mOffset144.y + accel.y;
    accel.z = d->mOffset144.z + accel.z;
    accel.x = d->mOffset144.x + accel.x;

    unsigned char attractorFlag = (unsigned char)(d->mFlags08 >> 23);
    if (attractorFlag & 1) {
      Vector3 attractor;
      attractor.x = this->mAttractor.x - p->mPosition.x;
      attractor.y = this->mAttractor.y - p->mPosition.y;
      attractor.z = this->mAttractor.z - p->mPosition.z;
      if (!FUN_00a79500(&d->mPath28c, &attractor, this->mAttractorStrength, &accel))
        break;
    }

    float vy = p->mVelocity.y + accel.y * step;
    p->mVelocity.y = vy;
    float vx = p->mVelocity.x + accel.x * step;
    p->mVelocity.x = vx;
    float vz = p->mVelocity.z + accel.z * step;
    p->mVelocity.z = vz;
    float drag = kOne - this->mDesc->mDrag168 * step;
    p->mVelocity.x = vx * drag;
    p->mVelocity.y = vy * drag;
    p->mVelocity.z = vz * drag;

    unsigned char collFlag = (unsigned char)(this->mDesc->mFlags08 >> 12);
    if (((collFlag & 1) != 0 && !FUN_00a9b8d0(p, &pos)) ||
        (this->mpCollisionObj != 0 && !FUN_00a9bf20(p, step)))
      break;

    d = this->mDesc;
    float spin = d->mAlignSpin;
    if (spin != 0.0f) {
      float cross = p->mVelocity.y * vel.x - p->mVelocity.x * vel.y;
      float len = (float)sqrt(vel.x * vel.x + (vel.y * vel.y + vel.z * vel.z));
      if (0.0f < len)
        cross = cross / len;
      float s = p->mSpin - (d->mSpinDamping * p->mSpin) * step;
      p->mSpin = s;
      p->mSpin = s - (d->mAlignSpin * cross) * step;
    }

    dt -= step;
    if (dt <= 0.0f)
      return true;
  }
  return false;
}
