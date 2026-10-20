// Slice s009ca4b0: creature "block" ArgScript command registration and the
// nSPCreatureAnim::creature_effect helpers that live next to it, plus the EASTL
// fixed_hashtable / vector instantiations used by the creature effect table.
//
// Layouts are retail offsets read from the disassembly.  The generated header
// src/game/include/nSPCreatureAnim/creature_effect.h carries a dev-PDB layout
// (matrix_3x3 local_rot, size 0xb8) that does not match retail, so the real
// layout is reconstructed here (local_rot is a 16-byte quaternion, size 0xac).
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// =====================================================================
// allocation
// =====================================================================
void* __cdecl EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
inline void* operator new(unsigned int size, const char* name, int a, int b, int c, int d)
{
    return EAAllocate(size, name, a, b, c, d);
}
inline void* operator new(unsigned int, void* p) { return p; }
void __cdecl operator delete(void*);        // 0x00f47380

// =====================================================================
// EA::ArgScript command registration
// =====================================================================
namespace EA {
namespace ArgScript {

struct cIParser;
struct cState;
struct cArguments;

struct cICommand {
    virtual int AddRef();                       // +0x00
    virtual int Release();                      // +0x04
    virtual void* Cast(unsigned long type);     // +0x08
    virtual void ParseLine(void* line);         // +0x0c
    virtual void Execute(cArguments& args);     // +0x10
};

struct cCommandBase : cICommand {
    cIParser*   mParser;                // +0x04
    int         mRefCount;              // +0x08
    cCommandBase();                     // 0x0083c800
};

struct cIBlockCommand : cICommand {
    virtual cState* GetChildState();    // +0x14
};

struct cBlockCommandBase : cIBlockCommand {
    cIParser*     mParser;              // +0x04
    int           mRefCount;            // +0x08
    cState*       mChildState;          // +0x0c
    unsigned long mCommands[8];         // +0x10
    void OnRegister(cIParser* parser, cState* state);                  // 0x0083c780
    virtual void AddCommand(const char* keyword, cICommand* command);  // +0x18
};

template <typename T, typename Base> struct cCommandStateT : Base {
    T* mState;                          // block: +0x30, command: +0x0c
    cCommandStateT() {}
};
template <typename T> struct cCommandT : cCommandStateT<T, cCommandBase> {
    cCommandT() {}
};
template <typename T> struct cBlockCommandT : cCommandStateT<T, cBlockCommandBase> {
    cBlockCommandT() {}
};

}
}

using EA::ArgScript::cIParser;
using EA::ArgScript::cState;
using EA::ArgScript::cArguments;

namespace {

struct cBlockBlockState;                        // the creature-block parser state (the +0x30 member)

struct cBlockBlockCommand : EA::ArgScript::cBlockCommandT<cBlockBlockState> {
    void OnRegister(cIParser* parser, cState* state);
};

// One sub-command class per block field; each only overrides Execute.
#define BLOCK_COMMAND(Name)                                                       \
    struct c##Name##Command : EA::ArgScript::cCommandT<cBlockBlockCommand> {      \
        c##Name##Command() {}                                                      \
        virtual void Execute(cArguments& args);                                   \
    };

BLOCK_COMMAND(Name)
BLOCK_COMMAND(InstanceId)
BLOCK_COMMAND(Version)
BLOCK_COMMAND(ParentIndex)
BLOCK_COMMAND(SymmetricIndex)
BLOCK_COMMAND(JointPosition)
BLOCK_COMMAND(SubmeshIndex)
BLOCK_COMMAND(LeftHanded)
BLOCK_COMMAND(Cal3DBoneName)
BLOCK_COMMAND(Cal3DOrigin)
BLOCK_COMMAND(Position)
BLOCK_COMMAND(EffectsOrigin)
BLOCK_COMMAND(Orientation)
BLOCK_COMMAND(BBoxMin)
BLOCK_COMMAND(BBoxMax)
BLOCK_COMMAND(Mass)
BLOCK_COMMAND(Scale)
BLOCK_COMMAND(SoundIDFoot)
BLOCK_COMMAND(SoundIDMouth)
BLOCK_COMMAND(SoundIDWeapon)
BLOCK_COMMAND(Cap)
BLOCK_COMMAND(Deform)
}  // namespace

namespace BlockKeywords {
extern const char* name;                    // 0x01550fe4 "name"
extern const char* instanceId;              // 0x01550fe8
extern const char* version;                 // 0x01551020
extern const char* parentIndex;             // 0x01550ff8
extern const char* symmetricIndex;          // 0x01551018
extern const char* jointPosition;           // 0x01550fdc
extern const char* submeshIndex;            // 0x01551014
extern const char* leftHanded;              // 0x0155101c
extern const char* cal3DBoneName;           // 0x01550fd0
extern const char* cal3DOrigin;             // 0x01550fd4
extern const char* position;                // 0x01550ffc
extern const char* effectsOrigin;           // 0x01551000
extern const char* orientation;             // 0x01550ff4
extern const char* bBoxMin;                 // 0x01550fc0
extern const char* bBoxMax;                 // 0x01550fbc
extern const char* mass;                    // 0x01550fe0
extern const char* scale;                   // 0x01551004
extern const char* soundIDFoot;             // 0x01551008
extern const char* soundIDMouth;            // 0x0155100c
extern const char* soundIDWeapon;           // 0x01551010
extern const char* cap;                     // 0x01550fc8
extern const char* deformChannel;           // 0x01550fd8
}

namespace {

// @ 0x009ca4b0
void cBlockBlockCommand::OnRegister(cIParser* parser, cState* state)
{
    mState = (cBlockBlockState*)state;
    EA::ArgScript::cBlockCommandBase::OnRegister(parser, state);

#define REGISTER(Name, keyword) \
    AddCommand(BlockKeywords::keyword, new ("ArgScript/" #Name, 0, 0, 0, 0) c##Name##Command())

    REGISTER(Name, name);
    REGISTER(InstanceId, instanceId);
    REGISTER(Version, version);
    REGISTER(ParentIndex, parentIndex);
    REGISTER(SymmetricIndex, symmetricIndex);
    REGISTER(JointPosition, jointPosition);
    REGISTER(SubmeshIndex, submeshIndex);
    REGISTER(LeftHanded, leftHanded);
    REGISTER(Cal3DBoneName, cal3DBoneName);
    REGISTER(Cal3DOrigin, cal3DOrigin);
    REGISTER(Position, position);
    REGISTER(EffectsOrigin, effectsOrigin);
    REGISTER(Orientation, orientation);
    REGISTER(BBoxMin, bBoxMin);
    REGISTER(BBoxMax, bBoxMax);
    REGISTER(Mass, mass);
    REGISTER(Scale, scale);
    REGISTER(SoundIDFoot, soundIDFoot);
    REGISTER(SoundIDMouth, soundIDMouth);
    REGISTER(SoundIDWeapon, soundIDWeapon);
    REGISTER(Cap, cap);
    REGISTER(Deform, deformChannel);

#undef REGISTER
}

}  // namespace

// =====================================================================
// nSPCreatureAnim::creature_effect
// =====================================================================
namespace nSPCreatureAnim {

struct creature_instance_data;

struct IUnknown {
    virtual int AddRef();
    virtual int Release();
    virtual void* Cast(unsigned long type);
};
struct cIVisualEffect : IUnknown {};
struct cMWModel;

// Auto-refcounting pointer; operator= expands to the retail
// "compare / AddRef new / store / Release old" pattern.
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) {}
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    operator T*() const { return mpObject; }
};
// cMWModel's operator= is out of line (counter at +0x40) at 0x00478db0.
template <> struct AutoRefCount<cMWModel> {
    cMWModel* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(cMWModel* p) : mpObject(p) {}
    AutoRefCount& operator=(cMWModel* p);       // 0x00478db0
    operator cMWModel*() const { return mpObject; }
};

struct vector_3 {
    float x, y, z;
    vector_3() { z = 0.0f; y = 0.0f; x = 0.0f; }
    vector_3& operator=(const vector_3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct vector_4 {
    float x, y, z, w;
    vector_4() { z = 0.0f; y = 0.0f; x = 0.0f; w = 1.0f; }
    vector_4& operator=(const vector_4& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
};

struct creature_instance_data {
    int AddRef();                               // 0x00a17060
    int Release();                              // 0x009c4cc0
};

// retail size 0xac (the dev PDB layout is 0xb8 and has a matrix local_rot)
struct creature_effect {
    unsigned long key;                                  // 0x000
    unsigned long id;                                   // 0x004
    unsigned long bidx;                                 // 0x008
    vector_3      local_pos;                            // 0x00c
    vector_4      local_rot;                            // 0x018
    bool          f28;                                  // 0x028
    bool          f29;                                  // 0x029
    unsigned char pad_2a[2];
    float         f2c;                                  // 0x02c
    bool          f30;                                  // 0x030
    unsigned char pad_31[3];
    unsigned long d34;                                  // 0x034
    unsigned long d38;                                  // 0x038
    unsigned long d3c;                                  // 0x03c
    unsigned long d40;                                  // 0x040
    unsigned long d44;                                  // 0x044
    union {
        long  i;                                        // 0x048
        float f;
    } data48;
    AutoRefCount<creature_instance_data> ref4c;         // 0x04c
    AutoRefCount<creature_instance_data> ref50;         // 0x050
    AutoRefCount<creature_instance_data> ref54;         // 0x054
    unsigned long d58;                                  // 0x058
    unsigned long d5c;                                  // 0x05c
    unsigned long d60;                                  // 0x060
    vector_3      src_pos_rand;                         // 0x064
    unsigned long d70;                                  // 0x070
    unsigned long d74;                                  // 0x074
    AutoRefCount<creature_instance_data> ref78;         // 0x078
    unsigned long d7c;                                  // 0x07c
    vector_3      dst_pos_rand;                         // 0x080
    AutoRefCount<cIVisualEffect> effect;                // 0x08c
    AutoRefCount<cMWModel>       model;                 // 0x090
    unsigned long sound_id;                             // 0x094
    vector_3      last_sound_pos;                       // 0x098
    AutoRefCount<IUnknown>       unknown;               // 0x0a4
    unsigned long da8;                                  // 0x0a8

    creature_effect();                                  // 0x009caac0
    ~creature_effect();                                 // 0x009c9870
    creature_effect& operator=(const creature_effect& o);   // 0x009cabd0
    void Clear(bool bAll);                              // 0x009c96b0
    void Init(cIVisualEffect* p, unsigned long bidx, unsigned long id);        // 0x009caa40
    void Init(unsigned long soundId, unsigned long bidx, unsigned long id);    // 0x009caa90
};

// @ 0x009caa40
void creature_effect::Init(cIVisualEffect* p, unsigned long bidx_, unsigned long id_)
{
    Clear(false);
    id = id_;
    bidx = bidx_;
    effect = p;
}

// @ 0x009caa90
void creature_effect::Init(unsigned long soundId, unsigned long bidx_, unsigned long id_)
{
    Clear(false);
    id = id_;
    bidx = bidx_;
    sound_id = soundId;
}

// @ 0x009caac0
creature_effect::creature_effect()
    : local_pos(), local_rot(), ref4c(), ref50(), ref54(),
      src_pos_rand(), ref78(), dst_pos_rand(), effect(), model(),
      last_sound_pos(), unknown()
{
    Clear(true);
}

// @ 0x009cabd0
creature_effect& creature_effect::operator=(const creature_effect& o)
{
    key = o.key;
    id = o.id;
    bidx = o.bidx;
    local_pos = o.local_pos;
    local_rot = o.local_rot;
    f28 = o.f28;
    f29 = o.f29;
    f2c = o.f2c;
    f30 = o.f30;
    d34 = o.d34;
    d38 = o.d38;
    d3c = o.d3c;
    d40 = o.d40;
    d44 = o.d44;
    data48.i = o.data48.i;
    data48.f = o.data48.f;
    ref4c = o.ref4c.mpObject;
    ref50 = o.ref50.mpObject;
    ref54 = o.ref54.mpObject;
    d58 = o.d58;
    d5c = o.d5c;
    d60 = o.d60;
    src_pos_rand = o.src_pos_rand;
    d70 = o.d70;
    d74 = o.d74;
    ref78 = o.ref78.mpObject;
    d7c = o.d7c;
    dst_pos_rand = o.dst_pos_rand;
    effect = o.effect.mpObject;
    model = o.model.mpObject;
    sound_id = o.sound_id;
    last_sound_pos = o.last_sound_pos;
    unknown = o.unknown.mpObject;
    da8 = o.da8;
    return *this;
}

// =====================================================================
// effect table (EASTL fixed_hashtable<unsigned long, creature_effect*>)
// =====================================================================
namespace eastl {

struct hashtable_iterator {
    void* mpNode;       // +0x00
    void* mpBucket;     // +0x04
};

}  // namespace eastl

using eastl::hashtable_iterator;

struct effect_node {
    unsigned long     key;                  // +0x00
    creature_effect*  value;                // +0x04
    effect_node*      next;                 // +0x08
};

struct effect_pair {
    unsigned long     first;                // key
    creature_effect*  second;               // value
};

struct RehashInfo {
    unsigned char doRehash;         // +0x00
    unsigned long newBucketCount;   // +0x04
};

// mod_range_hashing / prime_rehash_policy storage; insert() lives out-of-line
// at 0x00921440 and is modelled as a member so ecx = &policy.
struct effect_rehash_policy {
    unsigned char bytes[0x0c];
    void insert(RehashInfo* out, unsigned long nBucketCount,
                unsigned long nElementCount, int bForce);   // 0x00921440
};

struct effect_table {
    void*                 pad_00;           // +0x00
    void**                mpBucketArray;    // +0x04
    unsigned long         mnBucketCount;    // +0x08
    unsigned long         mnElementCount;   // +0x0c
    effect_rehash_policy  policy;           // +0x10
    void*                 mpFreeList;       // +0x1c
    unsigned char         pad_20[0x0c];     // +0x20
    unsigned long         mnNodeSize;       // +0x2c

    hashtable_iterator find(const unsigned long& key) const;            // 0x00645ed0
    hashtable_iterator* insert(hashtable_iterator* out, const effect_pair* v, bool bRehash);  // 0x009cae00
    void Rehash(unsigned long nNewBucketCount);                        // 0x00a22220
};

// @ 0x009cae00
hashtable_iterator* effect_table::insert(hashtable_iterator* out, const effect_pair* v, bool)
{
    RehashInfo pr;
    policy.insert(&pr, mnBucketCount, mnElementCount, 1);
    if (pr.doRehash)
        Rehash(pr.newBucketCount);

    unsigned long n = v->first % mnBucketCount;

    effect_node* node;
    if (mpFreeList) {
        node = (effect_node*)mpFreeList;
        mpFreeList = *(void**)mpFreeList;
    } else {
        node = (effect_node*)EAAllocate(mnNodeSize, "EASTL", 0, 0,
            (int)"c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    if (node) {
        node->key = v->first;
        node->value = v->second;
    }
    node->next = 0;

    effect_node* bucket = (effect_node*)mpBucketArray[n];
    if (bucket) {
        effect_node* p = bucket;
        do {
            if (v->first == p->key) {
                node->next = p->next;
                p->next = node;
                goto done;
            }
            p = p->next;
        } while (p);
    }
    node->next = bucket;
    mpBucketArray[n] = node;
done:
    mnElementCount++;
    out->mpNode = node;
    out->mpBucket = &mpBucketArray[n];
    return out;
}

// --- effect free list -------------------------------------------------
struct EffectFreeList {
    creature_effect** mpBegin;
    creature_effect** mpEnd;
};
extern EffectFreeList* g_EffectFreeList;    // 0x0166c068

// full owner layout: the effect table lives at +0x17a0
struct creature_instance_data_full : creature_instance_data {
    unsigned char pad_000[0x17a0];
    effect_table  effects;                              // +0x17a0

    int* LookupEffect(unsigned long key);                                       // 0x009cab60
    creature_effect* AllocateEffect(unsigned long key, bool bFlag, hashtable_iterator* pOut);  // 0x009cb300
};

// @ 0x009cab60
int* creature_instance_data_full::LookupEffect(unsigned long key)
{
    effect_table& t = effects;
    unsigned long k = key;
    hashtable_iterator it = t.find(k);
    if (it.mpNode != t.mpBucketArray[t.mnBucketCount])
        return *(int**)((char*)it.mpNode + 4);
    return 0;
}

// @ 0x009cb300
creature_effect* creature_instance_data_full::AllocateEffect(unsigned long key, bool bFlag, hashtable_iterator* pOut)
{
    effect_table& t = effects;
    unsigned long k = key;
    hashtable_iterator it = t.find(k);
    if (!bFlag) {
        if (it.mpNode != t.mpBucketArray[t.mnBucketCount]) {
            if (pOut) *pOut = it;
            return 0;
        }
    }
    EffectFreeList* fl = g_EffectFreeList;
    creature_effect* p;
    if (fl->mpBegin == fl->mpEnd) {
        p = (creature_effect*)EAAllocate(0xac, "Anim/cid/new_ce", 0, 0, 0, 0);
        if (p)
            p = new (p) creature_effect();
        else
            p = 0;
    } else {
        p = *--fl->mpEnd;
    }
    effect_pair v;
    v.first = k;
    v.second = p;
    t.insert(&it, &v, false);
    if (pOut) *pOut = it;
    p->key = key;
    p->f28 = bFlag;
    return p;
}

}  // namespace nSPCreatureAnim

// @ 0x009cabb0
void __cdecl FUN_009cabb0(nSPCreatureAnim::creature_effect* p)
{
    if (!p)
        return;
    p->~creature_effect();
    operator delete(p);
}

// =====================================================================
// EASTL vector instantiations (creature block definitions / effect items)
// =====================================================================
namespace nSPCreatureAnim {
namespace eastl {

static const char* const kAllocator = "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// 0x468-byte element (a creature block definition)
struct BlockDef {
    unsigned char bytes[0x468];
};

void  FUN_009b3e40(BlockDef* dst, const BlockDef* src);                    // copy-construct one
void  FUN_009c0a70(BlockDef* dst, unsigned long n, const BlockDef* value); // fill_n
void* FUN_009c84d0(const BlockDef* first, const BlockDef* last, BlockDef* dst);  // copy -> dst+n
void  FUN_009be710(void* a, void* b, void* c, void* d, void* e);
void  FUN_009c8580(BlockDef* dst, BlockDef* first, BlockDef* last);
void  FUN_009ca480(BlockDef* first, BlockDef* last, const BlockDef* value);

struct BlockDefVec {
    BlockDef* mpBegin;          // +0x00
    BlockDef* mpEnd;            // +0x04
    BlockDef* mpCapacity;       // +0x08

    void insert(BlockDef* position, unsigned long n, const BlockDef& value);    // 0x009caee0
};

// @ 0x009caee0  vector<BlockDef>::insert(position, n, value)
void BlockDefVec::insert(BlockDef* position, unsigned long n, const BlockDef& value)
{
    if ((unsigned long)(mpCapacity - mpEnd) / 0x468 < n) {
        unsigned long size = (unsigned long)(mpEnd - mpBegin) / 0x468;
        unsigned long newCap = size * 2;
        if (size == 0) newCap = 1;
        unsigned long want = size + n;
        if (want > newCap) newCap = want;
        BlockDef* newBegin = newCap
            ? (BlockDef*)EAAllocate(newCap * 0x468, "EASTL", 0, 0, (int)kAllocator, 0xd1) : 0;
        BlockDef* mid = (BlockDef*)FUN_009c84d0(mpBegin, position, newBegin);
        FUN_009c0a70(mid, n, &value);
        BlockDef* newEnd = (BlockDef*)FUN_009c84d0(position, mpEnd, mid + n);
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            operator delete(mpBegin);
        mpBegin = newBegin;
        mpEnd = newEnd;
        mpCapacity = newBegin + newCap;
        return;
    }
    if (n == 0)
        return;
    BlockDef tmp;
    FUN_009b3e40(&tmp, &value);
    BlockDef* oldEnd = mpEnd;
    unsigned long roomAtEnd = (unsigned long)(mpEnd - position) / 0x468;
    if (n < roomAtEnd) {
        BlockDef* split = oldEnd - n;
        FUN_009be710(&tmp, oldEnd, oldEnd, split, &tmp);
        mpEnd += n;
        FUN_009c8580(position, split, oldEnd);
        FUN_009ca480(position, position + n, &tmp);
        return;
    }
    FUN_009c0a70(oldEnd, n - roomAtEnd, &tmp);
    mpEnd += (n - roomAtEnd);
    FUN_009be710(&tmp, position, oldEnd - n, oldEnd, &tmp);
    mpEnd += roomAtEnd;
    FUN_009ca480(position, oldEnd, &tmp);
}

// 0x28-byte element (an effect item)
struct EffectItem {
    unsigned char bytes[0x28];
};

void  FUN_009be750(EffectItem* dst, EffectItem* first, EffectItem* last);   // move-construct range
void* FUN_009c8510(EffectItem* first, EffectItem* last, EffectItem* dst);   // copy -> dst+n
void  FUN_009c89d0(EffectItem* first, unsigned long n, const EffectItem* value, EffectItem* pos);
void  FUN_009c85c0(EffectItem* first, EffectItem* last);                    // destroy range
void  FUN_009c8970(EffectItem* first, EffectItem* last, const EffectItem* value);  // fill

struct EffectItemVec {
    EffectItem* mpBegin;        // +0x00
    EffectItem* mpEnd;          // +0x04
    EffectItem* mpCapacity;     // +0x08

    void insert(EffectItem* position, unsigned long n, const EffectItem& value);    // 0x009cb0d0
};

// @ 0x009cb0d0  vector<EffectItem>::insert(position, n, value)
void EffectItemVec::insert(EffectItem* position, unsigned long n, const EffectItem& value)
{
    if ((unsigned long)(mpCapacity - mpEnd) / 0x28 < n) {
        unsigned long size = (unsigned long)(mpEnd - mpBegin) / 0x28;
        unsigned long newCap = size * 2;
        if (size == 0) newCap = 1;
        unsigned long want = size + n;
        if (want > newCap) newCap = want;
        EffectItem* newBegin = newCap
            ? (EffectItem*)EAAllocate(newCap * 0x28, "EASTL", 0, 0, (int)kAllocator, 0xd1) : 0;
        EffectItem* mid = (EffectItem*)FUN_009c8510(mpBegin, position, newBegin);
        FUN_009c89d0(mid, n, &value, position);
        EffectItem* newEnd = (EffectItem*)FUN_009c8510(position, mpEnd, mid + n);
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            operator delete(mpBegin);
        mpBegin = newBegin;
        mpEnd = newEnd;
        mpCapacity = newBegin + newCap;
        return;
    }
    if (n == 0)
        return;
    EffectItem tmp;
    FUN_009be750(&tmp, (EffectItem*)&value, (EffectItem*)&value + 1);
    EffectItem* oldEnd = mpEnd;
    unsigned long roomAtEnd = (unsigned long)(mpEnd - position) / 0x28;
    if (n < roomAtEnd) {
        EffectItem* split = oldEnd - n;
        FUN_009be750(split, split, oldEnd);
        mpEnd += n;
        FUN_009c85c0(position, split);
        FUN_009c8970(position, split, &tmp);
        return;
    }
    FUN_009c89d0(oldEnd, n - roomAtEnd, &tmp, position);
    mpEnd += (n - roomAtEnd);
    FUN_009be750(position, oldEnd - n, oldEnd);
    mpEnd += roomAtEnd;
    FUN_009c8970(position, oldEnd, &tmp);
}

}  // namespace eastl
}  // namespace nSPCreatureAnim
