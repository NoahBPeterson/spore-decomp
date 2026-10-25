// Slice s00cb1110: trace-cache hash map (eastl hashtable) node insert + get-or-create for the
// global table at 0x0157d30c.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
//
// The map key is a 32-bit id (an object address); the mapped value is a 0x820-byte trace cache made
// of 8 cached hit records (0x100 bytes each) followed by 8 cached object pointers.  The hashtable is
// the eastl layout: hash-functor base, bucket array, bucket count, element count, rehash policy.
#include "types.h"

// EA allocator entry points (0x00f473a0 / 0x00f47380)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t, void* p) { return p; }

#define EASTL_ALLOCATOR_FILE \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

struct TraceCache
{
    char mBytes[0x820];          // 8 * 0x100 hit records followed by 8 cached object pointers
};

struct Value                       // the hashtable value (0x824 bytes)
{
    unsigned   mKey;               // +0x000
    TraceCache mTrace;             // +0x004 .. +0x823

    Value(const Value& src);       // 0x00cb02a0
};

struct Node
{
    Value mValue;                  // +0x000 .. +0x823
    Node* mpNext;                  // +0x824
};

struct Iter                        // eastl hash iterator (8 bytes)
{
    Node*  mpNode;                 // +0x00
    Node** mpBucket;               // +0x04
};

struct InsertResult                // eastl insert() result (12 bytes)
{
    Node*  mpNode;                 // +0x00
    Node** mpBucket;               // +0x04
    bool   mInserted;              // +0x08
};

struct RehashResult                // prime_rehash_policy::RehashResult (8 bytes)
{
    bool     first;                // +0x00
    unsigned second;               // +0x04
};

struct RehashPolicy
{
    float    mfMaxLoadFactor;      // +0x00
    float    mfGrowthFactor;       // +0x04
    unsigned mnNextResize;         // +0x08

    // 0x00921440
    RehashResult GetRehashRequired(unsigned nBucketCount, unsigned nElementCount, unsigned nElementAdd);
};

struct Ht                          // global instance at 0x0157d30c
{
    void*        mField00;         // +0x00 (hash functor)
    Node**       mpBuckets;        // +0x04
    unsigned     mBucketCount;     // +0x08
    unsigned     mSize;            // +0x0c
    RehashPolicy mRehashPolicy;    // +0x10

    void Find(Iter* out, const unsigned* key);                            // 0x00cb00d0
    TraceCache* FindOrInsert(const unsigned* key);                        // 0x00c2b080
    void DoRehash(unsigned newBucketCount);                               // 0x00c29710

    Node* DoFindNode(Node* pNode, unsigned key)
    {
        for (; pNode; pNode = pNode->mpNext) {
            if (key == pNode->mValue.mKey)
                return pNode;
        }
        return 0;
    }

    Node* DoAllocateNode(const Value& value)
    {
        Node* const pNode = (Node*)operator new[](sizeof(Node), "Simulator", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
        if (pNode)
            ::new (&pNode->mValue) Value(value);
        pNode->mpNext = 0;
        return pNode;
    }

    InsertResult DoInsertValue(const Value& value, bool trueType);        // 0x00cb1110
};

// 0x00cadb50: zero the eight hit records, then release the eight cached objects.
void __cdecl FUN_00cadb50(TraceCache* cache);

// =======================================================================================
// 00cb1110 -- Ht::DoInsertValue (eastl hashtable insert-with-tag)
// =======================================================================================
// @ 0x00cb1110
InsertResult Ht::DoInsertValue(const Value& value, bool trueType)
{
    const unsigned c = value.mKey;
    unsigned n = c % mBucketCount;
    Node* const pNode = DoFindNode(mpBuckets[n], value.mKey);
    InsertResult result;
    if (pNode == 0) {
        const RehashResult bRehash = mRehashPolicy.GetRehashRequired(mBucketCount, mSize, 1);
        Node* const pNodeNew = DoAllocateNode(value);
        if (bRehash.first) {
            n = c % bRehash.second;
            DoRehash(bRehash.second);
        }
        pNodeNew->mpNext = mpBuckets[n];
        mpBuckets[n] = pNodeNew;
        ++mSize;
        result.mpNode = pNodeNew;
        result.mInserted = true;
        result.mpBucket = mpBuckets + n;
        return result;
    }
    result.mpNode = pNode;
    result.mInserted = false;
    result.mpBucket = mpBuckets + n;
    return result;
}

// =======================================================================================
// 00cb1210 -- get-or-create the cached trace record for a key in the global table
//             (near-identical twin of FUN_00c2b110, which uses the table at 0x01572460)
// =======================================================================================
// @ 0x00cb1210
TraceCache* FUN_00cb1210(unsigned key)
{
    Ht* const ht = (Ht*)0x0157d30c;
    Iter it;

    ht->Find(&it, &key);
    Node* const pNode = it.mpNode;
    if (pNode == ht->mpBuckets[ht->mBucketCount]) {
        TraceCache* cache = ht->FindOrInsert(&key);
        FUN_00cadb50(cache);
        return cache;
    }
    return (TraceCache*)((int)pNode + 4);
}
