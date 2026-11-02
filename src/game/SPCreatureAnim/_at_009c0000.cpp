// src/game/SPCreatureAnim/_at_009c0000.cpp -- migrated from slice(s) s009ccfe0 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/_at_009c0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cIParser.h"

// unnamed retail callees and globals (address in the comment)
extern float DAT_01485720;   // 1.0f
#include <math.h>

// ---- items of slice s009ccfe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_0099c1a0(float* out, const float* q, const float* v);          // 0x0099c1a0 QuaternionVectorTransform
void* __cdecl FUN_0099c0b0(float* out, const float* a, const float* b);          // 0x0099c0b0
void* __cdecl FUN_0099c310(float* out, const float* q, const float* v);          // 0x0099c310
int   __cdecl nSPCreatureAnim_EvaluateContextTargetQuery(void* creature, int one, int key,
                                                         void* q, int z0, int z1);  // 0x009b2340
void* __cdecl EA_RectT_assign(void* dst, const void* src);                       // 0x00572600 EA::RectT<float>::operator=
extern float DAT_01485720;   // 1.0f
// ---- items of slice s009ccfe0 end

// @ 0x009cd580
void __cdecl FUN_009cd580(char* self, float* out_pos, void* out_rect, int use_rot)
{
    float local_50;
    float local_4c;
    float local_48;
    float local_44[3];
    float local_38[3];
    float local_2c[3];
    float local_20[4];
    float local_10[4];
    int mode = *(int*)(self + 0x274);

    if (mode == 0) {
        if (out_pos != 0) {
            float* p = (float*)FUN_0099c1a0(local_2c, (float*)(self + 0x3c),
                                            (float*)(self + 0x278));
            out_pos[2] = *(float*)(self + 0x20) + p[2];
            out_pos[1] = *(float*)(self + 0x1c) + p[1];
            out_pos[0] = *(float*)(self + 0x18) + p[0];
        }
        if (out_rect != 0) {
            float q0 = *(float*)(self + 0x3c);
            float q120 = *(float*)(self + 0x290);
            float q1 = *(float*)(self + 0x284);
            float f40 = *(float*)(self + 0x40);
            float q2 = *(float*)(self + 0x28c);
            float f44a = *(float*)(self + 0x44);
            float q3 = *(float*)(self + 0x288);
            float f48a = *(float*)(self + 0x48);
            float f44b = *(float*)(self + 0x44);
            float q1b = *(float*)(self + 0x284);
            float q3b = *(float*)(self + 0x288);
            float f48b = *(float*)(self + 0x48);
            float f48c = *(float*)(self + 0x48);
            float q1c = *(float*)(self + 0x284);
            float q3c = *(float*)(self + 0x288);
            float f44c = *(float*)(self + 0x44);
            ((float*)out_rect)[0] = ((q0 * q120 + q1 * f48a) - f44a * q3) + f40 * q2;
            ((float*)out_rect)[1] = ((f40 * q120 + f44b * q1b) + q3b * f48b) - q2 * q0;
            ((float*)out_rect)[2] = ((f44c * q120 - f40 * q1c) + q3c * q0) + q2 * f48c;
            ((float*)out_rect)[3] = ((q120 * f48c - q0 * q1c) - f40 * q3c) - q2 * f44c;
        }
        return;
    }
    if (mode == 1) {
        if (out_pos != 0) {
            out_pos[0] = *(float*)(self + 0x278);
            out_pos[1] = *(float*)(self + 0x27c);
            out_pos[2] = *(float*)(self + 0x280);
        }
        if (out_rect != 0) {
            ((float*)out_rect)[0] = *(float*)(self + 0x284);
            ((float*)out_rect)[1] = *(float*)(self + 0x288);
            ((float*)out_rect)[2] = *(float*)(self + 0x28c);
            ((float*)out_rect)[3] = *(float*)(self + 0x290);
        }
        return;
    }
    if (mode != 2 || *(int*)(self + 0x294) == 0 || **(int**)(self + 0x294) == 0
        || nSPCreatureAnim_EvaluateContextTargetQuery(&self, 1, **(int**)(self + 0x294),
                                                      self + 0x298, 0, 0) == 0) {
        if (out_pos != 0) {
            out_pos[0] = 0.0f; out_pos[1] = 0.0f; out_pos[2] = 0.0f;
        }
        if (out_rect != 0) {
            ((float*)out_rect)[0] = 0.0f;
            ((float*)out_rect)[1] = 0.0f;
            ((float*)out_rect)[2] = 0.0f;
            ((float*)out_rect)[3] = 1.0f;
        }
        return;
    }
    {
        int* tgt = *(int**)(self + 0x294);
        float* body = (float*)((char*)tgt + *(int*)(self + 0x60) * 0x2bc + 0x2e4);
        if (out_pos != 0) {
            if (use_rot == 0) {
                float* p = (float*)FUN_0099c1a0(local_38, (float*)(tgt + 0xf),
                                                body + 4);
                out_pos[0] = p[0] + (float)tgt[6];
                out_pos[1] = (float)tgt[7] + p[1];
                out_pos[2] = (float)tgt[8] + p[2];
            }
            else {
                float* q = *(float**)(body);
                local_48 = (float)tgt[0x1c];
                local_50 = q[0x10c] * local_48;
                local_4c = q[0x110] * local_48;
                local_48 = q[0x114] * local_48;
                float* p = (float*)FUN_0099c1a0(local_44, (float*)(tgt + 0xf), &local_50);
                out_pos[0] = p[0] + (float)tgt[6];
                out_pos[1] = p[1] + (float)tgt[7];
                out_pos[2] = p[2] + (float)tgt[8];
            }
        }
        if (out_rect != 0) {
            float* src;
            float* dst;
            if (use_rot == 0) { src = body + 0x40 / 4; dst = local_10; }
            else { src = (float*)(*(int*)body + 0x118); dst = local_20; }
            void* r = FUN_0099c0b0(dst, (float*)(tgt + 0xf), src);
            EA_RectT_assign(out_rect, r);
        }
    }
}

// @ 0x009cd930
void __cdecl FUN_009cd930(char* self, float* pos)
{
    float local_18;
    float local_14;
    float local_10;
    float local_c[3];

    if (*(int*)(self + 0x274) != 2)
        return;
    int* tgt = *(int**)(self + 0x294);
    if (tgt == 0 || *tgt == 0)
        return;
    if (nSPCreatureAnim_EvaluateContextTargetQuery(&self, 1, *tgt, self + 0x298, 0, 0) == 0)
        return;
    local_18 = pos[0] - (float)tgt[6];
    int* body = (int*)(self + *(int*)(self + 0x60) * 0x2bc + 0x2e4);
    local_14 = pos[1] - (float)tgt[7];
    local_10 = pos[2] - (float)tgt[8];
    float* p = (float*)FUN_0099c310(local_c, (float*)(tgt + 0xf), &local_18);
    *(float*)((char*)body + 0x58) = *(float*)((char*)body + 0x58) + p[0];
    *(float*)((char*)body + 0x5c) = p[1] + *(float*)((char*)body + 0x5c);
    *(float*)((char*)body + 0x60) = p[2] + *(float*)((char*)body + 0x60);
    *(float*)((char*)body + 0x64) = *(float*)((char*)body + 0x64) + DAT_01485720;
    int* inst = *(int**)(body);
    int* src = (int*)((char*)inst + 0x118);
    ((float*)((char*)body + 0x68))[0] = ((float*)src)[0];
    ((float*)((char*)body + 0x6c))[0] = ((float*)src)[1];
    ((float*)((char*)body + 0x70))[0] = ((float*)src)[2];
    ((float*)((char*)body + 0x74))[0] = ((float*)src)[3];
    *(float*)((char*)body + 0x78) = DAT_01485720;
    int idx = *(int*)((char*)inst + 0x1f8);
    int eax = idx * 2;
    unsigned char* pb = (unsigned char*)(*(int*)((char*)body + 4) + (eax >> 3) + 0x1b8);
    unsigned char bit = (unsigned char)(1 << (eax & 7));
    *pb |= bit;
}
