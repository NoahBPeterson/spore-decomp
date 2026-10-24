// src/game/SPEditors/SPEditorSpine.cpp -- migrated from slice(s) s005d4630, s005d1f30, s005d12c0, s005d02d0, s005cf830, s005ce9b0, s005cdd00, s005ccc90 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorSpine.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>
#include "SP/cSPEditorSpine.h"
#include <math.h>
#include <float.h>

// ---- items of slice s005ccc90 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
class cRefCounted {
 public:
  int mPad0;
  int mRef;  // +4
  void IncRef(int unused);
  void DecRef(int unused);

  char pad0[4];
};
class cTimeObj {
 public:
  PV(0) PV(1)
  virtual int GetType();  // +0x8
  int mPad4, mPad8;
  float mFloat0c;         // +0xc
  cTimeObj* mChild;       // +0x10
};
inline float Clamp(float x, float lo, float hi)
{
  __asm {
    movss xmm0, x
    maxss xmm0, lo
    minss xmm0, hi
    movss x, xmm0
  }
  return x;
}
class cInterp {
 public:
  char pad0[0x88];
  float mFloat88;  // +0x88
  float mFloat8c;  // +0x8c
  float mFloat90;  // +0x90
  float mFloat94;  // +0x94
  float mFloat98;  // +0x98
  void Interp(float a, float b, float* out1, float* out2);
};
// ---- items of slice s005ccc90 end

// ---- items of slice s005cdd00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_004a5970(void*, ...);
struct __declspec(align(16)) hkVector4_s005c_dd00 {
  float x, y, z, w;
  hkVector4_s005c_dd00() {}
  hkVector4_s005c_dd00(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};
struct hkTransform_s005c_dd00 {
  char pad[0x40];
};
class hkEntity_s005c_dd00 {
 public:
  void removeReference();
  void addCollisionListener(void* listener);
};
class hkRigidBody_s005c_dd00 : public hkEntity_s005c_dd00 {
 public:
  void setTransform(const hkTransform_s005c_dd00& t);
};
class hkWorld_s005c_dd00 {
 public:
  hkEntity_s005c_dd00* addEntity(hkEntity_s005c_dd00* e, int activation);
};
class cHandleish {
 public:
  void SetEnabled(int enabled);  // 0x005a8a80
};
class hkGenericConstraintData {
 public:
  hkGenericConstraintData();
};
class hkMemory {
 public:
  virtual void* slot0();
  virtual void* slot1();
  virtual void* slot2();
  virtual void* slot3();
  virtual void* allocate(int size, int memClass);  // vtable +0x10
};
extern hkMemory* g_hkMemory;  // 0x016e4178
class hkConstraintConstructionKit {
 public:
  char pad[0x1c];
  void begin(hkGenericConstraintData* data);
  int setPivotA(const hkVector4_s005c_dd00& v);
  int setPivotB(const hkVector4_s005c_dd00& v);
  int setLinearDofWorld(const hkVector4_s005c_dd00& v, int dof);
  void constrainLinearDof(int dof);
  void setAngularBasisABodyFrame();
  void setAngularBasisBBodyFrame();
  void constrainToAngularDof(int dof);
  void end();
};
namespace SP {
namespace EditorUtils {
float GetExactSkinRadiusFromVertebra(float scale);  // 0x004a5b70
}
}
namespace SP {
class cSPEditorSpine_s005c_dd00 {
 public:
  char pad00[0x14];
  hkWorld_s005c_dd00* mpWorld;            // +0x14
  void* mpCollisionListener;   // +0x18
  char pad1c[0x40 - 0x1c];
  hkConstraintConstructionKit* mChainConstraint;  // +0x40 (unused here)
  void* mpCursorSpring;                           // +0x44
  char pad48[0x54 - 0x48];
  float mSpineNewVertebraRelativeScale;  // +0x54
  int mSpineHavokWorldNumSolverIters;    // +0x58
  int mSpineHavokWorldSimType;           // +0x5c
  float mSpineHavokWorldSolverTau;       // +0x60
  float mSpineHavokWorldSolverDamp;      // +0x64
  float mSpineFrictionConstant;          // +0x68
  float mSpineVertebraAllowedPenetrationDepth;  // +0x6c
  float mSpineVertebraMaxMassProportion;        // +0x70
  char pad74[0x9c - 0x74];
  int mSpineField9c;                     // +0x9c
  float mSpineFieldA0;                   // +0xa0
  float mSpineFieldA4;                   // +0xa4
  float mSpineLooseLinearDamping;        // +0xa8
  float mSpineLooseAngularDamping;       // +0xac
  float mSpineTightLinearDamping;        // +0xb0
  float mSpineTightAngularDamping;       // +0xb4
  float mSpineMouseSpringDamping;        // +0xb8
  float mSpineMouseSpringElasticity;     // +0xbc
  float mSpineMouseMaxForceFactor;       // +0xc0
  char padc4[0x11c - 0xc4];
  float mVertebraHalfWidth;              // +0x11c
  char pad120[0x12c - 0x120];

  hkRigidBody_s005c_dd00* CreateVertebraBody(float scale, hkTransform_s005c_dd00* transform);  // 0x005cdd00 (SP::cSPEditorSpine::CreateVertebraBody)
  int* AddVertebraBody(int* out, float scale, hkTransform_s005c_dd00* transform);
  void LoadDynamicTuning();  // 0x005ce300 (SP::cSPEditorSpine::LoadDynamicTuning)
  void CalcVertebraPhysicsBoundingBox(float param, unsigned char* shape, float* out);  // 0x005ce680 (SP::cSPEditorSpine::CalcVertebraPhysicsBoundingBox)
};
}
namespace SP {
class cSpineHelper {
 public:
  char pad00[0xe8];
  void* mFieldE8;   // +0xe8
  void* mFieldEC;   // +0xec
  char padF0[0xf4 - 0xf0];
  cHandleish* mFieldF4;  // +0xf4
  cHandleish* mFieldF8;  // +0xf8

  void SetEnabled(int enabled);       // 005ce210
  void ReleaseE8();                   // 005ce250
  void* GetHandle(int id);            // 005ce270
};
}
// ---- items of slice s005cdd00 end

// ---- items of slice s005ce9b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct E20 {
  int a;
  int b;
  float c;
  float d;
  int e;
  E20() {}
  E20(const E20& o) : a(o.a), b(o.b), c(o.c), d(o.d), e(o.e) {}
};
}
namespace SP {
struct E20Iter {
  E20* mpNode;
  E20Iter() {}
  E20Iter(E20* p) : mpNode(p) {}
  E20& operator*() const { return *mpNode; }
  bool operator!=(const E20Iter& o) const { return mpNode != o.mpNode; }
  E20Iter& operator++() {
    ++mpNode;
    return *this;
  }
};
}
namespace SP {
struct Vec2 { float x, y; };
}
namespace SP {
struct V3 { float x, y, z; };
}
namespace SP {
struct Hit;
}
namespace SP {
struct Circle {            // 0x24-byte record of the spine "belt" outline
  uint32_t id;
  float x, y, r;
  uint32_t pad[5];
  float FindHit(const Vec2* pt, int ccw, Hit** out);   // 0x005D53E0, thiscall
};
}
namespace SP {
struct Hit {
  Circle* a;
  Circle* b;
  float x, y;
  int kind;                // 0 = tangent hop, 1 = search, 2 = finish
};
}
namespace SP {
struct CircleVec { Circle* begin; Circle* end; };
}
namespace SP {
struct OutPath {           // vector of dwords + helpers
  uint32_t* begin;
  uint32_t* end;
  void Arc(const Vec2* center, float r, const Vec2* pt, float ang);   // 0x005D5A30
  void Join(const Vec2* a, const Vec2* b);                            // 0x005D5AD0
};
}
namespace SP {
struct Curve { void Eval(Vec2* out, float t); };                      // 0x005D5050
}
namespace SP {
struct SpineNode {
  uint32_t pad0[0x13];
  float px, py;            // +0x4c, +0x50
  uint32_t pad1[(0xdc0 - 0x54) / 4];
  float param;             // +0xdc0
  uint32_t pad2;
  uint32_t flags;          // +0xdc8
};
}
namespace SP {
struct KeyHolder { uint32_t pad[0x16]; uint32_t key; };
}
namespace SP {
struct Block {
  uint32_t pad[10];
  KeyHolder* holder;       // +0x28
  int GetSymmetryIndex();  // 0x0044F220
};
}
namespace SP {
struct SpineHandle {
  uint32_t pad0[0x3a];
  SpineNode* n1;           // +0xe8
  SpineNode* n2;           // +0xec
  uint32_t pad1[(0x120 - 0xf0) / 4];
  Curve* c1;               // +0x120
  Curve* c2;               // +0x124
  Vec2* NearestParam(Vec2* res, SpineNode* o);                        // 0x005CF110
  void Extrude(Block* blk, float t, float s, int a4);                 // 0x005CF4F0
};
}
float* FUN_004a5d10(void* out, SP::SpineNode* n);
float FUN_004a5bd0(SP::SpineNode* n);
void FUN_0049d6b0(SP::Block* b, SP::V3 c, SP::V3 d, int a4, int flag, float mx);
void FUN_0069b650(SP::Vec2* out, const SP::Vec2* p, const SP::Vec2* a, const SP::Vec2* b);
char FUN_005d4ff0(const SP::Vec2* p, const SP::Vec2* q, const SP::Vec2* r);
int FUN_005d5630(SP::Vec2 a, SP::Vec2 b, SP::V3 circ, float* out4);
template <class T> inline const T& MaxRef(const T& a, const T& b) { return (b < a) ? a : b; }
template <class T> inline const T& MinRef(const T& a, const T& b) { return (a < b) ? a : b; }
// ---- items of slice s005ce9b0 end

// ---- items of slice s005d02d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void EASTL_allocator_deallocate(void* p);  // 0x00f47380
namespace SP {
struct Leg {
  char pad[0xdc0];
  float mFieldDC0;  // +0xdc0
};
}
namespace SP {
class LimbVector {
 public:
  Leg** mpBegin;
  Leg** mpEnd;
  Leg** mpCapacity;
  void* mReserved0;
  void* mReserved1;
  LimbVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~LimbVector() {
    if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  Leg* operator[](unsigned int i) const { return mpBegin[i]; }
};
}
namespace SP {
namespace EditorUtils {
void GetAllLimbs(void* manager, LimbVector* out, int flag);  // 0x004a0020
}
}
namespace SP {
namespace EditorUtils {
void* GetFirstFootBlock(void* leg);                          // 0x004a9840
}
}
namespace SP {
class cSPEditorSpine_s005d_02d0 {
 public:
  char pad00[0xe8];
  void* mpLimbs;  // +0xe8

  Leg* GetFirstLeg();   // 005d0ce0 0x005d0ce0
  Leg* GetLastLeg();    // 005d0d90 0x005d0d90
};
}
// ---- items of slice s005d02d0 end

// ---- items of slice s005d12c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Sub24 {
  int mW[5];
  Sub24(const Sub24& other);
  Sub24& operator=(const Sub24& other);
};
}
namespace SP {
struct Elem24 {
  int mA;
  float mB;
  float mC;
  float mD;
  Sub24 mSub;
  Elem24(const Elem24& other) : mA(other.mA), mB(other.mB), mC(other.mC), mD(other.mD), mSub(other.mSub) {}
};
}
namespace SP {
class cSpine75 {
 public:
  char pad00[0xc5];
  bool mFieldC5;  // +0xc5

  void SetFlag(bool enable, int unused);  // 005d1600
  void EnableBody();                      // 005d1530
  void DisableBody();                     // 005d14a0
};
}
// ---- items of slice s005d12c0 end

// ---- items of slice s005d1f30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RBNode {
  RBNode* mpNodeLeft;    // +0
  RBNode* mpNodeRight;   // +4
  RBNode* mpNodeParent;  // +8
  int mnColor;           // +0xc
};
namespace SP {
class cSpine76 {
 public:
  char pad00[0xa8];
  float mFieldA8;  // +0xa8
  float mFieldAC;  // +0xac
  char padB0[0xd4 - 0xb0];
  RBNode* mpFirst;  // +0xd4 (tree begin; sentinel is this+0xd0)

  void SetTuning(int unused);  // 005d2740
  void Refresh(int unused);    // 005d2790
  __declspec(noinline) void FUN_005d1ba0();     // 005d1ba0
  __declspec(noinline) void FUN_005d1e70();     // 005d1e70
  __declspec(noinline) void FUN_005d1f30(int);  // 005d1f30
  __declspec(noinline) void FUN_005d2480(int);  // 005d2480
};
}
namespace SP {
volatile int g_spine76Sink = 0;
}
// ---- items of slice s005d1f30 end

// @ 0x005cd670
void SpineBigStub(void* a, void* b, void* c)
{
  (void)a;
  (void)b;
  (void)c;
}








// @ 0x005cd870
void cInterp::Interp(float a, float b, float* out1, float* out2)
{
  float t = ((a + b) * 0.5f) / mFloat98;
  t = Clamp(t, 0.0f, 1.0f);
  t = (mFloat94 - mFloat90) * (1.0f - t) + mFloat90;
  *out1 = mFloat88 * t;
  *out2 = mFloat8c * t;
}








// @ 0x005cd910
float TimeObjValue(cTimeObj* obj)
{
  if (obj->GetType() != 0xe)
    return 0.0f;
  cTimeObj* child = obj->mChild;
  if (child->GetType() != 8)
    return 0.0f;
  return child->mFloat0c;
}








// @ 0x005cd9a0
void CreateVertebraShapeStub(float r)
{
  (void)r;
}








// @ 0x005cdbb0
void cRefCounted::IncRef(int unused)
{
  (void)unused;
  mRef++;
}








// @ 0x005cdbc0
void cRefCounted::DecRef(int unused)
{
  (void)unused;
  mRef--;
}








// @ 0x005cdbf0
void CreateWallBoxStub(void* a, void* b)
{
  (void)a;
  (void)b;
}







// @ 0x005cdd00
hkRigidBody_s005c_dd00* SP::cSPEditorSpine_s005c_dd00::CreateVertebraBody(float scale, hkTransform_s005c_dd00* transform)
{
  (void)scale;
  (void)transform;
  return 0;
}







// @ 0x005ce060
int* SP::cSPEditorSpine_s005c_dd00::AddVertebraBody(int* out, float scale, hkTransform_s005c_dd00* transform)
{
  out[0] = 0;
  out[1] = 0;
  out[2] = 0;
  out[3] = 0;
  out[0] = (int)CreateVertebraBody(scale, transform);
  mpWorld->addEntity((hkEntity_s005c_dd00*)out[0], 1);
  ((hkEntity_s005c_dd00*)out[0])->removeReference();
  ((hkEntity_s005c_dd00*)out[0])->addCollisionListener(mpCollisionListener);
  *(unsigned short*)((char*)out[0] + 0x96) = 0;
  return out;
}







// @ 0x005ce0c0
hkGenericConstraintData* CreateAxialConstraintData(int dof)
{
  void* mem = g_hkMemory->allocate(0x4c, 0x29);
  *(unsigned short*)((char*)mem + 4) = 0x4c;
  hkGenericConstraintData* data = new (mem) hkGenericConstraintData();
  hkConstraintConstructionKit kit;
  kit.begin(data);
  hkVector4_s005c_dd00 zeroA;
  zeroA.x = 0.0f; zeroA.y = 0.0f; zeroA.z = 0.0f; zeroA.w = 0.0f;
  kit.setPivotA(zeroA);
  hkVector4_s005c_dd00 zeroB;
  zeroB.x = 0.0f; zeroB.y = 0.0f; zeroB.z = 0.0f; zeroB.w = 0.0f;
  kit.setPivotB(zeroB);
  hkVector4_s005c_dd00 axisX;
  axisX.x = 1.0f; axisX.y = 0.0f; axisX.z = 0.0f; axisX.w = 0.0f;
  hkVector4_s005c_dd00 axisY;
  axisY.x = 0.0f; axisY.y = 1.0f; axisY.z = 0.0f; axisY.w = 0.0f;
  hkVector4_s005c_dd00 axisZ;
  axisZ.x = 0.0f; axisZ.y = 0.0f; axisZ.z = 1.0f; axisZ.w = 0.0f;
  kit.setLinearDofWorld(axisX, 0);
  kit.setLinearDofWorld(axisY, 1);
  kit.setLinearDofWorld(axisZ, 2);
  kit.constrainLinearDof(dof);
  kit.setAngularBasisABodyFrame();
  kit.setAngularBasisBBodyFrame();
  kit.constrainToAngularDof(dof);
  kit.end();
  return data;
}







// @ 0x005ce210
void SP::cSpineHelper::SetEnabled(int enabled)
{
  if (mFieldF4 != 0 && mFieldF8 != 0) {
    mFieldF4->SetEnabled(enabled);
    mFieldF8->SetEnabled(enabled);
  }
}







// @ 0x005ce250
void SP::cSpineHelper::ReleaseE8()
{
  FUN_004a5970(mFieldE8);
}







// @ 0x005ce270
void* SP::cSpineHelper::GetHandle(int id)
{
  if ((int)mFieldE8 == id)
    return mFieldF4;
  if ((int)mFieldEC == id)
    return mFieldF8;
  return 0;
}







// @ 0x005ce2a0
void NormalizeVector2(float* out, const float* in)
{
  float x = in[0];
  float len = sqrtf(x * x + in[1] * in[1] + 1e-8f);
  volatile float scale = 1.0f / len;
  out[1] = in[1] * scale;
  out[0] = x * scale;
}







// @ 0x005ce300
void SP::cSPEditorSpine::LoadDynamicTuning()
{}







// Layout of the vertebra shape buffer passed in as `shape` by the caller.
struct cVertebraShape {
  unsigned char mFlags;   // +0x00
  unsigned char mPad[3];  // +0x01
  float mCenterX;         // +0x04
  float mCenterY;         // +0x08
  float mCenterZ;         // +0x0c
  float mScale;           // +0x10
  float mRow0X;           // +0x14
  float mRow0Y;           // +0x18
  float mRow0Z;           // +0x1c
  float mRow1X;           // +0x20
  float mRow1Y;           // +0x24
  float mRow1Z;           // +0x28
  float mRow2X;           // +0x2c
  float mRow2Y;           // +0x30
  float mRow2Z;           // +0x34
};

// @ 0x005ce680
void SP::cSPEditorSpine_s005c_dd00::CalcVertebraPhysicsBoundingBox(float scale, unsigned char* shape, float* out)
{
  cVertebraShape* vs = (cVertebraShape*)shape;
  __declspec(align(16)) float offset = SP::EditorUtils::GetExactSkinRadiusFromVertebra(scale) +
                 (mVertebraHalfWidth + mVertebraHalfWidth) * mSpineVertebraMaxMassProportion * 0.25f;
  float dx = scale * -0.15993178f;
  float x = 0.0f;
  float y = 0.0f;
  float z = dx;
  if (vs->mFlags & 2) {
    x = (vs->mRow1X + vs->mRow0X) * 0.0f + vs->mRow2X * dx;
    y = (vs->mRow1Y + vs->mRow0Y) * 0.0f + vs->mRow2Y * dx;
    z = (vs->mRow1Z + vs->mRow0Z) * 0.0f + vs->mRow2Z * dx;
  }
  float m01 = vs->mScale;
  float cx = vs->mCenterX + m01 * x;
  float cy = vs->mCenterY + m01 * y;
  float cz = vs->mCenterZ + m01 * z;
  out[0] = cx - offset;
  out[1] = cy - offset;
  out[2] = cz - offset;
  out[3] = cx + offset;
  out[4] = cy + offset;
  out[5] = cz + offset;
}







// @ 0x005ce7b0
int FUN_005ce7b0(void*, float*, int, char, float*, void*)
{ return 0; }






// @ 0x005ce9b0
int __stdcall FUN_005ce9b0(SP::OutPath* out, SP::CircleVec* v, int idx, float px, float py, unsigned flag)
{
  SP::Circle* cur = v->begin + idx;
  SP::Vec2 pt;
  pt.x = px;
  pt.y = py;
  uint32_t id = cur->id;
  SP::Hit* hit;
  float ang = cur->FindHit(&pt, flag, &hit);
  int kind = hit->kind;
  for (;;) {
    if (kind == 2) {
      SP::Vec2 c;
      c.x = cur->x;
      c.y = cur->y;
      out->Arc(&c, cur->r, &pt, ang);
      return 1;
    }
    SP::Circle* next = 0;
    if (kind == 0) {
      next = hit->a;
      if (next->id == id) next = hit->b;
      SP::Vec2 c;
      c.x = cur->x;
      c.y = cur->y;
      out->Arc(&c, cur->r, &pt, ang);
      pt.x = hit->x;
      pt.y = hit->y;
    } else if (kind == 1) {
      uint32_t j = hit->b->id;
      SP::Circle* c2 = v->begin + j;
      float dx, dy;
      do {
        next = c2;
        if (j >= (uint32_t)(v->end - v->begin)) return 0;
        dx = next->x - cur->x;
        dy = next->y - cur->y;
        float dist2 = dx * dx + dy * dy;
        ++j;
        c2 = next + 1;
        if (!(cur->r > sqrtf(dist2))) break;
      } while (true);
      float r2 = next->r;
      float r1 = cur->r;
      float dist = sqrtf(dx * dx + dy * dy);
      float a = acosf(fabsf(r2 - r1) / dist);
      if (r1 < r2) a = 3.14159265f - a;
      if ((char)flag == 0) a = -a;
      float cs = cosf(a), sn = sinf(a);
      float ry = dx * sn + dy * cs;
      float rx = dx * cs - dy * sn;
      float inv = 1.0f / sqrtf(ry * ry + rx * rx + 1e-8f);
      rx = inv * rx;
      ry = inv * ry;
      SP::Vec2 q, q2;
      q.x = cur->x + rx * r1;
      q.y = cur->y + ry * r1;
      q2.x = next->x + rx * next->r;
      q2.y = next->y + ry * next->r;
      float ex = pt.x - cur->x, ey = pt.y - cur->y;
      float inv2 = 1.0f / sqrtf(ex * ex + ey * ey + 1e-8f);
      float nx = inv2 * ex, ny = inv2 * ey;
      SP::Vec2 cc;
      cc.x = cur->x;
      cc.y = cur->y;
      char c = FUN_005d4ff0(&cc, &pt, &q);
      if ((char)flag == 0) c = (c == 0);
      if (c) {
        float a2 = acosf(nx * rx + ny * ry);
        if ((char)flag == 0) a2 = -a2;
        SP::Vec2 c3;
        c3.x = cur->x;
        c3.y = cur->y;
        out->Arc(&c3, cur->r, &pt, a2);
      } else {
        q.x = pt.x;
        q.y = pt.y;
      }
      float bx = q2.x - q.x, by = q2.y - q.y;
      float best = sqrtf(bx * bx + by * by);
      SP::Vec2 bp = q2;
      for (uint32_t k = 0; k < (uint32_t)(v->end - v->begin); ++k) {
        if (k != cur->id) {
          SP::Circle* o = v->begin + k;
          SP::V3 oc;
          oc.x = o->x;
          oc.y = o->y;
          oc.z = o->r;
          float res[4];
          if (FUN_005d5630(q, q2, oc, res) == 2) {
            float vx = res[0] - q.x, vy = res[1] - q.y;
            if (vy * by + vx * bx > -1.5258789e-05f) {
              float l = sqrtf(vx * vx + vy * vy);
              if (l > 1.5258789e-05f && best > l) {
                bp.x = res[0];
                bp.y = res[1];
                best = l;
                next = o;
              }
            }
            vx = res[2] - q.x;
            vy = res[3] - q.y;
            if (vy * by + vx * bx > -1.5258789e-05f) {
              float l = sqrtf(vx * vx + vy * vy);
              if (l > 1.5258789e-05f && best > l) {
                bp.x = res[2];
                bp.y = res[3];
                best = l;
                next = o;
              }
            }
          }
        }
      }
      out->Join(&q, &bp);
      pt = bp;
    } else {
      // kind other than 0/1/2: nothing emitted, fall through to the loop guard
    }
    if ((int)(out->end - out->begin) > (int)(v->end - v->begin) * 4) return 0;
    cur = next;
    id = cur->id;
    ang = cur->FindHit(&pt, flag, &hit);
    kind = hit->kind;
  }
}






// @ 0x005cf110
SP::Vec2* SP::SpineHandle::NearestParam(Vec2* res, SpineNode* o)
{
  if (!c1 || !c2) return res;
  SP::Vec2 P;
  P.x = o->px;
  P.y = o->py;
  if ((o->flags >> 7) & 1) {
    float tmp[3];
    float* p = FUN_004a5d10(tmp, o);
    P.x = p[1];
    P.y = p[2];
  }
  float bestT = 0.0f, bestD = 1e6f;
  float t = 0.05f;
  SP::Vec2 A, B, Q;
  do {
    c1->Eval(&A, t);
    c2->Eval(&B, t);
    FUN_0069b650(&Q, &P, &A, &B);
    float d = sqrtf((Q.y - P.y) * (Q.y - P.y) + (Q.x - P.x) * (Q.x - P.x));
    if (d < bestD) {
      bestT = t;
      bestD = d;
    }
    t += 0.05f;
  } while (t < 0.99f);
  float a = bestT - 0.15f, z = 0.0f;
  float lo = MaxRef(a, z);
  float b = bestT + 0.15f, one = 1.0f;
  float hi = MinRef(b, one);
  float mid = (hi + lo) * 0.5f;
  for (;;) {
    c1->Eval(&A, mid);
    c2->Eval(&B, mid);
    FUN_0069b650(&Q, &P, &A, &B);
    float d = sqrtf((Q.y - P.y) * (Q.y - P.y) + (Q.x - P.x) * (Q.x - P.x));
    if (d <= 0.001f) break;
    if (FUN_005d4ff0(&P, &B, &A)) lo = mid;
    else hi = mid;
    if (hi - lo < 1e-5f) break;
    mid = (hi + lo) * 0.5f;
  }
  float bx = A.x - B.x, by = A.y - B.y;
  float qx = A.x - Q.x, qy = A.y - Q.y;
  res->x = (hi + lo) * 0.5f;
  res->y = sqrtf(qy * qy + qx * qx) / sqrtf(by * by + bx * bx);
  return res;
}






// @ 0x005cf4f0
void SP::SpineHandle::Extrude(Block* blk, float t, float s, int a4)
{
  SP::Vec2 A, B;
  c1->Eval(&A, t);
  c2->Eval(&B, t);
  float dx = B.x - A.x, dy = B.y - A.y;
  float qx = dx * s + A.x, qy = A.y + dy * s;
  float mx = dx * 0.5f + A.x, my = A.y + dy * 0.5f;
  if (s < 0.5f) {
    dy = -dy;
    dx = -dx;
  }
  float k = (float)fabs((double)(s - 0.5f));
  float ex = dx * k, ey = dy * k;
  float r1 = sqrtf(ex * ex + ey * ey);
  float hx = dx * 0.5f, hy = dy * 0.5f;
  float r = sqrtf(hx * hx + hy * hy);
  SP::V3 C;
  if (n1->param > t) {
    float tmp[3];
    float* p = FUN_004a5d10(tmp, n1);
    C = *(SP::V3*)p;
    r = FUN_004a5bd0(n1);
  } else if (t > n2->param) {
    float tmp[3];
    float* p = FUN_004a5d10(tmp, n2);
    C = *(SP::V3*)p;
    r = FUN_004a5bd0(n2);
  } else {
    C.x = 0.0f;
    C.y = mx;
    C.z = my;
  }
  float res;
  if (r1 < r - 1.5258789e-05f) res = sqrtf(r * r - r1 * r1);
  else res = 0.0f;
  float o = (float)blk->GetSymmetryIndex() * res;
  int flag = blk->holder->key != 0xdfad9f51;
  SP::V3 D;
  D.x = o - C.x;
  D.y = qx - C.y;
  D.z = qy - C.z;
  FUN_0049d6b0(blk, C, D, a4, flag, FLT_MAX);
}






// @ 0x005cf7a0
SP::E20Iter CopyE20(SP::E20Iter first, SP::E20Iter last, SP::E20Iter dest)
{
  SP::E20Iter currentDest(dest);
  for (; first != last; ++first, ++currentDest)
    if (&*currentDest) new ((void*)&*currentDest) SP::E20(*first);
  return currentDest;
}





// @ 0x005cf830
void SP::cSPEditorSpine::LoadStaticTuning()
{}





// @ 0x005cfde0
void FUN_005cfde0(int, int, float*, int, float*, float*, int, char)
{}




// @ 0x005d02d0
void FUN_005d02d0(int, int, float, float)
{}




// @ 0x005d07f0
void FUN_005d07f0(int)
{}




// @ 0x005d0ce0
namespace SP {
Leg* cSPEditorSpine_s005d_02d0::GetFirstLeg()
{
  LimbVector limbs;
  EditorUtils::GetAllLimbs(mpLimbs, &limbs, 1);
  Leg* best = 0;
  for (unsigned int i = 0; i < limbs.size(); ++i) {
    Leg* leg = limbs[i];
    if (EditorUtils::GetFirstFootBlock(leg) != 0) {
      if (best == 0 || leg->mFieldDC0 < best->mFieldDC0)
        best = leg;
    }
  }
  return best;
}
}  // namespace SP




// @ 0x005d0d90
namespace SP {
Leg* cSPEditorSpine_s005d_02d0::GetLastLeg()
{
  LimbVector limbs;
  EditorUtils::GetAllLimbs(mpLimbs, &limbs, 1);
  Leg* best = 0;
  for (unsigned int i = 0; i < limbs.size(); ++i) {
    Leg* leg = limbs[i];
    if (EditorUtils::GetFirstFootBlock(leg) != 0) {
      if (best == 0 || leg->mFieldDC0 > best->mFieldDC0)
        best = leg;
    }
  }
  return best;
}
}  // namespace SP




// @ 0x005d0ea0
void FUN_005d0ea0(int)
{}



// @ 0x005d12c0
namespace SP {
void RecordBlockCoordinatesSkeleton(void*, void*)
{}
}  // namespace SP



// @ 0x005d13f0
namespace SP {
Elem24* CopyElem24(Elem24* first, Elem24* last, Elem24* dest)
{
  if (first != last) {
    do {
      if (dest) {
        dest->mA = first->mA;
        dest->mB = first->mB;
        dest->mC = first->mC;
        dest->mD = first->mD;
        new ((void*)&dest->mSub) Sub24(first->mSub);
      }
      ++first;
      ++dest;
    } while (first != last);
  }
  return dest;
}
}  // namespace SP



// @ 0x005d1450
namespace SP {
Elem24* RelocateElem24Backward(Elem24* first, Elem24* last, Elem24* dest)
{
  if (last == first) return dest;
  do {
    --last;
    --dest;
    dest->mA = last->mA;
    dest->mB = last->mB;
    dest->mC = last->mC;
    dest->mD = last->mD;
    dest->mSub = last->mSub;
  } while (last != first);
  return dest;
}
}  // namespace SP



// @ 0x005d14a0
namespace SP {
void FUN_005d14a0(int)
{}
}  // namespace SP



// @ 0x005d1530
namespace SP {
void FUN_005d1530(int)
{}
}  // namespace SP



// @ 0x005d1600
namespace SP {
void cSpine75::SetFlag(bool enable, int)
{
  if (enable) {
    if (!mFieldC5) {
      EnableBody();
      mFieldC5 = true;
    }
  } else {
    if (mFieldC5) {
      DisableBody();
      mFieldC5 = false;
    }
  }
}
}  // namespace SP



// @ 0x005d1640
namespace SP {
void FUN_005d1640(int)
{}
}  // namespace SP



// @ 0x005d1780
namespace SP {
void FUN_005d1780(int)
{}
}  // namespace SP



// @ 0x005d19e0
namespace SP {
void FUN_005d19e0(int)
{}
}  // namespace SP



// @ 0x005d1ba0
namespace SP {
void FUN_005d1ba0(int)
{}
}  // namespace SP



// @ 0x005d1d40
namespace SP {
void FUN_005d1d40(int)
{}
}  // namespace SP



// @ 0x005d1e70
namespace SP {
void FUN_005d1e70(int)
{}
}  // namespace SP


// @ 0x005d1f30
namespace SP {
__declspec(noinline) void cSpine76::FUN_005d1f30(int x)
{ g_spine76Sink = x; }
}  // namespace SP


// @ 0x005d2480
namespace SP {
__declspec(noinline) void cSpine76::FUN_005d2480(int x)
{ g_spine76Sink = x; }
}  // namespace SP


// @ 0x005d25c0
void FUN_005d25c0(int)
{}

// @ 0x005d4ff0
bool CrossSideCcw(float* p1, float* p2, float* p3)
{
  float v = (p1[1] - p2[1]) * (p3[0] - p2[0]) - (p3[1] - p2[1]) * (p1[0] - p2[0]);
  if (0.0f > v) return true;
  return false;
}

// @ 0x005d5050
void FUN_005d5050(int)
{}
