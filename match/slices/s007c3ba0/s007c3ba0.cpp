// Slice s007c3ba0 — SP::cViewer camera/frustum helpers and the camera accessor
// cluster.  /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// types
// ---------------------------------------------------------------------------
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

void __cdecl EASTL_deallocate(void*);      // 0x00f47380
void __cdecl FUN_00f47410(void*);

extern int g_16f6dac;
extern int g_16f8a38;
extern int g_16f9110;
extern float g_153c7a8;

// ---------------------------------------------------------------------------
// @ 0x007c3ba0
// ---------------------------------------------------------------------------
bool cViewer::FUN_007c3ba0()
{
    if (mShaderDataRT != 0) {
        if (g_16f6dac == mShaderDataRT) {
            g_16f8a38 = g_16f8a38 | 2;
            g_16f9110 = g_16f9110 | 8;
            g_16f6dac = 0;
        }
        EASTL_deallocate((void*)mShaderDataRT);
        mShaderDataRT = 0;
    }
    if (mCamera != 0) {
        FUN_00f47410(mCamera);
        mCamera = 0;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x007c3c50
// ---------------------------------------------------------------------------
void cViewer::FUN_007c3c50(unsigned char param)
{
    int flags = 0;
    if ((param & 1) != 0)
        flags = 1;
    if ((param & 2) != 0)
        flags = flags | 2;
    if ((param & 4) != 0)
        flags = flags | 4;
    mCamera->SetClear(mClearColor, flags);
}

// ---------------------------------------------------------------------------
// @ 0x007c3c90 / 0x007c3ca0
// ---------------------------------------------------------------------------
float cViewer::FUN_007c3c90() { return mCamera->f70; }
float cViewer::FUN_007c3ca0() { return mCamera->f74; }

// ---------------------------------------------------------------------------
// @ 0x007c3d30  SP::cViewer::GetCameraLocationInfo
// ---------------------------------------------------------------------------
struct Vec3 { float x, y, z; };
void cViewer::GetCameraLocationInfo(float* w, float* y, float* z, float* x)
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

// ---------------------------------------------------------------------------
// @ 0x007c3da0  copy the 3x3 rotation part
// ---------------------------------------------------------------------------
void Matrix44::FUN_007c3da0(float* dst)
{
    int* d = (int*)dst;
    const int* s = (const int*)this;
    d[0] = s[0]; d[1] = s[1]; d[2] = s[2];
    d[3] = s[4]; d[4] = s[5]; d[5] = s[6];
    d += 6; s += 8;
    d[0] = s[0]; d[1] = s[1]; d[2] = s[2];
}

// ---------------------------------------------------------------------------
// @ 0x007c3f70
// ---------------------------------------------------------------------------
extern float g_1635db8, g_1635dbc, g_1635dc0, g_1635dc4;
extern float g_10000f;

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

// ---------------------------------------------------------------------------
// @ 0x007c4000
// ---------------------------------------------------------------------------
void cViewer::FUN_007c4000()
{
    if (mCamera != 0)
        FUN_007c3ba0();
}

// ---------------------------------------------------------------------------
// @ 0x007c4010
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x007c4050 / 0x007c40a0  field-of-view angles (x87 fpatan)
// ---------------------------------------------------------------------------
float cViewer::FUN_007c4050()
{
    float a = mCamera->f60;
    if (mCamera->f5c != a)
        a = a * 1.3333334f;
    return (360.0f / g_153c7a8) * atan2f(a, 1.0f);
}
float cViewer::FUN_007c40a0()
{
    return (360.0f / g_153c7a8) * atan2f(mCamera->f60, 1.0f);
}

// ---------------------------------------------------------------------------
// @ 0x007c40c0 / 0x007c40e0
// ---------------------------------------------------------------------------
void cViewer::FUN_007c40c0(float* a, float* b)
{
    *a = mCamera->f5c;
    *b = mCamera->f60;
}
float cViewer::FUN_007c40e0()
{
    return mCamera->f5c / mCamera->f60;
}

// ---------------------------------------------------------------------------
// @ 0x007c4a60
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x007c4ad0
// ---------------------------------------------------------------------------
void cViewer::FUN_007c4ad0(float a, float b)
{
    Camera* c = mCamera;
    c->f54 = a;
    c->f58 = b;
    FUN_007c4940();
}

// ---------------------------------------------------------------------------
// @ 0x007c4b00
// ---------------------------------------------------------------------------
void cViewer::FUN_007c4b00(float a, float b)
{
    Camera* c = mCamera;
    c->f5c = a;
    c->f60 = b;
    c->f64 = 1.0f / a;
    c->f68 = 1.0f / b;
    FUN_007c4940();
}

// ---------------------------------------------------------------------------
// @ 0x007c4b50
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x007c4ba0 / 0x007c4bc0
// ---------------------------------------------------------------------------
void cViewer::FUN_007c4ba0(float a) { Camera* c = mCamera; c->f70 = a; FUN_007c4940(); }
void cViewer::FUN_007c4bc0(float a) { Camera* c = mCamera; c->f74 = a; FUN_007c4940(); }

// ---------------------------------------------------------------------------
// skeletons (not reconstructed)
// ---------------------------------------------------------------------------
extern void g_FUN_007c4940_body();
__declspec(noinline) void cViewer::FUN_007c4940() { g_FUN_007c4940_body(); }
void FUN_007c3de0(void* a, void* b) { (void)a; (void)b; }
void FUN_007c40f0(void* a, void* b) { (void)a; (void)b; }
void FUN_007c4180(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }
void FUN_007c42a0(void* a, void* b) { (void)a; (void)b; }
void FUN_007c43e0(void* a) { (void)a; }
void FUN_007c4510(void* a) { (void)a; }
void FUN_007c46f0(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }
void FUN_007c4730(void* a) { (void)a; }
void FUN_007c4900(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }
