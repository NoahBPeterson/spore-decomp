// Slice s00db7fc0: constructor tail of an object holding an inline hash table --
// builds a fixed pool over the inline arena at +0x5c (0xa0 bytes, 0x14 nodes),
// sets the default rehash policy (0x10000.0f? no: the 0x13f0620 / 0x1470f1c
// constants), initialises the table, then inserts the initial entry.
// Status: not byte-exact (216 vs 255 bytes).  The original reuses ONE 0x18-byte
// stack scratch area for the temp allocator (pool head + arena begin/end + count +
// pool control), for the rehash policy (same three words) and for the two
// "p3 pointer" temporaries passed to the bucket-init call, so its arguments are a
// chain of `lea edx,[esp+X]; push edx` over one buffer.  Modelled as in
// 0x00db4f60 (catalogs same shape) but cl 15 here keeps separate slots, and the
// initial-insert tail (0x00db5d70 with the first/end bucket pair) collapses to
// four pushes.  Levers tried: TempAlloc + policy overlay, plain float members,
// raw pointer/void* arg forms.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

extern float g_13f0620;                         // 0x013f0620
extern float g_1470f1c;                         // 0x01470f1c

struct FixedPoolBase_00db7fc0 {
    void* mpHead;                               // +0x00
    void  init(void* pMemory, unsigned int memorySize, unsigned int nodeSize,
               unsigned int alignment, unsigned int alignmentOffset);   // 0x00921260
};

struct TempAlloc_00db7fc0 {                     // temporary allocator on the stack
    FixedPoolBase_00db7fc0 mPool;               // +0x00
    void*   mUnk04;                             // +0x04
    void*   mBegin;                             // +0x08
    void*   mEnd;                               // +0x0c
    unsigned mCount;                            // +0x10
    void*   mExtra;                             // +0x14
};

struct RehashPolicy_00db7fc0 {
    float    mLoadFactor;                       // +0x00
    float    mGrowthFactor;                     // +0x04
    unsigned mnNextResize;                      // +0x08
    unsigned get_next_bucket_count(unsigned n); // 0x009213c0 (inlined)
};

struct Table_00db7fc0 {
    void*  mpUnk00;                             // +0x00
    void*  mpBucketArray;                       // +0x04
    unsigned mnBucketCount;                     // +0x08
    unsigned mnElementCount;                    // +0x0c
    RehashPolicy_00db7fc0 mRehashPolicy;        // +0x10
    int    mF14;                                // +0x14
    int    mF18;                                // +0x18
    char   mPoolPad[0x1c];                      // +0x1c .. +0x33
    void*  mPoolControl;                        // +0x34
    char   mPad38[0x24];                        // +0x38 .. +0x5b
    char   mTempArena[0xa0];                    // +0x5c .. +0xfb

    void   Parse(unsigned int n);               // 0x00921340
    void*  SetBuckets(unsigned int n, void* p2, void* r3, void* r4, void* v5,
                      void* r6, void* temp);    // 0x00db3cf0
    void   Sub_00db5d70(void* a, void* b, void* c, void* d);   // 0x00db5d70
    void   Sub_00daee00(unsigned int n);                       // 0x00daee00

    Table_00db7fc0* Init(void* p2, void* p3);
};

extern "C" unsigned FUN_00921340(unsigned n);    // 0x00921340

// @ 0x00db7fc0
Table_00db7fc0* Table_00db7fc0::Init(void* p2, void* p3)
{
    TempAlloc_00db7fc0 temp;
    temp.mPool.mpHead = 0;
    temp.mPool.init(mTempArena, 0xa0, 0x14, 4, 0);
    temp.mBegin = mTempArena;
    temp.mEnd = (char*)temp.mBegin + 0xa0;
    temp.mCount = 0x14;
    temp.mExtra = &mPoolControl;
    unsigned buckets = FUN_00921340(9);
    SetBuckets(buckets, p2, (void*)&p3, (void*)&p3, p3, (void*)&p3, &temp);
    RehashPolicy_00db7fc0* policy = (RehashPolicy_00db7fc0*)&temp;
    policy->mLoadFactor = 10000.0f;
    policy->mGrowthFactor = 2.0f;
    policy->mnNextResize = 0;
    mRehashPolicy = *policy;
    unsigned n = policy->get_next_bucket_count(mnElementCount);
    if (n > mnBucketCount)
        Sub_00daee00(n);
    Sub_00db5d70(p2, (void*)p3, p2, (void*)p3);
    return this;
}