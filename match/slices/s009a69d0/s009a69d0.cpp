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

// ---------------------------------------------------------------- referenced engine objects
struct IVisualEffect {
    virtual int Unknown0();                    // +0x00
    virtual void Release();                    // +0x04
};

namespace nSPCreatureAnim {

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
    unsigned char mUnknown0[0x18];
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
    unsigned char mUnknown271[0x2d5 - 0x271];
    bool mbSecondFootstep;                     // +0x2d5
    unsigned char mUnknown2d6[0x2e4 - 0x2d6];
    creature_body_instance_data* mpBodies;     // +0x2e4
    creature_body_instance_data* mpBodiesEnd;  // +0x2e8
    unsigned char mUnknown2ec[0x15b8 - 0x2ec];
    anim_data_15b8 mAnimData;                  // +0x15b8
    checkerlib::vector_4 mFootstepBasis;       // +0x1660
};

}  // namespace nSPCreatureAnim

// ---------------------------------------------------------------- engine helpers
float* QuaternionVectorTransform(float* out, const float* quat, const float* vec);  // 0x0099c1a0
void EffectsSpawnThunk(void* manager, uint32 id, const float* pos, const float* mat,
                       IVisualEffect** outEffect);                                  // 0x009fc050
void AudioSetEvent1(IVisualEffect* event, float maxDistance);                        // 0x009fbd50
unsigned int PlaySound(const char* name, void* creature, int soundId, const float* pos,
                       char a, char b, float volume);                               // 0x009a5090

extern float g_zero;                                                                // 0x013eb1bc

using nSPCreatureAnim::creature_body_instance_data;
using nSPCreatureAnim::creature_instance_data;
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
namespace eastl {
struct hash_node {
    uint32 mKey;                               // +0x00
    void* mpValue;                             // +0x04
    hash_node* mpNext;                         // +0x08
};
struct hashtable_iterator {
    hash_node* mpNode;                         // +0x00
    hash_node** mpBucket;                      // +0x04
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
};

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
