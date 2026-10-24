// SP::cCreatureCameraBase camera math (SporeEP1_RL). Region 0x625e70-0x626daf.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
//   00625e70  AimTowardsTarget
//   00625f70  FUN_00625f70  (walk/orbit damping toward the target)
//   00626290  ReloadTuning
//   006268a0  CalculateCameraToWorldMatrix
//   00626b50  SetInitialCameraValues
#include "types.h"
#include <math.h>

static inline void** Vt(void* p) { return *(void***)p; }

// ---- property lists (Property::GetFloat/GetInt are out-of-line thiscall members) ----------
struct Property {
  char pad00[0x12];
  unsigned short mType;   // +0x12 (9 = int32, 13 = float)
  float* GetFloat();      // 0x0041ea70
  int* GetInt();          // 0x0041e990
};
namespace App {
class PropertyList {
 public:
  virtual void AddRef();
  virtual void Release();
  virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
  virtual void v7(); virtual void v8();
  virtual bool GetProperty(uint32_t id, Property*& result);         // +0x24
};
class IPropertyManager {
 public:
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10();
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList*& result);  // +0x2c
};
}  // namespace App
App::IPropertyManager* PropertyManager();     // 0x0067de30
extern uint32_t gCameraTuningGroup;           // 0x01521b5c
extern const float kDegToRad;                 // 0x013fdec8 (0.017453292)
extern float gTune_1521888, gTune_152188c, gTune_1521890, gTune_152187c, gTune_1521880,
    gTune_1521884, gTune_1521894, gTune_1521898, gTune_152189c;

struct PropListPtr {
  App::PropertyList* mpObject;
  PropListPtr() : mpObject(0) {}
  App::PropertyList*& operator&() {
    if (mpObject) {
      App::PropertyList* p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return mpObject;
  }
  ~PropListPtr() { if (mpObject) mpObject->Release(); }
};

static inline void ReadFloat(App::PropertyList* list, uint32_t id, float& dst) {
  if (list) {
    Property* p;
    if (list->GetProperty(id, p) && p->mType == 13)
      dst = *p->GetFloat();
  }
}
static inline void ReadFloatDeg(App::PropertyList* list, uint32_t id, float& dst) {
  if (list) {
    Property* p;
    if (list->GetProperty(id, p) && p->mType == 13)
      dst = *p->GetFloat() * kDegToRad;
  }
}

struct cVec3 { float x, y, z; };
struct cQuat { float x, y, z, w; };
struct cMat33 {
  cVec3 xAxis, yAxis, zAxis;   // +0x00/+0x0c/+0x18
  void Assign(const void* src);   // 0x41cb40
};
struct cTransform {
  uint16_t mFlags;              // +0x00
  uint16_t mModificationCount;  // +0x02
  cVec3  mTranslation;          // +0x04
  float  mScale;                // +0x10
  cMat33 mRotation;             // +0x14
  void RotateY(float a);        // 0x4099b0
  void PreRotateX(float a);     // 0x5a2d90
  cTransform& operator=(const cTransform& x);  // 0x537dc0
};

struct tCameraData {
  float dt;                          // +0x00
  cVec3 platformPosition;            // +0x04
  cVec3 platformVelocity;            // +0x10
  cQuat platformOrientation;         // +0x1c
  cVec3 avatarPosition;              // +0x2c
  float currentPlayerTheta;          // +0x38
  float currentPlayerPitch;          // +0x3c
  float currentPlayerDistance;       // +0x40
  cVec3 desiredPosition;             // +0x44
  cVec3 desiredLookAt;               // +0x50
  float mDesiredLookAtXOffset;       // +0x5c
  float mDesiredLookAtYOffset;       // +0x60
  cVec3 newPlatformPosition;         // +0x64
  cVec3 newPlatformVelocity;         // +0x70
  cQuat newPlatformOrientation;      // +0x7c
  float desiredPlayerTheta;          // +0x8c
  float desiredPlayerPitch;          // +0x90
  float desiredPlayerDistance;       // +0x94
  float nonPenetratingPhi;           // +0x98
  bool  bPenetrating;                // +0x9c
  cVec3 currentPreTranslate;         // +0xa0
  cVec3 desiredPreTranslate;         // +0xac
  bool  bTransitioning;              // +0xb8
};

class cICameraController { public: virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); };
class IRef2 { public: virtual void r0(); virtual void r1(); };
struct Depends {
  char pad00[0x5c];
  cVec3 mTargetCameraPositionOffset;   // +0x5c (this+0x6c)
  cVec3 mActualCameraPositionOffset;   // +0x68 (this+0x78)
};

class cCreatureCameraBase : public cICameraController, public IRef2 {
public:
  int padA[2];                 // +0x08
  char mDependsRaw[0x78];      // +0x10 (cCreatureCameraDepends)
  int mCameraInputState;       // +0x88
  int mCameraState;            // +0x8c
  int mCameraMode;             // +0x90
  int mDesiredCameraMode;      // +0x94
  tCameraData mCameraData;     // +0x98
  float mMouseSensitivityX;    // +0x154
  float mMouseSensitivityY;    // +0x158
  float mMouseSensitivityZ;    // +0x15c
  float mMinCameraPhi;         // +0x160
  float mMaxCameraPhi;         // +0x164
  float mMinCameraDistance;    // +0x168
  float mMaxCameraDistance;    // +0x16c
  float mNearClip;             // +0x170
  float mFarClip;              // +0x174
  float mTuning178;            // +0x178
  float mTuning17c;            // +0x17c
  float mTuning180;            // +0x180
  float mTuning184;            // +0x184
  float mTuning188;            // +0x188
  float mFieldOfViewX;         // +0x18c
  float mFieldOfViewY;         // +0x190
  char mCameraToWorld[0x38];   // +0x194
  char padTail[0x200 - 0x1cc];
  App::PropertyList* mpTuningProps;  // +0x200

  void AimTowardsTarget(int unused);              // 00625e70
  void FUN_00625f70();                            // 00625f70
  void ReloadTuning();                            // 00626290
  void CalculateCameraToWorldMatrix();            // 006268a0
  void SetInitialCameraValues(uint32_t a, uint32_t b, uint32_t c, const float* v);  // 00626b50
  void SetCurrentPolarCoords(float theta, float phi, float distance);  // 0x00625560
};

extern float gUpX;    // 0x15f66f8
extern float gUpY;    // 0x15f66fc
extern float gUpZ;    // 0x15f6700
extern float gT0;     // 0x15f65fc
extern float gT1;     // 0x15f6600
extern float gT2;     // 0x15f6604
extern char  gMat3;   // 0x15f672c
void* __cdecl QuaternionFromFacingAndUp(void* out, const float* facing, const float* up);  // 0x69b600
void  __cdecl FUN_004099b0(float a);                                             // 0x4099b0

// @ 0x00625e70
void cCreatureCameraBase::AimTowardsTarget(int unused) {
  float dy = mCameraData.desiredLookAt.y - mCameraData.newPlatformPosition.y;
  float dz = mCameraData.desiredLookAt.z - mCameraData.newPlatformPosition.z;
  float dx = mCameraData.desiredLookAt.x - mCameraData.newPlatformPosition.x;
  float facing[3];
  float up[3];
  float out[4];
  up[0] = gUpX;
  up[1] = gUpY;
  up[2] = gUpZ;
  float inv = 1.0f / sqrt(dx * dx + dy * dy + dz * dz);
  facing[0] = inv * dx;
  facing[1] = inv * dy;
  facing[2] = inv * dz;
  QuaternionFromFacingAndUp(out, facing, up);
  mCameraData.newPlatformOrientation.x = out[0];
  mCameraData.newPlatformOrientation.y = out[1];
  mCameraData.newPlatformOrientation.z = out[2];
  mCameraData.newPlatformOrientation.w = out[3];
  (void)unused;
}

cVec3 QuatRotate(const cVec3& v, const cQuat& q);   // 0x0059AED0 (hidden return pointer, cdecl)

// @ 0x00625f70  damp distance / orbit angles toward their desired values (frame-rate independent)
void cCreatureCameraBase::FUN_00625f70() {
  float minDist = mMinCameraDistance;
  float* sel = &mCameraData.desiredPlayerDistance;
  if (mCameraData.desiredPlayerDistance <= minDist)
    sel = &minDist;
  float target = *sel;
  float dt = mCameraData.dt;
  mCameraData.desiredPlayerDistance = target;
  double k = exp((double)(dt / mTuning188) * -0.30103f);
  double nd = ((double)target - (double)mCameraData.currentPlayerDistance) * (1.0 - k)
              + (double)mCameraData.currentPlayerDistance;
  mCameraData.currentPlayerDistance = (float)nd;
  float dist = (float)nd;
  cVec3 up;
  up.x = gUpX;
  up.y = gUpY;
  up.z = gUpZ;
  double k2 = exp((double)(dt / mTuning180) * -0.30103f);
  double theta = (double)mCameraData.currentPlayerTheta
                 + ((double)mCameraData.desiredPlayerTheta - (double)mCameraData.currentPlayerTheta) * (1.0 - k2);
  mCameraData.currentPlayerTheta = (float)theta;
  double half = theta * 0.5f;
  cVec3 diff;
  diff.x = mCameraData.desiredLookAt.x - mCameraData.desiredPosition.x;
  diff.y = mCameraData.desiredLookAt.y - mCameraData.desiredPosition.y;
  diff.z = mCameraData.desiredLookAt.z - mCameraData.desiredPosition.z;
  float sh = (float)sin(half);
  cQuat q;
  q.x = up.x * sh;
  q.y = up.y * sh;
  q.z = up.z * sh;
  q.w = (float)cos(half);
  cVec3 r = QuatRotate(diff, q);
  float d = r.z * up.z + r.y * up.y + r.x * up.x;
  float vx = r.x - d * up.x;
  float vy = r.y - up.y * d;
  float vz = r.z - up.z * d;
  // The original rounds each of these to float in memory before the final
  // single-precision SSE combination; keep that round-trip so the compiler
  // does not carry x87 extended values into the expression.
  volatile float invf = (float)(1.0 / sqrt((double)vx * vx + ((double)vy * vy + (double)vz * vz)));
  double k3 = exp((double)(dt / mTuning184) * -0.30103f);
  double pitch = (double)mCameraData.currentPlayerPitch
                 + ((double)mCameraData.desiredPlayerPitch - (double)mCameraData.currentPlayerPitch) * (1.0 - k3);
  mCameraData.currentPlayerPitch = (float)pitch;
  volatile float syf = (float)(sin(pitch) * dist);
  volatile float cyf = (float)(cos(pitch) * dist);
  volatile float px = invf * vx;
  volatile float py = vy * invf;
  volatile float pz = vz * invf;
  volatile float cx = px * cyf;
  volatile float cyy = py * cyf;
  volatile float cz = pz * cyf;
  volatile float ox = mCameraData.desiredLookAt.x - cx;
  volatile float oy = mCameraData.desiredLookAt.y - cyy;
  volatile float oz = mCameraData.desiredLookAt.z - cz;
  volatile float ux = up.x * syf;
  volatile float uy = up.y * syf;
  volatile float uz = up.z * syf;
  mCameraData.desiredPosition.x = ox + ux;
  mCameraData.desiredPosition.y = oy + uy;
  mCameraData.desiredPosition.z = oz + uz;
}

// @ 0x00626290
void cCreatureCameraBase::ReloadTuning() {
  App::IPropertyManager* pm = PropertyManager();
  PropListPtr list;
  ReadFloat(mpTuningProps, 0x01102b20, mNearClip);
  ReadFloat(mpTuningProps, 0x01102b2f, mFarClip);
  ReadFloat(mpTuningProps, 0x00fe243b, mMinCameraPhi);
  ReadFloat(mpTuningProps, 0x00fe243f, mMaxCameraPhi);
  mMinCameraPhi *= kDegToRad;
  mMaxCameraPhi *= kDegToRad;
  ReadFloat(mpTuningProps, 0x303eb34d, mMinCameraDistance);
  ReadFloat(mpTuningProps, 0x703eb357, mMaxCameraDistance);

  if (pm->GetPropertyList(0xceadeb40, gCameraTuningGroup, &list)) {
    App::PropertyList* l = list.mpObject;
    if (l) {
      Property* p;
      if (l->GetProperty(0xb060e649, p) && p->mType == 9) {
        unsigned mode = *(unsigned*)p->GetInt();
        if (mode <= 0u)
          mCameraMode = mode;
      }
    }
    ReadFloatDeg(list.mpObject, 0xf06d1e9b, mMouseSensitivityX);
    ReadFloatDeg(list.mpObject, 0x306d1e9e, mMouseSensitivityY);
    ReadFloat(list.mpObject, 0x506d1ea0, mMouseSensitivityZ);
    ReadFloat(list.mpObject, 0x126ecc27, gTune_1521888);
    ReadFloat(list.mpObject, 0xe815bc27, gTune_152188c);
    ReadFloat(list.mpObject, 0xb5f3ddd9, gTune_1521890);
    ReadFloat(list.mpObject, 0x01a57b85, gTune_152187c);
    ReadFloat(list.mpObject, 0x01a57b91, gTune_1521880);
    ReadFloat(list.mpObject, 0x01a57b9b, gTune_1521884);
    ReadFloat(list.mpObject, 0xd03ee49b, mTuning178);
    ReadFloat(list.mpObject, 0x703ee4a1, mTuning17c);
    ReadFloat(list.mpObject, 0x503ee4a2, mTuning180);
    ReadFloat(list.mpObject, 0x303ee4a4, mTuning184);
    ReadFloat(list.mpObject, 0xf03ee4a8, mTuning188);
    ReadFloat(list.mpObject, 0xaac5a161, gTune_1521894);
    ReadFloat(list.mpObject, 0x7932c8c4, gTune_1521898);
    ReadFloat(list.mpObject, 0xf7e0935e, gTune_152189c);
  }
}

// @ 0x006268a0
void cCreatureCameraBase::CalculateCameraToWorldMatrix() {
  cTransform t;
  t.mTranslation.x = gT0;
  t.mTranslation.y = gT1;
  t.mModificationCount = 0;
  t.mTranslation.z = gT2;
  t.mFlags = 0;
  t.mScale = 1.0f;
  t.mRotation.Assign(&gMat3);
  t.RotateY(mCameraData.currentPlayerTheta);
  t.PreRotateX(-mCameraData.currentPlayerPitch);
  float z = mCameraData.desiredLookAt.z;
  float ax, ay, az;
  if (mCameraData.bTransitioning) {
    mCameraData.desiredPreTranslate.x = 0.0f;
    mCameraData.desiredPreTranslate.y = -mCameraData.currentPlayerDistance;
    mCameraData.desiredPreTranslate.z = mCameraData.desiredLookAt.z;
    float pz = mCameraData.currentPreTranslate.z * t.mScale;
    float py = mCameraData.currentPreTranslate.y * t.mScale;
    float px = mCameraData.currentPreTranslate.x * t.mScale;
    ax = (t.mRotation.zAxis.x * pz + t.mRotation.yAxis.x * py) + t.mRotation.xAxis.x * px;
    ay = (t.mRotation.zAxis.y * pz + t.mRotation.yAxis.y * py) + t.mRotation.xAxis.y * px;
    az = (t.mRotation.zAxis.z * pz + t.mRotation.yAxis.z * py) + t.mRotation.xAxis.z * px;
  } else {
    float sz = z * t.mScale;
    float sy = -(mCameraData.currentPlayerDistance * t.mScale);
    float sx = t.mScale * 0.0f;
    ax = (t.mRotation.zAxis.x * sz + t.mRotation.yAxis.x * sy) + t.mRotation.xAxis.x * sx;
    ay = (t.mRotation.zAxis.y * sz + t.mRotation.yAxis.y * sy) + t.mRotation.xAxis.y * sx;
    az = (t.mRotation.zAxis.z * sz + t.mRotation.yAxis.z * sy) + t.mRotation.xAxis.z * sx;
  }
  t.mTranslation.x = ((Depends*)((char*)this + 0x10))->mActualCameraPositionOffset.x
                     + (t.mTranslation.x + ax);
  t.mFlags |= 4;
  t.mTranslation.y = ((Depends*)((char*)this + 0x10))->mActualCameraPositionOffset.y
                     + (t.mTranslation.y + ay);
  t.mModificationCount += 2;
  t.mTranslation.z = ((Depends*)((char*)this + 0x10))->mActualCameraPositionOffset.z
                     + (t.mTranslation.z + az);
  *(cTransform*)mCameraToWorld = t;
  *(uint8_t*)((char*)this + 0x1cc) = 0;
}

// @ 0x00626b50
void cCreatureCameraBase::SetInitialCameraValues(uint32_t a, uint32_t b, uint32_t c,
                                                 const float* v) {
  // The original sets ecx = this and passes the first parameter with its sign bit flipped:
  // SetCurrentPolarCoords(-a, b, c) -- a, b, c are float bit patterns.
  union BitsToFloat { uint32_t u; float f; };
  BitsToFloat negA, fb, fc;
  negA.u = a ^ 0x80000000u;
  fb.u = b;
  fc.u = c;
  SetCurrentPolarCoords(negA.f, fb.f, fc.f);
  cTransform t;
  t.mTranslation.x = gT0;
  t.mTranslation.y = gT1;
  t.mModificationCount = 0;
  t.mTranslation.z = gT2;
  t.mFlags = 0;
  t.mScale = 1.0f;
  t.mRotation.Assign(&gMat3);
  ((Depends*)((char*)this + 0x10))->mActualCameraPositionOffset.x = gT0;
  ((Depends*)((char*)this + 0x10))->mActualCameraPositionOffset.y = gT1;
  ((Depends*)((char*)this + 0x10))->mActualCameraPositionOffset.z = gT2;
  ((Depends*)((char*)this + 0x10))->mTargetCameraPositionOffset.x = gT0;
  ((Depends*)((char*)this + 0x10))->mTargetCameraPositionOffset.y = gT1;
  ((Depends*)((char*)this + 0x10))->mTargetCameraPositionOffset.z = gT2;
  mCameraData.currentPreTranslate.x = v[0];
  mCameraData.currentPreTranslate.y = v[1];
  mCameraData.currentPreTranslate.z = v[2];
  mCameraData.desiredPreTranslate.x = 0.0f;
  mCameraData.desiredPreTranslate.y = -mCameraData.desiredPlayerDistance;
  mCameraData.desiredPreTranslate.z = mCameraData.desiredLookAt.z;
  t.RotateY(mCameraData.currentPlayerTheta);
  t.PreRotateX(-mCameraData.currentPlayerPitch);
  float fz = v[2] * t.mScale;
  float fy = v[1] * t.mScale;
  float fx = v[0] * t.mScale;
  t.mTranslation.x = ((Depends*)((char*)this + 0x10))->mActualCameraPositionOffset.x
      + (t.mTranslation.x + ((t.mRotation.zAxis.x * fz + t.mRotation.xAxis.x * fx)
                             + t.mRotation.yAxis.x * fy));
  t.mTranslation.y = ((Depends*)((char*)this + 0x10))->mActualCameraPositionOffset.y
      + (t.mTranslation.y + ((t.mRotation.zAxis.y * fz + t.mRotation.xAxis.y * fx)
                             + t.mRotation.yAxis.y * fy));
  t.mModificationCount += 2;
  t.mFlags |= 4;
  t.mTranslation.z = ((Depends*)((char*)this + 0x10))->mActualCameraPositionOffset.z
      + (t.mTranslation.z + ((t.mRotation.zAxis.z * fz + t.mRotation.yAxis.z * fy)
                             + t.mRotation.xAxis.z * fx));
  *(cTransform*)mCameraToWorld = t;
  *(uint8_t*)((char*)this + 0x1cc) = 0;
  mCameraData.bTransitioning = true;
}
