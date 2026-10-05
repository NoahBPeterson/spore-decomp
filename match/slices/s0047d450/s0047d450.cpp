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

struct cMWModel {
    void* mWorld;                 // +0x00  cIModelWorld* (its first dword is the vtable)
    uint32_t mFlags;              // +0x04
    char   pad_08[0x38];
    int    mRefCount;             // +0x40
    void Release();
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
void   Model_SetFlag(cMWModel* model, int flag);                            // @ 0x00437f70

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

// @ 0x0047db30 -- complete main path (two model setups), shape only: the exact
// inlined AutoRefCount / bitset sequence of the original is not reproduced.
void cSPEditorHandle::Init(cSPEditorBlock* block, bool loadProps, uint32_t modelKey, uint32_t overdrawKey)
{
    this->mCurrentState = 1;
    this->mBlock = block;
    if (this->mModel) {
        cMWModel* p = this->mModel;
        ((void(__thiscall*)(void*, cMWModel*, int))WorldSlot(p, 0x16c / 4))(p->mWorld, p, 0);
        // drop the model's modification-count ref
        void** slot = (void**)((char*)p + 0x64);
        if (*slot) {
            void* t = *slot;
            *slot = 0;
            ((void(__thiscall*)(void*))t)(t);
        }
    }
    if (this->mOverdrawModel) {
        cMWModel* p = this->mOverdrawModel;
        ((void(__thiscall*)(void*, cMWModel*, int))WorldSlot(p, 0x16c / 4))(p->mWorld, p, 0);
        void** slot = (void**)((char*)p + 0x64);
        if (*slot) {
            void* t = *slot;
            *slot = 0;
            ((void(__thiscall*)(void*))t)(t);
        }
    }
    if (this->mModel) {
        cMWModel* t = this->mModel;
        this->mModel = 0;
        if (t)
            t->Release();
    }
    if (this->mOverdrawModel) {
        cMWModel* t = this->mOverdrawModel;
        this->mOverdrawModel = 0;
        if (t)
            t->Release();
    }
    if (loadProps) {
        LoadProps();
        void* world = block->mModelWorld;
        if (modelKey == 0)
            modelKey = this->mDefaultModelKey[0];
        if (modelKey) {
            cMWModel* m = (cMWModel*)((void*(__thiscall*)(void*, uint32_t, void*, int))((void**)world)[3])(world, modelKey, (void*)0x015d4308, 0);
            if (m != this->mModel) {
                cMWModel* old = this->mModel;
                if (m)
                    ++m->mRefCount;
                this->mModel = m;
                if (old)
                    old->Release();
            }
            ((void(__thiscall*)(void*, cMWModel*))((void**)world)[22])(world, this->mModel);
            Model_SetFlag(this->mModel, 0);
        }
        if (overdrawKey == 0 && this->mHasOverdraw)
            overdrawKey = this->mDefaultOverdrawKey[0];
        if (overdrawKey && this->mHasOverdraw) {
            cMWModel* m = (cMWModel*)((void*(__thiscall*)(void*, uint32_t, void*, int))((void**)world)[3])(world, overdrawKey, (void*)0x015d4308, 0);
            if (m != this->mOverdrawModel) {
                cMWModel* old = this->mOverdrawModel;
                if (m)
                    ++m->mRefCount;
                this->mOverdrawModel = m;
                if (old)
                    old->Release();
            }
            ((void(__thiscall*)(void*, cMWModel*))((void**)world)[22])(world, this->mOverdrawModel);
            Model_SetFlag(this->mOverdrawModel, 0);
        }
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
            ((void(__thiscall*)(void*))t)(t);
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
            ((void(__thiscall*)(void*))t)(t);
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
