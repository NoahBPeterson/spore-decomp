// SP::cPollinator transaction poster helpers (CreateMyFeed / UpdateMyFeed / DeleteMyFeed /
// SubscribeToFeed / UnsubscribeToFeed) built on an EASTL deque<AutoRefCount<cITransaction>>,
// plus outline ports of Init / ProcessTransactionQueue / the feed-edit helpers.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE (no /EHsc).
#include "types.h"

typedef unsigned int uint32_t;
typedef unsigned int size_t;

extern "C" long _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd)
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line);
void __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

namespace eastl {
class allocator { public:
    void* allocate(size_t n) { return EASTL_allocator_allocate((uint32_t)n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
    void deallocate(void* p) { EASTL_allocator_deallocate(p); }
};
}  // namespace eastl

// Transaction: primary vtable slot 1 = AddRef, slot 2 = Release.
struct cITransaction {
    virtual void v0();
    virtual void AddRef();   // +0x4
    virtual void Release();  // +0x8
};

template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount& x) {
        T* const pNew = x.mpObject;
        if (pNew != mpObject) {
            T* const pOld = mpObject;
            if (pNew) pNew->AddRef();
            mpObject = pNew;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};

template <class T, int kSubarraySize = 64>
struct DequeIterator {
    T* mpCurrent;
    T* mpBegin;
    T* mpEnd;
    T** mpCurrentArrayPtr;
    DequeIterator() {}
    DequeIterator(const DequeIterator& x) : mpCurrent(x.mpCurrent), mpBegin(x.mpBegin), mpEnd(x.mpEnd), mpCurrentArrayPtr(x.mpCurrentArrayPtr) {}
    void SetSubarray(T** p) { mpCurrentArrayPtr = p; mpBegin = *p; mpEnd = mpBegin + kSubarraySize; }
    DequeIterator& operator--() {
        if (mpCurrent == mpBegin) {
            --mpCurrentArrayPtr;
            SetSubarray(mpCurrentArrayPtr);
            mpCurrent = mpEnd;
        }
        --mpCurrent;
        return *this;
    }
    DequeIterator& operator++() {
        if (++mpCurrent == mpEnd) {
            SetSubarray(mpCurrentArrayPtr + 1);
            mpCurrent = mpBegin;
        }
        return *this;
    }
};

void PushFrontSlowHelper(void* value);  // 0x0060db40

template <class T, int kSubarraySize = 64>
struct deque {
    typedef DequeIterator<T, kSubarraySize> iterator;
    T** mpPtrArray;
    uint32_t mnPtrArraySize;
    iterator mItBegin;
    iterator mItEnd;
    eastl::allocator mAllocator;
    void push_front(const T& value) {
        if (mItBegin.mpCurrent == mItBegin.mpBegin) {
            PushFrontSlowHelper((void*)&value);
        } else {
            --mItBegin.mpCurrent;
            *mItBegin.mpCurrent = value;
        }
    }
};

typedef deque<AutoRefCount<cITransaction>, 64> TransactionDeque;

// Transaction constructors run in place on the freshly allocated block (ecx = block).
struct TxnMem {
    cITransaction* GetAssetFeed(void* a, void* b);  // 0x0061a810
    cITransaction* EditFeed(int a);                 // 0x0061a970
    cITransaction* EatFeed(void* a);                // 0x0061c5e0
    cITransaction* DeleteMyFeed(void* a);           // 0x00619150
    cITransaction* SubscribeFeed(int a, void* b, int c);  // 0x00618da0
    cITransaction* UnsubscribeFeed(void* a);        // 0x006191d0
};

void* __cdecl Alloc0xf0(size_t);
void* __cdecl Alloc0x70(size_t);
void* __cdecl Alloc0x18(size_t);

// cString::Format-style variadic helper (self, format, ...): writes a cString in place.
void __cdecl StringFormat(void* self, const char* fmt, ...);   // 0x00472fe0

// Array container passed to UpdateMyFeed: data pointer at +4, element count at +8.
struct FeedContainer {
    int     mField0;      // +0x0
    void**  mpData;       // +0x4
    int     mnSize;       // +0x8
};

// Feed assembler sub-object (t+0x30 / t+0x50): four-argument thiscall helper.
struct FeedAssembler {
    void FUN_0060f0d0(void* a, void* b, void* c, void* d);   // 0x0060f0d0
};

// Replicates the shipped first-non-null scan then forwards to 0x60f0d0.
static void FeedAppendEntry(void* obj, void* container) {
    FeedContainer* fc = (FeedContainer*)container;
    void** data = fc->mpData;
    void** endPtr = data + fc->mnSize;
    void* endVal = *endPtr;
    void** cur = data;
    void* val = *cur;
    if (val == 0) {
        do { ++cur; } while (*cur == 0);
        val = *cur;
    }
    ((FeedAssembler*)obj)->FUN_0060f0d0(val, cur, endVal, endPtr);
}

namespace SP {
class cPollinator { public:
    virtual void v0();
    virtual void v1();
    uint32_t mField4;                    // +0x4
    TransactionDeque mTransactionQueue;  // +0x8
    char pad34[0xf1 - 0x34];
    char mEnabled;                       // +0xf1

    void ProcessTransactionQueue();                       // 0x00610140
    void CreateMyFeed(void* a, void* b, int c);           // 0x006104f0
    void UpdateMyFeed(void* a, void* b, void* c, void* d); // 0x006105d0
    void DeleteMyFeed(void* a);                           // 0x006106f0
    void SubscribeToFeed(void* a);                        // 0x00610780
    void UnsubscribeToFeed(void* a);                      // 0x00610810
    void PostGetAssetFeed(void* a, void* b);              // 0x006103d0
    void PostEatFeed(void* a);                            // 0x00610460
};

volatile int g_txnQueueOutlineSink;
// The outline body is a stub, but the call must survive optimisation so the harness can
// resolve it to the shipped 0x610140 (a volatile access keeps the call from being elided).
// @ 0x610140
__declspec(noinline) void cPollinator::ProcessTransactionQueue() { (void)g_txnQueueOutlineSink; }

// @ 0x6103d0  (SP::cPollinator::GetAssetFeed candidate)
void cPollinator::PostGetAssetFeed(void* a, void* b) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0xf0(0xf0);
    if (mem) t = ((TxnMem*)mem)->GetAssetFeed(a, b);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_front(ref);
        t->Release();
    }
    ProcessTransactionQueue();
}

// @ 0x610460  (SP::cPollinator::EatFeed candidate)
void cPollinator::PostEatFeed(void* a) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0xf0(0xf0);
    if (mem) t = ((TxnMem*)mem)->EatFeed(a);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_front(ref);
        t->Release();
    }
    ProcessTransactionQueue();
}

// @ 0x6104f0  (SP::cPollinator::CreateMyFeed)
void cPollinator::CreateMyFeed(void* a, void* b, int c) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0x70(0x70);
    if (mem) t = ((TxnMem*)mem)->EditFeed(0);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_front(ref);
        t->Release();
    }
    ProcessTransactionQueue();
}

// @ 0x6105d0  (SP::cPollinator::UpdateMyFeed)
void cPollinator::UpdateMyFeed(void* a, void* b, void* c, void* d) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0x70(0x70);
    if (mem) t = ((TxnMem*)mem)->EditFeed(1);
    StringFormat((char*)t + 0x10, (const char*)0x13f5b98, a);
    StringFormat((char*)t + 0x20, (const char*)0x13ef064, b);
    FeedAppendEntry((char*)t + 0x30, c);
    FeedAppendEntry((char*)t + 0x50, d);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_front(ref);
        t->Release();
    }
    ProcessTransactionQueue();
}

// @ 0x6106f0  (SP::cPollinator::DeleteMyFeed)
void cPollinator::DeleteMyFeed(void* a) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0x18(0x18);
    if (mem) t = ((TxnMem*)mem)->DeleteMyFeed(a);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        if (mTransactionQueue.mItBegin.mpCurrent == mTransactionQueue.mItBegin.mpBegin) {
            PushFrontSlowHelper(&ref);
        } else {
            mTransactionQueue.mItBegin.mpCurrent = mTransactionQueue.mItBegin.mpCurrent - 1;
            *mTransactionQueue.mItBegin.mpCurrent = ref;
        }
        t->Release();
    }
    ProcessTransactionQueue();
}

// @ 0x610780  (SP::cPollinator::SubscribeToFeed)
void cPollinator::SubscribeToFeed(void* a) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0xf0(0xf0);
    if (mem) t = ((TxnMem*)mem)->SubscribeFeed(1, a, 0);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_front(ref);
        t->Release();
    }
    ProcessTransactionQueue();
}

// @ 0x610810  (SP::cPollinator::UnsubscribeToFeed)
void cPollinator::UnsubscribeToFeed(void* a) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0x18(0x18);
    if (mem) t = ((TxnMem*)mem)->UnsubscribeFeed(a);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_front(ref);
        t->Release();
    }
    ProcessTransactionQueue();
}
}  // namespace SP

// Outline ports of the remaining functions of the slice.
// @ 0x60f910
void cPollinatorInit(void* self) { (void)self; }
// @ 0x610070
void FeedHelper00610070(void* self, void* a) { (void)self; (void)a; }
