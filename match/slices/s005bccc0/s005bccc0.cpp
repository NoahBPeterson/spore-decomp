// Slice s005bccc0 -- SP::cSPEditorManipulation* (Spore creature editor)
// Flags for this region: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <string.h>

typedef unsigned int size_t;
void* operator new(size_t n, const char* name, int a, int b, int c, int d);   // EA 6-arg operator new (0x00f473a0)
void* operator new(size_t n, const char* name, int a, int b, const char* file, int line);
void RBTreeInsert(void* node, void* parent, void* anchor, int side);   // 0x009216a0
void operator_delete__(void* p);                                              // 0x00f47380

struct cSPEditorPileList { void* p0; void* p1; void* p2; };

struct Vec3 { float x, y, z; Vec3() {} Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; } };
typedef Vec3 Vec3C;
inline void* operator new(size_t, void* p, int) { return p; }

struct Mat3 {                       // 3x3 float matrix, by-value copies go through Matrix3::Assign (0x0041cb40)
    float m[9];
    Mat3() {}
    Mat3(const Mat3& o) { Assign(o); }
    void Assign(const Mat3& o);     // @ 0x0041cb40
};

// ---------------------------------------------------------------- Havok-ish helpers
struct hkVector4 { float x, y, z, w; };
struct hkMotionState { char pad[0x40]; Vec3 pos; };                 // position at +0x40
struct hkRigidBody {
    char pad[0x1c];
    char collidable[0x3c];          // +0x1c
    hkMotionState* mpMotion;        // +0x58
    void setPosition(const hkVector4& p);   // @ 0x01087820
};
struct hkLinearCastInput {          // at +0x90 of the frame
    hkVector4 to;
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
struct hkWorld {
    void linearCast(void* collidable, hkLinearCastInput* in, CdCollector* collector, void* startCollector);   // @ 0x01082b90
};
struct cSPEditorPhysicsWorld {
    char pad[0xc];
    int* mpFloorBody;               // +0xc
    hkWorld* World();               // @ 0x004b91c0
    void SetDefaultFloorFilter();   // @ 0x004b9470
    void UpdateCollisionFilters();  // @ 0x004b9420
};

// ---------------------------------------------------------------- editor model / spine / block
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
struct cSPEditorModel {
    virtual void v0();
    RefCountV rc;                   // +4 vptr, +8 count
    char pad0[0x24];
    void AddRef() { rc.AddRef(); }
    cSPEditorPhysicsWorld* GetWorld();   // @ 0x004ad450
    void SetFlag(int v);                 // @ 0x004ad470
    void SetColliding(bool b);           // @ 0x004adc20
    bool IsColliding();                  // @ 0x004adc40
    float GetScale();                    // @ 0x004adaa0
};
struct cSPEditorSpine {
    virtual void v0();
    virtual int AddRef();           // +4
    virtual int Release();          // +8
    char pad[0xe8 - 4];
    int mnVertebrae;                // +0xe8
    void Prepare();                 // @ 0x005d2790
    void Update(int a, cSPEditorModel* m);   // @ 0x005d07f0
};

struct cSPEditorBlock {
    char pad0[0x28];
    cSPEditorModel* mpModel;        // +0x28
    char pad1[0x48 - 0x2c];
    Vec3 mPosition;                 // +0x48
    char pad2[0x60 - 0x54];
    Mat3 mOrientation;              // +0x60
    char pad3[0xa8 - 0x84];
    Mat3 mBaseOrientation;          // +0xa8
    char pad4[0x18c - 0xcc];
    hkRigidBody* mpBody;            // +0x18c
    char pad5[0x33c - 0x190];
    cSPEditorBlock* mpParent;       // +0x33c
    char pad6[0x3c9 - 0x340];
    char mbOnFloor;                 // +0x3c9
    char pad7[0x3e0 - 0x3ca];
    cSPEditorBlock* mpSymmetric;    // +0x3e0
    char pad8[0xdc8 - 0x3e4];
    uint32_t mFlagsA;               // +0xdc8
    uint32_t mFlagsB;               // +0xdcc
    void GetBBox(float* out6, int a, int b, int c);      // @ 0x0044ae00
    int GetSymmetryIndex();                                // @ 0x0044f220
    int CalculateSymmetrySign();                           // @ 0x0044f240
    void SetModelBasedOnSymmetrySign(int sign, int a, int b, int c, int d);   // @ 0x00439110
    void RecursiveFlagA();                                 // @ 0x0044ede0
    char Unk43bbc0(int a);                                 // @ 0x0043bbc0
    void DetachFrom(cSPEditorBlock* b);                    // @ 0x00438a40 (called on the parent)
};

struct cIVisualEffect { virtual void v0(); virtual void v1(); virtual void v2(); virtual void Update(int a); };  // slot 3 @ +0xc

struct IAnimEvent {                 // cSPEditorAnimatedEventInfo (refcounted message)
    virtual void v0();
    virtual int AddRef();           // +4
    virtual int Release();          // +8
    IAnimEvent* Construct();        // @ 0x0059d960
    void MessagePost(uint32_t id, int a, void* obj, int b, int c, float d, int e, int f, float g);   // @ 0x0059d840
};

namespace EditorUtils {
    void DeleteInvalidBlocks(int count, int flag);                     // 0x004a6f10
    void RepinBlockToTorso(cSPEditorBlock* b, Vec3 pos, Mat3 rot, int flag);   // 0x0049fbd0
    void SetSymmetricBlocksUIState(cSPEditorBlock* b, cSPEditorPileList* pile, int flag);   // 0x004a7f30
    float GetAlignmentPosition(cSPEditorBlock* b, cSPEditorPileList* pile, Vec3 start, Mat3 rot2,
                               Vec3* cand, Mat3* local, char* flag, int one, Mat3 rot1);   // 0x00490a70
}
bool FUN_004a0900(cSPEditorBlock* b, cSPEditorPileList* pile, Vec3 origin, Vec3 dir, Vec3* out);   // 0x004a0900
void* FUN_004a37f0(void* tmpVec, cSPEditorModel* m, uint32_t id);                                   // 0x004a37f0
void FUN_004a6690(cSPEditorBlock* b, cSPEditorPileList* pile, int a, int c, int d);                // 0x004a6690
void FUN_004a6d20(cSPEditorBlock* b, cSPEditorPileList* pile, int flag, int a, int c, int d, int e, int f);   // 0x004a6d20
void FUN_004a7dd0(cSPEditorBlock* b);                                                               // 0x004a7dd0
void FUN_004a88d0(uint32_t id);                                                                     // 0x004a88d0
void FUN_0049bcc0(cSPEditorBlock* b, Vec3 origin, Vec3 dir, Vec3 a, Vec3 b2, int one);              // 0x0049bcc0
void* FUN_0067cac0(uint32_t id, int a);                                                             // 0x0067cac0
void FUN_0067c8c0(void* p);                                                                         // 0x0067c8c0 (thiscall on result)
struct cViewer {
    void GetWorldRayFromScreenCoords(float x, float y, Vec3* origin, Vec3* dir);   // 0x007c4730
};
struct cIAppViewer {                 // cIApp: GetViewer is vtable slot 22 (+0x58)
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual cViewer* GetViewer();    // +0x58
};
namespace SP {
    cIAppViewer* App();              // 0x0067dd10
    inline cViewer* GetViewer() { return App()->GetViewer(); }
}

extern uint32_t gUIStateIdOn;    // 0x015ea8e4
extern uint32_t gUIStateIdOff;   // 0x015ea87c

struct cEffectVec {              // eastl::vector<cIVisualEffect*, sp_vector_allocator>
    cIVisualEffect** mpBegin;
    cIVisualEffect** mpEnd;
    cIVisualEffect** mpCapacity;
    cEffectVec& operator=(const cEffectVec& o);   // @ 0x005bc9b0
};
struct cTempVec { cIVisualEffect** mpBegin; cIVisualEffect** mpEnd; cIVisualEffect** mpCapacity; };

namespace SP {

// ---------------------------------------------------------------- spine resize (existing, byte-exact)
class cSPEditorManipulationSpineResize {
 public:
  char pad[0x78];
  // @ 0x005bdc80
  cSPEditorPileList GetPileList();
};

// @ 0x005bdc80
cSPEditorPileList cSPEditorManipulationSpineResize::GetPileList() {
  cSPEditorPileList v;
  v.p0 = 0;
  v.p1 = 0;
  v.p2 = 0;
  return v;
}

// ---------------------------------------------------------------- StackingSimple
class cSPEditorManipulationStackingSimple {
 public:
  void* vtbl0;                       // +0x00
  char mChangedObject;               // +0x04
  char pad05[0x1c - 5];
  cSPEditorBlock* mpBlock;           // +0x1c
  char mNewAttachment;               // +0x20
  char pad21[3];
  cSPEditorBlock* mpOriginalParent;  // +0x24
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
  bool DoOnMouseMove(float x, float y, int flags);
};

// @ 0x005bccc0
bool cSPEditorManipulationStackingSimple::DoOnMouseMove(float x, float y, int flags)
{
    cSPEditorBlock* block = mpBlock;
    mX = x;
    mY = y;
    cSPEditorModel* model = block->mpModel;
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
    cSPEditorBlock* oldParent = block->mpParent;
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
        hkRigidBody* body = block->mpBody;

        float bbox[6];
        block->GetBBox(bbox, 0, 0, 0);
        float cx = (bbox[0] + bbox[3]) * 0.5f - block->mPosition.x;
        float cy = (bbox[1] + bbox[4]) * 0.5f - block->mPosition.y;
        float cz = ((bbox[2] + bbox[5]) * 0.5f + 0.02f) - block->mPosition.z;
        Vec3 T;
        T.x = origin.x + cx;
        T.y = origin.y + cy;
        T.z = origin.z + cz;
        hkVector4 hp;
        hp.x = T.x; hp.y = T.y; hp.z = T.z; hp.w = 0.0f;
        body->setPosition(hp);

        hkLinearCastInput in;
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
        cSPEditorBlock* parent = block->mpParent;
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

// ---------------------------------------------------------------- TranslateCreature
struct cLimb { void Unk48a4c0(); };   // @ 0x0048a4c0

struct cSPEditorManipulationBase { virtual ~cSPEditorManipulationBase() {} char pad[0x10]; };
struct cRefCountBase { virtual ~cRefCountBase() {} int mnRefCount; };

struct PosMapAnchor {
    uint32_t right, left, parent, color;
};
struct PosMap {                        // eastl::map<cSPEditorBlock*, Vec3>: rbtree at +0
    uint32_t pad0;
    PosMapAnchor anchor;               // +4
    uint32_t mnSize;                   // +0x14
    char pad18[0x1c - 0x18];
    ~PosMap() { DoNukeSubtree((void*)anchor.parent); }
    void DoNukeSubtree(void* node);   // @ 0x009a9600 (rbtree::DoNukeSubtree)
    struct Value { uint32_t key; Vec3C v; Value() {} Value(const Value& o) : key(o.key), v(o.v) {} };
    struct Iter { void* node; };
    Iter* DoInsertValueImpl(Iter* out, void* hint, const Value* v, bool bForceToLeft);   // 0x005bdb60
};

struct ModelRef {                      // EA::AutoRefCount<cSPEditorModel>
    cSPEditorModel* mpObject;
    ~ModelRef() { if (mpObject) mpObject->rc.Release(); }
    ModelRef& operator=(cSPEditorModel* p)
    {
        if (p != mpObject) {
            cSPEditorModel* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->rc.Release();
        }
        return *this;
    }
};
struct SpineRef {                      // EA::AutoRefCount<cSPEditorSpine>
    cSPEditorSpine* mpObject;
    ~SpineRef() { if (mpObject) mpObject->Release(); }
    SpineRef& operator=(cSPEditorSpine* p)
    {
        if (p != mpObject) {
            cSPEditorSpine* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
struct cSPVec { cSPEditorBlock** mpBegin; cSPEditorBlock** mpEnd; cSPEditorBlock** mpCapacity;
                ~cSPVec() { if (mpBegin && ((int*)mpBegin)[-1]) operator_delete__(mpBegin); } };

class cSPEditorManipulationTranslateCreature : public cSPEditorManipulationBase, public cRefCountBase {
 public:
  ModelRef mModel;                   // +0x1c
  SpineRef mSpine;                   // +0x20
  cSPVec mLimbs;                     // +0x24
  char pad30[0x38 - 0x30];
  bool mModelUsingSymmetry;          // +0x38
  char pad39[3];
  Vec3 mOriginalPlanarPosition;      // +0x3c
  PosMap mOriginalPositions;         // +0x48

  // @ 0x005bd650
  bool OnMouseUp(int a, int b, int c, int d);
  // @ 0x005bd750
  void SetTargets(cSPEditorModel* model, cSPEditorSpine* spine);
  // @ 0x005bd7c0
  Vec3* PickPlaneOfSymmetry(Vec3* out, float x, float y, float unused);
  // @ 0x005bdad0
  ~cSPEditorManipulationTranslateCreature();
};

// @ 0x005bd650
bool cSPEditorManipulationTranslateCreature::OnMouseUp(int, int, int, int)
{
    if (mModel.mpObject)
        mModel.mpObject->SetColliding(mModelUsingSymmetry);
    if (mSpine.mpObject) {
        mSpine.mpObject->Prepare();
        mSpine.mpObject->Update(0, mModel.mpObject);
    }
    bool colliding = mModel.mpObject->IsColliding();
    mModel.mpObject->SetColliding(false);
    int n = (int)(mLimbs.mpEnd - mLimbs.mpBegin);
    for (int i = 0; i < n; i++)
        ((cLimb*)mLimbs.mpBegin[i])->Unk48a4c0();
    mModel.mpObject->SetColliding(colliding);
    EditorUtils::DeleteInvalidBlocks(mSpine.mpObject->mnVertebrae, 0);
    IAnimEvent* evt;
    void* mem = operator new(0x30, "Editor", 0, 0, 0, 0);
    evt = mem ? ((IAnimEvent*)mem)->Construct() : 0;
    if (evt)
        evt->AddRef();
    evt->MessagePost(0xd77440ff, 0, mModel.mpObject, 0, 0, 0.0f, 0, -1, 1.0f);
    if (evt)
        evt->Release();
    return false;
}

// @ 0x005bd750
void cSPEditorManipulationTranslateCreature::SetTargets(cSPEditorModel* model, cSPEditorSpine* spine)
{
    mModel = model;
    mSpine = spine;
}

// @ 0x005bdad0
cSPEditorManipulationTranslateCreature::~cSPEditorManipulationTranslateCreature()
{
    // members are destroyed in reverse order: mOriginalPositions, mLimbs, mSpine, mModel
}

// @ 0x005bdb60
PosMap::Iter* PosMap::DoInsertValueImpl(Iter* out, void* hint, const Value* v, bool bForceToLeft)
{
    int side;                          // RBTreeSide: left = 0, right = 1
    if (bForceToLeft || hint == (void*)&anchor || v->key < *(uint32_t*)((char*)hint + 0x10))
        side = 0;
    else
        side = 1;
    char* node = (char*)operator new(0x20, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (node + 0x10, 0) Value(*v);
    RBTreeInsert(node, hint, &anchor, side);
    mnSize++;
    out->node = node;
    return out;
}

// @ 0x005bd7c0
Vec3* cSPEditorManipulationTranslateCreature::PickPlaneOfSymmetry(Vec3* out, float x, float y, float)
{
    Vec3 o, d;
    SP::GetViewer()->GetWorldRayFromScreenCoords(x, y, &o, &d);

    // direction to the origin in the ground plane
    float inv = 1.0f / sqrtf((-o.x) * (-o.x) + (-o.y) * (-o.y));
    float nx = -o.x * inv;
    float ny = -o.y * inv;
    float dotx = fabsf((inv * 0.0f + ny) * 0.0f + nx);

    Vec3 n;                              // candidate plane normal
    n.x = 1.0f; n.y = 0.0f; n.z = 0.0f;
    if (dotx < 0.5f) {
        float s = 1.0f;
        if ((o.x > 0.0f && o.y < 0.0f) || (o.x < 0.0f && o.y > 0.0f))
            s = -1.0f;
        float t = dotx * 2.0f;
        n.x = t;
        n.y = -s * t + s;
        n.z = t * 0.0f;
    }
    Vec3 p = mOriginalPlanarPosition;
    *out = p;
    float denom = d.x * n.x + d.y * n.y + d.z * n.z;
    if (denom != 0.0f) {
        float t = -((o.x * n.x + o.y * n.y + o.z * n.z) - (p.x * n.x + p.y * n.y + p.z * n.z)) / denom;
        if (t >= 0.0f) {
            out->x = 0.0f;
            out->y = d.y * t + o.y;
            out->z = d.z * t + o.z;
            return out;
        }
    }
    // second try: horizontal plane through the original position
    float denom2 = (d.y + d.x) * 0.0f + d.z;
    if (denom2 != 0.0f) {
        float t = -(((o.y + o.x) * 0.0f + ((p.y + p.x) * -0.0f - p.z)) + o.z) / denom2;
        if (t >= 0.0f) {
            out->x = 0.0f;
            out->y = d.y * t + o.y;
            out->z = d.z * t + o.z;
        }
    }
    return out;
}

}  // namespace SP
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct cViewer {
    void GetWorldRayFromScreenCoords(float, float, void*, void*); // 0x007c4730
};
}
