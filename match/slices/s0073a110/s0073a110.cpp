// Slice s0073a110 — graphics/model helpers (SP::cModelInstance and Simulator ability classes).
//
// Optimized /O2 module (no frame pointer).  Retail layout differs from the 2008 dev PDB and the
// 2017 ModAPI, so member offsets below are placed at the offsets observed in the disassembly; gaps
// are pad.  Flags: /O2 /MD /Gy /EHsc /TP /GS- (no stack cookie in these small functions).

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef int int32_t;
typedef unsigned char uint8_t;

#include <intrin.h>

// ---------------------------------------------------------------------------
// Shared refcounted object: vtable at +0, refcount at +4.
// ---------------------------------------------------------------------------
class RefObj {
public:
    virtual void vfunc0(int) = 0;   // slot 0
    virtual void vfunc1() = 0;      // slot 1
    int mnRefCount;                 // +4
};

struct RefPtr {
    RefObj* mpObj;                  // +0
    void Release();
};

// @ 0x0073A820
void RefPtr::Release()
{
    RefObj* p = mpObj;
    if (p != 0) {
        int n = (*(volatile int*)&p->mnRefCount += -1);
        if (n == 0) {
            (*(volatile int*)&p->mnRefCount) = 1;
            _ReadWriteBarrier();
            p->vfunc0(1);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x0073A800 — set two flag bits (bit0 from arg1, bit1 from arg2) on a +8 dword.
// ---------------------------------------------------------------------------
struct FlagObj {
    char pad[8];
    uint32_t mFlags;                // +8
    void SetFlags(bool a, bool b);
};

void FlagObj::SetFlags(bool a, bool b)
{
    if (a)
        mFlags |= 1;
    if (b)
        mFlags |= 2;
}

// ---------------------------------------------------------------------------
// @ 0x0073A7A0 — copy a 0x24-byte matrix block to *out, then return true.
// ---------------------------------------------------------------------------
struct Mat24 { int d[9]; };

struct MatOwner {
    char pad0[0x14];
    Mat24 mMat;                     // +0x14
    bool GetMat(Mat24* out);
};

bool MatOwner::GetMat(Mat24* out)
{
    for (int i = 0; i < 9; ++i)
        out->d[i] = 0;
    for (int i = 0; i < 9; ++i)
        out->d[i] = mMat.d[i];
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x0073A850 — scale the upper-left 3x3 of a packed 3x3 source by src->scale
// into a padded 4x4 destination and copy the translation.
// ---------------------------------------------------------------------------
struct Mat43In {
    int f0;             // +0
    union { float tx; int txBits; };    // +4
    union { float ty; int tyBits; };    // +8
    union { float tz; int tzBits; };    // +0xc
    float scale;        // +0x10
    float r[3][3];      // +0x14 (packed, stride 3)
    // +0x38 ...
};

struct Mat44Out {
    float r[3][4];      // +0..+0x2c (padded, stride 4)
    float tx, ty, tz;   // +0x30
};

int ScaleMat(const Mat43In* src, Mat44Out* dst)
{
    const float s = src->scale;
    dst->r[0][0] = src->r[0][0] * s;
    dst->r[0][1] = src->r[0][1] * s;
    dst->r[0][2] = src->r[0][2] * s;
    dst->r[1][0] = src->r[1][0] * s;
    dst->r[1][1] = src->r[1][1] * s;
    dst->r[1][2] = src->r[1][2] * s;
    dst->r[2][0] = src->r[2][0] * s;
    dst->r[2][1] = src->r[2][1] * s;
    dst->r[2][2] = src->r[2][2] * s;
    dst->tx = src->tx;
    dst->ty = src->ty;
    const int tz = src->tzBits;     // eax is left holding the last copied word
    dst->tz = src->tz;
    return tz;
}

// ---------------------------------------------------------------------------
// SP::cModelInstance — retail member offsets observed in the disassembly.
// ---------------------------------------------------------------------------
namespace SP {

// 8-byte animation/bone group record (cAnimGroupInfo).
struct cAnimGroupInfo {
    char  mBindingIdx;      // +0
    char  mBoneCount;       // +1
    short mBoneOffset;      // +2
    char  mAnimCount;       // +4
    char  mAnimFirstDeform; // +5
    short mAnimOffset;      // +6
};

struct cAnimDef { char pad0[8]; int mId; char pad0c[0x14]; float mLength; };   // KeyframeAnimation (id +8, length +0x20)
struct cIdObj { char pad0[0x10]; int mId; };           // +0x10 id
struct cBindInfo {
    char pad0[0xc];
    cIdObj* m0c;                                       // +0x0c
    cIdObj* m10;                                       // +0x10
    char pad14[4];
    int m18;                                           // +0x18
};
struct cBlender {                                      // cMultiBlender-like player
    char pad0[4];
    void** mVptr4;                                     // +0x04 (vtable of the played interface)
    char pad8[0x14];
    cAnimDef* mDef;                                    // +0x1c
    float mTime;                                       // +0x20
    bool AnyAnimating();                               // 0x0075a6e0 cMultiBlender::AnyAnimating
    void SetAnimating(cAnimDef* a, bool v);            // 0x0075b6e0 cMultiBlender::SetAnimating
    void SetLooping(bool v);                           // 0x0075a770 (byte at +0x50)
    void SetAnim(cAnimDef* a, float start);            // 0x011fdba0
};
struct cBinding {                                      // 12-byte binding record
    cBlender* mBlender;                                // +0
    bool mActive;                                      // +4
    bool mLoop;                                        // +5
    short pad6;
    cBindInfo* mInfo;                                  // +8
};
struct cMaterial {                                     // 0xc4-byte record, same prefix as cBinding
    cBlender* mBlender;
    bool mActive;
    bool mLoop;
    short pad6;
    cBindInfo* mInfo;
    char pad0c[0xc4 - 0xc];
};
struct cCtrlEntry { int mKey; cAnimDef* mDef; };       // 8 bytes

struct AnimGroupVec {
    cAnimGroupInfo* mpBegin;
    cAnimGroupInfo* mpEnd;
    cAnimGroupInfo* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    cAnimGroupInfo& operator[](int i) { return mpBegin[i]; }
};

class cModelInstance {
public:
    char pad0[8];                   // +0x00
    unsigned mFlags8;               // +0x08 (bit 0x20: multi-blender mode)
    int  mFieldC;                   // +0x0c
    int  mField10;                  // +0x10
    AnimGroupVec mAnimGroups;       // +0x14 (begin/end/cap; size() and operator[] stay inline calls)
    char pad20[0x28 - 0x20];
    cMaterial* mMaterials;          // +0x28
    cMaterial* mMaterialsEnd;       // +0x2c
    char pad30[0x3c - 0x30];
    cBinding* mBindABegin;          // +0x3c
    cBinding* mBindAEnd;            // +0x40
    char pad44[0x50 - 0x44];
    cBinding* mBindCBegin;          // +0x50
    cBinding* mBindCEnd;            // +0x54
    char pad58[0x78 - 0x58];
    int* mControllers;              // +0x78
    char pad7c[0x154 - 0x7c];
public:
    int GetAnimationMoveToTimes(int animID, int* dst, char bEnd);
    bool SetActive(int key, int groupIdx, bool animating, float t, bool loop);
    bool AdvanceBinding(cBinding* b, float dt);
    bool IsValidGroup(int i) {
        return i >= 0 && i < mAnimGroups.size();
    }
};

// @ 0x0073ABB0
int cModelInstance::GetAnimationMoveToTimes(int animID, int* dst, char bEnd)
{
    if (!IsValidGroup(animID))
        return 0;
    cAnimGroupInfo* e = &mAnimGroups[animID];
    int start = e->mAnimOffset;
    int n = e->mAnimCount;
    if (bEnd) {
        start += e->mAnimFirstDeform;
        n -= e->mAnimFirstDeform;
    }
    if (dst != 0 && n > 0) {
        int i = 0;
        do {
            // the controller table is re-read every step: the store through dst may alias it
            dst[i] = *(const int*)((const char*)mControllers + start * 8 + i * 8);
            ++i;
        } while (i < n);
    }
    return n;
}

} // namespace SP

// ---------------------------------------------------------------------------
// SP::cModelInstance::SetActive: activate / deactivate every binding whose controller matches `key`.
namespace SP {
static __forceinline void ApplyBinding(cModelInstance* mi, cBinding* b, cAnimDef* target, bool animating, float t, bool loop)
{
    if (mi->mFlags8 & 0x20) {
        cBlender* bl = b->mBlender;
        bl->SetAnimating(target, animating);
        bl->SetLooping(!loop);
        b->mActive = true;
    } else {
        cBlender* bl = b->mBlender;
        if (animating) {
            if (target != bl->mDef || !b->mActive) {
                if (target != bl->mDef)
                    bl->SetAnim(target, t);
                b->mActive = true;
            }
        } else if (target == bl->mDef) {
            b->mActive = false;
        }
    }
}

// @ 0x0073AC20
bool cModelInstance::SetActive(int key, int groupIdx, bool animating, float t, bool loop)
{
    if (!IsValidGroup(groupIdx))
        return false;
    cAnimGroupInfo* g = &mAnimGroups[groupIdx];
    const int start = g->mAnimOffset;
    const int end = start + g->mAnimCount;
    const int bidx = g->mBindingIdx;
    int bend;
    if (g->mBindingIdx != (char)-1)
        bend = bidx + 1;
    else
        bend = bidx;
    bool result = false;
    for (int i = start; i < end; ++i) {
        if (((cCtrlEntry*)mControllers)[i].mKey == key) {
        cAnimDef* target = ((cCtrlEntry*)mControllers)[i].mDef;
        const int nA = (int)(mBindAEnd - mBindABegin);
        for (int k = 0; k < nA; ++k) {
            cBinding* b = &mBindABegin[k];
            b->mLoop = loop;
            if (b->mInfo->m10->mId == target->mId) {
                ApplyBinding(this, b, target, animating, t, loop);
                result = true;
            }
        }
        for (int j = bidx; j < bend; ++j) {
            cBinding* b = (cBinding*)&mMaterials[j];
            b->mLoop = loop;
            if (b->mInfo->m0c->mId == target->mId) {
                ApplyBinding(this, b, target, animating, t, loop);
                result = true;
            }
        }
        const int nC = (int)(mBindCEnd - mBindCBegin);
        for (int k = 0; k < nC; ++k) {
            cBinding* b = &mBindCBegin[k];
            b->mLoop = loop;
            if (b->mInfo->m18 == target->mId) {
                ApplyBinding(this, b, target, animating, t, loop);
                result = true;
            }
        }
        }
    }
    return result;
}
} // namespace SP

// ---------------------------------------------------------------------------
// The remaining functions in this slice belong to other classes in the same
// region (Simulator ability objects and mesh helpers).  They are reconstructed
// below / summarised; see partial.txt and nonmatching.txt for status.
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// 0x0073A110 — select the model's vertex streams, mirror the selected slot
// headers into the mesh buffers and dispatch the merge/convert step.
// ---------------------------------------------------------------------------
struct StreamSlot {
    int32_t mType;          // +0x00
    int32_t mField04;       // +0x04
    int32_t mSelector;      // +0x08
    int32_t mField0C;       // +0x0c
    uint8_t mPayload[0x10]; // +0x10 (element-stream header / EltArray)
};

struct SampledModel {
    char pad0[8];
    StreamSlot* mpSlots;    // +0x08
};

struct MeshBuffers {
    char pad0[8];
    StreamSlot* mpSlots;    // +0x08
    StreamSlot* mpSlotsEnd; // +0x0c
    void AssignModel(SampledModel* model);                // 0x00738e50
};

struct EltArray {
    int32_t  mNumElts;      // +0x00
    uint8_t* mData;         // +0x04
    uint16_t mEltSize;      // +0x08
    uint16_t mEltStride;    // +0x0a
    void*    mDataRC;       // +0x0c
    void Assign(const uint8_t* payload);                  // 0x00424f70
};

void SelectStreams(SampledModel* model, int count, int* out,
                   const int* ids, int, const int* kinds, int);   // 0x0071ded0
void CopySlot15(const uint8_t* src, uint8_t* dst);                 // 0x007201d0
void UpdateStreamSet(uint32_t count, int selector, EltArray* a, EltArray* b,
                     EltArray* c, EltArray* d, EltArray* e, EltArray* f,
                     EltArray* g, EltArray* h, uint8_t* verts);    // 0x00731e70

// @ 0x0073A110
bool ModelUpdatePass(uint8_t* verts, SampledModel* model, MeshBuffers* buffers)
{
    int out[5];
    const int ids[5]   = { 1, 2, 3, 9, 10 };
    const int kinds[5] = { 3, 0, 0, 0, 0 };
    SelectStreams(model, 5, out, ids, 0, kinds, 0);

    if (out[0] < 0 || out[3] < 0)
        return false;

    StreamSlot* modelSlots = model->mpSlots;
    EltArray*   selected0  = (EltArray*)(modelSlots[out[0]].mPayload);

    EltArray a = { 0, 0, 0, 0, 0 };
    EltArray b = { 0, 0, 0, 0, 0 };
    EltArray c = { 0, 0, 0, 0, 0 };
    EltArray d = { 0, 0, 0, 0, 0 };
    EltArray e = { 0, 0, 0, 0, 0 };
    if (out[1] >= 0)
        a.Assign(modelSlots[out[1]].mPayload);
    if (out[2] >= 0)
        b.Assign(modelSlots[out[2]].mPayload);

    if (buffers->mpSlots == buffers->mpSlotsEnd) {
        buffers->AssignModel(model);
        CopySlot15((const uint8_t*)selected0, buffers->mpSlots[out[0]].mPayload);
        if (out[1] >= 0)
            CopySlot15((const uint8_t*)&a, buffers->mpSlots[out[1]].mPayload);
        if (out[2] >= 0)
            CopySlot15((const uint8_t*)&b, buffers->mpSlots[out[2]].mPayload);
    }

    StreamSlot* bufferSlots = buffers->mpSlots;
    EltArray* selected3 = (EltArray*)(bufferSlots[out[0]].mPayload);
    if (out[1] >= 0)
        c.Assign(bufferSlots[out[1]].mPayload);
    if (out[2] >= 0)
        d.Assign(bufferSlots[out[2]].mPayload);

    int selector = 1;
    if (out[4] >= 0) {
        e.Assign(modelSlots[out[4]].mPayload);
        int fmt = modelSlots[out[4]].mSelector;
        if ((unsigned)(fmt - 1) <= 3)
            selector = fmt;
        else if (fmt == 10)
            selector = 4;
    }

    UpdateStreamSet((uint32_t)selector, modelSlots[out[3]].mSelector,
                    (EltArray*)modelSlots[out[3]].mPayload, &e, selected0,
                    selected3, &a, &c, &b, &d, verts);
    return true;
}

// ---------------------------------------------------------------------------
// 0x0073A4B0 — drop the inactive quadric records, remap the per-cluster
// quadric indices and truncate both vectors.
// ---------------------------------------------------------------------------
struct QRecRef {
    virtual void AddRef();      // +0x00
    virtual void Release();     // +0x04
};

struct FixedIdVector6 {         // 0x30-byte id list at QuadricRec+0x14
    uint32_t mData[0x0c];
    FixedIdVector6& operator=(const FixedIdVector6& rhs);      // 0x00719170
};

struct FixedEntryVector3 {      // 0x48-byte entry list at QuadricRec+0x44
    uint32_t mData[0x12];
    void Free(uint32_t* begin, uint32_t* end);                  // 0x004772a0
    void DoAssign(const FixedEntryVector3& rhs, void* ctx);     // 0x0042d020
};

struct QuadricRec {             // 0x8c stride
    uint32_t        mType;      // +0x00
    uint32_t        mFlags04;   // +0x04
    int16_t         mFmt;       // +0x08
    uint16_t        mStride;    // +0x0a
    QRecRef*        mpRef;      // +0x0c
    uint32_t        mIndex;     // +0x10
    FixedIdVector6  mIds;       // +0x14
    FixedEntryVector3 mVerts;   // +0x44
};

struct FaceCluster {            // 0x14 stride at ctx+0x30
    uint32_t mField00;          // +0x00
    int32_t  mQuadIndex;        // +0x04
    int32_t  mBegin;            // +0x08
    int32_t  mEnd;              // +0x0c
    uint32_t mField10;          // +0x10
};

struct SectionVec {              // eastl::vector<QuadricRec>::resize at 0x0071f7e0
    QuadricRec* mpBegin;        // +0x1c
    QuadricRec* mpEnd;          // +0x20
    void resize(int n);
};

struct VecFC {                  // eastl::vector<FaceCluster>::resize at 0x0071efa0
    FaceCluster* mpBegin;       // +0x30
    FaceCluster* mpEnd;         // +0x34
    void resize(unsigned n);
};

struct QuadricCtx {
    char pad0[0x1c];
    SectionVec  mQuads;         // +0x1c
    char pad24[0xc];
    VecFC       mClusters;      // +0x30
};

struct IndexVec {               // inline-capacity int vector built by 0x00737e80
    int* mpBegin;               // +0x00
    int* mpEnd;                 // +0x04
    int* mpCap;                 // +0x08
    char pad0c[4];              // +0x0c
    int* mpInline;              // +0x10 (start of the inline buffer)
    int  mBuf[16];              // +0x18
    void Init_00737e80(int n, int fill);
};

void EASTL_allocator_deallocate(void* p);                        // 0x00f47380

static void CopyQuadric(QuadricRec* dst, QuadricRec* src, void* ctx)
{
    dst->mType    = src->mType;
    dst->mFlags04 = src->mFlags04;
    dst->mFmt     = src->mFmt;
    dst->mStride  = src->mStride;
    if (dst->mpRef != src->mpRef) {
        if (src->mpRef)
            src->mpRef->AddRef();
        QRecRef* old = dst->mpRef;
        dst->mpRef = src->mpRef;
        if (old)
            old->Release();
    }
    dst->mIndex = src->mIndex;
    dst->mIds   = src->mIds;
    dst->mVerts.Free(dst->mVerts.mData, dst->mVerts.mData + 1);
    dst->mVerts.DoAssign(src->mVerts, ctx);
}

// @ 0x0073A4B0
void QuadricVectorResize(QuadricCtx* ctx)
{
    const int count = (int)(ctx->mQuads.mpEnd - ctx->mQuads.mpBegin);

    IndexVec map;
    map.Init_00737e80(count, -1);

    int out = 0;
    for (int i = 0; i < count; ++i) {
        QuadricRec* src = &ctx->mQuads.mpBegin[i];
        if (src->mType == 0)
            continue;
        if (out < i)
            CopyQuadric(&ctx->mQuads.mpBegin[out], src, ctx);
        map.mpBegin[i] = out;
        ++out;
    }
    ctx->mQuads.resize(out);

    const int clusterCount = (int)(ctx->mClusters.mpEnd - ctx->mClusters.mpBegin);
    int written = 0;
    for (int j = 0; j < clusterCount; ++j) {
        FaceCluster* c = &ctx->mClusters.mpBegin[j];
        int idx = map.mpBegin[c->mQuadIndex];
        c->mQuadIndex = idx;
        if (idx != -1 && c->mBegin < c->mEnd) {
            if (written < j)
                ctx->mClusters.mpBegin[written] = *c;
            ++written;
        }
    }
    ctx->mClusters.resize((unsigned)written);

    if (map.mpBegin && map.mpBegin != map.mpInline)
        EASTL_allocator_deallocate(map.mpBegin);
}

// 0x0073A6E0 — ability-object constructor (130 bytes).
struct __declspec(align(16)) Vec4a { float x, y, z, w; };

class __declspec(align(16)) BigObj {
public:
    int f00, f04, f08, f0c;     // +0x00
    int f10;                    // +0x10
    int f14;                    // +0x14
    int f18;                    // +0x18
    int f1c;                    // +0x1c
    Vec4a v20;                  // +0x20
    Vec4a v30;                  // +0x30
    char pad40[0x10];           // +0x40
    int f50;                    // +0x50
    char pad54[0x7c];           // +0x54
    int fd0;                    // +0xd0
    char padd4[0x8];            // +0xd4
    int fdc;                    // +0xdc
    char pade0[0x8];            // +0xe0
    int fe8;                    // +0xe8
    char padec[0x4];            // +0xec
    int ff0;                    // +0xf0
    char padf4[0x4];            // +0xf4
    int ff8;                    // +0xf8
    float ffc;                  // +0xfc
    int f100;                   // +0x100
    int f104;                   // +0x104
    char f108;                  // +0x108
    void Ctor(int a, int b, int c, Vec4a* p4, Vec4a* p5);
};

// @ 0x0073a6e0
void BigObj::Ctor(int a, int b, int c, Vec4a* p4, Vec4a* p5)
{
    f00 = a; f04 = b; f08 = c; f0c = 0;
    fd0 = 0; fdc = 0; f50 = 0;
    ff0 = 0; ff8 = 0; f14 = 0; fe8 = 0;
    v20 = *p4;
    v30 = *p5;
    int t = f1c;
    ffc = 1.0f;
    f100 = 0;
    f18 = t;
    f104 = 0;
    f108 = 0;
}

// ---------------------------------------------------------------------------
// 0x0073A900 — flush the bound resource of a mesh/model owner into its
// hand-off slot, refreshing the cached transforms and the global cell/triple
// state on the way.
// ---------------------------------------------------------------------------
struct ResourceObj {
    virtual void v0();          // +0x00
    void** mpSecondaryVtbl;     // +0x04 (slot 3 is called with this = ResourceObj)
};
typedef void (__thiscall *FnResSlot3)(ResourceObj*);

struct ResSlot {
    void* mpObj;                // +0x00
    void* mpDispatch;           // +0x04
    void* mpAux;                // +0x08
    void Reset();               // 0x007966a0
    void Commit();              // 0x01200940
};

struct BoundTransform {
    uint8_t mFlags;             // +0x00
    char pad01[0xf];
    float mScale;               // +0x10
    char pad14[0x2c];           // +0x40
};
struct BoundTransformB {
    uint8_t mFlags;             // +0x00
    char pad01[0xf];
    float mScale;               // +0x10
    char pad14[0x24];           // +0x38
};

struct BoundResource {
    ResourceObj*    mpResource; // +0x00
    char pad04[4];
    ResSlot*        mpSlot;     // +0x08
    void*           mpCell;     // +0x0c
    BoundTransform  mXformA;    // +0x10
    char pad50[0x30];           // +0x50 .. +0x80
    BoundTransformB mXformB;    // +0x80
    void*           mpTripleA;  // +0xb8
    void*           mpTripleB;  // +0xbc
    void*           mpTripleC;  // +0xc0
};

void SetGlobalCellId(void* cell);                      // 0x00796650
void BuildTransformA(BoundTransformB* t);               // 0x007966f0
void BuildTransformB(BoundTransform* t);                // 0x00796800
void SetGlobalTriple(void* a, void* b, void* c);       // 0x00796680

// @ 0x0073A900
void ReleaseBoundResource(BoundResource* self, void* newObj)
{
    ResSlot* slot = self->mpSlot;
    if (!slot)
        return;
    if (!self->mpResource)
        return slot->Reset();

    ResourceObj* res = self->mpResource;
    ((FnResSlot3)res->mpSecondaryVtbl[3])(res);
    SetGlobalCellId(self->mpCell);
    if (self->mXformB.mScale != 1.0f || (self->mXformB.mFlags & 6) != 0)
        BuildTransformA(&self->mXformB);
    if (self->mXformA.mScale != 1.0f || (self->mXformA.mFlags & 6) != 0)
        BuildTransformB(&self->mXformA);
    if (self->mpTripleA)
        SetGlobalTriple(self->mpTripleA, self->mpTripleC, self->mpTripleB);

    slot->mpObj = self->mpResource;
    if (!newObj)
        return slot->Commit();
    void* old = slot->mpAux;
    slot->mpAux = newObj;
    slot->Commit();
    slot->mpAux = old;
}

// Ability object constructor setting two vtables (81 bytes).
struct AbIface { virtual void ifn0(); };
struct AbRC { AbRC() : mRC(0) {} virtual void rcfn0(); virtual void rcfn1(); int mRC; };
struct AbHeld {
    virtual void dtor(int) = 0;     // +0x00
    virtual void release();         // +0x04
    int mnRefCount;                 // +0x08 (retail reads +4 on the secondary view)
};

// Owning pointer at AbilityA+0xc: destructor drops the held reference.
struct HeldRef {
    AbHeld* mp;
    ~HeldRef()
    {
        AbHeld* p = mp;
        if (p) {
            if (--p->mnRefCount == 0) {
                p->mnRefCount = 1;
                p->dtor(1);
            }
        }
    }
};
struct AbilityA : AbIface, AbRC {
    AbilityA(AbHeld* h, int v) { mHeld.mp = h; if (h) ++h->mnRefCount; mVal = v; }
    virtual void a0();
    virtual void a1();
    HeldRef mHeld;      // +0xc
    int mVal;           // +0x10
    ~AbilityA();
};
struct AbPtr {
    AbHeld* p;
    AbPtr() : p(0) {}
    ~AbPtr() { if (p) p->release(); }
};
struct AbilityB : AbilityA {
    AbilityB(AbHeld* h, int v, int a, int b);
    virtual void b0();
    virtual void b1();
    AbPtr mHeld2;       // +0x14
    int mB18;           // +0x18
    int mB1c;           // +0x1c
    ~AbilityB();
};

// @ 0x0073AA70
AbilityB::AbilityB(AbHeld* h, int v, int a, int b) : AbilityA(h, v), mB18(a), mB1c(b)
{
}

// @ 0x0073A9E0 — reset the two AbilityA vtables and release the held reference.
AbilityA::~AbilityA()
{
}

// @ 0x0073AAE0 — release the secondary held pointer, then run the AbilityA dtor.
AbilityB::~AbilityB()
{
}

// @ 0x0073AB40 — assign a refcounted controller field and refresh two words (96 bytes).
struct CtrlObj {
    void** vftable;                 // +0
    int mnRefCount;                 // +4
    char pad8[0x90 - 8];            // +8 .. +0x90
    long long mCounter;             // +0x90
};

struct CtrlHolder {
    char pad0[0xf0];
    CtrlObj* mCtrl;                 // +0xf0
    long long mCounter2;            // +0xf8
    void SetController(CtrlObj* p);
};

void CtrlHolder::SetController(CtrlObj* p)
{
    CtrlObj* old = mCtrl;
    if (p != old) {
        if (p != 0)
            ++p->mnRefCount;
        mCtrl = p;
        if (old != 0) {
            int n = (*(volatile int*)&old->mnRefCount += -1);
            if (n == 0) {
                (*(volatile int*)&old->mnRefCount) = 1;
                _ReadWriteBarrier();
                ((void(__thiscall*)(CtrlObj*, int))old->vftable[0])(old, 1);
            }
        }
    }
    mCounter2 = p->mCounter - 1;
}

// Advance one binding's blender by dt (clamped at the animation end for looping bindings).
namespace SP {
// @ 0x0073AF20
bool cModelInstance::AdvanceBinding(cBinding* b, float dt)
{
    cBlender* bl = b->mBlender;
    if (bl != 0 && b->mActive) {
        if (mFlags8 & 0x20) {
            if (bl->AnyAnimating()) {
                cBlender* c = b->mBlender;
                ((void(__thiscall*)(cBlender*, float))c->mVptr4[0])(c, dt);
                return true;
            }
        } else {
            float len = bl->mDef->mLength;
            if (b->mLoop && len <= bl->mTime + dt) {
                dt = len - bl->mTime;
                b->mActive = false;
            }
            ((void(__thiscall*)(cBlender*, float))bl->mVptr4[0])(bl, dt);
            return true;
        }
    }
    return false;
}
} // namespace SP
