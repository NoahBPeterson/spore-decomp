// slice s006e3100: SP::CaptureSceneViews (cubemap capture: six face cameras, one render target).
//
// Complete translation of the 3,696-byte routine.  For each of the six cube faces it
//   1. orients that face's camera (axis table + a fixed up-vector fallback cascade),
//   2. points it at a shared raster/viewport and clears it,
//   3. builds a BehaviorMessage describing the face and a fresh render pipeline object
//      (vertex-layout object assembled from the device's attribute list, plus its three
//      companion graphics objects) and submits both to the graphics device.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <intrin.h>

// ---------------------------------------------------------------- helpers
struct Vec3 { float x, y, z; };

static inline Vec3 V3(float x, float y, float z) { Vec3 v; v.x = x; v.y = y; v.z = z; return v; }
static inline Vec3 Cross(const Vec3& a, const Vec3& b)
{
    return V3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
// v * 1/sqrt(|v|^2 + 1e-8): the safe normalize used throughout (see SP::normalized_safe 0x00449c20)
static inline Vec3 NormalizeSafe(const Vec3& v)
{
    float inv = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + 1e-8f);
    return V3(v.x * inv, v.y * inv, v.z * inv);
}
static inline Vec3 Neg(const Vec3& v) { return V3(-v.x, -v.y, -v.z); }

// 4 rows of (x, y, z, unused): right, up, forward (all negated/flipped as the engine expects), position
struct Xform { float m[4][4]; };

// ---------------------------------------------------------------- engine stubs
void* operator new(size_t, const char* name, int, int, int, int);        // EA 6-arg new (0x00f473a0)
void  operator delete(void*, const char*, int, int, int, int);

struct Handle {                  // {object, id} pair returned by the device; default is {-1,-1}
    void* p; int id;
    Handle() : p((void*)-1), id(-1) {}
};

// graphics object (refcount slots 0/1: AddRef, Release)
struct cGfxObject {
    virtual int AddRef();
    virtual int Release();
};
template <class T>
struct Ref {
    T* mp;
    Ref(T* p) : mp(p) { if (mp) mp->AddRef(); }
    ~Ref() { if (mp) mp->Release(); }
    T* get() const { return mp; }
    T* operator->() const { return mp; }
};

struct cVertexLayout : cGfxObject {                                       // 0x20 bytes
    char pad[0x18];
    cVertexLayout();                                                      // 0x00760c00
    void AddElement(uint32_t a, uint32_t type, uint32_t c);               // 0x00760fd0
};
struct cRenderStateA : cGfxObject { char pad[0x18]; cRenderStateA(); };   // 0x20 bytes (ctor 0x00760c00 shared shape)
struct cRenderStateB : cGfxObject { char pad[0x18]; cRenderStateB(); };
struct cPipeline : cGfxObject {                                           // 0x140 bytes
    char pad[0x138];
    cPipeline();                                                          // 0x0076b350
    void Init(Handle* h, cVertexLayout* layout, cRenderStateA* a, cRenderStateB* b,
              int a0, int a1, int a2, int a3, int a4, int a5, int a6);    // 0x0076b460
};

// behavior message queued for the face (0x50 bytes, refcounted at +4)
struct cBehaviorMessage {
    virtual ~cBehaviorMessage();
    virtual int AddRef();
    virtual int Release();
    long mnRefCount;                // +0x04
    int mFace;                      // +0x08
    int pad0c;
    int mHandleId;                  // +0x10
    int pad14;
    void* mHandlePtr;               // +0x18
    int pad1c;
    int mParamA;                    // +0x20  (arg 9)
    int pad24;
    int mSelf;                      // +0x28  (arg 1)
    int pad2c;
    int mParamC;                    // +0x30  (arg 11)
    int pad34;
    void* mRaster;                  // +0x38
    int pad3c;
    cPipeline* mPipeline;           // +0x40
    int pad44;
    int mZero48;                    // +0x48
    int pad4c;
    cBehaviorMessage() : mZero48(0) { _InterlockedExchange(&mnRefCount, 0); }
};
struct cCaptureMessage : cBehaviorMessage {                               // vtable 0x01452a38
    virtual ~cCaptureMessage();
};

struct Attr { uint32_t a; uint32_t type; uint32_t c; };
struct Surface { char pad[0xc]; uint16_t w; uint16_t h; };

struct SubmitReq {                                                        // 0x2c bytes
    int one; int z4; char z8; int zc; int z10; uint32_t msgType; cBehaviorMessage* msg;
    void* camera; int z20; int z24; int z28;
};

// resource/target manager (FUN_0067dda0)
struct IGfxDevice {
virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual Handle* CreateTarget(Handle* out, int w, int h, int fmt, int levels, int a, int b);   // +0x10
    virtual void v5();
    virtual Surface* Lookup(Handle h);                                    // +0x18
virtual void w7(); virtual void w8(); virtual void w9(); virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15(); virtual void w16(); virtual void w17();
    virtual void SetName(Handle h, const char* name);                     // +0x48
};
// graphics service (FUN_0067dd50)
struct IGfxService {
virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25();
    virtual int GetAttrCount();                                           // +0x68
    virtual void s27();
    virtual Attr* GetAttr(int i);                                         // +0x70
    virtual void s29();
    virtual void Submit(cPipeline* p, int zero, SubmitReq* req);          // +0x78
};

IGfxService* GetGfxService();                                            // 0x0067dd50
IGfxDevice*  GetGfxDevice();                                             // 0x0067dda0
void* CreateRaster(int w, int h, int a, int b, int c);                   // SP::CreateRaster 0x00761420

struct cFaceCamera {                                                      // a capture view (thiscall members)
    void SetFarClip(float f);                                             // 0x007c4bc0
    void SetTransform(const Xform* x);                                    // 0x007c4d20
    void SetTarget(void* raster);                                         // 0x007c3cc0
    void SetViewportRect(int x, int y, int w, int h);                     // 0x007c5310
    void SetFrustum(float a, float b);                                    // 0x007c4b00
    void SetClearColor(const float* rgba);                                // 0x007c3c20
    void Func7c3ce0(int a, int b);                                        // 0x007c3ce0
    void Func7c3c50(int mode);                                            // 0x007c3c50
};

// attribute types the pipeline layout ignores
static inline bool SkipAttrType(uint32_t t)
{
    return t == 0x11 || t == 0x22 || t == 0x1a || t == 0x1f || t == 0x23 || t == 0x1d || t == 0x1e ||
           t == 0x16 || t == 3 || t == 4 || t == 5 || t == 0x12 || t == 0x13 || t == 0x21;
}

// @ 0x006e3100
void CaptureSceneViews(int self, cFaceCamera** cameras, float radius, float px, float py, float pz,
                       uint16_t size, char flip, int p9, int p10, int p11)
{
    IGfxService* service = GetGfxService();
    IGfxDevice* device = GetGfxDevice();

    Handle created;
    Handle target;
    target = *device->CreateTarget(&created, size, size, 0x16, 1, -1, 0);
    device->SetName(target, "CubemapCapture");
    Surface* surface = device->Lookup(target);
    void* raster = CreateRaster(size, size, 1, 2, 0x4b);

    float farClip = radius * 2.0f;
    float half = radius * 0.5f;

    for (int face = 0; face < 6; face++) {
        cFaceCamera* cam = cameras[face];
        cam->SetFarClip(farClip);

        Vec3 d;
        switch (face) {
        case 0: d = V3(1.0f, 0.0f, 0.0f); break;
        case 1: d = V3(-1.0f, 0.0f, 0.0f); break;
        case 2: d = V3(0.0f, 0.0f, -1.0f); break;
        case 3: d = V3(0.0f, 0.0f, 1.0f); break;
        case 4: d = V3(0.0f, 1.0f, 0.0f); break;
        case 5: d = V3(0.0f, -1.0f, 0.0f); break;
        }

        Vec3 fwd = NormalizeSafe(d);

        // side vector: d x X for the +-Z faces, d x Y for the others
        Vec3 side;
        if (d.x == 0.0f && ((d.y == 0.0f && d.z == 1.0f) || (d.y == 0.0f && d.z == -1.0f)))
            side = NormalizeSafe(Cross(d, V3(1.0f, 0.0f, 0.0f)));
        else
            side = NormalizeSafe(Cross(d, V3(0.0f, 1.0f, 0.0f)));

        // degenerate (looking along the up axis): fall back to a fixed side vector
        if (sqrtf(side.x * side.x + side.y * side.y + side.z * side.z) < 1e-06f) {
            if (d.x == 0.0f && d.y == 1.0f && d.z == 0.0f)
                side = V3(0.0f, 0.0f, -1.0f);
            else
                side = V3(0.0f, 0.0f, 1.0f);
        }

        Vec3 up = NormalizeSafe(Cross(side, fwd));
        if ((d.x == 0.0f && d.y == -1.0f && d.z == 0.0f) || (d.x == 1.0f && d.y == 0.0f && d.z == 0.0f))
            up = Neg(up);

        Vec3 right = Neg(NormalizeSafe(Cross(up, fwd)));
        if (flip)
            right = Neg(right);

        Xform xf;
        Vec3 negUp = Neg(up);
        Vec3 negFwd = Neg(fwd);
        xf.m[0][0] = negUp.x;   xf.m[0][1] = negUp.y;   xf.m[0][2] = negUp.z;
        xf.m[1][0] = right.x;   xf.m[1][1] = right.y;   xf.m[1][2] = right.z;
        xf.m[2][0] = negFwd.x;  xf.m[2][1] = negFwd.y;  xf.m[2][2] = negFwd.z;
        xf.m[3][0] = px + d.x * farClip;
        xf.m[3][1] = py + d.y * farClip;
        xf.m[3][2] = pz + d.z * farClip;

        cam->SetTransform(&xf);
        cam->SetTarget(raster);
        cam->SetViewportRect(0, 0, surface->w, surface->h);
        cam->SetFrustum(half, half);
        float clear[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        cam->SetClearColor(clear);
        cam->Func7c3ce0(p10, 0);
        cam->Func7c3c50(7);

        Ref<cCaptureMessage> msg(new("Graphics", 0, 0, 0, 0) cCaptureMessage);
        msg->mFace = face;
        msg->mHandleId = target.id;
        msg->mHandlePtr = target.p;
        msg->mParamA = p9;
        msg->mSelf = self;
        msg->mParamC = p11;
        msg->mRaster = raster;

        Ref<cVertexLayout> layout(new("Graphics", 0, 0, 0, 0) cVertexLayout);
        Ref<cRenderStateA> stateA(new("Graphics", 0, 0, 0, 0) cRenderStateA);
        Ref<cRenderStateB> stateB(new("Graphics", 0, 0, 0, 0) cRenderStateB);
        Ref<cPipeline> pipeline(new("Graphics", 0, 0, 0, 0) cPipeline);

        int count = service->GetAttrCount();
        for (int i = 0; i < count; i++) {
            Attr* attr = service->GetAttr(i);
            uint32_t type = attr->type;
            if (!SkipAttrType(type) && type <= 0x1a)
                layout->AddElement(attr->a, type, attr->c);
        }

        pipeline->Init(&target, layout.get(), stateA.get(), stateB.get(), 0, 1, 0, 0, 0, 2, 0);
        msg->mPipeline = pipeline.get();

        SubmitReq req;
        req.one = 1;
        req.z4 = 0;
        req.z8 = 0;
        req.zc = 0;
        req.z10 = 0;
        req.msgType = 0x1c9127b;
        req.msg = msg.get();
        req.camera = cam;
        req.z20 = 0;
        req.z24 = 0;
        req.z28 = 0;
        service->Submit(pipeline.get(), 0, &req);
    }
}
