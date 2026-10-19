// Slice s007b29a0 — texture/thumbnail RTT and property-driven helpers. Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <intrin.h>

template <int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
struct PropHandle {
    char pad[0x10];
    unsigned char flags;                            // +0x10
    unsigned short type;                            // +0x12
    int* GetInt();                                  // 0x0041E990 __thiscall
};
struct PropList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8();
    virtual bool v9(int hash, PropHandle** out);    // +0x24
    virtual PropHandle* v10(int hash);              // +0x28
    int GetIntProperty(unsigned hash);              // 0x006A2660
};
extern PropList* g_sAppProperties;                  // 0x015FD918

// ---------------------------------------------------------------------------
// @ 0x007b3a30  (store a 4-float row at base+0x3c with stride 0x10)
// ---------------------------------------------------------------------------
struct W3a30 {
    char pad[0x3c];
    void set(int idx, float* v);
};
void W3a30::set(int idx, float* v)
{
    char* b = (char*)this;
    float* p = (float*)(b + 0x3c);
    int o = idx*4;
    p[o + 0] = v[0];
    *(float*)(b + (idx + 4) * 0x10) = v[1];
    p[o + 2] = v[2];
    p[o + 3] = v[3];
}

// ---------------------------------------------------------------------------
// @ 0x007b39d0  (lazy init reading a property)
// ---------------------------------------------------------------------------
struct W39d0 {
    char pad[0x70];
    int m70;                                        // +0x70
    int m74;                                        // +0x74
    unsigned char m78;                              // +0x78
    void f();
};
void W39d0::f()
{
    if (m78)
        return;
    m78 = 1;
    m74 = 0x10;
    PropList* p = g_sAppProperties;
    if (p) {
        PropHandle* h;
        if (p->v9(0x67c8be6, &h) && h->type == 9)
            m74 = *h->GetInt();
    }
    m70 = 0;
}

// ---------------------------------------------------------------------------
// remaining entry points (best-effort / skeleton reconstruction)
// ---------------------------------------------------------------------------
struct RttRect { int mPageID; int mAllocID; };
struct IRttManager {
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3(); virtual void r4();
    virtual void ReleaseRect(RttRect id);           // +0x14
};
struct TimelineViewer {
    void Shutdown();                                // 0x007C3BA0
    ~TimelineViewer();                              // 0x007C4000
};
struct TimelineJob {
    char pad0[0x34];
    TimelineViewer* mViewer;                        // +0x34
    char pad1[8];
    bool mActive;                                   // +0x40
};
struct ThumbnailMgr29a0 {
    char pad0[0x4c];
    RttRect mTimelineRect[3];                       // +0x4c
    char pad1[0x10b4 - 0x64];
    IRttManager* mRTTMgr;                           // +0x10b4
    char pad2[0x2100 - 0x10b8];
    TimelineJob* mTimelineJobs[3];                  // +0x2100
    void ReleaseTimelineJobs();
};

// @ 0x007b29a0
void ThumbnailMgr29a0::ReleaseTimelineJobs()
{
    for (int i = 0; i < 3; i++) {
        mRTTMgr->ReleaseRect(mTimelineRect[i]);
        TimelineJob* job = mTimelineJobs[i];
        if (job->mActive) {
            if (job->mViewer) {
                job->mViewer->Shutdown();
                delete job->mViewer;
                job->mViewer = 0;
            }
            job->mActive = false;
        }
    }
}
// ---------------------------------------------------------------------------
// (types) submit the current timeline job's raster to the GPU.
// ---------------------------------------------------------------------------
// cViewer (0x174 bytes) — RTT/capture render-target helper.
struct cViewer {
    char pad0[0x174];
    cViewer();                                          // 0x007C3F70
    bool Init(bool windowed);                           // 0x007C4DD0
    bool Copy(cViewer* src, bool a, bool b);            // 0x007C50B0
    void SetRaster(int* handle, bool setViewport);      // 0x007C4BE0
    void SetClearColor(const void* c);                  // 0x007C3C20
    void Clear(unsigned flags);                         // 0x007C3C50
    void SetViewportRectArgs(unsigned short x, unsigned short y,
                             unsigned short w, unsigned short h);   // 0x007C5310
    void Shutdown();                                    // 0x007C3BA0
    ~cViewer();                                         // 0x007C4000
};

// EA "Graphics" allocator (6-arg placement new) and its matching placement delete
// (required so a throwing cViewer ctor emits the new-expression cleanup EH frame).
void* operator new(unsigned int, const char*, int, int, int, int);   // 0x00F473A0
void operator delete(void*);                                         // 0x00F47380
void operator delete(void*, const char*, int, int, int, int);

// app/manager singleton returned by FUN_0067dd40 (slots 49/57/58 used here).
struct AppMgr {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08(); virtual void a09(); virtual void a10(); virtual void a11();
    virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
    virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
    virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23();
    virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27();
    virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31();
    virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35();
    virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39();
    virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43();
    virtual void a44(); virtual void a45(); virtual void a46(); virtual void a47();
    virtual void a48();
    virtual void GetHandle49(void* out);                // +0x00c4
    virtual void a50(); virtual void a51(); virtual void a52(); virtual void a53();
    virtual void a54(); virtual void a55(); virtual void a56();
    virtual void GetHandle57(void* out);                // +0x00e4
    virtual void GetHandle58(void* out);                // +0x00e8
};
extern "C" AppMgr* FUN_0067dd40();                      // 0x0067DD40

struct JobObj2e10 { int mHandle; unsigned char mFlags; };
struct TargetObj { void* tex; unsigned flags; };
struct Tex { int Lock(int mode, int zero, void* out);   // 0x011EF750
             void Unlock(void* p); };                   // 0x011EF880
struct LockInfo { void* data; int a, b, c, d, e, f; };

// factory (0x0067DD60): Register(+0x34) / Create(+0x3c)
struct IFactory2e10 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void v13(void* p);                      // +0x34
    virtual void v14();
    virtual TargetObj* Create(int, int, int, int, int, int, int, int);  // +0x3c
};
extern "C" IFactory2e10* FUN_0067dd60();            // 0x0067DD60

// size/upload source (0x0067DDB0): +0x18 (void*) / +0x54 sized upload
struct IRenderKey2e10 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void v6(void* p);                       // +0x18
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20();
    virtual void v21(cViewer*, int*, int*, int, float);  // +0x54
};
extern "C" IRenderKey2e10* FUN_0067ddb0();          // 0x0067DDB0

// blitter (0x0067DDA0): +0x18 info() / +0x24 measure() / +0x30 blit()
struct IRenderDev2e10 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void* Info(int a, int b);               // +0x18
    virtual void v7(); virtual void v8();
    virtual void Measure(int a, int b, int* o0, int* o1, int* o2, int* o3);  // +0x24
    virtual void v10(); virtual void v11();
    virtual void v12(int, int, int);                // +0x30
};
extern "C" IRenderDev2e10* FUN_0067dda0();          // 0x0067DDA0

// size-dimension source (0x0067DD50): slot 7 (+0x1c) returns int[2].
struct IDimSrc {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
    virtual void d4(); virtual void d5(); virtual void d6();
    virtual int* GetDim();                          // +0x1c
};
extern "C" IDimSrc* FUN_0067dd50();                 // 0x0067DD50
extern "C" void* FUN_006bb610();                    // 0x006BB610

struct GpuHandle2e10 {
    int Lock(int a, int b, void* out);              // 0x011EF750
    void Unlock(void* p);                           // 0x011EF880
};
struct ThumbnailMgr2e10 {
    char pad0[0x30];
    char* m30;                                      // +0x30
    void Submit();
};

// @ 0x007b2e10
void ThumbnailMgr2e10::Submit()
{
    JobObj2e10* job = *(JobObj2e10**)(m30 + 0x1c);
    if (!(job->mFlags & 1))
        FUN_0067dd60()->v13(job);
    GpuHandle2e10* h = (GpuHandle2e10*)job->mHandle;
    int local[9];
    if (h->Lock(2, 0, &local[2])) {
        local[0] = -1;
        local[1] = -1;
        FUN_0067ddb0()->v6(&local[0]);
        FUN_0067dda0()->v12(local[0], local[1], local[2]);
        h->Unlock(&local[2]);
    }
}
// ===========================================================================
// refcounted job-argument types + AutoRef assign helpers
// ===========================================================================
struct cThumbRef { virtual int AddRef(); virtual int Release(); };              // slots 0/1
struct cThumbTgt {
    virtual void t0(); virtual int AddRef(); virtual int Release();             // slots 1/2
    char pad[0x24]; bool m28;
};

static __forceinline void AssignA(cThumbRef*& slot, cThumbRef* p)
{
    cThumbRef* old = slot;
    if (p != old) {
        if (p) p->AddRef();
        slot = p;
        if (old) old->Release();
    }
}
static __forceinline void AssignT(cThumbTgt*& slot, cThumbTgt* p)
{
    cThumbTgt* old = slot;
    if (p != old) {
        if (p) p->AddRef();
        slot = p;
        if (old) old->Release();
    }
}

// ---------------------------------------------------------------------------
// cThumbJobA: job-run types
// ---------------------------------------------------------------------------
struct cThumbJobA {
    char pad0[0xc];
    bool m0c;                       // +0x0c
    cThumbRef* m10;                 // +0x10
    cViewer* m14;                   // +0x14
    int m18, m1c;                   // +0x18, +0x1c
    int m20, m24, m28;              // +0x20, +0x24, +0x28
    void* m2c;                      // +0x2c
    cThumbTgt* m30;                 // +0x30
    void Run(cThumbRef* ctx, cViewer* world, cThumbTgt* tgt);
};

// @ 0x007b2ab0
void cThumbJobA::Run(cThumbRef* ctx, cViewer* world, cThumbTgt* tgt)
{
    if (m0c)
        return;
    m14 = new ("Graphics", 0, 0, 0, 0) cViewer;
    m14->Init(false);
    m14->Copy(world, false, false);
    AssignA(m10, ctx);
    if (tgt->m28) {
        FUN_0067dd40()->GetHandle58(&m18);
        int* h = &m18;
        int o0, o1;
        FUN_0067dda0()->Measure(h[0], h[1], &o0, &o1, &m24, &m28);
        unsigned char* info = (unsigned char*)FUN_0067dda0()->Info(h[0], h[1]);
        int size = (info[0x10] >> 3) * m24 * m28;
        m20 = size;
        m2c = operator new(size, "Graphics", 0, 0, 0, 0);
    }
    AssignT(m30, tgt);
    m0c = true;
}

// ---------------------------------------------------------------------------
// cThumbJobB: job-run types
// ---------------------------------------------------------------------------
struct cThumbJobB {
    char pad0[0xc];
    bool m0c;                       // +0x0c
    cThumbRef* m10;                 // +0x10
    cViewer* m14;                   // +0x14
    int m18, m1c;                   // +0x18, +0x1c
    int m20, m24, m28;              // +0x20, +0x24, +0x28
    void* m2c;                      // +0x2c
    cThumbTgt* m30;                 // +0x30
    void Run(cThumbRef* ctx, cViewer* world, cThumbTgt* tgt);
};

// @ 0x007b2ca0
void cThumbJobB::Run(cThumbRef* ctx, cViewer* world, cThumbTgt* tgt)
{
    if (m0c)
        return;
    AssignA(m10, ctx);
    m14 = new ("Graphics", 0, 0, 0, 0) cViewer;
    m14->Init(false);
    m14->Copy(world, false, false);
    FUN_0067dd40()->GetHandle58(&m18);
    int* h = &m18;
    int o0, o1;
    FUN_0067dda0()->Measure(h[0], h[1], &o0, &o1, &m24, &m28);
    unsigned char* info = (unsigned char*)FUN_0067dda0()->Info(h[0], h[1]);
    int size = (info[0x10] >> 3) * m24 * m28;
    m20 = size;
    m2c = operator new(size, "Graphics", 0, 0, 0, 0);
    m0c = true;
    AssignT(m30, tgt);
}

// ---------------------------------------------------------------------------
// cThumbResA/cThumbResB: resource-holder destructors
// ---------------------------------------------------------------------------
struct ResBaseA { virtual ~ResBaseA() {} };
struct ResBaseB { virtual ~ResBaseB() {} int mnRefCount; };
template <class T> struct AutoRefC { T* p; ~AutoRefC() { if (p) p->Release(); } };

struct cThumbResA : ResBaseA, ResBaseB {
    int m0c;                        // +0x0c
    AutoRefC<cThumbRef> m10;        // +0x10
    AutoRefC<cThumbRef> m14;        // +0x14
    int pad18, pad1c;
    AutoRefC<cThumbTgt> m20;        // +0x20
    virtual ~cThumbResA();
};

// @ 0x007b2eb0
cThumbResA::~cThumbResA() {}

struct cThumbResB : ResBaseA, ResBaseB {
    int m0c;                        // +0x0c
    AutoRefC<cThumbRef> m10;        // +0x10
    virtual ~cThumbResB();
};

// @ 0x007b32e0
cThumbResB::~cThumbResB() {}

// ---------------------------------------------------------------------------
// cThumbJobC: job-run types
// ---------------------------------------------------------------------------
struct cThumbJobC {
    char pad0[0xc];
    bool m0c;                       // +0x0c
    cThumbRef* m10;                 // +0x10
    cThumbRef* m14;                 // +0x14
    cViewer* m18;                   // +0x18
    cViewer* m1c;                   // +0x1c
    cThumbTgt* m20;                 // +0x20
    void Run(cThumbRef* a, cThumbRef* b, cThumbTgt* c);
};

// @ 0x007b2f40
void cThumbJobC::Run(cThumbRef* a, cThumbRef* b, cThumbTgt* c)
{
    if (m0c)
        return;
    m18 = new ("Graphics", 0, 0, 0, 0) cViewer;
    m18->Init(false);
    AssignA(m10, a);
    AssignA(m14, b);
    m0c = true;
    AssignT(m20, c);
    m1c = new ("Graphics", 0, 0, 0, 0) cViewer;
    m1c->Init(false);
}

// ---------------------------------------------------------------------------
// cThumbJobD: job-run types
// ---------------------------------------------------------------------------
struct cThumbJobD {
    char pad0[0xc];
    bool m0c;                       // +0x0c
    cThumbRef* m10;                 // +0x10
    cViewer* m14;                   // +0x14
    cThumbTgt* m18;                 // +0x18
    void Run(cThumbRef* a, cThumbTgt* b);
};

// @ 0x007b31f0
void cThumbJobD::Run(cThumbRef* a, cThumbTgt* b)
{
    if (m0c)
        return;
    m14 = new ("Graphics", 0, 0, 0, 0) cViewer;
    m14->Init(false);
    AssignA(m10, a);
    m0c = true;
    AssignT(m18, b);
}

// ---------------------------------------------------------------------------
// (types) build the RTT target for one job and upload it.
// ---------------------------------------------------------------------------
struct RtParams {
    char pad0[0x10];
    int m10, m14;                   // +0x10, +0x14
    char pad18[0xc];
    int m24;                        // +0x24
    char pad28[0xc];
    int m34, m38;                   // +0x34, +0x38
};
struct RtJob30 {
    char pad0[0x10];
    int m10, m14;                   // +0x10, +0x14
    int pad18, pad1c;
    RtParams* m20;                  // +0x20
    void Build();
};

// @ 0x007b3090
void RtJob30::Build()
{
    int* dim = FUN_0067dd50()->GetDim();
    float f = (float)dim[1] / (float)dim[0] * (float)(unsigned)m20->m24;
    int h = (int)f;
    TargetObj* obj = FUN_0067dd60()->Create(
        m20->m38, m20->m34, m20->m24, h, 1, 8, 0x15, 8);
    if (!(obj->flags & 1))
        FUN_0067dd60()->v13(obj);
    LockInfo info;
    Tex* t = (Tex*)obj->tex;
    if (t->Lock(2, 0, &info)) {
        FUN_0067dda0()->v12(m20->m10, m20->m14, (int)info.data);
        if (!(obj->flags & 1))
            FUN_0067dd60()->v13(obj);
        t->Unlock(&info);
    }
}

// ---------------------------------------------------------------------------
// (types) property-driven RTT capture.
// ---------------------------------------------------------------------------
struct IObj3 {
    virtual void q0(); virtual void q1(); virtual void q2();
    virtual void v3(int, int, void*, int);                      // +0x0c
};
struct IObj79 {
    virtual void z00(); virtual void z01(); virtual void z02(); virtual void z03();
    virtual void z04(); virtual void z05(); virtual void z06(); virtual void z07();
    virtual void z08(); virtual void z09(); virtual void z10(); virtual void z11();
    virtual void z12(); virtual void z13(); virtual void z14(); virtual void z15();
    virtual void z16(); virtual void z17(); virtual void z18(); virtual void z19();
    virtual void z20(); virtual void z21(); virtual void z22(); virtual void z23();
    virtual void z24(); virtual void z25(); virtual void z26(); virtual void z27();
    virtual void z28(); virtual void z29(); virtual void z30(); virtual void z31();
    virtual void z32(); virtual void z33(); virtual void z34(); virtual void z35();
    virtual void z36(); virtual void z37(); virtual void z38(); virtual void z39();
    virtual void z40(); virtual void z41(); virtual void z42(); virtual void z43();
    virtual void z44(); virtual void z45(); virtual void z46(); virtual void z47();
    virtual void z48(); virtual void z49(); virtual void z50(); virtual void z51();
    virtual void z52(); virtual void z53(); virtual void z54(); virtual void z55();
    virtual void z56(); virtual void z57(); virtual void z58(); virtual void z59();
    virtual void z60(); virtual void z61(); virtual void z62(); virtual void z63();
    virtual void z64(); virtual void z65(); virtual void z66(); virtual void z67();
    virtual void z68(); virtual void z69(); virtual void z70(); virtual void z71();
    virtual void z72(); virtual void z73(); virtual void z74(); virtual void z75();
    virtual void z76(); virtual void z77(); virtual void z78();
    virtual IObj3* v79();                                       // +0x13c
};
struct RtDesc { int f0, f4, f8, fc; };
struct Ctx { cViewer* v; int a, b, c; };
struct RtJob40 {
    char pad0[0x10];
    IObj79* m10;                    // +0x10
    cViewer* m14;                   // +0x14
    int m18;                        // +0x18
    void Doit(int a0, int a1, RtDesc* d, int a3);
};

// @ 0x007b3340
void RtJob40::Doit(int a0, int a1, RtDesc* d, int a3)
{
    int v0, v1, v2, v3;
    int prop1 = g_sAppProperties->GetIntProperty(0x5893ee8);
    int prop2 = g_sAppProperties->GetIntProperty(0x5893ed4);
    PropHandle* h = g_sAppProperties->v10(0x5d2c54b);
    float* color;
    if (h->type == 0x34 || h->type == 0x10) {
        if (h->flags & 0x30)
            color = (float*)*(void**)h;
        else
            color = (float*)(h->type ? (void*)h : 0);
    } else {
        color = (float*)FUN_006bb610();
    }
    float col[4];
    col[0] = color[0];
    col[1] = color[1];
    col[2] = color[2];
    col[3] = color[3];
    int handle1[2] = {-1, -1};
    FUN_0067dd40()->GetHandle57(handle1);
    m14->SetRaster(handle1, true);
    m14->SetClearColor(col);
    m14->Clear(7);
    Ctx ctx;
    ctx.v = m14;
    ctx.a = d->f4;
    ctx.b = d->f8;
    ctx.c = d->fc;
    m10->v79()->v3(a0, a1, &ctx, a3);
    int h2[2] = {-1, -1};
    FUN_0067dd40()->GetHandle49(h2);
    m14->SetRaster(h2, true);
    FUN_0067dda0()->Measure(h2[0], h2[1], &v0, &v1, &v2, &v3);
    unsigned q = (unsigned)m18 / (unsigned)prop1;
    unsigned rem = (unsigned)m18 % (unsigned)prop1;
    v2 = prop2;
    v3 = prop2;
    v0 = rem * prop2;
    v1 = q * prop2;
    m14->SetViewportRectArgs(v0, v1, v2, v3);
    FUN_0067ddb0()->v21(m14, handle1, h2, a3, col[3]);
}
void FUN_007b35a0(void*) {}
void FUN_007b3630(void*) {}
void FUN_007b3760(void*) {}
void FUN_007b3820(void*) {}
