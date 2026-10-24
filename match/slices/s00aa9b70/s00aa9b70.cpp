// Slice s00aa9b70 (batch big0, slice 17): unnamed per-mode basis-colour / normal
// builder. __cdecl, default /O2, scalar SSE sqrt.
#include "types.h"
#include <xmmintrin.h>

static __forceinline float SqrtF(float x) {
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(x)));
}

static __forceinline float Sqrt3(float a, float b, float c) {
    float m = a < 0.0f ? -a : a;
    float t = b < 0.0f ? -b : b;
    if (t > m) m = t;
    t = c < 0.0f ? -c : c;
    if (t > m) m = t;
    if (m == 0.0f)
        return 0.0f;
    /* Power-of-two rescaling keeps the x87-extended dot product inside the
       single-precision exponent range; the significand and rounding are
       unchanged, so this matches the original's inline fsqrt. */
    float s = 1.0f;
    for (int k = 0; k < 126; ++k) {
        float ms = m * s;
        if (ms > 2.0f)
            s *= 0.5f;
        else if (ms < 0.5f)
            s *= 2.0f;
        else
            break;
    }
    float x = a * s;
    float y = b * s;
    float z = c * s;
    float d = (x * x + y * y) + z * z;
    return SqrtF(d) / s;
}

struct VecXform {
    unsigned char data[0x38];
    void Apply(float* v);                                  // 0xa7d6b0 thiscall vector transform
};

struct BasisData {
    unsigned char pad00[0x5c];
    float defaultBasis0, defaultBasis1, defaultBasis2;     // +0x5c
    float caseBasis0, caseBasis1, caseBasis2;              // +0x68
    float defaultNormal0, defaultNormal1, defaultNormal2;  // +0x74
    unsigned char pad80[0x74];
    float caseNormal0, caseNormal1, caseNormal2;           // +0xf4
};

struct EffectParams {
    unsigned char pad00[0x2c];
    float vecA0, vecA1, vecA2;                             // +0x2c
    float vecB0, vecB1, vecB2;                             // +0x38
    unsigned char pad44[0xee];
    unsigned char countX, countY, mode;                    // +0x132
    unsigned char pad135[0x4b];
    unsigned char colorA, colorB, colorC, colorD;          // +0x180
};

struct BasisSource {
    unsigned char pad00[0x30];
    BasisData* data;                                       // +0x30
    unsigned char pad34[0x94];
    VecXform transform0;                                   // +0xc8
    VecXform transform1;                                   // +0x100
};
extern float DAT_01679444, DAT_01679448, DAT_0167944c;     // basis vectors
extern float DAT_016794a0, DAT_016794a4, DAT_016794a8, DAT_016794ac;
extern float DAT_016794b0, DAT_016794b4;

struct EffectOutput {
    float basis0, basis1, basis2;       // +0x00
    float normal0, normal1, normal2;    // +0x0c
    float color0, color1, color2, color3; // +0x18
    unsigned char modeFlags;            // +0x28
    unsigned char pad29[3];
    float invCountX, invCountY;         // +0x2c
    int countX, countY, levels;         // +0x34
};

// @ 0x00aa9b70
int FUN_00aa9b70(BasisSource* source, EffectParams* params, EffectOutput* out)
{
    float local_18, local_14, local_10, local_c, local_8, local_4;
    float fVar6, fVar2;
    unsigned uVar5;
    unsigned char uVar4;

    switch (params->mode) {
    case 1:
    case 5:
        local_18 = (params->vecB0 + params->vecA0) * 0.5f;
        local_14 = (params->vecB1 + params->vecA1) * 0.5f;
        local_10 = (params->vecB2 + params->vecA2) * 0.5f;
        if (params->mode == 1) {
            source->transform0.Apply(&local_18);
            source->transform1.Apply(&local_18);
        }
        local_c = local_14 * DAT_0167944c - local_10 * DAT_01679448;
        local_8 = local_10 * DAT_01679444 - local_18 * DAT_0167944c;
        local_4 = local_18 * DAT_01679448 - local_14 * DAT_01679444;
        fVar6 = Sqrt3(local_4, local_8, local_c);
        if (!(fVar6 > 0.0001f)) {
            out->basis0 = DAT_016794a0;
            out->basis1 = DAT_016794a4;
            out->basis2 = DAT_016794a8;
            out->normal0 = DAT_016794ac;
            out->normal1 = DAT_016794b0;
            fVar6 = DAT_016794b4;
        } else {
            fVar6 = 1.0f / fVar6;
            local_18 = fVar6 * local_c;
            local_14 = local_8 * fVar6;
            out->basis0 = local_18;
            local_10 = local_4 * fVar6;
            out->basis1 = local_14;
            out->basis2 = local_10;
            local_c = out->basis2 * DAT_01679448 - out->basis1 * DAT_0167944c;
            local_8 = out->basis0 * DAT_0167944c - out->basis2 * DAT_01679444;
            local_4 = out->basis1 * DAT_01679444 - out->basis0 * DAT_01679448;
            out->normal0 = local_c;
            out->normal1 = local_8;
            fVar6 = local_4;
        }
        out->normal2 = fVar6;
        if (params->mode == 5) {
            source->transform0.Apply(&out->basis0);
            source->transform0.Apply(&out->normal0);
            source->transform1.Apply(&out->basis0);
            source->transform1.Apply(&out->normal0);
        }
        break;
    case 6: {
        float* pfVar1 = &out->normal0;
        *pfVar1 = DAT_01679444;
        out->normal1 = DAT_01679448;
        out->normal2 = DAT_0167944c;
        source->transform0.Apply(pfVar1);
        source->transform1.Apply(pfVar1);
        out->basis0 = source->data->caseBasis0;
        out->basis1 = source->data->caseBasis1;
        out->basis2 = source->data->caseBasis2;
        fVar6 = out->basis1;
        fVar2 = out->basis0;
        out->basis0 = out->normal2 * fVar6 - out->normal1 * out->basis2;
        out->basis1 = *pfVar1 * out->basis2 - out->normal2 * fVar2;
        out->basis2 = out->normal1 * fVar2 - *pfVar1 * fVar6;
        fVar6 = 1.0f / (Sqrt3(out->basis0, out->basis1, out->basis2) + 0.1f);
        out->basis0 = fVar6 * out->basis0;
        out->basis1 = out->basis1 * fVar6;
        out->basis2 = fVar6 * out->basis2;
        break;
    }
    case 7: {
        out->normal0 = source->data->caseNormal0;
        out->normal1 = source->data->caseNormal1;
        out->normal2 = source->data->caseNormal2;
        out->basis0 = source->data->caseBasis0;
        out->basis1 = source->data->caseBasis1;
        out->basis2 = source->data->caseBasis2;
        fVar6 = out->basis1;
        fVar2 = out->basis0;
        out->basis0 = out->normal2 * fVar6 - out->normal1 * out->basis2;
        out->basis1 = out->normal0 * out->basis2 - out->normal2 * fVar2;
        out->basis2 = out->normal1 * fVar2 - out->normal0 * fVar6;
        fVar6 = 1.0f / (Sqrt3(out->basis0, out->basis1, out->basis2) + 0.1f);
        out->basis0 = fVar6 * out->basis0;
        out->basis1 = out->basis1 * fVar6;
        out->basis2 = fVar6 * out->basis2;
        break;
    }
    default:
        out->basis0 = source->data->defaultBasis0;
        out->basis1 = source->data->defaultBasis1;
        out->basis2 = source->data->defaultBasis2;
        out->normal0 = source->data->defaultNormal0;
        out->normal1 = source->data->defaultNormal1;
        out->normal2 = source->data->defaultNormal2;
        break;
    }

    if (params->colorA != 0 || params->colorC != 0) {
        out->color0 = (float)params->colorB * 0.003921569f;
        out->color1 = (float)params->colorA * 0.0627451f;
        out->color2 = (float)params->colorD * 0.003921569f;
        out->color3 = (float)params->colorC * 0.0627451f;
    }
    if ((params->countX < 2) && (params->countY < 2)) {
        uVar4 = 0;
    } else {
        uVar4 = 1;
    }
    out->modeFlags = uVar4;
    out->invCountX = 1.0f / (float)params->countX;
    out->invCountY = 1.0f / (float)params->countY;
    out->countX = (int)params->countX - 1;
    out->countY = (int)params->countY - 1;
    out->levels = 0;
    uVar5 = (unsigned)params->countX;
    while (1 < uVar5) {
        uVar5 >>= 1;
        ++out->levels;
    }
    return (int)uVar5;
}
