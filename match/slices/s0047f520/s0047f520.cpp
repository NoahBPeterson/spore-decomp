// Slice s0047f520: SP::cSPEditorHandle subclasses (BallConnector, Deform) -- /Od code.
// Retail layouts differ from the 2008 PDB for the Deform class (retail string is at +0x11c,
// mSetPickData at +0x118), so members are named by role and retail offset.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef int16_t  i16;

struct Vec3 { float x, y, z; };
struct Mat3 { float m[9]; Mat3* Assign(const void* src); };   // Assign 0x41cb40
struct cMWModel {
    char pad0[8];
    u16 mFlags;      // +8
    i16 mCount;      // +10
    Vec3 mPos;       // +0xc
    char pad18[4];   // +0x18
    Mat3 mBasis;     // +0x1c
    char pad40[4];   // +0x40
    u32 mGroups[2];  // +0x44
};

// cIModelManager / ModelManager interface; GetGroupID is virtual slot 0x28
struct cSPModelManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual u32 GetGroupID(u32 name, int flag);   // slot 0x28
};

extern cSPModelManager* ModelManager();       // 0x0067dd80 (SP::ModelManager)
extern void* EditorTuning();                  // 0x00401070 tuning struct, Vec3 members at +0x6c.. +0x90
extern void __fastcall Transform_Ctor(void* t);             // 0x409930 (ecx = &mTransform)
extern void __fastcall TrianglePinningInfo_Ctor(void* p);   // 0x4e8f70 (ecx = this)
extern void  operator_delete_array(void* p);        // 0x00f47380, cdecl 1 arg
extern const float kDeformVec0;  // 0x15d4fd8
extern const float kDeformVec1;  // 0x15d4fdc
extern const float kDeformVec2;  // 0x15d4fe0
extern const float kDefaultHandleOffset[3];                // 0x15d4aa8
extern const float kPreviewDelta;                          // 0x1471064 (0.5f)
extern char gEmptyString[];                                // 0x1667bac

// base-class methods (single ecx arg -> free __fastcall reproduces thiscall)
extern void __fastcall cSPEditorHandle_Shutdown(void* self);   // 0x47e2c0 SP::cSPEditorHandle::Shutdown
extern void __fastcall cSPEditorHandle_BaseDtor(void* self);   // 0x47d870 ~cSPEditorHandle
extern void __fastcall cSPEditorHandle_BaseCtor(void* self);   // 0x47d6a0 ctor

// opaque transform-ops object (0x38 bytes) with an in-place Assign / Apply
struct cSPTransformOps {
    u32 raw[0x38 / 4];
    cSPTransformOps* Assign(const void* src);   // 0x537dc0
    void Apply(Vec3* v);                        // 0x44d4f0
};

struct cSPEditorBlock;
struct cModelDeformationHandle;

// a refcounted object released through vtable slot 1
struct IRefCounted { virtual void q0(); virtual void Release(); };

struct cSPEditorTrianglePinningInfo {
    u32 mField0;             // +0
    void* mpRef4;            // +4 (IRefCounted)
    void Update();           // 0x4ae250
};

// Common handle layout (retail, 0x50 bytes)
struct cSPEditorHandle {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void PlaceHandle();                    // slot 5 (+0x14)
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual void GetHandlePosition(Vec3* out);     // slot 9 (+0x24)
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    void* mRefCountVft;                    // +4
    char pad8[8];
    cSPEditorBlock* mBlock;                // +0x10
    cMWModel* mModel;                      // +0x14
    cMWModel* mOverdrawModel;              // +0x18
    char pad1c[0x34];

    int Init(cSPEditorBlock* block, bool b, u32 a, u32 c);   // 0x47db30 (returns self)
};

struct cSPEditorBlock {
    char pad0[0x10];
    void* mp10;                            // +0x10
    char pad14[4];
    void* mp18;                            // +0x18
    void GetTransform(cSPTransformOps* out);   // 0x4362a0
};

struct cModelDeformationHandle {
    u32 mField0;                 // +0
    cSPTransformOps mTransform;  // +4
    u32 mField3c;                // +0x3c
    Vec3 mVec40;                 // +0x40
    Vec3 mVec4c;                 // +0x4c
    float mFloat58;              // +0x58
    cModelDeformationHandle* Copy(const cModelDeformationHandle* src);  // 0x47fda0
};

struct cSPEditorHandleDeform : cSPEditorHandle {
    cModelDeformationHandle mData;             // +0x50 (0x5c bytes)
    u32  mPinningType;                         // +0xac
    u32  mAxisToIgnore;                        // +0xb0
    cSPEditorHandleDeform* mSymmetricHandle;   // +0xb4
    char padb8[0x118 - 0xb8];
    u8   mSetPickData;                         // +0x118
    char pad119[3];
    char* mpSoundBegin;                        // +0x11c
    char* mpSoundEnd;                          // +0x120
    char* mpSoundCap;                          // +0x124
    char pad128[4];                            // +0x128
    Vec3 mVec12c;                              // +0x12c
    Vec3 mVec138;                              // +0x138
    Vec3 mVec144;                              // +0x144
    char pad150[0x184 - 0x150];
    float mPreviewDelta;                       // +0x184
    cSPEditorTrianglePinningInfo mTriangleInfo; // +0x188
    char pad190[0x1d4 - 0x190];
    u8 mIsHiddenHandle;                        // +0x1d4
    u8 mDoNotPlaceHandle;                      // +0x1d5

    void SetFade(float f);                                        // 0x4809a0
    void SetData(const cModelDeformationHandle* data, bool flag); // 0x47fd30
    void UpdateDirection(bool flag);                              // 0x47fe20
    void Init(cSPModelManager* mgr, cSPEditorBlock* block,
              const cModelDeformationHandle* data, bool flag);    // 0x480030
};

extern void __fastcall cSPEditorHandleDeform_Shutdown(cSPEditorHandle* self);   // 0x47fcb0

// @ 0x47f520
void __fastcall BallConnector_Dtor(cSPEditorHandle* self)
{
    *(void**)self = (void*)0x13ef1c0;
    self->mRefCountVft = (void*)0x13ef1ac;
    cSPEditorHandle_Shutdown(self);
    cSPEditorHandle_BaseDtor(self);
}

struct BallConnectorIface { void* QueryInterface(u32 id); };

// @ 0x47f550  (QueryInterface-style: returns this for 3 known interface IDs)
void* BallConnectorIface::QueryInterface(u32 id)
{
    switch (id) {
    case 0xee3f516e: return this;
    case 0x050a1fe5: return this;
    case 0x050e8e23: return this;
    }
    return 0;
}

static __forceinline void SetGroupBit(cMWModel* m, u32 bit)
{
    if (bit < 0x40)
        m->mGroups[bit >> 5] |= 1u << (bit % 32);
}

// @ 0x47f5a0  push position + orientation to both models' transform components
void __fastcall cSPEditorHandle_UpdateModelTransforms(cSPEditorHandle* self)
{
    Vec3 pos;
    Mat3 rot;
    self->GetHandlePosition(&pos);
    rot.Assign((char*)self->mBlock + 0x60);
    cMWModel* m = self->mModel;
    if (m) {
        u16* f = (u16*)((char*)m + 8);
        *(Vec3*)(f + 2) = pos;
        f[0] |= 4;
        *(i16*)(f + 1) += 1;
        u16* g = (u16*)((char*)self->mModel + 8);
        *(Mat3*)((char*)g + 0x14) = rot;
        g[0] |= 2;
        *(i16*)(g + 1) += 1;
    }
    cMWModel* od = self->mOverdrawModel;
    if (od) {
        u16* f = (u16*)((char*)od + 8);
        *(Vec3*)(f + 2) = pos;
        f[0] |= 4;
        *(i16*)(f + 1) += 1;
        u16* g = (u16*)((char*)self->mOverdrawModel + 8);
        *(Mat3*)((char*)g + 0x14) = rot;
        g[0] |= 2;
        *(i16*)(g + 1) += 1;
    }
}

// @ 0x47f720
int __fastcall BallConnector_Init(cSPEditorHandle* self, int /*edx*/, void* param)
{
    int r = self->Init((cSPEditorBlock*)param, true, 0, 0);
    if (!self->mBlock)
        return r;
    if (self->mModel)
        SetGroupBit(self->mModel, ModelManager()->GetGroupID(0x900c6cdd, 0));
    if (self->mOverdrawModel) {
        SetGroupBit(self->mOverdrawModel, ModelManager()->GetGroupID(0x22fff11, 0));
        SetGroupBit(self->mOverdrawModel, ModelManager()->GetGroupID(0x900c6cdd, 0));
    }
    return (int)(size_t)self;
}

// @ 0x47f960  handle position: block's vec at +0x48, or a default constant
Vec3* __fastcall cSPEditorHandle_GetBlockOffset(cSPEditorHandle* self, int /*edx*/, Vec3* out)
{
    if (self->mBlock) {
        out->x = *(float*)((char*)self->mBlock + 0x48);
        out->y = *(float*)((char*)self->mBlock + 0x4c);
        out->z = *(float*)((char*)self->mBlock + 0x50);
    } else {
        out->x = kDefaultHandleOffset[0];
        out->y = kDefaultHandleOffset[1];
        out->z = kDefaultHandleOffset[2];
    }
    return out;
}

// @ 0x47f9e0
Vec3* __fastcall cSPEditorHandle_GetTuningVec90(void* self, int /*edx*/, Vec3* out)
{
    Vec3* v = (Vec3*)((char*)EditorTuning() + 0x90);
    *out = *v;
    return out;
}

// @ 0x47fa30  SP::cSPEditorHandleDeform::cSPEditorHandleDeform
void* __fastcall cSPEditorHandleDeform_Ctor(cSPEditorHandle* self)
{
    cSPEditorHandle_BaseCtor(self);
    *(void**)self = (void*)0x13ef270;
    self->mRefCountVft = (void*)0x13ef25c;
    Transform_Ctor((char*)self + 0x54);
    cSPEditorHandleDeform* d = (cSPEditorHandleDeform*)self;
    d->mPinningType = 0x95f07f3d;
    d->mAxisToIgnore = 0;
    d->mSymmetricHandle = 0;
    d->mSetPickData = 0;
    d->mpSoundBegin = 0;
    d->mpSoundEnd = 0;
    d->mpSoundCap = 0;
    d->mpSoundBegin = gEmptyString;
    d->mpSoundEnd = d->mpSoundBegin;
    d->mpSoundCap = d->mpSoundBegin + 1;
    for (int off = 0; off < 3; off++) {
        Vec3* v = (Vec3*)((char*)d + 0x12c + off * 0xc);
        v->x = kDeformVec0;
        v->y = kDeformVec1;
        v->z = kDeformVec2;
    }
    d->mPreviewDelta = kPreviewDelta;
    TrianglePinningInfo_Ctor((char*)self + 0x188);
    d->mDoNotPlaceHandle = 0;
    return self;
}

// @ 0x47fc10  Deform destructor
void __fastcall cSPEditorHandleDeform_Dtor(cSPEditorHandle* self)
{
    *(void**)self = (void*)0x13ef270;
    self->mRefCountVft = (void*)0x13ef25c;
    cSPEditorHandleDeform* d = (cSPEditorHandleDeform*)self;
    cSPEditorHandleDeform_Shutdown(self);
    void* held = d->mTriangleInfo.mpRef4;
    if (held)
        ((IRefCounted*)held)->Release();
    if (d->mpSoundCap - d->mpSoundBegin > 1) {
        if (d->mpSoundBegin)
            operator_delete_array(d->mpSoundBegin);
    }
    cSPEditorHandle_BaseDtor(self);
}

// @ 0x47fcb0  Deform shutdown
void __fastcall cSPEditorHandleDeform_Shutdown(cSPEditorHandle* self)
{
    cSPEditorHandle_Shutdown(self);
    ((cSPEditorHandleDeform*)self)->mSymmetricHandle = 0;
    ((cSPEditorHandleDeform*)self)->mTriangleInfo.Update();
}

struct DeformIface { void* QueryInterface(u32 id); };

// @ 0x47fce0
void* DeformIface::QueryInterface(u32 id)
{
    switch (id) {
    case 0xee3f516e: return this;
    case 0x050a1fe5: return this;
    case 0x050a993c: return this;
    }
    return 0;
}

// @ 0x47fd30
void cSPEditorHandleDeform::SetData(const cModelDeformationHandle* data, bool flag)
{
    mData.Copy(data);
    if (mBlock) {
        cSPTransformOps xf;
        mBlock->GetTransform(&xf);
        xf.Apply(&mData.mVec40);
        xf.Apply(&mData.mVec4c);
    }
    UpdateDirection(flag);
}

// @ 0x47fda0  copy cModelDeformationHandle (0x5c bytes)
cModelDeformationHandle* cModelDeformationHandle::Copy(const cModelDeformationHandle* src)
{
    mField0 = src->mField0;
    mTransform.Assign(&src->mTransform);
    mField3c = src->mField3c;
    mVec40 = src->mVec40;
    mVec4c = src->mVec4c;
    mFloat58 = src->mFloat58;
    return this;
}

extern Vec3* Vec3_Sub(Vec3* out, void* a, void* b);                       // FUN_0041db10
extern Mat3* Mat3_FromXform(void* out, void* xf);                         // FUN_0041ded0
extern Vec3* Mat3_TransformDir(Vec3* out, Mat3* m, Vec3* v);              // FUN_0047ff90
extern Vec3* Vec3_Normalize(Vec3* out, Vec3* v);                          // FUN_00436ce0
extern float Vec3_Dot(Vec3* a, void* b);                                  // FUN_00455cc0

// @ 0x47fe20
void cSPEditorHandleDeform::UpdateDirection(bool flag)
{
    if (!flag) {
        float d = mData.mFloat58;
        if (d < 0.0f || 1.0f < d)
            SetFade(0.0f);
        else
            SetFade(d);
    }
    Vec3 dir;
    Vec3 tmp = *Vec3_Sub(&dir, &mData.mVec4c, &mData.mVec40);
    char xf[0x24];
    Mat3 m = *Mat3_FromXform(xf, (char*)mBlock->mp10 + 0x1c);
    tmp = *Mat3_TransformDir(&dir, &m, &tmp);
    Vec3 nrm;
    Vec3* n = Vec3_Normalize(&nrm, &tmp);
    mVec12c = *n;
    PlaceHandle();
}

// @ 0x47ff90  three dot products of a vector against rows of a 3x3 matrix
Vec3* Mat3_TransformDir_(Vec3* out, char* mat, void* v)
{
    float a = Vec3_Dot((Vec3*)v, mat);
    float b = Vec3_Dot((Vec3*)v, mat + 0xc);
    float c = Vec3_Dot((Vec3*)v, mat + 0x18);
    out->x = a; out->y = b; out->z = c;
    return out;
}

// @ 0x480030  SP::cSPEditorHandleDeform::Init
void cSPEditorHandleDeform::Init(cSPModelManager* mgr, cSPEditorBlock* block,
                                 const cModelDeformationHandle* data, bool flag)
{
    mData.Copy(data);
    cSPEditorHandle::Init(block, flag, 0, 0);
    if (mModel)
        SetGroupBit(mModel, mgr->GetGroupID(0x1ba53ea, 0));
    if (mOverdrawModel) {
        SetGroupBit(mOverdrawModel, mgr->GetGroupID(0x1ba53eb, 0));
        SetGroupBit(mOverdrawModel, mgr->GetGroupID(0x22fff11, 0));
    }
    mIsHiddenHandle = 0;
    SetData(data, false);
}

// @ 0x480280  handle colour/vec chosen by pinning type (+0x8c) from EditorTuning
Vec3* __fastcall Deform_GetTuningVec(char* self, int /*edx*/, Vec3* out)
{
    char* t = (char*)EditorTuning();
    u32 k = *(u32*)(self + 0x8c);
    if (k == 0x503283aa)      *out = *(Vec3*)(t + 0x78);
    else if (k == 0xe20e2032) *out = *(Vec3*)(t + 0x84);
    else                      *out = *(Vec3*)(t + 0x6c);
    return out;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
