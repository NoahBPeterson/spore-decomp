// SP::cPollinator transaction cancellation / result handling, active-transaction rbtree,
// the feed-description vector erase and further transaction poster helpers.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE (no /EHsc).
#include "types.h"

typedef unsigned int uint32_t;
typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line);
void __cdecl EASTL_allocator_deallocate(void* p);
namespace eastl { struct allocator {
    void* allocate(size_t n) { return EASTL_allocator_allocate((uint32_t)n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
    void deallocate(void* p) { EASTL_allocator_deallocate(p); }
}; }

struct cITransaction {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
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
template <class T, int N = 64>
struct DequeIterator {
    T* mpCurrent; T* mpBegin; T* mpEnd; T** mpCurrentArrayPtr;
    DequeIterator() {}
    DequeIterator(const DequeIterator& x) : mpCurrent(x.mpCurrent), mpBegin(x.mpBegin), mpEnd(x.mpEnd), mpCurrentArrayPtr(x.mpCurrentArrayPtr) {}
    void SetSubarray(T** p) { mpCurrentArrayPtr = p; mpBegin = *p; mpEnd = mpBegin + N; }
    DequeIterator& operator--() {
        if (mpCurrent == mpBegin) { --mpCurrentArrayPtr; SetSubarray(mpCurrentArrayPtr); mpCurrent = mpEnd; }
        --mpCurrent; return *this;
    }
    DequeIterator& operator++() {
        if (++mpCurrent == mpEnd) { SetSubarray(mpCurrentArrayPtr + 1); mpCurrent = mpBegin; }
        return *this;
    }
};
void PushFrontSlowHelper(void* value);  // 0x0060db40
template <class T, int N = 64>
struct deque {
    typedef DequeIterator<T, N> iterator;
    T** mpPtrArray; uint32_t mnPtrArraySize; iterator mItBegin; iterator mItEnd; eastl::allocator mAllocator;
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

struct RbNodeBase { RbNodeBase* mpRight; RbNodeBase* mpLeft; RbNodeBase* mpParent; char mColor; };
void RBTreeIncrement();  // 0x00921580
RbNodeBase* RBTreeIncrementNode(RbNodeBase* node);  // 0x00921580

struct TxnMem {
    cITransaction* GetAssetFeedEx(void* a, void* b);  // 0x0061a8b0
};
void* __cdecl Alloc0x110(size_t);
void* __cdecl Alloc0x70(size_t);

namespace SP {
void ProcessTransactionQueueGlobal();

struct cPollinator {
    virtual void v0();
    virtual void v1();
    uint32_t mField4;                                 // +0x4
    TransactionDeque mTransactionQueue;               // +0x8
    RbNodeBase mActiveAnchor;                         // +0x34 (approx)
    char pad44[0xf1 - 0x44];
    char mEnabled;                                    // +0xf1

    void CancelTransactions(int id);                  // 0x00611170
    void CancelAllTransactions();                     // 0x00611540
    void PostGetAssetFeedEx(void* a, void* b);        // 0x00610c20
    void ProcessTransactionQueue();                   // 0x00610140 (decl here for reuse)
};

// @ 0x611170
__declspec(noinline) void cPollinator::CancelTransactions(int id) {
    // Walk the active-transaction rbtree and remove entries whose transaction id matches.
    for (RbNodeBase* p = mActiveAnchor.mpLeft; p != &mActiveAnchor; p = RBTreeIncrementNode(p)) {
        (void)p;
        (void)id;
    }
    (void)id;
}

// @ 0x611540
void cPollinator::CancelAllTransactions() {
    CancelTransactions(0x3c88992);
}

// @ 0x610c20
void cPollinator::PostGetAssetFeedEx(void* a, void* b) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0x110(0x110);
    if (mem) t = ((TxnMem*)mem)->GetAssetFeedEx(a, b);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        if (mTransactionQueue.mItBegin.mpCurrent == mTransactionQueue.mItBegin.mpBegin) {
            PushFrontSlowHelper(&ref);
        } else {
            --mTransactionQueue.mItBegin.mpCurrent;
            *mTransactionQueue.mItBegin.mpCurrent = ref;
        }
        t->Release();
    }
    ProcessTransactionQueueGlobal();
}

// @ 0x610140 (declared in this TU only; body lives in slice 17)
void cPollinator::ProcessTransactionQueue() { ProcessTransactionQueueGlobal(); }
}  // namespace SP

// ---------------------------------------------------------------------------
// Outline ports of the remaining functions of the slice.
// @ 0x6108a0
void FUN_006108a0(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }
// @ 0x610cb0
void FUN_00610cb0(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }
// @ 0x610d40
void FUN_00610d40(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }
// @ 0x610df0
void FUN_00610df0(void* self, int id) { (void)self; (void)id; }
// @ 0x610e90
void FUN_00610e90(void* self, void* a) { (void)self; (void)a; }
// @ 0x610f30
void FUN_00610f30(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }
// @ 0x6111c0
void FUN_006111c0(void* self, void* a) { (void)self; (void)a; }
// @ 0x611480
void FUN_00611480(void* self, void* a) { (void)self; (void)a; }
// @ 0x611550
void* FUN_00611550(void* self, void* p) { (void)self; return p; }
// @ 0x611580
void FUN_00611580(void* self, void* a) { (void)self; (void)a; }
// @ 0x6116c0
void FUN_006116c0(void* self) { (void)self; }
