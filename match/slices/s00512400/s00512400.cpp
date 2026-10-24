// w1g1 slice s00512400 -- /Od render-job setup: fills a 0x48-byte job record from a
// config object (colors, transform, bone indices).
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct RenderCfg;
struct JobAlloc {
    void Begin();      // 0x00513ec0
    void* Get();       // 0x00513e90
};
struct RenderJobSink {
    uint8_t pad[0x28];
    JobAlloc alloc;    // +0x28
    void InitRenderJob(RenderCfg* cfg, uint32_t* pBones, uint32_t id, float* pos, float* color,
                       uint32_t a6, uint32_t a7);
};


// ---------------------------------------------------------------------------
// config object (fields used by this routine)
// ---------------------------------------------------------------------------
struct RenderCfg {
    uint8_t pad0[0x10];
    float f10;        // 0x10
    float f14;        // 0x14
    float f18;        // 0x18
    uint8_t pad1[0x40 - 0x1c];
    float f40;        // 0x40
    uint8_t pad2[0x5c - 0x44];
    float f5c;        // 0x5c
    float f60;        // 0x60
    float f64;        // 0x64
    float f68;        // 0x68
    float f6c;        // 0x6c
    uint8_t pad3[0x74 - 0x70];
    float f74;        // 0x74
    uint8_t pad4[0x7c - 0x78];
    float f7c;        // 0x7c
    float f80;        // 0x80
    float f84;        // 0x84
    uint8_t b88;      // 0x88
    uint8_t pad5[0x9c - 0x89];
    uint8_t b9c;      // 0x9c
    uint8_t pad6[3];
    uint8_t ba0;      // 0xa0
    uint8_t pad7[3];
    uint8_t ba4;      // 0xa4

    void BuildMatrix(float* p5, uint32_t p6, uint32_t p7, int mode, float* out0, float* out1, int z); // 0x004fe510
};

inline float Saturate(float x)
{
    float f = 0.0f;
    if (x >= 0.0f)
        f = x;
    f = f * 255.0f;
    if (f >= 255.0f)
        f = 255.0f;
    return f;
}
inline int RoundInt(float x) { return (int)(x + 0.5f); }

// @ 0x00512400
void RenderJobSink::InitRenderJob(RenderCfg* cfg, uint32_t* pBones, uint32_t id, float* pos, float* color,
                   uint32_t a6, uint32_t a7)
{
    if (cfg->f10 > 0.0f && cfg->f40 > 0.0f) {
        alloc.Begin();
        uint32_t* job = (uint32_t*)alloc.Get();
        job[0] = id;
        job[1] = *(uint32_t*)&color[0];
        job[2] = *(uint32_t*)&color[1];
        job[3] = *(uint32_t*)&color[2];

        float local[6];
        cfg->BuildMatrix(color, a6, a7, 2, &local[0], &local[3], 0);

        job[4] = *(uint32_t*)&local[0];
        job[5] = *(uint32_t*)&local[1];
        job[6] = *(uint32_t*)&local[2];
        job[7] = *(uint32_t*)&local[3];
        job[8] = *(uint32_t*)&local[4];
        job[9] = *(uint32_t*)&local[5];

        const float v10 = -((local[0] * pos[0] + local[1] * pos[1]) + local[2] * pos[2]) + 0.5f - cfg->f14;
        const float v11 = -((local[3] * pos[0] + local[4] * pos[1]) + local[5] * pos[2]) + 0.5f - cfg->f18;
        job[10] = *(uint32_t*)&v10;
        job[11] = *(uint32_t*)&v11;

        for (int i = 0; i < 3; ++i)
            job[12 + i] = pBones[i];

        const uint32_t c0 =
            (uint32_t)RoundInt(Saturate(cfg->f5c * cfg->f6c)) << 24 |
            ((uint32_t)RoundInt(Saturate(cfg->f60)) & 0xff) << 16 |
            ((uint32_t)RoundInt(Saturate(cfg->f64)) & 0xff) << 8 |
            ((uint32_t)RoundInt(Saturate(cfg->f68)) & 0xff);
        job[15] = c0;

        const uint32_t c1 =
            (uint32_t)RoundInt(Saturate(cfg->f84 * cfg->f5c)) << 24 |
            ((uint32_t)RoundInt(Saturate(cfg->f74)) & 0xff) << 16 |
            ((uint32_t)RoundInt(Saturate(cfg->f7c * cfg->f5c)) & 0xff) << 8 |
            ((uint32_t)RoundInt(Saturate(cfg->f80)) & 0xff);
        job[16] = c1;

        ((uint8_t*)job)[0x44] = cfg->b9c;
        ((uint8_t*)job)[0x45] = cfg->ba0;
        ((uint8_t*)job)[0x46] = cfg->ba4;
        ((uint8_t*)job)[0x47] = cfg->b88;
    }
}
