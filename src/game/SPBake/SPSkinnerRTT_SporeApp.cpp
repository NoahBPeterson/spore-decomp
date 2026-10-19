// src/game/SPBake/SPSkinnerRTT_SporeApp.cpp -- migrated from slice(s) s005296b0, s005288f0 by tools/migrate/rewrite.py
// Object file: SPBake/SPSkinnerRTT_SporeApp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPSkinner/cRTTBuffer.h"
#include "SP/cRenderTargetRectID.h"
#include "rw/graphics/EmbeddedState.h"
#include "SP/cDirectPropertyList.h"
#include <xmmintrin.h>

// unnamed retail callees and globals (address in the comment)
extern uint32_t g_15dea68;
extern uint32_t* g_dec10;   // 0x015dec10
extern uint32_t g_softStateDirty;      // 0x016f9528
extern uint32_t g_transformType;       // 0x016f96a0
extern void*    g_transform;           // 0x016fa380
extern float    g_transformLocal[16];  // 0x016fa4f0

// ---- items of slice s005288f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_140e35c;                  // 0x0140e35c  render-target format (0x15)
extern uint32_t g_15dea6c;
struct cRenderTargetRectID {
    int mPageID;      // +0x0
    int mAllocID;     // +0x4
    cRenderTargetRectID() : mPageID(-1), mAllocID(-1) {}
};
struct RwDevice {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
    virtual cRenderTargetRectID v04(uint32_t w, uint32_t h, int fmt, short flags, uint32_t z, int n);  // +0x10 (hidden sret)
    virtual void v05();                                                                            // +0x14
    virtual int  v06(cRenderTargetRectID id);                                                      // +0x18
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
    virtual void v18(cRenderTargetRectID id, const char* name);                                    // +0x48
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
void RwSetMode(int, void*, int);                       // 0x00777ae0
struct StateBits {
    char pad[8];
    uint32_t mFlags;
    void Set(unsigned char a, unsigned char b, unsigned char c, unsigned char d);   // 0x00529280
};
struct cSPVector4_s0052_88f0 {
    float x, y, z, w;
    cSPVector4_s0052_88f0() {}
    float& operator[](int i) { return (&x)[i]; }
};
struct EmbeddedState {                 // rw::graphics::EmbeddedState
    char pad[0x10];
    uint32_t m_hardStateDirty;         // +0x10
    void SetRaster(int index, void* raster);   // 0x011ee6b0
};
struct MaterialObj { uint32_t pad0; EmbeddedState* mState; };   // state at +4
struct IMaterialManager {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
    virtual MaterialObj* GetMaterial(uint32_t id);     // +0x28
};
IMaterialManager* GetMaterialManager();                // 0x0067dd70
struct RwShaderConsts { void SetShConst(unsigned short index, float x, float y, float z, float w); };  // 0x0077ca20
extern RwShaderConsts g_15ded98;
struct SseVec4 {
    __m128 v;
    SseVec4() {}
    SseVec4(float x, float y, float z, float w) { v = _mm_set_ps(w, z, y, x); }
};
struct cDirectPropertyList {
    char pad[0x3c];
    int* mpValues;           // +0x3c
    bool GetBool(int idx) const { return mpValues[idx] != 0; }
};
extern cDirectPropertyList* g_15fd918;   // sAppProperties 0x015fd918
struct RwCamera {                        // object returned by FUN_00761380
    SseVec4 mMatrix[4];                  // +0x00
    char pad40[0x1c];
    float mWinCenterX, mWinCenterY;      // +0x5c, +0x60
    float mWinScaleX, mWinScaleY;        // +0x64, +0x68
    int mProjType;                       // +0x6c
    float mNear, mFar;                   // +0x70, +0x74
    uint32_t mVpX, mVpY, mVpW, mVpH;     // +0x78..+0x84
    float mDepthMin, mDepthMax;          // +0x88, +0x8c
};
RwCamera* GetCamera();                   // 0x00761380
inline void SetMatrix(RwCamera* c, const SseVec4& a, const SseVec4& b, const SseVec4& d, const SseVec4& e) {
    c->mMatrix[0] = a; c->mMatrix[1] = b; c->mMatrix[2] = d; c->mMatrix[3] = e;
}
inline void SetViewport(uint16_t h, uint16_t w, uint16_t y, uint16_t x, float f, float n, RwCamera* c) {
    c->mVpX = x; c->mVpY = y; c->mVpW = w; c->mVpH = h; c->mDepthMin = n; c->mDepthMax = f;
}
inline void SetProjType(RwCamera* c, int t) { c->mProjType = t; }
inline void SetNear(RwCamera* c, float n) { c->mNear = n; }
inline void SetFar(RwCamera* c, float f) { c->mFar = f; }
inline void SetWindow(RwCamera* c, float cx, float cy, float sx, float sy) {
    c->mWinCenterX = cx; c->mWinCenterY = cy; c->mWinScaleX = sx; c->mWinScaleY = sy;
}
namespace nSPSkinner {
struct cRTTBuffer_s0052_88f0 {                     // size 0x64
    RwCamera* mCamera;                  // +0x00
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
    EmbeddedState* PrepareState();               // 0x005293a0
    void Destroy();                              // 0x00528e20
    uint32_t ClampAndStream(uint32_t requested); // 0x00529520
};
}
namespace nSPSkinner {
typedef void (__thiscall *RwDeviceVtbl5)(void* self, int pageID, int allocID);
}
using nSPSkinner::cRTTBuffer_s0052_88f0;
struct Matrix44f { float m[16]; };
struct DrawCtx {
    char pad[8];
    uint32_t writemask;
    void Draw(float* v, float w);   // 0x005292d0
};
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

// @ 0x005288f0
namespace nSPSkinner {
cRTTBuffer_s0052_88f0::cRTTBuffer_s0052_88f0(uint32_t w, uint32_t h)
: mCamera(0)
{
    mWidth = w;
    mHeight = h;
    mTexture = 0;
    short flags = 0;
    RwDevice* dev = GetDevice();
    mRTTRect = dev->v04(w, h, g_140e35c, flags, 0xffffffffu, 0);
    GetDevice()->v18(mRTTRect, "SkinPaint");
    mTexture = (void*)GetDevice()->v06(mRTTRect);
    mCamera = GetCamera();
    SetViewport((uint16_t)mHeight, (uint16_t)mWidth, 0, 0, 1.0f, 0.0f, mCamera);
    SetProjType(mCamera, 2);
    SetNear(mCamera, 1.0f);
    SetFar(mCamera, 3.0f);
    SetWindow(mCamera, 0.5f, 0.5f, 1.0f / 0.5f, 1.0f / 0.5f);
    SseVec4 r0 = SseVec4(-1.0f, 0.0f, 0.0f, -1.0f);
    SseVec4 r1 = SseVec4(0.0f, -1.0f, 0.0f, 0.0f);
    SseVec4 r2 = SseVec4(0.0f, 0.0f, 1.0f, 0.0f);
    SseVec4 r3;
    if (g_15fd918->GetBool(0x44)) {
        float fx = 0.5f / (float)mWidth + 0.5f;
        float fy = 0.5f / (float)mHeight + 0.5f;
        r3 = SseVec4(fx, fy, -2.0f, fx);
    } else {
        r3 = SseVec4(0.5f, 0.5f, -2.0f, 0.5f);
    }
    SetMatrix(mCamera, r0, r1, r2, r3);
    ((StateBits*)this)->Set(1, 1, 1, 1);
}
}  // namespace nSPSkinner

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

// @ 0x005293a0
EmbeddedState* nSPSkinner::cRTTBuffer_s0052_88f0::PrepareState()
{
    SetRenderState(0xa8, writemask & g_15dea68);
    if (material == 0)
        material = (maxtexture != 0 ? 0x9f4dd1ca : 0) + 0xf8b396;
    EmbeddedState* shaderState = GetMaterialManager()->GetMaterial(material)->mState;
    for (int i = 0; i < maxtexture; ++i) {
        if ((((1 << i) & shaderState->m_hardStateDirty) != 0) ? 1 : 0)
            shaderState->SetRaster(i, textures[i]);
    }
    for (int j = 0; j < maxparam; ++j)
        g_15ded98.SetShConst((unsigned short)j, params[j][0], params[j][1], params[j][2], params[j][3]);
    RwSetMode(0x201, &g_15dea6c, 0);
    return shaderState;
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
