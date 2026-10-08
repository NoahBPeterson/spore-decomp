// Slice s00f6a960 -- three-pass full-screen quad draw (constant buffers 0x242/0x201, 0x250, 0x251).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (no /EHsc: the function has no SEH frame)
#include "types.h"
#include <string.h>

struct Vec4 { float x, y, z, w; Vec4() {} Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };

struct Vec3 { float x, y, z; Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };

struct Rect { float x0, y0, x1, y1; };

struct Handle { uint32_t value; uint32_t flags; };   // lazily resolved resource handle (bit0 = resolved)

// singleton at 0x0067dd60: resolves a Handle through vtable slot 13 (+0x34)
struct IResolver { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                   virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
                   virtual void v10(); virtual void v11(); virtual void v12();
                   virtual void Resolve(Handle* h); };                                  // +0x34
// singleton at 0x0067dda0: viewport query through vtable slot 9 (+0x24)
struct IViewportInfo { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                       virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
                       virtual void Query(uint32_t a, uint32_t b, int* px, int* py, int* w, int* h); }; // +0x24
IResolver* __cdecl GetResolver();       // 0x0067dd60
IViewportInfo* __cdecl GetViewportInfo(); // 0x0067dda0

struct ShaderIds { char pad[4]; uint32_t id; };      // [ptr+4] is the shader id
struct ShaderTable { char pad34[0x34]; ShaderIds* s34; ShaderIds* s38; ShaderIds* s3c; };
ShaderTable* __cdecl GetShaderTable();    // 0x00f48a60

void __cdecl SetShaderConst(int slot, const void* data, int zero);   // 0x00777ae0

// Constant/texture binding object (ctor at 0x00fc2c10, dtor at 0x00fc2830)
struct Binding {
    uint32_t m0, m4, m8, mc;
    Binding(uint32_t shader, int index, uint32_t value);
    ~Binding();
};

struct DrawData {                 // object returned by Owner-arg vtable slot 4 (+0x10)
    char pad00[0x31c];
    Handle* h31c;
    Handle* h320;
    Handle* h324;
    Handle* h328;
    char pad32c[0x43c - 0x32c];
    Vec4 c43c;
    Vec4 c44c;
    Vec4* Query1(Vec4* tmp);      // 0x00fb9ad0
    Vec4* Query2(Vec4* tmp);      // 0x00fb9ca0
};

struct Source {                   // arg1: vtable +0x10 returns DrawData; indexed handle getters
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual DrawData* GetData();   // +0x10
    uint32_t TexA(int i);         // 0x00f98260
    uint32_t TexB(int i);         // 0x00f98270
    uint32_t TexC(int i);         // 0x00f98280
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

struct Compositor {
    char pad00[0x1c];
    Viewer* mViewer;
    char pad20[0x200 - 0x20];
    IBatch* mBatch;
    bool Draw(Source* src, const uint32_t* raster, int a3, Rect r,
              float v0, float v1, float v2, int a11, void* a12);       // 0x00f6a960
};

static inline uint32_t ResolveHandle(Handle* h)
{
    if (!(h->flags & 1))
        GetResolver()->Resolve(h);
    return h->value;
}

// @ 0x00f6a960
bool Compositor::Draw(Source* src, const uint32_t* raster, int a3, Rect r,
                      float v0, float v1, float v2, int a11, void* a12)
{
    DrawData* d = src->GetData();
    if (!d)
        return false;

    Vec4 v;
    v.x = v0;
    v.y = v1;
    v.z = 1.0f / (v2 - v0);
    v.w = 0.0f;
    int vx, vy, vw, vh;
    GetViewportInfo()->Query(raster[0], raster[1], &vx, &vy, &vw, &vh);

    uint32_t shader = GetShaderTable()->s34->id;
    static Vec4 cb0[4];
    cb0[0] = d->c44c;
    cb0[1] = d->c43c;
    cb0[2] = v;
    cb0[2].w = 0.5f / (float)vw;
    cb0[3] = Vec4(0.0f, -1.0f, 1.0f, 1.0f);

    void* out = 0;
    if (!mBatch->Alloc(&out, 0x18, 4, 0))
        return false;
    SetShaderConst(0x242, cb0, 0);
    SetShaderConst(0x201, 0, 0);
    memset(out, 0, 0x60);
    *(Vec3*)out = Vec3(r.x0, 1.0f - r.y1, 1.0f);
    *(Vec3*)((char*)out + 0x18) = Vec3(r.x1, 1.0f - r.y1, 1.0f);
    *(Vec3*)((char*)out + 0x30) = Vec3(r.x0, 1.0f - r.y0, 1.0f);
    *(Vec3*)((char*)out + 0x48) = Vec3(r.x1, 1.0f - r.y0, 1.0f);
    mViewer->SetRaster(raster, 1);
    if (mViewer->Update()) {
        Binding b0(shader, 0, src->TexC(a3));
        Binding b1(shader, 1, ResolveHandle(d->h328));
        if (!mBatch->Apply(shader, a12))
            return false;
        mViewer->Finish();
    }
    SetShaderConst(0x242, 0, 0);

    {
        shader = GetShaderTable()->s38->id;
        static Vec4 cb1;
        {
            Vec4 tmp;
            cb1 = *d->Query1(&tmp);
        }
        SetShaderConst(0x242, cb0, 0);
        SetShaderConst(0x250, &cb1, 0);
        mViewer->SetRaster(raster, 1);
        if (mViewer->Update()) {
            Binding b0(shader, 0, src->TexA(a3));
            Binding b1(shader, 1, ResolveHandle(d->h31c));
            if (!mBatch->Apply(shader, a12))
                return false;
            mViewer->Finish();
        }
        SetShaderConst(0x242, 0, 0);
        SetShaderConst(0x250, 0, 0);
    }

    {
        shader = GetShaderTable()->s3c->id;
        static Vec4 cb2;
        {
            Vec4 tmp;
            cb2 = *d->Query2(&tmp);
        }
        SetShaderConst(0x242, cb0, 0);
        SetShaderConst(0x251, &cb2, 0);
        mViewer->SetRaster(raster, 1);
        if (mViewer->Update()) {
            Binding b0(shader, 0, src->TexB(a3));
            Binding b1(shader, 1, src->TexA(a3));
            Binding b2(shader, 2, ResolveHandle(d->h320));
            if (!mBatch->Apply(shader, a12))
                return false;
            mBatch->Flush();
            mViewer->Finish();
        }
        SetShaderConst(0x242, 0, 0);
        SetShaderConst(0x251, 0, 0);
    }
    return true;
}
