// src/game/SPBake/SPEditorHandle.cpp -- migrated from slice(s) s0047e4b0, s0047d450 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorHandle.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorHandle.h"
#include "SP/cMWModel.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorBlock.h"
#include "cSPTransform.h"

// unnamed retail callees and globals (address in the comment)
extern uint32_t g_modelGroup;                                       // 0x015d4308

// ---- items of slice s0047d450 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cPropertyList;
struct cSPEditorBlock;
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};
struct cMWModel;
struct IModelWorld0 { virtual void a0(); virtual void a1(); virtual void a2();
    virtual cMWModel* CreateModel(uint32_t key, uint32_t group, int flag); };
struct IModelWorld1 : VPad<18, IModelWorld0> { virtual void RegisterModel(cMWModel* m); };
struct IModelWorld2 : VPad<68, IModelWorld1> { virtual void ReleaseModel(cMWModel* m, int flag); };
typedef IModelWorld2 cIModelWorld;
struct cMWModel {
    cIModelWorld* mWorld;         // +0x00
    uint32_t mFlags;              // +0x04
    char   pad_08[0x38];
    int    mRefCount;             // +0x40
    void Release();               // 0x40f360
    void SetFlag(int v);          // 0x437f70 (thiscall, ret 4)
};
struct cPropertyList {
    void** vptr;                  // +0x00
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

    cSPEditorHandle* Construct();
    void* AsInterface(uint32_t id);
    void  Destroy();
    void  LoadProps();
    void  Init(cSPEditorBlock* block, bool loadProps, uint32_t modelKey, uint32_t overdrawKey);
    void  Shutdown();
};
extern uint32_t g_modelGroup;                                       // 0x015d4308
struct cSPEditorBlock {
    void* mPropList;              // +0x0c (unused here)
    char  pad_10[0x08];
    void* mModelWorld;            // +0x18  cIModelWorld*
    uint32_t mInstance;           // +0x1c
};
void*  PropertyManager();                                                   // @ 0x0067de30
void   GetFloatProperty(cPropertyList* pl, uint32_t key, float* out);       // @ 0x0040cf10
void   GetPropertyAsKey(cPropertyList* pl, uint32_t key, void* out);        // @ 0x006a1250
float* Property_GetFloat(void* property);                                   // @ 0x0041ea70
uint8_t* Property_GetKeyArray(void* property);                              // @ 0x0041e920
inline void* WorldSlot(cMWModel* p, int slot)
{
    return ((void**)(*(void**)p->mWorld))[slot];
}
struct IUnknown32 {
    virtual void AddRef();
    virtual void Release();
};
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount& operator=(T* pNew)
    {
        T* pTemp = mpObject;
        if (pNew)
            pNew->AddRef();
        mpObject = pNew;
        if (pTemp)
            pTemp->Release();
        return *this;
    }
};
struct ModelRef {
    cMWModel* mpObject;
    cMWModel* get() const { return mpObject; }
    ModelRef& operator=(cMWModel* pNew)
    {
        cMWModel* pTemp = mpObject;
        if (pNew)
            ++pNew->mRefCount;
        mpObject = pNew;
        if (pTemp)
            pTemp->Release();
        return *this;
    }
};
struct Bitset32 {
    uint32_t mWord;
    void set(unsigned i, bool value)
    {
        if (i < 0x20) {
            if (value)
                mWord |= (1u << (i % 0x20));
            else
                mWord &= ~(1u << (i % 0x20));
        }
    }
};
struct V3 { float x, y, z; };
struct HandleV : IUnknown32 {
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13();
    virtual float GetHighlight(int state);                              // 0x38
    virtual float GetOverdrawHighlight(int state);                      // 0x3c
    virtual const V3* GetColor(V3* out, int state);         // 0x40
    virtual const V3* GetOverdrawColor(V3* out, int state); // 0x44
    virtual float GetScale();                                           // 0x48
};
#define MDL(F) (((ModelRef*)&this->F)->get())
#define DROP_OWNER(M)                                                                    \
    {                                                                                    \
        cMWModel* p = (M);                                                               \
        p->mWorld->ReleaseModel(p, 0);                                                   \
        cMWModel* q = (M);                                                               \
        AutoRefCount<IUnknown32>* slot = (AutoRefCount<IUnknown32>*)((char*)q + 0x64);   \
        if (slot->mpObject)                                                              \
            *slot = 0;                                                                   \
    }
#define SETUP_MODEL(FIELD, KEY, VSLOT_COLOR, VSLOT_HIGHLIGHT)                            \
    {                                                                                    \
        cMWModel* m = world->CreateModel(KEY, g_modelGroup, 0);                          \
        ModelRef* ref = (ModelRef*)&this->FIELD;                                         \
        if (m != ref->mpObject)                                                          \
            *ref = m;                                                                    \
        world->RegisterModel(MDL(FIELD));                                               \
        {                                                                                \
            AutoRefCount<IUnknown32>* slot = (AutoRefCount<IUnknown32>*)((char*)MDL(FIELD) + 0x64); \
            if ((IUnknown32*)this != slot->mpObject)                                     \
                *slot = (IUnknown32*)this;                                               \
        }                                                                                \
        MDL(FIELD)->SetFlag(0);                                                   \
        ((Bitset32*)((char*)MDL(FIELD) + 4))->set(1, true);                             \
        {                                                                                \
            cMWModel* mdl = MDL(FIELD);                                                 \
            float scale = ((HandleV*)this)->GetScale(); \
            char* tf = (char*)mdl + 8;                                                   \
            *(float*)(tf + 0x10) = scale;                                                \
            ++*(uint16_t*)(tf + 2);                                                      \
        }                                                                                \
        {                                                                                \
            cMWModel* mdl = MDL(FIELD);                                                 \
            V3 tmp;                                                                      \
            *(V3*)((char*)mdl + 0x4c) = *((HandleV*)this)->VSLOT_COLOR(&tmp, this->mCurrentState); \
        }                                                                                \
        {                                                                                \
            cMWModel* mdl = MDL(FIELD);                                                 \
            float h = ((HandleV*)this)->VSLOT_HIGHLIGHT(this->mCurrentState); \
            *(float*)((char*)mdl + 0x58) = h;                                            \
        }                                                                                \
    }
// ---- items of slice s0047d450 end

// ---- items of slice s0047e4b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_const_zero;   // 0x015d4578 (equiv t3)
extern float g_const_one;
struct Bitset32_s0047_e4b0 {
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
struct cSPEditorBlock_s0047_e4b0;
struct cSPTransform_s0047_e4b0 {
    uint16_t pad0;                 // +0x00
    uint16_t mModificationCount;   // +0x02
    char     pad4[0x0c];
    float    mScale;               // +0x10
};
struct cMWModel_s0047_e4b0 {
    void* mWorld;                 // +0x00
    Bitset32_s0047_e4b0 mFlags;              // +0x04
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
struct cSPEditorHandle_s0047_e4b0 {
    void** vptr;                  // +0x00
    void** vptr2;                 // +0x04
    int    mUnk8;                 // +0x08
    cPropertyList* mPropList;     // +0x0c
    cSPEditorBlock_s0047_e4b0* mBlock;       // +0x10
    cMWModel_s0047_e4b0* mModel;             // +0x14
    cMWModel_s0047_e4b0* mOverdrawModel;     // +0x18
    int    mCurrentState;         // +0x1c
    float  mFadeInTime;           // +0x20
    float  mFadeOutTime;          // +0x24
    float  mAnimateInTime;        // +0x28
    float  mAnimateOutTime;       // +0x2c
    uint32_t mDefaultModelKey[3]; // +0x30
    uint32_t mDefaultOverdrawKey[3]; // +0x3c
    bool   mHasOverdraw;          // +0x48
    float  mDefaultScale;         // +0x4c

    uint32_t SetModelFlags(bool flag, uint8_t highlight);  // 0x0047e4b0 (cSPEditorHandle::SetModelFlags)
    void* GetPosition(void* out);
    void* GetZeroVector(void* out);
    float GetHandleAlphaForState(int state);  // 0x0047e6e0 (cSPEditorHandle::GetHandleAlphaForState)
    float GetOverdrawHandleAlphaForState(int state);  // 0x0047e830 (cSPEditorHandle::GetOverdrawHandleAlphaForState)
    void* GetHandleColorForState(void* out, int state);  // 0x0047e980 (cSPEditorHandle::GetHandleColorForState)
    void* GetOverdrawHandleColorForState(void* out, int state);  // 0x0047eaa0 (cSPEditorHandle::GetOverdrawHandleColorForState)
    bool IsFlagSet();
    void SetStateFlags();
    uint32_t SetScale(float s);
    void SetState(int state, bool animate);
    cMWModel_s0047_e4b0* GetModel() { return mModel; }
    cMWModel_s0047_e4b0* GetOverdrawModel() { return mOverdrawModel; }
    void BaseConstruct();
    cSPEditorHandle_s0047_e4b0* ConstructDerived();
};
struct cSPEditorBlock_s0047_e4b0 {
    char pad[0x48];
    float mPosX, mPosY, mPosZ;    // +0x48
};
void  GetPropertyAsColorRGB(cPropertyList* pl, uint32_t key, void* out);   // @ 0x006a11b0
inline void GetFloatProperty_s0047_e4b0(cPropertyList* pl, uint32_t key, float* out)
{
    if (pl) {
        void* prop;
        if (((bool(__thiscall*)(cPropertyList*, uint32_t, void**))pl->vptr[9])(pl, key, &prop)
                && *(uint16_t*)((char*)prop + 0x12) == 0xd)
            *out = *Property_GetFloat(prop);
    }
}
extern Vector3 g_defaultHandleColor;   // 0x015d443c (equiv t2)
// ---- items of slice s0047e4b0 end

// @ 0x0047d950
void cSPEditorHandle::LoadProps()
{
    uint32_t key[3];
    ((void(__thiscall*)(cSPEditorHandle*, void*))this->vptr[13])(this, key);
    void* pm = PropertyManager();
    if (this->mPropList) {
        cPropertyList* temp = this->mPropList;
        this->mPropList = 0;
        ((void(__thiscall*)(cPropertyList*))temp->vptr[1])(temp);
    }
    ((void(__thiscall*)(void*, uint32_t, uint32_t, cPropertyList**))((void**)(*(void**)pm))[11])(pm, key[0], key[2], &this->mPropList);

    if (this->mPropList) {
        GetFloatProperty(this->mPropList, 0x050fc37a, &this->mAnimateInTime);
        GetFloatProperty(this->mPropList, 0x050fc37b, &this->mAnimateOutTime);
        GetFloatProperty(this->mPropList, 0x050fc37c, &this->mFadeInTime);
        GetFloatProperty(this->mPropList, 0x050fc37d, &this->mFadeOutTime);
        if (this->mPropList) {
            void* local = 0;
            bool ok = ((bool(__thiscall*)(cPropertyList*, uint32_t, void**))((void**)(*(void**)this->mPropList))[9])(this->mPropList, 0x050fc24d, &local);
            if (ok && *(uint16_t*)((char*)local + 0x12) == 0xd) {
                float* f = Property_GetFloat(local);
                this->mDefaultScale = *f;
            }
        }
        GetPropertyAsKey(this->mPropList, 0x050fc326, &this->mDefaultModelKey);
        GetPropertyAsKey(this->mPropList, 0x050fc327, &this->mDefaultOverdrawKey);
        if (this->mPropList) {
            void* local = 0;
            bool ok = ((bool(__thiscall*)(cPropertyList*, uint32_t, void**))((void**)(*(void**)this->mPropList))[9])(this->mPropList, 0x050fc33e, &local);
            if (ok && *(uint16_t*)((char*)local + 0x12) == 1) {
                uint8_t* b = Property_GetKeyArray(local);
                this->mHasOverdraw = *b;
            }
        }
    }
}

// @ 0x0047db30
void cSPEditorHandle::Init(cSPEditorBlock* block, bool loadProps, uint32_t modelKey, uint32_t overdrawKey)
{
    this->mCurrentState = 1;
    this->mBlock = block;
    if (MDL(mModel))
        DROP_OWNER(MDL(mModel))
    if (MDL(mOverdrawModel))
        DROP_OWNER(MDL(mOverdrawModel))
    {
        ModelRef* ref = (ModelRef*)&this->mModel;
        if (ref->mpObject)
            *ref = 0;
    }
    {
        ModelRef* ref = (ModelRef*)&this->mOverdrawModel;
        if (ref->mpObject)
            *ref = 0;
    }
    if (loadProps) {
        LoadProps();
        cIModelWorld* world = (cIModelWorld*)this->mBlock->mModelWorld;
        if (modelKey == 0)
            modelKey = this->mDefaultModelKey[0];
        if (modelKey)
            SETUP_MODEL(mModel, modelKey, GetColor, GetHighlight)
        if (overdrawKey == 0 && this->mHasOverdraw)
            overdrawKey = this->mDefaultOverdrawKey[0];
        if (overdrawKey && this->mHasOverdraw)
            SETUP_MODEL(mOverdrawModel, overdrawKey, GetOverdrawColor, GetOverdrawHighlight)
    }
}

// @ 0x0047e2c0
void cSPEditorHandle::Shutdown()
{
    if (this->mModel) {
        cMWModel* p = this->mModel;
        ((void(__thiscall*)(void*, cMWModel*, int))WorldSlot(p, 0x16c / 4))(p->mWorld, p, 0);
        void** slot = (void**)((char*)p + 0x64);
        if (*slot) {
            void* t = *slot;
            *slot = 0;
            ((void(__thiscall*)(void*))((void**)*(void**)t)[1])(t);
        }
        if (this->mModel) {
            cMWModel* t = this->mModel;
            this->mModel = 0;
            if (t)
                t->Release();
        }
    }
    if (this->mOverdrawModel) {
        cMWModel* p = this->mOverdrawModel;
        ((void(__thiscall*)(void*, cMWModel*, int))WorldSlot(p, 0x16c / 4))(p->mWorld, p, 0);
        void** slot = (void**)((char*)p + 0x64);
        if (*slot) {
            void* t = *slot;
            *slot = 0;
            ((void(__thiscall*)(void*))((void**)*(void**)t)[1])(t);
        }
        if (this->mOverdrawModel) {
            cMWModel* t = this->mOverdrawModel;
            this->mOverdrawModel = 0;
            if (t)
                t->Release();
        }
    }
    if (this->mPropList) {
        cPropertyList* t = this->mPropList;
        this->mPropList = 0;
        if (t)
            ((void(__thiscall*)(cPropertyList*))t->vptr[1])(t);
    }
    this->mBlock = 0;
}

// @ 0x0047e6e0
float cSPEditorHandle_s0047_e4b0::GetHandleAlphaForState(int state)
{
    float result = g_const_one;
    if (this->mPropList) {
        switch (state) {
        case 0: GetFloatProperty_s0047_e4b0(this->mPropList, 0x050fc1d4, &result); break;
        case 1: result = g_const_zero; break;
        case 2: GetFloatProperty_s0047_e4b0(this->mPropList, 0x050fc1d2, &result); break;
        case 3: GetFloatProperty_s0047_e4b0(this->mPropList, 0x050fc1d0, &result); break;
        }
    }
    return result;
}

// @ 0x0047e830
float cSPEditorHandle_s0047_e4b0::GetOverdrawHandleAlphaForState(int state)
{
    float result = g_const_one;
    if (this->mPropList) {
        switch (state) {
        case 0: GetFloatProperty_s0047_e4b0(this->mPropList, 0x050fc1d5, &result); break;
        case 1: result = g_const_zero; break;
        case 2: GetFloatProperty_s0047_e4b0(this->mPropList, 0x050fc1d3, &result); break;
        case 3: GetFloatProperty_s0047_e4b0(this->mPropList, 0x050fc1d1, &result); break;
        }
    }
    return result;
}

// @ 0x0047e980
void* cSPEditorHandle_s0047_e4b0::GetHandleColorForState(void* out, int state)
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
void* cSPEditorHandle_s0047_e4b0::GetOverdrawHandleColorForState(void* out, int state)
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
