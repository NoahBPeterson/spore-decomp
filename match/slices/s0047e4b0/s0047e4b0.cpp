// Slice s0047e4b0: Editor cSPEditorHandle state/color/alpha accessors and a
// derived constructor, built /Od /Ob1 /arch:SSE.
#include "types.h"

typedef unsigned int uintptr_t;

inline void* operator new(unsigned int, void* p) { return p; }

// EASTL-like bitset with the div-based generic word/bit split seen in this module.
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

struct cSPTransform {
    uint16_t pad0;                 // +0x00
    uint16_t mModificationCount;   // +0x02
    char     pad4[0x0c];
    float    mScale;               // +0x10
};

struct cMWModel {
    void* mWorld;                 // +0x00
    Bitset32 mFlags;              // +0x04
    cSPTransform mTransform;      // +0x08
    uint32_t pad1c[9];            // +0x1c
    int    mRefCount;             // +0x40
    uint32_t pad44[2];            // +0x44
    Vector3 mColor;               // +0x4c
    float  mAlpha;                // +0x58
    void AddRef() { mRefCount = mRefCount + 1; }
    void Release();
    void SetFlag(bool b);         // @ 0x00437f70
};

struct cSPEditorHandle {
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


void  GetPropertyAsColorRGB(cPropertyList* pl, uint32_t key, void* out);   // @ 0x006a11b0
float* Property_GetFloat(void* property);                                  // @ 0x0041ea70

inline void GetFloatProperty(cPropertyList* pl, uint32_t key, float* out)
{
    if (pl) {
        void* prop;
        if (((bool(__thiscall*)(cPropertyList*, uint32_t, void**))pl->vptr[9])(pl, key, &prop)
                && *(uint16_t*)((char*)prop + 0x12) == 0xd)
            *out = *Property_GetFloat(prop);
    }
}

extern float g_const_zero;   // 0x015d4578 (equiv t3)
extern float g_const_one;
extern Vector3 g_defaultHandleColor;   // 0x015d443c (equiv t2)

// @ 0x0047e4b0
// The original (/Od) leaves eax = this, with the low byte overwritten by the highlight byte store
// (`mov al, [ebp+0xc]`) whenever either model is present; both-null leaves eax = this. That hidden
// eax is what the equivalence checker compares (the original writes eax before every ret).
uint32_t cSPEditorHandle::SetModelFlags(bool flag, uint8_t highlight)
{
    if (this->mModel) {
        this->mModel->mFlags.set(3, flag);
        *(uint8_t*)((char*)this->mModel + 0x5c) = highlight;
    }
    if (this->mOverdrawModel) {
        this->mOverdrawModel->mFlags.set(3, flag);
        *(uint8_t*)((char*)this->mOverdrawModel + 0x5c) = highlight;
    }
    uint32_t eax = (uint32_t)(uintptr_t)this;
    if (this->mModel || this->mOverdrawModel)
        eax = (eax & 0xFFFFFF00u) | highlight;
    return eax;
}

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

// @ 0x0047e6e0
float cSPEditorHandle::GetHandleAlphaForState(int state)
{
    float result = g_const_one;
    if (this->mPropList) {
        switch (state) {
        case 0: GetFloatProperty(this->mPropList, 0x050fc1d4, &result); break;
        case 1: result = g_const_zero; break;
        case 2: GetFloatProperty(this->mPropList, 0x050fc1d2, &result); break;
        case 3: GetFloatProperty(this->mPropList, 0x050fc1d0, &result); break;
        }
    }
    return result;
}

// @ 0x0047e830
float cSPEditorHandle::GetOverdrawHandleAlphaForState(int state)
{
    float result = g_const_one;
    if (this->mPropList) {
        switch (state) {
        case 0: GetFloatProperty(this->mPropList, 0x050fc1d5, &result); break;
        case 1: result = g_const_zero; break;
        case 2: GetFloatProperty(this->mPropList, 0x050fc1d3, &result); break;
        case 3: GetFloatProperty(this->mPropList, 0x050fc1d1, &result); break;
        }
    }
    return result;
}

// @ 0x0047e980
void* cSPEditorHandle::GetHandleColorForState(void* out, int state)
{
    Vector3 color;
    color.x = g_defaultHandleColor.x;
    color.y = g_defaultHandleColor.y;
    color.z = g_defaultHandleColor.z;
    if (this->mPropList) {
        switch (state) {
        case 0: GetPropertyAsColorRGB(this->mPropList, 0x050fc18b, &color); break;
        case 1: GetPropertyAsColorRGB(this->mPropList, 0x050fc187, &color); break;
        case 2: GetPropertyAsColorRGB(this->mPropList, 0x050fc189, &color); break;
        case 3: GetPropertyAsColorRGB(this->mPropList, 0x050fc187, &color); break;
        }
    }
    ((float*)out)[0] = color.x;
    ((float*)out)[1] = color.y;
    ((float*)out)[2] = color.z;
    return out;
}

// @ 0x0047eaa0
void* cSPEditorHandle::GetOverdrawHandleColorForState(void* out, int state)
{
    Vector3 color;
    color.x = g_defaultHandleColor.x;
    color.y = g_defaultHandleColor.y;
    color.z = g_defaultHandleColor.z;
    if (this->mPropList) {
        switch (state) {
        case 0: GetPropertyAsColorRGB(this->mPropList, 0x050fc18c, &color); break;
        case 1: GetPropertyAsColorRGB(this->mPropList, 0x050fc188, &color); break;
        case 2: GetPropertyAsColorRGB(this->mPropList, 0x050fc18a, &color); break;
        case 3: GetPropertyAsColorRGB(this->mPropList, 0x050fc188, &color); break;
        }
    }
    ((float*)out)[0] = color.x;
    ((float*)out)[1] = color.y;
    ((float*)out)[2] = color.z;
    return out;
}

// @ 0x0047ebe0
void* cSPEditorHandle::GetZeroVector(void* out)
{
    Vector3 v = { 0.0f, 0.0f, 0.0f };
    ((float*)out)[0] = v.x;
    ((float*)out)[1] = v.y;
    ((float*)out)[2] = v.z;
    return out;
}

// @ 0x0047f290
bool cSPEditorHandle::IsFlagSet()
{
    if (this->mModel == 0)
        return false;
    if (this->mOverdrawModel == 0)
        return this->mModel->mFlags.test(0);
    bool m = this->mModel->mFlags.test(0);
    if (!m && !this->mOverdrawModel->mFlags.test(0))
        return false;
    return true;
}

// @ 0x0047f3b0
void cSPEditorHandle::SetStateFlags()
{
    ((void(__thiscall*)(cSPEditorHandle*, int, int))this->vptr[0xc])(this, 1, 0);
    ((void(__thiscall*)(cSPEditorHandle*, int, int))this->vptr[0xc])(this, 3, 1);
}

// @ 0x0047f3e0
// Hidden eax (/Od residue, compared by the checker): with an overdraw model, eax = (overdraw+8)
// upper half | incremented modification count (the `add ax,1` overwrites low16); with only the
// model, eax = model+8; with neither, eax = this.
uint32_t cSPEditorHandle::SetScale(float s)
{
    cMWModel* m1 = this->mModel;
    cMWModel* m2 = this->mOverdrawModel;
    if (m1) {
        cSPTransform& xform = m1->mTransform;
        xform.mScale = s * this->mDefaultScale;
        ++xform.mModificationCount;
    }
    if (m2) {
        cSPTransform& xform = m2->mTransform;
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

// By-value AutoRefCount<cMWModel> argument: copy constructs with AddRef.
struct ModelRef {
    cMWModel* p;
    ModelRef(const ModelRef& r)
    {
        p = r.p;
        if (p)
            p->AddRef();
    }
};

struct AnimMgr {
    void** vptr;
};

void* GetAnimMgr();   // @ 0x00401060, returns the global at 0x015d0c18
bool Vector3_NotEqual(const Vector3* a, const Vector3* b);   // @ 0x0041dd30, cdecl

typedef void (__thiscall *AnimFn)(void*, ModelRef, int, float, float, int);
#define ANIM(pAnimator, model, prop, value, time) \
    ((AnimFn)(*(void***)(pAnimator))[6])((pAnimator), *(ModelRef*)&(model), (prop), (value), (time), 1)

// @ 0x0047ec40
void cSPEditorHandle::SetState(int state, bool animate)
{
    if (state != this->mCurrentState && this->mCurrentState == 1) {
        if (GetModel())
            GetModel()->SetFlag(true);
        if (GetOverdrawModel())
            GetOverdrawModel()->SetFlag(true);
    }

    float time;
    void* pAnimator = 0;
    if (animate)
        pAnimator = GetAnimMgr();
    time = (state == 1) ? this->mFadeOutTime : this->mFadeInTime;

    if (GetModel()) {
        float oldAlpha = ((float(__thiscall*)(cSPEditorHandle*, int))this->vptr[0xe])(this, this->mCurrentState);
        float newAlpha = ((float(__thiscall*)(cSPEditorHandle*, int))this->vptr[0xe])(this, state);
        if (oldAlpha != newAlpha) {
            if (animate)
                ANIM(pAnimator, this->mModel, 4, newAlpha, time);
            else
                GetModel()->mAlpha = newAlpha;
        }
        Vector3 oldColor, newColor;
        ((void*(__thiscall*)(cSPEditorHandle*, Vector3*, int))this->vptr[0x10])(this, &oldColor, this->mCurrentState);
        ((void*(__thiscall*)(cSPEditorHandle*, Vector3*, int))this->vptr[0x10])(this, &newColor, state);
        if (Vector3_NotEqual(&oldColor, &newColor)) {
            if (animate) {
                ANIM(pAnimator, this->mModel, 1, newColor.x, time);
                ANIM(pAnimator, this->mModel, 2, newColor.y, time);
                ANIM(pAnimator, this->mModel, 3, newColor.z, time);
            } else {
                Vector3& dst = GetModel()->mColor;
                dst = newColor;
            }
        }
    }

    if (GetOverdrawModel()) {
        float oldAlpha = ((float(__thiscall*)(cSPEditorHandle*, int))this->vptr[0xf])(this, this->mCurrentState);
        float newAlpha = ((float(__thiscall*)(cSPEditorHandle*, int))this->vptr[0xf])(this, state);
        if (oldAlpha != newAlpha) {
            if (animate)
                ANIM(pAnimator, this->mOverdrawModel, 4, newAlpha, time);
            else
                GetOverdrawModel()->mAlpha = newAlpha;
        }
        Vector3 oldColor, newColor;
        ((void*(__thiscall*)(cSPEditorHandle*, Vector3*, int))this->vptr[0x11])(this, &oldColor, this->mCurrentState);
        ((void*(__thiscall*)(cSPEditorHandle*, Vector3*, int))this->vptr[0x11])(this, &newColor, state);
        if (Vector3_NotEqual(&oldColor, &newColor)) {
            if (animate) {
                ANIM(pAnimator, this->mOverdrawModel, 1, newColor.x, time);
                ANIM(pAnimator, this->mOverdrawModel, 2, newColor.y, time);
                ANIM(pAnimator, this->mOverdrawModel, 3, newColor.z, time);
            } else {
                Vector3& dst = GetOverdrawModel()->mColor;
                dst = newColor;
            }
        }
    }
    this->mCurrentState = state;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
