// slice s005d02d0 -- SP::cSPEditorSpine: leg queries, vertebra sync (0x5d02d0),
// Update (0x5d07f0) and the constructor (0x5d0ea0).  Retail offsets taken from the disasm;
// fields are laid out by hand because the generated header does not match the retail layout.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

extern void EASTL_allocator_deallocate(void* p);  // 0x00f47380

// ---------------------------------------------------------------------------
// data globals (retail addresses)
extern float g_1485720;   // 0x01485720  _HK_REAL_ONE
extern float g_1485378;   // 0x01485378  _HK_REAL_ZERO
extern float g_15180c0;   // 0x015180c0
extern float g_15180d0;   // 0x015180d0  vertebra half width
extern float g_15ba0d0;   // 0x015ba0d0  temp linear error recovery velocity
extern float g_15ba0d4;   // 0x015ba0d4  temp exponential error recovery velocity
extern float g_15ba104;   // 0x015ba104
extern float g_13f893c;   // 0x013f893c
extern float g_13f89c0;   // 0x013f89c0  -2/3 (exponential damping constant)
extern float g_13f8934;   // 0x013f8934  1.5
extern float g_13f1f0c;   // 0x013f1f0c  1/60
extern float g_13f6bf8;   // 0x013f6bf8  0.033333335
extern float g_13f4fd0;   // 0x013f4fd0  4294967296.0f (int->uint wrap)
extern float g_13f9428;   // 0x013f9428  0.001
extern float g_13ebca0;   // 0x013ebca0  0.0001
extern void* g_15180ac;   // 0x015180ac
extern void* g_13f1ab0;   // 0x013f1ab0  ??_7cILayer@@6B@
extern void* g_13f89d4;   // 0x013f89d4
extern void* g_13f89c4;   // 0x013f89c4
extern void* g_13f89a4;   // 0x013f89a4
extern void* g_16e4178;   // 0x016e4178  hkMemory::s_instance

// ---------------------------------------------------------------------------
// calling-convention helpers
typedef void (__thiscall* VFn0)(void* self);
typedef void (__thiscall* VFn1)(void* self, void* arg);
typedef void* (__thiscall* VAlloc)(void* self, int size, int type);
#define VSLOT(obj, off) (((void**)(*(void**)(obj)))[(off) / 4])

namespace SP {

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };

struct Leg {
  char pad[0xdc0];
  float mFieldDC0;  // +0xdc0
};

// A 3-pointer growable vector whose heap buffer carries an ownership word just before the
// first element (the original frees it only when that word is non-zero).
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

namespace EditorUtils {
void GetAllLimbs(void* manager, LimbVector* out, int flag);  // 0x004a0020
void* GetFirstFootBlock(void* leg);                          // 0x004a9840
}

// ---- eastl red-black map node ----
struct RbNode {
  RbNode* mpRight;   // +0x00
  RbNode* mpLeft;    // +0x04
  RbNode* mpParent;  // +0x08
  int     color;     // +0x0c
  void*   key;       // +0x10  (cSPEditorBlock*)
  void*   val0;      // +0x14  (cSPEditorVertebraInfo first field: entity)
};
void* FUN_00921580(void* n);   // eastl::RBTreeIncrement

// ---- spherical vertebra info: transform pointer at +0x58 ----
struct Xf {
  char pad0[0x40];
  Vec4 pos;                 // +0x40
  char pad50[0x80 - 0x50];
  float src[4];             // +0x80
};
struct VertebraInfo {
  char pad0[0x58];
  Xf*  xf;                  // +0x58
};

// ---- editor block ----
struct Block {
  char  pad0[0x48];
  Vec3  pos;                // +0x48
  char  pad54[0x60 - 0x54];
  float m60[9];             // +0x60
  char  pad84[0xa8 - 0x84];
  float m[9];               // +0xa8
  char  padcc[0x340 - 0xcc];
  void** limbBegin;         // +0x340
  void** limbEnd;           // +0x344
  char  pad348[0xdc8 - 0x348];
  unsigned flags;           // +0xdc8
  void FUN_00448e90(const Vec3& p, char b);      // SetPosition
  void FUN_00449420(const float* m, char b);     // SetOrientation
};

// ---- hkWorld / entity / limb helpers ----
struct HkWorld {
  void FUN_010840e0(void* cinfo, int pragma);        // hkWorld ctor
  void FUN_01082a90(float dt);                       // stepDeltaTime
  void FUN_01086f80(void* f, int a, int b, int c);   // setCollisionFilter
  void* FUN_01082ee0(void* e, int act);              // addEntity
};
struct Entity {
  char pad0[0x58];
  void* shape;                                       // +0x58
  void FUN_01088ae0();                               // activate
  void FUN_01087520(int a, int b, int c);            // setMotionType
  void FUN_01087890(void* xf);                       // setTransform
};
struct LimbStructure {
  void FUN_004890e0(int v);                           // 0x004890e0
  void FUN_00489ae0();                                // FixAllJoints
};
struct HkWorldCinfo {
  void FUN_010880e0();                                // ctor
  void FUN_010881d0(float size);                      // setBroadPhaseWorldSize
};
struct HkRigidBodyCinfo {
  void FUN_01087ed0();                                // ctor
};
struct HkBoxShape {
  void FUN_010c05d0(const float* v, float r);         // ctor
};
struct HkRigidBody {
  void FUN_010878b0(const void* cinfo);               // ctor
};
struct SpinFilter {
  void FUN_005effe0();                                // ctor
  void FUN_005effa0(int a, int b);                    // disableCollisionsUsingBitfield
  void FUN_005eff70(int a, int b);                    // enableCollisionsBetween
};

// free functions
void  FUN_004a9610(void* src, void* dst);             // ConvertToMatrix
void  FUN_005cfde0(int limb, int blk, float* v, float* d, float* m, float* z, int mode, char one);
void  FUN_004a92c0(void* rot, void* xf);              // HavokAlignedRoutine
void  FUN_005cd670(void* xf, int flag);               // SpineBigStub
void  FUN_010c25a0(void* agent);                      // registerAllAgents
void* FUN_006abeb0(int size);                         // 8-byte wrapper allocator

// ---- model (UsingSymmetry / SetUsingSymmetry) ----
struct Model {
  char pad00[0x28];
  bool UsingSymmetry();                // 0x004adc40
  void SetUsingSymmetry(int v);        // 0x004adc20
};

// ---------------------------------------------------------------------------
class cSPEditorSpine {
 public:
  char  pad00[0x14];
  void* mpWorld;                                       // +0x14
  char  pad18[0xc4 - 0x18];
  float mSpineVelocityLimit;                           // +0xc4
  float mSpineErrorRecoveryVelocityExponential;        // +0xc8
  char  padcc[0xd0 - 0xcc];
  RbNode* mAnchorRight;                                // +0xd0
  RbNode* mAnchorLeft;                                 // +0xd4
  RbNode* mAnchorParent;                               // +0xd8
  int     mAnchorColor;                                // +0xdc
  unsigned mMapSize;                                   // +0xe0
  char  pade4[0xe8 - 0xe4];
  void* mpLimbs;                                       // +0xe8
  char  padec[0xf4 - 0xec];
  void* pF4;                                           // +0xf4
  void* pF8;                                           // +0xf8
  char  padfc[0x108 - 0xfc];
  void** limbVecBegin;                                 // +0x108
  void** limbVecEnd;                                   // +0x10c
  char  pad110[0x128 - 0x110];

  void LoadDynamicTuning();                            // 0x005ce300
  void LoadStaticTuning();                             // 0x005cf830

  Leg* GetFirstLeg();                                  // 005d0ce0
  Leg* GetLastLeg();                                   // 005d0d90

  void FUN_005d02d0();                                 // 0x005d02d0
  void FUN_005d07f0(int dt, void* model);              // 0x005d07f0
  cSPEditorSpine* FUN_005d0ea0();                      // 0x005d0ea0
};

// @ 0x005D0CE0
Leg* cSPEditorSpine::GetFirstLeg() {
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

// @ 0x005D0D90
Leg* cSPEditorSpine::GetLastLeg() {
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

// Scratch frame shared by the vertebra loop; conv/blkPos/xfPos are contiguous so that
// &conv[6] (the third basis row) runs into blkPos and xfPos exactly like the original.
struct BuilderLocals {
  float conv[9];     // 0x28
  float blkPos[3];   // 0x4c
  float xfPos[3];    // 0x58
  float delta[3];    // 0xac
  float W[9];        // 0x10c
  float zero[4];
};

// @ 0x005D02D0
void cSPEditorSpine::FUN_005d02d0() {
  void* mgr = mpLimbs;
  Model* model = 0;
  int sym = 0;
  if (mgr != 0) {
    model = *(Model**)((char*)mgr + 0x28);
    if (model != 0) {
      sym = model->UsingSymmetry() ? 1 : 0;
      model->SetUsingSymmetry(0);
    }
  }

  RbNode* node = mAnchorLeft;
  char* sentinel = (char*)this + 0xd0;
  if ((char*)node != sentinel) {
    do {
      Block* blk = *(Block**)((char*)node + 0x10);
      void* vi = *(void**)((char*)node + 0x14);
      Xf* xf = *(Xf**)((char*)vi + 0x58);

      BuilderLocals L;
      for (int i = 0; i < 3; ++i) {
        L.blkPos[i] = (&blk->pos.x)[i];
        L.xfPos[i] = (&xf->pos.x)[i];
      }
      FUN_004a9610(xf->src, L.conv);
      for (int i = 0; i < 3; ++i)
        L.delta[i] = L.xfPos[i] - L.blkPos[i];

      float T[9];
      T[0] = blk->m[0]; T[1] = blk->m[3]; T[2] = blk->m[6];
      T[3] = blk->m[1]; T[4] = blk->m[4]; T[5] = blk->m[7];
      T[6] = blk->m[2]; T[7] = blk->m[5]; T[8] = blk->m[8];
      for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
          L.W[r * 3 + c] = T[r * 3 + 0] * L.conv[0 + c] +
                           T[r * 3 + 1] * L.conv[3 + c] +
                           T[r * 3 + 2] * L.conv[6 + c];

      blk->FUN_00448e90(*(Vec3*)L.xfPos, 1);
      blk->FUN_00449420(L.conv, 1);

      int n = (int)((char*)blk->limbEnd - (char*)blk->limbBegin) >> 2;
      for (int i = 0; i < n; ++i) {
        void* limb = blk->limbBegin[i];
        unsigned flags = *(unsigned*)((char*)limb + 0xdc8);
        if (((flags >> 7) & 1) == 0) {
          L.zero[0] = 0.0f; L.zero[1] = 0.0f; L.zero[2] = 0.0f; L.zero[3] = 0.0f;
          FUN_005cfde0((int)limb, (int)blk, L.conv + 6, L.delta, L.W, L.zero,
                       2 - ((flags >> 11) & 1), 1);
        }
      }
      node = (RbNode*)FUN_00921580(node);
    } while ((char*)node != sentinel);
  }

  mgr = mpLimbs;
  if (mgr != 0) {
    model = *(Model**)((char*)mgr + 0x28);
    if (model != 0)
      model->SetUsingSymmetry(sym);
  }
}

// (1 - 2^(sqrt(len2) * -2/3 * log2(e))) * 1.5, the damping factor the original computes
// with the x87 fsqrt/fmul/f2xm1/fscale/fsubr/fmul sequence.
static float DampFactor(float len2) {
  float len = sqrtf(len2);
  double ex = (double)len * (double)g_13f89c0 * 1.4426950408889634;
  double two = pow(2.0, ex);
  return (float)((1.0 - two) * 1.5);
}

// @ 0x005D07F0
void cSPEditorSpine::FUN_005d07f0(int dt, void* modelPtr) {
  Model* model = (Model*)modelPtr;
  LoadDynamicTuning();

  float f = (float)dt;
  if (dt < 0)
    f = f + g_13f4fd0;                    // + 2^32
  f = f * g_13f9428 + mSpineErrorRecoveryVelocityExponential;
  mSpineErrorRecoveryVelocityExponential = f;
  if (f > g_13f6bf8)
    mSpineErrorRecoveryVelocityExponential = g_13f6bf8;

  f = mSpineErrorRecoveryVelocityExponential;
  while (f >= g_13f1f0c) {
    ((HkWorld*)mpWorld)->FUN_01082a90(g_13f1f0c);
    f = mSpineErrorRecoveryVelocityExponential - g_13f1f0c;
    mSpineErrorRecoveryVelocityExponential = f;
  }

  if (*(char*)((char*)this + 0xc5) == 0) {
    // ---- branch A ----
    RbNode* it = mAnchorLeft;
    char* sentinel = (char*)this + 0xd0;
    if ((char*)it != sentinel) {
      do {
        Entity* e = *(Entity**)((char*)it + 0x14);
        Vec4 z;
        z.x = 0.0f; z.y = 0.0f; z.z = 0.0f; z.w = 0.0f;
        e->FUN_01088ae0();
        ((VFn1)VSLOT(e->shape, 0x58))(e->shape, &z);
        Entity* e2 = *(Entity**)((char*)it + 0x14);
        e2->FUN_01088ae0();
        ((VFn1)VSLOT(e2->shape, 0x5c))(e2->shape, &z);
        (*(Entity**)((char*)it + 0x14))->FUN_01087520(6, 1, 0);
        it = (RbNode*)FUN_00921580(it);
      } while ((char*)it != sentinel);
    }

    RbNode* it2 = mAnchorLeft;
    if ((char*)it2 != sentinel) {
      do {
        Block* blk = *(Block**)((char*)it2 + 0x10);
        float mat[16];
        mat[0] = 1.0f; mat[1] = 0.0f; mat[2] = 0.0f; mat[3] = 0.0f;
        mat[4] = 0.0f; mat[5] = 1.0f; mat[6] = 0.0f; mat[7] = 0.0f;
        mat[8] = 0.0f; mat[9] = 0.0f; mat[10] = 1.0f; mat[11] = 0.0f;
        mat[12] = blk->pos.x; mat[13] = blk->pos.y; mat[14] = blk->pos.z; mat[15] = 0.0f;
        FUN_004a92c0(blk->m60, mat);
        FUN_005cd670(mat, 0);
        (*(Entity**)((char*)it2 + 0x14))->FUN_01087890(mat);
        it2 = (RbNode*)FUN_00921580(it2);
      } while ((char*)it2 != sentinel);
    }
    return;
  }

  // ---- branch B: damped per-vertebra velocities, then rebuild everything ----
  RbNode* it = mAnchorLeft;
  char* sentinel = (char*)this + 0xd0;
  if ((char*)it != sentinel) {
    do {
      Entity* e = *(Entity**)((char*)it + 0x14);
      void* shape = e->shape;
      float* v = (float*)((char*)shape + 0xd0);
      float len2 = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
      if (g_13ebca0 < len2) {
        float len = sqrtf(len2);
        float inv = 1.0f / len;
        float factor = DampFactor(len2);
        Vec4 s;
        s.x = factor * (v[0] * inv);
        s.y = (v[1] * inv) * factor;
        s.z = (v[2] * inv) * factor;
        s.w = (v[3] * inv) * factor;
        e->FUN_01088ae0();
        ((VFn1)VSLOT(shape, 0x58))(shape, &s);
      }
      void* shape2 = e->shape;
      float* w = (float*)((char*)shape2 + 0xe0);
      float len2b = w[0] * w[0] + w[1] * w[1] + w[2] * w[2];
      if (g_13ebca0 < len2b) {
        float len = sqrtf(len2b);
        float inv = 1.0f / len;
        float factor = DampFactor(len2b);
        Vec4 s;
        s.x = factor * (w[0] * inv);
        s.y = (w[1] * inv) * factor;
        s.z = (w[2] * inv) * factor;
        s.w = (w[3] * inv) * factor;
        e->FUN_01088ae0();
        ((VFn1)VSLOT(shape2, 0x5c))(shape2, &s);
      }
      it = (RbNode*)FUN_00921580(it);
    } while ((char*)it != sentinel);
  }

  FUN_005d02d0();
  int u = model->UsingSymmetry() ? 1 : 0;
  model->SetUsingSymmetry(0);
  int count = (int)((char*)limbVecEnd - (char*)limbVecBegin) >> 2;
  for (int i = 0; i < count; ++i) {
    LimbStructure* limb = (LimbStructure*)limbVecBegin[i];
    limb->FUN_004890e0(1);
    limb->FUN_00489ae0();
  }
  model->SetUsingSymmetry(u);

  void* a = pF4;
  if (a != 0 && pF8 != 0) {
    ((VFn0)VSLOT(a, 0x14))(a);
    ((VFn0)VSLOT(pF8, 0x14))(pF8);
  }
}

// @ 0x005D0EA0
cSPEditorSpine* cSPEditorSpine::FUN_005d0ea0() {
  char* base = (char*)this;

  *(int*)(base + 0x04) = 0;
  *(int*)(base + 0x08) = (int)(size_t)g_13f1ab0;
  *(float*)(base + 0x40) = g_1485720;
  *(float*)(base + 0x44) = g_1485720;
  *(float*)(base + 0xc8) = 0.0f;
  float v = g_15180d0;
  *(void**)(base) = g_13f89d4;
  *(void**)(base + 0x08) = g_13f89c4;
  *(int*)(base + 0x14) = 0;
  *(int*)(base + 0x1c) = 0;
  *(char*)(base + 0x30) = 0;
  *(int*)(base + 0x38) = 0;
  *(int*)(base + 0x3c) = 0;
  *(char*)(base + 0xc5) = 0;
  *(int*)(base + 0xd4) = 0;
  *(int*)(base + 0xd8) = 0;
  *(int*)(base + 0xdc) = 0;
  *(int*)(base + 0xd8) = 0;
  *(char*)(base + 0xdc) = 0;
  *(int*)(base + 0xe0) = 0;
  *(int*)(base + 0xd0) = (int)(size_t)(base + 0xd0);
  *(int*)(base + 0xd4) = (int)(size_t)(base + 0xd0);
  *(int*)(base + 0xe8) = 0;
  *(int*)(base + 0xec) = 0;
  *(int*)(base + 0xf4) = 0;
  *(int*)(base + 0xf8) = 0;
  *(int*)(base + 0xfc) = 0;
  *(int*)(base + 0x100) = 0;
  *(int*)(base + 0x104) = 0;
  *(int*)(base + 0x108) = 0;
  *(int*)(base + 0x10c) = 0;
  *(int*)(base + 0x110) = 0;
  *(float*)(base + 0x11c) = v;
  *(int*)(base + 0x120) = 0;
  *(int*)(base + 0x124) = 0;
  *(float*)(base + 0x0c) = g_15ba0d0;
  *(float*)(base + 0x10) = g_15ba0d4;

  LoadStaticTuning();

  char cinfo[0x100];
  ((HkWorldCinfo*)cinfo)->FUN_010880e0();
  {
    float bpsize = g_15180c0;
    *(float*)(cinfo + 0x10) = 0.0f;
    *(float*)(cinfo + 0x14) = 0.0f;
    *(float*)(cinfo + 0x18) = 0.0f;
    *(float*)(cinfo + 0x1c) = 0.0f;
    ((HkWorldCinfo*)cinfo)->FUN_010881d0(bpsize);
  }

  *(float*)(cinfo + 0x6c) = *(float*)(base + 0x58);
  *(char*)(cinfo + 0x95) = *(char*)(base + 0x54);
  *(float*)(cinfo + 0x70) = *(float*)(base + 0x5c);
  *(int*)(cinfo + 0x74) = *(int*)(base + 0x50);
  *(char*)(cinfo + 0x68) = 2;
  *(float*)(cinfo + 0x50) = g_13f893c;

  HkWorld* world = (HkWorld*)((VAlloc)VSLOT(g_16e4178, 0x10))(g_16e4178, 0x2f0, 0x2c);
  *(unsigned short*)((char*)world + 4) = 0x2f0;
  world->FUN_010840e0(cinfo, 0x765c);
  *(HkWorld**)(base + 0x14) = world;
  FUN_010c25a0(*(void**)((char*)world + 0x80));

  SpinFilter* filter = (SpinFilter*)((VAlloc)VSLOT(g_16e4178, 0x10))(g_16e4178, 0x9c, 0x24);
  *(unsigned short*)((char*)filter + 4) = 0x9c;
  filter->FUN_005effe0();
  world->FUN_01086f80(filter, 1, 0, 1);
  *(int*)((char*)filter + 0x18) += 1;
  *(int*)(base + 0x34) = *(int*)((char*)filter + 0x18);
  filter->FUN_005effa0(-2, -2);
  filter->FUN_005eff70(1, 2);
  if (*(unsigned short*)((char*)filter + 4) != 0) {
    *(unsigned short*)((char*)filter + 6) -= 1;
    if (*(unsigned short*)((char*)filter + 6) == 0)
      ((VFn0)VSLOT(filter, 0x00))((void*)filter);
  }

  void* obj = FUN_006abeb0(8);
  if (obj != 0) {
    *(void**)obj = g_13f89a4;
    *(int*)((char*)obj + 4) = 0;
  } else {
    obj = 0;
  }
  *(void**)(base + 0x18) = obj;

  char cinfo2[0xc0];
  ((HkRigidBodyCinfo*)cinfo2)->FUN_01087ed0();
  float bx = g_15180c0 * g_13f893c;
  float bw = g_15180c0 * g_1485378;
  float boxVec[4];
  boxVec[0] = bx; boxVec[1] = bx; boxVec[2] = bx; boxVec[3] = bw;

  HkBoxShape* shape = (HkBoxShape*)((VAlloc)VSLOT(g_16e4178, 0x10))(g_16e4178, 0x20, 0x24);
  *(unsigned short*)((char*)shape + 4) = 0x20;
  shape->FUN_010c05d0(boxVec, g_15ba104);

  *(void**)(cinfo2 + 0x04) = shape;
  *(char*)(cinfo2 + 0xb0) = 6;
  *(float*)(cinfo2 + 0x10) = 0.0f;
  *(float*)(cinfo2 + 0x14) = 0.0f;
  *(float*)(cinfo2 + 0x18) = 0.0f;
  *(float*)(cinfo2 + 0x1c) = 0.0f;
  *(float*)(cinfo2 + 0xa0) = 0.0f;

  HkRigidBody* body = (HkRigidBody*)((VAlloc)VSLOT(g_16e4178, 0x10))(g_16e4178, 0xd0, 0x2a);
  *(unsigned short*)((char*)body + 4) = 0xd0;
  body->FUN_010878b0(cinfo2);
  *(HkRigidBody**)(base + 0x1c) = body;

  if (*(unsigned short*)((char*)shape + 4) != 0) {
    *(unsigned short*)((char*)shape + 6) -= 1;
    if (*(unsigned short*)((char*)shape + 6) == 0)
      ((VFn0)VSLOT(shape, 0x00))(shape);
  }

  *(int*)((char*)body + 0x38) = 3;
  world->FUN_01082ee0(body, 1);

  *(int*)(base + 0x100) = 0;
  *(int*)(base + 0xfc) = (int)0xd05c53a3;
  *(int*)(base + 0x104) = (int)(size_t)g_15180ac;
  return this;
}

}  // namespace SP