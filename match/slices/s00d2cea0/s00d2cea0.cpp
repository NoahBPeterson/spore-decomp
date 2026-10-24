// Slice s00d2cea0 -- SP::cCreatureDisplayStrategy lifetime, display tick and the
// eastl fixed_hash_map / fixed_pool members embedded in it.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <new>
#include <xmmintrin.h>

namespace SP {

// ------------------------------------------------------------------ engine helpers
struct cGonzagoTimer {
    uint32_t mData[8];                                       // 0x20 bytes
    cGonzagoTimer();
    ~cGonzagoTimer();
    void Restart();
    void Stop();
    long long GetElapsedTime();
};

struct cRefCounted {
    void*    mpVtable;                                       // +0x00
    int32_t  mRefCount;                                      // +0x04
    int32_t  mPad08;                                         // +0x08
};

struct cSPUILayout {
    void* mpVtable;                                          // +0x00
    void Shutdown(int release);                              // 0x00b63380
    void Release();                                          // vtable slot 8
};

struct cMessageServer {
    void* mpVtable;                                          // +0x00
    void RemoveTarget(void* target, uint32_t msg, int32_t arg);
};

struct cFixedPoolBase {
    void*    mpHead;                                         // +0x00
    uint32_t mPad04[5];                                      // +0x04
    void init(void* memory, uint32_t blockSize, uint32_t blockCount,
              uint32_t alignment, uint32_t flags);           // 0x00921260
};

struct cPHTable {
    uint32_t mPad00;                                         // +0x00
    void*    mpBuckets;                                      // +0x04
    uint32_t mBucketCount;                                   // +0x08
    uint32_t mEntryCount;                                    // +0x0c
    uint32_t mPad10[3];                                      // +0x10 .. +0x1b
    void*    mpFreeList;                                     // +0x1c
    uint32_t mPad20;                                         // +0x20
    void*    mpPoolBegin;                                    // +0x24
    void*    mpPoolEnd;                                      // +0x28
    uint32_t mPad2c;                                         // +0x2c
    void*    mpSentinel;                                     // +0x30
    void FreeBuckets(void** buckets, uint32_t count);        // 0x00a24480
};

struct cSPTimer {
    uint32_t mData[4];
    void Restart();
    void Stop();
    long long GetElapsedTime();
};

struct cGameNounManager {
    void* mpVtable;                                          // +0x00
    void* GetAvatar();
};

struct cCreatureModeStrategy {
    static void Instance();
    static void SignalCreatureEvent(uint32_t event);
};

// ------------------------------------------------------------------ fixed_hash_map
struct cFixedPoolBlock {
    cFixedPoolBase mPool;                                    // +0x00
    uint32_t       mPad18[6];                                // +0x18
};

// eastl::fixed_hash_map<uint32_t, EA::RectT<float>, 8, 8, 1>
struct cRectHashTable {
    uint32_t mPad00[2];                                      // +0x00
    uint32_t mBucketCount;                                   // +0x08
    uint32_t mPad0c;                                         // +0x0c
    float    mDefaultMaxX;                                   // +0x10
    float    mDefaultMaxY;                                   // +0x14
    void*    mpIterator;                                     // +0x18
    cFixedPoolBase mPool;                                    // +0x1c
    uint32_t mPad34[9];                                      // +0x34 .. +0x57
    uint8_t  mPoolStorage[0xc0];                             // +0x58
    uint32_t mPad118;                                        // +0x118
    uint32_t mPad11c;                                        // +0x11c
    uint32_t mPad120;                                        // +0x120
    uint32_t mPad124;                                        // +0x124
    uint32_t mPad128;                                        // +0x128
    uint32_t mPad12c;                                        // +0x12c
    uint32_t mPad130;                                        // +0x130
    uint32_t mPad134;                                        // +0x134
    uint32_t mPad138;                                        // +0x138
    uint32_t mPad13c;                                        // +0x13c
    cFixedPoolBase mMapPool;                                 // +0x140
    uint8_t  mMapStorage[0xc0];                              // +0x158? size 0xc0
    cRectHashTable* Construct(void* a, void* b);
};

// ------------------------------------------------------------------ rounded queue
struct cRoundedQueuePool {
    uint32_t   mPad00[6];                                    // +0x00 .. +0x17
    long long* mpEnd;                                        // +0x18
    uint32_t   mPad1c;                                       // +0x1c
    long long* mpCapacity;                                   // +0x20
    void Allocate(void** slot);                              // 0x00d2ca90
};

struct cRoundedQueue {
    uint32_t         mPad00;                                 // +0x00
    cRoundedQueuePool mPool;                                 // +0x04
    void Append(float value);
};

// ------------------------------------------------------------------ display strategy
struct cCreatureDisplayStrategy {
    void*    mpVtable;                                       // +0x00
    uint32_t mPad04;                                         // +0x04
    uint32_t mCapacity;                                      // +0x08
    void*    mpAllocator;                                    // +0x0c
    float    mMaxValue;                                      // +0x10
    float    mMinValue;                                      // +0x14
    void*    mpList;                                         // +0x18
    uint32_t mPad1c[6];                                      // +0x1c .. +0x33
    uint32_t mAllocatorBase;                                 // +0x34
    uint32_t mPad38;                                         // +0x38
    void*    mpVtableB;                                      // +0x3c
    void*    mMessenger;                                     // +0x40
    uint32_t mPad44[1];                                      // +0x44
    void*    mp48;                                           // +0x48
    void*    mp4c;                                           // +0x4c
    uint32_t mState;                                         // +0x50
    uint8_t  mFlag54;                                        // +0x54
    uint8_t  mFlag55;                                        // +0x55
    uint32_t mPad58[0x10 / 4];                               // +0x58 .. +0x67
    cGonzagoTimer mTimer1;                                   // +0x68
    cGonzagoTimer mTimer2;                                   // +0x88

    uint32_t mPadA8[0x38 / 4];                               // +0xa8 .. +0xdf
    cGonzagoTimer mTimer3;                                   // +0xe0
    cGonzagoTimer mTimer4;                                   // +0x100

    uint32_t mPad120;                                        // +0x120
    cRefCounted* mpRef124;                                   // +0x124
    uint32_t mPad128;                                        // +0x128
    uint32_t mSub12c[0x5c / 4];                              // +0x12c .. +0x187
    void*    mp188;                                          // +0x188
    void*    mp18c;                                          // +0x18c
    cPHTable mTable;                                         // +0x190
    uint32_t mPad1c4[0x14 / 4];                              // +0x1c4 .. +0x1d7
    void*    mpCursor194;                                    // +0x194
    uint32_t mCursorCount198;                                // +0x198
    cGonzagoTimer mTimer158;                                 // +0x158

    cCreatureDisplayStrategy* Construct(void* a, void* b);
    cCreatureDisplayStrategy* Init();
    void Deactivate();
    void Tick();
    void UpdateDrama();
    void Destroy();                                          // 0x00d2d3d0
};

// ------------------------------------------------------------------ externals
cMessageServer* __cdecl MessageServer();                     // 0x00b42b20
cGameNounManager* __cdecl NounManager();                     // 0x00b3d300
void* __cdecl GetCurrentGameMode();                          // 0x00b9e660
void  __cdecl FUN_00d2bef0(uint32_t a, uint32_t b);          // 0x00d2bef0
void  __cdecl FUN_00e28a80();                                // 0x00e28a80
void  __cdecl FUN_00e33a00();                                // 0x00e33a00
void  __cdecl FUN_00d2c9b0();                                // 0x00d2c9b0
void  __cdecl FUN_00d39360(uint32_t id, void** ctx);         // 0x00d39360
void  __cdecl FUN_00c17350(uint32_t a, uint32_t b);          // 0x00c17350
void* __cdecl FUN_00c1d460(uint32_t a, uint32_t b);          // 0x00c1d460
void* __cdecl FUN_0057a6d0();                                // 0x0057a6d0
void  __cdecl FUN_00435e90();                                // 0x00435e90
void  __cdecl FUN_00d2c490(uint32_t value);                  // 0x00d2c490
float __cdecl FUN_00d2e410(void* avatar);                    // 0x00d2e410
float __cdecl FUN_00d2e380(uint32_t mode);                   // 0x00d2e380
void* __cdecl FUN_00921340(uint32_t size);                   // 0x00921340
uint32_t __cdecl FUN_009213c0(void* obj);                    // 0x009213c0
void  __cdecl FUN_00d2bf60(uint32_t value);                  // 0x00d2bf60
void  __cdecl FUN_00d2c3e0(void* node, void* a, void** b, void** c,
                           void* d, void** e, cFixedPoolBase* pool); // 0x00d2c3e0
void  __cdecl FUN_00b5d6b0(void* node, void* a, void** b, void** c,
                           void* d, void** e, cFixedPoolBase* pool); // 0x00b5d6b0
void  __cdecl FUN_00b5d220(uint32_t value);                  // 0x00b5d220
void  __cdecl FUN_00af14b0();                                // 0x00af14b0
void* __cdecl MemAlloc(uint32_t size, const char* tag, int a, int b,
                       const char* file, uint32_t line);      // 0x00f473a0
void  __cdecl MemDeleteArray(void* p);                       // 0x00f47380
void* __cdecl operator_new(uint32_t size, const char* tag, int a, int b,
                           const char* file, uint32_t line);  // 0x00f473a0

struct cLocale {
    static void SetMoneyString(long long amount, wchar_t* out, uint32_t cap,
                               const wchar_t* fmt, float* extra);
};
extern const float gDefaultMax;                              // 0x013f0620
extern const float gDefaultMin;                              // 0x01470f1c
extern uint32_t gUnusedA;                                    // 0x0169dfe4
extern uint32_t gUnusedB;                                    // 0x0169dfe8
extern uint32_t gUnusedC;                                    // 0x0169dfec

// @ 0x00d2cea0
void cCreatureDisplayStrategy::Deactivate()
{
    if (mpVtableB && ((cRefCounted*)mpVtableB)->mpVtable) {
        (*(void (__thiscall**)(cRefCounted*))((void**)((cRefCounted*)mpVtableB)->mpVtable)[0x88 / 4])
            ((cRefCounted*)mpVtableB);
        mpVtableB = 0;
    }
    if (mMessenger) {
        (*(void (__thiscall**)(void*))((void**)*(void**)mMessenger)[0x0c / 4])(mMessenger);
        mMessenger = 0;
    }
    if (mpRef124) {
        FUN_00e28a80();
        cRefCounted* ref = mpRef124;
        mpRef124 = 0;
        if (--ref->mRefCount == 0) {
            ref->mRefCount = 1;
            (*(void (__thiscall**)(cRefCounted*, int))((void**)ref->mpVtable)[0])(ref, 1);
        }
    }
    MessageServer()->RemoveTarget(&mMessenger, 0x14051500, -0x270f);
    FUN_00d2bef0(gUnusedA, gUnusedB);
    gUnusedC = 0;
    if (mpList) {
        FUN_00e33a00();
        void* list = mpList;
        mpList = 0;
        (*(void (__thiscall**)(void*))((void**)*(void**)list)[0x04 / 4])(list);
    }
    if (mpAllocator) {
        ((cSPUILayout*)mpAllocator)->Shutdown(1);
        mpAllocator = 0;
    }
    if (mp188) {
        (*(void (__thiscall**)(void*, int))((void**)*(void**)mp188)[0x0c / 4])(mp188, 1);
        mp188 = 0;
    }
    if (mp18c) {
        (*(void (__thiscall**)(void*, int))((void**)*(void**)mp18c)[0x0c / 4])(mp18c, 1);
        mp18c = 0;
    }
    if (mp48) {
        (*(void (__thiscall**)(void*, int))((void**)*(void**)mp48)[0x0c / 4])(mp48, 1);
        mp48 = 0;
    }
    if (mp4c) {
        (*(void (__thiscall**)(void*))((void**)*(void**)mp4c)[0x04 / 4])(mp4c);
        mp4c = 0;
    }
    mState = 0;
    mFlag54 = 1;

    // Clear the per-noun temporary highlight flag on every live display noun.
    void** it = (void**)mpCursor194;
    while ((uint32_t)it != *(uint32_t*)((uint8_t*)&mpCursor194 + mCursorCount198)) {
        void* noun = (void*)it[1];
        if (noun) {
            void* display = *(void**)((uint8_t*)noun + 0xb54);
            if (display)
                *(float*)((uint8_t*)display + 0x80) = 1.0f;
            *(uint32_t*)((uint8_t*)noun + 0xb58) &= ~0x800u;
        }
        it += 2;
    }
}

// @ 0x00d2d0b0
void cCreatureDisplayStrategy::Tick()
{
    if (mState == 0) {
        if (mAllocatorBase == 0)
            return;
        FUN_00d2c9b0();
        mState = 1;
        return;
    }
    if (mState == 1) {
        long long elapsed = mTimer1.GetElapsedTime();
        if ((uint32_t)(elapsed >> 32) == 0 && (uint32_t)elapsed <= 1000)
            return;
        mTimer1.Stop();
        mState = 0;
    }
}

// @ 0x00d2d300
cCreatureDisplayStrategy* cCreatureDisplayStrategy::Construct(void* a, void* b)
{
    cFixedPoolBase pool;
    pool.mpHead = 0;
    pool.init(&mPad58[0], 0xc0, 0x18, 4, 0);

    void* node = FUN_00921340(8);
    FUN_00d2c3e0(node, a, (void**)&b, (void**)&b, b, (void**)&b, &pool);

    mMaxValue = 10000.0f;
    mMinValue = 2.0f;
    mpList = 0;
    uint32_t count = FUN_009213c0(mpAllocator);
    if (mCapacity < count)
        FUN_00d2bf60(count);
    return this;
}

// @ 0x00d2d3d0
void cCreatureDisplayStrategy::Destroy()
{
    mpVtable = (void*)0x0147a508;
    mPad38 = 0x0147a4ec;
    mpVtableB = (void*)0x0147a4dc;
    mMessenger = (void*)0x0147a4cc;

    mTable.FreeBuckets((void**)mTable.mpBuckets, mTable.mBucketCount);
    mTable.mEntryCount = 0;
    if (mTable.mBucketCount > 1 && mTable.mpBuckets != mTable.mpSentinel) {
        if ((uint8_t*)mTable.mpBuckets < (uint8_t*)mTable.mpPoolBegin
            || (uint8_t*)mTable.mpBuckets >= (uint8_t*)mTable.mpPoolEnd) {
            MemDeleteArray(mTable.mpBuckets);
        } else {
            *(void**)mTable.mpBuckets = mTable.mpFreeList;
            mTable.mpFreeList = mTable.mpBuckets;
        }
    }

    if (mp18c)
        (*(void (__thiscall**)(void*))((void**)*(void**)mp18c)[0x04 / 4])(mp18c);
    if (mp188)
        (*(void (__thiscall**)(void*))((void**)*(void**)mp188)[0x04 / 4])(mp188);

    mTimer158.~cGonzagoTimer();
    mSub12c[0] = 0;
    if (mpRef124) {
        cRefCounted* ref = mpRef124;
        if (--ref->mRefCount == 0) {
            ref->mRefCount = 1;
            (*(void (__thiscall**)(cRefCounted*, int))((void**)ref->mpVtable)[0])(ref, 1);
        }
    }
    if (mPad120)
        (*(void (__thiscall**)(void*))((void**)*(void**)mPad120)[0x04 / 4])((void*)mPad120);

    mTimer4.~cGonzagoTimer();
    mTimer3.~cGonzagoTimer();
    if (mpAllocator)
        ((cSPUILayout*)mpAllocator)->Release();
    mTimer2.~cGonzagoTimer();
    mTimer1.~cGonzagoTimer();
    if (mpList)
        (*(void (__thiscall**)(void*))((void**)*(void**)mpList)[0x04 / 4])(mpList);
    if (mp4c)
        (*(void (__thiscall**)(void*))((void**)*(void**)mp4c)[0x04 / 4])(mp4c);
    if (mp48)
        (*(void (__thiscall**)(void*))((void**)*(void**)mp48)[0x04 / 4])(mp48);
}

// @ 0x00d2d560
void cRoundedQueue::Append(float value)
{
    long long rounded = (int)value;
    if (rounded > 0) {
        cRoundedQueuePool* pool = &mPool;
        long long* slot = pool->mpEnd;
        long long* next = slot + 1;
        if (next != pool->mpCapacity) {
            pool->mpEnd = next;
            if (slot)
                *slot = rounded;
        } else {
            pool->Allocate((void**)&rounded);
        }
    }
}

// @ 0x00d2d5c0
cRectHashTable* cRectHashTable::Construct(void* a, void* b)
{
    cFixedPoolBase pool;
    pool.mpHead = 0;
    pool.init(mPoolStorage, 0xc0, 0xc, 4, 0);

    void* node = FUN_00921340(0x11);
    FUN_00b5d6b0(node, a, &b, &b, b, &b, &pool);

    mDefaultMaxX = gDefaultMax;
    mDefaultMaxY = gDefaultMin;
    mpIterator = 0;
    uint32_t count = FUN_009213c0((void*)mPad0c);
    if (mBucketCount < count)
        FUN_00b5d220(count);
    return this;
}

// @ 0x00d2d690
cCreatureDisplayStrategy* cCreatureDisplayStrategy::Init()
{
    FUN_00af14b0();
    mpVtableB = (void*)0x0147a4dc;
    mMessenger = (void*)0x0147a4cc;
    mPad44[0] = 0;
    mPad38 = 0x0147a4ec;
    mpVtable = (void*)0x0147a508;
    mp48 = 0;
    mp4c = 0;
    mFlag55 = 1;
    mpList = 0;
    *(void**)((uint8_t*)&mpList + 4) = 0;
    cGonzagoTimer* t1 = &mTimer1;
    new (t1) cGonzagoTimer();
    new (&mTimer2) cGonzagoTimer();
    mPadA8[0] = 1;
    mpAllocator = 0;
    new (&mTimer3) cGonzagoTimer();
    new (&mTimer4) cGonzagoTimer();
    mPad120 = 0;
    mpRef124 = 0;
    mPad128 = 0;
    mSub12c[0] = 0;
    FUN_00d2c490(0);
    new (&mTimer158) cGonzagoTimer();
    mPad1c4[0] = 0;
    return this;
}

// @ 0x00d2d7d0
void cCreatureDisplayStrategy::UpdateDrama()
{
    // 1359-byte drama tick: not reconstructed in this pass.
    if (mpList == 0)
        return;
    if (mState == 0)
        mState = 1;
}

} // namespace SP
