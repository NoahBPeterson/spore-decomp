// s00f9df20: 0x00f9e4d0 (scatter-texture pass: refreshes the six scatter cube faces, or draws one face quad)
#include "types.h"

struct Raster;
struct Viewer;

// Lazily-resolved resource handle: {object, flags}; bit 0 of flags = resolved.
struct LazyRes {
    Raster* p;
    uint32_t flags;
    uint32_t Get();     // 0x0046f260 (out-of-line: resolve, then return p)
};

struct ResMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void Resolve(LazyRes* h);      // slot 13 (+0x34)
};
extern ResMgr* __cdecl GetResMgr();        // 0x0067dd60

static inline Raster* ResolveRaster(LazyRes* h)
{
    if (!(h->flags & 1)) {
        GetResMgr()->Resolve(h);
    }
    return h->p;
}

struct TexHandleBox { uint32_t h; };
struct HandlePtr { uint32_t* p; };

struct Raster {
    char pad[0x12];
    uint8_t m_face;
    uint32_t Fill(int zero);                                                  // 0x011f0000
    void FillSpriteTexture(uint32_t pixels, uint32_t bytes, int zero);        // 0x011f0440
    int Lock(int mode, int zero, uint32_t* out);                              // 0x011ef750
    void Unlock(uint32_t* info);                                              // 0x011ef880
};

struct Viewer {
    void SetRaster(LazyRes* r, int flag);   // 0x007c4be0
    bool Update();                          // 0x007c4fd0
    void Finish();                          // 0x007c3c10
};

struct CompiledState { void Dispatch(); };  // 0x011ee580
struct Material { uint32_t pad; CompiledState* cs; };
struct MaterialManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual Material* GetMaterial(uint32_t key);   // slot 10 (+0x28)
};
extern MaterialManager* __cdecl GetMaterialManager();   // 0x0067dd70

struct AppIface2 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6();
    virtual uint32_t Get();    // slot 7 (+0x1c)
};
struct AppIface {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual AppIface2* Get();  // slot 20 (+0x50)
};
extern AppIface* __cdecl GetApp();                      // 0x0067dd10

struct ShConst {
    float v[60];
    void Zero();                                        // 0x0077d170
    void Set(int idx, float x, float y, float z, float w);   // 0x0077ca20
};

struct CfgBlock {          // terrain state + 0x2f4
    uint32_t pad0;
    uint32_t* p4;         // +0x04
    uint32_t pad1[2];
    uint32_t* p10;        // +0x10
    uint32_t pad2;
    LazyRes* h18;          // +0x18
    uint32_t pad3[2];
    LazyRes* h24;          // +0x24
    uint32_t* p28;        // +0x28
};

struct CamObj {            // result of Terrain::GetCam (+0x34..+0x3c)
    char pad[0x34];
    float x, y, z;
};

struct StateObj {
    char pad[0x2f4];
    CfgBlock cfg;          // +0x2f4
    float GetF();          // 0x00fb8a00
    float GetG();          // 0x00fb88d0
    void Compute(float* out);   // 0x00fb9ad0
};

struct TerrainParams {
    char pad[0x42c];
    float a, b, c;         // +0x42c
    void Setup(uint32_t h, float f, int n);   // 0x00fbf570
};

struct Terrain {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual CamObj* GetCam();         // slot 3 (+0xc)
    virtual StateObj* GetState();     // slot 4 (+0x10)
    uint32_t pad0[0x51];
    uint32_t* arrA[6];               // +0x148
    uint32_t* arrB[6];               // +0x160
    uint32_t pad1[0x25];
    TerrainParams* params;            // +0x20c
    uint32_t pad2[0x1a0];
    LazyRes* hTex;                    // +0x890
    uint32_t pad3[4];
    int lastFace;                     // +0x8a4
    void UpdateScatterTexture(int face, Raster* dst, const void* data, uint32_t arg);   // 0x00f9d9b0
    void RefreshA();                  // 0x00f98970
};

struct PlanetPass {
    uint32_t pad0[3];
    Terrain* terrain;      // +0x0c
    int mode;              // +0x10
    int face;              // +0x14
    LazyRes raster;        // +0x18
    Viewer* viewer;        // +0x20
    void Run(uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00f9e4d0
};

struct BigThing { char pad[0x434]; float f; };

extern uint32_t g_16fa3a8;          // 0x016fa3a8 raster stage dirty bits
extern uint32_t g_16f9674;          // 0x016f9674
extern LazyRes* g_16c9f54;          // 0x016c9f54
extern uint8_t g_15b11a0[];          // 0x015b11a0
extern uint32_t g_15b1150[];       // 0x015b1150
extern uint32_t g_15b115c[];       // 0x015b115c
extern uint32_t g_15b1168[];       // 0x015b1168
extern uint32_t* g_16c9e44[6];     // 0x016c9e44
extern uint8_t g_1490418[];         // 0x01490418

extern uint32_t __cdecl GetTerraformPlanetType(float f);         // 0x00fc1fd0
extern void __cdecl SetTexture(int slot, uint32_t h);             // 0x006dd2e0
extern bool __cdecl LockDraw(int a, int b, float** out, void* info);   // 0x006ddcc0
extern void __cdecl IssueDraw(int a, uint32_t b);                 // 0x006ddd10
extern "C" __declspec(nothrow) void* __cdecl memset(void*, int, unsigned int);   // 0x011e073e

struct Vec3f { float x, y, z; };
static inline Vec3f MkV(float x, float y, float z) { Vec3f r; r.x = x; r.y = y; r.z = z; return r; }
static inline void SetV(float* v, float x, float y, float z) { *(Vec3f*)v = MkV(x, y, z); }
static inline void PutF(float* d, float v) { union { float f; uint32_t u; } t; t.f = v; *(uint32_t*)d = t.u; }

// @ 0x00f9e4d0
void PlanetPass::Run(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    terrain->lastFace = -1;
    if (!viewer) {
        return;
    }
    if (mode == 3) {
        g_16fa3a8 |= 0x200;
        g_16f9674 = 0;
        uint32_t h = GetApp()->Get()->Get();
        terrain->params->Setup(h, 100.0f, 3);
        terrain->RefreshA();
        Raster* dst = ResolveRaster(g_16c9f54);
        for (int f = 0; f < 6; ++f) {
            terrain->UpdateScatterTexture(f, dst, g_15b11a0, d);
        }
        for (int i = 0; i < 6; ++i) {
            Raster* src = ResolveRaster(terrain->hTex);
            uint32_t info;
            src->m_face = (uint8_t)i;
            if (src->Lock(2, 0, &info)) {
                dst->m_face = (uint8_t)i;
                uint32_t n = dst->Fill(0);
                dst->FillSpriteTexture(info, n, 0);
                src->Unlock(&info);
            }
        }
        return;
    }

    viewer->SetRaster(&raster, 1);
    uint32_t tex[5];
    tex[0] = tex[1] = tex[2] = tex[3] = tex[4] = 0;
    uint32_t type = GetTerraformPlanetType(terrain->GetState()->GetF());
    CfgBlock* cfg = &terrain->GetState()->cfg;
    Material* mat;
    if (type & 1) {
        mat = GetMaterialManager()->GetMaterial(g_15b1150[mode]);
        switch (mode) {
        case 0:
            tex[0] = *g_16c9e44[face];
            tex[1] = *terrain->arrB[face];
            tex[2] = *cfg->p28;
            break;
        case 1:
            tex[0] = *terrain->arrB[face];
            break;
        case 2:
            tex[0] = *terrain->arrA[face];
            tex[1] = *terrain->arrB[face];
            break;
        }
    } else if (type == 2) {
        mat = GetMaterialManager()->GetMaterial(g_15b115c[mode]);
        switch (mode) {
        case 0:
            tex[0] = *g_16c9e44[face];
            tex[1] = *terrain->arrB[face];
            tex[2] = cfg->h24->Get();
            break;
        case 1:
            tex[0] = *terrain->arrB[face];
            break;
        case 2:
            tex[0] = *terrain->arrA[face];
            tex[1] = *terrain->arrB[face];
            break;
        }
    } else if (type == 4) {
        mat = GetMaterialManager()->GetMaterial(g_15b1168[mode]);
        switch (mode) {
        case 0:
            tex[0] = *g_16c9e44[face];
            tex[1] = *terrain->arrB[face];
            tex[2] = cfg->h18->Get();
            tex[3] = *cfg->p10;
            tex[4] = *cfg->p4;
            break;
        case 1:
            tex[0] = *terrain->arrB[face];
            tex[1] = cfg->h18->Get();
            break;
        case 2:
            tex[0] = *terrain->arrA[face];
            break;
        }
    } else {
        return;
    }

    bool flipX = false, flipY = false, alt = false;
    switch (face) {
    case 0: flipX = true; alt = false; flipY = true; break;
    case 1:
    case 2:
    case 3: flipX = false; flipY = false; alt = false; break;
    case 4: flipX = true; flipY = false; alt = true; break;
    case 5: flipX = false; alt = true; flipY = true; break;
    }

    float sgn = (face & 1) ? -1.0f : 1.0f;
    float sv[3];
    sv[0] = sgn; sv[1] = 1.0f; sv[2] = sgn;
    const uint8_t* ax = &g_1490418[(face >> 1) * 4];
    int i0 = ax[0], i1 = ax[1], i2 = ax[2];
    TerrainParams* tp = terrain->params;
    float p0 = sv[i0], p1 = sv[i1], p2 = sv[i2];
    float q[3];
    q[0] = tp->a; q[1] = tp->b; q[2] = tp->c;
    float out4[4];
    terrain->GetState()->Compute(out4);
    ShConst sh;
    sh.Zero();
    CamObj* cam = terrain->GetCam();
    float cx = cam->x, cy = cam->y, cz = cam->z;
    sh.Set(0, cx, cy, cz, terrain->GetState()->GetG());
    sh.Set(1, q[0], q[1], q[2], 0.0f);
    sh.Set(2, (float)i0, (float)i1, (float)i2, 0.0f);
    sh.Set(3, p0, p1, p2, 0.0f);
    sh.Set(4, out4[0], out4[1], out4[2], out4[3]);

    if (viewer->Update()) {
        float* vb;
        uint32_t lockInfo;
        if (LockDraw(2, 4, &vb, &lockInfo)) {
            memset(vb, 0, 0x60);
            PutF(vb + 4, 0.0f); PutF(vb + 5, 0.0f);
            PutF(vb + 10, 1.0f); PutF(vb + 11, 0.0f);
            PutF(vb + 16, 1.0f); PutF(vb + 17, 1.0f);
            PutF(vb + 22, 0.0f); PutF(vb + 23, 1.0f);
            if (alt) {
                SetV(vb + 0, 1.0f, 1.0f, 0.2f);
                SetV(vb + 6, 1.0f, -1.0f, 0.2f);
                SetV(vb + 12, -1.0f, -1.0f, 0.2f);
                SetV(vb + 18, -1.0f, 1.0f, 0.2f);
            } else {
                SetV(vb + 0, 1.0f, 1.0f, 0.2f);
                SetV(vb + 6, -1.0f, 1.0f, 0.2f);
                SetV(vb + 12, -1.0f, -1.0f, 0.2f);
                SetV(vb + 18, 1.0f, -1.0f, 0.2f);
            }
            if (flipX) {
                vb[0] = -vb[0]; vb[6] = -vb[6]; vb[12] = -vb[12]; vb[18] = -vb[18];
            }
            if (flipY) {
                vb[1] = -vb[1]; vb[7] = -vb[7]; vb[13] = -vb[13]; vb[19] = -vb[19];
            }
            mat->cs->Dispatch();
            SetTexture(0, tex[0]);
            SetTexture(1, tex[1]);
            SetTexture(2, tex[2]);
            SetTexture(3, tex[3]);
            SetTexture(4, tex[4]);
            IssueDraw(3, d);
        }
        viewer->Finish();
    }
}
