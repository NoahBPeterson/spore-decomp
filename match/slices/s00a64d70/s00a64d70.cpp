// Slice s00a64d70 (batch gold7).  Region 0x00a64d70-0x00a65e4b.
// EA::Audio::Eapd (EA's embedded Pure Data): the Instance / InstanceManager
// family, the small intrusive hashtable (bucket array + intrusive nodes +
// embedded node pool) they are built on, the GroupMap wrapper and the tiny
// vtable-dispatch / copy helpers around them.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_1403934[];
extern "C" char g_1455648[];
extern "C" char g_1454fac[];
extern "C" char g_1455668[];

#include "s00a64d70.h"

// Mutable sentinel that keeps the CreateCanvas call from being folded away in
// the callers that are byte-matched (the real body is not recovered yet).
static volatile uint32_t gCreateCanvasResult;

// ===========================================================================
// vtable-dispatch wrapper: forward one argument to slot 2 of the vtable
// ===========================================================================
// @ 0x00a657f0
void* VtblOwner::DispatchSlot2(void* arg, void* unused)
{
    (void)unused;
    typedef void* (__thiscall* Fn)(void*, void*);
    Fn fn = (Fn)(*(void***)this)[2];
    return fn(this, arg);
}

// ===========================================================================
// flat 0x38-byte copy constructor: copy 14 words, rewriting the two vtable
// words with this class's own vtable
// ===========================================================================
// @ 0x00a65ab0
Copyable38* Copyable38::CopyCtor(const Copyable38* src)
{
    uint32_t* d = mW;
    const uint32_t* s = src->mW;
    d[0]  = (int)g_1454fac;      // own vtable
    d[1]  = s[1];
    d[2]  = s[2];
    d[3]  = (int)g_1454fac;      // nested holder's vtable
    d[4]  = s[4];
    d[5]  = s[5];
    d[6]  = s[6];
    d[7]  = s[7];
    d[8]  = s[8];
    d[9]  = s[9];
    d[10] = s[10];
    d[11] = s[11];
    d[12] = s[12];
    d[13] = s[13];
    return this;
}

// ===========================================================================
// FixedPool::AllocSize -- vtable-slot-2 allocation on the embedded allocator
// ===========================================================================
void* FixedPool::AllocSize(uint32_t size)
{
    typedef void* (__thiscall* Fn)(void*, uint32_t);
    return ((Fn)(*(void***)this)[2])(this, size);
}

void* FixedPool::AllocPooled()
{
    typedef void* (__thiscall* Fn)(void*, uint32_t);
    return ((Fn)(*(void***)&mOverflowAllocator)[2])(&mOverflowAllocator, mnNodeSize);
}

// ===========================================================================
// FreePool::Free -- hand a node back to the pool, or to the overflow allocator
// when the node did not come from the fixed pool buffer.
// ===========================================================================
// @ 0x00a65800
void PoolFreeView::FreeNode(void* node)
{
    FixedPool* pool = &mPool;
    --pool->mnCurrentSize;
    if (node >= pool->mpPoolBegin && node < pool->mpPoolEnd)
    {
        *(void**)node = pool->mpHead;
        pool->mpHead = node;
        return;
    }
    typedef void (__thiscall* Fn)(void*, void*);
    ((Fn)(*(void***)&pool->mOverflowAllocator)[3])(&pool->mOverflowAllocator, node);
}

// ===========================================================================
// HashtableBig::AllocNode -- pull a node from the pool and initialise it
// ===========================================================================
// @ 0x00a65c70
void* HashtableBig::AllocNode(const void* value)
{
    void* node = mAlloc.mpHead;
    if (node)
        mAlloc.mpHead = *(void**)node;
    else
        node = mAlloc.AllocPooled();
    if (node)
    {
        uint32_t cur = ++mAlloc.mnCurrentSize;
        if (cur > mAlloc.mnPeakSize)
            mAlloc.mnPeakSize = cur;
        *(uint32_t*)node = *(const uint32_t*)value;
        *(uint32_t*)((char*)node + 4) = *(const uint32_t*)((const char*)value + 4);
        void** link = (void**)((char*)node + 8);
        link[1] = link;
        *link = link;
    }
    *(uint32_t*)((char*)node + 0x10) = 0;
    return node;
}

// ===========================================================================
// HashtableBig::EraseFn -- unlink one node from its bucket, fix up the pool
// free list and (for the InstanceMap table) tear down the Instance.
// ===========================================================================
// @ 0x00a65b10
void* HashtableBig::EraseFn(void* out, void* node, void** bucket)
{
    HashNode20* n = (HashNode20*)node;          // edx
    uint32_t* o = (uint32_t*)out;               // esi
    void** b = bucket;                          // ebx (never advanced)
    HashNode20* next = *(HashNode20**)((char*)n + 0x14);
    o[1] = (uint32_t)b;
    o[0] = (uint32_t)next;
    /* if the next-link is null, advance the stored bucket cursor to the next
       non-empty slot (the original bumps o->bucket, not the ebx copy) */
    while (next == 0) {
        o[1] += 4;
        next = *(HashNode20**)o[1];
        o[0] = (uint32_t)next;
    }
    /* unlink `node` from its chain: walk the +0x14 links to its predecessor */
    HashNode20* p = *(HashNode20**)b;
    if (p == n) {
        *(HashNode20**)b = *(HashNode20**)((char*)p + 0x14);
    } else {
        HashNode20* c = p;
        HashNode20* e = *(HashNode20**)((char*)c + 0x14);
        while (e != n) {
            c = e;
            e = *(HashNode20**)((char*)e + 0x14);
        }
        *(HashNode20**)((char*)c + 0x14) = *(HashNode20**)((char*)e + 0x14);
    }
    uint32_t minus1 = 0xffffffffu;
    if ((uint32_t*)n != *(uint32_t**)((char*)this + 0x50)) {
        *(uint32_t*)((char*)this + 0x44) += minus1;
        if ((void*)n >= *(void**)((char*)this + 0x38) &&
            (void*)n <  *(void**)((char*)this + 0x3c)) {
            *(uint32_t*)((char*)n) = *(uint32_t*)((char*)this + 0x40);
            *(void**)((char*)this + 0x40) = n;
            *(uint32_t*)((char*)this + 0x0c) += minus1;
            return o;
        }
        typedef void (__thiscall* Fn)(void*, void*);
        ((Fn)(*(void***)((char*)this + 0x28))[3])((char*)this + 0x28, n);
    }
    *(uint32_t*)((char*)this + 0x0c) += minus1;
    return o;
}

// ===========================================================================
// HashtableBig::Rehash16 -- rebuild the bucket array, relinking nodes whose
// next-link lives at +0x10, then free the old array (to the pool when it came
// from there, otherwise to the overflow allocator).
// ===========================================================================
// @ 0x00a658b0
void* HashtableBig::Rehash16(uint32_t newCount)
{
    void** newBuckets = (void**)AllocBuckets(newCount);
    uint32_t i = 0;
    if (mnBucketCount > i)
    {
        do
        {
            void* node = mpBucketArray[i];
            while (node)
            {
                uint32_t h = *(uint32_t*)node % newCount;
                HashNode20* next = *(HashNode20**)((char*)node + 0x10);
                mpBucketArray[i] = next;
                *(void**)((char*)node + 0x10) = newBuckets[h];
                newBuckets[h] = node;
                node = mpBucketArray[i];
            }
            ++i;
        } while (i < mnBucketCount);
    }
    void** old = (void**)mpBucketArray;
    if (mnBucketCount > 1 && old != (void**)mAlloc.mpBucketBuffer)
    {
        --mAlloc.mnCurrentSize;
        if (old >= (void**)mAlloc.mpPoolBegin && old < (void**)mAlloc.mpPoolEnd)
        {
            *old = mAlloc.mpHead;
            mAlloc.mpHead = old;
        }
        else
        {
            typedef void (__thiscall* Fn)(void*, void*);
            ((Fn)(*(void***)&mAlloc.mOverflowAllocator)[3])(&mAlloc.mOverflowAllocator, old);
        }
    }
    mpBucketArray = (HashNode20**)newBuckets;
    mnBucketCount = newCount;
    /* retail returns the OLD bucket array (the value left in eax by the free
       path), not the freshly allocated one */
    return old;
}

// ===========================================================================
// HashtableBig::Rehash20 -- same, nodes whose next-link lives at +0x14
// ===========================================================================
// @ 0x00a659e0
void* HashtableBig::Rehash20(uint32_t newCount)
{
    void** newBuckets = (void**)AllocBuckets20(newCount);
    uint32_t i = 0;
    if (mnBucketCount > i)
    {
        do
        {
            void* node = mpBucketArray[i];
            while (node)
            {
                uint32_t h = *(uint32_t*)node % newCount;
                HashNode20* next = *(HashNode20**)((char*)node + 0x14);
                mpBucketArray[i] = next;
                *(void**)((char*)node + 0x14) = newBuckets[h];
                newBuckets[h] = node;
                node = mpBucketArray[i];
            }
            ++i;
        } while (i < mnBucketCount);
    }
    void** old = (void**)mpBucketArray;
    if (mnBucketCount > 1 && old != (void**)mAlloc.mpBucketBuffer)
    {
        --mAlloc.mnCurrentSize;
        if (old >= (void**)mAlloc.mpPoolBegin && old < (void**)mAlloc.mpPoolEnd)
        {
            *old = mAlloc.mpHead;
            mAlloc.mpHead = old;
        }
        else
        {
            typedef void (__thiscall* Fn)(void*, void*);
            ((Fn)(*(void***)&mAlloc.mOverflowAllocator)[3])(&mAlloc.mOverflowAllocator, old);
        }
    }
    mpBucketArray = (HashNode20**)newBuckets;
    mnBucketCount = newCount;
    /* retail returns the OLD bucket array (the value left in eax by the free
       path), not the freshly allocated one */
    return old;
}

// ===========================================================================
// HashtableBig::InitPool10 -- init the node pool, seed the table, set the load
// factor and rehash if the initial count is still too small (PatchMap shape)
// ===========================================================================

// ===========================================================================
// HashtableBig::InitPool20 -- same, InstanceMap shape
// ===========================================================================

// ===========================================================================
// SymbolDispatchSlot::Dispatch -- forward to the interface, then look the
// symbol up and hand it to the table's float handler
// ===========================================================================
// @ 0x00a64e60
uint32_t SymbolDispatchSlot::Dispatch(uint32_t sym, float f)
{
    uint8_t found = 0;
    if (mpTarget)
    {
        typedef void (__thiscall* Fn)(void*, uint32_t, float);
        ((Fn)(*(void***)mpTarget)[2])(mpTarget, sym, f);
    }
    HashNode16* local[2];
    mpMap->FindNode(local, &sym);
    if (mpMap->mpBucketArray[mpMap->mnBucketCount] == local[0])
        return found;
    /* the float handler is a member (thiscall): `this` = local[0]+4 in ecx */
    typedef uint32_t (__thiscall* FloatFn)(void*, float);
    return ((FloatFn)MakeFloatHandler)((char*)local[0] + 4, f);
}

// ===========================================================================
// GroupAdder::AddGroup -- insert the group's symbol, then notify the listener
// ===========================================================================
// @ 0x00a65070
uint32_t GroupAdder::AddGroup(void* group)
{
    uint32_t key = *(uint32_t*)((char*)group + 0x2c);
    Hashtable* map = mpMap;
    HashNode16* local[2];
    map->FindNode(local, &key);
    if (map->mpBucketArray[map->mnBucketCount] == (HashNode16*)local[0])
    {
        /* 0xa646f0 is IterHelper::MakeEntryIter(entry): this = a stack
           IterHelper, entry = group; it[0] = *(group+0x34), it[1] = group. */
        typedef void* (__thiscall* MakeIterFn)(void*, void*);
        uint32_t entry[2];
        ((MakeIterFn)MakeEntryIter)(entry, group);
        /* retail fills mKey, mV1 = it[0] and mV2 = it[1] (it leaves mpNext
           unused: Insert only copies the three leading words) */
        HashNode16 pair;
        pair.mKey   = key;
        pair.mV1    = entry[0];
        pair.mV2    = entry[1];
        pair.mpNext = 0;
        InsertResult res;
        map->Insert(&res, &pair, 0);
        /* 0xa64710 is a thiscall taking the argument in ecx */
        typedef void (__thiscall* ResetFn)(void*);
        ((ResetFn)ResetAndClear)(&res);
        ((ResetFn)ResetAndClear)(&local);
        if (mpListener)
        {
            typedef void (__thiscall* Fn)(void*, void*, uint32_t, void*);
            ((Fn)(*(void***)mpListener)[1])(mpListener,
                *(void**)((char*)group + 0x34), key, *(void**)((char*)group + 0x30));
        }
        return 1;
    }
    /* 0xa64730 is EapdAssetManager::PushNode(node), called with this = the
       found node's value word (local[0]+4) */
    typedef uint32_t (__thiscall* PushFn)(void*, void*);
    return ((PushFn)PushNode)((char*)local[0] + 4, group);
}

// ===========================================================================
// GroupMap::~GroupMap (scalar deleting)
// ===========================================================================
// ===========================================================================
// FixedHashtableAllocator::InitBucketsEx -- size the bucket buffer from the
// element count and hand a new buffer to the overflow allocator
// ===========================================================================
// @ 0x00a656b0
bool FixedHashtableAllocator::InitBucketsEx(uint32_t size, uint32_t a1, uint32_t a2)
{
    if (mpBucketBuffer)
    {
        typedef void (__thiscall* Fn)(void*, void*);
        ((Fn)(*(void***)this)[3])(this, mpBucketBuffer);
        mpBucketBuffer = 0;
    }
    uint32_t n = (uint32_t)(uint64_t)((float)size * 1.3333334f);
    mnBucketCount = n;
    if (n < 3)
        mnBucketCount = 3;
    else
        mnBucketCount = FUN_00921340(n) + 1;
    uint32_t want = mnBucketCount * 4;
    if (want == 0x14)
        return Init(0x14, size + 1, (void*)a1, (void*)a2);
    if (Init(0x14, size, (void*)a1, (void*)a2))
    {
        typedef void* (__thiscall* Fn)(void*, uint32_t);
        void* buf = ((Fn)(*(void***)this)[2])(this, mnBucketCount * 4);
        mpBucketBuffer = buf;
        return buf != 0;
    }
    return false;
}

// ===========================================================================
// Hashtable::Construct -- initialise the fields the small table ctor owns
// ===========================================================================
// The allocator InitNamed builds on the stack: its destructor (resetting the vtable) covers the Construct call.
// Out-of-line entry points as other objects see them (bodies not visible to this caller).
struct HashtableCalls_a65180 {
    Hashtable* Construct(const void* nameSlot);                 // 0xa64f80
    Hashtable* InitNamed(void* nameSlot, const char* name);    // 0xa65180
};
struct NamedAllocTemp_a65180 {
    void*       mpVtbl;   // +0x00
    int         mA;       // +0x04
    const char* mpName;   // +0x08
    NamedAllocTemp_a65180(const NamedAllocTemp_a65180& o, const char* name) : mpVtbl((void*)&g_1454fac), mA(o.mA), mpName(name) {}
    ~NamedAllocTemp_a65180() { mpVtbl = (void*)g_1403934; }
};

// @ 0x00a65180
Hashtable* Hashtable::InitNamed(void* nameSlot, const char* name)
{
    const uint32_t* src = (const uint32_t*)nameSlot;
    NamedAllocTemp_a65180 slot(*(const NamedAllocTemp_a65180*)src, name);
    ((HashtableCalls_a65180*)this)->Construct(&slot);
    return this;
}

// @ 0x00a64f80
Hashtable* Hashtable::Construct(const void* nameSlot)
{
    const uint32_t* slot = (const uint32_t*)nameSlot;
    mnElementCount   = 0;
    mfMaxLoadFactor  = 1.0f;
    /* +0x14 is the growth factor, a float in the original (retail stores
       2.0f with movss, not a plain integer 2) */
    *(float*)&mnGrowthFactor = 2.0f;
    mnNextResize     = 0;
    mPool.mpVtbl = (void*)&g_1454fac;
    mPool.mA     = slot[1];
    mPool.mpName = (const char*)slot[2];
    mnBucketCount    = 1;
    mpBucketArray    = (HashNode16**)0x154df28;  // static empty-bucket sentinel
    return this;
}

// ===========================================================================
// Hashtable::InitNamed -- build a name slot and construct the table
// ===========================================================================
// ===========================================================================
// Hashtable::Dispose -- release the bucket array and reset the allocator face
// ===========================================================================
// Destruction view of Hashtable (0x00a65000; callers reach it as Hashtable::Dispose): the bucket nodes are freed, then
// the array through the allocator member, whose own destructor resets its vtable.
struct HashPoolVt_a65000 {
    void* s0; void* s1; void* s2;
    void (__thiscall* Free)(void* self, void* p);   // +0xc
};
struct HashPool_a65000 {
    HashPoolVt_a65000* vt;
    uint32_t mA;
    const char* mpName;
    void Free(void* p) { vt->Free(this, p); }
    ~HashPool_a65000() { vt = (HashPoolVt_a65000*)g_1403934; }
};
struct HashtableDtorView_a65000 {
    uint32_t pad0;
    void** mpBucketArray;     // +0x04
    uint32_t mnBucketCount;   // +0x08
    uint32_t mnElementCount;  // +0x0c
    uint32_t pad10[3];
    HashPool_a65000 mPool;    // +0x1c
    void DoFreeBuckets(void** buckets, uint32_t n);   // 0x00a64c50
    ~HashtableDtorView_a65000();
};

// @ 0x00a65000
HashtableDtorView_a65000::~HashtableDtorView_a65000()
{
    DoFreeBuckets(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        mPool.Free(mpBucketArray);
}

// ===========================================================================
// Hashtable::Insert -- find-or-insert one {key,v1,v2} triple
// ===========================================================================
// @ 0x00a64d70
void Hashtable::Insert(InsertResult* out, const HashNode16* pair, const uint32_t* pKey)
{
    (void)pKey;
    uint32_t key = pair->mKey;
    HashNode16* node = *(&mpBucketArray[key % mnBucketCount]);
    HashNode16** bucket = &mpBucketArray[key % mnBucketCount];
    while (node)
    {
        if (key == node->mKey)
        {
            out->mpNode   = node;
            out->mbInserted = 0;
            out->mpBucket = bucket;
            return;
        }
        node = node->mpNext;
    }

    uint32_t local[2];
    ((HashPolicy*)&mfMaxLoadFactor)->NextBucketCount(local, mnBucketCount, mnElementCount, 1);
    typedef void* (__thiscall* AllocFn)(void*, uint32_t);
    HashNode16* fresh = (HashNode16*)((AllocFn)(*(void***)&mPool)[2])(&mPool, 0x10);
    if (fresh)
    {
        fresh->mKey = pair->mKey;
        fresh->mV1  = pair->mV1;
        fresh->mV2  = pair->mV2;
    }
    fresh->mpNext = 0;

    /* NextBucketCount writes the "changed" flag as a single byte (retail tests
       it with `cmp byte ptr [..]`), then the new count in the next dword */
    if (((uint8_t*)local)[0])
    {
        ResizeBuckets(local[1]);
        bucket = &mpBucketArray[key % local[1]];
    }

    fresh->mpNext = *bucket;
    *bucket = fresh;
    ++mnElementCount;

    out->mpNode   = fresh;
    out->mbInserted = 1;
    out->mpBucket = bucket;
}

// ===========================================================================
// Hashtable::Erase -- key-erase shared with the ObjectHashMap (0xa64be0)
// ===========================================================================
// @ 0x00a64be0
uint32_t Hashtable::Erase(uint32_t* key)
{
    uint32_t before = mnElementCount;
    uint32_t idx = *key % mnBucketCount;
    HashNode16** bucket = &mpBucketArray[idx];
    if (*bucket)
    {
        HashNode16* cur = *bucket;
        while (key ? (*key != cur->mKey) : 0)
        {
            bucket = &cur->mpNext;
            if (!*bucket)
                break;
            cur = *bucket;
        }
        while (*bucket)
        {
            HashNode16* node = *bucket;
            if (*key != node->mKey)
                break;
            *bucket = node->mpNext;
            typedef void (__thiscall* FreeFn)(void*, void*);
            ((FreeFn)(*(void***)&mPool)[3])(&mPool, node);
            --mnElementCount;
        }
    }
    return before - mnElementCount;
}

// ===========================================================================
// GroupMap::~GroupMap (base destructor) -- tear down the GroupMap's inner
// table at this+0x10 and install the base vtable.  The old duplicate
// `Hashtable::BaseDtor` definition that shared this address (and compiled to
// Dispose() on `this`) was removed: retail disposes this+0x10.
// ===========================================================================
// Destruction view of GroupMap (0x00a651e0, GroupMap::DisposeInner): the table member is destroyed, then the base
// resets the vtable.
struct GroupMapBase_a651e0 {
    void*      mpVtbl;     // +0x00
    void*      mpSelf;     // +0x04
    uint32_t   mField08;   // +0x08
    uint32_t   mField0c;   // +0x0c
    GroupMapBase_a651e0() : mpSelf((char*)this + 0x10), mField08(0), mField0c(0) {}
    ~GroupMapBase_a651e0() { mpVtbl = (void*)g_1455648; }
};
struct GroupMapDtorView_a651e0 : GroupMapBase_a651e0 {
    HashtableDtorView_a65000 mGroups;   // +0x10
    ~GroupMapDtorView_a651e0();
};

// @ 0x00a651e0
GroupMapDtorView_a651e0::~GroupMapDtorView_a651e0()
{
}

// GroupMap's deleting destructor (0x00a65500, GroupMap::ScalarDtor) with the destructor inlined.
void OperatorDeleteNothrow_a65500(void* p) throw();   // 0xf47380
struct GroupMapDelView_a65500 : GroupMapBase_a651e0 {
    HashtableDtorView_a65000 mGroups;   // +0x10
    GroupMapDelView_a65500* ScalarDtor(uint32_t flags);
};

// @ 0x00a65500
GroupMapDelView_a65500* GroupMapDelView_a65500::ScalarDtor(uint32_t flags)
{
    this->~GroupMapDelView_a65500();
    if (flags & 1)
        OperatorDeleteNothrow_a65500(this);
    return this;
}

// ===========================================================================
// Instance::~Instance
// ===========================================================================
// @ 0x00a65230
// ===========================================================================
// Instance::~Instance -- free the canvas, destroy every group in the
// Instance/Group table, run the owner ClearLists pass, dispose the GroupMap and
// the two embedded tables, and finally re-stamp the object's vtable.
// ===========================================================================
// @ 0x00a65230
void Instance::Destroy()
{
    pd_free(mpCanvas);                          // 0xa493d0

    /* walk every group in mGroups and destroy/free it */
    HashNode16** bucket = mGroups.mpBucketArray;
    HashNode16* node = *bucket;
    if (node == 0) {
        while (*++bucket == 0) { }
        node = *bucket;
    }
    if (mGroups.mpBucketArray[mGroups.mnBucketCount] != node) {
        do {
            HashNode16* cur = node;
            node = cur->mpNext;
            if (node == 0) {
                while (*++bucket == 0) { }
                node = *bucket;
            }
            AnyGroup* group = (AnyGroup*)cur->mV2;
            void* samples = group->mpSamples;            // group->+0x00
            if (samples != 0) {
                /* the allocator sub-object begins at group+0x0c: its vtable is
                   the pointer stored there and `this` is the address itself */
                typedef void (__thiscall* Fn)(void*, void*);
                ((Fn)(*(void***)&group->mpVtbl0c)[3])((void*)&group->mpVtbl0c, samples);
            }
            group->mpVtbl0c = (void*)g_1403934;
            typedef void (__thiscall* FreeFn)(void*, void*);
            ((FreeFn)(*(void***)this)[3])(this, group);
        } while (mGroups.mpBucketArray[mGroups.mnBucketCount] != node);
    }

    void* owner = Eapd_GetOwnerA();             // 0xa67ce0
    ((EapdOwner*)owner)->ClearLists(this);      // 0xa646a0

    mGroupMap.mGroups.Dispose();                // 0xa65000
    mGroupMap.mpVtbl = (void*)g_1455648;        // 0x01455648
    mGroups.Finalize();                         // 0xa64b70
    mpVtbl = (void*)g_1403934;                  // 0x01403934
}

// ===========================================================================
// Instance::CreateGroup -- find the symbol, and when it is absent allocate a
// 0x20-byte group, initialise it (failing soft if Init returns false) and
// insert {symbol, a3, group} into the Instance/Group table.
// ===========================================================================
// @ 0x00a65360
void* Instance::CreateGroup(uint32_t* sym, void* a3, void* a4, uint32_t a5)
{
    void* group = 0;
    HashNode16* foundNode = 0;
    /* The original keys the table on the caller's 4-byte symbol token (it hands
       `find` the address of its own argument slot), not on the pointee. */
    uint32_t key = (uint32_t)sym;
    mGroups.FindNode(&foundNode, &key);
    /* sentinel == foundNode means the symbol is absent -> build a group */
    if (mGroups.mpBucketArray[mGroups.mnBucketCount] != foundNode)
        return group;

    typedef void* (__thiscall* AllocFn)(void*, uint32_t);
    void* block = ((AllocFn)(*(void***)this)[2])(this, 0x20);
    if (block)
        group = ((GroupHelp*)block)->Init(this);
    else
        group = 0;
    if (group == 0)
        return group;

    if (!((AnyGroup*)group)->Init(sym, a3, a4, a5)) {
        ((AnyGroup*)group)->Destroy();
        typedef void (__thiscall* FreeFn)(void*, void*);
        ((FreeFn)(*(void***)this)[3])(this, group);
        return 0;
    }
    HashNode16 pair;
    pair.mKey = key;
    pair.mV1  = (uint32_t)a3;
    pair.mV2  = (uint32_t)group;
    pair.mpNext = 0;
    InsertResult res;
    mGroups.Insert(&res, &pair, 0);
    return group;
}

// ===========================================================================
// Instance::FreeGroup -- erase the key, destroy and free the group record
// ===========================================================================
// @ 0x00a65470
void Instance::FreeGroup(uint32_t key, uint32_t unused, void* group)
{
    (void)unused;
    mGroups.Erase(&key);
    ((AnyGroup*)group)->Destroy();
    typedef void (__thiscall* Fn)(void*, void*);
    ((Fn)(*(void***)this)[3])(this, group);
}

// ===========================================================================
// GroupMap::GroupMapCtor
// ===========================================================================
// Construction view of GroupMap (0x00a654a0, GroupMap::GroupMapCtor).
struct GroupMapCtorView_a654a0 : GroupMapBase_a651e0 {
    Hashtable mGroups;   // +0x10
    GroupMapCtorView_a654a0(void* nameSlot);
};

// @ 0x00a654a0
GroupMapCtorView_a654a0::GroupMapCtorView_a654a0(void* nameSlot)
{
    mpVtbl = (void*)g_1455668;
    ((HashtableCalls_a65180*)&mGroups)->InitNamed(nameSlot, "EAPd/InputManager");
}

// ===========================================================================
// Instance ctor -- install the vtables, name the Instance/Group table, build
// the GroupMap wrapper, then stash the two caller pointers.
// ===========================================================================
// @ 0x00a65560
Instance* Instance::InstanceCtor(void* sys, void* a3, void* a4)
{
    mpVtbl       = (void*)&g_1454fac;
    mField04     = *(uint32_t*)((char*)sys + 4);
    mpClassName  = "EAPd/Instance";     // 0x014556ac
    mGroups.InitNamed(sys, "EAPd/GroupMap");   // 0x0145569c
    mGroupMap.GroupMapCtor(sys);
    mField6c = (uint32_t)a4;
    mpCanvas = a3;
    mField74 = 1;
    return this;
}

// ===========================================================================
// InstanceManager::CanvasOrId -- create a canvas, hand back its id
// ===========================================================================
// @ 0x00a657a0
bool InstanceManager::CanvasOrId(void* a2, void* a3, uint32_t* out)
{
    mCurId2 = 0xffffffff;
    CreateCanvas(a2, a3, 0, 0);
    *out = mCurId2;
    mCurId2 = 0xffffffff;
    return *out != 0xffffffff;
}

// ===========================================================================
// InstanceManager::RemoveInstance -- find the binding, unlink the node from the
// map's intrusive iterator list, erase it (fixing the pool free list), then
// destroy and free the Instance.  Returns true when something was removed.
// ===========================================================================
// @ 0x00a65cd0
bool InstanceManager::RemoveInstance(uint32_t id)
{
    /* InstanceMap iterator node: +4 = prev link, +8 = next link, +0x10 = value */
    void* iter[2];                       // {node, bucket}
    mBindings.Find(iter, &id);
    void* raw = iter[0];
    if (raw == (void*)mBindings.mpBucketArray[mBindings.mnBucketCount])
        return false;

    uint32_t* node = (uint32_t*)raw;
    uint32_t* next = *(uint32_t**)((char*)node + 8);
    uint32_t* prev = *(uint32_t**)((char*)node + 4);
    void* instance = *(void**)((char*)node + 0x10);
    *next = (uint32_t)prev;
    *(uint32_t**)((char*)prev + 4) = next;
    *(uint32_t*)((char*)node + 4) = 0;
    *(uint32_t*)((char*)node + 8) = 0;

    mBindings.EraseFn(iter, raw, (void**)iter[1]);

    ((Instance*)instance)->Destroy();
    typedef void (__thiscall* FreeFn)(void*, void*);
    ((FreeFn)(*(void***)((char*)this + 4))[3])((char*)this + 4, instance);
    return true;
}

// ===========================================================================
// InstanceManager::FindInstance
// ===========================================================================
// @ 0x00a65d60
void* InstanceManager::FindInstance(uint32_t id)
{
    HashtableBig* map = &mBindings;
    void* none = 0;
    void* local[2];
    map->Find(local, &id);
    void* result = none;
    if (local[0] != map->mpBucketArray[map->mnBucketCount])
        result = *(void**)((char*)local[0] + 0x10);
    return result;
}

// ===========================================================================
// InstanceManager::CreateCanvas  -- build a canvas for a {name,id} pair via the
// canvas interface (vtable slot 3), register the filename symbols, then tell
// the interface we are done (slot 4).  Returns the canvas id (0 on failure).
// ===========================================================================
// @ 0x00a655f0
uint32_t InstanceManager::CreateCanvas(void* a2, void* a3, uint32_t a4, uint32_t a5)
{
    uint32_t uVar2 = 0;
    /* Frame order matches the original: local_10/local_c are the two outputs of
       the interface call, symHash/symName the pair GetGroupSymbol fills. */
    uint32_t local_10;
    uint32_t local_c;
    uint32_t symHash;
    uint32_t symName;
    GetGroupSymbol(&symHash);                           // 0xa635d0
    Canvas* cv = *(Canvas**)((char*)this + 0x38);
    typedef uint8_t (__thiscall* Slot3Fn)(void*, uint32_t, uint32_t, void*, void*,
                                          uint32_t, uint32_t, uint32_t*, uint32_t*);
    uint8_t ok = ((Slot3Fn)(*(void***)cv)[3])(cv, symHash, symName, a2, a3,
                                              g_1675864, g_1675868,
                                              &local_10, &local_c);
    if (ok) {
        SetNewFilenameSymbol1(a2, a3);                   // 0xa4a410
        SetNewFilenameSymbol2((void*)a4, (void*)a5);     // 0xa4a3f0
        uVar2 = MakeCanvasId((void*)local_10, (void*)local_c); // 0xa47c00
        SetNewFilenameSymbol1((void*)gEmptySymbol, (void*)g_16758a0);
        SetNewFilenameSymbol2((void*)0, (void*)0);
        typedef void (__thiscall* Slot4Fn)(void*, void*);
        ((Slot4Fn)(*(void***)cv)[4])(cv, (void*)local_10);
    }
    return uVar2;
}

