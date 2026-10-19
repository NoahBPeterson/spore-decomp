// src/game/SPBake/SPSkinnerRTT_SporeApp.cpp -- migrated from slice(s) s005296b0, s005288f0 by tools/migrate/rewrite.py
// Object file: SPBake/SPSkinnerRTT_SporeApp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPSkinner/cRTTBuffer.h"
#include "SP/cRenderTargetRectID.h"

// unnamed retail callees and globals (address in the comment)
extern uint32_t g_15dea68;
extern uint32_t* g_dec10;   // 0x015dec10
extern uint32_t g_softStateDirty;      // 0x016f9528
extern uint32_t g_transformType;       // 0x016f96a0
extern void*    g_transform;           // 0x016fa380
extern float    g_transformLocal[16];  // 0x016fa4f0

// ---- items of slice s005288f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RwDevice {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void* v04(int* out, uint32_t w, uint32_t h, int fmt, short flags, uint32_t z, int n);  // +0x10
    virtual void v05();                                                                            // +0x14
    virtual int  v06(uint32_t a, uint32_t b);                                                      // +0x18
    virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(uint32_t a, uint32_t b, const char* name);                                    // +0x48
};
RwDevice* GetDevice();                 // 0x0067dda0
void FreeObj(void* p);                 // 0x00f47410
void SetRenderState(int state, uint32_t value);       // 0x00529350
void DrawVertices4(void* v, int n);                   // 0x011f3d40
uint32_t RwStreamX(uint32_t);                          // 0x011fd790
void RwStreamY(uint32_t, void*);                       // 0x011fd7b0
void RwGfxCall(int, void*);                            // 0x004cdd70
struct RwObj { void Shutdown(); };
void RwShutdown2();                                    // 0x011fd7d0
int  RwCheck();                                        // 0x011f3f20
extern uint32_t g_15dea68;
struct cSPVector4_s0052_88f0 { float x, y, z, w; };
namespace nSPSkinner {
struct cRenderTargetRectID {
    int mPageID;      // +0x0
    int mAllocID;     // +0x4
};
}
namespace nSPSkinner {
struct cRTTBuffer_s0052_88f0 {                     // size 0x64
    RwDevice* mCamera;                  // +0x00
    uint32_t material;                  // +0x04
    uint32_t writemask;                 // +0x08
    cSPVector4_s0052_88f0 params[3];               // +0x0c
    void* textures[2];                  // +0x3c
    int maxparam;                       // +0x44
    int maxtexture;                     // +0x48
    uint32_t vtxcount;                  // +0x4c
    cRenderTargetRectID mRTTRect;       // +0x50
    uint32_t mWidth;                    // +0x58
    uint32_t mHeight;                   // +0x5c
    void* mTexture;                     // +0x60

    cRTTBuffer_s0052_88f0(uint32_t w, uint32_t h);         // 0x005288f0
    void* PrepareState();                        // 0x005293a0
    void Destroy();                              // 0x00528e20
    uint32_t ClampAndStream(uint32_t requested); // 0x00529520
};
}
namespace nSPSkinner {
typedef void (__thiscall *RwDeviceVtbl5)(void* self, int pageID, int allocID);
}
using nSPSkinner::cRTTBuffer_s0052_88f0;
struct Matrix44f { float m[16]; };
struct StateBits {
    char pad[8];
    uint32_t mFlags;
    void Set(unsigned char a, unsigned char b, unsigned char c, unsigned char d);   // 0x00529280
};
struct DrawCtx {
    char pad[8];
    uint32_t writemask;
    void Draw(float* v, float w);   // 0x005292d0
};
extern uint32_t* g_dec10;   // 0x015dec10
extern uint32_t g_softStateDirty;      // 0x016f9528
extern uint32_t g_transformType;       // 0x016f96a0
extern void*    g_transform;           // 0x016fa380
extern float    g_transformLocal[16];  // 0x016fa4f0
// ---- items of slice s005288f0 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
void EffectsDispatch(Matrix44f* m, uint32_t type);   // defined at 0x005291f0, called earlier in the TU

// ---- items of slice s005296b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t DAT_016f9238, DAT_016f923c, DAT_016f9218, DAT_016f9244;
extern uint32_t DAT_015dea64, DAT_015dea5c, DAT_015dea58, DAT_015dea68, DAT_015dea60;
extern uint32_t g_renderStateDirty;   // 0x016fa388
extern uint32_t g_rasterDelta;        // 0x016f921c
void RwTeardown();                                                     // 0x00529690
void ActiveStateSetTexture(int n, void* tex);                          // rw::graphics::ActiveState::SetTexture
void FUN_011f38e0();                                                   // 0x011f38e0
struct V2 { uint32_t x, y; };
struct cQuadWriter {
    void EmitVertex4(uint32_t* a, uint32_t* b, uint32_t* c, uint32_t d);   // 0x005295b0
    uint32_t FUN_00529520(int);                                            // 0x00529520
    void WriteQuadVerts(V2* a, V2* b, uint32_t param_3);                   // 0x005296b0
};
struct RwDevice_s0052_96b0 {
    char pad[0x208];
    void* m_raster[8];
};
struct cRTTBuffer18 {
    RwDevice_s0052_96b0* mCamera;
    uint32_t material;
    uint32_t writemask;
    void BeginDraw();       // 0x00529bf0
};
// ---- items of slice s005296b0 end

// @ 0x00528e20
namespace nSPSkinner {
void cRTTBuffer_s0052_88f0::Destroy()
{
    cRTTBuffer_s0052_88f0* self = this;
    RwDevice* d = GetDevice();
    RwDeviceVtbl5 fn = *(RwDeviceVtbl5*)(*(int*)d + 0x14);
    fn(d, self->mRTTRect.mPageID, self->mRTTRect.mAllocID);
    FreeObj(self->mCamera);
}
}  // namespace nSPSkinner

// @ 0x00528e90
bool RenderSingleModels()
{
    RwDevice* dev = GetDevice();
    (void)dev;
    if (RwCheck() != 0) {
        Matrix44f local;
        for (int i = 0; i < 16; ++i)
            local.m[i] = 0.0f;
        EffectsDispatch(&local, 1);
        return true;
    }
    return false;
}

// @ 0x005291f0
void EffectsDispatch(Matrix44f* m, uint32_t type)
{
    g_softStateDirty |= 1;
    g_transformType = type;
    g_transform = g_transformLocal;
    for (int i = 0; i < 16; ++i)
        g_transformLocal[i] = m->m[i];
}

// @ 0x00529280
void StateBits::Set(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    mFlags = (a ? 1 : 0) | (b ? 2 : 0) | (c ? 4 : 0) | (d ? 8 : 0);
}

// @ 0x005292d0
void DrawCtx::Draw(float* v, float w)
{
    SetRenderState(0xa8, writemask & g_15dea68);
    float local[4];
    local[0] = v[0];
    local[1] = v[1];
    local[2] = v[2];
    local[3] = w;
    DrawVertices4(local, 1);
}

// @ 0x00529350
void SetRenderState(int state, uint32_t value)
{
    ((uint32_t*)0x016fa38c)[(state - 7) >> 5] |= 1u << ((state - 7) & 0x1f);
    ((uint32_t*)0x016f91e0)[state] = value;
}

// @ 0x00529520
uint32_t nSPSkinner::cRTTBuffer_s0052_88f0::ClampAndStream(uint32_t requested)
{
    cRTTBuffer_s0052_88f0* self = this;
    int st = (int)self->PrepareState();
    uint32_t n = (uint32_t)RwStreamX((uint32_t)st);
    n = n / 3;
    uint32_t chosen = (n < requested) ? n : requested;
    char local_8[4];
    RwStreamY((uint32_t)st, local_8);
    *(uint32_t*)0x015dec08 = chosen * 3;
    RwGfxCall(chosen * 3, (void*)0x015dec08);
    return chosen;
}

// @ 0x005295b0
void WriteBuffer(uint32_t* a, uint32_t* b, uint32_t* c, uint32_t d)
{
    uint32_t* p = g_dec10;
    p[0] = a[0]; p[1] = a[1]; p[2] = 0;
    g_dec10 = p + 3;
    p = g_dec10;
    p[0] = b[0]; p[1] = b[1];
    g_dec10 = p + 2;
    p = g_dec10;
    p[0] = c[0]; p[1] = c[1]; p[2] = c[2];
    g_dec10 = p + 3;
    p = g_dec10;
    p[0] = d;
    g_dec10 = p + 1;
}

// @ 0x00529690
void __fastcall RwTeardown(RwObj* p)
{
    p->Shutdown();
    RwShutdown2();
}

// @ 0x005296b0
void cQuadWriter::WriteQuadVerts(V2* a, V2* b, uint32_t param_3)
{
    FUN_00529520(2);
    uint32_t l10 = 0, lc = 0, l8 = 0;
    uint32_t l18 = a->x, l14 = a->y;
    uint32_t l20 = a->x, l1c = a->y;
    EmitVertex4(&l20, &l18, &l10, param_3);

    uint32_t l2c = 0x3f800000, l28 = 0, l24 = 0;
    uint32_t l34 = b->x, l30 = a->y;
    uint32_t l3c = b->x, l38 = a->y;
    EmitVertex4(&l3c, &l34, &l2c, param_3);

    uint32_t l48 = 0x3f800000, l44 = 0x3f800000, l40 = 0;
    uint32_t l50 = b->x, l4c = b->y;
    uint32_t l58 = b->x, l54 = b->y;
    EmitVertex4(&l58, &l50, &l48, param_3);

    uint32_t l64 = 0x3f800000, l60 = 0x3f800000, l5c = 0;
    uint32_t l6c = b->x, l68 = b->y;
    uint32_t l74 = b->x, l70 = b->y;
    EmitVertex4(&l74, &l6c, &l64, param_3);

    uint32_t l80 = 0, l7c = 0x3f800000, l78 = 0;
    uint32_t l88 = a->x, l84 = b->y;
    uint32_t l90 = a->x, l8c = b->y;
    EmitVertex4(&l90, &l88, &l80, param_3);

    uint32_t l9c = 0, l98 = 0, l94 = 0;
    uint32_t la4 = a->x, la0 = a->y;
    uint32_t lac = a->x, la8 = a->y;
    EmitVertex4(&lac, &la4, &l9c, param_3);

    RwTeardown();
}

// @ 0x00529bf0
void cRTTBuffer18::BeginDraw()
{
    DAT_016f9238 = DAT_015dea64;
    if (DAT_015dea5c == 0)
        DAT_016f923c = 8;
    else
        DAT_016f923c = 4;
    g_renderStateDirty |= 0x18080;
    DAT_016f9218 = DAT_015dea58;
    SetRenderState(0xa8, DAT_015dea68);
    g_rasterDelta = (DAT_015dea60 != 8) ? 1 : 0;
    g_renderStateDirty |= 0x40100;
    DAT_016f9244 = DAT_015dea60;
    ActiveStateSetTexture(0, 0);
    ActiveStateSetTexture(1, 0);
    g_renderStateDirty |= 3;
    FUN_011f38e0();
    mCamera->m_raster[0] = 0;
}
