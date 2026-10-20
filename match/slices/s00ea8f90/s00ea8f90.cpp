// slice s00ea8f90 -- SP::Audio mix-mode subsystem (cMixMode, cMixModeManager, cFactoryMixMode).
//   0x00ea8f90  SP::Audio::cMixMode::Start()
//   0x00ea9260  SP::Audio::cMixMode::Stop(bool)
//   0x00ea9320  SP::Audio::cMixMode::cMixMode(cMixModeManager*, EA::ResourceMan::Key)
//   0x00ea93c0  SP::Audio::cMixMode::~cMixMode()
//   0x00ea9440  eastl::vector<cMixMode*,SP_STL_Sound>::DoInsertValue
//   0x00ea9550  SP::Audio::cMixMode::ConfigurePrimitive()
//   0x00ea9790  bool IsMixableKey(unsigned int)
//   0x00ea9880  SP::Audio::cMixModeManager::UpdateSounds(float)
//   0x00ea99a0  SP::Audio::cMixModeManager::RemoveSound(unsigned int, bool)
//   0x00ea9a40  SP::Audio::cMixModeManager::StartMode(unsigned int)
//   0x00ea9a80  SP::Audio::cMixModeManager::StopMode(unsigned int, bool)
//   0x00ea9ac0  SP::Audio::cMixModeManager::IsModeActive(unsigned int)
//   0x00ea9b00  SP::Audio::cMixModeManager::RegisterSound(unsigned int)
//   0x00ea9bb0  MessageModeMap::find(unsigned int) const
//   0x00ea9c20  SP::Audio::`anonymous_namespace'::cFactoryMixMode::scalar_deleting_destructor
//   0x00ea9c70  SP::Audio::cMixModeManager::Shutdown()
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <string.h>

#pragma warning(disable: 4100)

typedef unsigned int   u32;

void* __cdecl  GetSystemAT();                          // 0x00a206f0  EA::Audio::GetSystemAT
void  __cdecl  RecordEvent4(u32, u32, float, u32);     // 0x00435f40  ?RecordEvent4@@YAXIIMI@Z
void* __cdecl  GetServer();                            // 0x00883860
void* __cdecl  KillSetiEffects(void*, void*);          // 0x00435ed0  (2-arg call site)
bool  __cdecl  PauseSound(u32, int);                   // 0x00a37290
void  __cdecl  operator_delete(void*);                 // 0x00f47380
void* __cdecl  EAAllocate(u32, const char*, int, int, int, int);   // 0x00f473a0
void* __cdecl  operator_new(u32, const char*, int, int, int, int); // 0x00f473a0
void  __cdecl  FUN_00572020(int, int);                 // 0x00572020
void  __cdecl  FUN_00eade60(void*);                    // 0x00eade60
u32   __cdecl  FUN_00b4f930(void*, void*);             // 0x00b4f930
void* __cdecl  FUN_011e0744(void*, const void*, u32);  // 0x011e0744  (block copy helper, returns dst)
void* __cdecl  LowerBoundPair(void*, void*, void*, unsigned char); // 0x005701b0
void  __cdecl  DoNukeSubtree(void*);                   // 0x009a9600
void  __cdecl  MutexDtor(void*);                       // 0x00922130
void  __cdecl  ZoneObject_delete(void*);               // 0x00926060
void  __cdecl  RemoveHandler(void*, void*, void*, void*, void*);   // 0x00571db0

// vtable slot fetch: value of this->vftable[off/4] (off is a byte offset).
static inline void* VT(void* obj, int off) { return ((void**) (*(void**) obj))[off / 4]; }

typedef void  (__thiscall *Fn0)(void*);
typedef void  (__thiscall *Fn1u)(void*, u32);
typedef void  (__thiscall *Fn2u)(void*, u32, u32);
typedef void  (__thiscall *Fn1f)(void*, float);
typedef float (__thiscall *Fnf0)(void*);
typedef u32   (__thiscall *Fnu0)(void*);
typedef u32   (__thiscall *Fnu1u)(void*, u32, void*, void*);
typedef bool  (__thiscall *Fnb1u)(void*, u32, void*, void*);
typedef void  (__thiscall *Fnv1u)(void*, u32, void*, u32);

namespace SP {
namespace Audio {

class cMixMode;
class cMixModeManager;

// ---------------------------------------------------------------------------
// eastl::vector<unsigned int, SP_STL_Sound> -- retail 0x14 (3 pointers + 8 bytes allocator).
struct SoundVector {
    u32* mBegin;   // +0x00
    u32* mEnd;     // +0x04
    u32* mCap;     // +0x08
    u32  mAlloc[2];// +0x0c
    void VectorInsert(u32* pos, const u32* value);   // 0x00ea9440
};

// ---------------------------------------------------------------------------
// eastl::hash_map<unsigned int, AutoRefCount<cMixMode>> (cMixModeManager::mModes).
struct ModeNode {
    u32        first;    // +0x00 key
    cMixMode*  second;   // +0x04 value
    ModeNode*  mpNext;   // +0x08
};
struct ModeIterator {
    ModeNode*  mpNode;       // +0x00
    ModeNode** mpBucket;     // +0x04
    ModeIterator() {}        // non-trivial: returned via hidden pointer (as eastl does)
    ModeNode* operator->() const { return mpNode; }
};
struct ModeMap {                       // 0x20 bytes
    u32         mPolicy;               // +0x00
    ModeNode**  mpBucketArray;         // +0x04
    u32         mnBucketCount;         // +0x08
    u32         mnElementCount;        // +0x0c
    char        mAllocator[0x10];      // +0x10
    ModeIterator find(const u32& key) const;   // 0x00645ed0 (shared hashtable::find)
    ModeNode* end_node() const { return mpBucketArray[mnBucketCount]; }
    void DoFreeNodes(ModeNode** bucketArray, u32 bucketCount);   // 0x00961d60
};

// ---------------------------------------------------------------------------
// eastl::hash_map<unsigned int, cMixSound> (cMixModeManager::mSounds).
struct SoundNode {
    u32        key;            // +0x00
    u32        instanceId;     // +0x04
    u32        refCount;       // +0x08
    float      fSecsSinceStop; // +0x0c
    SoundNode* mpNext;         // +0x10
};
struct SoundIterator {
    SoundNode*  mpNode;
    SoundNode** mpBucket;
    SoundIterator() {}
    SoundIterator(SoundNode* n, SoundNode** b) : mpNode(n), mpBucket(b) {}
    SoundNode* operator->() const { return mpNode; }
};
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

// ---------------------------------------------------------------------------
// EA::ResourceMan::Key (3 dwords, passed by value).
struct Key { u32 instanceID; u32 typeID; u32 groupID; };

// ---------------------------------------------------------------------------
// SP::Audio::cMixMode (retail layout). Three vtable words (+0x00/+0x04/+0x08) come from
// three polymorphic base subobjects; methods reachable in this slice are dispatched through
// the primary table (+0x00): Value at +0x1c (slot 7), SetValue at +0x34 (slot 13),
// ConfigurePrimitive at +0x38 (slot 14).
class cMixMode {
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
    cMixModeManager* mManager;  // +0x24
    u32      mKeyInstance; // +0x28
    u32      mKeyType;     // +0x2c
    u32      mKeyGroup;    // +0x30
    SoundVector mA;        // +0x34 (start sounds)
    SoundVector mB;        // +0x48 (pause/instance sounds)
    SoundVector mC;        // +0x5c
    bool     mb70;         // +0x70
    bool     mbRunning;    // +0x71

    cMixMode(cMixModeManager* mgr, Key key);   // 0x00ea9320
    ~cMixMode();                               // 0x00ea93c0
    bool Start();                              // 0x00ea8f90
    bool Stop(bool flag);                      // 0x00ea9260
    bool IsRunning();                          // 0x00ea8ec0 (external)
    void ConfigurePrimitive();                 // 0x00ea9550
};

// ---------------------------------------------------------------------------
// SP::Audio::cMixModeManager (retail layout).
class cMixModeManager {
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

// ---------------------------------------------------------------------------
// Sorted message-key -> mix-mode-id map (eastl::vector_map<u32,u32>).
struct KeyModePair { u32 first; u32 second; };
struct MessageModeMap {
    KeyModePair* mpBegin;      // +0x00
    KeyModePair* mpEnd;        // +0x04
    KeyModePair* mpCapacity;   // +0x08
    u32          mAlloc[2];    // +0x0c
    char         mFlag14;      // +0x14
    KeyModePair* find(const u32& key) const;   // 0x00ea9bb0
    KeyModePair* end() const { return mpEnd; }
};

// ---------------------------------------------------------------------------
// SP::Audio::`anonymous namespace'::cFactoryMixMode.
struct MixModeMutex {                 // EA::Thread::Mutex (0x30 bytes)
    char m[0x30];
    void Dtor();                      // 0x00922130  (??1Mutex@Thread@EA@@QAE@XZ)
};
struct MixModeRbtree {                // rbtree<unsigned int, ...>
    char  m00[0x0c];
    void* mpRoot;                     // +0x0c
    char  m10[0x0c];
    void  DoNukeSubtree(void* node);  // 0x009a9600
};
class cFactoryMixMode {
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

// ---------------------------------------------------------------------------
// @ 0x00ea8f90
bool cMixMode::Start()
{
    if (((Fnf0) VT(this, 0x1c))(this) != 0.0f)
        return false;

    // register every start sound with the manager
    for (u32* p = mA.mBegin; p != mA.mEnd; ++p)
        mManager->RegisterSound(*p);

    // notify the audio system for each instance sound
    for (u32* p = mB.mBegin; p != mB.mEnd; ++p) {
        void* sys = GetSystemAT();
        if (!sys)
            continue;
        ((Fn1u) VT(sys, 0x38))(sys, 0x3475376u);
        ((Fn2u) VT(sys, 0x40))(sys, 0x3475385u, *p);
        ((Fn2u) VT(sys, 0x40))(sys, 0x34753a7u, 0xb85523e5u);
        ((Fn1f) VT(sys, 0x3c))(sys, 1.0f);
        ((Fn2u) VT(sys, 0x40))(sys, 0x34753adu, 0);
        ((Fn0)  VT(sys, 0x58))(sys);
    }

    // second batch
    {
        void* sys = GetSystemAT();
        if (sys) {
            for (u32* p = mC.mBegin; p != mC.mEnd; ++p) {
                ((Fn1u) VT(sys, 0x38))(sys, 0x7ead55cu);
                ((Fn2u) VT(sys, 0x40))(sys, 0x4362049u, *p);
                ((Fn0)  VT(sys, 0x58))(sys);
            }
        }
    }

    // configuration-driven properties
    if (mpConfig != 0) {
        void* sys = GetSystemAT();
        if (sys != 0) {
            u32 a = 0, b = 0;
            ((Fn1u) VT(sys, 0x38))(sys, 0x5c2b8a3u);
            if (((Fnb1u) VT(mpConfig, 0x48))(mpConfig, 0x4f76ed4au, &a, &b))
                ((Fnv1u) VT(sys, 0x4c))(sys, 0x4f76ed4au, &a, b * 4);
            a = 0; b = 0;
            if (((Fnb1u) VT(mpConfig, 0x48))(mpConfig, 0xa6c8bfccu, &a, &b))
                ((Fnv1u) VT(sys, 0x4c))(sys, 0xa6c8bfccu, &a, b * 4);
            a = 0; b = 0;
            if (((Fnb1u) VT(mpConfig, 0x48))(mpConfig, 0xe91c6f7eu, &a, &b))
                ((Fnv1u) VT(sys, 0x4c))(sys, 0xe91c6f7eu, &a, b * 4);
            a = 0; b = 0;
            if (((Fnb1u) VT(mpConfig, 0x48))(mpConfig, 0x8750500du, &a, &b))
                ((Fnv1u) VT(sys, 0x4c))(sys, 0x8750500du, &a, b * 4);

            u32 h = ((Fnu0) VT(sys, 0x64))(sys);
            void* node = (void*) (size_t) FUN_00b4f930((void*) (size_t) h, 0);
            (void) node;
            u32 flags = 0;
            mb70 = (flags != 0);
            if (mb70)
                ((Fn0) VT(sys, 0x58))(sys);
            else
                ((Fn0) VT(sys, 0x5c))(sys);

            a = 0; b = 0;
            if (((Fnb1u) VT(mpConfig, 0x48))(mpConfig, 0x1fc4bce8u, &a, &b)) {
                ((Fn1u) VT(sys, 0x38))(sys, 0x60c62f5u);
                ((Fnv1u) VT(sys, 0x4c))(sys, 0x60c631du, &a, b * 4);
                ((Fn0)  VT(sys, 0x58))(sys);
            }
        }
    }

    ((Fn1f) VT(this, 0x34))(this, 1.0f);
    mbRunning = true;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00ea9260
bool cMixMode::Stop(bool flag)
{
    if (((Fnf0) VT(this, 0x1c))(this) == 0.0f)
        return false;

    ((Fn1f) VT(this, 0x34))(this, 0.0f);
    mbRunning = false;

    for (u32* p = mB.mBegin; p != mB.mEnd; ++p)
        RecordEvent4(*p, 0xb85523e5u, 0.0f, 0);

    for (u32* p = mA.mBegin; p != mA.mEnd; ++p)
        mManager->RemoveSound(*p, flag);

    void* sys = GetSystemAT();
    if (sys != 0 && mb70) {
        mb70 = false;
        ((Fn1u) VT(sys, 0x38))(sys, 0x5c2b8a3u);
        ((Fn0)  VT(sys, 0x58))(sys);
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00ea9320
cMixMode::cMixMode(cMixModeManager* mgr, Key key)
{
    mVtbl1 = (void*) 0x13eb384;
    mVtbl2 = (void*) 0x13ef094;
    m0c = 0;
    mbDirty = true;
    mValue = 0.0f;
    mpConfig = 0;
    mManager = mgr;
    mKeyInstance = key.instanceID;
    mKeyType = key.typeID;
    mKeyGroup = key.groupID;
    m1c = 0;
    m20 = 0;
    mVtbl0 = (void*) 0x1488000;
    mVtbl1 = (void*) 0x1487ff0;
    mVtbl2 = (void*) 0x1487fec;
    mA.mBegin = 0; mA.mEnd = 0; mA.mCap = 0;
    mB.mBegin = 0; mB.mEnd = 0; mB.mCap = 0;
    mC.mBegin = 0; mC.mEnd = 0; mC.mCap = 0;
    mb70 = false;
    mbRunning = false;
}

// ---------------------------------------------------------------------------
// @ 0x00ea93c0
cMixMode::~cMixMode()
{
    if (mC.mBegin) operator_delete(mC.mBegin);
    if (mB.mBegin) operator_delete(mB.mBegin);
    if (mA.mBegin) operator_delete(mA.mBegin);
    if (mpConfig)
        ((Fn0) VT(mpConfig, 0x04))(mpConfig);
    mVtbl2 = (void*) 0x13ef094;
    mVtbl1 = (void*) 0x13eb394;
    mVtbl0 = (void*) 0x13eb938;
}

// ---------------------------------------------------------------------------
// @ 0x00ea9440  eastl::vector<cMixMode*,SP_STL_Sound>::DoInsertValue(pos, value)
void SoundVector::VectorInsert(u32* pos, const u32* value)
{
    u32* begin = mBegin;
    u32* end   = mEnd;
    u32* cap   = mCap;
    if (end != cap) {
        const u32* v = value;
        if (pos <= v && v < end)
            ++v;
        if (end)
            *end = end[-1];
        memmove(pos + 1, pos, (u32) (end - pos - 1) * 4);
        *pos = *v;
        mEnd = end + 1;
        return;
    }
    u32 count  = (u32) (end - begin);
    u32 newCap = count ? count * 2 : 1;
    u32* dst = (u32*) EAAllocate(newCap * 4, (const char*) (size_t) 0x13f09b4, 0, 0,
                                 (int) 0x13ebb38, 0xd1);
    u32 at = (u32) (pos - begin);
    u32* slot = (u32*) FUN_011e0744(dst, begin, at * 4) + at;
    if (slot)
        *slot = *value;
    u32* newEnd = (u32*) FUN_011e0744(slot + 1, pos, (u32) (end - pos) * 4) + (u32) (end - pos);
    if (begin)
        operator_delete(begin);
    mBegin = dst;
    mEnd = newEnd;
    mCap = dst + newCap;
}

// ---------------------------------------------------------------------------
// @ 0x00ea9550

static void ConfigureVector(SoundVector* v, void* cfg, u32 id)
{
    u32 cnt = 0, arr = 0;
    v->mEnd = v->mBegin;
    if (cfg == 0)
        return;
    if (!((Fnb1u) VT(cfg, 0x4c))(cfg, id, &cnt, &arr) || cnt == 0)
        return;
    FUN_00eade60((void*) (size_t) cnt);
    for (u32 i = 0; i < cnt; ++i) {
        u32 val = *(u32*) (arr + i * 0xc);
        if (v->mEnd < v->mCap)
            *v->mEnd++ = val;
        else
            v->VectorInsert(v->mEnd, &val);
    }
}

void cMixMode::ConfigurePrimitive()
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

// ---------------------------------------------------------------------------
// @ 0x00ea9790
bool __stdcall IsMixableKey(u32 obj)
{
    return *(int*) (obj + 4) == 0x497925e;
}

// ---------------------------------------------------------------------------
// @ 0x00ea9880  cMixModeManager::UpdateSounds(float dt) -- walk the mSounds tree.
void cMixModeManager::UpdateSounds(float dt)
{
    SoundNode** bucket = mSounds.mpBucketArray;
    SoundNode* node = *bucket;
    while (node == 0)
        node = *++bucket;
    SoundNode* last = mSounds.mpBucketArray[mSounds.mnBucketCount];
    while (node != last) {
        if (node->refCount == 0) {
            node->fSecsSinceStop += dt;
            if (node->fSecsSinceStop > 0.5f) {
                void* sys = GetSystemAT();
                if (sys != 0) {
                    ((Fn1u) VT(sys, 0x38))(sys, 0x347536bu);
                    ((Fn2u) VT(sys, 0x40))(sys, 0x3475385u, node->instanceId);
                    ((Fn2u) VT(sys, 0x40))(sys, 0x34753a0u, 0);
                    ((Fn0)  VT(sys, 0x58))(sys);
                }
                u32 inst = node->instanceId;
                sys = GetSystemAT();
                if (sys != 0)
                    ((Fn1u) VT(sys, 0x2c))(sys, inst);
                SoundIterator next = mSounds.erase(SoundIterator(node, bucket));
                node = next.mpNode;
                bucket = next.mpBucket;
            } else {
                node = node->mpNext;
                while (node == 0)
                    node = *++bucket;
            }
        } else {
            node = node->mpNext;
            while (node == 0)
                node = *++bucket;
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ea99a0  cMixModeManager::RemoveSound(unsigned int id, bool flag)
void cMixModeManager::RemoveSound(u32 id, bool flag)
{
    SoundIterator it = mSounds.find(id);
    if (mSounds.end_node() == it.mpNode)
        return;
    if (--it.mpNode->refCount != 0)
        return;
    if (flag) {
        FUN_00572020((int) it.mpNode->instanceId, 1);
        void* sys = GetSystemAT();
        if (sys != 0)
            ((Fn1u) VT(sys, 0x2c))(sys, it.mpNode->instanceId);
        mSounds.erase(it);
    } else {
        it.mpNode->fSecsSinceStop = 0.0f;
        PauseSound(it.mpNode->instanceId, 1);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ea9a40  cMixModeManager::StartMode(unsigned int id)
void cMixModeManager::StartMode(u32 id)
{
    ModeIterator it = mModes.find(id);
    if (mModes.end_node() != it.mpNode)
        it.mpNode->second->Start();
}

// ---------------------------------------------------------------------------
// @ 0x00ea9a80  cMixModeManager::StopMode(unsigned int id, bool flag)
void cMixModeManager::StopMode(u32 id, bool flag)
{
    ModeIterator it = mModes.find(id);
    if (mModes.end_node() != it.mpNode)
        it.mpNode->second->Stop(flag);
}

// ---------------------------------------------------------------------------
// @ 0x00ea9ac0  cMixModeManager::IsModeActive(unsigned int id)
bool cMixModeManager::IsModeActive(u32 id)
{
    ModeIterator it = mModes.find(id);
    if (mModes.end_node() == it.mpNode)
        return false;
    return it.mpNode->second->IsRunning();
}

// ---------------------------------------------------------------------------
// @ 0x00ea9b00  cMixModeManager::RegisterSound(unsigned int id)
void cMixModeManager::RegisterSound(u32 id)
{
    SoundIterator it = mSounds.find(id);
    if (it.mpNode != mSounds.end_node()) {
        if (++it.mpNode->refCount == 1)
            PauseSound(it.mpNode->instanceId, 0);
        return;
    }

    void* sys = GetSystemAT();
    u32 handle = 0;
    if (sys != 0)
        handle = ((Fnu0) VT(sys, 0x24))(sys);
    KillSetiEffects((void*) (size_t) id, (void*) (size_t) handle);

    SoundNode value;
    value.key = id;
    value.instanceId = handle;
    value.refCount = 1;
    SoundIterator out;
    mSounds.insert(&out, &value, id & 0xffffff00u);
}

// ---------------------------------------------------------------------------
// @ 0x00ea9bb0  MessageModeMap::find(const u32&) const
KeyModePair* MessageModeMap::find(const u32& key) const
{
    KeyModePair* end = mpEnd;
    KeyModePair* it = (KeyModePair*) LowerBoundPair(mpBegin, end, (void*) &key, (unsigned char) mFlag14);
    if (it == end || key < it->first || it == it + 1)
        it = end;
    return it;
}

// ---------------------------------------------------------------------------
// @ 0x00ea9c20
void* cFactoryMixMode::scalar_deleting_destructor(unsigned char flags)
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

// ---------------------------------------------------------------------------
// @ 0x00ea9c70
void cMixModeManager::Shutdown()
{
    // 1) stop every mix mode still registered in mModes
    ModeNode** bucket = mModes.mpBucketArray;
    ModeNode* node = *bucket;
    while (node == 0)
        node = *++bucket;
    ModeNode* last = mModes.mpBucketArray[mModes.mnBucketCount];
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
        void* sys = GetSystemAT();
        if (sys != 0) {
            ((Fn1u) VT(sys, 0x38))(sys, 0x347536bu);
            ((Fn2u) VT(sys, 0x40))(sys, 0x3475385u, snode->instanceId);
            ((Fn2u) VT(sys, 0x40))(sys, 0x34753a0u, 0);
            ((Fn0)  VT(sys, 0x58))(sys);
            sys = GetSystemAT();
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

}  // namespace Audio
}  // namespace SP
