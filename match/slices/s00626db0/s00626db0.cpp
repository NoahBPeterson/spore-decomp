// SP::cCreatureCameraBase accessors, activation and control update (SporeEP1_RL).
// Region 0x626db0-0x627d44. Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

static inline void** Vt(void* p) { return *(void***)p; }

struct cVec3 { float x, y, z; };
struct cQuat { float x, y, z, w; };
struct cMat33 { cVec3 xAxis, yAxis, zAxis; };
struct cTransform {
  cMat33 mRotation;             // +0x00 (0x24)
  cVec3  mTranslation;          // +0x24 (0xc -> 0x30)
  float  mScale;                // +0x30
  uint32_t mFlags;              // +0x34
};                              // size 0x38

extern float gUpX;   // 0x15f66f8
extern float gUpY;   // 0x15f66fc
extern float gUpZ;   // 0x15f6700
extern float gT0;    // 0x15f65fc
extern float gT1;    // 0x15f6600
extern float gT2;    // 0x15f6604
extern float gOffX;  // 0x15f6774
extern float gOffY;  // 0x15f6778
extern float gOffZ;  // 0x15f677c
extern float gA0;    // 0x1521894
extern float gA1;    // 0x1521898
extern float gA2;    // 0x152189c
extern uint32_t gMsgIds[];  // 0x13fdfa0

void* __cdecl MessageServer();                       // 0x67dcc0
void  __cdecl RemoveHandler(void* server, void* handler, void** ids, int n, int prio);  // 0x571db0
void  __cdecl Matrix3_Assign(void* dst, const void* src);   // 0x41cb40
void  __cdecl Modifier_Accumulate(void* t, const void* src); // 0x40ccb0
void  __cdecl Eapd_sys_gui(void* p);                 // 0xc2e4e0 UTFWin::ILayoutElement::SetSerializer

// Absolute-offset view of the camera object (verified against the disassembly).
struct cCreatureCameraBase {
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
  cTransform mCameraToWorld;   // +0x194
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
  cCreatureCameraBase();                       // 0x6271f0
  ~cCreatureCameraBase();                      // 0x6275d0
};

// helper-access into the camera-data block (mCameraData at +0x98 in the real layout):
//   theta +0x98, pitch +0x9c, distance +0xa0, desiredLookAt +0xe8, newPlatformPosition +0xfc
static inline cVec3& desiredLookAt(cCreatureCameraBase* c) { return *(cVec3*)((char*)c + 0xe8); }
static inline cVec3& newPlatformPosition(cCreatureCameraBase* c) { return *(cVec3*)((char*)c + 0xfc); }
static inline cVec3& desiredPosition(cCreatureCameraBase* c) { return *(cVec3*)((char*)c + 0xd0); }
static inline cVec3& platformPosition(cCreatureCameraBase* c) { return *(cVec3*)((char*)c + 0x9c); }
static inline cVec3& platformVelocity(cCreatureCameraBase* c) { return *(cVec3*)((char*)c + 0xa8); }
static inline cVec3& currentPreTranslate(cCreatureCameraBase* c) { return *(cVec3*)((char*)c + 0x138); }
static inline cQuat& platformOrientation(cCreatureCameraBase* c) { return *(cQuat*)((char*)c + 0xb4); }
static inline cQuat& newPlatformOrientation(cCreatureCameraBase* c) { return *(cQuat*)((char*)c + 0x114); }

float __cdecl FUN_00625a90_ret();   // 0x625a90 (void -> runs on this)
void  __cdecl FUN_00625a90_proxy(cCreatureCameraBase* c);   // 0x625a90
void  __cdecl FUN_00625bf0_proxy(cCreatureCameraBase* c);   // 0x625bf0
void  __cdecl cCreatureCameraDepends_SetLocalExtents(void* d);  // 0x6252c0-ish

// @ 0x00627000
void cCreatureCameraBase::GetAudioAnchorPosition(float* out) {
  float f = mAvatarMinZ;
  float ux = gUpX, uy = gUpY, uz = gUpZ;
  out[0] = ux * f + avatarX;
  out[1] = avatarY + uy * f;
  out[2] = avatarZ + uz * f;
}

// @ 0x00626db0
void cCreatureCameraBase::GetCurrentCameraPosition(float* out) {
  if (*(uint8_t*)((char*)this + 0x150) != 0) {
    // CalculateCameraToWorldMatrix(this)
    extern void CalcCam(cCreatureCameraBase*);
    CalcCam(this);
  }
  float x = gT0, y = gT1, z = gT2;
  out[0] = x;
  out[1] = y;
  out[2] = z;
  if ((mCameraToWorld.mFlags & 2) != 0) {
    cMat33& m = mCameraToWorld.mRotation;
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
void cCreatureCameraBase::UpdateCamera_StandardControl(float dt) {
  currentPlayerTheta = dt;                 // +0x98 (mCameraData.dt)
  FUN_00625a90_proxy(this);
  desiredLookAtV.x = avatarX;
  desiredLookAtV.y = avatarY;
  desiredLookAtV.z = avatarZ;
  desiredPositionV.x = desiredLookAtV.x - gOffX;
  desiredPositionV.y = desiredLookAtV.y - gOffY;
  desiredPositionV.z = desiredLookAtV.z - gOffZ;
  extern void FUN_00625f70_proxy(cCreatureCameraBase*);
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
  extern void AimProxy(cCreatureCameraBase*);
  AimProxy(this);
  platformOrientation(this) = newPlatformOrientation(this);
}

// @ 0x00627060
void cCreatureCameraBase::InitCreatureData(void* pCreature) {
  float f0 = gA0;
  float f1 = gA1 * 0.017453292f;
  float f2 = gA2 * 0.017453292f;
  currentPlayerTheta = 0.0f;
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
void* __cdecl translateTransform(void* dst, void* src, void* outDst) {
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

// @ 0x006275d0
cCreatureCameraBase::~cCreatureCameraBase() {
  if (mpShared) ((void(__thiscall*)(void*))Vt(mpShared)[1])(mpShared);
  if (mpServer) {
    void* s = mpServer;
    mpServer = 0;
    RemoveHandler(s, mpHandler, (void**)mpIdArray, mnIdArrayCount, mnPriority);
  }
  Eapd_sys_gui((char*)this + 0x10);
}

// @ 0x00627ca0
void cCreatureCameraBase::Activate() {
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

// @ 0x006271f0  ctor (skeleton; see partial.txt)
cCreatureCameraBase::cCreatureCameraBase() {}

// @ 0x00627660  (skeleton; see partial.txt)
void cCreatureCameraBase::FUN_00627660() {}
