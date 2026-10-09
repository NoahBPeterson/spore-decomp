// Slice s007b55f0 - cThumbnailManager job plumbing (refcounted render-job setup).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

void* operator new(unsigned int, const char*, int, int, int, int);   // 0x00f473a0

// ---- atomic intrusive refcount (EA RefCount with underflow guard) ------------------------
// obj layout: +0 payload, +4 flags, +8 refcount
struct TargetBase {
    struct Tex* tex;                    // +0
    uint32_t flags;                     // +4
};

static __forceinline long DecAndGet(volatile long* p)
{
    _InterlockedExchangeAdd(p, -1);
    return _InterlockedExchangeAdd(p, 0);
}

struct RcBase {
    volatile long rc;
    void AddRef() { _InterlockedExchangeAdd(&rc, 1); }
    void Release()
    {
        long v = DecAndGet(&rc);
        if (v < 1)
            _InterlockedExchangeAdd(&rc, 1);
        else
            _InterlockedExchangeAdd(&rc, 0);
    }
};

struct TargetObj : TargetBase, RcBase {
};

struct LockInfo {
    void* data;
    int a, b, c, d, e, f;
};

struct Tex {
    int Lock(int mode, int zero, LockInfo* out);    // 011ef750
    void Unlock(LockInfo* info);                    // 011ef880
};

struct AutoTarget {
    TargetObj* p;
    AutoTarget(TargetObj* o) : p(o) { if (o) static_cast<RcBase*>(o)->AddRef(); }
    ~AutoTarget() { static_cast<RcBase*>(p)->Release(); }
};

// ---- global interfaces -------------------------------------------------------------------
struct TargetFactory {              // FUN_0067dd60
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void Register(TargetObj* o);                                    // +0x34
    virtual void v14();
    virtual TargetObj* Create(int a, int b, int c, int d, int e, int f, int g, int h); // +0x3c
};
struct SizeSource {                 // FUN_0067ddb0
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void GetSize(int* wh);                                          // +0x18
};
struct Blitter {                    // FUN_0067dda0
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8();
    virtual void MeasureSomething(int w, int h, int* o0, int* o1, int* o2, int* o3); // +0x24
    virtual void v10();
    virtual void v11();
    virtual void Blit(int a, int b, int c);                                 // +0x30
};

TargetFactory* GetTargetFactory();  // 0067dd60
SizeSource* GetSizeSource();        // 0067ddb0
Blitter* GetBlitter();              // 0067dda0

// ---- thumbnail job shapes -----------------------------------------------------------------
struct RtParams {
    char pad0[0x0c];
    int f0c, f10;
    int pad14;
    int f18, f1c, f20, f24;
};

struct RtJobA {
    char pad0[0x30];
    RtParams* p;                    // +0x30
    void Run();
};

struct RtJobB {
    char pad0[0x18];
    RtParams* p;                    // +0x18
    void Run();
};

static __forceinline void UploadTargetA(TargetObj* obj)
{
    LockInfo info;
    Tex* t = obj->tex;
    if (t->Lock(2, 0, &info)) {
        int wh[2];
        wh[0] = -1;
        wh[1] = -1;
        GetSizeSource()->GetSize(wh);
        GetBlitter()->Blit(wh[0], wh[1], (int)info.data);
        if (!(obj->flags & 1))
            GetTargetFactory()->Register(obj);
        obj->tex->Unlock(&info);
    }
}

static __forceinline void UploadTargetB(TargetObj* obj)
{
    Tex* t = obj->tex;
    LockInfo info;
    if (t->Lock(2, 0, &info)) {
        int wh[2];
        wh[0] = -1;
        wh[1] = -1;
        GetSizeSource()->GetSize(wh);
        GetBlitter()->Blit(wh[0], wh[1], (int)info.data);
        t->Unlock(&info);
    }
}

// @ 0x007b6010
void RtJobA::Run()
{
    TargetFactory* f = GetTargetFactory();
    TargetObj* obj = f->Create(p->f20, p->f24, p->f18, p->f1c, 1, 0x208, 0x15, 8);
    AutoTarget ref(obj);
    if (!(obj->flags & 1))
        GetTargetFactory()->Register(obj);
    UploadTargetA(obj);
}

// @ 0x007b63b0
void RtJobB::Run()
{
    TargetFactory* f = GetTargetFactory();
    TargetObj* obj = f->Create(p->f10, p->f0c, p->f1c, p->f20, 1, 0x208, 0x15, 8);
    AutoTarget ref(obj);
    if (!(obj->flags & 1))
        GetTargetFactory()->Register(obj);
    UploadTargetB(obj);
}

// ---- 007b64f0: AutoRef member release -----------------------------------------------------
struct RefHolder {
    char pad0[8];
    TargetObj* p;                   // +8
};

// @ 0x007b64f0
void __fastcall RefHolder_Reset(RefHolder* h)
{
    if (h->p) {
        TargetObj* o = h->p;
        if (o) {
            h->p = 0;
            static_cast<RcBase*>(o)->Release();
        }
    }
}

// ---- 007b5ad0: post a render-job message (stdcall, 5 args) ---------------------------------
struct IRefObj {
    virtual int AddRef();
    virtual int Release();
};

struct IJobBase {                   // primary base of JobInfo (vptr at +0)
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual void v3();
    virtual int* Build(int zero, void* msg);                // +0x10 (slot 4)
};

struct CVSBase {                    // vptr at +4, refcount at +8
    virtual void cv0();
    int rc8;
    CVSBase() { rc8 = 0; }
};

struct JobInfo : IJobBase, CVSBase {    // 0x1c bytes, "Graphics" heap
    bool bound;                                             // +0xc
    IRefObj* owner;                                         // +0x10
    int arg14;                                              // +0x14
    int arg18;                                              // +0x18
    JobInfo() { bound = false; owner = 0; }
    virtual int AddRef();
    virtual int Release();
    virtual void v2();
    virtual void v3();
    virtual int* Build(int zero, void* msg);
    virtual void cv0();
};

struct MsgBase {
    virtual int mv0();
    virtual int AddRef();
    virtual int Release();
    volatile long rc;               // +4
    MsgBase() { _InterlockedExchange(&rc, 0); }
};

struct JobMsg : MsgBase {           // 0x18 bytes
    JobInfo* job;                   // +8
    int pad0c;
    int arg10;                      // +0x10
    int pad14;
    JobMsg() { arg10 = 0; }
    virtual int mv0();
    virtual int AddRef();
    virtual int Release();
};

struct MsgBuf {
    int a;
    int b;
    char flag;
    int d, e;
    int tag;
    JobMsg* msg;
    int g, h, i, j;
};

struct MsgSink {
    char pad[0x78];
};

struct SinkObj {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void Post(int id);                              // +0x78
};

SinkObj* GetSink();                 // 0067dd50

template <class T> struct SmartP {
    T* p;
    SmartP(T* x) : p(x) { if (p) p->AddRef(); }
    ~SmartP() { if (p) p->Release(); }
    T* operator->() const { return p; }
};

// @ 0x007b5ad0
void __stdcall PostRenderJob(IRefObj* owner, int arg14, int arg18, int tagv, int arg10)
{
    SmartP<JobInfo> job(new ("Graphics", 0, 0, 0, 0) JobInfo);
    if (!job->bound) {
        job->arg14 = arg14;
        IRefObj* old = job->owner;
        if (owner != old) {
            if (owner)
                owner->AddRef();
            job->owner = owner;
            if (old)
                old->Release();
        }
        job->bound = true;
        job->arg18 = arg18;
    }
    MsgBuf mb;
    mb.a = 1;
    mb.b = 0;
    mb.flag = 1;
    mb.d = 0;
    mb.e = 0;
    mb.tag = 0;
    mb.msg = 0;
    mb.g = mb.h = mb.i = mb.j = 0;
    {
        SmartP<JobMsg> m(new ("Graphics", 0, 0, 0, 0) JobMsg);
        m->job = job.p;
        m->arg10 = arg10;
        mb.flag = 0;
        mb.b = tagv;
        mb.tag = 0x5fadac4;
        mb.msg = m.p;
        SinkObj* sink = GetSink();
        sink->Post((int)job->Build(0, &mb));
    }
}

// ---- bounds / framing helpers -------------------------------------------------------------
#include <math.h>
#define FLT_BIG 3.402823466e+38f

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) { x = a; y = b; z = c; }
};

struct Bounds6 {
    Vector3 mn;
    Vector3 mx;
    Bounds6() { mn = Vector3(FLT_BIG, FLT_BIG, FLT_BIG); mx = Vector3(-FLT_BIG, -FLT_BIG, -FLT_BIG); }
    void Expand(const Vector3* p, int n, int stride);       // 007b4c10
};

struct MeshGeom {
    int count;                      // +0x10
    const Vector3* verts;           // +0x14
};

struct MeshEntry {                  // 0x20 bytes
    char pad0[0x10];
    MeshGeom geom;
    char pad18[2];
    unsigned short stride;          // +0x1a
    char pad1c[4];
};

struct MeshObj {
    char pad0[8];
    MeshEntry* entries;             // +8
};

struct MeshVec {
    MeshObj** begin;
    MeshObj** end;
};

int __cdecl FindEntry(MeshObj* o, int a, int b, int c, int d);   // 0071ddc0

// @ 0x007b5c80
void __stdcall MeshBoundingSphere(MeshVec* v, Vector3* outCenter, float* outRadius)
{
    Bounds6 b;
    int n = (int)(v->end - v->begin);
    for (int i = 0; i < n; i++) {
        int idx = FindEntry(v->begin[i], 1, -1, 3, 0xe);
        if (idx >= 0) {
            MeshEntry* base = v->begin[i]->entries;
            const MeshGeom& g = base[idx].geom;
            b.Expand(g.verts, g.count, base[idx].stride);
        }
    }
    if (b.mn.x > b.mx.x)
        return;
    float dx = b.mx.x - b.mn.x;
    float dy = b.mx.y - b.mn.y;
    float dz = b.mx.z - b.mn.z;
    *outCenter = Vector3((b.mx.x + b.mn.x) * 0.5f, (b.mx.y + b.mn.y) * 0.5f, (b.mx.z + b.mn.z) * 0.5f);
    *outRadius = sqrtf(dx * dx + dy * dy + dz * dz) * 0.5f + 1.0f;
}

// ---- thumbnail framing: fit the opaque pixel box into the viewport ------------------------
struct ViewParams {
    char pad0[0x3c];
    float offX;                     // +0x3c
    float offY;                     // +0x40
    float padX;                     // +0x44
    float padY;                     // +0x48
    float scale;                    // +0x4c
    float sx, sy;                   // +0x50, +0x54
    float z;                        // +0x58
};

struct ViewNode {
    char pad0[0x0c];
    ViewParams** params;            // +0xc
};

struct FrameScene {
    char pad0[8];
    int w8;                         // +8
    int hc;                         // +0xc
    ViewNode* node;                 // +0x10
    char pad14[0x0c];
    float fitSize;                  // +0x20
    float fitAspect;                // +0x24
};

struct FrameJob {
    char pad0[0x18];
    int a18, b1c;                   // +0x18, +0x1c
    char pad20[4];
    int h;                          // +0x24
    int w;                          // +0x28
    unsigned char* data;            // +0x2c  (RGBA, 4 bytes per pixel)
    FrameScene* sc;                 // +0x30
    void Fit();
    void FitAspect();
};

// @ 0x007b5e20
void FrameJob::Fit()
{
    GetBlitter()->Blit(a18, b1c, (int)data);
    int minI = h;
    int maxI = 0;
    int minJ = w;
    int maxJ = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (data[(i * w + j) * 4 + 3]) {
                if (j < minI) minI = j;
                if (j > maxI) maxI = j;
                if (i < minJ) minJ = i;
                if (i > maxJ) maxJ = i;
            }
        }
    }
    int o0, o1, o2, o3;
    GetBlitter()->MeasureSomething(sc->w8, sc->hc, &o0, &o1, &o2, &o3);
    float fMinI = (float)minI;
    float dI = (float)fabs(maxI - fMinI);
    float fMinJ = (float)minJ;
    float dJ = (float)fabs(fMinJ - maxJ);
    float scale;
    if (dI > dJ)
        scale = (float)h / dI;
    else
        scale = (float)w / dJ;
    scale = scale * 0.8f;
    ViewParams* p = *sc->node->params;
    float inv = 1.0f / (float)h;
    p->padX = (((float)h - scale * dI) * 0.5f * inv) * 0.75f;
    p->padY = (((float)w - scale * dJ) * 0.5f * inv) * 0.75f;
    p->offX = fMinI * inv;
    p->offY = fMinJ * inv;
    p->sx = 1.2f;
    p->sy = 1.2f;
    p->scale = scale;
    p->z = 0.0f;
}

// @ 0x007b6160
void FrameJob::FitAspect()
{
    GetBlitter()->Blit(a18, b1c, (int)data);
    int minI = h;
    int maxI = 0;
    int minJ = w;
    int maxJ = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (data[(i * w + j) * 4 + 3]) {
                if (j < minI) minI = j;
                if (j > maxI) maxI = j;
                if (i < minJ) minJ = i;
                if (i > maxJ) maxJ = i;
            }
        }
    }
    int o0, o1, o2, o3;
    GetBlitter()->MeasureSomething(sc->w8, sc->hc, &o0, &o1, &o2, &o3);
    FrameScene* s = sc;
    float fMinI = (float)minI;
    float dI = (float)fabs(maxI - fMinI);
    float fMinJ = (float)minJ;
    float dJ = (float)fabs(fMinJ - maxJ);
    float scale;
    if (dI > dJ)
        scale = (s->fitSize / dI) * (float)h;
    else
        scale = (s->fitSize / dJ) * (float)w;
    float hf = (float)h;
    float py = ((float)w - scale * dJ) * 0.5f;
    float inv = 1.0f / hf;
    float padY = (inv * py) * 0.75f;
    float padX = (((float)h - scale * dI) * 0.5f * inv) * 0.75f;
    if (dJ < dI)
        padY = (s->fitAspect * inv) * py + padY;
    ViewParams* p = *s->node->params;
    p->padX = padX;
    p->offX = fMinI * inv;
    p->offY = fMinJ * inv;
    p->padY = padY;
    p->sx = 1.2f;
    p->sy = 1.2f;
    p->scale = scale;
    p->z = 0.0f;
}

// ---- 007b55f0: pull the camera back until the bounds fit the frustum ----------------------
struct Matrix3 {
    Vector3 row0, row1, row2;
    Matrix3& Assign(const Matrix3& m);          // 0041cb40
};

struct XForm {                      // transform block: flags, change counter, position, scale, basis
    unsigned short flags;           // +0
    unsigned short rev;             // +2
    Vector3 pos;                    // +4
    float scale;                    // +0x10
    Matrix3 m;                      // +0x14
    void PreRotateY(float a);       // 006baa70
};

struct cFrustumCull {
    unsigned int data[0x3c];
    void Setup(const float* viewProj);                          // 006ffe00
    unsigned FrustumTestSphere(const float* a, const float* b, int c);   // 00700120
};

struct FitViewer {
    char pad0[0xc0];
    float viewProj[16];             // +0xc0
    void SetFov(float f);           // 007c4b50
    void SetXForm(XForm* x);        // 007c40f0
    void SetViewAngleY(float a);    // 007c53d0
    void SetNear(float n);          // 007c4ba0
    void ApplyXForm(XForm* x);      // 007c4d00
};

struct FitScene {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void Attach(int zero, FitViewer* v);            // +0x20
};

struct FitDevice {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
    virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12();
    virtual bool Select(int target);                        // +0x34
    virtual FitScene* GetScene();                           // +0x38
    virtual int GetCurrent();                               // +0x3c
};

struct FitApp {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11();
    virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
    virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
    virtual FitDevice* GetDevice();                         // +0x50
};

FitApp* GetApp();                   // 0067dd10 (SP::App)

extern const Matrix3 g_identityBasis;       // 01635788
extern float g_defaultPosX;   // 0x01635648
extern float g_defaultPosY;   // 0x0163564c
extern float g_defaultPosZ;   // 0x01635650

struct Mat16 { float m[16]; };

// @ 0x007b55f0
void __stdcall FitViewerToBounds(const float* b, FitViewer* v, int target, float yaw)
{
    if (!v)
        return;
    FitDevice* dev = GetApp()->GetDevice();
    int prev = dev->GetCurrent();
    if (!dev->Select(target))
        return;
    v->SetFov(1.0f);
    dev->GetScene()->Attach(0, v);
    dev->Select(prev);
    XForm xf;
    xf.flags = 0;
    xf.rev = 0;
    xf.pos.x = g_defaultPosX;
    xf.pos.y = g_defaultPosY;
    xf.pos.z = g_defaultPosZ;
    xf.scale = 1.0f;
    xf.m.Assign(g_identityBasis);
    v->SetXForm(&xf);
    xf.PreRotateY(yaw);
    Vector3 np = xf.pos;
    Matrix3 m2;
    m2.Assign(xf.m);
    float len = sqrtf(m2.row1.z * m2.row1.z + m2.row1.y * m2.row1.y + m2.row1.x * m2.row1.x + 1e-8f);
    float inv = 1.0f / len;
    Vector3 dir(m2.row1.x * inv, m2.row1.y * inv, m2.row1.z * inv);
    v->SetFov(1.0f);
    v->SetViewAngleY(50.0f);
    v->SetNear(0.01f);
    float ex = b[3] - b[0];
    float ey = b[4] - b[1];
    float ez = b[5] - b[2];
    float r = sqrtf(ey * ey + (ez * ez + ex * ex)) * 0.5f;
    float cx = (b[3] + b[0]) * 0.5f;
    float cy = (b[4] + b[1]) * 0.5f;
    float cz = (b[5] + b[2]) * 0.5f;
    xf.flags |= 4;
    xf.rev++;
    np.x = cx - dir.x * r;
    np.y = cy - dir.y * r;
    np.z = cz - dir.z * r;
    xf.pos = np;
    v->ApplyXForm(&xf);
    for (unsigned k = 0; k < 5000; k++) {
        Mat16 vp = *(const Mat16*)v->viewProj;
        cFrustumCull cull;
        cull.Setup(vp.m);
        unsigned res = cull.FrustumTestSphere(b, b + 3, 0);
        if (res & 0xc0)
            return;
        bool nb0 = !(res & 1);
        bool nb1 = !((res >> 1) & 1);
        bool nb2 = !((res >> 2) & 1);
        bool nb3 = !((res >> 3) & 1);
        bool nb4 = !((res >> 4) & 1);
        bool nb5 = !((res >> 5) & 1);
        if ((nb0 && nb1) || (nb2 && nb3)) {
            r = r * 1.01f;
            np.x = cx - dir.x * r;
            np.y = cy - dir.y * r;
            np.z = cz - dir.z * r;
        } else {
            if (nb4 || nb5)
                continue;
            if (nb0)
                np.x = np.x - 0.1f;
            else if (nb1)
                np.x = np.x + 0.1f;
            if (nb2)
                np.y = np.y - 0.1f;
            else if (nb3)
                np.y = np.y + 0.1f;
            else if (!(nb0 || nb1))
                continue;
        }
        xf.flags |= 4;
        xf.rev++;
        xf.pos = np;
        v->ApplyXForm(&xf);
    }
}
// --- equivalence checker address annotations
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
    extern float g_defaultPosY; // 0x0163564c
    extern float g_defaultPosZ; // 0x01635650

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
