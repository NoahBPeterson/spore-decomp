// Slice s009a69d0 -- nSPCreatureAnim footstep audio: PlayFootstep spawns the footstep
// visual/sound effects at the current foot position, UpdateFootsteps walks the active foot
// list and triggers PlayFootstep for each planted foot, and equal_range is the EASTL
// hashtable lookup used by the Eapd audio table.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>
typedef unsigned int uint32;

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt)
#pragma intrinsic(fabs)

// ---------------------------------------------------------------- math types
namespace checkerlib {
class vector_3 {
public:
    float x;   // +0x0
    float y;   // +0x4
    float z;   // +0x8
};
class vector_4 {
public:
    float x;   // +0x0
    float y;   // +0x4
    float z;   // +0x8
    float w;   // +0xc
};
}

// ---------------------------------------------------------------- EASTL hashtable
namespace eastl {
struct hash_node {
    uint32 mKey;                               // +0x00
    void* mpValue;                             // +0x04
    hash_node* mpNext;                         // +0x08
};
struct hashtable_iterator {
    hash_node* mpNode;                         // +0x00
    hash_node** mpBucket;                      // +0x04
    void Advance();                            // 0x009a69d0
};
struct hashtable_range {
    hashtable_iterator first;                  // +0x00
    hashtable_iterator second;                 // +0x08
};
}

typedef eastl::hashtable_range EapdRange;
typedef eastl::hash_node EapdHashNode;
typedef eastl::hashtable_iterator EapdIterator;

class EapdHashTable {
public:
    unsigned char mUnknown0[4];                // +0x00
    EapdHashNode** mpBucketArray;              // +0x04
    uint32 mnBucketCount;                      // +0x08
    EapdRange equal_range(const uint32& key);
    EapdIterator begin();                      // 0x00594410
};

// ---------------------------------------------------------------- referenced engine objects
// Transform message filled in by IEffect::GetXform / consumed by SetXform.
struct XformMsg {
    unsigned short mFlags;                     // +0x00
    unsigned short mCount;                     // +0x02
    checkerlib::vector_3 mPos;                 // +0x04
    float mScale;                              // +0x10
    float mRot[9];                             // +0x14
    XformMsg();                                // 0x00434040
};

struct IVisualEffect {
    virtual int Unknown0();                    // +0x00
    virtual void Release();                    // +0x04
    virtual void Unknown08();                  // +0x08
    virtual void Unknown0c();                  // +0x0c
    virtual bool IsPlaying();                  // +0x10
    virtual void Unknown14();                  // +0x14
    virtual void SetXform(XformMsg* msg);      // +0x18
    virtual void Unknown1c();                  // +0x1c
    virtual void GetXform(XformMsg* msg);      // +0x20
};

// Intrusive reference-counted pointer (EA::AutoRefCount) assign helper.
struct effect_ref {
    void* mpObject;                            // +0x00
    effect_ref* assign(void* object);          // 0x0099cab0
};

namespace nSPCreatureAnim {

struct creature_effect;

// Per-body static data. Retail keeps the footstep radius vector at +0x138, a body flags
// byte at +0x150 and the body sound id at +0x1f8.
struct creature_body_static_data {
    unsigned char mUnknown0[0x138];
    checkerlib::vector_3 mFootstepExtent;      // +0x138
    unsigned char mUnknown144[0x150 - 0x144];
    unsigned char mFlags;                      // +0x150
    unsigned char mUnknown151[0x1f8 - 0x151];
    int mFootSoundId;                          // +0x1f8
};

// Per-body instance data (retail stride 0x2bc).
struct creature_body_instance_data {
    creature_body_static_data* mpStaticData;   // +0x00
    unsigned char mUnknown4[0x10 - 0x04];
    checkerlib::vector_3 mCenter;              // +0x10
    unsigned char mUnknown1c[0x4c - 0x1c];
    float mAnimWeight;                         // +0x4c
    unsigned char mUnknown50[0x2bc - 0x50];
};

// One foot of the walking dynamics (retail stride 0x108).
class dynamics_foot {
public:
    unsigned char mUnknown0[0x58];
    int mBodyIdx;                              // +0x58
    bool mFootDown;                            // +0x5c
    bool mEdgeTrigger;                         // +0x5d
    unsigned char mUnknown5e[0x108 - 0x5e];
};

struct footstep_event_list {
    dynamics_foot* mpBegin;                    // +0x00
    dynamics_foot* mpEnd;                      // +0x04
};

// Sub-object at creature_instance_data+0x15b8; its footstep event list lives at +0x24.
struct anim_data_15b8 {
    unsigned char mUnknown0[0x24];
    footstep_event_list mEvents;               // +0x24
    footstep_event_list* get_events();         // 0x00a09f50
    unsigned char mUnknown2c[0xa8 - 0x2c];
};

// Per-creature animation instance data (retail layout).
struct creature_instance_data {
    void* mpStaticData;                        // +0x00
    void* mpRoot;                              // +0x04
    unsigned char mUnknown08[0x18 - 0x08];
    checkerlib::vector_3 mPosition;            // +0x18
    unsigned char mUnknown24[0x3c - 0x24];
    float mQuatW;                              // +0x3c
    float mQuatX;                              // +0x40
    float mQuatY;                              // +0x44
    float mQuatZ;                              // +0x48
    unsigned char mUnknown4c[0x70 - 0x4c];
    float mScale;                              // +0x70
    unsigned char mUnknown74[0x260 - 0x74];
    bool mbField260;                           // +0x260
    bool mbFootstepsEnabled;                   // +0x261
    unsigned char mUnknown262[0x270 - 0x262];
    bool mbField270;                           // +0x270
    unsigned char mUnknown271[0x2ac - 0x271];
    uint32 mField2ac;                          // +0x2ac
    unsigned char* mpEventData;                // +0x2b0
    int mEventDataStride;                      // +0x2b4
    uint32* mpEventDataCount;                  // +0x2b8
    uint32 mEventDataCapacity;                 // +0x2bc
    unsigned char mUnknown2c0[0x2c4 - 0x2c0];
    unsigned char mSoundName[0x2d5 - 0x2c4];   // +0x2c4
    bool mbSecondFootstep;                     // +0x2d5
    unsigned char mUnknown2d6[0x2e4 - 0x2d6];
    creature_body_instance_data* mpBodies;     // +0x2e4
    creature_body_instance_data* mpBodiesEnd;  // +0x2e8
    unsigned char mUnknown2ec[0x15b8 - 0x2ec];
    anim_data_15b8 mAnimData;                  // +0x15b8
    checkerlib::vector_4 mFootstepBasis;       // +0x1660
    unsigned char mUnknown1670[0x17a0 - 0x1670];
    EapdHashTable mEffects;                    // +0x17a0
    void HitBody(uint32 bodyId, const checkerlib::vector_3& vec, uint32 a, bool b, float c); // 0x009bb680
    void SetStyleWeightForAllGroups(const char* group, int value, float weight);             // 0x009b7b70
    creature_effect* AddEffect(uint32 id, int a, int b);                                     // 0x009cb300
    int Release();                                                                            // 0x009c4cc0
};

// Animation-event record stored in creature_instance_data's effect table (retail layout).
struct creature_effect {
    uint32 key;                                        // +0x00
    uint32 id;                                         // +0x04
    uint32 bidx;                                       // +0x08
    checkerlib::vector_3 local_pos;                    // +0x0c
    // Retail's prelude before allow_dupes is 0xc shorter than the dev header's
    // matrix_3x3, so the retail record starts its flags at +0x30. This function
    // never touches the prelude.
    unsigned char mUnknown18[0x30 - 0x18];             // +0x18
    bool allow_dupes;                                  // +0x30
    bool event_info_valid;                             // +0x31
    unsigned char mPad32[2];                           // +0x32
    uint32 EventTypeAndFlags;                          // +0x34
    uint32 EventSourcePosFlags;                        // +0x38
    uint32 EventSourceRotFlags;                        // +0x3c
    uint32 EventSourceScaleFlags;                      // +0x40
    uint32 EventDestinationFlags;                      // +0x44
    uint32 EventData0I;                                // +0x48
    effect_ref source_pos_creature;                    // +0x4c
    effect_ref source_rot_creature;                    // +0x50
    effect_ref source_scale_creature;                  // +0x54
    uint32 source_pos_bidx;                            // +0x58
    uint32 source_rot_bidx;                            // +0x5c
    uint32 source_scale_bidx;                          // +0x60
    checkerlib::vector_3 source_pos_random_offset;     // +0x64
    int rot_relation;                                  // +0x70
    int scale_relation;                                // +0x74
    effect_ref destination_creature;                   // +0x78
    uint32 destination_bidx;                           // +0x7c
    checkerlib::vector_3 destination_pos_random_offset;// +0x80
    effect_ref effect;                                 // +0x8c
    effect_ref model;                                  // +0x90
    uint32 sound_id;                                   // +0x94
    checkerlib::vector_3 last_sound_pos;               // +0x98
    effect_ref unknown;                                // +0xa4
    void (*set_unknown_posrot)();                      // +0xa8
    void Init(IVisualEffect* effect, uint32 a, uint32 b);  // 0x009caa40
    void Init(uint32 soundId, uint32 a, uint32 b);         // 0x009caa90
    void RefreshWorldState();                              // 0x009c8900
};

}  // namespace nSPCreatureAnim

// ---------------------------------------------------------------- engine helpers
float* QuaternionVectorTransform(float* out, const float* quat, const float* vec);  // 0x0099c1a0
bool EffectsSpawnThunk(void* manager, uint32 id, const float* pos, const float* mat,
                       IVisualEffect** outEffect);                                  // 0x009fc050
void AudioSetEvent1(IVisualEffect* event, float maxDistance);                        // 0x009fbd50
void AudioSetEvent5(IVisualEffect* event, const void* value);                        // 0x009fbd30
void AudioSetEvent9(IVisualEffect* event, const float* value);                       // 0x009fbcd0
void AudioSetEvent10(IVisualEffect* event, float value);                             // 0x009fbcf0
unsigned int PlaySound(const char* name, void* creature, int soundId, const float* pos,
                       char a, char b, float volume);                               // 0x009a5090
void QuaternionToMatrix(float* out, const float* quat);                             // 0x009a46a0
float* NormalizeVec3(float* out, const float* v, float* lenOut);                    // 0x009a49d0
void FUN_00e82690(int a, float b);                                                  // 0x00e82690

namespace nSPCreatureAnim {
uint32 GetEventDataAs32Bits(int a0, void* a1, int a2, int a3, void* creature,
                            uint32 index, float defaultValue, int a7);              // 0x009a5860
float GetEventDataAsFloat(int a0, void* a1, int a2, void* p3,
                          uint32 index, float defaultValue, int a6);                // 0x009a59a0
bool ContextFilterEventLocationData(uint32 a0, uint32 a1, const uint32* ids,
                                    uint32 a3, uint32 a4);                          // 0x009a4890
bool ComputeEventLocationState(char randomize, int evData, uint32 flags, int p4,
                               void* owner, void* creature, uint32 boneIdx,
                               float* pos, float* pos2, void* outQuat, float* outScalar,
                               float* outVec, float* dirIn, float* dirIn2, int p15); // 0x009a59e0
}

struct IMessageServer {
    virtual void Unknown0();                   // +0x00
    virtual void Unknown4();                   // +0x04
    virtual void Unknown8();                   // +0x08
    virtual void Unknown0c();                  // +0x0c
    virtual void Unknown10();                  // +0x10
    virtual void PostMessage(uint32 id, const void* msg, int flags); // +0x14
};
IMessageServer* GetMessageServer();            // 0x0067dcc0

extern float g_zero;                                                                // 0x013eb1bc
extern float g_01550aa8;                                                            // 0x01550aa8
extern float g_01550aac;                                                            // 0x01550aac
extern float g_hitBodyScale;                                                        // 0x01550ac4

using nSPCreatureAnim::creature_body_instance_data;
using nSPCreatureAnim::creature_instance_data;
using nSPCreatureAnim::creature_effect;
using nSPCreatureAnim::GetEventDataAs32Bits;
using nSPCreatureAnim::GetEventDataAsFloat;
using nSPCreatureAnim::ContextFilterEventLocationData;
using nSPCreatureAnim::ComputeEventLocationState;
using nSPCreatureAnim::dynamics_foot;

// ---------------------------------------------------------------- footstep effect
// @ 0x009a6a00
void PlayFootstep(void* manager, creature_instance_data* creature,
                  creature_body_instance_data* body, float volume)
{
    float transformed[3];
    float* p = QuaternionVectorTransform(transformed, &creature->mQuatW, &body->mCenter.x);

    float pos[3];
    pos[0] = p[0] + creature->mPosition.x;
    pos[1] = p[1] + creature->mPosition.y;
    pos[2] = p[2] + creature->mPosition.z;

    const float w = creature->mQuatW;
    const float x = creature->mQuatX;
    const float y = creature->mQuatY;
    const float z = creature->mQuatZ;

    float mat[9];
    mat[0] = 1.0f - (x * x + y * y) * 2.0f;
    mat[1] = (x * w - z * y) * 2.0f;
    mat[2] = (z * x + y * w) * 2.0f;
    mat[3] = (z * y + x * w) * 2.0f;
    mat[4] = 1.0f - (w * w + y * y) * 2.0f;
    mat[5] = (x * y - z * w) * 2.0f;
    mat[6] = (y * w - z * x) * 2.0f;
    mat[7] = (z * w + x * y) * 2.0f;
    mat[8] = 1.0f - (w * w + x * x) * 2.0f;

    const float scale = creature->mScale;
    const float rx = body->mpStaticData->mFootstepExtent.x * scale;
    const float ry = body->mpStaticData->mFootstepExtent.y * scale;
    const float rz = body->mpStaticData->mFootstepExtent.z * scale;
    const float maxDistance = 2.0f * (float)sqrt((double)(rx * rx + ry * ry + rz * rz));

    IVisualEffect* effect = 0;
    EffectsSpawnThunk(manager, 0x2d4adb36, pos, mat, &effect);
    if (effect != 0)
        AudioSetEvent1(effect, maxDistance);

    if (creature->mbSecondFootstep) {
        if (effect != 0) {
            IVisualEffect* old = effect;
            effect = 0;
            old->Release();
        }
        EffectsSpawnThunk(manager, 0xdcae75d5, pos, mat, &effect);
        if (effect != 0)
            AudioSetEvent1(effect, maxDistance);
    }

    PlaySound("foot_step", creature, body->mpStaticData->mFootSoundId, pos, 0, 0, volume);

    if (effect != 0)
        effect->Release();
}

// ---------------------------------------------------------------- footstep update
// @ 0x009a6cc0
void UpdateFootsteps(void* manager, creature_instance_data* creature)
{
    if (!creature->mbFootstepsEnabled || !creature->mbField270)
        return;

    nSPCreatureAnim::footstep_event_list* events = creature->mAnimData.get_events();
    int total = (int)(events->mpEnd - events->mpBegin);
    if (total != 0) {
        int remaining = total;
        int index = 0;
        do {
            dynamics_foot* foot = &events->mpBegin[index];
            creature_body_instance_data* body = &creature->mpBodies[foot->mBodyIdx];
            if (foot->mEdgeTrigger && foot->mFootDown &&
                (body->mpStaticData->mFlags & 0x10) == 0 &&
                body->mAnimWeight == 1.0f &&
                (creature->mFootstepBasis.x * creature->mFootstepBasis.x +
                 creature->mFootstepBasis.y * creature->mFootstepBasis.y +
                 creature->mFootstepBasis.z * creature->mFootstepBasis.z > 0.1 ||
                 fabs((double)creature->mFootstepBasis.w) > 0.2)) {
                PlayFootstep(manager, creature, body, g_zero);
            }
            ++index;
        } while (--remaining);
    }
}

// ---------------------------------------------------------------- EASTL hashtable lookup
// @ 0x009a6dd0
EapdRange EapdHashTable::equal_range(const uint32& key)
{
    EapdHashNode** const buckets = this->mpBucketArray;
    EapdHashNode** const bucket = &buckets[key % this->mnBucketCount];
    EapdHashNode* node = *bucket;
    while (node != 0) {
        if (key == node->mKey)
            break;
        node = node->mpNext;
    }

    EapdRange result;
    if (node == 0) {
        _ReadWriteBarrier();
        EapdHashNode** const endBucket = &this->mpBucketArray[this->mnBucketCount];
        EapdHashNode* const endNode = *endBucket;
        result.first.mpNode = endNode;
        result.first.mpBucket = endBucket;
        result.second.mpNode = endNode;
        result.second.mpBucket = endBucket;
        return result;
    }

    EapdHashNode* next = node->mpNext;
    while (next != 0 && key == next->mKey)
        next = next->mpNext;

    EapdHashNode** nextBucket = bucket;
    if (next == 0) {
        nextBucket = bucket + 1;
        while (*nextBucket == 0)
            ++nextBucket;
        next = *nextBucket;
    }

    result.first.mpNode = node;
    result.first.mpBucket = bucket;
    result.second.mpNode = next;
    result.second.mpBucket = nextBucket;
    return result;
}

// ---------------------------------------------------------------- event dispatch
// Raw animation-event payload laid out by the animation resource (uint32 slots; the
// slot indices below follow the disassembly's [eventData + 4*index] accesses).
struct creature_event_data {
    uint32 mEventType;          // +0x00  slot 0
    uint32 mLocFlagsPos;        // +0x04  slot 1
    uint32 mField08;            // +0x08  slot 2
    uint32 mField0c;            // +0x0c  slot 3
    uint32 mLocFlagsRot;        // +0x10  slot 4
    uint32 mField14;            // +0x14  slot 5
    uint32 mField18;            // +0x18  slot 6
    uint32 mLocFlagsScale;      // +0x1c  slot 7
    uint32 mField20;            // +0x20  slot 8
    uint32 mField24;            // +0x24  slot 9
    uint32 mLocFlagsDest;       // +0x28  slot 0xa
    uint32 mField2c;            // +0x2c  slot 0xb
    uint32 mField30;            // +0x30  slot 0xc
    uint32 mField34;            // +0x34  slot 0xd
    uint32 mEventId;            // +0x38  slot 0xe
    uint32 mEffectId;           // +0x3c  slot 0xf
    const char* mpName;         // +0x40  slot 0x10
    uint32 mEventValue;         // +0x44  slot 0x11
    uint32 mField48;            // +0x48  slot 0x12
    uint32 mField4c;            // +0x4c  slot 0x13
};

// One entry of the creature's per-instance data-event ring buffer.
struct creature_data_event_record {
    uint32 mEffectId;           // +0x00
    uint32 mBoneIdx;            // +0x04
    uint32 mValue;              // +0x08
};

// Six-dword message posted through cMessageServer's vtable slot +0x14.
struct creature_event_message {
    uint32 mEffectId;           // +0x00
    const char* mpName;         // +0x04
    void* mpRoot;               // +0x08
    uint32 mBoneIdx;            // +0x0c
    uint32 mEventValue;         // +0x10
    uint32 mField14;            // +0x14
};

// @ 0x009a6e60
void __cdecl HandleEventType(void* param1, creature_instance_data* param2,
                             creature_instance_data* param3, void* param4, void* param5,
                             uint32 param6, uint32 param7, uint32 param8,
                             const float* param9, const float* param10, const float* param11,
                             float param12, const float* param13, int param14, int param15,
                             creature_instance_data* param16, const uint32* param17,
                             uint32 param18, uint32 param19, creature_event_data* param20,
                             int param21)
{
    const uint32 eventType = param20->mEventType;
    const uint32 mode = eventType & 0x20007;

    // Modes above 0x20000: only exactly 0x20001 posts a message, the rest are ignored.
    if (mode > 0x20000) {
        if (mode != 0x20001)
            return;
        creature_event_message msg;
        msg.mEffectId = param20->mEffectId;
        msg.mpName = param20->mpName;
        msg.mpRoot = param3 != 0 ? param3->mpRoot : 0;
        msg.mBoneIdx = param6;
        msg.mEventValue = param20->mEventValue;
        msg.mField14 = param20->mField4c;
        if (GetMessageServer() != 0)
            GetMessageServer()->PostMessage(param20->mEffectId, &msg, 0);
        return;
    }

    if (mode == 0x20000) {
        if (param3 == 0)
            return;
        const uint32 v1 = GetEventDataAs32Bits((int)eventType, &param20->mField4c, 1, 0,
                                               param3, param6, 0.0f, param21);
        const uint32 v2 = GetEventDataAs32Bits((int)eventType, &param20->mEventValue, 0, 1,
                                               param3, param6, 0.0f, param21);
        param3->SetStyleWeightForAllGroups(param20->mpName, (int)v2, *(const float*)&v1);
        return;
    }

    switch (mode) {
    case 0: {
        // Sound event: create the sound handle and register it in the effect table.
        const uint32 sound = PlaySound(param20->mpName, param3, (int)param6, param9, 1,
                                       (char)((eventType >> 10) & 1), 0.0f);
        if (sound == 0)
            return;
        creature_effect* ev = param2->AddEffect(param19, 1, 0);
        ev->Init(sound, param6, param20->mEventId);
        ev->allow_dupes = true;
        ev->EventTypeAndFlags = eventType;
        ev->EventData0I = param20->mEventValue;
        ev->EventSourcePosFlags = param20->mLocFlagsPos;
        ev->EventSourceRotFlags = param20->mLocFlagsRot;
        ev->EventSourceScaleFlags = param20->mLocFlagsScale;
        ev->source_pos_creature.assign(param3);
        ev->source_rot_creature.assign(param4);
        ev->source_scale_creature.assign(param5);
        ev->source_scale_bidx = param8;
        ev->source_rot_bidx = param7;
        ev->source_pos_bidx = param6;
        ev->source_pos_random_offset.x = param13[0];
        ev->source_pos_random_offset.y = param13[1];
        ev->source_pos_random_offset.z = param13[2];
        ev->scale_relation = param15;
        ev->rot_relation = param14;
        ev->EventDestinationFlags = 0;
        creature_instance_data* oldDest =
            (creature_instance_data*)ev->destination_creature.mpObject;
        if (oldDest != 0) {
            ev->destination_creature.mpObject = 0;
            oldDest->Release();
        }
        ev->destination_bidx = 0;
        ev->destination_pos_random_offset.x = 0.0f;
        ev->destination_pos_random_offset.y = 0.0f;
        ev->destination_pos_random_offset.z = 0.0f;
        return;
    }

    case 1: {
        // Visual effect event: resolve each candidate location, spawn the effect and
        // register the fully populated effect record.
        float pos[3];
        float pos2[3];
        float quatOut[4];
        float scalar;
        float vec[3];

        const uint32 count = param18 != 0 ? param18 : 1;
        uint32 bodyId = 0xffffffff;
        for (uint32 i = 0; i < count; ++i) {
            if (param18 != 0) {
                if (!ContextFilterEventLocationData(param20->mLocFlagsDest, i, param17,
                                                    param2->mField2ac, param6))
                    continue;
                bodyId = param17[i];
                ComputeEventLocationState(1, (int)eventType, param20->mLocFlagsDest,
                                          (int)param20->mEventValue, param2, param16, bodyId,
                                          pos, pos2, quatOut, &scalar, vec, pos, pos2, param21);
            }

            float mat[9];
            QuaternionToMatrix(mat, param11);

            IVisualEffect* effect = 0;
            if (EffectsSpawnThunk(param1, param20->mEffectId, param9, mat, &effect)) {
                AudioSetEvent1(effect, param12);
                if ((eventType & 0x200000) != 0) {
                    XformMsg info;
                    effect->GetXform(&info);
                    ++info.mCount;
                    info.mScale = param12;
                    effect->SetXform(&info);
                }
                if (param3 != 0 && (eventType & 0x10000) != 0)
                    AudioSetEvent5(effect, &param3->mSoundName[0]);

                creature_effect* ev = param2->AddEffect(param19, 1, 0);
                ev->Init(effect, param6, param20->mEventId);
                ev->allow_dupes = true;
                ev->EventTypeAndFlags = eventType;
                ev->EventData0I = param20->mEventValue;
                ev->EventSourcePosFlags = param20->mLocFlagsPos;
                ev->EventSourceRotFlags = param20->mLocFlagsRot;
                ev->EventSourceScaleFlags = param20->mLocFlagsScale;
                ev->source_pos_creature.assign(param3);
                ev->source_rot_creature.assign(param4);
                ev->source_scale_creature.assign(param5);
                ev->source_scale_bidx = param8;
                ev->source_rot_bidx = param7;
                ev->source_pos_bidx = param6;
                ev->source_pos_random_offset.x = param13[0];
                ev->source_pos_random_offset.y = param13[1];
                ev->source_pos_random_offset.z = param13[2];
                ev->scale_relation = param15;
                ev->rot_relation = param14;
                if (param18 != 0) {
                    AudioSetEvent9(effect, pos);
                    AudioSetEvent10(effect, 1.0f);
                    ev->EventDestinationFlags = param20->mLocFlagsDest;
                    ev->destination_creature.assign(param16);
                    ev->destination_bidx = bodyId;
                    ev->destination_pos_random_offset.x = vec[0];
                    ev->destination_pos_random_offset.y = vec[1];
                    ev->destination_pos_random_offset.z = vec[2];
                } else {
                    ev->EventDestinationFlags = 0;
                    creature_instance_data* oldDest =
                        (creature_instance_data*)ev->destination_creature.mpObject;
                    if (oldDest != 0) {
                        ev->destination_creature.mpObject = 0;
                        oldDest->Release();
                    }
                    ev->destination_bidx = 0;
                    ev->destination_pos_random_offset.x = 0.0f;
                    ev->destination_pos_random_offset.y = 0.0f;
                    ev->destination_pos_random_offset.z = 0.0f;
                }
            }
            if (effect != 0)
                effect->Release();
        }
        return;
    }

    case 2: {
        // Append a (effect id, bone, value) record to the creature's data-event buffer.
        if (param3 == 0 || param3->mpEventDataCount == 0 || param3->mpEventData == 0)
            return;
        if (*param3->mpEventDataCount >= param3->mEventDataCapacity)
            return;
        creature_data_event_record* record = (creature_data_event_record*)
            (param3->mpEventData + param3->mEventDataStride * *param3->mpEventDataCount);
        record->mEffectId = param20->mEffectId;
        record->mBoneIdx = param6;
        record->mValue = param20->mEventValue;
        ++*param3->mpEventDataCount;
        return;
    }

    case 3: {
        // Hit-body event: apply the scaled event direction as a hit to each candidate body.
        if (param16 == 0)
            return;
        for (uint32 i = 0; i < param18; ++i) {
            const uint32 bodyId = param17[i];
            if (!ContextFilterEventLocationData(param20->mLocFlagsDest, i, param17,
                                                param2->mField2ac, param6))
                continue;
            float value = GetEventDataAsFloat((int)eventType, &param20->mEventValue, 0,
                                              param3, param6, g_01550aa8, param21);
            value *= g_01550aac;
            float dir[3];
            const float* n = NormalizeVec3(dir, param10, (float*)0);
            checkerlib::vector_3 hit;
            hit.x = value * n[0];
            hit.y = value * n[1];
            hit.z = value * n[2];
            param16->HitBody(bodyId, hit, 0, false, g_hitBodyScale);
        }
        return;
    }

    case 4: {
        // Refresh the named effect entries in the creature's effect table.
        EapdHashTable* table = &param2->mEffects;
        EapdIterator first;
        EapdIterator second;
        if ((eventType & 0x400000) != 0) {
            second.mpNode = table->mpBucketArray[table->mnBucketCount];
            second.mpBucket = &table->mpBucketArray[table->mnBucketCount];
            first = table->begin();
        } else {
            const uint32 key = param19;
            const EapdRange range = table->equal_range(key);
            first = range.first;
            second = range.second;
        }
        if (first.mpNode == table->mpBucketArray[table->mnBucketCount])
            return;
        while (first.mpNode != second.mpNode) {
            creature_effect* ev = (creature_effect*)first.mpNode->mpValue;
            if (ev->id == param20->mEventId)
                ev->RefreshWorldState();
            first.Advance();
        }
        return;
    }

    case 5: {
        // Update the stored event value of the named effect entries.
        EapdHashTable* table = &param2->mEffects;
        EapdIterator first;
        EapdIterator second;
        if ((eventType & 0x400000) != 0) {
            second.mpNode = table->mpBucketArray[table->mnBucketCount];
            second.mpBucket = &table->mpBucketArray[table->mnBucketCount];
            first = table->begin();
        } else {
            const uint32 key = param19;
            const EapdRange range = table->equal_range(key);
            first = range.first;
            second = range.second;
        }
        if (first.mpNode == table->mpBucketArray[table->mnBucketCount])
            return;
        while (first.mpNode != second.mpNode) {
            creature_effect* ev = (creature_effect*)first.mpNode->mpValue;
            if (ev->id == param20->mEventId)
                ev->EventData0I = param20->mEventValue;
            first.Advance();
        }
        return;
    }

    case 6: {
        // Raw float event forwarded to the caller-supplied handler.
        const float value = GetEventDataAsFloat((int)eventType, &param20->mEventValue, 0,
                                                param3, param6, 0.0f, param21);
        FUN_00e82690((int)param20->mEffectId, value);
        return;
    }

    case 7: {
        // Footstep event at the given body.
        if (param3 == 0)
            return;
        const uint32 bodyCount = (uint32)(param3->mpBodiesEnd - param3->mpBodies);
        if (param6 >= bodyCount)
            return;
        const float volume = GetEventDataAsFloat((int)eventType, &param20->mEventValue, 0,
                                                 param3, param6, 0.0f, param21);
        PlayFootstep(param1, param3, &param3->mpBodies[param6], volume);
        return;
    }

    default:
        return;
    }
}
