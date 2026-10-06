// Slice s0080e6b0 (batch w2g6).
// UI::cSPUILayeredObject, cSPUICustomRendererImpl, UI::LayerManager.
// Built /O2 /MD /Gy /EHsc /TP /arch:SSE2.
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;

void* __cdecl  GameAlloc(size_t size, const char* name, int, int, int, int);
void  __cdecl  GameFree(void* p);
void  __fastcall Fun_7c3f70(void*);          // 0x7c3f70
void  __fastcall Fun_7c3ba0(void*);          // 0x7c3ba0
void  __fastcall Fun_7c4000(void*);          // 0x7c4000
void  __fastcall Fun_7c4dd0(void*, int);      // 0x7c4dd0 SP::cSPEditorPhysicsWorld::Init
void  __fastcall Fun_8e2b20(void*);           // 0x8e2b20
void  __fastcall SharedVecDtor(void*);        // 0x5c7f10
void* __cdecl  ModelManagerGet();             // 0x67dd80
void* __cdecl  EffectsManagerGet();           // 0x67ddd0
void  __fastcall Fun_82e4b0(void*, void*);    // 0x82e4b0
void  __fastcall Fun_82e4c0(void*, void*);    // 0x82e4c0
void  __cdecl  Fun_7c4000c(void*);            // 0x7c4000

typedef void* (__thiscall *VF0)(void*);
typedef void  (__thiscall *VF0v)(void*);
typedef void* (__thiscall *VF1)(void*, void*);
typedef void  (__thiscall *VF1v)(void*, void*);
static inline void** VT(void* o) { return *(void***)o; }

// ---------------- UI::cSPUILayeredObject ----------------
struct cMWModel { u8 pad[0x40]; i32 mRefCount; u8 pad44[4]; };
struct cSPUILayeredObject {
    void**  vtbl;        // +0
    i32     mRefCount;   // +4 (base RefCount)
    void*   mpViewer;    // +8
    void*   mpWindow;    // +0xc
    void*   mpWinProc;   // +0x10
    cMWModel** mModelsBegin;  // +0x14
    cMWModel** mModelsEnd;    // +0x18
    cMWModel** mModelsCap;    // +0x1c
    u8      pad20[0x74 - 0x20];
    u8      flag74;      // +0x74
    u8      flag75;      // +0x75
    u8      flag76;      // +0x76
    u8      flag77;      // +0x77
    u8      flag78;      // +0x78

    cSPUILayeredObject* __thiscall ctor();          // 0x80e850
    void __thiscall dtor();                         // 0x80ead0
    u32  __thiscall RemoveModel(cMWModel* m);       // 0x80e980
    void __thiscall RemoveAllModels();              // 0x80ea50
    void __thiscall MethodE6B0(void* a, void* b);   // 0x80e6b0
};

// ---------------- cSPUICustomRendererImpl ----------------
struct LayerInfoVec {                 // eastl::vector<cLayerInfo, fixed_vector_allocator<12,5,...>>
    void* begin;      // +0
    void* end;        // +4
    void* cap;        // +8
    void* x0c;        // +0xc
    void* inline_;    // +0x10
    void __thiscall dtor();   // 0x80ea80
};

struct cSPUICustomRendererImpl {
    void** vtbl;         // +0   0x1417df8 / 0x1417e18
    void** vtbl2;        // +4   0x1417df4 / 0x1417e14
    u32    atomic8;      // +8
    LayerInfoVec mLayers;// +0xc
    u8     pad20[0x60 - 0x20];
    u8     sub60[0x1d4 - 0x60];
    u8     pad1d4[0x250 - 0x1d4];
    void*  p250;         // +0x250
    void*  p254;         // +0x254
    void*  p258;         // +0x258

    void* __thiscall ctor();              // 0x80ebc0
    void* __thiscall VectorDtor(u8 flags);// 0x80ec40 (dtor w/ flag)
    void  __thiscall ScalarDtor();        // 0x80eca0
    void __thiscall MethodF380(void*);    // 0x80f380
};

// ---------------- UI::LayerManager ----------------
struct UI_LayerManager {
    void** vtbl;      // +0   0x1417de4
    void** vtbl2;     // +4   0x1417dd4
    u8     pad8[0xc - 8];
    void*  v1begin;   // +0xc
    void*  v1end;     // +0x10
    void*  v1cap;     // +0x14
    u8     pad18[0x20 - 0x18];
    void*  v2begin;   // +0x20
    void*  v2end;     // +0x24
    void*  v2cap;     // +0x28
    u8     pad2c[0x34 - 0x2c];
    u8     b34;       // +0x34
    u8     pad35[0x38 - 0x35];
    i32    i38;       // +0x38
    void*  p3c;       // +0x3c
    u8     pad40[0x94 - 0x40];
    u8     b94;       // +0x94

    void __thiscall ctor();          // 0x80edb0
    void* __thiscall VectorDtor(u8); // 0x80ee10
};

// =========================== bodies ===========================

// @ 0x0080e6b0
void __thiscall cSPUILayeredObject::MethodE6B0(void* a, void* b)
{
    u8* self = (u8*)this;
    *(u32*)(self + 0x38) = (u32)(size_t)a;
    Fun_82e4b0(self, b);
    Fun_82e4c0(self, b);
    if (a) {
        void* x = ((VF0)VT(a)[4 / 4])(a);
        void* r = ((VF0)VT(x)[0x34 / 4])(x);
        f32 v[4];
        v[0] = ((f32*)r)[0]; v[1] = ((f32*)r)[1]; v[2] = ((f32*)r)[2]; v[3] = ((f32*)r)[3];
        (void)v;
    }
}

// @ 0x0080e850
cSPUILayeredObject* __thiscall cSPUILayeredObject::ctor()
{
    u8* self = (u8*)this;
    mRefCount = 0;
    vtbl = (void**)0x1417dc4;
    mpViewer = 0;
    mpWindow = 0;
    mpWinProc = 0;
    mModelsBegin = 0; mModelsEnd = 0; mModelsCap = 0;
    *(u32*)(self + 0x28) = 0;
    *(u16*)(self + 0x2e) = 0;
    *(u16*)(self + 0x2c) = 0;
    *(f32*)(self + 0x30) = 0.0f;
    *(f32*)(self + 0x34) = 0.0f;
    *(f32*)(self + 0x38) = 0.0f;
    *(f32*)(self + 0x3c) = 1.0f;
    *(f32*)(self + 0x64) = 0.0f;
    *(f32*)(self + 0x68) = 0.0f;
    *(f32*)(self + 0x6c) = 0.0f;
    *(f32*)(self + 0x70) = 0.0f;
    flag74 = 0; flag75 = 0; flag76 = 0; flag77 = 0; flag78 = 1;
    mpViewer = GameAlloc(0x174, "UI/cSPUILayeredObject/cViewer", 0, 0, 0, 0);
    if (mpViewer) Fun_7c3f70(mpViewer);
    Fun_7c4dd0(mpViewer, 0);
    void* wp = GameAlloc(0x10, "UI/cObjectWindowWinProc", 0, 0, 0, 0);
    if (wp) {
        *(void**)((u8*)wp + 0x0c) = this;
    }
    mpWinProc = wp;
    return this;
}

// @ 0x0080e980
u32 __thiscall cSPUILayeredObject::RemoveModel(cMWModel* param)
{
    u32 n = (u32)(mModelsEnd - mModelsBegin);
    for (u32 i = 0; i < n; ++i) {
        cMWModel* m = mModelsBegin[i];
        if (m == param) {
            // detach from world
            void* world = *(void**)((u8*)param + 4);
            ((VF1v)VT(world)[0x16c / 4])(world, param);
            cMWModel* last = mModelsEnd[-1];
            cMWModel* old = mModelsBegin[i];
            if (last != old) {
                if (last) last->mRefCount += 1;
                mModelsBegin[i] = last;
                if (old) {
                    if (old->mRefCount > 1) old->mRefCount -= 1;
                    else { void* w = *(void**)((u8*)old + 4); ((VF1v)VT(w)[0x170 / 4])(w, old); }
                }
            }
            mModelsEnd -= 1;
            cMWModel* tail = mModelsEnd[0];
            if (tail) {
                if (tail->mRefCount > 1) tail->mRefCount -= 1;
                else { void* w = *(void**)((u8*)tail + 4); ((VF1v)VT(w)[0x170 / 4])(w, tail); }
            }
            *(f32*)((u8*)this + 0x6c) = 0.0f;
            return 1;
        }
    }
    return 0;
}

// @ 0x0080ea50
void __thiscall cSPUILayeredObject::RemoveAllModels()
{
    while (mModelsBegin != mModelsEnd) RemoveModel(*mModelsBegin);
}

// @ 0x0080ea80
void __thiscall LayerInfoVec::dtor()
{
    void** e = (void**)end;
    for (void** p = (void**)begin; p < e; p = (void**)((u8*)p + 0xc)) {
        void* o = *p;
        if (o) ((VF0v)VT(o)[1])(o);
    }
    void* b = begin;
    if (b && b != inline_) GameFree(b);
}

// @ 0x0080ead0
void __thiscall cSPUILayeredObject::dtor()
{
    u8* self = (u8*)this;
    vtbl = (void**)0x1417dc4;
    while (mModelsBegin != mModelsEnd) RemoveModel(*mModelsBegin);
    Fun_7c3ba0(mpViewer);
    if (mpViewer) { Fun_7c4000(mpViewer); GameFree(mpViewer); }
    mpViewer = 0;
    if (mpWindow) {
        if (flag74) { void* w = mpWindow; ((VF1v)VT(w)[0x108 / 4])(w, mpWinProc); }
        void* w = mpWindow;
        if (w) { mpWindow = 0; ((VF0v)VT(w)[1])(w); }
        flag74 = 0;
    }
    if (mpWinProc) { void* w = mpWinProc; mpWinProc = 0; ((VF0v)VT(w)[1])(w); }
    if (*(void**)(self + 0x28)) {
        void* o = *(void**)(self + 0x28);
        ((VF0v)VT(o)[1])(o);
    }
    // destroy model vector
    {
        u8* b = (u8*)mModelsBegin;
        u8* e = (u8*)mModelsEnd;
        for (; b < e; b += 4) { /* refcount release */ }
        void* p = mModelsBegin;
        if (p && ((u32*)p)[-1]) GameFree(p);
    }
    if (*(void**)(self + 0x10)) { void* o = *(void**)(self + 0x10); ((VF0v)VT(o)[1])(o); }
    if (*(void**)(self + 0xc)) { void* o = *(void**)(self + 0xc); ((VF0v)VT(o)[1])(o); }
    vtbl = (void**)0x13ec458;
}

// @ 0x0080ebc0
void* __thiscall cSPUICustomRendererImpl::ctor()
{
    u8* self = (u8*)this;
    vtbl = (void**)0x14426a0;
    vtbl2 = (void**)0x13ef094;
    atomic8 = 0;
    vtbl = (void**)0x1417df8;
    vtbl2 = (void**)0x1417df4;
    void* inl = self + 0x24;
    *(void**)(self + 0x1c) = inl;
    *(void**)(self + 0x10) = inl;
    *(void**)(self + 0xc) = inl;
    *(void**)(self + 0x14) = (u8*)inl + 0x3c;
    Fun_7c3f70(self + 0x60);
    *(u8*)(self + 0x24c) = 0;
    Fun_7c4dd0(self + 0x60, 0);
    return this;
}

// @ 0x80ec40 -- declared return void* to match deleting-dtor shape
void* __thiscall cSPUICustomRendererImpl::VectorDtor(u8 flags)
{
    u8* self = (u8*)this;
    vtbl = (void**)0x1417df8;
    vtbl2 = (void**)0x1417df4;
    Fun_7c3ba0(self + 0x60);
    Fun_7c4000(self + 0x60);
    mLayers.dtor();
    vtbl2 = (void**)0x13ef094;
    vtbl = (void**)0x13eb938;
    if (flags & 1) GameFree(this);
    return this;
}

void __fastcall FUN_0080dbb0(void*);   // 0x80dbb0 (slice 24)
// @ 0x80eca0
void __thiscall cSPUICustomRendererImpl::ScalarDtor()
{
    u8* self = (u8*)this;
    vtbl = (void**)0x1417e18;
    vtbl2 = (void**)0x1417e14;
    if (p258) FUN_0080dbb0(this);
    if (p258) { void* o = p258; ((VF0v)VT(o)[1])(o); }
    if (p254) { void* o = p254; ((VF0v)VT(o)[1])(o); }
    if (p250) { void* o = p250; ((VF0v)VT(o)[1])(o); }
    vtbl = (void**)0x1417df8;
    vtbl2 = (void**)0x1417df4;
    Fun_7c3ba0(self + 0x60);
    Fun_7c4000(self + 0x60);
    mLayers.dtor();
    vtbl2 = (void**)0x13ef094;
    vtbl = (void**)0x13eb938;
}

// @ 0x80ed50
void* __cdecl FUN_0080ed50()
{
    cSPUICustomRendererImpl* p = (cSPUICustomRendererImpl*)
        GameAlloc(0x264, (const char*)0x13f6b3c, 0, 0, 0, 0);
    if (!p) return 0;
    p->ctor();
    p->vtbl = (void**)0x1417e18;
    p->vtbl2 = (void**)0x1417e14;
    p->p250 = 0; p->p254 = 0; p->p258 = 0;
    return (u8*)p + 0x250;
}

// @ 0x0080edb0
void __thiscall UI_LayerManager::ctor()
{
    u8* self = (u8*)this;
    *(void**)(self + 4) = (void*)0x13ec458;
    *(u32*)(self + 8) = 0;
    vtbl = (void**)0x1417de4;
    *(void**)(self + 4) = (void*)0x1417dd4;
    *(u32*)(self + 0xc) = 0;
    *(u32*)(self + 0x10) = 0;
    *(u32*)(self + 0x14) = 0;
    *(u32*)(self + 0x20) = 0;
    *(u32*)(self + 0x24) = 0;
    *(u32*)(self + 0x28) = 0;
    *(u8*)(self + 0x34) = 0;
    *(u32*)(self + 0x38) = 0xffffffff;
    *(u32*)(self + 0x3c) = 0;
    void* inl = self + 0x58;
    *(void**)(self + 0x50) = inl;
    *(void**)(self + 0x44) = inl;
    *(void**)(self + 0x40) = inl;
    *(void**)(self + 0x48) = (u8*)inl + 0x3c;
    *(u8*)(self + 0x94) = 0;
}

// @ 0x0080ee10
void* __thiscall UI_LayerManager::VectorDtor(u8 flags)
{
    u8* self = (u8*)this;
    vtbl = (void**)0x1417de4;
    *(void**)(self + 4) = (void*)0x1417dd4;
    Fun_8e2b20(self + 0x40);
    if (p3c) { void* o = p3c; ((VF0v)VT(o)[1])(o); }
    SharedVecDtor(self + 0x20);
    SharedVecDtor(self + 0xc);
    *(void**)(self + 4) = (void*)0x13ec458;
    vtbl = (void**)0x13eb938;
    if (flags & 1) GameFree(this);
    return this;
}

// pointer vector used by the renderer impl
struct PtrVec {
    void** begin;  // +0
    void** end;    // +4
    void** cap;    // +8
    void*  x0c;    // +0xc
    void*  inline_;// +0x10
    void __thiscall Insert1(void** pos, void** val);   // 0x80efe0
    void __thiscall Insert12(void** pos, void** val);  // 0x80f140
};

// @ 0x0080efe0
void __thiscall PtrVec::Insert1(void** pos, void** val)
{
    if (end != cap) {
        void** e = end;
        void** v = val;
        if (begin <= pos && pos < e) v = pos + 1;
        if (e) {
            void* o = e[-1];
            *e = o;
            if (o) ((VF0v)VT(o)[0])(o);
        }
        for (void** p = e - 1; p > pos; --p) p[0] = p[-1];
        void* nv = *v;
        void* ov = *pos;
        if (nv != ov) {
            if (nv) ((VF0v)VT(nv)[0])(nv);
            *pos = nv;
            if (ov) ((VF0v)VT(ov)[1])(ov);
        }
        end += 1;
        return;
    }
    u32 n = (u32)(end - begin);
    u32 nc = n ? n * 2 : 1;
    void** mem = nc ? (void**)GameAlloc(nc * 4, (const char*)0x13f6b3c, 0, 0, 0, 0) : 0;
    begin = mem; end = begin; cap = mem + nc;
}

// @ 0x0080f140
void __thiscall PtrVec::Insert12(void** pos, void** val)
{
    if (end != cap) {
        void** e = end;
        void** v = val;
        if (begin <= pos && pos < e) v = pos + 3;
        if (e) {
            void* o = e[-3];
            *e = o;
            if (o) ((VF0v)VT(o)[0])(o);
            e[1] = e[-2]; e[2] = e[-1];
        }
        (void)v;
        end += 3;
        return;
    }
    u32 n = (u32)(end - begin) / 3;
    u32 nc = n ? n * 2 : 1;
    void** mem = nc ? (void**)GameAlloc(nc * 0xc, (const char*)0x13f6b3c, 0, 0, 0, 0) : 0;
    (void)mem;
}

// free-function form so FUN_0080f360 can tail-call it
void __fastcall FUN_0080f2e0(char* self, void** obj, void* a, void* b);
// @ 0x0080f2e0
void __fastcall FUN_0080f2e0(char* self, void** obj, void* a, void* b)
{
    void* o = obj ? *obj : 0;
    if (o) ((VF0v)VT(o)[0])(o);
    PtrVec* v = (PtrVec*)(self + 0xc);
    if (v->end < v->cap) {
        void** e = v->end;
        v->end = e + 3;
        if (e) {
            void* x = obj ? *obj : 0;
            *e = x;
            if (x) ((VF0v)VT(x)[0])(x);
            e[1] = a; e[2] = b;
        }
    } else {
        v->Insert12(v->end, obj);
    }
    void* x = obj ? *obj : 0;
    if (x) ((VF0v)VT(x)[1])(x);
}

// @ 0x0080f360
void __fastcall FUN_0080f360(char* p, void** obj, void* a, void* b)
{
    char* q = p ? p - 0xc : 0;
    FUN_0080f2e0(q, obj, a, b);
}

// @ 0x0080f380
void __thiscall cSPUICustomRendererImpl::MethodF380(void* param)
{
    p258 = param;
    void* m = ModelManagerGet();
    void* r = ((VF1)VT(m)[0x14 / 4])(m, param);
    if (r != p258) {
        void* old = p258;
        if (r) ((VF0v)VT(r)[0])(r);
        p258 = r;
        if (old) ((VF0v)VT(old)[1])(old);
    }
}

// @ 0x0080f530
void __fastcall FUN_0080f530(void* self, void* a) { (void)self; (void)a; }

// @ 0x0080f730
void __cdecl FUN_0080f730() {}
