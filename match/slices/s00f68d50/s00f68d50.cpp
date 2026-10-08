// Slice s00f68d50: SP::cTerrainEditor::SynthesizeAboveTextureDecal (0x00f691d0).
// Draws one textured decal quad (4 vertices, 0x70 bytes each) into a transient vertex buffer and renders it
// with the decal shader (constant buffer 0x242), binding the decal texture handle at info+0x128.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <string.h>
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

struct TerrainEditorStub {
    char pad00[0x1c];
    Viewer* mViewer;            // +0x1c
    char pad20[0x208 - 0x20];
    IBatch* mBatch;             // +0x208

    bool SynthesizeAboveTextureDecal(ILayer* layer, DecalInfo* info, const uint32_t* raster, int face,
                                     float u0, float v0, float u1, float v1, void* arg);   // 0x00f691d0
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
