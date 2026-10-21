// Slice s00f708d0: a cube-face sampling / terrain-blend query class (11 members).
// Built /O2.
#include "types.h"

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// Small helpers / external functions (addresses as named in the cards).
// ---------------------------------------------------------------------------
struct V4 {
    float x, y, z, w;
};

float SampleBilinear(void* cubeImage, V4* uv);            // 0x00f8de70 SP::cCubeImage::SampleBilinear
float FbPtr9e70(void* p, float t);                        // 0x00fb9e70
float TerrainFloatU16(void* map, V4* uv);                 // 0x00f88650
float TerrainFloatU32(void* map, V4* uv);                 // 0x00f8d620
V4*   TerrainGetVector4(V4* out, V4* uv);                 // 0x00f89e50
void* EffectsManager();                                   // 0x0067ddd0
void  Matrix33Assign(void* out, const void* src);         // 0x0041cb40
void  GetCameraLocationInfo(void* viewer, V4* out, int, int, int); // 0x007c3d30
void  GetCameraDirInfo(void* viewer, V4* out);            // 0x00fb8db0

extern float DAT_01485720;    // 1.0f
extern float DAT_01471064;    // 0.5f
extern float DAT_01485378;    // 0.0f
extern float DAT_013ec478;    // 0.05f
extern float DAT_013ec4b8;    // 1e-08f
extern float DAT_013f7344;    // 0.95f
extern const float DAT_016c9a20;

// Effects-manager interface handed out by EffectsManager vtable slot 0x8c.
// Members are called through explicit vtable slots because the real interface
// has dozens of entries we do not model.
struct IEff {
    void** mpVtbl;
};
inline void*  EffGet(void* mgr, unsigned int key, void* p) { return ((void*(*)(void*,unsigned int,void*))(((void**)mgr)[0x8c/4]))(mgr, key, p); }
inline void   EffAddRef(IEff* e)                           { ((void(*)(IEff*))(e->mpVtbl[0]))(e); }
inline void   EffRelease(IEff* e)                          { ((void(*)(IEff*))(e->mpVtbl[1]))(e); }
inline float  EffCall10(IEff* e)                           { return ((float(*)(IEff*))(e->mpVtbl[0x10/4]))(e); }
inline float  EffCall20(IEff* e, const V4* dir)            { return ((float(*)(IEff*,const V4*))(e->mpVtbl[0x20/4]))(e, dir); }

void EAFreeOp(void* p);       // 0x00f47380

inline float AbsF(float f) { return f < 0.0f ? -f : f; }
float SqrtF(float f);         // 0x006be790 (linker-resolved CRT sqrt helper)

// ---------------------------------------------------------------------------
// The query object.
// ---------------------------------------------------------------------------
struct CCubeQuery {
    char pad0[0x0c];
    struct Ctx* mpCtx;        // +0x0c
    struct Terrain* mpTerrain; // +0x10
    struct Viewer* mpViewer;   // +0x14
    void* mpSlot;              // +0x18
    // member functions
    float QueryA(const V4* dir);       // 0x00f708d0
    float QueryB(const V4* dir);       // 0x00f70c30
    float QueryC(const V4* dir);       // 0x00f70fa0
    float QueryD(const V4* dir);       // 0x00f71220
    V4*   GetCubeUV(V4* out);          // 0x00f713c0
    V4*   DirToTerrainColor(V4* out, const V4* dir);  // 0x00f713e0
    V4*   GetColorA(V4* out);          // 0x00f715d0
    V4*   GetColorB(V4* out);          // 0x00f71610
    V4*   GetScaledColor(V4* out, const V4* unused);  // 0x00f716b0
};

struct Ctx {
    char pad0[8];
    void* mpMapA;             // +0x08
    void* mpMapB;             // +0x0c
    void* mpCube;             // +0x10
    void* mpUV;               // +0x14
    char pad1[0x38 - 0x18];
    float f38;                // +0x38
    float f3c;                // +0x3c
    float f40;                // +0x40
    float f44;                // +0x44
    float f48;                // +0x48
};

struct Terrain {
    char pad0[0x2f4];
    char body[0x2f4];         // +0x2f4 base
};

struct Viewer {
    char pad0[0x14];
    void* mpCubeImage;        // +0x14
};

// ---------------------------------------------------------------------------
// Shared cube-face UV selection. Given a direction, produce (u, v, face).
// ---------------------------------------------------------------------------
static void CubeUV(const V4* dir, float* uv, uint* face)
{
    float cx = dir->x, cy = dir->y, cz = dir->z;
    float ax = AbsF(cx), ay = AbsF(cy), az = AbsF(cz);
    if (az >= ax && az >= ay) {
        uv[0] = (cx / cz + 1.0f) * 0.5f;
        uv[1] = (cy / az + 1.0f) * 0.5f;
        *face = cz < 0.0f ? 1 : 0;
    } else if (ay >= ax) {
        uv[0] = (cz / cy + 1.0f) * 0.5f;
        uv[1] = (cx / ay + 1.0f) * 0.5f;
        *face = cy < 0.0f ? 5 : 4;
    } else {
        uv[0] = (cy / cx + 1.0f) * 0.5f;
        uv[1] = (cz / ax + 1.0f) * 0.5f;
        *face = cx < 0.0f ? 3 : 2;
    }
}

// ---------------------------------------------------------------------------
// A stored direction (x,y,z) with a cube-image lookup, used by 0xf715d0/0xf71610.
// ---------------------------------------------------------------------------
// @ 0x00f708d0
float CCubeQuery::QueryA(const V4* dir)
{
    float uv[2];
    uint face;
    V4  uv4;
    CubeUV(dir, uv, &face);

    Ctx* ctx = mpCtx;
    if (ctx->mpCube) {
        CubeUV(dir, &uv4.x, (uint*)&uv4.z);   // recomputed for the bilinear tap
        uv4.w = uv4.z;
        float s = SampleBilinear(&uv4, &uv4);
        (void)s;
        float t = FbPtr9e70(mpTerrain, s);
        if (t > DAT_013ec478)
            goto Lfail;
    }
    if (ctx->mpMapA) {
        float f = ctx->f38;
        V4 tap;
        tap.x = (ctx->f44 + ctx->f3c) * f;
        tap.y = ctx->f48;
        float terrain = TerrainFloatU32(ctx->mpMapA, &tap);
        if (terrain * f >= tap.x)
            goto Lfail;
    }
    {
        IEff* eff = (IEff*)EffGet(EffectsManager(), 0x107ae878, 0);
        if (eff) {
            EffAddRef(eff);
            float r = EffCall20(eff, dir);
            EffRelease(eff);
            if (r != 0.0f)
                return 1.0f;
        }
    }
Lfail:
    return 0.0f;
}

// @ 0x00f70c30
float CCubeQuery::QueryB(const V4* dir)
{
    float uv[2];
    uint face;
    V4  uv4;
    CubeUV(dir, uv, &face);

    Ctx* ctx = mpCtx;
    if (ctx->mpCube) {
        CubeUV(dir, &uv4.x, (uint*)&uv4.z);
        uv4.w = uv4.z;
        float s = SampleBilinear(&uv4, &uv4);
        float t = FbPtr9e70(mpTerrain, s);
        if (t >= DAT_013ec478)
            goto Lfail;
    }
    if (ctx->mpMapA) {
        float f = ctx->f38;
        V4 tap;
        tap.x = (ctx->f44 + ctx->f3c) * f;
        tap.y = ctx->f48;
        float terrain = TerrainFloatU16(ctx->mpMapA, &tap);
        if (terrain * f <= tap.x)
            goto Lfail;
    }
    {
        IEff* eff = (IEff*)EffGet(EffectsManager(), 0x107ae878, 0);
        if (eff) {
            EffAddRef(eff);
            float r = EffCall20(eff, dir);
            EffRelease(eff);
            if (r != 0.0f)
                return 1.0f;
        }
    }
Lfail:
    return 0.0f;
}

// @ 0x00f70fa0
float CCubeQuery::QueryC(const V4* dir)
{
    float uv[2];
    uint face;
    CubeUV(dir, uv, &face);

    Ctx* ctx = mpCtx;
    if (ctx->mpCube) {
        float s = SampleBilinear(&uv[0], (V4*)&uv[0]);
        float t = FbPtr9e70(mpTerrain, s);
        if (t < 0.95f)
            return 0.0f;
    }
    if (ctx->mpMapA && ctx->mpMapB) {
        float f = ctx->f38;
        float hi = ctx->f48;
        float lo = (ctx->f44 + ctx->f3c) * f;
        float a = TerrainFloatU32(ctx->mpMapA, (V4*)&uv[0]);
        if (!(hi <= a * f))
            goto Lcheck2;
        return 0.0f;
    Lcheck2:
        {
            float b = TerrainFloatU16(ctx->mpMapB, (V4*)&uv[0]);
            if (!(b * f <= lo))
                goto Lcheck3;
            return 0.0f;
        }
    }
Lcheck3:
    {
        IEff* eff = (IEff*)EffGet(EffectsManager(), 0x107ae878, 0);
        if (eff) {
            EffAddRef(eff);
            float r = EffCall20(eff, dir);
            EffRelease(eff);
            if (r != 0.0f)
                return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00f71220
float CCubeQuery::QueryD(const V4* dir)
{
    float m[9];
    V4 camLoc;
    V4 camDir;

    Matrix33Assign(m, &DAT_016c9a20);
    GetCameraLocationInfo(mpViewer, &camLoc, 0, 0, 0);
    GetCameraDirInfo(mpViewer, &camDir);

    float dx = dir->x, dy = dir->y, dz = dir->z;
    float dscale = 1.0f / SqrtF((dx * dx + dy * dy + dz * dz) + DAT_013ec4b8);
    float cscale = 1.0f / SqrtF(camLoc.x * camLoc.x + camLoc.y * camLoc.y + camLoc.z * camLoc.z);

    camDir.x += cscale * camLoc.x;
    camDir.y += camLoc.y * cscale;
    camDir.z += camLoc.z * cscale;

    float nscale = 1.0f / SqrtF(camDir.x * camDir.x + camDir.y * camDir.y + camDir.z * camDir.z);
    float dot = (camDir.z * nscale) * (dz * dscale)
              + (camDir.y * nscale) * (dy * dscale)
              + (nscale * camDir.x) * (dscale * dx);

    float v = dot;
    if (v < 0.0f)
        v = 0.0f;
    if (v > 1.0f)
        v = 1.0f;
    float v2 = v * v;
    return v2 * v2;
}

// @ 0x00f713c0
V4* CCubeQuery::GetCubeUV(V4* out)
{
    void* p = mpCtx->mpUV;
    if (!p)
        return 0;
    (void)out;
    return (V4*)((char*)p + 0x0c);
}

// @ 0x00f713e0
V4* CCubeQuery::DirToTerrainColor(V4* out, const V4* dir)
{
    if (!mpCtx->mpUV) {
        out->x = 1.0f; out->y = 1.0f; out->z = 1.0f; out->w = 1.0f;
        return out;
    }
    float uv2[2];
    uint face;
    CubeUV(dir, uv2, &face);
    {
        V4 key;
        key.x = uv2[0];
        key.y = uv2[1];
        key.z = (float)face;
        V4* r = TerrainGetVector4(&key, &key);
        out->x = r->x; out->y = r->y; out->z = r->z;
    }
    out->w = 1.0f;
    return out;
}

// @ 0x00f715d0
V4* CCubeQuery::GetColorA(V4* out)
{
    const float* p = (const float*)((char*)mpTerrain + 0x42c);
    out->w = DAT_01485720;
    out->x = p[0];
    out->y = p[1];
    out->z = p[2];
    return out;
}

// @ 0x00f71610
V4* CCubeQuery::GetColorB(V4* out)
{
    const float* p = (const float*)((char*)mpTerrain + 0x59c);
    out->x = p[0];
    out->y = p[1];
    out->w = DAT_01485720;
    out->z = p[2];
    return out;
}

// @ 0x00f71660
int QueryScaleA()
{
    IEff* eff = (IEff*)EffGet(EffectsManager(), 0x107ae878, 0);
    if (!eff)
        return 0;
    EffAddRef(eff);
    int r = (int)EffCall10(eff);
    EffRelease(eff);
    return r;
}

// @ 0x00f716b0
V4* CCubeQuery::GetScaledColor(V4* out, const V4* unused)
{
    IEff* eff = (IEff*)EffGet(EffectsManager(), 0x107ae878, 0);
    if (eff)
        EffAddRef(eff);
    float s = 1.0f;
    if (eff) {
        s = EffCall20(eff, unused);
        if (eff)
            EffRelease(eff);
    }
    const float* p = (const float*)((char*)mpTerrain + 0x59c);
    out->x = p[0] * s;
    out->y = p[1] * s;
    out->z = p[2] * s;
    out->w = s;
    if (eff)
        EffRelease(eff);
    return out;
}

// @ 0x00f71760
void* RefCountedDtor(void* self, unsigned char flags)
{
    int* rc = *(int**)((char*)self + 0x0c);
    if (rc) {
        int n = rc[1] - 1;
        rc[1] = n;
        if (n == 0) {
            rc[1] = 1;
            (*(void(**)(int))(*rc))(1);
        }
    }
    *(void**)((char*)self + 4) = (void*)0x013ef094;
    if (flags & 1)
        EAFreeOp(self);
    return self;
}
