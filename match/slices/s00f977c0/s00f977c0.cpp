// Slice s00f977c0 -- SP::cTerrainSphere  (SPTerrainSphere.obj)
// 0x00f977c0 effects-system registration, quad-LOD predicate, quad-stream tests, the per-frame
// render-job driver, the sky/water/atmosphere quad draws and the per-face bbox merge.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

// ---- globals -----------------------------------------------------------------------------------
extern uint32_t g_16ca590[4];        // 0x016ca590
extern uint32_t g_16ca5a0;           // 0x016ca5a0  static-init guard
extern uint32_t g_16f65a0;           // 0x016f65a0  active vertex descriptor
extern uint32_t g_16c9e78;           // 0x016c9e78  wanted vertex descriptor
extern uint32_t g_16f9110;           // 0x016f9110  soft-state-dirty flags
extern uint8_t  g_16ca3d4[];         // 0x016ca3d4  terrain-editor rect-id table
extern void*    g_sAppProps;         // 0x015fd918  SP::App::sAppProperties
extern const float  C_1485720;       // 0x01485720 = 1.0f
extern const float  C_1471064;       // 0x01471064 effect scale
extern const float  C_13eb8b0;       // 0x013eb8b0 sign mask
extern const float  C_13f9428;       // 0x013f9428 lod epsilon
extern const float  C_15b118c;       // 0x015b118c fov scale
extern const float  C_13ec4b8;       // 0x013ec4b8 1e-08f
extern const float  C_13eb1bc;       // 0x013eb1bc -1.0f
extern const double C_13f1298;       // 0x013f1298 2.0

// ---- helpers -----------------------------------------------------------------------------------
void*  __cdecl FUN_0067ddd0();                       // 0x0067ddd0  SP::EffectsManager
void*  __cdecl FUN_0067dd60();                       // 0x0067dd60  EA::ResourceManager
void   __cdecl FUN_00fb9aa0(float a, float b, float c);                 // 0x00fb9aa0
uint32_t* __cdecl FUN_00fb9ad0(uint32_t* out);       // 0x00fb9ad0
float  __cdecl FUN_00fb8a00(void* mapset);           // 0x00fb8a00
uint32_t __cdecl GetTerraformPlanetType(float r);    // 0x00fc1fd0
void   __cdecl FUN_00777ae0(uint32_t shader, const void* data, int zero); // 0x00777ae0
typedef void (__thiscall *tq2)(void*, void*, uint32_t, uint32_t);
typedef void (__thiscall *tq3)(void*, void*, uint32_t, uint32_t, uint32_t);
typedef void (__thiscall *tq4)(void*, uint32_t, uint32_t, int);
void   __cdecl FUN_00fb66d0x();
void   __cdecl FUN_00fb6850x();
void   __cdecl FUN_00fb6cd0x();
void   __cdecl FUN_00fb6e00x();
void   __cdecl FUN_00fb3040x();
int    __cdecl rw_VertexDescriptor_AreEqual(const void* a, const void* b); // 0x011f2e70
void   __fastcall rw_VertexDescriptor_SetActive(void* self);             // 0x011f2bc0
void   __fastcall FUN_007c3c10(void* self);           // 0x007c3c10
bool   __fastcall FUN_007c4fd0(void* self);           // 0x007c4fd0
void*  __cdecl FUN_00f48a70();                       // 0x00f48a70  TerrainEditor / Compositor
bool   __cdecl FUN_00f678a0();                       // 0x00f678a0
bool   __cdecl FUN_00fad140(void* decal, int face, float* box);   // 0x00fad140
bool   __cdecl FUN_00fad550(void* decal, int face, uint32_t a);    // 0x00fad550
bool   __cdecl FUN_00f6a960(void* src, const uint32_t* rectId, int face,
                            float l, float t, float r, float b,
                            int a, int c, float one, float one2, void* g);
uint32_t* __cdecl FUN_00700120(void* frustum, const void* a, const void* b, int c);
typedef uint32_t (__fastcall *tFrust)(void* self, void* pad, const void* a, const void* b, int c);
float  __cdecl FUN_00f63e10(float x);                // 0x00f63e10 sqrt helper used by the quad test
extern "C" int __stdcall QueryPerformanceCounter_imp(long long* out);  // IAT 0x013cc2b8

bool  __cdecl GetDescription(void* list, uint32_t id);                 // 0x006a25a0

struct cPropertyList {
    bool GetDescription(uint32_t id);        // 0x006a25a0 __thiscall ret 4
};

// cViewer
struct cViewer {
    void  SetRaster(const void* a, int b);   // vtable +0x34
    bool  Update();                          // 0x007c3c10 -> bool
};

// EA::Stopwatch / EA::LimitStopwatch (0x93a560 / 0x93a480, thiscall)
struct cStopwatch {
    uint32_t m00, m04, m08, m0c, m10, m14;
};
struct cLimitStopwatch : cStopwatch {
    long long mnEndTime;                     // +0x18
    void Construct(int n, bool b);           // 0x93a560
    void SetTimeLimit(uint32_t ms, bool b);  // 0x93a480
};

struct ViewFrame {
    uint32_t m00, m04;
    uint8_t  m08;
    uint8_t  pad09[3];
    uint8_t  m0c, m0d, m0e, m0f;
    uint8_t  pad10[0x30 - 0x10];
    float    m30;                            // +0x30
    float    m34;                            // +0x34
    float    m38;                            // +0x38
    float    m3c;                            // +0x3c
    uint8_t  pad40[0x64 - 0x40];
    float    m64;                            // +0x64 lod result
    float    m68;                            // +0x68 bearing
    uint8_t  pad6c[0x88 - 0x6c];
    float    m88;                            // +0x88
    float    m8c;                            // +0x8c
    uint8_t  pad90[0x1d4 - 0x90];
    int32_t  m1d4;                           // +0x1d4
    uint8_t  pad1d8[0x2f4 - 0x1d8];
    void*    mStreams[14];                   // +0x2f4
};
struct AppHeader {                           // object at [0x15fd918]+0x3c
    uint8_t pad[0x84];
    float m84, m88, m8c;
};

struct PlanetHeader {                        // object at this+0x2c
    uint8_t pad[0x34];
    float m34, m38, m3c;
};

struct StateMgr {
    void FUN_00fb9aa0(float a, float b, float c);            // 0x00fb9aa0 (thiscall)
};

// quad/decal element: +0x00 object (vtable +0x00), +0x04 float key, +0x0c flags (0x40 = culled)
struct QuadEntry {
    void*    mpObj;         // +0x00
    float    mKey;          // +0x04
    uint32_t pad08;
    uint32_t mFlags;        // +0x0c
};

// view object with the 0x218 uniform/decal block table (stride 0x14)
struct cView {
    uint32_t pad0[0x218 / 4];
    struct Block {
        void*    mBegin;                  // +0x00
        void*    mEnd;                    // +0x04
        uint8_t  pad08[0x14 - 8];
    } mBlocks[4];                         // +0x218, stride 0x14
};

struct Raster {
    uint8_t pad0[0xb8];
    uint32_t mB8;
};

// ---- the terrain sphere -----------------------------------------------------------------------
#define V(n) virtual void v##n();
struct cTerrainSphere {
    V(0) V(1) V(2) V(3)
    virtual ViewFrame* GetViewFrame();                       // +0x10 (slot 4)
    virtual cView* GetView();                                // +0x14 (slot 5)

    void AddToEffectsSystem();                               // 0x00f977c0
    bool QuadDetailTest(const ViewFrame* frame, const float* verts, float* outDist);  // 0x00f97960
    bool AreRastersReady();                                  // 0x00f97c30
    void ReleaseRasters();                                   // 0x00f97d00
    bool RenderJobPass(uint32_t arg);                        // 0x00f97e60
    void DrawSkyQuads(uint32_t a, uint32_t b);               // 0x00f97f50
    void RenderWater(uint32_t a, uint32_t b);                // 0x00f98020
    void DrawWaterQuads(uint32_t a, uint32_t b);             // 0x00f98170
    void RenderAtmosphere(uint32_t a, uint32_t b);           // 0x00f981d0
    void DrawAtmoQuads(uint32_t a, uint32_t b);              // 0x00f98530
    bool UpdateAboveRaster(int face, const float* rect, uint32_t a3, uint32_t a4); // 0x00f98290
    void MergeFaceBox(int face, float l, float t, float r, float b);               // 0x00f98620
    uint32_t GetQuadKeyA(int idx);                           // 0x00f98260
    uint32_t GetQuadKeyB(int idx);                           // 0x00f98270
    uint32_t GetQuadKeyC(int idx);                           // 0x00f98280

    uint8_t  pad04[0x08 - 0x04];
    uint32_t m08;                                            // +0x008
    uint8_t  pad0c[0x2c - 0x0c];
    void*    mpPlanet;                                       // +0x02c
    uint8_t  pad30[0xfc - 0x30];
    cViewer* mpRenderJob;                                    // +0x0fc
    uint8_t  pad100[0x108 - 0x100];
    uint8_t  mSingleStep;                                    // +0x108
    uint8_t  pad109[3];
    float    mTimeLimitMs;                                   // +0x10c
    uint8_t  pad110[0x111 - 0x110];
    uint8_t  mFlag111;                                       // +0x111
    uint8_t  pad112[0x148 - 0x112];
    void**   mArr148;                                        // +0x148
    uint8_t  pad14c[0x160 - 0x14c];
    void**   mArr160;                                        // +0x160
    uint8_t  pad164[0x178 - 0x164];
    void**   mArr178;                                        // +0x178
    uint8_t  pad17c[0x190 - 0x17c];
    QuadEntry* mpQuadBegin;                                  // +0x190
    QuadEntry* mpQuadEnd;                                    // +0x194
    uint8_t  pad198[0x1a4 - 0x198];
    QuadEntry* mpQuad2Begin;                                 // +0x1a4
    QuadEntry* mpQuad2End;                                   // +0x1a8
    uint8_t  pad1ac[0x1b8 - 0x1ac];
    QuadEntry* mpQuad3Begin;                                 // +0x1b8
    QuadEntry* mpQuad3End;                                   // +0x1bc
    uint8_t  pad1c0[0x1d4 - 0x1c0];
    int32_t  m1d4;                                           // +0x1d4
    uint8_t  pad1d8[0x20c - 0x1d8];
    void*    mpStateMgr;                                     // +0x20c
    uint8_t  pad210[0x360 - 0x210];
    float    m360;                                           // +0x360
    float    m364;                                           // +0x364
    uint8_t  pad368[0x434 - 0x368];
    float    mFaceBox[6][4];                                 // +0x434
    uint8_t  pad494[0x8e4 - (0x434 + 6 * 16)];
    cViewer* mpViewer;                                       // +0x8e4
    uint8_t  pad8e8[0x92c - 0x8e8];
    uint8_t  mFrustum[0x3c];                                 // +0x92c
};
#undef V

// ---- code -------------------------------------------------------------------------------------
// @ 0x00f977c0
void cTerrainSphere::AddToEffectsSystem()
{
    void* mgr = FUN_0067ddd0();
    typedef void* (__thiscall *TGet)(void*, uint32_t, int);
    TGet get = (TGet)(*(void***)mgr)[0x7c / 4];
    void* found = get(mgr, 0x2e892928, 0);
    if (!found)
        return;

    PlanetHeader* planet = (PlanetHeader*)mpPlanet;
    float f34 = planet->m34;
    float f38 = planet->m38;
    float f3c = planet->m3c;

    StateMgr* sm = (StateMgr*)mpStateMgr;
    sm->FUN_00fb9aa0(f34, f38, f3c * f38);

    float dist = f34 * C_1471064;
    float add = f3c * C_1471064;

    void* e;
    e = get(mgr, 0x2e892928, 0);
    *(float*)((char*)e + 0x0c) = dist;
    *(float*)((char*)e + 0x10) = add;
    *(float*)((char*)e + 0x14) = -dist;
    e = get(mgr, 0x2e892929, 0);
    *(float*)((char*)e + 0x0c) = dist;
    *(float*)((char*)e + 0x10) = add;
    *(float*)((char*)e + 0x14) = dist;
    e = get(mgr, 0x2e89292b, 0);
    *(float*)((char*)e + 0x10) = add;
    *(float*)((char*)e + 0x14) = dist;
    *(float*)((char*)e + 0x0c) = dist;
    e = get(mgr, 0x2e89292a, 0);
    *(float*)((char*)e + 0x0c) = dist + add;
    e = get(mgr, 0x3598109, 0);
    *(float*)((char*)e + 0x0c) = f38;
    e = get(mgr, 0x4fe7337, 0);
    *(float*)((char*)e + 0x0c) = f38;
    m360 = f34;
    m364 = f3c;
    mFlag111 = 0;
}

// @ 0x00f97960
bool cTerrainSphere::QuadDetailTest(const ViewFrame* frame, const float* verts, float* outDist)
{
    cPropertyList* props = (cPropertyList*)g_sAppProps;
    if (props->GetDescription(0x2fbb4880))
        return true;

    float resf = (float)(int)(0x200 / m1d4);

    float f88 = frame->m88;
    float f8c = frame->m8c;
    float fx = frame->m34;
    float fy = frame->m38;
    float fz = frame->m3c;
    float f30 = frame->m30;

    AppHeader* app = (AppHeader*)(*(uint8_t**)&g_sAppProps)[0x3c];
    float t84 = app->m84;
    float t88 = app->m88;
    float t8c = app->m8c;

    float scale = (f8c + f88);
    float dx = verts[0] - fx * scale * C_1471064;
    float dy = verts[1] - fy * scale * C_1471064;
    float dz = verts[2] - fz * scale * C_1471064;
    *outDist = sqrtf(dz * dz + dy * dy + dx * dx);

    if (f30 < C_1485720 / resf + C_13f9428)
        goto tail;

    {
        float lim = (float)(sqrt(2.0) * C_15b118c * f30);
        float len = sqrtf(verts[0] * verts[0] + verts[1] * verts[1] + verts[2] * verts[2]) + C_13ec4b8;
        float lo = len < f88 ? f88 : len;
        if (f8c < lo)
            lo = f8c;
        float d = (verts[1] * fy + verts[2] * fz + verts[0] * fx) / len;
        if (d <= C_13eb1bc)
            d = C_13eb1bc;
        if (C_1485720 <= d)
            d = C_1485720;
        float ang = FUN_00f63e10(d);
        float w = ang - lim;
        if (!(0.0f < w))
            w = 0.0f;
        float band = (len - lo) * t8c;
        float lod = sqrtf(w * lo * (w * lo) + band * band) / f30;
        const_cast<ViewFrame*>(frame)->m68 = lod;
        if (lod < t84)
            return false;
    }
tail:
    {
        ViewFrame* vf = const_cast<ViewFrame*>(frame);
        float f64 = C_1485720;
        if (vf->m04) {
            float v = (t84 - *(float*)((char*)vf->m04 + 0x68)) / t88;
            f64 = v < 0.0f ? 0.0f : (C_1485720 < v ? C_1485720 : v);
        }
        vf->m64 = f64;
    }
    return true;
}

// @ 0x00f97c30
bool cTerrainSphere::AreRastersReady()
{
    void** p = &GetViewFrame()->mStreams[0];
#define R(i) do { uint32_t s = (uint32_t)p[i]; \
        if (s && !(*(uint8_t*)(s + 4) & 1)) return false; } while (0)
    R(0); R(1); R(2); R(3); R(4); R(5); R(6); R(7); R(8); R(9);
    R(10); R(11); R(12); R(13);
#undef R
    return true;
}

// @ 0x00f97d00
void cTerrainSphere::ReleaseRasters()
{
    char* b = (char*)GetViewFrame() + 0x2f4;
#define R(i) do { if (*(void**)(b + i * 4)) { \
        void* mgr = FUN_0067dd60(); \
        void** vt = *(void***)mgr; \
        ((void (__thiscall*)(void*, uint32_t))vt[0x34 / 4])(mgr, (uint32_t)*(void**)(b + i * 4)); \
    } } while (0)
    R(0); R(1); R(2); R(3); R(4); R(5); R(6); R(7); R(8); R(9);
    R(10); R(11); R(12); R(13);
#undef R
}

// @ 0x00f97e60
bool cTerrainSphere::RenderJobPass(uint32_t arg)
{
    cViewer* job = mpRenderJob;
    if (!mSingleStep) {
        if (!job)
            return true;
        long long ms = (long long)mTimeLimitMs;
        cLimitStopwatch sw;
        sw.Construct(4, false);
        sw.SetTimeLimit((uint32_t)ms, true);
        long long now;
        for (;;) {
            QueryPerformanceCounter_imp(&now);
            if ((int)(sw.mnEndTime - now) < 0)
                break;
            if (!mpRenderJob)
                break;
            if (!job->Update())
                return false;
        }
        return true;
    }
    if (job && !job->Update())
        return false;
    return true;
}

// @ 0x00f97f50
void cTerrainSphere::DrawSkyQuads(uint32_t a, uint32_t b)
{
    uint32_t n = (uint32_t)(mpQuadEnd - mpQuadBegin);
    if ((int)n <= 0)
        return;
    int off = 0;
    uint32_t cnt = n;
    do {
        char* e = (char*)mpQuadBegin + off;
        void* obj = *(void**)e;
        float key = *(float*)(e + 0x04);
        uint32_t* flags = (uint32_t*)(e + 0x0c);
        if (((cPropertyList*)g_sAppProps)->GetDescription(0x63ae57a)) {
            uint32_t hit = 0;
            if (b & 0x6000000)
                hit = (uint32_t)((tFrust)(void*)&FUN_00700120)(mFrustum, 0, (char*)obj + 0x70,
                                             (char*)obj + 0x7c, 0);
            *flags = hit;
        } else {
            *flags = 0;
        }
        if (!(*flags & 0x40)) {
            *(float*)((char*)obj + 0x64) = key;
            ((tq2)(void*)&FUN_00fb66d0x)(obj, mpViewer, a, b);
        }
        off += 0x10;
    } while (--cnt);
}

// @ 0x00f98020
void cTerrainSphere::RenderWater(uint32_t a, uint32_t b)
{
    if ((g_16ca5a0 & 1) == 0)
        g_16ca5a0 |= 1;

    cPropertyList* props = (cPropertyList*)g_sAppProps;

    uint32_t buf[4];
    FUN_00fb9ad0(buf);
    g_16ca590[0] = buf[0];
    g_16ca590[1] = buf[1];
    g_16ca590[2] = buf[2];
    g_16ca590[3] = buf[3];

    FUN_00777ae0(0x250, g_16ca590, 0);
    FUN_00777ae0(0x255, (const void*)1, 0);

    uint32_t type;
    uint32_t t = GetTerraformPlanetType(FUN_00fb8a00(GetViewFrame()));
    if (t & 1)
        type = 2;
    else if (t == 2)
        type = 4;
    else
        type = (t == 4 ? 1 : 0) + 2;

    if (props->GetDescription(0xab73e4f9)) {
        uint32_t n = (uint32_t)(mpQuadEnd - mpQuadBegin);
        if ((int)n > 0) {
            int off = 0;
            uint32_t cnt = n;
            do {
                char* e = (char*)mpQuadBegin + off;
                if (!(*(uint32_t*)(e + 0x0c) & 0x40))
                    ((tq3)(void*)&FUN_00fb6850x)(*(void**)e, mpViewer, a, type, b);
                off += 0x10;
            } while (--cnt);
        }
    }
    FUN_00777ae0(0x255, 0, 0);
    FUN_00777ae0(0x250, 0, 0);
}

// @ 0x00f98170
void cTerrainSphere::DrawWaterQuads(uint32_t a, uint32_t b)
{
    uint32_t n = (uint32_t)(mpQuadEnd - mpQuadBegin);
    if ((int)n <= 0)
        return;
    int off = 0;
    uint32_t cnt = n;
    do {
        char* e = (char*)mpQuadBegin + off;
        if (!(*(uint32_t*)(e + 0x0c) & 0x40))
            ((tq2)(void*)&FUN_00fb3040x)(*(void**)e, mpViewer, a, b);
        off += 0x10;
    } while (--cnt);
}

// @ 0x00f981d0
void cTerrainSphere::RenderAtmosphere(uint32_t a, uint32_t b)
{
    uint32_t want = g_16c9e78;
    uint32_t have = g_16f65a0;
    if (!have || !rw_VertexDescriptor_AreEqual((void*)have, (void*)want))
        g_16f9110 |= 0x100000;
    g_16f65a0 = want;
    rw_VertexDescriptor_SetActive((void*)want);

    uint32_t n = (uint32_t)(mpQuad3End - mpQuad3Begin);
    if ((int)n > 0) {
        int off = 0;
        uint32_t cnt = n;
        do {
            char* e = (char*)mpQuad3Begin + off;
            ((tq2)(void*)&FUN_00fb6cd0x)(*(void**)e, mpViewer, a, b);
            off += 0x10;
        } while (--cnt);
    }
}

// @ 0x00f98530
void cTerrainSphere::DrawAtmoQuads(uint32_t a, uint32_t b)
{
    if (((cPropertyList*)g_sAppProps)->GetDescription(0x4badc321)) {
        if (!FUN_007c4fd0(this))
            return;
        uint32_t n = (uint32_t)(mpQuadEnd - mpQuadBegin);
        if ((int)n > 0) {
            int off = 0;
            uint32_t cnt = n;
            do {
                char* e = (char*)mpQuadBegin + off;
                *(float*)((char*)*(void**)e + 0x64) = *(float*)(e + 0x04);
                ((tq4)(void*)&FUN_00fb6e00x)(*(void**)e, a, b, 0);
                off += 0x10;
            } while (--cnt);
        }
    } else {
        if (!FUN_007c4fd0(this))
            return;
        uint32_t n = (uint32_t)(mpQuad2End - mpQuad2Begin);
        if ((int)n > 0) {
            int off = 0;
            uint32_t cnt = n;
            do {
                char* e = (char*)mpQuad2Begin + off;
                *(float*)((char*)*(void**)e + 0x64) = *(float*)(e + 0x04);
                ((tq4)(void*)&FUN_00fb6e00x)(*(void**)e, a, b, 0);
                off += 0x10;
            } while (--cnt);
        }
    }
    FUN_007c3c10(this);
}

// @ 0x00f98290
bool cTerrainSphere::UpdateAboveRaster(int face, const float* rect, uint32_t a3, uint32_t a4)
{
    float l = rect[0], t = rect[1], r = rect[2], b = rect[3];
    cView* view = GetView();
    for (int fi = 0; fi < 4; ++fi) {
        cView::Block* blk = &view->mBlocks[fi];
        uint32_t cnt = (uint32_t)(((char*)blk->mEnd - (char*)blk->mBegin) >> 2);
        for (uint32_t i = 0; i < cnt; ++i) {
            void** slot = (void**)((char*)blk->mBegin + i * 4);
            if (!*slot)
                continue;
            Raster* raster = (Raster*)*slot;
            if (!((raster->mB8 >> 3) & 1))
                continue;
            float box[4];
            if (!FUN_00fad140(raster, face, box))
                continue;
            if (!(r < box[0] && t > box[2] && l < box[3] && b > box[1]))
                continue;
            if (t > box[0]) t = box[0];
            if (l > box[2]) l = box[2];
            if (r < box[3]) r = box[3];
            if (b < box[1]) b = box[1];
        }
    }
    if (l != t && r != b) {
        void* editor = FUN_00f48a70();
        uint32_t* rectId = (uint32_t*)(g_16ca3d4 + face * 8);
        float one = C_1485720;
        if (!FUN_00f6a960(editor, rectId, face, l, t, r, b, 0, 0, one, one, (void*)a4))
            return false;
    }
    if (!FUN_00f678a0()) {
        for (int fi = 0; fi < 4; ++fi) {
            cView::Block* blk = &view->mBlocks[fi];
            uint32_t cnt = (uint32_t)(((char*)blk->mEnd - (char*)blk->mBegin) >> 2);
            for (uint32_t i = 0; i < cnt; ++i) {
                void** slot = (void**)((char*)blk->mBegin + i * 4);
                if (!*slot)
                    continue;
                Raster* raster = (Raster*)*slot;
                if (!((raster->mB8 >> 3) & 1))
                    continue;
                float box[4];
                if (!FUN_00fad140(raster, face, box))
                    continue;
                if (!(l < box[2] && r < box[3] && t > box[0] && b > box[1]))
                    continue;
                if (!FUN_00fad550(raster, face, a4))
                    return false;
            }
        }
    }
    return true;
}

// @ 0x00f98620
void cTerrainSphere::MergeFaceBox(int face, float l, float t, float r, float b)
{
    float* p = mFaceBox[face];
    if (p[0] == p[2] || p[1] == p[3]) {
        p[0] = l;
        p[1] = t;
        p[2] = r;
        p[3] = b;
    } else {
        float v, w;
        v = p[0]; w = l;
        if (!(w > v)) v = w;
        p[0] = v;
        v = p[1]; w = t;
        if (!(w > v)) v = w;
        p[1] = v;
        v = p[2]; w = r;
        if (!(v > w)) v = w;
        p[2] = v;
        v = p[3]; w = b;
        if (!(v > w)) v = w;
        p[3] = v;
    }
}

// @ 0x00f98260
uint32_t cTerrainSphere::GetQuadKeyA(int idx)
{
    uint32_t key = **(uint32_t**)((char*)this + 0x160 + idx * 4);
    return key;
}

// @ 0x00f98270
uint32_t cTerrainSphere::GetQuadKeyB(int idx)
{
    uint32_t key = **(uint32_t**)((char*)this + 0x148 + idx * 4);
    return key;
}

// @ 0x00f98280
uint32_t cTerrainSphere::GetQuadKeyC(int idx)
{
    uint32_t key = **(uint32_t**)((char*)this + 0x178 + idx * 4);
    return key;
}
