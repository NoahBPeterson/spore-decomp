// slice s00763cb0
// SP::cGraphicsResourceFactory arena/raster loading module.
// flags: /O2 /MD /Gy /EHsc /TP /GS-
#include <intrin.h>
#include "types.h"

// ---------------------------------------------------------------------------
// externs (relocation targets)
// ---------------------------------------------------------------------------
extern "C" {
void* __cdecl AddRegistrationCallback(int id, void* cb);   // 0x06adfe0
void* __cdecl ArenaTypeRegGetType(int t);                   // 0x011e22c0
void* __cdecl GetManager();                                 // 0x067dcd0
int   __cdecl FUN_011f06c0(void* a, void* b);               // 0x011f06c0
}
extern void* g_sAppProperties;                              // 0x015fd918
extern char  kRasterRecordTypes[];                          // 0x0140e000

// 0x764320 thiscall (3 stack args): call kept out of line so Wrap670 keeps its call
struct RasterCtx { char Create(void* a, void* b, void* c); };

// 0x763620 / 0x763770 thiscall (3 stack args)
struct Ctx63620 { char Load(void* a, void* b, void* c); };
struct Ctx63770 { char Fill(void* a, void* b, void* c); };

// ===========================================================================
// @ 0x00763df0
int __cdecl FUN_763df0(void* a, void* b) {
    void* p = g_sAppProperties;
    int c = *(int*)((char*)p + 0x3c);
    if (*(int*)((char*)c + 0x130) != 0) {
        int n = *(int*)((char*)b + 0x134);
        int i = 0;
        if (n > 0) {
            int* arr = (int*)((char*)b + 0x138);
            do {
                if (a == (void*)*arr) {
                    *(int*)((char*)a + 8) = 0;
                    return 1;
                }
                i++;
                arr++;
            } while (i < n);
        }
    }
    return FUN_011f06c0(a, b);
}

// ===========================================================================
// shared interface stubs (vtable slots as used by the loaders below)
struct V3u { uint32_t x, y, z; };

// object kept in cArenaLoadState::mArenaResource (AddRef slot 0, Release slot 1)
struct IfA {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad04;
    V3u v08;                   // +8
    uint32_t pad14;
    void* f18;                 // +0x18
};
struct Z4 { uint32_t a, b, c, d; };
struct BRD {                                            // rw::BaseResourceDescriptor
    uint32_t size, align;
    BRD();      // 0x006c0fa0
    ~BRD();     // 0x00c2e4e0
};
struct BRDs { BRD d[4]; };                              // rw::BaseResourceDescriptors<4>
struct RDesc : BRDs { RDesc() { d[0].size = 0; d[0].align = 1; } };   // rw::ResourceDescriptor
// object kept in cArenaLoadState::mRwAllocator
struct IfB {
    virtual void AddRef();
    virtual void Release();
    virtual void v2();
    virtual void v3();
    virtual void Alloc(const RDesc* rd, int z);   // slot 4
    virtual void Done();                          // slot 5
    virtual void Reset(Z4* z);                    // slot 6
    virtual char** Blocks();                      // slot 7
};
struct Registry { virtual void v0(); virtual void v1(); virtual void v2(); virtual void* Query(uint32_t id); };   // slot 3
struct Stm7 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual uint32_t Size();                       // slot 7
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual uint32_t Read(void* p, uint32_t n);    // slot 12
};

// ===========================================================================
// @ 0x00763e50  value copy of an object state (operator= of a class with Vector3 / __m128 members)
struct V3f { float x, y, z; V3f& operator=(const V3f& o) { x = o.x; y = o.y; z = o.z; return *this; } };
#pragma pack(push, 1)
struct Flags3 { uint8_t b0; uint16_t w1; uint8_t b3;
    Flags3& operator=(const Flags3& o) { b0 = o.b0; w1 = o.w1; b3 = o.b3; return *this; } };
#pragma pack(pop)
struct __declspec(align(16)) ObjState {
    V3f a;                                  // +0
    __declspec(align(16)) __m128 v10;       // +0x10
    V3f b, c;                               // +0x20, +0x2c
    Flags3 fl;                              // +0x38
    V3f d;                                  // +0x3c
    __declspec(align(16)) __m128 v50;       // +0x50
    __m128 v60, v70, v80;
    V3f e;                                  // +0x90
    ObjState& Assign(const ObjState& o);
};
ObjState& ObjState::Assign(const ObjState& o) {
    a = o.a; v10 = o.v10; b = o.b; c = o.c; fl = o.fl; d = o.d;
    v50 = o.v50; v60 = o.v60; v70 = o.v70; v80 = o.v80; e = o.e;
    return *this;
}

// ===========================================================================
// 0x007640c0 and others below are still partial stubs

// ===========================================================================
// @ 0x007642c0 / 0x007643d0  refcounted subobject destructors
template <class T> struct AutoRefT { T* p; ~AutoRefT() { if (p) p->Release(); } };
struct D7642c0 {                    // SP::cGraphicsResourceFactory::cArenaLoadState
    uint32_t size;                 // +0 mRecordSize
    AutoRefT<IfA> a;               // +4 mArenaResource
    AutoRefT<IfB> b;               // +8 mRwAllocator
    D7642c0() { a.p = 0; b.p = 0; }
    __declspec(noinline) ~D7642c0();
};
D7642c0::~D7642c0() {}
struct RefObj { virtual void s0(); virtual void s1(); virtual void s2(); };
struct AutoRef { RefObj* p; ~AutoRef() { if (p) p->s1(); } };
struct D7643d0 {
    AutoRef a;                 // +0
    AutoRef b;                 // +4
    ~D7643d0();
};
D7643d0::~D7643d0() {}

// ===========================================================================
// @ 0x00764220  rw::core::arena::Arena default constructor (dev size 0x98)
struct TR { uint32_t a, b, c, d; TR() { a = 0; b = 0; c = 0; d = 0; } };   // rw::TargetResource
struct Arena98 {
    uint32_t hdr[0x44 / 4];
    RDesc a;                       // +0x44 m_resourceDescriptor
    RDesc b;                       // +0x64 m_resourcesUsed
    TR r;                          // +0x84 m_resource
    uint32_t grp;                  // +0x94 m_arenaGroup
    __declspec(noinline) Arena98();   // 0x00764220
    ~Arena98();                       // 0x007635b0
};
Arena98::Arena98() {}

// ===========================================================================
// @ 0x00764320  create a raster from a load state and hand over the mip data
void* __cdecl SP_CreateRaster(int, int, int, int, int);   // 0x00761420
void __cdecl FreeMem(void* p);                             // 0x00f47380
struct RasterObj { char pad[0x12]; uint8_t face; void SetMipLevelData(void* data, uint32_t level); };   // 0x011f0270
struct RasterLoadState {
    uint32_t pad0[1];
    int w, h, nml, tp, fm;     // +4
    uint8_t isCube; uint8_t pad19[3];
    uint32_t numFaces;         // +0x1c
    uint32_t pad20[0x58 / 4];
    void** pix;                // +0x78
};
struct OutRec { char pad[0x18]; void* raster; };
unsigned char __stdcall FUN_764320(RasterLoadState* s, void* unused, OutRec* out) {
    RasterObj* r = (RasterObj*)SP_CreateRaster(s->w, s->h, s->nml, s->tp, s->fm);
    uint32_t idx = 0;
    for (uint32_t j = 0; j < (uint32_t)s->nml; j++) {
        for (uint32_t i = 0; i < s->numFaces; i++) {
            if (s->isCube) r->face = (uint8_t)i;
            r->SetMipLevelData(s->pix[idx], j);
            FreeMem(s->pix[idx]);
            s->pix[idx] = 0;
            idx++;
        }
    }
    if (s->isCube) r->face = 0;
    out->raster = r;
    return 1;
}

// ===========================================================================
// @ 0x00764430  serialize the record array of a model (0x7c-byte records)
struct T3 { uint32_t x, y, z; T3(uint32_t a, uint32_t b, uint32_t c) : x(a), y(b), z(c) {} };
struct WStream {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13();
    virtual uint32_t Write(const void* p, uint32_t n);   // slot 14 (+0x38)
};
struct Cell { void* GetChildID(uint32_t* count); };   // 0x00700360 thiscall (ret 4)
struct P74 { char pad[8]; T3 v; };
struct Rec7c { char a[0x38]; char b[0x38]; uint32_t f70; P74* p74; Cell* p78; };
struct RecSrc { char pad[0x108]; char* begin; char* end; };
unsigned char __stdcall FUN_764430(WStream* s, RecSrc* o) {
    uint32_t count = (int)(o->end - o->begin) / 0x7c;
    s->Write(&count, 4);
    uint32_t off = 0;
    for (uint32_t i = 0; i < count; i++) {
        Rec7c* r = (Rec7c*)(o->begin + off);
        s->Write(r, 0x38);
        s->Write(r->b, 0x38);
        s->Write(&r->f70, 4);
        P74* q = r->p74;
        if (q) {
            T3 t = q->v;
            s->Write(&t, 0xc);
        } else {
            T3 u(0xffffffff, 0xffffffff, 0xffffffff);
            s->Write(&u, 0xc);
        }
        uint32_t flag = r->p78 != 0;
        s->Write(&flag, 4);
        if (r->p78) {
            uint32_t n;
            void* d = r->p78->GetChildID(&n);
            s->Write(&n, 4);
            s->Write(d, n * 0xa0);
        }
        off += 0x7c;
    }
    return 1;
}

// ===========================================================================
// 0x00764760  constructor with two (u16,u16,Vector3,float,Matrix3) blocks
struct Matrix3 { float m[9]; Matrix3& Assign(const Matrix3& o); };   // 0x0041cb40 thiscall
struct V3g { float x, y, z; };
extern V3g g_v3_01630408;       // 0x01630408
extern float g_one_01485720;    // 0x01485720
extern Matrix3 g_mat_01630560;  // 0x01630560
struct Blk {
    uint16_t a, b;       // +0
    V3g pos;             // +4
    float w;             // +0x10
    Matrix3 m;           // +0x14
};
struct Ctor764760 {
    Blk blk0;            // +0
    Blk blk1;            // +0x38
    uint32_t p70, p74, p78;
    Ctor764760* Init(uint32_t v);
};
static void InitBlk(Blk* b) {
    b->a = 0; b->b = 0;
    b->pos.x = g_v3_01630408.x; b->pos.y = g_v3_01630408.y; b->pos.z = g_v3_01630408.z;
    b->w = g_one_01485720;
    b->m.Assign(g_mat_01630560);
}
// @ 0x00764760
Ctor764760* Ctor764760::Init(uint32_t v) {
    InitBlk(&blk0);
    InitBlk(&blk1);
    p74 = p78 = 0;
    p70 = v;
    return this;
}

// ===========================================================================
// @ 0x00764670 / 0x007646a0 / 0x007646c0 / 0x00764820 / 0x007649f0
struct Slot9 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
               virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); };
struct cSPMemPool { void* LockedAlloc(uint32_t size, int a, int b, int c, int d, int e); };   // 0x009289f0 (ret 0x18)
extern cSPMemPool* g_pSPMemPool;                                                              // 0x016c8b44
void* __cdecl ZoneObject_new(int size, const char* name, int a, int b, int c, int d);         // 0x00926020
void* __cdecl TaggedNew(uint32_t size, const char* name, int a, int b, int c, int d);         // 0x00f473a0
struct Rc { virtual void Del(int); long rc; };
struct SharedBuf {                       // EA::IO::SharedPointer-like buffer holder, 0x18 bytes
    void* vptr0; Rc rcb; void* pad0c; void* data; int pad14;
    SharedBuf(void* a, void* b, uint8_t c);   // 0x0093bc40
    static void* operator new(size_t n, const char* name, int a, int b, int c, int d) { return ZoneObject_new((int)n, name, a, b, c, d); }
    static void operator delete(void*, const char*, int, int, int, int) {}
    static void operator delete(void*) {}
};
struct SBHandle {
    SharedBuf* p;
    SBHandle(SharedBuf* q) : p(q) { if (p) _InterlockedIncrement(&p->rcb.rc); }
    ~SBHandle() {
        Rc* r = &p->rcb;
        long n = _InterlockedDecrement(&r->rc);
        if (n == 0) {
            _InterlockedExchange(&r->rc, 1);
            if (r) r->Del(1);
        }
    }
};
struct Stm {                                  // memory stream held at Loader::p28
    virtual void v0(); virtual void AddRef(); virtual void Release(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual int GetSize();                    // slot 11
    virtual int Read(void* p, uint32_t n);    // slot 12
};
struct AsyncReq : Stm {                       // Graphics::GraphicsFactoryAsyncRequest, 0x24 bytes
    char pad[0x24 - 4];
    AsyncReq(SharedBuf* sp, uint32_t size, const char* name);   // 0x0093c270
    static void* operator new(size_t n, const char* name, int a, int b, int c, int d) { return TaggedNew((uint32_t)n, name, a, b, c, d); }
    static void operator delete(void*, const char*, int, int, int, int) {}
    static void operator delete(void*) {}
};
struct AsyncMgr { void RequestComplete(void* req, void* arg); };   // 0x006ae880 thiscall (ret 8)
AsyncMgr* __cdecl GetAsyncMgr();                                    // 0x0067de70
bool __cdecl FUN_6ae2f0(char* a, void* b);                          // 0x006ae2f0 cdecl
static __forceinline void* PoolAlloc(uint32_t n) { return g_pSPMemPool->LockedAlloc(n, 0, 0, 0, 0, 0); }
struct Loader {
    char pad0[0xc];
    void* pC;                  // +0xc
    Slot9* p10;                // +0x10
    void* p14;                 // +0x14
    char pad18[4];
    char r1c[0xc];             // +0x1c
    Stm* p28;                  // +0x28
    char p2c[0x308];           // +0x2c
    unsigned char b334;        // +0x334
    void Wrap670(int);
    void Wrap6a0(int);
    void Wrap6c0(int);
    bool Load820(int);         // 0x764820
    bool Complete(char* a);    // 0x7649f0
};
void Loader::Wrap670(int) {
    RasterCtx* ctx = (RasterCtx*)pC;
    char ok = ctx->Create(p2c, p28, p14);
    if (ok)
        b334 = 1;
}
// @ 0x007646a0
void Loader::Wrap6a0(int) {
    ((Ctx63620*)pC)->Load(p2c, p28, p14);
}
void Loader::Wrap6c0(int) {
    if (((Ctx63770*)pC)->Fill(p2c, p28, p14))
        b334 = 1;
}

// @ 0x00764820
bool Loader::Load820(int) {
    uint32_t size = p28->GetSize();
    if (size == (uint32_t)-1) return false;
    SharedBuf* sb = new ("Graphics", 0, 0, 0, 0) SharedBuf(PoolAlloc(size), (void*)1, 0);
    SBHandle h(sb);
    char* dst = (char*)sb->data;
    uint32_t left = size;
    while (left > 0) {
        int n = p28->Read(dst, left);
        if (n == -1) break;
        left -= n;
        dst += n;
    }
    if (left != 0) return false;
    AsyncReq* req = new ("Graphics/GraphicsFactoryAsyncRequest", 0, 0, 0, 0) AsyncReq(sb, size, "UTF/MemoryStream");
    Stm* old = p28;
    if (req != old) {
        if (req) req->AddRef();
        p28 = req;
        if (old) old->Release();
    }
    return true;
}

// @ 0x007649f0
bool Loader::Complete(char* a) {
    p10->v9();
    if (!b334) {
        GetAsyncMgr()->RequestComplete(r1c, 0);
        return false;
    }
    GetAsyncMgr()->RequestComplete(r1c, p14);
    void* q = p14;
    return FUN_6ae2f0(a, q);
}

// ===========================================================================
// SP::cGraphicsResourceFactory arena loading
struct ArenaOwner { void* arena; };
struct ArenaIter { char pad[0x134]; uint32_t f134; char pad2[0x40];
    void Init(); void Done();                                   // 0x011e2fe0 / 0x011e2690
    ArenaIter() { Init(); f134 = 0; } ~ArenaIter() { Done(); } };
int __cdecl ArenaStart(void* arena, ArenaIter* it, void* owner, int* flag);   // 0x011e3c70
unsigned int __cdecl FixupNext(ArenaIter*);     // 0x011e39e0 rw::core::arena::Arena::FixupNext
unsigned int __cdecl DestructNext(ArenaIter*);  // 0x011e2330 rw::core::arena::Arena::DestructNext
bool __cdecl FUN_763fd0(void* arena);           // 0x00763fd0

namespace SP {
class cGraphicsResourceFactory {
public:
    bool Init();                                            // 007641c0
    bool FixupArena(ArenaOwner* p);                         // 00764580
    bool ReadResourceArena(D7642c0* st, Stm7* s, Registry* reg);   // 00764a50
    bool BuildArena(Stm7* s, Registry* reg, const V3u* pv); // 00764ce0
};
}

// @ 0x00764580
bool SP::cGraphicsResourceFactory::FixupArena(ArenaOwner* p) {
    ArenaIter it;
    void* a = p->arena;
    int flag = 1;
    if (ArenaStart(a, &it, p, &flag)) {
        while (FixupNext(&it)) {}
        if (flag) return true;
        while (DestructNext(&it)) {}
    }
    return false;
}

// @ 0x00764a50
bool SP::cGraphicsResourceFactory::ReadResourceArena(D7642c0* st, Stm7* s, Registry* reg) {
    st->size = s->Size();
    {
        IfA* nw = reg ? (IfA*)reg->Query(0x2f4e681b) : 0;
        IfA* old = st->a.p;
        if (nw != old) { if (nw) nw->AddRef(); st->a.p = nw; if (old) old->Release(); }
    }
    {
        IfB* nw = reg ? (IfB*)reg->Query(0x034c84e9) : 0;
        IfB* old = st->b.p;
        if (nw != old) { if (nw) nw->AddRef(); st->b.p = nw; if (old) old->Release(); }
    }
    if (st->a.p && st->b.p) {
        if (st->a.p->f18) {
            Z4 z; z.b = 0; z.c = 0; z.d = 0; z.a = 0;
            st->b.p->Reset(&z);
            IfA* q = st->a.p;
            q->f18 = 0;
        }
        Arena98 holder;
        if (st->size < 0x98) return false;
        if (s->Read(&holder, 0x98) != 0x98) return false;
        st->size -= 0x98;
        RDesc rd = holder.a;
        if (holder.a.d[0].size < 0x98) return false;
        st->b.p->Alloc(&rd, 0);
        char** blocks = st->b.p->Blocks();
        *(Arena98*)blocks[0] = holder;
        for (uint32_t i = 0; i < 4; i++) {
            uint32_t n = rd.d[i].size;
            char* p = blocks[i];
            if (i == 0) { n -= 0x98; p += 0x98; }
            if (st->size < n) return false;
            if (n > 0) {
                if (s->Read(p, n) != n) return false;
                st->size -= n;
            }
        }
        if (st->size != 0) return false;
        return true;
    }
    return false;
}

// @ 0x00764ce0
bool SP::cGraphicsResourceFactory::BuildArena(Stm7* s, Registry* reg, const V3u* pv) {
    D7642c0 st;
    if (!ReadResourceArena(&st, s, reg)) return false;
    char** blocks = st.b.p->Blocks();
    char* first = blocks[0];
    if (FixupArena((ArenaOwner*)blocks)) {
        if (FUN_763fd0(first)) st.b.p->Done();
        st.a.p->f18 = first;
        st.a.p->v08 = *pv;
        return true;
    }
    return false;
}

// ===========================================================================
// @ 0x007641c0
bool SP::cGraphicsResourceFactory::Init() {
    AddRegistrationCallback(0x2f4e681b, (void*)0x7632f0);
    void* t = ArenaTypeRegGetType(0x20003);
    *(void**)((char*)t + 0xc) = (void*)0x763df0;
    t = ArenaTypeRegGetType(0x2000b);
    *(void**)((char*)t + 0xc) = (void*)0x763cb0;
    void* m = GetManager();
    ((void(__thiscall*)(void*, int, void*, int))(*(void***)m)[0x24 / 4])(m, 0x2f4e681c, kRasterRecordTypes, 3);
    return true;
}

// ===========================================================================
// @ 0x00763cb0  D3D9 texture-stage raster registration + per-stage state refresh
// Lazily builds two shared raster objects from the property list, then refreshes
// every texture stage (0..3) whose hard-state dirty bit is set.
// ===========================================================================
struct EmbeddedState {
    char     pad0[0x10];
    uint32_t dirtyBits;                              // +0x10
    unsigned int GetTextureStageState(int stage);    // 0x011ee870
    void         SetRaster(int stage, void* raster); // 0x011ee6b0
};
struct RasterThing {
    void FUN_00763c60(unsigned state);               // 0x00763c60
};
struct Managed { void* value; uint8_t flags; };      // +0 flags bit0
void* __cdecl GetRasterMgr();                        // 0x0067dd60
uint32_t __cdecl FUN_011ed690(void* hard, void* raster);   // 0x011ed690
extern void*    g_texStageRaster0;                   // 0x016303f8
extern void*    g_texStageRaster1;                   // 0x016303fc
extern uint32_t g_texStageCreate[3];                 // 0x016304d4 / d8 / dc
extern uint32_t g_texStageRasterType[3];             // 0x016304c8 / cc / d0

// @ 0x00763cb0
uint32_t __cdecl FUN_763cb0(EmbeddedState* hard, RasterThing* raster) {
    if (g_texStageRaster0 == 0) {
        typedef void* (__thiscall *FnCreate)(void*, V3u, int);
        typedef void  (__thiscall *FnRelease)(void*, void*);
        void* mgr = GetRasterMgr();
        Managed* m = (Managed*)((FnCreate)((*(void***)mgr)[0x1c / 4]))(mgr, *(const V3u*)g_texStageCreate, 0);
        if ((m->flags & 1) == 0) {
            void* mgr2 = GetRasterMgr();
            ((FnRelease)((*(void***)mgr2)[0x34 / 4]))(mgr2, m);
        }
        g_texStageRaster0 = m->value;

        mgr = GetRasterMgr();
        Managed* m2 = (Managed*)((FnCreate)((*(void***)mgr)[0x1c / 4]))(mgr, *(const V3u*)g_texStageRasterType, 0);
        if ((m2->flags & 1) == 0) {
            void* mgr2 = GetRasterMgr();
            ((FnRelease)((*(void***)mgr2)[0x34 / 4]))(mgr2, m2);
        }
        g_texStageRaster1 = m2->value;
    }

    uint32_t result = FUN_011ed690(hard, raster);

    void* props = g_sAppProperties;
    if (*(uint32_t*)((char*)(*(uint32_t*)((char*)props + 0x3c)) + 0x130) != 0) {
        uint32_t bit = 1;
        for (int stage = 0; stage < 4; ++stage, bit = _rotl(bit, 1)) {
            if ((hard->dirtyBits & bit) == 0)
                return result;
            if (stage > 0) {
                raster->FUN_00763c60(hard->GetTextureStageState(stage));
                void* r;
                if (stage == 1)
                    r = g_texStageRaster0;
                else if (stage == 2)
                    r = g_texStageRaster1;
                else
                    r = 0;
                hard->SetRaster(stage, r);
            }
        }
    }
    return result;
}

// ===========================================================================
// @ 0x00763fd0  clear the disposable references of every object exported by an arena
// ===========================================================================
struct __declspec(align(8)) RDesc8 {
    uint32_t size; uint32_t align;
    RDesc8();      // 0x006c0fa0
    ~RDesc8();     // 0x00c2e4e0
};
struct ExportRec { uint32_t type; void* obj; };
struct Arena {
    int  GetNumExportedObjects();                              // 0x011e23a0
    void GetExportedObjectByIndex(uint32_t i, ExportRec* out); // 0x011e28e0
};

// @ 0x00763fd0
bool __cdecl FUN_763fd0(void* arena) {
    Arena* a = (Arena*)arena;
    int n = a->GetNumExportedObjects();
    for (unsigned i = 0; (int)i < n; ++i) {
        RDesc8 desc[4];
        ExportRec rec;
        desc[0].size = 0;
        desc[0].align = 1;
        a->GetExportedObjectByIndex(i, &rec);
        switch (rec.type) {
        case 0x20005:
            *(uint32_t*)((char*)rec.obj + 0x18) = 0;
            break;
        case 0x20007:
            *(uint32_t*)((char*)rec.obj + 0x18) = 0;
            break;
        }
    }
    return true;
}

// ===========================================================================
// @ 0x007640c0  multiple-inheritance ctor: two vtables, atomic refcount at +8
// ===========================================================================
// @ 0x007640c0
void* __fastcall FUN_7640c0(void* self) {
    uint32_t* p = (uint32_t*)self;
    p[0] = 0x013f1ab0;                 // first vtable (primary base)
    p[1] = 0x013ef094;                 // second vtable (secondary base)
    _InterlockedExchange((volatile long*)(p + 2), 0);   // atomic refcount init at +8
    p[0] = 0x0140e044;                 // final first vtable
    p[1] = 0x0140e040;                 // final second vtable
    p[3] = 0;                          // +0x0c
    p[4] = 0;                          // +0x10
    *((uint8_t*)p + 0x18) = 1;         // +0x18
    return self;
}
