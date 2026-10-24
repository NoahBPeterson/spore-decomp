// Slice s00a64d70 (batch gold7).  Region 0x00a64d70-0x00a65e4b.
// EA::Audio::Eapd (EA's embedded Pure Data): the Instance / InstanceManager
// family, the small intrusive hashtable (bucket array + intrusive nodes +
// embedded node pool) they are built on, the GroupMap wrapper and the tiny
// vtable-dispatch / copy helpers around them.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
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
    d[0]  = 0x1454fac;      // own vtable
    d[1]  = s[1];
    d[2]  = s[2];
    d[3]  = 0x1454fac;      // nested holder's vtable
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
    return node;
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
    return newBuckets;
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
    return newBuckets;
}

// ===========================================================================
// HashtableBig::InitPool10 -- init the node pool, seed the table, set the load
// factor and rehash if the initial count is still too small (PatchMap shape)
// ===========================================================================
// @ 0x00a65db0
bool HashtableBig::InitPool10(uint32_t a, uint32_t b, uint32_t c)
{
    if (mAlloc.InitPool(a, b, c))
    {
        Rehash16(mAlloc.mnBucketCount - 1);
        mfMaxLoadFactor = 10000.0f;
        mnGrowthFactor  = 2;
        mnNextResize    = 0;
        uint32_t want = FUN_009213c0(mnElementCount);
        if (mnBucketCount < want)
            Rehash16(want);
        return true;
    }
    return false;
}

// ===========================================================================
// HashtableBig::InitPool20 -- same, InstanceMap shape
// ===========================================================================
// @ 0x00a65e40
bool HashtableBig::InitPool20(uint32_t a, uint32_t b, uint32_t c)
{
    if (mAlloc.InitBuckets(a, b, c))
    {
        Rehash20(mAlloc.mnBucketCount - 1);
        mfMaxLoadFactor = 10000.0f;
        mnGrowthFactor  = 2;
        mnNextResize    = 0;
        uint32_t want = FUN_009213c0(mnElementCount);
        if (mnBucketCount < want)
            Rehash20(want);
        return true;
    }
    return false;
}

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
    return MakeFloatHandler((char*)local[0] + 4, f);
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
        uint32_t* entry = (uint32_t*)MakeEntryIter(group);
        HashNode16 pair;
        pair.mKey  = key;
        pair.mV1   = *(uint32_t*)((char*)group + 0x30);
        pair.mV2   = entry[0];
        pair.mpNext = (HashNode16*)entry[1];
        InsertResult res;
        map->Insert(&res, &pair, 0);
        ResetAndClear(&res);
        ResetAndClear(&local);
        if (mpListener)
        {
            typedef void (__thiscall* Fn)(void*, void*, uint32_t, void*);
            ((Fn)(*(void***)mpListener)[1])(mpListener,
                *(void**)((char*)group + 0x34), key, *(void**)((char*)group + 0x30));
        }
        return 1;
    }
    return PushNode(group);
}

// ===========================================================================
// GroupMap::~GroupMap (scalar deleting)
// ===========================================================================
// @ 0x00a65500
GroupMap* GroupMap::ScalarDtor(uint32_t flags)
{
    mGroups.Dispose();
    mpVtbl = (void*)0x1455648;
    if (flags & 1)
        OperatorDelete(this);
    return this;
}

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
// @ 0x00a64f80
Hashtable* Hashtable::Construct(const void* nameSlot)
{
    const uint32_t* slot = (const uint32_t*)nameSlot;
    mnElementCount   = 0;
    mfMaxLoadFactor  = 1.0f;
    mnGrowthFactor   = 2;
    mnNextResize     = 0;
    mPool.mInitAllocator.mpVtbl = (void*)0x1454fac;
    mPool.mInitAllocator.mA     = slot[1];
    mPool.mInitAllocator.mpName = (const char*)slot[2];
    mnBucketCount    = 1;
    mpBucketArray    = (HashNode16**)0x154df28;  // static empty-bucket sentinel
    return this;
}

// ===========================================================================
// Hashtable::InitNamed -- build a name slot and construct the table
// ===========================================================================
// @ 0x00a65180
Hashtable* Hashtable::InitNamed(void* nameSlot, const char* name)
{
    const uint32_t* src = (const uint32_t*)nameSlot;
    NamedAllocator slot;
    slot.mpVtbl = (void*)0x1454fac;
    slot.mA     = src[1];
    slot.mpName = name;
    Construct(&slot);
    return this;
}

// ===========================================================================
// Hashtable::Dispose -- release the bucket array and reset the allocator face
// ===========================================================================
// @ 0x00a65000
void Hashtable::Dispose()
{
    DisposeArray2((void**)mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        mPool.Free(mpBucketArray);
    mPool.mInitAllocator.mpVtbl = (void*)0x1403934;
}

// ===========================================================================
// Hashtable::Dtor -- tear the small table down
// ===========================================================================
// @ 0x00a651e0
void Hashtable::BaseDtor()
{
    Dispose();
    *(void**)this = (void*)0x1455648;
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
    HashNode16* fresh = (HashNode16*)mPool.AllocSize(0x10);
    if (fresh)
    {
        fresh->mKey = pair->mKey;
        fresh->mV1  = pair->mV1;
        fresh->mV2  = pair->mV2;
    }
    fresh->mpNext = 0;

    if (local[0])
    {
        bucket = &mpBucketArray[key % local[1]];
        ResizeBuckets(local[1]);
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
            mPool.Free(node);
            --mnElementCount;
        }
    }
    return before - mnElementCount;
}

// ===========================================================================
// GroupMap::DisposeInner -- tear down the GroupMap's inner table and install
// the Instance vtable
// ===========================================================================
// @ 0x00a651e0
void GroupMap::DisposeInner()
{
    mGroups.Dispose();
    mpVtbl = (void*)0x1455648;
}

// ===========================================================================
// Instance::~Instance
// ===========================================================================
// @ 0x00a65230
void Instance::Destroy()
{
    return;
}

// ===========================================================================
// Instance::CreateGroup
// ===========================================================================
// @ 0x00a65360
void* Instance::CreateGroup(uint32_t* sym, void* a3, void* a4, uint32_t a5)
{
    return 0;
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
// @ 0x00a654a0
GroupMap* GroupMap::GroupMapCtor(void* nameSlot)
{
    mpSelf   = (GroupMap*)((char*)this + 0x10);
    mField08 = 0;
    mField0c = 0;
    mpVtbl   = (void*)0x1455668;
    mGroups.InitNamed(nameSlot, "EAPd/InputManager");
    return this;
}

// ===========================================================================
// Instance ctor
// ===========================================================================
// @ 0x00a65560
Instance* Instance::InstanceCtor(void* sys, void* a3, void* a4)
{
    return this;
}

// ===========================================================================
// InstanceManager::CanvasOrId -- create a canvas, hand back its id
// ===========================================================================
// @ 0x00a657a0
bool InstanceManager::CanvasOrId(void* a2, void* a3, uint32_t* out)
{
    mCurId2 = 0xffffffff;
    CreateCanvas(a3, a2, 0, 0);
    *out = mCurId2;
    mCurId2 = 0xffffffff;
    return *out != 0xffffffff;
}

// ===========================================================================
// InstanceManager::RemoveInstance
// ===========================================================================
// @ 0x00a65cd0
bool InstanceManager::RemoveInstance(uint32_t id)
{
    return false;
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
// InstanceManager::CreateCanvas  --  booked as nonmatching; body not recovered
// ===========================================================================
// @ 0x00a655f0
uint32_t InstanceManager::CreateCanvas(void* a2, void* a3, uint32_t a4, uint32_t a5)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
    return gCreateCanvasResult;
}

