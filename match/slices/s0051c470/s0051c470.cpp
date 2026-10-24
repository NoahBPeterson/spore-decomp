// Slice 4: Skinner::PaintSystem ctor/dtor cluster and small EASTL refcount/list helpers.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"
#include <intrin.h>

int   GetPaintSystem();                                   // 0x00401080
void  FUN_005173a0(void* p);                              // 0x005173a0
void* EA_alloc(unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void  EASTL_allocator_deallocate(void* p);                // 0x00f47380
void  VectorAutoRef_erase(void* first, void* last, void* out); // 0x0042f530

extern void* g_vtblSkinnerPaintSystem;   // 0x013eb394
extern void* g_vtblLocaleChange;         // 0x013eb918
extern void* g_vtblSimCreatureAbility;   // 0x013ef094
extern void* g_vtblEditorResource;       // 0x013eb938
extern void* g_vtblPaintA;               // 0x013f1b80
extern void* g_vtblPaintB;               // 0x013f1b74
extern void* g_vtblPaintC;               // 0x013f1b5c
extern void* g_vtblPaintD;               // 0x013f1b58

// 0x0c-byte header then an atomic refcount (EA::Thread::AtomicInt<int>).
struct RefCounted {
    uint32_t mvtbl; uint32_t pad04; uint32_t pad08;
    volatile long mnRefCount;              // +0x0c
    int AddRef();
};

// Base subobjects of the MI EditorResource.
struct BaseEditor { void dtor(); };

struct PaintSystem {
    PaintSystem(int kind, void* a, void* b, char c, void* d, char e, char f);
    void dtor();
};

// PendingBatch subobject at PaintSystem+0x34; Flush is __thiscall with no stack args.
struct PendingBatch {
    bool Flush();                          // 0x004039f0
};

struct DList { void adv(); };
struct EditorResource { void* deleting_dtor(unsigned flags); };
struct AutoRefVector {
    void** mpBegin;                                   // +0x00
    void** mpEnd;                                     // +0x04
    void* erase(void* pos);                           // 0x0051d270
    void resize(int n);                               // 0x00421bf0
};

struct ListIter { int* p; };

struct IRefObj {                       // vtable slot 0 = AddRef, slot 1 = Release
    virtual void AddRef();
    virtual void Release();
};

struct BakeSprites : IRefObj {
    uint32_t pad04, pad08;
    AutoRefVector mImages;             // +0x0c
    char pad18[8];
    BakeSprites* Construct();          // 0x007b00f0 (thiscall ctor)
};


// @ 0x0051c620 int RefCounted::AddRef()
int RefCounted::AddRef()
{
    return (int)_InterlockedIncrement(&mnRefCount);
}

// @ 0x0051c470 ??0PaintSystem@Skinner@@...
PaintSystem::PaintSystem(int kind, void* a, void* b, char c, void* d, char e, char f)
{
    *(void**)this = &g_vtblSkinnerPaintSystem;
    *(void**)((char*)this + 4) = &g_vtblLocaleChange;
    ((BaseEditor*)((char*)this + 8))->dtor();   // inlined base ctor
    *(void**)this = &g_vtblPaintA;
    *(void**)((char*)this + 4) = &g_vtblPaintB;
    *(void**)((char*)this + 8) = &g_vtblPaintC;
    *(void**)((char*)this + 0xc) = &g_vtblPaintD;
    *(void**)((char*)this + 0x18) = a;
    *(void**)((char*)this + 0x1c) = b;
    *(int*)((char*)this + 0x20) = 0;
    *(void**)((char*)this + 0x24) = d;
    *(char*)((char*)this + 0x28) = e;
    *(char*)((char*)this + 0x29) = f;
    *(char*)((char*)this + 0x2a) = c;
    *(int*)((char*)this + 0x2c) = 0;
    *(int*)((char*)this + 0x30) = 0;
    *(int*)((char*)this + 0x34) = 0;
    *(int*)((char*)this + 0x38) = 0;
    *(int*)((char*)this + 0x3c) = 0;
    *(int*)((char*)this + 0x40) = 0;
    *(int*)((char*)this + 0x44) = 0;
    int ps = GetPaintSystem();
    int mat = *(int*)(ps + 0xc);
    void* mem = EA_alloc(0x20, "Skinner", 0, 0, 0, 0);
    void* bs = 0;
    if (mem != 0)
        bs = ((BakeSprites*)mem)->Construct();
    void** slot = (void**)((char*)this + 0x30);
    if (bs != *slot) {
        void* old = *slot;
        if (bs != 0)
            ((void(__thiscall*)(void*))(*(void***)bs)[0])(bs);
        *slot = bs;
        if (old != 0)
            ((void(__thiscall*)(void*))(*(void***)old)[1])(old);
    }
    if (mat != 0 && *(int*)(mat + 0x10 + kind * 4) != 0)
        *(void**)((char*)this + 0x20) = *(void**)(*(int*)(mat + 0x10 + kind * 4) + 0x60);
}

// @ 0x0051d010 PaintSystem dtor (base-vtable restore)
void PaintSystem::dtor()
{
    if (*(int*)((char*)this + 0x34) != 0)
        ((PendingBatch*)((char*)this + 0x34))->Flush();
    if (*(int*)((char*)this + 0x30) != 0)
        ((void(__thiscall*)(void*))(*(void***)*(void**)((char*)this + 0x30))[1])(*(void**)((char*)this + 0x30));
    *(void**)((char*)this + 0x0c) = &g_vtblSimCreatureAbility;
    *(void**)((char*)this + 0x08) = &g_vtblEditorResource;
    *(void**)((char*)this + 0x04) = &g_vtblLocaleChange;
    *(void**)this = &g_vtblSkinnerPaintSystem;
}

// @ 0x0051d090 EditorResource scalar deleting dtor
void* EditorResource::deleting_dtor(unsigned flags)
{
    *(void**)((char*)this + 4) = &g_vtblSimCreatureAbility;
    *(void**)this = &g_vtblEditorResource;
    if ((flags & 1) != 0)
        EASTL_allocator_deallocate(this);
    return this;
}

// @ 0x0051d140 intrusive-list node advance
void DList::adv()
{
    *(int*)this = *(int*)(*(int*)this + 0x10);
    while (*(int*)this == 0) {
        *(int*)((char*)this + 4) = *(int*)((char*)this + 4) + 4;
        *(int*)this = **(int**)((char*)this + 4);
    }
}

// @ 0x0051d270 eastl::vector<AutoRefCount<...>>::erase one element
void* AutoRefVector::erase(void* pos)
{
    if ((char*)pos + 4 < *(char**)((char*)this + 4)) {
        char b0 = 0, b1 = 0, b2 = 0;
        (void)b0; (void)b1; (void)b2;
        VectorAutoRef_erase((char*)pos + 4, *(void**)((char*)this + 4), pos);
    }
    char* end = *(char**)((char*)this + 4) - 4;
    *(char**)((char*)this + 4) = end;
    void** node = (void**)end;
    if (*node != 0)
        ((void(__thiscall*)(void*))(*(void***)*node)[1])(*node);
    return pos;
}

// ===========================================================================
// 0x0051c640 / 0x0051c6a0: cSkinpaintTextureExtractor (one merged 2462-byte extent: a small
// secondary-base init function followed by the real HandleMessage, ret 8).
// ===========================================================================
struct AtomicRefCounted { int Release(); };            // 0x00402420 (thiscall)

// AutoRefCount<T> with the inline assign the /Od original expands.
template<class T> struct ARC {
    T* p;
    ARC() : p(0) {}
    ARC(T* x) : p(x) { if (p) p->AddRef(); }
    ~ARC() { if (p) p->Release(); }
    ARC& operator=(T* x) {
        if (x != p) {
            T* old = p;
            if (x) x->AddRef();
            p = x;
            if (old) old->Release();
        }
        return *this;
    }
};

// atomic refcounted texture handle (RefCount at +8, lock xadd on AddRef)
struct TexRef {
    uint32_t vt; uint32_t pad04;
    volatile long mnRefCount;          // +0x08
    int Release();                     // 0x00402420
};
struct TexSlot {
    TexRef* p;
    TexSlot& operator=(TexRef* x) {
        if (x != p) {
            TexRef* old = p;
            if (x) _InterlockedExchangeAdd(&x->mnRefCount, 1);
            p = x;
            if (old) old->Release();
        }
        return *this;
    }
    void** AsPPVoidParam();            // 0x0041d870
};
struct SkinPaintSys { char pad[0x1c]; void* mpOwnerData; };   // GetPaintSystem() result: +0x1c is the info block
struct InfoBlock { char pad[0x7c]; TexSlot mSlotA; TexSlot mSlotB; };   // +0x7c, +0x80

struct MsgParam { void* v; int pad; };
struct Msg {
    int pad0, pad1; MsgParam mp[4];                    // mp[i] at 8 + 8*i
    void* Get(int i) { return mp[i].v; }
};

struct ServiceObj {                    // FUN_0067dd60 result
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20();
    virtual void SetTexture(void* tex, int a);                       // +0x54
    virtual void SetInstance(int inst, int a, int b, int c);         // +0x58
};
struct BatchSvc {                      // FUN_0068f4d0 result
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void Begin();              // +0x20
    virtual void End();                // +0x24
};
struct DescSrc { bool GetDescription(unsigned id); };            // 0x006a25a0 (thiscall)
struct Connector { void Init(void* server, void* owner, void* id, int n); };   // 0x004db620
struct ResKey { uint32_t a, b, c; };

extern "C" void* SP_MessageServer();                              // 0x0067dcc0
ServiceObj* FUN_0067dd60();                                       // 0x0067dd60
BatchSvc*   FUN_0068f4d0();                                       // 0x0068f4d0
SkinPaintSys* FUN_00401080();                                     // 0x00401080
void DXTCompressNoAlpha(void* img, void* vec, unsigned id, void* listener); // 0x007b1830
void DXTCompress(void* img, void* vec, unsigned id, void* listener);        // 0x007b1710
void FUN_007b06c0(void* src, void** dst, int idx, int stage, unsigned id, void* listener); // 0x007b06c0
bool WriteImageDataAsTexture(void* vec, int w, int h, void** out);          // 0x007aff00
void RegisterImagesAsTexture(void* vec, ResKey* key, void* saveArea, int one); // 0x007b10d0
void* SP_GetSaveArea(unsigned id);                                // 0x006b1f90
extern DescSrc* g_descSrc;                                        // 0x015fd918
extern IRefObj* g_defaultImage;                                   // 0x015de138

// cSkinpaintTextureExtractor secondary-base init (this = base + 8)
struct SkinTexExtractorB {
    char pad00[0xc];
    char mFlag;                        // +0x0c
    char pad0d[0x18 - 0x0d];
    int  mInstance;                    // +0x18
    char pad1c[0x2c - 0x1c];
    Connector mConn;                   // +0x2c
    void Init();
};
// @ 0x0051c640 cSkinpaintTextureExtractor secondary-base init
void SkinTexExtractorB::Init()
{
    int hole;
    mConn.Init(SP_MessageServer(), (char*)this - 8, (void*)0x150cad8, 3);
    if (mInstance != 0) {
        ServiceObj* svc = FUN_0067dd60();
        svc->SetInstance(mInstance, 0, 1, 0);
    } else {
        mFlag = 1;
    }
}

// cSkinpaintTextureExtractor::HandleMessage (0x0051c6a0)
struct SkinTexExtractor {
    uint32_t vp0, vp1, pad08, pad0c, pad10;
    bool mDone;                        // +0x14
    char pad15[3];
    int  mW;                           // +0x18
    int  mH;                           // +0x1c
    int  mInstance;                    // +0x20
    int  mParam24;                     // +0x24
    bool mF28, mF29, mF2a; char pad2b;
    int  mCounter;                     // +0x2c
    BakeSprites* mpBake;               // +0x30
    bool HandleMessage(unsigned msgId, void* data);
};

// @ 0x0051c6a0 cSkinpaintTextureExtractor::HandleMessage
bool SkinTexExtractor::HandleMessage(unsigned msgId, void* data)
{
    if (mDone != 0)
        return false;
    void* listener = this ? (void*)((char*)this + 4) : 0;
    bool unused = false;
    bool run = false;
    (void)unused;
    if (msgId == 0x522264d) {
        Msg* m = (Msg*)data;
        if ((int)(intptr_t)m->Get(3) == mInstance) {
            ARC<IRefObj> img((IRefObj*)m->Get(0));
            if (img.p == 0)
                img = g_defaultImage;
            if (mF29 != 0) {
                BakeSprites* bs = mpBake;
                DXTCompressNoAlpha(img.p, bs ? (void*)&bs->mImages : 0, 0x52cf019, listener);
            } else {
                BakeSprites* bs = mpBake;
                DXTCompress(img.p, bs ? (void*)&bs->mImages : 0, 0x52cf019, listener);
            }
        }
    } else if (msgId == 0x52cf019 && data == listener) {
        if (mF28 != 0) {
            AutoRefVector* v = &mpBake->mImages;
            if ((unsigned)(v->mpEnd - v->mpBegin) > 1)
                mpBake->mImages.erase(mpBake->mImages.mpBegin);
        }
        int stage = -1;
        int idx = -1;
        if (mParam24 >= 0x1f4) { stage = 6; idx = mParam24 - 0x1f4; }
        else if (mParam24 >= 0x12c) { stage = 5; idx = mParam24 - 0x12c; }
        else if (mParam24 >= 0x64) { stage = 4; idx = mParam24 - 0x64; }
        if (idx < 0 || idx >= 100) {
            run = true;
        } else {
            ARC<BakeSprites> src(mpBake);
            void* mem = EA_alloc(0x20, "Skinner", 0, 0, 0, 0);
            BakeSprites* nb = 0;
            if (mem != 0)
                nb = ((BakeSprites*)mem)->Construct();
            ARC<BakeSprites>* slot = (ARC<BakeSprites>*)&mpBake;
            *slot = nb;
            int n = (int)(src.p->mImages.mpEnd - src.p->mImages.mpBegin);
            mpBake->mImages.resize(n);
            BatchSvc* bsvc = FUN_0068f4d0();
            bsvc->Begin();
            int count = (int)(mpBake->mImages.mpEnd - mpBake->mImages.mpBegin);
            for (int i = 0; i < count; i++) {
                void** dstSlot = (void**)(mpBake->mImages.mpBegin + i);
                void** dstPP = ((TexSlot*)dstSlot)->AsPPVoidParam();
                void* srcImg = *(src.p->mImages.mpBegin + i);
                FUN_007b06c0(srcImg, dstPP, idx, stage, 0x52cf020, listener);
            }
            bsvc->End();
        }
    } else if (msgId == 0x52cf020 && data == listener) {
        mCounter = mCounter + 1;
        if (mCounter == (int)(mpBake->mImages.mpEnd - mpBake->mImages.mpBegin))
            run = true;
    }

    if (!run)
        return false;

    TexSlot tex;
    tex.p = 0;
    BakeSprites* bs = mpBake;
    void* vec = bs ? (void*)&bs->mImages : 0;
    if (tex.p != 0) {
        TexRef* t = tex.p;
        tex.p = 0;
        t->Release();
    }
    WriteImageDataAsTexture(vec, mW, mH, (void**)&tex.p);
    if (mF2a != 0 && tex.p != 0) {
        if (g_descSrc->GetDescription(0x26cd3c9)) {
            ResKey key;
            key.a = (uint32_t)mW;
            key.b = 0x2f4e681c;
            key.c = (uint32_t)mH;
            BakeSprites* b2 = mpBake;
            RegisterImagesAsTexture(b2 ? (void*)&b2->mImages : 0, &key, SP_GetSaveArea(0x11ac1ac), 1);
            ServiceObj* svc = FUN_0067dd60();
            svc->SetTexture(tex.p, 0);
        }
    }
    SkinPaintSys* ps = FUN_00401080();
    if (ps != 0 && ps->mpOwnerData != 0) {
        InfoBlock* info = (InfoBlock*)ps->mpOwnerData;
        unsigned sel = (unsigned)mH;
        if ((sel & 0xff) == 0) {
            info->mSlotA = tex.p;
        } else if ((sel & 0xff) == 1) {
            info->mSlotB = tex.p;
        }
    }
    ARC<BakeSprites>* bslot = (ARC<BakeSprites>*)&mpBake;
    if (bslot->p != 0)
        *bslot = 0;
    mDone = 1;
    if (tex.p != 0)
        tex.p->Release();
    return false;
}
