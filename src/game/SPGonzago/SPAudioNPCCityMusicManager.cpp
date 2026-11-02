// src/game/SPGonzago/SPAudioNPCCityMusicManager.cpp -- migrated from slice(s) s00eaa9a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAudioNPCCityMusicManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Messaging/AutoHandler.h"
#include "EA/Allocator/ZoneObject.h"
#include "SP/Audio/cMixModeManager.h"
#pragma warning(disable: 4100)

// ---- items of slice s00eaa9a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
namespace Audio {
struct ResourceKey { uint32_t instanceID, typeID, groupID; };
}
}
namespace SP {
namespace Audio {
class cMixMode_s00ea_a9a0 { public:
    virtual void AddRef();                              // +0
    virtual void Release();                             // +4
    uint32_t pad[0x1c];
    cMixMode_s00ea_a9a0(ResourceKey key, void* mgr);               // 0x00ea9320 (ret 0x10: key by value + manager)
    static void* operator new(size_t sz, const char* name, int a, int b, int c, int d);  // 0x00f473a0
};
}
}
namespace SP {
namespace Audio {
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount& operator=(T* p) {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};
}
}
namespace SP {
namespace Audio {
struct ModeNode {
    uint32_t first;
    AutoRefCount<cMixMode_s00ea_a9a0> second;
    ModeNode* mpNext;
};
}
}
namespace SP {
namespace Audio {
struct ModeIterator {
    ModeNode* mpNode;
    ModeNode** mpBucket;
    ModeIterator(ModeNode* node, ModeNode** bucket) : mpNode(node), mpBucket(bucket) {}
    ModeIterator(ModeNode** bucket) : mpNode(*bucket), mpBucket(bucket) {}
    ModeIterator(const ModeIterator& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
};
}
}
namespace SP {
namespace Audio {
inline bool operator==(const ModeIterator& a, const ModeIterator& b) { return a.mpNode == b.mpNode; }
}
}
namespace SP {
namespace Audio {
struct ChannelNode {
    uint32_t mKey;                  // +0x00
    int32_t mRefCount;              // +0x04
    ChannelNode* mpNext;            // +0x08
};
}
}
namespace SP {
namespace Audio {
struct RandomState {
    uint32_t mState;                // +0x00
    uint32_t Range(uint32_t count); // 0x00a68fb0
};
}
}
namespace SP {
namespace Audio {
struct ChannelMap {
    void* mpVtable;                 // +0x00
    ChannelNode** mpBucketArray;    // +0x04
    uint32_t mnBucketCount;         // +0x08
    uint32_t mnElementCount;        // +0x0c
    char mAllocator[0x10];          // +0x10

    void FreeNodes(ChannelNode** buckets, uint32_t count);   // 0x00693230
    ChannelNode* FindNode(uint32_t key);
    ChannelNode* InsertNode(uint32_t key);
};
}
}
namespace SP {
namespace Audio {
struct IGonzagoSubsystem {
    virtual void AddRef();
    virtual void Release();
};
}
}
namespace SP {
namespace Audio {
struct GonzagoDesc {
    uint32_t mField0, mField1, mField2, mField3;
};
}
}
namespace SP {
namespace Audio {
struct IGonzagoSystem {
virtual void v00();
virtual void v04();
virtual void v08();
    virtual void CreateSubsystem(IGonzagoSubsystem** out, const GonzagoDesc* desc,
                                 int a, int b, int c, int d);   // +0x0c
};
}
}
namespace SP {
namespace Audio {
class cNPCCityMusicManager;
}
}
namespace SP {
namespace Audio {
IGonzagoSystem* GetGonzagoSystem();                    // 0x008de1a0
}
}
namespace SP {
namespace Audio {
bool __cdecl GetChannelList(IGonzagoSubsystem* sub, float param, void*** list, int* count);  // 0x006a0840
}
}
namespace SP {
namespace Audio {
extern const float kGonzagoParams[5];                  // 0x01488284
}
}
namespace SP {
namespace Audio {
class cNPCCityMusicManager {
public:
    void ClearChannelMaps();                            // 0x00eab520
    ChannelNode* AcquireChannel(uint32_t id);           // 0x00eab560
    void AddChannelRef(uint32_t id, void* key);         // 0x00eab650
    void ReleaseChannel(uint32_t id, void* key);        // 0x00eab690
    void InitGonzagoSubsystem();                        // 0x00eab6e0

    char pad00[0x1c];                   // +0x00
    ChannelMap mChannels[5];            // +0x1c
    RandomState mRandom;                // +0xbc
};
}
}
namespace SP {
namespace Audio {
ChannelNode* ChannelMap::FindNode(uint32_t key) {
    if (!mnBucketCount)
        return 0;
    ChannelNode* node = mpBucketArray[key % mnBucketCount];
    while (node && node->mKey != key)
        node = node->mpNext;
    return node;
}
}
}
namespace SP {
namespace Audio {
ChannelNode* ChannelMap::InsertNode(uint32_t key) {
    if (!mnBucketCount) {
        mnBucketCount = 8;
        mpBucketArray = new ChannelNode*[8]();
    }
    uint32_t bucket = key % mnBucketCount;
    ChannelNode* node = new ChannelNode;
    node->mKey = key;
    node->mRefCount = 0;
    node->mpNext = mpBucketArray[bucket];
    mpBucketArray[bucket] = node;
    ++mnElementCount;
    return node;
}
}
}
// ---- items of slice s00eaa9a0 end

// @ 0x00eab520
namespace SP { namespace Audio {
void cNPCCityMusicManager::ClearChannelMaps()
{
    for (int i = 0; i < 5; ++i) {
        ChannelMap& map = mChannels[i];
        map.FreeNodes(map.mpBucketArray, map.mnBucketCount);
        map.mnElementCount = 0;
    }
}
}}  // namespace SP::Audio

// @ 0x00eab560
namespace SP { namespace Audio {
ChannelNode* cNPCCityMusicManager::AcquireChannel(uint32_t id)
{
    ChannelMap& map = mChannels[id];
    int best = 0x7fffffff;
    int ties = 0;
    for (uint32_t bucket = 0; bucket < map.mnBucketCount; ++bucket) {
        for (ChannelNode* node = map.mpBucketArray[bucket]; node; node = node->mpNext) {
            int count = node->mRefCount;
            if (count == best) {
                ++ties;
            } else if (count < best) {
                best = count;
                ties = 1;
            }
        }
    }
    uint32_t pick = mRandom.Range((uint32_t)ties);
    for (uint32_t bucket = 0; bucket < map.mnBucketCount; ++bucket) {
        for (ChannelNode* node = map.mpBucketArray[bucket]; node; node = node->mpNext) {
            if (node->mRefCount == best) {
                if (pick == 0)
                    return node;
                --pick;
            }
        }
    }
    return 0;
}
}}  // namespace SP::Audio

// @ 0x00eab650
namespace SP { namespace Audio {
void cNPCCityMusicManager::AddChannelRef(uint32_t id, void* key)
{
    ChannelMap& map = mChannels[id];
    uint32_t value = (uint32_t)key;
    ChannelNode* node = map.FindNode(value);
    if (!node)
        node = map.InsertNode(value);
    ++node->mRefCount;
}
}}  // namespace SP::Audio

// @ 0x00eab690
namespace SP { namespace Audio {
void cNPCCityMusicManager::ReleaseChannel(uint32_t id, void* key)
{
    ChannelNode* node = mChannels[id].FindNode((uint32_t)key);
    if (node && node->mRefCount > 0)
        --node->mRefCount;
}
}}  // namespace SP::Audio

// @ 0x00eab6e0
namespace SP { namespace Audio {
void cNPCCityMusicManager::InitGonzagoSubsystem()
{
    IGonzagoSystem* system = GetGonzagoSystem();
    if (!system)
        return;
    GonzagoDesc desc = { 0xba8f3430, 0x00b1b104, 0x021407ee, 0 };
    IGonzagoSubsystem* subsystem = 0;
    system->CreateSubsystem(&subsystem, &desc, 0, 0, 0, 0);
    if (!subsystem)
        return;
    subsystem->AddRef();
    for (int i = 0; i < 5; ++i) {
        void** list = 0;
        int count = 0;
        if (GetChannelList(subsystem, kGonzagoParams[i], &list, &count)) {
            for (int j = 0; j < count; ++j) {
                uint32_t key = (uint32_t)list[j];
                ChannelNode* node = mChannels[i].FindNode(key);
                if (!node)
                    node = mChannels[i].InsertNode(key);
                node->mRefCount = 0;
            }
        }
    }
    subsystem->Release();
}
}}  // namespace SP::Audio
