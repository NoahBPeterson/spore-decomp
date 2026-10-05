// slice s005cdd00 -- SP::cSPEditorSpine vertebra body/constraint construction + spine helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include <math.h>
#include "types.h"

// ---------------------------------------------------------------------------
// Havok / engine stubs (layouts taken from the disassembly; only offsets used)
// ---------------------------------------------------------------------------
struct __declspec(align(16)) hkVector4 {
  float x, y, z, w;
  hkVector4() {}
  hkVector4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};

struct hkTransform {
  char pad[0x40];
};

struct hkMatrix3 {
  hkVector4 c0, c1, c2;
  void mul(float s);
};

class hkEntity {
 public:
  void removeReference();
  void addCollisionListener(void* listener);
};

class hkRigidBody : public hkEntity {
 public:
  void setTransform(const hkTransform& t);
};

class hkWorld {
 public:
  hkEntity* addEntity(hkEntity* e, int activation);
};

class cHandleish {
 public:
  void SetEnabled(int enabled);  // 0x005a8a80
};

struct hkRigidBodyCinfo {
  char pad[0xd0];
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
  int setPivotA(const hkVector4& v);
  int setPivotB(const hkVector4& v);
  int setLinearDofWorld(const hkVector4& v, int dof);
  void constrainLinearDof(int dof);
  void setAngularBasisABodyFrame();
  void setAngularBasisBBodyFrame();
  void constrainToAngularDof(int dof);
  void end();
};

// ---------------------------------------------------------------------------
namespace SP {

namespace EditorUtils {
float GetExactSkinRadiusFromVertebra(float scale);  // 0x004a5b70
}

class cSPEditorSpine {
 public:
  char pad00[0x14];
  hkWorld* mpWorld;            // +0x14
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

  hkRigidBody* CreateVertebraBody(float scale, hkTransform* transform);
  int* AddVertebraBody(int* out, float scale, hkTransform* transform);
  void LoadDynamicTuning();
  void CalcVertebraPhysicsBoundingBox(float param, unsigned char* shape, float* out);
};

// unnamed helper class shared by 005ce210/250/270
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

}  // namespace SP

using namespace SP;

// ---------------------------------------------------------------------------
// 005ce060 -- create a vertebra body, add it to the world, attach listener.
// ---------------------------------------------------------------------------
// @ 0x005CE060
int* cSPEditorSpine::AddVertebraBody(int* out, float scale, hkTransform* transform) {
  out[0] = 0;
  out[1] = 0;
  out[2] = 0;
  out[3] = 0;
  out[0] = (int)CreateVertebraBody(scale, transform);
  mpWorld->addEntity((hkEntity*)out[0], 1);
  ((hkEntity*)out[0])->removeReference();
  ((hkEntity*)out[0])->addCollisionListener(mpCollisionListener);
  *(unsigned short*)((char*)out[0] + 0x96) = 0;
  return out;
}

// ---------------------------------------------------------------------------
// 005ce210
// ---------------------------------------------------------------------------
// @ 0x005CE210
void cSpineHelper::SetEnabled(int enabled) {
  if (mFieldF4 != 0 && mFieldF8 != 0) {
    mFieldF4->SetEnabled(enabled);
    mFieldF8->SetEnabled(enabled);
  }
}

// @ 0x005CE250
extern "C" void FUN_004a5970(void*, ...);
void cSpineHelper::ReleaseE8() {
  FUN_004a5970(mFieldE8);
}

// @ 0x005CE270
void* cSpineHelper::GetHandle(int id) {
  if ((int)mFieldE8 == id)
    return mFieldF4;
  if ((int)mFieldEC == id)
    return mFieldF8;
  return 0;
}

// ---------------------------------------------------------------------------
// 005ce2a0 -- normalize a 2D vector (x,y), writing the unit vector to out.
// ---------------------------------------------------------------------------
// @ 0x005CE2A0
void NormalizeVector2(float* out, const float* in) {
  float x = in[0];
  float y = in[1];
  float len = sqrtf(x * x + y * y + 1e-8f);
  float scale = 1.0f / len;
  out[0] = scale * x;
  out[1] = scale * y;
}

// placeholders for the remaining (large) functions
// @ 0x005CE0C0
hkGenericConstraintData* CreateAxialConstraintData(int dof) {
  void* mem = g_hkMemory->allocate(0x4c, 0x29);
  *(unsigned short*)((char*)mem + 4) = 0x4c;
  hkGenericConstraintData* data = new (mem) hkGenericConstraintData();
  hkConstraintConstructionKit kit;
  kit.begin(data);
  hkVector4 zeroA;
  zeroA.x = 0.0f; zeroA.y = 0.0f; zeroA.z = 0.0f; zeroA.w = 0.0f;
  kit.setPivotA(zeroA);
  hkVector4 zeroB;
  zeroB.x = 0.0f; zeroB.y = 0.0f; zeroB.z = 0.0f; zeroB.w = 0.0f;
  kit.setPivotB(zeroB);
  hkVector4 axisX;
  axisX.x = 1.0f; axisX.y = 0.0f; axisX.z = 0.0f; axisX.w = 0.0f;
  hkVector4 axisY;
  axisY.x = 0.0f; axisY.y = 1.0f; axisY.z = 0.0f; axisY.w = 0.0f;
  hkVector4 axisZ;
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
// @ 0x005CDD00
// PARTIAL: full Havok rigid-body construction (hkRigidBodyCinfo setup + hkRigidBody alloc,
// two hkShape transforms, mouse-spring wiring) is not reconstructed; see partial.txt.
hkRigidBody* cSPEditorSpine::CreateVertebraBody(float scale, hkTransform* transform) {
  (void)scale;
  (void)transform;
  return 0;
}

// @ 0x005CE300
// PARTIAL: the DynamicTuning property lookups (PropertyManager + Property virtual calls and the
// mirrored tuning globals) are not reconstructed; see partial.txt.
void cSPEditorSpine::LoadDynamicTuning() {}
// @ 0x005CE680
void cSPEditorSpine::CalcVertebraPhysicsBoundingBox(float scale, unsigned char* shape, float* out) {
  float offset = SP::EditorUtils::GetExactSkinRadiusFromVertebra(scale) +
                 (mVertebraHalfWidth + mVertebraHalfWidth) * mSpineVertebraMaxMassProportion * 0.25f;
  float dx = scale * -0.15993178f;
  float x = 0.0f;
  float y = 0.0f;
  float z = dx;
  if (shape[0] & 2) {
    x = (*(float*)(shape + 0x20) + *(float*)(shape + 0x14)) * 0.0f + *(float*)(shape + 0x2c) * dx;
    y = (*(float*)(shape + 0x24) + *(float*)(shape + 0x18)) * 0.0f + *(float*)(shape + 0x30) * dx;
    z = (*(float*)(shape + 0x28) + *(float*)(shape + 0x1c)) * 0.0f + *(float*)(shape + 0x34) * dx;
  }
  float m01 = *(float*)(shape + 0x10);
  float cx = *(float*)(shape + 4) + m01 * x;
  float cy = *(float*)(shape + 8) + m01 * y;
  float cz = *(float*)(shape + 0xc) + m01 * z;
  out[0] = cx - offset;
  out[1] = cy - offset;
  out[2] = cz - offset;
  out[3] = cx + offset;
  out[4] = cy + offset;
  out[5] = cz + offset;
}
// @ 0x005CE7B0
int FUN_005ce7b0(void*, float*, int, char, float*, void*) { return 0; }
