// Slice s00a2d790: EA::Audio::System and its EASTL containers.
// Retail layout offsets taken from the disassembly. The 2008 PDB gives real
// names for several members (mPrimitives, ...); unknown gaps are byte pads.
#include <string.h>
#include <intrin.h>

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* p);

typedef unsigned int uint;
typedef unsigned char uchar;

struct XF;           // generic stub for external __thiscall callees
struct AudioSystem;

// --- generic thiscall callees: ecx = object, rest on stack ---
struct XF {
    void* hashtable_find(void* out, void* key);      // 0x645ed0 (arg1 = out, arg2 = key)
    void* rbtree_find(void* out, void* key);         // 0xe5c780
    void* FUN_00a2a150(void* out);
    void* FUN_00a2a510(void* out);
    void  FUN_00a276e0(void* a, void* b);
    void  FUN_00a2b230(void* a, void* b, void* c, void* d);
    void  FUN_00a26a20(void* a, void* b, void* c);
    void  FUN_00a26ce0(void* a, void* b, void* c);
    void  FUN_00a26fa0(void* a);
    void  FUN_00a2ac20(void* a, void* b);
    void  FUN_00a2af30(void* a, void* b);
    void  FUN_00a22220(uint n);
    void  FUN_00a2bb30();
    void  FUN_00a21390();
    void  AutoRef_op(uint* p);
    void* Lock(void* name);      // 0x9221b0
    void  Unlock();              // 0x922270
    void* DoInsertValue(void* out, void* pos, const void* key, int dummy);   // 0x00a27cc0
    int   DoFreeNodes(void* a, void* b);
    void  DoNukeSubtree(void* a);                                     // 0x009a9600
    void  StopwatchCtor(void* a, void* b);
    void  HashtableCtor(uint bucketCount, void* a, void* b, void* c,
                        void* d, void* e, void* pool);      // 0x00a1cdb0
    void  Noop();
};

// EASTL fixed_pool_base (0x921260 init); 0x18 bytes so the ctor's pool[5] read is benign
struct FixedPoolLocal {
    void* mpHead;                                   // +0x00
    uint  mPad[5];                                  // +0x04
    void init(void* pool, uint size, uint count, uint align, uint flag);   // 0x00921260
};

// EASTL prime_rehash_policy: {load factor, growth factor, next resize}
struct PrimeRehashPolicy {
    float mMaxLoadFactor;                           // +0x00
    float mGrowthFactor;                            // +0x04
    uint  mNextResize;                              // +0x08
    uint GetBucketCount(uint n) const;              // 0x009213c0
};

// EA::Stopwatch ctor used by PickRandomKey (0x93a560, units + use-tsc)
struct StopwatchE {
    uint mStartLo, mStartHi, mAccLo, mAccHi;        // +0x00
    uint mUnits;                                    // +0x10
    char mPad[0x24 - 0x14];
    void ctor(int units, bool useTsc);              // 0x0093a560
};

// --- external cdecl/free callees ---
void* __cdecl operator_new(uint, const char*, int, int, const char*, int);   // 0x00f473a0
void  __cdecl FUN_00f47380(void* p);                                        // 0x00f47380
void* __cdecl FUN_00a17090(uint size);
void* __cdecl FUN_00a17100(void* p);
void* __cdecl copy_impl(void* first, void* last, void* dst);   // 0x006782c0
uint  __cdecl FUN_00921340(uint n);
uint  __cdecl FUN_009213c0(uint n);
void* __cdecl FUN_00a248a0(void* a);
void* __cdecl FUN_008de1a0();                                  // 0x008de1a0 Debug::ObjectError
void* __cdecl RBTreeIncrement(void* node);                     // 0x00921580
void  __cdecl FUN_00921340_dummy();
void* __cdecl eastl_copy(void*, void*, void*);
extern "C" void* DAT_016e61a8;
extern "C" void  FUN_0112c600();
extern "C" void  FUN_0112c620();
extern "C" int   FUN_00a26fa0_c;

// --- stack stopwatch used by the timing wrapper (EA::Stopwatch) ---
struct Stopwatch {
    uint      mStartLo;   // +0x00
    uint      mStartHi;   // +0x04
    uint      mAccLo;     // +0x08
    uint      mAccHi;     // +0x0c
    uint      mMode;      // +0x10
    float     mScale;     // +0x14  ticks -> seconds
    float*    mpTarget;   // +0x18  accumulator handed to the ctor
    uint      mPad;       // +0x1c
    Stopwatch(float* target);    // 0x00a248a0
    long long Elapsed();         // 0x0093a3a0
};

struct AudioSystem {
    uchar pad[0x140000];

    // 00a2d790
    bool RegisterPrimitive(void* p);
    // 00a2d880
    bool  FUN_00a2d880(uint key, void* out);
    // 00a2d940 : ctor
    void* FUN_00a2d940(void* arg);
    // 00a2d990
    int FUN_00a2d990(void* arg);
    // 00a2d9d0 : dtor
    void* FUN_00a2d9d0(uchar flags);
    // 00a2da30
    void FUN_00a2da30();
    // 00a2dc40
    void SetupPropertyAggregationRules();
    // 00a2de20
    bool DestroySubmixes();
    // 00a2dfe0  (out of line: the retail call at 0x00a2e5b5 is a real call, not an inline)
    __declspec(noinline) void FUN_00a2dfe0(void* p);
    // 00a2e060
    uint& FUN_00a2e060(const uint& k);
    // 00a2e0e0
    int FUN_00a2e0e0(uint* p);
    // 00a2e1b0
    void* FUN_00a2e1b0(void* out, void* node, void* parent);
    // 00a2e260
    void FUN_00a2e260(void* p);
    // 00a2e2f0
    AudioSystem* FUN_00a2e2f0(void* p);
    // 00a2e420
    void* FUN_00a2e420(void* p);
    // 00a2e4c0
    void* FUN_00a2e4c0(void* p);
};

// helper: virtual call at vtable byte offset
static void* vc(void* obj, int off) {
    return ((void**)*(void**)obj)[off / 4];
}

// @ 0x00a2d790
bool AudioSystem::RegisterPrimitive(void* p) {
    if (!p) return false;
    typedef char (__thiscall *F0)(void*);
    if (!((F0)vc(p, 0x10))(p)) return false;
    uint id = ((uint (__thiscall*)(void*))vc(p, 0x18))(p);
    uint key = id;
    void* it = 0;
    ((XF*)((uchar*)this + 0x13f4))->hashtable_find(&key, &it);
    if (*(uint*)it != *(uint*)(*(uint*)((uchar*)this + 0x13f8) +
                              *(int*)((uchar*)this + 0x13fc) * 4))
        return false;
    void* elem = ((XF*)((uchar*)this + 0x13f4))->FUN_00a2a150(&key);
    ((XF*)elem)->AutoRef_op(&key);
    ((void (__thiscall*)(void*, uint))vc(this, 0x38))(this, 0x399197f);
    ((void (__thiscall*)(void*, uint, uint))vc(this, 0x40))(this, 0x3475385, id);
    ((void (__thiscall*)(void*))vc(this, 0x58))(this);
    ((void (__thiscall*)(void*, uint))vc(this, 0x38))(this, 0x3991984);
    ((void (__thiscall*)(void*, uint, uint))vc(this, 0x40))(this, 0x3475385, id);
    float f = ((float (__thiscall*)(void*))vc(p, 0x1c))(p);
    ((void (__thiscall*)(void*, uint, float))vc(this, 0x3c))(this, 0x34753aa, f);
    ((void (__thiscall*)(void*))vc(this, 0x58))(this);
    return true;
}

// @ 0x00a2d880
bool AudioSystem::FUN_00a2d880(uint key, void* out) {
    (void)out;
    void* it[2];   // returned iterator (8 bytes: node + bucket count)
    ((XF*)((uchar*)this + 0x23e4))->hashtable_find(it, &key);
    if (it[0] != *(void**)(*(uint*)((uchar*)this + 0x23e8) +
                           *(int*)((uchar*)this + 0x23ec) * 4))
        return false;
    void* node = FUN_00a17090(0x1c);
    if (node) node = ((void* (__thiscall*)(void*, void*))FUN_00a17100)(node, this);
    ((void (__thiscall*)(void*))vc(node, 0))(node);
    void* slot = ((XF*)((uchar*)this + 0x23e4))->FUN_00a2a510(&key);
    *(void**)slot = node;
    return true;
}

// @ 0x00a2d940
void* AudioSystem::FUN_00a2d940(void* arg) {
    *(void**)this = (void*)0x1452cb0;
    ((XF*)((uchar*)this + 4))->FUN_00a26fa0(arg);
    return this;
}

// @ 0x00a2d990
int AudioSystem::FUN_00a2d990(void* arg) {
    if (*(int*)((uchar*)arg + 8) == 0x21407ee) {
        void* out;
        int* r = (int*)((XF*)((uchar*)this + 4))->rbtree_find(&out, (uchar*)arg + 4);
        if ((uchar*)this + 8 != (uchar*)*r)
            return 1;
    }
    return 0;
}

// @ 0x00a2d9d0
void* AudioSystem::FUN_00a2d9d0(uchar flags) {
    ((XF*)((uchar*)this + 4))->DoNukeSubtree(*(void**)((uchar*)this + 0x10));
    *(void**)this = (void*)0x13eb394;
    if (flags & 1) FUN_00f47380(this);
    return this;
}

// @ 0x00a2da30  (PickRandomKey; EASTL hashtable + EH)
void AudioSystem::FUN_00a2da30() {
    // Timing wrapper: Stopwatch(int units = 4, bool useTsc = false), then its inlined
    // Start(): units == 1 uses rdtsc, otherwise QueryPerformanceCounter.
    StopwatchE sw;
    sw.ctor(4, false);
    uint nowLo, nowHi;
    if (sw.mUnits == 1) {
        unsigned long long t = __rdtsc();
        nowLo = (uint)t;
        nowHi = (uint)(t >> 32);
    } else {
        long long ctr = 0;
        QueryPerformanceCounter(&ctr);
        nowLo = (uint)ctr;
        nowHi = (uint)(ctr >> 32);
    }
    sw.mStartLo = nowLo;
    sw.mStartHi = nowHi;
    sw.mAccLo = 0;
    sw.mAccHi = 0;

    // The audio debug object owns the primitive-key set.
    void* dbg = FUN_008de1a0();
    if (!dbg)
        return;

    // slot 0x38 fills {records begin/end/cap, functor, key array}
    struct Functor { void* vtbl; } fn;
    fn.vtbl = (void*)0x1452a00;
    void* records[3] = {0, 0, 0};
    void* keys[5] = {0, 0, 0, 0, 0};
    ((void (__thiscall*)(void*, void*, void*, void*))vc(dbg, 0x38))(dbg, records, &fn, keys);

    // Retire the previous key table and its nodes.
    uchar* ht = (uchar*)this + 0x80424;
    ((XF*)ht)->DoFreeNodes(*(void**)(ht + 4), *(void**)(ht + 8));
    *(uint*)(ht + 0xc) = 0;

    uint n = (uint)(((uchar*)records[1] - (uchar*)records[0]) / 0xc);
    uchar* out = 0;
    for (uint i = 0; i < n; ++i) {
        uchar* r = (uchar*)records[0] + i * 0xc;
        void* key = keys[i];
        // The key is an AutoRefCount wrapper: +4 holds the counted object.
        if (key)
            ((void (__thiscall*)(void*))*(void**)*(void**)((uchar*)key + 4))(*(void**)((uchar*)key + 4));

        struct KeyRec { uint a, b, c; void* key; } tmp;
        tmp.a = *(uint*)(r + 0);
        tmp.b = *(uint*)(r + 4);
        tmp.c = *(uint*)(r + 8);
        tmp.key = key;
        if (key)
            ((void (__thiscall*)(void*))*(void**)*(void**)((uchar*)key + 4))(*(void**)((uchar*)key + 4));
        ((XF*)ht)->FUN_00a26a20(&out, &tmp, 0);
        if (tmp.key) {
            void* t = *(void**)((uchar*)tmp.key + 4);
            ((void (__thiscall*)(void*))((void**)*(void**)t)[1])(t);
        }
        if (key) {
            void* t = *(void**)((uchar*)key + 4);
            ((void (__thiscall*)(void*))((void**)*(void**)t)[1])(t);
        }
    }

    // Free the two temporary arrays (EASTL allocates 4 bookkeeping bytes before the block).
    if (keys[0] && *(uint*)((uchar*)keys[0] - 4) != 0)
        FUN_00f47380(keys[0]);
    if (records[0] && *(uint*)((uchar*)records[0] - 4) != 0)
        FUN_00f47380(records[0]);
}

// @ 0x00a2dc40  (SetupPropertyAggregationRules; EASTL + EH)
void AudioSystem::SetupPropertyAggregationRules() {
    // Clear the aggregation-rule table (at +0x11a3d8) and its node storage.
    uchar* ht = (uchar*)this + 0x11a3d8;
    ((XF*)ht)->DoFreeNodes(*(void**)(ht + 4), *(void**)(ht + 8));
    *(uint*)(ht + 0xc) = 0;

    // Fetch the rule set from the audio system. `this` is polymorphic, so [this] is its vtable:
    // slot 0xf4(name, &out, tag) returns the object the slot 0x138 predicate tests.
    void* handle = 0;
    void* got = ((void* (__thiscall*)(void*, const char*, void**, uint))vc(this, 0xf4))
                    (this, "aggregation", &handle, 0x21407ee);
    if (!((char (__thiscall*)(void*, void*))vc(this, 0x138))(this, got)) {
        if (handle)
            ((void (__thiscall*)(void*))vc(handle, 4))(handle);      // Release
        return;
    }

    // Build a temporary rbtree/set of {key, value} from the handle's key list.
    struct SetNode { SetNode *left, *right, *parent; uint colour, key, value; };
    SetNode header;
    header.left = 0;
    header.right = 0;
    header.parent = 0;
    header.colour = 0;
    ((uint*)&header)[4] = 0;
    *(SetNode**)((uchar*)&header + 0x00) = &header;
    *(SetNode**)((uchar*)&header + 0x04) = &header;

    ((void (__thiscall*)(void*, void*, int))vc(handle, 0x0c))(handle, &header, 1);

    for (SetNode* node = *(SetNode**)((uchar*)&header + 4); node != &header;
         node = (SetNode*)RBTreeIncrement(node)) {
        uint key = node->key;
        uint val = 0;
        ((void (__thiscall*)(void*, uint, uint*))vc(handle, 0x38))(handle, key, &val);

        void* it[2] = {0, 0};
        ((XF*)ht)->hashtable_find(it, &key);
        if (it[0] == *(void**)(*(uint*)(ht + 4) + *(int*)(ht + 8) * 4)) {
            struct Pair { uint key, value; } pair;
            pair.key = key;
            pair.value = val;
            void* slot = 0;
            ((XF*)ht)->FUN_00a26ce0(&slot, &pair, 0);
            it[0] = slot;
        }
        *(uint*)((uchar*)it[0] + 4) = val;
    }

    // Tear the temporary tree down node by node.
    SetNode* node = *(SetNode**)((uchar*)&header + 8);
    while (node) {
        SetNode* next = node->right;
        ((XF*)&header)->DoNukeSubtree(node->left);
        FUN_00f47380(node);
        node = next;
    }

    if (handle)
        ((void (__thiscall*)(void*))vc(handle, 4))(handle);          // Release
}

// @ 0x00a2de20  (DestroySubmixes)
bool AudioSystem::DestroySubmixes() {
    if (DAT_016e61a8) FUN_0112c600();
    uint* begin = *(uint**)((uchar*)this + 0x119ba4);
    uint* end = *(uint**)((uchar*)this + 0x119ba8);
    for (uint* it = begin; it != end; ++it) {
        void* o = (void*)*it;
        if (o) ((void (__thiscall*)(void*))vc(o, 0))(o);
        ((XF*)o)->FUN_00a21390();
        ((void (__thiscall*)(void*, void*))vc(this, 0x170))(this, o);
        if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
    }
    for (uint* it = *(uint**)((uchar*)this + 0x119ba4),
             * ie = *(uint**)((uchar*)this + 0x119ba8); it != ie; ++it) {
        void* o = (void*)*it;
        if (o) ((void (__thiscall*)(void*))vc(o, 0))(o);
        ((XF*)o)->FUN_00a2bb30();
        if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
    }
    // vector::erase(begin(), end()): move nothing, destroy the tail, drop the size
    uint* first = *(uint**)((uchar*)this + 0x119ba4);
    uint* last = *(uint**)((uchar*)this + 0x119ba8);
    uint* newEnd = (uint*)copy_impl(last, last, first);
    uint* tail = *(uint**)((uchar*)this + 0x119ba8);
    for (uint* p = newEnd; p < tail; ++p) {
        void* o = (void*)*p;
        if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
    }
    *(uint**)((uchar*)this + 0x119ba8) = first;
    if (DAT_016e61a8) FUN_0112c620();
    return true;
}

// @ 0x00a2dfe0
void AudioSystem::FUN_00a2dfe0(void* p) {
    uchar* vec = (uchar*)this;
    void** cur = *(void***)(vec + 4);
    if (cur < *(void***)(vec + 8)) {
        *(void***)(vec + 4) = cur + 1;
        if (cur) {
            void* o = *(void**)p;
            *cur = o;
            if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
        }
    } else {
        ((XF*)vec)->FUN_00a2ac20(cur, p);
    }
}

// @ 0x00a2e060  (eastl::map<unsigned long,unsigned long>::operator[])
uint& AudioSystem::FUN_00a2e060(const uint& k) {
    // EASTL rbtree: header node at +4, root at +0xc; node = {left, right, parent, colour, key@0x10, value@0x14}
    uchar* tree = (uchar*)this;
    uchar* header = tree + 4;
    uchar* node = *(uchar**)(tree + 0xc);
    uchar* cand = header;
    while (node) {
        if (k <= *(uint*)(node + 0x10)) {
            cand = node;
            node = *(uchar**)(node + 4);
        } else {
            node = *(uchar**)node;
        }
    }
    if (cand != header && k >= *(uint*)(cand + 0x10))
        return *(uint*)(cand + 0x14);
    uint pair[2];
    pair[0] = k;
    pair[1] = 0;
    uchar* out;
    *(char*)&out = 0;
    ((XF*)tree)->DoInsertValue(&out, cand, pair, *(uint*)&out);
    return *(uint*)(out + 0x14);
}

// @ 0x00a2e0e0
int AudioSystem::FUN_00a2e0e0(uint* p) {
    uchar* ht = (uchar*)this;
    int before = *(int*)(ht + 0xc);
    uint idx = *p % *(uint*)(ht + 8);
    uint* bucket = (uint*)(*(int*)(ht + 4) + idx * 4);
    if (*bucket) {
        uint* node;
        for (;;) {
            node = (uint*)*bucket;
            if (*p == *node) break;
            bucket = node + 9;
            if (!node[9]) break;
        }
        uint v = *bucket;
        while (v != 0 && (node = (uint*)*bucket, *p == *node)) {
            *bucket = node[9];
            FUN_00f47380(node);
            *(int*)(ht + 0xc) -= 1;
            v = *bucket;
        }
    }
    return before - *(int*)(ht + 0xc);
}

// @ 0x00a2e1b0
void* AudioSystem::FUN_00a2e1b0(void* out, void* node, void* parent) {
    int* o = (int*)out;
    int* par = (int*)parent;
    int iVar1 = par[9];
    o[1] = (int)parent;
    *o = iVar1;
    while (iVar1 == 0) {
        o[1] += 4;
        iVar1 = *(int*)o[1];
        *o = iVar1;
    }
    int* puVar2 = (int*)*par;
    if (puVar2 == node) {
        *par = puVar2[9];
    } else {
        for (int* puVar3 = (int*)puVar2[9]; puVar3 != node; puVar3 = (int*)puVar3[9])
            puVar2 = puVar3;
        puVar2[9] = ((int*)node)[9];
    }
    FUN_00f47380(node);
    *(int*)((uchar*)this + 0xc) -= 1;
    return out;
}

// @ 0x00a2e260
void AudioSystem::FUN_00a2e260(void* p) {
    uchar* vec = (uchar*)this;
    uchar* cur = *(uchar**)(vec + 4);
    if (cur < *(uchar**)(vec + 8)) {
        *(uchar**)(vec + 4) = cur + 0x14;
        if (cur) {
            memcpy(cur, p, 0x10);
            void* o = *(void**)((uchar*)p + 0x10);
            *(void**)(cur + 0x10) = o;
            if (o) ((void (__thiscall*)(void*))vc(o, 0))(o);
        }
    } else {
        ((XF*)vec)->FUN_00a2af30(cur, p);
    }
}

// @ 0x00a2e2f0  (fixed_hashtable ctor: pool at +0x8c, buckets at +0x34)
AudioSystem* AudioSystem::FUN_00a2e2f0(void* p) {
    uchar* base = (uchar*)this;

    // Inline fixed_pool_base at +0x8c: 0xf0-byte blocks, 0xc of them, 4-byte aligned.
    FixedPoolLocal pool;
    pool.mpHead = 0;
    pool.mPad[0] = pool.mPad[1] = pool.mPad[2] = pool.mPad[3] = 0;
    pool.mPad[4] = (uint)(base + 0x34);            // +0x14: preallocated bucket-array buffer
    pool.init(base + 0x8c, 0xf0, 0xc, 4, 0);

    // Hashtable ctor: bucket count from the prime policy, five (unused) functor refs and the pool.
    uint buckets = FUN_00921340(0x15);
    ((XF*)base)->HashtableCtor(buckets, &p, &p, &p, &p, &p, &pool);

    *(float*)(base + 0x10) = 10000.0f;
    *(float*)(base + 0x14) = 2.0f;
    *(uint*)(base + 0x18) = 0;

    // The table's policy is (load 10000, growth 2); a fresh policy object stands in
    // for it when deciding whether the bucket count has to grow.
    PrimeRehashPolicy policy;
    policy.mMaxLoadFactor = 10000.0f;
    policy.mGrowthFactor = 2.0f;
    policy.mNextResize = 0;
    uint bc = policy.GetBucketCount(*(uint*)(base + 0xc));
    if (*(uint*)(base + 8) < bc)
        ((XF*)base)->FUN_00a22220(bc);

    // Link the bucket sentinels: start at the first non-empty bucket of p's array.
    uchar* desc = (uchar*)p;
    uchar** bucketArray = *(uchar***)(desc + 4);
    uint index = *(uint*)(desc + 8);
    uchar** slot = bucketArray + index;
    uchar* first = *slot;
    uchar** scan = bucketArray;
    uchar* head = *scan;
    if (!head) {
        do {
            ++scan;
            head = *scan;
        } while (!head);
    }
    ((XF*)base)->FUN_00a2b230(head, scan, first, slot);
    return this;
}

// @ 0x00a2e420
void* AudioSystem::FUN_00a2e420(void* p) {
    void* node = *(void**)((uchar*)this + 0x1c);
    if (node) {
        *(void**)((uchar*)this + 0x1c) = *(void**)node;
    } else {
        node = operator_new(*(uint*)((uchar*)this + 0x2c), "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    if (node) {
        *(uint*)node = *(uint*)p;
        *(uint*)((uchar*)node + 4) = *(uint*)((uchar*)p + 4);
        ((XF*)((uchar*)node + 8))->FUN_00a26fa0((uchar*)p + 8);
    }
    *(uint*)((uchar*)node + 0x24) = 0;
    return node;
}

// @ 0x00a2e4c0
void* AudioSystem::FUN_00a2e4c0(void* p) {
    Stopwatch sw((float*)((uchar*)this + 0x5c));
    ((XF*)((uchar*)this + 0x28))->Lock((void*)0x1452970);
    long long t = sw.Elapsed();
    *(float*)((uchar*)this + 0x58) += (float)t * sw.mScale;
    uint* it = *(uint**)((uchar*)this + 0x14);
    uint* end = *(uint**)((uchar*)this + 0x18);
    for (; it != end; ++it) {
        void* elem = (void*)*it;
        if (elem == p) {
            ((XF*)((uchar*)this + 0x28))->Unlock();
            long long t2 = sw.Elapsed();
            *sw.mpTarget += (float)t2 * sw.mScale;
            return elem;
        }
    }
    void* tmp = p;
    if (tmp) ((void (__thiscall*)(void*))vc(tmp, 4))(tmp);
    ((AudioSystem*)((uchar*)this + 0x14))->FUN_00a2dfe0(&tmp);
    if (tmp) ((void (__thiscall*)(void*))vc(tmp, 8))(tmp);
    ((XF*)((uchar*)this + 0x28))->Unlock();
    long long t3 = sw.Elapsed();
    *sw.mpTarget += (float)t3 * sw.mScale;
    return p;
}
