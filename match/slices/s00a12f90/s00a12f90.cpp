// Slice s00a12f90 -- EA::Audio property/aggregate hash-table methods on Group,
// ResourceVoiceTemplate::ConstructVoice and EmitterSndPlayer::CreateVoice.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------------------
// eastl-style hash table node / iterator / table (retail layout, see s00a13fc0)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// external callees (retail VAs in comments; bodies live in other slices)
// ---------------------------------------------------------------------------
void* __cdecl FUN_00a206f0();                          // 0x00a206f0 EA::Audio::GetSystemAT
void* __cdecl EAAllocate(u32 size, const char* name, int flags, int align,
                         const char* file, int line);  // 0x00f473a0
void  __cdecl FUN_00a136f0(void* table, const void* pair, int unused);  // 0x00a136f0 node insert
void* __cdecl FUN_00a17090(u32 size);                  // 0x00a17090 operator new
void* __cdecl FUN_00a17100(void* mem, void* owner);// 0x00a17100 construct property
void  __cdecl FUN_00a16fd0(void* self, float value);// 0x00a16fd0 set value
void  __cdecl FUN_00fccdd0(void* self, u32 id);     // 0x00fccdd0 set id
void* __cdecl FUN_00a34cb0(void* a, void* b, void* c, void* d, void* e); // AddPropertyBinding
void* __cdecl FUN_00b85500(void* a, void* b);          // 0x00b85500 vector reset
void* __cdecl eastl_vec_erase(void* self, void* first, void* last);      // 0x009e0480
void* __cdecl eastl_vec_insert(void* pos, void* last, void* value);      // 0x011e0744
void* __cdecl eastl_push_4(void* pos, void* value);    // 0x00899480
void* __cdecl eastl_push_c(void* pos, void* value);    // 0x0060a600
void* __cdecl FUN_0112ce00();                          // 0x0112ce00 VoiceList::getOrCreate
void* __cdecl FUN_0112cd30(u32 id);                    // 0x0112cd30 NodeList::find
void  __cdecl FUN_0112c600();                          // 0x0112c600 System::Lock
void  __cdecl FUN_0112c620();                          // 0x0112c620 System::Unlock
void  __cdecl FUN_00a34d70(void* self, void* v);    // 0x00a34d70
void  __cdecl FUN_00a11350(void* self);             // 0x00a11350
bool  __cdecl VoiceContainer_Create(void* self, int flag); // 0x00a342c0
void* __cdecl FindPlugin(void* self, u32 id);       // 0x00a34230
extern void* DAT_016e61a8;                             // 0x016e61a8 System lock

// ===========================================================================
// EA::Audio::Group
// ===========================================================================
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

// @ 0x00a13840
bool Group::DisconnectPrimitive(u32 id, void* prim)
{
    PHTable* t = &mAggregates;
    HashIter it = t->find(id);
    if (it.node == t->mpBuckets[t->mnBucketCount])
        return false;

    void* reg = it.node->value;
    void** sub = (void**)((char*)reg + 4);
    ((void (__thiscall*)(void*, void*))(*(void***)sub)[5])(sub, prim);
    if (((int (__thiscall*)(void*))(*(void***)sub)[6])(sub) == 0) {
        ((void (__thiscall*)(void*, int))(*(void***)reg)[11])(reg, 0);

        PHTable* mt = &mMixees;
        it = mt->begin();
        PHNode* n = it.node;
        PHNode** bucket = it.bucket;
        PHNode* end = mt->mpBuckets[mt->mnBucketCount];
        while (n != end) {
            void* v = n->value;
            ((void (__thiscall*)(void*, void*, void*))(*(void***)v)[7])(v, prim, reg);
            n = n->next;
            if (!n) { do { n = *++bucket; } while (!n); }
        }
    }
    return true;
}

// @ 0x00a138f0
bool Group::Subscribe(void* m)
{
    u32 id = ((u32 (__thiscall*)(void*))(*(void***)m)[2])(m);
    PHTable* t = &mMixees;
    HashIter it = t->find(id);
    if (it.node == t->mpBuckets[t->mnBucketCount])
        return false;

    ((void (__thiscall*)(void*))(*(void***)m)[0])(m);
    struct Pair { u32 key; void* value; } pair;
    pair.key = id;
    pair.value = m;
    ((void (__thiscall*)(void*))(*(void***)m)[0])(m);
    FUN_00a136f0(t, &pair, 0);
    ((void (__thiscall*)(void*))(*(void***)m)[0])(m);

    // tell every aggregate that a mixee subscribed
    PHNode** b = mAggregates.mpBuckets;
    PHNode* n = b[0];
    if (!n) { ++b; while (!*b) ++b; n = *b; }
    PHNode* end = mAggregates.mpBuckets[mAggregates.mnBucketCount];
    while (n != end) {
        void* v = n->value;
        if (((int (__thiscall*)(void*))(*(void***)v)[6])(v) != 0) {
            void* vv = *(void**)v;
            ((void (__thiscall*)(void*, void*))(*(void***)m)[6])(m, ((void* (__thiscall*)(void*))(*(void***)v)[6])(v));
            (void)vv;
        }
        n = n->next;
        if (!n) { do { n = *++b; } while (!n); }
    }

    // push the current value of every registered property to the new mixee
    PHNode** rb = mRegisters.mpBuckets;
    PHNode* rn = rb[0];
    if (!rn) { ++rb; while (!*rb) ++rb; rn = *rb; }
    PHNode* rend = mRegisters.mpBuckets[mRegisters.mnBucketCount];
    while (rn != rend) {
        void* v = rn->value;
        void* sys = FUN_00a206f0();
        u32 key = ((u32 (__thiscall*)(void*))(*(void***)v)[6])(v);
        if (((void* (__thiscall*)(void*, u32))(*(void***)sys)[0xf8 / 4])(sys, key) == 0) {
            float f = ((float (__thiscall*)(void*, int))(*(void***)v)[7])(v, 1);
            ((void (__thiscall*)(void*, u32, float))(*(void***)m)[3])(m, key, f);
        }
        rn = rn->next;
        if (!rn) { do { rn = *++rb; } while (!rn); }
    }

    if (mPauseCount != 0)
        ((void (__thiscall*)(void*, u32, float, int))(*(void***)m)[3])(m, 0xb85523e5, 1.0f, 1);
    return true;
}

// @ 0x00a13b40
bool Group::Unsubscribe(void* m)
{
    u32 id = ((u32 (__thiscall*)(void*))(*(void***)m)[2])(m);
    PHTable* t = &mMixees;
    HashIter it = t->find(id);
    if (it.node == t->mpBuckets[t->mnBucketCount])
        return false;
    t->erase(it);

    PHTable* at = &mAggregates;
    PHNode** b = at->mpBuckets;
    PHNode* n = b[0];
    if (!n) { ++b; while (!*b) ++b; n = *b; }
    PHNode* end = at->mpBuckets[at->mnBucketCount];
    while (n != end) {
        void* v = n->value;
        u32 key = ((u32 (__thiscall*)(void*))(*(void***)v)[6])(v);
        ((void (__thiscall*)(void*, u32))(*(void***)m)[7])(m, key);
        n = n->next;
        if (!n) { do { n = *++b; } while (!n); }
    }

    if (mPauseCount > 0)
        ((void (__thiscall*)(void*, u32, float, int))(*(void***)m)[3])(m, 0xb85523e5, 0.0f, 1);
    return true;
}

// @ 0x00a13c40
bool Group::Empty(u32 id, void* m)
{
    PHTable* t = &mMixees;
    HashIter it = t->find(id);
    if (it.node == t->mpBuckets[t->mnBucketCount])
        return false;

    ((void (__thiscall*)(void*))(*(void***)m)[0])(m);
    struct Pair { u32 key; void* value; } pair;
    pair.key = ((u32 (__thiscall*)(void*))(*(void***)m)[2])(m);
    ((void (__thiscall*)(void*))(*(void***)m)[0])(m);
    pair.value = m;
    FUN_00a136f0(t, &pair, 0);
    t->erase(it);
    return true;
}

// @ 0x00a13d50
void Group::SetProperty(u32 id, float value, bool flag)
{
    if (value != value)          // NaN is rejected
        return;

    if (id == 0xb85523e5) {
        Pause(value != 0.0f);
        return;
    }

    PHTable* t = &mRegisters;
    HashIter it = t->find(id);
    if (it.node != t->mpBuckets[t->mnBucketCount]) {
        FUN_00a16fd0(it.node->value, value);
        return;
    }

    void* mem = FUN_00a17090(0x1c);
    void* p = 0;
    if (mem)
        p = FUN_00a17100(mem, this);
    ((void (__thiscall*)(void*))(*(void***)p)[4])(p);
    FUN_00fccdd0(p, id);
    FUN_00a16fd0(p, value);
    ((void (__thiscall*)(void*))(*(void***)p)[0])(p);

    struct Pair { u32 key; void* value; } pair;
    pair.key = id;
    pair.value = p;
    FUN_00a136f0(t, &pair, 0);

    void* sys = FUN_00a206f0();
    if (((void* (__thiscall*)(void*, u32))(*(void***)sys)[0xf8 / 4])(sys, id) != 0) {
        ((void (__thiscall*)(void*, u32, void*))(*(void***)this)[6])(this, id, p);
        return;
    }

    PHTable* mt = &mMixees;
    HashIter bit = mt->begin();
    PHNode* n = bit.node;
    PHNode** bucket = bit.bucket;
    PHNode* end = mt->mpBuckets[mt->mnBucketCount];
    while (n != end) {
        void* v = n->value;
        float f = ((float (__thiscall*)(void*, int))(*(void***)p)[7])(p, 1);
        ((void (__thiscall*)(void*, u32, float))(*(void***)v)[3])(v, id, f);
        n = n->next;
        if (!n) { do { n = *++bucket; } while (!n); }
    }
}

// ===========================================================================
// 0x00a135c0 -- allocate and initialise one hash node from a {key,value} pair
// ===========================================================================
struct NodePair { u32 key; void* value; };

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

// ===========================================================================
// EA::Audio::ResourceVoiceTemplate / EmitterSndPlayer
// ===========================================================================
namespace EA {
namespace Audio {

struct ResourceVoiceTemplate {
    void* mVtbl;             // +0x00
    char  pad04[0x10];
    void* mPluginBegin;      // +0x14
    void* mPluginEnd;        // +0x18
    char  pad1c[0x194 - 0x1c];
    void* mBindBegin;        // +0x194
    void* mBindEnd;          // +0x198

    bool ConstructVoice(int mode, void* voice);   // 0x00a12f90
};

// @ 0x00a12f90
bool ResourceVoiceTemplate::ConstructVoice(int mode, void* voice)
{
    char* p3 = (char*)voice;

    FUN_00b85500(*(void**)(p3 + 0x184), *(void**)(p3 + 0x188));
    eastl_vec_erase((void*)(p3 + 8), *(void**)(p3 + 8), *(void**)(p3 + 0xc));
    eastl_vec_insert(*(void**)(p3 + 0x8a0), *(void**)(p3 + 0x8a4), 0);
    eastl_vec_insert(*(void**)(p3 + 0x8cc), *(void**)(p3 + 0x8d0), 0);

    if (DAT_016e61a8 != 0)
        FUN_0112c600();                                   // System::Lock

    void* voiceObj = FUN_0112ce00();                      // VoiceList::getOrCreate
    if (voiceObj == 0) {
        if (DAT_016e61a8 != 0)
            FUN_0112c620();                               // System::Unlock
        return false;
    }

    bool one = (mode == 1);
    int n = (int)(((char*)mPluginEnd - (char*)mPluginBegin) / 0xc);
    for (int i = 0; i < n; ++i) {
        u32* plugin = (u32*)((char*)mPluginBegin + i * 0xc);

        if (plugin[0] == 0x53656e30)                      // 'Sen0'
            eastl_push_4(*(void**)(p3 + 0x8a0), (void*)plugin[2]);

        bool skip = false;
        if (plugin[0] == 0x506e3230) {                    // 'Pn20'
            if (one) {
                skip = true;
            } else {
                void* sys = FUN_00a206f0();
                mode = ((int (__thiscall*)(void*))(*(void***)sys)[0xbc / 4])(sys);
            }
        } else if (plugin[0] == 0x506e3231) {             // 'Pn21'
            void* sys = FUN_00a206f0();
            mode = ((int (__thiscall*)(void*))(*(void***)sys)[0xbc / 4])(sys);
        }

        if (skip)
            continue;

        void* node = FUN_0112cd30(plugin[0]);             // NodeList::find
        if (node == 0) {
            if (DAT_016e61a8 != 0)
                FUN_0112c620();
            return false;
        }

        // append a default PlugInConfig to the voice's config vector (stride 0xc)
        void* cfgEnd = *(void**)(p3 + 0xc);
        if (cfgEnd < *(void**)(p3 + 0x10)) {
            *(void**)(p3 + 0xc) = (char*)cfgEnd + 0xc;
            if (cfgEnd) {
                ((u32*)cfgEnd)[0] = 0;
                ((u32*)cfgEnd)[1] = 0;
                ((u32*)cfgEnd)[2] = 0;
            }
        } else {
            struct PlugInConfig { u32 a, b, c; } def = { 0, 0, 0 };
            eastl_vec_insert(cfgEnd, 0, &def);
        }

        eastl_push_c(*(void**)(p3 + 0x8cc), (void*)plugin[1]);

        u32* cfg = (u32*)((char*)*(void**)(p3 + 0xc) - 0xc);
        cfg[0] = 0;
        cfg[1] = (u32)node;
        cfg[2] = (plugin[0] == 0x44616330) ? (u8)(mode & 0xff) : 0;
    }

    int nb = (int)(((char*)mBindEnd - (char*)mBindBegin) / 0x18);
    for (int i = 0; i < nb; ++i) {
        u32* bind = (u32*)((char*)mBindBegin + i * 0x18);
        u32 pluginId = bind[3];
        if (pluginId == 0x506e3230 && !one)
            continue;
        void* opt = (bind[5] & 1) ? (void*)(bind + 2) : 0;
        FUN_00a34cb0((void*)bind[0], (void*)pluginId, (void*)bind[4], (void*)bind[1], opt);
    }

    if (DAT_016e61a8 != 0)
        FUN_0112c620();
    return true;
}

struct EmitterSndPlayer {
    char  pad000[0x374];
    void* mName;             // +0x374
    char  pad378[0x38c - 0x378];
    char  mVoice[0xd10 - 0x38c];   // +0x38c voice-data sub-object
    int   mStartTime;        // +0xd10
    char  padD14[0xd24 - 0xd14];
    int   mPitch;            // +0xd24
    char  padD28[0xd6c - 0xd28];
    void* mpPluginA;         // +0xd6c
    void* mpPluginB;         // +0xd70
    void* mpPluginC;         // +0xd74
    void* mpPluginD;         // +0xd78
    void* mpPluginE;         // +0xd80
    u32   mFlags;            // +0xd84

    bool CreateVoice();      // 0x00a13300
};

// @ 0x00a13300
bool EmitterSndPlayer::CreateVoice()
{
    if (mName == 0)
        return false;
    if (!((char (__thiscall*)(void*, u32))(*(void***)mName)[0x18 / 4])(mName, 0x544e850b))
        return false;

    u32 name0[3] = { 0, 0, 0 };
    ((void (__thiscall*)(void*, u32, void*))(*(void***)mName)[0x34 / 4])(mName, 0x544e850b, name0);
    u32 key[2] = { 0x29e333b, 0x21407ee };

    void* handle = 0;
    void* sys = FUN_00a206f0();
    if (handle)
        ((void (__thiscall*)(void*))(*(void***)handle)[1])(handle);
    if (!((char (__thiscall*)(void*, void*, void*))(*(void***)sys)[0x18c / 4])(sys, key, &handle)) {
        if (handle)
            ((void (__thiscall*)(void*))(*(void***)handle)[1])(handle);
        return false;
    }

    mFlags |= 0x10;
    if (!((ResourceVoiceTemplate*)mVoice)->ConstructVoice(mStartTime, mVoice)) {
        if (handle)
            ((void (__thiscall*)(void*))(*(void***)handle)[1])(handle);
        return false;
    }

    if (((char (__thiscall*)(void*, u32))(*(void***)mName)[0x18 / 4])(mName, 0x2fe09c83)) {
        void* p = ((void* (__thiscall*)(void*, u32))(*(void***)mName)[0x3c / 4])(mName, 0x2fe09c83);
        if (p) {
            void* sys2 = FUN_00a206f0();
            void* h = ((void* (__thiscall*)(void*, void*))(*(void***)sys2)[0xf0 / 4])(sys2, p);
            FUN_00a34d70(mVoice, h);
        }
    }

    if (*(void**)(mVoice + 8) == *(void**)(mVoice + 0xc)) {
        if (handle)
            ((void (__thiscall*)(void*))(*(void***)handle)[1])(handle);
        return false;
    }

    FUN_00a11350((char*)this + 0x13);
    VoiceContainer_Create(mVoice, 0);

    if (DAT_016e61a8 != 0)
        FUN_0112c620();                                   // System::Unlock

    ((void (__thiscall*)(void*, int))(*(void***)this)[0x7c / 4])(this, mPitch);

    mpPluginA = FindPlugin(mVoice, 0x536e5031);
    mpPluginB = FindPlugin(mVoice, 0x52737030);

    void* chain = *(void**)(mVoice + 4);
    if (chain) {
        int cnt = (int)(((char*)*(void**)(mVoice + 0xc) - (char*)*(void**)(mVoice + 8)) / 0xc);
        mpPluginC = *(void**)((char*)chain + cnt * 4 - 4);
    }

    mpPluginD = FindPlugin(mVoice, 0x54537430);
    mpPluginE = FindPlugin(mVoice, 0x50617530);

    bool ok = (mpPluginA != 0);
    if (handle)
        ((void (__thiscall*)(void*))(*(void***)handle)[1])(handle);
    return ok;
}

}  // namespace Audio
}  // namespace EA
