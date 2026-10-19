// src/game/SPTerrain/SPTerrainEditor.cpp -- migrated from slice(s) s00f6b9a0, s00f6a960 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainEditor.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include "SP/cTerrainSphere.h"

// ---- items of slice s00f6a960 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec4 { float x, y, z, w; Vec4() {} Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };
struct Vec3 { float x, y, z; Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Rect { float x0, y0, x1, y1; };
struct Handle { uint32_t value; uint32_t flags; };   // lazily resolved resource handle (bit0 = resolved)
struct IResolver { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                   virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
                   virtual void v10(); virtual void v11(); virtual void v12();
                   virtual void Resolve(Handle* h); };                                  // +0x34
struct IViewportInfo { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                       virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
                       virtual void Query(uint32_t a, uint32_t b, int* px, int* py, int* w, int* h); }; // +0x24
IResolver* __cdecl GetResolver();       // 0x0067dd60
IViewportInfo* __cdecl GetViewportInfo(); // 0x0067dda0
struct ShaderIds { char pad[4]; uint32_t id; };      // [ptr+4] is the shader id
struct ShaderTable { char pad34[0x34]; ShaderIds* s34; ShaderIds* s38; ShaderIds* s3c; };
ShaderTable* __cdecl GetShaderTable();    // 0x00f48a60
void __cdecl SetShaderConst(int slot, const void* data, int zero);   // 0x00777ae0
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
// ---- items of slice s00f6a960 end

// ---- items of slice s00f6b9a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace TE {
struct Rect_s00f6_b9a0 {
    float l, t, r, b;
    float Width() const { return r - l; }
    float Height() const { return b - t; }
};
}
namespace TE {
struct MinMax { float mn, mx; };
}
namespace TE {
struct Raster {
    uint32_t pad0[3];
    uint16_t width;            // +0x0c
    uint16_t height;           // +0x0e
    uint8_t depth;             // +0x10 (bits per pixel)
    // read back the pixels into dst (anonymous_namespace::FillSpriteTexture, thiscall ret 0xc)
    void ReadPixels(uint32_t* dst, uint32_t bytes, int offset);   // 0x011F0440
};
}
namespace TE {
struct HeightData {
    uint32_t pad0[2];
    int mSide;                 // +0x08
    int mVersion;              // +0x0c
    uint16_t* mSamples;        // +0x10  [face][side*side]
};
}
namespace TE {
struct HeightMap {
    uint32_t pad0[2];
    HeightData* mpData;        // +0x08
    char pad0c[0x50 - 0x0c];
    float mMinHeight;          // +0x50
    float mMaxHeight;          // +0x54
    void SetRange(const MinMax* r);                               // 0x00F92520 (thiscall, ret 4)
};
}
namespace TE {
struct cTerrainSphere {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual HeightMap* GetHeightMap();                            // +0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void Notify(int flag);                                // +0x48
    void Relevel(float a, int b);                                 // 0x00FA43E0 (thiscall, ret 8)
    void MarkFaceDirty(int face, const Rect_s00f6_b9a0* r);                  // 0x00F99AC0 (thiscall, ret 8)
};
}
namespace TE {
struct IMessageServer {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void Post(uint32_t id, int a, int b);                 // +0x14
};
}
namespace TE {
IMessageServer* MessageServer();                                  // 0x0067DCC0
}
namespace TE {
struct U32Vector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void resize(uint32_t n);                                      // 0x004CD3C0 (thiscall, ret 4)
};
}
namespace TE {
extern void* g_gate;                                              // 0x015B0E48: self-referencing pointer
}
namespace TE {
extern const float kMinTileFraction;                              // 0x013EB8A0 constant 0.25f
}
namespace TE {
extern const float kHeightUnit;                                   // 0x0140D4F8 (1/32768)
}
namespace TE {
template <class T> inline const T& Min(const T& a, const T& b) { return b < a ? b : a; }
}
namespace TE {
template <class T> inline const T& Max(const T& a, const T& b) { return a < b ? b : a; }
}
namespace TE {
struct cTerrainEditor {
    char pad0[0x20];
    Raster* mHeightRaster[6];           // +0x20
    char pad38[0x74 - 0x38];
    cTerrainSphere* mpSphere;           // +0x74
    char pad78[0x80 - 0x78];
    Rect_s00f6_b9a0 mDirty[6];                     // +0x80
    char pade0[0x140 - 0xe0];
    uint16_t mMinMax[6][2];             // +0x140: per face {min, max} heights
    char pad158[0x168 - 0x158];
    U32Vector mTemp;                    // +0x168

    bool ReadTile(int face, const int* rect, float a);            // 0x00F69F50 (thiscall, ret 0xc)
    bool UpdateCPUFromGPU(float elapsed);
};
}
namespace TE {
static __forceinline void ClearRect(Rect_s00f6_b9a0& r) { r.l = 0.0f; r.t = 0.0f; r.r = 0.0f; r.b = 0.0f; }
}
// ---- items of slice s00f6b9a0 end

// @ 0x00f6a960
bool Compositor::Draw(Source* src, const uint32_t* raster, int a3, Rect r, float v0, float v1, float v2, int a11, void* a12)
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

// @ 0x00f6bd70
namespace TE {
bool cTerrainEditor::UpdateCPUFromGPU(float elapsed)
{
    cTerrainSphere* sphere = mpSphere;
    if (sphere == 0 || g_gate != (void*)&g_gate)
        return false;

    const float eps = 0.001953125f;
    bool dirty = false;
    for (int i = 0; i < 5; i++) {
        Rect_s00f6_b9a0& r = mDirty[i];
        if (r.l != r.r && r.t != r.b) {
            if (r.Width() < eps || r.Height() < eps)
                ClearRect(r);
            else
                dirty = true;
        }
    }
    {
        Rect_s00f6_b9a0& r = mDirty[5];
        if (r.l != r.r && r.t != r.b) {
            if (r.Width() < eps || r.Height() < eps)
                ClearRect(r);
            else
                goto relevel;
        }
    }
    if (!dirty)
        return true;
relevel:
    sphere->Relevel(elapsed, 0);

    {
        Raster* raster = mHeightRaster[0];
        const uint32_t width = raster->width;
        const uint32_t height = raster->height;
        const uint32_t bytesPerPixel = raster->depth >> 3;
        HeightData* heights = mpSphere->GetHeightMap()->mpData;
        bool anyUpdated = false;
        uint16_t* minMax = &mMinMax[0][0];

        for (int face = 0; face < 6; face++, minMax += 2) {
            Rect_s00f6_b9a0& r = mDirty[face];
            if (r.l != r.r && r.t != r.b) {
                static float sFullFraction = kMinTileFraction;
                uint16_t mn = 0xffff;
                uint16_t mx = 0;
                uint16_t* src = heights->mSamples + heights->mSide * heights->mSide * face;
                if (sFullFraction <= r.Width() || sFullFraction <= r.Height()) {
                    // large dirty area: read the whole face back
                    const uint32_t count = height * width;
                    mTemp.resize(count);
                    uint32_t* buf = mTemp.mpBegin;
                    mHeightRaster[face]->ReadPixels(buf, bytesPerPixel * height * width, 0);
                    anyUpdated = true;
                    uint16_t* dst = src;
                    for (uint32_t i = 0; i < count; i++) {
                        const uint16_t v = (uint16_t)(buf[i] >> 8);
                        dst[i] = v;
                        if (v < mn) mn = v;
                        if (mx < v) mx = v;
                    }
                } else {
                    // small dirty area: read it back in 64x64 tiles
                    const float fh = (float)height;
                    const float fw = (float)width;
                    const int row1 = (int)(r.b * fh);
                    const int col1 = (int)(r.r * fw);
                    const int row0 = (int)(r.t * fh);
                    const int col0 = (int)(r.l * fw);
                    const int nrows = (((uint32_t)(row1 - row0) - 1) >> 6) + 1;
                    const int ncols = (((uint32_t)(col1 - col0) - 1) >> 6) + 1;
                    int y = row0;
                    for (int rb = 0; rb < nrows; rb++, y += 0x40) {
                        int x = col0;
                        for (int cb = 0; cb < ncols; cb++, x += 0x40) {
                            int tile[4];
                            tile[0] = x;
                            tile[1] = y;
                            tile[2] = x + 0x40;
                            tile[3] = y + 0x40;
                            if (!ReadTile(face, tile, elapsed))
                                return false;
                        }
                    }
                    anyUpdated = true;
                    const uint32_t count = height * width;
                    for (uint32_t i = 0; i < count; i++) {
                        const uint16_t v = src[i];
                        if (v < mn) mn = v;
                        if (mx < v) mx = v;
                    }
                }
                minMax[0] = mn;
                minMax[1] = mx;
                mpSphere->MarkFaceDirty(face, &r);
                mpSphere->Notify(1);
            }
        }

        for (int i = 0; i < 6; i++)
            ClearRect(mDirty[i]);

        if (anyUpdated) {
            uint16_t lo = 0xffff;
            uint16_t hi = 0;
            lo = Min(lo, mMinMax[0][0]); hi = Max(hi, mMinMax[0][1]);
            lo = Min(lo, mMinMax[1][0]); hi = Max(hi, mMinMax[1][1]);
            lo = Min(lo, mMinMax[2][0]); hi = Max(hi, mMinMax[2][1]);
            lo = Min(lo, mMinMax[3][0]); hi = Max(hi, mMinMax[3][1]);
            lo = Min(lo, mMinMax[4][0]); hi = Max(hi, mMinMax[4][1]);
            lo = Min(lo, mMinMax[5][0]); hi = Max(hi, mMinMax[5][1]);
            MinMax range;
            range.mn = (float)((int)lo - 0x8000) * kHeightUnit;
            range.mx = (float)((int)hi - 0x8000) * kHeightUnit;
            mpSphere->GetHeightMap()->SetRange(&range);
        }
        mpSphere->GetHeightMap()->mpData->mVersion++;
        MessageServer()->Post(0x44448ed, 0, 0);
    }
    return true;
}
}  // namespace TE
