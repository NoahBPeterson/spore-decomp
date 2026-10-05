// Slice s00783590: spherical-harmonic (SH) helpers (0x783590..0x7843a0):
// normalisation apply/remove, diffuse reflection, Z mirror, SH basis multiply,
// hemisphere-environment projection and Henyey-Greenstein phase terms.
// /O2 /MD /Gy /EHsc /TP module (SSE1 + x87).
#include "types.h"
#include <math.h>
#include <xmmintrin.h>
#pragma intrinsic(sqrt)

// SH normalisation constants (PDB names)
extern float kSH_Y_00, kSH_Y_1x;
extern float kSH_Y_2_2, kSH_Y_2_1, kSH_Y_20, kSH_Y_21, kSH_Y_22;
extern float kSH_Y_3_3, kSH_Y_3_2, kSH_Y_3_1, kSH_Y_30, kSH_Y_31, kSH_Y_32, kSH_Y_33;
extern float kSH_Y_4_4, kSH_Y_4_3, kSH_Y_4_2, kSH_Y_4_1, kSH_Y_40, kSH_Y_41, kSH_Y_42, kSH_Y_43, kSH_Y_44;
extern float g_153ae10;
extern char  kBasisTriples3, kBasisTriples4, kBasisTriples5;

void SP_MultiplySH(int n, int a, int b, void* out, char* triples);
float FUN_00783130(float theta, unsigned m, float phi, float extra);

// @ 0x00784330
void CalcHGPhaseZH(float a, const float* src, int order, float* dst)
{
    __m128 x = _mm_load_ps(src);
    if (order > 0) {
        int i = 1;
        do {
            __m128 scale = _mm_set1_ps((float)sqrt((double)((float)i * g_153ae10 * 4.0f)));
            _mm_store_ps(dst, _mm_mul_ps(scale, x));
            x = _mm_mul_ps(_mm_set1_ps(a), x);
            i += 2;
            order--;
        } while (order != 0);
    }
}

// @ 0x007843a0
void CalcHGPhaseZHAdd(float a, const float* src, int order, float* dst)
{
    __m128 x = _mm_load_ps(src);
    if (order > 0) {
        int i = 1;
        do {
            __m128 scale = _mm_set1_ps((float)sqrt((double)((float)i * g_153ae10 * 4.0f)));
            _mm_store_ps(dst, _mm_add_ps(_mm_mul_ps(scale, x), _mm_load_ps(dst)));
            x = _mm_mul_ps(_mm_set1_ps(a), x);
            i += 2;
            order--;
        } while (order != 0);
    }
}

// @ 0x00783c90
void MirrorSHInZ(int n, float* data)
{
    for (int i = 0; i < n; ++i) {
        for (int j = -i; j <= i; ++j) {
            if ((i + j) & 1) {
                int idx = (i + 1) * i + j;
                float* p = data + idx * 4;
                __m128 v = _mm_load_ps(p);
                __m128 neg = _mm_sub_ps(_mm_setzero_ps(), v);
                _mm_store_ps(p, neg);
            }
        }
    }
}

// @ 0x00783f40
void FUN_00783f40(int order, int a, int b, void* out)
{
    switch (order) {
    case 3: SP_MultiplySH(9, a, b, out, &kBasisTriples3); break;
    case 4: SP_MultiplySH(0x10, a, b, out, &kBasisTriples4); break;
    case 5: SP_MultiplySH(0x19, a, b, out, &kBasisTriples5); break;
    }
}

// @ 0x00783590
void ApplyNormalizationConstants(int order, float* v)
{
#define MUL4(c, o) do { float a=v[(o)+1], b=v[(o)+2], d=v[(o)+3]; v[(o)]=(c)*v[(o)]; v[(o)+1]=(c)*a; v[(o)+2]=(c)*b; v[(o)+3]=(c)*d; } while(0)
    MUL4(kSH_Y_00, 0);
    if (1 < order) {
        MUL4(kSH_Y_1x, 4);
        float y1 = kSH_Y_1x;
        v[8] = y1 * v[8]; v[9] = y1 * v[9]; v[0xa] = y1 * v[0xa]; v[0xb] = y1 * v[0xb];
        v[0xc] = y1 * v[0xc]; v[0xd] = y1 * v[0xd]; v[0xe] = y1 * v[0xe]; v[0xf] = y1 * v[0xf];
        if (2 < order) {
            MUL4(kSH_Y_2_2, 0x10);
            MUL4(kSH_Y_2_1, 0x14);
            MUL4(kSH_Y_20, 0x18);
            MUL4(kSH_Y_21, 0x1c);
            MUL4(kSH_Y_22, 0x20);
            if (3 < order) {
                MUL4(kSH_Y_3_3, 0x24);
                MUL4(kSH_Y_3_2, 0x28);
                MUL4(kSH_Y_3_1, 0x2c);
                MUL4(kSH_Y_30, 0x30);
                MUL4(kSH_Y_31, 0x34);
                MUL4(kSH_Y_32, 0x38);
                MUL4(kSH_Y_33, 0x3c);
                if (4 < order) {
                    MUL4(kSH_Y_4_4, 0x40);
                    MUL4(kSH_Y_4_3, 0x44);
                    MUL4(kSH_Y_4_2, 0x48);
                    MUL4(kSH_Y_4_1, 0x4c);
                    MUL4(kSH_Y_40, 0x50);
                    MUL4(kSH_Y_41, 0x54);
                    MUL4(kSH_Y_42, 0x58);
                    MUL4(kSH_Y_43, 0x5c);
                    MUL4(kSH_Y_44, 0x60);
                }
            }
        }
    }
#undef MUL4
}

// @ 0x00783830
void RemoveNormalizationConstants(int order, float* v)
{
#define MUL4(c, o) do { float a=1.0f/(c); v[(o)]=a*v[(o)]; v[(o)+1]=a*v[(o)+1]; v[(o)+2]=a*v[(o)+2]; v[(o)+3]=a*v[(o)+3]; } while(0)
    MUL4(kSH_Y_00, 0);
    if (1 < order) {
        float a = 1.0f / kSH_Y_1x;
        v[4] = a * v[4]; v[5] = a * v[5]; v[6] = a * v[6]; v[7] = a * v[7];
        v[8] = a * v[8]; v[9] = a * v[9]; v[0xa] = a * v[0xa]; v[0xb] = a * v[0xb];
        v[0xc] = a * v[0xc]; v[0xd] = a * v[0xd]; v[0xe] = a * v[0xe]; v[0xf] = a * v[0xf];
        if (2 < order) {
            MUL4(kSH_Y_2_2, 0x10);
            MUL4(kSH_Y_2_1, 0x14);
            MUL4(kSH_Y_20, 0x18);
            MUL4(kSH_Y_21, 0x1c);
            MUL4(kSH_Y_22, 0x20);
            if (3 < order) {
                MUL4(kSH_Y_3_3, 0x24);
                MUL4(kSH_Y_3_2, 0x28);
                MUL4(kSH_Y_3_1, 0x2c);
                MUL4(kSH_Y_30, 0x30);
                MUL4(kSH_Y_31, 0x34);
                MUL4(kSH_Y_32, 0x38);
                MUL4(kSH_Y_33, 0x3c);
                if (4 < order) {
                    MUL4(kSH_Y_4_4, 0x40);
                    MUL4(kSH_Y_4_3, 0x44);
                    MUL4(kSH_Y_4_2, 0x48);
                    MUL4(kSH_Y_4_1, 0x4c);
                    MUL4(kSH_Y_40, 0x50);
                    MUL4(kSH_Y_41, 0x54);
                    MUL4(kSH_Y_42, 0x58);
                    MUL4(kSH_Y_43, 0x5c);
                    MUL4(kSH_Y_44, 0x60);
                }
            }
        }
    }
#undef MUL4
}

// @ 0x00783b20
void ApplyDiffuseReflection(int order, const float* lit, const float* diff, float* out)
{
    float l1 = lit[1], l2 = lit[2], l3 = lit[3];
    float d1 = diff[1], d2 = diff[2], d3 = diff[3];
    out[0] = (lit[0] + diff[0]) * out[0];
    out[1] = (d1 + l1) * out[1];
    out[2] = (d2 + l2) * out[2];
    out[3] = (d3 + l3) * out[3];
    if (1 < order) {
        float f1 = lit[0] * 0.6666667f + diff[0];
        float f2 = lit[1] * 0.6666667f + diff[1];
        float f3 = lit[2] * 0.6666667f + diff[2];
        float f4 = lit[3] * 0.6666667f + diff[3];
        out[4] *= f1; out[5] *= f2; out[6] *= f3; out[7] *= f4;
        out[8] *= f1; out[9] *= f2; out[0xa] *= f3; out[0xb] *= f4;
        out[0xc] *= f1; out[0xd] *= f2; out[0xe] *= f3; out[0xf] *= f4;
        if (2 < order) {
            float g1 = lit[0] * 0.25f + diff[0];
            float g2 = lit[1] * 0.25f + diff[1];
            float g3 = lit[2] * 0.25f + diff[2];
            float g4 = lit[3] * 0.25f + diff[3];
            out[0x10] *= g1; out[0x11] *= g2; out[0x12] *= g3; out[0x13] *= g4;
            out[0x14] *= g1; out[0x15] *= g2; out[0x16] *= g3; out[0x17] *= g4;
            out[0x18] *= g1; out[0x19] *= g2; out[0x1a] *= g3; out[0x1b] *= g4;
            out[0x1c] *= g1; out[0x1d] *= g2; out[0x1e] *= g3; out[0x1f] *= g4;
            out[0x20] *= g1; out[0x21] *= g2; out[0x22] *= g3; out[0x23] *= g4;
            if (3 < order) {
                float* p = out + 0x24;
                for (int k = 0; k < 7; ++k) {
                    p[0] *= diff[0]; p[1] *= diff[1]; p[2] *= diff[2]; p[3] *= diff[3];
                    p += 4;
                }
                if (4 < order) {
                    float h1 = lit[0] * -0.041666668f + diff[0];
                    float h2 = lit[1] * -0.041666668f + diff[1];
                    float h3 = lit[2] * -0.041666668f + diff[2];
                    float h4 = lit[3] * -0.041666668f + diff[3];
                    p = out + 0x40;
                    for (int k = 0; k < 9; ++k) {
                        p[0] *= h1; p[1] *= h2; p[2] *= h3; p[3] *= h4;
                        p += 4;
                    }
                    if (5 < order && 0x19 < order * order) {
                        p = out + 100;
                        for (int k = order * order - 0x19; k != 0; --k) {
                            p[0] *= diff[0]; p[1] *= diff[1]; p[2] *= diff[2]; p[3] *= diff[3];
                            p += 4;
                        }
                    }
                }
            }
        }
    }
}

// @ 0x00783cf0 -- complete but shape-approximate (see nonmatching.txt)
void SP_MultiplySH(int count, int a, int b, void* out, char* triples)
{
    float* o = (float*)out;
    for (int i = 0; i < count; ++i)
        o[i] = 0.0f;
    for (char* t = triples; t[0] >= 0; t += 8) {
        float w = *(float*)(t + 4);
        int x = t[0], y = t[1], z = t[2];
        const float* px = (const float*)(x * 16 + a);
        const float* py = (const float*)(y * 16 + b);
        float* pz = (float*)(z * 16 + (int)out);
        if (x == y) {
            pz[0] += w * px[0] * py[0];
            pz[1] += w * px[1] * py[1];
            pz[2] += w * px[2] * py[2];
            pz[3] += w * px[3] * py[3];
            if (y != z) {
                float* pz2 = (float*)(x * 16 + (int)out);
                const float* q1 = (const float*)(y * 16 + a);
                const float* q2 = (const float*)(z * 16 + b);
                pz2[0] += w * q1[0] * q2[0];
                pz2[1] += w * q1[1] * q2[1];
                pz2[2] += w * q1[2] * q2[2];
                pz2[3] += w * q1[3] * q2[3];
            }
        } else if (y == z) {
            pz[0] += w * px[0] * py[0];
            pz[1] += w * px[1] * py[1];
            pz[2] += w * px[2] * py[2];
            pz[3] += w * px[3] * py[3];
            float* pz2 = (float*)(y * 16 + (int)out);
            const float* q1 = (const float*)(x * 16 + a);
            const float* q2 = (const float*)(z * 16 + b);
            pz2[0] += w * q1[0] * q2[0];
            pz2[1] += w * q1[1] * q2[1];
            pz2[2] += w * q1[2] * q2[2];
            pz2[3] += w * q1[3] * q2[3];
        } else {
            const float* q1 = (const float*)(y * 16 + a);
            const float* q2 = (const float*)(z * 16 + b);
            pz[0] += w * (px[0] * py[0] + q1[0] * q2[0]);
            pz[1] += w * (px[1] * py[1] + q1[1] * q2[1]);
            pz[2] += w * (px[2] * py[2] + q1[2] * q2[2]);
            pz[3] += w * (px[3] * py[3] + q1[3] * q2[3]);
        }
    }
}

// @ 0x00783fb0 -- PARTIAL: environment-map projection loop skeleton
void FindSHCoeffsFromHemiEnvMap(int env, int order, float* out)
{
    int w = *(int*)(env + 0x1c);
    int h = *(int*)(env + 0x20);
    float scale = (g_153ae10 * 2.0f) / (float)w;
    for (int y = 0; y < h; ++y) {
        float ny = 1.0f - ((float)y + 0.5f + (float)y + 0.5f) / (float)h;
        for (int x = 0; x < w; ++x) {
            float nx = ((float)x + 0.5f + (float)x + 0.5f) / (float)w - 1.0f;
            float r2 = nx * nx + ny * ny;
            if (r2 <= 1.0f) {
                // omitted: texture sample, Legendre evaluation and 4-channel accumulate
                (void)scale;
                (void)order;
                (void)out;
            }
        }
    }
}
