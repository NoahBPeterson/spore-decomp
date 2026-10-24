// Slice s00eaa9a0: SP::Audio::cMixModeManager::Init (0x00EAA9A0, 2241 bytes, __thiscall, no args)
//
// Fills three global sorted message-key -> mix-mode-id maps (0x016c7144 / 0x016c715c /
// 0x016c7174; 11 + 6 + 42 entries), registers the manager as a message handler for 0x35 ids,
// registers the mix-mode resource factory, then loads every mix-mode record key from the
// resource manager and creates one cMixMode per key into mModes (hash_map<uint, AutoRefCount>)
// unless the id already exists. Returns true.
// Build flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast, no /EHsc (as the sibling HandleMessage).
#include "types.h"

#pragma warning(disable: 4100)

namespace SP { namespace Audio {

struct ResourceKey { uint32_t instanceID, typeID, groupID; };

class cMixMode { public:
    virtual void AddRef();                              // +0
    virtual void Release();                             // +4
    uint32_t pad[0x1c];
    cMixMode(ResourceKey key, void* mgr);               // 0x00ea9320 (ret 0x10: key by value + manager)
    static void* operator new(size_t sz, const char* name, int a, int b, int c, int d);  // 0x00f473a0
};

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

struct ModeNode {
    uint32_t first;
    AutoRefCount<cMixMode> second;
    ModeNode* mpNext;
};

struct ModeIterator {
    ModeNode* mpNode;
    ModeNode** mpBucket;
    ModeIterator(ModeNode* node, ModeNode** bucket) : mpNode(node), mpBucket(bucket) {}
    ModeIterator(ModeNode** bucket) : mpNode(*bucket), mpBucket(bucket) {}
    ModeIterator(const ModeIterator& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
};
inline bool operator==(const ModeIterator& a, const ModeIterator& b) { return a.mpNode == b.mpNode; }

// eastl::hash_map<unsigned int, AutoRefCount<cMixMode>>
struct ModeHashMap {
    uint32_t mRehashPolicy;
    ModeNode** mpBucketArray;                           // +0x04
    uint32_t mnBucketCount;                             // +0x08
    uint32_t mnElementCount;
    char mAllocator[0x10];
    AutoRefCount<cMixMode>& operator[](const uint32_t& key);   // 0x00b6ff20
    ModeIterator end() { return ModeIterator(mpBucketArray + mnBucketCount); }
    ModeIterator find(const uint32_t& key) {
        uint32_t n = mnBucketCount;
        ModeNode** bucket = mpBucketArray + key % n;
        for (ModeNode* node = *bucket; node; node = node->mpNext)
            if (key == node->first)
                return ModeIterator(node, bucket);
        return ModeIterator(mpBucketArray + n);
    }
};

// eastl::vector_map<uint32_t, uint32_t>
struct MessageModeMap {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity;
    uint32_t mAllocator[2];
    uint32_t& operator[](const uint32_t& key);          // 0x00eaa910 (ret 4)
};
extern MessageModeMap sMessageModes1;                   // 0x016c7144
extern MessageModeMap sMessageModes2;                   // 0x016c715c
extern MessageModeMap sMessageModes3;                   // 0x016c7174

struct IKeyFilter {
    virtual bool IsValid(const ResourceKey& key);
    virtual void Other();
};
struct cMixModeFilter : IKeyFilter {                    // vtable 0x014880a8
    cMixModeFilter() {}
};

struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual uint32_t GetRecordKeyList(ResourceKey** dst, IKeyFilter* filter, void* dbs);   // +0x38
    virtual void v3c(); virtual void v40();
    virtual bool RegisterFactory(bool add, void* factory, uint32_t arg);                   // +0x44
};
IResourceManager* GetManager();                         // 0x0067dcd0

struct cAudioSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void AddMixMode(cMixMode* mode);            // +0x18
    virtual void v1c();                                 // +0x1c
    virtual void* CreateAudioObject();                  // +0x20
};
cAudioSystem* GetSystemAT();                            // 0x00a206f0

struct IMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual void AddHandler(void* handler, uint32_t id);   // +0x24
};
IMessageServer* GetServer();                            // 0x00883860

struct ZoneObject {
    static void* operator new(size_t sz, const char* name, int a, int b, int c, int d);  // 0x00926020
};
struct cFactoryBase : ZoneObject { cFactoryBase(); virtual ~cFactoryBase(); };   // 0x00a19d60
struct cFactoryMixMode : cFactoryBase {                 // vtable 0x014880b0
    cFactoryMixMode() {}
    uint32_t pad[(0x70 - 4) / 4];
};

void __cdecl operator_delete_array(void* p);                                                    // 0x00f47380

extern const uint32_t kHandlerIds[0x35];                // 0x01488108

struct AutoHandler {
    IMessageServer* mpServer;
    void* mpHandler;
    const uint32_t* mpIdArray;
    uint32_t mnIdArrayCount;
    uint32_t mnPriority;
};

class cMixModeManager {
public:
    bool Init();
    cMixMode* CreateMode(const ResourceKey& key);

    char pad00[0xc];
    ModeHashMap mModes;                                 // +0x0c
    char pad2c[0x4c - 0x2c];
    AutoHandler mAutoHandler;                           // +0x4c
    uint32_t mCurrentContext;                           // +0x60
};

struct __declspec(align(8)) KeyVector {
    ResourceKey* mpBegin; ResourceKey* mpEnd; ResourceKey* mpCapacity;
    KeyVector() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~KeyVector() {
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            operator_delete_array(mpBegin);
    }
};

bool cMixModeManager::Init()
{
    uint32_t key;
    sMessageModes1[0xdbdba1] = 0xdd4d5cd8;
    sMessageModes1[0x2ccd1d2] = 0xf9fe9926;
    sMessageModes1[0x42b4372] = 0xf9fe9926;
    sMessageModes1[0x36af998] = 0xf90da250;
    sMessageModes1[0x36c4f0a] = 0x6ed85c78;
    sMessageModes1[0x1654c00] = 0x6973a63d;
    sMessageModes1[0x1654c01] = 0xc676ce3e;
    sMessageModes1[0x1654c02] = 0xa8720d1b;
    sMessageModes1[0x1654c04] = 0xd5a6e8bd;
    sMessageModes1[0x1654c05] = 0x69676f4d;
    sMessageModes1[0x1654c10] = 0xa7cf8068;

    sMessageModes2[0x1654c00] = 0x6faded13;
    sMessageModes2[0x1654c01] = 0x1db6d6cc;
    sMessageModes2[0x1654c02] = 0x52dd00c1;
    sMessageModes2[0x1654c04] = 0xdbe12f93;
    sMessageModes2[0x1654c05] = 0x6fa34923;
    sMessageModes2[0x1654c10] = 0xff07ec0d;

    sMessageModes3[0x3615a30b] = 0x2da9fa8;
    sMessageModes3[0x1d2ec0a4] = 0x2da9fa8;
    sMessageModes3[0x1d2ec0a5] = 0x2da9fa8;
    sMessageModes3[0x1d2ec0a6] = 0x2da9fa8;
    sMessageModes3[0x1d2ec0a7] = 0x2da9fa8;
    sMessageModes3[0x1d2ec0a0] = 0x2da9fa8;
    sMessageModes3[0xef18a560] = 0x2da9fa8;
    sMessageModes3[0xe46c381e] = 0xc2a252bb;
    sMessageModes3[0xfd4902bd] = 0xc2a252bb;
    sMessageModes3[0x465c50ba] = 0xc2a252bb;
    sMessageModes3[0x312e9d6a] = 0xc2a252bb;
    sMessageModes3[0x281f5960] = 0xc2a252bb;
    sMessageModes3[0x290adace] = 0xc2a252bb;
    sMessageModes3[0x465c50ba] = 0xc2a252bb;
    sMessageModes3[0x5bf8f774] = 0xc2a252bb;
    sMessageModes3[0xb7af8ff8] = 0xc2a252bb;
    sMessageModes3[0x156276d1] = 0x166e3272;
    sMessageModes3[0x247e2615] = 0x166e3272;
    sMessageModes3[0x9adf00a9] = 0x5691e628;
    sMessageModes3[0xd817cd63] = 0x5691e628;
    sMessageModes3[0x99e92f05] = 0x5691e628;
    sMessageModes3[0x4e3f7777] = 0x5691e628;
    sMessageModes3[0xbdd15f3d] = 0x5691e628;
    sMessageModes3[0x8707be7d] = 0x5691e628;
    sMessageModes3[0x72c49181] = 0x5691e628;
    sMessageModes3[0x99f87089] = 0x5691e628;
    sMessageModes3[0x7d433fad] = 0x5691e628;
    sMessageModes3[0x8f963dcb] = 0x5691e628;
    sMessageModes3[0x441cd3e6] = 0x5691e628;
    sMessageModes3[0x9ad7d4aa] = 0x5691e628;
    sMessageModes3[0x1f2a25b6] = 0x5691e628;
    sMessageModes3[0x449c040f] = 0x5691e628;
    sMessageModes3[0xf670aa43] = 0x5691e628;
    sMessageModes3[0x2a5147a9] = 0x5691e628;
    sMessageModes3[0x1a4e0708] = 0x5691e628;
    sMessageModes3[0xc0b74287] = 0x5691e628;
    sMessageModes3[0xbc1041e6] = 0x9e189fb8;
    sMessageModes3[0xc15695da] = 0x9e189fb8;
    sMessageModes3[0x2090a11b] = 0x9e189fb8;
    sMessageModes3[0x37e82da1] = 0x9e189fb8;
    sMessageModes3[0xa56567f7] = 0x9e189fb8;
    sMessageModes3[0x96b24187] = 0x9e189fb8;

    IMessageServer* server = GetServer();
    mAutoHandler.mpServer = server;
    mAutoHandler.mpHandler = this;
    mAutoHandler.mpIdArray = kHandlerIds;
    mAutoHandler.mnIdArrayCount = 0x35;
    mAutoHandler.mnPriority = 0;
    if (server && this) {
        for (uint32_t i = 0; i < 0xd4; i += 4)
            server->AddHandler(this, *(const uint32_t*)((const char*)kHandlerIds + i));
    }

    cFactoryMixMode* factory = new ("Audio", 0, 0, 0, 0) cFactoryMixMode;
    GetManager()->RegisterFactory(true, factory, 0);

    KeyVector keys;
    cMixModeFilter filter;
    GetManager()->GetRecordKeyList(&keys.mpBegin, &filter, 0);
    cAudioSystem* audio = GetSystemAT();
    ModeHashMap& modes = mModes;
    ResourceKey* last = keys.mpEnd;
    for (ResourceKey* it = keys.mpBegin; it != last; ++it) {
        cMixMode* mode = new ("Audio", 0, 0, 0, 0) cMixMode(*it, this);
        if (mode)
            mode->AddRef();
        if (modes.find(it->instanceID) == modes.end()) {
            modes[it->instanceID] = mode;
            audio->AddMixMode(mode);
        }
        if (mode)
            mode->Release();
    }
    return true;
}

// ---------------------------------------------------------------------------------------------------
// NPC city music runtime (the vtable at 0x01488224) and its five-channel manager.
// ---------------------------------------------------------------------------------------------------

struct Vector3 { float x, y, z; };

struct ChannelNode {
    uint32_t mKey;                  // +0x00
    int32_t mRefCount;              // +0x04
    ChannelNode* mpNext;            // +0x08
};

struct RandomState {
    uint32_t mState;                // +0x00
    uint32_t Range(uint32_t count); // 0x00a68fb0
};

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

struct IGonzagoSubsystem {
    virtual void AddRef();
    virtual void Release();
};

struct GonzagoDesc {
    uint32_t mField0, mField1, mField2, mField3;
};

struct IGonzagoSystem {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void CreateSubsystem(IGonzagoSubsystem** out, const GonzagoDesc* desc,
                                 int a, int b, int c, int d);   // +0x0c
};

struct GonzagoController {
    void Activate(uint32_t subsystem, int a, int b);   // 0x00c8b130
    void SetFade(int a, float value);                  // 0x00c88a00
    void SetVolume(int a, float value);                // 0x00c8a020
    void Deactivate(int a, int b);                     // 0x00c8ad30
    char mData[0x64];
};

class cNPCCityMusicManager;

IGonzagoSystem* GetGonzagoSystem();                    // 0x008de1a0
cNPCCityMusicManager* GetMusicManager();               // 0x00b3d500
bool __cdecl GetChannelList(IGonzagoSubsystem* sub, float param, void*** list, int* count);  // 0x006a0840

extern const float kGonzagoParams[5];                  // 0x01488284
extern const float kGonzagoOne;                        // 0x013ef548
extern const float kGonzagoZero;                       // 0x014882b8
extern const char kMusicNamePrefix[];                  // 0x01a80d26
extern const char kMusicNameSuffix[];                  // 0x015a9018

struct MusicNameBuffer {
    char mData[0xa14];
    void Init(const void* owner, const char* a, const char* b);   // 0x00692f90
    bool Parse(const char* name);                                 // 0x00693e10
};

void __cdecl UpdateAudioPosition(void* handle, void* object, float x, float y, float z);  // 0x00571f80
void __cdecl ReleaseAudioObject(void* object, int flags);                        // 0x00572020
void __cdecl SetAudioObjectEnabled(void* object, uint8_t enabled);               // 0x00a37290
void __cdecl SetAudioVector(void* object, float x, float y, float z);            // 0x009fbc50

class cNPCCityMusic {
public:
    cNPCCityMusic();                                    // 0x00eab4a0
    explicit cNPCCityMusic(uint32_t id);                // 0x00eab410
    cNPCCityMusic* Destroy(int flags);                  // 0x00eab4d0
    bool Load(const char* name);                        // 0x00eab2e0
    void SetPosition(const Vector3* position);          // 0x00eab340
    void ClearPosition();                               // 0x00eab390
    void SetEnabled(uint8_t enabled);                   // 0x00eab3b0
    void SetVector(const Vector3* value);               // 0x00eab3e0
    void SetGonzagoEnabled(bool enabled);               // 0x00eab860

    void* mpVtable0;                    // +0x00
    void* volatile mpVtable1;           // +0x04
    uint32_t mField08;                  // +0x08
    uint32_t mId;                       // +0x0c
    void* mHandle;                      // +0x10
    void* mpAudioObject;                // +0x14
    uint8_t mEnabled;                   // +0x18
    char pad19[0x34 - 0x19];            // +0x19
    GonzagoController mGonzago;         // +0x34
    float mGonzagoVolume;               // +0x98
    char pad9c[0x126 - 0x9c];           // +0x9c
    uint8_t mGonzagoActive;             // +0x126
    char pad127[0x12c - 0x127];         // +0x127
    float mGonzagoFade;                 // +0x12c
    float mGonzagoScale;                // +0x130
    char pad134[0x1a4 - 0x134];         // +0x134
    uint32_t mGonzagoSubsystem;         // +0x1a4
};

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

ChannelNode* ChannelMap::FindNode(uint32_t key) {
    if (!mnBucketCount)
        return 0;
    ChannelNode* node = mpBucketArray[key % mnBucketCount];
    while (node && node->mKey != key)
        node = node->mpNext;
    return node;
}

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

// @ 0x00eab2e0
bool cNPCCityMusic::Load(const char* name) {
    MusicNameBuffer buffer;
    buffer.Init(this, kMusicNameSuffix, kMusicNamePrefix);
    bool ok = buffer.Parse(name);
    if (ok)
        GetMusicManager()->AddChannelRef(mId, mHandle);
    return ok;
}

// @ 0x00eab340
void cNPCCityMusic::SetPosition(const Vector3* position) {
    cAudioSystem* system = GetSystemAT();
    void* object = system ? system->CreateAudioObject() : 0;
    mpAudioObject = object;
    UpdateAudioPosition(mHandle, object, position->x, position->y, position->z);
}

// @ 0x00eab390
void cNPCCityMusic::ClearPosition() {
    if (mpAudioObject) {
        ReleaseAudioObject(mpAudioObject, 0);
        mpAudioObject = 0;
    }
}

// @ 0x00eab3b0
void cNPCCityMusic::SetEnabled(uint8_t enabled) {
    if (mpAudioObject && mEnabled != enabled) {
        SetAudioObjectEnabled(mpAudioObject, enabled);
        mEnabled = enabled;
    }
}

// @ 0x00eab3e0
void cNPCCityMusic::SetVector(const Vector3* value) {
    if (mpAudioObject)
        SetAudioVector(mpAudioObject, value->x, value->y, value->z);
}

// @ 0x00eab410
cNPCCityMusic::cNPCCityMusic(uint32_t id) {
    mpVtable1 = (void*)0x13ec458;
    mField08 = 0;
    mpVtable0 = (void*)0x1488224;
    mpVtable1 = (void*)0x1488214;
    mId = id;
    mHandle = 0;
    mpAudioObject = 0;
    mEnabled = 0;
    mHandle = GetMusicManager()->AcquireChannel(id);
}

// @ 0x00eab4a0
cNPCCityMusic::cNPCCityMusic() {
    mpVtable1 = (void*)0x13ec458;
    mField08 = 0;
    mpVtable0 = (void*)0x1488224;
    mpVtable1 = (void*)0x1488214;
    mId = 0xffffffff;
    mHandle = 0;
    mpAudioObject = 0;
    mEnabled = 0;
}

// @ 0x00eab4d0
cNPCCityMusic* cNPCCityMusic::Destroy(int flags) {
    mpVtable0 = (void*)0x1488224;
    mpVtable1 = (void*)0x1488214;
    cNPCCityMusicManager* manager = GetMusicManager();
    if (manager)
        manager->ReleaseChannel(mId, mHandle);
    mpVtable1 = (void*)0x13ec458;
    mpVtable0 = (void*)0x13eb938;
    if (flags & 1)
        operator_delete_array(this);
    return this;
}

// @ 0x00eab520
void cNPCCityMusicManager::ClearChannelMaps() {
    for (int i = 0; i < 5; ++i) {
        ChannelMap& map = mChannels[i];
        map.FreeNodes(map.mpBucketArray, map.mnBucketCount);
        map.mnElementCount = 0;
    }
}

// @ 0x00eab560
ChannelNode* cNPCCityMusicManager::AcquireChannel(uint32_t id) {
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

// @ 0x00eab650
void cNPCCityMusicManager::AddChannelRef(uint32_t id, void* key) {
    ChannelMap& map = mChannels[id];
    uint32_t value = (uint32_t)key;
    ChannelNode* node = map.FindNode(value);
    if (!node)
        node = map.InsertNode(value);
    ++node->mRefCount;
}

// @ 0x00eab690
void cNPCCityMusicManager::ReleaseChannel(uint32_t id, void* key) {
    ChannelNode* node = mChannels[id].FindNode((uint32_t)key);
    if (node && node->mRefCount > 0)
        --node->mRefCount;
}

// @ 0x00eab6e0
void cNPCCityMusicManager::InitGonzagoSubsystem() {
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

// @ 0x00eab860
void cNPCCityMusic::SetGonzagoEnabled(bool enabled) {
    if (enabled) {
        if (mGonzagoActive)
            return;
        if (mGonzagoFade == kGonzagoZero)
            return;
        mGonzagoActive = 1;
        mGonzago.Activate(mGonzagoSubsystem, 0, 1);
        mGonzago.SetFade(1, kGonzagoOne);
        mGonzago.SetVolume(1, mGonzagoScale * mGonzagoVolume);
    } else {
        if (!mGonzagoActive)
            return;
        mGonzagoActive = 0;
        mGonzago.Deactivate(1, 0);
    }
}

} }
