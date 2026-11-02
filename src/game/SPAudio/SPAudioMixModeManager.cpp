// src/game/SPAudio/SPAudioMixModeManager.cpp -- migrated from slice(s) s00ea8f90, s00eaa9a0, s00ea9dd0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioMixModeManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Audio/cMixMode.h"
#include "SP/Audio/cMixModeManager.h"
#include "EA/Messaging/AutoHandler.h"
#include "EA/Allocator/ZoneObject.h"
#include <string.h>
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

// ---- items of slice s00ea8f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
void* __cdecl  GetSystemAT_s00ea_8f90();                          // 0x00a206f0  EA::Audio::GetSystemAT
void  __cdecl  operator_delete(void*);                 // 0x00f47380
void* __cdecl  LowerBoundPair(void*, void*, void*, unsigned char); // 0x005701b0
void  __cdecl  DoNukeSubtree(void*);                   // 0x009a9600
void  __cdecl  ZoneObject_delete(void*);               // 0x00926060
void  __cdecl  RemoveHandler(void*, void*, void*, void*, void*);   // 0x00571db0
static inline void* VT(void* obj, int off) { return ((void**) (*(void**) obj))[off / 4]; }
typedef void  (__thiscall *Fn0)(void*);
typedef void  (__thiscall *Fn1u)(void*, u32);
typedef void  (__thiscall *Fn2u)(void*, u32, u32);
typedef float (__thiscall *Fnf0)(void*);
namespace SP {
namespace Audio {
class cMixMode_s00ea_8f90;
}
}
namespace SP {
namespace Audio {
class cMixModeManager_s00ea_8f90;
}
}
namespace SP {
namespace Audio {
struct SoundVector {
    u32* mBegin;   // +0x00
    u32* mEnd;     // +0x04
    u32* mCap;     // +0x08
    u32  mAlloc[2];// +0x0c
    void VectorInsert(u32* pos, const u32* value);   // 0x00ea9440
};
}
}
namespace SP {
namespace Audio {
struct ModeNode_s00ea_8f90 {
    u32        first;    // +0x00 key
    cMixMode_s00ea_8f90*  second;   // +0x04 value
    ModeNode_s00ea_8f90*  mpNext;   // +0x08
};
}
}
namespace SP {
namespace Audio {
struct ModeIterator_s00ea_8f90 {
    ModeNode_s00ea_8f90*  mpNode;       // +0x00
    ModeNode_s00ea_8f90** mpBucket;     // +0x04
    ModeIterator_s00ea_8f90() {}        // non-trivial: returned via hidden pointer (as eastl does)
    ModeNode_s00ea_8f90* operator->() const { return mpNode; }
};
}
}
namespace SP {
namespace Audio {
struct ModeMap {                       // 0x20 bytes
    u32         mPolicy;               // +0x00
    ModeNode_s00ea_8f90**  mpBucketArray;         // +0x04
    u32         mnBucketCount;         // +0x08
    u32         mnElementCount;        // +0x0c
    char        mAllocator[0x10];      // +0x10
    ModeIterator_s00ea_8f90 find(const u32& key) const;   // 0x00645ed0 (shared hashtable::find)
    ModeNode_s00ea_8f90* end_node() const { return mpBucketArray[mnBucketCount]; }
    void DoFreeNodes(ModeNode_s00ea_8f90** bucketArray, u32 bucketCount);   // 0x00961d60
};
}
}
namespace SP {
namespace Audio {
struct SoundNode {
    u32        key;            // +0x00
    u32        instanceId;     // +0x04
    u32        refCount;       // +0x08
    float      fSecsSinceStop; // +0x0c
    SoundNode* mpNext;         // +0x10
};
}
}
namespace SP {
namespace Audio {
struct SoundIterator {
    SoundNode*  mpNode;
    SoundNode** mpBucket;
    SoundIterator() {}
    SoundIterator(SoundNode* n, SoundNode** b) : mpNode(n), mpBucket(b) {}
    SoundNode* operator->() const { return mpNode; }
};
}
}
namespace SP {
namespace Audio {
struct SoundMap {                      // 0x20 bytes
    u32          mPolicy;              // +0x00
    SoundNode**  mpBucketArray;        // +0x04
    u32          mnBucketCount;        // +0x08
    u32          mnElementCount;       // +0x0c
    char         mAllocator[0x10];     // +0x10
    SoundIterator find(const u32& key) const;  // 0x00db4780
    SoundNode* end_node() const { return mpBucketArray[mnBucketCount]; }
    SoundIterator erase(SoundIterator it);     // 0x00b4f930
    void insert(SoundIterator* sret, const void* value, u32 flag);  // 0x00ad9370
    void DoFreeNodes(SoundNode** bucketArray, u32 bucketCount);  // 0x007611f0
};
}
}
namespace SP {
namespace Audio {
struct Key { u32 instanceID; u32 typeID; u32 groupID; };
}
}
namespace SP {
namespace Audio {
class cMixMode_s00ea_8f90 {
 public:
    void*    mVtbl0;       // +0x00
    void*    mVtbl1;       // +0x04
    void*    mVtbl2;       // +0x08
    int      m0c;          // +0x0c
    bool     mbDirty;      // +0x10
    char     pad11[3];     // +0x11
    float    mValue;       // +0x14
    void*    mpConfig;     // +0x18
    int      m1c;          // +0x1c
    int      m20;          // +0x20
    cMixModeManager_s00ea_8f90* mManager;  // +0x24
    u32      mKeyInstance; // +0x28
    u32      mKeyType;     // +0x2c
    u32      mKeyGroup;    // +0x30
    SoundVector mA;        // +0x34 (start sounds)
    SoundVector mB;        // +0x48 (pause/instance sounds)
    SoundVector mC;        // +0x5c
    bool     mb70;         // +0x70
    bool     mbRunning;    // +0x71

    cMixMode_s00ea_8f90(cMixModeManager_s00ea_8f90* mgr, Key key);   // 0x00ea9320
    ~cMixMode_s00ea_8f90();                               // 0x00ea93c0
    bool Start();                              // 0x00ea8f90
    bool Stop(bool flag);                      // 0x00ea9260
    bool IsRunning();                          // 0x00ea8ec0 (external)
    void ConfigurePrimitive();                 // 0x00ea9550
};
}
}
namespace SP {
namespace Audio {
class cMixModeManager_s00ea_8f90 {
 public:
    void*    m00;               // +0x00  (vftable 0)
    void*    m04;               // +0x04  (vftable 1)
    int      m08;               // +0x08
    ModeMap  mModes;            // +0x0c
    SoundMap mSounds;           // +0x2c
    void*    mhServer;          // +0x4c
    void*    mhHandler;         // +0x50
    void*    mhIds;             // +0x54
    u32      mhCount;           // +0x58
    int      mhPriority;        // +0x5c
    u32      mCurrentContext;   // +0x60
    u32      mCurrentPauseElements; // +0x64
    bool     mbFlag68;          // +0x68

    void StartMode(u32 id);                     // 0x00ea9a40
    void StopMode(u32 id, bool flag);           // 0x00ea9a80
    bool IsModeActive(u32 id);                  // 0x00ea9ac0
    void RegisterSound(u32 id);                 // 0x00ea9b00
    void RemoveSound(u32 id, bool flag);        // 0x00ea99a0
    void UpdateSounds(float dt);                // 0x00ea9880
    void Shutdown();                            // 0x00ea9c70
};
}
}
namespace SP {
namespace Audio {
struct KeyModePair_s00ea_8f90 { u32 first; u32 second; };
}
}
namespace SP {
namespace Audio {
struct MessageModeMap_s00ea_8f90 {
    KeyModePair_s00ea_8f90* mpBegin;      // +0x00
    KeyModePair_s00ea_8f90* mpEnd;        // +0x04
    KeyModePair_s00ea_8f90* mpCapacity;   // +0x08
    u32          mAlloc[2];    // +0x0c
    char         mFlag14;      // +0x14
    KeyModePair_s00ea_8f90* find(const u32& key) const;   // 0x00ea9bb0
    KeyModePair_s00ea_8f90* end() const { return mpEnd; }
};
}
}
namespace SP {
namespace Audio {
struct MixModeMutex {                 // EA::Thread::Mutex (0x30 bytes)
    char m[0x30];
    void Dtor();                      // 0x00922130  (??1Mutex@Thread@EA@@QAE@XZ)
};
}
}
namespace SP {
namespace Audio {
struct MixModeRbtree {                // rbtree<unsigned int, ...>
    char  m00[0x0c];
    void* mpRoot;                     // +0x0c
    char  m10[0x0c];
    void  DoNukeSubtree(void* node);  // 0x009a9600
};
}
}
namespace SP {
namespace Audio {
class cFactoryMixMode_s00ea_8f90 {
 public:
    void*         mVtbl;         // +0x00
    char          m04[0x0c];     // +0x04
    MixModeMutex  mMutex;        // +0x10
    MixModeRbtree mTree;         // +0x40
    u32*          mpVecBegin;    // +0x5c
    char          m60[0x04];     // +0x60
    u32*          mpVecEnd;      // +0x64

    void* scalar_deleting_destructor(unsigned char flags);   // 0x00ea9c20
};
}
}
namespace SP {
namespace Audio {
 void ConfigureVector(SoundVector* v, void* cfg, u32 id); 
}  // 0x00ea9550 (defined below; used by a stub's inline body)
}
namespace SP {
namespace Audio {
void cMixMode_s00ea_8f90::ConfigurePrimitive()
{
    bool restart = (((Fnf0) VT(this, 0x1c))(this) != 0.0f);
    if (restart)
        Stop(false);

    ConfigureVector(&mA, mpConfig, 0x6c4692b7u);
    ConfigureVector(&mB, mpConfig, 0x4a253755u);
    ConfigureVector(&mC, mpConfig, 0xecdc329du);

    if (restart)
        Start();
}
}
}
// ---- items of slice s00ea8f90 end

// @ 0x00ea9a40
namespace SP { namespace Audio {
void cMixModeManager_s00ea_8f90::StartMode(u32 id)
{
    ModeIterator_s00ea_8f90 it = mModes.find(id);
    if (mModes.end_node() != it.mpNode)
        it.mpNode->second->Start();
}
}}  // namespace SP::Audio

// @ 0x00ea9a80
namespace SP { namespace Audio {
void cMixModeManager_s00ea_8f90::StopMode(u32 id, bool flag)
{
    ModeIterator_s00ea_8f90 it = mModes.find(id);
    if (mModes.end_node() != it.mpNode)
        it.mpNode->second->Stop(flag);
}
}}  // namespace SP::Audio

// @ 0x00ea9ac0
namespace SP { namespace Audio {
bool cMixModeManager_s00ea_8f90::IsModeActive(u32 id)
{
    ModeIterator_s00ea_8f90 it = mModes.find(id);
    if (mModes.end_node() == it.mpNode)
        return false;
    return it.mpNode->second->IsRunning();
}
}}  // namespace SP::Audio

// @ 0x00ea9bb0
namespace SP { namespace Audio {
KeyModePair_s00ea_8f90* MessageModeMap_s00ea_8f90::find(const u32& key) const
{
    KeyModePair_s00ea_8f90* end = mpEnd;
    KeyModePair_s00ea_8f90* it = (KeyModePair_s00ea_8f90*) LowerBoundPair(mpBegin, end, (void*) &key, (unsigned char) mFlag14);
    if (it == end || key < it->first || it == it + 1)
        it = end;
    return it;
}
}}  // namespace SP::Audio

// @ 0x00ea9c20
namespace SP { namespace Audio {
void* cFactoryMixMode_s00ea_8f90::scalar_deleting_destructor(unsigned char flags)
{
    char* b = (char*) mpVecBegin;
    char* e = (char*) mpVecEnd;
    if ((int) (e - b) > 1 && b != 0)
        operator_delete(b);
    void* root = mTree.mpRoot;
    mTree.DoNukeSubtree(root);
    mMutex.Dtor();
    mVtbl = (void*) 0x13effb8;
    if (flags & 1)
        ZoneObject_delete(this);
    return this;
}
}}  // namespace SP::Audio

// @ 0x00ea9c70
namespace SP { namespace Audio {
void cMixModeManager_s00ea_8f90::Shutdown()
{
    // 1) stop every mix mode still registered in mModes
    ModeNode_s00ea_8f90** bucket = mModes.mpBucketArray;
    ModeNode_s00ea_8f90* node = *bucket;
    while (node == 0)
        node = *++bucket;
    ModeNode_s00ea_8f90* last = mModes.mpBucketArray[mModes.mnBucketCount];
    while (node != last) {
        node->second->Stop(false);
        node = node->mpNext;
        while (node == 0)
            node = *++bucket;
    }
    mModes.DoFreeNodes(mModes.mpBucketArray, mModes.mnBucketCount);
    mModes.mnElementCount = 0;

    // 2) tear down every lingering sound instance in mSounds
    SoundNode** sbucket = mSounds.mpBucketArray;
    SoundNode* snode = *sbucket;
    while (snode == 0)
        snode = *++sbucket;
    SoundNode* slast = mSounds.mpBucketArray[mSounds.mnBucketCount];
    while (snode != slast) {
        void* sys = GetSystemAT_s00ea_8f90();
        if (sys != 0) {
            ((Fn1u) VT(sys, 0x38))(sys, 0x347536bu);
            ((Fn2u) VT(sys, 0x40))(sys, 0x3475385u, snode->instanceId);
            ((Fn2u) VT(sys, 0x40))(sys, 0x34753a0u, 0);
            ((Fn0)  VT(sys, 0x58))(sys);
            sys = GetSystemAT_s00ea_8f90();
            if (sys != 0)
                ((Fn1u) VT(sys, 0x2c))(sys, snode->instanceId);
        }
        snode = snode->mpNext;
        while (snode == 0)
            snode = *++sbucket;
    }
    mSounds.DoFreeNodes(mSounds.mpBucketArray, mSounds.mnBucketCount);
    mSounds.mnElementCount = 0;

    // 3) detach the message handler
    if (mhServer != 0) {
        void* server = mhServer;
        mhServer = 0;
        RemoveHandler(server, mhHandler, mhIds, (void*) (size_t) mhCount, (void*) (size_t) mhPriority);
    }
}
}}  // namespace SP::Audio

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
