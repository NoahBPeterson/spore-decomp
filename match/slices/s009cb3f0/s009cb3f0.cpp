// Slice s009cb3f0: nSPCreatureAnim creature-effect table maintenance (erase / clear-all /
// update-all / attach), the creature_body_static_data and effect-item vector resize helpers,
// the NumBlocks ArgScript command and the two foot-placement helpers.
//
// Retail layouts come from the disassembly (the 2008 PDB predates the quaternion/vector
// revision).  Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }

// =====================================================================
// leaf helpers (external, resolved by VA)
// =====================================================================
int  __cdecl Snprintf8(char* dst, unsigned cap, const char* fmt, ...);   // 0x009384e0
void* __fastcall FUN_009b3cd0(void* self);                               // 0x009b3cd0 construct default element (ret 0)
void __cdecl FUN_009b4310(void* first, void* last, void* dst);           // 0x009b4310 eastl::move (0x468)
void __cdecl FUN_009bed40(void* first, void* last, void* dst);           // 0x009bed40 eastl::move (0x28)
void __cdecl FUN_009c8630(float* out, int data);                         // 0x009c8630
void __cdecl FUN_009c86e0(float* out, int* idx, int data);               // 0x009c86e0
void __cdecl FUN_009c87e0(void* out, int* idx, int elem);                // 0x009c87e0

extern const float DAT_01485720;    // 1.0f
extern const float DAT_01471064;    // 0.5f
extern const float DAT_01470f1c;    // 2.0f
extern const float DAT_013eb8b0;    // -0.0f sign mask
extern const float DAT_013eb960;    // 0.01f
extern const float DAT_01447408;    // 3.4028235e+38 (FLT_MAX)
extern const float DAT_0155123c;    // 3.4028235e+38
extern const char  DAT_013f5b98[];  // "%s"
extern const char  DAT_014478ac[];
extern const char  DAT_0144789c[];

namespace nSPCreatureAnim {

// =====================================================================
// EASTL fixed_hashtable<unsigned long, creature_effect*> node / table
// =====================================================================
struct creature_effect;

struct effect_node {
    unsigned long    key;       // +0x00
    creature_effect* value;     // +0x04
    effect_node*     next;      // +0x08
};

struct hashtable_iterator {
    effect_node*  mpNode;       // +0x00
    effect_node** mpBucket;     // +0x04
    hashtable_iterator() {}
    hashtable_iterator(effect_node* n, effect_node** b) { mpBucket = b; mpNode = n; }
    hashtable_iterator(const hashtable_iterator& o)
    { mpBucket = o.mpBucket; mpNode = o.mpNode; }
    hashtable_iterator& operator=(const hashtable_iterator& o)
    { mpNode = o.mpNode; mpBucket = o.mpBucket; return *this; }
};

struct range_out {
    effect_node*  first;        // +0x00
    effect_node** firstBucket;  // +0x04
    effect_node*  last;         // +0x08
    effect_node** lastBucket;   // +0x0c
};

struct effect_table {
    void*           pad_00;         // +0x00
    effect_node**   mpBucketArray;  // +0x04
    unsigned long   mnBucketCount;  // +0x08
    unsigned long   mnElementCount; // +0x0c
    unsigned char   pad_10[0x0c];   // +0x10 rehash policy
    effect_node*    mpFreeList;     // +0x1c
    unsigned char   pad_20[0x0c];   // +0x20
    effect_node*    mpInlineNode;   // +0x30

    range_out* equal_range(range_out* out, const unsigned long* key);   // 0x009a6dd0
    hashtable_iterator erase(hashtable_iterator position);              // 0x00b51640
};

// =====================================================================
// effect free list (SP::SimpleVector<creature_effect*> global at 0x0166c068)
// =====================================================================
struct effect_free_list {
    typedef creature_effect* value_type;
    creature_effect** mpBegin;      // +0x00
    creature_effect** mpEnd;        // +0x04
    creature_effect** mpCapacity;   // +0x08
    void DoInsertValue(creature_effect** pos, creature_effect* const& value);   // 0x00a80dd0
    void push_back(creature_effect* const& value)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) value_type(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
extern effect_free_list* g_EffectFreeList;      // 0x0166c068

// =====================================================================
// creature_effect (retail layout, size 0xac)
// =====================================================================
struct IUnknown {
    virtual int AddRef();
    virtual int Release();
    virtual void* Cast(unsigned long type);
};
struct cIVisualEffect : IUnknown {};
struct cMWModel;
struct creature_instance_data;

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

// vector_3 / vector_4 constructors run in z,y,x(,w) order (matches the retail codegen).
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
// plain (ctor-less) geometry used by the large body records
struct float3 { float x, y, z; };
struct float4 { float x, y, z, w; };

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
    union { long i; float f; } data48;                  // 0x048
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

    void Clear(bool bAll);                              // 0x009c96b0
    creature_effect& operator=(const creature_effect& o);   // 0x009cabd0
};

// =====================================================================
// creature_instance_data (retail offsets; effect table at +0x17a0)
// =====================================================================
struct creature_instance_data {
    int AddRef();                                       // 0x0099cab0
    int Release();
    unsigned char pad_000[0x384];
    unsigned char bodyVec[0x0c];                        // 0x384 (begin/end/cap)
    unsigned char pad_390[0x3c8 - 0x390];
    unsigned long counter_3c8;                          // 0x3c8
    unsigned char pad_3cc[0x3f5 - 0x3cc];
    unsigned char flag_3f5;                             // 0x3f5
    unsigned char pad_3f6[0x17a0 - 0x3f6];
    effect_table  effects;                              // 0x17a0

    bool UpdateEffect(creature_effect* p);              // 0x009c9910

    creature_effect* AllocateEffect(unsigned long key, bool bFlag,
                                    hashtable_iterator* pOut);                  // 0x009cb300
    hashtable_iterator EraseEffect(hashtable_iterator position);        // 0x009cb3f0
    void RemoveEffect(creature_effect* p);                                      // 0x009cb460
    void ClearAllEffects();                                                     // 0x009cb4f0
    void AttachEffect(hashtable_iterator* out, creature_instance_data* src,
                      effect_node* node, effect_node** bucket,
                      unsigned long bidx, hashtable_iterator* pOut);            // 0x009cb5a0
};

// @ 0x009cb3f0
hashtable_iterator creature_instance_data::EraseEffect(hashtable_iterator pos)
{
    g_EffectFreeList->push_back(pos.mpNode->value);
    pos.mpNode->value->Clear(false);
    return effects.erase(pos);
}

// @ 0x009cb460
void creature_instance_data::RemoveEffect(creature_effect* p)
{
    if (!p)
        return;
    unsigned long key = p->key;
    effect_table* t = &effects;
    range_out range;
    t->equal_range(&range, &key);
    if (range.first == t->mpBucketArray[t->mnBucketCount])
        return;
    effect_node* node = range.first;
    effect_node** bucket = range.firstBucket;
    if (node == range.last)
        return;
    while (node->value != p) {
        node = node->next;
        while (!node)
            node = *++bucket;
        if (node == range.last)
            return;
    }
    *(hashtable_iterator*)&range = EraseEffect(hashtable_iterator(node, bucket));
}

// @ 0x009cb4f0
void creature_instance_data::ClearAllEffects()
{
    effect_node** buckets = effects.mpBucketArray;
    effect_node** bucket = buckets;
    effect_node* node = *bucket;
    if (!node) {
        do {
            bucket++;
        } while (*bucket == 0);
        node = *bucket;
    }
    effect_node* end = buckets[effects.mnBucketCount];
    if (node != end) {
        hashtable_iterator it;
        do {
            g_EffectFreeList->push_back(node->value);
            node->value->Clear(false);
            it = effects.erase(hashtable_iterator(node, bucket));
            node = it.mpNode;
            bucket = it.mpBucket;
        } while (node != end);
    }
}

// @ 0x009cb5a0
void creature_instance_data::AttachEffect(hashtable_iterator* out, creature_instance_data* src,
                                          effect_node* node, effect_node** bucket,
                                          unsigned long bidx, hashtable_iterator* pOut)
{
    if (!src) {
        out->mpNode = 0;
        out->mpBucket = 0;
        return;
    }
    effect_node** end = &src->effects.mpBucketArray[src->effects.mnBucketCount];
    if (node == *end)
        goto fail;
    {
        creature_effect* old = node->value;
        if (!old)
            goto fail;
        creature_effect* ne = AllocateEffect(old->key, old->f28, pOut);
        if (!ne)
            goto fail;
        *ne = *old;
        ne->bidx = bidx;
        if (ne->ref4c.mpObject == src) {
            ne->ref4c = this;
            ne->d58 = (ne->d58 == old->bidx) ? bidx : 1;
        }
        if (ne->ref50.mpObject == src) {
            ne->ref50 = this;
            ne->d5c = (ne->d5c == old->bidx) ? bidx : 1;
        }
        if (ne->ref54.mpObject == src) {
            ne->ref54 = this;
            ne->d60 = (ne->d60 == old->bidx) ? bidx : 1;
        }
        if (ne->ref78.mpObject == src) {
            ne->ref78 = this;
            ne->d7c = (ne->d7c == old->bidx) ? bidx : 1;
        }
        if (old->effect.mpObject) {
            cIVisualEffect* p = old->effect.mpObject;
            old->effect.mpObject = 0;
            p->Release();
        }
        old->model = 0;
        old->sound_id = 0;
        if (old->unknown.mpObject) {
            IUnknown* p = old->unknown.mpObject;
            old->unknown.mpObject = 0;
            p->Release();
        }
        *out = EraseEffect(hashtable_iterator(node, bucket));
        return;
    }
fail:
    out->mpNode = *end;
    out->mpBucket = end;
}

// @ 0x009cb760
void __cdecl FUN_009cb760(creature_instance_data* self)
{
    effect_table& t = self->effects;
    effect_node** buckets = t.mpBucketArray;
    effect_node** bucket = buckets;
    effect_node* node = *bucket;
    if (!node) {
        bucket++;
        node = *bucket;
        while (!node) {
            bucket++;
            node = *bucket;
        }
    }
    if (node != buckets[t.mnBucketCount]) {
        hashtable_iterator it;
        do {
            if (!node->value || !self->UpdateEffect(node->value)) {
                g_EffectFreeList->push_back(node->value);
                node->value->Clear(false);
                it = t.erase(hashtable_iterator(node, bucket));
                node = it.mpNode;
                bucket = it.mpBucket;
            } else {
                node = node->next;
                while (!node)
                    node = *++bucket;
            }
        } while (node != buckets[t.mnBucketCount]);
    }
}

// =====================================================================
// creature_body_static_data (0x468) and its vector
// =====================================================================
struct body_flags_150 {
    unsigned char flags;                // +0x00
    unsigned char pad_01[0xa7];
    void Set(unsigned long fourcc, int flag);   // 0x009b3090
};

struct creature_body_static_data {
    char          name[0x104];          // 0x000
    unsigned long instance_id;          // 0x104
    unsigned long group_id;             // 0x108
    float3        rest_center;          // 0x10c
    float4        rest_orientation;     // 0x118
    unsigned char pad_128[0x138 - 0x128];
    float         f138;                 // 0x138
    float         f13c;                 // 0x13c
    float         f140;                 // 0x140
    unsigned char pad_144[0x150 - 0x144];
    body_flags_150 f150;                // 0x150
    unsigned long f1f8;                 // 0x1f8
    unsigned long f1fc;                 // 0x1fc
    unsigned long f200;                 // 0x200
    unsigned char pad_204[0x208 - 0x204];
    unsigned long f208;                 // 0x208
    unsigned char pad_20c[0x21c - 0x20c];
    unsigned long f21c;                 // 0x21c
    char          foot_name[0x104];     // 0x220
    unsigned char pad_324[0x350 - 0x324];
    float         out350;               // 0x350
    float         out354;               // 0x354
    float         out358;               // 0x358
    unsigned char pad_35c[0x36c - 0x35c];
    float         f36c;                 // 0x36c
    unsigned char pad_370[0x378 - 0x370];
    float         f378;                 // 0x378
    float         f37c;                 // 0x37c
    unsigned char pad_380[0x468 - 0x380];

    void Clear();                       // 0x009b3180
};

struct body_static_vec {
    creature_body_static_data* mpBegin;         // +0x00
    creature_body_static_data* mpEnd;           // +0x04
    creature_body_static_data* mpCapacity;      // +0x08

    void insert(creature_body_static_data* position, unsigned long n,
                creature_body_static_data* value);                          // 0x009caee0
    void resize(unsigned long n);                                       // 0x009cb840
};

// 0x28-byte effect item: [0x00..0x0b] uninitialised, a vector_3 then a vector_4
struct effect_item {
    unsigned char pad_00[0x0c];
    vector_3      a;            // 0x0c
    vector_4      b;            // 0x18
};

struct effect_item_vec {
    effect_item* mpBegin;       // +0x00
    effect_item* mpEnd;         // +0x04
    effect_item* mpCapacity;    // +0x08

    void insert(effect_item* position, unsigned long n, effect_item* value);   // 0x009cb0d0
    void resize(unsigned long n);                                       // 0x009cb8f0
};

// @ 0x009cb840
void body_static_vec::resize(unsigned long n)
{
    if (n > (unsigned long)(mpEnd - mpBegin)) {
        creature_body_static_data tmp;
        FUN_009b3cd0(&tmp);
        insert(mpEnd, n - (unsigned long)(mpEnd - mpBegin), &tmp);
        return;
    }
    creature_body_static_data* p = mpBegin + n;
    FUN_009b4310(mpEnd, mpEnd, p);
    mpEnd -= mpEnd - p;
}

// @ 0x009cb8f0
void effect_item_vec::resize(unsigned long n)
{
    effect_item* begin = mpBegin;
    effect_item* end = mpEnd;
    if (n > (unsigned long)(end - begin)) {
        effect_item tmp;
        insert(end, n - (unsigned long)(end - begin), &tmp);
        return;
    }
    effect_item* p = begin + n;
    FUN_009bed40(end, end, p);
    mpEnd -= (end - p);
}

// @ 0x009cb9f0
void FUN_009cb9f0(float* pos, unsigned long* idx, char* instance)
{
    unsigned long base = *(unsigned long*)(instance + 0x384);
    unsigned long v = *(unsigned long*)(base + (*idx) * 0x468 + 0x200);
    long count = (long)(*(unsigned long*)(instance + 0x388) - base) / 0x468;
    long want = count + (v != 0xffffffff ? 1 : 0) + 1;

    ((body_static_vec*)(instance + 0x384))->resize((unsigned long)want);

    bool bVar6 = false;
    if ((long)count >= (long)want) {
        *(unsigned char*)(instance + 0x3f5) = 0;
        return;
    }
    unsigned long off = count * 0x468;
    do {
        creature_body_static_data* e =
            (creature_body_static_data*)(*(unsigned long*)(instance + 0x384) + off);
        e->Clear();
        Snprintf8(e->name, 0x104, DAT_013f5b98, DAT_014478ac);
        Snprintf8(e->foot_name, 0x104, DAT_0144789c, count);
        e->f378 = DAT_01485720;
        e->group_id = 0x40600000;
        e->instance_id = 0x6b2c0771;
        e->f1f8 = count;
        e->f21c = 0xffffffff;
        e->f37c = DAT_01471064;
        if (v == 0xffffffff) {
            e->f200 = 0xffffffff;
            e->f1fc = *idx;
        } else {
            e->f1fc = bVar6 ? v : *idx;
            e->f200 = bVar6 ? want - 2 : want - 1;
        }
        e->rest_center.x = pos[0];
        e->rest_center.y = pos[1];
        e->rest_center.z = pos[2];
        if (bVar6)
            e->rest_center.x = -pos[0];
        e->f138 = DAT_013eb960;
        e->f13c = DAT_013eb960;
        e->f140 = DAT_013eb960;
        e->f150.Set(0x746f6f66, 1);
        e->f36c = DAT_01447408;
        unsigned long pi = e->f1fc;
        creature_body_static_data* par =
            (creature_body_static_data*)(*(unsigned long*)(instance + 0x384) + pi * 0x468);
        par->f208 += 1;

        float dx = e->rest_center.x - par->rest_center.x;
        float dy = e->rest_center.y - par->rest_center.y;
        float dz = e->rest_center.z - par->rest_center.z;
        float qx = par->rest_orientation.x;
        float qy = par->rest_orientation.y;
        float qz = par->rest_orientation.z;
        float qw = par->rest_orientation.w;

        float t0 = (qy * qx - -(qz * qw)) * dy + (qz * qx + -(qy * qw)) * dz
                 + (-(qz * qz) + -(qy * qy)) * dx;
        float t1 = (-(qz * qz) + -(qx * qx)) * dy + (qz * qy - -(qx * qw)) * dz
                 + (qy * qx + -(qz * qw)) * dx;
        float t2 = (-(qy * qy) + -(qx * qx)) * dz + (qz * qy + -(qx * qw)) * dy
                 + (qz * qx - -(qy * qw)) * dx;
        e->out350 = t0 * DAT_01470f1c + dx;
        e->out354 = t1 * DAT_01470f1c + dy;
        e->out358 = t2 * DAT_01470f1c + dz;

        *(unsigned long*)(instance + 0x3c8) += 1;
        count++;
        off += 0x468;
        bVar6 = true;
    } while ((long)count < (long)want);
    *(unsigned char*)(instance + 0x3f5) = 0;
}

// @ 0x009cbdb0
void FUN_009cbdb0(char* instance)
{
    float best = DAT_01447408;
    float limit = DAT_01447408;
    int   index = -1;

    FUN_009c8630(&best, (int)instance);
    FUN_009c86e0(&limit, &index, (int)instance);
    float prev = limit;

    if (index == -1)
        return;
    do {
        if (best <= limit)
            return;
        if ((best - prev) * DAT_0155123c <= limit - prev)
            return;
        creature_body_static_data* e =
            (creature_body_static_data*)(*(unsigned long*)(instance + 0x384) + index * 0x468);
        index = -1;
        vector_3 p;
        if (e->f150.flags & 2) {
            FUN_009c87e0(&p, &index, (int)e);
            if (index != -1)
                FUN_009cb9f0(&p.x, (unsigned long*)&index, instance);
        }
        limit = DAT_01447408;
        index = -1;
        FUN_009c86e0(&limit, &index, (int)instance);
    } while (index != -1);
}

}  // namespace nSPCreatureAnim

// =====================================================================
// ArgScript cNumBlocksCommand::Execute (0x009cb9b0)
// =====================================================================
namespace {

struct cArguments {
    void* MainArguments(int n);                 // 0x00838320
};

struct cIParser {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38();
    virtual unsigned long GetBlockCount(unsigned long id);   // +0x9c
};

struct cBlockState;                             // the +0xc member's type
struct cNumBlocksCommand {
    cIParser*     mParser;      // +0x04
    int           mRefCount;    // +0x08
    cBlockState*  mState;       // +0x0c

    virtual void Execute(cArguments& args);      // 0x009cb9b0
};

// @ 0x009cb9b0
void cNumBlocksCommand::Execute(cArguments& args)
{
    void* p = args.MainArguments(1);
    unsigned long n = mParser->GetBlockCount(*(unsigned long*)p);
    ((nSPCreatureAnim::body_static_vec*)(*(unsigned long*)((char*)mState + 0x44) + 0x384))->resize(n);
}

}  // namespace
