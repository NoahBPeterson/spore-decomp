// SP::cCreatureCameraBase accessors, activation and control update (SporeEP1_RL).
// Region 0x626db0-0x627d44. Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <new>

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
void  __cdecl Matrix3_Assign(void* self, const void* src);   // 0x41cb40 (__thiscall shape)
void  __cdecl Modifier_Accumulate(void* self, const void* src); // 0x40ccb0 (__thiscall shape)
typedef void (__thiscall *Thiscall2)(void*, const void*);
void  __cdecl Eapd_sys_gui(void* p);                 // 0xc2e4e0 UTFWin::ILayoutElement::SetSerializer

// Base-class skeleton of SP::cICameraController (IUnknown32 @0, IHandlerRC @4) + RefCountVTemplate<int> @8.
struct IUnknown32S { virtual void u0(); virtual void u1(); ~IUnknown32S() {} };
struct IHandlerS { virtual void h0(); };
struct IHandlerRCS : IHandlerS { virtual void h0(); ~IHandlerRCS() {} };
struct cICameraControllerS : IUnknown32S, IHandlerRCS { ~cICameraControllerS() {} };
struct RefCountVS { virtual void r0(); int mRefCount; RefCountVS() : mRefCount(0) {} ~RefCountVS() {} };
struct Matrix3S { void Assign(const Matrix3S& o); };           // 0x41cb40
struct cCreatureCameraDependsS {                                     // size 0x78
  float avatarX;               // +0x00
  float avatarY;               // +0x04
  float avatarZ;               // +0x08
  uint32_t pad0c[6];
  float mAvatarMinZ;           // +0x24
  uint32_t pad28[(0x74 - 0x28) / 4];
  void* mAnimCreature;         // +0x74
  cCreatureCameraDependsS();                                         // 0x6281c0
  ~cCreatureCameraDependsS();                                        // 0xc2e4e0 (folded with SetSerializer)
};
struct IShared { virtual void AddRef(); virtual void Release(); };
struct AutoRefShared {
  IShared* mpObject;
  ~AutoRefShared() { if (mpObject) mpObject->Release(); }
};
struct AutoHandlerS {
  void* mpServer;              // +0x00
  void* mpHandler;             // +0x04
  void* mpIdArray;             // +0x08
  int   mnIdArrayCount;        // +0x0c
  int   mnPriority;            // +0x10
  ~AutoHandlerS() {
    if (mpServer) {
      void* s = mpServer;
      mpServer = 0;
      RemoveHandler(s, mpHandler, (void**)mpIdArray, mnIdArrayCount, mnPriority);
    }
  }
};

// View of the +0xd0 theta/pitch/distance block (overlaps the desired-position vectors).
struct CamThetaBlock {
  float currentTheta;          // +0xd0
  float currentPitch;          // +0xd4
  float currentDistance;       // +0xd8
};

// Absolute-offset view of the camera object (verified against the disassembly).
struct cCreatureCameraBase : cICameraControllerS, RefCountVS {
  cCreatureCameraDependsS mDepends;   // +0x10
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
  float desiredPlayerTheta;    // +0x124
  float desiredPlayerPitch;    // +0x128
  float desiredPlayerDistance; // +0x12c
  char  pad130[0x160-0x130];
  float mThetaMin;             // +0x160
  float mThetaMax;             // +0x164
  char  pad168[0x194-0x168];
  cTransform mCameraToWorld;   // +0x194
  bool  mTransformNeedsUpdating; // +0x1cc (1 byte)
  char  pad1cd[0x1d0-0x1cd];
  AutoHandlerS mMessageRegistration;  // +0x1d0
  char  pad1e4[0x1ec-0x1e4];
  bool  mMouseLeft;            // +0x1ec
  bool  mMouseMiddle;          // +0x1ed
  bool  mMouseRight;           // +0x1ee
  bool  mbActive;              // +0x1ef
  char  pad1f0[0x200-0x1f0];
  AutoRefShared mpShared;      // +0x200

  void GetAudioAnchorPosition(float* out);     // 0x627000
  void GetCurrentCameraPosition(float* out);   // 0x626db0
  void CalculateCameraToWorldMatrix();         // 0x6268a0
  void UpdateCamera_StandardControl(float dt); // 0x626ee0
  void Activate();                             // 0x627ca0
  void ReloadTuning();                         // 0x626290
  void InitCameraData();                       // 0x625830
  void InitCreatureData(void* pCreature);      // 0x627060
  void FUN_00627660();                         // 0x627660
  cCreatureCameraBase(IShared* pShared);       // 0x6271f0
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
static inline cVec3& desiredPositionTmp(cCreatureCameraBase* c) { return *(cVec3*)((char*)c + 0xdc); }
static inline cVec3& newPlatformVelSource(cCreatureCameraBase* c) { return *(cVec3*)((char*)c + 0x108); }

float __cdecl FUN_00625a90_ret();   // 0x625a90 (void -> runs on this)
void  __cdecl FUN_00625a90_proxy(cCreatureCameraBase* c);   // 0x625a90
void  __cdecl FUN_00625bf0_proxy(cCreatureCameraBase* c);   // 0x625bf0
void  __cdecl FUN_00625f70_proxy(cCreatureCameraBase* c);   // 0x625f70
void  __cdecl AimProxy(cCreatureCameraBase* c);             // 0x625e70
typedef void (__thiscall *Thiscall1)(void*);
typedef void (__thiscall *ThiscallBool)(void*, bool);
void  __cdecl cCreatureCameraDepends_SetLocalExtents(void* d);  // 0x628100 (__thiscall: ecx = this)


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
  float f = mDepends.mAvatarMinZ;
  float ux = gUpX, uy = gUpY, uz = gUpZ;
  out[0] = ux * f + mDepends.avatarX;
  out[1] = mDepends.avatarY + uy * f;
  out[2] = mDepends.avatarZ + uz * f;
}

// @ 0x00626db0
void cCreatureCameraBase::GetCurrentCameraPosition(float* out) {
  cSPTransformR& xf = *(cSPTransformR*)((char*)this + 0x194);
  if (*(uint8_t*)((char*)this + 0x1cc) != 0) {
    CalculateCameraToWorldMatrix();
  }
  float x = gT0, y = gT1, z = gT2;
  out[0] = x;
  out[1] = y;
  out[2] = z;
  if ((xf.mFlags & 2) != 0) {
    out[0] = (xf.zAxis.x * z + xf.yAxis.x * y) + xf.xAxis.x * x;
    out[1] = (xf.zAxis.y * z + xf.yAxis.y * y) + xf.xAxis.y * x;
    out[2] = (xf.zAxis.z * z + xf.yAxis.z * y) + xf.xAxis.z * x;
  }
  float s = xf.mScale;
  out[0] = s * out[0] + xf.mTranslation.x;
  out[1] = s * out[1] + xf.mTranslation.y;
  out[2] = out[2] * s + xf.mTranslation.z;
}

// @ 0x00626ee0
void cCreatureCameraBase::UpdateCamera_StandardControl(float dt) {
  currentPlayerTheta = dt;                 // +0x98 (mCameraData.dt)
  ((Thiscall1)FUN_00625a90_proxy)(this);
  float x = desiredLookAtV.x, y = desiredLookAtV.y, z = desiredLookAtV.z;
  desiredLookAt(this).x = x;
  desiredLookAt(this).y = y;
  desiredLookAt(this).z = z;
  desiredPositionTmp(this).x = x - gOffX;
  desiredPositionTmp(this).y = y - gOffY;
  desiredPositionTmp(this).z = z - gOffZ;
  ((Thiscall1)FUN_00625f70_proxy)(this);
  ((Thiscall1)FUN_00625bf0_proxy)(this);
  float px = desiredPositionTmp(this).x, py = desiredPositionTmp(this).y, pz = desiredPositionTmp(this).z;
  newPlatformPosition(this).x = px; platformPosition(this).x = px;
  newPlatformPosition(this).y = py; platformPosition(this).y = py;
  newPlatformPosition(this).z = pz; platformPosition(this).z = pz;
  cVec3 v = newPlatformVelSource(this);
  platformVelocity(this).x = v.x;
  platformVelocity(this).y = v.y;
  platformVelocity(this).z = v.z;
  ((ThiscallBool)AimProxy)(this, false);
  platformOrientation(this) = newPlatformOrientation(this);
}

// @ 0x00627060
void cCreatureCameraBase::InitCreatureData(void* pCreature) {
  CamThetaBlock& theta = *(CamThetaBlock*)((char*)this + 0xd0);
  float radius = gA2;
  float theta0 = gA0 * 0.017453292f;
  float pitch = gA1 * 0.017453292f;
  theta.currentTheta = 0.0f;
  float a = 0.0f;
  if (0.0f <= mThetaMin) a = mThetaMin;
  if (mThetaMax <= a) a = mThetaMax;
  theta.currentPitch = a;
  theta.currentDistance = 2.0f;
  float lo = mThetaMin;
  float hi = mThetaMax;
  mTransformNeedsUpdating = 1;
  desiredPlayerTheta = theta0;
  if (pitch <= lo) pitch = lo;
  if (hi <= pitch) pitch = hi;
  desiredPlayerPitch = pitch;
  float dist = 0.1f;
  if (radius > 0.1f) dist = radius;
  desiredPlayerDistance = dist;
  mDepends.mAnimCreature = pCreature;
  ((Thiscall1)cCreatureCameraDepends_SetLocalExtents)(&mDepends);
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
  ((Thiscall2)Matrix3_Assign)((char*)dst + 0x14, (char*)outDst + 0x14);
  ((Thiscall2)Modifier_Accumulate)(dst, src);
  return dst;
}

// The original dtor is compiler-generated (no user body); this wrapper forces the out-of-line instance.
// @ 0x006275d0
__declspec(noinline) void DestroyCam(cCreatureCameraBase* p) { p->~cCreatureCameraBase(); }

// @ 0x00627ca0
void cCreatureCameraBase::Activate() {
  if (mbActive) return;
  ReloadTuning();
  InitCameraData();
  void* ms = MessageServer();
  void* handler = (char*)this + 4;
  mMessageRegistration.mpServer = ms;
  mMessageRegistration.mpHandler = handler;
  mMessageRegistration.mpIdArray = (void*)gMsgIds;
  mMessageRegistration.mnIdArrayCount = 5;
  mMessageRegistration.mnPriority = 0;
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

extern float gQ0;  // 0x1521a70
extern float gQ1;  // 0x1521a74
extern float gQ2;  // 0x1521a78
extern float gQ3;  // 0x1521a7c
extern Matrix3S gIdentity3;  // 0x15f672c
#define U(x) (*(const uint32_t*)&(x))
#define M(T, off) (*(T*)((char*)this + (off)))

// @ 0x006271f0
cCreatureCameraBase::cCreatureCameraBase(IShared* pShared) {
  M(float, 0x154) = 0.017453292f;
  M(float, 0x158) = 0.004363323f;
  M(float, 0x15c) = 0.001f;
  M(float, 0x160) = -0.43633232f;
  M(float, 0x164) = 0.87266463f;
  M(float, 0x168) = 5.0f;
  M(float, 0x174) = 10000.0f;
  M(float, 0x16c) = 25.0f;
  M(float, 0x178) = 0.5f;
  M(float, 0x17c) = 0.5f;
  M(float, 0x180) = 0.5f;
  M(int, 0x88) = 0;
  M(int, 0x8c) = 0;
  M(int, 0x90) = 0;
  M(int, 0x94) = 0;
  M(float, 0x170) = 1.0f;
  M(float, 0x184) = 1.0f;
  M(float, 0x188) = 1.0f;
  M(float, 0x18c) = 30.0f;
  M(float, 0x190) = 30.0f;
  M(uint16_t, 0x196) = 0;
  M(uint16_t, 0x194) = 0;
  M(float, 0x198) = gT0;
  M(float, 0x19c) = gT1;
  M(float, 0x1a0) = gT2;
  M(float, 0x1a4) = 1.0f;
  ((Matrix3S*)((char*)this + 0x1a8))->Assign(gIdentity3);
  M(bool, 0x1cc) = true;
  M(int, 0x1d0) = 0;
  M(int, 0x1d4) = 0;
  M(int, 0x1d8) = 0;
  M(int, 0x1dc) = 0;
  M(int, 0x1e0) = 0;
  M(float, 0x1e4) = 0.0f;
  M(float, 0x1e8) = 0.0f;
  M(bool, 0x1ec) = false;
  M(bool, 0x1ed) = false;
  M(bool, 0x1ee) = false;
  M(bool, 0x1ef) = false;
  M(bool, 0x1f0) = true;
  M(int, 0x1f4) = 0;
  M(int, 0x1f8) = 0;
  M(float, 0x1fc) = 0.0f;
  mpShared.mpObject = pShared;
  if (pShared) pShared->AddRef();
  M(float, 0x98) = 0.0f;
  float minDist = M(float, 0x168);
  M(uint32_t, 0x9c) = U(gT0); M(uint32_t, 0xa0) = U(gT1); M(uint32_t, 0xa4) = U(gT2);
  M(uint32_t, 0xa8) = U(gT0); M(uint32_t, 0xac) = U(gT1); M(uint32_t, 0xb0) = U(gT2);
  M(uint32_t, 0xb4) = U(gQ0); M(uint32_t, 0xb8) = U(gQ1); M(uint32_t, 0xbc) = U(gQ2); M(uint32_t, 0xc0) = U(gQ3);
  M(uint32_t, 0xc4) = U(gT0); M(uint32_t, 0xc8) = U(gT1);
  uint32_t z = U(gT2);
  M(float, 0xd8) = minDist;
  M(uint32_t, 0xcc) = z;
  M(float, 0xd0) = 0.0f;
  M(float, 0xd4) = 0.0f;
  M(uint32_t, 0xdc) = U(gT0); M(uint32_t, 0xe0) = U(gT1); M(uint32_t, 0xe4) = U(gT2);
  M(uint32_t, 0xe8) = U(gT0); M(uint32_t, 0xec) = U(gT1); M(uint32_t, 0xf0) = U(gT2);
  M(float, 0xf4) = 0.0f;
  M(float, 0xf8) = 0.0f;
  M(uint32_t, 0xfc) = U(gT0); M(uint32_t, 0x100) = U(gT1); M(uint32_t, 0x104) = U(gT2);
  M(uint32_t, 0x108) = U(gT0); M(uint32_t, 0x10c) = U(gT1); M(uint32_t, 0x110) = U(gT2);
  M(uint32_t, 0x114) = U(gQ0); M(uint32_t, 0x118) = U(gQ1); M(uint32_t, 0x11c) = U(gQ2);
  uint32_t w = U(gQ3);
  M(bool, 0x134) = false;
  M(uint32_t, 0x120) = w;
  M(float, 0x124) = 0.0f;
  M(float, 0x128) = 0.0f;
  M(float, 0x12c) = 0.0f;
  M(float, 0x130) = 0.0f;
}

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

