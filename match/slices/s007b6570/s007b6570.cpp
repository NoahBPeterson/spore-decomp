// Slice s007b6570 - cThumbnailManager job plumbing (refcounted render jobs).
// 32-bit MSVC 2008 SP1, /O2 /arch:SSE. Vtable stubs are generated padding (v##) around the real slots.
#include <intrin.h>
#include <string.h>

struct Tgt3; struct Tgt3Q; struct Tgt3P; struct cViewer;
// ---- callee stub classes (slot index = vtable offset / 4) ----
struct GfxA {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
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
    virtual void v1a();
    virtual void v1b();
    virtual void v1c();
    virtual void v1d();
    virtual void v1e();
    virtual void v1f();
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
    virtual void v2a();
    virtual void v2b();
    virtual void v2c();
    virtual void v2d();
    virtual void v2e();
    virtual void v2f();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void f57(int* out);
};
struct GfxB {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void f6(int* out);
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void f22(int* a, int* b, int c, float d);
    virtual void v17();
    virtual void v18();
    virtual void f25(int a, int b, int c, int d, int e);
};
struct FitScene {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void Attach(int zero, cViewer* v);
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void s19();
};
struct FitDevice {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual int f7();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual bool Select(int target);
    virtual FitScene* GetScene();
    virtual int GetCurrent();
};
struct App {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual FitDevice* f20();
};
struct MsgSrv {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void f5(int id, void* msg, int z);
    virtual void f6(int a, int b, int c, int d);
};
struct Mgr67dd50 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
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
    virtual void v1a();
    virtual void v1b();
    virtual void v1c();
    virtual void v1d();
    virtual void f30(void* self, int z, void* st);
};
struct Tgt3 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void f3(int a, int b, int c, int d);
};
struct SlotObj {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual Tgt3* f4();
};
struct Tgt3P {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void f3(int a, void* p, int c, int d);
};
struct Obj79 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
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
    virtual void v1a();
    virtual void v1b();
    virtual void v1c();
    virtual void v1d();
    virtual void v1e();
    virtual void v1f();
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
    virtual void v2a();
    virtual void v2b();
    virtual void v2c();
    virtual void v2d();
    virtual void v2e();
    virtual void v2f();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v3a();
    virtual void v3b();
    virtual void v3c();
    virtual void v3d();
    virtual void v3e();
    virtual void v3f();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v4a();
    virtual void v4b();
    virtual void v4c();
    virtual void v4d();
    virtual void v4e();
    virtual Tgt3Q* f79();
};
struct Tgt3Q {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void f3(int a, int b, void* p, int d);
};
struct Obj0c {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void f3(int a, int b, void* p, int d);
};

// ---- viewer (cViewer stub; real methods at 0x7c3c10.. etc.) ----
struct ViewerRef { int viewer; int z0, z1, z2; };      // {viewer,0,0,0} context handed to job callbacks

struct cViewer {
    char pad0[0xc0];
    float viewProj[16];                    // +0xc0
    void Copy(int a, int b, int c);        // 0x7c50b0
    void F4b50(float v);                   // 0x7c4b50
    void SetRaster(const int* r, int a);   // 0x7c4be0
    void F3c20(const float* v);            // 0x7c3c20
    void F3c50(int a);                     // 0x7c3c50
    void F4a60(int* rect);                 // 0x7c4a60
    bool Update();                         // 0x7c4fd0
    void F3c10();                          // 0x7c3c10
    void SetViewAngleY(float a);           // 0x7c53d0
    void F40f0(void* xf);                  // 0x7c40f0
    void F4d00(void* xf);                  // 0x7c4d00
    float F40a0();                         // 0x7c40a0
    void F4ba0(float a);                   // 0x7c4ba0
};

GfxA*      __cdecl Gfx_67dd40();
GfxB*      __cdecl Gfx_67ddb0();
void*      __cdecl Gfx_67dda0();
App*       __cdecl SP_App();                 // 0x67dd10
MsgSrv*    __cdecl SP_MessageServer();       // 0x67dcc0
Mgr67dd50* __cdecl Mgr_67dd50();
void __cdecl shader(int id, const void* data, int on);   // 0x777ae0
extern float g_1485720;

void* __cdecl operator new(unsigned int, const char*, int, int, int, int);

struct AtomicInt32 {
    volatile long mn;
    void Set(long v) { _InterlockedExchange(&mn, v); }
};
struct MsgHdr {
    virtual void s0();
    virtual void AddRef();
    virtual void Release();
    AtomicInt32 mRefCount;     // +0x04
    int f8;
    int fc;
    int f10;
    int f14;
    MsgHdr() : f10(0) {}
};
struct MsgBase : MsgHdr {
    virtual void s0();
    virtual void AddRef();
    virtual void Release();
    MsgBase() { mRefCount.Set(0); }
};
struct Msg : MsgBase {
    Msg() {}
    virtual void s0();
};

struct MsgRef {
    Msg* p;
    MsgRef(Msg* x) : p(x) { if (p) ((void(__thiscall*)(Msg*))(*(void***)p)[1])(p); }
    ~MsgRef() { p->Release(); }
};

// ===========================================================================
//  0x007b6570  job setup: viewer copy + graphics message
// ===========================================================================
struct Obj14 { char pad[0xc]; Obj0c* o; };
struct ThumbA {
    char pad[0x10];
    cViewer* viewer;     // +0x10
    Obj14*   p14;        // +0x14
    void Fn35a0();       // 0x7b35a0
    void Run6570(int a1, int a2, int* a3, int a4);
};
// @ 0x007b6570
void ThumbA::Run6570(int a1, int a2, int* a3, int a4)
{
    viewer->Copy(*a3, 0, 0);
    viewer->F4b50(1.0f);
    MsgRef mr(new("Graphics", 0, 0, 0, 0) Msg());
    Msg* m = mr.p;
    int a[2] = { -1, -1 };
    Gfx_67dd40()->f57(a);
    int b[2] = { -1, -1 };
    Gfx_67ddb0()->f6(b);
    viewer->SetRaster(a, 1);
    float col[4] = { 0.0f, 0.0f, 0.0f, g_1485720 };
    viewer->F3c20(col);
    viewer->F3c50(7);
    m->f8 = SP_App()->f20()->f7();
    SP_MessageServer()->f5(0x12d74a2, m, 0);
    ViewerRef ctx = { (int)viewer, 0, 0, 0 };
    p14->o->f3(a1, a2, &ctx, a4);
    Gfx_67ddb0()->f22(a, b, a4, 1.0f);
    Fn35a0();
}

// ===========================================================================
//  0x007b6730  job: viewer pair render + shader constants
// ===========================================================================
extern int g_16f8b10[16];
extern int g_16f8c70[16];
struct ThumbB {
    char pad0[0xc];
    cViewer* viewerA;     // +0x0c
    cViewer* viewerB;     // +0x10
    int      m14[16];     // +0x14
    int      m54[16];     // +0x54
    int      r94[2];      // +0x94
    int      r9c[2];      // +0x9c
    char     pada4[4];
    Obj79*   oa8;         // +0xa8
    char     padac[0x14];
    GfxB*    oc0;         // +0xc0
    char     padc4[0x14];
    bool     bd8;         // +0xd8
    void Fn3820(cViewer* v, int* r, int a);    // 0x7b3820
    void Run6730(int a1, int a2, int a3, int a4);
};
// @ 0x007b6730
void ThumbB::Run6730(int a1, int a2, int a3, int a4)
{
    {
        int rect[4] = { 0, 0, 0x200, 0x200 };
        viewerA->F4a60(rect);
    }
    if (viewerA->Update()) {
        memcpy(m14, g_16f8b10, sizeof(m14));
        memcpy(m54, g_16f8c70, sizeof(m54));
        shader(0x20a, m14, 1);
        shader(0x20b, m54, 1);
        viewerA->F3c10();
    }
    GfxB* g = Gfx_67ddb0();
    Gfx_67dda0();
    if (bd8) {
        Fn3820(viewerA, r94, a4);
    } else {
        viewerA->SetRaster(r94, 1);
        viewerA->F3c50(7);
        ViewerRef ctx = { (int)viewerA, 0, 0, 0 };
        oa8->f79()->f3(1, a2, &ctx, a4);
    }
    if (bd8) {
        Fn3820(viewerB, r9c, a4);
    } else {
        viewerB->SetRaster(r9c, 1);
        viewerB->F3c50(7);
        ViewerRef ctx = { (int)viewerB, 0, 0, 0 };
        oa8->f79()->f3(a1, a2, &ctx, a4);
    }
    shader(0x20a, 0, 0);
    shader(0x20b, 0, 0);
    g->f25((int)oc0, a1, a2, a3, a4);
}

// ===========================================================================
//  0x007b68f0  job: raster + dispatch
// ===========================================================================
struct ThumbC {
    char pad0[0x108c];
    cViewer* viewer;    // +0x108c
    char pad1[0x10f4 - 0x1090];
    int      raster[2]; // +0x10f4
    ThumbC*  next;      // +0x10fc
    void Fn49f0(int a, int b, ViewerRef* c, int d);   // 0x7b49f0
    void Run68f0(int flag, int a2, int a3, int a4, int a5);
};
// @ 0x007b68f0
void ThumbC::Run68f0(int flag, int a2, int a3, int a4, int a5)
{
    viewer->SetRaster(raster, 1);
    if (flag == 0)
        viewer->F3c50(7);
    ViewerRef ctx = { (int)viewer, 0, 0, 0 };
    next->Fn49f0(a2, a3, &ctx, a5);
}

// ===========================================================================
//  0x007b6980  job slice pump
// ===========================================================================
struct JobStatus {
    int  one;
    int  zero;
    char flag;
    int  z[8];
};
struct ThumbD {
    char pad0[0xc];
    SlotObj** begin;   // +0x0c
    SlotObj** end;     // +0x10
    char pad1[0x10];
    int count;         // +0x24 ... (+0x14..+0x23 above)
    int index;         // +0x28
    int msgId;         // +0x2c
    int msgArg;        // +0x30
    void Fn49f0(int a, int b, int c, int d);   // 0x7b49f0
    void Run6980(int a, int b, int c, int d);
};
// @ 0x007b6980
void ThumbD::Run6980(int a, int b, int c, int d)
{
    int lim = count;
    if (lim == 0) {
        Fn49f0(a, b, c, d);
        return;
    }
    int n = (int)(end - begin);
    int idx = index;
    lim += idx;
    if (lim > n) lim = n;
    for (int i = idx; i < lim; i++)
        begin[i]->f4()->f3(a, b, c, d);
    if (lim < n) {
        index = lim;
        Mgr67dd50* m = Mgr_67dd50();
        JobStatus st;
        st.zero = 0;
        for (int k = 0; k < 8; k++) st.z[k] = 0;
        st.one = 1;
        st.flag = 1;
        m->f30(this, 0, &st);
        return;
    }
    if (msgArg != 0)
        SP_MessageServer()->f6(msgId, msgArg, 0, 0);
}

// ===========================================================================
//  0x007b6a90  dispatch loop
// ===========================================================================
struct IItem {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void a3();
    virtual void* Get();
};

struct IOut {
    virtual void b0();
    virtual void b1();
    virtual void b2();
    virtual void Run(int a, int b, int c, int d);
};

struct ItemList2 {
    char pad0[0x20];
    IItem** begin;      // +0x20
    IItem** end;        // +0x24
    void Other();
    void Fn(int a, int b, int c, int d);
};

// @ 0x007b6a90
void ItemList2::Fn(int a, int b, int c, int d)
{
    if (begin != end) {
        int n = end - begin;
        for (unsigned i = 0; i < (unsigned)n; i++) {
            IItem* item = begin[i];
            IOut* out = (IOut*)item->Get();
            out->Run(a, b, c, d);
        }
    }
    Other();
}


// ===========================================================================
//  EH destructors (members with inline dtors give the unwind states)
// ===========================================================================
void __cdecl operator_delete__(void* p) throw();     // 0xf47380

struct IRef2 { virtual void s0(); virtual void s1(); virtual void Release2(); };
struct VBase {
    IRef2** mBegin;
    IRef2** mEnd;
    ~VBase() {
        if (mBegin && ((int*)mBegin)[-1])
            operator_delete__(mBegin);
    }
};
struct RefVec : VBase {
    ~RefVec();
};
static inline void DestroyRange(IRef2** first, IRef2** last)
{
    for (; first < last; ++first)
        if (*first) (*first)->Release2();
}
// @ 0x007b6b60
RefVec::~RefVec()
{
    DestroyRange(mBegin, mEnd);
}

struct IRef1 { virtual void s0(); virtual void Release1(); };
struct RefP1 {
    IRef1* p;
    ~RefP1() { if (p) p->Release1(); }
};
struct Str16 {
    unsigned short* mBegin;
    unsigned short* mEnd;
    unsigned short* mCap;
    ~Str16() {
        if ((((int)mCap - (int)mBegin) & ~1) > 2 && mBegin)
            operator_delete__(mBegin);
    }
};
struct Base0 {
    virtual ~Base0() {}
};
struct AbilityA : Base0 {
    char  pad[0x40 - 4];
    RefP1 m40;        // +0x40
    Str16 m44;        // +0x44
    char  pad50[4];
    RefP1 m54;        // +0x54
    ~AbilityA();
};
// @ 0x007b6bd0
AbilityA::~AbilityA() {}

struct AtomicLong {
    volatile long mn;
};
static inline long AtomicAdd(volatile long* p, long v) { return _InterlockedExchangeAdd(p, v); }
struct RcObj { char pad[8]; AtomicLong rc; };
struct AtomicPtr {
    RcObj* p;
    ~AtomicPtr() {
        if (p) {
            AtomicLong* c = &p->rc;
            AtomicAdd(&c->mn, -1);
            long v = AtomicAdd(&c->mn, 0);
            if (v < 1) AtomicAdd(&c->mn, 1);
            else AtomicAdd(&c->mn, 0);
        }
    }
};
struct AbilityB : Base0 {
    char      pad[4];
    AtomicPtr m8;     // +0x08
    char      padc[4];
    RefP1     m10;    // +0x10
    char      pad14[4];
    char*     mBegin; // +0x18
    char*     mEnd;
    char*     mCap;   // +0x20
    ~AbilityB();
};
// @ 0x007b6c70
AbilityB::~AbilityB()
{
    if (mCap - mBegin > 1 && mBegin)
        operator_delete__(mBegin);
}


// ===========================================================================
//  0x007b6d50 / 0x007b7270  camera pull-back: fit a list of bounding spheres in the view frustum
// ===========================================================================
#include <math.h>
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    Vector3& operator+=(const Vector3& b) { x += b.x; y += b.y; z += b.z; return *this; }
};
struct Matrix3 {
    Vector3 row0, row1, row2;
    Matrix3& Assign(const Matrix3& m);          // 0x41cb40
};
struct XForm {                      // flags, change counter, position, scale, basis
    unsigned short flags;           // +0
    unsigned short rev;             // +2
    Vector3 pos;                    // +4
    float scale;                    // +0x10
    Matrix3 m;                      // +0x14
    void PreRotateY(float a);       // 0x6baa70
};
struct cFrustumCull {
    char data[0xf0];
    void Setup(const float* viewProj);                                   // 0x6ffe00
    char FrustumTestSphere(const float* a, const float* b, int c);       // 0x700120
};
struct SphV {
    float x, y, z;
    SphV() {}
    SphV(const SphV& o) { x = o.x; y = o.y; z = o.z; }
};
struct Sphere6 { SphV c; SphV e; };
struct Mat16 { float m[16]; };
struct SphereVec { Sphere6* begin; Sphere6* end; };

extern const Matrix3 g_identityBasis;                          // 0x1635788
extern float g_defaultPosX;      // 0x1635648
extern float g_defaultPosY;      // 0x163564c
extern float g_defaultPosZ;      // 0x1635650
extern float g_13ec4b4, g_13ec4b8, g_140ffc8, g_13eb960, g_140f7ac, g_1471064;

struct FitJob {
    char Fit6d50(SphereVec* v, cViewer* vw, const float* c, const float* off, float* fov);
    void Run7270(SphereVec* v, cViewer* vw, int target, const float* c, float k, float yaw);
};

// @ 0x007b6d50
char FitJob::Fit6d50(SphereVec* v, cViewer* vw, const float* c, const float* off, float* fov)
{
    float fv = *fov;
    Sphere6 s;
    XForm xf;
    vw->SetViewAngleY(fv);
    cFrustumCull cull1;
    Mat16 vp1 = *(Mat16*)vw->viewProj;
    cull1.Setup(vp1.m);
    int n = (int)(v->end - v->begin);
    for (int i = 0; i < n; i++) {
        s = v->begin[i];
        if (cull1.FrustumTestSphere(&s.c.x, &s.e.x, 0) >= 0) {
            xf.flags = 0;
            xf.rev = 0;
            xf.pos.x = g_defaultPosX;
            xf.pos.y = g_defaultPosY;
            xf.pos.z = g_defaultPosZ;
            xf.scale = g_1485720;
            xf.m.row0 = Vector3(g_identityBasis.row0.x, g_identityBasis.row0.y, g_identityBasis.row0.z);
    xf.m.row1 = Vector3(g_identityBasis.row1.x, g_identityBasis.row1.y, g_identityBasis.row1.z);
    xf.m.row2 = Vector3(g_identityBasis.row2.x, g_identityBasis.row2.y, g_identityBasis.row2.z);
            vw->F40f0(&xf);
            xf.pos = xf.pos - *(const Vector3*)off;
            xf.flags |= 4;
            xf.rev++;
            vw->F4d00(&xf);
            return 0;
        }
    }
    vw->SetViewAngleY(fv * g_13ec4b4);
    cFrustumCull cull2;
    Mat16 vp2 = *(Mat16*)vw->viewProj;
    cull2.Setup(vp2.m);
    n = (int)(v->end - v->begin);
    bool all = true;
    for (int i = 0; i < n; i++) {
        s = v->begin[i];
        if (cull2.FrustumTestSphere(&s.c.x, &s.e.x, 0) >= 0)
            all = false;
    }
    if (!all)
        return 1;
    xf.flags = 0;
    xf.rev = 0;
    xf.pos.x = g_defaultPosX;
    xf.pos.y = g_defaultPosY;
    xf.pos.z = g_defaultPosZ;
    xf.scale = g_1485720;
    xf.m.row0 = Vector3(g_identityBasis.row0.x, g_identityBasis.row0.y, g_identityBasis.row0.z);
    xf.m.row1 = Vector3(g_identityBasis.row1.x, g_identityBasis.row1.y, g_identityBasis.row1.z);
    xf.m.row2 = Vector3(g_identityBasis.row2.x, g_identityBasis.row2.y, g_identityBasis.row2.z);
    vw->F40f0(&xf);
    xf.flags |= 4;
    xf.rev++;
    xf.pos += *(const Vector3*)off * g_1471064;
    vw->F4d00(&xf);
    return 0;
}

// @ 0x007b7270
void FitJob::Run7270(SphereVec* v, cViewer* vw, int target, const float* c, float k, float yaw)
{
    if (!vw)
        return;
    FitDevice* dev = SP_App()->f20();
    {
        XForm xf;
        xf.flags = 0;
        xf.rev = 0;
        xf.pos.x = g_defaultPosX;
        xf.pos.y = g_defaultPosY;
        xf.pos.z = g_defaultPosZ;
        xf.scale = g_1485720;
        xf.m.Assign(g_identityBasis);
        vw->F4d00(&xf);
    }
    if (target) {
        int prev = dev->GetCurrent();
        if (!dev->Select(target))
            return;
        vw->F4b50(1.0f);
        dev->GetScene()->Attach(0, vw);
        dev->Select(prev);
    } else {
        vw->F4b50(1.0f);
        dev->GetScene()->Attach(0, vw);
    }
    XForm xf2;
    xf2.flags = 0;
    xf2.rev = 0;
    xf2.pos.x = g_defaultPosX;
    xf2.pos.y = g_defaultPosY;
    xf2.pos.z = g_defaultPosZ;
    xf2.scale = g_1485720;
    xf2.m.Assign(g_identityBasis);
    vw->F40f0(&xf2);
    xf2.PreRotateY(yaw);
    xf2.pos.x = c[0];
    xf2.pos.y = c[1];
    xf2.pos.z = c[2];
    xf2.flags |= 4;
    xf2.rev++;
    vw->F4d00(&xf2);
    Matrix3 m2;
    m2.Assign(xf2.m);
    float inv = 1.0f / (float)sqrt((double)(m2.row1.x * m2.row1.x + m2.row1.y * m2.row1.y + m2.row1.z * m2.row1.z + g_13ec4b8));
    float s = k * g_140ffc8;
    float off[3];
    off[0] = m2.row1.x * inv * s;
    off[1] = m2.row1.y * inv * s;
    off[2] = m2.row1.z * inv * s;
    dev->GetScene()->s19();
    vw->F4b50(1.0f);
    float fov = vw->F40a0();
    vw->F4ba0(g_13eb960);
    int i = 0;
    do {
        if (Fit6d50(v, vw, c, off, &fov))
            break;
        i++;
    } while ((float)i < g_140f7ac);
    vw->SetViewAngleY(fov);
}
// --- equivalence checker address annotations
    extern float g_defaultPosY; // 0x0163564c
    extern float g_defaultPosZ; // 0x01635650

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
