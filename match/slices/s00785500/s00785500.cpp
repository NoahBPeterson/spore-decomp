// Slice s00785500: one 4022-byte function, the explicit template instance
// SP::RotateZHToSHAdd<rw::math::vpu::Vector4, rw::math::vpu::Vector4> (0x785500).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast  (fp:fast: the original spills x87 float temporaries to dword slots; the checker FAILs at /fp:precise)
//
// Rotates the zonal-harmonic coefficients (in) by the direction p and accumulates into
// the SH output (out): band l (up to order 8) is built from band l-1 with the usual
// SH rotation recurrence, then every row is scaled by the matching Vector4 of `in`.
// The k* globals are runtime-initialised SH constants (zero in the image).  The
// sqrt(<double>) forms are the original's fsqrt of table doubles (not folded by cl).
#include "types.h"
#include <math.h>

// kXXX lives at 0x01634XXX in the original image.
extern float k05c;  // 0x0163405c
extern float k064;  // 0x01634064
extern float k074;  // 0x01634074
extern float k078;  // 0x01634078
extern float k07c;  // 0x0163407c
extern float k09c;  // 0x0163409c
extern float k0a8;  // 0x016340a8
extern float k0b0;  // 0x016340b0
extern float k0cc;  // 0x016340cc
extern float k0d4;  // 0x016340d4
extern float k0dc;  // 0x016340dc
extern float k0e4;  // 0x016340e4
extern float k0e8;  // 0x016340e8
extern float k0ec;  // 0x016340ec
extern float k0f8;  // 0x016340f8
extern float k0fc;  // 0x016340fc
extern float k104;  // 0x01634104
extern float k10c;  // 0x0163410c
extern float k130;  // 0x01634130
extern float k134;  // 0x01634134
extern float k150;  // 0x01634150
extern float k168;  // 0x01634168
extern float k1b0;  // 0x016341b0
extern float k1dc;  // 0x016341dc
extern float k1e0;  // 0x016341e0

static inline double S(double v) { return sqrt(v); }

// @ 0x00785500
void SP_RotateZHToSHAdd(float* P, int order, float* in, float* out)
{
    out[0] += in[0];
    out[1] += in[1];
    out[2] += in[2];
    out[3] += in[3];
    if (order < 2) return;

    const float b = P[1];
    const float c = P[2];
    const float a = P[0];

    // band 1
    {
        const float w[3] = { b, c, a };
        for (int i = 0; i < 3; ++i) {
            out[4 + i * 4 + 0] += w[i] * in[4];
            out[4 + i * 4 + 1] += w[i] * in[5];
            out[4 + i * 4 + 2] += w[i] * in[6];
            out[4 + i * 4 + 3] += w[i] * in[7];
        }
    }
    if (order < 3) return;

    // band 2
    float t[5];
    t[0] = ((a * b) * 2.0f) * k104;
    t[1] = ((c * b) * 2.0f) * k104;
    t[2] = c * c - (b * b + a * a) * k0dc;
    t[3] = ((a * c) * 2.0f) * k104;
    t[4] = (a * a - b * b) * k104;
    {
        float* o = out + 0x10;
        for (int i = 0; i < 5; ++i, o += 4) {
            const float v = t[i];
            o[0] += v * in[8];
            o[1] += v * in[9];
            o[2] += v * in[10];
            o[3] += v * in[11];
        }
    }
    if (order < 4) return;

    // band 3
    float s[7];
    s[0] = (t[4] * b + t[0] * a) * k078;
    s[1] = ((t[1] * a + t[3] * b) + t[0] * c) * k0cc;
    s[2] = ((k1e0 * t[1]) * c - (t[0] * a - t[4] * b) * k1b0) + (k150 * t[2]) * b;
    s[3] = t[2] * c - (t[1] * b + t[3] * a) * k0b0;
    s[4] = ((k150 * t[2]) * a - (t[0] * b + t[4] * a) * k1b0) + (k1e0 * t[3]) * c;
    s[5] = ((t[3] * a - t[1] * b) + t[4] * c) * k0cc;
    s[6] = (t[4] * a - t[0] * b) * k078;
    {
        float* o = out + 0x24;
        for (int i = 0; i < 7; ++i, o += 4) {
            const float v = s[i];
            o[0] = v * in[12];
            o[1] = v * in[13];
            o[2] = v * in[14];
            o[3] = v * in[15];
        }
    }
    if (order < 5) return;

    // band 4
    float q[9];
    q[0] = (s[6] * b + s[0] * a) * k0fc;
    q[1] = (s[5] * b + s[1] * a) * k09c + (k1dc * s[0]) * c;
    q[2] = ((s[2] * a + s[4] * b) * k0d4 - (s[0] * a - s[6] * b) * k130) + (k104 * s[1]) * c;
    q[3] = ((k0e8 * s[2]) * c - (s[1] * a - s[5] * b) * k074) + (k0ec * s[3]) * b;
    q[4] = s[3] * c - (s[2] * b + s[4] * a) * k0f8;
    q[5] = ((k0ec * s[3]) * a - (s[1] * b + s[5] * a) * k074) + (k0e8 * s[4]) * c;
    q[6] = ((s[4] * a - s[2] * b) * k0d4 - (s[0] * b + s[6] * a) * k130) + (k104 * s[5]) * c;
    q[7] = (s[5] * a - s[1] * b) * k09c + (k1dc * s[6]) * c;
    q[8] = (s[6] * a - s[0] * b) * k0fc;
    {
        float* o = out + 0x40;
        for (int i = 0; i < 9; ++i, o += 4) {
            const float v = q[i];
            o[0] = v * in[16];
            o[1] = v * in[17];
            o[2] = v * in[18];
            o[3] = v * in[19];
        }
    }
    if (order < 6) return;

    // band 5
    float r[11];
    r[0] = (q[8] * b + q[0] * a) * S(0.9);
    r[1] = (c * q[0]) * S(0.36) + (q[7] * b + q[1] * a) * k134;
    r[2] = (q[1] * c) * S(0.64) + ((q[6] * b + q[2] * a) * k10c - (q[0] * a - q[8] * b) * k168);
    r[3] = (q[2] * c) * S(0.84) + ((q[5] * b + q[3] * a) * k0e4 - (q[1] * a - q[7] * b) * k0a8);
    r[4] = (q[3] * c) * S(0.96) + ((q[4] * k064) * b - (q[2] * a - q[6] * b) * k05c);
    r[5] = q[4] * c - (q[3] * b + q[5] * a) * S(0.4);
    r[6] = (q[5] * c) * S(0.96) + ((q[4] * k064) * a - (q[2] * b + q[6] * a) * k05c);
    r[7] = (q[6] * c) * S(0.84) + ((q[5] * a - q[3] * b) * k0e4 - (q[1] * b + q[7] * a) * k0a8);
    r[8] = (q[7] * c) * S(0.64) + ((q[6] * a - q[2] * b) * k10c - (q[0] * b + q[8] * a) * k168);
    r[9] = (q[8] * c) * S(0.36) + (q[7] * a - q[1] * b) * k134;
    r[10] = (q[8] * a - q[0] * b) * S(0.9);
    {
        float* o = out + 0x64;
        for (int i = 0; i < 11; ++i, o += 4) {
            const float v = r[i];
            o[0] = v * in[20];
            o[1] = v * in[21];
            o[2] = v * in[22];
            o[3] = v * in[23];
        }
    }
    if (order < 7) return;

    // band 6
    float u[13];
    u[0] = (r[0] * a + r[10] * b) * S(0.9166666666666666);
    u[1] = (r[0] * c) * S(0.3055555555555556) + (r[9] * b + r[1] * a) * S(0.7638888888888888);
    u[2] = ((r[1] * k0cc) * c + (r[8] * b + r[2] * a) * k0ec) - (r[0] * a - r[10] * b) * S(0.013888888888888888);
    u[3] = (r[2] * k104) * c + ((r[3] * a + r[7] * b) * S(0.5) - (r[1] * a - r[9] * b) * S(0.041666666666666664));
    u[4] = (r[3] * k1e0) * c + ((r[6] * b + r[4] * a) * S(0.3888888888888889) - (r[2] * a - r[8] * b) * k07c);
    u[5] = b * (r[5] * S(0.5833333333333334)) + ((r[4] * c) * S(0.9722222222222222) - (r[3] * a - r[7] * b) * S(0.1388888888888889));
    u[6] = r[5] * c - (r[4] * b + r[6] * a) * S(0.4166666666666667);
    u[7] = (r[6] * c) * S(0.9722222222222222) + (a * (r[5] * S(0.5833333333333334)) - (r[3] * b + r[7] * a) * S(0.1388888888888889));
    u[8] = (r[7] * k1e0) * c + ((r[6] * a - r[4] * b) * S(0.3888888888888889) - (r[2] * b + r[8] * a) * k07c);
    u[9] = (r[8] * k104) * c + ((r[7] * a - r[3] * b) * S(0.5) - (r[1] * b + r[9] * a) * S(0.041666666666666664));
    u[10] = ((r[9] * k0cc) * c + (r[8] * a - r[2] * b) * k0ec) - (r[0] * b + r[10] * a) * S(0.013888888888888888);
    u[11] = (r[10] * c) * S(0.3055555555555556) + (r[9] * a - r[1] * b) * S(0.7638888888888888);
    u[12] = (r[10] * a - r[0] * b) * S(0.9166666666666666);
    {
        float* o = out + 0x90;
        for (int i = 0; i < 13; ++i, o += 4) {
            const float v = u[i];
            o[0] = v * in[24];
            o[1] = v * in[25];
            o[2] = v * in[26];
            o[3] = v * in[27];
        }
    }
    if (order < 8) return;

    // band 7
    float w[15];
    w[0] = (u[0] * a + u[12] * b) * S(0.9285714285714286);
    w[1] = (u[0] * c) * S(0.2653061224489796) + (u[1] * a + u[11] * b) * S(0.7959183673469388);
    w[2] = (u[1] * c) * S(0.4897959183673469) + ((u[2] * a + u[10] * b) * S(0.673469387755102) - (u[0] * a - u[12] * b) * S(0.01020408163265306));
    w[3] = (u[2] * c) * S(0.673469387755102) + ((u[3] * a + u[9] * b) * S(0.5612244897959183) - (u[1] * a - u[11] * b) * S(0.030612244897959183));
    w[4] = (u[3] * c) * S(0.8163265306122449) + ((u[4] * a + u[8] * b) * S(0.45918367346938777) - (u[2] * a - u[10] * b) * S(0.061224489795918366));
    w[5] = (u[4] * c) * S(0.9183673469387755) + ((u[7] * b + u[5] * a) * S(0.3673469387755102) - (u[3] * a - u[9] * b) * S(0.10204081632653061));
    w[6] = b * (u[6] * S(0.5714285714285714)) + ((u[5] * c) * S(0.9795918367346939) - (u[4] * a - u[8] * b) * S(0.15306122448979592));
    w[7] = u[6] * c - (u[5] * b + u[7] * a) * S(0.42857142857142855);
    w[8] = (u[7] * c) * S(0.9795918367346939) + (a * (u[6] * S(0.5714285714285714)) - (u[4] * b + u[8] * a) * S(0.15306122448979592));
    w[9] = (c * u[8]) * S(0.9183673469387755) + ((u[7] * a - u[5] * b) * S(0.3673469387755102) - (u[3] * b + u[9] * a) * S(0.10204081632653061));
    w[10] = (u[9] * c) * S(0.8163265306122449) + ((u[8] * a - u[4] * b) * S(0.45918367346938777) - (u[2] * b + u[10] * a) * S(0.061224489795918366));
    w[11] = (c * u[10]) * S(0.673469387755102) + ((u[9] * a - u[3] * b) * S(0.5612244897959183) - (u[1] * b + u[11] * a) * S(0.030612244897959183));
    w[12] = (u[11] * c) * S(0.4897959183673469) + ((u[10] * a - u[2] * b) * S(0.673469387755102) - (u[0] * b + u[12] * a) * S(0.01020408163265306));
    w[13] = (u[12] * c) * S(0.2653061224489796) + (u[11] * a - u[1] * b) * S(0.7959183673469388);
    w[14] = (u[12] * a - u[0] * b) * S(0.9285714285714286);
    {
        float* o = out + 0xc4;
        for (int i = 0; i < 15; ++i, o += 4) {
            const float v = w[i];
            o[0] = v * in[28];
            o[1] = v * in[29];
            o[2] = v * in[30];
            o[3] = v * in[31];
        }
    }
}
