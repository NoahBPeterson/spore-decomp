// Slice s00f68d50: SP::cTerrainEditor::SynthesizeAboveTextureDecal (0x00f691d0).
// Draws one textured decal quad (4 vertices, 0x70 bytes each) into a transient vertex buffer and renders it
// with the decal shader (constant buffer 0x242), binding the decal texture handle at info+0x128.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <string.h>
#include <math.h>
#include <xmmintrin.h>

struct Vec3 { float x, y, z; };
struct Vec4 {
    float x, y, z, w;
    Vec4() {}
    Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};

struct Handle { uint32_t value; uint32_t flags; };   // lazily resolved resource handle (bit0 = resolved)

struct IResolver {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void Resolve(Handle* h);                                   // +0x34
};
struct IViewportInfo {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void Query(uint32_t a, uint32_t b, int* px, int* py, int* w, int* h);   // +0x24
};
IResolver* __cdecl GetResolver();          // 0x0067dd60
IViewportInfo* __cdecl GetViewportInfo();  // 0x0067dda0

struct ShaderIds { char pad[4]; uint32_t id; };
struct ShaderTable { char pad[0x40]; ShaderIds* s40; };
ShaderTable* __cdecl GetShaderTable();     // 0x00f48a60

void __cdecl SetShaderConst(int slot, const void* data, int zero);   // 0x00777ae0

struct Binding {                           // ctor 0x00fc2c10, dtor 0x00fc2830
    uint32_t m0, m4, m8, mc;
    Binding(uint32_t shader, int index, uint32_t value);
    ~Binding();
};

struct Viewer {
    void SetRaster(const void* r, int flag);   // 0x007c4be0
    bool Update();                             // 0x007c4fd0
    void Finish();                             // 0x007c3c10
};

struct IBatch {
    virtual void v0(); virtual void v1();
    virtual bool Alloc(void** out, int stride, int count, int zero);   // +0x08
    virtual bool Apply(uint32_t shader, void* arg);                    // +0x0c
    virtual void Flush();                                              // +0x10
};

struct ILayer { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void Begin(); };  // +0x10

// Decal description (retail layout, from the asm).
struct DecalInfo {
    char  pad00[0x40];
    Vec4  color;        // +0x40 (r, g, b, a in 0..2)
    char  pad50[0xec - 0x50];
    Vec3  vA;           // +0xec
    Vec4  vB;           // +0xf8
    Vec4  vC;           // +0x108
    Vec4  vD;           // +0x118
    Handle* tex;        // +0x128
};

struct Vertex {         // 0x70 bytes
    Vec4 pos;           // +0x00
    Vec3 axis;          // +0x10
    uint32_t color;     // +0x1c
    Vec4 a;             // +0x20
    Vec4 b;             // +0x30
    Vec4 c;             // +0x40
    Vec4 d;             // +0x50
    uint32_t tail[4];   // +0x60
};

extern const unsigned char g_faceAxes[][4];   // 0x0148f608
extern unsigned int g_softStateDirty;         // 0x016f9528
extern unsigned int g_transformType;          // 0x016f96a0
extern void* g_transform;                     // 0x016fa380
__declspec(align(16)) struct Matrix44Affine { __m128 r[4]; };
extern __m128 g_transformLocal[4];              // 0x016fa4f0

#pragma warning(disable:4035)
#pragma warning(disable:4700)
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

static inline int ToByte(float v)
{
    if (0.0f > v)
        v = 0.0f;
    else if (v > 2.0f)
        v = 2.0f;
    return FloorToInt(v * 127.5f);
}

struct cBrushHeightInfo;   // opaque

// Brush texture description (retail offsets, confirmed against every read in the asm).
struct cBrushTextureInfo {
    char pad00[0x2c];
    Vec4 mTexturePlane;         // +0x2c
    char pad3c[4];              // +0x3c
    Vec3 mZeroUVLoc;            // +0x40
    Vec3 mDirectionU;           // +0x4c
    float mScaleU;              // +0x58
    Vec3 mDirectionV;           // +0x5c
    float mScaleV;              // +0x68
};

// Transient quad-buffer allocator reached through cTerrainEditor+0x204.
struct IQuadBufferAllocator {
    virtual void v0();
    virtual bool AllocBuffers(void** vbuf, int stride, int nv, void** ibuf, int ni, int flag);  // +0x04
};

struct QuadVertex {             // 0x2c bytes
    float mX, mY;               // +0x00 (positions, written by TessellateBrush)
    char pad08[8];
    float mA, mB, mC, mD;       // +0x10 (brush vertex data)
    uint32_t mColor;            // +0x20
    float mU, mV;               // +0x24
};

struct RectF {
    float mLeft, mTop, mRight, mBottom;
};

struct TerrainEditorStub {
    char pad00[0x1c];
    Viewer* mViewer;            // +0x1c
    char pad20[0x78 - 0x20];
    bool mGPUDirtyFace[6];      // +0x78
    char pad7e[0x80 - 0x7e];
    RectF mCPUDirtyRect[6];     // +0x80
    RectF mBrushDirtyRect[6];   // +0xe0
    char pad140[0x1cd - 0x140];
    bool mCapturingImpostor;            // +0x1cd
    bool mCapturingPlanetToImpostor;    // +0x1ce
    char pad1cf[0x204 - 0x1cf];
    IQuadBufferAllocator* mQuadBufferAllocator;   // +0x204
    IBatch* mBatch;             // +0x208

    bool SynthesizeAboveTextureDecal(ILayer* layer, DecalInfo* info, const uint32_t* raster, int face,
                                     float u0, float v0, float u1, float v1, void* arg);   // 0x00f691d0
    bool LoadBuffersForQuadBrush(const Vec3* verts, int numVerts, int face,
                                 const cBrushHeightInfo& heightInfo, const cBrushTextureInfo& texInfo,
                                 int numSubdiv);                                       // 0x00f68d50
    bool QuadQueueEmpty();                                                         // 0x00f699a0
    bool IsAllWorkDone();                                                          // 0x00f699b0
    void TessellateBrush(void* vbuf, void* ibuf, const Vec3* verts, int numVerts, int numSubdiv,
                         int nv, int ni);                                          // 0x00f687f0
    void GetBrushVertexData(const cBrushHeightInfo& heightInfo, const cBrushTextureInfo& texInfo,
                            float* out);                                           // 0x00f675b0
};

static inline uint32_t ResolveHandle(Handle* h)
{
    if (!(h->flags & 1))
        GetResolver()->Resolve(h);
    return h->value;
}

// @ 0x00f691d0
bool TerrainEditorStub::SynthesizeAboveTextureDecal(ILayer* layer, DecalInfo* info, const uint32_t* raster,
                                                    int face, float u0, float v0, float u1, float v1,
                                                    void* arg)
{
    layer->Begin();

    g_softStateDirty |= 1;
    Matrix44Affine ident;
    ident.r[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
    ident.r[1] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
    ident.r[2] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
    ident.r[3] = _mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f);
    g_transformType = 2;
    g_transform = g_transformLocal;
    g_transformLocal[0] = ident.r[0];
    g_transformLocal[1] = ident.r[1];
    g_transformLocal[2] = ident.r[2];
    g_transformLocal[3] = ident.r[3];

    Vec4 vq(0.0f, 0.0f, 1.0f, 0.0f);
    int vx, vy, vw, vh;
    GetViewportInfo()->Query(raster[0], raster[1], &vx, &vy, &vw, &vh);
    uint32_t shader = GetShaderTable()->s40->id;

    Vertex* verts;
    if (!mBatch->Alloc((void**)&verts, 0x70, 4, 0))
        return false;
    memset(verts, 0, 0x1c0);
    verts[0].pos = Vec4(u0, 1.0f - v1, 1.0f, 1.0f);
    verts[1].pos = Vec4(u1, 1.0f - v1, 1.0f, 1.0f);
    verts[2].pos = Vec4(u0, 1.0f - v0, 1.0f, 1.0f);
    verts[3].pos = Vec4(u1, 1.0f - v0, 1.0f, 1.0f);

    float a[3];
    float sign = (face & 1) ? -1.0f : 1.0f;
    int row = (face >> 1) * 4;
    a[0] = sign;
    a[1] = 1.0f;
    a[2] = sign;
    unsigned char ia = g_faceAxes[face >> 1][0];
    unsigned char ib = g_faceAxes[face >> 1][1];
    unsigned char ic = g_faceAxes[face >> 1][2];
    (void)row;
    float f0 = a[ia];
    float f1 = a[ib];
    float f2 = a[ic];
    a[2] = 1.0f;

    for (int i = 0; i < 4; ++i) {
        Vertex* v = &verts[i];
        a[0] = v->pos.x;
        a[1] = 1.0f - v->pos.y;
        v->axis.x = (a[ia] * 2.0f - 1.0f) * f0;
        v->axis.y = (a[ib] * 2.0f - 1.0f) * f1;
        v->axis.z = (a[ic] * 2.0f - 1.0f) * f2;
        v->b = info->vB;
        v->a = Vec4(info->vA.x, info->vA.y, info->vA.z, 0.0f);
        v->c = info->vC;
        v->d = info->vD;
        float c0 = info->color.x;
        float c1 = info->color.y;
        float c2 = info->color.z;
        float c3 = info->color.w;
        int b = ToByte(c2);
        int g = ToByte(c1);
        int r = ToByte(c0);
        int al = ToByte(c3);
        v->color = (((al << 8 | r) << 8 | g) << 8 | b);
    }

    static Vec4 cb[4];
    cb[2] = vq;
    cb[2].w = 0.5f / (float)vw;
    cb[3] = Vec4(0.0f, -1.0f, 1.0f, 1.0f);
    SetShaderConst(0x242, cb, 0);

    mViewer->SetRaster(raster, 1);
    if (mViewer->Update()) {
        Binding b0(shader, 0, ResolveHandle(info->tex));
        if (!mBatch->Apply(shader, arg))
            return false;
        mBatch->Flush();
        mViewer->Finish();
    }
    SetShaderConst(0x242, 0, 0);
    return true;
}

// ---------------------------------------------------------------------------------------------------
// Quad-buffer tessellation support (0x00f68d50 / 0x00f699a0 / 0x00f699b0).

struct QuadQueue {              // intrusive list head
    QuadQueue* mpNext;          // +0x00
    QuadQueue* mpPrev;          // +0x04
};
extern QuadQueue g_quadQueue;   // 0x015b0e48

uint32_t __cdecl ColorRGBToU32(const Vec3* color);   // 0x00458a40

// @ 0x00f699a0
bool TerrainEditorStub::QuadQueueEmpty()
{
    return g_quadQueue.mpNext == &g_quadQueue;
}

// @ 0x00f699b0
bool TerrainEditorStub::IsAllWorkDone()
{
    if (!QuadQueueEmpty())
        return false;
    if (mCapturingPlanetToImpostor)
        return false;
    for (int i = 0; i < 6; ++i) {
        if (mGPUDirtyFace[i])
            return false;
        const RectF& cpu = mCPUDirtyRect[i];
        if (cpu.mLeft != cpu.mRight && cpu.mTop != cpu.mBottom)
            return false;
        const RectF& brush = mBrushDirtyRect[i];
        if (brush.mLeft != brush.mRight && brush.mTop != brush.mBottom)
            return false;
    }
    return true;
}

// @ 0x00f68d50
bool TerrainEditorStub::LoadBuffersForQuadBrush(const Vec3* verts, int numVerts, int face,
                                                const cBrushHeightInfo& heightInfo,
                                                const cBrushTextureInfo& texInfo, int numSubdiv)
{
    int n = numVerts - 2;
    int ni = 3 * n;
    int nv = numVerts;
    for (int i = 0; i < numSubdiv; ++i) {
        nv += 3 * n;
        ni = 12 * n;
        n *= 4;
    }

    QuadVertex* vbuf = 0;
    void* ibuf = 0;
    if (!mQuadBufferAllocator->AllocBuffers((void**)&vbuf, 0x2c, nv, &ibuf, ni, 1))
        return false;

    TessellateBrush(vbuf, ibuf, verts, numVerts, numSubdiv, nv, ni);

    float a[3];
    float sign = (face & 1) ? -1.0f : 1.0f;
    a[0] = sign;
    a[1] = 1.0f;
    a[2] = sign;
    const unsigned char* axes = g_faceAxes[face >> 1];
    unsigned char ia = axes[0];
    unsigned char ib = axes[1];
    unsigned char ic = axes[2];
    float f0 = a[ia];
    float f1 = a[ib];
    float f2 = a[ic];
    a[2] = 1.0f;

    float axisOut[4];
    GetBrushVertexData(heightInfo, texInfo, axisOut);

    Vec4 plane = texInfo.mTexturePlane;
    Vec3 zeroUV = texInfo.mZeroUVLoc;
    Vec3 dirU = texInfo.mDirectionU;
    Vec3 dirV = texInfo.mDirectionV;

    float t;    // deliberately left uninitialized, as in the original
    for (int i = 0; i < nv; ++i) {
        QuadVertex* v = &vbuf[i];
        a[0] = v->mX;
        a[1] = 1.0f - v->mY;
        float nx = (a[ia] * 2.0f - 1.0f) * f0;
        float ny = (a[ib] * 2.0f - 1.0f) * f1;
        float nz = (a[ic] * 2.0f - 1.0f) * f2;
        float inv = (float)(1.0 / sqrt((double)nx * (double)nx
                                       + ((double)nz * (double)nz + (double)ny * (double)ny)));
        nx *= inv;
        ny *= inv;
        nz *= inv;
        float denom = nx * plane.x + nz * plane.z + ny * plane.y;
        if (denom != 0.0f)
            t = -((plane.x * 0.0f + plane.y * 0.0f + plane.z * 0.0f + plane.w) / denom);
        float dx = nx * t - zeroUV.x;
        float dy = ny * t - zeroUV.y;
        float dz = nz * t - zeroUV.z;
        v->mU = (dx * dirU.x + dz * dirU.z + dy * dirU.y) / texInfo.mScaleU;
        v->mV = 1.0f - (dx * dirV.x + dz * dirV.z + dy * dirV.y) / texInfo.mScaleV;
        v->mA = axisOut[0];
        v->mB = axisOut[1];
        v->mC = axisOut[2];
        v->mD = axisOut[3];
        Vec3 color;
        color.x = nx * 0.5f + 0.5f;
        color.y = ny * 0.5f + 0.5f;
        color.z = nz * 0.5f + 0.5f;
        v->mColor = ColorRGBToU32(&color);
    }
    return true;
}
