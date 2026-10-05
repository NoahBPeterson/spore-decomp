// SP::cPollinator upload-queue / transaction helpers: the 16-byte upload-queue entry vector
// (push_back / DoInsertValue), NextIDReady, HandlePollinateRequest, the asset-metadata update and
// the EASTL deque<AutoRefCount<ITransaction>>::erase + rbtree<...>::erase/DoNukeSubtree instances.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- (no /EHsc).
#include "types.h"

typedef unsigned int uint32_t;

extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)
extern "C" void* __cdecl memmove(void*, const void*, uint32_t);
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
void __cdecl EASTL_allocator_deallocate(void* p);                                                                                  // 0x00f47380

#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

namespace eastl {
struct allocator {
    void* allocate(size_t n) { return EASTL_allocator_allocate((uint32_t)n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
    void deallocate(void* p) { EASTL_allocator_deallocate(p); }
};
}  // namespace eastl

// Intrusive refcounted object: virtual deleting dtor in slot 0, refcount at +4.
struct RefCounted {
    virtual void Delete(unsigned char flags);
    void AddRef() { _InterlockedExchangeAdd((volatile long*)((char*)this + 4), 1); }
    void Release() {
        if (_InterlockedExchangeAdd((volatile long*)((char*)this + 4), -1) == 1) {
            _InterlockedExchange((volatile long*)((char*)this + 4), 1);
            Delete(1);
        }
    }
};

// Little helpers matching the vtable slots used by the queue entry.
struct IObj4 {
    virtual void v0();
    virtual void AddRef4();   // +0x4
    virtual void Release8();  // +0x8
};

// A trivial 16-byte value (3 dwords + 2 flag bytes) for the upload queue.
struct QValue {
    uint32_t mKey0;  // +0x0
    uint32_t mKey1;  // +0x4
    uint32_t mKey2;  // +0x8
    uint8_t mFlag0;  // +0xc
    uint8_t mFlag1;  // +0xd
    uint8_t mPad[2];
    QValue() {}
    QValue(const QValue& x)
        : mKey0(x.mKey0), mKey1(x.mKey1), mKey2(x.mKey2), mFlag0(x.mFlag0), mFlag1(x.mFlag1) {}
};

QValue* QValue_copy(const QValue* first, const QValue* last, QValue* dest) {
    for (; first != last; ++first, ++dest) *dest = *first;
    return dest;
}

// ---------------------------------------------------------------------------
// Upload queue (vector of 16-byte entries).
struct UploadQueue {
    QValue* mpBegin;     // +0x0
    QValue* mpEnd;       // +0x4
    QValue* mpCapacity;  // +0x8
    uint32_t mPad0c;     // +0xc

    void DoInsertValue(QValue* position, const QValue* value);  // 0x0060ec20
    void push_back(const QValue& value);                        // 0x0060f080
};

// @ 0x60f080
void UploadQueue::push_back(const QValue& value) {
    QValue* const p = mpEnd;
    if (p < mpCapacity) {
        mpEnd = p + 1;
        ::new (p) QValue(value);
    } else {
        DoInsertValue(p, &value);
    }
}

void FUN_00edba80(void* dest, const void* src, const void* srcEnd);  // 0x00edba80

// @ 0x60ec20
void UploadQueue::DoInsertValue(QValue* position, const QValue* value) {
    if (mpEnd != mpCapacity) {
        if (value >= position && value < mpEnd) value = (const QValue*)((const char*)value + 16);
        if (mpEnd) ::new (mpEnd) QValue(*(QValue*)((char*)mpEnd - 16));
        FUN_00edba80(position, (char*)mpEnd - 16, mpEnd);
        *position = *value;
        ++mpEnd;
        return;
    }
    int n = (int)(mpEnd - mpBegin);
    if (n <= 0)
        n = 1;
    else
        n = n * 2;
    QValue* pNew = 0;
    if (n != 0) pNew = (QValue*)EASTL_allocator_allocate(n * 16, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    QValue* pMid = QValue_copy(mpBegin, position, pNew);
    if (pMid) *pMid = *value;
    QValue* pEndNew = QValue_copy(position, mpEnd, pMid + 1);
    if (mpBegin) EASTL_allocator_deallocate(mpBegin);
    mpEnd = pEndNew;
    mpCapacity = pNew + n;
    mpBegin = pNew;
}

// @ 0x60ea40
QValue* MakeNode(const QValue* src) {
    char* const pNode = (char*)EASTL_allocator_allocate(0x20, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    QValue* const pValue = (QValue*)(pNode + 0x10);
    if (pValue) *pValue = *src;
    return (QValue*)pNode;
}

// @ 0x60eab0 : static empty-string / empty-container initializer.
struct EmptyQueue {
    char* mpBegin;  // +0x0
    char* mpEnd;    // +0x4
    char* mpCap;    // +0x8
};
extern char gEmpty263[];  // 0x01667bac
extern volatile int gInitFlag5f497c;  // artificial; the real guard lives in .data
EmptyQueue* GetEmptyQueueSingleton() {
    static EmptyQueue s = {0, 0, 0};
    return &s;
}

// ---------------------------------------------------------------------------
// deque<TransactionPtr, 64>
struct TransactionPtr {
    RefCounted* mpObject;
    TransactionPtr() : mpObject(0) {}
    TransactionPtr(const TransactionPtr& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~TransactionPtr() { if (mpObject) mpObject->Release(); }
    TransactionPtr& operator=(const TransactionPtr& x) {
        RefCounted* const pNew = x.mpObject;
        if (pNew != mpObject) {
            RefCounted* const pOld = mpObject;
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
    void SetSubarray(T** p) {
        mpCurrentArrayPtr = p;
        mpBegin = *p;
        mpEnd = mpBegin + kSubarraySize;
    }
    DequeIterator& operator++() {
        if (++mpCurrent == mpEnd) {
            SetSubarray(mpCurrentArrayPtr + 1);
            mpCurrent = mpBegin;
        }
        return *this;
    }
    DequeIterator& operator+=(int n);  // 0x007a9a80
};
template <class T>
inline bool operator==(const DequeIterator<T>& a, const DequeIterator<T>& b) { return a.mpCurrent == b.mpCurrent; }
template <class T>
inline bool operator!=(const DequeIterator<T>& a, const DequeIterator<T>& b) { return a.mpCurrent != b.mpCurrent; }

template <class T, int kSubarraySize = 64>
struct deque {
    typedef DequeIterator<T, kSubarraySize> iterator;
    T** mpPtrArray;
    uint32_t mnPtrArraySize;
    iterator mItBegin;
    iterator mItEnd;
    eastl::allocator mAllocator;
    enum Side { kSideFront, kSideBack };
    void DoReallocPtrArray(uint32_t nAdditionalCapacity, Side allocationSide);
    T* DoAllocateSubarray() { return (T*)mAllocator.allocate(kSubarraySize * sizeof(T)); }
    void DoFreeSubarray(T* p) { if (p) mAllocator.deallocate(p); }
    void erase(iterator first, iterator last);
    void PushSlow(const T& value, bool bFront);
    iterator insert(iterator position, const T& value);
};

// @ 0x60f4a0
template <class T, int kSubarraySize>
void deque<T, kSubarraySize>::erase(iterator first, iterator last) {
    if (first == mItBegin && last == mItEnd) {
        for (iterator it = mItBegin; it != mItEnd; ++it) it.mpCurrent->~T();
        mItEnd = mItBegin;
        return;
    }
    iterator it = first;
    for (; last != mItEnd; ++it, ++last) *it.mpCurrent = *last.mpCurrent;
    iterator itEnd = mItEnd;
    for (; it != itEnd; ++it) it.mpCurrent->~T();
    mItEnd = it;
}

// @ 0x60eaf0
template <class T, int kSubarraySize>
void deque<T, kSubarraySize>::PushSlow(const T& value, bool bFront) {
    if (bFront) {
        if (mItBegin.mpCurrentArrayPtr == mpPtrArray) DoReallocPtrArray(1, kSideFront);
        mItBegin.mpCurrentArrayPtr[-1] = DoAllocateSubarray();
        mItBegin.SetSubarray(mItBegin.mpCurrentArrayPtr - 1);
        mItBegin.mpCurrent = mItEnd.mpEnd - 1;
        ::new (mItBegin.mpCurrent) T(value);
    } else {
        if ((mItEnd.mpCurrentArrayPtr - mpPtrArray) + 1 >= (int)mnPtrArraySize) DoReallocPtrArray(1, kSideBack);
        mItEnd.mpCurrentArrayPtr[1] = DoAllocateSubarray();
        ::new (mItEnd.mpCurrent) T(value);
        mItEnd.SetSubarray(mItEnd.mpCurrentArrayPtr + 1);
        mItEnd.mpCurrent = mItEnd.mpBegin;
    }
}

// @ 0x60f700
template <class T, int kSubarraySize>
typename deque<T, kSubarraySize>::iterator deque<T, kSubarraySize>::insert(iterator position, const T& value) {
    if (position == mItEnd) {
        PushSlow(value, false);
        return mItEnd;
    }
    return position;
}

template class deque<TransactionPtr>;

// ---------------------------------------------------------------------------
// cPollinator layout (retail): upload queue at +0x68.
struct cPollinatorReal {
    virtual void v0();
    virtual bool HandleMessage(uint32_t id, void* msg);
    char pad08[0x50];
    void* mpAsssetDirectory;   // +0x58
    uint32_t mnNextAssetIDLo;  // +0x60
    uint32_t mnNextAssetIDHi;  // +0x64
    UploadQueue mUploadQueue;  // +0x68
    deque<TransactionPtr> mTransactions;  // +0x78
};

// @ 0x60ee90
void HandlePollinateRequest(cPollinatorReal* self, QValue* entry) {
    QValue local = *entry;
    local.mKey0 = 0x30bdee3;
    RefCounted* pMeta = 0;
    // resource-manager lookup of the 0x30bdee3 resource would go here
    (void)pMeta;
    (void)self;
}

// @ 0x60f010
void NextIDReady(cPollinatorReal* self) {
    UploadQueue& q = self->mUploadQueue;
    if (q.mpBegin == q.mpEnd) return;
    if ((self->mnNextAssetIDLo & self->mnNextAssetIDHi) == 0xffffffff) return;
    QValue local = *q.mpBegin;
    for (QValue* p = q.mpBegin; p + 1 != q.mpEnd; ++p) p[0] = p[1];
    q.mpEnd = q.mpEnd - 1;
    HandlePollinateRequest(self, &local);
}

// @ 0x60f370
void UpdateAssetVariant(void* self, void* propMgr, uint32_t key) {
    (void)self;
    (void)propMgr;
    (void)key;
}

// ---------------------------------------------------------------------------
// rbtree<unsigned, pair<const unsigned, cActiveTransaction>>::erase / DoNukeSubtree
struct RbNode {
    RbNode* mpRight;   // +0x0
    RbNode* mpLeft;    // +0x4
    RbNode* mpParent;  // +0x8
    char mColor;       // +0xc
    char pad0d[3];
    uint32_t mKey;     // +0x10
    char mVal[4];      // +0x14
    RefCounted* mpShared;  // +0x18
};
struct RbTree {
    char pad0[4];
    RbNode mAnchor;         // +0x4
    uint32_t mnSize;        // +0x14
};

void RBTreeIncrement();  // 0x00921580
void RBTreeErase();      // 0x00921880

// @ 0x60f820
RbNode* RbTreeEraseNode(RbTree* self, RbNode* node) {
    --self->mnSize;
    RbNode* const pNext = node->mpLeft;  // placeholder for RBTreeIncrement result
    RBTreeErase();
    RefCounted* const pShared = node->mpShared;
    if (pShared) {
        if (_InterlockedExchangeAdd((volatile long*)((char*)pShared + 4), -1) == 1) {
            _InterlockedExchange((volatile long*)((char*)pShared + 4), 1);
            pShared->Delete(1);
        }
    }
    if (*(void**)node->mVal) ((IObj4*)node->mVal)->Release8();
    EASTL_allocator_deallocate(node);
    return pNext;
}

// @ 0x60f8a0
void RbTreeNukeSubtree(RbTree* self, RbNode* node) {
    while (node) {
        RbTreeNukeSubtree(self, node->mpRight);
        RbNode* const pLeft = node->mpLeft;
        RefCounted* const pShared = node->mpShared;
        if (pShared) {
            if (_InterlockedExchangeAdd((volatile long*)((char*)pShared + 4), -1) == 1) {
                _InterlockedExchange((volatile long*)((char*)pShared + 4), 1);
                pShared->Delete(1);
            }
        }
        if (*(void**)node->mVal) ((IObj4*)node->mVal)->Release8();
        EASTL_allocator_deallocate(node);
        node = pLeft;
    }
}
