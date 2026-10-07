// Slice s009b0e90 -- nSPCreatureAnim::EvaluateBoneTransform (3810 bytes, 13 stack args, __cdecl).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// Evaluates one bone's world position and orientation from the current animation state.
//   p1  flags word of the animation state (bit0 = full evaluation, bits1-2 = mode, bit3 = scaled, bit4 = alt)
//   p3  context flags (bit4 = has target, bit5/8 = parent-relative selector, 0x200 = target offset)
//   p5  secondary flags (bits 5-6 select how the target quaternion combines, bit4 = has target quaternion)
//   p7  instance (scale at +0x70, skeleton data at *(*(p7+8)))
//   p8  bone data pointer holder (*p8 = bone data: rest translation +0x10c, rest quat +0x118, ...)
//   p11 out position (3 floats), p12 out orientation (4 floats)
// Float order of operations follows the disassembly; the callees are masked relocations.
#include "types.h"

struct V3 { float x, y, z; };

float* __cdecl QuatRotate(float* out, const float* q, const float* v);                 // 0x0099C1A0 quat * vec
float* __cdecl QuatMul(float* out, const float* a, const float* b);                    // 0x0099C0B0
void   __cdecl SimpleTargetOffset(uint32_t ctxFlags, uint32_t animFlags, char* inst, char** skel, float* io); // 0x009B0D80
void   __cdecl BuildFrame(float* out, char* inst, uint32_t* state, int p2);            // 0x009B0720
float* __cdecl AdjustFrame(float* out, char* inst, int boneAux, float* in, int zero);  // 0x009B77A0
void   __cdecl SolveTarget(float* outM, float* pos, float* target, float* outLen, int a, int b, V3 up);   // 0x009B0340
float  __cdecl ChannelWeight(float* v, uint32_t ctxFlags, uint32_t animFlags, char* inst, char** skel);   // 0x009B0CB0
float* __cdecl Normalize3(float* out, float* v, float* outLen);                        // 0x009A49D0
// 0x009A4F10 (checkerlib::matrix_to_quaternion, 2 args)
float* __cdecl MatToQuat(float* out, float* m);                                        // 0x009A4F10
void   __cdecl SolveFrame(char* inst, float* q, float* q2, float* frame, float* pos, float* m);   // 0x009B07D0
extern int g_adjustFrameEnabled;                                                       // 0x01550A70

// @ 0x009B0E90
void __cdecl EvaluateBoneTransform(uint32_t* p1, int p2, uint32_t* p3, float* p4, uint32_t* p5, float* p6,
                                   char* p7, char** p8, float* p9, float* p10, float* p11, float* p12,
                                   int p13)
{
    float tmp[4];
    float scale = *(float*)(p7 + 0x70);
    char* bone = *p8;

    // rest position scaled
    float pos0 = *(float*)(bone + 0x10c) * scale;
    float pos1 = *(float*)(bone + 0x110) * scale;
    float pos2 = *(float*)(bone + 0x114) * scale;
    float tgt[3];
    tgt[0] = 0.0f; tgt[1] = 0.0f; tgt[2] = 0.0f;

    if (p3 != 0) {
        uint32_t ctx = *p3;
        if ((ctx & 0x200) != 0) {
            tgt[0] = *(float*)(bone + 0x344) * scale;
            tgt[1] = *(float*)(bone + 0x348) * scale;
            tgt[2] = *(float*)(bone + 0x34c) * scale;
            float* r = QuatRotate(tmp, (float*)(bone + 0x118), tgt);
            pos0 = pos0 + r[0];
            pos1 = r[1] + pos1;
            pos2 = r[2] + pos2;
        }
        if ((ctx & 0x120) == 0x100) {
            char* par = **(char***)(p7 + 8);
            float q0 = *(float*)(par + 0x118);
            float q1 = *(float*)(par + 0x11c);
            float q2 = *(float*)(par + 0x120);
            float q3 = *(float*)(par + 0x124);
            float a0 = p10[0], a1 = p10[1], a2 = p10[2], a3 = p10[3];
            float rel[4];
            rel[0] = ((a0 * q3 - q0 * a3) + a2 * q1) - a1 * q2;
            rel[1] = ((a1 * q3 - a2 * q0) - q1 * a3) + q2 * a0;
            rel[2] = ((a1 * q0 + a2 * q3) - q1 * a0) - q2 * a3;
            rel[3] = ((q2 * a2 + a1 * q1) + q0 * a0) + a3 * q3;
            float d[3];
            d[0] = pos0 - *(float*)(par + 0x10c) * scale;
            d[1] = pos1 - *(float*)(par + 0x110) * scale;
            d[2] = pos2 - *(float*)(par + 0x114) * scale;
            float* r = QuatRotate(tmp, rel, d);
            pos0 = *p9 + r[0];
            pos1 = r[1] + p9[1];
            pos2 = r[2] + p9[2];
        }
    }

    // bone world-space orientation candidates
    char* par2 = **(char***)(p7 + 8);
    float b0 = *(float*)(bone + 0x118);
    float b1 = *(float*)(bone + 0x11c);
    float b2 = *(float*)(bone + 0x120);
    float b3 = *(float*)(bone + 0x124);
    float P0 = *(float*)(par2 + 0x118);
    float P1 = *(float*)(par2 + 0x11c);
    float P2 = *(float*)(par2 + 0x120);
    float P3 = *(float*)(par2 + 0x124);
    float a0 = p10[0], a1 = p10[1], a2 = p10[2], a3 = p10[3];
    float q10 = ((P3 * a0 - P0 * a3) + a2 * P1) - a1 * P2;
    float qc  = ((a1 * P3 - a2 * P0) - P1 * a3) + P2 * a0;
    float q8  = ((a1 * P0 + a2 * P3) - P1 * a0) - P2 * a3;
    float q4  = ((P2 * a2 + a1 * P1) + a3 * P3) + P0 * a0;

    float oq0 = b0, oq1 = b1, oq2 = b2, oq3 = b3;
    if (p5 != 0 && (((uint8_t)*p5) & 0x60) == 0x60) {
        oq0 = ((b3 * q10 + q4 * b0) - q8 * b1) + qc * b2;
        oq1 = ((qc * b3 + q4 * b1) + q8 * b0) - b2 * q10;
        float t = q8 * b2;
        float u = q8 * b3 - qc * b0;
        oq2 = (u + q4 * b2) + b1 * q10;
        oq3 = ((q4 * b3 - q10 * b0) - qc * b1) - t;
    }

    float cx = pos0, cy = pos1, cz = pos2;     // result position
    float oqa[4];                               // bone orientation (local_a8..)
    oqa[0] = oq0; oqa[1] = oq1; oqa[2] = oq2; oqa[3] = oq3;
    float bq[4];                                // result orientation (local_b8..)
    bq[0] = oq0; bq[1] = oq1; bq[2] = oq2; bq[3] = oq3;

    if (p4 != 0 && p3 != 0 && (*p3 & 0x10) != 0) {
        cx = p4[0];
        cy = p4[1];
        cz = p4[2];
        if ((*p1 & 1) == 0) {
            float k0 = pos0, k1 = pos1, k2 = pos2;
            uint32_t ctx = *p3;
            float io[3];
            io[0] = cx; io[1] = cy; io[2] = cz;
            SimpleTargetOffset(*p3, *p1, p7, p8, io);
            cx = io[0]; cy = io[1]; cz = io[2];
            if (p13 != 0)
                cx = -cx;
            if ((ctx & 0x120) == 0x20 || (ctx & 0x120) == 0x100) {
                cx = k0 + cx;
                cy = k1 + cy;
                if ((*p1 & 0x10) == 0)
                    cz = k2 + cz;
                else
                    cz = (1.0f - cz) * k2;
            }
        } else {
            float f24[3];
            BuildFrame(f24, p7, p1, p2);
            if (g_adjustFrameEnabled != 0) {
                float* r = AdjustFrame(tmp, p7, *(int*)(*p8 + 0x1f8), f24, 0);
                f24[0] = r[0]; f24[1] = r[1]; f24[2] = r[2];
            }
            float wpos[3];
            wpos[0] = pos0; wpos[1] = pos1; wpos[2] = pos2;
            if ((*p1 & 0x10) == 0) {
                float m54[9];
                float len5c;
                float c[3];
                c[0] = cx; c[1] = cy; c[2] = cz;
                V3 up; up.x = 0.0f; up.y = 0.0f; up.z = 1.0f;
                SolveTarget(m54, wpos, f24, &len5c, 0, 2, up);
                // m54 layout: [0]=xx [1]=? ...; columns are (54,4c,48/3c/34 ...) per the original locals
                float local_54 = m54[0], local_50 = m54[1], local_4c = m54[2];
                float local_48 = m54[3], local_44 = m54[4], local_40 = m54[5];
                float local_3c = m54[6], local_38 = m54[7], local_34 = m54[8];
                float axis[3];          // local_78.. : (local_54, local_3c, local_48 ...)
                float v6c[3];           // local_6c, 68, 64
                float v88[3];
                axis[0] = local_54; axis[1] = local_48; axis[2] = local_3c;
                // original stores: 74=48, 6c=4c, 68=40, 78=54, 70=3c, 64=34
                float v78[3];
                v78[0] = local_54; v78[1] = local_48; v78[2] = local_3c;
                v6c[0] = local_4c; v6c[1] = local_40; v6c[2] = local_34;
                float fx = local_50, fy = local_44, fz = local_38;
                if (p13 != 0) { fx = -local_50; fy = -local_44; fz = -local_38; }
                uint32_t fl = *p1;
                float fVar13 = local_3c;
                float fVar11 = local_54;
                float fVar12;
                if ((fl & 8) == 0) {
                    c[1] = c[1] * len5c;
                    c[2] = c[2] * len5c;
                    fVar12 = c[0] * len5c;
                    v88[0] = fx; v88[1] = fy; v88[2] = fz;
                } else {
                    v88[0] = fx; v88[1] = fy; v88[2] = fz;
                    float w = ChannelWeight(v78, *p3, fl, p7, p8);
                    fVar12 = w * c[0];
                    c[0] = fVar12;
                }
                uint32_t ctxf = *p3;
                float w1 = ChannelWeight(v88, ctxf, fl, p7, p8);
                c[1] = w1 * c[1];
                float w2 = ChannelWeight(v6c, ctxf, fl, p7, p8);
                float s = w2 * c[2];
                v88[0] = local_4c * s;
                v88[1] = local_40 * s;
                v88[2] = s * local_34;
                float fz2 = fz * c[1];
                cx = ((fVar11 * fVar12 + fx * c[1]) + v88[0]) + pos0;
                cy = ((local_48 * fVar12 + fy * c[1]) + v88[1]) + pos1;
                cz = ((fVar13 * fVar12 + fz2) + v88[2]) + pos2;
            } else {
                float fVar9 = f24[1] - pos1;
                float fVar10 = f24[0] - pos0;
                float fVar8 = f24[2] - pos2;
                float wt = 1.0f;
                float v6c[3];
                float len14;
                float local_5c = f24[2];
                v6c[0] = fVar10; v6c[1] = fVar9; v6c[2] = fVar8;
                if ((*p1 & 8) != 0) {
                    float* r = Normalize3(tmp, v6c, &len14);
                    fVar10 = r[0]; fVar9 = r[1]; fVar8 = r[2];
                    v6c[0] = fVar10; v6c[1] = fVar9; v6c[2] = fVar8;
                    wt = ChannelWeight(v6c, *p3, *p1, p7, p8);
                }
                float v78[3];
                v78[0] = fVar8 * 0.0f - fVar9 * -1.0f;
                v78[1] = fVar10 * -1.0f - fVar8 * 0.0f;
                v78[2] = fVar9 * 0.0f - fVar10 * 0.0f;
                float v88[3];
                Normalize3(v88, v78, 0);
                float w2 = ChannelWeight(v88, *p3, *p1, p7, p8);
                float e0 = v88[0], e1 = v88[1], e2 = v88[2];
                if (p13 != 0) { e0 = -v88[0]; e1 = -v88[1]; e2 = -v88[2]; }
                float fVar12 = p4[0] * wt;
                float fVar11 = p4[1] * w2;
                float fVar13 = fVar12;
                if ((*p1 & 8) != 0)
                    fVar13 = fVar12 / len14;
                fVar13 = ((local_5c - pos2) * fVar13 + pos2) * p4[2];
                float l70 = fVar13 * -1.0f;
                fVar13 = fVar13 * 0.0f;
                cx = ((v6c[0] * fVar12 + e0 * fVar11) + fVar13) + pos0;
                cy = ((v6c[1] * fVar12 + e1 * fVar11) + fVar13) + pos1;
                cz = ((v6c[2] * fVar12 + e2 * fVar11) + l70) + pos2;
            }
        }
    }

    // target orientation: the (optionally mirrored) target quaternion is copied into the result
    // orientation itself, so a combine mode other than 0x20/0x60 leaves the target as the result
    if (p6 != 0 && p5 != 0 && (*p5 & 0x10) != 0) {
        uint32_t f5 = *p5;
        float* res;
        if ((*p1 & 1) == 0) {
            bq[0] = p6[0]; bq[2] = p6[2]; bq[3] = p6[3]; bq[1] = p6[1];
            if (p13 != 0) { bq[1] = -bq[1]; bq[2] = -bq[2]; }
            if ((f5 & 0x60) != 0x20 && (f5 & 0x60) != 0x60) goto done;
            float out10[4];
            res = QuatMul(out10, bq, oqa);
        } else {
            uint32_t mode = *p1 & 6;
            if (mode == 0) {
                bq[0] = p6[0]; bq[2] = p6[2]; bq[3] = p6[3]; bq[1] = p6[1];
                if (p13 != 0) { bq[1] = -bq[1]; bq[2] = -bq[2]; }
                if ((f5 & 0x60) != 0x20 && (f5 & 0x60) != 0x60) goto done;
                float out98[4];
                res = QuatMul(out98, bq, oqa);
            } else if (mode == 2) {
                float f78[4];
                BuildFrame(f78, p7, p1, p2);
                float m54[9];
                m54[1] = 0.0f; m54[2] = 0.0f; m54[3] = 0.0f;
                m54[5] = 0.0f; m54[6] = 0.0f; m54[7] = 0.0f;
                m54[8] = 1.0f; m54[4] = 1.0f; m54[0] = 1.0f;
                float qq[4];
                qq[0] = q10; qq[1] = qc; qq[2] = q8; qq[3] = q4;
                float cpa[3];
                cpa[0] = cx; cpa[1] = cy; cpa[2] = cz;
                SolveFrame(p7, oqa, qq, f78, cpa, m54);
                cx = cpa[0]; cy = cpa[1]; cz = cpa[2];
                if ((((uint8_t)*p5) & 0x60) == 0x40) {
                    bq[0] = p6[0]; bq[2] = p6[2]; bq[3] = p6[3]; bq[1] = p6[1];
                    if (p13 != 0) { bq[1] = -bq[1]; bq[2] = -bq[2]; }
                    float t88[4];
                    float* m = MatToQuat(t88, m54);
                    float out24[4];
                    res = QuatMul(out24, m, bq);
                } else {
                    float t6c[4];
                    res = MatToQuat(t6c, m54);
                }
            } else {
                goto done;
            }
        }
        bq[0] = res[0]; bq[1] = res[1]; bq[2] = res[2]; bq[3] = res[3];
    }
done:
    if (p11 != 0) {
        if (p3 == 0 || (*p3 & 0x200) == 0) {
            p11[0] = cx;
            p11[1] = cy;
        } else {
            float* r = QuatRotate(tmp, bq, tgt);
            float r1 = r[1];
            cz = cz - r[2];
            p11[0] = cx - r[0];
            p11[1] = cy - r1;
        }
        p11[2] = cz;
    }
    if (p12 != 0) {
        p12[0] = bq[0];
        p12[1] = bq[1];
        p12[2] = bq[2];
        p12[3] = bq[3];
    }
}
