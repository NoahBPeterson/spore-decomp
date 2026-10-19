// src/game/SPEditors/SPEditorManipulationStackingSimple.cpp -- migrated from slice(s) s005bccc0, s005bc0f0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorManipulationStackingSimple.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorManipulationObject.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
#include <new>
#include <math.h>
#include "SP/cSPEditorAnimatedEventInfo.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorPhysicsWorld.h"
#include "SP/cSPEditorSpine.h"
#include "SP/cViewer.h"
#include <string.h>

// ---- items of slice s005bc0f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
struct cSPVector3_s005b_c0f0 { float x, y, z; cSPVector3_s005b_c0f0() {} cSPVector3_s005b_c0f0(float a, float b, float c) : x(a), y(b), z(c) {} };
namespace EA {
template <typename T>
class AutoRefCount_s005b_c0f0 {
 public:
  T* mpObject;
  AutoRefCount_s005b_c0f0() : mpObject(0) {}
  AutoRefCount_s005b_c0f0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005b_c0f0() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005b_c0f0& operator=(T* p) {
    if (p != mpObject) { T* t = mpObject; if (p) p->AddRef(); mpObject = p; if (t) t->Release(); }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005b_c0f0 {
 public:
  RefCountVTemplate_s005b_c0f0() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005b_c0f0() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace eastl {
template <typename T>
class sp_vector {
 public:
  T* mpBegin; T* mpEnd; T* mpCapacity; int mAllocator[2];
  ~sp_vector() { if (mpBegin && ((int*)mpBegin)[-1] != 0) EASTL_allocator_deallocate(mpBegin); }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  sp_vector& operator=(const sp_vector& x);
};
}
namespace SP {
class cSPEditorBlock_s005b_c0f0 {
 public:
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  char pad04[0x33c - 4];
  void* m33c;                       // +0x33c
  cSPEditorBlock_s005b_c0f0** mChildrenBegin;  // +0x340
  cSPEditorBlock_s005b_c0f0** mChildrenEnd;    // +0x344
};
}
namespace SP {
class cSPEditorManipulationObject_s005b_c0f0 {
 public:
  __declspec(noinline) cSPEditorManipulationObject_s005b_c0f0();
  virtual ~cSPEditorManipulationObject_s005b_c0f0() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};
}
namespace SP {
class cSPEditorManipulationStackingSimple : public cSPEditorManipulationObject_s005b_c0f0, public EA::RefCountVTemplate_s005b_c0f0<int> {
 public:
  EA::AutoRefCount_s005b_c0f0<cSPEditorBlock_s005b_c0f0> mBlock;                            // +0x1c
  bool mNewAttachment;                                                // +0x20
  char pad21[0x24 - 0x21];
  cSPEditorBlock_s005b_c0f0* mOriginalParent;                                    // +0x24
  eastl::sp_vector<EA::AutoRefCount_s005b_c0f0<cSPEditorBlock_s005b_c0f0> > mPileList;      // +0x28
  eastl::sp_vector<void*> mEffectList;                                // +0x3c
  cSPVector3_s005b_c0f0 mMouseOffset;                                            // +0x50
  float mX;                                                           // +0x5c
  float mY;                                                           // +0x60
  cSPVector3_s005b_c0f0 mOriginalMouseOffset;                                    // +0x64
  bool mUnk70;                                                        // +0x70

  cSPEditorManipulationStackingSimple();
  ~cSPEditorManipulationStackingSimple();
  void Init(cSPEditorBlock_s005b_c0f0** block, cSPVector3_s005b_c0f0 offset);
  bool DoOnMouseDown();
  void Other1();
  void Other2();
};
}
namespace SP {
volatile int g_s59_sink;
}
namespace SP {
__declspec(noinline) cSPEditorManipulationObject_s005b_c0f0::cSPEditorManipulationObject_s005b_c0f0() { g_s59_sink = 1; }
}
// ---- items of slice s005bc0f0 end

// ---- items of slice s005bccc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gUIStateIdOn;    // 0x015ea8e4
extern uint32_t gUIStateIdOff;   // 0x015ea87c
void operator_delete__(void* p);                                              // 0x00f47380
struct cSPEditorPileList { void* p0; void* p1; void* p2; };
struct Vec3 { float x, y, z; Vec3() {} Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; } };
struct Mat3 {                       // 3x3 float matrix, by-value copies go through Matrix3::Assign (0x0041cb40)
    float m[9];
    Mat3() {}
    Mat3(const Mat3& o) { Assign(o); }
    void Assign(const Mat3& o);     // @ 0x0041cb40
};
struct hkVector4_s005b_ccc0 { float x, y, z, w; };
struct hkMotionState { char pad[0x40]; Vec3 pos; };                 // position at +0x40
struct hkRigidBody_s005b_ccc0 {
    char pad[0x1c];
    char collidable[0x3c];          // +0x1c
    hkMotionState* mpMotion;        // +0x58
    void setPosition(const hkVector4_s005b_ccc0& p);   // @ 0x01087820
};
struct hkLinearCastInput_s005b_ccc0 {          // at +0x90 of the frame
    hkVector4_s005b_ccc0 to;
    float maxExtraPenetration;
    float startPointTolerance;
};
struct CdCollector {                // closest-point collector at +0xd0 of the frame
    void* vptr;                     // 0x013ef52c
    float earlyOutDistance;
    char pad[0x24];
    float hitFraction;              // +0x2c
    int numHits;                    // +0x30
    char pad2[4];
    int* hitBody;                   // +0x38
};
struct hkWorld_s005b_ccc0 {
    void linearCast(void* collidable, hkLinearCastInput_s005b_ccc0* in, CdCollector* collector, void* startCollector);   // @ 0x01082b90
};
struct cSPEditorPhysicsWorld_s005b_ccc0 {
    char pad[0xc];
    int* mpFloorBody;               // +0xc
    hkWorld_s005b_ccc0* World();               // @ 0x004b91c0
    void SetDefaultFloorFilter();   // @ 0x004b9470
    void UpdateCollisionFilters();  // @ 0x004b9420
};
struct RefCountV {                  // EA::RefCountVTemplate<int> sub-object (vptr + count)
    virtual ~RefCountV() {}
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    __forceinline int Release()
    {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) {
            mnRefCount = 1;
            delete this;
        }
        return n;
    }
};
struct cSPEditorModel_s005b_ccc0 {
    virtual void v0();
    RefCountV rc;                   // +4 vptr, +8 count
    char pad0[0x24];
    void AddRef() { rc.AddRef(); }
    cSPEditorPhysicsWorld_s005b_ccc0* GetWorld();   // @ 0x004ad450
    void SetFlag(int v);                 // @ 0x004ad470
    void SetColliding(bool b);           // @ 0x004adc20
    bool IsColliding();                  // @ 0x004adc40
    float GetScale();                    // @ 0x004adaa0
};
struct cSPEditorBlock_s005b_ccc0 {
    char pad0[0x28];
    cSPEditorModel_s005b_ccc0* mpModel;        // +0x28
    char pad1[0x48 - 0x2c];
    Vec3 mPosition;                 // +0x48
    char pad2[0x60 - 0x54];
    Mat3 mOrientation;              // +0x60
    char pad3[0xa8 - 0x84];
    Mat3 mBaseOrientation;          // +0xa8
    char pad4[0x18c - 0xcc];
    hkRigidBody_s005b_ccc0* mpBody;            // +0x18c
    char pad5[0x33c - 0x190];
    cSPEditorBlock_s005b_ccc0* mpParent;       // +0x33c
    char pad6[0x3c9 - 0x340];
    char mbOnFloor;                 // +0x3c9
    char pad7[0x3e0 - 0x3ca];
    cSPEditorBlock_s005b_ccc0* mpSymmetric;    // +0x3e0
    char pad8[0xdc8 - 0x3e4];
    uint32_t mFlagsA;               // +0xdc8
    uint32_t mFlagsB;               // +0xdcc
    void GetBBox(float* out6, int a, int b, int c);      // @ 0x0044ae00
    int GetSymmetryIndex();                                // @ 0x0044f220
    int CalculateSymmetrySign();                           // @ 0x0044f240
    void SetModelBasedOnSymmetrySign(int sign, int a, int b, int c, int d);   // @ 0x00439110
    void RecursiveFlagA();                                 // @ 0x0044ede0
    char Unk43bbc0(int a);                                 // @ 0x0043bbc0
    void DetachFrom(cSPEditorBlock_s005b_ccc0* b);                    // @ 0x00438a40 (called on the parent)
};
struct cIVisualEffect { virtual void v0(); virtual void v1(); virtual void v2(); virtual void Update(int a); };  // slot 3 @ +0xc
namespace EditorUtils {
    void RepinBlockToTorso(cSPEditorBlock_s005b_ccc0* b, Vec3 pos, Mat3 rot, int flag);   // 0x0049fbd0
}
namespace EditorUtils {
    void SetSymmetricBlocksUIState(cSPEditorBlock_s005b_ccc0* b, cSPEditorPileList* pile, int flag);   // 0x004a7f30
}
namespace EditorUtils {
    float GetAlignmentPosition(cSPEditorBlock_s005b_ccc0* b, cSPEditorPileList* pile, Vec3 start, Mat3 rot2,
                               Vec3* cand, Mat3* local, char* flag, int one, Mat3 rot1);   // 0x00490a70
}
bool FUN_004a0900(cSPEditorBlock_s005b_ccc0* b, cSPEditorPileList* pile, Vec3 origin, Vec3 dir, Vec3* out);   // 0x004a0900
void* FUN_004a37f0(void* tmpVec, cSPEditorModel_s005b_ccc0* m, uint32_t id);                                   // 0x004a37f0
void FUN_004a6690(cSPEditorBlock_s005b_ccc0* b, cSPEditorPileList* pile, int a, int c, int d);                // 0x004a6690
void FUN_004a6d20(cSPEditorBlock_s005b_ccc0* b, cSPEditorPileList* pile, int flag, int a, int c, int d, int e, int f);   // 0x004a6d20
void FUN_004a7dd0(cSPEditorBlock_s005b_ccc0* b);                                                               // 0x004a7dd0
void FUN_004a88d0(uint32_t id);                                                                     // 0x004a88d0
void FUN_0049bcc0(cSPEditorBlock_s005b_ccc0* b, Vec3 origin, Vec3 dir, Vec3 a, Vec3 b2, int one);              // 0x0049bcc0
void* FUN_0067cac0(uint32_t id, int a);                                                             // 0x0067cac0
void FUN_0067c8c0(void* p);                                                                         // 0x0067c8c0 (thiscall on result)
struct cViewer_s005b_ccc0 {
    void GetWorldRayFromScreenCoords(float x, float y, Vec3* origin, Vec3* dir);   // 0x007c4730
};
struct cIAppViewer {                 // cIApp: GetViewer is vtable slot 22 (+0x58)
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual cViewer_s005b_ccc0* GetViewer();    // +0x58
};
namespace SP {
    cIAppViewer* App();              // 0x0067dd10
}
namespace SP {
    inline cViewer_s005b_ccc0* GetViewer() { return App()->GetViewer(); }
}
struct cEffectVec {              // eastl::vector<cIVisualEffect*, sp_vector_allocator>
    cIVisualEffect** mpBegin;
    cIVisualEffect** mpEnd;
    cIVisualEffect** mpCapacity;
    cEffectVec& operator=(const cEffectVec& o);   // @ 0x005bc9b0
};
struct cTempVec { cIVisualEffect** mpBegin; cIVisualEffect** mpEnd; cIVisualEffect** mpCapacity; };
namespace SP {
class cSPEditorManipulationStackingSimple_s005b_ccc0 {
 public:
  void* vtbl0;                       // +0x00
  char mChangedObject;               // +0x04
  char pad05[0x1c - 5];
  cSPEditorBlock_s005b_ccc0* mpBlock;           // +0x1c
  char mNewAttachment;               // +0x20
  char pad21[3];
  cSPEditorBlock_s005b_ccc0* mpOriginalParent;  // +0x24
  cSPEditorPileList mPileList;       // +0x28 (taken by address)
  char pad34[0x3c - 0x34];
  cEffectVec mEffectList;            // +0x3c
  char pad48[0x50 - 0x48];
  Vec3 mMouseOffset;                 // +0x50
  float mX;                          // +0x5c
  float mY;                          // +0x60
  Vec3 mOriginalMouseOffset;         // +0x64
  char mbFlag70;                     // +0x70

  // @ 0x005bccc0
  bool DoOnMouseMove(float x, float y, int flags);  // 0x005bccc0 (SP::cSPEditorManipulationStackingSimple::DoOnMouseMove)
};
}
// ---- items of slice s005bccc0 end

// @ 0x005bc630
namespace SP {
void cSPEditorManipulationStackingSimple::Other2()
{}
}  // namespace SP

// @ 0x005bc7f0
namespace SP {
void cSPEditorManipulationStackingSimple::Init(cSPEditorBlock_s005b_c0f0** block, cSPVector3_s005b_c0f0 offset)
{
  mBlock = *block;
  mMouseOffset = offset;
  mOriginalMouseOffset = offset;
  if (mBlock)
    mOriginalParent = (cSPEditorBlock_s005b_c0f0*)mBlock->m33c;
  mNewAttachment = false;
}
}  // namespace SP

// @ 0x005bc860
namespace SP {
cSPEditorManipulationStackingSimple::cSPEditorManipulationStackingSimple()
{
  mBlock = (cSPEditorBlock_s005b_c0f0*)0;
  mPileList.mpBegin = 0;
  mPileList.mpEnd = 0;
  mPileList.mpCapacity = 0;
  mMouseOffset = cSPVector3_s005b_c0f0(0.0f, 0.0f, 0.0f);
  mEffectList.mpBegin = 0;
  mEffectList.mpEnd = 0;
  mEffectList.mpCapacity = 0;
  mOriginalMouseOffset = cSPVector3_s005b_c0f0(0.0f, 0.0f, 0.0f);
  mUnk70 = false;
  mChangedObject = false;
}
}  // namespace SP

// @ 0x005bc930
namespace SP {
cSPEditorManipulationStackingSimple::~cSPEditorManipulationStackingSimple()
{}
}  // namespace SP

// @ 0x005bc9b0
namespace eastl {
template <typename T> sp_vector<T>& sp_vector<T>::operator=(const sp_vector<T>& x)
{
  if (this != &x) {
    mpBegin = x.mpBegin;
    mpEnd = x.mpEnd;
    mpCapacity = x.mpCapacity;
  }
  return *this;
}
}  // namespace eastl

// @ 0x005bcaa0
namespace SP {
bool cSPEditorManipulationStackingSimple::DoOnMouseDown()
{ return false; }
}  // namespace SP

// @ 0x005bccc0
namespace SP {
bool cSPEditorManipulationStackingSimple_s005b_ccc0::DoOnMouseMove(float x, float y, int flags)
{
    cSPEditorBlock_s005b_ccc0* block = mpBlock;
    mX = x;
    mY = y;
    cSPEditorModel_s005b_ccc0* model = block->mpModel;
    if (model)
        model->AddRef();
    block = mpBlock;
    Vec3 startPos = block->mPosition;
    Mat3 localRot;
    localRot.Assign(block->mOrientation);

    Vec3 origin, dir;
    SP::GetViewer()->GetWorldRayFromScreenCoords(x, y, &origin, &dir);

    block = mpBlock;
    origin.x = mMouseOffset.x + origin.x;
    origin.y = mMouseOffset.y + origin.y;
    origin.z = mMouseOffset.z + origin.z;
    uint32_t flagsA = block->mFlagsA;
    cSPEditorBlock_s005b_ccc0* oldParent = block->mpParent;
    uint32_t stacked = 0;
    Vec3 snapOffset;
    bool attached = FUN_004a0900(block, &mPileList, origin, dir, &snapOffset);
    bool bit12 = (flagsA >> 12) & 1;

    Vec3 cand;
    if (!attached) {
        cand = startPos;
        if (bit12) {
            mMouseOffset = mOriginalMouseOffset;
            // mEffectList.erase(begin, end)
            cIVisualEffect** first = mEffectList.mpBegin;
            cIVisualEffect** last = mEffectList.mpEnd;
            memcpy(first, last, (char*)last - (char*)last);
            mEffectList.mpEnd -= (last - first);
            block = mpBlock;
            if (((block->mFlagsB >> 12) & 1) || ((block->mFlagsB >> 13) & 1)) {
                cTempVec tmp;
                cTempVec* r = (cTempVec*)FUN_004a37f0(&tmp, block->mpModel, 0x6027fb5a);
                mEffectList = *(cEffectVec*)r;
                if (tmp.mpBegin && ((int*)tmp.mpBegin)[-1])
                    operator_delete__(tmp.mpBegin);
            }
        }
        if (mpBlock->mpParent)
            mpBlock->mpParent->DetachFrom(mpBlock);
        FUN_004a6690(mpBlock, &mPileList, 0, 1, 1);
        block = mpBlock;
        hkRigidBody_s005b_ccc0* body = block->mpBody;

        float bbox[6];
        block->GetBBox(bbox, 0, 0, 0);
        float cx = (bbox[0] + bbox[3]) * 0.5f - block->mPosition.x;
        float cy = (bbox[1] + bbox[4]) * 0.5f - block->mPosition.y;
        float cz = ((bbox[2] + bbox[5]) * 0.5f + 0.02f) - block->mPosition.z;
        Vec3 T;
        T.x = origin.x + cx;
        T.y = origin.y + cy;
        T.z = origin.z + cz;
        hkVector4_s005b_ccc0 hp;
        hp.x = T.x; hp.y = T.y; hp.z = T.z; hp.w = 0.0f;
        body->setPosition(hp);

        hkLinearCastInput_s005b_ccc0 in;
        in.to.x = dir.x * 100.0f + T.x;
        in.to.y = dir.y * 100.0f + T.y;
        in.to.z = dir.z * 100.0f + T.z;
        in.to.w = 0.0f;
        in.maxExtraPenetration = 0.0f;
        in.startPointTolerance = 1.1920929e-07f;
        CdCollector col;
        col.vptr = (void*)0x013ef52c;
        col.earlyOutDistance = 3.4028199e+38f;
        col.hitFraction = 3.4028199e+38f;
        col.numHits = 0;
        model->GetWorld()->World()->linearCast(&body->collidable, &in, &col, 0);

        char onFloor = 0;
        if (col.numHits != 0) {
            int* hit = col.hitBody;
            int* hb = hit + hit[4];
            stacked = 1;
            if ((int*)((char*)hit + hit[4]) == model->GetWorld()->mpFloorBody) {
                onFloor = 1;
                stacked = 0;
            }
            hkMotionState* ms = body->mpMotion;
            float t = col.hitFraction;
            float u = 1.0f - t;
            cand.x = (u * ms->pos.x + t * in.to.x) - cx;
            cand.y = (u * ms->pos.y + t * in.to.y) - cy;
            cand.z = (u * ms->pos.z + t * in.to.z) - cz;
            (void)hb;
        }
        block = mpBlock;
        block->mbOnFloor = onFloor;
        if (block->mpSymmetric)
            block->mpSymmetric->mbOnFloor = onFloor;
        FUN_004a7dd0(mpBlock);

        if ((char)stacked == 0) {
            float len = sqrtf(origin.y * origin.y + origin.x * origin.x);
            float inv = 1.0f / len;
            Vec3 n;
            n.x = inv * origin.x;
            n.y = origin.y * inv;
            n.z = inv * 0.0f;
            float s = model->GetScale();
            Vec3 a;
            a.x = -n.x * s;
            a.y = -n.y * s;
            a.z = -n.z * s;
            FUN_0049bcc0(mpBlock, origin, dir, a, n, 1);
        } else {
            EditorUtils::RepinBlockToTorso(mpBlock, cand, mpBlock->mBaseOrientation, 0);
        }
        cand = mpBlock->mPosition;
        localRot.Assign(mpBlock->mOrientation);
        char flagC = mpBlock->Unk43bbc0(0);
        float score = EditorUtils::GetAlignmentPosition(mpBlock, &mPileList, startPos, mpBlock->mBaseOrientation, &cand, &localRot, &flagC, 1, mpBlock->mBaseOrientation);
        if (mpBlock->mpModel)
            mpBlock->mpModel->GetScale();
        if (score > -1.0f) {
            EditorUtils::RepinBlockToTorso(mpBlock, cand, mpBlock->mBaseOrientation, 0);
            block = mpBlock;
            block->mbOnFloor = flagC;
            if (block->mpSymmetric)
                block->mpSymmetric->mbOnFloor = flagC;
            if (!mbFlag70) {
                FUN_004a88d0(gUIStateIdOn);
                mbFlag70 = 1;
            }
        } else if (mbFlag70) {
            FUN_004a88d0(gUIStateIdOff);
            mbFlag70 = 0;
        }
        model->SetFlag(0);
        model->GetWorld()->SetDefaultFloorFilter();
        model->GetWorld()->UpdateCollisionFilters();
        if (model->IsColliding()) {
            int symIdx = mpBlock->GetSymmetryIndex();
            int sign = mpBlock->CalculateSymmetrySign();
            if (sign != symIdx)
                mpBlock->SetModelBasedOnSymmetrySign(sign, 1, 1, 0, 0);
        }
    } else {
        block = mpBlock;
        cSPEditorBlock_s005b_ccc0* parent = block->mpParent;
        if (parent && parent != oldParent && parent->mpSymmetric != oldParent &&
            parent != mpOriginalParent && parent->mpSymmetric != mpOriginalParent &&
            ((block->mFlagsA >> 12) & 1))
            mNewAttachment = 1;
        cIVisualEffect** b = mEffectList.mpBegin;
        if (b != mEffectList.mpEnd) {
            int n = (int)(mEffectList.mpEnd - b);
            for (int i = 0; i < n; i++)
                mEffectList.mpBegin[i]->Update(0);
        }
        mMouseOffset.x = snapOffset.x + mMouseOffset.x;
        mMouseOffset.y = snapOffset.y + mMouseOffset.y;
        mMouseOffset.z = snapOffset.z + mMouseOffset.z;
        block = mpBlock;
        uint32_t fb = block->mFlagsB;
        if ((fb >> 12) & 1)
            FUN_0067c8c0(FUN_0067cac0(0x7918a61c, 1));
        else if ((fb >> 13) & 1)
            FUN_0067c8c0(FUN_0067cac0(0x25180ef4, 1));
    }
    mpBlock->RecursiveFlagA();
    EditorUtils::SetSymmetricBlocksUIState(mpBlock, &mPileList, 0);
    FUN_004a6d20(mpBlock, &mPileList, stacked, 0, 0, 0, 1, 1);
    if (!mChangedObject)
        mChangedObject = 1;
    if (model)
        model->rc.Release();
    return true;
}
}  // namespace SP
