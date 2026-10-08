// Slice s0047d450: Editor module, built /Od /Ob1 /arch:SSE (/fp:fast).
// EASTL heap algorithms over a (float key, value) pair, then the cSPEditorHandle
// object: constructor, destructor, Init, LoadProps, Shutdown and an interface cast.
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }

// Unused locals of inline helpers that /Od still reserves frame slots for.
template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---------------------------------------------------------------------------
// EASTL heap element: 8 bytes, ordered by the float key.
struct FloatKeyPair {
    float x, y;
    FloatKeyPair(const FloatKeyPair& v) { x = v.x; y = v.y; }
    const float& operator[](int i) const { return (&x)[i]; }
};

struct FloatKeyLess {
    bool operator()(const FloatKeyPair& a, const FloatKeyPair& b) const { return a[0] < b[0]; }
};

void adjust_heap(FloatKeyPair* first, int topPosition, int heapSize, int position, FloatKeyPair value, FloatKeyLess compare);

// @ 0x0047d450
void promote_heap(FloatKeyPair* first, int topPosition, int position, FloatKeyPair value, FloatKeyLess compare)
{
    for (int parentPosition = (position - 1) >> 1;
         position > topPosition && compare(first[parentPosition], value);
         parentPosition = (position - 1) >> 1)
    {
        first[position] = first[parentPosition];
        position = parentPosition;
    }
    first[position] = value;
}

// @ 0x0047d4f0
void pop_heap(FloatKeyPair* first, FloatKeyPair* last, FloatKeyLess compare)
{
    FloatKeyPair temp(*(last - 1));
    *(last - 1) = *first;
    adjust_heap(first, 0, (int)(last - first) - 1, 0, temp, compare);
}

// ---------------------------------------------------------------------------
// cSPEditorHandle (retail layout, size 0x50).  The class is modelled as a plain
// struct with explicit vtable-pointer fields so the constructor's own base-ctor
// vptr stores are hand-written in the same order as the original.
struct cPropertyList;
struct cSPEditorBlock;

// cIModelWorld, only the vtable slots Init uses: 3 = create model (0xc), 22 = register model (0x58),
// 91 = release model (0x16c).  Filler virtuals pad the slots in between.
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

extern void* g_vtblA;
extern void* g_vtblB;
extern void* g_vtblC;
extern void* g_vtblD;
extern void* g_vtblE;
extern uint32_t g_modelGroup;                                       // 0x015d4308
extern float g_ctorConst1;
extern float g_ctorConst2;

// @ 0x0047d6a0
cSPEditorHandle* cSPEditorHandle::Construct()
{
    this->vptr = &g_vtblA;
    this->vptr = &g_vtblB;
    this->vptr2 = &g_vtblC;
    this->mUnk8 = 0;
    this->vptr = &g_vtblD;
    this->vptr2 = &g_vtblE;
    this->mPropList = 0;
    if (this->mPropList)
        ((void(__thiscall*)(cPropertyList*))this->mPropList->vptr[0])(this->mPropList);
    this->mBlock = 0;
    this->mModel = 0;
    if (this->mModel)
        ++this->mModel->mRefCount;
    this->mOverdrawModel = 0;
    if (this->mOverdrawModel)
        ++this->mOverdrawModel->mRefCount;
    this->mFadeInTime = g_ctorConst1;
    this->mFadeOutTime = g_ctorConst1;
    this->mAnimateInTime = g_ctorConst1;
    this->mAnimateOutTime = g_ctorConst1;
    this->mDefaultModelKey[0] = 0;
    this->mDefaultModelKey[1] = 0;
    this->mDefaultModelKey[2] = 0;
    this->mDefaultOverdrawKey[0] = 0;
    this->mDefaultOverdrawKey[1] = 0;
    this->mDefaultOverdrawKey[2] = 0;
    this->mHasOverdraw = 0;
    this->mDefaultScale = g_ctorConst2;
    return this;
}

// @ 0x0047d910
void* cSPEditorHandle::AsInterface(uint32_t id)
{
    uint32_t t14 = id;
    if (t14 == 0xee3f516e)
        return this;
    if (t14 == 0x050a1fe5)
        return this;
    return 0;
}

// ---------------------------------------------------------------------------
// The remaining cSPEditorHandle methods.  Callees / vtables are masked
// relocations, so they are declared with the right calling convention and the
// calls are reproduced through explicit vtable-slot casts (retail layout).
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
bool*  Property_GetBool(void* property);                                    // @ 0x0041e920
uint8_t* Property_GetKeyArray(void* property);                              // @ 0x0041e920

inline void* WorldSlot(cMWModel* p, int slot)
{
    return ((void**)(*(void**)p->mWorld))[slot];
}

// @ 0x0047d870
void cSPEditorHandle::Destroy()
{
    this->vptr = &g_vtblD;
    this->vptr2 = &g_vtblE;
    Shutdown();
    if (this->mOverdrawModel)
        ((void(__thiscall*)(cMWModel*))((void**)(*(void**)this->mOverdrawModel))[1])(this->mOverdrawModel);
    if (this->mModel)
        this->mModel->Release();
    if (this->mPropList)
        ((void(__thiscall*)(cPropertyList*))this->mPropList->vptr[1])(this->mPropList);
    this->vptr2 = &g_vtblC;
    this->vptr = &g_vtblA;
}

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
    ((void(__thiscall*)(void*, uint32_t, uint32_t, cPropertyList**))((void**)pm)[11])(pm, key[0], key[2], &this->mPropList);

    if (this->mPropList) {
        GetFloatProperty(this->mPropList, 0x050fc37a, &this->mAnimateInTime);
        GetFloatProperty(this->mPropList, 0x050fc37b, &this->mAnimateOutTime);
        GetFloatProperty(this->mPropList, 0x050fc37c, &this->mFadeInTime);
        GetFloatProperty(this->mPropList, 0x050fc37d, &this->mFadeOutTime);
        if (this->mPropList) {
            void* local = 0;
            bool ok = ((bool(__thiscall*)(cPropertyList*, uint32_t, void**))((void**)this->mPropList)[9])(this->mPropList, 0x050fc24d, &local);
            if (ok && *(uint16_t*)((char*)local + 0x12) == 0xd) {
                float* f = Property_GetFloat(local);
                this->mDefaultScale = *f;
            }
        }
        GetPropertyAsKey(this->mPropList, 0x050fc326, &this->mDefaultModelKey);
        GetPropertyAsKey(this->mPropList, 0x050fc327, &this->mDefaultOverdrawKey);
        if (this->mPropList) {
            void* local = 0;
            bool ok = ((bool(__thiscall*)(cPropertyList*, uint32_t, void**))((void**)this->mPropList)[9])(this->mPropList, 0x050fc33e, &local);
            if (ok && *(uint16_t*)((char*)local + 0x12) == 1) {
                uint8_t* b = Property_GetKeyArray(local);
                this->mHasOverdraw = *b;
            }
        }
    }
}

// @ 0x0047db30
// The two model setups are expanded by hand in the original (/Od): drop the old models, then for
// each default/overridden key create the model through the model world, attach the handle as
// owner, set the flag bits, scale, color and highlight.  The AutoRefCount assignments are the
// inlined EA::AutoRefCount operator= (its `if (pNew)` arm survives as dead code when pNew is 0).
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

// cMWModel exposes the intrusive ref count used by AutoRefCount<cMWModel>.
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

// EASTL bitset<32>::set(i, value) as inlined in the original (out-of-range index is ignored).
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

// vtable view of cSPEditorHandle (slots 0x34..0x48).
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

// Drops the world's reference to the model and clears its owner (+0x64).
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
