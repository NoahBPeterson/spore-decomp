// nSPSkinner RTT-paint buffer + RenderWare effects dispatch (unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE).
#include "types.h"

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}
inline void* operator new(unsigned int, void* p) { return p; }

// ---------------------------------------------------------------- RenderWare graphics device
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
int  GetVertexBufferHandle();          // 0x00761380
void FreeObj(void* p);                 // 0x00f47410
void RasterRelease(uint32_t a, uint32_t b);  // via device vtbl 0x14
void* MaterialManager();               // 0x0067dd70

void SetRenderState(int state, uint32_t value);       // 0x00529350
void SetSomeState(int, int, int, int);                 // 0x00529280
void DrawVertices4(void* v, int n);                   // 0x011f3d40
uint32_t RwStreamX(uint32_t);                          // 0x011fd790
void RwStreamY(uint32_t, void*);                       // 0x011fd7b0
void RwGfxCall(int, void*);                            // 0x004cdd70
void __fastcall RwShutdown1(void*);                    // 0x011fd820
struct RwObj { void Shutdown(); };
void RwShutdown2();                                    // 0x011fd7d0
int  RwCheck();                                        // 0x011f3f20
void RwSetParam(uint32_t, float, float, float, float); // 0x0077ca20
void RwSetMode(int, void*, int);                       // 0x00777ae0
void cEffectsModelHelper();                            // 0x00528e20

extern uint32_t g_15dea68;

// ---------------------------------------------------------------- cSPVector4
struct cSPVector4 { float x, y, z, w; };

namespace nSPSkinner {

struct cRenderTargetRectID {
    int mPageID;      // +0x0
    int mAllocID;     // +0x4
};

struct cRTTBuffer {                     // size 0x64
    RwDevice* mCamera;                  // +0x00
    uint32_t material;                  // +0x04
    uint32_t writemask;                 // +0x08
    cSPVector4 params[3];               // +0x0c
    void* textures[2];                  // +0x3c
    int maxparam;                       // +0x44
    int maxtexture;                     // +0x48
    uint32_t vtxcount;                  // +0x4c
    cRenderTargetRectID mRTTRect;       // +0x50
    uint32_t mWidth;                    // +0x58
    uint32_t mHeight;                   // +0x5c
    void* mTexture;                     // +0x60

    cRTTBuffer(uint32_t w, uint32_t h);         // 0x005288f0
    void* PrepareState();                        // 0x005293a0
};

// @ 0x005288f0
cRTTBuffer::cRTTBuffer(uint32_t w, uint32_t h)
{
    mCamera = 0;
    for (int i = 2; i >= 0; --i) { }
    mRTTRect.mPageID = -1;
    mRTTRect.mAllocID = -1;
    mWidth = w;
    mHeight = h;
    mTexture = 0;
    cRTTBuffer* self = this;
    short local_24 = 0;
    int local_30[2];
    int* dev = (int*)GetDevice();
    void* p = ((RwDevice*)dev)->v04(local_30, w, h, 0x15, local_24, 0xffffffffu, 0);
    (void)p;
    uint32_t a = *(uint32_t*)((char*)local_30 + 0x50);
    uint32_t b = *(uint32_t*)((char*)local_30 + 0x54);
    ((RwDevice*)GetDevice())->v18(a, b, "SkinPaint");
    int tex = ((RwDevice*)GetDevice())->v06(a, b);
    *(int*)((char*)self + 0x60) = tex;
    int vb = GetVertexBufferHandle();
    *(int*)self = vb;
    uint16_t hgt = *(uint16_t*)((char*)self + 0x2c);
    uint16_t wid = *(uint16_t*)((char*)self + 0x2e);
    int vb2 = *(int*)self;
    *(uint32_t*)(vb2 + 0x78) = 0;
    *(uint32_t*)(vb2 + 0x7c) = 0;
    *(uint32_t*)(vb2 + 0x80) = wid;
    *(uint32_t*)(vb2 + 0x84) = hgt;
    *(uint32_t*)(vb2 + 0x88) = 0;
    *(uint32_t*)(vb2 + 0x8c) = 0x3f800000;
    *(uint32_t*)(*(int*)self + 0x6c) = 2;
    *(uint32_t*)(*(int*)self + 0x70) = 0x3f800000;
    *(uint32_t*)(*(int*)self + 0x74) = 0x40400000;
    int vb3 = *(int*)self;
    *(uint32_t*)(vb3 + 0x5c) = 0x3f000000;
    *(uint32_t*)(vb3 + 0x60) = 0x3f000000;
    *(uint32_t*)(vb3 + 100) = 0x40000000;
    *(uint32_t*)(vb3 + 0x68) = 0x40000000;
    float fx, fy;
    if (*(int*)(*(int*)(g_15dea68 + 0x3c) + 0x110) == 0) {
        fx = 0.5f; fy = 0.5f;
    } else {
        fy = 0.5f / (float)(uint32_t)*(uint16_t*)((char*)self + 0x2c) + 0.5f;
        fx = 0.5f / (float)(uint32_t)*(uint16_t*)((char*)self + 0x2e) + 0.5f;
    }
    float* m = (float*)*(int*)self;
    m[0] = -1.0f; m[1] = 0; m[2] = 0;
    m[3] = -1.0f; m[4] = 0;
    m[5] = -1.0f; m[6] = 0; m[7] = 0; m[8] = 0; m[9] = 0;
    m[10] = 1.0f; m[11] = 0;
    m[12] = fy; m[13] = fx;
    m[14] = -2.0f; m[15] = fy;
    SetSomeState(1, 1, 1, 1);
}

// @ 0x00528e20  (real shape: device->vtbl[5](mRTTRect fields), free(mCamera))
void cRTTBufferDestroy(cRTTBuffer* self)
{
    int* d = (int*)GetDevice();
    (*(void(__thiscall*)(int*, int, int))(*(int*)d + 0x14))(d, self->mRTTRect.mPageID, self->mRTTRect.mAllocID);
    FreeObj(self->mCamera);
}

}  // namespace nSPSkinner
using nSPSkinner::cRTTBuffer;

// @ 0x005291f0
struct Matrix44f { float m[16]; };

// @ 0x00529280
struct StateBits {
    char pad[8];
    uint32_t mFlags;
    void Set(unsigned char a, unsigned char b, unsigned char c, unsigned char d);   // 0x00529280
};
void StateBits::Set(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    mFlags = (a ? 1 : 0) | (b ? 2 : 0) | (c ? 4 : 0) | (d ? 8 : 0);
}

// @ 0x00529350
void SetRenderState(int state, uint32_t value)
{
    ((uint32_t*)0x016fa38c)[(state - 7) >> 5] |= 1u << ((state - 7) & 0x1f);
    ((uint32_t*)0x016f91e0)[state] = value;
}

// @ 0x005292d0
struct DrawCtx {
    char pad[8];
    uint32_t writemask;
    void Draw(float* v, float w);   // 0x005292d0
};
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

// @ 0x00529520
uint32_t ClampAndStream(cRTTBuffer* self, uint32_t requested)
{
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
extern uint32_t* g_dec10;   // 0x015dec10
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

// ---------------------------------------------------------------- effects dispatch
extern uint32_t g_softStateDirty;      // 0x016f9528
extern uint32_t g_transformType;       // 0x016f96a0
extern void*    g_transform;           // 0x016fa380
extern float    g_transformLocal[16];  // 0x016fa4f0

// @ 0x005291f0
void EffectsDispatch(Matrix44f* m, uint32_t type)
{
    g_softStateDirty |= 1;
    g_transformType = type;
    g_transform = g_transformLocal;
    for (int i = 0; i < 16; ++i)
        g_transformLocal[i] = m->m[i];
}

// @ 0x00528e90  SP::cEffectsRenderer::RenderSingleModels
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
