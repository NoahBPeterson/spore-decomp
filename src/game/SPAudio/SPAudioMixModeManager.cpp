// src/game/SPAudio/SPAudioMixModeManager.cpp -- migrated from slice(s) s00eaa9a0, s00ea9dd0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioMixModeManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Audio/cMixMode.h"
#include "SP/Audio/cMixModeManager.h"
#include "EA/Messaging/AutoHandler.h"
#include "EA/Allocator/ZoneObject.h"
#pragma warning(disable: 4100)

// ---- items of slice s00ea9dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
namespace Audio {
struct cMixMode_s00ea_9dd0 {
    void Start();                                       // 0x00ea8f90 (cMixMode::Start)
};
}
}
namespace SP {
namespace Audio {
template <class T> struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
};
}
}
namespace SP {
namespace Audio {
struct ModeNode {
    uint32_t first;
    AutoRefCount<cMixMode_s00ea_9dd0> second;
    ModeNode* mpNext;
};
}
}
namespace SP {
namespace Audio {
struct ModeIterator {
    ModeNode* mpNode;
    ModeNode** mpBucket;
    ModeNode* operator->() const { return mpNode; }
};
}
}
namespace SP {
namespace Audio {
struct ModeHashMap {
    uint32_t mRehashPolicy;
    ModeNode** mpBucketArray;                           // +0x04
    uint32_t mnBucketCount;                             // +0x08
    uint32_t mnElementCount;
    char mAllocator[0x10];
    ModeIterator find(const uint32_t& key) const;       // 0x00645ed0 (ICF-shared hashtable::find)
    ModeNode* end_node() const { return mpBucketArray[mnBucketCount]; }
};
}
}
namespace SP {
namespace Audio {
struct KeyModePair { uint32_t first; uint32_t second; };
}
}
namespace SP {
namespace Audio {
struct MessageModeMap {
    KeyModePair* mpBegin;
    KeyModePair* mpEnd;
    KeyModePair* mpCapacity;
    char mAllocator[0x8];
    KeyModePair* find(const uint32_t& key);             // 0x00ea9bb0
    KeyModePair* end() const { return mpEnd; }
};
}
}
namespace SP {
namespace Audio {
extern MessageModeMap sMessageModes1;                   // 0x016c7144
}
}
namespace SP {
namespace Audio {
extern MessageModeMap sMessageModes2;                   // 0x016c715c
}
}
namespace SP {
namespace Audio {
extern MessageModeMap sMessageModes3;                   // 0x016c7174
}
}
namespace SP {
namespace Audio {
struct cAudioSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void SetPause(float value);                 // +0x18
};
}
}
namespace SP {
namespace Audio {
struct cGameStateD0 { char pad[0xd0]; int mValueD0; };
}
}
namespace SP {
namespace Audio {
extern cGameStateD0* gGameState16c7aa4;                 // 0x016c7aa4
}
}
namespace SP {
Audio::cAudioSystem* AudioSystem();                     // 0x0067cb00 (SP::AudioSystem)
}
namespace SP {
namespace Audio {
class cMixModeManager_s00ea_9dd0 {
public:
    virtual bool HandleMessage(uint32_t messageID, void* pMessage);  // 0x00ea9dd0 (SP::Audio::cMixModeManager::HandleMessage)
    void StartMixMode(uint32_t id);                     // 0x00ea9a40
    void StopMixMode(uint32_t id, bool flag);           // 0x00ea9a80
    bool IsMixModeActive(uint32_t id);                  // 0x00ea9ac0

    char pad04[0x8];
    ModeHashMap mModes;                                 // +0x0c
    char pad2c[0x60 - 0x2c];
    uint32_t mCurrentContext;                           // +0x60
    uint32_t mCurrentPauseElements;                     // +0x64
    bool mbFlag68;                                      // +0x68 (retail only)
};
}
}
// ---- items of slice s00ea9dd0 end

// ---- items of slice s00eaa9a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
namespace Audio {
struct ResourceKey { uint32_t instanceID, typeID, groupID; };
}
}
namespace SP {
namespace Audio {
struct cMixMode_s00ea_a9a0 {
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
template <class T> struct AutoRefCount_s00ea_a9a0 {
    T* mpObject;
    AutoRefCount_s00ea_a9a0& operator=(T* p) {
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
struct ModeNode_s00ea_a9a0 {
    uint32_t first;
    AutoRefCount_s00ea_a9a0<cMixMode_s00ea_a9a0> second;
    ModeNode_s00ea_a9a0* mpNext;
};
}
}
namespace SP {
namespace Audio {
struct ModeIterator_s00ea_a9a0 {
    ModeNode_s00ea_a9a0* mpNode;
    ModeNode_s00ea_a9a0** mpBucket;
    ModeIterator_s00ea_a9a0(ModeNode_s00ea_a9a0* node, ModeNode_s00ea_a9a0** bucket) : mpNode(node), mpBucket(bucket) {}
    ModeIterator_s00ea_a9a0(ModeNode_s00ea_a9a0** bucket) : mpNode(*bucket), mpBucket(bucket) {}
    ModeIterator_s00ea_a9a0(const ModeIterator_s00ea_a9a0& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
};
}
}
namespace SP {
namespace Audio {
inline bool operator==(const ModeIterator_s00ea_a9a0& a, const ModeIterator_s00ea_a9a0& b) { return a.mpNode == b.mpNode; }
}
}
namespace SP {
namespace Audio {
struct ModeHashMap_s00ea_a9a0 {
    uint32_t mRehashPolicy;
    ModeNode_s00ea_a9a0** mpBucketArray;                           // +0x04
    uint32_t mnBucketCount;                             // +0x08
    uint32_t mnElementCount;
    char mAllocator[0x10];
    AutoRefCount_s00ea_a9a0<cMixMode_s00ea_a9a0>& operator[](const uint32_t& key);   // 0x00b6ff20
    ModeIterator_s00ea_a9a0 end() { return ModeIterator_s00ea_a9a0(mpBucketArray + mnBucketCount); }
    ModeIterator_s00ea_a9a0 find(const uint32_t& key) {
        uint32_t n = mnBucketCount;
        ModeNode_s00ea_a9a0** bucket = mpBucketArray + key % n;
        for (ModeNode_s00ea_a9a0* node = *bucket; node; node = node->mpNext)
            if (key == node->first)
                return ModeIterator_s00ea_a9a0(node, bucket);
        return ModeIterator_s00ea_a9a0(mpBucketArray + n);
    }
};
}
}
namespace SP {
namespace Audio {
struct MessageModeMap_s00ea_a9a0 {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity;
    uint32_t mAllocator[2];
    uint32_t& operator[](const uint32_t& key);          // 0x00eaa910 (ret 4)
};
}
}
namespace SP {
namespace Audio {
extern MessageModeMap_s00ea_a9a0 sMessageModes1_s00ea_a9a0;                   // 0x016c7144
}
}
namespace SP {
namespace Audio {
extern MessageModeMap_s00ea_a9a0 sMessageModes2_s00ea_a9a0;                   // 0x016c715c
}
}
namespace SP {
namespace Audio {
extern MessageModeMap_s00ea_a9a0 sMessageModes3_s00ea_a9a0;                   // 0x016c7174
}
}
namespace SP {
namespace Audio {
struct IKeyFilter {
    virtual bool IsValid(const ResourceKey& key);
    virtual void Other();
};
}
}
namespace SP {
namespace Audio {
struct cMixModeFilter : IKeyFilter {                    // vtable 0x014880a8
    cMixModeFilter() {}
};
}
}
namespace SP {
namespace Audio {
struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual uint32_t GetRecordKeyList(ResourceKey** dst, IKeyFilter* filter, void* dbs);   // +0x38
    virtual void v3c(); virtual void v40();
    virtual bool RegisterFactory(bool add, void* factory, uint32_t arg);                   // +0x44
};
}
}
namespace SP {
namespace Audio {
IResourceManager* GetManager();                         // 0x0067dcd0
}
}
namespace SP {
namespace Audio {
struct cAudioSystem_s00ea_a9a0 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void AddMixMode(cMixMode_s00ea_a9a0* mode);            // +0x18
};
}
}
namespace SP {
namespace Audio {
cAudioSystem_s00ea_a9a0* GetSystemAT();                            // 0x00a206f0
}
}
namespace SP {
namespace Audio {
struct IMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual void AddHandler(void* handler, uint32_t id);   // +0x24
};
}
}
namespace SP {
namespace Audio {
IMessageServer* GetServer();                            // 0x00883860
}
}
namespace SP {
namespace Audio {
struct ZoneObject {
    static void* operator new(size_t sz, const char* name, int a, int b, int c, int d);  // 0x00926020
};
}
}
namespace SP {
namespace Audio {
struct cFactoryBase : ZoneObject { cFactoryBase(); virtual ~cFactoryBase(); };   // 0x00a19d60
}
}
namespace SP {
namespace Audio {
struct cFactoryMixMode : cFactoryBase {                 // vtable 0x014880b0
    cFactoryMixMode() {}
    uint32_t pad[(0x70 - 4) / 4];
};
}
}
namespace SP {
namespace Audio {
void __cdecl operator_delete_array(void* p);                                                    // 0x00f47380
}
}
namespace SP {
namespace Audio {
extern const uint32_t kHandlerIds[0x35];                // 0x01488108
}
}
namespace SP {
namespace Audio {
struct AutoHandler {
    IMessageServer* mpServer;
    void* mpHandler;
    const uint32_t* mpIdArray;
    uint32_t mnIdArrayCount;
    uint32_t mnPriority;
};
}
}
namespace SP {
namespace Audio {
class cMixModeManager_s00ea_a9a0 {
public:
    bool Init();  // 0x00eaa9a0 (SP::Audio::cMixModeManager::Init)
    cMixMode_s00ea_a9a0* CreateMode(const ResourceKey& key);

    char pad00[0xc];
    ModeHashMap_s00ea_a9a0 mModes;                                 // +0x0c
    char pad2c[0x4c - 0x2c];
    AutoHandler mAutoHandler;                           // +0x4c
    uint32_t mCurrentContext;                           // +0x60
};
}
}
namespace SP {
namespace Audio {
struct __declspec(align(8)) KeyVector {
    ResourceKey* mpBegin; ResourceKey* mpEnd; ResourceKey* mpCapacity;
    KeyVector() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~KeyVector() {
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            operator_delete_array(mpBegin);
    }
};
}
}
// ---- items of slice s00eaa9a0 end

// @ 0x00ea9dd0
namespace SP { namespace Audio {
bool cMixModeManager_s00ea_9dd0::HandleMessage(uint32_t messageID, void* pMessage)
{
    uint32_t* msg = (uint32_t*)pMessage;
    switch (messageID) {
    case 0x238de9c:
        StopMixMode(0xcc2efa4a, false);
        return true;
    case 0x22d1adc: {
        StopMixMode(0x3ed3bf9, false);
        uint32_t key = msg[2];
        KeyModePair* it = sMessageModes1.find(key);
        if (it == sMessageModes1.end())
            return true;
        uint32_t mode = it->second;
        if (mbFlag68 || key != 0x2ccd1d2 || mode != 0xf9fe9926)
            StartMixMode(mode);
        if (mode == 0xa7cf8068) {
            if (!gGameState16c7aa4)
                return true;
            if (gGameState16c7aa4->mValueD0 == 0) {
                if (IsMixModeActive(0x2d329d5f))
                    StopMixMode(0x2d329d5f, false);
                StartMixMode(0x1a27f146);
            }
            else {
                if (IsMixModeActive(0x1a27f146))
                    StopMixMode(0x1a27f146, false);
                StartMixMode(0x2d329d5f);
            }
            return true;
        }
        if (IsMixModeActive(0x2d329d5f))
            StopMixMode(0x2d329d5f, false);
        if (IsMixModeActive(0x1a27f146))
            StopMixMode(0x1a27f146, false);
        return true;
    }
    case 0x212d3e7: {
        uint32_t key = msg[4];
        KeyModePair* it = sMessageModes1.find(key);
        if (it != sMessageModes1.end()) {
            uint32_t mode = it->second;
            StopMixMode(mode, false);
            if (mode == 0x69676f4d)
                StopMixMode(mCurrentContext, false);
        }
        StartMixMode(0x3ed3bf9);
        AudioSystem()->SetPause(0.0f);
        return true;
    }
    case 0x248975f:
        StopMixMode(mCurrentContext, false);
        StartMixMode(0xc2b96aae);
        mCurrentContext = 0xc2b96aae;
        return true;
    case 0x248976a:
        StopMixMode(mCurrentContext, false);
        StartMixMode(0xd69af078);
        mCurrentContext = 0xd69af078;
        return true;
    case 0x2489766:
        StopMixMode(mCurrentContext, false);
        StartMixMode(0x79e526cb);
        mCurrentContext = 0x79e526cb;
        return true;
    case 0x3867294:
        if (pMessage)
            StartMixMode(0xa1638df0);
        else
            StopMixMode(0xa1638df0, false);
        return true;
    case 0x3e9a620:
        StartMixMode(0xf8bfa142);
        return true;
    case 0x3ac86ad:
        StartMixMode(0x2a04d2ef);
        return true;
    case 0x3e9a625:
        StopMixMode(0xf8bfa142, false);
        return true;
    case 0x47d2b68: {
        uint32_t key = msg[0];
        KeyModePair* it = sMessageModes2.find(key);
        if (it != sMessageModes2.end())
            StopMixMode(it->second, false);
        StopMixMode(0xc3b6e28f, false);
        return true;
    }
    case 0x4471c60:
        StopMixMode(0x38432c22, false);
        return true;
    case 0x47d7cc5:
        StartMixMode(0xed1b527e);
        return true;
    case 0x49731a9:
        StartMixMode(0x321723de);
        return true;
    case 0x490a868: {
        StartMixMode(0xc3b6e28f);
        uint32_t key = msg[0];
        KeyModePair* it = sMessageModes2.find(key);
        if (it != sMessageModes2.end())
            StartMixMode(it->second);
        return true;
    }
    case 0x47d7cc6:
        StopMixMode(0xed1b527e, false);
        return true;
    case 0x49731ad:
        StopMixMode(0x321723de, false);
        return true;
    case 0x4a07018:
        StartMixMode(0x38432c22);
        return true;
    case 0x49790b2:
        StartMixMode(0xcc2efa4a);
        return true;
    case 0x4c7032b:
        StartMixMode(0x41601d81);
        return true;
    case 0x4c70cc0:
        StartMixMode(0xb667073e);
        return true;
    case 0x4c703a5:
        StopMixMode(0x41601d81, false);
        return true;
    case 0x4c70ce5:
        StopMixMode(0xb667073e, false);
        return true;
    case 0x4fd2bd3:
        StopMixMode(0xb6755dd6, false);
        return true;
    case 0x4fd2bce:
        StartMixMode(0xb6755dd6);
        return true;
    case 0x539a4ce: {
        ModeIterator it = mModes.find(0xe50be14b);
        if (it.mpNode != mModes.end_node())
            it->second->Start();
        return true;
    }
    case 0x5b07bda:
        StartMixMode(0x47395ae5);
        return true;
    case 0x546bbb8:
        if (pMessage)
            StartMixMode(0x1dfbe8cc);
        else
            StopMixMode(0x1dfbe8cc, false);
        return true;
    case 0x539a4cf:
        StopMixMode(0xe50be14b, false);
        return true;
    case 0x5b07be5:
        StopMixMode(0x47395ae5, false);
        return true;
    case 0x5c81b25:
        StopMixMode(0xdf1030f7, false);
        return true;
    case 0x5c81b19:
        StartMixMode(0xdf1030f7);
        return true;
    case 0x5e902d3:
        StopMixMode(0xcdde2d78, false);
        return true;
    case 0x604c6e0:
        StartMixMode(0x4bbc71ca);
        return true;
    case 0x604a973:
        StartMixMode(0xcdde2d78);
        return true;
    case 0x604c6f4:
        StopMixMode(0x4bbc71ca, false);
        return true;
    case 0x604d85d:
        StopMixMode(0xf3f05329, false);
        return true;
    case 0x604d856:
        StartMixMode(0xf3f05329);
        return true;
    case 0x60c8707: {
        uint32_t key = msg[2];
        KeyModePair* it = sMessageModes3.find(key);
        if (it != sMessageModes3.end())
            StartMixMode(it->second);
        return true;
    }
    case 0x6202731:
        StopMixMode(0x577eef2b, false);
        StartMixMode(0xcbc1c57);
        return true;
    case 0x61d72de:
        StopMixMode(0x321723de, true);
        return true;
    case 0x60c874f: {
        uint32_t key = msg[2];
        KeyModePair* it = sMessageModes3.find(key);
        if (it != sMessageModes3.end())
            StopMixMode(it->second, false);
        return true;
    }
    case 0x66f8f25:
        StartMixMode(0xf9fe9926);
        mbFlag68 = true;
        return true;
    case 0x695d2ed:
        StartMixMode(0xcbc1c57);
        return true;
    case 0x691a1c3:
        StopMixMode(0xcbc1c57, false);
        StartMixMode(0x577eef2b);
        return true;
    case 0x695d2f5:
        StopMixMode(0xcbc1c57, false);
        return true;
    case 0x74baf67: {
        uint32_t startIndex = msg[2];
        uint32_t stopIndex = msg[4];
        uint32_t modes[3] = { 0x2e1a0bf7, 0x2d329d5f, 0x1fec7fdf };
        if (stopIndex < 3)
            StopMixMode(modes[stopIndex], false);
        if (startIndex < 3)
            StartMixMode(modes[startIndex]);
        return true;
    }
    case 0x3ac86b5:
    case 0x69c3314:
        StopMixMode(0x2a04d2ef, false);
        return true;
    case 0x7c7686f:
        StartMixMode(0xcc2efa4a);
        StartMixMode(0xf9fe9926);
        mbFlag68 = true;
        return true;
    case 0x7e36045:
        if (!pMessage)
            StopMixMode(0xfff641ab, false);
        else
            StopMixMode(0x250fc692, false);
        return true;
    case 0x7e36032:
        if (!pMessage)
            StartMixMode(0xfff641ab);
        else
            StartMixMode(0x250fc692);
        return true;
    }
    return false;
}
}}  // namespace SP::Audio

// @ 0x00eaa9a0
namespace SP { namespace Audio {
bool cMixModeManager_s00ea_a9a0::Init()
{
    uint32_t key;
    sMessageModes1_s00ea_a9a0[0xdbdba1] = 0xdd4d5cd8;
    sMessageModes1_s00ea_a9a0[0x2ccd1d2] = 0xf9fe9926;
    sMessageModes1_s00ea_a9a0[0x42b4372] = 0xf9fe9926;
    sMessageModes1_s00ea_a9a0[0x36af998] = 0xf90da250;
    sMessageModes1_s00ea_a9a0[0x36c4f0a] = 0x6ed85c78;
    sMessageModes1_s00ea_a9a0[0x1654c00] = 0x6973a63d;
    sMessageModes1_s00ea_a9a0[0x1654c01] = 0xc676ce3e;
    sMessageModes1_s00ea_a9a0[0x1654c02] = 0xa8720d1b;
    sMessageModes1_s00ea_a9a0[0x1654c04] = 0xd5a6e8bd;
    sMessageModes1_s00ea_a9a0[0x1654c05] = 0x69676f4d;
    sMessageModes1_s00ea_a9a0[0x1654c10] = 0xa7cf8068;

    sMessageModes2_s00ea_a9a0[0x1654c00] = 0x6faded13;
    sMessageModes2_s00ea_a9a0[0x1654c01] = 0x1db6d6cc;
    sMessageModes2_s00ea_a9a0[0x1654c02] = 0x52dd00c1;
    sMessageModes2_s00ea_a9a0[0x1654c04] = 0xdbe12f93;
    sMessageModes2_s00ea_a9a0[0x1654c05] = 0x6fa34923;
    sMessageModes2_s00ea_a9a0[0x1654c10] = 0xff07ec0d;

    sMessageModes3_s00ea_a9a0[0x3615a30b] = 0x2da9fa8;
    sMessageModes3_s00ea_a9a0[0x1d2ec0a4] = 0x2da9fa8;
    sMessageModes3_s00ea_a9a0[0x1d2ec0a5] = 0x2da9fa8;
    sMessageModes3_s00ea_a9a0[0x1d2ec0a6] = 0x2da9fa8;
    sMessageModes3_s00ea_a9a0[0x1d2ec0a7] = 0x2da9fa8;
    sMessageModes3_s00ea_a9a0[0x1d2ec0a0] = 0x2da9fa8;
    sMessageModes3_s00ea_a9a0[0xef18a560] = 0x2da9fa8;
    sMessageModes3_s00ea_a9a0[0xe46c381e] = 0xc2a252bb;
    sMessageModes3_s00ea_a9a0[0xfd4902bd] = 0xc2a252bb;
    sMessageModes3_s00ea_a9a0[0x465c50ba] = 0xc2a252bb;
    sMessageModes3_s00ea_a9a0[0x312e9d6a] = 0xc2a252bb;
    sMessageModes3_s00ea_a9a0[0x281f5960] = 0xc2a252bb;
    sMessageModes3_s00ea_a9a0[0x290adace] = 0xc2a252bb;
    sMessageModes3_s00ea_a9a0[0x465c50ba] = 0xc2a252bb;
    sMessageModes3_s00ea_a9a0[0x5bf8f774] = 0xc2a252bb;
    sMessageModes3_s00ea_a9a0[0xb7af8ff8] = 0xc2a252bb;
    sMessageModes3_s00ea_a9a0[0x156276d1] = 0x166e3272;
    sMessageModes3_s00ea_a9a0[0x247e2615] = 0x166e3272;
    sMessageModes3_s00ea_a9a0[0x9adf00a9] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0xd817cd63] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0x99e92f05] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0x4e3f7777] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0xbdd15f3d] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0x8707be7d] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0x72c49181] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0x99f87089] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0x7d433fad] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0x8f963dcb] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0x441cd3e6] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0x9ad7d4aa] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0x1f2a25b6] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0x449c040f] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0xf670aa43] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0x2a5147a9] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0x1a4e0708] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0xc0b74287] = 0x5691e628;
    sMessageModes3_s00ea_a9a0[0xbc1041e6] = 0x9e189fb8;
    sMessageModes3_s00ea_a9a0[0xc15695da] = 0x9e189fb8;
    sMessageModes3_s00ea_a9a0[0x2090a11b] = 0x9e189fb8;
    sMessageModes3_s00ea_a9a0[0x37e82da1] = 0x9e189fb8;
    sMessageModes3_s00ea_a9a0[0xa56567f7] = 0x9e189fb8;
    sMessageModes3_s00ea_a9a0[0x96b24187] = 0x9e189fb8;

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
    cAudioSystem_s00ea_a9a0* audio = GetSystemAT();
    ModeHashMap_s00ea_a9a0& modes = mModes;
    ResourceKey* last = keys.mpEnd;
    for (ResourceKey* it = keys.mpBegin; it != last; ++it) {
        cMixMode_s00ea_a9a0* mode = new ("Audio", 0, 0, 0, 0) cMixMode_s00ea_a9a0(*it, this);
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
}}  // namespace SP::Audio
