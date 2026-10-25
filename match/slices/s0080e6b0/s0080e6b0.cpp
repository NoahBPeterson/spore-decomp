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
void  __fastcall Fun_7c3ba0(void*);          // 0x7c3ba0
void  __fastcall Fun_7c4000(void*);          // 0x7c4000
void  __fastcall Fun_8e2b20(void*);           // 0x8e2b20
void  __fastcall SharedVecDtor(void*);        // 0x5c7f10
void* __cdecl  ModelManagerGet();             // 0x67dd80
void* __cdecl  LightingManagerGet();          // 0x67dd90
void* __cdecl  EffectsManagerGet();           // 0x67ddd0
void* __cdecl  fnMgr67dd50();                 // 0x67dd50
void* __cdecl  fnGet6eea10();                 // 0x6eea10
void* __cdecl  fnAddBoundingBox();            // 0x67cad0
void* __cdecl  fnMessageServer();             // 0x67dcc0
void  __cdecl  fnFun82e4b0(void*);            // 0x82e4b0
void  __cdecl  fnFun82e4c0(void*);            // 0x82e4c0
void* __cdecl  fnUninitCopy4(void**, void**, void**);   // 0x80de80
void* __cdecl  fnDestroy4(void**, void**, void**);      // 0x80dec0
void* __cdecl  fnUninitCopy12(void**, void**, void**);  // 0x80df00
void* __cdecl  fnDestroy12(void**, void**, void**);     // 0x760b10
void* __cdecl  fnCopyBackward4(void**, void**, void**); // 0xac97a0
void* __cdecl  fnCopyBackward12(void**, void**, void**);// 0x780a50
void* __cdecl  fnCopyBackwardRef(void**, void**, void**);// 0x5c1dc0
void* __cdecl  fnMemCpy(void*, const void*, size_t);    // 0x11e0744
void* __cdecl  fnMemSet(void*, int, size_t);            // 0x11e073e

typedef void* (__thiscall *VF0)(void*);
typedef void  (__thiscall *VF0v)(void*);
typedef void* (__thiscall *VF1)(void*, void*);
typedef void  (__thiscall *VF1v)(void*, void*);
typedef void* (__thiscall *VF2)(void*, void*, void*);
typedef void  (__thiscall *VF2v)(void*, void*, void*);
typedef void* (__thiscall *VF3)(void*, void*, void*, void*);
typedef void  (__thiscall *VF3v)(void*, void*, void*, void*);
typedef void* (__thiscall *VF4)(void*, void*, void*, void*, void*);
typedef void  (__thiscall *VF4v)(void*, void*, void*, void*, void*);
typedef void* (__thiscall *VF5)(void*, void*, void*, void*, void*, void*);
static inline void** VT(void* o) { return *(void***)o; }

// ---------------- UI::cSPUILayeredObject ----------------
struct cMWModel { u8 pad0[4]; void* pWorld; u8 pad8[0x40 - 8]; i32 mRefCount; u8 pad44[4]; };

// UI::cObjectWindowWinProc
struct WinProc {
    void** vtbl;   // +0
    void** vtbl2;  // +4
    void*  pad8;   // +8
    void*  owner;  // +0xc
};

struct cViewer {
    void* __thiscall Ctor();       // 0x7c3f70
    void  __thiscall Init(u8);     // 0x7c4dd0
    void  __thiscall Clear(int);   // 0x7c3c50
};

struct Matrix3 {
    f32 m[9];
    void __thiscall Assign(const void* src);   // 0x41cb40
};

class cSPUILayeredObject { public:
    void**  vtbl;        // +0
    i32     mRefCount;   // +4 (base RefCount)
    void*   mpViewer;    // +8
    void*   mpWindow;    // +0xc
    void*   mpWinProc;   // +0x10
    cMWModel** mModelsBegin;  // +0x14
    cMWModel** mModelsEnd;    // +0x18
    cMWModel** mModelsCap;    // +0x1c
    u32     pad20;       // +0x20
    u32     pad24;       // +0x24
    void*   p28;         // +0x28
    u16     w2c;         // +0x2c
    u16     w2e;         // +0x2e
    f32     f30;         // +0x30
    f32     f34;         // +0x34
    f32     f38;         // +0x38
    f32     f3c;         // +0x3c
    u8      mat40[0x24]; // +0x40 Matrix3
    f32     f64, f68, f6c, f70; // +0x64
    u8      flag74;      // +0x74
    u8      flag75;      // +0x75
    u8      flag76;      // +0x76
    u8      flag77;      // +0x77
    u8      flag78;      // +0x78
    u8      pad79[3];

    void AddRef()  { ((VF0v)VT(this)[1])(this); }   // vtable slot +4
    void Release() { ((VF0v)VT(this)[2])(this); }   // vtable slot +8

    cSPUILayeredObject* __thiscall ctor();          // 0x80e850
    void __thiscall dtor();                         // 0x80ead0
    u32  __thiscall RemoveModel(cMWModel* m);       // 0x80e980
    void __thiscall RemoveAllModels();              // 0x80ea50
    bool __thiscall RenderBegin(int);               // 0x80e270
    void __thiscall RenderEnd();                    // 0x80de20
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

class cSPUICustomRendererImpl { public:
    void** vtbl;         // +0   0x1417df8 / 0x1417e18
    void** vtbl2;        // +4   0x1417df4 / 0x1417e14
    u32    atomic8;      // +8
    LayerInfoVec mLayers;// +0xc
    u8     pad20[0x60 - 0x20];
    u8     sub60[0x1d4 - 0x60];
    u8     pad1d4[0x24c - 0x1d4];
    u8     b24c;         // +0x24c
    u8     pad24d[0x250 - 0x24d];
    void*  p250;         // +0x250
    void*  p254;         // +0x254
    void*  p258;         // +0x258
    void*  p25c;         // +0x25c
    void*  p260;         // +0x260

    void* __thiscall ctor();              // 0x80ebc0
    void* __thiscall VectorDtor(u8 flags);// 0x80ec40 (dtor w/ flag)
    void  __thiscall ScalarDtor();        // 0x80eca0
    void  __thiscall MethodF380(void*, void*, void*); // 0x80f380
};

// ---------------- vector helpers ----------------
struct PtrVec {
    void** begin;  // +0
    void** end;    // +4
    void** cap;    // +8
    void*  x0c;    // +0xc
    void*  inline_;// +0x10
    void __thiscall Insert1(void** pos, void** val);   // 0x80efe0
    void __thiscall Insert12(void** pos, void** val);  // 0x80f140
};

struct ObjVec {
    cSPUILayeredObject** begin;  // +0
    cSPUILayeredObject** end;    // +4
    cSPUILayeredObject** cap;    // +8
    void __thiscall InsertObj(cSPUILayeredObject** pos, cSPUILayeredObject** val); // 0x80ee90
};

struct ModelVec {
    cMWModel** begin;
    cMWModel** end;
    cMWModel** cap;
    void __thiscall DoDestroyValues(cMWModel** first, cMWModel** last); // 0x5f3680
};

// ---------------- UI::LayerManager ----------------
struct UI_LayerManager {
    void** vtbl;      // +0   0x1417de4
    void** vtbl2;     // +4   0x1417dd4
    u8     pad8[0xc - 8];
    cSPUILayeredObject** objBegin; // +0xc
    cSPUILayeredObject** objEnd;   // +0x10
    cSPUILayeredObject** objCap;   // +0x14
    u8     pad18[0x20 - 0x18];
    void*  v2begin;   // +0x20
    void*  v2end;     // +0x24
    void*  v2cap;     // +0x28
    u8     pad2c[0x34 - 0x2c];
    u8     b34;       // +0x34
    u8     pad35[0x38 - 0x35];
    i32    i38;       // +0x38
    void*  p3c;       // +0x3c
    PtrVec mLayerWorlds; // +0x40
    u8     pad54[0x94 - 0x54];
    u8     b94;       // +0x94

    UI_LayerManager* __thiscall ctor();  // 0x80edb0
    void* __thiscall VectorDtor(u8); // 0x80ee10
    void __thiscall Render(void*, int, void*, void*); // 0x80e6b0
    bool __thiscall Init();                            // 0x80f530
    cSPUILayeredObject* __thiscall AddObject();        // 0x80f730
};

struct BoxList {
    u8  pad0[0xc];
    void** begin;   // +0xc
    void** end;     // +0x10
};

struct cMWRenderModel {
    u8  pad0[8];
    void* mpViewer;   // +8
    u8  padC[0x28 - 0xc];
    void* p28;        // +0x28
    u8  pad2c[0x77 - 0x2c];
    u8  b77;          // +0x77
    u8  pad78[4];
    bool __thiscall RenderBegin(int);   // 0x80e270
    void __thiscall RenderEnd();        // 0x80de20
};

extern f32 g_164cd08, g_164cd0c, g_164cd10, g_1485720;

// =========================== bodies ===========================

// @ 0x0080e6b0
void __thiscall UI_LayerManager::Render(void* target, int index, void* a3, void* a4)
{
    struct Msg { void* layer; u8 flag; };
    i38 = index;
    fnFun82e4b0(a4);
    fnFun82e4c0(a3);
    if (target) {
        void* r = ((VF0)VT(target)[4 / 4])(target);
        void* f = ((VF0)VT(r)[0x34 / 4])(r);
        f32 v[4];
        v[0] = ((f32*)f)[0]; v[1] = ((f32*)f)[1];
        v[2] = ((f32*)f)[2]; v[3] = ((f32*)f)[3];
        ((VF1v)VT(target)[0x2c / 4])(target, &v[0]);
    }
    BoxList* box = (BoxList*)fnAddBoundingBox();
    Msg msg;
    msg.layer = 0;
    if ((u32)i38 < 0xf)
        msg.layer = mLayerWorlds.begin[i38];
    msg.flag = 1;
    void* srv = fnMessageServer();
    ((VF3v)VT(srv)[0x14 / 4])(srv, (void*)0x24e5e7f, &msg, 0);
    int n = (int)((u8*)box->end - (u8*)box->begin) >> 2;
    for (int i = 0; i < n; ++i) {
        cSPUILayeredObject* o = (cSPUILayeredObject*)box->begin[i];
        if (!o->flag77) continue;
        if (!o->RenderBegin(i38)) continue;
        ((cViewer*)o->mpViewer)->Clear(6);
        void* lr = ((VF0)VT(msg.layer)[0x13c / 4])(msg.layer);
        ((VF4v)VT(lr)[0xc / 4])(lr, 0, 0, &msg, a4);
        if (o->p28)
            ((VF4v)VT(o->p28)[0xc / 4])(o->p28, 0, 0, &msg, a4);
        o->RenderEnd();
    }
    msg.flag = 0;
    void* srv2 = fnMessageServer();
    ((VF3v)VT(srv2)[0x14 / 4])(srv2, (void*)0x24e5e7f, &msg, 0);
    i38 = -1;
    fnFun82e4b0(0);
}

// @ 0x0080e850
cSPUILayeredObject* __thiscall cSPUILayeredObject::ctor()
{
    mRefCount = 0;
    vtbl = (void**)0x1417dc4;
    mpViewer = 0;
    mpWindow = 0;
    mpWinProc = 0;
    mModelsBegin = 0; mModelsEnd = 0; mModelsCap = 0;
    p28 = 0;
    w2e = 0;
    w2c = 0;
    f30 = g_164cd08;
    f34 = g_164cd0c;
    f38 = g_164cd10;
    f3c = g_1485720;
    ((Matrix3*)mat40)->Assign((const void*)0x164ce30);
    f64 = 0.0f; f68 = 0.0f; f6c = 0.0f; f70 = 0.0f;
    flag74 = 0; flag75 = 0; flag76 = 0; flag77 = 0; flag78 = 1;

    void* v = GameAlloc(0x174, "UI/cSPUILayeredObject/cViewer", 0, 0, 0, 0);
    if (v) v = ((cViewer*)v)->Ctor();
    mpViewer = v;
    ((cViewer*)v)->Init(0);

    WinProc* wp = (WinProc*)GameAlloc(0x10, "UI/cObjectWindowWinProc", 0, 0, 0, 0);
    if (wp) {
        wp->vtbl2 = (void**)0x13ef094;
        wp->pad8 = 0;
        wp->vtbl = (void**)0x1417d6c;
        wp->vtbl2 = (void**)0x14188c0;
        wp->owner = this;
    } else
        wp = 0;

    WinProc* old = (WinProc*)mpWinProc;
    if (wp != old) {
        if (wp) ((VF0v)VT(wp)[0])(wp);
        mpWinProc = wp;
        if (old) ((VF0v)VT(old)[1])(old);
    }
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
            void* world = param->pWorld;
            ((VF1v)VT(world)[0x16c / 4])(world, param);
            cMWModel* last = mModelsEnd[-1];
            cMWModel* old = mModelsBegin[i];
            if (last != old) {
                if (last) last->mRefCount += 1;
                mModelsBegin[i] = last;
                if (old) {
                    if (old->mRefCount > 1) old->mRefCount -= 1;
                    else { void* w = old->pWorld; ((VF1v)VT(w)[0x170 / 4])(w, old); }
                }
            }
            mModelsEnd -= 1;
            cMWModel* tail = mModelsEnd[0];
            if (tail) {
                if (tail->mRefCount > 1) tail->mRefCount -= 1;
                else { void* w = tail->pWorld; ((VF1v)VT(w)[0x170 / 4])(w, tail); }
            }
            f6c = 0.0f;
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
    vtbl = (void**)0x1417dc4;
    while (mModelsBegin != mModelsEnd) RemoveModel(*mModelsBegin);
    Fun_7c3ba0(mpViewer);
    void* viewer = mpViewer;
    if (viewer) {
        Fun_7c4000(viewer);
        GameFree(viewer);
    }
    mpViewer = 0;
    void* win = mpWindow;
    if (win) {
        if (flag74) ((VF1v)VT(win)[0x108 / 4])(win, mpWinProc);
        void* w = mpWindow;
        if (w) { mpWindow = 0; ((VF0v)VT(w)[1])(w); }
        flag74 = 0;
    }
    void* wp = mpWinProc;
    if (wp) { mpWinProc = 0; ((VF0v)VT(wp)[1])(wp); }
    if (p28) ((VF0v)VT(p28)[1])(p28);
    ((ModelVec*)&mModelsBegin)->DoDestroyValues(mModelsBegin, mModelsEnd);
    void* mb = mModelsBegin;
    if (mb && ((u32*)mb)[-1]) GameFree(mb);
    if (mpWinProc) ((VF0v)VT(mpWinProc)[1])(mpWinProc);
    if (mpWindow) ((VF0v)VT(mpWindow)[1])(mpWindow);
    vtbl = (void**)0x13ec458;
}

// @ 0x0080ebc0
void* __thiscall cSPUICustomRendererImpl::ctor()
{
    vtbl = (void**)0x14426a0;
    vtbl2 = (void**)0x13ef094;
    atomic8 = 0;
    vtbl = (void**)0x1417df8;
    vtbl2 = (void**)0x1417df4;
    void* inl = (u8*)this + 0x24;
    mLayers.inline_ = inl;
    mLayers.end = inl;
    mLayers.begin = inl;
    mLayers.cap = (u8*)inl + 0x3c;
    ((cViewer*)((u8*)this + 0x60))->Ctor();
    b24c = 0;
    ((cViewer*)((u8*)this + 0x60))->Init(0);
    fnMemSet((u8*)this + 0x1d4, 0, 0x78);
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
UI_LayerManager* __thiscall UI_LayerManager::ctor()
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
    return this;
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

// @ 0x0080efe0
void __thiscall PtrVec::Insert1(void** pos, void** val)
{
    if (end != cap) {
        void** e = end;
        void** v = val;
        if (val >= pos && val < e) v = val + 1;
        if (e) {
            void* o = e[-1];
            *e = o;
            if (o) ((VF0v)VT(o)[0])(o);
        }
        fnCopyBackward4(pos, e - 1, e);
        void* nv = *v;
        void* ov = *pos;
        if (nv != ov) {
            if (nv) ((VF0v)VT(nv)[0])(nv);
            *pos = nv;
            if (ov) ((VF0v)VT(ov)[1])(ov);
        }
        end = e + 1;
        return;
    }
    u32 n = (u32)(end - begin);
    u32 nc = n ? n * 2 : 1;
    void** mem = nc ? (void**)GameAlloc(nc * 4, (const char*)0x13f6b3c, 0, 0, (int)0x13ebb38, 0xd1) : 0;
    void** mid = (void**)fnUninitCopy4(begin, pos, mem);
    fnDestroy4(begin, pos, mem);
    if (mid) {
        void* o = *val;
        *mid = o;
        if (o) ((VF0v)VT(o)[0])(o);
    }
    void** nend = (void**)fnUninitCopy4(pos, end, mid + 1);
    fnDestroy4(pos, end, mid + 1);
    if (begin && (void*)begin != inline_) GameFree(begin);
    begin = mem;
    end = nend;
    cap = mem + nc;
}

// @ 0x0080f140
void __thiscall PtrVec::Insert12(void** pos, void** val)
{
    if (end != cap) {
        void** e = end;
        void** v = val;
        if (val >= pos && val < e) v = (void**)((u8*)val + 0xc);
        if (e) {
            void* o = e[-3];
            *e = o;
            if (o) ((VF0v)VT(o)[0])(o);
            e[1] = e[-2];
            e[2] = e[-1];
        }
        fnCopyBackward12(pos, (void**)((u8*)e - 0xc), e);
        void* nv = *v;
        void* ov = *pos;
        if (nv != ov) {
            if (nv) ((VF0v)VT(nv)[0])(nv);
            *pos = nv;
            if (ov) ((VF0v)VT(ov)[1])(ov);
        }
        pos[1] = v[1];
        pos[2] = v[2];
        end = (void**)((u8*)e + 0xc);
        return;
    }
    u32 n = (u32)((u8*)end - (u8*)begin) / 0xc;
    u32 nc = n ? n * 2 : 1;
    void** mem = nc ? (void**)GameAlloc(nc * 0xc, (const char*)0x13f6b3c, 0, 0, (int)0x13ebb38, 0xd1) : 0;
    void** mid = (void**)fnUninitCopy12(begin, pos, mem);
    fnDestroy12(begin, pos, mem);
    if (mid) {
        void* o = *val;
        *mid = o;
        if (o) ((VF0v)VT(o)[0])(o);
        mid[1] = val[1];
        mid[2] = val[2];
    }
    void** nend = (void**)fnUninitCopy12(pos, end, mid + 3);
    fnDestroy12(pos, end, mid + 3);
    if (begin && (void*)begin != inline_) GameFree(begin);
    begin = mem;
    end = nend;
    cap = mem + nc * 3;
}

// free-function form so FUN_0080f360 can tail-call it
void __fastcall FUN_0080f2e0(char* self, void** obj, void* a, void* b);
// @ 0x0080f2e0
void __fastcall FUN_0080f2e0(char* self, void** obj, void* a, void* b)
{
    void* o = (void*)obj;      // the object itself (original stores it directly)
    void* lc = o;
    if (o) ((VF0v)VT(o)[0])(o);
    PtrVec* v = (PtrVec*)(self + 0xc);
    if (v->end < v->cap) {
        void** e = v->end;
        v->end = (void**)((u8*)e + 0xc);
        if (e) {
            e[0] = o;
            if (o) ((VF0v)VT(o)[0])(o);
            e[1] = a;
            e[2] = b;
        }
    } else {
        v->Insert12(v->end, &lc);
        o = lc;
    }
    if (o) ((VF0v)VT(o)[1])(o);
}

// @ 0x0080f360
void __fastcall FUN_0080f360(char* p, void** obj, void* a, void* b)
{
    char* q = p ? p - 0xc : 0;
    FUN_0080f2e0(q, obj, a, b);
}

// @ 0x0080f380
void __thiscall cSPUICustomRendererImpl::MethodF380(void* a1, void* a2, void* a3)
{
    p25c = a1;
    void* mgr = ModelManagerGet();
    void* r = ((VF3)VT(mgr)[0x14 / 4])(mgr, a1, 0, 0);
    if (r != p258) {
        if (r) ((VF0v)VT(r)[0])(r);
        void* old = p258;
        p258 = r;
        if (old) ((VF0v)VT(old)[1])(old);
    }
    ((VF3v)VT(p258)[0x140 / 4])(p258, a3, 0, (void*)1);
    ((VF1v)VT(p258)[0x134 / 4])(p258, (void*)1);
    void* x = ((VF2)VT(p258)[0x13c / 4])(p258, (void*)0xd, (void*)0x7f00);
    FUN_0080f2e0((char*)this, (void**)x, (void*)0xd, (void*)0x7f00);
    if (a2) {
        void* e = fnGet6eea10();
        if (e != p250) {
            if (e) ((VF0v)VT(e)[0])(e);
            void* old = p250;
            p250 = e;
            if (old) ((VF0v)VT(old)[1])(old);
        }
        ((VF1v)VT(p250)[0x78 / 4])(p250, 0);
        ((VF2v)VT(p250)[0x84 / 4])(p250, (u8*)this + 0x60, 0);
        ((VF1v)VT(p250)[0x88 / 4])(p250, a3);
        void* y = ((VF2)VT(p250)[0xa0 / 4])(p250, (void*)0x12, 0);
        FUN_0080f2e0((char*)this, (void**)y, (void*)0x12, 0);
        p260 = a2;
        void* em = EffectsManagerGet();
        void* f = ((VF2)VT(em)[0x4c / 4])(em, a2, 0);
        if (f != p254) {
            if (f) ((VF0v)VT(f)[0])(f);
            void* old = p254;
            p254 = f;
            if (old) ((VF0v)VT(old)[1])(old);
        }
        ((VF1v)VT(p254)[0x1c / 4])(p254, p250);
        ((VF1v)VT(p254)[0x24 / 4])(p254, (void*)6);
        ((VF1v)VT(p258)[0x148 / 4])(p258, p254);
    }
}

// @ 0x0080f530
bool __thiscall UI_LayerManager::Init()
{
    if (b34) return true;
    b34 = 1;

    void* mgr = ModelManagerGet();
    void* mw = ((VF3)VT(mgr)[0x14 / 4])(mgr, (void*)0x32fab08, (void*)"UILayerModelWorld", 0);
    if (mw != p3c) {
        if (mw) ((VF0v)VT(mw)[0])(mw);
        void* old = p3c;
        p3c = mw;
        if (old) ((VF0v)VT(old)[1])(old);
    }

    void* lm = LightingManagerGet();
    void* light = ((VF5)VT(lm)[0x18 / 4])(lm, (void*)0x4a497e9, 0, (void*)0x934d9760, 0, (void*)1);
    ((VF1v)VT(p3c)[0x140 / 4])(p3c, light);

    for (int i = 0xf; i != 0; --i) {
        void* zero = 0;
        if (mLayerWorlds.end < mLayerWorlds.cap) {
            *mLayerWorlds.end = 0;
            mLayerWorlds.end = mLayerWorlds.end + 1;
        } else {
            mLayerWorlds.Insert1(mLayerWorlds.end, (void**)&zero);
            if (zero) ((VF0v)VT(zero)[1])(zero);
        }
        void* last = mLayerWorlds.end[-1];
        if (last != p3c) {
            if (p3c) ((VF0v)VT(p3c)[0])(p3c);
            mLayerWorlds.end[-1] = p3c;
            if (last) ((VF0v)VT(last)[1])(last);
        }
    }

    if ((u32)((u8*)objCap - (u8*)objBegin) / 4 < 0x20) {
        void* mem = GameAlloc(0x80, (const char*)0x13f6b3c, 0, 0, (int)0x13ebb38, 0xd1);
        u32 bytes = (u32)((u8*)objEnd - (u8*)objBegin);
        fnMemCpy(mem, objBegin, bytes);
        if (objBegin && ((u32*)objBegin)[-1]) GameFree(objBegin);
        u32 count = bytes / 4;
        objBegin = (cSPUILayeredObject**)mem;
        objEnd = (cSPUILayeredObject**)((u8*)mem + count * 4);
        objCap = (cSPUILayeredObject**)((u8*)mem + 0x80);
    }

    void* dm = fnMgr67dd50();
    ((VF3v)VT(dm)[0x4c / 4])(dm, this, (void*)0x1e, 0);
    ((VF1v)VT(p3c)[0x134 / 4])(p3c, (void*)1);

    u32 mask[4] = { 0, 0, 0, 0 };
    void* mm = ModelManagerGet();
    u32 bit = (u32)(size_t)((VF2)VT(mm)[0x28 / 4])(mm, (void*)0x32fab27, 0);
    if (bit < 0x40)
        mask[bit >> 5] |= 1u << (bit & 0x1f);
    ((VF3v)VT(p3c)[0x11c / 4])(p3c, &mask[0], &mask[2], 0);
    return true;
}

// @ 0x0080f730
cSPUILayeredObject* __thiscall UI_LayerManager::AddObject()
{
    cSPUILayeredObject* obj = (cSPUILayeredObject*)
        GameAlloc(0x7c, "UI/cSPUILayeredObject", 0, 0, 0, 0);
    if (obj) obj = obj->ctor();
    cSPUILayeredObject* local = obj;
    if (obj) obj->AddRef();
    if (objEnd < objCap) {
        cSPUILayeredObject** e = objEnd;
        objEnd = e + 1;
        if (e) {
            *e = obj;
            if (obj) obj->AddRef();
        }
    } else {
        ((ObjVec*)((u8*)this + 0xc))->InsertObj(objEnd, &local);
    }
    if (local) local->Release();
    return obj;
}

// 0x80ee90 -- object-vector grow/reinsert (slots +4 AddRef, +8 Release)
void __thiscall ObjVec::InsertObj(cSPUILayeredObject** pos, cSPUILayeredObject** val)
{
    if (end != cap) {
        cSPUILayeredObject** e = end;
        cSPUILayeredObject** v = val;
        if (val >= pos && val < e) v = val + 1;
        if (e) {
            cSPUILayeredObject* o = e[-1];
            *e = o;
            if (o) o->AddRef();
        }
        fnCopyBackwardRef((void**)pos, (void**)(e - 1), (void**)e);
        cSPUILayeredObject* nv = *v;
        cSPUILayeredObject* ov = *pos;
        if (nv != ov) {
            if (nv) nv->AddRef();
            *pos = nv;
            if (ov) ov->Release();
        }
        end = e + 1;
        return;
    }
    u32 n = (u32)(end - begin);
    u32 nc = n ? n * 2 : 1;
    cSPUILayeredObject** mem = nc ? (cSPUILayeredObject**)
        GameAlloc(nc * 4, (const char*)0x13f6b3c, 0, 0, (int)0x13ebb38, 0xd1) : 0;
    u32 b1 = (u32)((u8*)pos - (u8*)begin);
    fnMemCpy(mem, begin, b1);
    cSPUILayeredObject** mid = (cSPUILayeredObject**)((u8*)mem + (b1 & ~3u));
    if (mid) {
        cSPUILayeredObject* o = *val;
        *mid = o;
        if (o) o->AddRef();
    }
    u32 b2 = (u32)((u8*)end - (u8*)pos);
    fnMemCpy(mid + 1, pos, b2);
    cSPUILayeredObject** nend = (cSPUILayeredObject**)((u8*)(mid + 1) + (b2 & ~3u));
    if (begin && ((u32*)begin)[-1] != 0) GameFree(begin);
    end = nend;
    begin = mem;
    cap = mem + nc;
}

// 0x5f3680 -- vector<AutoRefCount<cMWModel>>::DoDestroyValues(first,last)
void __thiscall ModelVec::DoDestroyValues(cMWModel** first, cMWModel** last)
{
    for (cMWModel** p = first; p < last; ++p) {
        cMWModel* m = *p;
        if (m) {
            if (m->mRefCount > 1) m->mRefCount -= 1;
            else { void* w = m->pWorld; ((VF1v)VT(w)[0x170 / 4])(w, m); }
        }
    }
}
