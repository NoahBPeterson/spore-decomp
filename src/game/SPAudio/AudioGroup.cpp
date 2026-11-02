// src/game/SPAudio/AudioGroup.cpp -- migrated from slice(s) s00ea8f90, s00a13fc0, s00a12f90 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioGroup.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/Group.h"
#include "EA/Audio/ResourceVoiceTemplate.h"
#include <stdlib.h>
#include <string.h>
#include <new>
#include "SP/Audio/cMixMode.h"

// ---- items of slice s00a12f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
struct PHNode { u32 hash; void* value; PHNode* next; };   // 12 bytes
struct HashIter { PHNode* node; PHNode** bucket; };
struct NodePair;                                          // {u32 key; void* value;}
struct PHTable {
    u32      m00;              // +0x00
    PHNode** mpBuckets;        // +0x04
    u32      mnBucketCount;    // +0x08
    u32      mnElementCount;   // +0x0c
    u32      m10, m14, m18;    // +0x10
    PHNode*  mpFreeList;       // +0x1c
    u32      m20;              // +0x20
    void*    mpPoolBegin;      // +0x24
    void*    mpPoolEnd;        // +0x28
    u32      m2c;              // +0x2c
    void*    mpInline;         // +0x30

    HashIter find(const u32& key) const;   // 0x00645ed0
    HashIter begin() const;                // 0x00594410
    HashIter erase(HashIter it);           // 0x00d2c9f0

    PHNode* AllocNode(const NodePair* pair);   // 0x00a135c0
};
void* __cdecl EAAllocate(u32 size, const char* name, int flags, int align,
                         const char* file, int line);  // 0x00f473a0
struct Group {
    void* mVtbl;             // +0x00
    void* mRefVtbl;          // +0x04
    int   mRefCount;         // +0x08
    u32   mId;               // +0x0c
    u32   mPauseCount;       // +0x10
    PHTable mMixees;         // +0x14   (region 0xff0 bytes)
    char    mixPad[0xff0 - sizeof(PHTable)];
    PHTable mRegisters;      // +0x1004 (region 0x438 bytes)
    char    regPad[0x438 - sizeof(PHTable)];
    PHTable mAggregates;     // +0x143c (region 0x438 bytes)
    char    aggPad[0x438 - sizeof(PHTable)];

    void Pause(bool pause);                        // 0x00a13650
    bool GetProperty(u32 id, float& out);          // 0x00a137b0
    bool HasProperty(u32 id);                      // 0x00a13800
    bool DisconnectPrimitive(u32 id, void* prim);  // 0x00a13840
    bool Subscribe(void* m);                       // 0x00a138f0
    bool Unsubscribe(void* m);                     // 0x00a13b40
    bool Empty(u32 id, void* m);                   // 0x00a13c40
    void SetProperty(u32 id, float value, bool flag);  // 0x00a13d50
};
struct NodePair { u32 key; void* value; };
// ---- items of slice s00a12f90 end

// ---- items of slice s00a13fc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SystemAT;
SystemAT* FUN_00a206f0();                      // EA::Audio::GetSystemAT
void* FUN_00a16ad0(u32 size);
int   FUN_00a16d00(void* mem, int id);
void  FUN_00a16a30(void* self, void* server);
void  FUN_00a16a90(void* self, void* v);
void  FUN_00a136f0(void* out, void* key, int unused);
struct PHTable_s00a1_3fc0 {
    u32      m00;
    PHNode** mpBuckets;        // +0x04
    u32      mnBucketCount;    // +0x08
    u32      mnElementCount;   // +0x0c
    u32      m10;
    u32      m14;
    u32      m18;
    PHNode*  mpFreeList;       // +0x1c
    u32      m20;
    void*    mpPoolBegin;      // +0x24
    void*    mpPoolEnd;        // +0x28
    u32      m2c;
    void*    mpInline;         // +0x30

    void FreeBuckets(PHNode** buckets, u32 count);  // 0x00a24480 (PHTable::FreeBuckets)
    ~PHTable_s00a1_3fc0();
};
PHTable_s00a1_3fc0::~PHTable_s00a1_3fc0()
{
    FreeBuckets(mpBuckets, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1 && mpBuckets != (PHNode**)mpInline) {
        if ((char*)mpBuckets < (char*)mpPoolBegin || (char*)mpPoolEnd <= (char*)mpBuckets)
            operator delete(mpBuckets);
        else {
            *(void**)mpBuckets = mpFreeList;
            mpFreeList = (PHNode*)mpBuckets;
        }
    }
}
struct FHT1 {
    PHTable_s00a1_3fc0 mTable;                              // +0x00
    char    mPad[0xff0 - sizeof(PHTable_s00a1_3fc0)];
    FHT1() {}
    FHT1(unsigned& a, unsigned& b);
};
struct HTable28 {
    PHTable_s00a1_3fc0 mTable;                              // +0x00
    char    mPad[0x438 - sizeof(PHTable_s00a1_3fc0)];
    HTable28() {}
    __declspec(noinline) HTable28(unsigned& a, unsigned& b);
};
struct MixableBase {
    void* mVtbl;
};
struct RefCountBase {
    void* mRefVtbl;
    ~RefCountBase() { mRefVtbl = (void*)0x13ef094; }
};
struct Group_s00a1_3fc0 : MixableBase, RefCountBase {
    int       mRefCount;     // +0x08
    u32       mId;           // +0x0c
    u32       mPauseCount;   // +0x10
    FHT1      mMixees;       // +0x14
    HTable28  mRegisters;    // +0x1004
    HTable28  mAggregates;   // +0x143c

    Group_s00a1_3fc0(u32 id);
    bool ConnectPrimitive(u32 id, void* prim);
    bool Shutdown();
    ~Group_s00a1_3fc0();
};
// ---- items of slice s00a13fc0 end

// ---- items of slice s00ea8f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable: 4100)
void* __cdecl  GetSystemAT();                          // 0x00a206f0  EA::Audio::GetSystemAT
bool  __cdecl  PauseSound(u32, int);                   // 0x00a37290
void  __cdecl  FUN_00572020(int, int);                 // 0x00572020
static inline void* VT(void* obj, int off) { return ((void**) (*(void**) obj))[off / 4]; }
typedef void  (__thiscall *Fn1u)(void*, u32);
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
struct ModeNode {
    u32        first;    // +0x00 key
    cMixMode_s00ea_8f90*  second;   // +0x04 value
    ModeNode*  mpNext;   // +0x08
};
}
}
namespace SP {
namespace Audio {
struct ModeIterator {
    ModeNode*  mpNode;       // +0x00
    ModeNode** mpBucket;     // +0x04
    ModeIterator() {}        // non-trivial: returned via hidden pointer (as eastl does)
    ModeNode* operator->() const { return mpNode; }
};
}
}
namespace SP {
namespace Audio {
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

// @ 0x00a135c0
PHNode* PHTable::AllocNode(const NodePair* p)
{
    PHNode* n = mpFreeList;
    if (n == 0) {
        n = (PHNode*)EAAllocate(m2c, "EASTL", 0, 0,
                                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                0xd1);
    } else {
        mpFreeList = (PHNode*)n->hash;
    }
    if (n) {
        n->hash = p->key;
        n->value = p->value;
        if (n->value)
            ((void (__thiscall*)(void*))(*(void***)n->value)[0])(n->value);
    }
    n->next = 0;
    return n;
}

// @ 0x00a13650
void Group::Pause(bool pause)
{
    u32 count = mPauseCount;
    bool changed = (pause && count == 0) || (!pause && count == 1);
    if (pause) { ++count; mPauseCount = count; }
    else if (count > 0) { --count; mPauseCount = count; }
    if (changed) {
        PHNode** bucket = mMixees.mpBuckets;
        PHNode* n = bucket[0];
        if (!n) { ++bucket; while (!*bucket) ++bucket; n = *bucket; }
        // The volatile read of the bucket count stops MSVC from caching
        // mpBuckets; retail reloads mMixees.mpBuckets to form the end pointer.
        u32 nb = ((volatile PHTable&)mMixees).mnBucketCount;
        PHNode** bp = mMixees.mpBuckets;
        PHNode* end = bp[nb];
        while (n != end) {
            void* v = n->value;
            ((void (__thiscall*)(void*, u32, float, int))(*(void***)v)[3])(v, 0xb85523e5, (float)pause, 1);
            n = n->next;
            if (!n) { do { n = *++bucket; } while (!n); }
        }
    }
}

// @ 0x00a137b0
bool Group::GetProperty(u32 id, float& out)
{
    PHTable* t = &mRegisters;
    HashIter it = t->find(id);
    if (it.node == t->mpBuckets[t->mnBucketCount])
        return false;
    void* v = it.node->value;
    out = ((float (__thiscall*)(void*))(*(void***)v)[7])(v);
    return true;
}

// @ 0x00a13800
bool Group::HasProperty(u32 id)
{
    PHTable* t = &mRegisters;
    PHNode* end = t->mpBuckets[t->mnBucketCount];
    return t->find(id).node != end;
}

// @ 0x00a13fc0
bool Group_s00a1_3fc0::ConnectPrimitive(u32 id, void* prim)
{
    SystemAT* sys = FUN_00a206f0();
    void* handle = ((void* (__thiscall*)(SystemAT*, u32))(*(void***)sys)[0xf8 / 4])(sys, id);
    if (handle == 0)
        return false;

    PHNode** b = mAggregates.mTable.mpBuckets;
    PHNode* n = b[0];
    unsigned bi = 0;
    if (!n) {
        do { n = b[++bi]; } while (!n);
    }
    PHNode* end = b[mAggregates.mTable.mnBucketCount];
    void* obj;
    if (n != end) {
        obj = n->value;
        if (obj) {
            ((void (__thiscall*)(void*))(*(void***)obj)[0x00 / 4])(obj);
        }
        ((void (__thiscall*)(void*, void*))(*(void***)obj)[0x10 / 4])(obj, prim);
    } else {
        void* mem = FUN_00a16ad0(0x6c);
        obj = 0;
        if (mem)
            obj = (void*)FUN_00a16d00(mem, id);
        if (obj) {
            ((void (__thiscall*)(void*))(*(void***)obj)[0x00 / 4])(obj);
        }
        FUN_00a16a30(obj, handle);
        FUN_00a16a90(obj, handle);
        ((void (__thiscall*)(void*, void*))(*(void***)obj)[0x10 / 4])(obj, prim);
        ((void (__thiscall*)(void*))(*(void***)obj)[0x10 / 4])(obj);
        FUN_00a136f0(&mAggregates, &id, 0);
    }

    int r = ((int (__thiscall*)(void*))(*(void***)obj)[0x18 / 4])(obj);
    if (r == 1) {
        ((void (__thiscall*)(void*, int))(*(void***)obj)[0x2c / 4])(obj, 1);
        PHNode** b2 = mMixees.mTable.mpBuckets;
        PHNode* n2 = b2[0];
        unsigned bi2 = 0;
        if (!n2) {
            do { n2 = b2[++bi2]; } while (!n2);
        }
        PHNode* end2 = b2[mMixees.mTable.mnBucketCount];
        while (n2 != end2) {
            void* v = n2->value;
            ((void (__thiscall*)(void*, void*))(*(void***)v)[0x18 / 4])(v, obj);
            n2 = n2->next;
            if (!n2) { do { n2 = b2[++bi2]; } while (!n2); }
        }
    }
    ((void (__thiscall*)(void*))(*(void***)obj)[0x04 / 4])(obj);
    return true;
}

// @ 0x00a141c0
bool Group_s00a1_3fc0::Shutdown()
{
    // 1. ask every mixee to disconnect
    PHNode** b = mMixees.mTable.mpBuckets;
    PHNode* n = b[0];
    unsigned bi = 0;
    if (!n) {
        do { n = b[++bi]; } while (!n);
    }
    PHNode* end = b[mMixees.mTable.mnBucketCount];
    while (n != end) {
        u32 key = n->hash;
        n = n->next;
        if (!n) { do { n = b[++bi]; } while (!n); }
        ((void (__thiscall*)(Group_s00a1_3fc0*, u32))(*(void***)this)[0x2c / 4])(this, key);
    }

    // 2. release registers that point back at this group
    b = mRegisters.mTable.mpBuckets;
    n = b[0];
    bi = 0;
    if (!n) {
        do { n = b[++bi]; } while (!n);
    }
    end = b[mRegisters.mTable.mnBucketCount];
    while (n != end) {
        void* v = n->value;
        if (((void* (__thiscall*)(void*))(*(void***)v)[0x30 / 4])(v) == this)
            ((void (__thiscall*)(void*))(*(void***)v)[0x14 / 4])(v);
        n = n->next;
        if (!n) { do { n = b[++bi]; } while (!n); }
    }
    mRegisters.mTable.FreeBuckets(mRegisters.mTable.mpBuckets, mRegisters.mTable.mnBucketCount);
    mRegisters.mTable.mnElementCount = 0;

    // 3. release the remaining aggregates
    b = mAggregates.mTable.mpBuckets;
    n = b[0];
    bi = 0;
    if (!n) {
        do { n = b[++bi]; } while (!n);
    }
    end = b[mAggregates.mTable.mnBucketCount];
    while (n != end) {
        void* v = n->value;
        ((void (__thiscall*)(void*))(*(void***)v)[0x14 / 4])(v);
        n = n->next;
        if (!n) { do { n = b[++bi]; } while (!n); }
    }
    mAggregates.mTable.FreeBuckets(mAggregates.mTable.mpBuckets, mAggregates.mTable.mnBucketCount);
    mAggregates.mTable.mnElementCount = 0;
    return true;
}

// @ 0x00ea99a0
namespace SP { namespace Audio {
void cMixModeManager_s00ea_8f90::RemoveSound(u32 id, bool flag)
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
}}  // namespace SP::Audio
