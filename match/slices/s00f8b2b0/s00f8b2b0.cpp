// Slice s00f8b2b0 (batch big0, slice 13): SP::UpdateNormalMap.
// Behavioural transcription of the Ghidra decompile; /O2 + /arch:SSE /fp:fast
// (prologue `sub esp,0x100` + rdtsc, no frame pointer). Types that Ghidra
// mangled (int/float reuse, pointer-punned locals) were resolved from the asm:
//   - t0..t3 are the clamped int sub-rectangles,
//   - bit0..bit3 of the face flag are the six cube-face guard conditions,
//   - cscale[3] is the format-dependent normal->colour axis {s,1,s}.
#include "types.h"
#include <math.h>

// --- masked callees ---------------------------------------------------------
extern void FUN_00f7d9d0(int, int, int, int, int, int, int,
                         float, float, float, float, float, float, int, int, int); // 0xf7d9d0
extern void WrapCubeFace(int width, void* a, void* b, void* c, void* d, void* e);   // 0x684ca0
extern int  SP_cPropertyList_GetDescription(void* list, unsigned int id);           // 0x???? placeholder
extern int  DAT_016c9bc4;
extern const unsigned char DAT_0148ff28[];

static int  RND(float x) { return (int)x; }   // cvttss2si (trunc), then floor-correct below

// pack a normal subject to the format permutation/sign and the alpha byte.
static unsigned PackRGBA(const float* n, float alpha, const int* idx, const float* cs)
{
    float r = n[idx[0]] * (cs[0] * 0.5f) + 0.5f;
    float g = n[idx[1]] * (cs[1] * 0.5f) + 0.5f;
    float b = n[idx[2]] * (cs[2] * 0.5f) + 0.5f;
    unsigned a = (unsigned)RND(alpha * 255.0f) & 0xffU;
    unsigned bb = (unsigned)RND(b * 255.0f) & 0xffU;
    unsigned gg = (unsigned)RND(g * 255.0f) & 0xffU;
    unsigned rr = (unsigned)RND(r * 255.0f) & 0xffU;
    return (((a << 8 | bb) << 8 | gg) << 8 | rr);
}

// @ 0x00f8b2b0
int FUN_00f8b2b0(int param_1, int param_2, int param_3, float param_4, float param_5,
                 float param_6, float param_7, float param_8, float param_9, float param_10)
{
    int width = *(int*)(param_1 + 8);
    float wf = (float)width;

    // ---- clamped integer sub-rectangle (t0=x0, t2=x1, t1=y0, t3=y1) -------
    int t0 = RND(param_7 * wf);
    if (param_7 * wf < (float)t0) t0 = t0 - 1;
    int t2 = RND(param_9 * wf);
    if (param_9 * wf < (float)t2) t2 = t2 - 1;
    int t1r = RND(param_8 * wf);
    if (param_8 * wf < (float)t1r) t1r = t1r - 1;
    float t3f = param_10 * wf;
    int t3 = RND(t3f);
    if (t3f < (float)t3) t3 = t3 - 1;

    int flag0, flag1, flag2, flag3;
    if (t0 < 1) { flag0 = 1; t0 = 1; } else flag0 = 0;
    int fv1 = width - 1;
    if (fv1 <= t2) { flag1 = 1; t2 = width - 2; } else flag1 = 0;
    if (t1r < 1) { flag2 = 1; t1r = 1; } else flag2 = 0;
    if (fv1 <= t3) { flag3 = 1; t3 = width - 2; } else flag3 = 0;

    // ---- format tables and the normal->colour axis {s, 1, s} --------------
    int iVar6 = (param_3 >> 1) * 4;
    float s = ((param_3 & 1) == 0) ? 1.0f : -1.0f;
    int idx[3];
    idx[0] = DAT_0148ff28[iVar6 + 0];
    idx[1] = DAT_0148ff28[iVar6 + 1];
    idx[2] = DAT_0148ff28[iVar6 + 2];
    float axis[3] = { s, 1.0f, s };
    float cscale[3] = { axis[idx[0]], axis[idx[1]], axis[idx[2]] };

    if (DAT_016c9bc4 == 0) {
        FUN_00f7d9d0(*(int*)(param_2 + 0x10) +
                         *(int*)(param_2 + 8) * *(int*)(param_2 + 8) * param_3 * 4,
                     *(int*)(param_1 + 0x10) +
                         *(int*)(param_1 + 8) * *(int*)(param_1 + 8) * param_3 * 2,
                     t0, t2, t1r, t3, (int)param_4, param_4, param_5, param_6,
                     axis[idx[0]], axis[idx[1]], axis[idx[2]],
                     idx[0], idx[1], idx[2]);
    }
    (void)SP_cPropertyList_GetDescription(0, 0xbb60eb9c);

    if ((flag0 | flag1 | flag2 | flag3) == 0)
        return 0;

    // ---- loop constants ---------------------------------------------------
    param_5 = param_5 * 0.5f;
    float local_60 = param_4 - param_5;
    float local_5c = param_5 * 3.0518044e-05f;
    float local_50 = cscale[0] * 0.5f;
    float local_3c = cscale[1] * 0.5f;
    float local_a0 = (wf * 0.5f) * (param_5 * 3.0518044e-05f);
    float local_54 = 2.0f / (param_5 * param_6);
    float local_98 = 2.0f / wf;
    float local_38 = cscale[2] * 0.5f;
    int w2 = width * width;
    unsigned char* heightBase = (unsigned char*)(*(int*)(param_1 + 0x10));
    unsigned char* dstBase = (unsigned char*)(*(int*)(param_2 + 0x10));
    int dstW = *(int*)(param_2 + 8);

    // ======================================================================
    // face flag2 (local_9c._2_1_): rows t0..t2
    // ======================================================================
    if (flag2) {
        float lf0 = (float)t0;
        float lf8 = (float)param_3;
        int   lf4 = -1;
        int   le4 = 1;
        float lfc = 0.0f;
        WrapCubeFace(width, &lf8, &lf0, &lf4, &le4, &lfc);
        int i6 = *(int*)(param_1 + 8) * *(int*)(param_1 + 8);
        unsigned short* local_d0 = (unsigned short*)
            (*(int*)(param_1 + 0x10) + i6 * param_3 * 2);
        int local_ac = *(int*)(param_2 + 0x10) +
                       *(int*)(param_2 + 8) * *(int*)(param_2 + 8) * param_3 * 4;
        unsigned short* local_8c = (unsigned short*)
            (*(int*)(param_1 + 0x10) +
             ((int)lf4 * width + i6 * (int)lf8 + (int)lf0) * 2);
        float cc = local_98 * 0.5f - 1.0f;
        float b0 = ((float)t0 + 0.5f) * local_98 - 1.0f;
        if (t0 <= t2) {
            float ec = (float)((int)lfc * width * 2);
            unsigned* c8 = (unsigned*)(local_d0 + t0 + width);
            local_d0 = local_d0 + t0 + 1;
            int f8i = t0;
            do {
                float hyp = sqrtf((b0 * b0 + cc * cc) + 1.0f);
                float du = (float)((int)*local_8c - (int)(unsigned short)*c8) * local_a0;
                float dv = (float)((int)local_d0[-2] - (int)*local_d0) * local_a0;
                float inv = 1.0f / hyp;
                float h = hyp / ((float)local_d0[-1] * local_5c + local_60);
                float nx = h * du;
                float ny = h * dv;
                float nrm[3];
                nrm[1] = inv * b0 + ny;
                nrm[2] = inv * cc + nx;
                nrm[0] = inv - (ny * b0 + nx * cc);
                float len = ((nrm[1] * nrm[1] + nrm[0] * nrm[0]) + nrm[2] * nrm[2]) + 1e-08f;
                float sc = 1.0f / sqrtf(len);
                nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
                float alpha = sqrtf(dv * dv + du * du) * local_54;
                if (alpha < 0.0f) alpha = 0.0f;
                if (alpha > 1.0f) alpha = 1.0f;
                *(unsigned*)(local_ac + f8i * 4) = PackRGBA(nrm, alpha, idx, cscale);
                local_8c = (unsigned short*)((char*)local_8c + (int)ec);
                f8i = f8i + 1;
                local_d0 = local_d0 + 1;
                b0 = b0 + local_98;
            } while (f8i <= t2);
        }
    }

    // ======================================================================
    // face flag3 (local_9c._3_1_): rows t0..t2 (transposed)
    // ======================================================================
    if (flag3) {
        float lf0 = (float)param_3;
        int   le4 = 1;
        float lfc = 0.0f;
        float lf4 = (float)t0;
        float lf8 = (float)width;
        WrapCubeFace(width, &lf4, &lfc, &lf8, &le4, &lf0);
        int i6 = *(int*)(param_1 + 8) * *(int*)(param_1 + 8);
        unsigned short* local_d0 = (unsigned short*)
            (*(int*)(param_1 + 0x10) +
             (i6 * (int)lf4 + (int)lf8 * width + (int)lfc) * 2);
        float ec = (float)((int)lf0 * width);
        int local_ac = *(int*)(param_1 + 0x10) +
                       (i6 * param_3 + (width - 1) * width) * 2;
        int local_24 = *(int*)(param_2 + 0x10) +
                       (*(int*)(param_2 + 8) * *(int*)(param_2 + 8) * param_3 +
                        (width - 1) * width) * 4;
        float cc = ((float)(width - 1) + 0.5f) * local_98 - 1.0f;
        float b0 = ((float)t0 + 0.5f) * local_98 - 1.0f;
        if (t0 <= t2) {
            unsigned* c8 = (unsigned*)(local_ac + (t0 - width) * 2);
            unsigned short* local_8c = (unsigned short*)(local_ac + 2 + t0 * 2);
            int f8i = t0;
            do {
                float hyp = sqrtf((b0 * b0 + cc * cc) + 1.0f);
                float du = (float)((int)local_8c[-2] - (int)*local_8c) * local_a0;
                float dv = (float)((int)(unsigned short)*c8 - (int)*local_d0) * local_a0;
                float inv = 1.0f / hyp;
                float h = hyp / ((float)local_8c[-1] * local_5c + local_60);
                float du2 = du * h;
                float dv2 = dv * h;
                float nrm[3];
                nrm[0] = b0 * inv + du2;
                nrm[1] = cc * inv + dv2;
                nrm[2] = inv - (cc * dv2 + b0 * du2);
                float len = ((nrm[2] * nrm[2] + nrm[1] * nrm[1]) + nrm[0] * nrm[0]) + 1e-08f;
                float sc = 1.0f / sqrtf(len);
                nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
                float alpha = sqrtf(du * du + dv * dv) * local_54;
                if (alpha < 0.0f) alpha = 0.0f;
                if (alpha > 1.0f) alpha = 1.0f;
                *(unsigned*)(local_24 + f8i * 4) = PackRGBA(nrm, alpha, idx, cscale);
                local_d0 = (unsigned short*)((char*)local_d0 + (int)ec);
                f8i = f8i + 1;
                local_8c = local_8c + 1;
                b0 = b0 + local_98;
            } while (f8i <= t2);
        }
    }

    // ======================================================================
    // face flag0 ((char)local_9c): columns t1r..t3
    // ======================================================================
    if (flag0) {
        float lf4 = (float)t1r;
        float lf0 = (float)param_3;
        int   lf8 = -1;
        float lfc = 0.0f;
        int   le4 = 1;
        WrapCubeFace(width, &lf0, &lf8, &lf4, &lfc, &le4);
        float lb0 = (float)(*(int*)(param_1 + 0x10));
        int i6 = *(int*)(param_1 + 8) * *(int*)(param_1 + 8);
        unsigned short* local_d0 = (unsigned short*)
            ((int)lb0 + (i6 * (int)lf0 + (int)lf4 * width + (int)lf8) * 2);
        unsigned short* puVar9 = (unsigned short*)
            ((int)lb0 + (i6 * param_3 + t1r * width) * 2);
        float b0 = ((float)t1r + 0.5f) * local_98 - 1.0f;
        unsigned* c8 = (unsigned*)(*(int*)(param_2 + 0x10) +
            (*(int*)(param_2 + 8) * *(int*)(param_2 + 8) * param_3 + t1r * width) * 4);
        float cc = local_98 * 0.5f - 1.0f;
        if (t1r <= t3) {
            int cnt = (t3 - t1r) + 1;
            do {
                float hyp = sqrtf((b0 * b0 + cc * cc) + 1.0f);
                float du = (float)((int)*local_d0 - (int)puVar9[1]) * local_a0;
                float dv = (float)((int)puVar9[-width] - (int)puVar9[width]) * local_a0;
                float inv = 1.0f / hyp;
                float h = hyp / ((float)*puVar9 * local_5c + local_60);
                float nx = du * h;
                float ny = dv * h;
                float nrm[3];
                nrm[0] = cc * inv + nx;
                nrm[1] = b0 * inv + ny;
                nrm[2] = inv - (b0 * ny + cc * nx);
                float len = ((nrm[2] * nrm[2] + nrm[1] * nrm[1]) + nrm[0] * nrm[0]) + 1e-08f;
                float sc = 1.0f / sqrtf(len);
                nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
                float alpha = sqrtf(du * du + dv * dv) * local_54;
                if (alpha < 0.0f) alpha = 0.0f;
                if (alpha > 1.0f) alpha = 1.0f;
                *c8 = PackRGBA(nrm, alpha, idx, cscale);
                c8 += width;
                local_d0 = (unsigned short*)((char*)local_d0 + (int)lfc);
                puVar9 += width;
                b0 = b0 + local_98;
            } while (--cnt != 0);
        }
    }

    // ======================================================================
    // face flag1 (local_9c._1_1_): columns t1r..t3 (transposed)
    // ======================================================================
    if (flag1) {
        float lf4 = (float)t1r;
        float lf0 = (float)param_3;
        float lfc = 0.0f;
        int   le4 = 1;
        float lf8 = (float)width;
        WrapCubeFace(width, &lf0, &lf8, &lf4, &lfc, &le4);
        float lb0 = (float)(*(int*)(param_1 + 0x10));
        int i6 = *(int*)(param_1 + 8) * *(int*)(param_1 + 8);
        unsigned short* local_d0 = (unsigned short*)
            ((int)lb0 + (i6 * (int)lf0 + (int)lf4 * width + (int)lf8) * 2);
        unsigned short* puVar9 = (unsigned short*)
            ((int)lb0 + (i6 * param_3 + t1r * width + (width - 1)) * 2);
        float b0 = ((float)t1r + 0.5f) * local_98 - 1.0f;
        unsigned* c8 = (unsigned*)(*(int*)(param_2 + 0x10) +
            (*(int*)(param_2 + 8) * *(int*)(param_2 + 8) * param_3 +
             t1r * width + (width - 1)) * 4);
        float cc = ((float)(width - 1) + 0.5f) * local_98 - 1.0f;
        if (t1r <= t3) {
            int cnt = (t3 - t1r) + 1;
            do {
                float hyp = sqrtf((b0 * b0 + cc * cc) + 1.0f);
                float du = (float)((int)puVar9[-1] - (int)*local_d0) * local_a0;
                float dv = (float)((int)puVar9[-width] - (int)puVar9[width]) * local_a0;
                float inv = 1.0f / hyp;
                float h = hyp / ((float)*puVar9 * local_5c + local_60);
                float nx = du * h;
                float ny = dv * h;
                float nrm[3];
                nrm[0] = cc * inv + nx;
                nrm[1] = b0 * inv + ny;
                nrm[2] = inv - (b0 * ny + cc * nx);
                float len = ((nrm[0] * nrm[0] + nrm[2] * nrm[2]) + nrm[1] * nrm[1]) + 1e-08f;
                float sc = 1.0f / sqrtf(len);
                nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
                float alpha = sqrtf(du * du + dv * dv) * local_54;
                if (alpha < 0.0f) alpha = 0.0f;
                if (alpha > 1.0f) alpha = 1.0f;
                *c8 = PackRGBA(nrm, alpha, idx, cscale);
                c8 += width;
                local_d0 = (unsigned short*)((char*)local_d0 + (int)lfc);
                puVar9 += width;
                b0 = b0 + local_98;
            } while (--cnt != 0);
        }
    }

    // ======================================================================
    // corner texels (single pixel each)
    // ======================================================================
    if (flag2) {
        if (flag0) {
            int fa[3] = { -1, 0, param_3 };
            int fbc = (int)~(unsigned)(width - 1);
            float fc0 = 0.0f;
            int fb8 = param_3;
            if (fbc != 0)
                WrapCubeFace(width, &fa[2], fa, &fa[1], 0, 0);
            if (((unsigned)fbc & ((unsigned)fbc | (unsigned)(int)fc0)) != 0)
                WrapCubeFace(width, &fb8, &fc0, &fbc, 0, 0);
            int i6 = width;
            int c4 = i6 * param_3;
            int c8 = c4 * i6;
            float cc = local_98 * 0.5f - 1.0f;
            unsigned char* hb = heightBase;
            float len = sqrtf((cc * cc + cc * cc) + 1.0f);
            float duN = (float)(int)(*(unsigned short*)(hb +
                             ((fa[2] * i6 + fa[1]) * i6 + fa[0]) * 2) -
                         *(unsigned short*)(hb + 2 + c8 * 2)) * local_a0;
            float dvN = (float)(int)(*(unsigned short*)(hb +
                             ((fb8 * i6 + fbc) * i6 + (int)fc0) * 2) -
                         *(unsigned short*)(hb + (c4 + 1) * i6 * 2)) * local_a0;
            float inv = 1.0f / len;
            float h = len / ((float)*(unsigned short*)(hb + c8 * 2) * local_5c + local_60);
            float nx = duN * h;
            float ny = dvN * h;
            float nrm[3];
            nrm[0] = cc * inv + nx;
            nrm[1] = cc * inv + ny;
            nrm[2] = inv - (cc * nx + cc * ny);
            float l2 = ((nrm[2] * nrm[2] + nrm[1] * nrm[1]) + nrm[0] * nrm[0]) + 1e-08f;
            float sc = 1.0f / sqrtf(l2);
            nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
            float alpha = sqrtf(duN * duN + dvN * dvN) * local_54;
            if (alpha < 0.0f) alpha = 0.0f;
            if (alpha > 1.0f) alpha = 1.0f;
            *(unsigned*)(*(int*)(param_2 + 0x10) +
                         *(int*)(param_2 + 8) * *(int*)(param_2 + 8) * param_3 * 4) =
                PackRGBA(nrm, alpha, idx, cscale);
        }
        if (flag1) {
            int fa[3] = { width, 0, param_3 };
            int c4 = (int)~(unsigned)(width - 1);
            int fb8 = (int)(width - 2) + width;
            int i6 = width;
            float cc = local_98 * 0.5f - 1.0f;
            float b0 = ((float)(width - 1) + 0.5f) * local_98 - 1.0f;
            float hyp = sqrtf((b0 * b0 + cc * cc) + 1.0f);
            unsigned char* hb = heightBase;
            float v84 = (float)(int)(*(unsigned short*)(hb +
                             ((c4 * i6 + width - 1)) * 2) -
                         *(unsigned short*)(hb +
                             ((fa[2] * i6 + fa[1]) * i6 + fa[0]) * 2)) * local_a0;
            float v88 = (float)(int)(*(unsigned short*)(hb +
                             ((fb8 * i6 + c4)) * 2) -
                         *(unsigned short*)(hb +
                             (((c4 + 1) * i6 + width - 1)) * 2)) * local_a0;
            float inv = 1.0f / hyp;
            float h = hyp / ((float)*(unsigned short*)(hb + ((c4 * i6 + (int)(width - 1)) * 2)) * local_5c + local_60);
            float nx = v84 * h;
            float ny = v88 * h;
            float nrm[3];
            nrm[2] = inv - (b0 * nx + cc * ny);
            nrm[0] = b0 * inv + nx;
            nrm[1] = cc * inv + ny;
            float l2 = ((nrm[2] * nrm[2] + nrm[1] * nrm[1]) + nrm[0] * nrm[0]) + 1e-08f;
            float sc = 1.0f / sqrtf(l2);
            nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
            float alpha = sqrtf(v84 * v84 + v88 * v88) * local_54;
            if (alpha < 0.0f) alpha = 0.0f;
            if (alpha > 1.0f) alpha = 1.0f;
            *(unsigned*)(*(int*)(param_2 + 0x10) +
                         (*(int*)(param_2 + 8) * *(int*)(param_2 + 8) * param_3 + width - 1) * 4) =
                PackRGBA(nrm, alpha, idx, cscale);
        }
    }

    if (flag3) {
        if (flag0) {
            int fa[3] = { -1, width - 1, param_3 };
            int c4 = (int)~(unsigned)(width - 1);
            float fc0 = 0.0f;
            int fb8 = param_3;
            if (c4 != 0)
                WrapCubeFace(width, &fa[2], fa, &fa[1], 0, 0);
            if (((unsigned)c4 & ((unsigned)c4 | (unsigned)(int)fc0)) != 0)
                WrapCubeFace(width, &fb8, &fc0, &c4, 0, 0);
            int i6 = width;
            int c4i = i6 * param_3;
            int idx10 = (c4i + width - 1) * i6;
            float cc = ((float)(width - 1) + 0.5f) * local_98 - 1.0f;
            float b0 = local_98 * 0.5f - 1.0f;
            unsigned char* hb = heightBase;
            float hyp = sqrtf((b0 * b0 + cc * cc) + 1.0f);
            float v84 = (float)(int)(*(unsigned short*)(hb +
                             ((fa[2] * i6 + fa[1]) * i6 + fa[0]) * 2) -
                         *(unsigned short*)(hb + 2 + idx10 * 2)) * local_a0;
            float v88 = (float)(int)(*(unsigned short*)(hb +
                             (((width - 2) + c4i) * i6 + width - 1) * 2) -
                         *(unsigned short*)(hb +
                             ((fb8 * i6 + c4) * i6 + (int)fc0) * 2)) * local_a0;
            float inv = 1.0f / hyp;
            float h = hyp / ((float)*(unsigned short*)(hb + (idx10 + width - 1) * 2) * local_5c + local_60);
            float nx = v84 * h;
            float ny = v88 * h;
            float nrm[3];
            nrm[2] = inv - (b0 * nx + cc * ny);
            nrm[0] = b0 * inv + nx;
            nrm[1] = cc * inv + ny;
            float l2 = ((nrm[2] * nrm[2] + nrm[1] * nrm[1]) + nrm[0] * nrm[0]) + 1e-08f;
            float sc = 1.0f / sqrtf(l2);
            nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
            float alpha = sqrtf(v84 * v84 + v88 * v88) * local_54;
            if (alpha < 0.0f) alpha = 0.0f;
            if (alpha > 1.0f) alpha = 1.0f;
            *(unsigned*)(*(int*)(param_2 + 0x10) +
                         (*(int*)(param_2 + 8) * param_3 + width - 1) *
                             *(int*)(param_2 + 8) * 4) =
                PackRGBA(nrm, alpha, idx, cscale);
        }
        if (flag1) {
            int c4 = (int)~(unsigned)(width - 1);
            int fa[3] = { width, width - 1, param_3 };
            float fc0 = 0.0f;
            int fb8 = param_3;
            if (((unsigned)c4 & ((unsigned)width | (unsigned)(width - 1))) != 0)
                WrapCubeFace(width, &fa[2], fa, &fa[1], 0, 0);
            if (((unsigned)c4 & ((unsigned)c4 | (unsigned)(int)fc0)) != 0)
                WrapCubeFace(width, &fb8, &fc0, &c4, 0, 0);
            int i6 = width;
            int c4i = i6 * param_3;
            int idx10 = (width - 1 + c4i) * i6;
            float cc = ((float)(width - 1) + 0.5f) * local_98 - 1.0f;
            float b0 = ((float)(width - 1) + 0.5f) * local_98 - 1.0f;
            unsigned char* hb = heightBase;
            float hyp = sqrtf((b0 * b0 + cc * cc) + 1.0f);
            float v94 = (float)(int)(*(unsigned short*)(hb + (idx10 + width - 2) * 2) -
                         *(unsigned short*)(hb +
                             ((fa[2] * i6 + fa[1]) * i6 + fa[0]) * 2)) * local_a0;
            float v84 = (float)(int)(*(unsigned short*)(hb +
                             (((width - 2) + c4i) * i6 + width - 1) * 2) -
                         *(unsigned short*)(hb +
                             ((fb8 * i6 + c4) * i6 + (int)fc0) * 2)) * local_a0;
            float inv = 1.0f / hyp;
            float h = hyp / ((float)*(unsigned short*)(hb + (idx10 + width - 1) * 2) * local_5c + local_60);
            float nx = v94 * h;
            float ny = v84 * h;
            float nrm[3];
            nrm[0] = b0 * inv + nx;
            nrm[1] = cc * inv + ny;
            nrm[2] = inv - (nx * b0 + ny * cc);
            float l2 = ((nrm[2] * nrm[2] + nrm[1] * nrm[1]) + nrm[0] * nrm[0]) + 1e-08f;
            float sc = 1.0f / sqrtf(l2);
            nrm[0] *= sc; nrm[1] *= sc; nrm[2] *= sc;
            float alpha = sqrtf(v94 * v94 + v84 * v84) * local_54;
            if (alpha < 0.0f) alpha = 0.0f;
            if (alpha > 1.0f) alpha = 1.0f;
            *(unsigned*)(*(int*)(param_2 + 0x10) +
                         ((*(int*)(param_2 + 8) * param_3 + width - 1) *
                              *(int*)(param_2 + 8) + (width - 1)) * 4) =
                PackRGBA(nrm, alpha, idx, cscale);
        }
    }
    return 0;
}
