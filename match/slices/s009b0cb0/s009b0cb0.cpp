// Slice s009b0cb0 -- nSPCreatureAnim channel-weight / simple-target-offset helpers
// (ChannelWeight 0x009b0cb0, SimpleTargetOffset 0x009b0d80).
//
// Object file <SporeApp>/CreatureAnim.obj (same module as s009b4e00 / s009b0e90).  Context flag bits
// 6-7 select the weight mode: 0x40 = the per-axis channel weights of the animation state's data
// block (+0x364) times the state scale (+0x70), 0x80 = one scalar weight from the bone (+0x434, or
// the data block's +0x374 when the bone's +0x154 flags have bit 3) times that scale.
// ChannelWeight reduces the mode weight against a vector (plus 1e-8f), SimpleTargetOffset scales a
// target offset in place, skipping z when the animation flags have bit 4 (0x10).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct AnimChannels {              // *(void**)inst: per-axis channel weights
    unsigned char pad0[0x364];
    float mWeights[3];             // +0x364 per-axis channel weights
    unsigned char pad370[0x374 - 0x370];
    float mAltWeight;              // +0x374 (used when the bone asks for it)
};

struct BoneRec {                   // *skel: the bone record
    unsigned char pad0[0x154];
    unsigned char mFlags;          // +0x154 (bit 3 = take the state's own weight)
    unsigned char pad1[0x434 - 0x155];
    float mWeight;                 // +0x434
};

struct AnimState {                 // inst
    AnimChannels* mpChannels;      // +0x000
    unsigned char pad4[0x70 - 0x4];
    float mScale;                  // +0x70
};

// @ 0x009b0cb0
float __cdecl ChannelWeight(float* v, uint32_t ctxFlags, uint32_t animFlags, AnimState* inst, BoneRec** skel)
{
    switch (ctxFlags & 0xc0) {
    case 0x40: {
        float scale = inst->mScale;
        const float* w = inst->mpChannels->mWeights;
        float f[3];
        for (int i = 0; i < 3; i++)
            f[i] = w[i] * scale;
        return v[2] * f[2] + v[1] * f[1] + v[0] * f[0] + 1e-8f;
    }
    case 0x80: {
        BoneRec* bone = *skel;
        float scale = inst->mScale;
        float w = bone->mWeight * scale;
        if ((bone->mFlags & 8) != 0)
            w = inst->mpChannels->mAltWeight * scale;
        if (w > 1e-6f)
            return w;
        break;
    }
    }
    return 1.0f;
}

// @ 0x009b0d80
void __cdecl SimpleTargetOffset(uint32_t ctxFlags, uint32_t animFlags, AnimState* inst, BoneRec** skel, float* io)
{
    switch (ctxFlags & 0xc0) {
    case 0x40: {
        float scale = inst->mScale;
        const float* w = inst->mpChannels->mWeights;
        float f[3];
        f[0] = w[0] * scale;
        f[1] = w[1] * scale;
        f[2] = w[2] * scale;
        io[0] = io[0] * f[0];
        io[1] = io[1] * f[1];
        if ((animFlags & 0x10) == 0)
            io[2] = io[2] * f[2];
        break;
    }
    case 0x80: {
        BoneRec* bone = *skel;
        float scale = inst->mScale;
        float w = bone->mWeight * scale;
        if ((bone->mFlags & 8) != 0)
            w = inst->mpChannels->mAltWeight * scale;
        if (w > 1e-6) {
            io[0] *= w;
            io[1] *= w;
            if ((animFlags & 0x10) == 0)
                io[2] *= w;
        }
        break;
    }
    }
}
