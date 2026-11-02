// src/game/SPAudio/_at_00ea0000.cpp -- migrated from slice(s) s00ea8f90 by tools/migrate/rewrite.py
// Object file: SPAudio/_at_00ea0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Audio/cMixMode.h"
#include "SP/Audio/cMixModeManager.h"
#include <string.h>
#pragma warning(disable: 4100)

// ---- items of slice s00ea8f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
void* __cdecl  GetSystemAT();                          // 0x00a206f0  EA::Audio::GetSystemAT
void* __cdecl  KillSetiEffects(void*, void*);          // 0x00435ed0  (2-arg call site)
bool  __cdecl  PauseSound(u32, int);                   // 0x00a37290
static inline void* VT(void* obj, int off) { return ((void**) (*(void**) obj))[off / 4]; }
typedef void  (__thiscall *Fn0)(void*);
typedef void  (__thiscall *Fn1u)(void*, u32);
typedef void  (__thiscall *Fn2u)(void*, u32, u32);
typedef float (__thiscall *Fnf0)(void*);
typedef u32   (__thiscall *Fnu0)(void*);
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
namespace SP { namespace Audio { void ConfigureVector(SoundVector* v, void* cfg, u32 id); }}  // 0x00ea9550 (defined below; used by a stub's inline body)
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

// @ 0x00ea9790
namespace SP { namespace Audio {
bool __stdcall IsMixableKey(u32 obj)
{
    return *(int*) (obj + 4) == 0x497925e;
}
}}  // namespace SP::Audio

// @ 0x00ea9880
namespace SP { namespace Audio {
void cMixModeManager_s00ea_8f90::UpdateSounds(float dt)
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
}}  // namespace SP::Audio

// @ 0x00ea9b00
namespace SP { namespace Audio {
void cMixModeManager_s00ea_8f90::RegisterSound(u32 id)
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
}}  // namespace SP::Audio
