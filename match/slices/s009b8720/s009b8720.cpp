// @ 0x009b8720 .. slice s009b8720  (batch gold7)
// Target module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// Context: nSPCreatureAnim::creature_instance_data walking / root-motion update helpers.
#include "types.h"
#include <math.h>

// --- externals (names irrelevant to byte comparison: call rel32 is masked) ----------
extern "C" int DAT_014470a0;      // 0x014470a0  (double 1e-08)
extern "C" int DAT_01470f1c;      // 0x01470f1c  (float 0.5f)
extern "C" int DAT_01485720;      // 0x01485720  (_HK_REAL_ONE = 1.0f)
extern "C" int DAT_013eb8b0;      // 0x013eb8b0  (16-byte sign mask)
extern "C" int DAT_01485378;      // 0x01485378  (_HK_REAL_ZERO = 0.0f)
extern "C" int DAT_014853e0;      // 0x014853e0  (float 2.0f)
extern "C" int DAT_015509f8;      // 0x015509f8  (float)
extern "C" int DAT_01550b18;      // 0x01550b18  (float eps)
extern "C" int DAT_01550d64;      // 0x01550d64  (float)
extern "C" int DAT_01448874;      // 0x01448874  (float 1e-06f)
extern "C" int DAT_013eb960;      // 0x013eb960  (float 0.01f)
extern "C" int DAT_01485544;      // 0x01485544  (0.75f)
extern "C" int DAT_014471fc;      // 0x014471fc  (0.0f)
extern "C" int DAT_01550d6c;      // 0x01550d6c  (float)
extern "C" int DAT_01550d68;      // 0x01550d68  (float)
extern "C" int DAT_01550d70;      // 0x01550d70  (float)
extern "C" int DAT_01550d74;      // 0x01550d74  (float)
extern "C" int DAT_01550d78;      // 0x01550d78  (float)
extern "C" int DAT_01550d08;      // 0x01550d08  (float)
extern "C" int DAT_01550d0c;      // 0x01550d0c  (float)
extern "C" int DAT_01550d10;      // 0x01550d10  (float)
extern "C" int DAT_01550d14;      // 0x01550d14  (float)
extern "C" int DAT_01550d18;      // 0x01550d18  (float)
extern "C" int DAT_01550d1c;      // 0x01550d1c  (float)
extern "C" int DAT_01550d20;      // 0x01550d20  (float)
extern "C" int DAT_01550d24;      // 0x01550d24  (float)
extern "C" int DAT_01550d28;      // 0x01550d28  (float)
extern "C" int DAT_015509e0;      // 0x015509e0
extern "C" int DAT_015509ec;      // 0x015509ec

// --- callees --------------------------------------------------------------------
extern "C" void  FUN_009b4ba0(void* out, void* q, void* v); // 0x009b4ba0
void  __fastcall FUN_0099c4a0(int this_, int dummy, int a, int b, float c, float d); // 0x0099c4a0
void  __fastcall FUN_0099c310(void* out, int dummy, void* a, void* b); // 0x0099c310
void  __fastcall Bone_IntegrateVelocity(int this_, int dummy, float f, float* a, float* b); // 0x009b5ab0
int   __fastcall FUN_00c37030(int this_);                          // 0x00c37030  (GetFootprintRadius)
int   __fastcall FUN_009d3530(int this_);                          // 0x009d3530
float __fastcall FUN_009ce700(float x);                            // 0x009ce700
void  __fastcall FUN_009d00a0(int this_, int dummy, void* out, void* param); // 0x009d00a0
void  __fastcall FUN_009b3970(void* p);                            // 0x009b3970

namespace nSPCreatureAnim {

// Sub-objects the walking helpers receive in ecx. Layouts mirror slice s009d3950
// (the slice that owns the 0x009d3xxx/0x009d6xxx definitions).
struct vector_3 { float x, y, z; };

// Spatial-object base as seen by CalcRootGoalPosDelta (0x009b9340): orientation quaternion and
// the axis-aligned local extents. Offsets are taken from the retail disassembly of this slice.
struct SpatialObject {
    uint32_t _00[0x1c/4];                               // 0x000
    float    orient_w;                                  // 0x01c orientation.w
    float    extent_lower_z;                            // 0x020 original-local lower.z
    uint32_t _24;                                       // 0x024
    float    extent_lower_x;                            // 0x028 original-local lower.x
    float    extent_upper_x;                            // 0x02c original-local upper.x
};

struct Obj2;                                            // the creature instance (this slice)

struct AniDyn;                                          // 0x15b8

// std::vector-shaped container (begin/end pointers) as returned by the accessors below.
struct GaitGroup;
struct BoneGoal;
struct Vector30 { void* begin; void* end; };            // elements are 0x30 bytes
struct Vector104 { void* begin; void* end; };           // elements are 0x104 bytes
struct Vector108 { void* begin; void* end; };           // elements are 0x108 bytes

// One 0x108-byte gait-group record (the vector owned by AniDyn via FUN_00a09f50).
struct GaitGroup {                                      // stride 0x108
    float    vx, vy, vz;                                // 0x000 desired velocity
    uint32_t _0c[6];                                    // 0x00c
    uint32_t f24_0[9];                                  // 0x024 integration scratch (float[9])
    uint32_t i44;                                       // 0x044
    uint32_t i48;                                       // 0x048
    float    f4c;                                       // 0x04c
    float    f50;                                       // 0x050
    float    f54;                                       // 0x054
    int      i58;                                       // 0x058 bone index
    uint32_t pad_05c[0x108/4 - 0x5c/4];                 // 0x05c..0x108
};

// The 0x104-byte record of the vector owned by AniDyn via GetPoliticalID.
struct BoneGoal {                                       // stride 0x104
    uint32_t f00_0[0x100/4];                            // 0x000
    float    f100;                                      // 0x100
    void     FUN_009d63e0(float t);                     // 0x009d63e0
};

// One 0x2bc-byte bone as used by FUN_009b9090's goal clamp: current pose vs. goal pose.
struct GoalBone {                                       // stride 0x2bc
    uint32_t _00[0x38/4];                               // 0x000
    bool     flag_38;                                   // 0x038
    uint8_t  pad_039[0x0f];                             // 0x039..0x048
    float    f48;                                       // 0x048
    uint32_t _4c[0x30/4];                               // 0x04c..0x07c
    float    cur_x;                                     // 0x07c current pose
    float    cur_y;                                     // 0x080
    float    cur_z;                                     // 0x084
    uint32_t pad_088[0x108/4];                          // 0x088..0x190
    float    goal_x;                                    // 0x190 goal pose
    float    goal_y;                                    // 0x194
    float    goal_z;                                    // 0x198
    uint32_t tail[0x124/4];                             // 0x19c..0x2bc
};

// One 0x22c-byte "motion phase" record read by FUN_009b9340: two 3-float vectors at
// +0x10c and +0x70. Offsets match the retail disassembly.
struct MotionPhase {                                    // stride 0x1a8 (unused here)
    uint32_t _00[0x70/4];                               // 0x000
    float    scale_70;                                  // 0x070
    uint32_t _74[0x98/4];                               // 0x074..0x10c
    float    f10c;                                      // 0x10c
    float    f110;                                      // 0x110
    float    f114;                                      // 0x114
};

// One 0x22c-byte root-goal record read by FUN_009b9340 (a is *param_2's element).
struct RootGoal {                                       // stride 0x124 (unused here)
    float    x, y, z;                                   // 0x000
    uint32_t _0c[0x10/4];                               // 0x00c
    float    f1c;                                       // 0x01c
    float    f20;                                       // 0x020
    float    f24;                                       // 0x024
    float    f28;                                       // 0x028
    float    f2c;                                       // 0x02c
};

// The sub-object at bone + 0xa0 (receiver of 0x0099c4a0).
struct BoneHandle {
    uint32_t _00[0x1c/4];                               // 0x000
    void     FUN_0099c4a0(int a, int b, float c, float d); // 0x0099c4a0
};

// A single bone instance (indexed by GaitGroup::i58, stride 0x2bc, based at mpBone_2e4).
struct BoneInst {                                       // stride 0x2bc
    uint32_t   _00[0x4c/4];                             // 0x000
    float      f4c;                                     // 0x04c
    uint32_t   _50[0x50/4];                             // 0x050
    BoneHandle hA0;                                     // 0x0a0
    uint32_t   tail[0x200/4];                           // 0x0bc..0x2bc
    void       Bone_IntegrateVelocity(float f, float* a, float* b); // 0x009b5ab0
};

struct GaitState {                                      // 0x2f8
    int    state;                                       // 0x000
    int    prev;                                        // 0x004
    float  f08;                                         // 0x008
    float  f0c;                                         // 0x00c
    uint32_t _10[10];                                   // 0x010
    void*  p38;                                         // 0x038
    void*  p3c;                                         // 0x03c
    float  FUN_009dbd50();                              // 0x009dbd50
};

struct AniDyn {                                         // receiver of the 0x9d3xxx helpers
    uint32_t _00[0xa8/4];                               // 0x000..0x0a8

    int*   FUN_009d3200(void* p, float f);              // 0x009d3200
    void   FUN_009d32d0();                              // 0x009d32d0
    void   FUN_009d3f70(Obj2* p);                       // 0x009d3f70
    float  FUN_009d3a20(Obj2* p, float a, int x, float b); // 0x009d3a20
    void   FUN_009d3b50(float t);                       // 0x009d3b50
    void   FUN_009d6700(float t);                       // 0x009d6700
    Vector108* FUN_00a09f50();                          // 0x00a09f50 gait-group vector
    Vector30*  FUN_00ad2800();                          // 0x00ad2800
    Vector104* GetPoliticalID();                        // 0x0097e850
    float  FUN_009d3530();                              // 0x009d3530
    float  FUN_009ce700(float x);                       // 0x009ce700
    void   FUN_009d00a0(float* out, void* phase);       // 0x009d00a0
    float* FUN_009b9340(float* out, int** a, SpatialObject* s, float dt); // 0x009b9340
};

// The walking/root-motion region of creature_instance_data at its retail offsets. The dev-PDB
// header is shifted relative to retail, so members are named by role and offset.
struct creature_instance_data {
    // 0x000..0x058 : requested rot + scale + actual rot block
    uint32_t pad_000[6];                         // 0x000
    float    f_18;                               // 0x018
    float    f_1c;                               // 0x01c
    float    f_20;                               // 0x020
    uint32_t pad_024[6];                         // 0x024
    float    f_3c;                               // 0x03c
    float    f_40;                               // 0x040
    float    f_44;                               // 0x044
    float    f_48;                               // 0x048
    float    f_4c;                               // 0x04c
    float    f_50;                               // 0x050
    float    f_54;                               // 0x054
    float    f_58;                               // 0x058
    uint32_t pad_05c[5];                         // 0x05c
    float    requested_scale;                    // 0x070
    uint32_t pad_074[6];                         // 0x074
    float    f_8c;                              // 0x08c
    float    f_90;                              // 0x090
    float    f_94;                              // 0x094
    uint32_t pad_098[26];                        // 0x098
    float    f_100;                              // 0x100
    float    f_104;                              // 0x104
    float    f_108;                              // 0x108
    float    f_10c;                              // 0x10c
    uint32_t pad_110[11];                        // 0x110
    float    f_13c;                              // 0x13c
    float    f_140;                              // 0x140
    float    f_144;                              // 0x144
    uint32_t pad_148;                            // 0x148
    float    f_14c;                              // 0x14c
    float    f_150;                              // 0x150
    float    f_154;                              // 0x154
    float    f_158;                              // 0x158
    uint32_t pad_15c;
    float    f_160;                              // 0x160
    uint32_t pad_164[7];
    float    f_180;                              // 0x180
    float    f_184;                              // 0x184
    float    f_188;                              // 0x188
    float    f_18c;                              // 0x18c
    float    f_190;                              // 0x190
    float    f_194;                              // 0x194
    float    f_198;                              // 0x198
    float    f_19c;                              // 0x19c
    float    f_1a0;                              // 0x1a0
    uint32_t pad_1a4[47];                        // 0x1a4
    bool     flag_260;                           // 0x260
    bool     flag_261;                           // 0x261
    uint16_t pad_262;                            // 0x262
    float    walk_linear_x;                      // 0x264
    float    walk_linear_y;                      // 0x268
    float    walk_angular;                       // 0x26c
    uint32_t pad_270[0x74/4];                    // 0x270..0x2e4
    int*     mpBone_2e4;                         // 0x2e4
    uint32_t pad_2e8[0x10/4];                    // 0x2e8..0x2f8
    GaitState gait_2f8;                          // 0x2f8
    uint32_t pad_338[0x1280/4];                  // 0x338..0x15b8
    AniDyn   anim_15b8;                          // 0x15b8
    uint32_t pad_1600[0x60/4];                   // 0x1600..0x1660
    float    accum_1660;                         // 0x1660 root motion delta
    float    accum_1664;
    float    accum_1668;
    float    accum_166c;
    vector_3 root_1670;                          // 0x1670
    float    root_167c;
    bool     flag_1680;                          // 0x1680

    void FUN_009b8250(float param_2);            // 0x009b8250
    void FUN_009b83b0(float param_2);            // 0x009b83b0
    void FUN_009b8650(float param_2);            // 0x009b8650
    void FUN_009b7da0(float param_2);            // 0x009b7da0
    void FUN_009b7c00(float param_2, float* param_3, float param_4); // 0x009b7c00

    // this slice
    void FUN_009b8720(float param_2);            // 0x009b8720
    void FUN_009b8760(float param_2);            // 0x009b8760
    void FUN_009b8d50(float param_2);            // 0x009b8d50
    void FUN_009b8e40(float param_2);            // 0x009b8e40
    void FUN_009b8f40(float param_2);            // 0x009b8f40
    void FUN_009b8fd0(float* out_a, float* out_b); // 0x009b8fd0
    void FUN_009b9090();                         // 0x009b9090
    float* FUN_009b9250(float* out, float* p);   // 0x009b9250
};

}  // namespace nSPCreatureAnim

using nSPCreatureAnim::creature_instance_data;
using nSPCreatureAnim::AniDyn;
using nSPCreatureAnim::SpatialObject;

// ===========================================================================
// 0x009b8720  apply a new style weight: shrink first, then blend the limit
// ===========================================================================
// @ 0x009b8720
void creature_instance_data::FUN_009b8720(float param_2)
{
    FUN_009b8250(param_2);
    if (*(char*)(*(int*)this + 0x3f4) != 0) {
        FUN_009b83b0(param_2);
    } else {
        FUN_009b8650(param_2);
    }
}

// ===========================================================================
// 0x009b8760  rebuild the walk goal (position + heading) for the current frame
// ===========================================================================
// @ 0x009b8760
void creature_instance_data::FUN_009b8760(float param_2)
{
    float local_3c;
    float local_38 = f_188 + f_140;
    float fVar1 = f_194;
    float fVar9 = (float)(1.0 / ((double)param_2 + *(double*)&DAT_014470a0));
    float fVar2 = f_154;
    float fVar3 = f_198;
    float local_34 = f_18c + f_144;
    float fVar4 = f_158;
    float local_20 = ((fVar1 * fVar4 + f_14c * f_1a0) - f_150 * f_19c) + fVar2 * fVar3;
    float local_1c = ((fVar3 * fVar4 + f_19c * f_14c) + f_150 * f_1a0) - fVar2 * fVar1;
    float local_14 = ((fVar4 * f_1a0 - fVar1 * f_14c) - fVar3 * f_150) - fVar2 * f_19c;
    float local_18 = ((f_19c * fVar4 - fVar3 * f_14c) + f_150 * fVar1) + fVar2 * f_1a0;
    float local_2c = (f_184 + f_13c) * fVar9;
    float local_28 = local_38 * fVar9;
    float local_24 = local_34 * fVar9;
    FUN_009b4ba0(&local_3c, &local_20, 0);
    float fA = f_40;
    float fB = f_3c;
    float fC = f_48;
    float fD = f_44;
    float fVar10 = f_58;
    float fVar13 = local_34 * (1.0f - (fB * fB + fA * fA) * 2.0f);
    float fVar11 = local_38 * ((fD * fA - fB * fC) * 2.0f);
    float fVar5 = f_54;
    float fVar6 = f_50;
    float fVar7 = f_90;
    float fVar12 = f_4c * fVar6;
    float fVar8 = f_4c;
    walk_linear_x =
        (((-(fVar6 * fVar10) + f_4c * fVar5) * f_94 +
          (-(fVar6 * fVar6) + -(fVar5 * fVar5)) * f_8c) +
         (fVar12 - -(fVar5 * fVar10)) * fVar7) * 2.0f + f_8c;
    walk_linear_y =
        (((fVar6 * fVar5 - -(fVar8 * fVar10)) * f_94 +
          (-(fVar8 * fVar8) + -(fVar5 * fVar5)) * fVar7) +
         (fVar12 + -(fVar5 * fVar10)) * f_8c) * 2.0f + fVar7;
    float fVar10b = f_4c;
    float fVar5b = f_58;
    float fVar6b = f_48;
    float fVar7b = f_54;
    float fVar8b = f_40;
    local_20 = ((f_3c * fVar5b - fVar10b * fVar6b) + f_50 * f_44) - fVar7b * fVar8b;
    float fVar12b = f_3c;
    local_1c = ((fVar8b * fVar5b - f_44 * fVar10b) - f_50 * fVar6b) + fVar7b * fVar12b;
    local_18 = ((fVar8b * fVar10b + f_44 * fVar5b) - f_50 * fVar12b) - fVar7b * fVar6b;
    local_14 = ((fVar8b * f_50 + fVar7b * f_44) + fVar10b * fVar12b) + fVar6b * fVar5b;
    float local_10;
    float local_c;
    float local_8;
    float local_4;
    FUN_009b4ba0(&local_10, &local_20, 0);
    float fVar10c = f_40;
    float fVar5c = f_3c;
    walk_angular =
        (local_4 * fVar9) *
        (local_c * ((f_44 * fVar10c - fVar5c * f_48) * 2.0f) +
         (local_8 * (1.0f - (fVar5c * fVar5c + fVar10c * fVar10c) * 2.0f) +
          ((fVar5c * f_44 + fVar10c * f_48) * 2.0f) * local_10));
    float fVar10d = (f_108 * local_24 + f_104 * local_28) + f_100 * local_2c;
    local_24 = local_24 - f_108 * fVar10d;
    local_2c = local_2c - f_100 * fVar10d;
    local_28 = local_28 - f_104 * fVar10d;
    if (((local_2c * local_2c + local_28 * local_28) + local_24 * local_24 <= *(float*)&DAT_01550b18) &&
        ((float)fabs(((((fB * fD + fA * fC) * 2.0f) * local_3c + fVar13) + fVar11) *
               (local_34 * fVar9)) <= *(float*)&DAT_01550b18)) {
        flag_261 = false;
        return;
    }
    flag_261 = true;
}

// ===========================================================================
// 0x009b8fd0  root height bias: pick min(offset, limit) and a blended weight
// ===========================================================================
// @ 0x009b8fd0
void creature_instance_data::FUN_009b8fd0(float* param_2, float* param_3)
{
    float fVar2 = ((f_20 * f_108 + f_1c * f_104) + f_18 * f_100);    if (fVar2 <= f_10c) {
        *param_2 = fVar2;
        *param_3 = *(float*)&DAT_01485720;
        return;
    }
    *param_2 = f_10c;
    float t = 1.0f - ((fVar2 - f_10c) /
                      (*(float*)(*(int*)this + 0x36c) * requested_scale)) *
                         *(float*)&DAT_01550d64;
    float lo = 0.0f;
    float* p = (t > lo) ? &t : &lo;
    *param_3 = *p;
}

// ===========================================================================
// 0x009b8d50  integrate the root motion and update the root track
// ===========================================================================
// @ 0x009b8d50
void creature_instance_data::FUN_009b8d50(float param_2)
{
    if (1e-06f < param_2) {
        float local_c = accum_1660;
        float uVar1 = accum_166c;
        float local_8 = accum_1664;
        float local_4 = accum_1668;
        FUN_009b7da0(param_2);
        anim_15b8.FUN_009d3200(&accum_1660, accum_166c);
        FUN_009b7c00(param_2, &local_c, uVar1);
    }
    anim_15b8.FUN_009d3f70((Obj2*)this);
    anim_15b8.FUN_009d32d0();
    float f = gait_2f8.FUN_009dbd50();
    f = anim_15b8.FUN_009d3a20((Obj2*)this, f, (int)&root_1670, root_167c);
    anim_15b8.FUN_009d3b50(f);
    anim_15b8.FUN_009d6700(param_2);
}

// ===========================================================================
// 0x009b8e40  integrate every gait group's velocity into the bone chain
// ===========================================================================
// @ 0x009b8e40
void creature_instance_data::FUN_009b8e40(float param_2)
{
    (void)param_2;
    Vector108* v = anim_15b8.FUN_00a09f50();
    unsigned n = (unsigned)(((char*)v->end - (char*)v->begin) / 0x108);
    if (n == 0) return;
    char* base = (char*)v->begin;
    for (unsigned i = 0; i != n; ++i) {
        GaitGroup* p = (GaitGroup*)(base + i * 0x108);
        BoneInst* bone = &((BoneInst*)mpBone_2e4)[p->i58];
        float fVar1 = bone->f4c;
        if (fVar1 > 0.0f) {
            float local_c = p->vx * requested_scale;
            float local_8 = p->vy * requested_scale;
            float local_4 = p->vz * requested_scale;
            bone->Bone_IntegrateVelocity(fVar1, &local_c, (float*)p->f24_0);
            if (DAT_015509e0 != 0) {
                bone->hA0.FUN_0099c4a0(
                    (int)p->i44, (int)p->i48, p->f4c, p->f54);
            }
        }
    }
}

// ===========================================================================
// 0x009b8f40  feed the current walk goal to all foot groups
// ===========================================================================
// @ 0x009b8f40
void creature_instance_data::FUN_009b8f40(float param_2)
{
    if (DAT_015509ec != 0 && *(char*)(*(int*)this + 0x3f5) == 0) {
        Vector30* v = anim_15b8.FUN_00ad2800();
        if (v != 0 && 3u <= (unsigned)(((char*)v->end - (char*)v->begin) / 0x30)) {
            Vector104* g = anim_15b8.GetPoliticalID();
            int ebx = (int)(((char*)g->end - (char*)g->begin) / 0x104);
            if (ebx != 0) {
                int esi = 0;
                do {
                    BoneGoal* p = (BoneGoal*)((char*)g->begin + esi);
                    p->FUN_009d63e0(param_2);
                    esi += 0x104;
                } while (--ebx != 0);
            }
        }
    }
}

// ===========================================================================
// 0x009b9090  clamp each gait group's bone goal toward the current pose
// ===========================================================================
// @ 0x009b9090
void creature_instance_data::FUN_009b9090()
{
    Vector108* v = anim_15b8.FUN_00a09f50();
    if (v == 0) return;
    int n = (int)(((char*)v->end - (char*)v->begin) / 0x108);
    if (n <= 0) return;
    int off = 0;
    int cnt = n;
    do {
        char* b = (char*)v->begin;
        int bi = *(int*)(off + b + 0x58);
        if (bi != -1) {
            GoalBone* bone = (GoalBone*)((char*)mpBone_2e4 + bi * 0x2bc);
            if (bone->f48 <= 0.0f) {
                float ddz = bone->goal_z - bone->cur_z;
                float ddx = bone->goal_x - bone->cur_x;
                float ddy = bone->goal_y - bone->cur_y;
                float d2 = ddy * ddy + ddz * ddz + ddx * ddx;
                float l2 = *(float*)&DAT_015509f8 * *(float*)&DAT_015509f8;
                if (d2 <= l2 * *(float*)&DAT_014853e0) {
                    if (l2 >= d2) {
                        bone->goal_x = bone->cur_x;
                        bone->goal_y = bone->cur_y;
                        bone->goal_z = bone->cur_z;
                    } else {
                        float t = (float)sqrt(d2) - *(float*)&DAT_015509f8;
                        t = t / *(float*)&DAT_015509f8;
                        float u = *(float*)&DAT_01485720 - t;
                        bone->goal_x = bone->cur_x * u + bone->goal_x * t;
                        bone->goal_y = bone->cur_y * u + bone->goal_y * t;
                        bone->goal_z = bone->cur_z * u + bone->goal_z * t;
                    }
                    bone->flag_38 = true;
                }
            }
        }
        off += 0x108;
    } while (--cnt != 0);
}

// ===========================================================================
// 0x009b9250  build a turn-rate vector from a planar velocity (register ABI)
// ===========================================================================
// @ 0x009b9250
float* creature_instance_data::FUN_009b9250(float* param_2, float* param_3)
{
    float py = param_3[1];
    float px = param_3[0];
    param_2[2] = 0.0f;
    param_2[1] = 0.0f;
    param_2[0] = 0.0f;
    float len = (float)sqrt(px * px + py * py);
    if (len <= *(float*)&DAT_014471fc) {
        param_2[0] = 0.0f;
        param_2[1] = 0.0f;
        param_2[2] = 0.0f;
        return param_2;
    }
    FUN_009b3970(&len);
    float s = (float)sin(len);
    float c = (float)cos(len);
    float k = *(float*)&DAT_01550d68;
    if (param_3[1] < 0.0f)
        k = *(float*)&DAT_01485720;
    float f1 = *(float*)&DAT_01485720;
    float inv = f1 / len;
    param_2[0] = (inv * param_3[0]) * *(float*)&DAT_01550d68 * s;
    param_2[1] = (inv * param_3[1] * k) * s;
    param_2[2] = (c - f1) * inv;
    return param_2;
}

// ===========================================================================
// 0x009b9340  root goal position delta (AniDyn member; 4 stack args, ret 0x10)
// ===========================================================================
// @ 0x009b9340
float* AniDyn::FUN_009b9340(float* param_1, int** param_2, SpatialObject* param_3, float param_4)
{
    param_1[2] = 0.0f;
    param_1[1] = 0.0f;
    param_1[0] = 0.0f;
    float minimum = *(float*)&DAT_01448874;
    float orient_w = param_3->orient_w;
    float ext_lz = param_3->extent_lower_z;
    int* v = *param_2;
    int* core = (int*)v[0];
    float ext_lx = param_3->extent_lower_x;
    float ext_ux = param_3->extent_upper_x;
    float scale = *(float*)(v[1] + 0x70);
    float lc = *(float*)(core + 0x10c) * scale;
    float l8 = *(float*)(core + 0x110) * scale;
    float l4 = *(float*)(core + 0x114) * scale;

    float lo = minimum;
    float* p = (l4 > minimum) ? &l4 : &lo;
    float sel = *p;
    float sel2 = sel * *(float*)&DAT_01485544;
    float hi = *(float*)&DAT_013eb960;
    float* p2 = (sel2 > hi) ? &sel2 : &hi;
    float chosen = *p2;
    float fpr = FUN_00c37030((int)param_3) * scale;
    float* p3 = (fpr <= chosen) ? &chosen : &fpr;
    float ratio = *p3 / chosen;
    float one = *(float*)&DAT_01485720;
    float* p4 = (one > ratio) ? &ratio : &one;
    float factor = FUN_009d3530();
    factor = FUN_009ce700(factor) * *p4;

    FUN_009d00a0(&lc, param_3);
    float dt = factor * param_4;

    float a = ((lc * *(float*)&DAT_01550d74) * l4) * ext_lx;
    float b = ((l8 * *(float*)&DAT_01550d70) * sel) * ext_ux;
    float c = ((ext_lz * *(float*)&DAT_01550d78 + l4 * orient_w) * *(float*)&DAT_01550d6c) * sel;

    param_1[0] = ((*(float*)&DAT_01550d08 * c + *(float*)&DAT_01550d14 * l8 * ext_lx) +
                  *(float*)&DAT_01550d20 * a) * dt;
    param_1[1] = ((*(float*)&DAT_01550d0c * c + *(float*)&DAT_01550d18 * b +
                   *(float*)&DAT_01550d24 * a)) * dt;
    param_1[2] = ((*(float*)&DAT_01550d10 * c + *(float*)&DAT_01550d1c * b +
                   *(float*)&DAT_01550d28 * a)) * dt;
    return param_1;
}


