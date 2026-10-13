// src/game/SPEditors/SPCreatureCameraBase.cpp -- migrated from slice(s) s00627d50, s00626db0, s00625e70, s00624fb0, s00623f90 by tools/migrate/rewrite.py
// Object file: SPEditors/SPCreatureCameraBase.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCreatureCameraBase.h"
#include "EA/Messaging/AutoHandler.h"
#include "EA/UTFWinExtras/WinXHTML.h"
#include "SP/cCreatureCameraDepends.h"
#include "SP/cICameraController.h"
#include "cSPUILayout.h"
#include "EA/Messaging/Server.h"
#include "cSPVector3.h"
#include "SP/cAnimatingCreature.h"
#include "cSPBoundingBox.h"
#include "cSPQuaternion.h"
#include "SP/tAvatarData.h"
#include <new>
#include <string.h>
#include <math.h>
#include "EA/Variant.h"
#include "SP/cDirectPropertyList.h"
#include "cSPTransform.h"
#include "EA/IO/FileStream.h"
#include "SP/cSPPlayModeAnimation.h"
#include "SP/cSPPlayModeSubModeAction.h"
#include "SP/cSPEditorAnimatedCreatureManager.h"
#include "SP/cSPPlayMode.h"
#include "SP/cSPPlayModeUI.h"
#include "SP/cTexturePreload.h"
#include <float.h>
#include <intrin.h>

// ---- items of slice s00623f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 { float x, y, z; Vector3() {} Vector3(float a, float b, float c) : x(a), y(b), z(c) {} };
static inline Vector3 operator*(const Vector3& v, float s) { return Vector3(v.x * s, v.y * s, v.z * s); }
namespace EA {
namespace Messaging {
void __cdecl RemoveHandler(Server* srv, void* handler, void* ids, int count, int prio);
}
}
struct IWinMgr {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4();
    virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9();
    virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14();
    virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
    virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24();
    virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29();
    virtual void p30(); virtual void p31(); virtual void p32();
    virtual void* GetInputCapture();   // +0x84
};
struct AssetBrowserT { char pad[0x1c]; bool mbBusy; };
IWinMgr* __cdecl WindowManager();
AssetBrowserT* __cdecl AssetBrowser();
// ---- items of slice s00623f90 end

// ---- items of slice s00624fb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}
struct cSPVector3_s0062_4fb0 {
    float x, y, z;
};
struct Vector3Copy {   // Math::Vector3 with a user copy ctor (per-field copy, movss)
    float x, y, z;
    Vector3Copy() {}
    Vector3Copy(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3Copy(const Vector3Copy& v) : x(v.x), y(v.y), z(v.z) {}
};
static inline Vector3Copy NegateVecC(const Vector3Copy& v)
{
    Vector3Copy r(v);
    r.x = -r.x;
    r.y = -r.y;
    r.z = -r.z;
    return r;
}
struct cSPQuaternion_s0062_4fb0 {
    float x, y, z, w;
};
struct cSPBoundingBox_s0062_4fb0 {
    cSPVector3_s0062_4fb0 mMin;
    cSPVector3_s0062_4fb0 mMax;
};
extern const cSPVector3_s0062_4fb0 kAvatarCameraOffset_s0062_4fb0;   // 0x15f6774
extern const cSPVector3_s0062_4fb0 kAvatarUp_s0062_4fb0;             // 0x15f66f8
namespace SP {
struct tAvatarData_s0062_4fb0 {
    cSPVector3_s0062_4fb0 mPosition;       // +0x00
    cSPQuaternion_s0062_4fb0 mOrientaion;  // +0x0c
    cSPBoundingBox_s0062_4fb0 mLocalExtents;   // +0x1c
    cSPVector3_s0062_4fb0 mVelocity;       // +0x34
    Vector3Copy mDestination;   // +0x40
    cSPVector3_s0062_4fb0 mWASDDirection;  // +0x4c
    bool mbWASD;
    bool mbWASDTurning;
};
}
namespace SP {
struct cAnimatingCreature_s0062_4fb0 {
    int pad0;
    Vector3Copy mPos;   // +4
};
}
namespace SP {
class cCreatureCameraDepends_s0062_4fb0 {
public:
    tAvatarData_s0062_4fb0 mAvatar;                       // +0x00
    cSPVector3_s0062_4fb0 mTargetCameraPositionOffset;    // +0x5c
    cSPVector3_s0062_4fb0 mActualCameraPositionOffset;    // +0x68
    cAnimatingCreature_s0062_4fb0* mAnimCreature;         // +0x74
    void InitAvatarData();                     // 0x6256a0
    void FUN_006280d0(Vector3Copy v, int flag); // slice s00627d50
    void UpdateOffsets(float dt);              // 0x625750
};
}
namespace SP {
struct IMessageServer {
    PV4 PV
    virtual void PostMessage(unsigned a, unsigned b, int c);   // +0x14
};
}
namespace SP {
IMessageServer* __cdecl MessageServer();
}
extern const cSPVector3 kZeroVector;           // 0x15f65fc
extern const cSPQuaternion kIdentityQuat;      // 0x1521a70
extern const float kHalfLifeTime;              // 0x1521884
extern const float kVelocityRate;              // 0x1521880
extern const float kVelocityAccel;             // 0x152187c
extern const float kHalfTurn;                  // 0x15f6770
// ---- items of slice s00624fb0 end

// ---- items of slice s00625e70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gCameraTuningGroup;           // 0x01521b5c
extern const float kDegToRad;                 // 0x013fdec8 (0.017453292)
extern float gTune_1521888, gTune_152188c, gTune_1521890, gTune_152187c, gTune_1521880,
    gTune_1521884, gTune_1521894, gTune_1521898, gTune_152189c;
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
}
namespace App {
class IPropertyManager {
 public:
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10();
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList*& result);  // +0x2c
};
}
App::IPropertyManager* PropertyManager();     // 0x0067de30
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
void* __cdecl QuaternionFromFacingAndUp(void* out, const float* facing, const float* up);  // 0x69b600
extern float gUpX;    // 0x15f66f8
extern float gUpY;    // 0x15f66fc
extern float gUpZ;    // 0x15f6700
extern float gT0;     // 0x15f65fc
extern float gT1;     // 0x15f6600
extern float gT2;     // 0x15f6604
extern char  gMat3;   // 0x15f672c
// ---- items of slice s00625e70 end

// ---- items of slice s00626db0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gOffX;  // 0x15f6774
extern float gOffY;  // 0x15f6778
extern float gOffZ;  // 0x15f677c
extern uint32_t gMsgIds[];  // 0x13fdfa0
static inline void** Vt(void* p) { return *(void***)p; }
struct cMat33_s0062_6db0 { cVec3 xAxis, yAxis, zAxis; };
struct cTransform_s0062_6db0 {
  cMat33_s0062_6db0 mRotation;             // +0x00 (0x24)
  cVec3  mTranslation;          // +0x24 (0xc -> 0x30)
  float  mScale;                // +0x30
  uint32_t mFlags;              // +0x34
};                              // size 0x38
void* __cdecl MessageServer();                       // 0x67dcc0
void  __cdecl Matrix3_Assign(void* dst, const void* src);   // 0x41cb40
void  __cdecl Modifier_Accumulate(void* t, const void* src); // 0x40ccb0
struct cCreatureCameraBase_s0062_6db0 {
  char  pad00[0x04];
  char  pad04[0x0c];
  float avatarX;               // +0x10
  float avatarY;               // +0x14
  float avatarZ;               // +0x18
  char  pad1c[0x18];
  float mAvatarMinZ;           // +0x34
  char  pad38[0x50];
  int   mCameraInputState;     // +0x88
  char  pad8c[0x98-0x8c];
  float currentPlayerTheta;    // +0x98
  char  pad9c[0xc4-0x9c];
  cVec3 desiredLookAtV;        // +0xc4
  cVec3 desiredPositionV;      // +0xd0
  cVec3 newPlatformPos;        // +0xdc
  cVec3 newPlatformVel;        // +0xe8
  cQuat newPlatformOri;        // +0xf4
  cQuat currentOri;            // +0x104
  cQuat newOri2;               // +0x114
  char  pad124[0x194-0x124];
  cTransform_s0062_6db0 mCameraToWorld;   // +0x194
  char  pad1cc[0x1d0-0x1cc];
  void* mpServer;              // +0x1d0
  void* mpHandler;             // +0x1d4
  void* mpIdArray;             // +0x1d8
  int   mnIdArrayCount;        // +0x1dc
  int   mnPriority;            // +0x1e0
  char  pad1e4[0x1ec-0x1e4];
  bool  mMouseLeft;            // +0x1ec
  bool  mMouseMiddle;          // +0x1ed
  bool  mMouseRight;           // +0x1ee
  bool  mbActive;              // +0x1ef
  char  pad1f0[0x200-0x1f0];
  void* mpShared;              // +0x200

  void GetAudioAnchorPosition(float* out);     // 0x627000
  void GetCurrentCameraPosition(float* out);   // 0x626db0
  void UpdateCamera_StandardControl(float dt); // 0x626ee0
  void Activate();                             // 0x627ca0
  void ReloadTuning();                         // 0x626290
  void InitCameraData();                       // 0x625830
  void InitCreatureData(void* pCreature);      // 0x627060
  void FUN_00627660();                         // 0x627660
  cCreatureCameraBase_s0062_6db0();                       // 0x6271f0
  ~cCreatureCameraBase_s0062_6db0();                      // 0x6275d0
};
static inline cVec3& desiredLookAt(cCreatureCameraBase_s0062_6db0* c) { return *(cVec3*)((char*)c + 0xe8); }
static inline cVec3& platformPosition(cCreatureCameraBase_s0062_6db0* c) { return *(cVec3*)((char*)c + 0x9c); }
static inline cVec3& platformVelocity(cCreatureCameraBase_s0062_6db0* c) { return *(cVec3*)((char*)c + 0xa8); }
static inline cQuat& platformOrientation(cCreatureCameraBase_s0062_6db0* c) { return *(cQuat*)((char*)c + 0xb4); }
static inline cQuat& newPlatformOrientation(cCreatureCameraBase_s0062_6db0* c) { return *(cQuat*)((char*)c + 0x114); }
void  __cdecl FUN_00625a90_proxy(cCreatureCameraBase_s0062_6db0* c);   // 0x625a90
void  __cdecl FUN_00625bf0_proxy(cCreatureCameraBase_s0062_6db0* c);   // 0x625bf0
void  __cdecl cCreatureCameraDepends_SetLocalExtents(void* d);  // 0x6252c0-ish
extern cVec3 gCamLocalPos;  // 0x15f65fc
extern cVec3 gCamForward;   // 0x15f6774
extern cVec3 gCamRight;     // 0x15f6720
struct cSPTransformR {
  uint16_t mFlags;
  uint16_t mModificationCount;
  cVec3 mTranslation;
  float mScale;
  cVec3 xAxis, yAxis, zAxis;
};
__forceinline float Clamp_s0062_6db0(float x, float lo, float hi) {
  __asm {
    movss xmm0, x
    maxss xmm0, lo
    minss xmm0, hi
    movss x, xmm0
  }
  return x;
}
static __forceinline void RotateDir(const cSPTransformR& t, float& x, float& y, float& z) {
  if (t.mFlags & 2) {
    float rx = (t.zAxis.x * z + t.yAxis.x * y) + t.xAxis.x * x;
    float ry = (t.zAxis.y * z + t.yAxis.y * y) + t.xAxis.y * x;
    float rz = (t.zAxis.z * z + t.yAxis.z * y) + t.xAxis.z * x;
    x = rx; y = ry; z = rz;
  }
}
struct CamView {
  char  pad00[0xd4];
  float currentPlayerPitch;     // +0xd4
  char  padd8[0xe8 - 0xd8];
  cVec3 desiredLookAt;          // +0xe8
  char  padf4[0x130 - 0xf4];
  float nonPenetratingPhi;      // +0x130
  bool  bPenetrating;           // +0x134
  char  pad135[0x170 - 0x135];
  float mNearClip;              // +0x170
  char  pad174[0x18c - 0x174];
  float mFieldOfViewX;          // +0x18c
  float mFieldOfViewY;          // +0x190
  cSPTransformR mCameraToWorld;  // +0x194
  char  pad1c[0x1f4 - 0x194 - sizeof(cSPTransformR)];
  void* mpQueryFn;              // +0x1f4
  void* mpQueryCtx;             // +0x1f8
  float mLastQuery;             // +0x1fc

  float QueryClearance(const cVec3* p);       // 0x625600
  void CalculateCameraToWorldMatrix();        // 0x6268a0
};
extern float gA0;    // 0x1521894
extern float gA1;    // 0x1521898
extern float gA2;    // 0x152189c
// ---- items of slice s00626db0 end

// ---- items of slice s00627d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gCameraTurnRate;   // 0x15219dc
extern float kZoomRate;   // 0x13fdfb4 = 30.30303
extern float kZoomScale;  // 0x13f9324 = 0.015
struct cSPVector3_s0062_7d50 {
    float x, y, z;
};
struct cSPQuaternion_s0062_7d50 {
    float x, y, z, w;
};
struct cSPBoundingBox_s0062_7d50 {
    cSPVector3_s0062_7d50 mMin;
    cSPVector3_s0062_7d50 mMax;
};
namespace SP {
struct tAvatarData_s0062_7d50 {
    Vector3Copy mPosition;      // +0x00
    cSPQuaternion_s0062_7d50 mOrientaion;  // +0x0c
    cSPBoundingBox_s0062_7d50 mLocalExtents;   // +0x1c
    cSPVector3_s0062_7d50 mVelocity;       // +0x34
    Vector3Copy mDestination;   // +0x40
    cSPVector3_s0062_7d50 mWASDDirection;  // +0x4c
    bool mbWASD;
    bool mbWASDTurning;
};
}
namespace SP {
struct cAnimatingCreature_s0062_7d50 {
    int pad0;
    Vector3Copy mPos;      // +4
    char pad1[0x3c - 0x10];
    float mScale;          // +0x3c
    char pad2[0x17c - 0x40];
    int** mpIndexPtr;      // +0x17c
};
}
namespace SP {
class cCreatureCameraDepends_s0062_7d50 {
public:
    tAvatarData_s0062_7d50 mAvatar;                       // +0x00
    cSPVector3_s0062_7d50 mTargetCameraPositionOffset;    // +0x5c
    cSPVector3_s0062_7d50 mActualCameraPositionOffset;    // +0x68
    cAnimatingCreature_s0062_7d50* mAnimCreature;         // +0x74
    cCreatureCameraDepends_s0062_7d50();                  // 0x6281c0
    void SetTargetOffset(Vector3Copy v, bool snap);   // 0x6280d0
    void SetLocalExtents();                    // 0x628100
    void UpdateOffsets(float dt);              // 0x625750
    void OnKeyUp_SendMessage(int key, int unused);    // 0x628230
    void OnKeyDown_SendMessage(int key, int unused);  // 0x628340
};
}
namespace SP {
class cICameraController_s0062_7d50 { public: virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); };
}
namespace SP {
class IRef2_s0062_7d50 { public: virtual void r0(); virtual void r1(); };
}
namespace SP {
struct tCameraData_s0062_7d50 {
    float dt;                                   // +0x00
    cSPVector3_s0062_7d50 platformPosition;                // +0x04
    cSPVector3_s0062_7d50 platformVelocity;                // +0x10
    cSPQuaternion_s0062_7d50 platformOrientation;          // +0x1c
    cSPVector3_s0062_7d50 avatarPosition;                  // +0x2c
    float currentPlayerTheta;                   // +0x38
    float currentPlayerPitch;                   // +0x3c
    float currentPlayerDistance;                // +0x40
    cSPVector3_s0062_7d50 desiredPosition;                 // +0x44
    cSPVector3_s0062_7d50 desiredLookAt;                   // +0x50
    float mDesiredLookAtXOffset;                // +0x5c
    float mDesiredLookAtYOffset;                // +0x60
    cSPVector3_s0062_7d50 newPlatformPosition;             // +0x64
    cSPVector3_s0062_7d50 newPlatformVelocity;             // +0x70
    cSPQuaternion_s0062_7d50 newPlatformOrientation;       // +0x7c
    float desiredPlayerTheta;                   // +0x8c
    float desiredPlayerPitch;                   // +0x90
    float desiredPlayerDistance;                // +0x94
    float nonPenetratingPhi;                    // +0x98
    bool bPenetrating;                          // +0x9c
    cSPVector3_s0062_7d50 currentPreTranslate;             // +0xa0
    cSPVector3_s0062_7d50 desiredPreTranslate;             // +0xac
    bool bTransitioning;                        // +0xb8
};
}
namespace SP {
struct ICameraHelper {   // object passed to Update (field-of-view / projection owner)
    float GetFovBase();                         // 0x7c40a0
    float GetFovAspect();                       // 0x7c40e0
    void SetViewMatrix(void* pMatrix);          // 0x7c4d00
    void SetNearClip(float f);                  // 0x7c4ba0
    void SetFarClip(float f);                   // 0x7c4bc0
};
}
namespace SP {
class cCreatureCameraBase_s0062_7d50 : public cICameraController_s0062_7d50, public IRef2_s0062_7d50 {
public:
    int padA[2];
    cCreatureCameraDepends_s0062_7d50 mDepends;            // +0x10
    int mCameraInputState;                      // +0x88
    int mCameraState;                           // +0x8c
    int mCameraMode;                            // +0x90
    int mDesiredCameraMode;                     // +0x94
    tCameraData_s0062_7d50 mCameraData;                    // +0x98
    float mMouseSensitivityX;                   // +0x154
    float mMouseSensitivityY;                   // +0x158
    float mMouseSensitivityZ;                   // +0x15c
    float mMinCameraPhi;                        // +0x160
    float mMaxCameraPhi;                        // +0x164
    float mMinCameraDistance;                   // +0x168
    float mMaxCameraDistance;                   // +0x16c
    float mNearClip;                            // +0x170
    float mFarClip;                             // +0x174
    char padC[0x18c - 0x178];
    float mFieldOfViewX;                        // +0x18c
    float mFieldOfViewY;                        // +0x190
    char mCameraToWorld[0x38];                  // +0x194

    void UpdateCamera(float dt);                // 0x627d50
    void Update(unsigned ticks, ICameraHelper* pHelper);   // 0x627eb0
    void NormalizeTheta();                      // 0x6252c0
    void UpdateCamera_StandardControl(float dt);// 0x626ee0
    static void CalculateCameraToWorldMatrix(); // 0x6268a0
    void FUN_00627660();  // 0x00627660 (SP::cCreatureCameraBase::FUN_00627660)
};
}
// ---- items of slice s00627d50 end

// @ 0x00624eb0
bool SP::cCreatureCameraBase::Shutdown()
{
    Deactivate();
    return true;
}








// @ 0x00624ec0
void SP::cCreatureCameraBase::Deactivate()
{
    if (mbActive) {
        mMouseLeftButton = false;
        mMouseMiddleButton = false;
        mMouseRightButton = false;
        EA::Messaging::Server* pServer = mMessageRegistration.mpServer;
        if (pServer) {
            mMessageRegistration.mpServer = 0;
            EA::Messaging::RemoveHandler(pServer, mMessageRegistration.mpHandler, mMessageRegistration.mpIdArray,
                                         mMessageRegistration.mnIdArrayCount, mMessageRegistration.mnPriority);
        }
        mbActive = false;
    }
}








// @ 0x00624f20
bool SP::cCreatureCameraBase::OnKeyDown(unsigned int a, unsigned int b)
{
    if (mbEnabled) {
        void* r = WindowManager()->GetInputCapture();
        AssetBrowserT* ab = AssetBrowser();
        if (!r && !ab->mbBusy)
            mDepends.OnKeyDown_SendMessage(a, b);
    }
    return false;
}








// @ 0x00624f70
bool SP::cCreatureCameraBase::OnKeyUp(unsigned int a, unsigned int b)
{
    if (mbEnabled)
        mDepends.OnKeyUp_SendMessage(a, b);
    return false;
}








// @ 0x00624f90
void SP::cCreatureCameraBase::OnFocusChange(bool v)
{
    if (!v)
        mCameraInputState = (SP::cCreatureCameraBase::eCameraInputState)(0);
}







// @ 0x00624fb0
bool SP::cCreatureCameraBase::OnMouseUp(unsigned int button, float x, float y, unsigned int state)
{
    if (!mbEnabled)
        return true;
    switch (button) {
    case 1000:
        mMouseLeftButton = false;
        break;
    case 0x3e9:
        mMouseMiddleButton = false;
        break;
    case 0x3ea:
        mMouseRightButton = false;
        break;
    }
    mMouseX = x;
    mMouseY = y;
    return false;
}




// @ 0x00625010
bool SP::cCreatureCameraBase::OnMouseMove(float x, float y, unsigned int state)
{
    float oldX = mMouseX;
    float oldY = mMouseY;
    mMouseX = x;
    mMouseY = y;
    if ((mMouseRightButton || mMouseMiddleButton) && !mMouseLeftButton) {
        float dx = x - oldX;
        float dy = y - oldY;
        float yaw = -(mMouseSensitivityX * Clamp(dx, -20.0f, 20.0f));
        float pitch = mMouseSensitivityY * Clamp(dy, -20.0f, 20.0f);
        if (yaw < 0.0f)
            mCameraState = (SP::cCreatureCameraBase::eCameraInputState)(1);
        else if (yaw > 0.0f)
            mCameraState = (SP::cCreatureCameraBase::eCameraInputState)(2);
        else if (pitch > 0.0f)
            mCameraState = (SP::cCreatureCameraBase::eCameraInputState)(6);
        else if (pitch < 0.0f)
            mCameraState = (SP::cCreatureCameraBase::eCameraInputState)(7);
        else
            mCameraState = (SP::cCreatureCameraBase::eCameraInputState)(0);
        mCameraData.desiredPlayerTheta += yaw;
        if (dy < 0.0f && mCameraData.bPenetrating && mCameraData.nonPenetratingPhi > 0.0f)
            pitch = 0.0f;
        mCameraData.desiredPlayerPitch = Clamp(mCameraData.desiredPlayerPitch + pitch, mMinCameraPhi, mMaxCameraPhi);
        MessageServer()->PostMessage(0x52f180, 0x1c, 0);
    }
    return false;
}




// @ 0x006251f0
bool SP::cCreatureCameraBase::OnMouseWheel(int delta, float x, float y, unsigned int state)
{
    if (!mbEnabled)
        return true;
    if (state == 0) {
        if (delta > 0)
            mCameraState = (SP::cCreatureCameraBase::eCameraInputState)(4);
        else
            mCameraState = (SP::cCreatureCameraBase::eCameraInputState)(((delta >= 0) - 1) & 5);
        mCameraData.desiredPlayerDistance = (1.0f - (float)delta * mMouseSensitivityZ) * mCameraData.desiredPlayerDistance;
        MessageServer()->PostMessage(0x52f180, 0x1d, 0);
    }
    return false;
}




// @ 0x00625270
void SP::cCreatureCameraBase::Zoom(float f)
{
    mCameraData.desiredPlayerDistance = (f + 1.0f) * mCameraData.desiredPlayerDistance;
}




// @ 0x006252a0
void SP::cCreatureCameraBase::RotateLeftRight(float f)
{
    mCameraData.desiredPlayerTheta = f + mCameraData.desiredPlayerTheta;
}




// @ 0x006252c0
#include <math.h>
void SP::cCreatureCameraBase::NormalizeTheta()
{
    float t = mCameraData.desiredPlayerTheta;
    float c = mCameraData.currentPlayerTheta;
    if (fabsf(t - c) < 1.52587890625e-05f) {
        if (kHalfTurn < c && kHalfTurn < t) {
            c = c - kHalfTurn;
            mCameraData.desiredPlayerTheta = t - kHalfTurn;
            mCameraData.currentPlayerTheta = c;
            return;
        }
        if (c < -kHalfTurn && t < -kHalfTurn) {
            c = c + kHalfTurn;
            mCameraData.desiredPlayerTheta = t + kHalfTurn;
            mCameraData.currentPlayerTheta = c;
        }
    }
}




// @ 0x006254f0
bool SP::cCreatureCameraBase::OnMouseDown(unsigned int button, float x, float y, unsigned int state)
{
    if (!mbEnabled)
        return true;
    switch (button) {
    case 1000:
        mMouseLeftButton = true;
        break;
    case 0x3e9:
        mMouseMiddleButton = true;
        break;
    case 0x3ea:
        mMouseRightButton = true;
        break;
    }
    mMouseX = x;
    mMouseY = y;
    if (mMouseLeftButton)
        mDesiredCameraMode = (SP::cCreatureCameraBase::eCameraMode)(0);
    return true;
}




// @ 0x006256a0
namespace SP {
void cCreatureCameraDepends_s0062_4fb0::InitAvatarData()
{
    mAvatar.mPosition.x = 0.0f;
    mAvatar.mPosition.y = 0.0f;
    mAvatar.mPosition.z = 0.0f;
    Vector3Copy facing = NegateVecC(*(const Vector3Copy*)&kAvatarCameraOffset_s0062_4fb0);
    cSPQuaternion_s0062_4fb0 q;
    extern cSPQuaternion_s0062_4fb0* __cdecl QuaternionFromFacingAndUp(cSPQuaternion_s0062_4fb0* out, const Vector3Copy* facing, const cSPVector3_s0062_4fb0* up);
    mAvatar.mOrientaion = *QuaternionFromFacingAndUp(&q, &facing, &kAvatarUp_s0062_4fb0);
    mAvatar.mDestination = Vector3Copy(0.0f, 0.0f, 0.0f);
}
}  // namespace SP




// @ 0x00625830
void SP::cCreatureCameraBase::InitCameraData()
{
    mCameraData.newPlatformPosition = kZeroVector;
    mCameraData.newPlatformVelocity = kZeroVector;
    mCameraData.newPlatformOrientation = kIdentityQuat;
    mCameraData.currentPreTranslate = kZeroVector;
    mCameraData.desiredPreTranslate = kZeroVector;
    SP::cCreatureCameraDepends* pDep = &mDepends;
    pDep->InitAvatarData();
    if (!pDep->mAnimCreature) {
        pDep->mActualCameraPositionOffset = kZeroVector;
        pDep->mTargetCameraPositionOffset = kZeroVector;
    }
    mCameraData.platformPosition.x = pDep->mAvatar.mPosition.x - kAvatarCameraOffset_s0062_4fb0.x;
    mCameraData.platformPosition.y = pDep->mAvatar.mPosition.y - kAvatarCameraOffset_s0062_4fb0.y;
    mCameraData.platformPosition.z = pDep->mAvatar.mPosition.z - kAvatarCameraOffset_s0062_4fb0.z;
    mCameraData.platformOrientation = pDep->mAvatar.mOrientaion;
    mCameraData.platformVelocity = kZeroVector;
    float h = pDep->mAvatar.mLocalExtents.mMax.z;
    mCameraData.avatarPosition.x = pDep->mAvatar.mPosition.x + h * kAvatarUp_s0062_4fb0.x;
    mCameraData.avatarPosition.y = pDep->mAvatar.mPosition.y + h * kAvatarUp_s0062_4fb0.y;
    mCameraData.avatarPosition.z = pDep->mAvatar.mPosition.z + h * kAvatarUp_s0062_4fb0.z;
    mCameraData.desiredLookAt = mCameraData.avatarPosition;
    mCameraData.mDesiredLookAtYOffset = 0.0f;
    mCameraData.mDesiredLookAtXOffset = 0.0f;
    mCameraData.desiredPosition.x = mCameraData.avatarPosition.x - kAvatarCameraOffset_s0062_4fb0.x;
    mCameraData.desiredPosition.y = mCameraData.avatarPosition.y - kAvatarCameraOffset_s0062_4fb0.y;
    mCameraData.desiredPosition.z = mCameraData.avatarPosition.z - kAvatarCameraOffset_s0062_4fb0.z;
}




// @ 0x00625a90
void SP::cCreatureCameraBase::UpdateDesiredLookAt()
{
    float d = mDepends.mAvatar.mLocalExtents.mMax.z * 0.5f;
    float e = d * 0.25f + d;
    float ax = kAvatarUp_s0062_4fb0.x * e + mDepends.mAvatar.mPosition.x;
    float ay = mDepends.mAvatar.mPosition.y + kAvatarUp_s0062_4fb0.y * e;
    float az = mDepends.mAvatar.mPosition.z + kAvatarUp_s0062_4fb0.z * e;
    float t = (mCameraData.currentPlayerDistance - mMinCameraDistance) / (mMaxCameraDistance - mMinCameraDistance);
    t = Clamp(t, 0.0f, 1.0f);
    mCameraData.avatarPosition.x = ((mDepends.mAvatar.mPosition.x + kAvatarUp_s0062_4fb0.x * d) - ax) * t + ax;
    mCameraData.avatarPosition.y = ((mDepends.mAvatar.mPosition.y + kAvatarUp_s0062_4fb0.y * d) - ay) * t + ay;
    mCameraData.avatarPosition.z = ((mDepends.mAvatar.mPosition.z + kAvatarUp_s0062_4fb0.z * d) - az) * t + az;
}




// @ 0x00625bf0
#include <math.h>
void SP::cCreatureCameraBase::EndPositionUpdate()
{
    float f = (float)exp((double)(mCameraData.dt / kHalfLifeTime) * (double)-0.30103f);
    mCameraData.newPlatformVelocity.x = mCameraData.platformVelocity.x * f;
    mCameraData.newPlatformVelocity.y = mCameraData.platformVelocity.y * f;
    mCameraData.newPlatformVelocity.z = mCameraData.platformVelocity.z * f;
    if (sqrtf(mCameraData.newPlatformVelocity.x * mCameraData.newPlatformVelocity.x +
              mCameraData.newPlatformVelocity.y * mCameraData.newPlatformVelocity.y +
              mCameraData.newPlatformVelocity.z * mCameraData.newPlatformVelocity.z) < 0.01f) {
        mCameraData.newPlatformVelocity = kZeroVector;
    }
    float dx = mCameraData.desiredPosition.x - mCameraData.platformPosition.x;
    float dy = mCameraData.desiredPosition.y - mCameraData.platformPosition.y;
    float dz = mCameraData.desiredPosition.z - mCameraData.platformPosition.z;
    if (0.01f < sqrtf(dz * dz + dy * dy + dx * dx)) {
        float inv = 1.0f / kVelocityRate;
        float maxDelta = kVelocityAccel * mCameraData.dt;
        float vz = dz * inv - mCameraData.newPlatformVelocity.z;
        float vx = inv * dx - mCameraData.newPlatformVelocity.x;
        float vy = dy * inv - mCameraData.newPlatformVelocity.y;
        float lenSq = vz * vz + vy * vy + vx * vx;
        if (maxDelta * maxDelta < lenSq) {
            float s = maxDelta / sqrtf(lenSq);
            vx = vx * s;
            vy = vy * s;
            vz = s * vz;
        }
        mCameraData.newPlatformVelocity.x = vx + mCameraData.newPlatformVelocity.x;
        mCameraData.newPlatformVelocity.y = vy + mCameraData.newPlatformVelocity.y;
        mCameraData.newPlatformVelocity.z = vz + mCameraData.newPlatformVelocity.z;
    }
    float dt = mCameraData.dt;
    mCameraData.newPlatformPosition.x = mCameraData.platformPosition.x + dt * mCameraData.newPlatformVelocity.x;
    mCameraData.newPlatformPosition.y = mCameraData.platformPosition.y + mCameraData.newPlatformVelocity.y * dt;
    mCameraData.newPlatformPosition.z = mCameraData.platformPosition.z + mCameraData.newPlatformVelocity.z * dt;
}



// @ 0x00625e70
void SP::cCreatureCameraBase::AimTowardsTarget(bool unused)
{
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



// @ 0x00626290
void cCreatureCameraBase::ReloadTuning()
{
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
void SP::cCreatureCameraBase::CalculateCameraToWorldMatrix()
{
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
  *(cTransform*)((char *)&mCameraToWorld) = t;
  *(uint8_t*)((char*)this + 0x1cc) = 0;
}


// @ 0x00626db0
void cCreatureCameraBase_s0062_6db0::GetCurrentCameraPosition(float* out)
{
  if (*(uint8_t*)((char*)this + 0x150) != 0) {
    // CalculateCameraToWorldMatrix(this)
    extern void CalcCam(cCreatureCameraBase_s0062_6db0*);
    CalcCam(this);
  }
  float x = gT0, y = gT1, z = gT2;
  out[0] = x;
  out[1] = y;
  out[2] = z;
  if ((mCameraToWorld.mFlags & 2) != 0) {
    cMat33_s0062_6db0& m = mCameraToWorld.mRotation;
    out[0] = (m.zAxis.x * z + m.yAxis.x * y) + m.xAxis.x * x;
    out[1] = (m.zAxis.y * z + m.yAxis.y * y) + m.xAxis.y * x;
    out[2] = (m.zAxis.z * z + m.yAxis.z * y) + m.xAxis.z * x;
  }
  float s = mCameraToWorld.mScale;
  out[0] = s * out[0] + mCameraToWorld.mTranslation.x;
  out[1] = s * out[1] + mCameraToWorld.mTranslation.y;
  out[2] = out[2] * s + mCameraToWorld.mTranslation.z;
}


// @ 0x00626ee0
void cCreatureCameraBase_s0062_6db0::UpdateCamera_StandardControl(float dt)
{
  currentPlayerTheta = dt;                 // +0x98 (mCameraData.dt)
  FUN_00625a90_proxy(this);
  desiredLookAtV.x = avatarX;
  desiredLookAtV.y = avatarY;
  desiredLookAtV.z = avatarZ;
  desiredPositionV.x = desiredLookAtV.x - gOffX;
  desiredPositionV.y = desiredLookAtV.y - gOffY;
  desiredPositionV.z = desiredLookAtV.z - gOffZ;
  extern void FUN_00625f70_proxy(cCreatureCameraBase_s0062_6db0*);
  FUN_00625f70_proxy(this);
  FUN_00625bf0_proxy(this);
  float x = desiredPositionV.x, y = desiredPositionV.y, z = desiredPositionV.z;
  newPlatformPos.x = x; platformPosition(this).x = x;
  newPlatformPos.y = y; platformPosition(this).y = y;
  newPlatformPos.z = z; platformPosition(this).z = z;
  cVec3 v = newPlatformVel;
  platformVelocity(this).x = v.x;
  platformVelocity(this).y = v.y;
  platformVelocity(this).z = v.z;
  extern void AimProxy(cCreatureCameraBase_s0062_6db0*);
  AimProxy(this);
  platformOrientation(this) = newPlatformOrientation(this);
}


// @ 0x00627000
void cCreatureCameraBase_s0062_6db0::GetAudioAnchorPosition(float* out)
{
  float f = mAvatarMinZ;
  float ux = gUpX, uy = gUpY, uz = gUpZ;
  out[0] = ux * f + avatarX;
  out[1] = avatarY + uy * f;
  out[2] = avatarZ + uz * f;
}


// @ 0x00627060
void SP::cCreatureCameraBase::InitCreatureData(SP::cAnimatingCreature * pCreature)
{
  float f0 = gA0;
  float f1 = gA1 * 0.017453292f;
  float f2 = gA2 * 0.017453292f;
  mCameraData.dt = 0.0f;
  float a = 0.0f;
  if (0.0f <= *(float*)((char*)this + 0x160)) a = *(float*)((char*)this + 0x160);
  if (*(float*)((char*)this + 0x164) <= a) a = *(float*)((char*)this + 0x164);
  *(float*)((char*)this + 0x9c) = a;       // currentPlayerPitch
  *(float*)((char*)this + 0xa0) = 2.0f;    // currentPlayerDistance
  float lo = *(float*)((char*)this + 0x160);
  float hi = *(float*)((char*)this + 0x164);
  *(uint8_t*)((char*)this + 0x1cc) = 1;    // mTransformNeedsUpdating
  *(float*)((char*)this + 0x124) = f1;     // desiredPlayerTheta
  if (f2 <= lo) f2 = lo;
  if (hi <= f2) f2 = hi;
  *(float*)((char*)this + 0x128) = f2;     // desiredPlayerPitch
  float dist = 0.1f;
  if (f0 > 0.1f) dist = f0;
  *(float*)((char*)this + 0x12c) = dist;   // desiredPlayerDistance
  *(void**)((char*)this + 0x1b0) = pCreature;  // mDepends.mAnimCreature
  cCreatureCameraDepends_SetLocalExtents((char*)this + 0x10);
  InitCameraData();
}


// @ 0x006271a0
void* __cdecl translateTransform(void* dst, void* src, void* outDst)
{
  *(uint16_t*)dst = *(uint16_t*)outDst;
  *(uint16_t*)((char*)dst + 2) = *(uint16_t*)((char*)outDst + 2);
  *(uint32_t*)((char*)dst + 4) = *(uint32_t*)((char*)outDst + 4);
  *(uint32_t*)((char*)dst + 8) = *(uint32_t*)((char*)outDst + 8);
  *(uint32_t*)((char*)dst + 0xc) = *(uint32_t*)((char*)outDst + 0xc);
  *(uint32_t*)((char*)dst + 0x10) = *(uint32_t*)((char*)outDst + 0x10);
  Matrix3_Assign((char*)dst + 0x14, (char*)outDst + 0x14);
  Modifier_Accumulate(dst, src);
  return dst;
}


// @ 0x00627660
void cCreatureCameraBase_s0062_6db0::FUN_00627660()
{
  CamView* cv = (CamView*)this;
  cSPTransformR& t = cv->mCameraToWorld;
  float lx = gCamLocalPos.x, ly = gCamLocalPos.y, lz = gCamLocalPos.z;
  RotateDir(t, lx, ly, lz);
  float s = t.mScale;
  cVec3 pos;
  pos.x = s * lx + t.mTranslation.x;
  pos.y = t.mTranslation.y + ly * s;
  pos.z = t.mTranslation.z + lz * s;
  float fovX = cv->mFieldOfViewX;
  float fovY = cv->mFieldOfViewY;
  float fx = gCamForward.x, fy = gCamForward.y, fz = gCamForward.z;
  RotateDir(t, fx, fy, fz);
  float s1 = t.mScale;
  cVec3 fwd; fwd.x = s1 * fx; fwd.y = fy * s1; fwd.z = fz * s1;
  float rx = gCamRight.x, ry = gCamRight.y, rz = gCamRight.z;
  RotateDir(t, rx, ry, rz);
  float s2 = t.mScale;
  cVec3 rgt; rgt.x = s2 * rx; rgt.y = ry * s2; rgt.z = rz * s2;
  float near_ = cv->mNearClip;
  float halfW = (float)(tan(fovX) * near_);
  cVec3 tgt;
  tgt.x = near_ * fwd.x + pos.x;
  tgt.y = fwd.y * near_ + pos.y;
  tgt.z = fwd.z * near_ + pos.z;
  cVec3 off;
  off.x = rgt.x * halfW;
  off.y = rgt.y * halfW;
  off.z = rgt.z * halfW;
  cVec3 c1, c2;
  c1.x = off.x + tgt.x; c1.y = off.y + tgt.y; c1.z = off.z + tgt.z;
  c2.x = tgt.x - off.x; c2.y = tgt.y - off.y; c2.z = tgt.z - off.z;
  float r0 = cv->QueryClearance(&pos);
  float r1 = cv->QueryClearance(&tgt);
  if (r1 < 0.0f) r1 = 0.0f;
  float r2 = cv->QueryClearance(&c1);
  if (r2 < 0.0f) r2 = 0.0f;
  float r3 = cv->QueryClearance(&c2);
  if (r3 < 0.0f) r3 = 0.0f;
  const float* pa = (r3 > r2) ? &r3 : &r2;
  const float* pb = (r1 > r0) ? &r1 : &r0;
  const float* pm = pb;
  if (*pa > *pb) pm = pa;
  float h2 = (float)(tan(fovY) * cv->mNearClip + *pm);
  if (pos.z < h2) {
    cv->bPenetrating = true;
    t.mFlags |= 4;
    t.mModificationCount += 1;
    cVec3 np; np.x = pos.x; np.y = pos.y; np.z = h2;
    t.mTranslation = np;
    float oldPitch = cv->currentPlayerPitch;
    float dx1 = cv->desiredLookAt.x - pos.x;
    float dy1 = cv->desiredLookAt.y - pos.y;
    float dz1 = cv->desiredLookAt.z - pos.z;
    float inv1 = 1.0f / sqrtf(dx1 * dx1 + (dy1 * dy1 + dz1 * dz1));
    float dz2 = cv->desiredLookAt.z - h2;
    float dy2 = cv->desiredLookAt.y - pos.y;
    float dx2 = cv->desiredLookAt.x - pos.x;
    float inv2 = 1.0f / sqrtf(dx2 * dx2 + (dy2 * dy2 + dz2 * dz2));
    float dot = (dz2 * inv2) * (dz1 * inv1) + (dy2 * inv2) * (dy1 * inv1) + (inv2 * dx2) * (inv1 * dx1);
    dot = Clamp_s0062_6db0(dot, -1.0f, 1.0f);
    float ang = (float)acos(dot) + cv->currentPlayerPitch;
    cv->currentPlayerPitch = ang;
    cv->nonPenetratingPhi = ang;
    cv->CalculateCameraToWorldMatrix();
    cv->currentPlayerPitch = oldPitch;
    return;
  }
  cv->bPenetrating = false;
}


// @ 0x00627ca0
void cCreatureCameraBase_s0062_6db0::Activate()
{
  if (mbActive) return;
  ReloadTuning();
  InitCameraData();
  void* ms = MessageServer();
  void* handler = (char*)this + 4;
  mpServer = ms;
  mpHandler = handler;
  mpIdArray = (void*)gMsgIds;
  mnIdArrayCount = 5;
  mnPriority = 0;
  if (ms != 0 && handler != 0) {
    for (uint32_t i = 0; i < 0x14; i += 4) {
      ((void(__thiscall*)(void*, void*, uint32_t))Vt(ms)[9])
          (ms, handler, *(uint32_t*)((char*)gMsgIds + i));
    }
  }
  mMouseLeft = false;
  mMouseMiddle = false;
  mMouseRight = false;
  mCameraInputState = 0;
  mbActive = true;
}

// @ 0x00627d50
namespace SP {
void cCreatureCameraBase_s0062_7d50::UpdateCamera(float dt)
{
    static float sRotateRate = gCameraTurnRate;
    switch (mCameraInputState) {
    case 1:
        mCameraData.desiredPlayerTheta = mCameraData.desiredPlayerTheta - sRotateRate * dt;
        break;
    case 2:
        mCameraData.desiredPlayerTheta = sRotateRate * dt + mCameraData.desiredPlayerTheta;
        break;
    case 4:
        {
            float z = dt * kZoomRate;
            z = z * kZoomScale;
            mCameraData.desiredPlayerDistance = (1.0f - z) * mCameraData.desiredPlayerDistance;
        }
        break;
    case 5:
        {
            float z = dt * kZoomRate;
            z = z * kZoomScale;
            mCameraData.desiredPlayerDistance = (z + 1.0f) * mCameraData.desiredPlayerDistance;
        }
        break;
    }
    float d = Clamp(mCameraData.desiredPlayerDistance, mMinCameraDistance, mMaxCameraDistance);
    int mode = mCameraMode;
    mCameraData.desiredPlayerDistance = d;
    if (mode == 0)
        UpdateCamera_StandardControl(dt);
}
}  // namespace SP

// @ 0x00627eb0
namespace SP {
void cCreatureCameraBase_s0062_7d50::Update(unsigned ticks, ICameraHelper* pHelper)
{
    float dt = (float)ticks * 0.001f;
    float a = pHelper->GetFovBase();
    float b = pHelper->GetFovAspect();
    mFieldOfViewX = b * a * 0.017453292f;
    mFieldOfViewY = pHelper->GetFovBase() * 0.017453292f;
    cCreatureCameraDepends_s0062_7d50* pDep = &mDepends;
    pDep->UpdateOffsets(dt);
    if (pDep->mAnimCreature)
        pDep->mAvatar.mPosition = pDep->mAnimCreature->mPos;
    if (mCameraData.bTransitioning) {
        float t = Clamp(dt, 0.01f, 0.1f);
        mCameraData.currentPreTranslate.y = (mCameraData.desiredPreTranslate.y - mCameraData.currentPreTranslate.y) * t * 3.0f + mCameraData.currentPreTranslate.y;
        mCameraData.currentPreTranslate.z = (mCameraData.desiredPreTranslate.z - mCameraData.currentPreTranslate.z) * t * 3.0f + mCameraData.currentPreTranslate.z;
        mCameraData.currentPreTranslate.x = mCameraData.currentPreTranslate.x + (mCameraData.desiredPreTranslate.x - mCameraData.currentPreTranslate.x) * t * 3.0f;
        float dx = mCameraData.desiredPreTranslate.x - mCameraData.currentPreTranslate.x;
        float dy = mCameraData.desiredPreTranslate.y - mCameraData.currentPreTranslate.y;
        float dz = mCameraData.desiredPreTranslate.z - mCameraData.currentPreTranslate.z;
        if (sqrtf(dz * dz + dy * dy + dx * dx) < 0.001f)
            mCameraData.bTransitioning = false;
    }
    UpdateCamera(dt);
    mCameraData.nonPenetratingPhi = mCameraData.currentPlayerPitch;
    NormalizeTheta();
    CalculateCameraToWorldMatrix();
    FUN_00627660();
    pHelper->SetViewMatrix(mCameraToWorld);
    pHelper->SetNearClip(mNearClip);
    pHelper->SetFarClip(mFarClip);
}
}  // namespace SP

// @ 0x006280d0
namespace SP {
void cCreatureCameraDepends_s0062_7d50::SetTargetOffset(Vector3Copy v, bool snap)
{
    mTargetCameraPositionOffset = (const cSPVector3_s0062_7d50&)v;
    if (snap)
        mActualCameraPositionOffset = (const cSPVector3_s0062_7d50&)v;
}
}  // namespace SP
