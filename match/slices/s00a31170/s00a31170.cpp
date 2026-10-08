// Slice s00a31170: SP::Audio::cSystem::InitAT (0x00a31170).
// Audio module, /O2 /MD /Gy /GS- /EHsc /TP /arch:SSE /fp:fast.
//
// Second half of the audio system start-up: registers the three audio factory objects
// with the resource manager, creates the rw::audio::core::System, wires its allocators,
// the file-system/stream-pool plumbing and the emitter constructor, looks the output
// plugins up (DAC mode / sample rate), applies the mute state, seeds the id pools,
// preloads the configuration and finally reads every polyphony table database into
// the polyphony map.
#include "types.h"

#include <intrin.h>

#define V1(n) virtual void n();
#define V4(n) V1(n##a) V1(n##b) V1(n##c) V1(n##d)
#define V16(n) V4(n##a) V4(n##b) V4(n##c) V4(n##d)

void __cdecl operator_delete_array(void* p);                       // 0x00f47380 operator delete[]

struct ResKey { uint32_t instance, type, group; };

// ---------------------------------------------------------------------------
//  small helper types
// ---------------------------------------------------------------------------
struct ListNode {
    ListNode* mpNext;
    ListNode* mpPrev;
    void* mpData;                       // +0x08
};
struct DbList {                         // eastl::list<AutoRefCount<Database>> with an allocator
    ListNode mAnchor;                   // next/prev only used
    void* mpAllocator;                  // +0x08
    uint32_t mFlags;                    // +0x0c
};
struct CoreAlloc {
    virtual void v0();
    virtual void v4();
    virtual void v8();
    virtual void Free(void* p, unsigned size);                              // +0x0c
};
CoreAlloc* __cdecl GetDefaultAllocator();                                   // 0x00925cb0

// eastl::vector<uint8_t, sp_vector_allocator>
struct ByteVec {
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCapacity;
    ByteVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~ByteVec()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete_array(mpBegin);
    }
    void resize(unsigned n);            // 0x004c0410
};

// ref-counted factory object with an atomic reference count at +4
extern void* g_vtRefBase[];             // 0x013effa8
extern void* g_vtFactoryA[];            // 0x01452a44
extern void* g_vtFactoryB[];            // 0x01452a78
extern void* g_vtFactoryC[];            // 0x01452ac0
struct FactoryObj {
    void** vt;
    long ref;
    __forceinline FactoryObj* Init(void** derived)
    {
        vt = g_vtRefBase;
        _InterlockedExchange(&ref, 0);
        vt = derived;
        return this;
    }
};
class IFactory {
public:
    virtual void v0();
    virtual int AddRef();               // +0x04
    virtual int Release();              // +0x08
};

void* __cdecl ZoneAlloc(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00926020
extern const char g_audioName[];        // 0x0140a5a0 "Audio"

// resource objects
class IStream {
public:
    virtual void v0(); virtual void v4(); virtual void v8(); virtual void vc();
    virtual void v10(); virtual void v14();
    virtual void Close();                                   // +0x18
    virtual uint32_t GetSize();                             // +0x1c
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual uint32_t Read(void* buf, uint32_t size);        // +0x30
};
class IResource {
public:
    virtual void v0(); virtual void v4();
    virtual int Release();                                  // +0x08
    virtual void vc(); virtual void v10(); virtual void v14();
    virtual IStream* OpenStream();                          // +0x18
    virtual uint32_t GetTypeID();                           // +0x1c
};
class IDatabase {
public:
    V4(d0) V4(d1) V4(d2) V1(d3)
    virtual bool GetResource(const ResKey* key, IResource** out, int a, int b, int c, int d);   // +0x34
};
class IResourceType {                    // result of the manager's +0x58 lookup
public:
    virtual void v0(); virtual void v4(); virtual void v8();
    virtual uint32_t GetTypeID();                           // +0x0c
};
class IResourceManager {
public:
    V16(m1)
    V1(m40)
    virtual void RegisterFactory(int kind, IFactory* factory, int flags);   // +0x44
    virtual void m48(); virtual void m4c(); virtual void m50(); virtual void m54();
    virtual IResourceType* GetResourceType(const ResKey* key);              // +0x58
    virtual void GetDatabases(DbList* out, const ResKey* key);              // +0x5c
};
IResourceManager* __cdecl GetResourceManager();             // 0x008de1a0 (EA::Audio::Eapd::Debug::ObjectError)

// ---------------------------------------------------------------------------
//  rw::audio::core
// ---------------------------------------------------------------------------
class IPluginParam {
public:
    void SetParam(int index, const void* value);            // 0x0112ccc0 (merged thunk: jmp [vtbl+4])
};
struct VoiceContainer {
    IPluginParam* FindPlugin(uint32_t id);                  // 0x00a34230
};
struct RWSystem {
    uint32_t pad[0xa8 / 4];
    void* mpCallback;                                       // +0xa8
    void SetCallback(void* fn);                             // 0x0112c870
    void AddPlugin(IPluginParam* p);                        // 0x009879d0
};
struct StreamPool;
RWSystem* __cdecl CreateInstance(void* allocator, uint32_t size);                      // 0x0112c9e0
StreamPool* __cdecl ReleaseHandler(uint32_t id, uint32_t a, uint32_t b, uint32_t c,
                                   RWSystem* rw, void* allocator, int d);              // 0x0112e290

struct FsParams {
    void* mpChannel;
    void* mpAllocator2;
    uint32_t mA;
    uint32_t mB;
    FsParams();                                             // 0x011e64c0
};
void __cdecl FsInit(FsParams* p);                           // 0x011e5cd0
struct FsManager {
    void SetDriver(void* driver, int a);                    // 0x011e59b0
};
FsManager* __cdecl GetFsManager();                          // 0x011e58f0
extern int g_FsAllocatorManager;                            // 0x016f4b10

struct AudioLock {                      // global mutex wrapper (thiscall, ecx = lock)
    void Lock();                        // 0x0112c600
    void Unlock();                      // 0x0112c620
};
extern AudioLock* g_pAudioLock;         // 0x016e61a8
struct AutoAudioLock {
    __forceinline AutoAudioLock()
    {
        if (g_pAudioLock)
            g_pAudioLock->Lock();
    }
    __forceinline ~AutoAudioLock()
    {
        if (g_pAudioLock)
            g_pAudioLock->Unlock();
    }
};

// EASTL containers (retail layouts)
struct HashIter {
    void* mpNode;
    void** mpBucket;
};
struct PolyPair {
    uint32_t first;
    uint32_t second;
};
struct HashInsertResult {
    HashIter it;
    bool inserted;
};
struct PolyphonyMap {                   // eastl::hash_map<uint32_t, int>
    uint32_t mAllocator;
    void** mpBucketArray;               // +0x04
    uint32_t mnBucketCount;             // +0x08
    HashIter* find(HashIter* out, const uint32_t& key);                      // 0x00645ed0
    void insert(HashInsertResult* out, const PolyPair* value, bool b);       // 0x00a26ce0
};
struct EmitterMap {                     // fixed_hash_map<uint32_t, IEmitter*(*)()>
    uint32_t mData;
    void*& At(const uint32_t& key);     // 0x00a2a510 operator[]
};
struct IdRing {                         // ring buffer of ids
    uint32_t mData;
    void push_back(const uint32_t& id); // 0x00a21d30
};
struct IdPool {
    uint32_t mData[0xf0 / 4];
    void Init(unsigned capacity);       // 0x00a102a0
};

void* __cdecl ConstructEmitterSndPlayer();                  // 0x00a20700

extern char g_1552da0[];                // 0x01552da0
extern const char g_systemName[];       // 0x01452d1c "system"

// ---------------------------------------------------------------------------
//  cSystem (retail layout; offsets from the asm)
// ---------------------------------------------------------------------------
struct IntArrayRef {                    // {int* base; int index} at +0x118a20
    int* mpBase;
    int mIndex;
};

template<int N> struct Gap { uint32_t pad[N]; };

class cSystem {
public:
    V16(a)                              // slots 0x00..0x3c
    V16(b)                              // 0x40..0x7c
    V16(c)                              // 0x80..0xbc
    V4(d)                               // 0xc0..0xcc
    V4(e)                               // 0xd0..0xdc
    V4(f)                               // 0xe0..0xec
    V1(g)                               // 0xf0
    virtual uint32_t HashName(const char* name);                // +0xf4
    V1(h)                               // 0xf8
    virtual void SetTuning(uint32_t key, float value);          // +0xfc
    V16(i)                              // 0x100..0x13c
    V4(j) V4(k) V4(l)                   // 0x140..0x16c
    V1(m) V1(n) V1(o)                   // 0x170..0x178
    virtual VoiceContainer* GetVoiceHolder(uint32_t id);        // +0x17c (object with a container at +0x10)
    V4(p) V4(q) V4(r)                   // 0x180..0x1ac
    V1(s)                               // 0x1b0
    virtual void Hook1b4();                                     // +0x1b4
    V1(t)                               // 0x1b8
    virtual void Hook1bc(const char* p);                        // +0x1bc
    V1(u)                               // 0x1c0
    virtual void Hook1c4();                                     // +0x1c4
    virtual void Hook1c8();                                     // +0x1c8
    V4(v) V4(w) V1(x)                   // 0x1cc..0x1ec
    virtual void Hook1f0();                                     // +0x1f0

    Gap<(0x90 - 4) / 4> pad04;
    uint32_t mCommandBufferSize;        // +0x90
    uint8_t pad94[2];
    bool mbMutedForSilence;             // +0x96
    bool mbMutedForFocus;               // +0x97
    bool mbMutedByProperty;             // +0x98
    bool mbMuted;                       // +0x99
    bool mbMuteApplied;                 // +0x9a
    uint8_t pad9b;
    uint32_t mAllocator;                // +0x9c
    uint32_t mAllocator2;               // +0xa0
    RWSystem* mpRWAC;                   // +0xa4
    float mDacOutputMode;               // +0xa8
    float mDacOutputSampleRate;         // +0xac
    Gap<(0xe8 - 0xb0) / 4> padb0;
    StreamPool* mpStreamPoolDefault;    // +0xe8
    uint32_t mStreamPoolNumStreams;     // +0xec
    uint32_t mStreamPoolBufferSize;     // +0xf0
    uint32_t mStreamPoolMaxRequests;    // +0xf4
    Gap<(0x198 - 0xf8) / 4> mDebugChannel;      // +0xf8
    Gap<(0x200 - 0x198) / 4> mResourceDeviceDriver;   // +0x198
    int mPerformanceLevel;              // +0x200
    Gap<(0x2b4 - 0x204) / 4> pad204;
    IdPool mPoolA;                      // +0x2b4
    IdPool mPoolB;                      // +0x3a4
    Gap<(0x118a20 - 0x494) / 4> pad494;
    IntArrayRef mIdArray;               // +0x118a20
    Gap<(0x118a78 - 0x118a28) / 4> pad118a28;
    EmitterMap mEmitterMap;             // +0x118a78
    Gap<(0x131840 - 0x118a7c) / 4> pad118a7c;
    IdRing mIdRing;                     // +0x131840
    Gap<(0x137fe8 - 0x131844) / 4> pad131844;
    PolyphonyMap mPolyphonyMap;         // +0x137fe8
    Gap<(0x15b750 - 0x137ff4) / 4> pad137ff4;
    uint32_t mIterValue;                // +0x15b750
    void* mIterPos;                     // +0x15b754
    uint32_t mIter8, mIterC, mIter10;   // +0x15b758..0x15b760
    Gap<(0x15b778 - 0x15b764) / 4> pad15b764;
    IFactory* mpFactoryB;               // +0x15b778

    void MuteAll(bool mute, bool immediate);        // 0x00a233b0
    void PreloadConfigurations();                   // 0x00a30940
    void FUN_a2ef60();                              // 0x00a2ef60
    void FUN_a2da30();                              // 0x00a2da30
    bool InitAT();
};

// @ 0x00a31170
bool cSystem::InitAT()
{
    mbMuteApplied = false;
    int* slot = &mIdArray.mpBase[mIdArray.mIndex];
    mIterValue = *slot;
    mIterPos = slot;
    mIter8 = 0;
    mIterC = 0;
    mIter10 = 0;

    IResourceManager* mgr = GetResourceManager();
    if (mgr) {
        FactoryObj* fa = (FactoryObj*)ZoneAlloc(8, g_audioName, 0, 0, 0, 0);
        fa = fa ? fa->Init(g_vtFactoryA) : 0;
        mgr->RegisterFactory(1, (IFactory*)fa, 0);

        FactoryObj* fb = (FactoryObj*)ZoneAlloc(8, g_audioName, 0, 0, 0, 0);
        fb = fb ? fb->Init(g_vtFactoryB) : 0;
        IFactory* nb = (IFactory*)fb;
        IFactory* old = mpFactoryB;
        if (nb != old) {
            if (nb)
                nb->AddRef();
            mpFactoryB = nb;
            if (old)
                old->Release();
        }
        mgr->RegisterFactory(1, mpFactoryB, 0);

        FactoryObj* fc = (FactoryObj*)ZoneAlloc(8, g_audioName, 0, 0, 0, 0);
        fc = fc ? fc->Init(g_vtFactoryC) : 0;
        mgr->RegisterFactory(1, (IFactory*)fc, 0);
    }

    Hook1bc(g_1552da0);
    mpRWAC = CreateInstance(&mAllocator, mCommandBufferSize);
    if (!mpRWAC)
        return false;

    mPoolA.Init(5000);
    mPoolB.Init(5000);

    AutoAudioLock lock;
    mpRWAC->SetCallback((void*)0x00b1e4d0);
    Hook1b4();
    if (g_FsAllocatorManager == 0) {
        FsParams fp;
        fp.mpChannel = &mDebugChannel;
        fp.mpAllocator2 = &mAllocator2;
        fp.mA = 2;
        fp.mB = 0x400;
        FsInit(&fp);
    }
    FsManager* fs = GetFsManager();
    if (fs)
        fs->SetDriver(&mResourceDeviceDriver, 0);
    mpStreamPoolDefault = ReleaseHandler(0x2ea8fb98, mStreamPoolNumStreams, mStreamPoolBufferSize,
                                         mStreamPoolMaxRequests, mpRWAC, &mAllocator, 0);
    uint32_t emitterKey = 0x1a527db;
    mEmitterMap.At(emitterKey) = (void*)ConstructEmitterSndPlayer;
    Hook1f0();
    FUN_a2ef60();
    FUN_a2da30();
    Hook1c4();

    VoiceContainer* holder = GetVoiceHolder(0xf1cc1687);
    if (!holder)
        return false;
    VoiceContainer* container = (VoiceContainer*)((char*)holder + 0x10);
    IPluginParam* p1 = container->FindPlugin(0x53756230);
    if (!p1)
        return false;
    mpRWAC->AddPlugin(p1);
    IPluginParam* p2 = container->FindPlugin(0x44616330);
    if (!p2)
        return false;

    float mode = mDacOutputMode;
    p2->SetParam(1, &mode);
    float rate = mDacOutputSampleRate;
    p2->SetParam(2, &rate);
    p2->SetParam(3, 0);

    bool muted;
    if (mbMutedForSilence || mbMuted || mbMutedForFocus || mbMutedByProperty)
        muted = true;
    else
        muted = false;
    if (muted != mbMuteApplied)
        MuteAll(muted, true);
    Hook1c8();

    uint32_t id = 0x7d1;
    do {
        uint32_t tmp = id;
        mIdRing.push_back(tmp);
        ++id;
    } while (id <= 0xbb8);

    ResKey sysKey;
    sysKey.instance = 0;
    sysKey.type = 0x2b9f662;
    sysKey.group = 0x21407ee;
    sysKey.instance = HashName(g_systemName);
    IResourceType* rt = GetResourceManager()->GetResourceType(&sysKey);
    if (rt && rt->GetTypeID() != 0x34728492)
        PreloadConfigurations();
    SetTuning(0x6df5822d, (float)mPerformanceLevel);

    IResourceManager* mgr2 = GetResourceManager();
    if (mgr2) {
        ResKey tableKey;
        tableKey.instance = 0xa101b2c4;
        tableKey.type = 0x5bad11c;
        tableKey.group = 0x21407ee;
        DbList list;
        list.mAnchor.mpNext = list.mAnchor.mpPrev = &list.mAnchor;
        list.mpAllocator = GetDefaultAllocator();
        list.mFlags = 0;
        mgr2->GetDatabases(&list, &tableKey);
        for (ListNode* node = list.mAnchor.mpNext; node != &list.mAnchor; node = node->mpNext) {
            IResource* res = 0;
            IDatabase* db = (IDatabase*)node->mpData;
            if (db->GetResource(&tableKey, &res, 1, 6, 1, 0)) {
                IStream* stream = res->OpenStream();
                if (stream) {
                    ByteVec buf;
                    uint32_t size = stream->GetSize();
                    buf.resize(size);
                    uint8_t* data = buf.mpBegin;
                    if (size == stream->Read(data, size)) {
                        uint32_t count = size >> 3;
                        while (count != 0) {
                            uint32_t key = ((uint32_t*)data)[0];
                            uint32_t value = ((uint32_t*)data)[1];
                            --count;
                            void* end = mPolyphonyMap.mpBucketArray[mPolyphonyMap.mnBucketCount];
                            data += 8;
                            HashIter it;
                            if (mPolyphonyMap.find(&it, key)->mpNode == end) {
                                PolyPair pr;
                                pr.first = key;
                                pr.second = value;
                                HashInsertResult ir;
                                mPolyphonyMap.insert(&ir, &pr, false);
                            }
                        }
                    }
                    stream->Close();
                }
            }
            if (res)
                res->Release();
        }
        for (ListNode* n = list.mAnchor.mpNext; n != &list.mAnchor;) {
            ListNode* next = n->mpNext;
            ((CoreAlloc*)list.mpAllocator)->Free(n, 0xc);
            n = next;
        }
    }
    return true;
}
