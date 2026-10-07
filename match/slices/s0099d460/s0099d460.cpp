// Slice s0099d460 -- nSPCreatureAnim::EvaluateAnimationBodyState (3238 bytes, __cdecl, 4 args).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-  (no cookie despite the local arrays)
//
// Blends every active animation's bone channels into the per-body accumulators of a creature:
//  - walks the 16-byte bone-binding entries of the animation state (skipping flagged ones and
//    ones not in the current 64-bit layer mask), finds each animation's first position channel
//    (type 1) and first rotation channel (type 2), evaluates the bone transform
//    (EvaluateBoneTransform, relative to the parent bone's blended position), and adds the
//    weighted position / rotation to the body accumulators (two sets, chosen by channel flags),
//    also accumulating the root/mirror bones into a local 255-entry blend table that is
//    normalized lazily (FUN_0099ce40) when a child needs its parent;
//  - feeds the remaining type-3 channels (scalar / phase channels) into the body's channel
//    accumulator at +0xa0 (sin/cos split for phase channels);
//  - finally lets every flagged animation trigger HitBody on the target creature.
// Retail layouts differ from the 2008 PDB (body state stride 0x2bc, animation stride 0x1f0), so
// the structs below are local stubs with offsets read from the disassembly.
#include "types.h"

extern "C" void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
#pragma intrinsic(sin, cos)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    void Set(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }
    void Set(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
};

struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
    Quaternion& operator=(const Quaternion& o);     // @ 0x00572600
    void Set(const Quaternion& o) { x = o.x; y = o.y; z = o.z; w = o.w; }
};

// One entry of the local blend table (9 floats).
struct BlendAccum {
    Vector3 pos;            // +0x00
    float posWeight;        // +0x0c
    Quaternion rot;         // +0x10
    float rotWeight;        // +0x20
    BlendAccum() : pos(0.0f, 0.0f, 0.0f), posWeight(0.0f), rot(0.0f, 0.0f, 0.0f, 0.0f), rotWeight(0.0f) {}
    void Unitize();         // @ 0x0099ce40 (divide by the weights, normalize rot)
};

// Body-state channel accumulator at body state +0xa0 (slice s0099bf80).
struct ChannelAccum {
    bool Add(uint32_t key, uint32_t val, float f0, float f1);              // @ 0x0099c4a0
    bool Add(uint32_t key, uint32_t val, float f0, float f1, float f2);    // @ 0x0099c540
};

struct BoneStatic {                 // skeleton bone data
    char pad0[0x10c];
    Vector3 restPos;                // +0x10c
    Quaternion restRot;             // +0x118
};

struct BodyStaticExtra {
    char pad0[0x150];
    uint32_t mFlags;                // +0x150
};

struct BodyStatic {
    char pad0[0x10c];
    Vector3 restPos;                // +0x10c
    char pad118[0x154 - 0x118];
    uint8_t mFlags;                 // +0x154
    char pad155[0x214 - 0x155];
    BodyStaticExtra* mpExtra;       // +0x214
};

struct BodyState {                  // 0x2bc bytes
    BodyStatic* mpStatic;           // +0x00
    char pad04[0x3c - 0x04];
    Vector3 mPosition;              // +0x3c
    float mTotalWeight;             // +0x48
    char pad4c[0x54 - 0x4c];
    uint8_t mFlags54;               // +0x54
    uint8_t mFlags55;               // +0x55
    char pad56[2];
    Vector3 mPosAccum;              // +0x58
    float mPosWeight;               // +0x64
    Quaternion mRotAccum;           // +0x68
    float mRotWeight;               // +0x78
    Vector3 mPosAccum2;             // +0x7c
    float mPosWeight2;              // +0x88
    Quaternion mRotAccum2;          // +0x8c
    float mRotWeight2;              // +0x9c
    ChannelAccum mChannels;         // +0xa0
    char pada1[0x2bc - 0xa1];
};

struct AnimChannel {                // 0x20 bytes
    uint32_t mFlags;                // +0x00 (bits 0-3 type, 0x40 phase, 0x80 ..)
    uint32_t mKey;                  // +0x04
    uint32_t pad08[2];
    uint32_t mIndex;                // +0x10
    uint32_t pad14[3];
};

struct AnimHeader {                 // at animation data +0x88
    uint32_t mFlags;                // +0x00 (+0x88)
    uint32_t pad04[4];
    uint32_t mFlags2;               // +0x14 (+0x9c)
};

struct AnimData {
    char pad0[0x88];
    AnimHeader mHeader;             // +0x88
    char padA0[0xac - 0xa0];
    uint8_t mFlagsAC;               // +0xac
    char padAD[0xdc - 0xad];
    uint32_t mChannelCount;         // +0xdc
    AnimChannel* mpChannels;        // +0xe0

    __forceinline AnimChannel* FindChannel(uint32_t type) {
        for (uint32_t i = 0; i < mChannelCount; i++) {
            if ((mpChannels[i].mFlags & 0xf) == type && mpChannels[i].mKey != 0)
                return &mpChannels[i];
        }
        return 0;
    }
};

struct AnimAux {                    // 40 bytes, indexed by channel mIndex - 3
    float mPhase;                   // +0x00
    float mWeight;                  // +0x04
    uint32_t pad[8];
};

struct AnimInstance {               // 0x1f0 bytes
    AnimData* mpData;               // +0x00
    uint32_t pad04[3];
    uint8_t mFlags;                 // +0x10
    char pad11[7];
    float mArg18[3];                // +0x18 (position-channel state)
    float mPosWeight;               // +0x24
    char pad28[0x68 - 0x28];
    float mArg68[4];                // +0x68 (rotation-channel state)
    float mRotWeight;               // +0x78
    char pad7c[0xcc - 0x7c];
    AnimAux mAux[6];                // +0xcc
    uint8_t mFlags1BC;              // +0x1bc
    char pad1bd[0x1f0 - 0x1bd];
};

struct BoneBinding {                // 16 bytes
    unsigned __int64 mLayerMask;    // +0x00
    uint32_t mChannelMask;          // +0x08 (low 24 bits)
    uint8_t mBone;                  // +0x0c
    uint8_t mAnim;                  // +0x0d
    uint8_t mParent;                // +0x0e (0xff = none)
    uint8_t mFlags;                 // +0x0f
};

struct AnimState {
    uint32_t pad0[2];
    unsigned __int64 mAnimMask;     // +0x08
    uint32_t mFlags;                // +0x10
    uint32_t pad14[2];
    BoneBinding* mpBindBegin;       // +0x1c
    BoneBinding* mpBindEnd;         // +0x20
};

struct AnimSetData {
    char pad0[0x144];
    uint32_t mAnimCount;            // +0x144
};

struct AnimSet {
    AnimSetData* mpData;            // +0x00
    uint32_t pad04;
    AnimState* mpState;             // +0x08
    uint32_t mLayer;                // +0x0c
    uint32_t pad10;
    AnimInstance* mpAnims;          // +0x14
};

struct CreatureStatic;
struct HitRecord;
struct CreatureInstance;

struct CreatureTarget {             // creature_instance_data
    CreatureStatic* mpStatic;       // +0x00
    void HitBody(int body, Vector3* impulse, int a, int b, float scale);   // @ 0x009bb680
};

struct CreatureInstance {
    uint32_t pad0[2];
    BoneStatic** mpSkeleton;        // +0x08
    char pad0c[0x18 - 0x0c];
    Vector3 mPosition;              // +0x18
    char pad24[0x3c - 0x24];
    Quaternion mOrientation;        // +0x3c
    char pad4c[0x70 - 0x4c];
    float mScale;                   // +0x70
    char pad74[0x1b8 - 0x74];
    uint8_t mBodyBits[0x260 - 0x1b8];   // +0x1b8
    bool mb260;                     // +0x260
    bool mb261;                     // +0x261
    uint8_t mRootBone;              // +0x262
    char pad263[0x274 - 0x263];
    int mMode;                      // +0x274
    char pad278[0x294 - 0x278];
    CreatureTarget* mpTarget;       // +0x294
    char mHitRecord[0x2e4 - 0x298]; // +0x298
    BodyState* mpBodies;            // +0x2e4
};

void __cdecl EvaluateBoneTransform(AnimHeader* header, Vector3* parentPos, AnimChannel* posChannel,
                                   float* arg18, AnimChannel* rotChannel, float* arg68,
                                   CreatureInstance* creature, BodyState* body, Vector3* rootPos,
                                   Quaternion* rootRot, Vector3* outPos, Quaternion* outRot,
                                   int flags);                                  // @ 0x009b0e90
Quaternion __cdecl QuatAccumulate(const Quaternion* a, const Quaternion* b);   // @ 0x0099cba0
Vector3 __cdecl AdjustFrame(CreatureInstance* creature, uint32_t bone, Vector3* pos, int zero);   // @ 0x009b77a0
Vector3 __cdecl QuatRotate(const Quaternion* q, const Vector3* v);             // @ 0x0099c1a0
void __cdecl SetRootPosition(CreatureInstance* creature, Vector3* pos);        // @ 0x009cd930
int __cdecl FindHitBody(int* out, int mask, CreatureStatic* data, void* rec, int a, int b);   // @ 0x009b2340

extern int g_adjustFrames;          // 0x01550a74
extern float g_hitBodyScale;        // 0x01550ac4
extern const float kTwoPi;          // 0x01446dec (6.2831855f)

// @ 0x0099d460
void __cdecl EvaluateAnimationBodyState(float weight, CreatureInstance* creature, AnimSet* set,
                                        float scaledFactor)
{
    if (weight <= 0.0f)
        return;
    {
        BlendAccum blend[255];
        bool unitized[255] = { false };

        AnimState* state = set->mpState;
        bool mirror;
        if ((state->mFlags & 1) == 0 || (state->mFlags & 2) != 0)
            mirror = false;
        else
            mirror = true;

        float scale = creature->mScale;
        BoneStatic* root = *creature->mpSkeleton;
        Vector3 rootPos(root->restPos.x * scale, root->restPos.y * scale, root->restPos.z * scale);
        Quaternion rootRot;
        rootRot.Set((*creature->mpSkeleton)->restRot);
        unsigned __int64 layerMask = (unsigned __int64)1 << set->mLayer;

        uint32_t bindCount = (uint32_t)(state->mpBindEnd - state->mpBindBegin);
        for (uint32_t b = 0; b < bindCount; b++) {
            BoneBinding* bind = &set->mpState->mpBindBegin[b];
            if ((bind->mFlags & 9) != 0)
                continue;
            if ((bind->mLayerMask & layerMask) == 0)
                continue;

            uint32_t bone = bind->mBone;
            if (!unitized[0] && bone > 0) {
                blend[0].Unitize();
                rootPos.Set(blend[0].pos);
                rootRot.Set(blend[0].rot);
                unitized[0] = true;
            }

            AnimInstance* anim = &set->mpAnims[bind->mAnim];
            AnimHeader* header = &anim->mpData->mHeader;
            BodyState* body = &creature->mpBodies[bone];
            int bindFlags = bind->mFlags & 2;
            int parent;
            if (bind->mParent == 0xff)
                parent = -1;
            else
                parent = bind->mParent;
            uint32_t bitByte = (bone * 2) >> 3;
            uint8_t bit = (uint8_t)(1 << ((bone * 2) & 7));
            uint8_t bit2 = bit + bit;

            float w = weight;
            if ((body->mpStatic->mFlags & 0x14) != 0) {
                body->mFlags55 |= 1;
                if ((anim->mFlags & 2) != 0)
                    body->mFlags54 |= 1;
                else
                    w = weight * scaledFactor;
            }
            if (bone == 0 && (anim->mFlags & 2) != 0)
                creature->mRootBone = (uint8_t)bone;

            AnimData* data = anim->mpData;
            uint32_t channelMask = bind->mChannelMask & 0xffffff;
            AnimChannel* posChannel = data->FindChannel(1);
            uint32_t posMask = posChannel ? 1u << (posChannel - data->mpChannels) : 0;
            AnimChannel* rotChannel = data->FindChannel(2);
            uint32_t rotMask = rotChannel ? 1u << (rotChannel - data->mpChannels) : 0;

            if ((channelMask & (rotMask | posMask)) != 0 && w > 0.0f) {
                Vector3 pos(0.0f, 0.0f, 0.0f);
                Quaternion rot(0.0f, 0.0f, 0.0f, 1.0f);
                bool applied = false;
                Vector3 parentPos(0.0f, 0.0f, 0.0f);
                if (parent != -1) {
                    if ((header->mFlags & 0x20) != 0) {
                        BodyStatic* ps = creature->mpBodies[parent].mpStatic;
                        float s = creature->mScale;
                        parentPos.Set(s * ps->restPos.x, ps->restPos.y * s, ps->restPos.z * s);
                    } else {
                        Vector3* src;
                        if ((set->mpState->mFlags & 2) != 0) {
                            src = &creature->mpBodies[parent].mPosition;
                        } else {
                            if (!unitized[parent]) {
                                blend[parent].Unitize();
                                unitized[parent] = true;
                            }
                            src = &blend[parent].pos;
                        }
                        parentPos.Set(*src);
                    }
                }

                EvaluateBoneTransform(header, &parentPos, posChannel, anim->mArg18, rotChannel, anim->mArg68,
                                      creature, body, &rootPos, &rootRot, &pos, &rot, bindFlags);

                bool alt;
                BodyStaticExtra* extra = body->mpStatic->mpExtra;
                if (extra == 0 || (extra->mFlags & 2) == 0 || (extra->mFlags & 8) != 0)
                    alt = false;
                else
                    alt = true;

                if ((channelMask & posMask) != 0) {
                    if (bone == 0 || mirror) {
                        float pw = anim->mPosWeight;
                        BlendAccum& e = blend[bone];
                        e.pos.y = pw * pos.y + e.pos.y;
                        e.pos.z = e.pos.z + pw * pos.z;
                        e.pos.x = e.pos.x + pw * pos.x;
                        e.posWeight = anim->mPosWeight + e.posWeight;
                    }
                    float pw = anim->mPosWeight * w;
                    if (pw > 0.0f) {
                        if (g_adjustFrames != 0)
                            pos = AdjustFrame(creature, bone, &pos, 0);
                        if ((posChannel->mFlags & 0x400) != 0 || (alt && (posChannel->mFlags & 0x800) == 0)) {
                            body->mPosAccum2.x = body->mPosAccum2.x + pos.x * pw;
                            body->mPosAccum2.y = body->mPosAccum2.y + pos.y * pw;
                            body->mPosAccum2.z = pos.z * pw + body->mPosAccum2.z;
                            body->mPosWeight2 = body->mPosWeight2 + pw;
                            creature->mBodyBits[bitByte] |= bit2;
                        } else {
                            body->mPosAccum.x = pos.x * pw + body->mPosAccum.x;
                            body->mPosAccum.y = pos.y * pw + body->mPosAccum.y;
                            body->mPosAccum.z = body->mPosAccum.z + pos.z * pw;
                            body->mPosWeight = body->mPosWeight + pw;
                            creature->mBodyBits[bitByte] |= bit;
                        }
                        if ((anim->mFlags & 1) != 0 && (header->mFlags & 1) != 0 &&
                            (header->mFlags2 & 0x100003) == 2) {
                            Vector3 r = QuatRotate(&creature->mOrientation, &pos);
                            Vector3 p(r.x + creature->mPosition.x, creature->mPosition.y + r.y,
                                      creature->mPosition.z + r.z);
                            SetRootPosition(creature, &p);
                        }
                    }
                    applied = true;
                }

                if ((channelMask & rotMask) != 0) {
                    if (bone == 0 || mirror) {
                        float rw = anim->mRotWeight;
                        Quaternion q(rw * rot.x, rw * rot.y, rw * rot.z, rw * rot.w);
                        Quaternion* dst = &blend[bone].rot;
                        *dst = QuatAccumulate(dst, &q);
                        blend[bone].rotWeight = blend[bone].rotWeight + anim->mRotWeight;
                    }
                    float rw = anim->mRotWeight * w;
                    if (rw > 0.0f) {
                        if ((int8_t)rotChannel->mFlags < 0 || (alt && (rotChannel->mFlags & 0x100) == 0)) {
                            Quaternion q(rot.x * rw, rot.y * rw, rot.z * rw, rot.w * rw);
                            body->mRotAccum2 = QuatAccumulate(&body->mRotAccum2, &q);
                            body->mRotWeight2 = rw + body->mRotWeight2;
                            creature->mBodyBits[bitByte] |= bit2;
                        } else {
                            Quaternion q(rot.x * rw, rot.y * rw, rot.z * rw, rot.w * rw);
                            body->mRotAccum = QuatAccumulate(&body->mRotAccum, &q);
                            body->mRotWeight = body->mRotWeight + rw;
                            creature->mBodyBits[bitByte] |= bit;
                        }
                    }
                    applied = true;
                }

                if (applied) {
                    if (!creature->mb261 || !creature->mb260 || bone != 0)
                        body->mTotalWeight = body->mTotalWeight + w;
                }
            }

            channelMask &= ~rotMask & ~posMask;
            uint32_t count = anim->mpData->mChannelCount;
            if (channelMask != 0) {
                for (uint32_t i = 0; i < count; i++) {
                    if ((channelMask & (1 << i)) == 0)
                        continue;
                    AnimChannel* ch = &anim->mpData->mpChannels[i];
                    uint32_t f = ch->mFlags;
                    if ((f & 0xf) != 3)
                        continue;
                    AnimAux& aux = anim->mAux[ch->mIndex - 3];
                    float cw = aux.mWeight * weight;
                    if ((f & 0x40) != 0) {
                        double a = (double)aux.mPhase * kTwoPi;
                        body->mChannels.Add(ch->mKey, ((f & 0x80) | 0x100) >> 7, (float)(cos(a) * cw),
                                            (float)(sin(a) * cw), cw);
                    } else {
                        body->mChannels.Add(ch->mKey, (f >> 7) & 1, aux.mPhase * cw, cw);
                    }
                }
            }
        }

        uint32_t animCount = set->mpData->mAnimCount;
        for (uint32_t i = 0; i < animCount; i++) {
            AnimInstance* anim = &set->mpAnims[i];
            if ((anim->mpData->mFlagsAC & 1) == 0)
                continue;
            if ((((unsigned __int64)1 << i) & set->mpState->mAnimMask) == 0)
                continue;
            if ((anim->mFlags1BC & 1) == 0 || (anim->mFlags & 1) != 0)
                continue;
            if (creature->mMode != 2)
                continue;
            CreatureTarget* target = creature->mpTarget;
            if (target == 0)
                continue;
            int hitBody;
            if (FindHitBody(&hitBody, 1, target->mpStatic, creature->mHitRecord, 0, 0)) {
                Vector3 impulse(0.0f, 0.0f, 0.0f);
                target->HitBody(hitBody, &impulse, 0, 0, g_hitBodyScale);
            }
        }
    }
}
