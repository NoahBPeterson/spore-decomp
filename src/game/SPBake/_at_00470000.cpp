// src/game/SPBake/_at_00470000.cpp -- migrated from slice(s) s0047f520, s0047e4b0 by tools/migrate/rewrite.py
// Object file: SPBake/_at_00470000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPMatrix3.h"
#include "cSPVector3.h"
#include "SP/cMWModel.h"
#include "SP/cModelDeformationHandle.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorHandle.h"
#include "SP/cSPEditorHandleDeform.h"
#include "SP/cSPEditorTrianglePinningInfo.h"
#include "cSPTransform.h"

// unnamed retail callees and globals (address in the comment)
extern float g_const_zero;   // 0x015d4578 (equiv t3)
extern float g_const_one;

// ---- items of slice s0047e4b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uintptr_t;
struct Bitset32 {
    uint32_t mWord[1];
    void set(int i, bool value)
    {
        if (i < 32) {
            if (value)
                mWord[i / 32] |= (1u << (i % 32));
            else
                mWord[i / 32] &= ~(1u << (i % 32));
        }
    }
    bool test(int i) const { return (mWord[i / 32] & (1u << (i % 32))) != 0; }
};
struct Vector3 { float x, y, z; };
struct cPropertyList;
struct cSPEditorBlock;
struct cPropertyList {
    void** vptr;
};
struct cSPTransform_s0047_e4b0 {
    uint16_t pad0;                 // +0x00
    uint16_t mModificationCount;   // +0x02
    char     pad4[0x0c];
    float    mScale;               // +0x10
};
struct cMWModel {
    void* mWorld;                 // +0x00
    Bitset32 mFlags;              // +0x04
    cSPTransform_s0047_e4b0 mTransform;      // +0x08
    uint32_t pad1c[9];            // +0x1c
    int    mRefCount;             // +0x40
    uint32_t pad44[2];            // +0x44
    Vector3 mColor;               // +0x4c
    float  mAlpha;                // +0x58
    void AddRef() { mRefCount = mRefCount + 1; }
    void Release();
    void SetFlag(bool b);         // @ 0x00437f70
};
struct Vec3;
struct cSPEditorHandle {
    Vec3* GetTuningVec90(Vec3* out);
    void** vptr;                  // +0x00
    void** vptr2;                 // +0x04
    int    mUnk8;                 // +0x08
    cPropertyList* mPropList;     // +0x0c
    cSPEditorBlock* mBlock;       // +0x10
    cMWModel* mModel;             // +0x14
    cMWModel* mOverdrawModel;     // +0x18
    int    mCurrentState;         // +0x1c
    float  mFadeInTime;           // +0x20
    float  mFadeOutTime;          // +0x24
    float  mAnimateInTime;        // +0x28
    float  mAnimateOutTime;       // +0x2c
    uint32_t mDefaultModelKey[3]; // +0x30
    uint32_t mDefaultOverdrawKey[3]; // +0x3c
    bool   mHasOverdraw;          // +0x48
    float  mDefaultScale;         // +0x4c

    uint32_t SetModelFlags(bool flag, uint8_t highlight);
    void* GetPosition(void* out);
    void* GetZeroVector(void* out);
    float GetHandleAlphaForState(int state);
    float GetOverdrawHandleAlphaForState(int state);
    void* GetHandleColorForState(void* out, int state);
    void* GetOverdrawHandleColorForState(void* out, int state);
    bool IsFlagSet();
    void SetStateFlags();
    uint32_t SetScale(float s);
    void SetState(int state, bool animate);
    cMWModel* GetModel() { return mModel; }
    cMWModel* GetOverdrawModel() { return mOverdrawModel; }
    void BaseConstruct();
    cSPEditorHandle* ConstructDerived();
};
struct cSPEditorBlock {
    char pad[0x48];
    float mPosX, mPosY, mPosZ;    // +0x48
};
extern float g_const_zero;   // 0x015d4578 (equiv t3)
extern float g_const_one;
// ---- items of slice s0047e4b0 end

// ---- items of slice s0047f520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* EditorTuning();                  // 0x00401070 tuning struct, Vec3 members at +0x6c.. +0x90
extern const float kDefaultHandleOffset[3];                // 0x15d4aa8
extern void __fastcall cSPEditorHandle_Shutdown(void* self);   // 0x47e2c0 SP::cSPEditorHandle::Shutdown
extern void __fastcall cSPEditorHandle_BaseDtor(void* self);   // 0x47d870 ~cSPEditorHandle
typedef uint32_t u32;
typedef uint16_t u16;
typedef int16_t  i16;
struct Vec3 { float x, y, z; };
struct Mat3 { float m[9]; Mat3* Assign(const void* src); };   // Assign 0x41cb40
struct cMWModel_s0047_f520 {
    char pad0[8];
    u16 mFlags;      // +8
    i16 mCount;      // +10
    Vec3 mPos;       // +0xc
    char pad18[4];   // +0x18
    Mat3 mBasis;     // +0x1c
    char pad40[4];   // +0x40
    u32 mGroups[2];  // +0x44
};
struct cSPTransformOps {
    u32 raw[0x38 / 4];
    cSPTransformOps* Assign(const void* src);   // 0x537dc0
    void Apply(Vec3* v);                        // 0x44d4f0
};
struct cSPEditorBlock_s0047_f520;
struct cSPEditorHandle_s0047_f520 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void PlaceHandle();                    // slot 5 (+0x14)
virtual void v6();
virtual void v7();
virtual void v8();
    virtual void GetHandlePosition(Vec3* out);     // slot 9 (+0x24)
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
    void* mRefCountVft;                    // +4
    char pad8[8];
    cSPEditorBlock_s0047_f520* mBlock;                // +0x10
    cMWModel_s0047_f520* mModel;                      // +0x14
    cMWModel_s0047_f520* mOverdrawModel;              // +0x18
    char pad1c[0x34];

    int Init(cSPEditorBlock_s0047_f520* block, bool b, u32 a, u32 c);   // 0x47db30 (returns self)
};
struct cSPEditorBlock_s0047_f520 {
    char pad0[0x10];
    void* mp10;                            // +0x10
    char pad14[4];
    void* mp18;                            // +0x18
    void GetTransform(cSPTransformOps* out);   // 0x4362a0
};
struct BallConnectorIface { void* QueryInterface(u32 id); };
// ---- items of slice s0047f520 end

// @ 0x0047e600
void* cSPEditorHandle::GetPosition(void* out)
{
    if (this->mBlock) {
        ((float*)out)[0] = this->mBlock->mPosX;
        ((float*)out)[1] = this->mBlock->mPosY;
        ((float*)out)[2] = this->mBlock->mPosZ;
    } else {
        ((float*)out)[0] = g_const_zero;
        ((float*)out)[1] = g_const_zero;
        ((float*)out)[2] = g_const_zero;
    }
    return out;
}

// @ 0x0047f3b0
void cSPEditorHandle::SetStateFlags()
{
    ((void(__thiscall*)(cSPEditorHandle*, int, int))this->vptr[0xc])(this, 1, 0);
    ((void(__thiscall*)(cSPEditorHandle*, int, int))this->vptr[0xc])(this, 3, 1);
}

// @ 0x0047f3e0
uint32_t cSPEditorHandle::SetScale(float s)
{
    cMWModel* m1 = this->mModel;
    cMWModel* m2 = this->mOverdrawModel;
    if (m1) {
        cSPTransform_s0047_e4b0& xform = m1->mTransform;
        xform.mScale = s * this->mDefaultScale;
        ++xform.mModificationCount;
    }
    if (m2) {
        cSPTransform_s0047_e4b0& xform = m2->mTransform;
        xform.mScale = s * this->mDefaultScale;
        ++xform.mModificationCount;
    }
    if (m2)
        return ((uint32_t)(uintptr_t)((char*)m2 + 8) & 0xFFFF0000u) | (uint16_t)m2->mTransform.mModificationCount;
    if (m1)
        return (uint32_t)(uintptr_t)((char*)m1 + 8);
    return (uint32_t)(uintptr_t)this;
}

// @ 0x0047f4b0
cSPEditorHandle* cSPEditorHandle::ConstructDerived()
{
    this->BaseConstruct();
    this->vptr = (void**)&g_const_zero;
    this->vptr2 = (void**)&g_const_one;
    return this;
}

// @ 0x0047f520
void __fastcall BallConnector_Dtor(cSPEditorHandle_s0047_f520* self)
{
    *(void**)self = (void*)0x13ef1c0;
    self->mRefCountVft = (void*)0x13ef1ac;
    cSPEditorHandle_Shutdown(self);
    cSPEditorHandle_BaseDtor(self);
}

// @ 0x0047f550
void* BallConnectorIface::QueryInterface(u32 id)
{
    switch ((int)id) {
    case 0x050e8e23: return this;
    case 0x050a1fe5: return this;
    case (int)0xee3f516e: return this;
    }
    return 0;
}

// @ 0x0047f5a0
void __fastcall cSPEditorHandle_UpdateModelTransforms(cSPEditorHandle_s0047_f520* self)
{
    Vec3 pos;
    Mat3 rot;
    self->GetHandlePosition(&pos);
    rot.Assign((char*)self->mBlock + 0x60);
    cMWModel_s0047_f520* m = self->mModel;
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
    cMWModel_s0047_f520* od = self->mOverdrawModel;
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

// @ 0x0047f960
Vec3* __fastcall cSPEditorHandle_GetBlockOffset(cSPEditorHandle_s0047_f520* self, int /*edx*/, Vec3* out)
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

// @ 0x0047f9e0
Vec3* cSPEditorHandle::GetTuningVec90(Vec3* out)
{
    char* tuning = (char*)EditorTuning();
    *out = *(Vec3*)(tuning + 0x90);
    return out;
}
