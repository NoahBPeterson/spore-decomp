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
  cMat33 mRotation;             // +0x00
  cVec3  mTranslation;          // +0x24
  uint32_t mModificationCount;  // +0x30
  uint32_t mFlags;              // +0x34
  float  mScale;                // +0x38
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
struct Depends { char pad[0x78]; cVec3 mActualCameraPositionOffset; };  // +0x78 within depends

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
float __cdecl FUN_00625560(uint32_t a, uint32_t b, uint32_t c);                  // 0x625560

// @ 0x00625e70
void cCreatureCameraBase::AimTowardsTarget(int unused) {
  float dy = mCameraData.desiredLookAt.y - mCameraData.newPlatformPosition.y;
  float dz = mCameraData.desiredLookAt.z - mCameraData.newPlatformPosition.z;
  float dx = mCameraData.desiredLookAt.x - mCameraData.newPlatformPosition.x;
  float f0 = dx;
  float f1 = dy;
  float f2 = dz;
  float u0 = gUpX;
  float u1 = gUpY;
  float u2 = gUpZ;
  float inv = 1.0f / sqrt(dy * dy + dz * dz + dx * dx);
  u0 = inv * dx;
  u1 = inv * dy;
  u2 = inv * dz;
  QuaternionFromFacingAndUp(&mCameraData.newPlatformOrientation, &f0, &u0);
  (void)unused;
}

// @ 0x00625f70
void cCreatureCameraBase::FUN_00625f70() {
  float distLimit = mMinCameraDistance;
  float* chosen = (mCameraData.currentPlayerDistance <= mMinCameraDistance)
                      ? &distLimit : &mCameraData.currentPlayerDistance;
  float d = *chosen;
  float rate = mCameraData.nonPenetratingPhi;
  (void)rate; (void)d;
  float f = (float)pow(10.0, (double)(mCameraData.nonPenetratingPhi / mFarClip) * -0.30103);
  mCameraData.desiredPlayerDistance = (d - mCameraData.desiredPlayerDistance) * (1.0f - f)
                                      + mCameraData.desiredPlayerDistance;
  // (transcendental x87 body; see partial.txt)
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
  FUN_00625560(a ^ 0x80000000u, b, c);
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
