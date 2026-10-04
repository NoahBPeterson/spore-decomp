// Slice s0060d860: SP::cPollinator helpers (asset-id -> variant property updates), an EASTL deque of
// intrusive-refcounted objects (iterators, push_front/push_back slow paths, remove_copy_if, dtor),
// the cJobResultMessage destructor and the "pollen" console cheat (SP::cPollinatorCheat::Execute).
// Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)
extern "C" unsigned long __cdecl strtoul(const char*, char**, int);
inline void* operator new(unsigned int, void* p) { return p; }

void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
void __cdecl EASTL_allocator_deallocate(void* p);                                                                                  // 0x00f47380

#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

namespace EA {
namespace ResourceMan {
struct Key {
    uint32_t instanceID, typeID, groupID;
};
}
using ResourceMan::Key;

// Atomic intrusive refcount with a virtual deleting destructor in slot 0 (RefCountVTemplate-like).
struct AtomicInt {
    volatile long mValue;
    long Increment() { return _InterlockedExchangeAdd(&mValue, 1) + 1; }
    long Decrement() { return _InterlockedExchangeAdd(&mValue, -1) - 1; }
    void SetValue(long v) { _InterlockedExchange(&mValue, v); }
};
struct RefCounted {
    virtual ~RefCounted();
    AtomicInt mRefCount;
    void AddRef() { mRefCount.Increment(); }
    void Release() {
        if (mRefCount.Decrement() == 0) {
            mRefCount.SetValue(1);
            delete this;
        }
    }
};
template <class T>
struct AutoRefCount {
    T* mpObject;
    ~AutoRefCount() {
        if (mpObject) mpObject->Release();
    }
};

struct U64Pair {
    uint32_t lo, hi;
};
struct Variant {
    char mData[16];
    uint16_t mFlags;
    uint16_t mTypeId;
    void Construct(const U64Pair* p);                                                     // 0x0060cfa0
    void Construct(uint32_t type, uint32_t size, uint32_t a, uint32_t b, uint32_t c);      // 0x0093dd80
    void Destruct(int);                                                                    // 0x0093db80
    Variant(const U64Pair* p) {
        mTypeId = 0;
        mFlags = 0;
        Construct(p);
    }
    Variant(uint32_t a, uint32_t b) {
        mFlags = 0;
        mTypeId = 0;
        Construct(0xc, 0x18, a, 8, b);
    }
    ~Variant() {
        if (mFlags & 4) Destruct(0);
    }
};
}  // namespace EA
using EA::Key;

// ---------------------------------------------------------------------------------------------
// Intrusive-refcounted message-like object (AddRef = slot 1, Release = slot 2).
struct IQueued {
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    virtual void v3();
    virtual uint32_t GetId();                          // +0x10
    virtual void v5();
    virtual void Notify(uint32_t, uint32_t, uint32_t);  // +0x18
    virtual void v7();
    virtual bool IsCancelled();                        // +0x20
};

struct QueuedPtr {
    IQueued* mpObject;
    QueuedPtr(const QueuedPtr& x) : mpObject(x.mpObject) {
        if (mpObject) mpObject->AddRef();
    }
    QueuedPtr& operator=(const QueuedPtr& x) {
        IQueued* const pNew = x.mpObject;
        if (pNew != mpObject) {
            IQueued* const pTemp = mpObject;
            if (pNew) pNew->AddRef();
            mpObject = pNew;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    operator IQueued*() const { return mpObject; }
    ~QueuedPtr() {
        if (mpObject) mpObject->Release();
    }
};

namespace eastl {
struct allocator {
    void* allocate(size_t n) { return EASTL_allocator_allocate(n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
    void deallocate(void* p) { EASTL_allocator_deallocate(p); }
};

template <class T, int kSubarraySize = 64>
struct DequeIterator {
    T* mpCurrent;
    T* mpBegin;
    T* mpEnd;
    T** mpCurrentArrayPtr;

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
    DequeIterator& operator+=(int n);  // 0x007a9a80
    DequeIterator& operator-=(int n) { return (*this).operator+=(-n); }
    DequeIterator operator+(int n) const { return DequeIterator(*this).operator+=(n); }
    DequeIterator operator-(int n) const { return DequeIterator(*this).operator-=(n); }
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
    allocator mAllocator;

    enum Side { kSideFront, kSideBack };
    void DoReallocPtrArray(uint32_t nAdditionalCapacity, Side allocationSide);  // 0x0060d3c0
    T* DoAllocateSubarray() { return (T*)mAllocator.allocate(kSubarraySize * sizeof(T)); }
    void DoFreePtrArray(T** p) {
        if (p) mAllocator.deallocate(p);
    }
    void DoFreeSubarray(T* p) {
        if (p) mAllocator.deallocate(p);
    }

    void pop_back();                       // 0x0060dae0
    void DoPushFrontSlow(const T& value);  // 0x0060db40
    void DoPushBackSlow(const T& value);   // 0x0060dbd0
    ~deque();                              // 0x0060e660
};

template <class T, int N>
void deque<T, N>::pop_back() {
    if (mItEnd.mpCurrent != mItEnd.mpBegin) {
        --mItEnd.mpCurrent;
        mItEnd.mpCurrent->~T();
    } else {
        DoFreeSubarray(mItEnd.mpBegin);
        mItEnd.SetSubarray(mItEnd.mpCurrentArrayPtr - 1);
        mItEnd.mpCurrent = mItEnd.mpEnd - 1;
        mItEnd.mpCurrent->~T();
    }
}

template <class T, int N>
void deque<T, N>::DoPushFrontSlow(const T& value) {
    T valueSaved(value);
    if (mItBegin.mpCurrentArrayPtr == mpPtrArray) DoReallocPtrArray(1, kSideFront);
    mItBegin.mpCurrentArrayPtr[-1] = DoAllocateSubarray();
    mItBegin.SetSubarray(mItBegin.mpCurrentArrayPtr - 1);
    mItBegin.mpCurrent = mItBegin.mpEnd - 1;
    ::new (mItBegin.mpCurrent) T(valueSaved);
}

template <class T, int N>
void deque<T, N>::DoPushBackSlow(const T& value) {
    T valueSaved(value);
    if ((mItEnd.mpCurrentArrayPtr - mpPtrArray) + 1 >= (int)mnPtrArraySize) DoReallocPtrArray(1, kSideBack);
    mItEnd.mpCurrentArrayPtr[1] = DoAllocateSubarray();
    ::new (mItEnd.mpCurrent) T(valueSaved);
    mItEnd.SetSubarray(mItEnd.mpCurrentArrayPtr + 1);
    mItEnd.mpCurrent = mItEnd.mpBegin;
}

template <class T, int N>
deque<T, N>::~deque() {
    for (iterator itCurrent(mItBegin); itCurrent != mItEnd; ++itCurrent) itCurrent.mpCurrent->~T();
    if (mpPtrArray) {
        T** const pEnd = mItEnd.mpCurrentArrayPtr + 1;
        for (T** pCurrent = mItBegin.mpCurrentArrayPtr; pCurrent < pEnd; ++pCurrent) DoFreeSubarray(*pCurrent);
        DoFreePtrArray(mpPtrArray);
    }
}
}  // namespace eastl

typedef eastl::deque<QueuedPtr> QueuedDeque;
typedef eastl::DequeIterator<QueuedPtr> QueuedIter;

// Predicates with side effects used by remove_if.
struct CancelByIdPred {
    uint32_t mId, mArg;
    bool operator()(IQueued* pObj) const {
        if (pObj->GetId() == mId) {
            pObj->Notify(8, 0, mArg);
            return true;
        }
        return false;
    }
};
struct CancelCancelledPred {
    uint32_t mArg;
    bool operator()(IQueued* pObj) const {
        if (pObj->IsCancelled()) {
            pObj->Notify(8, 0, mArg);
            return true;
        }
        return false;
    }
};

namespace eastl {
template <class P>
QueuedIter remove_copy_if(QueuedIter first, QueuedIter last, QueuedIter result, P pred) {
    for (; first != last; ++first) {
        if (!pred(*first.mpCurrent)) {
            *result.mpCurrent = *first.mpCurrent;
            ++result;
        }
    }
    return result;
}
QueuedIter find_if(QueuedIter first, QueuedIter last, CancelByIdPred pred);        // 0x0060d000
QueuedIter find_if(QueuedIter first, QueuedIter last, CancelCancelledPred pred);   // 0x0060d0a0
template <class P>
QueuedIter remove_if(QueuedIter first, QueuedIter last, P pred) {
    first = find_if(first, last, pred);
    if (first != last) {
        QueuedIter i(first);
        return remove_copy_if(++i, last, first, pred);
    }
    return first;
}
}  // namespace eastl

// ---------------------------------------------------------------------------------------------
namespace SP {
namespace Pollen {
struct cAssetMetadata {
    virtual int AddRef();
    virtual int Release();
    const EA::U64Pair* GetServerId();  // 0x005507a0 (not virtual)
};
bool GetAssetMetadata(const Key& key, cAssetMetadata** ppMetadata);  // 0x00552450
struct cAssetDirectory {
    bool GetLocalKey(uint64_t serverId, Key* pKey) const;                       // 0x0054e460
    bool GetServerId(const Key& key, uint64_t* pServerId, bool bLoad) const;    // 0x0054e530
};
}  // namespace Pollen

struct cPropertyManager {
    void SetProperty(uint32_t id, EA::Variant* v);                              // 0x0061fdb0
    void SetProperty2(uint32_t id, uint32_t lo, uint32_t hi, EA::Variant* v);   // 0x0061fee0
};
cPropertyManager* GetPropertyManager();  // 0x0061df20

struct cPollinator {
    virtual void v0();
    virtual bool HandleMessage(uint32_t id, void* msg);
    char pad[0x54];
    Pollen::cAssetDirectory* mpAsssetDirectory;  // +0x58

    void UpdateProperty(uint32_t id, const Key& key);                                  // 0x0060d860
    void UpdateProperty2(uint32_t id, const Key* key, EA::Variant* v);                 // 0x0060d920
    void UpdatePropertyInt(uint32_t id, const Key* key, uint32_t a, uint32_t b);       // 0x0060e600
};
cPollinator* GetPollinator();  // 0x0067cb30

// @ 0x0060d860
void cPollinator::UpdateProperty(uint32_t id, const Key& key) {
    if (mpAsssetDirectory) {
        EA::U64Pair serverId = {0xffffffff, 0xffffffff};
        Pollen::cAssetMetadata* pMetadata = 0;
        if (Pollen::GetAssetMetadata(key, &pMetadata)) serverId = *pMetadata->GetServerId();
        if ((serverId.lo & serverId.hi) != 0xffffffff) {
            if (cPropertyManager* pMgr = GetPropertyManager()) {
                EA::Variant v(&serverId);
                pMgr->SetProperty(id, &v);
            }
        }
        if (pMetadata) pMetadata->Release();
    }
}

// @ 0x0060d920
void cPollinator::UpdateProperty2(uint32_t id, const Key* key, EA::Variant* v) {
    Pollen::cAssetMetadata* pMetadata = 0;
    if (Pollen::GetAssetMetadata(*key, &pMetadata)) {
        EA::U64Pair serverId = *pMetadata->GetServerId();
        if ((serverId.lo & serverId.hi) != 0xffffffff) {
            if (cPropertyManager* pMgr = GetPropertyManager()) pMgr->SetProperty2(id, serverId.lo, serverId.hi, v);
        }
    }
    if (pMetadata) pMetadata->Release();
}

// @ 0x0060e600
void cPollinator::UpdatePropertyInt(uint32_t id, const Key* key, uint32_t a, uint32_t b) {
    EA::Variant v(a, b);
    UpdateProperty2(id, key, &v);
}
}  // namespace SP

// ---------------------------------------------------------------------------------------------
struct cTextureAsyncQueueEntry {
    struct cTextureInstanceInternal* mTexture;
};
template struct eastl::DequeIterator<cTextureAsyncQueueEntry>;  // 0x0060da40 operator+, 0x0060da90 operator-

template struct eastl::deque<QueuedPtr>;
template QueuedIter eastl::remove_if<CancelByIdPred>(QueuedIter, QueuedIter, CancelByIdPred);              // 0x0060e6e0
template QueuedIter eastl::remove_if<CancelCancelledPred>(QueuedIter, QueuedIter, CancelCancelledPred);    // 0x0060e800

// @ 0x0060d9f0
struct QueueSource {
    QueuedPtr mPtr;
    EA::RefCounted* mpShared;
    uint16_t mFlags;
};
struct QueueEntry {
    uint32_t mId;
    QueuedPtr mPtr;
    EA::RefCounted* mpShared;
    uint16_t mFlags;
    QueueEntry(const uint32_t* id, const QueueSource* s) : mId(*id), mPtr(s->mPtr), mpShared(s->mpShared) {
        if (mpShared) mpShared->AddRef();
        mFlags = s->mFlags;
    }
};
QueueEntry* MakeQueueEntry(QueueEntry* p, const uint32_t* id, const QueueSource* s) { return new (p) QueueEntry(id, s); }

// ---------------------------------------------------------------------------------------------
struct IMessageRC {
    virtual ~IMessageRC() {}
    virtual int AddRef();
    virtual int Release();
};
struct RefCountVTemplate {
    virtual ~RefCountVTemplate() {}
    volatile long mRefCount;
};
namespace SP {
// @ 0x0060df50 (scalar deleting destructor)
struct cJobResultMessage : public IMessageRC, public RefCountVTemplate {
    uint32_t mnJobId;
    uint32_t mnJobResult;
    EA::AutoRefCount<EA::RefCounted> mpIncomingMessage;  // +0x14
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
cJobResultMessage* NewJobResult() { return new cJobResultMessage; }
}  // namespace SP

// @ 0x0060e5b0 (destructor body of a holder of a message pointer + refcounted response)
struct JobHolder {
    uint32_t mField0;
    QueuedPtr mpMessage;                               // +4
    EA::AutoRefCount<EA::RefCounted> mpResponse;       // +8
    void Destroy() { this->~JobHolder(); }
    ~JobHolder() {}
};

// ---------------------------------------------------------------------------------------------
// @ 0x0060e540: posts a UI::BehaviorMessage carrying a float.
void* operator new(size_t, const char*, int, int, const char*, int);
void operator delete(void*, const char*, int, int, const char*, int);

struct MessageBase {
    virtual ~MessageBase() {}
    EA::AtomicInt mRefCount;
    MessageBase() { mRefCount.SetValue(0); }
};
struct MessageData {
    float mValue;
    char pad[0x24];
    uint32_t mMessageId;
    MessageData(uint32_t id) : mMessageId(id) {}
};
struct BehaviorMessage : public MessageData, public MessageBase {
    uint32_t pad34;
    uint32_t mField38;
    uint32_t pad3c;
    BehaviorMessage() : MessageData(0x656435b), mField38(0) {}
};
struct cMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void PostMessage(uint32_t id, void* pMsg, int a, int b);   // +0x18
    virtual void s7(); virtual void s8();
    virtual void RegisterHandler(void* pHandler, uint32_t id);          // +0x24
};
cMessageServer* GetMessageServer();  // 0x0067dcc0

void PostBehaviorFloat(float value) {
    BehaviorMessage* pMsg = new ("Pollinator", 0, 0, 0, 0) BehaviorMessage();
    pMsg->mValue = value;
    GetMessageServer()->PostMessage(0x656435b, pMsg, 0, 0);
}

// ---------------------------------------------------------------------------------------------
namespace EA {
namespace ArgScript {
struct Line {
    bool HasOption(const char* name);                                                    // 0x00837ee0
    const char** GetOption(const char* name, size_t count);                              // 0x00838330
    const char** GetOptionRange(const char* name, size_t* count, size_t nMin, size_t nMax);  // 0x00838130
    bool HasFlag(const char* name);                                                      // 0x008380b0
};
void __cdecl Output(void* pOut, const char* fmt, ...);  // 0x00841000
}  // namespace ArgScript
}  // namespace EA
using EA::ArgScript::Line;
using EA::ArgScript::Output;

namespace SP {
bool GetTypeFromName(const char* name, uint32_t* pType);  // 0x0060ccf0 (anonymous namespace)
}
uint64_t __cdecl StrToU64(const char* s, char** end, int base);       // 0x0092d6f0
void __cdecl SPKeyFromName(Key* pKey, const char* name, int a, int b);  // 0x0068d5a0

struct SimpleString {
    const char* mpBegin;
    const char* mpEnd;
    const char* mpCapacity;
    SimpleString() : mpBegin((const char*)0x1667bac), mpEnd((const char*)0x1667bac), mpCapacity((const char*)0x1667bad) {}
    ~SimpleString() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin) EASTL_allocator_deallocate((void*)mpBegin);
    }
};
void __cdecl DescribeKey(const Key* pKey, SimpleString* pOut);  // 0x00563de0

namespace SP {
struct cPollinatorCheat {
    void* vtbl;
    void* mpOutput;  // +4
    uint32_t pad8, padC;
    void* mHandlerVtbl;   // +0x10 (message handler subobject)
    int mnFlood;          // +0x14
    void Execute(Line& args);  // 0x0060dfb0
};

// @ 0x0060dfb0
void cPollinatorCheat::Execute(Line& args) {
    cPollinator* pPollinator = GetPollinator();
    size_t nArgs;
    if (args.HasOption("get")) {
        const char** a = args.GetOption("get", 1);
        if (a) {
            uint64_t assetId = StrToU64(a[0], 0, 10);
            pPollinator->HandleMessage(0x192dc39, &assetId);
        } else {
            Output(mpOutput, "Usage:\n pollen -get <assetID>\n");
        }
    }
    if (args.HasOption("getBatch")) {
        const char** a = args.GetOption("getBatch", 2);
        if (a) {
            struct { uint32_t type, count; } req;
            if (GetTypeFromName(a[0], &req.type)) {
                req.count = strtoul(a[1], 0, 10);
                if (req.count <= 1000) {
                    pPollinator->HandleMessage(0x19168dd, &req);
                    return;
                }
                Output(mpOutput, "Sorry - maximum batch size is 1000. Try a smaller number...\n");
                return;
            }
            Output(mpOutput, "Unknown type name : %s. Use one of\n", a[0]);
            Output(mpOutput, "\tCell\n");
            Output(mpOutput, "\tCreature\n");
            Output(mpOutput, "\tTribeCreature\n");
            Output(mpOutput, "\tCivCreature\n");
            Output(mpOutput, "\tSpaceCreature\n");
            Output(mpOutput, "\tBuildingCityHall\n");
            Output(mpOutput, "\tBuildingHouse\n");
            Output(mpOutput, "\tBuildingFarm\n");
            Output(mpOutput, "\tBuildingIndustry\n");
            Output(mpOutput, "\tBuildingEntertainment\n");
            Output(mpOutput, "\tVehicleMilitaryLand\n");
            Output(mpOutput, "\tVehicleMilitaryWater\n");
            Output(mpOutput, "\tVehicleMilitaryAir\n");
            Output(mpOutput, "\tVehicleEconomicLand\n");
            Output(mpOutput, "\tVehicleEconomicWater\n");
            Output(mpOutput, "\tVehicleEconomicAir\n");
            Output(mpOutput, "\tVehicleCulturalLand\n");
            Output(mpOutput, "\tVehicleCulturalWater\n");
            Output(mpOutput, "\tVehicleCulturalAir\n");
            Output(mpOutput, "\tVehicleHarvester\n");
            Output(mpOutput, "\tVehicleColonyLand\n");
            Output(mpOutput, "\tVehicleColonyWater\n");
            Output(mpOutput, "\tVehicleColonyAir\n");
            Output(mpOutput, "\tVehicleUFO\n");
            Output(mpOutput, "\tPlantSmall\n");
            Output(mpOutput, "\tPlantMedium\n");
            Output(mpOutput, "\tPlantLarge\n");
            return;
        }
        Output(mpOutput, "Usage:\n pollen -getBatch <type:creature|building|vehicle> <count:integer>\n");
    }
    if (args.HasOption("serverID")) {
        Key key = {0, 0, 0};
        const char** a = args.GetOptionRange("serverID", &nArgs, 1, 3);
        if (nArgs == 1) {
            SPKeyFromName(&key, a[0], 0, 0);
        } else if (nArgs == 3) {
            key.typeID = strtoul(a[0], 0, 0);
            key.groupID = strtoul(a[1], 0, 0);
            key.instanceID = strtoul(a[2], 0, 0);
        } else {
            Output(mpOutput, "Usage: -serverID [<key name> | <hex triplet>]\n");
            goto queryIdSection;
        }
        uint64_t serverId;
        if (pPollinator->mpAsssetDirectory->GetServerId(key, &serverId, false))
            Output(mpOutput, "Server Asset ID = %I64u\n", serverId);
        else
            Output(mpOutput, "Server ID unknown\n");
        SimpleString desc;
        DescribeKey(&key, &desc);
        if (desc.mpBegin != desc.mpEnd)
            Output(mpOutput, desc.mpBegin);
        else
            Output(mpOutput, "Couldn't find metadata\n");
    }
queryIdSection:
    if (args.HasOption("queryID")) {
        const char** a = args.GetOptionRange("queryID", &nArgs, 1, 1);
        Pollen::cAssetDirectory* pDir = pPollinator->mpAsssetDirectory;
        Key key = {0, 0, 0};
        if (pDir->GetLocalKey(StrToU64(a[0], 0, 0), &key)) {
            SimpleString desc;
            DescribeKey(&key, &desc);
            if (desc.mpBegin != desc.mpEnd)
                Output(mpOutput, desc.mpBegin);
            else
                Output(mpOutput, "Known server ID (0x%08x:0x%08x:0x%08x), but couldn't find metadata\n", key.typeID, key.groupID, key.instanceID);
        } else {
            Output(mpOutput, "Unknown server ID\n");
        }
    }
    if (args.HasOption("flood")) {
        const char** a = args.GetOption("flood", 1);
        if (a) {
            mnFlood = (int)strtoul(a[0], 0, 10) - 1;
            GetMessageServer()->RegisterHandler(&mHandlerVtbl, 0x269c832);
            pPollinator->HandleMessage(0x632d709, 0);
        } else {
            Output(mpOutput, "Usage:\n pollen -flood <flood count>\n");
        }
    }
    if (args.HasFlag("floodstop") && mnFlood) mnFlood = 0;
}
}  // namespace SP
