// Slice s007c3ba0 — SP::cViewer camera/frustum helpers and the camera accessor
// cluster.  /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// types
// ---------------------------------------------------------------------------
struct Vec4 { float x, y, z, w; };
struct Vec3f { float x, y, z; };
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
    void   FUN_007c40f0(unsigned short*);
    void   FUN_007c4180(float*, const float*);            // clip-space perspective divide
    void   FUN_007c42a0(float*);                          // build projection matrix
    bool   FUN_007c43e0();                                // rebuild the device matrices
    bool   FUN_007c4510(float, float, float*, float*);    // screen -> world (projected)
    bool   FUN_007c4730(float, float, float*, float*);    // screen -> world ray
    void   FUN_007c46f0(void*, void*);
    void   FUN_007c4900(void*, void*);
    void   FUN_007c4a60(unsigned short*);
    void   FUN_007c4ad0(float, float);
    void   FUN_007c4b00(float, float);
    void   FUN_007c4b50(float);
    void   FUN_007c4ba0(float);
    void   FUN_007c4bc0(float);
    void   FUN_007c4940();                  // recompute derived transforms
};

void FUN_007c3de0(float* dst, const float* src);   // 0x007c3de0 rigid 4x4 inverse

void __cdecl FUN_0045df90(float*, const float*, float*);       // 0x0045df90 4x4 inverse
void __cdecl FUN_0045eac0(float*, const float*, const float*); // 0x0045eac0 4x4 multiply
void __cdecl FUN_011e1ff2(float*, const float*, const float*); // 0x011e1ff2 MatrixMultiply
void __cdecl FUN_011e1fec(float*, const float*);               // 0x011e1fec MatrixTranspose

extern float g_16f8b10[];   // 0x016f8b10
extern float g_16f8be0[];   // 0x016f8be0
extern float g_16f8c70[];   // 0x016f8c70
extern float g_16f90d0[];   // 0x016f90d0

void __cdecl EASTL_deallocate(void*);      // 0x00f47380
void __cdecl FUN_00f47410(void*);
extern "C" void* __cdecl FUN_0067dd50();   // 0x0067dd50

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
    // Three 12-byte row copies out of the 16-byte rows (xAxis/yAxis/zAxis -> dst[0..8]).
    // Retail keeps the first two rows relative to the original bases and then advances both
    // (`add $0x20,%ecx; add $0x18,%eax` at 0x7c3dc9), which also leaves eax = dst+0x18; cl folds
    // the advances into displacements here because the bumped pointers are dead afterwards.
    const int* s = (const int*)this;
    int* d = (int*)dst;
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    d[3] = s[4];
    d[4] = s[5];
    d[5] = s[6];
    d[6] = s[8];
    d[7] = s[9];
    d[8] = s[10];
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
// @ 0x007c40f0  append one vertex record (3x3 rotation + translation) to a buffer
// ---------------------------------------------------------------------------
void cViewer::FUN_007c40f0(unsigned short* p)
{
    float rot[9];
    const float* s = (const float*)&mCameraToWorldTransform;
    rot[0] = s[0]; rot[1] = s[1]; rot[2] = s[2];
    rot[3] = s[4]; rot[4] = s[5]; rot[5] = s[6];
    rot[6] = s[8]; rot[7] = s[9]; rot[8] = s[10];

    p[0] = (unsigned short)(p[0] | 2);
    p[1] = (unsigned short)(p[1] + 1);

    float* d = (float*)(p + 10);                 // +0x14
    for (int i = 0; i < 9; ++i)
        d[i] = rot[i];

    float* t = (float*)(p + 2);                  // +0x04
    t[0] = mCameraToWorldTransform.wAxis.x;
    t[1] = mCameraToWorldTransform.wAxis.y;
    t[2] = mCameraToWorldTransform.wAxis.z;

    p[0] = (unsigned short)(p[0] | 4);
    p[1] = (unsigned short)(p[1] + 1);
}

// ---------------------------------------------------------------------------
// @ 0x007c46f0  wrapper: viewport size from the camera device -> FUN_007c4510
// ---------------------------------------------------------------------------
void cViewer::FUN_007c46f0(void* a, void* b)
{
    void* p = FUN_0067dd50();
    void** vt = *(void***)p;
    int* r = (int*)((void*(__thiscall*)(void*))vt[0x1c / 4])(p);
    FUN_007c4510((float)r[2], (float)r[3], (float*)a, (float*)b);
}

// ---------------------------------------------------------------------------
// @ 0x007c4900  wrapper: viewport size from the camera device -> world ray
// ---------------------------------------------------------------------------
void cViewer::FUN_007c4900(void* a, void* b)
{
    void* p = FUN_0067dd50();
    void** vt = *(void***)p;
    int* r = (int*)((void*(__thiscall*)(void*))vt[0x1c / 4])(p);
    FUN_007c4730((float)r[2], (float)r[3], (float*)a, (float*)b);
}

// ---------------------------------------------------------------------------
// @ 0x007c3de0  rigid 4x4 inverse: transpose the 3x3 and negate the translation
// ---------------------------------------------------------------------------
void FUN_007c3de0(float* d, const float* s)
{
    d[0] = s[0];  d[1] = s[4];  d[2] = s[8];
    d[4] = s[1];  d[5] = s[5];  d[6] = s[9];
    d[8] = s[2];  d[9] = s[6];  d[10] = s[10];
    d[12] = -(s[14] * s[2] + s[13] * s[1] + s[12] * s[0]);
    d[13] = -(s[14] * s[6] + s[13] * s[5] + s[12] * s[4]);
    d[14] = -(s[14] * s[10] + s[13] * s[9] + s[12] * s[8]);
}

// ---------------------------------------------------------------------------
// @ 0x007c4180  transform a point by mWorldToClipTransform, divide through by w
// ---------------------------------------------------------------------------
void cViewer::FUN_007c4180(float* out, const float* v)
{
    const Matrix44* m = &mWorldToClipTransform;
    float x = ((m->zAxis.x * v[2] + m->yAxis.x * v[1]) + m->xAxis.x * v[0]) + m->wAxis.x;
    float y = ((m->zAxis.y * v[2] + m->yAxis.y * v[1]) + m->xAxis.y * v[0]) + m->wAxis.y;
    float z = ((m->zAxis.z * v[2] + m->yAxis.z * v[1]) + m->xAxis.z * v[0]) + m->wAxis.z;
    float w = ((m->zAxis.w * v[2] + m->yAxis.w * v[1]) + m->xAxis.w * v[0]) + m->wAxis.w;
    float inv = 1.0f / w;
    out[0] = inv * x;
    out[1] = inv * y;
    out[2] = inv * z;
}

// ---------------------------------------------------------------------------
// @ 0x007c42a0  build the camera -> clip projection matrix
// ---------------------------------------------------------------------------
void cViewer::FUN_007c42a0(float* dst)
{
    Camera* cam = mCamera;
    for (int i = 0; i < 16; ++i)
        dst[i] = 0.0f;

    float f58 = cam->f58;
    float f70 = cam->f70;
    float f74 = cam->f74;
    float f54 = cam->f54;
    float invW = 1.0f / cam->f5c;
    float invH = 1.0f / cam->f60;

    dst[0] = invW;
    dst[5] = invH;

    if (cam->n6c == 2) {
        float f = 1.0f / (f74 - f70);
        dst[10] = f;
        dst[8] = 0.0f;
        dst[9] = 0.0f;
        dst[11] = 0.0f;
        dst[12] = invW * f54;
        dst[13] = invH * f58;
        dst[14] = -(f * f70);
        dst[15] = 1.0f;
        return;
    }

    dst[11] = 1.0f;
    if (cam->n6c == 3) {
        dst[8] = 0.0f;
        dst[9] = 0.0f;
        dst[10] = 1.0f;
        dst[12] = 0.0f;
        dst[13] = 0.0f;
        dst[14] = -f70;
        dst[15] = 0.0f;
        return;
    }

    dst[8] = invW * f54;
    float f = f74 / (f74 - f70);
    dst[10] = f;
    dst[9] = invH * f58;
    dst[12] = 0.0f;
    dst[13] = 0.0f;
    dst[14] = -(f * f70);
    dst[15] = 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x007c43e0  rebuild the device matrices (mirror + projection + transpose)
// ---------------------------------------------------------------------------
bool cViewer::FUN_007c43e0()
{
    float local[16];
    const float* cam = (const float*)mCamera;
    for (int i = 0; i < 16; ++i)
        local[i] = cam[i];

    FUN_007c3de0(g_16f8b10, local);

    g_16f8b10[0] = -g_16f8b10[0];
    g_16f8b10[4] = -g_16f8b10[4];
    g_16f8b10[8] = -g_16f8b10[8];
    g_16f8b10[12] = -g_16f8b10[12];
    g_16f8b10[3] = 0.0f;
    g_16f8b10[7] = 0.0f;
    g_16f8b10[11] = 0.0f;
    g_16f8b10[15] = 1.0f;

    FUN_007c42a0(g_16f90d0);
    FUN_011e1ff2(g_16f8be0, g_16f8b10, g_16f90d0);
    FUN_011e1fec(g_16f8c70, g_16f8be0);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x007c4510  screen coords -> world position (a) and far point (b)
// ---------------------------------------------------------------------------
bool cViewer::FUN_007c4510(float sx, float sy, float* a, float* b)
{
    Camera* cam = mCamera;
    float u = ((sx - (float)(unsigned short)cam->vpX) * 2.0f) / (float)(unsigned short)cam->vpW - 1.0f;
    float v = 1.0f - ((sy - (float)(unsigned short)cam->vpY) * 2.0f) / (float)(unsigned short)cam->vpH;

    const Matrix44* m = &mClipToWorldTransform;
    float fy = m->wAxis.y + (m->xAxis.y * u + m->yAxis.y * v);
    float fx = m->wAxis.x + (u * m->xAxis.x + m->yAxis.x * v);
    float fz = m->wAxis.z + (m->xAxis.z * u + m->yAxis.z * v);
    float fw = m->wAxis.w + (m->xAxis.w * u + m->yAxis.w * v);
    float dinv = 1.0f / (m->zAxis.w + fw);
    float inv = 1.0f / fw;

    a[0] = inv * fx;
    a[1] = fy * inv;
    a[2] = fz * inv;
    b[0] = dinv * (m->zAxis.x + fx);
    b[1] = (m->zAxis.y + fy) * dinv;
    b[2] = (m->zAxis.z + fz) * dinv;
    return true;
}

// The original accumulates the squared length, and takes its reciprocal square root, in the x87
// extended-precision registers (fld/fmul/faddp/fsqrt/fld1/fdivrp) from deltas already rounded to
// 32-bit float, not in 32-bit SSE.  A separate no-inline definition reproduces both properties:
// the arguments are rounded to float on the way in, and /fp:fast cannot contract the squared sum
// back to mulss/addss (which would overflow for large projected coordinates).
__declspec(noinline) static float RayInvLen(float dx, float dy, float dz)
{
    volatile double a = (double)dx * (double)dx;
    volatile double b = (double)dy * (double)dy;
    volatile double c = (double)dz * (double)dz;
    double s = ((double)a + (double)b + (double)c) + 1e-08;
    return (float)(1.0 / sqrt(s));
}

// ---------------------------------------------------------------------------
// @ 0x007c4730  screen coords -> world-space ray (origin + normalised direction)
// ---------------------------------------------------------------------------
bool cViewer::FUN_007c4730(float sx, float sy, float* org, float* dir)
{
    Camera* cam = mCamera;
    unsigned short vpX = (unsigned short)cam->vpX;
    unsigned short vpW = (unsigned short)cam->vpW;
    unsigned short vpY = (unsigned short)cam->vpY;
    unsigned short vpH = (unsigned short)cam->vpH;

    org[0] = mCameraToWorldTransform.wAxis.x;
    org[1] = mCameraToWorldTransform.wAxis.y;
    org[2] = mCameraToWorldTransform.wAxis.z;

    float u = ((sx - (float)vpX) * 2.0f) / (float)vpW - 1.0f;
    float v = 1.0f - ((sy - (float)vpY) * 2.0f) / (float)vpH;

    const Matrix44* m = &mClipToWorldTransform;
    float fw = (((m->yAxis.w * v + m->xAxis.w * u) + m->wAxis.w) + m->zAxis.w);
    float invW = 1.0f / fw;
    float dz = ((((m->yAxis.z * v + m->xAxis.z * u) + m->wAxis.z) + m->zAxis.z) * invW - org[2]);
    float dy = ((((m->yAxis.y * v + m->xAxis.y * u) + m->wAxis.y) + m->zAxis.y) * invW - org[1]);
    float dx = ((((m->yAxis.x * v + m->xAxis.x * u) + m->wAxis.x) + m->zAxis.x) * invW - org[0]);

    float inv = RayInvLen(dx, dy, dz);

    dir[0] = inv * dx;
    dir[1] = dy * inv;
    dir[2] = dz * inv;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x007c4940  recompute the derived camera transforms
// ---------------------------------------------------------------------------
void cViewer::FUN_007c4940()
{
    float tmp[16];
    float det = 0.0f;

    FUN_0045df90(tmp, (const float*)this, &det);
    for (int i = 0; i < 16; ++i)
        ((float*)&mWorldToCameraTransform)[i] = tmp[i];

    FUN_007c42a0((float*)&mCameraToClipTransform);

    Vec4 save = mCameraToClipTransform.yAxis;
    mCameraToClipTransform.yAxis = mCameraToClipTransform.zAxis;
    mCameraToClipTransform.zAxis.x = save.x;
    mCameraToClipTransform.zAxis.y = save.y;
    mCameraToClipTransform.zAxis.z = save.z;
    mCameraToClipTransform.zAxis.w = save.w;

    FUN_0045eac0(tmp, (const float*)&mWorldToCameraTransform, (const float*)&mCameraToClipTransform);
    for (int i = 0; i < 16; ++i)
        ((float*)&mWorldToClipTransform)[i] = tmp[i];

    FUN_0045df90(tmp, (const float*)&mWorldToClipTransform, &det);
    for (int i = 0; i < 16; ++i)
        ((float*)&mClipToWorldTransform)[i] = tmp[i];
}

// ---------------------------------------------------------------------------
// skeletons (not reconstructed)
// ---------------------------------------------------------------------------
