// slice s00764df0
// SP::cGraphicsResourceFactory raster/game-mesh/arena serialization tail.
// flags: /O2 /MD /Gy /EHsc /TP /GS-
#include <intrin.h>
#include <new>
#include "types.h"

// ---------------------------------------------------------------------------
// @ 0x007650d0 / 0x00765150  loader dispatch wrappers
struct Ctx764df0 { char CreateRaster(void* a, void* b, void* c); };   // 0x764df0 thiscall, 3 args
struct Ctx764a50 { char ReadArena(void* a, void* b, void* c); };      // 0x764a50 thiscall, 3 args

struct Loader29 {
    char pad0[0xc];
    void* pC;                  // +0xc
    char pad10[4];
    void* p14;                 // +0x14
    char pad18[0x10];
    void* p28;                 // +0x28
    char p2c[0x308];           // +0x2c
    unsigned char b334;
    void WrapDf0(int);
    void WrapA50(int);
};

// @ 0x00765150
void Loader29::WrapDf0(int) {
    Ctx764df0* ctx = (Ctx764df0*)pC;
    char ok = ctx->CreateRaster(p2c, p28, p14);
    if (ok)
        b334 = 1;
}

// @ 0x007650d0
void Loader29::WrapA50(int) {
    ((Ctx764a50*)pC)->ReadArena(p2c, p28, p14);
}

// ===========================================================================
// @ 0x00765980  eastl hashtable bucket-array grow
extern "C" {
void* __cdecl EA_New(uint32_t size, const char* f, int a, int b, const char* g, int line); // 0x0f473a0
void  __cdecl EA_Delete(void* p);                                                          // 0x0f47380
void  __cdecl DoFreeNodes(void* b, void* e, void* n);                                      // 0x04554f0
}
extern const char g_allocFile[];   // 0x13ebb38
struct Node8 { int x, y; };
struct HVec { Node8* b; Node8* e; Node8* cap; void grow(unsigned n); };
void HVec::grow(unsigned n) {
    if (n > (unsigned)(cap - b)) {
        Node8* newp = n ? (Node8*)EA_New(n * 8, "Graphics", 0, 0, g_allocFile, 0xd1) : 0;
        DoFreeNodes(b, e, newp);
        if (b && *(int*)((char*)b - 4) != 0)
            EA_Delete(b);
        Node8* oldb = b;
        size_t count = e - oldb;
        b = newp;
        e = newp + count;
        cap = newp + n;
    }
}

// ===========================================================================
// @ 0x00765ac0  destructor: owned-pointer vector at +0x78 and vector at +0x20
struct Vec { void** b; void** e; void** cap; int alloc; void** inlinebuf; };
struct D765ac0 {
    char pad[0x20];
    Vec v20;                 // +0x20
    char padX[0x78 - 0x34];
    Vec v78;                 // +0x78
    ~D765ac0();
};
D765ac0::~D765ac0() {
    int n = (int)(v78.e - v78.b);
    for (int i = 0; i < n; i++) {
        if (v78.b[i])
            EA_Delete(v78.b[i]);
    }
    if (v78.b && v78.b != v78.inlinebuf)
        EA_Delete(v78.b);
    if (v20.b && v20.b != v20.inlinebuf)
        EA_Delete(v20.b);
}

// ===========================================================================
// ctor (partial: EH frame / member model not reproduced)
struct IUnknown32 { virtual void u0(); virtual void u1(); virtual void u2(); };
struct AtomicInt { int v; int operator=(int x) { return _InterlockedExchange((volatile long*)&v, x); } };
struct Resource : IUnknown32 {
    AtomicInt mRefCount; int k0, k1, k2;
    Resource() { mRefCount = 0; k0 = 0; k1 = 0; k2 = 0; }
};
struct cResourceBase : Resource { int* cb; cResourceBase() { cb = 0; } };
struct D765f10 : cResourceBase {
    int f18;
    void* f1c;
    D765f10(void* arg);
};
// @ 0x00765f10
D765f10::D765f10(void* arg) {
    f18 = 0;
    f1c = arg;
    if (arg)
        ((IUnknown32*)arg)->u0();
    f18 = 0;
}

// ===========================================================================
struct RefCountedBase { virtual void dtor(int); };
struct AutoRcT { RefCountedBase* p; };          // +8, released by ~D765580
struct FactoryBase { void* vptr; int f4; };     // +0 vtable, +4
extern void* g_vtblD765580;                     // 0x140e09c
extern void* g_vtblFactoryBase;                 // 0x13effb8
struct D765580 : FactoryBase {
    AutoRcT m8;    // +8
    ~D765580();
};
// @ 0x00765580  ~cGraphicsResourceFactory (refcounted cJobLock member at +8)
D765580::~D765580() {
    vptr = &g_vtblD765580;
    RefCountedBase* q = m8.p;
    if (q) {
        int n = _InterlockedExchangeAdd((volatile long*)((char*)q + 4), -1) - 1;
        if (n == 0) {
            _InterlockedExchange((volatile long*)((char*)q + 4), 1);
            if (q)
                q->dtor(1);
        }
    }
    vptr = &g_vtblFactoryBase;
}

// ===========================================================================
// shared stubs for the functions below
struct RefIface { virtual void AddRef(); virtual void Release(); };
struct ArenaHolder : RefIface { char pad[0x14]; void* arenaPtr; };   // +0x18 arena (rw::core::arena::Arena*)
struct Elem { uint32_t a, b; Elem(); ~Elem(); };               // 0x006c0fa0 / 0x00c2e4e0
struct Res16 { void* m[4]; Res16() { for (int i = 0; i < 4; i++) m[i] = 0; } };
struct RDesc2 { Elem d[4]; RDesc2() { d[0].a = 0; d[0].b = 1; } };
__declspec(noinline) Elem::Elem() { a = 0; b = 1; }     // 0x006c0fa0
__declspec(noinline) Elem::~Elem() {}                    // 0x00c2e4e0
struct ExpObj { uint32_t type; void* obj; Res16 res; RDesc2 rd;
    ExpObj() : type(0), obj(0) {}
};
struct Arena {
    int GetNumExportedObjects();                           // 0x011e23a0
    void GetExportedObjectByIndex(int idx, ExpObj* out);   // 0x011e28e0
};
bool __cdecl SetCachingType(int type, void* obj);          // 0x006ac040
struct RefObj2 { virtual void s0(); virtual void s1(); virtual void s2(); };
struct D7643d0 {                  // two refcounted handles (release = slot 1)
    RefObj2* a;                   // +0
    RefObj2* b;                   // +4
    D7643d0() { a = 0; b = 0; }
    ~D7643d0();                   // 0x007643d0
    RefObj2** ResetB() { if (b) { RefObj2* t = b; b = 0; t->s1(); } return &b; }
};

// ===========================================================================
// @ 0x00764df0  CreateRasterFromArena: find the 0x20003 exported object of the arena resource
struct ArenaSrc { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                  virtual void Get(RefIface** out); };      // slot 5
struct CreateRasterIn { ArenaSrc* loader; ArenaHolder* res; };
struct CreateRasterOut { char pad[0x18]; void* cell; RefIface* ref; };     // +0x18, +0x1c

namespace SP {
class cGraphicsResourceFactory {
public:
    bool CreateRasterFromArena(CreateRasterIn* in, void* z, CreateRasterOut* out);   // 00764df0
    bool Fn7655f0(void* a, void* b, void* c);                                        // 007655f0
};
}

// @ 0x00764df0
bool SP::cGraphicsResourceFactory::CreateRasterFromArena(CreateRasterIn* in, void* z, CreateRasterOut* out) {
    ArenaSrc* ld = in->loader;
    if (ld) {
        ArenaHolder* old = in->res;
        if (old) { in->res = 0; old->Release(); }
        ld->Get((RefIface**)&in->res);
    }
    ArenaHolder* res = in->res;
    if (res) {
        Arena* arena = (Arena*)res->arenaPtr;
        SetCachingType(2, res);
        uint32_t n = arena->GetNumExportedObjects();
        for (uint32_t i = 0; i < n; i++) {
            void* cell;
            {
                ExpObj e;
                arena->GetExportedObjectByIndex(i, &e);
                if (e.type != 0x20003) continue;
                cell = e.obj;
            }
            if (!cell) break;
            out->cell = cell;
            RefIface* old = out->ref;
            if ((RefIface*)res != old) {
                res->AddRef();
                out->ref = res;
                if (old) old->Release();
            }
            return true;
        }
    }
    return false;
}

// ===========================================================================
// @ 0x007655f0  resource-manager async load wrapper
struct ResMgr { virtual void v0(); virtual void v1(); virtual void v2();
                virtual char Get(void* a, RefObj2** out, int z, void* b, void* self, void* c); };   // slot 3, ret 0x18
void* __cdecl GetManager();                                // 0x0067dcd0
// @ 0x007655f0
bool SP::cGraphicsResourceFactory::Fn7655f0(void* a, void* b, void* c) {
    D7643d0 d;
    ResMgr* mgr = (ResMgr*)GetManager();
    if (mgr->Get(c, d.ResetB(), 0, a, this, c))
        return CreateRasterFromArena((CreateRasterIn*)&d, 0, (CreateRasterOut*)b);
    return 0;
}

// ===========================================================================
// @ 0x007650f0  async arena finish
struct ArenaOwner { void* arena; };
struct Obj34 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
               virtual void Fn5(); virtual void v6(); virtual ArenaOwner* Fn7(); };
struct Rec30 { char pad[0x18]; void* f18; };
bool __cdecl FUN_763fd0(void* arena);                      // 0x00763fd0
namespace SP { class cGraphicsResourceFactory2 { public: bool FixupArena(ArenaOwner* p); }; }   // 0x00764580
struct LoaderF0 {
    char pad0[0xc];
    SP::cGraphicsResourceFactory2* pC;    // +0xc
    char pad10[0x20];
    Rec30* p30;                           // +0x30
    Obj34* p34;                           // +0x34
    char pad38[0x334 - 0x38];
    unsigned char b334;
    bool Fn7650f0(int);
};
// @ 0x007650f0
bool LoaderF0::Fn7650f0(int) {
    SP::cGraphicsResourceFactory2* f = pC;
    ArenaOwner* o = p34->Fn7();
    void* arena = o->arena;
    if (!f->FixupArena(o))
        return false;
    if (FUN_763fd0(arena))
        p34->Fn5();
    p30->f18 = arena;
    b334 = 1;
    return true;
}

// ===========================================================================
// @ 0x00764f60  WriteResourceGameMeshes
struct IStream_;
struct Mesh764 { char pad[8]; char* recs; };               // +8 record array (0x20 stride)
struct GameMeshes { char pad[8]; char f8[0x10]; Mesh764** begin; Mesh764** end; };   // +8 object, +0x18/+0x1c vector
bool __cdecl WriteUint32(IStream_* s, const uint32_t* p, uint32_t n, int endian);       // 0x0093aa70
bool __cdecl WriteMesh(IStream_* s, Mesh764* m);                                        // 0x0071e390
int  __cdecl FUN_71ddc0(Mesh764* m, int a, int b, int c, int d);                        // 0x0071ddc0
struct MatRec { uint32_t a, b; uint16_t c, d; RefIface* e;
    MatRec(const MatRec& o) : a(o.a), b(o.b), c(o.c), d(o.d), e(o.e) { if (e) e->AddRef(); }
    ~MatRec() { if (e) e->Release(); } };
struct MaterialMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void Fn17(uint32_t a, uint32_t b, IStream_* s, void* c); };            // slot 0x44
MaterialMgr* __cdecl GetMaterialManager();                                              // 0x0067dd70
static __forceinline void W32(IStream_* s, uint32_t x) { WriteUint32(s, &x, 1, 0); }
// @ 0x00764f60
bool __stdcall FUN_764f60(GameMeshes* g, IStream_* s) {
    int n = (int)(g->end - g->begin);
    W32(s, 1);
    W32(s, n);
    for (int i = 0; i < n; i++) {
        Mesh764** pp = g->begin + i;
        if (!WriteMesh(s, *pp))
            return false;
    }
    for (int i = 0; i < n; i++) {
        Mesh764* m = g->begin[i];
        int idx = FUN_71ddc0(m, 0x15, 0, 6, 8);
        if (idx >= 0) {
            MatRec* r = (MatRec*)(m->recs + idx * 0x20 + 0x10);
            MatRec copy(*r);
            GetMaterialManager()->Fn17(copy.a, copy.b, s, g->f8);
        }
    }
    return true;
}

// ===========================================================================
// @ 0x007656c0  read/serialize game-mesh record stream
struct AtomicL {
    volatile long v;
    __forceinline long Increment() { return _InterlockedExchangeAdd(&v, 1) + 1; }
    __forceinline long Decrement() { return _InterlockedExchangeAdd(&v, -1) - 1; }
    __forceinline long GetValue() { return _InterlockedExchangeAdd(&v, 0); }
};
struct RcObj { uint32_t p0, p4; AtomicL rc; };
static __forceinline void RcAddRef(RcObj* p) { p->rc.Increment(); }
static __forceinline void RcRelease(RcObj* p) {
    p->rc.Decrement();
    if (p->rc.GetValue() < 1)
        p->rc.Increment();
    else
        p->rc.GetValue();
}
struct RcRef {
    RcObj* p;
    RcRef(RcObj* q) : p(q) { if (p) RcAddRef(p); }
    ~RcRef() { if (p) RcRelease(p); }
    void Reset() { if (p) { RcObj* t = p; p = 0; RcRelease(t); } }
    void Assign(RcObj* q) {
        RcObj* old = p;
        if (q != old) {
            if (q) RcAddRef(q);
            p = q;
            if (old) RcRelease(old);
        }
    }
};
struct SlotEnt { uint32_t a; RcObj* ref; uint32_t c, d; };
struct MeshS { char pad4[4]; uint16_t w4; uint16_t w6; void* p8; uint32_t cnt; SlotEnt ents[1]; };   // ents at +0x10
struct MeshVec { char pad[8]; MeshS** begin; MeshS** end; };
struct WStream7 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13();
    virtual uint32_t Write(const void* p, uint32_t n);   // slot 14 (+0x38)
};
struct KeyOut { uint32_t instance, type, group; };
struct KeyMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void GetKey(KeyOut* out, RcObj* h); };      // slot 11 (+0x2c)
KeyMgr* __cdecl FUN_67dd60();                           // 0x0067dd60
uint32_t __cdecl FUN_778050(uint32_t t);                // 0x00778050
// @ 0x007656c0
bool __stdcall FUN_7656c0(WStream7* s, MeshVec* o) {
    uint32_t count = (uint32_t)(o->end - o->begin);
    s->Write(&count, 4);
    for (uint32_t i = 0; i < count; i++) {
        uint32_t t = (*(o->begin + i))->w4;
        s->Write(&t, 4);
        if (t != 0x20d) {
            MeshS** pp = o->begin + i;
            s->Write((*pp)->p8, FUN_778050(t));
        } else {
            MeshS* m = o->begin[i];
            uint32_t n = m->cnt;
            s->Write(&n, 4);
            for (uint32_t j = 0; j < n; j++) {
                SlotEnt* e = &m->ents[j];
                RcRef h(e->ref);
                RcRef* er = (RcRef*)&e->ref;
                er->Reset();
                s->Write(e, 0x10);
                KeyOut k;
                FUN_67dd60()->GetKey(&k, h.p);
                s->Write(&k.instance, 4);
                s->Write(&k.group, 4);
                er->Assign(h.p);
            }
        }
    }
    return true;
}

// ===========================================================================
// shared job machinery (SP::cJob, jobs started by the async resource loaders)
struct cJob {
    void* mpCallback;           // +0
    void* mpCallbackData;       // +4
    char pad08[0x10];
    uint32_t mFlags;            // +0x18
    void SetCallback(void* f, void* d) { mpCallback = f; mpCallbackData = d; }
    int  Release();                       // 0x00690120
    void Queue();                         // 0x006909b0
    void SetOwner(void* o);               // 0x0068f9b0 (AddRefs the owner into mpExtraObject)
    void AddDependency(cJob* other);      // 0x00691380
};
struct JobRefL {
    cJob* p;
    JobRefL() : p(0) {}
    ~JobRefL() { if (p) p->Release(); }
    void Reset() { if (p) { cJob* t = p; p = 0; t->Release(); } }
};
struct IJobMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual bool CreateJob(JobRefL* out);     // slot 4 (+0x10)
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual void Lock();                      // slot 8 (+0x20)
    virtual void Unlock();                    // slot 9 (+0x24)
};
IJobMgr* __cdecl GetJobManager();             // 0x0068f4d0
struct JobLockL {
    IJobMgr* m;
    JobLockL(IJobMgr* x) : m(x) { m->Lock(); }
    ~JobLockL() { m->Unlock(); }
};
void __cdecl Job7651a0(void*);                // 0x007651a0
void __cdecl Job7651b0(void*);                // 0x007651b0
void __cdecl Job7651c0(void*);                // 0x007651c0

struct IRef2 { virtual void v0(); virtual void Release(); virtual void v2(); virtual void* Query(uint32_t id); };   // slot 3 = Query
struct ReqState {
    IRef2* a;                   // +0
    IRef2* b;                   // +4
    uint32_t c;                 // +8
    char padc[0xd0 - 0xc];
    uint32_t state;             // +0xd0
    __forceinline IRef2** Init() { state = 2; a = 0; IRef2** pb = &b; *pb = 0; return pb; }
};

// @ 0x00765b30  async arena request start (two chained jobs)
struct AsyncReqB {
    char pad0[0x18];
    uint32_t id18;              // +0x18
    char pad1c[0x10];
    ReqState st;                // +0x2c
    bool Start(JobRefL* out);
};
// @ 0x00765b30
bool AsyncReqB::Start(JobRefL* out) {
    if (id18 != 0x2f4e681b)
        return false;
    st.state = 5;
    st.b = 0;
    st.c = 0;
    JobLockL lock(GetJobManager());
    JobRefL a;
    {
        IJobMgr* m = GetJobManager();
        a.Reset();
        if (!m->CreateJob(&a))
            return false;
    }
    JobRefL b;
    {
        IJobMgr* m = GetJobManager();
        b.Reset();
        if (!m->CreateJob(&b))
            return false;
    }
    a.p->SetCallback((void*)Job7651a0, this);
    a.p->mFlags = 4;
    a.p->SetOwner(this);
    a.p->Queue();
    b.p->SetCallback((void*)Job7651b0, this);
    b.p->mFlags = 1;
    b.p->SetOwner(this);
    b.p->AddDependency(a.p);
    b.p->Queue();
    out->p = b.p;
    b.p = 0;
    return true;
}

// @ 0x00765d30  ResourceManagerHasTexture-style async request (one job)
struct DomNode { cJob* Type(); };                                      // 0x00fc7e50
struct RecInfo { uint32_t f0, f4; };
struct IKeyObj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual RecInfo* Info();                 // slot 4 (+0x10)
    virtual void v5(); virtual void v6();
    virtual void* Aux();                     // slot 7 (+0x1c)
};
struct IMgr8 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual bool Get(RecInfo* a, IRef2** r1, IRef2** r2, int z0, int z1, void* aux, uint32_t v, int z2);   // slot 4, ret 0x20
};
struct AsyncReqC {
    char pad0[0xc];
    uint32_t f0c;               // +0xc
    IKeyObj* obj;               // +0x10
    char pad14[4];
    uint32_t id18;              // +0x18
    char pad1c[0x10];
    ReqState st;                // +0x2c
    bool Start(JobRefL* out);
};
// @ 0x00765d30
bool AsyncReqC::Start(JobRefL* out) {
    if (id18 != 0x2f4e681c)
        return false;
    if (obj->Info()->f4 != 0x2f4e681b)
        return false;
    IRef2** pb = st.Init();
    IKeyObj* o = obj;
    IMgr8* mgr = (IMgr8*)GetManager();
    uint32_t v = f0c;
    if (*pb) { IRef2* t = *pb; *pb = 0; t->Release(); }
    if (st.a) { IRef2* t = st.a; st.a = 0; t->Release(); }
    if (!mgr->Get(o->Info(), &st.a, pb, 0, 0, o->Aux(), v, 0))
        return false;
    JobRefL job;
    IJobMgr* jm = GetJobManager();
    job.Reset();
    if (!jm->CreateJob(&job))
        return false;
    if (st.a) {
        void* x = st.a->Query(0x3a212ac);
        if (x) {
            cJob* jp = job.p;
            jp->AddDependency(((DomNode*)x)->Type());
        }
    }
    job.p->SetCallback((void*)Job7651c0, this);
    job.p->mFlags = 1;
    job.p->SetOwner(this);
    job.p->Queue();
    out->p = job.p;
    job.p = 0;
    return true;
}

// ===========================================================================
// fill a run of 0x7c-byte records at 0x00765230 by copy-construct
struct Rec7c { char raw[0x7c]; Rec7c(const Rec7c& o); void Assign(const Rec7c& o); };   // 0x00422fd0 thiscall, ret 4
// @ 0x00765230
void __cdecl FUN_765230(Rec7c* p, unsigned count, const Rec7c& value) {
    for (unsigned i = count; i > 0; --i) {
        if (p)
            new ((void*)p) Rec7c(value);
        p = (Rec7c*)((char*)p + 0x7c);
    }
}

// ===========================================================================
// async request start at 0x007652c0 (two chained jobs)
void __cdecl FUN_764700(void*);
void __cdecl FUN_764710(void*);
struct AsyncReqA {
    char pad0[0x10];
    IKeyObj* obj;               // +0x10
    void* f14;                  // +0x14
    uint32_t id18;              // +0x18
    char pad1c[0x10];
    uint32_t f2c;               // +0x2c
    char pad30[0x14];
    void* f44;                  // +0x44
    char pad48[0xb4];
    uint32_t state;             // +0xfc
    bool Start(JobRefL* out);
};
// @ 0x007652c0
bool AsyncReqA::Start(JobRefL* out) {
    if (id18 != 0x2f4e681c)
        return false;
    state = 1;
    f44 = 0;
    if (obj->Info()->f4 != 0x2f7d0004)
        return false;
    f2c = 4;
    JobLockL lock(GetJobManager());
    JobRefL a;
    {
        IJobMgr* m = GetJobManager();
        a.Reset();
        if (!m->CreateJob(&a))
            return false;
    }
    JobRefL b;
    {
        IJobMgr* m = GetJobManager();
        b.Reset();
        if (!m->CreateJob(&b))
            return false;
    }
    a.p->SetCallback((void*)FUN_764700, this);
    a.p->mFlags = 4;
    a.p->SetOwner(this);
    a.p->Queue();
    b.p->SetCallback((void*)FUN_764710, this);
    b.p->mFlags = 1;
    b.p->SetOwner(this);
    b.p->AddDependency(a.p);
    b.p->Queue();
    out->p = b.p;
    b.p = 0;
    return true;
}

// ===========================================================================
// cGraphicsResourceFactory ctor at 0x007654f0 (base Factory + locked cJobLock at +8)
namespace EA {
struct AtomicInt { long mValue; long operator++(int) { volatile long* r = &mValue; return _InterlockedExchangeAdd(r, 1); } };
class RefCountTemplate { public:
    RefCountTemplate() { volatile long* r = &mnRefCount.mValue; _InterlockedExchange(r, 0); }
    virtual ~RefCountTemplate() {}
    int AddRef() { return mnRefCount++ + 1; }
    int Release();
    AtomicInt mnRefCount;               // +4
};
template<class T> struct AutoRefCountX {
    T* mpObject;
    AutoRefCountX() : mpObject(0) {}
    AutoRefCountX(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCountX() { if (mpObject) mpObject->Release(); }
};
namespace ResourceMan {
class Factory : public EA::RefCountTemplate { public:};
}
}
struct cJobLock : EA::RefCountTemplate {          // size 0x40
    char pad8[0x38];
    cJobLock();                                   // 0x0068eff0
};
void* operator new(size_t, const char*, int, int, int, int);
void operator delete(void*, const char*, int, int, int, int) throw();
struct GrfCtor : EA::ResourceMan::Factory {
    EA::AutoRefCountX<cJobLock> mPrestreamMemoryBufferLock;   // +8
    GrfCtor();
};
// @ 0x007654f0
GrfCtor::GrfCtor()
    : mPrestreamMemoryBufferLock(new ("Graphics", 0, 0, 0, 0) cJobLock()) {}
