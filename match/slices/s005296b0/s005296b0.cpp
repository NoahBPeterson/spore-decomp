// nSPSkinner RTT-buffer draw paths: vertex emission, BeginDraw state, HSV<->RGB (/Od /Ob1 /MD /Gy /TP /arch:SSE).
#include "types.h"

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}

// ---------------------------------------------------------------- external helpers
void EmitVertex4(uint32_t* a, uint32_t* b, uint32_t* c, uint32_t d);   // 0x005295b0
void RwTeardown();                                                     // 0x00529690
uint32_t FUN_00529520(int);                                            // 0x00529520
void SetRenderState(int state, uint32_t value);                        // 0x00529350
void ActiveStateSetTexture(int n, void* tex);                          // rw::graphics::ActiveState::SetTexture
void FUN_011f38e0();                                                   // 0x011f38e0
float* Vector3Scale(float* out, float* a, float* b);                   // 0x0041de40

struct RwDevice {
    char pad[0x208];
    void* m_raster[8];
};
struct cRTTBuffer18 {
    RwDevice* mCamera;
    uint32_t material;
    uint32_t writemask;
    void BeginDraw();       // 0x00529bf0
};

extern uint32_t DAT_016f9238, DAT_016f923c, DAT_016f9218, DAT_016f9244;
extern uint32_t DAT_015dea64, DAT_015dea5c, DAT_015dea58, DAT_015dea68, DAT_015dea60;
extern uint32_t g_renderStateDirty;   // 0x016fa388
extern uint32_t g_rasterDelta;        // 0x016f921c

// @ 0x005296b0
struct V2 { uint32_t x, y; };
void WriteQuadVerts(V2* a, V2* b, uint32_t param_3)
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

inline void cRTTBuffer18BeginDrawImpl(cRTTBuffer18* self) { self->BeginDraw(); }

// @ 0x00529d30  RGB -> HSV
float* RGBtoHSV(float* out, float r, float g, float b)
{
    int which;
    float mx;
    float d;
    if (r <= g) {
        if (g <= b) {
            which = 2; mx = b; d = b - r;
        } else {
            which = 1; mx = g;
            float t = g - b;
            if (r < b) t = g - r;
            d = t;
        }
    } else if (b <= r) {
        which = 0; mx = r;
        float t = r - g;
        if (b < g) t = r - b;
        d = t;
    } else {
        which = 2; mx = b; d = b - g;
    }
    if (d <= 1.5258789e-05f) {
        out[0] = 0.0f;
        out[1] = 0.0f;
        out[2] = mx;
    } else {
        float s = 60.0f / d;
        if (which == 2)
            s = s * (r - g) + 240.0f;
        else if (which == 1)
            s = s * (b - r) + 120.0f;
        else {
            s = s * (g - b);
            if (g < b) s = s + 360.0f;
        }
        out[0] = s;
        out[1] = d / mx;
        out[2] = mx;
    }
    return out;
}

// @ 0x0052a030  HSV -> RGB
float* HSVtoRGB(float* out, float param_2, float param_3)
{
    float local_10 = param_2 * 0.016666668f;
    int local_c = (int)local_10;
    float local_98 = 1.0f - param_3;
    float local_80 = 1.0f - (local_10 - (float)local_c) * param_3;
    float local_9c = (local_10 - (float)local_c) * param_3 + local_98;
    float local_18 = local_9c;
    float local_14 = local_80;
    float local_8 = local_98;
    switch (local_c) {
    case 0: {
        float v[3] = { 1.0f, local_9c, local_98 };
        float* p = Vector3Scale(out, v, &local_18);
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
        break;
    }
    case 1: {
        float v[3] = { local_80, 1.0f, local_98 };
        float* p = Vector3Scale(out, v, &local_18);
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
        break;
    }
    case 2: {
        float v[3] = { local_98, 1.0f, local_9c };
        float* p = Vector3Scale(out, v, &local_18);
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
        break;
    }
    case 3: {
        float v[3] = { local_98, 1.0f, 0.0f };
        float* p = Vector3Scale(out, v, &local_18);
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
        break;
    }
    case 4: {
        float v[3] = { local_80, local_98, 0.0f };
        float* p = Vector3Scale(out, v, &local_18);
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
        break;
    }
    default: {
        float v[3] = { 1.0f, local_98, local_80 };
        float* p = Vector3Scale(out, v, &local_18);
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
    }
    }
    return out;
}
