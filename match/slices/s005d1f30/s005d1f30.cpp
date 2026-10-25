// slice s005d1f30 -- SP::cSPEditorSpine vertebra tree maintenance helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

namespace SP {

// ---------------------------------------------------------------------------
// Stub types. Layouts are read from the retail disassembly: the dev PDB
// cSPEditorSpine layout is shifted by -8 from the vertebra map onwards.
// ---------------------------------------------------------------------------

// eastl red-black tree node base (order confirmed against slice s00456360).
struct RBNodeBase {
  RBNodeBase* mpNodeRight;   // +0
  RBNodeBase* mpNodeLeft;    // +4
  RBNodeBase* mpNodeParent;  // +8
  int mnColor;               // +0xc
};

// full node: base followed by the key/value payload.
struct RBNode : RBNodeBase {
  unsigned int mKey;  // +0x10
};

// value type of cSPEditorSpine::mVertebrae (dev PDB size 0x10).
struct cSPEditorVertebraInfo {
  void* mpRigidBody;         // +0
  void* mpHingeConstraint;   // +4
  void* mpPlanarConstraint;  // +8
  int mOrderInSpine;         // +0xc
};

// eastl::map<unsigned, cSPEditorVertebraInfo>
struct VertebraMap {
  char pad0[4];         // +0x00 comparator / allocator (empty)
  RBNodeBase mAnchor;   // +0x04 (sentinel); begin() = mAnchor.mpNodeLeft
  int mnSize;           // +0x14
  int pad18;            // +0x18 (the map object spans 0x1c bytes)

  RBNode** find(RBNode** it, const unsigned int* key) const;    // 0x00e5c780
  cSPEditorVertebraInfo& operator[](const unsigned int& key);   // 0x00632e90
};

// Havok reference-counted base; memSizeAndFlags and referenceCount are u16.
struct hkRefObj {
  virtual void vDestroy(int deleteIt);  // slot 0
  unsigned short mMemSizeAndFlags;      // +4
  unsigned short mReferenceCount;       // +6

  void Release() {
    if (mMemSizeAndFlags) {
      if (--mReferenceCount == 0) vDestroy(1);
    }
  }
};

class hkMemory {
 public:
  virtual void* pad0();
  virtual void* pad1();
  virtual void* pad2();
  virtual void* pad3();
  virtual void* allocate(int size, int align);  // slot at vtable +0x10
};

class hkWorld {
 public:
  void* addConstraint(void* constraint);      // 0x01086da0
  void removeConstraint(char* out, void* c);  // 0x01086e90
};

struct hkRigidMotion {
  char pad0[0xc8];
  float mLinearDamping;   // +0xc8
  float mAngularDamping;  // +0xcc
  float getMass() const;  // 0x01088270
};

struct hkRigidBody {
  void* mpVtbl;          // +0
  char pad04[0x54];
  hkRigidMotion* mBody;  // +0x58 (motion sub-object)
};

struct hkTransform {
  float m[16];
};

struct hkConstraintInstance {
  void* mpVtbl;  // +0
  char pad04[8];
};

struct hkGenericConstraintData {
  void* mpVtbl;                 // +0
  unsigned short mMemSize;      // +4
  unsigned short mRefCount;     // +6
  void* mpEntityA;              // +8
  void* mpEntityB;              // +0xc
};

// hkLimitedHingeConstraintData (retail size 0x90).
struct hkLimitedHingeConstraintData : hkRefObj {
  void* mpEntityA;                          // +8
  float mSpineChainDamping;                 // +0xc
  float mSpineHingeAngularLimitsTauFactor;  // +0x10
  float mSpineMassTimesFactor;              // +0x14
  float mSpineChainTau;                     // +0x18
  float mAxisA[4];                          // +0x20
  char pad30[0x30];
  float mAxisB[4];  // +0x60
  char pad70[0x26];
  unsigned short mFlags96;  // +0x96

  void setInBodySpace(const hkTransform& a, const hkTransform& b, const hkTransform& c,
                      const hkTransform& d, const hkTransform& e, const hkTransform& f);
  // 0x0108aec0
};

// cSPEditorBlock fields touched by this slice.
struct cSPEditorBlock {
  char pad00[0x48];
  float mField48;  // +0x48
  float mField4c;  // +0x4c
  float mField50;  // +0x50
  char pad54[0xc];
  float mOrientation60[12];  // +0x60
  char pad90[0x148];
  float mField1d8;  // +0x1d8
};

// State object the constraint chain is anchored through (0x28 bytes here).
struct hkConstraintChainState : hkRefObj {
  char pad08[0x10];
  int mSpineMinCollisionDeadZoneDistance;  // +0x18
  int mSpineUseFewerAxialConstraints;      // +0x1c
};

// ---------------------------------------------------------------------------
// externs (callees are masked relocations; the address notes the original)
// ---------------------------------------------------------------------------
extern void* g_hkMemoryInstance;  // 0x016e4178

RBNode* RBTreeIncrement(RBNodeBase* node);  // 0x00921580
void* FUN_004a5970(void* key);              // 0x004a5970 (next vertebra block key)
void* CreateAxialConstraintData(int unused);                            // 0x005ce0c0
void* FUN_0108bb00(void* self);                                         // 0x0108bb00
void* FUN_0108bf10(void* self, void* a, void* b, void* c, int d);       // 0x0108bf10
void* FUN_0108ba70(void* a, void* b);                                   // 0x0108ba70
void* FUN_0108acb0(void* self);                                         // 0x0108acb0
void* FUN_0108ac30(void* self, void* entity);                           // 0x0108ac30
void FUN_0108ae30(void* self);                                          // 0x0108ae30

void HavokAlignedRoutine(void* src, void* dst);  // 0x004a92c0
void SpineBigStub(void* a, void* b);             // 0x005cd670

static hkRefObj* hkAlloc(int size) {
  void* p = ((hkMemory*)g_hkMemoryInstance)->allocate(size, 0x29);
  ((hkRefObj*)p)->mMemSizeAndFlags = (unsigned short)size;
  return (hkRefObj*)p;
}

// ---------------------------------------------------------------------------
// cSPEditorSpine (slice spelling cSpine76 keeps the existing manifest row)
// ---------------------------------------------------------------------------
class cSpine76 {
 public:
  char pad00[0x14];
  hkWorld* mpHavokWorld_14;  // +0x14
  char pad18[4];
  hkWorld* mpHavokWorld;  // +0x1c
  char pad20[0x18];
  void* mpChain;  // +0x38
  char pad3c[0x3c];
  bool mSpineVertebraHavokPaddingFactor;  // +0x78
  char pad79[3];
  int mSpineMinCollisionDeadZoneDistance;  // +0x7c
  bool mSpineUseFewerAxialConstraints;     // +0x80
  char pad81[3];
  float mSpineChainTau;                     // +0x84
  float mSpineChainDamping;                 // +0x88
  float mSpineHingeAngularLimitsTauFactor;  // +0x8c
  char pad90[0xc];
  int mMaxFlexIndex;                        // +0x9c
  float mScaleOfLeastFlexibility;           // +0xa0
  float mSpineDampingMaxInfluenceDistance;  // +0xa4
  float mSpineLooseLinearDamping;           // +0xa8
  float mSpineLooseAngularDamping;          // +0xac
  char padb0[0x1c];
  VertebraMap mVertebrae;          // +0xcc
  cSPEditorBlock* mFirstVertebra;  // +0xe8
  cSPEditorBlock* mLastVertebra;   // +0xec
  char padf0[0x2c];
  float mVertebraHalfWidth;  // +0x11c

  void SetTuning(int unused);                        // 005d2740
  void Refresh(int unused);                          // 005d2790
  __declspec(noinline) void FUN_005d1ba0();          // 005d1ba0
  __declspec(noinline) void FUN_005d1e70();          // 005d1e70
  __declspec(noinline) void FUN_005d1d40();          // 005d1d40
  void FUN_005d1f30();                               // 005d1f30 (ReconstructChain)
  __declspec(noinline) void FUN_005d2480(int key);   // 005d2480
  __declspec(noinline) void FUN_005d25c0(unsigned int key);  // 005d25c0
  __declspec(noinline) int* AddVertebraBody(int* pOut, float f, const hkTransform& t);
  // 0x005ce060
  void FUN_005cdae0(cSPEditorVertebraInfo* info);  // 0x005cdae0
};

// ---------------------------------------------------------------------------
// definitions
// ---------------------------------------------------------------------------

// @ 0x005D2740
void cSpine76::SetTuning(int) {
  RBNodeBase* end = &mVertebrae.mAnchor;
  for (RBNodeBase* n = end->mpNodeLeft; n != end; n = RBTreeIncrement(n)) {
    cSPEditorVertebraInfo* info = (cSPEditorVertebraInfo*)((char*)n + sizeof(RBNode));
    hkRigidBody* body = (hkRigidBody*)info->mpRigidBody;
    hkRigidMotion* motion = body->mBody;
    motion->mLinearDamping = mSpineLooseLinearDamping;
    motion->mAngularDamping = mSpineLooseAngularDamping;
  }
  FUN_005d1ba0();
}

// @ 0x005D2790
void cSpine76::Refresh(int) {
  FUN_005d1e70();
  RBNodeBase* end = &mVertebrae.mAnchor;
  for (RBNodeBase* n = end->mpNodeLeft; n != end; n = RBTreeIncrement(n)) {
    FUN_005d2480((int)(size_t)((RBNode*)n)->mKey);
  }
  FUN_005d1f30();
}

// --- helpers owned by other slices (kept from the earlier wave) -------------
volatile int g_spine76Sink = 0;

// @ 0x005D1BA0
// PARTIAL: 0x197-byte helper reconstructed elsewhere.
__declspec(noinline) void cSpine76::FUN_005d1ba0() { g_spine76Sink = 2; }
// @ 0x005D1E70
// PARTIAL: 0xb7-byte tree teardown reconstructed elsewhere.
__declspec(noinline) void cSpine76::FUN_005d1e70() { g_spine76Sink = 3; }
// @ 0x005D1D40
// PARTIAL: 0x124-byte helper reconstructed elsewhere.
__declspec(noinline) void cSpine76::FUN_005d1d40() { g_spine76Sink = 4; }

// @ 0x005D1F30  (cSPEditorSpine::ReconstructChain)
void cSpine76::FUN_005d1f30() {
  FUN_005d1e70();

  hkConstraintChainState* chainState = (hkConstraintChainState*)hkAlloc(0x28);
  void* chain = FUN_0108bb00(chainState);
  bool bAbort = false;

  FUN_005d1d40();

  unsigned int key = (unsigned int)(size_t)mFirstVertebra;
  for (;;) {
    if (key == 0) break;

    RBNode* hit;
    cSPEditorVertebraInfo* info =
        (*mVertebrae.find(&hit, &key) == (RBNode*)&mVertebrae.mAnchor) ? 0 : &mVertebrae[key];

    if (!mSpineVertebraHavokPaddingFactor || key == (unsigned int)(size_t)mFirstVertebra ||
        key == (unsigned int)(size_t)mLastVertebra) {
      // axial (planar) constraint between this vertebra and the world
      hkRefObj* axialData = (hkRefObj*)CreateAxialConstraintData(0);
      hkRefObj* ci = hkAlloc(0x28);
      hkConstraintInstance* inst =
          (hkConstraintInstance*)FUN_0108bf10(ci, mpHavokWorld, info->mpRigidBody, axialData, 1);
      axialData->Release();
      mpHavokWorld_14->addConstraint(inst);
      ((hkRefObj*)inst)->Release();
      info->mpPlanarConstraint = inst;

      if (key == (unsigned int)(size_t)mLastVertebra) break;
    }

    // hinge constraint linking this vertebra to the next one
    unsigned int nextKey = (unsigned int)(size_t)FUN_004a5970((void*)(size_t)key);
    RBNode* nextHit;
    if (*mVertebrae.find(&nextHit, &nextKey) == (RBNode*)&mVertebrae.mAnchor) {
      bAbort = true;
      break;
    }
    cSPEditorVertebraInfo* nextInfo = &mVertebrae[nextKey];

    float halfWidth = mVertebraHalfWidth;
    float fStep = (halfWidth * 2.0f) * 0.25f;
    float fUp = fStep + halfWidth;
    float fBack = halfWidth - 0.025f;
    float fDown = -halfWidth - fStep;

    float vA[4] = {0.0f, 0.0f, 0.0f, fDown};
    float vB[4] = {fBack, 0.0f, 0.0f, 0.0f};
    FUN_0108ba70(vA, vB);
    void* planar = nextInfo->mpPlanarConstraint;
    if (planar) {
      char dummy;
      mpHavokWorld_14->removeConstraint(&dummy, planar);
      nextInfo->mpPlanarConstraint = 0;
    }

    hkRefObj* hinge = hkAlloc(0x90);
    FUN_0108ae30(hinge);
    hkLimitedHingeConstraintData* hd = (hkLimitedHingeConstraintData*)hinge;

    float a[16] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float b[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    hd->setInBodySpace(*(hkTransform*)b, *(hkTransform*)a, *(hkTransform*)b, *(hkTransform*)b,
                       *(hkTransform*)a, *(hkTransform*)a);

    hd->mSpineChainDamping = mSpineChainDamping;
    hd->mSpineHingeAngularLimitsTauFactor = mSpineHingeAngularLimitsTauFactor;
    hd->mAxisA[0] = fBack;
    hd->mAxisA[1] = 0.0f;
    hd->mAxisA[2] = 0.0f;
    hd->mAxisA[3] = fUp;
    hd->mAxisB[0] = fBack;
    hd->mAxisB[1] = 0.0f;
    hd->mAxisB[2] = 0.0f;
    hd->mAxisB[3] = fDown;
    hd->mSpineMassTimesFactor = ((hkRigidBody*)info->mpRigidBody)->mBody->getMass() * 0.7f;
    hd->mSpineChainTau = mSpineChainTau;

    hkRefObj* hingeInst = hkAlloc(0x28);
    hkConstraintInstance* inst2 =
        (hkConstraintInstance*)FUN_0108bf10(hingeInst, mpHavokWorld, info->mpRigidBody, hinge, 1);
    hd->Release();
    mpHavokWorld_14->addConstraint(inst2);
    info->mpHingeConstraint = inst2;

    key = (unsigned int)(size_t)FUN_004a5970((void*)(size_t)key);
  }

  if (bAbort) {
    chainState->Release();
    mpChain = 0;
    return;
  }

  chainState->mSpineMinCollisionDeadZoneDistance = mSpineMinCollisionDeadZoneDistance;
  chainState->mSpineUseFewerAxialConstraints = mSpineUseFewerAxialConstraints ? 1 : 0;
  void* chainBody = FUN_0108acb0(chainState);
  chainState->Release();

  for (unsigned int k = (unsigned int)(size_t)mFirstVertebra; k != 0;
       k = (unsigned int)(size_t)FUN_004a5970((void*)(size_t)k)) {
    RBNode* hit;
    cSPEditorVertebraInfo* vi =
        (*mVertebrae.find(&hit, &k) == (RBNode*)&mVertebrae.mAnchor) ? 0 : &mVertebrae[k];
    FUN_0108ac30(chainBody, vi ? vi->mpRigidBody : 0);
  }

  mpHavokWorld_14->addConstraint(chainBody);
  ((hkRefObj*)chainBody)->Release();
  FUN_005d1ba0();
  mpChain = chainBody;
}

// @ 0x005D2480
void cSpine76::FUN_005d2480(int key) {
  if (key == 0) return;
  cSPEditorBlock* block = (cSPEditorBlock*)key;

  unsigned int keyLocal = (unsigned int)key;
  RBNode* node;
  cSPEditorVertebraInfo* info = (*mVertebrae.find(&node, &keyLocal) == (RBNode*)&mVertebrae.mAnchor)
                                    ? 0
                                    : &mVertebrae[keyLocal];

  FUN_005cdae0(info);

  __declspec(align(16)) hkTransform xf = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                                          0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  xf.m[12] = block->mField48;
  xf.m[13] = block->mField4c;
  xf.m[14] = block->mField50;
  xf.m[15] = 0.0f;

  float f = block->mField1d8;

  HavokAlignedRoutine(&block->mOrientation60[0], &xf);
  SpineBigStub(&xf, 0);

  int out[4];
  int* p = AddVertebraBody(out, f, xf);
  info->mpRigidBody = (void*)(size_t)p[0];
  info->mpHingeConstraint = (void*)(size_t)p[1];
  info->mpPlanarConstraint = (void*)(size_t)p[2];
  info->mOrderInSpine = p[3];
}

}  // namespace SP

using SP::cSPEditorBlock;
using SP::cSPEditorVertebraInfo;
using SP::cSpine76;
using SP::RBNode;
using SP::RBTreeIncrement;
using SP::hkRefObj;
using SP::hkRigidBody;
using SP::hkTransform;

// @ 0x005D25C0
void cSpine76::FUN_005d25c0(unsigned int key) {
  RBNode* node;
  cSPEditorVertebraInfo* info =
      (*mVertebrae.find(&node, &key) == (RBNode*)&mVertebrae.mAnchor) ? 0 : &mVertebrae[key];

  int order = info->mOrderInSpine;
  if (order < 0 || order >= mVertebrae.mnSize) return;

  unsigned int it = (unsigned int)(size_t)mFirstVertebra;
  if (it == 0) return;

  int idx = -order;
  while (it != 0) {
    RBNode* hit;
    cSPEditorVertebraInfo* itInfo =
        (*mVertebrae.find(&hit, &it) == (RBNode*)&mVertebrae.mAnchor) ? 0 : &mVertebrae[it];

    int j = (idx >= 0) ? idx : order;
    float f;
    if (j < mMaxFlexIndex) {
      f = (1.0f - cosf((float)j * 3.1415927f / (float)mMaxFlexIndex)) * 0.5f;
    } else {
      f = 1.0f;
    }

    hkRigidBody* body = (hkRigidBody*)itInfo->mpRigidBody;
    hkRigidMotion* motion = body->mBody;
    motion->mLinearDamping =
        mScaleOfLeastFlexibility + (mSpineLooseLinearDamping - mScaleOfLeastFlexibility) * f;
    motion->mAngularDamping = mSpineDampingMaxInfluenceDistance +
                              (mSpineLooseAngularDamping - mSpineDampingMaxInfluenceDistance) * f;

    it = (unsigned int)(size_t)FUN_004a5970((void*)(size_t)it);
    ++idx;
    --order;
  }
}
