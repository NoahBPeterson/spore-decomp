// src/game/SPTerrain/_at_00fc0000.cpp -- migrated from slice(s) s00fc2080 by tools/migrate/rewrite.py
// Object file: SPTerrain/_at_00fc0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// ---- items of slice s00fc2080 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace graphics {
class EmbeddedState_s00fc_2080 { public:
    char     pad00[0x10];
    uint32_t mHardStateDirty;   // +0x10
    uint32_t D3D9GetTextureStageState(uint32_t stage);            // 0x11ee870
    void     SetRaster(uint32_t stage, uint32_t value);           // 0x11ee6b0
};
}
}
using rw::graphics::EmbeddedState_s00fc_2080;
class RasterState {
public:
    EmbeddedState_s00fc_2080* mpState;   // +0x00
    uint32_t       mStage;    // +0x04
    uint32_t       mValue;    // +0x08
    uint32_t       mOld;      // +0x0c
    void          Assign(EmbeddedState_s00fc_2080* st, uint32_t stage, uint32_t value);  // 0xfc27e0
    RasterState*  Construct(EmbeddedState_s00fc_2080* st, uint32_t stage, uint32_t value); // 0xfc2c10
    void          Clear();                                                    // 0xfc2830
};
class ILightingManager {
public:
virtual void l0();
virtual void l1();
virtual void l2();
virtual void l3();
virtual void l4();
virtual void l5();
virtual void l6();
virtual void l7();
    virtual void l8();
    virtual void GetDirection(float* out);   // +0x24 (only call site: 0xfc2ab0)
};
namespace SP {
 ILightingManager* LightingManager();   // 0x0067dd90
}
void TerraVectorInsert(void* dst, const void* src, uint32_t bytes);  // 0x11e0744
__declspec(noinline)
bool     TerraPaint(float* a, float* b, float* normal, float* out);   // 0xfc2870
float    TerraScatter(float* p);                                 // 0xfc2ab0
void     TerraSmooth(float* items, int* count, float* normal);   // 0xfc2c70
// ---- items of slice s00fc2080 end

// @ 0x00fc27e0
void RasterState::Assign(EmbeddedState_s00fc_2080* st, uint32_t stage, uint32_t value)
{
    if (st != 0 && (st->mHardStateDirty & (1u << stage)) != 0) {
        mpState = st;
        mStage = stage;
        mValue = value;
        mOld = st->D3D9GetTextureStageState(stage);
        st->SetRaster(stage, value);
    }
}

// @ 0x00fc2830
void RasterState::Clear()
{
    if (mpState != 0) {
        mpState->SetRaster(mStage, mOld);
        mpState = 0;
        mStage = 0;
        mValue = 0;
        mOld = 0;
    }
}

// @ 0x00fc2870
bool TerraPaint(float* a, float* b, float* normal, float* out)
{
    // t = a x b
    float t0 = a[1] * b[2] - a[2] * b[1];
    float t1 = a[0] * b[1] - a[1] * b[0];
    float t2 = a[2] * b[0] - a[0] * b[2];

    // r = t x normal, with the component pairing the original uses
    float r0 = normal[2] * t2 - normal[1] * t1;
    float r1 = normal[0] * t1 - normal[2] * t0;
    float r2 = normal[1] * t0 - normal[0] * t2;

    float len = (float)sqrt((double)(r2 * r2) + (double)(r1 * r1) + (double)(r0 * r0));
    float inv = (float)(1.0 / (double)len);

    out[0] = r0 * inv;
    out[1] = r1 * inv;
    out[2] = r2 * inv;

    // Blend the remaining three floats by the angle between the emitted
    // direction and a, relative to the angle between b and a.
    float d0 = out[0] * a[0] + out[1] * a[1] + out[2] * a[2];
    if (d0 > 1.0f) d0 = 1.0f;
    else if (d0 < 0.0f) d0 = 0.0f;

    float d1 = b[0] * a[0] + b[1] * a[1] + b[2] * a[2];
    if (d1 > 1.0f) d1 = 1.0f;
    else if (d1 < 0.0f) d1 = 0.0f;

    float t = (float)((double)acos((double)d0) / (double)acos((double)d1));

    out[3] = (b[3] - a[3]) * t + a[3];
    out[4] = a[4] + (b[4] - a[4]) * t;
    out[5] = (b[5] - a[5]) * t + a[5];
    return true;
}

// @ 0x00fc2ab0
float TerraScatter(float* p)
{
    float v[6];
    SP::LightingManager()->GetDirection(v);

    // Two unit directions in the xy plane; the z components stay zero and are
    // kept explicit so the signed-zero behaviour matches the original.
    float inv1 = (float)(1.0 / sqrt((double)v[0] * (double)v[0]
                                    + (double)v[3] * (double)v[3] + 1e-8f));
    float a0 = inv1 * v[0];
    float a1 = inv1 * v[3];
    float z1 = inv1 * 0.0f;

    float inv2 = (float)(1.0 / sqrt((double)p[0] * (double)p[0]
                                    + (double)p[1] * (double)p[1] + 1e-8f));
    float b0 = inv2 * p[0];
    float b1 = p[1] * inv2;
    float z2 = inv2 * 0.0f;

    double x = ((double)b0 * z1 - (double)z2 * a1)
             + ((double)z2 * a0 - (double)b1 * z1) * 0.0
             + ((double)b1 * a1 - (double)b0 * a0);
    double y = (double)z2 * z1 + ((double)b1 * a0 + (double)b0 * a1);
    double ang = atan2(x, y);

    // Scale chain: (ang*0.31830987 + 1) * 12 * 60 * 60, kept in x87 in one
    // expression as the original does.
    return (float)(((ang * 0.31830987f) + 1.0f) * 12.0f * 60.0f * 60.0f);
}

// @ 0x00fc2c10
RasterState* RasterState::Construct(EmbeddedState_s00fc_2080* st, uint32_t stage, uint32_t value)
{
    mpState = 0;
    mStage = 0;
    mValue = 0;
    mOld = 0;
    if (st != 0 && (st->mHardStateDirty & (1u << stage)) != 0) {
        mpState = st;
        mStage = stage;
        mValue = value;
        mOld = st->D3D9GetTextureStageState(stage);
        st->SetRaster(stage, value);
    }
    return this;
}

// @ 0x00fc2c70
void TerraSmooth(float* items, int* count, float* normal)
{
    unsigned char cls[16];
    float out[112];
    int n = *count;
    int kept = 0;
    bool allPos = true;
    bool allNeg = true;

    if (n <= 0) return;

    // Classify every item against the plane through `normal`.
    for (int i = 0; i < n; i++) {
        float* it = items + i * 7;
        bool pos = (it[0] * normal[0] + it[2] * normal[2]) + it[1] * normal[1] > 0.0f;
        cls[i] = pos;
        if (pos) allNeg = false; else allPos = false;
    }

    if (allPos) return;
    if (allNeg) {
        *count = 0;
        return;
    }

    // Keep the first item when it is on the positive side, then walk the
    // ring, painting one boundary item per sign change and copying every
    // positive run item after it.
    if (cls[0]) {
        for (int k = 0; k < 7; k++) out[k] = items[k];
        kept = 1;
    }

    float* dst = out + kept * 7;
    float* cur = items;
    unsigned char prev = cls[0];
    for (int i = 1; i <= n; i++) {
        int j = i % n;
        if (prev != cls[j]) {
            float tmp[7];
            if (prev)
                TerraPaint(cur, items + j * 7, normal, tmp);
            else
                TerraPaint(items + j * 7, cur, normal, tmp);
            kept++;
            for (int k = 0; k < 7; k++) *dst++ = tmp[k];
        }
        prev = cls[j];
        if (prev && i != n) {
            float* src = items + j * 7;
            kept++;
            for (int k = 0; k < 7; k++) *dst++ = src[k];
        }
        cur += 7;
    }

    *count = kept;
    TerraVectorInsert(items, out, (uint32_t)kept * 0x1c);
}
