// src/game/SPEngine/SPGraphicsViewer.cpp -- migrated from slice(s) s007c4be0, s007c3ba0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsViewer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cViewer.h"
#include "cSPMatrix4.h"

// unnamed retail callees and globals (address in the comment)
extern float g_153c7a8;
extern float g_1635db8, g_1635dbc, g_1635dc0, g_1635dc4;
extern float g_10000f;
extern void g_FUN_007c4940_body();
#include <math.h>
#include "SP/cShaderDataRenderType.h"
#include "rw/core/arena/Arena.h"

// ---- items of slice s007c3ba0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec4 { float x, y, z, w; };
struct Matrix44 {
    Vec4 xAxis, yAxis, zAxis, wAxis;    // +0x00,+0x10,+0x20,+0x30
    void FUN_007c3da0(float* dst);
};
struct Camera {
    char pad0[0x54];
    float f54, f58;                 // +0x54,+0x58
    float f5c, f60;                 // +0x5c,+0x60 (width,height)
    float f64, f68;                 // +0x64,+0x68 (inverse)
    int   n6c;                      // +0x6c (projection type)
    float f70, f74;                 // +0x70,+0x74
    int   vpX, vpY, vpW, vpH;       // +0x78,+0x7c,+0x80,+0x84 (viewport)
    int   f88, f8c;                 // +0x88,+0x8c
    void SetClear(void* color, int flags);
};
struct cViewer {
    Matrix44 mCameraToWorldTransform;      // +0x00
    Matrix44 mWorldToCameraTransform;      // +0x40
    Matrix44 mCameraToClipTransform;       // +0x80
    Matrix44 mWorldToClipTransform;        // +0xc0
    Matrix44 mClipToWorldTransform;        // +0x100
    float    mClearColor[4];               // +0x140
    int      mRenderType;                  // +0x150
    int      mRenderTypeVariation;         // +0x154
    int      mShaderDataRT;                // +0x158
    float    mMaterialLODs[4];             // +0x15c
    unsigned char mTileRender;             // +0x16c
    char pad1[3];
    Camera*  mCamera;                      // +0x170

    bool   FUN_007c3ba0();
    void   FUN_007c3c50(unsigned char);
    float  FUN_007c3c90();
    float  FUN_007c3ca0();
    void   GetCameraLocationInfo(float*, float*, float*, float*);
    cViewer* FUN_007c3f70();
    void   FUN_007c4000();
    void   FUN_007c4010(unsigned*);
    float  FUN_007c4050();
    float  FUN_007c40a0();
    void   FUN_007c40c0(float*, float*);
    float  FUN_007c40e0();
    void   FUN_007c4a60(unsigned short*);
    void   FUN_007c4ad0(float, float);
    void   FUN_007c4b00(float, float);
    void   FUN_007c4b50(float);
    void   FUN_007c4ba0(float);
    void   FUN_007c4bc0(float);
    __declspec(noinline) void FUN_007c4940();   // recompute derived transforms
};
extern float g_153c7a8;
extern float g_1635db8, g_1635dbc, g_1635dc0, g_1635dc4;
extern float g_10000f;
extern void g_FUN_007c4940_body();
// ---- items of slice s007c3ba0 end

// ---- items of slice s007c4be0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* FUN_00761380();                 // default raster factory / init
extern float g_identityMatrix[16];           // 0x1635fa0
extern void* g_defaultCameraRaster;          // 0x15d0838
extern void* g_defaultZBufferRaster;         // 0x15d083c
extern float g_tanScaleA;                    // 0x153c7a8
extern float g_tanScaleB;                    // 0x1401c04
extern float g_aspectEps;                    // 0x153c98c
extern float g_defaultFov;                   // 0x1410350
extern "C" void* EANew(int size, const char* name, int, int, int, int);  // 0xf473a0
extern "C" float tanf(float);                                            // CRT
extern "C" void  DrawShader(int cmd, void* data, int changed);           // 0x777ae0
extern "C" void  FUN_011f38f0(int a, void* b);                           // 0x11f38f0
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
struct D3DVIEWPORT9 { u32 X, Y, Width, Height; float MinZ, MaxZ; };
struct rwCamera {
    float m_transform[16];       // +0x00  Matrix44Affine
    void* m_raster[4];           // +0x40
    void* m_zbuffer;             // +0x50
    float m_viewOffset[2];       // +0x54
    float m_viewWindow[2];       // +0x5c
    float m_recipViewWindow[2];  // +0x64
    int   m_projectionType;      // +0x6c
    float m_nearPlane;           // +0x70
    float m_farPlane;            // +0x74
    D3DVIEWPORT9 m_viewport;     // +0x78
    void* m_window;              // +0x90
    u32   m_stencilClear;        // +0x94

    void  AssignTo(void* out);        // 0x7779e0
    int   Check();                    // 0x11f3f20
    void  SetTexture(void* t);        // 0x7c3b70
    void  SetSize(int x, int y, int w, int h);  // 0x76d7d0
    void  GetViewport(void* out);     // 0x7c4010
};
struct cViewer_s007c_4be0 {
    float mCameraToWorld[16];    // +0x00
    float mWorldToCamera[16];    // +0x40
    float mCameraToClip[16];     // +0x80
    float mWorldToClip[16];      // +0xc0
    float mClipToWorld[16];      // +0x100
    u8    mClearColor[16];       // +0x140
    int   mRenderType;           // +0x150
    int   mRenderTypeVariation;  // +0x154
    void* mShaderDataRT;         // +0x158
    float mMaterialLODs[4];      // +0x15c
    bool  mTileRender;           // +0x16c
    u8    pad16d[3];
    rwCamera* mCamera;           // +0x170

    void UpdateTransforms();                 // 0x7c4940 (extern)
    void SetViewportRect(u16* r);            // 0x7c4a60 (extern)
    void SetAspect(float a);                 // 0x7c4b50 (extern)
    int  BuildTransforms();                  // 0x7c43e0 (extern)

    void SetRaster(int* handle, bool setViewport);
    void SetCameraToWorld(float* m);
    void SetBasis(void* basis);
    void SetCameraToWorldFromBasis(float* p);
    bool Init(bool windowed);  // 0x004b8c10 (cViewer::Init)
    bool Update();
    bool Copy(cViewer_s007c_4be0* src, bool a, bool b);  // 0x007c50b0 (cViewer::Copy)
    void CopyFrom(cViewer_s007c_4be0* src);
    void SetViewportRectArgs(u16 x, u16 y, u16 w, u16 h);
    void SetViewAngle(float a);
    void SetViewAngleY(float a);
    void SetViewWindow(float x, float y);
};
struct Renderer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual int  v18(int a, int b);
    virtual void v1c();
    virtual void v20(int a, int b, int* out);   // (handle[0], handle[1], &rect): the original pushes rect first
};
extern Renderer* GetRenderer();          // 0x67dda0
struct Basis3 { void Build(void* owner); };  // 0x6b9440
extern u8    g_forceAspect;                  // 0x153c988
struct cShaderDataRenderType { u8 mType; u8 pad[3]; int mVariation; };
// ---- items of slice s007c4be0 end

// @ 0x007c3d30
void SP::cViewer::GetCameraLocationInfo(cSPVector3 * w, cSPVector3 * y, cSPVector3 * z, cSPVector3 * x) const
{
    if (w != 0) {
        int* d = (int*)w; const int* s = (const int*)&mCameraToWorldTransform.wAxis;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2];
    }
    if (y != 0) {
        int* d = (int*)y; const int* s = (const int*)&mCameraToWorldTransform.yAxis;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2];
    }
    if (z != 0) {
        int* d = (int*)z; const int* s = (const int*)&mCameraToWorldTransform.zAxis;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2];
    }
    if (x != 0) {
        int* d = (int*)x; const int* s = (const int*)&mCameraToWorldTransform.xAxis;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2];
    }
}


// @ 0x007c3da0
void Matrix44::FUN_007c3da0(float* dst)
{
    int* d = (int*)dst;
    const int* s = (const int*)this;
    d[0] = s[0]; d[1] = s[1]; d[2] = s[2];
    d[3] = s[4]; d[4] = s[5]; d[5] = s[6];
    d += 6; s += 8;
    d[0] = s[0]; d[1] = s[1]; d[2] = s[2];
}


// @ 0x007c3de0
void FUN_007c3de0(void* a, void* b)
{ (void)a; (void)b; }


// @ 0x007c3f70
cViewer* cViewer::FUN_007c3f70()
{
    mClearColor[0] = g_1635db8;
    mClearColor[1] = g_1635dbc;
    mClearColor[2] = g_1635dc0;
    mClearColor[3] = g_1635dc4;
    float lod = g_10000f;
    mRenderType = 0;
    mRenderTypeVariation = 0;
    mShaderDataRT = 0;
    mMaterialLODs[0] = lod;
    mMaterialLODs[1] = lod;
    mMaterialLODs[2] = lod;
    mMaterialLODs[3] = lod;
    mTileRender = 1;
    mCamera = 0;
    return this;
}


// @ 0x007c4000
void cViewer::FUN_007c4000()
{
    if (mCamera != 0)
        FUN_007c3ba0();
}


// @ 0x007c4010
void cViewer::FUN_007c4010(unsigned* out)
{
    Camera* c = mCamera;
    unsigned short x = (unsigned short)c->vpX;
    unsigned short y = (unsigned short)c->vpY;
    unsigned short w = (unsigned short)c->vpW;
    unsigned short h = (unsigned short)c->vpH;
    out[2] = (unsigned)w + (unsigned)x;
    out[1] = (unsigned)y;
    out[0] = (unsigned)x;
    out[3] = (unsigned)h + (unsigned)y;
}


// @ 0x007c4050
float cViewer::FUN_007c4050()
{
    float a = mCamera->f60;
    if (mCamera->f5c != a)
        a = a * 1.3333334f;
    return (360.0f / g_153c7a8) * atan2f(a, 1.0f);
}


// @ 0x007c40a0
float cViewer::FUN_007c40a0()
{
    return (360.0f / g_153c7a8) * atan2f(mCamera->f60, 1.0f);
}


// @ 0x007c40c0
void cViewer::FUN_007c40c0(float* a, float* b)
{
    *a = mCamera->f5c;
    *b = mCamera->f60;
}


// @ 0x007c40e0
float cViewer::FUN_007c40e0()
{
    return mCamera->f5c / mCamera->f60;
}


// @ 0x007c40f0
void FUN_007c40f0(void* a, void* b)
{ (void)a; (void)b; }


// @ 0x007c4180
void FUN_007c4180(void* a, void* b, void* c)
{ (void)a; (void)b; (void)c; }


// @ 0x007c42a0
void FUN_007c42a0(void* a, void* b)
{ (void)a; (void)b; }


// @ 0x007c43e0
void FUN_007c43e0(void* a)
{ (void)a; }


// @ 0x007c4510
void FUN_007c4510(void* a)
{ (void)a; }


// @ 0x007c46f0
void FUN_007c46f0(void* a, void* b, void* c)
{ (void)a; (void)b; (void)c; }


// @ 0x007c4730
void FUN_007c4730(void* a)
{ (void)a; }


// @ 0x007c4900
void FUN_007c4900(void* a, void* b, void* c)
{ (void)a; (void)b; (void)c; }


// @ 0x007c4940
__declspec(noinline) void cViewer::FUN_007c4940()
{ g_FUN_007c4940_body(); }


// @ 0x007c4a60
void cViewer::FUN_007c4a60(unsigned short* p)
{
    unsigned short y  = p[2];
    unsigned short h  = p[6];
    unsigned short x  = p[0];
    unsigned short wv = p[4];
    Camera* c = mCamera;
    c->vpY = (unsigned)y;
    c->vpW = (unsigned)(unsigned short)(wv - x);
    c->f88 = 0;
    c->vpX = (unsigned)x;
    c->vpH = (unsigned)(unsigned short)(h - y);
    c->f8c = 0x3f800000;
    FUN_007c4940();
}


// @ 0x007c4ad0
void cViewer::FUN_007c4ad0(float a, float b)
{
    Camera* c = mCamera;
    c->f54 = a;
    c->f58 = b;
    FUN_007c4940();
}


// @ 0x007c4b00
void cViewer::FUN_007c4b00(float a, float b)
{
    Camera* c = mCamera;
    c->f5c = a;
    c->f60 = b;
    c->f64 = 1.0f / a;
    c->f68 = 1.0f / b;
    FUN_007c4940();
}


// @ 0x007c4b50
void cViewer::FUN_007c4b50(float a)
{
    Camera* c = mCamera;
    float h = c->f60;
    float w = h * a;
    float invW = 1.0f / w;
    float invH = 1.0f / h;
    c->f5c = w;
    c->f60 = h;
    c->f64 = invW;
    c->f68 = invH;
    FUN_007c4940();
}


// @ 0x007c4ba0
void cViewer::FUN_007c4ba0(float a)
{ Camera* c = mCamera; c->f70 = a; FUN_007c4940(); }


// @ 0x007c4bc0
void cViewer::FUN_007c4bc0(float a)
{ Camera* c = mCamera; c->f74 = a; FUN_007c4940(); }

// @ 0x007c4be0
__declspec(noinline) void cViewer_s007c_4be0::SetRaster(int* handle, bool setViewport)
{
    Renderer* r = GetRenderer();
    int v = r->v18(handle[0], handle[1]);
    mCamera->m_raster[0] = (void*)v;
    if (setViewport) {
        int rect[4];
        Renderer* r2 = GetRenderer();
        r2->v20(handle[0], handle[1], rect);
        SetViewportRect((u16*)rect);
    }
}

// @ 0x007c4c40
__declspec(noinline) void cViewer_s007c_4be0::SetCameraToWorld(float* m)
{
    for (int i = 0; i < 16; i++) mCameraToWorld[i] = m[i];
    rwCamera* cam = mCamera;
    float* d = cam->m_transform;
    // SIMD 3x3 transpose with sign flip on row 0 (see disassembly).
    d[0] = -m[0]; d[1] = -m[1]; d[2] = -m[2]; d[3] = -m[0];
    d[4] =  m[8]; d[5] =  m[9]; d[6] =  m[10]; d[7] =  m[8];
    d[8] =  m[4]; d[9] =  m[5]; d[10] = m[6]; d[11] = m[4];
    d[12] = m[12]; d[13] = m[13]; d[14] = m[14]; d[15] = m[12];
    UpdateTransforms();
}

// @ 0x007c4d00
__declspec(noinline) void cViewer_s007c_4be0::SetBasis(void* basis)
{
    ((Basis3*)basis)->Build(this);
    SetCameraToWorld(mCameraToWorld);
}

// @ 0x007c4d20
__declspec(noinline) void cViewer_s007c_4be0::SetCameraToWorldFromBasis(float* p)
{
    float m[16];
    m[0] = -p[0]; m[1] = -p[1]; m[2] = -p[2]; m[3] = 0.0f;
    m[4] =  p[8]; m[5] =  p[9]; m[6] =  p[10]; m[7] = 0.0f;
    m[8] =  p[4]; m[9] =  p[5]; m[10] = p[6]; m[11] = 0.0f;
    m[12] = p[12]; m[13] = p[13]; m[14] = p[14]; m[15] = 1.0f;
    SetCameraToWorld(m);
}

// @ 0x007c4dd0
__declspec(noinline) bool cViewer_s007c_4be0::Init(bool windowed)
{
    if (mCamera != 0) return false;
    mCamera = (rwCamera*)FUN_00761380();
    if (mCamera == 0) return false;
    if (mShaderDataRT == 0) {
        mShaderDataRT = EANew(8, "Graphics", 0, 0, 0, 0);
        ((int*)mShaderDataRT)[1] = -1;
        *(u8*)mShaderDataRT = 0xff;
    }

    rwCamera* cam = mCamera;
    cam->m_nearPlane = 1.0f;
    cam->m_farPlane = 1000.0f;

    rwCamera* def = (rwCamera*)g_defaultCameraRaster;
    u16 w = *(u16*)((char*)def + 0x0c);
    u16 h = *(u16*)((char*)def + 0x0e);
    cam->m_viewport.X = 0;
    cam->m_viewport.Y = 0;
    cam->m_viewport.Width = w;
    cam->m_viewport.Height = h;
    cam->m_viewport.MinZ = 0.0f;
    cam->m_viewport.MaxZ = 1.0f;

    float* d = cam->m_transform;
    d[0]=1.0f; d[1]=0; d[2]=0; d[3]=0;
    d[4]=0; d[5]=1.0f; d[6]=0; d[7]=0;
    d[8]=0; d[9]=0; d[10]=1.0f; d[11]=0;
    d[12]=0; d[13]=0; d[14]=0; d[15]=0;

    for (int i = 0; i < 16; i++) mCameraToWorld[i] = g_identityMatrix[i];

    cam->m_raster[0] = g_defaultCameraRaster;
    cam->m_zbuffer   = g_defaultZBufferRaster;

    if (!windowed) {
        cam->m_projectionType = 1;
        float t = tanf(g_tanScaleA * g_tanScaleB * g_defaultFov);
        cam->m_viewWindow[1] = t;
        float a = ((float)w / (float)h) * t;
        cam->m_viewWindow[0] = a;
        cam->m_recipViewWindow[0] = 1.0f / a;
        cam->m_recipViewWindow[1] = 1.0f / t;
    } else {
        cam->m_projectionType = 2;
        cam->m_viewWindow[0] = 1.0f;
        cam->m_viewWindow[1] = 1.0f;
        cam->m_recipViewWindow[1] = 1.0f;
        cam->m_recipViewWindow[0] = 1.0f;
    }
    UpdateTransforms();
    return true;
}

// @ 0x007c4fd0
__declspec(noinline) bool cViewer_s007c_4be0::Update()
{
    rwCamera* cam = mCamera;
    if (cam->m_raster[0] == 0) return false;

    float aspect = (float)cam->m_viewport.Width / (float)cam->m_viewport.Height;
    float cur = cam->m_viewWindow[0] / cam->m_viewWindow[1];
    float diff = cur - aspect;
    if (diff < 0) diff = -diff;
    if (diff > g_aspectEps && g_forceAspect != 0 && mTileRender)
        SetAspect(aspect);

    if (!mCamera->Check()) return false;
    BuildTransforms();

    cShaderDataRenderType* sd = (cShaderDataRenderType*)mShaderDataRT;
    int changed;
    if (sd->mVariation == mRenderType) {
        changed = (u8)sd->mType == (u8)mRenderTypeVariation ? 0 : 1;
    } else {
        changed = 1;
    }
    sd->mVariation = mRenderType;
    sd->mType = (u8)mRenderTypeVariation;
    DrawShader(0x201, sd, changed);
    return true;
}

// @ 0x007c50b0
__declspec(noinline) bool cViewer_s007c_4be0::Copy(cViewer_s007c_4be0* src, bool copyZBuffer, bool keepRaster)
{
    if (this == src) return true;
    if (src == 0 || src->mCamera == 0 || mCamera == 0) return false;

    rwCamera* sc = src->mCamera;
    mTileRender = src->mTileRender;
    mRenderTypeVariation = src->mRenderTypeVariation;
    mRenderType = src->mRenderType;
    mCamera->m_projectionType = sc->m_projectionType;
    mCamera->m_nearPlane = sc->m_nearPlane;
    mCamera->m_farPlane  = sc->m_farPlane;
    mCamera->m_viewOffset[0] = sc->m_viewOffset[0];
    mCamera->m_viewOffset[1] = sc->m_viewOffset[1];

    char local[0x40];
    sc->AssignTo(local);
    mCamera->SetTexture(local);

    for (int i = 0; i < 16; i++) mCameraToWorld[i] = src->mCameraToWorld[i];
    mCamera->m_raster[0] = sc->m_raster[0];
    if (!copyZBuffer)
        mCamera->m_zbuffer = sc->m_zbuffer;
    if (!keepRaster && sc->m_raster[1] != 0)
        FUN_011f38f0(1, sc->m_raster[1]);

    int r[4];
    sc->GetViewport(r);
    mCamera->SetSize(r[0], r[1], r[2] - r[0], r[3] - r[1]);

    float vx = sc->m_viewWindow[0];
    float vy = sc->m_viewWindow[1];
    rwCamera* dc = mCamera;
    dc->m_viewWindow[0] = vx;
    dc->m_viewWindow[1] = vy;
    dc->m_recipViewWindow[0] = 1.0f / vx;
    dc->m_recipViewWindow[1] = 1.0f / vy;
    UpdateTransforms();
    return true;
}

// @ 0x007c5240
__declspec(noinline) void cViewer_s007c_4be0::CopyFrom(cViewer_s007c_4be0* src)
{
    if (this == src) return;
    mTileRender = src->mTileRender;
    {
        float* s = src->mCamera->m_transform;
        float* d = mCamera->m_transform;
        for (int i = 0; i < 16; i++) d[i] = s[i];
    }
    for (int i = 0; i < 16; i++) mCameraToWorld[i] = src->mCameraToWorld[i];
    mCamera->m_nearPlane = src->mCamera->m_nearPlane;
    mCamera->m_farPlane  = src->mCamera->m_farPlane;
    float vx = src->mCamera->m_viewWindow[0];
    float vy = src->mCamera->m_viewWindow[1];
    rwCamera* d = mCamera;
    d->m_viewWindow[0] = vx;
    d->m_viewWindow[1] = vy;
    d->m_recipViewWindow[0] = 1.0f / vx;
    d->m_recipViewWindow[1] = 1.0f / vy;
    UpdateTransforms();
}
