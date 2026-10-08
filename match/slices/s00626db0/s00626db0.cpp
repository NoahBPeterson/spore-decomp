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


// ---- 0x00627660: camera-collision push-out (retail-layout view of the camera object) -------------
extern cVec3 gCamLocalPos;  // 0x15f65fc
extern cVec3 gCamForward;   // 0x15f6774
extern cVec3 gCamRight;     // 0x15f6720
#include <math.h>
struct cSPTransformR {
  uint16_t mFlags;
  uint16_t mModificationCount;
  cVec3 mTranslation;
  float mScale;
  cVec3 xAxis, yAxis, zAxis;
};

  // 0x15f65fc

__forceinline float Clamp(float x, float lo, float hi) {
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

// @ 0x00627660  camera-vs-ground push-out (see CamView::FUN_00627660 above)
void cCreatureCameraBase::FUN_00627660() {
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
    dot = Clamp(dot, -1.0f, 1.0f);
    float ang = (float)acos(dot) + cv->currentPlayerPitch;
    cv->currentPlayerPitch = ang;
    cv->nonPenetratingPhi = ang;
    cv->CalculateCameraToWorldMatrix();
    cv->currentPlayerPitch = oldPitch;
    return;
  }
  cv->bPenetrating = false;
}

