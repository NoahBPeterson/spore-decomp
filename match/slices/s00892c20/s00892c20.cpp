// Slice s00892c20 -- hash-table setter: lock, look the key up, store the value
// into the found node, unlock.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct CRITICAL_SECTION_s00892c20 {
    void* mDebugInfo;
    long  mLockCount;
    void* mOwningThread;
    void* mRecursionCount;
    void* mLockSemaphore;
    unsigned mSpinCount;
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION_s00892c20* cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION_s00892c20* cs);

struct HtValueNode {
    unsigned short mKey;    // +0
    unsigned short mPad2;
    unsigned mValue;        // +4
    HtValueNode* mpNext;    // +8
};
struct HtValueIter {
    HtValueNode* mpNode;    // +0
    HtValueNode** mpBucket; // +4
};

struct HtU32 {                              // hashtable keyed by a 32-bit id
    void* mpLock;                           // +0
    HtValueNode** mpBuckets;                // +4
    unsigned mnBuckets;                     // +8
    HtValueIter* Find(HtValueIter* out, const unsigned* key);   // 0x00892970
};

struct cValueHolder_s00892c20 {
    char pad00[0x28];
    CRITICAL_SECTION_s00892c20 mCS;   // +0x28
    char pad40[0x150 - 0x40];
    HtU32 mById;                      // +0x150

    void SetValue(unsigned key, unsigned value);
};

// @ 0x00892c20
void cValueHolder_s00892c20::SetValue(unsigned key, unsigned value)
{
    EnterCriticalSection(&mCS);

    HtU32* table = &mById;
    HtValueIter it;
    table->Find(&it, &key);
    if (it.mpNode != table->mpBuckets[table->mnBuckets])
        it.mpNode->mValue = value;

    LeaveCriticalSection(&mCS);
}
