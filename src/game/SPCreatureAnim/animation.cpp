// src/game/SPCreatureAnim/animation.cpp -- migrated from slice(s) s0099f970, s0099f0b0, s0099e110, s0099d460 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/animation.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPCreatureAnim/creature_instance_data.h"
#include "nSPCreatureAnim/latest_version/animation_static_data.h"
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl memset(void*, int, unsigned int);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern int g_adjustFrames;          // 0x01550a74
extern float g_hitBodyScale;        // 0x01550ac4
extern const float kTwoPi;          // 0x01446dec (6.2831855f)
#pragma intrinsic(memset)
#pragma intrinsic(sin, cos)

// ---- items of slice s0099d460 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
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
struct BlendAccum {
    Vector3 pos;            // +0x00
    float posWeight;        // +0x0c
    Quaternion rot;         // +0x10
    float rotWeight;        // +0x20
    BlendAccum() : pos(0.0f, 0.0f, 0.0f), posWeight(0.0f), rot(0.0f, 0.0f, 0.0f, 0.0f), rotWeight(0.0f) {}
    void Unitize();         // @ 0x0099ce40 (divide by the weights, normalize rot)
};
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
// ---- items of slice s0099d460 end

// ---- items of slice s0099e110 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace nSPCreatureAnim {
 class stream_wrapper; 
}
extern void FUN_f47380(void*);                 // operator delete(void*) cdecl
extern int FUN_00a088e0(int);
extern void FUN_11e073e(void*, int, int);
extern void __stdcall FUN_401930(void*, int, int, void*);
extern void FUN_0099cf50();
extern int g_15504dc;
extern "C" __declspec(dllimport) void* __cdecl fopen(const char*, const char*);
extern "C" __declspec(dllimport) int   __cdecl fclose(void*);
struct S99d060 { void f(); };                 // release a reference (0x99d060)
struct S99ed90 { int f(void*, char*, int); }; // ReadAnimationStaticDataFromStreamWrapper (external)
struct S99ecb0 {
  S99ecb0* f(int p);
};
struct S99ece0 {
  S99ece0* f();
};
struct S99f050 { void f(); };
struct S99f090 { S99f090* f(); };
// ---- items of slice s0099e110 end

// ---- items of slice s0099f0b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint32_t kAnimElemSize[16];        // 0x015504cc : bytes per channel element, by type nibble
extern int g_animSerial;                        // 0x0166b260
extern const float g_one;                       // 0x01485720
extern const float kQuatEpsilon;                // 0x013f11c8 (1e-6)
typedef unsigned int uint;
static inline int Strlen(const char* s)
{
    const char* p = s;
    while (*p++) {}
    return (int)(p - s - 1);
}
void* __cdecl operator_new(uint size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
struct AnimEvent {                              // 0x60 bytes
    uint32_t flags;                             // +0x00 (bits 6..7: kind; 1 and 2 carry a string)
    char pad04[0x3c];
    const char* str;                            // +0x40
    uint32_t pad44;
    float weight;                               // +0x48
    char pad4c[0x14];
};
struct AnimChannel_s0099_f0b0 {                            // 0x20 bytes
    uint32_t flags;                             // +0x00 (low nibble: element type, 0x10: kept when filtering)
    uint32_t pad04;                             // +0x04 (non-zero marks an event channel)
    uint32_t offset;                            // +0x08 element offset inside a frame
    uint32_t stride;                            // +0x0c frame stride
    char pad10[0x10];
};
struct AnimGroup {                              // 0xe4 bytes
    uint32_t pad00;
    void* owner;                                // +0x04
    char name[0xa4];                            // +0x08
    uint16_t flags;                             // +0xac (bit0 usable, bit3 always kept)
    char padae[0x26];
    uint32_t frameCount;                        // +0xd4
    char* frameData;                            // +0xd8
    uint32_t channelCount;                      // +0xdc
    AnimChannel_s0099_f0b0* channels;                      // +0xe0
};
struct AnimEventRef {                           // 12 bytes inside an event channel's frame data
    uint32_t pad0;
    uint32_t pad4;
    uint16_t first;                             // +8 : first event record
    uint8_t count;                              // +10
};
struct AnimHeader_s0099_f0b0 {                             // 0x200 bytes
    uint32_t magic;                             // +0x000 'ANIM'
    uint32_t size;                              // +0x004
    uint32_t version;                           // +0x008 (0x19)
    char name[0x108];                           // +0x00c
    uint32_t pad114;                            // +0x114
    uint32_t flags;                             // +0x118 (bit0: has weighted events)
    char pad11c[0x10];
    uint32_t serial;                            // +0x12c
    char pad130[0xc];
    uint32_t eventCount;                        // +0x13c
    AnimEvent* events;                          // +0x140
    uint32_t groupCount;                        // +0x144
    AnimGroup** groups;                         // +0x148
    uint32_t fixupCount;                        // +0x14c
    uint32_t fixupOffset;                       // +0x150
    char pad154[0xac];
};
// ---- items of slice s0099f0b0 end

// ---- items of slice s0099f970 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_quatBlendFlag;              // 0x015504f8
typedef uint32_t u32;
typedef uint8_t u8;
struct TrackDesc {
    char pad0[0x118];
    u8 flags118;          // bit 3: looping
    char pad119[7];
    float wrapTime;       // +0x120
};
struct Channel {          // 0x20 bytes
    u32 flags;            // low 4 bits: type, 0x10: enabled, 0x20: no clamp
    u32 keyed;            // +4
    u32 offset;           // +8
    u32 stride;           // +0xc
    u32 slot;             // +0x10 index into g_channelSlotTable
    u32 pad[3];
};
struct Track {
    void* vtbl;
    TrackDesc* desc;                // +4
    char pad8[0xd4 - 8];
    int keyCount;                   // +0xd4
    char* data;                     // +0xd8
    u32 channelCount;               // +0xdc
    Channel* channels;              // +0xe0
};
struct SlotEntry { int offset; int pad[7]; };
extern SlotEntry g_channelSlotTable[];   // 0x01446cc0
void FindNeighbours(Track* t, int* upper, int* prev, int* lower, int* next);        // 0x99c9f0
float* QuatBlend(float* out, const float* a, const float* b, float t);               // 0x99cc70
float* QuatMul(float* out, const float* a, const float* b);                          // 0x99cba0
float* QuatNormalize(float* out, const float* in, float* lenOut);                    // 0x99cae0
void CopyFixedKey(int stride, char* data, Channel* chans, u32 count, u32* out);      // 0x99f900
static inline float Fwd(u32 a, u32 b, float W)
{
    if (a < b) {
        return W - (float)b;
    }
    return (float)(a - b);
}
static inline float Nxt(u32 a, u32 b)
{
    u32 u = b;
    if (a <= u) {
        u = u - a;
    }
    return (float)u;
}
static inline float TanOut(u32 mode, float v0, float v1, float v2, float tn, float d01, float d12)
{
    if (mode == 0) {
        return ((v2 - v0) / (d12 + d01)) * d12;
    }
    if (mode == 1) {
        return v2 - v1;
    }
    if (mode == 3) {
        return tn * d12;
    }
    return 0.0f;
}
static inline float TanIn(u32 mode, float v1, float v2, float v3, float tn, float d21, float d23)
{
    if (mode == 0) {
        return ((v3 - v1) / (d23 + d21)) * d21;
    }
    if (mode == 1) {
        return v2 - v1;
    }
    if (mode == 3) {
        return tn * d21;
    }
    return 0.0f;
}
static inline float Clamp01(float f)
{
    if (0.0f < f) {
        if (1.0f < f) {
            f = 1.0f;
        }
        return f;
    }
    return 0.0f;
}
#define F(p, off) (*(float*)((char*)(p) + (off)))
#define B(p, off) (*(u8*)((char*)(p) + (off)))
// ---- items of slice s0099f970 end

// @ 0x0099d460
void __cdecl EvaluateAnimationBodyState(float weight, CreatureInstance* creature, AnimSet* set, float scaledFactor)
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

// @ 0x0099ecb0
S99ecb0* S99ecb0::f(int p)
{
  int old = *(int*)this;
  if (p != old) {
    if (p) *(int*)(p + 0x114) += 1;
    *(int*)this = p;
    if (old) ((S99d060*)(size_t)old)->f();
  }
  return this;
}

// @ 0x0099ece0
S99ece0* S99ece0::f()
{
  char* self = (char*)this;
  char* p = self + 0x24;
  for (int i = 3; i >= 0; i--) {
    *(float*)(p) = 0.0f;
    *(float*)(p + 4) = 0.0f;
    *(unsigned char*)(p + 8) = 0;
    *(unsigned char*)(p + 9) = 0;
    *(unsigned short*)(p + 0xa) = 0;
    p += 0x10;
  }
  p = self + 0x78;
  for (int i = 4; i >= 0; i--) {
    *(float*)(p) = 0.0f;
    *(float*)(p + 4) = 0.0f;
    *(unsigned char*)(p + 8) = 0;
    *(unsigned char*)(p + 9) = 0;
    *(unsigned short*)(p + 0xa) = 0;
    p += 0x10;
  }
  p = self + 0xd0;
  for (int i = 5; i >= 0; i--) {
    FUN_401930(p, 0x10, 2, (void*)FUN_0099cf50);
    p += 0x28;
  }
  FUN_11e073e(self, 0, 0x1b8);
  *(int*)(self + 4) = g_15504dc;
  g_15504dc += 1;
  return this;
}

// @ 0x0099ed90
namespace nSPCreatureAnim {
latest_version::animation_static_data * ReadAnimationStaticDataFromStreamWrapper(stream_wrapper & a1, char const * a2, unsigned long a3)
{ return 0; }
}  // namespace nSPCreatureAnim

// @ 0x0099efa0
char* FUN_0099efa0(char* first, char* last, char* dst)
{
  if (first != last) {
    int off = (int)(first - dst);
    do {
      if (dst) {
        *(int*)dst = *(int*)(dst + off);
        *(int*)(dst + 4) = *(int*)(dst + off + 4);
      }
      dst += 8;
    } while (dst + off != last);
  }
  return dst;
}

// @ 0x0099efd0
int FUN_0099efd0(char* name, int arg)
{
  if (name == 0) {
    if (arg != 0) return FUN_00a088e0(arg);
    return 0;
  }
  void* file = fopen(name, "rb");
  if (file == 0) return 0;
  struct { void* vt; void* fp; } local;
  local.vt = (void*)0x1446dd8;
  local.fp = file;
  int r = ((S99ed90*)&local)->f(&local, name, arg);
  fclose(file);
  return r;
}

// @ 0x0099f050
void S99f050::f()
{
  int* p = (int*)((char*)this + 0xc2c);
  for (int edi = 0x3f; edi >= 0; edi--) {
    int v = p[-10];
    p = (int*)((char*)p - 0x28);
    if (v && *(int*)(v - 4) != 0) FUN_f47380((void*)v);
  }
}

// @ 0x0099f090
S99f090* S99f090::f()
{
  S99f090* self = this;
  int* p = (int*)this;
  p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 0; p[5] = 0;
  p[7] = 0; p[8] = 0; p[9] = 0; p[0xc] = 0;
  return self;
}

// @ 0x0099f110
AnimHeader_s0099_f0b0* CloneAnim(AnimHeader_s0099_f0b0* src, bool filterOn)
{
    int groupBytes = 0x200;                     // header + group pointer table, grows per kept group
    uint fixups = 2;
    uint groupCount = 0;
    int eventCount = 0;
    int stringBytes = 0;
    uint8_t hasWeight = 0;
    uint groupIdx[64];
    uint nGroups = src->groupCount;
    {
        AnimGroup** gp = src->groups;
        for (uint gi = 0; gi < nGroups; gi++, gp++) {
            AnimGroup* grp = *gp;
            bool keep = true;
            if (filterOn) {
                if (!(grp->flags & 1)) {
                    keep = false;
                } else if (!(grp->flags & 8)) {
                    keep = false;
                    for (uint c = 0; c < grp->channelCount; c++) {
                        if (grp->channels[c].flags & 0x10) {
                            keep = true;
                            break;
                        }
                    }
                }
            }
            if (keep) {
                uint nch = grp->channelCount;
                groupBytes += 0xe8;
                fixups += 4;
                groupIdx[groupCount++] = gi;
                AnimChannel_s0099_f0b0* ch = grp->channels;
                for (uint rem = nch; rem; rem--, ch++) {
                    uint f = ch->flags;
                    if ((f & 0x10) || !filterOn || !(f & 0xf))
                        groupBytes += 0x20 + kAnimElemSize[f & 0xf] * grp->frameCount;
                }
                if (grp->flags != 0) {
                    AnimChannel_s0099_f0b0* evch = 0;
                    AnimChannel_s0099_f0b0* p = grp->channels;
                    for (uint c = 0; c < nch; c++, p++) {
                        if (!(p->flags & 0xf) && p->pad04) {
                            evch = grp->channels + c;
                            break;
                        }
                    }
                    char* frame = grp->frameData + evch->offset;
                    uint frames = grp->frameCount;
                    {
                        for (; frames; frames--, frame += evch->stride) {
                            AnimEventRef* ref = (AnimEventRef*)frame;
                            if (ref->count) {
                                uint first = ref->first;
                                eventCount += ref->count;
                                uint last = first + ref->count;
                                if (first < last) {
                                    AnimEvent* ev = src->events + first;
                                    int n = last - first;
                                    do {
                                        if (ev->weight > 0.0f)
                                            hasWeight |= 1;
                                        switch (ev->flags & 0xc0) {
                                        case 0x40:
                                        case 0x80:
                                            if (ev->str) {
                                                stringBytes += Strlen(ev->str) + 1;
                                                fixups++;
                                            }
                                        }
                                        ev++;
                                        n--;
                                    } while (n);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int fixupAt = groupBytes + fixups * 4;      // offset of the event records
    uint total = fixupAt + eventCount * 0x60 + stringBytes;
    uint pad = ((total + 3) & ~3u) - total;
    total += pad;
    char* mem = (char*)operator_new(total, "Anim/Anim", 0, 0, 0, 0);
    memset(mem + total - pad, 0, pad);
    char* strCursor = mem + fixupAt + eventCount * 0x60;
    AnimHeader_s0099_f0b0* dst = (AnimHeader_s0099_f0b0*)mem;
    uint32_t keepField = dst->pad114;
    *dst = *src;
    dst->pad114 = keepField;
    uint32_t* fixCursor = (uint32_t*)(mem + groupBytes);
    dst->serial = g_animSerial++;
    dst->size = total;
    dst->magic = 0x4d494e41;
    dst->version = 0x19;
    uint recIdx = 0;
    {
        int len = Strlen(dst->name);
        memset(dst->name + len + 1, 0, 0x103 - len);
    }
    dst->eventCount = eventCount;
    dst->events = (AnimEvent*)(mem + fixupAt);
    dst->fixupCount = fixups;
    dst->groupCount = groupCount;
    dst->pad114 = 0;
    dst->fixupOffset = groupBytes;
    fixCursor[0] = 0x140;
    fixCursor[1] = 0x148;
    fixCursor += 2;
    AnimGroup** table = (AnimGroup**)(mem + 0x200);
    if (hasWeight != 0)
        dst->flags |= 1;
    else
        dst->flags &= ~1u;
    int off = (int)((char*)table - mem);
    dst->groups = table;
    for (uint k = groupCount; k; k--) {
        *fixCursor++ = off;
        off += 4;
    }
    char* cursor = (char*)(table + groupCount);
    for (uint j = 0; j < groupCount; j++) {
        AnimGroup* sg = src->groups[groupIdx[j]];
        dst->groups[j] = (AnimGroup*)cursor;
        AnimGroup* ng = (AnimGroup*)cursor;
        memcpy(ng, sg, 0xe4);
        {
            int len = Strlen(ng->name);
            memset(ng->name + len + 1, 0, 0x7f - len);
        }
        ng->owner = dst;
        *fixCursor++ = (cursor - mem) + 4;
        *fixCursor++ = (cursor - mem) + 0xd8;
        *fixCursor++ = (cursor - mem) + 0xe0;
        ng->channels = (AnimChannel_s0099_f0b0*)(cursor + 0xe4);
        uint nsc = sg->channelCount;
        uint kept = 0;
        uint stride = 0;
        uint chIdx[9];
        if (nsc) {
            int o = 0;
            uint c = 0;
            do {
                AnimChannel_s0099_f0b0* sc = (AnimChannel_s0099_f0b0*)((char*)sg->channels + o);
                if ((sc->flags & 0x10) || !filterOn || !(sc->flags & 0xf)) {
                    chIdx[kept] = c;
                    memcpy(ng->channels + kept, sc, 0x20);
                    kept++;
                    stride += kAnimElemSize[sc->flags & 0xf];
                }
                o += 0x20;
                c++;
            } while (c < nsc);
        }
        char* data = cursor + 0xe4 + kept * 0x20;
        ng->channelCount = kept;
        {
            uint acc = 0;
            for (uint c = 0; c < kept; c++) {
                AnimChannel_s0099_f0b0* nc = &ng->channels[c];
                nc->offset = acc;
                nc->stride = stride;
                acc += kAnimElemSize[nc->flags & 0xf];
            }
        }
        ng->frameData = data;
        for (uint f = 0; f < sg->frameCount; f++) {
            for (uint c = 0; c < kept; c++) {
                AnimChannel_s0099_f0b0* sc = &sg->channels[chIdx[c]];
                uint sz = kAnimElemSize[sc->flags & 0xf];
                memcpy(data, sg->frameData + sc->stride * f + sc->offset, sz);
                if ((sc->flags & 0xf) == 2) {
                    float* q = (float*)data;
                    if (q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3] < kQuatEpsilon) {
                        q[0] = 0.0f;
                        q[1] = 0.0f;
                        q[2] = 0.0f;
                        q[3] = g_one;
                    }
                }
                char* elem = data;
                data += sz;
                if (!(sc->flags & 0xf)) {
                    AnimEventRef* ref = (AnimEventRef*)elem;
                    uint cnt = ref->count;
                    if (cnt) {
                        AnimEvent* de = (AnimEvent*)(mem + fixupAt) + recIdx;
                        AnimEvent* se = src->events + ref->first;
                        memcpy(de, se, cnt * 0x60);
                        ref->first = (uint16_t)recIdx;
                        for (uint r = cnt; r; r--, de++) {
                            switch (de->flags & 0xc0) {
                            case 0x40:
                            case 0x80:
                                if (de->str) {
                                    const char* s = de->str;
                                    int len = Strlen(s) + 1;
                                    de->str = strCursor;
                                    *fixCursor++ = ((char*)de - mem) + 0x40;
                                    de->flags = (de->flags & 0xffffff7f) | 0x40;
                                    for (const char* p = s; p != s + len; p++)
                                        strCursor[p - s] = *p;
                                    strCursor += len;
                                }
                            }
                        }
                        recIdx += cnt;
                    }
                }
            }
        }
        cursor = data;
    }
    return dst;
}

// @ 0x0099f970
bool EvaluateTrack(float time, int upper, Track* trk, u32* out, int* outIndex)
{
    if (trk->keyCount == 0) {
        return false;
    }

    int prevIdx, lowerIdx, nextIdx;
    FindNeighbours(trk, &upper, &prevIdx, &lowerIdx, &nextIdx);

    u32 count = trk->channelCount;
    float W = trk->desc->wrapTime - 1.0f;

    // first enabled key channel
    Channel* kc = 0;
    {
        Channel* c = trk->channels;
        for (u32 i = 0; i < count; i++, c++) {
            if ((c->flags & 0xf) == 0 && c->keyed != 0) {
                kc = c;
                break;
            }
        }
    }

    char* data = trk->data;
    char* K1 = data + kc->stride * lowerIdx + kc->offset;   // lower key
    char* K2 = data + kc->stride * upper + kc->offset;      // upper key
    int lower = lowerIdx;

    if (lowerIdx == upper) {
        CopyFixedKey(lowerIdx, trk->data, trk->channels, count, out);
    } else {
        u32 t1 = *(u32*)K1;
        char* K0 = data + kc->stride * prevIdx + kc->offset;
        char* K3 = data + kc->stride * nextIdx + kc->offset;
        u32 t2 = *(u32*)K2;
        u32 t0 = *(u32*)K0;
        u32 t3 = *(u32*)K3;

        float s = (time - (float)t1) / (float)(t2 - t1);
        float s2 = s * s;
        float s3 = s2 * s;
        float h01 = s2 * 3.0f - s3 * 2.0f;
        float h00 = (1.0f - s2 * 3.0f) + s3 * 2.0f;
        float h10 = (s - s2 * 2.0f) + s3;
        float h11 = s3 - s2;

        float d01 = Fwd(t1, t0, W);
        float d12 = Nxt(t1, t2);
        float d21 = Fwd(t2, t1, W);
        float d23 = Nxt(t2, t3);

        for (u32 ci = 0; ci < count; ci++) {
            Channel* ch = &trk->channels[ci];
            if ((ch->flags & 0x10) == 0) {
                continue;
            }
            u32 type = ch->flags & 0xf;
            char* base = trk->data;
            u32 stride = ch->stride;
            u32 off = ch->offset;
            char* v1 = base + stride * lowerIdx + off;
            char* v2 = base + stride * upper + off;
            char* v0 = base + stride * prevIdx + off;
            char* v3 = base + stride * nextIdx + off;

            if (type == 1) {
                float* dst = (float*)(out + 5);
                for (int c = 0; c < 3; c++) {
                    int o = 0x10 * c;
                    float a = TanOut(B(v1, 0x19 + o) & 3, F(v0, 4 * c), F(v1, 4 * c), F(v2, 4 * c),
                                     F(v1, 0x14 + o), d01, d12);
                    float b = TanIn(B(v2, 0x18 + o) & 3, F(v1, 4 * c), F(v2, 4 * c), F(v3, 4 * c),
                                    F(v2, 0x10 + o), d21, d23);
                    dst[c] = ((F(v1, 4 * c) * h00 + F(v2, 4 * c) * h01) + b * h11) + a * h10;
                }
                {
                    float a = TanOut(B(v1, 0x49) & 3, F(v0, 0xc), F(v1, 0xc), F(v2, 0xc), F(v1, 0x44), d01, d12);
                    float b = TanIn(B(v2, 0x48) & 3, F(v1, 0xc), F(v2, 0xc), F(v3, 0xc), F(v2, 0x40), d21, d23);
                    float r = ((F(v2, 0xc) * h01 + F(v1, 0xc) * h00) + b * h11) + a * h10;
                    *(float*)&out[8] = Clamp01(r);
                }
            } else if (type == 2) {
                float q1[4], q2[4], q0[4], q3[4];
                for (int i = 0; i < 4; i++) {
                    q1[i] = F(v1, 4 * i);
                    q2[i] = F(v2, 4 * i);
                }
                u32 m1 = B(v1, 0x1d) & 3;
                if (m1 == 1) {
                    float tmp[4];
                    float* r = QuatBlend(tmp, q1, q2, -1.0f);
                    for (int i = 0; i < 4; i++) q0[i] = r[i];
                } else {
                    for (int i = 0; i < 4; i++) q0[i] = q2[i];
                    if (m1 != 2) {
                        for (int i = 0; i < 4; i++) q0[i] = F(v0, 4 * i);
                    }
                }
                u32 m2 = B(v2, 0x1c) & 3;
                if (m2 == 1) {
                    float tmp[4];
                    float* r = QuatBlend(tmp, q2, q1, -1.0f);
                    for (int i = 0; i < 4; i++) q3[i] = r[i];
                } else if (m2 == 2) {
                    for (int i = 0; i < 4; i++) q3[i] = q1[i];
                } else {
                    for (int i = 0; i < 4; i++) q3[i] = F(v3, 4 * i);
                }

                float* res;
                if (g_quatBlendFlag == 0) {
                    float a0[4], d0[4], c0[4], n90[4], nb0[4], r10[4];
                    float sp1 = s + 1.0f;
                    QuatBlend(a0, q0, q1, sp1);
                    QuatBlend(d0, q1, q2, s);
                    QuatBlend(c0, q2, q3, s - 1.0f);
                    QuatBlend(n90, a0, d0, sp1 * 0.5f);
                    QuatBlend(nb0, d0, c0, s * 0.5f);
                    res = QuatBlend(r10, n90, nb0, s);
                } else {
                    float sp1 = s + 1.0f;
                    float f0[4], n1[4], n2[4], n3[4], e30[4], e40[4], e70[4], e50[4], w[4], x[4], f130[4], res4[4];
                    QuatBlend(f0, q0, q1, sp1);
                    float oms = 1.0f - s;
                    for (int i = 0; i < 4; i++) {
                        w[i] = q2[i] * s;
                        x[i] = q1[i] * oms;
                    }
                    QuatNormalize(n1, QuatMul(e30, x, w), 0);
                    QuatBlend(f130, q2, q3, s - 1.0f);
                    float h = sp1 * 0.5f;
                    float omh = 1.0f - h;
                    float w2[4], x2[4];
                    for (int i = 0; i < 4; i++) {
                        w2[i] = n1[i] * h;
                        x2[i] = f0[i] * omh;
                    }
                    QuatNormalize(n2, QuatMul(e40, x2, w2), 0);
                    float hs = s * 0.5f;
                    float oms2 = 1.0f - hs;
                    float w3[4], x3[4];
                    for (int i = 0; i < 4; i++) {
                        w3[i] = f130[i] * hs;
                        x3[i] = n1[i] * oms2;
                    }
                    QuatNormalize(n3, QuatMul(e70, x3, w3), 0);
                    float w4[4], x4[4];
                    for (int i = 0; i < 4; i++) {
                        w4[i] = n3[i] * s;
                        x4[i] = n2[i] * oms;
                    }
                    res = QuatNormalize(res4, QuatMul(e50, x4, w4), 0);
                }
                out[0x19] = ((u32*)res)[0];
                out[0x1a] = ((u32*)res)[1];
                out[0x1b] = ((u32*)res)[2];
                out[0x1c] = ((u32*)res)[3];

                float a = TanOut(B(v1, 0x5d) & 3, F(v0, 0x10), F(v1, 0x10), F(v2, 0x10), F(v1, 0x58), d01, d12);
                float b = TanIn(B(v2, 0x5c) & 3, F(v1, 0x10), F(v2, 0x10), F(v3, 0x10), F(v2, 0x54), d21, d23);
                float r = ((F(v2, 0x10) * h01 + F(v1, 0x10) * h00) + b * h11) + a * h10;
                *(float*)&out[0x1d] = Clamp01(r);
            } else if (type == 3) {
                float* dst = (float*)((char*)out + g_channelSlotTable[ch->slot].offset);
                for (int c = 0; c < 2; c++) {
                    int o = 0x10 * c;
                    float a = TanOut(B(v1, 0x11 + o) & 3, F(v0, 4 * c), F(v1, 4 * c), F(v2, 4 * c),
                                     F(v1, 0xc + o), d01, d12);
                    float b = TanIn(B(v2, 0x10 + o) & 3, F(v1, 4 * c), F(v2, 4 * c), F(v3, 4 * c),
                                    F(v2, 0x8 + o), d21, d23);
                    float r = ((F(v1, 4 * c) * h00 + F(v2, 4 * c) * h01) + b * h11) + a * h10;
                    float f = r;
                    if ((ch->flags & 0x20) == 0) {
                        f = Clamp01(r);
                    }
                    dst[c] = f;
                }
            }
        }
        out[0] = *(u32*)K1;
        out[1] = ((u32*)K1)[1];
        out[2] = ((u32*)K1)[2];
        out[3] = ((u32*)K1)[3];
        out[4] = ((u32*)K1)[4];
    }

    float f1 = (float)*(u32*)K1;
    if (time != f1) {
        float f2 = (float)*(u32*)K2;
        if (time != f2) {
            if (outIndex) {
                *outIndex = -1;
            }
            return false;
        }
        if (outIndex) {
            *outIndex = upper;
        }
        return true;
    }
    if (outIndex) {
        *outIndex = lower;
    }
    return true;
}
