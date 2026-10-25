// SP::cPollinator upload-queue / transaction helpers: the 16-byte upload-queue entry vector
// (push_back / DoInsertValue), NextIDReady, HandlePollinateRequest, the asset-metadata update and
// the EASTL deque<AutoRefCount<ITransaction>>::erase + rbtree<...>::erase/DoNukeSubtree instances.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- (no /EHsc).
#include "types.h"

typedef unsigned int uint32_t;

extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" long _InterlockedDecrement(volatile long*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedDecrement)
extern "C" void* __cdecl memmove(void*, const void*, uint32_t);
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
void __cdecl EASTL_allocator_deallocate(void* p);                                                                                  // 0x00f47380

#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

namespace eastl {
class allocator { public:
    void* allocate(size_t n) { return EASTL_allocator_allocate((uint32_t)n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
    void deallocate(void* p) { EASTL_allocator_deallocate(p); }
};
}  // namespace eastl

// Intrusive refcounted object: virtual deleting dtor in slot 0, refcount at +4.
struct RefCounted {
    virtual void Delete(unsigned char flags);
    void AddRef() { _InterlockedExchangeAdd((volatile long*)((char*)this + 4), 1); }
    void Release() {
        long n = _InterlockedDecrement((volatile long*)((char*)this + 4));
        if (n == 0) {
            _InterlockedExchange((volatile long*)((char*)this + 4), 1);
            if (this) Delete(1);
        }
    }
};

// Little helpers matching the vtable slots used by the queue entry.
struct IObj4 {
    virtual void v0();
    virtual void AddRef4();   // +0x4
    virtual void Release8();  // +0x8
};

// Node value: identical 16-byte layout to the queue entry, but its copy constructor
// AddRefs the two ref-counted members (the queue entry itself is copied as a POD).
struct NodeValue {
    uint32_t    mKey0;   // +0x00
    IObj4*      mpA;     // +0x04  AddRef through virtual slot +4
    RefCounted* mpB;     // +0x08  AddRef through the interlked count at +4
    uint16_t    mFlags;  // +0x0c
    NodeValue() {}
    __forceinline NodeValue(const NodeValue& x) {
        mKey0 = x.mKey0;
        mpA = x.mpA;
        if (mpA) mpA->AddRef4();
        mpB = x.mpB;
        if (mpB) _InterlockedExchangeAdd((volatile long*)((char*)mpB + 4), 1);
        mFlags = x.mFlags;
    }
};

// A trivial 16-byte value (3 dwords + 2 flag bytes) for the upload queue.
struct QValue {
    uint32_t mKey0;  // +0x0
    uint32_t mKey1;  // +0x4
    uint32_t mKey2;  // +0x8
    bool     mFlag0; // +0xc
    bool     mFlag1; // +0xd
    uint8_t mPad[2];
    QValue() {}
    QValue(const QValue& x)
        : mKey0(x.mKey0), mKey1(x.mKey1), mKey2(x.mKey2), mFlag0(x.mFlag0), mFlag1(x.mFlag1) {}
    QValue& operator=(const QValue& x);
};
#pragma optimize("", off)
inline QValue& QValue::operator=(const QValue& x) {
    mKey0 = x.mKey0;
    mKey1 = x.mKey1;
    mKey2 = x.mKey2;
    mFlag0 = x.mFlag0;
    mFlag1 = x.mFlag1;
    return *this;
}
#pragma optimize("", on)

// Retail's non-full vector-insert path assigns the whole 16-byte entry (including the
// two padding bytes); the reallocation path copies only the live fields.
void QValue_assign16(QValue* dest, const QValue* src) {
    dest->mKey0 = src->mKey0;
    dest->mKey1 = src->mKey1;
    dest->mKey2 = src->mKey2;
    dest->mFlag0 = src->mFlag0;
    dest->mFlag1 = src->mFlag1;
    dest->mPad[0] = src->mPad[0];
    dest->mPad[1] = src->mPad[1];
}

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

    void DoInsertValue(QValue* value, const QValue* position);  // 0x0060ec20
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
void UploadQueue::DoInsertValue(QValue* value, const QValue* position) {
    if (mpEnd != mpCapacity) {
        if (position >= value && position < mpEnd) position = (const QValue*)((const char*)position + 16);
        if (mpEnd) ::new (mpEnd) QValue(*(QValue*)((char*)mpEnd - 16));
        FUN_00edba80(value, (char*)mpEnd - 16, mpEnd);
        QValue_assign16(value, position);
        ++mpEnd;
        return;
    }
    int n = (int)((mpEnd - mpBegin) >> 4);
    if (n <= 0)
        n = 1;
    else
        n = n * 2;
    QValue* pNew = 0;
    if (n != 0) pNew = (QValue*)EASTL_allocator_allocate(n * 16, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    QValue* pMid = QValue_copy(mpBegin, value, pNew);
    if (pMid) *pMid = *position;
    QValue* pEndNew = QValue_copy(value, mpEnd, pMid + 1);
    if (mpBegin && *(int*)((char*)mpBegin - 4) != 0) EASTL_allocator_deallocate(mpBegin);
    mpEnd = pEndNew;
    mpCapacity = pNew + n;
    mpBegin = pNew;
}

// @ 0x60ea40
void* __stdcall MakeNode(const NodeValue* src) {
    char* const pNode = (char*)EASTL_allocator_allocate(0x20, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    NodeValue* const pValue = (NodeValue*)(pNode + 0x10);
    if (pValue) ::new (pValue) NodeValue(*src);
    return pNode;
}

// @ 0x60eab0 : static empty-string / empty-container initializer.
// A function-local static 12-byte object {begin=empty, end=empty, capacity=empty+1} whose
// non-trivial destructor makes cl emit the onexit/atexit registration for it.
struct EmptyQueue {
    char* mpBegin;  // +0x0
    char* mpEnd;    // +0x4
    char* mpCap;    // +0x8
    ~EmptyQueue();
};
extern char gEmpty263[];  // 0x01667bac
EmptyQueue* GetEmptyQueueSingleton() {
    static EmptyQueue s = {gEmpty263, gEmpty263, gEmpty263 + 1};
    return &s;
}

// ---------------------------------------------------------------------------
// SP::Pollen::cITransaction: an intrusive-refcounted transaction (AddRef in vtable slot +4,
// Release in slot +8), wrapped by AutoRefCount so that every copy AddRefs and every
// destruction Releases.
struct cITransaction {
    virtual void v0();      // +0x0
    virtual void AddRef();  // +0x4
    virtual void Release(); // +0x8
};

template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { mpObject->AddRef(); }
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

// eastl::copy_impl<0, random_access_iterator_tag>::do_copy (0x00705250).
template <class T>
T* eastl_copy(T* first, T* last, T* result);

// eastl::DequeIterator: the four-pointer deque iterator. operator+= (0x007a9a80),
// operator+ (0x0060da40) and operator- (0x0060da90) live out of line.
template <class T, int kSubarraySize = 64>
struct DequeIterator {
    T*  mpCurrent;           // +0x00
    T*  mpBegin;             // +0x04
    T*  mpEnd;               // +0x08
    T** mpCurrentArrayPtr;   // +0x0c

    DequeIterator() {}
    DequeIterator(const DequeIterator& x)
        : mpCurrent(x.mpCurrent), mpBegin(x.mpBegin), mpEnd(x.mpEnd), mpCurrentArrayPtr(x.mpCurrentArrayPtr) {}

    void SetSubarray(T** pCurrentArrayPtr) {
        mpCurrentArrayPtr = pCurrentArrayPtr;
        mpBegin = *pCurrentArrayPtr;
        mpEnd = mpBegin + kSubarraySize;
    }
    DequeIterator& operator++() {
        if (++mpCurrent == mpEnd) {
            SetSubarray(mpCurrentArrayPtr + 1);
            mpCurrent = mpBegin;
        }
        return *this;
    }
    DequeIterator& operator--() {
        if (mpCurrent == mpBegin) {
            SetSubarray(mpCurrentArrayPtr - 1);
            mpCurrent = mpEnd;
        }
        --mpCurrent;
        return *this;
    }
    DequeIterator& operator+=(int n);  // 0x007a9a80

    // eastl::DequeIterator::operator+ (0x0060da40) / operator- (0x0060da90).
    DequeIterator operator+(int n) const { return DequeIterator(*this).operator+=(n); }
    DequeIterator operator-(int n) const { return DequeIterator(*this).operator+=(-n); }

    // The clever HP-STL difference formula, as in eastl (deque.h:1218).
    int operator-(const DequeIterator& x) const {
        return kSubarraySize * ((int)(mpCurrentArrayPtr - x.mpCurrentArrayPtr) - 1)
             + (int)(mpCurrent - mpBegin) + (int)(x.mpEnd - x.mpCurrent);
    }

    // DequeIterator::copy / copy_backward (0x0060f180 / 0x0060f1f0) without the
    // has_trivial_relocate memmove fast path: AutoRefCount never relocates trivially.
    DequeIterator copy(const DequeIterator& first, const DequeIterator& last) const {
        DequeIterator itFirst(first);
        DequeIterator itResult(*this);
        for (; itFirst != last; ++itFirst, ++itResult) *itResult.mpCurrent = *itFirst.mpCurrent;
        return itFirst;
    }
    void copy_backward(const DequeIterator& first, const DequeIterator& last) const {
        DequeIterator itLast(last);
        DequeIterator itResult(*this);
        for (; itLast != first; ) {
            --itLast;
            --itResult;
            *itResult.mpCurrent = *itLast.mpCurrent;
        }
    }
};
template <class T, int N>
inline bool operator==(const DequeIterator<T, N>& a, const DequeIterator<T, N>& b) { return a.mpCurrent == b.mpCurrent; }
template <class T, int N>
inline bool operator!=(const DequeIterator<T, N>& a, const DequeIterator<T, N>& b) { return a.mpCurrent != b.mpCurrent; }

template <class T, int kSubarraySize = 64>
struct deque {
    typedef DequeIterator<T, kSubarraySize> iterator;
    T** mpPtrArray;                          // +0x00
    uint32_t mnPtrArraySize;                 // +0x04
    iterator mItBegin;                       // +0x08
    iterator mItEnd;                         // +0x18
    eastl::allocator mAllocator;             // +0x28

    enum Side { kSideFront, kSideBack };
    void DoReallocPtrArray(uint32_t nAdditionalCapacity, Side allocationSide);  // 0x0060d3c0
    T* DoAllocateSubarray() { return (T*)mAllocator.allocate(kSubarraySize * sizeof(T)); }
    void DoFreeSubarray(T* p) { if (p) mAllocator.deallocate(p); }
    void DoFreeSubarrays(T** pBegin, T** pEnd) {
        while (pBegin < pEnd) DoFreeSubarray(*pBegin++);
    }

    // push_front / push_back slow paths (0x0060db40 / 0x0060dbd0).
    void DoPushFrontSlow(const T& value);  // 0x0060db40
    void DoPushBackSlow(const T& value);   // 0x0060dbd0

    void push_front(const T& value) {
        if (mItBegin.mpCurrent == mItBegin.mpBegin) {
            DoPushFrontSlow(value);
        } else {
            T* const p = --mItBegin.mpCurrent;
            if (p) ::new (p) T(value);
        }
    }
    void push_back(const T& value) {
        T* const p = mItEnd.mpCurrent;
        T* const pNew = p + 1;
        if (pNew != mItEnd.mpEnd) {
            mItEnd.mpCurrent = pNew;
            if (p) ::new (p) T(value);
        } else {
            DoPushBackSlow(value);
        }
    }

    // 0x00e2fd40 / 0x0060dae0 / 0x0060d2e0.
    void pop_front();  // 0x00e2fd40
    void pop_back();   // 0x0060dae0
    void clear();      // 0x0060d2e0

    uint32_t size() const { return (uint32_t)(mItEnd - mItBegin); }

    bool Add(cITransaction* pTransaction, bool bFront);  // 0x0060eaf0
    iterator erase(iterator position);                   // 0x0060f700
    iterator erase(iterator first, iterator last);       // 0x0060f4a0
};

// @ 0x60eaf0
template <class T, int kSubarraySize>
bool deque<T, kSubarraySize>::Add(cITransaction* pTransaction, bool bFront) {
    if (!pTransaction) return false;
    if (!bFront) {
        AutoRefCount<cITransaction> refTransaction(pTransaction);
        push_back(refTransaction);
    } else {
        AutoRefCount<cITransaction> refTransaction(pTransaction);
        push_front(refTransaction);
    }
    return true;
}

// @ 0x60f700
template <class T, int kSubarraySize>
typename deque<T, kSubarraySize>::iterator deque<T, kSubarraySize>::erase(iterator position) {
    iterator itNext(position);
    ++itNext;
    const int i = position - mItBegin;
    if (i < (int)(size() / 2)) {
        itNext.copy_backward(mItBegin, position);
        pop_front();
    } else {
        position.copy(itNext, mItEnd);
        pop_back();
    }
    return mItBegin + i;
}

// @ 0x60f4a0
template <class T, int kSubarraySize>
typename deque<T, kSubarraySize>::iterator deque<T, kSubarraySize>::erase(iterator first, iterator last) {
    if (first != mItBegin || last != mItEnd) {
        const int n = last - first;
        const int i = first - mItBegin;
        if (i < (int)((size() - n) / 2)) {
            const iterator itNewBegin = mItBegin + n;
            T** const pPtrArrayBegin = mItBegin.mpCurrentArrayPtr;
            last.copy_backward(mItBegin, first);
            for (; mItBegin != itNewBegin; ++mItBegin) mItBegin.mpCurrent->~T();
            DoFreeSubarrays(pPtrArrayBegin, itNewBegin.mpCurrentArrayPtr);
        } else {
            const iterator itNewEnd = mItEnd - n;
            T** const pPtrArrayEnd = itNewEnd.mpCurrentArrayPtr + 1;
            first.copy(last, mItEnd);
            for (iterator itTemp(itNewEnd); itTemp != mItEnd; ++itTemp) itTemp.mpCurrent->~T();
            DoFreeSubarrays(pPtrArrayEnd, mItEnd.mpCurrentArrayPtr + 1);
            mItEnd = itNewEnd;
        }
        return mItBegin + i;
    }
    clear();
    return mItEnd;
}

typedef AutoRefCount<cITransaction> TransactionPtr;
typedef deque<TransactionPtr, 64> TransactionDeque;
typedef DequeIterator<TransactionPtr, 64> TxnIterator;
template class deque<TransactionPtr, 64>;

// ---------------------------------------------------------------------------
// The resource-manager key and the upload-queue entry (a 12-byte key plus two flags in a
// 16-byte slot; the trailing two bytes are padding).
struct ResourceKey {
    uint32_t instanceID;  // +0x0
    uint32_t typeID;      // +0x4
    uint32_t groupID;     // +0x8
};
struct cUploadRequest {
    ResourceKey mKey;   // +0x00
    bool        mbA;    // +0x0c
    bool        mbB;    // +0x0d
    uint8_t     mPad[2];  // +0x0e
    cUploadRequest() {}
};

// The server id of an asset: {lo, hi}.
struct U64Pair {
    uint32_t lo;
    uint32_t hi;
};

// SP::Pollen::cAssetMetadata: Release in vtable slot +4, Cast(typeID) in slot +0xc.
struct cAssetMetadata {
    virtual void AddRef();               // +0x0
    virtual void Release();              // +0x4
    virtual void v2();                   // +0x8
    virtual void* Cast(uint32_t typeID); // +0xc
    U64Pair* GetServerID();                      // 0x005507a0
    void SetServerID(uint32_t lo, uint32_t hi);  // 0x00551af0
};

bool __cdecl GetAssetMetadata(const ResourceKey& key, cAssetMetadata** ppMetadata);  // 0x00552450

// The resource manager the pollinator talks to: GetResource in vtable slot +0xc,
// WriteResource in slot +0x20, CacheResource in slot +0x6c.
struct IResourceManager {
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual bool GetResource(const ResourceKey& key, cAssetMetadata** ppMetadata,
                             uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // +0xc
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void WriteResource(cAssetMetadata* pMetadata, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // +0x20
    virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void CacheResource(cAssetMetadata* pMetadata, int bCache);  // +0x6c
};
IResourceManager* __cdecl GetManager();  // 0x0067dcd0

// A property manager plus the variant it accepts (0x0061fdb0 / 0x0061df20).
struct EA_Variant {
    char mData[0x10];  // +0x00
    uint16_t mFlags;   // +0x10
    uint16_t mTypeId;  // +0x12
    EA_Variant() { mFlags = 0; mTypeId = 0; }
    EA_Variant(uint32_t a, uint32_t b) { mFlags = 0; mTypeId = 0; Construct(0xc, 0x18, a, 8, b); }
    ~EA_Variant() { if (mFlags & 4) Destruct(0); }
    void Construct(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);  // 0x0093dd80
    void Destruct(int);                                                                          // 0x0093db80
    EA_Variant& operator=(const EA_Variant& x);                                                  // 0x00542b80
};
struct cPropertyManager {
    void SetProperty(uint32_t id, EA_Variant* pVariant);  // 0x0061fdb0
};
cPropertyManager* __cdecl GetPropertyManager();  // 0x0061df20

// The 8-byte-element vector used to build the variant's payload (reserve 0x004756f0,
// push_back 0x00475800).
struct U64Vector {
    uint64_t* mpBegin;    // +0x0
    uint64_t* mpEnd;      // +0x4
    uint64_t* mpCapacity; // +0x8
    void reserve(size_t n);              // 0x004756f0
    void push_back(const uint64_t& x);   // 0x00475800
};

// A server-id -> thumbnail exporter (GetImportExport 0x005f7930, UpdateExportThumb 0x005fb430).
struct cImportExport {
    void UpdateExportThumb();  // 0x005fb430
};
cImportExport* __stdcall GetImportExport(const ResourceKey* pKey);  // 0x005f7930

// The transaction built for an accepted pollinate request.
struct cAssetUploadTransaction {
    void* Ctor(cAssetMetadata* pMetadata, void* pAssetDirectory,
               uint32_t a, uint32_t b, uint32_t c);  // 0x00615d30
};
void* __cdecl AllocTransaction(size_t size);  // 0x00615810

// SP::Pollen::cAssetDirectory sits at +0x58 (used here only as an opaque argument).
struct cAssetDirectory;

// ---------------------------------------------------------------------------
// SP::cPollinator: the transaction queue at +0x08, the asset directory at +0x58, the next
// server id at +0x60/+0x64 and the upload queue at +0x68.
struct cPollinator {
    virtual void v0();
    virtual void v1();
    uint32_t mPad04;                   // +0x04
    TransactionDeque mTransactions;    // +0x08 (0x2c bytes)
    char mPad34[0x58 - 0x34];          // +0x34
    cAssetDirectory* mpAssetDirectory; // +0x58
    uint32_t mPad5c;                   // +0x5c
    uint32_t mnNextAssetIDLo;          // +0x60
    uint32_t mnNextAssetIDHi;          // +0x64
    UploadQueue mUploadQueue;          // +0x68

    void NextIDReady();                                                          // 0x0060f010
    void HandlePollinateRequest(const ResourceKey& key, bool a, bool b);         // 0x0060ee90
    void UpdateAssetVariant(uint32_t propID, const ResourceKey* pKey, uint64_t value);  // 0x0060f370
    void OnGameEvent(const ResourceKey& key);                                    // 0x0060cf30
};

// @ 0x60f010
void cPollinator::NextIDReady() {
    if (mUploadQueue.mpBegin == mUploadQueue.mpEnd) return;
    if ((mnNextAssetIDLo & mnNextAssetIDHi) == 0xffffffffu) return;
    QValue* const pBegin = mUploadQueue.mpBegin;
    cUploadRequest req;
    req.mKey.instanceID = pBegin->mKey0;
    req.mKey.typeID = pBegin->mKey1;
    req.mKey.groupID = pBegin->mKey2;
    req.mbA = pBegin->mFlag0;
    req.mbB = pBegin->mFlag1;
    if (pBegin + 1 < mUploadQueue.mpEnd) eastl_copy(pBegin + 1, mUploadQueue.mpEnd, pBegin);
    mUploadQueue.mpEnd = mUploadQueue.mpEnd - 1;
    HandlePollinateRequest(req.mKey, req.mbA, req.mbB);
}

// @ 0x60ee90
void cPollinator::HandlePollinateRequest(const ResourceKey& key, bool a, bool b) {
    ResourceKey localKey = key;
    localKey.typeID = 0x30bdee3;
    cAssetMetadata* pMetadata = 0;
    IResourceManager* pMgr = GetManager();
    if (pMetadata) {
        cAssetMetadata* const pTmp = pMetadata;
        pMetadata = 0;
        pTmp->Release();
    }
    if (pMgr->GetResource(localKey, &pMetadata, 0, 0, 0, 0)) {
        cAssetMetadata* pMeta = 0;
        if (pMetadata) pMeta = (cAssetMetadata*)pMetadata->Cast(0x30bdee3);
        U64Pair* const pServerID = pMeta->GetServerID();
        if ((pServerID->lo & pServerID->hi) == 0xffffffffu) {
            pMeta->SetServerID(mnNextAssetIDLo, mnNextAssetIDHi);
            GetManager()->WriteResource(pMetadata, 0, 0, 0, 0);
            GetManager()->CacheResource(pMetadata, 1);
            GetImportExport(&key)->UpdateExportThumb();
        }
        mnNextAssetIDLo = 0xffffffffu;
        mnNextAssetIDHi = 0xffffffffu;
        cAssetUploadTransaction* pTransaction = 0;
        void* const pMemory = AllocTransaction(0x30);
        if (pMemory)
            pTransaction = (cAssetUploadTransaction*)((cAssetUploadTransaction*)pMemory)->Ctor(
                pMeta, mpAssetDirectory, a, b, 0);
        if (pTransaction) {
            AutoRefCount<cITransaction> ref((cITransaction*)pTransaction);
            mTransactions.push_front(ref);
        }
        OnGameEvent(key);
    }
    if (pMetadata) pMetadata->Release();
}

// @ 0x60f370
void cPollinator::UpdateAssetVariant(uint32_t propID, const ResourceKey* pKey, uint64_t value) {
    if (!mpAssetDirectory) return;
    cAssetMetadata* pMetadata = 0;
    if (GetAssetMetadata(*pKey, &pMetadata)) {
        U64Pair sid = *pMetadata->GetServerID();
        if ((sid.lo & sid.hi) != 0xffffffffu) {
            cPropertyManager* const pMgr = GetPropertyManager();
            if (pMgr) {
                U64Vector ids;
                ids.mpBegin = 0;
                ids.mpEnd = 0;
                ids.mpCapacity = 0;
                ids.reserve(2);
                ids.push_back(*(uint64_t*)&sid);
                ids.push_back(value);
                uint64_t* const pIdsBegin = ids.mpBegin;
                EA_Variant var;
                var = EA_Variant((uint32_t)pIdsBegin, 2);
                pMgr->SetProperty(propID, &var);
                if (pIdsBegin && *(int*)((char*)pIdsBegin - 4) != 0) EASTL_allocator_deallocate(pIdsBegin);
            }
        }
    }
    if (pMetadata) pMetadata->Release();
}

// ---------------------------------------------------------------------------
// The cPollinator transaction map: rbtree<unsigned, pair<const unsigned, cActiveTransaction>>.
// The two members this slice covers are erase (0x0060f820) and DoNukeSubtree (0x0060f8a0).
// The node adds the key at +0x10 and the 8-byte transaction value at +0x14 whose destructor
// drops its two reference-counted members (+0x18 first, then +0x14).
struct ActiveTransaction {
    IObj4*      mpTransaction;  // +0x14  polymorphic, Release in vtable slot +8
    RefCounted* mpRef;          // +0x18  interlocked refcount at +4
    ~ActiveTransaction() {
        if (mpRef) mpRef->Release();
        if (mpTransaction) mpTransaction->Release8();
    }
};

// rbtree_node_base: 16 bytes, the anchor only ever uses this prefix.
struct RbNodeBase {
    RbNodeBase* mpNodeRight;  // +0x0
    RbNodeBase* mpNodeLeft;   // +0x4
    RbNodeBase* mpNodeParent; // +0x8
    char mColor;              // +0xc
    char pad0d[3];
};

struct RbNode : RbNodeBase {
    uint32_t mKey;              // +0x10
    ActiveTransaction mValue;   // +0x14
};

RbNodeBase* RBTreeIncrement(const RbNodeBase* pNode);              // 0x00921580
void RBTreeErase(RbNodeBase* pNode, RbNodeBase* pNodeAnchor);      // 0x00921880

// A 4-byte iterator with a user-declared copy constructor, so the returned object is
// built through the hidden return pointer (first argument), as in retail.
struct RbIter {
    RbNode* mpNode;
    RbIter() : mpNode(0) {}
    explicit RbIter(RbNode* pNode) : mpNode(pNode) {}
    RbIter(const RbIter& x) : mpNode(x.mpNode) {}
    RbIter& operator++() { mpNode = (RbNode*)RBTreeIncrement(mpNode); return *this; }
};

struct RbTree {
    int mCompare;         // +0x0
    RbNodeBase mAnchor;   // +0x4
    uint32_t mnSize;      // +0x14

    void DoFreeNode(RbNode* pNode) {
        pNode->mValue.~ActiveTransaction();
        EASTL_allocator_deallocate(pNode);
    }

// @ 0x60f820
    RbIter erase(RbIter position) {
        const RbIter iErase(position);
        --mnSize;
        ++position;
        RBTreeErase(iErase.mpNode, &mAnchor);
        DoFreeNode(iErase.mpNode);
        return position;
    }

// @ 0x60f8a0
    void DoNukeSubtree(RbNode* pNode) {
        while (pNode) {
            DoNukeSubtree((RbNode*)pNode->mpNodeRight);
            RbNode* const pNodeLeft = (RbNode*)pNode->mpNodeLeft;
            DoFreeNode(pNode);
            pNode = pNodeLeft;
        }
    }
};

// Nothing else in this TU calls the two members; taking their addresses keeps the
// out-of-line instantiations the slice targets alive.
void (RbTree::*gRbTreeNukeSubtree)(RbNode*) = &RbTree::DoNukeSubtree;
RbIter (RbTree::*gRbTreeErase)(RbIter) = &RbTree::erase;
