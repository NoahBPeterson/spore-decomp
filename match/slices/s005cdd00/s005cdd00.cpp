// slice s005cdd00 -- SP::cSPEditorSpine vertebra body/constraint construction + spine helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include <math.h>
#include <string.h>
#include "types.h"

// ---------------------------------------------------------------------------
// Havok / engine stubs (layouts taken from the disassembly; only offsets used)
// ---------------------------------------------------------------------------
struct __declspec(align(16)) hkVector4 {
  float x, y, z, w;
  hkVector4() {}
  hkVector4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};

class hkTransform { public:
  char pad[0x40];
};

class hkMatrix3 { public:
  hkVector4 c0, c1, c2;
  void mul(float s);  // 0x01081bb0
};

class hkRigidBodyCinfo {
 public:
  hkRigidBodyCinfo();  // 0x01087ed0
  unsigned int m_collisionFilterInfo;  // +0x00
  void* m_shape;                       // +0x04
  unsigned char m_collisionResponse;   // +0x08
  unsigned short m_processContactCallbackDelay;  // +0x0a
  __declspec(align(16)) hkVector4 m_position;    // +0x10
  hkVector4 m_rotation;                // +0x20
  hkVector4 m_linearVelocity;          // +0x30
  hkVector4 m_angularVelocity;         // +0x40
  hkMatrix3 m_inertiaTensor;           // +0x50
  hkVector4 m_centerOfMass;            // +0x80
  float m_mass;                        // +0x90
  float m_linearDamping;               // +0x94
  float m_angularDamping;              // +0x98
  float m_friction;                    // +0x9c
  float m_restitution;                 // +0xa0
  float m_maxLinearVelocity;           // +0xa4
  float m_maxAngularVelocity;          // +0xa8
  float m_allowedPenetrationDepth;     // +0xac
  unsigned char m_motionType;          // +0xb0
  unsigned char m_rigidBodyDeactivatorType;  // +0xb1
  unsigned char m_solverDeactivation;  // +0xb2
  unsigned char m_qualityType;         // +0xb3
  unsigned char m_autoRemoveLevel;     // +0xb4
};

class hkReferencedObject {
 public:
  virtual void destroy(int dealloc);  // vtable +0
  unsigned short m_memSizeAndFlags;   // +0x04
  unsigned short m_referenceCount;    // +0x06
};

class hkShape : public hkReferencedObject {
 public:
  char pad08[0x10 - 0x08];  // +0x08
  hkShape* m_childShape;    // +0x10
};

struct hkMassProperties {
  char pad00[0x20];
  hkMatrix3 m_inertiaTensor;  // +0x20
};

class hkMotion;

class hkEntity {
 public:
  void removeReference();
  void addCollisionListener(void* listener);
  char pad00[0x58];  // the retail hkEntity data before m_motion
};

class hkMotion {
 public:
  virtual void v00();
  virtual void v04();
  virtual void v08();
  virtual void v0c();
  virtual void v10();
  virtual void v14();
  virtual void v18();
  virtual void v1c();
  virtual void v20();
  virtual void v24();
  virtual void v28();
  virtual void v2c();
  virtual void v30();
  virtual void v34();
  virtual void v38(void* out);  // vtable +0x38
  virtual void v3c(void* out);  // vtable +0x3c
};

class hkRigidBody : public hkEntity {
 public:
  hkRigidBody(const hkRigidBodyCinfo& info);  // 0x010878b0
  void setTransform(const hkTransform& t);    // 0x01087890
  void getMotionStateAndVelocities(void* out);  // 0x010871e0
  hkMotion* m_motion;        // +0x58
  char pad5c[0x64 - 0x5c];
  float mMaterialFriction;   // +0x64
};

class hkWorld {
 public:
  hkEntity* addEntity(hkEntity* e, int activation);
};

class cHandleish {
 public:
  void SetEnabled(int enabled);  // 0x005a8a80
};

void hkInertiaTensorComputer_computeShapeMassProperties(hkShape* shape, float mass,
                                                        hkMassProperties* out);  // 0x01127680
hkShape* CreateVertebraShapeStub(float scale);  // 0x005cd9a0

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
// Property system (layout from the 005ce300 disassembly: vptr at +0, type at +0x12,
// release at vtable +4, GetProperty at +0x24, manager GetPropertyList at +0x2c).
// ---------------------------------------------------------------------------
class Property;

class PropertyManager {
 public:
  virtual void p00();
  virtual void p04();
  virtual void p08();
  virtual void p0c();
  virtual void p10();
  virtual void p14();
  virtual void p18();
  virtual void p1c();
  virtual void p20();
  virtual void p24();
  virtual void p28();
  virtual bool GetPropertyList(unsigned int listHash, unsigned int owner, Property** out);  // +0x2c
};

class Property {
 public:
  virtual void q00();       // +0x00
  virtual void Release();   // +0x04
  virtual void q08();
  virtual void q0c();
  virtual void q10();
  virtual void q14();
  virtual void q18();
  virtual void q1c();
  virtual void q20();
  virtual bool GetProperty(unsigned int hash, Property** out);  // +0x24
  char pad04[0x12 - 0x04];        // +0x04
  unsigned short mType;           // +0x12
  float* GetFloat();              // 0x0041ea70
  int* GetInt();                  // 0x0041e990
};

void* FUN_0067de30();  // 0x0067de30
extern unsigned int g_spinePropertyListOwner;  // 0x01517fd4
extern float g_spineMouseSpringElasticity;     // 0x015ba0d0
extern float g_spineMouseMaxForceFactor;       // 0x015ba0d4

static inline void LoadFloatProperty(Property* list, unsigned int hash, float* dest) {
  Property* found = 0;
  if (list->GetProperty(hash, &found) && found->mType == 0x0d)
    *dest = *found->GetFloat();
}

static inline void LoadIntProperty(Property* list, unsigned int hash, int* dest) {
  Property* found = 0;
  if (list->GetProperty(hash, &found) && found->mType == 9)
    *dest = *found->GetInt();
}

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
  float mSpineMinVertebraScale;   // +0x40
  float mSpineMaxVertebraScale;   // +0x44
  char pad48[4];                  // +0x48
  float mMaxBlockScale;           // +0x4c
  char pad50[4];                  // +0x50
  float mSpineNewVertebraRelativeScale;  // +0x54
  int mSpineHavokWorldNumSolverIters;    // +0x58
  int mSpineHavokWorldSimType;           // +0x5c
  float mSpineHavokWorldSolverTau;       // +0x60
  float mSpineHavokWorldSolverDamp;      // +0x64
  float mSpineFrictionConstant;          // +0x68
  float mSpineVertebraAllowedPenetrationDepth;  // +0x6c
  float mSpineVertebraMaxMassProportion;        // +0x70
  char pad74[4];                                // +0x74
  unsigned char mSpineVertebraHavokPaddingFactor;  // +0x78
  char pad79[0x9c - 0x79];                      // +0x79
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
  float len = sqrtf(x * x + in[1] * in[1] + 1e-8f);
  volatile float scale = 1.0f / len;
  out[1] = in[1] * scale;
  out[0] = x * scale;
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
hkRigidBody* cSPEditorSpine::CreateVertebraBody(float scale, hkTransform* transform) {
  hkShape* shape = CreateVertebraShapeStub(scale);
  hkRigidBodyCinfo info;
  info.m_shape = shape;
  info.m_motionType = 1;

  float minScale = mSpineMinVertebraScale;
  float maxScale = mSpineMaxVertebraScale;
  float clamped = scale;
  if (clamped <= minScale)
    clamped = minScale;
  if (maxScale <= clamped)
    clamped = maxScale;
  float scaleFactor = ((clamped - minScale) / (maxScale - minScale)) *
                          (mSpineFrictionConstant - 1.0f) +
                      1.0f;

  hkMassProperties massProps;
  memset(&massProps, 0, sizeof(massProps));
  hkInertiaTensorComputer_computeShapeMassProperties(shape->m_childShape, 1.0f, &massProps);
  info.m_inertiaTensor = massProps.m_inertiaTensor;
  info.m_mass = scaleFactor;
  info.m_inertiaTensor.mul(mSpineVertebraAllowedPenetrationDepth * scaleFactor);

  info.m_allowedPenetrationDepth = mSpineHavokWorldSolverDamp;
  info.m_angularDamping = mSpineLooseAngularDamping;
  info.m_maxAngularVelocity = 0.0f;
  info.m_friction = mSpineLooseLinearDamping;

  void* mem = g_hkMemory->allocate(0xd0, 0x2a);
  *(unsigned short*)((char*)mem + 4) = 0xd0;
  hkRigidBody* body = new (mem) hkRigidBody(info);

  if (shape->m_memSizeAndFlags != 0) {
    shape->m_referenceCount--;
    if (shape->m_referenceCount == 0)
      shape->destroy(1);
  }

  body->mMaterialFriction = mSpineHavokWorldSolverTau;
  body->setTransform(*transform);

  if (mSpineVertebraHavokPaddingFactor != 0) {
    char buffer[0x100] = {};
    body->m_motion->v3c(buffer);
    memset(buffer + 0x14, 0, 0x1c);
    body->getMotionStateAndVelocities(buffer);
  }
  return body;
}

// @ 0x005CE300
void cSPEditorSpine::LoadDynamicTuning() {
  mMaxBlockScale = 0.9f;
  mSpineMouseSpringElasticity = 1.5f;
  mSpineMouseMaxForceFactor = 0.05f;
  mSpineLooseAngularDamping = 10.0f;
  mSpineFieldA0 = 1.0f;
  mSpineFieldA4 = 1.0f;
  mSpineTightLinearDamping = 2.0f;
  mSpineField9c = 3;
  mSpineLooseLinearDamping = 30.0f;
  mSpineTightAngularDamping = 0.5f;
  mSpineMouseSpringDamping = 30.0f;

  Property* list = 0;
  PropertyManager* manager = (PropertyManager*)FUN_0067de30();
  if (manager->GetPropertyList(0xbef6f201, g_spinePropertyListOwner, &list) && list) {
    LoadFloatProperty(list, 0x1cbb8a7, &mMaxBlockScale);
    LoadFloatProperty(list, 0x62e4dba8, &mSpineMouseSpringElasticity);
    LoadFloatProperty(list, 0x64553361, &mSpineMouseMaxForceFactor);
    LoadIntProperty(list, 0x5446ac96, &mSpineField9c);
    LoadFloatProperty(list, 0xbcbd7e27, &mSpineFieldA0);
    LoadFloatProperty(list, 0x7cb94bf4, &mSpineFieldA4);
    LoadFloatProperty(list, 0x98cef991, &mSpineLooseLinearDamping);
    LoadFloatProperty(list, 0x874a0e6e, &mSpineLooseAngularDamping);
    LoadFloatProperty(list, 0x9a54b3da, &mSpineTightLinearDamping);
    LoadFloatProperty(list, 0x3cd0684f, &mSpineTightAngularDamping);
    LoadFloatProperty(list, 0x71b632f5, &mSpineMouseSpringDamping);
  }
  if (list)
    list->Release();
  g_spineMouseSpringElasticity = mSpineMouseSpringElasticity;
  g_spineMouseMaxForceFactor = mSpineMouseMaxForceFactor;
}
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

// @ 0x005CE680
void cSPEditorSpine::CalcVertebraPhysicsBoundingBox(float scale, unsigned char* shape, float* out) {
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
// ---------------------------------------------------------------------------
// 005ce7b0 -- search the vertebra-circle list for a free point along `dir`.
// ---------------------------------------------------------------------------
struct cVertebraCircle {
  int mId;           // +0x00
  float mX;          // +0x04
  float mY;          // +0x08
  float mRadius;     // +0x0c
  char pad10[0x14];  // +0x10 .. +0x24
};

struct cVertebraCircleList {
  cVertebraCircle* mpBegin;  // +0x00
  cVertebraCircle* mpEnd;    // +0x04
};

struct cSpineOffset2 {
  char pad0[4];
  float mX;  // +0x04
  float mY;  // +0x08
};

struct float2 { float x, y; };
struct float3 { float x, y, z; };
struct float4 { float x, y, z, w; };

int FUN_005d5630(float2 origin, float2 query, float3 circle, float4* out);  // 0x005d5630

// @ 0x005CE7B0
int FUN_005ce7b0(cVertebraCircleList* list, float* dir, cSpineOffset2* offset,
                 char forward, float* outPoint, int* outId) {
  const float kEpsilon = 1.5258789e-05f;
  int count = (int)(list->mpEnd - list->mpBegin);
  int result = 0;
  if (count == 0)
    return 0;

  for (int i = 0; i < count; ++i) {
    int idx = forward ? i : count - i - 1;
    cVertebraCircle* circle = &list->mpBegin[idx];

    float2 origin;
    origin.x = offset->mX;
    origin.y = offset->mY;
    float2 query;
    query.x = dir[0] + offset->mX;
    query.y = dir[1] + offset->mY;
    float3 shape;
    shape.x = circle->mX;
    shape.y = circle->mY;
    shape.z = circle->mRadius;
    float4 hit;
    int hitCount = FUN_005d5630(origin, query, shape, &hit);
    result = count;
    if (hitCount != 2)
      continue;

    float dot = dir[0] * (hit.x - circle->mX) + dir[1] * (hit.y - circle->mY);
    float px, py;
    if (dot <= 0.0f) {
      px = hit.z;
      py = hit.w;
    } else {
      px = hit.x;
      py = hit.y;
    }

    int n = (int)(list->mpEnd - list->mpBegin);
    int j = 0;
    for (; j < n; ++j) {
      if (j == idx)
        continue;
      cVertebraCircle* other = &list->mpBegin[j];
      float dx = px - other->mX;
      float dy = py - other->mY;
      if (sqrtf(dx * dx + dy * dy) < other->mRadius - kEpsilon)
        break;
    }
    if (j == n) {
      outPoint[0] = px;
      outPoint[1] = py;
      int id = circle->mId;
      *outId = id;
      return (id & 0xFFFFFF00) | 1;
    }
  }
  return result & 0xFFFFFF00;
}
