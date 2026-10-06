// slice s005d36e0 -- SP::cSPEditorSpine large limb/geometry rebuild helpers (unnamed in the dev PDB).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// ---- local stubs (retail offsets: dev PDB cSPEditorSpine minus 8) ----
struct hkMemory {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void* allocate(int size, int type);  // vtbl +0x10
};
extern hkMemory* g_hkMemory;  // @ 0x016e4178

__declspec(align(16)) struct hkVector4 { float x, y, z, w; };
struct hkTransform { float rot[12]; float trans[4]; };

struct hkReferencedObject {
  virtual void deleteThis(int);
  uint16_t memSizeAndFlags;  // +4
  uint16_t referenceCount;   // +6
  void removeReference() {
    if (memSizeAndFlags != 0) {
      referenceCount--;
      if (referenceCount == 0) deleteThis(1);
    }
  }
};

struct hkMouseSpringAction : hkReferencedObject {
  uint32_t pad[0x12];
  hkMouseSpringAction* Construct(const hkVector4& posInRb, const hkVector4& mousePos, float damping,
                                 float elasticity, float maxForce, struct hkRigidBody* rb);  // @ 0x011278b0
  void setMaxRelativeForce(float f);  // @ 0x00c87bc0 (ICF'd as SetMaxCargoAmount)
};

struct hkRigidMotion {
  uint32_t pad[0x10];
  float pos[4];  // +0x40
  float getMass() const;  // @ 0x01088270
};
struct hkRigidBody {
  uint32_t pad[0x16];
  hkRigidMotion* motion;  // +0x58
  void setMotionType(int type, int a, int b);  // @ 0x01087520
  void addCollisionListener(void* l);          // @ 0x01088c90
  void removeReference();                      // @ 0x0109ae60
};
struct hkWorld {
  void removeAction(hkMouseSpringAction* a);  // @ 0x01086f40
  void addAction(hkMouseSpringAction* a);     // @ 0x01085e60
  hkRigidBody* addEntity(hkRigidBody* e, int a);  // @ 0x01082ee0
};

#define AT(T, p, off) (*(T*)((char*)(p) + (off)))
struct cSPEditorBlock {
  virtual void* Dtor(int);  // +0
  virtual void AddRef();    // +4
  virtual void Release();   // +8
  uint32_t pad0[0x11];
  float pos[3];  // +0x48
  uint32_t pad1[3];
  float xform[4];  // +0x60
  uint32_t pad2[0x5a];
  float scale;  // +0x1d8
  uint32_t pad3;
  float defaultOrient[2];  // +0x1e0
  cSPEditorBlock();  // @ 0x004346b0
  bool BuildBlock(uint32_t instance, uint32_t group, void* pWorld, void* pParent, float field30,
                  bool a, bool b, bool c);  // @ 0x00441440, ret 0x20
  void Shutdown2();                          // @ 0x00451400
  void SetPosition(const float* v, int flag);  // @ 0x00448e90
  void LinkNext(cSPEditorBlock* o);           // @ 0x00438700
};

struct cSPEditorHandleSpine {
  virtual void AddRef();   // +0
  virtual void Release();  // +4
  cSPEditorHandleSpine();  // @ 0x005a8ad0
  void Init(cSPEditorBlock* blk, const float* offset, const float* basis);  // @ 0x005a8970, ret 0xc
};
void* operator new(unsigned int, const char*, int, int, int, int);  // @ 0x00f473a0

struct Tuning { uint32_t pad[7]; float f1c; };
Tuning* EditorTuning();  // @ 0x00401070

struct VNodeBase { VNodeBase* right; VNodeBase* left; VNodeBase* parent; uint32_t color; };
struct VNode : VNodeBase { cSPEditorBlock* key; hkRigidBody* body; uint32_t pad[3]; };
struct VInfo { hkRigidBody* body; uint32_t a, b, c; };
struct VIter {
  VNodeBase* node;
  VIter() {}
  VIter(const VIter& o) : node(o.node) {}
};
struct VMap {
  uint32_t cmp;
  VNodeBase anchor;  // +4 (this+0xd0 in the spine)
  uint32_t size, alloc;
  VIter find(cSPEditorBlock* const& key);       // @ 0x00e5c780
  VInfo* subscript(cSPEditorBlock* const& key);  // @ 0x00632e90
};
void* RBTreeIncrement(void* n);  // @ 0x00921580

struct cBlockList {
  uint32_t Count();                    // @ 0x004accf0
  cSPEditorBlock* At(uint32_t i);      // @ 0x004accb0
};
cSPEditorBlock* NextBlock(cSPEditorBlock* b);  // @ 0x004a5970 (cdecl)
void FUN_004a92c0(float* a, hkTransform* t);
void FUN_005cd670(hkTransform* t, int);

struct cPhysWorldHolder { hkWorld* World(); };  // @ 0x004b91c0
struct cEditorCtx {
  void FUN_004ad280();
  float FUN_004adaa0();
  float FUN_004adb00();
  float FUN_004adb40();
  cPhysWorldHolder* FUN_004ad450();
  void FUN_004abaf0(cSPEditorBlock* b, int flag);
};
struct Mat3 { float m[9]; };
extern Mat3 g_BasisMat;  // @ 0x015ee4dc

struct cSPEditorSpine {
  uint32_t pad0[5];
  hkWorld* world;                // +0x14
  void* listener;                // +0x18
  uint32_t pad0b;
  float wallX0, wallZ0, wallX1, wallZ1;  // +0x20..0x2c
  bool wallsCreated;             // +0x30
  uint8_t pad0c[3];
  uint32_t pad1[2];
  hkMouseSpringAction* spring;   // +0x3c
  float f40, f44;                // +0x40, +0x44
  uint32_t pad2[0x1a];
  float springDamping;           // +0xb0
  float springElasticity;        // +0xb4
  float springMaxForce;          // +0xb8
  uint32_t pad3[2];
  uint8_t pad4[1];
  bool simulating;               // +0xc5
  uint8_t pad5[2];
  uint32_t pad6;
  VMap vertebrae;                // +0xcc
  cSPEditorBlock* firstBlock;    // +0xe8
  cSPEditorBlock* lastBlock;     // +0xec
  cSPEditorBlock* sceneBlock;    // +0xf0
  cSPEditorHandleSpine* firstHandle;  // +0xf4
  cSPEditorHandleSpine* lastHandle;   // +0xf8
  uint32_t keyInstance;          // +0xfc
  uint32_t keyType;              // +0x100
  uint32_t keyGroup;             // +0x104
  uint32_t pad8[5];
  float vertebraHalfWidth;       // +0x11c

  void FUN_005d1530();
  void FUN_005d25c0(cSPEditorBlock* b);
  float FUN_005d3100();
  void FUN_005d31b0();
  void FUN_005d2790();
  hkRigidBody* CreateVertebraBody(float scale, hkTransform* t);  // @ 0x005cdd00

  __forceinline void BuildHandles() {
    Tuning* tuning = EditorTuning();
    cSPEditorHandleSpine* h = new ("Editor", 0, 0, 0, 0) cSPEditorHandleSpine;
    cSPEditorHandleSpine* old = firstHandle;
    if (h != old) {
      if (h) h->AddRef();
      firstHandle = h;
      if (old) old->Release();
    }
    float V[3];
    V[0] = 0.0f; V[1] = -tuning->f1c; V[2] = 0.0f;
    firstHandle->Init(firstBlock, V, g_BasisMat.m);
    Mat3 M = g_BasisMat;
    M.m[4] = -1.0f;
    M.m[8] = -1.0f;
    h = new ("Editor", 0, 0, 0, 0) cSPEditorHandleSpine;
    old = lastHandle;
    if (h != old) {
      if (h) h->AddRef();
      lastHandle = h;
      if (old) old->Release();
    }
    V[0] = 0.0f; V[1] = tuning->f1c; V[2] = 0.0f;
    lastHandle->Init(lastBlock, V, M.m);
  }

  bool FUN_005d43d0(cSPEditorBlock** pBlock, float a, float b, float c, float d, float e, float f);
  void FUN_005d3f10(cBlockList* blocks, cSPEditorBlock* sceneBlk);
  void FUN_005d36e0(struct cEditorCtx* ctx, cSPEditorBlock* sceneWorld, uint32_t n);
  void CreateWallBoxAndAddToWorld(const float* halfExt, const float* pos, hkWorld* w);  // @ 0x005cdbf0
  void FUN_005d1e70();
  void FUN_005d2480(cSPEditorBlock* b);
  void FUN_005d1f30();
};

// @ 0x005D43D0
bool cSPEditorSpine::FUN_005d43d0(cSPEditorBlock** pBlock, float a, float b, float c, float d, float e,
                                  float f) {
  cSPEditorBlock* key = *pBlock;
  if (vertebrae.find(key).node != &vertebrae.anchor) {
    VInfo* info = vertebrae.subscript(key);
    if (info) {
      if (!simulating) {
        FUN_005d1530();
        simulating = true;
      }
      for (VNodeBase* n = vertebrae.anchor.left; n != &vertebrae.anchor; n = (VNodeBase*)RBTreeIncrement(n))
        ((VNode*)n)->body->setMotionType(1, 1, 0);
      FUN_005d25c0(*pBlock);
      float den = (f + e) * 0.0f + d;
      if (den != 0.0f) {
        float t = -(((c + b) * 0.0f + a) / den);
        if (t >= 0.0f) {
          float x = a + d * t;
          float y = b + e * t;
          float z = c + f * t;
          hkVector4 mouse;
          mouse.x = x; mouse.y = y; mouse.z = z; mouse.w = 0.0f;
          hkRigidMotion* m = info->body->motion;
          hkVector4 local;
          local.x = x - m->pos[0];
          local.y = y - m->pos[1];
          local.z = z - m->pos[2];
          local.w = -m->pos[3];
          local.x = 0.0f;
          mouse.x = 0.0f;
          if (spring) {
            world->removeAction(spring);
            spring->removeReference();
          }
          hkMouseSpringAction* act = (hkMouseSpringAction*)g_hkMemory->allocate(0x50, 0x26);
          act->memSizeAndFlags = 0x50;
          act = act->Construct(local, mouse, springDamping, springElasticity, 1.0f, info->body);
          spring = act;
          float s = FUN_005d3100();
          float mass = info->body->motion->getMass();
          spring->setMaxRelativeForce(springMaxForce / mass * s);
          world->addAction(spring);
        }
      }
      return true;
    }
  }
  return false;
}

// @ 0x005D3F10
void cSPEditorSpine::FUN_005d3f10(cBlockList* blocks, cSPEditorBlock* sceneBlk) {
  if (firstBlock) { cSPEditorBlock* p = firstBlock; firstBlock = 0; p->Release(); }
  if (lastBlock) { cSPEditorBlock* p = lastBlock; lastBlock = 0; p->Release(); }
  FUN_005d31b0();
  uint32_t n = blocks->Count();
  for (uint32_t i = 0; i < n; i++) {
    cSPEditorBlock* blk = blocks->At(i);
    if (((AT(uint32_t, blk, 0xdc8)) >> 7) & 1) {
      float scale = blk->scale;
      hkTransform T;
      T.rot[0] = 1.0f; T.rot[1] = 0.0f; T.rot[2] = 0.0f; T.rot[3] = 0.0f;
      T.rot[4] = 0.0f; T.rot[5] = 1.0f; T.rot[6] = 0.0f; T.rot[7] = 0.0f;
      T.rot[8] = 0.0f; T.rot[9] = 0.0f; T.rot[10] = 1.0f; T.rot[11] = 0.0f;
      T.trans[0] = blk->pos[0]; T.trans[1] = blk->pos[1]; T.trans[2] = blk->pos[2]; T.trans[3] = 0.0f;
      FUN_004a92c0(blk->xform, &T);
      FUN_005cd670(&T, 0);
      hkRigidBody* rb = CreateVertebraBody(scale, &T);
      world->addEntity(rb, 1);
      rb->removeReference();
      rb->addCollisionListener(listener);
      *(uint16_t*)((char*)rb + 0x96) = 0;
      VInfo* info = vertebrae.subscript(blk);
      info->body = rb; info->a = 0; info->b = 0; info->c = 0;
      if (AT(uint32_t, blk, 0x33c) == 0) {
        cSPEditorBlock* old = firstBlock;
        if (blk != old) {
          blk->AddRef();
          firstBlock = blk;
          if (old) old->Release();
        }
      }
    }
  }
  cSPEditorBlock* p = firstBlock;
  while (p && !lastBlock) {
    cSPEditorBlock* nx = NextBlock(p);
    if (nx) {
      p = nx;
    } else {
      cSPEditorBlock* old = lastBlock;
      if (p != old) {
        if (p) p->AddRef();
        lastBlock = p;
        if (old) old->Release();
      }
    }
  }
  if (firstBlock && lastBlock) {
    sceneBlock = sceneBlk;
    FUN_005d2790();
    BuildHandles();
    return;
  }
  if (firstBlock) { cSPEditorBlock* p2 = firstBlock; firstBlock = 0; p2->Release(); }
  if (lastBlock) { cSPEditorBlock* p2 = lastBlock; lastBlock = 0; p2->Release(); }
}

extern float g_WallThickness;  // @ 0x015180c8
extern float g_WallDepth;      // @ 0x015ee448

// @ 0x005D36E0
void cSPEditorSpine::FUN_005d36e0(cEditorCtx* ctx, cSPEditorBlock* sceneWorld, uint32_t n) {
  sceneBlock = sceneWorld;
  if (firstBlock) { cSPEditorBlock* p = firstBlock; firstBlock = 0; p->Release(); }
  if (lastBlock) { cSPEditorBlock* p = lastBlock; lastBlock = 0; p->Release(); }
  ctx->FUN_004ad280();
  FUN_005d31b0();
  cSPEditorBlock* tmp = new ("Editor", 0, 0, 0, 0) cSPEditorBlock;
  tmp->BuildBlock(keyInstance, keyGroup, sceneBlock, 0, 0.0f, false, false, true);
  f40 = tmp->defaultOrient[0];
  f44 = tmp->defaultOrient[1];
  tmp->Shutdown2();
  tmp->Dtor(1);
  if (!wallsCreated) {
    float width = ctx->FUN_004adaa0();
    wallZ1 = ctx->FUN_004adb00();
    wallZ0 = ctx->FUN_004adb40();
    wallX0 = -0.5f * width;
    wallX1 = width * 0.5f;
    float W = g_WallThickness;
    float depth = g_WallDepth;
    float h = wallZ0 - wallZ1;
    float H[4];
    float P[4];
    H[0] = depth * 0.5f;
    H[1] = ((wallX1 - wallX0) + W * 2.0f) * 0.5f;
    H[2] = W * 0.5f;
    H[3] = 0.0f;
    P[0] = 0.0f; P[1] = 0.0f; P[2] = (wallZ1 - W * 0.5f) - 0.02f; P[3] = 0.0f;
    CreateWallBoxAndAddToWorld(H, P, world);
    P[0] = 0.0f; P[1] = 0.0f; P[2] = (W * 0.5f + wallZ0) + 0.02f; P[3] = 0.0f;
    CreateWallBoxAndAddToWorld(H, P, world);
    H[0] = depth * 0.5f;
    H[1] = W * 0.5f;
    H[2] = (W * 2.0f + h) * 0.5f;
    H[3] = 0.0f;
    P[0] = 0.0f; P[1] = (wallX1 + W * 0.5f) + 0.02f; P[2] = h * 0.5f + wallZ1; P[3] = 0.0f;
    CreateWallBoxAndAddToWorld(H, P, world);
    P[0] = 0.0f; P[1] = (wallX0 - W * 0.5f) - 0.02f; P[2] = h * 0.5f + wallZ1; P[3] = 0.0f;
    CreateWallBoxAndAddToWorld(H, P, world);
    wallsCreated = true;
  }
  ctx->FUN_004adaa0();
  ctx->FUN_004adaa0();
  float third = ctx->FUN_004adaa0() * 0.33333334f;
  float sp = vertebraHalfWidth * 2.0f * 1.5f;
  float start = sp * 0.5f - ((float)n * sp) * 0.5f;
  for (uint32_t i = 0; i < n; i++) {
    float off = (float)i * sp + start;
    hkTransform T;
    T.rot[0] = 1.0f; T.rot[1] = 0.0f; T.rot[2] = 0.0f; T.rot[3] = 0.0f;
    T.rot[4] = 0.0f; T.rot[5] = 1.0f; T.rot[6] = 0.0f; T.rot[7] = 0.0f;
    T.rot[8] = 0.0f; T.rot[9] = 0.0f; T.rot[10] = 1.0f; T.rot[11] = 0.0f;
    T.trans[0] = 0.0f; T.trans[1] = off; T.trans[2] = third; T.trans[3] = 0.0f;
    hkRigidBody* rb = CreateVertebraBody(1.0f, &T);
    world->addEntity(rb, 1);
    rb->removeReference();
    rb->addCollisionListener(listener);
    *(uint16_t*)((char*)rb + 0x96) = 0;
    cSPEditorBlock* blk = new ("Editor", 0, 0, 0, 0) cSPEditorBlock;
    float f30 = ctx->FUN_004adaa0();
    blk->BuildBlock(keyInstance, keyGroup, sceneBlock, ctx->FUN_004ad450()->World(), f30, true, true, true);
    float V[3];
    V[0] = 0.0f; V[1] = off; V[2] = third;
    blk->SetPosition(V, 0);
    VInfo* info = vertebrae.subscript(blk);
    info->body = rb; info->a = 0; info->b = 0; info->c = 0;
    ctx->FUN_004abaf0(blk, 1);
    if (firstBlock == 0) {
      cSPEditorBlock* old = firstBlock;
      if (blk != old) {
        if (blk) blk->AddRef();
        firstBlock = blk;
        if (old) old->Release();
      }
    } else if (lastBlock) {
      lastBlock->LinkNext(blk);
    }
    cSPEditorBlock* old2 = lastBlock;
    if (blk != old2) {
      if (blk) blk->AddRef();
      lastBlock = blk;
      if (old2) old2->Release();
    }
  }
  FUN_005d1e70();
  for (VNodeBase* nd = vertebrae.anchor.left; nd != &vertebrae.anchor; nd = (VNodeBase*)RBTreeIncrement(nd))
    FUN_005d2480(((VNode*)nd)->key);
  FUN_005d1f30();
  BuildHandles();
}
