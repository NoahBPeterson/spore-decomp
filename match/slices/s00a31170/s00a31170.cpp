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
#include <float.h>

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
struct IStream { private:
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
    void shutdown();                                        // 0x0112c880
};
struct StreamPool {
    void QueueRelease();                                    // 0x0112e410
};
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
    void Init(void* flag);              // 0x00a26fa0 (ret 4)
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
    uint32_t mnNodeCount;               // +0x0c
    HashIter* find(HashIter* out, const uint32_t& key);                      // 0x00645ed0
    void insert(HashInsertResult* out, const PolyPair* value, bool b);       // 0x00a26ce0
    void FreeNodes(void* first, void* last);                                 // 0x00a1b6c0
};
struct EmitterMap {                     // fixed_hash_map<uint32_t, IEmitter*(*)()>
    uint32_t mAllocator;                // +0x00
    void* mpBegin;                      // +0x04
    void* mpEnd;                        // +0x08
    uint32_t mCount;                    // +0x0c
    void*& At(const uint32_t& key);     // 0x00a2a510 operator[]
    void FreeNodes(void* first, void* last);                                 // 0x00a1b6c0
};
struct IdRing {                         // ring buffer of ids
    void* mpBegin;                      // +0x00
    void* mpEnd;                        // +0x04
    uint32_t mCount;                    // +0x08
    void push_back(const uint32_t& id); // 0x00a21d30
    void Reset(void* base) { mpEnd = mpBegin = base; mCount = 0; }
};
struct IdPool {
    uint32_t mData[0xf0 / 4];
    void Init(unsigned capacity);       // 0x00a102a0
    void Reset();                       // 0x00a0fdd0
};
struct IdPoolShort {                    // second id pool; its allocator block ends at +0x404
    uint32_t mData[0x60 / 4];
    void Init(unsigned capacity);       // 0x00a102a0
};

// ---------------------------------------------------------------------------
//  container storage walked by the audio-system teardown (0x00a31800)
// ---------------------------------------------------------------------------
struct EaTable {                        // eastl node container: allocator word, {begin, end, count}
    uint32_t mAllocator;                // +0x00
    void* mpBegin;                      // +0x04
    void* mpEnd;                        // +0x08
    uint32_t mCount;                    // +0x0c
    void DoFreeNodes(void* first, void* last);          // 0x00a1b6c0 (ret 8)
    void FreeBuckets(void** buckets, uint32_t n);       // 0x00a24480 (ret 8)
    void FreeSubNodes(void** nodes, uint32_t n);        // 0x00a276e0 (ret 8)
    void FreeResNodes(void** nodes, uint32_t n);        // 0x00a26f30 (ret 8)
    void FreeProfBuckets(void* first, uint32_t n);      // 0x0068fb70 (ret 8)
    void FreeFloatNodes(void* first, void* last);       // 0x00a2f6e0 (ret 8)
    void FreeMiscNodes(void* first, void* last);        // 0x00a2add0 (ret 8)
    void FreeFdfNodes(void* first, void* last);         // 0x00b6fdf0 (ret 8)
    void FindMisc(HashIter* out, const uint32_t& key);  // 0x00a23c10 (ret 8)
    void FindInt(HashIter* out, const uint32_t& key);   // 0x00645ed0 (ret 8)
    void* Sentinel() { return ((void**)mpBegin)[(int)(intptr_t)mpEnd]; }
};
struct EaVec {                          // eastl vector / id ring storage
    void* mpBegin;                      // +0x00
    void* mpEnd;                        // +0x04
    void* mpCapacity;                   // +0x08
};
struct BitVec {                         // eastl::vector<bool> storage (4-byte word stride)
    uint32_t* mpBegin;                  // +0x00
    uint32_t* mpEnd;                    // +0x04
    uint32_t* mpCapacity;               // +0x08
    void EraseAll();                    // erase(begin(), end()) -> memcpy + restamped end
};
struct EaTree {                         // eastl::rbtree header
    uint32_t mAllocator;                // +0x00
    void* mpHeaderNode;                 // +0x04
    void* mpRoot;                       // +0x08
    void* mpNodeChain;                  // +0x0c
    uint8_t mbFlag;                     // +0x10
    uint8_t mPad11[3];
    uint32_t mCount;                    // +0x14
    uint32_t mPad18;                    // +0x18
    void NukeSubtree(void* node);       // 0x009a9600 (ret 4)
    void Clear()
    {
        NukeSubtree(mpNodeChain);
        mpRoot = &mpHeaderNode;
        mpNodeChain = 0;
        mbFlag = 0;
        mCount = 0;
        mpHeaderNode = &mpHeaderNode;
    }
};
struct EaList {                         // eastl::list anchor (no destructor, pool allocated)
    ListNode* mpNext;                   // +0x00
    ListNode* mpPrev;                   // +0x04
    void FreeNodes();                   // 0x00a222c0
    void Clear()
    {
        ListNode* node = mpNext;
        while (node != (ListNode*)this) {
            ListNode* next = node->mpNext;
            node->mpPrev = 0;
            node->mpNext = 0;
            node = next;
        }
        mpNext = (ListNode*)this;
        mpPrev = (ListNode*)this;
    }
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
    V4(b1) V4(b2) V4(b3) V1(b13)        // 0x40..0x70
    virtual void Hook74(void* pending);                         // +0x74
    V1(b15) V1(b16)                     // 0x78, 0x7c
    virtual void Hook80(int enable);                            // +0x80
    V4(c1) V4(c2) V4(c3) V1(c4) V1(c5) V1(c6)                   // 0x84..0xbc
    V4(d)                               // 0xc0..0xcc
    V1(ea) V1(eb) V1(ec)                // 0xd0..0xd8
    virtual void HookDC();                                      // +0xdc
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
    virtual void Hook1b8();                                     // +0x1b8
    virtual void Hook1bc(const char* p);                        // +0x1bc
    V1(u)                               // 0x1c0
    virtual void Hook1c4();                                     // +0x1c4
    virtual void Hook1c8();                                     // +0x1c8
    virtual void Hook1cc();                                     // +0x1cc
    virtual void Hook1d0();                                     // +0x1d0
    V1(v1) V1(v2) V4(w) V1(x)           // 0x1d4..0x1ec
    virtual void Hook1f0();                                     // +0x1f0

    Gap<1> pad04;                       // +0x04
    void* mpMessageHandler;             // +0x08
    uint32_t mHandlerArg0;              // +0x0c
    uint32_t mHandlerArg1;              // +0x10
    uint32_t mHandlerArg2;              // +0x14
    uint32_t mHandlerArg3;              // +0x18
    Gap<(0x90 - 0x1c) / 4> pad1c;
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
    Gap<(0x210 - 0x204) / 4> pad204;
    float mFadeVolume;                  // +0x210
    Gap<(0x2b4 - 0x214) / 4> pad214;
    IdPool mPoolA;                      // +0x2b4
    IdPoolShort mPoolB;                 // +0x3a4
    EaTable mHash404;                   // +0x404
    Gap<(0x13f4 - 0x414) / 4> pad414;
    EaTable mHash13f4;                  // +0x13f4
    Gap<(0x23e4 - 0x1404) / 4> pad1404;
    EaTable mHash23e4;                  // +0x23e4
    Gap<(0x33d4 - 0x23f4) / 4> pad23f4;
    EaTable mHash33d4;                  // +0x33d4
    Gap<(0x80424 - 0x33e4) / 4> pad33e4;
    EaTable mHash80424;                 // +0x80424
    Gap<(0x1189fc - 0x80434) / 4> pad80434;
    EaTable mFdf1189fc;                 // +0x1189fc
    Gap<(0x118a1c - 0x118a0c) / 4> pad118a0c;
    EaTable mIdTable;                   // +0x118a1c (mIdArray's base/index are its begin/end)
    Gap<(0x118a3c - 0x118a2c) / 4> pad118a2c;
    EaTable mFdf118a3c;                 // +0x118a3c
    Gap<(0x118a5c - 0x118a4c) / 4> pad118a4c;
    EaTree mTree118a5c;                 // +0x118a5c
    EmitterMap mEmitterMap;             // +0x118a78
    Gap<(0x118b90 - 0x118a88) / 4> pad118a88;
    EaTable mRes118b90;                 // +0x118b90
    Gap<(0x118bb0 - 0x118ba0) / 4> pad118ba0;
    EaTable mHash118bb0;                // +0x118bb0
    Gap<(0x119ba0 - 0x118bc0) / 4> pad118bc0;
    void* mpLogReporterList;            // +0x119ba0
    EaVec mReporterVec;                 // +0x119ba4
    Gap<(0x119bb8 - 0x119bb0) / 4> pad119bb0;
    EaTable mHash119bb8;                // +0x119bb8
    Gap<(0x11a3d8 - 0x119bc8) / 4> pad119bc8;
    EaTable mHash11a3d8;                // +0x11a3d8
    Gap<(0x11b3c8 - 0x11a3e8) / 4> pad11a3e8;
    EaTable mFloat11b3c8;               // +0x11b3c8
    Gap<(0x1277b4 - 0x11b3d8) / 4> pad11b3d8;
    EaTable mMisc1277b4;                // +0x1277b4
    Gap<(0x128ae0 - 0x1277c4) / 4> pad1277c4;
    EaTable mProf128ae0;                // +0x128ae0
    Gap<(0x12c9ac - 0x128af0) / 4> pad128af0;
    void* mpProfPool;                   // +0x12c9ac
    Gap<(0x12d968 - 0x12c9b0) / 4> pad12c9b0;
    EaVec mRing12d968;                  // +0x12d968
    EaTable mProf12d974;                // +0x12d974
    Gap<(0x131840 - 0x12d984) / 4> pad12d984;
    IdRing mIdRing;                     // +0x131840
    Gap<(0x1327fc - 0x13184c) / 4> pad13184c;
    EaVec mRing1327fc;                  // +0x1327fc
    EaTable mProf132808;                // +0x132808
    Gap<(0x1366d4 - 0x132818) / 4> pad132818;
    void* mpProfPool2;                  // +0x1366d4
    Gap<(0x137690 - 0x1366d8) / 4> pad1366d8;
    EaVec mRing137690;                  // +0x137690
    BitVec mBits13769c;                 // +0x13769c
    Gap<(0x13777c - 0x1376a8) / 4> pad1376a8;
    EaTable mHash13777c;                // +0x13777c
    Gap<(0x137fe8 - 0x13778c) / 4> pad13778c;
    PolyphonyMap mPolyphonyMap;         // +0x137fe8
    Gap<(0x157438 - 0x137ff8) / 4> pad137ff8;
    EaList mList157438;                 // +0x157438
    EaTable mProf157440;                // +0x157440
    Gap<(0x157c60 - 0x157450) / 4> pad157450;
    EaList mPromptList;                 // +0x157c60
    Gap<(0x158f48 - 0x157c68) / 4> pad157c68;
    ListNode* mpPromptIter;             // +0x158f48
    Gap<(0x15b750 - 0x158f4c) / 4> pad158f4c;
    uint32_t mIterValue;                // +0x15b750
    void* mIterPos;                     // +0x15b754
    uint32_t mIter8, mIterC, mIter10;   // +0x15b758..0x15b760
    Gap<(0x15b778 - 0x15b764) / 4> pad15b764;
    IFactory* mpFactoryB;               // +0x15b778
    Gap<(0x15bb7c - 0x15b77c) / 4> pad15b77c;
    BitVec mBits15bb7c;                 // +0x15bb7c

    void MuteAll(bool mute, bool immediate);        // 0x00a233b0
    void PreloadConfigurations();                   // 0x00a30940
    void FUN_a2ef60();                              // 0x00a2ef60
    void FUN_a2da30();                              // 0x00a2da30
    bool InitAT();
    bool ShutdownAT();                              // 0x00a31800
    void InsertMapped(HashIter* out, const PolyPair* value, uint8_t flag);  // 0x00a2f510
    bool FUN_00a31dc0(uint32_t key, void* query);   // 0x00a31dc0
};

// @ 0x00a31170
bool cSystem::InitAT()
{
    mbMuteApplied = false;
    int* slot = &((int*)mIdTable.mpBegin)[(int)(intptr_t)mIdTable.mpEnd];
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

// ---------------------------------------------------------------------------
//  teardown helpers
// ---------------------------------------------------------------------------
void __cdecl FUN_00571db0(void* handler, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // Messaging::RemoveHandler
void __cdecl FUN_011e5d30();                                        // filesys_destroy
void __cdecl FUN_00e25bd0(void* first, void* last);                 // eastl::vector::erase(first, last)
void __cdecl FUN_00926410(void* p);                                 // list-node release
void __cdecl FUN_011e0744(void* dst, const void* src, uint32_t n);  // memcpy

// eastl hashtable node payload: pair<const uint32_t, T> at node + 4
struct KeyValue {
    uint32_t mKey;                      // +0x00
    uint32_t mValue;                    // +0x04
    bool Remove(void* query);           // 0x00a27e60 (ret 4)
};
struct MapNode {
    void* mpNext;                       // +0x00
    KeyValue mPair;                     // +0x04
};

extern uint32_t g_teardownFlag;             // 0x0166d9fc
extern float kPromptReleaseTime;            // 0x013ef548

struct IPrompt {
    virtual void v0();
    virtual void v4();
    virtual void Release(float a, float b); // +0x08
};

void BitVec::EraseAll()
{
    FUN_011e0744(mpBegin, mpEnd, 0);
    mpEnd -= mpEnd - mpBegin;
}

// @ 0x00a31800
bool cSystem::ShutdownAT()
{
    mPoolA.Reset();
    Hook1b8();
    HookDC();
    Hook80(1);

    if (mPromptList.mpNext != (ListNode*)&mPromptList) {
        for (mpPromptIter = mPromptList.mpNext; mpPromptIter != (ListNode*)&mPromptList; )
        {
            ListNode* node = mpPromptIter;
            ((IPrompt*)node->mpData)->Release(kPromptReleaseTime, kPromptReleaseTime);
            mpPromptIter = node->mpNext;
        }
    }

    mFadeVolume = 0.0f;
    Hook1d0();
    Hook1cc();

    if (mpMessageHandler) {
        void* handler = mpMessageHandler;
        mpMessageHandler = 0;
        FUN_00571db0(handler, mHandlerArg0, mHandlerArg1, mHandlerArg2, mHandlerArg3);
    }

    if (mpStreamPoolDefault) {
        {
            AutoAudioLock lock;
            mpStreamPoolDefault->QueueRelease();
            mpStreamPoolDefault = 0;
        }
    }

    if (mpRWAC) {
        unsigned int ctrl = _controlfp(0, 0);
        bool restore = (ctrl & 0x30000) != 0x10000;
        if (restore)
            _controlfp(0x10000, 0x30000);
        mpRWAC->shutdown();
        mpRWAC = 0;
        if (restore)
            _controlfp(ctrl, 0x30000);
    }

    FUN_011e5d30();

    if (mPromptList.mpNext != (ListNode*)&mPromptList) {
        for (mpPromptIter = mPromptList.mpNext; mpPromptIter != (ListNode*)&mPromptList; )
        {
            ListNode* node = mpPromptIter;
            Hook74(node->mpData);
            mpPromptIter = node->mpNext;
        }
        mPromptList.FreeNodes();
        mPromptList.mpNext = (ListNode*)&mPromptList;
        mPromptList.mpPrev = (ListNode*)&mPromptList;
    }

    mHash404.DoFreeNodes(mHash404.mpBegin, mHash404.mpEnd);
    mHash404.mCount = 0;
    mHash13f4.FreeBuckets((void**)mHash13f4.mpBegin, (uint32_t)(intptr_t)mHash13f4.mpEnd);
    mHash13f4.mCount = 0;
    mHash23e4.DoFreeNodes(mHash23e4.mpBegin, mHash23e4.mpEnd);
    mHash23e4.mCount = 0;
    mHash33d4.DoFreeNodes(mHash33d4.mpBegin, mHash33d4.mpEnd);
    mHash33d4.mCount = 0;
    mHash80424.FreeSubNodes((void**)mHash80424.mpBegin, (uint32_t)(intptr_t)mHash80424.mpEnd);
    mHash80424.mCount = 0;
    mFdf1189fc.FreeFdfNodes(mFdf1189fc.mpBegin, mFdf1189fc.mpEnd);
    mFdf1189fc.mCount = 0;
    mIdTable.FreeFdfNodes(mIdTable.mpBegin, mIdTable.mpEnd);
    mIdTable.mCount = 0;
    mTree118a5c.Clear();
    mEmitterMap.FreeNodes(mEmitterMap.mpBegin, mEmitterMap.mpEnd);
    mEmitterMap.mCount = 0;
    mRes118b90.FreeResNodes((void**)mRes118b90.mpBegin, (uint32_t)(intptr_t)mRes118b90.mpEnd);
    mRes118b90.mCount = 0;
    mHash118bb0.DoFreeNodes(mHash118bb0.mpBegin, mHash118bb0.mpEnd);
    mHash118bb0.mCount = 0;

    if (mpLogReporterList) {
        FUN_00926410(mpLogReporterList);
        operator_delete_array(mpLogReporterList);
    }
    mpLogReporterList = 0;
    FUN_00e25bd0(mReporterVec.mpBegin, mReporterVec.mpEnd);

    mHash119bb8.FreeBuckets((void**)mHash119bb8.mpBegin, (uint32_t)(intptr_t)mHash119bb8.mpEnd);
    mHash119bb8.mCount = 0;
    mHash11a3d8.DoFreeNodes(mHash11a3d8.mpBegin, mHash11a3d8.mpEnd);
    mHash11a3d8.mCount = 0;
    mFloat11b3c8.FreeFloatNodes(mFloat11b3c8.mpBegin, mFloat11b3c8.mpEnd);
    mFloat11b3c8.mCount = 0;
    mMisc1277b4.FreeMiscNodes(mMisc1277b4.mpBegin, mMisc1277b4.mpEnd);
    mMisc1277b4.mCount = 0;
    mProf128ae0.FreeProfBuckets(mProf128ae0.mpBegin, (uint32_t)(intptr_t)mProf128ae0.mpEnd);
    mProf128ae0.mCount = 0;

    mRing12d968.mpBegin = mpProfPool;
    mRing12d968.mpEnd = mpProfPool;
    mRing12d968.mpCapacity = 0;
    mProf12d974.FreeProfBuckets(mProf12d974.mpBegin, (uint32_t)(intptr_t)mProf12d974.mpEnd);
    mProf12d974.mCount = 0;

    mRing1327fc.mpBegin = mIdRing.mpBegin;
    mRing1327fc.mpEnd = mIdRing.mpBegin;
    mRing1327fc.mpCapacity = 0;
    mProf132808.FreeProfBuckets(mProf132808.mpBegin, (uint32_t)(intptr_t)mProf132808.mpEnd);
    mProf132808.mCount = 0;

    mRing137690.mpBegin = mpProfPool2;
    mRing137690.mpEnd = mpProfPool2;
    mRing137690.mpCapacity = 0;
    mBits13769c.EraseAll();

    mList157438.Clear();
    mProf157440.FreeProfBuckets(mProf157440.mpBegin, (uint32_t)(intptr_t)mProf157440.mpEnd);
    mProf157440.mCount = 0;

    mBits15bb7c.EraseAll();

    mFdf118a3c.FreeFdfNodes(mFdf118a3c.mpBegin, mFdf118a3c.mpEnd);
    mFdf118a3c.mCount = 0;
    mHash13777c.DoFreeNodes(mHash13777c.mpBegin, mHash13777c.mpEnd);
    mHash13777c.mCount = 0;

    if (mpFactoryB) {
        IFactory* old = mpFactoryB;
        mpFactoryB = 0;
        old->Release();
    }

    mPolyphonyMap.FreeNodes(mPolyphonyMap.mpBucketArray, (void*)(intptr_t)mPolyphonyMap.mnBucketCount);
    mPolyphonyMap.mnNodeCount = 0;

    g_teardownFlag = 0;
    return true;
}

// @ 0x00a31dc0
bool cSystem::FUN_00a31dc0(uint32_t key, void* query)
{
    bool removed = false;
    HashIter it;

    mMisc1277b4.FindMisc(&it, key);
    if (it.mpNode != mMisc1277b4.Sentinel())
        return ((MapNode*)it.mpNode)->mPair.Remove(query);

    mHash404.FindInt(&it, key);
    if (it.mpNode == mHash404.Sentinel())
        return removed;

    KeyValue* kv = &((MapNode*)it.mpNode)->mPair;
    uint32_t value = kv->mValue;

    EaTree temp;
    temp.mAllocator = 0;
    temp.mpHeaderNode = &temp;
    temp.mpRoot = &temp;
    temp.mpNodeChain = 0;
    temp.mbFlag = 0;
    temp.mCount = 0;

    removed = kv->Remove(query);
    if (removed) {
        PolyPair pair;
        HashIter out;
        uint8_t flag = 0;
        pair.first = key;
        pair.second = value;
        out.Init(&flag);                        // 0x00a26fa0
        InsertMapped(&out, &pair, flag);        // 0x00a2f510
        temp.NukeSubtree(temp.mpNodeChain);
    }
    temp.NukeSubtree(temp.mpNodeChain);
    return removed;
}
