// src/game/SPEngine/SPGraphicsCubeMapCapture.cpp -- migrated from slice(s) s006e51b0, s006e4210, s006e3f70, s006e3100, s006e2b50, s006e1db0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsCubeMapCapture.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/math/vpu/Vector4.h"
#include "cSPMatrix4.h"
#include "SP/cViewer.h"
#include <math.h>
#include <intrin.h>
#include <string.h>

// ---- items of slice s006e1db0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Block16 {
    int v[16];
    Block16& Set(const int* a, const int* b, const int* c, const int* d);
};
// ---- items of slice s006e1db0 end

// ---- items of slice s006e2b50 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char byte;
struct Matrix44 {
    float xAxis[4];
    float yAxis[4];
    float zAxis[4];
    float wAxis[4];
};
struct cViewer {
    Matrix44 mCameraToWorldTransform;   // +0x0
    cViewer* UpdateTransforms(float* p);
};
extern "C" double sqrt(double);
extern "C" void AddColourSample(float* colour, int n, float* dir, void* dst);
// ---- items of slice s006e2b50 end

// ---- items of slice s006e3100 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
static inline Vec3 V3(float x, float y, float z) { Vec3 v; v.x = x; v.y = y; v.z = z; return v; }
static inline Vec3 Cross(const Vec3& a, const Vec3& b)
{
    return V3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
static inline Vec3 NormalizeSafe(const Vec3& v)
{
    float inv = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + 1e-8f);
    return V3(v.x * inv, v.y * inv, v.z * inv);
}
static inline Vec3 Neg(const Vec3& v) { return V3(-v.x, -v.y, -v.z); }
struct Xform { float m[4][4]; };
void* operator new(size_t, const char* name, int, int, int, int);        // EA 6-arg new (0x00f473a0)
struct Handle {                  // {object, id} pair returned by the device; default is {-1,-1}
    void* p; int id;
    Handle() : p((void*)-1), id(-1) {}
};
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
struct IGfxDevice {
virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual Handle* CreateTarget(Handle* out, int w, int h, int fmt, int levels, int a, int b);   // +0x10
    virtual void v5();
    virtual Surface* Lookup(Handle h);                                    // +0x18
virtual void w7(); virtual void w8(); virtual void w9(); virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15(); virtual void w16(); virtual void w17();
    virtual void SetName(Handle h, const char* name);                     // +0x48
};
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
static inline bool SkipAttrType(uint32_t t)
{
    return t == 0x11 || t == 0x22 || t == 0x1a || t == 0x1f || t == 0x23 || t == 0x1d || t == 0x1e ||
           t == 0x16 || t == 3 || t == 4 || t == 5 || t == 0x12 || t == 0x13 || t == 0x21;
}
// ---- items of slice s006e3100 end

// ---- items of slice s006e3f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Matrix44_s006e_3f70 {
    float m[16];
    Matrix44_s006e_3f70& Set(const float* a, const float* b, const float* c, const float* d);
};
// ---- items of slice s006e3f70 end

// ---- items of slice s006e4210 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned size, const char* tag, int a, int b, int c, int d);   // 0x00f473a0
struct TargetHandle { unsigned a, b; };               // render-target id pair (two dwords)
struct TargetInfo { char pad[0xc]; unsigned short width, height; };   // +0xc / +0xe
struct IGraphicsDevice {                              // FUN_0067dda0
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual TargetHandle* CreateTarget(TargetHandle* out, unsigned w, unsigned h, int format,
                                       int a, int b, int c);        // +0x10 (slot 4)
    virtual void s5();
    virtual TargetInfo* GetTargetInfo(unsigned a, unsigned b);      // +0x18 (slot 6)
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void SetTargetName(unsigned a, unsigned b, const char* name);   // +0x48 (slot 18)
};
struct RenderQueueEntry { unsigned a; unsigned kind; unsigned c; };
struct MsgBase {                                      // vtbl_UI::BehaviorMessage (0x013eb90c)
    virtual void s0();
    virtual int AddRef();                             // +4
    virtual int Release();                            // +8
    long mRefCount;
    MsgBase() { _InterlockedExchange(&mRefCount, 0); }
};
struct CaptureMsgA : MsgBase {                        // 0x18 bytes
    unsigned mTarget;                                 // +8
    unsigned pad_c;
    unsigned mZero;                                   // +0x10
    unsigned pad_14;
    CaptureMsgA() { mZero = 0; }
};
struct CaptureCommand;                                // 0x24 bytes (0x0076b660 / 0x0076b720)
struct CaptureMsgB : MsgBase {                        // 0x30 bytes
    unsigned mFace;                                   // +8
    unsigned pad_c;
    unsigned mHandleB;                                // +0x10
    unsigned pad_14;
    unsigned mHandleA;                                // +0x18
    unsigned pad_1c;
    CaptureCommand* mCommand;                         // +0x20
    unsigned pad_24;
    unsigned mZero;                                   // +0x28
    unsigned pad_2c;
    CaptureMsgB() { mZero = 0; }
};
struct EffectsCollection {                            // 0x20 bytes (ctor 0x00760c00)
    EffectsCollection();                              // 0x00760c00
    virtual int AddRef();                             // +0
    virtual int Release();                            // +4
    void AddEffect(unsigned a, unsigned kind, unsigned c);   // 0x00760fd0
};
struct CaptureCommand {                               // ctor 0x0076b660 (D660)
    CaptureCommand();                                 // 0x0076b660
    virtual int AddRef();                             // +0
    virtual int Release();                            // +4
    void Init(unsigned face, unsigned target, TargetHandle* handle, EffectsCollection* fx,
              int arg8);                              // 0x0076b720 (Ctor76b720)
};
struct QueueItem {                                    // command record (0x2c bytes)
    unsigned mKind;                                   // +0 = 1
    unsigned mZero4;                                  // +4
    unsigned char mFlag;                              // +8
    unsigned mTypeId;                                 // +0xc
    CaptureMsgA* mMsgA;                               // +0x10
    unsigned mId2;                                    // +0x14
    CaptureMsgB* mMsgB;                               // +0x18
    unsigned mTarget;                                 // +0x1c
    unsigned mZero20, mZero24, mZero28;
};
struct IRenderQueue {                                 // FUN_0067dd50
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25();
    virtual int GetEntryCount();                      // +0x68 (slot 26)
    virtual void s27();
    virtual RenderQueueEntry* GetEntry(int i);        // +0x70 (slot 28)
    virtual void s29();
    virtual void Submit(CaptureCommand* cmd, int zero, QueueItem* item);   // +0x78 (slot 30)
};
struct IEffectsManager {                              // SP::EffectsManager()
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void SetTime(float a, float b);           // +0x40 (slot 16)
};
struct IRenderTarget {                                // pOut[i]
    void SetViewMatrix(const float* m);               // 0x007c4d20
    void SetViewportRect(int x, int y, int w, int h); // 0x007c5310 (cViewer_SetViewportRect)
    void Clear(const float* rgba);                    // 0x007c3c20
};
struct cViewer_s006e_4210 {                                      // stack object; only the transform is used
    float m[16];
    float* UpdateTransforms(const float* p);          // 0x006e3000 (returns this)
};
float* Matrix44Multiply(float* out, const float* lhs, const float* rhs);   // 0x006e3f70 (cdecl, returns out)
IRenderQueue*    GetRenderQueue();                    // 0x0067dd50
IGraphicsDevice* GetGraphicsDevice();                 // 0x0067dda0
IEffectsManager* EffectsManager();                    // 0x0067ddd0 (SP::EffectsManager)
template <class T> struct Ref_s006e_4210 {                       // intrusive smart pointer (AddRef on construct)
    T* p;
    explicit Ref_s006e_4210(T* q) : p(q) { if (p) p->AddRef(); }
    ~Ref_s006e_4210() { if (p) p->Release(); }
    T* operator->() const { return p; }
};
namespace SP {
void CaptureCubeMap(int* pOut, float* pPosition, float* pRotation,
                    unsigned short size, int arg5, int arg6, bool flip, int arg8);  // namespace SP
}
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
// ---- items of slice s006e4210 end

// ---- items of slice s006e51b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" __declspec(nothrow) void* __cdecl memset(void*, int, unsigned int);
extern "C" __declspec(dllimport) int __cdecl fprintf(void*, const char*, ...);
extern "C" __declspec(dllimport) void* __cdecl fopen(const char*, const char*);
extern "C" __declspec(dllimport) int __cdecl fclose(void*);
extern int   __cdecl FUN_00688cf0(int a);
extern char g_sentinel;   // 0x1667bac (shared empty-string sentinel)
#pragma function(memcpy)
void __cdecl operator delete[](void*);   // 0xf47380
void* operator new(unsigned int n, const char* name, int a, int b, int c, int d);   // 0xf473a0
struct Vec4 { float v[4]; };
struct CoeffRef { const void* p; int i; };
struct CubeFace {
    char pad[0x12];
    unsigned char face;
    void __thiscall FillSpriteTexture(void* pixels, unsigned int bytes, int zero);   // 0x11f0440
};
extern void __cdecl PrefilterCube(Vec4* coeffs, int size, int face, void* pixels, float x, float y, float z, int extra);   // 0x6e2b50
struct VObj { void** vtbl; };
extern VObj* __cdecl GetRenderer();       // 0x67dd50
extern VObj* __cdecl GetModelManager();   // 0x67dd80
struct EStr {
    char *b, *e, *c;
    EStr() { b = &g_sentinel; e = &g_sentinel; c = &g_sentinel + 1; }
    ~EStr()
    {
        if (c - b > 1 && b) {
            operator delete[](b);
        }
    }
};
extern EStr __cdecl ConvertToString8(int v);                               // 0x93c440
extern int __cdecl StrSprintf(EStr* self, const char* fmt, ...);           // 0x472fe0
// ---- items of slice s006e51b0 end

// @ 0x006e2ae0
Block16& Block16::Set(const int* a, const int* b, const int* c, const int* d)
{
    v[0] = a[0]; v[1] = a[1]; v[2] = a[2]; v[3] = a[3];
    v[4] = b[0]; v[5] = b[1]; v[6] = b[2]; v[7] = b[3];
    v[8] = c[0]; v[9] = c[1]; v[10] = c[2]; v[11] = c[3];
    v[12] = d[0]; v[13] = d[1]; v[14] = d[2]; v[15] = d[3];
    return *this;
}

// @ 0x006e2b50
namespace SP {
void PrefilterCube(rw::math::vpu::Vector4 * dst, int size, int face, unsigned char const * pixels, float px, float py, float pz, bool flag)
{
    int pixels_v = (int)pixels;
    int y = 0;
    if (0 < size) {
        float half = (float)size * 0.5f;
        byte* row = (byte*)(pixels_v + 2);
        do {
            float fy = ((float)y - half) / half;
            float fy2 = fy * fy;
            int x = 0;
            byte* p = row;
            do {
                float fx = ((float)x - half) / half;
                float fx2 = fx * fx;
                float base = fx2 + fy2 + 1.0f;
                // The original writes the direction only for faces 0..5; any other face reads
                // the untouched stack slots (undefined in C, 0xCC under the harness).
                float dir[4];
                if (face == 0 || face == 2) {
                    float n = (float)(1.0 / sqrt((double)base));
                    dir[1] = n;
                    dir[0] = n * fy;
                    dir[2] = n * fx;
                    if (face == 2) { dir[1] = -dir[1]; dir[0] = -dir[0]; }
                } else if (face == 1 || face == 3) {
                    float n = (float)(1.0 / sqrt((double)base));
                    dir[0] = n;
                    dir[1] = -(n * fy);
                    dir[2] = n * fx;
                    if (face == 3) { dir[0] = -dir[0]; dir[1] = -dir[1]; }
                } else if (face == 4 || face == 5) {
                    float n = (float)(1.0 / sqrt((double)base));
                    dir[0] = n * fy;
                    dir[1] = -(n * fx);
                    dir[2] = n;
                    if (face == 5) { dir[0] = -dir[0]; dir[1] = -dir[1]; }
                }
                float n0 = dir[1];
                float n1 = dir[0];
                float n2 = dir[2];
                float len3 = (n0 * n0 + n1 * n1) + 1.0f;
                float c2 = (float)p[-2] * 0.003921569f;
                float c1 = (float)p[-1] * 0.003921569f;
                float c0 = (float)*p * 0.003921569f;
                float ca = (float)p[1] * 0.003921569f;
                float wt = 4.0f / (((len3 * len3) / (float)sqrt((double)len3)) *
                                   (float)(size * size));
                if (flag != '\0') {
                    float dx = n1 - px, dy = n2 - py, dz = n0 - pz;
                    float d = (float)sqrt((double)(dx * dx + (dy * dy + dz * dz)));
                    if (d < 1.0f) {
                        float t = 1.0f - d;
                        c0 = c0 + t;
                        c1 = c1 + t;
                        c2 = c2 + t;
                        ca = ca + t;
                    }
                }
                float colour[5];
                colour[0] = wt * c0;
                colour[1] = wt * c1;
                colour[2] = wt * c2;
                colour[3] = wt * ca;
                colour[4] = 0.0f;
                AddColourSample(colour, 5, dir, dst);
                x = x + 1;
                p = p + 1;
            } while (x < size);
            row = row + size;
            y = y + 1;
        } while (y < size);
    }
}
}  // namespace SP

// @ 0x006e3000
// Retail fills a stack temporary with the 12 axis components and then copies the whole 4x4 into
// the viewer, so the w lanes of the viewer get whatever the temporary's w lanes hold -- they are
// never written (the copy at 0x006e3040 loads the untouched stack slot). EAX holds `this`.
cViewer* cViewer::UpdateTransforms(float* p)
{
    Matrix44 m;
    m.xAxis[0] = p[0];
    m.xAxis[1] = p[1];
    m.xAxis[2] = p[2];
    m.yAxis[0] = p[3];
    m.yAxis[1] = p[4];
    m.yAxis[2] = p[5];
    m.zAxis[0] = p[6];
    m.zAxis[1] = p[7];
    m.zAxis[2] = p[8];
    m.wAxis[0] = p[9];
    m.wAxis[1] = p[10];
    m.wAxis[2] = p[11];
    mCameraToWorldTransform = m;
    return this;
}

// @ 0x006e3100
void CaptureSceneViews(int self, cFaceCamera** cameras, float radius, float px, float py, float pz, uint16_t size, char flip, int p9, int p10, int p11)
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

// @ 0x006e3f70
float* Matrix44Multiply(float* out, const float* lhs, const float* rhs)
{
    // The w column (element 3 of each row) is intentionally left unset, exactly as
    // retail does: only 12 of the 16 dwords are computed before the Set helper
    // copies four 4-dword rows into the destination.
    float r0[4];
    float r1[4];
    float r2[4];
    float r3[4];
    float f1 = lhs[0xc];
    float f2 = rhs[1];
    float f3 = lhs[0xd];
    float f4 = *rhs;
    float f5 = lhs[0xe];
    r3[0] = rhs[0xc] + (rhs[8] * f5 + (rhs[4] * f3 + f1 * f4));
    r3[1] = rhs[0xd] + (rhs[9] * f5 + (rhs[5] * f3 + f2 * f1));
    r3[2] = rhs[0xe] + (rhs[10] * f5 + (rhs[6] * f3 + rhs[2] * f1));
    float f6 = lhs[8];
    float f7 = lhs[9];
    float f8 = lhs[10];
    r2[1] = rhs[9] * f8 + (rhs[5] * f7 + f6 * f2);
    r2[0] = f8 * rhs[8] + (f7 * rhs[4] + f6 * f4);
    r2[2] = rhs[10] * f8 + (rhs[6] * f7 + f6 * rhs[2]);
    float f9 = lhs[4];
    float f10 = lhs[5];
    float f11 = lhs[6];
    r1[0] = rhs[8] * f11 + (rhs[4] * f10 + f9 * f4);
    r1[1] = rhs[9] * f11 + (rhs[5] * f10 + f9 * f2);
    r1[2] = rhs[10] * f11 + (rhs[6] * f10 + f9 * rhs[2]);
    float f12 = lhs[0];
    float f13 = lhs[1];
    float f14 = lhs[2];
    r0[0] = f14 * rhs[8] + (f13 * rhs[4] + f12 * f4);
    r0[1] = rhs[9] * f14 + (rhs[5] * f13 + f12 * f2);
    r0[2] = rhs[10] * f14 + (rhs[6] * f13 + f12 * rhs[2]);
    ((Matrix44_s006e_3f70*)out)->Set(r0, r1, r2, r3);
    return out;
}

// @ 0x006e4210
void SP::CaptureCubeMap(int* pOut, float* pPosition, float* pRotation, unsigned short size, int arg5, int arg6, bool flip, int arg8)
{
    IRenderQueue* pQueue = GetRenderQueue();
    IGraphicsDevice* pDevice = GetGraphicsDevice();

    unsigned hB = (unsigned)-1;
    unsigned hA = (unsigned)-1;
    TargetHandle tmpHandle;
    TargetHandle* ph = pDevice->CreateTarget(&tmpHandle, size, size, 0x16, 1, -1, 0);
    hA = ph->a;
    hB = ph->b;
    pDevice->SetTargetName(ph->a, ph->b, "CubemapCapture");
    TargetInfo* pInfo = pDevice->GetTargetInfo(hA, hB);
    TargetHandle handle;
    handle.a = hA;
    handle.b = hB;

    for (int face = 0; face < 6; face++) {
        float a, b, c;                                // face direction
        switch (face) {
        case 0: a = 1.0f;  b = 0.0f;  c = 0.0f;  break;
        case 1: a = -1.0f; b = 0.0f;  c = 0.0f;  break;
        case 2: a = 0.0f;  b = 0.0f;  c = 1.0f;  break;
        case 3: a = 0.0f;  b = 0.0f;  c = -1.0f; break;
        case 4: a = 0.0f;  b = 1.0f;  c = 0.0f;  break;
        case 5: a = 0.0f;  b = -1.0f; c = 0.0f;  break;
        }

        // normalized face direction F
        float s = 1.0f / sqrtf(((c * c + b * b) + a * a) + 1e-08f);
        float Fx = s * a;
        float Fy = s * b;
        float Fz = s * c;

        // U = normalize(dir x ref)
        float ux, uy, uz;
        if (a == 0.0f && ((b == 0.0f && c == 1.0f) || (b == 0.0f && c == -1.0f))) {
            float t0 = b * 0.0f - c * 0.0f;
            float t1 = c - a * 0.0f;
            float t2 = a * 0.0f - b;
            float k = 1.0f / sqrtf(((t0 * t0 + t1 * t1) + t2 * t2) + 1e-08f);
            ux = k * t0; uy = k * t1; uz = k * t2;
        } else {
            float t0 = b * 0.0f - c;
            float t1 = c * 0.0f - a * 0.0f;
            float t2 = a - b * 0.0f;
            float k = 1.0f / sqrtf(((t0 * t0 + t1 * t1) + t2 * t2) + 1e-08f);
            ux = k * t0; uy = k * t1; uz = k * t2;
        }
        if (sqrtf((uy * uy + uz * uz) + ux * ux) < 1e-06f) {
            if (a == 0.0f && b == 1.0f && c == 0.0f) {
                ux = 0.0f; uy = 0.0f; uz = -1.0f;
            } else {
                ux = 0.0f; uy = 0.0f; uz = 1.0f;
            }
        }

        // W = normalize(U x F) (negated for the Y-axis-parallel faces)
        float wx, wy, wz;
        {
            float t0 = Fz * uy - Fy * uz;
            float t1 = Fx * uz - ux * Fz;
            float t2 = ux * Fy - Fx * uy;
            float k = 1.0f / sqrtf(((t0 * t0 + t1 * t1) + t2 * t2) + 1e-08f);
            wx = k * t0; wy = k * t1; wz = k * t2;
            if ((a == 0.0f && b == -1.0f && c == 0.0f) || (a == 1.0f && b == 0.0f && c == 0.0f)) {
                wx = -wx; wy = -wy; wz = -wz;
            }
        }

        // V = normalize(W x F), up = -V (or +V when flipping)
        float upx, upy, upz;
        {
            float t0 = Fz * wy - Fy * wz;
            float t1 = Fx * wz - wx * Fz;
            float t2 = wx * Fy - Fx * wy;
            float k = 1.0f / sqrtf(((t0 * t0 + t1 * t1) + t2 * t2) + 1e-08f);
            upx = -(k * t0); upy = -(k * t1); upz = -(k * t2);
            if (flip) {
                upx = -upx; upy = -upy; upz = -upz;
            }
        }

        float M[16];                                  // view matrix; the w column is left unset
        M[0] = -wx;  M[1] = -wy;  M[2] = -wz;
        M[4] = upx;  M[5] = upy;  M[6] = upz;
        M[8] = -Fx;  M[9] = -Fy;  M[10] = -Fz;
        M[12] = pPosition[0];
        M[13] = pPosition[1];
        M[14] = pPosition[2];

        // rotation matrix from the quaternion (x, y, z, w)
        float qx = pRotation[0], qy = pRotation[1], qz = pRotation[2], qw = pRotation[3];
        float yy = qy * qy, zz = qz * qz, xy = qy * qx, xz = qz * qx, zy = qz * qy;
        float wx_ = qw * qx, wy_ = qw * qy, wz_ = qw * qz, xx = qx * qx;
        float R[16];
        R[0] = 1.0f - (yy + zz) * 2.0f;
        R[1] = (xy + wz_) * 2.0f;
        R[2] = (xz - wy_) * 2.0f;
        R[3] = (xy - wz_) * 2.0f;
        R[4] = 1.0f - (xx + zz) * 2.0f;
        R[5] = (zy + wx_) * 2.0f;
        R[6] = (xz + wy_) * 2.0f;
        R[7] = (zy - wx_) * 2.0f;
        R[8] = 1.0f - (xx + yy) * 2.0f;
        R[9] = 0.0f; R[10] = 0.0f; R[11] = 0.0f;

        cViewer_s006e_4210 viewer;
        float* pX = viewer.UpdateTransforms(R);
        float* pM = Matrix44Multiply(R, M, pX);
        memcpy(M, pM, 64);

        IRenderTarget* pTarget = (IRenderTarget*)pOut[face];
        pTarget->SetViewMatrix(M);
        pTarget->SetViewportRect(0, 0, pInfo->width, pInfo->height);
        float clear[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        pTarget->Clear(clear);

        Ref_s006e_4210<CaptureMsgA> msgA(new("Graphics", 0, 0, 0, 0) CaptureMsgA);
        msgA->mTarget = (unsigned)pOut[face];

        Ref_s006e_4210<CaptureMsgB> msgB(new("Graphics", 0, 0, 0, 0) CaptureMsgB);
        msgB->mFace = face;
        msgB->mHandleB = hB;
        msgB->mHandleA = hA;

        Ref_s006e_4210<EffectsCollection> fx(new("Graphics", 0, 0, 0, 0) EffectsCollection);
        EffectsManager()->SetTime(0.0f, 0.0f);

        int n = pQueue->GetEntryCount();
        for (int k = 0; k < n; k++) {
            RenderQueueEntry* e = pQueue->GetEntry(k);
            unsigned kind = e->kind;
            if (kind != 0x11 && kind != 0x22 && kind != 0x1a &&
                kind != 0x1f && kind != 0x23 && kind != 0x1e) {
                fx.p->AddEffect(e->a, kind, e->c);
            }
        }

        Ref_s006e_4210<CaptureCommand> cmd(new("Graphics", 0, 0, 0, 0) CaptureCommand);
        cmd.p->Init(face, pOut[face], &handle, fx.p, arg8);
        msgB->mCommand = cmd.p;

        QueueItem item;
        item.mZero4 = 0;
        item.mZero20 = 0; item.mZero24 = 0; item.mZero28 = 0;
        item.mFlag = 0;
        item.mTarget = (unsigned)pOut[face];
        item.mKind = 1;
        item.mTypeId = 0x12d74a2;
        item.mMsgA = msgA.p;
        item.mId2 = 0x1c91276;
        item.mMsgB = msgB.p;
        pQueue->Submit(cmd.p, 0, &item);
    }
}

// @ 0x006e51b0
void SP_SHFromCubeMap(CubeFace* tex, int size, char dump, const char* name, int extra, float x, float y, float z)
{
    static const int faceMap[6] = { 5, 1, 4, 0, 3, 2 };
    __declspec(align(16)) Vec4 coeffs[25];
    memset(coeffs, 0, sizeof(coeffs));

    // The original sums the squares on the x87 stack (double precision) before fsqrt and
    // rounds only the root to float; the double arithmetic here reproduces that.
    float root = (float)sqrt((double)x * x + ((double)y * y + (double)z * z) + (double)1e-08f);
    float inv = 1.0f / root;
    x = inv * x;
    y = y * inv;
    z = z * inv;

    if (tex) {
        unsigned int bytes = size * size * 4;
        for (int f = 0; f < 6; ++f) {
            void* pix = operator new(bytes, "Graphics", 0, 0, 0, 0);
            tex->face = (unsigned char)faceMap[f];
            tex->FillSpriteTexture(pix, bytes, 0);
            PrefilterCube(coeffs, size, f, pix, x, y, z, extra);
            if (pix) {
                operator delete[](pix);
            }
        }
    }

    VObj* rr = GetRenderer();
    ((void(__fastcall*)(VObj*, int, int))rr->vtbl[0x58 / 4])(rr, 0, 0xd);
    VObj* mm = GetModelManager();
    VObj* sub = ((VObj*(__fastcall*)(VObj*, int))mm->vtbl[0x20 / 4])(mm, 0);
    ((void(__fastcall*)(VObj*, int, int))sub->vtbl[0x144 / 4])(sub, 0, 0);

    if (dump) {
        EStr dir = ConvertToString8(FUN_00688cf0(-1));
        EStr path;
        StrSprintf(&path, "%s%s.txt", dir.b, name);
        void* f = fopen(path.b, "w");
        if (f) {
            fprintf(f, "\n         Lighting Coefficients\n\n");
            fprintf(f, "(l,m)       RED        GREEN     BLUE\n");
            int running = 0;
            int m0 = 0;
            int l = 0;
            do {
                int l1 = l + 1;
                if (m0 < l1) {
                    const Vec4* row = &coeffs[running];
                    running += l1 - m0;
                    for (int m = m0; m < l1; ++m, ++row) {
                        CoeffRef r0 = { row, 0 };
                        CoeffRef r1 = { row, 1 };
                        CoeffRef r2 = { row, 2 };
                        fprintf(f, "  setc ct_%d%d (%9.6f, %9.6f, %9.6f)\n", l, m + l, r0, r1, r2);
                    }
                }
                m0--;
                l = l1;
            } while (m0 > -5);
            fclose(f);
        }
    }
}
