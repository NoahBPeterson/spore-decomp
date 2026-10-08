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

struct cMixMode {
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

} }
