// nSPCreatureAnim::UpdateAnimationStaticDataVersion (0x009a86b0, 3888 bytes).
// Upgrades a loaded (already pointer-fixed-up) animation_static_data blob in place, one version
// step at a time, from whatever version it was saved with up to the current retail version 25.
// Layouts: 2008 PDB nSPCreatureAnim::v6..v14 structs (retail goes further, to v25), offsets
// confirmed against the disassembly.
//
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2
#include "types.h"

extern "C" __declspec(dllimport) void* __cdecl memmove(void* dst, const void* src, unsigned int n);
extern "C" void* __cdecl memset(void* dst, int v, unsigned int n);

namespace nSPCreatureAnim {

struct context_target {                 // size 0x10 (pack 4 inside the channel)
    uint32_t TypeAndFlags;              // +0x0
    uint32_t Query;                     // +0x4
    uint32_t Reserved[2];               // +0x8
};

struct context {                        // size 0x24
    uint32_t Flags;                     // +0x0
    context_target Primary;             // +0x4
    context_target Secondary;           // +0x14
};

struct key_data_description {           // size 0x20
    uint32_t TypeAndFlags;              // +0x0  low nibble = key data type
    uint32_t DataID;                    // +0x4
    uint32_t OffsetBytes;               // +0x8
    uint32_t StrideBytes;               // +0xc
    uint32_t Reserved[4];               // +0x10
};

struct key_data_frame_info {            // size 0x14 (key data type 0)
    uint32_t FrameI;                    // +0x0
    uint32_t UID;                       // +0x4
    uint16_t EventIndex;                // +0x8
    uint8_t NumEvents;                  // +0xa
    uint8_t Reserved0;                  // +0xb
    uint32_t KeyedFlags;                // +0xc
    uint32_t Reserved1;                 // +0x10
};

struct animation_static_data;

struct animation_channel_static_data {  // size 0xe4
    uint32_t MagicCHAN;                 // +0x0
    animation_static_data* StaticData;  // +0x4
    char Name[128];                     // +0x8
    context Context;                    // +0x88
    union {
        uint32_t Flags;                 // +0xac
        struct {
            uint16_t Flags16;           // +0xac
            uint8_t BlendGroup;         // +0xae
            uint8_t Reserved;           // +0xaf
        };
    };
    uint32_t SpasmFlags;                // +0xb0
    uint32_t Reserved1[8];              // +0xb4
    uint32_t NumKeys;                   // +0xd4
    uint8_t* Keys;                      // +0xd8
    uint32_t NumKeyDataDescriptions;    // +0xdc
    key_data_description* KeyDataDescriptions;   // +0xe0
};

namespace v9 {
struct animation_event_static_data {    // size 0x20
    uint32_t TypeAndFlags;
    uint32_t ConditionFOURCC;
    uint32_t NameID;
    char* NameString;                   // +0xc
    float Value0;
    uint32_t UserData;
    uint32_t Reserved[2];
};
}
namespace v10 {
struct animation_event_static_data {    // size 0x60 (v10 and v11)
    uint32_t TypeAndFlags;              // +0x0
    uint32_t SourceFlags;               // +0x4
    uint32_t DestinationFlags;          // +0x8
    uint32_t SourceQuery[2];            // +0xc
    uint32_t DestinationQuery[2];       // +0x14
    uint32_t Condition4CC;              // +0x1c
    uint32_t ID;                        // +0x20
    uint32_t NameID;                    // +0x24
    char* NameString;                   // +0x28
    uint32_t Data0;                     // +0x2c
    uint32_t Reserved[12];              // +0x30
};
}
namespace v12 {
struct animation_event_static_data {    // size 0x60
    uint32_t TypeAndFlags;              // +0x0
    uint32_t SourcePosFlags;            // +0x4
    uint32_t SourcePosQuery[2];         // +0x8
    uint32_t SourceRotFlags;            // +0x10
    uint32_t SourceRotQuery[2];         // +0x14
    uint32_t SourceScaleFlags;          // +0x1c
    uint32_t SourceScaleQuery[2];       // +0x20
    uint32_t DestinationFlags;          // +0x28
    uint32_t DestinationQuery[2];       // +0x2c
    uint32_t Condition4CC;              // +0x34
    uint32_t ID;                        // +0x38
    uint32_t NameID;                    // +0x3c
    char* NameString;                   // +0x40
    uint32_t Data0;                     // +0x44
    float ForcedOverrideLODRadius2;     // +0x48
    uint32_t Reserved[5];               // +0x4c
};
}

struct animation_static_data {          // size 0x200 (0x154 before v14)
    uint32_t MagicANIM;                 // +0x0
    uint32_t SizeBytes;                 // +0x4
    uint32_t Version;                   // +0x8
    char Name[260];                     // +0xc
    uint32_t ID;                        // +0x110
    int32_t RefCount;                   // +0x114
    uint32_t Flags;                     // +0x118
    float SecondsPerFrame;              // +0x11c
    float TotalFrames;                  // +0x120
    uint32_t SpasmActiveFramesMin;      // +0x124
    uint32_t SpasmActiveFramesMax;      // +0x128
    uint32_t LRUSequence;               // +0x12c
    uint32_t Reserved0[3];              // +0x130
    uint32_t NumEvents;                 // +0x13c
    void* Events;                       // +0x140
    uint32_t NumChannels;               // +0x144
    animation_channel_static_data** ChannelPointers;   // +0x148
    uint32_t NumFixups;                 // +0x14c
    uint32_t FixupTableOffsetBytes;     // +0x150
    uint32_t BranchPredicatesMask;      // +0x154
    uint32_t BranchPredicatesMatch;     // +0x158
    uint32_t Reserved1[41];             // +0x15c
};

uint32_t* GetAvailableDeformsForContextTarget(const context_target* target, uint32_t* count);  // 0x009a8560
uint32_t* GetAvailableDeformIDsForContextTarget(const context_target* target, uint32_t* count); // 0x009a85c0

namespace converters {
void ConvertEvent_v9_v10(const v9::animation_event_static_data* src, v10::animation_event_static_data* dst);    // 0x009a8290
void ConvertEvent_v11_v12(const v10::animation_event_static_data* src, v12::animation_event_static_data* dst);  // 0x009a81b0
}

enum {
    kKeyFrameInfo = 0,
    kKeyVector3 = 1,
    kKeyQuaternion = 2,
    kKeyDeform = 3,
};

static inline uint32_t KeyType(const key_data_description* d) { return d->TypeAndFlags & 0xf; }

static inline uint8_t* GetKey(animation_channel_static_data* ch, key_data_description* d, uint32_t k)
{
    return ch->Keys + d->StrideBytes * k + d->OffsetBytes;
}

// True when some frame-info key of the channel carries events; false as soon as a non-frame-info
// description with bit 0x10 is seen.
static __forceinline bool ChannelHasKeyEvents(animation_channel_static_data* ch)
{
    bool found = false;
    for (uint32_t i = 0; i < ch->NumKeyDataDescriptions; i++) {
        key_data_description* d = &ch->KeyDataDescriptions[i];
        if (KeyType(d) == kKeyFrameInfo) {
            for (uint32_t k = 0; k < ch->NumKeys; k++) {
                if (((key_data_frame_info*)GetKey(ch, d, k))->NumEvents != 0) {
                    found = true;
                    break;
                }
            }
        } else if (d->TypeAndFlags & 0x10) {
            return false;
        }
    }
    if (found)
        return true;
    return false;
}

static inline uint32_t AlignSize(uint32_t n) { return (n + 3) & ~3u; }

bool UpdateAnimationStaticDataVersion(animation_static_data* data)
{
    uint32_t sizeBytes = data->SizeBytes;
    while (data->Version != 25) {
        switch (data->Version) {
        case 6: {
            uint32_t numChannels = data->NumChannels;
            for (uint32_t c = 0; c < numChannels; c++) {
                animation_channel_static_data* ch = data->ChannelPointers[c];
                uint32_t numDeforms;
                uint32_t* deforms = GetAvailableDeformsForContextTarget(&ch->Context.Primary, &numDeforms);
                uint32_t deform = 0;
                uint32_t numDescs = ch->NumKeyDataDescriptions; for (uint32_t i = 0; i < numDescs; i++) {
                    uint32_t t = ch->KeyDataDescriptions[i].TypeAndFlags;
                    if ((t & 0xf) == kKeyDeform) {
                        if (deform < numDeforms && deforms[deform] != 0x70e47545)
                            t |= 0x10;
                        else
                            t &= ~0x10u;
                        ch->KeyDataDescriptions[i].TypeAndFlags = t;
                        deform++;
                    }
                }
            }
            data->Version = 7;
            break;
        }
        case 7: {
            uint32_t numChannels = data->NumChannels;
            for (uint32_t c = 0; c < numChannels; c++) {
                animation_channel_static_data* ch = data->ChannelPointers[c];
                uint32_t numDescs = ch->NumKeyDataDescriptions; for (uint32_t i = 0; i < numDescs; i++) {
                    key_data_description* d = &ch->KeyDataDescriptions[i];
                    if (KeyType(d) == kKeyVector3) {
                        uint32_t numKeys = ch->NumKeys;
                        for (uint32_t k = 0; k < numKeys; k++)
                            ((float*)GetKey(ch, d, k))[3] = 1.0f;
                    } else if (KeyType(d) == kKeyQuaternion) {
                        uint32_t numKeys = ch->NumKeys;
                        for (uint32_t k = 0; k < numKeys; k++)
                            ((float*)GetKey(ch, d, k))[4] = 1.0f;
                    }
                }
            }
            data->Version = 8;
            break;
        }
        case 8:
            data->RefCount = 0;
            data->Version = 9;
            break;
        case 9: {
            // Events grow from 0x20 to 0x60 bytes: rebuild them at the end of the blob.
            uint32_t numEvents = data->NumEvents;
            v9::animation_event_static_data* oldEvents = (v9::animation_event_static_data*)data->Events;
            uint32_t eventsOffset = AlignSize(sizeBytes);
            v10::animation_event_static_data* newEvents =
                (v10::animation_event_static_data*)((char*)data + eventsOffset);
            data->Events = newEvents;
            for (uint32_t e = 0; e < numEvents; e++)
                converters::ConvertEvent_v9_v10(&oldEvents[e], &newEvents[e]);

            // Re-point the NameString fixups at the new events.
            uint32_t* fixups = (uint32_t*)((char*)data + data->FixupTableOffsetBytes);
            uint32_t e = 0;
            while (e < numEvents && newEvents[e].NameString == 0)
                e++;
            if (e < numEvents) {
                uint32_t oldOffset = (uint32_t)((char*)&oldEvents[e].NameString - (char*)data);
                uint32_t numFixups = data->NumFixups;
                for (uint32_t f = 0; f < numFixups; f++) {
                    if (fixups[f] == oldOffset) {
                        fixups[f] = (uint32_t)((char*)&newEvents[e].NameString - (char*)data);
                        e++;
                        if (e >= numEvents)
                            break;
                        while (newEvents[e].NameString == 0) {
                            e++;
                            if (e >= numEvents)
                                goto done9;
                        }
                        if (e >= numEvents)
                            break;
                        oldOffset = (uint32_t)((char*)&oldEvents[e].NameString - (char*)data);
                    }
                }
            }
        done9:
            sizeBytes = eventsOffset + numEvents * sizeof(v10::animation_event_static_data);
            data->Version = 10;
            break;
        }
        case 10: {
            data->Flags &= ~4u;
            if ((uint8_t)(data->Flags & 3) == 1)
                data->Flags |= 8;
            data->Flags &= ~3u;
            uint32_t numChannels = data->NumChannels;
            for (uint32_t c = 0; c < numChannels; c++) {
                animation_channel_static_data* ch = data->ChannelPointers[c];
                ch->Flags &= ~2u;
                ch->StaticData = data;
                if (ch->Flags & 4) {
                    ch->Flags &= ~4u;
                    uint32_t numDescs = ch->NumKeyDataDescriptions; for (uint32_t i = 0; i < numDescs; i++) {
                        key_data_description* d = &ch->KeyDataDescriptions[i];
                        if (KeyType(d) == kKeyFrameInfo) {
                            uint32_t numKeys = ch->NumKeys;
                            for (uint32_t k = 0; k < numKeys; k++)
                                ((key_data_frame_info*)GetKey(ch, d, k))->KeyedFlags |= 2;
                        }
                    }
                }
            }
            data->Version = 11;
            break;
        }
        case 11: {
            uint32_t numEvents = data->NumEvents;
            v10::animation_event_static_data* events = (v10::animation_event_static_data*)data->Events;
            v12::animation_event_static_data* newEvents = (v12::animation_event_static_data*)events;
            for (uint32_t i = 0; i < numEvents; i++) {
                v10::animation_event_static_data old = events[i];
                converters::ConvertEvent_v11_v12(&old, &newEvents[i]);
            }

            uint32_t* fixups = (uint32_t*)((char*)data + data->FixupTableOffsetBytes);
            uint32_t e = 0;
            while (e < numEvents && newEvents[e].NameString == 0)
                e++;
            if (e < numEvents) {
                uint32_t oldOffset = (uint32_t)((char*)&events[e].NameString - (char*)data);
                uint32_t numFixups = data->NumFixups;
                for (uint32_t f = 0; f < numFixups; f++) {
                    if (fixups[f] == oldOffset) {
                        fixups[f] = (uint32_t)((char*)&newEvents[e].NameString - (char*)data);
                        e++;
                        if (e >= numEvents)
                            break;
                        while (newEvents[e].NameString == 0) {
                            e++;
                            if (e >= numEvents)
                                goto done11;
                        }
                        if (e >= numEvents)
                            break;
                        oldOffset = (uint32_t)((char*)&events[e].NameString - (char*)data);
                    }
                }
            }
        done11:
            data->Version = 12;
            break;
        }
        case 12: {
            uint8_t nextGroup = 0;
            uint32_t numChannels = data->NumChannels;
            for (uint32_t c = 0; c < numChannels; c++) {
                animation_channel_static_data* ch = data->ChannelPointers[c];
                bool hasEvents = ChannelHasKeyEvents(ch);
                if ((ch->Flags & 8) || hasEvents) {
                    ch->Flags &= ~8u;
                    uint32_t j;
                    for (j = 0; j < c; j++) {
                        animation_channel_static_data* other = data->ChannelPointers[j];
                        if (ch->Context.Primary.TypeAndFlags == other->Context.Primary.TypeAndFlags &&
                            ch->Context.Primary.Query == other->Context.Primary.Query)
                            break;
                    }
                    if (j < c && data->ChannelPointers[j]->BlendGroup != 0xffffffff)
                        ch->BlendGroup = data->ChannelPointers[j]->BlendGroup;
                    else
                        ch->BlendGroup = nextGroup++;
                } else {
                    ch->BlendGroup = nextGroup++;
                }
            }
            data->Version = 13;
            break;
        }
        case 13: {
            // v14 grew the header from 0x154 to 0x200 bytes: shift everything after it.
            char* oldEnd = (char*)data + 0x154;
            uint32_t size = sizeBytes;
            memmove((char*)data + 0x200, oldEnd, size - 0x154);
            memset(oldEnd, 0, 0xac);
            data->FixupTableOffsetBytes += 0xac;
            uint32_t* fixups = (uint32_t*)((char*)data + data->FixupTableOffsetBytes);
            uint32_t numFixups = data->NumFixups;
            for (uint32_t f = 0; f < numFixups; f++) {
                if (fixups[f] >= 0x154)
                    fixups[f] += 0xac;
                char** p = (char**)((char*)data + fixups[f]);
                if (*p >= oldEnd)
                    *p += 0xac;
            }
            sizeBytes = AlignSize(size) + 0xac;
            data->Version = 14;
            break;
        }
        case 14: {
            uint32_t numChannels = data->NumChannels;
            for (uint32_t c = 0; c < numChannels; c++) {
                animation_channel_static_data* ch = data->ChannelPointers[c];
                if ((ch->Context.Primary.TypeAndFlags & 0x100003) == 0 && ch->Context.Primary.Query == 'toor') {
                    ch->Context.Primary.TypeAndFlags = (ch->Context.Primary.TypeAndFlags & 0xffeffffd) | 1;
                    ch->Context.Primary.Query = 0;
                }
                if ((ch->Context.Secondary.TypeAndFlags & 0x100003) == 0 && ch->Context.Secondary.Query == 'toor') {
                    ch->Context.Secondary.TypeAndFlags = (ch->Context.Secondary.TypeAndFlags & 0xffeffffd) | 1;
                    ch->Context.Secondary.Query = 0;
                }
                ch->Flags16 &= 0xfff7;
                for (uint32_t i = 0; i < ch->NumKeyDataDescriptions; i++) {
                    key_data_description* d = &ch->KeyDataDescriptions[i];
                    if (KeyType(d) == kKeyFrameInfo) {
                        for (uint32_t k = 0; k < ch->NumKeys; k++) {
                            if (((key_data_frame_info*)GetKey(ch, d, k))->NumEvents != 0) {
                                ch->Flags16 |= 8;
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            data->Version = 15;
            break;
        }
        case 15:
        case 16:
        case 17:
        case 18: {
            // Degenerate (zero) quaternion keys become identity.
            uint32_t numChannels = data->NumChannels;
            for (uint32_t c = 0; c < numChannels; c++) {
                animation_channel_static_data* ch = data->ChannelPointers[c];
                uint32_t numDescs = ch->NumKeyDataDescriptions; for (uint32_t i = 0; i < numDescs; i++) {
                    key_data_description* d = &ch->KeyDataDescriptions[i];
                    if (KeyType(d) == kKeyQuaternion) {
                        uint32_t numKeys = ch->NumKeys;
                        for (uint32_t k = 0; k < numKeys; k++) {
                            float* q = (float*)GetKey(ch, d, k);
                            if (q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3] < 1e-6f) {
                                q[0] = 0.0f;
                                q[1] = 0.0f;
                                q[2] = 0.0f;
                                q[3] = 1.0f;
                            }
                        }
                    }
                }
            }
            data->Version = 19;
            break;
        }
        case 19: {
            uint32_t numChannels = data->NumChannels;
            for (uint32_t c = 0; c < numChannels; c++) {
                animation_channel_static_data* ch = data->ChannelPointers[c];
                ch->Context.Primary.TypeAndFlags &= 0xfffefcff;
                ch->Context.Secondary.TypeAndFlags &= 0xfffefcff;
                uint32_t numDescs = ch->NumKeyDataDescriptions; for (uint32_t i = 0; i < numDescs; i++) {
                    uint32_t t = ch->KeyDataDescriptions[i].TypeAndFlags;
                    if ((t & 0xf) == kKeyQuaternion) {
                        uint32_t keep = 0;
                        if (!(ch->Context.Flags & 1)) {
                            if (t & 0x20)
                                keep = 0x20;
                        } else {
                            switch (ch->Context.Flags & 6) {
                            case 0:
                                if (t & 0x20)
                                    keep = 0x20;
                                break;
                            case 2:
                                if (t & 0x40)
                                    keep = 0x40;
                                break;
                            }
                        }
                        ch->KeyDataDescriptions[i].TypeAndFlags = (t & ~0x60u) | keep;
                    }
                }
            }
            data->Version = 20;
            break;
        }
        case 20:
        case 21:
        case 22:
            data->Version = 23;
            break;
        case 23: {
            uint32_t numChannels = data->NumChannels;
            for (uint32_t c = 0; c < numChannels; c++) {
                animation_channel_static_data* ch = data->ChannelPointers[c];
                uint32_t deform = 0;
                uint32_t numDeforms;
                uint32_t* deforms = GetAvailableDeformIDsForContextTarget(&ch->Context.Primary, &numDeforms);
                uint32_t numDescs = ch->NumKeyDataDescriptions; for (uint32_t i = 0; i < numDescs; i++) {
                    key_data_description* d = &ch->KeyDataDescriptions[i];
                    uint32_t t = d->TypeAndFlags;
                    switch (t & 0xf) {
                    case kKeyFrameInfo:
                        d->TypeAndFlags = t & ~0x20u;
                        break;
                    case kKeyVector3:
                        if (ch->Context.Flags & 1)
                            d->TypeAndFlags = t & ~0xc0u;
                        break;
                    case kKeyDeform:
                        t &= ~0x40u;
                        d->TypeAndFlags = t;
                        if (deform < numDeforms) {
                            d->DataID = deforms[deform];
                        } else {
                            d->TypeAndFlags = t & ~0x10u;
                            d->DataID = 0;
                        }
                        deform++;
                        break;
                    }
                }
            }
            data->Version = 24;
            break;
        }
        case 24: {
            uint32_t numChannels = data->NumChannels;
            for (uint32_t c = 0; c < numChannels; c++) {
                animation_channel_static_data* ch = data->ChannelPointers[c];
                uint32_t kind = ch->Context.Primary.TypeAndFlags & 0x100003;
                if (kind == 1 || (kind == 0 && ch->Context.Primary.Query == 'toor')) {
                    uint32_t numDescs = ch->NumKeyDataDescriptions; for (uint32_t i = 0; i < numDescs; i++) {
                        key_data_description* d = &ch->KeyDataDescriptions[i];
                        if (KeyType(d) == kKeyFrameInfo) {
                            uint32_t numKeys = ch->NumKeys;
                            for (uint32_t k = 0; k < numKeys; k++)
                                ((key_data_frame_info*)GetKey(ch, d, k))->KeyedFlags &= ~2u;
                        }
                    }
                }
            }
            data->Version = 25;
            break;
        }
        default:
            return false;
        }
    }
    return true;
}

}  // namespace nSPCreatureAnim
