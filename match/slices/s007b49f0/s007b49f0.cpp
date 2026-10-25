// Slice s007b49f0 - cThumbnailManager helpers and a bounds-expansion helper.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE1, comiss, no movq).
#include "types.h"
#include <math.h>
#include <new>
#include <intrin.h>

#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

struct Vector3 { float x, y, z; };

struct Bounds6 {
    Vector3 mn;
    Vector3 mx;
    void Expand(const Vector3* p, int n, int stride);
};

// @ 0x007b4c10
void Bounds6::Expand(const Vector3* p, int n, int stride)
{
    n = n - 1;
    if (n >= 0) {
        do {
            if (mn.x > mx.x) {
                mn = *p;
                mx = *p;
            } else {
                if (mn.x > p->x) mn.x = p->x; else if (p->x > mx.x) mx.x = p->x;
                if (mn.y > p->y) mn.y = p->y; else if (p->y > mx.y) mx.y = p->y;
                if (mn.z > p->z) mn.z = p->z; else if (p->z > mx.z) mx.z = p->z;
            }
            p = (const Vector3*)((const char*)p + stride);
            n = n - 1;
        } while (n >= 0);
    }
}

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

struct ItemList {
    char pad0[0xc];
    IItem** begin;      // +0xc
    IItem** end;        // +0x10
    void Fn(int a, int b, int c, int d);
};

// @ 0x007b49f0
void ItemList::Fn(int a, int b, int c, int d)
{
    int n = end - begin;
    for (unsigned i = 0; i < (unsigned)n; i++) {
        IItem* item = begin[i];
        IOut* out = (IOut*)item->Get();
        out->Run(a, b, c, d);
    }
}

// ===========================================================================
// Shared helpers
// ===========================================================================

// Placement allocator used across the graphics code ("Graphics" heap).
void* operator new(unsigned int size, const char* area, int a, int b, int c, int d); // 0x00f473a0

// Vtable / static objects reached by absolute address (relocated in the image).
extern void* g_vtbl_140fedc[];   // 0x0140fedc
extern void* g_vtbl_140fee8[];   // 0x0140fee8
extern void* g_vtbl_13ef094[];   // 0x013ef094
extern void* g_vtbl_13ebcdc[];   // 0x013ebcdc
extern void* g_vtbl_140fef4[];   // 0x0140fef4
extern void* g_vtbl_1453eac[];   // 0x01453eac
extern void* g_vtbl_13ebcb8[];   // 0x013ebcb8
extern void* g_vtbl_140ff20[];   // 0x0140ff20
extern void* g_vtbl_140ff0c[];   // 0x0140ff0c
extern void* g_vtbl_140ff08[];   // 0x0140ff08
extern void* g_vtbl_13eb384[];   // 0x013eb384
extern void* g_vtbl_13eb394[];   // 0x013eb394
extern void* g_vtbl_13eb938[];   // 0x013eb938

// Reference-counted object whose count sits at +8; the underflow-guarded release
// (matches AtomicRefCounted::Release at 0x00401b80).
static __forceinline void ReleaseRc8(void* obj)
{
    volatile long* rc = (volatile long*)((char*)obj + 8);
    _InterlockedExchangeAdd(rc, -1);
    if (_InterlockedExchangeAdd(rc, 0) < 1)
        _InterlockedExchangeAdd(rc, 1);
    else
        _InterlockedExchangeAdd(rc, 0);
}

struct IRefCounted {
    virtual void v0();          // +0x00
    virtual void Release();     // +0x04
};

struct Matrix3 {
    Vector3 row0, row1, row2;
    Matrix3& Assign(const Matrix3& m);          // 0x0041cb40
};

struct XForm {                                  // transform block (0x38 bytes)
    unsigned short flags;                       // +0x00
    unsigned short rev;                         // +0x02
    Vector3 pos;                                // +0x04
    float scale;                                // +0x10
    Matrix3 m;                                  // +0x14
};

// ---- render-target job (0x007b4a50) ---------------------------------------
struct LockInfo {                               // 0x1c bytes
    void* data;
    int a, b, c, d, e, f;
};

struct ITex {
    int Lock(int mode, int zero, LockInfo* out);    // 0x011ef750
    void Unlock(LockInfo* info);                    // 0x011ef880
};

struct RenderTarget {
    ITex* tex;                                  // +0x00
    uint32_t flags;                             // +0x04
};

struct ITargetFactory {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void Register(RenderTarget* o);                                 // +0x34
    virtual void v14();
    virtual RenderTarget* Create(int a, int b, int c, int d, int e, int f,
                                 int g, int h);                             // +0x3c
};

struct IBlitter {
    virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3();
    virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7();
    virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11();
    virtual void Blit(int a, int b, int c);                                 // +0x30
};

ITargetFactory* GetTargetFactory();     // 0x0067dd60
IBlitter* GetBlitter();                 // 0x0067dda0

struct JobOwner {                           // object pointed to by the job's owner slot
    char pad0[8];
    int mMode;                              // +0x08
};

struct ThumbnailBlitJob {
    char pad0[0x0c];
    JobOwner** mppOwner;                    // +0x0c
    char pad10[0x38 - 0x10];
    int m38;                                // +0x38
    int m3c;                                // +0x3c
    char pad40[4];
    int m44;                                // +0x44
    int m48;                                // +0x48
    int m4c;                                // +0x4c
    int m50;                                // +0x50
    void Render();
};

// @ 0x007b4a50
void ThumbnailBlitJob::Render()
{
    int mode = (*mppOwner)->mMode;
    int src = m44;
    if (mode == 1)
        src = m48;
    else if (mode == 2)
        src = m4c;

    RenderTarget* obj = GetTargetFactory()->Create(src, m50, 0xc8, 0x96, 1, 0x208, 0x15, 8);
    if (!(obj->flags & 1))
        GetTargetFactory()->Register(obj);

    LockInfo info;
    ITex* tex = obj->tex;
    if (tex->Lock(2, 0, &info)) {
        GetBlitter()->Blit(m38, m3c, (int)info.data);
        if (!(obj->flags & 1))
            GetTargetFactory()->Register(obj);
        obj->tex->Unlock(&info);
    }
}

// ===========================================================================
// cThumbnailManager
// ===========================================================================

struct Point2 {
    unsigned x;                             // +0x00
    unsigned y;                             // +0x04
};

struct Viewer;                              // SP::cViewer local image

struct FilterSetup {                        // descriptor handed to filter vtbl+0xc
    Viewer* mpViewer;                       // +0x00
    void*   m04;                            // +0x04
    void*   m08;                            // +0x08
    void*   m0c;                            // +0x0c
};

struct TerrainFilter {
    virtual void v0();                                          // +0x00 (vptr only)
    virtual void Release();                                     // slot +0x04
    virtual void v2();                                          // slot +0x08
    virtual void Setup(int a, int b, FilterSetup* s, int d);    // slot +0x0c
    int      m04;                           // +0x04 (unused by this slice)
    int      m08;                           // +0x08
    int      m0c;                           // +0x0c
    unsigned m10;                           // +0x10
    unsigned m14;                           // +0x14
    unsigned m18;                           // +0x18
    unsigned m1c;                           // +0x1c
    unsigned m20;                           // +0x20
};

struct IModelWorld;                         // interface with a slot at +0x170

struct cMWModel {
    IModelWorld* mWorld;                    // +0x00
    int          mFlags;                    // +0x04
    char         pad08[0x40 - 0x08];
    int          mRefCount;                 // +0x40
};

struct IModelWorld {
    virtual void v000(); virtual void v001(); virtual void v002(); virtual void v003();
    virtual void v004(); virtual void v005(); virtual void v006(); virtual void v007();
    virtual void v008(); virtual void v009(); virtual void v010(); virtual void v011();
    virtual void v012(); virtual void v013(); virtual void v014(); virtual void v015();
    virtual void v016(); virtual void v017(); virtual void v018(); virtual void v019();
    virtual void v020(); virtual void v021(); virtual void v022(); virtual void v023();
    virtual void v024(); virtual void v025(); virtual void v026(); virtual void v027();
    virtual void v028(); virtual void v029(); virtual void v030(); virtual void v031();
    virtual void v032(); virtual void v033(); virtual void v034(); virtual void v035();
    virtual void v036(); virtual void v037(); virtual void v038(); virtual void v039();
    virtual void v040(); virtual void v041(); virtual void v042(); virtual void v043();
    virtual void v044(); virtual void v045(); virtual void v046(); virtual void v047();
    virtual void v048(); virtual void v049(); virtual void v050(); virtual void v051();
    virtual void v052(); virtual void v053(); virtual void v054(); virtual void v055();
    virtual void v056(); virtual void v057(); virtual void v058(); virtual void v059();
    virtual void v060(); virtual void v061(); virtual void v062(); virtual void v063();
    virtual void v064(); virtual void v065(); virtual void v066(); virtual void v067();
    virtual void v068(); virtual void v069(); virtual void v070(); virtual void v071();
    virtual void v072(); virtual void v073(); virtual void v074(); virtual void v075();
    virtual void v076(); virtual void v077(); virtual void v078(); virtual void v079();
    virtual void v080(); virtual void v081(); virtual void v082(); virtual void v083();
    virtual void v084(); virtual void v085(); virtual void v086(); virtual void v087();
    virtual void v088(); virtual void v089(); virtual void v090(); virtual void v091();
    virtual void ReleaseModel(cMWModel* obj, int flag);         // +0x170
};

struct Stopwatch {
    char mData[0x18];                       // +0x2110
    Stopwatch(int a, int b);                // 0x0093a560
};

struct JobSlot {
    int mValue;                             // +0x00 (4 bytes)
    JobSlot();                              // 0x00743b50
    ~JobSlot();                             // 0x007a9610
};

struct cThumbnailManager {
    void* mpVtbl0;                          // +0x0000
    void* mpVtbl1;                          // +0x0004
    void* mpVtbl2;                          // +0x0008
    void* mp00c;                            // +0x000c
    int   m010;                             // +0x0010
    int   mIds[20];                         // +0x0014 .. +0x0060
    void* mp064;                            // +0x0064
    void* mp068;                            // +0x0068
    void* mp06c;                            // +0x006c
    void* mp070;                            // +0x0070
    void* mp074;                            // +0x0074
    char  mPad078[0x1090 - 0x078];          // +0x0078
    void* mp1090;                           // +0x1090
    int   m1094;                            // +0x1094
    int   m1098;                            // +0x1098
    int   m109c;                            // +0x109c
    int   m10a0;                            // +0x10a0
    int   m10a4;                            // +0x10a4
    int   m10a8;                            // +0x10a8
    int   m10ac;                            // +0x10ac
    int   m10b0;                            // +0x10b0
    int   m10b4;                            // +0x10b4
    int   m10b8;                            // +0x10b8
    unsigned char m10bc;                    // +0x10bc
    char  mPad10bd[3];                      // +0x10bd
    IRefCounted* mp10c0;                    // +0x10c0
    IRefCounted* mp10c4;                    // +0x10c4
    cMWModel*    mp10c8;                    // +0x10c8
    void*        mp10cc;                    // +0x10cc
    unsigned char m10d0;                    // +0x10d0
    unsigned char m10d1;                    // +0x10d1
    char  mPad10d2[2];                      // +0x10d2
    TerrainFilter* mp10d4;                  // +0x10d4
    TerrainFilter* mp10d8;                  // +0x10d8
    TerrainFilter* mp10dc;                  // +0x10dc
    Viewer*        mp10e0;                  // +0x10e0
    IRefCounted*   mp10e4;                  // +0x10e4
    IRefCounted*   mp10e8;                  // +0x10e8
    IRefCounted*   mp10ec;                  // +0x10ec
    void*          mp10f0;                  // +0x10f0
    int   m10f4;                            // +0x10f4
    int   m10f8;                            // +0x10f8
    IRefCounted* mp10fc;                    // +0x10fc
    JobSlot mAmbOccRenderJob[0x400];        // +0x1100
    JobSlot mTimelineJobs[3];               // +0x2100
    char  mPad210c[4];                      // +0x210c
    Stopwatch mStopwatch;                   // +0x2110

    void SetTerrainFilterRects(Point2* a, Point2* b, Point2* c, int d);
    void Ctor();
    void Dtor();
};

static void ReleaseSkinModel(cMWModel* obj)
{
    int rc = obj->mRefCount;
    if (rc < 2)
        obj->mWorld->ReleaseModel(obj, (obj->mFlags >> 31) & 1);
    else
        obj->mRefCount = rc - 1;
}

// @ 0x007b4b10
void cThumbnailManager::SetTerrainFilterRects(Point2* a, Point2* b, Point2* c, int d)
{
    if (!m10d1)
        return;
    FilterSetup setup;
    setup.mpViewer = mp10e0;
    setup.m04 = 0;
    setup.m08 = 0;
    setup.m0c = 0;

    mp10d4->m10 = a->x;
    mp10d4->m14 = a->y;
    mp10d4->m1c = b->x;
    mp10d4->m20 = b->y;
    mp10d4->Setup(0, 0, &setup, d);

    mp10d8->m10 = b->x;
    mp10d8->m14 = b->y;
    mp10d8->m1c = c->x;
    mp10d8->m20 = c->y;
    mp10d8->Setup(0, 0, &setup, d);

    mp10dc->m10 = c->x;
    mp10dc->m14 = c->y;
    mp10dc->m1c = a->x;
    mp10dc->m20 = a->y;
    mp10dc->Setup(0, 0, &setup, d);
}

// ---- render-target request objects (0x007b4cd0 / 0x007b4d70) ---------------
struct RtRequestA {                             // refcounted render-target request
    void*        mpVtbl;                        // +0x00
    char         pad04[0x0c];                   // +0x04
    IRefCounted* mp10;                          // +0x10
    char         pad14[8];                      // +0x14
    void*        mp1c;                          // +0x1c
    void Dtor();
};

// @ 0x007b4cd0
void RtRequestA::Dtor()
{
    mpVtbl = g_vtbl_140fedc;
    if (mp1c)
        ReleaseRc8(mp1c);
    if (mp10)
        mp10->Release();
    mpVtbl = g_vtbl_13ef094;
}

struct RtRequestB {
    void*        mpVtbl;                        // +0x00
    char         pad04[4];                      // +0x04
    void*        mp08;                          // +0x08
    IRefCounted* mp0c;                          // +0x0c
    void Dtor();
};

// @ 0x007b4d70
void RtRequestB::Dtor()
{
    mpVtbl = g_vtbl_140fee8;
    if (mp0c)
        mp0c->Release();
    if (mp08)
        ReleaseRc8(mp08);
    mpVtbl = g_vtbl_13ef094;
}

// ===========================================================================
// RawImage (0x007b4e10) - refcounted pixel buffer constructor
// ===========================================================================

extern "C" void* memcpy(void* dst, const void* src, unsigned int n);   // 0x011e0744

struct RawImage {
    void* mpVtbl;                           // +0x00
    volatile long mRefCount;                // +0x04
    int m08;                                // +0x08
    int m0c;                                // +0x0c
    int m10;                                // +0x10
    int m14;                                // +0x14
    void* mpVtbl18;                         // +0x18
    int m1c;                                // +0x1c
    int m20;                                // +0x20
    int m24;                                // +0x24
    void* mpData;                           // +0x28
    int m2c;                                // +0x2c
    int m30;                                // +0x30
    unsigned char m34;                      // +0x34
    RawImage* Ctor(int w, int h, const void* src, int a3, int a4);
};

// @ 0x007b4e10
RawImage* RawImage::Ctor(int w, int h, const void* src, int a3, int a4)
{
    mpVtbl = g_vtbl_13ebcdc;
    _InterlockedExchange(&mRefCount, 0);
    m08 = 0;
    m0c = 0;
    m10 = 0;
    m14 = 0;
    mpVtbl18 = g_vtbl_1453eac;
    m1c = w;
    m20 = h;
    m24 = -1;
    mpData = 0;
    unsigned size = (unsigned)w * (unsigned)h * 4;
    mpVtbl = g_vtbl_140fef4;
    mpVtbl18 = g_vtbl_13ebcb8;
    void* dst = operator new(size, "Graphics", 0, 0, 0, 0);
    mpData = dst;
    memcpy(dst, src, size);
    m30 = a4;
    m2c = a3;
    m34 = 1;
    return this;
}

// ===========================================================================
// cThumbnailManager ctor / dtor
// ===========================================================================

// @ 0x007b4ee0
void cThumbnailManager::Ctor()
{
    mpVtbl1 = g_vtbl_13eb384;
    mpVtbl2 = g_vtbl_13ef094;
    mp00c = 0;
    mpVtbl0 = g_vtbl_140ff20;
    mpVtbl1 = g_vtbl_140ff0c;
    mpVtbl2 = g_vtbl_140ff08;
    mIds[0] = -1; mIds[1] = -1; mIds[2] = -1; mIds[3] = -1; mIds[4] = -1;
    mIds[5] = -1; mIds[6] = -1; mIds[7] = -1; mIds[8] = -1; mIds[9] = -1;
    mIds[10] = -1; mIds[11] = -1; mIds[12] = -1; mIds[13] = -1; mIds[14] = -1;
    mIds[15] = -1; mIds[16] = -1; mIds[17] = -1; mIds[18] = -1; mIds[19] = -1;
    mp064 = 0;
    mp068 = 0;
    mp06c = 0;
    mp070 = 0;
    mp074 = 0;
    mp1090 = 0;
    m1094 = -1;
    m1098 = -1;
    m10a4 = -1;
    m10a8 = -1;
    m10ac = -1;
    m10b0 = -1;
    m10bc = 0;
    mp10c0 = 0;
    mp10c4 = 0;
    mp10c8 = 0;
    mp10cc = 0;
    m10d0 = 0;
    m10d1 = 0;
    mp10d4 = 0;
    mp10d8 = 0;
    mp10dc = 0;
    mp10e4 = 0;
    mp10e8 = 0;
    mp10ec = 0;
    mp10f0 = 0;
    m10f4 = -1;
    m10f8 = -1;
    mp10fc = 0;
    for (unsigned i = 0; i < 0x400; ++i)
        new (&mAmbOccRenderJob[i]) JobSlot();
    for (unsigned i = 0; i < 3; ++i)
        new (&mTimelineJobs[i]) JobSlot();
    new (&mStopwatch) Stopwatch(5, 0);
}

// @ 0x007b5090
void cThumbnailManager::Dtor()
{
    mpVtbl0 = g_vtbl_140ff20;
    mpVtbl1 = g_vtbl_140ff0c;
    mpVtbl2 = g_vtbl_140ff08;
    for (unsigned i = 3; i-- > 0; )
        mTimelineJobs[i].~JobSlot();
    for (unsigned i = 0x400; i-- > 0; )
        mAmbOccRenderJob[i].~JobSlot();
    if (mp10fc) mp10fc->Release();
    if (mp10ec) mp10ec->Release();
    if (mp10e8) mp10e8->Release();
    if (mp10e4) mp10e4->Release();
    if (mp10dc) mp10dc->Release();
    if (mp10d8) mp10d8->Release();
    if (mp10d4) mp10d4->Release();
    if (mp10c8) ReleaseSkinModel(mp10c8);
    if (mp10c4) mp10c4->Release();
    if (mp10c0) mp10c0->Release();
    if (mp074) ReleaseRc8(mp074);
    if (mp070) ReleaseRc8(mp070);
    if (mp06c) ReleaseRc8(mp06c);
    if (mp068) ReleaseRc8(mp068);
    if (mp064) ReleaseRc8(mp064);
    mpVtbl2 = g_vtbl_13ef094;
    mpVtbl1 = g_vtbl_13eb394;
    mpVtbl0 = g_vtbl_13eb938;
}

// ===========================================================================
// FrameBoundingBoxPalette (0x007b5320)
// ===========================================================================

struct FitViewer {
    void SetFov(float f);                   // 0x007c4b50
    void SetXForm(XForm* x);                // 0x007c40f0
    void SetViewAngleY(float a);            // 0x007c53d0
    void SetNear(float n);                  // 0x007c4ba0
    void ApplyXForm(XForm* x);              // 0x007c4d00
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

FitApp* GetApp();                           // 0x0067dd10

extern const Matrix3 g_identityBasis;       // 0x01635788
extern float g_defaultPosX;                 // 0x01635648
extern float g_defaultPosY;                 // 0x0163564c
extern float g_defaultPosZ;                 // 0x01635650

// @ 0x007b5320
void __stdcall FrameBoundingBoxPalette(const float* bounds, FitViewer* v, int target,
                                       float radiusScale, int mode, float fov)
{
    if (!v)
        return;
    FitDevice* dev = GetApp()->GetDevice();
    int prev = dev->GetCurrent();
    if (!dev->Select(target))
        return;
    v->SetFov(fov);
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

    Vector3 np = xf.pos;
    Matrix3 m2;
    m2.Assign(xf.m);
    float len = sqrtf(m2.row1.x * m2.row1.x + m2.row1.y * m2.row1.y
                      + m2.row1.z * m2.row1.z + 1e-8f);
    float inv = 1.0f / len;
    Vector3 dir;
    dir.x = m2.row1.x * inv;
    dir.y = m2.row1.y * inv;
    dir.z = m2.row1.z * inv;

    v->SetFov(fov);
    v->SetViewAngleY(50.0f);
    v->SetNear(0.01f);

    float ex = bounds[3] - bounds[0];
    float ey = bounds[4] - bounds[1];
    float ez = bounds[5] - bounds[2];
    float radius = sqrtf(ex * ex + ey * ey + ez * ez) * radiusScale;
    float cx = (bounds[0] + bounds[3]) * 0.5f;
    float cy = (bounds[1] + bounds[4]) * 0.5f;
    float cz = (bounds[2] + bounds[5]) * 0.5f;

    if (mode == 9) {
        np.x = -dir.x;
        np.y = -dir.y;
        np.z = -dir.z;
    } else {
        np.x = cx - dir.x * radius;
        np.y = cy - dir.y * radius;
        np.z = cz - dir.z * radius;
    }
    xf.flags |= 4;
    xf.rev++;
    xf.pos = np;
    v->ApplyXForm(&xf);
}
